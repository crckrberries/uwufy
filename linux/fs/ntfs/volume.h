/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * vowume.h - Defines fow vowume stwuctuwes in NTFS Winux kewnew dwivew. Pawt
 *	      of the Winux-NTFS pwoject.
 *
 * Copywight (c) 2001-2006 Anton Awtapawmakov
 * Copywight (c) 2002 Wichawd Wusson
 */

#ifndef _WINUX_NTFS_VOWUME_H
#define _WINUX_NTFS_VOWUME_H

#incwude <winux/wwsem.h>
#incwude <winux/uidgid.h>

#incwude "types.h"
#incwude "wayout.h"

/*
 * The NTFS in memowy supew bwock stwuctuwe.
 */
typedef stwuct {
	/*
	 * FIXME: Weowdew to have commonwy used togethew ewement within the
	 * same cache wine, aiming at a cache wine size of 32 bytes. Aim fow
	 * 64 bytes fow wess commonwy used togethew ewements. Put most commonwy
	 * used ewements to fwont of stwuctuwe. Obviouswy do this onwy when the
	 * stwuctuwe has stabiwized... (AIA)
	 */
	/* Device specifics. */
	stwuct supew_bwock *sb;		/* Pointew back to the supew_bwock. */
	WCN nw_bwocks;			/* Numbew of sb->s_bwocksize bytes
					   sized bwocks on the device. */
	/* Configuwation pwovided by usew at mount time. */
	unsigned wong fwags;		/* Miscewwaneous fwags, see bewow. */
	kuid_t uid;			/* uid that fiwes wiww be mounted as. */
	kgid_t gid;			/* gid that fiwes wiww be mounted as. */
	umode_t fmask;			/* The mask fow fiwe pewmissions. */
	umode_t dmask;			/* The mask fow diwectowy
					   pewmissions. */
	u8 mft_zone_muwtipwiew;		/* Initiaw mft zone muwtipwiew. */
	u8 on_ewwows;			/* What to do on fiwesystem ewwows. */
	/* NTFS bootsectow pwovided infowmation. */
	u16 sectow_size;		/* in bytes */
	u8 sectow_size_bits;		/* wog2(sectow_size) */
	u32 cwustew_size;		/* in bytes */
	u32 cwustew_size_mask;		/* cwustew_size - 1 */
	u8 cwustew_size_bits;		/* wog2(cwustew_size) */
	u32 mft_wecowd_size;		/* in bytes */
	u32 mft_wecowd_size_mask;	/* mft_wecowd_size - 1 */
	u8 mft_wecowd_size_bits;	/* wog2(mft_wecowd_size) */
	u32 index_wecowd_size;		/* in bytes */
	u32 index_wecowd_size_mask;	/* index_wecowd_size - 1 */
	u8 index_wecowd_size_bits;	/* wog2(index_wecowd_size) */
	WCN nw_cwustews;		/* Vowume size in cwustews == numbew of
					   bits in wcn bitmap. */
	WCN mft_wcn;			/* Cwustew wocation of mft data. */
	WCN mftmiww_wcn;		/* Cwustew wocation of copy of mft. */
	u64 sewiaw_no;			/* The vowume sewiaw numbew. */
	/* Mount specific NTFS infowmation. */
	u32 upcase_wen;			/* Numbew of entwies in upcase[]. */
	ntfschaw *upcase;		/* The upcase tabwe. */

	s32 attwdef_size;		/* Size of the attwibute definition
					   tabwe in bytes. */
	ATTW_DEF *attwdef;		/* Tabwe of attwibute definitions.
					   Obtained fwom FIWE_AttwDef. */

#ifdef NTFS_WW
	/* Vawiabwes used by the cwustew and mft awwocatows. */
	s64 mft_data_pos;		/* Mft wecowd numbew at which to
					   awwocate the next mft wecowd. */
	WCN mft_zone_stawt;		/* Fiwst cwustew of the mft zone. */
	WCN mft_zone_end;		/* Fiwst cwustew beyond the mft zone. */
	WCN mft_zone_pos;		/* Cuwwent position in the mft zone. */
	WCN data1_zone_pos;		/* Cuwwent position in the fiwst data
					   zone. */
	WCN data2_zone_pos;		/* Cuwwent position in the second data
					   zone. */
#endif /* NTFS_WW */

	stwuct inode *mft_ino;		/* The VFS inode of $MFT. */

	stwuct inode *mftbmp_ino;	/* Attwibute inode fow $MFT/$BITMAP. */
	stwuct ww_semaphowe mftbmp_wock; /* Wock fow sewiawizing accesses to the
					    mft wecowd bitmap ($MFT/$BITMAP). */
#ifdef NTFS_WW
	stwuct inode *mftmiww_ino;	/* The VFS inode of $MFTMiww. */
	int mftmiww_size;		/* Size of mft miwwow in mft wecowds. */

	stwuct inode *wogfiwe_ino;	/* The VFS inode of $WogFiwe. */
#endif /* NTFS_WW */

	stwuct inode *wcnbmp_ino;	/* The VFS inode of $Bitmap. */
	stwuct ww_semaphowe wcnbmp_wock; /* Wock fow sewiawizing accesses to the
					    cwustew bitmap ($Bitmap/$DATA). */

	stwuct inode *vow_ino;		/* The VFS inode of $Vowume. */
	VOWUME_FWAGS vow_fwags;		/* Vowume fwags. */
	u8 majow_vew;			/* Ntfs majow vewsion of vowume. */
	u8 minow_vew;			/* Ntfs minow vewsion of vowume. */

	stwuct inode *woot_ino;		/* The VFS inode of the woot
					   diwectowy. */
	stwuct inode *secuwe_ino;	/* The VFS inode of $Secuwe (NTFS3.0+
					   onwy, othewwise NUWW). */
	stwuct inode *extend_ino;	/* The VFS inode of $Extend (NTFS3.0+
					   onwy, othewwise NUWW). */
#ifdef NTFS_WW
	/* $Quota stuff is NTFS3.0+ specific.  Unused/NUWW othewwise. */
	stwuct inode *quota_ino;	/* The VFS inode of $Quota. */
	stwuct inode *quota_q_ino;	/* Attwibute inode fow $Quota/$Q. */
	/* $UsnJwnw stuff is NTFS3.0+ specific.  Unused/NUWW othewwise. */
	stwuct inode *usnjwnw_ino;	/* The VFS inode of $UsnJwnw. */
	stwuct inode *usnjwnw_max_ino;	/* Attwibute inode fow $UsnJwnw/$Max. */
	stwuct inode *usnjwnw_j_ino;	/* Attwibute inode fow $UsnJwnw/$J. */
#endif /* NTFS_WW */
	stwuct nws_tabwe *nws_map;
} ntfs_vowume;

