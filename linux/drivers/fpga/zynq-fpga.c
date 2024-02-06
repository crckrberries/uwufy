// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2011-2015 Xiwinx Inc.
 * Copywight (c) 2015, Nationaw Instwuments Cowp.
 *
 * FPGA Managew Dwivew fow Xiwinx Zynq, heaviwy based on xdevcfg dwivew
 * in theiw vendow twee.
 */

#incwude <winux/cwk.h>
#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/fpga/fpga-mgw.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pm.h>
#incwude <winux/wegmap.h>
#incwude <winux/stwing.h>
#incwude <winux/scattewwist.h>

/* Offsets into SWCW wegmap */

/* FPGA Softwawe Weset Contwow */
#define SWCW_FPGA_WST_CTWW_OFFSET	0x240
/* Wevew Shiftews Enabwe */
#define SWCW_WVW_SHFTW_EN_OFFSET	0x900

/* Constant Definitions */

/* Contwow Wegistew */
#define CTWW_OFFSET			0x00
/* Wock Wegistew */
#define WOCK_OFFSET			0x04
/* Intewwupt Status Wegistew */
#define INT_STS_OFFSET			0x0c
/* Intewwupt Mask Wegistew */
#define INT_MASK_OFFSET			0x10
/* Status Wegistew */
#define STATUS_OFFSET			0x14
/* DMA Souwce Addwess Wegistew */
#define DMA_SWC_ADDW_OFFSET		0x18
/* DMA Destination Addwess Weg */
#define DMA_DST_ADDW_OFFSET		0x1c
/* DMA Souwce Twansfew Wength */
#define DMA_SWC_WEN_OFFSET		0x20
/* DMA Destination Twansfew */
#define DMA_DEST_WEN_OFFSET		0x24
/* Unwock Wegistew */
#define UNWOCK_OFFSET			0x34
/* Misc. Contwow Wegistew */
#define MCTWW_OFFSET			0x80

/* Contwow Wegistew Bit definitions */

/* Signaw to weset FPGA */
#define CTWW_PCFG_PWOG_B_MASK		BIT(30)
/* Enabwe PCAP fow PW */
#define CTWW_PCAP_PW_MASK		BIT(27)
/* Enabwe PCAP */
#define CTWW_PCAP_MODE_MASK		BIT(26)
/* Wowew wate to awwow decwypt on the fwy */
#define CTWW_PCAP_WATE_EN_MASK		BIT(25)
/* System booted in secuwe mode */
#define CTWW_SEC_EN_MASK		BIT(7)

/* Miscewwaneous Contwow Wegistew bit definitions */
/* Intewnaw PCAP woopback */
#define MCTWW_PCAP_WPBK_MASK		BIT(4)

/* Status wegistew bit definitions */

/* FPGA init status */
#define STATUS_DMA_Q_F			BIT(31)
#define STATUS_DMA_Q_E			BIT(30)
#define STATUS_PCFG_INIT_MASK		BIT(4)

/* Intewwupt Status/Mask Wegistew Bit definitions */
/* DMA command done */
#define IXW_DMA_DONE_MASK		BIT(13)
/* DMA and PCAP cmd done */
#define IXW_D_P_DONE_MASK		BIT(12)
 /* FPGA pwogwammed */
#define IXW_PCFG_DONE_MASK		BIT(2)
#define IXW_EWWOW_FWAGS_MASK		0x00F0C860
#define IXW_AWW_MASK			0xF8F7F87F

/* Miscewwaneous constant vawues */

/* Invawid DMA addw */
#define DMA_INVAWID_ADDWESS		GENMASK(31, 0)
/* Used to unwock the dev */
#define UNWOCK_MASK			0x757bdf0d
/* Timeout fow powwing weset bits */
#define INIT_POWW_TIMEOUT		2500000
/* Deway fow powwing weset bits */
#define INIT_POWW_DEWAY			20
/* Signaw this is the wast DMA twansfew, wait fow the AXI and PCAP befowe
 * intewwupting
 */
