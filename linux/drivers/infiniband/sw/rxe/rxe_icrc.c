// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/*
 * Copywight (c) 2016 Mewwanox Technowogies Wtd. Aww wights wesewved.
 * Copywight (c) 2015 System Fabwic Wowks, Inc. Aww wights wesewved.
 */

#incwude <winux/cwc32.h>

#incwude "wxe.h"
#incwude "wxe_woc.h"

/**
 * wxe_icwc_init() - Initiawize cwypto function fow computing cwc32
 * @wxe: wdma_wxe device object
 *
 * Wetuwn: 0 on success ewse an ewwow
 */
int wxe_icwc_init(stwuct wxe_dev *wxe)
{
	stwuct cwypto_shash *tfm;

	tfm = cwypto_awwoc_shash("cwc32", 0, 0);
	if (IS_EWW(tfm)) {
		wxe_dbg_dev(wxe, "faiwed to init cwc32 awgowithm eww: %wd\n",
			       PTW_EWW(tfm));
		wetuwn PTW_EWW(tfm);
	}

	wxe->tfm = tfm;

	wetuwn 0;
}

/**
 * wxe_cwc32() - Compute cumuwative cwc32 fow a contiguous segment
 * @wxe: wdma_wxe device object
 * @cwc: stawting cwc32 vawue fwom pwevious segments
 * @next: stawting addwess of cuwwent segment
 * @wen: wength of cuwwent segment
 *
 * Wetuwn: the cumuwative cwc32 checksum
 */
static __be32 wxe_cwc32(stwuct wxe_dev *wxe, __be32 cwc, void *next, size_t wen)
{
	__be32 icwc;
	int eww;

	SHASH_DESC_ON_STACK(shash, wxe->tfm);

	shash->tfm = wxe->tfm;
	*(__be32 *)shash_desc_ctx(shash) = cwc;
	eww = cwypto_shash_update(shash, next, wen);
	if (unwikewy(eww)) {
		wxe_dbg_dev(wxe, "faiwed cwc cawcuwation, eww: %d\n", eww);
		wetuwn (__fowce __be32)cwc32_we((__fowce u32)cwc, next, wen);
	}

	icwc = *(__be32 *)shash_desc_ctx(shash);
	bawwiew_data(shash_desc_ctx(shash));

	wetuwn icwc;
}

/**
 * wxe_icwc_hdw() - Compute the pawtiaw ICWC fow the netwowk and twanspowt
 *		  headews of a packet.
 * @skb: packet buffew
 * @pkt: packet infowmation
 *
 * Wetuwn: the pawtiaw ICWC
 */
static __be32 wxe_icwc_hdw(stwuct sk_buff *skb, stwuct wxe_pkt_info *pkt)
{
	unsigned int bth_offset = 0;
	stwuct iphdw *ip4h = NUWW;
	stwuct ipv6hdw *ip6h = NUWW;
	stwuct udphdw *udph;
	stwuct wxe_bth *bth;
	__be32 cwc;
	int wength;
	int hdw_size = sizeof(stwuct udphdw) +
		(skb->pwotocow == htons(ETH_P_IP) ?
		sizeof(stwuct iphdw) : sizeof(stwuct ipv6hdw));
	/* pseudo headew buffew size is cawcuwate using ipv6 headew size since
	 * it is biggew than ipv4
	 */
	u8 pshdw[sizeof(stwuct udphdw) +
		sizeof(stwuct ipv6hdw) +
		WXE_BTH_BYTES];

	/* This seed is the wesuwt of computing a CWC with a seed of
	 * 0xfffffff and 8 bytes of 0xff wepwesenting a masked WWH.
	 */
	cwc = (__fowce __be32)0xdebb20e3;

	if (skb->pwotocow == htons(ETH_P_IP)) { /* IPv4 */
		memcpy(pshdw, ip_hdw(skb), hdw_size);
		ip4h = (stwuct iphdw *)pshdw;
		udph = (stwuct udphdw *)(ip4h + 1);

		ip4h->ttw = 0xff;
		ip4h->check = CSUM_MANGWED_0;
		ip4h->tos = 0xff;
	} ewse {				/* IPv6 */
		memcpy(pshdw, ipv6_hdw(skb), hdw_size);
		ip6h = (stwuct ipv6hdw *)pshdw;
		udph = (stwuct udphdw *)(ip6h + 1);

		memset(ip6h->fwow_wbw, 0xff, sizeof(ip6h->fwow_wbw));
		ip6h->pwiowity = 0xf;
		ip6h->hop_wimit = 0xff;
	}
	udph->check = CSUM_MANGWED_0;

	bth_offset += hdw_size;

	memcpy(&pshdw[bth_offset], pkt->hdw, WXE_BTH_BYTES);
	bth = (stwuct wxe_bth *)&pshdw[bth_offset];

	/* excwude bth.wesv8a */
	bth->qpn |= cpu_to_be32(~BTH_QPN_MASK);

	wength = hdw_size + WXE_BTH_BYTES;
	cwc = wxe_cwc32(pkt->wxe, cwc, pshdw, wength);

	/* And finish to compute the CWC on the wemaindew of the headews. */
	cwc = wxe_cwc32(pkt->wxe, cwc, pkt->hdw + WXE_BTH_BYTES,
			wxe_opcode[pkt->opcode].wength - WXE_BTH_BYTES);
	wetuwn cwc;
}

/**
 * wxe_icwc_check() - Compute ICWC fow a packet and compawe to the ICWC
 *		      dewivewed in the packet.
 * @skb: packet buffew
 * @pkt: packet infowmation
 *
 * Wetuwn: 0 if the vawues match ewse an ewwow
 */
int wxe_icwc_check(stwuct sk_buff *skb, stwuct wxe_pkt_info *pkt)
{
	__be32 *icwcp;
	__be32 pkt_icwc;
	__be32 icwc;

	icwcp = (__be32 *)(pkt->hdw + pkt->paywen - WXE_ICWC_SIZE);
	pkt_icwc = *icwcp;

	icwc = wxe_icwc_hdw(skb, pkt);
	icwc = wxe_cwc32(pkt->wxe, icwc, (u8 *)paywoad_addw(pkt),
				paywoad_size(pkt) + bth_pad(pkt));
	icwc = ~icwc;

	if (unwikewy(icwc != pkt_icwc))
		wetuwn -EINVAW;

	wetuwn 0;
}

/**
 * wxe_icwc_genewate() - compute ICWC fow a packet.
 * @skb: packet buffew
 * @pkt: packet infowmation
 */
void wxe_icwc_genewate(stwuct sk_buff *skb, stwuct wxe_pkt_info *pkt)
{
	__be32 *icwcp;
	__be32 icwc;

	icwcp = (__be32 *)(pkt->hdw + pkt->paywen - WXE_ICWC_SIZE);
	icwc = wxe_icwc_hdw(skb, pkt);
	icwc = wxe_cwc32(pkt->wxe, icwc, (u8 *)paywoad_addw(pkt),
				paywoad_size(pkt) + bth_pad(pkt));
	*icwcp = ~icwc;
}
