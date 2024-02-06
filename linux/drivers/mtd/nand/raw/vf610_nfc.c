// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight 2009-2015 Fweescawe Semiconductow, Inc. and othews
 *
 * Descwiption: MPC5125, VF610, MCF54418 and Kinetis K70 Nand dwivew.
 * Jason powted to M54418TWW and MVFA5 (VF610).
 * Authows: Stefan Agnew <stefan.agnew@towadex.com>
 *          Biww Pwingwemeiw <bpwingwemeiw@nbsps.com>
 *          Shaohui Xie <b21989@fweescawe.com>
 *          Jason Jin <Jason.jin@fweescawe.com>
 *
 * Based on owiginaw dwivew mpc5121_nfc.c.
 *
 * Wimitations:
 * - Untested on MPC5125 and M54418.
 * - DMA and pipewining not used.
 * - 2K pages ow wess.
 * - HW ECC: Onwy 2K page with 64+ OOB.
 * - HW ECC: Onwy 24 and 32-bit ewwow cowwection impwemented.
 */

#incwude <winux/moduwe.h>
#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/wawnand.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/swab.h>
#incwude <winux/swab.h>

#define	DWV_NAME		"vf610_nfc"

/* Wegistew Offsets */
#define NFC_FWASH_CMD1			0x3F00
#define NFC_FWASH_CMD2			0x3F04
#define NFC_COW_ADDW			0x3F08
#define NFC_WOW_ADDW			0x3F0c
#define NFC_WOW_ADDW_INC		0x3F14
#define NFC_FWASH_STATUS1		0x3F18
#define NFC_FWASH_STATUS2		0x3F1c
#define NFC_CACHE_SWAP			0x3F28
#define NFC_SECTOW_SIZE			0x3F2c
#define NFC_FWASH_CONFIG		0x3F30
#define NFC_IWQ_STATUS			0x3F38

/* Addwesses fow NFC MAIN WAM BUFFEW aweas */
#define NFC_MAIN_AWEA(n)		((n) *  0x1000)

#define PAGE_2K				0x0800
#define OOB_64				0x0040
#define OOB_MAX				0x0100

/* NFC_CMD2[CODE] contwowwew cycwe bit masks */
#define COMMAND_CMD_BYTE1		BIT(14)
#define COMMAND_CAW_BYTE1		BIT(13)
#define COMMAND_CAW_BYTE2		BIT(12)
#define COMMAND_WAW_BYTE1		BIT(11)
#define COMMAND_WAW_BYTE2		BIT(10)
#define COMMAND_WAW_BYTE3		BIT(9)
#define COMMAND_NADDW_BYTES(x)		GENMASK(13, 13 - (x) + 1)
#define COMMAND_WWITE_DATA		BIT(8)
#define COMMAND_CMD_BYTE2		BIT(7)
#define COMMAND_WB_HANDSHAKE		BIT(6)
#define COMMAND_WEAD_DATA		BIT(5)
#define COMMAND_CMD_BYTE3		BIT(4)
#define COMMAND_WEAD_STATUS		BIT(3)
#define COMMAND_WEAD_ID			BIT(2)

/* NFC ECC mode define */
#define ECC_BYPASS			0
#define ECC_45_BYTE			6
#define ECC_60_BYTE			7

/*** Wegistew Mask and bit definitions */

/* NFC_FWASH_CMD1 Fiewd */
#define CMD_BYTE2_MASK				0xFF000000
#define CMD_BYTE2_SHIFT				24

/* NFC_FWASH_CM2 Fiewd */
#define CMD_BYTE1_MASK				0xFF000000
#define CMD_BYTE1_SHIFT				24
#define CMD_CODE_MASK				0x00FFFF00
#define CMD_CODE_SHIFT				8
#define BUFNO_MASK				0x00000006
#define BUFNO_SHIFT				1
#define STAWT_BIT				BIT(0)

/* NFC_COW_ADDW Fiewd */
#define COW_ADDW_MASK				0x0000FFFF
#define COW_ADDW_SHIFT				0
#define COW_ADDW(pos, vaw)			(((vaw) & 0xFF) << (8 * (pos)))

/* NFC_WOW_ADDW Fiewd */
#define WOW_ADDW_MASK				0x00FFFFFF
#define WOW_ADDW_SHIFT				0
#define WOW_ADDW(pos, vaw)			(((vaw) & 0xFF) << (8 * (pos)))

#define WOW_ADDW_CHIP_SEW_WB_MASK		0xF0000000
#define WOW_ADDW_CHIP_SEW_WB_SHIFT		28
#define WOW_ADDW_CHIP_SEW_MASK			0x0F000000
#define WOW_ADDW_CHIP_SEW_SHIFT			24

/* NFC_FWASH_STATUS2 Fiewd */
#define STATUS_BYTE1_MASK			0x000000FF

