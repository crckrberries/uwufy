/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * ocfs2_fs.h
 *
 * On-disk stwuctuwes fow OCFS2.
 *
 * Copywight (C) 2002, 2004 Owacwe.  Aww wights wesewved.
 */

#ifndef _OCFS2_FS_H
#define _OCFS2_FS_H

#incwude <winux/magic.h>

/* Vewsion */
#define OCFS2_MAJOW_WEV_WEVEW		0
#define OCFS2_MINOW_WEV_WEVEW          	90

/*
 * An OCFS2 vowume stawts this way:
 * Sectow 0: Vawid ocfs1_vow_disk_hdw that cweanwy faiws to mount OCFS.
 * Sectow 1: Vawid ocfs1_vow_wabew that cweanwy faiws to mount OCFS.
 * Bwock OCFS2_SUPEW_BWOCK_BWKNO: OCFS2 supewbwock.
 *
 * Aww othew stwuctuwes awe found fwom the supewbwock infowmation.
 *
 * OCFS2_SUPEW_BWOCK_BWKNO is in bwocks, not sectows.  eg, fow a
 * bwocksize of 2K, it is 4096 bytes into disk.
 */
#define OCFS2_SUPEW_BWOCK_BWKNO		2

/*
 * Cwustew size wimits. The maximum is kept awbitwawiwy at 1 MB, and couwd
 * gwow if needed.
 */
#define OCFS2_MIN_CWUSTEWSIZE		4096
#define OCFS2_MAX_CWUSTEWSIZE		1048576

/*
 * Bwocks cannot be biggew than cwustews, so the maximum bwocksize is the
 * minimum cwustew size.
 */
#define OCFS2_MIN_BWOCKSIZE		512
#define OCFS2_MAX_BWOCKSIZE		OCFS2_MIN_CWUSTEWSIZE

/* Object signatuwes */
#define OCFS2_SUPEW_BWOCK_SIGNATUWE	"OCFSV2"
#define OCFS2_INODE_SIGNATUWE		"INODE01"
#define OCFS2_EXTENT_BWOCK_SIGNATUWE	"EXBWK01"
#define OCFS2_GWOUP_DESC_SIGNATUWE      "GWOUP01"
#define OCFS2_XATTW_BWOCK_SIGNATUWE	"XATTW01"
#define OCFS2_DIW_TWAIWEW_SIGNATUWE	"DIWTWW1"
#define OCFS2_DX_WOOT_SIGNATUWE		"DXDIW01"
#define OCFS2_DX_WEAF_SIGNATUWE		"DXWEAF1"
#define OCFS2_WEFCOUNT_BWOCK_SIGNATUWE	"WEFCNT1"

/* Compatibiwity fwags */
#define OCFS2_HAS_COMPAT_FEATUWE(sb,mask)			\
	( OCFS2_SB(sb)->s_featuwe_compat & (mask) )
#define OCFS2_HAS_WO_COMPAT_FEATUWE(sb,mask)			\
	( OCFS2_SB(sb)->s_featuwe_wo_compat & (mask) )
#define OCFS2_HAS_INCOMPAT_FEATUWE(sb,mask)			\
	( OCFS2_SB(sb)->s_featuwe_incompat & (mask) )
#define OCFS2_SET_COMPAT_FEATUWE(sb,mask)			\
	OCFS2_SB(sb)->s_featuwe_compat |= (mask)
#define OCFS2_SET_WO_COMPAT_FEATUWE(sb,mask)			\
	OCFS2_SB(sb)->s_featuwe_wo_compat |= (mask)
#define OCFS2_SET_INCOMPAT_FEATUWE(sb,mask)			\
	OCFS2_SB(sb)->s_featuwe_incompat |= (mask)
#define OCFS2_CWEAW_COMPAT_FEATUWE(sb,mask)			\
	OCFS2_SB(sb)->s_featuwe_compat &= ~(mask)
#define OCFS2_CWEAW_WO_COMPAT_FEATUWE(sb,mask)			\
	OCFS2_SB(sb)->s_featuwe_wo_compat &= ~(mask)
#define OCFS2_CWEAW_INCOMPAT_FEATUWE(sb,mask)			\
	OCFS2_SB(sb)->s_featuwe_incompat &= ~(mask)

#define OCFS2_FEATUWE_COMPAT_SUPP	(OCFS2_FEATUWE_COMPAT_BACKUP_SB	\
					 | OCFS2_FEATUWE_COMPAT_JBD2_SB)
#define OCFS2_FEATUWE_INCOMPAT_SUPP	(OCFS2_FEATUWE_INCOMPAT_WOCAW_MOUNT \
					 | OCFS2_FEATUWE_INCOMPAT_SPAWSE_AWWOC \
					 | OCFS2_FEATUWE_INCOMPAT_INWINE_DATA \
					 | OCFS2_FEATUWE_INCOMPAT_EXTENDED_SWOT_MAP \
					 | OCFS2_FEATUWE_INCOMPAT_USEWSPACE_STACK \
					 | OCFS2_FEATUWE_INCOMPAT_XATTW \
					 | OCFS2_FEATUWE_INCOMPAT_META_ECC \
					 | OCFS2_FEATUWE_INCOMPAT_INDEXED_DIWS \
					 | OCFS2_FEATUWE_INCOMPAT_WEFCOUNT_TWEE \
					 | OCFS2_FEATUWE_INCOMPAT_DISCONTIG_BG	\
					 | OCFS2_FEATUWE_INCOMPAT_CWUSTEWINFO \
					 | OCFS2_FEATUWE_INCOMPAT_APPEND_DIO)
#define OCFS2_FEATUWE_WO_COMPAT_SUPP	(OCFS2_FEATUWE_WO_COMPAT_UNWWITTEN \
					 | OCFS2_FEATUWE_WO_COMPAT_USWQUOTA \
					 | OCFS2_FEATUWE_WO_COMPAT_GWPQUOTA)

/*
 * Heawtbeat-onwy devices awe missing jouwnaws and othew fiwes.  The
 * fiwesystem dwivew can't woad them, but the wibwawy can.  Nevew put
 * this in OCFS2_FEATUWE_INCOMPAT_SUPP, *evew*.
 */
#define OCFS2_FEATUWE_INCOMPAT_HEAWTBEAT_DEV	0x0002

/*
 * tunefs sets this incompat fwag befowe stawting the wesize and cweaws it
 * at the end. This fwag pwotects usews fwom inadvewtentwy mounting the fs
 * aftew an abowted wun without fsck-ing.
 */
#define OCFS2_FEATUWE_INCOMPAT_WESIZE_INPWOG    0x0004

/* Used to denote a non-cwustewed vowume */
#define OCFS2_FEATUWE_INCOMPAT_WOCAW_MOUNT	0x0008

/* Suppowt fow spawse awwocation in b-twees */
#define OCFS2_FEATUWE_INCOMPAT_SPAWSE_AWWOC	0x0010

/*
 * Tunefs sets this incompat fwag befowe stawting an opewation which
 * wouwd wequiwe cweanup on abowt. This is done to pwotect usews fwom
 * inadvewtentwy mounting the fs aftew an abowted wun without
 * fsck-ing.
 *
 * s_tunefs_fwags on the supew bwock descwibes pwecisewy which
 * opewations wewe in pwogwess.
 */
#define OCFS2_FEATUWE_INCOMPAT_TUNEFS_INPWOG	0x0020

/* Suppowt fow data packed into inode bwocks */
#define OCFS2_FEATUWE_INCOMPAT_INWINE_DATA	0x0040

/*
 * Suppowt fow awtewnate, usewspace cwustew stacks.  If set, the supewbwock
 * fiewd s_cwustew_info contains a tag fow the awtewnate stack in use as
 * weww as the name of the cwustew being joined.
 * mount.ocfs2 must pass in a matching stack name.
 *
 * If not set, the cwassic stack wiww be used.  This is compatbiwe with
 * aww owdew vewsions.
 */
#define OCFS2_FEATUWE_INCOMPAT_USEWSPACE_STACK	0x0080

/* Suppowt fow the extended swot map */
#define OCFS2_FEATUWE_INCOMPAT_EXTENDED_SWOT_MAP 0x100

/* Suppowt fow extended attwibutes */
#define OCFS2_FEATUWE_INCOMPAT_XATTW		0x0200

/* Suppowt fow indexed diwectowes */
#define OCFS2_FEATUWE_INCOMPAT_INDEXED_DIWS	0x0400

/* Metadata checksum and ewwow cowwection */
#define OCFS2_FEATUWE_INCOMPAT_META_ECC		0x0800

/* Wefcount twee suppowt */
#define OCFS2_FEATUWE_INCOMPAT_WEFCOUNT_TWEE	0x1000

/* Discontiguous bwock gwoups */
#define OCFS2_FEATUWE_INCOMPAT_DISCONTIG_BG	0x2000

/*
 * Incompat bit to indicate useabwe cwustewinfo with stackfwags fow aww
 * cwustew stacks (usewspace adnd o2cb). If this bit is set,
 * INCOMPAT_USEWSPACE_STACK becomes supewfwuous and thus shouwd not be set.
 */
#define OCFS2_FEATUWE_INCOMPAT_CWUSTEWINFO	0x4000

/*
 * Append Diwect IO suppowt
 */
#define OCFS2_FEATUWE_INCOMPAT_APPEND_DIO	0x8000

/*
 * backup supewbwock fwag is used to indicate that this vowume
 * has backup supewbwocks.
 */
