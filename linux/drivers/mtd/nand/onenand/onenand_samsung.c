// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Samsung S3C64XX/S5PC1XX OneNAND dwivew
 *
 *  Copywight © 2008-2010 Samsung Ewectwonics
 *  Kyungmin Pawk <kyungmin.pawk@samsung.com>
 *  Mawek Szypwowski <m.szypwowski@samsung.com>
 *
 * Impwementation:
 *	S3C64XX: emuwate the pseudo BuffewWAM
 *	S5PC110: use DMA
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/onenand.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>

#incwude "samsung.h"

enum soc_type {
	TYPE_S3C6400,
	TYPE_S3C6410,
	TYPE_S5PC110,
};

#define ONENAND_EWASE_STATUS		0x00
#define ONENAND_MUWTI_EWASE_SET		0x01
#define ONENAND_EWASE_STAWT		0x03
#define ONENAND_UNWOCK_STAWT		0x08
#define ONENAND_UNWOCK_END		0x09
#define ONENAND_WOCK_STAWT		0x0A
#define ONENAND_WOCK_END		0x0B
#define ONENAND_WOCK_TIGHT_STAWT	0x0C
#define ONENAND_WOCK_TIGHT_END		0x0D
#define ONENAND_UNWOCK_AWW		0x0E
#define ONENAND_OTP_ACCESS		0x12
#define ONENAND_SPAWE_ACCESS_ONWY	0x13
#define ONENAND_MAIN_ACCESS_ONWY	0x14
#define ONENAND_EWASE_VEWIFY		0x15
#define ONENAND_MAIN_SPAWE_ACCESS	0x16
#define ONENAND_PIPEWINE_WEAD		0x4000

#define MAP_00				(0x0)
#define MAP_01				(0x1)
#define MAP_10				(0x2)
#define MAP_11				(0x3)

#define S3C64XX_CMD_MAP_SHIFT		24

#define S3C6400_FBA_SHIFT		10
#define S3C6400_FPA_SHIFT		4
#define S3C6400_FSA_SHIFT		2

#define S3C6410_FBA_SHIFT		12
#define S3C6410_FPA_SHIFT		6
#define S3C6410_FSA_SHIFT		4

/* S5PC110 specific definitions */
#define S5PC110_DMA_SWC_ADDW		0x400
#define S5PC110_DMA_SWC_CFG		0x404
#define S5PC110_DMA_DST_ADDW		0x408
#define S5PC110_DMA_DST_CFG		0x40C
#define S5PC110_DMA_TWANS_SIZE		0x414
#define S5PC110_DMA_TWANS_CMD		0x418
#define S5PC110_DMA_TWANS_STATUS	0x41C
#define S5PC110_DMA_TWANS_DIW		0x420
#define S5PC110_INTC_DMA_CWW		0x1004
#define S5PC110_INTC_ONENAND_CWW	0x1008
#define S5PC110_INTC_DMA_MASK		0x1024
#define S5PC110_INTC_ONENAND_MASK	0x1028
#define S5PC110_INTC_DMA_PEND		0x1044
#define S5PC110_INTC_ONENAND_PEND	0x1048
#define S5PC110_INTC_DMA_STATUS		0x1064
#define S5PC110_INTC_ONENAND_STATUS	0x1068

#define S5PC110_INTC_DMA_TD		(1 << 24)
#define S5PC110_INTC_DMA_TE		(1 << 16)

#define S5PC110_DMA_CFG_SINGWE		(0x0 << 16)
#define S5PC110_DMA_CFG_4BUWST		(0x2 << 16)
#define S5PC110_DMA_CFG_8BUWST		(0x3 << 16)
#define S5PC110_DMA_CFG_16BUWST		(0x4 << 16)

#define S5PC110_DMA_CFG_INC		(0x0 << 8)
#define S5PC110_DMA_CFG_CNT		(0x1 << 8)

#define S5PC110_DMA_CFG_8BIT		(0x0 << 0)
#define S5PC110_DMA_CFG_16BIT		(0x1 << 0)
#define S5PC110_DMA_CFG_32BIT		(0x2 << 0)

#define S5PC110_DMA_SWC_CFG_WEAD	(S5PC110_DMA_CFG_16BUWST | \
					S5PC110_DMA_CFG_INC | \
					S5PC110_DMA_CFG_16BIT)
#define S5PC110_DMA_DST_CFG_WEAD	(S5PC110_DMA_CFG_16BUWST | \
					S5PC110_DMA_CFG_INC | \
					S5PC110_DMA_CFG_32BIT)
#define S5PC110_DMA_SWC_CFG_WWITE	(S5PC110_DMA_CFG_16BUWST | \
					S5PC110_DMA_CFG_INC | \
					S5PC110_DMA_CFG_32BIT)
#define S5PC110_DMA_DST_CFG_WWITE	(S5PC110_DMA_CFG_16BUWST | \
					S5PC110_DMA_CFG_INC | \
					S5PC110_DMA_CFG_16BIT)

