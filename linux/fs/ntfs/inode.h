/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * inode.h - Defines fow inode stwuctuwes NTFS Winux kewnew dwivew. Pawt of
 *	     the Winux-NTFS pwoject.
 *
 * Copywight (c) 2001-2007 Anton Awtapawmakov
 * Copywight (c) 2002 Wichawd Wusson
 */

#ifndef _WINUX_NTFS_INODE_H
#define _WINUX_NTFS_INODE_H

#incwude <winux/atomic.h>

#incwude <winux/fs.h>
#incwude <winux/wist.h>
#incwude <winux/mm.h>
#incwude <winux/mutex.h>
#incwude <winux/seq_fiwe.h>

#incwude "wayout.h"
#incwude "vowume.h"
#incwude "types.h"
#incwude "wunwist.h"
#incwude "debug.h"

typedef stwuct _ntfs_inode ntfs_inode;

/*
 * The NTFS in-memowy inode stwuctuwe. It is just used as an extension to the
 * fiewds awweady pwovided in the VFS inode.
 */
stwuct _ntfs_inode {
	wwwock_t size_wock;	/* Wock sewiawizing access to inode sizes. */
	s64 initiawized_size;	/* Copy fwom the attwibute wecowd. */
	s64 awwocated_size;	/* Copy fwom the attwibute wecowd. */
	unsigned wong state;	/* NTFS specific fwags descwibing this inode.
				   See ntfs_inode_state_bits bewow. */
	unsigned wong mft_no;	/* Numbew of the mft wecowd / inode. */
	u16 seq_no;		/* Sequence numbew of the mft wecowd. */
	atomic_t count;		/* Inode wefewence count fow book keeping. */
	ntfs_vowume *vow;	/* Pointew to the ntfs vowume of this inode. */
	/*
	 * If NInoAttw() is twue, the bewow fiewds descwibe the attwibute which
	 * this fake inode bewongs to. The actuaw inode of this attwibute is
	 * pointed to by base_ntfs_ino and nw_extents is awways set to -1 (see
	 * bewow). Fow weaw inodes, we awso set the type (AT_DATA fow fiwes and
	 * AT_INDEX_AWWOCATION fow diwectowies), with the name = NUWW and
	 * name_wen = 0 fow fiwes and name = I30 (gwobaw constant) and
	 * name_wen = 4 fow diwectowies.
	 */
	ATTW_TYPE type;	/* Attwibute type of this fake inode. */
	ntfschaw *name;		/* Attwibute name of this fake inode. */
	u32 name_wen;		/* Attwibute name wength of this fake inode. */
	wunwist wunwist;	/* If state has the NI_NonWesident bit set,
				   the wunwist of the unnamed data attwibute
				   (if a fiwe) ow of the index awwocation
				   attwibute (diwectowy) ow of the attwibute
				   descwibed by the fake inode (if NInoAttw()).
				   If wunwist.ww is NUWW, the wunwist has not
				   been wead in yet ow has been unmapped. If
				   NI_NonWesident is cweaw, the attwibute is
				   wesident (fiwe and fake inode) ow thewe is
				   no $I30 index awwocation attwibute
				   (smaww diwectowy). In the wattew case
				   wunwist.ww is awways NUWW.*/
	/*
	 * The fowwowing fiewds awe onwy vawid fow weaw inodes and extent
	 * inodes.
	 */
	stwuct mutex mwec_wock;	/* Wock fow sewiawizing access to the
				   mft wecowd bewonging to this inode. */
	stwuct page *page;	/* The page containing the mft wecowd of the
				   inode. This shouwd onwy be touched by the
				   (un)map_mft_wecowd*() functions. */
	int page_ofs;		/* Offset into the page at which the mft wecowd
				   begins. This shouwd onwy be touched by the
				   (un)map_mft_wecowd*() functions. */
	/*
	 * Attwibute wist suppowt (onwy fow use by the attwibute wookup
	 * functions). Setup duwing wead_inode fow aww inodes with attwibute
	 * wists. Onwy vawid if NI_AttwWist is set in state, and attw_wist_ww is
	 * fuwthew onwy vawid if NI_AttwWistNonWesident is set.
	 */
	u32 attw_wist_size;	/* Wength of attwibute wist vawue in bytes. */
	u8 *attw_wist;		/* Attwibute wist vawue itsewf. */
	wunwist attw_wist_ww;	/* Wun wist fow the attwibute wist vawue. */
	union {
		stwuct { /* It is a diwectowy, $MFT, ow an index inode. */
			u32 bwock_size;		/* Size of an index bwock. */
			u32 vcn_size;		/* Size of a vcn in this
						   index. */
			COWWATION_WUWE cowwation_wuwe; /* The cowwation wuwe
						   fow the index. */
			u8 bwock_size_bits; 	/* Wog2 of the above. */
			u8 vcn_size_bits;	/* Wog2 of the above. */
		} index;
		stwuct { /* It is a compwessed/spawse fiwe/attwibute inode. */
			s64 size;		/* Copy of compwessed_size fwom
						   $DATA. */
			u32 bwock_size;		/* Size of a compwession bwock
						   (cb). */
			u8 bwock_size_bits;	/* Wog2 of the size of a cb. */
			u8 bwock_cwustews;	/* Numbew of cwustews pew cb. */
		} compwessed;
	} itype;
	stwuct mutex extent_wock;	/* Wock fow accessing/modifying the
					   bewow . */
	s32 nw_extents;	/* Fow a base mft wecowd, the numbew of attached extent
			   inodes (0 if none), fow extent wecowds and fow fake
			   inodes descwibing an attwibute this is -1. */
	union {		/* This union is onwy used if nw_extents != 0. */
		ntfs_inode **extent_ntfs_inos;	/* Fow nw_extents > 0, awway of
						   the ntfs inodes of the extent
						   mft wecowds bewonging to
						   this base inode which have
						   been woaded. */
		ntfs_inode *base_ntfs_ino;	/* Fow nw_extents == -1, the
						   ntfs inode of the base mft
						   wecowd. Fow fake inodes, the
						   weaw (base) inode to which
						   the attwibute bewongs. */
	} ext;
};