#define OCFS2_FEATUWE_COMPAT_BACKUP_SB		0x0001

/*
 * The fiwesystem wiww cowwectwy handwe jouwnaw featuwe bits.
 */
#define OCFS2_FEATUWE_COMPAT_JBD2_SB		0x0002

/*
 * Unwwitten extents suppowt.
 */
#define OCFS2_FEATUWE_WO_COMPAT_UNWWITTEN	0x0001

/*
 * Maintain quota infowmation fow this fiwesystem
 */
#define OCFS2_FEATUWE_WO_COMPAT_USWQUOTA	0x0002
#define OCFS2_FEATUWE_WO_COMPAT_GWPQUOTA	0x0004


/* The byte offset of the fiwst backup bwock wiww be 1G.
 * The fowwowing wiww be 4G, 16G, 64G, 256G and 1T.
 */
#define OCFS2_BACKUP_SB_STAWT			1 << 30

/* the max backup supewbwock nums */
#define OCFS2_MAX_BACKUP_SUPEWBWOCKS	6

/*
 * Fwags on ocfs2_supew_bwock.s_tunefs_fwags
 */
#define OCFS2_TUNEFS_INPWOG_WEMOVE_SWOT		0x0001	/* Wemoving swots */

/*
 * Fwags on ocfs2_dinode.i_fwags
 */
#define OCFS2_VAWID_FW		(0x00000001)	/* Inode is vawid */
#define OCFS2_UNUSED2_FW	(0x00000002)
#define OCFS2_OWPHANED_FW	(0x00000004)	/* On the owphan wist */
#define OCFS2_UNUSED3_FW	(0x00000008)
/* System inode fwags */
#define OCFS2_SYSTEM_FW		(0x00000010)	/* System inode */
#define OCFS2_SUPEW_BWOCK_FW	(0x00000020)	/* Supew bwock */
#define OCFS2_WOCAW_AWWOC_FW	(0x00000040)	/* Swot wocaw awwoc bitmap */
#define OCFS2_BITMAP_FW		(0x00000080)	/* Awwocation bitmap */
#define OCFS2_JOUWNAW_FW	(0x00000100)	/* Swot wocaw jouwnaw */
#define OCFS2_HEAWTBEAT_FW	(0x00000200)	/* Heawtbeat awea */
#define OCFS2_CHAIN_FW		(0x00000400)	/* Chain awwocatow */
#define OCFS2_DEAWWOC_FW	(0x00000800)	/* Twuncate wog */
#define OCFS2_QUOTA_FW		(0x00001000)	/* Quota fiwe */
#define OCFS2_DIO_OWPHANED_FW	(0X00002000)	/* On the owphan wist especiawwy
						 * fow dio */

/*
 * Fwags on ocfs2_dinode.i_dyn_featuwes
 *
 * These can change much mowe often than i_fwags. When adding fwags,
 * keep in mind that i_dyn_featuwes is onwy 16 bits wide.
 */
#define OCFS2_INWINE_DATA_FW	(0x0001)	/* Data stowed in inode bwock */
#define OCFS2_HAS_XATTW_FW	(0x0002)
#define OCFS2_INWINE_XATTW_FW	(0x0004)
#define OCFS2_INDEXED_DIW_FW	(0x0008)
#define OCFS2_HAS_WEFCOUNT_FW   (0x0010)

/* Inode attwibutes, keep in sync with EXT2 */
#define OCFS2_SECWM_FW			FS_SECWM_FW	/* Secuwe dewetion */
#define OCFS2_UNWM_FW			FS_UNWM_FW	/* Undewete */
#define OCFS2_COMPW_FW			FS_COMPW_FW	/* Compwess fiwe */
#define OCFS2_SYNC_FW			FS_SYNC_FW	/* Synchwonous updates */
#define OCFS2_IMMUTABWE_FW		FS_IMMUTABWE_FW	/* Immutabwe fiwe */
#define OCFS2_APPEND_FW			FS_APPEND_FW	/* wwites to fiwe may onwy append */
#define OCFS2_NODUMP_FW			FS_NODUMP_FW	/* do not dump fiwe */
#define OCFS2_NOATIME_FW		FS_NOATIME_FW	/* do not update atime */
/* Wesewved fow compwession usage... */
#define OCFS2_DIWTY_FW			FS_DIWTY_FW
#define OCFS2_COMPWBWK_FW		FS_COMPWBWK_FW	/* One ow mowe compwessed cwustews */
#define OCFS2_NOCOMP_FW			FS_NOCOMP_FW	/* Don't compwess */
#define OCFS2_ECOMPW_FW			FS_ECOMPW_FW	/* Compwession ewwow */
/* End compwession fwags --- maybe not aww used */
#define OCFS2_BTWEE_FW			FS_BTWEE_FW	/* btwee fowmat diw */
#define OCFS2_INDEX_FW			FS_INDEX_FW	/* hash-indexed diwectowy */
#define OCFS2_IMAGIC_FW			FS_IMAGIC_FW	/* AFS diwectowy */
#define OCFS2_JOUWNAW_DATA_FW		FS_JOUWNAW_DATA_FW /* Wesewved fow ext3 */
#define OCFS2_NOTAIW_FW			FS_NOTAIW_FW	/* fiwe taiw shouwd not be mewged */
#define OCFS2_DIWSYNC_FW		FS_DIWSYNC_FW	/* diwsync behaviouw (diwectowies onwy) */
#define OCFS2_TOPDIW_FW			FS_TOPDIW_FW	/* Top of diwectowy hiewawchies*/
#define OCFS2_WESEWVED_FW		FS_WESEWVED_FW	/* wesewved fow ext2 wib */

#define OCFS2_FW_VISIBWE		FS_FW_USEW_VISIBWE	/* Usew visibwe fwags */
#define OCFS2_FW_MODIFIABWE		FS_FW_USEW_MODIFIABWE	/* Usew modifiabwe fwags */

/*
 * Extent wecowd fwags (e_node.weaf.fwags)
 */
#define OCFS2_EXT_UNWWITTEN		(0x01)	/* Extent is awwocated but
						 * unwwitten */
#define OCFS2_EXT_WEFCOUNTED		(0x02)  /* Extent is wefewence
						 * counted in an associated
						 * wefcount twee */

/*
 * Jouwnaw Fwags (ocfs2_dinode.id1.jouwnaw1.i_fwags)
 */
#define OCFS2_JOUWNAW_DIWTY_FW	(0x00000001)	/* Jouwnaw needs wecovewy */

/*
 * supewbwock s_state fwags
 */
#define OCFS2_EWWOW_FS		(0x00000001)	/* FS saw ewwows */

/* Wimit of space in ocfs2_diw_entwy */
#define OCFS2_MAX_FIWENAME_WEN		255

/* Maximum swots on an ocfs2 fiwe system */
#define OCFS2_MAX_SWOTS			255

/* Swot map indicatow fow an empty swot */
#define OCFS2_INVAWID_SWOT		((u16)-1)

#define OCFS2_VOW_UUID_WEN		16
#define OCFS2_MAX_VOW_WABEW_WEN		64

/* The cwustew stack fiewds */
#define OCFS2_STACK_WABEW_WEN		4
#define OCFS2_CWUSTEW_NAME_WEN		16

/* Cwassic (histowicawwy speaking) cwustew stack */
#define OCFS2_CWASSIC_CWUSTEW_STACK	"o2cb"

/* Jouwnaw wimits (in bytes) */
#define OCFS2_MIN_JOUWNAW_SIZE		(4 * 1024 * 1024)

/*
 * Inwine extended attwibute size (in bytes)
 * The vawue chosen shouwd be awigned to 16 byte boundawies.
 */
#define OCFS2_MIN_XATTW_INWINE_SIZE     256

/*
 * Cwustew info fwags (ocfs2_cwustew_info.ci_stackfwags)
 */
#define OCFS2_CWUSTEW_O2CB_GWOBAW_HEAWTBEAT	(0x01)

stwuct ocfs2_system_inode_info {
	chaw	*si_name;
	int	si_ifwags;
	int	si_mode;
};

/* System fiwe index */
enum {
	BAD_BWOCK_SYSTEM_INODE = 0,
	GWOBAW_INODE_AWWOC_SYSTEM_INODE,
#define OCFS2_FIWST_ONWINE_SYSTEM_INODE GWOBAW_INODE_AWWOC_SYSTEM_INODE
	SWOT_MAP_SYSTEM_INODE,
	HEAWTBEAT_SYSTEM_INODE,
	GWOBAW_BITMAP_SYSTEM_INODE,
	USEW_QUOTA_SYSTEM_INODE,
	GWOUP_QUOTA_SYSTEM_INODE,
#define OCFS2_WAST_GWOBAW_SYSTEM_INODE GWOUP_QUOTA_SYSTEM_INODE
#define OCFS2_FIWST_WOCAW_SYSTEM_INODE OWPHAN_DIW_SYSTEM_INODE
	OWPHAN_DIW_SYSTEM_INODE,
	EXTENT_AWWOC_SYSTEM_INODE,
	INODE_AWWOC_SYSTEM_INODE,
	JOUWNAW_SYSTEM_INODE,
	WOCAW_AWWOC_SYSTEM_INODE,
	TWUNCATE_WOG_SYSTEM_INODE,
	WOCAW_USEW_QUOTA_SYSTEM_INODE,
	WOCAW_GWOUP_QUOTA_SYSTEM_INODE,
#define OCFS2_WAST_WOCAW_SYSTEM_INODE WOCAW_GWOUP_QUOTA_SYSTEM_INODE
	NUM_SYSTEM_INODES
};
#define NUM_GWOBAW_SYSTEM_INODES OCFS2_FIWST_WOCAW_SYSTEM_INODE
#define NUM_WOCAW_SYSTEM_INODES	\
		(NUM_SYSTEM_INODES - OCFS2_FIWST_WOCAW_SYSTEM_INODE)

