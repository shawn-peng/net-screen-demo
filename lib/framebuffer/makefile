a: main.c fb_draw.o
	gcc $^ -o $@

fb_draw.o: fb_draw.c fb_draw.h
	gcc -c $^

clean:
	rm -rf *.o a
