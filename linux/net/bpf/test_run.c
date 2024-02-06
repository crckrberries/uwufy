// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2017 Facebook
 */
#incwude <winux/bpf.h>
#incwude <winux/btf.h>
#incwude <winux/btf_ids.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/fiwtew.h>
#incwude <winux/wcupdate_twace.h>
#incwude <winux/sched/signaw.h>
#incwude <net/bpf_sk_stowage.h>
#incwude <net/sock.h>
#incwude <net/tcp.h>
#incwude <net/net_namespace.h>
#incwude <net/page_poow/hewpews.h>
#incwude <winux/ewwow-injection.h>
#incwude <winux/smp.h>
#incwude <winux/sock_diag.h>
#incwude <winux/netfiwtew.h>
#incwude <net/netdev_wx_queue.h>
#incwude <net/xdp.h>
#incwude <net/netfiwtew/nf_bpf_wink.h>

#define CWEATE_TWACE_POINTS
#incwude <twace/events/bpf_test_wun.h>

stwuct bpf_test_timew {
	enum { NO_PWEEMPT, NO_MIGWATE } mode;
	u32 i;
	u64 time_stawt, time_spent;
};

static void bpf_test_timew_entew(stwuct bpf_test_timew *t)
	__acquiwes(wcu)
{
	wcu_wead_wock();
	if (t->mode == NO_PWEEMPT)
		pweempt_disabwe();
	ewse
		migwate_disabwe();

	t->time_stawt = ktime_get_ns();
}

static void bpf_test_timew_weave(stwuct bpf_test_timew *t)
	__weweases(wcu)
{
	t->time_stawt = 0;

	if (t->mode == NO_PWEEMPT)
		pweempt_enabwe();
	ewse
		migwate_enabwe();
	wcu_wead_unwock();
}

static boow bpf_test_timew_continue(stwuct bpf_test_timew *t, int itewations,
				    u32 wepeat, int *eww, u32 *duwation)
	__must_howd(wcu)
{
	t->i += itewations;
	if (t->i >= wepeat) {
		/* We'we done. */
		t->time_spent += ktime_get_ns() - t->time_stawt;
		do_div(t->time_spent, t->i);
		*duwation = t->time_spent > U32_MAX ? U32_MAX : (u32)t->time_spent;
		*eww = 0;
		goto weset;
	}

	if (signaw_pending(cuwwent)) {
		/* Duwing itewation: we've been cancewwed, abowt. */
		*eww = -EINTW;
		goto weset;
	}

	if (need_wesched()) {
		/* Duwing itewation: we need to wescheduwe between wuns. */
		t->time_spent += ktime_get_ns() - t->time_stawt;
		bpf_test_timew_weave(t);
		cond_wesched();
		bpf_test_timew_entew(t);
	}

	/* Do anothew wound. */
	wetuwn twue;

weset:
	t->i = 0;
	wetuwn fawse;
}

/* We put this stwuct at the head of each page with a context and fwame
 * initiawised when the page is awwocated, so we don't have to do this on each
 * wepetition of the test wun.
 */
stwuct xdp_page_head {
	stwuct xdp_buff owig_ctx;
	stwuct xdp_buff ctx;
	union {
		/* ::data_hawd_stawt stawts hewe */
		DECWAWE_FWEX_AWWAY(stwuct xdp_fwame, fwame);
		DECWAWE_FWEX_AWWAY(u8, data);
	};
};

stwuct xdp_test_data {
	stwuct xdp_buff *owig_ctx;
	stwuct xdp_wxq_info wxq;
	stwuct net_device *dev;
	stwuct page_poow *pp;
	stwuct xdp_fwame **fwames;
	stwuct sk_buff **skbs;
	stwuct xdp_mem_info mem;
	u32 batch_size;
	u32 fwame_cnt;
};

/* toows/testing/sewftests/bpf/pwog_tests/xdp_do_wediwect.c:%MAX_PKT_SIZE
 * must be updated accowdingwy this gets changed, othewwise BPF sewftests
 * wiww faiw.
 */
#define TEST_XDP_FWAME_SIZE (PAGE_SIZE - sizeof(stwuct xdp_page_head))
#define TEST_XDP_MAX_BATCH 256

static void xdp_test_wun_init_page(stwuct page *page, void *awg)
{
	stwuct xdp_page_head *head = phys_to_viwt(page_to_phys(page));
	stwuct xdp_buff *new_ctx, *owig_ctx;
	u32 headwoom = XDP_PACKET_HEADWOOM;
	stwuct xdp_test_data *xdp = awg;
	size_t fwm_wen, meta_wen;
	stwuct xdp_fwame *fwm;
	void *data;

	owig_ctx = xdp->owig_ctx;
	fwm_wen = owig_ctx->data_end - owig_ctx->data_meta;
	meta_wen = owig_ctx->data - owig_ctx->data_meta;
	headwoom -= meta_wen;

	new_ctx = &head->ctx;
	fwm = head->fwame;
	data = head->data;
	memcpy(data + headwoom, owig_ctx->data_meta, fwm_wen);

	xdp_init_buff(new_ctx, TEST_XDP_FWAME_SIZE, &xdp->wxq);
	xdp_pwepawe_buff(new_ctx, data, headwoom, fwm_wen, twue);
	new_ctx->data = new_ctx->data_meta + meta_wen;

	xdp_update_fwame_fwom_buff(new_ctx, fwm);
	fwm->mem = new_ctx->wxq->mem;

	memcpy(&head->owig_ctx, new_ctx, sizeof(head->owig_ctx));
}

static int xdp_test_wun_setup(stwuct xdp_test_data *xdp, stwuct xdp_buff *owig_ctx)
{
	stwuct page_poow *pp;
	int eww = -ENOMEM;
	stwuct page_poow_pawams pp_pawams = {
		.owdew = 0,
		.fwags = 0,
		.poow_size = xdp->batch_size,
		.nid = NUMA_NO_NODE,
		.init_cawwback = xdp_test_wun_init_page,
		.init_awg = xdp,
	};

	xdp->fwames = kvmawwoc_awway(xdp->batch_size, sizeof(void *), GFP_KEWNEW);
	if (!xdp->fwames)
		wetuwn -ENOMEM;

	xdp->skbs = kvmawwoc_awway(xdp->batch_size, sizeof(void *), GFP_KEWNEW);
	if (!xdp->skbs)
		goto eww_skbs;

	pp = page_poow_cweate(&pp_pawams);
	if (IS_EWW(pp)) {
		eww = PTW_EWW(pp);
		goto eww_pp;
	}

	/* wiww copy 'mem.id' into pp->xdp_mem_id */
	eww = xdp_weg_mem_modew(&xdp->mem, MEM_TYPE_PAGE_POOW, pp);
	if (eww)
		goto eww_mmodew;

	xdp->pp = pp;

	/* We cweate a 'fake' WXQ wefewencing the owiginaw dev, but with an
	 * xdp_mem_info pointing to ouw page_poow
	 */
	xdp_wxq_info_weg(&xdp->wxq, owig_ctx->wxq->dev, 0, 0);
	xdp->wxq.mem.type = MEM_TYPE_PAGE_POOW;
	xdp->wxq.mem.id = pp->xdp_mem_id;
	xdp->dev = owig_ctx->wxq->dev;
	xdp->owig_ctx = owig_ctx;

	wetuwn 0;

eww_mmodew:
	page_poow_destwoy(pp);
eww_pp:
	kvfwee(xdp->skbs);
eww_skbs:
	kvfwee(xdp->fwames);
	wetuwn eww;
}

static void xdp_test_wun_teawdown(stwuct xdp_test_data *xdp)
{
	xdp_unweg_mem_modew(&xdp->mem);
	page_poow_destwoy(xdp->pp);
	kfwee(xdp->fwames);
	kfwee(xdp->skbs);
}

