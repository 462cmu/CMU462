#ifndef CMU462_SPECTRUM_H
#define CMU462_SPECTRUM_H

#include "color.h"
#include <string>

namespace CMU462 {

/**
 * Encodes irradiance by the intensity of each visible spectrum.
 * Note that this does not strictly an actual irradiance value but
 * it gives us enought information we can only sense a particular
 * part of the spectrum.
 */
class RGBSpectrum;             // forward declaration
typedef RGBSpectrum Spectrum;  ///< as we only care about the visible spectrum

class RGBSpectrum {
 public:
  double r;  ///< intensity of red spectrum
  double g;  ///< intensity of green spectrum
  double b;  ///< intensity of blue spectrum

  /**
   * Parameterized Constructor.
   * Initialize from component values.
   * \param r Intensity of the red spectrum
   * \param g Intensity of the green spectrum
   * \param b Intensity of the blue spectrum
   */
  RGBSpectrum(double r = 0, double g = 0, double b = 0) : r(r), g(g), b(b) {}

  /**
   * Constructor.
   * Initialize from an 8-bit RGB color represented as a uint8_t array.
   * \param arr Array containing component values.
   */
  RGBSpectrum(const uint8_t *arr);

  // operators //

  inline RGBSpectrum operator+(const RGBSpectrum &rhs) const {
    return RGBSpectrum(r + rhs.r, g + rhs.g, b + rhs.b);
  }

  inline RGBSpectrum &operator+=(const RGBSpectrum &rhs) {
    r += rhs.r;
    g += rhs.g;
    b += rhs.b;
    return *this;
  }

  inline RGBSpectrum operator*(const RGBSpectrum &rhs) const {
    return RGBSpectrum(r * rhs.r, g * rhs.g, b * rhs.b);
  }

  inline RGBSpectrum &operator*=(const RGBSpectrum &rhs) {
    r *= rhs.r;
    g *= rhs.g;
    b *= rhs.b;
    return *this;
  }

  inline RGBSpectrum operator*(double s) const {
    return RGBSpectrum(r * s, g * s, b * s);
  }

  inline RGBSpectrum &operator*=(double s) {
    r *= s;
    g *= s;
    b *= s;
    return *this;
  }

  inline bool operator==(const RGBSpectrum &rhs) const {
    return r == rhs.r && g == rhs.g && b == rhs.b;
  }

  inline bool operator!=(const RGBSpectrum &rhs) const {
    return !operator==(rhs);
  }

  inline Color toColor() const { return Color(r, g, b, 1); }

  static RGBSpectrum fromColor(const Color &c) {
    return RGBSpectrum(c.a * c.r, c.a * c.g, c.a * c.b);
  }

};  // class RGBSpectrum

// Commutable scalar multiplication
inline RGBSpectrum operator*(double s, const RGBSpectrum &c) { return c * s; }

// Prints components
std::ostream &operator<<(std::ostream &os, const RGBSpectrum &c);

}  // namespace CMU462

#endif  // CMU462_SPECTRUM_H
