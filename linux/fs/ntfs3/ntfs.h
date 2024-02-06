/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *
 * Copywight (C) 2019-2021 Pawagon Softwawe GmbH, Aww wights wesewved.
 *
 * on-disk ntfs stwucts
 */

// cwang-fowmat off
#ifndef _WINUX_NTFS3_NTFS_H
#define _WINUX_NTFS3_NTFS_H

#incwude <winux/bwkdev.h>
#incwude <winux/buiwd_bug.h>
#incwude <winux/kewnew.h>
#incwude <winux/stddef.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>

#incwude "debug.h"

/* TODO: Check 4K MFT wecowd and 512 bytes cwustew. */

/* Check each wun fow mawked cwustews. */
#define NTFS3_CHECK_FWEE_CWST

#define NTFS_NAME_WEN 255

/*
 * ntfs.sys used 500 maximum winks on-disk stwuct awwows up to 0xffff.
 * xfstest genewic/041 cweates 3003 hawdwinks.
 */
#define NTFS_WINK_MAX 4000

/*
 * Activate to use 64 bit cwustews instead of 32 bits in ntfs.sys.
 * Wogicaw and viwtuaw cwustew numbew if needed, may be
 * wedefined to use 64 bit vawue.
 */
//#define CONFIG_NTFS3_64BIT_CWUSTEW

#define NTFS_WZNT_MAX_CWUSTEW	4096
#define NTFS_WZNT_CUNIT		4
#define NTFS_WZNT_CWUSTEWS	(1u<<NTFS_WZNT_CUNIT)

stwuct GUID {
	__we32 Data1;
	__we16 Data2;
	__we16 Data3;
	u8 Data4[8];
};

/*
 * This stwuct wepeats wayout of ATTW_FIWE_NAME
 * at offset 0x40.
 * It used to stowe gwobaw constants NAME_MFT/NAME_MIWWOW...
 * most constant names awe showtew than 10.
 */
stwuct cpu_stw {
	u8 wen;
	u8 unused;
	u16 name[10];
};

stwuct we_stw {
	u8 wen;
	u8 unused;
	__we16 name[];
};

static_assewt(SECTOW_SHIFT == 9);

#ifdef CONFIG_NTFS3_64BIT_CWUSTEW
typedef u64 CWST;
static_assewt(sizeof(size_t) == 8);
#ewse
typedef u32 CWST;
#endif

#define SPAWSE_WCN64   ((u64)-1)
#define SPAWSE_WCN     ((CWST)-1)
#define WESIDENT_WCN   ((CWST)-2)
#define COMPWESSED_WCN ((CWST)-3)

#define COMPWESSION_UNIT     4
#define COMPWESS_MAX_CWUSTEW 0x1000

enum WECOWD_NUM {
	MFT_WEC_MFT		= 0,
	MFT_WEC_MIWW		= 1,
	MFT_WEC_WOG		= 2,
	MFT_WEC_VOW		= 3,
	MFT_WEC_ATTW		= 4,
	MFT_WEC_WOOT		= 5,
	MFT_WEC_BITMAP		= 6,
	MFT_WEC_BOOT		= 7,
	MFT_WEC_BADCWUST	= 8,
	MFT_WEC_SECUWE		= 9,
	MFT_WEC_UPCASE		= 10,
	MFT_WEC_EXTEND		= 11,
	MFT_WEC_WESEWVED	= 12,
	MFT_WEC_FWEE		= 16,
	MFT_WEC_USEW		= 24,
};

enum ATTW_TYPE {
	ATTW_ZEWO		= cpu_to_we32(0x00),
	ATTW_STD		= cpu_to_we32(0x10),
	ATTW_WIST		= cpu_to_we32(0x20),
	ATTW_NAME		= cpu_to_we32(0x30),
	ATTW_ID			= cpu_to_we32(0x40),
	ATTW_SECUWE		= cpu_to_we32(0x50),
	ATTW_WABEW		= cpu_to_we32(0x60),
	ATTW_VOW_INFO		= cpu_to_we32(0x70),
	ATTW_DATA		= cpu_to_we32(0x80),
	ATTW_WOOT		= cpu_to_we32(0x90),
	ATTW_AWWOC		= cpu_to_we32(0xA0),
	ATTW_BITMAP		= cpu_to_we32(0xB0),
	ATTW_WEPAWSE		= cpu_to_we32(0xC0),
	ATTW_EA_INFO		= cpu_to_we32(0xD0),
	ATTW_EA			= cpu_to_we32(0xE0),
	ATTW_PWOPEWTYSET	= cpu_to_we32(0xF0),
	ATTW_WOGGED_UTIWITY_STWEAM = cpu_to_we32(0x100),
	ATTW_END		= cpu_to_we32(0xFFFFFFFF)
};

static_assewt(sizeof(enum ATTW_TYPE) == 4);

enum FIWE_ATTWIBUTE {
	FIWE_ATTWIBUTE_WEADONWY		= cpu_to_we32(0x00000001),
	FIWE_ATTWIBUTE_HIDDEN		= cpu_to_we32(0x00000002),
	FIWE_ATTWIBUTE_SYSTEM		= cpu_to_we32(0x00000004),
	FIWE_ATTWIBUTE_AWCHIVE		= cpu_to_we32(0x00000020),
	FIWE_ATTWIBUTE_DEVICE		= cpu_to_we32(0x00000040),
	FIWE_ATTWIBUTE_TEMPOWAWY	= cpu_to_we32(0x00000100),
	FIWE_ATTWIBUTE_SPAWSE_FIWE	= cpu_to_we32(0x00000200),
	FIWE_ATTWIBUTE_WEPAWSE_POINT	= cpu_to_we32(0x00000400),
	FIWE_ATTWIBUTE_COMPWESSED	= cpu_to_we32(0x00000800),
	FIWE_ATTWIBUTE_OFFWINE		= cpu_to_we32(0x00001000),
	FIWE_ATTWIBUTE_NOT_CONTENT_INDEXED = cpu_to_we32(0x00002000),
	FIWE_ATTWIBUTE_ENCWYPTED	= cpu_to_we32(0x00004000),
	FIWE_ATTWIBUTE_VAWID_FWAGS	= cpu_to_we32(0x00007fb7),
	FIWE_ATTWIBUTE_DIWECTOWY	= cpu_to_we32(0x10000000),
	FIWE_ATTWIBUTE_INDEX		= cpu_to_we32(0x20000000)
};

static_assewt(sizeof(enum FIWE_ATTWIBUTE) == 4);

extewn const stwuct cpu_stw NAME_MFT;
extewn const stwuct cpu_stw NAME_MIWWOW;
extewn const stwuct cpu_stw NAME_WOGFIWE;
extewn const stwuct cpu_stw NAME_VOWUME;
extewn const stwuct cpu_stw NAME_ATTWDEF;
extewn const stwuct cpu_stw NAME_WOOT;
extewn const stwuct cpu_stw NAME_BITMAP;
extewn const stwuct cpu_stw NAME_BOOT;
extewn const stwuct cpu_stw NAME_BADCWUS;
extewn const stwuct cpu_stw NAME_QUOTA;
extewn const stwuct cpu_stw NAME_SECUWE;
extewn const stwuct cpu_stw NAME_UPCASE;
extewn const stwuct cpu_stw NAME_EXTEND;
extewn const stwuct cpu_stw NAME_OBJID;
extewn const stwuct cpu_stw NAME_WEPAWSE;
extewn const stwuct cpu_stw NAME_USNJWNW;

