#include <CppUtil/Engine/OptixAIDenoiser.h>
#include <CppUtil/Basic/Image.h>

#undef min
#undef max
#define NOMINMAX
#include <optix_world.h>

using namespace CppUtil::Engine;
using namespace CppUtil::Basic;
using namespace std;

optix::Context optix_context;
optix::Buffer input_buffer;
optix::Buffer output_buffer;
optix::PostprocessingStage denoiserStage;
optix::CommandList commandList;

void jobStart(int width, int height, float blend);
void jobComplete();
void denoiseImplement(float * img, int w, int h, float blend, bool is_batch);

void OptixAIDenoiser::Denoise(Image::Ptr img) {
	int w = img->GetWidth();
	int h = img->GetHeight();
	if (!init) {
		jobStart(w, h, 0.05f);
		width = w;
		height = h;
	} else if (width != w || height != h) {
		jobComplete();
		jobStart(w, h, 0.05f);
		width = w;
		height = h;
	}

	float * imgf = new float[4 * w*h];
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++){
			if (img->GetChannel() == 4) {
				auto pixel = img->GetPixel_F(x, y);
				for (int c = 0; c < 4; c++) {
					imgf[y*(w * 4) + x * 4 + c] = pixel[c];
				}
			}
			else {
				auto pixel = img->GetPixel_F(x, y);
				for (int c = 0; c < 3; c++) {
					imgf[y*(w * 4) + x * 4 + c] = pixel[c];
				}
				imgf[y*(w * 4) + x * 4 + 3] = 1.0f;
			}
		}

	}

	denoiseImplement(imgf, w, h, 0.05f, false);

	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			if (img->GetChannel() == 4) {
				img->SetPixel(x, y, glm::vec4(
					imgf[y*(w * 4) + x * 4],
					imgf[y*(w * 4) + x * 4 + 1],
					imgf[y*(w * 4) + x * 4 + 2],
					imgf[y*(w * 4) + x * 4 + 3]));
			}
			else {
				img->SetPixel(x, y, glm::vec3(
					imgf[y*(w * 4) + x * 4],
					imgf[y*(w * 4) + x * 4 + 1],
					imgf[y*(w * 4) + x * 4 + 2]));
			}
		}
	}

	delete imgf;
}

void denoiseImplement(float * img, int w, int h, float blend, bool is_batch)
{	
	cout << "Width : " << w << ", ";
	cout << "Height : " << h << ", ";

	// Copy all image data to the gpu buffers
	memcpy(input_buffer->map(), img, sizeof(float) * 4 * w * h);
	input_buffer->unmap();

	// Execute denoise
	std::cout << "Denoising..." << std::endl;
	commandList->execute();
	std::cout << "Denoising complete" << std::endl;

	// Copy denoised image back to the cpu
	memcpy(img, output_buffer->map(), sizeof(float) * 4 * w * h);
	output_buffer->unmap();
}

void jobStart(int width, int height, float blend)
{
	// Create optix image buffers
	optix_context = optix::Context::create();
	input_buffer = optix_context->createBuffer(RT_BUFFER_INPUT, RT_FORMAT_FLOAT4, width, height);
	output_buffer = optix_context->createBuffer(RT_BUFFER_OUTPUT, RT_FORMAT_FLOAT4, width, height);

	// Setup the optix denoiser post processing stage
	denoiserStage = optix_context->createBuiltinPostProcessingStage("DLDenoiser");
	denoiserStage->declareVariable("input_buffer")->set(input_buffer);
	denoiserStage->declareVariable("output_buffer")->set(output_buffer);
	denoiserStage->declareVariable("blend")->setFloat(blend);

	// Add the denoiser to the new optix command list
	commandList = optix_context->createCommandList();
	//commandList->appendLaunch(0, width, height);
	commandList->appendPostprocessingStage(denoiserStage, width, height);
	commandList->finalize();
	// Compile context. I'm not sure if this is needed given there is no megakernal?
	optix_context->validate();
	optix_context->compile();
}

void jobComplete()
{
	denoiserStage->destroy();
	commandList->destroy();

	input_buffer->destroy();
	output_buffer->destroy();
	optix_context->destroy();
}
