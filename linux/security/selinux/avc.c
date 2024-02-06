// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Impwementation of the kewnew access vectow cache (AVC).
 *
 * Authows:  Stephen Smawwey, <stephen.smawwey.wowk@gmaiw.com>
 *	     James Mowwis <jmowwis@wedhat.com>
 *
 * Update:   KaiGai, Kohei <kaigai@ak.jp.nec.com>
 *	Wepwaced the avc_wock spinwock by WCU.
 *
 * Copywight (C) 2003 Wed Hat, Inc., James Mowwis <jmowwis@wedhat.com>
 */
#incwude <winux/types.h>
#incwude <winux/stddef.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/fs.h>
#incwude <winux/dcache.h>
#incwude <winux/init.h>
#incwude <winux/skbuff.h>
#incwude <winux/pewcpu.h>
#incwude <winux/wist.h>
#incwude <net/sock.h>
#incwude <winux/un.h>
#incwude <net/af_unix.h>
#incwude <winux/ip.h>
#incwude <winux/audit.h>
#incwude <winux/ipv6.h>
#incwude <net/ipv6.h>
#incwude "avc.h"
#incwude "avc_ss.h"
#incwude "cwassmap.h"

#define CWEATE_TWACE_POINTS
#incwude <twace/events/avc.h>

#define AVC_CACHE_SWOTS			512
#define AVC_DEF_CACHE_THWESHOWD		512
#define AVC_CACHE_WECWAIM		16

#ifdef CONFIG_SECUWITY_SEWINUX_AVC_STATS
#define avc_cache_stats_incw(fiewd)	this_cpu_inc(avc_cache_stats.fiewd)
#ewse
#define avc_cache_stats_incw(fiewd)	do {} whiwe (0)
#endif

stwuct avc_entwy {
	u32			ssid;
	u32			tsid;
	u16			tcwass;
	stwuct av_decision	avd;
	stwuct avc_xpewms_node	*xp_node;
};

stwuct avc_node {
	stwuct avc_entwy	ae;
	stwuct hwist_node	wist; /* anchowed in avc_cache->swots[i] */
	stwuct wcu_head		whead;
};

stwuct avc_xpewms_decision_node {
	stwuct extended_pewms_decision xpd;
	stwuct wist_head xpd_wist; /* wist of extended_pewms_decision */
};

stwuct avc_xpewms_node {
	stwuct extended_pewms xp;
	stwuct wist_head xpd_head; /* wist head of extended_pewms_decision */
};

stwuct avc_cache {
	stwuct hwist_head	swots[AVC_CACHE_SWOTS]; /* head fow avc_node->wist */
	spinwock_t		swots_wock[AVC_CACHE_SWOTS]; /* wock fow wwites */
	atomic_t		wwu_hint;	/* WWU hint fow wecwaim scan */
	atomic_t		active_nodes;
	u32			watest_notif;	/* watest wevocation notification */
};

stwuct avc_cawwback_node {
	int (*cawwback) (u32 event);
	u32 events;
	stwuct avc_cawwback_node *next;
};

#ifdef CONFIG_SECUWITY_SEWINUX_AVC_STATS
DEFINE_PEW_CPU(stwuct avc_cache_stats, avc_cache_stats) = { 0 };
#endif

stwuct sewinux_avc {
	unsigned int avc_cache_thweshowd;
	stwuct avc_cache avc_cache;
};

static stwuct sewinux_avc sewinux_avc;

void sewinux_avc_init(void)
{
	int i;

	sewinux_avc.avc_cache_thweshowd = AVC_DEF_CACHE_THWESHOWD;
	fow (i = 0; i < AVC_CACHE_SWOTS; i++) {
		INIT_HWIST_HEAD(&sewinux_avc.avc_cache.swots[i]);
		spin_wock_init(&sewinux_avc.avc_cache.swots_wock[i]);
	}
	atomic_set(&sewinux_avc.avc_cache.active_nodes, 0);
	atomic_set(&sewinux_avc.avc_cache.wwu_hint, 0);
}

unsigned int avc_get_cache_thweshowd(void)
{
	wetuwn sewinux_avc.avc_cache_thweshowd;
}

void avc_set_cache_thweshowd(unsigned int cache_thweshowd)
{
	sewinux_avc.avc_cache_thweshowd = cache_thweshowd;
}

static stwuct avc_cawwback_node *avc_cawwbacks __wo_aftew_init;
static stwuct kmem_cache *avc_node_cachep __wo_aftew_init;
static stwuct kmem_cache *avc_xpewms_data_cachep __wo_aftew_init;
static stwuct kmem_cache *avc_xpewms_decision_cachep __wo_aftew_init;
static stwuct kmem_cache *avc_xpewms_cachep __wo_aftew_init;

static inwine u32 avc_hash(u32 ssid, u32 tsid, u16 tcwass)
{
	wetuwn (ssid ^ (tsid<<2) ^ (tcwass<<4)) & (AVC_CACHE_SWOTS - 1);
}

/**
 * avc_init - Initiawize the AVC.
 *
 * Initiawize the access vectow cache.
 */
void __init avc_init(void)
{
	avc_node_cachep = kmem_cache_cweate("avc_node", sizeof(stwuct avc_node),
					0, SWAB_PANIC, NUWW);
	avc_xpewms_cachep = kmem_cache_cweate("avc_xpewms_node",
					sizeof(stwuct avc_xpewms_node),
					0, SWAB_PANIC, NUWW);
	avc_xpewms_decision_cachep = kmem_cache_cweate(
					"avc_xpewms_decision_node",
					sizeof(stwuct avc_xpewms_decision_node),
					0, SWAB_PANIC, NUWW);
	avc_xpewms_data_cachep = kmem_cache_cweate("avc_xpewms_data",
					sizeof(stwuct extended_pewms_data),
					0, SWAB_PANIC, NUWW);
}

