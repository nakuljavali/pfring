/*
 *
 * (C) 2005-14 - ntop.org
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesses General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 */


#ifndef _PFRING_UTILS_H_
#define _PFRING_UTILS_H_

#if 0
struct eth_hdr {
  unsigned char   h_dest[ETH_ALEN];       /* destination eth addr */
  unsigned char   h_source[ETH_ALEN];     /* source ether addr    */
  u_int16_t       h_proto;                /* packet type ID field */
};

/* defined in pf_ring.h */
struct eth_vlan_hdr {
  u_int16_t       h_vlan_id;              /* Tag Control Information (QoS, VLAN ID) */
  u_int16_t       h_proto;                /* packet type ID field */
};
#endif

#define __LITTLE_ENDIAN_BITFIELD /* FIX */
struct iphdr {
#if defined(__LITTLE_ENDIAN_BITFIELD)
  u_int8_t	ihl:4,
    version:4;
#elif defined (__BIG_ENDIAN_BITFIELD)
  u_int8_t	version:4,
    ihl:4;
#else
#error	"Please fix <asm/byteorder.h>"
#endif
  u_int8_t	tos;
  u_int16_t	tot_len;
  u_int16_t	id;
#define IP_CE		0x8000
#define IP_DF		0x4000
#define IP_MF		0x2000
#define IP_OFFSET	0x1FFF
  u_int16_t	frag_off;
  u_int8_t	ttl;
  u_int8_t	protocol;
  u_int16_t	check;
  u_int32_t	saddr;
  u_int32_t	daddr;
  /*The options start here. */
};

struct tcphdr {
  u_int16_t	source;
  u_int16_t	dest;
  u_int32_t	seq;
  u_int32_t	ack_seq;
#if defined(__LITTLE_ENDIAN_BITFIELD)
  u_int16_t	res1:4,
    doff:4,
    fin:1,
    syn:1,
    rst:1,
    psh:1,
    ack:1,
    urg:1,
    ece:1,
    cwr:1;
#elif defined(__BIG_ENDIAN_BITFIELD)
  u_int16_t	doff:4,
    res1:4,
    cwr:1,
    ece:1,
    urg:1,
    ack:1,
    psh:1,
    rst:1,
    syn:1,
    fin:1;
#else
#error	"Adjust your <asm/byteorder.h> defines"
#endif
  u_int16_t	window;
  u_int16_t	check;
  u_int16_t	urg_ptr;
};

struct udphdr {
  u_int16_t	source;
  u_int16_t	dest;
  u_int16_t	len;
  u_int16_t	check;
};

#define TH_FIN_MULTIPLIER	0x01
#define TH_SYN_MULTIPLIER	0x02
#define TH_RST_MULTIPLIER	0x04
#define TH_PUSH_MULTIPLIER	0x08
#define TH_ACK_MULTIPLIER	0x10
#define TH_URG_MULTIPLIER	0x20

struct ipv6hdr {
#if defined(__LITTLE_ENDIAN_BITFIELD)
  u_int8_t		priority:4,
		version:4;
#elif defined(__BIG_ENDIAN_BITFIELD)
  u_int8_t		version:4,
		priority:4;
#else
#endif
  u_int8_t		flow_lbl[3];

  u_int8_t	        payload_len;
  u_int8_t		nexthdr;
  u_int8_t		hop_limit;

  struct in6_addr saddr;
  struct in6_addr daddr;
};

struct ipv6_opt_hdr {
  u_int8_t		nexthdr;
  u_int8_t 		hdrlen;
	/* TLV encoded option data follows */
} __attribute__((packed));

#define NEXTHDR_HOP     	  0
#define NEXTHDR_TCP     	  6
#define NEXTHDR_UDP     	 17
#define NEXTHDR_IPV6    	 41
#define NEXTHDR_ROUTING 	 43
#define NEXTHDR_FRAGMENT	 44
#define NEXTHDR_ESP     	 50
#define NEXTHDR_AUTH    	 51
#define NEXTHDR_ICMP    	 58
#define NEXTHDR_NONE    	 59
#define NEXTHDR_DEST    	 60
#define NEXTHDR_MOBILITY	135

#endif /* _PFRING_UTILS_H_ */

