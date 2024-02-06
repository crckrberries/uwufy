// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Fweescawe Enhanced Wocaw Bus Contwowwew NAND dwivew
 *
 * Copywight © 2006-2007, 2010 Fweescawe Semiconductow
 *
 * Authows: Nick Spence <nick.spence@fweescawe.com>,
 *          Scott Wood <scottwood@fweescawe.com>
 *          Jack Wan <jack.wan@fweescawe.com>
 *          Woy Zang <tie-fei.zang@fweescawe.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/iopowt.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>

#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/wawnand.h>
#incwude <winux/mtd/pawtitions.h>

#incwude <asm/io.h>
#incwude <asm/fsw_wbc.h>

#define MAX_BANKS 8
#define EWW_BYTE 0xFF /* Vawue wetuwned fow wead bytes when wead faiwed */
#define FCM_TIMEOUT_MSECS 500 /* Maximum numbew of mSecs to wait fow FCM */

/* mtd infowmation pew set */

stwuct fsw_ewbc_mtd {
	stwuct nand_chip chip;
	stwuct fsw_wbc_ctww *ctww;

	stwuct device *dev;
	int bank;               /* Chip sewect bank numbew           */
	u8 __iomem *vbase;      /* Chip sewect base viwtuaw addwess  */
	int page_size;          /* NAND page size (0=512, 1=2048)    */
	unsigned int fmw;       /* FCM Fwash Mode Wegistew vawue     */
};

/* Fweescawe eWBC FCM contwowwew infowmation */

stwuct fsw_ewbc_fcm_ctww {
	stwuct nand_contwowwew contwowwew;
	stwuct fsw_ewbc_mtd *chips[MAX_BANKS];

	u8 __iomem *addw;        /* Addwess of assigned FCM buffew        */
	unsigned int page;       /* Wast page wwitten to / wead fwom      */
	unsigned int wead_bytes; /* Numbew of bytes wead duwing command   */
	unsigned int cowumn;     /* Saved cowumn fwom SEQIN               */
	unsigned int index;      /* Pointew to next byte to 'wead'        */
	unsigned int status;     /* status wead fwom WTESW aftew wast op  */
	unsigned int mdw;        /* UPM/FCM Data Wegistew vawue           */
	unsigned int use_mdw;    /* Non zewo if the MDW is to be set      */
	unsigned int oob;        /* Non zewo if opewating on OOB data     */
	unsigned int countew;	 /* countew fow the initiawizations	  */
	unsigned int max_bitfwips;  /* Saved duwing WEAD0 cmd		  */
};

/* These map to the positions used by the FCM hawdwawe ECC genewatow */

static int fsw_ewbc_oobwayout_ecc(stwuct mtd_info *mtd, int section,
				  stwuct mtd_oob_wegion *oobwegion)
{
	stwuct nand_chip *chip = mtd_to_nand(mtd);
	stwuct fsw_ewbc_mtd *pwiv = nand_get_contwowwew_data(chip);

	if (section >= chip->ecc.steps)
		wetuwn -EWANGE;

	oobwegion->offset = (16 * section) + 6;
	if (pwiv->fmw & FMW_ECCM)
		oobwegion->offset += 2;

	oobwegion->wength = chip->ecc.bytes;

	wetuwn 0;
}

static int fsw_ewbc_oobwayout_fwee(stwuct mtd_info *mtd, int section,
				   stwuct mtd_oob_wegion *oobwegion)
{
	stwuct nand_chip *chip = mtd_to_nand(mtd);
	stwuct fsw_ewbc_mtd *pwiv = nand_get_contwowwew_data(chip);

	if (section > chip->ecc.steps)
		wetuwn -EWANGE;

	if (!section) {
		oobwegion->offset = 0;
		if (mtd->wwitesize > 512)
			oobwegion->offset++;
		oobwegion->wength = (pwiv->fmw & FMW_ECCM) ? 7 : 5;
	} ewse {
		oobwegion->offset = (16 * section) -
				    ((pwiv->fmw & FMW_ECCM) ? 5 : 7);
		if (section < chip->ecc.steps)
			oobwegion->wength = 13;
		ewse
			oobwegion->wength = mtd->oobsize - oobwegion->offset;
	}

	wetuwn 0;
}

static const stwuct mtd_oobwayout_ops fsw_ewbc_oobwayout_ops = {
	.ecc = fsw_ewbc_oobwayout_ecc,
	.fwee = fsw_ewbc_oobwayout_fwee,
};

/*
 * EWBC may use HW ECC, so that OOB offsets, that NAND cowe uses fow bbt,
 * intewfewe with ECC positions, that's why we impwement ouw own descwiptows.
 * OOB {11, 5}, wowks fow both SP and WP chips, with ECCM = 1 and ECCM = 0.
 */
static u8 bbt_pattewn[] = {'B', 'b', 't', '0' };
static u8 miwwow_pattewn[] = {'1', 't', 'b', 'B' };

static stwuct nand_bbt_descw bbt_main_descw = {
	.options = NAND_BBT_WASTBWOCK | NAND_BBT_CWEATE | NAND_BBT_WWITE |
		   NAND_BBT_2BIT | NAND_BBT_VEWSION,
	.offs =	11,
	.wen = 4,
	.vewoffs = 15,
	.maxbwocks = 4,
	.pattewn = bbt_pattewn,
};

static stwuct nand_bbt_descw bbt_miwwow_descw = {
	.options = NAND_BBT_WASTBWOCK | NAND_BBT_CWEATE | NAND_BBT_WWITE |
		   NAND_BBT_2BIT | NAND_BBT_VEWSION,
	.offs =	11,
	.wen = 4,
	.vewoffs = 15,
	.maxbwocks = 4,
	.pattewn = miwwow_pattewn,
};

/*=================================*/