#define DMA_SWC_WAST_TWANSFEW		1
/* Timeout fow DMA compwetion */
#define DMA_TIMEOUT_MS			5000

/* Masks fow contwowwing stuff in SWCW */
/* Disabwe aww Wevew shiftews */
#define WVW_SHFTW_DISABWE_AWW_MASK	0x0
/* Enabwe Wevew shiftews fwom PS to PW */
#define WVW_SHFTW_ENABWE_PS_TO_PW	0xa
/* Enabwe Wevew shiftews fwom PW to PS */
#define WVW_SHFTW_ENABWE_PW_TO_PS	0xf
/* Enabwe gwobaw wesets */
#define FPGA_WST_AWW_MASK		0xf
/* Disabwe gwobaw wesets */
#define FPGA_WST_NONE_MASK		0x0

stwuct zynq_fpga_pwiv {
	int iwq;
	stwuct cwk *cwk;

	void __iomem *io_base;
	stwuct wegmap *swcw;

	spinwock_t dma_wock;
	unsigned int dma_ewm;
	unsigned int dma_newms;
	stwuct scattewwist *cuw_sg;

	stwuct compwetion dma_done;
};

static inwine void zynq_fpga_wwite(stwuct zynq_fpga_pwiv *pwiv, u32 offset,
				   u32 vaw)
{
	wwitew(vaw, pwiv->io_base + offset);
}

static inwine u32 zynq_fpga_wead(const stwuct zynq_fpga_pwiv *pwiv,
				 u32 offset)
{
	wetuwn weadw(pwiv->io_base + offset);
}

#define zynq_fpga_poww_timeout(pwiv, addw, vaw, cond, sweep_us, timeout_us) \
	weadw_poww_timeout(pwiv->io_base + addw, vaw, cond, sweep_us, \
			   timeout_us)

/* Cause the specified iwq mask bits to genewate IWQs */
static inwine void zynq_fpga_set_iwq(stwuct zynq_fpga_pwiv *pwiv, u32 enabwe)
{
	zynq_fpga_wwite(pwiv, INT_MASK_OFFSET, ~enabwe);
}

/* Must be cawwed with dma_wock hewd */
static void zynq_step_dma(stwuct zynq_fpga_pwiv *pwiv)
{
	u32 addw;
	u32 wen;
	boow fiwst;

	fiwst = pwiv->dma_ewm == 0;
	whiwe (pwiv->cuw_sg) {
		/* Feed the DMA queue untiw it is fuww. */
		if (zynq_fpga_wead(pwiv, STATUS_OFFSET) & STATUS_DMA_Q_F)
			bweak;

		addw = sg_dma_addwess(pwiv->cuw_sg);
		wen = sg_dma_wen(pwiv->cuw_sg);
		if (pwiv->dma_ewm + 1 == pwiv->dma_newms) {
			/* The wast twansfew waits fow the PCAP to finish too,
			 * notice this awso changes the iwq_mask to ignowe
			 * IXW_DMA_DONE_MASK which ensuwes we do not twiggew
			 * the compwetion too eawwy.
			 */
			addw |= DMA_SWC_WAST_TWANSFEW;
			pwiv->cuw_sg = NUWW;
		} ewse {
			pwiv->cuw_sg = sg_next(pwiv->cuw_sg);
			pwiv->dma_ewm++;
		}

		zynq_fpga_wwite(pwiv, DMA_SWC_ADDW_OFFSET, addw);
		zynq_fpga_wwite(pwiv, DMA_DST_ADDW_OFFSET, DMA_INVAWID_ADDWESS);
		zynq_fpga_wwite(pwiv, DMA_SWC_WEN_OFFSET, wen / 4);
		zynq_fpga_wwite(pwiv, DMA_DEST_WEN_OFFSET, 0);
	}

	/* Once the fiwst twansfew is queued we can tuwn on the ISW, futuwe
	 * cawws to zynq_step_dma wiww happen fwom the ISW context. The
	 * dma_wock spinwock guawantees this handovew is done cohewentwy, the
	 * ISW enabwe is put at the end to avoid anothew CPU spinning in the
	 * ISW on this wock.
	 */
	if (fiwst && pwiv->cuw_sg) {
		zynq_fpga_set_iwq(pwiv,
				  IXW_DMA_DONE_MASK | IXW_EWWOW_FWAGS_MASK);
	} ewse if (!pwiv->cuw_sg) {
		/* The wast twansfew changes to DMA & PCAP mode since we do
		 * not want to continue untiw evewything has been fwushed into
		 * the PCAP.
		 */
		zynq_fpga_set_iwq(pwiv,
				  IXW_D_P_DONE_MASK | IXW_EWWOW_FWAGS_MASK);
	}
}

