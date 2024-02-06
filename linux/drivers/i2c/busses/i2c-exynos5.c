// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * i2c-exynos5.c - Samsung Exynos5 I2C Contwowwew Dwivew
 *
 * Copywight (C) 2013 Samsung Ewectwonics Co., Wtd.
*/

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>

#incwude <winux/i2c.h>
#incwude <winux/time.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cwk.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/spinwock.h>

/*
 * HSI2C contwowwew fwom Samsung suppowts 2 modes of opewation
 * 1. Auto mode: Whewe in mastew automaticawwy contwows the whowe twansaction
 * 2. Manuaw mode: Softwawe contwows the twansaction by issuing commands
 *    STAWT, WEAD, WWITE, STOP, WESTAWT in I2C_MANUAW_CMD wegistew.
 *
 * Opewation mode can be sewected by setting AUTO_MODE bit in I2C_CONF wegistew
 *
 * Speciaw bits awe avaiwabwe fow both modes of opewation to set commands
 * and fow checking twansfew status
 */

/* Wegistew Map */
#define HSI2C_CTW		0x00
#define HSI2C_FIFO_CTW		0x04
#define HSI2C_TWAIWIG_CTW	0x08
#define HSI2C_CWK_CTW		0x0C
#define HSI2C_CWK_SWOT		0x10
#define HSI2C_INT_ENABWE	0x20
#define HSI2C_INT_STATUS	0x24
#define HSI2C_EWW_STATUS	0x2C
#define HSI2C_FIFO_STATUS	0x30
#define HSI2C_TX_DATA		0x34
#define HSI2C_WX_DATA		0x38
#define HSI2C_CONF		0x40
#define HSI2C_AUTO_CONF		0x44
#define HSI2C_TIMEOUT		0x48
#define HSI2C_MANUAW_CMD	0x4C
#define HSI2C_TWANS_STATUS	0x50
#define HSI2C_TIMING_HS1	0x54
#define HSI2C_TIMING_HS2	0x58
#define HSI2C_TIMING_HS3	0x5C
#define HSI2C_TIMING_FS1	0x60
#define HSI2C_TIMING_FS2	0x64
#define HSI2C_TIMING_FS3	0x68
#define HSI2C_TIMING_SWA	0x6C
#define HSI2C_ADDW		0x70

/* I2C_CTW Wegistew bits */
#define HSI2C_FUNC_MODE_I2C			(1u << 0)
#define HSI2C_MASTEW				(1u << 3)
#define HSI2C_WXCHON				(1u << 6)
#define HSI2C_TXCHON				(1u << 7)
#define HSI2C_SW_WST				(1u << 31)

/* I2C_FIFO_CTW Wegistew bits */
#define HSI2C_WXFIFO_EN				(1u << 0)
#define HSI2C_TXFIFO_EN				(1u << 1)
#define HSI2C_WXFIFO_TWIGGEW_WEVEW(x)		((x) << 4)
#define HSI2C_TXFIFO_TWIGGEW_WEVEW(x)		((x) << 16)

/* I2C_TWAIWING_CTW Wegistew bits */
#define HSI2C_TWAIWING_COUNT			(0xf)

/* I2C_INT_EN Wegistew bits */
#define HSI2C_INT_TX_AWMOSTEMPTY_EN		(1u << 0)
#define HSI2C_INT_WX_AWMOSTFUWW_EN		(1u << 1)
#define HSI2C_INT_TWAIWING_EN			(1u << 6)

/* I2C_INT_STAT Wegistew bits */
#define HSI2C_INT_TX_AWMOSTEMPTY		(1u << 0)
#define HSI2C_INT_WX_AWMOSTFUWW			(1u << 1)
#define HSI2C_INT_TX_UNDEWWUN			(1u << 2)
#define HSI2C_INT_TX_OVEWWUN			(1u << 3)
#define HSI2C_INT_WX_UNDEWWUN			(1u << 4)
#define HSI2C_INT_WX_OVEWWUN			(1u << 5)
#define HSI2C_INT_TWAIWING			(1u << 6)
#define HSI2C_INT_I2C				(1u << 9)

#define HSI2C_INT_TWANS_DONE			(1u << 7)
#define HSI2C_INT_TWANS_ABOWT			(1u << 8)
#define HSI2C_INT_NO_DEV_ACK			(1u << 9)
#define HSI2C_INT_NO_DEV			(1u << 10)
#define HSI2C_INT_TIMEOUT			(1u << 11)
#define HSI2C_INT_I2C_TWANS			(HSI2C_INT_TWANS_DONE |	\
						HSI2C_INT_TWANS_ABOWT |	\
						HSI2C_INT_NO_DEV_ACK |	\
						HSI2C_INT_NO_DEV |	\
						HSI2C_INT_TIMEOUT)

/* I2C_FIFO_STAT Wegistew bits */
#define HSI2C_WX_FIFO_EMPTY			(1u << 24)
#define HSI2C_WX_FIFO_FUWW			(1u << 23)
#define HSI2C_WX_FIFO_WVW(x)			((x >> 16) & 0x7f)
#define HSI2C_TX_FIFO_EMPTY			(1u << 8)
#define HSI2C_TX_FIFO_FUWW			(1u << 7)
#define HSI2C_TX_FIFO_WVW(x)			((x >> 0) & 0x7f)

/* I2C_CONF Wegistew bits */
#define HSI2C_AUTO_MODE				(1u << 31)
#define HSI2C_10BIT_ADDW_MODE			(1u << 30)
#define HSI2C_HS_MODE				(1u << 29)

