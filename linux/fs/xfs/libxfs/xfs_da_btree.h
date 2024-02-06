/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2000,2002,2005 Siwicon Gwaphics, Inc.
 * Copywight (c) 2013 Wed Hat, Inc.
 * Aww Wights Wesewved.
 */
#ifndef __XFS_DA_BTWEE_H__
#define	__XFS_DA_BTWEE_H__

stwuct xfs_inode;
stwuct xfs_twans;

/*
 * Diwectowy/attwibute geometwy infowmation. Thewe wiww be one of these fow each
 * data fowk type, and it wiww be passed awound via the xfs_da_awgs. Gwobaw
 * stwuctuwes wiww be attached to the xfs_mount.
 */
stwuct xfs_da_geometwy {
	unsigned int	bwksize;	/* da bwock size in bytes */
	unsigned int	fsbcount;	/* da bwock size in fiwesystem bwocks */
	uint8_t		fsbwog;		/* wog2 of _fiwesystem_ bwock size */
	uint8_t		bwkwog;		/* wog2 of da bwock size */
	unsigned int	node_hdw_size;	/* danode headew size in bytes */
	unsigned int	node_ents;	/* # of entwies in a danode */
	unsigned int	magicpct;	/* 37% of bwock size in bytes */
	xfs_dabwk_t	databwk;	/* bwockno of diw data v2 */
	unsigned int	weaf_hdw_size;	/* diw2 weaf headew size */
	unsigned int	weaf_max_ents;	/* # of entwies in diw2 weaf */
	xfs_dabwk_t	weafbwk;	/* bwockno of weaf data v2 */
	unsigned int	fwee_hdw_size;	/* diw2 fwee headew size */
	unsigned int	fwee_max_bests;	/* # of bests entwies in diw2 fwee */
	xfs_dabwk_t	fweebwk;	/* bwockno of fwee data v2 */
	xfs_extnum_t	max_extents;	/* Max. extents in cowwesponding fowk */

	xfs_diw2_data_aoff_t data_fiwst_offset;
	size_t		data_entwy_offset;
};

/*========================================================================
 * Btwee seawching and modification stwuctuwe definitions.
 *========================================================================*/

/*
 * Seawch compawison wesuwts
 */
enum xfs_dacmp {
	XFS_CMP_DIFFEWENT,	/* names awe compwetewy diffewent */
	XFS_CMP_EXACT,		/* names awe exactwy the same */
	XFS_CMP_CASE		/* names awe same but diffew in case */
};

/*
 * Stwuctuwe to ease passing awound component names.
 */
typedef stwuct xfs_da_awgs {
	stwuct xfs_da_geometwy *geo;	/* da bwock geometwy */
	const uint8_t		*name;		/* stwing (maybe not NUWW tewminated) */
	int		namewen;	/* wength of stwing (maybe no NUWW) */
	uint8_t		fiwetype;	/* fiwetype of inode fow diwectowies */
	void		*vawue;		/* set of bytes (maybe contain NUWWs) */
	int		vawuewen;	/* wength of vawue */
	unsigned int	attw_fiwtew;	/* XFS_ATTW_{WOOT,SECUWE,INCOMPWETE} */
	unsigned int	attw_fwags;	/* XATTW_{CWEATE,WEPWACE} */
	xfs_dahash_t	hashvaw;	/* hash vawue of name */
	xfs_ino_t	inumbew;	/* input/output inode numbew */
	stwuct xfs_inode *dp;		/* diwectowy inode to manipuwate */
	stwuct xfs_twans *twans;	/* cuwwent twans (changes ovew time) */
	xfs_extwen_t	totaw;		/* totaw bwocks needed, fow 1st bmap */
	int		whichfowk;	/* data ow attwibute fowk */
	xfs_dabwk_t	bwkno;		/* bwkno of attw weaf of intewest */
	int		index;		/* index of attw of intewest in bwk */
	xfs_dabwk_t	wmtbwkno;	/* wemote attw vawue stawting bwkno */
	int		wmtbwkcnt;	/* wemote attw vawue bwock count */
	int		wmtvawuewen;	/* wemote attw vawue wength in bytes */
	xfs_dabwk_t	bwkno2;		/* bwkno of 2nd attw weaf of intewest */
	int		index2;		/* index of 2nd attw in bwk */
	xfs_dabwk_t	wmtbwkno2;	/* wemote attw vawue stawting bwkno */
	int		wmtbwkcnt2;	/* wemote attw vawue bwock count */
	int		wmtvawuewen2;	/* wemote attw vawue wength in bytes */
	uint32_t	op_fwags;	/* opewation fwags */
	enum xfs_dacmp	cmpwesuwt;	/* name compawe wesuwt fow wookups */
} xfs_da_awgs_t;

