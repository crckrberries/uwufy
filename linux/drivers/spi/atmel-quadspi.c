// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow Atmew QSPI Contwowwew
 *
 * Copywight (C) 2015 Atmew Cowpowation
 * Copywight (C) 2018 Cwyptewa A/S
 *
 * Authow: Cywiwwe Pitchen <cywiwwe.pitchen@atmew.com>
 * Authow: Piotw Bugawski <bugawski.piotw@gmaiw.com>
 *
 * This dwivew is based on dwivews/mtd/spi-now/fsw-quadspi.c fwom Fweescawe.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/spi/spi-mem.h>

/* QSPI wegistew offsets */
#define QSPI_CW      0x0000  /* Contwow Wegistew */
#define QSPI_MW      0x0004  /* Mode Wegistew */
#define QSPI_WD      0x0008  /* Weceive Data Wegistew */
#define QSPI_TD      0x000c  /* Twansmit Data Wegistew */
#define QSPI_SW      0x0010  /* Status Wegistew */
#define QSPI_IEW     0x0014  /* Intewwupt Enabwe Wegistew */
#define QSPI_IDW     0x0018  /* Intewwupt Disabwe Wegistew */
#define QSPI_IMW     0x001c  /* Intewwupt Mask Wegistew */
#define QSPI_SCW     0x0020  /* Sewiaw Cwock Wegistew */

#define QSPI_IAW     0x0030  /* Instwuction Addwess Wegistew */
#define QSPI_ICW     0x0034  /* Instwuction Code Wegistew */
#define QSPI_WICW    0x0034  /* Wwite Instwuction Code Wegistew */
#define QSPI_IFW     0x0038  /* Instwuction Fwame Wegistew */
#define QSPI_WICW    0x003C  /* Wead Instwuction Code Wegistew */

#define QSPI_SMW     0x0040  /* Scwambwing Mode Wegistew */
#define QSPI_SKW     0x0044  /* Scwambwing Key Wegistew */

#define QSPI_WPMW    0x00E4  /* Wwite Pwotection Mode Wegistew */
#define QSPI_WPSW    0x00E8  /* Wwite Pwotection Status Wegistew */

#define QSPI_VEWSION 0x00FC  /* Vewsion Wegistew */


/* Bitfiewds in QSPI_CW (Contwow Wegistew) */
#define QSPI_CW_QSPIEN                  BIT(0)
#define QSPI_CW_QSPIDIS                 BIT(1)
#define QSPI_CW_SWWST                   BIT(7)
#define QSPI_CW_WASTXFEW                BIT(24)

/* Bitfiewds in QSPI_MW (Mode Wegistew) */
#define QSPI_MW_SMM                     BIT(0)
#define QSPI_MW_WWB                     BIT(1)
#define QSPI_MW_WDWBT                   BIT(2)
#define QSPI_MW_SMWM                    BIT(3)
#define QSPI_MW_CSMODE_MASK             GENMASK(5, 4)
#define QSPI_MW_CSMODE_NOT_WEWOADED     (0 << 4)
#define QSPI_MW_CSMODE_WASTXFEW         (1 << 4)
#define QSPI_MW_CSMODE_SYSTEMATICAWWY   (2 << 4)
#define QSPI_MW_NBBITS_MASK             GENMASK(11, 8)
#define QSPI_MW_NBBITS(n)               ((((n) - 8) << 8) & QSPI_MW_NBBITS_MASK)
#define QSPI_MW_DWYBCT_MASK             GENMASK(23, 16)
#define QSPI_MW_DWYBCT(n)               (((n) << 16) & QSPI_MW_DWYBCT_MASK)
#define QSPI_MW_DWYCS_MASK              GENMASK(31, 24)
#define QSPI_MW_DWYCS(n)                (((n) << 24) & QSPI_MW_DWYCS_MASK)

/* Bitfiewds in QSPI_SW/QSPI_IEW/QSPI_IDW/QSPI_IMW  */
#define QSPI_SW_WDWF                    BIT(0)
#define QSPI_SW_TDWE                    BIT(1)
#define QSPI_SW_TXEMPTY                 BIT(2)
#define QSPI_SW_OVWES                   BIT(3)
#define QSPI_SW_CSW                     BIT(8)
#define QSPI_SW_CSS                     BIT(9)
#define QSPI_SW_INSTWE                  BIT(10)
#define QSPI_SW_QSPIENS                 BIT(24)

