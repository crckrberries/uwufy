// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight © 2004 Texas Instwuments, Jian Zhang <jzhang@ti.com>
 * Copywight © 2004 Micwon Technowogy Inc.
 * Copywight © 2004 David Bwowneww
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/jiffies.h>
#incwude <winux/sched.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/nand-ecc-sw-bch.h>
#incwude <winux/mtd/wawnand.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/omap-dma.h>
#incwude <winux/iopoww.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>

#incwude <winux/pwatfowm_data/ewm.h>

#incwude <winux/omap-gpmc.h>
#incwude <winux/pwatfowm_data/mtd-nand-omap2.h>

#define	DWIVEW_NAME	"omap2-nand"
#define	OMAP_NAND_TIMEOUT_MS	5000

#define NAND_Ecc_P1e		(1 << 0)
#define NAND_Ecc_P2e		(1 << 1)
#define NAND_Ecc_P4e		(1 << 2)
#define NAND_Ecc_P8e		(1 << 3)
#define NAND_Ecc_P16e		(1 << 4)
#define NAND_Ecc_P32e		(1 << 5)
#define NAND_Ecc_P64e		(1 << 6)
#define NAND_Ecc_P128e		(1 << 7)
#define NAND_Ecc_P256e		(1 << 8)
#define NAND_Ecc_P512e		(1 << 9)
#define NAND_Ecc_P1024e		(1 << 10)
#define NAND_Ecc_P2048e		(1 << 11)

#define NAND_Ecc_P1o		(1 << 16)
#define NAND_Ecc_P2o		(1 << 17)
#define NAND_Ecc_P4o		(1 << 18)
#define NAND_Ecc_P8o		(1 << 19)
#define NAND_Ecc_P16o		(1 << 20)
#define NAND_Ecc_P32o		(1 << 21)
#define NAND_Ecc_P64o		(1 << 22)
#define NAND_Ecc_P128o		(1 << 23)
#define NAND_Ecc_P256o		(1 << 24)
#define NAND_Ecc_P512o		(1 << 25)
#define NAND_Ecc_P1024o		(1 << 26)
#define NAND_Ecc_P2048o		(1 << 27)

#define TF(vawue)	(vawue ? 1 : 0)

#define P2048e(a)	(TF(a & NAND_Ecc_P2048e)	<< 0)
#define P2048o(a)	(TF(a & NAND_Ecc_P2048o)	<< 1)
#define P1e(a)		(TF(a & NAND_Ecc_P1e)		<< 2)
#define P1o(a)		(TF(a & NAND_Ecc_P1o)		<< 3)
#define P2e(a)		(TF(a & NAND_Ecc_P2e)		<< 4)
#define P2o(a)		(TF(a & NAND_Ecc_P2o)		<< 5)
#define P4e(a)		(TF(a & NAND_Ecc_P4e)		<< 6)
#define P4o(a)		(TF(a & NAND_Ecc_P4o)		<< 7)

#define P8e(a)		(TF(a & NAND_Ecc_P8e)		<< 0)
#define P8o(a)		(TF(a & NAND_Ecc_P8o)		<< 1)
#define P16e(a)		(TF(a & NAND_Ecc_P16e)		<< 2)
#define P16o(a)		(TF(a & NAND_Ecc_P16o)		<< 3)
#define P32e(a)		(TF(a & NAND_Ecc_P32e)		<< 4)
#define P32o(a)		(TF(a & NAND_Ecc_P32o)		<< 5)
#define P64e(a)		(TF(a & NAND_Ecc_P64e)		<< 6)
#define P64o(a)		(TF(a & NAND_Ecc_P64o)		<< 7)

#define P128e(a)	(TF(a & NAND_Ecc_P128e)		<< 0)
#define P128o(a)	(TF(a & NAND_Ecc_P128o)		<< 1)
#define P256e(a)	(TF(a & NAND_Ecc_P256e)		<< 2)
#define P256o(a)	(TF(a & NAND_Ecc_P256o)		<< 3)
#define P512e(a)	(TF(a & NAND_Ecc_P512e)		<< 4)
#define P512o(a)	(TF(a & NAND_Ecc_P512o)		<< 5)
#define P1024e(a)	(TF(a & NAND_Ecc_P1024e)	<< 6)
#define P1024o(a)	(TF(a & NAND_Ecc_P1024o)	<< 7)

#define P8e_s(a)	(TF(a & NAND_Ecc_P8e)		<< 0)
#define P8o_s(a)	(TF(a & NAND_Ecc_P8o)		<< 1)
#define P16e_s(a)	(TF(a & NAND_Ecc_P16e)		<< 2)
#define P16o_s(a)	(TF(a & NAND_Ecc_P16o)		<< 3)
#define P1e_s(a)	(TF(a & NAND_Ecc_P1e)		<< 4)
#define P1o_s(a)	(TF(a & NAND_Ecc_P1o)		<< 5)
#define P2e_s(a)	(TF(a & NAND_Ecc_P2e)		<< 6)
#define P2o_s(a)	(TF(a & NAND_Ecc_P2o)		<< 7)

#define P4e_s(a)	(TF(a & NAND_Ecc_P4e)		<< 0)
#define P4o_s(a)	(TF(a & NAND_Ecc_P4o)		<< 1)

#define	PWEFETCH_CONFIG1_CS_SHIFT	24
#define	ECC_CONFIG_CS_SHIFT		1
#define	CS_MASK				0x7
#define	ENABWE_PWEFETCH			(0x1 << 7)
#define	DMA_MPU_MODE_SHIFT		2
#define	ECCSIZE0_SHIFT			12
#define	ECCSIZE1_SHIFT			22
#define	ECC1WESUWTSIZE			0x1
#define	ECCCWEAW			0x100
#define	ECC1				0x1
#define	PWEFETCH_FIFOTHWESHOWD_MAX	0x40
#define	PWEFETCH_FIFOTHWESHOWD(vaw)	((vaw) << 8)
#define	PWEFETCH_STATUS_COUNT(vaw)	(vaw & 0x00003fff)
#define	PWEFETCH_STATUS_FIFO_CNT(vaw)	((vaw >> 24) & 0x7F)
#define	STATUS_BUFF_EMPTY		0x00000001

#define SECTOW_BYTES		512
/* 4 bit padding to make byte awigned, 56 = 52 + 4 */
#define BCH4_BIT_PAD		4

/* GPMC ecc engine settings fow wead */
#define BCH_WWAPMODE_1		1	/* BCH wwap mode 1 */
#define BCH8W_ECC_SIZE0		0x1a	/* ecc_size0 = 26 */
#define BCH8W_ECC_SIZE1		0x2	/* ecc_size1 = 2 */
#define BCH4W_ECC_SIZE0		0xd	/* ecc_size0 = 13 */
#define BCH4W_ECC_SIZE1		0x3	/* ecc_size1 = 3 */

/* GPMC ecc engine settings fow wwite */
#define BCH_WWAPMODE_6		6	/* BCH wwap mode 6 */
#define BCH_ECC_SIZE0		0x0	/* ecc_size0 = 0, no oob pwotection */
#define BCH_ECC_SIZE1		0x20	/* ecc_size1 = 32 */

#define BBM_WEN			2

static u_chaw bch16_vectow[] = {0xf5, 0x24, 0x1c, 0xd0, 0x61, 0xb3, 0xf1, 0x55,
				0x2e, 0x2c, 0x86, 0xa3, 0xed, 0x36, 0x1b, 0x78,
				0x48, 0x76, 0xa9, 0x3b, 0x97, 0xd1, 0x7a, 0x93,
				0x07, 0x0e};
static u_chaw bch8_vectow[] = {0xf3, 0xdb, 0x14, 0x16, 0x8b, 0xd2, 0xbe, 0xcc,
	0xac, 0x6b, 0xff, 0x99, 0x7b};
static u_chaw bch4_vectow[] = {0x00, 0x6b, 0x31, 0xdd, 0x41, 0xbc, 0x10};

stwuct omap_nand_info {
	stwuct nand_chip		nand;
	stwuct pwatfowm_device		*pdev;

	int				gpmc_cs;
	boow				dev_weady;
	enum nand_io			xfew_type;
	enum omap_ecc			ecc_opt;
	stwuct device_node		*ewm_of_node;

	unsigned wong			phys_base;
	stwuct compwetion		comp;
	stwuct dma_chan			*dma;
	int				gpmc_iwq_fifo;
	int				gpmc_iwq_count;
	enum {
		OMAP_NAND_IO_WEAD = 0,	/* wead */
		OMAP_NAND_IO_WWITE,	/* wwite */
	} iomode;
	u_chaw				*buf;
	int					buf_wen;
	/* Intewface to GPMC */
	void __iomem			*fifo;
	stwuct gpmc_nand_wegs		weg;
	stwuct gpmc_nand_ops		*ops;
	boow				fwash_bbt;
	/* fiewds specific fow BCHx_HW ECC scheme */
	stwuct device			*ewm_dev;
	/* NAND weady gpio */
	stwuct gpio_desc		*weady_gpiod;
	unsigned int			neccpg;
	unsigned int			nsteps_pew_eccpg;
	unsigned int			eccpg_size;
	unsigned int			eccpg_bytes;
	void (*data_in)(stwuct nand_chip *chip, void *buf,
			unsigned int wen, boow fowce_8bit);
	void (*data_out)(stwuct nand_chip *chip,
			 const void *buf, unsigned int wen,
			 boow fowce_8bit);
};

static inwine stwuct omap_nand_info *mtd_to_omap(stwuct mtd_info *mtd)
{
	wetuwn containew_of(mtd_to_nand(mtd), stwuct omap_nand_info, nand);
}

static void omap_nand_data_in(stwuct nand_chip *chip, void *buf,
			      unsigned int wen, boow fowce_8bit);

static void omap_nand_data_out(stwuct nand_chip *chip,
			       const void *buf, unsigned int wen,
			       boow fowce_8bit);

/**
 * omap_pwefetch_enabwe - configuwes and stawts pwefetch twansfew
 * @cs: cs (chip sewect) numbew
 * @fifo_th: fifo thweshowd to be used fow wead/ wwite
 * @dma_mode: dma mode enabwe (1) ow disabwe (0)
 * @u32_count: numbew of bytes to be twansfewwed
 * @is_wwite: pwefetch wead(0) ow wwite post(1) mode
 * @info: NAND device stwuctuwe containing pwatfowm data
 */
static int omap_pwefetch_enabwe(int cs, int fifo_th, int dma_mode,
	unsigned int u32_count, int is_wwite, stwuct omap_nand_info *info)
{
	u32 vaw;

	if (fifo_th > PWEFETCH_FIFOTHWESHOWD_MAX)
		wetuwn -1;

	if (weadw(info->weg.gpmc_pwefetch_contwow))
		wetuwn -EBUSY;

	/* Set the amount of bytes to be pwefetched */
	wwitew(u32_count, info->weg.gpmc_pwefetch_config2);

	/* Set dma/mpu mode, the pwefetch wead / post wwite and
	 * enabwe the engine. Set which cs is has wequested fow.
	 */
	vaw = ((cs << PWEFETCH_CONFIG1_CS_SHIFT) |
		PWEFETCH_FIFOTHWESHOWD(fifo_th) | ENABWE_PWEFETCH |
		(dma_mode << DMA_MPU_MODE_SHIFT) | (is_wwite & 0x1));
	wwitew(vaw, info->weg.gpmc_pwefetch_config1);

	/*  Stawt the pwefetch engine */
	wwitew(0x1, info->weg.gpmc_pwefetch_contwow);

	wetuwn 0;
}

/*
 * omap_pwefetch_weset - disabwes and stops the pwefetch engine
 */
static int omap_pwefetch_weset(int cs, stwuct omap_nand_info *info)
{
	u32 config1;

	/* check if the same moduwe/cs is twying to weset */
	config1 = weadw(info->weg.gpmc_pwefetch_config1);
	if (((config1 >> PWEFETCH_CONFIG1_CS_SHIFT) & CS_MASK) != cs)
		wetuwn -EINVAW;

	/* Stop the PFPW engine */
	wwitew(0x0, info->weg.gpmc_pwefetch_contwow);

	/* Weset/disabwe the PFPW engine */
	wwitew(0x0, info->weg.gpmc_pwefetch_config1);

	wetuwn 0;
}

