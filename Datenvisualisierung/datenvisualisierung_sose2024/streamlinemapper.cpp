#include "streamlinemapper.h"
#include <iostream>

StreamlineMapper::StreamlineMapper()
{
    std::cout << "StreamlineMapper constructor called" << std::endl;
}

StreamlineMapper::~StreamlineMapper() {
    std::cout << "StreamlineMapper destructor called" << std::endl;
}

void StreamlineMapper::getData(float *cube, int x, int y, int z) {

    source = cube;
    xs = x;
    ys = y;
    zs = z;
}

void StreamlineMapper::setValues(int seeds, int interpolation_length) {

    num_steps = interpolation_length;
    num_seeds = seeds;
}

float StreamlineMapper::bilinearInterpolation(float x_i, float y_i, int z_slice, int i) {

    if (x_i > 1 or x_i < 0 or y_i > 1 or y_i < 0) {
        return 1.0;
    }

    int x = x_i * (xs-1);
    int y = y_i * (ys-1);

    int y_shift = xs;
    int z_shift = z_slice*xs*ys + xs*y;

    float xd = (x_i-x)/(xs-1);
    float yd = (y_i-y)/(ys-1);
    float new_x1 = (1-xd) * source[3*(x+z_shift)+i] + xd * source[3*(x+1+z_shift)+i]; //lower part of the rectangle
    float new_x2 = (1-xd) * source[3*(x+y_shift+z_shift)+i] + xd * source[3*(x+1+y_shift+z_shift)+i]; // aaaand the upper part

    return (1-yd) * new_x1 + yd * new_x2;
}

float StreamlineMapper::trilinearInterpolation(float x_i, float y_i, float z_i, int i) {

    if (x_i > 1 or x_i < 0 or z_i > 1 or z_i < 0 or y_i > 1 or y_i < 0) {
        return 1.0;
    }
    int z = z_i * (zs-1);
    float zd = (z_i-z)/(zs-1);
    float cLower = bilinearInterpolation(x_i, y_i, z, i);
    float cUpper = bilinearInterpolation(x_i, y_i, z+1, i);
    return (1-zd) * cLower + zd * cUpper;
}

QVector3D StreamlineMapper::euler2D(QVector3D coordinate, float deltaT) {

    float v_x = trilinearInterpolation(coordinate.x(), coordinate.y(), coordinate.z(), 0);
    float v_y = trilinearInterpolation(coordinate.x(), coordinate.y(), coordinate.z(), 1);
    coordinate = coordinate + QVector3D(v_x, v_y, 0)*deltaT;
    return coordinate;
}

QVector3D StreamlineMapper::euler3D(QVector3D coordinate, float deltaT) {
    float v_x = trilinearInterpolation(coordinate.x(), coordinate.y(), coordinate.z(), 0);
    float v_y = trilinearInterpolation(coordinate.x(), coordinate.y(), coordinate.z(), 1);
    float v_z = trilinearInterpolation(coordinate.x(), coordinate.y(), coordinate.z(), 2);
    coordinate = coordinate + QVector3D(v_x, v_y, v_z)*deltaT;
    return coordinate;
}

QVector3D StreamlineMapper::rungeKutta2D(QVector3D coordinate, float deltaT) {

    float v_x = trilinearInterpolation(coordinate.x(), coordinate.y(), coordinate.z(), 0);
    float v_y = trilinearInterpolation(coordinate.x(), coordinate.y(), coordinate.z(), 1);
    QVector3D k1 = QVector3D(v_x, v_y, 0) * deltaT;
    QVector3D xNew = coordinate + (k1/2);

    v_x = trilinearInterpolation(xNew.x(),xNew.y(),xNew.z(), 0);
    v_y = trilinearInterpolation(xNew.x(),xNew.y(),xNew.z(), 1);
    QVector3D k2 = QVector3D(v_x, v_y, 0) * deltaT;

    xNew = coordinate + (k2/2);
    v_x = trilinearInterpolation(xNew.x(),xNew.y(),xNew.z(), 0);
    v_y = trilinearInterpolation(xNew.x(),xNew.y(),xNew.z(), 1);
    QVector3D k3 = QVector3D(v_x, v_y, 0) * deltaT;

    xNew = coordinate + k3;
    v_x = trilinearInterpolation(xNew.x(),xNew.y(),xNew.z(), 0);
    v_y = trilinearInterpolation(xNew.x(),xNew.y(),xNew.z(), 1);
    QVector3D k4 = QVector3D(v_x, v_y, 0) * deltaT;

    coordinate = coordinate + (k1/6) + (k2/3) + (k3/3) + (k4/6);

    return coordinate;
}

QVector3D StreamlineMapper::rungeKutta3D(QVector3D coordinate, float deltaT) {
    float v_x = trilinearInterpolation(coordinate.x(), coordinate.y(), coordinate.z(), 0);
    float v_y = trilinearInterpolation(coordinate.y(), coordinate.y(), coordinate.z(), 1);
    float v_z = trilinearInterpolation(coordinate.z(), coordinate.y(), coordinate.z(), 2);
    QVector3D k1 = QVector3D(v_x, v_y, v_z) * deltaT;
    QVector3D xNew = coordinate + (k1/2);

    v_x = trilinearInterpolation(xNew.x(),xNew.y(),xNew.z(), 0);
    v_y = trilinearInterpolation(xNew.x(),xNew.y(),xNew.z(), 1);
    v_z = trilinearInterpolation(xNew.x(),xNew.y(),xNew.z(), 2);
    QVector3D k2 = QVector3D(v_x, v_y, v_z) * deltaT;

    xNew = coordinate + (k2/2);
    v_x = trilinearInterpolation(xNew.x(),xNew.y(),xNew.z(), 0);
    v_y = trilinearInterpolation(xNew.x(),xNew.y(),xNew.z(), 1);
    v_z = trilinearInterpolation(xNew.x(),xNew.y(),xNew.z(), 2);
    QVector3D k3 = QVector3D(v_x, v_y, v_z) * deltaT;

    xNew = coordinate + k3;
    v_x = trilinearInterpolation(xNew.x(),xNew.y(),xNew.z(), 0);
    v_y = trilinearInterpolation(xNew.x(),xNew.y(),xNew.z(), 1);
    v_z = trilinearInterpolation(xNew.x(),xNew.y(),xNew.z(), 2);
    QVector3D k4 = QVector3D(v_x, v_y, v_z) * deltaT;

    coordinate = coordinate + (k1/6) + (k2/3) + (k3/3) + (k4/6);

    return coordinate;
}

int StreamlineMapper::get_num_seeds() {
    return num_seeds;
}

QVector<QVector<QVector3D>> StreamlineMapper::computeStreamlines() {


    QVector<QVector<QVector3D>> vectors; // We store all of our points in a dynamic array as Vector3Ds

    QVector3D seed_point;
    QVector<QVector3D> container;
    //vectors << seed_point;
    float dT = 0.2;

    for (int i = 0; i < num_seeds; i++) {
        seed_point = QVector3D(0.1*(i%10) +0.01, 0.1*(i/10 % 10) +0.01, 0.1 * (i/100) +0.01);
        container << seed_point;
        for (int j = 0; j < num_steps-1; j++) {
            seed_point = euler3D(seed_point, dT);
            if (seed_point.x() < 0 or seed_point.x() > 1 or seed_point.y() < 0 or seed_point.y() > 1 or seed_point.z() < 0 or seed_point.z() > 1) {
                break;
            }
            container << seed_point;
        }
        vectors << container;
        container.clear();
    }
    return vectors;
}