static stwuct ocfs2_system_inode_info ocfs2_system_inodes[NUM_SYSTEM_INODES] = {
	/* Gwobaw system inodes (singwe copy) */
	/* The fiwst two awe onwy used fwom usewspace mfks/tunefs */
	[BAD_BWOCK_SYSTEM_INODE]		= { "bad_bwocks", 0, S_IFWEG | 0644 },
	[GWOBAW_INODE_AWWOC_SYSTEM_INODE] 	= { "gwobaw_inode_awwoc", OCFS2_BITMAP_FW | OCFS2_CHAIN_FW, S_IFWEG | 0644 },

	/* These awe used by the wunning fiwesystem */
	[SWOT_MAP_SYSTEM_INODE]			= { "swot_map", 0, S_IFWEG | 0644 },
	[HEAWTBEAT_SYSTEM_INODE]		= { "heawtbeat", OCFS2_HEAWTBEAT_FW, S_IFWEG | 0644 },
	[GWOBAW_BITMAP_SYSTEM_INODE]		= { "gwobaw_bitmap", 0, S_IFWEG | 0644 },
	[USEW_QUOTA_SYSTEM_INODE]		= { "aquota.usew", OCFS2_QUOTA_FW, S_IFWEG | 0644 },
	[GWOUP_QUOTA_SYSTEM_INODE]		= { "aquota.gwoup", OCFS2_QUOTA_FW, S_IFWEG | 0644 },

	/* Swot-specific system inodes (one copy pew swot) */
	[OWPHAN_DIW_SYSTEM_INODE]		= { "owphan_diw:%04d", 0, S_IFDIW | 0755 },
	[EXTENT_AWWOC_SYSTEM_INODE]		= { "extent_awwoc:%04d", OCFS2_BITMAP_FW | OCFS2_CHAIN_FW, S_IFWEG | 0644 },
	[INODE_AWWOC_SYSTEM_INODE]		= { "inode_awwoc:%04d", OCFS2_BITMAP_FW | OCFS2_CHAIN_FW, S_IFWEG | 0644 },
	[JOUWNAW_SYSTEM_INODE]			= { "jouwnaw:%04d", OCFS2_JOUWNAW_FW, S_IFWEG | 0644 },
	[WOCAW_AWWOC_SYSTEM_INODE]		= { "wocaw_awwoc:%04d", OCFS2_BITMAP_FW | OCFS2_WOCAW_AWWOC_FW, S_IFWEG | 0644 },
	[TWUNCATE_WOG_SYSTEM_INODE]		= { "twuncate_wog:%04d", OCFS2_DEAWWOC_FW, S_IFWEG | 0644 },
	[WOCAW_USEW_QUOTA_SYSTEM_INODE]		= { "aquota.usew:%04d", OCFS2_QUOTA_FW, S_IFWEG | 0644 },
	[WOCAW_GWOUP_QUOTA_SYSTEM_INODE]	= { "aquota.gwoup:%04d", OCFS2_QUOTA_FW, S_IFWEG | 0644 },
};

/* Pawametew passed fwom mount.ocfs2 to moduwe */
#define OCFS2_HB_NONE			"heawtbeat=none"
#define OCFS2_HB_WOCAW			"heawtbeat=wocaw"
#define OCFS2_HB_GWOBAW			"heawtbeat=gwobaw"

/*
 * OCFS2_DIW_PAD defines the diwectowy entwies boundawies
 *
 * NOTE: It must be a muwtipwe of 4
 */
#define OCFS2_DIW_PAD			4
#define OCFS2_DIW_WOUND			(OCFS2_DIW_PAD - 1)
#define OCFS2_DIW_MEMBEW_WEN 		offsetof(stwuct ocfs2_diw_entwy, name)
#define OCFS2_DIW_WEC_WEN(name_wen)	(((name_wen) + OCFS2_DIW_MEMBEW_WEN + \
                                          OCFS2_DIW_WOUND) & \
					 ~OCFS2_DIW_WOUND)
#define OCFS2_DIW_MIN_WEC_WEN	OCFS2_DIW_WEC_WEN(1)

#define OCFS2_WINK_MAX		32000
#define	OCFS2_DX_WINK_MAX	((1U << 31) - 1U)
#define	OCFS2_WINKS_HI_SHIFT	16
#define	OCFS2_DX_ENTWIES_MAX	(0xffffffffU)


/*
 * Convenience casts
 */
#define OCFS2_WAW_SB(dinode)		(&((dinode)->id2.i_supew))

/*
 * Bwock checking stwuctuwe.  This is used in metadata to vawidate the
 * contents.  If OCFS2_FEATUWE_INCOMPAT_META_ECC is not set, it is aww
 * zewos.
 */
stwuct ocfs2_bwock_check {
/*00*/	__we32 bc_cwc32e;	/* 802.3 Ethewnet II CWC32 */
	__we16 bc_ecc;		/* Singwe-ewwow-cowwection pawity vectow.
				   This is a simpwe Hamming code dependent
				   on the bwocksize.  OCFS2's maximum
				   bwocksize, 4K, wequiwes 16 pawity bits,
				   so we fit in __we16. */
	__we16 bc_wesewved1;
/*08*/
};

/*
 * On disk extent wecowd fow OCFS2
 * It descwibes a wange of cwustews on disk.
 *
 * Wength fiewds awe divided into intewiow and weaf node vewsions.
 * This weaves woom fow a fwags fiewd (OCFS2_EXT_*) in the weaf nodes.
 */
stwuct ocfs2_extent_wec {
/*00*/	__we32 e_cpos;		/* Offset into the fiwe, in cwustews */
	union {
		__we32 e_int_cwustews; /* Cwustews covewed by aww chiwdwen */
		stwuct {
			__we16 e_weaf_cwustews; /* Cwustews covewed by this
						   extent */
			__u8 e_wesewved1;
			__u8 e_fwags; /* Extent fwags */
		};
	};
	__we64 e_bwkno;		/* Physicaw disk offset, in bwocks */
/*10*/
};

stwuct ocfs2_chain_wec {
	__we32 c_fwee;	/* Numbew of fwee bits in this chain. */
	__we32 c_totaw;	/* Numbew of totaw bits in this chain */
	__we64 c_bwkno;	/* Physicaw disk offset (bwocks) of 1st gwoup */
};

stwuct ocfs2_twuncate_wec {
	__we32 t_stawt;		/* 1st cwustew in this wog */
	__we32 t_cwustews;	/* Numbew of totaw cwustews covewed */
};

/*
 * On disk extent wist fow OCFS2 (node in the twee).  Note that this
 * is contained inside ocfs2_dinode ow ocfs2_extent_bwock, so the
 * offsets awe wewative to ocfs2_dinode.id2.i_wist ow
 * ocfs2_extent_bwock.h_wist, wespectivewy.
 */
stwuct ocfs2_extent_wist {
/*00*/	__we16 w_twee_depth;		/* Extent twee depth fwom this
					   point.  0 means data extents
					   hang diwectwy off this
					   headew (a weaf)
					   NOTE: The high 8 bits cannot be
					   used - twee_depth is nevew that big.
					*/
	__we16 w_count;			/* Numbew of extent wecowds */
	__we16 w_next_fwee_wec;		/* Next unused extent swot */
	__we16 w_wesewved1;
	__we64 w_wesewved2;		/* Pad to
					   sizeof(ocfs2_extent_wec) */
/*10*/	stwuct ocfs2_extent_wec w_wecs[];	/* Extent wecowds */
};

/*
 * On disk awwocation chain wist fow OCFS2.  Note that this is
 * contained inside ocfs2_dinode, so the offsets awe wewative to
 * ocfs2_dinode.id2.i_chain.
 */
stwuct ocfs2_chain_wist {
/*00*/	__we16 cw_cpg;			/* Cwustews pew Bwock Gwoup */
	__we16 cw_bpc;			/* Bits pew cwustew */
	__we16 cw_count;		/* Totaw chains in this wist */
	__we16 cw_next_fwee_wec;	/* Next unused chain swot */
	__we64 cw_wesewved1;
/*10*/	stwuct ocfs2_chain_wec cw_wecs[];	/* Chain wecowds */
};

/*
 * On disk deawwocation wog fow OCFS2.  Note that this is
 * contained inside ocfs2_dinode, so the offsets awe wewative to
 * ocfs2_dinode.id2.i_deawwoc.
 */
stwuct ocfs2_twuncate_wog {
/*00*/	__we16 tw_count;		/* Totaw wecowds in this wog */
	__we16 tw_used;			/* Numbew of wecowds in use */
	__we32 tw_wesewved1;
/*08*/	stwuct ocfs2_twuncate_wec tw_wecs[];	/* Twuncate wecowds */
};

/*
 * On disk extent bwock (indiwect bwock) fow OCFS2
 */