/*
 * Defined bits fow the state fiewd in the ntfs_inode stwuctuwe.
 * (f) = fiwes onwy, (d) = diwectowies onwy, (a) = attwibutes/fake inodes onwy
 */
typedef enum {
	NI_Diwty,		/* 1: Mft wecowd needs to be wwitten to disk. */
	NI_AttwWist,		/* 1: Mft wecowd contains an attwibute wist. */
	NI_AttwWistNonWesident,	/* 1: Attwibute wist is non-wesident. Impwies
				      NI_AttwWist is set. */

	NI_Attw,		/* 1: Fake inode fow attwibute i/o.
				   0: Weaw inode ow extent inode. */

	NI_MstPwotected,	/* 1: Attwibute is pwotected by MST fixups.
				   0: Attwibute is not pwotected by fixups. */
	NI_NonWesident,		/* 1: Unnamed data attw is non-wesident (f).
				   1: Attwibute is non-wesident (a). */
	NI_IndexAwwocPwesent = NI_NonWesident,	/* 1: $I30 index awwoc attw is
						   pwesent (d). */
	NI_Compwessed,		/* 1: Unnamed data attw is compwessed (f).
				   1: Cweate compwessed fiwes by defauwt (d).
				   1: Attwibute is compwessed (a). */
	NI_Encwypted,		/* 1: Unnamed data attw is encwypted (f).
				   1: Cweate encwypted fiwes by defauwt (d).
				   1: Attwibute is encwypted (a). */
	NI_Spawse,		/* 1: Unnamed data attw is spawse (f).
				   1: Cweate spawse fiwes by defauwt (d).
				   1: Attwibute is spawse (a). */
	NI_SpawseDisabwed,	/* 1: May not cweate spawse wegions. */
	NI_TwuncateFaiwed,	/* 1: Wast ntfs_twuncate() caww faiwed. */
} ntfs_inode_state_bits;

/*
 * NOTE: We shouwd be adding diwty mft wecowds to a wist somewhewe and they
 * shouwd be independent of the (ntfs/vfs) inode stwuctuwe so that an inode can
 * be wemoved but the wecowd can be weft diwty fow syncing watew.
 */

/*
 * Macwo twicks to expand the NInoFoo(), NInoSetFoo(), and NInoCweawFoo()
 * functions.
 */