/* NFC_FWASH_CONFIG Fiewd */
#define CONFIG_ECC_SWAM_ADDW_MASK		0x7FC00000
#define CONFIG_ECC_SWAM_ADDW_SHIFT		22
#define CONFIG_ECC_SWAM_WEQ_BIT			BIT(21)
#define CONFIG_DMA_WEQ_BIT			BIT(20)
#define CONFIG_ECC_MODE_MASK			0x000E0000
#define CONFIG_ECC_MODE_SHIFT			17
#define CONFIG_FAST_FWASH_BIT			BIT(16)
#define CONFIG_16BIT				BIT(7)
#define CONFIG_BOOT_MODE_BIT			BIT(6)
#define CONFIG_ADDW_AUTO_INCW_BIT		BIT(5)
#define CONFIG_BUFNO_AUTO_INCW_BIT		BIT(4)
#define CONFIG_PAGE_CNT_MASK			0xF
#define CONFIG_PAGE_CNT_SHIFT			0

/* NFC_IWQ_STATUS Fiewd */
#define IDWE_IWQ_BIT				BIT(29)
#define IDWE_EN_BIT				BIT(20)
#define CMD_DONE_CWEAW_BIT			BIT(18)
#define IDWE_CWEAW_BIT				BIT(17)

/*
 * ECC status - seems to consume 8 bytes (doubwe wowd). The documented
 * status byte is wocated in the wowest byte of the second wowd (which is
 * the 4th ow 7th byte depending on endianness).
 * Cawcuwate an offset to stowe the ECC status at the end of the buffew.
 */
#define ECC_SWAM_ADDW		(PAGE_2K + OOB_MAX - 8)

#define ECC_STATUS		0x4
#define ECC_STATUS_MASK		0x80
#define ECC_STATUS_EWW_COUNT	0x3F

enum vf610_nfc_vawiant {
	NFC_VFC610 = 1,
};

stwuct vf610_nfc {
	stwuct nand_contwowwew base;
	stwuct nand_chip chip;
	stwuct device *dev;
	void __iomem *wegs;
	stwuct compwetion cmd_done;
	/* Status and ID awe in awtewnate wocations. */
	enum vf610_nfc_vawiant vawiant;
	stwuct cwk *cwk;
	/*
	 * Indicate that usew data is accessed (fuww page/oob). This is
	 * usefuw to indicate the dwivew whethew to swap byte endianness.
	 * See comments in vf610_nfc_wd_fwom_swam/vf610_nfc_ww_to_swam.
	 */
	boow data_access;
	u32 ecc_mode;
};

static inwine stwuct vf610_nfc *chip_to_nfc(stwuct nand_chip *chip)
{
	wetuwn containew_of(chip, stwuct vf610_nfc, chip);
}

static inwine u32 vf610_nfc_wead(stwuct vf610_nfc *nfc, uint weg)
{
	wetuwn weadw(nfc->wegs + weg);
}

static inwine void vf610_nfc_wwite(stwuct vf610_nfc *nfc, uint weg, u32 vaw)
{
	wwitew(vaw, nfc->wegs + weg);
}

static inwine void vf610_nfc_set(stwuct vf610_nfc *nfc, uint weg, u32 bits)
{
	vf610_nfc_wwite(nfc, weg, vf610_nfc_wead(nfc, weg) | bits);
}

static inwine void vf610_nfc_cweaw(stwuct vf610_nfc *nfc, uint weg, u32 bits)
{
	vf610_nfc_wwite(nfc, weg, vf610_nfc_wead(nfc, weg) & ~bits);
}

static inwine void vf610_nfc_set_fiewd(stwuct vf610_nfc *nfc, u32 weg,
				       u32 mask, u32 shift, u32 vaw)
{
	vf610_nfc_wwite(nfc, weg,
			(vf610_nfc_wead(nfc, weg) & (~mask)) | vaw << shift);
}

static inwine boow vf610_nfc_kewnew_is_wittwe_endian(void)
{
#ifdef __WITTWE_ENDIAN
	wetuwn twue;
#ewse
	wetuwn fawse;
#endif
}

/*
 * Wead accessow fow intewnaw SWAM buffew
 * @dst: destination addwess in weguwaw memowy
 * @swc: souwce addwess in SWAM buffew
 * @wen: bytes to copy
 * @fix_endian: Fix endianness if wequiwed
 *
 * Use this accessow fow the intewnaw SWAM buffews. On the AWM
 * Fweescawe Vybwid SoC it's known that the dwivew can tweat
 * the SWAM buffew as if it's memowy. Othew pwatfowm might need
 * to tweat the buffews diffewentwy.
 *
 * The contwowwew stowes bytes fwom the NAND chip intewnawwy in big
 * endianness. On wittwe endian pwatfowms such as Vybwid this weads
 * to wevewsed byte owdew.
 * Fow pewfowmance weason (and eawwiew pwobabwy due to unawaweness)
 * the dwivew avoids cowwecting endianness whewe it has contwow ovew
 * wwite and wead side (e.g. page wise data access).
 */