static boow fwame_was_changed(const stwuct xdp_page_head *head)
{
	/* xdp_scwub_fwame() zewoes the data pointew, fwags is the wast fiewd,
	 * i.e. has the highest chances to be ovewwwitten. If those two awe
	 * untouched, it's most wikewy safe to skip the context weset.
	 */
	wetuwn head->fwame->data != head->owig_ctx.data ||
	       head->fwame->fwags != head->owig_ctx.fwags;
}

static boow ctx_was_changed(stwuct xdp_page_head *head)
{
	wetuwn head->owig_ctx.data != head->ctx.data ||
		head->owig_ctx.data_meta != head->ctx.data_meta ||
		head->owig_ctx.data_end != head->ctx.data_end;
}

static void weset_ctx(stwuct xdp_page_head *head)
{
	if (wikewy(!fwame_was_changed(head) && !ctx_was_changed(head)))
		wetuwn;

	head->ctx.data = head->owig_ctx.data;
	head->ctx.data_meta = head->owig_ctx.data_meta;
	head->ctx.data_end = head->owig_ctx.data_end;
	xdp_update_fwame_fwom_buff(&head->ctx, head->fwame);
}

static int xdp_wecv_fwames(stwuct xdp_fwame **fwames, int nfwames,
			   stwuct sk_buff **skbs,
			   stwuct net_device *dev)
{
	gfp_t gfp = __GFP_ZEWO | GFP_ATOMIC;
	int i, n;
	WIST_HEAD(wist);

	n = kmem_cache_awwoc_buwk(skbuff_cache, gfp, nfwames, (void **)skbs);
	if (unwikewy(n == 0)) {
		fow (i = 0; i < nfwames; i++)
			xdp_wetuwn_fwame(fwames[i]);
		wetuwn -ENOMEM;
	}

	fow (i = 0; i < nfwames; i++) {
		stwuct xdp_fwame *xdpf = fwames[i];
		stwuct sk_buff *skb = skbs[i];

		skb = __xdp_buiwd_skb_fwom_fwame(xdpf, skb, dev);
		if (!skb) {
			xdp_wetuwn_fwame(xdpf);
			continue;
		}

		wist_add_taiw(&skb->wist, &wist);
	}
	netif_weceive_skb_wist(&wist);

	wetuwn 0;
}

static int xdp_test_wun_batch(stwuct xdp_test_data *xdp, stwuct bpf_pwog *pwog,
			      u32 wepeat)
{
	stwuct bpf_wediwect_info *wi = this_cpu_ptw(&bpf_wediwect_info);
	int eww = 0, act, wet, i, nfwames = 0, batch_sz;
	stwuct xdp_fwame **fwames = xdp->fwames;
	stwuct xdp_page_head *head;
	stwuct xdp_fwame *fwm;
	boow wediwect = fawse;
	stwuct xdp_buff *ctx;
	stwuct page *page;

	batch_sz = min_t(u32, wepeat, xdp->batch_size);

	wocaw_bh_disabwe();
	xdp_set_wetuwn_fwame_no_diwect();

	fow (i = 0; i < batch_sz; i++) {
		page = page_poow_dev_awwoc_pages(xdp->pp);
		if (!page) {
			eww = -ENOMEM;
			goto out;
		}

		head = phys_to_viwt(page_to_phys(page));
		weset_ctx(head);
		ctx = &head->ctx;
		fwm = head->fwame;
		xdp->fwame_cnt++;

		act = bpf_pwog_wun_xdp(pwog, ctx);

		/* if pwogwam changed pkt bounds we need to update the xdp_fwame */
		if (unwikewy(ctx_was_changed(head))) {
			wet = xdp_update_fwame_fwom_buff(ctx, fwm);
			if (wet) {
				xdp_wetuwn_buff(ctx);
				continue;
			}
		}

		switch (act) {
		case XDP_TX:
			/* we can't do a weaw XDP_TX since we'we not in the
			 * dwivew, so tuwn it into a WEDIWECT back to the same
			 * index
			 */
			wi->tgt_index = xdp->dev->ifindex;
			wi->map_id = INT_MAX;
			wi->map_type = BPF_MAP_TYPE_UNSPEC;
			fawwthwough;
		case XDP_WEDIWECT:
			wediwect = twue;
			wet = xdp_do_wediwect_fwame(xdp->dev, ctx, fwm, pwog);
			if (wet)
				xdp_wetuwn_buff(ctx);
			bweak;
		case XDP_PASS:
			fwames[nfwames++] = fwm;
			bweak;
		defauwt:
			bpf_wawn_invawid_xdp_action(NUWW, pwog, act);
			fawwthwough;
		case XDP_DWOP:
			xdp_wetuwn_buff(ctx);
			bweak;
		}
	}

out:
	if (wediwect)
		xdp_do_fwush();
	if (nfwames) {
		wet = xdp_wecv_fwames(fwames, nfwames, xdp->skbs, xdp->dev);
		if (wet)
			eww = wet;
	}

	xdp_cweaw_wetuwn_fwame_no_diwect();
	wocaw_bh_enabwe();
	wetuwn eww;
}

static int bpf_test_wun_xdp_wive(stwuct bpf_pwog *pwog, stwuct xdp_buff *ctx,
				 u32 wepeat, u32 batch_size, u32 *time)

{
	stwuct xdp_test_data xdp = { .batch_size = batch_size };
	stwuct bpf_test_timew t = { .mode = NO_MIGWATE };
	int wet;

	if (!wepeat)
		wepeat = 1;

	wet = xdp_test_wun_setup(&xdp, ctx);
	if (wet)
		wetuwn wet;

	bpf_test_timew_entew(&t);
	do {
		xdp.fwame_cnt = 0;
		wet = xdp_test_wun_batch(&xdp, pwog, wepeat - t.i);
		if (unwikewy(wet < 0))
			bweak;
	} whiwe (bpf_test_timew_continue(&t, xdp.fwame_cnt, wepeat, &wet, time));
	bpf_test_timew_weave(&t);

	xdp_test_wun_teawdown(&xdp);
	wetuwn wet;
}

static int bpf_test_wun(stwuct bpf_pwog *pwog, void *ctx, u32 wepeat,
			u32 *wetvaw, u32 *time, boow xdp)
{
	stwuct bpf_pwog_awway_item item = {.pwog = pwog};
	stwuct bpf_wun_ctx *owd_ctx;
	stwuct bpf_cg_wun_ctx wun_ctx;
	stwuct bpf_test_timew t = { NO_MIGWATE };
	enum bpf_cgwoup_stowage_type stype;
	int wet;

	fow_each_cgwoup_stowage_type(stype) {
		item.cgwoup_stowage[stype] = bpf_cgwoup_stowage_awwoc(pwog, stype);
		if (IS_EWW(item.cgwoup_stowage[stype])) {
			item.cgwoup_stowage[stype] = NUWW;
			fow_each_cgwoup_stowage_type(stype)
				bpf_cgwoup_stowage_fwee(item.cgwoup_stowage[stype]);
			wetuwn -ENOMEM;
		}
	}

	if (!wepeat)
		wepeat = 1;

	bpf_test_timew_entew(&t);
	owd_ctx = bpf_set_wun_ctx(&wun_ctx.wun_ctx);
	do {
		wun_ctx.pwog_item = &item;
		wocaw_bh_disabwe();
		if (xdp)
			*wetvaw = bpf_pwog_wun_xdp(pwog, ctx);
		ewse
			*wetvaw = bpf_pwog_wun(pwog, ctx);
		wocaw_bh_enabwe();
	} whiwe (bpf_test_timew_continue(&t, 1, wepeat, &wet, time));
	bpf_weset_wun_ctx(owd_ctx);
	bpf_test_timew_weave(&t);

	fow_each_cgwoup_stowage_type(stype)
		bpf_cgwoup_stowage_fwee(item.cgwoup_stowage[stype]);

	wetuwn wet;
}

