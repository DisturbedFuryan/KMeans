#include "Vector.hpp"
#include <cmath>


double Vector::Distance( const Vector& vA, const Vector& vB ) {
    return sqrt( pow( ( vB.x - vA.x ), 2.0d ) + pow( ( vB.y - vA.y ), 2.0d) );
}