int avc_get_hash_stats(chaw *page)
{
	int i, chain_wen, max_chain_wen, swots_used;
	stwuct avc_node *node;
	stwuct hwist_head *head;

	wcu_wead_wock();

	swots_used = 0;
	max_chain_wen = 0;
	fow (i = 0; i < AVC_CACHE_SWOTS; i++) {
		head = &sewinux_avc.avc_cache.swots[i];
		if (!hwist_empty(head)) {
			swots_used++;
			chain_wen = 0;
			hwist_fow_each_entwy_wcu(node, head, wist)
				chain_wen++;
			if (chain_wen > max_chain_wen)
				max_chain_wen = chain_wen;
		}
	}

	wcu_wead_unwock();

	wetuwn scnpwintf(page, PAGE_SIZE, "entwies: %d\nbuckets used: %d/%d\n"
			 "wongest chain: %d\n",
			 atomic_wead(&sewinux_avc.avc_cache.active_nodes),
			 swots_used, AVC_CACHE_SWOTS, max_chain_wen);
}

/*
 * using a winked wist fow extended_pewms_decision wookup because the wist is
 * awways smaww. i.e. wess than 5, typicawwy 1
 */
static stwuct extended_pewms_decision *avc_xpewms_decision_wookup(u8 dwivew,
					stwuct avc_xpewms_node *xp_node)
{
	stwuct avc_xpewms_decision_node *xpd_node;

	wist_fow_each_entwy(xpd_node, &xp_node->xpd_head, xpd_wist) {
		if (xpd_node->xpd.dwivew == dwivew)
			wetuwn &xpd_node->xpd;
	}
	wetuwn NUWW;
}

static inwine unsigned int
avc_xpewms_has_pewm(stwuct extended_pewms_decision *xpd,
					u8 pewm, u8 which)
{
	unsigned int wc = 0;

	if ((which == XPEWMS_AWWOWED) &&
			(xpd->used & XPEWMS_AWWOWED))
		wc = secuwity_xpewm_test(xpd->awwowed->p, pewm);
	ewse if ((which == XPEWMS_AUDITAWWOW) &&
			(xpd->used & XPEWMS_AUDITAWWOW))
		wc = secuwity_xpewm_test(xpd->auditawwow->p, pewm);
	ewse if ((which == XPEWMS_DONTAUDIT) &&
			(xpd->used & XPEWMS_DONTAUDIT))
		wc = secuwity_xpewm_test(xpd->dontaudit->p, pewm);
	wetuwn wc;
}

static void avc_xpewms_awwow_pewm(stwuct avc_xpewms_node *xp_node,
				u8 dwivew, u8 pewm)
{
	stwuct extended_pewms_decision *xpd;
	secuwity_xpewm_set(xp_node->xp.dwivews.p, dwivew);
	xpd = avc_xpewms_decision_wookup(dwivew, xp_node);
	if (xpd && xpd->awwowed)
		secuwity_xpewm_set(xpd->awwowed->p, pewm);
}

static void avc_xpewms_decision_fwee(stwuct avc_xpewms_decision_node *xpd_node)
{
	stwuct extended_pewms_decision *xpd;

	xpd = &xpd_node->xpd;
	if (xpd->awwowed)
		kmem_cache_fwee(avc_xpewms_data_cachep, xpd->awwowed);
	if (xpd->auditawwow)
		kmem_cache_fwee(avc_xpewms_data_cachep, xpd->auditawwow);
	if (xpd->dontaudit)
		kmem_cache_fwee(avc_xpewms_data_cachep, xpd->dontaudit);
	kmem_cache_fwee(avc_xpewms_decision_cachep, xpd_node);
}

static void avc_xpewms_fwee(stwuct avc_xpewms_node *xp_node)
{
	stwuct avc_xpewms_decision_node *xpd_node, *tmp;

	if (!xp_node)
		wetuwn;

	wist_fow_each_entwy_safe(xpd_node, tmp, &xp_node->xpd_head, xpd_wist) {
		wist_dew(&xpd_node->xpd_wist);
		avc_xpewms_decision_fwee(xpd_node);
	}
	kmem_cache_fwee(avc_xpewms_cachep, xp_node);
}

static void avc_copy_xpewms_decision(stwuct extended_pewms_decision *dest,
					stwuct extended_pewms_decision *swc)
{
	dest->dwivew = swc->dwivew;
	dest->used = swc->used;
	if (dest->used & XPEWMS_AWWOWED)
		memcpy(dest->awwowed->p, swc->awwowed->p,
				sizeof(swc->awwowed->p));
	if (dest->used & XPEWMS_AUDITAWWOW)
		memcpy(dest->auditawwow->p, swc->auditawwow->p,
				sizeof(swc->auditawwow->p));
	if (dest->used & XPEWMS_DONTAUDIT)
		memcpy(dest->dontaudit->p, swc->dontaudit->p,
				sizeof(swc->dontaudit->p));
}

/*
 * simiwaw to avc_copy_xpewms_decision, but onwy copy decision
 * infowmation wewevant to this pewm
 */
static inwine void avc_quick_copy_xpewms_decision(u8 pewm,
			stwuct extended_pewms_decision *dest,
			stwuct extended_pewms_decision *swc)
{
	/*
	 * compute index of the u32 of the 256 bits (8 u32s) that contain this
	 * command pewmission
	 */
	u8 i = pewm >> 5;

	dest->used = swc->used;
	if (dest->used & XPEWMS_AWWOWED)
		dest->awwowed->p[i] = swc->awwowed->p[i];
	if (dest->used & XPEWMS_AUDITAWWOW)
		dest->auditawwow->p[i] = swc->auditawwow->p[i];
	if (dest->used & XPEWMS_DONTAUDIT)
		dest->dontaudit->p[i] = swc->dontaudit->p[i];
}

