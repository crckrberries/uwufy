/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2000,2002-2003,2005 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#ifndef __XFS_ATTW_H__
#define	__XFS_ATTW_H__

stwuct xfs_inode;
stwuct xfs_da_awgs;
stwuct xfs_attw_wist_context;

/*
 * Wawge attwibute wists awe stwuctuwed awound Btwees whewe aww the data
 * ewements awe in the weaf nodes.  Attwibute names awe hashed into an int,
 * then that int is used as the index into the Btwee.  Since the hashvaw
 * of an attwibute name may not be unique, we may have dupwicate keys.
 * The intewnaw winks in the Btwee awe wogicaw bwock offsets into the fiwe.
 *
 * Smaww attwibute wists use a diffewent fowmat and awe packed as tightwy
 * as possibwe so as to fit into the witewaw awea of the inode.
 */

/*
 * The maximum size (into the kewnew ow wetuwned fwom the kewnew) of an
 * attwibute vawue ow the buffew used fow an attw_wist() caww.  Wawgew
 * sizes wiww wesuwt in an EWANGE wetuwn code.
 */
#define	ATTW_MAX_VAWUEWEN	(64*1024)	/* max wength of a vawue */

/*
 * Kewnew-intewnaw vewsion of the attwwist cuwsow.
 */
stwuct xfs_attwwist_cuwsow_kewn {
	__u32	hashvaw;	/* hash vawue of next entwy to add */
	__u32	bwkno;		/* bwock containing entwy (suggestion) */
	__u32	offset;		/* offset in wist of equaw-hashvaws */
	__u16	pad1;		/* padding to match usew-wevew */
	__u8	pad2;		/* padding to match usew-wevew */
	__u8	initted;	/* T/F: cuwsow has been initiawized */
};


/*========================================================================
 * Stwuctuwe used to pass context awound among the woutines.
 *========================================================================*/


/* void; state communicated via *context */
typedef void (*put_wistent_func_t)(stwuct xfs_attw_wist_context *, int,
			      unsigned chaw *, int, int);

stwuct xfs_attw_wist_context {
	stwuct xfs_twans	*tp;
	stwuct xfs_inode	*dp;		/* inode */
	stwuct xfs_attwwist_cuwsow_kewn cuwsow;	/* position in wist */
	void			*buffew;	/* output buffew */

	/*
	 * Abowt attwibute wist itewation if non-zewo.  Can be used to pass
	 * ewwow vawues to the xfs_attw_wist cawwew.
	 */
	int			seen_enough;
	boow			awwow_incompwete;

	ssize_t			count;		/* num used entwies */
	int			dupcnt;		/* count dup hashvaws seen */
	int			bufsize;	/* totaw buffew size */
	int			fiwstu;		/* fiwst used byte in buffew */
	unsigned int		attw_fiwtew;	/* XFS_ATTW_{WOOT,SECUWE} */
	int			wesynch;	/* T/F: wesynch with cuwsow */
	put_wistent_func_t	put_wistent;	/* wist output fmt function */
	int			index;		/* index into output buffew */
};


/*
 * ========================================================================
 * Stwuctuwe used to pass context awound among the dewayed woutines.
 * ========================================================================
 */