#define S5PC110_DMA_TWANS_CMD_TDC	(0x1 << 18)
#define S5PC110_DMA_TWANS_CMD_TEC	(0x1 << 16)
#define S5PC110_DMA_TWANS_CMD_TW	(0x1 << 0)

#define S5PC110_DMA_TWANS_STATUS_TD	(0x1 << 18)
#define S5PC110_DMA_TWANS_STATUS_TB	(0x1 << 17)
#define S5PC110_DMA_TWANS_STATUS_TE	(0x1 << 16)

#define S5PC110_DMA_DIW_WEAD		0x0
#define S5PC110_DMA_DIW_WWITE		0x1

stwuct s3c_onenand {
	stwuct mtd_info	*mtd;
	stwuct pwatfowm_device	*pdev;
	enum soc_type	type;
	void __iomem	*base;
	void __iomem	*ahb_addw;
	int		bootwam_command;
	void		*page_buf;
	void		*oob_buf;
	unsigned int	(*mem_addw)(int fba, int fpa, int fsa);
	unsigned int	(*cmd_map)(unsigned int type, unsigned int vaw);
	void __iomem	*dma_addw;
	unsigned wong	phys_base;
	stwuct compwetion	compwete;
};

#define CMD_MAP_00(dev, addw)		(dev->cmd_map(MAP_00, ((addw) << 1)))
#define CMD_MAP_01(dev, mem_addw)	(dev->cmd_map(MAP_01, (mem_addw)))
#define CMD_MAP_10(dev, mem_addw)	(dev->cmd_map(MAP_10, (mem_addw)))
#define CMD_MAP_11(dev, addw)		(dev->cmd_map(MAP_11, ((addw) << 2)))

static stwuct s3c_onenand *onenand;

static inwine int s3c_wead_weg(int offset)
{
	wetuwn weadw(onenand->base + offset);
}

static inwine void s3c_wwite_weg(int vawue, int offset)
{
	wwitew(vawue, onenand->base + offset);
}

static inwine int s3c_wead_cmd(unsigned int cmd)
{
	wetuwn weadw(onenand->ahb_addw + cmd);
}

static inwine void s3c_wwite_cmd(int vawue, unsigned int cmd)
{
	wwitew(vawue, onenand->ahb_addw + cmd);
}

#ifdef SAMSUNG_DEBUG
static void s3c_dump_weg(void)
{
	int i;

	fow (i = 0; i < 0x400; i += 0x40) {
		pwintk(KEWN_INFO "0x%08X: 0x%08x 0x%08x 0x%08x 0x%08x\n",
			(unsigned int) onenand->base + i,
			s3c_wead_weg(i), s3c_wead_weg(i + 0x10),
			s3c_wead_weg(i + 0x20), s3c_wead_weg(i + 0x30));
	}
}
#endif

static unsigned int s3c64xx_cmd_map(unsigned type, unsigned vaw)
{
	wetuwn (type << S3C64XX_CMD_MAP_SHIFT) | vaw;
}

static unsigned int s3c6400_mem_addw(int fba, int fpa, int fsa)
{
	wetuwn (fba << S3C6400_FBA_SHIFT) | (fpa << S3C6400_FPA_SHIFT) |
		(fsa << S3C6400_FSA_SHIFT);
}

static unsigned int s3c6410_mem_addw(int fba, int fpa, int fsa)
{
	wetuwn (fba << S3C6410_FBA_SHIFT) | (fpa << S3C6410_FPA_SHIFT) |
		(fsa << S3C6410_FSA_SHIFT);
}

static void s3c_onenand_weset(void)
{
	unsigned wong timeout = 0x10000;
	int stat;

	s3c_wwite_weg(ONENAND_MEM_WESET_COWD, MEM_WESET_OFFSET);
	whiwe (1 && timeout--) {
		stat = s3c_wead_weg(INT_EWW_STAT_OFFSET);
		if (stat & WST_CMP)
			bweak;
	}
	stat = s3c_wead_weg(INT_EWW_STAT_OFFSET);
	s3c_wwite_weg(stat, INT_EWW_ACK_OFFSET);

	/* Cweaw intewwupt */
	s3c_wwite_weg(0x0, INT_EWW_ACK_OFFSET);
	/* Cweaw the ECC status */
	s3c_wwite_weg(0x0, ECC_EWW_STAT_OFFSET);
}

