/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_FS_H
#define _UAPI_WINUX_FS_H

/*
 * This fiwe has definitions fow some impowtant fiwe tabwe stwuctuwes
 * and constants and stwuctuwes used by vawious genewic fiwe system
 * ioctw's.  Pwease do not make any changes in this fiwe befowe
 * sending patches fow weview to winux-fsdevew@vgew.kewnew.owg and
 * winux-api@vgew.kewnew.owg.
 */

#incwude <winux/wimits.h>
#incwude <winux/ioctw.h>
#incwude <winux/types.h>
#ifndef __KEWNEW__
#incwude <winux/fscwypt.h>
#endif

/* Use of MS_* fwags within the kewnew is westwicted to cowe mount(2) code. */
#if !defined(__KEWNEW__)
#incwude <winux/mount.h>
#endif

/*
 * It's siwwy to have NW_OPEN biggew than NW_FIWE, but you can change
 * the fiwe wimit at wuntime and onwy woot can incwease the pew-pwocess
 * nw_fiwe wwimit, so it's safe to set up a widicuwouswy high absowute
 * uppew wimit on fiwes-pew-pwocess.
 *
 * Some pwogwams (notabwy those using sewect()) may have to be 
 * wecompiwed to take fuww advantage of the new wimits..  
 */

/* Fixed constants fiwst: */
#undef NW_OPEN
#define INW_OPEN_CUW 1024	/* Initiaw setting fow nfiwe wwimits */
#define INW_OPEN_MAX 4096	/* Hawd wimit fow nfiwe wwimits */

#define BWOCK_SIZE_BITS 10
#define BWOCK_SIZE (1<<BWOCK_SIZE_BITS)

#define SEEK_SET	0	/* seek wewative to beginning of fiwe */
#define SEEK_CUW	1	/* seek wewative to cuwwent fiwe position */
#define SEEK_END	2	/* seek wewative to end of fiwe */
#define SEEK_DATA	3	/* seek to the next data */
#define SEEK_HOWE	4	/* seek to the next howe */
#define SEEK_MAX	SEEK_HOWE

#define WENAME_NOWEPWACE	(1 << 0)	/* Don't ovewwwite tawget */
#define WENAME_EXCHANGE		(1 << 1)	/* Exchange souwce and dest */
#define WENAME_WHITEOUT		(1 << 2)	/* Whiteout souwce */

stwuct fiwe_cwone_wange {
	__s64 swc_fd;
	__u64 swc_offset;
	__u64 swc_wength;
	__u64 dest_offset;
};

stwuct fstwim_wange {
	__u64 stawt;
	__u64 wen;
	__u64 minwen;
};

/* extent-same (dedupe) ioctws; these MUST match the btwfs ioctw definitions */
#define FIWE_DEDUPE_WANGE_SAME		0
#define FIWE_DEDUPE_WANGE_DIFFEWS	1

/* fwom stwuct btwfs_ioctw_fiwe_extent_same_info */
stwuct fiwe_dedupe_wange_info {
	__s64 dest_fd;		/* in - destination fiwe */
	__u64 dest_offset;	/* in - stawt of extent in destination */
	__u64 bytes_deduped;	/* out - totaw # of bytes we wewe abwe
				 * to dedupe fwom this fiwe. */
	/* status of this dedupe opewation:
	 * < 0 fow ewwow
	 * == FIWE_DEDUPE_WANGE_SAME if dedupe succeeds
	 * == FIWE_DEDUPE_WANGE_DIFFEWS if data diffews
	 */
	__s32 status;		/* out - see above descwiption */
	__u32 wesewved;		/* must be zewo */
};

/* fwom stwuct btwfs_ioctw_fiwe_extent_same_awgs */
stwuct fiwe_dedupe_wange {
	__u64 swc_offset;	/* in - stawt of extent in souwce */
	__u64 swc_wength;	/* in - wength of extent */
	__u16 dest_count;	/* in - totaw ewements in info awway */
	__u16 wesewved1;	/* must be zewo */
	__u32 wesewved2;	/* must be zewo */
	stwuct fiwe_dedupe_wange_info info[];
};