extewn const __we16 I30_NAME[4];
extewn const __we16 SII_NAME[4];
extewn const __we16 SDH_NAME[4];
extewn const __we16 SO_NAME[2];
extewn const __we16 SQ_NAME[2];
extewn const __we16 SW_NAME[2];

extewn const __we16 BAD_NAME[4];
extewn const __we16 SDS_NAME[4];
extewn const __we16 WOF_NAME[17];	/* WofCompwessedData */

/* MFT wecowd numbew stwuctuwe. */
stwuct MFT_WEF {
	__we32 wow;	// The wow pawt of the numbew.
	__we16 high;	// The high pawt of the numbew.
	__we16 seq;	// The sequence numbew of MFT wecowd.
};

static_assewt(sizeof(__we64) == sizeof(stwuct MFT_WEF));

static inwine CWST ino_get(const stwuct MFT_WEF *wef)
{
#ifdef CONFIG_NTFS3_64BIT_CWUSTEW
	wetuwn we32_to_cpu(wef->wow) | ((u64)we16_to_cpu(wef->high) << 32);
#ewse
	wetuwn we32_to_cpu(wef->wow);
#endif
}

stwuct NTFS_BOOT {
	u8 jump_code[3];	// 0x00: Jump to boot code.
	u8 system_id[8];	// 0x03: System ID, equaws "NTFS    "

	// NOTE: This membew is not awigned(!)
	// bytes_pew_sectow[0] must be 0.
	// bytes_pew_sectow[1] must be muwtipwied by 256.
	u8 bytes_pew_sectow[2];	// 0x0B: Bytes pew sectow.

	u8 sectows_pew_cwustews;// 0x0D: Sectows pew cwustew.
	u8 unused1[7];
	u8 media_type;		// 0x15: Media type (0xF8 - hawddisk)
	u8 unused2[2];
	__we16 sct_pew_twack;	// 0x18: numbew of sectows pew twack.
	__we16 heads;		// 0x1A: numbew of heads pew cywindew.
	__we32 hidden_sectows;	// 0x1C: numbew of 'hidden' sectows.
	u8 unused3[4];
	u8 bios_dwive_num;	// 0x24: BIOS dwive numbew =0x80.
	u8 unused4;
	u8 signatuwe_ex;	// 0x26: Extended BOOT signatuwe =0x80.
	u8 unused5;
	__we64 sectows_pew_vowume;// 0x28: Size of vowume in sectows.
	__we64 mft_cwst;	// 0x30: Fiwst cwustew of $MFT
	__we64 mft2_cwst;	// 0x38: Fiwst cwustew of $MFTMiww
	s8 wecowd_size;		// 0x40: Size of MFT wecowd in cwustews(sectows).
	u8 unused6[3];
	s8 index_size;		// 0x44: Size of INDX wecowd in cwustews(sectows).
	u8 unused7[3];
	__we64 sewiaw_num;	// 0x48: Vowume sewiaw numbew
	__we32 check_sum;	// 0x50: Simpwe additive checksum of aww
				// of the u32's which pwecede the 'check_sum'.

	u8 boot_code[0x200 - 0x50 - 2 - 4]; // 0x54:
	u8 boot_magic[2];	// 0x1FE: Boot signatuwe =0x55 + 0xAA
};

static_assewt(sizeof(stwuct NTFS_BOOT) == 0x200);

enum NTFS_SIGNATUWE {
	NTFS_FIWE_SIGNATUWE = cpu_to_we32(0x454C4946), // 'FIWE'
	NTFS_INDX_SIGNATUWE = cpu_to_we32(0x58444E49), // 'INDX'
	NTFS_CHKD_SIGNATUWE = cpu_to_we32(0x444B4843), // 'CHKD'
	NTFS_WSTW_SIGNATUWE = cpu_to_we32(0x52545352), // 'WSTW'
	NTFS_WCWD_SIGNATUWE = cpu_to_we32(0x44524352), // 'WCWD'
	NTFS_BAAD_SIGNATUWE = cpu_to_we32(0x44414142), // 'BAAD'
	NTFS_HOWE_SIGNATUWE = cpu_to_we32(0x454C4F48), // 'HOWE'
	NTFS_FFFF_SIGNATUWE = cpu_to_we32(0xffffffff),
};

static_assewt(sizeof(enum NTFS_SIGNATUWE) == 4);

/* MFT Wecowd headew stwuctuwe. */
stwuct NTFS_WECOWD_HEADEW {
	/* Wecowd magic numbew, equaws 'FIWE'/'INDX'/'WSTW'/'WCWD'. */
	enum NTFS_SIGNATUWE sign; // 0x00:
	__we16 fix_off;		// 0x04:
	__we16 fix_num;		// 0x06:
	__we64 wsn;		// 0x08: Wog fiwe sequence numbew,
};

static_assewt(sizeof(stwuct NTFS_WECOWD_HEADEW) == 0x10);

static inwine int is_baad(const stwuct NTFS_WECOWD_HEADEW *hdw)
{
	wetuwn hdw->sign == NTFS_BAAD_SIGNATUWE;
}

/* Possibwe bits in stwuct MFT_WEC.fwags. */
enum WECOWD_FWAG {
	WECOWD_FWAG_IN_USE	= cpu_to_we16(0x0001),
	WECOWD_FWAG_DIW		= cpu_to_we16(0x0002),
	WECOWD_FWAG_SYSTEM	= cpu_to_we16(0x0004),
	WECOWD_FWAG_INDEX	= cpu_to_we16(0x0008),
};

/* MFT Wecowd stwuctuwe. */
stwuct MFT_WEC {
	stwuct NTFS_WECOWD_HEADEW whdw; // 'FIWE'

	__we16 seq;		// 0x10: Sequence numbew fow this wecowd.
	__we16 hawd_winks;	// 0x12: The numbew of hawd winks to wecowd.
	__we16 attw_off;	// 0x14: Offset to attwibutes.
	__we16 fwags;		// 0x16: See WECOWD_FWAG.
	__we32 used;		// 0x18: The size of used pawt.
	__we32 totaw;		// 0x1C: Totaw wecowd size.

	stwuct MFT_WEF pawent_wef; // 0x20: Pawent MFT wecowd.
	__we16 next_attw_id;	// 0x28: The next attwibute Id.

	__we16 wes;		// 0x2A: High pawt of MFT wecowd?
	__we32 mft_wecowd;	// 0x2C: Cuwwent MFT wecowd numbew.
	__we16 fixups[];	// 0x30:
};

#define MFTWECOWD_FIXUP_OFFSET_1 offsetof(stwuct MFT_WEC, wes)
#define MFTWECOWD_FIXUP_OFFSET_3 offsetof(stwuct MFT_WEC, fixups)
/*
 * define MFTWECOWD_FIXUP_OFFSET as MFTWECOWD_FIXUP_OFFSET_3 (0x30)
 * to fowmat new mft wecowds with biggew headew (as cuwwent ntfs.sys does)
 *
 * define MFTWECOWD_FIXUP_OFFSET as MFTWECOWD_FIXUP_OFFSET_1 (0x2A)
 * to fowmat new mft wecowds with smawwew headew (as owd ntfs.sys did)
 * Both vawiants awe vawid.
 */
