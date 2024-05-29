#include <iostream>
#include "transform.h"
#include <cmath>

namespace egc
{
    mat4 scale(float sx, float sy, float sz)
    {
        mat4 mat;

        mat.at(0, 0) = sx;
        mat.at(1, 1) = sy;
        mat.at(2, 2) = sz;

        return mat;
    }


    mat4 rotateY(float angle)
    {
        float ang = (angle * PI) / 180;

        mat4 mat;

        mat.at(0, 0) = cos(ang);
        mat.at(2, 0) = -sin(ang);
        mat.at(0, 2) = sin(ang);
        mat.at(2, 2) = cos(ang);

        return mat;
    }

    //transformation matrices in 2D
    mat3 translate(const vec2 translateArray) {
        float translationMatrixVector[] = { 1,0,0,0,1,0,translateArray.x,translateArray.y,1 };
        return mat3(translationMatrixVector);
    };
    mat3 translate(float tx, float ty) {
        float translationMatrixVector[] = { 1,0,0,0,1,0,tx,ty,1 };
        return mat3(translationMatrixVector);
    };
    mat3 scale(const vec2 scaleArray) {
        float scalingMatrixVector[] = { scaleArray.x,0,0,0,scaleArray.y,0,0,0,1 };
        return mat3(scalingMatrixVector);
    };
    mat3 scale(float sx, float sy) {
        float scalingMatrixVector[] = { sx,0,0,0,sy,0,0,0,1 };
        return mat3(scalingMatrixVector);
    };

    mat3 rotate(float angle) {
        angle = angle * PI / 180;
        float rotateMatrixVector[] = { cos(angle),sin(angle),0,-sin(angle),cos(angle),0,0,0,1 };
        return mat3(rotateMatrixVector);
    };

    //transformation matrices in 3D
    mat4 translate(const vec3 translateArray) {
        float translationMatrixVector[] = { 1,0,0,0,0,1,0,0,0,0,1,0,translateArray.x,translateArray.y,translateArray.z,1 };
        return mat4(translationMatrixVector);
    };
    mat4 translate(float tx, float ty, float tz) {
        float translationMatrixVector[] = { 1,0,0,0,0,1,0,0,0,0,1,0,tx,ty,tz,1 };
        return mat4(translationMatrixVector);
    };

    mat4 scale(const vec3 scaleArray) {
        float scalingMatrixVector[] = { scaleArray.x,0,0,0,0,scaleArray.y,0,0,0,0,scaleArray.z,0,0,0,0,1 };
        return mat4(scalingMatrixVector);
    };

    mat4 rotateX(float angle) {
        angle = angle * PI / 180;
        float rotateMatrixVector[] = { 1,0,0,0,0,cos(angle),sin(angle),0,0,-sin(angle),cos(angle),0,0,0,0,1 };
        return mat4(rotateMatrixVector);
    };

    mat4 rotateZ(float angle) {
        angle = angle * PI / 180;
        float rotateMatrixVector[] = { cos(angle),sin(angle),0,0,-sin(angle),cos(angle),0,0,0,0,1,0,0,0,0,1 };
        return mat4(rotateMatrixVector);
    };
}
