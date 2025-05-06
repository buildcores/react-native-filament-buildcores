#pragma once

#include "jsi/RNFPointerHolder.h"
#include "core/utils/RNFEntityWrapper.h"

#include "utils/RNFManipulatorWrapper.h"
#include <filament/Camera.h>
#include <vector>
#include <string>
#include <memory>

namespace margelo {
using namespace filament;

class CameraWrapper : public PointerHolder<Camera> {
public:
  explicit CameraWrapper(std::shared_ptr<Camera> camera) : PointerHolder("CameraWrapper", camera) {}

  void loadHybridMethods() override;

  // Getter
  std::vector<double> getModelMatrix();

private:
  void lookAt(std::vector<double> eye, std::vector<double> center, std::vector<double> up);
  void setLensProjection(double fov, double aspect, double near, double far);
  void setProjection(double fovInDegrees, double aspect, double near, double far, std::string directionStr);
  void setModelMatrix(std::vector<double> matrixData);
  void setCustomProjection(std::vector<double> projectionMatrixData, double near, double far);
  std::shared_ptr<EntityWrapper> getEntity();
  // Convenience methods
  void lookAtCameraManipulator(std::shared_ptr<ManipulatorWrapper> cameraManipulator);
};
} // namespace margelo
