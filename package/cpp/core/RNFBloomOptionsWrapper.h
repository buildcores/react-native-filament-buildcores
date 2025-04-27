#pragma once

#include "RNFQualityLevel.h"
#include "jsi/RNFEnumMapper.h"
#include "jsi/RNFHybridObject.h"
#include <filament/Options.h>
#include <string>
#include <stdexcept>

namespace margelo {

using namespace filament;

class BloomOptionsWrapper : public HybridObject, public BloomOptions {
public:
  explicit BloomOptionsWrapper() : HybridObject("BloomOptions") {}
  explicit BloomOptionsWrapper(const BloomOptions& options) : HybridObject("BloomOptions"), BloomOptions(options) {}

  void loadHybridMethods() {
    registerHybridGetter("enabled", &BloomOptionsWrapper::getEnabled, this);
    registerHybridSetter("enabled", &BloomOptionsWrapper::setEnabled, this);
    registerHybridGetter("levels", &BloomOptionsWrapper::getLevels, this);
    registerHybridSetter("levels", &BloomOptionsWrapper::setLevels, this);
    registerHybridGetter("resolution", &BloomOptionsWrapper::getResolution, this);
    registerHybridSetter("resolution", &BloomOptionsWrapper::setResolution, this);
    registerHybridGetter("strength", &BloomOptionsWrapper::getStrength, this);
    registerHybridSetter("strength", &BloomOptionsWrapper::setStrength, this);
    registerHybridGetter("blendMode", &BloomOptionsWrapper::getBlendMode, this);
    registerHybridSetter("blendMode", &BloomOptionsWrapper::setBlendMode, this);
    registerHybridGetter("threshold", &BloomOptionsWrapper::getThreshold, this);
    registerHybridSetter("threshold", &BloomOptionsWrapper::setThreshold, this);
    registerHybridGetter("highlight", &BloomOptionsWrapper::getHighlight, this);
    registerHybridSetter("highlight", &BloomOptionsWrapper::setHighlight, this);
    registerHybridGetter("quality", &BloomOptionsWrapper::getQuality, this);
    registerHybridSetter("quality", &BloomOptionsWrapper::setQuality, this);
    registerHybridGetter("lensFlare", &BloomOptionsWrapper::getLensFlare, this);
    registerHybridSetter("lensFlare", &BloomOptionsWrapper::setLensFlare, this);
    registerHybridGetter("starburst", &BloomOptionsWrapper::getStarburst, this);
    registerHybridSetter("starburst", &BloomOptionsWrapper::setStarburst, this);
    registerHybridGetter("chromaticAberration", &BloomOptionsWrapper::getChromaticAberration, this);
    registerHybridSetter("chromaticAberration", &BloomOptionsWrapper::setChromaticAberration, this);
    registerHybridGetter("ghostCount", &BloomOptionsWrapper::getGhostCount, this);
    registerHybridSetter("ghostCount", &BloomOptionsWrapper::setGhostCount, this);
    registerHybridGetter("ghostSpacing", &BloomOptionsWrapper::getGhostSpacing, this);
    registerHybridSetter("ghostSpacing", &BloomOptionsWrapper::setGhostSpacing, this);
    registerHybridGetter("ghostThreshold", &BloomOptionsWrapper::getGhostThreshold, this);
    registerHybridSetter("ghostThreshold", &BloomOptionsWrapper::setGhostThreshold, this);
    registerHybridGetter("haloThickness", &BloomOptionsWrapper::getHaloThickness, this);
    registerHybridSetter("haloThickness", &BloomOptionsWrapper::setHaloThickness, this);
    registerHybridGetter("haloRadius", &BloomOptionsWrapper::getHaloRadius, this);
    registerHybridSetter("haloRadius", &BloomOptionsWrapper::setHaloRadius, this);
    registerHybridGetter("haloThreshold", &BloomOptionsWrapper::getHaloThreshold, this);
    registerHybridSetter("haloThreshold", &BloomOptionsWrapper::setHaloThreshold, this);
    // Dirt properties are not implemented yet
  }

private:
  // Helper for invalid union string
  static std::runtime_error invalidUnion(const std::string& passedUnion) {
    return std::runtime_error("Cannot convert JS Value to Enum: Invalid Union value passed! (\"" + passedUnion + "\")");
  }
  // Helper for invalid enum value
  template <typename T> static std::runtime_error invalidEnum(T passedEnum) {
    return std::runtime_error("Cannot convert Enum to JS Value: Invalid Enum passed! (Value #" + std::to_string(static_cast<int>(passedEnum)) + ")");
  }

