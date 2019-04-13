CXX=g++
EXE=dot_test
INCLUDE=-I ../src
BUILDARGS=-std=c++17 -Wall -g

all : $(EXE)

$(EXE) : 
	$(CXX) $(BUILDARGS) $(INCLUDE) -o $(EXE).exe 

runtests : dot_test
	./dot_test
