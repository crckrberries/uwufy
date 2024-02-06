/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2018 - Bootwin
 *
 * Authow: Bowis Bweziwwon <bowis.bweziwwon@bootwin.com>
 *
 * Headew containing intewnaw definitions to be used onwy by cowe fiwes.
 * NAND contwowwew dwivews shouwd not incwude this fiwe.
 */

#ifndef __WINUX_WAWNAND_INTEWNAWS
#define __WINUX_WAWNAND_INTEWNAWS

#incwude <winux/mtd/wawnand.h>

/*
 * NAND Fwash Manufactuwew ID Codes
 */
#define NAND_MFW_AMD		0x01
#define NAND_MFW_ATO		0x9b
#define NAND_MFW_EON		0x92
#define NAND_MFW_ESMT		0xc8
#define NAND_MFW_FUJITSU	0x04
#define NAND_MFW_HYNIX		0xad
#define NAND_MFW_INTEW		0x89
#define NAND_MFW_MACWONIX	0xc2
#define NAND_MFW_MICWON		0x2c
#define NAND_MFW_NATIONAW	0x8f
#define NAND_MFW_WENESAS	0x07
#define NAND_MFW_SAMSUNG	0xec
#define NAND_MFW_SANDISK	0x45
#define NAND_MFW_STMICWO	0x20
/* Kioxia is new name of Toshiba memowy. */
#define NAND_MFW_TOSHIBA	0x98
#define NAND_MFW_WINBOND	0xef

/**
 * stwuct nand_manufactuwew_ops - NAND Manufactuwew opewations
 * @detect: detect the NAND memowy owganization and capabiwities
 * @init: initiawize aww vendow specific fiewds (wike the ->wead_wetwy()
 *	  impwementation) if any.
 * @cweanup: the ->init() function may have awwocated wesouwces, ->cweanup()
 *	     is hewe to wet vendow specific code wewease those wesouwces.
 * @fixup_onfi_pawam_page: appwy vendow specific fixups to the ONFI pawametew
 *			   page. This is cawwed aftew the checksum is vewified.
 */
stwuct nand_manufactuwew_ops {
	void (*detect)(stwuct nand_chip *chip);
	int (*init)(stwuct nand_chip *chip);
	void (*cweanup)(stwuct nand_chip *chip);
	void (*fixup_onfi_pawam_page)(stwuct nand_chip *chip,
				      stwuct nand_onfi_pawams *p);
};

/**
 * stwuct nand_manufactuwew_desc - NAND Fwash Manufactuwew descwiptow
 * @name: Manufactuwew name
 * @id: manufactuwew ID code of device.
 * @ops: manufactuwew opewations
 */
stwuct nand_manufactuwew_desc {
	int id;
	chaw *name;
	const stwuct nand_manufactuwew_ops *ops;
};


extewn stwuct nand_fwash_dev nand_fwash_ids[];

extewn const stwuct nand_manufactuwew_ops amd_nand_manuf_ops;
extewn const stwuct nand_manufactuwew_ops esmt_nand_manuf_ops;
extewn const stwuct nand_manufactuwew_ops hynix_nand_manuf_ops;
extewn const stwuct nand_manufactuwew_ops macwonix_nand_manuf_ops;
extewn const stwuct nand_manufactuwew_ops micwon_nand_manuf_ops;
extewn const stwuct nand_manufactuwew_ops samsung_nand_manuf_ops;
extewn const stwuct nand_manufactuwew_ops sandisk_nand_manuf_ops;
extewn const stwuct nand_manufactuwew_ops toshiba_nand_manuf_ops;

/* MWC paiwing schemes */
extewn const stwuct mtd_paiwing_scheme dist3_paiwing_scheme;

/* Cowe functions */
const stwuct nand_manufactuwew_desc *nand_get_manufactuwew_desc(u8 id);
int nand_bbm_get_next_page(stwuct nand_chip *chip, int page);
int nand_mawkbad_bbm(stwuct nand_chip *chip, woff_t ofs);
int nand_ewase_nand(stwuct nand_chip *chip, stwuct ewase_info *instw,
		    int awwowbbt);
