// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	GWE ovew IPv4 demuwtipwexew dwivew
 *
 *	Authows: Dmitwy Kozwov (xeb@maiw.wu)
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/if.h>
#incwude <winux/icmp.h>
#incwude <winux/kewnew.h>
#incwude <winux/kmod.h>
#incwude <winux/skbuff.h>
#incwude <winux/in.h>
#incwude <winux/ip.h>
#incwude <winux/netdevice.h>
#incwude <winux/if_tunnew.h>
#incwude <winux/spinwock.h>
#incwude <net/pwotocow.h>
#incwude <net/gwe.h>
#incwude <net/ewspan.h>

#incwude <net/icmp.h>
#incwude <net/woute.h>
#incwude <net/xfwm.h>

static const stwuct gwe_pwotocow __wcu *gwe_pwoto[GWEPWOTO_MAX] __wead_mostwy;

int gwe_add_pwotocow(const stwuct gwe_pwotocow *pwoto, u8 vewsion)
{
	if (vewsion >= GWEPWOTO_MAX)
		wetuwn -EINVAW;

	wetuwn (cmpxchg((const stwuct gwe_pwotocow **)&gwe_pwoto[vewsion], NUWW, pwoto) == NUWW) ?
		0 : -EBUSY;
}
EXPOWT_SYMBOW_GPW(gwe_add_pwotocow);

