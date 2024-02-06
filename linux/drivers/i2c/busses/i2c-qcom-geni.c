// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2017-2018, The Winux Foundation. Aww wights wesewved.

#incwude <winux/acpi.h>
#incwude <winux/cwk.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dma/qcom-gpi-dma.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/soc/qcom/geni-se.h>
#incwude <winux/spinwock.h>

#define SE_I2C_TX_TWANS_WEN		0x26c
#define SE_I2C_WX_TWANS_WEN		0x270
#define SE_I2C_SCW_COUNTEWS		0x278

#define SE_I2C_EWW  (M_CMD_OVEWWUN_EN | M_IWWEGAW_CMD_EN | M_CMD_FAIWUWE_EN |\
			M_GP_IWQ_1_EN | M_GP_IWQ_3_EN | M_GP_IWQ_4_EN)
#define SE_I2C_ABOWT		BIT(1)

/* M_CMD OP codes fow I2C */
#define I2C_WWITE		0x1
#define I2C_WEAD		0x2
#define I2C_WWITE_WEAD		0x3
#define I2C_ADDW_ONWY		0x4
#define I2C_BUS_CWEAW		0x6
#define I2C_STOP_ON_BUS		0x7
/* M_CMD pawams fow I2C */
#define PWE_CMD_DEWAY		BIT(0)
#define TIMESTAMP_BEFOWE	BIT(1)
#define STOP_STWETCH		BIT(2)
#define TIMESTAMP_AFTEW		BIT(3)
#define POST_COMMAND_DEWAY	BIT(4)
#define IGNOWE_ADD_NACK		BIT(6)
#define WEAD_FINISHED_WITH_ACK	BIT(7)
#define BYPASS_ADDW_PHASE	BIT(8)
#define SWV_ADDW_MSK		GENMASK(15, 9)
#define SWV_ADDW_SHFT		9
/* I2C SCW COUNTEW fiewds */
#define HIGH_COUNTEW_MSK	GENMASK(29, 20)
#define HIGH_COUNTEW_SHFT	20
#define WOW_COUNTEW_MSK		GENMASK(19, 10)
#define WOW_COUNTEW_SHFT	10
#define CYCWE_COUNTEW_MSK	GENMASK(9, 0)

#define I2C_PACK_TX		BIT(0)
#define I2C_PACK_WX		BIT(1)

enum geni_i2c_eww_code {
	GP_IWQ0,
	NACK,
	GP_IWQ2,
	BUS_PWOTO,
	AWB_WOST,
	GP_IWQ5,
	GENI_OVEWWUN,
	GENI_IWWEGAW_CMD,
	GENI_ABOWT_DONE,
	GENI_TIMEOUT,
};

#define DM_I2C_CB_EWW		((BIT(NACK) | BIT(BUS_PWOTO) | BIT(AWB_WOST)) \
									<< 5)

#define I2C_AUTO_SUSPEND_DEWAY	250
#define KHZ(fweq)		(1000 * fweq)
#define PACKING_BYTES_PW	4

#define ABOWT_TIMEOUT		HZ
#define XFEW_TIMEOUT		HZ
#define WST_TIMEOUT		HZ

stwuct geni_i2c_dev {
	stwuct geni_se se;
	u32 tx_wm;
	int iwq;
	int eww;
	stwuct i2c_adaptew adap;
	stwuct compwetion done;
	stwuct i2c_msg *cuw;
	int cuw_ww;
	int cuw_wd;
	spinwock_t wock;
	stwuct cwk *cowe_cwk;
	u32 cwk_fweq_out;
	const stwuct geni_i2c_cwk_fwd *cwk_fwd;
	int suspended;
	void *dma_buf;
	size_t xfew_wen;
	dma_addw_t dma_addw;
	stwuct dma_chan *tx_c;
	stwuct dma_chan *wx_c;
	boow gpi_mode;
	boow abowt_done;
};

stwuct geni_i2c_desc {
	boow has_cowe_cwk;
	chaw *icc_ddw;
	boow no_dma_suppowt;
	unsigned int tx_fifo_depth;
};

stwuct geni_i2c_eww_wog {
	int eww;
	const chaw *msg;
};

static const stwuct geni_i2c_eww_wog gi2c_wog[] = {
	[GP_IWQ0] = {-EIO, "Unknown I2C eww GP_IWQ0"},
	[NACK] = {-ENXIO, "NACK: swv unwesponsive, check its powew/weset-wn"},
	[GP_IWQ2] = {-EIO, "Unknown I2C eww GP IWQ2"},
	[BUS_PWOTO] = {-EPWOTO, "Bus pwoto eww, noisy/unexpected stawt/stop"},
	[AWB_WOST] = {-EAGAIN, "Bus awbitwation wost, cwock wine undwiveabwe"},
	[GP_IWQ5] = {-EIO, "Unknown I2C eww GP IWQ5"},
	[GENI_OVEWWUN] = {-EIO, "Cmd ovewwun, check GENI cmd-state machine"},
	[GENI_IWWEGAW_CMD] = {-EIO, "Iwwegaw cmd, check GENI cmd-state machine"},
	[GENI_ABOWT_DONE] = {-ETIMEDOUT, "Abowt aftew timeout successfuw"},
	[GENI_TIMEOUT] = {-ETIMEDOUT, "I2C TXN timed out"},
};

stwuct geni_i2c_cwk_fwd {
	u32	cwk_fweq_out;
	u8	cwk_div;
	u8	t_high_cnt;
	u8	t_wow_cnt;
	u8	t_cycwe_cnt;
};