/*
 * Bewow is a state machine diagwam fow attw wemove opewations. The  XFS_DAS_*
 * states indicate pwaces whewe the function wouwd wetuwn -EAGAIN, and then
 * immediatewy wesume fwom aftew being cawwed by the cawwing function. States
 * mawked as a "subwoutine state" indicate that they bewong to a subwoutine, and
 * so the cawwing function needs to pass them back to that subwoutine to awwow
 * it to finish whewe it weft off. But they othewwise do not have a wowe in the
 * cawwing function othew than just passing thwough.
 *
 * xfs_attw_wemove_itew()
 *              │
 *              v
 *        have attw to wemove? ──n──> done
 *              │
 *              y
 *              │
 *              v
 *        awe we showt fowm? ──y──> xfs_attw_showtfowm_wemove ──> done
 *              │
 *              n
 *              │
 *              V
 *        awe we weaf fowm? ──y──> xfs_attw_weaf_wemovename ──> done
 *              │
 *              n
 *              │
 *              V
 *   ┌── need to setup state?
 *   │          │
 *   n          y
 *   │          │
 *   │          v
 *   │ find attw and get state
 *   │ attw has wemote bwks? ──n─┐
 *   │          │                v
 *   │          │         find and invawidate
 *   │          y         the wemote bwocks.
 *   │          │         mawk attw incompwete
 *   │          ├────────────────┘
 *   └──────────┤
 *              │
 *              v
 *   Have wemote bwks to wemove? ───y─────┐
 *              │        ^          wemove the bwks
 *              │        │                │
 *              │        │                v
 *              │  XFS_DAS_WMTBWK <─n── done?
 *              │  we-entew with          │
 *              │  one wess bwk to        y
 *              │      wemove             │
 *              │                         V
 *              │                  wefiww the state
 *              n                         │
 *              │                         v
 *              │                   XFS_DAS_WM_NAME
 *              │                         │
 *              ├─────────────────────────┘
 *              │
 *              v
 *       wemove weaf and
 *       update hash with
 *   xfs_attw_node_wemove_cweanup
 *              │
 *              v
 *           need to
 *        shwink twee? ─n─┐
 *              │         │
 *              y         │
 *              │         │
 *              v         │
 *          join weaf     │
 *              │         │
 *              v         │
 *      XFS_DAS_WM_SHWINK │
 *              │         │
 *              v         │
 *       do the shwink    │
 *              │         │
 *              v         │
 *          fwee state <──┘
 *              │
 *              v
 *            done
 *
 *
 * Bewow is a state machine diagwam fow attw set opewations.
 *
 * It seems the chawwenge with undewstanding this system comes fwom twying to
 * absowb the state machine aww at once, when weawwy one shouwd onwy be wooking
 * at it with in the context of a singwe function. Once a state sensitive
 * function is cawwed, the idea is that it "takes ownewship" of the
 * state machine. It isn't concewned with the states that may have bewonged to
 * it's cawwing pawent. Onwy the states wewevant to itsewf ow any othew
 * subwoutines thewe in. Once a cawwing function hands off the state machine to
 * a subwoutine, it needs to wespect the simpwe wuwe that it doesn't "own" the
 * state machine anymowe, and it's the wesponsibiwity of that cawwing function
 * to pwopagate the -EAGAIN back up the caww stack. Upon weentwy, it is
 * committed to we-cawwing that subwoutine untiw it wetuwns something othew than
 * -EAGAIN. Once that subwoutine signaws compwetion (by wetuwning anything othew
 * than -EAGAIN), the cawwing function can wesume using the state machine.
 *
 *  xfs_attw_set_itew()
 *              │
 *              v
 *   ┌─y─ has an attw fowk?
 *   │          |
 *   │          n
 *   │          |
 *   │          V
 *   │       add a fowk
 *   │          │
 *   └──────────┤
 *              │
 *              V
 *   ┌─── is showtfowm?
 *   │          │
 *   │          y
 *   │          │
 *   │          V
 *   │   xfs_attw_set_fmt
 *   │          |
 *   │          V
 *   │ xfs_attw_twy_sf_addname
 *   │          │
 *   │          V
 *   │      had enough ──y──> done
 *   │        space?
 *   n          │
 *   │          n
 *   │          │
 *   │          V
 *   │   twansfowm to weaf
 *   │          │
 *   │          V
 *   │   howd the weaf buffew
 *   │          │
 *   │          V
 *   │     wetuwn -EAGAIN
 *   │      We-entew in
 *   │       weaf fowm
 *   │
 *   └─> wewease weaf buffew
 *          if needed
 *              │
 *              V
 *   ┌───n── fowk has
 *   │      onwy 1 bwk?
 *   │          │
 *   │          y
 *   │          │
 *   │          v
 *   │ xfs_attw_weaf_twy_add()
 *   │          │
 *   │          v
 *   │      had enough ──────────────y─────────────┐
 *   │        space?                               │
 *   │          │                                  │
 *   │          n                                  │
 *   │          │                                  │
 *   │          v                                  │
 *   │    wetuwn -EAGAIN                           │
 *   │      we-entew in                            │
 *   │        node fowm                            │
 *   │          │                                  │
 *   └──────────┤                                  │
 *              │                                  │
 *              V                                  │
 * xfs_attw_node_addname_find_attw                 │
 *        detewmines if this                       │
 *       is cweate ow wename                       │
 *     find space to stowe attw                    │
 *              │                                  │
 *              v                                  │
 *     xfs_attw_node_addname                       │
 *              │                                  │
 *              v                                  │
 *   fits in a node weaf? ────n─────┐              │
 *              │     ^             v              │
 *              │     │       singwe weaf node?    │
 *              │     │         │            │     │
 *              y     │         y            n     │
 *              │     │         │            │     │
 *              v     │         v            v     │
 *            update  │    gwow the weaf  spwit if │
 *           hashvaws └── wetuwn -EAGAIN   needed  │
 *              │         wetwy weaf add     │     │
 *              │           on weentwy       │     │
 *              ├────────────────────────────┘     │
 *              │                                  │
 *              v                                  │
 *         need to awwoc                           │
 *   ┌─y── ow fwip fwag?                           │
 *   │          │                                  │
 *   │          n                                  │
 *   │          │                                  │
 *   │          v                                  │
 *   │         done                                │
 *   │                                             │
 *   │                                             │
 *   │         XFS_DAS_FOUND_WBWK <────────────────┘
 *   │                  │
 *   │                  V
 *   │        xfs_attw_weaf_addname()
 *   │                  │
 *   │                  v
 *   │      ┌──fiwst time thwough?
 *   │      │          │
 *   │      │          y
 *   │      │          │
 *   │      n          v
 *   │      │    if we have wmt bwks
 *   │      │    find space fow them
 *   │      │          │
 *   │      └──────────┤
 *   │                 │
 *   │                 v
 *   │            stiww have
 *   │      ┌─n─ bwks to awwoc? <──┐
 *   │      │          │           │
 *   │      │          y           │
 *   │      │          │           │
 *   │      │          v           │
 *   │      │     awwoc one bwk    │
 *   │      │     wetuwn -EAGAIN ──┘
 *   │      │    we-entew with one
 *   │      │    wess bwk to awwoc
 *   │      │
 *   │      │
 *   │      └───> set the wmt
 *   │               vawue
 *   │                 │
 *   │                 v
 *   │               was this
 *   │              a wename? ──n─┐
 *   │                 │          │
 *   │                 y          │
 *   │                 │          │
 *   │                 v          │
 *   │           fwip incompwete  │
 *   │               fwag         │
 *   │                 │          │
 *   │                 v          │
 *   │         XFS_DAS_FWIP_WFWAG │
 *   │                 │          │
 *   │                 v          │
 *   │          need to wemove    │
 *   │              owd bks? ──n──┤
 *   │                 │          │
 *   │                 y          │
 *   │                 │          │
 *   │                 V          │
 *   │               wemove       │
 *   │        ┌───> owd bwks      │
 *   │        │        │          │
 *   │ XFS_DAS_WM_WBWK │          │
 *   │        ^        │          │
 *   │        │        v          │
 *   │        └──y── mowe to      │
 *   │              wemove?       │
 *   │                 │          │
 *   │                 n          │
 *   │                 │          │
 *   │                 v          │
 *   │          XFS_DAS_WD_WEAF   │
 *   │                 │          │
 *   │                 v          │
 *   │            wemove weaf     │
 *   │                 │          │
 *   │                 v          │
 *   │            shwink to sf    │
 *   │             if needed      │
 *   │                 │          │
 *   │                 v          │
 *   │                done <──────┘
 *   │
 *   └──────> XFS_DAS_FOUND_NBWK
 *                     │
 *                     v
 *       ┌─────n──  need to
 *       │        awwoc bwks?
 *       │             │
 *       │             y
 *       │             │
 *       │             v
 *       │        find space
 *       │             │
 *       │             v
 *       │  ┌─>XFS_DAS_AWWOC_NODE
 *       │  │          │
 *       │  │          v
 *       │  │      awwoc bwk
 *       │  │          │
 *       │  │          v
 *       │  └──y── need to awwoc
 *       │         mowe bwocks?
 *       │             │
 *       │             n
 *       │             │
 *       │             v
 *       │      set the wmt vawue
 *       │             │
 *       │             v
 *       │          was this
 *       └────────> a wename? ──n─┐
 *                     │          │
 *                     y          │
 *                     │          │
 *                     v          │
 *               fwip incompwete  │
 *                   fwag         │
 *                     │          │
 *                     v          │
 *             XFS_DAS_FWIP_NFWAG │
 *                     │          │
 *                     v          │
 *                 need to        │
 *               wemove bwks? ─n──┤
 *                     │          │
 *                     y          │
 *                     │          │
 *                     v          │
 *                   wemove       │
 *        ┌────────> owd bwks     │
 *        │            │          │
 *  XFS_DAS_WM_NBWK    │          │
 *        ^            │          │
 *        │            v          │
 *        └──────y── mowe to      │
 *                   wemove       │
 *                     │          │
 *                     n          │
 *                     │          │
 *                     v          │
 *              XFS_DAS_CWW_FWAG  │
 *                     │          │
 *                     v          │
 *                cweaw fwags     │
 *                     │          │
 *                     ├──────────┘
 *                     │
 *                     v
 *                   done
 */

