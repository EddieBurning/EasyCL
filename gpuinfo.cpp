// Copyright Hugh Perkins 2013 hughperkins at gmail
//
// This Source Code Form is subject to the terms of the Mozilla Public License, 
// v. 2.0. If a copy of the MPL was not distributed with this file, You can 
// obtain one at http://mozilla.org/MPL/2.0/.

#include <iostream>
#include <cassert>
#include <cstdlib>
using namespace std;

#include "clew.h"

#include "deviceinfo_helper.h"

int main( int argc, char *argv[] ) {
    bool clpresent = 0 == clewInit();
    if( !clpresent ) {
        cout << "opencl library not found." << endl;
        return -1;
    }

    cl_int error = 0;   // Used to handle error codes
    cl_platform_id platform_ids[10];
    cl_context context;
    cl_command_queue queue;
    cl_device_id device;

    // Platform
    cl_uint num_platforms;
    error = clGetPlatformIDs(10, platform_ids, &num_platforms);
    cout << "num platforms: " << num_platforms << endl;
    assert (num_platforms == 1);
    assert (error == CL_SUCCESS);
    cout << endl;

    for( int i = 0; i < num_platforms; i++ ) {
        cout << "platform " << i << ":" << endl;
        cl_platform_id platform_id = platform_ids[i];
        // Device
        cl_uint num_devices;
        error = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL, 1, &device, &num_devices);
        if (error != CL_SUCCESS) {
           cout << "Error getting device ids: " << error << endl;
           exit(error);
        }
        cout << "num devices: " << num_devices << endl;
        cl_device_id *device_ids = new cl_device_id[num_devices];
        error = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL, num_devices, device_ids, &num_devices);
        if (error != CL_SUCCESS) {
           cout << "Error getting device ids: " << error << endl;
           exit(error);
        }
        for( int i = 0; i < num_devices; i++ ) {
            device = device_ids[i];
            cout << "device " << i << " id " << device << endl;
            printDeviceInfo( "device type", device, CL_DEVICE_TYPE );
            printDeviceInfoMB( "global memory size", device, CL_DEVICE_GLOBAL_MEM_SIZE );
            printDeviceInfoKB( "local memory size", device, CL_DEVICE_LOCAL_MEM_SIZE );
            printDeviceInfoKB( "global cache size", device, CL_DEVICE_GLOBAL_MEM_CACHE_SIZE );
            printDeviceInfo( "global cacheline size", device, CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE );
            printDeviceInfo( "max compute units", device, CL_DEVICE_MAX_COMPUTE_UNITS );
            printDeviceInfo( "max workgroup size", device, CL_DEVICE_MAX_WORK_GROUP_SIZE );
            printDeviceInfo( "max workitem dimensions", device, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS );
            printDeviceInfoArray( "max workitem sizes", device, CL_DEVICE_MAX_WORK_ITEM_SIZES, 3 );
            printDeviceInfoString( "device name", device, CL_DEVICE_NAME );
            printDeviceInfoString( "opencl c version", device, CL_DEVICE_OPENCL_C_VERSION );
            printDeviceInfoString( "opencl device version", device, CL_DEVICE_VERSION );
            printDeviceInfo( "frequency MHz", device, CL_DEVICE_MAX_CLOCK_FREQUENCY );
            cout << endl;
        }
        cout << endl;
    }
    return 0;
}