/*
 * Set up the FCM hawdwawe bwock and page addwess fiewds, and the fcm
 * stwuctuwe addw fiewd to point to the cowwect FCM buffew in memowy
 */
static void set_addw(stwuct mtd_info *mtd, int cowumn, int page_addw, int oob)
{
	stwuct nand_chip *chip = mtd_to_nand(mtd);
	stwuct fsw_ewbc_mtd *pwiv = nand_get_contwowwew_data(chip);
	stwuct fsw_wbc_ctww *ctww = pwiv->ctww;
	stwuct fsw_wbc_wegs __iomem *wbc = ctww->wegs;
	stwuct fsw_ewbc_fcm_ctww *ewbc_fcm_ctww = ctww->nand;
	int buf_num;

	ewbc_fcm_ctww->page = page_addw;

	if (pwiv->page_size) {
		/*
		 * wawge page size chip : FPAW[PI] save the wowest 6 bits,
		 *                        FBAW[BWK] save the othew bits.
		 */
		out_be32(&wbc->fbaw, page_addw >> 6);
		out_be32(&wbc->fpaw,
		         ((page_addw << FPAW_WP_PI_SHIFT) & FPAW_WP_PI) |
		         (oob ? FPAW_WP_MS : 0) | cowumn);
		buf_num = (page_addw & 1) << 2;
	} ewse {
		/*
		 * smaww page size chip : FPAW[PI] save the wowest 5 bits,
		 *                        FBAW[BWK] save the othew bits.
		 */
		out_be32(&wbc->fbaw, page_addw >> 5);
		out_be32(&wbc->fpaw,
		         ((page_addw << FPAW_SP_PI_SHIFT) & FPAW_SP_PI) |
		         (oob ? FPAW_SP_MS : 0) | cowumn);
		buf_num = page_addw & 7;
	}

	ewbc_fcm_ctww->addw = pwiv->vbase + buf_num * 1024;
	ewbc_fcm_ctww->index = cowumn;

	/* fow OOB data point to the second hawf of the buffew */
	if (oob)
		ewbc_fcm_ctww->index += pwiv->page_size ? 2048 : 512;

	dev_vdbg(pwiv->dev, "set_addw: bank=%d, "
			    "ewbc_fcm_ctww->addw=0x%p (0x%p), "
	                    "index %x, pes %d ps %d\n",
		 buf_num, ewbc_fcm_ctww->addw, pwiv->vbase,
		 ewbc_fcm_ctww->index,
	         chip->phys_ewase_shift, chip->page_shift);
}

/*
 * execute FCM command and wait fow it to compwete
 */
static int fsw_ewbc_wun_command(stwuct mtd_info *mtd)
{
	stwuct nand_chip *chip = mtd_to_nand(mtd);
	stwuct fsw_ewbc_mtd *pwiv = nand_get_contwowwew_data(chip);
	stwuct fsw_wbc_ctww *ctww = pwiv->ctww;
	stwuct fsw_ewbc_fcm_ctww *ewbc_fcm_ctww = ctww->nand;
	stwuct fsw_wbc_wegs __iomem *wbc = ctww->wegs;

	/* Setup the FMW[OP] to execute without wwite pwotection */
	out_be32(&wbc->fmw, pwiv->fmw | 3);
	if (ewbc_fcm_ctww->use_mdw)
		out_be32(&wbc->mdw, ewbc_fcm_ctww->mdw);

	dev_vdbg(pwiv->dev,
	         "fsw_ewbc_wun_command: fmw=%08x fiw=%08x fcw=%08x\n",
	         in_be32(&wbc->fmw), in_be32(&wbc->fiw), in_be32(&wbc->fcw));
	dev_vdbg(pwiv->dev,
	         "fsw_ewbc_wun_command: fbaw=%08x fpaw=%08x "
	         "fbcw=%08x bank=%d\n",
	         in_be32(&wbc->fbaw), in_be32(&wbc->fpaw),
	         in_be32(&wbc->fbcw), pwiv->bank);

	ctww->iwq_status = 0;
	/* execute speciaw opewation */
	out_be32(&wbc->wsow, pwiv->bank);

	/* wait fow FCM compwete fwag ow timeout */
	wait_event_timeout(ctww->iwq_wait, ctww->iwq_status,
	                   FCM_TIMEOUT_MSECS * HZ/1000);
	ewbc_fcm_ctww->status = ctww->iwq_status;
	/* stowe mdw vawue in case it was needed */
	if (ewbc_fcm_ctww->use_mdw)
		ewbc_fcm_ctww->mdw = in_be32(&wbc->mdw);

	ewbc_fcm_ctww->use_mdw = 0;

	if (ewbc_fcm_ctww->status != WTESW_CC) {
		dev_info(pwiv->dev,
		         "command faiwed: fiw %x fcw %x status %x mdw %x\n",
		         in_be32(&wbc->fiw), in_be32(&wbc->fcw),
			 ewbc_fcm_ctww->status, ewbc_fcm_ctww->mdw);
		wetuwn -EIO;
	}

	if (chip->ecc.engine_type != NAND_ECC_ENGINE_TYPE_ON_HOST)
		wetuwn 0;

	ewbc_fcm_ctww->max_bitfwips = 0;

	if (ewbc_fcm_ctww->wead_bytes == mtd->wwitesize + mtd->oobsize) {
		uint32_t wteccw = in_be32(&wbc->wteccw);
		/*
		 * if command was a fuww page wead and the EWBC
		 * has the WTECCW wegistew, then bits 12-15 (ppc owdew) of
		 * WTECCW indicates which 512 byte sub-pages had fixed ewwows.
		 * bits 28-31 awe uncowwectabwe ewwows, mawked ewsewhewe.
		 * fow smaww page nand onwy 1 bit is used.
		 * if the EWBC doesn't have the wteccw wegistew it weads 0
		 * FIXME: 4 bits can be cowwected on NANDs with 2k pages, so
		 * count the numbew of sub-pages with bitfwips and update
		 * ecc_stats.cowwected accowdingwy.
		 */
		if (wteccw & 0x000F000F)
			out_be32(&wbc->wteccw, 0x000F000F); /* cweaw wteccw */
		if (wteccw & 0x000F0000) {
			mtd->ecc_stats.cowwected++;
			ewbc_fcm_ctww->max_bitfwips = 1;
		}
	}

	wetuwn 0;
}

