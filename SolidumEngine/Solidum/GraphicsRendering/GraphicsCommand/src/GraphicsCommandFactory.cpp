#include "../include/GraphicsCommandFactory.h"



GraphicsCommandFactory::GraphicsCommandFactory()
{
}


GraphicsCommandFactory::~GraphicsCommandFactory()
{
}

GraphicsCommand * GraphicsCommandFactory::createObject(GRAPHICS_COMMAND_TYPE type)
{
	GraphicsCommand* command;

	switch (type)
	{
	case GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_UNIFORM:
		command = new ShaderUpdateUniformCommand();
		break;
	case GRAPHICS_COMMAND_TYPE::SHADER_SYNC_UNIFORMS:
		command = new ShaderSyncUniforms();
		break;
	case GRAPHICS_COMMAND_TYPE::PIPELINE_BIND_SR:
		command = new PipelineSRBindCommand();
		break;
	case GRAPHICS_COMMAND_TYPE::PIPELINE_BIND_VERTEX_BUFFER:
		command = new PipelineBufferBindCommand();
		break;
	case GRAPHICS_COMMAND_TYPE::PIPELINE_BIND_INPUT_LAYOUT:
		command = new PipelineILBindCommand();
		break;
	case GRAPHICS_COMMAND_TYPE::PIPELINE_BIND_PRIMITIVE_TOPOLOGY:
		command = new PipelineSetPTCommand();
		break;
	case GRAPHICS_COMMAND_TYPE::PIPELINE_BIND_BLEND_STATE:
		command = new PipelineSetBlendStateCommand();
		break;
	case GRAPHICS_COMMAND_TYPE::PIPELINE_BIND_DEPTH_TEST_STATE:
		command = new PipelineSetDepthTestStateCommand();
		break;
	case GRAPHICS_COMMAND_TYPE::PIPELINE_BIND_RASTER_STATE:
		command = new PipelineSetRasterStateCommand();
		break;
	case GRAPHICS_COMMAND_TYPE::PIPELINE_BIND_VIEWPORT_STATE:
		command = new PipelineSetViewportCommand();
		break;
	case GRAPHICS_COMMAND_TYPE::PIPELINE_RENDER_TARGET_COMMAND:
		command = new PipelineRenderTargetCommand();
		break;
	case GRAPHICS_COMMAND_TYPE::PIPELINE_SWAPFRAME:
		command = new PipelineSwapFrame();
		break;
	case GRAPHICS_COMMAND_TYPE::PIPELINE_CLEAR_DEPTH_BUFFER:
		command = new PipelineClearDepthStencil();
		break;
	case GRAPHICS_COMMAND_TYPE::PIPELINE_BIND_SHADERS:
		command = new PipelineBindShaderCommand();
		break;
	case GRAPHICS_COMMAND_TYPE::PIPELINE_DRAW_INSTANCED:
		command = new PipelineDrawInstancedCommand();
		break;
	case GRAPHICS_COMMAND_TYPE::PIPELINE_DRAW_INDEXED:
		command = new PipelineDrawIndexedCommand();
		break;
	case GRAPHICS_COMMAND_TYPE::PIPELINE_RESET:
		command = new PipelineStateResetCommand();
		break;
	default:
		command = nullptr;
		break;
	}

	return command;
}