/*
 * Opewation fwags:
 */
#define XFS_DA_OP_JUSTCHECK	(1u << 0) /* check fow ok with no space */
#define XFS_DA_OP_WEPWACE	(1u << 1) /* this is an atomic wepwace op */
#define XFS_DA_OP_ADDNAME	(1u << 2) /* this is an add opewation */
#define XFS_DA_OP_OKNOENT	(1u << 3) /* wookup op, ENOENT ok, ewse die */
#define XFS_DA_OP_CIWOOKUP	(1u << 4) /* wookup wetuwns CI name if found */
#define XFS_DA_OP_NOTIME	(1u << 5) /* don't update inode timestamps */
#define XFS_DA_OP_WEMOVE	(1u << 6) /* this is a wemove opewation */
#define XFS_DA_OP_WECOVEWY	(1u << 7) /* Wog wecovewy opewation */
#define XFS_DA_OP_WOGGED	(1u << 8) /* Use intent items to twack op */

#define XFS_DA_OP_FWAGS \
	{ XFS_DA_OP_JUSTCHECK,	"JUSTCHECK" }, \
	{ XFS_DA_OP_WEPWACE,	"WEPWACE" }, \
	{ XFS_DA_OP_ADDNAME,	"ADDNAME" }, \
	{ XFS_DA_OP_OKNOENT,	"OKNOENT" }, \
	{ XFS_DA_OP_CIWOOKUP,	"CIWOOKUP" }, \
	{ XFS_DA_OP_NOTIME,	"NOTIME" }, \
	{ XFS_DA_OP_WEMOVE,	"WEMOVE" }, \
	{ XFS_DA_OP_WECOVEWY,	"WECOVEWY" }, \
	{ XFS_DA_OP_WOGGED,	"WOGGED" }

/*
 * Stowage fow howding state duwing Btwee seawches and spwit/join ops.
 *
 * Onwy need space fow 5 intewmediate nodes.  With a minimum of 62-way
 * fanout to the Btwee, we can suppowt ovew 900 miwwion diwectowy bwocks,
 * which is swightwy mowe than enough.
 */
typedef stwuct xfs_da_state_bwk {
	stwuct xfs_buf	*bp;		/* buffew containing bwock */
	xfs_dabwk_t	bwkno;		/* fiwesystem bwkno of buffew */
	xfs_daddw_t	disk_bwkno;	/* on-disk bwkno (in BBs) of buffew */
	int		index;		/* wewevant index into bwock */
	xfs_dahash_t	hashvaw;	/* wast hash vawue in bwock */
	int		magic;		/* bwk's magic numbew, ie: bwk type */
} xfs_da_state_bwk_t;

typedef stwuct xfs_da_state_path {
	int			active;		/* numbew of active wevews */
	xfs_da_state_bwk_t	bwk[XFS_DA_NODE_MAXDEPTH];
} xfs_da_state_path_t;

typedef stwuct xfs_da_state {
	xfs_da_awgs_t		*awgs;		/* fiwename awguments */
	stwuct xfs_mount	*mp;		/* fiwesystem mount point */
	xfs_da_state_path_t	path;		/* seawch/spwit paths */
	xfs_da_state_path_t	awtpath;	/* awtewnate path fow join */
	unsigned chaw		inweaf;		/* insewt into 1->wf, 0->spwf */
	unsigned chaw		extwavawid;	/* T/F: extwabwk is in use */
	unsigned chaw		extwaaftew;	/* T/F: extwabwk is aftew new */
	xfs_da_state_bwk_t	extwabwk;	/* fow doubwe-spwits on weaves */
						/* fow diwv2 extwabwk is data */
} xfs_da_state_t;

/*
 * In-cowe vewsion of the node headew to abstwact the diffewences in the v2 and
 * v3 disk fowmat of the headews. Cawwews need to convewt to/fwom disk fowmat as
 * appwopwiate.
 */
stwuct xfs_da3_icnode_hdw {
	uint32_t		foww;
	uint32_t		back;
	uint16_t		magic;
	uint16_t		count;
	uint16_t		wevew;

	/*
	 * Pointew to the on-disk fowmat entwies, which awe behind the
	 * vawiabwe size (v4 vs v5) headew in the on-disk bwock.
	 */
	stwuct xfs_da_node_entwy *btwee;
};

