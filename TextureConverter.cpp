#include <DirectXMath.h>
#include <Windows.h>
using namespace DirectX;
#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")
#include <cassert>
#include <d3d12.h>
#include <dxgi1_6.h>
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#include <vector>

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#include <string>


#include<cstdio>
#include<DirectXTex.h>
#include<cstdlib>
#include "TextureConverter.h"
HRESULT result;

void TextureConverter::ConvertTextureWICToDDS(const std::string& filePath)
{
	LoadWICTextureFromFile(filePath);
	SaveDDSTextureToFile();
}

void TextureConverter::LoadWICTextureFromFile(const std::string& filepath)
{
	std::wstring wfilePath = ConvertMultiByteStringToWideString(filepath);
	result = LoadFromWICFile(wfilePath.c_str(), WIC_FLAGS_NONE, &metadata_, scratchImage_);
	assert(SUCCEEDED(result));
	SeparateFilePath(wfilePath);
}

std::wstring TextureConverter::ConvertMultiByteStringToWideString(const std::string& mString)
{

	int filePathBufferSize = MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, nullptr, 0);

	std::wstring wString;
	wString.resize(filePathBufferSize);

	MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, &wString[0], filePathBufferSize);

	return wString;
}

void TextureConverter::SeparateFilePath(const std::wstring& filePath)
{
	size_t pos1;
	std::wstring exceptExt;

	pos1 = filePath.rfind('.');

	if (pos1 != std::wstring::npos)
	{
		fileExt_ = filePath.substr(pos1 + 1, filePath.size() - pos1 - 1);
		exceptExt = filePath.substr(0, pos1);
	}
	else
	{
		fileExt_ = L"";
		exceptExt = filePath;
	}
	pos1 = exceptExt.rfind('\\');
	if (pos1 != std::wstring::npos)
	{
		directoryPath_ = exceptExt.substr(0, pos1 + 1);
		fileName_ = exceptExt.substr(pos1 + 1, exceptExt.size() - pos1 - 1);
		return;
	}
	pos1 = exceptExt.rfind('/');

	if (pos1 != std::wstring::npos)
	{
		directoryPath_ = exceptExt.substr(0, pos1 + 1);
		fileName_ = exceptExt.substr(pos1 + 1, exceptExt.size() - pos1 - 1);
		return;
	}
	directoryPath_ = L"";
	fileName_ = exceptExt;
}

void TextureConverter::SaveDDSTextureToFile()
{
	metadata_.format = MakeSRGB(metadata_.format);
	HRESULT result;

	std::wstring filePath = directoryPath_ + fileName_ + L".dds";

	result = SaveToDDSFile(scratchImage_.GetImages(), scratchImage_.GetImageCount(),
		metadata_, DDS_FLAGS_NONE, filePath.c_str());
	assert(SUCCEEDED(result));
}
