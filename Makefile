test_routing: routing.c helpers.c packet.c test_routing.c
	clang routing.c helpers.c packet.c test_routing.c -o test_routing

test_routing_new: routing.c helpers.c packet.c test_routing_new.c
	clang routing.c helpers.c packet.c test_routing_new.c -o test_routing_new

test_routing_parallel: routing.c helpers.c packet.c test_routing_parallel.c
	clang routing.c helpers.c packet.c test_routing_parallel.c -o test_routing_parallel -lpthread

clean:
	rm -f test_routing test_routing_new