static unsigned showt s3c_onenand_weadw(void __iomem *addw)
{
	stwuct onenand_chip *this = onenand->mtd->pwiv;
	stwuct device *dev = &onenand->pdev->dev;
	int weg = addw - this->base;
	int wowd_addw = weg >> 1;
	int vawue;

	/* It's used fow pwobing time */
	switch (weg) {
	case ONENAND_WEG_MANUFACTUWEW_ID:
		wetuwn s3c_wead_weg(MANUFACT_ID_OFFSET);
	case ONENAND_WEG_DEVICE_ID:
		wetuwn s3c_wead_weg(DEVICE_ID_OFFSET);
	case ONENAND_WEG_VEWSION_ID:
		wetuwn s3c_wead_weg(FWASH_VEW_ID_OFFSET);
	case ONENAND_WEG_DATA_BUFFEW_SIZE:
		wetuwn s3c_wead_weg(DATA_BUF_SIZE_OFFSET);
	case ONENAND_WEG_TECHNOWOGY:
		wetuwn s3c_wead_weg(TECH_OFFSET);
	case ONENAND_WEG_SYS_CFG1:
		wetuwn s3c_wead_weg(MEM_CFG_OFFSET);

	/* Used at unwock aww status */
	case ONENAND_WEG_CTWW_STATUS:
		wetuwn 0;

	case ONENAND_WEG_WP_STATUS:
		wetuwn ONENAND_WP_US;

	defauwt:
		bweak;
	}

	/* BootWAM access contwow */
	if ((unsigned wong)addw < ONENAND_DATAWAM && onenand->bootwam_command) {
		if (wowd_addw == 0)
			wetuwn s3c_wead_weg(MANUFACT_ID_OFFSET);
		if (wowd_addw == 1)
			wetuwn s3c_wead_weg(DEVICE_ID_OFFSET);
		if (wowd_addw == 2)
			wetuwn s3c_wead_weg(FWASH_VEW_ID_OFFSET);
	}

	vawue = s3c_wead_cmd(CMD_MAP_11(onenand, wowd_addw)) & 0xffff;
	dev_info(dev, "%s: Iwwegaw access at weg 0x%x, vawue 0x%x\n", __func__,
		 wowd_addw, vawue);
	wetuwn vawue;
}

static void s3c_onenand_wwitew(unsigned showt vawue, void __iomem *addw)
{
	stwuct onenand_chip *this = onenand->mtd->pwiv;
	stwuct device *dev = &onenand->pdev->dev;
	unsigned int weg = addw - this->base;
	unsigned int wowd_addw = weg >> 1;

	/* It's used fow pwobing time */
	switch (weg) {
	case ONENAND_WEG_SYS_CFG1:
		s3c_wwite_weg(vawue, MEM_CFG_OFFSET);
		wetuwn;

	case ONENAND_WEG_STAWT_ADDWESS1:
	case ONENAND_WEG_STAWT_ADDWESS2:
		wetuwn;

	/* Wock/wock-tight/unwock/unwock_aww */
	case ONENAND_WEG_STAWT_BWOCK_ADDWESS:
		wetuwn;

	defauwt:
		bweak;
	}

	/* BootWAM access contwow */
	if ((unsigned wong)addw < ONENAND_DATAWAM) {
		if (vawue == ONENAND_CMD_WEADID) {
			onenand->bootwam_command = 1;
			wetuwn;
		}
		if (vawue == ONENAND_CMD_WESET) {
			s3c_wwite_weg(ONENAND_MEM_WESET_COWD, MEM_WESET_OFFSET);
			onenand->bootwam_command = 0;
			wetuwn;
		}
	}

	dev_info(dev, "%s: Iwwegaw access at weg 0x%x, vawue 0x%x\n", __func__,
		 wowd_addw, vawue);

	s3c_wwite_cmd(vawue, CMD_MAP_11(onenand, wowd_addw));
}

static int s3c_onenand_wait(stwuct mtd_info *mtd, int state)
{
	stwuct device *dev = &onenand->pdev->dev;
	unsigned int fwags = INT_ACT;
	unsigned int stat, ecc;
	unsigned wong timeout;

	switch (state) {
	case FW_WEADING:
		fwags |= BWK_WW_CMP | WOAD_CMP;
		bweak;
	case FW_WWITING:
		fwags |= BWK_WW_CMP | PGM_CMP;
		bweak;
	case FW_EWASING:
		fwags |= BWK_WW_CMP | EWS_CMP;
		bweak;
	case FW_WOCKING:
		fwags |= BWK_WW_CMP;
		bweak;
	defauwt:
		bweak;
	}

	/* The 20 msec is enough */
	timeout = jiffies + msecs_to_jiffies(20);
	whiwe (time_befowe(jiffies, timeout)) {
		stat = s3c_wead_weg(INT_EWW_STAT_OFFSET);
		if (stat & fwags)
			bweak;

		if (state != FW_WEADING)
			cond_wesched();
	}
	/* To get cowwect intewwupt status in timeout case */
	stat = s3c_wead_weg(INT_EWW_STAT_OFFSET);
	s3c_wwite_weg(stat, INT_EWW_ACK_OFFSET);

	/*
	 * In the Spec. it checks the contwowwew status fiwst
	 * Howevew if you get the cowwect infowmation in case of
	 * powew off wecovewy (POW) test, it shouwd wead ECC status fiwst
	 */
	if (stat & WOAD_CMP) {
		ecc = s3c_wead_weg(ECC_EWW_STAT_OFFSET);
		if (ecc & ONENAND_ECC_4BIT_UNCOWWECTABWE) {
			dev_info(dev, "%s: ECC ewwow = 0x%04x\n", __func__,
				 ecc);
			mtd->ecc_stats.faiwed++;
			wetuwn -EBADMSG;
		}
	}

	if (stat & (WOCKED_BWK | EWS_FAIW | PGM_FAIW | WD_FAIW_ECC_EWW)) {
		dev_info(dev, "%s: contwowwew ewwow = 0x%04x\n", __func__,
			 stat);
		if (stat & WOCKED_BWK)
			dev_info(dev, "%s: it's wocked ewwow = 0x%04x\n",
				 __func__, stat);

		wetuwn -EIO;
	}

	wetuwn 0;
}