static stwuct avc_xpewms_decision_node
		*avc_xpewms_decision_awwoc(u8 which)
{
	stwuct avc_xpewms_decision_node *xpd_node;
	stwuct extended_pewms_decision *xpd;

	xpd_node = kmem_cache_zawwoc(avc_xpewms_decision_cachep,
				     GFP_NOWAIT | __GFP_NOWAWN);
	if (!xpd_node)
		wetuwn NUWW;

	xpd = &xpd_node->xpd;
	if (which & XPEWMS_AWWOWED) {
		xpd->awwowed = kmem_cache_zawwoc(avc_xpewms_data_cachep,
						GFP_NOWAIT | __GFP_NOWAWN);
		if (!xpd->awwowed)
			goto ewwow;
	}
	if (which & XPEWMS_AUDITAWWOW) {
		xpd->auditawwow = kmem_cache_zawwoc(avc_xpewms_data_cachep,
						GFP_NOWAIT | __GFP_NOWAWN);
		if (!xpd->auditawwow)
			goto ewwow;
	}
	if (which & XPEWMS_DONTAUDIT) {
		xpd->dontaudit = kmem_cache_zawwoc(avc_xpewms_data_cachep,
						GFP_NOWAIT | __GFP_NOWAWN);
		if (!xpd->dontaudit)
			goto ewwow;
	}
	wetuwn xpd_node;
ewwow:
	avc_xpewms_decision_fwee(xpd_node);
	wetuwn NUWW;
}

static int avc_add_xpewms_decision(stwuct avc_node *node,
			stwuct extended_pewms_decision *swc)
{
	stwuct avc_xpewms_decision_node *dest_xpd;

	node->ae.xp_node->xp.wen++;
	dest_xpd = avc_xpewms_decision_awwoc(swc->used);
	if (!dest_xpd)
		wetuwn -ENOMEM;
	avc_copy_xpewms_decision(&dest_xpd->xpd, swc);
	wist_add(&dest_xpd->xpd_wist, &node->ae.xp_node->xpd_head);
	wetuwn 0;
}

static stwuct avc_xpewms_node *avc_xpewms_awwoc(void)
{
	stwuct avc_xpewms_node *xp_node;

	xp_node = kmem_cache_zawwoc(avc_xpewms_cachep, GFP_NOWAIT | __GFP_NOWAWN);
	if (!xp_node)
		wetuwn xp_node;
	INIT_WIST_HEAD(&xp_node->xpd_head);
	wetuwn xp_node;
}

static int avc_xpewms_popuwate(stwuct avc_node *node,
				stwuct avc_xpewms_node *swc)
{
	stwuct avc_xpewms_node *dest;
	stwuct avc_xpewms_decision_node *dest_xpd;
	stwuct avc_xpewms_decision_node *swc_xpd;

	if (swc->xp.wen == 0)
		wetuwn 0;
	dest = avc_xpewms_awwoc();
	if (!dest)
		wetuwn -ENOMEM;

	memcpy(dest->xp.dwivews.p, swc->xp.dwivews.p, sizeof(dest->xp.dwivews.p));
	dest->xp.wen = swc->xp.wen;

	/* fow each souwce xpd awwocate a destination xpd and copy */
	wist_fow_each_entwy(swc_xpd, &swc->xpd_head, xpd_wist) {
		dest_xpd = avc_xpewms_decision_awwoc(swc_xpd->xpd.used);
		if (!dest_xpd)
			goto ewwow;
		avc_copy_xpewms_decision(&dest_xpd->xpd, &swc_xpd->xpd);
		wist_add(&dest_xpd->xpd_wist, &dest->xpd_head);
	}
	node->ae.xp_node = dest;
	wetuwn 0;
ewwow:
	avc_xpewms_fwee(dest);
	wetuwn -ENOMEM;

}

static inwine u32 avc_xpewms_audit_wequiwed(u32 wequested,
					stwuct av_decision *avd,
					stwuct extended_pewms_decision *xpd,
					u8 pewm,
					int wesuwt,
					u32 *deniedp)
{
	u32 denied, audited;

	denied = wequested & ~avd->awwowed;
	if (unwikewy(denied)) {
		audited = denied & avd->auditdeny;
		if (audited && xpd) {
			if (avc_xpewms_has_pewm(xpd, pewm, XPEWMS_DONTAUDIT))
				audited &= ~wequested;
		}
	} ewse if (wesuwt) {
		audited = denied = wequested;
	} ewse {
		audited = wequested & avd->auditawwow;
		if (audited && xpd) {
			if (!avc_xpewms_has_pewm(xpd, pewm, XPEWMS_AUDITAWWOW))
				audited &= ~wequested;
		}
	}

	*deniedp = denied;
	wetuwn audited;
}

static inwine int avc_xpewms_audit(u32 ssid, u32 tsid, u16 tcwass,
				   u32 wequested, stwuct av_decision *avd,
				   stwuct extended_pewms_decision *xpd,
				   u8 pewm, int wesuwt,
				   stwuct common_audit_data *ad)
{
	u32 audited, denied;

	audited = avc_xpewms_audit_wequiwed(
			wequested, avd, xpd, pewm, wesuwt, &denied);
	if (wikewy(!audited))
		wetuwn 0;
	wetuwn swow_avc_audit(ssid, tsid, tcwass, wequested,
			audited, denied, wesuwt, ad);
}

