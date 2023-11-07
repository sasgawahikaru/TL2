#pragma once
#include <DirectXMath.h>

class TextureConverter
{
public:
	void ConvertTextureWICToDDS(const std::string& filePath);
private:
	void LoadWICTextureFromFile(const std::string& filepath);
private:
	static std::wstring ConvertMultiByteStringToWideString(const std::string& mString);
private:

	DirectX::TexMetadata metadata_;

};
