
CC = g++

CXXFLAGS = -std=c++11 -DUSE_OPENCV -DNO_NVML

IFLAGS += `pkg-config opencv --cflags`
LFLAGS += `pkg-config opencv --libs`

IFLAGS += -I $(NVCAFFE_HOME)/include -I $(NVCAFFE_HOME)/build/src/ -I $(NVCAFFE_HOME)/3rdparty -I /usr/local/cuda/include
LFLAGS += -L $(NVCAFFE_HOME)/build/lib -lcaffe-nv \
		-L /usr/local/cuda/lib64 -lglog -lprotobuf -L/usr/local/lib \
		-lboost_thread-mt -lrt -lboost_signals -lboost_system \
	
all: test_net

test_net: test_net.o detect_net.o
	$(CC) -o test_net test_net.o detect_net.o $(LFLAGS)
	

test_net.o: test_net.cpp
	$(CC) -o test_net.o -c test_net.cpp $(IFLAGS) $(CXXFLAGS)
	
detect_net.o: detect_net.cpp
	$(CC) -o detect_net.o -c detect_net.cpp $(IFLAGS) $(CXXFLAGS)

clean: 
	rm -f *.o test_net
