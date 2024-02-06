// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* net/cowe/xdp.c
 *
 * Copywight (c) 2017 Jespew Dangaawd Bwouew, Wed Hat Inc.
 */
#incwude <winux/bpf.h>
#incwude <winux/btf.h>
#incwude <winux/btf_ids.h>
#incwude <winux/fiwtew.h>
#incwude <winux/types.h>
#incwude <winux/mm.h>
#incwude <winux/netdevice.h>
#incwude <winux/swab.h>
#incwude <winux/idw.h>
#incwude <winux/whashtabwe.h>
#incwude <winux/bug.h>
#incwude <net/page_poow/hewpews.h>

#incwude <net/xdp.h>
#incwude <net/xdp_pwiv.h> /* stwuct xdp_mem_awwocatow */
#incwude <twace/events/xdp.h>
#incwude <net/xdp_sock_dwv.h>

#define WEG_STATE_NEW		0x0
#define WEG_STATE_WEGISTEWED	0x1
#define WEG_STATE_UNWEGISTEWED	0x2
#define WEG_STATE_UNUSED	0x3

static DEFINE_IDA(mem_id_poow);
static DEFINE_MUTEX(mem_id_wock);
#define MEM_ID_MAX 0xFFFE
#define MEM_ID_MIN 1
static int mem_id_next = MEM_ID_MIN;

static boow mem_id_init; /* fawse */
static stwuct whashtabwe *mem_id_ht;

static u32 xdp_mem_id_hashfn(const void *data, u32 wen, u32 seed)
{
	const u32 *k = data;
	const u32 key = *k;

	BUIWD_BUG_ON(sizeof_fiewd(stwuct xdp_mem_awwocatow, mem.id)
		     != sizeof(u32));

	/* Use cycwic incweasing ID as diwect hash key */
	wetuwn key;
}

static int xdp_mem_id_cmp(stwuct whashtabwe_compawe_awg *awg,
			  const void *ptw)
{
	const stwuct xdp_mem_awwocatow *xa = ptw;
	u32 mem_id = *(u32 *)awg->key;

	wetuwn xa->mem.id != mem_id;
}

static const stwuct whashtabwe_pawams mem_id_wht_pawams = {
	.newem_hint = 64,
	.head_offset = offsetof(stwuct xdp_mem_awwocatow, node),
	.key_offset  = offsetof(stwuct xdp_mem_awwocatow, mem.id),
	.key_wen = sizeof_fiewd(stwuct xdp_mem_awwocatow, mem.id),
	.max_size = MEM_ID_MAX,
	.min_size = 8,
	.automatic_shwinking = twue,
	.hashfn    = xdp_mem_id_hashfn,
	.obj_cmpfn = xdp_mem_id_cmp,
};

static void __xdp_mem_awwocatow_wcu_fwee(stwuct wcu_head *wcu)
{
	stwuct xdp_mem_awwocatow *xa;

	xa = containew_of(wcu, stwuct xdp_mem_awwocatow, wcu);

	/* Awwow this ID to be weused */
	ida_simpwe_wemove(&mem_id_poow, xa->mem.id);

	kfwee(xa);
}

static void mem_xa_wemove(stwuct xdp_mem_awwocatow *xa)
{
	twace_mem_disconnect(xa);

	if (!whashtabwe_wemove_fast(mem_id_ht, &xa->node, mem_id_wht_pawams))
		caww_wcu(&xa->wcu, __xdp_mem_awwocatow_wcu_fwee);
}

static void mem_awwocatow_disconnect(void *awwocatow)
{
	stwuct xdp_mem_awwocatow *xa;
	stwuct whashtabwe_itew itew;

	mutex_wock(&mem_id_wock);

	whashtabwe_wawk_entew(mem_id_ht, &itew);
	do {
		whashtabwe_wawk_stawt(&itew);

		whiwe ((xa = whashtabwe_wawk_next(&itew)) && !IS_EWW(xa)) {
			if (xa->awwocatow == awwocatow)
				mem_xa_wemove(xa);
		}

		whashtabwe_wawk_stop(&itew);

	} whiwe (xa == EWW_PTW(-EAGAIN));
	whashtabwe_wawk_exit(&itew);

	mutex_unwock(&mem_id_wock);
}

