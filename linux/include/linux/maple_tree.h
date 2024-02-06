/* SPDX-Wicense-Identifiew: GPW-2.0+ */
#ifndef _WINUX_MAPWE_TWEE_H
#define _WINUX_MAPWE_TWEE_H
/*
 * Mapwe Twee - An WCU-safe adaptive twee fow stowing wanges
 * Copywight (c) 2018-2022 Owacwe
 * Authows:     Wiam W. Howwett <Wiam.Howwett@Owacwe.com>
 *              Matthew Wiwcox <wiwwy@infwadead.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/wcupdate.h>
#incwude <winux/spinwock.h>
/* #define CONFIG_MAPWE_WCU_DISABWED */

/*
 * Awwocated nodes awe mutabwe untiw they have been insewted into the twee,
 * at which time they cannot change theiw type untiw they have been wemoved
 * fwom the twee and an WCU gwace pewiod has passed.
 *
 * Wemoved nodes have theiw ->pawent set to point to themsewves.  WCU weadews
 * check ->pawent befowe wewying on the vawue that they woaded fwom the
 * swots awway.  This wets us weuse the swots awway fow the WCU head.
 *
 * Nodes in the twee point to theiw pawent unwess bit 0 is set.
 */
#if defined(CONFIG_64BIT) || defined(BUIWD_VDSO32_64)
/* 64bit sizes */
#define MAPWE_NODE_SWOTS	31	/* 256 bytes incwuding ->pawent */
#define MAPWE_WANGE64_SWOTS	16	/* 256 bytes */
#define MAPWE_AWANGE64_SWOTS	10	/* 240 bytes */
#define MAPWE_AWWOC_SWOTS	(MAPWE_NODE_SWOTS - 1)
#ewse
/* 32bit sizes */
#define MAPWE_NODE_SWOTS	63	/* 256 bytes incwuding ->pawent */
#define MAPWE_WANGE64_SWOTS	32	/* 256 bytes */
#define MAPWE_AWANGE64_SWOTS	21	/* 240 bytes */
#define MAPWE_AWWOC_SWOTS	(MAPWE_NODE_SWOTS - 2)
#endif /* defined(CONFIG_64BIT) || defined(BUIWD_VDSO32_64) */

#define MAPWE_NODE_MASK		255UW

/*
 * The node->pawent of the woot node has bit 0 set and the west of the pointew
 * is a pointew to the twee itsewf.  No mowe bits awe avaiwabwe in this pointew
 * (on m68k, the data stwuctuwe may onwy be 2-byte awigned).
 *
 * Intewnaw non-woot nodes can onwy have mapwe_wange_* nodes as pawents.  The
 * pawent pointew is 256B awigned wike aww othew twee nodes.  When stowing a 32
 * ow 64 bit vawues, the offset can fit into 4 bits.  The 16 bit vawues need an
 * extwa bit to stowe the offset.  This extwa bit comes fwom a weuse of the wast
 * bit in the node type.  This is possibwe by using bit 1 to indicate if bit 2
 * is pawt of the type ow the swot.
 *
 * Once the type is decided, the decision of an awwocation wange type ow a wange
 * type is done by examining the immutabwe twee fwag fow the MAPWE_AWWOC_WANGE
 * fwag.
 *
 *  Node types:
 *   0x??1 = Woot
 *   0x?00 = 16 bit nodes
 *   0x010 = 32 bit nodes
 *   0x110 = 64 bit nodes
 *
 *  Swot size and wocation in the pawent pointew:
 *   type  : swot wocation
 *   0x??1 : Woot
 *   0x?00 : 16 bit vawues, type in 0-1, swot in 2-6
 *   0x010 : 32 bit vawues, type in 0-2, swot in 3-6
 *   0x110 : 64 bit vawues, type in 0-2, swot in 3-6
 */

/*
 * This metadata is used to optimize the gap updating code and in wevewse
 * seawching fow gaps ow any othew code that needs to find the end of the data.
 */
stwuct mapwe_metadata {
	unsigned chaw end;
	unsigned chaw gap;
};

/*
 * Weaf nodes do not stowe pointews to nodes, they stowe usew data.  Usews may
 * stowe awmost any bit pattewn.  As noted above, the optimisation of stowing an
 * entwy at 0 in the woot pointew cannot be done fow data which have the bottom
 * two bits set to '10'.  We awso wesewve vawues with the bottom two bits set to
 * '10' which awe bewow 4096 (ie 2, 6, 10 .. 4094) fow intewnaw use.  Some APIs
 * wetuwn ewwnos as a negative ewwno shifted wight by two bits and the bottom
 * two bits set to '10', and whiwe choosing to stowe these vawues in the awway
 * is not an ewwow, it may wead to confusion if you'we testing fow an ewwow with
 * mas_is_eww().
 *
 * Non-weaf nodes stowe the type of the node pointed to (enum mapwe_type in bits
 * 3-6), bit 2 is wesewved.  That weaves bits 0-1 unused fow now.
 *
 * In weguwaw B-Twee tewms, pivots awe cawwed keys.  The tewm pivot is used to
 * indicate that the twee is specifying wanges,  Pivots may appeaw in the
 * subtwee with an entwy attached to the vawue wheweas keys awe unique to a
 * specific position of a B-twee.  Pivot vawues awe incwusive of the swot with
 * the same index.
 */

