project=problem2
file1=pre
file2=sort
objects=$(project).o $(file1).o $(file2).o
cc=gcc
cflags=-Wall -Werror -g
.PHONY: clean test

exec: $(project) $(file1) $(file2)
	./$<

test: exec clean

all: $(objects)

$(project): $(project).o
	$(cc) -o $(project) $<

$(file1): $(file1).o
	$(cc) -o $(file1) $<

$(file2): $(file2).o
	$(cc) -o $(file2) $<

$(objects): %.o: %.c
	$(cc) -c $(cflags) $< -o $@

clean:
	rm -f $(project) $(file1) $(file2) $(objects)