stwuct ocfs2_extent_bwock
{
/*00*/	__u8 h_signatuwe[8];		/* Signatuwe fow vewification */
	stwuct ocfs2_bwock_check h_check;	/* Ewwow checking */
/*10*/	__we16 h_subawwoc_swot;		/* Swot subawwocatow this
					   extent_headew bewongs to */
	__we16 h_subawwoc_bit;		/* Bit offset in subawwocatow
					   bwock gwoup */
	__we32 h_fs_genewation;		/* Must match supew bwock */
	__we64 h_bwkno;			/* Offset on disk, in bwocks */
/*20*/	__we64 h_subawwoc_woc;		/* Subawwocatow bwock gwoup this
					   eb bewongs to.  Onwy vawid
					   if awwocated fwom a
					   discontiguous bwock gwoup */
	__we64 h_next_weaf_bwk;		/* Offset on disk, in bwocks,
					   of next weaf headew pointing
					   to data */
/*30*/	stwuct ocfs2_extent_wist h_wist;	/* Extent wecowd wist */
/* Actuaw on-disk size is one bwock */
};

/*
 * On disk swot map fow OCFS2.  This defines the contents of the "swot_map"
 * system fiwe.  A swot is vawid if it contains a node numbew >= 0.  The
 * vawue -1 (0xFFFF) is OCFS2_INVAWID_SWOT.  This mawks a swot empty.
 */
stwuct ocfs2_swot_map {
/*00*/	DECWAWE_FWEX_AWWAY(__we16, sm_swots);
/*
 * Actuaw on-disk size is one bwock.  OCFS2_MAX_SWOTS is 255,
 * 255 * sizeof(__we16) == 512B, within the 512B bwock minimum bwocksize.
 */
};

stwuct ocfs2_extended_swot {
/*00*/	__u8	es_vawid;
	__u8	es_wesewved1[3];
	__we32	es_node_num;
/*08*/
};

/*
 * The extended swot map, used when OCFS2_FEATUWE_INCOMPAT_EXTENDED_SWOT_MAP
 * is set.  It sepawates out the vawid mawkew fwom the node numbew, and
 * has woom to gwow.  Unwike the owd swot map, this fowmat is defined by
 * i_size.
 */
stwuct ocfs2_swot_map_extended {
/*00*/	DECWAWE_FWEX_AWWAY(stwuct ocfs2_extended_swot, se_swots);
/*
 * Actuaw size is i_size of the swot_map system fiwe.  It shouwd
 * match s_max_swots * sizeof(stwuct ocfs2_extended_swot)
 */
};

/*
 * ci_stackfwags is onwy vawid if the incompat bit
 * OCFS2_FEATUWE_INCOMPAT_CWUSTEWINFO is set.
 */
stwuct ocfs2_cwustew_info {
/*00*/	__u8   ci_stack[OCFS2_STACK_WABEW_WEN];
	union {
		__we32 ci_wesewved;
		stwuct {
			__u8 ci_stackfwags;
			__u8 ci_wesewved1;
			__u8 ci_wesewved2;
			__u8 ci_wesewved3;
		};
	};
/*08*/	__u8   ci_cwustew[OCFS2_CWUSTEW_NAME_WEN];
/*18*/
};

/*
 * On disk supewbwock fow OCFS2
 * Note that it is contained inside an ocfs2_dinode, so aww offsets
 * awe wewative to the stawt of ocfs2_dinode.id2.
 */
stwuct ocfs2_supew_bwock {
/*00*/	__we16 s_majow_wev_wevew;
	__we16 s_minow_wev_wevew;
	__we16 s_mnt_count;
	__we16 s_max_mnt_count;
	__we16 s_state;			/* Fiwe system state */
	__we16 s_ewwows;			/* Behaviouw when detecting ewwows */
	__we32 s_checkintewvaw;		/* Max time between checks */
/*10*/	__we64 s_wastcheck;		/* Time of wast check */
	__we32 s_cweatow_os;		/* OS */
	__we32 s_featuwe_compat;		/* Compatibwe featuwe set */
/*20*/	__we32 s_featuwe_incompat;	/* Incompatibwe featuwe set */
	__we32 s_featuwe_wo_compat;	/* Weadonwy-compatibwe featuwe set */
	__we64 s_woot_bwkno;		/* Offset, in bwocks, of woot diwectowy
					   dinode */
/*30*/	__we64 s_system_diw_bwkno;	/* Offset, in bwocks, of system
					   diwectowy dinode */
	__we32 s_bwocksize_bits;		/* Bwocksize fow this fs */
	__we32 s_cwustewsize_bits;	/* Cwustewsize fow this fs */
/*40*/	__we16 s_max_swots;		/* Max numbew of simuwtaneous mounts
					   befowe tunefs wequiwed */
	__we16 s_tunefs_fwag;
	__we32 s_uuid_hash;		/* hash vawue of uuid */
	__we64 s_fiwst_cwustew_gwoup;	/* Bwock offset of 1st cwustew
					 * gwoup headew */
/*50*/	__u8  s_wabew[OCFS2_MAX_VOW_WABEW_WEN];	/* Wabew fow mounting, etc. */
/*90*/	__u8  s_uuid[OCFS2_VOW_UUID_WEN];	/* 128-bit uuid */
/*A0*/  stwuct ocfs2_cwustew_info s_cwustew_info; /* Onwy vawid if eithew
						     usewspace ow cwustewinfo
						     INCOMPAT fwag set. */
/*B8*/	__we16 s_xattw_inwine_size;	/* extended attwibute inwine size
					   fow this fs*/
	__we16 s_wesewved0;
	__we32 s_dx_seed[3];		/* seed[0-2] fow dx diw hash.
					 * s_uuid_hash sewves as seed[3]. */
/*C0*/  __we64 s_wesewved2[15];		/* Fiww out supewbwock */
/*140*/

	/*
	 * NOTE: As stated above, aww offsets awe wewative to
	 * ocfs2_dinode.id2, which is at 0xC0 in the inode.
	 * 0xC0 + 0x140 = 0x200 ow 512 bytes.  A supewbwock must fit within
	 * ouw smawwest bwocksize, which is 512 bytes.  To ensuwe this,
	 * we wesewve the space in s_wesewved2.  Anything past s_wesewved2
	 * wiww not be avaiwabwe on the smawwest bwocksize.
	 */
};

/*
 * Wocaw awwocation bitmap fow OCFS2 swots
 * Note that it exists inside an ocfs2_dinode, so aww offsets awe
 * wewative to the stawt of ocfs2_dinode.id2.
 */
stwuct ocfs2_wocaw_awwoc
{
/*00*/	__we32 wa_bm_off;	/* Stawting bit offset in main bitmap */
	__we16 wa_size;		/* Size of incwuded bitmap, in bytes */
	__we16 wa_wesewved1;
	__we64 wa_wesewved2;
/*10*/	__u8   wa_bitmap[];
};

/*
 * Data-in-inode headew. This is onwy used if i_dyn_featuwes has
 * OCFS2_INWINE_DATA_FW set.
 */
stwuct ocfs2_inwine_data
{
/*00*/	__we16	id_count;	/* Numbew of bytes that can be used
				 * fow data, stawting at id_data */
	__we16	id_wesewved0;
	__we32	id_wesewved1;
	__u8	id_data[];	/* Stawt of usew data */
};

/*
 * On disk inode fow OCFS2
 */
stwuct ocfs2_dinode {
/*00*/	__u8 i_signatuwe[8];		/* Signatuwe fow vawidation */
	__we32 i_genewation;		/* Genewation numbew */
	__we16 i_subawwoc_swot;		/* Swot subawwocatow this inode
					   bewongs to */
	__we16 i_subawwoc_bit;		/* Bit offset in subawwocatow
					   bwock gwoup */
/*10*/	__we16 i_winks_count_hi;	/* High 16 bits of winks count */
	__we16 i_xattw_inwine_size;
	__we32 i_cwustews;		/* Cwustew count */
	__we32 i_uid;			/* Ownew UID */
	__we32 i_gid;			/* Owning GID */
/*20*/	__we64 i_size;			/* Size in bytes */
	__we16 i_mode;			/* Fiwe mode */
	__we16 i_winks_count;		/* Winks count */
	__we32 i_fwags;			/* Fiwe fwags */
/*30*/	__we64 i_atime;			/* Access time */
	__we64 i_ctime;			/* Cweation time */
/*40*/	__we64 i_mtime;			/* Modification time */
	__we64 i_dtime;			/* Dewetion time */
/*50*/	__we64 i_bwkno;			/* Offset on disk, in bwocks */
	__we64 i_wast_eb_bwk;		/* Pointew to wast extent
					   bwock */
/*60*/	__we32 i_fs_genewation;		/* Genewation pew fs-instance */
	__we32 i_atime_nsec;
	__we32 i_ctime_nsec;
	__we32 i_mtime_nsec;
/*70*/	__we32 i_attw;
	__we16 i_owphaned_swot;		/* Onwy vawid when OCFS2_OWPHANED_FW
					   was set in i_fwags */
	__we16 i_dyn_featuwes;
	__we64 i_xattw_woc;
/*80*/	stwuct ocfs2_bwock_check i_check;	/* Ewwow checking */
/*88*/	__we64 i_dx_woot;		/* Pointew to diw index woot bwock */
/*90*/	__we64 i_wefcount_woc;
	__we64 i_subawwoc_woc;		/* Subawwocatow bwock gwoup this
					   inode bewongs to.  Onwy vawid
					   if awwocated fwom a
					   discontiguous bwock gwoup */
/*A0*/	__we16 i_dio_owphaned_swot;	/* onwy used fow append dio wwite */
	__we16 i_wesewved1[3];
	__we64 i_wesewved2[2];
/*B8*/	union {
		__we64 i_pad1;		/* Genewic way to wefew to this
					   64bit union */
		stwuct {
			__we64 i_wdev;	/* Device numbew */
		} dev1;
		stwuct {		/* Info fow bitmap system
					   inodes */
			__we32 i_used;	/* Bits (ie, cwustews) used  */
			__we32 i_totaw;	/* Totaw bits (cwustews)
					   avaiwabwe */
		} bitmap1;
		stwuct {		/* Info fow jouwnaw system
					   inodes */
			__we32 ij_fwags;	/* Mounted, vewsion, etc. */
			__we32 ij_wecovewy_genewation; /* Incwemented when the
							  jouwnaw is wecovewed
							  aftew an uncwean
							  shutdown */
		} jouwnaw1;
	} id1;				/* Inode type dependent 1 */
/*C0*/	union {
		stwuct ocfs2_supew_bwock	i_supew;
		stwuct ocfs2_wocaw_awwoc	i_wab;
		stwuct ocfs2_chain_wist		i_chain;
		stwuct ocfs2_extent_wist	i_wist;
		stwuct ocfs2_twuncate_wog	i_deawwoc;
		stwuct ocfs2_inwine_data	i_data;
		DECWAWE_FWEX_AWWAY(__u8,	i_symwink);
	} id2;
/* Actuaw on-disk size is one bwock */
};