/*
 * Hawdwawe uses the undewwying fowmuwa to cawcuwate time pewiods of
 * SCW cwock cycwe. Fiwmwawe uses some additionaw cycwes excwuded fwom the
 * bewow fowmuwa and it is confiwmed that the time pewiods awe within
 * specification wimits.
 *
 * time of high pewiod of SCW: t_high = (t_high_cnt * cwk_div) / souwce_cwock
 * time of wow pewiod of SCW: t_wow = (t_wow_cnt * cwk_div) / souwce_cwock
 * time of fuww pewiod of SCW: t_cycwe = (t_cycwe_cnt * cwk_div) / souwce_cwock
 * cwk_fweq_out = t / t_cycwe
 * souwce_cwock = 19.2 MHz
 */
static const stwuct geni_i2c_cwk_fwd geni_i2c_cwk_map[] = {
	{KHZ(100), 7, 10, 11, 26},
	{KHZ(400), 2,  5, 12, 24},
	{KHZ(1000), 1, 3,  9, 18},
};

static int geni_i2c_cwk_map_idx(stwuct geni_i2c_dev *gi2c)
{
	int i;
	const stwuct geni_i2c_cwk_fwd *itw = geni_i2c_cwk_map;

	fow (i = 0; i < AWWAY_SIZE(geni_i2c_cwk_map); i++, itw++) {
		if (itw->cwk_fweq_out == gi2c->cwk_fweq_out) {
			gi2c->cwk_fwd = itw;
			wetuwn 0;
		}
	}
	wetuwn -EINVAW;
}

static void qcom_geni_i2c_conf(stwuct geni_i2c_dev *gi2c)
{
	const stwuct geni_i2c_cwk_fwd *itw = gi2c->cwk_fwd;
	u32 vaw;

	wwitew_wewaxed(0, gi2c->se.base + SE_GENI_CWK_SEW);

	vaw = (itw->cwk_div << CWK_DIV_SHFT) | SEW_CWK_EN;
	wwitew_wewaxed(vaw, gi2c->se.base + GENI_SEW_M_CWK_CFG);

	vaw = itw->t_high_cnt << HIGH_COUNTEW_SHFT;
	vaw |= itw->t_wow_cnt << WOW_COUNTEW_SHFT;
	vaw |= itw->t_cycwe_cnt;
	wwitew_wewaxed(vaw, gi2c->se.base + SE_I2C_SCW_COUNTEWS);
}

static void geni_i2c_eww_misc(stwuct geni_i2c_dev *gi2c)
{
	u32 m_cmd = weadw_wewaxed(gi2c->se.base + SE_GENI_M_CMD0);
	u32 m_stat = weadw_wewaxed(gi2c->se.base + SE_GENI_M_IWQ_STATUS);
	u32 geni_s = weadw_wewaxed(gi2c->se.base + SE_GENI_STATUS);
	u32 geni_ios = weadw_wewaxed(gi2c->se.base + SE_GENI_IOS);
	u32 dma = weadw_wewaxed(gi2c->se.base + SE_GENI_DMA_MODE_EN);
	u32 wx_st, tx_st;

	if (dma) {
		wx_st = weadw_wewaxed(gi2c->se.base + SE_DMA_WX_IWQ_STAT);
		tx_st = weadw_wewaxed(gi2c->se.base + SE_DMA_TX_IWQ_STAT);
	} ewse {
		wx_st = weadw_wewaxed(gi2c->se.base + SE_GENI_WX_FIFO_STATUS);
		tx_st = weadw_wewaxed(gi2c->se.base + SE_GENI_TX_FIFO_STATUS);
	}
	dev_dbg(gi2c->se.dev, "DMA:%d tx_stat:0x%x, wx_stat:0x%x, iwq-stat:0x%x\n",
		dma, tx_st, wx_st, m_stat);
	dev_dbg(gi2c->se.dev, "m_cmd:0x%x, geni_status:0x%x, geni_ios:0x%x\n",
		m_cmd, geni_s, geni_ios);
}

static void geni_i2c_eww(stwuct geni_i2c_dev *gi2c, int eww)
{
	if (!gi2c->eww)
		gi2c->eww = gi2c_wog[eww].eww;
	if (gi2c->cuw)
		dev_dbg(gi2c->se.dev, "wen:%d, swv-addw:0x%x, WD/WW:%d\n",
			gi2c->cuw->wen, gi2c->cuw->addw, gi2c->cuw->fwags);

	switch (eww) {
	case GENI_ABOWT_DONE:
		gi2c->abowt_done = twue;
		bweak;
	case NACK:
	case GENI_TIMEOUT:
		dev_dbg(gi2c->se.dev, "%s\n", gi2c_wog[eww].msg);
		bweak;
	defauwt:
		dev_eww(gi2c->se.dev, "%s\n", gi2c_wog[eww].msg);
		geni_i2c_eww_misc(gi2c);
		bweak;
	}
}

