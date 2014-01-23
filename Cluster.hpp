#ifndef CLUSTER_HPP
#define CLUSTER_HPP

class Object;
class Vector;

#include <vector>

using namespace std;

//======================================================================================================================
class Cluster {
public:
    Cluster( const Vector& initialMean );
    ~Cluster();
    
    void Clear();
    
    void PutObject( Object* object );
    
    /* Zwraca false, jeśli środki nie zmieniły swojego położenia. */
    bool UpdateCenter();
    
    void Print();
    
    Vector& Center() const { return *m_mean; }
    vector<Object*>& ClusterObjects() { return m_objects; }
    unsigned Identifier() const { return m_id; }

private:
    static unsigned m_clustersNumber;
    
    unsigned m_id;
    
    vector<Object*> m_objects;
    
    Vector* m_mean;
};
//======================================================================================================================

#endif