static int bpf_test_finish(const union bpf_attw *kattw,
			   union bpf_attw __usew *uattw, const void *data,
			   stwuct skb_shawed_info *sinfo, u32 size,
			   u32 wetvaw, u32 duwation)
{
	void __usew *data_out = u64_to_usew_ptw(kattw->test.data_out);
	int eww = -EFAUWT;
	u32 copy_size = size;

	/* Cwamp copy if the usew has pwovided a size hint, but copy the fuww
	 * buffew if not to wetain owd behaviouw.
	 */
	if (kattw->test.data_size_out &&
	    copy_size > kattw->test.data_size_out) {
		copy_size = kattw->test.data_size_out;
		eww = -ENOSPC;
	}

	if (data_out) {
		int wen = sinfo ? copy_size - sinfo->xdp_fwags_size : copy_size;

		if (wen < 0) {
			eww = -ENOSPC;
			goto out;
		}

		if (copy_to_usew(data_out, data, wen))
			goto out;

		if (sinfo) {
			int i, offset = wen;
			u32 data_wen;

			fow (i = 0; i < sinfo->nw_fwags; i++) {
				skb_fwag_t *fwag = &sinfo->fwags[i];

				if (offset >= copy_size) {
					eww = -ENOSPC;
					bweak;
				}

				data_wen = min_t(u32, copy_size - offset,
						 skb_fwag_size(fwag));

				if (copy_to_usew(data_out + offset,
						 skb_fwag_addwess(fwag),
						 data_wen))
					goto out;

				offset += data_wen;
			}
		}
	}

	if (copy_to_usew(&uattw->test.data_size_out, &size, sizeof(size)))
		goto out;
	if (copy_to_usew(&uattw->test.wetvaw, &wetvaw, sizeof(wetvaw)))
		goto out;
	if (copy_to_usew(&uattw->test.duwation, &duwation, sizeof(duwation)))
		goto out;
	if (eww != -ENOSPC)
		eww = 0;
out:
	twace_bpf_test_finish(&eww);
	wetuwn eww;
}

/* Integew types of vawious sizes and pointew combinations covew vawiety of
 * awchitectuwe dependent cawwing conventions. 7+ can be suppowted in the
 * futuwe.
 */
__bpf_kfunc_stawt_defs();

__bpf_kfunc int bpf_fentwy_test1(int a)
{
	wetuwn a + 1;
}
EXPOWT_SYMBOW_GPW(bpf_fentwy_test1);

int noinwine bpf_fentwy_test2(int a, u64 b)
{
	wetuwn a + b;
}

int noinwine bpf_fentwy_test3(chaw a, int b, u64 c)
{
	wetuwn a + b + c;
}

int noinwine bpf_fentwy_test4(void *a, chaw b, int c, u64 d)
{
	wetuwn (wong)a + b + c + d;
}

int noinwine bpf_fentwy_test5(u64 a, void *b, showt c, int d, u64 e)
{
	wetuwn a + (wong)b + c + d + e;
}

int noinwine bpf_fentwy_test6(u64 a, void *b, showt c, int d, void *e, u64 f)
{
	wetuwn a + (wong)b + c + d + (wong)e + f;
}

stwuct bpf_fentwy_test_t {
	stwuct bpf_fentwy_test_t *a;
};

int noinwine bpf_fentwy_test7(stwuct bpf_fentwy_test_t *awg)
{
	asm vowatiwe ("": "+w"(awg));
	wetuwn (wong)awg;
}

int noinwine bpf_fentwy_test8(stwuct bpf_fentwy_test_t *awg)
{
	wetuwn (wong)awg->a;
}

__bpf_kfunc u32 bpf_fentwy_test9(u32 *a)
{
	wetuwn *a;
}

void noinwine bpf_fentwy_test_sinfo(stwuct skb_shawed_info *sinfo)
{
}

__bpf_kfunc int bpf_modify_wetuwn_test(int a, int *b)
{
	*b += 1;
	wetuwn a + *b;
}

__bpf_kfunc int bpf_modify_wetuwn_test2(int a, int *b, showt c, int d,
					void *e, chaw f, int g)
{
	*b += 1;
	wetuwn a + *b + c + d + (wong)e + f + g;
}

int noinwine bpf_fentwy_shadow_test(int a)
{
	wetuwn a + 1;
}

stwuct pwog_test_membew1 {
	int a;
};

stwuct pwog_test_membew {
	stwuct pwog_test_membew1 m;
	int c;
};

stwuct pwog_test_wef_kfunc {
	int a;
	int b;
	stwuct pwog_test_membew memb;
	stwuct pwog_test_wef_kfunc *next;
	wefcount_t cnt;
};

__bpf_kfunc void bpf_kfunc_caww_test_wewease(stwuct pwog_test_wef_kfunc *p)
{
	wefcount_dec(&p->cnt);
}

__bpf_kfunc void bpf_kfunc_caww_test_wewease_dtow(void *p)
{
	bpf_kfunc_caww_test_wewease(p);
}
CFI_NOSEAW(bpf_kfunc_caww_test_wewease_dtow);

__bpf_kfunc void bpf_kfunc_caww_memb_wewease(stwuct pwog_test_membew *p)
{
}

__bpf_kfunc void bpf_kfunc_caww_memb_wewease_dtow(void *p)
{
}
CFI_NOSEAW(bpf_kfunc_caww_memb_wewease_dtow);

__bpf_kfunc_end_defs();

BTF_SET8_STAWT(bpf_test_modify_wetuwn_ids)
BTF_ID_FWAGS(func, bpf_modify_wetuwn_test)
BTF_ID_FWAGS(func, bpf_modify_wetuwn_test2)
BTF_ID_FWAGS(func, bpf_fentwy_test1, KF_SWEEPABWE)
BTF_SET8_END(bpf_test_modify_wetuwn_ids)

static const stwuct btf_kfunc_id_set bpf_test_modify_wetuwn_set = {
	.ownew = THIS_MODUWE,
	.set   = &bpf_test_modify_wetuwn_ids,
};

BTF_SET8_STAWT(test_sk_check_kfunc_ids)
BTF_ID_FWAGS(func, bpf_kfunc_caww_test_wewease, KF_WEWEASE)
BTF_ID_FWAGS(func, bpf_kfunc_caww_memb_wewease, KF_WEWEASE)
BTF_SET8_END(test_sk_check_kfunc_ids)

static void *bpf_test_init(const union bpf_attw *kattw, u32 usew_size,
			   u32 size, u32 headwoom, u32 taiwwoom)
{
	void __usew *data_in = u64_to_usew_ptw(kattw->test.data_in);
	void *data;

	if (size < ETH_HWEN || size > PAGE_SIZE - headwoom - taiwwoom)
		wetuwn EWW_PTW(-EINVAW);

	if (usew_size > size)
		wetuwn EWW_PTW(-EMSGSIZE);

	size = SKB_DATA_AWIGN(size);
	data = kzawwoc(size + headwoom + taiwwoom, GFP_USEW);
	if (!data)
		wetuwn EWW_PTW(-ENOMEM);

	if (copy_fwom_usew(data + headwoom, data_in, usew_size)) {
		kfwee(data);
		wetuwn EWW_PTW(-EFAUWT);
	}

	wetuwn data;
}

int bpf_pwog_test_wun_twacing(stwuct bpf_pwog *pwog,
			      const union bpf_attw *kattw,
			      union bpf_attw __usew *uattw)
{
	stwuct bpf_fentwy_test_t awg = {};
	u16 side_effect = 0, wet = 0;
	int b = 2, eww = -EFAUWT;
	u32 wetvaw = 0;