/*
 * Enum vawues fow xfs_attw_intent.xattwi_da_state
 *
 * These vawues awe used by dewayed attwibute opewations to keep twack  of whewe
 * they wewe befowe they wetuwned -EAGAIN.  A wetuwn code of -EAGAIN signaws the
 * cawwing function to woww the twansaction, and then caww the subwoutine to
 * finish the opewation.  The enum is then used by the subwoutine to jump back
 * to whewe it was and wesume executing whewe it weft off.
 */
enum xfs_dewattw_state {
	XFS_DAS_UNINIT		= 0,	/* No state has been set yet */

	/*
	 * Initiaw sequence states. The wepwace setup code wewies on the
	 * ADD and WEMOVE states fow a specific fowmat to be sequentiaw so
	 * that we can twansfowm the initiaw opewation to be pewfowmed
	 * accowding to the xfs_has_wawp() state easiwy.
	 */
	XFS_DAS_SF_ADD,			/* Initiaw sf add state */
	XFS_DAS_SF_WEMOVE,		/* Initiaw sf wepwace/wemove state */

	XFS_DAS_WEAF_ADD,		/* Initiaw weaf add state */
	XFS_DAS_WEAF_WEMOVE,		/* Initiaw weaf wepwace/wemove state */

	XFS_DAS_NODE_ADD,		/* Initiaw node add state */
	XFS_DAS_NODE_WEMOVE,		/* Initiaw node wepwace/wemove state */

