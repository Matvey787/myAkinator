SANITIZER = -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr
DIFFERENT_FLAGS = -I include -D _DEBUG -lncurses -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wlarger-than=81920 -Wstack-usage=81920 -pie -fPIE -Werror=vla
OBJECTS = o_files/main.o o_files/splitOnStrs.o o_files/rFile.o o_files/createTree.o o_files/delTree.o o_files/printLeafDef.o o_files/runAkinator.o o_files/wrDotFile.o o_files/wrPngFile.o

all: init out

out: $(OBJECTS)
	g++ $(OBJECTS) -o out $(DEBUG_SET)  $(DIFFERENT_FLAGS) $(SANITIZER)

o_files/main.o: source/main.cpp
	g++ -c source/main.cpp -o o_files/main.o $(DEBUG_SET)  $(DIFFERENT_FLAGS) $(SANITIZER)

o_files/splitOnStrs.o: source/readFile/splitOnStrs.cpp
	g++ -c source/readFile/splitOnStrs.cpp -o o_files/splitOnStrs.o $(DEBUG_SET)  $(DIFFERENT_FLAGS) $(SANITIZER)

o_files/rFile.o: source/readFile/rFile.cpp
	g++ -c source/readFile/rFile.cpp -o o_files/rFile.o $(DEBUG_SET)  $(DIFFERENT_FLAGS) $(SANITIZER)

o_files/createTree.o: source/tree/createTree.cpp
	g++ -c source/tree/createTree.cpp -o o_files/createTree.o $(DEBUG_SET)  $(DIFFERENT_FLAGS) $(SANITIZER)

o_files/delTree.o: source/tree/delTree.cpp
	g++ -c source/tree/delTree.cpp -o o_files/delTree.o $(DEBUG_SET)  $(DIFFERENT_FLAGS) $(SANITIZER)

o_files/printLeafDef.o: source/tree/printLeafDef.cpp
	g++ -c source/tree/printLeafDef.cpp -o o_files/printLeafDef.o $(DEBUG_SET)  $(DIFFERENT_FLAGS) $(SANITIZER)

o_files/runAkinator.o: source/runAkinator.cpp
	g++ -c source/runAkinator.cpp -o o_files/runAkinator.o $(DEBUG_SET)  $(DIFFERENT_FLAGS) $(SANITIZER)

o_files/wrDotFile.o: source/graphDump/wrDotFile.cpp
	g++ -c source/graphDump/wrDotFile.cpp -o o_files/wrDotFile.o $(DEBUG_SET)  $(DIFFERENT_FLAGS) $(SANITIZER)

o_files/wrPngFile.o: source/graphDump/wrPngFile.cpp
	g++ -c source/graphDump/wrPngFile.cpp -o o_files/wrPngFile.o $(DEBUG_SET)  $(DIFFERENT_FLAGS) $(SANITIZER)

clean:
	rm -rf o_files/*.o out o_files

init:
	mkdir -p o_files