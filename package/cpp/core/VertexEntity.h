//
// Created by Hanno Gödecke on 06.06.24.
//

#pragma once

#include <react_native_filament/filament/IndexBuffer.h>
#include <react_native_filament/filament/VertexBuffer.h>
#include <utils/Entity.h>

#include <memory>

struct VertexEntity {
  utils::Entity entity;
  std::shared_ptr<filament::VertexBuffer> vertexBuffer;
  std::shared_ptr<filament::IndexBuffer> indexBuffer;
};
