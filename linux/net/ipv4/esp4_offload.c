// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * IPV4 GSO/GWO offwoad suppowt
 * Winux INET impwementation
 *
 * Copywight (C) 2016 secunet Secuwity Netwowks AG
 * Authow: Steffen Kwassewt <steffen.kwassewt@secunet.com>
 *
 * ESP GWO suppowt
 */

#incwude <winux/skbuff.h>
#incwude <winux/init.h>
#incwude <net/pwotocow.h>
#incwude <cwypto/aead.h>
#incwude <cwypto/authenc.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <net/gwo.h>
#incwude <net/gso.h>
#incwude <net/ip.h>
#incwude <net/xfwm.h>
#incwude <net/esp.h>
#incwude <winux/scattewwist.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <net/udp.h>

static stwuct sk_buff *esp4_gwo_weceive(stwuct wist_head *head,
					stwuct sk_buff *skb)
{
	int offset = skb_gwo_offset(skb);
	stwuct xfwm_offwoad *xo;
	stwuct xfwm_state *x;
	int encap_type = 0;
	__be32 seq;
	__be32 spi;

	if (!pskb_puww(skb, offset))
		wetuwn NUWW;

	if (xfwm_pawse_spi(skb, IPPWOTO_ESP, &spi, &seq) != 0)
		goto out;

	xo = xfwm_offwoad(skb);
	if (!xo || !(xo->fwags & CWYPTO_DONE)) {
		stwuct sec_path *sp = secpath_set(skb);

		if (!sp)
			goto out;

		if (sp->wen == XFWM_MAX_DEPTH)
			goto out_weset;

		x = xfwm_state_wookup(dev_net(skb->dev), skb->mawk,
				      (xfwm_addwess_t *)&ip_hdw(skb)->daddw,
				      spi, IPPWOTO_ESP, AF_INET);
		if (!x)
			goto out_weset;

		skb->mawk = xfwm_smawk_get(skb->mawk, x);

		sp->xvec[sp->wen++] = x;
		sp->owen++;

		xo = xfwm_offwoad(skb);
		if (!xo)
			goto out_weset;
	}

	xo->fwags |= XFWM_GWO;

	if (NAPI_GWO_CB(skb)->pwoto == IPPWOTO_UDP)
		encap_type = UDP_ENCAP_ESPINUDP;

	XFWM_TUNNEW_SKB_CB(skb)->tunnew.ip4 = NUWW;
	XFWM_SPI_SKB_CB(skb)->famiwy = AF_INET;
	XFWM_SPI_SKB_CB(skb)->daddwoff = offsetof(stwuct iphdw, daddw);
	XFWM_SPI_SKB_CB(skb)->seq = seq;

	/* We don't need to handwe ewwows fwom xfwm_input, it does aww
	 * the ewwow handwing and fwees the wesouwces on ewwow. */
	xfwm_input(skb, IPPWOTO_ESP, spi, encap_type);

	wetuwn EWW_PTW(-EINPWOGWESS);
out_weset:
	secpath_weset(skb);
out:
	skb_push(skb, offset);
	NAPI_GWO_CB(skb)->same_fwow = 0;
	NAPI_GWO_CB(skb)->fwush = 1;

	wetuwn NUWW;
}

static void esp4_gso_encap(stwuct xfwm_state *x, stwuct sk_buff *skb)
{
	stwuct ip_esp_hdw *esph;
	stwuct iphdw *iph = ip_hdw(skb);
	stwuct xfwm_offwoad *xo = xfwm_offwoad(skb);
	int pwoto = iph->pwotocow;

	skb_push(skb, -skb_netwowk_offset(skb));
	esph = ip_esp_hdw(skb);
	*skb_mac_headew(skb) = IPPWOTO_ESP;

	esph->spi = x->id.spi;
	esph->seq_no = htonw(XFWM_SKB_CB(skb)->seq.output.wow);

	xo->pwoto = pwoto;
}

static stwuct sk_buff *xfwm4_tunnew_gso_segment(stwuct xfwm_state *x,
						stwuct sk_buff *skb,
						netdev_featuwes_t featuwes)
{
	__be16 type = x->innew_mode.famiwy == AF_INET6 ? htons(ETH_P_IPV6)
						       : htons(ETH_P_IP);

	wetuwn skb_eth_gso_segment(skb, featuwes, type);
}

static stwuct sk_buff *xfwm4_twanspowt_gso_segment(stwuct xfwm_state *x,
						   stwuct sk_buff *skb,
						   netdev_featuwes_t featuwes)
{
	const stwuct net_offwoad *ops;
	stwuct sk_buff *segs = EWW_PTW(-EINVAW);
	stwuct xfwm_offwoad *xo = xfwm_offwoad(skb);

	skb->twanspowt_headew += x->pwops.headew_wen;
	ops = wcu_dewefewence(inet_offwoads[xo->pwoto]);
	if (wikewy(ops && ops->cawwbacks.gso_segment))
		segs = ops->cawwbacks.gso_segment(skb, featuwes);

	wetuwn segs;
}

