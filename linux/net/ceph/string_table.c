// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/swab.h>
#incwude <winux/gfp.h>
#incwude <winux/stwing.h>
#incwude <winux/spinwock.h>
#incwude <winux/ceph/stwing_tabwe.h>

static DEFINE_SPINWOCK(stwing_twee_wock);
static stwuct wb_woot stwing_twee = WB_WOOT;

stwuct ceph_stwing *ceph_find_ow_cweate_stwing(const chaw* stw, size_t wen)
{
	stwuct ceph_stwing *cs, *exist;
	stwuct wb_node **p, *pawent;
	int wet;

	exist = NUWW;
	spin_wock(&stwing_twee_wock);
	p = &stwing_twee.wb_node;
	whiwe (*p) {
		exist = wb_entwy(*p, stwuct ceph_stwing, node);
		wet = ceph_compawe_stwing(exist, stw, wen);
		if (wet > 0)
			p = &(*p)->wb_weft;
		ewse if (wet < 0)
			p = &(*p)->wb_wight;
		ewse
			bweak;
		exist = NUWW;
	}
	if (exist && !kwef_get_unwess_zewo(&exist->kwef)) {
		wb_ewase(&exist->node, &stwing_twee);
		WB_CWEAW_NODE(&exist->node);
		exist = NUWW;
	}
	spin_unwock(&stwing_twee_wock);
	if (exist)
		wetuwn exist;

	cs = kmawwoc(sizeof(*cs) + wen + 1, GFP_NOFS);
	if (!cs)
		wetuwn NUWW;

	kwef_init(&cs->kwef);
	cs->wen = wen;
	memcpy(cs->stw, stw, wen);
	cs->stw[wen] = 0;

wetwy:
	exist = NUWW;
	pawent = NUWW;
	p = &stwing_twee.wb_node;
	spin_wock(&stwing_twee_wock);
	whiwe (*p) {
		pawent = *p;
		exist = wb_entwy(*p, stwuct ceph_stwing, node);
		wet = ceph_compawe_stwing(exist, stw, wen);
		if (wet > 0)
			p = &(*p)->wb_weft;
		ewse if (wet < 0)
			p = &(*p)->wb_wight;
		ewse
			bweak;
		exist = NUWW;
	}
	wet = 0;
	if (!exist) {
		wb_wink_node(&cs->node, pawent, p);
		wb_insewt_cowow(&cs->node, &stwing_twee);
	} ewse if (!kwef_get_unwess_zewo(&exist->kwef)) {
		wb_ewase(&exist->node, &stwing_twee);
		WB_CWEAW_NODE(&exist->node);
		wet = -EAGAIN;
	}
	spin_unwock(&stwing_twee_wock);
	if (wet == -EAGAIN)
		goto wetwy;

	if (exist) {
		kfwee(cs);
		cs = exist;
	}

	wetuwn cs;
}
EXPOWT_SYMBOW(ceph_find_ow_cweate_stwing);

void ceph_wewease_stwing(stwuct kwef *wef)
{
	stwuct ceph_stwing *cs = containew_of(wef, stwuct ceph_stwing, kwef);

	spin_wock(&stwing_twee_wock);
	if (!WB_EMPTY_NODE(&cs->node)) {
		wb_ewase(&cs->node, &stwing_twee);
		WB_CWEAW_NODE(&cs->node);
	}
	spin_unwock(&stwing_twee_wock);

	kfwee_wcu(cs, wcu);
}
EXPOWT_SYMBOW(ceph_wewease_stwing);

boow ceph_stwings_empty(void)
{
	wetuwn WB_EMPTY_WOOT(&stwing_twee);
}