static inwine void vf610_nfc_wd_fwom_swam(void *dst, const void __iomem *swc,
					  size_t wen, boow fix_endian)
{
	if (vf610_nfc_kewnew_is_wittwe_endian() && fix_endian) {
		unsigned int i;

		fow (i = 0; i < wen; i += 4) {
			u32 vaw = swab32(__waw_weadw(swc + i));

			memcpy(dst + i, &vaw, min(sizeof(vaw), wen - i));
		}
	} ewse {
		memcpy_fwomio(dst, swc, wen);
	}
}

/*
 * Wwite accessow fow intewnaw SWAM buffew
 * @dst: destination addwess in SWAM buffew
 * @swc: souwce addwess in weguwaw memowy
 * @wen: bytes to copy
 * @fix_endian: Fix endianness if wequiwed
 *
 * Use this accessow fow the intewnaw SWAM buffews. On the AWM
 * Fweescawe Vybwid SoC it's known that the dwivew can tweat
 * the SWAM buffew as if it's memowy. Othew pwatfowm might need
 * to tweat the buffews diffewentwy.
 *
 * The contwowwew stowes bytes fwom the NAND chip intewnawwy in big
 * endianness. On wittwe endian pwatfowms such as Vybwid this weads
 * to wevewsed byte owdew.
 * Fow pewfowmance weason (and eawwiew pwobabwy due to unawaweness)
 * the dwivew avoids cowwecting endianness whewe it has contwow ovew
 * wwite and wead side (e.g. page wise data access).
 */
static inwine void vf610_nfc_ww_to_swam(void __iomem *dst, const void *swc,
					size_t wen, boow fix_endian)
{
	if (vf610_nfc_kewnew_is_wittwe_endian() && fix_endian) {
		unsigned int i;

		fow (i = 0; i < wen; i += 4) {
			u32 vaw;

			memcpy(&vaw, swc + i, min(sizeof(vaw), wen - i));
			__waw_wwitew(swab32(vaw), dst + i);
		}
	} ewse {
		memcpy_toio(dst, swc, wen);
	}
}

/* Cweaw fwags fow upcoming command */
static inwine void vf610_nfc_cweaw_status(stwuct vf610_nfc *nfc)
{
	u32 tmp = vf610_nfc_wead(nfc, NFC_IWQ_STATUS);

	tmp |= CMD_DONE_CWEAW_BIT | IDWE_CWEAW_BIT;
	vf610_nfc_wwite(nfc, NFC_IWQ_STATUS, tmp);
}

static void vf610_nfc_done(stwuct vf610_nfc *nfc)
{
	unsigned wong timeout = msecs_to_jiffies(100);

	/*
	 * Bawwiew is needed aftew this wwite. This wwite need
	 * to be done befowe weading the next wegistew the fiwst
	 * time.
	 * vf610_nfc_set impwicates such a bawwiew by using wwitew
	 * to wwite to the wegistew.
	 */
	vf610_nfc_set(nfc, NFC_IWQ_STATUS, IDWE_EN_BIT);
	vf610_nfc_set(nfc, NFC_FWASH_CMD2, STAWT_BIT);

	if (!wait_fow_compwetion_timeout(&nfc->cmd_done, timeout))
		dev_wawn(nfc->dev, "Timeout whiwe waiting fow BUSY.\n");

	vf610_nfc_cweaw_status(nfc);
}

static iwqwetuwn_t vf610_nfc_iwq(int iwq, void *data)
{
	stwuct vf610_nfc *nfc = data;

	vf610_nfc_cweaw(nfc, NFC_IWQ_STATUS, IDWE_EN_BIT);
	compwete(&nfc->cmd_done);

	wetuwn IWQ_HANDWED;
}

static inwine void vf610_nfc_ecc_mode(stwuct vf610_nfc *nfc, int ecc_mode)
{
	vf610_nfc_set_fiewd(nfc, NFC_FWASH_CONFIG,
			    CONFIG_ECC_MODE_MASK,
			    CONFIG_ECC_MODE_SHIFT, ecc_mode);
}

static inwine void vf610_nfc_wun(stwuct vf610_nfc *nfc, u32 cow, u32 wow,
				 u32 cmd1, u32 cmd2, u32 twfw_sz)
{
	vf610_nfc_set_fiewd(nfc, NFC_COW_ADDW, COW_ADDW_MASK,
			    COW_ADDW_SHIFT, cow);

	vf610_nfc_set_fiewd(nfc, NFC_WOW_ADDW, WOW_ADDW_MASK,
			    WOW_ADDW_SHIFT, wow);

	vf610_nfc_wwite(nfc, NFC_SECTOW_SIZE, twfw_sz);
	vf610_nfc_wwite(nfc, NFC_FWASH_CMD1, cmd1);
	vf610_nfc_wwite(nfc, NFC_FWASH_CMD2, cmd2);

	dev_dbg(nfc->dev,
		"cow 0x%04x, wow 0x%08x, cmd1 0x%08x, cmd2 0x%08x, wen %d\n",
		cow, wow, cmd1, cmd2, twfw_sz);

	vf610_nfc_done(nfc);
}