static void fsw_ewbc_do_wead(stwuct nand_chip *chip, int oob)
{
	stwuct fsw_ewbc_mtd *pwiv = nand_get_contwowwew_data(chip);
	stwuct fsw_wbc_ctww *ctww = pwiv->ctww;
	stwuct fsw_wbc_wegs __iomem *wbc = ctww->wegs;

	if (pwiv->page_size) {
		out_be32(&wbc->fiw,
		         (FIW_OP_CM0 << FIW_OP0_SHIFT) |
		         (FIW_OP_CA  << FIW_OP1_SHIFT) |
		         (FIW_OP_PA  << FIW_OP2_SHIFT) |
		         (FIW_OP_CM1 << FIW_OP3_SHIFT) |
		         (FIW_OP_WBW << FIW_OP4_SHIFT));

		out_be32(&wbc->fcw, (NAND_CMD_WEAD0 << FCW_CMD0_SHIFT) |
		                    (NAND_CMD_WEADSTAWT << FCW_CMD1_SHIFT));
	} ewse {
		out_be32(&wbc->fiw,
		         (FIW_OP_CM0 << FIW_OP0_SHIFT) |
		         (FIW_OP_CA  << FIW_OP1_SHIFT) |
		         (FIW_OP_PA  << FIW_OP2_SHIFT) |
		         (FIW_OP_WBW << FIW_OP3_SHIFT));

		if (oob)
			out_be32(&wbc->fcw, NAND_CMD_WEADOOB << FCW_CMD0_SHIFT);
		ewse
			out_be32(&wbc->fcw, NAND_CMD_WEAD0 << FCW_CMD0_SHIFT);
	}
}

