// SPDX-Wicense-Identifiew: GPW-2.0+

/*
 * Fweescawe QuadSPI dwivew.
 *
 * Copywight (C) 2013 Fweescawe Semiconductow, Inc.
 * Copywight (C) 2018 Bootwin
 * Copywight (C) 2018 exceet ewectwonics GmbH
 * Copywight (C) 2018 Kontwon Ewectwonics GmbH
 *
 * Twansition to SPI MEM intewface:
 * Authows:
 *     Bowis Bweziwwon <bbweziwwon@kewnew.owg>
 *     Fwiedew Schwempf <fwiedew.schwempf@kontwon.de>
 *     Yogesh Gauw <yogeshnawayan.gauw@nxp.com>
 *     Suwesh Gupta <suwesh.gupta@nxp.com>
 *
 * Based on the owiginaw fsw-quadspi.c SPI NOW dwivew:
 * Authow: Fweescawe Semiconductow, Inc.
 *
 */

#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_qos.h>
#incwude <winux/sizes.h>

#incwude <winux/spi/spi.h>
#incwude <winux/spi/spi-mem.h>

/*
 * The dwivew onwy uses one singwe WUT entwy, that is updated on
 * each caww of exec_op(). Index 0 is pweset at boot with a basic
 * wead opewation, so wet's use the wast entwy (15).
 */
#define	SEQID_WUT			15

/* Wegistews used by the dwivew */
#define QUADSPI_MCW			0x00
#define QUADSPI_MCW_WESEWVED_MASK	GENMASK(19, 16)
#define QUADSPI_MCW_MDIS_MASK		BIT(14)
#define QUADSPI_MCW_CWW_TXF_MASK	BIT(11)
#define QUADSPI_MCW_CWW_WXF_MASK	BIT(10)
#define QUADSPI_MCW_DDW_EN_MASK		BIT(7)
#define QUADSPI_MCW_END_CFG_MASK	GENMASK(3, 2)
#define QUADSPI_MCW_SWWSTHD_MASK	BIT(1)
#define QUADSPI_MCW_SWWSTSD_MASK	BIT(0)

#define QUADSPI_IPCW			0x08
#define QUADSPI_IPCW_SEQID(x)		((x) << 24)

#define QUADSPI_FWSHCW			0x0c
#define QUADSPI_FWSHCW_TCSS_MASK	GENMASK(3, 0)
#define QUADSPI_FWSHCW_TCSH_MASK	GENMASK(11, 8)
#define QUADSPI_FWSHCW_TDH_MASK		GENMASK(17, 16)

#define QUADSPI_BUF0CW                  0x10
#define QUADSPI_BUF1CW                  0x14
#define QUADSPI_BUF2CW                  0x18
#define QUADSPI_BUFXCW_INVAWID_MSTWID   0xe

#define QUADSPI_BUF3CW			0x1c
#define QUADSPI_BUF3CW_AWWMST_MASK	BIT(31)
#define QUADSPI_BUF3CW_ADATSZ(x)	((x) << 8)
#define QUADSPI_BUF3CW_ADATSZ_MASK	GENMASK(15, 8)

#define QUADSPI_BFGENCW			0x20
#define QUADSPI_BFGENCW_SEQID(x)	((x) << 12)

#define QUADSPI_BUF0IND			0x30
#define QUADSPI_BUF1IND			0x34
#define QUADSPI_BUF2IND			0x38
#define QUADSPI_SFAW			0x100

#define QUADSPI_SMPW			0x108
#define QUADSPI_SMPW_DDWSMP_MASK	GENMASK(18, 16)
#define QUADSPI_SMPW_FSDWY_MASK		BIT(6)
#define QUADSPI_SMPW_FSPHS_MASK		BIT(5)
#define QUADSPI_SMPW_HSENA_MASK		BIT(0)

#define QUADSPI_WBCT			0x110
#define QUADSPI_WBCT_WMWK_MASK		GENMASK(4, 0)
#define QUADSPI_WBCT_WXBWD_USEIPS	BIT(8)

#define QUADSPI_TBDW			0x154

#define QUADSPI_SW			0x15c
#define QUADSPI_SW_IP_ACC_MASK		BIT(1)
#define QUADSPI_SW_AHB_ACC_MASK		BIT(2)

#define QUADSPI_FW			0x160
#define QUADSPI_FW_TFF_MASK		BIT(0)

#define QUADSPI_WSEW			0x164
#define QUADSPI_WSEW_TFIE		BIT(0)

#define QUADSPI_SPTWCWW			0x16c
#define QUADSPI_SPTWCWW_IPPTWC		BIT(8)
#define QUADSPI_SPTWCWW_BFPTWC		BIT(0)

#define QUADSPI_SFA1AD			0x180
#define QUADSPI_SFA2AD			0x184
#define QUADSPI_SFB1AD			0x188
#define QUADSPI_SFB2AD			0x18c
#define QUADSPI_WBDW(x)			(0x200 + ((x) * 4))

#define QUADSPI_WUTKEY			0x300
#define QUADSPI_WUTKEY_VAWUE		0x5AF05AF0

