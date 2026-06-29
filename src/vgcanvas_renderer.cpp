#include "vgcanvas_renderer.hpp"

#include "image_loader/image_loader_stb.h"
#include "rive/math/raw_path.hpp"
#include "rive/math/vec2d.hpp"
#include "rive/shapes/paint/color.hpp"
#include "utils/factory_utils.hpp"

using namespace rive;

namespace {

class VGCanvasLinearGradientShader : public VGCanvasRenderShader {
 private:
  float m_sx;
  float m_sy;
  float m_ex;
  float m_ey;
  std::vector<ColorInt> m_colors;
  std::vector<float> m_stops;

 public:
  VGCanvasLinearGradientShader(float sx,
                               float sy,
                               float ex,
                               float ey,
                               const ColorInt colors[],
                               const float stops[],
                               size_t count)
      : m_sx(sx), m_sy(sy), m_ex(ex), m_ey(ey), m_colors(colors, colors + count) {
    if (stops != NULL) {
      m_stops.assign(stops, stops + count);
    } else {
      m_stops.resize(count);
      for (size_t i = 0; i < count; i++) {
        m_stops[i] = (float)i / (float)(count - 1);
      }
    }
  }

  void applyTo(vg_paint_t* paint) const override {
    vg_paint_set_linear_gradient(paint, m_sx, m_sy, m_ex, m_ey);
    for (size_t i = 0; i < m_colors.size(); i++) {
      ColorInt value = m_colors[i];
      color_t c =
          color_init(colorRed(value), colorGreen(value), colorBlue(value), colorAlpha(value));
      vg_paint_add_gradient_stop(paint, c, m_stops[i]);
    }
  }
};

class VGCanvasRadialGradientShader : public VGCanvasRenderShader {
 private:
  float m_cx;
  float m_cy;
  float m_ex;
  float m_ey;
  std::vector<ColorInt> m_colors;
  std::vector<float> m_stops;

 public:
  VGCanvasRadialGradientShader(float cx,
                               float cy,
                               float radius,
                               const ColorInt colors[],
                               const float stops[],
                               size_t count)
      : m_cx(cx), m_cy(cy), m_ex(cx + radius), m_ey(cy), m_colors(colors, colors + count) {
    (void)radius;
    if (stops != NULL) {
      m_stops.assign(stops, stops + count);
    } else {
      m_stops.resize(count);
      for (size_t i = 0; i < count; i++) {
        m_stops[i] = (float)i / (float)(count - 1);
      }
    }
  }

  void applyTo(vg_paint_t* paint) const override {
    vg_paint_set_radial_gradient(paint, m_cx, m_cy, m_ex, m_ey);
    for (size_t i = 0; i < m_colors.size(); i++) {
      ColorInt value = m_colors[i];
      color_t c =
          color_init(colorRed(value), colorGreen(value), colorBlue(value), colorAlpha(value));
      vg_paint_add_gradient_stop(paint, c, m_stops[i]);
    }
  }
};

static Mat2D basis_matrix(Vec2D p0, Vec2D p1, Vec2D p2) {
  auto e0 = p1 - p0;
  auto e1 = p2 - p0;
  return Mat2D(e0.x, e0.y, e1.x, e1.y, p0.x, p0.y);
}

}  // namespace

void VGCanvasRenderPath::fillRule(FillRule value) {
  (void)value;
}

void VGCanvasRenderPath::rewind() {
  vg_path_destroy(m_Path);
  m_Path = NULL;
  m_hasLast = false;
}

void VGCanvasRenderPath::addRenderPath(const RenderPath* path, const Mat2D& t) {
  auto vgPath = lite_rtti_cast<const VGCanvasRenderPath*>(path);
  if (vgPath == NULL) {
    return;
  }
  const vg_path_t* src = vgPath->path();
  if (src != NULL) {
    matrix_t m;
    vg_path_t* iter = vg_path_dup(src, TRUE);

    matrix_set(&m, t[0], t[1], t[2], t[3], t[4], t[5]);
    vg_path_transform(iter, &m);
    m_Path = vg_path_append(m_Path, iter);
  }
}

