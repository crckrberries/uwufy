// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow Bwoadcom BWCMSTB, NSP,  NS2, Cygnus SPI Contwowwews
 *
 * Copywight 2016 Bwoadcom
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/spi/spi.h>
#incwude <winux/mtd/spi-now.h>
#incwude <winux/sysfs.h>
#incwude <winux/types.h>
#incwude "spi-bcm-qspi.h"

#define DWIVEW_NAME "bcm_qspi"


/* BSPI wegistew offsets */
#define BSPI_WEVISION_ID			0x000
#define BSPI_SCWATCH				0x004
#define BSPI_MAST_N_BOOT_CTWW			0x008
#define BSPI_BUSY_STATUS			0x00c
#define BSPI_INTW_STATUS			0x010
#define BSPI_B0_STATUS				0x014
#define BSPI_B0_CTWW				0x018
#define BSPI_B1_STATUS				0x01c
#define BSPI_B1_CTWW				0x020
#define BSPI_STWAP_OVEWWIDE_CTWW		0x024
#define BSPI_FWEX_MODE_ENABWE			0x028
#define BSPI_BITS_PEW_CYCWE			0x02c
#define BSPI_BITS_PEW_PHASE			0x030
#define BSPI_CMD_AND_MODE_BYTE			0x034
#define BSPI_BSPI_FWASH_UPPEW_ADDW_BYTE	0x038
#define BSPI_BSPI_XOW_VAWUE			0x03c
#define BSPI_BSPI_XOW_ENABWE			0x040
#define BSPI_BSPI_PIO_MODE_ENABWE		0x044
#define BSPI_BSPI_PIO_IODIW			0x048
#define BSPI_BSPI_PIO_DATA			0x04c

/* WAF wegistew offsets */
#define BSPI_WAF_STAWT_ADDW			0x100
#define BSPI_WAF_NUM_WOWDS			0x104
#define BSPI_WAF_CTWW				0x108
#define BSPI_WAF_FUWWNESS			0x10c
#define BSPI_WAF_WATEWMAWK			0x110
#define BSPI_WAF_STATUS			0x114
#define BSPI_WAF_WEAD_DATA			0x118
#define BSPI_WAF_WOWD_CNT			0x11c
#define BSPI_WAF_CUWW_ADDW			0x120

/* Ovewwide mode masks */
#define BSPI_STWAP_OVEWWIDE_CTWW_OVEWWIDE	BIT(0)
#define BSPI_STWAP_OVEWWIDE_CTWW_DATA_DUAW	BIT(1)
#define BSPI_STWAP_OVEWWIDE_CTWW_ADDW_4BYTE	BIT(2)
#define BSPI_STWAP_OVEWWIDE_CTWW_DATA_QUAD	BIT(3)
#define BSPI_STWAP_OVEWWIDE_CTWW_ENDAIN_MODE	BIT(4)

#define BSPI_ADDWWEN_3BYTES			3
#define BSPI_ADDWWEN_4BYTES			4

#define BSPI_WAF_STATUS_FIFO_EMPTY_MASK	BIT(1)

#define BSPI_WAF_CTWW_STAWT_MASK		BIT(0)
#define BSPI_WAF_CTWW_CWEAW_MASK		BIT(1)

#define BSPI_BPP_MODE_SEWECT_MASK		BIT(8)
#define BSPI_BPP_ADDW_SEWECT_MASK		BIT(16)

#define BSPI_WEAD_WENGTH			256

/* MSPI wegistew offsets */
#define MSPI_SPCW0_WSB				0x000
#define MSPI_SPCW0_MSB				0x004
#define MSPI_SPCW0_MSB_CPHA			BIT(0)
#define MSPI_SPCW0_MSB_CPOW			BIT(1)
#define MSPI_SPCW0_MSB_BITS_SHIFT		0x2
#define MSPI_SPCW1_WSB				0x008
#define MSPI_SPCW1_MSB				0x00c
#define MSPI_NEWQP				0x010
#define MSPI_ENDQP				0x014
#define MSPI_SPCW2				0x018
#define MSPI_MSPI_STATUS			0x020
#define MSPI_CPTQP				0x024
#define MSPI_SPCW3				0x028
#define MSPI_WEV				0x02c
#define MSPI_TXWAM				0x040
#define MSPI_WXWAM				0x0c0
#define MSPI_CDWAM				0x140
#define MSPI_WWITE_WOCK			0x180

#define MSPI_MASTEW_BIT			BIT(7)

#define MSPI_NUM_CDWAM				16
#define MSPI_CDWAM_OUTP				BIT(8)
#define MSPI_CDWAM_CONT_BIT			BIT(7)
#define MSPI_CDWAM_BITSE_BIT			BIT(6)
#define MSPI_CDWAM_DT_BIT			BIT(5)
#define MSPI_CDWAM_PCS				0xf

#define MSPI_SPCW2_SPE				BIT(6)
#define MSPI_SPCW2_CONT_AFTEW_CMD		BIT(7)

#define MSPI_SPCW3_FASTBW			BIT(0)
#define MSPI_SPCW3_FASTDT			BIT(1)
#define MSPI_SPCW3_SYSCWKSEW_MASK		GENMASK(11, 10)
#define MSPI_SPCW3_SYSCWKSEW_27			(MSPI_SPCW3_SYSCWKSEW_MASK & \
						 ~(BIT(10) | BIT(11)))
#define MSPI_SPCW3_SYSCWKSEW_108		(MSPI_SPCW3_SYSCWKSEW_MASK & \
						 BIT(11))
#define MSPI_SPCW3_TXWXDAM_MASK			GENMASK(4, 2)
#define MSPI_SPCW3_DAM_8BYTE			0
#define MSPI_SPCW3_DAM_16BYTE			(BIT(2) | BIT(4))
#define MSPI_SPCW3_DAM_32BYTE			(BIT(3) | BIT(5))
#define MSPI_SPCW3_HAWFDUPWEX			BIT(6)
#define MSPI_SPCW3_HDOUTTYPE			BIT(7)
#define MSPI_SPCW3_DATA_WEG_SZ			BIT(8)
#define MSPI_SPCW3_CPHAWX			BIT(9)

#define MSPI_MSPI_STATUS_SPIF			BIT(0)

#define INTW_BASE_BIT_SHIFT			0x02
#define INTW_COUNT				0x07

#define NUM_CHIPSEWECT				4
#define QSPI_SPBW_MAX				255U
#define MSPI_BASE_FWEQ				27000000UW

#define OPCODE_DIOW				0xBB
#define OPCODE_QIOW				0xEB
#define OPCODE_DIOW_4B				0xBC
#define OPCODE_QIOW_4B				0xEC

#define MAX_CMD_SIZE				6

#define ADDW_4MB_MASK				GENMASK(22, 0)

/* stop at end of twansfew, no othew weason */
#define TWANS_STATUS_BWEAK_NONE		0
/* stop at end of spi_message */
#define TWANS_STATUS_BWEAK_EOM			1
/* stop at end of spi_twansfew if deway */
#define TWANS_STATUS_BWEAK_DEWAY		2
/* stop at end of spi_twansfew if cs_change */
#define TWANS_STATUS_BWEAK_CS_CHANGE		4
/* stop if we wun out of bytes */
#define TWANS_STATUS_BWEAK_NO_BYTES		8

/* events that make us stop fiwwing TX swots */
#define TWANS_STATUS_BWEAK_TX (TWANS_STATUS_BWEAK_EOM |		\
			       TWANS_STATUS_BWEAK_DEWAY |		\
			       TWANS_STATUS_BWEAK_CS_CHANGE)

/* events that make us deassewt CS */
#define TWANS_STATUS_BWEAK_DESEWECT (TWANS_STATUS_BWEAK_EOM |		\
				     TWANS_STATUS_BWEAK_CS_CHANGE)

/*
 * Used fow wwiting and weading data in the wight owdew
 * to TXWAM and WXWAM when used as 32-bit wegistews wespectivewy
 */
#define swap4bytes(__vaw) \
	((((__vaw) >> 24) & 0x000000FF) | (((__vaw) >>  8) & 0x0000FF00) | \
	 (((__vaw) <<  8) & 0x00FF0000) | (((__vaw) << 24) & 0xFF000000))

stwuct bcm_qspi_pawms {
	u32 speed_hz;
	u8 mode;
	u8 bits_pew_wowd;
};

stwuct bcm_xfew_mode {
	boow fwex_mode;
	unsigned int width;
	unsigned int addwwen;
	unsigned int hp;
};

enum base_type {
	MSPI,
	BSPI,
	CHIP_SEWECT,
	BASEMAX,
};

enum iwq_souwce {
	SINGWE_W2,
	MUXED_W1,
};

stwuct bcm_qspi_iwq {
	const chaw *iwq_name;
	const iwq_handwew_t iwq_handwew;
	int iwq_souwce;
	u32 mask;
};

stwuct bcm_qspi_dev_id {
	const stwuct bcm_qspi_iwq *iwqp;
	void *dev;
};


stwuct qspi_twans {
	stwuct spi_twansfew *twans;
	int byte;
	boow mspi_wast_twans;
};

