#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <net/ethernet.h>
#include <numa.h>

#include "pfring.h"
#include "pfring_zc.h"


int main(int argc, char* argv[]) {
  pfring_zc_cluster *cluster;
  int cpu_id;
  static u_int32_t buffer_len = ETHERMTU + 100;
  static u_int32_t queue_len = 1000;
  char *source_dev, *dest_dev;
  pfring_zc_queue *recv_queue, *send_queue;
  pfring_zc_pkt_buff *recv_buff;

  if (argc != 4) {
    printf("USAGE: %s <src> <dest> <cpu_id>\n", argv[0]);
    exit(-1);
  }

  // get device names
  source_dev = argv[1];
  dest_dev = argv[2];

  // get CPU ID
  cpu_id = atoi(argv[3]);

  // create cluster
  cluster = pfring_zc_create_cluster(cpu_id, buffer_len,
				     0, queue_len, numa_node_of_cpu(cpu_id), NULL);
  if (cluster == NULL) {
    perror("pfring_zc_create_cluster failed");
    exit(-1);
  }
  recv_buff = pfring_zc_get_packet_handle(cluster);

  // open devices
  recv_queue = pfring_zc_open_device(cluster, source_dev, rx_only, 0);
  if (recv_queue == NULL) {
    perror("pfring_zc_open_device");
    fprintf(stderr, "error opening device %s for receive\n", source_dev);
    exit(-1);
  }
  send_queue = pfring_zc_open_device(cluster, dest_dev, tx_only, 0);
  if (send_queue == NULL) {
    perror("pfring_zc_open_device");
    fprintf(stderr, "error opening device %s for transmit\n", dest_dev);
    exit(-1);
  }

  // forward traffic packet-by-packet
  while (1) {
    static u_int8_t wait_for_packet = 1;

    // receive a packet
    if (pfring_zc_recv_pkt(recv_queue, &recv_buff, wait_for_packet) < 0) {
      perror("error receiving packet");
      exit(-1);
    }

    char new[6];
    memcpy(new,pfring_zc_pkt_buff_data(recv_buff, recv_queue),5);
    printf("packet length %d\n", recv_buff->len);
    printf("data: %s\n",new);

  }

}