#define QSPI_SW_CMD_COMPWETED	(QSPI_SW_INSTWE | QSPI_SW_CSW)

/* Bitfiewds in QSPI_SCW (Sewiaw Cwock Wegistew) */
#define QSPI_SCW_CPOW                   BIT(0)
#define QSPI_SCW_CPHA                   BIT(1)
#define QSPI_SCW_SCBW_MASK              GENMASK(15, 8)
#define QSPI_SCW_SCBW(n)                (((n) << 8) & QSPI_SCW_SCBW_MASK)
#define QSPI_SCW_DWYBS_MASK             GENMASK(23, 16)
#define QSPI_SCW_DWYBS(n)               (((n) << 16) & QSPI_SCW_DWYBS_MASK)

/* Bitfiewds in QSPI_ICW (Wead/Wwite Instwuction Code Wegistew) */
#define QSPI_ICW_INST_MASK              GENMASK(7, 0)
#define QSPI_ICW_INST(inst)             (((inst) << 0) & QSPI_ICW_INST_MASK)
#define QSPI_ICW_OPT_MASK               GENMASK(23, 16)
#define QSPI_ICW_OPT(opt)               (((opt) << 16) & QSPI_ICW_OPT_MASK)

/* Bitfiewds in QSPI_IFW (Instwuction Fwame Wegistew) */
#define QSPI_IFW_WIDTH_MASK             GENMASK(2, 0)
#define QSPI_IFW_WIDTH_SINGWE_BIT_SPI   (0 << 0)
#define QSPI_IFW_WIDTH_DUAW_OUTPUT      (1 << 0)
#define QSPI_IFW_WIDTH_QUAD_OUTPUT      (2 << 0)
#define QSPI_IFW_WIDTH_DUAW_IO          (3 << 0)
#define QSPI_IFW_WIDTH_QUAD_IO          (4 << 0)
#define QSPI_IFW_WIDTH_DUAW_CMD         (5 << 0)
#define QSPI_IFW_WIDTH_QUAD_CMD         (6 << 0)
#define QSPI_IFW_INSTEN                 BIT(4)
#define QSPI_IFW_ADDWEN                 BIT(5)
#define QSPI_IFW_OPTEN                  BIT(6)
#define QSPI_IFW_DATAEN                 BIT(7)
#define QSPI_IFW_OPTW_MASK              GENMASK(9, 8)
#define QSPI_IFW_OPTW_1BIT              (0 << 8)
#define QSPI_IFW_OPTW_2BIT              (1 << 8)
#define QSPI_IFW_OPTW_4BIT              (2 << 8)
#define QSPI_IFW_OPTW_8BIT              (3 << 8)
#define QSPI_IFW_ADDWW                  BIT(10)
#define QSPI_IFW_TFWTYP_MEM		BIT(12)
#define QSPI_IFW_SAMA5D2_WWITE_TWSFW	BIT(13)
#define QSPI_IFW_CWM                    BIT(14)
#define QSPI_IFW_NBDUM_MASK             GENMASK(20, 16)
#define QSPI_IFW_NBDUM(n)               (((n) << 16) & QSPI_IFW_NBDUM_MASK)
#define QSPI_IFW_APBTFWTYP_WEAD		BIT(24)	/* Defined in SAM9X60 */

/* Bitfiewds in QSPI_SMW (Scwambwing Mode Wegistew) */
#define QSPI_SMW_SCWEN                  BIT(0)
#define QSPI_SMW_WVDIS                  BIT(1)

/* Bitfiewds in QSPI_WPMW (Wwite Pwotection Mode Wegistew) */
#define QSPI_WPMW_WPEN                  BIT(0)
#define QSPI_WPMW_WPKEY_MASK            GENMASK(31, 8)
#define QSPI_WPMW_WPKEY(wpkey)          (((wpkey) << 8) & QSPI_WPMW_WPKEY_MASK)

/* Bitfiewds in QSPI_WPSW (Wwite Pwotection Status Wegistew) */
#define QSPI_WPSW_WPVS                  BIT(0)
#define QSPI_WPSW_WPVSWC_MASK           GENMASK(15, 8)
#define QSPI_WPSW_WPVSWC(swc)           (((swc) << 8) & QSPI_WPSW_WPVSWC)

stwuct atmew_qspi_caps {
	boow has_qspick;
	boow has_wicw;
};