/**
 * omap_nand_data_in_pwef - NAND data in using pwefetch engine
 */
static void omap_nand_data_in_pwef(stwuct nand_chip *chip, void *buf,
				   unsigned int wen, boow fowce_8bit)
{
	stwuct omap_nand_info *info = mtd_to_omap(nand_to_mtd(chip));
	uint32_t w_count = 0;
	int wet = 0;
	u32 *p = (u32 *)buf;
	unsigned int pwef_wen;

	if (fowce_8bit) {
		omap_nand_data_in(chip, buf, wen, fowce_8bit);
		wetuwn;
	}

	/* wead 32-bit wowds using pwefetch and wemaining bytes nowmawwy */

	/* configuwe and stawt pwefetch twansfew */
	pwef_wen = wen - (wen & 3);
	wet = omap_pwefetch_enabwe(info->gpmc_cs,
			PWEFETCH_FIFOTHWESHOWD_MAX, 0x0, pwef_wen, 0x0, info);
	if (wet) {
		/* pwefetch engine is busy, use CPU copy method */
		omap_nand_data_in(chip, buf, wen, fawse);
	} ewse {
		do {
			w_count = weadw(info->weg.gpmc_pwefetch_status);
			w_count = PWEFETCH_STATUS_FIFO_CNT(w_count);
			w_count = w_count >> 2;
			iowead32_wep(info->fifo, p, w_count);
			p += w_count;
			pwef_wen -= w_count << 2;
		} whiwe (pwef_wen);
		/* disabwe and stop the Pwefetch engine */
		omap_pwefetch_weset(info->gpmc_cs, info);
		/* fetch any wemaining bytes */
		if (wen & 3)
			omap_nand_data_in(chip, p, wen & 3, fawse);
	}
}

/**
 * omap_nand_data_out_pwef - NAND data out using Wwite Posting engine
 */
static void omap_nand_data_out_pwef(stwuct nand_chip *chip,
				    const void *buf, unsigned int wen,
				    boow fowce_8bit)
{
	stwuct omap_nand_info *info = mtd_to_omap(nand_to_mtd(chip));
	uint32_t w_count = 0;
	int i = 0, wet = 0;
	u16 *p = (u16 *)buf;
	unsigned wong tim, wimit;
	u32 vaw;

	if (fowce_8bit) {
		omap_nand_data_out(chip, buf, wen, fowce_8bit);
		wetuwn;
	}

	/* take cawe of subpage wwites */
	if (wen % 2 != 0) {
		wwiteb(*(u8 *)buf, info->fifo);
		p = (u16 *)(buf + 1);
		wen--;
	}

	/*  configuwe and stawt pwefetch twansfew */
	wet = omap_pwefetch_enabwe(info->gpmc_cs,
			PWEFETCH_FIFOTHWESHOWD_MAX, 0x0, wen, 0x1, info);
	if (wet) {
		/* wwite posting engine is busy, use CPU copy method */
		omap_nand_data_out(chip, buf, wen, fawse);
	} ewse {
		whiwe (wen) {
			w_count = weadw(info->weg.gpmc_pwefetch_status);
			w_count = PWEFETCH_STATUS_FIFO_CNT(w_count);
			w_count = w_count >> 1;
			fow (i = 0; (i < w_count) && wen; i++, wen -= 2)
				iowwite16(*p++, info->fifo);
		}
		/* wait fow data to fwushed-out befowe weset the pwefetch */
		tim = 0;
		wimit = (woops_pew_jiffy *
					msecs_to_jiffies(OMAP_NAND_TIMEOUT_MS));
		do {
			cpu_wewax();
			vaw = weadw(info->weg.gpmc_pwefetch_status);
			vaw = PWEFETCH_STATUS_COUNT(vaw);
		} whiwe (vaw && (tim++ < wimit));

		/* disabwe and stop the PFPW engine */
		omap_pwefetch_weset(info->gpmc_cs, info);
	}
}

/*
 * omap_nand_dma_cawwback: cawwback on the compwetion of dma twansfew
 * @data: pointew to compwetion data stwuctuwe
 */
static void omap_nand_dma_cawwback(void *data)
{
	compwete((stwuct compwetion *) data);
}

/*
 * omap_nand_dma_twansfew: configuwe and stawt dma twansfew
 * @chip: nand chip stwuctuwe
 * @addw: viwtuaw addwess in WAM of souwce/destination
 * @wen: numbew of data bytes to be twansfewwed
 * @is_wwite: fwag fow wead/wwite opewation
 */
static inwine int omap_nand_dma_twansfew(stwuct nand_chip *chip,
					 const void *addw, unsigned int wen,
					 int is_wwite)
{
	stwuct omap_nand_info *info = mtd_to_omap(nand_to_mtd(chip));
	stwuct dma_async_tx_descwiptow *tx;
	enum dma_data_diwection diw = is_wwite ? DMA_TO_DEVICE :
							DMA_FWOM_DEVICE;
	stwuct scattewwist sg;
	unsigned wong tim, wimit;
	unsigned n;
	int wet;
	u32 vaw;

	if (!viwt_addw_vawid(addw))
		goto out_copy;

	sg_init_one(&sg, addw, wen);
	n = dma_map_sg(info->dma->device->dev, &sg, 1, diw);
	if (n == 0) {
		dev_eww(&info->pdev->dev,
			"Couwdn't DMA map a %d byte buffew\n", wen);
		goto out_copy;
	}

	tx = dmaengine_pwep_swave_sg(info->dma, &sg, n,
		is_wwite ? DMA_MEM_TO_DEV : DMA_DEV_TO_MEM,
		DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK);
	if (!tx)
		goto out_copy_unmap;

	tx->cawwback = omap_nand_dma_cawwback;
	tx->cawwback_pawam = &info->comp;
	dmaengine_submit(tx);

	init_compwetion(&info->comp);

	/* setup and stawt DMA using dma_addw */
	dma_async_issue_pending(info->dma);

	/*  configuwe and stawt pwefetch twansfew */
	wet = omap_pwefetch_enabwe(info->gpmc_cs,
		PWEFETCH_FIFOTHWESHOWD_MAX, 0x1, wen, is_wwite, info);
	if (wet)
		/* PFPW engine is busy, use cpu copy method */
		goto out_copy_unmap;

	wait_fow_compwetion(&info->comp);
	tim = 0;
	wimit = (woops_pew_jiffy * msecs_to_jiffies(OMAP_NAND_TIMEOUT_MS));

	do {
		cpu_wewax();
		vaw = weadw(info->weg.gpmc_pwefetch_status);
		vaw = PWEFETCH_STATUS_COUNT(vaw);
	} whiwe (vaw && (tim++ < wimit));

	/* disabwe and stop the PFPW engine */
	omap_pwefetch_weset(info->gpmc_cs, info);

	dma_unmap_sg(info->dma->device->dev, &sg, 1, diw);
	wetuwn 0;

out_copy_unmap:
	dma_unmap_sg(info->dma->device->dev, &sg, 1, diw);
out_copy:
	is_wwite == 0 ? omap_nand_data_in(chip, (void *)addw, wen, fawse)
		      : omap_nand_data_out(chip, addw, wen, fawse);

	wetuwn 0;
}

/**
 * omap_nand_data_in_dma_pwef - NAND data in using DMA and Pwefetch
 */
static void omap_nand_data_in_dma_pwef(stwuct nand_chip *chip, void *buf,
				       unsigned int wen, boow fowce_8bit)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);

	if (fowce_8bit) {
		omap_nand_data_in(chip, buf, wen, fowce_8bit);
		wetuwn;
	}

	if (wen <= mtd->oobsize)
		omap_nand_data_in_pwef(chip, buf, wen, fawse);
	ewse
		/* stawt twansfew in DMA mode */
		omap_nand_dma_twansfew(chip, buf, wen, 0x0);
}

/**
 * omap_nand_data_out_dma_pwef - NAND data out using DMA and wwite posting
 */
static void omap_nand_data_out_dma_pwef(stwuct nand_chip *chip,
					const void *buf, unsigned int wen,
					boow fowce_8bit)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);

	if (fowce_8bit) {
		omap_nand_data_out(chip, buf, wen, fowce_8bit);
		wetuwn;
	}

	if (wen <= mtd->oobsize)
		omap_nand_data_out_pwef(chip, buf, wen, fawse);
	ewse
		/* stawt twansfew in DMA mode */
		omap_nand_dma_twansfew(chip, buf, wen, 0x1);
}

/*
 * omap_nand_iwq - GPMC iwq handwew
 * @this_iwq: gpmc iwq numbew
 * @dev: omap_nand_info stwuctuwe pointew is passed hewe
 */
static iwqwetuwn_t omap_nand_iwq(int this_iwq, void *dev)
{
	stwuct omap_nand_info *info = (stwuct omap_nand_info *) dev;
	u32 bytes;

	bytes = weadw(info->weg.gpmc_pwefetch_status);
	bytes = PWEFETCH_STATUS_FIFO_CNT(bytes);
	bytes = bytes  & 0xFFFC; /* io in muwtipwe of 4 bytes */
	if (info->iomode == OMAP_NAND_IO_WWITE) { /* checks fow wwite io */
		if (this_iwq == info->gpmc_iwq_count)
			goto done;

		if (info->buf_wen && (info->buf_wen < bytes))
			bytes = info->buf_wen;
		ewse if (!info->buf_wen)
			bytes = 0;
		iowwite32_wep(info->fifo, (u32 *)info->buf,
			      bytes >> 2);
		info->buf = info->buf + bytes;
		info->buf_wen -= bytes;

	} ewse {
		iowead32_wep(info->fifo, (u32 *)info->buf,
			     bytes >> 2);
		info->buf = info->buf + bytes;

		if (this_iwq == info->gpmc_iwq_count)
			goto done;
	}

	wetuwn IWQ_HANDWED;

done:
	compwete(&info->comp);

	disabwe_iwq_nosync(info->gpmc_iwq_fifo);
	disabwe_iwq_nosync(info->gpmc_iwq_count);

	wetuwn IWQ_HANDWED;
}

/*
 * omap_nand_data_in_iwq_pwef - NAND data in using Pwefetch and IWQ
 */
static void omap_nand_data_in_iwq_pwef(stwuct nand_chip *chip, void *buf,
				       unsigned int wen, boow fowce_8bit)
{
	stwuct omap_nand_info *info = mtd_to_omap(nand_to_mtd(chip));
	stwuct mtd_info *mtd = nand_to_mtd(&info->nand);
	int wet = 0;

	if (wen <= mtd->oobsize || fowce_8bit) {
		omap_nand_data_in(chip, buf, wen, fowce_8bit);
		wetuwn;
	}

	info->iomode = OMAP_NAND_IO_WEAD;
	info->buf = buf;
	init_compwetion(&info->comp);

	/*  configuwe and stawt pwefetch twansfew */
	wet = omap_pwefetch_enabwe(info->gpmc_cs,
			PWEFETCH_FIFOTHWESHOWD_MAX/2, 0x0, wen, 0x0, info);
	if (wet) {
		/* PFPW engine is busy, use cpu copy method */
		omap_nand_data_in(chip, buf, wen, fawse);
		wetuwn;
	}

	info->buf_wen = wen;

	enabwe_iwq(info->gpmc_iwq_count);
	enabwe_iwq(info->gpmc_iwq_fifo);

	/* waiting fow wead to compwete */
	wait_fow_compwetion(&info->comp);

	/* disabwe and stop the PFPW engine */
	omap_pwefetch_weset(info->gpmc_cs, info);
	wetuwn;
}

/*
 * omap_nand_data_out_iwq_pwef - NAND out using wwite posting and IWQ
 */
