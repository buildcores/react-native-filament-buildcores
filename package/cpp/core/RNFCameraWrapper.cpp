#include "RNFCameraWrapper.h"
#include "RNFCameraFovEnum.h"
#include <math/mat4.h>
#include <vector>

void margelo::CameraWrapper::loadHybridMethods() {
  registerHybridMethod("lookAtCameraManipulator", &CameraWrapper::lookAtCameraManipulator, this);
  registerHybridMethod("lookAt", &CameraWrapper::lookAt, this);
  registerHybridMethod("setLensProjection", &CameraWrapper::setLensProjection, this);
  registerHybridMethod("setProjection", &CameraWrapper::setProjection, this);
  registerHybridMethod("setModelMatrix", &CameraWrapper::setModelMatrix, this);
}

void margelo::CameraWrapper::lookAtCameraManipulator(std::shared_ptr<ManipulatorWrapper> cameraManipulator) {
  if (!cameraManipulator) {
    throw std::invalid_argument("CameraManipulator is null");
  }

  math::float3 eye, center, up;
  cameraManipulator->getManipulator()->getLookAt(&eye, &center, &up);
  pointee()->lookAt(eye, center, up);
}

void margelo::CameraWrapper::lookAt(std::vector<double> eye, std::vector<double> center, std::vector<double> up) {
  math::float3 eyeVec = {static_cast<float>(eye[0]), static_cast<float>(eye[1]), static_cast<float>(eye[2])};
  math::float3 centerVec = {static_cast<float>(center[0]), static_cast<float>(center[1]), static_cast<float>(center[2])};
  math::float3 upVec = {static_cast<float>(up[0]), static_cast<float>(up[1]), static_cast<float>(up[2])};
  pointee()->lookAt(eyeVec, centerVec, upVec);
}

void margelo::CameraWrapper::setLensProjection(double fov, double aspect, double near, double far) {
  pointee()->setLensProjection(static_cast<float>(fov), static_cast<float>(aspect), static_cast<float>(near), static_cast<float>(far));
}

void margelo::CameraWrapper::setProjection(double fovInDegrees, double aspect, double near, double far,
                                           std::string directionStr = "vertical") {
  Camera::Fov direction;
  EnumMapper::convertJSUnionToEnum(directionStr, &direction);

  pointee()->setProjection(static_cast<float>(fovInDegrees), static_cast<float>(aspect), static_cast<float>(near), static_cast<float>(far),
                           direction);
}

void margelo::CameraWrapper::setModelMatrix(std::vector<double> matrixData) {
  if (matrixData.size() != 16) {
    throw std::runtime_error("setModelMatrix: matrixData must contain 16 elements.");
  }
  filament::math::mat4 modelMatrix(
      matrixData[0], matrixData[1], matrixData[2], matrixData[3],   // Col 0
      matrixData[4], matrixData[5], matrixData[6], matrixData[7],   // Col 1
      matrixData[8], matrixData[9], matrixData[10], matrixData[11], // Col 2
      matrixData[12], matrixData[13], matrixData[14], matrixData[15] // Col 3
  );
  pointee()->setModelMatrix(modelMatrix);
}
