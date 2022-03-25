CPP_FILES       := $(wildcard src/source/*.cpp) $(wildcard src/*.cpp)
RC_FILES        := $(wildcard res/*.rc)
O_FILES         := $(subst .cpp,.o,$(CPP_FILES)) $(subst .rc,.o,$(RC_FILES))
COMPILED_FLAGS  := -pedantic -W -Wall -O3
LINKED_FLAGS	:= -s

INCLUDE_DIRECTORIES		:= -Iinclude 
LIB_DIRECTORIES			:= -Llib
LIB_FILES				:= -lopenal32 sfml-audio-2.dll sfml-graphics-2.dll sfml-network-2.dll sfml-system-2.dll sfml-window-2.dll

app: $(O_FILES)
	g++ $^ -o $@ $(LIB_DIRECTORIES) $(LIB_FILES) $(LINKED_FLAGS)

%.o: %.cpp
	g++ -c $^ -o $@ $(INCLUDE_DIRECTORIES) $(COMPILED_FLAGS)

%.o: %.rc
	windres $^ -o $@ $(INCLUDE_DIRECTORIES)

clean:
	del *.o *.exe