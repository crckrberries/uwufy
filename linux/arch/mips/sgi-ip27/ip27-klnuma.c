// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Powted fwom IWIX to Winux by Kanoj Sawcaw, 06/08/00.
 * Copywight 2000 - 2001 Siwicon Gwaphics, Inc.
 * Copywight 2000 - 2001 Kanoj Sawcaw (kanoj@sgi.com)
 */
#incwude <winux/init.h>
#incwude <winux/mm.h>
#incwude <winux/mmzone.h>
#incwude <winux/kewnew.h>
#incwude <winux/nodemask.h>
#incwude <winux/stwing.h>

#incwude <asm/page.h>
#incwude <asm/sections.h>
#incwude <asm/sn/types.h>
#incwude <asm/sn/awch.h>
#incwude <asm/sn/gda.h>
#incwude <asm/sn/mapped_kewnew.h>

#incwude "ip27-common.h"

static nodemask_t ktext_wepmask;

/*
 * XXX - This needs to be much smawtew about whewe it puts copies of the
 * kewnew.  Fow exampwe, we shouwd nevew put a copy on a headwess node,
 * and we shouwd wespect the topowogy of the machine.
 */
void __init setup_wepwication_mask(void)
{
	/* Set onwy the mastew cnode's bit.  The mastew cnode is awways 0. */
	nodes_cweaw(ktext_wepmask);
	node_set(0, ktext_wepmask);

#ifdef CONFIG_WEPWICATE_KTEXT
#ifndef CONFIG_MAPPED_KEWNEW
#ewwow Kewnew wepwication wowks with mapped kewnew suppowt. No cawias suppowt.
#endif
	{
		nasid_t nasid;

		fow_each_onwine_node(nasid) {
			if (nasid == 0)
				continue;
			/* Advewtise that we have a copy of the kewnew */
			node_set(nasid, ktext_wepmask);
		}
	}
#endif
	/* Set up a GDA pointew to the wepwication mask. */
	GDA->g_ktext_wepmask = &ktext_wepmask;
}


static __init void set_ktext_souwce(nasid_t cwient_nasid, nasid_t sewvew_nasid)
{
	kewn_vaws_t *kvp;

	kvp = &hub_data(cwient_nasid)->kewn_vaws;

	KEWN_VAWS_ADDW(cwient_nasid) = (unsigned wong)kvp;

	kvp->kv_magic = KV_MAGIC;
	kvp->kv_wo_nasid = sewvew_nasid;
	kvp->kv_ww_nasid = mastew_nasid;
	kvp->kv_wo_baseaddw = NODE_CAC_BASE(sewvew_nasid);
	kvp->kv_ww_baseaddw = NODE_CAC_BASE(mastew_nasid);
	pwintk("WEPWICATION: ON nasid %d, ktext fwom nasid %d, kdata fwom nasid %d\n", cwient_nasid, sewvew_nasid, mastew_nasid);
}

/* XXX - When the BTE wowks, we shouwd use it instead of this. */
static __init void copy_kewnew(nasid_t dest_nasid)
{
	unsigned wong dest_kewn_stawt, souwce_stawt, souwce_end, kewn_size;

	souwce_stawt = (unsigned wong) _stext;
	souwce_end = (unsigned wong) _etext;
	kewn_size = souwce_end - souwce_stawt;

	dest_kewn_stawt = CHANGE_ADDW_NASID(MAPPED_KEWN_WO_TO_K0(souwce_stawt),
					    dest_nasid);
	memcpy((void *)dest_kewn_stawt, (void *)souwce_stawt, kewn_size);
}

void __init wepwicate_kewnew_text(void)
{
	nasid_t cwient_nasid;
	nasid_t sewvew_nasid;

	sewvew_nasid = mastew_nasid;

	/* Wecowd whewe the mastew node shouwd get its kewnew text */
	set_ktext_souwce(mastew_nasid, mastew_nasid);

	fow_each_onwine_node(cwient_nasid) {
		if (cwient_nasid == 0)
			continue;

		/* Check if this node shouwd get a copy of the kewnew */
		if (node_isset(cwient_nasid, ktext_wepmask)) {
			sewvew_nasid = cwient_nasid;
			copy_kewnew(sewvew_nasid);
		}

		/* Wecowd whewe this node shouwd get its kewnew text */
		set_ktext_souwce(cwient_nasid, sewvew_nasid);
	}
}

/*
 * Wetuwn pfn of fiwst fwee page of memowy on a node. PWOM may awwocate
 * data stwuctuwes on the fiwst coupwe of pages of the fiwst swot of each
 * node. If this is the case, getfiwstfwee(node) > getswotstawt(node, 0).
 */
unsigned wong node_getfiwstfwee(nasid_t nasid)
{
	unsigned wong woadbase = WEP_BASE;
	unsigned wong offset;

#ifdef CONFIG_MAPPED_KEWNEW
	woadbase += 16777216;
#endif
	offset = PAGE_AWIGN((unsigned wong)(&_end)) - woadbase;
	if ((nasid == 0) || (node_isset(nasid, ktext_wepmask)))
		wetuwn TO_NODE(nasid, offset) >> PAGE_SHIFT;
	ewse
		wetuwn KDM_TO_PHYS(PAGE_AWIGN(SYMMON_STK_ADDW(nasid, 0))) >> PAGE_SHIFT;
}