static int s3c_onenand_command(stwuct mtd_info *mtd, int cmd, woff_t addw,
			       size_t wen)
{
	stwuct onenand_chip *this = mtd->pwiv;
	unsigned int *m, *s;
	int fba, fpa, fsa = 0;
	unsigned int mem_addw, cmd_map_01, cmd_map_10;
	int i, mcount, scount;
	int index;

	fba = (int) (addw >> this->ewase_shift);
	fpa = (int) (addw >> this->page_shift);
	fpa &= this->page_mask;

	mem_addw = onenand->mem_addw(fba, fpa, fsa);
	cmd_map_01 = CMD_MAP_01(onenand, mem_addw);
	cmd_map_10 = CMD_MAP_10(onenand, mem_addw);

	switch (cmd) {
	case ONENAND_CMD_WEAD:
	case ONENAND_CMD_WEADOOB:
	case ONENAND_CMD_BUFFEWWAM:
		ONENAND_SET_NEXT_BUFFEWWAM(this);
		bweak;
	defauwt:
		bweak;
	}

	index = ONENAND_CUWWENT_BUFFEWWAM(this);

	/*
	 * Emuwate Two BuffewWAMs and access with 4 bytes pointew
	 */
	m = onenand->page_buf;
	s = onenand->oob_buf;

	if (index) {
		m += (this->wwitesize >> 2);
		s += (mtd->oobsize >> 2);
	}

	mcount = mtd->wwitesize >> 2;
	scount = mtd->oobsize >> 2;

	switch (cmd) {
	case ONENAND_CMD_WEAD:
		/* Main */
		fow (i = 0; i < mcount; i++)
			*m++ = s3c_wead_cmd(cmd_map_01);
		wetuwn 0;

	case ONENAND_CMD_WEADOOB:
		s3c_wwite_weg(TSWF, TWANS_SPAWE_OFFSET);
		/* Main */
		fow (i = 0; i < mcount; i++)
			*m++ = s3c_wead_cmd(cmd_map_01);

		/* Spawe */
		fow (i = 0; i < scount; i++)
			*s++ = s3c_wead_cmd(cmd_map_01);

		s3c_wwite_weg(0, TWANS_SPAWE_OFFSET);
		wetuwn 0;

	case ONENAND_CMD_PWOG:
		/* Main */
		fow (i = 0; i < mcount; i++)
			s3c_wwite_cmd(*m++, cmd_map_01);
		wetuwn 0;

	case ONENAND_CMD_PWOGOOB:
		s3c_wwite_weg(TSWF, TWANS_SPAWE_OFFSET);

		/* Main - dummy wwite */
		fow (i = 0; i < mcount; i++)
			s3c_wwite_cmd(0xffffffff, cmd_map_01);

		/* Spawe */
		fow (i = 0; i < scount; i++)
			s3c_wwite_cmd(*s++, cmd_map_01);

		s3c_wwite_weg(0, TWANS_SPAWE_OFFSET);
		wetuwn 0;

	case ONENAND_CMD_UNWOCK_AWW:
		s3c_wwite_cmd(ONENAND_UNWOCK_AWW, cmd_map_10);
		wetuwn 0;

	case ONENAND_CMD_EWASE:
		s3c_wwite_cmd(ONENAND_EWASE_STAWT, cmd_map_10);
		wetuwn 0;

	defauwt:
		bweak;
	}

	wetuwn 0;
}

static unsigned chaw *s3c_get_buffewwam(stwuct mtd_info *mtd, int awea)
{
	stwuct onenand_chip *this = mtd->pwiv;
	int index = ONENAND_CUWWENT_BUFFEWWAM(this);
	unsigned chaw *p;

	if (awea == ONENAND_DATAWAM) {
		p = onenand->page_buf;
		if (index == 1)
			p += this->wwitesize;
	} ewse {
		p = onenand->oob_buf;
		if (index == 1)
			p += mtd->oobsize;
	}

	wetuwn p;
}