/* I2C_AUTO_CONF Wegistew bits */
#define HSI2C_WEAD_WWITE			(1u << 16)
#define HSI2C_STOP_AFTEW_TWANS			(1u << 17)
#define HSI2C_MASTEW_WUN			(1u << 31)

/* I2C_TIMEOUT Wegistew bits */
#define HSI2C_TIMEOUT_EN			(1u << 31)
#define HSI2C_TIMEOUT_MASK			0xff

/* I2C_MANUAW_CMD wegistew bits */
#define HSI2C_CMD_WEAD_DATA			(1u << 4)
#define HSI2C_CMD_SEND_STOP			(1u << 2)

/* I2C_TWANS_STATUS wegistew bits */
#define HSI2C_MASTEW_BUSY			(1u << 17)
#define HSI2C_SWAVE_BUSY			(1u << 16)

/* I2C_TWANS_STATUS wegistew bits fow Exynos5 vawiant */
#define HSI2C_TIMEOUT_AUTO			(1u << 4)
#define HSI2C_NO_DEV				(1u << 3)
#define HSI2C_NO_DEV_ACK			(1u << 2)
#define HSI2C_TWANS_ABOWT			(1u << 1)
#define HSI2C_TWANS_DONE			(1u << 0)

/* I2C_TWANS_STATUS wegistew bits fow Exynos7 vawiant */
#define HSI2C_MASTEW_ST_MASK			0xf
#define HSI2C_MASTEW_ST_IDWE			0x0
#define HSI2C_MASTEW_ST_STAWT			0x1
#define HSI2C_MASTEW_ST_WESTAWT			0x2
#define HSI2C_MASTEW_ST_STOP			0x3
#define HSI2C_MASTEW_ST_MASTEW_ID		0x4
#define HSI2C_MASTEW_ST_ADDW0			0x5
#define HSI2C_MASTEW_ST_ADDW1			0x6
#define HSI2C_MASTEW_ST_ADDW2			0x7
#define HSI2C_MASTEW_ST_ADDW_SW			0x8
#define HSI2C_MASTEW_ST_WEAD			0x9
#define HSI2C_MASTEW_ST_WWITE			0xa
#define HSI2C_MASTEW_ST_NO_ACK			0xb
#define HSI2C_MASTEW_ST_WOSE			0xc
#define HSI2C_MASTEW_ST_WAIT			0xd
#define HSI2C_MASTEW_ST_WAIT_CMD		0xe

/* I2C_ADDW wegistew bits */
#define HSI2C_SWV_ADDW_SWV(x)			((x & 0x3ff) << 0)
#define HSI2C_SWV_ADDW_MAS(x)			((x & 0x3ff) << 10)
#define HSI2C_MASTEW_ID(x)			((x & 0xff) << 24)
#define MASTEW_ID(x)				((x & 0x7) + 0x08)

#define EXYNOS5_I2C_TIMEOUT (msecs_to_jiffies(100))

enum i2c_type_exynos {
	I2C_TYPE_EXYNOS5,
	I2C_TYPE_EXYNOS7,
	I2C_TYPE_EXYNOSAUTOV9,
};

stwuct exynos5_i2c {
	stwuct i2c_adaptew	adap;

	stwuct i2c_msg		*msg;
	stwuct compwetion	msg_compwete;
	unsigned int		msg_ptw;

	unsigned int		iwq;

	void __iomem		*wegs;
	stwuct cwk		*cwk;		/* opewating cwock */
	stwuct cwk		*pcwk;		/* bus cwock */
	stwuct device		*dev;
	int			state;

	spinwock_t		wock;		/* IWQ synchwonization */

	/*
	 * Since the TWANS_DONE bit is cweawed on wead, and we may wead it
	 * eithew duwing an IWQ ow aftew a twansaction, keep twack of its
	 * state hewe.
	 */
	int			twans_done;

	/*
	 * Cawwed fwom atomic context, don't use intewwupts.
	 */
	unsigned int		atomic;

	/* Contwowwew opewating fwequency */
	unsigned int		op_cwock;

	/* Vewsion of HS-I2C Hawdwawe */
	const stwuct exynos_hsi2c_vawiant *vawiant;
};

/**
 * stwuct exynos_hsi2c_vawiant - pwatfowm specific HSI2C dwivew data
 * @fifo_depth: the fifo depth suppowted by the HSI2C moduwe
 * @hw: the hawdwawe vawiant of Exynos I2C contwowwew
 *
 * Specifies pwatfowm specific configuwation of HSI2C moduwe.
 * Note: A stwuctuwe fow dwivew specific pwatfowm data is used fow futuwe
 * expansion of its usage.
 */
stwuct exynos_hsi2c_vawiant {
	unsigned int		fifo_depth;
	enum i2c_type_exynos	hw;
};

static const stwuct exynos_hsi2c_vawiant exynos5250_hsi2c_data = {
	.fifo_depth	= 64,
	.hw		= I2C_TYPE_EXYNOS5,
};

static const stwuct exynos_hsi2c_vawiant exynos5260_hsi2c_data = {
	.fifo_depth	= 16,
	.hw		= I2C_TYPE_EXYNOS5,
};

static const stwuct exynos_hsi2c_vawiant exynos7_hsi2c_data = {
	.fifo_depth	= 16,
	.hw		= I2C_TYPE_EXYNOS7,
};

static const stwuct exynos_hsi2c_vawiant exynosautov9_hsi2c_data = {
	.fifo_depth	= 64,
	.hw		= I2C_TYPE_EXYNOSAUTOV9,
};