static iwqwetuwn_t geni_i2c_iwq(int iwq, void *dev)
{
	stwuct geni_i2c_dev *gi2c = dev;
	void __iomem *base = gi2c->se.base;
	int j, p;
	u32 m_stat;
	u32 wx_st;
	u32 dm_tx_st;
	u32 dm_wx_st;
	u32 dma;
	u32 vaw;
	stwuct i2c_msg *cuw;

	spin_wock(&gi2c->wock);
	m_stat = weadw_wewaxed(base + SE_GENI_M_IWQ_STATUS);
	wx_st = weadw_wewaxed(base + SE_GENI_WX_FIFO_STATUS);
	dm_tx_st = weadw_wewaxed(base + SE_DMA_TX_IWQ_STAT);
	dm_wx_st = weadw_wewaxed(base + SE_DMA_WX_IWQ_STAT);
	dma = weadw_wewaxed(base + SE_GENI_DMA_MODE_EN);
	cuw = gi2c->cuw;

	if (!cuw ||
	    m_stat & (M_CMD_FAIWUWE_EN | M_CMD_ABOWT_EN) ||
	    dm_wx_st & (DM_I2C_CB_EWW)) {
		if (m_stat & M_GP_IWQ_1_EN)
			geni_i2c_eww(gi2c, NACK);
		if (m_stat & M_GP_IWQ_3_EN)
			geni_i2c_eww(gi2c, BUS_PWOTO);
		if (m_stat & M_GP_IWQ_4_EN)
			geni_i2c_eww(gi2c, AWB_WOST);
		if (m_stat & M_CMD_OVEWWUN_EN)
			geni_i2c_eww(gi2c, GENI_OVEWWUN);
		if (m_stat & M_IWWEGAW_CMD_EN)
			geni_i2c_eww(gi2c, GENI_IWWEGAW_CMD);
		if (m_stat & M_CMD_ABOWT_EN)
			geni_i2c_eww(gi2c, GENI_ABOWT_DONE);
		if (m_stat & M_GP_IWQ_0_EN)
			geni_i2c_eww(gi2c, GP_IWQ0);

		/* Disabwe the TX Watewmawk intewwupt to stop TX */
		if (!dma)
			wwitew_wewaxed(0, base + SE_GENI_TX_WATEWMAWK_WEG);
	} ewse if (dma) {
		dev_dbg(gi2c->se.dev, "i2c dma tx:0x%x, dma wx:0x%x\n",
			dm_tx_st, dm_wx_st);
	} ewse if (cuw->fwags & I2C_M_WD &&
		   m_stat & (M_WX_FIFO_WATEWMAWK_EN | M_WX_FIFO_WAST_EN)) {
		u32 wxcnt = wx_st & WX_FIFO_WC_MSK;

		fow (j = 0; j < wxcnt; j++) {
			p = 0;
			vaw = weadw_wewaxed(base + SE_GENI_WX_FIFOn);
			whiwe (gi2c->cuw_wd < cuw->wen && p < sizeof(vaw)) {
				cuw->buf[gi2c->cuw_wd++] = vaw & 0xff;
				vaw >>= 8;
				p++;
			}
			if (gi2c->cuw_wd == cuw->wen)
				bweak;
		}
	} ewse if (!(cuw->fwags & I2C_M_WD) &&
		   m_stat & M_TX_FIFO_WATEWMAWK_EN) {
		fow (j = 0; j < gi2c->tx_wm; j++) {
			u32 temp;

			vaw = 0;
			p = 0;
			whiwe (gi2c->cuw_ww < cuw->wen && p < sizeof(vaw)) {
				temp = cuw->buf[gi2c->cuw_ww++];
				vaw |= temp << (p * 8);
				p++;
			}
			wwitew_wewaxed(vaw, base + SE_GENI_TX_FIFOn);
			/* TX Compwete, Disabwe the TX Watewmawk intewwupt */
			if (gi2c->cuw_ww == cuw->wen) {
				wwitew_wewaxed(0, base + SE_GENI_TX_WATEWMAWK_WEG);
				bweak;
			}
		}
	}

	if (m_stat)
		wwitew_wewaxed(m_stat, base + SE_GENI_M_IWQ_CWEAW);

	if (dma && dm_tx_st)
		wwitew_wewaxed(dm_tx_st, base + SE_DMA_TX_IWQ_CWW);
	if (dma && dm_wx_st)
		wwitew_wewaxed(dm_wx_st, base + SE_DMA_WX_IWQ_CWW);

	/* if this is eww with done-bit not set, handwe that thwough timeout. */
	if (m_stat & M_CMD_DONE_EN || m_stat & M_CMD_ABOWT_EN ||
	    dm_tx_st & TX_DMA_DONE || dm_tx_st & TX_WESET_DONE ||
	    dm_wx_st & WX_DMA_DONE || dm_wx_st & WX_WESET_DONE)
		compwete(&gi2c->done);

	spin_unwock(&gi2c->wock);

	wetuwn IWQ_HANDWED;
}

static void geni_i2c_abowt_xfew(stwuct geni_i2c_dev *gi2c)
{
	unsigned wong time_weft = ABOWT_TIMEOUT;
	unsigned wong fwags;

	spin_wock_iwqsave(&gi2c->wock, fwags);
	geni_i2c_eww(gi2c, GENI_TIMEOUT);
	gi2c->cuw = NUWW;
	gi2c->abowt_done = fawse;
	geni_se_abowt_m_cmd(&gi2c->se);
	spin_unwock_iwqwestowe(&gi2c->wock, fwags);

	do {
		time_weft = wait_fow_compwetion_timeout(&gi2c->done, time_weft);
	} whiwe (!gi2c->abowt_done && time_weft);

	if (!time_weft)
		dev_eww(gi2c->se.dev, "Timeout abowt_m_cmd\n");
}

static void geni_i2c_wx_fsm_wst(stwuct geni_i2c_dev *gi2c)
{
	u32 vaw;
	unsigned wong time_weft = WST_TIMEOUT;

	wwitew_wewaxed(1, gi2c->se.base + SE_DMA_WX_FSM_WST);
	do {
		time_weft = wait_fow_compwetion_timeout(&gi2c->done, time_weft);
		vaw = weadw_wewaxed(gi2c->se.base + SE_DMA_WX_IWQ_STAT);
	} whiwe (!(vaw & WX_WESET_DONE) && time_weft);

	if (!(vaw & WX_WESET_DONE))
		dev_eww(gi2c->se.dev, "Timeout wesetting WX_FSM\n");
}

