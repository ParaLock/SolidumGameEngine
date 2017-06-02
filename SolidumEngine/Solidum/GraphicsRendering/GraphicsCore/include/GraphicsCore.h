#pragma once
#include "../../../sysInclude.h"
#include "../../Window/include/window.h"

#include "../../Directx11Rendering/dxDevice/include/dxDeviceManager.h"
#include "../../Directx11Rendering/dxDevice/include/dxDeviceAccessor.h"
#include "../../ActiveGraphicsAPI.h"
#include "../../Directx11Rendering/dxRenderTarget/include/dxRenderTarget.h"

#include "../../Lights/include/Light.h"

#include "../../../ResourceFramework/include/ResourceManagerPool.h"

#include "../../../EntityFramework/Entity/include/IEntity.h"

#include "../../../EventFramework/include/IEventListener.h"

#include "../../../EventFramework/include/EventFrameworkCore.h"

#include "../../RenderNodeTree/include/RenderNodeTree.h"

#include "../../GPUPipeline/include/GPUPipeline.h"

#include "../../Directx11Rendering/api_function_wrappers/include/dx11_pipeline_functions_wrapper.h"
#include "../../PipelineCommands/include/PipelineFunctions.h"

#include "../../PipelineCommands/include/PipelineCommand.h"

#include "../../RenderNode/include/RenderNodePool.h"
#include "../../GraphicsCommand/include/GraphicsCommandPool.h"

#include "../../Particles/include/ParticlePool.h"
#include "../../Particles/include/ParticleFactory.h"

#include "../../Renderers/include/LightRenderer.h"
#include "../../Renderers/include/GeometryDeferredRenderer.h"
#include "../../Renderers/include/ShadowMapRenderer.h"
#include "../../Renderers/include/SkyRenderer.h"
#include "../../Renderers/include/ParticleRenderer.h"

#include "../../RenderFlowGraph/include/RenderFlowGraph.h"

#include "../../../TaskFramework/include/TaskTree.h"

#include "IGraphicsCore.h"

class RenderNodeFactory;
class ParticlePool;
class BoundingSphere;

class GraphicsCore : public IEventListener, public IGraphicsCore
{
private:
	std::map<std::string, Renderer*> _registeredRenderers;

	dxDeviceManager *_dxManager = nullptr;
	ResourceManagerPool *_resManagerPool = nullptr;

	RenderNodeTree *_renderTree;

	TaskTree* _primaryTaskTree;

	GlobalRenderingParams _globalRenderingParameters;

	GPUPipeline* _endFrameState;

	std::map<DEFAULT_SHADER_TYPE, Shader*> _defaultShaders;

	std::vector<Renderer*> _sortedRenderers;

	RenderFlowGraph* _primaryFlowGraph;

	RenderNodeFactory* _renderNodeFactory;
	RenderNodePool* _renderNodePool;

	GraphicsCommandFactory* _graphicsCommandFactory;
	GraphicsCommandPool* _graphicsCommandPool;

	ParticleFactory* _particleFactory;
	ParticlePool* _particlePool;

public:
	GraphicsCore(SUPPORTED_GRAPHICS_API api, window *outputWindow, ResourceManagerPool* resManagerPool, TaskTree* masterTaskTree);
	~GraphicsCore();

	void beginFrame();

	void endFrame();

	void prepareRender(GraphicsCommandList* endscenePipeline, GraphicsCommandList* scenePipeline);

	void render(GraphicsCommandList* endscenePipeline, GraphicsCommandList* scenePipeline);

	void setCurrentRenderingCamera(CameraComponent* cam);

	void onEvent(EVENT_PTR evt);

	RenderNodeTree* getRenderNodeTree() { return _renderTree; };
	RenderNodePool* getRenderNodePool() { return _renderNodePool; };

	GraphicsCommandPool* getGraphicsCommandPool() { return _graphicsCommandPool; };
	GraphicsCommandFactory* getGraphicsCommandFactory() { return _graphicsCommandFactory; }

	TaskTree* getPrimaryTaskTree() { return _primaryTaskTree; };

	void registerRenderer(Renderer* newRenderer);
	void setPrimaryRenderFlowGraph(RenderFlowGraph* graph);

	void calculateRenderOrder();

	ParticlePool* getParticlePool() { return _particlePool; }

	void setWorldBoundingSphere(BoundingSphere* boundingSphere) { _globalRenderingParameters._worldBoundingSphere = boundingSphere; }

	GPUPipeline* getEndscenePSO() { return _endFrameState; }

	static GraphicsCore* singletonInstance;
	static GraphicsCore* getInstance();
};