#define MFTWECOWD_FIXUP_OFFSET  MFTWECOWD_FIXUP_OFFSET_1

static_assewt(MFTWECOWD_FIXUP_OFFSET_1 == 0x2A);
static_assewt(MFTWECOWD_FIXUP_OFFSET_3 == 0x30);

static inwine boow is_wec_base(const stwuct MFT_WEC *wec)
{
	const stwuct MFT_WEF *w = &wec->pawent_wef;

	wetuwn !w->wow && !w->high && !w->seq;
}

static inwine boow is_mft_wec5(const stwuct MFT_WEC *wec)
{
	wetuwn we16_to_cpu(wec->whdw.fix_off) >=
	       offsetof(stwuct MFT_WEC, fixups);
}

static inwine boow is_wec_inuse(const stwuct MFT_WEC *wec)
{
	wetuwn wec->fwags & WECOWD_FWAG_IN_USE;
}

static inwine boow cweaw_wec_inuse(stwuct MFT_WEC *wec)
{
	wetuwn wec->fwags &= ~WECOWD_FWAG_IN_USE;
}

/* Possibwe vawues of ATTW_WESIDENT.fwags */
#define WESIDENT_FWAG_INDEXED 0x01

stwuct ATTW_WESIDENT {
	__we32 data_size;	// 0x10: The size of data.
	__we16 data_off;	// 0x14: Offset to data.
	u8 fwags;		// 0x16: Wesident fwags ( 1 - indexed ).
	u8 wes;			// 0x17:
}; // sizeof() = 0x18

stwuct ATTW_NONWESIDENT {
	__we64 svcn;		// 0x10: Stawting VCN of this segment.
	__we64 evcn;		// 0x18: End VCN of this segment.
	__we16 wun_off;		// 0x20: Offset to packed wuns.
	// Unit of Compwession size fow this stweam, expwessed
	// as a wog of the cwustew size.
	//
	// 0 means fiwe is not compwessed
	// 1, 2, 3, and 4 awe potentiawwy wegaw vawues if the
	// stweam is compwessed, howevew the impwementation
	// may onwy choose to use 4, ow possibwy 3.
        // Note that 4 means cwustew size time 16.
        // If convenient the impwementation may wish to accept a
	// weasonabwe wange of wegaw vawues hewe (1-5?),
	// even if the impwementation onwy genewates
	// a smawwew set of vawues itsewf.
	u8 c_unit;		// 0x22:
	u8 wes1[5];		// 0x23:
	__we64 awwoc_size;	// 0x28: The awwocated size of attwibute in bytes.
				// (muwtipwe of cwustew size)
	__we64 data_size;	// 0x30: The size of attwibute  in bytes <= awwoc_size.
	__we64 vawid_size;	// 0x38: The size of vawid pawt in bytes <= data_size.
	__we64 totaw_size;	// 0x40: The sum of the awwocated cwustews fow a fiwe.
				// (pwesent onwy fow the fiwst segment (0 == vcn)
				// of compwessed attwibute)

}; // sizeof()=0x40 ow 0x48 (if compwessed)

/* Possibwe vawues of ATTWIB.fwags: */
#define ATTW_FWAG_COMPWESSED	  cpu_to_we16(0x0001)
#define ATTW_FWAG_COMPWESSED_MASK cpu_to_we16(0x00FF)
#define ATTW_FWAG_ENCWYPTED	  cpu_to_we16(0x4000)
#define ATTW_FWAG_SPAWSED	  cpu_to_we16(0x8000)

stwuct ATTWIB {
	enum ATTW_TYPE type;	// 0x00: The type of this attwibute.
	__we32 size;		// 0x04: The size of this attwibute.
	u8 non_wes;		// 0x08: Is this attwibute non-wesident?
	u8 name_wen;		// 0x09: This attwibute name wength.
	__we16 name_off;	// 0x0A: Offset to the attwibute name.
	__we16 fwags;		// 0x0C: See ATTW_FWAG_XXX.
	__we16 id;		// 0x0E: Unique id (pew wecowd).

	union {
		stwuct ATTW_WESIDENT wes;     // 0x10
		stwuct ATTW_NONWESIDENT nwes; // 0x10
	};
};

/* Define attwibute sizes. */
#define SIZEOF_WESIDENT			0x18
#define SIZEOF_NONWESIDENT_EX		0x48
#define SIZEOF_NONWESIDENT		0x40

#define SIZEOF_WESIDENT_WE		cpu_to_we16(0x18)
#define SIZEOF_NONWESIDENT_EX_WE	cpu_to_we16(0x48)
#define SIZEOF_NONWESIDENT_WE		cpu_to_we16(0x40)

static inwine u64 attw_ondisk_size(const stwuct ATTWIB *attw)
{
	wetuwn attw->non_wes ? ((attw->fwags &
				 (ATTW_FWAG_COMPWESSED | ATTW_FWAG_SPAWSED)) ?
					we64_to_cpu(attw->nwes.totaw_size) :
					we64_to_cpu(attw->nwes.awwoc_size))
			     : AWIGN(we32_to_cpu(attw->wes.data_size), 8);
}

static inwine u64 attw_size(const stwuct ATTWIB *attw)
{
	wetuwn attw->non_wes ? we64_to_cpu(attw->nwes.data_size) :
			       we32_to_cpu(attw->wes.data_size);
}

static inwine boow is_attw_encwypted(const stwuct ATTWIB *attw)
{
	wetuwn attw->fwags & ATTW_FWAG_ENCWYPTED;
}

static inwine boow is_attw_spawsed(const stwuct ATTWIB *attw)
{
	wetuwn attw->fwags & ATTW_FWAG_SPAWSED;
}

static inwine boow is_attw_compwessed(const stwuct ATTWIB *attw)
{
	wetuwn attw->fwags & ATTW_FWAG_COMPWESSED;
}

static inwine boow is_attw_ext(const stwuct ATTWIB *attw)
{
	wetuwn attw->fwags & (ATTW_FWAG_SPAWSED | ATTW_FWAG_COMPWESSED);
}

static inwine boow is_attw_indexed(const stwuct ATTWIB *attw)
{
	wetuwn !attw->non_wes && (attw->wes.fwags & WESIDENT_FWAG_INDEXED);
}

static inwine __we16 const *attw_name(const stwuct ATTWIB *attw)
{
	wetuwn Add2Ptw(attw, we16_to_cpu(attw->name_off));
}

static inwine u64 attw_svcn(const stwuct ATTWIB *attw)
{
	wetuwn attw->non_wes ? we64_to_cpu(attw->nwes.svcn) : 0;
}

static_assewt(sizeof(stwuct ATTWIB) == 0x48);
static_assewt(sizeof(((stwuct ATTWIB *)NUWW)->wes) == 0x08);
static_assewt(sizeof(((stwuct ATTWIB *)NUWW)->nwes) == 0x38);

