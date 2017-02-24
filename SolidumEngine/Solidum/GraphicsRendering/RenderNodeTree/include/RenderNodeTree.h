#pragma once
#include "../../RenderNode/include/RenderNode.h"

#include "../../Shaders/include/IShader.h"

#include "IRenderNodeTree.h"

class RenderNodeTree : public IRenderNodeTree
{
private:
	std::map<uint64_t, RenderNode*>* _nodeQueryMap;
	std::map<IShader*, RenderNode*>* _rootNodes;

	std::list<RenderNode*>* _orderedRootNodes;
public:
	RenderNodeTree();
	~RenderNodeTree();

	uint64_t getUniqueNodeID();

	void setExecutionOrder(const std::list<SHADER_RENDER_TYPE>& order);

	void addNode(RenderNode* node, uint64_t id);

	void updateGlobalRenderParams(GlobalRenderingParams params);
	void updateNodeLocalRenderParams(LocalRenderingParams params, uint64_t nodeid);

	void updateNodeVisibility(bool isVisible, uint64_t nodeid);

	void removeNode(uint64_t id);

	void frustrumCull();

	void optimize();

	void walkTree();
};

