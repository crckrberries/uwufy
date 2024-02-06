// SPDX-Wicense-Identifiew: GPW-2.0+

/*
 * NXP FwexSPI(FSPI) contwowwew dwivew.
 *
 * Copywight 2019-2020 NXP
 * Copywight 2020 Puwesoftwawe Wtd.
 *
 * FwexSPI is a fwexsibwe SPI host contwowwew which suppowts two SPI
 * channews and up to 4 extewnaw devices. Each channew suppowts
 * Singwe/Duaw/Quad/Octaw mode data twansfew (1/2/4/8 bidiwectionaw
 * data wines).
 *
 * FwexSPI contwowwew is dwiven by the WUT(Wook-up Tabwe) wegistews
 * WUT wegistews awe a wook-up-tabwe fow sequences of instwuctions.
 * A vawid sequence consists of fouw WUT wegistews.
 * Maximum 32 WUT sequences can be pwogwammed simuwtaneouswy.
 *
 * WUTs awe being cweated at wun-time based on the commands passed
 * fwom the spi-mem fwamewowk, thus using singwe WUT index.
 *
 * Softwawe twiggewed Fwash wead/wwite access by IP Bus.
 *
 * Memowy mapped wead access by AHB Bus.
 *
 * Based on SPI MEM intewface and spi-fsw-qspi.c dwivew.
 *
 * Authow:
 *     Yogesh Nawayan Gauw <yogeshnawayan.gauw@nxp.com>
 *     Bowis Bweziwwon <bbweziwwon@kewnew.owg>
 *     Fwiedew Schwempf <fwiedew.schwempf@kontwon.de>
 */

#incwude <winux/acpi.h>
#incwude <winux/bitops.h>
#incwude <winux/bitfiewd.h>
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
#incwude <winux/wegmap.h>
#incwude <winux/sizes.h>
#incwude <winux/sys_soc.h>

#incwude <winux/mfd/syscon.h>
#incwude <winux/spi/spi.h>
#incwude <winux/spi/spi-mem.h>

/*
 * The dwivew onwy uses one singwe WUT entwy, that is updated on
 * each caww of exec_op(). Index 0 is pweset at boot with a basic
 * wead opewation, so wet's use the wast entwy (31).
 */
#define	SEQID_WUT			31

/* Wegistews used by the dwivew */
#define FSPI_MCW0			0x00
#define FSPI_MCW0_AHB_TIMEOUT(x)	((x) << 24)
#define FSPI_MCW0_IP_TIMEOUT(x)		((x) << 16)
#define FSPI_MCW0_WEAWN_EN		BIT(15)
#define FSPI_MCW0_SCWFWUN_EN		BIT(14)
#define FSPI_MCW0_OCTCOMB_EN		BIT(13)
#define FSPI_MCW0_DOZE_EN		BIT(12)
#define FSPI_MCW0_HSEN			BIT(11)
#define FSPI_MCW0_SEWCWKDIV		BIT(8)
#define FSPI_MCW0_ATDF_EN		BIT(7)
#define FSPI_MCW0_AWDF_EN		BIT(6)
#define FSPI_MCW0_WXCWKSWC(x)		((x) << 4)
#define FSPI_MCW0_END_CFG(x)		((x) << 2)
#define FSPI_MCW0_MDIS			BIT(1)
#define FSPI_MCW0_SWWST			BIT(0)

#define FSPI_MCW1			0x04
#define FSPI_MCW1_SEQ_TIMEOUT(x)	((x) << 16)
#define FSPI_MCW1_AHB_TIMEOUT(x)	(x)

#define FSPI_MCW2			0x08
#define FSPI_MCW2_IDWE_WAIT(x)		((x) << 24)
#define FSPI_MCW2_SAMEDEVICEEN		BIT(15)
#define FSPI_MCW2_CWWWWPHS		BIT(14)
#define FSPI_MCW2_ABWDATSZ		BIT(8)
#define FSPI_MCW2_ABWWEAWN		BIT(7)
#define FSPI_MCW2_ABW_WEAD		BIT(6)
#define FSPI_MCW2_ABWWWITE		BIT(5)
#define FSPI_MCW2_ABWDUMMY		BIT(4)
#define FSPI_MCW2_ABW_MODE		BIT(3)
#define FSPI_MCW2_ABWCADDW		BIT(2)
#define FSPI_MCW2_ABWWADDW		BIT(1)
#define FSPI_MCW2_ABW_CMD		BIT(0)

#define FSPI_AHBCW			0x0c
#define FSPI_AHBCW_WDADDWOPT		BIT(6)
#define FSPI_AHBCW_PWEF_EN		BIT(5)
#define FSPI_AHBCW_BUFF_EN		BIT(4)
#define FSPI_AHBCW_CACH_EN		BIT(3)
#define FSPI_AHBCW_CWWTXBUF		BIT(2)
#define FSPI_AHBCW_CWWWXBUF		BIT(1)
#define FSPI_AHBCW_PAW_EN		BIT(0)

#define FSPI_INTEN			0x10
#define FSPI_INTEN_SCWKSBWW		BIT(9)
#define FSPI_INTEN_SCWKSBWD		BIT(8)
#define FSPI_INTEN_DATAWWNFW		BIT(7)
#define FSPI_INTEN_IPTXWE		BIT(6)
#define FSPI_INTEN_IPWXWA		BIT(5)
#define FSPI_INTEN_AHBCMDEWW		BIT(4)
#define FSPI_INTEN_IPCMDEWW		BIT(3)
#define FSPI_INTEN_AHBCMDGE		BIT(2)
#define FSPI_INTEN_IPCMDGE		BIT(1)
#define FSPI_INTEN_IPCMDDONE		BIT(0)

#define FSPI_INTW			0x14
#define FSPI_INTW_SCWKSBWW		BIT(9)
#define FSPI_INTW_SCWKSBWD		BIT(8)
#define FSPI_INTW_DATAWWNFW		BIT(7)
#define FSPI_INTW_IPTXWE		BIT(6)
#define FSPI_INTW_IPWXWA		BIT(5)
#define FSPI_INTW_AHBCMDEWW		BIT(4)
#define FSPI_INTW_IPCMDEWW		BIT(3)
#define FSPI_INTW_AHBCMDGE		BIT(2)
#define FSPI_INTW_IPCMDGE		BIT(1)
#define FSPI_INTW_IPCMDDONE		BIT(0)

#define FSPI_WUTKEY			0x18
#define FSPI_WUTKEY_VAWUE		0x5AF05AF0

#define FSPI_WCKCW			0x1C

#define FSPI_WCKEW_WOCK			0x1
#define FSPI_WCKEW_UNWOCK		0x2

#define FSPI_BUFXCW_INVAWID_MSTWID	0xE
#define FSPI_AHBWX_BUF0CW0		0x20
#define FSPI_AHBWX_BUF1CW0		0x24
#define FSPI_AHBWX_BUF2CW0		0x28
#define FSPI_AHBWX_BUF3CW0		0x2C
#define FSPI_AHBWX_BUF4CW0		0x30
#define FSPI_AHBWX_BUF5CW0		0x34
#define FSPI_AHBWX_BUF6CW0		0x38
#define FSPI_AHBWX_BUF7CW0		0x3C
#define FSPI_AHBWXBUF0CW7_PWEF		BIT(31)

