#include "runtime/core/math/graphics_utils.h"

#include "runtime/core/base/macro.h"

#define _USE_MATH_DEFINES
#include <math.h>

// https://github.com/OpenGP/htrack/blob/master/util/eigen_opengl_helpers.h

namespace ArchViz
{
    FMatrix4 look_at(const FVector3& eye, const FVector3& center, const FVector3& up)
    {
        FVector3 f   = (center - eye).normalized();
        FVector3 u   = up.normalized();
        FVector3 s   = f.cross(u).normalized();
        u            = s.cross(f);
        FMatrix4 mat = FMatrix4::Zero();
        mat(0, 0)    = s.x();
        mat(0, 1)    = s.y();
        mat(0, 2)    = s.z();
        mat(0, 3)    = -s.dot(eye);
        mat(1, 0)    = u.x();
        mat(1, 1)    = u.y();
        mat(1, 2)    = u.z();
        mat(1, 3)    = -u.dot(eye);
        mat(2, 0)    = -f.x();
        mat(2, 1)    = -f.y();
        mat(2, 2)    = -f.z();
        mat(2, 3)    = f.dot(eye);
        mat.row(3) << 0, 0, 0, 1;
        return mat;
    }

    FMatrix4 perspective(float fovy, float ratio, float znear, float zfar)
    {
        FMatrix4 tr = FMatrix4::Zero();

        ASSERT(ratio > 0);
        ASSERT(zfar > znear);
        ASSERT(znear > 0);

        float radf          = M_PI * fovy / 180.0f;
        float tan_half_fovy = tanf(radf / 2.0);

        tr(0, 0) = 1.0 / (ratio * tan_half_fovy);
        tr(1, 1) = 1.0 / (tan_half_fovy);
        tr(2, 2) = -(zfar + znear) / (zfar - znear);
        tr(3, 2) = -1.0;
        tr(2, 3) = -(2.0 * zfar * znear) / (zfar - znear);

        return tr;
    }

    FMatrix4 orthogonal(float left, float right, float bottom, float top, float znear, float zfar)
    {
        FMatrix4 mat = FMatrix4::Identity();
        mat(0, 0)    = 2.0f / (right - left);
        mat(1, 1)    = 2.0f / (top - bottom);
        mat(2, 2)    = -2.0f / (zfar - znear);
        mat(3, 0)    = -(right + left) / (right - left);
        mat(3, 1)    = -(top + bottom) / (top - bottom);
        mat(3, 2)    = -(zfar + znear) / (zfar - znear);
        return mat;
    }
} // namespace ArchViz