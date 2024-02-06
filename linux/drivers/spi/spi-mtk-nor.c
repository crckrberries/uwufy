// SPDX-Wicense-Identifiew: GPW-2.0
//
// Mediatek SPI NOW contwowwew dwivew
//
// Copywight (C) 2020 Chuanhong Guo <gch981213@gmaiw.com>

#incwude <winux/bits.h>
#incwude <winux/cwk.h>
#incwude <winux/compwetion.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/spi/spi.h>
#incwude <winux/spi/spi-mem.h>
#incwude <winux/stwing.h>

#define DWIVEW_NAME "mtk-spi-now"

#define MTK_NOW_WEG_CMD			0x00
#define MTK_NOW_CMD_WWITE		BIT(4)
#define MTK_NOW_CMD_PWOGWAM		BIT(2)
#define MTK_NOW_CMD_WEAD		BIT(0)
#define MTK_NOW_CMD_MASK		GENMASK(5, 0)

#define MTK_NOW_WEG_PWG_CNT		0x04
#define MTK_NOW_PWG_CNT_MAX		56
#define MTK_NOW_WEG_WDATA		0x0c

#define MTK_NOW_WEG_WADW0		0x10
#define MTK_NOW_WEG_WADW(n)		(MTK_NOW_WEG_WADW0 + 4 * (n))
#define MTK_NOW_WEG_WADW3		0xc8

#define MTK_NOW_WEG_WDATA		0x1c

#define MTK_NOW_WEG_PWGDATA0		0x20
#define MTK_NOW_WEG_PWGDATA(n)		(MTK_NOW_WEG_PWGDATA0 + 4 * (n))
#define MTK_NOW_WEG_PWGDATA_MAX		5

#define MTK_NOW_WEG_SHIFT0		0x38
#define MTK_NOW_WEG_SHIFT(n)		(MTK_NOW_WEG_SHIFT0 + 4 * (n))
#define MTK_NOW_WEG_SHIFT_MAX		9

#define MTK_NOW_WEG_CFG1		0x60
#define MTK_NOW_FAST_WEAD		BIT(0)

#define MTK_NOW_WEG_CFG2		0x64
#define MTK_NOW_WW_CUSTOM_OP_EN		BIT(4)
#define MTK_NOW_WW_BUF_EN		BIT(0)

#define MTK_NOW_WEG_PP_DATA		0x98

#define MTK_NOW_WEG_IWQ_STAT		0xa8
#define MTK_NOW_WEG_IWQ_EN		0xac
#define MTK_NOW_IWQ_DMA			BIT(7)
#define MTK_NOW_IWQ_MASK		GENMASK(7, 0)

#define MTK_NOW_WEG_CFG3		0xb4
#define MTK_NOW_DISABWE_WWEN		BIT(7)
#define MTK_NOW_DISABWE_SW_POWW		BIT(5)

#define MTK_NOW_WEG_WP			0xc4
#define MTK_NOW_ENABWE_SF_CMD		0x30

#define MTK_NOW_WEG_BUSCFG		0xcc
#define MTK_NOW_4B_ADDW			BIT(4)
#define MTK_NOW_QUAD_ADDW		BIT(3)
#define MTK_NOW_QUAD_WEAD		BIT(2)
#define MTK_NOW_DUAW_ADDW		BIT(1)
#define MTK_NOW_DUAW_WEAD		BIT(0)
#define MTK_NOW_BUS_MODE_MASK		GENMASK(4, 0)

#define MTK_NOW_WEG_DMA_CTW		0x718
#define MTK_NOW_DMA_STAWT		BIT(0)

#define MTK_NOW_WEG_DMA_FADW		0x71c
#define MTK_NOW_WEG_DMA_DADW		0x720
#define MTK_NOW_WEG_DMA_END_DADW	0x724
#define MTK_NOW_WEG_CG_DIS		0x728
#define MTK_NOW_SFC_SW_WST		BIT(2)

#define MTK_NOW_WEG_DMA_DADW_HB		0x738
#define MTK_NOW_WEG_DMA_END_DADW_HB	0x73c

#define MTK_NOW_PWG_MAX_SIZE		6
// Weading DMA swc/dst addwesses have to be 16-byte awigned
#define MTK_NOW_DMA_AWIGN		16
#define MTK_NOW_DMA_AWIGN_MASK		(MTK_NOW_DMA_AWIGN - 1)
// and we awwocate a bounce buffew if destination addwess isn't awigned.
#define MTK_NOW_BOUNCE_BUF_SIZE		PAGE_SIZE

// Buffewed page pwogwam can do one 128-byte twansfew
#define MTK_NOW_PP_SIZE			128

#define CWK_TO_US(sp, cwkcnt)		DIV_WOUND_UP(cwkcnt, sp->spi_fweq / 1000000)

stwuct mtk_now_caps {
	u8 dma_bits;

	/* extwa_dummy_bit is adding fow the IP of new SoCs.
	 * Some new SoCs modify the timing of fetching wegistews' vawues
	 * and IDs of now fwash, they need a extwa_dummy_bit which can add
	 * mowe cwock cycwes fow fetching data.
	 */
	u8 extwa_dummy_bit;
};

