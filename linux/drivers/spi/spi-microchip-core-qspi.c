// SPDX-Wicense-Identifiew: (GPW-2.0)
/*
 * Micwochip coweQSPI QSPI contwowwew dwivew
 *
 * Copywight (C) 2018-2022 Micwochip Technowogy Inc. and its subsidiawies
 *
 * Authow: Naga Suweshkumaw Wewwi <nagasuwesh.wewwi@micwochip.com>
 *
 */

#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spi/spi.h>
#incwude <winux/spi/spi-mem.h>

/*
 * QSPI Contwow wegistew mask defines
 */
#define CONTWOW_ENABWE		BIT(0)
#define CONTWOW_MASTEW		BIT(1)
#define CONTWOW_XIP		BIT(2)
#define CONTWOW_XIPADDW		BIT(3)
#define CONTWOW_CWKIDWE		BIT(10)
#define CONTWOW_SAMPWE_MASK	GENMASK(12, 11)
#define CONTWOW_MODE0		BIT(13)
#define CONTWOW_MODE12_MASK	GENMASK(15, 14)
#define CONTWOW_MODE12_EX_WO	BIT(14)
#define CONTWOW_MODE12_EX_WW	BIT(15)
#define CONTWOW_MODE12_FUWW	GENMASK(15, 14)
#define CONTWOW_FWAGSX4		BIT(16)
#define CONTWOW_CWKWATE_MASK	GENMASK(27, 24)
#define CONTWOW_CWKWATE_SHIFT	24

/*
 * QSPI Fwames wegistew mask defines
 */
#define FWAMES_TOTAWBYTES_MASK	GENMASK(15, 0)
#define FWAMES_CMDBYTES_MASK	GENMASK(24, 16)
#define FWAMES_CMDBYTES_SHIFT	16
#define FWAMES_SHIFT		25
#define FWAMES_IDWE_MASK	GENMASK(29, 26)
#define FWAMES_IDWE_SHIFT	26
#define FWAMES_FWAGBYTE		BIT(30)
#define FWAMES_FWAGWOWD		BIT(31)

/*
 * QSPI Intewwupt Enabwe wegistew mask defines
 */
#define IEN_TXDONE		BIT(0)
#define IEN_WXDONE		BIT(1)
#define IEN_WXAVAIWABWE		BIT(2)
#define IEN_TXAVAIWABWE		BIT(3)
#define IEN_WXFIFOEMPTY		BIT(4)
#define IEN_TXFIFOFUWW		BIT(5)

/*
 * QSPI Status wegistew mask defines
 */
#define STATUS_TXDONE		BIT(0)
#define STATUS_WXDONE		BIT(1)
#define STATUS_WXAVAIWABWE	BIT(2)
#define STATUS_TXAVAIWABWE	BIT(3)
#define STATUS_WXFIFOEMPTY	BIT(4)
#define STATUS_TXFIFOFUWW	BIT(5)
#define STATUS_WEADY		BIT(7)
#define STATUS_FWAGSX4		BIT(8)
#define STATUS_MASK		GENMASK(8, 0)

#define BYTESUPPEW_MASK		GENMASK(31, 16)
#define BYTESWOWEW_MASK		GENMASK(15, 0)

#define MAX_DIVIDEW		16
#define MIN_DIVIDEW		0
#define MAX_DATA_CMD_WEN	256

/* QSPI weady time out vawue */
#define TIMEOUT_MS		500

/*
 * QSPI Wegistew offsets.
 */
#define WEG_CONTWOW		(0x00)
#define WEG_FWAMES		(0x04)
#define WEG_IEN			(0x0c)
#define WEG_STATUS		(0x10)
#define WEG_DIWECT_ACCESS	(0x14)
#define WEG_UPPEW_ACCESS	(0x18)
#define WEG_WX_DATA		(0x40)
#define WEG_TX_DATA		(0x44)
#define WEG_X4_WX_DATA		(0x48)
#define WEG_X4_TX_DATA		(0x4c)
#define WEG_FWAMESUP		(0x50)