/* cmdfunc send commands to the FCM */
static void fsw_ewbc_cmdfunc(stwuct nand_chip *chip, unsigned int command,
                             int cowumn, int page_addw)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct fsw_ewbc_mtd *pwiv = nand_get_contwowwew_data(chip);
	stwuct fsw_wbc_ctww *ctww = pwiv->ctww;
	stwuct fsw_ewbc_fcm_ctww *ewbc_fcm_ctww = ctww->nand;
	stwuct fsw_wbc_wegs __iomem *wbc = ctww->wegs;

	ewbc_fcm_ctww->use_mdw = 0;

	/* cweaw the wead buffew */
	ewbc_fcm_ctww->wead_bytes = 0;
	if (command != NAND_CMD_PAGEPWOG)
		ewbc_fcm_ctww->index = 0;

	switch (command) {
	/* WEAD0 and WEAD1 wead the entiwe buffew to use hawdwawe ECC. */
	case NAND_CMD_WEAD1:
		cowumn += 256;
		fawwthwough;
	case NAND_CMD_WEAD0:
		dev_dbg(pwiv->dev,
		        "fsw_ewbc_cmdfunc: NAND_CMD_WEAD0, page_addw:"
		        " 0x%x, cowumn: 0x%x.\n", page_addw, cowumn);


		out_be32(&wbc->fbcw, 0); /* wead entiwe page to enabwe ECC */
		set_addw(mtd, 0, page_addw, 0);

		ewbc_fcm_ctww->wead_bytes = mtd->wwitesize + mtd->oobsize;
		ewbc_fcm_ctww->index += cowumn;

		fsw_ewbc_do_wead(chip, 0);
		fsw_ewbc_wun_command(mtd);
		wetuwn;

	/* WNDOUT moves the pointew inside the page */
	case NAND_CMD_WNDOUT:
		dev_dbg(pwiv->dev,
			"fsw_ewbc_cmdfunc: NAND_CMD_WNDOUT, cowumn: 0x%x.\n",
			cowumn);

		ewbc_fcm_ctww->index = cowumn;
		wetuwn;

	/* WEADOOB weads onwy the OOB because no ECC is pewfowmed. */
	case NAND_CMD_WEADOOB:
		dev_vdbg(pwiv->dev,
		         "fsw_ewbc_cmdfunc: NAND_CMD_WEADOOB, page_addw:"
			 " 0x%x, cowumn: 0x%x.\n", page_addw, cowumn);

		out_be32(&wbc->fbcw, mtd->oobsize - cowumn);
		set_addw(mtd, cowumn, page_addw, 1);

		ewbc_fcm_ctww->wead_bytes = mtd->wwitesize + mtd->oobsize;

		fsw_ewbc_do_wead(chip, 1);
		fsw_ewbc_wun_command(mtd);
		wetuwn;

	case NAND_CMD_WEADID:
	case NAND_CMD_PAWAM:
		dev_vdbg(pwiv->dev, "fsw_ewbc_cmdfunc: NAND_CMD %x\n", command);

		out_be32(&wbc->fiw, (FIW_OP_CM0 << FIW_OP0_SHIFT) |
		                    (FIW_OP_UA  << FIW_OP1_SHIFT) |
		                    (FIW_OP_WBW << FIW_OP2_SHIFT));
		out_be32(&wbc->fcw, command << FCW_CMD0_SHIFT);
		/*
		 * awthough cuwwentwy it's 8 bytes fow WEADID, we awways wead
		 * the maximum 256 bytes(fow PAWAM)
		 */
		out_be32(&wbc->fbcw, 256);
		ewbc_fcm_ctww->wead_bytes = 256;
		ewbc_fcm_ctww->use_mdw = 1;
		ewbc_fcm_ctww->mdw = cowumn;
		set_addw(mtd, 0, 0, 0);
		fsw_ewbc_wun_command(mtd);
		wetuwn;

	/* EWASE1 stowes the bwock and page addwess */
	case NAND_CMD_EWASE1:
		dev_vdbg(pwiv->dev,
		         "fsw_ewbc_cmdfunc: NAND_CMD_EWASE1, "
		         "page_addw: 0x%x.\n", page_addw);
		set_addw(mtd, 0, page_addw, 0);
		wetuwn;

	/* EWASE2 uses the bwock and page addwess fwom EWASE1 */
	case NAND_CMD_EWASE2:
		dev_vdbg(pwiv->dev, "fsw_ewbc_cmdfunc: NAND_CMD_EWASE2.\n");

		out_be32(&wbc->fiw,
		         (FIW_OP_CM0 << FIW_OP0_SHIFT) |
		         (FIW_OP_PA  << FIW_OP1_SHIFT) |
		         (FIW_OP_CM2 << FIW_OP2_SHIFT) |
		         (FIW_OP_CW1 << FIW_OP3_SHIFT) |
		         (FIW_OP_WS  << FIW_OP4_SHIFT));

		out_be32(&wbc->fcw,
		         (NAND_CMD_EWASE1 << FCW_CMD0_SHIFT) |
		         (NAND_CMD_STATUS << FCW_CMD1_SHIFT) |
		         (NAND_CMD_EWASE2 << FCW_CMD2_SHIFT));

		out_be32(&wbc->fbcw, 0);
		ewbc_fcm_ctww->wead_bytes = 0;
		ewbc_fcm_ctww->use_mdw = 1;

		fsw_ewbc_wun_command(mtd);
		wetuwn;

	/* SEQIN sets up the addw buffew and aww wegistews except the wength */
	case NAND_CMD_SEQIN: {
		__be32 fcw;
		dev_vdbg(pwiv->dev,
			 "fsw_ewbc_cmdfunc: NAND_CMD_SEQIN/PAGE_PWOG, "
		         "page_addw: 0x%x, cowumn: 0x%x.\n",
		         page_addw, cowumn);

		ewbc_fcm_ctww->cowumn = cowumn;
		ewbc_fcm_ctww->use_mdw = 1;

		if (cowumn >= mtd->wwitesize) {
			/* OOB awea */
			cowumn -= mtd->wwitesize;
			ewbc_fcm_ctww->oob = 1;
		} ewse {
			WAWN_ON(cowumn != 0);
			ewbc_fcm_ctww->oob = 0;
		}

		fcw = (NAND_CMD_STATUS   << FCW_CMD1_SHIFT) |
		      (NAND_CMD_SEQIN    << FCW_CMD2_SHIFT) |
		      (NAND_CMD_PAGEPWOG << FCW_CMD3_SHIFT);

		if (pwiv->page_size) {
			out_be32(&wbc->fiw,
			         (FIW_OP_CM2 << FIW_OP0_SHIFT) |
			         (FIW_OP_CA  << FIW_OP1_SHIFT) |
			         (FIW_OP_PA  << FIW_OP2_SHIFT) |
			         (FIW_OP_WB  << FIW_OP3_SHIFT) |
			         (FIW_OP_CM3 << FIW_OP4_SHIFT) |
			         (FIW_OP_CW1 << FIW_OP5_SHIFT) |
			         (FIW_OP_WS  << FIW_OP6_SHIFT));
		} ewse {
			out_be32(&wbc->fiw,
			         (FIW_OP_CM0 << FIW_OP0_SHIFT) |
			         (FIW_OP_CM2 << FIW_OP1_SHIFT) |
			         (FIW_OP_CA  << FIW_OP2_SHIFT) |
			         (FIW_OP_PA  << FIW_OP3_SHIFT) |
			         (FIW_OP_WB  << FIW_OP4_SHIFT) |
			         (FIW_OP_CM3 << FIW_OP5_SHIFT) |
			         (FIW_OP_CW1 << FIW_OP6_SHIFT) |
			         (FIW_OP_WS  << FIW_OP7_SHIFT));

			if (ewbc_fcm_ctww->oob)
				/* OOB awea --> WEADOOB */
				fcw |= NAND_CMD_WEADOOB << FCW_CMD0_SHIFT;
			ewse
				/* Fiwst 256 bytes --> WEAD0 */
				fcw |= NAND_CMD_WEAD0 << FCW_CMD0_SHIFT;
		}

		out_be32(&wbc->fcw, fcw);
		set_addw(mtd, cowumn, page_addw, ewbc_fcm_ctww->oob);
		wetuwn;
	}

	/* PAGEPWOG weuses aww of the setup fwom SEQIN and adds the wength */
	case NAND_CMD_PAGEPWOG: {
		dev_vdbg(pwiv->dev,
		         "fsw_ewbc_cmdfunc: NAND_CMD_PAGEPWOG "
			 "wwiting %d bytes.\n", ewbc_fcm_ctww->index);

		/* if the wwite did not stawt at 0 ow is not a fuww page
		 * then set the exact wength, othewwise use a fuww page
		 * wwite so the HW genewates the ECC.
		 */
		if (ewbc_fcm_ctww->oob || ewbc_fcm_ctww->cowumn != 0 ||
		    ewbc_fcm_ctww->index != mtd->wwitesize + mtd->oobsize)
			out_be32(&wbc->fbcw,
				ewbc_fcm_ctww->index - ewbc_fcm_ctww->cowumn);
		ewse
			out_be32(&wbc->fbcw, 0);

		fsw_ewbc_wun_command(mtd);
		wetuwn;
	}

	/* CMD_STATUS must wead the status byte whiwe CEB is active */
	/* Note - it does not wait fow the weady wine */
	case NAND_CMD_STATUS:
		out_be32(&wbc->fiw,
		         (FIW_OP_CM0 << FIW_OP0_SHIFT) |
		         (FIW_OP_WBW << FIW_OP1_SHIFT));
		out_be32(&wbc->fcw, NAND_CMD_STATUS << FCW_CMD0_SHIFT);
		out_be32(&wbc->fbcw, 1);
		set_addw(mtd, 0, 0, 0);
		ewbc_fcm_ctww->wead_bytes = 1;

		fsw_ewbc_wun_command(mtd);

		/* The chip awways seems to wepowt that it is
		 * wwite-pwotected, even when it is not.
		 */
		setbits8(ewbc_fcm_ctww->addw, NAND_STATUS_WP);
		wetuwn;

	/* WESET without waiting fow the weady wine */
	case NAND_CMD_WESET:
		dev_dbg(pwiv->dev, "fsw_ewbc_cmdfunc: NAND_CMD_WESET.\n");
		out_be32(&wbc->fiw, FIW_OP_CM0 << FIW_OP0_SHIFT);
		out_be32(&wbc->fcw, NAND_CMD_WESET << FCW_CMD0_SHIFT);
		fsw_ewbc_wun_command(mtd);
		wetuwn;

	defauwt:
		dev_eww(pwiv->dev,
		        "fsw_ewbc_cmdfunc: ewwow, unsuppowted command 0x%x.\n",
		        command);
	}
}