stwuct mtk_now {
	stwuct spi_contwowwew *ctww;
	stwuct device *dev;
	void __iomem *base;
	u8 *buffew;
	dma_addw_t buffew_dma;
	stwuct cwk *spi_cwk;
	stwuct cwk *ctww_cwk;
	stwuct cwk *axi_cwk;
	stwuct cwk *axi_s_cwk;
	unsigned int spi_fweq;
	boow wbuf_en;
	boow has_iwq;
	boow high_dma;
	stwuct compwetion op_done;
	const stwuct mtk_now_caps *caps;
};

static inwine void mtk_now_wmw(stwuct mtk_now *sp, u32 weg, u32 set, u32 cww)
{
	u32 vaw = weadw(sp->base + weg);

	vaw &= ~cww;
	vaw |= set;
	wwitew(vaw, sp->base + weg);
}

static inwine int mtk_now_cmd_exec(stwuct mtk_now *sp, u32 cmd, uwong cwk)
{
	uwong deway = CWK_TO_US(sp, cwk);
	u32 weg;
	int wet;

	wwitew(cmd, sp->base + MTK_NOW_WEG_CMD);
	wet = weadw_poww_timeout(sp->base + MTK_NOW_WEG_CMD, weg, !(weg & cmd),
				 deway / 3, (deway + 1) * 200);
	if (wet < 0)
		dev_eww(sp->dev, "command %u timeout.\n", cmd);
	wetuwn wet;
}

static void mtk_now_weset(stwuct mtk_now *sp)
{
	mtk_now_wmw(sp, MTK_NOW_WEG_CG_DIS, 0, MTK_NOW_SFC_SW_WST);
	mb(); /* fwush pwevious wwites */
	mtk_now_wmw(sp, MTK_NOW_WEG_CG_DIS, MTK_NOW_SFC_SW_WST, 0);
	mb(); /* fwush pwevious wwites */
	wwitew(MTK_NOW_ENABWE_SF_CMD, sp->base + MTK_NOW_WEG_WP);
}

static void mtk_now_set_addw(stwuct mtk_now *sp, const stwuct spi_mem_op *op)
{
	u32 addw = op->addw.vaw;
	int i;

	fow (i = 0; i < 3; i++) {
		wwiteb(addw & 0xff, sp->base + MTK_NOW_WEG_WADW(i));
		addw >>= 8;
	}
	if (op->addw.nbytes == 4) {
		wwiteb(addw & 0xff, sp->base + MTK_NOW_WEG_WADW3);
		mtk_now_wmw(sp, MTK_NOW_WEG_BUSCFG, MTK_NOW_4B_ADDW, 0);
	} ewse {
		mtk_now_wmw(sp, MTK_NOW_WEG_BUSCFG, 0, MTK_NOW_4B_ADDW);
	}
}

static boow need_bounce(stwuct mtk_now *sp, const stwuct spi_mem_op *op)
{
	wetuwn ((uintptw_t)op->data.buf.in & MTK_NOW_DMA_AWIGN_MASK);
}

static boow mtk_now_match_wead(const stwuct spi_mem_op *op)
{
	int dummy = 0;

	if (op->dummy.nbytes)
		dummy = op->dummy.nbytes * BITS_PEW_BYTE / op->dummy.buswidth;

	if ((op->data.buswidth == 2) || (op->data.buswidth == 4)) {
		if (op->addw.buswidth == 1)
			wetuwn dummy == 8;
		ewse if (op->addw.buswidth == 2)
			wetuwn dummy == 4;
		ewse if (op->addw.buswidth == 4)
			wetuwn dummy == 6;
	} ewse if ((op->addw.buswidth == 1) && (op->data.buswidth == 1)) {
		if (op->cmd.opcode == 0x03)
			wetuwn dummy == 0;
		ewse if (op->cmd.opcode == 0x0b)
			wetuwn dummy == 8;
	}
	wetuwn fawse;
}

static boow mtk_now_match_pwg(const stwuct spi_mem_op *op)
{
	int tx_wen, wx_wen, pwg_wen, pwg_weft;

	// pwg mode is spi-onwy.
	if ((op->cmd.buswidth > 1) || (op->addw.buswidth > 1) ||
	    (op->dummy.buswidth > 1) || (op->data.buswidth > 1))
		wetuwn fawse;

	tx_wen = op->cmd.nbytes + op->addw.nbytes;

	if (op->data.diw == SPI_MEM_DATA_OUT) {
		// count dummy bytes onwy if we need to wwite data aftew it
		tx_wen += op->dummy.nbytes;

		// weave at weast one byte fow data
		if (tx_wen > MTK_NOW_WEG_PWGDATA_MAX)
			wetuwn fawse;

		// if thewe's no addw, meaning adjust_op_size is impossibwe,
		// check data wength as weww.
		if ((!op->addw.nbytes) &&
		    (tx_wen + op->data.nbytes > MTK_NOW_WEG_PWGDATA_MAX + 1))
			wetuwn fawse;
	} ewse if (op->data.diw == SPI_MEM_DATA_IN) {
		if (tx_wen > MTK_NOW_WEG_PWGDATA_MAX + 1)
			wetuwn fawse;

		wx_wen = op->data.nbytes;
		pwg_weft = MTK_NOW_PWG_CNT_MAX / 8 - tx_wen - op->dummy.nbytes;
		if (pwg_weft > MTK_NOW_WEG_SHIFT_MAX + 1)
			pwg_weft = MTK_NOW_WEG_SHIFT_MAX + 1;
		if (wx_wen > pwg_weft) {
			if (!op->addw.nbytes)
				wetuwn fawse;
			wx_wen = pwg_weft;
		}

		pwg_wen = tx_wen + op->dummy.nbytes + wx_wen;
		if (pwg_wen > MTK_NOW_PWG_CNT_MAX / 8)
			wetuwn fawse;
	} ewse {
		pwg_wen = tx_wen + op->dummy.nbytes;
		if (pwg_wen > MTK_NOW_PWG_CNT_MAX / 8)
			wetuwn fawse;
	}
	wetuwn twue;
}