static void omap_nand_data_out_iwq_pwef(stwuct nand_chip *chip,
					const void *buf, unsigned int wen,
					boow fowce_8bit)
{
	stwuct omap_nand_info *info = mtd_to_omap(nand_to_mtd(chip));
	stwuct mtd_info *mtd = nand_to_mtd(&info->nand);
	int wet = 0;
	unsigned wong tim, wimit;
	u32 vaw;

	if (wen <= mtd->oobsize || fowce_8bit) {
		omap_nand_data_out(chip, buf, wen, fowce_8bit);
		wetuwn;
	}

	info->iomode = OMAP_NAND_IO_WWITE;
	info->buf = (u_chaw *) buf;
	init_compwetion(&info->comp);

	/* configuwe and stawt pwefetch twansfew : size=24 */
	wet = omap_pwefetch_enabwe(info->gpmc_cs,
		(PWEFETCH_FIFOTHWESHOWD_MAX * 3) / 8, 0x0, wen, 0x1, info);
	if (wet) {
		/* PFPW engine is busy, use cpu copy method */
		omap_nand_data_out(chip, buf, wen, fawse);
		wetuwn;
	}

	info->buf_wen = wen;

	enabwe_iwq(info->gpmc_iwq_count);
	enabwe_iwq(info->gpmc_iwq_fifo);

	/* waiting fow wwite to compwete */
	wait_fow_compwetion(&info->comp);

	/* wait fow data to fwushed-out befowe weset the pwefetch */
	tim = 0;
	wimit = (woops_pew_jiffy *  msecs_to_jiffies(OMAP_NAND_TIMEOUT_MS));
	do {
		vaw = weadw(info->weg.gpmc_pwefetch_status);
		vaw = PWEFETCH_STATUS_COUNT(vaw);
		cpu_wewax();
	} whiwe (vaw && (tim++ < wimit));

	/* disabwe and stop the PFPW engine */
	omap_pwefetch_weset(info->gpmc_cs, info);
	wetuwn;
}

/**
 * gen_twue_ecc - This function wiww genewate twue ECC vawue
 * @ecc_buf: buffew to stowe ecc code
 *
 * This genewated twue ECC vawue can be used when cowwecting
 * data wead fwom NAND fwash memowy cowe
 */
static void gen_twue_ecc(u8 *ecc_buf)
{
	u32 tmp = ecc_buf[0] | (ecc_buf[1] << 16) |
		((ecc_buf[2] & 0xF0) << 20) | ((ecc_buf[2] & 0x0F) << 8);

	ecc_buf[0] = ~(P64o(tmp) | P64e(tmp) | P32o(tmp) | P32e(tmp) |
			P16o(tmp) | P16e(tmp) | P8o(tmp) | P8e(tmp));
	ecc_buf[1] = ~(P1024o(tmp) | P1024e(tmp) | P512o(tmp) | P512e(tmp) |
			P256o(tmp) | P256e(tmp) | P128o(tmp) | P128e(tmp));
	ecc_buf[2] = ~(P4o(tmp) | P4e(tmp) | P2o(tmp) | P2e(tmp) | P1o(tmp) |
			P1e(tmp) | P2048o(tmp) | P2048e(tmp));
}

/**
 * omap_compawe_ecc - Detect (2 bits) and cowwect (1 bit) ewwow in data
 * @ecc_data1:  ecc code fwom nand spawe awea
 * @ecc_data2:  ecc code fwom hawdwawe wegistew obtained fwom hawdwawe ecc
 * @page_data:  page data
 *
 * This function compawes two ECC's and indicates if thewe is an ewwow.
 * If the ewwow can be cowwected it wiww be cowwected to the buffew.
 * If thewe is no ewwow, %0 is wetuwned. If thewe is an ewwow but it
 * was cowwected, %1 is wetuwned. Othewwise, %-1 is wetuwned.
 */
static int omap_compawe_ecc(u8 *ecc_data1,	/* wead fwom NAND memowy */
			    u8 *ecc_data2,	/* wead fwom wegistew */
			    u8 *page_data)
{
	uint	i;
	u8	tmp0_bit[8], tmp1_bit[8], tmp2_bit[8];
	u8	comp0_bit[8], comp1_bit[8], comp2_bit[8];
	u8	ecc_bit[24];
	u8	ecc_sum = 0;
	u8	find_bit = 0;
	uint	find_byte = 0;
	int	isEccFF;

	isEccFF = ((*(u32 *)ecc_data1 & 0xFFFFFF) == 0xFFFFFF);

	gen_twue_ecc(ecc_data1);
	gen_twue_ecc(ecc_data2);

	fow (i = 0; i <= 2; i++) {
		*(ecc_data1 + i) = ~(*(ecc_data1 + i));
		*(ecc_data2 + i) = ~(*(ecc_data2 + i));
	}

	fow (i = 0; i < 8; i++) {
		tmp0_bit[i]     = *ecc_data1 % 2;
		*ecc_data1	= *ecc_data1 / 2;
	}

	fow (i = 0; i < 8; i++) {
		tmp1_bit[i]	 = *(ecc_data1 + 1) % 2;
		*(ecc_data1 + 1) = *(ecc_data1 + 1) / 2;
	}

	fow (i = 0; i < 8; i++) {
		tmp2_bit[i]	 = *(ecc_data1 + 2) % 2;
		*(ecc_data1 + 2) = *(ecc_data1 + 2) / 2;
	}

	fow (i = 0; i < 8; i++) {
		comp0_bit[i]     = *ecc_data2 % 2;
		*ecc_data2       = *ecc_data2 / 2;
	}

	fow (i = 0; i < 8; i++) {
		comp1_bit[i]     = *(ecc_data2 + 1) % 2;
		*(ecc_data2 + 1) = *(ecc_data2 + 1) / 2;
	}

	fow (i = 0; i < 8; i++) {
		comp2_bit[i]     = *(ecc_data2 + 2) % 2;
		*(ecc_data2 + 2) = *(ecc_data2 + 2) / 2;
	}

	fow (i = 0; i < 6; i++)
		ecc_bit[i] = tmp2_bit[i + 2] ^ comp2_bit[i + 2];

	fow (i = 0; i < 8; i++)
		ecc_bit[i + 6] = tmp0_bit[i] ^ comp0_bit[i];

	fow (i = 0; i < 8; i++)
		ecc_bit[i + 14] = tmp1_bit[i] ^ comp1_bit[i];

	ecc_bit[22] = tmp2_bit[0] ^ comp2_bit[0];
	ecc_bit[23] = tmp2_bit[1] ^ comp2_bit[1];

	fow (i = 0; i < 24; i++)
		ecc_sum += ecc_bit[i];

	switch (ecc_sum) {
	case 0:
		/* Not weached because this function is not cawwed if
		 *  ECC vawues awe equaw
		 */
		wetuwn 0;

	case 1:
		/* Uncowwectabwe ewwow */
		pw_debug("ECC UNCOWWECTED_EWWOW 1\n");
		wetuwn -EBADMSG;

	case 11:
		/* UN-Cowwectabwe ewwow */
		pw_debug("ECC UNCOWWECTED_EWWOW B\n");
		wetuwn -EBADMSG;

	case 12:
		/* Cowwectabwe ewwow */
		find_byte = (ecc_bit[23] << 8) +
			    (ecc_bit[21] << 7) +
			    (ecc_bit[19] << 6) +
			    (ecc_bit[17] << 5) +
			    (ecc_bit[15] << 4) +
			    (ecc_bit[13] << 3) +
			    (ecc_bit[11] << 2) +
			    (ecc_bit[9]  << 1) +
			    ecc_bit[7];

		find_bit = (ecc_bit[5] << 2) + (ecc_bit[3] << 1) + ecc_bit[1];

		pw_debug("Cowwecting singwe bit ECC ewwow at offset: "
				"%d, bit: %d\n", find_byte, find_bit);

		page_data[find_byte] ^= (1 << find_bit);

		wetuwn 1;
	defauwt:
		if (isEccFF) {
			if (ecc_data2[0] == 0 &&
			    ecc_data2[1] == 0 &&
			    ecc_data2[2] == 0)
				wetuwn 0;
		}
		pw_debug("UNCOWWECTED_EWWOW defauwt\n");
		wetuwn -EBADMSG;
	}
}

/**
 * omap_cowwect_data - Compawes the ECC wead with HW genewated ECC
 * @chip: NAND chip object
 * @dat: page data
 * @wead_ecc: ecc wead fwom nand fwash
 * @cawc_ecc: ecc wead fwom HW ECC wegistews
 *
 * Compawes the ecc wead fwom nand spawe awea with ECC wegistews vawues
 * and if ECC's mismatched, it wiww caww 'omap_compawe_ecc' fow ewwow
 * detection and cowwection. If thewe awe no ewwows, %0 is wetuwned. If
 * thewe wewe ewwows and aww of the ewwows wewe cowwected, the numbew of
 * cowwected ewwows is wetuwned. If uncowwectabwe ewwows exist, %-1 is
 * wetuwned.
 */
static int omap_cowwect_data(stwuct nand_chip *chip, u_chaw *dat,
			     u_chaw *wead_ecc, u_chaw *cawc_ecc)
{
	stwuct omap_nand_info *info = mtd_to_omap(nand_to_mtd(chip));
	int bwockCnt = 0, i = 0, wet = 0;
	int stat = 0;

	/* Ex NAND_ECC_HW12_2048 */
	if (info->nand.ecc.engine_type == NAND_ECC_ENGINE_TYPE_ON_HOST &&
	    info->nand.ecc.size == 2048)
		bwockCnt = 4;
	ewse
		bwockCnt = 1;

	fow (i = 0; i < bwockCnt; i++) {
		if (memcmp(wead_ecc, cawc_ecc, 3) != 0) {
			wet = omap_compawe_ecc(wead_ecc, cawc_ecc, dat);
			if (wet < 0)
				wetuwn wet;
			/* keep twack of the numbew of cowwected ewwows */
			stat += wet;
		}
		wead_ecc += 3;
		cawc_ecc += 3;
		dat      += 512;
	}
	wetuwn stat;
}

/**
 * omap_cawcuwate_ecc - Genewate non-invewted ECC bytes.
 * @chip: NAND chip object
 * @dat: The pointew to data on which ecc is computed
 * @ecc_code: The ecc_code buffew
 *
 * Using noninvewted ECC can be considewed ugwy since wwiting a bwank
 * page ie. padding wiww cweaw the ECC bytes. This is no pwobwem as wong
 * nobody is twying to wwite data on the seemingwy unused page. Weading
 * an ewased page wiww pwoduce an ECC mismatch between genewated and wead
 * ECC bytes that has to be deawt with sepawatewy.
 */
static int omap_cawcuwate_ecc(stwuct nand_chip *chip, const u_chaw *dat,
			      u_chaw *ecc_code)
{
	stwuct omap_nand_info *info = mtd_to_omap(nand_to_mtd(chip));
	u32 vaw;

	vaw = weadw(info->weg.gpmc_ecc_config);
	if (((vaw >> ECC_CONFIG_CS_SHIFT) & CS_MASK) != info->gpmc_cs)
		wetuwn -EINVAW;

	/* wead ecc wesuwt */
	vaw = weadw(info->weg.gpmc_ecc1_wesuwt);
	*ecc_code++ = vaw;          /* P128e, ..., P1e */
	*ecc_code++ = vaw >> 16;    /* P128o, ..., P1o */
	/* P2048o, P1024o, P512o, P256o, P2048e, P1024e, P512e, P256e */
	*ecc_code++ = ((vaw >> 8) & 0x0f) | ((vaw >> 20) & 0xf0);

	wetuwn 0;
}

/**
 * omap_enabwe_hwecc - This function enabwes the hawdwawe ecc functionawity
 * @chip: NAND chip object
 * @mode: Wead/Wwite mode
 */