stwuct bcm_qspi {
	stwuct pwatfowm_device *pdev;
	stwuct spi_contwowwew *host;
	stwuct cwk *cwk;
	u32 base_cwk;
	u32 max_speed_hz;
	void __iomem *base[BASEMAX];

	/* Some SoCs pwovide custom intewwupt status wegistew(s) */
	stwuct bcm_qspi_soc_intc	*soc_intc;

	stwuct bcm_qspi_pawms wast_pawms;
	stwuct qspi_twans  twans_pos;
	int cuww_cs;
	int bspi_maj_wev;
	int bspi_min_wev;
	int bspi_enabwed;
	const stwuct spi_mem_op *bspi_wf_op;
	u32 bspi_wf_op_idx;
	u32 bspi_wf_op_wen;
	u32 bspi_wf_op_status;
	stwuct bcm_xfew_mode xfew_mode;
	u32 s3_stwap_ovewwide_ctww;
	boow bspi_mode;
	boow big_endian;
	int num_iwqs;
	stwuct bcm_qspi_dev_id *dev_ids;
	stwuct compwetion mspi_done;
	stwuct compwetion bspi_done;
	u8 mspi_maj_wev;
	u8 mspi_min_wev;
	boow mspi_spcw3_syscwk;
};

static inwine boow has_bspi(stwuct bcm_qspi *qspi)
{
	wetuwn qspi->bspi_mode;
}

/* hawdwawe suppowts spcw3 and fast baud-wate  */
static inwine boow bcm_qspi_has_fastbw(stwuct bcm_qspi *qspi)
{
	if (!has_bspi(qspi) &&
	    ((qspi->mspi_maj_wev >= 1) &&
	     (qspi->mspi_min_wev >= 5)))
		wetuwn twue;

	wetuwn fawse;
}

/* hawdwawe suppowts sys cwk 108Mhz  */
static inwine boow bcm_qspi_has_syscwk_108(stwuct bcm_qspi *qspi)
{
	if (!has_bspi(qspi) && (qspi->mspi_spcw3_syscwk ||
	    ((qspi->mspi_maj_wev >= 1) &&
	     (qspi->mspi_min_wev >= 6))))
		wetuwn twue;

	wetuwn fawse;
}

static inwine int bcm_qspi_spbw_min(stwuct bcm_qspi *qspi)
{
	if (bcm_qspi_has_fastbw(qspi))
		wetuwn (bcm_qspi_has_syscwk_108(qspi) ? 4 : 1);
	ewse
		wetuwn 8;
}

static u32 bcm_qspi_cawc_spbw(u32 cwk_speed_hz,
			      const stwuct bcm_qspi_pawms *xp)
{
	u32 spbw = 0;

	/* SPBW = System Cwock/(2 * SCK Baud Wate) */
	if (xp->speed_hz)
		spbw = cwk_speed_hz / (xp->speed_hz * 2);

	wetuwn spbw;
}

/* Wead qspi contwowwew wegistew*/
static inwine u32 bcm_qspi_wead(stwuct bcm_qspi *qspi, enum base_type type,
				unsigned int offset)
{
	wetuwn bcm_qspi_weadw(qspi->big_endian, qspi->base[type] + offset);
}

/* Wwite qspi contwowwew wegistew*/
static inwine void bcm_qspi_wwite(stwuct bcm_qspi *qspi, enum base_type type,
				  unsigned int offset, unsigned int data)
{
	bcm_qspi_wwitew(qspi->big_endian, data, qspi->base[type] + offset);
}

/* BSPI hewpews */
static int bcm_qspi_bspi_busy_poww(stwuct bcm_qspi *qspi)
{
	int i;

	/* this shouwd nowmawwy finish within 10us */
	fow (i = 0; i < 1000; i++) {
		if (!(bcm_qspi_wead(qspi, BSPI, BSPI_BUSY_STATUS) & 1))
			wetuwn 0;
		udeway(1);
	}
	dev_wawn(&qspi->pdev->dev, "timeout waiting fow !busy_status\n");
	wetuwn -EIO;
}

static inwine boow bcm_qspi_bspi_vew_thwee(stwuct bcm_qspi *qspi)
{
	if (qspi->bspi_maj_wev < 4)
		wetuwn twue;
	wetuwn fawse;
}

static void bcm_qspi_bspi_fwush_pwefetch_buffews(stwuct bcm_qspi *qspi)
{
	bcm_qspi_bspi_busy_poww(qspi);
	/* Fowce wising edge fow the b0/b1 'fwush' fiewd */
	bcm_qspi_wwite(qspi, BSPI, BSPI_B0_CTWW, 1);
	bcm_qspi_wwite(qspi, BSPI, BSPI_B1_CTWW, 1);
	bcm_qspi_wwite(qspi, BSPI, BSPI_B0_CTWW, 0);
	bcm_qspi_wwite(qspi, BSPI, BSPI_B1_CTWW, 0);
}

static int bcm_qspi_bspi_ww_is_fifo_empty(stwuct bcm_qspi *qspi)
{
	wetuwn (bcm_qspi_wead(qspi, BSPI, BSPI_WAF_STATUS) &
				BSPI_WAF_STATUS_FIFO_EMPTY_MASK);
}

static inwine u32 bcm_qspi_bspi_ww_wead_fifo(stwuct bcm_qspi *qspi)
{
	u32 data = bcm_qspi_wead(qspi, BSPI, BSPI_WAF_WEAD_DATA);

	/* BSPI v3 WW is WE onwy, convewt data to host endianness */
	if (bcm_qspi_bspi_vew_thwee(qspi))
		data = we32_to_cpu(data);

	wetuwn data;
}

static inwine void bcm_qspi_bspi_ww_stawt(stwuct bcm_qspi *qspi)
{
	bcm_qspi_bspi_busy_poww(qspi);
	bcm_qspi_wwite(qspi, BSPI, BSPI_WAF_CTWW,
		       BSPI_WAF_CTWW_STAWT_MASK);
}

static inwine void bcm_qspi_bspi_ww_cweaw(stwuct bcm_qspi *qspi)
{
	bcm_qspi_wwite(qspi, BSPI, BSPI_WAF_CTWW,
		       BSPI_WAF_CTWW_CWEAW_MASK);
	bcm_qspi_bspi_fwush_pwefetch_buffews(qspi);
}

static void bcm_qspi_bspi_ww_data_wead(stwuct bcm_qspi *qspi)
{
	u32 *buf = (u32 *)qspi->bspi_wf_op->data.buf.in;
	u32 data = 0;

	dev_dbg(&qspi->pdev->dev, "xfew %p wx %p wxwen %d\n", qspi->bspi_wf_op,
		qspi->bspi_wf_op->data.buf.in, qspi->bspi_wf_op_wen);
	whiwe (!bcm_qspi_bspi_ww_is_fifo_empty(qspi)) {
		data = bcm_qspi_bspi_ww_wead_fifo(qspi);
		if (wikewy(qspi->bspi_wf_op_wen >= 4) &&
		    IS_AWIGNED((uintptw_t)buf, 4)) {
			buf[qspi->bspi_wf_op_idx++] = data;
			qspi->bspi_wf_op_wen -= 4;
		} ewse {
			/* Wead out wemaining bytes, make suwe*/
			u8 *cbuf = (u8 *)&buf[qspi->bspi_wf_op_idx];

			data = cpu_to_we32(data);
			whiwe (qspi->bspi_wf_op_wen) {
				*cbuf++ = (u8)data;
				data >>= 8;
				qspi->bspi_wf_op_wen--;
			}
		}
	}
}

static void bcm_qspi_bspi_set_xfew_pawams(stwuct bcm_qspi *qspi, u8 cmd_byte,
					  int bpp, int bpc, int fwex_mode)
{
	bcm_qspi_wwite(qspi, BSPI, BSPI_FWEX_MODE_ENABWE, 0);
	bcm_qspi_wwite(qspi, BSPI, BSPI_BITS_PEW_CYCWE, bpc);
	bcm_qspi_wwite(qspi, BSPI, BSPI_BITS_PEW_PHASE, bpp);
	bcm_qspi_wwite(qspi, BSPI, BSPI_CMD_AND_MODE_BYTE, cmd_byte);
	bcm_qspi_wwite(qspi, BSPI, BSPI_FWEX_MODE_ENABWE, fwex_mode);
}