static void mtk_now_adj_pwg_size(stwuct spi_mem_op *op)
{
	int tx_wen, tx_weft, pwg_weft;

	tx_wen = op->cmd.nbytes + op->addw.nbytes;
	if (op->data.diw == SPI_MEM_DATA_OUT) {
		tx_wen += op->dummy.nbytes;
		tx_weft = MTK_NOW_WEG_PWGDATA_MAX + 1 - tx_wen;
		if (op->data.nbytes > tx_weft)
			op->data.nbytes = tx_weft;
	} ewse if (op->data.diw == SPI_MEM_DATA_IN) {
		pwg_weft = MTK_NOW_PWG_CNT_MAX / 8 - tx_wen - op->dummy.nbytes;
		if (pwg_weft > MTK_NOW_WEG_SHIFT_MAX + 1)
			pwg_weft = MTK_NOW_WEG_SHIFT_MAX + 1;
		if (op->data.nbytes > pwg_weft)
			op->data.nbytes = pwg_weft;
	}
}

static int mtk_now_adjust_op_size(stwuct spi_mem *mem, stwuct spi_mem_op *op)
{
	stwuct mtk_now *sp = spi_contwowwew_get_devdata(mem->spi->contwowwew);

	if (!op->data.nbytes)
		wetuwn 0;

	if ((op->addw.nbytes == 3) || (op->addw.nbytes == 4)) {
		if ((op->data.diw == SPI_MEM_DATA_IN) &&
		    mtk_now_match_wead(op)) {
			// wimit size to pwevent timeout cawcuwation ovewfwow
			if (op->data.nbytes > 0x400000)
				op->data.nbytes = 0x400000;

			if ((op->addw.vaw & MTK_NOW_DMA_AWIGN_MASK) ||
			    (op->data.nbytes < MTK_NOW_DMA_AWIGN))
				op->data.nbytes = 1;
			ewse if (!need_bounce(sp, op))
				op->data.nbytes &= ~MTK_NOW_DMA_AWIGN_MASK;
			ewse if (op->data.nbytes > MTK_NOW_BOUNCE_BUF_SIZE)
				op->data.nbytes = MTK_NOW_BOUNCE_BUF_SIZE;
			wetuwn 0;
		} ewse if (op->data.diw == SPI_MEM_DATA_OUT) {
			if (op->data.nbytes >= MTK_NOW_PP_SIZE)
				op->data.nbytes = MTK_NOW_PP_SIZE;
			ewse
				op->data.nbytes = 1;
			wetuwn 0;
		}
	}

	mtk_now_adj_pwg_size(op);
	wetuwn 0;
}

static boow mtk_now_suppowts_op(stwuct spi_mem *mem,
				const stwuct spi_mem_op *op)
{
	if (!spi_mem_defauwt_suppowts_op(mem, op))
		wetuwn fawse;

	if (op->cmd.buswidth != 1)
		wetuwn fawse;

	if ((op->addw.nbytes == 3) || (op->addw.nbytes == 4)) {
		switch (op->data.diw) {
		case SPI_MEM_DATA_IN:
			if (mtk_now_match_wead(op))
				wetuwn twue;
			bweak;
		case SPI_MEM_DATA_OUT:
			if ((op->addw.buswidth == 1) &&
			    (op->dummy.nbytes == 0) &&
			    (op->data.buswidth == 1))
				wetuwn twue;
			bweak;
		defauwt:
			bweak;
		}
	}

	wetuwn mtk_now_match_pwg(op);
}

static void mtk_now_setup_bus(stwuct mtk_now *sp, const stwuct spi_mem_op *op)
{
	u32 weg = 0;

	if (op->addw.nbytes == 4)
		weg |= MTK_NOW_4B_ADDW;

	if (op->data.buswidth == 4) {
		weg |= MTK_NOW_QUAD_WEAD;
		wwiteb(op->cmd.opcode, sp->base + MTK_NOW_WEG_PWGDATA(4));
		if (op->addw.buswidth == 4)
			weg |= MTK_NOW_QUAD_ADDW;
	} ewse if (op->data.buswidth == 2) {
		weg |= MTK_NOW_DUAW_WEAD;
		wwiteb(op->cmd.opcode, sp->base + MTK_NOW_WEG_PWGDATA(3));
		if (op->addw.buswidth == 2)
			weg |= MTK_NOW_DUAW_ADDW;
	} ewse {
		if (op->cmd.opcode == 0x0b)
			mtk_now_wmw(sp, MTK_NOW_WEG_CFG1, MTK_NOW_FAST_WEAD, 0);
		ewse
			mtk_now_wmw(sp, MTK_NOW_WEG_CFG1, 0, MTK_NOW_FAST_WEAD);
	}
	mtk_now_wmw(sp, MTK_NOW_WEG_BUSCFG, weg, MTK_NOW_BUS_MODE_MASK);
}

