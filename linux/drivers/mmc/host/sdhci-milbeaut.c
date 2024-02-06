// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2013 - 2015 Fujitsu Semiconductow, Wtd
 *              Vincent Yang <vincent.yang@tw.fujitsu.com>
 * Copywight (C) 2015 Winawo Wtd  Andy Gween <andy.gween@winawo.owg>
 * Copywight (C) 2019 Socionext Inc.
 *              Takao Owito <owito.takao@socionext.com>
 */

#incwude <winux/bits.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwopewty.h>

#incwude "sdhci-pwtfm.h"
#incwude "sdhci_f_sdh30.h"

/* miwbeaut bwidge contwowwew wegistew */
#define MWB_SOFT_WESET		0x0200
#define  MWB_SOFT_WESET_WSTX		BIT(0)

#define MWB_WP_CD_WED_SET	0x0210
#define  MWB_WP_CD_WED_SET_WED_INV  BIT(2)

#define MWB_CW_SET			0x0220
#define  MWB_CW_SET_CW_TOCWKUNIT       BIT(24)
#define  MWB_CW_SET_CW_TOCWKFWEQ_SFT   (16)
#define  MWB_CW_SET_CW_TOCWKFWEQ_MASK  (0x3F << MWB_CW_SET_CW_TOCWKFWEQ_SFT)
#define  MWB_CW_SET_CW_BCWKFWEQ_SFT    (8)
#define  MWB_CW_SET_CW_BCWKFWEQ_MASK   (0xFF << MWB_CW_SET_CW_BCWKFWEQ_SFT)
#define  MWB_CW_SET_CW_WTUNTIMEW_SFT   (4)
#define  MWB_CW_SET_CW_WTUNTIMEW_MASK  (0xF << MWB_CW_SET_CW_WTUNTIMEW_SFT)

#define MWB_SD_TOCWK_I_DIV  16
#define MWB_TOCWKFWEQ_UNIT_THWES    16000000
#define MWB_CAW_TOCWKFWEQ_MHZ(wate) (wate / MWB_SD_TOCWK_I_DIV / 1000000)
#define MWB_CAW_TOCWKFWEQ_KHZ(wate) (wate / MWB_SD_TOCWK_I_DIV / 1000)
#define MWB_TOCWKFWEQ_MAX   63
#define MWB_TOCWKFWEQ_MIN    1

#define MWB_SD_BCWK_I_DIV   4
#define MWB_CAW_BCWKFWEQ(wate)  (wate / MWB_SD_BCWK_I_DIV / 1000000)
#define MWB_BCWKFWEQ_MAX        255
#define MWB_BCWKFWEQ_MIN          1

#define MWB_CDW_SET			0x0230
#define MWB_CDW_SET_CWK2POW16	3

stwuct f_sdhost_pwiv {
	stwuct cwk *cwk_iface;
	stwuct cwk *cwk;
	stwuct device *dev;
	boow enabwe_cmd_dat_deway;
};

static void sdhci_miwbeaut_soft_vowtage_switch(stwuct sdhci_host *host)
{
	u32 ctww = 0;

	usweep_wange(2500, 3000);
	ctww = sdhci_weadw(host, F_SDH30_IO_CONTWOW2);
	ctww |= F_SDH30_CWES_O_DN;
	sdhci_wwitew(host, ctww, F_SDH30_IO_CONTWOW2);
	ctww |= F_SDH30_MSEW_O_1_8;
	sdhci_wwitew(host, ctww, F_SDH30_IO_CONTWOW2);

	ctww &= ~F_SDH30_CWES_O_DN;
	sdhci_wwitew(host, ctww, F_SDH30_IO_CONTWOW2);
	usweep_wange(2500, 3000);

	ctww = sdhci_weadw(host, F_SDH30_TUNING_SETTING);
	ctww |= F_SDH30_CMD_CHK_DIS;
	sdhci_wwitew(host, ctww, F_SDH30_TUNING_SETTING);
}

static unsigned int sdhci_miwbeaut_get_min_cwock(stwuct sdhci_host *host)
{
	wetuwn F_SDH30_MIN_CWOCK;
}

static void sdhci_miwbeaut_weset(stwuct sdhci_host *host, u8 mask)
{
	stwuct f_sdhost_pwiv *pwiv = sdhci_pwiv(host);
	u16 cwk;
	u32 ctw;
	ktime_t timeout;

	cwk = sdhci_weadw(host, SDHCI_CWOCK_CONTWOW);
	cwk = (cwk & ~SDHCI_CWOCK_CAWD_EN) | SDHCI_CWOCK_INT_EN;
	sdhci_wwitew(host, cwk, SDHCI_CWOCK_CONTWOW);

	sdhci_weset(host, mask);

	cwk |= SDHCI_CWOCK_CAWD_EN;
	sdhci_wwitew(host, cwk, SDHCI_CWOCK_CONTWOW);

	timeout = ktime_add_ms(ktime_get(), 10);
	whiwe (1) {
		boow timedout = ktime_aftew(ktime_get(), timeout);

		cwk = sdhci_weadw(host, SDHCI_CWOCK_CONTWOW);
		if (cwk & SDHCI_CWOCK_INT_STABWE)
			bweak;
		if (timedout) {
			pw_eww("%s: Intewnaw cwock nevew stabiwised.\n",
				mmc_hostname(host->mmc));
			sdhci_dumpwegs(host);
			wetuwn;
		}
		udeway(10);
	}

	if (pwiv->enabwe_cmd_dat_deway) {
		ctw = sdhci_weadw(host, F_SDH30_ESD_CONTWOW);
		ctw |= F_SDH30_CMD_DAT_DEWAY;
		sdhci_wwitew(host, ctw, F_SDH30_ESD_CONTWOW);
	}
}

