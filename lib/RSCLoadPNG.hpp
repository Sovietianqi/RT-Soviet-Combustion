/*
 * Project Name: [RT-Soviet-Combustion]
 * Copyright (C) [星空赤影，Sovietianqi & RT Studio]
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * Contact Information:
 * [星空赤影，Sovietianqi & RT Studio]
 * [https://github.com/Sovietianqi/RT-Soviet-Combustion]
 */
#include <png.h>
#include <vector>
#include <Drawing.h>
#include <Surface.h>
#include <GeneralDefinitions.h>

class PNG
{
protected:
		bool ForceLoadFile(const char* pFileName, int flag1, int flag2)
			{ JMP_THIS(0x6B9D00); }

public:

	static PNG * const Instance;

	static WORD DefaultTransparentColor;
   static bool LoadPNGFile(const char* pFileName, BSurface** ppSurface)
    {
        FILE *fp = fopen(pFileName, "rb");
        if (!fp)
            return false;

        png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        if (!png_ptr)
        {
            fclose(fp);
            return false;
        }

        png_infop info_ptr = png_create_info_struct(png_ptr);
        if (!info_ptr)
        {
            png_destroy_read_struct(&png_ptr, NULL, NULL);
            fclose(fp);
            return false;
        }

        if (setjmp(png_jmpbuf(png_ptr)))
        {
            png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
            fclose(fp);
            return false;
        }

        png_init_io(png_ptr, fp);
        png_read_info(png_ptr, info_ptr);

        // 获取图像的宽度和高度
        int width = png_get_image_width(png_ptr, info_ptr);
        int height = png_get_image_height(png_ptr, info_ptr);

        // 获取颜色类型
        int color_type = png_get_color_type(png_ptr, info_ptr);
        int bit_depth = png_get_bit_depth(png_ptr, info_ptr);

        // 分配内存来存储图像数据
        std::vector<png_byte> image_data(width * height * 4);

        // 读取图像数据
        png_read_image(png_ptr, reinterpret_cast<png_bytep>(image_data.data()));

        // 关闭文件和libpng结构
        fclose(fp);
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

        // 创建BSurface对象并填充图像数据
        *ppSurface = new BSurface(width, height, BSurface::Format::RGBA);
        if (*ppSurface)
        {
            // 将图像数据复制到BSurface对象中
            memcpy((*ppSurface)->GetBits(), image_data.data(), image_data.size());
            return true;
        }

        return false;
    }
	BSurface* GetSurface(const char* pFileName, BytePalette * pPalette = nullptr)
		{ JMP_THIS(0x6BA140); }

	bool BlitToSurface(RectangleStruct *BoundingRect, DSurface *TargetSurface, BSurface *PCXSurface, WORD TransparentColor = DefaultTransparentColor)
		{ JMP_THIS(0x6BA580); }

	void *Buffer;
};
