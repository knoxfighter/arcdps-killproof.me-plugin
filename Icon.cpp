#include "Icon.h"

#include <string>
#include <wincodec.h>

#include "global.h"

Icon::Icon(UINT name) {
	std::string nameString(std::to_string(name));
	
	HRSRC imageResHandle = FindResource(self_dll, MAKEINTRESOURCE(name), L"PNG");
	if (!imageResHandle) {
		// not found
		std::string text = "Error finding Resource: ";
		text.append(nameString);
		throw std::runtime_error(text);
	}

	// does not need to be freed
	HGLOBAL imageResDataHandle = LoadResource(self_dll, imageResHandle);
	if (!imageResDataHandle) {
		// loading failed
		std::string text = "Error loading resource: ";
		text.append(nameString);
		throw std::runtime_error(text);
	}

	LPVOID imageFile = LockResource(imageResDataHandle);
	if (!imageFile) {
		// locking failed
		std::string text = "Error locking resource: ";
		text.append(nameString);
		throw std::runtime_error(text);
	}

	DWORD imageFileSize = SizeofResource(self_dll, imageResHandle);
	if (!imageFileSize) {
		// error getting size of file
		std::string text = "Error getting Size of Resource: ";
		text.append(nameString);
		throw std::runtime_error(text);
	}

	IWICImagingFactory* m_pIWICFactory = NULL;
	HRESULT createInstance = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pIWICFactory));
	if (!SUCCEEDED(createInstance)) {
		// error creating instance
		std::string text = "Error creating WIC intance: ";
		text.append(nameString);
		text.append(" - ");
		text.append(std::to_string(createInstance));
		throw std::runtime_error(text);
	}

	IWICStream* pIWICStream = NULL;
	HRESULT streamRes = m_pIWICFactory->CreateStream(&pIWICStream);
	if (!SUCCEEDED(streamRes)) {
		// creating stream failed
		std::string text = "Error creating WIC stream: ";
		text.append(nameString);
		text.append(" - ");
		text.append(std::to_string(streamRes));
		throw std::runtime_error(text);
	}

	HRESULT initializeFromMemoryRes = pIWICStream->InitializeFromMemory(reinterpret_cast<BYTE*>(imageFile), imageFileSize);
	if (!SUCCEEDED(initializeFromMemoryRes)) {
		// error initializing from memory
		std::string text = "Error initializing WICStream from memory: ";
		text.append(nameString);
		text.append(" - ");
		text.append(std::to_string(initializeFromMemoryRes));
		throw std::runtime_error(text);
	}

	IWICBitmapDecoder* pIDecoder = NULL;
	HRESULT decoderFromStreamRes = m_pIWICFactory->CreateDecoderFromStream(pIWICStream, NULL, WICDecodeMetadataCacheOnLoad, &pIDecoder);
	if (!SUCCEEDED(decoderFromStreamRes)) {
		// error creating decode from stream
		std::string text = "Error creating decoder from stream: ";
		text.append(nameString);
		text.append(" - ");
		text.append(std::to_string(decoderFromStreamRes));
		throw std::runtime_error(text);
	}

	IWICBitmapFrameDecode* pIDecodeFrame = NULL;
	HRESULT getFrameRes = pIDecoder->GetFrame(0, &pIDecodeFrame);
	if (!SUCCEEDED(getFrameRes)) {
		// error getting frame from decoder
		std::string text = "Error getting frame 0: ";
		text.append(nameString);
		text.append(" - ");
		text.append(std::to_string(getFrameRes));
		throw std::runtime_error(text);
	}

	WICPixelFormatGUID pixelFormat;
	HRESULT pixelFormatRes = pIDecodeFrame->GetPixelFormat(&pixelFormat);
	if (!SUCCEEDED(pixelFormatRes)) {
		// error getting pixel format
		std::string text = "Error getting pixel format: ";
		text.append(nameString);
		text.append(" - ");
		text.append(std::to_string(pixelFormatRes));
		return;
	}

	IWICComponentInfo* pIComponentInfo = NULL;
	HRESULT componentInfoRes = m_pIWICFactory->CreateComponentInfo(pixelFormat, &pIComponentInfo);
	if (!SUCCEEDED(componentInfoRes)) {
		// error creating component info
		std::string text = "Error creating component info: ";
		text.append(nameString);
		text.append(" - ");
		text.append(std::to_string(componentInfoRes));
		return;
	}

	IWICPixelFormatInfo* pIPixelFormatInfo;
	HRESULT pixelFormatInfoRes = pIComponentInfo->QueryInterface(__uuidof(IWICPixelFormatInfo), reinterpret_cast<void**>(&pIPixelFormatInfo));
	if (!SUCCEEDED(pixelFormatInfoRes)) {
		// error querying pixel format info
		std::string text = "Error querying format info: ";
		text.append(nameString);
		text.append(" - ");
		text.append(std::to_string(pixelFormatInfoRes));
		return;
	}

	UINT bitsPerPixel;
	HRESULT bitsPerPixelRes = pIPixelFormatInfo->GetBitsPerPixel(&bitsPerPixel);
	if (!SUCCEEDED(bitsPerPixelRes)) {
		// error getting bits per pixel
		std::string text = "Error getting bits per pixel: ";
		text.append(nameString);
		text.append(" - ");
		text.append(std::to_string(bitsPerPixelRes));
		return;
	}

	pIDecodeFrame->GetSize(&width, &height);
	HRESULT createTextureRes = d3d9Device->CreateTexture(width, height, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &texture, NULL);
	if (!SUCCEEDED(createTextureRes)) {
		// error creating d3d9 texture
		std::string text = "Error creating d3d9 texture: ";
		text.append(nameString);
		text.append(" - ");
		text.append(std::to_string(createTextureRes));
		return;
	}

	float totalPixels = bitsPerPixel * width + 7; // +7 forces to next byte if needed
	UINT stride = totalPixels / 8;

	byte* pixelBuffer = new byte[1048576]; // 1MB size
	HRESULT copyPixelsRes = pIDecodeFrame->CopyPixels(NULL, stride, 1048576, pixelBuffer);
	if (!SUCCEEDED(copyPixelsRes)) {
		// error copying pixels to buffer
		std::string text = "Error copying pixels: ";
		text.append(nameString);
		text.append(" - ");
		text.append(std::to_string(copyPixelsRes));
		return;
	}

	D3DLOCKED_RECT rect;
	texture->LockRect(0, &rect, 0, D3DLOCK_DISCARD);
	unsigned char* dest = static_cast<unsigned char*>(rect.pBits);
	memcpy(dest, pixelBuffer, sizeof(char) * width * height * 4);
	texture->UnlockRect(0);

	// cleanup
	delete[] pixelBuffer;
	m_pIWICFactory->Release();
	pIWICStream->Release();
	pIDecoder->Release();
	pIDecodeFrame->Release();
	pIComponentInfo->Release();
	pIPixelFormatInfo->Release();
}

Icon::~Icon() {
	texture->Release();
}
