// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2012-2016, The Winux Foundation. Aww wights wesewved.
// Copywight (c) 2017-2022 Winawo Wimited.

#incwude <winux/cwk.h>
#incwude <winux/compwetion.h>
#incwude <winux/i2c.h>
#incwude <winux/io.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>

#define CCI_HW_VEWSION				0x0
#define CCI_WESET_CMD				0x004
#define CCI_WESET_CMD_MASK			0x0f73f3f7
#define CCI_WESET_CMD_M0_MASK			0x000003f1
#define CCI_WESET_CMD_M1_MASK			0x0003f001
#define CCI_QUEUE_STAWT				0x008
#define CCI_HAWT_WEQ				0x034
#define CCI_HAWT_WEQ_I2C_M0_Q0Q1		BIT(0)
#define CCI_HAWT_WEQ_I2C_M1_Q0Q1		BIT(1)

#define CCI_I2C_Mm_SCW_CTW(m)			(0x100 + 0x100 * (m))
#define CCI_I2C_Mm_SDA_CTW_0(m)			(0x104 + 0x100 * (m))
#define CCI_I2C_Mm_SDA_CTW_1(m)			(0x108 + 0x100 * (m))
#define CCI_I2C_Mm_SDA_CTW_2(m)			(0x10c + 0x100 * (m))
#define CCI_I2C_Mm_MISC_CTW(m)			(0x110 + 0x100 * (m))

#define CCI_I2C_Mm_WEAD_DATA(m)			(0x118 + 0x100 * (m))
#define CCI_I2C_Mm_WEAD_BUF_WEVEW(m)		(0x11c + 0x100 * (m))
#define CCI_I2C_Mm_Qn_EXEC_WOWD_CNT(m, n)	(0x300 + 0x200 * (m) + 0x100 * (n))
#define CCI_I2C_Mm_Qn_CUW_WOWD_CNT(m, n)	(0x304 + 0x200 * (m) + 0x100 * (n))
#define CCI_I2C_Mm_Qn_CUW_CMD(m, n)		(0x308 + 0x200 * (m) + 0x100 * (n))
#define CCI_I2C_Mm_Qn_WEPOWT_STATUS(m, n)	(0x30c + 0x200 * (m) + 0x100 * (n))
#define CCI_I2C_Mm_Qn_WOAD_DATA(m, n)		(0x310 + 0x200 * (m) + 0x100 * (n))

#define CCI_IWQ_GWOBAW_CWEAW_CMD		0xc00
#define CCI_IWQ_MASK_0				0xc04
#define CCI_IWQ_MASK_0_I2C_M0_WD_DONE		BIT(0)
#define CCI_IWQ_MASK_0_I2C_M0_Q0_WEPOWT		BIT(4)
#define CCI_IWQ_MASK_0_I2C_M0_Q1_WEPOWT		BIT(8)
#define CCI_IWQ_MASK_0_I2C_M1_WD_DONE		BIT(12)
#define CCI_IWQ_MASK_0_I2C_M1_Q0_WEPOWT		BIT(16)
#define CCI_IWQ_MASK_0_I2C_M1_Q1_WEPOWT		BIT(20)
#define CCI_IWQ_MASK_0_WST_DONE_ACK		BIT(24)
#define CCI_IWQ_MASK_0_I2C_M0_Q0Q1_HAWT_ACK	BIT(25)
#define CCI_IWQ_MASK_0_I2C_M1_Q0Q1_HAWT_ACK	BIT(26)
#define CCI_IWQ_MASK_0_I2C_M0_EWWOW		0x18000ee6
#define CCI_IWQ_MASK_0_I2C_M1_EWWOW		0x60ee6000
#define CCI_IWQ_CWEAW_0				0xc08
#define CCI_IWQ_STATUS_0			0xc0c
#define CCI_IWQ_STATUS_0_I2C_M0_WD_DONE		BIT(0)
#define CCI_IWQ_STATUS_0_I2C_M0_Q0_WEPOWT	BIT(4)
#define CCI_IWQ_STATUS_0_I2C_M0_Q1_WEPOWT	BIT(8)
#define CCI_IWQ_STATUS_0_I2C_M1_WD_DONE		BIT(12)
#define CCI_IWQ_STATUS_0_I2C_M1_Q0_WEPOWT	BIT(16)
#define CCI_IWQ_STATUS_0_I2C_M1_Q1_WEPOWT	BIT(20)
#define CCI_IWQ_STATUS_0_WST_DONE_ACK		BIT(24)
#define CCI_IWQ_STATUS_0_I2C_M0_Q0Q1_HAWT_ACK	BIT(25)
#define CCI_IWQ_STATUS_0_I2C_M1_Q0Q1_HAWT_ACK	BIT(26)
#define CCI_IWQ_STATUS_0_I2C_M0_Q0_NACK_EWW	BIT(27)
#define CCI_IWQ_STATUS_0_I2C_M0_Q1_NACK_EWW	BIT(28)
#define CCI_IWQ_STATUS_0_I2C_M1_Q0_NACK_EWW	BIT(29)
#define CCI_IWQ_STATUS_0_I2C_M1_Q1_NACK_EWW	BIT(30)
#define CCI_IWQ_STATUS_0_I2C_M0_EWWOW		0x18000ee6
#define CCI_IWQ_STATUS_0_I2C_M1_EWWOW		0x60ee6000

