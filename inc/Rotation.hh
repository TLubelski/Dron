#ifndef ROTATION_HH
#define ROTATION_HH

#include "cmp.hh"
#include "Matrix.hh"
#include <cmath>

enum Axis{X_axis = 'x', Y_axis = 'y', Z_axis = 'z'};

/*********************************
  Class of rotation matrix
**********************************/
class Rotation : public Matrix3D
{
public:
    Rotation(){ this->make_I(); }
    
    Rotation(Axis axis, double angle)
        : Matrix3D( create_matrix(axis, angle) ) { }
    
    Rotation(Matrix3D matrix)
        : Matrix3D(matrix)
        {
            if (!cmp(matrix.det(Sarruss), 1) || !cmp(matrix[0] * matrix[1], 0) || !cmp(matrix[0] * matrix[2], 0) || !cmp(matrix[1] * matrix[2], 0) )
            {
                std::cerr << "[!] Incorrect rotation matrix" << std::endl;
                exit(1);
            }
        }

private:
    static Matrix3D create_matrix(Axis axis, double angle)
    {
        switch (axis)
        {
        case X_axis:
            return Matrix3D({Vector3D({1.0, 0.0, 0.0}),
                             Vector3D({0.0, cos(angle * M_PI / 180), -sin(angle * M_PI / 180)}),
                             Vector3D({0.0, sin(angle * M_PI / 180), cos(angle * M_PI / 180)})});
            break;

        case Y_axis:
            return Matrix3D({Vector3D({cos(angle * M_PI / 180), 0.0, sin(angle * M_PI / 180)}),
                             Vector3D({0.0, 1.0, 0.0}),
                             Vector3D({-sin(angle * M_PI / 180), 0.0, cos(angle * M_PI / 180)})});
            break;

        case Z_axis:
            return Matrix3D({Vector3D({cos(angle * M_PI / 180), -sin(angle * M_PI / 180), 0.0}),
                             Vector3D({sin(angle * M_PI / 180), cos(angle * M_PI / 180), 0.0}),
                             Vector3D({0.0, 0.0, 1.0})});
            break;

        default:
            std::cerr << "[!]Incorrect axis in Rotation" << std::endl;
            exit(1);
            break;
        }
    }
};

#endif