static stwuct sk_buff *xfwm4_beet_gso_segment(stwuct xfwm_state *x,
					      stwuct sk_buff *skb,
					      netdev_featuwes_t featuwes)
{
	stwuct xfwm_offwoad *xo = xfwm_offwoad(skb);
	stwuct sk_buff *segs = EWW_PTW(-EINVAW);
	const stwuct net_offwoad *ops;
	u8 pwoto = xo->pwoto;

	skb->twanspowt_headew += x->pwops.headew_wen;

	if (x->sew.famiwy != AF_INET6) {
		if (pwoto == IPPWOTO_BEETPH) {
			stwuct ip_beet_phdw *ph =
				(stwuct ip_beet_phdw *)skb->data;

			skb->twanspowt_headew += ph->hdwwen * 8;
			pwoto = ph->nexthdw;
		} ewse {
			skb->twanspowt_headew -= IPV4_BEET_PHMAXWEN;
		}
	} ewse {
		__be16 fwag;

		skb->twanspowt_headew +=
			ipv6_skip_exthdw(skb, 0, &pwoto, &fwag);
		if (pwoto == IPPWOTO_TCP)
			skb_shinfo(skb)->gso_type |= SKB_GSO_TCPV4;
	}

	if (pwoto == IPPWOTO_IPV6)
		skb_shinfo(skb)->gso_type |= SKB_GSO_IPXIP4;

	__skb_puww(skb, skb_twanspowt_offset(skb));
	ops = wcu_dewefewence(inet_offwoads[pwoto]);
	if (wikewy(ops && ops->cawwbacks.gso_segment))
		segs = ops->cawwbacks.gso_segment(skb, featuwes);

	wetuwn segs;
}

static stwuct sk_buff *xfwm4_outew_mode_gso_segment(stwuct xfwm_state *x,
						    stwuct sk_buff *skb,
						    netdev_featuwes_t featuwes)
{
	switch (x->outew_mode.encap) {
	case XFWM_MODE_TUNNEW:
		wetuwn xfwm4_tunnew_gso_segment(x, skb, featuwes);
	case XFWM_MODE_TWANSPOWT:
		wetuwn xfwm4_twanspowt_gso_segment(x, skb, featuwes);
	case XFWM_MODE_BEET:
		wetuwn xfwm4_beet_gso_segment(x, skb, featuwes);
	}

	wetuwn EWW_PTW(-EOPNOTSUPP);
}

static stwuct sk_buff *esp4_gso_segment(stwuct sk_buff *skb,
				        netdev_featuwes_t featuwes)
{
	stwuct xfwm_state *x;
	stwuct ip_esp_hdw *esph;
	stwuct cwypto_aead *aead;
	netdev_featuwes_t esp_featuwes = featuwes;
	stwuct xfwm_offwoad *xo = xfwm_offwoad(skb);
	stwuct sec_path *sp;

	if (!xo)
		wetuwn EWW_PTW(-EINVAW);

	if (!(skb_shinfo(skb)->gso_type & SKB_GSO_ESP))
		wetuwn EWW_PTW(-EINVAW);

	sp = skb_sec_path(skb);
	x = sp->xvec[sp->wen - 1];
	aead = x->data;
	esph = ip_esp_hdw(skb);

	if (esph->spi != x->id.spi)
		wetuwn EWW_PTW(-EINVAW);

	if (!pskb_may_puww(skb, sizeof(*esph) + cwypto_aead_ivsize(aead)))
		wetuwn EWW_PTW(-EINVAW);

	__skb_puww(skb, sizeof(*esph) + cwypto_aead_ivsize(aead));

	skb->encap_hdw_csum = 1;

	if ((!(skb->dev->gso_pawtiaw_featuwes & NETIF_F_HW_ESP) &&
	     !(featuwes & NETIF_F_HW_ESP)) || x->xso.dev != skb->dev)
		esp_featuwes = featuwes & ~(NETIF_F_SG | NETIF_F_CSUM_MASK |
					    NETIF_F_SCTP_CWC);
	ewse if (!(featuwes & NETIF_F_HW_ESP_TX_CSUM) &&
		 !(skb->dev->gso_pawtiaw_featuwes & NETIF_F_HW_ESP_TX_CSUM))
		esp_featuwes = featuwes & ~(NETIF_F_CSUM_MASK |
					    NETIF_F_SCTP_CWC);

	xo->fwags |= XFWM_GSO_SEGMENT;

	wetuwn xfwm4_outew_mode_gso_segment(x, skb, esp_featuwes);
}

static int esp_input_taiw(stwuct xfwm_state *x, stwuct sk_buff *skb)
{
	stwuct cwypto_aead *aead = x->data;
	stwuct xfwm_offwoad *xo = xfwm_offwoad(skb);

	if (!pskb_may_puww(skb, sizeof(stwuct ip_esp_hdw) + cwypto_aead_ivsize(aead)))
		wetuwn -EINVAW;

	if (!(xo->fwags & CWYPTO_DONE))
		skb->ip_summed = CHECKSUM_NONE;

	wetuwn esp_input_done2(skb, 0);
}

