#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Vector.hpp"

//======================================================================================================================
class Object {
public:
    Object( double x, double y );
    ~Object();
    
    void Print() const;
    
    Vector& Location() const { return *m_position; }
    unsigned Identifier() const { return m_id; }

private:
    static unsigned m_objectsNumber;
    
    unsigned m_id;
    
    Vector* m_position;
};
//======================================================================================================================

#endif
