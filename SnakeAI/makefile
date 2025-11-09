CXX = g++
LDFLAGS = -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
INCLDFLAGS = 
DEBUGFLAGS = -g 
MEMORYFLAGS = -O1 -fsanitize=address,undefined -fno-omit-frame-pointer
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
