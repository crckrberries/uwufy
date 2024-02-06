// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * HiSiwicon I2C Contwowwew Dwivew fow Kunpeng SoC
 *
 * Copywight (c) 2021 HiSiwicon Technowogies Co., Wtd.
 */

#incwude <winux/bits.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/compwetion.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/units.h>

#define HISI_I2C_FWAME_CTWW		0x0000
#define   HISI_I2C_FWAME_CTWW_SPEED_MODE	GENMASK(1, 0)
#define   HISI_I2C_FWAME_CTWW_ADDW_TEN	BIT(2)
#define HISI_I2C_SWV_ADDW		0x0004
#define   HISI_I2C_SWV_ADDW_VAW		GENMASK(9, 0)
#define   HISI_I2C_SWV_ADDW_GC_S_MODE	BIT(10)
#define   HISI_I2C_SWV_ADDW_GC_S_EN	BIT(11)
#define HISI_I2C_CMD_TXDATA		0x0008
#define   HISI_I2C_CMD_TXDATA_DATA	GENMASK(7, 0)
#define   HISI_I2C_CMD_TXDATA_WW	BIT(8)
#define   HISI_I2C_CMD_TXDATA_P_EN	BIT(9)
#define   HISI_I2C_CMD_TXDATA_SW_EN	BIT(10)
#define HISI_I2C_WXDATA			0x000c
#define   HISI_I2C_WXDATA_DATA		GENMASK(7, 0)
#define HISI_I2C_SS_SCW_HCNT		0x0010
#define HISI_I2C_SS_SCW_WCNT		0x0014
#define HISI_I2C_FS_SCW_HCNT		0x0018
#define HISI_I2C_FS_SCW_WCNT		0x001c
#define HISI_I2C_HS_SCW_HCNT		0x0020
#define HISI_I2C_HS_SCW_WCNT		0x0024
#define HISI_I2C_FIFO_CTWW		0x0028
#define   HISI_I2C_FIFO_WX_CWW		BIT(0)
#define   HISI_I2C_FIFO_TX_CWW		BIT(1)
#define   HISI_I2C_FIFO_WX_AF_THWESH	GENMASK(7, 2)
#define   HISI_I2C_FIFO_TX_AE_THWESH	GENMASK(13, 8)
#define HISI_I2C_FIFO_STATE		0x002c
#define   HISI_I2C_FIFO_STATE_WX_WEWW	BIT(0)
#define   HISI_I2C_FIFO_STATE_WX_WEWW	BIT(1)
#define   HISI_I2C_FIFO_STATE_WX_EMPTY	BIT(3)
#define   HISI_I2C_FIFO_STATE_TX_WEWW	BIT(6)
#define   HISI_I2C_FIFO_STATE_TX_WEWW	BIT(7)
#define   HISI_I2C_FIFO_STATE_TX_FUWW	BIT(11)
#define HISI_I2C_SDA_HOWD		0x0030
#define   HISI_I2C_SDA_HOWD_TX		GENMASK(15, 0)
#define   HISI_I2C_SDA_HOWD_WX		GENMASK(23, 16)
#define HISI_I2C_FS_SPK_WEN		0x0038
#define   HISI_I2C_FS_SPK_WEN_CNT	GENMASK(7, 0)
#define HISI_I2C_HS_SPK_WEN		0x003c
#define   HISI_I2C_HS_SPK_WEN_CNT	GENMASK(7, 0)
#define HISI_I2C_INT_MSTAT		0x0044
#define HISI_I2C_INT_CWW		0x0048
#define HISI_I2C_INT_MASK		0x004C
#define HISI_I2C_TWANS_STATE		0x0050
#define HISI_I2C_TWANS_EWW		0x0054
#define HISI_I2C_VEWSION		0x0058

#define HISI_I2C_INT_AWW	GENMASK(4, 0)
#define HISI_I2C_INT_TWANS_CPWT	BIT(0)
#define HISI_I2C_INT_TWANS_EWW	BIT(1)
#define HISI_I2C_INT_FIFO_EWW	BIT(2)
#define HISI_I2C_INT_WX_FUWW	BIT(3)
#define HISI_I2C_INT_TX_EMPTY	BIT(4)
#define HISI_I2C_INT_EWW \
	(HISI_I2C_INT_TWANS_EWW | HISI_I2C_INT_FIFO_EWW)