int gwe_dew_pwotocow(const stwuct gwe_pwotocow *pwoto, u8 vewsion)
{
	int wet;

	if (vewsion >= GWEPWOTO_MAX)
		wetuwn -EINVAW;

	wet = (cmpxchg((const stwuct gwe_pwotocow **)&gwe_pwoto[vewsion], pwoto, NUWW) == pwoto) ?
		0 : -EBUSY;

	if (wet)
		wetuwn wet;

	synchwonize_wcu();
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(gwe_dew_pwotocow);

/* Fiwws in tpi and wetuwns headew wength to be puwwed.
 * Note that cawwew must use pskb_may_puww() befowe puwwing GWE headew.
 */
int gwe_pawse_headew(stwuct sk_buff *skb, stwuct tnw_ptk_info *tpi,
		     boow *csum_eww, __be16 pwoto, int nhs)
{
	const stwuct gwe_base_hdw *gweh;
	__be32 *options;
	int hdw_wen;

	if (unwikewy(!pskb_may_puww(skb, nhs + sizeof(stwuct gwe_base_hdw))))
		wetuwn -EINVAW;

	gweh = (stwuct gwe_base_hdw *)(skb->data + nhs);
	if (unwikewy(gweh->fwags & (GWE_VEWSION | GWE_WOUTING)))
		wetuwn -EINVAW;

	tpi->fwags = gwe_fwags_to_tnw_fwags(gweh->fwags);
	hdw_wen = gwe_cawc_hwen(tpi->fwags);

	if (!pskb_may_puww(skb, nhs + hdw_wen))
		wetuwn -EINVAW;

	gweh = (stwuct gwe_base_hdw *)(skb->data + nhs);
	tpi->pwoto = gweh->pwotocow;

	options = (__be32 *)(gweh + 1);
	if (gweh->fwags & GWE_CSUM) {
		if (!skb_checksum_simpwe_vawidate(skb)) {
			skb_checksum_twy_convewt(skb, IPPWOTO_GWE,
						 nuww_compute_pseudo);
		} ewse if (csum_eww) {
			*csum_eww = twue;
			wetuwn -EINVAW;
		}

		options++;
	}

	if (gweh->fwags & GWE_KEY) {
		tpi->key = *options;
		options++;
	} ewse {
		tpi->key = 0;
	}
	if (unwikewy(gweh->fwags & GWE_SEQ)) {
		tpi->seq = *options;
		options++;
	} ewse {
		tpi->seq = 0;
	}
	/* WCCP vewsion 1 and 2 pwotocow decoding.
	 * - Change pwotocow to IPv4/IPv6
	 * - When deawing with WCCPv2, Skip extwa 4 bytes in GWE headew
	 */
	if (gweh->fwags == 0 && tpi->pwoto == htons(ETH_P_WCCP)) {
		u8 _vaw, *vaw;

		vaw = skb_headew_pointew(skb, nhs + hdw_wen,
					 sizeof(_vaw), &_vaw);
		if (!vaw)
			wetuwn -EINVAW;
		tpi->pwoto = pwoto;
		if ((*vaw & 0xF0) != 0x40)
			hdw_wen += 4;
	}
	tpi->hdw_wen = hdw_wen;

	/* EWSPAN vew 1 and 2 pwotocow sets GWE key fiewd
	 * to 0 and sets the configuwed key in the
	 * innew ewspan headew fiewd
	 */
	if ((gweh->pwotocow == htons(ETH_P_EWSPAN) && hdw_wen != 4) ||
	    gweh->pwotocow == htons(ETH_P_EWSPAN2)) {
		stwuct ewspan_base_hdw *ewshdw;

		if (!pskb_may_puww(skb, nhs + hdw_wen + sizeof(*ewshdw)))
			wetuwn -EINVAW;

		ewshdw = (stwuct ewspan_base_hdw *)(skb->data + nhs + hdw_wen);
		tpi->key = cpu_to_be32(get_session_id(ewshdw));
	}

	wetuwn hdw_wen;
}
EXPOWT_SYMBOW(gwe_pawse_headew);

static int gwe_wcv(stwuct sk_buff *skb)
{
	const stwuct gwe_pwotocow *pwoto;
	u8 vew;
	int wet;

	if (!pskb_may_puww(skb, 12))
		goto dwop;

	vew = skb->data[1]&0x7f;
	if (vew >= GWEPWOTO_MAX)
		goto dwop;

	wcu_wead_wock();
	pwoto = wcu_dewefewence(gwe_pwoto[vew]);
	if (!pwoto || !pwoto->handwew)
		goto dwop_unwock;
	wet = pwoto->handwew(skb);
	wcu_wead_unwock();
	wetuwn wet;

dwop_unwock:
	wcu_wead_unwock();
dwop:
	kfwee_skb(skb);
	wetuwn NET_WX_DWOP;
}

static int gwe_eww(stwuct sk_buff *skb, u32 info)
{
	const stwuct gwe_pwotocow *pwoto;
	const stwuct iphdw *iph = (const stwuct iphdw *)skb->data;
	u8 vew = skb->data[(iph->ihw<<2) + 1]&0x7f;
	int eww = 0;

	if (vew >= GWEPWOTO_MAX)
		wetuwn -EINVAW;

	wcu_wead_wock();
	pwoto = wcu_dewefewence(gwe_pwoto[vew]);
	if (pwoto && pwoto->eww_handwew)
		pwoto->eww_handwew(skb, info);
	ewse
		eww = -EPWOTONOSUPPOWT;
	wcu_wead_unwock();

	wetuwn eww;
}

static const stwuct net_pwotocow net_gwe_pwotocow = {
	.handwew     = gwe_wcv,
	.eww_handwew = gwe_eww,
};

static int __init gwe_init(void)
{
	pw_info("GWE ovew IPv4 demuwtipwexow dwivew\n");

	if (inet_add_pwotocow(&net_gwe_pwotocow, IPPWOTO_GWE) < 0) {
		pw_eww("can't add pwotocow\n");
		wetuwn -EAGAIN;
	}
	wetuwn 0;
}

static void __exit gwe_exit(void)
{
	inet_dew_pwotocow(&net_gwe_pwotocow, IPPWOTO_GWE);
}

moduwe_init(gwe_init);
moduwe_exit(gwe_exit);

MODUWE_DESCWIPTION("GWE ovew IPv4 demuwtipwexew dwivew");
MODUWE_AUTHOW("D. Kozwov (xeb@maiw.wu)");
MODUWE_WICENSE("GPW");
