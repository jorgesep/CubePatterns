/*
 * Cube.h
 *
 *  Created on: May 30, 2012
 *      Author: jsepulve
 */

#ifndef POINT_H_
#define POINT_H_

#include <vector>
#include <math.h>
#include <iostream>

/**
 * Defines a basic cube vertex unit.
 */

namespace patterns {


class Point 
{
public:
    /// Default constructor.
    Point() : m_id(0), m_X(0), m_Y(0), m_Z(0), m_T(1), m_point(0) { };

    /** 
     * Parametric constructor
     * Initializes x,y,z vertex position, calculates vertex number.
     */
    Point(int , int , int , int );

    /** 
     * Parametric constructor
     * Initializes x,y,z vertex position, calculates vertex number.
     */
    Point(int , int , int );
    /**
     * Initializes point vertex number, determines x,y,z position
     */
    Point(int p): m_T(1) { this->PointToCoordinates(p); };

    virtual ~Point() {};

    /// Copy constructor
    Point(const Point & point) { *this = point; };

    /// Assignment operator
    Point &operator =(const Point &point) {
        if (*this != point)
        {
            m_id= point.m_id;
            m_X = point.m_X;
            m_Y = point.m_Y;
            m_Z = point.m_Z;
            m_point = point.m_point;
            m_T = point.m_T;
        }
        return *this;
    };

    /// Equals operator
    bool operator ==(const Point &point) const {
        return ((m_id == point.m_id) &&
                (m_X == point.m_X) &&
                (m_Y == point.m_Y) &&
                (m_Z == point.m_Z) &&
                (m_T == point.m_T) &&
                (m_point == point.m_point));
    };

    /// Not Equals operator
    bool operator !=(const Point &point) const {
        return ((m_id    != point.m_id) ||
                (m_X     != point.m_X ) ||
                (m_Y     != point.m_Y ) ||
                (m_Z     != point.m_Z ) ||
                (m_T     != point.m_T ) ||
                (m_point != point.m_point));
    };

    /// X rotate operator
    Point &operator >>(const int step) {
        this->rotX(step);
        return *this;
    };

    /// Z rotate operator
    Point &operator <<(const int step) {
        this->rotZ(step);
        return *this;
    };

    /// Y rotate operator
    Point &operator ^(const int step) {
        this->rotY(step);
        return *this;
    };


    Point &operator +(const Point &point) {
        m_X += point.m_X;
        m_Y += point.m_Y;
        m_Z += point.m_Z;
        m_point = this->CoordinatesToPoint();
        return *this;
    };

    Point &operator -(const Point &point) {
        m_X -= point.m_X;
        m_Y -= point.m_Y;
        m_Z -= point.m_Z;
        m_point = this->CoordinatesToPoint();
        return *this;
    };

    /**
     * Rotates set new vertex position.
     * @param x position
     * @param y position
     * @param z position
     */
    void setPosition(int, int, int);

    /**
     * Sets up new vertex position
     * @param point position
     */ 
    void setPosition(int);

    /**
     * Rotate X axis in steps of 90 degrees.
     */
    int rotX(int);

    /**
     * Rotate Y axis in steps of 90 degrees.
     */
    int rotY(int step) { return this->rotate(1,step); };

    /**
     * Rotate Z axis in steps of 90 degrees.
     */
    int rotZ(int step) { return this->rotate(2,step); };

    /**
     * Returns vertex number.
     */
    int getPoint() { return m_point; }

    int getX() { return m_X; };
    int getY() { return m_Y; };
    int getZ() { return m_Z; };
    int getID() { return m_id; };

    void setX(int _x) { m_X = _x; };
    void setY(int _y) { m_Y = _y; };
    void setZ(int _z) { m_Z = _z; };

private:
    int rotate(int, int);
    int CoordinatesToPoint();
    void PointToCoordinates(int);
    int coordinatesToID(int, int, int);

    /**
     * Check 90 degrees step be into 0..3.
     */
    int getSteps(int);

    int m_id;
    int m_X;
    int m_Y;
    int m_Z;
    int m_T;
    int m_point;

    static const int TOTAL_POINTS;
    /**
     * Matrix to determine vertex number
     */ 
    static const int CoordinatesToPointConversionMatrix [];

    /**
     * Matrix to return x,y,z according vertex number.
     */
    static const int PointToCoordinatesConversionMatrix [][3];

    /**
     *
     */
    static const int RotationMatrix_X[4][4][4];
    static const int RotationMatrix_Y[4][4][4];
    static const int RotationMatrix_Z[4][4][4];
};

}

#endif /* POINT_H_ */