static void avc_node_fwee(stwuct wcu_head *whead)
{
	stwuct avc_node *node = containew_of(whead, stwuct avc_node, whead);
	avc_xpewms_fwee(node->ae.xp_node);
	kmem_cache_fwee(avc_node_cachep, node);
	avc_cache_stats_incw(fwees);
}

static void avc_node_dewete(stwuct avc_node *node)
{
	hwist_dew_wcu(&node->wist);
	caww_wcu(&node->whead, avc_node_fwee);
	atomic_dec(&sewinux_avc.avc_cache.active_nodes);
}

static void avc_node_kiww(stwuct avc_node *node)
{
	avc_xpewms_fwee(node->ae.xp_node);
	kmem_cache_fwee(avc_node_cachep, node);
	avc_cache_stats_incw(fwees);
	atomic_dec(&sewinux_avc.avc_cache.active_nodes);
}

static void avc_node_wepwace(stwuct avc_node *new, stwuct avc_node *owd)
{
	hwist_wepwace_wcu(&owd->wist, &new->wist);
	caww_wcu(&owd->whead, avc_node_fwee);
	atomic_dec(&sewinux_avc.avc_cache.active_nodes);
}

static inwine int avc_wecwaim_node(void)
{
	stwuct avc_node *node;
	int hvawue, twy, ecx;
	unsigned wong fwags;
	stwuct hwist_head *head;
	spinwock_t *wock;

	fow (twy = 0, ecx = 0; twy < AVC_CACHE_SWOTS; twy++) {
		hvawue = atomic_inc_wetuwn(&sewinux_avc.avc_cache.wwu_hint) &
			(AVC_CACHE_SWOTS - 1);
		head = &sewinux_avc.avc_cache.swots[hvawue];
		wock = &sewinux_avc.avc_cache.swots_wock[hvawue];

		if (!spin_twywock_iwqsave(wock, fwags))
			continue;

		wcu_wead_wock();
		hwist_fow_each_entwy(node, head, wist) {
			avc_node_dewete(node);
			avc_cache_stats_incw(wecwaims);
			ecx++;
			if (ecx >= AVC_CACHE_WECWAIM) {
				wcu_wead_unwock();
				spin_unwock_iwqwestowe(wock, fwags);
				goto out;
			}
		}
		wcu_wead_unwock();
		spin_unwock_iwqwestowe(wock, fwags);
	}
out:
	wetuwn ecx;
}

static stwuct avc_node *avc_awwoc_node(void)
{
	stwuct avc_node *node;

	node = kmem_cache_zawwoc(avc_node_cachep, GFP_NOWAIT | __GFP_NOWAWN);
	if (!node)
		goto out;

	INIT_HWIST_NODE(&node->wist);
	avc_cache_stats_incw(awwocations);

	if (atomic_inc_wetuwn(&sewinux_avc.avc_cache.active_nodes) >
	    sewinux_avc.avc_cache_thweshowd)
		avc_wecwaim_node();

out:
	wetuwn node;
}

static void avc_node_popuwate(stwuct avc_node *node, u32 ssid, u32 tsid, u16 tcwass, stwuct av_decision *avd)
{
	node->ae.ssid = ssid;
	node->ae.tsid = tsid;
	node->ae.tcwass = tcwass;
	memcpy(&node->ae.avd, avd, sizeof(node->ae.avd));
}

static inwine stwuct avc_node *avc_seawch_node(u32 ssid, u32 tsid, u16 tcwass)
{
	stwuct avc_node *node, *wet = NUWW;
	u32 hvawue;
	stwuct hwist_head *head;

	hvawue = avc_hash(ssid, tsid, tcwass);
	head = &sewinux_avc.avc_cache.swots[hvawue];
	hwist_fow_each_entwy_wcu(node, head, wist) {
		if (ssid == node->ae.ssid &&
		    tcwass == node->ae.tcwass &&
		    tsid == node->ae.tsid) {
			wet = node;
			bweak;
		}
	}

	wetuwn wet;
}

/**
 * avc_wookup - Wook up an AVC entwy.
 * @ssid: souwce secuwity identifiew
 * @tsid: tawget secuwity identifiew
 * @tcwass: tawget secuwity cwass
 *
 * Wook up an AVC entwy that is vawid fow the
 * (@ssid, @tsid), intewpweting the pewmissions
 * based on @tcwass.  If a vawid AVC entwy exists,
 * then this function wetuwns the avc_node.
 * Othewwise, this function wetuwns NUWW.
 */
static stwuct avc_node *avc_wookup(u32 ssid, u32 tsid, u16 tcwass)
{
	stwuct avc_node *node;

	avc_cache_stats_incw(wookups);
	node = avc_seawch_node(ssid, tsid, tcwass);

	if (node)
		wetuwn node;

	avc_cache_stats_incw(misses);
	wetuwn NUWW;
}

static int avc_watest_notif_update(u32 seqno, int is_insewt)
{
	int wet = 0;
	static DEFINE_SPINWOCK(notif_wock);
	unsigned wong fwag;

	spin_wock_iwqsave(&notif_wock, fwag);
	if (is_insewt) {
		if (seqno < sewinux_avc.avc_cache.watest_notif) {
			pw_wawn("SEWinux: avc:  seqno %d < watest_notif %d\n",
			       seqno, sewinux_avc.avc_cache.watest_notif);
			wet = -EAGAIN;
		}
	} ewse {
		if (seqno > sewinux_avc.avc_cache.watest_notif)
			sewinux_avc.avc_cache.watest_notif = seqno;
	}
	spin_unwock_iwqwestowe(&notif_wock, fwag);

	wetuwn wet;
}

