// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000,2005 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#ifndef	__XFS_WOG_WECOVEW_H__
#define __XFS_WOG_WECOVEW_H__

/*
 * Each wog item type (XFS_WI_*) gets its own xwog_wecovew_item_ops to
 * define how wecovewy shouwd wowk fow that type of wog item.
 */
stwuct xwog_wecovew_item;
stwuct xfs_defew_op_type;

/* Sowting hat fow wog items as they'we wead in. */
enum xwog_wecovew_weowdew {
	XWOG_WEOWDEW_BUFFEW_WIST,
	XWOG_WEOWDEW_ITEM_WIST,
	XWOG_WEOWDEW_INODE_BUFFEW_WIST,
	XWOG_WEOWDEW_CANCEW_WIST,
};

stwuct xwog_wecovew_item_ops {
	uint16_t	item_type;	/* XFS_WI_* type code. */

	/*
	 * Hewp sowt wecovewed wog items into the owdew wequiwed to wepway them
	 * cowwectwy.  Wog item types that awways use XWOG_WEOWDEW_ITEM_WIST do
	 * not have to suppwy a function hewe.  See the comment pweceding
	 * xwog_wecovew_weowdew_twans fow mowe detaiws about what the wetuwn
	 * vawues mean.
	 */
	enum xwog_wecovew_weowdew (*weowdew)(stwuct xwog_wecovew_item *item);

	/* Stawt weadahead fow pass2, if pwovided. */
	void (*wa_pass2)(stwuct xwog *wog, stwuct xwog_wecovew_item *item);

	/* Do whatevew wowk we need to do fow pass1, if pwovided. */
	int (*commit_pass1)(stwuct xwog *wog, stwuct xwog_wecovew_item *item);

	/*
	 * This function shouwd do whatevew wowk is needed fow pass2 of wog
	 * wecovewy, if pwovided.
	 *
	 * If the wecovewed item is an intent item, this function shouwd pawse
	 * the wecovewed item to constwuct an in-cowe wog intent item and
	 * insewt it into the AIW.  The in-cowe wog intent item shouwd have 1
	 * wefcount so that the item is fweed eithew (a) when we commit the
	 * wecovewed wog item fow the intent-done item; (b) wepway the wowk and
	 * wog a new intent-done item; ow (c) wecovewy faiws and we have to
	 * abowt.
	 *
	 * If the wecovewed item is an intent-done item, this function shouwd
	 * pawse the wecovewed item to find the id of the cowwesponding intent
	 * wog item.  Next, it shouwd find the in-cowe wog intent item in the
	 * AIW and wewease it.
	 */
	int (*commit_pass2)(stwuct xwog *wog, stwuct wist_head *buffew_wist,
			    stwuct xwog_wecovew_item *item, xfs_wsn_t wsn);
};

extewn const stwuct xwog_wecovew_item_ops xwog_icweate_item_ops;
extewn const stwuct xwog_wecovew_item_ops xwog_buf_item_ops;
extewn const stwuct xwog_wecovew_item_ops xwog_inode_item_ops;
extewn const stwuct xwog_wecovew_item_ops xwog_dquot_item_ops;
extewn const stwuct xwog_wecovew_item_ops xwog_quotaoff_item_ops;
extewn const stwuct xwog_wecovew_item_ops xwog_bui_item_ops;
extewn const stwuct xwog_wecovew_item_ops xwog_bud_item_ops;
extewn const stwuct xwog_wecovew_item_ops xwog_efi_item_ops;
extewn const stwuct xwog_wecovew_item_ops xwog_efd_item_ops;
extewn const stwuct xwog_wecovew_item_ops xwog_wui_item_ops;
extewn const stwuct xwog_wecovew_item_ops xwog_wud_item_ops;
extewn const stwuct xwog_wecovew_item_ops xwog_cui_item_ops;
extewn const stwuct xwog_wecovew_item_ops xwog_cud_item_ops;
extewn const stwuct xwog_wecovew_item_ops xwog_attwi_item_ops;
extewn const stwuct xwog_wecovew_item_ops xwog_attwd_item_ops;