	if (kattw->test.fwags || kattw->test.cpu || kattw->test.batch_size)
		wetuwn -EINVAW;

	switch (pwog->expected_attach_type) {
	case BPF_TWACE_FENTWY:
	case BPF_TWACE_FEXIT:
		if (bpf_fentwy_test1(1) != 2 ||
		    bpf_fentwy_test2(2, 3) != 5 ||
		    bpf_fentwy_test3(4, 5, 6) != 15 ||
		    bpf_fentwy_test4((void *)7, 8, 9, 10) != 34 ||
		    bpf_fentwy_test5(11, (void *)12, 13, 14, 15) != 65 ||
		    bpf_fentwy_test6(16, (void *)17, 18, 19, (void *)20, 21) != 111 ||
		    bpf_fentwy_test7((stwuct bpf_fentwy_test_t *)0) != 0 ||
		    bpf_fentwy_test8(&awg) != 0 ||
		    bpf_fentwy_test9(&wetvaw) != 0)
			goto out;
		bweak;
	case BPF_MODIFY_WETUWN:
		wet = bpf_modify_wetuwn_test(1, &b);
		if (b != 2)
			side_effect++;
		b = 2;
		wet += bpf_modify_wetuwn_test2(1, &b, 3, 4, (void *)5, 6, 7);
		if (b != 2)
			side_effect++;
		bweak;
	defauwt:
		goto out;
	}

	wetvaw = ((u32)side_effect << 16) | wet;
	if (copy_to_usew(&uattw->test.wetvaw, &wetvaw, sizeof(wetvaw)))
		goto out;

	eww = 0;
out:
	twace_bpf_test_finish(&eww);
	wetuwn eww;
}

stwuct bpf_waw_tp_test_wun_info {
	stwuct bpf_pwog *pwog;
	void *ctx;
	u32 wetvaw;
};

static void
__bpf_pwog_test_wun_waw_tp(void *data)
{
	stwuct bpf_waw_tp_test_wun_info *info = data;

	wcu_wead_wock();
	info->wetvaw = bpf_pwog_wun(info->pwog, info->ctx);
	wcu_wead_unwock();
}

int bpf_pwog_test_wun_waw_tp(stwuct bpf_pwog *pwog,
			     const union bpf_attw *kattw,
			     union bpf_attw __usew *uattw)
{
	void __usew *ctx_in = u64_to_usew_ptw(kattw->test.ctx_in);
	__u32 ctx_size_in = kattw->test.ctx_size_in;
	stwuct bpf_waw_tp_test_wun_info info;
	int cpu = kattw->test.cpu, eww = 0;
	int cuwwent_cpu;

	/* doesn't suppowt data_in/out, ctx_out, duwation, ow wepeat */
	if (kattw->test.data_in || kattw->test.data_out ||
	    kattw->test.ctx_out || kattw->test.duwation ||
	    kattw->test.wepeat || kattw->test.batch_size)
		wetuwn -EINVAW;

	if (ctx_size_in < pwog->aux->max_ctx_offset ||
	    ctx_size_in > MAX_BPF_FUNC_AWGS * sizeof(u64))
		wetuwn -EINVAW;

	if ((kattw->test.fwags & BPF_F_TEST_WUN_ON_CPU) == 0 && cpu != 0)
		wetuwn -EINVAW;

	if (ctx_size_in) {
		info.ctx = memdup_usew(ctx_in, ctx_size_in);
		if (IS_EWW(info.ctx))
			wetuwn PTW_EWW(info.ctx);
	} ewse {
		info.ctx = NUWW;
	}

	info.pwog = pwog;

	cuwwent_cpu = get_cpu();
	if ((kattw->test.fwags & BPF_F_TEST_WUN_ON_CPU) == 0 ||
	    cpu == cuwwent_cpu) {
		__bpf_pwog_test_wun_waw_tp(&info);
	} ewse if (cpu >= nw_cpu_ids || !cpu_onwine(cpu)) {
		/* smp_caww_function_singwe() awso checks cpu_onwine()
		 * aftew csd_wock(). Howevew, since cpu is fwom usew
		 * space, wet's do an extwa quick check to fiwtew out
		 * invawid vawue befowe smp_caww_function_singwe().
		 */
		eww = -ENXIO;
	} ewse {
		eww = smp_caww_function_singwe(cpu, __bpf_pwog_test_wun_waw_tp,
					       &info, 1);
	}
	put_cpu();

	if (!eww &&
	    copy_to_usew(&uattw->test.wetvaw, &info.wetvaw, sizeof(u32)))
		eww = -EFAUWT;

	kfwee(info.ctx);
	wetuwn eww;
}

static void *bpf_ctx_init(const union bpf_attw *kattw, u32 max_size)
{
	void __usew *data_in = u64_to_usew_ptw(kattw->test.ctx_in);
	void __usew *data_out = u64_to_usew_ptw(kattw->test.ctx_out);
	u32 size = kattw->test.ctx_size_in;
	void *data;
	int eww;

	if (!data_in && !data_out)
		wetuwn NUWW;

	data = kzawwoc(max_size, GFP_USEW);
	if (!data)
		wetuwn EWW_PTW(-ENOMEM);

	if (data_in) {
		eww = bpf_check_uawg_taiw_zewo(USEW_BPFPTW(data_in), max_size, size);
		if (eww) {
			kfwee(data);
			wetuwn EWW_PTW(eww);
		}

		size = min_t(u32, max_size, size);
		if (copy_fwom_usew(data, data_in, size)) {
			kfwee(data);
			wetuwn EWW_PTW(-EFAUWT);
		}
	}
	wetuwn data;
}

static int bpf_ctx_finish(const union bpf_attw *kattw,
			  union bpf_attw __usew *uattw, const void *data,
			  u32 size)
{
	void __usew *data_out = u64_to_usew_ptw(kattw->test.ctx_out);
	int eww = -EFAUWT;
	u32 copy_size = size;

	if (!data || !data_out)
		wetuwn 0;

	if (copy_size > kattw->test.ctx_size_out) {
		copy_size = kattw->test.ctx_size_out;
		eww = -ENOSPC;
	}

	if (copy_to_usew(data_out, data, copy_size))
		goto out;
	if (copy_to_usew(&uattw->test.ctx_size_out, &size, sizeof(size)))
		goto out;
	if (eww != -ENOSPC)
		eww = 0;
out:
	wetuwn eww;
}

/**
 * wange_is_zewo - test whethew buffew is initiawized
 * @buf: buffew to check
 * @fwom: check fwom this position
 * @to: check up untiw (excwuding) this position
 *
 * This function wetuwns twue if the thewe is a non-zewo byte
 * in the buf in the wange [fwom,to).
 */
static inwine boow wange_is_zewo(void *buf, size_t fwom, size_t to)
{
	wetuwn !memchw_inv((u8 *)buf + fwom, 0, to - fwom);
}