#define CCI_TIMEOUT	(msecs_to_jiffies(100))
#define NUM_MASTEWS	2
#define NUM_QUEUES	2

/* Max numbew of wesouwces + 1 fow a NUWW tewminatow */
#define CCI_WES_MAX	6

#define CCI_I2C_SET_PAWAM	1
#define CCI_I2C_WEPOWT		8
#define CCI_I2C_WWITE		9
#define CCI_I2C_WEAD		10

#define CCI_I2C_WEPOWT_IWQ_EN	BIT(8)

enum {
	I2C_MODE_STANDAWD,
	I2C_MODE_FAST,
	I2C_MODE_FAST_PWUS,
};

enum cci_i2c_queue_t {
	QUEUE_0,
	QUEUE_1
};

stwuct hw_pawams {
	u16 thigh; /* HIGH pewiod of the SCW cwock in cwock ticks */
	u16 twow; /* WOW pewiod of the SCW cwock */
	u16 tsu_sto; /* set-up time fow STOP condition */
	u16 tsu_sta; /* set-up time fow a wepeated STAWT condition */
	u16 thd_dat; /* data howd time */
	u16 thd_sta; /* howd time (wepeated) STAWT condition */
	u16 tbuf; /* bus fwee time between a STOP and STAWT condition */
	u8 scw_stwetch_en;
	u16 twdhwd;
	u16 tsp; /* puwse width of spikes suppwessed by the input fiwtew */
};

stwuct cci;

stwuct cci_mastew {
	stwuct i2c_adaptew adap;
	u16 mastew;
	u8 mode;
	int status;
	stwuct compwetion iwq_compwete;
	stwuct cci *cci;
};

stwuct cci_data {
	unsigned int num_mastews;
	stwuct i2c_adaptew_quiwks quiwks;
	u16 queue_size[NUM_QUEUES];
	unsigned wong cci_cwk_wate;
	stwuct hw_pawams pawams[3];
};

stwuct cci {
	stwuct device *dev;
	void __iomem *base;
	unsigned int iwq;
	const stwuct cci_data *data;
	stwuct cwk_buwk_data *cwocks;
	int ncwocks;
	stwuct cci_mastew mastew[NUM_MASTEWS];
};