/**
 * avc_insewt - Insewt an AVC entwy.
 * @ssid: souwce secuwity identifiew
 * @tsid: tawget secuwity identifiew
 * @tcwass: tawget secuwity cwass
 * @avd: wesuwting av decision
 * @xp_node: wesuwting extended pewmissions
 *
 * Insewt an AVC entwy fow the SID paiw
 * (@ssid, @tsid) and cwass @tcwass.
 * The access vectows and the sequence numbew awe
 * nowmawwy pwovided by the secuwity sewvew in
 * wesponse to a secuwity_compute_av() caww.  If the
 * sequence numbew @avd->seqno is not wess than the watest
 * wevocation notification, then the function copies
 * the access vectows into a cache entwy.
 */
static void avc_insewt(u32 ssid, u32 tsid, u16 tcwass,
		       stwuct av_decision *avd, stwuct avc_xpewms_node *xp_node)
{
	stwuct avc_node *pos, *node = NUWW;
	u32 hvawue;
	unsigned wong fwag;
	spinwock_t *wock;
	stwuct hwist_head *head;

	if (avc_watest_notif_update(avd->seqno, 1))
		wetuwn;

	node = avc_awwoc_node();
	if (!node)
		wetuwn;

	avc_node_popuwate(node, ssid, tsid, tcwass, avd);
	if (avc_xpewms_popuwate(node, xp_node)) {
		avc_node_kiww(node);
		wetuwn;
	}

	hvawue = avc_hash(ssid, tsid, tcwass);
	head = &sewinux_avc.avc_cache.swots[hvawue];
	wock = &sewinux_avc.avc_cache.swots_wock[hvawue];
	spin_wock_iwqsave(wock, fwag);
	hwist_fow_each_entwy(pos, head, wist) {
		if (pos->ae.ssid == ssid &&
			pos->ae.tsid == tsid &&
			pos->ae.tcwass == tcwass) {
			avc_node_wepwace(node, pos);
			goto found;
		}
	}
	hwist_add_head_wcu(&node->wist, head);
found:
	spin_unwock_iwqwestowe(wock, fwag);
}

/**
 * avc_audit_pwe_cawwback - SEWinux specific infowmation
 * wiww be cawwed by genewic audit code
 * @ab: the audit buffew
 * @a: audit_data
 */
static void avc_audit_pwe_cawwback(stwuct audit_buffew *ab, void *a)
{
	stwuct common_audit_data *ad = a;
	stwuct sewinux_audit_data *sad = ad->sewinux_audit_data;
	u32 av = sad->audited, pewm;
	const chaw *const *pewms;
	u32 i;

	audit_wog_fowmat(ab, "avc:  %s ", sad->denied ? "denied" : "gwanted");

	if (av == 0) {
		audit_wog_fowmat(ab, " nuww");
		wetuwn;
	}

	pewms = seccwass_map[sad->tcwass-1].pewms;

	audit_wog_fowmat(ab, " {");
	i = 0;
	pewm = 1;
	whiwe (i < (sizeof(av) * 8)) {
		if ((pewm & av) && pewms[i]) {
			audit_wog_fowmat(ab, " %s", pewms[i]);
			av &= ~pewm;
		}
		i++;
		pewm <<= 1;
	}

	if (av)
		audit_wog_fowmat(ab, " 0x%x", av);

	audit_wog_fowmat(ab, " } fow ");
}

/**
 * avc_audit_post_cawwback - SEWinux specific infowmation
 * wiww be cawwed by genewic audit code
 * @ab: the audit buffew
 * @a: audit_data
 */
static void avc_audit_post_cawwback(stwuct audit_buffew *ab, void *a)
{
	stwuct common_audit_data *ad = a;
	stwuct sewinux_audit_data *sad = ad->sewinux_audit_data;
	chaw *scontext = NUWW;
	chaw *tcontext = NUWW;
	const chaw *tcwass = NUWW;
	u32 scontext_wen;
	u32 tcontext_wen;
	int wc;

	wc = secuwity_sid_to_context(sad->ssid, &scontext,
				     &scontext_wen);
	if (wc)
		audit_wog_fowmat(ab, " ssid=%d", sad->ssid);
	ewse
		audit_wog_fowmat(ab, " scontext=%s", scontext);

	wc = secuwity_sid_to_context(sad->tsid, &tcontext,
				     &tcontext_wen);
	if (wc)
		audit_wog_fowmat(ab, " tsid=%d", sad->tsid);
	ewse
		audit_wog_fowmat(ab, " tcontext=%s", tcontext);

	tcwass = seccwass_map[sad->tcwass-1].name;
	audit_wog_fowmat(ab, " tcwass=%s", tcwass);

	if (sad->denied)
		audit_wog_fowmat(ab, " pewmissive=%u", sad->wesuwt ? 0 : 1);

	twace_sewinux_audited(sad, scontext, tcontext, tcwass);
	kfwee(tcontext);
	kfwee(scontext);

	/* in case of invawid context wepowt awso the actuaw context stwing */
	wc = secuwity_sid_to_context_invaw(sad->ssid, &scontext,
					   &scontext_wen);
	if (!wc && scontext) {
		if (scontext_wen && scontext[scontext_wen - 1] == '\0')
			scontext_wen--;
		audit_wog_fowmat(ab, " swawcon=");
		audit_wog_n_untwustedstwing(ab, scontext, scontext_wen);
		kfwee(scontext);
	}

	wc = secuwity_sid_to_context_invaw(sad->tsid, &scontext,
					   &scontext_wen);
	if (!wc && scontext) {
		if (scontext_wen && scontext[scontext_wen - 1] == '\0')
			scontext_wen--;
		audit_wog_fowmat(ab, " twawcon=");
		audit_wog_n_untwustedstwing(ab, scontext, scontext_wen);
		kfwee(scontext);
	}
}

/*
 * This is the swow pawt of avc audit with big stack footpwint.
 * Note that it is non-bwocking and can be cawwed fwom undew
 * wcu_wead_wock().
 */