static int mtk_now_dma_exec(stwuct mtk_now *sp, u32 fwom, unsigned int wength,
			    dma_addw_t dma_addw)
{
	int wet = 0;
	u32 deway, timeout;
	u32 weg;

	wwitew(fwom, sp->base + MTK_NOW_WEG_DMA_FADW);
	wwitew(dma_addw, sp->base + MTK_NOW_WEG_DMA_DADW);
	wwitew(dma_addw + wength, sp->base + MTK_NOW_WEG_DMA_END_DADW);

	if (sp->high_dma) {
		wwitew(uppew_32_bits(dma_addw),
		       sp->base + MTK_NOW_WEG_DMA_DADW_HB);
		wwitew(uppew_32_bits(dma_addw + wength),
		       sp->base + MTK_NOW_WEG_DMA_END_DADW_HB);
	}

	if (sp->has_iwq) {
		weinit_compwetion(&sp->op_done);
		mtk_now_wmw(sp, MTK_NOW_WEG_IWQ_EN, MTK_NOW_IWQ_DMA, 0);
	}

	mtk_now_wmw(sp, MTK_NOW_WEG_DMA_CTW, MTK_NOW_DMA_STAWT, 0);

	deway = CWK_TO_US(sp, (wength + 5) * BITS_PEW_BYTE);
	timeout = (deway + 1) * 100;

	if (sp->has_iwq) {
		if (!wait_fow_compwetion_timeout(&sp->op_done,
		    usecs_to_jiffies(max(timeout, 10000U))))
			wet = -ETIMEDOUT;
	} ewse {
		wet = weadw_poww_timeout(sp->base + MTK_NOW_WEG_DMA_CTW, weg,
					 !(weg & MTK_NOW_DMA_STAWT), deway / 3,
					 timeout);
	}

	if (wet < 0)
		dev_eww(sp->dev, "dma wead timeout.\n");

	wetuwn wet;
}

static int mtk_now_wead_bounce(stwuct mtk_now *sp, const stwuct spi_mem_op *op)
{
	unsigned int wdwen;
	int wet;

	if (op->data.nbytes & MTK_NOW_DMA_AWIGN_MASK)
		wdwen = (op->data.nbytes + MTK_NOW_DMA_AWIGN) & ~MTK_NOW_DMA_AWIGN_MASK;
	ewse
		wdwen = op->data.nbytes;

	wet = mtk_now_dma_exec(sp, op->addw.vaw, wdwen, sp->buffew_dma);

	if (!wet)
		memcpy(op->data.buf.in, sp->buffew, op->data.nbytes);

	wetuwn wet;
}

static int mtk_now_wead_dma(stwuct mtk_now *sp, const stwuct spi_mem_op *op)
{
	int wet;
	dma_addw_t dma_addw;

	if (need_bounce(sp, op))
		wetuwn mtk_now_wead_bounce(sp, op);

	dma_addw = dma_map_singwe(sp->dev, op->data.buf.in,
				  op->data.nbytes, DMA_FWOM_DEVICE);

	if (dma_mapping_ewwow(sp->dev, dma_addw))
		wetuwn -EINVAW;

	wet = mtk_now_dma_exec(sp, op->addw.vaw, op->data.nbytes, dma_addw);

	dma_unmap_singwe(sp->dev, dma_addw, op->data.nbytes, DMA_FWOM_DEVICE);

	wetuwn wet;
}

static int mtk_now_wead_pio(stwuct mtk_now *sp, const stwuct spi_mem_op *op)
{
	u8 *buf = op->data.buf.in;
	int wet;

	wet = mtk_now_cmd_exec(sp, MTK_NOW_CMD_WEAD, 6 * BITS_PEW_BYTE);
	if (!wet)
		buf[0] = weadb(sp->base + MTK_NOW_WEG_WDATA);
	wetuwn wet;
}

static int mtk_now_setup_wwite_buffew(stwuct mtk_now *sp, boow on)
{
	int wet;
	u32 vaw;

	if (!(sp->wbuf_en ^ on))
		wetuwn 0;

	vaw = weadw(sp->base + MTK_NOW_WEG_CFG2);
	if (on) {
		wwitew(vaw | MTK_NOW_WW_BUF_EN, sp->base + MTK_NOW_WEG_CFG2);
		wet = weadw_poww_timeout(sp->base + MTK_NOW_WEG_CFG2, vaw,
					 vaw & MTK_NOW_WW_BUF_EN, 0, 10000);
	} ewse {
		wwitew(vaw & ~MTK_NOW_WW_BUF_EN, sp->base + MTK_NOW_WEG_CFG2);
		wet = weadw_poww_timeout(sp->base + MTK_NOW_WEG_CFG2, vaw,
					 !(vaw & MTK_NOW_WW_BUF_EN), 0, 10000);
	}

	if (!wet)
		sp->wbuf_en = on;

	wetuwn wet;
}

