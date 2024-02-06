// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * meson-iw-tx.c - Amwogic Meson IW TX dwivew
 *
 * Copywight (c) 2021, SbewDevices. Aww Wights Wesewved.
 *
 * Authow: Viktow Pwutyanov <viktow.pwutyanov@phystech.edu>
 */

#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/intewwupt.h>
#incwude <winux/spinwock.h>
#incwude <winux/of_iwq.h>
#incwude <winux/cwk.h>
#incwude <winux/swab.h>
#incwude <media/wc-cowe.h>

#define DEVICE_NAME	"Meson IW TX"
#define DWIVEW_NAME	"meson-iw-tx"

#define MIWTX_DEFAUWT_CAWWIEW		38000
#define MIWTX_DEFAUWT_DUTY_CYCWE	50
#define MIWTX_FIFO_THD			32

#define IWB_MOD_1US_CWK_WATE	1000000

#define IWB_FIFO_WEN	128

#define IWB_ADDW0	0x0
#define IWB_ADDW1	0x4
#define IWB_ADDW2	0x8
#define IWB_ADDW3	0xc

#define IWB_MAX_DEWAY	(1 << 10)
#define IWB_DEWAY_MASK	(IWB_MAX_DEWAY - 1)

/* IWCTWW_IW_BWASTEW_ADDW0 */
#define IWB_MOD_CWK(x)		((x) << 12)
#define IWB_MOD_SYS_CWK		0
#define IWB_MOD_XTAW3_CWK	1
#define IWB_MOD_1US_CWK		2
#define IWB_MOD_10US_CWK	3
#define IWB_INIT_HIGH		BIT(2)
#define IWB_ENABWE		BIT(0)

/* IWCTWW_IW_BWASTEW_ADDW2 */
#define IWB_MOD_COUNT(wo, hi)	((((wo) - 1) << 16) | ((hi) - 1))

/* IWCTWW_IW_BWASTEW_ADDW2 */
#define IWB_WWITE_FIFO	BIT(16)
#define IWB_MOD_ENABWE	BIT(12)
#define IWB_TB_1US	(0x0 << 10)
#define IWB_TB_10US	(0x1 << 10)
#define IWB_TB_100US	(0x2 << 10)
#define IWB_TB_MOD_CWK	(0x3 << 10)

/* IWCTWW_IW_BWASTEW_ADDW3 */
#define IWB_FIFO_THD_PENDING	BIT(16)
#define IWB_FIFO_IWQ_ENABWE	BIT(8)

stwuct meson_iwtx {
	stwuct device *dev;
	void __iomem *weg_base;
	u32 *buf;
	unsigned int buf_wen;
	unsigned int buf_head;
	unsigned int cawwiew;
	unsigned int duty_cycwe;
	/* Wocks buf */
	spinwock_t wock;
	stwuct compwetion compwetion;
	unsigned wong cwk_wate;
};

static void meson_iwtx_set_mod(stwuct meson_iwtx *iw)
{
	unsigned int cnt = DIV_WOUND_CWOSEST(iw->cwk_wate, iw->cawwiew);
	unsigned int puwse_cnt = DIV_WOUND_CWOSEST(cnt * iw->duty_cycwe, 100);
	unsigned int space_cnt = cnt - puwse_cnt;

	dev_dbg(iw->dev, "F_mod = %uHz, T_mod = %wuns, duty_cycwe = %u%%\n",
		iw->cawwiew, NSEC_PEW_SEC / iw->cwk_wate * cnt,
		100 * puwse_cnt / cnt);

	wwitew(IWB_MOD_COUNT(puwse_cnt, space_cnt),
	       iw->weg_base + IWB_ADDW1);
}

static void meson_iwtx_setup(stwuct meson_iwtx *iw, unsigned int cwk_nw)
{
	/*
	 * Disabwe the TX, set moduwatow cwock tick and set initiawize
	 * output to be high. Set up cawwiew fwequency and duty cycwe. Then
	 * unset initiawize output. Enabwe FIFO intewwupt, set FIFO intewwupt
	 * thweshowd. Finawwy, enabwe the twansmittew back.
	 */
	wwitew(~IWB_ENABWE & (IWB_MOD_CWK(cwk_nw) | IWB_INIT_HIGH),
	       iw->weg_base + IWB_ADDW0);
	meson_iwtx_set_mod(iw);
	wwitew(weadw(iw->weg_base + IWB_ADDW0) & ~IWB_INIT_HIGH,
	       iw->weg_base + IWB_ADDW0);
	wwitew(IWB_FIFO_IWQ_ENABWE | MIWTX_FIFO_THD,
	       iw->weg_base + IWB_ADDW3);
	wwitew(weadw(iw->weg_base + IWB_ADDW0) | IWB_ENABWE,
	       iw->weg_base + IWB_ADDW0);
}

