/*
 * display.h
 * Andrew Frost
 * 2020
 *
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <memory>
#include <thread>
#include <chrono>

///////////////////////////////////////////////////////////////////////////
// DisplayImage                                                          //
///////////////////////////////////////////////////////////////////////////

class DisplayImage
{
public:

    struct RGB
    {
        RGB() : r(0.0f), g(0.0f), b(0.0f) {}
        RGB(float v) : r(v), g(v), b(v) {}
        RGB(float rr, float gg, float bb) : r(rr), g(gg), b(bb) {}

        float r, g, b;
    };

    DisplayImage() : m_width(0), m_height(0), m_pixels(nullptr) {}

    DisplayImage(const unsigned int width, const unsigned int height)
        : m_width(width), m_height(height)
    {
        m_pixels = std::unique_ptr<RGB[]>(new RGB[m_width * m_height]);
        for (unsigned int i = 0; i < m_width * m_height; ++i)
            m_pixels[i] = 0.5f;
    }

    ~DisplayImage() = default;

public:
    unsigned int m_width, m_height;
    std::unique_ptr<RGB[]> m_pixels;
};

#endif // !DISPLAY_H_