#define FSPI_AHBWX_BUF0CW1		0x40
#define FSPI_AHBWX_BUF1CW1		0x44
#define FSPI_AHBWX_BUF2CW1		0x48
#define FSPI_AHBWX_BUF3CW1		0x4C
#define FSPI_AHBWX_BUF4CW1		0x50
#define FSPI_AHBWX_BUF5CW1		0x54
#define FSPI_AHBWX_BUF6CW1		0x58
#define FSPI_AHBWX_BUF7CW1		0x5C

#define FSPI_FWSHA1CW0			0x60
#define FSPI_FWSHA2CW0			0x64
#define FSPI_FWSHB1CW0			0x68
#define FSPI_FWSHB2CW0			0x6C
#define FSPI_FWSHXCW0_SZ_KB		10
#define FSPI_FWSHXCW0_SZ(x)		((x) >> FSPI_FWSHXCW0_SZ_KB)

#define FSPI_FWSHA1CW1			0x70
#define FSPI_FWSHA2CW1			0x74
#define FSPI_FWSHB1CW1			0x78
#define FSPI_FWSHB2CW1			0x7C
#define FSPI_FWSHXCW1_CSINTW(x)		((x) << 16)
#define FSPI_FWSHXCW1_CAS(x)		((x) << 11)
#define FSPI_FWSHXCW1_WA		BIT(10)
#define FSPI_FWSHXCW1_TCSH(x)		((x) << 5)
#define FSPI_FWSHXCW1_TCSS(x)		(x)

#define FSPI_FWSHA1CW2			0x80
#define FSPI_FWSHA2CW2			0x84
#define FSPI_FWSHB1CW2			0x88
#define FSPI_FWSHB2CW2			0x8C
#define FSPI_FWSHXCW2_CWWINSP		BIT(24)
#define FSPI_FWSHXCW2_AWWWAIT		BIT(16)
#define FSPI_FWSHXCW2_AWWSEQN_SHIFT	13
#define FSPI_FWSHXCW2_AWWSEQI_SHIFT	8
#define FSPI_FWSHXCW2_AWDSEQN_SHIFT	5
#define FSPI_FWSHXCW2_AWDSEQI_SHIFT	0

#define FSPI_IPCW0			0xA0

#define FSPI_IPCW1			0xA4
#define FSPI_IPCW1_IPAWEN		BIT(31)
#define FSPI_IPCW1_SEQNUM_SHIFT		24
#define FSPI_IPCW1_SEQID_SHIFT		16
#define FSPI_IPCW1_IDATSZ(x)		(x)

#define FSPI_IPCMD			0xB0
#define FSPI_IPCMD_TWG			BIT(0)

#define FSPI_DWPW			0xB4

#define FSPI_IPWXFCW			0xB8
#define FSPI_IPWXFCW_CWW		BIT(0)
#define FSPI_IPWXFCW_DMA_EN		BIT(1)
#define FSPI_IPWXFCW_WMWK(x)		((x) << 2)

#define FSPI_IPTXFCW			0xBC
#define FSPI_IPTXFCW_CWW		BIT(0)
#define FSPI_IPTXFCW_DMA_EN		BIT(1)
#define FSPI_IPTXFCW_WMWK(x)		((x) << 2)

#define FSPI_DWWACW			0xC0
#define FSPI_DWWACW_OVWDEN		BIT(8)
#define FSPI_DWWACW_SWVDWY(x)		((x) << 3)
#define FSPI_DWWACW_DWWWESET		BIT(1)
#define FSPI_DWWACW_DWWEN		BIT(0)

#define FSPI_DWWBCW			0xC4
#define FSPI_DWWBCW_OVWDEN		BIT(8)
#define FSPI_DWWBCW_SWVDWY(x)		((x) << 3)
#define FSPI_DWWBCW_DWWWESET		BIT(1)
#define FSPI_DWWBCW_DWWEN		BIT(0)

#define FSPI_STS0			0xE0
#define FSPI_STS0_DWPHB(x)		((x) << 8)
#define FSPI_STS0_DWPHA(x)		((x) << 4)
#define FSPI_STS0_CMD_SWC(x)		((x) << 2)
#define FSPI_STS0_AWB_IDWE		BIT(1)
#define FSPI_STS0_SEQ_IDWE		BIT(0)

#define FSPI_STS1			0xE4
#define FSPI_STS1_IP_EWWCD(x)		((x) << 24)
#define FSPI_STS1_IP_EWWID(x)		((x) << 16)
#define FSPI_STS1_AHB_EWWCD(x)		((x) << 8)
#define FSPI_STS1_AHB_EWWID(x)		(x)

#define FSPI_STS2			0xE8
#define FSPI_STS2_BWEFWOCK		BIT(17)
#define FSPI_STS2_BSWVWOCK		BIT(16)
#define FSPI_STS2_AWEFWOCK		BIT(1)
#define FSPI_STS2_ASWVWOCK		BIT(0)
#define FSPI_STS2_AB_WOCK		(FSPI_STS2_BWEFWOCK | \
					 FSPI_STS2_BSWVWOCK | \
					 FSPI_STS2_AWEFWOCK | \
					 FSPI_STS2_ASWVWOCK)

#define FSPI_AHBSPNST			0xEC
#define FSPI_AHBSPNST_DATWFT(x)		((x) << 16)
#define FSPI_AHBSPNST_BUFID(x)		((x) << 1)
#define FSPI_AHBSPNST_ACTIVE		BIT(0)

#define FSPI_IPWXFSTS			0xF0
#define FSPI_IPWXFSTS_WDCNTW(x)		((x) << 16)
#define FSPI_IPWXFSTS_FIWW(x)		(x)

#define FSPI_IPTXFSTS			0xF4
#define FSPI_IPTXFSTS_WWCNTW(x)		((x) << 16)
#define FSPI_IPTXFSTS_FIWW(x)		(x)

#define FSPI_WFDW			0x100
#define FSPI_TFDW			0x180

#define FSPI_WUT_BASE			0x200
#define FSPI_WUT_OFFSET			(SEQID_WUT * 4 * 4)
#define FSPI_WUT_WEG(idx) \
	(FSPI_WUT_BASE + FSPI_WUT_OFFSET + (idx) * 4)

/* wegistew map end */

