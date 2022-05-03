/*
    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/

/**
 * \file nanogui/cubemap.h
 *
 * \brief Defines an abstraction for cubemaps that works with
 * OpenGL.
 */

#pragma once

#include <iostream>

#include <nanogui/object.h>
#include <nanogui/vector.h>
#include <nanogui/traits.h>
#include <nanogui/texture.h>

NAMESPACE_BEGIN(nanogui)

class NANOGUI_EXPORT CubeMap : public Object {
public:
    /**
     * \brief Allocate memory for a cubemap with the given configuration
     *
     * \note
     *   Certain combinations of pixel and component formats may not be
     *   natively supported by the hardware. In this case, \ref init() chooses
     *   a similar supported configuration that can subsequently be queried
     *   using \ref pixel_format() and \ref component_format().
     *   Some caution must be exercised in this case, since \ref upload() will
     *   need to provide the data in a different storage format.
     */
    CubeMap(Texture::PixelFormat pixel_format,
            Texture::ComponentFormat component_format,
            const Vector2i &size,
            Texture::InterpolationMode min_interpolation_mode = Texture::InterpolationMode::Bilinear,
            Texture::InterpolationMode mag_interpolation_mode = Texture::InterpolationMode::Bilinear,
            Texture::WrapMode wrap_mode = Texture::WrapMode::ClampToEdge);

    /// Return the pixel format
    Texture::PixelFormat pixel_format() const { return m_pixel_format; }

    /// Return the component format
    Texture::ComponentFormat component_format() const { return m_component_format; }

    /// Return the interpolation mode for minimization
    Texture::InterpolationMode min_interpolation_mode() const { return m_min_interpolation_mode; }

    /// Return the interpolation mode for minimization
    Texture::InterpolationMode mag_interpolation_mode() const { return m_mag_interpolation_mode; }

    /// Return the wrap mode
    Texture::WrapMode wrap_mode() const { return m_wrap_mode; }

    /// Return the size of this texture
    const Vector2i &size() const { return m_size; }

    /// Return the number of bytes consumed per pixel of this texture
    size_t bytes_per_pixel() const;

    /// Return the number of channels of this texture
    size_t channels() const;

    /// Upload packed pixel data from the CPU to the GPU
    void upload(const uint8_t *data);

    /// Download packed pixel data from the GPU to the CPU
    void download(uint8_t *data);

    /// Resize the texture (discards the current contents)
    void resize(const Vector2i &size);

#if defined(NANOGUI_USE_OPENGL) || defined(NANOGUI_USE_GLES)
    uint32_t texture_handle() const { return m_texture_handle; }
#elif defined(NANOGUI_USE_METAL)
    void *texture_handle() const { return m_texture_handle; }
#endif

protected:
    /// Initialize the texture handle
    void init();

    /// Release all resources
    virtual ~CubeMap();

protected:
    Texture::PixelFormat m_pixel_format;
    Texture::ComponentFormat m_component_format;
    Texture::InterpolationMode m_min_interpolation_mode;
    Texture::InterpolationMode m_mag_interpolation_mode;
    Texture::WrapMode m_wrap_mode;
    Vector2i m_size;

    #if defined(NANOGUI_USE_OPENGL) || defined(NANOGUI_USE_GLES)
        uint32_t m_texture_handle = 0;
    #elif defined(NANOGUI_USE_METAL)
        void *m_texture_handle = nullptr;
    #endif
};

NAMESPACE_END(nanogui)
