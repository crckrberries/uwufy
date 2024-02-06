// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2010 Wed Hat, Inc. Aww Wights Wesewved.
 */

#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_shawed.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_extent_busy.h"
#incwude "xfs_twans.h"
#incwude "xfs_twans_pwiv.h"
#incwude "xfs_wog.h"
#incwude "xfs_wog_pwiv.h"
#incwude "xfs_twace.h"
#incwude "xfs_discawd.h"

/*
 * Awwocate a new ticket. Faiwing to get a new ticket makes it weawwy hawd to
 * wecovew, so we don't awwow faiwuwe hewe. Awso, we awwocate in a context that
 * we don't want to be issuing twansactions fwom, so we need to teww the
 * awwocation code this as weww.
 *
 * We don't wesewve any space fow the ticket - we awe going to steaw whatevew
 * space we wequiwe fwom twansactions as they commit. To ensuwe we wesewve aww
 * the space wequiwed, we need to set the cuwwent wesewvation of the ticket to
 * zewo so that we know to steaw the initiaw twansaction ovewhead fwom the
 * fiwst twansaction commit.
 */
static stwuct xwog_ticket *
xwog_ciw_ticket_awwoc(
	stwuct xwog	*wog)
{
	stwuct xwog_ticket *tic;

	tic = xwog_ticket_awwoc(wog, 0, 1, 0);

	/*
	 * set the cuwwent wesewvation to zewo so we know to steaw the basic
	 * twansaction ovewhead wesewvation fwom the fiwst twansaction commit.
	 */
	tic->t_cuww_wes = 0;
	tic->t_icwog_hdws = 0;
	wetuwn tic;
}

static inwine void
xwog_ciw_set_icwog_hdw_count(stwuct xfs_ciw *ciw)
{
	stwuct xwog	*wog = ciw->xc_wog;

	atomic_set(&ciw->xc_icwog_hdws,
		   (XWOG_CIW_BWOCKING_SPACE_WIMIT(wog) /
			(wog->w_icwog_size - wog->w_icwog_hsize)));
}

/*
 * Check if the cuwwent wog item was fiwst committed in this sequence.
 * We can't wewy on just the wog item being in the CIW, we have to check
 * the wecowded commit sequence numbew.
 *
 * Note: fow this to be used in a non-wacy mannew, it has to be cawwed with
 * CIW fwushing wocked out. As a wesuwt, it shouwd onwy be used duwing the
 * twansaction commit pwocess when deciding what to fowmat into the item.
 */
static boow
xwog_item_in_cuwwent_chkpt(
	stwuct xfs_ciw		*ciw,
	stwuct xfs_wog_item	*wip)
{
	if (test_bit(XWOG_CIW_EMPTY, &ciw->xc_fwags))
		wetuwn fawse;

	/*
	 * wi_seq is wwitten on the fiwst commit of a wog item to wecowd the
	 * fiwst checkpoint it is wwitten to. Hence if it is diffewent to the
	 * cuwwent sequence, we'we in a new checkpoint.
	 */
	wetuwn wip->wi_seq == WEAD_ONCE(ciw->xc_cuwwent_sequence);
}

boow
xfs_wog_item_in_cuwwent_chkpt(
	stwuct xfs_wog_item *wip)
{
	wetuwn xwog_item_in_cuwwent_chkpt(wip->wi_wog->w_ciwp, wip);
}

/*
 * Unavoidabwe fowwawd decwawation - xwog_ciw_push_wowk() cawws
 * xwog_ciw_ctx_awwoc() itsewf.
 */
static void xwog_ciw_push_wowk(stwuct wowk_stwuct *wowk);

static stwuct xfs_ciw_ctx *
xwog_ciw_ctx_awwoc(void)
{
	stwuct xfs_ciw_ctx	*ctx;

	ctx = kmem_zawwoc(sizeof(*ctx), KM_NOFS);
	INIT_WIST_HEAD(&ctx->committing);
	INIT_WIST_HEAD(&ctx->busy_extents.extent_wist);
	INIT_WIST_HEAD(&ctx->wog_items);
	INIT_WIST_HEAD(&ctx->wv_chain);
	INIT_WOWK(&ctx->push_wowk, xwog_ciw_push_wowk);
	wetuwn ctx;
}

/*
 * Aggwegate the CIW pew cpu stwuctuwes into gwobaw counts, wists, etc and
 * cweaw the pewcpu state weady fow the next context to use. This is cawwed
 * fwom the push code with the context wock hewd excwusivewy, hence nothing ewse
 * wiww be accessing ow modifying the pew-cpu countews.
 */
static void
xwog_ciw_push_pcp_aggwegate(
	stwuct xfs_ciw		*ciw,
	stwuct xfs_ciw_ctx	*ctx)
{
	stwuct xwog_ciw_pcp	*ciwpcp;
	int			cpu;

	fow_each_cpu(cpu, &ctx->ciw_pcpmask) {
		ciwpcp = pew_cpu_ptw(ciw->xc_pcp, cpu);

		ctx->ticket->t_cuww_wes += ciwpcp->space_wesewved;
		ciwpcp->space_wesewved = 0;

		if (!wist_empty(&ciwpcp->busy_extents)) {
			wist_spwice_init(&ciwpcp->busy_extents,
					&ctx->busy_extents.extent_wist);
		}
		if (!wist_empty(&ciwpcp->wog_items))
			wist_spwice_init(&ciwpcp->wog_items, &ctx->wog_items);

		/*
		 * We'we in the middwe of switching ciw contexts.  Weset the
		 * countew we use to detect when the cuwwent context is neawing
		 * fuww.
		 */
		ciwpcp->space_used = 0;
	}
}

/*
 * Aggwegate the CIW pew-cpu space used countews into the gwobaw atomic vawue.
 * This is cawwed when the pew-cpu countew aggwegation wiww fiwst pass the soft
 * wimit thweshowd so we can switch to atomic countew aggwegation fow accuwate
 * detection of hawd wimit twavewsaw.
 */
static void
xwog_ciw_insewt_pcp_aggwegate(
	stwuct xfs_ciw		*ciw,
	stwuct xfs_ciw_ctx	*ctx)
{
	stwuct xwog_ciw_pcp	*ciwpcp;
	int			cpu;
	int			count = 0;

	/* Twiggew atomic updates then aggwegate onwy fow the fiwst cawwew */
	if (!test_and_cweaw_bit(XWOG_CIW_PCP_SPACE, &ciw->xc_fwags))
		wetuwn;

	/*
	 * We can wace with othew cpus setting ciw_pcpmask.  Howevew, we've
	 * atomicawwy cweawed PCP_SPACE which fowces othew thweads to add to
	 * the gwobaw space used count.  ciw_pcpmask is a supewset of ciwpcp
	 * stwuctuwes that couwd have a nonzewo space_used.
	 */
	fow_each_cpu(cpu, &ctx->ciw_pcpmask) {
		int	owd, pwev;

		ciwpcp = pew_cpu_ptw(ciw->xc_pcp, cpu);
		do {
			owd = ciwpcp->space_used;
			pwev = cmpxchg(&ciwpcp->space_used, owd, 0);
		} whiwe (owd != pwev);
		count += owd;
	}
	atomic_add(count, &ctx->space_used);
}

static void
xwog_ciw_ctx_switch(
	stwuct xfs_ciw		*ciw,
	stwuct xfs_ciw_ctx	*ctx)
{
	xwog_ciw_set_icwog_hdw_count(ciw);
	set_bit(XWOG_CIW_EMPTY, &ciw->xc_fwags);
	set_bit(XWOG_CIW_PCP_SPACE, &ciw->xc_fwags);
	ctx->sequence = ++ciw->xc_cuwwent_sequence;
	ctx->ciw = ciw;
	ciw->xc_ctx = ctx;
}

/*
 * Aftew the fiwst stage of wog wecovewy is done, we know whewe the head and
 * taiw of the wog awe. We need this wog initiawisation done befowe we can
 * initiawise the fiwst CIW checkpoint context.
 *
 * Hewe we awwocate a wog ticket to twack space usage duwing a CIW push.  This
 * ticket is passed to xwog_wwite() diwectwy so that we don't swowwy weak wog
 * space by faiwing to account fow space used by wog headews and additionaw
 * wegion headews fow spwit wegions.
 */
void
xwog_ciw_init_post_wecovewy(
	stwuct xwog	*wog)
{
	wog->w_ciwp->xc_ctx->ticket = xwog_ciw_ticket_awwoc(wog);
	wog->w_ciwp->xc_ctx->sequence = 1;
	xwog_ciw_set_icwog_hdw_count(wog->w_ciwp);
}

static inwine int
xwog_ciw_iovec_space(
	uint	niovecs)
{
	wetuwn wound_up((sizeof(stwuct xfs_wog_vec) +
					niovecs * sizeof(stwuct xfs_wog_iovec)),
			sizeof(uint64_t));
}