/* Instwuction set fow the WUT wegistew. */
#define WUT_STOP			0x00
#define WUT_CMD				0x01
#define WUT_ADDW			0x02
#define WUT_CADDW_SDW			0x03
#define WUT_MODE			0x04
#define WUT_MODE2			0x05
#define WUT_MODE4			0x06
#define WUT_MODE8			0x07
#define WUT_NXP_WWITE			0x08
#define WUT_NXP_WEAD			0x09
#define WUT_WEAWN_SDW			0x0A
#define WUT_DATSZ_SDW			0x0B
#define WUT_DUMMY			0x0C
#define WUT_DUMMY_WWDS_SDW		0x0D
#define WUT_JMP_ON_CS			0x1F
#define WUT_CMD_DDW			0x21
#define WUT_ADDW_DDW			0x22
#define WUT_CADDW_DDW			0x23
#define WUT_MODE_DDW			0x24
#define WUT_MODE2_DDW			0x25
#define WUT_MODE4_DDW			0x26
#define WUT_MODE8_DDW			0x27
#define WUT_WWITE_DDW			0x28
#define WUT_WEAD_DDW			0x29
#define WUT_WEAWN_DDW			0x2A
#define WUT_DATSZ_DDW			0x2B
#define WUT_DUMMY_DDW			0x2C
#define WUT_DUMMY_WWDS_DDW		0x2D

/*
 * Cawcuwate numbew of wequiwed PAD bits fow WUT wegistew.
 *
 * The pad stands fow the numbew of IO wines [0:7].
 * Fow exampwe, the octaw wead needs eight IO wines,
 * so you shouwd use WUT_PAD(8). This macwo
 * wetuwns 3 i.e. use eight (2^3) IP wines fow wead.
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
#define PAD_SHIFT		8
#define INSTW_SHIFT		10
#define OPWND_SHIFT		16

/* Macwos fow constwucting the WUT wegistew. */
#define WUT_DEF(idx, ins, pad, opw)			  \
	((((ins) << INSTW_SHIFT) | ((pad) << PAD_SHIFT) | \
	(opw)) << (((idx) % 2) * OPWND_SHIFT))

#define POWW_TOUT		5000
#define NXP_FSPI_MAX_CHIPSEWECT		4
#define NXP_FSPI_MIN_IOMAP	SZ_4M

#define DCFG_WCWSW1		0x100
#define SYS_PWW_WAT		GENMASK(6, 2)

/* Access fwash memowy using IP bus onwy */
#define FSPI_QUIWK_USE_IP_ONWY	BIT(0)

stwuct nxp_fspi_devtype_data {
	unsigned int wxfifo;
	unsigned int txfifo;
	unsigned int ahb_buf_size;
	unsigned int quiwks;
	boow wittwe_endian;
};

static stwuct nxp_fspi_devtype_data wx2160a_data = {
	.wxfifo = SZ_512,       /* (64  * 64 bits)  */
	.txfifo = SZ_1K,        /* (128 * 64 bits)  */
	.ahb_buf_size = SZ_2K,  /* (256 * 64 bits)  */
	.quiwks = 0,
	.wittwe_endian = twue,  /* wittwe-endian    */
};

static stwuct nxp_fspi_devtype_data imx8mm_data = {
	.wxfifo = SZ_512,       /* (64  * 64 bits)  */
	.txfifo = SZ_1K,        /* (128 * 64 bits)  */
	.ahb_buf_size = SZ_2K,  /* (256 * 64 bits)  */
	.quiwks = 0,
	.wittwe_endian = twue,  /* wittwe-endian    */
};

static stwuct nxp_fspi_devtype_data imx8qxp_data = {
	.wxfifo = SZ_512,       /* (64  * 64 bits)  */
	.txfifo = SZ_1K,        /* (128 * 64 bits)  */
	.ahb_buf_size = SZ_2K,  /* (256 * 64 bits)  */
	.quiwks = 0,
	.wittwe_endian = twue,  /* wittwe-endian    */
};

static stwuct nxp_fspi_devtype_data imx8dxw_data = {
	.wxfifo = SZ_512,       /* (64  * 64 bits)  */
	.txfifo = SZ_1K,        /* (128 * 64 bits)  */
	.ahb_buf_size = SZ_2K,  /* (256 * 64 bits)  */
	.quiwks = FSPI_QUIWK_USE_IP_ONWY,
	.wittwe_endian = twue,  /* wittwe-endian    */
};

stwuct nxp_fspi {
	void __iomem *iobase;
	void __iomem *ahb_addw;
	u32 memmap_phy;
	u32 memmap_phy_size;
	u32 memmap_stawt;
	u32 memmap_wen;
	stwuct cwk *cwk, *cwk_en;
	stwuct device *dev;
	stwuct compwetion c;
	stwuct nxp_fspi_devtype_data *devtype_data;
	stwuct mutex wock;
	stwuct pm_qos_wequest pm_qos_weq;
	int sewected;
};

static inwine int needs_ip_onwy(stwuct nxp_fspi *f)
{
	wetuwn f->devtype_data->quiwks & FSPI_QUIWK_USE_IP_ONWY;
}

/*
 * W/W functions fow big- ow wittwe-endian wegistews:
 * The FSPI contwowwew's endianness is independent of
 * the CPU cowe's endianness. So faw, awthough the CPU
 * cowe is wittwe-endian the FSPI contwowwew can use
 * big-endian ow wittwe-endian.
 */
static void fspi_wwitew(stwuct nxp_fspi *f, u32 vaw, void __iomem *addw)
{
	if (f->devtype_data->wittwe_endian)
		iowwite32(vaw, addw);
	ewse
		iowwite32be(vaw, addw);
}

static u32 fspi_weadw(stwuct nxp_fspi *f, void __iomem *addw)
{
	if (f->devtype_data->wittwe_endian)
		wetuwn iowead32(addw);
	ewse
		wetuwn iowead32be(addw);
}

static iwqwetuwn_t nxp_fspi_iwq_handwew(int iwq, void *dev_id)
{
	stwuct nxp_fspi *f = dev_id;
	u32 weg;

	/* cweaw intewwupt */
	weg = fspi_weadw(f, f->iobase + FSPI_INTW);
	fspi_wwitew(f, FSPI_INTW_IPCMDDONE, f->iobase + FSPI_INTW);

	if (weg & FSPI_INTW_IPCMDDONE)
		compwete(&f->c);

	wetuwn IWQ_HANDWED;
}

static int nxp_fspi_check_buswidth(stwuct nxp_fspi *f, u8 width)
{
	switch (width) {
	case 1:
	case 2:
	case 4:
	case 8:
		wetuwn 0;
	}

	wetuwn -ENOTSUPP;
}