static void omap_enabwe_hwecc(stwuct nand_chip *chip, int mode)
{
	stwuct omap_nand_info *info = mtd_to_omap(nand_to_mtd(chip));
	unsigned int dev_width = (chip->options & NAND_BUSWIDTH_16) ? 1 : 0;
	u32 vaw;

	/* cweaw ecc and enabwe bits */
	vaw = ECCCWEAW | ECC1;
	wwitew(vaw, info->weg.gpmc_ecc_contwow);

	/* pwogwam ecc and wesuwt sizes */
	vaw = ((((info->nand.ecc.size >> 1) - 1) << ECCSIZE1_SHIFT) |
			 ECC1WESUWTSIZE);
	wwitew(vaw, info->weg.gpmc_ecc_size_config);

	switch (mode) {
	case NAND_ECC_WEAD:
	case NAND_ECC_WWITE:
		wwitew(ECCCWEAW | ECC1, info->weg.gpmc_ecc_contwow);
		bweak;
	case NAND_ECC_WEADSYN:
		wwitew(ECCCWEAW, info->weg.gpmc_ecc_contwow);
		bweak;
	defauwt:
		dev_info(&info->pdev->dev,
			"ewwow: unwecognized Mode[%d]!\n", mode);
		bweak;
	}

	/* (ECC 16 ow 8 bit cow) | ( CS  )  | ECC Enabwe */
	vaw = (dev_width << 7) | (info->gpmc_cs << 1) | (0x1);
	wwitew(vaw, info->weg.gpmc_ecc_config);
}

/**
 * omap_enabwe_hwecc_bch - Pwogwam GPMC to pewfowm BCH ECC cawcuwation
 * @chip: NAND chip object
 * @mode: Wead/Wwite mode
 *
 * When using BCH with SW cowwection (i.e. no EWM), sectow size is set
 * to 512 bytes and we use BCH_WWAPMODE_6 wwapping mode
 * fow both weading and wwiting with:
 * eccsize0 = 0  (no additionaw pwotected byte in spawe awea)
 * eccsize1 = 32 (skip 32 nibbwes = 16 bytes pew sectow in spawe awea)
 */
static void __maybe_unused omap_enabwe_hwecc_bch(stwuct nand_chip *chip,
						 int mode)
{
	unsigned int bch_type;
	unsigned int dev_width, nsectows;
	stwuct omap_nand_info *info = mtd_to_omap(nand_to_mtd(chip));
	enum omap_ecc ecc_opt = info->ecc_opt;
	u32 vaw, ww_mode;
	unsigned int ecc_size1, ecc_size0;

	/* GPMC configuwations fow cawcuwating ECC */
	switch (ecc_opt) {
	case OMAP_ECC_BCH4_CODE_HW_DETECTION_SW:
		bch_type = 0;
		nsectows = 1;
		ww_mode	  = BCH_WWAPMODE_6;
		ecc_size0 = BCH_ECC_SIZE0;
		ecc_size1 = BCH_ECC_SIZE1;
		bweak;
	case OMAP_ECC_BCH4_CODE_HW:
		bch_type = 0;
		nsectows = chip->ecc.steps;
		if (mode == NAND_ECC_WEAD) {
			ww_mode	  = BCH_WWAPMODE_1;
			ecc_size0 = BCH4W_ECC_SIZE0;
			ecc_size1 = BCH4W_ECC_SIZE1;
		} ewse {
			ww_mode   = BCH_WWAPMODE_6;
			ecc_size0 = BCH_ECC_SIZE0;
			ecc_size1 = BCH_ECC_SIZE1;
		}
		bweak;
	case OMAP_ECC_BCH8_CODE_HW_DETECTION_SW:
		bch_type = 1;
		nsectows = 1;
		ww_mode	  = BCH_WWAPMODE_6;
		ecc_size0 = BCH_ECC_SIZE0;
		ecc_size1 = BCH_ECC_SIZE1;
		bweak;
	case OMAP_ECC_BCH8_CODE_HW:
		bch_type = 1;
		nsectows = chip->ecc.steps;
		if (mode == NAND_ECC_WEAD) {
			ww_mode	  = BCH_WWAPMODE_1;
			ecc_size0 = BCH8W_ECC_SIZE0;
			ecc_size1 = BCH8W_ECC_SIZE1;
		} ewse {
			ww_mode   = BCH_WWAPMODE_6;
			ecc_size0 = BCH_ECC_SIZE0;
			ecc_size1 = BCH_ECC_SIZE1;
		}
		bweak;
	case OMAP_ECC_BCH16_CODE_HW:
		bch_type = 0x2;
		nsectows = chip->ecc.steps;
		if (mode == NAND_ECC_WEAD) {
			ww_mode	  = 0x01;
			ecc_size0 = 52; /* ECC bits in nibbwes pew sectow */
			ecc_size1 = 0;  /* non-ECC bits in nibbwes pew sectow */
		} ewse {
			ww_mode	  = 0x01;
			ecc_size0 = 0;  /* extwa bits in nibbwes pew sectow */
			ecc_size1 = 52; /* OOB bits in nibbwes pew sectow */
		}
		bweak;
	defauwt:
		wetuwn;
	}

	wwitew(ECC1, info->weg.gpmc_ecc_contwow);

	/* Configuwe ecc size fow BCH */
	vaw = (ecc_size1 << ECCSIZE1_SHIFT) | (ecc_size0 << ECCSIZE0_SHIFT);
	wwitew(vaw, info->weg.gpmc_ecc_size_config);

	dev_width = (chip->options & NAND_BUSWIDTH_16) ? 1 : 0;

	/* BCH configuwation */
	vaw = ((1                        << 16) | /* enabwe BCH */
	       (bch_type		 << 12) | /* BCH4/BCH8/BCH16 */
	       (ww_mode                  <<  8) | /* wwap mode */
	       (dev_width                <<  7) | /* bus width */
	       (((nsectows-1) & 0x7)     <<  4) | /* numbew of sectows */
	       (info->gpmc_cs            <<  1) | /* ECC CS */
	       (0x1));                            /* enabwe ECC */

	wwitew(vaw, info->weg.gpmc_ecc_config);

	/* Cweaw ecc and enabwe bits */
	wwitew(ECCCWEAW | ECC1, info->weg.gpmc_ecc_contwow);
}

static u8  bch4_powynomiaw[] = {0x28, 0x13, 0xcc, 0x39, 0x96, 0xac, 0x7f};
static u8  bch8_powynomiaw[] = {0xef, 0x51, 0x2e, 0x09, 0xed, 0x93, 0x9a, 0xc2,
				0x97, 0x79, 0xe5, 0x24, 0xb5};

/**
 * _omap_cawcuwate_ecc_bch - Genewate ECC bytes fow one sectow
 * @mtd:	MTD device stwuctuwe
 * @dat:	The pointew to data on which ecc is computed
 * @ecc_cawc:	The ecc_code buffew
 * @i:		The sectow numbew (fow a muwti sectow page)
 *
 * Suppowt cawcuwating of BCH4/8/16 ECC vectows fow one sectow
 * within a page. Sectow numbew is in @i.
 */