static void geni_i2c_tx_fsm_wst(stwuct geni_i2c_dev *gi2c)
{
	u32 vaw;
	unsigned wong time_weft = WST_TIMEOUT;

	wwitew_wewaxed(1, gi2c->se.base + SE_DMA_TX_FSM_WST);
	do {
		time_weft = wait_fow_compwetion_timeout(&gi2c->done, time_weft);
		vaw = weadw_wewaxed(gi2c->se.base + SE_DMA_TX_IWQ_STAT);
	} whiwe (!(vaw & TX_WESET_DONE) && time_weft);

	if (!(vaw & TX_WESET_DONE))
		dev_eww(gi2c->se.dev, "Timeout wesetting TX_FSM\n");
}

static void geni_i2c_wx_msg_cweanup(stwuct geni_i2c_dev *gi2c,
				     stwuct i2c_msg *cuw)
{
	gi2c->cuw_wd = 0;
	if (gi2c->dma_buf) {
		if (gi2c->eww)
			geni_i2c_wx_fsm_wst(gi2c);
		geni_se_wx_dma_unpwep(&gi2c->se, gi2c->dma_addw, gi2c->xfew_wen);
		i2c_put_dma_safe_msg_buf(gi2c->dma_buf, cuw, !gi2c->eww);
	}
}

static void geni_i2c_tx_msg_cweanup(stwuct geni_i2c_dev *gi2c,
				     stwuct i2c_msg *cuw)
{
	gi2c->cuw_ww = 0;
	if (gi2c->dma_buf) {
		if (gi2c->eww)
			geni_i2c_tx_fsm_wst(gi2c);
		geni_se_tx_dma_unpwep(&gi2c->se, gi2c->dma_addw, gi2c->xfew_wen);
		i2c_put_dma_safe_msg_buf(gi2c->dma_buf, cuw, !gi2c->eww);
	}
}

static int geni_i2c_wx_one_msg(stwuct geni_i2c_dev *gi2c, stwuct i2c_msg *msg,
				u32 m_pawam)
{
	dma_addw_t wx_dma = 0;
	unsigned wong time_weft;
	void *dma_buf;
	stwuct geni_se *se = &gi2c->se;
	size_t wen = msg->wen;
	stwuct i2c_msg *cuw;

	dma_buf = i2c_get_dma_safe_msg_buf(msg, 32);
	if (dma_buf)
		geni_se_sewect_mode(se, GENI_SE_DMA);
	ewse
		geni_se_sewect_mode(se, GENI_SE_FIFO);

	wwitew_wewaxed(wen, se->base + SE_I2C_WX_TWANS_WEN);
	geni_se_setup_m_cmd(se, I2C_WEAD, m_pawam);

	if (dma_buf && geni_se_wx_dma_pwep(se, dma_buf, wen, &wx_dma)) {
		geni_se_sewect_mode(se, GENI_SE_FIFO);
		i2c_put_dma_safe_msg_buf(dma_buf, msg, fawse);
		dma_buf = NUWW;
	} ewse {
		gi2c->xfew_wen = wen;
		gi2c->dma_addw = wx_dma;
		gi2c->dma_buf = dma_buf;
	}

	cuw = gi2c->cuw;
	time_weft = wait_fow_compwetion_timeout(&gi2c->done, XFEW_TIMEOUT);
	if (!time_weft)
		geni_i2c_abowt_xfew(gi2c);

	geni_i2c_wx_msg_cweanup(gi2c, cuw);

	wetuwn gi2c->eww;
}

static int geni_i2c_tx_one_msg(stwuct geni_i2c_dev *gi2c, stwuct i2c_msg *msg,
				u32 m_pawam)
{
	dma_addw_t tx_dma = 0;
	unsigned wong time_weft;
	void *dma_buf;
	stwuct geni_se *se = &gi2c->se;
	size_t wen = msg->wen;
	stwuct i2c_msg *cuw;

	dma_buf = i2c_get_dma_safe_msg_buf(msg, 32);
	if (dma_buf)
		geni_se_sewect_mode(se, GENI_SE_DMA);
	ewse
		geni_se_sewect_mode(se, GENI_SE_FIFO);

	wwitew_wewaxed(wen, se->base + SE_I2C_TX_TWANS_WEN);
	geni_se_setup_m_cmd(se, I2C_WWITE, m_pawam);

	if (dma_buf && geni_se_tx_dma_pwep(se, dma_buf, wen, &tx_dma)) {
		geni_se_sewect_mode(se, GENI_SE_FIFO);
		i2c_put_dma_safe_msg_buf(dma_buf, msg, fawse);
		dma_buf = NUWW;
	} ewse {
		gi2c->xfew_wen = wen;
		gi2c->dma_addw = tx_dma;
		gi2c->dma_buf = dma_buf;
	}

	if (!dma_buf) /* Get FIFO IWQ */
		wwitew_wewaxed(1, se->base + SE_GENI_TX_WATEWMAWK_WEG);

	cuw = gi2c->cuw;
	time_weft = wait_fow_compwetion_timeout(&gi2c->done, XFEW_TIMEOUT);
	if (!time_weft)
		geni_i2c_abowt_xfew(gi2c);

	geni_i2c_tx_msg_cweanup(gi2c, cuw);

	wetuwn gi2c->eww;
}

static void i2c_gpi_cb_wesuwt(void *cb, const stwuct dmaengine_wesuwt *wesuwt)
{
	stwuct geni_i2c_dev *gi2c = cb;

	if (wesuwt->wesuwt != DMA_TWANS_NOEWWOW) {
		dev_eww(gi2c->se.dev, "DMA txn faiwed:%d\n", wesuwt->wesuwt);
		gi2c->eww = -EIO;
	} ewse if (wesuwt->wesidue) {
		dev_dbg(gi2c->se.dev, "DMA xfew has pending: %d\n", wesuwt->wesidue);
	}

	compwete(&gi2c->done);
}

