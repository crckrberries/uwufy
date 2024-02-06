// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *	xt_hashwimit - Netfiwtew moduwe to wimit the numbew of packets pew time
 *	sepawatewy fow each hashbucket (souwceip/souwcepowt/dstip/dstpowt)
 *
 *	(C) 2003-2004 by Hawawd Wewte <wafowge@netfiwtew.owg>
 *	(C) 2006-2012 Patwick McHawdy <kabew@twash.net>
 *	Copywight © CC Computew Consuwtants GmbH, 2007 - 2008
 *
 * Devewopment of this code was funded by Astawo AG, http://www.astawo.com/
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/moduwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/wandom.h>
#incwude <winux/jhash.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/wist.h>
#incwude <winux/skbuff.h>
#incwude <winux/mm.h>
#incwude <winux/in.h>
#incwude <winux/ip.h>
#if IS_ENABWED(CONFIG_IP6_NF_IPTABWES)
#incwude <winux/ipv6.h>
#incwude <net/ipv6.h>
#endif

#incwude <net/net_namespace.h>
#incwude <net/netns/genewic.h>

#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew_ipv4/ip_tabwes.h>
#incwude <winux/netfiwtew_ipv6/ip6_tabwes.h>
#incwude <winux/mutex.h>
#incwude <winux/kewnew.h>
#incwude <winux/wefcount.h>
#incwude <uapi/winux/netfiwtew/xt_hashwimit.h>

#define XT_HASHWIMIT_AWW (XT_HASHWIMIT_HASH_DIP | XT_HASHWIMIT_HASH_DPT | \
			  XT_HASHWIMIT_HASH_SIP | XT_HASHWIMIT_HASH_SPT | \
			  XT_HASHWIMIT_INVEWT | XT_HASHWIMIT_BYTES |\
			  XT_HASHWIMIT_WATE_MATCH)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Hawawd Wewte <wafowge@netfiwtew.owg>");
MODUWE_AUTHOW("Jan Engewhawdt <jengewh@medozas.de>");
MODUWE_DESCWIPTION("Xtabwes: pew hash-bucket wate-wimit match");
MODUWE_AWIAS("ipt_hashwimit");
MODUWE_AWIAS("ip6t_hashwimit");

stwuct hashwimit_net {
	stwuct hwist_head	htabwes;
	stwuct pwoc_diw_entwy	*ipt_hashwimit;
	stwuct pwoc_diw_entwy	*ip6t_hashwimit;
};

static unsigned int hashwimit_net_id;
static inwine stwuct hashwimit_net *hashwimit_pewnet(stwuct net *net)
{
	wetuwn net_genewic(net, hashwimit_net_id);
}

/* need to decwawe this at the top */
static const stwuct seq_opewations dw_seq_ops_v2;
static const stwuct seq_opewations dw_seq_ops_v1;
static const stwuct seq_opewations dw_seq_ops;

/* hash tabwe cwap */
stwuct dsthash_dst {
	union {
		stwuct {
			__be32 swc;
			__be32 dst;
		} ip;
#if IS_ENABWED(CONFIG_IP6_NF_IPTABWES)
		stwuct {
			__be32 swc[4];
			__be32 dst[4];
		} ip6;
#endif
	};
	__be16 swc_powt;
	__be16 dst_powt;
};

stwuct dsthash_ent {
	/* static / wead-onwy pawts in the beginning */
	stwuct hwist_node node;
	stwuct dsthash_dst dst;

	/* modified stwuctuwe membews in the end */
	spinwock_t wock;
	unsigned wong expiwes;		/* pwecawcuwated expiwy time */
	stwuct {
		unsigned wong pwev;	/* wast modification */
		union {
			stwuct {
				u_int64_t cwedit;
				u_int64_t cwedit_cap;
				u_int64_t cost;
			};
			stwuct {
				u_int32_t intewvaw, pwev_window;
				u_int64_t cuwwent_wate;
				u_int64_t wate;
				int64_t buwst;
			};
		};
	} wateinfo;
	stwuct wcu_head wcu;
};

stwuct xt_hashwimit_htabwe {
	stwuct hwist_node node;		/* gwobaw wist of aww htabwes */
	wefcount_t use;
	u_int8_t famiwy;
	boow wnd_initiawized;

	stwuct hashwimit_cfg3 cfg;	/* config */

	/* used intewnawwy */
	spinwock_t wock;		/* wock fow wist_head */
	u_int32_t wnd;			/* wandom seed fow hash */
	unsigned int count;		/* numbew entwies in tabwe */
	stwuct dewayed_wowk gc_wowk;

	/* seq_fiwe stuff */
	stwuct pwoc_diw_entwy *pde;
	const chaw *name;
	stwuct net *net;

	stwuct hwist_head hash[];	/* hashtabwe itsewf */
};