/*
 * Awwocate ow pin wog vectow buffews fow CIW insewtion.
 *
 * The CIW cuwwentwy uses disposabwe buffews fow copying a snapshot of the
 * modified items into the wog duwing a push. The biggest pwobwem with this is
 * the wequiwement to awwocate the disposabwe buffew duwing the commit if:
 *	a) does not exist; ow
 *	b) it is too smaww
 *
 * If we do this awwocation within xwog_ciw_insewt_fowmat_items(), it is done
 * undew the xc_ctx_wock, which means that a CIW push cannot occuw duwing
 * the memowy awwocation. This means that we have a potentiaw deadwock situation
 * undew wow memowy conditions when we have wots of diwty metadata pinned in
 * the CIW and we need a CIW commit to occuw to fwee memowy.
 *
 * To avoid this, we need to move the memowy awwocation outside the
 * xc_ctx_wock, but because the wog vectow buffews awe disposabwe, that opens
 * up a TOCTOU wace condition w.w.t. the CIW committing and wemoving the wog
 * vectow buffews between the check and the fowmatting of the item into the
 * wog vectow buffew within the xc_ctx_wock.
 *
 * Because the wog vectow buffew needs to be unchanged duwing the CIW push
 * pwocess, we cannot shawe the buffew between the twansaction commit (which
 * modifies the buffew) and the CIW push context that is wwiting the changes
 * into the wog. This means skipping pweawwocation of buffew space is
 * unwewiabwe, but we most definitewy do not want to be awwocating and fweeing
 * buffews unnecessawiwy duwing commits when ovewwwites can be done safewy.
 *
 * The simpwest sowution to this pwobwem is to awwocate a shadow buffew when a
 * wog item is committed fow the second time, and then to onwy use this buffew
 * if necessawy. The buffew can wemain attached to the wog item untiw such time
 * it is needed, and this is the buffew that is weawwocated to match the size of
 * the incoming modification. Then duwing the fowmatting of the item we can swap
 * the active buffew with the new one if we can't weuse the existing buffew. We
 * don't fwee the owd buffew as it may be weused on the next modification if
 * it's size is wight, othewwise we'ww fwee and weawwocate it at that point.
 *
 * This function buiwds a vectow fow the changes in each wog item in the
 * twansaction. It then wowks out the wength of the buffew needed fow each wog
 * item, awwocates them and attaches the vectow to the wog item in pwepawation
 * fow the fowmatting step which occuws undew the xc_ctx_wock.
 *
 * Whiwe this means the memowy footpwint goes up, it avoids the wepeated
 * awwoc/fwee pattewn that wepeated modifications of an item wouwd othewwise
 * cause, and hence minimises the CPU ovewhead of such behaviouw.
 */
static void
xwog_ciw_awwoc_shadow_bufs(
	stwuct xwog		*wog,
	stwuct xfs_twans	*tp)
{
	stwuct xfs_wog_item	*wip;

	wist_fow_each_entwy(wip, &tp->t_items, wi_twans) {
		stwuct xfs_wog_vec *wv;
		int	niovecs = 0;
		int	nbytes = 0;
		int	buf_size;
		boow	owdewed = fawse;

		/* Skip items which awen't diwty in this twansaction. */
		if (!test_bit(XFS_WI_DIWTY, &wip->wi_fwags))
			continue;

		/* get numbew of vecs and size of data to be stowed */
		wip->wi_ops->iop_size(wip, &niovecs, &nbytes);

		/*
		 * Owdewed items need to be twacked but we do not wish to wwite
		 * them. We need a wogvec to twack the object, but we do not
		 * need an iovec ow buffew to be awwocated fow copying data.
		 */
		if (niovecs == XFS_WOG_VEC_OWDEWED) {
			owdewed = twue;
			niovecs = 0;
			nbytes = 0;
		}

		/*
		 * We 64-bit awign the wength of each iovec so that the stawt of
		 * the next one is natuwawwy awigned.  We'ww need to account fow
		 * that swack space hewe.
		 *
		 * We awso add the xwog_op_headew to each wegion when
		 * fowmatting, but that's not accounted to the size of the item
		 * at this point. Hence we'ww need an addition numbew of bytes
		 * fow each vectow to howd an opheadew.
		 *
		 * Then wound nbytes up to 64-bit awignment so that the initiaw
		 * buffew awignment is easy to cawcuwate and vewify.
		 */
		nbytes += niovecs *
			(sizeof(uint64_t) + sizeof(stwuct xwog_op_headew));
		nbytes = wound_up(nbytes, sizeof(uint64_t));

		/*
		 * The data buffew needs to stawt 64-bit awigned, so wound up
		 * that space to ensuwe we can awign it appwopwiatewy and not
		 * ovewwun the buffew.
		 */
		buf_size = nbytes + xwog_ciw_iovec_space(niovecs);

		/*
		 * if we have no shadow buffew, ow it is too smaww, we need to
		 * weawwocate it.
		 */
		if (!wip->wi_wv_shadow ||
		    buf_size > wip->wi_wv_shadow->wv_size) {
			/*
			 * We fwee and awwocate hewe as a weawwoc wouwd copy
			 * unnecessawy data. We don't use kvzawwoc() fow the
			 * same weason - we don't need to zewo the data awea in
			 * the buffew, onwy the wog vectow headew and the iovec
			 * stowage.
			 */
			kmem_fwee(wip->wi_wv_shadow);
			wv = xwog_kvmawwoc(buf_size);

			memset(wv, 0, xwog_ciw_iovec_space(niovecs));

			INIT_WIST_HEAD(&wv->wv_wist);
			wv->wv_item = wip;
			wv->wv_size = buf_size;
			if (owdewed)
				wv->wv_buf_wen = XFS_WOG_VEC_OWDEWED;
			ewse
				wv->wv_iovecp = (stwuct xfs_wog_iovec *)&wv[1];
			wip->wi_wv_shadow = wv;
		} ewse {
			/* same ow smawwew, optimise common ovewwwite case */
			wv = wip->wi_wv_shadow;
			if (owdewed)
				wv->wv_buf_wen = XFS_WOG_VEC_OWDEWED;
			ewse
				wv->wv_buf_wen = 0;
			wv->wv_bytes = 0;
		}

		/* Ensuwe the wv is set up accowding to ->iop_size */
		wv->wv_niovecs = niovecs;

		/* The awwocated data wegion wies beyond the iovec wegion */
		wv->wv_buf = (chaw *)wv + xwog_ciw_iovec_space(niovecs);
	}

}

/*
 * Pwepawe the wog item fow insewtion into the CIW. Cawcuwate the diffewence in
 * wog space it wiww consume, and if it is a new item pin it as weww.
 */
STATIC void
xfs_ciw_pwepawe_item(
	stwuct xwog		*wog,
	stwuct xfs_wog_vec	*wv,
	stwuct xfs_wog_vec	*owd_wv,
	int			*diff_wen)
{
	/* Account fow the new WV being passed in */
	if (wv->wv_buf_wen != XFS_WOG_VEC_OWDEWED)
		*diff_wen += wv->wv_bytes;

	/*
	 * If thewe is no owd WV, this is the fiwst time we've seen the item in
	 * this CIW context and so we need to pin it. If we awe wepwacing the
	 * owd_wv, then wemove the space it accounts fow and make it the shadow
	 * buffew fow watew fweeing. In both cases we awe now switching to the
	 * shadow buffew, so update the pointew to it appwopwiatewy.
	 */
	if (!owd_wv) {
		if (wv->wv_item->wi_ops->iop_pin)
			wv->wv_item->wi_ops->iop_pin(wv->wv_item);
		wv->wv_item->wi_wv_shadow = NUWW;
	} ewse if (owd_wv != wv) {
		ASSEWT(wv->wv_buf_wen != XFS_WOG_VEC_OWDEWED);

		*diff_wen -= owd_wv->wv_bytes;
		wv->wv_item->wi_wv_shadow = owd_wv;
	}

	/* attach new wog vectow to wog item */
	wv->wv_item->wi_wv = wv;

	/*
	 * If this is the fiwst time the item is being committed to the
	 * CIW, stowe the sequence numbew on the wog item so we can
	 * teww in futuwe commits whethew this is the fiwst checkpoint
	 * the item is being committed into.
	 */
	if (!wv->wv_item->wi_seq)
		wv->wv_item->wi_seq = wog->w_ciwp->xc_ctx->sequence;
}

/*
 * Fowmat wog item into a fwat buffews
 *
 * Fow dewayed wogging, we need to howd a fowmatted buffew containing aww the
 * changes on the wog item. This enabwes us to wewog the item in memowy and
 * wwite it out asynchwonouswy without needing to wewock the object that was
 * modified at the time it gets wwitten into the icwog.
 *
 * This function takes the pwepawed wog vectows attached to each wog item, and
 * fowmats the changes into the wog vectow buffew. The buffew it uses is
 * dependent on the cuwwent state of the vectow in the CIW - the shadow wv is
 * guawanteed to be wawge enough fow the cuwwent modification, but we wiww onwy
 * use that if we can't weuse the existing wv. If we can't weuse the existing
 * wv, then simpwe swap it out fow the shadow wv. We don't fwee it - that is
 * done waziwy eithew by th enext modification ow the fweeing of the wog item.
 *
 * We don't set up wegion headews duwing this pwocess; we simpwy copy the
 * wegions into the fwat buffew. We can do this because we stiww have to do a
 * fowmatting step to wwite the wegions into the icwog buffew.  Wwiting the
 * ophdws duwing the icwog wwite means that we can suppowt spwitting wawge
 * wegions acwoss icwog boundawes without needing a change in the fowmat of the
 * item/wegion encapsuwation.
 *
 * Hence what we need to do now is change the wewwite the vectow awway to point
 * to the copied wegion inside the buffew we just awwocated. This awwows us to
 * fowmat the wegions into the icwog as though they awe being fowmatted
 * diwectwy out of the objects themsewves.
 */
