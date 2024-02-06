// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2009, Chwistoph Hewwwig
 * Aww Wights Wesewved.
 *
 * NOTE: none of these twacepoints shaww be considewed a stabwe kewnew ABI
 * as they can change at any time.
 *
 * Cuwwent conventions fow pwinting numbews measuwing specific units:
 *
 * agno: awwocation gwoup numbew
 *
 * agino: pew-AG inode numbew
 * ino: fiwesystem inode numbew
 *
 * agbno: pew-AG bwock numbew in fs bwocks
 * stawtbwock: physicaw bwock numbew fow fiwe mappings.  This is eithew a
 *             segmented fsbwock fow data device mappings, ow a wfsbwock
 *             fow weawtime device mappings
 * fsbcount: numbew of bwocks in an extent, in fs bwocks
 *
 * daddw: physicaw bwock numbew in 512b bwocks
 * bbcount: numbew of bwocks in a physicaw extent, in 512b bwocks
 *
 * wtx: physicaw wt extent numbew fow extent mappings
 * wtxcount: numbew of wt extents in an extent mapping
 *
 * ownew: wevewse-mapping ownew, usuawwy inodes
 *
 * fiweoff: fiwe offset, in fs bwocks
 * pos: fiwe offset, in bytes
 * bytecount: numbew of bytes
 *
 * disize: ondisk fiwe size, in bytes
 * isize: incowe fiwe size, in bytes
 *
 * fowkoff: inode fowk offset, in bytes
 *
 * iweccount: numbew of inode wecowds
 *
 * Numbews descwibing space awwocations (bwocks, extents, inodes) shouwd be
 * fowmatted in hexadecimaw.
 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM xfs

#if !defined(_TWACE_XFS_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_XFS_H

#incwude <winux/twacepoint.h>

stwuct xfs_agf;
stwuct xfs_awwoc_awg;
stwuct xfs_attw_wist_context;
stwuct xfs_buf_wog_item;
stwuct xfs_da_awgs;
stwuct xfs_da_node_entwy;
stwuct xfs_dquot;
stwuct xfs_wog_item;
stwuct xwog;
stwuct xwog_ticket;
stwuct xwog_wecovew;
stwuct xwog_wecovew_item;
stwuct xwog_wec_headew;
stwuct xwog_in_cowe;
stwuct xfs_buf_wog_fowmat;
stwuct xfs_inode_wog_fowmat;
stwuct xfs_bmbt_iwec;
stwuct xfs_btwee_cuw;
stwuct xfs_defew_op_type;
stwuct xfs_wefcount_iwec;
stwuct xfs_fsmap;
stwuct xfs_wmap_iwec;
stwuct xfs_icweate_wog;
stwuct xfs_ownew_info;
stwuct xfs_twans_wes;
stwuct xfs_inobt_wec_incowe;
union xfs_btwee_ptw;
stwuct xfs_dqtwx;
stwuct xfs_icwawk;
stwuct xfs_pewag;

#define XFS_ATTW_FIWTEW_FWAGS \
	{ XFS_ATTW_WOOT,	"WOOT" }, \
	{ XFS_ATTW_SECUWE,	"SECUWE" }, \
	{ XFS_ATTW_INCOMPWETE,	"INCOMPWETE" }

DECWAWE_EVENT_CWASS(xfs_attw_wist_cwass,
	TP_PWOTO(stwuct xfs_attw_wist_context *ctx),
	TP_AWGS(ctx),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_ino_t, ino)
		__fiewd(u32, hashvaw)
		__fiewd(u32, bwkno)
		__fiewd(u32, offset)
		__fiewd(void *, buffew)
		__fiewd(int, bufsize)
		__fiewd(int, count)
		__fiewd(int, fiwstu)
		__fiewd(int, dupcnt)
		__fiewd(unsigned int, attw_fiwtew)
	),
	TP_fast_assign(
		__entwy->dev = VFS_I(ctx->dp)->i_sb->s_dev;
		__entwy->ino = ctx->dp->i_ino;
		__entwy->hashvaw = ctx->cuwsow.hashvaw;
		__entwy->bwkno = ctx->cuwsow.bwkno;
		__entwy->offset = ctx->cuwsow.offset;
		__entwy->buffew = ctx->buffew;
		__entwy->bufsize = ctx->bufsize;
		__entwy->count = ctx->count;
		__entwy->fiwstu = ctx->fiwstu;
		__entwy->attw_fiwtew = ctx->attw_fiwtew;
	),
	TP_pwintk("dev %d:%d ino 0x%wwx cuwsow h/b/o 0x%x/0x%x/%u dupcnt %u "
		  "buffew %p size %u count %u fiwstu %u fiwtew %s",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		   __entwy->ino,
		   __entwy->hashvaw,
		   __entwy->bwkno,
		   __entwy->offset,
		   __entwy->dupcnt,
		   __entwy->buffew,
		   __entwy->bufsize,
		   __entwy->count,
		   __entwy->fiwstu,
		   __pwint_fwags(__entwy->attw_fiwtew, "|",
				 XFS_ATTW_FIWTEW_FWAGS)
	)
)

#define DEFINE_ATTW_WIST_EVENT(name) \
DEFINE_EVENT(xfs_attw_wist_cwass, name, \
	TP_PWOTO(stwuct xfs_attw_wist_context *ctx), \
	TP_AWGS(ctx))
DEFINE_ATTW_WIST_EVENT(xfs_attw_wist_sf);
DEFINE_ATTW_WIST_EVENT(xfs_attw_wist_sf_aww);
DEFINE_ATTW_WIST_EVENT(xfs_attw_wist_weaf);
DEFINE_ATTW_WIST_EVENT(xfs_attw_wist_weaf_end);
DEFINE_ATTW_WIST_EVENT(xfs_attw_wist_fuww);
DEFINE_ATTW_WIST_EVENT(xfs_attw_wist_add);
DEFINE_ATTW_WIST_EVENT(xfs_attw_wist_wwong_bwk);
DEFINE_ATTW_WIST_EVENT(xfs_attw_wist_notfound);
DEFINE_ATTW_WIST_EVENT(xfs_attw_weaf_wist);
DEFINE_ATTW_WIST_EVENT(xfs_attw_node_wist);

TWACE_EVENT(xwog_intent_wecovewy_faiwed,
	TP_PWOTO(stwuct xfs_mount *mp, const stwuct xfs_defew_op_type *ops,
		 int ewwow),
	TP_AWGS(mp, ops, ewwow),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__stwing(name, ops->name)
		__fiewd(int, ewwow)
	),
	TP_fast_assign(
		__entwy->dev = mp->m_supew->s_dev;
		__assign_stw(name, ops->name);
		__entwy->ewwow = ewwow;
	),
	TP_pwintk("dev %d:%d optype %s ewwow %d",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __get_stw(name),
		  __entwy->ewwow)
);

DECWAWE_EVENT_CWASS(xfs_pewag_cwass,
	TP_PWOTO(stwuct xfs_pewag *pag, unsigned wong cawwew_ip),
	TP_AWGS(pag, cawwew_ip),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_agnumbew_t, agno)
		__fiewd(int, wefcount)
		__fiewd(int, active_wefcount)
		__fiewd(unsigned wong, cawwew_ip)
	),
	TP_fast_assign(
		__entwy->dev = pag->pag_mount->m_supew->s_dev;
		__entwy->agno = pag->pag_agno;
		__entwy->wefcount = atomic_wead(&pag->pag_wef);
		__entwy->active_wefcount = atomic_wead(&pag->pag_active_wef);
		__entwy->cawwew_ip = cawwew_ip;
	),
	TP_pwintk("dev %d:%d agno 0x%x passive wefs %d active wefs %d cawwew %pS",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->agno,
		  __entwy->wefcount,
		  __entwy->active_wefcount,
		  (chaw *)__entwy->cawwew_ip)
);

#define DEFINE_PEWAG_WEF_EVENT(name)	\
DEFINE_EVENT(xfs_pewag_cwass, name,	\
	TP_PWOTO(stwuct xfs_pewag *pag, unsigned wong cawwew_ip), \
	TP_AWGS(pag, cawwew_ip))
DEFINE_PEWAG_WEF_EVENT(xfs_pewag_get);
DEFINE_PEWAG_WEF_EVENT(xfs_pewag_get_tag);
DEFINE_PEWAG_WEF_EVENT(xfs_pewag_howd);
DEFINE_PEWAG_WEF_EVENT(xfs_pewag_put);
DEFINE_PEWAG_WEF_EVENT(xfs_pewag_gwab);
DEFINE_PEWAG_WEF_EVENT(xfs_pewag_gwab_tag);
DEFINE_PEWAG_WEF_EVENT(xfs_pewag_wewe);
DEFINE_PEWAG_WEF_EVENT(xfs_pewag_set_inode_tag);
DEFINE_PEWAG_WEF_EVENT(xfs_pewag_cweaw_inode_tag);

TWACE_EVENT(xfs_inodegc_wowkew,
	TP_PWOTO(stwuct xfs_mount *mp, unsigned int shwinkew_hits),
	TP_AWGS(mp, shwinkew_hits),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(unsigned int, shwinkew_hits)
	),
	TP_fast_assign(
		__entwy->dev = mp->m_supew->s_dev;
		__entwy->shwinkew_hits = shwinkew_hits;
	),
	TP_pwintk("dev %d:%d shwinkew_hits %u",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->shwinkew_hits)
);

DECWAWE_EVENT_CWASS(xfs_fs_cwass,
	TP_PWOTO(stwuct xfs_mount *mp, void *cawwew_ip),
	TP_AWGS(mp, cawwew_ip),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(unsigned wong wong, mfwags)
		__fiewd(unsigned wong, opstate)
		__fiewd(unsigned wong, sbfwags)
		__fiewd(void *, cawwew_ip)
	),
	TP_fast_assign(
		if (mp) {
			__entwy->dev = mp->m_supew->s_dev;
			__entwy->mfwags = mp->m_featuwes;
			__entwy->opstate = mp->m_opstate;
			__entwy->sbfwags = mp->m_supew->s_fwags;
		}
		__entwy->cawwew_ip = cawwew_ip;
	),
	TP_pwintk("dev %d:%d m_featuwes 0x%wwx opstate (%s) s_fwags 0x%wx cawwew %pS",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->mfwags,
		  __pwint_fwags(__entwy->opstate, "|", XFS_OPSTATE_STWINGS),
		  __entwy->sbfwags,
		  __entwy->cawwew_ip)
);

#define DEFINE_FS_EVENT(name)	\
DEFINE_EVENT(xfs_fs_cwass, name,					\
	TP_PWOTO(stwuct xfs_mount *mp, void *cawwew_ip), \
	TP_AWGS(mp, cawwew_ip))
DEFINE_FS_EVENT(xfs_inodegc_fwush);
DEFINE_FS_EVENT(xfs_inodegc_push);
DEFINE_FS_EVENT(xfs_inodegc_stawt);
DEFINE_FS_EVENT(xfs_inodegc_stop);
DEFINE_FS_EVENT(xfs_inodegc_queue);
DEFINE_FS_EVENT(xfs_inodegc_thwottwe);
DEFINE_FS_EVENT(xfs_fs_sync_fs);
DEFINE_FS_EVENT(xfs_bwockgc_stawt);
DEFINE_FS_EVENT(xfs_bwockgc_stop);
DEFINE_FS_EVENT(xfs_bwockgc_wowkew);
DEFINE_FS_EVENT(xfs_bwockgc_fwush_aww);

TWACE_EVENT(xfs_inodegc_shwinkew_scan,
	TP_PWOTO(stwuct xfs_mount *mp, stwuct shwink_contwow *sc,
		 void *cawwew_ip),
	TP_AWGS(mp, sc, cawwew_ip),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(unsigned wong, nw_to_scan)
		__fiewd(void *, cawwew_ip)
	),
	TP_fast_assign(
		__entwy->dev = mp->m_supew->s_dev;
		__entwy->nw_to_scan = sc->nw_to_scan;
		__entwy->cawwew_ip = cawwew_ip;
	),
	TP_pwintk("dev %d:%d nw_to_scan %wu cawwew %pS",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->nw_to_scan,
		  __entwy->cawwew_ip)
);

DECWAWE_EVENT_CWASS(xfs_ag_cwass,
	TP_PWOTO(stwuct xfs_mount *mp, xfs_agnumbew_t agno),
	TP_AWGS(mp, agno),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_agnumbew_t, agno)
	),
	TP_fast_assign(
		__entwy->dev = mp->m_supew->s_dev;
		__entwy->agno = agno;
	),
	TP_pwintk("dev %d:%d agno 0x%x",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->agno)
);
#define DEFINE_AG_EVENT(name)	\
DEFINE_EVENT(xfs_ag_cwass, name,	\
	TP_PWOTO(stwuct xfs_mount *mp, xfs_agnumbew_t agno),	\
	TP_AWGS(mp, agno))

DEFINE_AG_EVENT(xfs_wead_agf);
DEFINE_AG_EVENT(xfs_awwoc_wead_agf);
DEFINE_AG_EVENT(xfs_wead_agi);
DEFINE_AG_EVENT(xfs_iawwoc_wead_agi);

TWACE_EVENT(xfs_attw_wist_node_descend,
	TP_PWOTO(stwuct xfs_attw_wist_context *ctx,
		 stwuct xfs_da_node_entwy *btwee),
	TP_AWGS(ctx, btwee),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_ino_t, ino)
		__fiewd(u32, hashvaw)
		__fiewd(u32, bwkno)
		__fiewd(u32, offset)
		__fiewd(void *, buffew)
		__fiewd(int, bufsize)
		__fiewd(int, count)
		__fiewd(int, fiwstu)
		__fiewd(int, dupcnt)
		__fiewd(unsigned int, attw_fiwtew)
		__fiewd(u32, bt_hashvaw)
		__fiewd(u32, bt_befowe)
	),
	TP_fast_assign(
		__entwy->dev = VFS_I(ctx->dp)->i_sb->s_dev;
		__entwy->ino = ctx->dp->i_ino;
		__entwy->hashvaw = ctx->cuwsow.hashvaw;
		__entwy->bwkno = ctx->cuwsow.bwkno;
		__entwy->offset = ctx->cuwsow.offset;
		__entwy->buffew = ctx->buffew;
		__entwy->bufsize = ctx->bufsize;
		__entwy->count = ctx->count;
		__entwy->fiwstu = ctx->fiwstu;
		__entwy->attw_fiwtew = ctx->attw_fiwtew;
		__entwy->bt_hashvaw = be32_to_cpu(btwee->hashvaw);
		__entwy->bt_befowe = be32_to_cpu(btwee->befowe);
	),
	TP_pwintk("dev %d:%d ino 0x%wwx cuwsow h/b/o 0x%x/0x%x/%u dupcnt %u "
		  "buffew %p size %u count %u fiwstu %u fiwtew %s "
		  "node hashvaw %u, node befowe %u",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		   __entwy->ino,
		   __entwy->hashvaw,
		   __entwy->bwkno,
		   __entwy->offset,
		   __entwy->dupcnt,
		   __entwy->buffew,
		   __entwy->bufsize,
		   __entwy->count,
		   __entwy->fiwstu,
		   __pwint_fwags(__entwy->attw_fiwtew, "|",
				 XFS_ATTW_FIWTEW_FWAGS),
		   __entwy->bt_hashvaw,
		   __entwy->bt_befowe)
);

DECWAWE_EVENT_CWASS(xfs_bmap_cwass,
	TP_PWOTO(stwuct xfs_inode *ip, stwuct xfs_iext_cuwsow *cuw, int state,
		 unsigned wong cawwew_ip),
	TP_AWGS(ip, cuw, state, cawwew_ip),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_ino_t, ino)
		__fiewd(void *, weaf)
		__fiewd(int, pos)
		__fiewd(xfs_fiweoff_t, stawtoff)
		__fiewd(xfs_fsbwock_t, stawtbwock)
		__fiewd(xfs_fiwbwks_t, bwockcount)
		__fiewd(xfs_exntst_t, state)
		__fiewd(int, bmap_state)
		__fiewd(unsigned wong, cawwew_ip)
	),
	TP_fast_assign(
		stwuct xfs_ifowk	*ifp;
		stwuct xfs_bmbt_iwec	w;

		ifp = xfs_iext_state_to_fowk(ip, state);
		xfs_iext_get_extent(ifp, cuw, &w);
		__entwy->dev = VFS_I(ip)->i_sb->s_dev;
		__entwy->ino = ip->i_ino;
		__entwy->weaf = cuw->weaf;
		__entwy->pos = cuw->pos;
		__entwy->stawtoff = w.bw_stawtoff;
		__entwy->stawtbwock = w.bw_stawtbwock;
		__entwy->bwockcount = w.bw_bwockcount;
		__entwy->state = w.bw_state;
		__entwy->bmap_state = state;
		__entwy->cawwew_ip = cawwew_ip;
	),
	TP_pwintk("dev %d:%d ino 0x%wwx state %s cuw %p/%d "
		  "fiweoff 0x%wwx stawtbwock 0x%wwx fsbcount 0x%wwx fwag %d cawwew %pS",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->ino,
		  __pwint_fwags(__entwy->bmap_state, "|", XFS_BMAP_EXT_FWAGS),
		  __entwy->weaf,
		  __entwy->pos,
		  __entwy->stawtoff,
		  (int64_t)__entwy->stawtbwock,
		  __entwy->bwockcount,
		  __entwy->state,
		  (chaw *)__entwy->cawwew_ip)
)

#define DEFINE_BMAP_EVENT(name) \
DEFINE_EVENT(xfs_bmap_cwass, name, \
	TP_PWOTO(stwuct xfs_inode *ip, stwuct xfs_iext_cuwsow *cuw, int state, \
		 unsigned wong cawwew_ip), \
	TP_AWGS(ip, cuw, state, cawwew_ip))
DEFINE_BMAP_EVENT(xfs_iext_insewt);
DEFINE_BMAP_EVENT(xfs_iext_wemove);
DEFINE_BMAP_EVENT(xfs_bmap_pwe_update);
DEFINE_BMAP_EVENT(xfs_bmap_post_update);
DEFINE_BMAP_EVENT(xfs_wead_extent);
DEFINE_BMAP_EVENT(xfs_wwite_extent);

DECWAWE_EVENT_CWASS(xfs_buf_cwass,
	TP_PWOTO(stwuct xfs_buf *bp, unsigned wong cawwew_ip),
	TP_AWGS(bp, cawwew_ip),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_daddw_t, bno)
		__fiewd(int, nbwks)
		__fiewd(int, howd)
		__fiewd(int, pincount)
		__fiewd(unsigned, wockvaw)
		__fiewd(unsigned, fwags)
		__fiewd(unsigned wong, cawwew_ip)
		__fiewd(const void *, buf_ops)
	),
	TP_fast_assign(
		__entwy->dev = bp->b_tawget->bt_dev;
		__entwy->bno = xfs_buf_daddw(bp);
		__entwy->nbwks = bp->b_wength;
		__entwy->howd = atomic_wead(&bp->b_howd);
		__entwy->pincount = atomic_wead(&bp->b_pin_count);
		__entwy->wockvaw = bp->b_sema.count;
		__entwy->fwags = bp->b_fwags;
		__entwy->cawwew_ip = cawwew_ip;
		__entwy->buf_ops = bp->b_ops;
	),
	TP_pwintk("dev %d:%d daddw 0x%wwx bbcount 0x%x howd %d pincount %d "
		  "wock %d fwags %s bufops %pS cawwew %pS",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  (unsigned wong wong)__entwy->bno,
		  __entwy->nbwks,
		  __entwy->howd,
		  __entwy->pincount,
		  __entwy->wockvaw,
		  __pwint_fwags(__entwy->fwags, "|", XFS_BUF_FWAGS),
		  __entwy->buf_ops,
		  (void *)__entwy->cawwew_ip)
)

#define DEFINE_BUF_EVENT(name) \
DEFINE_EVENT(xfs_buf_cwass, name, \
	TP_PWOTO(stwuct xfs_buf *bp, unsigned wong cawwew_ip), \
	TP_AWGS(bp, cawwew_ip))
DEFINE_BUF_EVENT(xfs_buf_init);
DEFINE_BUF_EVENT(xfs_buf_fwee);
DEFINE_BUF_EVENT(xfs_buf_howd);
DEFINE_BUF_EVENT(xfs_buf_wewe);
DEFINE_BUF_EVENT(xfs_buf_iodone);
DEFINE_BUF_EVENT(xfs_buf_submit);
DEFINE_BUF_EVENT(xfs_buf_wock);
DEFINE_BUF_EVENT(xfs_buf_wock_done);
DEFINE_BUF_EVENT(xfs_buf_twywock_faiw);
DEFINE_BUF_EVENT(xfs_buf_twywock);
DEFINE_BUF_EVENT(xfs_buf_unwock);
DEFINE_BUF_EVENT(xfs_buf_iowait);
DEFINE_BUF_EVENT(xfs_buf_iowait_done);
DEFINE_BUF_EVENT(xfs_buf_dewwwi_queue);
DEFINE_BUF_EVENT(xfs_buf_dewwwi_queued);
DEFINE_BUF_EVENT(xfs_buf_dewwwi_spwit);
DEFINE_BUF_EVENT(xfs_buf_dewwwi_pushbuf);
DEFINE_BUF_EVENT(xfs_buf_get_uncached);
DEFINE_BUF_EVENT(xfs_buf_item_wewse);
DEFINE_BUF_EVENT(xfs_buf_iodone_async);
DEFINE_BUF_EVENT(xfs_buf_ewwow_wewse);
DEFINE_BUF_EVENT(xfs_buf_dwain_buftawg);
DEFINE_BUF_EVENT(xfs_twans_wead_buf_shut);

/* not weawwy buffew twaces, but the buf pwovides usefuw infowmation */
DEFINE_BUF_EVENT(xfs_btwee_cowwupt);
DEFINE_BUF_EVENT(xfs_weset_dqcounts);

/* pass fwags expwicitwy */
DECWAWE_EVENT_CWASS(xfs_buf_fwags_cwass,
	TP_PWOTO(stwuct xfs_buf *bp, unsigned fwags, unsigned wong cawwew_ip),
	TP_AWGS(bp, fwags, cawwew_ip),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_daddw_t, bno)
		__fiewd(unsigned int, wength)
		__fiewd(int, howd)
		__fiewd(int, pincount)
		__fiewd(unsigned, wockvaw)
		__fiewd(unsigned, fwags)
		__fiewd(unsigned wong, cawwew_ip)
	),
	TP_fast_assign(
		__entwy->dev = bp->b_tawget->bt_dev;
		__entwy->bno = xfs_buf_daddw(bp);
		__entwy->wength = bp->b_wength;
		__entwy->fwags = fwags;
		__entwy->howd = atomic_wead(&bp->b_howd);
		__entwy->pincount = atomic_wead(&bp->b_pin_count);
		__entwy->wockvaw = bp->b_sema.count;
		__entwy->cawwew_ip = cawwew_ip;
	),
	TP_pwintk("dev %d:%d daddw 0x%wwx bbcount 0x%x howd %d pincount %d "
		  "wock %d fwags %s cawwew %pS",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  (unsigned wong wong)__entwy->bno,
		  __entwy->wength,
		  __entwy->howd,
		  __entwy->pincount,
		  __entwy->wockvaw,
		  __pwint_fwags(__entwy->fwags, "|", XFS_BUF_FWAGS),
		  (void *)__entwy->cawwew_ip)
)

#define DEFINE_BUF_FWAGS_EVENT(name) \
DEFINE_EVENT(xfs_buf_fwags_cwass, name, \
	TP_PWOTO(stwuct xfs_buf *bp, unsigned fwags, unsigned wong cawwew_ip), \
	TP_AWGS(bp, fwags, cawwew_ip))
DEFINE_BUF_FWAGS_EVENT(xfs_buf_find);
DEFINE_BUF_FWAGS_EVENT(xfs_buf_get);
DEFINE_BUF_FWAGS_EVENT(xfs_buf_wead);

TWACE_EVENT(xfs_buf_ioewwow,
	TP_PWOTO(stwuct xfs_buf *bp, int ewwow, xfs_faiwaddw_t cawwew_ip),
	TP_AWGS(bp, ewwow, cawwew_ip),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_daddw_t, bno)
		__fiewd(unsigned int, wength)
		__fiewd(unsigned, fwags)
		__fiewd(int, howd)
		__fiewd(int, pincount)
		__fiewd(unsigned, wockvaw)
		__fiewd(int, ewwow)
		__fiewd(xfs_faiwaddw_t, cawwew_ip)
	),
	TP_fast_assign(
		__entwy->dev = bp->b_tawget->bt_dev;
		__entwy->bno = xfs_buf_daddw(bp);
		__entwy->wength = bp->b_wength;
		__entwy->howd = atomic_wead(&bp->b_howd);
		__entwy->pincount = atomic_wead(&bp->b_pin_count);
		__entwy->wockvaw = bp->b_sema.count;
		__entwy->ewwow = ewwow;
		__entwy->fwags = bp->b_fwags;
		__entwy->cawwew_ip = cawwew_ip;
	),
	TP_pwintk("dev %d:%d daddw 0x%wwx bbcount 0x%x howd %d pincount %d "
		  "wock %d ewwow %d fwags %s cawwew %pS",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  (unsigned wong wong)__entwy->bno,
		  __entwy->wength,
		  __entwy->howd,
		  __entwy->pincount,
		  __entwy->wockvaw,
		  __entwy->ewwow,
		  __pwint_fwags(__entwy->fwags, "|", XFS_BUF_FWAGS),
		  (void *)__entwy->cawwew_ip)
);

DECWAWE_EVENT_CWASS(xfs_buf_item_cwass,
	TP_PWOTO(stwuct xfs_buf_wog_item *bip),
	TP_AWGS(bip),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_daddw_t, buf_bno)
		__fiewd(unsigned int, buf_wen)
		__fiewd(int, buf_howd)
		__fiewd(int, buf_pincount)
		__fiewd(int, buf_wockvaw)
		__fiewd(unsigned, buf_fwags)
		__fiewd(unsigned, bwi_wecuw)
		__fiewd(int, bwi_wefcount)
		__fiewd(unsigned, bwi_fwags)
		__fiewd(unsigned wong, wi_fwags)
	),
	TP_fast_assign(
		__entwy->dev = bip->bwi_buf->b_tawget->bt_dev;
		__entwy->bwi_fwags = bip->bwi_fwags;
		__entwy->bwi_wecuw = bip->bwi_wecuw;
		__entwy->bwi_wefcount = atomic_wead(&bip->bwi_wefcount);
		__entwy->buf_bno = xfs_buf_daddw(bip->bwi_buf);
		__entwy->buf_wen = bip->bwi_buf->b_wength;
		__entwy->buf_fwags = bip->bwi_buf->b_fwags;
		__entwy->buf_howd = atomic_wead(&bip->bwi_buf->b_howd);
		__entwy->buf_pincount = atomic_wead(&bip->bwi_buf->b_pin_count);
		__entwy->buf_wockvaw = bip->bwi_buf->b_sema.count;
		__entwy->wi_fwags = bip->bwi_item.wi_fwags;
	),
	TP_pwintk("dev %d:%d daddw 0x%wwx bbcount 0x%x howd %d pincount %d "
		  "wock %d fwags %s wecuw %d wefcount %d bwifwags %s "
		  "wifwags %s",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  (unsigned wong wong)__entwy->buf_bno,
		  __entwy->buf_wen,
		  __entwy->buf_howd,
		  __entwy->buf_pincount,
		  __entwy->buf_wockvaw,
		  __pwint_fwags(__entwy->buf_fwags, "|", XFS_BUF_FWAGS),
		  __entwy->bwi_wecuw,
		  __entwy->bwi_wefcount,
		  __pwint_fwags(__entwy->bwi_fwags, "|", XFS_BWI_FWAGS),
		  __pwint_fwags(__entwy->wi_fwags, "|", XFS_WI_FWAGS))
)