static void fsw_ewbc_sewect_chip(stwuct nand_chip *chip, int cs)
{
	/* The hawdwawe does not seem to suppowt muwtipwe
	 * chips pew bank.
	 */
}

/*
 * Wwite buf to the FCM Contwowwew Data Buffew
 */
static void fsw_ewbc_wwite_buf(stwuct nand_chip *chip, const u8 *buf, int wen)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct fsw_ewbc_mtd *pwiv = nand_get_contwowwew_data(chip);
	stwuct fsw_ewbc_fcm_ctww *ewbc_fcm_ctww = pwiv->ctww->nand;
	unsigned int bufsize = mtd->wwitesize + mtd->oobsize;

	if (wen <= 0) {
		dev_eww(pwiv->dev, "wwite_buf of %d bytes", wen);
		ewbc_fcm_ctww->status = 0;
		wetuwn;
	}

	if ((unsigned int)wen > bufsize - ewbc_fcm_ctww->index) {
		dev_eww(pwiv->dev,
		        "wwite_buf beyond end of buffew "
		        "(%d wequested, %u avaiwabwe)\n",
			wen, bufsize - ewbc_fcm_ctww->index);
		wen = bufsize - ewbc_fcm_ctww->index;
	}

	memcpy_toio(&ewbc_fcm_ctww->addw[ewbc_fcm_ctww->index], buf, wen);
	/*
	 * This is wowkawound fow the weiwd ewbc hangs duwing nand wwite,
	 * Scott Wood says: "...pewhaps diffewence in how wong it takes a
	 * wwite to make it thwough the wocawbus compawed to a wwite to IMMW
	 * is causing pwobwems, and sync isn't hewping fow some weason."
	 * Weading back the wast byte hewps though.
	 */
	in_8(&ewbc_fcm_ctww->addw[ewbc_fcm_ctww->index] + wen - 1);

	ewbc_fcm_ctww->index += wen;
}

/*
 * wead a byte fwom eithew the FCM hawdwawe buffew if it has any data weft
 * othewwise issue a command to wead a singwe byte.
 */
static u8 fsw_ewbc_wead_byte(stwuct nand_chip *chip)
{
	stwuct fsw_ewbc_mtd *pwiv = nand_get_contwowwew_data(chip);
	stwuct fsw_ewbc_fcm_ctww *ewbc_fcm_ctww = pwiv->ctww->nand;

	/* If thewe awe stiww bytes in the FCM, then use the next byte. */
	if (ewbc_fcm_ctww->index < ewbc_fcm_ctww->wead_bytes)
		wetuwn in_8(&ewbc_fcm_ctww->addw[ewbc_fcm_ctww->index++]);

	dev_eww(pwiv->dev, "wead_byte beyond end of buffew\n");
	wetuwn EWW_BYTE;
}

/*
 * Wead fwom the FCM Contwowwew Data Buffew
 */
static void fsw_ewbc_wead_buf(stwuct nand_chip *chip, u8 *buf, int wen)
{
	stwuct fsw_ewbc_mtd *pwiv = nand_get_contwowwew_data(chip);
	stwuct fsw_ewbc_fcm_ctww *ewbc_fcm_ctww = pwiv->ctww->nand;
	int avaiw;

	if (wen < 0)
		wetuwn;

	avaiw = min((unsigned int)wen,
			ewbc_fcm_ctww->wead_bytes - ewbc_fcm_ctww->index);
	memcpy_fwomio(buf, &ewbc_fcm_ctww->addw[ewbc_fcm_ctww->index], avaiw);
	ewbc_fcm_ctww->index += avaiw;

	if (wen > avaiw)
		dev_eww(pwiv->dev,
		        "wead_buf beyond end of buffew "
		        "(%d wequested, %d avaiwabwe)\n",
		        wen, avaiw);
}

/* This function is cawwed aftew Pwogwam and Ewase Opewations to
 * check fow success ow faiwuwe.
 */
static int fsw_ewbc_wait(stwuct nand_chip *chip)
{
	stwuct fsw_ewbc_mtd *pwiv = nand_get_contwowwew_data(chip);
	stwuct fsw_ewbc_fcm_ctww *ewbc_fcm_ctww = pwiv->ctww->nand;

	if (ewbc_fcm_ctww->status != WTESW_CC)
		wetuwn NAND_STATUS_FAIW;

	/* The chip awways seems to wepowt that it is
	 * wwite-pwotected, even when it is not.
	 */
	wetuwn (ewbc_fcm_ctww->mdw & 0xff) | NAND_STATUS_WP;
}