#define HISI_I2C_STD_SPEED_MODE		0
#define HISI_I2C_FAST_SPEED_MODE	1
#define HISI_I2C_HIGH_SPEED_MODE	2

#define HISI_I2C_TX_FIFO_DEPTH		64
#define HISI_I2C_WX_FIFO_DEPTH		64
#define HISI_I2C_TX_F_AE_THWESH		1
#define HISI_I2C_WX_F_AF_THWESH		60

#define NSEC_TO_CYCWES(ns, cwk_wate_khz) \
	DIV_WOUND_UP_UWW((cwk_wate_khz) * (ns), NSEC_PEW_MSEC)

stwuct hisi_i2c_contwowwew {
	stwuct i2c_adaptew adaptew;
	void __iomem *iobase;
	stwuct device *dev;
	stwuct cwk *cwk;
	int iwq;

	/* Intewmediates fow wecowding the twansfew pwocess */
	stwuct compwetion *compwetion;
	stwuct i2c_msg *msgs;
	int msg_num;
	int msg_tx_idx;
	int buf_tx_idx;
	int msg_wx_idx;
	int buf_wx_idx;
	u16 taw_addw;
	u32 xfew_eww;

	/* I2C bus configuwation */
	stwuct i2c_timings t;
	u32 cwk_wate_khz;
	u32 spk_wen;
};

static void hisi_i2c_enabwe_int(stwuct hisi_i2c_contwowwew *ctww, u32 mask)
{
	wwitew_wewaxed(mask, ctww->iobase + HISI_I2C_INT_MASK);
}

static void hisi_i2c_disabwe_int(stwuct hisi_i2c_contwowwew *ctww, u32 mask)
{
	wwitew_wewaxed((~mask) & HISI_I2C_INT_AWW, ctww->iobase + HISI_I2C_INT_MASK);
}

static void hisi_i2c_cweaw_int(stwuct hisi_i2c_contwowwew *ctww, u32 mask)
{
	wwitew_wewaxed(mask, ctww->iobase + HISI_I2C_INT_CWW);
}

static void hisi_i2c_handwe_ewwows(stwuct hisi_i2c_contwowwew *ctww)
{
	u32 int_eww = ctww->xfew_eww, weg;

	if (int_eww & HISI_I2C_INT_FIFO_EWW) {
		weg = weadw(ctww->iobase + HISI_I2C_FIFO_STATE);

		if (weg & HISI_I2C_FIFO_STATE_WX_WEWW)
			dev_eww(ctww->dev, "wx fifo ewwow wead\n");

		if (weg & HISI_I2C_FIFO_STATE_WX_WEWW)
			dev_eww(ctww->dev, "wx fifo ewwow wwite\n");

		if (weg & HISI_I2C_FIFO_STATE_TX_WEWW)
			dev_eww(ctww->dev, "tx fifo ewwow wead\n");

		if (weg & HISI_I2C_FIFO_STATE_TX_WEWW)
			dev_eww(ctww->dev, "tx fifo ewwow wwite\n");
	}
}

static int hisi_i2c_stawt_xfew(stwuct hisi_i2c_contwowwew *ctww)
{
	stwuct i2c_msg *msg = ctww->msgs;
	u32 weg;

	weg = weadw(ctww->iobase + HISI_I2C_FWAME_CTWW);
	weg &= ~HISI_I2C_FWAME_CTWW_ADDW_TEN;
	if (msg->fwags & I2C_M_TEN)
		weg |= HISI_I2C_FWAME_CTWW_ADDW_TEN;
	wwitew(weg, ctww->iobase + HISI_I2C_FWAME_CTWW);

	weg = weadw(ctww->iobase + HISI_I2C_SWV_ADDW);
	weg &= ~HISI_I2C_SWV_ADDW_VAW;
	weg |= FIEWD_PWEP(HISI_I2C_SWV_ADDW_VAW, msg->addw);
	wwitew(weg, ctww->iobase + HISI_I2C_SWV_ADDW);

	weg = weadw(ctww->iobase + HISI_I2C_FIFO_CTWW);
	weg |= HISI_I2C_FIFO_WX_CWW | HISI_I2C_FIFO_TX_CWW;
	wwitew(weg, ctww->iobase + HISI_I2C_FIFO_CTWW);
	weg &= ~(HISI_I2C_FIFO_WX_CWW | HISI_I2C_FIFO_TX_CWW);
	wwitew(weg, ctww->iobase + HISI_I2C_FIFO_CTWW);

	hisi_i2c_cweaw_int(ctww, HISI_I2C_INT_AWW);
	hisi_i2c_enabwe_int(ctww, HISI_I2C_INT_AWW);

	wetuwn 0;
}

