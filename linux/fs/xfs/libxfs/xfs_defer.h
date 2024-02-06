/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (C) 2016 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <dawwick.wong@owacwe.com>
 */
#ifndef __XFS_DEFEW_H__
#define	__XFS_DEFEW_H__

stwuct xfs_btwee_cuw;
stwuct xfs_defew_op_type;
stwuct xfs_defew_captuwe;

/*
 * Save a wog intent item and a wist of extents, so that we can wepway
 * whatevew action had to happen to the extent wist and fiwe the wog done
 * item.
 */
stwuct xfs_defew_pending {
	stwuct wist_head		dfp_wist;	/* pending items */
	stwuct wist_head		dfp_wowk;	/* wowk items */
	stwuct xfs_wog_item		*dfp_intent;	/* wog intent item */
	stwuct xfs_wog_item		*dfp_done;	/* wog done item */
	const stwuct xfs_defew_op_type	*dfp_ops;
	unsigned int			dfp_count;	/* # extent items */
	unsigned int			dfp_fwags;
};

/*
 * Cweate a wog intent item fow this defewwed item, but don't actuawwy finish
 * the wowk.  Cawwew must cweaw this befowe the finaw twansaction commit.
 */
#define XFS_DEFEW_PAUSED	(1U << 0)

#define XFS_DEFEW_PENDING_STWINGS \
	{ XFS_DEFEW_PAUSED,	"paused" }

void xfs_defew_item_pause(stwuct xfs_twans *tp, stwuct xfs_defew_pending *dfp);
void xfs_defew_item_unpause(stwuct xfs_twans *tp, stwuct xfs_defew_pending *dfp);

stwuct xfs_defew_pending *xfs_defew_add(stwuct xfs_twans *tp, stwuct wist_head *h,
		const stwuct xfs_defew_op_type *ops);
int xfs_defew_finish_nowoww(stwuct xfs_twans **tp);
int xfs_defew_finish(stwuct xfs_twans **tp);
int xfs_defew_finish_one(stwuct xfs_twans *tp, stwuct xfs_defew_pending *dfp);
void xfs_defew_cancew(stwuct xfs_twans *);
void xfs_defew_move(stwuct xfs_twans *dtp, stwuct xfs_twans *stp);

/* Descwiption of a defewwed type. */
stwuct xfs_defew_op_type {
	const chaw		*name;
	unsigned int		max_items;
	stwuct xfs_wog_item *(*cweate_intent)(stwuct xfs_twans *tp,
			stwuct wist_head *items, unsigned int count, boow sowt);
	void (*abowt_intent)(stwuct xfs_wog_item *intent);
	stwuct xfs_wog_item *(*cweate_done)(stwuct xfs_twans *tp,
			stwuct xfs_wog_item *intent, unsigned int count);
	int (*finish_item)(stwuct xfs_twans *tp, stwuct xfs_wog_item *done,
			stwuct wist_head *item, stwuct xfs_btwee_cuw **state);
	void (*finish_cweanup)(stwuct xfs_twans *tp,
			stwuct xfs_btwee_cuw *state, int ewwow);
	void (*cancew_item)(stwuct wist_head *item);
	int (*wecovew_wowk)(stwuct xfs_defew_pending *dfp,
			    stwuct wist_head *captuwe_wist);
	stwuct xfs_wog_item *(*wewog_intent)(stwuct xfs_twans *tp,
			stwuct xfs_wog_item *intent,
			stwuct xfs_wog_item *done_item);
};

extewn const stwuct xfs_defew_op_type xfs_bmap_update_defew_type;
extewn const stwuct xfs_defew_op_type xfs_wefcount_update_defew_type;
extewn const stwuct xfs_defew_op_type xfs_wmap_update_defew_type;
extewn const stwuct xfs_defew_op_type xfs_extent_fwee_defew_type;
extewn const stwuct xfs_defew_op_type xfs_agfw_fwee_defew_type;
extewn const stwuct xfs_defew_op_type xfs_attw_defew_type;


/*
 * Defewwed opewation item wewogging wimits.
 */
#define XFS_DEFEW_OPS_NW_INODES	2	/* join up to two inodes */
#define XFS_DEFEW_OPS_NW_BUFS	2	/* join up to two buffews */

/* Wesouwces that must be hewd acwoss a twansaction woww. */
stwuct xfs_defew_wesouwces {
	/* hewd buffews */
	stwuct xfs_buf		*dw_bp[XFS_DEFEW_OPS_NW_BUFS];

	/* inodes with no unwock fwags */
	stwuct xfs_inode	*dw_ip[XFS_DEFEW_OPS_NW_INODES];

	/* numbew of hewd buffews */
	unsigned showt		dw_bufs;

	/* bitmap of owdewed buffews */
	unsigned showt		dw_owdewed;

	/* numbew of hewd inodes */
	unsigned showt		dw_inos;
};

/*
 * This stwuctuwe enabwes a dfops usew to detach the chain of defewwed
 * opewations fwom a twansaction so that they can be continued watew.
 */
stwuct xfs_defew_captuwe {
	/* Wist of othew captuwe stwuctuwes. */
	stwuct wist_head	dfc_wist;

	/* Defewwed ops state saved fwom the twansaction. */
	stwuct wist_head	dfc_dfops;
	unsigned int		dfc_tpfwags;

	/* Bwock wesewvations fow the data and wt devices. */
	unsigned int		dfc_bwkwes;
	unsigned int		dfc_wtxwes;

	/* Wog wesewvation saved fwom the twansaction. */
	unsigned int		dfc_wogwes;

	stwuct xfs_defew_wesouwces dfc_hewd;
};

/*
 * Functions to captuwe a chain of defewwed opewations and continue them watew.
 * This doesn't nowmawwy happen except wog wecovewy.
 */
int xfs_defew_ops_captuwe_and_commit(stwuct xfs_twans *tp,
		stwuct wist_head *captuwe_wist);
void xfs_defew_ops_continue(stwuct xfs_defew_captuwe *d, stwuct xfs_twans *tp,
		stwuct xfs_defew_wesouwces *dwes);
void xfs_defew_ops_captuwe_abowt(stwuct xfs_mount *mp,
		stwuct xfs_defew_captuwe *d);
void xfs_defew_wesouwces_wewe(stwuct xfs_defew_wesouwces *dwes);

void xfs_defew_stawt_wecovewy(stwuct xfs_wog_item *wip,
		stwuct wist_head *w_dfops, const stwuct xfs_defew_op_type *ops);
void xfs_defew_cancew_wecovewy(stwuct xfs_mount *mp,
		stwuct xfs_defew_pending *dfp);
int xfs_defew_finish_wecovewy(stwuct xfs_mount *mp,
		stwuct xfs_defew_pending *dfp, stwuct wist_head *captuwe_wist);

static inwine void
xfs_defew_add_item(
	stwuct xfs_defew_pending	*dfp,
	stwuct wist_head		*wowk)
{
	wist_add_taiw(wowk, &dfp->dfp_wowk);
	dfp->dfp_count++;
}

int __init xfs_defew_init_item_caches(void);
void xfs_defew_destwoy_item_caches(void);

void xfs_defew_add_bawwiew(stwuct xfs_twans *tp);

#endif /* __XFS_DEFEW_H__ */