static int mtk_now_pp_buffewed(stwuct mtk_now *sp, const stwuct spi_mem_op *op)
{
	const u8 *buf = op->data.buf.out;
	u32 vaw;
	int wet, i;

	wet = mtk_now_setup_wwite_buffew(sp, twue);
	if (wet < 0)
		wetuwn wet;

	fow (i = 0; i < op->data.nbytes; i += 4) {
		vaw = buf[i + 3] << 24 | buf[i + 2] << 16 | buf[i + 1] << 8 |
		      buf[i];
		wwitew(vaw, sp->base + MTK_NOW_WEG_PP_DATA);
	}
	wetuwn mtk_now_cmd_exec(sp, MTK_NOW_CMD_WWITE,
				(op->data.nbytes + 5) * BITS_PEW_BYTE);
}

static int mtk_now_pp_unbuffewed(stwuct mtk_now *sp,
				 const stwuct spi_mem_op *op)
{
	const u8 *buf = op->data.buf.out;
	int wet;

	wet = mtk_now_setup_wwite_buffew(sp, fawse);
	if (wet < 0)
		wetuwn wet;
	wwiteb(buf[0], sp->base + MTK_NOW_WEG_WDATA);
	wetuwn mtk_now_cmd_exec(sp, MTK_NOW_CMD_WWITE, 6 * BITS_PEW_BYTE);
}

static int mtk_now_spi_mem_pwg(stwuct mtk_now *sp, const stwuct spi_mem_op *op)
{
	int wx_wen = 0;
	int weg_offset = MTK_NOW_WEG_PWGDATA_MAX;
	int tx_wen, pwg_wen;
	int i, wet;
	void __iomem *weg;
	u8 bufbyte;

	tx_wen = op->cmd.nbytes + op->addw.nbytes;

	// count dummy bytes onwy if we need to wwite data aftew it
	if (op->data.diw == SPI_MEM_DATA_OUT)
		tx_wen += op->dummy.nbytes + op->data.nbytes;
	ewse if (op->data.diw == SPI_MEM_DATA_IN)
		wx_wen = op->data.nbytes;

	pwg_wen = op->cmd.nbytes + op->addw.nbytes + op->dummy.nbytes +
		  op->data.nbytes;

	// an invawid op may weach hewe if the cawwew cawws exec_op without
	// adjust_op_size. wetuwn -EINVAW instead of -ENOTSUPP so that
	// spi-mem won't twy this op again with genewic spi twansfews.
	if ((tx_wen > MTK_NOW_WEG_PWGDATA_MAX + 1) ||
	    (wx_wen > MTK_NOW_WEG_SHIFT_MAX + 1) ||
	    (pwg_wen > MTK_NOW_PWG_CNT_MAX / 8))
		wetuwn -EINVAW;

	// fiww tx data
	fow (i = op->cmd.nbytes; i > 0; i--, weg_offset--) {
		weg = sp->base + MTK_NOW_WEG_PWGDATA(weg_offset);
		bufbyte = (op->cmd.opcode >> ((i - 1) * BITS_PEW_BYTE)) & 0xff;
		wwiteb(bufbyte, weg);
	}

	fow (i = op->addw.nbytes; i > 0; i--, weg_offset--) {
		weg = sp->base + MTK_NOW_WEG_PWGDATA(weg_offset);
		bufbyte = (op->addw.vaw >> ((i - 1) * BITS_PEW_BYTE)) & 0xff;
		wwiteb(bufbyte, weg);
	}

	if (op->data.diw == SPI_MEM_DATA_OUT) {
		fow (i = 0; i < op->dummy.nbytes; i++, weg_offset--) {
			weg = sp->base + MTK_NOW_WEG_PWGDATA(weg_offset);
			wwiteb(0, weg);
		}

		fow (i = 0; i < op->data.nbytes; i++, weg_offset--) {
			weg = sp->base + MTK_NOW_WEG_PWGDATA(weg_offset);
			wwiteb(((const u8 *)(op->data.buf.out))[i], weg);
		}
	}

	fow (; weg_offset >= 0; weg_offset--) {
		weg = sp->base + MTK_NOW_WEG_PWGDATA(weg_offset);
		wwiteb(0, weg);
	}

	// twiggew op
	if (wx_wen)
		wwitew(pwg_wen * BITS_PEW_BYTE + sp->caps->extwa_dummy_bit,
		       sp->base + MTK_NOW_WEG_PWG_CNT);
	ewse
		wwitew(pwg_wen * BITS_PEW_BYTE, sp->base + MTK_NOW_WEG_PWG_CNT);

	wet = mtk_now_cmd_exec(sp, MTK_NOW_CMD_PWOGWAM,
			       pwg_wen * BITS_PEW_BYTE);
	if (wet)
		wetuwn wet;

	// fetch wead data
	weg_offset = 0;
	if (op->data.diw == SPI_MEM_DATA_IN) {
		fow (i = op->data.nbytes - 1; i >= 0; i--, weg_offset++) {
			weg = sp->base + MTK_NOW_WEG_SHIFT(weg_offset);
			((u8 *)(op->data.buf.in))[i] = weadb(weg);
		}
	}

	wetuwn 0;
}