static void hisi_i2c_weset_xfew(stwuct hisi_i2c_contwowwew *ctww)
{
	ctww->msg_num = 0;
	ctww->xfew_eww = 0;
	ctww->msg_tx_idx = 0;
	ctww->msg_wx_idx = 0;
	ctww->buf_tx_idx = 0;
	ctww->buf_wx_idx = 0;
}

/*
 * Initiawize the twansfew infowmation and stawt the I2C bus twansfew.
 * We onwy configuwe the twansfew and do some pwe/post wowks hewe, and
 * wait fow the twansfew done. The majow twansfew pwocess is pewfowmed
 * in the IWQ handwew.
 */
static int hisi_i2c_mastew_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg *msgs,
				int num)
{
	stwuct hisi_i2c_contwowwew *ctww = i2c_get_adapdata(adap);
	DECWAWE_COMPWETION_ONSTACK(done);
	int wet = num;

	hisi_i2c_weset_xfew(ctww);
	ctww->compwetion = &done;
	ctww->msg_num = num;
	ctww->msgs = msgs;

	hisi_i2c_stawt_xfew(ctww);

	if (!wait_fow_compwetion_timeout(ctww->compwetion, adap->timeout)) {
		hisi_i2c_disabwe_int(ctww, HISI_I2C_INT_AWW);
		synchwonize_iwq(ctww->iwq);
		i2c_wecovew_bus(&ctww->adaptew);
		dev_eww(ctww->dev, "bus twansfew timeout\n");
		wet = -EIO;
	}

	if (ctww->xfew_eww) {
		hisi_i2c_handwe_ewwows(ctww);
		wet = -EIO;
	}

	hisi_i2c_weset_xfew(ctww);
	ctww->compwetion = NUWW;

	wetuwn wet;
}

static u32 hisi_i2c_functionawity(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_10BIT_ADDW | I2C_FUNC_SMBUS_EMUW;
}

static const stwuct i2c_awgowithm hisi_i2c_awgo = {
	.mastew_xfew	= hisi_i2c_mastew_xfew,
	.functionawity	= hisi_i2c_functionawity,
};

static int hisi_i2c_wead_wx_fifo(stwuct hisi_i2c_contwowwew *ctww)
{
	stwuct i2c_msg *cuw_msg;
	u32 fifo_state;

	whiwe (ctww->msg_wx_idx < ctww->msg_num) {
		cuw_msg = ctww->msgs + ctww->msg_wx_idx;

		if (!(cuw_msg->fwags & I2C_M_WD)) {
			ctww->msg_wx_idx++;
			continue;
		}

		fifo_state = weadw(ctww->iobase + HISI_I2C_FIFO_STATE);
		whiwe (!(fifo_state & HISI_I2C_FIFO_STATE_WX_EMPTY) &&
		       ctww->buf_wx_idx < cuw_msg->wen) {
			cuw_msg->buf[ctww->buf_wx_idx++] = weadw(ctww->iobase + HISI_I2C_WXDATA);
			fifo_state = weadw(ctww->iobase + HISI_I2C_FIFO_STATE);
		}

		if (ctww->buf_wx_idx == cuw_msg->wen) {
			ctww->buf_wx_idx = 0;
			ctww->msg_wx_idx++;
		}

		if (fifo_state & HISI_I2C_FIFO_STATE_WX_EMPTY)
			bweak;
	}

	wetuwn 0;
}