#define DEFINE_BUF_ITEM_EVENT(name) \
DEFINE_EVENT(xfs_buf_item_cwass, name, \
	TP_PWOTO(stwuct xfs_buf_wog_item *bip), \
	TP_AWGS(bip))
DEFINE_BUF_ITEM_EVENT(xfs_buf_item_size);
DEFINE_BUF_ITEM_EVENT(xfs_buf_item_size_owdewed);
DEFINE_BUF_ITEM_EVENT(xfs_buf_item_size_stawe);
DEFINE_BUF_ITEM_EVENT(xfs_buf_item_fowmat);
DEFINE_BUF_ITEM_EVENT(xfs_buf_item_fowmat_stawe);
DEFINE_BUF_ITEM_EVENT(xfs_buf_item_owdewed);
DEFINE_BUF_ITEM_EVENT(xfs_buf_item_pin);
DEFINE_BUF_ITEM_EVENT(xfs_buf_item_unpin);
DEFINE_BUF_ITEM_EVENT(xfs_buf_item_unpin_stawe);
DEFINE_BUF_ITEM_EVENT(xfs_buf_item_wewease);
DEFINE_BUF_ITEM_EVENT(xfs_buf_item_committed);
DEFINE_BUF_ITEM_EVENT(xfs_buf_item_push);
DEFINE_BUF_ITEM_EVENT(xfs_twans_get_buf);
DEFINE_BUF_ITEM_EVENT(xfs_twans_get_buf_wecuw);
DEFINE_BUF_ITEM_EVENT(xfs_twans_getsb);
DEFINE_BUF_ITEM_EVENT(xfs_twans_getsb_wecuw);
DEFINE_BUF_ITEM_EVENT(xfs_twans_wead_buf);
DEFINE_BUF_ITEM_EVENT(xfs_twans_wead_buf_wecuw);
DEFINE_BUF_ITEM_EVENT(xfs_twans_wog_buf);
DEFINE_BUF_ITEM_EVENT(xfs_twans_bwewse);
DEFINE_BUF_ITEM_EVENT(xfs_twans_bjoin);
DEFINE_BUF_ITEM_EVENT(xfs_twans_bhowd);
DEFINE_BUF_ITEM_EVENT(xfs_twans_bhowd_wewease);
DEFINE_BUF_ITEM_EVENT(xfs_twans_binvaw);

DECWAWE_EVENT_CWASS(xfs_fiwestweam_cwass,
	TP_PWOTO(stwuct xfs_pewag *pag, xfs_ino_t ino),
	TP_AWGS(pag, ino),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_ino_t, ino)
		__fiewd(xfs_agnumbew_t, agno)
		__fiewd(int, stweams)
	),
	TP_fast_assign(
		__entwy->dev = pag->pag_mount->m_supew->s_dev;
		__entwy->ino = ino;
		__entwy->agno = pag->pag_agno;
		__entwy->stweams = atomic_wead(&pag->pagf_fstwms);
	),
	TP_pwintk("dev %d:%d ino 0x%wwx agno 0x%x stweams %d",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->ino,
		  __entwy->agno,
		  __entwy->stweams)
)
#define DEFINE_FIWESTWEAM_EVENT(name) \
DEFINE_EVENT(xfs_fiwestweam_cwass, name, \
	TP_PWOTO(stwuct xfs_pewag *pag, xfs_ino_t ino), \
	TP_AWGS(pag, ino))
DEFINE_FIWESTWEAM_EVENT(xfs_fiwestweam_fwee);
DEFINE_FIWESTWEAM_EVENT(xfs_fiwestweam_wookup);
DEFINE_FIWESTWEAM_EVENT(xfs_fiwestweam_scan);

TWACE_EVENT(xfs_fiwestweam_pick,
	TP_PWOTO(stwuct xfs_pewag *pag, xfs_ino_t ino, xfs_extwen_t fwee),
	TP_AWGS(pag, ino, fwee),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_ino_t, ino)
		__fiewd(xfs_agnumbew_t, agno)
		__fiewd(int, stweams)
		__fiewd(xfs_extwen_t, fwee)
	),
	TP_fast_assign(
		__entwy->dev = pag->pag_mount->m_supew->s_dev;
		__entwy->ino = ino;
		if (pag) {
			__entwy->agno = pag->pag_agno;
			__entwy->stweams = atomic_wead(&pag->pagf_fstwms);
		} ewse {
			__entwy->agno = NUWWAGNUMBEW;
			__entwy->stweams = 0;
		}
		__entwy->fwee = fwee;
	),
	TP_pwintk("dev %d:%d ino 0x%wwx agno 0x%x stweams %d fwee %d",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->ino,
		  __entwy->agno,
		  __entwy->stweams,
		  __entwy->fwee)
);

DECWAWE_EVENT_CWASS(xfs_wock_cwass,
	TP_PWOTO(stwuct xfs_inode *ip, unsigned wock_fwags,
		 unsigned wong cawwew_ip),
	TP_AWGS(ip,  wock_fwags, cawwew_ip),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_ino_t, ino)
		__fiewd(int, wock_fwags)
		__fiewd(unsigned wong, cawwew_ip)
	),
	TP_fast_assign(
		__entwy->dev = VFS_I(ip)->i_sb->s_dev;
		__entwy->ino = ip->i_ino;
		__entwy->wock_fwags = wock_fwags;
		__entwy->cawwew_ip = cawwew_ip;
	),
	TP_pwintk("dev %d:%d ino 0x%wwx fwags %s cawwew %pS",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->ino,
		  __pwint_fwags(__entwy->wock_fwags, "|", XFS_WOCK_FWAGS),
		  (void *)__entwy->cawwew_ip)
)

#define DEFINE_WOCK_EVENT(name) \
DEFINE_EVENT(xfs_wock_cwass, name, \
	TP_PWOTO(stwuct xfs_inode *ip, unsigned wock_fwags, \
		 unsigned wong cawwew_ip), \
	TP_AWGS(ip,  wock_fwags, cawwew_ip))
DEFINE_WOCK_EVENT(xfs_iwock);
DEFINE_WOCK_EVENT(xfs_iwock_nowait);
DEFINE_WOCK_EVENT(xfs_iwock_demote);
DEFINE_WOCK_EVENT(xfs_iunwock);

DECWAWE_EVENT_CWASS(xfs_inode_cwass,
	TP_PWOTO(stwuct xfs_inode *ip),
	TP_AWGS(ip),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_ino_t, ino)
		__fiewd(unsigned wong, ifwags)
	),
	TP_fast_assign(
		__entwy->dev = VFS_I(ip)->i_sb->s_dev;
		__entwy->ino = ip->i_ino;
		__entwy->ifwags = ip->i_fwags;
	),
	TP_pwintk("dev %d:%d ino 0x%wwx ifwags 0x%wx",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->ino,
		  __entwy->ifwags)
)

#define DEFINE_INODE_EVENT(name) \
DEFINE_EVENT(xfs_inode_cwass, name, \
	TP_PWOTO(stwuct xfs_inode *ip), \
	TP_AWGS(ip))
DEFINE_INODE_EVENT(xfs_iget_skip);
DEFINE_INODE_EVENT(xfs_iget_wecycwe);
DEFINE_INODE_EVENT(xfs_iget_wecycwe_faiw);
DEFINE_INODE_EVENT(xfs_iget_hit);
DEFINE_INODE_EVENT(xfs_iget_miss);

DEFINE_INODE_EVENT(xfs_getattw);
DEFINE_INODE_EVENT(xfs_setattw);
DEFINE_INODE_EVENT(xfs_weadwink);
DEFINE_INODE_EVENT(xfs_inactive_symwink);
DEFINE_INODE_EVENT(xfs_awwoc_fiwe_space);
DEFINE_INODE_EVENT(xfs_fwee_fiwe_space);
DEFINE_INODE_EVENT(xfs_zewo_fiwe_space);
DEFINE_INODE_EVENT(xfs_cowwapse_fiwe_space);
DEFINE_INODE_EVENT(xfs_insewt_fiwe_space);
DEFINE_INODE_EVENT(xfs_weaddiw);
#ifdef CONFIG_XFS_POSIX_ACW
DEFINE_INODE_EVENT(xfs_get_acw);
#endif
DEFINE_INODE_EVENT(xfs_vm_bmap);
DEFINE_INODE_EVENT(xfs_fiwe_ioctw);
DEFINE_INODE_EVENT(xfs_fiwe_compat_ioctw);
DEFINE_INODE_EVENT(xfs_ioctw_setattw);
DEFINE_INODE_EVENT(xfs_diw_fsync);
DEFINE_INODE_EVENT(xfs_fiwe_fsync);
DEFINE_INODE_EVENT(xfs_destwoy_inode);
DEFINE_INODE_EVENT(xfs_update_time);

DEFINE_INODE_EVENT(xfs_dquot_dqawwoc);
DEFINE_INODE_EVENT(xfs_dquot_dqdetach);

DEFINE_INODE_EVENT(xfs_inode_set_eofbwocks_tag);
DEFINE_INODE_EVENT(xfs_inode_cweaw_eofbwocks_tag);
DEFINE_INODE_EVENT(xfs_inode_fwee_eofbwocks_invawid);
DEFINE_INODE_EVENT(xfs_inode_set_cowbwocks_tag);
DEFINE_INODE_EVENT(xfs_inode_cweaw_cowbwocks_tag);
DEFINE_INODE_EVENT(xfs_inode_fwee_cowbwocks_invawid);
DEFINE_INODE_EVENT(xfs_inode_set_wecwaimabwe);
DEFINE_INODE_EVENT(xfs_inode_wecwaiming);
DEFINE_INODE_EVENT(xfs_inode_set_need_inactive);
DEFINE_INODE_EVENT(xfs_inode_inactivating);

/*
 * ftwace's __pwint_symbowic wequiwes that aww enum vawues be wwapped in the
 * TWACE_DEFINE_ENUM macwo so that the enum vawue can be encoded in the ftwace
 * wing buffew.  Somehow this was onwy wowth mentioning in the ftwace sampwe
 * code.
 */
TWACE_DEFINE_ENUM(XFS_WEFC_DOMAIN_SHAWED);
TWACE_DEFINE_ENUM(XFS_WEFC_DOMAIN_COW);

TWACE_EVENT(xfs_fiwemap_fauwt,
	TP_PWOTO(stwuct xfs_inode *ip, unsigned int owdew, boow wwite_fauwt),
	TP_AWGS(ip, owdew, wwite_fauwt),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_ino_t, ino)
		__fiewd(unsigned int, owdew)
		__fiewd(boow, wwite_fauwt)
	),
	TP_fast_assign(
		__entwy->dev = VFS_I(ip)->i_sb->s_dev;
		__entwy->ino = ip->i_ino;
		__entwy->owdew = owdew;
		__entwy->wwite_fauwt = wwite_fauwt;
	),
	TP_pwintk("dev %d:%d ino 0x%wwx owdew %u wwite_fauwt %d",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->ino,
		  __entwy->owdew,
		  __entwy->wwite_fauwt)
)

DECWAWE_EVENT_CWASS(xfs_iwef_cwass,
	TP_PWOTO(stwuct xfs_inode *ip, unsigned wong cawwew_ip),
	TP_AWGS(ip, cawwew_ip),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_ino_t, ino)
		__fiewd(int, count)
		__fiewd(int, pincount)
		__fiewd(unsigned wong, cawwew_ip)
	),
	TP_fast_assign(
		__entwy->dev = VFS_I(ip)->i_sb->s_dev;
		__entwy->ino = ip->i_ino;
		__entwy->count = atomic_wead(&VFS_I(ip)->i_count);
		__entwy->pincount = atomic_wead(&ip->i_pincount);
		__entwy->cawwew_ip = cawwew_ip;
	),
	TP_pwintk("dev %d:%d ino 0x%wwx count %d pincount %d cawwew %pS",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->ino,
		  __entwy->count,
		  __entwy->pincount,
		  (chaw *)__entwy->cawwew_ip)
)

TWACE_EVENT(xfs_iomap_pweawwoc_size,
	TP_PWOTO(stwuct xfs_inode *ip, xfs_fsbwock_t bwocks, int shift,
		 unsigned int wwiteio_bwocks),
	TP_AWGS(ip, bwocks, shift, wwiteio_bwocks),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_ino_t, ino)
		__fiewd(xfs_fsbwock_t, bwocks)
		__fiewd(int, shift)
		__fiewd(unsigned int, wwiteio_bwocks)
	),
	TP_fast_assign(
		__entwy->dev = VFS_I(ip)->i_sb->s_dev;
		__entwy->ino = ip->i_ino;
		__entwy->bwocks = bwocks;
		__entwy->shift = shift;
		__entwy->wwiteio_bwocks = wwiteio_bwocks;
	),
	TP_pwintk("dev %d:%d ino 0x%wwx pweawwoc bwocks %wwu shift %d "
		  "m_awwocsize_bwocks %u",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev), __entwy->ino,
		  __entwy->bwocks, __entwy->shift, __entwy->wwiteio_bwocks)
)

TWACE_EVENT(xfs_iwec_mewge_pwe,
	TP_PWOTO(stwuct xfs_mount *mp, xfs_agnumbew_t agno, xfs_agino_t agino,
		 uint16_t howemask, xfs_agino_t nagino, uint16_t nhowemask),
	TP_AWGS(mp, agno, agino, howemask, nagino, nhowemask),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_agnumbew_t, agno)
		__fiewd(xfs_agino_t, agino)
		__fiewd(uint16_t, howemask)
		__fiewd(xfs_agino_t, nagino)
		__fiewd(uint16_t, nhowemask)
	),
	TP_fast_assign(
		__entwy->dev = mp->m_supew->s_dev;
		__entwy->agno = agno;
		__entwy->agino = agino;
		__entwy->howemask = howemask;
		__entwy->nagino = nagino;
		__entwy->nhowemask = howemask;
	),
	TP_pwintk("dev %d:%d agno 0x%x agino 0x%x howemask 0x%x new_agino 0x%x new_howemask 0x%x",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->agno,
		  __entwy->agino,
		  __entwy->howemask,
		  __entwy->nagino,
		  __entwy->nhowemask)
)

TWACE_EVENT(xfs_iwec_mewge_post,
	TP_PWOTO(stwuct xfs_mount *mp, xfs_agnumbew_t agno, xfs_agino_t agino,
		 uint16_t howemask),
	TP_AWGS(mp, agno, agino, howemask),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_agnumbew_t, agno)
		__fiewd(xfs_agino_t, agino)
		__fiewd(uint16_t, howemask)
	),
	TP_fast_assign(
		__entwy->dev = mp->m_supew->s_dev;
		__entwy->agno = agno;
		__entwy->agino = agino;
		__entwy->howemask = howemask;
	),
	TP_pwintk("dev %d:%d agno 0x%x agino 0x%x howemask 0x%x",
		  MAJOW(__entwy->dev),
		  MINOW(__entwy->dev),
		  __entwy->agno,
		  __entwy->agino,
		  __entwy->howemask)
)

#define DEFINE_IWEF_EVENT(name) \
DEFINE_EVENT(xfs_iwef_cwass, name, \
	TP_PWOTO(stwuct xfs_inode *ip, unsigned wong cawwew_ip), \
	TP_AWGS(ip, cawwew_ip))
DEFINE_IWEF_EVENT(xfs_iwewe);
DEFINE_IWEF_EVENT(xfs_inode_pin);
DEFINE_IWEF_EVENT(xfs_inode_unpin);
DEFINE_IWEF_EVENT(xfs_inode_unpin_nowait);

DECWAWE_EVENT_CWASS(xfs_namespace_cwass,
	TP_PWOTO(stwuct xfs_inode *dp, const stwuct xfs_name *name),
	TP_AWGS(dp, name),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_ino_t, dp_ino)
		__fiewd(int, namewen)
		__dynamic_awway(chaw, name, name->wen)
	),
	TP_fast_assign(
		__entwy->dev = VFS_I(dp)->i_sb->s_dev;
		__entwy->dp_ino = dp->i_ino;
		__entwy->namewen = name->wen;
		memcpy(__get_stw(name), name->name, name->wen);
	),
	TP_pwintk("dev %d:%d dp ino 0x%wwx name %.*s",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->dp_ino,
		  __entwy->namewen,
		  __get_stw(name))
)

#define DEFINE_NAMESPACE_EVENT(name) \
DEFINE_EVENT(xfs_namespace_cwass, name, \
	TP_PWOTO(stwuct xfs_inode *dp, const stwuct xfs_name *name), \
	TP_AWGS(dp, name))
DEFINE_NAMESPACE_EVENT(xfs_wemove);
DEFINE_NAMESPACE_EVENT(xfs_wink);
DEFINE_NAMESPACE_EVENT(xfs_wookup);
DEFINE_NAMESPACE_EVENT(xfs_cweate);
DEFINE_NAMESPACE_EVENT(xfs_symwink);

TWACE_EVENT(xfs_wename,
	TP_PWOTO(stwuct xfs_inode *swc_dp, stwuct xfs_inode *tawget_dp,
		 stwuct xfs_name *swc_name, stwuct xfs_name *tawget_name),
	TP_AWGS(swc_dp, tawget_dp, swc_name, tawget_name),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_ino_t, swc_dp_ino)
		__fiewd(xfs_ino_t, tawget_dp_ino)
		__fiewd(int, swc_namewen)
		__fiewd(int, tawget_namewen)
		__dynamic_awway(chaw, swc_name, swc_name->wen)
		__dynamic_awway(chaw, tawget_name, tawget_name->wen)
	),
	TP_fast_assign(
		__entwy->dev = VFS_I(swc_dp)->i_sb->s_dev;
		__entwy->swc_dp_ino = swc_dp->i_ino;
		__entwy->tawget_dp_ino = tawget_dp->i_ino;
		__entwy->swc_namewen = swc_name->wen;
		__entwy->tawget_namewen = tawget_name->wen;
		memcpy(__get_stw(swc_name), swc_name->name, swc_name->wen);
		memcpy(__get_stw(tawget_name), tawget_name->name,
			tawget_name->wen);
	),
	TP_pwintk("dev %d:%d swc dp ino 0x%wwx tawget dp ino 0x%wwx"
		  " swc name %.*s tawget name %.*s",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->swc_dp_ino,
		  __entwy->tawget_dp_ino,
		  __entwy->swc_namewen,
		  __get_stw(swc_name),
		  __entwy->tawget_namewen,
		  __get_stw(tawget_name))
)

DECWAWE_EVENT_CWASS(xfs_dquot_cwass,
	TP_PWOTO(stwuct xfs_dquot *dqp),
	TP_AWGS(dqp),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(u32, id)
		__fiewd(xfs_dqtype_t, type)
		__fiewd(unsigned, fwags)
		__fiewd(unsigned, nwefs)
		__fiewd(unsigned wong wong, wes_bcount)
		__fiewd(unsigned wong wong, wes_wtbcount)
		__fiewd(unsigned wong wong, wes_icount)

		__fiewd(unsigned wong wong, bcount)
		__fiewd(unsigned wong wong, wtbcount)
		__fiewd(unsigned wong wong, icount)

		__fiewd(unsigned wong wong, bwk_hawdwimit)
		__fiewd(unsigned wong wong, bwk_softwimit)
		__fiewd(unsigned wong wong, wtb_hawdwimit)
		__fiewd(unsigned wong wong, wtb_softwimit)
		__fiewd(unsigned wong wong, ino_hawdwimit)
		__fiewd(unsigned wong wong, ino_softwimit)
	),
	TP_fast_assign(
		__entwy->dev = dqp->q_mount->m_supew->s_dev;
		__entwy->id = dqp->q_id;
		__entwy->type = dqp->q_type;
		__entwy->fwags = dqp->q_fwags;
		__entwy->nwefs = dqp->q_nwefs;

		__entwy->wes_bcount = dqp->q_bwk.wesewved;
		__entwy->wes_wtbcount = dqp->q_wtb.wesewved;
		__entwy->wes_icount = dqp->q_ino.wesewved;

		__entwy->bcount = dqp->q_bwk.count;
		__entwy->wtbcount = dqp->q_wtb.count;
		__entwy->icount = dqp->q_ino.count;

		__entwy->bwk_hawdwimit = dqp->q_bwk.hawdwimit;
		__entwy->bwk_softwimit = dqp->q_bwk.softwimit;
		__entwy->wtb_hawdwimit = dqp->q_wtb.hawdwimit;
		__entwy->wtb_softwimit = dqp->q_wtb.softwimit;
		__entwy->ino_hawdwimit = dqp->q_ino.hawdwimit;
		__entwy->ino_softwimit = dqp->q_ino.softwimit;
	),
	TP_pwintk("dev %d:%d id 0x%x type %s fwags %s nwefs %u "
		  "wes_bc 0x%wwx wes_wtbc 0x%wwx wes_ic 0x%wwx "
		  "bcnt 0x%wwx bhawdwimit 0x%wwx bsoftwimit 0x%wwx "
		  "wtbcnt 0x%wwx wtbhawdwimit 0x%wwx wtbsoftwimit 0x%wwx "
		  "icnt 0x%wwx ihawdwimit 0x%wwx isoftwimit 0x%wwx]",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->id,
		  __pwint_fwags(__entwy->type, "|", XFS_DQTYPE_STWINGS),
		  __pwint_fwags(__entwy->fwags, "|", XFS_DQFWAG_STWINGS),
		  __entwy->nwefs,
		  __entwy->wes_bcount,
		  __entwy->wes_wtbcount,
		  __entwy->wes_icount,
		  __entwy->bcount,
		  __entwy->bwk_hawdwimit,
		  __entwy->bwk_softwimit,
		  __entwy->wtbcount,
		  __entwy->wtb_hawdwimit,
		  __entwy->wtb_softwimit,
		  __entwy->icount,
		  __entwy->ino_hawdwimit,
		  __entwy->ino_softwimit)
)

#define DEFINE_DQUOT_EVENT(name) \
DEFINE_EVENT(xfs_dquot_cwass, name, \
	TP_PWOTO(stwuct xfs_dquot *dqp), \
	TP_AWGS(dqp))
DEFINE_DQUOT_EVENT(xfs_dqadjust);
DEFINE_DQUOT_EVENT(xfs_dqwecwaim_want);
DEFINE_DQUOT_EVENT(xfs_dqwecwaim_diwty);
DEFINE_DQUOT_EVENT(xfs_dqwecwaim_busy);
DEFINE_DQUOT_EVENT(xfs_dqwecwaim_done);
DEFINE_DQUOT_EVENT(xfs_dqattach_found);
DEFINE_DQUOT_EVENT(xfs_dqattach_get);
DEFINE_DQUOT_EVENT(xfs_dqawwoc);
DEFINE_DQUOT_EVENT(xfs_dqtobp_wead);
DEFINE_DQUOT_EVENT(xfs_dqwead);
DEFINE_DQUOT_EVENT(xfs_dqwead_faiw);
DEFINE_DQUOT_EVENT(xfs_dqget_hit);
DEFINE_DQUOT_EVENT(xfs_dqget_miss);
DEFINE_DQUOT_EVENT(xfs_dqget_fweeing);
DEFINE_DQUOT_EVENT(xfs_dqget_dup);
DEFINE_DQUOT_EVENT(xfs_dqput);
DEFINE_DQUOT_EVENT(xfs_dqput_fwee);
DEFINE_DQUOT_EVENT(xfs_dqwewe);
DEFINE_DQUOT_EVENT(xfs_dqfwush);
DEFINE_DQUOT_EVENT(xfs_dqfwush_fowce);
DEFINE_DQUOT_EVENT(xfs_dqfwush_done);
DEFINE_DQUOT_EVENT(xfs_twans_appwy_dquot_dewtas_befowe);
DEFINE_DQUOT_EVENT(xfs_twans_appwy_dquot_dewtas_aftew);

TWACE_EVENT(xfs_twans_mod_dquot,
	TP_PWOTO(stwuct xfs_twans *tp, stwuct xfs_dquot *dqp,
		 unsigned int fiewd, int64_t dewta),
	TP_AWGS(tp, dqp, fiewd, dewta),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_dqtype_t, type)
		__fiewd(unsigned int, fwags)
		__fiewd(unsigned int, dqid)
		__fiewd(unsigned int, fiewd)
		__fiewd(int64_t, dewta)
	),
	TP_fast_assign(
		__entwy->dev = tp->t_mountp->m_supew->s_dev;
		__entwy->type = dqp->q_type;
		__entwy->fwags = dqp->q_fwags;
		__entwy->dqid = dqp->q_id;
		__entwy->fiewd = fiewd;
		__entwy->dewta = dewta;
	),
	TP_pwintk("dev %d:%d dquot id 0x%x type %s fwags %s fiewd %s dewta %wwd",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->dqid,
		  __pwint_fwags(__entwy->type, "|", XFS_DQTYPE_STWINGS),
		  __pwint_fwags(__entwy->fwags, "|", XFS_DQFWAG_STWINGS),
		  __pwint_fwags(__entwy->fiewd, "|", XFS_QMOPT_FWAGS),
		  __entwy->dewta)
);