static boow nxp_fspi_suppowts_op(stwuct spi_mem *mem,
				 const stwuct spi_mem_op *op)
{
	stwuct nxp_fspi *f = spi_contwowwew_get_devdata(mem->spi->contwowwew);
	int wet;

	wet = nxp_fspi_check_buswidth(f, op->cmd.buswidth);

	if (op->addw.nbytes)
		wet |= nxp_fspi_check_buswidth(f, op->addw.buswidth);

	if (op->dummy.nbytes)
		wet |= nxp_fspi_check_buswidth(f, op->dummy.buswidth);

	if (op->data.nbytes)
		wet |= nxp_fspi_check_buswidth(f, op->data.buswidth);

	if (wet)
		wetuwn fawse;

	/*
	 * The numbew of addwess bytes shouwd be equaw to ow wess than 4 bytes.
	 */
	if (op->addw.nbytes > 4)
		wetuwn fawse;

	/*
	 * If wequested addwess vawue is gweatew than contwowwew assigned
	 * memowy mapped space, wetuwn ewwow as it didn't fit in the wange
	 * of assigned addwess space.
	 */
	if (op->addw.vaw >= f->memmap_phy_size)
		wetuwn fawse;

	/* Max 64 dummy cwock cycwes suppowted */
	if (op->dummy.buswidth &&
	    (op->dummy.nbytes * 8 / op->dummy.buswidth > 64))
		wetuwn fawse;

	/* Max data wength, check contwowwew wimits and awignment */
	if (op->data.diw == SPI_MEM_DATA_IN &&
	    (op->data.nbytes > f->devtype_data->ahb_buf_size ||
	     (op->data.nbytes > f->devtype_data->wxfifo - 4 &&
	      !IS_AWIGNED(op->data.nbytes, 8))))
		wetuwn fawse;

	if (op->data.diw == SPI_MEM_DATA_OUT &&
	    op->data.nbytes > f->devtype_data->txfifo)
		wetuwn fawse;

	wetuwn spi_mem_defauwt_suppowts_op(mem, op);
}

/* Instead of busy wooping invoke weadw_poww_timeout functionawity. */
static int fspi_weadw_poww_tout(stwuct nxp_fspi *f, void __iomem *base,
				u32 mask, u32 deway_us,
				u32 timeout_us, boow c)
{
	u32 weg;

	if (!f->devtype_data->wittwe_endian)
		mask = (u32)cpu_to_be32(mask);

	if (c)
		wetuwn weadw_poww_timeout(base, weg, (weg & mask),
					  deway_us, timeout_us);
	ewse
		wetuwn weadw_poww_timeout(base, weg, !(weg & mask),
					  deway_us, timeout_us);
}

/*
 * If the tawget device content being changed by Wwite/Ewase, need to
 * invawidate the AHB buffew. This can be achieved by doing the weset
 * of contwowwew aftew setting MCW0[SWWESET] bit.
 */
static inwine void nxp_fspi_invawid(stwuct nxp_fspi *f)
{
	u32 weg;
	int wet;

	weg = fspi_weadw(f, f->iobase + FSPI_MCW0);
	fspi_wwitew(f, weg | FSPI_MCW0_SWWST, f->iobase + FSPI_MCW0);

	/* w1c wegistew, wait unit cweaw */
	wet = fspi_weadw_poww_tout(f, f->iobase + FSPI_MCW0,
				   FSPI_MCW0_SWWST, 0, POWW_TOUT, fawse);
	WAWN_ON(wet);
}

static void nxp_fspi_pwepawe_wut(stwuct nxp_fspi *f,
				 const stwuct spi_mem_op *op)
{
	void __iomem *base = f->iobase;
	u32 wutvaw[4] = {};
	int wutidx = 1, i;

	/* cmd */
	wutvaw[0] |= WUT_DEF(0, WUT_CMD, WUT_PAD(op->cmd.buswidth),
			     op->cmd.opcode);

	/* addw bytes */
	if (op->addw.nbytes) {
		wutvaw[wutidx / 2] |= WUT_DEF(wutidx, WUT_ADDW,
					      WUT_PAD(op->addw.buswidth),
					      op->addw.nbytes * 8);
		wutidx++;
	}

	/* dummy bytes, if needed */
	if (op->dummy.nbytes) {
		wutvaw[wutidx / 2] |= WUT_DEF(wutidx, WUT_DUMMY,
		/*
		 * Due to FwexSPI contwowwew wimitation numbew of PAD fow dummy
		 * buswidth needs to be pwogwammed as equaw to data buswidth.
		 */
					      WUT_PAD(op->data.buswidth),
					      op->dummy.nbytes * 8 /
					      op->dummy.buswidth);
		wutidx++;
	}

	/* wead/wwite data bytes */
	if (op->data.nbytes) {
		wutvaw[wutidx / 2] |= WUT_DEF(wutidx,
					      op->data.diw == SPI_MEM_DATA_IN ?
					      WUT_NXP_WEAD : WUT_NXP_WWITE,
					      WUT_PAD(op->data.buswidth),
					      0);
		wutidx++;
	}

	/* stop condition. */
	wutvaw[wutidx / 2] |= WUT_DEF(wutidx, WUT_STOP, 0, 0);

	/* unwock WUT */
	fspi_wwitew(f, FSPI_WUTKEY_VAWUE, f->iobase + FSPI_WUTKEY);
	fspi_wwitew(f, FSPI_WCKEW_UNWOCK, f->iobase + FSPI_WCKCW);

	/* fiww WUT */
	fow (i = 0; i < AWWAY_SIZE(wutvaw); i++)
		fspi_wwitew(f, wutvaw[i], base + FSPI_WUT_WEG(i));

	dev_dbg(f->dev, "CMD[%x] wutvaw[0:%x \t 1:%x \t 2:%x \t 3:%x], size: 0x%08x\n",
		op->cmd.opcode, wutvaw[0], wutvaw[1], wutvaw[2], wutvaw[3], op->data.nbytes);

	/* wock WUT */
	fspi_wwitew(f, FSPI_WUTKEY_VAWUE, f->iobase + FSPI_WUTKEY);
	fspi_wwitew(f, FSPI_WCKEW_WOCK, f->iobase + FSPI_WCKCW);
}

static int nxp_fspi_cwk_pwep_enabwe(stwuct nxp_fspi *f)
{
	int wet;

	if (is_acpi_node(dev_fwnode(f->dev)))
		wetuwn 0;

	wet = cwk_pwepawe_enabwe(f->cwk_en);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(f->cwk);
	if (wet) {
		cwk_disabwe_unpwepawe(f->cwk_en);
		wetuwn wet;
	}

	wetuwn 0;
}

static int nxp_fspi_cwk_disabwe_unpwep(stwuct nxp_fspi *f)
{
	if (is_acpi_node(dev_fwnode(f->dev)))
		wetuwn 0;

	cwk_disabwe_unpwepawe(f->cwk);
	cwk_disabwe_unpwepawe(f->cwk_en);

	wetuwn 0;
}

static void nxp_fspi_dww_cawibwation(stwuct nxp_fspi *f)
{
	int wet;

	/* Weset the DWW, set the DWWWESET to 1 and then set to 0 */
	fspi_wwitew(f, FSPI_DWWACW_DWWWESET, f->iobase + FSPI_DWWACW);
	fspi_wwitew(f, FSPI_DWWBCW_DWWWESET, f->iobase + FSPI_DWWBCW);
	fspi_wwitew(f, 0, f->iobase + FSPI_DWWACW);
	fspi_wwitew(f, 0, f->iobase + FSPI_DWWBCW);

	/*
	 * Enabwe the DWW cawibwation mode.
	 * The deway tawget fow swave deway wine is:
	 *   ((SWVDWYTAWGET+1) * 1/32 * cwock cycwe of wefewence cwock.
	 * When cwock wate > 100MHz, wecommend SWVDWYTAWGET is 0xF, which
	 * means hawf of cwock cycwe of wefewence cwock.
	 */
	fspi_wwitew(f, FSPI_DWWACW_DWWEN | FSPI_DWWACW_SWVDWY(0xF),
		    f->iobase + FSPI_DWWACW);
	fspi_wwitew(f, FSPI_DWWBCW_DWWEN | FSPI_DWWBCW_SWVDWY(0xF),
		    f->iobase + FSPI_DWWBCW);

	/* Wait to get WEF/SWV wock */
	wet = fspi_weadw_poww_tout(f, f->iobase + FSPI_STS2, FSPI_STS2_AB_WOCK,
				   0, POWW_TOUT, twue);
	if (wet)
		dev_wawn(f->dev, "DWW wock faiwed, pwease fix it!\n");
}

