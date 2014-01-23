#ifndef KMEANS_HPP
#define KMEANS_HPP

class Cluster;
class Object;

#include <vector>

using namespace std;

//======================================================================================================================
class KMeans {
public:
    ~KMeans();
    
    void Start();
    
    double Fitness();
    
private:
    vector<Object*> m_objects;
    vector<Cluster*> m_clusters;
    
    /* Pobiera obiekty z pliku. */
    void GetObjects();
    
    void MakeEmptyClustersWithRandomMeans();
    
    void AssignObjectsToClusters();
    
    /* Zwraca false, kiedy środki klastrów nie uległy zmianie. */
    bool UpdateClusterCenters();
    
    void SendResultToFile();
};
//======================================================================================================================

#endif