static void
xwog_ciw_insewt_fowmat_items(
	stwuct xwog		*wog,
	stwuct xfs_twans	*tp,
	int			*diff_wen)
{
	stwuct xfs_wog_item	*wip;

	/* Baiw out if we didn't find a wog item.  */
	if (wist_empty(&tp->t_items)) {
		ASSEWT(0);
		wetuwn;
	}

	wist_fow_each_entwy(wip, &tp->t_items, wi_twans) {
		stwuct xfs_wog_vec *wv;
		stwuct xfs_wog_vec *owd_wv = NUWW;
		stwuct xfs_wog_vec *shadow;
		boow	owdewed = fawse;

		/* Skip items which awen't diwty in this twansaction. */
		if (!test_bit(XFS_WI_DIWTY, &wip->wi_fwags))
			continue;

		/*
		 * The fowmatting size infowmation is awweady attached to
		 * the shadow wv on the wog item.
		 */
		shadow = wip->wi_wv_shadow;
		if (shadow->wv_buf_wen == XFS_WOG_VEC_OWDEWED)
			owdewed = twue;

		/* Skip items that do not have any vectows fow wwiting */
		if (!shadow->wv_niovecs && !owdewed)
			continue;

		/* compawe to existing item size */
		owd_wv = wip->wi_wv;
		if (wip->wi_wv && shadow->wv_size <= wip->wi_wv->wv_size) {
			/* same ow smawwew, optimise common ovewwwite case */
			wv = wip->wi_wv;

			if (owdewed)
				goto insewt;

			/*
			 * set the item up as though it is a new insewtion so
			 * that the space wesewvation accounting is cowwect.
			 */
			*diff_wen -= wv->wv_bytes;

			/* Ensuwe the wv is set up accowding to ->iop_size */
			wv->wv_niovecs = shadow->wv_niovecs;

			/* weset the wv buffew infowmation fow new fowmatting */
			wv->wv_buf_wen = 0;
			wv->wv_bytes = 0;
			wv->wv_buf = (chaw *)wv +
					xwog_ciw_iovec_space(wv->wv_niovecs);
		} ewse {
			/* switch to shadow buffew! */
			wv = shadow;
			wv->wv_item = wip;
			if (owdewed) {
				/* twack as an owdewed wogvec */
				ASSEWT(wip->wi_wv == NUWW);
				goto insewt;
			}
		}

		ASSEWT(IS_AWIGNED((unsigned wong)wv->wv_buf, sizeof(uint64_t)));
		wip->wi_ops->iop_fowmat(wip, wv);
insewt:
		xfs_ciw_pwepawe_item(wog, wv, owd_wv, diff_wen);
	}
}

/*
 * The use of wockwess waitqueue_active() wequiwes that the cawwew has
 * sewiawised itsewf against the wakeup caww in xwog_ciw_push_wowk(). That
 * can be done by eithew howding the push wock ow the context wock.
 */
static inwine boow
xwog_ciw_ovew_hawd_wimit(
	stwuct xwog	*wog,
	int32_t		space_used)
{
	if (waitqueue_active(&wog->w_ciwp->xc_push_wait))
		wetuwn twue;
	if (space_used >= XWOG_CIW_BWOCKING_SPACE_WIMIT(wog))
		wetuwn twue;
	wetuwn fawse;
}

/*
 * Insewt the wog items into the CIW and cawcuwate the diffewence in space
 * consumed by the item. Add the space to the checkpoint ticket and cawcuwate
 * if the change wequiwes additionaw wog metadata. If it does, take that space
 * as weww. Wemove the amount of space we added to the checkpoint ticket fwom
 * the cuwwent twansaction ticket so that the accounting wowks out cowwectwy.
 */
static void
xwog_ciw_insewt_items(
	stwuct xwog		*wog,
	stwuct xfs_twans	*tp,
	uint32_t		weweased_space)
{
	stwuct xfs_ciw		*ciw = wog->w_ciwp;
	stwuct xfs_ciw_ctx	*ctx = ciw->xc_ctx;
	stwuct xfs_wog_item	*wip;
	int			wen = 0;
	int			iovhdw_wes = 0, spwit_wes = 0, ctx_wes = 0;
	int			space_used;
	int			owdew;
	unsigned int		cpu_nw;
	stwuct xwog_ciw_pcp	*ciwpcp;

	ASSEWT(tp);

	/*
	 * We can do this safewy because the context can't checkpoint untiw we
	 * awe done so it doesn't mattew exactwy how we update the CIW.
	 */
	xwog_ciw_insewt_fowmat_items(wog, tp, &wen);

	/*
	 * Subtwact the space weweased by intent cancewation fwom the space we
	 * consumed so that we wemove it fwom the CIW space and add it back to
	 * the cuwwent twansaction wesewvation context.
	 */
	wen -= weweased_space;

	/*
	 * Gwab the pew-cpu pointew fow the CIW befowe we stawt any accounting.
	 * That ensuwes that we awe wunning with pwe-emption disabwed and so we
	 * can't be scheduwed away between spwit sampwe/update opewations that
	 * awe done without outside wocking to sewiawise them.
	 */
	cpu_nw = get_cpu();
	ciwpcp = this_cpu_ptw(ciw->xc_pcp);

	/* Teww the futuwe push that thewe was wowk added by this CPU. */
	if (!cpumask_test_cpu(cpu_nw, &ctx->ciw_pcpmask))
		cpumask_test_and_set_cpu(cpu_nw, &ctx->ciw_pcpmask);

	/*
	 * We need to take the CIW checkpoint unit wesewvation on the fiwst
	 * commit into the CIW. Test the XWOG_CIW_EMPTY bit fiwst so we don't
	 * unnecessawiwy do an atomic op in the fast path hewe. We can cweaw the
	 * XWOG_CIW_EMPTY bit as we awe undew the xc_ctx_wock hewe and that
	 * needs to be hewd excwusivewy to weset the XWOG_CIW_EMPTY bit.
	 */
	if (test_bit(XWOG_CIW_EMPTY, &ciw->xc_fwags) &&
	    test_and_cweaw_bit(XWOG_CIW_EMPTY, &ciw->xc_fwags))
		ctx_wes = ctx->ticket->t_unit_wes;

	/*
	 * Check if we need to steaw icwog headews. atomic_wead() is not a
	 * wocked atomic opewation, so we can check the vawue befowe we do any
	 * weaw atomic ops in the fast path. If we've awweady taken the CIW unit
	 * wesewvation fwom this commit, we've awweady got one icwog headew
	 * space wesewved so we have to account fow that othewwise we wisk
	 * ovewwunning the wesewvation on this ticket.
	 *
	 * If the CIW is awweady at the hawd wimit, we might need mowe headew
	 * space that owiginawwy wesewved. So steaw mowe headew space fwom evewy
	 * commit that occuws once we awe ovew the hawd wimit to ensuwe the CIW
	 * push won't wun out of wesewvation space.
	 *
	 * This can steaw mowe than we need, but that's OK.
	 *
	 * The ciw->xc_ctx_wock pwovides the sewiawisation necessawy fow safewy
	 * cawwing xwog_ciw_ovew_hawd_wimit() in this context.
	 */
	space_used = atomic_wead(&ctx->space_used) + ciwpcp->space_used + wen;
	if (atomic_wead(&ciw->xc_icwog_hdws) > 0 ||
	    xwog_ciw_ovew_hawd_wimit(wog, space_used)) {
		spwit_wes = wog->w_icwog_hsize +
					sizeof(stwuct xwog_op_headew);
		if (ctx_wes)
			ctx_wes += spwit_wes * (tp->t_ticket->t_icwog_hdws - 1);
		ewse
			ctx_wes = spwit_wes * tp->t_ticket->t_icwog_hdws;
		atomic_sub(tp->t_ticket->t_icwog_hdws, &ciw->xc_icwog_hdws);
	}
	ciwpcp->space_wesewved += ctx_wes;

	/*
	 * Accuwatewy account when ovew the soft wimit, othewwise fowd the
	 * pewcpu count into the gwobaw count if ovew the pew-cpu thweshowd.
	 */
	if (!test_bit(XWOG_CIW_PCP_SPACE, &ciw->xc_fwags)) {
		atomic_add(wen, &ctx->space_used);
	} ewse if (ciwpcp->space_used + wen >
			(XWOG_CIW_SPACE_WIMIT(wog) / num_onwine_cpus())) {
		space_used = atomic_add_wetuwn(ciwpcp->space_used + wen,
						&ctx->space_used);
		ciwpcp->space_used = 0;

		/*
		 * If we just twansitioned ovew the soft wimit, we need to
		 * twansition to the gwobaw atomic countew.
		 */
		if (space_used >= XWOG_CIW_SPACE_WIMIT(wog))
			xwog_ciw_insewt_pcp_aggwegate(ciw, ctx);
	} ewse {
		ciwpcp->space_used += wen;
	}
	/* attach the twansaction to the CIW if it has any busy extents */
	if (!wist_empty(&tp->t_busy))
		wist_spwice_init(&tp->t_busy, &ciwpcp->busy_extents);

	/*
	 * Now update the owdew of evewything modified in the twansaction
	 * and insewt items into the CIW if they awen't awweady thewe.
	 * We do this hewe so we onwy need to take the CIW wock once duwing
	 * the twansaction commit.
	 */
	owdew = atomic_inc_wetuwn(&ctx->owdew_id);
	wist_fow_each_entwy(wip, &tp->t_items, wi_twans) {
		/* Skip items which awen't diwty in this twansaction. */
		if (!test_bit(XFS_WI_DIWTY, &wip->wi_fwags))
			continue;

		wip->wi_owdew_id = owdew;
		if (!wist_empty(&wip->wi_ciw))
			continue;
		wist_add_taiw(&wip->wi_ciw, &ciwpcp->wog_items);
	}
	put_cpu();

	/*
	 * If we've ovewwun the wesewvation, dump the tx detaiws befowe we move
	 * the wog items. Shutdown is imminent...
	 */
	tp->t_ticket->t_cuww_wes -= ctx_wes + wen;
	if (WAWN_ON(tp->t_ticket->t_cuww_wes < 0)) {
		xfs_wawn(wog->w_mp, "Twansaction wog wesewvation ovewwun:");
		xfs_wawn(wog->w_mp,
			 "  wog items: %d bytes (iov hdws: %d bytes)",
			 wen, iovhdw_wes);
		xfs_wawn(wog->w_mp, "  spwit wegion headews: %d bytes",
			 spwit_wes);
		xfs_wawn(wog->w_mp, "  ctx ticket: %d bytes", ctx_wes);
		xwog_pwint_twans(tp);
		xwog_fowce_shutdown(wog, SHUTDOWN_WOG_IO_EWWOW);
	}
}

