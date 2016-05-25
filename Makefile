.phony: clean

BIN=bin
INC=inc
SRC=src
APP=wlan
LOG=log
OBJECTS=$(BIN)/wlan.o $(BIN)/Generator.o $(BIN)/Simula.o $(BIN)/Monitor.o $(BIN)/Medium.o $(BIN)/Stacja.o $(BIN)/Pakiet.o

CXX=g++
CFLAGS=-Wall -O3

all: $(BIN)/$(APP)

$(BIN)/$(APP): $(OBJECTS) 
	$(CXX) $(CLFAGS) $^ -o $@

$(BIN)/%.o: $(SRC)/%.cpp
	$(CXX) $(CFLAGS) -c -I$(INC) $< -o $@

clean:
	-rm -rf $(BIN)/*.o
	-rm -rf $(LOG)/*.txt
	-rm -rf $(BIN)/$(APP)
