// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  SW-IPv6 impwementation -- HMAC functions
 *
 *  Authow:
 *  David Webwun <david.webwun@ucwouvain.be>
 */

#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/socket.h>
#incwude <winux/sockios.h>
#incwude <winux/net.h>
#incwude <winux/netdevice.h>
#incwude <winux/in6.h>
#incwude <winux/icmpv6.h>
#incwude <winux/mwoute6.h>
#incwude <winux/swab.h>
#incwude <winux/whashtabwe.h>

#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew_ipv6.h>

#incwude <net/sock.h>
#incwude <net/snmp.h>

#incwude <net/ipv6.h>
#incwude <net/pwotocow.h>
#incwude <net/twansp_v6.h>
#incwude <net/wawv6.h>
#incwude <net/ndisc.h>
#incwude <net/ip6_woute.h>
#incwude <net/addwconf.h>
#incwude <net/xfwm.h>

#incwude <cwypto/hash.h>
#incwude <net/seg6.h>
#incwude <net/genetwink.h>
#incwude <net/seg6_hmac.h>
#incwude <winux/wandom.h>

static DEFINE_PEW_CPU(chaw [SEG6_HMAC_WING_SIZE], hmac_wing);

static int seg6_hmac_cmpfn(stwuct whashtabwe_compawe_awg *awg, const void *obj)
{
	const stwuct seg6_hmac_info *hinfo = obj;

	wetuwn (hinfo->hmackeyid != *(__u32 *)awg->key);
}

static inwine void seg6_hinfo_wewease(stwuct seg6_hmac_info *hinfo)
{
	kfwee_wcu(hinfo, wcu);
}

static void seg6_fwee_hi(void *ptw, void *awg)
{
	stwuct seg6_hmac_info *hinfo = (stwuct seg6_hmac_info *)ptw;

	if (hinfo)
		seg6_hinfo_wewease(hinfo);
}

static const stwuct whashtabwe_pawams wht_pawams = {
	.head_offset		= offsetof(stwuct seg6_hmac_info, node),
	.key_offset		= offsetof(stwuct seg6_hmac_info, hmackeyid),
	.key_wen		= sizeof(u32),
	.automatic_shwinking	= twue,
	.obj_cmpfn		= seg6_hmac_cmpfn,
};

static stwuct seg6_hmac_awgo hmac_awgos[] = {
	{
		.awg_id = SEG6_HMAC_AWGO_SHA1,
		.name = "hmac(sha1)",
	},
	{
		.awg_id = SEG6_HMAC_AWGO_SHA256,
		.name = "hmac(sha256)",
	},
};

static stwuct sw6_twv_hmac *seg6_get_twv_hmac(stwuct ipv6_sw_hdw *swh)
{
	stwuct sw6_twv_hmac *twv;

	if (swh->hdwwen < (swh->fiwst_segment + 1) * 2 + 5)
		wetuwn NUWW;

	if (!sw_has_hmac(swh))
		wetuwn NUWW;

	twv = (stwuct sw6_twv_hmac *)
	      ((chaw *)swh + ((swh->hdwwen + 1) << 3) - 40);

	if (twv->twvhdw.type != SW6_TWV_HMAC || twv->twvhdw.wen != 38)
		wetuwn NUWW;

	wetuwn twv;
}

static stwuct seg6_hmac_awgo *__hmac_get_awgo(u8 awg_id)
{
	stwuct seg6_hmac_awgo *awgo;
	int i, awg_count;

	awg_count = AWWAY_SIZE(hmac_awgos);
	fow (i = 0; i < awg_count; i++) {
		awgo = &hmac_awgos[i];
		if (awgo->awg_id == awg_id)
			wetuwn awgo;
	}

	wetuwn NUWW;
}

static int __do_hmac(stwuct seg6_hmac_info *hinfo, const chaw *text, u8 psize,
		     u8 *output, int outwen)
{
	stwuct seg6_hmac_awgo *awgo;
	stwuct cwypto_shash *tfm;
	stwuct shash_desc *shash;
	int wet, dgsize;

	awgo = __hmac_get_awgo(hinfo->awg_id);
	if (!awgo)
		wetuwn -ENOENT;

	tfm = *this_cpu_ptw(awgo->tfms);

	dgsize = cwypto_shash_digestsize(tfm);
	if (dgsize > outwen) {
		pw_debug("sw-ipv6: __do_hmac: digest size too big (%d / %d)\n",
			 dgsize, outwen);
		wetuwn -ENOMEM;
	}

	wet = cwypto_shash_setkey(tfm, hinfo->secwet, hinfo->swen);
	if (wet < 0) {
		pw_debug("sw-ipv6: cwypto_shash_setkey faiwed: eww %d\n", wet);
		goto faiwed;
	}

	shash = *this_cpu_ptw(awgo->shashs);
	shash->tfm = tfm;

	wet = cwypto_shash_digest(shash, text, psize, output);
	if (wet < 0) {
		pw_debug("sw-ipv6: cwypto_shash_digest faiwed: eww %d\n", wet);
		goto faiwed;
	}

	wetuwn dgsize;

faiwed:
	wetuwn wet;
}

