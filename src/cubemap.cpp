#include <nanogui/cubemap.h>
#include <stb_image.h>
#include <memory>

NAMESPACE_BEGIN(nanogui)

CubeMap::CubeMap(Texture::PixelFormat pixel_format,
                     Texture::ComponentFormat component_format,
                     const Vector2i &size,
                     Texture::InterpolationMode min_interpolation_mode,
                     Texture::InterpolationMode mag_interpolation_mode,
                     Texture::WrapMode wrap_mode)
    : m_pixel_format(pixel_format),
      m_component_format(component_format),
      m_min_interpolation_mode(min_interpolation_mode),
      m_mag_interpolation_mode(mag_interpolation_mode),
      m_wrap_mode(wrap_mode),
      m_size(size) {

    init();
}

size_t CubeMap::bytes_per_pixel() const {
    size_t result = 0;
    switch (m_component_format) {
        case Texture::ComponentFormat::UInt8:   result = 1; break;
        case Texture::ComponentFormat::Int8:    result = 1; break;
        case Texture::ComponentFormat::UInt16:  result = 2; break;
        case Texture::ComponentFormat::Int16:   result = 2; break;
        case Texture::ComponentFormat::UInt32:  result = 4; break;
        case Texture::ComponentFormat::Int32:   result = 4; break;
        case Texture::ComponentFormat::Float16: result = 2; break;
        case Texture::ComponentFormat::Float32: result = 4; break;
        default: throw std::runtime_error("Texture::bytes_per_pixel(): "
                                          "invalid component format!");
    }

    return result * channels();
}

size_t CubeMap::channels() const {
    size_t result = 1;
    switch (m_pixel_format) {
        case Texture::PixelFormat::R:            result = 1;  break;
        case Texture::PixelFormat::RA:           result = 2;  break;
        case Texture::PixelFormat::RGB:          result = 3;  break;
        case Texture::PixelFormat::RGBA:         result = 4;  break;
        case Texture::PixelFormat::BGR:          result = 3;  break;
        case Texture::PixelFormat::BGRA:         result = 4;  break;
        case Texture::PixelFormat::Depth:        result = 1;  break;
        case Texture::PixelFormat::DepthStencil: result = 2;  break;
        default: throw std::runtime_error("Texture::channels(): invalid "
                                          "pixel format!");
    }
    return result;
}

NAMESPACE_END(nanogui)
