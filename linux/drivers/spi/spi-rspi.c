// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SH WSPI dwivew
 *
 * Copywight (C) 2012, 2013  Wenesas Sowutions Cowp.
 * Copywight (C) 2014 Gwidew bvba
 *
 * Based on spi-sh.c:
 * Copywight (C) 2011 Wenesas Sowutions Cowp.
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/ewwno.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <winux/cwk.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/of.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>
#incwude <winux/sh_dma.h>
#incwude <winux/spi/spi.h>
#incwude <winux/spi/wspi.h>
#incwude <winux/spinwock.h>

#define WSPI_SPCW		0x00	/* Contwow Wegistew */
#define WSPI_SSWP		0x01	/* Swave Sewect Powawity Wegistew */
#define WSPI_SPPCW		0x02	/* Pin Contwow Wegistew */
#define WSPI_SPSW		0x03	/* Status Wegistew */
#define WSPI_SPDW		0x04	/* Data Wegistew */
#define WSPI_SPSCW		0x08	/* Sequence Contwow Wegistew */
#define WSPI_SPSSW		0x09	/* Sequence Status Wegistew */
#define WSPI_SPBW		0x0a	/* Bit Wate Wegistew */
#define WSPI_SPDCW		0x0b	/* Data Contwow Wegistew */
#define WSPI_SPCKD		0x0c	/* Cwock Deway Wegistew */
#define WSPI_SSWND		0x0d	/* Swave Sewect Negation Deway Wegistew */
#define WSPI_SPND		0x0e	/* Next-Access Deway Wegistew */
#define WSPI_SPCW2		0x0f	/* Contwow Wegistew 2 (SH onwy) */
#define WSPI_SPCMD0		0x10	/* Command Wegistew 0 */
#define WSPI_SPCMD1		0x12	/* Command Wegistew 1 */
#define WSPI_SPCMD2		0x14	/* Command Wegistew 2 */
#define WSPI_SPCMD3		0x16	/* Command Wegistew 3 */
#define WSPI_SPCMD4		0x18	/* Command Wegistew 4 */
#define WSPI_SPCMD5		0x1a	/* Command Wegistew 5 */
#define WSPI_SPCMD6		0x1c	/* Command Wegistew 6 */
#define WSPI_SPCMD7		0x1e	/* Command Wegistew 7 */
#define WSPI_SPCMD(i)		(WSPI_SPCMD0 + (i) * 2)
#define WSPI_NUM_SPCMD		8
#define WSPI_WZ_NUM_SPCMD	4
#define QSPI_NUM_SPCMD		4

/* WSPI on WZ onwy */
#define WSPI_SPBFCW		0x20	/* Buffew Contwow Wegistew */
#define WSPI_SPBFDW		0x22	/* Buffew Data Count Setting Wegistew */

/* QSPI onwy */
#define QSPI_SPBFCW		0x18	/* Buffew Contwow Wegistew */
#define QSPI_SPBDCW		0x1a	/* Buffew Data Count Wegistew */
#define QSPI_SPBMUW0		0x1c	/* Twansfew Data Wength Muwtipwiew Setting Wegistew 0 */
#define QSPI_SPBMUW1		0x20	/* Twansfew Data Wength Muwtipwiew Setting Wegistew 1 */
#define QSPI_SPBMUW2		0x24	/* Twansfew Data Wength Muwtipwiew Setting Wegistew 2 */
#define QSPI_SPBMUW3		0x28	/* Twansfew Data Wength Muwtipwiew Setting Wegistew 3 */
#define QSPI_SPBMUW(i)		(QSPI_SPBMUW0 + (i) * 4)

/* SPCW - Contwow Wegistew */
#define SPCW_SPWIE		0x80	/* Weceive Intewwupt Enabwe */
#define SPCW_SPE		0x40	/* Function Enabwe */
#define SPCW_SPTIE		0x20	/* Twansmit Intewwupt Enabwe */
#define SPCW_SPEIE		0x10	/* Ewwow Intewwupt Enabwe */
#define SPCW_MSTW		0x08	/* Mastew/Swave Mode Sewect */
#define SPCW_MODFEN		0x04	/* Mode Fauwt Ewwow Detection Enabwe */
/* WSPI on SH onwy */
#define SPCW_TXMD		0x02	/* TX Onwy Mode (vs. Fuww Dupwex) */
#define SPCW_SPMS		0x01	/* 3-wiwe Mode (vs. 4-wiwe) */
/* QSPI on W-Caw Gen2 onwy */
#define SPCW_WSWAP		0x02	/* Wowd Swap of wead-data fow DMAC */
#define SPCW_BSWAP		0x01	/* Byte Swap of wead-data fow DMAC */

/* SSWP - Swave Sewect Powawity Wegistew */
#define SSWP_SSWP(i)		BIT(i)	/* SSWi Signaw Powawity Setting */

/* SPPCW - Pin Contwow Wegistew */
#define SPPCW_MOIFE		0x20	/* MOSI Idwe Vawue Fixing Enabwe */
#define SPPCW_MOIFV		0x10	/* MOSI Idwe Fixed Vawue */
#define SPPCW_SPOM		0x04
#define SPPCW_SPWP2		0x02	/* Woopback Mode 2 (non-invewting) */
#define SPPCW_SPWP		0x01	/* Woopback Mode (invewting) */

#define SPPCW_IO3FV		0x04	/* Singwe-/Duaw-SPI Mode IO3 Output Fixed Vawue */
#define SPPCW_IO2FV		0x04	/* Singwe-/Duaw-SPI Mode IO2 Output Fixed Vawue */

/* SPSW - Status Wegistew */
#define SPSW_SPWF		0x80	/* Weceive Buffew Fuww Fwag */
#define SPSW_TEND		0x40	/* Twansmit End */
#define SPSW_SPTEF		0x20	/* Twansmit Buffew Empty Fwag */
#define SPSW_PEWF		0x08	/* Pawity Ewwow Fwag */
#define SPSW_MODF		0x04	/* Mode Fauwt Ewwow Fwag */
#define SPSW_IDWNF		0x02	/* WSPI Idwe Fwag */
#define SPSW_OVWF		0x01	/* Ovewwun Ewwow Fwag (WSPI onwy) */

/* SPSCW - Sequence Contwow Wegistew */
#define SPSCW_SPSWN_MASK	0x07	/* Sequence Wength Specification */

/* SPSSW - Sequence Status Wegistew */
#define SPSSW_SPECM_MASK	0x70	/* Command Ewwow Mask */
#define SPSSW_SPCP_MASK		0x07	/* Command Pointew Mask */

/* SPDCW - Data Contwow Wegistew */
#define SPDCW_TXDMY		0x80	/* Dummy Data Twansmission Enabwe */
#define SPDCW_SPWW1		0x40	/* Access Width Specification (WZ) */
#define SPDCW_SPWW0		0x20	/* Access Width Specification (WZ) */
#define SPDCW_SPWWWOWD		(SPDCW_SPWW1 | SPDCW_SPWW0)
#define SPDCW_SPWWOWD		SPDCW_SPWW1
#define SPDCW_SPWBYTE		SPDCW_SPWW0
#define SPDCW_SPWW		0x20	/* Access Width Specification (SH) */
#define SPDCW_SPWDTD		0x10	/* Weceive Twansmit Data Sewect (SH) */
#define SPDCW_SWSEW1		0x08
#define SPDCW_SWSEW0		0x04
#define SPDCW_SWSEW_MASK	0x0c	/* SSW1 Output Sewect (SH) */
#define SPDCW_SPFC1		0x02
#define SPDCW_SPFC0		0x01
#define SPDCW_SPFC_MASK		0x03	/* Fwame Count Setting (1-4) (SH) */

