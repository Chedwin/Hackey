//*******************************//
//
// Name:			ImageManager.h
// Description:		A basic description of the header goes here.
//
// Author:			Edwin Chen
// Created:			Oct 22, 2016
// Last updated:	Oct 22, 2016
//
//*******************************//

#pragma once

#include "Macro.h"
#include "Image.h"
#include "ResourceManager.h"

#ifndef IMAGE_MANAGER_H
#define IMAGE_MANAGER_H

#define IMAGE_MANAGER ImageManager::GetImageManager()

class ImageManager
{
public:
	ImageManager();
	~ImageManager();

	static ImageManager* GetImageManager();

	ResourceHandle<Image> UploadImage(const STRING& _name, Image* _image);
	ResourceHandle<Image> UploadFile(const STRING& _filePath, const STRING& _name);

	void DeleteImage(const STRING& _name);
	void ClearAllImages();

	ResourceHandle<Image> GetImageHandle(const STRING& _name);
	Image* GetImage(ResourceHandle<Image>& _handle);
	Image* GetImage(const STRING& _name);

private:
	static UNIQUE_PTR(ImageManager) _imgManager;
	friend DEFAULT_DELETE(ImageManager);

protected:
	ResourceManager<Image> _imageResources;

};

#endif