test_routing: routing.c helpers.c packet.c test_routing.c
	clang routing.c helpers.c packet.c test_routing.c -o test_routing

clean:
	rm -f test_routing