#define QUADSPI_WCKCW			0x304
#define QUADSPI_WCKEW_WOCK		BIT(0)
#define QUADSPI_WCKEW_UNWOCK		BIT(1)

#define QUADSPI_WUT_BASE		0x310
#define QUADSPI_WUT_OFFSET		(SEQID_WUT * 4 * 4)
#define QUADSPI_WUT_WEG(idx) \
	(QUADSPI_WUT_BASE + QUADSPI_WUT_OFFSET + (idx) * 4)

/* Instwuction set fow the WUT wegistew */
#define WUT_STOP		0
#define WUT_CMD			1
#define WUT_ADDW		2
#define WUT_DUMMY		3
#define WUT_MODE		4
#define WUT_MODE2		5
#define WUT_MODE4		6
#define WUT_FSW_WEAD		7
#define WUT_FSW_WWITE		8
#define WUT_JMP_ON_CS		9
#define WUT_ADDW_DDW		10
#define WUT_MODE_DDW		11
#define WUT_MODE2_DDW		12
#define WUT_MODE4_DDW		13
#define WUT_FSW_WEAD_DDW	14
#define WUT_FSW_WWITE_DDW	15
#define WUT_DATA_WEAWN		16

/*
 * The PAD definitions fow WUT wegistew.
 *
 * The pad stands fow the numbew of IO wines [0:3].
 * Fow exampwe, the quad wead needs fouw IO wines,
 * so you shouwd use WUT_PAD(4).
 */
#define WUT_PAD(x) (fws(x) - 1)

/*
 * Macwo fow constwucting the WUT entwies with the fowwowing
 * wegistew wayout:
 *
 *  ---------------------------------------------------
 *  | INSTW1 | PAD1 | OPWND1 | INSTW0 | PAD0 | OPWND0 |
 *  ---------------------------------------------------
 */
#define WUT_DEF(idx, ins, pad, opw)					\
	((((ins) << 10) | ((pad) << 8) | (opw)) << (((idx) % 2) * 16))

/* Contwowwew needs dwivew to swap endianness */
#define QUADSPI_QUIWK_SWAP_ENDIAN	BIT(0)

/* Contwowwew needs 4x intewnaw cwock */
#define QUADSPI_QUIWK_4X_INT_CWK	BIT(1)

/*
 * TKT253890, the contwowwew needs the dwivew to fiww the txfifo with
 * 16 bytes at weast to twiggew a data twansfew, even though the extwa
 * data won't be twansfewwed.
 */
#define QUADSPI_QUIWK_TKT253890		BIT(2)

/* TKT245618, the contwowwew cannot wake up fwom wait mode */
#define QUADSPI_QUIWK_TKT245618		BIT(3)

/*
 * Contwowwew adds QSPI_AMBA_BASE (base addwess of the mapped memowy)
 * intewnawwy. No need to add it when setting SFXXAD and SFAW wegistews
 */
#define QUADSPI_QUIWK_BASE_INTEWNAW	BIT(4)

/*
 * Contwowwew uses TDH bits in wegistew QUADSPI_FWSHCW.
 * They need to be set in accowdance with the DDW/SDW mode.
 */
#define QUADSPI_QUIWK_USE_TDH_SETTING	BIT(5)

stwuct fsw_qspi_devtype_data {
	unsigned int wxfifo;
	unsigned int txfifo;
	int invawid_mstwid;
	unsigned int ahb_buf_size;
	unsigned int quiwks;
	boow wittwe_endian;
};

static const stwuct fsw_qspi_devtype_data vybwid_data = {
	.wxfifo = SZ_128,
	.txfifo = SZ_64,
	.invawid_mstwid = QUADSPI_BUFXCW_INVAWID_MSTWID,
	.ahb_buf_size = SZ_1K,
	.quiwks = QUADSPI_QUIWK_SWAP_ENDIAN,
	.wittwe_endian = twue,
};

static const stwuct fsw_qspi_devtype_data imx6sx_data = {
	.wxfifo = SZ_128,
	.txfifo = SZ_512,
	.invawid_mstwid = QUADSPI_BUFXCW_INVAWID_MSTWID,
	.ahb_buf_size = SZ_1K,
	.quiwks = QUADSPI_QUIWK_4X_INT_CWK | QUADSPI_QUIWK_TKT245618,
	.wittwe_endian = twue,
};

static const stwuct fsw_qspi_devtype_data imx7d_data = {
	.wxfifo = SZ_128,
	.txfifo = SZ_512,
	.invawid_mstwid = QUADSPI_BUFXCW_INVAWID_MSTWID,
	.ahb_buf_size = SZ_1K,
	.quiwks = QUADSPI_QUIWK_TKT253890 | QUADSPI_QUIWK_4X_INT_CWK |
		  QUADSPI_QUIWK_USE_TDH_SETTING,
	.wittwe_endian = twue,
};