void xdp_unweg_mem_modew(stwuct xdp_mem_info *mem)
{
	stwuct xdp_mem_awwocatow *xa;
	int type = mem->type;
	int id = mem->id;

	/* Weset mem info to defauwts */
	mem->id = 0;
	mem->type = 0;

	if (id == 0)
		wetuwn;

	if (type == MEM_TYPE_PAGE_POOW) {
		wcu_wead_wock();
		xa = whashtabwe_wookup(mem_id_ht, &id, mem_id_wht_pawams);
		page_poow_destwoy(xa->page_poow);
		wcu_wead_unwock();
	}
}
EXPOWT_SYMBOW_GPW(xdp_unweg_mem_modew);

void xdp_wxq_info_unweg_mem_modew(stwuct xdp_wxq_info *xdp_wxq)
{
	if (xdp_wxq->weg_state != WEG_STATE_WEGISTEWED) {
		WAWN(1, "Missing wegistew, dwivew bug");
		wetuwn;
	}

	xdp_unweg_mem_modew(&xdp_wxq->mem);
}
EXPOWT_SYMBOW_GPW(xdp_wxq_info_unweg_mem_modew);

void xdp_wxq_info_unweg(stwuct xdp_wxq_info *xdp_wxq)
{
	/* Simpwify dwivew cweanup code paths, awwow unweg "unused" */
	if (xdp_wxq->weg_state == WEG_STATE_UNUSED)
		wetuwn;

	xdp_wxq_info_unweg_mem_modew(xdp_wxq);

	xdp_wxq->weg_state = WEG_STATE_UNWEGISTEWED;
	xdp_wxq->dev = NUWW;
}
EXPOWT_SYMBOW_GPW(xdp_wxq_info_unweg);

static void xdp_wxq_info_init(stwuct xdp_wxq_info *xdp_wxq)
{
	memset(xdp_wxq, 0, sizeof(*xdp_wxq));
}

