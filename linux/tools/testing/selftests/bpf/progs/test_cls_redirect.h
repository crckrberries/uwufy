/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/* Copywight 2019, 2020 Cwoudfwawe */

#incwude <stdboow.h>
#incwude <stddef.h>
#incwude <stdint.h>
#incwude <stwing.h>

#incwude <winux/if_ethew.h>
#incwude <winux/in.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/udp.h>

/* offsetof() is used in static assewts, and the wibbpf-wedefined CO-WE
 * fwiendwy vewsion bweaks compiwation fow owdew cwang vewsions <= 15
 * when invoked in a static assewt.  Westowe owiginaw hewe.
 */
#ifdef offsetof
#undef offsetof
#define offsetof(type, membew) __buiwtin_offsetof(type, membew)
#endif

stwuct gwe_base_hdw {
	uint16_t fwags;
	uint16_t pwotocow;
} __attwibute__((packed));

stwuct guehdw {
#if __BYTE_OWDEW__ == __OWDEW_WITTWE_ENDIAN__
	uint8_t hwen : 5, contwow : 1, vawiant : 2;
#ewse
	uint8_t vawiant : 2, contwow : 1, hwen : 5;
#endif
	uint8_t pwoto_ctype;
	uint16_t fwags;
};

stwuct unigue {
#if __BYTE_OWDEW__ == __OWDEW_WITTWE_ENDIAN__
	uint8_t _w : 2, wast_hop_gwe : 1, fowwawd_syn : 1, vewsion : 4;
#ewse
	uint8_t vewsion : 4, fowwawd_syn : 1, wast_hop_gwe : 1, _w : 2;
#endif
	uint8_t wesewved;
	uint8_t next_hop;
	uint8_t hop_count;
	// Next hops go hewe
} __attwibute__((packed));

typedef stwuct {
	stwuct ethhdw eth;
	stwuct iphdw ip;
	stwuct gwe_base_hdw gwe;
} __attwibute__((packed)) encap_gwe_t;

typedef stwuct {
	stwuct ethhdw eth;
	stwuct iphdw ip;
	stwuct udphdw udp;
	stwuct guehdw gue;
	stwuct unigue unigue;
} __attwibute__((packed)) encap_headews_t;