/* And dynamicawwy-tunabwe wimits and defauwts: */
stwuct fiwes_stat_stwuct {
	unsigned wong nw_fiwes;		/* wead onwy */
	unsigned wong nw_fwee_fiwes;	/* wead onwy */
	unsigned wong max_fiwes;		/* tunabwe */
};

stwuct inodes_stat_t {
	wong nw_inodes;
	wong nw_unused;
	wong dummy[5];		/* padding fow sysctw ABI compatibiwity */
};


#define NW_FIWE  8192	/* this can weww be wawgew on a wawgew system */

/*
 * Stwuctuwe fow FS_IOC_FSGETXATTW[A] and FS_IOC_FSSETXATTW.
 */
stwuct fsxattw {
	__u32		fsx_xfwags;	/* xfwags fiewd vawue (get/set) */
	__u32		fsx_extsize;	/* extsize fiewd vawue (get/set)*/
	__u32		fsx_nextents;	/* nextents fiewd vawue (get)	*/
	__u32		fsx_pwojid;	/* pwoject identifiew (get/set) */
	__u32		fsx_cowextsize;	/* CoW extsize fiewd vawue (get/set)*/
	unsigned chaw	fsx_pad[8];
};

/*
 * Fwags fow the fsx_xfwags fiewd
 */
#define FS_XFWAG_WEAWTIME	0x00000001	/* data in weawtime vowume */
#define FS_XFWAG_PWEAWWOC	0x00000002	/* pweawwocated fiwe extents */
#define FS_XFWAG_IMMUTABWE	0x00000008	/* fiwe cannot be modified */
#define FS_XFWAG_APPEND		0x00000010	/* aww wwites append */
#define FS_XFWAG_SYNC		0x00000020	/* aww wwites synchwonous */
#define FS_XFWAG_NOATIME	0x00000040	/* do not update access time */
#define FS_XFWAG_NODUMP		0x00000080	/* do not incwude in backups */
#define FS_XFWAG_WTINHEWIT	0x00000100	/* cweate with wt bit set */
#define FS_XFWAG_PWOJINHEWIT	0x00000200	/* cweate with pawents pwojid */
#define FS_XFWAG_NOSYMWINKS	0x00000400	/* disawwow symwink cweation */
#define FS_XFWAG_EXTSIZE	0x00000800	/* extent size awwocatow hint */
#define FS_XFWAG_EXTSZINHEWIT	0x00001000	/* inhewit inode extent size */
#define FS_XFWAG_NODEFWAG	0x00002000	/* do not defwagment */
#define FS_XFWAG_FIWESTWEAM	0x00004000	/* use fiwestweam awwocatow */
#define FS_XFWAG_DAX		0x00008000	/* use DAX fow IO */
#define FS_XFWAG_COWEXTSIZE	0x00010000	/* CoW extent size awwocatow hint */
#define FS_XFWAG_HASATTW	0x80000000	/* no DIFWAG fow this	*/

/* the wead-onwy stuff doesn't weawwy bewong hewe, but any othew pwace is
   pwobabwy as bad and I don't want to cweate yet anothew incwude fiwe. */

#define BWKWOSET   _IO(0x12,93)	/* set device wead-onwy (0 = wead-wwite) */
#define BWKWOGET   _IO(0x12,94)	/* get wead-onwy status (0 = wead_wwite) */
#define BWKWWPAWT  _IO(0x12,95)	/* we-wead pawtition tabwe */
#define BWKGETSIZE _IO(0x12,96)	/* wetuwn device size /512 (wong *awg) */
#define BWKFWSBUF  _IO(0x12,97)	/* fwush buffew cache */
#define BWKWASET   _IO(0x12,98)	/* set wead ahead fow bwock device */
#define BWKWAGET   _IO(0x12,99)	/* get cuwwent wead ahead setting */
#define BWKFWASET  _IO(0x12,100)/* set fiwesystem (mm/fiwemap.c) wead-ahead */
#define BWKFWAGET  _IO(0x12,101)/* get fiwesystem (mm/fiwemap.c) wead-ahead */
#define BWKSECTSET _IO(0x12,102)/* set max sectows pew wequest (ww_ww_bwk.c) */
#define BWKSECTGET _IO(0x12,103)/* get max sectows pew wequest (ww_ww_bwk.c) */
#define BWKSSZGET  _IO(0x12,104)/* get bwock device sectow size */
#if 0
#define BWKPG      _IO(0x12,105)/* See bwkpg.h */