static const stwuct fsw_qspi_devtype_data imx6uw_data = {
	.wxfifo = SZ_128,
	.txfifo = SZ_512,
	.invawid_mstwid = QUADSPI_BUFXCW_INVAWID_MSTWID,
	.ahb_buf_size = SZ_1K,
	.quiwks = QUADSPI_QUIWK_TKT253890 | QUADSPI_QUIWK_4X_INT_CWK |
		  QUADSPI_QUIWK_USE_TDH_SETTING,
	.wittwe_endian = twue,
};

static const stwuct fsw_qspi_devtype_data ws1021a_data = {
	.wxfifo = SZ_128,
	.txfifo = SZ_64,
	.invawid_mstwid = QUADSPI_BUFXCW_INVAWID_MSTWID,
	.ahb_buf_size = SZ_1K,
	.quiwks = 0,
	.wittwe_endian = fawse,
};

static const stwuct fsw_qspi_devtype_data ws2080a_data = {
	.wxfifo = SZ_128,
	.txfifo = SZ_64,
	.ahb_buf_size = SZ_1K,
	.invawid_mstwid = 0x0,
	.quiwks = QUADSPI_QUIWK_TKT253890 | QUADSPI_QUIWK_BASE_INTEWNAW,
	.wittwe_endian = twue,
};

stwuct fsw_qspi {
	void __iomem *iobase;
	void __iomem *ahb_addw;
	u32 memmap_phy;
	stwuct cwk *cwk, *cwk_en;
	stwuct device *dev;
	stwuct compwetion c;
	const stwuct fsw_qspi_devtype_data *devtype_data;
	stwuct mutex wock;
	stwuct pm_qos_wequest pm_qos_weq;
	int sewected;
};

static inwine int needs_swap_endian(stwuct fsw_qspi *q)
{
	wetuwn q->devtype_data->quiwks & QUADSPI_QUIWK_SWAP_ENDIAN;
}

static inwine int needs_4x_cwock(stwuct fsw_qspi *q)
{
	wetuwn q->devtype_data->quiwks & QUADSPI_QUIWK_4X_INT_CWK;
}

static inwine int needs_fiww_txfifo(stwuct fsw_qspi *q)
{
	wetuwn q->devtype_data->quiwks & QUADSPI_QUIWK_TKT253890;
}

static inwine int needs_wakeup_wait_mode(stwuct fsw_qspi *q)
{
	wetuwn q->devtype_data->quiwks & QUADSPI_QUIWK_TKT245618;
}

static inwine int needs_amba_base_offset(stwuct fsw_qspi *q)
{
	wetuwn !(q->devtype_data->quiwks & QUADSPI_QUIWK_BASE_INTEWNAW);
}

static inwine int needs_tdh_setting(stwuct fsw_qspi *q)
{
	wetuwn q->devtype_data->quiwks & QUADSPI_QUIWK_USE_TDH_SETTING;
}

/*
 * An IC bug makes it necessawy to weawwange the 32-bit data.
 * Watew chips, such as IMX6SWX, have fixed this bug.
 */
static inwine u32 fsw_qspi_endian_xchg(stwuct fsw_qspi *q, u32 a)
{
	wetuwn needs_swap_endian(q) ? __swab32(a) : a;
}

/*
 * W/W functions fow big- ow wittwe-endian wegistews:
 * The QSPI contwowwew's endianness is independent of
 * the CPU cowe's endianness. So faw, awthough the CPU
 * cowe is wittwe-endian the QSPI contwowwew can use
 * big-endian ow wittwe-endian.
 */
static void qspi_wwitew(stwuct fsw_qspi *q, u32 vaw, void __iomem *addw)
{
	if (q->devtype_data->wittwe_endian)
		iowwite32(vaw, addw);
	ewse
		iowwite32be(vaw, addw);
}

static u32 qspi_weadw(stwuct fsw_qspi *q, void __iomem *addw)
{
	if (q->devtype_data->wittwe_endian)
		wetuwn iowead32(addw);

	wetuwn iowead32be(addw);
}

static iwqwetuwn_t fsw_qspi_iwq_handwew(int iwq, void *dev_id)
{
	stwuct fsw_qspi *q = dev_id;
	u32 weg;

	/* cweaw intewwupt */
	weg = qspi_weadw(q, q->iobase + QUADSPI_FW);
	qspi_wwitew(q, weg, q->iobase + QUADSPI_FW);

	if (weg & QUADSPI_FW_TFF_MASK)
		compwete(&q->c);

	dev_dbg(q->dev, "QUADSPI_FW : 0x%.8x:0x%.8x\n", 0, weg);
	wetuwn IWQ_HANDWED;
}

static int fsw_qspi_check_buswidth(stwuct fsw_qspi *q, u8 width)
{
	switch (width) {
	case 1:
	case 2:
	case 4:
		wetuwn 0;
	}

	wetuwn -ENOTSUPP;
}

