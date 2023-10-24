#pragma once

class TextureConverter
{
public:
	void ConvertTextureWICToDDS(const std::string& filePath);
private:
	void LoadWICTextureFromFile(const std::string& filepath);
private:
	static std::wstring ConvertMultiByteStringToWideString(const std::string& mString);

	DirectX::TexMetadata metadata_;
	DirectX::ScratchImage scratchImage_;

	void SeparateFilePath(const std::wstring& filePath);

	void SaveDDSTextureToFile();

private:
	std::wstring directoryPath_;
	std::wstring fileName_;
	std::wstring fileExt_;
};
