#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>

// clang-format off
#include "swephexp.h"
// clang-format on

namespace swephpp {

enum class HouseCuspFlag : int32_t { Tropical = 0, Sidereal, Radians };
enum class HouseSystem : int {
  Equal = 'A',
  Alcabitius,
  Campanus,
  EqualMC,
  Carter = 'F',
  // Gauquelin,
  Azimuth = 'H',
  Sunshine,
  SunshineAlt,
  Koch,
  PullenSDelta,
  Morinus,
  WholeSign,
  Porphyry,
  Placidus,
  PullenSRatio,
  Regiomontanus,
  Sripati,
  PolichPage,
  KrusinskiPisaGoelzer,
  EqualVehlow,
  EqualWholeSign,
  ARSMeridian,
  APC
};

typedef std::array<double, 13> HouseCusps;

typedef struct {
  double ac;
  double mc;
  double armc;
  double vertex;
  double equasc; /* equatorial ascendant */
  double coasc1; /* co-ascendant (W. Koch) */
  double coasc2; /* co-ascendant (M. Munkasey)*/
  double polasc; /* polar ascendant (M. Munkasey)*/
} Angles;

typedef struct {
  double jd_ut;
  HouseCuspFlag flag;
  double geolat;
  double geolon;
  HouseSystem hsys;
} HouseOptions;

typedef struct {
  double lon;
  double lat;
  double dist;
  double spdlon;
  double spdlat;
  double spddist;
} PlanetEphData;

enum PlanetaryBody {
  Sun,
  Mercury,
  Moon,
  Venus,
  Mars,
  Jupiter,
  Saturn,
  Uranus,
  Neptune,
  Chiron,
  Pluto,
  MeanNode,
  TrueNode
};

const std::string planetstr(PlanetaryBody body) {
  switch (body) {
  case Sun:
    return "Sun";
  case Mercury:
    return "Mercury";
  case Moon:
    return "Moon";
  case Venus:
    return "Venus";
  case Mars:
    return "Mars";
  case Jupiter:
    return "Jupiter";
  case Saturn:
    return "Saturn";
  case Uranus:
    return "Uranus";
  case Neptune:
    return "Neptune";
  case Chiron:
    return "Chiron";
  case Pluto:
    return "Pluto";
  default:
    return "UNKNOWN";
  }
}

enum class Flag : int32_t {
  JPLEph = 1,
  SwissEph = 2,
  MoshierEph = 4,
  Heliocentric = 8,
  TruePosition = 16,
  J2000 = 32,
  NoNutation = 64,
  Speed3 = 128,
  Speed = 256,
  NoGDeflection = 512,
  NoAberration = 1024,
  Astrometric = NoAberration | NoGDeflection,
  Equatorial = 2 * 1024,
  XYZ = 4 * 1024,
  Radians = 8 * 1024,
  Barycentric = 16 * 1024,
  Topocentric = 32 * 1024,
  OrbelAA = Topocentric,
  Sidereal = 64 * 1024,
  ICRS = 128 * 1024,
  DPSIDEPS1980 = 256 * 1024,
  JPLHorizons = DPSIDEPS1980,
  JPLHorizonsApprox = 512 * 1024
};

typedef struct {
  double jd_ut;
  int id;
  Flag flag;
} CalcOpts;

typedef struct {
  double jd_ut;
  HouseCuspFlag flag;
  double geolat;
  double geolon;
  HouseSystem hsys;
} HousesOpts;

int houses_ex(const HousesOpts &opts, HouseCusps &cusps, Angles &ascmc);

const std::string house_name(HouseSystem sys);

int calc(const CalcOpts &opts, PlanetEphData &data);

inline int houses_ex(const HousesOpts &opts, swephpp::HouseCusps &cusps,
                     Angles &ascmc) {
  return swe_houses_ex(opts.jd_ut, static_cast<int32_t>(opts.flag), opts.geolat,
                       opts.geolon, static_cast<char>(opts.hsys),
                       reinterpret_cast<double *>(&cusps),
                       reinterpret_cast<double *>(&ascmc));
}

inline const std::string house_name(HouseSystem sys) {
  return swe_house_name(static_cast<char>(sys));
}

inline int calc(const CalcOpts &opts, PlanetEphData &data) {
  return swe_calc_ut(opts.jd_ut, opts.id, static_cast<int32_t>(opts.flag),
                     reinterpret_cast<double *>(&data), 0);
}

} // namespace swephpp
