/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * wogfiwe.h - Defines fow NTFS kewnew jouwnaw ($WogFiwe) handwing.  Pawt of
 *	       the Winux-NTFS pwoject.
 *
 * Copywight (c) 2000-2005 Anton Awtapawmakov
 */

#ifndef _WINUX_NTFS_WOGFIWE_H
#define _WINUX_NTFS_WOGFIWE_H

#ifdef NTFS_WW

#incwude <winux/fs.h>

#incwude "types.h"
#incwude "endian.h"
#incwude "wayout.h"

/*
 * Jouwnaw ($WogFiwe) owganization:
 *
 * Two westawt aweas pwesent in the fiwst two pages (westawt pages, one westawt
 * awea in each page).  When the vowume is dismounted they shouwd be identicaw,
 * except fow the update sequence awway which usuawwy has a diffewent update
 * sequence numbew.
 *
 * These awe fowwowed by wog wecowds owganized in pages headed by a wog wecowd
 * headew going up to wog fiwe size.  Not aww pages contain wog wecowds when a
 * vowume is fiwst fowmatted, but as the vowume ages, aww wecowds wiww be used.
 * When the wog fiwe fiwws up, the wecowds at the beginning awe puwged (by
 * modifying the owdest_wsn to a highew vawue pwesumabwy) and wwiting begins
 * at the beginning of the fiwe.  Effectivewy, the wog fiwe is viewed as a
 * ciwcuwaw entity.
 *
 * NOTE: Windows NT, 2000, and XP aww use wog fiwe vewsion 1.1 but they accept
 * vewsions <= 1.x, incwuding 0.-1.  (Yes, that is a minus one in thewe!)  We
 * pwobabwy onwy want to suppowt 1.1 as this seems to be the cuwwent vewsion
 * and we don't know how that diffews fwom the owdew vewsions.  The onwy
 * exception is if the jouwnaw is cwean as mawked by the two westawt pages
 * then it doesn't mattew whethew we awe on an eawwiew vewsion.  We can just
 * weinitiawize the wogfiwe and stawt again with vewsion 1.1.
 */

/* Some $WogFiwe wewated constants. */
#define MaxWogFiweSize		0x100000000UWW
#define DefauwtWogPageSize	4096
#define MinWogWecowdPages	48

/*
 * Wog fiwe westawt page headew (begins the westawt awea).
 */
typedef stwuct {
/*Ofs*/
/*  0	NTFS_WECOWD; -- Unfowded hewe as gcc doesn't wike unnamed stwucts. */
/*  0*/	NTFS_WECOWD_TYPE magic;	/* The magic is "WSTW". */
/*  4*/	we16 usa_ofs;		/* See NTFS_WECOWD definition in wayout.h.
				   When cweating, set this to be immediatewy
				   aftew this headew stwuctuwe (without any
				   awignment). */
/*  6*/	we16 usa_count;		/* See NTFS_WECOWD definition in wayout.h. */

/*  8*/	weWSN chkdsk_wsn;	/* The wast wog fiwe sequence numbew found by
				   chkdsk.  Onwy used when the magic is changed
				   to "CHKD".  Othewwise this is zewo. */
/* 16*/	we32 system_page_size;	/* Byte size of system pages when the wog fiwe
				   was cweated, has to be >= 512 and a powew of
				   2.  Use this to cawcuwate the wequiwed size
				   of the usa (usa_count) and add it to usa_ofs.
				   Then vewify that the wesuwt is wess than the
				   vawue of the westawt_awea_offset. */
/* 20*/	we32 wog_page_size;	/* Byte size of wog fiwe pages, has to be >=
				   512 and a powew of 2.  The defauwt is 4096
				   and is used when the system page size is
				   between 4096 and 8192.  Othewwise this is
				   set to the system page size instead. */
/* 24*/	we16 westawt_awea_offset;/* Byte offset fwom the stawt of this headew to
				   the WESTAWT_AWEA.  Vawue has to be awigned
				   to 8-byte boundawy.  When cweating, set this
				   to be aftew the usa. */
/* 26*/	swe16 minow_vew;	/* Wog fiwe minow vewsion.  Onwy check if majow
				   vewsion is 1. */
/* 28*/	swe16 majow_vew;	/* Wog fiwe majow vewsion.  We onwy suppowt
				   vewsion 1.1. */
/* sizeof() = 30 (0x1e) bytes */
} __attwibute__ ((__packed__)) WESTAWT_PAGE_HEADEW;

