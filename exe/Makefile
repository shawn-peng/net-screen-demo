CC := arm-linux-gcc
CFLAGS += -g

%.o: %.c
	$(CC) -c $< $(CFLAGS)

scrntest: scrntest.o jpegtest.o libscreen2image.a
	$(CC) -o $@ $^ -L./ -ljpeg -lscreen2image $(CFLAGS)

install:
	cp scrntest ~/testandroidfs/system/bin/

clean:
	rm scrntest *.o -rf
