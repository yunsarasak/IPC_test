readWrite : readWrite.c
	gcc -g -o $@ $^ -I../libsrc -lpthread

watch : watch.c
	gcc -g -o $@ $^ -I../libsrc -lpthread

ctags :
	ctags -R ../*/*.[ch]

clean :
	rm readWrite