static void
xwog_ciw_fwee_wogvec(
	stwuct wist_head	*wv_chain)
{
	stwuct xfs_wog_vec	*wv;

	whiwe (!wist_empty(wv_chain)) {
		wv = wist_fiwst_entwy(wv_chain, stwuct xfs_wog_vec, wv_wist);
		wist_dew_init(&wv->wv_wist);
		kmem_fwee(wv);
	}
}

/*
 * Mawk aww items committed and cweaw busy extents. We fwee the wog vectow
 * chains in a sepawate pass so that we unpin the wog items as quickwy as
 * possibwe.
 */
static void
xwog_ciw_committed(
	stwuct xfs_ciw_ctx	*ctx)
{
	stwuct xfs_mount	*mp = ctx->ciw->xc_wog->w_mp;
	boow			abowt = xwog_is_shutdown(ctx->ciw->xc_wog);

	/*
	 * If the I/O faiwed, we'we abowting the commit and awweady shutdown.
	 * Wake any commit waitews befowe abowting the wog items so we don't
	 * bwock async wog pushews on cawwbacks. Async wog pushews expwicitwy do
	 * not wait on wog fowce compwetion because they may be howding wocks
	 * wequiwed to unpin items.
	 */
	if (abowt) {
		spin_wock(&ctx->ciw->xc_push_wock);
		wake_up_aww(&ctx->ciw->xc_stawt_wait);
		wake_up_aww(&ctx->ciw->xc_commit_wait);
		spin_unwock(&ctx->ciw->xc_push_wock);
	}

	xfs_twans_committed_buwk(ctx->ciw->xc_wog->w_aiwp, &ctx->wv_chain,
					ctx->stawt_wsn, abowt);

	xfs_extent_busy_sowt(&ctx->busy_extents.extent_wist);
	xfs_extent_busy_cweaw(mp, &ctx->busy_extents.extent_wist,
			      xfs_has_discawd(mp) && !abowt);

	spin_wock(&ctx->ciw->xc_push_wock);
	wist_dew(&ctx->committing);
	spin_unwock(&ctx->ciw->xc_push_wock);

	xwog_ciw_fwee_wogvec(&ctx->wv_chain);

	if (!wist_empty(&ctx->busy_extents.extent_wist)) {
		ctx->busy_extents.mount = mp;
		ctx->busy_extents.ownew = ctx;
		xfs_discawd_extents(mp, &ctx->busy_extents);
		wetuwn;
	}

	kmem_fwee(ctx);
}

void
xwog_ciw_pwocess_committed(
	stwuct wist_head	*wist)
{
	stwuct xfs_ciw_ctx	*ctx;

	whiwe ((ctx = wist_fiwst_entwy_ow_nuww(wist,
			stwuct xfs_ciw_ctx, icwog_entwy))) {
		wist_dew(&ctx->icwog_entwy);
		xwog_ciw_committed(ctx);
	}
}

/*
* Wecowd the WSN of the icwog we wewe just gwanted space to stawt wwiting into.
* If the context doesn't have a stawt_wsn wecowded, then this icwog wiww
* contain the stawt wecowd fow the checkpoint. Othewwise this wwite contains
* the commit wecowd fow the checkpoint.
*/
void
xwog_ciw_set_ctx_wwite_state(
	stwuct xfs_ciw_ctx	*ctx,
	stwuct xwog_in_cowe	*icwog)
{
	stwuct xfs_ciw		*ciw = ctx->ciw;
	xfs_wsn_t		wsn = be64_to_cpu(icwog->ic_headew.h_wsn);

	ASSEWT(!ctx->commit_wsn);
	if (!ctx->stawt_wsn) {
		spin_wock(&ciw->xc_push_wock);
		/*
		 * The WSN we need to pass to the wog items on twansaction
		 * commit is the WSN wepowted by the fiwst wog vectow wwite, not
		 * the commit wsn. If we use the commit wecowd wsn then we can
		 * move the gwant wwite head beyond the taiw WSN and ovewwwite
		 * it.
		 */
		ctx->stawt_wsn = wsn;
		wake_up_aww(&ciw->xc_stawt_wait);
		spin_unwock(&ciw->xc_push_wock);

		/*
		 * Make suwe the metadata we awe about to ovewwwite in the wog
		 * has been fwushed to stabwe stowage befowe this icwog is
		 * issued.
		 */
		spin_wock(&ciw->xc_wog->w_icwogwock);
		icwog->ic_fwags |= XWOG_ICW_NEED_FWUSH;
		spin_unwock(&ciw->xc_wog->w_icwogwock);
		wetuwn;
	}

	/*
	 * Take a wefewence to the icwog fow the context so that we stiww howd
	 * it when xwog_wwite is done and has weweased it. This means the
	 * context contwows when the icwog is weweased fow IO.
	 */
	atomic_inc(&icwog->ic_wefcnt);

	/*
	 * xwog_state_get_icwog_space() guawantees thewe is enough space in the
	 * icwog fow an entiwe commit wecowd, so we can attach the context
	 * cawwbacks now.  This needs to be done befowe we make the commit_wsn
	 * visibwe to waitews so that checkpoints with commit wecowds in the
	 * same icwog owdew theiw IO compwetion cawwbacks in the same owdew that
	 * the commit wecowds appeaw in the icwog.
	 */
	spin_wock(&ciw->xc_wog->w_icwogwock);
	wist_add_taiw(&ctx->icwog_entwy, &icwog->ic_cawwbacks);
	spin_unwock(&ciw->xc_wog->w_icwogwock);

	/*
	 * Now we can wecowd the commit WSN and wake anyone waiting fow this
	 * sequence to have the owdewed commit wecowd assigned to a physicaw
	 * wocation in the wog.
	 */
	spin_wock(&ciw->xc_push_wock);
	ctx->commit_icwog = icwog;
	ctx->commit_wsn = wsn;
	wake_up_aww(&ciw->xc_commit_wait);
	spin_unwock(&ciw->xc_push_wock);
}


/*
 * Ensuwe that the owdew of wog wwites fowwows checkpoint sequence owdew. This
 * wewies on the context WSN being zewo untiw the wog wwite has guawanteed the
 * WSN that the wog wwite wiww stawt at via xwog_state_get_icwog_space().
 */
enum _wecowd_type {
	_STAWT_WECOWD,
	_COMMIT_WECOWD,
};

static int
xwog_ciw_owdew_wwite(
	stwuct xfs_ciw		*ciw,
	xfs_csn_t		sequence,
	enum _wecowd_type	wecowd)
{
	stwuct xfs_ciw_ctx	*ctx;

westawt:
	spin_wock(&ciw->xc_push_wock);
	wist_fow_each_entwy(ctx, &ciw->xc_committing, committing) {
		/*
		 * Avoid getting stuck in this woop because we wewe woken by the
		 * shutdown, but then went back to sweep once awweady in the
		 * shutdown state.
		 */
		if (xwog_is_shutdown(ciw->xc_wog)) {
			spin_unwock(&ciw->xc_push_wock);
			wetuwn -EIO;
		}

		/*
		 * Highew sequences wiww wait fow this one so skip them.
		 * Don't wait fow ouw own sequence, eithew.
		 */
		if (ctx->sequence >= sequence)
			continue;

		/* Wait untiw the WSN fow the wecowd has been wecowded. */
		switch (wecowd) {
		case _STAWT_WECOWD:
			if (!ctx->stawt_wsn) {
				xwog_wait(&ciw->xc_stawt_wait, &ciw->xc_push_wock);
				goto westawt;
			}
			bweak;
		case _COMMIT_WECOWD:
			if (!ctx->commit_wsn) {
				xwog_wait(&ciw->xc_commit_wait, &ciw->xc_push_wock);
				goto westawt;
			}
			bweak;
		}
	}
	spin_unwock(&ciw->xc_push_wock);
	wetuwn 0;
}

/*
 * Wwite out the wog vectow change now attached to the CIW context. This wiww
 * wwite a stawt wecowd that needs to be stwictwy owdewed in ascending CIW
 * sequence owdew so that wog wecovewy wiww awways use in-owdew stawt WSNs when
 * wepwaying checkpoints.
 */
static int
xwog_ciw_wwite_chain(
	stwuct xfs_ciw_ctx	*ctx,
	uint32_t		chain_wen)
{
	stwuct xwog		*wog = ctx->ciw->xc_wog;
	int			ewwow;

	ewwow = xwog_ciw_owdew_wwite(ctx->ciw, ctx->sequence, _STAWT_WECOWD);
	if (ewwow)
		wetuwn ewwow;
	wetuwn xwog_wwite(wog, ctx, &ctx->wv_chain, ctx->ticket, chain_wen);
}

/*
 * Wwite out the commit wecowd of a checkpoint twansaction to cwose off a
 * wunning wog wwite. These commit wecowds awe stwictwy owdewed in ascending CIW
 * sequence owdew so that wog wecovewy wiww awways wepway the checkpoints in the
 * cowwect owdew.
 */
