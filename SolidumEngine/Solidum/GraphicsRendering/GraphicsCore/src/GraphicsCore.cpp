#include "../include/GraphicsCore.h"

GraphicsCore::GraphicsCore(SUPPORTED_GRAPHICS_API api, window *outputWindow, ResourceManagerPool* resManagerPool)
{
	ActiveGraphicsAPI::setCurrentAPI(api);

	EventFrameworkCore::getInstance()->getGlobalEventHub("ComponentEventHub")->subscribeListener(this);

	_primaryCamera = new camera(0.1f, 1000.0f);
	_resManagerPool = resManagerPool;

	if (api == SUPPORTED_GRAPHICS_API::DIRECTX11) {

		_dxManager = new dxDeviceManager();

		dxConfigBlock dxConfig;

		dxConfig.swapchain.Height = outputWindow->screen_height;
		dxConfig.swapchain.Width = outputWindow->screen_width;
		dxConfig.swapchain.OutputWindow = outputWindow->hWnd;

		_dxManager->dxCreateDev(&dxConfig);

		dxDeviceAccessor::initAccessor(_dxManager);

		RenderTarget* frameBufferRT = new dxRenderTarget(
			dxDeviceAccessor::dxEncapsulator->getFrameBufferRenderTarget(),
			dxDeviceAccessor::dxEncapsulator->getFrameBufferTexture());

		resManagerPool->getResourceManager("RenderTargetManager")->addResource(frameBufferRT, "framebuffer");

		RenderTarget* depthBufferRT = new dxRenderTarget(
			dxDeviceAccessor::dxEncapsulator->getDepthBufferShaderView(),
			dxDeviceAccessor::dxEncapsulator->getDepthBufferTexture());

		resManagerPool->getResourceManager("RenderTargetManager")->addResource(frameBufferRT, "depth_buffer");
	}
}


GraphicsCore::~GraphicsCore()
{
	if (_dxManager != nullptr)
		delete _dxManager;
}

void GraphicsCore::RenderAll()
{
	std::map<std::string, IResource*> *allActiveRenderProcesses = _resManagerPool->
		getResourceManager("RenderProcessManager")->getResourceMap();

	std::list<RenderProcess*> deferredProcesses;

	for (auto itr = allActiveRenderProcesses->begin(); itr != allActiveRenderProcesses->end(); itr++) {

		if (itr->second->getLoadStatus()) {

			RenderProcess* rendProc = itr->second->getCore<RenderProcess>();

			std::list<RenderDataStream*>* streams = rendProc->getRegisteredStreams();

			for (auto streamItr = streams->begin(); streamItr != streams->end(); streamItr++) {

				RenderDataStream* stream = *streamItr;

				stream->writeNext((IResource*)_primaryCamera, STREAM_DATA_TYPE::CAMERA);
			}

			if (rendProc->getDeferredFlag()) {

				deferredProcesses.push_back(rendProc); continue;
			}	

			rendProc->execute();
		}
	}

	for (auto defProcItr = deferredProcesses.begin(); defProcItr != deferredProcesses.end(); defProcItr++) {
		RenderProcess* defRendProc = *defProcItr;

		defRendProc->execute();
	}
}

void GraphicsCore::onEvent(EVENT_PTR evt)
{
	RenderEvent* renderEvt;
	RenderProcess *rendProc;

	switch (evt.get()->getType())
	{
		case EVENT_TYPE::RENDER_EVENT_REGISTER_STREAM:
			renderEvt = evt->getEvent<RenderEvent>();

			rendProc = _resManagerPool->getResourceManager("RenderProcessManager")->
				getResource(renderEvt->getRendProcID())->getCore<RenderProcess>();

			rendProc->registerDataStream(renderEvt->getStream());

			break;
	default:
		break;
	}
}

void GraphicsCore::attachPrimaryCamera(camera* cam)
{
	_primaryCamera = cam;
}