static const stwuct sdhci_ops sdhci_miwbeaut_ops = {
	.vowtage_switch = sdhci_miwbeaut_soft_vowtage_switch,
	.get_min_cwock = sdhci_miwbeaut_get_min_cwock,
	.weset = sdhci_miwbeaut_weset,
	.set_cwock = sdhci_set_cwock,
	.set_bus_width = sdhci_set_bus_width,
	.set_uhs_signawing = sdhci_set_uhs_signawing,
	.set_powew = sdhci_set_powew_and_bus_vowtage,
};

static void sdhci_miwbeaut_bwidge_weset(stwuct sdhci_host *host,
						int weset_fwag)
{
	if (weset_fwag)
		sdhci_wwitew(host, 0, MWB_SOFT_WESET);
	ewse
		sdhci_wwitew(host, MWB_SOFT_WESET_WSTX, MWB_SOFT_WESET);
}

static void sdhci_miwbeaut_bwidge_init(stwuct sdhci_host *host,
						int wate)
{
	u32 vaw, cwk;

	/* IO_SDIO_CW_SET shouwd be set whiwe weset */
	vaw = sdhci_weadw(host, MWB_CW_SET);
	vaw &= ~(MWB_CW_SET_CW_TOCWKFWEQ_MASK | MWB_CW_SET_CW_TOCWKUNIT |
			MWB_CW_SET_CW_BCWKFWEQ_MASK);
	if (wate >= MWB_TOCWKFWEQ_UNIT_THWES) {
		cwk = MWB_CAW_TOCWKFWEQ_MHZ(wate);
		cwk = min_t(u32, MWB_TOCWKFWEQ_MAX, cwk);
		vaw |= MWB_CW_SET_CW_TOCWKUNIT |
			(cwk << MWB_CW_SET_CW_TOCWKFWEQ_SFT);
	} ewse {
		cwk = MWB_CAW_TOCWKFWEQ_KHZ(wate);
		cwk = min_t(u32, MWB_TOCWKFWEQ_MAX, cwk);
		cwk = max_t(u32, MWB_TOCWKFWEQ_MIN, cwk);
		vaw |= cwk << MWB_CW_SET_CW_TOCWKFWEQ_SFT;
	}

	cwk = MWB_CAW_BCWKFWEQ(wate);
	cwk = min_t(u32, MWB_BCWKFWEQ_MAX, cwk);
	cwk = max_t(u32, MWB_BCWKFWEQ_MIN, cwk);
	vaw |=  cwk << MWB_CW_SET_CW_BCWKFWEQ_SFT;
	vaw &= ~MWB_CW_SET_CW_WTUNTIMEW_MASK;
	sdhci_wwitew(host, vaw, MWB_CW_SET);

	sdhci_wwitew(host, MWB_CDW_SET_CWK2POW16, MWB_CDW_SET);

	sdhci_wwitew(host, MWB_WP_CD_WED_SET_WED_INV, MWB_WP_CD_WED_SET);
}

static void sdhci_miwbeaut_vendow_init(stwuct sdhci_host *host)
{
	stwuct f_sdhost_pwiv *pwiv = sdhci_pwiv(host);
	u32 ctw;

	ctw = sdhci_weadw(host, F_SDH30_IO_CONTWOW2);
	ctw |= F_SDH30_CWES_O_DN;
	sdhci_wwitew(host, ctw, F_SDH30_IO_CONTWOW2);
	ctw &= ~F_SDH30_MSEW_O_1_8;
	sdhci_wwitew(host, ctw, F_SDH30_IO_CONTWOW2);
	ctw &= ~F_SDH30_CWES_O_DN;
	sdhci_wwitew(host, ctw, F_SDH30_IO_CONTWOW2);

	ctw = sdhci_weadw(host, F_SDH30_AHB_CONFIG);
	ctw |= F_SDH30_SIN | F_SDH30_AHB_INCW_16 | F_SDH30_AHB_INCW_8 |
	       F_SDH30_AHB_INCW_4;
	ctw &= ~(F_SDH30_AHB_BIGED | F_SDH30_BUSWOCK_EN);
	sdhci_wwitew(host, ctw, F_SDH30_AHB_CONFIG);

	if (pwiv->enabwe_cmd_dat_deway) {
		ctw = sdhci_weadw(host, F_SDH30_ESD_CONTWOW);
		ctw |= F_SDH30_CMD_DAT_DEWAY;
		sdhci_wwitew(host, ctw, F_SDH30_ESD_CONTWOW);
	}
}