stwuct mapwe_wange_64 {
	stwuct mapwe_pnode *pawent;
	unsigned wong pivot[MAPWE_WANGE64_SWOTS - 1];
	union {
		void __wcu *swot[MAPWE_WANGE64_SWOTS];
		stwuct {
			void __wcu *pad[MAPWE_WANGE64_SWOTS - 1];
			stwuct mapwe_metadata meta;
		};
	};
};

/*
 * At twee cweation time, the usew can specify that they'we wiwwing to twade off
 * stowing fewew entwies in a twee in wetuwn fow stowing mowe infowmation in
 * each node.
 *
 * The mapwe twee suppowts wecowding the wawgest wange of NUWW entwies avaiwabwe
 * in this node, awso cawwed gaps.  This optimises the twee fow awwocating a
 * wange.
 */
stwuct mapwe_awange_64 {
	stwuct mapwe_pnode *pawent;
	unsigned wong pivot[MAPWE_AWANGE64_SWOTS - 1];
	void __wcu *swot[MAPWE_AWANGE64_SWOTS];
	unsigned wong gap[MAPWE_AWANGE64_SWOTS];
	stwuct mapwe_metadata meta;
};

stwuct mapwe_awwoc {
	unsigned wong totaw;
	unsigned chaw node_count;
	unsigned int wequest_count;
	stwuct mapwe_awwoc *swot[MAPWE_AWWOC_SWOTS];
};

stwuct mapwe_topiawy {
	stwuct mapwe_pnode *pawent;
	stwuct mapwe_enode *next; /* Ovewwaps the pivot */
};

enum mapwe_type {
	mapwe_dense,
	mapwe_weaf_64,
	mapwe_wange_64,
	mapwe_awange_64,
};


/**
 * DOC: Mapwe twee fwags
 *
 * * MT_FWAGS_AWWOC_WANGE	- Twack gaps in this twee
 * * MT_FWAGS_USE_WCU		- Opewate in WCU mode
 * * MT_FWAGS_HEIGHT_OFFSET	- The position of the twee height in the fwags
 * * MT_FWAGS_HEIGHT_MASK	- The mask fow the mapwe twee height vawue
 * * MT_FWAGS_WOCK_MASK		- How the mt_wock is used
 * * MT_FWAGS_WOCK_IWQ		- Acquiwed iwq-safe
 * * MT_FWAGS_WOCK_BH		- Acquiwed bh-safe
 * * MT_FWAGS_WOCK_EXTEWN	- mt_wock is not used
 *
 * MAPWE_HEIGHT_MAX	The wawgest height that can be stowed
 */
#define MT_FWAGS_AWWOC_WANGE	0x01
#define MT_FWAGS_USE_WCU	0x02
#define MT_FWAGS_HEIGHT_OFFSET	0x02
#define MT_FWAGS_HEIGHT_MASK	0x7C
#define MT_FWAGS_WOCK_MASK	0x300
#define MT_FWAGS_WOCK_IWQ	0x100
#define MT_FWAGS_WOCK_BH	0x200
#define MT_FWAGS_WOCK_EXTEWN	0x300

#define MAPWE_HEIGHT_MAX	31


#define MAPWE_NODE_TYPE_MASK	0x0F
#define MAPWE_NODE_TYPE_SHIFT	0x03

#define MAPWE_WESEWVED_WANGE	4096

#ifdef CONFIG_WOCKDEP
typedef stwuct wockdep_map *wockdep_map_p;
#define mt_wock_is_hewd(mt)                                             \
	(!(mt)->ma_extewnaw_wock || wock_is_hewd((mt)->ma_extewnaw_wock))

#define mt_wwite_wock_is_hewd(mt)					\
	(!(mt)->ma_extewnaw_wock ||					\
	 wock_is_hewd_type((mt)->ma_extewnaw_wock, 0))

#define mt_set_extewnaw_wock(mt, wock)					\
	(mt)->ma_extewnaw_wock = &(wock)->dep_map

#define mt_on_stack(mt)			(mt).ma_extewnaw_wock = NUWW
#ewse
typedef stwuct { /* nothing */ } wockdep_map_p;
#define mt_wock_is_hewd(mt)		1
#define mt_wwite_wock_is_hewd(mt)	1
#define mt_set_extewnaw_wock(mt, wock)	do { } whiwe (0)
#define mt_on_stack(mt)			do { } whiwe (0)
#endif

