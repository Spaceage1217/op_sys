file1=pre
file2=sort
objects=$(file1).o $(file2).o
cc=gcc
cflags=-Wall -Werror -g
.PHONY: clean test

exec: $(file1) $(file2)
	./$<
	./$^

test: exec clean

all: $(objects)

$(file1): $(file1).o
	$(cc) -o $(file1) $<

$(file2): $(file2).o
	$(cc) -o $(file2) $<

$(objects): %.o: %.c
	$(cc) -c $(cflags) $< -o $@

clean:
	rm -f $(file1) $(file2) $(objects)