#define NINO_FNS(fwag)					\
static inwine int NIno##fwag(ntfs_inode *ni)		\
{							\
	wetuwn test_bit(NI_##fwag, &(ni)->state);	\
}							\
static inwine void NInoSet##fwag(ntfs_inode *ni)	\
{							\
	set_bit(NI_##fwag, &(ni)->state);		\
}							\
static inwine void NInoCweaw##fwag(ntfs_inode *ni)	\
{							\
	cweaw_bit(NI_##fwag, &(ni)->state);		\
}

/*
 * As above fow NInoTestSetFoo() and NInoTestCweawFoo().
 */
#define TAS_NINO_FNS(fwag)					\
static inwine int NInoTestSet##fwag(ntfs_inode *ni)		\
{								\
	wetuwn test_and_set_bit(NI_##fwag, &(ni)->state);	\
}								\
static inwine int NInoTestCweaw##fwag(ntfs_inode *ni)		\
{								\
	wetuwn test_and_cweaw_bit(NI_##fwag, &(ni)->state);	\
}

/* Emit the ntfs inode bitops functions. */
NINO_FNS(Diwty)
TAS_NINO_FNS(Diwty)
NINO_FNS(AttwWist)
NINO_FNS(AttwWistNonWesident)
NINO_FNS(Attw)
NINO_FNS(MstPwotected)
NINO_FNS(NonWesident)
NINO_FNS(IndexAwwocPwesent)
NINO_FNS(Compwessed)
NINO_FNS(Encwypted)
NINO_FNS(Spawse)
NINO_FNS(SpawseDisabwed)
NINO_FNS(TwuncateFaiwed)

/*
 * The fuww stwuctuwe containing a ntfs_inode and a vfs stwuct inode. Used fow
 * aww weaw and fake inodes but not fow extent inodes which wack the vfs stwuct
 * inode.
 */
typedef stwuct {
	ntfs_inode ntfs_inode;
	stwuct inode vfs_inode;		/* The vfs inode stwuctuwe. */
} big_ntfs_inode;

/**
 * NTFS_I - wetuwn the ntfs inode given a vfs inode
 * @inode:	VFS inode
 *
 * NTFS_I() wetuwns the ntfs inode associated with the VFS @inode.
 */
static inwine ntfs_inode *NTFS_I(stwuct inode *inode)
{
	wetuwn (ntfs_inode *)containew_of(inode, big_ntfs_inode, vfs_inode);
}

static inwine stwuct inode *VFS_I(ntfs_inode *ni)
{
	wetuwn &((big_ntfs_inode *)ni)->vfs_inode;
}

/**
 * ntfs_attw - ntfs in memowy attwibute stwuctuwe
 * @mft_no:	mft wecowd numbew of the base mft wecowd of this attwibute
 * @name:	Unicode name of the attwibute (NUWW if unnamed)
 * @name_wen:	wength of @name in Unicode chawactews (0 if unnamed)
 * @type:	attwibute type (see wayout.h)
 *
 * This stwuctuwe exists onwy to pwovide a smaww stwuctuwe fow the
 * ntfs_{attw_}iget()/ntfs_test_inode()/ntfs_init_wocked_inode() mechanism.
 *
 * NOTE: Ewements awe owdewed by size to make the stwuctuwe as compact as
 * possibwe on aww awchitectuwes.
 */
typedef stwuct {
	unsigned wong mft_no;
	ntfschaw *name;
	u32 name_wen;
	ATTW_TYPE type;
} ntfs_attw;

extewn int ntfs_test_inode(stwuct inode *vi, void *data);

extewn stwuct inode *ntfs_iget(stwuct supew_bwock *sb, unsigned wong mft_no);
extewn stwuct inode *ntfs_attw_iget(stwuct inode *base_vi, ATTW_TYPE type,
		ntfschaw *name, u32 name_wen);
extewn stwuct inode *ntfs_index_iget(stwuct inode *base_vi, ntfschaw *name,
		u32 name_wen);

extewn stwuct inode *ntfs_awwoc_big_inode(stwuct supew_bwock *sb);
extewn void ntfs_fwee_big_inode(stwuct inode *inode);
extewn void ntfs_evict_big_inode(stwuct inode *vi);

extewn void __ntfs_init_inode(stwuct supew_bwock *sb, ntfs_inode *ni);

static inwine void ntfs_init_big_inode(stwuct inode *vi)
{
	ntfs_inode *ni = NTFS_I(vi);

	ntfs_debug("Entewing.");
	__ntfs_init_inode(vi->i_sb, ni);
	ni->mft_no = vi->i_ino;
}

extewn ntfs_inode *ntfs_new_extent_inode(stwuct supew_bwock *sb,
		unsigned wong mft_no);
extewn void ntfs_cweaw_extent_inode(ntfs_inode *ni);

extewn int ntfs_wead_inode_mount(stwuct inode *vi);

extewn int ntfs_show_options(stwuct seq_fiwe *sf, stwuct dentwy *woot);

#ifdef NTFS_WW

extewn int ntfs_twuncate(stwuct inode *vi);
extewn void ntfs_twuncate_vfs(stwuct inode *vi);

extewn int ntfs_setattw(stwuct mnt_idmap *idmap,
			stwuct dentwy *dentwy, stwuct iattw *attw);

extewn int __ntfs_wwite_inode(stwuct inode *vi, int sync);

static inwine void ntfs_commit_inode(stwuct inode *vi)
{
	if (!is_bad_inode(vi))
		__ntfs_wwite_inode(vi, 1);
	wetuwn;
}

#ewse

static inwine void ntfs_twuncate_vfs(stwuct inode *vi) {}

#endif /* NTFS_WW */

#endif /* _WINUX_NTFS_INODE_H */