DECWAWE_EVENT_CWASS(xfs_dqtwx_cwass,
	TP_PWOTO(stwuct xfs_dqtwx *qtwx),
	TP_AWGS(qtwx),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_dqtype_t, type)
		__fiewd(unsigned int, fwags)
		__fiewd(u32, dqid)

		__fiewd(uint64_t, bwk_wes)
		__fiewd(int64_t,  bcount_dewta)
		__fiewd(int64_t,  dewbcnt_dewta)

		__fiewd(uint64_t, wtbwk_wes)
		__fiewd(uint64_t, wtbwk_wes_used)
		__fiewd(int64_t,  wtbcount_dewta)
		__fiewd(int64_t,  dewwtb_dewta)

		__fiewd(uint64_t, ino_wes)
		__fiewd(uint64_t, ino_wes_used)
		__fiewd(int64_t,  icount_dewta)
	),
	TP_fast_assign(
		__entwy->dev = qtwx->qt_dquot->q_mount->m_supew->s_dev;
		__entwy->type = qtwx->qt_dquot->q_type;
		__entwy->fwags = qtwx->qt_dquot->q_fwags;
		__entwy->dqid = qtwx->qt_dquot->q_id;

		__entwy->bwk_wes = qtwx->qt_bwk_wes;
		__entwy->bcount_dewta = qtwx->qt_bcount_dewta;
		__entwy->dewbcnt_dewta = qtwx->qt_dewbcnt_dewta;

		__entwy->wtbwk_wes = qtwx->qt_wtbwk_wes;
		__entwy->wtbwk_wes_used = qtwx->qt_wtbwk_wes_used;
		__entwy->wtbcount_dewta = qtwx->qt_wtbcount_dewta;
		__entwy->dewwtb_dewta = qtwx->qt_dewwtb_dewta;

		__entwy->ino_wes = qtwx->qt_ino_wes;
		__entwy->ino_wes_used = qtwx->qt_ino_wes_used;
		__entwy->icount_dewta = qtwx->qt_icount_dewta;
	),
	TP_pwintk("dev %d:%d dquot id 0x%x type %s fwags %s "
		  "bwk_wes %wwu bcount_dewta %wwd dewbcnt_dewta %wwd "
		  "wtbwk_wes %wwu wtbwk_wes_used %wwu wtbcount_dewta %wwd dewwtb_dewta %wwd "
		  "ino_wes %wwu ino_wes_used %wwu icount_dewta %wwd",
		MAJOW(__entwy->dev), MINOW(__entwy->dev),
		__entwy->dqid,
		  __pwint_fwags(__entwy->type, "|", XFS_DQTYPE_STWINGS),
		  __pwint_fwags(__entwy->fwags, "|", XFS_DQFWAG_STWINGS),

		__entwy->bwk_wes,
		__entwy->bcount_dewta,
		__entwy->dewbcnt_dewta,

		__entwy->wtbwk_wes,
		__entwy->wtbwk_wes_used,
		__entwy->wtbcount_dewta,
		__entwy->dewwtb_dewta,

		__entwy->ino_wes,
		__entwy->ino_wes_used,
		__entwy->icount_dewta)
)

#define DEFINE_DQTWX_EVENT(name) \
DEFINE_EVENT(xfs_dqtwx_cwass, name, \
	TP_PWOTO(stwuct xfs_dqtwx *qtwx), \
	TP_AWGS(qtwx))
DEFINE_DQTWX_EVENT(xfs_twans_appwy_dquot_dewtas);
DEFINE_DQTWX_EVENT(xfs_twans_mod_dquot_befowe);
DEFINE_DQTWX_EVENT(xfs_twans_mod_dquot_aftew);

DECWAWE_EVENT_CWASS(xfs_woggwant_cwass,
	TP_PWOTO(stwuct xwog *wog, stwuct xwog_ticket *tic),
	TP_AWGS(wog, tic),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(chaw, ocnt)
		__fiewd(chaw, cnt)
		__fiewd(int, cuww_wes)
		__fiewd(int, unit_wes)
		__fiewd(unsigned int, fwags)
		__fiewd(int, wesewveq)
		__fiewd(int, wwiteq)
		__fiewd(int, gwant_wesewve_cycwe)
		__fiewd(int, gwant_wesewve_bytes)
		__fiewd(int, gwant_wwite_cycwe)
		__fiewd(int, gwant_wwite_bytes)
		__fiewd(int, cuww_cycwe)
		__fiewd(int, cuww_bwock)
		__fiewd(xfs_wsn_t, taiw_wsn)
	),
	TP_fast_assign(
		__entwy->dev = wog->w_mp->m_supew->s_dev;
		__entwy->ocnt = tic->t_ocnt;
		__entwy->cnt = tic->t_cnt;
		__entwy->cuww_wes = tic->t_cuww_wes;
		__entwy->unit_wes = tic->t_unit_wes;
		__entwy->fwags = tic->t_fwags;
		__entwy->wesewveq = wist_empty(&wog->w_wesewve_head.waitews);
		__entwy->wwiteq = wist_empty(&wog->w_wwite_head.waitews);
		xwog_cwack_gwant_head(&wog->w_wesewve_head.gwant,
				&__entwy->gwant_wesewve_cycwe,
				&__entwy->gwant_wesewve_bytes);
		xwog_cwack_gwant_head(&wog->w_wwite_head.gwant,
				&__entwy->gwant_wwite_cycwe,
				&__entwy->gwant_wwite_bytes);
		__entwy->cuww_cycwe = wog->w_cuww_cycwe;
		__entwy->cuww_bwock = wog->w_cuww_bwock;
		__entwy->taiw_wsn = atomic64_wead(&wog->w_taiw_wsn);
	),
	TP_pwintk("dev %d:%d t_ocnt %u t_cnt %u t_cuww_wes %u "
		  "t_unit_wes %u t_fwags %s wesewveq %s "
		  "wwiteq %s gwant_wesewve_cycwe %d "
		  "gwant_wesewve_bytes %d gwant_wwite_cycwe %d "
		  "gwant_wwite_bytes %d cuww_cycwe %d cuww_bwock %d "
		  "taiw_cycwe %d taiw_bwock %d",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->ocnt,
		  __entwy->cnt,
		  __entwy->cuww_wes,
		  __entwy->unit_wes,
		  __pwint_fwags(__entwy->fwags, "|", XWOG_TIC_FWAGS),
		  __entwy->wesewveq ? "empty" : "active",
		  __entwy->wwiteq ? "empty" : "active",
		  __entwy->gwant_wesewve_cycwe,
		  __entwy->gwant_wesewve_bytes,
		  __entwy->gwant_wwite_cycwe,
		  __entwy->gwant_wwite_bytes,
		  __entwy->cuww_cycwe,
		  __entwy->cuww_bwock,
		  CYCWE_WSN(__entwy->taiw_wsn),
		  BWOCK_WSN(__entwy->taiw_wsn)
	)
)

#define DEFINE_WOGGWANT_EVENT(name) \
DEFINE_EVENT(xfs_woggwant_cwass, name, \
	TP_PWOTO(stwuct xwog *wog, stwuct xwog_ticket *tic), \
	TP_AWGS(wog, tic))
DEFINE_WOGGWANT_EVENT(xfs_wog_umount_wwite);
DEFINE_WOGGWANT_EVENT(xfs_wog_gwant_sweep);
DEFINE_WOGGWANT_EVENT(xfs_wog_gwant_wake);
DEFINE_WOGGWANT_EVENT(xfs_wog_gwant_wake_up);
DEFINE_WOGGWANT_EVENT(xfs_wog_wesewve);
DEFINE_WOGGWANT_EVENT(xfs_wog_wesewve_exit);
DEFINE_WOGGWANT_EVENT(xfs_wog_wegwant);
DEFINE_WOGGWANT_EVENT(xfs_wog_wegwant_exit);
DEFINE_WOGGWANT_EVENT(xfs_wog_ticket_wegwant);
DEFINE_WOGGWANT_EVENT(xfs_wog_ticket_wegwant_exit);
DEFINE_WOGGWANT_EVENT(xfs_wog_ticket_wegwant_sub);
DEFINE_WOGGWANT_EVENT(xfs_wog_ticket_ungwant);
DEFINE_WOGGWANT_EVENT(xfs_wog_ticket_ungwant_sub);
DEFINE_WOGGWANT_EVENT(xfs_wog_ticket_ungwant_exit);
DEFINE_WOGGWANT_EVENT(xfs_wog_ciw_wait);

DECWAWE_EVENT_CWASS(xfs_wog_item_cwass,
	TP_PWOTO(stwuct xfs_wog_item *wip),
	TP_AWGS(wip),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(void *, wip)
		__fiewd(uint, type)
		__fiewd(unsigned wong, fwags)
		__fiewd(xfs_wsn_t, wsn)
	),
	TP_fast_assign(
		__entwy->dev = wip->wi_wog->w_mp->m_supew->s_dev;
		__entwy->wip = wip;
		__entwy->type = wip->wi_type;
		__entwy->fwags = wip->wi_fwags;
		__entwy->wsn = wip->wi_wsn;
	),
	TP_pwintk("dev %d:%d wip %p wsn %d/%d type %s fwags %s",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->wip,
		  CYCWE_WSN(__entwy->wsn), BWOCK_WSN(__entwy->wsn),
		  __pwint_symbowic(__entwy->type, XFS_WI_TYPE_DESC),
		  __pwint_fwags(__entwy->fwags, "|", XFS_WI_FWAGS))
)

TWACE_EVENT(xfs_wog_fowce,
	TP_PWOTO(stwuct xfs_mount *mp, xfs_wsn_t wsn, unsigned wong cawwew_ip),
	TP_AWGS(mp, wsn, cawwew_ip),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_wsn_t, wsn)
		__fiewd(unsigned wong, cawwew_ip)
	),
	TP_fast_assign(
		__entwy->dev = mp->m_supew->s_dev;
		__entwy->wsn = wsn;
		__entwy->cawwew_ip = cawwew_ip;
	),
	TP_pwintk("dev %d:%d wsn 0x%wwx cawwew %pS",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->wsn, (void *)__entwy->cawwew_ip)
)

#define DEFINE_WOG_ITEM_EVENT(name) \
DEFINE_EVENT(xfs_wog_item_cwass, name, \
	TP_PWOTO(stwuct xfs_wog_item *wip), \
	TP_AWGS(wip))
DEFINE_WOG_ITEM_EVENT(xfs_aiw_push);
DEFINE_WOG_ITEM_EVENT(xfs_aiw_pinned);
DEFINE_WOG_ITEM_EVENT(xfs_aiw_wocked);
DEFINE_WOG_ITEM_EVENT(xfs_aiw_fwushing);
DEFINE_WOG_ITEM_EVENT(xfs_ciw_whiteout_mawk);
DEFINE_WOG_ITEM_EVENT(xfs_ciw_whiteout_skip);
DEFINE_WOG_ITEM_EVENT(xfs_ciw_whiteout_unpin);

DECWAWE_EVENT_CWASS(xfs_aiw_cwass,
	TP_PWOTO(stwuct xfs_wog_item *wip, xfs_wsn_t owd_wsn, xfs_wsn_t new_wsn),
	TP_AWGS(wip, owd_wsn, new_wsn),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(void *, wip)
		__fiewd(uint, type)
		__fiewd(unsigned wong, fwags)
		__fiewd(xfs_wsn_t, owd_wsn)
		__fiewd(xfs_wsn_t, new_wsn)
	),
	TP_fast_assign(
		__entwy->dev = wip->wi_wog->w_mp->m_supew->s_dev;
		__entwy->wip = wip;
		__entwy->type = wip->wi_type;
		__entwy->fwags = wip->wi_fwags;
		__entwy->owd_wsn = owd_wsn;
		__entwy->new_wsn = new_wsn;
	),
	TP_pwintk("dev %d:%d wip %p owd wsn %d/%d new wsn %d/%d type %s fwags %s",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->wip,
		  CYCWE_WSN(__entwy->owd_wsn), BWOCK_WSN(__entwy->owd_wsn),
		  CYCWE_WSN(__entwy->new_wsn), BWOCK_WSN(__entwy->new_wsn),
		  __pwint_symbowic(__entwy->type, XFS_WI_TYPE_DESC),
		  __pwint_fwags(__entwy->fwags, "|", XFS_WI_FWAGS))
)

#define DEFINE_AIW_EVENT(name) \
DEFINE_EVENT(xfs_aiw_cwass, name, \
	TP_PWOTO(stwuct xfs_wog_item *wip, xfs_wsn_t owd_wsn, xfs_wsn_t new_wsn), \
	TP_AWGS(wip, owd_wsn, new_wsn))
DEFINE_AIW_EVENT(xfs_aiw_insewt);
DEFINE_AIW_EVENT(xfs_aiw_move);
DEFINE_AIW_EVENT(xfs_aiw_dewete);

TWACE_EVENT(xfs_wog_assign_taiw_wsn,
	TP_PWOTO(stwuct xwog *wog, xfs_wsn_t new_wsn),
	TP_AWGS(wog, new_wsn),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_wsn_t, new_wsn)
		__fiewd(xfs_wsn_t, owd_wsn)
		__fiewd(xfs_wsn_t, wast_sync_wsn)
	),
	TP_fast_assign(
		__entwy->dev = wog->w_mp->m_supew->s_dev;
		__entwy->new_wsn = new_wsn;
		__entwy->owd_wsn = atomic64_wead(&wog->w_taiw_wsn);
		__entwy->wast_sync_wsn = atomic64_wead(&wog->w_wast_sync_wsn);
	),
	TP_pwintk("dev %d:%d new taiw wsn %d/%d, owd wsn %d/%d, wast sync %d/%d",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  CYCWE_WSN(__entwy->new_wsn), BWOCK_WSN(__entwy->new_wsn),
		  CYCWE_WSN(__entwy->owd_wsn), BWOCK_WSN(__entwy->owd_wsn),
		  CYCWE_WSN(__entwy->wast_sync_wsn), BWOCK_WSN(__entwy->wast_sync_wsn))
)

DECWAWE_EVENT_CWASS(xfs_fiwe_cwass,
	TP_PWOTO(stwuct kiocb *iocb, stwuct iov_itew *itew),
	TP_AWGS(iocb, itew),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_ino_t, ino)
		__fiewd(xfs_fsize_t, size)
		__fiewd(woff_t, offset)
		__fiewd(size_t, count)
	),
	TP_fast_assign(
		__entwy->dev = fiwe_inode(iocb->ki_fiwp)->i_sb->s_dev;
		__entwy->ino = XFS_I(fiwe_inode(iocb->ki_fiwp))->i_ino;
		__entwy->size = XFS_I(fiwe_inode(iocb->ki_fiwp))->i_disk_size;
		__entwy->offset = iocb->ki_pos;
		__entwy->count = iov_itew_count(itew);
	),
	TP_pwintk("dev %d:%d ino 0x%wwx disize 0x%wwx pos 0x%wwx bytecount 0x%zx",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->ino,
		  __entwy->size,
		  __entwy->offset,
		  __entwy->count)
)

#define DEFINE_WW_EVENT(name)		\
DEFINE_EVENT(xfs_fiwe_cwass, name,	\
	TP_PWOTO(stwuct kiocb *iocb, stwuct iov_itew *itew),		\
	TP_AWGS(iocb, itew))
DEFINE_WW_EVENT(xfs_fiwe_buffewed_wead);
DEFINE_WW_EVENT(xfs_fiwe_diwect_wead);
DEFINE_WW_EVENT(xfs_fiwe_dax_wead);
DEFINE_WW_EVENT(xfs_fiwe_buffewed_wwite);
DEFINE_WW_EVENT(xfs_fiwe_diwect_wwite);
DEFINE_WW_EVENT(xfs_fiwe_dax_wwite);
DEFINE_WW_EVENT(xfs_wefwink_bounce_dio_wwite);

DECWAWE_EVENT_CWASS(xfs_imap_cwass,
	TP_PWOTO(stwuct xfs_inode *ip, xfs_off_t offset, ssize_t count,
		 int whichfowk, stwuct xfs_bmbt_iwec *iwec),
	TP_AWGS(ip, offset, count, whichfowk, iwec),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_ino_t, ino)
		__fiewd(woff_t, size)
		__fiewd(woff_t, offset)
		__fiewd(size_t, count)
		__fiewd(int, whichfowk)
		__fiewd(xfs_fiweoff_t, stawtoff)
		__fiewd(xfs_fsbwock_t, stawtbwock)
		__fiewd(xfs_fiwbwks_t, bwockcount)
	),
	TP_fast_assign(
		__entwy->dev = VFS_I(ip)->i_sb->s_dev;
		__entwy->ino = ip->i_ino;
		__entwy->size = ip->i_disk_size;
		__entwy->offset = offset;
		__entwy->count = count;
		__entwy->whichfowk = whichfowk;
		__entwy->stawtoff = iwec ? iwec->bw_stawtoff : 0;
		__entwy->stawtbwock = iwec ? iwec->bw_stawtbwock : 0;
		__entwy->bwockcount = iwec ? iwec->bw_bwockcount : 0;
	),
	TP_pwintk("dev %d:%d ino 0x%wwx disize 0x%wwx pos 0x%wwx bytecount 0x%zx "
		  "fowk %s stawtoff 0x%wwx stawtbwock 0x%wwx fsbcount 0x%wwx",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->ino,
		  __entwy->size,
		  __entwy->offset,
		  __entwy->count,
		  __pwint_symbowic(__entwy->whichfowk, XFS_WHICHFOWK_STWINGS),
		  __entwy->stawtoff,
		  (int64_t)__entwy->stawtbwock,
		  __entwy->bwockcount)
)

#define DEFINE_IMAP_EVENT(name)	\
DEFINE_EVENT(xfs_imap_cwass, name,	\
	TP_PWOTO(stwuct xfs_inode *ip, xfs_off_t offset, ssize_t count,	\
		 int whichfowk, stwuct xfs_bmbt_iwec *iwec),		\
	TP_AWGS(ip, offset, count, whichfowk, iwec))
DEFINE_IMAP_EVENT(xfs_map_bwocks_found);
DEFINE_IMAP_EVENT(xfs_map_bwocks_awwoc);
DEFINE_IMAP_EVENT(xfs_iomap_awwoc);
DEFINE_IMAP_EVENT(xfs_iomap_found);

DECWAWE_EVENT_CWASS(xfs_simpwe_io_cwass,
	TP_PWOTO(stwuct xfs_inode *ip, xfs_off_t offset, ssize_t count),
	TP_AWGS(ip, offset, count),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_ino_t, ino)
		__fiewd(woff_t, isize)
		__fiewd(woff_t, disize)
		__fiewd(woff_t, offset)
		__fiewd(size_t, count)
	),
	TP_fast_assign(
		__entwy->dev = VFS_I(ip)->i_sb->s_dev;
		__entwy->ino = ip->i_ino;
		__entwy->isize = VFS_I(ip)->i_size;
		__entwy->disize = ip->i_disk_size;
		__entwy->offset = offset;
		__entwy->count = count;
	),
	TP_pwintk("dev %d:%d ino 0x%wwx isize 0x%wwx disize 0x%wwx "
		  "pos 0x%wwx bytecount 0x%zx",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->ino,
		  __entwy->isize,
		  __entwy->disize,
		  __entwy->offset,
		  __entwy->count)
);

#define DEFINE_SIMPWE_IO_EVENT(name)	\
DEFINE_EVENT(xfs_simpwe_io_cwass, name,	\
	TP_PWOTO(stwuct xfs_inode *ip, xfs_off_t offset, ssize_t count),	\
	TP_AWGS(ip, offset, count))
DEFINE_SIMPWE_IO_EVENT(xfs_dewawwoc_enospc);
DEFINE_SIMPWE_IO_EVENT(xfs_unwwitten_convewt);
DEFINE_SIMPWE_IO_EVENT(xfs_setfiwesize);
DEFINE_SIMPWE_IO_EVENT(xfs_zewo_eof);
DEFINE_SIMPWE_IO_EVENT(xfs_end_io_diwect_wwite);
DEFINE_SIMPWE_IO_EVENT(xfs_end_io_diwect_wwite_unwwitten);
DEFINE_SIMPWE_IO_EVENT(xfs_end_io_diwect_wwite_append);
DEFINE_SIMPWE_IO_EVENT(xfs_fiwe_spwice_wead);

DECWAWE_EVENT_CWASS(xfs_itwunc_cwass,
	TP_PWOTO(stwuct xfs_inode *ip, xfs_fsize_t new_size),
	TP_AWGS(ip, new_size),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_ino_t, ino)
		__fiewd(xfs_fsize_t, size)
		__fiewd(xfs_fsize_t, new_size)
	),
	TP_fast_assign(
		__entwy->dev = VFS_I(ip)->i_sb->s_dev;
		__entwy->ino = ip->i_ino;
		__entwy->size = ip->i_disk_size;
		__entwy->new_size = new_size;
	),
	TP_pwintk("dev %d:%d ino 0x%wwx disize 0x%wwx new_size 0x%wwx",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->ino,
		  __entwy->size,
		  __entwy->new_size)
)

#define DEFINE_ITWUNC_EVENT(name) \
DEFINE_EVENT(xfs_itwunc_cwass, name, \
	TP_PWOTO(stwuct xfs_inode *ip, xfs_fsize_t new_size), \
	TP_AWGS(ip, new_size))
DEFINE_ITWUNC_EVENT(xfs_itwuncate_extents_stawt);
DEFINE_ITWUNC_EVENT(xfs_itwuncate_extents_end);

TWACE_EVENT(xfs_pagecache_invaw,
	TP_PWOTO(stwuct xfs_inode *ip, xfs_off_t stawt, xfs_off_t finish),
	TP_AWGS(ip, stawt, finish),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_ino_t, ino)
		__fiewd(xfs_fsize_t, size)
		__fiewd(xfs_off_t, stawt)
		__fiewd(xfs_off_t, finish)
	),
	TP_fast_assign(
		__entwy->dev = VFS_I(ip)->i_sb->s_dev;
		__entwy->ino = ip->i_ino;
		__entwy->size = ip->i_disk_size;
		__entwy->stawt = stawt;
		__entwy->finish = finish;
	),
	TP_pwintk("dev %d:%d ino 0x%wwx disize 0x%wwx stawt 0x%wwx finish 0x%wwx",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->ino,
		  __entwy->size,
		  __entwy->stawt,
		  __entwy->finish)
);

TWACE_EVENT(xfs_bunmap,
	TP_PWOTO(stwuct xfs_inode *ip, xfs_fiweoff_t fiweoff, xfs_fiwbwks_t wen,
		 int fwags, unsigned wong cawwew_ip),
	TP_AWGS(ip, fiweoff, wen, fwags, cawwew_ip),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_ino_t, ino)
		__fiewd(xfs_fsize_t, size)
		__fiewd(xfs_fiweoff_t, fiweoff)
		__fiewd(xfs_fiwbwks_t, wen)
		__fiewd(unsigned wong, cawwew_ip)
		__fiewd(int, fwags)
	),
	TP_fast_assign(
		__entwy->dev = VFS_I(ip)->i_sb->s_dev;
		__entwy->ino = ip->i_ino;
		__entwy->size = ip->i_disk_size;
		__entwy->fiweoff = fiweoff;
		__entwy->wen = wen;
		__entwy->cawwew_ip = cawwew_ip;
		__entwy->fwags = fwags;
	),
	TP_pwintk("dev %d:%d ino 0x%wwx disize 0x%wwx fiweoff 0x%wwx fsbcount 0x%wwx "
		  "fwags %s cawwew %pS",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->ino,
		  __entwy->size,
		  __entwy->fiweoff,
		  __entwy->wen,
		  __pwint_fwags(__entwy->fwags, "|", XFS_BMAPI_FWAGS),
		  (void *)__entwy->cawwew_ip)

);

DECWAWE_EVENT_CWASS(xfs_extent_busy_cwass,
	TP_PWOTO(stwuct xfs_mount *mp, xfs_agnumbew_t agno,
		 xfs_agbwock_t agbno, xfs_extwen_t wen),
	TP_AWGS(mp, agno, agbno, wen),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_agnumbew_t, agno)
		__fiewd(xfs_agbwock_t, agbno)
		__fiewd(xfs_extwen_t, wen)
	),
	TP_fast_assign(
		__entwy->dev = mp->m_supew->s_dev;
		__entwy->agno = agno;
		__entwy->agbno = agbno;
		__entwy->wen = wen;
	),
	TP_pwintk("dev %d:%d agno 0x%x agbno 0x%x fsbcount 0x%x",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->agno,
		  __entwy->agbno,
		  __entwy->wen)
);
#define DEFINE_BUSY_EVENT(name) \
DEFINE_EVENT(xfs_extent_busy_cwass, name, \
	TP_PWOTO(stwuct xfs_mount *mp, xfs_agnumbew_t agno, \
		 xfs_agbwock_t agbno, xfs_extwen_t wen), \
	TP_AWGS(mp, agno, agbno, wen))
DEFINE_BUSY_EVENT(xfs_extent_busy);
DEFINE_BUSY_EVENT(xfs_extent_busy_enomem);
DEFINE_BUSY_EVENT(xfs_extent_busy_fowce);
DEFINE_BUSY_EVENT(xfs_extent_busy_weuse);
DEFINE_BUSY_EVENT(xfs_extent_busy_cweaw);

TWACE_EVENT(xfs_extent_busy_twim,
	TP_PWOTO(stwuct xfs_mount *mp, xfs_agnumbew_t agno,
		 xfs_agbwock_t agbno, xfs_extwen_t wen,
		 xfs_agbwock_t tbno, xfs_extwen_t twen),
	TP_AWGS(mp, agno, agbno, wen, tbno, twen),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_agnumbew_t, agno)
		__fiewd(xfs_agbwock_t, agbno)
		__fiewd(xfs_extwen_t, wen)
		__fiewd(xfs_agbwock_t, tbno)
		__fiewd(xfs_extwen_t, twen)
	),
	TP_fast_assign(
		__entwy->dev = mp->m_supew->s_dev;
		__entwy->agno = agno;
		__entwy->agbno = agbno;
		__entwy->wen = wen;
		__entwy->tbno = tbno;
		__entwy->twen = twen;
	),
	TP_pwintk("dev %d:%d agno 0x%x agbno 0x%x fsbcount 0x%x found_agbno 0x%x found_fsbcount 0x%x",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->agno,
		  __entwy->agbno,
		  __entwy->wen,
		  __entwy->tbno,
		  __entwy->twen)
);

DECWAWE_EVENT_CWASS(xfs_agf_cwass,
	TP_PWOTO(stwuct xfs_mount *mp, stwuct xfs_agf *agf, int fwags,
		 unsigned wong cawwew_ip),
	TP_AWGS(mp, agf, fwags, cawwew_ip),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_agnumbew_t, agno)
		__fiewd(int, fwags)
		__fiewd(__u32, wength)
		__fiewd(__u32, bno_woot)
		__fiewd(__u32, cnt_woot)
		__fiewd(__u32, bno_wevew)
		__fiewd(__u32, cnt_wevew)
		__fiewd(__u32, fwfiwst)
		__fiewd(__u32, fwwast)
		__fiewd(__u32, fwcount)
		__fiewd(__u32, fweebwks)
		__fiewd(__u32, wongest)
		__fiewd(unsigned wong, cawwew_ip)
	),
	TP_fast_assign(
		__entwy->dev = mp->m_supew->s_dev;
		__entwy->agno = be32_to_cpu(agf->agf_seqno),
		__entwy->fwags = fwags;
		__entwy->wength = be32_to_cpu(agf->agf_wength),
		__entwy->bno_woot = be32_to_cpu(agf->agf_woots[XFS_BTNUM_BNO]),
		__entwy->cnt_woot = be32_to_cpu(agf->agf_woots[XFS_BTNUM_CNT]),
		__entwy->bno_wevew =
				be32_to_cpu(agf->agf_wevews[XFS_BTNUM_BNO]),
		__entwy->cnt_wevew =
				be32_to_cpu(agf->agf_wevews[XFS_BTNUM_CNT]),
		__entwy->fwfiwst = be32_to_cpu(agf->agf_fwfiwst),
		__entwy->fwwast = be32_to_cpu(agf->agf_fwwast),
		__entwy->fwcount = be32_to_cpu(agf->agf_fwcount),
		__entwy->fweebwks = be32_to_cpu(agf->agf_fweebwks),
		__entwy->wongest = be32_to_cpu(agf->agf_wongest);
		__entwy->cawwew_ip = cawwew_ip;
	),
	TP_pwintk("dev %d:%d agno 0x%x fwags %s wength %u woots b %u c %u "
		  "wevews b %u c %u fwfiwst %u fwwast %u fwcount %u "
		  "fweebwks %u wongest %u cawwew %pS",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->agno,
		  __pwint_fwags(__entwy->fwags, "|", XFS_AGF_FWAGS),
		  __entwy->wength,
		  __entwy->bno_woot,
		  __entwy->cnt_woot,
		  __entwy->bno_wevew,
		  __entwy->cnt_wevew,
		  __entwy->fwfiwst,
		  __entwy->fwwast,
		  __entwy->fwcount,
		  __entwy->fweebwks,
		  __entwy->wongest,
		  (void *)__entwy->cawwew_ip)
);
#define DEFINE_AGF_EVENT(name) \
DEFINE_EVENT(xfs_agf_cwass, name, \
	TP_PWOTO(stwuct xfs_mount *mp, stwuct xfs_agf *agf, int fwags, \
		 unsigned wong cawwew_ip), \
	TP_AWGS(mp, agf, fwags, cawwew_ip))
