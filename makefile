PROJECT = BioInformatics
CPPSRC = $(wildcard *.cpp)
CCSRC = $(wildcard *.cc)
HEADERS = $(wildcard *.h)

CC = g++
CXXFLAGS = -std=c++11 -O2 -Wall -g
OBJECTS = $(CPPSRC:.cpp=.o) $(CCSRC:.cc=.o)

$(PROJECT): $(OBJECTS)
	$(CC) -o $(PROJECT) $(OBJECTS)

welcome.o: welcome.cc $(HEADERS)
BioSequence.o: BioSequence.cpp $(HEADERS)
FastADocument.o: FastADocument.cpp $(HEADERS)
HashTable.o: HashTable.cpp $(HEADERS)
HashTableCalculationMethod.o: HashTableCalculationMethod.cpp $(HEADERS)
PAF.o: PAF.cpp $(HEADERS)
QueryMapper.o: QueryMapper.cpp $(HEADERS)
Stopwatch.o: Stopwatch.cpp $(HEADERS)

clean:
	-echo "TODO"
