
CXX      = i686-w64-mingw32-g++
CXXFLAGS = -m32 -masm=intel -shared
SOURCES  = $(wildcard ./source/*.cpp) $(wildcard ./source/*/*.cpp) $(wildcard ./source/*/*/*.cpp)
LDLIBS   = -ld3dx9_43
OUTPUT   = gtasa-anticheat.asi

all:
	$(CXX) $(strip $(CXXFLAGS) $(EXTRA_CXXFLAGS)) $(SOURCES) $(LDLIBS) -o $(OUTPUT)
