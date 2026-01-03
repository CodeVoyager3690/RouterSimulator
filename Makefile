test_routing: routing.c helpers.c packet.c test_routing.c
	clang routing.c helpers.c packet.c test_routing.c -o test_routing

test_routing_new: routing.c helpers.c packet.c test_routing_new.c
	clang routing.c helpers.c packet.c test_routing_new.c -o test_routing_new

test_routing_parallel: routing.c helpers.c packet.c test_routing_parallel.c
	clang routing.c helpers.c packet.c test_routing_parallel.c -o test_routing_parallel -lpthread

test_routing_routes: routing.c helpers.c packet.c test_routing_routes.c
	clang routing.c helpers.c packet.c test_routing_routes.c -o test_routing_routes

main: main.c routing.c helpers.c packet.c read_routers_from_file.c routing_parallel.c
	clang main.c routing.c helpers.c packet.c read_routers_from_file.c routing_parallel.c -o main -lpthread


clean:
	rm -f test_routing test_routing_new test_routing_parallel test_routing_routes