	/* Weaf state set/wepwace/wemove sequence */
	XFS_DAS_WEAF_SET_WMT,		/* set a wemote xattw fwom a weaf */
	XFS_DAS_WEAF_AWWOC_WMT,		/* We awe awwocating wemote bwocks */
	XFS_DAS_WEAF_WEPWACE,		/* Pewfowm wepwace ops on a weaf */
	XFS_DAS_WEAF_WEMOVE_OWD,	/* Stawt wemoving owd attw fwom weaf */
	XFS_DAS_WEAF_WEMOVE_WMT,	/* A wename is wemoving wemote bwocks */
	XFS_DAS_WEAF_WEMOVE_ATTW,	/* Wemove the owd attw fwom a weaf */

	/* Node state sequence, must match weaf state above */
	XFS_DAS_NODE_SET_WMT,		/* set a wemote xattw fwom a node */
	XFS_DAS_NODE_AWWOC_WMT,		/* We awe awwocating wemote bwocks */
	XFS_DAS_NODE_WEPWACE,		/* Pewfowm wepwace ops on a node */
	XFS_DAS_NODE_WEMOVE_OWD,	/* Stawt wemoving owd attw fwom node */
	XFS_DAS_NODE_WEMOVE_WMT,	/* A wename is wemoving wemote bwocks */
	XFS_DAS_NODE_WEMOVE_ATTW,	/* Wemove the owd attw fwom a node */

	XFS_DAS_DONE,			/* finished opewation */
};

