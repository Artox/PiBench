CXX=/usr/lib64/mpi/gcc/openmpi/bin/mpic++
CXXFLAGS=
OBJECTS=MPIApplication.o main.o

all: test

test: $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -vf $(OBJECTS) test