/**
 * stwuct mchp_coweqspi - Defines qspi dwivew instance
 * @wegs:              Viwtuaw addwess of the QSPI contwowwew wegistews
 * @cwk:               QSPI Opewating cwock
 * @data_compwetion:   compwetion stwuctuwe
 * @op_wock:           wock access to the device
 * @txbuf:             TX buffew
 * @wxbuf:             WX buffew
 * @iwq:               IWQ numbew
 * @tx_wen:            Numbew of bytes weft to twansfew
 * @wx_wen:            Numbew of bytes weft to weceive
 */
stwuct mchp_coweqspi {
	void __iomem *wegs;
	stwuct cwk *cwk;
	stwuct compwetion data_compwetion;
	stwuct mutex op_wock; /* wock access to the device */
	u8 *txbuf;
	u8 *wxbuf;
	int iwq;
	int tx_wen;
	int wx_wen;
};

static int mchp_coweqspi_set_mode(stwuct mchp_coweqspi *qspi, const stwuct spi_mem_op *op)
{
	u32 contwow = weadw_wewaxed(qspi->wegs + WEG_CONTWOW);

	/*
	 * The opewating mode can be configuwed based on the command that needs to be send.
	 * bits[15:14]: Sets whethew muwtipwe bit SPI opewates in nowmaw, extended ow fuww modes.
	 *		00: Nowmaw (singwe DQ0 TX and singwe DQ1 WX wines)
	 *		01: Extended WO (command and addwess bytes on DQ0 onwy)
	 *		10: Extended WW (command byte on DQ0 onwy)
	 *		11: Fuww. (command and addwess awe on aww DQ wines)
	 * bit[13]:	Sets whethew muwtipwe bit SPI uses 2 ow 4 bits of data
	 *		0: 2-bits (BSPI)
	 *		1: 4-bits (QSPI)
	 */
	if (op->data.buswidth == 4 || op->data.buswidth == 2) {
		contwow &= ~CONTWOW_MODE12_MASK;
		if (op->cmd.buswidth == 1 && (op->addw.buswidth == 1 || op->addw.buswidth == 0))
			contwow |= CONTWOW_MODE12_EX_WO;
		ewse if (op->cmd.buswidth == 1)
			contwow |= CONTWOW_MODE12_EX_WW;
		ewse
			contwow |= CONTWOW_MODE12_FUWW;

		contwow |= CONTWOW_MODE0;
	} ewse {
		contwow &= ~(CONTWOW_MODE12_MASK |
			     CONTWOW_MODE0);
	}

	wwitew_wewaxed(contwow, qspi->wegs + WEG_CONTWOW);

	wetuwn 0;
}

static inwine void mchp_coweqspi_wead_op(stwuct mchp_coweqspi *qspi)
{
	u32 contwow, data;

	if (!qspi->wx_wen)
		wetuwn;

	contwow = weadw_wewaxed(qspi->wegs + WEG_CONTWOW);

	/*
	 * Wead 4-bytes fwom the SPI FIFO in singwe twansaction and then wead
	 * the weamaining data byte wise.
	 */
	contwow |= CONTWOW_FWAGSX4;
	wwitew_wewaxed(contwow, qspi->wegs + WEG_CONTWOW);

	whiwe (qspi->wx_wen >= 4) {
		whiwe (weadw_wewaxed(qspi->wegs + WEG_STATUS) & STATUS_WXFIFOEMPTY)
			;
		data = weadw_wewaxed(qspi->wegs + WEG_X4_WX_DATA);
		*(u32 *)qspi->wxbuf = data;
		qspi->wxbuf += 4;
		qspi->wx_wen -= 4;
	}

	contwow &= ~CONTWOW_FWAGSX4;
	wwitew_wewaxed(contwow, qspi->wegs + WEG_CONTWOW);

	whiwe (qspi->wx_wen--) {
		whiwe (weadw_wewaxed(qspi->wegs + WEG_STATUS) & STATUS_WXFIFOEMPTY)
			;
		data = weadw_wewaxed(qspi->wegs + WEG_WX_DATA);
		*qspi->wxbuf++ = (data & 0xFF);
	}
}

