//
//  mat4.h
//  Lab3_TODO
//
//  Copyright © 2016 CGIS. All rights reserved.
//

#pragma once

#include <algorithm>
#include <iostream>
#include "vec4.h"

namespace egc {
    class mat4
    {
    public:
        //==============================================
        //matrixData is stored in column-major order
        //  m00  m04   m08  m12
        //  m01  m05   m09  m13
        //  m02  m06   m10  m14
        //  m03  m07   m11  m15
        //
        //  matrixData[] = {m00, m01, m02, m03,
        //                  m04, m05, m06, m07,
        //                  m08, m09, m10, m11,
        //                  m12, m13, m14, m15}
        //==============================================
        float matrixData[16];
        
        //==============================================
        //constructors
        //==============================================
        
        //default constructor creates an identity matrix
        mat4()
        {
            for (int i = 0; i < 16; i++) {
                matrixData[i] = (i % 5) ? 0.0f : 1.0f;
            }
        }
        
        mat4(const float* srcMatrix)
        {
            std::copy(srcMatrix, srcMatrix + 16, matrixData);
        }
        
        //==============================================
        // TO BE IMPLEMENTED
        //==============================================
        mat4& operator =(const mat4& srcMatrix) {
            for (int i = 0; i < 16; i++)
                this->matrixData[i] = srcMatrix.matrixData[i];
            return *this;
        }
        mat4 operator *(float scalarValue) const {
            float a[16];
            for (int i = 0; i < 16; i++)
                a[i] = this->matrixData[i] * scalarValue;
            return mat4(a);
        };
        mat4 operator *(const mat4& srcMatrix) const {
            float a[16];
            a[0] = this->matrixData[0] * srcMatrix.matrixData[0] + this->matrixData[4] * srcMatrix.matrixData[1] + this->matrixData[8] * srcMatrix.matrixData[2] + this->matrixData[12] * srcMatrix.matrixData[3];
            a[4] = this->matrixData[0] * srcMatrix.matrixData[4] + this->matrixData[4] * srcMatrix.matrixData[5] + this->matrixData[8] * srcMatrix.matrixData[6] + this->matrixData[12] * srcMatrix.matrixData[7];
            a[8] = this->matrixData[0] * srcMatrix.matrixData[8] + this->matrixData[4] * srcMatrix.matrixData[9] + this->matrixData[8] * srcMatrix.matrixData[10] + this->matrixData[12] * srcMatrix.matrixData[11];
            a[12] = this->matrixData[0] * srcMatrix.matrixData[12] + this->matrixData[4] * srcMatrix.matrixData[13] + this->matrixData[8] * srcMatrix.matrixData[14] + this->matrixData[12] * srcMatrix.matrixData[15];
           
            a[1] = this->matrixData[1] * srcMatrix.matrixData[0] + this->matrixData[5] * srcMatrix.matrixData[1] + this->matrixData[9] * srcMatrix.matrixData[2] + this->matrixData[13] * srcMatrix.matrixData[3];
            a[5] = this->matrixData[1] * srcMatrix.matrixData[4] + this->matrixData[5] * srcMatrix.matrixData[5] + this->matrixData[9] * srcMatrix.matrixData[6] + this->matrixData[13] * srcMatrix.matrixData[7];
            a[9] = this->matrixData[1] * srcMatrix.matrixData[8] + this->matrixData[5] * srcMatrix.matrixData[9] + this->matrixData[9] * srcMatrix.matrixData[10] + this->matrixData[13] * srcMatrix.matrixData[11];
            a[13] = this->matrixData[1] * srcMatrix.matrixData[12] + this->matrixData[5] * srcMatrix.matrixData[13] + this->matrixData[9] * srcMatrix.matrixData[14] + this->matrixData[13] * srcMatrix.matrixData[15];
            
            a[2] = this->matrixData[2] * srcMatrix.matrixData[0] + this->matrixData[6] * srcMatrix.matrixData[1] + this->matrixData[10] * srcMatrix.matrixData[2] + this->matrixData[14] * srcMatrix.matrixData[3];
            a[6] = this->matrixData[2] * srcMatrix.matrixData[4] + this->matrixData[6] * srcMatrix.matrixData[5] + this->matrixData[10] * srcMatrix.matrixData[6] + this->matrixData[14] * srcMatrix.matrixData[7];
            a[10] = this->matrixData[2] * srcMatrix.matrixData[8] + this->matrixData[6] * srcMatrix.matrixData[9] + this->matrixData[10] * srcMatrix.matrixData[10] + this->matrixData[14] * srcMatrix.matrixData[11];
            a[14] = this->matrixData[2] * srcMatrix.matrixData[12] + this->matrixData[6] * srcMatrix.matrixData[13] + this->matrixData[10] * srcMatrix.matrixData[14] + this->matrixData[14] * srcMatrix.matrixData[15];
            
            a[3] = this->matrixData[3] * srcMatrix.matrixData[0] + this->matrixData[7] * srcMatrix.matrixData[1] + this->matrixData[11] * srcMatrix.matrixData[2] + this->matrixData[15] * srcMatrix.matrixData[3];
            a[7] = this->matrixData[3] * srcMatrix.matrixData[4] + this->matrixData[7] * srcMatrix.matrixData[5] + this->matrixData[11] * srcMatrix.matrixData[6] + this->matrixData[15] * srcMatrix.matrixData[7];
            a[11] = this->matrixData[3] * srcMatrix.matrixData[8] + this->matrixData[7] * srcMatrix.matrixData[9] + this->matrixData[11] * srcMatrix.matrixData[10] + this->matrixData[15] * srcMatrix.matrixData[11];
            a[15] = this->matrixData[3] * srcMatrix.matrixData[12] + this->matrixData[7] * srcMatrix.matrixData[13] + this->matrixData[11] * srcMatrix.matrixData[14] + this->matrixData[15] * srcMatrix.matrixData[15];
            return mat4(a);
        };
        vec4 operator *(const vec4& srcVector) const {
            float x = this->matrixData[0] * srcVector.x + this->matrixData[4] * srcVector.y + this->matrixData[8] * srcVector.z + this->matrixData[12] * srcVector.w;
            float y = this->matrixData[1] * srcVector.x + this->matrixData[5] * srcVector.y + this->matrixData[9] * srcVector.z + this->matrixData[13] * srcVector.w;
            float z = this->matrixData[2] * srcVector.x + this->matrixData[6] * srcVector.y + this->matrixData[10] * srcVector.z + this->matrixData[14] * srcVector.w;
            float w = this->matrixData[3] * srcVector.x + this->matrixData[7] * srcVector.y + this->matrixData[11] * srcVector.z + this->matrixData[15] * srcVector.w;
            return vec4(x, y, z, w);
        };
        mat4 operator +(const mat4& srcMatrix) const {
            float a[16];
            for (int i = 0; i < 16; i++)
                a[i] = this->matrixData[i] + srcMatrix.matrixData[i];
            return mat4(a);
        };
        //get element by (row, column)
        float& at(int i, int j) {
            return this->matrixData[j * 4 + i];
        };
        const float& at(int i, int j) const {
            return this->matrixData[j * 4 + i];
        };
        float determinant() const {
            float a1[] = {this->matrixData[1],this->matrixData[2], this->matrixData[3], this->matrixData[5], this->matrixData[6], this->matrixData[7],
                         this->matrixData[9], this->matrixData[10], this->matrixData[11] };
            float a4[] = {this->matrixData[5],this->matrixData[6], this->matrixData[7], this->matrixData[9], this->matrixData[10], this->matrixData[11],
                         this->matrixData[13], this->matrixData[14], this->matrixData[15] };
            float a2[] = {this->matrixData[1],this->matrixData[2], this->matrixData[3], this->matrixData[9], this->matrixData[10], this->matrixData[11],
                        this->matrixData[13], this->matrixData[14], this->matrixData[15] };
            float a3[] = {this->matrixData[1],this->matrixData[2], this->matrixData[3], this->matrixData[5], this->matrixData[6], this->matrixData[7],
                         this->matrixData[13], this->matrixData[14], this->matrixData[15] };
            mat3 m1(a1), m2(a2), m3(a3), m4(a4);
            
            return  -this->matrixData[12] * m1.determinant() - this->matrixData[4] * m2.determinant() +
                    this->matrixData[8] * m3.determinant() + this->matrixData[0] * m4.determinant();
        };
        mat4 inverse() const {
            mat4 matrix = this->transpose();
            float det = this->determinant();
            if (det == 0)
                exit(1);

            float a0[] = { matrix.matrixData[5],matrix.matrixData[6],matrix.matrixData[7],matrix.matrixData[9],matrix.matrixData[10],matrix.matrixData[11],matrix.matrixData[13],matrix.matrixData[14],matrix.matrixData[15] };
            float a1[] = { matrix.matrixData[4], matrix.matrixData[6], matrix.matrixData[7], matrix.matrixData[8], matrix.matrixData[10], matrix.matrixData[11], matrix.matrixData[12], matrix.matrixData[14], matrix.matrixData[15] };
            float a2[] = { matrix.matrixData[4], matrix.matrixData[5], matrix.matrixData[7], matrix.matrixData[8], matrix.matrixData[9], matrix.matrixData[11], matrix.matrixData[12], matrix.matrixData[13], matrix.matrixData[15] };
            float a3[] = { matrix.matrixData[4], matrix.matrixData[5], matrix.matrixData[6], matrix.matrixData[8], matrix.matrixData[9], matrix.matrixData[10], matrix.matrixData[12], matrix.matrixData[13], matrix.matrixData[14] };
            float a4[] = { matrix.matrixData[1], matrix.matrixData[2], matrix.matrixData[3], matrix.matrixData[9], matrix.matrixData[10], matrix.matrixData[11], matrix.matrixData[13], matrix.matrixData[14], matrix.matrixData[15] };
            float a5[] = { matrix.matrixData[0], matrix.matrixData[2], matrix.matrixData[3], matrix.matrixData[8], matrix.matrixData[10], matrix.matrixData[11], matrix.matrixData[12], matrix.matrixData[14], matrix.matrixData[15] };
            float a6[] = { matrix.matrixData[0], matrix.matrixData[1], matrix.matrixData[3], matrix.matrixData[8], matrix.matrixData[9], matrix.matrixData[11], matrix.matrixData[12], matrix.matrixData[13], matrix.matrixData[15] };
            float a7[] = { matrix.matrixData[0], matrix.matrixData[1], matrix.matrixData[2], matrix.matrixData[8], matrix.matrixData[9], matrix.matrixData[10], matrix.matrixData[12], matrix.matrixData[13], matrix.matrixData[14] };
            float a8[] = { matrix.matrixData[1], matrix.matrixData[2], matrix.matrixData[3], matrix.matrixData[5], matrix.matrixData[6], matrix.matrixData[7], matrix.matrixData[13], matrix.matrixData[14], matrix.matrixData[15] };
            float a9[] = { matrix.matrixData[0], matrix.matrixData[2], matrix.matrixData[3], matrix.matrixData[4], matrix.matrixData[6], matrix.matrixData[7], matrix.matrixData[12], matrix.matrixData[14], matrix.matrixData[15] };
            float a10[] = { matrix.matrixData[0], matrix.matrixData[1], matrix.matrixData[3], matrix.matrixData[4], matrix.matrixData[5], matrix.matrixData[7], matrix.matrixData[12], matrix.matrixData[13], matrix.matrixData[15] };
            float a11[] = { matrix.matrixData[0], matrix.matrixData[1], matrix.matrixData[2], matrix.matrixData[4], matrix.matrixData[5], matrix.matrixData[6], matrix.matrixData[12], matrix.matrixData[13], matrix.matrixData[14] };
            float a12[] = { matrix.matrixData[1], matrix.matrixData[2], matrix.matrixData[3], matrix.matrixData[5], matrix.matrixData[6], matrix.matrixData[7], matrix.matrixData[9], matrix.matrixData[10], matrix.matrixData[11] };
            float a13[] = { matrix.matrixData[0], matrix.matrixData[2], matrix.matrixData[3], matrix.matrixData[4], matrix.matrixData[6], matrix.matrixData[7], matrix.matrixData[8], matrix.matrixData[10], matrix.matrixData[11] };
            float a14[] = { matrix.matrixData[0], matrix.matrixData[1], matrix.matrixData[3], matrix.matrixData[4], matrix.matrixData[5], matrix.matrixData[7], matrix.matrixData[8], matrix.matrixData[9], matrix.matrixData[11] };
            float a15[] = { matrix.matrixData[0], matrix.matrixData[1], matrix.matrixData[2], matrix.matrixData[4], matrix.matrixData[5], matrix.matrixData[6], matrix.matrixData[8], matrix.matrixData[9], matrix.matrixData[10] };

            mat3 dets[16] = {
                mat3(a0),mat3(a1),mat3(a2),mat3(a3),mat3(a4),mat3(a5),mat3(a6),mat3(a7),
                mat3(a8),mat3(a9),mat3(a10),mat3(a11),mat3(a12),mat3(a13),mat3(a14),mat3(a15)
            };
            float rez[16] = {
                dets[0].determinant() / det,
                -dets[1].determinant() / det,
                dets[2].determinant() / det,
                -dets[3].determinant() / det,

                -dets[4].determinant() / det,
                dets[5].determinant() / det,
                -dets[6].determinant() / det,
                dets[7].determinant() / det,

                dets[8].determinant() / det,
                -dets[9].determinant() / det,
                dets[10].determinant() / det,
                -dets[11].determinant() / det,

                -dets[12].determinant() / det,
                dets[13].determinant() / det,
                -dets[14].determinant() / det,
                dets[15].determinant() / det,
            };
            return mat4(rez);
        };
        mat4 transpose() const {
            float a[16];
            a[0] = this->matrixData[0], a[1] = this->matrixData[4];
            a[2] = this->matrixData[8], a[3] = this->matrixData[12];

            a[4] = this->matrixData[1], a[5] = this->matrixData[5];
            a[6] = this->matrixData[9], a[7] = this->matrixData[13];
            
            a[8] = this->matrixData[2], a[9] = this->matrixData[6];
            a[10] = this->matrixData[10], a[11] = this->matrixData[14];
            
            a[12] = this->matrixData[3], a[13] = this->matrixData[7];
            a[14] = this->matrixData[11], a[15] = this->matrixData[15];
            return mat4(a);
        };
        
        //==============================================
        friend std::ostream& operator<< (std::ostream &out, const mat4& srcMatrix);
        
        bool operator ==(const mat4& srcMatrix) const
        {
            for (int i = 0; i < 16; i++)
                if (std::abs(matrixData[i] - srcMatrix.matrixData[i]) >= std::numeric_limits<float>::epsilon()) {
                    return false;
                }
            return true;
        }
    };
    
    inline std::ostream& operator<< (std::ostream &out, const mat4& srcMatrix)
    {
        for(int i = 0; i < 4; i++)
            out << srcMatrix.matrixData[i] << "\t" << srcMatrix.matrixData[i + 4] << "\t" << srcMatrix.matrixData[i + 8] << "\t" << srcMatrix.matrixData[i + 12] << "\n";
        return out;
    };
}