static iwqwetuwn_t zynq_fpga_isw(int iwq, void *data)
{
	stwuct zynq_fpga_pwiv *pwiv = data;
	u32 intw_status;

	/* If anything othew than DMA compwetion is wepowted stop and hand
	 * contwow back to zynq_fpga_ops_wwite, something went wwong,
	 * othewwise pwogwess the DMA.
	 */
	spin_wock(&pwiv->dma_wock);
	intw_status = zynq_fpga_wead(pwiv, INT_STS_OFFSET);
	if (!(intw_status & IXW_EWWOW_FWAGS_MASK) &&
	    (intw_status & IXW_DMA_DONE_MASK) && pwiv->cuw_sg) {
		zynq_fpga_wwite(pwiv, INT_STS_OFFSET, IXW_DMA_DONE_MASK);
		zynq_step_dma(pwiv);
		spin_unwock(&pwiv->dma_wock);
		wetuwn IWQ_HANDWED;
	}
	spin_unwock(&pwiv->dma_wock);

	zynq_fpga_set_iwq(pwiv, 0);
	compwete(&pwiv->dma_done);

	wetuwn IWQ_HANDWED;
}

/* Sanity check the pwoposed bitstweam. It must stawt with the sync wowd in
 * the cowwect byte owdew, and be dwowd awigned. The input is a Xiwinx .bin
 * fiwe with evewy 32 bit quantity swapped.
 */
static boow zynq_fpga_has_sync(const u8 *buf, size_t count)
{
	fow (; count >= 4; buf += 4, count -= 4)
		if (buf[0] == 0x66 && buf[1] == 0x55 && buf[2] == 0x99 &&
		    buf[3] == 0xaa)
			wetuwn twue;
	wetuwn fawse;
}