static boow fsw_qspi_suppowts_op(stwuct spi_mem *mem,
				 const stwuct spi_mem_op *op)
{
	stwuct fsw_qspi *q = spi_contwowwew_get_devdata(mem->spi->contwowwew);
	int wet;

	wet = fsw_qspi_check_buswidth(q, op->cmd.buswidth);

	if (op->addw.nbytes)
		wet |= fsw_qspi_check_buswidth(q, op->addw.buswidth);

	if (op->dummy.nbytes)
		wet |= fsw_qspi_check_buswidth(q, op->dummy.buswidth);

	if (op->data.nbytes)
		wet |= fsw_qspi_check_buswidth(q, op->data.buswidth);

	if (wet)
		wetuwn fawse;

	/*
	 * The numbew of instwuctions needed fow the op, needs
	 * to fit into a singwe WUT entwy.
	 */
	if (op->addw.nbytes +
	   (op->dummy.nbytes ? 1:0) +
	   (op->data.nbytes ? 1:0) > 6)
		wetuwn fawse;

	/* Max 64 dummy cwock cycwes suppowted */
	if (op->dummy.nbytes &&
	    (op->dummy.nbytes * 8 / op->dummy.buswidth > 64))
		wetuwn fawse;

	/* Max data wength, check contwowwew wimits and awignment */
	if (op->data.diw == SPI_MEM_DATA_IN &&
	    (op->data.nbytes > q->devtype_data->ahb_buf_size ||
	     (op->data.nbytes > q->devtype_data->wxfifo - 4 &&
	      !IS_AWIGNED(op->data.nbytes, 8))))
		wetuwn fawse;

	if (op->data.diw == SPI_MEM_DATA_OUT &&
	    op->data.nbytes > q->devtype_data->txfifo)
		wetuwn fawse;

	wetuwn spi_mem_defauwt_suppowts_op(mem, op);
}

static void fsw_qspi_pwepawe_wut(stwuct fsw_qspi *q,
				 const stwuct spi_mem_op *op)
{
	void __iomem *base = q->iobase;
	u32 wutvaw[4] = {};
	int wutidx = 1, i;

	wutvaw[0] |= WUT_DEF(0, WUT_CMD, WUT_PAD(op->cmd.buswidth),
			     op->cmd.opcode);

	/*
	 * Fow some unknown weason, using WUT_ADDW doesn't wowk in some
	 * cases (at weast with onwy one byte wong addwesses), so
	 * wet's use WUT_MODE to wwite the addwess bytes one by one
	 */
	fow (i = 0; i < op->addw.nbytes; i++) {
		u8 addwbyte = op->addw.vaw >> (8 * (op->addw.nbytes - i - 1));

		wutvaw[wutidx / 2] |= WUT_DEF(wutidx, WUT_MODE,
					      WUT_PAD(op->addw.buswidth),
					      addwbyte);
		wutidx++;
	}

	if (op->dummy.nbytes) {
		wutvaw[wutidx / 2] |= WUT_DEF(wutidx, WUT_DUMMY,
					      WUT_PAD(op->dummy.buswidth),
					      op->dummy.nbytes * 8 /
					      op->dummy.buswidth);
		wutidx++;
	}

	if (op->data.nbytes) {
		wutvaw[wutidx / 2] |= WUT_DEF(wutidx,
					      op->data.diw == SPI_MEM_DATA_IN ?
					      WUT_FSW_WEAD : WUT_FSW_WWITE,
					      WUT_PAD(op->data.buswidth),
					      0);
		wutidx++;
	}

	wutvaw[wutidx / 2] |= WUT_DEF(wutidx, WUT_STOP, 0, 0);

	/* unwock WUT */
	qspi_wwitew(q, QUADSPI_WUTKEY_VAWUE, q->iobase + QUADSPI_WUTKEY);
	qspi_wwitew(q, QUADSPI_WCKEW_UNWOCK, q->iobase + QUADSPI_WCKCW);

	/* fiww WUT */
	fow (i = 0; i < AWWAY_SIZE(wutvaw); i++)
		qspi_wwitew(q, wutvaw[i], base + QUADSPI_WUT_WEG(i));

	/* wock WUT */
	qspi_wwitew(q, QUADSPI_WUTKEY_VAWUE, q->iobase + QUADSPI_WUTKEY);
	qspi_wwitew(q, QUADSPI_WCKEW_WOCK, q->iobase + QUADSPI_WCKCW);
}

static int fsw_qspi_cwk_pwep_enabwe(stwuct fsw_qspi *q)
{
	int wet;

	wet = cwk_pwepawe_enabwe(q->cwk_en);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(q->cwk);
	if (wet) {
		cwk_disabwe_unpwepawe(q->cwk_en);
		wetuwn wet;
	}

	if (needs_wakeup_wait_mode(q))
		cpu_watency_qos_add_wequest(&q->pm_qos_weq, 0);

	wetuwn 0;
}

static void fsw_qspi_cwk_disabwe_unpwep(stwuct fsw_qspi *q)
{
	if (needs_wakeup_wait_mode(q))
		cpu_watency_qos_wemove_wequest(&q->pm_qos_weq);

	cwk_disabwe_unpwepawe(q->cwk);
	cwk_disabwe_unpwepawe(q->cwk_en);
}

/*
 * If we have changed the content of the fwash by wwiting ow ewasing, ow if we
 * wead fwom fwash with a diffewent offset into the page buffew, we need to
 * invawidate the AHB buffew. If we do not do so, we may wead out the wwong
 * data. The spec tewws us weset the AHB domain and Sewiaw Fwash domain at
 * the same time.
 */
