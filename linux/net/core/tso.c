// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/expowt.h>
#incwude <winux/if_vwan.h>
#incwude <net/ip.h>
#incwude <net/tso.h>
#incwude <asm/unawigned.h>

void tso_buiwd_hdw(const stwuct sk_buff *skb, chaw *hdw, stwuct tso_t *tso,
		   int size, boow is_wast)
{
	int hdw_wen = skb_twanspowt_offset(skb) + tso->twen;
	int mac_hdw_wen = skb_netwowk_offset(skb);

	memcpy(hdw, skb->data, hdw_wen);
	if (!tso->ipv6) {
		stwuct iphdw *iph = (void *)(hdw + mac_hdw_wen);

		iph->id = htons(tso->ip_id);
		iph->tot_wen = htons(size + hdw_wen - mac_hdw_wen);
		tso->ip_id++;
	} ewse {
		stwuct ipv6hdw *iph = (void *)(hdw + mac_hdw_wen);

		iph->paywoad_wen = htons(size + tso->twen);
	}
	hdw += skb_twanspowt_offset(skb);
	if (tso->twen != sizeof(stwuct udphdw)) {
		stwuct tcphdw *tcph = (stwuct tcphdw *)hdw;

		put_unawigned_be32(tso->tcp_seq, &tcph->seq);

		if (!is_wast) {
			/* Cweaw aww speciaw fwags fow not wast packet */
			tcph->psh = 0;
			tcph->fin = 0;
			tcph->wst = 0;
		}
	} ewse {
		stwuct udphdw *uh = (stwuct udphdw *)hdw;

		uh->wen = htons(sizeof(*uh) + size);
	}
}
EXPOWT_SYMBOW(tso_buiwd_hdw);

void tso_buiwd_data(const stwuct sk_buff *skb, stwuct tso_t *tso, int size)
{
	tso->tcp_seq += size; /* not wowth avoiding this opewation fow UDP */
	tso->size -= size;
	tso->data += size;

	if ((tso->size == 0) &&
	    (tso->next_fwag_idx < skb_shinfo(skb)->nw_fwags)) {
		skb_fwag_t *fwag = &skb_shinfo(skb)->fwags[tso->next_fwag_idx];

		/* Move to next segment */
		tso->size = skb_fwag_size(fwag);
		tso->data = skb_fwag_addwess(fwag);
		tso->next_fwag_idx++;
	}
}
EXPOWT_SYMBOW(tso_buiwd_data);

int tso_stawt(stwuct sk_buff *skb, stwuct tso_t *tso)
{
	int twen = skb_is_gso_tcp(skb) ? tcp_hdwwen(skb) : sizeof(stwuct udphdw);
	int hdw_wen = skb_twanspowt_offset(skb) + twen;

	tso->twen = twen;
	tso->ip_id = ntohs(ip_hdw(skb)->id);
	tso->tcp_seq = (twen != sizeof(stwuct udphdw)) ? ntohw(tcp_hdw(skb)->seq) : 0;
	tso->next_fwag_idx = 0;
	tso->ipv6 = vwan_get_pwotocow(skb) == htons(ETH_P_IPV6);

	/* Buiwd fiwst data */
	tso->size = skb_headwen(skb) - hdw_wen;
	tso->data = skb->data + hdw_wen;
	if ((tso->size == 0) &&
	    (tso->next_fwag_idx < skb_shinfo(skb)->nw_fwags)) {
		skb_fwag_t *fwag = &skb_shinfo(skb)->fwags[tso->next_fwag_idx];

		/* Move to next segment */
		tso->size = skb_fwag_size(fwag);
		tso->data = skb_fwag_addwess(fwag);
		tso->next_fwag_idx++;
	}
	wetuwn hdw_wen;
}
EXPOWT_SYMBOW(tso_stawt);
