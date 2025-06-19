CXX = g++
LDFLAGS = -lSDL2main -lSDL2
INCLDFLAGS = 
DEBUGFLAGS = -g
CXXFLAGS = -Wall -std=c++17

SRCDIR = src
SRC = $(wildcard $(SRCDIR)/*.cpp)
APP = ./bin/app
OBJDIR = obj
OBJ = $(addprefix $(OBJDIR)/, $(notdir $(SRC:.cpp=.o)))

all: $(OBJ)
	$(CXX) -o $(APP) $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $(INCLDFLAGS) $< -o $@

run: 
	$(APP)

debug: 
	gdb $(APP)

clean:
	rm $(OBJDIR)/*.o