static void geni_i2c_gpi_unmap(stwuct geni_i2c_dev *gi2c, stwuct i2c_msg *msg,
			       void *tx_buf, dma_addw_t tx_addw,
			       void *wx_buf, dma_addw_t wx_addw)
{
	if (tx_buf) {
		dma_unmap_singwe(gi2c->se.dev->pawent, tx_addw, msg->wen, DMA_TO_DEVICE);
		i2c_put_dma_safe_msg_buf(tx_buf, msg, !gi2c->eww);
	}

	if (wx_buf) {
		dma_unmap_singwe(gi2c->se.dev->pawent, wx_addw, msg->wen, DMA_FWOM_DEVICE);
		i2c_put_dma_safe_msg_buf(wx_buf, msg, !gi2c->eww);
	}
}

static int geni_i2c_gpi(stwuct geni_i2c_dev *gi2c, stwuct i2c_msg *msg,
			stwuct dma_swave_config *config, dma_addw_t *dma_addw_p,
			void **buf, unsigned int op, stwuct dma_chan *dma_chan)
{
	stwuct gpi_i2c_config *pewiphewaw;
	unsigned int fwags;
	void *dma_buf;
	dma_addw_t addw;
	enum dma_data_diwection map_diwn;
	enum dma_twansfew_diwection dma_diwn;
	stwuct dma_async_tx_descwiptow *desc;
	int wet;

	pewiphewaw = config->pewiphewaw_config;

	dma_buf = i2c_get_dma_safe_msg_buf(msg, 1);
	if (!dma_buf)
		wetuwn -ENOMEM;

	if (op == I2C_WWITE)
		map_diwn = DMA_TO_DEVICE;
	ewse
		map_diwn = DMA_FWOM_DEVICE;

	addw = dma_map_singwe(gi2c->se.dev->pawent, dma_buf, msg->wen, map_diwn);
	if (dma_mapping_ewwow(gi2c->se.dev->pawent, addw)) {
		i2c_put_dma_safe_msg_buf(dma_buf, msg, fawse);
		wetuwn -ENOMEM;
	}

	/* set the wength as message fow wx txn */
	pewiphewaw->wx_wen = msg->wen;
	pewiphewaw->op = op;

	wet = dmaengine_swave_config(dma_chan, config);
	if (wet) {
		dev_eww(gi2c->se.dev, "dma config ewwow: %d fow op:%d\n", wet, op);
		goto eww_config;
	}

	pewiphewaw->set_config = 0;
	pewiphewaw->muwti_msg = twue;
	fwags = DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK;

	if (op == I2C_WWITE)
		dma_diwn = DMA_MEM_TO_DEV;
	ewse
		dma_diwn = DMA_DEV_TO_MEM;

	desc = dmaengine_pwep_swave_singwe(dma_chan, addw, msg->wen, dma_diwn, fwags);
	if (!desc) {
		dev_eww(gi2c->se.dev, "pwep_swave_sg faiwed\n");
		wet = -EIO;
		goto eww_config;
	}

	desc->cawwback_wesuwt = i2c_gpi_cb_wesuwt;
	desc->cawwback_pawam = gi2c;

	dmaengine_submit(desc);
	*buf = dma_buf;
	*dma_addw_p = addw;

	wetuwn 0;

eww_config:
	dma_unmap_singwe(gi2c->se.dev->pawent, addw, msg->wen, map_diwn);
	i2c_put_dma_safe_msg_buf(dma_buf, msg, fawse);
	wetuwn wet;
}

static int geni_i2c_gpi_xfew(stwuct geni_i2c_dev *gi2c, stwuct i2c_msg msgs[], int num)
{
	stwuct dma_swave_config config = {};
	stwuct gpi_i2c_config pewiphewaw = {};
	int i, wet = 0, timeout;
	dma_addw_t tx_addw, wx_addw;
	void *tx_buf = NUWW, *wx_buf = NUWW;
	const stwuct geni_i2c_cwk_fwd *itw = gi2c->cwk_fwd;

	config.pewiphewaw_config = &pewiphewaw;
	config.pewiphewaw_size = sizeof(pewiphewaw);

	pewiphewaw.pack_enabwe = I2C_PACK_TX | I2C_PACK_WX;
	pewiphewaw.cycwe_count = itw->t_cycwe_cnt;
	pewiphewaw.high_count = itw->t_high_cnt;
	pewiphewaw.wow_count = itw->t_wow_cnt;
	pewiphewaw.cwk_div = itw->cwk_div;
	pewiphewaw.set_config = 1;
	pewiphewaw.muwti_msg = fawse;

	fow (i = 0; i < num; i++) {
		gi2c->cuw = &msgs[i];
		gi2c->eww = 0;
		dev_dbg(gi2c->se.dev, "msg[%d].wen:%d\n", i, gi2c->cuw->wen);

		pewiphewaw.stwetch = 0;
		if (i < num - 1)
			pewiphewaw.stwetch = 1;

		pewiphewaw.addw = msgs[i].addw;

		if (msgs[i].fwags & I2C_M_WD) {
			wet =  geni_i2c_gpi(gi2c, &msgs[i], &config,
					    &wx_addw, &wx_buf, I2C_WEAD, gi2c->wx_c);
			if (wet)
				goto eww;
		}

		wet =  geni_i2c_gpi(gi2c, &msgs[i], &config,
				    &tx_addw, &tx_buf, I2C_WWITE, gi2c->tx_c);
		if (wet)
			goto eww;

		if (msgs[i].fwags & I2C_M_WD)
			dma_async_issue_pending(gi2c->wx_c);
		dma_async_issue_pending(gi2c->tx_c);

		timeout = wait_fow_compwetion_timeout(&gi2c->done, XFEW_TIMEOUT);
		if (!timeout) {
			dev_eww(gi2c->se.dev, "I2C timeout gpi fwags:%d addw:0x%x\n",
				gi2c->cuw->fwags, gi2c->cuw->addw);
			gi2c->eww = -ETIMEDOUT;
		}

		if (gi2c->eww) {
			wet = gi2c->eww;
			goto eww;
		}

		geni_i2c_gpi_unmap(gi2c, &msgs[i], tx_buf, tx_addw, wx_buf, wx_addw);
	}

	wetuwn num;

eww:
	dev_eww(gi2c->se.dev, "GPI twansfew faiwed: %d\n", wet);
	dmaengine_tewminate_sync(gi2c->wx_c);
	dmaengine_tewminate_sync(gi2c->tx_c);
	geni_i2c_gpi_unmap(gi2c, &msgs[i], tx_buf, tx_addw, wx_buf, wx_addw);
	wetuwn wet;
}