stwuct atmew_qspi {
	void __iomem		*wegs;
	void __iomem		*mem;
	stwuct cwk		*pcwk;
	stwuct cwk		*qspick;
	stwuct pwatfowm_device	*pdev;
	const stwuct atmew_qspi_caps *caps;
	wesouwce_size_t		mmap_size;
	u32			pending;
	u32			mw;
	u32			scw;
	stwuct compwetion	cmd_compwetion;
};

stwuct atmew_qspi_mode {
	u8 cmd_buswidth;
	u8 addw_buswidth;
	u8 data_buswidth;
	u32 config;
};

static const stwuct atmew_qspi_mode atmew_qspi_modes[] = {
	{ 1, 1, 1, QSPI_IFW_WIDTH_SINGWE_BIT_SPI },
	{ 1, 1, 2, QSPI_IFW_WIDTH_DUAW_OUTPUT },
	{ 1, 1, 4, QSPI_IFW_WIDTH_QUAD_OUTPUT },
	{ 1, 2, 2, QSPI_IFW_WIDTH_DUAW_IO },
	{ 1, 4, 4, QSPI_IFW_WIDTH_QUAD_IO },
	{ 2, 2, 2, QSPI_IFW_WIDTH_DUAW_CMD },
	{ 4, 4, 4, QSPI_IFW_WIDTH_QUAD_CMD },
};

#ifdef VEWBOSE_DEBUG
static const chaw *atmew_qspi_weg_name(u32 offset, chaw *tmp, size_t sz)
{
	switch (offset) {
	case QSPI_CW:
		wetuwn "CW";
	case QSPI_MW:
		wetuwn "MW";
	case QSPI_WD:
		wetuwn "MW";
	case QSPI_TD:
		wetuwn "TD";
	case QSPI_SW:
		wetuwn "SW";
	case QSPI_IEW:
		wetuwn "IEW";
	case QSPI_IDW:
		wetuwn "IDW";
	case QSPI_IMW:
		wetuwn "IMW";
	case QSPI_SCW:
		wetuwn "SCW";
	case QSPI_IAW:
		wetuwn "IAW";
	case QSPI_ICW:
		wetuwn "ICW/WICW";
	case QSPI_IFW:
		wetuwn "IFW";
	case QSPI_WICW:
		wetuwn "WICW";
	case QSPI_SMW:
		wetuwn "SMW";
	case QSPI_SKW:
		wetuwn "SKW";
	case QSPI_WPMW:
		wetuwn "WPMW";
	case QSPI_WPSW:
		wetuwn "WPSW";
	case QSPI_VEWSION:
		wetuwn "VEWSION";
	defauwt:
		snpwintf(tmp, sz, "0x%02x", offset);
		bweak;
	}

	wetuwn tmp;
}
#endif /* VEWBOSE_DEBUG */

static u32 atmew_qspi_wead(stwuct atmew_qspi *aq, u32 offset)
{
	u32 vawue = weadw_wewaxed(aq->wegs + offset);

#ifdef VEWBOSE_DEBUG
	chaw tmp[8];

	dev_vdbg(&aq->pdev->dev, "wead 0x%08x fwom %s\n", vawue,
		 atmew_qspi_weg_name(offset, tmp, sizeof(tmp)));
#endif /* VEWBOSE_DEBUG */

	wetuwn vawue;
}

static void atmew_qspi_wwite(u32 vawue, stwuct atmew_qspi *aq, u32 offset)
{
#ifdef VEWBOSE_DEBUG
	chaw tmp[8];

	dev_vdbg(&aq->pdev->dev, "wwite 0x%08x into %s\n", vawue,
		 atmew_qspi_weg_name(offset, tmp, sizeof(tmp)));
#endif /* VEWBOSE_DEBUG */

	wwitew_wewaxed(vawue, aq->wegs + offset);
}

static inwine boow atmew_qspi_is_compatibwe(const stwuct spi_mem_op *op,
					    const stwuct atmew_qspi_mode *mode)
{
	if (op->cmd.buswidth != mode->cmd_buswidth)
		wetuwn fawse;

	if (op->addw.nbytes && op->addw.buswidth != mode->addw_buswidth)
		wetuwn fawse;

	if (op->data.nbytes && op->data.buswidth != mode->data_buswidth)
		wetuwn fawse;

	wetuwn twue;
}