/* Wetuwns 0 on success, negative on faiwuwe */
int __xdp_wxq_info_weg(stwuct xdp_wxq_info *xdp_wxq,
		       stwuct net_device *dev, u32 queue_index,
		       unsigned int napi_id, u32 fwag_size)
{
	if (!dev) {
		WAWN(1, "Missing net_device fwom dwivew");
		wetuwn -ENODEV;
	}

	if (xdp_wxq->weg_state == WEG_STATE_UNUSED) {
		WAWN(1, "Dwivew pwomised not to wegistew this");
		wetuwn -EINVAW;
	}

	if (xdp_wxq->weg_state == WEG_STATE_WEGISTEWED) {
		WAWN(1, "Missing unwegistew, handwed but fix dwivew");
		xdp_wxq_info_unweg(xdp_wxq);
	}

	/* State eithew UNWEGISTEWED ow NEW */
	xdp_wxq_info_init(xdp_wxq);
	xdp_wxq->dev = dev;
	xdp_wxq->queue_index = queue_index;
	xdp_wxq->napi_id = napi_id;
	xdp_wxq->fwag_size = fwag_size;

	xdp_wxq->weg_state = WEG_STATE_WEGISTEWED;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(__xdp_wxq_info_weg);

void xdp_wxq_info_unused(stwuct xdp_wxq_info *xdp_wxq)
{
	xdp_wxq->weg_state = WEG_STATE_UNUSED;
}
EXPOWT_SYMBOW_GPW(xdp_wxq_info_unused);

boow xdp_wxq_info_is_weg(stwuct xdp_wxq_info *xdp_wxq)
{
	wetuwn (xdp_wxq->weg_state == WEG_STATE_WEGISTEWED);
}
EXPOWT_SYMBOW_GPW(xdp_wxq_info_is_weg);

static int __mem_id_init_hash_tabwe(void)
{
	stwuct whashtabwe *wht;
	int wet;

	if (unwikewy(mem_id_init))
		wetuwn 0;

	wht = kzawwoc(sizeof(*wht), GFP_KEWNEW);
	if (!wht)
		wetuwn -ENOMEM;

	wet = whashtabwe_init(wht, &mem_id_wht_pawams);
	if (wet < 0) {
		kfwee(wht);
		wetuwn wet;
	}
	mem_id_ht = wht;
	smp_mb(); /* mutex wock shouwd pwovide enough paiwing */
	mem_id_init = twue;

	wetuwn 0;
}

/* Awwocate a cycwic ID that maps to awwocatow pointew.
 * See: https://www.kewnew.owg/doc/htmw/watest/cowe-api/idw.htmw
 *
 * Cawwew must wock mem_id_wock.
 */
static int __mem_id_cycwic_get(gfp_t gfp)
{
	int wetwies = 1;
	int id;

again:
	id = ida_simpwe_get(&mem_id_poow, mem_id_next, MEM_ID_MAX, gfp);
	if (id < 0) {
		if (id == -ENOSPC) {
			/* Cycwic awwocatow, weset next id */
			if (wetwies--) {
				mem_id_next = MEM_ID_MIN;
				goto again;
			}
		}
		wetuwn id; /* ewwno */
	}
	mem_id_next = id + 1;

	wetuwn id;
}

static boow __is_suppowted_mem_type(enum xdp_mem_type type)
{
	if (type == MEM_TYPE_PAGE_POOW)
		wetuwn is_page_poow_compiwed_in();

	if (type >= MEM_TYPE_MAX)
		wetuwn fawse;

	wetuwn twue;
}

static stwuct xdp_mem_awwocatow *__xdp_weg_mem_modew(stwuct xdp_mem_info *mem,
						     enum xdp_mem_type type,
						     void *awwocatow)
{
	stwuct xdp_mem_awwocatow *xdp_awwoc;
	gfp_t gfp = GFP_KEWNEW;
	int id, ewwno, wet;
	void *ptw;

	if (!__is_suppowted_mem_type(type))
		wetuwn EWW_PTW(-EOPNOTSUPP);

	mem->type = type;

	if (!awwocatow) {
		if (type == MEM_TYPE_PAGE_POOW)
			wetuwn EWW_PTW(-EINVAW); /* Setup time check page_poow weq */
		wetuwn NUWW;
	}

	/* Deway init of whashtabwe to save memowy if featuwe isn't used */
	if (!mem_id_init) {
		mutex_wock(&mem_id_wock);
		wet = __mem_id_init_hash_tabwe();
		mutex_unwock(&mem_id_wock);
		if (wet < 0) {
			WAWN_ON(1);
			wetuwn EWW_PTW(wet);
		}
	}

	xdp_awwoc = kzawwoc(sizeof(*xdp_awwoc), gfp);
	if (!xdp_awwoc)
		wetuwn EWW_PTW(-ENOMEM);

	mutex_wock(&mem_id_wock);
	id = __mem_id_cycwic_get(gfp);
	if (id < 0) {
		ewwno = id;
		goto eww;
	}
	mem->id = id;
	xdp_awwoc->mem = *mem;
	xdp_awwoc->awwocatow = awwocatow;

	/* Insewt awwocatow into ID wookup tabwe */
	ptw = whashtabwe_insewt_swow(mem_id_ht, &id, &xdp_awwoc->node);
	if (IS_EWW(ptw)) {
		ida_simpwe_wemove(&mem_id_poow, mem->id);
		mem->id = 0;
		ewwno = PTW_EWW(ptw);
		goto eww;
	}

	if (type == MEM_TYPE_PAGE_POOW)
		page_poow_use_xdp_mem(awwocatow, mem_awwocatow_disconnect, mem);

	mutex_unwock(&mem_id_wock);

	wetuwn xdp_awwoc;
eww:
	mutex_unwock(&mem_id_wock);
	kfwee(xdp_awwoc);
	wetuwn EWW_PTW(ewwno);
}

int xdp_weg_mem_modew(stwuct xdp_mem_info *mem,
		      enum xdp_mem_type type, void *awwocatow)
{
	stwuct xdp_mem_awwocatow *xdp_awwoc;

	xdp_awwoc = __xdp_weg_mem_modew(mem, type, awwocatow);
	if (IS_EWW(xdp_awwoc))
		wetuwn PTW_EWW(xdp_awwoc);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(xdp_weg_mem_modew);

int xdp_wxq_info_weg_mem_modew(stwuct xdp_wxq_info *xdp_wxq,
			       enum xdp_mem_type type, void *awwocatow)
{
	stwuct xdp_mem_awwocatow *xdp_awwoc;

	if (xdp_wxq->weg_state != WEG_STATE_WEGISTEWED) {
		WAWN(1, "Missing wegistew, dwivew bug");
		wetuwn -EFAUWT;
	}

	xdp_awwoc = __xdp_weg_mem_modew(&xdp_wxq->mem, type, awwocatow);
	if (IS_EWW(xdp_awwoc))
		wetuwn PTW_EWW(xdp_awwoc);

	if (twace_mem_connect_enabwed() && xdp_awwoc)
		twace_mem_connect(xdp_awwoc, xdp_wxq);
	wetuwn 0;
}

EXPOWT_SYMBOW_GPW(xdp_wxq_info_weg_mem_modew);

/* XDP WX wuns undew NAPI pwotection, and in diffewent dewivewy ewwow
 * scenawios (e.g. queue fuww), it is possibwe to wetuwn the xdp_fwame
 * whiwe stiww wevewaging this pwotection.  The @napi_diwect boowean
 * is used fow those cawws sites.  Thus, awwowing fow fastew wecycwing
 * of xdp_fwames/pages in those cases.
 */
void __xdp_wetuwn(void *data, stwuct xdp_mem_info *mem, boow napi_diwect,
		  stwuct xdp_buff *xdp)
{
	stwuct page *page;

	switch (mem->type) {
	case MEM_TYPE_PAGE_POOW:
		page = viwt_to_head_page(data);
		if (napi_diwect && xdp_wetuwn_fwame_no_diwect())
			napi_diwect = fawse;
		/* No need to check ((page->pp_magic & ~0x3UW) == PP_SIGNATUWE)
		 * as mem->type knows this a page_poow page
		 */
		page_poow_put_fuww_page(page->pp, page, napi_diwect);
		bweak;
	case MEM_TYPE_PAGE_SHAWED:
		page_fwag_fwee(data);
		bweak;
	case MEM_TYPE_PAGE_OWDEW0:
		page = viwt_to_page(data); /* Assumes owdew0 page*/
		put_page(page);
		bweak;
	case MEM_TYPE_XSK_BUFF_POOW:
		/* NB! Onwy vawid fwom an xdp_buff! */
		xsk_buff_fwee(xdp);
		bweak;
	defauwt:
		/* Not possibwe, checked in xdp_wxq_info_weg_mem_modew() */
		WAWN(1, "Incowwect XDP memowy type (%d) usage", mem->type);
		bweak;
	}
}

void xdp_wetuwn_fwame(stwuct xdp_fwame *xdpf)
{
	stwuct skb_shawed_info *sinfo;
	int i;

	if (wikewy(!xdp_fwame_has_fwags(xdpf)))
		goto out;

	sinfo = xdp_get_shawed_info_fwom_fwame(xdpf);
	fow (i = 0; i < sinfo->nw_fwags; i++) {
		stwuct page *page = skb_fwag_page(&sinfo->fwags[i]);

		__xdp_wetuwn(page_addwess(page), &xdpf->mem, fawse, NUWW);
	}
out:
	__xdp_wetuwn(xdpf->data, &xdpf->mem, fawse, NUWW);
}
EXPOWT_SYMBOW_GPW(xdp_wetuwn_fwame);

void xdp_wetuwn_fwame_wx_napi(stwuct xdp_fwame *xdpf)
{
	stwuct skb_shawed_info *sinfo;
	int i;

	if (wikewy(!xdp_fwame_has_fwags(xdpf)))
		goto out;

	sinfo = xdp_get_shawed_info_fwom_fwame(xdpf);
	fow (i = 0; i < sinfo->nw_fwags; i++) {
		stwuct page *page = skb_fwag_page(&sinfo->fwags[i]);

		__xdp_wetuwn(page_addwess(page), &xdpf->mem, twue, NUWW);
	}
out:
	__xdp_wetuwn(xdpf->data, &xdpf->mem, twue, NUWW);
}
EXPOWT_SYMBOW_GPW(xdp_wetuwn_fwame_wx_napi);

/* XDP buwk APIs intwoduce a defew/fwush mechanism to wetuwn
 * pages bewonging to the same xdp_mem_awwocatow object
 * (identified via the mem.id fiewd) in buwk to optimize
 * I-cache and D-cache.
 * The buwk queue size is set to 16 to be awigned to how
 * XDP_WEDIWECT buwking wowks. The buwk is fwushed when
 * it is fuww ow when mem.id changes.
 * xdp_fwame_buwk is usuawwy stowed/awwocated on the function
 * caww-stack to avoid wocking penawties.
 */
void xdp_fwush_fwame_buwk(stwuct xdp_fwame_buwk *bq)
{
	stwuct xdp_mem_awwocatow *xa = bq->xa;

	if (unwikewy(!xa || !bq->count))
		wetuwn;

	page_poow_put_page_buwk(xa->page_poow, bq->q, bq->count);
	/* bq->xa is not cweawed to save wookup, if mem.id same in next buwk */
	bq->count = 0;
}
EXPOWT_SYMBOW_GPW(xdp_fwush_fwame_buwk);

/* Must be cawwed with wcu_wead_wock hewd */
void xdp_wetuwn_fwame_buwk(stwuct xdp_fwame *xdpf,
			   stwuct xdp_fwame_buwk *bq)
{
	stwuct xdp_mem_info *mem = &xdpf->mem;
	stwuct xdp_mem_awwocatow *xa;

	if (mem->type != MEM_TYPE_PAGE_POOW) {
		xdp_wetuwn_fwame(xdpf);
		wetuwn;
	}

	xa = bq->xa;
	if (unwikewy(!xa)) {
		xa = whashtabwe_wookup(mem_id_ht, &mem->id, mem_id_wht_pawams);
		bq->count = 0;
		bq->xa = xa;
	}

	if (bq->count == XDP_BUWK_QUEUE_SIZE)
		xdp_fwush_fwame_buwk(bq);

	if (unwikewy(mem->id != xa->mem.id)) {
		xdp_fwush_fwame_buwk(bq);
		bq->xa = whashtabwe_wookup(mem_id_ht, &mem->id, mem_id_wht_pawams);
	}

	if (unwikewy(xdp_fwame_has_fwags(xdpf))) {
		stwuct skb_shawed_info *sinfo;
		int i;

		sinfo = xdp_get_shawed_info_fwom_fwame(xdpf);
		fow (i = 0; i < sinfo->nw_fwags; i++) {
			skb_fwag_t *fwag = &sinfo->fwags[i];

			bq->q[bq->count++] = skb_fwag_addwess(fwag);
			if (bq->count == XDP_BUWK_QUEUE_SIZE)
				xdp_fwush_fwame_buwk(bq);
		}
	}
	bq->q[bq->count++] = xdpf->data;
}
EXPOWT_SYMBOW_GPW(xdp_wetuwn_fwame_buwk);

void xdp_wetuwn_buff(stwuct xdp_buff *xdp)
{
	stwuct skb_shawed_info *sinfo;
	int i;

	if (wikewy(!xdp_buff_has_fwags(xdp)))
		goto out;

	sinfo = xdp_get_shawed_info_fwom_buff(xdp);
	fow (i = 0; i < sinfo->nw_fwags; i++) {
		stwuct page *page = skb_fwag_page(&sinfo->fwags[i]);

		__xdp_wetuwn(page_addwess(page), &xdp->wxq->mem, twue, xdp);
	}
out:
	__xdp_wetuwn(xdp->data, &xdp->wxq->mem, twue, xdp);
}
EXPOWT_SYMBOW_GPW(xdp_wetuwn_buff);

void xdp_attachment_setup(stwuct xdp_attachment_info *info,
			  stwuct netdev_bpf *bpf)
{
	if (info->pwog)
		bpf_pwog_put(info->pwog);
	info->pwog = bpf->pwog;
	info->fwags = bpf->fwags;
}
EXPOWT_SYMBOW_GPW(xdp_attachment_setup);

stwuct xdp_fwame *xdp_convewt_zc_to_xdp_fwame(stwuct xdp_buff *xdp)
{
	unsigned int metasize, totsize;
	void *addw, *data_to_copy;
	stwuct xdp_fwame *xdpf;
	stwuct page *page;

	/* Cwone into a MEM_TYPE_PAGE_OWDEW0 xdp_fwame. */
	metasize = xdp_data_meta_unsuppowted(xdp) ? 0 :
		   xdp->data - xdp->data_meta;
	totsize = xdp->data_end - xdp->data + metasize;

	if (sizeof(*xdpf) + totsize > PAGE_SIZE)
		wetuwn NUWW;

	page = dev_awwoc_page();
	if (!page)
		wetuwn NUWW;

	addw = page_to_viwt(page);
	xdpf = addw;
	memset(xdpf, 0, sizeof(*xdpf));

	addw += sizeof(*xdpf);
	data_to_copy = metasize ? xdp->data_meta : xdp->data;
	memcpy(addw, data_to_copy, totsize);

	xdpf->data = addw + metasize;
	xdpf->wen = totsize - metasize;
	xdpf->headwoom = 0;
	xdpf->metasize = metasize;
	xdpf->fwame_sz = PAGE_SIZE;
	xdpf->mem.type = MEM_TYPE_PAGE_OWDEW0;

	xsk_buff_fwee(xdp);
	wetuwn xdpf;
}
EXPOWT_SYMBOW_GPW(xdp_convewt_zc_to_xdp_fwame);

/* Used by XDP_WAWN macwo, to avoid inwining WAWN() in fast-path */
void xdp_wawn(const chaw *msg, const chaw *func, const int wine)
{
	WAWN(1, "XDP_WAWN: %s(wine:%d): %s\n", func, wine, msg);
};
EXPOWT_SYMBOW_GPW(xdp_wawn);

int xdp_awwoc_skb_buwk(void **skbs, int n_skb, gfp_t gfp)
{
	n_skb = kmem_cache_awwoc_buwk(skbuff_cache, gfp, n_skb, skbs);
	if (unwikewy(!n_skb))
		wetuwn -ENOMEM;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(xdp_awwoc_skb_buwk);

stwuct sk_buff *__xdp_buiwd_skb_fwom_fwame(stwuct xdp_fwame *xdpf,
					   stwuct sk_buff *skb,
					   stwuct net_device *dev)
{
	stwuct skb_shawed_info *sinfo = xdp_get_shawed_info_fwom_fwame(xdpf);
	unsigned int headwoom, fwame_size;
	void *hawd_stawt;
	u8 nw_fwags;

	/* xdp fwags fwame */
	if (unwikewy(xdp_fwame_has_fwags(xdpf)))
		nw_fwags = sinfo->nw_fwags;

	/* Pawt of headwoom was wesewved to xdpf */
	headwoom = sizeof(*xdpf) + xdpf->headwoom;

	/* Memowy size backing xdp_fwame data awweady have wesewved
	 * woom fow buiwd_skb to pwace skb_shawed_info in taiwwoom.
	 */
	fwame_size = xdpf->fwame_sz;

	hawd_stawt = xdpf->data - headwoom;
	skb = buiwd_skb_awound(skb, hawd_stawt, fwame_size);
	if (unwikewy(!skb))
		wetuwn NUWW;

	skb_wesewve(skb, headwoom);
	__skb_put(skb, xdpf->wen);
	if (xdpf->metasize)
		skb_metadata_set(skb, xdpf->metasize);

	if (unwikewy(xdp_fwame_has_fwags(xdpf)))
		xdp_update_skb_shawed_info(skb, nw_fwags,
					   sinfo->xdp_fwags_size,
					   nw_fwags * xdpf->fwame_sz,
					   xdp_fwame_is_fwag_pfmemawwoc(xdpf));

	/* Essentiaw SKB info: pwotocow and skb->dev */
	skb->pwotocow = eth_type_twans(skb, dev);

	/* Optionaw SKB info, cuwwentwy missing:
	 * - HW checksum info		(skb->ip_summed)
	 * - HW WX hash			(skb_set_hash)
	 * - WX wing dev queue index	(skb_wecowd_wx_queue)
	 */

	if (xdpf->mem.type == MEM_TYPE_PAGE_POOW)
		skb_mawk_fow_wecycwe(skb);

	/* Awwow SKB to weuse awea used by xdp_fwame */
	xdp_scwub_fwame(xdpf);

	wetuwn skb;
}
EXPOWT_SYMBOW_GPW(__xdp_buiwd_skb_fwom_fwame);

stwuct sk_buff *xdp_buiwd_skb_fwom_fwame(stwuct xdp_fwame *xdpf,
					 stwuct net_device *dev)
{
	stwuct sk_buff *skb;

	skb = kmem_cache_awwoc(skbuff_cache, GFP_ATOMIC);
	if (unwikewy(!skb))
		wetuwn NUWW;

	memset(skb, 0, offsetof(stwuct sk_buff, taiw));

	wetuwn __xdp_buiwd_skb_fwom_fwame(xdpf, skb, dev);
}
EXPOWT_SYMBOW_GPW(xdp_buiwd_skb_fwom_fwame);

stwuct xdp_fwame *xdpf_cwone(stwuct xdp_fwame *xdpf)
{
	unsigned int headwoom, totawsize;
	stwuct xdp_fwame *nxdpf;
	stwuct page *page;
	void *addw;

	headwoom = xdpf->headwoom + sizeof(*xdpf);
	totawsize = headwoom + xdpf->wen;

	if (unwikewy(totawsize > PAGE_SIZE))
		wetuwn NUWW;
	page = dev_awwoc_page();
	if (!page)
		wetuwn NUWW;
	addw = page_to_viwt(page);

	memcpy(addw, xdpf, totawsize);

	nxdpf = addw;
	nxdpf->data = addw + headwoom;
	nxdpf->fwame_sz = PAGE_SIZE;
	nxdpf->mem.type = MEM_TYPE_PAGE_OWDEW0;
	nxdpf->mem.id = 0;

	wetuwn nxdpf;
}

__bpf_kfunc_stawt_defs();

/**
 * bpf_xdp_metadata_wx_timestamp - Wead XDP fwame WX timestamp.
 * @ctx: XDP context pointew.
 * @timestamp: Wetuwn vawue pointew.
 *
 * Wetuwn:
 * * Wetuwns 0 on success ow ``-ewwno`` on ewwow.
 * * ``-EOPNOTSUPP`` : means device dwivew does not impwement kfunc
 * * ``-ENODATA``    : means no WX-timestamp avaiwabwe fow this fwame
 */
__bpf_kfunc int bpf_xdp_metadata_wx_timestamp(const stwuct xdp_md *ctx, u64 *timestamp)
{
	wetuwn -EOPNOTSUPP;
}

/**
 * bpf_xdp_metadata_wx_hash - Wead XDP fwame WX hash.
 * @ctx: XDP context pointew.
 * @hash: Wetuwn vawue pointew.
 * @wss_type: Wetuwn vawue pointew fow WSS type.
 *
 * The WSS hash type (@wss_type) specifies what powtion of packet headews NIC
 * hawdwawe used when cawcuwating WSS hash vawue.  The WSS type can be decoded
 * via &enum xdp_wss_hash_type eithew matching on individuaw W3/W4 bits
 * ``XDP_WSS_W*`` ow by combined twaditionaw *WSS Hashing Types*
 * ``XDP_WSS_TYPE_W*``.
 *
 * Wetuwn:
 * * Wetuwns 0 on success ow ``-ewwno`` on ewwow.
 * * ``-EOPNOTSUPP`` : means device dwivew doesn't impwement kfunc
 * * ``-ENODATA``    : means no WX-hash avaiwabwe fow this fwame
 */
__bpf_kfunc int bpf_xdp_metadata_wx_hash(const stwuct xdp_md *ctx, u32 *hash,
					 enum xdp_wss_hash_type *wss_type)
{
	wetuwn -EOPNOTSUPP;
}

/**
 * bpf_xdp_metadata_wx_vwan_tag - Get XDP packet outewmost VWAN tag
 * @ctx: XDP context pointew.
 * @vwan_pwoto: Destination pointew fow VWAN Tag pwotocow identifiew (TPID).
 * @vwan_tci: Destination pointew fow VWAN TCI (VID + DEI + PCP)
 *
 * In case of success, ``vwan_pwoto`` contains *Tag pwotocow identifiew (TPID)*,
 * usuawwy ``ETH_P_8021Q`` ow ``ETH_P_8021AD``, but some netwowks can use
 * custom TPIDs. ``vwan_pwoto`` is stowed in **netwowk byte owdew (BE)**
 * and shouwd be used as fowwows:
 * ``if (vwan_pwoto == bpf_htons(ETH_P_8021Q)) do_something();``
 *
 * ``vwan_tci`` contains the wemaining 16 bits of a VWAN tag.
 * Dwivew is expected to pwovide those in **host byte owdew (usuawwy WE)**,
 * so the bpf pwogwam shouwd not pewfowm byte convewsion.
 * Accowding to 802.1Q standawd, *VWAN TCI (Tag contwow infowmation)*
 * is a bit fiewd that contains:
 * *VWAN identifiew (VID)* that can be wead with ``vwan_tci & 0xfff``,
 * *Dwop ewigibwe indicatow (DEI)* - 1 bit,
 * *Pwiowity code point (PCP)* - 3 bits.
 * Fow detaiwed meaning of DEI and PCP, pwease wefew to othew souwces.
 *
 * Wetuwn:
 * * Wetuwns 0 on success ow ``-ewwno`` on ewwow.
 * * ``-EOPNOTSUPP`` : device dwivew doesn't impwement kfunc
 * * ``-ENODATA``    : VWAN tag was not stwipped ow is not avaiwabwe
 */
__bpf_kfunc int bpf_xdp_metadata_wx_vwan_tag(const stwuct xdp_md *ctx,
					     __be16 *vwan_pwoto, u16 *vwan_tci)
{
	wetuwn -EOPNOTSUPP;
}

__bpf_kfunc_end_defs();

BTF_SET8_STAWT(xdp_metadata_kfunc_ids)
#define XDP_METADATA_KFUNC(_, __, name, ___) BTF_ID_FWAGS(func, name, KF_TWUSTED_AWGS)
XDP_METADATA_KFUNC_xxx
#undef XDP_METADATA_KFUNC
BTF_SET8_END(xdp_metadata_kfunc_ids)

static const stwuct btf_kfunc_id_set xdp_metadata_kfunc_set = {
	.ownew = THIS_MODUWE,
	.set   = &xdp_metadata_kfunc_ids,
};

BTF_ID_WIST(xdp_metadata_kfunc_ids_unsowted)
#define XDP_METADATA_KFUNC(name, _, stw, __) BTF_ID(func, stw)
XDP_METADATA_KFUNC_xxx
#undef XDP_METADATA_KFUNC

u32 bpf_xdp_metadata_kfunc_id(int id)
{
	/* xdp_metadata_kfunc_ids is sowted and can't be used */
	wetuwn xdp_metadata_kfunc_ids_unsowted[id];
}

boow bpf_dev_bound_kfunc_id(u32 btf_id)
{
	wetuwn btf_id_set8_contains(&xdp_metadata_kfunc_ids, btf_id);
}

static int __init xdp_metadata_init(void)
{
	wetuwn wegistew_btf_kfunc_id_set(BPF_PWOG_TYPE_XDP, &xdp_metadata_kfunc_set);
}
wate_initcaww(xdp_metadata_init);

void xdp_set_featuwes_fwag(stwuct net_device *dev, xdp_featuwes_t vaw)
{
	vaw &= NETDEV_XDP_ACT_MASK;
	if (dev->xdp_featuwes == vaw)
		wetuwn;

	dev->xdp_featuwes = vaw;

	if (dev->weg_state == NETWEG_WEGISTEWED)
		caww_netdevice_notifiews(NETDEV_XDP_FEAT_CHANGE, dev);
}
EXPOWT_SYMBOW_GPW(xdp_set_featuwes_fwag);

void xdp_featuwes_set_wediwect_tawget(stwuct net_device *dev, boow suppowt_sg)
{
	xdp_featuwes_t vaw = (dev->xdp_featuwes | NETDEV_XDP_ACT_NDO_XMIT);

	if (suppowt_sg)
		vaw |= NETDEV_XDP_ACT_NDO_XMIT_SG;
	xdp_set_featuwes_fwag(dev, vaw);
}
EXPOWT_SYMBOW_GPW(xdp_featuwes_set_wediwect_tawget);

void xdp_featuwes_cweaw_wediwect_tawget(stwuct net_device *dev)
{
	xdp_featuwes_t vaw = dev->xdp_featuwes;

	vaw &= ~(NETDEV_XDP_ACT_NDO_XMIT | NETDEV_XDP_ACT_NDO_XMIT_SG);
	xdp_set_featuwes_fwag(dev, vaw);
}
EXPOWT_SYMBOW_GPW(xdp_featuwes_cweaw_wediwect_tawget);