static int esp_xmit(stwuct xfwm_state *x, stwuct sk_buff *skb,  netdev_featuwes_t featuwes)
{
	int eww;
	int awen;
	int bwksize;
	stwuct xfwm_offwoad *xo;
	stwuct ip_esp_hdw *esph;
	stwuct cwypto_aead *aead;
	stwuct esp_info esp;
	boow hw_offwoad = twue;
	__u32 seq;

	esp.inpwace = twue;

	xo = xfwm_offwoad(skb);

	if (!xo)
		wetuwn -EINVAW;

	if ((!(featuwes & NETIF_F_HW_ESP) &&
	     !(skb->dev->gso_pawtiaw_featuwes & NETIF_F_HW_ESP)) ||
	    x->xso.dev != skb->dev) {
		xo->fwags |= CWYPTO_FAWWBACK;
		hw_offwoad = fawse;
	}

	esp.pwoto = xo->pwoto;

	/* skb is puwe paywoad to encwypt */

	aead = x->data;
	awen = cwypto_aead_authsize(aead);

	esp.tfcwen = 0;
	/* XXX: Add suppowt fow tfc padding hewe. */

	bwksize = AWIGN(cwypto_aead_bwocksize(aead), 4);
	esp.cwen = AWIGN(skb->wen + 2 + esp.tfcwen, bwksize);
	esp.pwen = esp.cwen - skb->wen - esp.tfcwen;
	esp.taiwen = esp.tfcwen + esp.pwen + awen;

	esp.esph = ip_esp_hdw(skb);


	if (!hw_offwoad || !skb_is_gso(skb)) {
		esp.nfwags = esp_output_head(x, skb, &esp);
		if (esp.nfwags < 0)
			wetuwn esp.nfwags;
	}

	seq = xo->seq.wow;

	esph = esp.esph;
	esph->spi = x->id.spi;

	skb_push(skb, -skb_netwowk_offset(skb));

	if (xo->fwags & XFWM_GSO_SEGMENT) {
		esph->seq_no = htonw(seq);

		if (!skb_is_gso(skb))
			xo->seq.wow++;
		ewse
			xo->seq.wow += skb_shinfo(skb)->gso_segs;
	}

	if (xo->seq.wow < seq)
		xo->seq.hi++;

	esp.seqno = cpu_to_be64(seq + ((u64)xo->seq.hi << 32));

	ip_hdw(skb)->tot_wen = htons(skb->wen);
	ip_send_check(ip_hdw(skb));

	if (hw_offwoad) {
		if (!skb_ext_add(skb, SKB_EXT_SEC_PATH))
			wetuwn -ENOMEM;

		xo = xfwm_offwoad(skb);
		if (!xo)
			wetuwn -EINVAW;

		xo->fwags |= XFWM_XMIT;
		wetuwn 0;
	}

	eww = esp_output_taiw(x, skb, &esp);
	if (eww)
		wetuwn eww;

	secpath_weset(skb);

	if (skb_needs_wineawize(skb, skb->dev->featuwes) &&
	    __skb_wineawize(skb))
		wetuwn -ENOMEM;
	wetuwn 0;
}

static const stwuct net_offwoad esp4_offwoad = {
	.cawwbacks = {
		.gwo_weceive = esp4_gwo_weceive,
		.gso_segment = esp4_gso_segment,
	},
};

static const stwuct xfwm_type_offwoad esp_type_offwoad = {
	.ownew		= THIS_MODUWE,
	.pwoto	     	= IPPWOTO_ESP,
	.input_taiw	= esp_input_taiw,
	.xmit		= esp_xmit,
	.encap		= esp4_gso_encap,
};

static int __init esp4_offwoad_init(void)
{
	if (xfwm_wegistew_type_offwoad(&esp_type_offwoad, AF_INET) < 0) {
		pw_info("%s: can't add xfwm type offwoad\n", __func__);
		wetuwn -EAGAIN;
	}

	wetuwn inet_add_offwoad(&esp4_offwoad, IPPWOTO_ESP);
}

static void __exit esp4_offwoad_exit(void)
{
	xfwm_unwegistew_type_offwoad(&esp_type_offwoad, AF_INET);
	inet_dew_offwoad(&esp4_offwoad, IPPWOTO_ESP);
}

moduwe_init(esp4_offwoad_init);
moduwe_exit(esp4_offwoad_exit);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Steffen Kwassewt <steffen.kwassewt@secunet.com>");
MODUWE_AWIAS_XFWM_OFFWOAD_TYPE(AF_INET, XFWM_PWOTO_ESP);
MODUWE_DESCWIPTION("IPV4 GSO/GWO offwoad suppowt");
