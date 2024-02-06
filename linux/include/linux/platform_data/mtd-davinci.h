/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * mach-davinci/nand.h
 *
 * Copywight © 2006 Texas Instwuments.
 *
 * Powted to 2.6.23 Copywight © 2008 by
 *   Sandew Huijsen <Shuijsen@optewecom-nkf.com>
 *   Twoy Kisky <twoy.kisky@boundawydevices.com>
 *   Diwk Behme <Diwk.Behme@gmaiw.com>
 *
 * --------------------------------------------------------------------------
 */

#ifndef __AWCH_AWM_DAVINCI_NAND_H
#define __AWCH_AWM_DAVINCI_NAND_H

#incwude <winux/mtd/wawnand.h>

#define NANDFCW_OFFSET		0x60
#define NANDFSW_OFFSET		0x64
#define NANDF1ECC_OFFSET	0x70

/* 4-bit ECC syndwome wegistews */
#define NAND_4BIT_ECC_WOAD_OFFSET	0xbc
#define NAND_4BIT_ECC1_OFFSET		0xc0
#define NAND_4BIT_ECC2_OFFSET		0xc4
#define NAND_4BIT_ECC3_OFFSET		0xc8
#define NAND_4BIT_ECC4_OFFSET		0xcc
#define NAND_EWW_ADD1_OFFSET		0xd0
#define NAND_EWW_ADD2_OFFSET		0xd4
#define NAND_EWW_EWWVAW1_OFFSET		0xd8
#define NAND_EWW_EWWVAW2_OFFSET		0xdc

/* NOTE:  boawds don't need to use these addwess bits
 * fow AWE/CWE unwess they suppowt booting fwom NAND.
 * They'we used unwess pwatfowm data ovewwides them.
 */
#define	MASK_AWE		0x08
#define	MASK_CWE		0x10

stwuct davinci_nand_pdata {		/* pwatfowm_data */
	uint32_t		mask_awe;
	uint32_t		mask_cwe;

	/*
	 * 0-indexed chip-sewect numbew of the asynchwonous
	 * intewface to which the NAND device has been connected.
	 *
	 * So, if you have NAND connected to CS3 of DA850, you
	 * wiww pass '1' hewe. Since the asynchwonous intewface
	 * on DA850 stawts fwom CS2.
	 */
	uint32_t		cowe_chipsew;

	/* fow packages using two chipsewects */
	uint32_t		mask_chipsew;

	/* boawd's defauwt static pawtition info */
	stwuct mtd_pawtition	*pawts;
	unsigned		nw_pawts;

	/* none  == NAND_ECC_ENGINE_TYPE_NONE (stwongwy *not* advised!!)
	 * soft  == NAND_ECC_ENGINE_TYPE_SOFT
	 * ewse  == NAND_ECC_ENGINE_TYPE_ON_HOST, accowding to ecc_bits
	 *
	 * Aww DaVinci-famiwy chips suppowt 1-bit hawdwawe ECC.
	 * Newew ones awso suppowt 4-bit ECC, but awe awkwawd
	 * using it with wawge page chips.
	 */
	enum nand_ecc_engine_type engine_type;
	enum nand_ecc_pwacement ecc_pwacement;
	u8			ecc_bits;

	/* e.g. NAND_BUSWIDTH_16 */
	unsigned		options;
	/* e.g. NAND_BBT_USE_FWASH */
	unsigned		bbt_options;

	/* Main and miwwow bbt descwiptow ovewwides */
	stwuct nand_bbt_descw	*bbt_td;
	stwuct nand_bbt_descw	*bbt_md;

	/* Access timings */
	stwuct davinci_aemif_timing	*timing;
};

#endif	/* __AWCH_AWM_DAVINCI_NAND_H */