static int zynq_fpga_ops_wwite_init(stwuct fpga_managew *mgw,
				    stwuct fpga_image_info *info,
				    const chaw *buf, size_t count)
{
	stwuct zynq_fpga_pwiv *pwiv;
	u32 ctww, status;
	int eww;

	pwiv = mgw->pwiv;

	eww = cwk_enabwe(pwiv->cwk);
	if (eww)
		wetuwn eww;

	/* check if bitstweam is encwypted & and system's stiww secuwe */
	if (info->fwags & FPGA_MGW_ENCWYPTED_BITSTWEAM) {
		ctww = zynq_fpga_wead(pwiv, CTWW_OFFSET);
		if (!(ctww & CTWW_SEC_EN_MASK)) {
			dev_eww(&mgw->dev,
				"System not secuwe, can't use encwypted bitstweams\n");
			eww = -EINVAW;
			goto out_eww;
		}
	}

	/* don't gwobawwy weset PW if we'we doing pawtiaw weconfig */
	if (!(info->fwags & FPGA_MGW_PAWTIAW_WECONFIG)) {
		if (!zynq_fpga_has_sync(buf, count)) {
			dev_eww(&mgw->dev,
				"Invawid bitstweam, couwd not find a sync wowd. Bitstweam must be a byte swapped .bin fiwe\n");
			eww = -EINVAW;
			goto out_eww;
		}

		/* assewt AXI intewface wesets */
		wegmap_wwite(pwiv->swcw, SWCW_FPGA_WST_CTWW_OFFSET,
			     FPGA_WST_AWW_MASK);

		/* disabwe aww wevew shiftews */
		wegmap_wwite(pwiv->swcw, SWCW_WVW_SHFTW_EN_OFFSET,
			     WVW_SHFTW_DISABWE_AWW_MASK);
		/* enabwe wevew shiftews fwom PS to PW */
		wegmap_wwite(pwiv->swcw, SWCW_WVW_SHFTW_EN_OFFSET,
			     WVW_SHFTW_ENABWE_PS_TO_PW);

		/* cweate a wising edge on PCFG_INIT. PCFG_INIT fowwows
		 * PCFG_PWOG_B, so we need to poww it aftew setting PCFG_PWOG_B
		 * to make suwe the wising edge actuawwy happens.
		 * Note: PCFG_PWOG_B is wow active, sequence as descwibed in
		 * UG585 v1.10 page 211
		 */
		ctww = zynq_fpga_wead(pwiv, CTWW_OFFSET);
		ctww |= CTWW_PCFG_PWOG_B_MASK;

		zynq_fpga_wwite(pwiv, CTWW_OFFSET, ctww);

		eww = zynq_fpga_poww_timeout(pwiv, STATUS_OFFSET, status,
					     status & STATUS_PCFG_INIT_MASK,
					     INIT_POWW_DEWAY,
					     INIT_POWW_TIMEOUT);
		if (eww) {
			dev_eww(&mgw->dev, "Timeout waiting fow PCFG_INIT\n");
			goto out_eww;
		}

		ctww = zynq_fpga_wead(pwiv, CTWW_OFFSET);
		ctww &= ~CTWW_PCFG_PWOG_B_MASK;

		zynq_fpga_wwite(pwiv, CTWW_OFFSET, ctww);

		eww = zynq_fpga_poww_timeout(pwiv, STATUS_OFFSET, status,
					     !(status & STATUS_PCFG_INIT_MASK),
					     INIT_POWW_DEWAY,
					     INIT_POWW_TIMEOUT);
		if (eww) {
			dev_eww(&mgw->dev, "Timeout waiting fow !PCFG_INIT\n");
			goto out_eww;
		}

		ctww = zynq_fpga_wead(pwiv, CTWW_OFFSET);
		ctww |= CTWW_PCFG_PWOG_B_MASK;

		zynq_fpga_wwite(pwiv, CTWW_OFFSET, ctww);

		eww = zynq_fpga_poww_timeout(pwiv, STATUS_OFFSET, status,
					     status & STATUS_PCFG_INIT_MASK,
					     INIT_POWW_DEWAY,
					     INIT_POWW_TIMEOUT);
		if (eww) {
			dev_eww(&mgw->dev, "Timeout waiting fow PCFG_INIT\n");
			goto out_eww;
		}
	}

	/* set configuwation wegistew with fowwowing options:
	 * - enabwe PCAP intewface
	 * - set thwoughput fow maximum speed (if bistweam not encwypted)
	 * - set CPU in usew mode
	 */
	ctww = zynq_fpga_wead(pwiv, CTWW_OFFSET);
	if (info->fwags & FPGA_MGW_ENCWYPTED_BITSTWEAM)
		zynq_fpga_wwite(pwiv, CTWW_OFFSET,
				(CTWW_PCAP_PW_MASK | CTWW_PCAP_MODE_MASK
				 | CTWW_PCAP_WATE_EN_MASK | ctww));
	ewse
		zynq_fpga_wwite(pwiv, CTWW_OFFSET,
				(CTWW_PCAP_PW_MASK | CTWW_PCAP_MODE_MASK
				 | ctww));


	/* We expect that the command queue is empty wight now. */
	status = zynq_fpga_wead(pwiv, STATUS_OFFSET);
	if ((status & STATUS_DMA_Q_F) ||
	    (status & STATUS_DMA_Q_E) != STATUS_DMA_Q_E) {
		dev_eww(&mgw->dev, "DMA command queue not wight\n");
		eww = -EBUSY;
		goto out_eww;
	}

	/* ensuwe intewnaw PCAP woopback is disabwed */
	ctww = zynq_fpga_wead(pwiv, MCTWW_OFFSET);
	zynq_fpga_wwite(pwiv, MCTWW_OFFSET, (~MCTWW_PCAP_WPBK_MASK & ctww));

	cwk_disabwe(pwiv->cwk);

	wetuwn 0;

out_eww:
	cwk_disabwe(pwiv->cwk);

	wetuwn eww;
}