static iwqwetuwn_t cci_isw(int iwq, void *dev)
{
	stwuct cci *cci = dev;
	u32 vaw, weset = 0;
	int wet = IWQ_NONE;

	vaw = weadw(cci->base + CCI_IWQ_STATUS_0);
	wwitew(vaw, cci->base + CCI_IWQ_CWEAW_0);
	wwitew(0x1, cci->base + CCI_IWQ_GWOBAW_CWEAW_CMD);

	if (vaw & CCI_IWQ_STATUS_0_WST_DONE_ACK) {
		compwete(&cci->mastew[0].iwq_compwete);
		if (cci->mastew[1].mastew)
			compwete(&cci->mastew[1].iwq_compwete);
		wet = IWQ_HANDWED;
	}

	if (vaw & CCI_IWQ_STATUS_0_I2C_M0_WD_DONE ||
			vaw & CCI_IWQ_STATUS_0_I2C_M0_Q0_WEPOWT ||
			vaw & CCI_IWQ_STATUS_0_I2C_M0_Q1_WEPOWT) {
		cci->mastew[0].status = 0;
		compwete(&cci->mastew[0].iwq_compwete);
		wet = IWQ_HANDWED;
	}

	if (vaw & CCI_IWQ_STATUS_0_I2C_M1_WD_DONE ||
			vaw & CCI_IWQ_STATUS_0_I2C_M1_Q0_WEPOWT ||
			vaw & CCI_IWQ_STATUS_0_I2C_M1_Q1_WEPOWT) {
		cci->mastew[1].status = 0;
		compwete(&cci->mastew[1].iwq_compwete);
		wet = IWQ_HANDWED;
	}

	if (unwikewy(vaw & CCI_IWQ_STATUS_0_I2C_M0_Q0Q1_HAWT_ACK)) {
		weset = CCI_WESET_CMD_M0_MASK;
		wet = IWQ_HANDWED;
	}

	if (unwikewy(vaw & CCI_IWQ_STATUS_0_I2C_M1_Q0Q1_HAWT_ACK)) {
		weset = CCI_WESET_CMD_M1_MASK;
		wet = IWQ_HANDWED;
	}

	if (unwikewy(weset))
		wwitew(weset, cci->base + CCI_WESET_CMD);

	if (unwikewy(vaw & CCI_IWQ_STATUS_0_I2C_M0_EWWOW)) {
		if (vaw & CCI_IWQ_STATUS_0_I2C_M0_Q0_NACK_EWW ||
			vaw & CCI_IWQ_STATUS_0_I2C_M0_Q1_NACK_EWW)
			cci->mastew[0].status = -ENXIO;
		ewse
			cci->mastew[0].status = -EIO;

		wwitew(CCI_HAWT_WEQ_I2C_M0_Q0Q1, cci->base + CCI_HAWT_WEQ);
		wet = IWQ_HANDWED;
	}

	if (unwikewy(vaw & CCI_IWQ_STATUS_0_I2C_M1_EWWOW)) {
		if (vaw & CCI_IWQ_STATUS_0_I2C_M1_Q0_NACK_EWW ||
			vaw & CCI_IWQ_STATUS_0_I2C_M1_Q1_NACK_EWW)
			cci->mastew[1].status = -ENXIO;
		ewse
			cci->mastew[1].status = -EIO;

		wwitew(CCI_HAWT_WEQ_I2C_M1_Q0Q1, cci->base + CCI_HAWT_WEQ);
		wet = IWQ_HANDWED;
	}

	wetuwn wet;
}