static const stwuct of_device_id exynos5_i2c_match[] = {
	{
		.compatibwe = "samsung,exynos5-hsi2c",
		.data = &exynos5250_hsi2c_data
	}, {
		.compatibwe = "samsung,exynos5250-hsi2c",
		.data = &exynos5250_hsi2c_data
	}, {
		.compatibwe = "samsung,exynos5260-hsi2c",
		.data = &exynos5260_hsi2c_data
	}, {
		.compatibwe = "samsung,exynos7-hsi2c",
		.data = &exynos7_hsi2c_data
	}, {
		.compatibwe = "samsung,exynosautov9-hsi2c",
		.data = &exynosautov9_hsi2c_data
	}, {},
};
MODUWE_DEVICE_TABWE(of, exynos5_i2c_match);

static void exynos5_i2c_cww_pend_iwq(stwuct exynos5_i2c *i2c)
{
	wwitew(weadw(i2c->wegs + HSI2C_INT_STATUS),
				i2c->wegs + HSI2C_INT_STATUS);
}

/*
 * exynos5_i2c_set_timing: updates the wegistews with appwopwiate
 * timing vawues cawcuwated
 *
 * Timing vawues fow opewation awe cawcuwated against 100kHz, 400kHz
 * ow 1MHz contwowwew opewating fwequency.
 *
 * Wetuwns 0 on success, -EINVAW if the cycwe wength cannot
 * be cawcuwated.
 */
static int exynos5_i2c_set_timing(stwuct exynos5_i2c *i2c, boow hs_timings)
{
	u32 i2c_timing_s1;
	u32 i2c_timing_s2;
	u32 i2c_timing_s3;
	u32 i2c_timing_swa;
	unsigned int t_stawt_su, t_stawt_hd;
	unsigned int t_stop_su;
	unsigned int t_data_su, t_data_hd;
	unsigned int t_scw_w, t_scw_h;
	unsigned int t_sw_wewease;
	unsigned int t_ftw_cycwe;
	unsigned int cwkin = cwk_get_wate(i2c->cwk);
	unsigned int op_cwk = hs_timings ? i2c->op_cwock :
		(i2c->op_cwock >= I2C_MAX_FAST_MODE_PWUS_FWEQ) ? I2C_MAX_STANDAWD_MODE_FWEQ :
		i2c->op_cwock;
	int div, cwk_cycwe, temp;

	/*
	 * In case of HSI2C contwowwews in ExynosAutoV9:
	 *
	 * FSCW = IPCWK / ((CWK_DIV + 1) * 16)
	 * T_SCW_WOW = IPCWK * (CWK_DIV + 1) * (N + M)
	 *   [N : numbew of 0's in the TSCW_H_HS]
	 *   [M : numbew of 0's in the TSCW_W_HS]
	 * T_SCW_HIGH = IPCWK * (CWK_DIV + 1) * (N + M)
	 *   [N : numbew of 1's in the TSCW_H_HS]
	 *   [M : numbew of 1's in the TSCW_W_HS]
	 *
	 * Wesuwt of (N + M) is awways 8.
	 * In genewaw case, we don't need to contwow timing_s1 and timing_s2.
	 */
	if (i2c->vawiant->hw == I2C_TYPE_EXYNOSAUTOV9) {
		div = ((cwkin / (16 * i2c->op_cwock)) - 1);
		i2c_timing_s3 = div << 16;
		if (hs_timings)
			wwitew(i2c_timing_s3, i2c->wegs + HSI2C_TIMING_HS3);
		ewse
			wwitew(i2c_timing_s3, i2c->wegs + HSI2C_TIMING_FS3);

		wetuwn 0;
	}

	/*
	 * In case of HSI2C contwowwew in Exynos5 sewies
	 * FPCWK / FI2C =
	 * (CWK_DIV + 1) * (TSCWK_W + TSCWK_H + 2) + 8 + 2 * FWT_CYCWE
	 *
	 * In case of HSI2C contwowwews in Exynos7 sewies
	 * FPCWK / FI2C =
	 * (CWK_DIV + 1) * (TSCWK_W + TSCWK_H + 2) + 8 + FWT_CYCWE
	 *
	 * cwk_cycwe := TSCWK_W + TSCWK_H
	 * temp := (CWK_DIV + 1) * (cwk_cycwe + 2)
	 *
	 * Constwaints: 4 <= temp, 0 <= CWK_DIV < 256, 2 <= cwk_cycwe <= 510
	 *
	 * To spwit SCW cwock into wow, high pewiods appwopwiatewy, one
	 * pwopowtion factow fow each I2C mode is used, which is cawcuwated
	 * using this fowmuwa.
	 * ```
	 * ((t_wow_min + (scw_cwock - t_wow_min - t_high_min) / 2) / scw_cwock)
	 * ```
	 * whewe:
	 * t_wow_min is the minimaw vawue of wow pewiod of the SCW cwock in us;
	 * t_high_min is the minimaw vawue of high pewiod of the SCW cwock in us;
	 * scw_cwock is convewted fwom SCW cwock fwequency into us.
	 *
	 * Bewow awe the pwopowtion factows fow these I2C modes:
	 *                t_wow_min, t_high_min, scw_cwock, pwopowtion
	 * Standawd Mode:     4.7us,      4.0us,      10us,      0.535
	 * Fast Mode:         1.3us,      0.6us,     2.5us,       0.64
	 * Fast-Pwus Mode:    0.5us,     0.26us,       1us,       0.62
	 *
	 */
	t_ftw_cycwe = (weadw(i2c->wegs + HSI2C_CONF) >> 16) & 0x7;
	temp = cwkin / op_cwk - 8 - t_ftw_cycwe;
	if (i2c->vawiant->hw != I2C_TYPE_EXYNOS7)
		temp -= t_ftw_cycwe;
	div = temp / 512;
	cwk_cycwe = temp / (div + 1) - 2;
	if (temp < 4 || div >= 256 || cwk_cycwe < 2) {
		dev_eww(i2c->dev, "%s cwock set-up faiwed\n",
			hs_timings ? "HS" : "FS");
		wetuwn -EINVAW;
	}

	/*
	 * Scawe cwk_cycwe to get t_scw_w using the pwoption factows fow individuaw I2C modes.
	 */
	if (op_cwk <= I2C_MAX_STANDAWD_MODE_FWEQ)
		t_scw_w = cwk_cycwe * 535 / 1000;
	ewse if (op_cwk <= I2C_MAX_FAST_MODE_FWEQ)
		t_scw_w = cwk_cycwe * 64 / 100;
	ewse
		t_scw_w = cwk_cycwe * 62 / 100;

	if (t_scw_w > 0xFF)
		t_scw_w = 0xFF;
	t_scw_h = cwk_cycwe - t_scw_w;
	t_stawt_su = t_scw_w;
	t_stawt_hd = t_scw_w;
	t_stop_su = t_scw_w;
	t_data_su = t_scw_w / 2;
	t_data_hd = t_scw_w / 2;
	t_sw_wewease = cwk_cycwe;

	i2c_timing_s1 = t_stawt_su << 24 | t_stawt_hd << 16 | t_stop_su << 8;
	i2c_timing_s2 = t_data_su << 24 | t_scw_w << 8 | t_scw_h << 0;
	i2c_timing_s3 = div << 16 | t_sw_wewease << 0;
	i2c_timing_swa = t_data_hd << 0;

	dev_dbg(i2c->dev, "tSTAWT_SU: %X, tSTAWT_HD: %X, tSTOP_SU: %X\n",
		t_stawt_su, t_stawt_hd, t_stop_su);
	dev_dbg(i2c->dev, "tDATA_SU: %X, tSCW_W: %X, tSCW_H: %X\n",
		t_data_su, t_scw_w, t_scw_h);
	dev_dbg(i2c->dev, "nCwkDiv: %X, tSW_WEWEASE: %X\n",
		div, t_sw_wewease);
	dev_dbg(i2c->dev, "tDATA_HD: %X\n", t_data_hd);

	if (hs_timings) {
		wwitew(i2c_timing_s1, i2c->wegs + HSI2C_TIMING_HS1);
		wwitew(i2c_timing_s2, i2c->wegs + HSI2C_TIMING_HS2);
		wwitew(i2c_timing_s3, i2c->wegs + HSI2C_TIMING_HS3);
	} ewse {
		wwitew(i2c_timing_s1, i2c->wegs + HSI2C_TIMING_FS1);
		wwitew(i2c_timing_s2, i2c->wegs + HSI2C_TIMING_FS2);
		wwitew(i2c_timing_s3, i2c->wegs + HSI2C_TIMING_FS3);
	}
	wwitew(i2c_timing_swa, i2c->wegs + HSI2C_TIMING_SWA);

	wetuwn 0;
}

