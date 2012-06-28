/*
 * Point.cpp
 *
 *  Created on: May 30, 2012
 *      Author: jsepulve
 */

#include "Point.h"


namespace patterns {

const int Point::TOTAL_POINTS = 27;
const int Point::CoordinatesToPointConversionMatrix [3] = {1,3,9};
const int Point::PointToCoordinatesConversionMatrix [TOTAL_POINTS][3] = {
    {0,0,0}, //0
    {1,0,0}, //1
    {2,0,0}, //2
    {0,1,0}, //3
    {1,1,0}, //4
    {2,1,0}, //5
    {0,2,0}, //6
    {1,2,0}, //7
    {2,2,0}, //8
    {0,0,1}, //9
    {1,0,1}, //10
    {2,0,1}, //11
    {0,1,1}, //12
    {1,1,1}, //13
    {2,1,1}, //14
    {0,2,1}, //15
    {1,2,1}, //16
    {2,2,1}, //17
    {0,0,2}, //18
    {1,0,2}, //19
    {2,0,2}, //20
    {0,1,2}, //21
    {1,1,2}, //22
    {2,1,2}, //23
    {0,2,2}, //24
    {1,2,2}, //25
    {2,2,2}  //26
};

const int Point::RotationMatrix_X [4][4][4] = {
    { /// 0 degree rotation
        { 1, 0, 0, 0},
        { 0, 1, 0, 0},
        { 0, 0, 1, 0},
        { 0, 0, 0, 0}
    },
    { /// 90 degree rotation
        {1, 0, 0, 0},
        {0, 0,-1, 2},
        {0, 1, 0, 0},
        {0, 0, 0, 1}
    },
    { /// 180 degree rotation
        {1, 0, 0, 0},
        {0,-1, 0, 2},
        {0, 0,-1, 2},
        {0, 0, 0, 1}
    },
    { /// 270 degree rotation
        {1, 0, 0, 0},
        {0, 0, 1, 0},
        {0,-1, 0, 2},
        {0, 0, 0, 1}
    }
};

const int Point::RotationMatrix_Y [4][4][4] =
{
    { /// 0 degree rotation
        { 1, 0, 0, 0},
        { 0, 1, 0, 0},
        { 0, 0, 1, 0},
        { 0, 0, 0, 0}
    },
    { /// 90 degree rotation
        { 0, 0, 1, 0},
        { 0, 1, 0, 0},
        {-1, 0, 0, 2},
        { 0, 0, 0, 1}
    },
    { /// 180 degree rotation
        {-1, 0, 0, 2},
        { 0, 1, 0, 0},
        { 0, 0,-1, 2},
        { 0, 0, 0, 1}
    },
    { /// 270 degree rotation
        { 0, 0,-1, 2},
        { 0, 1, 0, 0},
        { 1, 0, 0, 0},
        { 0, 0, 0, 1}
    }
};

const int Point::RotationMatrix_Z [4][4][4] =
{
    { /// 0 degree rotation
        { 1, 0, 0, 0},
        { 0, 1, 0, 0},
        { 0, 0, 1, 0},
        { 0, 0, 0, 0}
    },
    { /// 90 degree rotation
        { 0,-1, 0, 2},
        { 1, 0, 0, 0},
        { 0, 0, 1, 0},
        { 0, 0, 0, 1}
    },
    { /// 180 degree rotation
        {-1, 0, 0, 2},
        { 0,-1, 0, 2},
        { 0, 0, 1, 0},
        { 0, 0, 0, 1}
    },
    { /// 270 degree rotation
        { 0, 1, 0, 0},
        {-1, 0, 0, 2},
        { 0, 0, 1, 0},
        { 0, 0, 0, 1}
    }
};

Point::Point(int id, int x, int y, int z)
    : m_id(id), m_X(x), m_Y(y), m_Z(z), m_T(1) { 
    m_point = CoordinatesToPoint(); 
}

Point::Point(int x, int y, int z): m_X(x), m_Y(y), m_Z(z), m_T(1) { 
    m_point = CoordinatesToPoint(); 
    m_id    = m_point;
}



int Point::CoordinatesToPoint() {
    return (m_X*CoordinatesToPointConversionMatrix[0] +
            m_Y*CoordinatesToPointConversionMatrix[1] +
            m_Z*CoordinatesToPointConversionMatrix[2]);
}

void Point::PointToCoordinates(int point) {
    if ( (point >= 0) && (point <TOTAL_POINTS) ) {
        m_X = PointToCoordinatesConversionMatrix[point][0];
        m_Y = PointToCoordinatesConversionMatrix[point][1];
        m_Z = PointToCoordinatesConversionMatrix[point][2];
        m_point = point;
        m_id = m_point;
    }
    else {
        m_X=0;
        m_Y=0;
        m_Z=0;
        m_point = 0;
        m_id=0;
    }
}

int Point::rotX(int input_step) {
    int step = this->getSteps(input_step);

    const int (*rot)[4]=RotationMatrix_X[step];

    int temp[4] = {0, 0, 0, 0};

    for (int i=0; i<4; i++)
    {
        temp[i] = rot[i][0]*m_X + rot[i][1]*m_Y + rot[i][2]*m_Z + rot[i][3]*m_T;
    }
    m_X = temp[0];
    m_Y = temp[1];
    m_Z = temp[2];
    m_point = this->CoordinatesToPoint();

    return (m_point);
}

int Point::rotate(int axis, int number_steps) {
    /// Do nothing just return current position
    if ( (axis > -1) && (axis < 4) )
    {
        int step = this->getSteps(number_steps);
        const int (*rot)[4];
        if (axis == 0)
            rot=RotationMatrix_X[step];
        else if (axis == 1)
            rot=RotationMatrix_Y[step];
        else if (axis == 2)
            rot=RotationMatrix_Z[step];

        int temp[4] = {0, 0, 0, 0};

        for (int i=0; i<4; i++)
        {
            temp[i] = rot[i][0]*m_X + rot[i][1]*m_Y + rot[i][2]*m_Z + rot[i][3]*m_T;
        }

        m_X = temp[0];
        m_Y = temp[1];
        m_Z = temp[2];
        m_point = this->CoordinatesToPoint();
    }

    return (m_point);
}


void Point::setPosition(int _x, int _y, int _z) {
    m_X = _x;
    m_Y = _y;
    m_Z = _z;
    m_point = this->CoordinatesToPoint();
}

void Point::setPosition(int point) {
    this->PointToCoordinates(point);
    m_point = this->CoordinatesToPoint();
}


int Point::getSteps(int rotation) {
    if (rotation < 0)
    {
        int step = (int)fabs(rotation) % 4;
        if (step == 1)
            step = 3; // -90 degrees --> +270 degrees
        else if (step == 3)
            step = 1; // -270 degrees --> +90 degrees

        return step;
    }
    return (rotation % 4);
}

int Point::coordinatesToID(int x, int y, int z) {
    for (int i=0; i< TOTAL_POINTS; i++)
    {
        if ( (PointToCoordinatesConversionMatrix[i][0] == x) && 
                (PointToCoordinatesConversionMatrix[i][1] == y) && 
                (PointToCoordinatesConversionMatrix[i][2] == z) )
        {
            return i;
        }
    }
    return 0;
}


}