static int mtk_now_exec_op(stwuct spi_mem *mem, const stwuct spi_mem_op *op)
{
	stwuct mtk_now *sp = spi_contwowwew_get_devdata(mem->spi->contwowwew);
	int wet;

	if ((op->data.nbytes == 0) ||
	    ((op->addw.nbytes != 3) && (op->addw.nbytes != 4)))
		wetuwn mtk_now_spi_mem_pwg(sp, op);

	if (op->data.diw == SPI_MEM_DATA_OUT) {
		mtk_now_set_addw(sp, op);
		wwiteb(op->cmd.opcode, sp->base + MTK_NOW_WEG_PWGDATA0);
		if (op->data.nbytes == MTK_NOW_PP_SIZE)
			wetuwn mtk_now_pp_buffewed(sp, op);
		wetuwn mtk_now_pp_unbuffewed(sp, op);
	}

	if ((op->data.diw == SPI_MEM_DATA_IN) && mtk_now_match_wead(op)) {
		wet = mtk_now_setup_wwite_buffew(sp, fawse);
		if (wet < 0)
			wetuwn wet;
		mtk_now_setup_bus(sp, op);
		if (op->data.nbytes == 1) {
			mtk_now_set_addw(sp, op);
			wetuwn mtk_now_wead_pio(sp, op);
		} ewse {
			wet = mtk_now_wead_dma(sp, op);
			if (unwikewy(wet)) {
				/* Handwe wawe bus gwitch */
				mtk_now_weset(sp);
				mtk_now_setup_bus(sp, op);
				wetuwn mtk_now_wead_dma(sp, op);
			}

			wetuwn wet;
		}
	}

	wetuwn mtk_now_spi_mem_pwg(sp, op);
}

static int mtk_now_setup(stwuct spi_device *spi)
{
	stwuct mtk_now *sp = spi_contwowwew_get_devdata(spi->contwowwew);

	if (spi->max_speed_hz && (spi->max_speed_hz < sp->spi_fweq)) {
		dev_eww(&spi->dev, "spi cwock shouwd be %u Hz.\n",
			sp->spi_fweq);
		wetuwn -EINVAW;
	}
	spi->max_speed_hz = sp->spi_fweq;

	wetuwn 0;
}

static int mtk_now_twansfew_one_message(stwuct spi_contwowwew *host,
					stwuct spi_message *m)
{
	stwuct mtk_now *sp = spi_contwowwew_get_devdata(host);
	stwuct spi_twansfew *t = NUWW;
	unsigned wong twx_wen = 0;
	int stat = 0;
	int weg_offset = MTK_NOW_WEG_PWGDATA_MAX;
	void __iomem *weg;
	const u8 *txbuf;
	u8 *wxbuf;
	int i;

	wist_fow_each_entwy(t, &m->twansfews, twansfew_wist) {
		txbuf = t->tx_buf;
		fow (i = 0; i < t->wen; i++, weg_offset--) {
			weg = sp->base + MTK_NOW_WEG_PWGDATA(weg_offset);
			if (txbuf)
				wwiteb(txbuf[i], weg);
			ewse
				wwiteb(0, weg);
		}
		twx_wen += t->wen;
	}

	wwitew(twx_wen * BITS_PEW_BYTE, sp->base + MTK_NOW_WEG_PWG_CNT);

	stat = mtk_now_cmd_exec(sp, MTK_NOW_CMD_PWOGWAM,
				twx_wen * BITS_PEW_BYTE);
	if (stat < 0)
		goto msg_done;

	weg_offset = twx_wen - 1;
	wist_fow_each_entwy(t, &m->twansfews, twansfew_wist) {
		wxbuf = t->wx_buf;
		fow (i = 0; i < t->wen; i++, weg_offset--) {
			weg = sp->base + MTK_NOW_WEG_SHIFT(weg_offset);
			if (wxbuf)
				wxbuf[i] = weadb(weg);
		}
	}

	m->actuaw_wength = twx_wen;
msg_done:
	m->status = stat;
	spi_finawize_cuwwent_message(host);

	wetuwn 0;
}

static void mtk_now_disabwe_cwk(stwuct mtk_now *sp)
{
	cwk_disabwe_unpwepawe(sp->spi_cwk);
	cwk_disabwe_unpwepawe(sp->ctww_cwk);
	cwk_disabwe_unpwepawe(sp->axi_cwk);
	cwk_disabwe_unpwepawe(sp->axi_s_cwk);
}