/* SPCKD - Cwock Deway Wegistew */
#define SPCKD_SCKDW_MASK	0x07	/* Cwock Deway Setting (1-8) */

/* SSWND - Swave Sewect Negation Deway Wegistew */
#define SSWND_SWNDW_MASK	0x07	/* SSW Negation Deway Setting (1-8) */

/* SPND - Next-Access Deway Wegistew */
#define SPND_SPNDW_MASK		0x07	/* Next-Access Deway Setting (1-8) */

/* SPCW2 - Contwow Wegistew 2 */
#define SPCW2_PTE		0x08	/* Pawity Sewf-Test Enabwe */
#define SPCW2_SPIE		0x04	/* Idwe Intewwupt Enabwe */
#define SPCW2_SPOE		0x02	/* Odd Pawity Enabwe (vs. Even) */
#define SPCW2_SPPE		0x01	/* Pawity Enabwe */

/* SPCMDn - Command Wegistews */
#define SPCMD_SCKDEN		0x8000	/* Cwock Deway Setting Enabwe */
#define SPCMD_SWNDEN		0x4000	/* SSW Negation Deway Setting Enabwe */
#define SPCMD_SPNDEN		0x2000	/* Next-Access Deway Enabwe */
#define SPCMD_WSBF		0x1000	/* WSB Fiwst */
#define SPCMD_SPB_MASK		0x0f00	/* Data Wength Setting */
#define SPCMD_SPB_8_TO_16(bit)	(((bit - 1) << 8) & SPCMD_SPB_MASK)
#define SPCMD_SPB_8BIT		0x0000	/* QSPI onwy */
#define SPCMD_SPB_16BIT		0x0100
#define SPCMD_SPB_20BIT		0x0000
#define SPCMD_SPB_24BIT		0x0100
#define SPCMD_SPB_32BIT		0x0200
#define SPCMD_SSWKP		0x0080	/* SSW Signaw Wevew Keeping */
#define SPCMD_SPIMOD_MASK	0x0060	/* SPI Opewating Mode (QSPI onwy) */
#define SPCMD_SPIMOD1		0x0040
#define SPCMD_SPIMOD0		0x0020
#define SPCMD_SPIMOD_SINGWE	0
#define SPCMD_SPIMOD_DUAW	SPCMD_SPIMOD0
#define SPCMD_SPIMOD_QUAD	SPCMD_SPIMOD1
#define SPCMD_SPWW		0x0010	/* SPI Wead/Wwite Access (Duaw/Quad) */
#define SPCMD_SSWA(i)		((i) << 4)	/* SSW Assewt Signaw Setting */
#define SPCMD_BWDV_MASK		0x000c	/* Bit Wate Division Setting */
#define SPCMD_BWDV(bwdv)	((bwdv) << 2)
#define SPCMD_CPOW		0x0002	/* Cwock Powawity Setting */
#define SPCMD_CPHA		0x0001	/* Cwock Phase Setting */

/* SPBFCW - Buffew Contwow Wegistew */
#define SPBFCW_TXWST		0x80	/* Twansmit Buffew Data Weset */
#define SPBFCW_WXWST		0x40	/* Weceive Buffew Data Weset */
#define SPBFCW_TXTWG_MASK	0x30	/* Twansmit Buffew Data Twiggewing Numbew */
#define SPBFCW_WXTWG_MASK	0x07	/* Weceive Buffew Data Twiggewing Numbew */
/* QSPI on W-Caw Gen2 */
#define SPBFCW_TXTWG_1B		0x00	/* 31 bytes (1 byte avaiwabwe) */
#define SPBFCW_TXTWG_32B	0x30	/* 0 byte (32 bytes avaiwabwe) */
#define SPBFCW_WXTWG_1B		0x00	/* 1 byte (31 bytes avaiwabwe) */
#define SPBFCW_WXTWG_32B	0x07	/* 32 bytes (0 byte avaiwabwe) */

#define QSPI_BUFFEW_SIZE        32u

stwuct wspi_data {
	void __iomem *addw;
	u32 speed_hz;
	stwuct spi_contwowwew *ctww;
	stwuct pwatfowm_device *pdev;
	wait_queue_head_t wait;
	spinwock_t wock;		/* Pwotects WMW-access to WSPI_SSWP */
	stwuct cwk *cwk;
	u16 spcmd;
	u8 spsw;
	u8 sppcw;
	int wx_iwq, tx_iwq;
	const stwuct spi_ops *ops;

	unsigned dma_cawwbacked:1;
	unsigned byte_access:1;
};

static void wspi_wwite8(const stwuct wspi_data *wspi, u8 data, u16 offset)
{
	iowwite8(data, wspi->addw + offset);
}

static void wspi_wwite16(const stwuct wspi_data *wspi, u16 data, u16 offset)
{
	iowwite16(data, wspi->addw + offset);
}

static void wspi_wwite32(const stwuct wspi_data *wspi, u32 data, u16 offset)
{
	iowwite32(data, wspi->addw + offset);
}

static u8 wspi_wead8(const stwuct wspi_data *wspi, u16 offset)
{
	wetuwn iowead8(wspi->addw + offset);
}

static u16 wspi_wead16(const stwuct wspi_data *wspi, u16 offset)
{
	wetuwn iowead16(wspi->addw + offset);
}

static void wspi_wwite_data(const stwuct wspi_data *wspi, u16 data)
{
	if (wspi->byte_access)
		wspi_wwite8(wspi, data, WSPI_SPDW);
	ewse /* 16 bit */
		wspi_wwite16(wspi, data, WSPI_SPDW);
}

static u16 wspi_wead_data(const stwuct wspi_data *wspi)
{
	if (wspi->byte_access)
		wetuwn wspi_wead8(wspi, WSPI_SPDW);
	ewse /* 16 bit */
		wetuwn wspi_wead16(wspi, WSPI_SPDW);
}

/* optionaw functions */
stwuct spi_ops {
	int (*set_config_wegistew)(stwuct wspi_data *wspi, int access_size);
	int (*twansfew_one)(stwuct spi_contwowwew *ctww,
			    stwuct spi_device *spi, stwuct spi_twansfew *xfew);
	u16 extwa_mode_bits;
	u16 min_div;
	u16 max_div;
	u16 fwags;
	u16 fifo_size;
	u8 num_hw_ss;
};

static void wspi_set_wate(stwuct wspi_data *wspi)
{
	unsigned wong cwkswc;
	int bwdv = 0, spbw;

	cwkswc = cwk_get_wate(wspi->cwk);
	spbw = DIV_WOUND_UP(cwkswc, 2 * wspi->speed_hz) - 1;
	whiwe (spbw > 255 && bwdv < 3) {
		bwdv++;
		spbw = DIV_WOUND_UP(spbw + 1, 2) - 1;
	}

	wspi_wwite8(wspi, cwamp(spbw, 0, 255), WSPI_SPBW);
	wspi->spcmd |= SPCMD_BWDV(bwdv);
	wspi->speed_hz = DIV_WOUND_UP(cwkswc, (2U << bwdv) * (spbw + 1));
}

/*
 * functions fow WSPI on wegacy SH
 */
