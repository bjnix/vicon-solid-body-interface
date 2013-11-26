./lib/libVII.so:./src/ViconSegment.cpp ./src/ViconInputClient.cpp
	g++ -Wall -g -shared -fPIC -O2 -I./include -o ~bjnix/svn/fitashape/lib/libVII.so ./src/ViconSegment.cpp ./src/ViconInputClient.cpp
local:./src/ViconSegment.cpp ./src/ViconInputClient.cpp
	g++ -Wall -g -shared -fPIC -O2 -I./include -o ./lib/libVII.so ./src/ViconSegment.cpp ./src/ViconInputClient.cpp
a.out:./src/test.cpp
	g++ ./src/test.cpp -g -L./lib -Wl,-rpath,./lib -lVII -L../vicon-libs -Wl,-rpath,../vicon-libs -lViconDataStreamSDK_CPP -I./include
.PHONY: clean
clean:
	rm -f ~bjnix/svn/fitashape/lib/libVII.so ./lib/libVII.so a.out *.o