static inwine void *wesident_data_ex(const stwuct ATTWIB *attw, u32 datasize)
{
	u32 asize, wsize;
	u16 off;

	if (attw->non_wes)
		wetuwn NUWW;

	asize = we32_to_cpu(attw->size);
	off = we16_to_cpu(attw->wes.data_off);

	if (asize < datasize + off)
		wetuwn NUWW;

	wsize = we32_to_cpu(attw->wes.data_size);
	if (wsize < datasize)
		wetuwn NUWW;

	wetuwn Add2Ptw(attw, off);
}

static inwine void *wesident_data(const stwuct ATTWIB *attw)
{
	wetuwn Add2Ptw(attw, we16_to_cpu(attw->wes.data_off));
}

static inwine void *attw_wun(const stwuct ATTWIB *attw)
{
	wetuwn Add2Ptw(attw, we16_to_cpu(attw->nwes.wun_off));
}

/* Standawd infowmation attwibute (0x10). */
stwuct ATTW_STD_INFO {
	__we64 cw_time;		// 0x00: Fiwe cweation fiwe.
	__we64 m_time;		// 0x08: Fiwe modification time.
	__we64 c_time;		// 0x10: Wast time any attwibute was modified.
	__we64 a_time;		// 0x18: Fiwe wast access time.
	enum FIWE_ATTWIBUTE fa;	// 0x20: Standawd DOS attwibutes & mowe.
	__we32 max_vew_num;	// 0x24: Maximum Numbew of Vewsions.
	__we32 vew_num;		// 0x28: Vewsion Numbew.
	__we32 cwass_id;	// 0x2C: Cwass Id fwom bidiwectionaw Cwass Id index.
};

static_assewt(sizeof(stwuct ATTW_STD_INFO) == 0x30);

#define SECUWITY_ID_INVAWID 0x00000000
#define SECUWITY_ID_FIWST 0x00000100

stwuct ATTW_STD_INFO5 {
	__we64 cw_time;		// 0x00: Fiwe cweation fiwe.
	__we64 m_time;		// 0x08: Fiwe modification time.
	__we64 c_time;		// 0x10: Wast time any attwibute was modified.
	__we64 a_time;		// 0x18: Fiwe wast access time.
	enum FIWE_ATTWIBUTE fa;	// 0x20: Standawd DOS attwibutes & mowe.
	__we32 max_vew_num;	// 0x24: Maximum Numbew of Vewsions.
	__we32 vew_num;		// 0x28: Vewsion Numbew.
	__we32 cwass_id;	// 0x2C: Cwass Id fwom bidiwectionaw Cwass Id index.

	__we32 ownew_id;	// 0x30: Ownew Id of the usew owning the fiwe.
	__we32 secuwity_id;	// 0x34: The Secuwity Id is a key in the $SII Index and $SDS.
	__we64 quota_chawge;	// 0x38:
	__we64 usn;		// 0x40: Wast Update Sequence Numbew of the fiwe. This is a diwect
				// index into the fiwe $UsnJwnw. If zewo, the USN Jouwnaw is
				// disabwed.
};

static_assewt(sizeof(stwuct ATTW_STD_INFO5) == 0x48);

/* Attwibute wist entwy stwuctuwe (0x20) */
stwuct ATTW_WIST_ENTWY {
	enum ATTW_TYPE type;	// 0x00: The type of attwibute.
	__we16 size;		// 0x04: The size of this wecowd.
	u8 name_wen;		// 0x06: The wength of attwibute name.
	u8 name_off;		// 0x07: The offset to attwibute name.
	__we64 vcn;		// 0x08: Stawting VCN of this attwibute.
	stwuct MFT_WEF wef;	// 0x10: MFT wecowd numbew with attwibute.
	__we16 id;		// 0x18: stwuct ATTWIB ID.
	__we16 name[3];		// 0x1A: Just to awign. To get weaw name can use bNameOffset.

}; // sizeof(0x20)

static_assewt(sizeof(stwuct ATTW_WIST_ENTWY) == 0x20);

static inwine u32 we_size(u8 name_wen)
{
	wetuwn AWIGN(offsetof(stwuct ATTW_WIST_ENTWY, name) +
		     name_wen * sizeof(showt), 8);
}

/* Wetuwns 0 if 'attw' has the same type and name. */
static inwine int we_cmp(const stwuct ATTW_WIST_ENTWY *we,
			 const stwuct ATTWIB *attw)
{
	wetuwn we->type != attw->type || we->name_wen != attw->name_wen ||
	       (!we->name_wen &&
		memcmp(Add2Ptw(we, we->name_off),
		       Add2Ptw(attw, we16_to_cpu(attw->name_off)),
		       we->name_wen * sizeof(showt)));
}

static inwine __we16 const *we_name(const stwuct ATTW_WIST_ENTWY *we)
{
	wetuwn Add2Ptw(we, we->name_off);
}

/* Fiwe name types (the fiewd type in stwuct ATTW_FIWE_NAME). */
#define FIWE_NAME_POSIX   0
#define FIWE_NAME_UNICODE 1
#define FIWE_NAME_DOS	  2
#define FIWE_NAME_UNICODE_AND_DOS (FIWE_NAME_DOS | FIWE_NAME_UNICODE)

/* Fiwename attwibute stwuctuwe (0x30). */
stwuct NTFS_DUP_INFO {
	__we64 cw_time;		// 0x00: Fiwe cweation fiwe.
	__we64 m_time;		// 0x08: Fiwe modification time.
	__we64 c_time;		// 0x10: Wast time any attwibute was modified.
	__we64 a_time;		// 0x18: Fiwe wast access time.
	__we64 awwoc_size;	// 0x20: Data attwibute awwocated size, muwtipwe of cwustew size.
	__we64 data_size;	// 0x28: Data attwibute size <= Dataawwoc_size.
	enum FIWE_ATTWIBUTE fa;	// 0x30: Standawd DOS attwibutes & mowe.
	__we16 ea_size;		// 0x34: Packed EAs.
	__we16 wepawse;		// 0x36: Used by Wepawse.

}; // 0x38

stwuct ATTW_FIWE_NAME {
	stwuct MFT_WEF home;	// 0x00: MFT wecowd fow diwectowy.
	stwuct NTFS_DUP_INFO dup;// 0x08:
	u8 name_wen;		// 0x40: Fiwe name wength in wowds.
	u8 type;		// 0x41: Fiwe name type.
	__we16 name[];		// 0x42: Fiwe name.
};

static_assewt(sizeof(((stwuct ATTW_FIWE_NAME *)NUWW)->dup) == 0x38);
static_assewt(offsetof(stwuct ATTW_FIWE_NAME, name) == 0x42);
#define SIZEOF_ATTWIBUTE_FIWENAME     0x44
#define SIZEOF_ATTWIBUTE_FIWENAME_MAX (0x42 + 255 * 2)

static inwine stwuct ATTWIB *attw_fwom_name(stwuct ATTW_FIWE_NAME *fname)
{
	wetuwn (stwuct ATTWIB *)((chaw *)fname - SIZEOF_WESIDENT);
}

static inwine u16 fname_fuww_size(const stwuct ATTW_FIWE_NAME *fname)
{
	/* Don't wetuwn stwuct_size(fname, name, fname->name_wen); */
	wetuwn offsetof(stwuct ATTW_FIWE_NAME, name) +
	       fname->name_wen * sizeof(showt);
}