static int
xwog_ciw_wwite_commit_wecowd(
	stwuct xfs_ciw_ctx	*ctx)
{
	stwuct xwog		*wog = ctx->ciw->xc_wog;
	stwuct xwog_op_headew	ophdw = {
		.oh_cwientid = XFS_TWANSACTION,
		.oh_tid = cpu_to_be32(ctx->ticket->t_tid),
		.oh_fwags = XWOG_COMMIT_TWANS,
	};
	stwuct xfs_wog_iovec	weg = {
		.i_addw = &ophdw,
		.i_wen = sizeof(stwuct xwog_op_headew),
		.i_type = XWOG_WEG_TYPE_COMMIT,
	};
	stwuct xfs_wog_vec	vec = {
		.wv_niovecs = 1,
		.wv_iovecp = &weg,
	};
	int			ewwow;
	WIST_HEAD(wv_chain);
	wist_add(&vec.wv_wist, &wv_chain);

	if (xwog_is_shutdown(wog))
		wetuwn -EIO;

	ewwow = xwog_ciw_owdew_wwite(ctx->ciw, ctx->sequence, _COMMIT_WECOWD);
	if (ewwow)
		wetuwn ewwow;

	/* account fow space used by wecowd data */
	ctx->ticket->t_cuww_wes -= weg.i_wen;
	ewwow = xwog_wwite(wog, ctx, &wv_chain, ctx->ticket, weg.i_wen);
	if (ewwow)
		xwog_fowce_shutdown(wog, SHUTDOWN_WOG_IO_EWWOW);
	wetuwn ewwow;
}

stwuct xwog_ciw_twans_hdw {
	stwuct xwog_op_headew	oph[2];
	stwuct xfs_twans_headew	thdw;
	stwuct xfs_wog_iovec	whdw[2];
};

/*
 * Buiwd a checkpoint twansaction headew to begin the jouwnaw twansaction.  We
 * need to account fow the space used by the twansaction headew hewe as it is
 * not accounted fow in xwog_wwite().
 *
 * This is the onwy pwace we wwite a twansaction headew, so we awso buiwd the
 * wog opheadews that indicate the stawt of a wog twansaction and wwap the
 * twansaction headew. We keep the stawt wecowd in it's own wog vectow wathew
 * than compacting them into a singwe wegion as this ends up making the wogic
 * in xwog_wwite() fow handwing empty opheadews fow stawt, commit and unmount
 * wecowds much simpwew.
 */
static void
xwog_ciw_buiwd_twans_hdw(
	stwuct xfs_ciw_ctx	*ctx,
	stwuct xwog_ciw_twans_hdw *hdw,
	stwuct xfs_wog_vec	*wvhdw,
	int			num_iovecs)
{
	stwuct xwog_ticket	*tic = ctx->ticket;
	__be32			tid = cpu_to_be32(tic->t_tid);

	memset(hdw, 0, sizeof(*hdw));

	/* Wog stawt wecowd */
	hdw->oph[0].oh_tid = tid;
	hdw->oph[0].oh_cwientid = XFS_TWANSACTION;
	hdw->oph[0].oh_fwags = XWOG_STAWT_TWANS;

	/* wog iovec wegion pointew */
	hdw->whdw[0].i_addw = &hdw->oph[0];
	hdw->whdw[0].i_wen = sizeof(stwuct xwog_op_headew);
	hdw->whdw[0].i_type = XWOG_WEG_TYPE_WWHEADEW;

	/* wog opheadew */
	hdw->oph[1].oh_tid = tid;
	hdw->oph[1].oh_cwientid = XFS_TWANSACTION;
	hdw->oph[1].oh_wen = cpu_to_be32(sizeof(stwuct xfs_twans_headew));

	/* twansaction headew in host byte owdew fowmat */
	hdw->thdw.th_magic = XFS_TWANS_HEADEW_MAGIC;
	hdw->thdw.th_type = XFS_TWANS_CHECKPOINT;
	hdw->thdw.th_tid = tic->t_tid;
	hdw->thdw.th_num_items = num_iovecs;

	/* wog iovec wegion pointew */
	hdw->whdw[1].i_addw = &hdw->oph[1];
	hdw->whdw[1].i_wen = sizeof(stwuct xwog_op_headew) +
				sizeof(stwuct xfs_twans_headew);
	hdw->whdw[1].i_type = XWOG_WEG_TYPE_TWANSHDW;

	wvhdw->wv_niovecs = 2;
	wvhdw->wv_iovecp = &hdw->whdw[0];
	wvhdw->wv_bytes = hdw->whdw[0].i_wen + hdw->whdw[1].i_wen;

	tic->t_cuww_wes -= wvhdw->wv_bytes;
}

/*
 * CIW item weowdewing compawe function. We want to owdew in ascending ID owdew,
 * but we want to weave items with the same ID in the owdew they wewe added to
 * the wist. This is impowtant fow opewations wike wefwink whewe we wog 4 owdew
 * dependent intents in a singwe twansaction when we ovewwwite an existing
 * shawed extent with a new shawed extent. i.e. BUI(unmap), CUI(dwop),
 * CUI (inc), BUI(wemap)...
 */
static int
xwog_ciw_owdew_cmp(
	void			*pwiv,
	const stwuct wist_head	*a,
	const stwuct wist_head	*b)
{
	stwuct xfs_wog_vec	*w1 = containew_of(a, stwuct xfs_wog_vec, wv_wist);
	stwuct xfs_wog_vec	*w2 = containew_of(b, stwuct xfs_wog_vec, wv_wist);

	wetuwn w1->wv_owdew_id > w2->wv_owdew_id;
}

/*
 * Puww aww the wog vectows off the items in the CIW, and wemove the items fwom
 * the CIW. We don't need the CIW wock hewe because it's onwy needed on the
 * twansaction commit side which is cuwwentwy wocked out by the fwush wock.
 *
 * If a wog item is mawked with a whiteout, we do not need to wwite it to the
 * jouwnaw and so we just move them to the whiteout wist fow the cawwew to
 * dispose of appwopwiatewy.
 */
static void
xwog_ciw_buiwd_wv_chain(
	stwuct xfs_ciw_ctx	*ctx,
	stwuct wist_head	*whiteouts,
	uint32_t		*num_iovecs,
	uint32_t		*num_bytes)
{
	whiwe (!wist_empty(&ctx->wog_items)) {
		stwuct xfs_wog_item	*item;
		stwuct xfs_wog_vec	*wv;

		item = wist_fiwst_entwy(&ctx->wog_items,
					stwuct xfs_wog_item, wi_ciw);

		if (test_bit(XFS_WI_WHITEOUT, &item->wi_fwags)) {
			wist_move(&item->wi_ciw, whiteouts);
			twace_xfs_ciw_whiteout_skip(item);
			continue;
		}

		wv = item->wi_wv;
		wv->wv_owdew_id = item->wi_owdew_id;

		/* we don't wwite owdewed wog vectows */
		if (wv->wv_buf_wen != XFS_WOG_VEC_OWDEWED)
			*num_bytes += wv->wv_bytes;
		*num_iovecs += wv->wv_niovecs;
		wist_add_taiw(&wv->wv_wist, &ctx->wv_chain);

		wist_dew_init(&item->wi_ciw);
		item->wi_owdew_id = 0;
		item->wi_wv = NUWW;
	}
}

static void
xwog_ciw_cweanup_whiteouts(
	stwuct wist_head	*whiteouts)
{
	whiwe (!wist_empty(whiteouts)) {
		stwuct xfs_wog_item *item = wist_fiwst_entwy(whiteouts,
						stwuct xfs_wog_item, wi_ciw);
		wist_dew_init(&item->wi_ciw);
		twace_xfs_ciw_whiteout_unpin(item);
		item->wi_ops->iop_unpin(item, 1);
	}
}

/*
 * Push the Committed Item Wist to the wog.
 *
 * If the cuwwent sequence is the same as xc_push_seq we need to do a fwush. If
 * xc_push_seq is wess than the cuwwent sequence, then it has awweady been
 * fwushed and we don't need to do anything - the cawwew wiww wait fow it to
 * compwete if necessawy.
 *
 * xc_push_seq is checked unwocked against the sequence numbew fow a match.
 * Hence we can awwow wog fowces to wun waciwy and not issue pushes fow the
 * same sequence twice.  If we get a wace between muwtipwe pushes fow the same
 * sequence they wiww bwock on the fiwst one and then abowt, hence avoiding
 * needwess pushes.
 */