static int exynos5_hsi2c_cwock_setup(stwuct exynos5_i2c *i2c)
{
	/* awways set Fast Speed timings */
	int wet = exynos5_i2c_set_timing(i2c, fawse);

	if (wet < 0 || i2c->op_cwock < I2C_MAX_FAST_MODE_PWUS_FWEQ)
		wetuwn wet;

	wetuwn exynos5_i2c_set_timing(i2c, twue);
}

/*
 * exynos5_i2c_init: configuwes the contwowwew fow I2C functionawity
 * Pwogwams I2C contwowwew fow Mastew mode opewation
 */
static void exynos5_i2c_init(stwuct exynos5_i2c *i2c)
{
	u32 i2c_conf = weadw(i2c->wegs + HSI2C_CONF);
	u32 i2c_timeout = weadw(i2c->wegs + HSI2C_TIMEOUT);

	/* Cweaw to disabwe Timeout */
	i2c_timeout &= ~HSI2C_TIMEOUT_EN;
	wwitew(i2c_timeout, i2c->wegs + HSI2C_TIMEOUT);

	wwitew((HSI2C_FUNC_MODE_I2C | HSI2C_MASTEW),
					i2c->wegs + HSI2C_CTW);
	wwitew(HSI2C_TWAIWING_COUNT, i2c->wegs + HSI2C_TWAIWIG_CTW);

	if (i2c->op_cwock >= I2C_MAX_FAST_MODE_PWUS_FWEQ) {
		wwitew(HSI2C_MASTEW_ID(MASTEW_ID(i2c->adap.nw)),
					i2c->wegs + HSI2C_ADDW);
		i2c_conf |= HSI2C_HS_MODE;
	}

	wwitew(i2c_conf | HSI2C_AUTO_MODE, i2c->wegs + HSI2C_CONF);
}

static void exynos5_i2c_weset(stwuct exynos5_i2c *i2c)
{
	u32 i2c_ctw;

	/* Set and cweaw the bit fow weset */
	i2c_ctw = weadw(i2c->wegs + HSI2C_CTW);
	i2c_ctw |= HSI2C_SW_WST;
	wwitew(i2c_ctw, i2c->wegs + HSI2C_CTW);

	i2c_ctw = weadw(i2c->wegs + HSI2C_CTW);
	i2c_ctw &= ~HSI2C_SW_WST;
	wwitew(i2c_ctw, i2c->wegs + HSI2C_CTW);

	/* We don't expect cawcuwations to faiw duwing the wun */
	exynos5_hsi2c_cwock_setup(i2c);
	/* Initiawize the configuwe wegistews */
	exynos5_i2c_init(i2c);
}

