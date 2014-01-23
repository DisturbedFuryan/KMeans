#include "Cluster.hpp"
#include "Object.hpp"
#include "Utility.hpp"
#include "Vector.hpp"
#include <iostream>


Cluster::Cluster( const Vector& initialMean ) {
    m_mean = new Vector( initialMean.x, initialMean.y );
    
    m_id = m_clustersNumber;
    m_clustersNumber++;
}


Cluster::~Cluster() {
    delete m_mean;
    
    m_clustersNumber--;
}


void Cluster::Clear() {
    m_objects.clear();
}


void Cluster::PutObject( Object* object ) {
    m_objects.push_back( object );
}


bool Cluster::UpdateCenter() {
    Vector sum( 0.0d, 0.0d );
    
    for ( vector<Object*>::iterator it = m_objects.begin(); it != m_objects.end(); ++it ) {
        sum.x += (*it)->Location().x;
        sum.y += (*it)->Location().y;
    }
    
    Vector newCenter( ( sum.x /= m_objects.size() ), ( sum.y /= m_objects.size() ) );
    
    if ( ( newCenter.x == m_mean->x ) && ( newCenter.y == m_mean->y ) ) {
        if ( Utility::debug ) {/////////////////////////////////////////////////////////////////////////////////////////
            cout << "Center of cluster " << m_id << " has not changed.\n";
        }///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        
        return false;
    }
    
    m_mean->x = newCenter.x;
    m_mean->y = newCenter.y;
    
    if ( Utility::debug ) {/////////////////////////////////////////////////////////////////////////////////////////////
        cout << "New center of cluster " << m_id << ": x=" << m_mean->x << " y=" << m_mean->y << endl;
    }///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    return true;
}


void Cluster::Print() {
    cout << "cluster " << m_id << ":\n";
    
    for ( vector<Object*>::iterator it = m_objects.begin(); it != m_objects.end(); ++it ) {
        cout << "    object " << (*it)->Identifier() << endl;
    }
}


unsigned Cluster::m_clustersNumber = 0;
