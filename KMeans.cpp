#include "Cluster.hpp"
#include "KMeans.hpp"
#include "Object.hpp"
#include "Timer.hpp"
#include "Utility.hpp"
#include <fstream>
#include <iostream>


KMeans::~KMeans() {
    for ( vector<Cluster*>::iterator it = m_clusters.begin(); it != m_clusters.end(); ++it ) {
        delete *it;
    }
    
    for ( vector<Object*>::iterator it = m_objects.begin(); it != m_objects.end(); ++it ) {
        delete *it;
    }
}


void KMeans::Start() {
    GetObjects();
    
    MakeEmptyClustersWithRandomMeans();
    
    Timer timer;
    timer.Start();
    
    do {
        AssignObjectsToClusters();
    } while ( UpdateClusterCenters() );
    
    timer.Pause();
    
    cout << "Program grouped the objects in " << timer.GetTime() << " s\n";
    cout << "Fitness: " << Fitness() << endl;
    
    SendResultToFile();
}


double KMeans::Fitness() {
    double distancesSum = 0.0d;
    
    for ( vector<Cluster*>::iterator itCluster = m_clusters.begin(); itCluster != m_clusters.end(); ++itCluster ) {
        for ( vector<Object*>::iterator itClusterObject = (*itCluster)->ClusterObjects().begin();
              itClusterObject != (*itCluster)->ClusterObjects().end(); ++itClusterObject ) {
            distancesSum += Vector::Distance( (*itCluster)->Center(), (*itClusterObject)->Location() );
        }
    }
    
    return distancesSum;
}


void KMeans::GetObjects() {
    ifstream in( "objects.txt" );
    double x, y;
    
    while ( in >> x >> y ) {
        Object* object = new Object( x, y );
        m_objects.push_back(object);
    }
    
    if ( Utility::debug ) {/////////////////////////////////////////////////////////////////////////////////////////////
        cout << "Number of created objects: " << m_objects.size() << endl;
        for ( vector<Object*>::iterator it = m_objects.begin(); it != m_objects.end(); ++it ) {
            (*it)->Print();
        }
    }///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}


void KMeans::MakeEmptyClustersWithRandomMeans() {
    vector<int> selectedObjectsNumbers;
    int randomObjectNumber;
    bool uniqueNumber;
    
    for ( int i = 0 ; i < Utility::k; ++i ) {
        uniqueNumber = false;
        
        // Szukamy losowego środka wśród dostępnych obiektów. Staramy się nie wybrać ponownie tego samego obiektu.
        while ( !uniqueNumber ) {
            randomObjectNumber = Utility::RandomNumber( 0, ( m_objects.size() - 1 ) );
            
            uniqueNumber = true;
            
            for ( vector<int>::iterator it = selectedObjectsNumbers.begin();
                  it != selectedObjectsNumbers.end(); ++it) {
                if ( *it == randomObjectNumber ) {
                    uniqueNumber = false;
                    break;
                }
            }
        }
        
        // Tworzymy pusty klaster z wylosowanym środkiem.
        Cluster* cluster = new Cluster( m_objects[randomObjectNumber]->Location() );
        m_clusters.push_back( cluster );
        
        selectedObjectsNumbers.push_back( randomObjectNumber );
        
        if ( Utility::debug ) {/////////////////////////////////////////////////////////////////////////////////////////
            cout << "new cluster: id=" << cluster->Identifier() << " mean.x="
                 << cluster->Center().x << " mean.y = " << cluster->Center().y << " (by object "
                 << randomObjectNumber << ")\n";
        }///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    }
}


void KMeans::AssignObjectsToClusters() {
    // Czyszczenie klastrów.
    for ( vector<Cluster*>::iterator it = m_clusters.begin(); it != m_clusters.end(); ++it ) {
        (*it)->Clear();
    }
    
    double distance, bestDistance;
    Cluster* closestCluster;
    
    for ( vector<Object*>::iterator itObject = m_objects.begin(); itObject != m_objects.end(); ++itObject ) {
        bestDistance = Utility::infinity;
        closestCluster = nullptr;
        
        for ( vector<Cluster*>::iterator itCluster = m_clusters.begin(); itCluster != m_clusters.end(); ++itCluster ) {
            if ( ( distance = Vector::Distance( (*itObject)->Location(), (*itCluster)->Center() ) ) < bestDistance ) {
                closestCluster = *itCluster;
                bestDistance = distance;
            }
        }
        
        if ( closestCluster != nullptr ) {
            closestCluster->PutObject(*itObject);
        }
    }
    
    if ( Utility::debug ) {/////////////////////////////////////////////////////////////////////////////////////////////
        for ( vector<Cluster*>::iterator it = m_clusters.begin(); it != m_clusters.end(); ++it ) {
            (*it)->Print();
        }
    }///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}


bool KMeans::UpdateClusterCenters() {
    bool isAnyUpdate = false;
    
    for ( vector<Cluster*>::iterator it = m_clusters.begin(); it != m_clusters.end(); ++it ) {
        if ( (*it)->UpdateCenter() ) {
            isAnyUpdate = true;
        }
    }
    
    return isAnyUpdate;
}


void KMeans::SendResultToFile() {
    ofstream outClusteredObjects( "clustered_objects.txt" );
    ofstream outCenters( "centers.txt" );
    
    for ( vector<Cluster*>::iterator itCluster = m_clusters.begin(); itCluster != m_clusters.end(); ++itCluster ) {
        for ( vector<Object*>::iterator itClusterObject = (*itCluster)->ClusterObjects().begin();
              itClusterObject != (*itCluster)->ClusterObjects().end(); ++itClusterObject ) {
            outClusteredObjects << (*itCluster)->Identifier() << " " << (*itClusterObject)->Location().x
                                << " " << (*itClusterObject)->Location().y << endl;
        }
        
        outCenters << (*itCluster)->Identifier() << " " << (*itCluster)->Center().x << " "
                   << (*itCluster)->Center().y << endl;
    }
}