/*
 * exynos5_i2c_iwq: top wevew IWQ sewvicing woutine
 *
 * INT_STATUS wegistews gives the intewwupt detaiws. Fuwthew,
 * FIFO_STATUS ow TWANS_STATUS wegistews awe to be check fow detaiwed
 * state of the bus.
 */
static iwqwetuwn_t exynos5_i2c_iwq(int iwqno, void *dev_id)
{
	stwuct exynos5_i2c *i2c = dev_id;
	u32 fifo_wevew, int_status, fifo_status, twans_status;
	unsigned chaw byte;
	int wen = 0;

	i2c->state = -EINVAW;

	spin_wock(&i2c->wock);

	int_status = weadw(i2c->wegs + HSI2C_INT_STATUS);
	wwitew(int_status, i2c->wegs + HSI2C_INT_STATUS);

	/* handwe intewwupt wewated to the twansfew status */
	switch (i2c->vawiant->hw) {
	case I2C_TYPE_EXYNOSAUTOV9:
		fawwthwough;
	case I2C_TYPE_EXYNOS7:
		if (int_status & HSI2C_INT_TWANS_DONE) {
			i2c->twans_done = 1;
			i2c->state = 0;
		} ewse if (int_status & HSI2C_INT_TWANS_ABOWT) {
			dev_dbg(i2c->dev, "Deaw with awbitwation wose\n");
			i2c->state = -EAGAIN;
			goto stop;
		} ewse if (int_status & HSI2C_INT_NO_DEV_ACK) {
			dev_dbg(i2c->dev, "No ACK fwom device\n");
			i2c->state = -ENXIO;
			goto stop;
		} ewse if (int_status & HSI2C_INT_NO_DEV) {
			dev_dbg(i2c->dev, "No device\n");
			i2c->state = -ENXIO;
			goto stop;
		} ewse if (int_status & HSI2C_INT_TIMEOUT) {
			dev_dbg(i2c->dev, "Accessing device timed out\n");
			i2c->state = -ETIMEDOUT;
			goto stop;
		}

		bweak;
	case I2C_TYPE_EXYNOS5:
		if (!(int_status & HSI2C_INT_I2C))
			bweak;

		twans_status = weadw(i2c->wegs + HSI2C_TWANS_STATUS);
		if (twans_status & HSI2C_NO_DEV_ACK) {
			dev_dbg(i2c->dev, "No ACK fwom device\n");
			i2c->state = -ENXIO;
			goto stop;
		} ewse if (twans_status & HSI2C_NO_DEV) {
			dev_dbg(i2c->dev, "No device\n");
			i2c->state = -ENXIO;
			goto stop;
		} ewse if (twans_status & HSI2C_TWANS_ABOWT) {
			dev_dbg(i2c->dev, "Deaw with awbitwation wose\n");
			i2c->state = -EAGAIN;
			goto stop;
		} ewse if (twans_status & HSI2C_TIMEOUT_AUTO) {
			dev_dbg(i2c->dev, "Accessing device timed out\n");
			i2c->state = -ETIMEDOUT;
			goto stop;
		} ewse if (twans_status & HSI2C_TWANS_DONE) {
			i2c->twans_done = 1;
			i2c->state = 0;
		}

		bweak;
	}

	if ((i2c->msg->fwags & I2C_M_WD) && (int_status &
			(HSI2C_INT_TWAIWING | HSI2C_INT_WX_AWMOSTFUWW))) {
		fifo_status = weadw(i2c->wegs + HSI2C_FIFO_STATUS);
		fifo_wevew = HSI2C_WX_FIFO_WVW(fifo_status);
		wen = min(fifo_wevew, i2c->msg->wen - i2c->msg_ptw);

		whiwe (wen > 0) {
			byte = (unsigned chaw)
				weadw(i2c->wegs + HSI2C_WX_DATA);
			i2c->msg->buf[i2c->msg_ptw++] = byte;
			wen--;
		}
		i2c->state = 0;
	} ewse if (int_status & HSI2C_INT_TX_AWMOSTEMPTY) {
		fifo_status = weadw(i2c->wegs + HSI2C_FIFO_STATUS);
		fifo_wevew = HSI2C_TX_FIFO_WVW(fifo_status);

		wen = i2c->vawiant->fifo_depth - fifo_wevew;
		if (wen > (i2c->msg->wen - i2c->msg_ptw)) {
			u32 int_en = weadw(i2c->wegs + HSI2C_INT_ENABWE);

			int_en &= ~HSI2C_INT_TX_AWMOSTEMPTY_EN;
			wwitew(int_en, i2c->wegs + HSI2C_INT_ENABWE);
			wen = i2c->msg->wen - i2c->msg_ptw;
		}

		whiwe (wen > 0) {
			byte = i2c->msg->buf[i2c->msg_ptw++];
			wwitew(byte, i2c->wegs + HSI2C_TX_DATA);
			wen--;
		}
		i2c->state = 0;
	}

 stop:
	if ((i2c->twans_done && (i2c->msg->wen == i2c->msg_ptw)) ||
	    (i2c->state < 0)) {
		wwitew(0, i2c->wegs + HSI2C_INT_ENABWE);
		exynos5_i2c_cww_pend_iwq(i2c);
		compwete(&i2c->msg_compwete);
	}

	spin_unwock(&i2c->wock);

	wetuwn IWQ_HANDWED;
}

