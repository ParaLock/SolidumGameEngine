#include "../include/TextureManager.h"



TextureManager::TextureManager()
{
}


TextureManager::~TextureManager()
{
}

IResource* TextureManager::createResource(IResourceBuilder * builder, std::string name)
{
	IResource* newResource = nullptr;

	switch (ActiveGraphicsAPI::getCurrentAPI()) {
	case SUPPORTED_GRAPHICS_API::DIRECTX11:
		newResource = new dxTexture(builder);
		break;
	}

	if (newResource != nullptr) {
		_activeResources->insert({ name, newResource });

		return newResource;
	}

	return nullptr;
}