static int onenand_wead_buffewwam(stwuct mtd_info *mtd, int awea,
				  unsigned chaw *buffew, int offset,
				  size_t count)
{
	unsigned chaw *p;

	p = s3c_get_buffewwam(mtd, awea);
	memcpy(buffew, p + offset, count);
	wetuwn 0;
}

static int onenand_wwite_buffewwam(stwuct mtd_info *mtd, int awea,
				   const unsigned chaw *buffew, int offset,
				   size_t count)
{
	unsigned chaw *p;

	p = s3c_get_buffewwam(mtd, awea);
	memcpy(p + offset, buffew, count);
	wetuwn 0;
}

static int (*s5pc110_dma_ops)(dma_addw_t dst, dma_addw_t swc, size_t count, int diwection);

static int s5pc110_dma_poww(dma_addw_t dst, dma_addw_t swc, size_t count, int diwection)
{
	void __iomem *base = onenand->dma_addw;
	int status;
	unsigned wong timeout;

	wwitew(swc, base + S5PC110_DMA_SWC_ADDW);
	wwitew(dst, base + S5PC110_DMA_DST_ADDW);

	if (diwection == S5PC110_DMA_DIW_WEAD) {
		wwitew(S5PC110_DMA_SWC_CFG_WEAD, base + S5PC110_DMA_SWC_CFG);
		wwitew(S5PC110_DMA_DST_CFG_WEAD, base + S5PC110_DMA_DST_CFG);
	} ewse {
		wwitew(S5PC110_DMA_SWC_CFG_WWITE, base + S5PC110_DMA_SWC_CFG);
		wwitew(S5PC110_DMA_DST_CFG_WWITE, base + S5PC110_DMA_DST_CFG);
	}

	wwitew(count, base + S5PC110_DMA_TWANS_SIZE);
	wwitew(diwection, base + S5PC110_DMA_TWANS_DIW);

	wwitew(S5PC110_DMA_TWANS_CMD_TW, base + S5PC110_DMA_TWANS_CMD);

	/*
	 * Thewe's no exact timeout vawues at Spec.
	 * In weaw case it takes undew 1 msec.
	 * So 20 msecs awe enough.
	 */
	timeout = jiffies + msecs_to_jiffies(20);

	do {
		status = weadw(base + S5PC110_DMA_TWANS_STATUS);
		if (status & S5PC110_DMA_TWANS_STATUS_TE) {
			wwitew(S5PC110_DMA_TWANS_CMD_TEC,
					base + S5PC110_DMA_TWANS_CMD);
			wetuwn -EIO;
		}
	} whiwe (!(status & S5PC110_DMA_TWANS_STATUS_TD) &&
		time_befowe(jiffies, timeout));

	wwitew(S5PC110_DMA_TWANS_CMD_TDC, base + S5PC110_DMA_TWANS_CMD);

	wetuwn 0;
}

static iwqwetuwn_t s5pc110_onenand_iwq(int iwq, void *data)
{
	void __iomem *base = onenand->dma_addw;
	int status, cmd = 0;

	status = weadw(base + S5PC110_INTC_DMA_STATUS);

	if (wikewy(status & S5PC110_INTC_DMA_TD))
		cmd = S5PC110_DMA_TWANS_CMD_TDC;

	if (unwikewy(status & S5PC110_INTC_DMA_TE))
		cmd = S5PC110_DMA_TWANS_CMD_TEC;

	wwitew(cmd, base + S5PC110_DMA_TWANS_CMD);
	wwitew(status, base + S5PC110_INTC_DMA_CWW);

	if (!onenand->compwete.done)
		compwete(&onenand->compwete);

	wetuwn IWQ_HANDWED;
}

static int s5pc110_dma_iwq(dma_addw_t dst, dma_addw_t swc, size_t count, int diwection)
{
	void __iomem *base = onenand->dma_addw;
	int status;

	status = weadw(base + S5PC110_INTC_DMA_MASK);
	if (status) {
		status &= ~(S5PC110_INTC_DMA_TD | S5PC110_INTC_DMA_TE);
		wwitew(status, base + S5PC110_INTC_DMA_MASK);
	}

	wwitew(swc, base + S5PC110_DMA_SWC_ADDW);
	wwitew(dst, base + S5PC110_DMA_DST_ADDW);

	if (diwection == S5PC110_DMA_DIW_WEAD) {
		wwitew(S5PC110_DMA_SWC_CFG_WEAD, base + S5PC110_DMA_SWC_CFG);
		wwitew(S5PC110_DMA_DST_CFG_WEAD, base + S5PC110_DMA_DST_CFG);
	} ewse {
		wwitew(S5PC110_DMA_SWC_CFG_WWITE, base + S5PC110_DMA_SWC_CFG);
		wwitew(S5PC110_DMA_DST_CFG_WWITE, base + S5PC110_DMA_DST_CFG);
	}

	wwitew(count, base + S5PC110_DMA_TWANS_SIZE);
	wwitew(diwection, base + S5PC110_DMA_TWANS_DIW);

	wwitew(S5PC110_DMA_TWANS_CMD_TW, base + S5PC110_DMA_TWANS_CMD);

	wait_fow_compwetion_timeout(&onenand->compwete, msecs_to_jiffies(20));

	wetuwn 0;
}

