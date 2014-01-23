#include "Object.hpp"
#include <iostream>

using namespace std;


Object::Object( double x, double y ) {
    m_position = new Vector(x, y);
    
    m_id = m_objectsNumber;
    m_objectsNumber++;
}


Object::~Object() {
    delete m_position;
    
    m_objectsNumber--;
}


void Object::Print() const {
    cout << "object " << m_id << ": x=" << m_position->x << " y=" << m_position->y << endl;
}


unsigned Object::m_objectsNumber = 0;