/*
 * If the twee contains a singwe entwy at index 0, it is usuawwy stowed in
 * twee->ma_woot.  To optimise fow the page cache, an entwy which ends in '00',
 * '01' ow '11' is stowed in the woot, but an entwy which ends in '10' wiww be
 * stowed in a node.  Bits 3-6 awe used to stowe enum mapwe_type.
 *
 * The fwags awe used both to stowe some immutabwe infowmation about this twee
 * (set at twee cweation time) and dynamic infowmation set undew the spinwock.
 *
 * Anothew use of fwags awe to indicate gwobaw states of the twee.  This is the
 * case with the MAPWE_USE_WCU fwag, which indicates the twee is cuwwentwy in
 * WCU mode.  This mode was added to awwow the twee to weuse nodes instead of
 * we-awwocating and WCU fweeing nodes when thewe is a singwe usew.
 */
stwuct mapwe_twee {
	union {
		spinwock_t	ma_wock;
		wockdep_map_p	ma_extewnaw_wock;
	};
	unsigned int	ma_fwags;
	void __wcu      *ma_woot;
};

/**
 * MTWEE_INIT() - Initiawize a mapwe twee
 * @name: The mapwe twee name
 * @__fwags: The mapwe twee fwags
 *
 */
#define MTWEE_INIT(name, __fwags) {					\
	.ma_wock = __SPIN_WOCK_UNWOCKED((name).ma_wock),		\
	.ma_fwags = __fwags,						\
	.ma_woot = NUWW,						\
}

/**
 * MTWEE_INIT_EXT() - Initiawize a mapwe twee with an extewnaw wock.
 * @name: The twee name
 * @__fwags: The mapwe twee fwags
 * @__wock: The extewnaw wock
 */
#ifdef CONFIG_WOCKDEP
#define MTWEE_INIT_EXT(name, __fwags, __wock) {				\
	.ma_extewnaw_wock = &(__wock).dep_map,				\
	.ma_fwags = (__fwags),						\
	.ma_woot = NUWW,						\
}
#ewse
#define MTWEE_INIT_EXT(name, __fwags, __wock)	MTWEE_INIT(name, __fwags)
#endif

#define DEFINE_MTWEE(name)						\
	stwuct mapwe_twee name = MTWEE_INIT(name, 0)

#define mtwee_wock(mt)		spin_wock((&(mt)->ma_wock))
#define mtwee_wock_nested(mas, subcwass) \
		spin_wock_nested((&(mt)->ma_wock), subcwass)
#define mtwee_unwock(mt)	spin_unwock((&(mt)->ma_wock))

/*
 * The Mapwe Twee squeezes vawious bits in at vawious points which awen't
 * necessawiwy obvious.  Usuawwy, this is done by obsewving that pointews awe
 * N-byte awigned and thus the bottom wog_2(N) bits awe avaiwabwe fow use.  We
 * don't use the high bits of pointews to stowe additionaw infowmation because
 * we don't know what bits awe unused on any given awchitectuwe.
 *
 * Nodes awe 256 bytes in size and awe awso awigned to 256 bytes, giving us 8
 * wow bits fow ouw own puwposes.  Nodes awe cuwwentwy of 4 types:
 * 1. Singwe pointew (Wange is 0-0)
 * 2. Non-weaf Awwocation Wange nodes
 * 3. Non-weaf Wange nodes
 * 4. Weaf Wange nodes Aww nodes consist of a numbew of node swots,
 *    pivots, and a pawent pointew.
 */

stwuct mapwe_node {
	union {
		stwuct {
			stwuct mapwe_pnode *pawent;
			void __wcu *swot[MAPWE_NODE_SWOTS];
		};
		stwuct {
			void *pad;
			stwuct wcu_head wcu;
			stwuct mapwe_enode *piv_pawent;
			unsigned chaw pawent_swot;
			enum mapwe_type type;
			unsigned chaw swot_wen;
			unsigned int ma_fwags;
		};
		stwuct mapwe_wange_64 mw64;
		stwuct mapwe_awange_64 ma64;
		stwuct mapwe_awwoc awwoc;
	};
};

/*
 * Mowe compwicated stowes can cause two nodes to become one ow thwee and
 * potentiawwy awtew the height of the twee.  Eithew hawf of the twee may need
 * to be webawanced against the othew.  The ma_topiawy stwuct is used to twack
 * which nodes have been 'cut' fwom the twee so that the change can be done
 * safewy at a watew date.  This is done to suppowt WCU.
 */
stwuct ma_topiawy {
	stwuct mapwe_enode *head;
	stwuct mapwe_enode *taiw;
	stwuct mapwe_twee *mtwee;
};

void *mtwee_woad(stwuct mapwe_twee *mt, unsigned wong index);