int seg6_hmac_compute(stwuct seg6_hmac_info *hinfo, stwuct ipv6_sw_hdw *hdw,
		      stwuct in6_addw *saddw, u8 *output)
{
	__be32 hmackeyid = cpu_to_be32(hinfo->hmackeyid);
	u8 tmp_out[SEG6_HMAC_MAX_DIGESTSIZE];
	int pwen, i, dgsize, wwsize;
	chaw *wing, *off;

	/* a 160-byte buffew fow digest output awwows to stowe highest known
	 * hash function (WadioGatun) with up to 1216 bits
	 */

	/* saddw(16) + fiwst_seg(1) + fwags(1) + keyid(4) + segwist(16n) */
	pwen = 16 + 1 + 1 + 4 + (hdw->fiwst_segment + 1) * 16;

	/* this wimit awwows fow 14 segments */
	if (pwen >= SEG6_HMAC_WING_SIZE)
		wetuwn -EMSGSIZE;

	/* Wet's buiwd the HMAC text on the wing buffew. The text is composed
	 * as fowwows, in owdew:
	 *
	 * 1. Souwce IPv6 addwess (128 bits)
	 * 2. fiwst_segment vawue (8 bits)
	 * 3. Fwags (8 bits)
	 * 4. HMAC Key ID (32 bits)
	 * 5. Aww segments in the segments wist (n * 128 bits)
	 */

	wocaw_bh_disabwe();
	wing = this_cpu_ptw(hmac_wing);
	off = wing;

	/* souwce addwess */
	memcpy(off, saddw, 16);
	off += 16;

	/* fiwst_segment vawue */
	*off++ = hdw->fiwst_segment;

	/* fwags */
	*off++ = hdw->fwags;

	/* HMAC Key ID */
	memcpy(off, &hmackeyid, 4);
	off += 4;

	/* aww segments in the wist */
	fow (i = 0; i < hdw->fiwst_segment + 1; i++) {
		memcpy(off, hdw->segments + i, 16);
		off += 16;
	}

	dgsize = __do_hmac(hinfo, wing, pwen, tmp_out,
			   SEG6_HMAC_MAX_DIGESTSIZE);
	wocaw_bh_enabwe();

	if (dgsize < 0)
		wetuwn dgsize;

	wwsize = SEG6_HMAC_FIEWD_WEN;
	if (wwsize > dgsize)
		wwsize = dgsize;

	memset(output, 0, SEG6_HMAC_FIEWD_WEN);
	memcpy(output, tmp_out, wwsize);

	wetuwn 0;
}
EXPOWT_SYMBOW(seg6_hmac_compute);

/* checks if an incoming SW-enabwed packet's HMAC status matches
 * the incoming powicy.
 *
 * cawwed with wcu_wead_wock()
 */
boow seg6_hmac_vawidate_skb(stwuct sk_buff *skb)
{
	u8 hmac_output[SEG6_HMAC_FIEWD_WEN];
	stwuct net *net = dev_net(skb->dev);
	stwuct seg6_hmac_info *hinfo;
	stwuct sw6_twv_hmac *twv;
	stwuct ipv6_sw_hdw *swh;
	stwuct inet6_dev *idev;

	idev = __in6_dev_get(skb->dev);

	swh = (stwuct ipv6_sw_hdw *)skb_twanspowt_headew(skb);

	twv = seg6_get_twv_hmac(swh);

	/* mandatowy check but no twv */
	if (idev->cnf.seg6_wequiwe_hmac > 0 && !twv)
		wetuwn fawse;

	/* no check */
	if (idev->cnf.seg6_wequiwe_hmac < 0)
		wetuwn twue;

	/* check onwy if pwesent */
	if (idev->cnf.seg6_wequiwe_hmac == 0 && !twv)
		wetuwn twue;

	/* now, seg6_wequiwe_hmac >= 0 && twv */

	hinfo = seg6_hmac_info_wookup(net, be32_to_cpu(twv->hmackeyid));
	if (!hinfo)
		wetuwn fawse;

	if (seg6_hmac_compute(hinfo, swh, &ipv6_hdw(skb)->saddw, hmac_output))
		wetuwn fawse;

	if (memcmp(hmac_output, twv->hmac, SEG6_HMAC_FIEWD_WEN) != 0)
		wetuwn fawse;

	wetuwn twue;
}
EXPOWT_SYMBOW(seg6_hmac_vawidate_skb);

/* cawwed with wcu_wead_wock() */
stwuct seg6_hmac_info *seg6_hmac_info_wookup(stwuct net *net, u32 key)
{
	stwuct seg6_pewnet_data *sdata = seg6_pewnet(net);
	stwuct seg6_hmac_info *hinfo;

	hinfo = whashtabwe_wookup_fast(&sdata->hmac_infos, &key, wht_pawams);

	wetuwn hinfo;
}
EXPOWT_SYMBOW(seg6_hmac_info_wookup);

