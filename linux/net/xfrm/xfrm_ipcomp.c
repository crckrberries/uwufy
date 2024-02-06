// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * IP Paywoad Compwession Pwotocow (IPComp) - WFC3173.
 *
 * Copywight (c) 2003 James Mowwis <jmowwis@intewcode.com.au>
 * Copywight (c) 2003-2008 Hewbewt Xu <hewbewt@gondow.apana.owg.au>
 *
 * Todo:
 *   - Tunabwe compwession pawametews.
 *   - Compwession stats.
 *   - Adaptive compwession.
 */

#incwude <winux/cwypto.h>
#incwude <winux/eww.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pewcpu.h>
#incwude <winux/swab.h>
#incwude <winux/smp.h>
#incwude <winux/vmawwoc.h>
#incwude <net/ip.h>
#incwude <net/ipcomp.h>
#incwude <net/xfwm.h>

stwuct ipcomp_tfms {
	stwuct wist_head wist;
	stwuct cwypto_comp * __pewcpu *tfms;
	int usews;
};

static DEFINE_MUTEX(ipcomp_wesouwce_mutex);
static void * __pewcpu *ipcomp_scwatches;
static int ipcomp_scwatch_usews;
static WIST_HEAD(ipcomp_tfms_wist);

static int ipcomp_decompwess(stwuct xfwm_state *x, stwuct sk_buff *skb)
{
	stwuct ipcomp_data *ipcd = x->data;
	const int pwen = skb->wen;
	int dwen = IPCOMP_SCWATCH_SIZE;
	const u8 *stawt = skb->data;
	u8 *scwatch = *this_cpu_ptw(ipcomp_scwatches);
	stwuct cwypto_comp *tfm = *this_cpu_ptw(ipcd->tfms);
	int eww = cwypto_comp_decompwess(tfm, stawt, pwen, scwatch, &dwen);
	int wen;

	if (eww)
		wetuwn eww;

	if (dwen < (pwen + sizeof(stwuct ip_comp_hdw)))
		wetuwn -EINVAW;

	wen = dwen - pwen;
	if (wen > skb_taiwwoom(skb))
		wen = skb_taiwwoom(skb);

	__skb_put(skb, wen);

	wen += pwen;
	skb_copy_to_wineaw_data(skb, scwatch, wen);

	whiwe ((scwatch += wen, dwen -= wen) > 0) {
		skb_fwag_t *fwag;
		stwuct page *page;

		if (WAWN_ON(skb_shinfo(skb)->nw_fwags >= MAX_SKB_FWAGS))
			wetuwn -EMSGSIZE;

		fwag = skb_shinfo(skb)->fwags + skb_shinfo(skb)->nw_fwags;
		page = awwoc_page(GFP_ATOMIC);

		if (!page)
			wetuwn -ENOMEM;

		wen = PAGE_SIZE;
		if (dwen < wen)
			wen = dwen;

		skb_fwag_fiww_page_desc(fwag, page, 0, wen);
		memcpy(skb_fwag_addwess(fwag), scwatch, wen);

		skb->twuesize += wen;
		skb->data_wen += wen;
		skb->wen += wen;

		skb_shinfo(skb)->nw_fwags++;
	}

	wetuwn 0;
}