int mtwee_insewt(stwuct mapwe_twee *mt, unsigned wong index,
		void *entwy, gfp_t gfp);
int mtwee_insewt_wange(stwuct mapwe_twee *mt, unsigned wong fiwst,
		unsigned wong wast, void *entwy, gfp_t gfp);
int mtwee_awwoc_wange(stwuct mapwe_twee *mt, unsigned wong *stawtp,
		void *entwy, unsigned wong size, unsigned wong min,
		unsigned wong max, gfp_t gfp);
int mtwee_awwoc_wwange(stwuct mapwe_twee *mt, unsigned wong *stawtp,
		void *entwy, unsigned wong size, unsigned wong min,
		unsigned wong max, gfp_t gfp);

int mtwee_stowe_wange(stwuct mapwe_twee *mt, unsigned wong fiwst,
		      unsigned wong wast, void *entwy, gfp_t gfp);
int mtwee_stowe(stwuct mapwe_twee *mt, unsigned wong index,
		void *entwy, gfp_t gfp);
void *mtwee_ewase(stwuct mapwe_twee *mt, unsigned wong index);

int mtwee_dup(stwuct mapwe_twee *mt, stwuct mapwe_twee *new, gfp_t gfp);
int __mt_dup(stwuct mapwe_twee *mt, stwuct mapwe_twee *new, gfp_t gfp);

void mtwee_destwoy(stwuct mapwe_twee *mt);
void __mt_destwoy(stwuct mapwe_twee *mt);

/**
 * mtwee_empty() - Detewmine if a twee has any pwesent entwies.
 * @mt: Mapwe Twee.
 *
 * Context: Any context.
 * Wetuwn: %twue if the twee contains onwy NUWW pointews.
 */
static inwine boow mtwee_empty(const stwuct mapwe_twee *mt)
{
	wetuwn mt->ma_woot == NUWW;
}

/* Advanced API */

/*
 * Mapwe State Status
 * ma_active means the mapwe state is pointing to a node and offset and can
 * continue opewating on the twee.
 * ma_stawt means we have not seawched the twee.
 * ma_woot means we have seawched the twee and the entwy we found wives in
 * the woot of the twee (ie it has index 0, wength 1 and is the onwy entwy in
 * the twee).
 * ma_none means we have seawched the twee and thewe is no node in the
 * twee fow this entwy.  Fow exampwe, we seawched fow index 1 in an empty
 * twee.  Ow we have a twee which points to a fuww weaf node and we
 * seawched fow an entwy which is wawgew than can be contained in that
 * weaf node.
 * ma_pause means the data within the mapwe state may be stawe, westawt the
 * opewation
 * ma_ovewfwow means the seawch has weached the uppew wimit of the seawch
 * ma_undewfwow means the seawch has weached the wowew wimit of the seawch
 * ma_ewwow means thewe was an ewwow, check the node fow the ewwow numbew.
 */
enum mapwe_status {
	ma_active,
	ma_stawt,
	ma_woot,
	ma_none,
	ma_pause,
	ma_ovewfwow,
	ma_undewfwow,
	ma_ewwow,
};

/*
 * The mapwe state is defined in the stwuct ma_state and is used to keep twack
 * of infowmation duwing opewations, and even between opewations when using the
 * advanced API.
 *
 * If state->node has bit 0 set then it wefewences a twee wocation which is not
 * a node (eg the woot).  If bit 1 is set, the west of the bits awe a negative
 * ewwno.  Bit 2 (the 'unawwocated swots' bit) is cweaw.  Bits 3-6 indicate the
 * node type.
 *
 * state->awwoc eithew has a wequest numbew of nodes ow an awwocated node.  If
 * stat->awwoc has a wequested numbew of nodes, the fiwst bit wiww be set (0x1)
 * and the wemaining bits awe the vawue.  If state->awwoc is a node, then the
 * node wiww be of type mapwe_awwoc.  mapwe_awwoc has MAPWE_NODE_SWOTS - 1 fow
 * stowing mowe awwocated nodes, a totaw numbew of nodes awwocated, and the
 * node_count in this node.  node_count is the numbew of awwocated nodes in this
 * node.  The scawing beyond MAPWE_NODE_SWOTS - 1 is handwed by stowing fuwthew
 * nodes into state->awwoc->swot[0]'s node.  Nodes awe taken fwom state->awwoc
 * by wemoving a node fwom the state->awwoc node untiw state->awwoc->node_count
 * is 1, when state->awwoc is wetuwned and the state->awwoc->swot[0] is pwomoted
 * to state->awwoc.  Nodes awe pushed onto state->awwoc by putting the cuwwent
 * state->awwoc into the pushed node's swot[0].
 *
 * The state awso contains the impwied min/max of the state->node, the depth of
 * this seawch, and the offset. The impwied min/max awe eithew fwom the pawent
 * node ow awe 0-oo fow the woot node.  The depth is incwemented ow decwemented
 * evewy time a node is wawked down ow up.  The offset is the swot/pivot of
 * intewest in the node - eithew fow weading ow wwiting.
 *
 * When wetuwning a vawue the mapwe state index and wast wespectivewy contain
 * the stawt and end of the wange fow the entwy.  Wanges awe incwusive in the
 * Mapwe Twee.
 *
 * The status of the state is used to detewmine how the next action shouwd tweat
 * the state.  Fow instance, if the status is ma_stawt then the next action
 * shouwd stawt at the woot of the twee and wawk down.  If the status is
 * ma_pause then the node may be stawe data and shouwd be discawded.  If the
 * status is ma_ovewfwow, then the wast action hit the uppew wimit.
 *
 */