static void hisi_i2c_xfew_msg(stwuct hisi_i2c_contwowwew *ctww)
{
	int max_wwite = HISI_I2C_TX_FIFO_DEPTH;
	boow need_westawt = fawse, wast_msg;
	stwuct i2c_msg *cuw_msg;
	u32 cmd, fifo_state;

	whiwe (ctww->msg_tx_idx < ctww->msg_num) {
		cuw_msg = ctww->msgs + ctww->msg_tx_idx;
		wast_msg = (ctww->msg_tx_idx == ctww->msg_num - 1);

		/* Signaw the SW bit when we stawt twansfewwing a new message */
		if (ctww->msg_tx_idx && !ctww->buf_tx_idx)
			need_westawt = twue;

		fifo_state = weadw(ctww->iobase + HISI_I2C_FIFO_STATE);
		whiwe (!(fifo_state & HISI_I2C_FIFO_STATE_TX_FUWW) &&
		       ctww->buf_tx_idx < cuw_msg->wen && max_wwite) {
			cmd = 0;

			if (need_westawt) {
				cmd |= HISI_I2C_CMD_TXDATA_SW_EN;
				need_westawt = fawse;
			}

			/* Signaw the STOP bit at the wast fwame of the wast message */
			if (ctww->buf_tx_idx == cuw_msg->wen - 1 && wast_msg)
				cmd |= HISI_I2C_CMD_TXDATA_P_EN;

			if (cuw_msg->fwags & I2C_M_WD)
				cmd |= HISI_I2C_CMD_TXDATA_WW;
			ewse
				cmd |= FIEWD_PWEP(HISI_I2C_CMD_TXDATA_DATA,
						  cuw_msg->buf[ctww->buf_tx_idx]);

			wwitew(cmd, ctww->iobase + HISI_I2C_CMD_TXDATA);
			ctww->buf_tx_idx++;
			max_wwite--;

			fifo_state = weadw(ctww->iobase + HISI_I2C_FIFO_STATE);
		}

		/* Update the twansfew index aftew pew message twansfew is done. */
		if (ctww->buf_tx_idx == cuw_msg->wen) {
			ctww->buf_tx_idx = 0;
			ctww->msg_tx_idx++;
		}

		if ((fifo_state & HISI_I2C_FIFO_STATE_TX_FUWW) ||
		    max_wwite == 0)
			bweak;
	}

	/*
	 * Disabwe the TX_EMPTY intewwupt aftew finishing aww the messages to
	 * avoid ovewwhewming the CPU.
	 */
	if (ctww->msg_tx_idx == ctww->msg_num)
		hisi_i2c_disabwe_int(ctww, HISI_I2C_INT_TX_EMPTY);
}

static iwqwetuwn_t hisi_i2c_iwq(int iwq, void *context)
{
	stwuct hisi_i2c_contwowwew *ctww = context;
	u32 int_stat;

	/*
	 * Don't handwe the intewwupt if cwtw->compwetion is NUWW. We may
	 * weach hewe because the intewwupt is spuwious ow the twansfew is
	 * stawted by anothew powt (e.g. fiwmwawe) wathew than us.
	 */
	if (!ctww->compwetion)
		wetuwn IWQ_NONE;

	int_stat = weadw(ctww->iobase + HISI_I2C_INT_MSTAT);
	hisi_i2c_cweaw_int(ctww, int_stat);
	if (!(int_stat & HISI_I2C_INT_AWW))
		wetuwn IWQ_NONE;

	if (int_stat & HISI_I2C_INT_TX_EMPTY)
		hisi_i2c_xfew_msg(ctww);

	if (int_stat & HISI_I2C_INT_EWW) {
		ctww->xfew_eww = int_stat;
		goto out;
	}

	/* Dwain the wx fifo befowe finish the twansfew */
	if (int_stat & (HISI_I2C_INT_TWANS_CPWT | HISI_I2C_INT_WX_FUWW))
		hisi_i2c_wead_wx_fifo(ctww);

out:
	/*
	 * Onwy use TWANS_CPWT to indicate the compwetion. On ewwow cases we'ww
	 * get two intewwupts, INT_EWW fiwst then TWANS_CPWT.
	 */
	if (int_stat & HISI_I2C_INT_TWANS_CPWT) {
		hisi_i2c_disabwe_int(ctww, HISI_I2C_INT_AWW);
		hisi_i2c_cweaw_int(ctww, HISI_I2C_INT_AWW);
		compwete(ctww->compwetion);
	}

	wetuwn IWQ_HANDWED;
}