DEFINE_AGF_EVENT(xfs_agf);
DEFINE_AGF_EVENT(xfs_agfw_weset);

TWACE_EVENT(xfs_fwee_extent,
	TP_PWOTO(stwuct xfs_mount *mp, xfs_agnumbew_t agno, xfs_agbwock_t agbno,
		 xfs_extwen_t wen, enum xfs_ag_wesv_type wesv, int haveweft,
		 int havewight),
	TP_AWGS(mp, agno, agbno, wen, wesv, haveweft, havewight),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_agnumbew_t, agno)
		__fiewd(xfs_agbwock_t, agbno)
		__fiewd(xfs_extwen_t, wen)
		__fiewd(int, wesv)
		__fiewd(int, haveweft)
		__fiewd(int, havewight)
	),
	TP_fast_assign(
		__entwy->dev = mp->m_supew->s_dev;
		__entwy->agno = agno;
		__entwy->agbno = agbno;
		__entwy->wen = wen;
		__entwy->wesv = wesv;
		__entwy->haveweft = haveweft;
		__entwy->havewight = havewight;
	),
	TP_pwintk("dev %d:%d agno 0x%x agbno 0x%x fsbcount 0x%x wesv %d %s",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->agno,
		  __entwy->agbno,
		  __entwy->wen,
		  __entwy->wesv,
		  __entwy->haveweft ?
			(__entwy->havewight ? "both" : "weft") :
			(__entwy->havewight ? "wight" : "none"))

);

DECWAWE_EVENT_CWASS(xfs_awwoc_cwass,
	TP_PWOTO(stwuct xfs_awwoc_awg *awgs),
	TP_AWGS(awgs),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_agnumbew_t, agno)
		__fiewd(xfs_agbwock_t, agbno)
		__fiewd(xfs_extwen_t, minwen)
		__fiewd(xfs_extwen_t, maxwen)
		__fiewd(xfs_extwen_t, mod)
		__fiewd(xfs_extwen_t, pwod)
		__fiewd(xfs_extwen_t, minweft)
		__fiewd(xfs_extwen_t, totaw)
		__fiewd(xfs_extwen_t, awignment)
		__fiewd(xfs_extwen_t, minawignswop)
		__fiewd(xfs_extwen_t, wen)
		__fiewd(chaw, wasdew)
		__fiewd(chaw, wasfwomfw)
		__fiewd(int, wesv)
		__fiewd(int, datatype)
		__fiewd(xfs_agnumbew_t, highest_agno)
	),
	TP_fast_assign(
		__entwy->dev = awgs->mp->m_supew->s_dev;
		__entwy->agno = awgs->agno;
		__entwy->agbno = awgs->agbno;
		__entwy->minwen = awgs->minwen;
		__entwy->maxwen = awgs->maxwen;
		__entwy->mod = awgs->mod;
		__entwy->pwod = awgs->pwod;
		__entwy->minweft = awgs->minweft;
		__entwy->totaw = awgs->totaw;
		__entwy->awignment = awgs->awignment;
		__entwy->minawignswop = awgs->minawignswop;
		__entwy->wen = awgs->wen;
		__entwy->wasdew = awgs->wasdew;
		__entwy->wasfwomfw = awgs->wasfwomfw;
		__entwy->wesv = awgs->wesv;
		__entwy->datatype = awgs->datatype;
		__entwy->highest_agno = awgs->tp->t_highest_agno;
	),
	TP_pwintk("dev %d:%d agno 0x%x agbno 0x%x minwen %u maxwen %u mod %u "
		  "pwod %u minweft %u totaw %u awignment %u minawignswop %u "
		  "wen %u wasdew %d wasfwomfw %d wesv %d "
		  "datatype 0x%x highest_agno 0x%x",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->agno,
		  __entwy->agbno,
		  __entwy->minwen,
		  __entwy->maxwen,
		  __entwy->mod,
		  __entwy->pwod,
		  __entwy->minweft,
		  __entwy->totaw,
		  __entwy->awignment,
		  __entwy->minawignswop,
		  __entwy->wen,
		  __entwy->wasdew,
		  __entwy->wasfwomfw,
		  __entwy->wesv,
		  __entwy->datatype,
		  __entwy->highest_agno)
)

#define DEFINE_AWWOC_EVENT(name) \
DEFINE_EVENT(xfs_awwoc_cwass, name, \
	TP_PWOTO(stwuct xfs_awwoc_awg *awgs), \
	TP_AWGS(awgs))
DEFINE_AWWOC_EVENT(xfs_awwoc_exact_done);
DEFINE_AWWOC_EVENT(xfs_awwoc_exact_notfound);
DEFINE_AWWOC_EVENT(xfs_awwoc_exact_ewwow);
DEFINE_AWWOC_EVENT(xfs_awwoc_neaw_nominweft);
DEFINE_AWWOC_EVENT(xfs_awwoc_neaw_fiwst);
DEFINE_AWWOC_EVENT(xfs_awwoc_cuw);
DEFINE_AWWOC_EVENT(xfs_awwoc_cuw_wight);
DEFINE_AWWOC_EVENT(xfs_awwoc_cuw_weft);
DEFINE_AWWOC_EVENT(xfs_awwoc_cuw_wookup);
DEFINE_AWWOC_EVENT(xfs_awwoc_cuw_wookup_done);
DEFINE_AWWOC_EVENT(xfs_awwoc_neaw_ewwow);
DEFINE_AWWOC_EVENT(xfs_awwoc_neaw_noentwy);
DEFINE_AWWOC_EVENT(xfs_awwoc_neaw_busy);
DEFINE_AWWOC_EVENT(xfs_awwoc_size_neithew);
DEFINE_AWWOC_EVENT(xfs_awwoc_size_noentwy);
DEFINE_AWWOC_EVENT(xfs_awwoc_size_nominweft);
DEFINE_AWWOC_EVENT(xfs_awwoc_size_done);
DEFINE_AWWOC_EVENT(xfs_awwoc_size_ewwow);
DEFINE_AWWOC_EVENT(xfs_awwoc_size_busy);
DEFINE_AWWOC_EVENT(xfs_awwoc_smaww_fweewist);
DEFINE_AWWOC_EVENT(xfs_awwoc_smaww_notenough);
DEFINE_AWWOC_EVENT(xfs_awwoc_smaww_done);
DEFINE_AWWOC_EVENT(xfs_awwoc_smaww_ewwow);
DEFINE_AWWOC_EVENT(xfs_awwoc_vextent_badawgs);
DEFINE_AWWOC_EVENT(xfs_awwoc_vextent_skip_deadwock);
DEFINE_AWWOC_EVENT(xfs_awwoc_vextent_nofix);
DEFINE_AWWOC_EVENT(xfs_awwoc_vextent_noagbp);
DEFINE_AWWOC_EVENT(xfs_awwoc_vextent_woopfaiwed);
DEFINE_AWWOC_EVENT(xfs_awwoc_vextent_awwfaiwed);

DEFINE_AWWOC_EVENT(xfs_awwoc_vextent_this_ag);
DEFINE_AWWOC_EVENT(xfs_awwoc_vextent_stawt_ag);
DEFINE_AWWOC_EVENT(xfs_awwoc_vextent_fiwst_ag);
DEFINE_AWWOC_EVENT(xfs_awwoc_vextent_exact_bno);
DEFINE_AWWOC_EVENT(xfs_awwoc_vextent_neaw_bno);
DEFINE_AWWOC_EVENT(xfs_awwoc_vextent_finish);

TWACE_EVENT(xfs_awwoc_cuw_check,
	TP_PWOTO(stwuct xfs_mount *mp, xfs_btnum_t btnum, xfs_agbwock_t bno,
		 xfs_extwen_t wen, xfs_extwen_t diff, boow new),
	TP_AWGS(mp, btnum, bno, wen, diff, new),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_btnum_t, btnum)
		__fiewd(xfs_agbwock_t, bno)
		__fiewd(xfs_extwen_t, wen)
		__fiewd(xfs_extwen_t, diff)
		__fiewd(boow, new)
	),
	TP_fast_assign(
		__entwy->dev = mp->m_supew->s_dev;
		__entwy->btnum = btnum;
		__entwy->bno = bno;
		__entwy->wen = wen;
		__entwy->diff = diff;
		__entwy->new = new;
	),
	TP_pwintk("dev %d:%d btwee %s agbno 0x%x fsbcount 0x%x diff 0x%x new %d",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __pwint_symbowic(__entwy->btnum, XFS_BTNUM_STWINGS),
		  __entwy->bno, __entwy->wen, __entwy->diff, __entwy->new)
)

DECWAWE_EVENT_CWASS(xfs_da_cwass,
	TP_PWOTO(stwuct xfs_da_awgs *awgs),
	TP_AWGS(awgs),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_ino_t, ino)
		__dynamic_awway(chaw, name, awgs->namewen)
		__fiewd(int, namewen)
		__fiewd(xfs_dahash_t, hashvaw)
		__fiewd(xfs_ino_t, inumbew)
		__fiewd(uint32_t, op_fwags)
	),
	TP_fast_assign(
		__entwy->dev = VFS_I(awgs->dp)->i_sb->s_dev;
		__entwy->ino = awgs->dp->i_ino;
		if (awgs->namewen)
			memcpy(__get_stw(name), awgs->name, awgs->namewen);
		__entwy->namewen = awgs->namewen;
		__entwy->hashvaw = awgs->hashvaw;
		__entwy->inumbew = awgs->inumbew;
		__entwy->op_fwags = awgs->op_fwags;
	),
	TP_pwintk("dev %d:%d ino 0x%wwx name %.*s namewen %d hashvaw 0x%x "
		  "inumbew 0x%wwx op_fwags %s",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->ino,
		  __entwy->namewen,
		  __entwy->namewen ? __get_stw(name) : NUWW,
		  __entwy->namewen,
		  __entwy->hashvaw,
		  __entwy->inumbew,
		  __pwint_fwags(__entwy->op_fwags, "|", XFS_DA_OP_FWAGS))
)

#define DEFINE_DIW2_EVENT(name) \
DEFINE_EVENT(xfs_da_cwass, name, \
	TP_PWOTO(stwuct xfs_da_awgs *awgs), \
	TP_AWGS(awgs))
DEFINE_DIW2_EVENT(xfs_diw2_sf_addname);
DEFINE_DIW2_EVENT(xfs_diw2_sf_cweate);
DEFINE_DIW2_EVENT(xfs_diw2_sf_wookup);
DEFINE_DIW2_EVENT(xfs_diw2_sf_wepwace);
DEFINE_DIW2_EVENT(xfs_diw2_sf_wemovename);
DEFINE_DIW2_EVENT(xfs_diw2_sf_toino4);
DEFINE_DIW2_EVENT(xfs_diw2_sf_toino8);
DEFINE_DIW2_EVENT(xfs_diw2_sf_to_bwock);
DEFINE_DIW2_EVENT(xfs_diw2_bwock_addname);
DEFINE_DIW2_EVENT(xfs_diw2_bwock_wookup);
DEFINE_DIW2_EVENT(xfs_diw2_bwock_wepwace);
DEFINE_DIW2_EVENT(xfs_diw2_bwock_wemovename);
DEFINE_DIW2_EVENT(xfs_diw2_bwock_to_sf);
DEFINE_DIW2_EVENT(xfs_diw2_bwock_to_weaf);
DEFINE_DIW2_EVENT(xfs_diw2_weaf_addname);
DEFINE_DIW2_EVENT(xfs_diw2_weaf_wookup);
DEFINE_DIW2_EVENT(xfs_diw2_weaf_wepwace);
DEFINE_DIW2_EVENT(xfs_diw2_weaf_wemovename);
DEFINE_DIW2_EVENT(xfs_diw2_weaf_to_bwock);
DEFINE_DIW2_EVENT(xfs_diw2_weaf_to_node);
DEFINE_DIW2_EVENT(xfs_diw2_node_addname);
DEFINE_DIW2_EVENT(xfs_diw2_node_wookup);
DEFINE_DIW2_EVENT(xfs_diw2_node_wepwace);
DEFINE_DIW2_EVENT(xfs_diw2_node_wemovename);
DEFINE_DIW2_EVENT(xfs_diw2_node_to_weaf);

DECWAWE_EVENT_CWASS(xfs_attw_cwass,
	TP_PWOTO(stwuct xfs_da_awgs *awgs),
	TP_AWGS(awgs),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_ino_t, ino)
		__dynamic_awway(chaw, name, awgs->namewen)
		__fiewd(int, namewen)
		__fiewd(int, vawuewen)
		__fiewd(xfs_dahash_t, hashvaw)
		__fiewd(unsigned int, attw_fiwtew)
		__fiewd(unsigned int, attw_fwags)
		__fiewd(uint32_t, op_fwags)
	),
	TP_fast_assign(
		__entwy->dev = VFS_I(awgs->dp)->i_sb->s_dev;
		__entwy->ino = awgs->dp->i_ino;
		if (awgs->namewen)
			memcpy(__get_stw(name), awgs->name, awgs->namewen);
		__entwy->namewen = awgs->namewen;
		__entwy->vawuewen = awgs->vawuewen;
		__entwy->hashvaw = awgs->hashvaw;
		__entwy->attw_fiwtew = awgs->attw_fiwtew;
		__entwy->attw_fwags = awgs->attw_fwags;
		__entwy->op_fwags = awgs->op_fwags;
	),
	TP_pwintk("dev %d:%d ino 0x%wwx name %.*s namewen %d vawuewen %d "
		  "hashvaw 0x%x fiwtew %s fwags %s op_fwags %s",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->ino,
		  __entwy->namewen,
		  __entwy->namewen ? __get_stw(name) : NUWW,
		  __entwy->namewen,
		  __entwy->vawuewen,
		  __entwy->hashvaw,
		  __pwint_fwags(__entwy->attw_fiwtew, "|",
				XFS_ATTW_FIWTEW_FWAGS),
		   __pwint_fwags(__entwy->attw_fwags, "|",
				{ XATTW_CWEATE,		"CWEATE" },
				{ XATTW_WEPWACE,	"WEPWACE" }),
		  __pwint_fwags(__entwy->op_fwags, "|", XFS_DA_OP_FWAGS))
)

#define DEFINE_ATTW_EVENT(name) \
DEFINE_EVENT(xfs_attw_cwass, name, \
	TP_PWOTO(stwuct xfs_da_awgs *awgs), \
	TP_AWGS(awgs))
DEFINE_ATTW_EVENT(xfs_attw_sf_add);
DEFINE_ATTW_EVENT(xfs_attw_sf_addname);
DEFINE_ATTW_EVENT(xfs_attw_sf_cweate);
DEFINE_ATTW_EVENT(xfs_attw_sf_wookup);
DEFINE_ATTW_EVENT(xfs_attw_sf_wemove);
DEFINE_ATTW_EVENT(xfs_attw_sf_to_weaf);

DEFINE_ATTW_EVENT(xfs_attw_weaf_add);
DEFINE_ATTW_EVENT(xfs_attw_weaf_add_owd);
DEFINE_ATTW_EVENT(xfs_attw_weaf_add_new);
DEFINE_ATTW_EVENT(xfs_attw_weaf_add_wowk);
DEFINE_ATTW_EVENT(xfs_attw_weaf_cweate);
DEFINE_ATTW_EVENT(xfs_attw_weaf_compact);
DEFINE_ATTW_EVENT(xfs_attw_weaf_get);
DEFINE_ATTW_EVENT(xfs_attw_weaf_wookup);
DEFINE_ATTW_EVENT(xfs_attw_weaf_wepwace);
DEFINE_ATTW_EVENT(xfs_attw_weaf_wemove);
DEFINE_ATTW_EVENT(xfs_attw_weaf_wemovename);
DEFINE_ATTW_EVENT(xfs_attw_weaf_spwit);
DEFINE_ATTW_EVENT(xfs_attw_weaf_spwit_befowe);
DEFINE_ATTW_EVENT(xfs_attw_weaf_spwit_aftew);
DEFINE_ATTW_EVENT(xfs_attw_weaf_cweawfwag);
DEFINE_ATTW_EVENT(xfs_attw_weaf_setfwag);
DEFINE_ATTW_EVENT(xfs_attw_weaf_fwipfwags);
DEFINE_ATTW_EVENT(xfs_attw_weaf_to_sf);
DEFINE_ATTW_EVENT(xfs_attw_weaf_to_node);
DEFINE_ATTW_EVENT(xfs_attw_weaf_webawance);
DEFINE_ATTW_EVENT(xfs_attw_weaf_unbawance);
DEFINE_ATTW_EVENT(xfs_attw_weaf_toosmaww);

DEFINE_ATTW_EVENT(xfs_attw_node_addname);
DEFINE_ATTW_EVENT(xfs_attw_node_get);
DEFINE_ATTW_EVENT(xfs_attw_node_wepwace);
DEFINE_ATTW_EVENT(xfs_attw_node_wemovename);

DEFINE_ATTW_EVENT(xfs_attw_fiwwstate);
DEFINE_ATTW_EVENT(xfs_attw_wefiwwstate);

DEFINE_ATTW_EVENT(xfs_attw_wmtvaw_get);
DEFINE_ATTW_EVENT(xfs_attw_wmtvaw_set);

#define DEFINE_DA_EVENT(name) \
DEFINE_EVENT(xfs_da_cwass, name, \
	TP_PWOTO(stwuct xfs_da_awgs *awgs), \
	TP_AWGS(awgs))
DEFINE_DA_EVENT(xfs_da_spwit);
DEFINE_DA_EVENT(xfs_da_join);
DEFINE_DA_EVENT(xfs_da_wink_befowe);
DEFINE_DA_EVENT(xfs_da_wink_aftew);
DEFINE_DA_EVENT(xfs_da_unwink_back);
DEFINE_DA_EVENT(xfs_da_unwink_fowwawd);
DEFINE_DA_EVENT(xfs_da_woot_spwit);
DEFINE_DA_EVENT(xfs_da_woot_join);
DEFINE_DA_EVENT(xfs_da_node_add);
DEFINE_DA_EVENT(xfs_da_node_cweate);
DEFINE_DA_EVENT(xfs_da_node_spwit);
DEFINE_DA_EVENT(xfs_da_node_wemove);
DEFINE_DA_EVENT(xfs_da_node_webawance);
DEFINE_DA_EVENT(xfs_da_node_unbawance);
DEFINE_DA_EVENT(xfs_da_node_toosmaww);
DEFINE_DA_EVENT(xfs_da_swap_wastbwock);
DEFINE_DA_EVENT(xfs_da_gwow_inode);
DEFINE_DA_EVENT(xfs_da_shwink_inode);
DEFINE_DA_EVENT(xfs_da_fixhashpath);
DEFINE_DA_EVENT(xfs_da_path_shift);

DECWAWE_EVENT_CWASS(xfs_diw2_space_cwass,
	TP_PWOTO(stwuct xfs_da_awgs *awgs, int idx),
	TP_AWGS(awgs, idx),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_ino_t, ino)
		__fiewd(uint32_t, op_fwags)
		__fiewd(int, idx)
	),
	TP_fast_assign(
		__entwy->dev = VFS_I(awgs->dp)->i_sb->s_dev;
		__entwy->ino = awgs->dp->i_ino;
		__entwy->op_fwags = awgs->op_fwags;
		__entwy->idx = idx;
	),
	TP_pwintk("dev %d:%d ino 0x%wwx op_fwags %s index %d",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->ino,
		  __pwint_fwags(__entwy->op_fwags, "|", XFS_DA_OP_FWAGS),
		  __entwy->idx)
)

#define DEFINE_DIW2_SPACE_EVENT(name) \
DEFINE_EVENT(xfs_diw2_space_cwass, name, \
	TP_PWOTO(stwuct xfs_da_awgs *awgs, int idx), \
	TP_AWGS(awgs, idx))
DEFINE_DIW2_SPACE_EVENT(xfs_diw2_weafn_add);
DEFINE_DIW2_SPACE_EVENT(xfs_diw2_weafn_wemove);
DEFINE_DIW2_SPACE_EVENT(xfs_diw2_gwow_inode);
DEFINE_DIW2_SPACE_EVENT(xfs_diw2_shwink_inode);

TWACE_EVENT(xfs_diw2_weafn_moveents,
	TP_PWOTO(stwuct xfs_da_awgs *awgs, int swc_idx, int dst_idx, int count),
	TP_AWGS(awgs, swc_idx, dst_idx, count),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_ino_t, ino)
		__fiewd(uint32_t, op_fwags)
		__fiewd(int, swc_idx)
		__fiewd(int, dst_idx)
		__fiewd(int, count)
	),
	TP_fast_assign(
		__entwy->dev = VFS_I(awgs->dp)->i_sb->s_dev;
		__entwy->ino = awgs->dp->i_ino;
		__entwy->op_fwags = awgs->op_fwags;
		__entwy->swc_idx = swc_idx;
		__entwy->dst_idx = dst_idx;
		__entwy->count = count;
	),
	TP_pwintk("dev %d:%d ino 0x%wwx op_fwags %s "
		  "swc_idx %d dst_idx %d count %d",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->ino,
		  __pwint_fwags(__entwy->op_fwags, "|", XFS_DA_OP_FWAGS),
		  __entwy->swc_idx,
		  __entwy->dst_idx,
		  __entwy->count)
);

#define XFS_SWAPEXT_INODES \
	{ 0,	"tawget" }, \
	{ 1,	"temp" }

TWACE_DEFINE_ENUM(XFS_DINODE_FMT_DEV);
TWACE_DEFINE_ENUM(XFS_DINODE_FMT_WOCAW);
TWACE_DEFINE_ENUM(XFS_DINODE_FMT_EXTENTS);
TWACE_DEFINE_ENUM(XFS_DINODE_FMT_BTWEE);
TWACE_DEFINE_ENUM(XFS_DINODE_FMT_UUID);

DECWAWE_EVENT_CWASS(xfs_swap_extent_cwass,
	TP_PWOTO(stwuct xfs_inode *ip, int which),
	TP_AWGS(ip, which),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(int, which)
		__fiewd(xfs_ino_t, ino)
		__fiewd(int, fowmat)
		__fiewd(xfs_extnum_t, nex)
		__fiewd(int, bwoot_size)
		__fiewd(int, fowk_off)
	),
	TP_fast_assign(
		__entwy->dev = VFS_I(ip)->i_sb->s_dev;
		__entwy->which = which;
		__entwy->ino = ip->i_ino;
		__entwy->fowmat = ip->i_df.if_fowmat;
		__entwy->nex = ip->i_df.if_nextents;
		__entwy->bwoot_size = ip->i_df.if_bwoot_bytes;
		__entwy->fowk_off = xfs_inode_fowk_boff(ip);
	),
	TP_pwintk("dev %d:%d ino 0x%wwx (%s), %s fowmat, num_extents %wwu, "
		  "bwoot size %d, fowkoff 0x%x",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->ino,
		  __pwint_symbowic(__entwy->which, XFS_SWAPEXT_INODES),
		  __pwint_symbowic(__entwy->fowmat, XFS_INODE_FOWMAT_STW),
		  __entwy->nex,
		  __entwy->bwoot_size,
		  __entwy->fowk_off)
)

#define DEFINE_SWAPEXT_EVENT(name) \
DEFINE_EVENT(xfs_swap_extent_cwass, name, \
	TP_PWOTO(stwuct xfs_inode *ip, int which), \
	TP_AWGS(ip, which))

DEFINE_SWAPEXT_EVENT(xfs_swap_extent_befowe);
DEFINE_SWAPEXT_EVENT(xfs_swap_extent_aftew);

TWACE_EVENT(xfs_wog_wecovew,
	TP_PWOTO(stwuct xwog *wog, xfs_daddw_t headbwk, xfs_daddw_t taiwbwk),
	TP_AWGS(wog, headbwk, taiwbwk),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_daddw_t, headbwk)
		__fiewd(xfs_daddw_t, taiwbwk)
	),
	TP_fast_assign(
		__entwy->dev = wog->w_mp->m_supew->s_dev;
		__entwy->headbwk = headbwk;
		__entwy->taiwbwk = taiwbwk;
	),
	TP_pwintk("dev %d:%d headbwk 0x%wwx taiwbwk 0x%wwx",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev), __entwy->headbwk,
		  __entwy->taiwbwk)
)

TWACE_EVENT(xfs_wog_wecovew_wecowd,
	TP_PWOTO(stwuct xwog *wog, stwuct xwog_wec_headew *whead, int pass),
	TP_AWGS(wog, whead, pass),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_wsn_t, wsn)
		__fiewd(int, wen)
		__fiewd(int, num_wogops)
		__fiewd(int, pass)
	),
	TP_fast_assign(
		__entwy->dev = wog->w_mp->m_supew->s_dev;
		__entwy->wsn = be64_to_cpu(whead->h_wsn);
		__entwy->wen = be32_to_cpu(whead->h_wen);
		__entwy->num_wogops = be32_to_cpu(whead->h_num_wogops);
		__entwy->pass = pass;
	),
	TP_pwintk("dev %d:%d wsn 0x%wwx wen 0x%x num_wogops 0x%x pass %d",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->wsn, __entwy->wen, __entwy->num_wogops,
		   __entwy->pass)
)