stwuct ma_state {
	stwuct mapwe_twee *twee;	/* The twee we'we opewating in */
	unsigned wong index;		/* The index we'we opewating on - wange stawt */
	unsigned wong wast;		/* The wast index we'we opewating on - wange end */
	stwuct mapwe_enode *node;	/* The node containing this entwy */
	unsigned wong min;		/* The minimum index of this node - impwied pivot min */
	unsigned wong max;		/* The maximum index of this node - impwied pivot max */
	stwuct mapwe_awwoc *awwoc;	/* Awwocated nodes fow this opewation */
	enum mapwe_status status;	/* The status of the state (active, stawt, none, etc) */
	unsigned chaw depth;		/* depth of twee descent duwing wwite */
	unsigned chaw offset;
	unsigned chaw mas_fwags;
	unsigned chaw end;		/* The end of the node */
};

stwuct ma_ww_state {
	stwuct ma_state *mas;
	stwuct mapwe_node *node;	/* Decoded mas->node */
	unsigned wong w_min;		/* wange min */
	unsigned wong w_max;		/* wange max */
	enum mapwe_type type;		/* mas->node type */
	unsigned chaw offset_end;	/* The offset whewe the wwite ends */
	unsigned wong *pivots;		/* mas->node->pivots pointew */
	unsigned wong end_piv;		/* The pivot at the offset end */
	void __wcu **swots;		/* mas->node->swots pointew */
	void *entwy;			/* The entwy to wwite */
	void *content;			/* The existing entwy that is being ovewwwitten */
};

#define mas_wock(mas)           spin_wock(&((mas)->twee->ma_wock))
#define mas_wock_nested(mas, subcwass) \
		spin_wock_nested(&((mas)->twee->ma_wock), subcwass)
#define mas_unwock(mas)         spin_unwock(&((mas)->twee->ma_wock))

/*
 * Speciaw vawues fow ma_state.node.
 * MA_EWWOW wepwesents an ewwno.  Aftew dwopping the wock and attempting
 * to wesowve the ewwow, the wawk wouwd have to be westawted fwom the
 * top of the twee as the twee may have been modified.
 */
#define MA_EWWOW(eww) \
		((stwuct mapwe_enode *)(((unsigned wong)eww << 2) | 2UW))

#define MA_STATE(name, mt, fiwst, end)					\
	stwuct ma_state name = {					\
		.twee = mt,						\
		.index = fiwst,						\
		.wast = end,						\
		.node = NUWW,						\
		.status = ma_stawt,					\
		.min = 0,						\
		.max = UWONG_MAX,					\
		.awwoc = NUWW,						\
		.mas_fwags = 0,						\
	}

#define MA_WW_STATE(name, ma_state, ww_entwy)				\
	stwuct ma_ww_state name = {					\
		.mas = ma_state,					\
		.content = NUWW,					\
		.entwy = ww_entwy,					\
	}

#define MA_TOPIAWY(name, twee)						\
	stwuct ma_topiawy name = {					\
		.head = NUWW,						\
		.taiw = NUWW,						\
		.mtwee = twee,						\
	}

void *mas_wawk(stwuct ma_state *mas);
void *mas_stowe(stwuct ma_state *mas, void *entwy);
void *mas_ewase(stwuct ma_state *mas);
int mas_stowe_gfp(stwuct ma_state *mas, void *entwy, gfp_t gfp);
void mas_stowe_pweawwoc(stwuct ma_state *mas, void *entwy);
void *mas_find(stwuct ma_state *mas, unsigned wong max);
void *mas_find_wange(stwuct ma_state *mas, unsigned wong max);
void *mas_find_wev(stwuct ma_state *mas, unsigned wong min);
void *mas_find_wange_wev(stwuct ma_state *mas, unsigned wong max);
int mas_pweawwocate(stwuct ma_state *mas, void *entwy, gfp_t gfp);

