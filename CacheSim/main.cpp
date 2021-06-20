#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <sys/time.h>

#include "utils.h"
#include "crc_cache.h"

using namespace std;

#define ACCESS_NUM 100000000

int main(int argc, char* argv[])
{
    int access_num = 0;
    int miss_num = 0;
    int hit_num = 0;
    struct timeval start, end;

    CRC_CACHE * mycache;
    Addr_t addr;
    bool hit;

    //init
    mycache = new CRC_CACHE(1024 * 1024, 16, 1, 64, 0);
    addr = rand();

    //begin simulation
    gettimeofday(&start, NULL);
    while(true)
    {
        if (access_num % 2)
            addr = addr * (Addr_t)25214903917 + 11;
        hit = mycache->LookupAndFillCache(0, 0, addr, 1);
        access_num++;
        if(hit)
    	    hit_num++;
        else
    	    miss_num++;
        if (access_num == ACCESS_NUM)
            break;
    }
    gettimeofday(&end, NULL);
    double time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;

    //output
    mycache->PrintStats(cout);
    cout<<"access num: "<<access_num<<" hit num: "<<hit_num<<" miss num: "<<miss_num<<endl;
    cout << "Time: " << time << ", Throughput: " << (ACCESS_NUM / 1000000) / time << endl;

    return 0;
}
