project=lab2
objects=$(project).o
cc=gcc
cflags=-Wall -Werror -g
.PHONY: clean test

exec: $(project)
	./$<

test: exec clean

all: $(objects)

$(project): $(project).o
	$(cc) -o $(project) $<

$(objects): %.o: %.c
	$(cc) -c $(cflags) $< -o $@

clean:
	rm -f $(project) $(objects) *.dat
