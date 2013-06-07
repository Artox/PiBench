CXX=g++
CXXFLAGS=-O2
LDFLAGS=-lexplain

all: ping pong

ping: net.o ping.o
	$(CXX) $(CXXFLAGS) -o $@ net.o ping.o $(LDFLAGS)

pong: net.o pong.o
	$(CXX) $(CXXFLAGS) -o $@ net.o pong.o $(LDFLAGS)

.o: %.cpp net.h
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -vf *.o ping pong