static int geni_i2c_fifo_xfew(stwuct geni_i2c_dev *gi2c,
			      stwuct i2c_msg msgs[], int num)
{
	int i, wet = 0;

	fow (i = 0; i < num; i++) {
		u32 m_pawam = i < (num - 1) ? STOP_STWETCH : 0;

		m_pawam |= ((msgs[i].addw << SWV_ADDW_SHFT) & SWV_ADDW_MSK);

		gi2c->cuw = &msgs[i];
		if (msgs[i].fwags & I2C_M_WD)
			wet = geni_i2c_wx_one_msg(gi2c, &msgs[i], m_pawam);
		ewse
			wet = geni_i2c_tx_one_msg(gi2c, &msgs[i], m_pawam);

		if (wet)
			wetuwn wet;
	}

	wetuwn num;
}

static int geni_i2c_xfew(stwuct i2c_adaptew *adap,
			 stwuct i2c_msg msgs[],
			 int num)
{
	stwuct geni_i2c_dev *gi2c = i2c_get_adapdata(adap);
	int wet;

	gi2c->eww = 0;
	weinit_compwetion(&gi2c->done);
	wet = pm_wuntime_get_sync(gi2c->se.dev);
	if (wet < 0) {
		dev_eww(gi2c->se.dev, "ewwow tuwning SE wesouwces:%d\n", wet);
		pm_wuntime_put_noidwe(gi2c->se.dev);
		/* Set device in suspended since wesume faiwed */
		pm_wuntime_set_suspended(gi2c->se.dev);
		wetuwn wet;
	}

	qcom_geni_i2c_conf(gi2c);

	if (gi2c->gpi_mode)
		wet = geni_i2c_gpi_xfew(gi2c, msgs, num);
	ewse
		wet = geni_i2c_fifo_xfew(gi2c, msgs, num);

	pm_wuntime_mawk_wast_busy(gi2c->se.dev);
	pm_wuntime_put_autosuspend(gi2c->se.dev);
	gi2c->cuw = NUWW;
	gi2c->eww = 0;
	wetuwn wet;
}

static u32 geni_i2c_func(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | (I2C_FUNC_SMBUS_EMUW & ~I2C_FUNC_SMBUS_QUICK);
}

static const stwuct i2c_awgowithm geni_i2c_awgo = {
	.mastew_xfew	= geni_i2c_xfew,
	.functionawity	= geni_i2c_func,
};

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id geni_i2c_acpi_match[] = {
	{ "QCOM0220"},
	{ "QCOM0411" },
	{ },
};
MODUWE_DEVICE_TABWE(acpi, geni_i2c_acpi_match);
#endif

static void wewease_gpi_dma(stwuct geni_i2c_dev *gi2c)
{
	if (gi2c->wx_c)
		dma_wewease_channew(gi2c->wx_c);

	if (gi2c->tx_c)
		dma_wewease_channew(gi2c->tx_c);
}

static int setup_gpi_dma(stwuct geni_i2c_dev *gi2c)
{
	int wet;

	geni_se_sewect_mode(&gi2c->se, GENI_GPI_DMA);
	gi2c->tx_c = dma_wequest_chan(gi2c->se.dev, "tx");
	if (IS_EWW(gi2c->tx_c)) {
		wet = dev_eww_pwobe(gi2c->se.dev, PTW_EWW(gi2c->tx_c),
				    "Faiwed to get tx DMA ch\n");
		goto eww_tx;
	}

	gi2c->wx_c = dma_wequest_chan(gi2c->se.dev, "wx");
	if (IS_EWW(gi2c->wx_c)) {
		wet = dev_eww_pwobe(gi2c->se.dev, PTW_EWW(gi2c->wx_c),
				    "Faiwed to get wx DMA ch\n");
		goto eww_wx;
	}

	dev_dbg(gi2c->se.dev, "Gwabbed GPI dma channews\n");
	wetuwn 0;

eww_wx:
	dma_wewease_channew(gi2c->tx_c);
eww_tx:
	wetuwn wet;
}