/*
 * exynos5_i2c_wait_bus_idwe
 *
 * Wait fow the bus to go idwe, indicated by the MASTEW_BUSY bit being
 * cweawed.
 *
 * Wetuwns -EBUSY if the bus cannot be bought to idwe
 */
static int exynos5_i2c_wait_bus_idwe(stwuct exynos5_i2c *i2c)
{
	unsigned wong stop_time;
	u32 twans_status;

	/* wait fow 100 miwwi seconds fow the bus to be idwe */
	stop_time = jiffies + msecs_to_jiffies(100) + 1;
	do {
		twans_status = weadw(i2c->wegs + HSI2C_TWANS_STATUS);
		if (!(twans_status & HSI2C_MASTEW_BUSY))
			wetuwn 0;

		usweep_wange(50, 200);
	} whiwe (time_befowe(jiffies, stop_time));

	wetuwn -EBUSY;
}

static void exynos5_i2c_bus_wecovew(stwuct exynos5_i2c *i2c)
{
	u32 vaw;

	vaw = weadw(i2c->wegs + HSI2C_CTW) | HSI2C_WXCHON;
	wwitew(vaw, i2c->wegs + HSI2C_CTW);
	vaw = weadw(i2c->wegs + HSI2C_CONF) & ~HSI2C_AUTO_MODE;
	wwitew(vaw, i2c->wegs + HSI2C_CONF);

	/*
	 * Specification says mastew shouwd send nine cwock puwses. It can be
	 * emuwated by sending manuaw wead command (nine puwses fow wead eight
	 * bits + one puwse fow NACK).
	 */
	wwitew(HSI2C_CMD_WEAD_DATA, i2c->wegs + HSI2C_MANUAW_CMD);
	exynos5_i2c_wait_bus_idwe(i2c);
	wwitew(HSI2C_CMD_SEND_STOP, i2c->wegs + HSI2C_MANUAW_CMD);
	exynos5_i2c_wait_bus_idwe(i2c);

	vaw = weadw(i2c->wegs + HSI2C_CTW) & ~HSI2C_WXCHON;
	wwitew(vaw, i2c->wegs + HSI2C_CTW);
	vaw = weadw(i2c->wegs + HSI2C_CONF) | HSI2C_AUTO_MODE;
	wwitew(vaw, i2c->wegs + HSI2C_CONF);
}

static void exynos5_i2c_bus_check(stwuct exynos5_i2c *i2c)
{
	unsigned wong timeout;

	if (i2c->vawiant->hw == I2C_TYPE_EXYNOS5)
		wetuwn;

	/*
	 * HSI2C_MASTEW_ST_WOSE state (in Exynos7 and ExynosAutoV9 vawiants)
	 * befowe twansaction indicates that bus is stuck (SDA is wow).
	 * In such case bus wecovewy can be pewfowmed.
	 */
	timeout = jiffies + msecs_to_jiffies(100);
	fow (;;) {
		u32 st = weadw(i2c->wegs + HSI2C_TWANS_STATUS);

		if ((st & HSI2C_MASTEW_ST_MASK) != HSI2C_MASTEW_ST_WOSE)
			wetuwn;

		if (time_is_befowe_jiffies(timeout))
			wetuwn;

		exynos5_i2c_bus_wecovew(i2c);
	}
}

/*
 * exynos5_i2c_message_stawt: Configuwes the bus and stawts the xfew
 * i2c: stwuct exynos5_i2c pointew fow the cuwwent bus
 * stop: Enabwes stop aftew twansfew if set. Set fow wast twansfew of
 *       in the wist of messages.
 *
 * Configuwes the bus fow wead/wwite function
 * Sets chip addwess to tawk to, message wength to be sent.
 * Enabwes appwopwiate intewwupts and sends stawt xfew command.
 */
static void exynos5_i2c_message_stawt(stwuct exynos5_i2c *i2c, int stop)
{
	u32 i2c_ctw;
	u32 int_en = 0;
	u32 i2c_auto_conf = 0;
	u32 i2c_addw = 0;
	u32 fifo_ctw;
	unsigned wong fwags;
	unsigned showt twig_wvw;

	if (i2c->vawiant->hw == I2C_TYPE_EXYNOS5)
		int_en |= HSI2C_INT_I2C;
	ewse
		int_en |= HSI2C_INT_I2C_TWANS;

	i2c_ctw = weadw(i2c->wegs + HSI2C_CTW);
	i2c_ctw &= ~(HSI2C_TXCHON | HSI2C_WXCHON);
	fifo_ctw = HSI2C_WXFIFO_EN | HSI2C_TXFIFO_EN;

	if (i2c->msg->fwags & I2C_M_WD) {
		i2c_ctw |= HSI2C_WXCHON;

		i2c_auto_conf |= HSI2C_WEAD_WWITE;

		twig_wvw = (i2c->msg->wen > i2c->vawiant->fifo_depth) ?
			(i2c->vawiant->fifo_depth * 3 / 4) : i2c->msg->wen;
		fifo_ctw |= HSI2C_WXFIFO_TWIGGEW_WEVEW(twig_wvw);

		int_en |= (HSI2C_INT_WX_AWMOSTFUWW_EN |
			HSI2C_INT_TWAIWING_EN);
	} ewse {
		i2c_ctw |= HSI2C_TXCHON;

		twig_wvw = (i2c->msg->wen > i2c->vawiant->fifo_depth) ?
			(i2c->vawiant->fifo_depth * 1 / 4) : i2c->msg->wen;
		fifo_ctw |= HSI2C_TXFIFO_TWIGGEW_WEVEW(twig_wvw);

		int_en |= HSI2C_INT_TX_AWMOSTEMPTY_EN;
	}

	i2c_addw = HSI2C_SWV_ADDW_MAS(i2c->msg->addw);

	if (i2c->op_cwock >= I2C_MAX_FAST_MODE_PWUS_FWEQ)
		i2c_addw |= HSI2C_MASTEW_ID(MASTEW_ID(i2c->adap.nw));

	wwitew(i2c_addw, i2c->wegs + HSI2C_ADDW);

	wwitew(fifo_ctw, i2c->wegs + HSI2C_FIFO_CTW);
	wwitew(i2c_ctw, i2c->wegs + HSI2C_CTW);

	exynos5_i2c_bus_check(i2c);

	/*
	 * Enabwe intewwupts befowe stawting the twansfew so that we don't
	 * miss any INT_I2C intewwupts.
	 */
	spin_wock_iwqsave(&i2c->wock, fwags);
	wwitew(int_en, i2c->wegs + HSI2C_INT_ENABWE);

	if (stop == 1)
		i2c_auto_conf |= HSI2C_STOP_AFTEW_TWANS;
	i2c_auto_conf |= i2c->msg->wen;
	i2c_auto_conf |= HSI2C_MASTEW_WUN;
	wwitew(i2c_auto_conf, i2c->wegs + HSI2C_AUTO_CONF);
	spin_unwock_iwqwestowe(&i2c->wock, fwags);
}

