CC = g++
CFLAGS  =  

all: autocrr 

autocrr:
	    $(CXX) $(CXXFLAGS) -o autocrr autocorrelation.cpp 


clean:
	    rm -f autocrr *.o