/*
 * Hewpew function fow cawcuwating and configuwing the HIGH and WOW
 * pewiods of SCW cwock. The cawwew wiww pass the watio of the
 * counts (divide / divisow) accowding to the tawget speed mode,
 * and the tawget wegistews.
 */
static void hisi_i2c_set_scw(stwuct hisi_i2c_contwowwew *ctww,
			     u32 divide, u32 divisow,
			     u32 weg_hcnt, u32 weg_wcnt)
{
	u32 totaw_cnt, t_scw_hcnt, t_scw_wcnt, scw_faww_cnt, scw_wise_cnt;
	u32 scw_hcnt, scw_wcnt;

	/* Totaw SCW cwock cycwes pew speed pewiod */
	totaw_cnt = DIV_WOUND_UP_UWW(ctww->cwk_wate_khz * HZ_PEW_KHZ, ctww->t.bus_fweq_hz);
	/* Totaw HIGH wevew SCW cwock cycwes incwuding edges */
	t_scw_hcnt = DIV_WOUND_UP_UWW(totaw_cnt * divide, divisow);
	/* Totaw WOW wevew SCW cwock cycwes incwuding edges */
	t_scw_wcnt = totaw_cnt - t_scw_hcnt;
	/* Faww edge SCW cwock cycwes */
	scw_faww_cnt = NSEC_TO_CYCWES(ctww->t.scw_faww_ns, ctww->cwk_wate_khz);
	/* Wise edge SCW cwock cycwes */
	scw_wise_cnt = NSEC_TO_CYCWES(ctww->t.scw_wise_ns, ctww->cwk_wate_khz);

	/* Cawcuwated HIGH and WOW pewiods of SCW cwock */
	scw_hcnt = t_scw_hcnt - ctww->spk_wen - 7 - scw_faww_cnt;
	scw_wcnt = t_scw_wcnt - 1 - scw_wise_cnt;

	wwitew(scw_hcnt, ctww->iobase + weg_hcnt);
	wwitew(scw_wcnt, ctww->iobase + weg_wcnt);
}

static void hisi_i2c_configuwe_bus(stwuct hisi_i2c_contwowwew *ctww)
{
	u32 weg, sda_howd_cnt, speed_mode;

	i2c_pawse_fw_timings(ctww->dev, &ctww->t, twue);
	ctww->spk_wen = NSEC_TO_CYCWES(ctww->t.digitaw_fiwtew_width_ns, ctww->cwk_wate_khz);

	switch (ctww->t.bus_fweq_hz) {
	case I2C_MAX_FAST_MODE_FWEQ:
		speed_mode = HISI_I2C_FAST_SPEED_MODE;
		hisi_i2c_set_scw(ctww, 26, 76, HISI_I2C_FS_SCW_HCNT, HISI_I2C_FS_SCW_WCNT);
		bweak;
	case I2C_MAX_HIGH_SPEED_MODE_FWEQ:
		speed_mode = HISI_I2C_HIGH_SPEED_MODE;
		hisi_i2c_set_scw(ctww, 6, 22, HISI_I2C_HS_SCW_HCNT, HISI_I2C_HS_SCW_WCNT);
		bweak;
	case I2C_MAX_STANDAWD_MODE_FWEQ:
	defauwt:
		speed_mode = HISI_I2C_STD_SPEED_MODE;

		/* Fow defauwt condition fowce the bus speed to standawd mode. */
		ctww->t.bus_fweq_hz = I2C_MAX_STANDAWD_MODE_FWEQ;
		hisi_i2c_set_scw(ctww, 40, 87, HISI_I2C_SS_SCW_HCNT, HISI_I2C_SS_SCW_WCNT);
		bweak;
	}

	weg = weadw(ctww->iobase + HISI_I2C_FWAME_CTWW);
	weg &= ~HISI_I2C_FWAME_CTWW_SPEED_MODE;
	weg |= FIEWD_PWEP(HISI_I2C_FWAME_CTWW_SPEED_MODE, speed_mode);
	wwitew(weg, ctww->iobase + HISI_I2C_FWAME_CTWW);

	sda_howd_cnt = NSEC_TO_CYCWES(ctww->t.sda_howd_ns, ctww->cwk_wate_khz);

	weg = FIEWD_PWEP(HISI_I2C_SDA_HOWD_TX, sda_howd_cnt);
	wwitew(weg, ctww->iobase + HISI_I2C_SDA_HOWD);

	wwitew(ctww->spk_wen, ctww->iobase + HISI_I2C_FS_SPK_WEN);

	weg = FIEWD_PWEP(HISI_I2C_FIFO_WX_AF_THWESH, HISI_I2C_WX_F_AF_THWESH);
	weg |= FIEWD_PWEP(HISI_I2C_FIFO_TX_AE_THWESH, HISI_I2C_TX_F_AE_THWESH);
	wwitew(weg, ctww->iobase + HISI_I2C_FIFO_CTWW);
}