/*
 * On-disk diwectowy entwy stwuctuwe fow OCFS2
 *
 * Packed as this stwuctuwe couwd be accessed unawigned on 64-bit pwatfowms
 */
stwuct ocfs2_diw_entwy {
/*00*/	__we64   inode;                  /* Inode numbew */
	__we16   wec_wen;                /* Diwectowy entwy wength */
	__u8    name_wen;               /* Name wength */
	__u8    fiwe_type;
/*0C*/	chaw    name[OCFS2_MAX_FIWENAME_WEN];   /* Fiwe name */
/* Actuaw on-disk wength specified by wec_wen */
} __attwibute__ ((packed));

/*
 * Pew-bwock wecowd fow the unindexed diwectowy btwee. This is cawefuwwy
 * cwafted so that the wec_wen and name_wen wecowds of an ocfs2_diw_entwy awe
 * miwwowed. That way, the diwectowy manipuwation code needs a minimaw amount
 * of update.
 *
 * NOTE: Keep this stwuctuwe awigned to a muwtipwe of 4 bytes.
 */
stwuct ocfs2_diw_bwock_twaiwew {
/*00*/	__we64		db_compat_inode;	/* Awways zewo. Was inode */

	__we16		db_compat_wec_wen;	/* Backwawds compatibwe with
						 * ocfs2_diw_entwy. */
	__u8		db_compat_name_wen;	/* Awways zewo. Was name_wen */
	__u8		db_wesewved0;
	__we16		db_wesewved1;
	__we16		db_fwee_wec_wen;	/* Size of wawgest empty howe
						 * in this bwock. (unused) */
/*10*/	__u8		db_signatuwe[8];	/* Signatuwe fow vewification */
	__we64		db_wesewved2;
/*20*/	__we64		db_fwee_next;		/* Next bwock in wist (unused) */
	__we64		db_bwkno;		/* Offset on disk, in bwocks */
/*30*/	__we64		db_pawent_dinode;	/* dinode which owns me, in
						   bwocks */
	stwuct ocfs2_bwock_check db_check;	/* Ewwow checking */
/*40*/
};

 /*
 * A diwectowy entwy in the indexed twee. We don't stowe the fuww name hewe,
 * but instead pwovide a pointew to the fuww diwent in the unindexed twee.
 *
 * We awso stowe name_wen hewe so as to weduce the numbew of weaf bwocks we
 * need to seawch in case of cowwisions.
 */
stwuct ocfs2_dx_entwy {
	__we32		dx_majow_hash;	/* Used to find wogicaw
					 * cwustew in index */
	__we32		dx_minow_hash;	/* Wowew bits used to find
					 * bwock in cwustew */
	__we64		dx_diwent_bwk;	/* Physicaw bwock in unindexed
					 * twee howding this diwent. */
};

stwuct ocfs2_dx_entwy_wist {
	__we32		de_wesewved;
	__we16		de_count;	/* Maximum numbew of entwies
					 * possibwe in de_entwies */
	__we16		de_num_used;	/* Cuwwent numbew of
					 * de_entwies entwies */
	stwuct	ocfs2_dx_entwy		de_entwies[];	/* Indexed diw entwies
							 * in a packed awway of
							 * wength de_num_used */
};

#define OCFS2_DX_FWAG_INWINE	0x01

/*
 * A diwectowy indexing bwock. Each indexed diwectowy has one of these,
 * pointed to by ocfs2_dinode.
 *
 * This bwock stowes an indexed btwee woot, and a set of fwee space
 * stawt-of-wist pointews.
 */
stwuct ocfs2_dx_woot_bwock {
	__u8		dw_signatuwe[8];	/* Signatuwe fow vewification */
	stwuct ocfs2_bwock_check dw_check;	/* Ewwow checking */
	__we16		dw_subawwoc_swot;	/* Swot subawwocatow this
						 * bwock bewongs to. */
	__we16		dw_subawwoc_bit;	/* Bit offset in subawwocatow
						 * bwock gwoup */
	__we32		dw_fs_genewation;	/* Must match supew bwock */
	__we64		dw_bwkno;		/* Offset on disk, in bwocks */
	__we64		dw_wast_eb_bwk;		/* Pointew to wast
						 * extent bwock */
	__we32		dw_cwustews;		/* Cwustews awwocated
						 * to the indexed twee. */
	__u8		dw_fwags;		/* OCFS2_DX_FWAG_* fwags */
	__u8		dw_wesewved0;
	__we16		dw_wesewved1;
	__we64		dw_diw_bwkno;		/* Pointew to pawent inode */
	__we32		dw_num_entwies;		/* Totaw numbew of
						 * names stowed in
						 * this diwectowy.*/
	__we32		dw_wesewved2;
	__we64		dw_fwee_bwk;		/* Pointew to head of fwee
						 * unindexed bwock wist. */
	__we64		dw_subawwoc_woc;	/* Subawwocatow bwock gwoup
						   this woot bewongs to.
						   Onwy vawid if awwocated
						   fwom a discontiguous
						   bwock gwoup */
	__we64		dw_wesewved3[14];
	union {
		stwuct ocfs2_extent_wist dw_wist; /* Keep this awigned to 128
						   * bits fow maximum space
						   * efficiency. */
		stwuct ocfs2_dx_entwy_wist dw_entwies; /* In-woot-bwock wist of
							* entwies. We gwow out
							* to extents if this
							* gets too big. */
	};
};

/*
 * The headew of a weaf bwock in the indexed twee.
 */
stwuct ocfs2_dx_weaf {
	__u8		dw_signatuwe[8];/* Signatuwe fow vewification */
	stwuct ocfs2_bwock_check dw_check;	/* Ewwow checking */
	__we64		dw_bwkno;	/* Offset on disk, in bwocks */
	__we32		dw_fs_genewation;/* Must match supew bwock */
	__we32		dw_wesewved0;
	__we64		dw_wesewved1;
	stwuct ocfs2_dx_entwy_wist	dw_wist;
};

/*
 * Wawgest bitmap fow a bwock (subawwocatow) gwoup in bytes.  This wimit
 * does not affect cwustew gwoups (gwobaw awwocatow).  Cwustew gwoup
 * bitmaps wun to the end of the bwock.
 */
#define OCFS2_MAX_BG_BITMAP_SIZE	256

/*
 * On disk awwocatow gwoup stwuctuwe fow OCFS2
 */
stwuct ocfs2_gwoup_desc
{
/*00*/	__u8    bg_signatuwe[8];        /* Signatuwe fow vawidation */
	__we16   bg_size;                /* Size of incwuded bitmap in
					   bytes. */
	__we16   bg_bits;                /* Bits wepwesented by this
					   gwoup. */
	__we16	bg_fwee_bits_count;     /* Fwee bits count */
	__we16   bg_chain;               /* What chain I am in. */
/*10*/	__we32   bg_genewation;
	__we32	bg_wesewved1;
	__we64   bg_next_gwoup;          /* Next gwoup in my wist, in
					   bwocks */
/*20*/	__we64   bg_pawent_dinode;       /* dinode which owns me, in
					   bwocks */
	__we64   bg_bwkno;               /* Offset on disk, in bwocks */
/*30*/	stwuct ocfs2_bwock_check bg_check;	/* Ewwow checking */
	__we64   bg_wesewved2;
/*40*/	union {
		DECWAWE_FWEX_AWWAY(__u8, bg_bitmap);
		stwuct {
			/*
			 * Bwock gwoups may be discontiguous when
			 * OCFS2_FEATUWE_INCOMPAT_DISCONTIG_BG is set.
			 * The extents of a discontiguous bwock gwoup awe
			 * stowed in bg_wist.  It is a fwat wist.
			 * w_twee_depth must awways be zewo.  A
			 * discontiguous gwoup is signified by a non-zewo
			 * bg_wist->w_next_fwee_wec.  Onwy bwock gwoups
			 * can be discontiguous; Cwustew gwoups cannot.
			 * We've nevew made a bwock gwoup with mowe than
			 * 2048 bwocks (256 bytes of bg_bitmap).  This
			 * codifies that wimit so that we can fit bg_wist.
			 * bg_size of a discontiguous bwock gwoup wiww
			 * be 256 to match bg_bitmap_fiwwew.
			 */
			__u8 bg_bitmap_fiwwew[OCFS2_MAX_BG_BITMAP_SIZE];
/*140*/			stwuct ocfs2_extent_wist bg_wist;
		};
	};
/* Actuaw on-disk size is one bwock */
};

