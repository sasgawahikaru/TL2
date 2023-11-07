//#include <DirectXMath.h>
//#include <Windows.h>
//using namespace DirectX;
//#include <d3dcompiler.h>
//#pragma comment(lib, "d3dcompiler.lib")
//#include <cassert>
//#include <d3d12.h>
//#include <dxgi1_6.h>
//#pragma comment(lib, "d3d12.lib")
//#pragma comment(lib, "dxgi.lib")
//#include <vector>
//
//#define DIRECTINPUT_VERSION 0x0800
//#include <dinput.h>
//
//#pragma comment(lib, "dinput8.lib")
//#pragma comment(lib, "dxguid.lib")
#include <string>


#include<cstdio>
#include<DirectXTex.h>
#include<cstdlib>
#include "TextureConverter.h"


enum Argument
{
	kApplicationPath,
	kFilePath,

	NumArgument
};
int main(int argc, char* argv[])
{
	assert(argc >= NumArgument);

	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	assert(SUCCEEDED(hr));

	TextureConverter converter;

	converter.ConvertTextureWICToDDS(argv[kFilePath]);

	CoUninitialize();

	system("pause");
	return 0;
}