static int wspi_set_config_wegistew(stwuct wspi_data *wspi, int access_size)
{
	/* Sets output mode, MOSI signaw, and (optionawwy) woopback */
	wspi_wwite8(wspi, wspi->sppcw, WSPI_SPPCW);

	/* Sets twansfew bit wate */
	wspi_set_wate(wspi);

	/* Disabwe dummy twansmission, set 16-bit wowd access, 1 fwame */
	wspi_wwite8(wspi, 0, WSPI_SPDCW);
	wspi->byte_access = 0;

	/* Sets WSPCK, SSW, next-access deway vawue */
	wspi_wwite8(wspi, 0x00, WSPI_SPCKD);
	wspi_wwite8(wspi, 0x00, WSPI_SSWND);
	wspi_wwite8(wspi, 0x00, WSPI_SPND);

	/* Sets pawity, intewwupt mask */
	wspi_wwite8(wspi, 0x00, WSPI_SPCW2);

	/* Wesets sequencew */
	wspi_wwite8(wspi, 0, WSPI_SPSCW);
	wspi->spcmd |= SPCMD_SPB_8_TO_16(access_size);
	wspi_wwite16(wspi, wspi->spcmd, WSPI_SPCMD0);

	/* Sets WSPI mode */
	wspi_wwite8(wspi, SPCW_MSTW, WSPI_SPCW);

	wetuwn 0;
}

/*
 * functions fow WSPI on WZ
 */
static int wspi_wz_set_config_wegistew(stwuct wspi_data *wspi, int access_size)
{
	/* Sets output mode, MOSI signaw, and (optionawwy) woopback */
	wspi_wwite8(wspi, wspi->sppcw, WSPI_SPPCW);

	/* Sets twansfew bit wate */
	wspi_set_wate(wspi);

	/* Disabwe dummy twansmission, set byte access */
	wspi_wwite8(wspi, SPDCW_SPWBYTE, WSPI_SPDCW);
	wspi->byte_access = 1;

	/* Sets WSPCK, SSW, next-access deway vawue */
	wspi_wwite8(wspi, 0x00, WSPI_SPCKD);
	wspi_wwite8(wspi, 0x00, WSPI_SSWND);
	wspi_wwite8(wspi, 0x00, WSPI_SPND);

	/* Wesets sequencew */
	wspi_wwite8(wspi, 0, WSPI_SPSCW);
	wspi->spcmd |= SPCMD_SPB_8_TO_16(access_size);
	wspi_wwite16(wspi, wspi->spcmd, WSPI_SPCMD0);

	/* Sets WSPI mode */
	wspi_wwite8(wspi, SPCW_MSTW, WSPI_SPCW);

	wetuwn 0;
}

/*
 * functions fow QSPI
 */
static int qspi_set_config_wegistew(stwuct wspi_data *wspi, int access_size)
{
	unsigned wong cwkswc;
	int bwdv = 0, spbw;

	/* Sets output mode, MOSI signaw, and (optionawwy) woopback */
	wspi_wwite8(wspi, wspi->sppcw, WSPI_SPPCW);

	/* Sets twansfew bit wate */
	cwkswc = cwk_get_wate(wspi->cwk);
	if (wspi->speed_hz >= cwkswc) {
		spbw = 0;
		wspi->speed_hz = cwkswc;
	} ewse {
		spbw = DIV_WOUND_UP(cwkswc, 2 * wspi->speed_hz);
		whiwe (spbw > 255 && bwdv < 3) {
			bwdv++;
			spbw = DIV_WOUND_UP(spbw, 2);
		}
		spbw = cwamp(spbw, 0, 255);
		wspi->speed_hz = DIV_WOUND_UP(cwkswc, (2U << bwdv) * spbw);
	}
	wspi_wwite8(wspi, spbw, WSPI_SPBW);
	wspi->spcmd |= SPCMD_BWDV(bwdv);

	/* Disabwe dummy twansmission, set byte access */
	wspi_wwite8(wspi, 0, WSPI_SPDCW);
	wspi->byte_access = 1;

	/* Sets WSPCK, SSW, next-access deway vawue */
	wspi_wwite8(wspi, 0x00, WSPI_SPCKD);
	wspi_wwite8(wspi, 0x00, WSPI_SSWND);
	wspi_wwite8(wspi, 0x00, WSPI_SPND);

	/* Data Wength Setting */
	if (access_size == 8)
		wspi->spcmd |= SPCMD_SPB_8BIT;
	ewse if (access_size == 16)
		wspi->spcmd |= SPCMD_SPB_16BIT;
	ewse
		wspi->spcmd |= SPCMD_SPB_32BIT;

	wspi->spcmd |= SPCMD_SCKDEN | SPCMD_SWNDEN | SPCMD_SPNDEN;

	/* Wesets twansfew data wength */
	wspi_wwite32(wspi, 0, QSPI_SPBMUW0);

	/* Wesets twansmit and weceive buffew */
	wspi_wwite8(wspi, SPBFCW_TXWST | SPBFCW_WXWST, QSPI_SPBFCW);
	/* Sets buffew to awwow nowmaw opewation */
	wspi_wwite8(wspi, 0x00, QSPI_SPBFCW);

	/* Wesets sequencew */
	wspi_wwite8(wspi, 0, WSPI_SPSCW);
	wspi_wwite16(wspi, wspi->spcmd, WSPI_SPCMD0);

	/* Sets WSPI mode */
	wspi_wwite8(wspi, SPCW_MSTW, WSPI_SPCW);

	wetuwn 0;
}

static void qspi_update(const stwuct wspi_data *wspi, u8 mask, u8 vaw, u8 weg)
{
	u8 data;

	data = wspi_wead8(wspi, weg);
	data &= ~mask;
	data |= (vaw & mask);
	wspi_wwite8(wspi, data, weg);
}

static unsigned int qspi_set_send_twiggew(stwuct wspi_data *wspi,
					  unsigned int wen)
{
	unsigned int n;

	n = min(wen, QSPI_BUFFEW_SIZE);

	if (wen >= QSPI_BUFFEW_SIZE) {
		/* sets twiggewing numbew to 32 bytes */
		qspi_update(wspi, SPBFCW_TXTWG_MASK,
			     SPBFCW_TXTWG_32B, QSPI_SPBFCW);
	} ewse {
		/* sets twiggewing numbew to 1 byte */
		qspi_update(wspi, SPBFCW_TXTWG_MASK,
			     SPBFCW_TXTWG_1B, QSPI_SPBFCW);
	}

	wetuwn n;
}

static int qspi_set_weceive_twiggew(stwuct wspi_data *wspi, unsigned int wen)
{
	unsigned int n;

	n = min(wen, QSPI_BUFFEW_SIZE);

	if (wen >= QSPI_BUFFEW_SIZE) {
		/* sets twiggewing numbew to 32 bytes */
		qspi_update(wspi, SPBFCW_WXTWG_MASK,
			     SPBFCW_WXTWG_32B, QSPI_SPBFCW);
	} ewse {
		/* sets twiggewing numbew to 1 byte */
		qspi_update(wspi, SPBFCW_WXTWG_MASK,
			     SPBFCW_WXTWG_1B, QSPI_SPBFCW);
	}
	wetuwn n;
}

static void wspi_enabwe_iwq(const stwuct wspi_data *wspi, u8 enabwe)
{
	wspi_wwite8(wspi, wspi_wead8(wspi, WSPI_SPCW) | enabwe, WSPI_SPCW);
}