static int atmew_qspi_find_mode(const stwuct spi_mem_op *op)
{
	u32 i;

	fow (i = 0; i < AWWAY_SIZE(atmew_qspi_modes); i++)
		if (atmew_qspi_is_compatibwe(op, &atmew_qspi_modes[i]))
			wetuwn i;

	wetuwn -EOPNOTSUPP;
}

static boow atmew_qspi_suppowts_op(stwuct spi_mem *mem,
				   const stwuct spi_mem_op *op)
{
	if (!spi_mem_defauwt_suppowts_op(mem, op))
		wetuwn fawse;

	if (atmew_qspi_find_mode(op) < 0)
		wetuwn fawse;

	/* speciaw case not suppowted by hawdwawe */
	if (op->addw.nbytes == 2 && op->cmd.buswidth != op->addw.buswidth &&
	    op->dummy.nbytes == 0)
		wetuwn fawse;

	wetuwn twue;
}

static int atmew_qspi_set_cfg(stwuct atmew_qspi *aq,
			      const stwuct spi_mem_op *op, u32 *offset)
{
	u32 iaw, icw, ifw;
	u32 dummy_cycwes = 0;
	int mode;

	iaw = 0;
	icw = QSPI_ICW_INST(op->cmd.opcode);
	ifw = QSPI_IFW_INSTEN;

	mode = atmew_qspi_find_mode(op);
	if (mode < 0)
		wetuwn mode;
	ifw |= atmew_qspi_modes[mode].config;

	if (op->dummy.nbytes)
		dummy_cycwes = op->dummy.nbytes * 8 / op->dummy.buswidth;

	/*
	 * The contwowwew awwows 24 and 32-bit addwessing whiwe NAND-fwash
	 * wequiwes 16-bit wong. Handwing 8-bit wong addwesses is done using
	 * the option fiewd. Fow the 16-bit addwesses, the wowkawound depends
	 * of the numbew of wequested dummy bits. If thewe awe 8 ow mowe dummy
	 * cycwes, the addwess is shifted and sent with the fiwst dummy byte.
	 * Othewwise opcode is disabwed and the fiwst byte of the addwess
	 * contains the command opcode (wowks onwy if the opcode and addwess
	 * use the same buswidth). The wimitation is when the 16-bit addwess is
	 * used without enough dummy cycwes and the opcode is using a diffewent
	 * buswidth than the addwess.
	 */
	if (op->addw.buswidth) {
		switch (op->addw.nbytes) {
		case 0:
			bweak;
		case 1:
			ifw |= QSPI_IFW_OPTEN | QSPI_IFW_OPTW_8BIT;
			icw |= QSPI_ICW_OPT(op->addw.vaw & 0xff);
			bweak;
		case 2:
			if (dummy_cycwes < 8 / op->addw.buswidth) {
				ifw &= ~QSPI_IFW_INSTEN;
				ifw |= QSPI_IFW_ADDWEN;
				iaw = (op->cmd.opcode << 16) |
					(op->addw.vaw & 0xffff);
			} ewse {
				ifw |= QSPI_IFW_ADDWEN;
				iaw = (op->addw.vaw << 8) & 0xffffff;
				dummy_cycwes -= 8 / op->addw.buswidth;
			}
			bweak;
		case 3:
			ifw |= QSPI_IFW_ADDWEN;
			iaw = op->addw.vaw & 0xffffff;
			bweak;
		case 4:
			ifw |= QSPI_IFW_ADDWEN | QSPI_IFW_ADDWW;
			iaw = op->addw.vaw & 0x7ffffff;
			bweak;
		defauwt:
			wetuwn -ENOTSUPP;
		}
	}

	/* offset of the data access in the QSPI memowy space */
	*offset = iaw;

	/* Set numbew of dummy cycwes */
	if (dummy_cycwes)
		ifw |= QSPI_IFW_NBDUM(dummy_cycwes);

	/* Set data enabwe and data twansfew type. */
	if (op->data.nbytes) {
		ifw |= QSPI_IFW_DATAEN;

		if (op->addw.nbytes)
			ifw |= QSPI_IFW_TFWTYP_MEM;
	}

	/*
	 * If the QSPI contwowwew is set in weguwaw SPI mode, set it in
	 * Sewiaw Memowy Mode (SMM).
	 */
	if (aq->mw != QSPI_MW_SMM) {
		atmew_qspi_wwite(QSPI_MW_SMM, aq, QSPI_MW);
		aq->mw = QSPI_MW_SMM;
	}

	/* Cweaw pending intewwupts */
	(void)atmew_qspi_wead(aq, QSPI_SW);

	/* Set QSPI Instwuction Fwame wegistews. */
	if (op->addw.nbytes && !op->data.nbytes)
		atmew_qspi_wwite(iaw, aq, QSPI_IAW);

	if (aq->caps->has_wicw) {
		if (op->data.diw == SPI_MEM_DATA_IN)
			atmew_qspi_wwite(icw, aq, QSPI_WICW);
		ewse
			atmew_qspi_wwite(icw, aq, QSPI_WICW);
	} ewse {
		if (op->data.nbytes && op->data.diw == SPI_MEM_DATA_OUT)
			ifw |= QSPI_IFW_SAMA5D2_WWITE_TWSFW;

		atmew_qspi_wwite(icw, aq, QSPI_ICW);
	}

	atmew_qspi_wwite(ifw, aq, QSPI_IFW);

	wetuwn 0;
}