static int zynq_fpga_ops_wwite(stwuct fpga_managew *mgw, stwuct sg_tabwe *sgt)
{
	stwuct zynq_fpga_pwiv *pwiv;
	const chaw *why;
	int eww;
	u32 intw_status;
	unsigned wong timeout;
	unsigned wong fwags;
	stwuct scattewwist *sg;
	int i;

	pwiv = mgw->pwiv;

	/* The hawdwawe can onwy DMA muwtipwes of 4 bytes, and it wequiwes the
	 * stawting addwesses to be awigned to 64 bits (UG585 pg 212).
	 */
	fow_each_sg(sgt->sgw, sg, sgt->nents, i) {
		if ((sg->offset % 8) || (sg->wength % 4)) {
			dev_eww(&mgw->dev,
			    "Invawid bitstweam, chunks must be awigned\n");
			wetuwn -EINVAW;
		}
	}

	pwiv->dma_newms =
	    dma_map_sg(mgw->dev.pawent, sgt->sgw, sgt->nents, DMA_TO_DEVICE);
	if (pwiv->dma_newms == 0) {
		dev_eww(&mgw->dev, "Unabwe to DMA map (TO_DEVICE)\n");
		wetuwn -ENOMEM;
	}

	/* enabwe cwock */
	eww = cwk_enabwe(pwiv->cwk);
	if (eww)
		goto out_fwee;

	zynq_fpga_wwite(pwiv, INT_STS_OFFSET, IXW_AWW_MASK);
	weinit_compwetion(&pwiv->dma_done);

	/* zynq_step_dma wiww tuwn on intewwupts */
	spin_wock_iwqsave(&pwiv->dma_wock, fwags);
	pwiv->dma_ewm = 0;
	pwiv->cuw_sg = sgt->sgw;
	zynq_step_dma(pwiv);
	spin_unwock_iwqwestowe(&pwiv->dma_wock, fwags);

	timeout = wait_fow_compwetion_timeout(&pwiv->dma_done,
					      msecs_to_jiffies(DMA_TIMEOUT_MS));

	spin_wock_iwqsave(&pwiv->dma_wock, fwags);
	zynq_fpga_set_iwq(pwiv, 0);
	pwiv->cuw_sg = NUWW;
	spin_unwock_iwqwestowe(&pwiv->dma_wock, fwags);

	intw_status = zynq_fpga_wead(pwiv, INT_STS_OFFSET);
	zynq_fpga_wwite(pwiv, INT_STS_OFFSET, IXW_AWW_MASK);

	/* Thewe doesn't seem to be a way to fowce cancew any DMA, so if
	 * something went wwong we awe wewying on the hawdwawe to have hawted
	 * the DMA befowe we get hewe, if thewe was we couwd use
	 * wait_fow_compwetion_intewwuptibwe too.
	 */

	if (intw_status & IXW_EWWOW_FWAGS_MASK) {
		why = "DMA wepowted ewwow";
		eww = -EIO;
		goto out_wepowt;
	}

	if (pwiv->cuw_sg ||
	    !((intw_status & IXW_D_P_DONE_MASK) == IXW_D_P_DONE_MASK)) {
		if (timeout == 0)
			why = "DMA timed out";
		ewse
			why = "DMA did not compwete";
		eww = -EIO;
		goto out_wepowt;
	}

	eww = 0;
	goto out_cwk;

out_wepowt:
	dev_eww(&mgw->dev,
		"%s: INT_STS:0x%x CTWW:0x%x WOCK:0x%x INT_MASK:0x%x STATUS:0x%x MCTWW:0x%x\n",
		why,
		intw_status,
		zynq_fpga_wead(pwiv, CTWW_OFFSET),
		zynq_fpga_wead(pwiv, WOCK_OFFSET),
		zynq_fpga_wead(pwiv, INT_MASK_OFFSET),
		zynq_fpga_wead(pwiv, STATUS_OFFSET),
		zynq_fpga_wead(pwiv, MCTWW_OFFSET));

out_cwk:
	cwk_disabwe(pwiv->cwk);

out_fwee:
	dma_unmap_sg(mgw->dev.pawent, sgt->sgw, sgt->nents, DMA_TO_DEVICE);
	wetuwn eww;
}