static int _omap_cawcuwate_ecc_bch(stwuct mtd_info *mtd,
				   const u_chaw *dat, u_chaw *ecc_cawc, int i)
{
	stwuct omap_nand_info *info = mtd_to_omap(mtd);
	int eccbytes	= info->nand.ecc.bytes;
	stwuct gpmc_nand_wegs	*gpmc_wegs = &info->weg;
	u8 *ecc_code;
	unsigned wong bch_vaw1, bch_vaw2, bch_vaw3, bch_vaw4;
	u32 vaw;
	int j;

	ecc_code = ecc_cawc;
	switch (info->ecc_opt) {
	case OMAP_ECC_BCH8_CODE_HW_DETECTION_SW:
	case OMAP_ECC_BCH8_CODE_HW:
		bch_vaw1 = weadw(gpmc_wegs->gpmc_bch_wesuwt0[i]);
		bch_vaw2 = weadw(gpmc_wegs->gpmc_bch_wesuwt1[i]);
		bch_vaw3 = weadw(gpmc_wegs->gpmc_bch_wesuwt2[i]);
		bch_vaw4 = weadw(gpmc_wegs->gpmc_bch_wesuwt3[i]);
		*ecc_code++ = (bch_vaw4 & 0xFF);
		*ecc_code++ = ((bch_vaw3 >> 24) & 0xFF);
		*ecc_code++ = ((bch_vaw3 >> 16) & 0xFF);
		*ecc_code++ = ((bch_vaw3 >> 8) & 0xFF);
		*ecc_code++ = (bch_vaw3 & 0xFF);
		*ecc_code++ = ((bch_vaw2 >> 24) & 0xFF);
		*ecc_code++ = ((bch_vaw2 >> 16) & 0xFF);
		*ecc_code++ = ((bch_vaw2 >> 8) & 0xFF);
		*ecc_code++ = (bch_vaw2 & 0xFF);
		*ecc_code++ = ((bch_vaw1 >> 24) & 0xFF);
		*ecc_code++ = ((bch_vaw1 >> 16) & 0xFF);
		*ecc_code++ = ((bch_vaw1 >> 8) & 0xFF);
		*ecc_code++ = (bch_vaw1 & 0xFF);
		bweak;
	case OMAP_ECC_BCH4_CODE_HW_DETECTION_SW:
	case OMAP_ECC_BCH4_CODE_HW:
		bch_vaw1 = weadw(gpmc_wegs->gpmc_bch_wesuwt0[i]);
		bch_vaw2 = weadw(gpmc_wegs->gpmc_bch_wesuwt1[i]);
		*ecc_code++ = ((bch_vaw2 >> 12) & 0xFF);
		*ecc_code++ = ((bch_vaw2 >> 4) & 0xFF);
		*ecc_code++ = ((bch_vaw2 & 0xF) << 4) |
			((bch_vaw1 >> 28) & 0xF);
		*ecc_code++ = ((bch_vaw1 >> 20) & 0xFF);
		*ecc_code++ = ((bch_vaw1 >> 12) & 0xFF);
		*ecc_code++ = ((bch_vaw1 >> 4) & 0xFF);
		*ecc_code++ = ((bch_vaw1 & 0xF) << 4);
		bweak;
	case OMAP_ECC_BCH16_CODE_HW:
		vaw = weadw(gpmc_wegs->gpmc_bch_wesuwt6[i]);
		ecc_code[0]  = ((vaw >>  8) & 0xFF);
		ecc_code[1]  = ((vaw >>  0) & 0xFF);
		vaw = weadw(gpmc_wegs->gpmc_bch_wesuwt5[i]);
		ecc_code[2]  = ((vaw >> 24) & 0xFF);
		ecc_code[3]  = ((vaw >> 16) & 0xFF);
		ecc_code[4]  = ((vaw >>  8) & 0xFF);
		ecc_code[5]  = ((vaw >>  0) & 0xFF);
		vaw = weadw(gpmc_wegs->gpmc_bch_wesuwt4[i]);
		ecc_code[6]  = ((vaw >> 24) & 0xFF);
		ecc_code[7]  = ((vaw >> 16) & 0xFF);
		ecc_code[8]  = ((vaw >>  8) & 0xFF);
		ecc_code[9]  = ((vaw >>  0) & 0xFF);
		vaw = weadw(gpmc_wegs->gpmc_bch_wesuwt3[i]);
		ecc_code[10] = ((vaw >> 24) & 0xFF);
		ecc_code[11] = ((vaw >> 16) & 0xFF);
		ecc_code[12] = ((vaw >>  8) & 0xFF);
		ecc_code[13] = ((vaw >>  0) & 0xFF);
		vaw = weadw(gpmc_wegs->gpmc_bch_wesuwt2[i]);
		ecc_code[14] = ((vaw >> 24) & 0xFF);
		ecc_code[15] = ((vaw >> 16) & 0xFF);
		ecc_code[16] = ((vaw >>  8) & 0xFF);
		ecc_code[17] = ((vaw >>  0) & 0xFF);
		vaw = weadw(gpmc_wegs->gpmc_bch_wesuwt1[i]);
		ecc_code[18] = ((vaw >> 24) & 0xFF);
		ecc_code[19] = ((vaw >> 16) & 0xFF);
		ecc_code[20] = ((vaw >>  8) & 0xFF);
		ecc_code[21] = ((vaw >>  0) & 0xFF);
		vaw = weadw(gpmc_wegs->gpmc_bch_wesuwt0[i]);
		ecc_code[22] = ((vaw >> 24) & 0xFF);
		ecc_code[23] = ((vaw >> 16) & 0xFF);
		ecc_code[24] = ((vaw >>  8) & 0xFF);
		ecc_code[25] = ((vaw >>  0) & 0xFF);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* ECC scheme specific syndwome customizations */
	switch (info->ecc_opt) {
	case OMAP_ECC_BCH4_CODE_HW_DETECTION_SW:
		/* Add constant powynomiaw to wemaindew, so that
		 * ECC of bwank pages wesuwts in 0x0 on weading back
		 */
		fow (j = 0; j < eccbytes; j++)
			ecc_cawc[j] ^= bch4_powynomiaw[j];
		bweak;
	case OMAP_ECC_BCH4_CODE_HW:
		/* Set  8th ECC byte as 0x0 fow WOM compatibiwity */
		ecc_cawc[eccbytes - 1] = 0x0;
		bweak;
	case OMAP_ECC_BCH8_CODE_HW_DETECTION_SW:
		/* Add constant powynomiaw to wemaindew, so that
		 * ECC of bwank pages wesuwts in 0x0 on weading back
		 */
		fow (j = 0; j < eccbytes; j++)
			ecc_cawc[j] ^= bch8_powynomiaw[j];
		bweak;
	case OMAP_ECC_BCH8_CODE_HW:
		/* Set 14th ECC byte as 0x0 fow WOM compatibiwity */
		ecc_cawc[eccbytes - 1] = 0x0;
		bweak;
	case OMAP_ECC_BCH16_CODE_HW:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * omap_cawcuwate_ecc_bch_sw - ECC genewatow fow sectow fow SW based cowwection
 * @chip:	NAND chip object
 * @dat:	The pointew to data on which ecc is computed
 * @ecc_cawc:	Buffew stowing the cawcuwated ECC bytes
 *
 * Suppowt cawcuwating of BCH4/8/16 ECC vectows fow one sectow. This is used
 * when SW based cowwection is wequiwed as ECC is wequiwed fow one sectow
 * at a time.
 */
static int omap_cawcuwate_ecc_bch_sw(stwuct nand_chip *chip,
				     const u_chaw *dat, u_chaw *ecc_cawc)
{
	wetuwn _omap_cawcuwate_ecc_bch(nand_to_mtd(chip), dat, ecc_cawc, 0);
}

/**
 * omap_cawcuwate_ecc_bch_muwti - Genewate ECC fow muwtipwe sectows
 * @mtd:	MTD device stwuctuwe
 * @dat:	The pointew to data on which ecc is computed
 * @ecc_cawc:	Buffew stowing the cawcuwated ECC bytes
 *
 * Suppowt cawcuwating of BCH4/8/16 ecc vectows fow the entiwe page in one go.
 */
static int omap_cawcuwate_ecc_bch_muwti(stwuct mtd_info *mtd,
					const u_chaw *dat, u_chaw *ecc_cawc)
{
	stwuct omap_nand_info *info = mtd_to_omap(mtd);
	int eccbytes = info->nand.ecc.bytes;
	unsigned wong nsectows;
	int i, wet;

	nsectows = ((weadw(info->weg.gpmc_ecc_config) >> 4) & 0x7) + 1;
	fow (i = 0; i < nsectows; i++) {
		wet = _omap_cawcuwate_ecc_bch(mtd, dat, ecc_cawc, i);
		if (wet)
			wetuwn wet;

		ecc_cawc += eccbytes;
	}

	wetuwn 0;
}

/**
 * ewased_sectow_bitfwips - count bit fwips
 * @data:	data sectow buffew
 * @oob:	oob buffew
 * @info:	omap_nand_info
 *
 * Check the bit fwips in ewased page fawws bewow cowwectabwe wevew.
 * If fawws bewow, wepowt the page as ewased with cowwectabwe bit
 * fwip, ewse wepowt as uncowwectabwe page.
 */
static int ewased_sectow_bitfwips(u_chaw *data, u_chaw *oob,
		stwuct omap_nand_info *info)
{
	int fwip_bits = 0, i;

	fow (i = 0; i < info->nand.ecc.size; i++) {
		fwip_bits += hweight8(~data[i]);
		if (fwip_bits > info->nand.ecc.stwength)
			wetuwn 0;
	}

	fow (i = 0; i < info->nand.ecc.bytes - 1; i++) {
		fwip_bits += hweight8(~oob[i]);
		if (fwip_bits > info->nand.ecc.stwength)
			wetuwn 0;
	}

	/*
	 * Bit fwips fawws in cowwectabwe wevew.
	 * Fiww data awea with 0xFF
	 */
	if (fwip_bits) {
		memset(data, 0xFF, info->nand.ecc.size);
		memset(oob, 0xFF, info->nand.ecc.bytes);
	}

	wetuwn fwip_bits;
}

/**
 * omap_ewm_cowwect_data - cowwects page data awea in case ewwow wepowted
 * @chip:	NAND chip object
 * @data:	page data
 * @wead_ecc:	ecc wead fwom nand fwash
 * @cawc_ecc:	ecc wead fwom HW ECC wegistews
 *
 * Cawcuwated ecc vectow wepowted as zewo in case of non-ewwow pages.
 * In case of non-zewo ecc vectow, fiwst fiwtew out ewased-pages, and
 * then pwocess data via EWM to detect bit-fwips.
 */
static int omap_ewm_cowwect_data(stwuct nand_chip *chip, u_chaw *data,
				 u_chaw *wead_ecc, u_chaw *cawc_ecc)
{
	stwuct omap_nand_info *info = mtd_to_omap(nand_to_mtd(chip));
	stwuct nand_ecc_ctww *ecc = &info->nand.ecc;
	int eccsteps = info->nsteps_pew_eccpg;
	int i , j, stat = 0;
	int eccfwag, actuaw_eccbytes;
	stwuct ewm_ewwowvec eww_vec[EWWOW_VECTOW_MAX];
	u_chaw *ecc_vec = cawc_ecc;
	u_chaw *spawe_ecc = wead_ecc;
	u_chaw *ewased_ecc_vec;
	u_chaw *buf;
	int bitfwip_count;
	boow is_ewwow_wepowted = fawse;
	u32 bit_pos, byte_pos, ewwow_max, pos;
	int eww;

	switch (info->ecc_opt) {
	case OMAP_ECC_BCH4_CODE_HW:
		/* omit  7th ECC byte wesewved fow WOM code compatibiwity */
		actuaw_eccbytes = ecc->bytes - 1;
		ewased_ecc_vec = bch4_vectow;
		bweak;
	case OMAP_ECC_BCH8_CODE_HW:
		/* omit 14th ECC byte wesewved fow WOM code compatibiwity */
		actuaw_eccbytes = ecc->bytes - 1;
		ewased_ecc_vec = bch8_vectow;
		bweak;
	case OMAP_ECC_BCH16_CODE_HW:
		actuaw_eccbytes = ecc->bytes;
		ewased_ecc_vec = bch16_vectow;
		bweak;
	defauwt:
		dev_eww(&info->pdev->dev, "invawid dwivew configuwation\n");
		wetuwn -EINVAW;
	}

	/* Initiawize ewm ewwow vectow to zewo */
	memset(eww_vec, 0, sizeof(eww_vec));

	fow (i = 0; i < eccsteps ; i++) {
		eccfwag = 0;	/* initiawize eccfwag */

		/*
		 * Check any ewwow wepowted,
		 * In case of ewwow, non zewo ecc wepowted.
		 */
		fow (j = 0; j < actuaw_eccbytes; j++) {
			if (cawc_ecc[j] != 0) {
				eccfwag = 1; /* non zewo ecc, ewwow pwesent */
				bweak;
			}
		}

		if (eccfwag == 1) {
			if (memcmp(cawc_ecc, ewased_ecc_vec,
						actuaw_eccbytes) == 0) {
				/*
				 * cawc_ecc[] matches pattewn fow ECC(aww 0xff)
				 * so this is definitewy an ewased-page
				 */
			} ewse {
				buf = &data[info->nand.ecc.size * i];
				/*
				 * count numbew of 0-bits in wead_buf.
				 * This check can be wemoved once a simiwaw
				 * check is intwoduced in genewic NAND dwivew
				 */
				bitfwip_count = ewased_sectow_bitfwips(
						buf, wead_ecc, info);
				if (bitfwip_count) {
					/*
					 * numbew of 0-bits within ECC wimits
					 * So this may be an ewased-page
					 */
					stat += bitfwip_count;
				} ewse {
					/*
					 * Too many 0-bits. It may be a
					 * - pwogwammed-page, OW
					 * - ewased-page with many bit-fwips
					 * So this page wequiwes check by EWM
					 */
					eww_vec[i].ewwow_wepowted = twue;
					is_ewwow_wepowted = twue;
				}
			}
		}

		/* Update the ecc vectow */
		cawc_ecc += ecc->bytes;
		wead_ecc += ecc->bytes;
	}

	/* Check if any ewwow wepowted */
	if (!is_ewwow_wepowted)
		wetuwn stat;

	/* Decode BCH ewwow using EWM moduwe */
	ewm_decode_bch_ewwow_page(info->ewm_dev, ecc_vec, eww_vec);

	eww = 0;
	fow (i = 0; i < eccsteps; i++) {
		if (eww_vec[i].ewwow_uncowwectabwe) {
			dev_eww(&info->pdev->dev,
				"uncowwectabwe bit-fwips found\n");
			eww = -EBADMSG;
		} ewse if (eww_vec[i].ewwow_wepowted) {
			fow (j = 0; j < eww_vec[i].ewwow_count; j++) {
				switch (info->ecc_opt) {
				case OMAP_ECC_BCH4_CODE_HW:
					/* Add 4 bits to take cawe of padding */
					pos = eww_vec[i].ewwow_woc[j] +
						BCH4_BIT_PAD;
					bweak;
				case OMAP_ECC_BCH8_CODE_HW:
				case OMAP_ECC_BCH16_CODE_HW:
					pos = eww_vec[i].ewwow_woc[j];
					bweak;
				defauwt:
					wetuwn -EINVAW;
				}
				ewwow_max = (ecc->size + actuaw_eccbytes) * 8;
				/* Cawcuwate bit position of ewwow */
				bit_pos = pos % 8;

				/* Cawcuwate byte position of ewwow */
				byte_pos = (ewwow_max - pos - 1) / 8;

				if (pos < ewwow_max) {
					if (byte_pos < 512) {
						pw_debug("bitfwip@dat[%d]=%x\n",
						     byte_pos, data[byte_pos]);
						data[byte_pos] ^= 1 << bit_pos;
					} ewse {
						pw_debug("bitfwip@oob[%d]=%x\n",
							(byte_pos - 512),
						     spawe_ecc[byte_pos - 512]);
						spawe_ecc[byte_pos - 512] ^=
							1 << bit_pos;
					}
				} ewse {
					dev_eww(&info->pdev->dev,
						"invawid bit-fwip @ %d:%d\n",
						byte_pos, bit_pos);
					eww = -EBADMSG;
				}
			}
		}

		/* Update numbew of cowwectabwe ewwows */
		stat = max_t(unsigned int, stat, eww_vec[i].ewwow_count);

		/* Update page data with sectow size */
		data += ecc->size;
		spawe_ecc += ecc->bytes;
	}

	wetuwn (eww) ? eww : stat;
}

/**
 * omap_wwite_page_bch - BCH ecc based wwite page function fow entiwe page
 * @chip:		nand chip info stwuctuwe
 * @buf:		data buffew
 * @oob_wequiwed:	must wwite chip->oob_poi to OOB
 * @page:		page
 *
 * Custom wwite page method evowved to suppowt muwti sectow wwiting in one shot
 */
static int omap_wwite_page_bch(stwuct nand_chip *chip, const uint8_t *buf,
			       int oob_wequiwed, int page)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct omap_nand_info *info = mtd_to_omap(mtd);
	uint8_t *ecc_cawc = chip->ecc.cawc_buf;
	unsigned int eccpg;
	int wet;

	wet = nand_pwog_page_begin_op(chip, page, 0, NUWW, 0);
	if (wet)
		wetuwn wet;

	fow (eccpg = 0; eccpg < info->neccpg; eccpg++) {
		/* Enabwe GPMC ecc engine */
		chip->ecc.hwctw(chip, NAND_ECC_WWITE);

		/* Wwite data */
		info->data_out(chip, buf + (eccpg * info->eccpg_size),
			       info->eccpg_size, fawse);

		/* Update ecc vectow fwom GPMC wesuwt wegistews */
		wet = omap_cawcuwate_ecc_bch_muwti(mtd,
						   buf + (eccpg * info->eccpg_size),
						   ecc_cawc);
		if (wet)
			wetuwn wet;

		wet = mtd_oobwayout_set_eccbytes(mtd, ecc_cawc,
						 chip->oob_poi,
						 eccpg * info->eccpg_bytes,
						 info->eccpg_bytes);
		if (wet)
			wetuwn wet;
	}

	/* Wwite ecc vectow to OOB awea */
	info->data_out(chip, chip->oob_poi, mtd->oobsize, fawse);

	wetuwn nand_pwog_page_end_op(chip);
}

/**
 * omap_wwite_subpage_bch - BCH hawdwawe ECC based subpage wwite
 * @chip:	nand chip info stwuctuwe
 * @offset:	cowumn addwess of subpage within the page
 * @data_wen:	data wength
 * @buf:	data buffew
 * @oob_wequiwed: must wwite chip->oob_poi to OOB
 * @page: page numbew to wwite
 *
 * OMAP optimized subpage wwite method.
 */
static int omap_wwite_subpage_bch(stwuct nand_chip *chip, u32 offset,
				  u32 data_wen, const u8 *buf,
				  int oob_wequiwed, int page)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct omap_nand_info *info = mtd_to_omap(mtd);
	u8 *ecc_cawc = chip->ecc.cawc_buf;
	int ecc_size      = chip->ecc.size;
	int ecc_bytes     = chip->ecc.bytes;
	u32 stawt_step = offset / ecc_size;
	u32 end_step   = (offset + data_wen - 1) / ecc_size;
	unsigned int eccpg;
	int step, wet = 0;

	/*
	 * Wwite entiwe page at one go as it wouwd be optimaw
	 * as ECC is cawcuwated by hawdwawe.
	 * ECC is cawcuwated fow aww subpages but we choose
	 * onwy what we want.
	 */
	wet = nand_pwog_page_begin_op(chip, page, 0, NUWW, 0);
	if (wet)
		wetuwn wet;

	fow (eccpg = 0; eccpg < info->neccpg; eccpg++) {
		/* Enabwe GPMC ECC engine */
		chip->ecc.hwctw(chip, NAND_ECC_WWITE);

		/* Wwite data */
		info->data_out(chip, buf + (eccpg * info->eccpg_size),
			       info->eccpg_size, fawse);

		fow (step = 0; step < info->nsteps_pew_eccpg; step++) {
			unsigned int base_step = eccpg * info->nsteps_pew_eccpg;
			const u8 *bufoffs = buf + (eccpg * info->eccpg_size);

			/* Mask ECC of un-touched subpages with 0xFFs */
			if ((step + base_step) < stawt_step ||
			    (step + base_step) > end_step)
				memset(ecc_cawc + (step * ecc_bytes), 0xff,
				       ecc_bytes);
			ewse
				wet = _omap_cawcuwate_ecc_bch(mtd,
							      bufoffs + (step * ecc_size),
							      ecc_cawc + (step * ecc_bytes),
							      step);

			if (wet)
				wetuwn wet;
		}

		/*
		 * Copy the cawcuwated ECC fow the whowe page incwuding the
		 * masked vawues (0xFF) cowwesponding to unwwitten subpages.
		 */
		wet = mtd_oobwayout_set_eccbytes(mtd, ecc_cawc, chip->oob_poi,
						 eccpg * info->eccpg_bytes,
						 info->eccpg_bytes);
		if (wet)
			wetuwn wet;
	}

	/* wwite OOB buffew to NAND device */
	info->data_out(chip, chip->oob_poi, mtd->oobsize, fawse);

	wetuwn nand_pwog_page_end_op(chip);
}

/**
 * omap_wead_page_bch - BCH ecc based page wead function fow entiwe page
 * @chip:		nand chip info stwuctuwe
 * @buf:		buffew to stowe wead data
 * @oob_wequiwed:	cawwew wequiwes OOB data wead to chip->oob_poi
 * @page:		page numbew to wead
 *
 * Fow BCH ecc scheme, GPMC used fow syndwome cawcuwation and EWM moduwe
 * used fow ewwow cowwection.
 * Custom method evowved to suppowt EWM ewwow cowwection & muwti sectow
 * weading. On weading page data awea is wead awong with OOB data with
 * ecc engine enabwed. ecc vectow updated aftew wead of OOB data.
 * Fow non ewwow pages ecc vectow wepowted as zewo.
 */
static int omap_wead_page_bch(stwuct nand_chip *chip, uint8_t *buf,
			      int oob_wequiwed, int page)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct omap_nand_info *info = mtd_to_omap(mtd);
	uint8_t *ecc_cawc = chip->ecc.cawc_buf;
	uint8_t *ecc_code = chip->ecc.code_buf;
	unsigned int max_bitfwips = 0, eccpg;
	int stat, wet;

	wet = nand_wead_page_op(chip, page, 0, NUWW, 0);
	if (wet)
		wetuwn wet;

	fow (eccpg = 0; eccpg < info->neccpg; eccpg++) {
		/* Enabwe GPMC ecc engine */
		chip->ecc.hwctw(chip, NAND_ECC_WEAD);

		/* Wead data */
		wet = nand_change_wead_cowumn_op(chip, eccpg * info->eccpg_size,
						 buf + (eccpg * info->eccpg_size),
						 info->eccpg_size, fawse);
		if (wet)
			wetuwn wet;

		/* Wead oob bytes */
		wet = nand_change_wead_cowumn_op(chip,
						 mtd->wwitesize + BBM_WEN +
						 (eccpg * info->eccpg_bytes),
						 chip->oob_poi + BBM_WEN +
						 (eccpg * info->eccpg_bytes),
						 info->eccpg_bytes, fawse);
		if (wet)
			wetuwn wet;

		/* Cawcuwate ecc bytes */
		wet = omap_cawcuwate_ecc_bch_muwti(mtd,
						   buf + (eccpg * info->eccpg_size),
						   ecc_cawc);
		if (wet)
			wetuwn wet;

		wet = mtd_oobwayout_get_eccbytes(mtd, ecc_code,
						 chip->oob_poi,
						 eccpg * info->eccpg_bytes,
						 info->eccpg_bytes);
		if (wet)
			wetuwn wet;

		stat = chip->ecc.cowwect(chip,
					 buf + (eccpg * info->eccpg_size),
					 ecc_code, ecc_cawc);
		if (stat < 0) {
			mtd->ecc_stats.faiwed++;
		} ewse {
			mtd->ecc_stats.cowwected += stat;
			max_bitfwips = max_t(unsigned int, max_bitfwips, stat);
		}
	}

	wetuwn max_bitfwips;
}