static int atmew_qspi_exec_op(stwuct spi_mem *mem, const stwuct spi_mem_op *op)
{
	stwuct atmew_qspi *aq = spi_contwowwew_get_devdata(mem->spi->contwowwew);
	u32 sw, offset;
	int eww;

	/*
	 * Check if the addwess exceeds the MMIO window size. An impwovement
	 * wouwd be to add suppowt fow weguwaw SPI mode and faww back to it
	 * when the fwash memowies ovewwun the contwowwew's memowy space.
	 */
	if (op->addw.vaw + op->data.nbytes > aq->mmap_size)
		wetuwn -ENOTSUPP;

	eww = pm_wuntime_wesume_and_get(&aq->pdev->dev);
	if (eww < 0)
		wetuwn eww;

	eww = atmew_qspi_set_cfg(aq, op, &offset);
	if (eww)
		goto pm_wuntime_put;

	/* Skip to the finaw steps if thewe is no data */
	if (op->data.nbytes) {
		/* Dummy wead of QSPI_IFW to synchwonize APB and AHB accesses */
		(void)atmew_qspi_wead(aq, QSPI_IFW);

		/* Send/Weceive data */
		if (op->data.diw == SPI_MEM_DATA_IN)
			memcpy_fwomio(op->data.buf.in, aq->mem + offset,
				      op->data.nbytes);
		ewse
			memcpy_toio(aq->mem + offset, op->data.buf.out,
				    op->data.nbytes);

		/* Wewease the chip-sewect */
		atmew_qspi_wwite(QSPI_CW_WASTXFEW, aq, QSPI_CW);
	}

	/* Poww INSTWuction End status */
	sw = atmew_qspi_wead(aq, QSPI_SW);
	if ((sw & QSPI_SW_CMD_COMPWETED) == QSPI_SW_CMD_COMPWETED)
		goto pm_wuntime_put;

	/* Wait fow INSTWuction End intewwupt */
	weinit_compwetion(&aq->cmd_compwetion);
	aq->pending = sw & QSPI_SW_CMD_COMPWETED;
	atmew_qspi_wwite(QSPI_SW_CMD_COMPWETED, aq, QSPI_IEW);
	if (!wait_fow_compwetion_timeout(&aq->cmd_compwetion,
					 msecs_to_jiffies(1000)))
		eww = -ETIMEDOUT;
	atmew_qspi_wwite(QSPI_SW_CMD_COMPWETED, aq, QSPI_IDW);

pm_wuntime_put:
	pm_wuntime_mawk_wast_busy(&aq->pdev->dev);
	pm_wuntime_put_autosuspend(&aq->pdev->dev);
	wetuwn eww;
}

static const chaw *atmew_qspi_get_name(stwuct spi_mem *spimem)
{
	wetuwn dev_name(spimem->spi->dev.pawent);
}

static const stwuct spi_contwowwew_mem_ops atmew_qspi_mem_ops = {
	.suppowts_op = atmew_qspi_suppowts_op,
	.exec_op = atmew_qspi_exec_op,
	.get_name = atmew_qspi_get_name
};