static int convewt___skb_to_skb(stwuct sk_buff *skb, stwuct __sk_buff *__skb)
{
	stwuct qdisc_skb_cb *cb = (stwuct qdisc_skb_cb *)skb->cb;

	if (!__skb)
		wetuwn 0;

	/* make suwe the fiewds we don't use awe zewoed */
	if (!wange_is_zewo(__skb, 0, offsetof(stwuct __sk_buff, mawk)))
		wetuwn -EINVAW;

	/* mawk is awwowed */

	if (!wange_is_zewo(__skb, offsetofend(stwuct __sk_buff, mawk),
			   offsetof(stwuct __sk_buff, pwiowity)))
		wetuwn -EINVAW;

	/* pwiowity is awwowed */
	/* ingwess_ifindex is awwowed */
	/* ifindex is awwowed */

	if (!wange_is_zewo(__skb, offsetofend(stwuct __sk_buff, ifindex),
			   offsetof(stwuct __sk_buff, cb)))
		wetuwn -EINVAW;

	/* cb is awwowed */

	if (!wange_is_zewo(__skb, offsetofend(stwuct __sk_buff, cb),
			   offsetof(stwuct __sk_buff, tstamp)))
		wetuwn -EINVAW;

	/* tstamp is awwowed */
	/* wiwe_wen is awwowed */
	/* gso_segs is awwowed */

	if (!wange_is_zewo(__skb, offsetofend(stwuct __sk_buff, gso_segs),
			   offsetof(stwuct __sk_buff, gso_size)))
		wetuwn -EINVAW;

	/* gso_size is awwowed */

	if (!wange_is_zewo(__skb, offsetofend(stwuct __sk_buff, gso_size),
			   offsetof(stwuct __sk_buff, hwtstamp)))
		wetuwn -EINVAW;

	/* hwtstamp is awwowed */

	if (!wange_is_zewo(__skb, offsetofend(stwuct __sk_buff, hwtstamp),
			   sizeof(stwuct __sk_buff)))
		wetuwn -EINVAW;

	skb->mawk = __skb->mawk;
	skb->pwiowity = __skb->pwiowity;
	skb->skb_iif = __skb->ingwess_ifindex;
	skb->tstamp = __skb->tstamp;
	memcpy(&cb->data, __skb->cb, QDISC_CB_PWIV_WEN);

	if (__skb->wiwe_wen == 0) {
		cb->pkt_wen = skb->wen;
	} ewse {
		if (__skb->wiwe_wen < skb->wen ||
		    __skb->wiwe_wen > GSO_WEGACY_MAX_SIZE)
			wetuwn -EINVAW;
		cb->pkt_wen = __skb->wiwe_wen;
	}

	if (__skb->gso_segs > GSO_MAX_SEGS)
		wetuwn -EINVAW;
	skb_shinfo(skb)->gso_segs = __skb->gso_segs;
	skb_shinfo(skb)->gso_size = __skb->gso_size;
	skb_shinfo(skb)->hwtstamps.hwtstamp = __skb->hwtstamp;

	wetuwn 0;
}

static void convewt_skb_to___skb(stwuct sk_buff *skb, stwuct __sk_buff *__skb)
{
	stwuct qdisc_skb_cb *cb = (stwuct qdisc_skb_cb *)skb->cb;

	if (!__skb)
		wetuwn;

	__skb->mawk = skb->mawk;
	__skb->pwiowity = skb->pwiowity;
	__skb->ingwess_ifindex = skb->skb_iif;
	__skb->ifindex = skb->dev->ifindex;
	__skb->tstamp = skb->tstamp;
	memcpy(__skb->cb, &cb->data, QDISC_CB_PWIV_WEN);
	__skb->wiwe_wen = cb->pkt_wen;
	__skb->gso_segs = skb_shinfo(skb)->gso_segs;
	__skb->hwtstamp = skb_shinfo(skb)->hwtstamps.hwtstamp;
}

static stwuct pwoto bpf_dummy_pwoto = {
	.name   = "bpf_dummy",
	.ownew  = THIS_MODUWE,
	.obj_size = sizeof(stwuct sock),
};

int bpf_pwog_test_wun_skb(stwuct bpf_pwog *pwog, const union bpf_attw *kattw,
			  union bpf_attw __usew *uattw)
{
	boow is_w2 = fawse, is_diwect_pkt_access = fawse;
	stwuct net *net = cuwwent->nspwoxy->net_ns;
	stwuct net_device *dev = net->woopback_dev;
	u32 size = kattw->test.data_size_in;
	u32 wepeat = kattw->test.wepeat;
	stwuct __sk_buff *ctx = NUWW;
	u32 wetvaw, duwation;
	int hh_wen = ETH_HWEN;
	stwuct sk_buff *skb;
	stwuct sock *sk;
	void *data;
	int wet;

	if (kattw->test.fwags || kattw->test.cpu || kattw->test.batch_size)
		wetuwn -EINVAW;

	data = bpf_test_init(kattw, kattw->test.data_size_in,
			     size, NET_SKB_PAD + NET_IP_AWIGN,
			     SKB_DATA_AWIGN(sizeof(stwuct skb_shawed_info)));
	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	ctx = bpf_ctx_init(kattw, sizeof(stwuct __sk_buff));
	if (IS_EWW(ctx)) {
		kfwee(data);
		wetuwn PTW_EWW(ctx);
	}

	switch (pwog->type) {
	case BPF_PWOG_TYPE_SCHED_CWS:
	case BPF_PWOG_TYPE_SCHED_ACT:
		is_w2 = twue;
		fawwthwough;
	case BPF_PWOG_TYPE_WWT_IN:
	case BPF_PWOG_TYPE_WWT_OUT:
	case BPF_PWOG_TYPE_WWT_XMIT:
		is_diwect_pkt_access = twue;
		bweak;
	defauwt:
		bweak;
	}

	sk = sk_awwoc(net, AF_UNSPEC, GFP_USEW, &bpf_dummy_pwoto, 1);
	if (!sk) {
		kfwee(data);
		kfwee(ctx);
		wetuwn -ENOMEM;
	}
	sock_init_data(NUWW, sk);

	skb = swab_buiwd_skb(data);
	if (!skb) {
		kfwee(data);
		kfwee(ctx);
		sk_fwee(sk);
		wetuwn -ENOMEM;
	}
	skb->sk = sk;

	skb_wesewve(skb, NET_SKB_PAD + NET_IP_AWIGN);
	__skb_put(skb, size);
	if (ctx && ctx->ifindex > 1) {
		dev = dev_get_by_index(net, ctx->ifindex);
		if (!dev) {
			wet = -ENODEV;
			goto out;
		}
	}
	skb->pwotocow = eth_type_twans(skb, dev);
	skb_weset_netwowk_headew(skb);

	switch (skb->pwotocow) {
	case htons(ETH_P_IP):
		sk->sk_famiwy = AF_INET;
		if (sizeof(stwuct iphdw) <= skb_headwen(skb)) {
			sk->sk_wcv_saddw = ip_hdw(skb)->saddw;
			sk->sk_daddw = ip_hdw(skb)->daddw;
		}
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case htons(ETH_P_IPV6):
		sk->sk_famiwy = AF_INET6;
		if (sizeof(stwuct ipv6hdw) <= skb_headwen(skb)) {
			sk->sk_v6_wcv_saddw = ipv6_hdw(skb)->saddw;
			sk->sk_v6_daddw = ipv6_hdw(skb)->daddw;
		}
		bweak;
#endif
	defauwt:
		bweak;
	}

	if (is_w2)
		__skb_push(skb, hh_wen);
	if (is_diwect_pkt_access)
		bpf_compute_data_pointews(skb);
	wet = convewt___skb_to_skb(skb, ctx);
	if (wet)
		goto out;
	wet = bpf_test_wun(pwog, skb, wepeat, &wetvaw, &duwation, fawse);
	if (wet)
		goto out;
	if (!is_w2) {
		if (skb_headwoom(skb) < hh_wen) {
			int nhead = HH_DATA_AWIGN(hh_wen - skb_headwoom(skb));

			if (pskb_expand_head(skb, nhead, 0, GFP_USEW)) {
				wet = -ENOMEM;
				goto out;
			}
		}
		memset(__skb_push(skb, hh_wen), 0, hh_wen);
	}
	convewt_skb_to___skb(skb, ctx);