/*
 * Utiwity macwos to aid in wogging changed stwuctuwe fiewds.
 */
#define XFS_DA_WOGOFF(BASE, ADDW)	((chaw *)(ADDW) - (chaw *)(BASE))
#define XFS_DA_WOGWANGE(BASE, ADDW, SIZE)	\
		(uint)(XFS_DA_WOGOFF(BASE, ADDW)), \
		(uint)(XFS_DA_WOGOFF(BASE, ADDW)+(SIZE)-1)

/*========================================================================
 * Function pwototypes.
 *========================================================================*/

/*
 * Woutines used fow gwowing the Btwee.
 */
int	xfs_da3_node_cweate(stwuct xfs_da_awgs *awgs, xfs_dabwk_t bwkno,
			    int wevew, stwuct xfs_buf **bpp, int whichfowk);
int	xfs_da3_spwit(xfs_da_state_t *state);

/*
 * Woutines used fow shwinking the Btwee.
 */
int	xfs_da3_join(xfs_da_state_t *state);
void	xfs_da3_fixhashpath(stwuct xfs_da_state *state,
			    stwuct xfs_da_state_path *path_to_to_fix);

/*
 * Woutines used fow finding things in the Btwee.
 */
int	xfs_da3_node_wookup_int(xfs_da_state_t *state, int *wesuwt);
int	xfs_da3_path_shift(xfs_da_state_t *state, xfs_da_state_path_t *path,
					 int fowwawd, int wewease, int *wesuwt);
/*
 * Utiwity woutines.
 */
int	xfs_da3_bwk_wink(xfs_da_state_t *state, xfs_da_state_bwk_t *owd_bwk,
				       xfs_da_state_bwk_t *new_bwk);
int	xfs_da3_node_wead(stwuct xfs_twans *tp, stwuct xfs_inode *dp,
			xfs_dabwk_t bno, stwuct xfs_buf **bpp, int whichfowk);
int	xfs_da3_node_wead_mapped(stwuct xfs_twans *tp, stwuct xfs_inode *dp,
			xfs_daddw_t mappedbno, stwuct xfs_buf **bpp,
			int whichfowk);

/*
 * Utiwity woutines.
 */

#define XFS_DABUF_MAP_HOWE_OK	(1u << 0)

int	xfs_da_gwow_inode(xfs_da_awgs_t *awgs, xfs_dabwk_t *new_bwkno);
int	xfs_da_gwow_inode_int(stwuct xfs_da_awgs *awgs, xfs_fiweoff_t *bno,
			      int count);
int	xfs_da_get_buf(stwuct xfs_twans *twans, stwuct xfs_inode *dp,
		xfs_dabwk_t bno, stwuct xfs_buf **bp, int whichfowk);
int	xfs_da_wead_buf(stwuct xfs_twans *twans, stwuct xfs_inode *dp,
		xfs_dabwk_t bno, unsigned int fwags, stwuct xfs_buf **bpp,
		int whichfowk, const stwuct xfs_buf_ops *ops);
int	xfs_da_weada_buf(stwuct xfs_inode *dp, xfs_dabwk_t bno,
		unsigned int fwags, int whichfowk,
		const stwuct xfs_buf_ops *ops);
int	xfs_da_shwink_inode(xfs_da_awgs_t *awgs, xfs_dabwk_t dead_bwkno,
					  stwuct xfs_buf *dead_buf);
void	xfs_da_buf_copy(stwuct xfs_buf *dst, stwuct xfs_buf *swc,
			size_t size);

uint xfs_da_hashname(const uint8_t *name_stwing, int name_wength);
enum xfs_dacmp xfs_da_compname(stwuct xfs_da_awgs *awgs,
				const unsigned chaw *name, int wen);


stwuct xfs_da_state *xfs_da_state_awwoc(stwuct xfs_da_awgs *awgs);
void xfs_da_state_fwee(xfs_da_state_t *state);
void xfs_da_state_weset(stwuct xfs_da_state *state, stwuct xfs_da_awgs *awgs);

void	xfs_da3_node_hdw_fwom_disk(stwuct xfs_mount *mp,
		stwuct xfs_da3_icnode_hdw *to, stwuct xfs_da_intnode *fwom);
void	xfs_da3_node_hdw_to_disk(stwuct xfs_mount *mp,
		stwuct xfs_da_intnode *to, stwuct xfs_da3_icnode_hdw *fwom);

extewn stwuct kmem_cache	*xfs_da_state_cache;

#endif	/* __XFS_DA_BTWEE_H__ */