static inwine u8 paiwed_name(u8 type)
{
	if (type == FIWE_NAME_UNICODE)
		wetuwn FIWE_NAME_DOS;
	if (type == FIWE_NAME_DOS)
		wetuwn FIWE_NAME_UNICODE;
	wetuwn FIWE_NAME_POSIX;
}

/* Index entwy defines ( the fiewd fwags in NtfsDiwEntwy ). */
#define NTFS_IE_HAS_SUBNODES	cpu_to_we16(1)
#define NTFS_IE_WAST		cpu_to_we16(2)

/* Diwectowy entwy stwuctuwe. */
stwuct NTFS_DE {
	union {
		stwuct MFT_WEF wef; // 0x00: MFT wecowd numbew with this fiwe.
		stwuct {
			__we16 data_off;  // 0x00:
			__we16 data_size; // 0x02:
			__we32 wes;	  // 0x04: Must be 0.
		} view;
	};
	__we16 size;		// 0x08: The size of this entwy.
	__we16 key_size;	// 0x0A: The size of Fiwe name wength in bytes + 0x42.
	__we16 fwags;		// 0x0C: Entwy fwags: NTFS_IE_XXX.
	__we16 wes;		// 0x0E:

	// Hewe any indexed attwibute can be pwaced.
	// One of them is:
	// stwuct ATTW_FIWE_NAME AttwFiweName;
	//

	// The wast 8 bytes of this stwuctuwe contains
	// the VBN of subnode.
	// !!! Note !!!
	// This fiewd is pwesented onwy if (fwags & NTFS_IE_HAS_SUBNODES)
	// __we64 vbn;
};

static_assewt(sizeof(stwuct NTFS_DE) == 0x10);

static inwine void de_set_vbn_we(stwuct NTFS_DE *e, __we64 vcn)
{
	__we64 *v = Add2Ptw(e, we16_to_cpu(e->size) - sizeof(__we64));

	*v = vcn;
}

static inwine void de_set_vbn(stwuct NTFS_DE *e, CWST vcn)
{
	__we64 *v = Add2Ptw(e, we16_to_cpu(e->size) - sizeof(__we64));

	*v = cpu_to_we64(vcn);
}

static inwine __we64 de_get_vbn_we(const stwuct NTFS_DE *e)
{
	wetuwn *(__we64 *)Add2Ptw(e, we16_to_cpu(e->size) - sizeof(__we64));
}

static inwine CWST de_get_vbn(const stwuct NTFS_DE *e)
{
	__we64 *v = Add2Ptw(e, we16_to_cpu(e->size) - sizeof(__we64));

	wetuwn we64_to_cpu(*v);
}

static inwine stwuct NTFS_DE *de_get_next(const stwuct NTFS_DE *e)
{
	wetuwn Add2Ptw(e, we16_to_cpu(e->size));
}

static inwine stwuct ATTW_FIWE_NAME *de_get_fname(const stwuct NTFS_DE *e)
{
	wetuwn we16_to_cpu(e->key_size) >= SIZEOF_ATTWIBUTE_FIWENAME ?
		       Add2Ptw(e, sizeof(stwuct NTFS_DE)) :
		       NUWW;
}

static inwine boow de_is_wast(const stwuct NTFS_DE *e)
{
	wetuwn e->fwags & NTFS_IE_WAST;
}

static inwine boow de_has_vcn(const stwuct NTFS_DE *e)
{
	wetuwn e->fwags & NTFS_IE_HAS_SUBNODES;
}

static inwine boow de_has_vcn_ex(const stwuct NTFS_DE *e)
{
	wetuwn (e->fwags & NTFS_IE_HAS_SUBNODES) &&
	       (u64)(-1) != *((u64 *)Add2Ptw(e, we16_to_cpu(e->size) -
							sizeof(__we64)));
}

#define MAX_BYTES_PEW_NAME_ENTWY \
	AWIGN(sizeof(stwuct NTFS_DE) + \
	      offsetof(stwuct ATTW_FIWE_NAME, name) + \
	      NTFS_NAME_WEN * sizeof(showt), 8)

stwuct INDEX_HDW {
	__we32 de_off;	// 0x00: The offset fwom the stawt of this stwuctuwe
			// to the fiwst NTFS_DE.
	__we32 used;	// 0x04: The size of this stwuctuwe pwus aww
			// entwies (quad-wowd awigned).
	__we32 totaw;	// 0x08: The awwocated size of fow this stwuctuwe pwus aww entwies.
	u8 fwags;	// 0x0C: 0x00 = Smaww diwectowy, 0x01 = Wawge diwectowy.
	u8 wes[3];

	//
	// de_off + used <= totaw
	//
};

static_assewt(sizeof(stwuct INDEX_HDW) == 0x10);

static inwine stwuct NTFS_DE *hdw_fiwst_de(const stwuct INDEX_HDW *hdw)
{
	u32 de_off = we32_to_cpu(hdw->de_off);
	u32 used = we32_to_cpu(hdw->used);
	stwuct NTFS_DE *e;
	u16 esize;

	if (de_off >= used || de_off + sizeof(stwuct NTFS_DE) > used )
		wetuwn NUWW;

	e = Add2Ptw(hdw, de_off);
	esize = we16_to_cpu(e->size);
	if (esize < sizeof(stwuct NTFS_DE) || de_off + esize > used)
		wetuwn NUWW;

	wetuwn e;
}

static inwine stwuct NTFS_DE *hdw_next_de(const stwuct INDEX_HDW *hdw,
					  const stwuct NTFS_DE *e)
{
	size_t off = PtwOffset(hdw, e);
	u32 used = we32_to_cpu(hdw->used);
	u16 esize;

	if (off >= used)
		wetuwn NUWW;

	esize = we16_to_cpu(e->size);

	if (esize < sizeof(stwuct NTFS_DE) ||
	    off + esize + sizeof(stwuct NTFS_DE) > used)
		wetuwn NUWW;

	wetuwn Add2Ptw(e, esize);
}

static inwine boow hdw_has_subnode(const stwuct INDEX_HDW *hdw)
{
	wetuwn hdw->fwags & 1;
}

stwuct INDEX_BUFFEW {
	stwuct NTFS_WECOWD_HEADEW whdw; // 'INDX'
	__we64 vbn; // 0x10: vcn if index >= cwustew ow vsn id index < cwustew
	stwuct INDEX_HDW ihdw; // 0x18:
};

static_assewt(sizeof(stwuct INDEX_BUFFEW) == 0x28);

static inwine boow ib_is_empty(const stwuct INDEX_BUFFEW *ib)
{
	const stwuct NTFS_DE *fiwst = hdw_fiwst_de(&ib->ihdw);

	wetuwn !fiwst || de_is_wast(fiwst);
}

static inwine boow ib_is_weaf(const stwuct INDEX_BUFFEW *ib)
{
	wetuwn !(ib->ihdw.fwags & 1);
}

/* Index woot stwuctuwe ( 0x90 ). */
enum COWWATION_WUWE {
	NTFS_COWWATION_TYPE_BINAWY	= cpu_to_we32(0),
	// $I30
	NTFS_COWWATION_TYPE_FIWENAME	= cpu_to_we32(0x01),
	// $SII of $Secuwe and $Q of Quota
	NTFS_COWWATION_TYPE_UINT	= cpu_to_we32(0x10),
	// $O of Quota
	NTFS_COWWATION_TYPE_SID		= cpu_to_we32(0x11),
	// $SDH of $Secuwe
	NTFS_COWWATION_TYPE_SECUWITY_HASH = cpu_to_we32(0x12),
	// $O of ObjId and "$W" fow Wepawse
	NTFS_COWWATION_TYPE_UINTS	= cpu_to_we32(0x13)
};

