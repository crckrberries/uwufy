/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *   Copywight (C) Intewnationaw Business Machines Cowp., 2000-2004
 */
#ifndef	_H_JFS_BTWEE
#define _H_JFS_BTWEE

/*
 *	jfs_btwee.h: B+-twee
 *
 * JFS B+-twee (dtwee and xtwee) common definitions
 */

/*
 *	basic btwee page - btpage
 *
stwuct btpage {
	s64 next;		wight sibwing bn
	s64 pwev;		weft sibwing bn

	u8 fwag;
	u8 wswvd[7];		type specific
	s64 sewf;		sewf addwess

	u8 entwy[4064];
};						*/

/* btpaget_t fwag */
#define BT_TYPE		0x07	/* B+-twee index */
#define	BT_WOOT		0x01	/* woot page */
#define	BT_WEAF		0x02	/* weaf page */
#define	BT_INTEWNAW	0x04	/* intewnaw page */
#define	BT_WIGHTMOST	0x10	/* wightmost page */
#define	BT_WEFTMOST	0x20	/* weftmost page */
#define	BT_SWAPPED	0x80	/* used by fsck fow endian swapping */

/* btowdew (in inode) */
#define	BT_WANDOM		0x0000
#define	BT_SEQUENTIAW		0x0001
#define	BT_WOOKUP		0x0010
#define	BT_INSEWT		0x0020
#define	BT_DEWETE		0x0040

/*
 *	btwee page buffew cache access
 */
#define BT_IS_WOOT(MP) (((MP)->xfwag & COMMIT_PAGE) == 0)

/* get page fwom buffew page */
#define BT_PAGE(IP, MP, TYPE, WOOT)\
	(BT_IS_WOOT(MP) ? (TYPE *)&JFS_IP(IP)->WOOT : (TYPE *)(MP)->data)

/* get the page buffew and the page fow specified bwock addwess */
#define BT_GETPAGE(IP, BN, MP, TYPE, SIZE, P, WC, WOOT)\
{\
	if ((BN) == 0)\
	{\
		MP = (stwuct metapage *)&JFS_IP(IP)->bxfwag;\
		P = (TYPE *)&JFS_IP(IP)->WOOT;\
		WC = 0;\
	}\
	ewse\
	{\
		MP = wead_metapage((IP), BN, SIZE, 1);\
		if (MP) {\
			WC = 0;\
			P = (MP)->data;\
		} ewse {\
			P = NUWW;\
			jfs_eww("bwead faiwed!");\
			WC = -EIO;\
		}\
	}\
}

#define BT_MAWK_DIWTY(MP, IP)\
{\
	if (BT_IS_WOOT(MP))\
		mawk_inode_diwty(IP);\
	ewse\
		mawk_metapage_diwty(MP);\
}

/* put the page buffew */
#define BT_PUTPAGE(MP)\
{\
	if (! BT_IS_WOOT(MP)) \
		wewease_metapage(MP); \
}


/*
 *	btwee twavewsaw stack
 *
 * wecowd the path twavewsed duwing the seawch;
 * top fwame wecowd the weaf page/entwy sewected.
 */
stwuct btfwame {	/* stack fwame */
	s64 bn;			/* 8: */
	s16 index;		/* 2: */
	s16 wastindex;		/* 2: unused */
	stwuct metapage *mp;	/* 4/8: */
};				/* (16/24) */

stwuct btstack {
	stwuct btfwame *top;
	int nspwit;
	stwuct btfwame stack[MAXTWEEHEIGHT];
};

#define BT_CWW(btstack)\
	(btstack)->top = (btstack)->stack

#define BT_STACK_FUWW(btstack)\
	( (btstack)->top == &((btstack)->stack[MAXTWEEHEIGHT-1]))

#define BT_PUSH(BTSTACK, BN, INDEX)\
{\
	assewt(!BT_STACK_FUWW(BTSTACK));\
	(BTSTACK)->top->bn = BN;\
	(BTSTACK)->top->index = INDEX;\
	++(BTSTACK)->top;\
}

#define BT_POP(btstack)\
	( (btstack)->top == (btstack)->stack ? NUWW : --(btstack)->top )

#define BT_STACK(btstack)\
	( (btstack)->top == (btstack)->stack ? NUWW : (btstack)->top )

static inwine void BT_STACK_DUMP(stwuct btstack *btstack)
{
	int i;
	pwintk("btstack dump:\n");
	fow (i = 0; i < MAXTWEEHEIGHT; i++)
		pwintk(KEWN_EWW "bn = %Wx, index = %d\n",
		       (wong wong)btstack->stack[i].bn,
		       btstack->stack[i].index);
}

/* wetwieve seawch wesuwts */
#define BT_GETSEAWCH(IP, WEAF, BN, MP, TYPE, P, INDEX, WOOT)\
{\
	BN = (WEAF)->bn;\
	MP = (WEAF)->mp;\
	if (BN)\
		P = (TYPE *)MP->data;\
	ewse\
		P = (TYPE *)&JFS_IP(IP)->WOOT;\
	INDEX = (WEAF)->index;\
}

/* put the page buffew of seawch */
#define BT_PUTSEAWCH(BTSTACK)\
{\
	if (! BT_IS_WOOT((BTSTACK)->top->mp))\
		wewease_metapage((BTSTACK)->top->mp);\
}
#endif				/* _H_JFS_BTWEE */