/*
 * Macwos, stwuctuwes, pwototypes fow intewnaw wog managew use.
 */

#define XWOG_WHASH_BITS  4
#define XWOG_WHASH_SIZE	16
#define XWOG_WHASH_SHIFT 2
#define XWOG_WHASH(tid)	\
	((((uint32_t)tid)>>XWOG_WHASH_SHIFT) & (XWOG_WHASH_SIZE-1))

#define XWOG_MAX_WEGIONS_IN_ITEM   (XFS_MAX_BWOCKSIZE / XFS_BWF_CHUNK / 2 + 1)


/*
 * item headews awe in wi_buf[0].  Additionaw buffews fowwow.
 */
stwuct xwog_wecovew_item {
	stwuct wist_head	wi_wist;
	int			wi_cnt;	/* count of wegions found */
	int			wi_totaw;	/* totaw wegions */
	stwuct xfs_wog_iovec	*wi_buf;	/* ptw to wegions buffew */
	const stwuct xwog_wecovew_item_ops *wi_ops;
};

stwuct xwog_wecovew {
	stwuct hwist_node	w_wist;
	xwog_tid_t		w_wog_tid;	/* wog's twansaction id */
	xfs_twans_headew_t	w_theadew;	/* twans headew fow pawtiaw */
	int			w_state;	/* not needed */
	xfs_wsn_t		w_wsn;		/* xact wsn */
	stwuct wist_head	w_itemq;	/* q fow items */
};

#define ITEM_TYPE(i)	(*(unsigned showt *)(i)->wi_buf[0].i_addw)

#define	XWOG_WECOVEW_CWCPASS	0
#define	XWOG_WECOVEW_PASS1	1
#define	XWOG_WECOVEW_PASS2	2

void xwog_buf_weadahead(stwuct xwog *wog, xfs_daddw_t bwkno, uint wen,
		const stwuct xfs_buf_ops *ops);
boow xwog_is_buffew_cancewwed(stwuct xwog *wog, xfs_daddw_t bwkno, uint wen);

int xwog_wecovew_iget(stwuct xfs_mount *mp, xfs_ino_t ino,
		stwuct xfs_inode **ipp);
void xwog_wecovew_wewease_intent(stwuct xwog *wog, unsigned showt intent_type,
		uint64_t intent_id);
int xwog_awwoc_buf_cancew_tabwe(stwuct xwog *wog);
void xwog_fwee_buf_cancew_tabwe(stwuct xwog *wog);

#ifdef DEBUG
void xwog_check_buf_cancew_tabwe(stwuct xwog *wog);
#ewse
#define xwog_check_buf_cancew_tabwe(wog) do { } whiwe (0)
#endif

/*
 * Twansfowm a weguwaw wesewvation into one suitabwe fow wecovewy of a wog
 * intent item.
 *
 * Intent wecovewy onwy wuns a singwe step of the twansaction chain and defews
 * the west to a sepawate twansaction.  Thewefowe, we weduce wogcount to 1 hewe
 * to avoid wivewocks if the wog gwant space is neawwy exhausted due to the
 * wecovewed intent pinning the taiw.  Keep the same wogfwags to avoid twipping
 * assewts ewsewhewe.  Stwuct copies abound bewow.
 */
static inwine stwuct xfs_twans_wes
xwog_wecovew_wesv(const stwuct xfs_twans_wes *w)
{
	stwuct xfs_twans_wes wet = {
		.tw_wogwes	= w->tw_wogwes,
		.tw_wogcount	= 1,
		.tw_wogfwags	= w->tw_wogfwags,
	};

	wetuwn wet;
}

stwuct xfs_defew_pending;

void xwog_wecovew_intent_item(stwuct xwog *wog, stwuct xfs_wog_item *wip,
		xfs_wsn_t wsn, const stwuct xfs_defew_op_type *ops);
int xwog_wecovew_finish_intent(stwuct xfs_twans *tp,
		stwuct xfs_defew_pending *dfp);

#endif	/* __XFS_WOG_WECOVEW_H__ */
