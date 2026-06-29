#ifndef _RIVE_VGCANVAS_RENDERER_HPP_
#define _RIVE_VGCANVAS_RENDERER_HPP_

#include "base/bitmap.h"
#include "base/vgcanvas.h"
#include "base/vg_renderer.h"
#include "rive/factory.hpp"
#include "rive/renderer.hpp"
#include "utils/lite_rtti.hpp"
#include <vector>

namespace rive {

class VGCanvasRenderShader : public LITE_RTTI_OVERRIDE(RenderShader, VGCanvasRenderShader) {
 public:
  virtual void applyTo(vg_paint_t* paint) const = 0;
};

class VGCanvasRenderPath : public LITE_RTTI_OVERRIDE(RenderPath, VGCanvasRenderPath) {
 private:
  vg_path_t* m_Path;
  float m_lastX;
  float m_lastY;
  bool m_hasLast;

  void updateLastPoint(float x, float y) {
    m_lastX = x;
    m_lastY = y;
    m_hasLast = true;
  }

 public:
  VGCanvasRenderPath() : m_Path(NULL), m_lastX(0), m_lastY(0), m_hasLast(false) {
  }
  ~VGCanvasRenderPath() {
    this->rewind();
  }

  const vg_path_t* path() const {
    return m_Path;
  }
  void rewind() override;
  void addRenderPath(const RenderPath* path, const Mat2D& transform) override;
  void addRawPath(const RawPath& path) override;
  void fillRule(FillRule value) override;
  void moveTo(float x, float y) override;
  void lineTo(float x, float y) override;
  void cubicTo(float ox, float oy, float ix, float iy, float x, float y) override;
  void close() override;
};

class VGCanvasRenderPaint : public LITE_RTTI_OVERRIDE(RenderPaint, VGCanvasRenderPaint) {
 private:
  vg_paint_t* m_Paint;

  void clearGradient() {
    if (m_Paint != NULL && m_Paint->gradient != NULL) {
      vg_gradient_destroy(m_Paint->gradient);
      m_Paint->gradient = NULL;
    }
  }

 public:
  const vg_paint_t* paint() const {
    return m_Paint;
  }
  VGCanvasRenderPaint();
  ~VGCanvasRenderPaint();
  void style(RenderPaintStyle style) override;
  void color(ColorInt value) override;
  void thickness(float value) override;
  void join(StrokeJoin value) override;
  void cap(StrokeCap value) override;
  void blendMode(BlendMode value) override;
  void shader(rcp<RenderShader> sh) override;
  void invalidateStroke() override;
};

class VGCanvasRenderImage : public LITE_RTTI_OVERRIDE(RenderImage, VGCanvasRenderImage) {
 private:
  bitmap_t m_bitmap;

 public:
  explicit VGCanvasRenderImage(Span<const uint8_t> encoded);
  ~VGCanvasRenderImage() override;
  bitmap_t* bitmap() {
    return &m_bitmap;
  }
  const bitmap_t* bitmap() const {
    return &m_bitmap;
  }
};

class VGCanvasRenderer : public Renderer {
 private:
  vg_renderer_t* m_Renderer;
  std::vector<float> m_opacityStack;

 public:
  explicit VGCanvasRenderer(vg_renderer_t* renderer)
      : m_Renderer(renderer), m_opacityStack(1, 1.0f) {
  }
  void save() override;
  void restore() override;
  void transform(const Mat2D& transform) override;
  void modulateOpacity(float opacity) override;
  void drawPath(RenderPath* path, RenderPaint* paint) override;
  void clipPath(RenderPath* path) override;
  void drawImage(const RenderImage* image,
                 ImageSampler sampler,
                 BlendMode blendMode,
                 float opacity) override;
  void drawImageMesh(const RenderImage* image,
                     ImageSampler sampler,
                     rcp<RenderBuffer> vertices_f32,
                     rcp<RenderBuffer> uvCoords_f32,
                     rcp<RenderBuffer> indices_u16,
                     uint32_t vertexCount,
                     uint32_t indexCount,
                     BlendMode blendMode,
                     float opacity) override;
};

class VGCanvasFactory : public Factory {
 public:
  rcp<RenderBuffer> makeRenderBuffer(RenderBufferType type,
                                     RenderBufferFlags flags,
                                     size_t sizeInBytes) override;
  rcp<RenderShader> makeLinearGradient(float sx,
                                       float sy,
                                       float ex,
                                       float ey,
                                       const ColorInt colors[],
                                       const float stops[],
                                       size_t count) override;
  rcp<RenderShader> makeRadialGradient(float cx,
                                       float cy,
                                       float radius,
                                       const ColorInt colors[],
                                       const float stops[],
                                       size_t count) override;
  rcp<RenderPath> makeRenderPath(RawPath& rawPath, FillRule fillRule) override;
  rcp<RenderPath> makeEmptyRenderPath() override;
  rcp<RenderPaint> makeRenderPaint() override;
  rcp<RenderImage> decodeImage(Span<const uint8_t> encoded) override;
};

}  // namespace rive
#endif