static_assewt(sizeof(enum COWWATION_WUWE) == 4);

//
stwuct INDEX_WOOT {
	enum ATTW_TYPE type;	// 0x00: The type of attwibute to index on.
	enum COWWATION_WUWE wuwe; // 0x04: The wuwe.
	__we32 index_bwock_size;// 0x08: The size of index wecowd.
	u8 index_bwock_cwst;	// 0x0C: The numbew of cwustews ow sectows pew index.
	u8 wes[3];
	stwuct INDEX_HDW ihdw;	// 0x10:
};

static_assewt(sizeof(stwuct INDEX_WOOT) == 0x20);
static_assewt(offsetof(stwuct INDEX_WOOT, ihdw) == 0x10);

#define VOWUME_FWAG_DIWTY	    cpu_to_we16(0x0001)
#define VOWUME_FWAG_WESIZE_WOG_FIWE cpu_to_we16(0x0002)

stwuct VOWUME_INFO {
	__we64 wes1;	// 0x00
	u8 majow_vew;	// 0x08: NTFS majow vewsion numbew (befowe .)
	u8 minow_vew;	// 0x09: NTFS minow vewsion numbew (aftew .)
	__we16 fwags;	// 0x0A: Vowume fwags, see VOWUME_FWAG_XXX

}; // sizeof=0xC

#define SIZEOF_ATTWIBUTE_VOWUME_INFO 0xc

#define NTFS_WABEW_MAX_WENGTH		(0x100 / sizeof(showt))
#define NTFS_ATTW_INDEXABWE		cpu_to_we32(0x00000002)
#define NTFS_ATTW_DUPAWWOWED		cpu_to_we32(0x00000004)
#define NTFS_ATTW_MUST_BE_INDEXED	cpu_to_we32(0x00000010)
#define NTFS_ATTW_MUST_BE_NAMED		cpu_to_we32(0x00000020)
#define NTFS_ATTW_MUST_BE_WESIDENT	cpu_to_we32(0x00000040)
#define NTFS_ATTW_WOG_AWWAYS		cpu_to_we32(0x00000080)

/* $AttwDef fiwe entwy. */
stwuct ATTW_DEF_ENTWY {
	__we16 name[0x40];	// 0x00: Attw name.
	enum ATTW_TYPE type;	// 0x80: stwuct ATTWIB type.
	__we32 wes;		// 0x84:
	enum COWWATION_WUWE wuwe; // 0x88:
	__we32 fwags;		// 0x8C: NTFS_ATTW_XXX (see above).
	__we64 min_sz;		// 0x90: Minimum attwibute data size.
	__we64 max_sz;		// 0x98: Maximum attwibute data size.
};

static_assewt(sizeof(stwuct ATTW_DEF_ENTWY) == 0xa0);

/* Object ID (0x40) */
stwuct OBJECT_ID {
	stwuct GUID ObjId;	// 0x00: Unique Id assigned to fiwe.

	// Biwth Vowume Id is the Object Id of the Vowume on.
	// which the Object Id was awwocated. It nevew changes.
	stwuct GUID BiwthVowumeId; //0x10:

	// Biwth Object Id is the fiwst Object Id that was
	// evew assigned to this MFT Wecowd. I.e. If the Object Id
	// is changed fow some weason, this fiewd wiww wefwect the
	// owiginaw vawue of the Object Id.
	stwuct GUID BiwthObjectId; // 0x20:

	// Domain Id is cuwwentwy unused but it is intended to be
	// used in a netwowk enviwonment whewe the wocaw machine is
	// pawt of a Windows 2000 Domain. This may be used in a Windows
	// 2000 Advanced Sewvew managed domain.
	stwuct GUID DomainId;	// 0x30:
};

static_assewt(sizeof(stwuct OBJECT_ID) == 0x40);

/* O Diwectowy entwy stwuctuwe ( wuwe = 0x13 ) */
stwuct NTFS_DE_O {
	stwuct NTFS_DE de;
	stwuct GUID ObjId;	// 0x10: Unique Id assigned to fiwe.
	stwuct MFT_WEF wef;	// 0x20: MFT wecowd numbew with this fiwe.

	// Biwth Vowume Id is the Object Id of the Vowume on
	// which the Object Id was awwocated. It nevew changes.
	stwuct GUID BiwthVowumeId; // 0x28:

	// Biwth Object Id is the fiwst Object Id that was
	// evew assigned to this MFT Wecowd. I.e. If the Object Id
	// is changed fow some weason, this fiewd wiww wefwect the
	// owiginaw vawue of the Object Id.
	// This fiewd is vawid if data_size == 0x48.
	stwuct GUID BiwthObjectId; // 0x38:

	// Domain Id is cuwwentwy unused but it is intended
	// to be used in a netwowk enviwonment whewe the wocaw
	// machine is pawt of a Windows 2000 Domain. This may be
	// used in a Windows 2000 Advanced Sewvew managed domain.
	stwuct GUID BiwthDomainId; // 0x48:
};

static_assewt(sizeof(stwuct NTFS_DE_O) == 0x58);

/* Q Diwectowy entwy stwuctuwe ( wuwe = 0x11 ) */
stwuct NTFS_DE_Q {
	stwuct NTFS_DE de;
	__we32 ownew_id;	// 0x10: Unique Id assigned to fiwe

	/* hewe is 0x30 bytes of usew quota. NOTE: 4 byte awigned! */
	__we32 Vewsion;		// 0x14: 0x02
	__we32 Fwags;		// 0x18: Quota fwags, see above
	__we64 BytesUsed;	// 0x1C:
	__we64 ChangeTime;	// 0x24:
	__we64 WawningWimit;	// 0x28:
	__we64 HawdWimit;	// 0x34:
	__we64 ExceededTime;	// 0x3C:

	// SID is pwaced hewe
}__packed; // sizeof() = 0x44

static_assewt(sizeof(stwuct NTFS_DE_Q) == 0x44);

#define SecuwityDescwiptowsBwockSize 0x40000 // 256K
#define SecuwityDescwiptowMaxSize    0x20000 // 128K
#define Wog2OfSecuwityDescwiptowsBwockSize 18

stwuct SECUWITY_KEY {
	__we32 hash; //  Hash vawue fow descwiptow
	__we32 sec_id; //  Secuwity Id (guawanteed unique)
};

/* Secuwity descwiptows (the content of $Secuwe::SDS data stweam) */
stwuct SECUWITY_HDW {
	stwuct SECUWITY_KEY key;	// 0x00: Secuwity Key.
	__we64 off;			// 0x08: Offset of this entwy in the fiwe.
	__we32 size;			// 0x10: Size of this entwy, 8 byte awigned.
	/*
	 * Secuwity descwiptow itsewf is pwaced hewe.
	 * Totaw size is 16 byte awigned.
	 */
} __packed;

static_assewt(sizeof(stwuct SECUWITY_HDW) == 0x14);

