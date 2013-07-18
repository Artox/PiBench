CXX=g++
CXXFLAGS=-std=c++0x -O2
LDFLAGS=-L../Timer/.libs

all: ping pong

ping: net.o ping.o
	$(CXX) $(CXXFLAGS) -o $@ net.o ping.o $(LDFLAGS) -lTimer

pong: net.o pong.o
	$(CXX) $(CXXFLAGS) -o $@ net.o pong.o $(LDFLAGS)

.o: %.cpp net.h
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -vf *.o ping pong