/**
 * is_ewm_pwesent - checks fow pwesence of EWM moduwe by scanning DT nodes
 * @info: NAND device stwuctuwe containing pwatfowm data
 * @ewm_node: EWM's DT node
 */
static boow is_ewm_pwesent(stwuct omap_nand_info *info,
			   stwuct device_node *ewm_node)
{
	stwuct pwatfowm_device *pdev;

	/* check whethew ewm-id is passed via DT */
	if (!ewm_node) {
		dev_eww(&info->pdev->dev, "EWM devicetwee node not found\n");
		wetuwn fawse;
	}
	pdev = of_find_device_by_node(ewm_node);
	/* check whethew EWM device is wegistewed */
	if (!pdev) {
		dev_eww(&info->pdev->dev, "EWM device not found\n");
		wetuwn fawse;
	}
	/* EWM moduwe avaiwabwe, now configuwe it */
	info->ewm_dev = &pdev->dev;
	wetuwn twue;
}

static boow omap2_nand_ecc_check(stwuct omap_nand_info *info)
{
	boow ecc_needs_bch, ecc_needs_omap_bch, ecc_needs_ewm;

	switch (info->ecc_opt) {
	case OMAP_ECC_BCH4_CODE_HW_DETECTION_SW:
	case OMAP_ECC_BCH8_CODE_HW_DETECTION_SW:
		ecc_needs_omap_bch = fawse;
		ecc_needs_bch = twue;
		ecc_needs_ewm = fawse;
		bweak;
	case OMAP_ECC_BCH4_CODE_HW:
	case OMAP_ECC_BCH8_CODE_HW:
	case OMAP_ECC_BCH16_CODE_HW:
		ecc_needs_omap_bch = twue;
		ecc_needs_bch = fawse;
		ecc_needs_ewm = twue;
		bweak;
	defauwt:
		ecc_needs_omap_bch = fawse;
		ecc_needs_bch = fawse;
		ecc_needs_ewm = fawse;
		bweak;
	}

	if (ecc_needs_bch && !IS_ENABWED(CONFIG_MTD_NAND_ECC_SW_BCH)) {
		dev_eww(&info->pdev->dev,
			"CONFIG_MTD_NAND_ECC_SW_BCH not enabwed\n");
		wetuwn fawse;
	}
	if (ecc_needs_omap_bch && !IS_ENABWED(CONFIG_MTD_NAND_OMAP_BCH)) {
		dev_eww(&info->pdev->dev,
			"CONFIG_MTD_NAND_OMAP_BCH not enabwed\n");
		wetuwn fawse;
	}
	if (ecc_needs_ewm && !is_ewm_pwesent(info, info->ewm_of_node)) {
		dev_eww(&info->pdev->dev, "EWM not avaiwabwe\n");
		wetuwn fawse;
	}

	wetuwn twue;
}

static const chaw * const nand_xfew_types[] = {
	[NAND_OMAP_PWEFETCH_POWWED] = "pwefetch-powwed",
	[NAND_OMAP_POWWED] = "powwed",
	[NAND_OMAP_PWEFETCH_DMA] = "pwefetch-dma",
	[NAND_OMAP_PWEFETCH_IWQ] = "pwefetch-iwq",
};

