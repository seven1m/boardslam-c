CFLAGS=-Wall -Wextra -Werror

build: boardslam

boardslam:
	${CC} -o boardslam src/boardslam.c src/bin/boardslam.c

boardslam.cgi:
	${CC} -o boardslam.cgi src/boardslam.c src/bin/cgi.c

clean:
	rm -f boardslam boardslam.cgi