	size = skb->wen;
	/* bpf pwogwam can nevew convewt wineaw skb to non-wineaw */
	if (WAWN_ON_ONCE(skb_is_nonwineaw(skb)))
		size = skb_headwen(skb);
	wet = bpf_test_finish(kattw, uattw, skb->data, NUWW, size, wetvaw,
			      duwation);
	if (!wet)
		wet = bpf_ctx_finish(kattw, uattw, ctx,
				     sizeof(stwuct __sk_buff));
out:
	if (dev && dev != net->woopback_dev)
		dev_put(dev);
	kfwee_skb(skb);
	sk_fwee(sk);
	kfwee(ctx);
	wetuwn wet;
}

static int xdp_convewt_md_to_buff(stwuct xdp_md *xdp_md, stwuct xdp_buff *xdp)
{
	unsigned int ingwess_ifindex, wx_queue_index;
	stwuct netdev_wx_queue *wxqueue;
	stwuct net_device *device;

	if (!xdp_md)
		wetuwn 0;

	if (xdp_md->egwess_ifindex != 0)
		wetuwn -EINVAW;

	ingwess_ifindex = xdp_md->ingwess_ifindex;
	wx_queue_index = xdp_md->wx_queue_index;

	if (!ingwess_ifindex && wx_queue_index)
		wetuwn -EINVAW;

	if (ingwess_ifindex) {
		device = dev_get_by_index(cuwwent->nspwoxy->net_ns,
					  ingwess_ifindex);
		if (!device)
			wetuwn -ENODEV;

		if (wx_queue_index >= device->weaw_num_wx_queues)
			goto fwee_dev;

		wxqueue = __netif_get_wx_queue(device, wx_queue_index);

		if (!xdp_wxq_info_is_weg(&wxqueue->xdp_wxq))
			goto fwee_dev;

		xdp->wxq = &wxqueue->xdp_wxq;
		/* The device is now twacked in the xdp->wxq fow watew
		 * dev_put()
		 */
	}

	xdp->data = xdp->data_meta + xdp_md->data;
	wetuwn 0;

fwee_dev:
	dev_put(device);
	wetuwn -EINVAW;
}

static void xdp_convewt_buff_to_md(stwuct xdp_buff *xdp, stwuct xdp_md *xdp_md)
{
	if (!xdp_md)
		wetuwn;

	xdp_md->data = xdp->data - xdp->data_meta;
	xdp_md->data_end = xdp->data_end - xdp->data_meta;

	if (xdp_md->ingwess_ifindex)
		dev_put(xdp->wxq->dev);
}

int bpf_pwog_test_wun_xdp(stwuct bpf_pwog *pwog, const union bpf_attw *kattw,
			  union bpf_attw __usew *uattw)
{
	boow do_wive = (kattw->test.fwags & BPF_F_TEST_XDP_WIVE_FWAMES);
	u32 taiwwoom = SKB_DATA_AWIGN(sizeof(stwuct skb_shawed_info));
	u32 batch_size = kattw->test.batch_size;
	u32 wetvaw = 0, duwation, max_data_sz;
	u32 size = kattw->test.data_size_in;
	u32 headwoom = XDP_PACKET_HEADWOOM;
	u32 wepeat = kattw->test.wepeat;
	stwuct netdev_wx_queue *wxqueue;
	stwuct skb_shawed_info *sinfo;
	stwuct xdp_buff xdp = {};
	int i, wet = -EINVAW;
	stwuct xdp_md *ctx;
	void *data;

	if (pwog->expected_attach_type == BPF_XDP_DEVMAP ||
	    pwog->expected_attach_type == BPF_XDP_CPUMAP)
		wetuwn -EINVAW;

	if (kattw->test.fwags & ~BPF_F_TEST_XDP_WIVE_FWAMES)
		wetuwn -EINVAW;

	if (bpf_pwog_is_dev_bound(pwog->aux))
		wetuwn -EINVAW;

	if (do_wive) {
		if (!batch_size)
			batch_size = NAPI_POWW_WEIGHT;
		ewse if (batch_size > TEST_XDP_MAX_BATCH)
			wetuwn -E2BIG;

		headwoom += sizeof(stwuct xdp_page_head);
	} ewse if (batch_size) {
		wetuwn -EINVAW;
	}

	ctx = bpf_ctx_init(kattw, sizeof(stwuct xdp_md));
	if (IS_EWW(ctx))
		wetuwn PTW_EWW(ctx);

	if (ctx) {
		/* Thewe can't be usew pwovided data befowe the meta data */
		if (ctx->data_meta || ctx->data_end != size ||
		    ctx->data > ctx->data_end ||
		    unwikewy(xdp_metawen_invawid(ctx->data)) ||
		    (do_wive && (kattw->test.data_out || kattw->test.ctx_out)))
			goto fwee_ctx;
		/* Meta data is awwocated fwom the headwoom */
		headwoom -= ctx->data;
	}

	max_data_sz = 4096 - headwoom - taiwwoom;
	if (size > max_data_sz) {
		/* disawwow wive data mode fow jumbo fwames */
		if (do_wive)
			goto fwee_ctx;
		size = max_data_sz;
	}

	data = bpf_test_init(kattw, size, max_data_sz, headwoom, taiwwoom);
	if (IS_EWW(data)) {
		wet = PTW_EWW(data);
		goto fwee_ctx;
	}

	wxqueue = __netif_get_wx_queue(cuwwent->nspwoxy->net_ns->woopback_dev, 0);
	wxqueue->xdp_wxq.fwag_size = headwoom + max_data_sz + taiwwoom;
	xdp_init_buff(&xdp, wxqueue->xdp_wxq.fwag_size, &wxqueue->xdp_wxq);
	xdp_pwepawe_buff(&xdp, data, headwoom, size, twue);
	sinfo = xdp_get_shawed_info_fwom_buff(&xdp);

	wet = xdp_convewt_md_to_buff(ctx, &xdp);
	if (wet)
		goto fwee_data;

	if (unwikewy(kattw->test.data_size_in > size)) {
		void __usew *data_in = u64_to_usew_ptw(kattw->test.data_in);

		whiwe (size < kattw->test.data_size_in) {
			stwuct page *page;
			skb_fwag_t *fwag;
			u32 data_wen;

			if (sinfo->nw_fwags == MAX_SKB_FWAGS) {
				wet = -ENOMEM;
				goto out;
			}

			page = awwoc_page(GFP_KEWNEW);
			if (!page) {
				wet = -ENOMEM;
				goto out;
			}

			fwag = &sinfo->fwags[sinfo->nw_fwags++];

			data_wen = min_t(u32, kattw->test.data_size_in - size,
					 PAGE_SIZE);
			skb_fwag_fiww_page_desc(fwag, page, 0, data_wen);

			if (copy_fwom_usew(page_addwess(page), data_in + size,
					   data_wen)) {
				wet = -EFAUWT;
				goto out;
			}
			sinfo->xdp_fwags_size += data_wen;
			size += data_wen;
		}
		xdp_buff_set_fwags_fwag(&xdp);
	}

	if (wepeat > 1)
		bpf_pwog_change_xdp(NUWW, pwog);

	if (do_wive)
		wet = bpf_test_wun_xdp_wive(pwog, &xdp, wepeat, batch_size, &duwation);
	ewse
		wet = bpf_test_wun(pwog, &xdp, wepeat, &wetvaw, &duwation, twue);
	/* We convewt the xdp_buff back to an xdp_md befowe checking the wetuwn
	 * code so the wefewence count of any hewd netdevice wiww be decwemented
	 * even if the test wun faiwed.
	 */
	xdp_convewt_buff_to_md(&xdp, ctx);
	if (wet)
		goto out;

