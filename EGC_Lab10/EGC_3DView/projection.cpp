#include "projection.h"
#include <cmath> // for tan, acos

namespace egc {
    mat4 defineViewTransformMatrix(int startX, int startY, int width, int height)
    {
        mat4 viewTransformMatrix;

        float t[] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, -1, 0, 1 };
        float m[] = { 1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
        float s[] = { width / 2, 0, 0, 0, 0, height / 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };

        mat4 T(t), M(m), S(s);

        float t2[] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, startX, startY, 1, 1 };
        mat4 T2(t2);

        viewTransformMatrix = T2 * S * M * T;

        return viewTransformMatrix;
    }

    mat4 defineCameraMatrix(Camera mc)
    {
        mat4 cameraMatrix;

        vec3 w = -(mc.cameraTarget - mc.cameraPosition).normalize();
        vec3 u = crossProduct(mc.cameraUp, w).normalize();
        vec3 v = crossProduct(w, u);

        float c[] =
        {
            u.x, v.x, w.x, 0,
            u.y, v.y, w.y, 0,
            u.z, v.z, w.z, 0,
            0, 0, 0, 1
        };
        float e[] =
        {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            -mc.cameraPosition.x, -mc.cameraPosition.y, -mc.cameraPosition.z, 1
        };
        mat4 C(c), E(e);
        cameraMatrix = C * E;
        return cameraMatrix;
    }

    mat4 definePerspectiveProjectionMatrix(float fov, float aspect, float zNear, float zFar)
    {
        mat4 perspectiveProjectionMatrix;

        float tan_teta = tan(fov * PI / 180.0f);
        float m[] = { -1 / (aspect * tan_teta), 0, 0, 0, 0, -1 / tan_teta, 0, 0,
            0, 0, (zFar + zNear) / (zNear - zFar) , 1, 0, 0, 2 * zFar * zNear / (zFar - zNear), 0 };

        perspectiveProjectionMatrix = mat4(m);

        return perspectiveProjectionMatrix;
    }

    void perspectiveDivide(vec4& iv)
    {
        float a = iv.w;
        iv.x /= a;
        iv.y /= a;
        iv.z /= a;
        iv.w = 1.0f;
    }

    bool clipPointInHomogeneousCoordinate(const egc::vec4& vertex)
    {
        if (-vertex.w <= vertex.x <= vertex.w)
            return true;
        if (-vertex.w <= vertex.y <= vertex.w)
            return true;
        if (-vertex.w <= vertex.z <= vertex.w)
            return true;
        return false;
    }

    bool clipTriangleInHomegeneousCoordinates(const std::vector<egc::vec4>& triangle)
    {
        for (auto it : triangle)
            if (clipPointInHomogeneousCoordinate(it) == true)
                return true;
        return false;
    }

    egc::vec3 findNormalVectorToTriangle(const std::vector<egc::vec4>& triangle)
    {
        vec3 v0 = vec3(triangle.at(0).x, triangle.at(0).y, triangle.at(0).z);
        vec3 v1 = vec3(triangle.at(1).x, triangle.at(1).y, triangle.at(1).z);
        vec3 v2 = vec3(triangle.at(2).x, triangle.at(2).y, triangle.at(2).z);

        vec3 n = crossProduct(v1 - v0, v2 - v0).normalize();
        return n;
    }

    egc::vec4 findCenterPointOfTriangle(const std::vector<egc::vec4>& triangle)
    {
        egc::vec4 triangleCenter;
        triangleCenter = (triangle.at(0) + triangle.at(1) + triangle.at(2)) * (1.0f / 3.0f);
        triangleCenter.w = 1.0f; // Ensure w is set to 1 for center point
        return triangleCenter;
    }

    bool isTriangleVisible(const std::vector<egc::vec4>& triangle, const egc::vec3& normalVector)
    {
        vec3 secondVector = findNormalVectorToTriangle(triangle);
        float teta = acos(dotProduct(normalVector, secondVector));
        if (teta > cos(M_PI))
            return true;
        return false;
    }

    void displayNormalVectors(egc::vec3& normalVector, egc::vec4& triangleCenter, SDL_Renderer* renderer, egc::mat4 viewTransformMatrix, egc::mat4 perspectiveMatrix)
    {
        // Calculate the end point of the normal vector in world coordinates
        vec3 endPointWorld = vec3(triangleCenter.x, triangleCenter.y, triangleCenter.z) + normalVector * 0.5;
        vec4 endPoint(endPointWorld.x, endPointWorld.y, endPointWorld.z, 1.0f);

        // Transform the center of the triangle
        vec4 transformedCenter =  perspectiveMatrix * triangleCenter;
        perspectiveDivide(transformedCenter);
        transformedCenter = viewTransformMatrix * transformedCenter;


        // Transform the end point of the normal vector
        vec4 transformedEndPoint = perspectiveMatrix * endPoint;
        perspectiveDivide(transformedEndPoint);
        transformedEndPoint = viewTransformMatrix * transformedEndPoint;

        // Set the color for drawing the normal vectors
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

        // Draw the line from the transformed center to the transformed end point of the normal vector
        SDL_RenderDrawLine(renderer, static_cast<int>(transformedCenter.x), static_cast<int>(transformedCenter.y), static_cast<int>(transformedEndPoint.x), static_cast<int>(transformedEndPoint.y));
    }

}