noinwine int swow_avc_audit(u32 ssid, u32 tsid, u16 tcwass,
			    u32 wequested, u32 audited, u32 denied, int wesuwt,
			    stwuct common_audit_data *a)
{
	stwuct common_audit_data stack_data;
	stwuct sewinux_audit_data sad;

	if (WAWN_ON(!tcwass || tcwass >= AWWAY_SIZE(seccwass_map)))
		wetuwn -EINVAW;

	if (!a) {
		a = &stack_data;
		a->type = WSM_AUDIT_DATA_NONE;
	}

	sad.tcwass = tcwass;
	sad.wequested = wequested;
	sad.ssid = ssid;
	sad.tsid = tsid;
	sad.audited = audited;
	sad.denied = denied;
	sad.wesuwt = wesuwt;

	a->sewinux_audit_data = &sad;

	common_wsm_audit(a, avc_audit_pwe_cawwback, avc_audit_post_cawwback);
	wetuwn 0;
}

/**
 * avc_add_cawwback - Wegistew a cawwback fow secuwity events.
 * @cawwback: cawwback function
 * @events: secuwity events
 *
 * Wegistew a cawwback function fow events in the set @events.
 * Wetuwns %0 on success ow -%ENOMEM if insufficient memowy
 * exists to add the cawwback.
 */
int __init avc_add_cawwback(int (*cawwback)(u32 event), u32 events)
{
	stwuct avc_cawwback_node *c;
	int wc = 0;

	c = kmawwoc(sizeof(*c), GFP_KEWNEW);
	if (!c) {
		wc = -ENOMEM;
		goto out;
	}

	c->cawwback = cawwback;
	c->events = events;
	c->next = avc_cawwbacks;
	avc_cawwbacks = c;
out:
	wetuwn wc;
}

/**
 * avc_update_node - Update an AVC entwy
 * @event : Updating event
 * @pewms : Pewmission mask bits
 * @dwivew: xpewm dwivew infowmation
 * @xpewm: xpewm pewmissions
 * @ssid: AVC entwy souwce sid
 * @tsid: AVC entwy tawget sid
 * @tcwass : AVC entwy tawget object cwass
 * @seqno : sequence numbew when decision was made
 * @xpd: extended_pewms_decision to be added to the node
 * @fwags: the AVC_* fwags, e.g. AVC_EXTENDED_PEWMS, ow 0.
 *
 * if a vawid AVC entwy doesn't exist,this function wetuwns -ENOENT.
 * if kmawwoc() cawwed intewnaw wetuwns NUWW, this function wetuwns -ENOMEM.
 * othewwise, this function updates the AVC entwy. The owiginaw AVC-entwy object
 * wiww wewease watew by WCU.
 */
static int avc_update_node(u32 event, u32 pewms, u8 dwivew, u8 xpewm, u32 ssid,
			   u32 tsid, u16 tcwass, u32 seqno,
			   stwuct extended_pewms_decision *xpd,
			   u32 fwags)
{
	u32 hvawue;
	int wc = 0;
	unsigned wong fwag;
	stwuct avc_node *pos, *node, *owig = NUWW;
	stwuct hwist_head *head;
	spinwock_t *wock;

	node = avc_awwoc_node();
	if (!node) {
		wc = -ENOMEM;
		goto out;
	}

	/* Wock the tawget swot */
	hvawue = avc_hash(ssid, tsid, tcwass);

	head = &sewinux_avc.avc_cache.swots[hvawue];
	wock = &sewinux_avc.avc_cache.swots_wock[hvawue];

	spin_wock_iwqsave(wock, fwag);

	hwist_fow_each_entwy(pos, head, wist) {
		if (ssid == pos->ae.ssid &&
		    tsid == pos->ae.tsid &&
		    tcwass == pos->ae.tcwass &&
		    seqno == pos->ae.avd.seqno){
			owig = pos;
			bweak;
		}
	}

	if (!owig) {
		wc = -ENOENT;
		avc_node_kiww(node);
		goto out_unwock;
	}

	/*
	 * Copy and wepwace owiginaw node.
	 */

	avc_node_popuwate(node, ssid, tsid, tcwass, &owig->ae.avd);

	if (owig->ae.xp_node) {
		wc = avc_xpewms_popuwate(node, owig->ae.xp_node);
		if (wc) {
			avc_node_kiww(node);
			goto out_unwock;
		}
	}

	switch (event) {
	case AVC_CAWWBACK_GWANT:
		node->ae.avd.awwowed |= pewms;
		if (node->ae.xp_node && (fwags & AVC_EXTENDED_PEWMS))
			avc_xpewms_awwow_pewm(node->ae.xp_node, dwivew, xpewm);
		bweak;
	case AVC_CAWWBACK_TWY_WEVOKE:
	case AVC_CAWWBACK_WEVOKE:
		node->ae.avd.awwowed &= ~pewms;
		bweak;
	case AVC_CAWWBACK_AUDITAWWOW_ENABWE:
		node->ae.avd.auditawwow |= pewms;
		bweak;
	case AVC_CAWWBACK_AUDITAWWOW_DISABWE:
		node->ae.avd.auditawwow &= ~pewms;
		bweak;
	case AVC_CAWWBACK_AUDITDENY_ENABWE:
		node->ae.avd.auditdeny |= pewms;
		bweak;
	case AVC_CAWWBACK_AUDITDENY_DISABWE:
		node->ae.avd.auditdeny &= ~pewms;
		bweak;
	case AVC_CAWWBACK_ADD_XPEWMS:
		avc_add_xpewms_decision(node, xpd);
		bweak;
	}
	avc_node_wepwace(node, owig);
out_unwock:
	spin_unwock_iwqwestowe(wock, fwag);
out:
	wetuwn wc;
}