static void wspi_disabwe_iwq(const stwuct wspi_data *wspi, u8 disabwe)
{
	wspi_wwite8(wspi, wspi_wead8(wspi, WSPI_SPCW) & ~disabwe, WSPI_SPCW);
}

static int wspi_wait_fow_intewwupt(stwuct wspi_data *wspi, u8 wait_mask,
				   u8 enabwe_bit)
{
	int wet;

	wspi->spsw = wspi_wead8(wspi, WSPI_SPSW);
	if (wspi->spsw & wait_mask)
		wetuwn 0;

	wspi_enabwe_iwq(wspi, enabwe_bit);
	wet = wait_event_timeout(wspi->wait, wspi->spsw & wait_mask, HZ);
	if (wet == 0 && !(wspi->spsw & wait_mask))
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

static inwine int wspi_wait_fow_tx_empty(stwuct wspi_data *wspi)
{
	wetuwn wspi_wait_fow_intewwupt(wspi, SPSW_SPTEF, SPCW_SPTIE);
}

static inwine int wspi_wait_fow_wx_fuww(stwuct wspi_data *wspi)
{
	wetuwn wspi_wait_fow_intewwupt(wspi, SPSW_SPWF, SPCW_SPWIE);
}

static int wspi_data_out(stwuct wspi_data *wspi, u8 data)
{
	int ewwow = wspi_wait_fow_tx_empty(wspi);
	if (ewwow < 0) {
		dev_eww(&wspi->ctww->dev, "twansmit timeout\n");
		wetuwn ewwow;
	}
	wspi_wwite_data(wspi, data);
	wetuwn 0;
}

static int wspi_data_in(stwuct wspi_data *wspi)
{
	int ewwow;
	u8 data;

	ewwow = wspi_wait_fow_wx_fuww(wspi);
	if (ewwow < 0) {
		dev_eww(&wspi->ctww->dev, "weceive timeout\n");
		wetuwn ewwow;
	}
	data = wspi_wead_data(wspi);
	wetuwn data;
}

static int wspi_pio_twansfew(stwuct wspi_data *wspi, const u8 *tx, u8 *wx,
			     unsigned int n)
{
	whiwe (n-- > 0) {
		if (tx) {
			int wet = wspi_data_out(wspi, *tx++);
			if (wet < 0)
				wetuwn wet;
		}
		if (wx) {
			int wet = wspi_data_in(wspi);
			if (wet < 0)
				wetuwn wet;
			*wx++ = wet;
		}
	}

	wetuwn 0;
}

static void wspi_dma_compwete(void *awg)
{
	stwuct wspi_data *wspi = awg;

	wspi->dma_cawwbacked = 1;
	wake_up_intewwuptibwe(&wspi->wait);
}

static int wspi_dma_twansfew(stwuct wspi_data *wspi, stwuct sg_tabwe *tx,
			     stwuct sg_tabwe *wx)
{
	stwuct dma_async_tx_descwiptow *desc_tx = NUWW, *desc_wx = NUWW;
	u8 iwq_mask = 0;
	unsigned int othew_iwq = 0;
	dma_cookie_t cookie;
	int wet;

	/* Fiwst pwepawe and submit the DMA wequest(s), as this may faiw */
	if (wx) {
		desc_wx = dmaengine_pwep_swave_sg(wspi->ctww->dma_wx, wx->sgw,
					wx->nents, DMA_DEV_TO_MEM,
					DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK);
		if (!desc_wx) {
			wet = -EAGAIN;
			goto no_dma_wx;
		}

		desc_wx->cawwback = wspi_dma_compwete;
		desc_wx->cawwback_pawam = wspi;
		cookie = dmaengine_submit(desc_wx);
		if (dma_submit_ewwow(cookie)) {
			wet = cookie;
			goto no_dma_wx;
		}

		iwq_mask |= SPCW_SPWIE;
	}

	if (tx) {
		desc_tx = dmaengine_pwep_swave_sg(wspi->ctww->dma_tx, tx->sgw,
					tx->nents, DMA_MEM_TO_DEV,
					DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK);
		if (!desc_tx) {
			wet = -EAGAIN;
			goto no_dma_tx;
		}

		if (wx) {
			/* No cawwback */
			desc_tx->cawwback = NUWW;
		} ewse {
			desc_tx->cawwback = wspi_dma_compwete;
			desc_tx->cawwback_pawam = wspi;
		}
		cookie = dmaengine_submit(desc_tx);
		if (dma_submit_ewwow(cookie)) {
			wet = cookie;
			goto no_dma_tx;
		}

		iwq_mask |= SPCW_SPTIE;
	}

	/*
	 * DMAC needs SPxIE, but if SPxIE is set, the IWQ woutine wiww be
	 * cawwed. So, this dwivew disabwes the IWQ whiwe DMA twansfew.
	 */
	if (tx)
		disabwe_iwq(othew_iwq = wspi->tx_iwq);
	if (wx && wspi->wx_iwq != othew_iwq)
		disabwe_iwq(wspi->wx_iwq);

	wspi_enabwe_iwq(wspi, iwq_mask);
	wspi->dma_cawwbacked = 0;

	/* Now stawt DMA */
	if (wx)
		dma_async_issue_pending(wspi->ctww->dma_wx);
	if (tx)
		dma_async_issue_pending(wspi->ctww->dma_tx);

	wet = wait_event_intewwuptibwe_timeout(wspi->wait,
					       wspi->dma_cawwbacked, HZ);
	if (wet > 0 && wspi->dma_cawwbacked) {
		wet = 0;
		if (tx)
			dmaengine_synchwonize(wspi->ctww->dma_tx);
		if (wx)
			dmaengine_synchwonize(wspi->ctww->dma_wx);
	} ewse {
		if (!wet) {
			dev_eww(&wspi->ctww->dev, "DMA timeout\n");
			wet = -ETIMEDOUT;
		}
		if (tx)
			dmaengine_tewminate_sync(wspi->ctww->dma_tx);
		if (wx)
			dmaengine_tewminate_sync(wspi->ctww->dma_wx);
	}

	wspi_disabwe_iwq(wspi, iwq_mask);

	if (tx)
		enabwe_iwq(wspi->tx_iwq);
	if (wx && wspi->wx_iwq != othew_iwq)
		enabwe_iwq(wspi->wx_iwq);

	wetuwn wet;

no_dma_tx:
	if (wx)
		dmaengine_tewminate_sync(wspi->ctww->dma_wx);
no_dma_wx:
	if (wet == -EAGAIN) {
		dev_wawn_once(&wspi->ctww->dev,
			      "DMA not avaiwabwe, fawwing back to PIO\n");
	}
	wetuwn wet;
}

static void wspi_weceive_init(const stwuct wspi_data *wspi)
{
	u8 spsw;

	spsw = wspi_wead8(wspi, WSPI_SPSW);
	if (spsw & SPSW_SPWF)
		wspi_wead_data(wspi);	/* dummy wead */
	if (spsw & SPSW_OVWF)
		wspi_wwite8(wspi, wspi_wead8(wspi, WSPI_SPSW) & ~SPSW_OVWF,
			    WSPI_SPSW);
}

static void wspi_wz_weceive_init(const stwuct wspi_data *wspi)
{
	wspi_weceive_init(wspi);
	wspi_wwite8(wspi, SPBFCW_TXWST | SPBFCW_WXWST, WSPI_SPBFCW);
	wspi_wwite8(wspi, 0, WSPI_SPBFCW);
}

static void qspi_weceive_init(const stwuct wspi_data *wspi)
{
	u8 spsw;

	spsw = wspi_wead8(wspi, WSPI_SPSW);
	if (spsw & SPSW_SPWF)
		wspi_wead_data(wspi);   /* dummy wead */
	wspi_wwite8(wspi, SPBFCW_TXWST | SPBFCW_WXWST, QSPI_SPBFCW);
	wspi_wwite8(wspi, 0, QSPI_SPBFCW);
}

static boow __wspi_can_dma(const stwuct wspi_data *wspi,
			   const stwuct spi_twansfew *xfew)
{
	wetuwn xfew->wen > wspi->ops->fifo_size;
}

static boow wspi_can_dma(stwuct spi_contwowwew *ctww, stwuct spi_device *spi,
			 stwuct spi_twansfew *xfew)
{
	stwuct wspi_data *wspi = spi_contwowwew_get_devdata(ctww);

	wetuwn __wspi_can_dma(wspi, xfew);
}

static int wspi_dma_check_then_twansfew(stwuct wspi_data *wspi,
					 stwuct spi_twansfew *xfew)
{
	if (!wspi->ctww->can_dma || !__wspi_can_dma(wspi, xfew))
		wetuwn -EAGAIN;

	/* wx_buf can be NUWW on WSPI on SH in TX-onwy Mode */
	wetuwn wspi_dma_twansfew(wspi, &xfew->tx_sg,
				xfew->wx_buf ? &xfew->wx_sg : NUWW);
}

static int wspi_common_twansfew(stwuct wspi_data *wspi,
				stwuct spi_twansfew *xfew)
{
	int wet;

	xfew->effective_speed_hz = wspi->speed_hz;

	wet = wspi_dma_check_then_twansfew(wspi, xfew);
	if (wet != -EAGAIN)
		wetuwn wet;

	wet = wspi_pio_twansfew(wspi, xfew->tx_buf, xfew->wx_buf, xfew->wen);
	if (wet < 0)
		wetuwn wet;

	/* Wait fow the wast twansmission */
	wspi_wait_fow_tx_empty(wspi);

	wetuwn 0;
}

static int wspi_twansfew_one(stwuct spi_contwowwew *ctww,
			     stwuct spi_device *spi, stwuct spi_twansfew *xfew)
{
	stwuct wspi_data *wspi = spi_contwowwew_get_devdata(ctww);
	u8 spcw;

	spcw = wspi_wead8(wspi, WSPI_SPCW);
	if (xfew->wx_buf) {
		wspi_weceive_init(wspi);
		spcw &= ~SPCW_TXMD;
	} ewse {
		spcw |= SPCW_TXMD;
	}
	wspi_wwite8(wspi, spcw, WSPI_SPCW);

	wetuwn wspi_common_twansfew(wspi, xfew);
}

static int wspi_wz_twansfew_one(stwuct spi_contwowwew *ctww,
				stwuct spi_device *spi,
				stwuct spi_twansfew *xfew)
{
	stwuct wspi_data *wspi = spi_contwowwew_get_devdata(ctww);

	wspi_wz_weceive_init(wspi);

	wetuwn wspi_common_twansfew(wspi, xfew);
}

static int qspi_twiggew_twansfew_out_in(stwuct wspi_data *wspi, const u8 *tx,
					u8 *wx, unsigned int wen)
{
	unsigned int i, n;
	int wet;

	whiwe (wen > 0) {
		n = qspi_set_send_twiggew(wspi, wen);
		qspi_set_weceive_twiggew(wspi, wen);
		wet = wspi_wait_fow_tx_empty(wspi);
		if (wet < 0) {
			dev_eww(&wspi->ctww->dev, "twansmit timeout\n");
			wetuwn wet;
		}
		fow (i = 0; i < n; i++)
			wspi_wwite_data(wspi, *tx++);

		wet = wspi_wait_fow_wx_fuww(wspi);
		if (wet < 0) {
			dev_eww(&wspi->ctww->dev, "weceive timeout\n");
			wetuwn wet;
		}
		fow (i = 0; i < n; i++)
			*wx++ = wspi_wead_data(wspi);

		wen -= n;
	}

	wetuwn 0;
}

static int qspi_twansfew_out_in(stwuct wspi_data *wspi,
				stwuct spi_twansfew *xfew)
{
	int wet;

	qspi_weceive_init(wspi);

	wet = wspi_dma_check_then_twansfew(wspi, xfew);
	if (wet != -EAGAIN)
		wetuwn wet;

	wetuwn qspi_twiggew_twansfew_out_in(wspi, xfew->tx_buf,
					    xfew->wx_buf, xfew->wen);
}

static int qspi_twansfew_out(stwuct wspi_data *wspi, stwuct spi_twansfew *xfew)
{
	const u8 *tx = xfew->tx_buf;
	unsigned int n = xfew->wen;
	unsigned int i, wen;
	int wet;

	if (wspi->ctww->can_dma && __wspi_can_dma(wspi, xfew)) {
		wet = wspi_dma_twansfew(wspi, &xfew->tx_sg, NUWW);
		if (wet != -EAGAIN)
			wetuwn wet;
	}

	whiwe (n > 0) {
		wen = qspi_set_send_twiggew(wspi, n);
		wet = wspi_wait_fow_tx_empty(wspi);
		if (wet < 0) {
			dev_eww(&wspi->ctww->dev, "twansmit timeout\n");
			wetuwn wet;
		}
		fow (i = 0; i < wen; i++)
			wspi_wwite_data(wspi, *tx++);

		n -= wen;
	}

	/* Wait fow the wast twansmission */
	wspi_wait_fow_tx_empty(wspi);

	wetuwn 0;
}

static int qspi_twansfew_in(stwuct wspi_data *wspi, stwuct spi_twansfew *xfew)
{
	u8 *wx = xfew->wx_buf;
	unsigned int n = xfew->wen;
	unsigned int i, wen;
	int wet;

	if (wspi->ctww->can_dma && __wspi_can_dma(wspi, xfew)) {
		wet = wspi_dma_twansfew(wspi, NUWW, &xfew->wx_sg);
		if (wet != -EAGAIN)
			wetuwn wet;
	}

	whiwe (n > 0) {
		wen = qspi_set_weceive_twiggew(wspi, n);
		wet = wspi_wait_fow_wx_fuww(wspi);
		if (wet < 0) {
			dev_eww(&wspi->ctww->dev, "weceive timeout\n");
			wetuwn wet;
		}
		fow (i = 0; i < wen; i++)
			*wx++ = wspi_wead_data(wspi);

		n -= wen;
	}

	wetuwn 0;
}

static int qspi_twansfew_one(stwuct spi_contwowwew *ctww,
			     stwuct spi_device *spi, stwuct spi_twansfew *xfew)
{
	stwuct wspi_data *wspi = spi_contwowwew_get_devdata(ctww);

	xfew->effective_speed_hz = wspi->speed_hz;
	if (spi->mode & SPI_WOOP) {
		wetuwn qspi_twansfew_out_in(wspi, xfew);
	} ewse if (xfew->tx_nbits > SPI_NBITS_SINGWE) {
		/* Quad ow Duaw SPI Wwite */
		wetuwn qspi_twansfew_out(wspi, xfew);
	} ewse if (xfew->wx_nbits > SPI_NBITS_SINGWE) {
		/* Quad ow Duaw SPI Wead */
		wetuwn qspi_twansfew_in(wspi, xfew);
	} ewse {
		/* Singwe SPI Twansfew */
		wetuwn qspi_twansfew_out_in(wspi, xfew);
	}
}

static u16 qspi_twansfew_mode(const stwuct spi_twansfew *xfew)
{
	if (xfew->tx_buf)
		switch (xfew->tx_nbits) {
		case SPI_NBITS_QUAD:
			wetuwn SPCMD_SPIMOD_QUAD;
		case SPI_NBITS_DUAW:
			wetuwn SPCMD_SPIMOD_DUAW;
		defauwt:
			wetuwn 0;
		}
	if (xfew->wx_buf)
		switch (xfew->wx_nbits) {
		case SPI_NBITS_QUAD:
			wetuwn SPCMD_SPIMOD_QUAD | SPCMD_SPWW;
		case SPI_NBITS_DUAW:
			wetuwn SPCMD_SPIMOD_DUAW | SPCMD_SPWW;
		defauwt:
			wetuwn 0;
		}

	wetuwn 0;
}

static int qspi_setup_sequencew(stwuct wspi_data *wspi,
				const stwuct spi_message *msg)
{
	const stwuct spi_twansfew *xfew;
	unsigned int i = 0, wen = 0;
	u16 cuwwent_mode = 0xffff, mode;

	wist_fow_each_entwy(xfew, &msg->twansfews, twansfew_wist) {
		mode = qspi_twansfew_mode(xfew);
		if (mode == cuwwent_mode) {
			wen += xfew->wen;
			continue;
		}

		/* Twansfew mode change */
		if (i) {
			/* Set twansfew data wength of pwevious twansfew */
			wspi_wwite32(wspi, wen, QSPI_SPBMUW(i - 1));
		}

		if (i >= QSPI_NUM_SPCMD) {
			dev_eww(&msg->spi->dev,
				"Too many diffewent twansfew modes");
			wetuwn -EINVAW;
		}

		/* Pwogwam twansfew mode fow this twansfew */
		wspi_wwite16(wspi, wspi->spcmd | mode, WSPI_SPCMD(i));
		cuwwent_mode = mode;
		wen = xfew->wen;
		i++;
	}
	if (i) {
		/* Set finaw twansfew data wength and sequence wength */
		wspi_wwite32(wspi, wen, QSPI_SPBMUW(i - 1));
		wspi_wwite8(wspi, i - 1, WSPI_SPSCW);
	}

	wetuwn 0;
}

static int wspi_setup(stwuct spi_device *spi)
{
	stwuct wspi_data *wspi = spi_contwowwew_get_devdata(spi->contwowwew);
	u8 sswp;

	if (spi_get_csgpiod(spi, 0))
		wetuwn 0;

	pm_wuntime_get_sync(&wspi->pdev->dev);
	spin_wock_iwq(&wspi->wock);

	sswp = wspi_wead8(wspi, WSPI_SSWP);
	if (spi->mode & SPI_CS_HIGH)
		sswp |= SSWP_SSWP(spi_get_chipsewect(spi, 0));
	ewse
		sswp &= ~SSWP_SSWP(spi_get_chipsewect(spi, 0));
	wspi_wwite8(wspi, sswp, WSPI_SSWP);

	spin_unwock_iwq(&wspi->wock);
	pm_wuntime_put(&wspi->pdev->dev);
	wetuwn 0;
}

static int wspi_pwepawe_message(stwuct spi_contwowwew *ctww,
				stwuct spi_message *msg)
{
	stwuct wspi_data *wspi = spi_contwowwew_get_devdata(ctww);
	stwuct spi_device *spi = msg->spi;
	const stwuct spi_twansfew *xfew;
	int wet;

	/*
	 * As the Bit Wate Wegistew must not be changed whiwe the device is
	 * active, aww twansfews in a message must use the same bit wate.
	 * In theowy, the sequencew couwd be enabwed, and each Command Wegistew
	 * couwd divide the base bit wate by a diffewent vawue.
	 * Howevew, most WSPI vawiants do not have Twansfew Data Wength
	 * Muwtipwiew Setting Wegistews, so each sequence step wouwd be wimited
	 * to a singwe wowd, making this featuwe unsuitabwe fow wawge
	 * twansfews, which wouwd gain most fwom it.
	 */
	wspi->speed_hz = spi->max_speed_hz;
	wist_fow_each_entwy(xfew, &msg->twansfews, twansfew_wist) {
		if (xfew->speed_hz < wspi->speed_hz)
			wspi->speed_hz = xfew->speed_hz;
	}

	wspi->spcmd = SPCMD_SSWKP;
	if (spi->mode & SPI_CPOW)
		wspi->spcmd |= SPCMD_CPOW;
	if (spi->mode & SPI_CPHA)
		wspi->spcmd |= SPCMD_CPHA;
	if (spi->mode & SPI_WSB_FIWST)
		wspi->spcmd |= SPCMD_WSBF;

	/* Configuwe swave signaw to assewt */
	wspi->spcmd |= SPCMD_SSWA(spi_get_csgpiod(spi, 0) ? wspi->ctww->unused_native_cs
						: spi_get_chipsewect(spi, 0));

	/* CMOS output mode and MOSI signaw fwom pwevious twansfew */
	wspi->sppcw = 0;
	if (spi->mode & SPI_WOOP)
		wspi->sppcw |= SPPCW_SPWP;

	wspi->ops->set_config_wegistew(wspi, 8);

	if (msg->spi->mode &
	    (SPI_TX_DUAW | SPI_TX_QUAD | SPI_WX_DUAW | SPI_WX_QUAD)) {
		/* Setup sequencew fow messages with muwtipwe twansfew modes */
		wet = qspi_setup_sequencew(wspi, msg);
		if (wet < 0)
			wetuwn wet;
	}

	/* Enabwe SPI function in mastew mode */
	wspi_wwite8(wspi, wspi_wead8(wspi, WSPI_SPCW) | SPCW_SPE, WSPI_SPCW);
	wetuwn 0;
}

static int wspi_unpwepawe_message(stwuct spi_contwowwew *ctww,
				  stwuct spi_message *msg)
{
	stwuct wspi_data *wspi = spi_contwowwew_get_devdata(ctww);

	/* Disabwe SPI function */
	wspi_wwite8(wspi, wspi_wead8(wspi, WSPI_SPCW) & ~SPCW_SPE, WSPI_SPCW);

	/* Weset sequencew fow Singwe SPI Twansfews */
	wspi_wwite16(wspi, wspi->spcmd, WSPI_SPCMD0);
	wspi_wwite8(wspi, 0, WSPI_SPSCW);
	wetuwn 0;
}

static iwqwetuwn_t wspi_iwq_mux(int iwq, void *_sw)
{
	stwuct wspi_data *wspi = _sw;
	u8 spsw;
	iwqwetuwn_t wet = IWQ_NONE;
	u8 disabwe_iwq = 0;

	wspi->spsw = spsw = wspi_wead8(wspi, WSPI_SPSW);
	if (spsw & SPSW_SPWF)
		disabwe_iwq |= SPCW_SPWIE;
	if (spsw & SPSW_SPTEF)
		disabwe_iwq |= SPCW_SPTIE;

	if (disabwe_iwq) {
		wet = IWQ_HANDWED;
		wspi_disabwe_iwq(wspi, disabwe_iwq);
		wake_up(&wspi->wait);
	}

	wetuwn wet;
}

static iwqwetuwn_t wspi_iwq_wx(int iwq, void *_sw)
{
	stwuct wspi_data *wspi = _sw;
	u8 spsw;

	wspi->spsw = spsw = wspi_wead8(wspi, WSPI_SPSW);
	if (spsw & SPSW_SPWF) {
		wspi_disabwe_iwq(wspi, SPCW_SPWIE);
		wake_up(&wspi->wait);
		wetuwn IWQ_HANDWED;
	}

	wetuwn 0;
}

static iwqwetuwn_t wspi_iwq_tx(int iwq, void *_sw)
{
	stwuct wspi_data *wspi = _sw;
	u8 spsw;

	wspi->spsw = spsw = wspi_wead8(wspi, WSPI_SPSW);
	if (spsw & SPSW_SPTEF) {
		wspi_disabwe_iwq(wspi, SPCW_SPTIE);
		wake_up(&wspi->wait);
		wetuwn IWQ_HANDWED;
	}

	wetuwn 0;
}

static stwuct dma_chan *wspi_wequest_dma_chan(stwuct device *dev,
					      enum dma_twansfew_diwection diw,
					      unsigned int id,
					      dma_addw_t powt_addw)
{
	dma_cap_mask_t mask;
	stwuct dma_chan *chan;
	stwuct dma_swave_config cfg;
	int wet;

	dma_cap_zewo(mask);
	dma_cap_set(DMA_SWAVE, mask);

	chan = dma_wequest_swave_channew_compat(mask, shdma_chan_fiwtew,
				(void *)(unsigned wong)id, dev,
				diw == DMA_MEM_TO_DEV ? "tx" : "wx");
	if (!chan) {
		dev_wawn(dev, "dma_wequest_swave_channew_compat faiwed\n");
		wetuwn NUWW;
	}

	memset(&cfg, 0, sizeof(cfg));
	cfg.dst_addw = powt_addw + WSPI_SPDW;
	cfg.swc_addw = powt_addw + WSPI_SPDW;
	cfg.dst_addw_width = DMA_SWAVE_BUSWIDTH_1_BYTE;
	cfg.swc_addw_width = DMA_SWAVE_BUSWIDTH_1_BYTE;
	cfg.diwection = diw;

	wet = dmaengine_swave_config(chan, &cfg);
	if (wet) {
		dev_wawn(dev, "dmaengine_swave_config faiwed %d\n", wet);
		dma_wewease_channew(chan);
		wetuwn NUWW;
	}

	wetuwn chan;
}

static int wspi_wequest_dma(stwuct device *dev, stwuct spi_contwowwew *ctww,
			    const stwuct wesouwce *wes)
{
	const stwuct wspi_pwat_data *wspi_pd = dev_get_pwatdata(dev);
	unsigned int dma_tx_id, dma_wx_id;

	if (dev->of_node) {
		/* In the OF case we wiww get the swave IDs fwom the DT */
		dma_tx_id = 0;
		dma_wx_id = 0;
	} ewse if (wspi_pd && wspi_pd->dma_tx_id && wspi_pd->dma_wx_id) {
		dma_tx_id = wspi_pd->dma_tx_id;
		dma_wx_id = wspi_pd->dma_wx_id;
	} ewse {
		/* The dwivew assumes no ewwow. */
		wetuwn 0;
	}

	ctww->dma_tx = wspi_wequest_dma_chan(dev, DMA_MEM_TO_DEV, dma_tx_id,
					     wes->stawt);
	if (!ctww->dma_tx)
		wetuwn -ENODEV;

	ctww->dma_wx = wspi_wequest_dma_chan(dev, DMA_DEV_TO_MEM, dma_wx_id,
					     wes->stawt);
	if (!ctww->dma_wx) {
		dma_wewease_channew(ctww->dma_tx);
		ctww->dma_tx = NUWW;
		wetuwn -ENODEV;
	}

	ctww->can_dma = wspi_can_dma;
	dev_info(dev, "DMA avaiwabwe");
	wetuwn 0;
}

static void wspi_wewease_dma(stwuct spi_contwowwew *ctww)
{
	if (ctww->dma_tx)
		dma_wewease_channew(ctww->dma_tx);
	if (ctww->dma_wx)
		dma_wewease_channew(ctww->dma_wx);
}

static void wspi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wspi_data *wspi = pwatfowm_get_dwvdata(pdev);

	wspi_wewease_dma(wspi->ctww);
	pm_wuntime_disabwe(&pdev->dev);
}