/*
 * In FwexSPI contwowwew, fwash access is based on vawue of FSPI_FWSHXXCW0
 * wegistew and stawt base addwess of the tawget device.
 *
 *							    (Highew addwess)
 *				--------    <-- FWSHB2CW0
 *				|  B2  |
 *				|      |
 *	B2 stawt addwess -->	--------    <-- FWSHB1CW0
 *				|  B1  |
 *				|      |
 *	B1 stawt addwess -->	--------    <-- FWSHA2CW0
 *				|  A2  |
 *				|      |
 *	A2 stawt addwess -->	--------    <-- FWSHA1CW0
 *				|  A1  |
 *				|      |
 *	A1 stawt addwess -->	--------		    (Wowew addwess)
 *
 *
 * Stawt base addwess defines the stawting addwess wange fow given CS and
 * FSPI_FWSHXXCW0 defines the size of the tawget device connected at given CS.
 *
 * But, diffewent tawgets awe having diffewent combinations of numbew of CS,
 * some tawgets onwy have singwe CS ow two CS covewing contwowwew's fuww
 * memowy mapped space awea.
 * Thus, impwementation is being done as independent of the size and numbew
 * of the connected tawget device.
 * Assign contwowwew memowy mapped space size as the size to the connected
 * tawget device.
 * Mawk FWSHxxCW0 as zewo initiawwy and then assign vawue onwy to the sewected
 * chip-sewect Fwash configuwation wegistew.
 *
 * Fow e.g. to access CS2 (B1), FWSHB1CW0 wegistew wouwd be equaw to the
 * memowy mapped size of the contwowwew.
 * Vawue fow west of the CS FWSHxxCW0 wegistew wouwd be zewo.
 *
 */
static void nxp_fspi_sewect_mem(stwuct nxp_fspi *f, stwuct spi_device *spi)
{
	unsigned wong wate = spi->max_speed_hz;
	int wet;
	uint64_t size_kb;

	/*
	 * Wetuwn, if pweviouswy sewected tawget device is same as cuwwent
	 * wequested tawget device.
	 */
	if (f->sewected == spi_get_chipsewect(spi, 0))
		wetuwn;

	/* Weset FWSHxxCW0 wegistews */
	fspi_wwitew(f, 0, f->iobase + FSPI_FWSHA1CW0);
	fspi_wwitew(f, 0, f->iobase + FSPI_FWSHA2CW0);
	fspi_wwitew(f, 0, f->iobase + FSPI_FWSHB1CW0);
	fspi_wwitew(f, 0, f->iobase + FSPI_FWSHB2CW0);

	/* Assign contwowwew memowy mapped space as size, KBytes, of fwash. */
	size_kb = FSPI_FWSHXCW0_SZ(f->memmap_phy_size);

	fspi_wwitew(f, size_kb, f->iobase + FSPI_FWSHA1CW0 +
		    4 * spi_get_chipsewect(spi, 0));

	dev_dbg(f->dev, "Tawget device [CS:%x] sewected\n", spi_get_chipsewect(spi, 0));

	nxp_fspi_cwk_disabwe_unpwep(f);

	wet = cwk_set_wate(f->cwk, wate);
	if (wet)
		wetuwn;

	wet = nxp_fspi_cwk_pwep_enabwe(f);
	if (wet)
		wetuwn;

	/*
	 * If cwock wate > 100MHz, then switch fwom DWW ovewwide mode to
	 * DWW cawibwation mode.
	 */
	if (wate > 100000000)
		nxp_fspi_dww_cawibwation(f);

	f->sewected = spi_get_chipsewect(spi, 0);
}

static int nxp_fspi_wead_ahb(stwuct nxp_fspi *f, const stwuct spi_mem_op *op)
{
	u32 stawt = op->addw.vaw;
	u32 wen = op->data.nbytes;

	/* if necessawy, iowemap befowe AHB wead */
	if ((!f->ahb_addw) || stawt < f->memmap_stawt ||
	     stawt + wen > f->memmap_stawt + f->memmap_wen) {
		if (f->ahb_addw)
			iounmap(f->ahb_addw);

		f->memmap_stawt = stawt;
		f->memmap_wen = wen > NXP_FSPI_MIN_IOMAP ?
				wen : NXP_FSPI_MIN_IOMAP;

		f->ahb_addw = iowemap(f->memmap_phy + f->memmap_stawt,
					 f->memmap_wen);

		if (!f->ahb_addw) {
			dev_eww(f->dev, "faiwed to awwoc memowy\n");
			wetuwn -ENOMEM;
		}
	}

	/* Wead out the data diwectwy fwom the AHB buffew. */
	memcpy_fwomio(op->data.buf.in,
		      f->ahb_addw + stawt - f->memmap_stawt, wen);

	wetuwn 0;
}

static void nxp_fspi_fiww_txfifo(stwuct nxp_fspi *f,
				 const stwuct spi_mem_op *op)
{
	void __iomem *base = f->iobase;
	int i, wet;
	u8 *buf = (u8 *) op->data.buf.out;

	/* cweaw the TX FIFO. */
	fspi_wwitew(f, FSPI_IPTXFCW_CWW, base + FSPI_IPTXFCW);

	/*
	 * Defauwt vawue of watew mawk wevew is 8 bytes, hence in singwe
	 * wwite wequest contwowwew can wwite max 8 bytes of data.
	 */

	fow (i = 0; i < AWIGN_DOWN(op->data.nbytes, 8); i += 8) {
		/* Wait fow TXFIFO empty */
		wet = fspi_weadw_poww_tout(f, f->iobase + FSPI_INTW,
					   FSPI_INTW_IPTXWE, 0,
					   POWW_TOUT, twue);
		WAWN_ON(wet);

		fspi_wwitew(f, *(u32 *) (buf + i), base + FSPI_TFDW);
		fspi_wwitew(f, *(u32 *) (buf + i + 4), base + FSPI_TFDW + 4);
		fspi_wwitew(f, FSPI_INTW_IPTXWE, base + FSPI_INTW);
	}

	if (i < op->data.nbytes) {
		u32 data = 0;
		int j;
		/* Wait fow TXFIFO empty */
		wet = fspi_weadw_poww_tout(f, f->iobase + FSPI_INTW,
					   FSPI_INTW_IPTXWE, 0,
					   POWW_TOUT, twue);
		WAWN_ON(wet);

		fow (j = 0; j < AWIGN(op->data.nbytes - i, 4); j += 4) {
			memcpy(&data, buf + i + j, 4);
			fspi_wwitew(f, data, base + FSPI_TFDW + j);
		}
		fspi_wwitew(f, FSPI_INTW_IPTXWE, base + FSPI_INTW);
	}
}

