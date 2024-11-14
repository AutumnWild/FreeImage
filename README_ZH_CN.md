What is FreeImage ?
-----------------------------------------------------------------------------
FreeImage is an Open Source library project for developers who would like to support popular graphics image formats like PNG, BMP, JPEG, TIFF and others as needed by today's multimedia applications.
FreeImage is easy to use, fast, multithreading safe, and cross-platform (works with Windows, Linux and Mac OS X).

Thanks to it's ANSI C interface, FreeImage is usable in many languages including C, C++, VB, C#, Delphi, Java and also in common scripting languages such as Perl, Python, PHP, TCL, Lua or Ruby.

The library comes in two versions: a binary DLL distribution that can be linked against any WIN32/WIN64 C/C++ compiler and a source distribution.
Workspace files for Microsoft Visual Studio provided, as well as makefiles for Linux, Mac OS X and other systems.



## 1、Features

FreeImage 的英文版功能简介如下：

    Loading and Saving of as many bitmap types as possible
    Easy access to bitmap components,such as palette and data bits
    Converting bitmap’s bit depths from one to another
    Accessing pages in a bitmap when there are multiple.such as in TIFF
    basic manipulation of bitmaps,such as roation,flipping and resampling or point
    Alpha compositing and alpha blending

FreeImage 支持几乎所有图片格式的解析，解码，转码，图像处理，支持的图片格式包括 PNG，JPG，BMP，TGA，TIFF ... ；支持的图像处理操作包括 gamma校正，对比度，亮度，toneMapping，Alpha blending 等

FreeImage doesnot support:

    Advanced image processing operations such as convolution and transforms
    Bitmap drawing
    Vector graphics


## 2、Update

添加了cmake支持。



## 3、FreeImage API 

3.1 初始化API

    DLL_API void DLL_CALLCONV FreeImage_Initialise(BOOL load_local_plugins_only FI_DEFAULT(FALSE));
    DLL_API void DLL_CALLCONV FreeImage_DeInitialise(void);
     
    // Version routines ---------------------------------------------------------
     
    DLL_API const char *DLL_CALLCONV FreeImage_GetVersion(void);
    DLL_API const char *DLL_CALLCONV FreeImage_GetCopyrightMessage(void);

3.2 图像加载，保存相关API

FreeImage 不仅支持从文件中加载，可以直接从 File* 类型的handle 中加载图像

    DLL_API FIBITMAP *DLL_CALLCONV FreeImage_Allocate(int width, int height, int bpp, unsigned red_mask FI_DEFAULT(0), unsigned green_mask FI_DEFAULT(0), unsigned blue_mask FI_DEFAULT(0));
    DLL_API FIBITMAP *DLL_CALLCONV FreeImage_AllocateT(FREE_IMAGE_TYPE type, int width, int height, int bpp FI_DEFAULT(8), unsigned red_mask FI_DEFAULT(0), unsigned green_mask FI_DEFAULT(0), unsigned blue_mask FI_DEFAULT(0));
    DLL_API FIBITMAP * DLL_CALLCONV FreeImage_Clone(FIBITMAP *dib);
    DLL_API void DLL_CALLCONV FreeImage_Unload(FIBITMAP *dib);
    DLL_API FIBITMAP *DLL_CALLCONV FreeImage_Load(FREE_IMAGE_FORMAT fif, const char *filename, int flags FI_DEFAULT(0));
    DLL_API FIBITMAP *DLL_CALLCONV FreeImage_LoadU(FREE_IMAGE_FORMAT fif, const wchar_t *filename, int flags FI_DEFAULT(0));
    DLL_API FIBITMAP *DLL_CALLCONV FreeImage_LoadFromHandle(FREE_IMAGE_FORMAT fif, FreeImageIO *io, fi_handle handle, int flags FI_DEFAULT(0));
    DLL_API BOOL DLL_CALLCONV FreeImage_Save(FREE_IMAGE_FORMAT fif, FIBITMAP *dib, const char *filename, int flags FI_DEFAULT(0));

3.3 获取图像信息相关API

FreeImage 提供了丰富的 API 获取图像的所有信息