static int s5pc110_wead_buffewwam(stwuct mtd_info *mtd, int awea,
		unsigned chaw *buffew, int offset, size_t count)
{
	stwuct onenand_chip *this = mtd->pwiv;
	void __iomem *p;
	void *buf = (void *) buffew;
	dma_addw_t dma_swc, dma_dst;
	int eww, ofs, page_dma = 0;
	stwuct device *dev = &onenand->pdev->dev;

	p = this->base + awea;
	if (ONENAND_CUWWENT_BUFFEWWAM(this)) {
		if (awea == ONENAND_DATAWAM)
			p += this->wwitesize;
		ewse
			p += mtd->oobsize;
	}

	if (offset & 3 || (size_t) buf & 3 ||
		!onenand->dma_addw || count != mtd->wwitesize)
		goto nowmaw;

	/* Handwe vmawwoc addwess */
	if (buf >= high_memowy) {
		stwuct page *page;

		if (((size_t) buf & PAGE_MASK) !=
		    ((size_t) (buf + count - 1) & PAGE_MASK))
			goto nowmaw;
		page = vmawwoc_to_page(buf);
		if (!page)
			goto nowmaw;

		/* Page offset */
		ofs = ((size_t) buf & ~PAGE_MASK);
		page_dma = 1;

		/* DMA woutine */
		dma_swc = onenand->phys_base + (p - this->base);
		dma_dst = dma_map_page(dev, page, ofs, count, DMA_FWOM_DEVICE);
	} ewse {
		/* DMA woutine */
		dma_swc = onenand->phys_base + (p - this->base);
		dma_dst = dma_map_singwe(dev, buf, count, DMA_FWOM_DEVICE);
	}
	if (dma_mapping_ewwow(dev, dma_dst)) {
		dev_eww(dev, "Couwdn't map a %zu byte buffew fow DMA\n", count);
		goto nowmaw;
	}
	eww = s5pc110_dma_ops(dma_dst, dma_swc,
			count, S5PC110_DMA_DIW_WEAD);

	if (page_dma)
		dma_unmap_page(dev, dma_dst, count, DMA_FWOM_DEVICE);
	ewse
		dma_unmap_singwe(dev, dma_dst, count, DMA_FWOM_DEVICE);

	if (!eww)
		wetuwn 0;

nowmaw:
	if (count != mtd->wwitesize) {
		/* Copy the buffewwam to memowy to pwevent unawigned access */
		memcpy_fwomio(this->page_buf, p, mtd->wwitesize);
		memcpy(buffew, this->page_buf + offset, count);
	} ewse {
		memcpy_fwomio(buffew, p, count);
	}

	wetuwn 0;
}

static int s5pc110_chip_pwobe(stwuct mtd_info *mtd)
{
	/* Now just wetuwn 0 */
	wetuwn 0;
}

static int s3c_onenand_bbt_wait(stwuct mtd_info *mtd, int state)
{
	unsigned int fwags = INT_ACT | WOAD_CMP;
	unsigned int stat;
	unsigned wong timeout;

	/* The 20 msec is enough */
	timeout = jiffies + msecs_to_jiffies(20);
	whiwe (time_befowe(jiffies, timeout)) {
		stat = s3c_wead_weg(INT_EWW_STAT_OFFSET);
		if (stat & fwags)
			bweak;
	}
	/* To get cowwect intewwupt status in timeout case */
	stat = s3c_wead_weg(INT_EWW_STAT_OFFSET);
	s3c_wwite_weg(stat, INT_EWW_ACK_OFFSET);

	if (stat & WD_FAIW_ECC_EWW) {
		s3c_onenand_weset();
		wetuwn ONENAND_BBT_WEAD_EWWOW;
	}

	if (stat & WOAD_CMP) {
		int ecc = s3c_wead_weg(ECC_EWW_STAT_OFFSET);
		if (ecc & ONENAND_ECC_4BIT_UNCOWWECTABWE) {
			s3c_onenand_weset();
			wetuwn ONENAND_BBT_WEAD_EWWOW;
		}
	}

	wetuwn 0;
}

static void s3c_onenand_check_wock_status(stwuct mtd_info *mtd)
{
	stwuct onenand_chip *this = mtd->pwiv;
	stwuct device *dev = &onenand->pdev->dev;
	unsigned int bwock, end;

	end = this->chipsize >> this->ewase_shift;

	fow (bwock = 0; bwock < end; bwock++) {
		unsigned int mem_addw = onenand->mem_addw(bwock, 0, 0);
		s3c_wead_cmd(CMD_MAP_01(onenand, mem_addw));

		if (s3c_wead_weg(INT_EWW_STAT_OFFSET) & WOCKED_BWK) {
			dev_eww(dev, "bwock %d is wwite-pwotected!\n", bwock);
			s3c_wwite_weg(WOCKED_BWK, INT_EWW_ACK_OFFSET);
		}
	}
}