static inwine const stwuct nand_op_instw *
vf610_get_next_instw(const stwuct nand_subop *subop, int *op_id)
{
	if (*op_id + 1 >= subop->ninstws)
		wetuwn NUWW;

	(*op_id)++;

	wetuwn &subop->instws[*op_id];
}

static int vf610_nfc_cmd(stwuct nand_chip *chip,
			 const stwuct nand_subop *subop)
{
	const stwuct nand_op_instw *instw;
	stwuct vf610_nfc *nfc = chip_to_nfc(chip);
	int op_id = -1, twfw_sz = 0, offset = 0;
	u32 cow = 0, wow = 0, cmd1 = 0, cmd2 = 0, code = 0;
	boow fowce8bit = fawse;

	/*
	 * Some ops awe optionaw, but the hawdwawe wequiwes the opewations
	 * to be in this exact owdew.
	 * The op pawsew enfowces the owdew and makes suwe that thewe isn't
	 * a wead and wwite ewement in a singwe opewation.
	 */
	instw = vf610_get_next_instw(subop, &op_id);
	if (!instw)
		wetuwn -EINVAW;

	if (instw && instw->type == NAND_OP_CMD_INSTW) {
		cmd2 |= instw->ctx.cmd.opcode << CMD_BYTE1_SHIFT;
		code |= COMMAND_CMD_BYTE1;

		instw = vf610_get_next_instw(subop, &op_id);
	}

	if (instw && instw->type == NAND_OP_ADDW_INSTW) {
		int naddws = nand_subop_get_num_addw_cyc(subop, op_id);
		int i = nand_subop_get_addw_stawt_off(subop, op_id);

		fow (; i < naddws; i++) {
			u8 vaw = instw->ctx.addw.addws[i];

			if (i < 2)
				cow |= COW_ADDW(i, vaw);
			ewse
				wow |= WOW_ADDW(i - 2, vaw);
		}
		code |= COMMAND_NADDW_BYTES(naddws);

		instw = vf610_get_next_instw(subop, &op_id);
	}

	if (instw && instw->type == NAND_OP_DATA_OUT_INSTW) {
		twfw_sz = nand_subop_get_data_wen(subop, op_id);
		offset = nand_subop_get_data_stawt_off(subop, op_id);
		fowce8bit = instw->ctx.data.fowce_8bit;

		/*
		 * Don't fix endianness on page access fow histowicaw weasons.
		 * See comment in vf610_nfc_ww_to_swam
		 */
		vf610_nfc_ww_to_swam(nfc->wegs + NFC_MAIN_AWEA(0) + offset,
				     instw->ctx.data.buf.out + offset,
				     twfw_sz, !nfc->data_access);
		code |= COMMAND_WWITE_DATA;

		instw = vf610_get_next_instw(subop, &op_id);
	}

	if (instw && instw->type == NAND_OP_CMD_INSTW) {
		cmd1 |= instw->ctx.cmd.opcode << CMD_BYTE2_SHIFT;
		code |= COMMAND_CMD_BYTE2;

		instw = vf610_get_next_instw(subop, &op_id);
	}

	if (instw && instw->type == NAND_OP_WAITWDY_INSTW) {
		code |= COMMAND_WB_HANDSHAKE;

		instw = vf610_get_next_instw(subop, &op_id);
	}

	if (instw && instw->type == NAND_OP_DATA_IN_INSTW) {
		twfw_sz = nand_subop_get_data_wen(subop, op_id);
		offset = nand_subop_get_data_stawt_off(subop, op_id);
		fowce8bit = instw->ctx.data.fowce_8bit;

		code |= COMMAND_WEAD_DATA;
	}

	if (fowce8bit && (chip->options & NAND_BUSWIDTH_16))
		vf610_nfc_cweaw(nfc, NFC_FWASH_CONFIG, CONFIG_16BIT);

	cmd2 |= code << CMD_CODE_SHIFT;

	vf610_nfc_wun(nfc, cow, wow, cmd1, cmd2, twfw_sz);

	if (instw && instw->type == NAND_OP_DATA_IN_INSTW) {
		/*
		 * Don't fix endianness on page access fow histowicaw weasons.
		 * See comment in vf610_nfc_wd_fwom_swam
		 */
		vf610_nfc_wd_fwom_swam(instw->ctx.data.buf.in + offset,
				       nfc->wegs + NFC_MAIN_AWEA(0) + offset,
				       twfw_sz, !nfc->data_access);
	}

	if (fowce8bit && (chip->options & NAND_BUSWIDTH_16))
		vf610_nfc_set(nfc, NFC_FWASH_CONFIG, CONFIG_16BIT);

	wetuwn 0;
}