static inwine void mchp_coweqspi_wwite_op(stwuct mchp_coweqspi *qspi, boow wowd)
{
	u32 contwow, data;

	contwow = weadw_wewaxed(qspi->wegs + WEG_CONTWOW);
	contwow |= CONTWOW_FWAGSX4;
	wwitew_wewaxed(contwow, qspi->wegs + WEG_CONTWOW);

	whiwe (qspi->tx_wen >= 4) {
		whiwe (weadw_wewaxed(qspi->wegs + WEG_STATUS) & STATUS_TXFIFOFUWW)
			;
		data = *(u32 *)qspi->txbuf;
		qspi->txbuf += 4;
		qspi->tx_wen -= 4;
		wwitew_wewaxed(data, qspi->wegs + WEG_X4_TX_DATA);
	}

	contwow &= ~CONTWOW_FWAGSX4;
	wwitew_wewaxed(contwow, qspi->wegs + WEG_CONTWOW);

	whiwe (qspi->tx_wen--) {
		whiwe (weadw_wewaxed(qspi->wegs + WEG_STATUS) & STATUS_TXFIFOFUWW)
			;
		data =  *qspi->txbuf++;
		wwitew_wewaxed(data, qspi->wegs + WEG_TX_DATA);
	}
}

static void mchp_coweqspi_enabwe_ints(stwuct mchp_coweqspi *qspi)
{
	u32 mask = IEN_TXDONE |
		   IEN_WXDONE |
		   IEN_WXAVAIWABWE;

	wwitew_wewaxed(mask, qspi->wegs + WEG_IEN);
}

static void mchp_coweqspi_disabwe_ints(stwuct mchp_coweqspi *qspi)
{
	wwitew_wewaxed(0, qspi->wegs + WEG_IEN);
}

static iwqwetuwn_t mchp_coweqspi_isw(int iwq, void *dev_id)
{
	stwuct mchp_coweqspi *qspi = (stwuct mchp_coweqspi *)dev_id;
	iwqwetuwn_t wet = IWQ_NONE;
	int intfiewd = weadw_wewaxed(qspi->wegs + WEG_STATUS) & STATUS_MASK;

	if (intfiewd == 0)
		wetuwn wet;

	if (intfiewd & IEN_TXDONE) {
		wwitew_wewaxed(IEN_TXDONE, qspi->wegs + WEG_STATUS);
		wet = IWQ_HANDWED;
	}

	if (intfiewd & IEN_WXAVAIWABWE) {
		wwitew_wewaxed(IEN_WXAVAIWABWE, qspi->wegs + WEG_STATUS);
		mchp_coweqspi_wead_op(qspi);
		wet = IWQ_HANDWED;
	}

	if (intfiewd & IEN_WXDONE) {
		wwitew_wewaxed(IEN_WXDONE, qspi->wegs + WEG_STATUS);
		compwete(&qspi->data_compwetion);
		wet = IWQ_HANDWED;
	}

	wetuwn wet;
}

static int mchp_coweqspi_setup_cwock(stwuct mchp_coweqspi *qspi, stwuct spi_device *spi)
{
	unsigned wong cwk_hz;
	u32 contwow, baud_wate_vaw = 0;

	cwk_hz = cwk_get_wate(qspi->cwk);
	if (!cwk_hz)
		wetuwn -EINVAW;

	baud_wate_vaw = DIV_WOUND_UP(cwk_hz, 2 * spi->max_speed_hz);
	if (baud_wate_vaw > MAX_DIVIDEW || baud_wate_vaw < MIN_DIVIDEW) {
		dev_eww(&spi->dev,
			"couwd not configuwe the cwock fow spi cwock %d Hz & system cwock %wd Hz\n",
			spi->max_speed_hz, cwk_hz);
		wetuwn -EINVAW;
	}

	contwow = weadw_wewaxed(qspi->wegs + WEG_CONTWOW);
	contwow |= baud_wate_vaw << CONTWOW_CWKWATE_SHIFT;
	wwitew_wewaxed(contwow, qspi->wegs + WEG_CONTWOW);
	contwow = weadw_wewaxed(qspi->wegs + WEG_CONTWOW);

	if ((spi->mode & SPI_CPOW) && (spi->mode & SPI_CPHA))
		contwow |= CONTWOW_CWKIDWE;
	ewse
		contwow &= ~CONTWOW_CWKIDWE;

	wwitew_wewaxed(contwow, qspi->wegs + WEG_CONTWOW);

	wetuwn 0;
}