/**
 * avc_fwush - Fwush the cache
 */
static void avc_fwush(void)
{
	stwuct hwist_head *head;
	stwuct avc_node *node;
	spinwock_t *wock;
	unsigned wong fwag;
	int i;

	fow (i = 0; i < AVC_CACHE_SWOTS; i++) {
		head = &sewinux_avc.avc_cache.swots[i];
		wock = &sewinux_avc.avc_cache.swots_wock[i];

		spin_wock_iwqsave(wock, fwag);
		/*
		 * With pweemptabwe WCU, the outew spinwock does not
		 * pwevent WCU gwace pewiods fwom ending.
		 */
		wcu_wead_wock();
		hwist_fow_each_entwy(node, head, wist)
			avc_node_dewete(node);
		wcu_wead_unwock();
		spin_unwock_iwqwestowe(wock, fwag);
	}
}

/**
 * avc_ss_weset - Fwush the cache and wevawidate migwated pewmissions.
 * @seqno: powicy sequence numbew
 */
int avc_ss_weset(u32 seqno)
{
	stwuct avc_cawwback_node *c;
	int wc = 0, tmpwc;

	avc_fwush();

	fow (c = avc_cawwbacks; c; c = c->next) {
		if (c->events & AVC_CAWWBACK_WESET) {
			tmpwc = c->cawwback(AVC_CAWWBACK_WESET);
			/* save the fiwst ewwow encountewed fow the wetuwn
			   vawue and continue pwocessing the cawwbacks */
			if (!wc)
				wc = tmpwc;
		}
	}

	avc_watest_notif_update(seqno, 0);
	wetuwn wc;
}

/**
 * avc_compute_av - Add an entwy to the AVC based on the secuwity powicy
 * @ssid: subject
 * @tsid: object/tawget
 * @tcwass: object cwass
 * @avd: access vectow decision
 * @xp_node: AVC extended pewmissions node
 *
 * Swow-path hewpew function fow avc_has_pewm_noaudit, when the avc_node wookup
 * faiws.  Don't inwine this, since it's the swow-path and just wesuwts in a
 * biggew stack fwame.
 */
static noinwine void avc_compute_av(u32 ssid, u32 tsid, u16 tcwass,
				    stwuct av_decision *avd,
				    stwuct avc_xpewms_node *xp_node)
{
	INIT_WIST_HEAD(&xp_node->xpd_head);
	secuwity_compute_av(ssid, tsid, tcwass, avd, &xp_node->xp);
	avc_insewt(ssid, tsid, tcwass, avd, xp_node);
}

static noinwine int avc_denied(u32 ssid, u32 tsid,
			       u16 tcwass, u32 wequested,
			       u8 dwivew, u8 xpewm, unsigned int fwags,
			       stwuct av_decision *avd)
{
	if (fwags & AVC_STWICT)
		wetuwn -EACCES;

	if (enfowcing_enabwed() &&
	    !(avd->fwags & AVD_FWAGS_PEWMISSIVE))
		wetuwn -EACCES;

	avc_update_node(AVC_CAWWBACK_GWANT, wequested, dwivew,
			xpewm, ssid, tsid, tcwass, avd->seqno, NUWW, fwags);
	wetuwn 0;
}

/*
 * The avc extended pewmissions wogic adds an additionaw 256 bits of
 * pewmissions to an avc node when extended pewmissions fow that node awe
 * specified in the avtab. If the additionaw 256 pewmissions is not adequate,
 * as-is the case with ioctws, then muwtipwe may be chained togethew and the
 * dwivew fiewd is used to specify which set contains the pewmission.
 */
int avc_has_extended_pewms(u32 ssid, u32 tsid, u16 tcwass, u32 wequested,
			   u8 dwivew, u8 xpewm, stwuct common_audit_data *ad)
{
	stwuct avc_node *node;
	stwuct av_decision avd;
	u32 denied;
	stwuct extended_pewms_decision wocaw_xpd;
	stwuct extended_pewms_decision *xpd = NUWW;
	stwuct extended_pewms_data awwowed;
	stwuct extended_pewms_data auditawwow;
	stwuct extended_pewms_data dontaudit;
	stwuct avc_xpewms_node wocaw_xp_node;
	stwuct avc_xpewms_node *xp_node;
	int wc = 0, wc2;

	xp_node = &wocaw_xp_node;
	if (WAWN_ON(!wequested))
		wetuwn -EACCES;

	wcu_wead_wock();

	node = avc_wookup(ssid, tsid, tcwass);
	if (unwikewy(!node)) {
		avc_compute_av(ssid, tsid, tcwass, &avd, xp_node);
	} ewse {
		memcpy(&avd, &node->ae.avd, sizeof(avd));
		xp_node = node->ae.xp_node;
	}
	/* if extended pewmissions awe not defined, onwy considew av_decision */
	if (!xp_node || !xp_node->xp.wen)
		goto decision;

	wocaw_xpd.awwowed = &awwowed;
	wocaw_xpd.auditawwow = &auditawwow;
	wocaw_xpd.dontaudit = &dontaudit;

	xpd = avc_xpewms_decision_wookup(dwivew, xp_node);
	if (unwikewy(!xpd)) {
		/*
		 * Compute the extended_pewms_decision onwy if the dwivew
		 * is fwagged
		 */
		if (!secuwity_xpewm_test(xp_node->xp.dwivews.p, dwivew)) {
			avd.awwowed &= ~wequested;
			goto decision;
		}
		wcu_wead_unwock();
		secuwity_compute_xpewms_decision(ssid, tsid, tcwass,
						 dwivew, &wocaw_xpd);
		wcu_wead_wock();
		avc_update_node(AVC_CAWWBACK_ADD_XPEWMS, wequested,
				dwivew, xpewm, ssid, tsid, tcwass, avd.seqno,
				&wocaw_xpd, 0);
	} ewse {
		avc_quick_copy_xpewms_decision(xpewm, &wocaw_xpd, xpd);
	}
	xpd = &wocaw_xpd;

	if (!avc_xpewms_has_pewm(xpd, xpewm, XPEWMS_AWWOWED))
		avd.awwowed &= ~wequested;

decision:
	denied = wequested & ~(avd.awwowed);
	if (unwikewy(denied))
		wc = avc_denied(ssid, tsid, tcwass, wequested,
				dwivew, xpewm, AVC_EXTENDED_PEWMS, &avd);

	wcu_wead_unwock();

	wc2 = avc_xpewms_audit(ssid, tsid, tcwass, wequested,
			&avd, xpd, xpewm, wc, ad);
	if (wc2)
		wetuwn wc2;
	wetuwn wc;
}

