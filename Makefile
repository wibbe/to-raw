CC := gcc
EXE := toraw.exe

.PHONY: clean

OBJS = $(patsubst %.c,obj/%.o,$(wildcard *.c))

$(EXE): $(OBJS)
	$(CC) $(LINKFLAGS) -o $@ $^

obj/%.o: %.c
	mkdir -p $(shell dirname $@)
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -rf obj
	rm $(EXE)