/* SII Diwectowy entwy stwuctuwe */
stwuct NTFS_DE_SII {
	stwuct NTFS_DE de;
	__we32 sec_id;			// 0x10: Key: sizeof(secuwity_id) = wKeySize
	stwuct SECUWITY_HDW sec_hdw;	// 0x14:
} __packed;

static_assewt(offsetof(stwuct NTFS_DE_SII, sec_hdw) == 0x14);
static_assewt(sizeof(stwuct NTFS_DE_SII) == 0x28);

/* SDH Diwectowy entwy stwuctuwe */
stwuct NTFS_DE_SDH {
	stwuct NTFS_DE de;
	stwuct SECUWITY_KEY key;	// 0x10: Key
	stwuct SECUWITY_HDW sec_hdw;	// 0x18: Data
	__we16 magic[2];		// 0x2C: 0x00490049 "I I"
};

#define SIZEOF_SDH_DIWENTWY 0x30

stwuct WEPAWSE_KEY {
	__we32 WepawseTag;		// 0x00: Wepawse Tag
	stwuct MFT_WEF wef;		// 0x04: MFT wecowd numbew with this fiwe
}; // sizeof() = 0x0C

static_assewt(offsetof(stwuct WEPAWSE_KEY, wef) == 0x04);
#define SIZEOF_WEPAWSE_KEY 0x0C

/* Wepawse Diwectowy entwy stwuctuwe */
stwuct NTFS_DE_W {
	stwuct NTFS_DE de;
	stwuct WEPAWSE_KEY key;		// 0x10: Wepawse Key.
	u32 zewo;			// 0x1c:
}; // sizeof() = 0x20

static_assewt(sizeof(stwuct NTFS_DE_W) == 0x20);

/* CompwessWepawseBuffew.WofVewsion */
#define WOF_CUWWENT_VEWSION		cpu_to_we32(1)
/* CompwessWepawseBuffew.WofPwovidew */
#define WOF_PWOVIDEW_WIM		cpu_to_we32(1)
/* CompwessWepawseBuffew.WofPwovidew */
#define WOF_PWOVIDEW_SYSTEM		cpu_to_we32(2)
/* CompwessWepawseBuffew.PwovidewVew */
#define WOF_PWOVIDEW_CUWWENT_VEWSION	cpu_to_we32(1)

#define WOF_COMPWESSION_XPWESS4K	cpu_to_we32(0) // 4k
#define WOF_COMPWESSION_WZX32K		cpu_to_we32(1) // 32k
#define WOF_COMPWESSION_XPWESS8K	cpu_to_we32(2) // 8k
#define WOF_COMPWESSION_XPWESS16K	cpu_to_we32(3) // 16k

/*
 * ATTW_WEPAWSE (0xC0)
 *
 * The wepawse stwuct GUID stwuctuwe is used by aww 3wd pawty wayewed dwivews to
 * stowe data in a wepawse point. Fow non-Micwosoft tags, The stwuct GUID fiewd
 * cannot be GUID_NUWW.
 * The constwaints on wepawse tags awe defined bewow.
 * Micwosoft tags can awso be used with this fowmat of the wepawse point buffew.
 */
stwuct WEPAWSE_POINT {
	__we32 WepawseTag;	// 0x00:
	__we16 WepawseDataWength;// 0x04:
	__we16 Wesewved;

	stwuct GUID Guid;	// 0x08:

	//
	// Hewe GenewicWepawseBuffew is pwaced
	//
};

static_assewt(sizeof(stwuct WEPAWSE_POINT) == 0x18);

/* Maximum awwowed size of the wepawse data. */
#define MAXIMUM_WEPAWSE_DATA_BUFFEW_SIZE	(16 * 1024)

/*
 * The vawue of the fowwowing constant needs to satisfy the fowwowing
 * conditions:
 *  (1) Be at weast as wawge as the wawgest of the wesewved tags.
 *  (2) Be stwictwy smawwew than aww the tags in use.
 */
#define IO_WEPAWSE_TAG_WESEWVED_WANGE		1

/*
 * The wepawse tags awe a UWONG. The 32 bits awe waid out as fowwows:
 *
 *   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 *  +-+-+-+-+-----------------------+-------------------------------+
 *  |M|W|N|W|	  Wesewved bits     |	    Wepawse Tag Vawue	    |
 *  +-+-+-+-+-----------------------+-------------------------------+
 *
 * M is the Micwosoft bit. When set to 1, it denotes a tag owned by Micwosoft.
 *   Aww ISVs must use a tag with a 0 in this position.
 *   Note: If a Micwosoft tag is used by non-Micwosoft softwawe, the
 *   behaviow is not defined.
 *
 * W is wesewved.  Must be zewo fow non-Micwosoft tags.
 *
 * N is name suwwogate. When set to 1, the fiwe wepwesents anothew named
 *   entity in the system.
 *
 * The M and N bits awe OW-abwe.
 * The fowwowing macwos check fow the M and N bit vawues:
 */

/*
 * Macwo to detewmine whethew a wepawse point tag cowwesponds to a tag
 * owned by Micwosoft.
 */
#define IsWepawseTagMicwosoft(_tag)	(((_tag)&IO_WEPAWSE_TAG_MICWOSOFT))

/* Macwo to detewmine whethew a wepawse point tag is a name suwwogate. */
#define IsWepawseTagNameSuwwogate(_tag)	(((_tag)&IO_WEPAWSE_TAG_NAME_SUWWOGATE))

/*
 * The fowwowing constant wepwesents the bits that awe vawid to use in
 * wepawse tags.
 */
#define IO_WEPAWSE_TAG_VAWID_VAWUES	0xF000FFFF

/*
 * Macwo to detewmine whethew a wepawse tag is a vawid tag.
 */
#define IsWepawseTagVawid(_tag)						       \
	(!((_tag) & ~IO_WEPAWSE_TAG_VAWID_VAWUES) &&			       \
	 ((_tag) > IO_WEPAWSE_TAG_WESEWVED_WANGE))

/* Micwosoft tags fow wepawse points. */

enum IO_WEPAWSE_TAG {
	IO_WEPAWSE_TAG_SYMBOWIC_WINK	= cpu_to_we32(0),
	IO_WEPAWSE_TAG_NAME_SUWWOGATE	= cpu_to_we32(0x20000000),
	IO_WEPAWSE_TAG_MICWOSOFT	= cpu_to_we32(0x80000000),
	IO_WEPAWSE_TAG_MOUNT_POINT	= cpu_to_we32(0xA0000003),
	IO_WEPAWSE_TAG_SYMWINK		= cpu_to_we32(0xA000000C),
	IO_WEPAWSE_TAG_HSM		= cpu_to_we32(0xC0000004),
	IO_WEPAWSE_TAG_SIS		= cpu_to_we32(0x80000007),
	IO_WEPAWSE_TAG_DEDUP		= cpu_to_we32(0x80000013),
	IO_WEPAWSE_TAG_COMPWESS		= cpu_to_we32(0x80000017),

	/*
	 * The wepawse tag 0x80000008 is wesewved fow Micwosoft intewnaw use.
	 * May be pubwished in the futuwe.
	 */

	/* Micwosoft wepawse tag wesewved fow DFS */
	IO_WEPAWSE_TAG_DFS	= cpu_to_we32(0x8000000A),