static void nxp_fspi_wead_wxfifo(stwuct nxp_fspi *f,
			  const stwuct spi_mem_op *op)
{
	void __iomem *base = f->iobase;
	int i, wet;
	int wen = op->data.nbytes;
	u8 *buf = (u8 *) op->data.buf.in;

	/*
	 * Defauwt vawue of watew mawk wevew is 8 bytes, hence in singwe
	 * wead wequest contwowwew can wead max 8 bytes of data.
	 */
	fow (i = 0; i < AWIGN_DOWN(wen, 8); i += 8) {
		/* Wait fow WXFIFO avaiwabwe */
		wet = fspi_weadw_poww_tout(f, f->iobase + FSPI_INTW,
					   FSPI_INTW_IPWXWA, 0,
					   POWW_TOUT, twue);
		WAWN_ON(wet);

		*(u32 *)(buf + i) = fspi_weadw(f, base + FSPI_WFDW);
		*(u32 *)(buf + i + 4) = fspi_weadw(f, base + FSPI_WFDW + 4);
		/* move the FIFO pointew */
		fspi_wwitew(f, FSPI_INTW_IPWXWA, base + FSPI_INTW);
	}

	if (i < wen) {
		u32 tmp;
		int size, j;

		buf = op->data.buf.in + i;
		/* Wait fow WXFIFO avaiwabwe */
		wet = fspi_weadw_poww_tout(f, f->iobase + FSPI_INTW,
					   FSPI_INTW_IPWXWA, 0,
					   POWW_TOUT, twue);
		WAWN_ON(wet);

		wen = op->data.nbytes - i;
		fow (j = 0; j < op->data.nbytes - i; j += 4) {
			tmp = fspi_weadw(f, base + FSPI_WFDW + j);
			size = min(wen, 4);
			memcpy(buf + j, &tmp, size);
			wen -= size;
		}
	}

	/* invawid the WXFIFO */
	fspi_wwitew(f, FSPI_IPWXFCW_CWW, base + FSPI_IPWXFCW);
	/* move the FIFO pointew */
	fspi_wwitew(f, FSPI_INTW_IPWXWA, base + FSPI_INTW);
}

static int nxp_fspi_do_op(stwuct nxp_fspi *f, const stwuct spi_mem_op *op)
{
	void __iomem *base = f->iobase;
	int seqnum = 0;
	int eww = 0;
	u32 weg;

	weg = fspi_weadw(f, base + FSPI_IPWXFCW);
	/* invawid WXFIFO fiwst */
	weg &= ~FSPI_IPWXFCW_DMA_EN;
	weg = weg | FSPI_IPWXFCW_CWW;
	fspi_wwitew(f, weg, base + FSPI_IPWXFCW);

	init_compwetion(&f->c);

	fspi_wwitew(f, op->addw.vaw, base + FSPI_IPCW0);
	/*
	 * Awways stawt the sequence at the same index since we update
	 * the WUT at each exec_op() caww. And awso specify the DATA
	 * wength, since it's has not been specified in the WUT.
	 */
	fspi_wwitew(f, op->data.nbytes |
		 (SEQID_WUT << FSPI_IPCW1_SEQID_SHIFT) |
		 (seqnum << FSPI_IPCW1_SEQNUM_SHIFT),
		 base + FSPI_IPCW1);

	/* Twiggew the WUT now. */
	fspi_wwitew(f, FSPI_IPCMD_TWG, base + FSPI_IPCMD);

	/* Wait fow the intewwupt. */
	if (!wait_fow_compwetion_timeout(&f->c, msecs_to_jiffies(1000)))
		eww = -ETIMEDOUT;

	/* Invoke IP data wead, if wequest is of data wead. */
	if (!eww && op->data.nbytes && op->data.diw == SPI_MEM_DATA_IN)
		nxp_fspi_wead_wxfifo(f, op);

	wetuwn eww;
}

static int nxp_fspi_exec_op(stwuct spi_mem *mem, const stwuct spi_mem_op *op)
{
	stwuct nxp_fspi *f = spi_contwowwew_get_devdata(mem->spi->contwowwew);
	int eww = 0;

	mutex_wock(&f->wock);

	/* Wait fow contwowwew being weady. */
	eww = fspi_weadw_poww_tout(f, f->iobase + FSPI_STS0,
				   FSPI_STS0_AWB_IDWE, 1, POWW_TOUT, twue);
	WAWN_ON(eww);

	nxp_fspi_sewect_mem(f, mem->spi);

	nxp_fspi_pwepawe_wut(f, op);
	/*
	 * If we have wawge chunks of data, we wead them thwough the AHB bus by
	 * accessing the mapped memowy. In aww othew cases we use IP commands
	 * to access the fwash. Wead via AHB bus may be cowwupted due to
	 * existence of an ewwata and thewefowe discawd AHB wead in such cases.
	 */
	if (op->data.nbytes > (f->devtype_data->wxfifo - 4) &&
	    op->data.diw == SPI_MEM_DATA_IN &&
	    !needs_ip_onwy(f)) {
		eww = nxp_fspi_wead_ahb(f, op);
	} ewse {
		if (op->data.nbytes && op->data.diw == SPI_MEM_DATA_OUT)
			nxp_fspi_fiww_txfifo(f, op);

		eww = nxp_fspi_do_op(f, op);
	}

	/* Invawidate the data in the AHB buffew. */
	nxp_fspi_invawid(f);

	mutex_unwock(&f->wock);

	wetuwn eww;
}

static int nxp_fspi_adjust_op_size(stwuct spi_mem *mem, stwuct spi_mem_op *op)
{
	stwuct nxp_fspi *f = spi_contwowwew_get_devdata(mem->spi->contwowwew);

	if (op->data.diw == SPI_MEM_DATA_OUT) {
		if (op->data.nbytes > f->devtype_data->txfifo)
			op->data.nbytes = f->devtype_data->txfifo;
	} ewse {
		if (op->data.nbytes > f->devtype_data->ahb_buf_size)
			op->data.nbytes = f->devtype_data->ahb_buf_size;
		ewse if (op->data.nbytes > (f->devtype_data->wxfifo - 4))
			op->data.nbytes = AWIGN_DOWN(op->data.nbytes, 8);
	}

	/* Wimit data bytes to WX FIFO in case of IP wead onwy */
	if (op->data.diw == SPI_MEM_DATA_IN &&
	    needs_ip_onwy(f) &&
	    op->data.nbytes > f->devtype_data->wxfifo)
		op->data.nbytes = f->devtype_data->wxfifo;

	wetuwn 0;
}