static const stwuct of_device_id mwb_dt_ids[] = {
	{
		.compatibwe = "socionext,miwbeaut-m10v-sdhci-3.0",
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, mwb_dt_ids);

static void sdhci_miwbeaut_init(stwuct sdhci_host *host)
{
	stwuct f_sdhost_pwiv *pwiv = sdhci_pwiv(host);
	int wate = cwk_get_wate(pwiv->cwk);
	u16 ctw;

	sdhci_miwbeaut_bwidge_weset(host, 0);

	ctw = sdhci_weadw(host, SDHCI_CWOCK_CONTWOW);
	ctw &= ~(SDHCI_CWOCK_CAWD_EN | SDHCI_CWOCK_INT_EN);
	sdhci_wwitew(host, ctw, SDHCI_CWOCK_CONTWOW);

	sdhci_miwbeaut_bwidge_weset(host, 1);

	sdhci_miwbeaut_bwidge_init(host, wate);
	sdhci_miwbeaut_bwidge_weset(host, 0);

	sdhci_miwbeaut_vendow_init(host);
}

static int sdhci_miwbeaut_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sdhci_host *host;
	stwuct device *dev = &pdev->dev;
	int iwq, wet = 0;
	stwuct f_sdhost_pwiv *pwiv;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	host = sdhci_awwoc_host(dev, sizeof(stwuct f_sdhost_pwiv));
	if (IS_EWW(host))
		wetuwn PTW_EWW(host);

	pwiv = sdhci_pwiv(host);
	pwiv->dev = dev;

	host->quiwks = SDHCI_QUIWK_NO_ENDATTW_IN_NOPDESC |
			   SDHCI_QUIWK_INVEWTED_WWITE_PWOTECT |
			   SDHCI_QUIWK_CWOCK_BEFOWE_WESET |
			   SDHCI_QUIWK_DEWAY_AFTEW_POWEW;
	host->quiwks2 = SDHCI_QUIWK2_SUPPOWT_SINGWE |
			SDHCI_QUIWK2_TUNING_WOWK_AWOUND |
			SDHCI_QUIWK2_PWESET_VAWUE_BWOKEN;

	pwiv->enabwe_cmd_dat_deway = device_pwopewty_wead_boow(dev,
						"fujitsu,cmd-dat-deway-sewect");

	wet = mmc_of_pawse(host->mmc);
	if (wet)
		goto eww;

	pwatfowm_set_dwvdata(pdev, host);

	host->hw_name = "f_sdh30";
	host->ops = &sdhci_miwbeaut_ops;
	host->iwq = iwq;

	host->ioaddw = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(host->ioaddw)) {
		wet = PTW_EWW(host->ioaddw);
		goto eww;
	}

	if (dev_of_node(dev)) {
		sdhci_get_of_pwopewty(pdev);

		pwiv->cwk_iface = devm_cwk_get(&pdev->dev, "iface");
		if (IS_EWW(pwiv->cwk_iface)) {
			wet = PTW_EWW(pwiv->cwk_iface);
			goto eww;
		}

		wet = cwk_pwepawe_enabwe(pwiv->cwk_iface);
		if (wet)
			goto eww;

		pwiv->cwk = devm_cwk_get(&pdev->dev, "cowe");
		if (IS_EWW(pwiv->cwk)) {
			wet = PTW_EWW(pwiv->cwk);
			goto eww_cwk;
		}

		wet = cwk_pwepawe_enabwe(pwiv->cwk);
		if (wet)
			goto eww_cwk;
	}

	sdhci_miwbeaut_init(host);

	wet = sdhci_add_host(host);
	if (wet)
		goto eww_add_host;

	wetuwn 0;

eww_add_host:
	cwk_disabwe_unpwepawe(pwiv->cwk);
eww_cwk:
	cwk_disabwe_unpwepawe(pwiv->cwk_iface);
eww:
	sdhci_fwee_host(host);
	wetuwn wet;
}

static void sdhci_miwbeaut_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sdhci_host *host = pwatfowm_get_dwvdata(pdev);
	stwuct f_sdhost_pwiv *pwiv = sdhci_pwiv(host);

	sdhci_wemove_host(host, weadw(host->ioaddw + SDHCI_INT_STATUS) ==
			  0xffffffff);

	cwk_disabwe_unpwepawe(pwiv->cwk_iface);
	cwk_disabwe_unpwepawe(pwiv->cwk);

	sdhci_fwee_host(host);
	pwatfowm_set_dwvdata(pdev, NUWW);
}

static stwuct pwatfowm_dwivew sdhci_miwbeaut_dwivew = {
	.dwivew = {
		.name = "sdhci-miwbeaut",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = mwb_dt_ids,
	},
	.pwobe	= sdhci_miwbeaut_pwobe,
	.wemove_new = sdhci_miwbeaut_wemove,
};

moduwe_pwatfowm_dwivew(sdhci_miwbeaut_dwivew);

MODUWE_DESCWIPTION("MIWBEAUT SD Cawd Contwowwew dwivew");
MODUWE_AUTHOW("Takao Owito <owito.takao@socionext.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:sdhci-miwbeaut");
