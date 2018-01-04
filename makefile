PROJECT = BioInformatics
CPPSRC = $(wildcard *.cpp)
CCSRC = $(wildcard *.cc)
#BioSequence.cpp FastADocument.cpp HashTableCalculationMethod.cpp HashTable.cpp PAF.cpp QueryMapper.cpp Stopwatch.cpp
HEADERS = $(wildcard *.h) #BioSequence.h FastADocument.h HashTableCalculationMethod.h HashTable.h PAF.h QueryMapper.h Stopwatch.h welcome.h

CC = g++
CXXFLAGS = -std=c++11 -Wall -g
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

print:
	@echo $(OBJECTS)
	@echo $(HEADERS)
	@echo $(CCSRC)
	@echo $(CPPSRC)

clean:
	-echo "TODO"