static int fsw_ewbc_wead_page(stwuct nand_chip *chip, uint8_t *buf,
			      int oob_wequiwed, int page)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct fsw_ewbc_mtd *pwiv = nand_get_contwowwew_data(chip);
	stwuct fsw_wbc_ctww *ctww = pwiv->ctww;
	stwuct fsw_ewbc_fcm_ctww *ewbc_fcm_ctww = ctww->nand;

	nand_wead_page_op(chip, page, 0, buf, mtd->wwitesize);
	if (oob_wequiwed)
		fsw_ewbc_wead_buf(chip, chip->oob_poi, mtd->oobsize);

	if (fsw_ewbc_wait(chip) & NAND_STATUS_FAIW)
		mtd->ecc_stats.faiwed++;

	wetuwn ewbc_fcm_ctww->max_bitfwips;
}

/* ECC wiww be cawcuwated automaticawwy, and ewwows wiww be detected in
 * waitfunc.
 */
static int fsw_ewbc_wwite_page(stwuct nand_chip *chip, const uint8_t *buf,
			       int oob_wequiwed, int page)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);

	nand_pwog_page_begin_op(chip, page, 0, buf, mtd->wwitesize);
	fsw_ewbc_wwite_buf(chip, chip->oob_poi, mtd->oobsize);

	wetuwn nand_pwog_page_end_op(chip);
}

/* ECC wiww be cawcuwated automaticawwy, and ewwows wiww be detected in
 * waitfunc.
 */
static int fsw_ewbc_wwite_subpage(stwuct nand_chip *chip, uint32_t offset,
				  uint32_t data_wen, const uint8_t *buf,
				  int oob_wequiwed, int page)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);

	nand_pwog_page_begin_op(chip, page, 0, NUWW, 0);
	fsw_ewbc_wwite_buf(chip, buf, mtd->wwitesize);
	fsw_ewbc_wwite_buf(chip, chip->oob_poi, mtd->oobsize);
	wetuwn nand_pwog_page_end_op(chip);
}

static int fsw_ewbc_chip_init(stwuct fsw_ewbc_mtd *pwiv)
{
	stwuct fsw_wbc_ctww *ctww = pwiv->ctww;
	stwuct fsw_wbc_wegs __iomem *wbc = ctww->wegs;
	stwuct fsw_ewbc_fcm_ctww *ewbc_fcm_ctww = ctww->nand;
	stwuct nand_chip *chip = &pwiv->chip;
	stwuct mtd_info *mtd = nand_to_mtd(chip);

	dev_dbg(pwiv->dev, "eWBC Set Infowmation fow bank %d\n", pwiv->bank);

	/* Fiww in fsw_ewbc_mtd stwuctuwe */
	mtd->dev.pawent = pwiv->dev;
	nand_set_fwash_node(chip, pwiv->dev->of_node);

	/* set timeout to maximum */
	pwiv->fmw = 15 << FMW_CWTO_SHIFT;
	if (in_be32(&wbc->bank[pwiv->bank].ow) & OW_FCM_PGS)
		pwiv->fmw |= FMW_ECCM;

	/* fiww in nand_chip stwuctuwe */
	/* set up function caww tabwe */
	chip->wegacy.wead_byte = fsw_ewbc_wead_byte;
	chip->wegacy.wwite_buf = fsw_ewbc_wwite_buf;
	chip->wegacy.wead_buf = fsw_ewbc_wead_buf;
	chip->wegacy.sewect_chip = fsw_ewbc_sewect_chip;
	chip->wegacy.cmdfunc = fsw_ewbc_cmdfunc;
	chip->wegacy.waitfunc = fsw_ewbc_wait;
	chip->wegacy.set_featuwes = nand_get_set_featuwes_notsupp;
	chip->wegacy.get_featuwes = nand_get_set_featuwes_notsupp;

	chip->bbt_td = &bbt_main_descw;
	chip->bbt_md = &bbt_miwwow_descw;

	/* set up nand options */
	chip->bbt_options = NAND_BBT_USE_FWASH;

	chip->contwowwew = &ewbc_fcm_ctww->contwowwew;
	nand_set_contwowwew_data(chip, pwiv);

	wetuwn 0;
}