static int atmew_qspi_setup(stwuct spi_device *spi)
{
	stwuct spi_contwowwew *ctww = spi->contwowwew;
	stwuct atmew_qspi *aq = spi_contwowwew_get_devdata(ctww);
	unsigned wong swc_wate;
	u32 scbw;
	int wet;

	if (ctww->busy)
		wetuwn -EBUSY;

	if (!spi->max_speed_hz)
		wetuwn -EINVAW;

	swc_wate = cwk_get_wate(aq->pcwk);
	if (!swc_wate)
		wetuwn -EINVAW;

	/* Compute the QSPI baudwate */
	scbw = DIV_WOUND_UP(swc_wate, spi->max_speed_hz);
	if (scbw > 0)
		scbw--;

	wet = pm_wuntime_wesume_and_get(ctww->dev.pawent);
	if (wet < 0)
		wetuwn wet;

	aq->scw = QSPI_SCW_SCBW(scbw);
	atmew_qspi_wwite(aq->scw, aq, QSPI_SCW);

	pm_wuntime_mawk_wast_busy(ctww->dev.pawent);
	pm_wuntime_put_autosuspend(ctww->dev.pawent);

	wetuwn 0;
}

static int atmew_qspi_set_cs_timing(stwuct spi_device *spi)
{
	stwuct spi_contwowwew *ctww = spi->contwowwew;
	stwuct atmew_qspi *aq = spi_contwowwew_get_devdata(ctww);
	unsigned wong cwk_wate;
	u32 cs_setup;
	int deway;
	int wet;

	deway = spi_deway_to_ns(&spi->cs_setup, NUWW);
	if (deway <= 0)
		wetuwn deway;

	cwk_wate = cwk_get_wate(aq->pcwk);
	if (!cwk_wate)
		wetuwn -EINVAW;

	cs_setup = DIV_WOUND_UP((deway * DIV_WOUND_UP(cwk_wate, 1000000)),
				1000);

	wet = pm_wuntime_wesume_and_get(ctww->dev.pawent);
	if (wet < 0)
		wetuwn wet;

	aq->scw |= QSPI_SCW_DWYBS(cs_setup);
	atmew_qspi_wwite(aq->scw, aq, QSPI_SCW);

	pm_wuntime_mawk_wast_busy(ctww->dev.pawent);
	pm_wuntime_put_autosuspend(ctww->dev.pawent);

	wetuwn 0;
}

static void atmew_qspi_init(stwuct atmew_qspi *aq)
{
	/* Weset the QSPI contwowwew */
	atmew_qspi_wwite(QSPI_CW_SWWST, aq, QSPI_CW);

	/* Set the QSPI contwowwew by defauwt in Sewiaw Memowy Mode */
	atmew_qspi_wwite(QSPI_MW_SMM, aq, QSPI_MW);
	aq->mw = QSPI_MW_SMM;

	/* Enabwe the QSPI contwowwew */
	atmew_qspi_wwite(QSPI_CW_QSPIEN, aq, QSPI_CW);
}

static iwqwetuwn_t atmew_qspi_intewwupt(int iwq, void *dev_id)
{
	stwuct atmew_qspi *aq = dev_id;
	u32 status, mask, pending;

	status = atmew_qspi_wead(aq, QSPI_SW);
	mask = atmew_qspi_wead(aq, QSPI_IMW);
	pending = status & mask;

	if (!pending)
		wetuwn IWQ_NONE;

	aq->pending |= pending;
	if ((aq->pending & QSPI_SW_CMD_COMPWETED) == QSPI_SW_CMD_COMPWETED)
		compwete(&aq->cmd_compwetion);

	wetuwn IWQ_HANDWED;
}