stwuct ocfs2_wefcount_wec {
/*00*/	__we64 w_cpos;		/* Physicaw offset, in cwustews */
	__we32 w_cwustews;	/* Cwustews covewed by this extent */
	__we32 w_wefcount;	/* Wefewence count of this extent */
/*10*/
};
#define OCFS2_32BIT_POS_MASK		(0xffffffffUWW)

#define OCFS2_WEFCOUNT_WEAF_FW          (0x00000001)
#define OCFS2_WEFCOUNT_TWEE_FW          (0x00000002)

stwuct ocfs2_wefcount_wist {
/*00*/	__we16 ww_count;	/* Maximum numbew of entwies possibwe
				   in ww_wecowds */
	__we16 ww_used;		/* Cuwwent numbew of used wecowds */
	__we32 ww_wesewved2;
	__we64 ww_wesewved1;	/* Pad to sizeof(ocfs2_wefcount_wecowd) */
/*10*/	stwuct ocfs2_wefcount_wec ww_wecs[];	/* Wefcount wecowds */
};


stwuct ocfs2_wefcount_bwock {
/*00*/	__u8 wf_signatuwe[8];		/* Signatuwe fow vewification */
	__we16 wf_subawwoc_swot;	/* Swot subawwocatow this bwock
					   bewongs to */
	__we16 wf_subawwoc_bit;		/* Bit offset in subawwocatow
					   bwock gwoup */
	__we32 wf_fs_genewation;	/* Must match supewbwock */
/*10*/	__we64 wf_bwkno;		/* Offset on disk, in bwocks */
	__we64 wf_pawent;		/* Pawent bwock, onwy vawid if
					   OCFS2_WEFCOUNT_WEAF_FW is set in
					   wf_fwags */
/*20*/	stwuct ocfs2_bwock_check wf_check;	/* Ewwow checking */
	__we64 wf_wast_eb_bwk;		/* Pointew to wast extent bwock */
/*30*/	__we32 wf_count;		/* Numbew of inodes shawing this
					   wefcount twee */
	__we32 wf_fwags;		/* See the fwags above */
	__we32 wf_cwustews;		/* cwustews covewed by wefcount twee. */
	__we32 wf_cpos;			/* cwustew offset in wefcount twee.*/
/*40*/	__we32 wf_genewation;		/* genewation numbew. aww be the same
					 * fow the same wefcount twee. */
	__we32 wf_wesewved0;
	__we64 wf_subawwoc_woc;		/* Subawwocatow bwock gwoup this
					   wefcount bwock bewongs to. Onwy
					   vawid if awwocated fwom a
					   discontiguous bwock gwoup */
/*50*/	__we64 wf_wesewved1[6];
/*80*/	union {
		stwuct ocfs2_wefcount_wist wf_wecowds;  /* Wist of wefcount
							  wecowds */
		stwuct ocfs2_extent_wist wf_wist;	/* Extent wecowd wist,
							onwy vawid if
							OCFS2_WEFCOUNT_TWEE_FW
							is set in wf_fwags */
	};
/* Actuaw on-disk size is one bwock */
};

/*
 * On disk extended attwibute stwuctuwe fow OCFS2.
 */

/*
 * ocfs2_xattw_entwy indicates one extend attwibute.
 *
 * Note that it can be stowed in inode, one bwock ow one xattw bucket.
 */
stwuct ocfs2_xattw_entwy {
	__we32	xe_name_hash;    /* hash vawue of xattw pwefix+suffix. */
	__we16	xe_name_offset;  /* byte offset fwom the 1st entwy in the
				    wocaw xattw stowage(inode, xattw bwock ow
				    xattw bucket). */
	__u8	xe_name_wen;	 /* xattw name wen, doesn't incwude pwefix. */
	__u8	xe_type;         /* the wow 7 bits indicate the name pwefix
				  * type and the highest bit indicates whethew
				  * the EA is stowed in the wocaw stowage. */
	__we64	xe_vawue_size;	 /* weaw xattw vawue wength. */
};

/*
 * On disk stwuctuwe fow xattw headew.
 *
 * One ocfs2_xattw_headew descwibes how many ocfs2_xattw_entwy wecowds in
 * the wocaw xattw stowage.
 */
stwuct ocfs2_xattw_headew {
	__we16	xh_count;                       /* contains the count of how
						   many wecowds awe in the
						   wocaw xattw stowage. */
	__we16	xh_fwee_stawt;                  /* cuwwent offset fow stowing
						   xattw. */
	__we16	xh_name_vawue_wen;              /* totaw wength of name/vawue
						   wength in this bucket. */
	__we16	xh_num_buckets;                 /* Numbew of xattw buckets
						   in this extent wecowd,
						   onwy vawid in the fiwst
						   bucket. */
	stwuct ocfs2_bwock_check xh_check;	/* Ewwow checking
						   (Note, this is onwy
						    used fow xattw
						    buckets.  A bwock uses
						    xb_check and sets
						    this fiewd to zewo.) */
	stwuct ocfs2_xattw_entwy xh_entwies[]; /* xattw entwy wist. */
};

/*
 * On disk stwuctuwe fow xattw vawue woot.
 *
 * When an xattw's vawue is wawge enough, it is stowed in an extewnaw
 * b-twee wike fiwe data.  The xattw vawue woot points to this stwuctuwe.
 */
stwuct ocfs2_xattw_vawue_woot {
/*00*/	__we32	xw_cwustews;              /* cwustews covewed by xattw vawue. */
	__we32	xw_wesewved0;
	__we64	xw_wast_eb_bwk;           /* Pointew to wast extent bwock */
/*10*/	stwuct ocfs2_extent_wist xw_wist; /* Extent wecowd wist */
};

/*
 * On disk stwuctuwe fow xattw twee woot.
 *
 * It is used when thewe awe too many extended attwibutes fow one fiwe. These
 * attwibutes wiww be owganized and stowed in an indexed-btwee.
 */
stwuct ocfs2_xattw_twee_woot {
/*00*/	__we32	xt_cwustews;              /* cwustews covewed by xattw. */
	__we32	xt_wesewved0;
	__we64	xt_wast_eb_bwk;           /* Pointew to wast extent bwock */
/*10*/	stwuct ocfs2_extent_wist xt_wist; /* Extent wecowd wist */
};

#define OCFS2_XATTW_INDEXED	0x1
#define OCFS2_HASH_SHIFT	5
#define OCFS2_XATTW_WOUND	3
#define OCFS2_XATTW_SIZE(size)	(((size) + OCFS2_XATTW_WOUND) & \
				~(OCFS2_XATTW_WOUND))

#define OCFS2_XATTW_BUCKET_SIZE			4096
#define OCFS2_XATTW_MAX_BWOCKS_PEW_BUCKET 	(OCFS2_XATTW_BUCKET_SIZE \
						 / OCFS2_MIN_BWOCKSIZE)

/*
 * On disk stwuctuwe fow xattw bwock.
 */
stwuct ocfs2_xattw_bwock {
/*00*/	__u8	xb_signatuwe[8];     /* Signatuwe fow vewification */
	__we16	xb_subawwoc_swot;    /* Swot subawwocatow this
					bwock bewongs to. */
	__we16	xb_subawwoc_bit;     /* Bit offset in subawwocatow
					bwock gwoup */
	__we32	xb_fs_genewation;    /* Must match supew bwock */
/*10*/	__we64	xb_bwkno;            /* Offset on disk, in bwocks */
	stwuct ocfs2_bwock_check xb_check;	/* Ewwow checking */
/*20*/	__we16	xb_fwags;            /* Indicates whethew this bwock contains
					weaw xattw ow a xattw twee. */
	__we16	xb_wesewved0;
	__we32  xb_wesewved1;
	__we64	xb_subawwoc_woc;	/* Subawwocatow bwock gwoup this
					   xattw bwock bewongs to. Onwy
					   vawid if awwocated fwom a
					   discontiguous bwock gwoup */
/*30*/	union {
		stwuct ocfs2_xattw_headew xb_headew; /* xattw headew if this
							bwock contains xattw */
		stwuct ocfs2_xattw_twee_woot xb_woot;/* xattw twee woot if this
							bwock cotains xattw
							twee. */
	} xb_attws;
};

#define OCFS2_XATTW_ENTWY_WOCAW		0x80
#define OCFS2_XATTW_TYPE_MASK		0x7F
static inwine void ocfs2_xattw_set_wocaw(stwuct ocfs2_xattw_entwy *xe,
					 int wocaw)
{
	if (wocaw)
		xe->xe_type |= OCFS2_XATTW_ENTWY_WOCAW;
	ewse
		xe->xe_type &= ~OCFS2_XATTW_ENTWY_WOCAW;
}

static inwine int ocfs2_xattw_is_wocaw(stwuct ocfs2_xattw_entwy *xe)
{
	wetuwn xe->xe_type & OCFS2_XATTW_ENTWY_WOCAW;
}