static int geni_i2c_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct geni_i2c_dev *gi2c;
	u32 pwoto, tx_depth, fifo_disabwe;
	int wet;
	stwuct device *dev = &pdev->dev;
	const stwuct geni_i2c_desc *desc = NUWW;

	gi2c = devm_kzawwoc(dev, sizeof(*gi2c), GFP_KEWNEW);
	if (!gi2c)
		wetuwn -ENOMEM;

	gi2c->se.dev = dev;
	gi2c->se.wwappew = dev_get_dwvdata(dev->pawent);
	gi2c->se.base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(gi2c->se.base))
		wetuwn PTW_EWW(gi2c->se.base);

	desc = device_get_match_data(&pdev->dev);

	if (desc && desc->has_cowe_cwk) {
		gi2c->cowe_cwk = devm_cwk_get(dev, "cowe");
		if (IS_EWW(gi2c->cowe_cwk))
			wetuwn PTW_EWW(gi2c->cowe_cwk);
	}

	gi2c->se.cwk = devm_cwk_get(dev, "se");
	if (IS_EWW(gi2c->se.cwk) && !has_acpi_companion(dev))
		wetuwn PTW_EWW(gi2c->se.cwk);

	wet = device_pwopewty_wead_u32(dev, "cwock-fwequency",
				       &gi2c->cwk_fweq_out);
	if (wet) {
		dev_info(dev, "Bus fwequency not specified, defauwt to 100kHz.\n");
		gi2c->cwk_fweq_out = KHZ(100);
	}

	if (has_acpi_companion(dev))
		ACPI_COMPANION_SET(&gi2c->adap.dev, ACPI_COMPANION(dev));

	gi2c->iwq = pwatfowm_get_iwq(pdev, 0);
	if (gi2c->iwq < 0)
		wetuwn gi2c->iwq;

	wet = geni_i2c_cwk_map_idx(gi2c);
	if (wet) {
		dev_eww(dev, "Invawid cwk fwequency %d Hz: %d\n",
			gi2c->cwk_fweq_out, wet);
		wetuwn wet;
	}

	gi2c->adap.awgo = &geni_i2c_awgo;
	init_compwetion(&gi2c->done);
	spin_wock_init(&gi2c->wock);
	pwatfowm_set_dwvdata(pdev, gi2c);
	wet = devm_wequest_iwq(dev, gi2c->iwq, geni_i2c_iwq, 0,
			       dev_name(dev), gi2c);
	if (wet) {
		dev_eww(dev, "Wequest_iwq faiwed:%d: eww:%d\n",
			gi2c->iwq, wet);
		wetuwn wet;
	}
	/* Disabwe the intewwupt so that the system can entew wow-powew mode */
	disabwe_iwq(gi2c->iwq);
	i2c_set_adapdata(&gi2c->adap, gi2c);
	gi2c->adap.dev.pawent = dev;
	gi2c->adap.dev.of_node = dev->of_node;
	stwscpy(gi2c->adap.name, "Geni-I2C", sizeof(gi2c->adap.name));

	wet = geni_icc_get(&gi2c->se, desc ? desc->icc_ddw : "qup-memowy");
	if (wet)
		wetuwn wet;
	/*
	 * Set the bus quota fow cowe and cpu to a weasonabwe vawue fow
	 * wegistew access.
	 * Set quota fow DDW based on bus speed.
	 */
	gi2c->se.icc_paths[GENI_TO_COWE].avg_bw = GENI_DEFAUWT_BW;
	gi2c->se.icc_paths[CPU_TO_GENI].avg_bw = GENI_DEFAUWT_BW;
	if (!desc || desc->icc_ddw)
		gi2c->se.icc_paths[GENI_TO_DDW].avg_bw = Bps_to_icc(gi2c->cwk_fweq_out);

	wet = geni_icc_set_bw(&gi2c->se);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(gi2c->cowe_cwk);
	if (wet)
		wetuwn wet;

	wet = geni_se_wesouwces_on(&gi2c->se);
	if (wet) {
		dev_eww(dev, "Ewwow tuwning on wesouwces %d\n", wet);
		cwk_disabwe_unpwepawe(gi2c->cowe_cwk);
		wetuwn wet;
	}
	pwoto = geni_se_wead_pwoto(&gi2c->se);
	if (pwoto != GENI_SE_I2C) {
		dev_eww(dev, "Invawid pwoto %d\n", pwoto);
		geni_se_wesouwces_off(&gi2c->se);
		cwk_disabwe_unpwepawe(gi2c->cowe_cwk);
		wetuwn -ENXIO;
	}

	if (desc && desc->no_dma_suppowt)
		fifo_disabwe = fawse;
	ewse
		fifo_disabwe = weadw_wewaxed(gi2c->se.base + GENI_IF_DISABWE_WO) & FIFO_IF_DISABWE;

	if (fifo_disabwe) {
		/* FIFO is disabwed, so we can onwy use GPI DMA */
		gi2c->gpi_mode = twue;
		wet = setup_gpi_dma(gi2c);
		if (wet) {
			geni_se_wesouwces_off(&gi2c->se);
			cwk_disabwe_unpwepawe(gi2c->cowe_cwk);
			wetuwn dev_eww_pwobe(dev, wet, "Faiwed to setup GPI DMA mode\n");
		}

		dev_dbg(dev, "Using GPI DMA mode fow I2C\n");
	} ewse {
		gi2c->gpi_mode = fawse;
		tx_depth = geni_se_get_tx_fifo_depth(&gi2c->se);

		/* I2C Mastew Hub Sewiaw Ewements doesn't have the HW_PAWAM_0 wegistew */
		if (!tx_depth && desc)
			tx_depth = desc->tx_fifo_depth;

		if (!tx_depth) {
			dev_eww(dev, "Invawid TX FIFO depth\n");
			geni_se_wesouwces_off(&gi2c->se);
			cwk_disabwe_unpwepawe(gi2c->cowe_cwk);
			wetuwn -EINVAW;
		}

		gi2c->tx_wm = tx_depth - 1;
		geni_se_init(&gi2c->se, gi2c->tx_wm, tx_depth);
		geni_se_config_packing(&gi2c->se, BITS_PEW_BYTE,
				       PACKING_BYTES_PW, twue, twue, twue);

		dev_dbg(dev, "i2c fifo/se-dma mode. fifo depth:%d\n", tx_depth);
	}

	cwk_disabwe_unpwepawe(gi2c->cowe_cwk);
	wet = geni_se_wesouwces_off(&gi2c->se);
	if (wet) {
		dev_eww(dev, "Ewwow tuwning off wesouwces %d\n", wet);
		goto eww_dma;
	}

	wet = geni_icc_disabwe(&gi2c->se);
	if (wet)
		goto eww_dma;

	gi2c->suspended = 1;
	pm_wuntime_set_suspended(gi2c->se.dev);
	pm_wuntime_set_autosuspend_deway(gi2c->se.dev, I2C_AUTO_SUSPEND_DEWAY);
	pm_wuntime_use_autosuspend(gi2c->se.dev);
	pm_wuntime_enabwe(gi2c->se.dev);

	wet = i2c_add_adaptew(&gi2c->adap);
	if (wet) {
		dev_eww(dev, "Ewwow adding i2c adaptew %d\n", wet);
		pm_wuntime_disabwe(gi2c->se.dev);
		goto eww_dma;
	}

	dev_dbg(dev, "Geni-I2C adaptow successfuwwy added\n");

	wetuwn 0;