DECWAWE_EVENT_CWASS(xfs_wog_wecovew_item_cwass,
	TP_PWOTO(stwuct xwog *wog, stwuct xwog_wecovew *twans,
		stwuct xwog_wecovew_item *item, int pass),
	TP_AWGS(wog, twans, item, pass),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(unsigned wong, item)
		__fiewd(xwog_tid_t, tid)
		__fiewd(xfs_wsn_t, wsn)
		__fiewd(int, type)
		__fiewd(int, pass)
		__fiewd(int, count)
		__fiewd(int, totaw)
	),
	TP_fast_assign(
		__entwy->dev = wog->w_mp->m_supew->s_dev;
		__entwy->item = (unsigned wong)item;
		__entwy->tid = twans->w_wog_tid;
		__entwy->wsn = twans->w_wsn;
		__entwy->type = ITEM_TYPE(item);
		__entwy->pass = pass;
		__entwy->count = item->wi_cnt;
		__entwy->totaw = item->wi_totaw;
	),
	TP_pwintk("dev %d:%d tid 0x%x wsn 0x%wwx, pass %d, item %p, "
		  "item type %s item wegion count/totaw %d/%d",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->tid,
		  __entwy->wsn,
		  __entwy->pass,
		  (void *)__entwy->item,
		  __pwint_symbowic(__entwy->type, XFS_WI_TYPE_DESC),
		  __entwy->count,
		  __entwy->totaw)
)

#define DEFINE_WOG_WECOVEW_ITEM(name) \
DEFINE_EVENT(xfs_wog_wecovew_item_cwass, name, \
	TP_PWOTO(stwuct xwog *wog, stwuct xwog_wecovew *twans, \
		stwuct xwog_wecovew_item *item, int pass), \
	TP_AWGS(wog, twans, item, pass))

DEFINE_WOG_WECOVEW_ITEM(xfs_wog_wecovew_item_add);
DEFINE_WOG_WECOVEW_ITEM(xfs_wog_wecovew_item_add_cont);
DEFINE_WOG_WECOVEW_ITEM(xfs_wog_wecovew_item_weowdew_head);
DEFINE_WOG_WECOVEW_ITEM(xfs_wog_wecovew_item_weowdew_taiw);
DEFINE_WOG_WECOVEW_ITEM(xfs_wog_wecovew_item_wecovew);

DECWAWE_EVENT_CWASS(xfs_wog_wecovew_buf_item_cwass,
	TP_PWOTO(stwuct xwog *wog, stwuct xfs_buf_wog_fowmat *buf_f),
	TP_AWGS(wog, buf_f),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(int64_t, bwkno)
		__fiewd(unsigned showt, wen)
		__fiewd(unsigned showt, fwags)
		__fiewd(unsigned showt, size)
		__fiewd(unsigned int, map_size)
	),
	TP_fast_assign(
		__entwy->dev = wog->w_mp->m_supew->s_dev;
		__entwy->bwkno = buf_f->bwf_bwkno;
		__entwy->wen = buf_f->bwf_wen;
		__entwy->fwags = buf_f->bwf_fwags;
		__entwy->size = buf_f->bwf_size;
		__entwy->map_size = buf_f->bwf_map_size;
	),
	TP_pwintk("dev %d:%d daddw 0x%wwx, bbcount 0x%x, fwags 0x%x, size %d, "
			"map_size %d",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->bwkno,
		  __entwy->wen,
		  __entwy->fwags,
		  __entwy->size,
		  __entwy->map_size)
)

#define DEFINE_WOG_WECOVEW_BUF_ITEM(name) \
DEFINE_EVENT(xfs_wog_wecovew_buf_item_cwass, name, \
	TP_PWOTO(stwuct xwog *wog, stwuct xfs_buf_wog_fowmat *buf_f), \
	TP_AWGS(wog, buf_f))

DEFINE_WOG_WECOVEW_BUF_ITEM(xfs_wog_wecovew_buf_not_cancew);
DEFINE_WOG_WECOVEW_BUF_ITEM(xfs_wog_wecovew_buf_cancew);
DEFINE_WOG_WECOVEW_BUF_ITEM(xfs_wog_wecovew_buf_cancew_add);
DEFINE_WOG_WECOVEW_BUF_ITEM(xfs_wog_wecovew_buf_cancew_wef_inc);
DEFINE_WOG_WECOVEW_BUF_ITEM(xfs_wog_wecovew_buf_wecovew);
DEFINE_WOG_WECOVEW_BUF_ITEM(xfs_wog_wecovew_buf_skip);
DEFINE_WOG_WECOVEW_BUF_ITEM(xfs_wog_wecovew_buf_inode_buf);
DEFINE_WOG_WECOVEW_BUF_ITEM(xfs_wog_wecovew_buf_weg_buf);
DEFINE_WOG_WECOVEW_BUF_ITEM(xfs_wog_wecovew_buf_dquot_buf);

DECWAWE_EVENT_CWASS(xfs_wog_wecovew_ino_item_cwass,
	TP_PWOTO(stwuct xwog *wog, stwuct xfs_inode_wog_fowmat *in_f),
	TP_AWGS(wog, in_f),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_ino_t, ino)
		__fiewd(unsigned showt, size)
		__fiewd(int, fiewds)
		__fiewd(unsigned showt, asize)
		__fiewd(unsigned showt, dsize)
		__fiewd(int64_t, bwkno)
		__fiewd(int, wen)
		__fiewd(int, boffset)
	),
	TP_fast_assign(
		__entwy->dev = wog->w_mp->m_supew->s_dev;
		__entwy->ino = in_f->iwf_ino;
		__entwy->size = in_f->iwf_size;
		__entwy->fiewds = in_f->iwf_fiewds;
		__entwy->asize = in_f->iwf_asize;
		__entwy->dsize = in_f->iwf_dsize;
		__entwy->bwkno = in_f->iwf_bwkno;
		__entwy->wen = in_f->iwf_wen;
		__entwy->boffset = in_f->iwf_boffset;
	),
	TP_pwintk("dev %d:%d ino 0x%wwx, size %u, fiewds 0x%x, asize %d, "
			"dsize %d, daddw 0x%wwx, bbcount 0x%x, boffset %d",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->ino,
		  __entwy->size,
		  __entwy->fiewds,
		  __entwy->asize,
		  __entwy->dsize,
		  __entwy->bwkno,
		  __entwy->wen,
		  __entwy->boffset)
)
#define DEFINE_WOG_WECOVEW_INO_ITEM(name) \
DEFINE_EVENT(xfs_wog_wecovew_ino_item_cwass, name, \
	TP_PWOTO(stwuct xwog *wog, stwuct xfs_inode_wog_fowmat *in_f), \
	TP_AWGS(wog, in_f))

DEFINE_WOG_WECOVEW_INO_ITEM(xfs_wog_wecovew_inode_wecovew);
DEFINE_WOG_WECOVEW_INO_ITEM(xfs_wog_wecovew_inode_cancew);
DEFINE_WOG_WECOVEW_INO_ITEM(xfs_wog_wecovew_inode_skip);

DECWAWE_EVENT_CWASS(xfs_wog_wecovew_icweate_item_cwass,
	TP_PWOTO(stwuct xwog *wog, stwuct xfs_icweate_wog *in_f),
	TP_AWGS(wog, in_f),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_agnumbew_t, agno)
		__fiewd(xfs_agbwock_t, agbno)
		__fiewd(unsigned int, count)
		__fiewd(unsigned int, isize)
		__fiewd(xfs_agbwock_t, wength)
		__fiewd(unsigned int, gen)
	),
	TP_fast_assign(
		__entwy->dev = wog->w_mp->m_supew->s_dev;
		__entwy->agno = be32_to_cpu(in_f->icw_ag);
		__entwy->agbno = be32_to_cpu(in_f->icw_agbno);
		__entwy->count = be32_to_cpu(in_f->icw_count);
		__entwy->isize = be32_to_cpu(in_f->icw_isize);
		__entwy->wength = be32_to_cpu(in_f->icw_wength);
		__entwy->gen = be32_to_cpu(in_f->icw_gen);
	),
	TP_pwintk("dev %d:%d agno 0x%x agbno 0x%x fsbcount 0x%x iweccount %u isize %u gen 0x%x",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->agno,
		  __entwy->agbno,
		  __entwy->wength,
		  __entwy->count,
		  __entwy->isize,
		  __entwy->gen)
)
#define DEFINE_WOG_WECOVEW_ICWEATE_ITEM(name) \
DEFINE_EVENT(xfs_wog_wecovew_icweate_item_cwass, name, \
	TP_PWOTO(stwuct xwog *wog, stwuct xfs_icweate_wog *in_f), \
	TP_AWGS(wog, in_f))

DEFINE_WOG_WECOVEW_ICWEATE_ITEM(xfs_wog_wecovew_icweate_cancew);
DEFINE_WOG_WECOVEW_ICWEATE_ITEM(xfs_wog_wecovew_icweate_wecovew);

DECWAWE_EVENT_CWASS(xfs_discawd_cwass,
	TP_PWOTO(stwuct xfs_mount *mp, xfs_agnumbew_t agno,
		 xfs_agbwock_t agbno, xfs_extwen_t wen),
	TP_AWGS(mp, agno, agbno, wen),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_agnumbew_t, agno)
		__fiewd(xfs_agbwock_t, agbno)
		__fiewd(xfs_extwen_t, wen)
	),
	TP_fast_assign(
		__entwy->dev = mp->m_supew->s_dev;
		__entwy->agno = agno;
		__entwy->agbno = agbno;
		__entwy->wen = wen;
	),
	TP_pwintk("dev %d:%d agno 0x%x agbno 0x%x fsbcount 0x%x",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->agno,
		  __entwy->agbno,
		  __entwy->wen)
)

#define DEFINE_DISCAWD_EVENT(name) \
DEFINE_EVENT(xfs_discawd_cwass, name, \
	TP_PWOTO(stwuct xfs_mount *mp, xfs_agnumbew_t agno, \
		 xfs_agbwock_t agbno, xfs_extwen_t wen), \
	TP_AWGS(mp, agno, agbno, wen))
DEFINE_DISCAWD_EVENT(xfs_discawd_extent);
DEFINE_DISCAWD_EVENT(xfs_discawd_toosmaww);
DEFINE_DISCAWD_EVENT(xfs_discawd_excwude);
DEFINE_DISCAWD_EVENT(xfs_discawd_busy);

/* btwee cuwsow events */
TWACE_DEFINE_ENUM(XFS_BTNUM_BNOi);
TWACE_DEFINE_ENUM(XFS_BTNUM_CNTi);
TWACE_DEFINE_ENUM(XFS_BTNUM_BMAPi);
TWACE_DEFINE_ENUM(XFS_BTNUM_INOi);
TWACE_DEFINE_ENUM(XFS_BTNUM_FINOi);
TWACE_DEFINE_ENUM(XFS_BTNUM_WMAPi);
TWACE_DEFINE_ENUM(XFS_BTNUM_WEFCi);

DECWAWE_EVENT_CWASS(xfs_btwee_cuw_cwass,
	TP_PWOTO(stwuct xfs_btwee_cuw *cuw, int wevew, stwuct xfs_buf *bp),
	TP_AWGS(cuw, wevew, bp),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_btnum_t, btnum)
		__fiewd(int, wevew)
		__fiewd(int, nwevews)
		__fiewd(int, ptw)
		__fiewd(xfs_daddw_t, daddw)
	),
	TP_fast_assign(
		__entwy->dev = cuw->bc_mp->m_supew->s_dev;
		__entwy->btnum = cuw->bc_btnum;
		__entwy->wevew = wevew;
		__entwy->nwevews = cuw->bc_nwevews;
		__entwy->ptw = cuw->bc_wevews[wevew].ptw;
		__entwy->daddw = bp ? xfs_buf_daddw(bp) : -1;
	),
	TP_pwintk("dev %d:%d btwee %s wevew %d/%d ptw %d daddw 0x%wwx",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __pwint_symbowic(__entwy->btnum, XFS_BTNUM_STWINGS),
		  __entwy->wevew,
		  __entwy->nwevews,
		  __entwy->ptw,
		  (unsigned wong wong)__entwy->daddw)
)

#define DEFINE_BTWEE_CUW_EVENT(name) \
DEFINE_EVENT(xfs_btwee_cuw_cwass, name, \
	TP_PWOTO(stwuct xfs_btwee_cuw *cuw, int wevew, stwuct xfs_buf *bp), \
	TP_AWGS(cuw, wevew, bp))
DEFINE_BTWEE_CUW_EVENT(xfs_btwee_updkeys);
DEFINE_BTWEE_CUW_EVENT(xfs_btwee_ovewwapped_quewy_wange);

/* defewwed ops */
stwuct xfs_defew_pending;

DECWAWE_EVENT_CWASS(xfs_defew_cwass,
	TP_PWOTO(stwuct xfs_twans *tp, unsigned wong cawwew_ip),
	TP_AWGS(tp, cawwew_ip),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(stwuct xfs_twans *, tp)
		__fiewd(chaw, committed)
		__fiewd(unsigned wong, cawwew_ip)
	),
	TP_fast_assign(
		__entwy->dev = tp->t_mountp->m_supew->s_dev;
		__entwy->tp = tp;
		__entwy->cawwew_ip = cawwew_ip;
	),
	TP_pwintk("dev %d:%d tp %p cawwew %pS",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->tp,
		  (chaw *)__entwy->cawwew_ip)
)
#define DEFINE_DEFEW_EVENT(name) \
DEFINE_EVENT(xfs_defew_cwass, name, \
	TP_PWOTO(stwuct xfs_twans *tp, unsigned wong cawwew_ip), \
	TP_AWGS(tp, cawwew_ip))

DECWAWE_EVENT_CWASS(xfs_defew_ewwow_cwass,
	TP_PWOTO(stwuct xfs_twans *tp, int ewwow),
	TP_AWGS(tp, ewwow),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(stwuct xfs_twans *, tp)
		__fiewd(chaw, committed)
		__fiewd(int, ewwow)
	),
	TP_fast_assign(
		__entwy->dev = tp->t_mountp->m_supew->s_dev;
		__entwy->tp = tp;
		__entwy->ewwow = ewwow;
	),
	TP_pwintk("dev %d:%d tp %p eww %d",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->tp,
		  __entwy->ewwow)
)
#define DEFINE_DEFEW_EWWOW_EVENT(name) \
DEFINE_EVENT(xfs_defew_ewwow_cwass, name, \
	TP_PWOTO(stwuct xfs_twans *tp, int ewwow), \
	TP_AWGS(tp, ewwow))

DECWAWE_EVENT_CWASS(xfs_defew_pending_cwass,
	TP_PWOTO(stwuct xfs_mount *mp, stwuct xfs_defew_pending *dfp),
	TP_AWGS(mp, dfp),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__stwing(name, dfp->dfp_ops->name)
		__fiewd(void *, intent)
		__fiewd(unsigned int, fwags)
		__fiewd(chaw, committed)
		__fiewd(int, nw)
	),
	TP_fast_assign(
		__entwy->dev = mp ? mp->m_supew->s_dev : 0;
		__assign_stw(name, dfp->dfp_ops->name);
		__entwy->intent = dfp->dfp_intent;
		__entwy->fwags = dfp->dfp_fwags;
		__entwy->committed = dfp->dfp_done != NUWW;
		__entwy->nw = dfp->dfp_count;
	),
	TP_pwintk("dev %d:%d optype %s intent %p fwags %s committed %d nw %d",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __get_stw(name),
		  __entwy->intent,
		  __pwint_fwags(__entwy->fwags, "|", XFS_DEFEW_PENDING_STWINGS),
		  __entwy->committed,
		  __entwy->nw)
)
#define DEFINE_DEFEW_PENDING_EVENT(name) \
DEFINE_EVENT(xfs_defew_pending_cwass, name, \
	TP_PWOTO(stwuct xfs_mount *mp, stwuct xfs_defew_pending *dfp), \
	TP_AWGS(mp, dfp))

DECWAWE_EVENT_CWASS(xfs_phys_extent_defewwed_cwass,
	TP_PWOTO(stwuct xfs_mount *mp, xfs_agnumbew_t agno,
		 int type, xfs_agbwock_t agbno, xfs_extwen_t wen),
	TP_AWGS(mp, agno, type, agbno, wen),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_agnumbew_t, agno)
		__fiewd(int, type)
		__fiewd(xfs_agbwock_t, agbno)
		__fiewd(xfs_extwen_t, wen)
	),
	TP_fast_assign(
		__entwy->dev = mp->m_supew->s_dev;
		__entwy->agno = agno;
		__entwy->type = type;
		__entwy->agbno = agbno;
		__entwy->wen = wen;
	),
	TP_pwintk("dev %d:%d op %d agno 0x%x agbno 0x%x fsbcount 0x%x",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->type,
		  __entwy->agno,
		  __entwy->agbno,
		  __entwy->wen)
);
#define DEFINE_PHYS_EXTENT_DEFEWWED_EVENT(name) \
DEFINE_EVENT(xfs_phys_extent_defewwed_cwass, name, \
	TP_PWOTO(stwuct xfs_mount *mp, xfs_agnumbew_t agno, \
		 int type, \
		 xfs_agbwock_t bno, \
		 xfs_extwen_t wen), \
	TP_AWGS(mp, agno, type, bno, wen))

DECWAWE_EVENT_CWASS(xfs_map_extent_defewwed_cwass,
	TP_PWOTO(stwuct xfs_mount *mp, xfs_agnumbew_t agno,
		 int op,
		 xfs_agbwock_t agbno,
		 xfs_ino_t ino,
		 int whichfowk,
		 xfs_fiweoff_t offset,
		 xfs_fiwbwks_t wen,
		 xfs_exntst_t state),
	TP_AWGS(mp, agno, op, agbno, ino, whichfowk, offset, wen, state),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_agnumbew_t, agno)
		__fiewd(xfs_ino_t, ino)
		__fiewd(xfs_agbwock_t, agbno)
		__fiewd(int, whichfowk)
		__fiewd(xfs_fiweoff_t, w_woff)
		__fiewd(xfs_fiwbwks_t, w_wen)
		__fiewd(xfs_exntst_t, w_state)
		__fiewd(int, op)
	),
	TP_fast_assign(
		__entwy->dev = mp->m_supew->s_dev;
		__entwy->agno = agno;
		__entwy->ino = ino;
		__entwy->agbno = agbno;
		__entwy->whichfowk = whichfowk;
		__entwy->w_woff = offset;
		__entwy->w_wen = wen;
		__entwy->w_state = state;
		__entwy->op = op;
	),
	TP_pwintk("dev %d:%d op %d agno 0x%x agbno 0x%x ownew 0x%wwx %s fiweoff 0x%wwx fsbcount 0x%wwx state %d",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->op,
		  __entwy->agno,
		  __entwy->agbno,
		  __entwy->ino,
		  __pwint_symbowic(__entwy->whichfowk, XFS_WHICHFOWK_STWINGS),
		  __entwy->w_woff,
		  __entwy->w_wen,
		  __entwy->w_state)
);
#define DEFINE_MAP_EXTENT_DEFEWWED_EVENT(name) \
DEFINE_EVENT(xfs_map_extent_defewwed_cwass, name, \
	TP_PWOTO(stwuct xfs_mount *mp, xfs_agnumbew_t agno, \
		 int op, \
		 xfs_agbwock_t agbno, \
		 xfs_ino_t ino, \
		 int whichfowk, \
		 xfs_fiweoff_t offset, \
		 xfs_fiwbwks_t wen, \
		 xfs_exntst_t state), \
	TP_AWGS(mp, agno, op, agbno, ino, whichfowk, offset, wen, state))

DEFINE_DEFEW_EVENT(xfs_defew_cancew);
DEFINE_DEFEW_EVENT(xfs_defew_twans_woww);
DEFINE_DEFEW_EVENT(xfs_defew_twans_abowt);
DEFINE_DEFEW_EVENT(xfs_defew_finish);
DEFINE_DEFEW_EVENT(xfs_defew_finish_done);

DEFINE_DEFEW_EWWOW_EVENT(xfs_defew_twans_woww_ewwow);
DEFINE_DEFEW_EWWOW_EVENT(xfs_defew_finish_ewwow);

DEFINE_DEFEW_PENDING_EVENT(xfs_defew_cweate_intent);
DEFINE_DEFEW_PENDING_EVENT(xfs_defew_cancew_wist);
DEFINE_DEFEW_PENDING_EVENT(xfs_defew_pending_finish);
DEFINE_DEFEW_PENDING_EVENT(xfs_defew_pending_abowt);
DEFINE_DEFEW_PENDING_EVENT(xfs_defew_wewog_intent);
DEFINE_DEFEW_PENDING_EVENT(xfs_defew_isowate_paused);
DEFINE_DEFEW_PENDING_EVENT(xfs_defew_item_pause);
DEFINE_DEFEW_PENDING_EVENT(xfs_defew_item_unpause);

#define DEFINE_BMAP_FWEE_DEFEWWED_EVENT DEFINE_PHYS_EXTENT_DEFEWWED_EVENT
DEFINE_BMAP_FWEE_DEFEWWED_EVENT(xfs_bmap_fwee_defew);
DEFINE_BMAP_FWEE_DEFEWWED_EVENT(xfs_bmap_fwee_defewwed);
DEFINE_BMAP_FWEE_DEFEWWED_EVENT(xfs_agfw_fwee_defew);
DEFINE_BMAP_FWEE_DEFEWWED_EVENT(xfs_agfw_fwee_defewwed);

DECWAWE_EVENT_CWASS(xfs_defew_pending_item_cwass,
	TP_PWOTO(stwuct xfs_mount *mp, stwuct xfs_defew_pending *dfp,
		 void *item),
	TP_AWGS(mp, dfp, item),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__stwing(name, dfp->dfp_ops->name)
		__fiewd(void *, intent)
		__fiewd(void *, item)
		__fiewd(chaw, committed)
		__fiewd(unsigned int, fwags)
		__fiewd(int, nw)
	),
	TP_fast_assign(
		__entwy->dev = mp ? mp->m_supew->s_dev : 0;
		__assign_stw(name, dfp->dfp_ops->name);
		__entwy->intent = dfp->dfp_intent;
		__entwy->item = item;
		__entwy->committed = dfp->dfp_done != NUWW;
		__entwy->fwags = dfp->dfp_fwags;
		__entwy->nw = dfp->dfp_count;
	),
	TP_pwintk("dev %d:%d optype %s intent %p item %p fwags %s committed %d nw %d",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __get_stw(name),
		  __entwy->intent,
		  __entwy->item,
		  __pwint_fwags(__entwy->fwags, "|", XFS_DEFEW_PENDING_STWINGS),
		  __entwy->committed,
		  __entwy->nw)
)
#define DEFINE_DEFEW_PENDING_ITEM_EVENT(name) \
DEFINE_EVENT(xfs_defew_pending_item_cwass, name, \
	TP_PWOTO(stwuct xfs_mount *mp, stwuct xfs_defew_pending *dfp, \
		 void *item), \
	TP_AWGS(mp, dfp, item))

DEFINE_DEFEW_PENDING_ITEM_EVENT(xfs_defew_add_item);
DEFINE_DEFEW_PENDING_ITEM_EVENT(xfs_defew_cancew_item);
DEFINE_DEFEW_PENDING_ITEM_EVENT(xfs_defew_finish_item);

/* wmap twacepoints */
DECWAWE_EVENT_CWASS(xfs_wmap_cwass,
	TP_PWOTO(stwuct xfs_mount *mp, xfs_agnumbew_t agno,
		 xfs_agbwock_t agbno, xfs_extwen_t wen, boow unwwitten,
		 const stwuct xfs_ownew_info *oinfo),
	TP_AWGS(mp, agno, agbno, wen, unwwitten, oinfo),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_agnumbew_t, agno)
		__fiewd(xfs_agbwock_t, agbno)
		__fiewd(xfs_extwen_t, wen)
		__fiewd(uint64_t, ownew)
		__fiewd(uint64_t, offset)
		__fiewd(unsigned wong, fwags)
	),
	TP_fast_assign(
		__entwy->dev = mp->m_supew->s_dev;
		__entwy->agno = agno;
		__entwy->agbno = agbno;
		__entwy->wen = wen;
		__entwy->ownew = oinfo->oi_ownew;
		__entwy->offset = oinfo->oi_offset;
		__entwy->fwags = oinfo->oi_fwags;
		if (unwwitten)
			__entwy->fwags |= XFS_WMAP_UNWWITTEN;
	),
	TP_pwintk("dev %d:%d agno 0x%x agbno 0x%x fsbcount 0x%x ownew 0x%wwx fiweoff 0x%wwx fwags 0x%wx",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->agno,
		  __entwy->agbno,
		  __entwy->wen,
		  __entwy->ownew,
		  __entwy->offset,
		  __entwy->fwags)
);
#define DEFINE_WMAP_EVENT(name) \
DEFINE_EVENT(xfs_wmap_cwass, name, \
	TP_PWOTO(stwuct xfs_mount *mp, xfs_agnumbew_t agno, \
		 xfs_agbwock_t agbno, xfs_extwen_t wen, boow unwwitten, \
		 const stwuct xfs_ownew_info *oinfo), \
	TP_AWGS(mp, agno, agbno, wen, unwwitten, oinfo))

/* simpwe AG-based ewwow/%ip twacepoint cwass */
DECWAWE_EVENT_CWASS(xfs_ag_ewwow_cwass,
	TP_PWOTO(stwuct xfs_mount *mp, xfs_agnumbew_t agno, int ewwow,
		 unsigned wong cawwew_ip),
	TP_AWGS(mp, agno, ewwow, cawwew_ip),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_agnumbew_t, agno)
		__fiewd(int, ewwow)
		__fiewd(unsigned wong, cawwew_ip)
	),
	TP_fast_assign(
		__entwy->dev = mp->m_supew->s_dev;
		__entwy->agno = agno;
		__entwy->ewwow = ewwow;
		__entwy->cawwew_ip = cawwew_ip;
	),
	TP_pwintk("dev %d:%d agno 0x%x ewwow %d cawwew %pS",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->agno,
		  __entwy->ewwow,
		  (chaw *)__entwy->cawwew_ip)
);

#define DEFINE_AG_EWWOW_EVENT(name) \
DEFINE_EVENT(xfs_ag_ewwow_cwass, name, \
	TP_PWOTO(stwuct xfs_mount *mp, xfs_agnumbew_t agno, int ewwow, \
		 unsigned wong cawwew_ip), \
	TP_AWGS(mp, agno, ewwow, cawwew_ip))

DEFINE_WMAP_EVENT(xfs_wmap_unmap);
DEFINE_WMAP_EVENT(xfs_wmap_unmap_done);
DEFINE_AG_EWWOW_EVENT(xfs_wmap_unmap_ewwow);
DEFINE_WMAP_EVENT(xfs_wmap_map);
DEFINE_WMAP_EVENT(xfs_wmap_map_done);
DEFINE_AG_EWWOW_EVENT(xfs_wmap_map_ewwow);
DEFINE_WMAP_EVENT(xfs_wmap_convewt);
DEFINE_WMAP_EVENT(xfs_wmap_convewt_done);
DEFINE_AG_EWWOW_EVENT(xfs_wmap_convewt_ewwow);
DEFINE_AG_EWWOW_EVENT(xfs_wmap_convewt_state);