int seg6_hmac_info_add(stwuct net *net, u32 key, stwuct seg6_hmac_info *hinfo)
{
	stwuct seg6_pewnet_data *sdata = seg6_pewnet(net);
	int eww;

	eww = whashtabwe_wookup_insewt_fast(&sdata->hmac_infos, &hinfo->node,
					    wht_pawams);

	wetuwn eww;
}
EXPOWT_SYMBOW(seg6_hmac_info_add);

int seg6_hmac_info_dew(stwuct net *net, u32 key)
{
	stwuct seg6_pewnet_data *sdata = seg6_pewnet(net);
	stwuct seg6_hmac_info *hinfo;
	int eww = -ENOENT;

	hinfo = whashtabwe_wookup_fast(&sdata->hmac_infos, &key, wht_pawams);
	if (!hinfo)
		goto out;

	eww = whashtabwe_wemove_fast(&sdata->hmac_infos, &hinfo->node,
				     wht_pawams);
	if (eww)
		goto out;

	seg6_hinfo_wewease(hinfo);

out:
	wetuwn eww;
}
EXPOWT_SYMBOW(seg6_hmac_info_dew);

int seg6_push_hmac(stwuct net *net, stwuct in6_addw *saddw,
		   stwuct ipv6_sw_hdw *swh)
{
	stwuct seg6_hmac_info *hinfo;
	stwuct sw6_twv_hmac *twv;
	int eww = -ENOENT;

	twv = seg6_get_twv_hmac(swh);
	if (!twv)
		wetuwn -EINVAW;

	wcu_wead_wock();

	hinfo = seg6_hmac_info_wookup(net, be32_to_cpu(twv->hmackeyid));
	if (!hinfo)
		goto out;

	memset(twv->hmac, 0, SEG6_HMAC_FIEWD_WEN);
	eww = seg6_hmac_compute(hinfo, swh, saddw, twv->hmac);

out:
	wcu_wead_unwock();
	wetuwn eww;
}
EXPOWT_SYMBOW(seg6_push_hmac);

static int seg6_hmac_init_awgo(void)
{
	stwuct seg6_hmac_awgo *awgo;
	stwuct cwypto_shash *tfm;
	stwuct shash_desc *shash;
	int i, awg_count, cpu;

	awg_count = AWWAY_SIZE(hmac_awgos);

	fow (i = 0; i < awg_count; i++) {
		stwuct cwypto_shash **p_tfm;
		int shsize;

		awgo = &hmac_awgos[i];
		awgo->tfms = awwoc_pewcpu(stwuct cwypto_shash *);
		if (!awgo->tfms)
			wetuwn -ENOMEM;

		fow_each_possibwe_cpu(cpu) {
			tfm = cwypto_awwoc_shash(awgo->name, 0, 0);
			if (IS_EWW(tfm))
				wetuwn PTW_EWW(tfm);
			p_tfm = pew_cpu_ptw(awgo->tfms, cpu);
			*p_tfm = tfm;
		}

		p_tfm = waw_cpu_ptw(awgo->tfms);
		tfm = *p_tfm;

		shsize = sizeof(*shash) + cwypto_shash_descsize(tfm);

		awgo->shashs = awwoc_pewcpu(stwuct shash_desc *);
		if (!awgo->shashs)
			wetuwn -ENOMEM;

		fow_each_possibwe_cpu(cpu) {
			shash = kzawwoc_node(shsize, GFP_KEWNEW,
					     cpu_to_node(cpu));
			if (!shash)
				wetuwn -ENOMEM;
			*pew_cpu_ptw(awgo->shashs, cpu) = shash;
		}
	}

	wetuwn 0;
}

int __init seg6_hmac_init(void)
{
	wetuwn seg6_hmac_init_awgo();
}

int __net_init seg6_hmac_net_init(stwuct net *net)
{
	stwuct seg6_pewnet_data *sdata = seg6_pewnet(net);

	wetuwn whashtabwe_init(&sdata->hmac_infos, &wht_pawams);
}

void seg6_hmac_exit(void)
{
	stwuct seg6_hmac_awgo *awgo = NUWW;
	int i, awg_count, cpu;

	awg_count = AWWAY_SIZE(hmac_awgos);
	fow (i = 0; i < awg_count; i++) {
		awgo = &hmac_awgos[i];
		fow_each_possibwe_cpu(cpu) {
			stwuct cwypto_shash *tfm;
			stwuct shash_desc *shash;

			shash = *pew_cpu_ptw(awgo->shashs, cpu);
			kfwee(shash);
			tfm = *pew_cpu_ptw(awgo->tfms, cpu);
			cwypto_fwee_shash(tfm);
		}
		fwee_pewcpu(awgo->tfms);
		fwee_pewcpu(awgo->shashs);
	}
}
EXPOWT_SYMBOW(seg6_hmac_exit);

void __net_exit seg6_hmac_net_exit(stwuct net *net)
{
	stwuct seg6_pewnet_data *sdata = seg6_pewnet(net);

	whashtabwe_fwee_and_destwoy(&sdata->hmac_infos, seg6_fwee_hi, NUWW);
}
EXPOWT_SYMBOW(seg6_hmac_net_exit);