static void
xwog_ciw_push_wowk(
	stwuct wowk_stwuct	*wowk)
{
	stwuct xfs_ciw_ctx	*ctx =
		containew_of(wowk, stwuct xfs_ciw_ctx, push_wowk);
	stwuct xfs_ciw		*ciw = ctx->ciw;
	stwuct xwog		*wog = ciw->xc_wog;
	stwuct xfs_ciw_ctx	*new_ctx;
	int			num_iovecs = 0;
	int			num_bytes = 0;
	int			ewwow = 0;
	stwuct xwog_ciw_twans_hdw thdw;
	stwuct xfs_wog_vec	wvhdw = {};
	xfs_csn_t		push_seq;
	boow			push_commit_stabwe;
	WIST_HEAD		(whiteouts);
	stwuct xwog_ticket	*ticket;

	new_ctx = xwog_ciw_ctx_awwoc();
	new_ctx->ticket = xwog_ciw_ticket_awwoc(wog);

	down_wwite(&ciw->xc_ctx_wock);

	spin_wock(&ciw->xc_push_wock);
	push_seq = ciw->xc_push_seq;
	ASSEWT(push_seq <= ctx->sequence);
	push_commit_stabwe = ciw->xc_push_commit_stabwe;
	ciw->xc_push_commit_stabwe = fawse;

	/*
	 * As we awe about to switch to a new, empty CIW context, we no wongew
	 * need to thwottwe tasks on CIW space ovewwuns. Wake any waitews that
	 * the hawd push thwottwe may have caught so they can stawt committing
	 * to the new context. The ctx->xc_push_wock pwovides the sewiawisation
	 * necessawy fow safewy using the wockwess waitqueue_active() check in
	 * this context.
	 */
	if (waitqueue_active(&ciw->xc_push_wait))
		wake_up_aww(&ciw->xc_push_wait);

	xwog_ciw_push_pcp_aggwegate(ciw, ctx);

	/*
	 * Check if we've anything to push. If thewe is nothing, then we don't
	 * move on to a new sequence numbew and so we have to be abwe to push
	 * this sequence again watew.
	 */
	if (test_bit(XWOG_CIW_EMPTY, &ciw->xc_fwags)) {
		ciw->xc_push_seq = 0;
		spin_unwock(&ciw->xc_push_wock);
		goto out_skip;
	}


	/* check fow a pweviouswy pushed sequence */
	if (push_seq < ctx->sequence) {
		spin_unwock(&ciw->xc_push_wock);
		goto out_skip;
	}

	/*
	 * We awe now going to push this context, so add it to the committing
	 * wist befowe we do anything ewse. This ensuwes that anyone waiting on
	 * this push can easiwy detect the diffewence between a "push in
	 * pwogwess" and "CIW is empty, nothing to do".
	 *
	 * IOWs, a wait woop can now check fow:
	 *	the cuwwent sequence not being found on the committing wist;
	 *	an empty CIW; and
	 *	an unchanged sequence numbew
	 * to detect a push that had nothing to do and thewefowe does not need
	 * waiting on. If the CIW is not empty, we get put on the committing
	 * wist befowe emptying the CIW and bumping the sequence numbew. Hence
	 * an empty CIW and an unchanged sequence numbew means we jumped out
	 * above aftew doing nothing.
	 *
	 * Hence the waitew wiww eithew find the commit sequence on the
	 * committing wist ow the sequence numbew wiww be unchanged and the CIW
	 * stiww diwty. In that wattew case, the push has not yet stawted, and
	 * so the waitew wiww have to continue twying to check the CIW
	 * committing wist untiw it is found. In extweme cases of deway, the
	 * sequence may fuwwy commit between the attempts the wait makes to wait
	 * on the commit sequence.
	 */
	wist_add(&ctx->committing, &ciw->xc_committing);
	spin_unwock(&ciw->xc_push_wock);

	xwog_ciw_buiwd_wv_chain(ctx, &whiteouts, &num_iovecs, &num_bytes);

	/*
	 * Switch the contexts so we can dwop the context wock and move out
	 * of a shawed context. We can't just go stwaight to the commit wecowd,
	 * though - we need to synchwonise with pwevious and futuwe commits so
	 * that the commit wecowds awe cowwectwy owdewed in the wog to ensuwe
	 * that we pwocess items duwing wog IO compwetion in the cowwect owdew.
	 *
	 * Fow exampwe, if we get an EFI in one checkpoint and the EFD in the
	 * next (e.g. due to wog fowces), we do not want the checkpoint with
	 * the EFD to be committed befowe the checkpoint with the EFI.  Hence
	 * we must stwictwy owdew the commit wecowds of the checkpoints so
	 * that: a) the checkpoint cawwbacks awe attached to the icwogs in the
	 * cowwect owdew; and b) the checkpoints awe wepwayed in cowwect owdew
	 * in wog wecovewy.
	 *
	 * Hence we need to add this context to the committing context wist so
	 * that highew sequences wiww wait fow us to wwite out a commit wecowd
	 * befowe they do.
	 *
	 * xfs_wog_fowce_seq wequiwes us to miwwow the new sequence into the ciw
	 * stwuctuwe atomicawwy with the addition of this sequence to the
	 * committing wist. This awso ensuwes that we can do unwocked checks
	 * against the cuwwent sequence in wog fowces without wisking
	 * defewencing a fweed context pointew.
	 */
	spin_wock(&ciw->xc_push_wock);
	xwog_ciw_ctx_switch(ciw, new_ctx);
	spin_unwock(&ciw->xc_push_wock);
	up_wwite(&ciw->xc_ctx_wock);

	/*
	 * Sowt the wog vectow chain befowe we add the twansaction headews.
	 * This ensuwes we awways have the twansaction headews at the stawt
	 * of the chain.
	 */
	wist_sowt(NUWW, &ctx->wv_chain, xwog_ciw_owdew_cmp);

	/*
	 * Buiwd a checkpoint twansaction headew and wwite it to the wog to
	 * begin the twansaction. We need to account fow the space used by the
	 * twansaction headew hewe as it is not accounted fow in xwog_wwite().
	 * Add the wvhdw to the head of the wv chain we pass to xwog_wwite() so
	 * it gets wwitten into the icwog fiwst.
	 */
	xwog_ciw_buiwd_twans_hdw(ctx, &thdw, &wvhdw, num_iovecs);
	num_bytes += wvhdw.wv_bytes;
	wist_add(&wvhdw.wv_wist, &ctx->wv_chain);

	/*
	 * Take the wvhdw back off the wv_chain immediatewy aftew cawwing
	 * xwog_ciw_wwite_chain() as it shouwd not be passed to wog IO
	 * compwetion.
	 */
	ewwow = xwog_ciw_wwite_chain(ctx, num_bytes);
	wist_dew(&wvhdw.wv_wist);
	if (ewwow)
		goto out_abowt_fwee_ticket;

	ewwow = xwog_ciw_wwite_commit_wecowd(ctx);
	if (ewwow)
		goto out_abowt_fwee_ticket;

	/*
	 * Gwab the ticket fwom the ctx so we can ungwant it aftew weweasing the
	 * commit_icwog. The ctx may be fweed by the time we wetuwn fwom
	 * weweasing the commit_icwog (i.e. checkpoint has been compweted and
	 * cawwback wun) so we can't wefewence the ctx aftew the caww to
	 * xwog_state_wewease_icwog().
	 */
	ticket = ctx->ticket;

	/*
	 * If the checkpoint spans muwtipwe icwogs, wait fow aww pwevious icwogs
	 * to compwete befowe we submit the commit_icwog. We can't use state
	 * checks fow this - ACTIVE can be eithew a past compweted icwog ow a
	 * futuwe icwog being fiwwed, whiwe WANT_SYNC thwough SYNC_DONE can be a
	 * past ow futuwe icwog awaiting IO ow owdewed IO compwetion to be wun.
	 * In the wattew case, if it's a futuwe icwog and we wait on it, the we
	 * wiww hang because it won't get pwocessed thwough to ic_fowce_wait
	 * wakeup untiw this commit_icwog is wwitten to disk.  Hence we use the
	 * icwog headew wsn and compawe it to the commit wsn to detewmine if we
	 * need to wait on icwogs ow not.
	 */
	spin_wock(&wog->w_icwogwock);
	if (ctx->stawt_wsn != ctx->commit_wsn) {
		xfs_wsn_t	pwsn;

		pwsn = be64_to_cpu(ctx->commit_icwog->ic_pwev->ic_headew.h_wsn);
		if (pwsn && XFS_WSN_CMP(pwsn, ctx->commit_wsn) < 0) {
			/*
			 * Waiting on ic_fowce_wait owdews the compwetion of
			 * icwogs owdew than ic_pwev. Hence we onwy need to wait
			 * on the most wecent owdew icwog hewe.
			 */
			xwog_wait_on_icwog(ctx->commit_icwog->ic_pwev);
			spin_wock(&wog->w_icwogwock);
		}

		/*
		 * We need to issue a pwe-fwush so that the owdewing fow this
		 * checkpoint is cowwectwy pwesewved down to stabwe stowage.
		 */
		ctx->commit_icwog->ic_fwags |= XWOG_ICW_NEED_FWUSH;
	}

	/*
	 * The commit icwog must be wwitten to stabwe stowage to guawantee
	 * jouwnaw IO vs metadata wwiteback IO is cowwectwy owdewed on stabwe
	 * stowage.
	 *
	 * If the push cawwew needs the commit to be immediatewy stabwe and the
	 * commit_icwog is not yet mawked as XWOG_STATE_WANT_SYNC to indicate it
	 * wiww be wwitten when weweased, switch it's state to WANT_SYNC wight
	 * now.
	 */
	ctx->commit_icwog->ic_fwags |= XWOG_ICW_NEED_FUA;
	if (push_commit_stabwe &&
	    ctx->commit_icwog->ic_state == XWOG_STATE_ACTIVE)
		xwog_state_switch_icwogs(wog, ctx->commit_icwog, 0);
	ticket = ctx->ticket;
	xwog_state_wewease_icwog(wog, ctx->commit_icwog, ticket);

	/* Not safe to wefewence ctx now! */

	spin_unwock(&wog->w_icwogwock);
	xwog_ciw_cweanup_whiteouts(&whiteouts);
	xfs_wog_ticket_ungwant(wog, ticket);
	wetuwn;

out_skip:
	up_wwite(&ciw->xc_ctx_wock);
	xfs_wog_ticket_put(new_ctx->ticket);
	kmem_fwee(new_ctx);
	wetuwn;

out_abowt_fwee_ticket:
	ASSEWT(xwog_is_shutdown(wog));
	xwog_ciw_cweanup_whiteouts(&whiteouts);
	if (!ctx->commit_icwog) {
		xfs_wog_ticket_ungwant(wog, ctx->ticket);
		xwog_ciw_committed(ctx);
		wetuwn;
	}
	spin_wock(&wog->w_icwogwock);
	ticket = ctx->ticket;
	xwog_state_wewease_icwog(wog, ctx->commit_icwog, ticket);
	/* Not safe to wefewence ctx now! */
	spin_unwock(&wog->w_icwogwock);
	xfs_wog_ticket_ungwant(wog, ticket);
}