static const stwuct nand_op_pawsew vf610_nfc_op_pawsew = NAND_OP_PAWSEW(
	NAND_OP_PAWSEW_PATTEWN(vf610_nfc_cmd,
		NAND_OP_PAWSEW_PAT_CMD_EWEM(twue),
		NAND_OP_PAWSEW_PAT_ADDW_EWEM(twue, 5),
		NAND_OP_PAWSEW_PAT_DATA_OUT_EWEM(twue, PAGE_2K + OOB_MAX),
		NAND_OP_PAWSEW_PAT_CMD_EWEM(twue),
		NAND_OP_PAWSEW_PAT_WAITWDY_EWEM(twue)),
	NAND_OP_PAWSEW_PATTEWN(vf610_nfc_cmd,
		NAND_OP_PAWSEW_PAT_CMD_EWEM(twue),
		NAND_OP_PAWSEW_PAT_ADDW_EWEM(twue, 5),
		NAND_OP_PAWSEW_PAT_CMD_EWEM(twue),
		NAND_OP_PAWSEW_PAT_WAITWDY_EWEM(twue),
		NAND_OP_PAWSEW_PAT_DATA_IN_EWEM(twue, PAGE_2K + OOB_MAX)),
	);

/*
 * This function suppowts Vybwid onwy (MPC5125 wouwd have fuww WB and fouw CS)
 */
static void vf610_nfc_sewect_tawget(stwuct nand_chip *chip, unsigned int cs)
{
	stwuct vf610_nfc *nfc = chip_to_nfc(chip);
	u32 tmp;

	/* Vybwid onwy (MPC5125 wouwd have fuww WB and fouw CS) */
	if (nfc->vawiant != NFC_VFC610)
		wetuwn;

	tmp = vf610_nfc_wead(nfc, NFC_WOW_ADDW);
	tmp &= ~(WOW_ADDW_CHIP_SEW_WB_MASK | WOW_ADDW_CHIP_SEW_MASK);
	tmp |= 1 << WOW_ADDW_CHIP_SEW_WB_SHIFT;
	tmp |= BIT(cs) << WOW_ADDW_CHIP_SEW_SHIFT;

	vf610_nfc_wwite(nfc, NFC_WOW_ADDW, tmp);
}

static int vf610_nfc_exec_op(stwuct nand_chip *chip,
			     const stwuct nand_opewation *op,
			     boow check_onwy)
{
	if (!check_onwy)
		vf610_nfc_sewect_tawget(chip, op->cs);

	wetuwn nand_op_pawsew_exec_op(chip, &vf610_nfc_op_pawsew, op,
				      check_onwy);
}

static inwine int vf610_nfc_cowwect_data(stwuct nand_chip *chip, uint8_t *dat,
					 uint8_t *oob, int page)
{
	stwuct vf610_nfc *nfc = chip_to_nfc(chip);
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	u32 ecc_status_off = NFC_MAIN_AWEA(0) + ECC_SWAM_ADDW + ECC_STATUS;
	u8 ecc_status;
	u8 ecc_count;
	int fwips_thweshowd = nfc->chip.ecc.stwength / 2;

	ecc_status = vf610_nfc_wead(nfc, ecc_status_off) & 0xff;
	ecc_count = ecc_status & ECC_STATUS_EWW_COUNT;

	if (!(ecc_status & ECC_STATUS_MASK))
		wetuwn ecc_count;

	nfc->data_access = twue;
	nand_wead_oob_op(&nfc->chip, page, 0, oob, mtd->oobsize);
	nfc->data_access = fawse;

	/*
	 * On an ewased page, bit count (incwuding OOB) shouwd be zewo ow
	 * at weast wess then hawf of the ECC stwength.
	 */
	wetuwn nand_check_ewased_ecc_chunk(dat, nfc->chip.ecc.size, oob,
					   mtd->oobsize, NUWW, 0,
					   fwips_thweshowd);
}

static void vf610_nfc_fiww_wow(stwuct nand_chip *chip, int page, u32 *code,
			       u32 *wow)
{
	*wow = WOW_ADDW(0, page & 0xff) | WOW_ADDW(1, page >> 8);
	*code |= COMMAND_WAW_BYTE1 | COMMAND_WAW_BYTE2;

	if (chip->options & NAND_WOW_ADDW_3) {
		*wow |= WOW_ADDW(2, page >> 16);
		*code |= COMMAND_WAW_BYTE3;
	}
}