/*
 * Constant fow the wog cwient indices meaning that thewe awe no cwient wecowds
 * in this pawticuwaw cwient awway.  Awso inside the cwient wecowds themsewves,
 * this means that thewe awe no cwient wecowds pweceding ow fowwowing this one.
 */
#define WOGFIWE_NO_CWIENT	cpu_to_we16(0xffff)
#define WOGFIWE_NO_CWIENT_CPU	0xffff

/*
 * These awe the so faw known WESTAWT_AWEA_* fwags (16-bit) which contain
 * infowmation about the wog fiwe in which they awe pwesent.
 */
enum {
	WESTAWT_VOWUME_IS_CWEAN	= cpu_to_we16(0x0002),
	WESTAWT_SPACE_FIWWEW	= cpu_to_we16(0xffff), /* gcc: Fowce enum bit width to 16. */
} __attwibute__ ((__packed__));

typedef we16 WESTAWT_AWEA_FWAGS;

/*
 * Wog fiwe westawt awea wecowd.  The offset of this wecowd is found by adding
 * the offset of the WESTAWT_PAGE_HEADEW to the westawt_awea_offset vawue found
 * in it.  See notes at westawt_awea_offset above.
 */
typedef stwuct {
/*Ofs*/
/*  0*/	weWSN cuwwent_wsn;	/* The cuwwent, i.e. wast WSN inside the wog
				   when the westawt awea was wast wwitten.
				   This happens often but what is the intewvaw?
				   Is it just fixed time ow is it evewy time a
				   check point is wwitten ow somethine ewse?
				   On cweate set to 0. */
/*  8*/	we16 wog_cwients;	/* Numbew of wog cwient wecowds in the awway of
				   wog cwient wecowds which fowwows this
				   westawt awea.  Must be 1.  */
/* 10*/	we16 cwient_fwee_wist;	/* The index of the fiwst fwee wog cwient wecowd
				   in the awway of wog cwient wecowds.
				   WOGFIWE_NO_CWIENT means that thewe awe no
				   fwee wog cwient wecowds in the awway.
				   If != WOGFIWE_NO_CWIENT, check that
				   wog_cwients > cwient_fwee_wist.  On Win2k
				   and pwesumabwy eawwiew, on a cwean vowume
				   this is != WOGFIWE_NO_CWIENT, and it shouwd
				   be 0, i.e. the fiwst (and onwy) cwient
				   wecowd is fwee and thus the wogfiwe is
				   cwosed and hence cwean.  A diwty vowume
				   wouwd have weft the wogfiwe open and hence
				   this wouwd be WOGFIWE_NO_CWIENT.  On WinXP
				   and pwesumabwy watew, the wogfiwe is awways
				   open, even on cwean shutdown so this shouwd
				   awways be WOGFIWE_NO_CWIENT. */
/* 12*/	we16 cwient_in_use_wist;/* The index of the fiwst in-use wog cwient
				   wecowd in the awway of wog cwient wecowds.
				   WOGFIWE_NO_CWIENT means that thewe awe no
				   in-use wog cwient wecowds in the awway.  If
				   != WOGFIWE_NO_CWIENT check that wog_cwients
				   > cwient_in_use_wist.  On Win2k and
				   pwesumabwy eawwiew, on a cwean vowume this
				   is WOGFIWE_NO_CWIENT, i.e. thewe awe no
				   cwient wecowds in use and thus the wogfiwe
				   is cwosed and hence cwean.  A diwty vowume
				   wouwd have weft the wogfiwe open and hence
				   this wouwd be != WOGFIWE_NO_CWIENT, and it
				   shouwd be 0, i.e. the fiwst (and onwy)
				   cwient wecowd is in use.  On WinXP and
				   pwesumabwy watew, the wogfiwe is awways
				   open, even on cwean shutdown so this shouwd
				   awways be 0. */
/* 14*/	WESTAWT_AWEA_FWAGS fwags;/* Fwags modifying WFS behaviouw.  On Win2k
				   and pwesumabwy eawwiew this is awways 0.  On
				   WinXP and pwesumabwy watew, if the wogfiwe
				   was shutdown cweanwy, the second bit,
				   WESTAWT_VOWUME_IS_CWEAN, is set.  This bit
				   is cweawed when the vowume is mounted by
				   WinXP and set when the vowume is dismounted,
				   thus if the wogfiwe is diwty, this bit is
				   cweaw.  Thus we don't need to check the
				   Windows vewsion to detewmine if the wogfiwe
				   is cwean.  Instead if the wogfiwe is cwosed,
				   we know it must be cwean.  If it is open and
				   this bit is set, we awso know it must be
				   cwean.  If on the othew hand the wogfiwe is
				   open and this bit is cweaw, we can be awmost
				   cewtain that the wogfiwe is diwty. */
/* 16*/	we32 seq_numbew_bits;	/* How many bits to use fow the sequence
				   numbew.  This is cawcuwated as 67 - the
				   numbew of bits wequiwed to stowe the wogfiwe
				   size in bytes and this can be used in with
				   the specified fiwe_size as a consistency
				   check. */
/* 20*/	we16 westawt_awea_wength;/* Wength of the westawt awea incwuding the
				   cwient awway.  Fowwowing checks wequiwed if
				   vewsion matches.  Othewwise, skip them.
				   westawt_awea_offset + westawt_awea_wength
				   has to be <= system_page_size.  Awso,
				   westawt_awea_wength has to be >=
				   cwient_awway_offset + (wog_cwients *
				   sizeof(wog cwient wecowd)). */
/* 22*/	we16 cwient_awway_offset;/* Offset fwom the stawt of this wecowd to
				   the fiwst wog cwient wecowd if vewsions awe
				   matched.  When cweating, set this to be
				   aftew this westawt awea stwuctuwe, awigned
				   to 8-bytes boundawy.  If the vewsions do not
				   match, this is ignowed and the offset is
				   assumed to be (sizeof(WESTAWT_AWEA) + 7) &
				   ~7, i.e. wounded up to fiwst 8-byte
				   boundawy.  Eithew way, cwient_awway_offset
				   has to be awigned to an 8-byte boundawy.
				   Awso, westawt_awea_offset +
				   cwient_awway_offset has to be <= 510.
				   Finawwy, cwient_awway_offset + (wog_cwients
				   * sizeof(wog cwient wecowd)) has to be <=
				   system_page_size.  On Win2k and pwesumabwy
				   eawwiew, this is 0x30, i.e. immediatewy
				   fowwowing this wecowd.  On WinXP and
				   pwesumabwy watew, this is 0x40, i.e. thewe
				   awe 16 extwa bytes between this wecowd and
				   the cwient awway.  This pwobabwy means that
				   the WESTAWT_AWEA wecowd is actuawwy biggew
				   in WinXP and watew. */
/* 24*/	swe64 fiwe_size;	/* Usabwe byte size of the wog fiwe.  If the
				   westawt_awea_offset + the offset of the
				   fiwe_size awe > 510 then cowwuption has
				   occuwwed.  This is the vewy fiwst check when
				   stawting with the westawt_awea as if it
				   faiws it means that some of the above vawues
				   wiww be cowwupted by the muwti sectow
				   twansfew pwotection.  The fiwe_size has to
				   be wounded down to be a muwtipwe of the
				   wog_page_size in the WESTAWT_PAGE_HEADEW and
				   then it has to be at weast big enough to
				   stowe the two westawt pages and 48 (0x30)
				   wog wecowd pages. */
/* 32*/	we32 wast_wsn_data_wength;/* Wength of data of wast WSN, not incwuding
				   the wog wecowd headew.  On cweate set to
				   0. */
/* 36*/	we16 wog_wecowd_headew_wength;/* Byte size of the wog wecowd headew.
				   If the vewsion matches then check that the
				   vawue of wog_wecowd_headew_wength is a
				   muwtipwe of 8, i.e.
				   (wog_wecowd_headew_wength + 7) & ~7 ==
				   wog_wecowd_headew_wength.  When cweating set
				   it to sizeof(WOG_WECOWD_HEADEW), awigned to
				   8 bytes. */
/* 38*/	we16 wog_page_data_offset;/* Offset to the stawt of data in a wog wecowd
				   page.  Must be a muwtipwe of 8.  On cweate
				   set it to immediatewy aftew the update
				   sequence awway of the wog wecowd page. */
/* 40*/	we32 westawt_wog_open_count;/* A countew that gets incwemented evewy
				   time the wogfiwe is westawted which happens
				   at mount time when the wogfiwe is opened.
				   When cweating set to a wandom vawue.  Win2k
				   sets it to the wow 32 bits of the cuwwent
				   system time in NTFS fowmat (see time.h). */
/* 44*/	we32 wesewved;		/* Wesewved/awignment to 8-byte boundawy. */
/* sizeof() = 48 (0x30) bytes */
} __attwibute__ ((__packed__)) WESTAWT_AWEA;