```c++
void testFreeImagebitmapinfo(int argc, char **argv) {
	FreeImage_Initialise(FALSE);
	FIBITMAP *allocatelib = NULL;
 
	allocatelib = FreeImage_Load(FIF_JPEG, "freeimage.jpg", JPEG_DEFAULT);
 
	printf("FreeImage get image type: %d \n", FreeImage_GetImageType(allocatelib));
 
	printf("FreeImage get color used: %d \n", FreeImage_GetColorsUsed(allocatelib));
 
	printf("FreeImage get BPP : %d \n", FreeImage_GetBPP(allocatelib));
 
	printf("FreeImage get Width : %d \n", FreeImage_GetWidth(allocatelib));
	printf("FreeImage get Height : %d \n", FreeImage_GetHeight(allocatelib));
 
	printf("FreeImage get Line : %d \n", FreeImage_GetLine(allocatelib));
	printf("FreeImage get Pitch : %d \n", FreeImage_GetPitch(allocatelib));
 
	printf("FreeImage get DIBSize : %d \n", FreeImage_GetDIBSize(allocatelib));
	printf("FreeImage get MemorySize : %d \n", FreeImage_GetMemorySize(allocatelib));
	RGBQUAD *palette = NULL;
    printf("FreeImage get Palette : %d \n", (((palette = FreeImage_GetPalette(allocatelib)) == NULL)? TRUE : FALSE));
 
	// dpx
	printf("FreeImage get GetDotsPerMeterX : %d \n", FreeImage_GetDotsPerMeterX(allocatelib));
	// dpy
	printf("FreeImage get GetDotsPerMeterY : %d \n", FreeImage_GetDotsPerMeterY(allocatelib));
 
	FreeImage_SetDotsPerMeterX(allocatelib, 1000);
	FreeImage_SetDotsPerMeterY(allocatelib, 1000);
 
	CHECKBOOL(FreeImage_Save(FIF_PNG, allocatelib, "freeimage.png", PNG_DEFAULT));
```


​     
```c++
	BITMAPINFOHEADER *bitmapHeader = FreeImage_GetInfoHeader(allocatelib);
	if (bitmapHeader) {
		printf("FreeImage GetInfoHeader success!! \n");
	}
 
	BITMAPINFO *bitmapInfo = FreeImage_GetInfo(allocatelib);
	if (bitmapHeader) {
		printf("FreeImage GetInfoHeader success!! \n");
	}
	//  2 FIC_RGB
	printf("FreeImage get colortype:%d \n", FreeImage_GetColorType(allocatelib));
 
	//  RedMask:ff0000 GreenMask:ff00 BlueMask:ff
	printf("FreeImage get RedMask:%x GreenMask:%x BlueMask:%x \n", FreeImage_GetRedMask(allocatelib), \
		FreeImage_GetGreenMask(allocatelib), FreeImage_GetBlueMask(allocatelib));
 
	printf("FreeImage Has Pixels %d \n", FreeImage_HasPixels(allocatelib));
```


​     
```c
	FIBITMAP *thumbnail = FreeImage_GetThumbnail(allocatelib);
	if (!thumbnail) {
		printf("get thumbnail failed!! \n");
	}
```

3.4 获取像素地址API

通过 FreeImage_GetBits 和 FreeImage_GetScanLine 可以获取图像首地址和每一行的内存地址，为编辑每一个像素的内容提供了可能，结合自己的绘制代码，间接实现绘制图像的功能。

    void testFreeImagePixelAccess(int argc, char **argv) {
    	FreeImage_Initialise(FALSE);
    	FIBITMAP *allocatelib = NULL;
    	allocatelib = FreeImage_Allocate(1280, 720, 32);
    	CHECKNULL(allocatelib);
     
    	BYTE* ptr = FreeImage_GetBits(allocatelib);
    	
    	printf("FreeImage get BPP : %d \n", FreeImage_GetBPP(allocatelib));
    	printf("FreeImage get Width : %d \n", FreeImage_GetWidth(allocatelib));
    	printf("FreeImage get Height : %d \n", FreeImage_GetHeight(allocatelib));
     
    	for(unsigned int y = 0; y < FreeImage_GetHeight(allocatelib); y++) {
    		BYTE* ptr = FreeImage_GetScanLine(allocatelib, y);
    		for (unsigned int x = 0; x < FreeImage_GetWidth(allocatelib); x++) {
    			ptr[FI_RGBA_RED] = 0;
    			ptr[FI_RGBA_GREEN] = 255;
    			ptr[FI_RGBA_BLUE] = 0;
    			ptr[FI_RGBA_ALPHA] = 255;
    			ptr += FreeImage_GetBPP(allocatelib)/8;
    		}
    	}
     
    	RGBQUAD pixelColor;
    	FreeImage_GetPixelColor(allocatelib, 100, 100, &pixelColor);
    	printf("FreeImage get Pixel color: R:%d G:%d B:%d \n", pixelColor.rgbRed, pixelColor.rgbGreen, pixelColor.rgbBlue);
     
    	int start_x = 100;
    	int start_y = 100;
    	int rect_w = 200;
    	int rect_h = 200;
     
    	pixelColor.rgbRed = 255;
    	pixelColor.rgbGreen = 0;
    	pixelColor.rgbBlue = 0;
     
    	for (int y = start_y; y < (rect_h + start_y); y++) {
    		for (int x = start_x; x < (rect_w + start_x); x++) {
    			FreeImage_SetPixelColor(allocatelib, x, y, &pixelColor);
    		}
    	}
     
    	CHECKBOOL(FreeImage_Save(FIF_BMP, allocatelib, "allocate.bmp", BMP_DEFAULT));
     
    EXIT:
    	if (allocatelib) {
    		FreeImage_Unload(allocatelib);
    	}
     
    	FreeImage_DeInitialise();
    }