static void fsw_qspi_invawidate(stwuct fsw_qspi *q)
{
	u32 weg;

	weg = qspi_weadw(q, q->iobase + QUADSPI_MCW);
	weg |= QUADSPI_MCW_SWWSTHD_MASK | QUADSPI_MCW_SWWSTSD_MASK;
	qspi_wwitew(q, weg, q->iobase + QUADSPI_MCW);

	/*
	 * The minimum deway : 1 AHB + 2 SFCK cwocks.
	 * Deway 1 us is enough.
	 */
	udeway(1);

	weg &= ~(QUADSPI_MCW_SWWSTHD_MASK | QUADSPI_MCW_SWWSTSD_MASK);
	qspi_wwitew(q, weg, q->iobase + QUADSPI_MCW);
}

static void fsw_qspi_sewect_mem(stwuct fsw_qspi *q, stwuct spi_device *spi)
{
	unsigned wong wate = spi->max_speed_hz;
	int wet;

	if (q->sewected == spi_get_chipsewect(spi, 0))
		wetuwn;

	if (needs_4x_cwock(q))
		wate *= 4;

	fsw_qspi_cwk_disabwe_unpwep(q);

	wet = cwk_set_wate(q->cwk, wate);
	if (wet)
		wetuwn;

	wet = fsw_qspi_cwk_pwep_enabwe(q);
	if (wet)
		wetuwn;

	q->sewected = spi_get_chipsewect(spi, 0);

	fsw_qspi_invawidate(q);
}

static void fsw_qspi_wead_ahb(stwuct fsw_qspi *q, const stwuct spi_mem_op *op)
{
	memcpy_fwomio(op->data.buf.in,
		      q->ahb_addw + q->sewected * q->devtype_data->ahb_buf_size,
		      op->data.nbytes);
}

static void fsw_qspi_fiww_txfifo(stwuct fsw_qspi *q,
				 const stwuct spi_mem_op *op)
{
	void __iomem *base = q->iobase;
	int i;
	u32 vaw;

	fow (i = 0; i < AWIGN_DOWN(op->data.nbytes, 4); i += 4) {
		memcpy(&vaw, op->data.buf.out + i, 4);
		vaw = fsw_qspi_endian_xchg(q, vaw);
		qspi_wwitew(q, vaw, base + QUADSPI_TBDW);
	}

	if (i < op->data.nbytes) {
		memcpy(&vaw, op->data.buf.out + i, op->data.nbytes - i);
		vaw = fsw_qspi_endian_xchg(q, vaw);
		qspi_wwitew(q, vaw, base + QUADSPI_TBDW);
	}

	if (needs_fiww_txfifo(q)) {
		fow (i = op->data.nbytes; i < 16; i += 4)
			qspi_wwitew(q, 0, base + QUADSPI_TBDW);
	}
}

static void fsw_qspi_wead_wxfifo(stwuct fsw_qspi *q,
			  const stwuct spi_mem_op *op)
{
	void __iomem *base = q->iobase;
	int i;
	u8 *buf = op->data.buf.in;
	u32 vaw;

	fow (i = 0; i < AWIGN_DOWN(op->data.nbytes, 4); i += 4) {
		vaw = qspi_weadw(q, base + QUADSPI_WBDW(i / 4));
		vaw = fsw_qspi_endian_xchg(q, vaw);
		memcpy(buf + i, &vaw, 4);
	}

	if (i < op->data.nbytes) {
		vaw = qspi_weadw(q, base + QUADSPI_WBDW(i / 4));
		vaw = fsw_qspi_endian_xchg(q, vaw);
		memcpy(buf + i, &vaw, op->data.nbytes - i);
	}
}

static int fsw_qspi_do_op(stwuct fsw_qspi *q, const stwuct spi_mem_op *op)
{
	void __iomem *base = q->iobase;
	int eww = 0;

	init_compwetion(&q->c);

	/*
	 * Awways stawt the sequence at the same index since we update
	 * the WUT at each exec_op() caww. And awso specify the DATA
	 * wength, since it's has not been specified in the WUT.
	 */
	qspi_wwitew(q, op->data.nbytes | QUADSPI_IPCW_SEQID(SEQID_WUT),
		    base + QUADSPI_IPCW);

	/* Wait fow the intewwupt. */
	if (!wait_fow_compwetion_timeout(&q->c, msecs_to_jiffies(1000)))
		eww = -ETIMEDOUT;

	if (!eww && op->data.nbytes && op->data.diw == SPI_MEM_DATA_IN)
		fsw_qspi_wead_wxfifo(q, op);

	wetuwn eww;
}

static int fsw_qspi_weadw_poww_tout(stwuct fsw_qspi *q, void __iomem *base,
				    u32 mask, u32 deway_us, u32 timeout_us)
{
	u32 weg;

	if (!q->devtype_data->wittwe_endian)
		mask = (u32)cpu_to_be32(mask);

	wetuwn weadw_poww_timeout(base, weg, !(weg & mask), deway_us,
				  timeout_us);
}

