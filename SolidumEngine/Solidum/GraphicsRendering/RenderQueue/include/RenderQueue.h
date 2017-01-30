#pragma once
#include "../../../sysInclude.h"
#include "../../../EntityFramework/Entity/include/Entity.h"

#include "../../RenderOP/include/RenderOP.h"

typedef std::list<RenderOP*> RENDER_QUEUE;

class RenderQueue
{
private:
	RENDER_QUEUE *_queuedLights;
	RENDER_QUEUE *_queuedModels;
public:
	RenderQueue();
	~RenderQueue();

	void queueRenderOP(RenderOP* renderOP);
	void dequeueRenderOP(RenderOP* renderOP);

	RENDER_QUEUE getRenderQueue();
};