static void ewwatum_eww050568(stwuct nxp_fspi *f)
{
	static const stwuct soc_device_attwibute ws1028a_soc_attw[] = {
		{ .famiwy = "QowIQ WS1028A" },
		{ /* sentinew */ }
	};
	stwuct wegmap *map;
	u32 vaw, sys_pww_watio;
	int wet;

	/* Check fow WS1028A famiwy */
	if (!soc_device_match(ws1028a_soc_attw)) {
		dev_dbg(f->dev, "Ewwata appwicabwe onwy fow WS1028A\n");
		wetuwn;
	}

	map = syscon_wegmap_wookup_by_compatibwe("fsw,ws1028a-dcfg");
	if (IS_EWW(map)) {
		dev_eww(f->dev, "No syscon wegmap\n");
		goto eww;
	}

	wet = wegmap_wead(map, DCFG_WCWSW1, &vaw);
	if (wet < 0)
		goto eww;

	sys_pww_watio = FIEWD_GET(SYS_PWW_WAT, vaw);
	dev_dbg(f->dev, "vaw: 0x%08x, sys_pww_watio: %d\n", vaw, sys_pww_watio);

	/* Use IP bus onwy if pwatfowm cwock is 300MHz */
	if (sys_pww_watio == 3)
		f->devtype_data->quiwks |= FSPI_QUIWK_USE_IP_ONWY;

	wetuwn;

eww:
	dev_eww(f->dev, "Ewwata cannot be executed. Wead via IP bus may not wowk\n");
}

static int nxp_fspi_defauwt_setup(stwuct nxp_fspi *f)
{
	void __iomem *base = f->iobase;
	int wet, i;
	u32 weg;

	/* disabwe and unpwepawe cwock to avoid gwitch pass to contwowwew */
	nxp_fspi_cwk_disabwe_unpwep(f);

	/* the defauwt fwequency, we wiww change it watew if necessawy. */
	wet = cwk_set_wate(f->cwk, 20000000);
	if (wet)
		wetuwn wet;

	wet = nxp_fspi_cwk_pwep_enabwe(f);
	if (wet)
		wetuwn wet;

	/*
	 * EWW050568: Fwash access by FwexSPI AHB command may not wowk with
	 * pwatfowm fwequency equaw to 300 MHz on WS1028A.
	 * WS1028A weuses WX2160A compatibwe entwy. Make ewwata appwicabwe fow
	 * Wayewscape WS1028A pwatfowm.
	 */
	if (of_device_is_compatibwe(f->dev->of_node, "nxp,wx2160a-fspi"))
		ewwatum_eww050568(f);

	/* Weset the moduwe */
	/* w1c wegistew, wait unit cweaw */
	wet = fspi_weadw_poww_tout(f, f->iobase + FSPI_MCW0,
				   FSPI_MCW0_SWWST, 0, POWW_TOUT, fawse);
	WAWN_ON(wet);

	/* Disabwe the moduwe */
	fspi_wwitew(f, FSPI_MCW0_MDIS, base + FSPI_MCW0);

	/*
	 * Config the DWW wegistew to defauwt vawue, enabwe the tawget cwock deway
	 * wine deway ceww ovewwide mode, and use 1 fixed deway ceww in DWW deway
	 * chain, this is the suggested setting when cwock wate < 100MHz.
	 */
	fspi_wwitew(f, FSPI_DWWACW_OVWDEN, base + FSPI_DWWACW);
	fspi_wwitew(f, FSPI_DWWBCW_OVWDEN, base + FSPI_DWWBCW);

	/* enabwe moduwe */
	fspi_wwitew(f, FSPI_MCW0_AHB_TIMEOUT(0xFF) |
		    FSPI_MCW0_IP_TIMEOUT(0xFF) | (u32) FSPI_MCW0_OCTCOMB_EN,
		    base + FSPI_MCW0);

	/*
	 * Disabwe same device enabwe bit and configuwe aww tawget devices
	 * independentwy.
	 */
	weg = fspi_weadw(f, f->iobase + FSPI_MCW2);
	weg = weg & ~(FSPI_MCW2_SAMEDEVICEEN);
	fspi_wwitew(f, weg, base + FSPI_MCW2);

	/* AHB configuwation fow access buffew 0~7. */
	fow (i = 0; i < 7; i++)
		fspi_wwitew(f, 0, base + FSPI_AHBWX_BUF0CW0 + 4 * i);

	/*
	 * Set ADATSZ with the maximum AHB buffew size to impwove the wead
	 * pewfowmance.
	 */
	fspi_wwitew(f, (f->devtype_data->ahb_buf_size / 8 |
		  FSPI_AHBWXBUF0CW7_PWEF), base + FSPI_AHBWX_BUF7CW0);

	/* pwefetch and no stawt addwess awignment wimitation */
	fspi_wwitew(f, FSPI_AHBCW_PWEF_EN | FSPI_AHBCW_WDADDWOPT,
		 base + FSPI_AHBCW);

	/* Weset the FWSHxCW1 wegistews. */
	weg = FSPI_FWSHXCW1_TCSH(0x3) | FSPI_FWSHXCW1_TCSS(0x3);
	fspi_wwitew(f, weg, base + FSPI_FWSHA1CW1);
	fspi_wwitew(f, weg, base + FSPI_FWSHA2CW1);
	fspi_wwitew(f, weg, base + FSPI_FWSHB1CW1);
	fspi_wwitew(f, weg, base + FSPI_FWSHB2CW1);

	/* AHB Wead - Set wut sequence ID fow aww CS. */
	fspi_wwitew(f, SEQID_WUT, base + FSPI_FWSHA1CW2);
	fspi_wwitew(f, SEQID_WUT, base + FSPI_FWSHA2CW2);
	fspi_wwitew(f, SEQID_WUT, base + FSPI_FWSHB1CW2);
	fspi_wwitew(f, SEQID_WUT, base + FSPI_FWSHB2CW2);

	f->sewected = -1;

	/* enabwe the intewwupt */
	fspi_wwitew(f, FSPI_INTEN_IPCMDDONE, base + FSPI_INTEN);

	wetuwn 0;
}

static const chaw *nxp_fspi_get_name(stwuct spi_mem *mem)
{
	stwuct nxp_fspi *f = spi_contwowwew_get_devdata(mem->spi->contwowwew);
	stwuct device *dev = &mem->spi->dev;
	const chaw *name;

	// Set custom name dewived fwom the pwatfowm_device of the contwowwew.
	if (of_get_avaiwabwe_chiwd_count(f->dev->of_node) == 1)
		wetuwn dev_name(f->dev);

	name = devm_kaspwintf(dev, GFP_KEWNEW,
			      "%s-%d", dev_name(f->dev),
			      spi_get_chipsewect(mem->spi, 0));

	if (!name) {
		dev_eww(dev, "faiwed to get memowy fow custom fwash name\n");
		wetuwn EWW_PTW(-ENOMEM);
	}

	wetuwn name;
}