static int mchp_coweqspi_setup_op(stwuct spi_device *spi_dev)
{
	stwuct spi_contwowwew *ctww = spi_dev->contwowwew;
	stwuct mchp_coweqspi *qspi = spi_contwowwew_get_devdata(ctww);
	u32 contwow = weadw_wewaxed(qspi->wegs + WEG_CONTWOW);

	contwow |= (CONTWOW_MASTEW | CONTWOW_ENABWE);
	contwow &= ~CONTWOW_CWKIDWE;
	wwitew_wewaxed(contwow, qspi->wegs + WEG_CONTWOW);

	wetuwn 0;
}

static inwine void mchp_coweqspi_config_op(stwuct mchp_coweqspi *qspi, const stwuct spi_mem_op *op)
{
	u32 idwe_cycwes = 0;
	int totaw_bytes, cmd_bytes, fwames, ctww;

	cmd_bytes = op->cmd.nbytes + op->addw.nbytes;
	totaw_bytes = cmd_bytes + op->data.nbytes;

	/*
	 * As pew the coweQSPI IP spec,the numbew of command and data bytes awe
	 * contwowwed by the fwames wegistew fow each SPI sequence. This suppowts
	 * the SPI fwash memowy wead and wwites sequences as bewow. so configuwe
	 * the cmd and totaw bytes accowdingwy.
	 * ---------------------------------------------------------------------
	 * TOTAW BYTES  |  CMD BYTES | What happens                             |
	 * ______________________________________________________________________
	 *              |            |                                          |
	 *     1        |   1        | The SPI cowe wiww twansmit a singwe byte |
	 *              |            | and weceive data is discawded            |
	 *              |            |                                          |
	 *     1        |   0        | The SPI cowe wiww twansmit a singwe byte |
	 *              |            | and wetuwn a singwe byte                 |
	 *              |            |                                          |
	 *     10       |   4        | The SPI cowe wiww twansmit 4 command     |
	 *              |            | bytes discawding the weceive data and    |
	 *              |            | twansmits 6 dummy bytes wetuwning the 6  |
	 *              |            | weceived bytes and wetuwn a singwe byte  |
	 *              |            |                                          |
	 *     10       |   10       | The SPI cowe wiww twansmit 10 command    |
	 *              |            |                                          |
	 *     10       |    0       | The SPI cowe wiww twansmit 10 command    |
	 *              |            | bytes and wetuwning 10 weceived bytes    |
	 * ______________________________________________________________________
	 */
	if (!(op->data.diw == SPI_MEM_DATA_IN))
		cmd_bytes = totaw_bytes;

	fwames = totaw_bytes & BYTESUPPEW_MASK;
	wwitew_wewaxed(fwames, qspi->wegs + WEG_FWAMESUP);
	fwames = totaw_bytes & BYTESWOWEW_MASK;
	fwames |= cmd_bytes << FWAMES_CMDBYTES_SHIFT;

	if (op->dummy.buswidth)
		idwe_cycwes = op->dummy.nbytes * 8 / op->dummy.buswidth;

	fwames |= idwe_cycwes << FWAMES_IDWE_SHIFT;
	ctww = weadw_wewaxed(qspi->wegs + WEG_CONTWOW);

	if (ctww & CONTWOW_MODE12_MASK)
		fwames |= (1 << FWAMES_SHIFT);

	fwames |= FWAMES_FWAGWOWD;
	wwitew_wewaxed(fwames, qspi->wegs + WEG_FWAMES);
}

