# Network Router Simulator

## Overview

This application simulates routers that are connected. You can send a packet to a router that will get routed by each router to the next router.

The network topology is defined in `inputOutput/routes.txt`.
- The first line are the ID's of the routers, comma separated
- In the next lines the routing tables of the routers are defined. The following format is expected:
  ```
  router_id, ip address, mask, next hop router id
  ```

A visualisation of the current content of `routes.txt`'s topology is in `topology_diagram.txt`.

`inputOutput/packets.txt` shows through which routers a packet goes through.

When `main` is executed, the topology is loaded and a packet is created and sent to the first router. Then interactive mode starts where the user can create packets from the terminal. The user puts in source ip address, destination ip address, content and the router id to which the packet initially will be sent to.

---

## Architecture

### helpers.h, helpers.c
- Defines and implements queue, using a circular queue implementation.
- IP utility functions to print ip addresses, convert to integers and strings.

### packet.h, packet.c
- A packet is represented as a struct that has a source and destination address, a ttl field, and content.
- An ip address is represented as a 32 bit unsigned integer.
- Functions are implemented to create and free packets.
- There are serialize and deserialize functions to send a packet over a network, but these are not used.

### routing.h, routing.c
These files are responsible for the routing logic.

**Data Structures:**
- Three structs are defined: `RouteEntry`, `RoutingTable`, and `Router`
- A router has a queue where the packets will be stored, an ID and a Routing Table.
- A routing table is a list of routeEntries.
- A route Entry has a destination ip, a mask and a pointer to a router that a packet will need to be forwarded to if the packet's ip matches the destination ip with the mask.

**Functions:**
- Functions to create, free, initialize a router
- Functions to add a route to a router, send a packet to a router
- The function `process_packet` will dequeue a packet from a router, find the router to which the packet needs to be forwarded to (using longest prefix match) and send it to the router
- **Important:** Packets are freed eventually when a packet gets dropped or arrived at its destination
- `process_packets_parallel` is a function to continuously process packets. This function will be called by the `start_routing_parallel` function in `routing_parallel.c` file that creates and runs the function in a thread

### routing_parallel.h, routing_parallel.c
- Contains the `start_routing_parallel` function that creates threads for parallel packet processing
- Each router runs in its own thread, continuously processing packets from its queue

### read_routers_from_file.h, read_routers_from_file.c
- The routers and routing tables are defined in `routes.txt`
- `read_routers_from_file` will create the routers, setup the routing tables and return a `RouterInfo` struct which holds the number of routers and the routers themselves

### main.c
- Creates one packet and sends it to router with id 1
- Then enters interactive mode where the user can create and send packets through the terminal

---

## How to Execute

### Prerequisites
- C compiler (I used Clang)
- POSIX threads library

### Building and Running

1. Navigate to the `src/` directory:
   ```bash
   cd src
   ```

2. Compile the project:
   ```bash
   make main
   ```

3. Run the simulator:
   ```bash
   ./main
   ```

4. Follow the interactive prompts to create and send packets

### Cleaning Build Files
```bash
make clean
```