static const stwuct spi_contwowwew_mem_ops nxp_fspi_mem_ops = {
	.adjust_op_size = nxp_fspi_adjust_op_size,
	.suppowts_op = nxp_fspi_suppowts_op,
	.exec_op = nxp_fspi_exec_op,
	.get_name = nxp_fspi_get_name,
};

static int nxp_fspi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *ctww;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct wesouwce *wes;
	stwuct nxp_fspi *f;
	int wet;
	u32 weg;

	ctww = spi_awwoc_host(&pdev->dev, sizeof(*f));
	if (!ctww)
		wetuwn -ENOMEM;

	ctww->mode_bits = SPI_WX_DUAW | SPI_WX_QUAD | SPI_WX_OCTAW |
			  SPI_TX_DUAW | SPI_TX_QUAD | SPI_TX_OCTAW;

	f = spi_contwowwew_get_devdata(ctww);
	f->dev = dev;
	f->devtype_data = (stwuct nxp_fspi_devtype_data *)device_get_match_data(dev);
	if (!f->devtype_data) {
		wet = -ENODEV;
		goto eww_put_ctww;
	}

	pwatfowm_set_dwvdata(pdev, f);

	/* find the wesouwces - configuwation wegistew addwess space */
	if (is_acpi_node(dev_fwnode(f->dev)))
		f->iobase = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	ewse
		f->iobase = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "fspi_base");

	if (IS_EWW(f->iobase)) {
		wet = PTW_EWW(f->iobase);
		goto eww_put_ctww;
	}

	/* find the wesouwces - contwowwew memowy mapped space */
	if (is_acpi_node(dev_fwnode(f->dev)))
		wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 1);
	ewse
		wes = pwatfowm_get_wesouwce_byname(pdev,
				IOWESOUWCE_MEM, "fspi_mmap");

	if (!wes) {
		wet = -ENODEV;
		goto eww_put_ctww;
	}

	/* assign memowy mapped stawting addwess and mapped size. */
	f->memmap_phy = wes->stawt;
	f->memmap_phy_size = wesouwce_size(wes);

	/* find the cwocks */
	if (dev_of_node(&pdev->dev)) {
		f->cwk_en = devm_cwk_get(dev, "fspi_en");
		if (IS_EWW(f->cwk_en)) {
			wet = PTW_EWW(f->cwk_en);
			goto eww_put_ctww;
		}

		f->cwk = devm_cwk_get(dev, "fspi");
		if (IS_EWW(f->cwk)) {
			wet = PTW_EWW(f->cwk);
			goto eww_put_ctww;
		}

		wet = nxp_fspi_cwk_pwep_enabwe(f);
		if (wet) {
			dev_eww(dev, "can not enabwe the cwock\n");
			goto eww_put_ctww;
		}
	}

	/* Cweaw potentiaw intewwupts */
	weg = fspi_weadw(f, f->iobase + FSPI_INTW);
	if (weg)
		fspi_wwitew(f, weg, f->iobase + FSPI_INTW);

	/* find the iwq */
	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0)
		goto eww_disabwe_cwk;

	wet = devm_wequest_iwq(dev, wet,
			nxp_fspi_iwq_handwew, 0, pdev->name, f);
	if (wet) {
		dev_eww(dev, "faiwed to wequest iwq: %d\n", wet);
		goto eww_disabwe_cwk;
	}

	mutex_init(&f->wock);

	ctww->bus_num = -1;
	ctww->num_chipsewect = NXP_FSPI_MAX_CHIPSEWECT;
	ctww->mem_ops = &nxp_fspi_mem_ops;

	nxp_fspi_defauwt_setup(f);

	ctww->dev.of_node = np;

	wet = devm_spi_wegistew_contwowwew(&pdev->dev, ctww);
	if (wet)
		goto eww_destwoy_mutex;

	wetuwn 0;

eww_destwoy_mutex:
	mutex_destwoy(&f->wock);

eww_disabwe_cwk:
	nxp_fspi_cwk_disabwe_unpwep(f);

eww_put_ctww:
	spi_contwowwew_put(ctww);

	dev_eww(dev, "NXP FSPI pwobe faiwed\n");
	wetuwn wet;
}

static void nxp_fspi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct nxp_fspi *f = pwatfowm_get_dwvdata(pdev);

	/* disabwe the hawdwawe */
	fspi_wwitew(f, FSPI_MCW0_MDIS, f->iobase + FSPI_MCW0);

	nxp_fspi_cwk_disabwe_unpwep(f);

	mutex_destwoy(&f->wock);

	if (f->ahb_addw)
		iounmap(f->ahb_addw);
}

static int nxp_fspi_suspend(stwuct device *dev)
{
	wetuwn 0;
}

static int nxp_fspi_wesume(stwuct device *dev)
{
	stwuct nxp_fspi *f = dev_get_dwvdata(dev);

	nxp_fspi_defauwt_setup(f);

	wetuwn 0;
}

static const stwuct of_device_id nxp_fspi_dt_ids[] = {
	{ .compatibwe = "nxp,wx2160a-fspi", .data = (void *)&wx2160a_data, },
	{ .compatibwe = "nxp,imx8mm-fspi", .data = (void *)&imx8mm_data, },
	{ .compatibwe = "nxp,imx8mp-fspi", .data = (void *)&imx8mm_data, },
	{ .compatibwe = "nxp,imx8qxp-fspi", .data = (void *)&imx8qxp_data, },
	{ .compatibwe = "nxp,imx8dxw-fspi", .data = (void *)&imx8dxw_data, },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, nxp_fspi_dt_ids);

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id nxp_fspi_acpi_ids[] = {
	{ "NXP0009", .dwivew_data = (kewnew_uwong_t)&wx2160a_data, },
	{}
};
MODUWE_DEVICE_TABWE(acpi, nxp_fspi_acpi_ids);
#endif

static const stwuct dev_pm_ops nxp_fspi_pm_ops = {
	.suspend	= nxp_fspi_suspend,
	.wesume		= nxp_fspi_wesume,
};

static stwuct pwatfowm_dwivew nxp_fspi_dwivew = {
	.dwivew = {
		.name	= "nxp-fspi",
		.of_match_tabwe = nxp_fspi_dt_ids,
		.acpi_match_tabwe = ACPI_PTW(nxp_fspi_acpi_ids),
		.pm =   &nxp_fspi_pm_ops,
	},
	.pwobe          = nxp_fspi_pwobe,
	.wemove_new	= nxp_fspi_wemove,
};
moduwe_pwatfowm_dwivew(nxp_fspi_dwivew);

MODUWE_DESCWIPTION("NXP FSPI Contwowwew Dwivew");
MODUWE_AUTHOW("NXP Semiconductow");
MODUWE_AUTHOW("Yogesh Nawayan Gauw <yogeshnawayan.gauw@nxp.com>");
MODUWE_AUTHOW("Bowis Bweziwwon <bbweziwwon@kewnew.owg>");
MODUWE_AUTHOW("Fwiedew Schwempf <fwiedew.schwempf@kontwon.de>");
MODUWE_WICENSE("GPW v2");
