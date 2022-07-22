#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
// #include <unistd.h>  // NOLINT(build/include_order)
#include <vector>
#include <math.h>
#include <string>

using namespace std;

#define LOG(x) std::cerr

std::vector<uint8_t> decode_bmp(const uint8_t* input, int row_size, int width, int height, int channels, bool top_down) {
    std::vector<uint8_t> output(height * width * channels);
    for (int i = 0; i < height; i++) {
        int src_pos;
        int dst_pos;

        for (int j = 0; j < width; j++) {
            if (!top_down) {
                src_pos = ((height - 1 - i) * row_size) + j * channels;
            } else {
                src_pos = i * row_size + j * channels;
            }

            dst_pos = (i * width + j) * channels;

            switch (channels) {
                case 1:
                    output[dst_pos] = input[src_pos];
                    break;
                case 3:
                    // BGR -> RGB
                    output[dst_pos] = input[src_pos + 2];
                    output[dst_pos + 1] = input[src_pos + 1];
                    output[dst_pos + 2] = input[src_pos];
                    // cout<< int(output[dst_pos]) << " " << int(output[dst_pos+1]) << " " << int(output[dst_pos+2]) << endl;
                    break;
                case 4:
                    // BGRA -> RGBA
                    output[dst_pos] = input[src_pos + 2];
                    output[dst_pos + 1] = input[src_pos + 1];
                    output[dst_pos + 2] = input[src_pos];
                    output[dst_pos + 3] = input[src_pos + 3];
                    break;
                default:
                    LOG(FATAL) << "Unexpected number of channels: " << channels;
                    break;
            }
        }
    }
    return output;
}

int BGR2Lab(int B, int G, int R)
{
    return 1;
}

std::vector<uint8_t> read_bmp(const std::string& input_bmp_name, int* width, int* height, int* channels)//
{
    int begin, end;

    std::ifstream file(input_bmp_name, std::ios::in | std::ios::binary);
    if (!file) {
        LOG(FATAL) << "input file " << input_bmp_name << " not found\n";
        exit(-1);
    }

    begin = file.tellg();
    file.seekg(0, std::ios::end);
    end = file.tellg();
    size_t len = end - begin;

    LOG(INFO) << "len: " << len << " begin:" << begin << " end:"<< end<< "\n";

    std::vector<uint8_t> img_bytes(len);
    file.seekg(0, std::ios::beg);
    file.read(reinterpret_cast<char*>(img_bytes.data()), len);
    const int32_t header_size = *(reinterpret_cast<const int32_t*>(img_bytes.data() + 10));
    cout << "img_bytes.data()" << header_size << endl;
    
    *width = *(reinterpret_cast<const int32_t*>(img_bytes.data() + 18));
    *height = *(reinterpret_cast<const int32_t*>(img_bytes.data() + 22));
    const int32_t bpp = *(reinterpret_cast<const int32_t*>(img_bytes.data() + 28));
    *channels = bpp / 8;

    LOG(INFO) <<"header size, bpp:" <<header_size << " "<< bpp <<" width, height, channels: " << *width << ", " << *height << ", " << *channels << "\n";

    // there may be padding bytes when the width is not a multiple of 4 bytes
    // 8 * channels == bits per pixel
    const int row_size = (8 * *channels * *width + 31) / 32 * 4;

    // if height is negative, data layout is top down
    // otherwise, it's bottom up
    bool top_down = (*height < 0);

    // Decode image, allocating tensor once the image size is known
    const uint8_t* bmp_pixels = &img_bytes[header_size];
    
    // for (int i = 0; i< 54; i++)
    // {cout << int(bmp_pixels[i]) << endl;}
    // enhance(bmp_pixels, row_size, *width, abs(*height), *channels, top_down);
    
    return decode_bmp(bmp_pixels, row_size, *width, abs(*height), *channels, top_down);
}

int main(){

    string input_bmp_name = "/home/flycapture/Desktop/XiaChuan/SummerXC-66/CImageProcessing/guangdong1dong_6.bmp";
    int image_width = 1280;
    int image_height = 1024;
    int image_channels = 3;

    vector<uint8_t> in = read_bmp(input_bmp_name, &image_width, &image_height, &image_channels); 

    cout << "in_size: " << in.size() << endl;
    return 0;
}