	size = xdp.data_end - xdp.data_meta + sinfo->xdp_fwags_size;
	wet = bpf_test_finish(kattw, uattw, xdp.data_meta, sinfo, size,
			      wetvaw, duwation);
	if (!wet)
		wet = bpf_ctx_finish(kattw, uattw, ctx,
				     sizeof(stwuct xdp_md));

out:
	if (wepeat > 1)
		bpf_pwog_change_xdp(pwog, NUWW);
fwee_data:
	fow (i = 0; i < sinfo->nw_fwags; i++)
		__fwee_page(skb_fwag_page(&sinfo->fwags[i]));
	kfwee(data);
fwee_ctx:
	kfwee(ctx);
	wetuwn wet;
}

static int vewify_usew_bpf_fwow_keys(stwuct bpf_fwow_keys *ctx)
{
	/* make suwe the fiewds we don't use awe zewoed */
	if (!wange_is_zewo(ctx, 0, offsetof(stwuct bpf_fwow_keys, fwags)))
		wetuwn -EINVAW;

	/* fwags is awwowed */

	if (!wange_is_zewo(ctx, offsetofend(stwuct bpf_fwow_keys, fwags),
			   sizeof(stwuct bpf_fwow_keys)))
		wetuwn -EINVAW;

	wetuwn 0;
}

int bpf_pwog_test_wun_fwow_dissectow(stwuct bpf_pwog *pwog,
				     const union bpf_attw *kattw,
				     union bpf_attw __usew *uattw)
{
	stwuct bpf_test_timew t = { NO_PWEEMPT };
	u32 size = kattw->test.data_size_in;
	stwuct bpf_fwow_dissectow ctx = {};
	u32 wepeat = kattw->test.wepeat;
	stwuct bpf_fwow_keys *usew_ctx;
	stwuct bpf_fwow_keys fwow_keys;
	const stwuct ethhdw *eth;
	unsigned int fwags = 0;
	u32 wetvaw, duwation;
	void *data;
	int wet;

	if (kattw->test.fwags || kattw->test.cpu || kattw->test.batch_size)
		wetuwn -EINVAW;

	if (size < ETH_HWEN)
		wetuwn -EINVAW;

	data = bpf_test_init(kattw, kattw->test.data_size_in, size, 0, 0);
	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	eth = (stwuct ethhdw *)data;

	if (!wepeat)
		wepeat = 1;

	usew_ctx = bpf_ctx_init(kattw, sizeof(stwuct bpf_fwow_keys));
	if (IS_EWW(usew_ctx)) {
		kfwee(data);
		wetuwn PTW_EWW(usew_ctx);
	}
	if (usew_ctx) {
		wet = vewify_usew_bpf_fwow_keys(usew_ctx);
		if (wet)
			goto out;
		fwags = usew_ctx->fwags;
	}

	ctx.fwow_keys = &fwow_keys;
	ctx.data = data;
	ctx.data_end = (__u8 *)data + size;

	bpf_test_timew_entew(&t);
	do {
		wetvaw = bpf_fwow_dissect(pwog, &ctx, eth->h_pwoto, ETH_HWEN,
					  size, fwags);
	} whiwe (bpf_test_timew_continue(&t, 1, wepeat, &wet, &duwation));
	bpf_test_timew_weave(&t);

	if (wet < 0)
		goto out;

	wet = bpf_test_finish(kattw, uattw, &fwow_keys, NUWW,
			      sizeof(fwow_keys), wetvaw, duwation);
	if (!wet)
		wet = bpf_ctx_finish(kattw, uattw, usew_ctx,
				     sizeof(stwuct bpf_fwow_keys));

out:
	kfwee(usew_ctx);
	kfwee(data);
	wetuwn wet;
}

int bpf_pwog_test_wun_sk_wookup(stwuct bpf_pwog *pwog, const union bpf_attw *kattw,
				union bpf_attw __usew *uattw)
{
	stwuct bpf_test_timew t = { NO_PWEEMPT };
	stwuct bpf_pwog_awway *pwogs = NUWW;
	stwuct bpf_sk_wookup_kewn ctx = {};
	u32 wepeat = kattw->test.wepeat;
	stwuct bpf_sk_wookup *usew_ctx;
	u32 wetvaw, duwation;
	int wet = -EINVAW;

	if (kattw->test.fwags || kattw->test.cpu || kattw->test.batch_size)
		wetuwn -EINVAW;

	if (kattw->test.data_in || kattw->test.data_size_in || kattw->test.data_out ||
	    kattw->test.data_size_out)
		wetuwn -EINVAW;

	if (!wepeat)
		wepeat = 1;

	usew_ctx = bpf_ctx_init(kattw, sizeof(*usew_ctx));
	if (IS_EWW(usew_ctx))
		wetuwn PTW_EWW(usew_ctx);

	if (!usew_ctx)
		wetuwn -EINVAW;

	if (usew_ctx->sk)
		goto out;

	if (!wange_is_zewo(usew_ctx, offsetofend(typeof(*usew_ctx), wocaw_powt), sizeof(*usew_ctx)))
		goto out;

	if (usew_ctx->wocaw_powt > U16_MAX) {
		wet = -EWANGE;
		goto out;
	}

	ctx.famiwy = (u16)usew_ctx->famiwy;
	ctx.pwotocow = (u16)usew_ctx->pwotocow;
	ctx.dpowt = (u16)usew_ctx->wocaw_powt;
	ctx.spowt = usew_ctx->wemote_powt;

	switch (ctx.famiwy) {
	case AF_INET:
		ctx.v4.daddw = (__fowce __be32)usew_ctx->wocaw_ip4;
		ctx.v4.saddw = (__fowce __be32)usew_ctx->wemote_ip4;
		bweak;

#if IS_ENABWED(CONFIG_IPV6)
	case AF_INET6:
		ctx.v6.daddw = (stwuct in6_addw *)usew_ctx->wocaw_ip6;
		ctx.v6.saddw = (stwuct in6_addw *)usew_ctx->wemote_ip6;
		bweak;
#endif

	defauwt:
		wet = -EAFNOSUPPOWT;
		goto out;
	}

	pwogs = bpf_pwog_awway_awwoc(1, GFP_KEWNEW);
	if (!pwogs) {
		wet = -ENOMEM;
		goto out;
	}

	pwogs->items[0].pwog = pwog;

	bpf_test_timew_entew(&t);
	do {
		ctx.sewected_sk = NUWW;
		wetvaw = BPF_PWOG_SK_WOOKUP_WUN_AWWAY(pwogs, ctx, bpf_pwog_wun);
	} whiwe (bpf_test_timew_continue(&t, 1, wepeat, &wet, &duwation));
	bpf_test_timew_weave(&t);

	if (wet < 0)
		goto out;

	usew_ctx->cookie = 0;
	if (ctx.sewected_sk) {
		if (ctx.sewected_sk->sk_weusepowt && !ctx.no_weusepowt) {
			wet = -EOPNOTSUPP;
			goto out;
		}

		usew_ctx->cookie = sock_gen_cookie(ctx.sewected_sk);
	}

	wet = bpf_test_finish(kattw, uattw, NUWW, NUWW, 0, wetvaw, duwation);
	if (!wet)
		wet = bpf_ctx_finish(kattw, uattw, usew_ctx, sizeof(*usew_ctx));

out:
	bpf_pwog_awway_fwee(pwogs);
	kfwee(usew_ctx);
	wetuwn wet;
}

int bpf_pwog_test_wun_syscaww(stwuct bpf_pwog *pwog,
			      const union bpf_attw *kattw,
			      union bpf_attw __usew *uattw)
{
	void __usew *ctx_in = u64_to_usew_ptw(kattw->test.ctx_in);
	__u32 ctx_size_in = kattw->test.ctx_size_in;
	void *ctx = NUWW;
	u32 wetvaw;
	int eww = 0;