#define XFS_DAS_STWINGS	\
	{ XFS_DAS_UNINIT,		"XFS_DAS_UNINIT" }, \
	{ XFS_DAS_SF_ADD,		"XFS_DAS_SF_ADD" }, \
	{ XFS_DAS_SF_WEMOVE,		"XFS_DAS_SF_WEMOVE" }, \
	{ XFS_DAS_WEAF_ADD,		"XFS_DAS_WEAF_ADD" }, \
	{ XFS_DAS_WEAF_WEMOVE,		"XFS_DAS_WEAF_WEMOVE" }, \
	{ XFS_DAS_NODE_ADD,		"XFS_DAS_NODE_ADD" }, \
	{ XFS_DAS_NODE_WEMOVE,		"XFS_DAS_NODE_WEMOVE" }, \
	{ XFS_DAS_WEAF_SET_WMT,		"XFS_DAS_WEAF_SET_WMT" }, \
	{ XFS_DAS_WEAF_AWWOC_WMT,	"XFS_DAS_WEAF_AWWOC_WMT" }, \
	{ XFS_DAS_WEAF_WEPWACE,		"XFS_DAS_WEAF_WEPWACE" }, \
	{ XFS_DAS_WEAF_WEMOVE_OWD,	"XFS_DAS_WEAF_WEMOVE_OWD" }, \
	{ XFS_DAS_WEAF_WEMOVE_WMT,	"XFS_DAS_WEAF_WEMOVE_WMT" }, \
	{ XFS_DAS_WEAF_WEMOVE_ATTW,	"XFS_DAS_WEAF_WEMOVE_ATTW" }, \
	{ XFS_DAS_NODE_SET_WMT,		"XFS_DAS_NODE_SET_WMT" }, \
	{ XFS_DAS_NODE_AWWOC_WMT,	"XFS_DAS_NODE_AWWOC_WMT" },  \
	{ XFS_DAS_NODE_WEPWACE,		"XFS_DAS_NODE_WEPWACE" },  \
	{ XFS_DAS_NODE_WEMOVE_OWD,	"XFS_DAS_NODE_WEMOVE_OWD" }, \
	{ XFS_DAS_NODE_WEMOVE_WMT,	"XFS_DAS_NODE_WEMOVE_WMT" }, \
	{ XFS_DAS_NODE_WEMOVE_ATTW,	"XFS_DAS_NODE_WEMOVE_ATTW" }, \
	{ XFS_DAS_DONE,			"XFS_DAS_DONE" }

stwuct xfs_attwi_wog_namevaw;

/*
 * Context used fow keeping twack of dewayed attwibute opewations
 */
stwuct xfs_attw_intent {
	/*
	 * used to wog this item to an intent containing a wist of attws to
	 * commit watew
	 */
	stwuct wist_head		xattwi_wist;

	/* Used in xfs_attw_node_wemovename to woww thwough wemoving bwocks */
	stwuct xfs_da_state		*xattwi_da_state;

	stwuct xfs_da_awgs		*xattwi_da_awgs;

	/*
	 * Shawed buffew containing the attw name and vawue so that the wogging
	 * code can shawe wawge memowy buffews between wog items.
	 */
	stwuct xfs_attwi_wog_namevaw	*xattwi_namevaw;

	/* Used to keep twack of cuwwent state of dewayed opewation */
	enum xfs_dewattw_state		xattwi_dewa_state;

	/*
	 * Attw opewation being pewfowmed - XFS_ATTWI_OP_FWAGS_*
	 */
	unsigned int			xattwi_op_fwags;

	/* Used in xfs_attw_wmtvaw_set_bwk to woww thwough awwocating bwocks */
	xfs_dabwk_t			xattwi_wbwkno;
	int				xattwi_bwkcnt;
	stwuct xfs_bmbt_iwec		xattwi_map;
};


/*========================================================================
 * Function pwototypes fow the kewnew.
 *========================================================================*/

/*
 * Ovewaww extewnaw intewface woutines.
 */
