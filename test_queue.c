#include "packet.h"
#include "helpers.h"
#include <stdio.h>

int main(void)
{

    Queue *q = create_queue(4);
    if (!q)
    {
        printf("Failed to create queue\n");
        return 1;
    }

   
    uint8_t content1[] = "Hello";
    uint8_t content2[] = "World";
    uint8_t content3[] = "Succeeds";
    uint8_t content4[] = "Fails"; // queue full, should fail

    Packet *p1 = create_packet(0x0A000001, 0x0A000002, 64, content1, sizeof(content1));
    Packet *p2 = create_packet(0x0A000003, 0x0A000004, 64, content2, sizeof(content2));
    Packet *p3 = create_packet(0x0A000005, 0x0A000006, 64, content3, sizeof(content3));
    Packet *p4 = create_packet(0x0A000007, 0x0A000008, 64, content4, sizeof(content4));

    // enqueue packets
    printf("Enqueue p1, p2, p3\n");
    enqueue(q, p1);
    enqueue(q, p2);
    enqueue(q, p3);

    if (is_full_queue(q))
    {
        printf("Queue is full (expected)\n");
    }

    printf("Attempt enqueue p4 (should fail silently)\n");
    enqueue(q, p4);

    // dequeue and print packets
    printf("\nDequeue packets:\n");
    Packet *out;
    while ((out = dequeue(q)) != NULL)
    {
        print_packet(out);
        printf("-----------\n");
    }

    if (is_empty_queue(q))
    {
        printf("Queue is empty (expected)\n");
    }


    free_packet(p1);
    free_packet(p2);
    free_packet(p3);
    free_packet(p4);


    free_queue(q);

    return 0;
}