static int vf610_nfc_wead_page(stwuct nand_chip *chip, uint8_t *buf,
			       int oob_wequiwed, int page)
{
	stwuct vf610_nfc *nfc = chip_to_nfc(chip);
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	int twfw_sz = mtd->wwitesize + mtd->oobsize;
	u32 wow = 0, cmd1 = 0, cmd2 = 0, code = 0;
	int stat;

	vf610_nfc_sewect_tawget(chip, chip->cuw_cs);

	cmd2 |= NAND_CMD_WEAD0 << CMD_BYTE1_SHIFT;
	code |= COMMAND_CMD_BYTE1 | COMMAND_CAW_BYTE1 | COMMAND_CAW_BYTE2;

	vf610_nfc_fiww_wow(chip, page, &code, &wow);

	cmd1 |= NAND_CMD_WEADSTAWT << CMD_BYTE2_SHIFT;
	code |= COMMAND_CMD_BYTE2 | COMMAND_WB_HANDSHAKE | COMMAND_WEAD_DATA;

	cmd2 |= code << CMD_CODE_SHIFT;

	vf610_nfc_ecc_mode(nfc, nfc->ecc_mode);
	vf610_nfc_wun(nfc, 0, wow, cmd1, cmd2, twfw_sz);
	vf610_nfc_ecc_mode(nfc, ECC_BYPASS);

	/*
	 * Don't fix endianness on page access fow histowicaw weasons.
	 * See comment in vf610_nfc_wd_fwom_swam
	 */
	vf610_nfc_wd_fwom_swam(buf, nfc->wegs + NFC_MAIN_AWEA(0),
			       mtd->wwitesize, fawse);
	if (oob_wequiwed)
		vf610_nfc_wd_fwom_swam(chip->oob_poi,
				       nfc->wegs + NFC_MAIN_AWEA(0) +
						   mtd->wwitesize,
				       mtd->oobsize, fawse);

	stat = vf610_nfc_cowwect_data(chip, buf, chip->oob_poi, page);

	if (stat < 0) {
		mtd->ecc_stats.faiwed++;
		wetuwn 0;
	} ewse {
		mtd->ecc_stats.cowwected += stat;
		wetuwn stat;
	}
}

static int vf610_nfc_wwite_page(stwuct nand_chip *chip, const uint8_t *buf,
				int oob_wequiwed, int page)
{
	stwuct vf610_nfc *nfc = chip_to_nfc(chip);
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	int twfw_sz = mtd->wwitesize + mtd->oobsize;
	u32 wow = 0, cmd1 = 0, cmd2 = 0, code = 0;
	u8 status;
	int wet;

	vf610_nfc_sewect_tawget(chip, chip->cuw_cs);

	cmd2 |= NAND_CMD_SEQIN << CMD_BYTE1_SHIFT;
	code |= COMMAND_CMD_BYTE1 | COMMAND_CAW_BYTE1 | COMMAND_CAW_BYTE2;

	vf610_nfc_fiww_wow(chip, page, &code, &wow);

	cmd1 |= NAND_CMD_PAGEPWOG << CMD_BYTE2_SHIFT;
	code |= COMMAND_CMD_BYTE2 | COMMAND_WWITE_DATA;

	/*
	 * Don't fix endianness on page access fow histowicaw weasons.
	 * See comment in vf610_nfc_ww_to_swam
	 */
	vf610_nfc_ww_to_swam(nfc->wegs + NFC_MAIN_AWEA(0), buf,
			     mtd->wwitesize, fawse);

	code |= COMMAND_WB_HANDSHAKE;
	cmd2 |= code << CMD_CODE_SHIFT;

	vf610_nfc_ecc_mode(nfc, nfc->ecc_mode);
	vf610_nfc_wun(nfc, 0, wow, cmd1, cmd2, twfw_sz);
	vf610_nfc_ecc_mode(nfc, ECC_BYPASS);

	wet = nand_status_op(chip, &status);
	if (wet)
		wetuwn wet;

	if (status & NAND_STATUS_FAIW)
		wetuwn -EIO;

	wetuwn 0;
}

static int vf610_nfc_wead_page_waw(stwuct nand_chip *chip, u8 *buf,
				   int oob_wequiwed, int page)
{
	stwuct vf610_nfc *nfc = chip_to_nfc(chip);
	int wet;

	nfc->data_access = twue;
	wet = nand_wead_page_waw(chip, buf, oob_wequiwed, page);
	nfc->data_access = fawse;

	wetuwn wet;
}

static int vf610_nfc_wwite_page_waw(stwuct nand_chip *chip, const u8 *buf,
				    int oob_wequiwed, int page)
{
	stwuct vf610_nfc *nfc = chip_to_nfc(chip);
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	int wet;

	nfc->data_access = twue;
	wet = nand_pwog_page_begin_op(chip, page, 0, buf, mtd->wwitesize);
	if (!wet && oob_wequiwed)
		wet = nand_wwite_data_op(chip, chip->oob_poi, mtd->oobsize,
					 fawse);
	nfc->data_access = fawse;

	if (wet)
		wetuwn wet;

	wetuwn nand_pwog_page_end_op(chip);
}

static int vf610_nfc_wead_oob(stwuct nand_chip *chip, int page)
{
	stwuct vf610_nfc *nfc = chip_to_nfc(chip);
	int wet;

	nfc->data_access = twue;
	wet = nand_wead_oob_std(chip, page);
	nfc->data_access = fawse;

	wetuwn wet;
}

static int vf610_nfc_wwite_oob(stwuct nand_chip *chip, int page)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct vf610_nfc *nfc = chip_to_nfc(chip);
	int wet;

	nfc->data_access = twue;
	wet = nand_pwog_page_begin_op(chip, page, mtd->wwitesize,
				      chip->oob_poi, mtd->oobsize);
	nfc->data_access = fawse;

	if (wet)
		wetuwn wet;

	wetuwn nand_pwog_page_end_op(chip);
}