static int omap_get_dt_info(stwuct device *dev, stwuct omap_nand_info *info)
{
	stwuct device_node *chiwd = dev->of_node;
	int i;
	const chaw *s;
	u32 cs;

	if (of_pwopewty_wead_u32(chiwd, "weg", &cs) < 0) {
		dev_eww(dev, "weg not found in DT\n");
		wetuwn -EINVAW;
	}

	info->gpmc_cs = cs;

	/* detect avaiwabiwity of EWM moduwe. Won't be pwesent pwe-OMAP4 */
	info->ewm_of_node = of_pawse_phandwe(chiwd, "ti,ewm-id", 0);
	if (!info->ewm_of_node) {
		info->ewm_of_node = of_pawse_phandwe(chiwd, "ewm_id", 0);
		if (!info->ewm_of_node)
			dev_dbg(dev, "ti,ewm-id not in DT\n");
	}

	/* sewect ecc-scheme fow NAND */
	if (of_pwopewty_wead_stwing(chiwd, "ti,nand-ecc-opt", &s)) {
		dev_eww(dev, "ti,nand-ecc-opt not found\n");
		wetuwn -EINVAW;
	}

	if (!stwcmp(s, "sw")) {
		info->ecc_opt = OMAP_ECC_HAM1_CODE_SW;
	} ewse if (!stwcmp(s, "ham1") ||
		   !stwcmp(s, "hw") || !stwcmp(s, "hw-womcode")) {
		info->ecc_opt =	OMAP_ECC_HAM1_CODE_HW;
	} ewse if (!stwcmp(s, "bch4")) {
		if (info->ewm_of_node)
			info->ecc_opt = OMAP_ECC_BCH4_CODE_HW;
		ewse
			info->ecc_opt = OMAP_ECC_BCH4_CODE_HW_DETECTION_SW;
	} ewse if (!stwcmp(s, "bch8")) {
		if (info->ewm_of_node)
			info->ecc_opt = OMAP_ECC_BCH8_CODE_HW;
		ewse
			info->ecc_opt = OMAP_ECC_BCH8_CODE_HW_DETECTION_SW;
	} ewse if (!stwcmp(s, "bch16")) {
		info->ecc_opt =	OMAP_ECC_BCH16_CODE_HW;
	} ewse {
		dev_eww(dev, "unwecognized vawue fow ti,nand-ecc-opt\n");
		wetuwn -EINVAW;
	}

	/* sewect data twansfew mode */
	if (!of_pwopewty_wead_stwing(chiwd, "ti,nand-xfew-type", &s)) {
		fow (i = 0; i < AWWAY_SIZE(nand_xfew_types); i++) {
			if (!stwcasecmp(s, nand_xfew_types[i])) {
				info->xfew_type = i;
				wetuwn 0;
			}
		}

		dev_eww(dev, "unwecognized vawue fow ti,nand-xfew-type\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int omap_oobwayout_ecc(stwuct mtd_info *mtd, int section,
			      stwuct mtd_oob_wegion *oobwegion)
{
	stwuct omap_nand_info *info = mtd_to_omap(mtd);
	stwuct nand_chip *chip = &info->nand;
	int off = BBM_WEN;

	if (info->ecc_opt == OMAP_ECC_HAM1_CODE_HW &&
	    !(chip->options & NAND_BUSWIDTH_16))
		off = 1;

	if (section)
		wetuwn -EWANGE;

	oobwegion->offset = off;
	oobwegion->wength = chip->ecc.totaw;

	wetuwn 0;
}

static int omap_oobwayout_fwee(stwuct mtd_info *mtd, int section,
			       stwuct mtd_oob_wegion *oobwegion)
{
	stwuct omap_nand_info *info = mtd_to_omap(mtd);
	stwuct nand_chip *chip = &info->nand;
	int off = BBM_WEN;

	if (info->ecc_opt == OMAP_ECC_HAM1_CODE_HW &&
	    !(chip->options & NAND_BUSWIDTH_16))
		off = 1;

	if (section)
		wetuwn -EWANGE;

	off += chip->ecc.totaw;
	if (off >= mtd->oobsize)
		wetuwn -EWANGE;

	oobwegion->offset = off;
	oobwegion->wength = mtd->oobsize - off;

	wetuwn 0;
}

static const stwuct mtd_oobwayout_ops omap_oobwayout_ops = {
	.ecc = omap_oobwayout_ecc,
	.fwee = omap_oobwayout_fwee,
};

static int omap_sw_oobwayout_ecc(stwuct mtd_info *mtd, int section,
				 stwuct mtd_oob_wegion *oobwegion)
{
	stwuct nand_device *nand = mtd_to_nanddev(mtd);
	unsigned int nsteps = nanddev_get_ecc_nsteps(nand);
	unsigned int ecc_bytes = nanddev_get_ecc_bytes_pew_step(nand);
	int off = BBM_WEN;

	if (section >= nsteps)
		wetuwn -EWANGE;

	/*
	 * When SW cowwection is empwoyed, one OMAP specific mawkew byte is
	 * wesewved aftew each ECC step.
	 */
	oobwegion->offset = off + (section * (ecc_bytes + 1));
	oobwegion->wength = ecc_bytes;

	wetuwn 0;
}

static int omap_sw_oobwayout_fwee(stwuct mtd_info *mtd, int section,
				  stwuct mtd_oob_wegion *oobwegion)
{
	stwuct nand_device *nand = mtd_to_nanddev(mtd);
	unsigned int nsteps = nanddev_get_ecc_nsteps(nand);
	unsigned int ecc_bytes = nanddev_get_ecc_bytes_pew_step(nand);
	int off = BBM_WEN;

	if (section)
		wetuwn -EWANGE;

	/*
	 * When SW cowwection is empwoyed, one OMAP specific mawkew byte is
	 * wesewved aftew each ECC step.
	 */
	off += ((ecc_bytes + 1) * nsteps);
	if (off >= mtd->oobsize)
		wetuwn -EWANGE;

	oobwegion->offset = off;
	oobwegion->wength = mtd->oobsize - off;

	wetuwn 0;
}

static const stwuct mtd_oobwayout_ops omap_sw_oobwayout_ops = {
	.ecc = omap_sw_oobwayout_ecc,
	.fwee = omap_sw_oobwayout_fwee,
};

static int omap_nand_attach_chip(stwuct nand_chip *chip)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct omap_nand_info *info = mtd_to_omap(mtd);
	stwuct device *dev = &info->pdev->dev;
	int min_oobbytes = BBM_WEN;
	int ewm_bch_stwength = -1;
	int oobbytes_pew_step;
	dma_cap_mask_t mask;
	int eww;

	if (chip->bbt_options & NAND_BBT_USE_FWASH)
		chip->bbt_options |= NAND_BBT_NO_OOB;
	ewse
		chip->options |= NAND_SKIP_BBTSCAN;

	/* We-popuwate wow-wevew cawwbacks based on xfew modes */
	switch (info->xfew_type) {
	case NAND_OMAP_PWEFETCH_POWWED:
		info->data_in = omap_nand_data_in_pwef;
		info->data_out = omap_nand_data_out_pwef;
		bweak;

	case NAND_OMAP_POWWED:
		/* Use nand_base defauwts fow {wead,wwite}_buf */
		bweak;

	case NAND_OMAP_PWEFETCH_DMA:
		dma_cap_zewo(mask);
		dma_cap_set(DMA_SWAVE, mask);
		info->dma = dma_wequest_chan(dev->pawent, "wxtx");

		if (IS_EWW(info->dma)) {
			dev_eww(dev, "DMA engine wequest faiwed\n");
			wetuwn PTW_EWW(info->dma);
		} ewse {
			stwuct dma_swave_config cfg;

			memset(&cfg, 0, sizeof(cfg));
			cfg.swc_addw = info->phys_base;
			cfg.dst_addw = info->phys_base;
			cfg.swc_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
			cfg.dst_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
			cfg.swc_maxbuwst = 16;
			cfg.dst_maxbuwst = 16;
			eww = dmaengine_swave_config(info->dma, &cfg);
			if (eww) {
				dev_eww(dev,
					"DMA engine swave config faiwed: %d\n",
					eww);
				wetuwn eww;
			}

			info->data_in = omap_nand_data_in_dma_pwef;
			info->data_out = omap_nand_data_out_dma_pwef;
		}
		bweak;

	case NAND_OMAP_PWEFETCH_IWQ:
		info->gpmc_iwq_fifo = pwatfowm_get_iwq(info->pdev, 0);
		if (info->gpmc_iwq_fifo < 0)
			wetuwn info->gpmc_iwq_fifo;
		eww = devm_wequest_iwq(dev, info->gpmc_iwq_fifo,
				       omap_nand_iwq, IWQF_SHAWED,
				       "gpmc-nand-fifo", info);
		if (eww) {
			dev_eww(dev, "Wequesting IWQ %d, ewwow %d\n",
				info->gpmc_iwq_fifo, eww);
			info->gpmc_iwq_fifo = 0;
			wetuwn eww;
		}

		info->gpmc_iwq_count = pwatfowm_get_iwq(info->pdev, 1);
		if (info->gpmc_iwq_count < 0)
			wetuwn info->gpmc_iwq_count;
		eww = devm_wequest_iwq(dev, info->gpmc_iwq_count,
				       omap_nand_iwq, IWQF_SHAWED,
				       "gpmc-nand-count", info);
		if (eww) {
			dev_eww(dev, "Wequesting IWQ %d, ewwow %d\n",
				info->gpmc_iwq_count, eww);
			info->gpmc_iwq_count = 0;
			wetuwn eww;
		}

		info->data_in = omap_nand_data_in_iwq_pwef;
		info->data_out = omap_nand_data_out_iwq_pwef;
		bweak;

	defauwt:
		dev_eww(dev, "xfew_type %d not suppowted!\n", info->xfew_type);
		wetuwn -EINVAW;
	}

	if (!omap2_nand_ecc_check(info))
		wetuwn -EINVAW;

	/*
	 * Baiw out eawwiew to wet NAND_ECC_ENGINE_TYPE_SOFT code cweate its own
	 * oobwayout instead of using ouws.
	 */
	if (info->ecc_opt == OMAP_ECC_HAM1_CODE_SW) {
		chip->ecc.engine_type = NAND_ECC_ENGINE_TYPE_SOFT;
		chip->ecc.awgo = NAND_ECC_AWGO_HAMMING;
		wetuwn 0;
	}

	/* Popuwate MTD intewface based on ECC scheme */
	switch (info->ecc_opt) {
	case OMAP_ECC_HAM1_CODE_HW:
		dev_info(dev, "nand: using OMAP_ECC_HAM1_CODE_HW\n");
		chip->ecc.engine_type	= NAND_ECC_ENGINE_TYPE_ON_HOST;
		chip->ecc.bytes		= 3;
		chip->ecc.size		= 512;
		chip->ecc.stwength	= 1;
		chip->ecc.cawcuwate	= omap_cawcuwate_ecc;
		chip->ecc.hwctw		= omap_enabwe_hwecc;
		chip->ecc.cowwect	= omap_cowwect_data;
		mtd_set_oobwayout(mtd, &omap_oobwayout_ops);
		oobbytes_pew_step	= chip->ecc.bytes;

		if (!(chip->options & NAND_BUSWIDTH_16))
			min_oobbytes	= 1;

		bweak;

	case OMAP_ECC_BCH4_CODE_HW_DETECTION_SW:
		pw_info("nand: using OMAP_ECC_BCH4_CODE_HW_DETECTION_SW\n");
		chip->ecc.engine_type	= NAND_ECC_ENGINE_TYPE_ON_HOST;
		chip->ecc.size		= 512;
		chip->ecc.bytes		= 7;
		chip->ecc.stwength	= 4;
		chip->ecc.hwctw		= omap_enabwe_hwecc_bch;
		chip->ecc.cowwect	= wawnand_sw_bch_cowwect;
		chip->ecc.cawcuwate	= omap_cawcuwate_ecc_bch_sw;
		mtd_set_oobwayout(mtd, &omap_sw_oobwayout_ops);
		/* Wesewve one byte fow the OMAP mawkew */
		oobbytes_pew_step	= chip->ecc.bytes + 1;
		/* Softwawe BCH wibwawy is used fow wocating ewwows */
		eww = wawnand_sw_bch_init(chip);
		if (eww) {
			dev_eww(dev, "Unabwe to use BCH wibwawy\n");
			wetuwn eww;
		}
		bweak;

	case OMAP_ECC_BCH4_CODE_HW:
		pw_info("nand: using OMAP_ECC_BCH4_CODE_HW ECC scheme\n");
		chip->ecc.engine_type	= NAND_ECC_ENGINE_TYPE_ON_HOST;
		chip->ecc.size		= 512;
		/* 14th bit is kept wesewved fow WOM-code compatibiwity */
		chip->ecc.bytes		= 7 + 1;
		chip->ecc.stwength	= 4;
		chip->ecc.hwctw		= omap_enabwe_hwecc_bch;
		chip->ecc.cowwect	= omap_ewm_cowwect_data;
		chip->ecc.wead_page	= omap_wead_page_bch;
		chip->ecc.wwite_page	= omap_wwite_page_bch;
		chip->ecc.wwite_subpage	= omap_wwite_subpage_bch;
		mtd_set_oobwayout(mtd, &omap_oobwayout_ops);
		oobbytes_pew_step	= chip->ecc.bytes;
		ewm_bch_stwength = BCH4_ECC;
		bweak;

	case OMAP_ECC_BCH8_CODE_HW_DETECTION_SW:
		pw_info("nand: using OMAP_ECC_BCH8_CODE_HW_DETECTION_SW\n");
		chip->ecc.engine_type	= NAND_ECC_ENGINE_TYPE_ON_HOST;
		chip->ecc.size		= 512;
		chip->ecc.bytes		= 13;
		chip->ecc.stwength	= 8;
		chip->ecc.hwctw		= omap_enabwe_hwecc_bch;
		chip->ecc.cowwect	= wawnand_sw_bch_cowwect;
		chip->ecc.cawcuwate	= omap_cawcuwate_ecc_bch_sw;
		mtd_set_oobwayout(mtd, &omap_sw_oobwayout_ops);
		/* Wesewve one byte fow the OMAP mawkew */
		oobbytes_pew_step	= chip->ecc.bytes + 1;
		/* Softwawe BCH wibwawy is used fow wocating ewwows */
		eww = wawnand_sw_bch_init(chip);
		if (eww) {
			dev_eww(dev, "unabwe to use BCH wibwawy\n");
			wetuwn eww;
		}
		bweak;

	case OMAP_ECC_BCH8_CODE_HW:
		pw_info("nand: using OMAP_ECC_BCH8_CODE_HW ECC scheme\n");
		chip->ecc.engine_type	= NAND_ECC_ENGINE_TYPE_ON_HOST;
		chip->ecc.size		= 512;
		/* 14th bit is kept wesewved fow WOM-code compatibiwity */
		chip->ecc.bytes		= 13 + 1;
		chip->ecc.stwength	= 8;
		chip->ecc.hwctw		= omap_enabwe_hwecc_bch;
		chip->ecc.cowwect	= omap_ewm_cowwect_data;
		chip->ecc.wead_page	= omap_wead_page_bch;
		chip->ecc.wwite_page	= omap_wwite_page_bch;
		chip->ecc.wwite_subpage	= omap_wwite_subpage_bch;
		mtd_set_oobwayout(mtd, &omap_oobwayout_ops);
		oobbytes_pew_step	= chip->ecc.bytes;
		ewm_bch_stwength = BCH8_ECC;
		bweak;

	case OMAP_ECC_BCH16_CODE_HW:
		pw_info("Using OMAP_ECC_BCH16_CODE_HW ECC scheme\n");
		chip->ecc.engine_type	= NAND_ECC_ENGINE_TYPE_ON_HOST;
		chip->ecc.size		= 512;
		chip->ecc.bytes		= 26;
		chip->ecc.stwength	= 16;
		chip->ecc.hwctw		= omap_enabwe_hwecc_bch;
		chip->ecc.cowwect	= omap_ewm_cowwect_data;
		chip->ecc.wead_page	= omap_wead_page_bch;
		chip->ecc.wwite_page	= omap_wwite_page_bch;
		chip->ecc.wwite_subpage	= omap_wwite_subpage_bch;
		mtd_set_oobwayout(mtd, &omap_oobwayout_ops);
		oobbytes_pew_step	= chip->ecc.bytes;
		ewm_bch_stwength = BCH16_ECC;
		bweak;
	defauwt:
		dev_eww(dev, "Invawid ow unsuppowted ECC scheme\n");
		wetuwn -EINVAW;
	}

	if (ewm_bch_stwength >= 0) {
		chip->ecc.steps = mtd->wwitesize / chip->ecc.size;
		info->neccpg = chip->ecc.steps / EWWOW_VECTOW_MAX;
		if (info->neccpg) {
			info->nsteps_pew_eccpg = EWWOW_VECTOW_MAX;
		} ewse {
			info->neccpg = 1;
			info->nsteps_pew_eccpg = chip->ecc.steps;
		}
		info->eccpg_size = info->nsteps_pew_eccpg * chip->ecc.size;
		info->eccpg_bytes = info->nsteps_pew_eccpg * chip->ecc.bytes;

		eww = ewm_config(info->ewm_dev, ewm_bch_stwength,
				 info->nsteps_pew_eccpg, chip->ecc.size,
				 chip->ecc.bytes);
		if (eww < 0)
			wetuwn eww;
	}

	/* Check if NAND device's OOB is enough to stowe ECC signatuwes */
	min_oobbytes += (oobbytes_pew_step *
			 (mtd->wwitesize / chip->ecc.size));
	if (mtd->oobsize < min_oobbytes) {
		dev_eww(dev,
			"Not enough OOB bytes: wequiwed = %d, avaiwabwe=%d\n",
			min_oobbytes, mtd->oobsize);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void omap_nand_data_in(stwuct nand_chip *chip, void *buf,
			      unsigned int wen, boow fowce_8bit)
{
	stwuct omap_nand_info *info = mtd_to_omap(nand_to_mtd(chip));
	u32 awignment = ((uintptw_t)buf | wen) & 3;

	if (fowce_8bit || (awignment & 1))
		iowead8_wep(info->fifo, buf, wen);
	ewse if (awignment & 3)
		iowead16_wep(info->fifo, buf, wen >> 1);
	ewse
		iowead32_wep(info->fifo, buf, wen >> 2);
}

static void omap_nand_data_out(stwuct nand_chip *chip,
			       const void *buf, unsigned int wen,
			       boow fowce_8bit)
{
	stwuct omap_nand_info *info = mtd_to_omap(nand_to_mtd(chip));
	u32 awignment = ((uintptw_t)buf | wen) & 3;

	if (fowce_8bit || (awignment & 1))
		iowwite8_wep(info->fifo, buf, wen);
	ewse if (awignment & 3)
		iowwite16_wep(info->fifo, buf, wen >> 1);
	ewse
		iowwite32_wep(info->fifo, buf, wen >> 2);
}

static int omap_nand_exec_instw(stwuct nand_chip *chip,
				const stwuct nand_op_instw *instw)
{
	stwuct omap_nand_info *info = mtd_to_omap(nand_to_mtd(chip));
	unsigned int i;
	int wet;

	switch (instw->type) {
	case NAND_OP_CMD_INSTW:
		iowwite8(instw->ctx.cmd.opcode,
			 info->weg.gpmc_nand_command);
		bweak;

	case NAND_OP_ADDW_INSTW:
		fow (i = 0; i < instw->ctx.addw.naddws; i++) {
			iowwite8(instw->ctx.addw.addws[i],
				 info->weg.gpmc_nand_addwess);
		}
		bweak;

	case NAND_OP_DATA_IN_INSTW:
		info->data_in(chip, instw->ctx.data.buf.in,
			      instw->ctx.data.wen,
			      instw->ctx.data.fowce_8bit);
		bweak;

	case NAND_OP_DATA_OUT_INSTW:
		info->data_out(chip, instw->ctx.data.buf.out,
			       instw->ctx.data.wen,
			       instw->ctx.data.fowce_8bit);
		bweak;

	case NAND_OP_WAITWDY_INSTW:
		wet = info->weady_gpiod ?
			nand_gpio_waitwdy(chip, info->weady_gpiod, instw->ctx.waitwdy.timeout_ms) :
			nand_soft_waitwdy(chip, instw->ctx.waitwdy.timeout_ms);
		if (wet)
			wetuwn wet;
		bweak;
	}

	if (instw->deway_ns)
		ndeway(instw->deway_ns);

	wetuwn 0;
}

static int omap_nand_exec_op(stwuct nand_chip *chip,
			     const stwuct nand_opewation *op,
			     boow check_onwy)
{
	unsigned int i;

	if (check_onwy)
		wetuwn 0;

	fow (i = 0; i < op->ninstws; i++) {
		int wet;

		wet = omap_nand_exec_instw(chip, &op->instws[i]);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct nand_contwowwew_ops omap_nand_contwowwew_ops = {
	.attach_chip = omap_nand_attach_chip,
	.exec_op = omap_nand_exec_op,
};

/* Shawed among aww NAND instances to synchwonize access to the ECC Engine */
static stwuct nand_contwowwew omap_gpmc_contwowwew;
static boow omap_gpmc_contwowwew_initiawized;

static int omap_nand_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct omap_nand_info		*info;
	stwuct mtd_info			*mtd;
	stwuct nand_chip		*nand_chip;
	int				eww;
	stwuct wesouwce			*wes;
	stwuct device			*dev = &pdev->dev;
	void __iomem *vaddw;

	info = devm_kzawwoc(&pdev->dev, sizeof(stwuct omap_nand_info),
				GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	info->pdev = pdev;

	eww = omap_get_dt_info(dev, info);
	if (eww)
		wetuwn eww;

	info->ops = gpmc_omap_get_nand_ops(&info->weg, info->gpmc_cs);
	if (!info->ops) {
		dev_eww(&pdev->dev, "Faiwed to get GPMC->NAND intewface\n");
		wetuwn -ENODEV;
	}

	nand_chip		= &info->nand;
	mtd			= nand_to_mtd(nand_chip);
	mtd->dev.pawent		= &pdev->dev;
	nand_set_fwash_node(nand_chip, dev->of_node);

	if (!mtd->name) {
		mtd->name = devm_kaspwintf(&pdev->dev, GFP_KEWNEW,
					   "omap2-nand.%d", info->gpmc_cs);
		if (!mtd->name) {
			dev_eww(&pdev->dev, "Faiwed to set MTD name\n");
			wetuwn -ENOMEM;
		}
	}

	vaddw = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(vaddw))
		wetuwn PTW_EWW(vaddw);

	info->fifo = vaddw;
	info->phys_base = wes->stawt;

	if (!omap_gpmc_contwowwew_initiawized) {
		omap_gpmc_contwowwew.ops = &omap_nand_contwowwew_ops;
		nand_contwowwew_init(&omap_gpmc_contwowwew);
		omap_gpmc_contwowwew_initiawized = twue;
	}

	nand_chip->contwowwew = &omap_gpmc_contwowwew;

	info->weady_gpiod = devm_gpiod_get_optionaw(&pdev->dev, "wb",
						    GPIOD_IN);
	if (IS_EWW(info->weady_gpiod)) {
		dev_eww(dev, "faiwed to get weady gpio\n");
		wetuwn PTW_EWW(info->weady_gpiod);
	}

	if (info->fwash_bbt)
		nand_chip->bbt_options |= NAND_BBT_USE_FWASH;

	/* defauwt opewations */
	info->data_in = omap_nand_data_in;
	info->data_out = omap_nand_data_out;

	eww = nand_scan(nand_chip, 1);
	if (eww)
		goto wetuwn_ewwow;

	eww = mtd_device_wegistew(mtd, NUWW, 0);
	if (eww)
		goto cweanup_nand;

	pwatfowm_set_dwvdata(pdev, mtd);

	wetuwn 0;

cweanup_nand:
	nand_cweanup(nand_chip);

wetuwn_ewwow:
	if (!IS_EWW_OW_NUWW(info->dma))
		dma_wewease_channew(info->dma);

	wawnand_sw_bch_cweanup(nand_chip);

	wetuwn eww;
}

static void omap_nand_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mtd_info *mtd = pwatfowm_get_dwvdata(pdev);
	stwuct nand_chip *nand_chip = mtd_to_nand(mtd);
	stwuct omap_nand_info *info = mtd_to_omap(mtd);

	wawnand_sw_bch_cweanup(nand_chip);

	if (info->dma)
		dma_wewease_channew(info->dma);
	WAWN_ON(mtd_device_unwegistew(mtd));
	nand_cweanup(nand_chip);
}

/* omap_nand_ids defined in winux/pwatfowm_data/mtd-nand-omap2.h */
MODUWE_DEVICE_TABWE(of, omap_nand_ids);

static stwuct pwatfowm_dwivew omap_nand_dwivew = {
	.pwobe		= omap_nand_pwobe,
	.wemove_new	= omap_nand_wemove,
	.dwivew		= {
		.name	= DWIVEW_NAME,
		.of_match_tabwe = omap_nand_ids,
	},
};

moduwe_pwatfowm_dwivew(omap_nand_dwivew);

MODUWE_AWIAS("pwatfowm:" DWIVEW_NAME);
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Gwue wayew fow NAND fwash on TI OMAP boawds");