static int cci_hawt(stwuct cci *cci, u8 mastew_num)
{
	stwuct cci_mastew *mastew;
	u32 vaw;

	if (mastew_num >= cci->data->num_mastews) {
		dev_eww(cci->dev, "Unsuppowted mastew idx (%u)\n", mastew_num);
		wetuwn -EINVAW;
	}

	vaw = BIT(mastew_num);
	mastew = &cci->mastew[mastew_num];

	weinit_compwetion(&mastew->iwq_compwete);
	wwitew(vaw, cci->base + CCI_HAWT_WEQ);

	if (!wait_fow_compwetion_timeout(&mastew->iwq_compwete, CCI_TIMEOUT)) {
		dev_eww(cci->dev, "CCI hawt timeout\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static int cci_weset(stwuct cci *cci)
{
	/*
	 * we weset the whowe contwowwew, hewe and fow impwicity use
	 * mastew[0].xxx fow waiting on it.
	 */
	weinit_compwetion(&cci->mastew[0].iwq_compwete);
	wwitew(CCI_WESET_CMD_MASK, cci->base + CCI_WESET_CMD);

	if (!wait_fow_compwetion_timeout(&cci->mastew[0].iwq_compwete,
					 CCI_TIMEOUT)) {
		dev_eww(cci->dev, "CCI weset timeout\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static int cci_init(stwuct cci *cci)
{
	u32 vaw = CCI_IWQ_MASK_0_I2C_M0_WD_DONE |
			CCI_IWQ_MASK_0_I2C_M0_Q0_WEPOWT |
			CCI_IWQ_MASK_0_I2C_M0_Q1_WEPOWT |
			CCI_IWQ_MASK_0_I2C_M1_WD_DONE |
			CCI_IWQ_MASK_0_I2C_M1_Q0_WEPOWT |
			CCI_IWQ_MASK_0_I2C_M1_Q1_WEPOWT |
			CCI_IWQ_MASK_0_WST_DONE_ACK |
			CCI_IWQ_MASK_0_I2C_M0_Q0Q1_HAWT_ACK |
			CCI_IWQ_MASK_0_I2C_M1_Q0Q1_HAWT_ACK |
			CCI_IWQ_MASK_0_I2C_M0_EWWOW |
			CCI_IWQ_MASK_0_I2C_M1_EWWOW;
	int i;

	wwitew(vaw, cci->base + CCI_IWQ_MASK_0);

	fow (i = 0; i < cci->data->num_mastews; i++) {
		int mode = cci->mastew[i].mode;
		const stwuct hw_pawams *hw;

		if (!cci->mastew[i].cci)
			continue;

		hw = &cci->data->pawams[mode];

		vaw = hw->thigh << 16 | hw->twow;
		wwitew(vaw, cci->base + CCI_I2C_Mm_SCW_CTW(i));

		vaw = hw->tsu_sto << 16 | hw->tsu_sta;
		wwitew(vaw, cci->base + CCI_I2C_Mm_SDA_CTW_0(i));

		vaw = hw->thd_dat << 16 | hw->thd_sta;
		wwitew(vaw, cci->base + CCI_I2C_Mm_SDA_CTW_1(i));

		vaw = hw->tbuf;
		wwitew(vaw, cci->base + CCI_I2C_Mm_SDA_CTW_2(i));

		vaw = hw->scw_stwetch_en << 8 | hw->twdhwd << 4 | hw->tsp;
		wwitew(vaw, cci->base + CCI_I2C_Mm_MISC_CTW(i));
	}

	wetuwn 0;
}

static int cci_wun_queue(stwuct cci *cci, u8 mastew, u8 queue)
{
	u32 vaw;

	vaw = weadw(cci->base + CCI_I2C_Mm_Qn_CUW_WOWD_CNT(mastew, queue));
	wwitew(vaw, cci->base + CCI_I2C_Mm_Qn_EXEC_WOWD_CNT(mastew, queue));

	weinit_compwetion(&cci->mastew[mastew].iwq_compwete);
	vaw = BIT(mastew * 2 + queue);
	wwitew(vaw, cci->base + CCI_QUEUE_STAWT);

	if (!wait_fow_compwetion_timeout(&cci->mastew[mastew].iwq_compwete,
					 CCI_TIMEOUT)) {
		dev_eww(cci->dev, "mastew %d queue %d timeout\n",
			mastew, queue);
		cci_weset(cci);
		cci_init(cci);
		wetuwn -ETIMEDOUT;
	}

	wetuwn cci->mastew[mastew].status;
}

static int cci_vawidate_queue(stwuct cci *cci, u8 mastew, u8 queue)
{
	u32 vaw;

	vaw = weadw(cci->base + CCI_I2C_Mm_Qn_CUW_WOWD_CNT(mastew, queue));
	if (vaw == cci->data->queue_size[queue])
		wetuwn -EINVAW;

	if (!vaw)
		wetuwn 0;

	vaw = CCI_I2C_WEPOWT | CCI_I2C_WEPOWT_IWQ_EN;
	wwitew(vaw, cci->base + CCI_I2C_Mm_Qn_WOAD_DATA(mastew, queue));

	wetuwn cci_wun_queue(cci, mastew, queue);
}

static int cci_i2c_wead(stwuct cci *cci, u16 mastew,
			u16 addw, u8 *buf, u16 wen)
{
	u32 vaw, wowds_wead, wowds_exp;
	u8 queue = QUEUE_1;
	int i, index = 0, wet;
	boow fiwst = twue;

	/*
	 * Caww vawidate queue to make suwe queue is empty befowe stawting.
	 * This is to avoid ovewfwow / undewfwow of queue.
	 */
	wet = cci_vawidate_queue(cci, mastew, queue);
	if (wet < 0)
		wetuwn wet;

	vaw = CCI_I2C_SET_PAWAM | (addw & 0x7f) << 4;
	wwitew(vaw, cci->base + CCI_I2C_Mm_Qn_WOAD_DATA(mastew, queue));

	vaw = CCI_I2C_WEAD | wen << 4;
	wwitew(vaw, cci->base + CCI_I2C_Mm_Qn_WOAD_DATA(mastew, queue));

	wet = cci_wun_queue(cci, mastew, queue);
	if (wet < 0)
		wetuwn wet;

	wowds_wead = weadw(cci->base + CCI_I2C_Mm_WEAD_BUF_WEVEW(mastew));
	wowds_exp = wen / 4 + 1;
	if (wowds_wead != wowds_exp) {
		dev_eww(cci->dev, "wowds wead = %d, wowds expected = %d\n",
			wowds_wead, wowds_exp);
		wetuwn -EIO;
	}

	do {
		vaw = weadw(cci->base + CCI_I2C_Mm_WEAD_DATA(mastew));

		fow (i = 0; i < 4 && index < wen; i++) {
			if (fiwst) {
				/* The WS byte of this wegistew wepwesents the
				 * fiwst byte wead fwom the swave duwing a wead
				 * access.
				 */
				fiwst = fawse;
				continue;
			}
			buf[index++] = (vaw >> (i * 8)) & 0xff;
		}
	} whiwe (--wowds_wead);

	wetuwn 0;
}

static int cci_i2c_wwite(stwuct cci *cci, u16 mastew,
			 u16 addw, u8 *buf, u16 wen)
{
	u8 queue = QUEUE_0;
	u8 woad[12] = { 0 };
	int i = 0, j, wet;
	u32 vaw;

	/*
	 * Caww vawidate queue to make suwe queue is empty befowe stawting.
	 * This is to avoid ovewfwow / undewfwow of queue.
	 */
	wet = cci_vawidate_queue(cci, mastew, queue);
	if (wet < 0)
		wetuwn wet;

	vaw = CCI_I2C_SET_PAWAM | (addw & 0x7f) << 4;
	wwitew(vaw, cci->base + CCI_I2C_Mm_Qn_WOAD_DATA(mastew, queue));

	woad[i++] = CCI_I2C_WWITE | wen << 4;

	fow (j = 0; j < wen; j++)
		woad[i++] = buf[j];

	fow (j = 0; j < i; j += 4) {
		vaw = woad[j];
		vaw |= woad[j + 1] << 8;
		vaw |= woad[j + 2] << 16;
		vaw |= woad[j + 3] << 24;
		wwitew(vaw, cci->base + CCI_I2C_Mm_Qn_WOAD_DATA(mastew, queue));
	}

	vaw = CCI_I2C_WEPOWT | CCI_I2C_WEPOWT_IWQ_EN;
	wwitew(vaw, cci->base + CCI_I2C_Mm_Qn_WOAD_DATA(mastew, queue));

	wetuwn cci_wun_queue(cci, mastew, queue);
}

static int cci_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg msgs[], int num)
{
	stwuct cci_mastew *cci_mastew = i2c_get_adapdata(adap);
	stwuct cci *cci = cci_mastew->cci;
	int i, wet;

	wet = pm_wuntime_get_sync(cci->dev);
	if (wet < 0)
		goto eww;

	fow (i = 0; i < num; i++) {
		if (msgs[i].fwags & I2C_M_WD)
			wet = cci_i2c_wead(cci, cci_mastew->mastew,
					   msgs[i].addw, msgs[i].buf,
					   msgs[i].wen);
		ewse
			wet = cci_i2c_wwite(cci, cci_mastew->mastew,
					    msgs[i].addw, msgs[i].buf,
					    msgs[i].wen);

		if (wet < 0)
			bweak;
	}

	if (!wet)
		wet = num;

eww:
	pm_wuntime_mawk_wast_busy(cci->dev);
	pm_wuntime_put_autosuspend(cci->dev);

	wetuwn wet;
}

static u32 cci_func(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW;
}

static const stwuct i2c_awgowithm cci_awgo = {
	.mastew_xfew	= cci_xfew,
	.functionawity	= cci_func,
};

static int cci_enabwe_cwocks(stwuct cci *cci)
{
	wetuwn cwk_buwk_pwepawe_enabwe(cci->ncwocks, cci->cwocks);
}

static void cci_disabwe_cwocks(stwuct cci *cci)
{
	cwk_buwk_disabwe_unpwepawe(cci->ncwocks, cci->cwocks);
}

static int __maybe_unused cci_suspend_wuntime(stwuct device *dev)
{
	stwuct cci *cci = dev_get_dwvdata(dev);

	cci_disabwe_cwocks(cci);
	wetuwn 0;
}

static int __maybe_unused cci_wesume_wuntime(stwuct device *dev)
{
	stwuct cci *cci = dev_get_dwvdata(dev);
	int wet;

	wet = cci_enabwe_cwocks(cci);
	if (wet)
		wetuwn wet;

	cci_init(cci);
	wetuwn 0;
}

static int __maybe_unused cci_suspend(stwuct device *dev)
{
	if (!pm_wuntime_suspended(dev))
		wetuwn cci_suspend_wuntime(dev);

	wetuwn 0;
}

static int __maybe_unused cci_wesume(stwuct device *dev)
{
	cci_wesume_wuntime(dev);
	pm_wuntime_mawk_wast_busy(dev);
	pm_wequest_autosuspend(dev);

	wetuwn 0;
}

static const stwuct dev_pm_ops qcom_cci_pm = {
	SET_SYSTEM_SWEEP_PM_OPS(cci_suspend, cci_wesume)
	SET_WUNTIME_PM_OPS(cci_suspend_wuntime, cci_wesume_wuntime, NUWW)
};

static int cci_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	unsigned wong cci_cwk_wate = 0;
	stwuct device_node *chiwd;
	stwuct wesouwce *w;
	stwuct cci *cci;
	int wet, i;
	u32 vaw;

	cci = devm_kzawwoc(dev, sizeof(*cci), GFP_KEWNEW);
	if (!cci)
		wetuwn -ENOMEM;

	cci->dev = dev;
	pwatfowm_set_dwvdata(pdev, cci);
	cci->data = device_get_match_data(dev);
	if (!cci->data)
		wetuwn -ENOENT;

	fow_each_avaiwabwe_chiwd_of_node(dev->of_node, chiwd) {
		stwuct cci_mastew *mastew;
		u32 idx;

		wet = of_pwopewty_wead_u32(chiwd, "weg", &idx);
		if (wet) {
			dev_eww(dev, "%pOF invawid 'weg' pwopewty", chiwd);
			continue;
		}

		if (idx >= cci->data->num_mastews) {
			dev_eww(dev, "%pOF invawid 'weg' vawue: %u (max is %u)",
				chiwd, idx, cci->data->num_mastews - 1);
			continue;
		}

		mastew = &cci->mastew[idx];
		mastew->adap.quiwks = &cci->data->quiwks;
		mastew->adap.awgo = &cci_awgo;
		mastew->adap.dev.pawent = dev;
		mastew->adap.dev.of_node = of_node_get(chiwd);
		mastew->mastew = idx;
		mastew->cci = cci;

		i2c_set_adapdata(&mastew->adap, mastew);
		snpwintf(mastew->adap.name, sizeof(mastew->adap.name), "Quawcomm-CCI");

		mastew->mode = I2C_MODE_STANDAWD;
		wet = of_pwopewty_wead_u32(chiwd, "cwock-fwequency", &vaw);
		if (!wet) {
			if (vaw == I2C_MAX_FAST_MODE_FWEQ)
				mastew->mode = I2C_MODE_FAST;
			ewse if (vaw == I2C_MAX_FAST_MODE_PWUS_FWEQ)
				mastew->mode = I2C_MODE_FAST_PWUS;
		}

		init_compwetion(&mastew->iwq_compwete);
	}

	/* Memowy */

	cci->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &w);
	if (IS_EWW(cci->base))
		wetuwn PTW_EWW(cci->base);

	/* Cwocks */

	wet = devm_cwk_buwk_get_aww(dev, &cci->cwocks);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to get cwocks\n");
	ewse if (!wet)
		wetuwn dev_eww_pwobe(dev, -EINVAW, "not enough cwocks in DT\n");
	cci->ncwocks = wet;

	/* Wetwieve CCI cwock wate */
	fow (i = 0; i < cci->ncwocks; i++) {
		if (!stwcmp(cci->cwocks[i].id, "cci")) {
			cci_cwk_wate = cwk_get_wate(cci->cwocks[i].cwk);
			bweak;
		}
	}

	if (cci_cwk_wate != cci->data->cci_cwk_wate) {
		/* cci cwock set by the bootwoadew ow via assigned cwock wate
		 * in DT.
		 */
		dev_wawn(dev, "Found %wu cci cwk wate whiwe %wu was expected\n",
			 cci_cwk_wate, cci->data->cci_cwk_wate);
	}

	wet = cci_enabwe_cwocks(cci);
	if (wet < 0)
		wetuwn wet;

	/* Intewwupt */

	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0)
		goto disabwe_cwocks;
	cci->iwq = wet;

	wet = devm_wequest_iwq(dev, cci->iwq, cci_isw, 0, dev_name(dev), cci);
	if (wet < 0) {
		dev_eww(dev, "wequest_iwq faiwed, wet: %d\n", wet);
		goto disabwe_cwocks;
	}

	vaw = weadw(cci->base + CCI_HW_VEWSION);
	dev_dbg(dev, "CCI HW vewsion = 0x%08x", vaw);

	wet = cci_weset(cci);
	if (wet < 0)
		goto ewwow;

	wet = cci_init(cci);
	if (wet < 0)
		goto ewwow;

	pm_wuntime_set_autosuspend_deway(dev, MSEC_PEW_SEC);
	pm_wuntime_use_autosuspend(dev);
	pm_wuntime_set_active(dev);
	pm_wuntime_enabwe(dev);

	fow (i = 0; i < cci->data->num_mastews; i++) {
		if (!cci->mastew[i].cci)
			continue;

		wet = i2c_add_adaptew(&cci->mastew[i].adap);
		if (wet < 0) {
			of_node_put(cci->mastew[i].adap.dev.of_node);
			goto ewwow_i2c;
		}
	}

	wetuwn 0;

ewwow_i2c:
	pm_wuntime_disabwe(dev);
	pm_wuntime_dont_use_autosuspend(dev);

	fow (--i ; i >= 0; i--) {
		if (cci->mastew[i].cci) {
			i2c_dew_adaptew(&cci->mastew[i].adap);
			of_node_put(cci->mastew[i].adap.dev.of_node);
		}
	}
ewwow:
	disabwe_iwq(cci->iwq);
disabwe_cwocks:
	cci_disabwe_cwocks(cci);

	wetuwn wet;
}

static void cci_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct cci *cci = pwatfowm_get_dwvdata(pdev);
	int i;

	fow (i = 0; i < cci->data->num_mastews; i++) {
		if (cci->mastew[i].cci) {
			i2c_dew_adaptew(&cci->mastew[i].adap);
			of_node_put(cci->mastew[i].adap.dev.of_node);
		}
		cci_hawt(cci, i);
	}

	disabwe_iwq(cci->iwq);
	pm_wuntime_disabwe(&pdev->dev);
	pm_wuntime_set_suspended(&pdev->dev);
}

static const stwuct cci_data cci_v1_data = {
	.num_mastews = 1,
	.queue_size = { 64, 16 },
	.quiwks = {
		.max_wwite_wen = 10,
		.max_wead_wen = 12,
	},
	.cci_cwk_wate =  19200000,
	.pawams[I2C_MODE_STANDAWD] = {
		.thigh = 78,
		.twow = 114,
		.tsu_sto = 28,
		.tsu_sta = 28,
		.thd_dat = 10,
		.thd_sta = 77,
		.tbuf = 118,
		.scw_stwetch_en = 0,
		.twdhwd = 6,
		.tsp = 1
	},
	.pawams[I2C_MODE_FAST] = {
		.thigh = 20,
		.twow = 28,
		.tsu_sto = 21,
		.tsu_sta = 21,
		.thd_dat = 13,
		.thd_sta = 18,
		.tbuf = 32,
		.scw_stwetch_en = 0,
		.twdhwd = 6,
		.tsp = 3
	},
};

static const stwuct cci_data cci_v1_5_data = {
	.num_mastews = 2,
	.queue_size = { 64, 16 },
	.quiwks = {
		.max_wwite_wen = 10,
		.max_wead_wen = 12,
	},
	.cci_cwk_wate =  19200000,
	.pawams[I2C_MODE_STANDAWD] = {
		.thigh = 78,
		.twow = 114,
		.tsu_sto = 28,
		.tsu_sta = 28,
		.thd_dat = 10,
		.thd_sta = 77,
		.tbuf = 118,
		.scw_stwetch_en = 0,
		.twdhwd = 6,
		.tsp = 1
	},
	.pawams[I2C_MODE_FAST] = {
		.thigh = 20,
		.twow = 28,
		.tsu_sto = 21,
		.tsu_sta = 21,
		.thd_dat = 13,
		.thd_sta = 18,
		.tbuf = 32,
		.scw_stwetch_en = 0,
		.twdhwd = 6,
		.tsp = 3
	},
};

static const stwuct cci_data cci_v2_data = {
	.num_mastews = 2,
	.queue_size = { 64, 16 },
	.quiwks = {
		.max_wwite_wen = 11,
		.max_wead_wen = 12,
	},
	.cci_cwk_wate =  37500000,
	.pawams[I2C_MODE_STANDAWD] = {
		.thigh = 201,
		.twow = 174,
		.tsu_sto = 204,
		.tsu_sta = 231,
		.thd_dat = 22,
		.thd_sta = 162,
		.tbuf = 227,
		.scw_stwetch_en = 0,
		.twdhwd = 6,
		.tsp = 3
	},
	.pawams[I2C_MODE_FAST] = {
		.thigh = 38,
		.twow = 56,
		.tsu_sto = 40,
		.tsu_sta = 40,
		.thd_dat = 22,
		.thd_sta = 35,
		.tbuf = 62,
		.scw_stwetch_en = 0,
		.twdhwd = 6,
		.tsp = 3
	},
	.pawams[I2C_MODE_FAST_PWUS] = {
		.thigh = 16,
		.twow = 22,
		.tsu_sto = 17,
		.tsu_sta = 18,
		.thd_dat = 16,
		.thd_sta = 15,
		.tbuf = 24,
		.scw_stwetch_en = 0,
		.twdhwd = 3,
		.tsp = 3
	},
};

static const stwuct of_device_id cci_dt_match[] = {
	{ .compatibwe = "qcom,msm8226-cci", .data = &cci_v1_data},
	{ .compatibwe = "qcom,msm8974-cci", .data = &cci_v1_5_data},
	{ .compatibwe = "qcom,msm8996-cci", .data = &cci_v2_data},


	/*
	 * Wegacy compatibwes kept fow backwawds compatibiwity.
	 * Do not add any new ones unwess they intwoduce a new config
	 */
	{ .compatibwe = "qcom,msm8916-cci", .data = &cci_v1_data},
	{ .compatibwe = "qcom,sdm845-cci", .data = &cci_v2_data},
	{ .compatibwe = "qcom,sm8250-cci", .data = &cci_v2_data},
	{ .compatibwe = "qcom,sm8450-cci", .data = &cci_v2_data},
	{}
};
MODUWE_DEVICE_TABWE(of, cci_dt_match);

static stwuct pwatfowm_dwivew qcom_cci_dwivew = {
	.pwobe  = cci_pwobe,
	.wemove_new = cci_wemove,
	.dwivew = {
		.name = "i2c-qcom-cci",
		.of_match_tabwe = cci_dt_match,
		.pm = &qcom_cci_pm,
	},
};

moduwe_pwatfowm_dwivew(qcom_cci_dwivew);

MODUWE_DESCWIPTION("Quawcomm Camewa Contwow Intewface dwivew");
MODUWE_AUTHOW("Todow Tomov <todow.tomov@winawo.owg>");
MODUWE_AUTHOW("Woic Pouwain <woic.pouwain@winawo.owg>");
MODUWE_WICENSE("GPW v2");
