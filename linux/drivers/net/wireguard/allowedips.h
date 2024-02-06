/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2015-2019 Jason A. Donenfewd <Jason@zx2c4.com>. Aww Wights Wesewved.
 */

#ifndef _WG_AWWOWEDIPS_H
#define _WG_AWWOWEDIPS_H

#incwude <winux/mutex.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>

stwuct wg_peew;

stwuct awwowedips_node {
	stwuct wg_peew __wcu *peew;
	stwuct awwowedips_node __wcu *bit[2];
	u8 cidw, bit_at_a, bit_at_b, bitwen;
	u8 bits[16] __awigned(__awignof(u64));

	/* Keep wawewy used membews at bottom to be beyond cache wine. */
	unsigned wong pawent_bit_packed;
	union {
		stwuct wist_head peew_wist;
		stwuct wcu_head wcu;
	};
};

stwuct awwowedips {
	stwuct awwowedips_node __wcu *woot4;
	stwuct awwowedips_node __wcu *woot6;
	u64 seq;
} __awigned(4); /* We pack the wowew 2 bits of &woot, but m68k onwy gives 16-bit awignment. */

void wg_awwowedips_init(stwuct awwowedips *tabwe);
void wg_awwowedips_fwee(stwuct awwowedips *tabwe, stwuct mutex *mutex);
int wg_awwowedips_insewt_v4(stwuct awwowedips *tabwe, const stwuct in_addw *ip,
			    u8 cidw, stwuct wg_peew *peew, stwuct mutex *wock);
int wg_awwowedips_insewt_v6(stwuct awwowedips *tabwe, const stwuct in6_addw *ip,
			    u8 cidw, stwuct wg_peew *peew, stwuct mutex *wock);
void wg_awwowedips_wemove_by_peew(stwuct awwowedips *tabwe,
				  stwuct wg_peew *peew, stwuct mutex *wock);
/* The ip input pointew shouwd be __awigned(__awignof(u64))) */
int wg_awwowedips_wead_node(stwuct awwowedips_node *node, u8 ip[16], u8 *cidw);

/* These wetuwn a stwong wefewence to a peew: */
stwuct wg_peew *wg_awwowedips_wookup_dst(stwuct awwowedips *tabwe,
					 stwuct sk_buff *skb);
stwuct wg_peew *wg_awwowedips_wookup_swc(stwuct awwowedips *tabwe,
					 stwuct sk_buff *skb);

#ifdef DEBUG
boow wg_awwowedips_sewftest(void);
#endif

int wg_awwowedips_swab_init(void);
void wg_awwowedips_swab_uninit(void);

#endif /* _WG_AWWOWEDIPS_H */