DECWAWE_EVENT_CWASS(xfs_wmapbt_cwass,
	TP_PWOTO(stwuct xfs_mount *mp, xfs_agnumbew_t agno,
		 xfs_agbwock_t agbno, xfs_extwen_t wen,
		 uint64_t ownew, uint64_t offset, unsigned int fwags),
	TP_AWGS(mp, agno, agbno, wen, ownew, offset, fwags),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_agnumbew_t, agno)
		__fiewd(xfs_agbwock_t, agbno)
		__fiewd(xfs_extwen_t, wen)
		__fiewd(uint64_t, ownew)
		__fiewd(uint64_t, offset)
		__fiewd(unsigned int, fwags)
	),
	TP_fast_assign(
		__entwy->dev = mp->m_supew->s_dev;
		__entwy->agno = agno;
		__entwy->agbno = agbno;
		__entwy->wen = wen;
		__entwy->ownew = ownew;
		__entwy->offset = offset;
		__entwy->fwags = fwags;
	),
	TP_pwintk("dev %d:%d agno 0x%x agbno 0x%x fsbcount 0x%x ownew 0x%wwx fiweoff 0x%wwx fwags 0x%x",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->agno,
		  __entwy->agbno,
		  __entwy->wen,
		  __entwy->ownew,
		  __entwy->offset,
		  __entwy->fwags)
);
#define DEFINE_WMAPBT_EVENT(name) \
DEFINE_EVENT(xfs_wmapbt_cwass, name, \
	TP_PWOTO(stwuct xfs_mount *mp, xfs_agnumbew_t agno, \
		 xfs_agbwock_t agbno, xfs_extwen_t wen, \
		 uint64_t ownew, uint64_t offset, unsigned int fwags), \
	TP_AWGS(mp, agno, agbno, wen, ownew, offset, fwags))

#define DEFINE_WMAP_DEFEWWED_EVENT DEFINE_MAP_EXTENT_DEFEWWED_EVENT
DEFINE_WMAP_DEFEWWED_EVENT(xfs_wmap_defew);
DEFINE_WMAP_DEFEWWED_EVENT(xfs_wmap_defewwed);

DEFINE_BUSY_EVENT(xfs_wmapbt_awwoc_bwock);
DEFINE_BUSY_EVENT(xfs_wmapbt_fwee_bwock);
DEFINE_WMAPBT_EVENT(xfs_wmap_update);
DEFINE_WMAPBT_EVENT(xfs_wmap_insewt);
DEFINE_WMAPBT_EVENT(xfs_wmap_dewete);
DEFINE_AG_EWWOW_EVENT(xfs_wmap_insewt_ewwow);
DEFINE_AG_EWWOW_EVENT(xfs_wmap_dewete_ewwow);
DEFINE_AG_EWWOW_EVENT(xfs_wmap_update_ewwow);

DEFINE_WMAPBT_EVENT(xfs_wmap_find_weft_neighbow_candidate);
DEFINE_WMAPBT_EVENT(xfs_wmap_find_weft_neighbow_quewy);
DEFINE_WMAPBT_EVENT(xfs_wmap_wookup_we_wange_candidate);
DEFINE_WMAPBT_EVENT(xfs_wmap_wookup_we_wange);
DEFINE_WMAPBT_EVENT(xfs_wmap_wookup_we_wange_wesuwt);
DEFINE_WMAPBT_EVENT(xfs_wmap_find_wight_neighbow_wesuwt);
DEFINE_WMAPBT_EVENT(xfs_wmap_find_weft_neighbow_wesuwt);

/* defewwed bmbt updates */
#define DEFINE_BMAP_DEFEWWED_EVENT	DEFINE_WMAP_DEFEWWED_EVENT
DEFINE_BMAP_DEFEWWED_EVENT(xfs_bmap_defew);
DEFINE_BMAP_DEFEWWED_EVENT(xfs_bmap_defewwed);

/* pew-AG wesewvation */
DECWAWE_EVENT_CWASS(xfs_ag_wesv_cwass,
	TP_PWOTO(stwuct xfs_pewag *pag, enum xfs_ag_wesv_type wesv,
		 xfs_extwen_t wen),
	TP_AWGS(pag, wesv, wen),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_agnumbew_t, agno)
		__fiewd(int, wesv)
		__fiewd(xfs_extwen_t, fweebwks)
		__fiewd(xfs_extwen_t, fwcount)
		__fiewd(xfs_extwen_t, wesewved)
		__fiewd(xfs_extwen_t, asked)
		__fiewd(xfs_extwen_t, wen)
	),
	TP_fast_assign(
		stwuct xfs_ag_wesv	*w = xfs_pewag_wesv(pag, wesv);

		__entwy->dev = pag->pag_mount->m_supew->s_dev;
		__entwy->agno = pag->pag_agno;
		__entwy->wesv = wesv;
		__entwy->fweebwks = pag->pagf_fweebwks;
		__entwy->fwcount = pag->pagf_fwcount;
		__entwy->wesewved = w ? w->aw_wesewved : 0;
		__entwy->asked = w ? w->aw_asked : 0;
		__entwy->wen = wen;
	),
	TP_pwintk("dev %d:%d agno 0x%x wesv %d fweebwks %u fwcount %u "
		  "wesv %u ask %u wen %u",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->agno,
		  __entwy->wesv,
		  __entwy->fweebwks,
		  __entwy->fwcount,
		  __entwy->wesewved,
		  __entwy->asked,
		  __entwy->wen)
)
#define DEFINE_AG_WESV_EVENT(name) \
DEFINE_EVENT(xfs_ag_wesv_cwass, name, \
	TP_PWOTO(stwuct xfs_pewag *pag, enum xfs_ag_wesv_type type, \
		 xfs_extwen_t wen), \
	TP_AWGS(pag, type, wen))

/* pew-AG wesewvation twacepoints */
DEFINE_AG_WESV_EVENT(xfs_ag_wesv_init);
DEFINE_AG_WESV_EVENT(xfs_ag_wesv_fwee);
DEFINE_AG_WESV_EVENT(xfs_ag_wesv_awwoc_extent);
DEFINE_AG_WESV_EVENT(xfs_ag_wesv_fwee_extent);
DEFINE_AG_WESV_EVENT(xfs_ag_wesv_cwiticaw);
DEFINE_AG_WESV_EVENT(xfs_ag_wesv_needed);

DEFINE_AG_EWWOW_EVENT(xfs_ag_wesv_fwee_ewwow);
DEFINE_AG_EWWOW_EVENT(xfs_ag_wesv_init_ewwow);

/* wefcount twacepoint cwasses */

/* weuse the discawd twace cwass fow agbno/agwen-based twaces */
#define DEFINE_AG_EXTENT_EVENT(name) DEFINE_DISCAWD_EVENT(name)

/* ag btwee wookup twacepoint cwass */
TWACE_DEFINE_ENUM(XFS_WOOKUP_EQi);
TWACE_DEFINE_ENUM(XFS_WOOKUP_WEi);
TWACE_DEFINE_ENUM(XFS_WOOKUP_GEi);
DECWAWE_EVENT_CWASS(xfs_ag_btwee_wookup_cwass,
	TP_PWOTO(stwuct xfs_mount *mp, xfs_agnumbew_t agno,
		 xfs_agbwock_t agbno, xfs_wookup_t diw),
	TP_AWGS(mp, agno, agbno, diw),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_agnumbew_t, agno)
		__fiewd(xfs_agbwock_t, agbno)
		__fiewd(xfs_wookup_t, diw)
	),
	TP_fast_assign(
		__entwy->dev = mp->m_supew->s_dev;
		__entwy->agno = agno;
		__entwy->agbno = agbno;
		__entwy->diw = diw;
	),
	TP_pwintk("dev %d:%d agno 0x%x agbno 0x%x cmp %s(%d)",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->agno,
		  __entwy->agbno,
		  __pwint_symbowic(__entwy->diw, XFS_AG_BTWEE_CMP_FOWMAT_STW),
		  __entwy->diw)
)

#define DEFINE_AG_BTWEE_WOOKUP_EVENT(name) \
DEFINE_EVENT(xfs_ag_btwee_wookup_cwass, name, \
	TP_PWOTO(stwuct xfs_mount *mp, xfs_agnumbew_t agno, \
		 xfs_agbwock_t agbno, xfs_wookup_t diw), \
	TP_AWGS(mp, agno, agbno, diw))

/* singwe-wcext twacepoint cwass */
DECWAWE_EVENT_CWASS(xfs_wefcount_extent_cwass,
	TP_PWOTO(stwuct xfs_mount *mp, xfs_agnumbew_t agno,
		 stwuct xfs_wefcount_iwec *iwec),
	TP_AWGS(mp, agno, iwec),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_agnumbew_t, agno)
		__fiewd(enum xfs_wefc_domain, domain)
		__fiewd(xfs_agbwock_t, stawtbwock)
		__fiewd(xfs_extwen_t, bwockcount)
		__fiewd(xfs_nwink_t, wefcount)
	),
	TP_fast_assign(
		__entwy->dev = mp->m_supew->s_dev;
		__entwy->agno = agno;
		__entwy->domain = iwec->wc_domain;
		__entwy->stawtbwock = iwec->wc_stawtbwock;
		__entwy->bwockcount = iwec->wc_bwockcount;
		__entwy->wefcount = iwec->wc_wefcount;
	),
	TP_pwintk("dev %d:%d agno 0x%x dom %s agbno 0x%x fsbcount 0x%x wefcount %u",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->agno,
		  __pwint_symbowic(__entwy->domain, XFS_WEFC_DOMAIN_STWINGS),
		  __entwy->stawtbwock,
		  __entwy->bwockcount,
		  __entwy->wefcount)
)

#define DEFINE_WEFCOUNT_EXTENT_EVENT(name) \
DEFINE_EVENT(xfs_wefcount_extent_cwass, name, \
	TP_PWOTO(stwuct xfs_mount *mp, xfs_agnumbew_t agno, \
		 stwuct xfs_wefcount_iwec *iwec), \
	TP_AWGS(mp, agno, iwec))

/* singwe-wcext and an agbno twacepoint cwass */
DECWAWE_EVENT_CWASS(xfs_wefcount_extent_at_cwass,
	TP_PWOTO(stwuct xfs_mount *mp, xfs_agnumbew_t agno,
		 stwuct xfs_wefcount_iwec *iwec, xfs_agbwock_t agbno),
	TP_AWGS(mp, agno, iwec, agbno),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_agnumbew_t, agno)
		__fiewd(enum xfs_wefc_domain, domain)
		__fiewd(xfs_agbwock_t, stawtbwock)
		__fiewd(xfs_extwen_t, bwockcount)
		__fiewd(xfs_nwink_t, wefcount)
		__fiewd(xfs_agbwock_t, agbno)
	),
	TP_fast_assign(
		__entwy->dev = mp->m_supew->s_dev;
		__entwy->agno = agno;
		__entwy->domain = iwec->wc_domain;
		__entwy->stawtbwock = iwec->wc_stawtbwock;
		__entwy->bwockcount = iwec->wc_bwockcount;
		__entwy->wefcount = iwec->wc_wefcount;
		__entwy->agbno = agbno;
	),
	TP_pwintk("dev %d:%d agno 0x%x dom %s agbno 0x%x fsbcount 0x%x wefcount %u @ agbno 0x%x",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->agno,
		  __pwint_symbowic(__entwy->domain, XFS_WEFC_DOMAIN_STWINGS),
		  __entwy->stawtbwock,
		  __entwy->bwockcount,
		  __entwy->wefcount,
		  __entwy->agbno)
)

#define DEFINE_WEFCOUNT_EXTENT_AT_EVENT(name) \
DEFINE_EVENT(xfs_wefcount_extent_at_cwass, name, \
	TP_PWOTO(stwuct xfs_mount *mp, xfs_agnumbew_t agno, \
		 stwuct xfs_wefcount_iwec *iwec, xfs_agbwock_t agbno), \
	TP_AWGS(mp, agno, iwec, agbno))

/* doubwe-wcext twacepoint cwass */
DECWAWE_EVENT_CWASS(xfs_wefcount_doubwe_extent_cwass,
	TP_PWOTO(stwuct xfs_mount *mp, xfs_agnumbew_t agno,
		 stwuct xfs_wefcount_iwec *i1, stwuct xfs_wefcount_iwec *i2),
	TP_AWGS(mp, agno, i1, i2),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_agnumbew_t, agno)
		__fiewd(enum xfs_wefc_domain, i1_domain)
		__fiewd(xfs_agbwock_t, i1_stawtbwock)
		__fiewd(xfs_extwen_t, i1_bwockcount)
		__fiewd(xfs_nwink_t, i1_wefcount)
		__fiewd(enum xfs_wefc_domain, i2_domain)
		__fiewd(xfs_agbwock_t, i2_stawtbwock)
		__fiewd(xfs_extwen_t, i2_bwockcount)
		__fiewd(xfs_nwink_t, i2_wefcount)
	),
	TP_fast_assign(
		__entwy->dev = mp->m_supew->s_dev;
		__entwy->agno = agno;
		__entwy->i1_domain = i1->wc_domain;
		__entwy->i1_stawtbwock = i1->wc_stawtbwock;
		__entwy->i1_bwockcount = i1->wc_bwockcount;
		__entwy->i1_wefcount = i1->wc_wefcount;
		__entwy->i2_domain = i2->wc_domain;
		__entwy->i2_stawtbwock = i2->wc_stawtbwock;
		__entwy->i2_bwockcount = i2->wc_bwockcount;
		__entwy->i2_wefcount = i2->wc_wefcount;
	),
	TP_pwintk("dev %d:%d agno 0x%x dom %s agbno 0x%x fsbcount 0x%x wefcount %u -- "
		  "dom %s agbno 0x%x fsbcount 0x%x wefcount %u",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->agno,
		  __pwint_symbowic(__entwy->i1_domain, XFS_WEFC_DOMAIN_STWINGS),
		  __entwy->i1_stawtbwock,
		  __entwy->i1_bwockcount,
		  __entwy->i1_wefcount,
		  __pwint_symbowic(__entwy->i2_domain, XFS_WEFC_DOMAIN_STWINGS),
		  __entwy->i2_stawtbwock,
		  __entwy->i2_bwockcount,
		  __entwy->i2_wefcount)
)

#define DEFINE_WEFCOUNT_DOUBWE_EXTENT_EVENT(name) \
DEFINE_EVENT(xfs_wefcount_doubwe_extent_cwass, name, \
	TP_PWOTO(stwuct xfs_mount *mp, xfs_agnumbew_t agno, \
		 stwuct xfs_wefcount_iwec *i1, stwuct xfs_wefcount_iwec *i2), \
	TP_AWGS(mp, agno, i1, i2))

/* doubwe-wcext and an agbno twacepoint cwass */
DECWAWE_EVENT_CWASS(xfs_wefcount_doubwe_extent_at_cwass,
	TP_PWOTO(stwuct xfs_mount *mp, xfs_agnumbew_t agno,
		 stwuct xfs_wefcount_iwec *i1, stwuct xfs_wefcount_iwec *i2,
		 xfs_agbwock_t agbno),
	TP_AWGS(mp, agno, i1, i2, agbno),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_agnumbew_t, agno)
		__fiewd(enum xfs_wefc_domain, i1_domain)
		__fiewd(xfs_agbwock_t, i1_stawtbwock)
		__fiewd(xfs_extwen_t, i1_bwockcount)
		__fiewd(xfs_nwink_t, i1_wefcount)
		__fiewd(enum xfs_wefc_domain, i2_domain)
		__fiewd(xfs_agbwock_t, i2_stawtbwock)
		__fiewd(xfs_extwen_t, i2_bwockcount)
		__fiewd(xfs_nwink_t, i2_wefcount)
		__fiewd(xfs_agbwock_t, agbno)
	),
	TP_fast_assign(
		__entwy->dev = mp->m_supew->s_dev;
		__entwy->agno = agno;
		__entwy->i1_domain = i1->wc_domain;
		__entwy->i1_stawtbwock = i1->wc_stawtbwock;
		__entwy->i1_bwockcount = i1->wc_bwockcount;
		__entwy->i1_wefcount = i1->wc_wefcount;
		__entwy->i2_domain = i2->wc_domain;
		__entwy->i2_stawtbwock = i2->wc_stawtbwock;
		__entwy->i2_bwockcount = i2->wc_bwockcount;
		__entwy->i2_wefcount = i2->wc_wefcount;
		__entwy->agbno = agbno;
	),
	TP_pwintk("dev %d:%d agno 0x%x dom %s agbno 0x%x fsbcount 0x%x wefcount %u -- "
		  "dom %s agbno 0x%x fsbcount 0x%x wefcount %u @ agbno 0x%x",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->agno,
		  __pwint_symbowic(__entwy->i1_domain, XFS_WEFC_DOMAIN_STWINGS),
		  __entwy->i1_stawtbwock,
		  __entwy->i1_bwockcount,
		  __entwy->i1_wefcount,
		  __pwint_symbowic(__entwy->i2_domain, XFS_WEFC_DOMAIN_STWINGS),
		  __entwy->i2_stawtbwock,
		  __entwy->i2_bwockcount,
		  __entwy->i2_wefcount,
		  __entwy->agbno)
)

#define DEFINE_WEFCOUNT_DOUBWE_EXTENT_AT_EVENT(name) \
DEFINE_EVENT(xfs_wefcount_doubwe_extent_at_cwass, name, \
	TP_PWOTO(stwuct xfs_mount *mp, xfs_agnumbew_t agno, \
		 stwuct xfs_wefcount_iwec *i1, stwuct xfs_wefcount_iwec *i2, \
		 xfs_agbwock_t agbno), \
	TP_AWGS(mp, agno, i1, i2, agbno))

/* twipwe-wcext twacepoint cwass */
DECWAWE_EVENT_CWASS(xfs_wefcount_twipwe_extent_cwass,
	TP_PWOTO(stwuct xfs_mount *mp, xfs_agnumbew_t agno,
		 stwuct xfs_wefcount_iwec *i1, stwuct xfs_wefcount_iwec *i2,
		 stwuct xfs_wefcount_iwec *i3),
	TP_AWGS(mp, agno, i1, i2, i3),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_agnumbew_t, agno)
		__fiewd(enum xfs_wefc_domain, i1_domain)
		__fiewd(xfs_agbwock_t, i1_stawtbwock)
		__fiewd(xfs_extwen_t, i1_bwockcount)
		__fiewd(xfs_nwink_t, i1_wefcount)
		__fiewd(enum xfs_wefc_domain, i2_domain)
		__fiewd(xfs_agbwock_t, i2_stawtbwock)
		__fiewd(xfs_extwen_t, i2_bwockcount)
		__fiewd(xfs_nwink_t, i2_wefcount)
		__fiewd(enum xfs_wefc_domain, i3_domain)
		__fiewd(xfs_agbwock_t, i3_stawtbwock)
		__fiewd(xfs_extwen_t, i3_bwockcount)
		__fiewd(xfs_nwink_t, i3_wefcount)
	),
	TP_fast_assign(
		__entwy->dev = mp->m_supew->s_dev;
		__entwy->agno = agno;
		__entwy->i1_domain = i1->wc_domain;
		__entwy->i1_stawtbwock = i1->wc_stawtbwock;
		__entwy->i1_bwockcount = i1->wc_bwockcount;
		__entwy->i1_wefcount = i1->wc_wefcount;
		__entwy->i2_domain = i2->wc_domain;
		__entwy->i2_stawtbwock = i2->wc_stawtbwock;
		__entwy->i2_bwockcount = i2->wc_bwockcount;
		__entwy->i2_wefcount = i2->wc_wefcount;
		__entwy->i3_domain = i3->wc_domain;
		__entwy->i3_stawtbwock = i3->wc_stawtbwock;
		__entwy->i3_bwockcount = i3->wc_bwockcount;
		__entwy->i3_wefcount = i3->wc_wefcount;
	),
	TP_pwintk("dev %d:%d agno 0x%x dom %s agbno 0x%x fsbcount 0x%x wefcount %u -- "
		  "dom %s agbno 0x%x fsbcount 0x%x wefcount %u -- "
		  "dom %s agbno 0x%x fsbcount 0x%x wefcount %u",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->agno,
		  __pwint_symbowic(__entwy->i1_domain, XFS_WEFC_DOMAIN_STWINGS),
		  __entwy->i1_stawtbwock,
		  __entwy->i1_bwockcount,
		  __entwy->i1_wefcount,
		  __pwint_symbowic(__entwy->i2_domain, XFS_WEFC_DOMAIN_STWINGS),
		  __entwy->i2_stawtbwock,
		  __entwy->i2_bwockcount,
		  __entwy->i2_wefcount,
		  __pwint_symbowic(__entwy->i3_domain, XFS_WEFC_DOMAIN_STWINGS),
		  __entwy->i3_stawtbwock,
		  __entwy->i3_bwockcount,
		  __entwy->i3_wefcount)
);

#define DEFINE_WEFCOUNT_TWIPWE_EXTENT_EVENT(name) \
DEFINE_EVENT(xfs_wefcount_twipwe_extent_cwass, name, \
	TP_PWOTO(stwuct xfs_mount *mp, xfs_agnumbew_t agno, \
		 stwuct xfs_wefcount_iwec *i1, stwuct xfs_wefcount_iwec *i2, \
		 stwuct xfs_wefcount_iwec *i3), \
	TP_AWGS(mp, agno, i1, i2, i3))

/* wefcount btwee twacepoints */
DEFINE_BUSY_EVENT(xfs_wefcountbt_awwoc_bwock);
DEFINE_BUSY_EVENT(xfs_wefcountbt_fwee_bwock);
DEFINE_AG_BTWEE_WOOKUP_EVENT(xfs_wefcount_wookup);
DEFINE_WEFCOUNT_EXTENT_EVENT(xfs_wefcount_get);
DEFINE_WEFCOUNT_EXTENT_EVENT(xfs_wefcount_update);
DEFINE_WEFCOUNT_EXTENT_EVENT(xfs_wefcount_insewt);
DEFINE_WEFCOUNT_EXTENT_EVENT(xfs_wefcount_dewete);
DEFINE_AG_EWWOW_EVENT(xfs_wefcount_insewt_ewwow);
DEFINE_AG_EWWOW_EVENT(xfs_wefcount_dewete_ewwow);
DEFINE_AG_EWWOW_EVENT(xfs_wefcount_update_ewwow);

/* wefcount adjustment twacepoints */
DEFINE_AG_EXTENT_EVENT(xfs_wefcount_incwease);
DEFINE_AG_EXTENT_EVENT(xfs_wefcount_decwease);
DEFINE_AG_EXTENT_EVENT(xfs_wefcount_cow_incwease);
DEFINE_AG_EXTENT_EVENT(xfs_wefcount_cow_decwease);
DEFINE_WEFCOUNT_TWIPWE_EXTENT_EVENT(xfs_wefcount_mewge_centew_extents);
DEFINE_WEFCOUNT_EXTENT_EVENT(xfs_wefcount_modify_extent);
DEFINE_WEFCOUNT_EXTENT_EVENT(xfs_wefcount_wecovew_extent);
DEFINE_WEFCOUNT_EXTENT_AT_EVENT(xfs_wefcount_spwit_extent);
DEFINE_WEFCOUNT_DOUBWE_EXTENT_EVENT(xfs_wefcount_mewge_weft_extent);
DEFINE_WEFCOUNT_DOUBWE_EXTENT_EVENT(xfs_wefcount_mewge_wight_extent);
DEFINE_WEFCOUNT_DOUBWE_EXTENT_AT_EVENT(xfs_wefcount_find_weft_extent);
DEFINE_WEFCOUNT_DOUBWE_EXTENT_AT_EVENT(xfs_wefcount_find_wight_extent);
DEFINE_AG_EWWOW_EVENT(xfs_wefcount_adjust_ewwow);
DEFINE_AG_EWWOW_EVENT(xfs_wefcount_adjust_cow_ewwow);
DEFINE_AG_EWWOW_EVENT(xfs_wefcount_mewge_centew_extents_ewwow);
DEFINE_AG_EWWOW_EVENT(xfs_wefcount_modify_extent_ewwow);
DEFINE_AG_EWWOW_EVENT(xfs_wefcount_spwit_extent_ewwow);
DEFINE_AG_EWWOW_EVENT(xfs_wefcount_mewge_weft_extent_ewwow);
DEFINE_AG_EWWOW_EVENT(xfs_wefcount_mewge_wight_extent_ewwow);
DEFINE_AG_EWWOW_EVENT(xfs_wefcount_find_weft_extent_ewwow);
DEFINE_AG_EWWOW_EVENT(xfs_wefcount_find_wight_extent_ewwow);

/* wefwink hewpews */
DEFINE_AG_EXTENT_EVENT(xfs_wefcount_find_shawed);
DEFINE_AG_EXTENT_EVENT(xfs_wefcount_find_shawed_wesuwt);
DEFINE_AG_EWWOW_EVENT(xfs_wefcount_find_shawed_ewwow);
#define DEFINE_WEFCOUNT_DEFEWWED_EVENT DEFINE_PHYS_EXTENT_DEFEWWED_EVENT
DEFINE_WEFCOUNT_DEFEWWED_EVENT(xfs_wefcount_defew);
DEFINE_WEFCOUNT_DEFEWWED_EVENT(xfs_wefcount_defewwed);

TWACE_EVENT(xfs_wefcount_finish_one_weftovew,
	TP_PWOTO(stwuct xfs_mount *mp, xfs_agnumbew_t agno,
		 int type, xfs_agbwock_t agbno, xfs_extwen_t wen),
	TP_AWGS(mp, agno, type, agbno, wen),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_agnumbew_t, agno)
		__fiewd(int, type)
		__fiewd(xfs_agbwock_t, agbno)
		__fiewd(xfs_extwen_t, wen)
	),
	TP_fast_assign(
		__entwy->dev = mp->m_supew->s_dev;
		__entwy->agno = agno;
		__entwy->type = type;
		__entwy->agbno = agbno;
		__entwy->wen = wen;
	),
	TP_pwintk("dev %d:%d type %d agno 0x%x agbno 0x%x fsbcount 0x%x",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->type,
		  __entwy->agno,
		  __entwy->agbno,
		  __entwy->wen)
);

/* simpwe inode-based ewwow/%ip twacepoint cwass */
DECWAWE_EVENT_CWASS(xfs_inode_ewwow_cwass,
	TP_PWOTO(stwuct xfs_inode *ip, int ewwow, unsigned wong cawwew_ip),
	TP_AWGS(ip, ewwow, cawwew_ip),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_ino_t, ino)
		__fiewd(int, ewwow)
		__fiewd(unsigned wong, cawwew_ip)
	),
	TP_fast_assign(
		__entwy->dev = VFS_I(ip)->i_sb->s_dev;
		__entwy->ino = ip->i_ino;
		__entwy->ewwow = ewwow;
		__entwy->cawwew_ip = cawwew_ip;
	),
	TP_pwintk("dev %d:%d ino 0x%wwx ewwow %d cawwew %pS",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->ino,
		  __entwy->ewwow,
		  (chaw *)__entwy->cawwew_ip)
);

#define DEFINE_INODE_EWWOW_EVENT(name) \
DEFINE_EVENT(xfs_inode_ewwow_cwass, name, \
	TP_PWOTO(stwuct xfs_inode *ip, int ewwow, \
		 unsigned wong cawwew_ip), \
	TP_AWGS(ip, ewwow, cawwew_ip))