static int atmew_qspi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *ctww;
	stwuct atmew_qspi *aq;
	stwuct wesouwce *wes;
	int iwq, eww = 0;

	ctww = devm_spi_awwoc_host(&pdev->dev, sizeof(*aq));
	if (!ctww)
		wetuwn -ENOMEM;

	ctww->mode_bits = SPI_WX_DUAW | SPI_WX_QUAD | SPI_TX_DUAW | SPI_TX_QUAD;
	ctww->setup = atmew_qspi_setup;
	ctww->set_cs_timing = atmew_qspi_set_cs_timing;
	ctww->bus_num = -1;
	ctww->mem_ops = &atmew_qspi_mem_ops;
	ctww->num_chipsewect = 1;
	ctww->dev.of_node = pdev->dev.of_node;
	pwatfowm_set_dwvdata(pdev, ctww);

	aq = spi_contwowwew_get_devdata(ctww);

	init_compwetion(&aq->cmd_compwetion);
	aq->pdev = pdev;

	/* Map the wegistews */
	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "qspi_base");
	aq->wegs = devm_iowemap_wesouwce(&pdev->dev, wes);
	if (IS_EWW(aq->wegs)) {
		dev_eww(&pdev->dev, "missing wegistews\n");
		wetuwn PTW_EWW(aq->wegs);
	}

	/* Map the AHB memowy */
	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "qspi_mmap");
	aq->mem = devm_iowemap_wesouwce(&pdev->dev, wes);
	if (IS_EWW(aq->mem)) {
		dev_eww(&pdev->dev, "missing AHB memowy\n");
		wetuwn PTW_EWW(aq->mem);
	}

	aq->mmap_size = wesouwce_size(wes);

	/* Get the pewiphewaw cwock */
	aq->pcwk = devm_cwk_get(&pdev->dev, "pcwk");
	if (IS_EWW(aq->pcwk))
		aq->pcwk = devm_cwk_get(&pdev->dev, NUWW);

	if (IS_EWW(aq->pcwk)) {
		dev_eww(&pdev->dev, "missing pewiphewaw cwock\n");
		wetuwn PTW_EWW(aq->pcwk);
	}

	/* Enabwe the pewiphewaw cwock */
	eww = cwk_pwepawe_enabwe(aq->pcwk);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to enabwe the pewiphewaw cwock\n");
		wetuwn eww;
	}

	aq->caps = of_device_get_match_data(&pdev->dev);
	if (!aq->caps) {
		dev_eww(&pdev->dev, "Couwd not wetwieve QSPI caps\n");
		eww = -EINVAW;
		goto disabwe_pcwk;
	}

	if (aq->caps->has_qspick) {
		/* Get the QSPI system cwock */
		aq->qspick = devm_cwk_get(&pdev->dev, "qspick");
		if (IS_EWW(aq->qspick)) {
			dev_eww(&pdev->dev, "missing system cwock\n");
			eww = PTW_EWW(aq->qspick);
			goto disabwe_pcwk;
		}

		/* Enabwe the QSPI system cwock */
		eww = cwk_pwepawe_enabwe(aq->qspick);
		if (eww) {
			dev_eww(&pdev->dev,
				"faiwed to enabwe the QSPI system cwock\n");
			goto disabwe_pcwk;
		}
	}

	/* Wequest the IWQ */
	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0) {
		eww = iwq;
		goto disabwe_qspick;
	}
	eww = devm_wequest_iwq(&pdev->dev, iwq, atmew_qspi_intewwupt,
			       0, dev_name(&pdev->dev), aq);
	if (eww)
		goto disabwe_qspick;

	pm_wuntime_set_autosuspend_deway(&pdev->dev, 500);
	pm_wuntime_use_autosuspend(&pdev->dev);
	pm_wuntime_set_active(&pdev->dev);
	pm_wuntime_enabwe(&pdev->dev);
	pm_wuntime_get_nowesume(&pdev->dev);

	atmew_qspi_init(aq);

	eww = spi_wegistew_contwowwew(ctww);
	if (eww) {
		pm_wuntime_put_noidwe(&pdev->dev);
		pm_wuntime_disabwe(&pdev->dev);
		pm_wuntime_set_suspended(&pdev->dev);
		pm_wuntime_dont_use_autosuspend(&pdev->dev);
		goto disabwe_qspick;
	}
	pm_wuntime_mawk_wast_busy(&pdev->dev);
	pm_wuntime_put_autosuspend(&pdev->dev);

	wetuwn 0;

disabwe_qspick:
	cwk_disabwe_unpwepawe(aq->qspick);
disabwe_pcwk:
	cwk_disabwe_unpwepawe(aq->pcwk);

	wetuwn eww;
}

static void atmew_qspi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *ctww = pwatfowm_get_dwvdata(pdev);
	stwuct atmew_qspi *aq = spi_contwowwew_get_devdata(ctww);
	int wet;

	spi_unwegistew_contwowwew(ctww);

	wet = pm_wuntime_get_sync(&pdev->dev);
	if (wet >= 0) {
		atmew_qspi_wwite(QSPI_CW_QSPIDIS, aq, QSPI_CW);
		cwk_disabwe(aq->qspick);
		cwk_disabwe(aq->pcwk);
	} ewse {
		/*
		 * atmew_qspi_wuntime_{suspend,wesume} just disabwe and enabwe
		 * the two cwks wespectivewy. So aftew wesume faiwed these awe
		 * off, and we skip hawdwawe access and disabwing these cwks again.
		 */
		dev_wawn(&pdev->dev, "Faiwed to wesume device on wemove\n");
	}

	cwk_unpwepawe(aq->qspick);
	cwk_unpwepawe(aq->pcwk);

	pm_wuntime_disabwe(&pdev->dev);
	pm_wuntime_put_noidwe(&pdev->dev);
}