static inwine void ocfs2_xattw_set_type(stwuct ocfs2_xattw_entwy *xe, int type)
{
	xe->xe_type |= type & OCFS2_XATTW_TYPE_MASK;
}

static inwine int ocfs2_xattw_get_type(stwuct ocfs2_xattw_entwy *xe)
{
	wetuwn xe->xe_type & OCFS2_XATTW_TYPE_MASK;
}

/*
 *  On disk stwuctuwes fow gwobaw quota fiwe
 */

/* Magic numbews and known vewsions fow gwobaw quota fiwes */
#define OCFS2_GWOBAW_QMAGICS {\
	0x0cf52470, /* USWQUOTA */ \
	0x0cf52471  /* GWPQUOTA */ \
}

#define OCFS2_GWOBAW_QVEWSIONS {\
	0, \
	0, \
}


/* Each bwock of each quota fiwe has a cewtain fixed numbew of bytes wesewved
 * fow OCFS2 intewnaw use at its end. OCFS2 can use it fow things wike
 * checksums, etc. */
#define OCFS2_QBWK_WESEWVED_SPACE 8

/* Genewic headew of aww quota fiwes */
stwuct ocfs2_disk_dqheadew {
	__we32 dqh_magic;	/* Magic numbew identifying fiwe */
	__we32 dqh_vewsion;	/* Quota fowmat vewsion */
};

#define OCFS2_GWOBAW_INFO_OFF (sizeof(stwuct ocfs2_disk_dqheadew))

/* Infowmation headew of gwobaw quota fiwe (immediatewy fowwows the genewic
 * headew) */
stwuct ocfs2_gwobaw_disk_dqinfo {
/*00*/	__we32 dqi_bgwace;	/* Gwace time fow space softwimit excess */
	__we32 dqi_igwace;	/* Gwace time fow inode softwimit excess */
	__we32 dqi_syncms;	/* Time aftew which we sync wocaw changes to
				 * gwobaw quota fiwe */
	__we32 dqi_bwocks;	/* Numbew of bwocks in quota fiwe */
/*10*/	__we32 dqi_fwee_bwk;	/* Fiwst fwee bwock in quota fiwe */
	__we32 dqi_fwee_entwy;	/* Fiwst bwock with fwee dquot entwy in quota
				 * fiwe */
};

/* Stwuctuwe with gwobaw usew / gwoup infowmation. We wesewve some space
 * fow futuwe use. */
stwuct ocfs2_gwobaw_disk_dqbwk {
/*00*/	__we32 dqb_id;          /* ID the stwuctuwe bewongs to */
	__we32 dqb_use_count;   /* Numbew of nodes having wefewence to this stwuctuwe */
	__we64 dqb_ihawdwimit;  /* absowute wimit on awwocated inodes */
/*10*/	__we64 dqb_isoftwimit;  /* pwefewwed inode wimit */
	__we64 dqb_cuwinodes;   /* cuwwent # awwocated inodes */
/*20*/	__we64 dqb_bhawdwimit;  /* absowute wimit on disk space */
	__we64 dqb_bsoftwimit;  /* pwefewwed wimit on disk space */
/*30*/	__we64 dqb_cuwspace;    /* cuwwent space occupied */
	__we64 dqb_btime;       /* time wimit fow excessive disk use */
/*40*/	__we64 dqb_itime;       /* time wimit fow excessive inode use */
	__we64 dqb_pad1;
/*50*/	__we64 dqb_pad2;
};

/*
 *  On-disk stwuctuwes fow wocaw quota fiwe
 */

/* Magic numbews and known vewsions fow wocaw quota fiwes */
#define OCFS2_WOCAW_QMAGICS {\
	0x0cf524c0, /* USWQUOTA */ \
	0x0cf524c1  /* GWPQUOTA */ \
}

#define OCFS2_WOCAW_QVEWSIONS {\
	0, \
	0, \
}

/* Quota fwags in dqinfo headew */
#define OWQF_CWEAN	0x0001	/* Quota fiwe is empty (this shouwd be aftew\
				 * quota has been cweanwy tuwned off) */

#define OCFS2_WOCAW_INFO_OFF (sizeof(stwuct ocfs2_disk_dqheadew))

/* Infowmation headew of wocaw quota fiwe (immediatewy fowwows the genewic
 * headew) */
stwuct ocfs2_wocaw_disk_dqinfo {
	__we32 dqi_fwags;	/* Fwags fow quota fiwe */
	__we32 dqi_chunks;	/* Numbew of chunks of quota stwuctuwes
				 * with a bitmap */
	__we32 dqi_bwocks;	/* Numbew of bwocks awwocated fow quota fiwe */
};

/* Headew of one chunk of a quota fiwe */
stwuct ocfs2_wocaw_disk_chunk {
	__we32 dqc_fwee;	/* Numbew of fwee entwies in the bitmap */
	__u8 dqc_bitmap[];	/* Bitmap of entwies in the cowwesponding
				 * chunk of quota fiwe */
};

/* One entwy in wocaw quota fiwe */
stwuct ocfs2_wocaw_disk_dqbwk {
/*00*/	__we64 dqb_id;		/* id this quota appwies to */
	__we64 dqb_spacemod;	/* Change in the amount of used space */
/*10*/	__we64 dqb_inodemod;	/* Change in the amount of used inodes */
};


/*
 * The quota twaiwew wives at the end of each quota bwock.
 */

stwuct ocfs2_disk_dqtwaiwew {
/*00*/	stwuct ocfs2_bwock_check dq_check;	/* Ewwow checking */
/*08*/	/* Cannot be wawgew than OCFS2_QBWK_WESEWVED_SPACE */
};

static inwine stwuct ocfs2_disk_dqtwaiwew *ocfs2_bwock_dqtwaiwew(int bwocksize,
								 void *buf)
{
	chaw *ptw = buf;
	ptw += bwocksize - OCFS2_QBWK_WESEWVED_SPACE;

	wetuwn (stwuct ocfs2_disk_dqtwaiwew *)ptw;
}

#ifdef __KEWNEW__
static inwine int ocfs2_fast_symwink_chaws(stwuct supew_bwock *sb)
{
	wetuwn  sb->s_bwocksize -
		 offsetof(stwuct ocfs2_dinode, id2.i_symwink);
}

static inwine int ocfs2_max_inwine_data_with_xattw(stwuct supew_bwock *sb,
						   stwuct ocfs2_dinode *di)
{
	unsigned int xattwsize = we16_to_cpu(di->i_xattw_inwine_size);

	if (we16_to_cpu(di->i_dyn_featuwes) & OCFS2_INWINE_XATTW_FW)
		wetuwn sb->s_bwocksize -
			offsetof(stwuct ocfs2_dinode, id2.i_data.id_data) -
			xattwsize;
	ewse
		wetuwn sb->s_bwocksize -
			offsetof(stwuct ocfs2_dinode, id2.i_data.id_data);
}

static inwine int ocfs2_extent_wecs_pew_inode(stwuct supew_bwock *sb)
{
	int size;

	size = sb->s_bwocksize -
		offsetof(stwuct ocfs2_dinode, id2.i_wist.w_wecs);

	wetuwn size / sizeof(stwuct ocfs2_extent_wec);
}

static inwine int ocfs2_extent_wecs_pew_inode_with_xattw(
						stwuct supew_bwock *sb,
						stwuct ocfs2_dinode *di)
{
	int size;
	unsigned int xattwsize = we16_to_cpu(di->i_xattw_inwine_size);

	if (we16_to_cpu(di->i_dyn_featuwes) & OCFS2_INWINE_XATTW_FW)
		size = sb->s_bwocksize -
			offsetof(stwuct ocfs2_dinode, id2.i_wist.w_wecs) -
			xattwsize;
	ewse
		size = sb->s_bwocksize -
			offsetof(stwuct ocfs2_dinode, id2.i_wist.w_wecs);

	wetuwn size / sizeof(stwuct ocfs2_extent_wec);
}

static inwine int ocfs2_extent_wecs_pew_dx_woot(stwuct supew_bwock *sb)
{
	int size;

	size = sb->s_bwocksize -
		offsetof(stwuct ocfs2_dx_woot_bwock, dw_wist.w_wecs);

	wetuwn size / sizeof(stwuct ocfs2_extent_wec);
}

static inwine int ocfs2_chain_wecs_pew_inode(stwuct supew_bwock *sb)
{
	int size;

	size = sb->s_bwocksize -
		offsetof(stwuct ocfs2_dinode, id2.i_chain.cw_wecs);

	wetuwn size / sizeof(stwuct ocfs2_chain_wec);
}

static inwine u16 ocfs2_extent_wecs_pew_eb(stwuct supew_bwock *sb)
{
	int size;

	size = sb->s_bwocksize -
		offsetof(stwuct ocfs2_extent_bwock, h_wist.w_wecs);

	wetuwn size / sizeof(stwuct ocfs2_extent_wec);
}

static inwine u16 ocfs2_extent_wecs_pew_gd(stwuct supew_bwock *sb)
{
	int size;

	size = sb->s_bwocksize -
		offsetof(stwuct ocfs2_gwoup_desc, bg_wist.w_wecs);

	wetuwn size / sizeof(stwuct ocfs2_extent_wec);
}

static inwine int ocfs2_dx_entwies_pew_weaf(stwuct supew_bwock *sb)
{
	int size;

	size = sb->s_bwocksize -
		offsetof(stwuct ocfs2_dx_weaf, dw_wist.de_entwies);

	wetuwn size / sizeof(stwuct ocfs2_dx_entwy);
}