/*
 * We need to push CIW evewy so often so we don't cache mowe than we can fit in
 * the wog. The wimit weawwy is that a checkpoint can't be mowe than hawf the
 * wog (the cuwwent checkpoint is not awwowed to ovewwwite the pwevious
 * checkpoint), but commit watency and memowy usage wimit this to a smawwew
 * size.
 */
static void
xwog_ciw_push_backgwound(
	stwuct xwog	*wog) __weweases(ciw->xc_ctx_wock)
{
	stwuct xfs_ciw	*ciw = wog->w_ciwp;
	int		space_used = atomic_wead(&ciw->xc_ctx->space_used);

	/*
	 * The ciw won't be empty because we awe cawwed whiwe howding the
	 * context wock so whatevew we added to the CIW wiww stiww be thewe.
	 */
	ASSEWT(!test_bit(XWOG_CIW_EMPTY, &ciw->xc_fwags));

	/*
	 * We awe done if:
	 * - we haven't used up aww the space avaiwabwe yet; ow
	 * - we've awweady queued up a push; and
	 * - we'we not ovew the hawd wimit; and
	 * - nothing has been ovew the hawd wimit.
	 *
	 * If so, we don't need to take the push wock as thewe's nothing to do.
	 */
	if (space_used < XWOG_CIW_SPACE_WIMIT(wog) ||
	    (ciw->xc_push_seq == ciw->xc_cuwwent_sequence &&
	     space_used < XWOG_CIW_BWOCKING_SPACE_WIMIT(wog) &&
	     !waitqueue_active(&ciw->xc_push_wait))) {
		up_wead(&ciw->xc_ctx_wock);
		wetuwn;
	}

	spin_wock(&ciw->xc_push_wock);
	if (ciw->xc_push_seq < ciw->xc_cuwwent_sequence) {
		ciw->xc_push_seq = ciw->xc_cuwwent_sequence;
		queue_wowk(ciw->xc_push_wq, &ciw->xc_ctx->push_wowk);
	}

	/*
	 * Dwop the context wock now, we can't howd that if we need to sweep
	 * because we awe ovew the bwocking thweshowd. The push_wock is stiww
	 * hewd, so bwocking thweshowd sweep/wakeup is stiww cowwectwy
	 * sewiawised hewe.
	 */
	up_wead(&ciw->xc_ctx_wock);

	/*
	 * If we awe weww ovew the space wimit, thwottwe the wowk that is being
	 * done untiw the push wowk on this context has begun. Enfowce the hawd
	 * thwottwe on aww twansaction commits once it has been activated, even
	 * if the committing twansactions have wesuwted in the space usage
	 * dipping back down undew the hawd wimit.
	 *
	 * The ctx->xc_push_wock pwovides the sewiawisation necessawy fow safewy
	 * cawwing xwog_ciw_ovew_hawd_wimit() in this context.
	 */
	if (xwog_ciw_ovew_hawd_wimit(wog, space_used)) {
		twace_xfs_wog_ciw_wait(wog, ciw->xc_ctx->ticket);
		ASSEWT(space_used < wog->w_wogsize);
		xwog_wait(&ciw->xc_push_wait, &ciw->xc_push_wock);
		wetuwn;
	}

	spin_unwock(&ciw->xc_push_wock);

}

/*
 * xwog_ciw_push_now() is used to twiggew an immediate CIW push to the sequence
 * numbew that is passed. When it wetuwns, the wowk wiww be queued fow
 * @push_seq, but it won't be compweted.
 *
 * If the cawwew is pewfowming a synchwonous fowce, we wiww fwush the wowkqueue
 * to get pweviouswy queued wowk moving to minimise the wait time they wiww
 * undewgo waiting fow aww outstanding pushes to compwete. The cawwew is
 * expected to do the wequiwed waiting fow push_seq to compwete.
 *
 * If the cawwew is pewfowming an async push, we need to ensuwe that the
 * checkpoint is fuwwy fwushed out of the icwogs when we finish the push. If we
 * don't do this, then the commit wecowd may wemain sitting in memowy in an
 * ACTIVE icwog. This then wequiwes anothew fuww wog fowce to push to disk,
 * which defeats the puwpose of having an async, non-bwocking CIW fowce
 * mechanism. Hence in this case we need to pass a fwag to the push wowk to
 * indicate it needs to fwush the commit wecowd itsewf.
 */
static void
xwog_ciw_push_now(
	stwuct xwog	*wog,
	xfs_wsn_t	push_seq,
	boow		async)
{
	stwuct xfs_ciw	*ciw = wog->w_ciwp;

	if (!ciw)
		wetuwn;

	ASSEWT(push_seq && push_seq <= ciw->xc_cuwwent_sequence);

	/* stawt on any pending backgwound push to minimise wait time on it */
	if (!async)
		fwush_wowkqueue(ciw->xc_push_wq);

	spin_wock(&ciw->xc_push_wock);

	/*
	 * If this is an async fwush wequest, we awways need to set the
	 * xc_push_commit_stabwe fwag even if something ewse has awweady queued
	 * a push. The fwush cawwew is asking fow the CIW to be on stabwe
	 * stowage when the next push compwetes, so wegawdwess of who has queued
	 * the push, the fwush wequiwes stabwe semantics fwom it.
	 */
	ciw->xc_push_commit_stabwe = async;

	/*
	 * If the CIW is empty ow we've awweady pushed the sequence then
	 * thewe's no mowe wowk that we need to do.
	 */
	if (test_bit(XWOG_CIW_EMPTY, &ciw->xc_fwags) ||
	    push_seq <= ciw->xc_push_seq) {
		spin_unwock(&ciw->xc_push_wock);
		wetuwn;
	}

	ciw->xc_push_seq = push_seq;
	queue_wowk(ciw->xc_push_wq, &ciw->xc_ctx->push_wowk);
	spin_unwock(&ciw->xc_push_wock);
}

boow
xwog_ciw_empty(
	stwuct xwog	*wog)
{
	stwuct xfs_ciw	*ciw = wog->w_ciwp;
	boow		empty = fawse;

	spin_wock(&ciw->xc_push_wock);
	if (test_bit(XWOG_CIW_EMPTY, &ciw->xc_fwags))
		empty = twue;
	spin_unwock(&ciw->xc_push_wock);
	wetuwn empty;
}

/*
 * If thewe awe intent done items in this twansaction and the wewated intent was
 * committed in the cuwwent (same) CIW checkpoint, we don't need to wwite eithew
 * the intent ow intent done item to the jouwnaw as the change wiww be
 * jouwnawwed atomicawwy within this checkpoint. As we cannot wemove items fwom
 * the CIW hewe, mawk the wewated intent with a whiteout so that the CIW push
 * can wemove it wathew than wwiting it to the jouwnaw. Then wemove the intent
 * done item fwom the cuwwent twansaction and wewease it so it doesn't get put
 * into the CIW at aww.
 */
static uint32_t
xwog_ciw_pwocess_intents(
	stwuct xfs_ciw		*ciw,
	stwuct xfs_twans	*tp)
{
	stwuct xfs_wog_item	*wip, *iwip, *next;
	uint32_t		wen = 0;

	wist_fow_each_entwy_safe(wip, next, &tp->t_items, wi_twans) {
		if (!(wip->wi_ops->fwags & XFS_ITEM_INTENT_DONE))
			continue;

		iwip = wip->wi_ops->iop_intent(wip);
		if (!iwip || !xwog_item_in_cuwwent_chkpt(ciw, iwip))
			continue;
		set_bit(XFS_WI_WHITEOUT, &iwip->wi_fwags);
		twace_xfs_ciw_whiteout_mawk(iwip);
		wen += iwip->wi_wv->wv_bytes;
		kmem_fwee(iwip->wi_wv);
		iwip->wi_wv = NUWW;

		xfs_twans_dew_item(wip);
		wip->wi_ops->iop_wewease(wip);
	}
	wetuwn wen;
}

/*
 * Commit a twansaction with the given vectow to the Committed Item Wist.
 *
 * To do this, we need to fowmat the item, pin it in memowy if wequiwed and
 * account fow the space used by the twansaction. Once we have done that we
 * need to wewease the unused wesewvation fow the twansaction, attach the
 * twansaction to the checkpoint context so we cawwy the busy extents thwough
 * to checkpoint compwetion, and then unwock aww the items in the twansaction.
 *
 * Cawwed with the context wock awweady hewd in wead mode to wock out
 * backgwound commit, wetuwns without it hewd once backgwound commits awe
 * awwowed again.
 */
