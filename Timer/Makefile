all:
	libtool --mode=compile g++ -std=c++0x -c Timer.cpp
	libtool --mode=link g++ -o libTimer.la Timer.lo -rpath /usr/lib64
#	libtool --mode=install cp libTimer.la $(PREFIX)/lib/libTimer.la

clean: 
	rm -rfv .libs *.{l,}{o,a} test