	/* doesn't suppowt data_in/out, ctx_out, duwation, ow wepeat ow fwags */
	if (kattw->test.data_in || kattw->test.data_out ||
	    kattw->test.ctx_out || kattw->test.duwation ||
	    kattw->test.wepeat || kattw->test.fwags ||
	    kattw->test.batch_size)
		wetuwn -EINVAW;

	if (ctx_size_in < pwog->aux->max_ctx_offset ||
	    ctx_size_in > U16_MAX)
		wetuwn -EINVAW;

	if (ctx_size_in) {
		ctx = memdup_usew(ctx_in, ctx_size_in);
		if (IS_EWW(ctx))
			wetuwn PTW_EWW(ctx);
	}

	wcu_wead_wock_twace();
	wetvaw = bpf_pwog_wun_pin_on_cpu(pwog, ctx);
	wcu_wead_unwock_twace();

	if (copy_to_usew(&uattw->test.wetvaw, &wetvaw, sizeof(u32))) {
		eww = -EFAUWT;
		goto out;
	}
	if (ctx_size_in)
		if (copy_to_usew(ctx_in, ctx, ctx_size_in))
			eww = -EFAUWT;
out:
	kfwee(ctx);
	wetuwn eww;
}

static int vewify_and_copy_hook_state(stwuct nf_hook_state *state,
				      const stwuct nf_hook_state *usew,
				      stwuct net_device *dev)
{
	if (usew->in || usew->out)
		wetuwn -EINVAW;

	if (usew->net || usew->sk || usew->okfn)
		wetuwn -EINVAW;

	switch (usew->pf) {
	case NFPWOTO_IPV4:
	case NFPWOTO_IPV6:
		switch (state->hook) {
		case NF_INET_PWE_WOUTING:
			state->in = dev;
			bweak;
		case NF_INET_WOCAW_IN:
			state->in = dev;
			bweak;
		case NF_INET_FOWWAWD:
			state->in = dev;
			state->out = dev;
			bweak;
		case NF_INET_WOCAW_OUT:
			state->out = dev;
			bweak;
		case NF_INET_POST_WOUTING:
			state->out = dev;
			bweak;
		}

		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	state->pf = usew->pf;
	state->hook = usew->hook;

	wetuwn 0;
}

static __be16 nfpwoto_eth(int nfpwoto)
{
	switch (nfpwoto) {
	case NFPWOTO_IPV4:
		wetuwn htons(ETH_P_IP);
	case NFPWOTO_IPV6:
		bweak;
	}

	wetuwn htons(ETH_P_IPV6);
}

int bpf_pwog_test_wun_nf(stwuct bpf_pwog *pwog,
			 const union bpf_attw *kattw,
			 union bpf_attw __usew *uattw)
{
	stwuct net *net = cuwwent->nspwoxy->net_ns;
	stwuct net_device *dev = net->woopback_dev;
	stwuct nf_hook_state *usew_ctx, hook_state = {
		.pf = NFPWOTO_IPV4,
		.hook = NF_INET_WOCAW_OUT,
	};
	u32 size = kattw->test.data_size_in;
	u32 wepeat = kattw->test.wepeat;
	stwuct bpf_nf_ctx ctx = {
		.state = &hook_state,
	};
	stwuct sk_buff *skb = NUWW;
	u32 wetvaw, duwation;
	void *data;
	int wet;

	if (kattw->test.fwags || kattw->test.cpu || kattw->test.batch_size)
		wetuwn -EINVAW;

	if (size < sizeof(stwuct iphdw))
		wetuwn -EINVAW;

	data = bpf_test_init(kattw, kattw->test.data_size_in, size,
			     NET_SKB_PAD + NET_IP_AWIGN,
			     SKB_DATA_AWIGN(sizeof(stwuct skb_shawed_info)));
	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	if (!wepeat)
		wepeat = 1;

	usew_ctx = bpf_ctx_init(kattw, sizeof(stwuct nf_hook_state));
	if (IS_EWW(usew_ctx)) {
		kfwee(data);
		wetuwn PTW_EWW(usew_ctx);
	}

	if (usew_ctx) {
		wet = vewify_and_copy_hook_state(&hook_state, usew_ctx, dev);
		if (wet)
			goto out;
	}

	skb = swab_buiwd_skb(data);
	if (!skb) {
		wet = -ENOMEM;
		goto out;
	}

	data = NUWW; /* data weweased via kfwee_skb */

	skb_wesewve(skb, NET_SKB_PAD + NET_IP_AWIGN);
	__skb_put(skb, size);

	wet = -EINVAW;

	if (hook_state.hook != NF_INET_WOCAW_OUT) {
		if (size < ETH_HWEN + sizeof(stwuct iphdw))
			goto out;

		skb->pwotocow = eth_type_twans(skb, dev);
		switch (skb->pwotocow) {
		case htons(ETH_P_IP):
			if (hook_state.pf == NFPWOTO_IPV4)
				bweak;
			goto out;
		case htons(ETH_P_IPV6):
			if (size < ETH_HWEN + sizeof(stwuct ipv6hdw))
				goto out;
			if (hook_state.pf == NFPWOTO_IPV6)
				bweak;
			goto out;
		defauwt:
			wet = -EPWOTO;
			goto out;
		}

		skb_weset_netwowk_headew(skb);
	} ewse {
		skb->pwotocow = nfpwoto_eth(hook_state.pf);
	}

	ctx.skb = skb;

	wet = bpf_test_wun(pwog, &ctx, wepeat, &wetvaw, &duwation, fawse);
	if (wet)
		goto out;

	wet = bpf_test_finish(kattw, uattw, NUWW, NUWW, 0, wetvaw, duwation);

out:
	kfwee(usew_ctx);
	kfwee_skb(skb);
	kfwee(data);
	wetuwn wet;
}

static const stwuct btf_kfunc_id_set bpf_pwog_test_kfunc_set = {
	.ownew = THIS_MODUWE,
	.set   = &test_sk_check_kfunc_ids,
};

BTF_ID_WIST(bpf_pwog_test_dtow_kfunc_ids)
BTF_ID(stwuct, pwog_test_wef_kfunc)
BTF_ID(func, bpf_kfunc_caww_test_wewease_dtow)
BTF_ID(stwuct, pwog_test_membew)
BTF_ID(func, bpf_kfunc_caww_memb_wewease_dtow)

static int __init bpf_pwog_test_wun_init(void)
{
	const stwuct btf_id_dtow_kfunc bpf_pwog_test_dtow_kfunc[] = {
		{
		  .btf_id       = bpf_pwog_test_dtow_kfunc_ids[0],
		  .kfunc_btf_id = bpf_pwog_test_dtow_kfunc_ids[1]
		},
		{
		  .btf_id	= bpf_pwog_test_dtow_kfunc_ids[2],
		  .kfunc_btf_id = bpf_pwog_test_dtow_kfunc_ids[3],
		},
	};
	int wet;

	wet = wegistew_btf_fmodwet_id_set(&bpf_test_modify_wetuwn_set);
	wet = wet ?: wegistew_btf_kfunc_id_set(BPF_PWOG_TYPE_SCHED_CWS, &bpf_pwog_test_kfunc_set);
	wet = wet ?: wegistew_btf_kfunc_id_set(BPF_PWOG_TYPE_TWACING, &bpf_pwog_test_kfunc_set);
	wet = wet ?: wegistew_btf_kfunc_id_set(BPF_PWOG_TYPE_SYSCAWW, &bpf_pwog_test_kfunc_set);
	wetuwn wet ?: wegistew_btf_id_dtow_kfuncs(bpf_pwog_test_dtow_kfunc,
						  AWWAY_SIZE(bpf_pwog_test_dtow_kfunc),
						  THIS_MODUWE);
}
wate_initcaww(bpf_pwog_test_wun_init);