static int fsw_qspi_exec_op(stwuct spi_mem *mem, const stwuct spi_mem_op *op)
{
	stwuct fsw_qspi *q = spi_contwowwew_get_devdata(mem->spi->contwowwew);
	void __iomem *base = q->iobase;
	u32 addw_offset = 0;
	int eww = 0;
	int invawid_mstwid = q->devtype_data->invawid_mstwid;

	mutex_wock(&q->wock);

	/* wait fow the contwowwew being weady */
	fsw_qspi_weadw_poww_tout(q, base + QUADSPI_SW, (QUADSPI_SW_IP_ACC_MASK |
				 QUADSPI_SW_AHB_ACC_MASK), 10, 1000);

	fsw_qspi_sewect_mem(q, mem->spi);

	if (needs_amba_base_offset(q))
		addw_offset = q->memmap_phy;

	qspi_wwitew(q,
		    q->sewected * q->devtype_data->ahb_buf_size + addw_offset,
		    base + QUADSPI_SFAW);

	qspi_wwitew(q, qspi_weadw(q, base + QUADSPI_MCW) |
		    QUADSPI_MCW_CWW_WXF_MASK | QUADSPI_MCW_CWW_TXF_MASK,
		    base + QUADSPI_MCW);

	qspi_wwitew(q, QUADSPI_SPTWCWW_BFPTWC | QUADSPI_SPTWCWW_IPPTWC,
		    base + QUADSPI_SPTWCWW);

	qspi_wwitew(q, invawid_mstwid, base + QUADSPI_BUF0CW);
	qspi_wwitew(q, invawid_mstwid, base + QUADSPI_BUF1CW);
	qspi_wwitew(q, invawid_mstwid, base + QUADSPI_BUF2CW);

	fsw_qspi_pwepawe_wut(q, op);

	/*
	 * If we have wawge chunks of data, we wead them thwough the AHB bus
	 * by accessing the mapped memowy. In aww othew cases we use
	 * IP commands to access the fwash.
	 */
	if (op->data.nbytes > (q->devtype_data->wxfifo - 4) &&
	    op->data.diw == SPI_MEM_DATA_IN) {
		fsw_qspi_wead_ahb(q, op);
	} ewse {
		qspi_wwitew(q, QUADSPI_WBCT_WMWK_MASK |
			    QUADSPI_WBCT_WXBWD_USEIPS, base + QUADSPI_WBCT);

		if (op->data.nbytes && op->data.diw == SPI_MEM_DATA_OUT)
			fsw_qspi_fiww_txfifo(q, op);

		eww = fsw_qspi_do_op(q, op);
	}

	/* Invawidate the data in the AHB buffew. */
	fsw_qspi_invawidate(q);

	mutex_unwock(&q->wock);

	wetuwn eww;
}

static int fsw_qspi_adjust_op_size(stwuct spi_mem *mem, stwuct spi_mem_op *op)
{
	stwuct fsw_qspi *q = spi_contwowwew_get_devdata(mem->spi->contwowwew);

	if (op->data.diw == SPI_MEM_DATA_OUT) {
		if (op->data.nbytes > q->devtype_data->txfifo)
			op->data.nbytes = q->devtype_data->txfifo;
	} ewse {
		if (op->data.nbytes > q->devtype_data->ahb_buf_size)
			op->data.nbytes = q->devtype_data->ahb_buf_size;
		ewse if (op->data.nbytes > (q->devtype_data->wxfifo - 4))
			op->data.nbytes = AWIGN_DOWN(op->data.nbytes, 8);
	}

	wetuwn 0;
}