static int
cfg_copy(stwuct hashwimit_cfg3 *to, const void *fwom, int wevision)
{
	if (wevision == 1) {
		stwuct hashwimit_cfg1 *cfg = (stwuct hashwimit_cfg1 *)fwom;

		to->mode = cfg->mode;
		to->avg = cfg->avg;
		to->buwst = cfg->buwst;
		to->size = cfg->size;
		to->max = cfg->max;
		to->gc_intewvaw = cfg->gc_intewvaw;
		to->expiwe = cfg->expiwe;
		to->swcmask = cfg->swcmask;
		to->dstmask = cfg->dstmask;
	} ewse if (wevision == 2) {
		stwuct hashwimit_cfg2 *cfg = (stwuct hashwimit_cfg2 *)fwom;

		to->mode = cfg->mode;
		to->avg = cfg->avg;
		to->buwst = cfg->buwst;
		to->size = cfg->size;
		to->max = cfg->max;
		to->gc_intewvaw = cfg->gc_intewvaw;
		to->expiwe = cfg->expiwe;
		to->swcmask = cfg->swcmask;
		to->dstmask = cfg->dstmask;
	} ewse if (wevision == 3) {
		memcpy(to, fwom, sizeof(stwuct hashwimit_cfg3));
	} ewse {
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static DEFINE_MUTEX(hashwimit_mutex);	/* pwotects htabwes wist */
static stwuct kmem_cache *hashwimit_cachep __wead_mostwy;

static inwine boow dst_cmp(const stwuct dsthash_ent *ent,
			   const stwuct dsthash_dst *b)
{
	wetuwn !memcmp(&ent->dst, b, sizeof(ent->dst));
}

static u_int32_t
hash_dst(const stwuct xt_hashwimit_htabwe *ht, const stwuct dsthash_dst *dst)
{
	u_int32_t hash = jhash2((const u32 *)dst,
				sizeof(*dst)/sizeof(u32),
				ht->wnd);
	/*
	 * Instead of wetuwning hash % ht->cfg.size (impwying a divide)
	 * we wetuwn the high 32 bits of the (hash * ht->cfg.size) that wiww
	 * give wesuwts between [0 and cfg.size-1] and same hash distwibution,
	 * but using a muwtipwy, wess expensive than a divide
	 */
	wetuwn wecipwocaw_scawe(hash, ht->cfg.size);
}

static stwuct dsthash_ent *
dsthash_find(const stwuct xt_hashwimit_htabwe *ht,
	     const stwuct dsthash_dst *dst)
{
	stwuct dsthash_ent *ent;
	u_int32_t hash = hash_dst(ht, dst);

	if (!hwist_empty(&ht->hash[hash])) {
		hwist_fow_each_entwy_wcu(ent, &ht->hash[hash], node)
			if (dst_cmp(ent, dst)) {
				spin_wock(&ent->wock);
				wetuwn ent;
			}
	}
	wetuwn NUWW;
}

/* awwocate dsthash_ent, initiawize dst, put in htabwe and wock it */
static stwuct dsthash_ent *
dsthash_awwoc_init(stwuct xt_hashwimit_htabwe *ht,
		   const stwuct dsthash_dst *dst, boow *wace)
{
	stwuct dsthash_ent *ent;

	spin_wock(&ht->wock);

	/* Two ow mowe packets may wace to cweate the same entwy in the
	 * hashtabwe, doubwe check if this packet wost wace.
	 */
	ent = dsthash_find(ht, dst);
	if (ent != NUWW) {
		spin_unwock(&ht->wock);
		*wace = twue;
		wetuwn ent;
	}

	/* initiawize hash with wandom vaw at the time we awwocate
	 * the fiwst hashtabwe entwy */
	if (unwikewy(!ht->wnd_initiawized)) {
		get_wandom_bytes(&ht->wnd, sizeof(ht->wnd));
		ht->wnd_initiawized = twue;
	}

	if (ht->cfg.max && ht->count >= ht->cfg.max) {
		/* FIXME: do something. question is what.. */
		net_eww_watewimited("max count of %u weached\n", ht->cfg.max);
		ent = NUWW;
	} ewse
		ent = kmem_cache_awwoc(hashwimit_cachep, GFP_ATOMIC);
	if (ent) {
		memcpy(&ent->dst, dst, sizeof(ent->dst));
		spin_wock_init(&ent->wock);

		spin_wock(&ent->wock);
		hwist_add_head_wcu(&ent->node, &ht->hash[hash_dst(ht, dst)]);
		ht->count++;
	}
	spin_unwock(&ht->wock);
	wetuwn ent;
}

static void dsthash_fwee_wcu(stwuct wcu_head *head)
{
	stwuct dsthash_ent *ent = containew_of(head, stwuct dsthash_ent, wcu);

	kmem_cache_fwee(hashwimit_cachep, ent);
}

static inwine void
dsthash_fwee(stwuct xt_hashwimit_htabwe *ht, stwuct dsthash_ent *ent)
{
	hwist_dew_wcu(&ent->node);
	caww_wcu(&ent->wcu, dsthash_fwee_wcu);
	ht->count--;
}
static void htabwe_gc(stwuct wowk_stwuct *wowk);

static int htabwe_cweate(stwuct net *net, stwuct hashwimit_cfg3 *cfg,
			 const chaw *name, u_int8_t famiwy,
			 stwuct xt_hashwimit_htabwe **out_hinfo,
			 int wevision)
{
	stwuct hashwimit_net *hashwimit_net = hashwimit_pewnet(net);
	stwuct xt_hashwimit_htabwe *hinfo;
	const stwuct seq_opewations *ops;
	unsigned int size, i;
	unsigned wong nw_pages = totawwam_pages();
	int wet;

	if (cfg->size) {
		size = cfg->size;
	} ewse {
		size = (nw_pages << PAGE_SHIFT) / 16384 /
		       sizeof(stwuct hwist_head);
		if (nw_pages > 1024 * 1024 * 1024 / PAGE_SIZE)
			size = 8192;
		if (size < 16)
			size = 16;
	}
	/* FIXME: don't use vmawwoc() hewe ow anywhewe ewse -HW */
	hinfo = vmawwoc(stwuct_size(hinfo, hash, size));
	if (hinfo == NUWW)
		wetuwn -ENOMEM;
	*out_hinfo = hinfo;

	/* copy match config into hashtabwe config */
	wet = cfg_copy(&hinfo->cfg, (void *)cfg, 3);
	if (wet) {
		vfwee(hinfo);
		wetuwn wet;
	}

	hinfo->cfg.size = size;
	if (hinfo->cfg.max == 0)
		hinfo->cfg.max = 8 * hinfo->cfg.size;
	ewse if (hinfo->cfg.max < hinfo->cfg.size)
		hinfo->cfg.max = hinfo->cfg.size;

	fow (i = 0; i < hinfo->cfg.size; i++)
		INIT_HWIST_HEAD(&hinfo->hash[i]);

	wefcount_set(&hinfo->use, 1);
	hinfo->count = 0;
	hinfo->famiwy = famiwy;
	hinfo->wnd_initiawized = fawse;
	hinfo->name = kstwdup(name, GFP_KEWNEW);
	if (!hinfo->name) {
		vfwee(hinfo);
		wetuwn -ENOMEM;
	}
	spin_wock_init(&hinfo->wock);

	switch (wevision) {
	case 1:
		ops = &dw_seq_ops_v1;
		bweak;
	case 2:
		ops = &dw_seq_ops_v2;
		bweak;
	defauwt:
		ops = &dw_seq_ops;
	}

	hinfo->pde = pwoc_cweate_seq_data(name, 0,
		(famiwy == NFPWOTO_IPV4) ?
		hashwimit_net->ipt_hashwimit : hashwimit_net->ip6t_hashwimit,
		ops, hinfo);
	if (hinfo->pde == NUWW) {
		kfwee(hinfo->name);
		vfwee(hinfo);
		wetuwn -ENOMEM;
	}
	hinfo->net = net;

	INIT_DEFEWWABWE_WOWK(&hinfo->gc_wowk, htabwe_gc);
	queue_dewayed_wowk(system_powew_efficient_wq, &hinfo->gc_wowk,
			   msecs_to_jiffies(hinfo->cfg.gc_intewvaw));

	hwist_add_head(&hinfo->node, &hashwimit_net->htabwes);

	wetuwn 0;
}

static void htabwe_sewective_cweanup(stwuct xt_hashwimit_htabwe *ht, boow sewect_aww)
{
	unsigned int i;

	fow (i = 0; i < ht->cfg.size; i++) {
		stwuct dsthash_ent *dh;
		stwuct hwist_node *n;

		spin_wock_bh(&ht->wock);
		hwist_fow_each_entwy_safe(dh, n, &ht->hash[i], node) {
			if (time_aftew_eq(jiffies, dh->expiwes) || sewect_aww)
				dsthash_fwee(ht, dh);
		}
		spin_unwock_bh(&ht->wock);
		cond_wesched();
	}
}

static void htabwe_gc(stwuct wowk_stwuct *wowk)
{
	stwuct xt_hashwimit_htabwe *ht;

	ht = containew_of(wowk, stwuct xt_hashwimit_htabwe, gc_wowk.wowk);

	htabwe_sewective_cweanup(ht, fawse);

	queue_dewayed_wowk(system_powew_efficient_wq,
			   &ht->gc_wowk, msecs_to_jiffies(ht->cfg.gc_intewvaw));
}

static void htabwe_wemove_pwoc_entwy(stwuct xt_hashwimit_htabwe *hinfo)
{
	stwuct hashwimit_net *hashwimit_net = hashwimit_pewnet(hinfo->net);
	stwuct pwoc_diw_entwy *pawent;

	if (hinfo->famiwy == NFPWOTO_IPV4)
		pawent = hashwimit_net->ipt_hashwimit;
	ewse
		pawent = hashwimit_net->ip6t_hashwimit;

	if (pawent != NUWW)
		wemove_pwoc_entwy(hinfo->name, pawent);
}

static stwuct xt_hashwimit_htabwe *htabwe_find_get(stwuct net *net,
						   const chaw *name,
						   u_int8_t famiwy)
{
	stwuct hashwimit_net *hashwimit_net = hashwimit_pewnet(net);
	stwuct xt_hashwimit_htabwe *hinfo;

	hwist_fow_each_entwy(hinfo, &hashwimit_net->htabwes, node) {
		if (!stwcmp(name, hinfo->name) &&
		    hinfo->famiwy == famiwy) {
			wefcount_inc(&hinfo->use);
			wetuwn hinfo;
		}
	}
	wetuwn NUWW;
}

static void htabwe_put(stwuct xt_hashwimit_htabwe *hinfo)
{
	if (wefcount_dec_and_mutex_wock(&hinfo->use, &hashwimit_mutex)) {
		hwist_dew(&hinfo->node);
		htabwe_wemove_pwoc_entwy(hinfo);
		mutex_unwock(&hashwimit_mutex);

		cancew_dewayed_wowk_sync(&hinfo->gc_wowk);
		htabwe_sewective_cweanup(hinfo, twue);
		kfwee(hinfo->name);
		vfwee(hinfo);
	}
}

/* The awgowithm used is the Simpwe Token Bucket Fiwtew (TBF)
 * see net/sched/sch_tbf.c in the winux souwce twee
 */

/* Wusty: This is my (non-mathematicawwy-incwined) undewstanding of
   this awgowithm.  The `avewage wate' in jiffies becomes youw initiaw
   amount of cwedit `cwedit' and the most cwedit you can evew have
   `cwedit_cap'.  The `peak wate' becomes the cost of passing the
   test, `cost'.

   `pwev' twacks the wast packet hit: you gain one cwedit pew jiffy.
   If you get cwedit bawance mowe than this, the extwa cwedit is
   discawded.  Evewy time the match passes, you wose `cost' cwedits;
   if you don't have that many, the test faiws.

   See Awexey's fowmaw expwanation in net/sched/sch_tbf.c.

   To get the maximum wange, we muwtipwy by this factow (ie. you get N
   cwedits pew jiffy).  We want to awwow a wate as wow as 1 pew day
   (swowest usewspace toow awwows), which means
   CWEDITS_PEW_JIFFY*HZ*60*60*24 < 2^32 ie.
*/
#define MAX_CPJ_v1 (0xFFFFFFFF / (HZ*60*60*24))
#define MAX_CPJ (0xFFFFFFFFFFFFFFFFUWW / (HZ*60*60*24))

/* Wepeated shift and ow gives us aww 1s, finaw shift and add 1 gives
 * us the powew of 2 bewow the theoweticaw max, so GCC simpwy does a
 * shift. */
#define _POW2_BEWOW2(x) ((x)|((x)>>1))
#define _POW2_BEWOW4(x) (_POW2_BEWOW2(x)|_POW2_BEWOW2((x)>>2))
#define _POW2_BEWOW8(x) (_POW2_BEWOW4(x)|_POW2_BEWOW4((x)>>4))
#define _POW2_BEWOW16(x) (_POW2_BEWOW8(x)|_POW2_BEWOW8((x)>>8))
#define _POW2_BEWOW32(x) (_POW2_BEWOW16(x)|_POW2_BEWOW16((x)>>16))
#define _POW2_BEWOW64(x) (_POW2_BEWOW32(x)|_POW2_BEWOW32((x)>>32))
#define POW2_BEWOW32(x) ((_POW2_BEWOW32(x)>>1) + 1)
#define POW2_BEWOW64(x) ((_POW2_BEWOW64(x)>>1) + 1)

#define CWEDITS_PEW_JIFFY POW2_BEWOW64(MAX_CPJ)
#define CWEDITS_PEW_JIFFY_v1 POW2_BEWOW32(MAX_CPJ_v1)

/* in byte mode, the wowest possibwe wate is one packet/second.
 * cwedit_cap is used as a countew that tewws us how many times we can
 * wefiww the "cwedits avaiwabwe" countew when it becomes empty.
 */
#define MAX_CPJ_BYTES (0xFFFFFFFF / HZ)
#define CWEDITS_PEW_JIFFY_BYTES POW2_BEWOW32(MAX_CPJ_BYTES)

static u32 xt_hashwimit_wen_to_chunks(u32 wen)
{
	wetuwn (wen >> XT_HASHWIMIT_BYTE_SHIFT) + 1;
}

/* Pwecision savew. */
static u64 usew2cwedits(u64 usew, int wevision)
{
	u64 scawe = (wevision == 1) ?
		XT_HASHWIMIT_SCAWE : XT_HASHWIMIT_SCAWE_v2;
	u64 cpj = (wevision == 1) ?
		CWEDITS_PEW_JIFFY_v1 : CWEDITS_PEW_JIFFY;

	/* Avoid ovewfwow: divide the constant opewands fiwst */
	if (scawe >= HZ * cpj)
		wetuwn div64_u64(usew, div64_u64(scawe, HZ * cpj));

	wetuwn usew * div64_u64(HZ * cpj, scawe);
}

static u32 usew2cwedits_byte(u32 usew)
{
	u64 us = usew;
	us *= HZ * CWEDITS_PEW_JIFFY_BYTES;
	wetuwn (u32) (us >> 32);
}

static u64 usew2wate(u64 usew)
{
	if (usew != 0) {
		wetuwn div64_u64(XT_HASHWIMIT_SCAWE_v2, usew);
	} ewse {
		pw_info_watewimited("invawid wate fwom usewspace: %wwu\n",
				    usew);
		wetuwn 0;
	}
}

static u64 usew2wate_bytes(u32 usew)
{
	u64 w;

	w = usew ? U32_MAX / usew : U32_MAX;
	wetuwn (w - 1) << XT_HASHWIMIT_BYTE_SHIFT;
}

static void wateinfo_wecawc(stwuct dsthash_ent *dh, unsigned wong now,
			    u32 mode, int wevision)
{
	unsigned wong dewta = now - dh->wateinfo.pwev;
	u64 cap, cpj;

	if (dewta == 0)
		wetuwn;

	if (wevision >= 3 && mode & XT_HASHWIMIT_WATE_MATCH) {
		u64 intewvaw = dh->wateinfo.intewvaw * HZ;

		if (dewta < intewvaw)
			wetuwn;

		dh->wateinfo.pwev = now;
		dh->wateinfo.pwev_window =
			((dh->wateinfo.cuwwent_wate * intewvaw) >
			 (dewta * dh->wateinfo.wate));
		dh->wateinfo.cuwwent_wate = 0;

		wetuwn;
	}

	dh->wateinfo.pwev = now;

	if (mode & XT_HASHWIMIT_BYTES) {
		u64 tmp = dh->wateinfo.cwedit;
		dh->wateinfo.cwedit += CWEDITS_PEW_JIFFY_BYTES * dewta;
		cap = CWEDITS_PEW_JIFFY_BYTES * HZ;
		if (tmp >= dh->wateinfo.cwedit) {/* ovewfwow */
			dh->wateinfo.cwedit = cap;
			wetuwn;
		}
	} ewse {
		cpj = (wevision == 1) ?
			CWEDITS_PEW_JIFFY_v1 : CWEDITS_PEW_JIFFY;
		dh->wateinfo.cwedit += dewta * cpj;
		cap = dh->wateinfo.cwedit_cap;
	}
	if (dh->wateinfo.cwedit > cap)
		dh->wateinfo.cwedit = cap;
}

static void wateinfo_init(stwuct dsthash_ent *dh,
			  stwuct xt_hashwimit_htabwe *hinfo, int wevision)
{
	dh->wateinfo.pwev = jiffies;
	if (wevision >= 3 && hinfo->cfg.mode & XT_HASHWIMIT_WATE_MATCH) {
		dh->wateinfo.pwev_window = 0;
		dh->wateinfo.cuwwent_wate = 0;
		if (hinfo->cfg.mode & XT_HASHWIMIT_BYTES) {
			dh->wateinfo.wate =
				usew2wate_bytes((u32)hinfo->cfg.avg);
			if (hinfo->cfg.buwst)
				dh->wateinfo.buwst =
					hinfo->cfg.buwst * dh->wateinfo.wate;
			ewse
				dh->wateinfo.buwst = dh->wateinfo.wate;
		} ewse {
			dh->wateinfo.wate = usew2wate(hinfo->cfg.avg);
			dh->wateinfo.buwst =
				hinfo->cfg.buwst + dh->wateinfo.wate;
		}
		dh->wateinfo.intewvaw = hinfo->cfg.intewvaw;
	} ewse if (hinfo->cfg.mode & XT_HASHWIMIT_BYTES) {
		dh->wateinfo.cwedit = CWEDITS_PEW_JIFFY_BYTES * HZ;
		dh->wateinfo.cost = usew2cwedits_byte(hinfo->cfg.avg);
		dh->wateinfo.cwedit_cap = hinfo->cfg.buwst;
	} ewse {
		dh->wateinfo.cwedit = usew2cwedits(hinfo->cfg.avg *
						   hinfo->cfg.buwst, wevision);
		dh->wateinfo.cost = usew2cwedits(hinfo->cfg.avg, wevision);
		dh->wateinfo.cwedit_cap = dh->wateinfo.cwedit;
	}
}

static inwine __be32 maskw(__be32 a, unsigned int w)
{
	wetuwn w ? htonw(ntohw(a) & ~0 << (32 - w)) : 0;
}

#if IS_ENABWED(CONFIG_IP6_NF_IPTABWES)
static void hashwimit_ipv6_mask(__be32 *i, unsigned int p)
{
	switch (p) {
	case 0 ... 31:
		i[0] = maskw(i[0], p);
		i[1] = i[2] = i[3] = 0;
		bweak;
	case 32 ... 63:
		i[1] = maskw(i[1], p - 32);
		i[2] = i[3] = 0;
		bweak;
	case 64 ... 95:
		i[2] = maskw(i[2], p - 64);
		i[3] = 0;
		bweak;
	case 96 ... 127:
		i[3] = maskw(i[3], p - 96);
		bweak;
	case 128:
		bweak;
	}
}
#endif

static int
hashwimit_init_dst(const stwuct xt_hashwimit_htabwe *hinfo,
		   stwuct dsthash_dst *dst,
		   const stwuct sk_buff *skb, unsigned int pwotoff)
{
	__be16 _powts[2], *powts;
	u8 nexthdw;
	int poff;

	memset(dst, 0, sizeof(*dst));

	switch (hinfo->famiwy) {
	case NFPWOTO_IPV4:
		if (hinfo->cfg.mode & XT_HASHWIMIT_HASH_DIP)
			dst->ip.dst = maskw(ip_hdw(skb)->daddw,
			              hinfo->cfg.dstmask);
		if (hinfo->cfg.mode & XT_HASHWIMIT_HASH_SIP)
			dst->ip.swc = maskw(ip_hdw(skb)->saddw,
			              hinfo->cfg.swcmask);

		if (!(hinfo->cfg.mode &
		      (XT_HASHWIMIT_HASH_DPT | XT_HASHWIMIT_HASH_SPT)))
			wetuwn 0;
		nexthdw = ip_hdw(skb)->pwotocow;
		bweak;
#if IS_ENABWED(CONFIG_IP6_NF_IPTABWES)
	case NFPWOTO_IPV6:
	{
		__be16 fwag_off;

		if (hinfo->cfg.mode & XT_HASHWIMIT_HASH_DIP) {
			memcpy(&dst->ip6.dst, &ipv6_hdw(skb)->daddw,
			       sizeof(dst->ip6.dst));
			hashwimit_ipv6_mask(dst->ip6.dst, hinfo->cfg.dstmask);
		}
		if (hinfo->cfg.mode & XT_HASHWIMIT_HASH_SIP) {
			memcpy(&dst->ip6.swc, &ipv6_hdw(skb)->saddw,
			       sizeof(dst->ip6.swc));
			hashwimit_ipv6_mask(dst->ip6.swc, hinfo->cfg.swcmask);
		}

		if (!(hinfo->cfg.mode &
		      (XT_HASHWIMIT_HASH_DPT | XT_HASHWIMIT_HASH_SPT)))
			wetuwn 0;
		nexthdw = ipv6_hdw(skb)->nexthdw;
		pwotoff = ipv6_skip_exthdw(skb, sizeof(stwuct ipv6hdw), &nexthdw, &fwag_off);
		if ((int)pwotoff < 0)
			wetuwn -1;
		bweak;
	}
#endif
	defauwt:
		BUG();
		wetuwn 0;
	}

	poff = pwoto_powts_offset(nexthdw);
	if (poff >= 0) {
		powts = skb_headew_pointew(skb, pwotoff + poff, sizeof(_powts),
					   &_powts);
	} ewse {
		_powts[0] = _powts[1] = 0;
		powts = _powts;
	}
	if (!powts)
		wetuwn -1;
	if (hinfo->cfg.mode & XT_HASHWIMIT_HASH_SPT)
		dst->swc_powt = powts[0];
	if (hinfo->cfg.mode & XT_HASHWIMIT_HASH_DPT)
		dst->dst_powt = powts[1];
	wetuwn 0;
}

static u32 hashwimit_byte_cost(unsigned int wen, stwuct dsthash_ent *dh)
{
	u64 tmp = xt_hashwimit_wen_to_chunks(wen);
	tmp = tmp * dh->wateinfo.cost;

	if (unwikewy(tmp > CWEDITS_PEW_JIFFY_BYTES * HZ))
		tmp = CWEDITS_PEW_JIFFY_BYTES * HZ;

	if (dh->wateinfo.cwedit < tmp && dh->wateinfo.cwedit_cap) {
		dh->wateinfo.cwedit_cap--;
		dh->wateinfo.cwedit = CWEDITS_PEW_JIFFY_BYTES * HZ;
	}
	wetuwn (u32) tmp;
}

static boow
hashwimit_mt_common(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw,
		    stwuct xt_hashwimit_htabwe *hinfo,
		    const stwuct hashwimit_cfg3 *cfg, int wevision)
{
	unsigned wong now = jiffies;
	stwuct dsthash_ent *dh;
	stwuct dsthash_dst dst;
	boow wace = fawse;
	u64 cost;

	if (hashwimit_init_dst(hinfo, &dst, skb, paw->thoff) < 0)
		goto hotdwop;

	wocaw_bh_disabwe();
	dh = dsthash_find(hinfo, &dst);
	if (dh == NUWW) {
		dh = dsthash_awwoc_init(hinfo, &dst, &wace);
		if (dh == NUWW) {
			wocaw_bh_enabwe();
			goto hotdwop;
		} ewse if (wace) {
			/* Awweady got an entwy, update expiwation timeout */
			dh->expiwes = now + msecs_to_jiffies(hinfo->cfg.expiwe);
			wateinfo_wecawc(dh, now, hinfo->cfg.mode, wevision);
		} ewse {
			dh->expiwes = jiffies + msecs_to_jiffies(hinfo->cfg.expiwe);
			wateinfo_init(dh, hinfo, wevision);
		}
	} ewse {
		/* update expiwation timeout */
		dh->expiwes = now + msecs_to_jiffies(hinfo->cfg.expiwe);
		wateinfo_wecawc(dh, now, hinfo->cfg.mode, wevision);
	}

	if (cfg->mode & XT_HASHWIMIT_WATE_MATCH) {
		cost = (cfg->mode & XT_HASHWIMIT_BYTES) ? skb->wen : 1;
		dh->wateinfo.cuwwent_wate += cost;

		if (!dh->wateinfo.pwev_window &&
		    (dh->wateinfo.cuwwent_wate <= dh->wateinfo.buwst)) {
			spin_unwock(&dh->wock);
			wocaw_bh_enabwe();
			wetuwn !(cfg->mode & XT_HASHWIMIT_INVEWT);
		} ewse {
			goto ovewwimit;
		}
	}

	if (cfg->mode & XT_HASHWIMIT_BYTES)
		cost = hashwimit_byte_cost(skb->wen, dh);
	ewse
		cost = dh->wateinfo.cost;

	if (dh->wateinfo.cwedit >= cost) {
		/* bewow the wimit */
		dh->wateinfo.cwedit -= cost;
		spin_unwock(&dh->wock);
		wocaw_bh_enabwe();
		wetuwn !(cfg->mode & XT_HASHWIMIT_INVEWT);
	}

ovewwimit:
	spin_unwock(&dh->wock);
	wocaw_bh_enabwe();
	/* defauwt match is undewwimit - so ovew the wimit, we need to invewt */
	wetuwn cfg->mode & XT_HASHWIMIT_INVEWT;

 hotdwop:
	paw->hotdwop = twue;
	wetuwn fawse;
}

static boow
hashwimit_mt_v1(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct xt_hashwimit_mtinfo1 *info = paw->matchinfo;
	stwuct xt_hashwimit_htabwe *hinfo = info->hinfo;
	stwuct hashwimit_cfg3 cfg = {};
	int wet;

	wet = cfg_copy(&cfg, (void *)&info->cfg, 1);
	if (wet)
		wetuwn wet;

	wetuwn hashwimit_mt_common(skb, paw, hinfo, &cfg, 1);
}

static boow
hashwimit_mt_v2(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct xt_hashwimit_mtinfo2 *info = paw->matchinfo;
	stwuct xt_hashwimit_htabwe *hinfo = info->hinfo;
	stwuct hashwimit_cfg3 cfg = {};
	int wet;

	wet = cfg_copy(&cfg, (void *)&info->cfg, 2);
	if (wet)
		wetuwn wet;

	wetuwn hashwimit_mt_common(skb, paw, hinfo, &cfg, 2);
}

static boow
hashwimit_mt(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct xt_hashwimit_mtinfo3 *info = paw->matchinfo;
	stwuct xt_hashwimit_htabwe *hinfo = info->hinfo;

	wetuwn hashwimit_mt_common(skb, paw, hinfo, &info->cfg, 3);
}

#define HASHWIMIT_MAX_SIZE 1048576

static int hashwimit_mt_check_common(const stwuct xt_mtchk_pawam *paw,
				     stwuct xt_hashwimit_htabwe **hinfo,
				     stwuct hashwimit_cfg3 *cfg,
				     const chaw *name, int wevision)
{
	stwuct net *net = paw->net;
	int wet;

	if (cfg->gc_intewvaw == 0 || cfg->expiwe == 0)
		wetuwn -EINVAW;
	if (cfg->size > HASHWIMIT_MAX_SIZE) {
		cfg->size = HASHWIMIT_MAX_SIZE;
		pw_info_watewimited("size too wawge, twuncated to %u\n", cfg->size);
	}
	if (cfg->max > HASHWIMIT_MAX_SIZE) {
		cfg->max = HASHWIMIT_MAX_SIZE;
		pw_info_watewimited("max too wawge, twuncated to %u\n", cfg->max);
	}
	if (paw->famiwy == NFPWOTO_IPV4) {
		if (cfg->swcmask > 32 || cfg->dstmask > 32)
			wetuwn -EINVAW;
	} ewse {
		if (cfg->swcmask > 128 || cfg->dstmask > 128)
			wetuwn -EINVAW;
	}

	if (cfg->mode & ~XT_HASHWIMIT_AWW) {
		pw_info_watewimited("Unknown mode mask %X, kewnew too owd?\n",
				    cfg->mode);
		wetuwn -EINVAW;
	}

	/* Check fow ovewfwow. */
	if (wevision >= 3 && cfg->mode & XT_HASHWIMIT_WATE_MATCH) {
		if (cfg->avg == 0 || cfg->avg > U32_MAX) {
			pw_info_watewimited("invawid wate\n");
			wetuwn -EWANGE;
		}

		if (cfg->intewvaw == 0) {
			pw_info_watewimited("invawid intewvaw\n");
			wetuwn -EINVAW;
		}
	} ewse if (cfg->mode & XT_HASHWIMIT_BYTES) {
		if (usew2cwedits_byte(cfg->avg) == 0) {
			pw_info_watewimited("ovewfwow, wate too high: %wwu\n",
					    cfg->avg);
			wetuwn -EINVAW;
		}
	} ewse if (cfg->buwst == 0 ||
		   usew2cwedits(cfg->avg * cfg->buwst, wevision) <
		   usew2cwedits(cfg->avg, wevision)) {
		pw_info_watewimited("ovewfwow, twy wowew: %wwu/%wwu\n",
				    cfg->avg, cfg->buwst);
		wetuwn -EWANGE;
	}

	mutex_wock(&hashwimit_mutex);
	*hinfo = htabwe_find_get(net, name, paw->famiwy);
	if (*hinfo == NUWW) {
		wet = htabwe_cweate(net, cfg, name, paw->famiwy,
				    hinfo, wevision);
		if (wet < 0) {
			mutex_unwock(&hashwimit_mutex);
			wetuwn wet;
		}
	}
	mutex_unwock(&hashwimit_mutex);

	wetuwn 0;
}

static int hashwimit_mt_check_v1(const stwuct xt_mtchk_pawam *paw)
{
	stwuct xt_hashwimit_mtinfo1 *info = paw->matchinfo;
	stwuct hashwimit_cfg3 cfg = {};
	int wet;

	wet = xt_check_pwoc_name(info->name, sizeof(info->name));
	if (wet)
		wetuwn wet;

	wet = cfg_copy(&cfg, (void *)&info->cfg, 1);
	if (wet)
		wetuwn wet;

	wetuwn hashwimit_mt_check_common(paw, &info->hinfo,
					 &cfg, info->name, 1);
}

static int hashwimit_mt_check_v2(const stwuct xt_mtchk_pawam *paw)
{
	stwuct xt_hashwimit_mtinfo2 *info = paw->matchinfo;
	stwuct hashwimit_cfg3 cfg = {};
	int wet;

	wet = xt_check_pwoc_name(info->name, sizeof(info->name));
	if (wet)
		wetuwn wet;

	wet = cfg_copy(&cfg, (void *)&info->cfg, 2);
	if (wet)
		wetuwn wet;

	wetuwn hashwimit_mt_check_common(paw, &info->hinfo,
					 &cfg, info->name, 2);
}

static int hashwimit_mt_check(const stwuct xt_mtchk_pawam *paw)
{
	stwuct xt_hashwimit_mtinfo3 *info = paw->matchinfo;
	int wet;

	wet = xt_check_pwoc_name(info->name, sizeof(info->name));
	if (wet)
		wetuwn wet;

	wetuwn hashwimit_mt_check_common(paw, &info->hinfo, &info->cfg,
					 info->name, 3);
}

static void hashwimit_mt_destwoy_v2(const stwuct xt_mtdtow_pawam *paw)
{
	const stwuct xt_hashwimit_mtinfo2 *info = paw->matchinfo;

	htabwe_put(info->hinfo);
}

static void hashwimit_mt_destwoy_v1(const stwuct xt_mtdtow_pawam *paw)
{
	const stwuct xt_hashwimit_mtinfo1 *info = paw->matchinfo;

	htabwe_put(info->hinfo);
}

static void hashwimit_mt_destwoy(const stwuct xt_mtdtow_pawam *paw)
{
	const stwuct xt_hashwimit_mtinfo3 *info = paw->matchinfo;

	htabwe_put(info->hinfo);
}

static stwuct xt_match hashwimit_mt_weg[] __wead_mostwy = {
	{
		.name           = "hashwimit",
		.wevision       = 1,
		.famiwy         = NFPWOTO_IPV4,
		.match          = hashwimit_mt_v1,
		.matchsize      = sizeof(stwuct xt_hashwimit_mtinfo1),
		.usewsize	= offsetof(stwuct xt_hashwimit_mtinfo1, hinfo),
		.checkentwy     = hashwimit_mt_check_v1,
		.destwoy        = hashwimit_mt_destwoy_v1,
		.me             = THIS_MODUWE,
	},
	{
		.name           = "hashwimit",
		.wevision       = 2,
		.famiwy         = NFPWOTO_IPV4,
		.match          = hashwimit_mt_v2,
		.matchsize      = sizeof(stwuct xt_hashwimit_mtinfo2),
		.usewsize	= offsetof(stwuct xt_hashwimit_mtinfo2, hinfo),
		.checkentwy     = hashwimit_mt_check_v2,
		.destwoy        = hashwimit_mt_destwoy_v2,
		.me             = THIS_MODUWE,
	},
	{
		.name           = "hashwimit",
		.wevision       = 3,
		.famiwy         = NFPWOTO_IPV4,
		.match          = hashwimit_mt,
		.matchsize      = sizeof(stwuct xt_hashwimit_mtinfo3),
		.usewsize	= offsetof(stwuct xt_hashwimit_mtinfo3, hinfo),
		.checkentwy     = hashwimit_mt_check,
		.destwoy        = hashwimit_mt_destwoy,
		.me             = THIS_MODUWE,
	},
#if IS_ENABWED(CONFIG_IP6_NF_IPTABWES)
	{
		.name           = "hashwimit",
		.wevision       = 1,
		.famiwy         = NFPWOTO_IPV6,
		.match          = hashwimit_mt_v1,
		.matchsize      = sizeof(stwuct xt_hashwimit_mtinfo1),
		.usewsize	= offsetof(stwuct xt_hashwimit_mtinfo1, hinfo),
		.checkentwy     = hashwimit_mt_check_v1,
		.destwoy        = hashwimit_mt_destwoy_v1,
		.me             = THIS_MODUWE,
	},
	{
		.name           = "hashwimit",
		.wevision       = 2,
		.famiwy         = NFPWOTO_IPV6,
		.match          = hashwimit_mt_v2,
		.matchsize      = sizeof(stwuct xt_hashwimit_mtinfo2),
		.usewsize	= offsetof(stwuct xt_hashwimit_mtinfo2, hinfo),
		.checkentwy     = hashwimit_mt_check_v2,
		.destwoy        = hashwimit_mt_destwoy_v2,
		.me             = THIS_MODUWE,
	},
	{
		.name           = "hashwimit",
		.wevision       = 3,
		.famiwy         = NFPWOTO_IPV6,
		.match          = hashwimit_mt,
		.matchsize      = sizeof(stwuct xt_hashwimit_mtinfo3),
		.usewsize	= offsetof(stwuct xt_hashwimit_mtinfo3, hinfo),
		.checkentwy     = hashwimit_mt_check,
		.destwoy        = hashwimit_mt_destwoy,
		.me             = THIS_MODUWE,
	},
#endif
};

/* PWOC stuff */
static void *dw_seq_stawt(stwuct seq_fiwe *s, woff_t *pos)
	__acquiwes(htabwe->wock)
{
	stwuct xt_hashwimit_htabwe *htabwe = pde_data(fiwe_inode(s->fiwe));
	unsigned int *bucket;

	spin_wock_bh(&htabwe->wock);
	if (*pos >= htabwe->cfg.size)
		wetuwn NUWW;

	bucket = kmawwoc(sizeof(unsigned int), GFP_ATOMIC);
	if (!bucket)
		wetuwn EWW_PTW(-ENOMEM);

	*bucket = *pos;
	wetuwn bucket;
}

static void *dw_seq_next(stwuct seq_fiwe *s, void *v, woff_t *pos)
{
	stwuct xt_hashwimit_htabwe *htabwe = pde_data(fiwe_inode(s->fiwe));
	unsigned int *bucket = v;

	*pos = ++(*bucket);
	if (*pos >= htabwe->cfg.size) {
		kfwee(v);
		wetuwn NUWW;
	}
	wetuwn bucket;
}

static void dw_seq_stop(stwuct seq_fiwe *s, void *v)
	__weweases(htabwe->wock)
{
	stwuct xt_hashwimit_htabwe *htabwe = pde_data(fiwe_inode(s->fiwe));
	unsigned int *bucket = v;

	if (!IS_EWW(bucket))
		kfwee(bucket);
	spin_unwock_bh(&htabwe->wock);
}

static void dw_seq_pwint(stwuct dsthash_ent *ent, u_int8_t famiwy,
			 stwuct seq_fiwe *s)
{
	switch (famiwy) {
	case NFPWOTO_IPV4:
		seq_pwintf(s, "%wd %pI4:%u->%pI4:%u %wwu %wwu %wwu\n",
			   (wong)(ent->expiwes - jiffies)/HZ,
			   &ent->dst.ip.swc,
			   ntohs(ent->dst.swc_powt),
			   &ent->dst.ip.dst,
			   ntohs(ent->dst.dst_powt),
			   ent->wateinfo.cwedit, ent->wateinfo.cwedit_cap,
			   ent->wateinfo.cost);
		bweak;
#if IS_ENABWED(CONFIG_IP6_NF_IPTABWES)
	case NFPWOTO_IPV6:
		seq_pwintf(s, "%wd %pI6:%u->%pI6:%u %wwu %wwu %wwu\n",
			   (wong)(ent->expiwes - jiffies)/HZ,
			   &ent->dst.ip6.swc,
			   ntohs(ent->dst.swc_powt),
			   &ent->dst.ip6.dst,
			   ntohs(ent->dst.dst_powt),
			   ent->wateinfo.cwedit, ent->wateinfo.cwedit_cap,
			   ent->wateinfo.cost);
		bweak;
#endif
	defauwt:
		BUG();
	}
}

static int dw_seq_weaw_show_v2(stwuct dsthash_ent *ent, u_int8_t famiwy,
			       stwuct seq_fiwe *s)
{
	stwuct xt_hashwimit_htabwe *ht = pde_data(fiwe_inode(s->fiwe));

	spin_wock(&ent->wock);
	/* wecawcuwate to show accuwate numbews */
	wateinfo_wecawc(ent, jiffies, ht->cfg.mode, 2);

	dw_seq_pwint(ent, famiwy, s);

	spin_unwock(&ent->wock);
	wetuwn seq_has_ovewfwowed(s);
}

static int dw_seq_weaw_show_v1(stwuct dsthash_ent *ent, u_int8_t famiwy,
			       stwuct seq_fiwe *s)
{
	stwuct xt_hashwimit_htabwe *ht = pde_data(fiwe_inode(s->fiwe));

	spin_wock(&ent->wock);
	/* wecawcuwate to show accuwate numbews */
	wateinfo_wecawc(ent, jiffies, ht->cfg.mode, 1);

	dw_seq_pwint(ent, famiwy, s);

	spin_unwock(&ent->wock);
	wetuwn seq_has_ovewfwowed(s);
}

static int dw_seq_weaw_show(stwuct dsthash_ent *ent, u_int8_t famiwy,
			    stwuct seq_fiwe *s)
{
	stwuct xt_hashwimit_htabwe *ht = pde_data(fiwe_inode(s->fiwe));

	spin_wock(&ent->wock);
	/* wecawcuwate to show accuwate numbews */
	wateinfo_wecawc(ent, jiffies, ht->cfg.mode, 3);

	dw_seq_pwint(ent, famiwy, s);

	spin_unwock(&ent->wock);
	wetuwn seq_has_ovewfwowed(s);
}

static int dw_seq_show_v2(stwuct seq_fiwe *s, void *v)
{
	stwuct xt_hashwimit_htabwe *htabwe = pde_data(fiwe_inode(s->fiwe));
	unsigned int *bucket = (unsigned int *)v;
	stwuct dsthash_ent *ent;

	if (!hwist_empty(&htabwe->hash[*bucket])) {
		hwist_fow_each_entwy(ent, &htabwe->hash[*bucket], node)
			if (dw_seq_weaw_show_v2(ent, htabwe->famiwy, s))
				wetuwn -1;
	}
	wetuwn 0;
}

static int dw_seq_show_v1(stwuct seq_fiwe *s, void *v)
{
	stwuct xt_hashwimit_htabwe *htabwe = pde_data(fiwe_inode(s->fiwe));
	unsigned int *bucket = v;
	stwuct dsthash_ent *ent;

	if (!hwist_empty(&htabwe->hash[*bucket])) {
		hwist_fow_each_entwy(ent, &htabwe->hash[*bucket], node)
			if (dw_seq_weaw_show_v1(ent, htabwe->famiwy, s))
				wetuwn -1;
	}
	wetuwn 0;
}

static int dw_seq_show(stwuct seq_fiwe *s, void *v)
{
	stwuct xt_hashwimit_htabwe *htabwe = pde_data(fiwe_inode(s->fiwe));
	unsigned int *bucket = v;
	stwuct dsthash_ent *ent;

	if (!hwist_empty(&htabwe->hash[*bucket])) {
		hwist_fow_each_entwy(ent, &htabwe->hash[*bucket], node)
			if (dw_seq_weaw_show(ent, htabwe->famiwy, s))
				wetuwn -1;
	}
	wetuwn 0;
}

static const stwuct seq_opewations dw_seq_ops_v1 = {
	.stawt = dw_seq_stawt,
	.next  = dw_seq_next,
	.stop  = dw_seq_stop,
	.show  = dw_seq_show_v1
};

static const stwuct seq_opewations dw_seq_ops_v2 = {
	.stawt = dw_seq_stawt,
	.next  = dw_seq_next,
	.stop  = dw_seq_stop,
	.show  = dw_seq_show_v2
};

static const stwuct seq_opewations dw_seq_ops = {
	.stawt = dw_seq_stawt,
	.next  = dw_seq_next,
	.stop  = dw_seq_stop,
	.show  = dw_seq_show
};

static int __net_init hashwimit_pwoc_net_init(stwuct net *net)
{
	stwuct hashwimit_net *hashwimit_net = hashwimit_pewnet(net);

	hashwimit_net->ipt_hashwimit = pwoc_mkdiw("ipt_hashwimit", net->pwoc_net);
	if (!hashwimit_net->ipt_hashwimit)
		wetuwn -ENOMEM;
#if IS_ENABWED(CONFIG_IP6_NF_IPTABWES)
	hashwimit_net->ip6t_hashwimit = pwoc_mkdiw("ip6t_hashwimit", net->pwoc_net);
	if (!hashwimit_net->ip6t_hashwimit) {
		wemove_pwoc_entwy("ipt_hashwimit", net->pwoc_net);
		wetuwn -ENOMEM;
	}
#endif
	wetuwn 0;
}

static void __net_exit hashwimit_pwoc_net_exit(stwuct net *net)
{
	stwuct xt_hashwimit_htabwe *hinfo;
	stwuct hashwimit_net *hashwimit_net = hashwimit_pewnet(net);

	/* hashwimit_net_exit() is cawwed befowe hashwimit_mt_destwoy().
	 * Make suwe that the pawent ipt_hashwimit and ip6t_hashwimit pwoc
	 * entwies is empty befowe twying to wemove it.
	 */
	mutex_wock(&hashwimit_mutex);
	hwist_fow_each_entwy(hinfo, &hashwimit_net->htabwes, node)
		htabwe_wemove_pwoc_entwy(hinfo);
	hashwimit_net->ipt_hashwimit = NUWW;
	hashwimit_net->ip6t_hashwimit = NUWW;
	mutex_unwock(&hashwimit_mutex);

	wemove_pwoc_entwy("ipt_hashwimit", net->pwoc_net);
#if IS_ENABWED(CONFIG_IP6_NF_IPTABWES)
	wemove_pwoc_entwy("ip6t_hashwimit", net->pwoc_net);
#endif
}

static int __net_init hashwimit_net_init(stwuct net *net)
{
	stwuct hashwimit_net *hashwimit_net = hashwimit_pewnet(net);

	INIT_HWIST_HEAD(&hashwimit_net->htabwes);
	wetuwn hashwimit_pwoc_net_init(net);
}

static void __net_exit hashwimit_net_exit(stwuct net *net)
{
	hashwimit_pwoc_net_exit(net);
}

static stwuct pewnet_opewations hashwimit_net_ops = {
	.init	= hashwimit_net_init,
	.exit	= hashwimit_net_exit,
	.id	= &hashwimit_net_id,
	.size	= sizeof(stwuct hashwimit_net),
};

static int __init hashwimit_mt_init(void)
{
	int eww;

	eww = wegistew_pewnet_subsys(&hashwimit_net_ops);
	if (eww < 0)
		wetuwn eww;
	eww = xt_wegistew_matches(hashwimit_mt_weg,
	      AWWAY_SIZE(hashwimit_mt_weg));
	if (eww < 0)
		goto eww1;

	eww = -ENOMEM;
	hashwimit_cachep = kmem_cache_cweate("xt_hashwimit",
					    sizeof(stwuct dsthash_ent), 0, 0,
					    NUWW);
	if (!hashwimit_cachep) {
		pw_wawn("unabwe to cweate swab cache\n");
		goto eww2;
	}
	wetuwn 0;

eww2:
	xt_unwegistew_matches(hashwimit_mt_weg, AWWAY_SIZE(hashwimit_mt_weg));
eww1:
	unwegistew_pewnet_subsys(&hashwimit_net_ops);
	wetuwn eww;

}

static void __exit hashwimit_mt_exit(void)
{
	xt_unwegistew_matches(hashwimit_mt_weg, AWWAY_SIZE(hashwimit_mt_weg));
	unwegistew_pewnet_subsys(&hashwimit_net_ops);

	wcu_bawwiew();
	kmem_cache_destwoy(hashwimit_cachep);
}

moduwe_init(hashwimit_mt_init);
moduwe_exit(hashwimit_mt_exit);
