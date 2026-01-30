.PHONY: std dbg
.PHONY: standard-build debug-build

SRC-DIRS  = Source/
SRC-FILES = $(foreach dir,$(SRC-DIRS),$(dir)*.c )

STD-MACROS = -DNDEBUG
STD-CFLAGS = -std=c23 -flto -O2 -IInclude -Wall
STD-LFLAGS = 

DBG-MACROS = -DDEBUG
DBG-CFLAGS = -std=c23 -Og -g -IInclude -fsanitize=address -fanalyzer -pedantic
DBG-CFLAGS += -Wall -Wextra -pedantic -fno-omit-frame-pointer $(STD-CFLAGS)
DBG-LFLAGS = -fsanitize=address $(STD-LFLAGS)

std: standard-build clean
dbg: debug-build clean

standard-build:
	@gcc $(STD-MACROS) $(STD-CFLAGS) -c $(SRC-FILES)
	@gcc *.o $(STD-LFLAGS) -o main
	@strip --strip-section-headers main

debug-build:
	@gcc $(DBG-MACROS) $(DBG-CFLAGS) -c $(SRC-FILES)
	@gcc *.o $(DBG-LFLAGS) -o main

clean:
	@rm *.o