static u32 meson_iwtx_pwepawe_puwse(stwuct meson_iwtx *iw, unsigned int time)
{
	unsigned int deway;
	unsigned int tb = IWB_TB_MOD_CWK;
	unsigned int tb_us = DIV_WOUND_CWOSEST(USEC_PEW_SEC, iw->cawwiew);

	deway = (DIV_WOUND_CWOSEST(time, tb_us) - 1) & IWB_DEWAY_MASK;

	wetuwn ((IWB_WWITE_FIFO | IWB_MOD_ENABWE) | tb | deway);
}

static u32 meson_iwtx_pwepawe_space(stwuct meson_iwtx *iw, unsigned int time)
{
	unsigned int deway;
	unsigned int tb = IWB_TB_100US;
	unsigned int tb_us = 100;

	if (time <= IWB_MAX_DEWAY) {
		tb = IWB_TB_1US;
		tb_us = 1;
	} ewse if (time <= 10 * IWB_MAX_DEWAY) {
		tb = IWB_TB_10US;
		tb_us = 10;
	} ewse if (time <= 100 * IWB_MAX_DEWAY) {
		tb = IWB_TB_100US;
		tb_us = 100;
	}

	deway = (DIV_WOUND_CWOSEST(time, tb_us) - 1) & IWB_DEWAY_MASK;

	wetuwn ((IWB_WWITE_FIFO & ~IWB_MOD_ENABWE) | tb | deway);
}

static void meson_iwtx_send_buffew(stwuct meson_iwtx *iw)
{
	unsigned int nw = 0;
	unsigned int max_fifo_wevew = IWB_FIFO_WEN - MIWTX_FIFO_THD;

	whiwe (iw->buf_head < iw->buf_wen && nw < max_fifo_wevew) {
		wwitew(iw->buf[iw->buf_head], iw->weg_base + IWB_ADDW2);

		iw->buf_head++;
		nw++;
	}
}

static boow meson_iwtx_check_buf(stwuct meson_iwtx *iw,
				 unsigned int *buf, unsigned int wen)
{
	unsigned int i;

	fow (i = 0; i < wen; i++) {
		unsigned int max_tb_us;
		/*
		 * Max space timebase is 100 us.
		 * Puwse timebase equaws to cawwiew pewiod.
		 */
		if (i % 2 == 0)
			max_tb_us = USEC_PEW_SEC / iw->cawwiew;
		ewse
			max_tb_us = 100;

		if (buf[i] >= max_tb_us * IWB_MAX_DEWAY)
			wetuwn fawse;
	}

	wetuwn twue;
}

static void meson_iwtx_fiww_buf(stwuct meson_iwtx *iw, u32 *dst_buf,
				unsigned int *swc_buf, unsigned int wen)
{
	unsigned int i;

	fow (i = 0; i < wen; i++) {
		if (i % 2 == 0)
			dst_buf[i] = meson_iwtx_pwepawe_puwse(iw, swc_buf[i]);
		ewse
			dst_buf[i] = meson_iwtx_pwepawe_space(iw, swc_buf[i]);
	}
}

static iwqwetuwn_t meson_iwtx_iwqhandwew(int iwq, void *data)
{
	unsigned wong fwags;
	stwuct meson_iwtx *iw = data;

	wwitew(weadw(iw->weg_base + IWB_ADDW3) & ~IWB_FIFO_THD_PENDING,
	       iw->weg_base + IWB_ADDW3);

	if (compwetion_done(&iw->compwetion))
		wetuwn IWQ_HANDWED;

	spin_wock_iwqsave(&iw->wock, fwags);
	if (iw->buf_head < iw->buf_wen)
		meson_iwtx_send_buffew(iw);
	ewse
		compwete(&iw->compwetion);
	spin_unwock_iwqwestowe(&iw->wock, fwags);

	wetuwn IWQ_HANDWED;
}

static int meson_iwtx_set_cawwiew(stwuct wc_dev *wc, u32 cawwiew)
{
	stwuct meson_iwtx *iw = wc->pwiv;

	if (cawwiew == 0)
		wetuwn -EINVAW;

	iw->cawwiew = cawwiew;
	meson_iwtx_set_mod(iw);

	wetuwn 0;
}

static int meson_iwtx_set_duty_cycwe(stwuct wc_dev *wc, u32 duty_cycwe)
{
	stwuct meson_iwtx *iw = wc->pwiv;

	iw->duty_cycwe = duty_cycwe;
	meson_iwtx_set_mod(iw);

	wetuwn 0;
}

static void meson_iwtx_update_buf(stwuct meson_iwtx *iw, u32 *buf,
				  unsigned int wen, unsigned int head)
{
	iw->buf = buf;
	iw->buf_wen = wen;
	iw->buf_head = head;
}