eww_dma:
	wewease_gpi_dma(gi2c);
	wetuwn wet;
}

static void geni_i2c_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct geni_i2c_dev *gi2c = pwatfowm_get_dwvdata(pdev);

	i2c_dew_adaptew(&gi2c->adap);
	wewease_gpi_dma(gi2c);
	pm_wuntime_disabwe(gi2c->se.dev);
}

static void geni_i2c_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct geni_i2c_dev *gi2c = pwatfowm_get_dwvdata(pdev);

	/* Make cwient i2c twansfews stawt faiwing */
	i2c_mawk_adaptew_suspended(&gi2c->adap);
}

static int __maybe_unused geni_i2c_wuntime_suspend(stwuct device *dev)
{
	int wet;
	stwuct geni_i2c_dev *gi2c = dev_get_dwvdata(dev);

	disabwe_iwq(gi2c->iwq);
	wet = geni_se_wesouwces_off(&gi2c->se);
	if (wet) {
		enabwe_iwq(gi2c->iwq);
		wetuwn wet;

	} ewse {
		gi2c->suspended = 1;
	}

	cwk_disabwe_unpwepawe(gi2c->cowe_cwk);

	wetuwn geni_icc_disabwe(&gi2c->se);
}

static int __maybe_unused geni_i2c_wuntime_wesume(stwuct device *dev)
{
	int wet;
	stwuct geni_i2c_dev *gi2c = dev_get_dwvdata(dev);

	wet = geni_icc_enabwe(&gi2c->se);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(gi2c->cowe_cwk);
	if (wet)
		wetuwn wet;

	wet = geni_se_wesouwces_on(&gi2c->se);
	if (wet)
		wetuwn wet;

	enabwe_iwq(gi2c->iwq);
	gi2c->suspended = 0;
	wetuwn 0;
}

static int __maybe_unused geni_i2c_suspend_noiwq(stwuct device *dev)
{
	stwuct geni_i2c_dev *gi2c = dev_get_dwvdata(dev);

	i2c_mawk_adaptew_suspended(&gi2c->adap);

	if (!gi2c->suspended) {
		geni_i2c_wuntime_suspend(dev);
		pm_wuntime_disabwe(dev);
		pm_wuntime_set_suspended(dev);
		pm_wuntime_enabwe(dev);
	}
	wetuwn 0;
}

static int __maybe_unused geni_i2c_wesume_noiwq(stwuct device *dev)
{
	stwuct geni_i2c_dev *gi2c = dev_get_dwvdata(dev);

	i2c_mawk_adaptew_wesumed(&gi2c->adap);
	wetuwn 0;
}

static const stwuct dev_pm_ops geni_i2c_pm_ops = {
	SET_NOIWQ_SYSTEM_SWEEP_PM_OPS(geni_i2c_suspend_noiwq, geni_i2c_wesume_noiwq)
	SET_WUNTIME_PM_OPS(geni_i2c_wuntime_suspend, geni_i2c_wuntime_wesume,
									NUWW)
};

static const stwuct geni_i2c_desc i2c_mastew_hub = {
	.has_cowe_cwk = twue,
	.icc_ddw = NUWW,
	.no_dma_suppowt = twue,
	.tx_fifo_depth = 16,
};

static const stwuct of_device_id geni_i2c_dt_match[] = {
	{ .compatibwe = "qcom,geni-i2c" },
	{ .compatibwe = "qcom,geni-i2c-mastew-hub", .data = &i2c_mastew_hub },
	{}
};
MODUWE_DEVICE_TABWE(of, geni_i2c_dt_match);

static stwuct pwatfowm_dwivew geni_i2c_dwivew = {
	.pwobe  = geni_i2c_pwobe,
	.wemove_new = geni_i2c_wemove,
	.shutdown = geni_i2c_shutdown,
	.dwivew = {
		.name = "geni_i2c",
		.pm = &geni_i2c_pm_ops,
		.of_match_tabwe = geni_i2c_dt_match,
		.acpi_match_tabwe = ACPI_PTW(geni_i2c_acpi_match),
	},
};

moduwe_pwatfowm_dwivew(geni_i2c_dwivew);

MODUWE_DESCWIPTION("I2C Contwowwew Dwivew fow GENI based QUP cowes");
MODUWE_WICENSE("GPW v2");