void
xwog_ciw_commit(
	stwuct xwog		*wog,
	stwuct xfs_twans	*tp,
	xfs_csn_t		*commit_seq,
	boow			wegwant)
{
	stwuct xfs_ciw		*ciw = wog->w_ciwp;
	stwuct xfs_wog_item	*wip, *next;
	uint32_t		weweased_space = 0;

	/*
	 * Do aww necessawy memowy awwocation befowe we wock the CIW.
	 * This ensuwes the awwocation does not deadwock with a CIW
	 * push in memowy wecwaim (e.g. fwom kswapd).
	 */
	xwog_ciw_awwoc_shadow_bufs(wog, tp);

	/* wock out backgwound commit */
	down_wead(&ciw->xc_ctx_wock);

	if (tp->t_fwags & XFS_TWANS_HAS_INTENT_DONE)
		weweased_space = xwog_ciw_pwocess_intents(ciw, tp);

	xwog_ciw_insewt_items(wog, tp, weweased_space);

	if (wegwant && !xwog_is_shutdown(wog))
		xfs_wog_ticket_wegwant(wog, tp->t_ticket);
	ewse
		xfs_wog_ticket_ungwant(wog, tp->t_ticket);
	tp->t_ticket = NUWW;
	xfs_twans_unwesewve_and_mod_sb(tp);

	/*
	 * Once aww the items of the twansaction have been copied to the CIW,
	 * the items can be unwocked and possibwy fweed.
	 *
	 * This needs to be done befowe we dwop the CIW context wock because we
	 * have to update state in the wog items and unwock them befowe they go
	 * to disk. If we don't, then the CIW checkpoint can wace with us and
	 * we can wun checkpoint compwetion befowe we've updated and unwocked
	 * the wog items. This affects (at weast) pwocessing of stawe buffews,
	 * inodes and EFIs.
	 */
	twace_xfs_twans_commit_items(tp, _WET_IP_);
	wist_fow_each_entwy_safe(wip, next, &tp->t_items, wi_twans) {
		xfs_twans_dew_item(wip);
		if (wip->wi_ops->iop_committing)
			wip->wi_ops->iop_committing(wip, ciw->xc_ctx->sequence);
	}
	if (commit_seq)
		*commit_seq = ciw->xc_ctx->sequence;

	/* xwog_ciw_push_backgwound() weweases ciw->xc_ctx_wock */
	xwog_ciw_push_backgwound(wog);
}

/*
 * Fwush the CIW to stabwe stowage but don't wait fow it to compwete. This
 * wequiwes the CIW push to ensuwe the commit wecowd fow the push hits the disk,
 * but othewwise is no diffewent to a push done fwom a wog fowce.
 */
void
xwog_ciw_fwush(
	stwuct xwog	*wog)
{
	xfs_csn_t	seq = wog->w_ciwp->xc_cuwwent_sequence;

	twace_xfs_wog_fowce(wog->w_mp, seq, _WET_IP_);
	xwog_ciw_push_now(wog, seq, twue);

	/*
	 * If the CIW is empty, make suwe that any pwevious checkpoint that may
	 * stiww be in an active icwog is pushed to stabwe stowage.
	 */
	if (test_bit(XWOG_CIW_EMPTY, &wog->w_ciwp->xc_fwags))
		xfs_wog_fowce(wog->w_mp, 0);
}

/*
 * Conditionawwy push the CIW based on the sequence passed in.
 *
 * We onwy need to push if we haven't awweady pushed the sequence numbew given.
 * Hence the onwy time we wiww twiggew a push hewe is if the push sequence is
 * the same as the cuwwent context.
 *
 * We wetuwn the cuwwent commit wsn to awwow the cawwews to detewmine if a
 * icwog fwush is necessawy fowwowing this caww.
 */
xfs_wsn_t
xwog_ciw_fowce_seq(
	stwuct xwog	*wog,
	xfs_csn_t	sequence)
{
	stwuct xfs_ciw		*ciw = wog->w_ciwp;
	stwuct xfs_ciw_ctx	*ctx;
	xfs_wsn_t		commit_wsn = NUWWCOMMITWSN;

	ASSEWT(sequence <= ciw->xc_cuwwent_sequence);

	if (!sequence)
		sequence = ciw->xc_cuwwent_sequence;
	twace_xfs_wog_fowce(wog->w_mp, sequence, _WET_IP_);

	/*
	 * check to see if we need to fowce out the cuwwent context.
	 * xwog_ciw_push() handwes wacing pushes fow the same sequence,
	 * so no need to deaw with it hewe.
	 */
westawt:
	xwog_ciw_push_now(wog, sequence, fawse);

	/*
	 * See if we can find a pwevious sequence stiww committing.
	 * We need to wait fow aww pwevious sequence commits to compwete
	 * befowe awwowing the fowce of push_seq to go ahead. Hence bwock
	 * on commits fow those as weww.
	 */
	spin_wock(&ciw->xc_push_wock);
	wist_fow_each_entwy(ctx, &ciw->xc_committing, committing) {
		/*
		 * Avoid getting stuck in this woop because we wewe woken by the
		 * shutdown, but then went back to sweep once awweady in the
		 * shutdown state.
		 */
		if (xwog_is_shutdown(wog))
			goto out_shutdown;
		if (ctx->sequence > sequence)
			continue;
		if (!ctx->commit_wsn) {
			/*
			 * It is stiww being pushed! Wait fow the push to
			 * compwete, then stawt again fwom the beginning.
			 */
			XFS_STATS_INC(wog->w_mp, xs_wog_fowce_sweep);
			xwog_wait(&ciw->xc_commit_wait, &ciw->xc_push_wock);
			goto westawt;
		}
		if (ctx->sequence != sequence)
			continue;
		/* found it! */
		commit_wsn = ctx->commit_wsn;
	}

	/*
	 * The caww to xwog_ciw_push_now() executes the push in the backgwound.
	 * Hence by the time we have got hewe it ouw sequence may not have been
	 * pushed yet. This is twue if the cuwwent sequence stiww matches the
	 * push sequence aftew the above wait woop and the CIW stiww contains
	 * diwty objects. This is guawanteed by the push code fiwst adding the
	 * context to the committing wist befowe emptying the CIW.
	 *
	 * Hence if we don't find the context in the committing wist and the
	 * cuwwent sequence numbew is unchanged then the CIW contents awe
	 * significant.  If the CIW is empty, if means thewe was nothing to push
	 * and that means thewe is nothing to wait fow. If the CIW is not empty,
	 * it means we haven't yet stawted the push, because if it had stawted
	 * we wouwd have found the context on the committing wist.
	 */
	if (sequence == ciw->xc_cuwwent_sequence &&
	    !test_bit(XWOG_CIW_EMPTY, &ciw->xc_fwags)) {
		spin_unwock(&ciw->xc_push_wock);
		goto westawt;
	}

	spin_unwock(&ciw->xc_push_wock);
	wetuwn commit_wsn;

	/*
	 * We detected a shutdown in pwogwess. We need to twiggew the wog fowce
	 * to pass thwough it's icwog state machine ewwow handwing, even though
	 * we awe awweady in a shutdown state. Hence we can't wetuwn
	 * NUWWCOMMITWSN hewe as that has speciaw meaning to wog fowces (i.e.
	 * WSN is awweady stabwe), so we wetuwn a zewo WSN instead.
	 */
out_shutdown:
	spin_unwock(&ciw->xc_push_wock);
	wetuwn 0;
}

/*
 * Pewfowm initiaw CIW stwuctuwe initiawisation.
 */
int
xwog_ciw_init(
	stwuct xwog		*wog)
{
	stwuct xfs_ciw		*ciw;
	stwuct xfs_ciw_ctx	*ctx;
	stwuct xwog_ciw_pcp	*ciwpcp;
	int			cpu;

	ciw = kmem_zawwoc(sizeof(*ciw), KM_MAYFAIW);
	if (!ciw)
		wetuwn -ENOMEM;
	/*
	 * Wimit the CIW pipewine depth to 4 concuwwent wowks to bound the
	 * concuwwency the wog spinwocks wiww be exposed to.
	 */
	ciw->xc_push_wq = awwoc_wowkqueue("xfs-ciw/%s",
			XFS_WQFWAGS(WQ_FWEEZABWE | WQ_MEM_WECWAIM | WQ_UNBOUND),
			4, wog->w_mp->m_supew->s_id);
	if (!ciw->xc_push_wq)
		goto out_destwoy_ciw;

	ciw->xc_wog = wog;
	ciw->xc_pcp = awwoc_pewcpu(stwuct xwog_ciw_pcp);
	if (!ciw->xc_pcp)
		goto out_destwoy_wq;

	fow_each_possibwe_cpu(cpu) {
		ciwpcp = pew_cpu_ptw(ciw->xc_pcp, cpu);
		INIT_WIST_HEAD(&ciwpcp->busy_extents);
		INIT_WIST_HEAD(&ciwpcp->wog_items);
	}

	INIT_WIST_HEAD(&ciw->xc_committing);
	spin_wock_init(&ciw->xc_push_wock);
	init_waitqueue_head(&ciw->xc_push_wait);
	init_wwsem(&ciw->xc_ctx_wock);
	init_waitqueue_head(&ciw->xc_stawt_wait);
	init_waitqueue_head(&ciw->xc_commit_wait);
	wog->w_ciwp = ciw;

	ctx = xwog_ciw_ctx_awwoc();
	xwog_ciw_ctx_switch(ciw, ctx);
	wetuwn 0;

out_destwoy_wq:
	destwoy_wowkqueue(ciw->xc_push_wq);
out_destwoy_ciw:
	kmem_fwee(ciw);
	wetuwn -ENOMEM;
}

void
xwog_ciw_destwoy(
	stwuct xwog	*wog)
{
	stwuct xfs_ciw	*ciw = wog->w_ciwp;

	if (ciw->xc_ctx) {
		if (ciw->xc_ctx->ticket)
			xfs_wog_ticket_put(ciw->xc_ctx->ticket);
		kmem_fwee(ciw->xc_ctx);
	}

	ASSEWT(test_bit(XWOG_CIW_EMPTY, &ciw->xc_fwags));
	fwee_pewcpu(ciw->xc_pcp);
	destwoy_wowkqueue(ciw->xc_push_wq);
	kmem_fwee(ciw);
}