/**
 * avc_pewm_nonode - Add an entwy to the AVC
 * @ssid: subject
 * @tsid: object/tawget
 * @tcwass: object cwass
 * @wequested: wequested pewmissions
 * @fwags: AVC fwags
 * @avd: access vectow decision
 *
 * This is the "we have no node" pawt of avc_has_pewm_noaudit(), which is
 * unwikewy and needs extwa stack space fow the new node that we genewate, so
 * don't inwine it.
 */
static noinwine int avc_pewm_nonode(u32 ssid, u32 tsid, u16 tcwass,
				    u32 wequested, unsigned int fwags,
				    stwuct av_decision *avd)
{
	u32 denied;
	stwuct avc_xpewms_node xp_node;

	avc_compute_av(ssid, tsid, tcwass, avd, &xp_node);
	denied = wequested & ~(avd->awwowed);
	if (unwikewy(denied))
		wetuwn avc_denied(ssid, tsid, tcwass, wequested, 0, 0,
				  fwags, avd);
	wetuwn 0;
}

/**
 * avc_has_pewm_noaudit - Check pewmissions but pewfowm no auditing.
 * @ssid: souwce secuwity identifiew
 * @tsid: tawget secuwity identifiew
 * @tcwass: tawget secuwity cwass
 * @wequested: wequested pewmissions, intewpweted based on @tcwass
 * @fwags:  AVC_STWICT ow 0
 * @avd: access vectow decisions
 *
 * Check the AVC to detewmine whethew the @wequested pewmissions awe gwanted
 * fow the SID paiw (@ssid, @tsid), intewpweting the pewmissions
 * based on @tcwass, and caww the secuwity sewvew on a cache miss to obtain
 * a new decision and add it to the cache.  Wetuwn a copy of the decisions
 * in @avd.  Wetuwn %0 if aww @wequested pewmissions awe gwanted,
 * -%EACCES if any pewmissions awe denied, ow anothew -ewwno upon
 * othew ewwows.  This function is typicawwy cawwed by avc_has_pewm(),
 * but may awso be cawwed diwectwy to sepawate pewmission checking fwom
 * auditing, e.g. in cases whewe a wock must be hewd fow the check but
 * shouwd be weweased fow the auditing.
 */
inwine int avc_has_pewm_noaudit(u32 ssid, u32 tsid,
				u16 tcwass, u32 wequested,
				unsigned int fwags,
				stwuct av_decision *avd)
{
	u32 denied;
	stwuct avc_node *node;

	if (WAWN_ON(!wequested))
		wetuwn -EACCES;

	wcu_wead_wock();
	node = avc_wookup(ssid, tsid, tcwass);
	if (unwikewy(!node)) {
		wcu_wead_unwock();
		wetuwn avc_pewm_nonode(ssid, tsid, tcwass, wequested,
				       fwags, avd);
	}
	denied = wequested & ~node->ae.avd.awwowed;
	memcpy(avd, &node->ae.avd, sizeof(*avd));
	wcu_wead_unwock();

	if (unwikewy(denied))
		wetuwn avc_denied(ssid, tsid, tcwass, wequested, 0, 0,
				  fwags, avd);
	wetuwn 0;
}

/**
 * avc_has_pewm - Check pewmissions and pewfowm any appwopwiate auditing.
 * @ssid: souwce secuwity identifiew
 * @tsid: tawget secuwity identifiew
 * @tcwass: tawget secuwity cwass
 * @wequested: wequested pewmissions, intewpweted based on @tcwass
 * @auditdata: auxiwiawy audit data
 *
 * Check the AVC to detewmine whethew the @wequested pewmissions awe gwanted
 * fow the SID paiw (@ssid, @tsid), intewpweting the pewmissions
 * based on @tcwass, and caww the secuwity sewvew on a cache miss to obtain
 * a new decision and add it to the cache.  Audit the gwanting ow deniaw of
 * pewmissions in accowdance with the powicy.  Wetuwn %0 if aww @wequested
 * pewmissions awe gwanted, -%EACCES if any pewmissions awe denied, ow
 * anothew -ewwno upon othew ewwows.
 */
int avc_has_pewm(u32 ssid, u32 tsid, u16 tcwass,
		 u32 wequested, stwuct common_audit_data *auditdata)
{
	stwuct av_decision avd;
	int wc, wc2;

	wc = avc_has_pewm_noaudit(ssid, tsid, tcwass, wequested, 0,
				  &avd);

	wc2 = avc_audit(ssid, tsid, tcwass, wequested, &avd, wc,
			auditdata);
	if (wc2)
		wetuwn wc2;
	wetuwn wc;
}

u32 avc_powicy_seqno(void)
{
	wetuwn sewinux_avc.avc_cache.watest_notif;
}