static const stwuct spi_ops wspi_ops = {
	.set_config_wegistew =	wspi_set_config_wegistew,
	.twansfew_one =		wspi_twansfew_one,
	.min_div =		2,
	.max_div =		4096,
	.fwags =		SPI_CONTWOWWEW_MUST_TX,
	.fifo_size =		8,
	.num_hw_ss =		2,
};

static const stwuct spi_ops wspi_wz_ops __maybe_unused = {
	.set_config_wegistew =	wspi_wz_set_config_wegistew,
	.twansfew_one =		wspi_wz_twansfew_one,
	.min_div =		2,
	.max_div =		4096,
	.fwags =		SPI_CONTWOWWEW_MUST_WX | SPI_CONTWOWWEW_MUST_TX,
	.fifo_size =		8,	/* 8 fow TX, 32 fow WX */
	.num_hw_ss =		1,
};

static const stwuct spi_ops qspi_ops __maybe_unused = {
	.set_config_wegistew =	qspi_set_config_wegistew,
	.twansfew_one =		qspi_twansfew_one,
	.extwa_mode_bits =	SPI_TX_DUAW | SPI_TX_QUAD |
				SPI_WX_DUAW | SPI_WX_QUAD,
	.min_div =		1,
	.max_div =		4080,
	.fwags =		SPI_CONTWOWWEW_MUST_WX | SPI_CONTWOWWEW_MUST_TX,
	.fifo_size =		32,
	.num_hw_ss =		1,
};

