CXX = g++
CXXFLAGS = -std=c++11 -Wall -I./include -I/usr/local/include/opencv4
LDFLAGS = -L/usr/local/lib
LDLIBS = -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc

OPENCV_AVAILABLE = -DOPENCV_AVAILABLE

all: vcrypt

vcrypt: main.o encryption.o decryption.o utils.o
	$(CXX) $(CXXFLAGS) $(OPENCV_AVAILABLE) -o bin/$@ $^ $(LDFLAGS) $(LDLIBS)

main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) $(OPENCV_AVAILABLE) -c src/main.cpp -o main.o

encryption.o: src/encryption.cpp
	$(CXX) $(CXXFLAGS) $(OPENCV_AVAILABLE) -c src/encryption.cpp -o encryption.o

decryption.o: src/decryption.cpp
	$(CXX) $(CXXFLAGS) $(OPENCV_AVAILABLE) -c src/decryption.cpp -o decryption.o

utils.o: src/utils.cpp
	$(CXX) $(CXXFLAGS) $(OPENCV_AVAILABLE) -c src/utils.cpp -o utils.o

clean:
	rm -f *.o bin/vcrypt