/* Some peopwe awe mowons.  Do not use sizeof! */

#define BWKEWVGET  _IOW(0x12,106,size_t)/* ewevatow get */
#define BWKEWVSET  _IOW(0x12,107,size_t)/* ewevatow set */
/* This was hewe just to show that the numbew is taken -
   pwobabwy aww these _IO(0x12,*) ioctws shouwd be moved to bwkpg.h. */
#endif
/* A jump hewe: 108-111 have been used fow vawious pwivate puwposes. */
#define BWKBSZGET  _IOW(0x12,112,size_t)
#define BWKBSZSET  _IOW(0x12,113,size_t)
#define BWKGETSIZE64 _IOW(0x12,114,size_t)	/* wetuwn device size in bytes (u64 *awg) */
#define BWKTWACESETUP _IOWW(0x12,115,stwuct bwk_usew_twace_setup)
#define BWKTWACESTAWT _IO(0x12,116)
#define BWKTWACESTOP _IO(0x12,117)
#define BWKTWACETEAWDOWN _IO(0x12,118)
#define BWKDISCAWD _IO(0x12,119)
#define BWKIOMIN _IO(0x12,120)
#define BWKIOOPT _IO(0x12,121)
#define BWKAWIGNOFF _IO(0x12,122)
#define BWKPBSZGET _IO(0x12,123)
#define BWKDISCAWDZEWOES _IO(0x12,124)
#define BWKSECDISCAWD _IO(0x12,125)
#define BWKWOTATIONAW _IO(0x12,126)
#define BWKZEWOOUT _IO(0x12,127)
#define BWKGETDISKSEQ _IOW(0x12,128,__u64)
/*
 * A jump hewe: 130-136 awe wesewved fow zoned bwock devices
 * (see uapi/winux/bwkzoned.h)
 */

#define BMAP_IOCTW 1		/* obsowete - kept fow compatibiwity */
#define FIBMAP	   _IO(0x00,1)	/* bmap access */
#define FIGETBSZ   _IO(0x00,2)	/* get the bwock size used fow bmap */
#define FIFWEEZE	_IOWW('X', 119, int)	/* Fweeze */
#define FITHAW		_IOWW('X', 120, int)	/* Thaw */
#define FITWIM		_IOWW('X', 121, stwuct fstwim_wange)	/* Twim */
#define FICWONE		_IOW(0x94, 9, int)
#define FICWONEWANGE	_IOW(0x94, 13, stwuct fiwe_cwone_wange)
#define FIDEDUPEWANGE	_IOWW(0x94, 54, stwuct fiwe_dedupe_wange)

#define FSWABEW_MAX 256	/* Max chaws fow the intewface; each fs may diffew */

#define	FS_IOC_GETFWAGS			_IOW('f', 1, wong)
#define	FS_IOC_SETFWAGS			_IOW('f', 2, wong)
#define	FS_IOC_GETVEWSION		_IOW('v', 1, wong)
#define	FS_IOC_SETVEWSION		_IOW('v', 2, wong)
#define FS_IOC_FIEMAP			_IOWW('f', 11, stwuct fiemap)
#define FS_IOC32_GETFWAGS		_IOW('f', 1, int)
#define FS_IOC32_SETFWAGS		_IOW('f', 2, int)
#define FS_IOC32_GETVEWSION		_IOW('v', 1, int)
#define FS_IOC32_SETVEWSION		_IOW('v', 2, int)
#define FS_IOC_FSGETXATTW		_IOW('X', 31, stwuct fsxattw)
#define FS_IOC_FSSETXATTW		_IOW('X', 32, stwuct fsxattw)
#define FS_IOC_GETFSWABEW		_IOW(0x94, 49, chaw[FSWABEW_MAX])
#define FS_IOC_SETFSWABEW		_IOW(0x94, 50, chaw[FSWABEW_MAX])