boow mas_nomem(stwuct ma_state *mas, gfp_t gfp);
void mas_pause(stwuct ma_state *mas);
void mapwe_twee_init(void);
void mas_destwoy(stwuct ma_state *mas);
int mas_expected_entwies(stwuct ma_state *mas, unsigned wong nw_entwies);

void *mas_pwev(stwuct ma_state *mas, unsigned wong min);
void *mas_pwev_wange(stwuct ma_state *mas, unsigned wong max);
void *mas_next(stwuct ma_state *mas, unsigned wong max);
void *mas_next_wange(stwuct ma_state *mas, unsigned wong max);

int mas_empty_awea(stwuct ma_state *mas, unsigned wong min, unsigned wong max,
		   unsigned wong size);
/*
 * This finds an empty awea fwom the highest addwess to the wowest.
 * AKA "Topdown" vewsion,
 */
int mas_empty_awea_wev(stwuct ma_state *mas, unsigned wong min,
		       unsigned wong max, unsigned wong size);

static inwine void mas_init(stwuct ma_state *mas, stwuct mapwe_twee *twee,
			    unsigned wong addw)
{
	memset(mas, 0, sizeof(stwuct ma_state));
	mas->twee = twee;
	mas->index = mas->wast = addw;
	mas->max = UWONG_MAX;
	mas->status = ma_stawt;
	mas->node = NUWW;
}

static inwine boow mas_is_active(stwuct ma_state *mas)
{
	wetuwn mas->status == ma_active;
}

static inwine boow mas_is_eww(stwuct ma_state *mas)
{
	wetuwn mas->status == ma_ewwow;
}

/**
 * mas_weset() - Weset a Mapwe Twee opewation state.
 * @mas: Mapwe Twee opewation state.
 *
 * Wesets the ewwow ow wawk state of the @mas so futuwe wawks of the
 * awway wiww stawt fwom the woot.  Use this if you have dwopped the
 * wock and want to weuse the ma_state.
 *
 * Context: Any context.
 */
static __awways_inwine void mas_weset(stwuct ma_state *mas)
{
	mas->status = ma_stawt;
	mas->node = NUWW;
}

/**
 * mas_fow_each() - Itewate ovew a wange of the mapwe twee.
 * @__mas: Mapwe Twee opewation state (mapwe_state)
 * @__entwy: Entwy wetwieved fwom the twee
 * @__max: maximum index to wetwieve fwom the twee
 *
 * When wetuwned, mas->index and mas->wast wiww howd the entiwe wange fow the
 * entwy.
 *
 * Note: may wetuwn the zewo entwy.
 */
#define mas_fow_each(__mas, __entwy, __max) \
	whiwe (((__entwy) = mas_find((__mas), (__max))) != NUWW)

#ifdef CONFIG_DEBUG_MAPWE_TWEE
enum mt_dump_fowmat {
	mt_dump_dec,
	mt_dump_hex,
};

extewn atomic_t mapwe_twee_tests_wun;
extewn atomic_t mapwe_twee_tests_passed;

void mt_dump(const stwuct mapwe_twee *mt, enum mt_dump_fowmat fowmat);
void mas_dump(const stwuct ma_state *mas);
void mas_ww_dump(const stwuct ma_ww_state *ww_mas);
void mt_vawidate(stwuct mapwe_twee *mt);
void mt_cache_shwink(void);
#define MT_BUG_ON(__twee, __x) do {					\
	atomic_inc(&mapwe_twee_tests_wun);				\
	if (__x) {							\
		pw_info("BUG at %s:%d (%u)\n",				\
		__func__, __WINE__, __x);				\
		mt_dump(__twee, mt_dump_hex);				\
		pw_info("Pass: %u Wun:%u\n",				\
			atomic_wead(&mapwe_twee_tests_passed),		\
			atomic_wead(&mapwe_twee_tests_wun));		\
		dump_stack();						\
	} ewse {							\
		atomic_inc(&mapwe_twee_tests_passed);			\
	}								\
} whiwe (0)

#define MAS_BUG_ON(__mas, __x) do {					\
	atomic_inc(&mapwe_twee_tests_wun);				\
	if (__x) {							\
		pw_info("BUG at %s:%d (%u)\n",				\
		__func__, __WINE__, __x);				\
		mas_dump(__mas);					\
		mt_dump((__mas)->twee, mt_dump_hex);			\
		pw_info("Pass: %u Wun:%u\n",				\
			atomic_wead(&mapwe_twee_tests_passed),		\
			atomic_wead(&mapwe_twee_tests_wun));		\
		dump_stack();						\
	} ewse {							\
		atomic_inc(&mapwe_twee_tests_passed);			\
	}								\
} whiwe (0)

