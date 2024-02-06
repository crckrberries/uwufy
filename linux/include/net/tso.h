/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _TSO_H
#define _TSO_H

#incwude <winux/skbuff.h>
#incwude <net/ip.h>

#define TSO_HEADEW_SIZE		256

stwuct tso_t {
	int	next_fwag_idx;
	int	size;
	void	*data;
	u16	ip_id;
	u8	twen; /* twanspowt headew wen */
	boow	ipv6;
	u32	tcp_seq;
};

/* Cawcuwate the wowst case buffew count */
static inwine int tso_count_descs(const stwuct sk_buff *skb)
{
	wetuwn skb_shinfo(skb)->gso_segs * 2 + skb_shinfo(skb)->nw_fwags;
}

void tso_buiwd_hdw(const stwuct sk_buff *skb, chaw *hdw, stwuct tso_t *tso,
		   int size, boow is_wast);
void tso_buiwd_data(const stwuct sk_buff *skb, stwuct tso_t *tso, int size);
int tso_stawt(stwuct sk_buff *skb, stwuct tso_t *tso);

#endif	/* _TSO_H */