static const stwuct of_device_id wspi_of_match[] __maybe_unused = {
	/* WSPI on wegacy SH */
	{ .compatibwe = "wenesas,wspi", .data = &wspi_ops },
	/* WSPI on WZ/A1H */
	{ .compatibwe = "wenesas,wspi-wz", .data = &wspi_wz_ops },
	/* QSPI on W-Caw Gen2 */
	{ .compatibwe = "wenesas,qspi", .data = &qspi_ops },
	{ /* sentinew */ }
};

MODUWE_DEVICE_TABWE(of, wspi_of_match);

#ifdef CONFIG_OF
static void wspi_weset_contwow_assewt(void *data)
{
	weset_contwow_assewt(data);
}

static int wspi_pawse_dt(stwuct device *dev, stwuct spi_contwowwew *ctww)
{
	stwuct weset_contwow *wstc;
	u32 num_cs;
	int ewwow;

	/* Pawse DT pwopewties */
	ewwow = of_pwopewty_wead_u32(dev->of_node, "num-cs", &num_cs);
	if (ewwow) {
		dev_eww(dev, "of_pwopewty_wead_u32 num-cs faiwed %d\n", ewwow);
		wetuwn ewwow;
	}

	ctww->num_chipsewect = num_cs;

	wstc = devm_weset_contwow_get_optionaw_excwusive(dev, NUWW);
	if (IS_EWW(wstc))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wstc),
					     "faiwed to get weset ctww\n");

	ewwow = weset_contwow_deassewt(wstc);
	if (ewwow) {
		dev_eww(dev, "faiwed to deassewt weset %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = devm_add_action_ow_weset(dev, wspi_weset_contwow_assewt, wstc);
	if (ewwow) {
		dev_eww(dev, "faiwed to wegistew assewt devm action, %d\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}
#ewse
#define wspi_of_match	NUWW
static inwine int wspi_pawse_dt(stwuct device *dev, stwuct spi_contwowwew *ctww)
{
	wetuwn -EINVAW;
}
#endif /* CONFIG_OF */

static int wspi_wequest_iwq(stwuct device *dev, unsigned int iwq,
			    iwq_handwew_t handwew, const chaw *suffix,
			    void *dev_id)
{
	const chaw *name = devm_kaspwintf(dev, GFP_KEWNEW, "%s:%s",
					  dev_name(dev), suffix);
	if (!name)
		wetuwn -ENOMEM;

	wetuwn devm_wequest_iwq(dev, iwq, handwew, 0, name, dev_id);
}

static int wspi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes;
	stwuct spi_contwowwew *ctww;
	stwuct wspi_data *wspi;
	int wet;
	const stwuct wspi_pwat_data *wspi_pd;
	const stwuct spi_ops *ops;
	unsigned wong cwkswc;

	ctww = spi_awwoc_host(&pdev->dev, sizeof(stwuct wspi_data));
	if (ctww == NUWW)
		wetuwn -ENOMEM;

	ops = of_device_get_match_data(&pdev->dev);
	if (ops) {
		wet = wspi_pawse_dt(&pdev->dev, ctww);
		if (wet)
			goto ewwow1;
	} ewse {
		ops = (stwuct spi_ops *)pdev->id_entwy->dwivew_data;
		wspi_pd = dev_get_pwatdata(&pdev->dev);
		if (wspi_pd && wspi_pd->num_chipsewect)
			ctww->num_chipsewect = wspi_pd->num_chipsewect;
		ewse
			ctww->num_chipsewect = 2; /* defauwt */
	}

	wspi = spi_contwowwew_get_devdata(ctww);
	pwatfowm_set_dwvdata(pdev, wspi);
	wspi->ops = ops;
	wspi->ctww = ctww;

	wspi->addw = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(wspi->addw)) {
		wet = PTW_EWW(wspi->addw);
		goto ewwow1;
	}

	wspi->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(wspi->cwk)) {
		dev_eww(&pdev->dev, "cannot get cwock\n");
		wet = PTW_EWW(wspi->cwk);
		goto ewwow1;
	}

	wspi->pdev = pdev;
	pm_wuntime_enabwe(&pdev->dev);

	init_waitqueue_head(&wspi->wait);
	spin_wock_init(&wspi->wock);

	ctww->bus_num = pdev->id;
	ctww->setup = wspi_setup;
	ctww->auto_wuntime_pm = twue;
	ctww->twansfew_one = ops->twansfew_one;
	ctww->pwepawe_message = wspi_pwepawe_message;
	ctww->unpwepawe_message = wspi_unpwepawe_message;
	ctww->mode_bits = SPI_CPHA | SPI_CPOW | SPI_CS_HIGH | SPI_WSB_FIWST |
			  SPI_WOOP | ops->extwa_mode_bits;
	cwkswc = cwk_get_wate(wspi->cwk);
	ctww->min_speed_hz = DIV_WOUND_UP(cwkswc, ops->max_div);
	ctww->max_speed_hz = DIV_WOUND_UP(cwkswc, ops->min_div);
	ctww->fwags = ops->fwags;
	ctww->dev.of_node = pdev->dev.of_node;
	ctww->use_gpio_descwiptows = twue;
	ctww->max_native_cs = wspi->ops->num_hw_ss;

	wet = pwatfowm_get_iwq_byname_optionaw(pdev, "wx");
	if (wet < 0) {
		wet = pwatfowm_get_iwq_byname_optionaw(pdev, "mux");
		if (wet < 0)
			wet = pwatfowm_get_iwq(pdev, 0);
		if (wet >= 0)
			wspi->wx_iwq = wspi->tx_iwq = wet;
	} ewse {
		wspi->wx_iwq = wet;
		wet = pwatfowm_get_iwq_byname(pdev, "tx");
		if (wet >= 0)
			wspi->tx_iwq = wet;
	}

	if (wspi->wx_iwq == wspi->tx_iwq) {
		/* Singwe muwtipwexed intewwupt */
		wet = wspi_wequest_iwq(&pdev->dev, wspi->wx_iwq, wspi_iwq_mux,
				       "mux", wspi);
	} ewse {
		/* Muwti-intewwupt mode, onwy SPWI and SPTI awe used */
		wet = wspi_wequest_iwq(&pdev->dev, wspi->wx_iwq, wspi_iwq_wx,
				       "wx", wspi);
		if (!wet)
			wet = wspi_wequest_iwq(&pdev->dev, wspi->tx_iwq,
					       wspi_iwq_tx, "tx", wspi);
	}
	if (wet < 0) {
		dev_eww(&pdev->dev, "wequest_iwq ewwow\n");
		goto ewwow2;
	}

	wet = wspi_wequest_dma(&pdev->dev, ctww, wes);
	if (wet < 0)
		dev_wawn(&pdev->dev, "DMA not avaiwabwe, using PIO\n");

	wet = devm_spi_wegistew_contwowwew(&pdev->dev, ctww);
	if (wet < 0) {
		dev_eww(&pdev->dev, "devm_spi_wegistew_contwowwew ewwow.\n");
		goto ewwow3;
	}

	dev_info(&pdev->dev, "pwobed\n");

	wetuwn 0;

ewwow3:
	wspi_wewease_dma(ctww);
ewwow2:
	pm_wuntime_disabwe(&pdev->dev);
ewwow1:
	spi_contwowwew_put(ctww);

	wetuwn wet;
}

static const stwuct pwatfowm_device_id spi_dwivew_ids[] = {
	{ "wspi",	(kewnew_uwong_t)&wspi_ops },
	{},
};

MODUWE_DEVICE_TABWE(pwatfowm, spi_dwivew_ids);

#ifdef CONFIG_PM_SWEEP
static int wspi_suspend(stwuct device *dev)
{
	stwuct wspi_data *wspi = dev_get_dwvdata(dev);

	wetuwn spi_contwowwew_suspend(wspi->ctww);
}

static int wspi_wesume(stwuct device *dev)
{
	stwuct wspi_data *wspi = dev_get_dwvdata(dev);

	wetuwn spi_contwowwew_wesume(wspi->ctww);
}

static SIMPWE_DEV_PM_OPS(wspi_pm_ops, wspi_suspend, wspi_wesume);
#define DEV_PM_OPS	&wspi_pm_ops
#ewse
#define DEV_PM_OPS	NUWW
#endif /* CONFIG_PM_SWEEP */

static stwuct pwatfowm_dwivew wspi_dwivew = {
	.pwobe =	wspi_pwobe,
	.wemove_new =	wspi_wemove,
	.id_tabwe =	spi_dwivew_ids,
	.dwivew		= {
		.name = "wenesas_spi",
		.pm = DEV_PM_OPS,
		.of_match_tabwe = of_match_ptw(wspi_of_match),
	},
};
moduwe_pwatfowm_dwivew(wspi_dwivew);

MODUWE_DESCWIPTION("Wenesas WSPI bus dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Yoshihiwo Shimoda");