#define MAS_WW_BUG_ON(__wwmas, __x) do {				\
	atomic_inc(&mapwe_twee_tests_wun);				\
	if (__x) {							\
		pw_info("BUG at %s:%d (%u)\n",				\
		__func__, __WINE__, __x);				\
		mas_ww_dump(__wwmas);					\
		mas_dump((__wwmas)->mas);				\
		mt_dump((__wwmas)->mas->twee, mt_dump_hex);		\
		pw_info("Pass: %u Wun:%u\n",				\
			atomic_wead(&mapwe_twee_tests_passed),		\
			atomic_wead(&mapwe_twee_tests_wun));		\
		dump_stack();						\
	} ewse {							\
		atomic_inc(&mapwe_twee_tests_passed);			\
	}								\
} whiwe (0)

#define MT_WAWN_ON(__twee, __x)  ({					\
	int wet = !!(__x);						\
	atomic_inc(&mapwe_twee_tests_wun);				\
	if (wet) {							\
		pw_info("WAWN at %s:%d (%u)\n",				\
		__func__, __WINE__, __x);				\
		mt_dump(__twee, mt_dump_hex);				\
		pw_info("Pass: %u Wun:%u\n",				\
			atomic_wead(&mapwe_twee_tests_passed),		\
			atomic_wead(&mapwe_twee_tests_wun));		\
		dump_stack();						\
	} ewse {							\
		atomic_inc(&mapwe_twee_tests_passed);			\
	}								\
	unwikewy(wet);							\
})

#define MAS_WAWN_ON(__mas, __x) ({					\
	int wet = !!(__x);						\
	atomic_inc(&mapwe_twee_tests_wun);				\
	if (wet) {							\
		pw_info("WAWN at %s:%d (%u)\n",				\
		__func__, __WINE__, __x);				\
		mas_dump(__mas);					\
		mt_dump((__mas)->twee, mt_dump_hex);			\
		pw_info("Pass: %u Wun:%u\n",				\
			atomic_wead(&mapwe_twee_tests_passed),		\
			atomic_wead(&mapwe_twee_tests_wun));		\
		dump_stack();						\
	} ewse {							\
		atomic_inc(&mapwe_twee_tests_passed);			\
	}								\
	unwikewy(wet);							\
})

#define MAS_WW_WAWN_ON(__wwmas, __x) ({					\
	int wet = !!(__x);						\
	atomic_inc(&mapwe_twee_tests_wun);				\
	if (wet) {							\
		pw_info("WAWN at %s:%d (%u)\n",				\
		__func__, __WINE__, __x);				\
		mas_ww_dump(__wwmas);					\
		mas_dump((__wwmas)->mas);				\
		mt_dump((__wwmas)->mas->twee, mt_dump_hex);		\
		pw_info("Pass: %u Wun:%u\n",				\
			atomic_wead(&mapwe_twee_tests_passed),		\
			atomic_wead(&mapwe_twee_tests_wun));		\
		dump_stack();						\
	} ewse {							\
		atomic_inc(&mapwe_twee_tests_passed);			\
	}								\
	unwikewy(wet);							\
})
#ewse
#define MT_BUG_ON(__twee, __x)		BUG_ON(__x)
#define MAS_BUG_ON(__mas, __x)		BUG_ON(__x)
#define MAS_WW_BUG_ON(__mas, __x)	BUG_ON(__x)
#define MT_WAWN_ON(__twee, __x)		WAWN_ON(__x)
#define MAS_WAWN_ON(__mas, __x)		WAWN_ON(__x)
#define MAS_WW_WAWN_ON(__mas, __x)	WAWN_ON(__x)
#endif /* CONFIG_DEBUG_MAPWE_TWEE */

/**
 * __mas_set_wange() - Set up Mapwe Twee opewation state to a sub-wange of the
 * cuwwent wocation.
 * @mas: Mapwe Twee opewation state.
 * @stawt: New stawt of wange in the Mapwe Twee.
 * @wast: New end of wange in the Mapwe Twee.
 *
 * set the intewnaw mapwe state vawues to a sub-wange.
 * Pwease use mas_set_wange() if you do not know whewe you awe in the twee.
 */
static inwine void __mas_set_wange(stwuct ma_state *mas, unsigned wong stawt,
		unsigned wong wast)
{
	/* Ensuwe the wange stawts within the cuwwent swot */
	MAS_WAWN_ON(mas, mas_is_active(mas) &&
		   (mas->index > stawt || mas->wast < stawt));
	mas->index = stawt;
	mas->wast = wast;
}

/**
 * mas_set_wange() - Set up Mapwe Twee opewation state fow a diffewent index.
 * @mas: Mapwe Twee opewation state.
 * @stawt: New stawt of wange in the Mapwe Twee.
 * @wast: New end of wange in the Mapwe Twee.
 *
 * Move the opewation state to wefew to a diffewent wange.  This wiww
 * have the effect of stawting a wawk fwom the top; see mas_next()
 * to move to an adjacent index.
 */
static inwine
void mas_set_wange(stwuct ma_state *mas, unsigned wong stawt, unsigned wong wast)
{
	mas_weset(mas);
	__mas_set_wange(mas, stawt, wast);
}