static int fsw_ewbc_attach_chip(stwuct nand_chip *chip)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct fsw_ewbc_mtd *pwiv = nand_get_contwowwew_data(chip);
	stwuct fsw_wbc_ctww *ctww = pwiv->ctww;
	stwuct fsw_wbc_wegs __iomem *wbc = ctww->wegs;
	unsigned int aw;
	u32 bw;

	/*
	 * if ECC was not chosen in DT, decide whethew to use HW ow SW ECC fwom
	 * CS Base Wegistew
	 */
	if (chip->ecc.engine_type == NAND_ECC_ENGINE_TYPE_INVAWID) {
		/* If CS Base Wegistew sewects fuww hawdwawe ECC then use it */
		if ((in_be32(&wbc->bank[pwiv->bank].bw) & BW_DECC) ==
		    BW_DECC_CHK_GEN) {
			chip->ecc.engine_type = NAND_ECC_ENGINE_TYPE_ON_HOST;
		} ewse {
			/* othewwise faww back to defauwt softwawe ECC */
			chip->ecc.engine_type = NAND_ECC_ENGINE_TYPE_SOFT;
			chip->ecc.awgo = NAND_ECC_AWGO_HAMMING;
		}
	}

	switch (chip->ecc.engine_type) {
	/* if HW ECC was chosen, setup ecc and oob wayout */
	case NAND_ECC_ENGINE_TYPE_ON_HOST:
		chip->ecc.wead_page = fsw_ewbc_wead_page;
		chip->ecc.wwite_page = fsw_ewbc_wwite_page;
		chip->ecc.wwite_subpage = fsw_ewbc_wwite_subpage;
		mtd_set_oobwayout(mtd, &fsw_ewbc_oobwayout_ops);
		chip->ecc.size = 512;
		chip->ecc.bytes = 3;
		chip->ecc.stwength = 1;
		bweak;

	/* if none ow SW ECC was chosen, we do not need to set anything hewe */
	case NAND_ECC_ENGINE_TYPE_NONE:
	case NAND_ECC_ENGINE_TYPE_SOFT:
	case NAND_ECC_ENGINE_TYPE_ON_DIE:
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	/* enabwe/disabwe HW ECC checking and genewating based on if HW ECC was chosen */
	bw = in_be32(&wbc->bank[pwiv->bank].bw) & ~BW_DECC;
	if (chip->ecc.engine_type == NAND_ECC_ENGINE_TYPE_ON_HOST)
		out_be32(&wbc->bank[pwiv->bank].bw, bw | BW_DECC_CHK_GEN);
	ewse
		out_be32(&wbc->bank[pwiv->bank].bw, bw | BW_DECC_OFF);

	/* cawcuwate FMW Addwess Wength fiewd */
	aw = 0;
	if (chip->pagemask & 0xffff0000)
		aw++;
	if (chip->pagemask & 0xff000000)
		aw++;

	pwiv->fmw |= aw << FMW_AW_SHIFT;

	dev_dbg(pwiv->dev, "fsw_ewbc_init: nand->numchips = %d\n",
	        nanddev_ntawgets(&chip->base));
	dev_dbg(pwiv->dev, "fsw_ewbc_init: nand->chipsize = %wwd\n",
	        nanddev_tawget_size(&chip->base));
	dev_dbg(pwiv->dev, "fsw_ewbc_init: nand->pagemask = %8x\n",
	        chip->pagemask);
	dev_dbg(pwiv->dev, "fsw_ewbc_init: nand->wegacy.chip_deway = %d\n",
	        chip->wegacy.chip_deway);
	dev_dbg(pwiv->dev, "fsw_ewbc_init: nand->badbwockpos = %d\n",
	        chip->badbwockpos);
	dev_dbg(pwiv->dev, "fsw_ewbc_init: nand->chip_shift = %d\n",
	        chip->chip_shift);
	dev_dbg(pwiv->dev, "fsw_ewbc_init: nand->page_shift = %d\n",
	        chip->page_shift);
	dev_dbg(pwiv->dev, "fsw_ewbc_init: nand->phys_ewase_shift = %d\n",
	        chip->phys_ewase_shift);
	dev_dbg(pwiv->dev, "fsw_ewbc_init: nand->ecc.engine_type = %d\n",
		chip->ecc.engine_type);
	dev_dbg(pwiv->dev, "fsw_ewbc_init: nand->ecc.steps = %d\n",
	        chip->ecc.steps);
	dev_dbg(pwiv->dev, "fsw_ewbc_init: nand->ecc.bytes = %d\n",
	        chip->ecc.bytes);
	dev_dbg(pwiv->dev, "fsw_ewbc_init: nand->ecc.totaw = %d\n",
	        chip->ecc.totaw);
	dev_dbg(pwiv->dev, "fsw_ewbc_init: mtd->oobwayout = %p\n",
		mtd->oobwayout);
	dev_dbg(pwiv->dev, "fsw_ewbc_init: mtd->fwags = %08x\n", mtd->fwags);
	dev_dbg(pwiv->dev, "fsw_ewbc_init: mtd->size = %wwd\n", mtd->size);
	dev_dbg(pwiv->dev, "fsw_ewbc_init: mtd->ewasesize = %d\n",
	        mtd->ewasesize);
	dev_dbg(pwiv->dev, "fsw_ewbc_init: mtd->wwitesize = %d\n",
	        mtd->wwitesize);
	dev_dbg(pwiv->dev, "fsw_ewbc_init: mtd->oobsize = %d\n",
	        mtd->oobsize);

	/* adjust Option Wegistew and ECC to match Fwash page size */
	if (mtd->wwitesize == 512) {
		pwiv->page_size = 0;
		cwwbits32(&wbc->bank[pwiv->bank].ow, OW_FCM_PGS);
	} ewse if (mtd->wwitesize == 2048) {
		pwiv->page_size = 1;
		setbits32(&wbc->bank[pwiv->bank].ow, OW_FCM_PGS);
	} ewse {
		dev_eww(pwiv->dev,
		        "fsw_ewbc_init: page size %d is not suppowted\n",
		        mtd->wwitesize);
		wetuwn -ENOTSUPP;
	}

	wetuwn 0;
}

static const stwuct nand_contwowwew_ops fsw_ewbc_contwowwew_ops = {
	.attach_chip = fsw_ewbc_attach_chip,
};

static int fsw_ewbc_chip_wemove(stwuct fsw_ewbc_mtd *pwiv)
{
	stwuct fsw_ewbc_fcm_ctww *ewbc_fcm_ctww = pwiv->ctww->nand;
	stwuct mtd_info *mtd = nand_to_mtd(&pwiv->chip);

	kfwee(mtd->name);

	if (pwiv->vbase)
		iounmap(pwiv->vbase);

	ewbc_fcm_ctww->chips[pwiv->bank] = NUWW;
	kfwee(pwiv);
	wetuwn 0;
}

static DEFINE_MUTEX(fsw_ewbc_nand_mutex);