void VGCanvasRenderPath::addRawPath(const RawPath& path) {
  for (auto [verb, pts] : path) {
    switch (verb) {
      case PathVerb::move:
        moveTo(pts[0].x, pts[0].y);
        break;
      case PathVerb::line:
        lineTo(pts[1].x, pts[1].y);
        break;
      case PathVerb::quad: {
        float qx = pts[0].x;
        float qy = pts[0].y;
        float ex = pts[1].x;
        float ey = pts[1].y;
        float sx = m_hasLast ? m_lastX : qx;
        float sy = m_hasLast ? m_lastY : qy;
        float c1x = sx + 2.f / 3.f * (qx - sx);
        float c1y = sy + 2.f / 3.f * (qy - sy);
        float c2x = ex + 2.f / 3.f * (qx - ex);
        float c2y = ey + 2.f / 3.f * (qy - ey);
        cubicTo(c1x, c1y, c2x, c2y, ex, ey);
        break;
      }
      case PathVerb::cubic:
        cubicTo(pts[1].x, pts[1].y, pts[2].x, pts[2].y, pts[3].x, pts[3].y);
        break;
      case PathVerb::close:
        close();
        break;
    }
  }
}

void VGCanvasRenderPath::moveTo(float x, float y) {
  m_Path = vg_path_add_move_to(m_Path, x, y);
  updateLastPoint(x, y);
}

void VGCanvasRenderPath::lineTo(float x, float y) {
  m_Path = vg_path_add_line_to(m_Path, x, y);
  updateLastPoint(x, y);
}

void VGCanvasRenderPath::cubicTo(float ox, float oy, float ix, float iy, float x, float y) {
  m_Path = vg_path_add_cubic_to(m_Path, ox, oy, ix, iy, x, y);
  updateLastPoint(x, y);
}

void VGCanvasRenderPath::close() {
  m_Path = vg_path_add_close(m_Path);
}

VGCanvasRenderPaint::VGCanvasRenderPaint() {
  m_Paint = vg_paint_create();
}

VGCanvasRenderPaint::~VGCanvasRenderPaint() {
  vg_paint_destroy(m_Paint);
  m_Paint = NULL;
}

void VGCanvasRenderPaint::style(RenderPaintStyle style) {
  switch (style) {
    case RenderPaintStyle::fill:
      vg_paint_set_type(m_Paint, VG_PAINT_FILL);
      break;
    case RenderPaintStyle::stroke:
      vg_paint_set_type(m_Paint, VG_PAINT_STROKE);
      break;
  }
}

void VGCanvasRenderPaint::color(ColorInt value) {
  clearGradient();
  color_t c = color_init(colorRed(value), colorGreen(value), colorBlue(value), colorAlpha(value));
  vg_paint_set_color(m_Paint, c);
}

void VGCanvasRenderPaint::thickness(float value) {
  vg_paint_set_line_width(m_Paint, value);
}

void VGCanvasRenderPaint::join(StrokeJoin value) {
  switch (value) {
    case StrokeJoin::miter:
      vg_paint_set_join_type(m_Paint, VG_JOIN_MITTER);
      break;
    case StrokeJoin::bevel:
      vg_paint_set_join_type(m_Paint, VG_JOIN_BEVEL);
      break;
    case StrokeJoin::round:
      vg_paint_set_join_type(m_Paint, VG_JOIN_ROUND);
      break;
    default:
      break;
  }
}

void VGCanvasRenderPaint::cap(StrokeCap value) {
  switch (value) {
    case StrokeCap::butt:
      vg_paint_set_cap_type(m_Paint, VG_CAP_BUTT);
      break;
    case StrokeCap::square:
      vg_paint_set_cap_type(m_Paint, VG_CAP_SQUARE);
      break;
    case StrokeCap::round:
      vg_paint_set_cap_type(m_Paint, VG_CAP_ROUND);
      break;
    default:
      break;
  }
}

void VGCanvasRenderPaint::shader(rcp<RenderShader> sh) {
  auto vgShader = lite_rtti_rcp_cast<VGCanvasRenderShader>(std::move(sh));
  if (vgShader != NULL) {
    vgShader->applyTo(m_Paint);
  }
}

void VGCanvasRenderPaint::invalidateStroke() {
}

void VGCanvasRenderPaint::blendMode(BlendMode value) {
  if (value != rive::BlendMode::srcOver) {
    log_debug("not supported blendMode: %u\n", (unsigned int)value);
  }
}