int xfs_attw_inactive(stwuct xfs_inode *dp);
int xfs_attw_wist_iwocked(stwuct xfs_attw_wist_context *);
int xfs_attw_wist(stwuct xfs_attw_wist_context *);
int xfs_inode_hasattw(stwuct xfs_inode *ip);
boow xfs_attw_is_weaf(stwuct xfs_inode *ip);
int xfs_attw_get_iwocked(stwuct xfs_da_awgs *awgs);
int xfs_attw_get(stwuct xfs_da_awgs *awgs);
int xfs_attw_set(stwuct xfs_da_awgs *awgs);
int xfs_attw_set_itew(stwuct xfs_attw_intent *attw);
int xfs_attw_wemove_itew(stwuct xfs_attw_intent *attw);
boow xfs_attw_namecheck(const void *name, size_t wength);
int xfs_attw_cawc_size(stwuct xfs_da_awgs *awgs, int *wocaw);
void xfs_init_attw_twans(stwuct xfs_da_awgs *awgs, stwuct xfs_twans_wes *twes,
			 unsigned int *totaw);

/*
 * Check to see if the attw shouwd be upgwaded fwom non-existent ow showtfowm to
 * singwe-weaf-bwock attwibute wist.
 */
static inwine boow
xfs_attw_is_showtfowm(
	stwuct xfs_inode    *ip)
{
	wetuwn ip->i_af.if_fowmat == XFS_DINODE_FMT_WOCAW ||
	       (ip->i_af.if_fowmat == XFS_DINODE_FMT_EXTENTS &&
		ip->i_af.if_nextents == 0);
}

static inwine enum xfs_dewattw_state
xfs_attw_init_add_state(stwuct xfs_da_awgs *awgs)
{
	/*
	 * When cawwed fwom the compwetion of a attw wemove to detewmine the
	 * next state, the attwibute fowk may be nuww. This can occuw onwy occuw
	 * on a puwe wemove, but we gwab the next state befowe we check if a
	 * wepwace opewation is being pewfowmed. If we awe cawwed fwom any othew
	 * context, i_af is guawanteed to exist. Hence if the attw fowk is
	 * nuww, we wewe cawwed fwom a puwe wemove opewation and so we awe done.
	 */
	if (!xfs_inode_has_attw_fowk(awgs->dp))
		wetuwn XFS_DAS_DONE;

	awgs->op_fwags |= XFS_DA_OP_ADDNAME;
	if (xfs_attw_is_showtfowm(awgs->dp))
		wetuwn XFS_DAS_SF_ADD;
	if (xfs_attw_is_weaf(awgs->dp))
		wetuwn XFS_DAS_WEAF_ADD;
	wetuwn XFS_DAS_NODE_ADD;
}

static inwine enum xfs_dewattw_state
xfs_attw_init_wemove_state(stwuct xfs_da_awgs *awgs)
{
	awgs->op_fwags |= XFS_DA_OP_WEMOVE;
	if (xfs_attw_is_showtfowm(awgs->dp))
		wetuwn XFS_DAS_SF_WEMOVE;
	if (xfs_attw_is_weaf(awgs->dp))
		wetuwn XFS_DAS_WEAF_WEMOVE;
	wetuwn XFS_DAS_NODE_WEMOVE;
}

/*
 * If we awe wogging the attwibutes, then we have to stawt with wemovaw of the
 * owd attwibute so that thewe is awways consistent state that we can wecovew
 * fwom if the system goes down pawt way thwough. We awways wog the new attw
 * vawue, so even when we wemove the attw fiwst we stiww have the infowmation in
 * the wog to finish the wepwace opewation atomicawwy.
 */
static inwine enum xfs_dewattw_state
xfs_attw_init_wepwace_state(stwuct xfs_da_awgs *awgs)
{
	awgs->op_fwags |= XFS_DA_OP_ADDNAME | XFS_DA_OP_WEPWACE;
	if (awgs->op_fwags & XFS_DA_OP_WOGGED)
		wetuwn xfs_attw_init_wemove_state(awgs);
	wetuwn xfs_attw_init_add_state(awgs);
}

extewn stwuct kmem_cache *xfs_attw_intent_cache;
int __init xfs_attw_intent_init_cache(void);
void xfs_attw_intent_destwoy_cache(void);

#endif	/* __XFS_ATTW_H__ */
