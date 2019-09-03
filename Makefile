CFLAGS=-Wall -Wextra -Werror
LDFLAGS=-lm

build: boardslam

boardslam:
	${CC} ${CFLAGS} ${LDFLAGS} -o boardslam src/boardslam.c src/bin/boardslam.c

boardslam.cgi:
	${CC} ${CFLAGS} ${LDFLAGS} -o boardslam.cgi src/boardslam.c src/bin/cgi.c

clean:
	rm -f boardslam boardslam.cgi