VGCanvasRenderImage::VGCanvasRenderImage(Span<const uint8_t> encoded) {
  memset(&m_bitmap, 0, sizeof(m_bitmap));
  if (stb_load_image(0, encoded.data(), (uint32_t)encoded.size(), &m_bitmap,
                     BITMAP_FMT_RGBA8888, BITMAP_FMT_RGBA8888, LCD_ORIENTATION_0) == RET_OK) {
    m_Width = (int)m_bitmap.w;
    m_Height = (int)m_bitmap.h;
  }
}

VGCanvasRenderImage::~VGCanvasRenderImage() {
  bitmap_destroy(&m_bitmap);
}

void VGCanvasRenderer::save() {
  vg_renderer_save(m_Renderer);
  m_opacityStack.push_back(m_opacityStack.back());
}

void VGCanvasRenderer::restore() {
  vg_renderer_restore(m_Renderer);
  if (m_opacityStack.size() > 1) {
    m_opacityStack.pop_back();
  }
}

void VGCanvasRenderer::transform(const Mat2D& t) {
  if (t[0] == 0 && t[1] == 0 && t[2] == 0 && t[3] == 0) {
    vg_renderer_transform(m_Renderer, 1, 0, 0, 1, t[4], t[5]);
  } else {
    vg_renderer_transform(m_Renderer, t[0], t[1], t[2], t[3], t[4], t[5]);
  }
}

void VGCanvasRenderer::modulateOpacity(float opacity) {
  m_opacityStack.back() = std::max(0.0f, m_opacityStack.back() * opacity);
}

void VGCanvasRenderer::drawPath(RenderPath* path, RenderPaint* paint) {
  auto vgPath = lite_rtti_cast<VGCanvasRenderPath*>(path);
  auto vgPaint = lite_rtti_cast<VGCanvasRenderPaint*>(paint);
  if (vgPath == NULL || vgPaint == NULL) {
    return;
  }

  vgcanvas_t* vg = m_Renderer->vg;
  float alpha = vg->global_alpha;
  vgcanvas_set_global_alpha(vg, alpha * m_opacityStack.back());
  vg_renderer_draw_path(m_Renderer, vgPath->path(), vgPaint->paint());
  vgcanvas_set_global_alpha(vg, alpha);
}

void VGCanvasRenderer::clipPath(RenderPath* path) {
  auto vgPath = lite_rtti_cast<VGCanvasRenderPath*>(path);
  if (vgPath == NULL) {
    return;
  }
  vg_renderer_clip_path(m_Renderer, vgPath->path());
}

void VGCanvasRenderer::drawImage(const RenderImage* image,
                                 ImageSampler sampler,
                                 BlendMode blendMode,
                                 float opacity) {
  (void)sampler;
  auto vgImage = lite_rtti_cast<const VGCanvasRenderImage*>(image);
  if (vgImage == NULL || vgImage->bitmap()->w == 0) {
    return;
  }

  if (blendMode != BlendMode::srcOver) {
    log_debug("drawImage not supported blendMode: %u\n", (unsigned int)blendMode);
  }

  vgcanvas_t* vg = m_Renderer->vg;
  const bitmap_t* bmp = vgImage->bitmap();
  float finalOpacity = std::max(0.0f, opacity * m_opacityStack.back());
  const Mat2D& uv = image->uvTransform();

  vgcanvas_save(vg);
  vgcanvas_set_global_alpha(vg, finalOpacity);
  vgcanvas_transform(vg, uv[0], uv[1], uv[2], uv[3], uv[4], uv[5]);
  vgcanvas_draw_image(vg, (bitmap_t*)bmp, 0, 0, bmp->w, bmp->h, 0, 0, (float)bmp->w,
                      (float)bmp->h);
  vgcanvas_restore(vg);
}