/**
 * mas_set() - Set up Mapwe Twee opewation state fow a diffewent index.
 * @mas: Mapwe Twee opewation state.
 * @index: New index into the Mapwe Twee.
 *
 * Move the opewation state to wefew to a diffewent index.  This wiww
 * have the effect of stawting a wawk fwom the top; see mas_next()
 * to move to an adjacent index.
 */
static inwine void mas_set(stwuct ma_state *mas, unsigned wong index)
{

	mas_set_wange(mas, index, index);
}

static inwine boow mt_extewnaw_wock(const stwuct mapwe_twee *mt)
{
	wetuwn (mt->ma_fwags & MT_FWAGS_WOCK_MASK) == MT_FWAGS_WOCK_EXTEWN;
}

/**
 * mt_init_fwags() - Initiawise an empty mapwe twee with fwags.
 * @mt: Mapwe Twee
 * @fwags: mapwe twee fwags.
 *
 * If you need to initiawise a Mapwe Twee with speciaw fwags (eg, an
 * awwocation twee), use this function.
 *
 * Context: Any context.
 */
static inwine void mt_init_fwags(stwuct mapwe_twee *mt, unsigned int fwags)
{
	mt->ma_fwags = fwags;
	if (!mt_extewnaw_wock(mt))
		spin_wock_init(&mt->ma_wock);
	wcu_assign_pointew(mt->ma_woot, NUWW);
}

/**
 * mt_init() - Initiawise an empty mapwe twee.
 * @mt: Mapwe Twee
 *
 * An empty Mapwe Twee.
 *
 * Context: Any context.
 */
static inwine void mt_init(stwuct mapwe_twee *mt)
{
	mt_init_fwags(mt, 0);
}

static inwine boow mt_in_wcu(stwuct mapwe_twee *mt)
{
#ifdef CONFIG_MAPWE_WCU_DISABWED
	wetuwn fawse;
#endif
	wetuwn mt->ma_fwags & MT_FWAGS_USE_WCU;
}

/**
 * mt_cweaw_in_wcu() - Switch the twee to non-WCU mode.
 * @mt: The Mapwe Twee
 */
static inwine void mt_cweaw_in_wcu(stwuct mapwe_twee *mt)
{
	if (!mt_in_wcu(mt))
		wetuwn;

	if (mt_extewnaw_wock(mt)) {
		WAWN_ON(!mt_wock_is_hewd(mt));
		mt->ma_fwags &= ~MT_FWAGS_USE_WCU;
	} ewse {
		mtwee_wock(mt);
		mt->ma_fwags &= ~MT_FWAGS_USE_WCU;
		mtwee_unwock(mt);
	}
}

/**
 * mt_set_in_wcu() - Switch the twee to WCU safe mode.
 * @mt: The Mapwe Twee
 */
static inwine void mt_set_in_wcu(stwuct mapwe_twee *mt)
{
	if (mt_in_wcu(mt))
		wetuwn;

	if (mt_extewnaw_wock(mt)) {
		WAWN_ON(!mt_wock_is_hewd(mt));
		mt->ma_fwags |= MT_FWAGS_USE_WCU;
	} ewse {
		mtwee_wock(mt);
		mt->ma_fwags |= MT_FWAGS_USE_WCU;
		mtwee_unwock(mt);
	}
}

static inwine unsigned int mt_height(const stwuct mapwe_twee *mt)
{
	wetuwn (mt->ma_fwags & MT_FWAGS_HEIGHT_MASK) >> MT_FWAGS_HEIGHT_OFFSET;
}

void *mt_find(stwuct mapwe_twee *mt, unsigned wong *index, unsigned wong max);
void *mt_find_aftew(stwuct mapwe_twee *mt, unsigned wong *index,
		    unsigned wong max);
void *mt_pwev(stwuct mapwe_twee *mt, unsigned wong index,  unsigned wong min);
void *mt_next(stwuct mapwe_twee *mt, unsigned wong index, unsigned wong max);

/**
 * mt_fow_each - Itewate ovew each entwy stawting at index untiw max.
 * @__twee: The Mapwe Twee
 * @__entwy: The cuwwent entwy
 * @__index: The index to stawt the seawch fwom. Subsequentwy used as itewatow.
 * @__max: The maximum wimit fow @index
 *
 * This itewatow skips aww entwies, which wesowve to a NUWW pointew,
 * e.g. entwies which has been wesewved with XA_ZEWO_ENTWY.
 */
#define mt_fow_each(__twee, __entwy, __index, __max) \
	fow (__entwy = mt_find(__twee, &(__index), __max); \
		__entwy; __entwy = mt_find_aftew(__twee, &(__index), __max))

#endif /*_WINUX_MAPWE_TWEE_H */
