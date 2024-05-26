## TGAImage  
构造函数有
``` CPP
TGAImage()
TGAImage(width,height,bytesperpixel)
TGAImage::TGAImage(const TGAImage &img)  
TGAImage::~TGAImage()  
TGAImage & TGAImage::operator =(const TGAImage &img)
```

```cpp
boolTGAImage::read_tga_file()
```
检测异常包括  
- 是否成功打开文件
- 是否读取文件头
- 长宽是否大于零与每像素大小是否正确
- 图像类型
  - 0：没有图像数据 
  - 1：未压缩的颜色表图像 
  - 2：未压缩的真彩图像 
  - 3：未压缩的黑白图像 
  - 9：RLE压缩的颜色表图像 
  - 10：RLE压缩的真彩图像 
  - 11：RLE压缩的黑白图像
    - 是否读取压缩编码图像  

`
bool TGAImage::write_tga_file(const char *filename, bool rle)
`  检测是否成功写入

`TGAColor TGAImage::get(int x, int y)`返回所在位置颜色，不符合条件返回空

`bool TGAImage::set(int x, int y, TGAColor c)`写入位置颜色  
`TGAImage::get_bytespp()`  获得每像素大小  
`TGAImage::get_width()` 获得宽度  
`TGAImage::get_height()` 获得高度  
`bool TGAImage::flip_horizontally()`水平反转  
`bool TGAImage::flip_vertically() `垂直反转  
`unsigned char *TGAImage::buffer() `  返回data
`void TGAImage::clear()`  清空  
`bool TGAImage::scale(int w, int h)`缩放  