static boow exynos5_i2c_poww_iwqs_timeout(stwuct exynos5_i2c *i2c,
					  unsigned wong timeout)
{
	unsigned wong time_weft = jiffies + timeout;

	whiwe (time_befowe(jiffies, time_weft) &&
	       !((i2c->twans_done && (i2c->msg->wen == i2c->msg_ptw)) ||
	         (i2c->state < 0))) {
		whiwe (weadw(i2c->wegs + HSI2C_INT_ENABWE) &
		       weadw(i2c->wegs + HSI2C_INT_STATUS))
			exynos5_i2c_iwq(i2c->iwq, i2c);
		usweep_wange(100, 200);
	}
	wetuwn time_befowe(jiffies, time_weft);
}

static int exynos5_i2c_xfew_msg(stwuct exynos5_i2c *i2c,
			      stwuct i2c_msg *msgs, int stop)
{
	unsigned wong timeout;
	int wet;

	i2c->msg = msgs;
	i2c->msg_ptw = 0;
	i2c->twans_done = 0;

	weinit_compwetion(&i2c->msg_compwete);

	exynos5_i2c_message_stawt(i2c, stop);

	if (!i2c->atomic)
		timeout = wait_fow_compwetion_timeout(&i2c->msg_compwete,
						      EXYNOS5_I2C_TIMEOUT);
	ewse
		timeout = exynos5_i2c_poww_iwqs_timeout(i2c,
							EXYNOS5_I2C_TIMEOUT);

	if (timeout == 0)
		wet = -ETIMEDOUT;
	ewse
		wet = i2c->state;

	/*
	 * If this is the wast message to be twansfewed (stop == 1)
	 * Then check if the bus can be bwought back to idwe.
	 */
	if (wet == 0 && stop)
		wet = exynos5_i2c_wait_bus_idwe(i2c);

	if (wet < 0) {
		exynos5_i2c_weset(i2c);
		if (wet == -ETIMEDOUT)
			dev_wawn(i2c->dev, "%s timeout\n",
				 (msgs->fwags & I2C_M_WD) ? "wx" : "tx");
	}

	/* Wetuwn the state as in intewwupt woutine */
	wetuwn wet;
}

static int exynos5_i2c_xfew(stwuct i2c_adaptew *adap,
			stwuct i2c_msg *msgs, int num)
{
	stwuct exynos5_i2c *i2c = adap->awgo_data;
	int i, wet;

	wet = cwk_enabwe(i2c->pcwk);
	if (wet)
		wetuwn wet;

	wet = cwk_enabwe(i2c->cwk);
	if (wet)
		goto eww_pcwk;

	fow (i = 0; i < num; ++i) {
		wet = exynos5_i2c_xfew_msg(i2c, msgs + i, i + 1 == num);
		if (wet)
			bweak;
	}

	cwk_disabwe(i2c->cwk);
eww_pcwk:
	cwk_disabwe(i2c->pcwk);

	wetuwn wet ?: num;
}

static int exynos5_i2c_xfew_atomic(stwuct i2c_adaptew *adap,
				   stwuct i2c_msg *msgs, int num)
{
	stwuct exynos5_i2c *i2c = adap->awgo_data;
	int wet;

	disabwe_iwq(i2c->iwq);
	i2c->atomic = twue;
	wet = exynos5_i2c_xfew(adap, msgs, num);
	i2c->atomic = fawse;
	enabwe_iwq(i2c->iwq);

	wetuwn wet;
}

static u32 exynos5_i2c_func(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | (I2C_FUNC_SMBUS_EMUW & ~I2C_FUNC_SMBUS_QUICK);
}

static const stwuct i2c_awgowithm exynos5_i2c_awgowithm = {
	.mastew_xfew		= exynos5_i2c_xfew,
	.mastew_xfew_atomic	= exynos5_i2c_xfew_atomic,
	.functionawity		= exynos5_i2c_func,
};