void VGCanvasRenderer::drawImageMesh(const RenderImage* image,
                                     ImageSampler sampler,
                                     rcp<RenderBuffer> vertices,
                                     rcp<RenderBuffer> uvCoords,
                                     rcp<RenderBuffer> indices,
                                     uint32_t vertexCount,
                                     uint32_t indexCount,
                                     BlendMode blendMode,
                                     float opacity) {
  (void)sampler;
  (void)vertexCount;
  auto vgImage = lite_rtti_cast<const VGCanvasRenderImage*>(image);
  auto vgIndices = lite_rtti_rcp_cast<DataRenderBuffer>(indices);
  auto vgVertices = lite_rtti_rcp_cast<DataRenderBuffer>(vertices);
  auto vgUvCoords = lite_rtti_rcp_cast<DataRenderBuffer>(uvCoords);
  if (vgImage == NULL || vgIndices == NULL || vgVertices == NULL || vgUvCoords == NULL) {
    return;
  }

  if (blendMode != BlendMode::srcOver) {
    log_debug("drawImageMesh not supported blendMode: %u\n", (unsigned int)blendMode);
  }

  vgcanvas_t* vg = m_Renderer->vg;
  const bitmap_t* bmp = vgImage->bitmap();
  const Mat2D localMatrix = Mat2D(1, 0, 0, -1, 0, (float)image->height());
  const float sx = (float)image->width();
  const float sy = (float)image->height();
  auto scale = [sx, sy](Vec2D v) { return Vec2D{v.x * sx, v.y * sy}; };

  const uint16_t* ndx = vgIndices->u16s();
  const Vec2D* pts = vgVertices->vecs();
  const Vec2D* uvs = vgUvCoords->vecs();
  uint32_t triangles = indexCount / 3;
  float finalOpacity = std::max(0.0f, opacity * m_opacityStack.back());

  vgcanvas_save(vg);
  vgcanvas_set_global_alpha(vg, finalOpacity);

  for (uint32_t i = 0; i < triangles; i++) {
    const uint32_t index0 = ndx[i * 3 + 0];
    const uint32_t index1 = ndx[i * 3 + 1];
    const uint32_t index2 = ndx[i * 3 + 2];

    const Vec2D p0 = pts[index0];
    const Vec2D p1 = pts[index1];
    const Vec2D p2 = pts[index2];
    const Vec2D v0 = scale(uvs[index0]);
    const Vec2D v1 = scale(uvs[index1]);
    const Vec2D v2 = scale(uvs[index2]);
    Mat2D mx = basis_matrix(p0, p1, p2) * basis_matrix(v0, v1, v2).invertOrIdentity() * localMatrix;

    vgcanvas_save(vg);
    vgcanvas_begin_path(vg);
    vgcanvas_move_to(vg, p0.x, p0.y);
    vgcanvas_line_to(vg, p1.x, p1.y);
    vgcanvas_line_to(vg, p2.x, p2.y);
    vgcanvas_close_path(vg);
    vgcanvas_clip_path(vg);
    vgcanvas_transform(vg, mx[0], mx[1], mx[2], mx[3], mx[4], mx[5]);
    vgcanvas_draw_image(vg, (bitmap_t*)bmp, 0, 0, bmp->w, bmp->h, 0, 0, sx, sy);
    vgcanvas_restore(vg);
  }

  vgcanvas_restore(vg);
}

rcp<RenderBuffer> VGCanvasFactory::makeRenderBuffer(RenderBufferType type,
                                                    RenderBufferFlags flags,
                                                    size_t sizeInBytes) {
  return make_rcp<DataRenderBuffer>(type, flags, sizeInBytes);
}

rcp<RenderShader> VGCanvasFactory::makeLinearGradient(float sx,
                                                      float sy,
                                                      float ex,
                                                      float ey,
                                                      const ColorInt colors[],
                                                      const float stops[],
                                                      size_t count) {
  return make_rcp<VGCanvasLinearGradientShader>(sx, sy, ex, ey, colors, stops, count);
}

rcp<RenderShader> VGCanvasFactory::makeRadialGradient(float cx,
                                                      float cy,
                                                      float radius,
                                                      const ColorInt colors[],
                                                      const float stops[],
                                                      size_t count) {
  return make_rcp<VGCanvasRadialGradientShader>(cx, cy, radius, colors, stops, count);
}

rcp<RenderPath> VGCanvasFactory::makeRenderPath(RawPath& rawPath, FillRule fillRule) {
  auto path = make_rcp<VGCanvasRenderPath>();
  path->addRawPath(rawPath);
  path->fillRule(fillRule);
  rawPath.rewind();
  return path;
}

rcp<RenderPath> VGCanvasFactory::makeEmptyRenderPath() {
  return make_rcp<VGCanvasRenderPath>();
}

rcp<RenderPaint> VGCanvasFactory::makeRenderPaint() {
  return make_rcp<VGCanvasRenderPaint>();
}

rcp<RenderImage> VGCanvasFactory::decodeImage(Span<const uint8_t> encoded) {
  auto image = make_rcp<VGCanvasRenderImage>(encoded);
  if (image->width() <= 0 || image->height() <= 0) {
    return nullptr;
  }
  return image;
}