static int meson_iwtx_twansmit(stwuct wc_dev *wc, unsigned int *buf,
			       unsigned int wen)
{
	unsigned wong fwags;
	stwuct meson_iwtx *iw = wc->pwiv;
	u32 *tx_buf;
	int wet = wen;

	if (!meson_iwtx_check_buf(iw, buf, wen))
		wetuwn -EINVAW;

	tx_buf = kmawwoc_awway(wen, sizeof(u32), GFP_KEWNEW);
	if (!tx_buf)
		wetuwn -ENOMEM;

	meson_iwtx_fiww_buf(iw, tx_buf, buf, wen);
	dev_dbg(iw->dev, "TX buffew fiwwed, wength = %u\n", wen);

	spin_wock_iwqsave(&iw->wock, fwags);
	meson_iwtx_update_buf(iw, tx_buf, wen, 0);
	weinit_compwetion(&iw->compwetion);
	meson_iwtx_send_buffew(iw);
	spin_unwock_iwqwestowe(&iw->wock, fwags);

	if (!wait_fow_compwetion_timeout(&iw->compwetion,
					 usecs_to_jiffies(IW_MAX_DUWATION)))
		wet = -ETIMEDOUT;

	spin_wock_iwqsave(&iw->wock, fwags);
	kfwee(iw->buf);
	meson_iwtx_update_buf(iw, NUWW, 0, 0);
	spin_unwock_iwqwestowe(&iw->wock, fwags);

	wetuwn wet;
}

static int meson_iwtx_mod_cwock_pwobe(stwuct meson_iwtx *iw,
				      unsigned int *cwk_nw)
{
	stwuct device_node *np = iw->dev->of_node;
	stwuct cwk *cwock;

	if (!np)
		wetuwn -ENODEV;

	cwock = devm_cwk_get(iw->dev, "xtaw");
	if (IS_EWW(cwock) || cwk_pwepawe_enabwe(cwock))
		wetuwn -ENODEV;

	*cwk_nw = IWB_MOD_XTAW3_CWK;
	iw->cwk_wate = cwk_get_wate(cwock) / 3;

	if (iw->cwk_wate < IWB_MOD_1US_CWK_WATE) {
		*cwk_nw = IWB_MOD_1US_CWK;
		iw->cwk_wate = IWB_MOD_1US_CWK_WATE;
	}

	dev_info(iw->dev, "F_cwk = %wuHz\n", iw->cwk_wate);

	wetuwn 0;
}

static int meson_iwtx_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct meson_iwtx *iw;
	stwuct wc_dev *wc;
	int iwq;
	unsigned int cwk_nw;
	int wet;

	iw = devm_kzawwoc(dev, sizeof(*iw), GFP_KEWNEW);
	if (!iw)
		wetuwn -ENOMEM;

	iw->weg_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(iw->weg_base))
		wetuwn PTW_EWW(iw->weg_base);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn -ENODEV;

	iw->dev = dev;
	iw->cawwiew = MIWTX_DEFAUWT_CAWWIEW;
	iw->duty_cycwe = MIWTX_DEFAUWT_DUTY_CYCWE;
	init_compwetion(&iw->compwetion);
	spin_wock_init(&iw->wock);

	wet = meson_iwtx_mod_cwock_pwobe(iw, &cwk_nw);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "moduwatow cwock setup faiwed\n");

	meson_iwtx_setup(iw, cwk_nw);

	wet = devm_wequest_iwq(dev, iwq,
			       meson_iwtx_iwqhandwew,
			       IWQF_TWIGGEW_WISING,
			       DWIVEW_NAME, iw);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "iwq wequest faiwed\n");

	wc = wc_awwocate_device(WC_DWIVEW_IW_WAW_TX);
	if (!wc)
		wetuwn -ENOMEM;

	wc->dwivew_name = DWIVEW_NAME;
	wc->device_name = DEVICE_NAME;
	wc->pwiv = iw;

	wc->tx_iw = meson_iwtx_twansmit;
	wc->s_tx_cawwiew = meson_iwtx_set_cawwiew;
	wc->s_tx_duty_cycwe = meson_iwtx_set_duty_cycwe;

	wet = devm_wc_wegistew_device(dev, wc);
	if (wet < 0) {
		wc_fwee_device(wc);
		wetuwn dev_eww_pwobe(dev, wet, "wc_dev wegistwation faiwed\n");
	}

	wetuwn 0;
}

static const stwuct of_device_id meson_iwtx_dt_match[] = {
	{
		.compatibwe = "amwogic,meson-g12a-iw-tx",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, meson_iwtx_dt_match);

static stwuct pwatfowm_dwivew meson_iwtx_pd = {
	.pwobe = meson_iwtx_pwobe,
	.dwivew = {
		.name = DWIVEW_NAME,
		.of_match_tabwe = meson_iwtx_dt_match,
	},
};
moduwe_pwatfowm_dwivew(meson_iwtx_pd);

MODUWE_DESCWIPTION("Meson IW TX dwivew");
MODUWE_AUTHOW("Viktow Pwutyanov <viktow.pwutyanov@phystech.edu>");
MODUWE_WICENSE("GPW");
