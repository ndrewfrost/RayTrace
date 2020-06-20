/*
 * display.h
 * Andrew Frost
 * 2020
 *
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "../common/glm_common.h"
#include "../common/math.h"

#include <memory>
#include <thread>
#include <chrono>

///////////////////////////////////////////////////////////////////////////
// RGB                                                                   //
///////////////////////////////////////////////////////////////////////////

struct RGB
{
    RGB() : r(0), g(0), b(0) {}

    RGB(float v) {
        r = static_cast<uint8_t>(v * 255);
        g = static_cast<uint8_t>(v * 255);
        b = static_cast<uint8_t>(v * 255);
    }

    RGB(float rr, float gg, float bb)
    {
        r = static_cast<uint8_t>(rr * 255);
        g = static_cast<uint8_t>(gg * 255);
        b = static_cast<uint8_t>(bb * 255);
    }

    void reassign(glm::vec3 & color)
    {
        r = static_cast<uint8_t>(color.x * 255);
        g = static_cast<uint8_t>(color.y * 255);
        b = static_cast<uint8_t>(color.z * 255);
    }
    uint8_t r, g, b;
};

///////////////////////////////////////////////////////////////////////////
// DisplayImage                                                          //
///////////////////////////////////////////////////////////////////////////

class DisplayImage
{
public:
    DisplayImage() : m_width(0), m_height(0), m_pixels(nullptr), m_samples(1) {}

    DisplayImage(const unsigned int width, 
                 const unsigned int height, 
                 const unsigned int nSamples = 1)
        : m_width(width), m_height(height), m_samples(nSamples)
    {
        m_pixels = std::unique_ptr<RGB[]>(new RGB[m_width * m_height]);
        for (unsigned int i = 0; i < m_width * m_height; ++i)
            m_pixels[i] = RGB(0,0,100);
    }

    ~DisplayImage() = default;

    void fillBuffer(uint32_t* buffer)
    {    
       for (unsigned int y = 0; y < m_height; ++y) {
            for (unsigned int x = 0; x < m_width; ++x) {
                unsigned int index = y * m_height + x;
                buffer[index] = (m_pixels[index].r << 16)
                              + (m_pixels[index].g << 8)
                              + (m_pixels[index].b);
            }
       }
    }

    void setPixel(unsigned int x, unsigned int y, glm::vec3 & color)
    {
        // divide color by number of samples
        // gamma correct for gamma = 2.0
        float scale = 1.0f / m_samples;

        color.x = std::sqrt(scale * color.x);
        color.y = std::sqrt(scale * color.y);
        color.z = std::sqrt(scale * color.z);

        color.x = clamp(color.x, 0.f, 1.f);
        color.y = clamp(color.y, 0.f, 1.f);
        color.z = clamp(color.z, 0.f, 1.f);

        unsigned int index = (m_height - y - 1) * m_height +s x;
        m_pixels[index].reassign(color);
    }

    unsigned int getWidth() const { return m_width; }
    
    unsigned int getHeight() const { return m_height; }

    unsigned int getNumberSamples() const { return m_samples; }

private:
    unsigned int m_width, m_height, m_samples;
    std::unique_ptr<RGB[]> m_pixels;
};


#endif // !DISPLAY_H_