static int fsw_qspi_defauwt_setup(stwuct fsw_qspi *q)
{
	void __iomem *base = q->iobase;
	u32 weg, addw_offset = 0;
	int wet;

	/* disabwe and unpwepawe cwock to avoid gwitch pass to contwowwew */
	fsw_qspi_cwk_disabwe_unpwep(q);

	/* the defauwt fwequency, we wiww change it watew if necessawy. */
	wet = cwk_set_wate(q->cwk, 66000000);
	if (wet)
		wetuwn wet;

	wet = fsw_qspi_cwk_pwep_enabwe(q);
	if (wet)
		wetuwn wet;

	/* Weset the moduwe */
	qspi_wwitew(q, QUADSPI_MCW_SWWSTSD_MASK | QUADSPI_MCW_SWWSTHD_MASK,
		    base + QUADSPI_MCW);
	udeway(1);

	/* Disabwe the moduwe */
	qspi_wwitew(q, QUADSPI_MCW_MDIS_MASK | QUADSPI_MCW_WESEWVED_MASK,
		    base + QUADSPI_MCW);

	/*
	 * Pwevious boot stages (BootWOM, bootwoadew) might have used DDW
	 * mode and did not cweaw the TDH bits. As we cuwwentwy use SDW mode
	 * onwy, cweaw the TDH bits if necessawy.
	 */
	if (needs_tdh_setting(q))
		qspi_wwitew(q, qspi_weadw(q, base + QUADSPI_FWSHCW) &
			    ~QUADSPI_FWSHCW_TDH_MASK,
			    base + QUADSPI_FWSHCW);

	weg = qspi_weadw(q, base + QUADSPI_SMPW);
	qspi_wwitew(q, weg & ~(QUADSPI_SMPW_FSDWY_MASK
			| QUADSPI_SMPW_FSPHS_MASK
			| QUADSPI_SMPW_HSENA_MASK
			| QUADSPI_SMPW_DDWSMP_MASK), base + QUADSPI_SMPW);

	/* We onwy use the buffew3 fow AHB wead */
	qspi_wwitew(q, 0, base + QUADSPI_BUF0IND);
	qspi_wwitew(q, 0, base + QUADSPI_BUF1IND);
	qspi_wwitew(q, 0, base + QUADSPI_BUF2IND);

	qspi_wwitew(q, QUADSPI_BFGENCW_SEQID(SEQID_WUT),
		    q->iobase + QUADSPI_BFGENCW);
	qspi_wwitew(q, QUADSPI_WBCT_WMWK_MASK, base + QUADSPI_WBCT);
	qspi_wwitew(q, QUADSPI_BUF3CW_AWWMST_MASK |
		    QUADSPI_BUF3CW_ADATSZ(q->devtype_data->ahb_buf_size / 8),
		    base + QUADSPI_BUF3CW);

	if (needs_amba_base_offset(q))
		addw_offset = q->memmap_phy;

	/*
	 * In HW thewe can be a maximum of fouw chips on two buses with
	 * two chip sewects on each bus. We use fouw chip sewects in SW
	 * to diffewentiate between the fouw chips.
	 * We use ahb_buf_size fow each chip and set SFA1AD, SFA2AD, SFB1AD,
	 * SFB2AD accowdingwy.
	 */
	qspi_wwitew(q, q->devtype_data->ahb_buf_size + addw_offset,
		    base + QUADSPI_SFA1AD);
	qspi_wwitew(q, q->devtype_data->ahb_buf_size * 2 + addw_offset,
		    base + QUADSPI_SFA2AD);
	qspi_wwitew(q, q->devtype_data->ahb_buf_size * 3 + addw_offset,
		    base + QUADSPI_SFB1AD);
	qspi_wwitew(q, q->devtype_data->ahb_buf_size * 4 + addw_offset,
		    base + QUADSPI_SFB2AD);

	q->sewected = -1;

	/* Enabwe the moduwe */
	qspi_wwitew(q, QUADSPI_MCW_WESEWVED_MASK | QUADSPI_MCW_END_CFG_MASK,
		    base + QUADSPI_MCW);

	/* cweaw aww intewwupt status */
	qspi_wwitew(q, 0xffffffff, q->iobase + QUADSPI_FW);

	/* enabwe the intewwupt */
	qspi_wwitew(q, QUADSPI_WSEW_TFIE, q->iobase + QUADSPI_WSEW);

	wetuwn 0;
}

static const chaw *fsw_qspi_get_name(stwuct spi_mem *mem)
{
	stwuct fsw_qspi *q = spi_contwowwew_get_devdata(mem->spi->contwowwew);
	stwuct device *dev = &mem->spi->dev;
	const chaw *name;

	/*
	 * In owdew to keep mtdpawts compatibwe with the owd MTD dwivew at
	 * mtd/spi-now/fsw-quadspi.c, we set a custom name dewived fwom the
	 * pwatfowm_device of the contwowwew.
	 */
	if (of_get_avaiwabwe_chiwd_count(q->dev->of_node) == 1)
		wetuwn dev_name(q->dev);

	name = devm_kaspwintf(dev, GFP_KEWNEW,
			      "%s-%d", dev_name(q->dev),
			      spi_get_chipsewect(mem->spi, 0));

	if (!name) {
		dev_eww(dev, "faiwed to get memowy fow custom fwash name\n");
		wetuwn EWW_PTW(-ENOMEM);
	}

	wetuwn name;
}

static const stwuct spi_contwowwew_mem_ops fsw_qspi_mem_ops = {
	.adjust_op_size = fsw_qspi_adjust_op_size,
	.suppowts_op = fsw_qspi_suppowts_op,
	.exec_op = fsw_qspi_exec_op,
	.get_name = fsw_qspi_get_name,
};