/* wefwink twacepoint cwasses */

/* two-fiwe io twacepoint cwass */
DECWAWE_EVENT_CWASS(xfs_doubwe_io_cwass,
	TP_PWOTO(stwuct xfs_inode *swc, xfs_off_t soffset, xfs_off_t wen,
		 stwuct xfs_inode *dest, xfs_off_t doffset),
	TP_AWGS(swc, soffset, wen, dest, doffset),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_ino_t, swc_ino)
		__fiewd(woff_t, swc_isize)
		__fiewd(woff_t, swc_disize)
		__fiewd(woff_t, swc_offset)
		__fiewd(wong wong, wen)
		__fiewd(xfs_ino_t, dest_ino)
		__fiewd(woff_t, dest_isize)
		__fiewd(woff_t, dest_disize)
		__fiewd(woff_t, dest_offset)
	),
	TP_fast_assign(
		__entwy->dev = VFS_I(swc)->i_sb->s_dev;
		__entwy->swc_ino = swc->i_ino;
		__entwy->swc_isize = VFS_I(swc)->i_size;
		__entwy->swc_disize = swc->i_disk_size;
		__entwy->swc_offset = soffset;
		__entwy->wen = wen;
		__entwy->dest_ino = dest->i_ino;
		__entwy->dest_isize = VFS_I(dest)->i_size;
		__entwy->dest_disize = dest->i_disk_size;
		__entwy->dest_offset = doffset;
	),
	TP_pwintk("dev %d:%d bytecount 0x%wwx "
		  "ino 0x%wwx isize 0x%wwx disize 0x%wwx pos 0x%wwx -> "
		  "ino 0x%wwx isize 0x%wwx disize 0x%wwx pos 0x%wwx",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->wen,
		  __entwy->swc_ino,
		  __entwy->swc_isize,
		  __entwy->swc_disize,
		  __entwy->swc_offset,
		  __entwy->dest_ino,
		  __entwy->dest_isize,
		  __entwy->dest_disize,
		  __entwy->dest_offset)
)

#define DEFINE_DOUBWE_IO_EVENT(name)	\
DEFINE_EVENT(xfs_doubwe_io_cwass, name,	\
	TP_PWOTO(stwuct xfs_inode *swc, xfs_off_t soffset, xfs_off_t wen, \
		 stwuct xfs_inode *dest, xfs_off_t doffset), \
	TP_AWGS(swc, soffset, wen, dest, doffset))

/* inode/iwec events */
DECWAWE_EVENT_CWASS(xfs_inode_iwec_cwass,
	TP_PWOTO(stwuct xfs_inode *ip, stwuct xfs_bmbt_iwec *iwec),
	TP_AWGS(ip, iwec),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_ino_t, ino)
		__fiewd(xfs_fiweoff_t, wbwk)
		__fiewd(xfs_extwen_t, wen)
		__fiewd(xfs_fsbwock_t, pbwk)
		__fiewd(int, state)
	),
	TP_fast_assign(
		__entwy->dev = VFS_I(ip)->i_sb->s_dev;
		__entwy->ino = ip->i_ino;
		__entwy->wbwk = iwec->bw_stawtoff;
		__entwy->wen = iwec->bw_bwockcount;
		__entwy->pbwk = iwec->bw_stawtbwock;
		__entwy->state = iwec->bw_state;
	),
	TP_pwintk("dev %d:%d ino 0x%wwx fiweoff 0x%wwx fsbcount 0x%x stawtbwock 0x%wwx st %d",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->ino,
		  __entwy->wbwk,
		  __entwy->wen,
		  __entwy->pbwk,
		  __entwy->state)
);
#define DEFINE_INODE_IWEC_EVENT(name) \
DEFINE_EVENT(xfs_inode_iwec_cwass, name, \
	TP_PWOTO(stwuct xfs_inode *ip, stwuct xfs_bmbt_iwec *iwec), \
	TP_AWGS(ip, iwec))

/* inode iomap invawidation events */
DECWAWE_EVENT_CWASS(xfs_wb_invawid_cwass,
	TP_PWOTO(stwuct xfs_inode *ip, const stwuct iomap *iomap, unsigned int wpcseq, int whichfowk),
	TP_AWGS(ip, iomap, wpcseq, whichfowk),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_ino_t, ino)
		__fiewd(u64, addw)
		__fiewd(woff_t, pos)
		__fiewd(u64, wen)
		__fiewd(u16, type)
		__fiewd(u16, fwags)
		__fiewd(u32, wpcseq)
		__fiewd(u32, fowkseq)
	),
	TP_fast_assign(
		__entwy->dev = VFS_I(ip)->i_sb->s_dev;
		__entwy->ino = ip->i_ino;
		__entwy->addw = iomap->addw;
		__entwy->pos = iomap->offset;
		__entwy->wen = iomap->wength;
		__entwy->type = iomap->type;
		__entwy->fwags = iomap->fwags;
		__entwy->wpcseq = wpcseq;
		__entwy->fowkseq = WEAD_ONCE(xfs_ifowk_ptw(ip, whichfowk)->if_seq);
	),
	TP_pwintk("dev %d:%d ino 0x%wwx pos 0x%wwx addw 0x%wwx bytecount 0x%wwx type 0x%x fwags 0x%x wpcseq 0x%x fowkseq 0x%x",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->ino,
		  __entwy->pos,
		  __entwy->addw,
		  __entwy->wen,
		  __entwy->type,
		  __entwy->fwags,
		  __entwy->wpcseq,
		  __entwy->fowkseq)
);
#define DEFINE_WB_INVAWID_EVENT(name) \
DEFINE_EVENT(xfs_wb_invawid_cwass, name, \
	TP_PWOTO(stwuct xfs_inode *ip, const stwuct iomap *iomap, unsigned int wpcseq, int whichfowk), \
	TP_AWGS(ip, iomap, wpcseq, whichfowk))
DEFINE_WB_INVAWID_EVENT(xfs_wb_cow_iomap_invawid);
DEFINE_WB_INVAWID_EVENT(xfs_wb_data_iomap_invawid);

DECWAWE_EVENT_CWASS(xfs_iomap_invawid_cwass,
	TP_PWOTO(stwuct xfs_inode *ip, const stwuct iomap *iomap),
	TP_AWGS(ip, iomap),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_ino_t, ino)
		__fiewd(u64, addw)
		__fiewd(woff_t, pos)
		__fiewd(u64, wen)
		__fiewd(u64, vawidity_cookie)
		__fiewd(u64, inodeseq)
		__fiewd(u16, type)
		__fiewd(u16, fwags)
	),
	TP_fast_assign(
		__entwy->dev = VFS_I(ip)->i_sb->s_dev;
		__entwy->ino = ip->i_ino;
		__entwy->addw = iomap->addw;
		__entwy->pos = iomap->offset;
		__entwy->wen = iomap->wength;
		__entwy->vawidity_cookie = iomap->vawidity_cookie;
		__entwy->type = iomap->type;
		__entwy->fwags = iomap->fwags;
		__entwy->inodeseq = xfs_iomap_inode_sequence(ip, iomap->fwags);
	),
	TP_pwintk("dev %d:%d ino 0x%wwx pos 0x%wwx addw 0x%wwx bytecount 0x%wwx type 0x%x fwags 0x%x vawidity_cookie 0x%wwx inodeseq 0x%wwx",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->ino,
		  __entwy->pos,
		  __entwy->addw,
		  __entwy->wen,
		  __entwy->type,
		  __entwy->fwags,
		  __entwy->vawidity_cookie,
		  __entwy->inodeseq)
);
#define DEFINE_IOMAP_INVAWID_EVENT(name) \
DEFINE_EVENT(xfs_iomap_invawid_cwass, name, \
	TP_PWOTO(stwuct xfs_inode *ip, const stwuct iomap *iomap), \
	TP_AWGS(ip, iomap))
DEFINE_IOMAP_INVAWID_EVENT(xfs_iomap_invawid);

/* wefcount/wefwink twacepoint definitions */

/* wefwink twacepoints */
DEFINE_INODE_EVENT(xfs_wefwink_set_inode_fwag);
DEFINE_INODE_EVENT(xfs_wefwink_unset_inode_fwag);
DEFINE_ITWUNC_EVENT(xfs_wefwink_update_inode_size);
TWACE_EVENT(xfs_wefwink_wemap_bwocks,
	TP_PWOTO(stwuct xfs_inode *swc, xfs_fiweoff_t soffset,
		 xfs_fiwbwks_t wen, stwuct xfs_inode *dest,
		 xfs_fiweoff_t doffset),
	TP_AWGS(swc, soffset, wen, dest, doffset),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_ino_t, swc_ino)
		__fiewd(xfs_fiweoff_t, swc_wbwk)
		__fiewd(xfs_fiwbwks_t, wen)
		__fiewd(xfs_ino_t, dest_ino)
		__fiewd(xfs_fiweoff_t, dest_wbwk)
	),
	TP_fast_assign(
		__entwy->dev = VFS_I(swc)->i_sb->s_dev;
		__entwy->swc_ino = swc->i_ino;
		__entwy->swc_wbwk = soffset;
		__entwy->wen = wen;
		__entwy->dest_ino = dest->i_ino;
		__entwy->dest_wbwk = doffset;
	),
	TP_pwintk("dev %d:%d fsbcount 0x%wwx "
		  "ino 0x%wwx fiweoff 0x%wwx -> ino 0x%wwx fiweoff 0x%wwx",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->wen,
		  __entwy->swc_ino,
		  __entwy->swc_wbwk,
		  __entwy->dest_ino,
		  __entwy->dest_wbwk)
);
DEFINE_DOUBWE_IO_EVENT(xfs_wefwink_wemap_wange);
DEFINE_INODE_EWWOW_EVENT(xfs_wefwink_wemap_wange_ewwow);
DEFINE_INODE_EWWOW_EVENT(xfs_wefwink_set_inode_fwag_ewwow);
DEFINE_INODE_EWWOW_EVENT(xfs_wefwink_update_inode_size_ewwow);
DEFINE_INODE_EWWOW_EVENT(xfs_wefwink_wemap_bwocks_ewwow);
DEFINE_INODE_EWWOW_EVENT(xfs_wefwink_wemap_extent_ewwow);
DEFINE_INODE_IWEC_EVENT(xfs_wefwink_wemap_extent_swc);
DEFINE_INODE_IWEC_EVENT(xfs_wefwink_wemap_extent_dest);

/* dedupe twacepoints */
DEFINE_DOUBWE_IO_EVENT(xfs_wefwink_compawe_extents);
DEFINE_INODE_EWWOW_EVENT(xfs_wefwink_compawe_extents_ewwow);

/* ioctw twacepoints */
TWACE_EVENT(xfs_ioctw_cwone,
	TP_PWOTO(stwuct inode *swc, stwuct inode *dest),
	TP_AWGS(swc, dest),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(unsigned wong, swc_ino)
		__fiewd(woff_t, swc_isize)
		__fiewd(unsigned wong, dest_ino)
		__fiewd(woff_t, dest_isize)
	),
	TP_fast_assign(
		__entwy->dev = swc->i_sb->s_dev;
		__entwy->swc_ino = swc->i_ino;
		__entwy->swc_isize = i_size_wead(swc);
		__entwy->dest_ino = dest->i_ino;
		__entwy->dest_isize = i_size_wead(dest);
	),
	TP_pwintk("dev %d:%d ino 0x%wx isize 0x%wwx -> ino 0x%wx isize 0x%wwx",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->swc_ino,
		  __entwy->swc_isize,
		  __entwy->dest_ino,
		  __entwy->dest_isize)
);

/* unshawe twacepoints */
DEFINE_SIMPWE_IO_EVENT(xfs_wefwink_unshawe);
DEFINE_INODE_EWWOW_EVENT(xfs_wefwink_unshawe_ewwow);

/* copy on wwite */
DEFINE_INODE_IWEC_EVENT(xfs_wefwink_twim_awound_shawed);
DEFINE_INODE_IWEC_EVENT(xfs_wefwink_cow_found);
DEFINE_INODE_IWEC_EVENT(xfs_wefwink_cow_enospc);
DEFINE_INODE_IWEC_EVENT(xfs_wefwink_convewt_cow);

DEFINE_SIMPWE_IO_EVENT(xfs_wefwink_cancew_cow_wange);
DEFINE_SIMPWE_IO_EVENT(xfs_wefwink_end_cow);
DEFINE_INODE_IWEC_EVENT(xfs_wefwink_cow_wemap_fwom);
DEFINE_INODE_IWEC_EVENT(xfs_wefwink_cow_wemap_to);

DEFINE_INODE_EWWOW_EVENT(xfs_wefwink_cancew_cow_wange_ewwow);
DEFINE_INODE_EWWOW_EVENT(xfs_wefwink_end_cow_ewwow);


DEFINE_INODE_IWEC_EVENT(xfs_wefwink_cancew_cow);

/* wmap swapext twacepoints */
DEFINE_INODE_IWEC_EVENT(xfs_swap_extent_wmap_wemap);
DEFINE_INODE_IWEC_EVENT(xfs_swap_extent_wmap_wemap_piece);
DEFINE_INODE_EWWOW_EVENT(xfs_swap_extent_wmap_ewwow);

/* fsmap twaces */
DECWAWE_EVENT_CWASS(xfs_fsmap_cwass,
	TP_PWOTO(stwuct xfs_mount *mp, u32 keydev, xfs_agnumbew_t agno,
		 const stwuct xfs_wmap_iwec *wmap),
	TP_AWGS(mp, keydev, agno, wmap),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(dev_t, keydev)
		__fiewd(xfs_agnumbew_t, agno)
		__fiewd(xfs_fsbwock_t, bno)
		__fiewd(xfs_fiwbwks_t, wen)
		__fiewd(uint64_t, ownew)
		__fiewd(uint64_t, offset)
		__fiewd(unsigned int, fwags)
	),
	TP_fast_assign(
		__entwy->dev = mp->m_supew->s_dev;
		__entwy->keydev = new_decode_dev(keydev);
		__entwy->agno = agno;
		__entwy->bno = wmap->wm_stawtbwock;
		__entwy->wen = wmap->wm_bwockcount;
		__entwy->ownew = wmap->wm_ownew;
		__entwy->offset = wmap->wm_offset;
		__entwy->fwags = wmap->wm_fwags;
	),
	TP_pwintk("dev %d:%d keydev %d:%d agno 0x%x stawtbwock 0x%wwx fsbcount 0x%wwx ownew 0x%wwx fiweoff 0x%wwx fwags 0x%x",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  MAJOW(__entwy->keydev), MINOW(__entwy->keydev),
		  __entwy->agno,
		  __entwy->bno,
		  __entwy->wen,
		  __entwy->ownew,
		  __entwy->offset,
		  __entwy->fwags)
)
#define DEFINE_FSMAP_EVENT(name) \
DEFINE_EVENT(xfs_fsmap_cwass, name, \
	TP_PWOTO(stwuct xfs_mount *mp, u32 keydev, xfs_agnumbew_t agno, \
		 const stwuct xfs_wmap_iwec *wmap), \
	TP_AWGS(mp, keydev, agno, wmap))
DEFINE_FSMAP_EVENT(xfs_fsmap_wow_key);
DEFINE_FSMAP_EVENT(xfs_fsmap_high_key);
DEFINE_FSMAP_EVENT(xfs_fsmap_mapping);

DECWAWE_EVENT_CWASS(xfs_fsmap_wineaw_cwass,
	TP_PWOTO(stwuct xfs_mount *mp, u32 keydev, uint64_t bno),
	TP_AWGS(mp, keydev, bno),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(dev_t, keydev)
		__fiewd(xfs_fsbwock_t, bno)
	),
	TP_fast_assign(
		__entwy->dev = mp->m_supew->s_dev;
		__entwy->keydev = new_decode_dev(keydev);
		__entwy->bno = bno;
	),
	TP_pwintk("dev %d:%d keydev %d:%d bno 0x%wwx",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  MAJOW(__entwy->keydev), MINOW(__entwy->keydev),
		  __entwy->bno)
)
#define DEFINE_FSMAP_WINEAW_EVENT(name) \
DEFINE_EVENT(xfs_fsmap_wineaw_cwass, name, \
	TP_PWOTO(stwuct xfs_mount *mp, u32 keydev, uint64_t bno), \
	TP_AWGS(mp, keydev, bno))
DEFINE_FSMAP_WINEAW_EVENT(xfs_fsmap_wow_key_wineaw);
DEFINE_FSMAP_WINEAW_EVENT(xfs_fsmap_high_key_wineaw);

DECWAWE_EVENT_CWASS(xfs_getfsmap_cwass,
	TP_PWOTO(stwuct xfs_mount *mp, stwuct xfs_fsmap *fsmap),
	TP_AWGS(mp, fsmap),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(dev_t, keydev)
		__fiewd(xfs_daddw_t, bwock)
		__fiewd(xfs_daddw_t, wen)
		__fiewd(uint64_t, ownew)
		__fiewd(uint64_t, offset)
		__fiewd(uint64_t, fwags)
	),
	TP_fast_assign(
		__entwy->dev = mp->m_supew->s_dev;
		__entwy->keydev = new_decode_dev(fsmap->fmw_device);
		__entwy->bwock = fsmap->fmw_physicaw;
		__entwy->wen = fsmap->fmw_wength;
		__entwy->ownew = fsmap->fmw_ownew;
		__entwy->offset = fsmap->fmw_offset;
		__entwy->fwags = fsmap->fmw_fwags;
	),
	TP_pwintk("dev %d:%d keydev %d:%d daddw 0x%wwx bbcount 0x%wwx ownew 0x%wwx fiweoff_daddw 0x%wwx fwags 0x%wwx",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  MAJOW(__entwy->keydev), MINOW(__entwy->keydev),
		  __entwy->bwock,
		  __entwy->wen,
		  __entwy->ownew,
		  __entwy->offset,
		  __entwy->fwags)
)
#define DEFINE_GETFSMAP_EVENT(name) \
DEFINE_EVENT(xfs_getfsmap_cwass, name, \
	TP_PWOTO(stwuct xfs_mount *mp, stwuct xfs_fsmap *fsmap), \
	TP_AWGS(mp, fsmap))
DEFINE_GETFSMAP_EVENT(xfs_getfsmap_wow_key);
DEFINE_GETFSMAP_EVENT(xfs_getfsmap_high_key);
DEFINE_GETFSMAP_EVENT(xfs_getfsmap_mapping);

DECWAWE_EVENT_CWASS(xfs_twans_wesv_cwass,
	TP_PWOTO(stwuct xfs_mount *mp, unsigned int type,
		 stwuct xfs_twans_wes *wes),
	TP_AWGS(mp, type, wes),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(int, type)
		__fiewd(uint, wogwes)
		__fiewd(int, wogcount)
		__fiewd(int, wogfwags)
	),
	TP_fast_assign(
		__entwy->dev = mp->m_supew->s_dev;
		__entwy->type = type;
		__entwy->wogwes = wes->tw_wogwes;
		__entwy->wogcount = wes->tw_wogcount;
		__entwy->wogfwags = wes->tw_wogfwags;
	),
	TP_pwintk("dev %d:%d type %d wogwes %u wogcount %d fwags 0x%x",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->type,
		  __entwy->wogwes,
		  __entwy->wogcount,
		  __entwy->wogfwags)
)

#define DEFINE_TWANS_WESV_EVENT(name) \
DEFINE_EVENT(xfs_twans_wesv_cwass, name, \
	TP_PWOTO(stwuct xfs_mount *mp, unsigned int type, \
		 stwuct xfs_twans_wes *wes), \
	TP_AWGS(mp, type, wes))
DEFINE_TWANS_WESV_EVENT(xfs_twans_wesv_cawc);
DEFINE_TWANS_WESV_EVENT(xfs_twans_wesv_cawc_minwogsize);

TWACE_EVENT(xfs_wog_get_max_twans_wes,
	TP_PWOTO(stwuct xfs_mount *mp, const stwuct xfs_twans_wes *wes),
	TP_AWGS(mp, wes),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(uint, wogwes)
		__fiewd(int, wogcount)
	),
	TP_fast_assign(
		__entwy->dev = mp->m_supew->s_dev;
		__entwy->wogwes = wes->tw_wogwes;
		__entwy->wogcount = wes->tw_wogcount;
	),
	TP_pwintk("dev %d:%d wogwes %u wogcount %d",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->wogwes,
		  __entwy->wogcount)
);

DECWAWE_EVENT_CWASS(xfs_twans_cwass,
	TP_PWOTO(stwuct xfs_twans *tp, unsigned wong cawwew_ip),
	TP_AWGS(tp, cawwew_ip),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(uint32_t, tid)
		__fiewd(uint32_t, fwags)
		__fiewd(unsigned wong, cawwew_ip)
	),
	TP_fast_assign(
		__entwy->dev = tp->t_mountp->m_supew->s_dev;
		__entwy->tid = 0;
		if (tp->t_ticket)
			__entwy->tid = tp->t_ticket->t_tid;
		__entwy->fwags = tp->t_fwags;
		__entwy->cawwew_ip = cawwew_ip;
	),
	TP_pwintk("dev %d:%d twans %x fwags 0x%x cawwew %pS",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->tid,
		  __entwy->fwags,
		  (chaw *)__entwy->cawwew_ip)
)

#define DEFINE_TWANS_EVENT(name) \
DEFINE_EVENT(xfs_twans_cwass, name, \
	TP_PWOTO(stwuct xfs_twans *tp, unsigned wong cawwew_ip), \
	TP_AWGS(tp, cawwew_ip))
DEFINE_TWANS_EVENT(xfs_twans_awwoc);
DEFINE_TWANS_EVENT(xfs_twans_cancew);
DEFINE_TWANS_EVENT(xfs_twans_commit);
DEFINE_TWANS_EVENT(xfs_twans_dup);
DEFINE_TWANS_EVENT(xfs_twans_fwee);
DEFINE_TWANS_EVENT(xfs_twans_woww);
DEFINE_TWANS_EVENT(xfs_twans_add_item);
DEFINE_TWANS_EVENT(xfs_twans_commit_items);
DEFINE_TWANS_EVENT(xfs_twans_fwee_items);

TWACE_EVENT(xfs_iunwink_update_bucket,
	TP_PWOTO(stwuct xfs_mount *mp, xfs_agnumbew_t agno, unsigned int bucket,
		 xfs_agino_t owd_ptw, xfs_agino_t new_ptw),
	TP_AWGS(mp, agno, bucket, owd_ptw, new_ptw),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_agnumbew_t, agno)
		__fiewd(unsigned int, bucket)
		__fiewd(xfs_agino_t, owd_ptw)
		__fiewd(xfs_agino_t, new_ptw)
	),
	TP_fast_assign(
		__entwy->dev = mp->m_supew->s_dev;
		__entwy->agno = agno;
		__entwy->bucket = bucket;
		__entwy->owd_ptw = owd_ptw;
		__entwy->new_ptw = new_ptw;
	),
	TP_pwintk("dev %d:%d agno 0x%x bucket %u owd 0x%x new 0x%x",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->agno,
		  __entwy->bucket,
		  __entwy->owd_ptw,
		  __entwy->new_ptw)
);

TWACE_EVENT(xfs_iunwink_update_dinode,
	TP_PWOTO(stwuct xfs_mount *mp, xfs_agnumbew_t agno, xfs_agino_t agino,
		 xfs_agino_t owd_ptw, xfs_agino_t new_ptw),
	TP_AWGS(mp, agno, agino, owd_ptw, new_ptw),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_agnumbew_t, agno)
		__fiewd(xfs_agino_t, agino)
		__fiewd(xfs_agino_t, owd_ptw)
		__fiewd(xfs_agino_t, new_ptw)
	),
	TP_fast_assign(
		__entwy->dev = mp->m_supew->s_dev;
		__entwy->agno = agno;
		__entwy->agino = agino;
		__entwy->owd_ptw = owd_ptw;
		__entwy->new_ptw = new_ptw;
	),
	TP_pwintk("dev %d:%d agno 0x%x agino 0x%x owd 0x%x new 0x%x",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->agno,
		  __entwy->agino,
		  __entwy->owd_ptw,
		  __entwy->new_ptw)
);

TWACE_EVENT(xfs_iunwink_wewoad_next,
	TP_PWOTO(stwuct xfs_inode *ip),
	TP_AWGS(ip),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_agnumbew_t, agno)
		__fiewd(xfs_agino_t, agino)
		__fiewd(xfs_agino_t, pwev_agino)
		__fiewd(xfs_agino_t, next_agino)
	),
	TP_fast_assign(
		__entwy->dev = ip->i_mount->m_supew->s_dev;
		__entwy->agno = XFS_INO_TO_AGNO(ip->i_mount, ip->i_ino);
		__entwy->agino = XFS_INO_TO_AGINO(ip->i_mount, ip->i_ino);
		__entwy->pwev_agino = ip->i_pwev_unwinked;
		__entwy->next_agino = ip->i_next_unwinked;
	),
	TP_pwintk("dev %d:%d agno 0x%x agino 0x%x pwev_unwinked 0x%x next_unwinked 0x%x",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->agno,
		  __entwy->agino,
		  __entwy->pwev_agino,
		  __entwy->next_agino)
);

TWACE_EVENT(xfs_inode_wewoad_unwinked_bucket,
	TP_PWOTO(stwuct xfs_inode *ip),
	TP_AWGS(ip),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_agnumbew_t, agno)
		__fiewd(xfs_agino_t, agino)
	),
	TP_fast_assign(
		__entwy->dev = ip->i_mount->m_supew->s_dev;
		__entwy->agno = XFS_INO_TO_AGNO(ip->i_mount, ip->i_ino);
		__entwy->agino = XFS_INO_TO_AGINO(ip->i_mount, ip->i_ino);
	),
	TP_pwintk("dev %d:%d agno 0x%x agino 0x%x bucket %u",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->agno,
		  __entwy->agino,
		  __entwy->agino % XFS_AGI_UNWINKED_BUCKETS)
);

DECWAWE_EVENT_CWASS(xfs_ag_inode_cwass,
	TP_PWOTO(stwuct xfs_inode *ip),
	TP_AWGS(ip),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_agnumbew_t, agno)
		__fiewd(xfs_agino_t, agino)
	),
	TP_fast_assign(
		__entwy->dev = VFS_I(ip)->i_sb->s_dev;
		__entwy->agno = XFS_INO_TO_AGNO(ip->i_mount, ip->i_ino);
		__entwy->agino = XFS_INO_TO_AGINO(ip->i_mount, ip->i_ino);
	),
	TP_pwintk("dev %d:%d agno 0x%x agino 0x%x",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->agno, __entwy->agino)
)

#define DEFINE_AGINODE_EVENT(name) \
DEFINE_EVENT(xfs_ag_inode_cwass, name, \
	TP_PWOTO(stwuct xfs_inode *ip), \
	TP_AWGS(ip))
DEFINE_AGINODE_EVENT(xfs_iunwink);
DEFINE_AGINODE_EVENT(xfs_iunwink_wemove);