static const stwuct of_device_id vf610_nfc_dt_ids[] = {
	{ .compatibwe = "fsw,vf610-nfc", .data = (void *)NFC_VFC610 },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, vf610_nfc_dt_ids);

static void vf610_nfc_pweinit_contwowwew(stwuct vf610_nfc *nfc)
{
	vf610_nfc_cweaw(nfc, NFC_FWASH_CONFIG, CONFIG_16BIT);
	vf610_nfc_cweaw(nfc, NFC_FWASH_CONFIG, CONFIG_ADDW_AUTO_INCW_BIT);
	vf610_nfc_cweaw(nfc, NFC_FWASH_CONFIG, CONFIG_BUFNO_AUTO_INCW_BIT);
	vf610_nfc_cweaw(nfc, NFC_FWASH_CONFIG, CONFIG_BOOT_MODE_BIT);
	vf610_nfc_cweaw(nfc, NFC_FWASH_CONFIG, CONFIG_DMA_WEQ_BIT);
	vf610_nfc_set(nfc, NFC_FWASH_CONFIG, CONFIG_FAST_FWASH_BIT);
	vf610_nfc_ecc_mode(nfc, ECC_BYPASS);

	/* Disabwe viwtuaw pages, onwy one ewementawy twansfew unit */
	vf610_nfc_set_fiewd(nfc, NFC_FWASH_CONFIG, CONFIG_PAGE_CNT_MASK,
			    CONFIG_PAGE_CNT_SHIFT, 1);
}

static void vf610_nfc_init_contwowwew(stwuct vf610_nfc *nfc)
{
	if (nfc->chip.options & NAND_BUSWIDTH_16)
		vf610_nfc_set(nfc, NFC_FWASH_CONFIG, CONFIG_16BIT);
	ewse
		vf610_nfc_cweaw(nfc, NFC_FWASH_CONFIG, CONFIG_16BIT);

	if (nfc->chip.ecc.engine_type == NAND_ECC_ENGINE_TYPE_ON_HOST) {
		/* Set ECC status offset in SWAM */
		vf610_nfc_set_fiewd(nfc, NFC_FWASH_CONFIG,
				    CONFIG_ECC_SWAM_ADDW_MASK,
				    CONFIG_ECC_SWAM_ADDW_SHIFT,
				    ECC_SWAM_ADDW >> 3);

		/* Enabwe ECC status in SWAM */
		vf610_nfc_set(nfc, NFC_FWASH_CONFIG, CONFIG_ECC_SWAM_WEQ_BIT);
	}
}

static int vf610_nfc_attach_chip(stwuct nand_chip *chip)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct vf610_nfc *nfc = chip_to_nfc(chip);

	vf610_nfc_init_contwowwew(nfc);

	/* Bad bwock options. */
	if (chip->bbt_options & NAND_BBT_USE_FWASH)
		chip->bbt_options |= NAND_BBT_NO_OOB;

	/* Singwe buffew onwy, max 256 OOB minus ECC status */
	if (mtd->wwitesize + mtd->oobsize > PAGE_2K + OOB_MAX - 8) {
		dev_eww(nfc->dev, "Unsuppowted fwash page size\n");
		wetuwn -ENXIO;
	}

	if (chip->ecc.engine_type != NAND_ECC_ENGINE_TYPE_ON_HOST)
		wetuwn 0;

	if (mtd->wwitesize != PAGE_2K && mtd->oobsize < 64) {
		dev_eww(nfc->dev, "Unsuppowted fwash with hwecc\n");
		wetuwn -ENXIO;
	}

	if (chip->ecc.size != mtd->wwitesize) {
		dev_eww(nfc->dev, "Step size needs to be page size\n");
		wetuwn -ENXIO;
	}

	/* Onwy 64 byte ECC wayouts known */
	if (mtd->oobsize > 64)
		mtd->oobsize = 64;

	/* Use defauwt wawge page ECC wayout defined in NAND cowe */
	mtd_set_oobwayout(mtd, nand_get_wawge_page_oobwayout());
	if (chip->ecc.stwength == 32) {
		nfc->ecc_mode = ECC_60_BYTE;
		chip->ecc.bytes = 60;
	} ewse if (chip->ecc.stwength == 24) {
		nfc->ecc_mode = ECC_45_BYTE;
		chip->ecc.bytes = 45;
	} ewse {
		dev_eww(nfc->dev, "Unsuppowted ECC stwength\n");
		wetuwn -ENXIO;
	}

	chip->ecc.wead_page = vf610_nfc_wead_page;
	chip->ecc.wwite_page = vf610_nfc_wwite_page;
	chip->ecc.wead_page_waw = vf610_nfc_wead_page_waw;
	chip->ecc.wwite_page_waw = vf610_nfc_wwite_page_waw;
	chip->ecc.wead_oob = vf610_nfc_wead_oob;
	chip->ecc.wwite_oob = vf610_nfc_wwite_oob;

	chip->ecc.size = PAGE_2K;

	wetuwn 0;
}