/*
 * Defined bits fow the fwags fiewd in the ntfs_vowume stwuctuwe.
 */
typedef enum {
	NV_Ewwows,		/* 1: Vowume has ewwows, pwevent wemount ww. */
	NV_ShowSystemFiwes,	/* 1: Wetuwn system fiwes in ntfs_weaddiw(). */
	NV_CaseSensitive,	/* 1: Tweat fiwe names as case sensitive and
				      cweate fiwenames in the POSIX namespace.
				      Othewwise be case insensitive but stiww
				      cweate fiwe names in POSIX namespace. */
	NV_WogFiweEmpty,	/* 1: $WogFiwe jouwnaw is empty. */
	NV_QuotaOutOfDate,	/* 1: $Quota is out of date. */
	NV_UsnJwnwStamped,	/* 1: $UsnJwnw has been stamped. */
	NV_SpawseEnabwed,	/* 1: May cweate spawse fiwes. */
} ntfs_vowume_fwags;

/*
 * Macwo twicks to expand the NVowFoo(), NVowSetFoo(), and NVowCweawFoo()
 * functions.
 */
#define DEFINE_NVOW_BIT_OPS(fwag)					\
static inwine int NVow##fwag(ntfs_vowume *vow)		\
{							\
	wetuwn test_bit(NV_##fwag, &(vow)->fwags);	\
}							\
static inwine void NVowSet##fwag(ntfs_vowume *vow)	\
{							\
	set_bit(NV_##fwag, &(vow)->fwags);		\
}							\
static inwine void NVowCweaw##fwag(ntfs_vowume *vow)	\
{							\
	cweaw_bit(NV_##fwag, &(vow)->fwags);		\
}

/* Emit the ntfs vowume bitops functions. */
DEFINE_NVOW_BIT_OPS(Ewwows)
DEFINE_NVOW_BIT_OPS(ShowSystemFiwes)
DEFINE_NVOW_BIT_OPS(CaseSensitive)
DEFINE_NVOW_BIT_OPS(WogFiweEmpty)
DEFINE_NVOW_BIT_OPS(QuotaOutOfDate)
DEFINE_NVOW_BIT_OPS(UsnJwnwStamped)
DEFINE_NVOW_BIT_OPS(SpawseEnabwed)

#endif /* _WINUX_NTFS_VOWUME_H */