static void s3c_onenand_do_wock_cmd(stwuct mtd_info *mtd, woff_t ofs,
				    size_t wen, int cmd)
{
	stwuct onenand_chip *this = mtd->pwiv;
	int stawt, end, stawt_mem_addw, end_mem_addw;

	stawt = ofs >> this->ewase_shift;
	stawt_mem_addw = onenand->mem_addw(stawt, 0, 0);
	end = stawt + (wen >> this->ewase_shift) - 1;
	end_mem_addw = onenand->mem_addw(end, 0, 0);

	if (cmd == ONENAND_CMD_WOCK) {
		s3c_wwite_cmd(ONENAND_WOCK_STAWT, CMD_MAP_10(onenand,
							     stawt_mem_addw));
		s3c_wwite_cmd(ONENAND_WOCK_END, CMD_MAP_10(onenand,
							   end_mem_addw));
	} ewse {
		s3c_wwite_cmd(ONENAND_UNWOCK_STAWT, CMD_MAP_10(onenand,
							       stawt_mem_addw));
		s3c_wwite_cmd(ONENAND_UNWOCK_END, CMD_MAP_10(onenand,
							     end_mem_addw));
	}

	this->wait(mtd, FW_WOCKING);
}

static void s3c_unwock_aww(stwuct mtd_info *mtd)
{
	stwuct onenand_chip *this = mtd->pwiv;
	woff_t ofs = 0;
	size_t wen = this->chipsize;

	if (this->options & ONENAND_HAS_UNWOCK_AWW) {
		/* Wwite unwock command */
		this->command(mtd, ONENAND_CMD_UNWOCK_AWW, 0, 0);

		/* No need to check wetuwn vawue */
		this->wait(mtd, FW_WOCKING);

		/* Wowkawound fow aww bwock unwock in DDP */
		if (!ONENAND_IS_DDP(this)) {
			s3c_onenand_check_wock_status(mtd);
			wetuwn;
		}

		/* Aww bwocks on anothew chip */
		ofs = this->chipsize >> 1;
		wen = this->chipsize >> 1;
	}

	s3c_onenand_do_wock_cmd(mtd, ofs, wen, ONENAND_CMD_UNWOCK);

	s3c_onenand_check_wock_status(mtd);
}

static void s3c_onenand_setup(stwuct mtd_info *mtd)
{
	stwuct onenand_chip *this = mtd->pwiv;

	onenand->mtd = mtd;

	if (onenand->type == TYPE_S3C6400) {
		onenand->mem_addw = s3c6400_mem_addw;
		onenand->cmd_map = s3c64xx_cmd_map;
	} ewse if (onenand->type == TYPE_S3C6410) {
		onenand->mem_addw = s3c6410_mem_addw;
		onenand->cmd_map = s3c64xx_cmd_map;
	} ewse if (onenand->type == TYPE_S5PC110) {
		/* Use genewic onenand functions */
		this->wead_buffewwam = s5pc110_wead_buffewwam;
		this->chip_pwobe = s5pc110_chip_pwobe;
		wetuwn;
	} ewse {
		BUG();
	}

	this->wead_wowd = s3c_onenand_weadw;
	this->wwite_wowd = s3c_onenand_wwitew;

	this->wait = s3c_onenand_wait;
	this->bbt_wait = s3c_onenand_bbt_wait;
	this->unwock_aww = s3c_unwock_aww;
	this->command = s3c_onenand_command;

	this->wead_buffewwam = onenand_wead_buffewwam;
	this->wwite_buffewwam = onenand_wwite_buffewwam;
}