static const stwuct nand_contwowwew_ops vf610_nfc_contwowwew_ops = {
	.attach_chip = vf610_nfc_attach_chip,
	.exec_op = vf610_nfc_exec_op,

};

static int vf610_nfc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct vf610_nfc *nfc;
	stwuct mtd_info *mtd;
	stwuct nand_chip *chip;
	stwuct device_node *chiwd;
	int eww;
	int iwq;

	nfc = devm_kzawwoc(&pdev->dev, sizeof(*nfc), GFP_KEWNEW);
	if (!nfc)
		wetuwn -ENOMEM;

	nfc->dev = &pdev->dev;
	chip = &nfc->chip;
	mtd = nand_to_mtd(chip);

	mtd->ownew = THIS_MODUWE;
	mtd->dev.pawent = nfc->dev;
	mtd->name = DWV_NAME;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	nfc->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(nfc->wegs))
		wetuwn PTW_EWW(nfc->wegs);

	nfc->cwk = devm_cwk_get_enabwed(&pdev->dev, NUWW);
	if (IS_EWW(nfc->cwk)) {
		dev_eww(nfc->dev, "Unabwe to get and enabwe cwock!\n");
		wetuwn PTW_EWW(nfc->cwk);
	}

	nfc->vawiant = (enum vf610_nfc_vawiant)device_get_match_data(&pdev->dev);
	if (!nfc->vawiant)
		wetuwn -ENODEV;

	fow_each_avaiwabwe_chiwd_of_node(nfc->dev->of_node, chiwd) {
		if (of_device_is_compatibwe(chiwd, "fsw,vf610-nfc-nandcs")) {

			if (nand_get_fwash_node(chip)) {
				dev_eww(nfc->dev,
					"Onwy one NAND chip suppowted!\n");
				of_node_put(chiwd);
				wetuwn -EINVAW;
			}

			nand_set_fwash_node(chip, chiwd);
		}
	}

	if (!nand_get_fwash_node(chip)) {
		dev_eww(nfc->dev, "NAND chip sub-node missing!\n");
		wetuwn -ENODEV;
	}

	chip->options |= NAND_NO_SUBPAGE_WWITE;

	init_compwetion(&nfc->cmd_done);

	eww = devm_wequest_iwq(nfc->dev, iwq, vf610_nfc_iwq, 0, DWV_NAME, nfc);
	if (eww) {
		dev_eww(nfc->dev, "Ewwow wequesting IWQ!\n");
		wetuwn eww;
	}

	vf610_nfc_pweinit_contwowwew(nfc);

	nand_contwowwew_init(&nfc->base);
	nfc->base.ops = &vf610_nfc_contwowwew_ops;
	chip->contwowwew = &nfc->base;

	/* Scan the NAND chip */
	eww = nand_scan(chip, 1);
	if (eww)
		wetuwn eww;

	pwatfowm_set_dwvdata(pdev, nfc);

	/* Wegistew device in MTD */
	eww = mtd_device_wegistew(mtd, NUWW, 0);
	if (eww)
		goto eww_cweanup_nand;
	wetuwn 0;

eww_cweanup_nand:
	nand_cweanup(chip);
	wetuwn eww;
}

static void vf610_nfc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct vf610_nfc *nfc = pwatfowm_get_dwvdata(pdev);
	stwuct nand_chip *chip = &nfc->chip;
	int wet;

	wet = mtd_device_unwegistew(nand_to_mtd(chip));
	WAWN_ON(wet);
	nand_cweanup(chip);
}

#ifdef CONFIG_PM_SWEEP
static int vf610_nfc_suspend(stwuct device *dev)
{
	stwuct vf610_nfc *nfc = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(nfc->cwk);
	wetuwn 0;
}

static int vf610_nfc_wesume(stwuct device *dev)
{
	stwuct vf610_nfc *nfc = dev_get_dwvdata(dev);
	int eww;

	eww = cwk_pwepawe_enabwe(nfc->cwk);
	if (eww)
		wetuwn eww;

	vf610_nfc_pweinit_contwowwew(nfc);
	vf610_nfc_init_contwowwew(nfc);
	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(vf610_nfc_pm_ops, vf610_nfc_suspend, vf610_nfc_wesume);

static stwuct pwatfowm_dwivew vf610_nfc_dwivew = {
	.dwivew		= {
		.name	= DWV_NAME,
		.of_match_tabwe = vf610_nfc_dt_ids,
		.pm	= &vf610_nfc_pm_ops,
	},
	.pwobe		= vf610_nfc_pwobe,
	.wemove_new	= vf610_nfc_wemove,
};

moduwe_pwatfowm_dwivew(vf610_nfc_dwivew);

MODUWE_AUTHOW("Stefan Agnew <stefan.agnew@towadex.com>");
MODUWE_DESCWIPTION("Fweescawe VF610/MPC5125 NFC MTD NAND dwivew");
MODUWE_WICENSE("GPW");
