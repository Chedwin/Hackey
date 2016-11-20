//*******************************//
//
// Name:			TextureManager.h
// Description:		Global static manager containing all the textures (images) cached in memory.
//
// Author:			Edwin Chen
// Created:			Oct 22, 2016
// Last updated:	Nov 17, 2016
//
//*******************************//

#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "Macro.h"
#include "Texture.h"
#include "ResourceManager.h"

#define TEXTURE_MANAGER TextureManager::GetTextureManager()

class TextureManager {
protected:
	TextureManager();
	~TextureManager();
public:
	static TextureManager* GetTextureManager();

	// Create a texture then store it
	ResourceHandle<Texture> UploadTexture(const STRING& _name, Texture* _Texture);

	// Upload directly from file that creates and stores a texture for you
	ResourceHandle<Texture> UploadTextureFromFile(const STRING& _filePath, const STRING& _name);

	void DeleteTexture(const STRING& _name);
	void ClearAllTextures();

	ResourceHandle<Texture> GetTextureHandle(const STRING& _name);
	Texture* GetTexture(ResourceHandle<Texture>& _handle);
	Texture* GetTexture(const STRING& _name);

private:
	static UNIQUE_PTR(TextureManager) _textureManager;
	friend DEFAULT_DELETE(TextureManager);

protected:
	ResourceManager<Texture> _textureResources;

};

#endif