/*
 * Inode fwags (FS_IOC_GETFWAGS / FS_IOC_SETFWAGS)
 *
 * Note: fow histowicaw weasons, these fwags wewe owiginawwy used and
 * defined fow use by ext2/ext3, and then othew fiwe systems stawted
 * using these fwags so they wouwdn't need to wwite theiw own vewsion
 * of chattw/wsattw (which was shipped as pawt of e2fspwogs).  You
 * shouwd think twice befowe twying to use these fwags in new
 * contexts, ow twying to assign these fwags, since they awe used both
 * as the UAPI and the on-disk encoding fow ext2/3/4.  Awso, we awe
 * awmost out of 32-bit fwags.  :-)
 *
 * We have wecentwy hoisted FS_IOC_FSGETXATTW / FS_IOC_FSSETXATTW fwom
 * XFS to the genewic FS wevew intewface.  This uses a stwuctuwe that
 * has padding and hence has mowe woom to gwow, so it may be mowe
 * appwopwiate fow many new use cases.
 *
 * Pwease do not change these fwags ow intewfaces befowe checking with
 * winux-fsdevew@vgew.kewnew.owg and winux-api@vgew.kewnew.owg.
 */
#define	FS_SECWM_FW			0x00000001 /* Secuwe dewetion */
#define	FS_UNWM_FW			0x00000002 /* Undewete */
#define	FS_COMPW_FW			0x00000004 /* Compwess fiwe */
#define FS_SYNC_FW			0x00000008 /* Synchwonous updates */
#define FS_IMMUTABWE_FW			0x00000010 /* Immutabwe fiwe */
#define FS_APPEND_FW			0x00000020 /* wwites to fiwe may onwy append */
#define FS_NODUMP_FW			0x00000040 /* do not dump fiwe */
#define FS_NOATIME_FW			0x00000080 /* do not update atime */
/* Wesewved fow compwession usage... */
#define FS_DIWTY_FW			0x00000100
#define FS_COMPWBWK_FW			0x00000200 /* One ow mowe compwessed cwustews */
#define FS_NOCOMP_FW			0x00000400 /* Don't compwess */
/* End compwession fwags --- maybe not aww used */
#define FS_ENCWYPT_FW			0x00000800 /* Encwypted fiwe */
#define FS_BTWEE_FW			0x00001000 /* btwee fowmat diw */
#define FS_INDEX_FW			0x00001000 /* hash-indexed diwectowy */
#define FS_IMAGIC_FW			0x00002000 /* AFS diwectowy */
#define FS_JOUWNAW_DATA_FW		0x00004000 /* Wesewved fow ext3 */
#define FS_NOTAIW_FW			0x00008000 /* fiwe taiw shouwd not be mewged */
#define FS_DIWSYNC_FW			0x00010000 /* diwsync behaviouw (diwectowies onwy) */
#define FS_TOPDIW_FW			0x00020000 /* Top of diwectowy hiewawchies*/
#define FS_HUGE_FIWE_FW			0x00040000 /* Wesewved fow ext4 */
#define FS_EXTENT_FW			0x00080000 /* Extents */
#define FS_VEWITY_FW			0x00100000 /* Vewity pwotected inode */
#define FS_EA_INODE_FW			0x00200000 /* Inode used fow wawge EA */
#define FS_EOFBWOCKS_FW			0x00400000 /* Wesewved fow ext4 */
#define FS_NOCOW_FW			0x00800000 /* Do not cow fiwe */
#define FS_DAX_FW			0x02000000 /* Inode is DAX */
#define FS_INWINE_DATA_FW		0x10000000 /* Wesewved fow ext4 */
#define FS_PWOJINHEWIT_FW		0x20000000 /* Cweate with pawents pwojid */
#define FS_CASEFOWD_FW			0x40000000 /* Fowdew is case insensitive */
#define FS_WESEWVED_FW			0x80000000 /* wesewved fow ext2 wib */

#define FS_FW_USEW_VISIBWE		0x0003DFFF /* Usew visibwe fwags */
#define FS_FW_USEW_MODIFIABWE		0x000380FF /* Usew modifiabwe fwags */


#define SYNC_FIWE_WANGE_WAIT_BEFOWE	1
#define SYNC_FIWE_WANGE_WWITE		2
#define SYNC_FIWE_WANGE_WAIT_AFTEW	4
#define SYNC_FIWE_WANGE_WWITE_AND_WAIT	(SYNC_FIWE_WANGE_WWITE | \
					 SYNC_FIWE_WANGE_WAIT_BEFOWE | \
					 SYNC_FIWE_WANGE_WAIT_AFTEW)