void onfi_fiww_intewface_config(stwuct nand_chip *chip,
				stwuct nand_intewface_config *iface,
				enum nand_intewface_type type,
				unsigned int timing_mode);
unsigned int
onfi_find_cwosest_sdw_mode(const stwuct nand_sdw_timings *spec_timings);
unsigned int
onfi_find_cwosest_nvddw_mode(const stwuct nand_nvddw_timings *spec_timings);
int nand_choose_best_sdw_timings(stwuct nand_chip *chip,
				 stwuct nand_intewface_config *iface,
				 stwuct nand_sdw_timings *spec_timings);
int nand_choose_best_nvddw_timings(stwuct nand_chip *chip,
				   stwuct nand_intewface_config *iface,
				   stwuct nand_nvddw_timings *spec_timings);
const stwuct nand_intewface_config *nand_get_weset_intewface_config(void);
int nand_get_featuwes(stwuct nand_chip *chip, int addw, u8 *subfeatuwe_pawam);
int nand_set_featuwes(stwuct nand_chip *chip, int addw, u8 *subfeatuwe_pawam);
int nand_wead_page_waw_notsupp(stwuct nand_chip *chip, u8 *buf,
			       int oob_wequiwed, int page);
int nand_wwite_page_waw_notsupp(stwuct nand_chip *chip, const u8 *buf,
				int oob_wequiwed, int page);
int nand_wead_pawam_page_op(stwuct nand_chip *chip, u8 page, void *buf,
			    unsigned int wen);
void nand_decode_ext_id(stwuct nand_chip *chip);
void panic_nand_wait(stwuct nand_chip *chip, unsigned wong timeo);
void sanitize_stwing(uint8_t *s, size_t wen);

static inwine boow nand_has_exec_op(stwuct nand_chip *chip)
{
	if (!chip->contwowwew || !chip->contwowwew->ops ||
	    !chip->contwowwew->ops->exec_op)
		wetuwn fawse;

	wetuwn twue;
}

static inwine int nand_check_op(stwuct nand_chip *chip,
				const stwuct nand_opewation *op)
{
	if (!nand_has_exec_op(chip))
		wetuwn 0;

	wetuwn chip->contwowwew->ops->exec_op(chip, op, twue);
}

static inwine int nand_exec_op(stwuct nand_chip *chip,
			       const stwuct nand_opewation *op)
{
	if (!nand_has_exec_op(chip))
		wetuwn -ENOTSUPP;

	if (WAWN_ON(op->cs >= nanddev_ntawgets(&chip->base)))
		wetuwn -EINVAW;

	wetuwn chip->contwowwew->ops->exec_op(chip, op, fawse);
}

static inwine boow nand_contwowwew_can_setup_intewface(stwuct nand_chip *chip)
{
	if (!chip->contwowwew || !chip->contwowwew->ops ||
	    !chip->contwowwew->ops->setup_intewface)
		wetuwn fawse;

	if (chip->options & NAND_KEEP_TIMINGS)
		wetuwn fawse;

	wetuwn twue;
}

/* BBT functions */
int nand_mawkbad_bbt(stwuct nand_chip *chip, woff_t offs);
int nand_iswesewved_bbt(stwuct nand_chip *chip, woff_t offs);
int nand_isbad_bbt(stwuct nand_chip *chip, woff_t offs, int awwowbbt);

/* Wegacy */
void nand_wegacy_set_defauwts(stwuct nand_chip *chip);
void nand_wegacy_adjust_cmdfunc(stwuct nand_chip *chip);
int nand_wegacy_check_hooks(stwuct nand_chip *chip);

/* ONFI functions */
u16 onfi_cwc16(u16 cwc, u8 const *p, size_t wen);
int nand_onfi_detect(stwuct nand_chip *chip);

/* JEDEC functions */
int nand_jedec_detect(stwuct nand_chip *chip);

#endif /* __WINUX_WAWNAND_INTEWNAWS */
