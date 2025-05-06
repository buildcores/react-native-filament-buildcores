#include "RNFCameraWrapper.h"
#include "RNFCameraFovEnum.h"
#include "core/utils/RNFEntityWrapper.h"
#include <math/mat4.h>
#include <vector>

void margelo::CameraWrapper::loadHybridMethods() {
  registerHybridMethod("lookAtCameraManipulator", &CameraWrapper::lookAtCameraManipulator, this);
  registerHybridMethod("lookAt", &CameraWrapper::lookAt, this);
  registerHybridMethod("setLensProjection", &CameraWrapper::setLensProjection, this);
  registerHybridMethod("setProjection", &CameraWrapper::setProjection, this);
  registerHybridMethod("setModelMatrix", &CameraWrapper::setModelMatrix, this);
  registerHybridMethod("setCustomProjection", &CameraWrapper::setCustomProjection, this);
  registerHybridMethod("getModelMatrix", &CameraWrapper::getModelMatrix, this);
  registerHybridMethod("getEntity", &CameraWrapper::getEntity, this);
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

void margelo::CameraWrapper::setCustomProjection(std::vector<double> projectionMatrixData, double near, double far) {
  if (projectionMatrixData.size() != 16) {
    throw std::runtime_error("setCustomProjection: projectionMatrixData must contain 16 elements.");
  }
  filament::math::mat4 projectionMatrix(
      projectionMatrixData[0], projectionMatrixData[1], projectionMatrixData[2], projectionMatrixData[3],
      projectionMatrixData[4], projectionMatrixData[5], projectionMatrixData[6], projectionMatrixData[7],
      projectionMatrixData[8], projectionMatrixData[9], projectionMatrixData[10], projectionMatrixData[11],
      projectionMatrixData[12], projectionMatrixData[13], projectionMatrixData[14], projectionMatrixData[15]
  );
  pointee()->setCustomProjection(projectionMatrix, near, far);
}

std::vector<double> margelo::CameraWrapper::getModelMatrix() {
  filament::math::mat4 modelMatrix = pointee()->getModelMatrix();
  std::vector<double> matrixData(16);
  // Convert column-major mat4 to a flat vector (also column-major)
  // mat[col][row]
  matrixData[0] = modelMatrix[0][0]; matrixData[1] = modelMatrix[0][1]; matrixData[2] = modelMatrix[0][2]; matrixData[3] = modelMatrix[0][3]; // Col 0
  matrixData[4] = modelMatrix[1][0]; matrixData[5] = modelMatrix[1][1]; matrixData[6] = modelMatrix[1][2]; matrixData[7] = modelMatrix[1][3]; // Col 1
  matrixData[8] = modelMatrix[2][0]; matrixData[9] = modelMatrix[2][1]; matrixData[10] = modelMatrix[2][2]; matrixData[11] = modelMatrix[2][3]; // Col 2
  matrixData[12] = modelMatrix[3][0]; matrixData[13] = modelMatrix[3][1]; matrixData[14] = modelMatrix[3][2]; matrixData[15] = modelMatrix[3][3]; // Col 3
  return matrixData;
}

std::shared_ptr<EntityWrapper> margelo::CameraWrapper::getEntity() {
  utils::Entity entity = pointee()->getEntity();
  return std::make_shared<EntityWrapper>(entity);
}