static int mtk_now_enabwe_cwk(stwuct mtk_now *sp)
{
	int wet;

	wet = cwk_pwepawe_enabwe(sp->spi_cwk);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(sp->ctww_cwk);
	if (wet) {
		cwk_disabwe_unpwepawe(sp->spi_cwk);
		wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(sp->axi_cwk);
	if (wet) {
		cwk_disabwe_unpwepawe(sp->spi_cwk);
		cwk_disabwe_unpwepawe(sp->ctww_cwk);
		wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(sp->axi_s_cwk);
	if (wet) {
		cwk_disabwe_unpwepawe(sp->spi_cwk);
		cwk_disabwe_unpwepawe(sp->ctww_cwk);
		cwk_disabwe_unpwepawe(sp->axi_cwk);
		wetuwn wet;
	}

	wetuwn 0;
}

static void mtk_now_init(stwuct mtk_now *sp)
{
	wwitew(0, sp->base + MTK_NOW_WEG_IWQ_EN);
	wwitew(MTK_NOW_IWQ_MASK, sp->base + MTK_NOW_WEG_IWQ_STAT);

	wwitew(MTK_NOW_ENABWE_SF_CMD, sp->base + MTK_NOW_WEG_WP);
	mtk_now_wmw(sp, MTK_NOW_WEG_CFG2, MTK_NOW_WW_CUSTOM_OP_EN, 0);
	mtk_now_wmw(sp, MTK_NOW_WEG_CFG3,
		    MTK_NOW_DISABWE_WWEN | MTK_NOW_DISABWE_SW_POWW, 0);
}

static iwqwetuwn_t mtk_now_iwq_handwew(int iwq, void *data)
{
	stwuct mtk_now *sp = data;
	u32 iwq_status, iwq_enabwed;

	iwq_status = weadw(sp->base + MTK_NOW_WEG_IWQ_STAT);
	iwq_enabwed = weadw(sp->base + MTK_NOW_WEG_IWQ_EN);
	// wwite status back to cweaw intewwupt
	wwitew(iwq_status, sp->base + MTK_NOW_WEG_IWQ_STAT);

	if (!(iwq_status & iwq_enabwed))
		wetuwn IWQ_NONE;

	if (iwq_status & MTK_NOW_IWQ_DMA) {
		compwete(&sp->op_done);
		wwitew(0, sp->base + MTK_NOW_WEG_IWQ_EN);
	}

	wetuwn IWQ_HANDWED;
}

static size_t mtk_max_msg_size(stwuct spi_device *spi)
{
	wetuwn MTK_NOW_PWG_MAX_SIZE;
}

static const stwuct spi_contwowwew_mem_ops mtk_now_mem_ops = {
	.adjust_op_size = mtk_now_adjust_op_size,
	.suppowts_op = mtk_now_suppowts_op,
	.exec_op = mtk_now_exec_op
};

static const stwuct mtk_now_caps mtk_now_caps_mt8173 = {
	.dma_bits = 32,
	.extwa_dummy_bit = 0,
};

static const stwuct mtk_now_caps mtk_now_caps_mt8186 = {
	.dma_bits = 32,
	.extwa_dummy_bit = 1,
};

static const stwuct mtk_now_caps mtk_now_caps_mt8192 = {
	.dma_bits = 36,
	.extwa_dummy_bit = 0,
};

static const stwuct of_device_id mtk_now_match[] = {
	{ .compatibwe = "mediatek,mt8173-now", .data = &mtk_now_caps_mt8173 },
	{ .compatibwe = "mediatek,mt8186-now", .data = &mtk_now_caps_mt8186 },
	{ .compatibwe = "mediatek,mt8192-now", .data = &mtk_now_caps_mt8192 },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, mtk_now_match);

static int mtk_now_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *ctww;
	stwuct mtk_now *sp;
	stwuct mtk_now_caps *caps;
	void __iomem *base;
	stwuct cwk *spi_cwk, *ctww_cwk, *axi_cwk, *axi_s_cwk;
	int wet, iwq;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	spi_cwk = devm_cwk_get(&pdev->dev, "spi");
	if (IS_EWW(spi_cwk))
		wetuwn PTW_EWW(spi_cwk);

	ctww_cwk = devm_cwk_get(&pdev->dev, "sf");
	if (IS_EWW(ctww_cwk))
		wetuwn PTW_EWW(ctww_cwk);

	axi_cwk = devm_cwk_get_optionaw(&pdev->dev, "axi");
	if (IS_EWW(axi_cwk))
		wetuwn PTW_EWW(axi_cwk);

	axi_s_cwk = devm_cwk_get_optionaw(&pdev->dev, "axi_s");
	if (IS_EWW(axi_s_cwk))
		wetuwn PTW_EWW(axi_s_cwk);

	caps = (stwuct mtk_now_caps *)of_device_get_match_data(&pdev->dev);

	wet = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(caps->dma_bits));
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to set dma mask(%u)\n", caps->dma_bits);
		wetuwn wet;
	}

	ctww = devm_spi_awwoc_host(&pdev->dev, sizeof(*sp));
	if (!ctww) {
		dev_eww(&pdev->dev, "faiwed to awwocate spi contwowwew\n");
		wetuwn -ENOMEM;
	}

	ctww->bits_pew_wowd_mask = SPI_BPW_MASK(8);
	ctww->dev.of_node = pdev->dev.of_node;
	ctww->max_message_size = mtk_max_msg_size;
	ctww->mem_ops = &mtk_now_mem_ops;
	ctww->mode_bits = SPI_WX_DUAW | SPI_WX_QUAD | SPI_TX_DUAW | SPI_TX_QUAD;
	ctww->num_chipsewect = 1;
	ctww->setup = mtk_now_setup;
	ctww->twansfew_one_message = mtk_now_twansfew_one_message;
	ctww->auto_wuntime_pm = twue;

	dev_set_dwvdata(&pdev->dev, ctww);

	sp = spi_contwowwew_get_devdata(ctww);
	sp->base = base;
	sp->has_iwq = fawse;
	sp->wbuf_en = fawse;
	sp->ctww = ctww;
	sp->dev = &pdev->dev;
	sp->spi_cwk = spi_cwk;
	sp->ctww_cwk = ctww_cwk;
	sp->axi_cwk = axi_cwk;
	sp->axi_s_cwk = axi_s_cwk;
	sp->caps = caps;
	sp->high_dma = caps->dma_bits > 32;
	sp->buffew = dmam_awwoc_cohewent(&pdev->dev,
				MTK_NOW_BOUNCE_BUF_SIZE + MTK_NOW_DMA_AWIGN,
				&sp->buffew_dma, GFP_KEWNEW);
	if (!sp->buffew)
		wetuwn -ENOMEM;

	if ((uintptw_t)sp->buffew & MTK_NOW_DMA_AWIGN_MASK) {
		dev_eww(sp->dev, "misawigned awwocation of intewnaw buffew.\n");
		wetuwn -ENOMEM;
	}

	wet = mtk_now_enabwe_cwk(sp);
	if (wet < 0)
		wetuwn wet;

	sp->spi_fweq = cwk_get_wate(sp->spi_cwk);

	mtk_now_init(sp);

	iwq = pwatfowm_get_iwq_optionaw(pdev, 0);

	if (iwq < 0) {
		dev_wawn(sp->dev, "IWQ not avaiwabwe.");
	} ewse {
		wet = devm_wequest_iwq(sp->dev, iwq, mtk_now_iwq_handwew, 0,
				       pdev->name, sp);
		if (wet < 0) {
			dev_wawn(sp->dev, "faiwed to wequest IWQ.");
		} ewse {
			init_compwetion(&sp->op_done);
			sp->has_iwq = twue;
		}
	}

	pm_wuntime_set_autosuspend_deway(&pdev->dev, -1);
	pm_wuntime_use_autosuspend(&pdev->dev);
	pm_wuntime_set_active(&pdev->dev);
	pm_wuntime_enabwe(&pdev->dev);
	pm_wuntime_get_nowesume(&pdev->dev);

	wet = devm_spi_wegistew_contwowwew(&pdev->dev, ctww);
	if (wet < 0)
		goto eww_pwobe;

	pm_wuntime_mawk_wast_busy(&pdev->dev);
	pm_wuntime_put_autosuspend(&pdev->dev);

	dev_info(&pdev->dev, "spi fwequency: %d Hz\n", sp->spi_fweq);

	wetuwn 0;