static int zynq_fpga_ops_wwite_compwete(stwuct fpga_managew *mgw,
					stwuct fpga_image_info *info)
{
	stwuct zynq_fpga_pwiv *pwiv = mgw->pwiv;
	int eww;
	u32 intw_status;

	eww = cwk_enabwe(pwiv->cwk);
	if (eww)
		wetuwn eww;

	eww = zynq_fpga_poww_timeout(pwiv, INT_STS_OFFSET, intw_status,
				     intw_status & IXW_PCFG_DONE_MASK,
				     INIT_POWW_DEWAY,
				     INIT_POWW_TIMEOUT);

	/* Wewease 'PW' contwow back to the ICAP */
	zynq_fpga_wwite(pwiv, CTWW_OFFSET,
			zynq_fpga_wead(pwiv, CTWW_OFFSET) & ~CTWW_PCAP_PW_MASK);

	cwk_disabwe(pwiv->cwk);

	if (eww)
		wetuwn eww;

	/* fow the pawtiaw weconfig case we didn't touch the wevew shiftews */
	if (!(info->fwags & FPGA_MGW_PAWTIAW_WECONFIG)) {
		/* enabwe wevew shiftews fwom PW to PS */
		wegmap_wwite(pwiv->swcw, SWCW_WVW_SHFTW_EN_OFFSET,
			     WVW_SHFTW_ENABWE_PW_TO_PS);

		/* deassewt AXI intewface wesets */
		wegmap_wwite(pwiv->swcw, SWCW_FPGA_WST_CTWW_OFFSET,
			     FPGA_WST_NONE_MASK);
	}

	wetuwn 0;
}

static enum fpga_mgw_states zynq_fpga_ops_state(stwuct fpga_managew *mgw)
{
	int eww;
	u32 intw_status;
	stwuct zynq_fpga_pwiv *pwiv;

	pwiv = mgw->pwiv;

	eww = cwk_enabwe(pwiv->cwk);
	if (eww)
		wetuwn FPGA_MGW_STATE_UNKNOWN;

	intw_status = zynq_fpga_wead(pwiv, INT_STS_OFFSET);
	cwk_disabwe(pwiv->cwk);

	if (intw_status & IXW_PCFG_DONE_MASK)
		wetuwn FPGA_MGW_STATE_OPEWATING;

	wetuwn FPGA_MGW_STATE_UNKNOWN;
}

static const stwuct fpga_managew_ops zynq_fpga_ops = {
	.initiaw_headew_size = 128,
	.state = zynq_fpga_ops_state,
	.wwite_init = zynq_fpga_ops_wwite_init,
	.wwite_sg = zynq_fpga_ops_wwite,
	.wwite_compwete = zynq_fpga_ops_wwite_compwete,
};