  // BlendMode specific conversion functions
  static filament::BloomOptions::BlendMode blendModeFromString(const std::string& inUnion) {
      if (inUnion == "ADD") {
          return filament::BloomOptions::BlendMode::ADD;
      } else if (inUnion == "INTERPOLATE") {
          return filament::BloomOptions::BlendMode::INTERPOLATE;
      } else {
          throw invalidUnion(inUnion);
      }
  }
  static std::string blendModeToString(filament::BloomOptions::BlendMode inEnum) {
      switch (inEnum) {
          case filament::BloomOptions::BlendMode::ADD:
              return "ADD";
          case filament::BloomOptions::BlendMode::INTERPOLATE:
              return "INTERPOLATE";
          default:
              throw invalidEnum(inEnum);
      }
  }

  // Enabled
  bool getEnabled() { return enabled; }
  void setEnabled(bool value) { enabled = value; }

  // Levels
  int getLevels() { return levels; }
  void setLevels(int value) { levels = value; }

  // Resolution
  int getResolution() { return resolution; }
  void setResolution(int value) { resolution = value; }

  // Strength
  float getStrength() { return strength; }
  void setStrength(float value) { strength = value; }

  // Blend Mode - Use local conversion
  std::string getBlendMode() {
    return blendModeToString(blendMode);
  }
  void setBlendMode(std::string value) {
    this->blendMode = blendModeFromString(value);
  }

  // Threshold
  bool getThreshold() { return threshold; }
  void setThreshold(bool value) { threshold = value; }

  // Highlight
  float getHighlight() { return highlight; }
  void setHighlight(float value) { highlight = value; }

  // Quality - Still uses global EnumMapper
  std::string getQuality() {
    std::string qualityStr;
    EnumMapper::convertEnumToJSUnion(quality, &qualityStr);
    return qualityStr;
  }
  void setQuality(std::string value) {
    EnumMapper::convertJSUnionToEnum(value, &this->quality);
  }

  // Lens Flare
  bool getLensFlare() { return lensFlare; }
  void setLensFlare(bool value) { lensFlare = value; }

  // Starburst
  bool getStarburst() { return starburst; }
  void setStarburst(bool value) { starburst = value; }

  // Chromatic Aberration
  float getChromaticAberration() { return chromaticAberration; }
  void setChromaticAberration(float value) { chromaticAberration = value; }

  // Ghost Count
  int getGhostCount() { return ghostCount; }
  void setGhostCount(int value) { ghostCount = value; }

  // Ghost Spacing
  float getGhostSpacing() { return ghostSpacing; }
  void setGhostSpacing(float value) { ghostSpacing = value; }

  // Ghost Threshold
  float getGhostThreshold() { return ghostThreshold; }
  void setGhostThreshold(float value) { ghostThreshold = value; }

  // Halo Thickness
  float getHaloThickness() { return haloThickness; }
  void setHaloThickness(float value) { haloThickness = value; }

  // Halo Radius
  float getHaloRadius() { return haloRadius; }
  void setHaloRadius(float value) { haloRadius = value; }

  // Halo Threshold
  float getHaloThreshold() { return haloThreshold; }
  void setHaloThreshold(float value) { haloThreshold = value; }
};

} // namespace margelo 