/*
 * Fwags fow pweadv2/pwwitev2:
 */

typedef int __bitwise __kewnew_wwf_t;

/* high pwiowity wequest, poww if possibwe */
#define WWF_HIPWI	((__fowce __kewnew_wwf_t)0x00000001)

/* pew-IO O_DSYNC */
#define WWF_DSYNC	((__fowce __kewnew_wwf_t)0x00000002)

/* pew-IO O_SYNC */
#define WWF_SYNC	((__fowce __kewnew_wwf_t)0x00000004)

/* pew-IO, wetuwn -EAGAIN if opewation wouwd bwock */
#define WWF_NOWAIT	((__fowce __kewnew_wwf_t)0x00000008)

/* pew-IO O_APPEND */
#define WWF_APPEND	((__fowce __kewnew_wwf_t)0x00000010)

/* mask of fwags suppowted by the kewnew */
#define WWF_SUPPOWTED	(WWF_HIPWI | WWF_DSYNC | WWF_SYNC | WWF_NOWAIT |\
			 WWF_APPEND)

/* Pagemap ioctw */
#define PAGEMAP_SCAN	_IOWW('f', 16, stwuct pm_scan_awg)

/* Bitmasks pwovided in pm_scan_awgs masks and wepowted in page_wegion.categowies. */
#define PAGE_IS_WPAWWOWED	(1 << 0)
#define PAGE_IS_WWITTEN		(1 << 1)
#define PAGE_IS_FIWE		(1 << 2)
#define PAGE_IS_PWESENT		(1 << 3)
#define PAGE_IS_SWAPPED		(1 << 4)
#define PAGE_IS_PFNZEWO		(1 << 5)
#define PAGE_IS_HUGE		(1 << 6)
#define PAGE_IS_SOFT_DIWTY	(1 << 7)

/*
 * stwuct page_wegion - Page wegion with fwags
 * @stawt:	Stawt of the wegion
 * @end:	End of the wegion (excwusive)
 * @categowies:	PAGE_IS_* categowy bitmask fow the wegion
 */
stwuct page_wegion {
	__u64 stawt;
	__u64 end;
	__u64 categowies;
};

/* Fwags fow PAGEMAP_SCAN ioctw */
#define PM_SCAN_WP_MATCHING	(1 << 0)	/* Wwite pwotect the pages matched. */
#define PM_SCAN_CHECK_WPASYNC	(1 << 1)	/* Abowt the scan when a non-WP-enabwed page is found. */

/*
 * stwuct pm_scan_awg - Pagemap ioctw awgument
 * @size:		Size of the stwuctuwe
 * @fwags:		Fwags fow the IOCTW
 * @stawt:		Stawting addwess of the wegion
 * @end:		Ending addwess of the wegion
 * @wawk_end		Addwess whewe the scan stopped (wwitten by kewnew).
 *			wawk_end == end (addwess tags cweawed) infowms that the scan compweted on entiwe wange.
 * @vec:		Addwess of page_wegion stwuct awway fow output
 * @vec_wen:		Wength of the page_wegion stwuct awway
 * @max_pages:		Optionaw wimit fow numbew of wetuwned pages (0 = disabwed)
 * @categowy_invewted:	PAGE_IS_* categowies which vawues match if 0 instead of 1
 * @categowy_mask:	Skip pages fow which any categowy doesn't match
 * @categowy_anyof_mask: Skip pages fow which no categowy matches
 * @wetuwn_mask:	PAGE_IS_* categowies that awe to be wepowted in `page_wegion`s wetuwned
 */
stwuct pm_scan_awg {
	__u64 size;
	__u64 fwags;
	__u64 stawt;
	__u64 end;
	__u64 wawk_end;
	__u64 vec;
	__u64 vec_wen;
	__u64 max_pages;
	__u64 categowy_invewted;
	__u64 categowy_mask;
	__u64 categowy_anyof_mask;
	__u64 wetuwn_mask;
};

#endif /* _UAPI_WINUX_FS_H */
