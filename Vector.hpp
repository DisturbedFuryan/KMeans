#ifndef VECTOR_HPP
#define VECTOR_HPP

using namespace std;

//======================================================================================================================
class Vector {
public:
    double x, y;
    
    Vector( double xx, double yy ) : x( xx ), y( yy ) {}
    
    static double Distance( const Vector& vA, const Vector& vB );
};
//======================================================================================================================

#endif