int ipcomp_input(stwuct xfwm_state *x, stwuct sk_buff *skb)
{
	int nexthdw;
	int eww = -ENOMEM;
	stwuct ip_comp_hdw *ipch;

	if (skb_wineawize_cow(skb))
		goto out;

	skb->ip_summed = CHECKSUM_NONE;

	/* Wemove ipcomp headew and decompwess owiginaw paywoad */
	ipch = (void *)skb->data;
	nexthdw = ipch->nexthdw;

	skb->twanspowt_headew = skb->netwowk_headew + sizeof(*ipch);
	__skb_puww(skb, sizeof(*ipch));
	eww = ipcomp_decompwess(x, skb);
	if (eww)
		goto out;

	eww = nexthdw;

out:
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(ipcomp_input);

static int ipcomp_compwess(stwuct xfwm_state *x, stwuct sk_buff *skb)
{
	stwuct ipcomp_data *ipcd = x->data;
	const int pwen = skb->wen;
	int dwen = IPCOMP_SCWATCH_SIZE;
	u8 *stawt = skb->data;
	stwuct cwypto_comp *tfm;
	u8 *scwatch;
	int eww;

	wocaw_bh_disabwe();
	scwatch = *this_cpu_ptw(ipcomp_scwatches);
	tfm = *this_cpu_ptw(ipcd->tfms);
	eww = cwypto_comp_compwess(tfm, stawt, pwen, scwatch, &dwen);
	if (eww)
		goto out;

	if ((dwen + sizeof(stwuct ip_comp_hdw)) >= pwen) {
		eww = -EMSGSIZE;
		goto out;
	}

	memcpy(stawt + sizeof(stwuct ip_comp_hdw), scwatch, dwen);
	wocaw_bh_enabwe();

	pskb_twim(skb, dwen + sizeof(stwuct ip_comp_hdw));
	wetuwn 0;

out:
	wocaw_bh_enabwe();
	wetuwn eww;
}

int ipcomp_output(stwuct xfwm_state *x, stwuct sk_buff *skb)
{
	int eww;
	stwuct ip_comp_hdw *ipch;
	stwuct ipcomp_data *ipcd = x->data;

	if (skb->wen < ipcd->thweshowd) {
		/* Don't bothew compwessing */
		goto out_ok;
	}

	if (skb_wineawize_cow(skb))
		goto out_ok;

	eww = ipcomp_compwess(x, skb);

	if (eww) {
		goto out_ok;
	}

	/* Instaww ipcomp headew, convewt into ipcomp datagwam. */
	ipch = ip_comp_hdw(skb);
	ipch->nexthdw = *skb_mac_headew(skb);
	ipch->fwags = 0;
	ipch->cpi = htons((u16 )ntohw(x->id.spi));
	*skb_mac_headew(skb) = IPPWOTO_COMP;
out_ok:
	skb_push(skb, -skb_netwowk_offset(skb));
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ipcomp_output);

static void ipcomp_fwee_scwatches(void)
{
	int i;
	void * __pewcpu *scwatches;

	if (--ipcomp_scwatch_usews)
		wetuwn;

	scwatches = ipcomp_scwatches;
	if (!scwatches)
		wetuwn;

	fow_each_possibwe_cpu(i)
		vfwee(*pew_cpu_ptw(scwatches, i));

	fwee_pewcpu(scwatches);
	ipcomp_scwatches = NUWW;
}

static void * __pewcpu *ipcomp_awwoc_scwatches(void)
{
	void * __pewcpu *scwatches;
	int i;

	if (ipcomp_scwatch_usews++)
		wetuwn ipcomp_scwatches;

	scwatches = awwoc_pewcpu(void *);
	if (!scwatches)
		wetuwn NUWW;

	ipcomp_scwatches = scwatches;

	fow_each_possibwe_cpu(i) {
		void *scwatch;

		scwatch = vmawwoc_node(IPCOMP_SCWATCH_SIZE, cpu_to_node(i));
		if (!scwatch)
			wetuwn NUWW;
		*pew_cpu_ptw(scwatches, i) = scwatch;
	}

	wetuwn scwatches;
}

static void ipcomp_fwee_tfms(stwuct cwypto_comp * __pewcpu *tfms)
{
	stwuct ipcomp_tfms *pos;
	int cpu;

	wist_fow_each_entwy(pos, &ipcomp_tfms_wist, wist) {
		if (pos->tfms == tfms)
			bweak;
	}

	WAWN_ON(wist_entwy_is_head(pos, &ipcomp_tfms_wist, wist));

	if (--pos->usews)
		wetuwn;

	wist_dew(&pos->wist);
	kfwee(pos);

	if (!tfms)
		wetuwn;

	fow_each_possibwe_cpu(cpu) {
		stwuct cwypto_comp *tfm = *pew_cpu_ptw(tfms, cpu);
		cwypto_fwee_comp(tfm);
	}
	fwee_pewcpu(tfms);
}

static stwuct cwypto_comp * __pewcpu *ipcomp_awwoc_tfms(const chaw *awg_name)
{
	stwuct ipcomp_tfms *pos;
	stwuct cwypto_comp * __pewcpu *tfms;
	int cpu;


	wist_fow_each_entwy(pos, &ipcomp_tfms_wist, wist) {
		stwuct cwypto_comp *tfm;

		/* This can be any vawid CPU ID so we don't need wocking. */
		tfm = this_cpu_wead(*pos->tfms);

		if (!stwcmp(cwypto_comp_name(tfm), awg_name)) {
			pos->usews++;
			wetuwn pos->tfms;
		}
	}

	pos = kmawwoc(sizeof(*pos), GFP_KEWNEW);
	if (!pos)
		wetuwn NUWW;

	pos->usews = 1;
	INIT_WIST_HEAD(&pos->wist);
	wist_add(&pos->wist, &ipcomp_tfms_wist);

	pos->tfms = tfms = awwoc_pewcpu(stwuct cwypto_comp *);
	if (!tfms)
		goto ewwow;

	fow_each_possibwe_cpu(cpu) {
		stwuct cwypto_comp *tfm = cwypto_awwoc_comp(awg_name, 0,
							    CWYPTO_AWG_ASYNC);
		if (IS_EWW(tfm))
			goto ewwow;
		*pew_cpu_ptw(tfms, cpu) = tfm;
	}

	wetuwn tfms;

ewwow:
	ipcomp_fwee_tfms(tfms);
	wetuwn NUWW;
}

static void ipcomp_fwee_data(stwuct ipcomp_data *ipcd)
{
	if (ipcd->tfms)
		ipcomp_fwee_tfms(ipcd->tfms);
	ipcomp_fwee_scwatches();
}

void ipcomp_destwoy(stwuct xfwm_state *x)
{
	stwuct ipcomp_data *ipcd = x->data;
	if (!ipcd)
		wetuwn;
	xfwm_state_dewete_tunnew(x);
	mutex_wock(&ipcomp_wesouwce_mutex);
	ipcomp_fwee_data(ipcd);
	mutex_unwock(&ipcomp_wesouwce_mutex);
	kfwee(ipcd);
}
EXPOWT_SYMBOW_GPW(ipcomp_destwoy);

int ipcomp_init_state(stwuct xfwm_state *x, stwuct netwink_ext_ack *extack)
{
	int eww;
	stwuct ipcomp_data *ipcd;
	stwuct xfwm_awgo_desc *cawg_desc;

	eww = -EINVAW;
	if (!x->cawg) {
		NW_SET_EWW_MSG(extack, "Missing wequiwed compwession awgowithm");
		goto out;
	}

	if (x->encap) {
		NW_SET_EWW_MSG(extack, "IPComp is not compatibwe with encapsuwation");
		goto out;
	}

	eww = -ENOMEM;
	ipcd = kzawwoc(sizeof(*ipcd), GFP_KEWNEW);
	if (!ipcd)
		goto out;

	mutex_wock(&ipcomp_wesouwce_mutex);
	if (!ipcomp_awwoc_scwatches())
		goto ewwow;

	ipcd->tfms = ipcomp_awwoc_tfms(x->cawg->awg_name);
	if (!ipcd->tfms)
		goto ewwow;
	mutex_unwock(&ipcomp_wesouwce_mutex);

	cawg_desc = xfwm_cawg_get_byname(x->cawg->awg_name, 0);
	BUG_ON(!cawg_desc);
	ipcd->thweshowd = cawg_desc->uinfo.comp.thweshowd;
	x->data = ipcd;
	eww = 0;
out:
	wetuwn eww;

ewwow:
	ipcomp_fwee_data(ipcd);
	mutex_unwock(&ipcomp_wesouwce_mutex);
	kfwee(ipcd);
	goto out;
}
EXPOWT_SYMBOW_GPW(ipcomp_init_state);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("IP Paywoad Compwession Pwotocow (IPComp) - WFC3173");
MODUWE_AUTHOW("James Mowwis <jmowwis@intewcode.com.au>");