3.5 图像格式转换API 

通过 FreeImage_ConvertTo4Bits FreeImage_ConvertTo8Bits 可以实现图像在各个不同颜色通道和颜色色深之间转换，注意使用 FreeImage_ConvertTo4Bits 实际是转换为使用 palette 格式的图片，4Bits 对应的是 16 个颜色，图像中存储是是这16种颜色的索引值

    void testFreeImageConversion(int argc, char **argv) {
    	FreeImage_Initialise(FALSE);
    	FIBITMAP *allocatelib = NULL;
    	allocatelib = FreeImage_Load(FIF_JPEG, "freeimage.jpg", JPEG_DEFAULT);
    	CHECKNULL(allocatelib);
     
    	// 4 bits and 8 bits using palette
    	//FIBITMAP* outputlib = FreeImage_ConvertTo8Bits(allocatelib);
    	FIBITMAP* outputlib = FreeImage_ConvertTo4Bits(allocatelib);
    	printf("FreeImage get BPP : %d \n", FreeImage_GetBPP(outputlib));
    	printf("FreeImage get Width : %d \n", FreeImage_GetWidth(outputlib));
    	printf("FreeImage get Height : %d \n", FreeImage_GetHeight(outputlib));
    	//printf("FreeImage get Palette : %d \n", FreeImage_GetPalette(allocatelib));
     
    	const BITMAPINFOHEADER *bitmapHeader = FreeImage_GetInfoHeader(outputlib);
    	if (bitmapHeader) {
    		printf("color used %d  color important %d\n", bitmapHeader->biClrUsed, bitmapHeader->biClrImportant);
     
    		const RGBQUAD* palette = FreeImage_GetPalette(outputlib);
    		for (int i = 0; i < (bitmapHeader->biClrUsed); i++) {
    			printf("%d %d %d \n", palette[i].rgbRed, palette[i].rgbGreen, palette[i].rgbBlue);
    		}
    	}
     
    	CHECKBOOL(FreeImage_Save(FIF_BMP, outputlib, "outputlib_4Bits.bmp", BMP_DEFAULT));
     
    EXIT:
    	if (allocatelib) {
    		FreeImage_Unload(allocatelib);
    	}
     
    	FreeImage_DeInitialise();
    }

3.6 图像处理相关API

包含对图像的 旋转，Gamma，对比度调节等处理，使用 FreeImage_Paste 还可以实现图像的 alpha blend 效果

    	FreeImage_Initialise(FALSE);
    	FIBITMAP *allocatelib = NULL;
    	FIBITMAP *output_lib = NULL;
    	FIBITMAP *srclib = NULL;
    	allocatelib = FreeImage_Load(FIF_JPEG, "freeimage.jpg", JPEG_DEFAULT);
    	CHECKNULL(allocatelib);
     
    	output_lib = FreeImage_Rotate(allocatelib, 90.0);
    	//CHECKBOOL(FreeImage_Save(FIF_BMP, output_lib, "rotate.bmp", BMP_DEFAULT));
     
    	double x_orig = FreeImage_GetWidth(allocatelib) / 2.0;
    	double y_orig = FreeImage_GetHeight(allocatelib) / 2.0;
    	output_lib = FreeImage_RotateEx(allocatelib, 45.0, 0.0, 0.0, x_orig, y_orig, TRUE);
    	//CHECKBOOL(FreeImage_Save(FIF_BMP, output_lib, "rotate.bmp", BMP_DEFAULT));
     
    	//  alpha blend demo
    	srclib = FreeImage_Load(FIF_JPEG, "tony_logo.jpg", JPEG_DEFAULT);
     
    	FreeImage_Paste(allocatelib, srclib, (int)x_orig, (int)y_orig, 100);
    	CHECKBOOL(FreeImage_Save(FIF_BMP, allocatelib, "blend.bmp", BMP_DEFAULT));


## 4、Usage

FreeImage 支持 VisualStudio，Linux，Cygwin，MacoS 等平台，在 windows下开发可以直接下载编译好的 动态链接库文件，在VisualStudio 中设置对应的头文件和库文件的路径 