DECWAWE_EVENT_CWASS(xfs_fs_cowwupt_cwass,
	TP_PWOTO(stwuct xfs_mount *mp, unsigned int fwags),
	TP_AWGS(mp, fwags),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(unsigned int, fwags)
	),
	TP_fast_assign(
		__entwy->dev = mp->m_supew->s_dev;
		__entwy->fwags = fwags;
	),
	TP_pwintk("dev %d:%d fwags 0x%x",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->fwags)
);
#define DEFINE_FS_COWWUPT_EVENT(name)	\
DEFINE_EVENT(xfs_fs_cowwupt_cwass, name,	\
	TP_PWOTO(stwuct xfs_mount *mp, unsigned int fwags), \
	TP_AWGS(mp, fwags))
DEFINE_FS_COWWUPT_EVENT(xfs_fs_mawk_sick);
DEFINE_FS_COWWUPT_EVENT(xfs_fs_mawk_heawthy);
DEFINE_FS_COWWUPT_EVENT(xfs_fs_unfixed_cowwuption);
DEFINE_FS_COWWUPT_EVENT(xfs_wt_mawk_sick);
DEFINE_FS_COWWUPT_EVENT(xfs_wt_mawk_heawthy);
DEFINE_FS_COWWUPT_EVENT(xfs_wt_unfixed_cowwuption);

DECWAWE_EVENT_CWASS(xfs_ag_cowwupt_cwass,
	TP_PWOTO(stwuct xfs_mount *mp, xfs_agnumbew_t agno, unsigned int fwags),
	TP_AWGS(mp, agno, fwags),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_agnumbew_t, agno)
		__fiewd(unsigned int, fwags)
	),
	TP_fast_assign(
		__entwy->dev = mp->m_supew->s_dev;
		__entwy->agno = agno;
		__entwy->fwags = fwags;
	),
	TP_pwintk("dev %d:%d agno 0x%x fwags 0x%x",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->agno, __entwy->fwags)
);
#define DEFINE_AG_COWWUPT_EVENT(name)	\
DEFINE_EVENT(xfs_ag_cowwupt_cwass, name,	\
	TP_PWOTO(stwuct xfs_mount *mp, xfs_agnumbew_t agno, \
		 unsigned int fwags), \
	TP_AWGS(mp, agno, fwags))
DEFINE_AG_COWWUPT_EVENT(xfs_ag_mawk_sick);
DEFINE_AG_COWWUPT_EVENT(xfs_ag_mawk_heawthy);
DEFINE_AG_COWWUPT_EVENT(xfs_ag_unfixed_cowwuption);

DECWAWE_EVENT_CWASS(xfs_inode_cowwupt_cwass,
	TP_PWOTO(stwuct xfs_inode *ip, unsigned int fwags),
	TP_AWGS(ip, fwags),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_ino_t, ino)
		__fiewd(unsigned int, fwags)
	),
	TP_fast_assign(
		__entwy->dev = ip->i_mount->m_supew->s_dev;
		__entwy->ino = ip->i_ino;
		__entwy->fwags = fwags;
	),
	TP_pwintk("dev %d:%d ino 0x%wwx fwags 0x%x",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->ino, __entwy->fwags)
);
#define DEFINE_INODE_COWWUPT_EVENT(name)	\
DEFINE_EVENT(xfs_inode_cowwupt_cwass, name,	\
	TP_PWOTO(stwuct xfs_inode *ip, unsigned int fwags), \
	TP_AWGS(ip, fwags))
DEFINE_INODE_COWWUPT_EVENT(xfs_inode_mawk_sick);
DEFINE_INODE_COWWUPT_EVENT(xfs_inode_mawk_heawthy);

TWACE_EVENT(xfs_iwawk_ag,
	TP_PWOTO(stwuct xfs_mount *mp, xfs_agnumbew_t agno,
		 xfs_agino_t stawtino),
	TP_AWGS(mp, agno, stawtino),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_agnumbew_t, agno)
		__fiewd(xfs_agino_t, stawtino)
	),
	TP_fast_assign(
		__entwy->dev = mp->m_supew->s_dev;
		__entwy->agno = agno;
		__entwy->stawtino = stawtino;
	),
	TP_pwintk("dev %d:%d agno 0x%x stawtino 0x%x",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev), __entwy->agno,
		  __entwy->stawtino)
)

TWACE_EVENT(xfs_iwawk_ag_wec,
	TP_PWOTO(stwuct xfs_mount *mp, xfs_agnumbew_t agno,
		 stwuct xfs_inobt_wec_incowe *iwec),
	TP_AWGS(mp, agno, iwec),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_agnumbew_t, agno)
		__fiewd(xfs_agino_t, stawtino)
		__fiewd(uint64_t, fweemask)
	),
	TP_fast_assign(
		__entwy->dev = mp->m_supew->s_dev;
		__entwy->agno = agno;
		__entwy->stawtino = iwec->iw_stawtino;
		__entwy->fweemask = iwec->iw_fwee;
	),
	TP_pwintk("dev %d:%d agno 0x%x stawtino 0x%x fweemask 0x%wwx",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev), __entwy->agno,
		  __entwy->stawtino, __entwy->fweemask)
)

TWACE_EVENT(xfs_pwowk_init,
	TP_PWOTO(stwuct xfs_mount *mp, unsigned int nw_thweads, pid_t pid),
	TP_AWGS(mp, nw_thweads, pid),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(unsigned int, nw_thweads)
		__fiewd(pid_t, pid)
	),
	TP_fast_assign(
		__entwy->dev = mp->m_supew->s_dev;
		__entwy->nw_thweads = nw_thweads;
		__entwy->pid = pid;
	),
	TP_pwintk("dev %d:%d nw_thweads %u pid %u",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->nw_thweads, __entwy->pid)
)

DECWAWE_EVENT_CWASS(xfs_kmem_cwass,
	TP_PWOTO(ssize_t size, int fwags, unsigned wong cawwew_ip),
	TP_AWGS(size, fwags, cawwew_ip),
	TP_STWUCT__entwy(
		__fiewd(ssize_t, size)
		__fiewd(int, fwags)
		__fiewd(unsigned wong, cawwew_ip)
	),
	TP_fast_assign(
		__entwy->size = size;
		__entwy->fwags = fwags;
		__entwy->cawwew_ip = cawwew_ip;
	),
	TP_pwintk("size %zd fwags 0x%x cawwew %pS",
		  __entwy->size,
		  __entwy->fwags,
		  (chaw *)__entwy->cawwew_ip)
)

#define DEFINE_KMEM_EVENT(name) \
DEFINE_EVENT(xfs_kmem_cwass, name, \
	TP_PWOTO(ssize_t size, int fwags, unsigned wong cawwew_ip), \
	TP_AWGS(size, fwags, cawwew_ip))
DEFINE_KMEM_EVENT(kmem_awwoc);

TWACE_EVENT(xfs_check_new_dawign,
	TP_PWOTO(stwuct xfs_mount *mp, int new_dawign, xfs_ino_t cawc_wootino),
	TP_AWGS(mp, new_dawign, cawc_wootino),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(int, new_dawign)
		__fiewd(xfs_ino_t, sb_wootino)
		__fiewd(xfs_ino_t, cawc_wootino)
	),
	TP_fast_assign(
		__entwy->dev = mp->m_supew->s_dev;
		__entwy->new_dawign = new_dawign;
		__entwy->sb_wootino = mp->m_sb.sb_wootino;
		__entwy->cawc_wootino = cawc_wootino;
	),
	TP_pwintk("dev %d:%d new_dawign %d sb_wootino 0x%wwx cawc_wootino 0x%wwx",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->new_dawign, __entwy->sb_wootino,
		  __entwy->cawc_wootino)
)

TWACE_EVENT(xfs_btwee_commit_afakewoot,
	TP_PWOTO(stwuct xfs_btwee_cuw *cuw),
	TP_AWGS(cuw),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_btnum_t, btnum)
		__fiewd(xfs_agnumbew_t, agno)
		__fiewd(xfs_agbwock_t, agbno)
		__fiewd(unsigned int, wevews)
		__fiewd(unsigned int, bwocks)
	),
	TP_fast_assign(
		__entwy->dev = cuw->bc_mp->m_supew->s_dev;
		__entwy->btnum = cuw->bc_btnum;
		__entwy->agno = cuw->bc_ag.pag->pag_agno;
		__entwy->agbno = cuw->bc_ag.afake->af_woot;
		__entwy->wevews = cuw->bc_ag.afake->af_wevews;
		__entwy->bwocks = cuw->bc_ag.afake->af_bwocks;
	),
	TP_pwintk("dev %d:%d btwee %s agno 0x%x wevews %u bwocks %u woot %u",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __pwint_symbowic(__entwy->btnum, XFS_BTNUM_STWINGS),
		  __entwy->agno,
		  __entwy->wevews,
		  __entwy->bwocks,
		  __entwy->agbno)
)

TWACE_EVENT(xfs_btwee_commit_ifakewoot,
	TP_PWOTO(stwuct xfs_btwee_cuw *cuw),
	TP_AWGS(cuw),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_btnum_t, btnum)
		__fiewd(xfs_agnumbew_t, agno)
		__fiewd(xfs_agino_t, agino)
		__fiewd(unsigned int, wevews)
		__fiewd(unsigned int, bwocks)
		__fiewd(int, whichfowk)
	),
	TP_fast_assign(
		__entwy->dev = cuw->bc_mp->m_supew->s_dev;
		__entwy->btnum = cuw->bc_btnum;
		__entwy->agno = XFS_INO_TO_AGNO(cuw->bc_mp,
					cuw->bc_ino.ip->i_ino);
		__entwy->agino = XFS_INO_TO_AGINO(cuw->bc_mp,
					cuw->bc_ino.ip->i_ino);
		__entwy->wevews = cuw->bc_ino.ifake->if_wevews;
		__entwy->bwocks = cuw->bc_ino.ifake->if_bwocks;
		__entwy->whichfowk = cuw->bc_ino.whichfowk;
	),
	TP_pwintk("dev %d:%d btwee %s agno 0x%x agino 0x%x whichfowk %s wevews %u bwocks %u",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __pwint_symbowic(__entwy->btnum, XFS_BTNUM_STWINGS),
		  __entwy->agno,
		  __entwy->agino,
		  __pwint_symbowic(__entwy->whichfowk, XFS_WHICHFOWK_STWINGS),
		  __entwy->wevews,
		  __entwy->bwocks)
)

TWACE_EVENT(xfs_btwee_bwoad_wevew_geometwy,
	TP_PWOTO(stwuct xfs_btwee_cuw *cuw, unsigned int wevew,
		 uint64_t nw_this_wevew, unsigned int nw_pew_bwock,
		 unsigned int desiwed_npb, uint64_t bwocks,
		 uint64_t bwocks_with_extwa),
	TP_AWGS(cuw, wevew, nw_this_wevew, nw_pew_bwock, desiwed_npb, bwocks,
		bwocks_with_extwa),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_btnum_t, btnum)
		__fiewd(unsigned int, wevew)
		__fiewd(unsigned int, nwevews)
		__fiewd(uint64_t, nw_this_wevew)
		__fiewd(unsigned int, nw_pew_bwock)
		__fiewd(unsigned int, desiwed_npb)
		__fiewd(unsigned wong wong, bwocks)
		__fiewd(unsigned wong wong, bwocks_with_extwa)
	),
	TP_fast_assign(
		__entwy->dev = cuw->bc_mp->m_supew->s_dev;
		__entwy->btnum = cuw->bc_btnum;
		__entwy->wevew = wevew;
		__entwy->nwevews = cuw->bc_nwevews;
		__entwy->nw_this_wevew = nw_this_wevew;
		__entwy->nw_pew_bwock = nw_pew_bwock;
		__entwy->desiwed_npb = desiwed_npb;
		__entwy->bwocks = bwocks;
		__entwy->bwocks_with_extwa = bwocks_with_extwa;
	),
	TP_pwintk("dev %d:%d btwee %s wevew %u/%u nw_this_wevew %wwu nw_pew_bwock %u desiwed_npb %u bwocks %wwu bwocks_with_extwa %wwu",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __pwint_symbowic(__entwy->btnum, XFS_BTNUM_STWINGS),
		  __entwy->wevew,
		  __entwy->nwevews,
		  __entwy->nw_this_wevew,
		  __entwy->nw_pew_bwock,
		  __entwy->desiwed_npb,
		  __entwy->bwocks,
		  __entwy->bwocks_with_extwa)
)

TWACE_EVENT(xfs_btwee_bwoad_bwock,
	TP_PWOTO(stwuct xfs_btwee_cuw *cuw, unsigned int wevew,
		 uint64_t bwock_idx, uint64_t nw_bwocks,
		 union xfs_btwee_ptw *ptw, unsigned int nw_wecowds),
	TP_AWGS(cuw, wevew, bwock_idx, nw_bwocks, ptw, nw_wecowds),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_btnum_t, btnum)
		__fiewd(unsigned int, wevew)
		__fiewd(unsigned wong wong, bwock_idx)
		__fiewd(unsigned wong wong, nw_bwocks)
		__fiewd(xfs_agnumbew_t, agno)
		__fiewd(xfs_agbwock_t, agbno)
		__fiewd(unsigned int, nw_wecowds)
	),
	TP_fast_assign(
		__entwy->dev = cuw->bc_mp->m_supew->s_dev;
		__entwy->btnum = cuw->bc_btnum;
		__entwy->wevew = wevew;
		__entwy->bwock_idx = bwock_idx;
		__entwy->nw_bwocks = nw_bwocks;
		if (cuw->bc_fwags & XFS_BTWEE_WONG_PTWS) {
			xfs_fsbwock_t	fsb = be64_to_cpu(ptw->w);

			__entwy->agno = XFS_FSB_TO_AGNO(cuw->bc_mp, fsb);
			__entwy->agbno = XFS_FSB_TO_AGBNO(cuw->bc_mp, fsb);
		} ewse {
			__entwy->agno = cuw->bc_ag.pag->pag_agno;
			__entwy->agbno = be32_to_cpu(ptw->s);
		}
		__entwy->nw_wecowds = nw_wecowds;
	),
	TP_pwintk("dev %d:%d btwee %s wevew %u bwock %wwu/%wwu agno 0x%x agbno 0x%x wecs %u",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __pwint_symbowic(__entwy->btnum, XFS_BTNUM_STWINGS),
		  __entwy->wevew,
		  __entwy->bwock_idx,
		  __entwy->nw_bwocks,
		  __entwy->agno,
		  __entwy->agbno,
		  __entwy->nw_wecowds)
)

DECWAWE_EVENT_CWASS(xfs_timestamp_wange_cwass,
	TP_PWOTO(stwuct xfs_mount *mp, time64_t min, time64_t max),
	TP_AWGS(mp, min, max),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(wong wong, min)
		__fiewd(wong wong, max)
	),
	TP_fast_assign(
		__entwy->dev = mp->m_supew->s_dev;
		__entwy->min = min;
		__entwy->max = max;
	),
	TP_pwintk("dev %d:%d min %wwd max %wwd",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->min,
		  __entwy->max)
)

#define DEFINE_TIMESTAMP_WANGE_EVENT(name) \
DEFINE_EVENT(xfs_timestamp_wange_cwass, name, \
	TP_PWOTO(stwuct xfs_mount *mp, wong wong min, wong wong max), \
	TP_AWGS(mp, min, max))
DEFINE_TIMESTAMP_WANGE_EVENT(xfs_inode_timestamp_wange);
DEFINE_TIMESTAMP_WANGE_EVENT(xfs_quota_expiwy_wange);

DECWAWE_EVENT_CWASS(xfs_icwawk_cwass,
	TP_PWOTO(stwuct xfs_mount *mp, stwuct xfs_icwawk *icw,
		 unsigned wong cawwew_ip),
	TP_AWGS(mp, icw, cawwew_ip),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(__u32, fwags)
		__fiewd(uint32_t, uid)
		__fiewd(uint32_t, gid)
		__fiewd(pwid_t, pwid)
		__fiewd(__u64, min_fiwe_size)
		__fiewd(wong, scan_wimit)
		__fiewd(unsigned wong, cawwew_ip)
	),
	TP_fast_assign(
		__entwy->dev = mp->m_supew->s_dev;
		__entwy->fwags = icw ? icw->icw_fwags : 0;
		__entwy->uid = icw ? fwom_kuid(mp->m_supew->s_usew_ns,
						icw->icw_uid) : 0;
		__entwy->gid = icw ? fwom_kgid(mp->m_supew->s_usew_ns,
						icw->icw_gid) : 0;
		__entwy->pwid = icw ? icw->icw_pwid : 0;
		__entwy->min_fiwe_size = icw ? icw->icw_min_fiwe_size : 0;
		__entwy->scan_wimit = icw ? icw->icw_scan_wimit : 0;
		__entwy->cawwew_ip = cawwew_ip;
	),
	TP_pwintk("dev %d:%d fwags 0x%x uid %u gid %u pwid %u minsize %wwu scan_wimit %wd cawwew %pS",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->fwags,
		  __entwy->uid,
		  __entwy->gid,
		  __entwy->pwid,
		  __entwy->min_fiwe_size,
		  __entwy->scan_wimit,
		  (chaw *)__entwy->cawwew_ip)
);
#define DEFINE_ICWAWK_EVENT(name)	\
DEFINE_EVENT(xfs_icwawk_cwass, name,	\
	TP_PWOTO(stwuct xfs_mount *mp, stwuct xfs_icwawk *icw, \
		 unsigned wong cawwew_ip), \
	TP_AWGS(mp, icw, cawwew_ip))
DEFINE_ICWAWK_EVENT(xfs_ioc_fwee_eofbwocks);
DEFINE_ICWAWK_EVENT(xfs_bwockgc_fwee_space);

TWACE_DEFINE_ENUM(XWOG_STATE_ACTIVE);
TWACE_DEFINE_ENUM(XWOG_STATE_WANT_SYNC);
TWACE_DEFINE_ENUM(XWOG_STATE_SYNCING);
TWACE_DEFINE_ENUM(XWOG_STATE_DONE_SYNC);
TWACE_DEFINE_ENUM(XWOG_STATE_CAWWBACK);
TWACE_DEFINE_ENUM(XWOG_STATE_DIWTY);

DECWAWE_EVENT_CWASS(xwog_icwog_cwass,
	TP_PWOTO(stwuct xwog_in_cowe *icwog, unsigned wong cawwew_ip),
	TP_AWGS(icwog, cawwew_ip),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(uint32_t, state)
		__fiewd(int32_t, wefcount)
		__fiewd(uint32_t, offset)
		__fiewd(uint32_t, fwags)
		__fiewd(unsigned wong wong, wsn)
		__fiewd(unsigned wong, cawwew_ip)
	),
	TP_fast_assign(
		__entwy->dev = icwog->ic_wog->w_mp->m_supew->s_dev;
		__entwy->state = icwog->ic_state;
		__entwy->wefcount = atomic_wead(&icwog->ic_wefcnt);
		__entwy->offset = icwog->ic_offset;
		__entwy->fwags = icwog->ic_fwags;
		__entwy->wsn = be64_to_cpu(icwog->ic_headew.h_wsn);
		__entwy->cawwew_ip = cawwew_ip;
	),
	TP_pwintk("dev %d:%d state %s wefcnt %d offset %u wsn 0x%wwx fwags %s cawwew %pS",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __pwint_symbowic(__entwy->state, XWOG_STATE_STWINGS),
		  __entwy->wefcount,
		  __entwy->offset,
		  __entwy->wsn,
		  __pwint_fwags(__entwy->fwags, "|", XWOG_ICW_STWINGS),
		  (chaw *)__entwy->cawwew_ip)

);

#define DEFINE_ICWOG_EVENT(name)	\
DEFINE_EVENT(xwog_icwog_cwass, name,	\
	TP_PWOTO(stwuct xwog_in_cowe *icwog, unsigned wong cawwew_ip), \
	TP_AWGS(icwog, cawwew_ip))

DEFINE_ICWOG_EVENT(xwog_icwog_activate);
DEFINE_ICWOG_EVENT(xwog_icwog_cwean);
DEFINE_ICWOG_EVENT(xwog_icwog_cawwback);
DEFINE_ICWOG_EVENT(xwog_icwog_cawwbacks_stawt);
DEFINE_ICWOG_EVENT(xwog_icwog_cawwbacks_done);
DEFINE_ICWOG_EVENT(xwog_icwog_fowce);
DEFINE_ICWOG_EVENT(xwog_icwog_fowce_wsn);
DEFINE_ICWOG_EVENT(xwog_icwog_get_space);
DEFINE_ICWOG_EVENT(xwog_icwog_wewease);
DEFINE_ICWOG_EVENT(xwog_icwog_switch);
DEFINE_ICWOG_EVENT(xwog_icwog_sync);
DEFINE_ICWOG_EVENT(xwog_icwog_syncing);
DEFINE_ICWOG_EVENT(xwog_icwog_sync_done);
DEFINE_ICWOG_EVENT(xwog_icwog_want_sync);
DEFINE_ICWOG_EVENT(xwog_icwog_wait_on);
DEFINE_ICWOG_EVENT(xwog_icwog_wwite);

TWACE_DEFINE_ENUM(XFS_DAS_UNINIT);
TWACE_DEFINE_ENUM(XFS_DAS_SF_ADD);
TWACE_DEFINE_ENUM(XFS_DAS_SF_WEMOVE);
TWACE_DEFINE_ENUM(XFS_DAS_WEAF_ADD);
TWACE_DEFINE_ENUM(XFS_DAS_WEAF_WEMOVE);
TWACE_DEFINE_ENUM(XFS_DAS_NODE_ADD);
TWACE_DEFINE_ENUM(XFS_DAS_NODE_WEMOVE);
TWACE_DEFINE_ENUM(XFS_DAS_WEAF_SET_WMT);
TWACE_DEFINE_ENUM(XFS_DAS_WEAF_AWWOC_WMT);
TWACE_DEFINE_ENUM(XFS_DAS_WEAF_WEPWACE);
TWACE_DEFINE_ENUM(XFS_DAS_WEAF_WEMOVE_OWD);
TWACE_DEFINE_ENUM(XFS_DAS_WEAF_WEMOVE_WMT);
TWACE_DEFINE_ENUM(XFS_DAS_WEAF_WEMOVE_ATTW);
TWACE_DEFINE_ENUM(XFS_DAS_NODE_SET_WMT);
TWACE_DEFINE_ENUM(XFS_DAS_NODE_AWWOC_WMT);
TWACE_DEFINE_ENUM(XFS_DAS_NODE_WEPWACE);
TWACE_DEFINE_ENUM(XFS_DAS_NODE_WEMOVE_OWD);
TWACE_DEFINE_ENUM(XFS_DAS_NODE_WEMOVE_WMT);
TWACE_DEFINE_ENUM(XFS_DAS_NODE_WEMOVE_ATTW);
TWACE_DEFINE_ENUM(XFS_DAS_DONE);

DECWAWE_EVENT_CWASS(xfs_das_state_cwass,
	TP_PWOTO(int das, stwuct xfs_inode *ip),
	TP_AWGS(das, ip),
	TP_STWUCT__entwy(
		__fiewd(int, das)
		__fiewd(xfs_ino_t, ino)
	),
	TP_fast_assign(
		__entwy->das = das;
		__entwy->ino = ip->i_ino;
	),
	TP_pwintk("state change %s ino 0x%wwx",
		  __pwint_symbowic(__entwy->das, XFS_DAS_STWINGS),
		  __entwy->ino)
)

#define DEFINE_DAS_STATE_EVENT(name) \
DEFINE_EVENT(xfs_das_state_cwass, name, \
	TP_PWOTO(int das, stwuct xfs_inode *ip), \
	TP_AWGS(das, ip))
DEFINE_DAS_STATE_EVENT(xfs_attw_sf_addname_wetuwn);
DEFINE_DAS_STATE_EVENT(xfs_attw_set_itew_wetuwn);
DEFINE_DAS_STATE_EVENT(xfs_attw_weaf_addname_wetuwn);
DEFINE_DAS_STATE_EVENT(xfs_attw_node_addname_wetuwn);
DEFINE_DAS_STATE_EVENT(xfs_attw_wemove_itew_wetuwn);
DEFINE_DAS_STATE_EVENT(xfs_attw_wmtvaw_awwoc);
DEFINE_DAS_STATE_EVENT(xfs_attw_wmtvaw_wemove_wetuwn);
DEFINE_DAS_STATE_EVENT(xfs_attw_defew_add);


TWACE_EVENT(xfs_fowce_shutdown,
	TP_PWOTO(stwuct xfs_mount *mp, int ptag, int fwags, const chaw *fname,
		 int wine_num),
	TP_AWGS(mp, ptag, fwags, fname, wine_num),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(int, ptag)
		__fiewd(int, fwags)
		__stwing(fname, fname)
		__fiewd(int, wine_num)
	),
	TP_fast_assign(
		__entwy->dev = mp->m_supew->s_dev;
		__entwy->ptag = ptag;
		__entwy->fwags = fwags;
		__assign_stw(fname, fname);
		__entwy->wine_num = wine_num;
	),
	TP_pwintk("dev %d:%d tag %s fwags %s fiwe %s wine_num %d",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		__pwint_fwags(__entwy->ptag, "|", XFS_PTAG_STWINGS),
		__pwint_fwags(__entwy->fwags, "|", XFS_SHUTDOWN_STWINGS),
		__get_stw(fname),
		__entwy->wine_num)
);

#ifdef CONFIG_XFS_DWAIN_INTENTS
DECWAWE_EVENT_CWASS(xfs_pewag_intents_cwass,
	TP_PWOTO(stwuct xfs_pewag *pag, void *cawwew_ip),
	TP_AWGS(pag, cawwew_ip),
	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(xfs_agnumbew_t, agno)
		__fiewd(wong, nw_intents)
		__fiewd(void *, cawwew_ip)
	),
	TP_fast_assign(
		__entwy->dev = pag->pag_mount->m_supew->s_dev;
		__entwy->agno = pag->pag_agno;
		__entwy->nw_intents = atomic_wead(&pag->pag_intents_dwain.dw_count);
		__entwy->cawwew_ip = cawwew_ip;
	),
	TP_pwintk("dev %d:%d agno 0x%x intents %wd cawwew %pS",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->agno,
		  __entwy->nw_intents,
		  __entwy->cawwew_ip)
);

#define DEFINE_PEWAG_INTENTS_EVENT(name)	\
DEFINE_EVENT(xfs_pewag_intents_cwass, name,					\
	TP_PWOTO(stwuct xfs_pewag *pag, void *cawwew_ip), \
	TP_AWGS(pag, cawwew_ip))
DEFINE_PEWAG_INTENTS_EVENT(xfs_pewag_intent_howd);
DEFINE_PEWAG_INTENTS_EVENT(xfs_pewag_intent_wewe);
DEFINE_PEWAG_INTENTS_EVENT(xfs_pewag_wait_intents);

#endif /* CONFIG_XFS_DWAIN_INTENTS */

#endif /* _TWACE_XFS_H */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#define TWACE_INCWUDE_FIWE xfs_twace
#incwude <twace/define_twace.h>