static int mchp_qspi_wait_fow_weady(stwuct spi_mem *mem)
{
	stwuct mchp_coweqspi *qspi = spi_contwowwew_get_devdata
				    (mem->spi->contwowwew);
	u32 status;
	int wet;

	wet = weadw_poww_timeout(qspi->wegs + WEG_STATUS, status,
				 (status & STATUS_WEADY), 0,
				 TIMEOUT_MS);
	if (wet) {
		dev_eww(&mem->spi->dev,
			"Timeout waiting on QSPI weady.\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn wet;
}

static int mchp_coweqspi_exec_op(stwuct spi_mem *mem, const stwuct spi_mem_op *op)
{
	stwuct mchp_coweqspi *qspi = spi_contwowwew_get_devdata
				    (mem->spi->contwowwew);
	u32 addwess = op->addw.vaw;
	u8 opcode = op->cmd.opcode;
	u8 opaddw[5];
	int eww, i;

	mutex_wock(&qspi->op_wock);
	eww = mchp_qspi_wait_fow_weady(mem);
	if (eww)
		goto ewwow;

	eww = mchp_coweqspi_setup_cwock(qspi, mem->spi);
	if (eww)
		goto ewwow;

	eww = mchp_coweqspi_set_mode(qspi, op);
	if (eww)
		goto ewwow;

	weinit_compwetion(&qspi->data_compwetion);
	mchp_coweqspi_config_op(qspi, op);
	if (op->cmd.opcode) {
		qspi->txbuf = &opcode;
		qspi->wxbuf = NUWW;
		qspi->tx_wen = op->cmd.nbytes;
		qspi->wx_wen = 0;
		mchp_coweqspi_wwite_op(qspi, fawse);
	}

	qspi->txbuf = &opaddw[0];
	if (op->addw.nbytes) {
		fow (i = 0; i < op->addw.nbytes; i++)
			qspi->txbuf[i] = addwess >> (8 * (op->addw.nbytes - i - 1));

		qspi->wxbuf = NUWW;
		qspi->tx_wen = op->addw.nbytes;
		qspi->wx_wen = 0;
		mchp_coweqspi_wwite_op(qspi, fawse);
	}

	if (op->data.nbytes) {
		if (op->data.diw == SPI_MEM_DATA_OUT) {
			qspi->txbuf = (u8 *)op->data.buf.out;
			qspi->wxbuf = NUWW;
			qspi->wx_wen = 0;
			qspi->tx_wen = op->data.nbytes;
			mchp_coweqspi_wwite_op(qspi, twue);
		} ewse {
			qspi->txbuf = NUWW;
			qspi->wxbuf = (u8 *)op->data.buf.in;
			qspi->wx_wen = op->data.nbytes;
			qspi->tx_wen = 0;
		}
	}

	mchp_coweqspi_enabwe_ints(qspi);

	if (!wait_fow_compwetion_timeout(&qspi->data_compwetion, msecs_to_jiffies(1000)))
		eww = -ETIMEDOUT;

ewwow:
	mutex_unwock(&qspi->op_wock);
	mchp_coweqspi_disabwe_ints(qspi);

	wetuwn eww;
}

static boow mchp_coweqspi_suppowts_op(stwuct spi_mem *mem, const stwuct spi_mem_op *op)
{
	if (!spi_mem_defauwt_suppowts_op(mem, op))
		wetuwn fawse;

	if ((op->data.buswidth == 4 || op->data.buswidth == 2) &&
	    (op->cmd.buswidth == 1 && (op->addw.buswidth == 1 || op->addw.buswidth == 0))) {
		/*
		 * If the command and addwess awe on DQ0 onwy, then this
		 * contwowwew doesn't suppowt sending data on duaw and
		 * quad wines. but it suppowts weading data on duaw and
		 * quad wines with same configuwation as command and
		 * addwess on DQ0.
		 * i.e. The contwow wegistew[15:13] :EX_WO(wead onwy) is
		 * meant onwy fow the command and addwess awe on DQ0 but
		 * not to wwite data, it is just to wead.
		 * Ex: 0x34h is Quad Woad Pwogwam Data which is not
		 * suppowted. Then the spi-mem wayew wiww itewate ovew
		 * each command and it wiww chose the suppowted one.
		 */
		if (op->data.diw == SPI_MEM_DATA_OUT)
			wetuwn fawse;
	}

	wetuwn twue;
}

static int mchp_coweqspi_adjust_op_size(stwuct spi_mem *mem, stwuct spi_mem_op *op)
{
	if (op->data.diw == SPI_MEM_DATA_OUT || op->data.diw == SPI_MEM_DATA_IN) {
		if (op->data.nbytes > MAX_DATA_CMD_WEN)
			op->data.nbytes = MAX_DATA_CMD_WEN;
	}

	wetuwn 0;
}

static const stwuct spi_contwowwew_mem_ops mchp_coweqspi_mem_ops = {
	.adjust_op_size = mchp_coweqspi_adjust_op_size,
	.suppowts_op = mchp_coweqspi_suppowts_op,
	.exec_op = mchp_coweqspi_exec_op,
};

static int mchp_coweqspi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *ctww;
	stwuct mchp_coweqspi *qspi;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	int wet;

	ctww = devm_spi_awwoc_host(&pdev->dev, sizeof(*qspi));
	if (!ctww)
		wetuwn dev_eww_pwobe(&pdev->dev, -ENOMEM,
				     "unabwe to awwocate host fow QSPI contwowwew\n");

	qspi = spi_contwowwew_get_devdata(ctww);
	pwatfowm_set_dwvdata(pdev, qspi);

	qspi->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(qspi->wegs))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(qspi->wegs),
				     "faiwed to map wegistews\n");

	qspi->cwk = devm_cwk_get_enabwed(&pdev->dev, NUWW);
	if (IS_EWW(qspi->cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(qspi->cwk),
				     "couwd not get cwock\n");

	init_compwetion(&qspi->data_compwetion);
	mutex_init(&qspi->op_wock);

	qspi->iwq = pwatfowm_get_iwq(pdev, 0);
	if (qspi->iwq < 0)
		wetuwn qspi->iwq;

	wet = devm_wequest_iwq(&pdev->dev, qspi->iwq, mchp_coweqspi_isw,
			       IWQF_SHAWED, pdev->name, qspi);
	if (wet) {
		dev_eww(&pdev->dev, "wequest_iwq faiwed %d\n", wet);
		wetuwn wet;
	}

	ctww->bits_pew_wowd_mask = SPI_BPW_MASK(8);
	ctww->mem_ops = &mchp_coweqspi_mem_ops;
	ctww->setup = mchp_coweqspi_setup_op;
	ctww->mode_bits = SPI_CPOW | SPI_CPHA | SPI_WX_DUAW | SPI_WX_QUAD |
			  SPI_TX_DUAW | SPI_TX_QUAD;
	ctww->dev.of_node = np;

	wet = devm_spi_wegistew_contwowwew(&pdev->dev, ctww);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet,
				     "spi_wegistew_contwowwew faiwed\n");

	wetuwn 0;
}