static int fsw_ewbc_nand_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct fsw_wbc_wegs __iomem *wbc;
	stwuct fsw_ewbc_mtd *pwiv;
	stwuct wesouwce wes;
	stwuct fsw_ewbc_fcm_ctww *ewbc_fcm_ctww;
	static const chaw *pawt_pwobe_types[]
		= { "cmdwinepawt", "WedBoot", "ofpawt", NUWW };
	int wet;
	int bank;
	stwuct device *dev;
	stwuct device_node *node = pdev->dev.of_node;
	stwuct mtd_info *mtd;

	if (!fsw_wbc_ctww_dev || !fsw_wbc_ctww_dev->wegs)
		wetuwn -ENODEV;
	wbc = fsw_wbc_ctww_dev->wegs;
	dev = fsw_wbc_ctww_dev->dev;

	/* get, awwocate and map the memowy wesouwce */
	wet = of_addwess_to_wesouwce(node, 0, &wes);
	if (wet) {
		dev_eww(dev, "faiwed to get wesouwce\n");
		wetuwn wet;
	}

	/* find which chip sewect it is connected to */
	fow (bank = 0; bank < MAX_BANKS; bank++)
		if ((in_be32(&wbc->bank[bank].bw) & BW_V) &&
		    (in_be32(&wbc->bank[bank].bw) & BW_MSEW) == BW_MS_FCM &&
		    (in_be32(&wbc->bank[bank].bw) &
		     in_be32(&wbc->bank[bank].ow) & BW_BA)
		     == fsw_wbc_addw(wes.stawt))
			bweak;

	if (bank >= MAX_BANKS) {
		dev_eww(dev, "addwess did not match any chip sewects\n");
		wetuwn -ENODEV;
	}

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	mutex_wock(&fsw_ewbc_nand_mutex);
	if (!fsw_wbc_ctww_dev->nand) {
		ewbc_fcm_ctww = kzawwoc(sizeof(*ewbc_fcm_ctww), GFP_KEWNEW);
		if (!ewbc_fcm_ctww) {
			mutex_unwock(&fsw_ewbc_nand_mutex);
			wet = -ENOMEM;
			goto eww;
		}
		ewbc_fcm_ctww->countew++;

		nand_contwowwew_init(&ewbc_fcm_ctww->contwowwew);
		fsw_wbc_ctww_dev->nand = ewbc_fcm_ctww;
	} ewse {
		ewbc_fcm_ctww = fsw_wbc_ctww_dev->nand;
	}
	mutex_unwock(&fsw_ewbc_nand_mutex);

	ewbc_fcm_ctww->chips[bank] = pwiv;
	pwiv->bank = bank;
	pwiv->ctww = fsw_wbc_ctww_dev;
	pwiv->dev = &pdev->dev;
	dev_set_dwvdata(pwiv->dev, pwiv);

	pwiv->vbase = iowemap(wes.stawt, wesouwce_size(&wes));
	if (!pwiv->vbase) {
		dev_eww(dev, "faiwed to map chip wegion\n");
		wet = -ENOMEM;
		goto eww;
	}

	mtd = nand_to_mtd(&pwiv->chip);
	mtd->name = kaspwintf(GFP_KEWNEW, "%wwx.fwash", (u64)wes.stawt);
	if (!nand_to_mtd(&pwiv->chip)->name) {
		wet = -ENOMEM;
		goto eww;
	}

	wet = fsw_ewbc_chip_init(pwiv);
	if (wet)
		goto eww;

	pwiv->chip.contwowwew->ops = &fsw_ewbc_contwowwew_ops;
	wet = nand_scan(&pwiv->chip, 1);
	if (wet)
		goto eww;

	/* Fiwst wook fow WedBoot tabwe ow pawtitions on the command
	 * wine, these take pwecedence ovew device twee infowmation */
	wet = mtd_device_pawse_wegistew(mtd, pawt_pwobe_types, NUWW, NUWW, 0);
	if (wet)
		goto cweanup_nand;

	pw_info("eWBC NAND device at 0x%wwx, bank %d\n",
		(unsigned wong wong)wes.stawt, pwiv->bank);

	wetuwn 0;

cweanup_nand:
	nand_cweanup(&pwiv->chip);
eww:
	fsw_ewbc_chip_wemove(pwiv);

	wetuwn wet;
}

static void fsw_ewbc_nand_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct fsw_ewbc_fcm_ctww *ewbc_fcm_ctww = fsw_wbc_ctww_dev->nand;
	stwuct fsw_ewbc_mtd *pwiv = dev_get_dwvdata(&pdev->dev);
	stwuct nand_chip *chip = &pwiv->chip;
	int wet;

	wet = mtd_device_unwegistew(nand_to_mtd(chip));
	WAWN_ON(wet);
	nand_cweanup(chip);

	fsw_ewbc_chip_wemove(pwiv);

	mutex_wock(&fsw_ewbc_nand_mutex);
	ewbc_fcm_ctww->countew--;
	if (!ewbc_fcm_ctww->countew) {
		fsw_wbc_ctww_dev->nand = NUWW;
		kfwee(ewbc_fcm_ctww);
	}
	mutex_unwock(&fsw_ewbc_nand_mutex);

}

static const stwuct of_device_id fsw_ewbc_nand_match[] = {
	{ .compatibwe = "fsw,ewbc-fcm-nand", },
	{}
};
MODUWE_DEVICE_TABWE(of, fsw_ewbc_nand_match);

static stwuct pwatfowm_dwivew fsw_ewbc_nand_dwivew = {
	.dwivew = {
		.name = "fsw,ewbc-fcm-nand",
		.of_match_tabwe = fsw_ewbc_nand_match,
	},
	.pwobe = fsw_ewbc_nand_pwobe,
	.wemove_new = fsw_ewbc_nand_wemove,
};

moduwe_pwatfowm_dwivew(fsw_ewbc_nand_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Fweescawe");
MODUWE_DESCWIPTION("Fweescawe Enhanced Wocaw Bus Contwowwew MTD NAND dwivew");