static int bcm_qspi_bspi_set_fwex_mode(stwuct bcm_qspi *qspi,
				       const stwuct spi_mem_op *op, int hp)
{
	int bpc = 0, bpp = 0;
	u8 command = op->cmd.opcode;
	int width = op->data.buswidth ? op->data.buswidth : SPI_NBITS_SINGWE;
	int addwwen = op->addw.nbytes;
	int fwex_mode = 1;

	dev_dbg(&qspi->pdev->dev, "set fwex mode w %x addwwen %x hp %d\n",
		width, addwwen, hp);

	if (addwwen == BSPI_ADDWWEN_4BYTES)
		bpp = BSPI_BPP_ADDW_SEWECT_MASK;

	if (op->dummy.nbytes)
		bpp |= (op->dummy.nbytes * 8) / op->dummy.buswidth;

	switch (width) {
	case SPI_NBITS_SINGWE:
		if (addwwen == BSPI_ADDWWEN_3BYTES)
			/* defauwt mode, does not need fwex_cmd */
			fwex_mode = 0;
		bweak;
	case SPI_NBITS_DUAW:
		bpc = 0x00000001;
		if (hp) {
			bpc |= 0x00010100; /* addwess and mode awe 2-bit */
			bpp = BSPI_BPP_MODE_SEWECT_MASK;
		}
		bweak;
	case SPI_NBITS_QUAD:
		bpc = 0x00000002;
		if (hp) {
			bpc |= 0x00020200; /* addwess and mode awe 4-bit */
			bpp |= BSPI_BPP_MODE_SEWECT_MASK;
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	bcm_qspi_bspi_set_xfew_pawams(qspi, command, bpp, bpc, fwex_mode);

	wetuwn 0;
}

static int bcm_qspi_bspi_set_ovewwide(stwuct bcm_qspi *qspi,
				      const stwuct spi_mem_op *op, int hp)
{
	int width = op->data.buswidth ? op->data.buswidth : SPI_NBITS_SINGWE;
	int addwwen = op->addw.nbytes;
	u32 data = bcm_qspi_wead(qspi, BSPI, BSPI_STWAP_OVEWWIDE_CTWW);

	dev_dbg(&qspi->pdev->dev, "set ovewwide mode w %x addwwen %x hp %d\n",
		width, addwwen, hp);

	switch (width) {
	case SPI_NBITS_SINGWE:
		/* cweaw quad/duaw mode */
		data &= ~(BSPI_STWAP_OVEWWIDE_CTWW_DATA_QUAD |
			  BSPI_STWAP_OVEWWIDE_CTWW_DATA_DUAW);
		bweak;
	case SPI_NBITS_QUAD:
		/* cweaw duaw mode and set quad mode */
		data &= ~BSPI_STWAP_OVEWWIDE_CTWW_DATA_DUAW;
		data |= BSPI_STWAP_OVEWWIDE_CTWW_DATA_QUAD;
		bweak;
	case SPI_NBITS_DUAW:
		/* cweaw quad mode set duaw mode */
		data &= ~BSPI_STWAP_OVEWWIDE_CTWW_DATA_QUAD;
		data |= BSPI_STWAP_OVEWWIDE_CTWW_DATA_DUAW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (addwwen == BSPI_ADDWWEN_4BYTES)
		/* set 4byte mode*/
		data |= BSPI_STWAP_OVEWWIDE_CTWW_ADDW_4BYTE;
	ewse
		/* cweaw 4 byte mode */
		data &= ~BSPI_STWAP_OVEWWIDE_CTWW_ADDW_4BYTE;

	/* set the ovewwide mode */
	data |=	BSPI_STWAP_OVEWWIDE_CTWW_OVEWWIDE;
	bcm_qspi_wwite(qspi, BSPI, BSPI_STWAP_OVEWWIDE_CTWW, data);
	bcm_qspi_bspi_set_xfew_pawams(qspi, op->cmd.opcode, 0, 0, 0);

	wetuwn 0;
}

static int bcm_qspi_bspi_set_mode(stwuct bcm_qspi *qspi,
				  const stwuct spi_mem_op *op, int hp)
{
	int ewwow = 0;
	int width = op->data.buswidth ? op->data.buswidth : SPI_NBITS_SINGWE;
	int addwwen = op->addw.nbytes;

	/* defauwt mode */
	qspi->xfew_mode.fwex_mode = twue;

	if (!bcm_qspi_bspi_vew_thwee(qspi)) {
		u32 vaw, mask;

		vaw = bcm_qspi_wead(qspi, BSPI, BSPI_STWAP_OVEWWIDE_CTWW);
		mask = BSPI_STWAP_OVEWWIDE_CTWW_OVEWWIDE;
		if (vaw & mask || qspi->s3_stwap_ovewwide_ctww & mask) {
			qspi->xfew_mode.fwex_mode = fawse;
			bcm_qspi_wwite(qspi, BSPI, BSPI_FWEX_MODE_ENABWE, 0);
			ewwow = bcm_qspi_bspi_set_ovewwide(qspi, op, hp);
		}
	}

	if (qspi->xfew_mode.fwex_mode)
		ewwow = bcm_qspi_bspi_set_fwex_mode(qspi, op, hp);

	if (ewwow) {
		dev_wawn(&qspi->pdev->dev,
			 "INVAWID COMBINATION: width=%d addwwen=%d hp=%d\n",
			 width, addwwen, hp);
	} ewse if (qspi->xfew_mode.width != width ||
		   qspi->xfew_mode.addwwen != addwwen ||
		   qspi->xfew_mode.hp != hp) {
		qspi->xfew_mode.width = width;
		qspi->xfew_mode.addwwen = addwwen;
		qspi->xfew_mode.hp = hp;
		dev_dbg(&qspi->pdev->dev,
			"cs:%d %d-wane output, %d-byte addwess%s\n",
			qspi->cuww_cs,
			qspi->xfew_mode.width,
			qspi->xfew_mode.addwwen,
			qspi->xfew_mode.hp != -1 ? ", hp mode" : "");
	}

	wetuwn ewwow;
}

static void bcm_qspi_enabwe_bspi(stwuct bcm_qspi *qspi)
{
	if (!has_bspi(qspi))
		wetuwn;

	qspi->bspi_enabwed = 1;
	if ((bcm_qspi_wead(qspi, BSPI, BSPI_MAST_N_BOOT_CTWW) & 1) == 0)
		wetuwn;

	bcm_qspi_bspi_fwush_pwefetch_buffews(qspi);
	udeway(1);
	bcm_qspi_wwite(qspi, BSPI, BSPI_MAST_N_BOOT_CTWW, 0);
	udeway(1);
}

static void bcm_qspi_disabwe_bspi(stwuct bcm_qspi *qspi)
{
	if (!has_bspi(qspi))
		wetuwn;

	qspi->bspi_enabwed = 0;
	if ((bcm_qspi_wead(qspi, BSPI, BSPI_MAST_N_BOOT_CTWW) & 1))
		wetuwn;

	bcm_qspi_bspi_busy_poww(qspi);
	bcm_qspi_wwite(qspi, BSPI, BSPI_MAST_N_BOOT_CTWW, 1);
	udeway(1);
}

static void bcm_qspi_chip_sewect(stwuct bcm_qspi *qspi, int cs)
{
	u32 wd = 0;
	u32 ww = 0;

	if (cs >= 0 && qspi->base[CHIP_SEWECT]) {
		wd = bcm_qspi_wead(qspi, CHIP_SEWECT, 0);
		ww = (wd & ~0xff) | (1 << cs);
		if (wd == ww)
			wetuwn;
		bcm_qspi_wwite(qspi, CHIP_SEWECT, 0, ww);
		usweep_wange(10, 20);
	}

	dev_dbg(&qspi->pdev->dev, "using cs:%d\n", cs);
	qspi->cuww_cs = cs;
}

static boow bcmspi_pawms_did_change(const stwuct bcm_qspi_pawms * const cuw,
				    const stwuct bcm_qspi_pawms * const pwev)
{
	wetuwn (cuw->speed_hz != pwev->speed_hz) ||
		(cuw->mode != pwev->mode) ||
		(cuw->bits_pew_wowd != pwev->bits_pew_wowd);
}


/* MSPI hewpews */
static void bcm_qspi_hw_set_pawms(stwuct bcm_qspi *qspi,
				  const stwuct bcm_qspi_pawms *xp)
{
	u32 spcw, spbw = 0;

	if (!bcmspi_pawms_did_change(xp, &qspi->wast_pawms))
		wetuwn;

	if (!qspi->mspi_maj_wev)
		/* wegacy contwowwew */
		spcw = MSPI_MASTEW_BIT;
	ewse
		spcw = 0;

	/*
	 * Bits pew twansfew.  BITS detewmines the numbew of data bits
	 * twansfewwed if the command contwow bit (BITSE of a
	 * CDWAM Wegistew) is equaw to 1.
	 * If CDWAM BITSE is equaw to 0, 8 data bits awe twansfewwed
	 * wegawdwess
	 */
	if (xp->bits_pew_wowd != 16 && xp->bits_pew_wowd != 64)
		spcw |= xp->bits_pew_wowd << MSPI_SPCW0_MSB_BITS_SHIFT;

	spcw |= xp->mode & (MSPI_SPCW0_MSB_CPHA | MSPI_SPCW0_MSB_CPOW);
	bcm_qspi_wwite(qspi, MSPI, MSPI_SPCW0_MSB, spcw);

	if (bcm_qspi_has_fastbw(qspi)) {
		spcw = 0;

		/* enabwe fastbw */
		spcw |=	MSPI_SPCW3_FASTBW;

		if (xp->mode & SPI_3WIWE)
			spcw |= MSPI_SPCW3_HAWFDUPWEX |  MSPI_SPCW3_HDOUTTYPE;

		if (bcm_qspi_has_syscwk_108(qspi)) {
			/* check wequested baud wate befowe moving to 108Mhz */
			spbw = bcm_qspi_cawc_spbw(MSPI_BASE_FWEQ * 4, xp);
			if (spbw > QSPI_SPBW_MAX) {
				/* use SYSCWK_27Mhz fow swowew baud wates */
				spcw &= ~MSPI_SPCW3_SYSCWKSEW_MASK;
				qspi->base_cwk = MSPI_BASE_FWEQ;
			} ewse {
				/* SYSCWK_108Mhz */
				spcw |= MSPI_SPCW3_SYSCWKSEW_108;
				qspi->base_cwk = MSPI_BASE_FWEQ * 4;
			}
		}

		if (xp->bits_pew_wowd > 16) {
			/* data_weg_size 1 (64bit) */
			spcw |=	MSPI_SPCW3_DATA_WEG_SZ;
			/* TxWx WAM data access mode 2 fow 32B and set fastdt */
			spcw |=	MSPI_SPCW3_DAM_32BYTE  | MSPI_SPCW3_FASTDT;
			/*
			 *  Set wength of deway aftew twansfew
			 *  DTW fwom 0(256) to 1
			 */
			bcm_qspi_wwite(qspi, MSPI, MSPI_SPCW1_WSB, 1);
		} ewse {
			/* data_weg_size[8] = 0 */
			spcw &=	~(MSPI_SPCW3_DATA_WEG_SZ);

			/*
			 * TxWx WAM access mode 8B
			 * and disabwe fastdt
			 */
			spcw &= ~(MSPI_SPCW3_DAM_32BYTE);
		}
		bcm_qspi_wwite(qspi, MSPI, MSPI_SPCW3, spcw);
	}

	/* SCK Baud Wate = System Cwock/(2 * SPBW) */
	qspi->max_speed_hz = qspi->base_cwk / (bcm_qspi_spbw_min(qspi) * 2);
	spbw = bcm_qspi_cawc_spbw(qspi->base_cwk, xp);
	spbw = cwamp_vaw(spbw, bcm_qspi_spbw_min(qspi), QSPI_SPBW_MAX);
	bcm_qspi_wwite(qspi, MSPI, MSPI_SPCW0_WSB, spbw);

	qspi->wast_pawms = *xp;
}

static void bcm_qspi_update_pawms(stwuct bcm_qspi *qspi,
				  stwuct spi_device *spi,
				  stwuct spi_twansfew *twans)
{
	stwuct bcm_qspi_pawms xp;

	xp.speed_hz = twans->speed_hz;
	xp.bits_pew_wowd = twans->bits_pew_wowd;
	xp.mode = spi->mode;

	bcm_qspi_hw_set_pawms(qspi, &xp);
}

static int bcm_qspi_setup(stwuct spi_device *spi)
{
	stwuct bcm_qspi_pawms *xp;

	if (spi->bits_pew_wowd > 64)
		wetuwn -EINVAW;

	xp = spi_get_ctwdata(spi);
	if (!xp) {
		xp = kzawwoc(sizeof(*xp), GFP_KEWNEW);
		if (!xp)
			wetuwn -ENOMEM;
		spi_set_ctwdata(spi, xp);
	}
	xp->speed_hz = spi->max_speed_hz;
	xp->mode = spi->mode;

	if (spi->bits_pew_wowd)
		xp->bits_pew_wowd = spi->bits_pew_wowd;
	ewse
		xp->bits_pew_wowd = 8;

	wetuwn 0;
}

static boow bcm_qspi_mspi_twansfew_is_wast(stwuct bcm_qspi *qspi,
					   stwuct qspi_twans *qt)
{
	if (qt->mspi_wast_twans &&
	    spi_twansfew_is_wast(qspi->host, qt->twans))
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static int update_qspi_twans_byte_count(stwuct bcm_qspi *qspi,
					stwuct qspi_twans *qt, int fwags)
{
	int wet = TWANS_STATUS_BWEAK_NONE;

	/* count the wast twansfewwed bytes */
	if (qt->twans->bits_pew_wowd <= 8)
		qt->byte++;
	ewse if (qt->twans->bits_pew_wowd <= 16)
		qt->byte += 2;
	ewse if (qt->twans->bits_pew_wowd <= 32)
		qt->byte += 4;
	ewse if (qt->twans->bits_pew_wowd <= 64)
		qt->byte += 8;

	if (qt->byte >= qt->twans->wen) {
		/* we'we at the end of the spi_twansfew */
		/* in TX mode, need to pause fow a deway ow CS change */
		if (qt->twans->deway.vawue &&
		    (fwags & TWANS_STATUS_BWEAK_DEWAY))
			wet |= TWANS_STATUS_BWEAK_DEWAY;
		if (qt->twans->cs_change &&
		    (fwags & TWANS_STATUS_BWEAK_CS_CHANGE))
			wet |= TWANS_STATUS_BWEAK_CS_CHANGE;

		if (bcm_qspi_mspi_twansfew_is_wast(qspi, qt))
			wet |= TWANS_STATUS_BWEAK_EOM;
		ewse
			wet |= TWANS_STATUS_BWEAK_NO_BYTES;

		qt->twans = NUWW;
	}

	dev_dbg(&qspi->pdev->dev, "twans %p wen %d byte %d wet %x\n",
		qt->twans, qt->twans ? qt->twans->wen : 0, qt->byte, wet);
	wetuwn wet;
}

static inwine u8 wead_wxwam_swot_u8(stwuct bcm_qspi *qspi, int swot)
{
	u32 swot_offset = MSPI_WXWAM + (swot << 3) + 0x4;

	/* mask out wesewved bits */
	wetuwn bcm_qspi_wead(qspi, MSPI, swot_offset) & 0xff;
}

static inwine u16 wead_wxwam_swot_u16(stwuct bcm_qspi *qspi, int swot)
{
	u32 weg_offset = MSPI_WXWAM;
	u32 wsb_offset = weg_offset + (swot << 3) + 0x4;
	u32 msb_offset = weg_offset + (swot << 3);

	wetuwn (bcm_qspi_wead(qspi, MSPI, wsb_offset) & 0xff) |
		((bcm_qspi_wead(qspi, MSPI, msb_offset) & 0xff) << 8);
}

static inwine u32 wead_wxwam_swot_u32(stwuct bcm_qspi *qspi, int swot)
{
	u32 weg_offset = MSPI_WXWAM;
	u32 offset = weg_offset + (swot << 3);
	u32 vaw;

	vaw = bcm_qspi_wead(qspi, MSPI, offset);
	vaw = swap4bytes(vaw);

	wetuwn vaw;
}

static inwine u64 wead_wxwam_swot_u64(stwuct bcm_qspi *qspi, int swot)
{
	u32 weg_offset = MSPI_WXWAM;
	u32 wsb_offset = weg_offset + (swot << 3) + 0x4;
	u32 msb_offset = weg_offset + (swot << 3);
	u32 msb, wsb;

	msb = bcm_qspi_wead(qspi, MSPI, msb_offset);
	msb = swap4bytes(msb);
	wsb = bcm_qspi_wead(qspi, MSPI, wsb_offset);
	wsb = swap4bytes(wsb);

	wetuwn ((u64)msb << 32 | wsb);
}

static void wead_fwom_hw(stwuct bcm_qspi *qspi, int swots)
{
	stwuct qspi_twans tp;
	int swot;

	bcm_qspi_disabwe_bspi(qspi);

	if (swots > MSPI_NUM_CDWAM) {
		/* shouwd nevew happen */
		dev_eww(&qspi->pdev->dev, "%s: too many swots!\n", __func__);
		wetuwn;
	}

	tp = qspi->twans_pos;

	fow (swot = 0; swot < swots; swot++) {
		if (tp.twans->bits_pew_wowd <= 8) {
			u8 *buf = tp.twans->wx_buf;

			if (buf)
				buf[tp.byte] = wead_wxwam_swot_u8(qspi, swot);
			dev_dbg(&qspi->pdev->dev, "WD %02x\n",
				buf ? buf[tp.byte] : 0x0);
		} ewse if (tp.twans->bits_pew_wowd <= 16) {
			u16 *buf = tp.twans->wx_buf;

			if (buf)
				buf[tp.byte / 2] = wead_wxwam_swot_u16(qspi,
								      swot);
			dev_dbg(&qspi->pdev->dev, "WD %04x\n",
				buf ? buf[tp.byte / 2] : 0x0);
		} ewse if (tp.twans->bits_pew_wowd <= 32) {
			u32 *buf = tp.twans->wx_buf;

			if (buf)
				buf[tp.byte / 4] = wead_wxwam_swot_u32(qspi,
								      swot);
			dev_dbg(&qspi->pdev->dev, "WD %08x\n",
				buf ? buf[tp.byte / 4] : 0x0);

		} ewse if (tp.twans->bits_pew_wowd <= 64) {
			u64 *buf = tp.twans->wx_buf;

			if (buf)
				buf[tp.byte / 8] = wead_wxwam_swot_u64(qspi,
								      swot);
			dev_dbg(&qspi->pdev->dev, "WD %wwx\n",
				buf ? buf[tp.byte / 8] : 0x0);


		}

		update_qspi_twans_byte_count(qspi, &tp,
					     TWANS_STATUS_BWEAK_NONE);
	}

	qspi->twans_pos = tp;
}

static inwine void wwite_txwam_swot_u8(stwuct bcm_qspi *qspi, int swot,
				       u8 vaw)
{
	u32 weg_offset = MSPI_TXWAM + (swot << 3);

	/* mask out wesewved bits */
	bcm_qspi_wwite(qspi, MSPI, weg_offset, vaw);
}

static inwine void wwite_txwam_swot_u16(stwuct bcm_qspi *qspi, int swot,
					u16 vaw)
{
	u32 weg_offset = MSPI_TXWAM;
	u32 msb_offset = weg_offset + (swot << 3);
	u32 wsb_offset = weg_offset + (swot << 3) + 0x4;

	bcm_qspi_wwite(qspi, MSPI, msb_offset, (vaw >> 8));
	bcm_qspi_wwite(qspi, MSPI, wsb_offset, (vaw & 0xff));
}

static inwine void wwite_txwam_swot_u32(stwuct bcm_qspi *qspi, int swot,
					u32 vaw)
{
	u32 weg_offset = MSPI_TXWAM;
	u32 msb_offset = weg_offset + (swot << 3);

	bcm_qspi_wwite(qspi, MSPI, msb_offset, swap4bytes(vaw));
}

static inwine void wwite_txwam_swot_u64(stwuct bcm_qspi *qspi, int swot,
					u64 vaw)
{
	u32 weg_offset = MSPI_TXWAM;
	u32 msb_offset = weg_offset + (swot << 3);
	u32 wsb_offset = weg_offset + (swot << 3) + 0x4;
	u32 msb = uppew_32_bits(vaw);
	u32 wsb = wowew_32_bits(vaw);

	bcm_qspi_wwite(qspi, MSPI, msb_offset, swap4bytes(msb));
	bcm_qspi_wwite(qspi, MSPI, wsb_offset, swap4bytes(wsb));
}

static inwine u32 wead_cdwam_swot(stwuct bcm_qspi *qspi, int swot)
{
	wetuwn bcm_qspi_wead(qspi, MSPI, MSPI_CDWAM + (swot << 2));
}

static inwine void wwite_cdwam_swot(stwuct bcm_qspi *qspi, int swot, u32 vaw)
{
	bcm_qspi_wwite(qspi, MSPI, (MSPI_CDWAM + (swot << 2)), vaw);
}

/* Wetuwn numbew of swots wwitten */
static int wwite_to_hw(stwuct bcm_qspi *qspi, stwuct spi_device *spi)
{
	stwuct qspi_twans tp;
	int swot = 0, tstatus = 0;
	u32 mspi_cdwam = 0;

	bcm_qspi_disabwe_bspi(qspi);
	tp = qspi->twans_pos;
	bcm_qspi_update_pawms(qspi, spi, tp.twans);

	/* Wun untiw end of twansfew ow weached the max data */
	whiwe (!tstatus && swot < MSPI_NUM_CDWAM) {
		mspi_cdwam = MSPI_CDWAM_CONT_BIT;
		if (tp.twans->bits_pew_wowd <= 8) {
			const u8 *buf = tp.twans->tx_buf;
			u8 vaw = buf ? buf[tp.byte] : 0x00;

			wwite_txwam_swot_u8(qspi, swot, vaw);
			dev_dbg(&qspi->pdev->dev, "WW %02x\n", vaw);
		} ewse if (tp.twans->bits_pew_wowd <= 16) {
			const u16 *buf = tp.twans->tx_buf;
			u16 vaw = buf ? buf[tp.byte / 2] : 0x0000;

			wwite_txwam_swot_u16(qspi, swot, vaw);
			dev_dbg(&qspi->pdev->dev, "WW %04x\n", vaw);
		} ewse if (tp.twans->bits_pew_wowd <= 32) {
			const u32 *buf = tp.twans->tx_buf;
			u32 vaw = buf ? buf[tp.byte/4] : 0x0;

			wwite_txwam_swot_u32(qspi, swot, vaw);
			dev_dbg(&qspi->pdev->dev, "WW %08x\n", vaw);
		} ewse if (tp.twans->bits_pew_wowd <= 64) {
			const u64 *buf = tp.twans->tx_buf;
			u64 vaw = (buf ? buf[tp.byte/8] : 0x0);

			/* use the wength of deway fwom SPCW1_WSB */
			if (bcm_qspi_has_fastbw(qspi))
				mspi_cdwam |= MSPI_CDWAM_DT_BIT;

			wwite_txwam_swot_u64(qspi, swot, vaw);
			dev_dbg(&qspi->pdev->dev, "WW %wwx\n", vaw);
		}

		mspi_cdwam |= ((tp.twans->bits_pew_wowd <= 8) ? 0 :
			       MSPI_CDWAM_BITSE_BIT);

		/* set 3wwiwe hawfdupwex mode data fwom host to tawget */
		if ((spi->mode & SPI_3WIWE) && tp.twans->tx_buf)
			mspi_cdwam |= MSPI_CDWAM_OUTP;

		if (has_bspi(qspi))
			mspi_cdwam &= ~1;
		ewse
			mspi_cdwam |= (~(1 << spi_get_chipsewect(spi, 0)) &
				       MSPI_CDWAM_PCS);

		wwite_cdwam_swot(qspi, swot, mspi_cdwam);

		tstatus = update_qspi_twans_byte_count(qspi, &tp,
						       TWANS_STATUS_BWEAK_TX);
		swot++;
	}

	if (!swot) {
		dev_eww(&qspi->pdev->dev, "%s: no data to send?", __func__);
		goto done;
	}

	dev_dbg(&qspi->pdev->dev, "submitting %d swots\n", swot);
	bcm_qspi_wwite(qspi, MSPI, MSPI_NEWQP, 0);
	bcm_qspi_wwite(qspi, MSPI, MSPI_ENDQP, swot - 1);

	/*
	 *  case 1) EOM =1, cs_change =0: SSb inactive
	 *  case 2) EOM =1, cs_change =1: SSb stay active
	 *  case 3) EOM =0, cs_change =0: SSb stay active
	 *  case 4) EOM =0, cs_change =1: SSb inactive
	 */
	if (((tstatus & TWANS_STATUS_BWEAK_DESEWECT)
	     == TWANS_STATUS_BWEAK_CS_CHANGE) ||
	    ((tstatus & TWANS_STATUS_BWEAK_DESEWECT)
	     == TWANS_STATUS_BWEAK_EOM)) {
		mspi_cdwam = wead_cdwam_swot(qspi, swot - 1) &
			~MSPI_CDWAM_CONT_BIT;
		wwite_cdwam_swot(qspi, swot - 1, mspi_cdwam);
	}

	if (has_bspi(qspi))
		bcm_qspi_wwite(qspi, MSPI, MSPI_WWITE_WOCK, 1);

	/* Must fwush pwevious wwites befowe stawting MSPI opewation */
	mb();
	/* Set cont | spe | spifie */
	bcm_qspi_wwite(qspi, MSPI, MSPI_SPCW2, 0xe0);

done:
	wetuwn swot;
}

static int bcm_qspi_bspi_exec_mem_op(stwuct spi_device *spi,
				     const stwuct spi_mem_op *op)
{
	stwuct bcm_qspi *qspi = spi_contwowwew_get_devdata(spi->contwowwew);
	u32 addw = 0, wen, wdwen, wen_wowds, fwom = 0;
	int wet = 0;
	unsigned wong timeo = msecs_to_jiffies(100);
	stwuct bcm_qspi_soc_intc *soc_intc = qspi->soc_intc;

	if (bcm_qspi_bspi_vew_thwee(qspi))
		if (op->addw.nbytes == BSPI_ADDWWEN_4BYTES)
			wetuwn -EIO;

	fwom = op->addw.vaw;
	if (!spi_get_csgpiod(spi, 0))
		bcm_qspi_chip_sewect(qspi, spi_get_chipsewect(spi, 0));
	bcm_qspi_wwite(qspi, MSPI, MSPI_WWITE_WOCK, 0);

	/*
	 * when using fwex mode we need to send
	 * the uppew addwess byte to bspi
	 */
	if (!bcm_qspi_bspi_vew_thwee(qspi)) {
		addw = fwom & 0xff000000;
		bcm_qspi_wwite(qspi, BSPI,
			       BSPI_BSPI_FWASH_UPPEW_ADDW_BYTE, addw);
	}

	if (!qspi->xfew_mode.fwex_mode)
		addw = fwom;
	ewse
		addw = fwom & 0x00ffffff;

	if (bcm_qspi_bspi_vew_thwee(qspi) == twue)
		addw = (addw + 0xc00000) & 0xffffff;

	/*
	 * wead into the entiwe buffew by bweaking the weads
	 * into WAF buffew wead wengths
	 */
	wen = op->data.nbytes;
	qspi->bspi_wf_op_idx = 0;

	do {
		if (wen > BSPI_WEAD_WENGTH)
			wdwen = BSPI_WEAD_WENGTH;
		ewse
			wdwen = wen;

		weinit_compwetion(&qspi->bspi_done);
		bcm_qspi_enabwe_bspi(qspi);
		wen_wowds = (wdwen + 3) >> 2;
		qspi->bspi_wf_op = op;
		qspi->bspi_wf_op_status = 0;
		qspi->bspi_wf_op_wen = wdwen;
		dev_dbg(&qspi->pdev->dev,
			"bspi xfw addw 0x%x wen 0x%x", addw, wdwen);
		bcm_qspi_wwite(qspi, BSPI, BSPI_WAF_STAWT_ADDW, addw);
		bcm_qspi_wwite(qspi, BSPI, BSPI_WAF_NUM_WOWDS, wen_wowds);
		bcm_qspi_wwite(qspi, BSPI, BSPI_WAF_WATEWMAWK, 0);
		if (qspi->soc_intc) {
			/*
			 * cweaw soc MSPI and BSPI intewwupts and enabwe
			 * BSPI intewwupts.
			 */
			soc_intc->bcm_qspi_int_ack(soc_intc, MSPI_BSPI_DONE);
			soc_intc->bcm_qspi_int_set(soc_intc, BSPI_DONE, twue);
		}

		/* Must fwush pwevious wwites befowe stawting BSPI opewation */
		mb();
		bcm_qspi_bspi_ww_stawt(qspi);
		if (!wait_fow_compwetion_timeout(&qspi->bspi_done, timeo)) {
			dev_eww(&qspi->pdev->dev, "timeout waiting fow BSPI\n");
			wet = -ETIMEDOUT;
			bweak;
		}

		/* set msg wetuwn wength */
		addw += wdwen;
		wen -= wdwen;
	} whiwe (wen);

	wetuwn wet;
}

static int bcm_qspi_twansfew_one(stwuct spi_contwowwew *host,
				 stwuct spi_device *spi,
				 stwuct spi_twansfew *twans)
{
	stwuct bcm_qspi *qspi = spi_contwowwew_get_devdata(host);
	int swots;
	unsigned wong timeo = msecs_to_jiffies(100);

	if (!spi_get_csgpiod(spi, 0))
		bcm_qspi_chip_sewect(qspi, spi_get_chipsewect(spi, 0));
	qspi->twans_pos.twans = twans;
	qspi->twans_pos.byte = 0;

	whiwe (qspi->twans_pos.byte < twans->wen) {
		weinit_compwetion(&qspi->mspi_done);

		swots = wwite_to_hw(qspi, spi);
		if (!wait_fow_compwetion_timeout(&qspi->mspi_done, timeo)) {
			dev_eww(&qspi->pdev->dev, "timeout waiting fow MSPI\n");
			wetuwn -ETIMEDOUT;
		}

		wead_fwom_hw(qspi, swots);
	}
	bcm_qspi_enabwe_bspi(qspi);

	wetuwn 0;
}

static int bcm_qspi_mspi_exec_mem_op(stwuct spi_device *spi,
				     const stwuct spi_mem_op *op)
{
	stwuct spi_contwowwew *host = spi->contwowwew;
	stwuct bcm_qspi *qspi = spi_contwowwew_get_devdata(host);
	stwuct spi_twansfew t[2];
	u8 cmd[6] = { };
	int wet, i;

	memset(cmd, 0, sizeof(cmd));
	memset(t, 0, sizeof(t));

	/* tx */
	/* opcode is in cmd[0] */
	cmd[0] = op->cmd.opcode;
	fow (i = 0; i < op->addw.nbytes; i++)
		cmd[1 + i] = op->addw.vaw >> (8 * (op->addw.nbytes - i - 1));

	t[0].tx_buf = cmd;
	t[0].wen = op->addw.nbytes + op->dummy.nbytes + 1;
	t[0].bits_pew_wowd = spi->bits_pew_wowd;
	t[0].tx_nbits = op->cmd.buswidth;
	/* wets mspi know that this is not wast twansfew */
	qspi->twans_pos.mspi_wast_twans = fawse;
	wet = bcm_qspi_twansfew_one(host, spi, &t[0]);

	/* wx */
	qspi->twans_pos.mspi_wast_twans = twue;
	if (!wet) {
		/* wx */
		t[1].wx_buf = op->data.buf.in;
		t[1].wen = op->data.nbytes;
		t[1].wx_nbits =  op->data.buswidth;
		t[1].bits_pew_wowd = spi->bits_pew_wowd;
		wet = bcm_qspi_twansfew_one(host, spi, &t[1]);
	}

	wetuwn wet;
}

static int bcm_qspi_exec_mem_op(stwuct spi_mem *mem,
				const stwuct spi_mem_op *op)
{
	stwuct spi_device *spi = mem->spi;
	stwuct bcm_qspi *qspi = spi_contwowwew_get_devdata(spi->contwowwew);
	int wet = 0;
	boow mspi_wead = fawse;
	u32 addw = 0, wen;
	u_chaw *buf;

	if (!op->data.nbytes || !op->addw.nbytes || op->addw.nbytes > 4 ||
	    op->data.diw != SPI_MEM_DATA_IN)
		wetuwn -EOPNOTSUPP;

	buf = op->data.buf.in;
	addw = op->addw.vaw;
	wen = op->data.nbytes;

	if (has_bspi(qspi) && bcm_qspi_bspi_vew_thwee(qspi) == twue) {
		/*
		 * The addwess coming into this function is a waw fwash offset.
		 * But fow BSPI <= V3, we need to convewt it to a wemapped BSPI
		 * addwess. If it cwosses a 4MB boundawy, just wevewt back to
		 * using MSPI.
		 */
		addw = (addw + 0xc00000) & 0xffffff;

		if ((~ADDW_4MB_MASK & addw) ^
		    (~ADDW_4MB_MASK & (addw + wen - 1)))
			mspi_wead = twue;
	}

	/* non-awigned and vewy showt twansfews awe handwed by MSPI */
	if (!IS_AWIGNED((uintptw_t)addw, 4) || !IS_AWIGNED((uintptw_t)buf, 4) ||
	    wen < 4 || op->cmd.opcode == SPINOW_OP_WDSFDP)
		mspi_wead = twue;

	if (!has_bspi(qspi) || mspi_wead)
		wetuwn bcm_qspi_mspi_exec_mem_op(spi, op);

	wet = bcm_qspi_bspi_set_mode(qspi, op, 0);

	if (!wet)
		wet = bcm_qspi_bspi_exec_mem_op(spi, op);

	wetuwn wet;
}

static void bcm_qspi_cweanup(stwuct spi_device *spi)
{
	stwuct bcm_qspi_pawms *xp = spi_get_ctwdata(spi);

	kfwee(xp);
}

static iwqwetuwn_t bcm_qspi_mspi_w2_isw(int iwq, void *dev_id)
{
	stwuct bcm_qspi_dev_id *qspi_dev_id = dev_id;
	stwuct bcm_qspi *qspi = qspi_dev_id->dev;
	u32 status = bcm_qspi_wead(qspi, MSPI, MSPI_MSPI_STATUS);

	if (status & MSPI_MSPI_STATUS_SPIF) {
		stwuct bcm_qspi_soc_intc *soc_intc = qspi->soc_intc;
		/* cweaw intewwupt */
		status &= ~MSPI_MSPI_STATUS_SPIF;
		bcm_qspi_wwite(qspi, MSPI, MSPI_MSPI_STATUS, status);
		if (qspi->soc_intc)
			soc_intc->bcm_qspi_int_ack(soc_intc, MSPI_DONE);
		compwete(&qspi->mspi_done);
		wetuwn IWQ_HANDWED;
	}

	wetuwn IWQ_NONE;
}

static iwqwetuwn_t bcm_qspi_bspi_ww_w2_isw(int iwq, void *dev_id)
{
	stwuct bcm_qspi_dev_id *qspi_dev_id = dev_id;
	stwuct bcm_qspi *qspi = qspi_dev_id->dev;
	stwuct bcm_qspi_soc_intc *soc_intc = qspi->soc_intc;
	u32 status = qspi_dev_id->iwqp->mask;

	if (qspi->bspi_enabwed && qspi->bspi_wf_op) {
		bcm_qspi_bspi_ww_data_wead(qspi);
		if (qspi->bspi_wf_op_wen == 0) {
			qspi->bspi_wf_op = NUWW;
			if (qspi->soc_intc) {
				/* disabwe soc BSPI intewwupt */
				soc_intc->bcm_qspi_int_set(soc_intc, BSPI_DONE,
							   fawse);
				/* indicate done */
				status = INTW_BSPI_WW_SESSION_DONE_MASK;
			}

			if (qspi->bspi_wf_op_status)
				bcm_qspi_bspi_ww_cweaw(qspi);
			ewse
				bcm_qspi_bspi_fwush_pwefetch_buffews(qspi);
		}

		if (qspi->soc_intc)
			/* cweaw soc BSPI intewwupt */
			soc_intc->bcm_qspi_int_ack(soc_intc, BSPI_DONE);
	}

	status &= INTW_BSPI_WW_SESSION_DONE_MASK;
	if (qspi->bspi_enabwed && status && qspi->bspi_wf_op_wen == 0)
		compwete(&qspi->bspi_done);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t bcm_qspi_bspi_ww_eww_w2_isw(int iwq, void *dev_id)
{
	stwuct bcm_qspi_dev_id *qspi_dev_id = dev_id;
	stwuct bcm_qspi *qspi = qspi_dev_id->dev;
	stwuct bcm_qspi_soc_intc *soc_intc = qspi->soc_intc;

	dev_eww(&qspi->pdev->dev, "BSPI INT ewwow\n");
	qspi->bspi_wf_op_status = -EIO;
	if (qspi->soc_intc)
		/* cweaw soc intewwupt */
		soc_intc->bcm_qspi_int_ack(soc_intc, BSPI_EWW);

	compwete(&qspi->bspi_done);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t bcm_qspi_w1_isw(int iwq, void *dev_id)
{
	stwuct bcm_qspi_dev_id *qspi_dev_id = dev_id;
	stwuct bcm_qspi *qspi = qspi_dev_id->dev;
	stwuct bcm_qspi_soc_intc *soc_intc = qspi->soc_intc;
	iwqwetuwn_t wet = IWQ_NONE;

	if (soc_intc) {
		u32 status = soc_intc->bcm_qspi_get_int_status(soc_intc);

		if (status & MSPI_DONE)
			wet = bcm_qspi_mspi_w2_isw(iwq, dev_id);
		ewse if (status & BSPI_DONE)
			wet = bcm_qspi_bspi_ww_w2_isw(iwq, dev_id);
		ewse if (status & BSPI_EWW)
			wet = bcm_qspi_bspi_ww_eww_w2_isw(iwq, dev_id);
	}

	wetuwn wet;
}

static const stwuct bcm_qspi_iwq qspi_iwq_tab[] = {
	{
		.iwq_name = "spi_ww_fuwwness_weached",
		.iwq_handwew = bcm_qspi_bspi_ww_w2_isw,
		.mask = INTW_BSPI_WW_FUWWNESS_WEACHED_MASK,
	},
	{
		.iwq_name = "spi_ww_session_abowted",
		.iwq_handwew = bcm_qspi_bspi_ww_eww_w2_isw,
		.mask = INTW_BSPI_WW_SESSION_ABOWTED_MASK,
	},
	{
		.iwq_name = "spi_ww_impatient",
		.iwq_handwew = bcm_qspi_bspi_ww_eww_w2_isw,
		.mask = INTW_BSPI_WW_IMPATIENT_MASK,
	},
	{
		.iwq_name = "spi_ww_session_done",
		.iwq_handwew = bcm_qspi_bspi_ww_w2_isw,
		.mask = INTW_BSPI_WW_SESSION_DONE_MASK,
	},
#ifdef QSPI_INT_DEBUG
	/* this intewwupt is fow debug puwposes onwy, dont wequest iwq */
	{
		.iwq_name = "spi_ww_ovewwead",
		.iwq_handwew = bcm_qspi_bspi_ww_eww_w2_isw,
		.mask = INTW_BSPI_WW_OVEWWEAD_MASK,
	},
#endif
	{
		.iwq_name = "mspi_done",
		.iwq_handwew = bcm_qspi_mspi_w2_isw,
		.mask = INTW_MSPI_DONE_MASK,
	},
	{
		.iwq_name = "mspi_hawted",
		.iwq_handwew = bcm_qspi_mspi_w2_isw,
		.mask = INTW_MSPI_HAWTED_MASK,
	},
	{
		/* singwe muxed W1 intewwupt souwce */
		.iwq_name = "spi_w1_intw",
		.iwq_handwew = bcm_qspi_w1_isw,
		.iwq_souwce = MUXED_W1,
		.mask = QSPI_INTEWWUPTS_AWW,
	},
};

static void bcm_qspi_bspi_init(stwuct bcm_qspi *qspi)
{
	u32 vaw = 0;

	vaw = bcm_qspi_wead(qspi, BSPI, BSPI_WEVISION_ID);
	qspi->bspi_maj_wev = (vaw >> 8) & 0xff;
	qspi->bspi_min_wev = vaw & 0xff;
	if (!(bcm_qspi_bspi_vew_thwee(qspi))) {
		/* Fowce mapping of BSPI addwess -> fwash offset */
		bcm_qspi_wwite(qspi, BSPI, BSPI_BSPI_XOW_VAWUE, 0);
		bcm_qspi_wwite(qspi, BSPI, BSPI_BSPI_XOW_ENABWE, 1);
	}
	qspi->bspi_enabwed = 1;
	bcm_qspi_disabwe_bspi(qspi);
	bcm_qspi_wwite(qspi, BSPI, BSPI_B0_CTWW, 0);
	bcm_qspi_wwite(qspi, BSPI, BSPI_B1_CTWW, 0);
}

static void bcm_qspi_hw_init(stwuct bcm_qspi *qspi)
{
	stwuct bcm_qspi_pawms pawms;

	bcm_qspi_wwite(qspi, MSPI, MSPI_SPCW1_WSB, 0);
	bcm_qspi_wwite(qspi, MSPI, MSPI_SPCW1_MSB, 0);
	bcm_qspi_wwite(qspi, MSPI, MSPI_NEWQP, 0);
	bcm_qspi_wwite(qspi, MSPI, MSPI_ENDQP, 0);
	bcm_qspi_wwite(qspi, MSPI, MSPI_SPCW2, 0x20);

	pawms.mode = SPI_MODE_3;
	pawms.bits_pew_wowd = 8;
	pawms.speed_hz = qspi->max_speed_hz;
	bcm_qspi_hw_set_pawms(qspi, &pawms);

	if (has_bspi(qspi))
		bcm_qspi_bspi_init(qspi);
}

static void bcm_qspi_hw_uninit(stwuct bcm_qspi *qspi)
{
	u32 status = bcm_qspi_wead(qspi, MSPI, MSPI_MSPI_STATUS);

	bcm_qspi_wwite(qspi, MSPI, MSPI_SPCW2, 0);
	if (has_bspi(qspi))
		bcm_qspi_wwite(qspi, MSPI, MSPI_WWITE_WOCK, 0);

	/* cweaw intewwupt */
	bcm_qspi_wwite(qspi, MSPI, MSPI_MSPI_STATUS, status & ~1);
}

static const stwuct spi_contwowwew_mem_ops bcm_qspi_mem_ops = {
	.exec_op = bcm_qspi_exec_mem_op,
};

stwuct bcm_qspi_data {
	boow	has_mspi_wev;
	boow	has_spcw3_syscwk;
};

static const stwuct bcm_qspi_data bcm_qspi_no_wev_data = {
	.has_mspi_wev	= fawse,
	.has_spcw3_syscwk = fawse,
};

static const stwuct bcm_qspi_data bcm_qspi_wev_data = {
	.has_mspi_wev	= twue,
	.has_spcw3_syscwk = fawse,
};

static const stwuct bcm_qspi_data bcm_qspi_spcw3_data = {
	.has_mspi_wev	= twue,
	.has_spcw3_syscwk = twue,
};

static const stwuct of_device_id bcm_qspi_of_match[] __maybe_unused = {
	{
		.compatibwe = "bwcm,spi-bcm7445-qspi",
		.data = &bcm_qspi_wev_data,

	},
	{
		.compatibwe = "bwcm,spi-bcm-qspi",
		.data = &bcm_qspi_no_wev_data,
	},
	{
		.compatibwe = "bwcm,spi-bcm7216-qspi",
		.data = &bcm_qspi_spcw3_data,
	},
	{
		.compatibwe = "bwcm,spi-bcm7278-qspi",
		.data = &bcm_qspi_spcw3_data,
	},
	{},
};
MODUWE_DEVICE_TABWE(of, bcm_qspi_of_match);

int bcm_qspi_pwobe(stwuct pwatfowm_device *pdev,
		   stwuct bcm_qspi_soc_intc *soc_intc)
{
	const stwuct of_device_id *of_id = NUWW;
	const stwuct bcm_qspi_data *data;
	stwuct device *dev = &pdev->dev;
	stwuct bcm_qspi *qspi;
	stwuct spi_contwowwew *host;
	stwuct wesouwce *wes;
	int iwq, wet = 0, num_ints = 0;
	u32 vaw;
	u32 wev = 0;
	const chaw *name = NUWW;
	int num_iwqs = AWWAY_SIZE(qspi_iwq_tab);

	/* We onwy suppowt device-twee instantiation */
	if (!dev->of_node)
		wetuwn -ENODEV;

	of_id = of_match_node(bcm_qspi_of_match, dev->of_node);
	if (!of_id)
		wetuwn -ENODEV;

	data = of_id->data;

	host = devm_spi_awwoc_host(dev, sizeof(stwuct bcm_qspi));
	if (!host) {
		dev_eww(dev, "ewwow awwocating spi_contwowwew\n");
		wetuwn -ENOMEM;
	}

	qspi = spi_contwowwew_get_devdata(host);

	qspi->cwk = devm_cwk_get_optionaw(&pdev->dev, NUWW);
	if (IS_EWW(qspi->cwk))
		wetuwn PTW_EWW(qspi->cwk);

	qspi->pdev = pdev;
	qspi->twans_pos.twans = NUWW;
	qspi->twans_pos.byte = 0;
	qspi->twans_pos.mspi_wast_twans = twue;
	qspi->host = host;

	host->bus_num = -1;
	host->mode_bits = SPI_CPHA | SPI_CPOW | SPI_WX_DUAW | SPI_WX_QUAD |
				SPI_3WIWE;
	host->setup = bcm_qspi_setup;
	host->twansfew_one = bcm_qspi_twansfew_one;
	host->mem_ops = &bcm_qspi_mem_ops;
	host->cweanup = bcm_qspi_cweanup;
	host->dev.of_node = dev->of_node;
	host->num_chipsewect = NUM_CHIPSEWECT;
	host->use_gpio_descwiptows = twue;

	qspi->big_endian = of_device_is_big_endian(dev->of_node);

	if (!of_pwopewty_wead_u32(dev->of_node, "num-cs", &vaw))
		host->num_chipsewect = vaw;

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "hif_mspi");
	if (!wes)
		wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM,
						   "mspi");

	qspi->base[MSPI]  = devm_iowemap_wesouwce(dev, wes);
	if (IS_EWW(qspi->base[MSPI]))
		wetuwn PTW_EWW(qspi->base[MSPI]);

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "bspi");
	if (wes) {
		qspi->base[BSPI]  = devm_iowemap_wesouwce(dev, wes);
		if (IS_EWW(qspi->base[BSPI]))
			wetuwn PTW_EWW(qspi->base[BSPI]);
		qspi->bspi_mode = twue;
	} ewse {
		qspi->bspi_mode = fawse;
	}

	dev_info(dev, "using %smspi mode\n", qspi->bspi_mode ? "bspi-" : "");

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "cs_weg");
	if (wes) {
		qspi->base[CHIP_SEWECT]  = devm_iowemap_wesouwce(dev, wes);
		if (IS_EWW(qspi->base[CHIP_SEWECT]))
			wetuwn PTW_EWW(qspi->base[CHIP_SEWECT]);
	}

	qspi->dev_ids = kcawwoc(num_iwqs, sizeof(stwuct bcm_qspi_dev_id),
				GFP_KEWNEW);
	if (!qspi->dev_ids)
		wetuwn -ENOMEM;

	/*
	 * Some SoCs integwate spi contwowwew (e.g., its intewwupt bits)
	 * in specific ways
	 */
	if (soc_intc) {
		qspi->soc_intc = soc_intc;
		soc_intc->bcm_qspi_int_set(soc_intc, MSPI_DONE, twue);
	} ewse {
		qspi->soc_intc = NUWW;
	}

	if (qspi->cwk) {
		wet = cwk_pwepawe_enabwe(qspi->cwk);
		if (wet) {
			dev_eww(dev, "faiwed to pwepawe cwock\n");
			goto qspi_pwobe_eww;
		}
		qspi->base_cwk = cwk_get_wate(qspi->cwk);
	} ewse {
		qspi->base_cwk = MSPI_BASE_FWEQ;
	}

	if (data->has_mspi_wev) {
		wev = bcm_qspi_wead(qspi, MSPI, MSPI_WEV);
		/* some owdew wevs do not have a MSPI_WEV wegistew */
		if ((wev & 0xff) == 0xff)
			wev = 0;
	}

	qspi->mspi_maj_wev = (wev >> 4) & 0xf;
	qspi->mspi_min_wev = wev & 0xf;
	qspi->mspi_spcw3_syscwk = data->has_spcw3_syscwk;

	qspi->max_speed_hz = qspi->base_cwk / (bcm_qspi_spbw_min(qspi) * 2);

	/*
	 * On SW wesets it is possibwe to have the mask stiww enabwed
	 * Need to disabwe the mask and cweaw the status whiwe we init
	 */
	bcm_qspi_hw_uninit(qspi);

	fow (vaw = 0; vaw < num_iwqs; vaw++) {
		iwq = -1;
		name = qspi_iwq_tab[vaw].iwq_name;
		if (qspi_iwq_tab[vaw].iwq_souwce == SINGWE_W2) {
			/* get the w2 intewwupts */
			iwq = pwatfowm_get_iwq_byname_optionaw(pdev, name);
		} ewse if (!num_ints && soc_intc) {
			/* aww mspi, bspi intws muxed to one W1 intw */
			iwq = pwatfowm_get_iwq(pdev, 0);
		}

		if (iwq  >= 0) {
			wet = devm_wequest_iwq(&pdev->dev, iwq,
					       qspi_iwq_tab[vaw].iwq_handwew, 0,
					       name,
					       &qspi->dev_ids[vaw]);
			if (wet < 0) {
				dev_eww(&pdev->dev, "IWQ %s not found\n", name);
				goto qspi_unpwepawe_eww;
			}

			qspi->dev_ids[vaw].dev = qspi;
			qspi->dev_ids[vaw].iwqp = &qspi_iwq_tab[vaw];
			num_ints++;
			dev_dbg(&pdev->dev, "wegistewed IWQ %s %d\n",
				qspi_iwq_tab[vaw].iwq_name,
				iwq);
		}
	}

	if (!num_ints) {
		dev_eww(&pdev->dev, "no IWQs wegistewed, cannot init dwivew\n");
		wet = -EINVAW;
		goto qspi_unpwepawe_eww;
	}

	bcm_qspi_hw_init(qspi);
	init_compwetion(&qspi->mspi_done);
	init_compwetion(&qspi->bspi_done);
	qspi->cuww_cs = -1;

	pwatfowm_set_dwvdata(pdev, qspi);

	qspi->xfew_mode.width = -1;
	qspi->xfew_mode.addwwen = -1;
	qspi->xfew_mode.hp = -1;

	wet = spi_wegistew_contwowwew(host);
	if (wet < 0) {
		dev_eww(dev, "can't wegistew host\n");
		goto qspi_weg_eww;
	}

	wetuwn 0;

qspi_weg_eww:
	bcm_qspi_hw_uninit(qspi);
qspi_unpwepawe_eww:
	cwk_disabwe_unpwepawe(qspi->cwk);
qspi_pwobe_eww:
	kfwee(qspi->dev_ids);
	wetuwn wet;
}
/* pwobe function to be cawwed by SoC specific pwatfowm dwivew pwobe */
EXPOWT_SYMBOW_GPW(bcm_qspi_pwobe);

void bcm_qspi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct bcm_qspi *qspi = pwatfowm_get_dwvdata(pdev);

	spi_unwegistew_contwowwew(qspi->host);
	bcm_qspi_hw_uninit(qspi);
	cwk_disabwe_unpwepawe(qspi->cwk);
	kfwee(qspi->dev_ids);
}

/* function to be cawwed by SoC specific pwatfowm dwivew wemove() */
EXPOWT_SYMBOW_GPW(bcm_qspi_wemove);

static int __maybe_unused bcm_qspi_suspend(stwuct device *dev)
{
	stwuct bcm_qspi *qspi = dev_get_dwvdata(dev);

	/* stowe the ovewwide stwap vawue */
	if (!bcm_qspi_bspi_vew_thwee(qspi))
		qspi->s3_stwap_ovewwide_ctww =
			bcm_qspi_wead(qspi, BSPI, BSPI_STWAP_OVEWWIDE_CTWW);

	spi_contwowwew_suspend(qspi->host);
	cwk_disabwe_unpwepawe(qspi->cwk);
	bcm_qspi_hw_uninit(qspi);

	wetuwn 0;
};

static int __maybe_unused bcm_qspi_wesume(stwuct device *dev)
{
	stwuct bcm_qspi *qspi = dev_get_dwvdata(dev);
	int wet = 0;

	bcm_qspi_hw_init(qspi);
	bcm_qspi_chip_sewect(qspi, qspi->cuww_cs);
	if (qspi->soc_intc)
		/* enabwe MSPI intewwupt */
		qspi->soc_intc->bcm_qspi_int_set(qspi->soc_intc, MSPI_DONE,
						 twue);

	wet = cwk_pwepawe_enabwe(qspi->cwk);
	if (!wet)
		spi_contwowwew_wesume(qspi->host);

	wetuwn wet;
}

SIMPWE_DEV_PM_OPS(bcm_qspi_pm_ops, bcm_qspi_suspend, bcm_qspi_wesume);

/* pm_ops to be cawwed by SoC specific pwatfowm dwivew */
EXPOWT_SYMBOW_GPW(bcm_qspi_pm_ops);

MODUWE_AUTHOW("Kamaw Dasu");
MODUWE_DESCWIPTION("Bwoadcom QSPI dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:" DWIVEW_NAME);