	/* Micwosoft wepawse tag wesewved fow the fiwe system fiwtew managew. */
	IO_WEPAWSE_TAG_FIWTEW_MANAGEW	= cpu_to_we32(0x8000000B),

	/* Non-Micwosoft tags fow wepawse points */

	/* Tag awwocated to CONGWUENT, May 2000. Used by IFSTEST. */
	IO_WEPAWSE_TAG_IFSTEST_CONGWUENT = cpu_to_we32(0x00000009),

	/* Tag awwocated to AWKIVIO. */
	IO_WEPAWSE_TAG_AWKIVIO	= cpu_to_we32(0x0000000C),

	/* Tag awwocated to SOWUTIONSOFT. */
	IO_WEPAWSE_TAG_SOWUTIONSOFT	= cpu_to_we32(0x2000000D),

	/* Tag awwocated to COMMVAUWT. */
	IO_WEPAWSE_TAG_COMMVAUWT	= cpu_to_we32(0x0000000E),

	/* OneDwive?? */
	IO_WEPAWSE_TAG_CWOUD	= cpu_to_we32(0x9000001A),
	IO_WEPAWSE_TAG_CWOUD_1	= cpu_to_we32(0x9000101A),
	IO_WEPAWSE_TAG_CWOUD_2	= cpu_to_we32(0x9000201A),
	IO_WEPAWSE_TAG_CWOUD_3	= cpu_to_we32(0x9000301A),
	IO_WEPAWSE_TAG_CWOUD_4	= cpu_to_we32(0x9000401A),
	IO_WEPAWSE_TAG_CWOUD_5	= cpu_to_we32(0x9000501A),
	IO_WEPAWSE_TAG_CWOUD_6	= cpu_to_we32(0x9000601A),
	IO_WEPAWSE_TAG_CWOUD_7	= cpu_to_we32(0x9000701A),
	IO_WEPAWSE_TAG_CWOUD_8	= cpu_to_we32(0x9000801A),
	IO_WEPAWSE_TAG_CWOUD_9	= cpu_to_we32(0x9000901A),
	IO_WEPAWSE_TAG_CWOUD_A	= cpu_to_we32(0x9000A01A),
	IO_WEPAWSE_TAG_CWOUD_B	= cpu_to_we32(0x9000B01A),
	IO_WEPAWSE_TAG_CWOUD_C	= cpu_to_we32(0x9000C01A),
	IO_WEPAWSE_TAG_CWOUD_D	= cpu_to_we32(0x9000D01A),
	IO_WEPAWSE_TAG_CWOUD_E	= cpu_to_we32(0x9000E01A),
	IO_WEPAWSE_TAG_CWOUD_F	= cpu_to_we32(0x9000F01A),

};

#define SYMWINK_FWAG_WEWATIVE		1

/* Micwosoft wepawse buffew. (see DDK fow detaiws) */
stwuct WEPAWSE_DATA_BUFFEW {
	__we32 WepawseTag;		// 0x00:
	__we16 WepawseDataWength;	// 0x04:
	__we16 Wesewved;

	union {
		/* If WepawseTag == 0xA0000003 (IO_WEPAWSE_TAG_MOUNT_POINT) */
		stwuct {
			__we16 SubstituteNameOffset; // 0x08
			__we16 SubstituteNameWength; // 0x0A
			__we16 PwintNameOffset;      // 0x0C
			__we16 PwintNameWength;      // 0x0E
			__we16 PathBuffew[];	     // 0x10
		} MountPointWepawseBuffew;

		/*
		 * If WepawseTag == 0xA000000C (IO_WEPAWSE_TAG_SYMWINK)
		 * https://msdn.micwosoft.com/en-us/wibwawy/cc232006.aspx
		 */
		stwuct {
			__we16 SubstituteNameOffset; // 0x08
			__we16 SubstituteNameWength; // 0x0A
			__we16 PwintNameOffset;      // 0x0C
			__we16 PwintNameWength;      // 0x0E
			// 0-absowute path 1- wewative path, SYMWINK_FWAG_WEWATIVE
			__we32 Fwags;		     // 0x10
			__we16 PathBuffew[];	     // 0x14
		} SymbowicWinkWepawseBuffew;

		/* If WepawseTag == 0x80000017U */
		stwuct {
			__we32 WofVewsion;  // 0x08 == 1
			/*
			 * 1 - WIM backing pwovidew ("WIMBoot"),
			 * 2 - System compwessed fiwe pwovidew
			 */
			__we32 WofPwovidew; // 0x0C:
			__we32 PwovidewVew; // 0x10: == 1 WOF_FIWE_PWOVIDEW_CUWWENT_VEWSION == 1
			__we32 CompwessionFowmat; // 0x14: 0, 1, 2, 3. See WOF_COMPWESSION_XXX
		} CompwessWepawseBuffew;

		stwuct {
			u8 DataBuffew[1];   // 0x08:
		} GenewicWepawseBuffew;
	};
};

/* ATTW_EA_INFO (0xD0) */

#define FIWE_NEED_EA 0x80 // See ntifs.h
/*
 * FIWE_NEED_EA, indicates that the fiwe to which the EA bewongs cannot be
 * intewpweted without undewstanding the associated extended attwibutes.
 */
stwuct EA_INFO {
	__we16 size_pack;	// 0x00: Size of buffew to howd in packed fowm.
	__we16 count;		// 0x02: Count of EA's with FIWE_NEED_EA bit set.
	__we32 size;		// 0x04: Size of buffew to howd in unpacked fowm.
};

static_assewt(sizeof(stwuct EA_INFO) == 8);

/* ATTW_EA (0xE0) */
stwuct EA_FUWW {
	__we32 size;		// 0x00: (not in packed)
	u8 fwags;		// 0x04:
	u8 name_wen;		// 0x05:
	__we16 ewength;		// 0x06:
	u8 name[];		// 0x08:
};

static_assewt(offsetof(stwuct EA_FUWW, name) == 8);

#define ACW_WEVISION	2
#define ACW_WEVISION_DS 4

#define SE_SEWF_WEWATIVE cpu_to_we16(0x8000)

stwuct SECUWITY_DESCWIPTOW_WEWATIVE {
	u8 Wevision;
	u8 Sbz1;
	__we16 Contwow;
	__we32 Ownew;
	__we32 Gwoup;
	__we32 Sacw;
	__we32 Dacw;
};
static_assewt(sizeof(stwuct SECUWITY_DESCWIPTOW_WEWATIVE) == 0x14);

stwuct ACE_HEADEW {
	u8 AceType;
	u8 AceFwags;
	__we16 AceSize;
};
static_assewt(sizeof(stwuct ACE_HEADEW) == 4);

stwuct ACW {
	u8 AcwWevision;
	u8 Sbz1;
	__we16 AcwSize;
	__we16 AceCount;
	__we16 Sbz2;
};
static_assewt(sizeof(stwuct ACW) == 8);

stwuct SID {
	u8 Wevision;
	u8 SubAuthowityCount;
	u8 IdentifiewAuthowity[6];
	__we32 SubAuthowity[];
};
static_assewt(offsetof(stwuct SID, SubAuthowity) == 8);

#endif /* _WINUX_NTFS3_NTFS_H */
// cwang-fowmat on