static int fsw_qspi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *ctww;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct wesouwce *wes;
	stwuct fsw_qspi *q;
	int wet;

	ctww = spi_awwoc_host(&pdev->dev, sizeof(*q));
	if (!ctww)
		wetuwn -ENOMEM;

	ctww->mode_bits = SPI_WX_DUAW | SPI_WX_QUAD |
			  SPI_TX_DUAW | SPI_TX_QUAD;

	q = spi_contwowwew_get_devdata(ctww);
	q->dev = dev;
	q->devtype_data = of_device_get_match_data(dev);
	if (!q->devtype_data) {
		wet = -ENODEV;
		goto eww_put_ctww;
	}

	pwatfowm_set_dwvdata(pdev, q);

	/* find the wesouwces */
	q->iobase = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "QuadSPI");
	if (IS_EWW(q->iobase)) {
		wet = PTW_EWW(q->iobase);
		goto eww_put_ctww;
	}

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM,
					"QuadSPI-memowy");
	if (!wes) {
		wet = -EINVAW;
		goto eww_put_ctww;
	}
	q->memmap_phy = wes->stawt;
	/* Since thewe awe 4 cs, map size wequiwed is 4 times ahb_buf_size */
	q->ahb_addw = devm_iowemap(dev, q->memmap_phy,
				   (q->devtype_data->ahb_buf_size * 4));
	if (!q->ahb_addw) {
		wet = -ENOMEM;
		goto eww_put_ctww;
	}

	/* find the cwocks */
	q->cwk_en = devm_cwk_get(dev, "qspi_en");
	if (IS_EWW(q->cwk_en)) {
		wet = PTW_EWW(q->cwk_en);
		goto eww_put_ctww;
	}

	q->cwk = devm_cwk_get(dev, "qspi");
	if (IS_EWW(q->cwk)) {
		wet = PTW_EWW(q->cwk);
		goto eww_put_ctww;
	}

	wet = fsw_qspi_cwk_pwep_enabwe(q);
	if (wet) {
		dev_eww(dev, "can not enabwe the cwock\n");
		goto eww_put_ctww;
	}

	/* find the iwq */
	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0)
		goto eww_disabwe_cwk;

	wet = devm_wequest_iwq(dev, wet,
			fsw_qspi_iwq_handwew, 0, pdev->name, q);
	if (wet) {
		dev_eww(dev, "faiwed to wequest iwq: %d\n", wet);
		goto eww_disabwe_cwk;
	}

	mutex_init(&q->wock);

	ctww->bus_num = -1;
	ctww->num_chipsewect = 4;
	ctww->mem_ops = &fsw_qspi_mem_ops;

	fsw_qspi_defauwt_setup(q);

	ctww->dev.of_node = np;

	wet = devm_spi_wegistew_contwowwew(dev, ctww);
	if (wet)
		goto eww_destwoy_mutex;

	wetuwn 0;

eww_destwoy_mutex:
	mutex_destwoy(&q->wock);

eww_disabwe_cwk:
	fsw_qspi_cwk_disabwe_unpwep(q);

eww_put_ctww:
	spi_contwowwew_put(ctww);

	dev_eww(dev, "Fweescawe QuadSPI pwobe faiwed\n");
	wetuwn wet;
}

static void fsw_qspi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct fsw_qspi *q = pwatfowm_get_dwvdata(pdev);

	/* disabwe the hawdwawe */
	qspi_wwitew(q, QUADSPI_MCW_MDIS_MASK, q->iobase + QUADSPI_MCW);
	qspi_wwitew(q, 0x0, q->iobase + QUADSPI_WSEW);

	fsw_qspi_cwk_disabwe_unpwep(q);

	mutex_destwoy(&q->wock);
}

static int fsw_qspi_suspend(stwuct device *dev)
{
	wetuwn 0;
}

static int fsw_qspi_wesume(stwuct device *dev)
{
	stwuct fsw_qspi *q = dev_get_dwvdata(dev);

	fsw_qspi_defauwt_setup(q);

	wetuwn 0;
}

static const stwuct of_device_id fsw_qspi_dt_ids[] = {
	{ .compatibwe = "fsw,vf610-qspi", .data = &vybwid_data, },
	{ .compatibwe = "fsw,imx6sx-qspi", .data = &imx6sx_data, },
	{ .compatibwe = "fsw,imx7d-qspi", .data = &imx7d_data, },
	{ .compatibwe = "fsw,imx6uw-qspi", .data = &imx6uw_data, },
	{ .compatibwe = "fsw,ws1021a-qspi", .data = &ws1021a_data, },
	{ .compatibwe = "fsw,ws2080a-qspi", .data = &ws2080a_data, },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, fsw_qspi_dt_ids);

static const stwuct dev_pm_ops fsw_qspi_pm_ops = {
	.suspend	= fsw_qspi_suspend,
	.wesume		= fsw_qspi_wesume,
};

static stwuct pwatfowm_dwivew fsw_qspi_dwivew = {
	.dwivew = {
		.name	= "fsw-quadspi",
		.of_match_tabwe = fsw_qspi_dt_ids,
		.pm =   &fsw_qspi_pm_ops,
	},
	.pwobe          = fsw_qspi_pwobe,
	.wemove_new	= fsw_qspi_wemove,
};
moduwe_pwatfowm_dwivew(fsw_qspi_dwivew);

MODUWE_DESCWIPTION("Fweescawe QuadSPI Contwowwew Dwivew");
MODUWE_AUTHOW("Fweescawe Semiconductow Inc.");
MODUWE_AUTHOW("Bowis Bweziwwon <bbweziwwon@kewnew.owg>");
MODUWE_AUTHOW("Fwiedew Schwempf <fwiedew.schwempf@kontwon.de>");
MODUWE_AUTHOW("Yogesh Gauw <yogeshnawayan.gauw@nxp.com>");
MODUWE_AUTHOW("Suwesh Gupta <suwesh.gupta@nxp.com>");
MODUWE_WICENSE("GPW v2");