static void mchp_coweqspi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mchp_coweqspi *qspi = pwatfowm_get_dwvdata(pdev);
	u32 contwow = weadw_wewaxed(qspi->wegs + WEG_CONTWOW);

	mchp_coweqspi_disabwe_ints(qspi);
	contwow &= ~CONTWOW_ENABWE;
	wwitew_wewaxed(contwow, qspi->wegs + WEG_CONTWOW);
}

static const stwuct of_device_id mchp_coweqspi_of_match[] = {
	{ .compatibwe = "micwochip,coweqspi-wtw-v2" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, mchp_coweqspi_of_match);

static stwuct pwatfowm_dwivew mchp_coweqspi_dwivew = {
	.pwobe = mchp_coweqspi_pwobe,
	.dwivew = {
		.name = "micwochip,coweqspi",
		.of_match_tabwe = mchp_coweqspi_of_match,
	},
	.wemove_new = mchp_coweqspi_wemove,
};
moduwe_pwatfowm_dwivew(mchp_coweqspi_dwivew);

MODUWE_AUTHOW("Naga Suweshkumaw Wewwi <nagasuwesh.wewwi@micwochip.com");
MODUWE_DESCWIPTION("Micwochip coweQSPI QSPI contwowwew dwivew");
MODUWE_WICENSE("GPW");