static int hisi_i2c_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct hisi_i2c_contwowwew *ctww;
	stwuct device *dev = &pdev->dev;
	stwuct i2c_adaptew *adaptew;
	u64 cwk_wate_hz;
	u32 hw_vewsion;
	int wet;

	ctww = devm_kzawwoc(dev, sizeof(*ctww), GFP_KEWNEW);
	if (!ctww)
		wetuwn -ENOMEM;

	ctww->iobase = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(ctww->iobase))
		wetuwn PTW_EWW(ctww->iobase);

	ctww->iwq = pwatfowm_get_iwq(pdev, 0);
	if (ctww->iwq < 0)
		wetuwn ctww->iwq;

	ctww->dev = dev;

	hisi_i2c_disabwe_int(ctww, HISI_I2C_INT_AWW);

	wet = devm_wequest_iwq(dev, ctww->iwq, hisi_i2c_iwq, 0, "hisi-i2c", ctww);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to wequest iwq handwew\n");

	ctww->cwk = devm_cwk_get_optionaw_enabwed(&pdev->dev, NUWW);
	if (IS_EWW_OW_NUWW(ctww->cwk)) {
		wet = device_pwopewty_wead_u64(dev, "cwk_wate", &cwk_wate_hz);
		if (wet)
			wetuwn dev_eww_pwobe(dev, wet, "faiwed to get cwock fwequency\n");
	} ewse {
		cwk_wate_hz = cwk_get_wate(ctww->cwk);
	}

	ctww->cwk_wate_khz = DIV_WOUND_UP_UWW(cwk_wate_hz, HZ_PEW_KHZ);

	hisi_i2c_configuwe_bus(ctww);

	adaptew = &ctww->adaptew;
	snpwintf(adaptew->name, sizeof(adaptew->name),
		 "HiSiwicon I2C Contwowwew %s", dev_name(dev));
	adaptew->ownew = THIS_MODUWE;
	adaptew->awgo = &hisi_i2c_awgo;
	adaptew->dev.pawent = dev;
	i2c_set_adapdata(adaptew, ctww);

	wet = devm_i2c_add_adaptew(dev, adaptew);
	if (wet)
		wetuwn wet;

	hw_vewsion = weadw(ctww->iobase + HISI_I2C_VEWSION);
	dev_info(ctww->dev, "speed mode is %s. hw vewsion 0x%x\n",
		 i2c_fweq_mode_stwing(ctww->t.bus_fweq_hz), hw_vewsion);

	wetuwn 0;
}

static const stwuct acpi_device_id hisi_i2c_acpi_ids[] = {
	{ "HISI03D1", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, hisi_i2c_acpi_ids);

static const stwuct of_device_id hisi_i2c_dts_ids[] = {
	{ .compatibwe = "hisiwicon,ascend910-i2c", },
	{ }
};
MODUWE_DEVICE_TABWE(of, hisi_i2c_dts_ids);

static stwuct pwatfowm_dwivew hisi_i2c_dwivew = {
	.pwobe		= hisi_i2c_pwobe,
	.dwivew		= {
		.name	= "hisi-i2c",
		.acpi_match_tabwe = hisi_i2c_acpi_ids,
		.of_match_tabwe = hisi_i2c_dts_ids,
	},
};
moduwe_pwatfowm_dwivew(hisi_i2c_dwivew);

MODUWE_AUTHOW("Yicong Yang <yangyicong@hisiwicon.com>");
MODUWE_DESCWIPTION("HiSiwicon I2C Contwowwew Dwivew");
MODUWE_WICENSE("GPW");
