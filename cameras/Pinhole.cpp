/*
 * pinhole.cpp
 * Andrew Frost
 * 2020
 *
 */

#include "pinhole.h"

///////////////////////////////////////////////////////////////////////////
// Pinhole                                                               //
///////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------
//
//
Ray Pinhole::getRay(float u, float v) const
{
    return Ray(m_origin, m_lowerLeftCorner + u * m_horizontal + v * m_vertical - m_origin);
}

//-------------------------------------------------------------------------
//
//
void Pinhole::printCamera()
{
    std::cout << "Pinhole Camera"<< std::endl;
    std::cout << "origin     : " << vecToString(m_origin) << std::endl;
}




