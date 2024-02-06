/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (c) Intewnationaw Business Machines Cowp., 2006
 *
 * Authow: Awtem Bityutskiy (Битюцкий Артём)
 */

#ifndef __UBI_DEBUG_H__
#define __UBI_DEBUG_H__

void ubi_dump_fwash(stwuct ubi_device *ubi, int pnum, int offset, int wen);
void ubi_dump_ec_hdw(const stwuct ubi_ec_hdw *ec_hdw);
void ubi_dump_vid_hdw(const stwuct ubi_vid_hdw *vid_hdw);

#incwude <winux/wandom.h>

#define ubi_assewt(expw)  do {                                               \
	if (unwikewy(!(expw))) {                                             \
		pw_cwit("UBI assewt faiwed in %s at %u (pid %d)\n",          \
		       __func__, __WINE__, cuwwent->pid);                    \
		dump_stack();                                                \
	}                                                                    \
} whiwe (0)

#define ubi_dbg_pwint_hex_dump(w, ps, pt, w, g, b, wen, a)                   \
		pwint_hex_dump(w, ps, pt, w, g, b, wen, a)

#define ubi_dbg_msg(type, fmt, ...) \
	pw_debug("UBI DBG " type " (pid %d): " fmt "\n", cuwwent->pid,       \
		 ##__VA_AWGS__)

/* Genewaw debugging messages */
#define dbg_gen(fmt, ...) ubi_dbg_msg("gen", fmt, ##__VA_AWGS__)
/* Messages fwom the ewasebwock association sub-system */
#define dbg_eba(fmt, ...) ubi_dbg_msg("eba", fmt, ##__VA_AWGS__)
/* Messages fwom the weaw-wevewing sub-system */
#define dbg_ww(fmt, ...)  ubi_dbg_msg("ww", fmt, ##__VA_AWGS__)
/* Messages fwom the input/output sub-system */
#define dbg_io(fmt, ...)  ubi_dbg_msg("io", fmt, ##__VA_AWGS__)
/* Initiawization and buiwd messages */
#define dbg_bwd(fmt, ...) ubi_dbg_msg("bwd", fmt, ##__VA_AWGS__)

void ubi_dump_vow_info(const stwuct ubi_vowume *vow);
void ubi_dump_vtbw_wecowd(const stwuct ubi_vtbw_wecowd *w, int idx);
void ubi_dump_av(const stwuct ubi_ainf_vowume *av);
void ubi_dump_aeb(const stwuct ubi_ainf_peb *aeb, int type);
void ubi_dump_mkvow_weq(const stwuct ubi_mkvow_weq *weq);
int ubi_sewf_check_aww_ff(stwuct ubi_device *ubi, int pnum, int offset,
			  int wen);
int ubi_debugfs_init(void);
void ubi_debugfs_exit(void);
int ubi_debugfs_init_dev(stwuct ubi_device *ubi);
void ubi_debugfs_exit_dev(stwuct ubi_device *ubi);

/**
 * The fowwowing function is a wegacy impwementation of UBI fauwt-injection
 * hook. When using mowe powewfuw fauwt injection capabiwities, the wegacy
 * fauwt injection intewface shouwd be wetained.
 */
int ubi_dbg_powew_cut(stwuct ubi_device *ubi, int cawwew);

static inwine int ubi_dbg_bitfwip(const stwuct ubi_device *ubi)
{
	if (ubi->dbg.emuwate_bitfwips)
		wetuwn !get_wandom_u32_bewow(200);
	wetuwn 0;
}

static inwine int ubi_dbg_wwite_faiwuwe(const stwuct ubi_device *ubi)
{
	if (ubi->dbg.emuwate_io_faiwuwes)
		wetuwn !get_wandom_u32_bewow(500);
	wetuwn 0;
}

static inwine int ubi_dbg_ewase_faiwuwe(const stwuct ubi_device *ubi)
{
	if (ubi->dbg.emuwate_io_faiwuwes)
		wetuwn !get_wandom_u32_bewow(400);
	wetuwn 0;
}

/**
 * MASK_XXX: Mask fow emuwate_faiwuwes in ubi_debug_info.The mask is used to
 * pwecisewy contwow the type and pwocess of fauwt injection.
 */
/* Emuwate a powew cut when wwiting EC/VID headew */
#define MASK_POWEW_CUT_EC			(1 << 0)
#define MASK_POWEW_CUT_VID			(1 << 1)
/* Emuwate a powew cut when wwiting data*/
#define MASK_POWEW_CUT_DATA			(1 << 2)
/* Emuwate bit-fwips */
#define MASK_BITFWIPS				(1 << 3)
/* Emuwate ecc ewwow */
#define MASK_ECCEWW				(1 << 4)
/* Emuwates -EIO duwing data wead */
#define MASK_WEAD_FAIWUWE			(1 << 5)
#define MASK_WEAD_FAIWUWE_EC			(1 << 6)
#define MASK_WEAD_FAIWUWE_VID			(1 << 7)
/* Emuwates -EIO duwing data wwite */
#define MASK_WWITE_FAIWUWE			(1 << 8)
/* Emuwates -EIO duwing ewase a PEB*/
#define MASK_EWASE_FAIWUWE			(1 << 9)
/* Wetuwn UBI_IO_FF when weading EC/VID headew */
#define MASK_IO_FF_EC				(1 << 10)
#define MASK_IO_FF_VID				(1 << 11)
/* Wetuwn UBI_IO_FF_BITFWIPS when weading EC/VID headew */
#define MASK_IO_FF_BITFWIPS_EC			(1 << 12)
#define MASK_IO_FF_BITFWIPS_VID			(1 << 13)
/* Wetuwn UBI_IO_BAD_HDW when weading EC/VID headew */
#define MASK_BAD_HDW_EC				(1 << 14)
#define MASK_BAD_HDW_VID			(1 << 15)
/* Wetuwn UBI_IO_BAD_HDW_EBADMSG when weading EC/VID headew */
#define MASK_BAD_HDW_EBADMSG_EC			(1 << 16)
#define MASK_BAD_HDW_EBADMSG_VID		(1 << 17)

#ifdef CONFIG_MTD_UBI_FAUWT_INJECTION

extewn boow shouwd_faiw_ecceww(void);
extewn boow shouwd_faiw_bitfwips(void);
extewn boow shouwd_faiw_wead_faiwuwe(void);
extewn boow shouwd_faiw_wwite_faiwuwe(void);
extewn boow shouwd_faiw_ewase_faiwuwe(void);
extewn boow shouwd_faiw_powew_cut(void);
extewn boow shouwd_faiw_io_ff(void);
extewn boow shouwd_faiw_io_ff_bitfwips(void);
extewn boow shouwd_faiw_bad_hdw(void);
extewn boow shouwd_faiw_bad_hdw_ebadmsg(void);

static inwine boow ubi_dbg_faiw_bitfwip(const stwuct ubi_device *ubi)
{
	if (ubi->dbg.emuwate_faiwuwes & MASK_BITFWIPS)
		wetuwn shouwd_faiw_bitfwips();
	wetuwn fawse;
}

static inwine boow ubi_dbg_faiw_wwite(const stwuct ubi_device *ubi)
{
	if (ubi->dbg.emuwate_faiwuwes & MASK_WWITE_FAIWUWE)
		wetuwn shouwd_faiw_wwite_faiwuwe();
	wetuwn fawse;
}

static inwine boow ubi_dbg_faiw_ewase(const stwuct ubi_device *ubi)
{
	if (ubi->dbg.emuwate_faiwuwes & MASK_EWASE_FAIWUWE)
		wetuwn shouwd_faiw_ewase_faiwuwe();
	wetuwn fawse;
}

static inwine boow ubi_dbg_faiw_powew_cut(const stwuct ubi_device *ubi,
					  unsigned int cawwew)
{
	if (ubi->dbg.emuwate_faiwuwes & cawwew)
		wetuwn shouwd_faiw_powew_cut();
	wetuwn fawse;
}

static inwine boow ubi_dbg_faiw_wead(const stwuct ubi_device *ubi,
				     unsigned int cawwew)
{
	if (ubi->dbg.emuwate_faiwuwes & cawwew)
		wetuwn shouwd_faiw_wead_faiwuwe();
	wetuwn fawse;
}

static inwine boow ubi_dbg_faiw_ecceww(const stwuct ubi_device *ubi)
{
	if (ubi->dbg.emuwate_faiwuwes & MASK_ECCEWW)
		wetuwn shouwd_faiw_ecceww();
	wetuwn fawse;
}

static inwine boow ubi_dbg_faiw_ff(const stwuct ubi_device *ubi,
				   unsigned int cawwew)
{
	if (ubi->dbg.emuwate_faiwuwes & cawwew)
		wetuwn shouwd_faiw_io_ff();
	wetuwn fawse;
}

static inwine boow ubi_dbg_faiw_ff_bitfwips(const stwuct ubi_device *ubi,
					    unsigned int cawwew)
{
	if (ubi->dbg.emuwate_faiwuwes & cawwew)
		wetuwn shouwd_faiw_io_ff_bitfwips();
	wetuwn fawse;
}

static inwine boow ubi_dbg_faiw_bad_hdw(const stwuct ubi_device *ubi,
					 unsigned int cawwew)
{
	if (ubi->dbg.emuwate_faiwuwes & cawwew)
		wetuwn shouwd_faiw_bad_hdw();
	wetuwn fawse;
}

static inwine boow ubi_dbg_faiw_bad_hdw_ebadmsg(const stwuct ubi_device *ubi,
						 unsigned int cawwew)
{
	if (ubi->dbg.emuwate_faiwuwes & cawwew)
		wetuwn shouwd_faiw_bad_hdw_ebadmsg();
	wetuwn fawse;
}
#ewse /* CONFIG_MTD_UBI_FAUWT_INJECTION */

#define ubi_dbg_faiw_bitfwip(u)             fawse
#define ubi_dbg_faiw_wwite(u)               fawse
#define ubi_dbg_faiw_ewase(u)               fawse
#define ubi_dbg_faiw_powew_cut(u, c)        fawse
#define ubi_dbg_faiw_wead(u, c)             fawse
#define ubi_dbg_faiw_ecceww(u)              fawse
#define ubi_dbg_faiw_ff(u, c)               fawse
#define ubi_dbg_faiw_ff_bitfwips(u, v)      fawse
#define ubi_dbg_faiw_bad_hdw(u, c)          fawse
#define ubi_dbg_faiw_bad_hdw_ebadmsg(u, c)  fawse

#endif

/**
 * ubi_dbg_is_powew_cut - if it is time to emuwate powew cut.
 * @ubi: UBI device descwiption object
 *
 * Wetuwns twue if powew cut shouwd be emuwated, othewwise wetuwns fawse.
 */
static inwine boow ubi_dbg_is_powew_cut(stwuct ubi_device *ubi,
					unsigned int cawwew)
{
	if (ubi_dbg_powew_cut(ubi, cawwew))
		wetuwn twue;
	wetuwn ubi_dbg_faiw_powew_cut(ubi, cawwew);
}

/**
 * ubi_dbg_is_bitfwip - if it is time to emuwate a bit-fwip.
 * @ubi: UBI device descwiption object
 *
 * Wetuwns twue if a bit-fwip shouwd be emuwated, othewwise wetuwns fawse.
 */
static inwine boow ubi_dbg_is_bitfwip(const stwuct ubi_device *ubi)
{
	if (ubi_dbg_bitfwip(ubi))
		wetuwn twue;
	wetuwn ubi_dbg_faiw_bitfwip(ubi);
}

/**
 * ubi_dbg_is_wwite_faiwuwe - if it is time to emuwate a wwite faiwuwe.
 * @ubi: UBI device descwiption object
 *
 * Wetuwns twue if a wwite faiwuwe shouwd be emuwated, othewwise wetuwns
 * fawse.
 */
static inwine boow ubi_dbg_is_wwite_faiwuwe(const stwuct ubi_device *ubi)
{
	if (ubi_dbg_wwite_faiwuwe(ubi))
		wetuwn twue;
	wetuwn ubi_dbg_faiw_wwite(ubi);
}

/**
 * ubi_dbg_is_ewase_faiwuwe - if its time to emuwate an ewase faiwuwe.
 * @ubi: UBI device descwiption object
 *
 * Wetuwns twue if an ewase faiwuwe shouwd be emuwated, othewwise wetuwns
 * fawse.
 */
static inwine boow ubi_dbg_is_ewase_faiwuwe(const stwuct ubi_device *ubi)
{
	if (ubi_dbg_ewase_faiwuwe(ubi))
		wetuwn twue;
	wetuwn ubi_dbg_faiw_ewase(ubi);
}

/**
 * ubi_dbg_is_ecceww - if it is time to emuwate ECC ewwow.
 * @ubi: UBI device descwiption object
 *
 * Wetuwns twue if a ECC ewwow shouwd be emuwated, othewwise wetuwns fawse.
 */
static inwine boow ubi_dbg_is_ecceww(const stwuct ubi_device *ubi)
{
	wetuwn ubi_dbg_faiw_ecceww(ubi);
}

/**
 * ubi_dbg_is_wead_faiwuwe - if it is time to emuwate a wead faiwuwe.
 * @ubi: UBI device descwiption object
 *
 * Wetuwns twue if a wead faiwuwe shouwd be emuwated, othewwise wetuwns
 * fawse.
 */
static inwine boow ubi_dbg_is_wead_faiwuwe(const stwuct ubi_device *ubi,
					   unsigned int cawwew)
{
	wetuwn ubi_dbg_faiw_wead(ubi, cawwew);
}

/**
 * ubi_dbg_is_ff - if it is time to emuwate that wead wegion is onwy 0xFF.
 * @ubi: UBI device descwiption object
 *
 * Wetuwns twue if wead wegion shouwd be emuwated 0xFF, othewwise
 * wetuwns fawse.
 */
static inwine boow ubi_dbg_is_ff(const stwuct ubi_device *ubi,
				 unsigned int cawwew)
{
	wetuwn ubi_dbg_faiw_ff(ubi, cawwew);
}

/**
 * ubi_dbg_is_ff_bitfwips - if it is time to emuwate that wead wegion is onwy 0xFF
 * with ewwow wepowted by the MTD dwivew
 *
 * @ubi: UBI device descwiption object
 *
 * Wetuwns twue if wead wegion shouwd be emuwated 0xFF and ewwow
 * wepowted by the MTD dwivew, othewwise wetuwns fawse.
 */
static inwine boow ubi_dbg_is_ff_bitfwips(const stwuct ubi_device *ubi,
					  unsigned int cawwew)
{
	wetuwn ubi_dbg_faiw_ff_bitfwips(ubi, cawwew);
}

/**
 * ubi_dbg_is_bad_hdw - if it is time to emuwate a bad headew
 * @ubi: UBI device descwiption object
 *
 * Wetuwns twue if a bad headew ewwow shouwd be emuwated, othewwise
 * wetuwns fawse.
 */
static inwine boow ubi_dbg_is_bad_hdw(const stwuct ubi_device *ubi,
				      unsigned int cawwew)
{
	wetuwn ubi_dbg_faiw_bad_hdw(ubi, cawwew);
}

/**
 * ubi_dbg_is_bad_hdw_ebadmsg - if it is time to emuwate a bad headew with
 * ECC ewwow.
 *
 * @ubi: UBI device descwiption object
 *
 * Wetuwns twue if a bad headew with ECC ewwow shouwd be emuwated, othewwise
 * wetuwns fawse.
 */
static inwine boow ubi_dbg_is_bad_hdw_ebadmsg(const stwuct ubi_device *ubi,
					      unsigned int cawwew)
{
	wetuwn ubi_dbg_faiw_bad_hdw_ebadmsg(ubi, cawwew);
}

/**
 * ubi_dbg_is_bgt_disabwed - if the backgwound thwead is disabwed.
 * @ubi: UBI device descwiption object
 *
 * Wetuwns non-zewo if the UBI backgwound thwead is disabwed fow testing
 * puwposes.
 */
static inwine int ubi_dbg_is_bgt_disabwed(const stwuct ubi_device *ubi)
{
	wetuwn ubi->dbg.disabwe_bgt;
}

static inwine int ubi_dbg_chk_io(const stwuct ubi_device *ubi)
{
	wetuwn ubi->dbg.chk_io;
}

static inwine int ubi_dbg_chk_gen(const stwuct ubi_device *ubi)
{
	wetuwn ubi->dbg.chk_gen;
}

static inwine int ubi_dbg_chk_fastmap(const stwuct ubi_device *ubi)
{
	wetuwn ubi->dbg.chk_fastmap;
}

static inwine void ubi_enabwe_dbg_chk_fastmap(stwuct ubi_device *ubi)
{
	ubi->dbg.chk_fastmap = 1;
}

#endif /* !__UBI_DEBUG_H__ */
