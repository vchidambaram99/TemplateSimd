.PHONY: clean directories
source = $(shell find . -name *.cpp)
objects = $(patsubst ./src/%.cpp,./build/%.o, $(source))
depends = $(patsubst ./src/%.cpp,./build/%.d, $(source))
compile = g++ -Wall -O0 -o $@ -march=native
buildFolders = $(sort $(dir $(objects)))

executable: $(objects) makefile
	$(compile) $(objects)

./build/%.o:./src/%.cpp makefile | $(buildFolders)
	$(compile) -c $< -MMD -MP

$(buildFolders):
	mkdir -p $(buildFolders)

clean:
	rm -rf build
	rm -f executable

ifneq ($(MAKECMDGOALS),clean)
-include $(depends)
endif
