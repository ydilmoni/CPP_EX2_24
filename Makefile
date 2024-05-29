#Mail : yonidil1997@gmail.com
#ID : 316529445

#!make -f

CXX=g++
CXXFLAGS=-std=c++14 -Werror 
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99

SOURCES=Graph.cpp Algorithms.cpp TestCounter.cpp Test.cpp
OBJECTS=$(subst .cpp,.o,$(SOURCES))

demo:Algorithms.cpp Graph.cpp Demo.cpp
	$(CXX) $^ -o demo.exe
	./demo.exe


test: Algorithms.cpp Graph.cpp Test.cpp
	$(CXX) $^ -o test.exe
	./test.exe

testCounter: TestCounter.o Test.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o testCounter.exe
	./testCounter.exe

tidy:
	clang-tidy $(SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

valgrindTest: test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test.exe 2>&1 | { egrep "lost| at " || true; }

valgrindTestCounter: testCounter.exe
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./testCounter.exe 2>&1 | { egrep "lost| at " || true; }

%.o: %.cpp
	$(CXX) $(CXXFLAGS) --compile $< -o $@

clean:
	rm -f *.o *.exe 