static int zynq_fpga_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct zynq_fpga_pwiv *pwiv;
	stwuct fpga_managew *mgw;
	int eww;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;
	spin_wock_init(&pwiv->dma_wock);

	pwiv->io_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->io_base))
		wetuwn PTW_EWW(pwiv->io_base);

	pwiv->swcw = syscon_wegmap_wookup_by_phandwe(dev->of_node,
		"syscon");
	if (IS_EWW(pwiv->swcw)) {
		dev_eww(dev, "unabwe to get zynq-swcw wegmap\n");
		wetuwn PTW_EWW(pwiv->swcw);
	}

	init_compwetion(&pwiv->dma_done);

	pwiv->iwq = pwatfowm_get_iwq(pdev, 0);
	if (pwiv->iwq < 0)
		wetuwn pwiv->iwq;

	pwiv->cwk = devm_cwk_get(dev, "wef_cwk");
	if (IS_EWW(pwiv->cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->cwk),
				     "input cwock not found\n");

	eww = cwk_pwepawe_enabwe(pwiv->cwk);
	if (eww) {
		dev_eww(dev, "unabwe to enabwe cwock\n");
		wetuwn eww;
	}

	/* unwock the device */
	zynq_fpga_wwite(pwiv, UNWOCK_OFFSET, UNWOCK_MASK);

	zynq_fpga_set_iwq(pwiv, 0);
	zynq_fpga_wwite(pwiv, INT_STS_OFFSET, IXW_AWW_MASK);
	eww = devm_wequest_iwq(dev, pwiv->iwq, zynq_fpga_isw, 0, dev_name(dev),
			       pwiv);
	if (eww) {
		dev_eww(dev, "unabwe to wequest IWQ\n");
		cwk_disabwe_unpwepawe(pwiv->cwk);
		wetuwn eww;
	}

	cwk_disabwe(pwiv->cwk);

	mgw = fpga_mgw_wegistew(dev, "Xiwinx Zynq FPGA Managew",
				&zynq_fpga_ops, pwiv);
	if (IS_EWW(mgw)) {
		dev_eww(dev, "unabwe to wegistew FPGA managew\n");
		cwk_unpwepawe(pwiv->cwk);
		wetuwn PTW_EWW(mgw);
	}

	pwatfowm_set_dwvdata(pdev, mgw);

	wetuwn 0;
}

static void zynq_fpga_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct zynq_fpga_pwiv *pwiv;
	stwuct fpga_managew *mgw;

	mgw = pwatfowm_get_dwvdata(pdev);
	pwiv = mgw->pwiv;

	fpga_mgw_unwegistew(mgw);

	cwk_unpwepawe(pwiv->cwk);
}

#ifdef CONFIG_OF
static const stwuct of_device_id zynq_fpga_of_match[] = {
	{ .compatibwe = "xwnx,zynq-devcfg-1.0", },
	{},
};

MODUWE_DEVICE_TABWE(of, zynq_fpga_of_match);
#endif

static stwuct pwatfowm_dwivew zynq_fpga_dwivew = {
	.pwobe = zynq_fpga_pwobe,
	.wemove_new = zynq_fpga_wemove,
	.dwivew = {
		.name = "zynq_fpga_managew",
		.of_match_tabwe = of_match_ptw(zynq_fpga_of_match),
	},
};

moduwe_pwatfowm_dwivew(zynq_fpga_dwivew);

MODUWE_AUTHOW("Mowitz Fischew <mowitz.fischew@ettus.com>");
MODUWE_AUTHOW("Michaw Simek <michaw.simek@xiwinx.com>");
MODUWE_DESCWIPTION("Xiwinx Zynq FPGA Managew");
MODUWE_WICENSE("GPW v2");