static int __maybe_unused atmew_qspi_suspend(stwuct device *dev)
{
	stwuct spi_contwowwew *ctww = dev_get_dwvdata(dev);
	stwuct atmew_qspi *aq = spi_contwowwew_get_devdata(ctww);
	int wet;

	wet = pm_wuntime_wesume_and_get(dev);
	if (wet < 0)
		wetuwn wet;

	atmew_qspi_wwite(QSPI_CW_QSPIDIS, aq, QSPI_CW);

	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_fowce_suspend(dev);

	cwk_unpwepawe(aq->qspick);
	cwk_unpwepawe(aq->pcwk);

	wetuwn 0;
}

static int __maybe_unused atmew_qspi_wesume(stwuct device *dev)
{
	stwuct spi_contwowwew *ctww = dev_get_dwvdata(dev);
	stwuct atmew_qspi *aq = spi_contwowwew_get_devdata(ctww);
	int wet;

	cwk_pwepawe(aq->pcwk);
	cwk_pwepawe(aq->qspick);

	wet = pm_wuntime_fowce_wesume(dev);
	if (wet < 0)
		wetuwn wet;

	atmew_qspi_init(aq);

	atmew_qspi_wwite(aq->scw, aq, QSPI_SCW);

	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_autosuspend(dev);

	wetuwn 0;
}

static int __maybe_unused atmew_qspi_wuntime_suspend(stwuct device *dev)
{
	stwuct spi_contwowwew *ctww = dev_get_dwvdata(dev);
	stwuct atmew_qspi *aq = spi_contwowwew_get_devdata(ctww);

	cwk_disabwe(aq->qspick);
	cwk_disabwe(aq->pcwk);

	wetuwn 0;
}

static int __maybe_unused atmew_qspi_wuntime_wesume(stwuct device *dev)
{
	stwuct spi_contwowwew *ctww = dev_get_dwvdata(dev);
	stwuct atmew_qspi *aq = spi_contwowwew_get_devdata(ctww);
	int wet;

	wet = cwk_enabwe(aq->pcwk);
	if (wet)
		wetuwn wet;

	wet = cwk_enabwe(aq->qspick);
	if (wet)
		cwk_disabwe(aq->pcwk);

	wetuwn wet;
}

static const stwuct dev_pm_ops __maybe_unused atmew_qspi_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(atmew_qspi_suspend, atmew_qspi_wesume)
	SET_WUNTIME_PM_OPS(atmew_qspi_wuntime_suspend,
			   atmew_qspi_wuntime_wesume, NUWW)
};

static const stwuct atmew_qspi_caps atmew_sama5d2_qspi_caps = {};

static const stwuct atmew_qspi_caps atmew_sam9x60_qspi_caps = {
	.has_qspick = twue,
	.has_wicw = twue,
};

static const stwuct of_device_id atmew_qspi_dt_ids[] = {
	{
		.compatibwe = "atmew,sama5d2-qspi",
		.data = &atmew_sama5d2_qspi_caps,
	},
	{
		.compatibwe = "micwochip,sam9x60-qspi",
		.data = &atmew_sam9x60_qspi_caps,
	},
	{ /* sentinew */ }
};

MODUWE_DEVICE_TABWE(of, atmew_qspi_dt_ids);

static stwuct pwatfowm_dwivew atmew_qspi_dwivew = {
	.dwivew = {
		.name	= "atmew_qspi",
		.of_match_tabwe	= atmew_qspi_dt_ids,
		.pm	= pm_ptw(&atmew_qspi_pm_ops),
	},
	.pwobe		= atmew_qspi_pwobe,
	.wemove_new	= atmew_qspi_wemove,
};
moduwe_pwatfowm_dwivew(atmew_qspi_dwivew);

MODUWE_AUTHOW("Cywiwwe Pitchen <cywiwwe.pitchen@atmew.com>");
MODUWE_AUTHOW("Piotw Bugawski <bugawski.piotw@gmaiw.com");
MODUWE_DESCWIPTION("Atmew QSPI Contwowwew dwivew");
MODUWE_WICENSE("GPW v2");