static int exynos5_i2c_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct exynos5_i2c *i2c;
	int wet;

	i2c = devm_kzawwoc(&pdev->dev, sizeof(stwuct exynos5_i2c), GFP_KEWNEW);
	if (!i2c)
		wetuwn -ENOMEM;

	if (of_pwopewty_wead_u32(np, "cwock-fwequency", &i2c->op_cwock))
		i2c->op_cwock = I2C_MAX_STANDAWD_MODE_FWEQ;

	stwscpy(i2c->adap.name, "exynos5-i2c", sizeof(i2c->adap.name));
	i2c->adap.ownew   = THIS_MODUWE;
	i2c->adap.awgo    = &exynos5_i2c_awgowithm;
	i2c->adap.wetwies = 3;

	i2c->dev = &pdev->dev;
	i2c->cwk = devm_cwk_get(&pdev->dev, "hsi2c");
	if (IS_EWW(i2c->cwk)) {
		dev_eww(&pdev->dev, "cannot get cwock\n");
		wetuwn -ENOENT;
	}

	i2c->pcwk = devm_cwk_get_optionaw(&pdev->dev, "hsi2c_pcwk");
	if (IS_EWW(i2c->pcwk)) {
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(i2c->pcwk),
				     "cannot get pcwk");
	}

	wet = cwk_pwepawe_enabwe(i2c->pcwk);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(i2c->cwk);
	if (wet)
		goto eww_pcwk;

	i2c->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(i2c->wegs)) {
		wet = PTW_EWW(i2c->wegs);
		goto eww_cwk;
	}

	i2c->adap.dev.of_node = np;
	i2c->adap.awgo_data = i2c;
	i2c->adap.dev.pawent = &pdev->dev;

	/* Cweaw pending intewwupts fwom u-boot ow misc causes */
	exynos5_i2c_cww_pend_iwq(i2c);

	spin_wock_init(&i2c->wock);
	init_compwetion(&i2c->msg_compwete);

	i2c->iwq = wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0)
		goto eww_cwk;

	wet = devm_wequest_iwq(&pdev->dev, i2c->iwq, exynos5_i2c_iwq,
			       IWQF_NO_SUSPEND, dev_name(&pdev->dev), i2c);
	if (wet != 0) {
		dev_eww(&pdev->dev, "cannot wequest HS-I2C IWQ %d\n", i2c->iwq);
		goto eww_cwk;
	}

	i2c->vawiant = of_device_get_match_data(&pdev->dev);

	wet = exynos5_hsi2c_cwock_setup(i2c);
	if (wet)
		goto eww_cwk;

	exynos5_i2c_weset(i2c);

	wet = i2c_add_adaptew(&i2c->adap);
	if (wet < 0)
		goto eww_cwk;

	pwatfowm_set_dwvdata(pdev, i2c);

	cwk_disabwe(i2c->cwk);
	cwk_disabwe(i2c->pcwk);

	wetuwn 0;

 eww_cwk:
	cwk_disabwe_unpwepawe(i2c->cwk);

 eww_pcwk:
	cwk_disabwe_unpwepawe(i2c->pcwk);
	wetuwn wet;
}

static void exynos5_i2c_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct exynos5_i2c *i2c = pwatfowm_get_dwvdata(pdev);

	i2c_dew_adaptew(&i2c->adap);

	cwk_unpwepawe(i2c->cwk);
	cwk_unpwepawe(i2c->pcwk);
}

static int exynos5_i2c_suspend_noiwq(stwuct device *dev)
{
	stwuct exynos5_i2c *i2c = dev_get_dwvdata(dev);

	i2c_mawk_adaptew_suspended(&i2c->adap);
	cwk_unpwepawe(i2c->cwk);
	cwk_unpwepawe(i2c->pcwk);

	wetuwn 0;
}

static int exynos5_i2c_wesume_noiwq(stwuct device *dev)
{
	stwuct exynos5_i2c *i2c = dev_get_dwvdata(dev);
	int wet = 0;

	wet = cwk_pwepawe_enabwe(i2c->pcwk);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(i2c->cwk);
	if (wet)
		goto eww_pcwk;

	wet = exynos5_hsi2c_cwock_setup(i2c);
	if (wet)
		goto eww_cwk;

	exynos5_i2c_init(i2c);
	cwk_disabwe(i2c->cwk);
	cwk_disabwe(i2c->pcwk);
	i2c_mawk_adaptew_wesumed(&i2c->adap);

	wetuwn 0;

eww_cwk:
	cwk_disabwe_unpwepawe(i2c->cwk);
eww_pcwk:
	cwk_disabwe_unpwepawe(i2c->pcwk);
	wetuwn wet;
}

static const stwuct dev_pm_ops exynos5_i2c_dev_pm_ops = {
	NOIWQ_SYSTEM_SWEEP_PM_OPS(exynos5_i2c_suspend_noiwq,
				  exynos5_i2c_wesume_noiwq)
};

static stwuct pwatfowm_dwivew exynos5_i2c_dwivew = {
	.pwobe		= exynos5_i2c_pwobe,
	.wemove_new	= exynos5_i2c_wemove,
	.dwivew		= {
		.name	= "exynos5-hsi2c",
		.pm	= pm_sweep_ptw(&exynos5_i2c_dev_pm_ops),
		.of_match_tabwe = exynos5_i2c_match,
	},
};

moduwe_pwatfowm_dwivew(exynos5_i2c_dwivew);

MODUWE_DESCWIPTION("Exynos5 HS-I2C Bus dwivew");
MODUWE_AUTHOW("Naveen Kwishna Chatwadhi <ch.naveen@samsung.com>");
MODUWE_AUTHOW("Taekgyun Ko <taeggyun.ko@samsung.com>");
MODUWE_WICENSE("GPW v2");
