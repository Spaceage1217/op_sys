target1=threadPartA
target2=threadPartB
objects=$(target1).o $(target2).o
cc=gcc
cflags=-Wall -Werror -g
ldopts=-pthread -lm
.PHONY: clean test

exec: $(target1) $(target2)
	./$<
	./$(word 2,$^)

test: exec clean

all: $(objects)

$(target1): $(objects)
	$(cc) $(target1).o -o $@ $(ldopts)

$(target2): $(objects)
	$(cc) $(target2).o -o $@ $(ldopts)

$(objects): %.o: %.c
	$(cc) -c $(cflags) $< -o $@

clean:
	rm -f $(target1) $(target2) $(objects)
