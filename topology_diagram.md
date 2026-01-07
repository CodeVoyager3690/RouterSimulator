# Network Topology Diagram - routes2.txt

## Visual Representation

```
                    ┌─────────┐
                    │Router 1 │
                    │10.0.0.0 │
                    │192.168.0│
                    └────┬────┘
                         │
              ┌──────────┴──────────┐
              │                     │
         ┌────▼────┐           ┌────▼────┐
         │Router 2 │◄─────────►│Router 3 │
         │10.0.1.0 │           │10.0.2.0 │
         │172.16.0 │           │10.0.3.0 │
         │192.168.1│           │192.168.2│
         └────┬────┘           └────┬────┘
              │                     │
       ┌──────┼─────────────────────┼──────┐
       │      │                     │      │
  ┌────▼────┐ │                     │ ┌────▼────┐
  │Router 5 │ │                     │ │Router 6 │
  │172.16.x │ │                     │ │10.0.3.0 │
  │192.168.4│ │                     │ │172.16.10│
  └────┬────┘ │                     │ │100.50   │
       │      │                     │ └────┬────┘
       │      │    ┌────────────────┘      │
       │      │    │                       │
       │      │    │                  ┌────┴────┐
       │      └────┼─────────────────►│Router 4 │
       │           │                  │10.0.2.0 │
       │           │                  │10.0.4.0 │
       │           │                  │192.168.3│
       │           │                  └────┬────┘
       │           │                       │
       │           │                  ┌────▼────┐
       │           │                  │Router 7 │
       │           │                  │10.0.4.0 │
       │           │                  │172.16.20│
       │           │                  │192.168.5│
       │           │                  └────┬────┘
       │           │                       │
       └───────────┴───────────────────────┘
                   │
              ┌────▼────┐
              │Router 8 │
              │172.16.50│
              │192.168.6│
              └─────────┘
```

## Router Connections Matrix

| Router | Directly Connected To | Local Networks        |
|--------|----------------------|-----------------------|
| R1     | R2, R3               | 192.168.0.0/24       |
| R2     | R1, R3, R4, R5       | 192.168.1.0/24       |
| R3     | R1, R2, R4, R6       | 192.168.2.0/24       |
| R4     | R2, R3, R6, R7       | 192.168.3.0/24       |
| R5     | R2, R6, R8           | 192.168.4.0/24       |
| R6     | R3, R4, R7, R8       | 192.168.100.50/32    |
| R7     | R4, R6, R8           | 192.168.5.0/24       |
| R8     | R5, R6, R7           | 192.168.6.0/24       |

## Network Segments

### 10.0.x.0 Networks (Class A)
- 10.0.0.0/24: R1 → R2
- 10.0.1.0/24: R1 → R3, R2 → R3
- 10.0.2.0/24: R2 → R4, R3 → R4
- 10.0.3.0/24: R3 → R6, R4 → R6
- 10.0.4.0/24: R4 → R7, R6 → R7

### 172.16.x.0 Networks (Class B)
- 172.16.0.0/16: R1 → R2 → R5
- 172.16.10.0/24: R3 → R6, R5 → R6
- 172.16.20.0/24: R4 → R7, R6 → R7
- 172.16.50.0/24: R5 → R8, R6 → R8, R7 → R8

### 192.168.x.0 Networks (Class C - Local)
- Each router has its own local network (direct delivery)

## Topology Characteristics

- **Mesh Structure**: Multiple redundant paths between routers
- **Redundancy**: Most destinations reachable via multiple routes
- **Depth**: Up to 4 hops from edge to edge
- **Hub Routers**: R6 and R2 act as central hubs with most connections
- **Edge Routers**: R1 (entry), R8 (backbone exit)
- **Total Routers**: 8
- **Total Route Entries**: 32