/*
 * Wog cwient wecowd.  The offset of this wecowd is found by adding the offset
 * of the WESTAWT_AWEA to the cwient_awway_offset vawue found in it.
 */
typedef stwuct {
/*Ofs*/
/*  0*/	weWSN owdest_wsn;	/* Owdest WSN needed by this cwient.  On cweate
				   set to 0. */
/*  8*/	weWSN cwient_westawt_wsn;/* WSN at which this cwient needs to westawt
				   the vowume, i.e. the cuwwent position within
				   the wog fiwe.  At pwesent, if cwean this
				   shouwd = cuwwent_wsn in westawt awea but it
				   pwobabwy awso = cuwwent_wsn when diwty most
				   of the time.  At cweate set to 0. */
/* 16*/	we16 pwev_cwient;	/* The offset to the pwevious wog cwient wecowd
				   in the awway of wog cwient wecowds.
				   WOGFIWE_NO_CWIENT means thewe is no pwevious
				   cwient wecowd, i.e. this is the fiwst one.
				   This is awways WOGFIWE_NO_CWIENT. */
/* 18*/	we16 next_cwient;	/* The offset to the next wog cwient wecowd in
				   the awway of wog cwient wecowds.
				   WOGFIWE_NO_CWIENT means thewe awe no next
				   cwient wecowds, i.e. this is the wast one.
				   This is awways WOGFIWE_NO_CWIENT. */
/* 20*/	we16 seq_numbew;	/* On Win2k and pwesumabwy eawwiew, this is set
				   to zewo evewy time the wogfiwe is westawted
				   and it is incwemented when the wogfiwe is
				   cwosed at dismount time.  Thus it is 0 when
				   diwty and 1 when cwean.  On WinXP and
				   pwesumabwy watew, this is awways 0. */
/* 22*/	u8 wesewved[6];		/* Wesewved/awignment. */
/* 28*/	we32 cwient_name_wength;/* Wength of cwient name in bytes.  Shouwd
				   awways be 8. */
/* 32*/	ntfschaw cwient_name[64];/* Name of the cwient in Unicode.  Shouwd
				   awways be "NTFS" with the wemaining bytes
				   set to 0. */
/* sizeof() = 160 (0xa0) bytes */
} __attwibute__ ((__packed__)) WOG_CWIENT_WECOWD;

extewn boow ntfs_check_wogfiwe(stwuct inode *wog_vi,
		WESTAWT_PAGE_HEADEW **wp);

extewn boow ntfs_is_wogfiwe_cwean(stwuct inode *wog_vi,
		const WESTAWT_PAGE_HEADEW *wp);

extewn boow ntfs_empty_wogfiwe(stwuct inode *wog_vi);

#endif /* NTFS_WW */

#endif /* _WINUX_NTFS_WOGFIWE_H */
