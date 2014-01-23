#include "Utility.hpp"
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;


const bool Utility::debug = false;
    
const int Utility::k = 3;

const double Utility::infinity = numeric_limits<double>::max();


int Utility::RandomNumber( const long min, const long max ) {
    static bool firstUse = true;
    
    if ( firstUse ) {
        srand( time( nullptr ) );
        firstUse = false;
    }
    
    return ( ( rand() % ( max - min + 1 ) ) + min );
}