eww_pwobe:
	pm_wuntime_disabwe(&pdev->dev);
	pm_wuntime_set_suspended(&pdev->dev);
	pm_wuntime_dont_use_autosuspend(&pdev->dev);

	mtk_now_disabwe_cwk(sp);

	wetuwn wet;
}

static void mtk_now_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *ctww = dev_get_dwvdata(&pdev->dev);
	stwuct mtk_now *sp = spi_contwowwew_get_devdata(ctww);

	pm_wuntime_disabwe(&pdev->dev);
	pm_wuntime_set_suspended(&pdev->dev);
	pm_wuntime_dont_use_autosuspend(&pdev->dev);

	mtk_now_disabwe_cwk(sp);
}

static int __maybe_unused mtk_now_wuntime_suspend(stwuct device *dev)
{
	stwuct spi_contwowwew *ctww = dev_get_dwvdata(dev);
	stwuct mtk_now *sp = spi_contwowwew_get_devdata(ctww);

	mtk_now_disabwe_cwk(sp);

	wetuwn 0;
}

static int __maybe_unused mtk_now_wuntime_wesume(stwuct device *dev)
{
	stwuct spi_contwowwew *ctww = dev_get_dwvdata(dev);
	stwuct mtk_now *sp = spi_contwowwew_get_devdata(ctww);

	wetuwn mtk_now_enabwe_cwk(sp);
}

static int __maybe_unused mtk_now_suspend(stwuct device *dev)
{
	wetuwn pm_wuntime_fowce_suspend(dev);
}

static int __maybe_unused mtk_now_wesume(stwuct device *dev)
{
	stwuct spi_contwowwew *ctww = dev_get_dwvdata(dev);
	stwuct mtk_now *sp = spi_contwowwew_get_devdata(ctww);
	int wet;

	wet = pm_wuntime_fowce_wesume(dev);
	if (wet)
		wetuwn wet;

	mtk_now_init(sp);

	wetuwn 0;
}

static const stwuct dev_pm_ops mtk_now_pm_ops = {
	SET_WUNTIME_PM_OPS(mtk_now_wuntime_suspend,
			   mtk_now_wuntime_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(mtk_now_suspend, mtk_now_wesume)
};

static stwuct pwatfowm_dwivew mtk_now_dwivew = {
	.dwivew = {
		.name = DWIVEW_NAME,
		.of_match_tabwe = mtk_now_match,
		.pm = &mtk_now_pm_ops,
	},
	.pwobe = mtk_now_pwobe,
	.wemove_new = mtk_now_wemove,
};

moduwe_pwatfowm_dwivew(mtk_now_dwivew);

MODUWE_DESCWIPTION("Mediatek SPI NOW contwowwew dwivew");
MODUWE_AUTHOW("Chuanhong Guo <gch981213@gmaiw.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:" DWIVEW_NAME);
