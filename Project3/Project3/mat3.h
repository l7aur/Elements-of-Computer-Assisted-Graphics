//
//  mat3.h
//  Lab3_TODO
//
//  Copyright © 2016 CGIS. All rights reserved.
//

#pragma once

#include <algorithm>
#include <iostream>
#include "vec3.h"

namespace egc {
    class mat3
    {
    public:
        //==============================================
        //matrixData is stored in column-major order
        //  m0  m3   m6
        //  m1  m4   m7
        //  m2  m5   m8
        //
        //  matrixData[] = {m0, m1, m2,
        //                  m3, m4, m5,
        //                  m6, m7, m8}
        //==============================================
        float matrixData[9];
        
        //==============================================
        //constructors
        //==============================================
        
        //default constructor creates an identity matrix
        mat3()
        {
            for (int i = 0; i < 9; i++) {
                matrixData[i] = (i % 4) ? 0.0f : 1.0f;
            }
        }
        
        mat3(const float* srcMatrix)
        {
            std::copy(srcMatrix, srcMatrix + 9, matrixData);
        }
        
        //==============================================
        // TO BE IMPLEMENTED
        //==============================================
        mat3& operator =(const mat3& srcMatrix) {
            for (int i = 0; i < 9; i++)
                this->matrixData[i] = srcMatrix.matrixData[i];
            return *this;
        };
        mat3 operator *(float scalarValue) const {
            float a[9];
            for (int i = 0; i < 9; i++)
                a[i] = this->matrixData[i] * scalarValue;
            return mat3(a);
        };
        mat3 operator *(const mat3& srcMatrix) const {
            float a[9];
            a[0] = this->matrixData[0] * srcMatrix.matrixData[0] + this->matrixData[3] * srcMatrix.matrixData[1] + this->matrixData[6] * srcMatrix.matrixData[2];
            a[3] = this->matrixData[0] * srcMatrix.matrixData[3] + this->matrixData[3] * srcMatrix.matrixData[4] + this->matrixData[6] * srcMatrix.matrixData[5];
            a[6] = this->matrixData[0] * srcMatrix.matrixData[6] + this->matrixData[3] * srcMatrix.matrixData[7] + this->matrixData[6] * srcMatrix.matrixData[8];
            
            a[1] = this->matrixData[1] * srcMatrix.matrixData[0] + this->matrixData[4] * srcMatrix.matrixData[1] + this->matrixData[7] * srcMatrix.matrixData[2];
            a[4] = this->matrixData[1] * srcMatrix.matrixData[3] + this->matrixData[4] * srcMatrix.matrixData[4] + this->matrixData[7] * srcMatrix.matrixData[5];
            a[7] = this->matrixData[1] * srcMatrix.matrixData[6] + this->matrixData[4] * srcMatrix.matrixData[7] + this->matrixData[7] * srcMatrix.matrixData[8];
            
            a[2] = this->matrixData[2] * srcMatrix.matrixData[0] + this->matrixData[5] * srcMatrix.matrixData[1] + this->matrixData[8] * srcMatrix.matrixData[2];
            a[5] = this->matrixData[2] * srcMatrix.matrixData[3] + this->matrixData[5] * srcMatrix.matrixData[4] + this->matrixData[8] * srcMatrix.matrixData[5];
            a[8] = this->matrixData[2] * srcMatrix.matrixData[6] + this->matrixData[5] * srcMatrix.matrixData[7] + this->matrixData[8] * srcMatrix.matrixData[8];
            return mat3(a);
        };
        vec3 operator *(const vec3& srcVector) const {
            float x = this->matrixData[0] * srcVector.x + this->matrixData[3] * srcVector.y + this->matrixData[6] * srcVector.z;
            float y = this->matrixData[1] * srcVector.x + this->matrixData[4] * srcVector.y + this->matrixData[7] * srcVector.z;
            float z = this->matrixData[2] * srcVector.x + this->matrixData[5] * srcVector.y + this->matrixData[8] * srcVector.z;
            return vec3(x, y, z);
        };
        mat3 operator +(const mat3& srcMatrix) const {
            float a[9];
            for (int i = 0; i < 9; i++)
                a[i] = this->matrixData[i] + srcMatrix.matrixData[i];
            return mat3(a);
        };
        //get element by (row, column)
        float& at(int i, int j) {
            return this->matrixData[j * 3 + i];
        };
        const float& at(int i, int j) const {
            return this->matrixData[j * 3 + i];
        };
        float determinant() const {
            float p1 = this->matrixData[0] * this->matrixData[4] * this->matrixData[8];
            float p2 = this->matrixData[1] * this->matrixData[5] * this->matrixData[6];
            float p3 = this->matrixData[2] * this->matrixData[3] * this->matrixData[7];

            float p4 = this->matrixData[2] * this->matrixData[4] * this->matrixData[6];
            float p5 = this->matrixData[0] * this->matrixData[5] * this->matrixData[7];
            float p6 = this->matrixData[1] * this->matrixData[3] * this->matrixData[8];
            return p1 + p2 + p3 - p4 - p5 - p6;
        };
        mat3 inverse() const {
            float a[9];
            float det = this->determinant();
            if (det == 0)
                exit(1);
            mat3 a_star = this->transpose();
            a[0] = a_star.matrixData[4] * a_star.matrixData[8] - a_star.matrixData[5] * a_star.matrixData[7];
            a[1] = -(a_star.matrixData[3] * a_star.matrixData[8] - a_star.matrixData[5] * a_star.matrixData[6]);
            a[2] = a_star.matrixData[3] * a_star.matrixData[7] - a_star.matrixData[4] * a_star.matrixData[6];

            a[3] = -(a_star.matrixData[1] * a_star.matrixData[8] - a_star.matrixData[2] * a_star.matrixData[7]);
            a[4] = a_star.matrixData[0] * a_star.matrixData[8] - a_star.matrixData[2] * a_star.matrixData[6];
            a[5] = -(a_star.matrixData[0] * a_star.matrixData[7] - a_star.matrixData[1] * a_star.matrixData[6]);

            a[6] = a_star.matrixData[1] * a_star.matrixData[5] - a_star.matrixData[2] * a_star.matrixData[4];
            a[7] = -(a_star.matrixData[0] * a_star.matrixData[5] - a_star.matrixData[2] * a_star.matrixData[3]);
            a[8] = a_star.matrixData[0] * a_star.matrixData[4] - a_star.matrixData[1] * a_star.matrixData[3];

            for (int i = 0; i < 9; i++)
                a[i] /= det;

            return mat3(a);
        };
        mat3 transpose() const {
            float a[9];
            a[0] = this->matrixData[0];
            a[1] = this->matrixData[3];
            a[2] = this->matrixData[6];

            a[3] = this->matrixData[1];
            a[4] = this->matrixData[4];
            a[5] = this->matrixData[7];
            
            a[6] = this->matrixData[2];
            a[7] = this->matrixData[5];
            a[8] = this->matrixData[8];
            return mat3(a);
        };
        
        //==============================================
        friend std::ostream& operator<< (std::ostream &out, const mat3& srcMatrix);
        
        bool operator ==(const mat3& srcMatrix) const
        {
            for (int i = 0; i < 9; i++)
                if (std::abs(matrixData[i] - srcMatrix.matrixData[i]) >= std::numeric_limits<float>::epsilon()) {
                    return false;
                }
            return true;
        }
    };
    
    inline std::ostream& operator<< (std::ostream &out, const mat3& srcMatrix)
    {
        for(int i = 0; i < 3; i++)
            out << srcMatrix.matrixData[i] << "\t" << srcMatrix.matrixData[i + 3] << "\t" << srcMatrix.matrixData[i + 6] << "\n";
        return out;
    };
}