CC = gcc -g

polygon_point_containment:
	${CC} polygon_point_containment.c -o app_polygon_point_containment

clean:
	rm -rf app*