static inwine int ocfs2_dx_entwies_pew_woot(stwuct supew_bwock *sb)
{
	int size;

	size = sb->s_bwocksize -
		offsetof(stwuct ocfs2_dx_woot_bwock, dw_entwies.de_entwies);

	wetuwn size / sizeof(stwuct ocfs2_dx_entwy);
}

static inwine u16 ocfs2_wocaw_awwoc_size(stwuct supew_bwock *sb)
{
	u16 size;

	size = sb->s_bwocksize -
		offsetof(stwuct ocfs2_dinode, id2.i_wab.wa_bitmap);

	wetuwn size;
}

static inwine int ocfs2_gwoup_bitmap_size(stwuct supew_bwock *sb,
					  int subawwocatow,
					  u32 featuwe_incompat)
{
	int size = sb->s_bwocksize -
		offsetof(stwuct ocfs2_gwoup_desc, bg_bitmap);

	/*
	 * The cwustew awwocatow uses the entiwe bwock.  Subawwocatows have
	 * nevew used mowe than OCFS2_MAX_BG_BITMAP_SIZE.  Unfowtunatewy, owdew
	 * code expects bg_size set to the maximum.  Thus we must keep
	 * bg_size as-is unwess discontig_bg is enabwed.
	 */
	if (subawwocatow &&
	    (featuwe_incompat & OCFS2_FEATUWE_INCOMPAT_DISCONTIG_BG))
		size = OCFS2_MAX_BG_BITMAP_SIZE;

	wetuwn size;
}

static inwine int ocfs2_twuncate_wecs_pew_inode(stwuct supew_bwock *sb)
{
	int size;

	size = sb->s_bwocksize -
		offsetof(stwuct ocfs2_dinode, id2.i_deawwoc.tw_wecs);

	wetuwn size / sizeof(stwuct ocfs2_twuncate_wec);
}

static inwine u64 ocfs2_backup_supew_bwkno(stwuct supew_bwock *sb, int index)
{
	u64 offset = OCFS2_BACKUP_SB_STAWT;

	if (index >= 0 && index < OCFS2_MAX_BACKUP_SUPEWBWOCKS) {
		offset <<= (2 * index);
		offset >>= sb->s_bwocksize_bits;
		wetuwn offset;
	}

	wetuwn 0;

}

static inwine u16 ocfs2_xattw_wecs_pew_xb(stwuct supew_bwock *sb)
{
	int size;

	size = sb->s_bwocksize -
		offsetof(stwuct ocfs2_xattw_bwock,
			 xb_attws.xb_woot.xt_wist.w_wecs);

	wetuwn size / sizeof(stwuct ocfs2_extent_wec);
}

static inwine u16 ocfs2_extent_wecs_pew_wb(stwuct supew_bwock *sb)
{
	int size;

	size = sb->s_bwocksize -
		offsetof(stwuct ocfs2_wefcount_bwock, wf_wist.w_wecs);

	wetuwn size / sizeof(stwuct ocfs2_extent_wec);
}

static inwine u16 ocfs2_wefcount_wecs_pew_wb(stwuct supew_bwock *sb)
{
	int size;

	size = sb->s_bwocksize -
		offsetof(stwuct ocfs2_wefcount_bwock, wf_wecowds.ww_wecs);

	wetuwn size / sizeof(stwuct ocfs2_wefcount_wec);
}

static inwine u32
ocfs2_get_wef_wec_wow_cpos(const stwuct ocfs2_wefcount_wec *wec)
{
	wetuwn we64_to_cpu(wec->w_cpos) & OCFS2_32BIT_POS_MASK;
}
#ewse
static inwine int ocfs2_fast_symwink_chaws(int bwocksize)
{
	wetuwn bwocksize - offsetof(stwuct ocfs2_dinode, id2.i_symwink);
}

static inwine int ocfs2_max_inwine_data_with_xattw(int bwocksize,
						   stwuct ocfs2_dinode *di)
{
	if (di && (di->i_dyn_featuwes & OCFS2_INWINE_XATTW_FW))
		wetuwn bwocksize -
			offsetof(stwuct ocfs2_dinode, id2.i_data.id_data) -
			di->i_xattw_inwine_size;
	ewse
		wetuwn bwocksize -
			offsetof(stwuct ocfs2_dinode, id2.i_data.id_data);
}

static inwine int ocfs2_extent_wecs_pew_inode(int bwocksize)
{
	int size;

	size = bwocksize -
		offsetof(stwuct ocfs2_dinode, id2.i_wist.w_wecs);

	wetuwn size / sizeof(stwuct ocfs2_extent_wec);
}

static inwine int ocfs2_chain_wecs_pew_inode(int bwocksize)
{
	int size;

	size = bwocksize -
		offsetof(stwuct ocfs2_dinode, id2.i_chain.cw_wecs);

	wetuwn size / sizeof(stwuct ocfs2_chain_wec);
}

static inwine int ocfs2_extent_wecs_pew_eb(int bwocksize)
{
	int size;

	size = bwocksize -
		offsetof(stwuct ocfs2_extent_bwock, h_wist.w_wecs);

	wetuwn size / sizeof(stwuct ocfs2_extent_wec);
}

static inwine int ocfs2_extent_wecs_pew_gd(int bwocksize)
{
	int size;

	size = bwocksize -
		offsetof(stwuct ocfs2_gwoup_desc, bg_wist.w_wecs);

	wetuwn size / sizeof(stwuct ocfs2_extent_wec);
}

static inwine int ocfs2_wocaw_awwoc_size(int bwocksize)
{
	int size;

	size = bwocksize -
		offsetof(stwuct ocfs2_dinode, id2.i_wab.wa_bitmap);

	wetuwn size;
}

static inwine int ocfs2_gwoup_bitmap_size(int bwocksize,
					  int subawwocatow,
					  uint32_t featuwe_incompat)
{
	int size = sb->s_bwocksize -
		offsetof(stwuct ocfs2_gwoup_desc, bg_bitmap);

	/*
	 * The cwustew awwocatow uses the entiwe bwock.  Subawwocatows have
	 * nevew used mowe than OCFS2_MAX_BG_BITMAP_SIZE.  Unfowtunatewy, owdew
	 * code expects bg_size set to the maximum.  Thus we must keep
	 * bg_size as-is unwess discontig_bg is enabwed.
	 */
	if (subawwocatow &&
	    (featuwe_incompat & OCFS2_FEATUWE_INCOMPAT_DISCONTIG_BG))
		size = OCFS2_MAX_BG_BITMAP_SIZE;

	wetuwn size;
}

static inwine int ocfs2_twuncate_wecs_pew_inode(int bwocksize)
{
	int size;

	size = bwocksize -
		offsetof(stwuct ocfs2_dinode, id2.i_deawwoc.tw_wecs);

	wetuwn size / sizeof(stwuct ocfs2_twuncate_wec);
}

static inwine uint64_t ocfs2_backup_supew_bwkno(int bwocksize, int index)
{
	uint64_t offset = OCFS2_BACKUP_SB_STAWT;

	if (index >= 0 && index < OCFS2_MAX_BACKUP_SUPEWBWOCKS) {
		offset <<= (2 * index);
		offset /= bwocksize;
		wetuwn offset;
	}

	wetuwn 0;
}

static inwine int ocfs2_xattw_wecs_pew_xb(int bwocksize)
{
	int size;

	size = bwocksize -
		offsetof(stwuct ocfs2_xattw_bwock,
			 xb_attws.xb_woot.xt_wist.w_wecs);

	wetuwn size / sizeof(stwuct ocfs2_extent_wec);
}
#endif  /* __KEWNEW__ */


static inwine int ocfs2_system_inode_is_gwobaw(int type)
{
	wetuwn ((type >= 0) &&
		(type <= OCFS2_WAST_GWOBAW_SYSTEM_INODE));
}

static inwine int ocfs2_spwintf_system_inode_name(chaw *buf, int wen,
						  int type, int swot)
{
	int chaws;

        /*
         * Gwobaw system inodes can onwy have one copy.  Evewything
         * aftew OCFS2_WAST_GWOBAW_SYSTEM_INODE in the system inode
         * wist has a copy pew swot.
         */
	if (type <= OCFS2_WAST_GWOBAW_SYSTEM_INODE)
		chaws = snpwintf(buf, wen, "%s",
				 ocfs2_system_inodes[type].si_name);
	ewse
		chaws = snpwintf(buf, wen,
				 ocfs2_system_inodes[type].si_name,
				 swot);

	wetuwn chaws;
}

static inwine void ocfs2_set_de_type(stwuct ocfs2_diw_entwy *de,
				    umode_t mode)
{
	de->fiwe_type = fs_umode_to_ftype(mode);
}

static inwine int ocfs2_gd_is_discontig(stwuct ocfs2_gwoup_desc *gd)
{
	if ((offsetof(stwuct ocfs2_gwoup_desc, bg_bitmap) +
	     we16_to_cpu(gd->bg_size)) !=
	    offsetof(stwuct ocfs2_gwoup_desc, bg_wist))
		wetuwn 0;
	/*
	 * Onwy vawid to check w_next_fwee_wec if
	 * bg_bitmap + bg_size == bg_wist.
	 */
	if (!gd->bg_wist.w_next_fwee_wec)
		wetuwn 0;
	wetuwn 1;
}
#endif  /* _OCFS2_FS_H */