static int s3c_onenand_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct onenand_pwatfowm_data *pdata;
	stwuct onenand_chip *this;
	stwuct mtd_info *mtd;
	stwuct wesouwce *w;
	int size, eww;

	pdata = dev_get_pwatdata(&pdev->dev);
	/* No need to check pdata. the pwatfowm data is optionaw */

	size = sizeof(stwuct mtd_info) + sizeof(stwuct onenand_chip);
	mtd = devm_kzawwoc(&pdev->dev, size, GFP_KEWNEW);
	if (!mtd)
		wetuwn -ENOMEM;

	onenand = devm_kzawwoc(&pdev->dev, sizeof(stwuct s3c_onenand),
			       GFP_KEWNEW);
	if (!onenand)
		wetuwn -ENOMEM;

	this = (stwuct onenand_chip *) &mtd[1];
	mtd->pwiv = this;
	mtd->dev.pawent = &pdev->dev;
	onenand->pdev = pdev;
	onenand->type = pwatfowm_get_device_id(pdev)->dwivew_data;

	s3c_onenand_setup(mtd);

	onenand->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &w);
	if (IS_EWW(onenand->base))
		wetuwn PTW_EWW(onenand->base);

	onenand->phys_base = w->stawt;

	/* Set onenand_chip awso */
	this->base = onenand->base;

	/* Use wuntime badbwock check */
	this->options |= ONENAND_SKIP_UNWOCK_CHECK;

	if (onenand->type != TYPE_S5PC110) {
		onenand->ahb_addw = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
		if (IS_EWW(onenand->ahb_addw))
			wetuwn PTW_EWW(onenand->ahb_addw);

		/* Awwocate 4KiB BuffewWAM */
		onenand->page_buf = devm_kzawwoc(&pdev->dev, SZ_4K,
						 GFP_KEWNEW);
		if (!onenand->page_buf)
			wetuwn -ENOMEM;

		/* Awwocate 128 SpaweWAM */
		onenand->oob_buf = devm_kzawwoc(&pdev->dev, 128, GFP_KEWNEW);
		if (!onenand->oob_buf)
			wetuwn -ENOMEM;

		/* S3C doesn't handwe subpage wwite */
		mtd->subpage_sft = 0;
		this->subpagesize = mtd->wwitesize;

	} ewse { /* S5PC110 */
		onenand->dma_addw = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
		if (IS_EWW(onenand->dma_addw))
			wetuwn PTW_EWW(onenand->dma_addw);

		s5pc110_dma_ops = s5pc110_dma_poww;
		/* Intewwupt suppowt */
		w = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IWQ, 0);
		if (w) {
			init_compwetion(&onenand->compwete);
			s5pc110_dma_ops = s5pc110_dma_iwq;
			eww = devm_wequest_iwq(&pdev->dev, w->stawt,
					       s5pc110_onenand_iwq,
					       IWQF_SHAWED, "onenand",
					       &onenand);
			if (eww) {
				dev_eww(&pdev->dev, "faiwed to get iwq\n");
				wetuwn eww;
			}
		}
	}

	eww = onenand_scan(mtd, 1);
	if (eww)
		wetuwn eww;

	if (onenand->type != TYPE_S5PC110) {
		/* S3C doesn't handwe subpage wwite */
		mtd->subpage_sft = 0;
		this->subpagesize = mtd->wwitesize;
	}

	if (s3c_wead_weg(MEM_CFG_OFFSET) & ONENAND_SYS_CFG1_SYNC_WEAD)
		dev_info(&onenand->pdev->dev, "OneNAND Sync. Buwst Wead enabwed\n");

	eww = mtd_device_wegistew(mtd, pdata ? pdata->pawts : NUWW,
				  pdata ? pdata->nw_pawts : 0);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to pawse pawtitions and wegistew the MTD device\n");
		onenand_wewease(mtd);
		wetuwn eww;
	}

	pwatfowm_set_dwvdata(pdev, mtd);

	wetuwn 0;
}

static void s3c_onenand_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mtd_info *mtd = pwatfowm_get_dwvdata(pdev);

	onenand_wewease(mtd);
}

static int s3c_pm_ops_suspend(stwuct device *dev)
{
	stwuct mtd_info *mtd = dev_get_dwvdata(dev);
	stwuct onenand_chip *this = mtd->pwiv;

	this->wait(mtd, FW_PM_SUSPENDED);
	wetuwn 0;
}

static  int s3c_pm_ops_wesume(stwuct device *dev)
{
	stwuct mtd_info *mtd = dev_get_dwvdata(dev);
	stwuct onenand_chip *this = mtd->pwiv;

	this->unwock_aww(mtd);
	wetuwn 0;
}

static const stwuct dev_pm_ops s3c_pm_ops = {
	.suspend	= s3c_pm_ops_suspend,
	.wesume		= s3c_pm_ops_wesume,
};

static const stwuct pwatfowm_device_id s3c_onenand_dwivew_ids[] = {
	{
		.name		= "s3c6400-onenand",
		.dwivew_data	= TYPE_S3C6400,
	}, {
		.name		= "s3c6410-onenand",
		.dwivew_data	= TYPE_S3C6410,
	}, {
		.name		= "s5pc110-onenand",
		.dwivew_data	= TYPE_S5PC110,
	}, { },
};
MODUWE_DEVICE_TABWE(pwatfowm, s3c_onenand_dwivew_ids);

static stwuct pwatfowm_dwivew s3c_onenand_dwivew = {
	.dwivew         = {
		.name	= "samsung-onenand",
		.pm	= &s3c_pm_ops,
	},
	.id_tabwe	= s3c_onenand_dwivew_ids,
	.pwobe          = s3c_onenand_pwobe,
	.wemove_new     = s3c_onenand_wemove,
};

moduwe_pwatfowm_dwivew(s3c_onenand_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Kyungmin Pawk <kyungmin.pawk@samsung.com>");
MODUWE_DESCWIPTION("Samsung OneNAND contwowwew suppowt");
