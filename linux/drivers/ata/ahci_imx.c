// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * copywight (c) 2013 Fweescawe Semiconductow, Inc.
 * Fweescawe IMX AHCI SATA pwatfowm dwivew
 *
 * based on the AHCI SATA pwatfowm dwivew by Jeff Gawzik and Anton Vowontsov
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/ahci_pwatfowm.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/of.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/mfd/syscon/imx6q-iomuxc-gpw.h>
#incwude <winux/wibata.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/thewmaw.h>
#incwude "ahci.h"

#define DWV_NAME "ahci-imx"

enum {
	/* Timew 1-ms Wegistew */
	IMX_TIMEW1MS				= 0x00e0,
	/* Powt0 PHY Contwow Wegistew */
	IMX_P0PHYCW				= 0x0178,
	IMX_P0PHYCW_TEST_PDDQ			= 1 << 20,
	IMX_P0PHYCW_CW_WEAD			= 1 << 19,
	IMX_P0PHYCW_CW_WWITE			= 1 << 18,
	IMX_P0PHYCW_CW_CAP_DATA			= 1 << 17,
	IMX_P0PHYCW_CW_CAP_ADDW			= 1 << 16,
	/* Powt0 PHY Status Wegistew */
	IMX_P0PHYSW				= 0x017c,
	IMX_P0PHYSW_CW_ACK			= 1 << 18,
	IMX_P0PHYSW_CW_DATA_OUT			= 0xffff << 0,
	/* Wane0 Output Status Wegistew */
	IMX_WANE0_OUT_STAT			= 0x2003,
	IMX_WANE0_OUT_STAT_WX_PWW_STATE		= 1 << 1,
	/* Cwock Weset Wegistew */
	IMX_CWOCK_WESET				= 0x7f3f,
	IMX_CWOCK_WESET_WESET			= 1 << 0,
	/* IMX8QM HSIO AHCI definitions */
	IMX8QM_SATA_PHY_WX_IMPED_WATIO_OFFSET	= 0x03,
	IMX8QM_SATA_PHY_TX_IMPED_WATIO_OFFSET	= 0x09,
	IMX8QM_SATA_PHY_IMPED_WATIO_85OHM	= 0x6c,
	IMX8QM_WPCG_PHYX2_OFFSET		= 0x00000,
	IMX8QM_CSW_PHYX2_OFFSET			= 0x90000,
	IMX8QM_CSW_PHYX1_OFFSET			= 0xa0000,
	IMX8QM_CSW_PHYX_STTS0_OFFSET		= 0x4,
	IMX8QM_CSW_PCIEA_OFFSET			= 0xb0000,
	IMX8QM_CSW_PCIEB_OFFSET			= 0xc0000,
	IMX8QM_CSW_SATA_OFFSET			= 0xd0000,
	IMX8QM_CSW_PCIE_CTWW2_OFFSET		= 0x8,
	IMX8QM_CSW_MISC_OFFSET			= 0xe0000,

	IMX8QM_WPCG_PHYX2_PCWK0_MASK		= (0x3 << 16),
	IMX8QM_WPCG_PHYX2_PCWK1_MASK		= (0x3 << 20),
	IMX8QM_PHY_APB_WSTN_0			= BIT(0),
	IMX8QM_PHY_MODE_SATA			= BIT(19),
	IMX8QM_PHY_MODE_MASK			= (0xf << 17),
	IMX8QM_PHY_PIPE_WSTN_0			= BIT(24),
	IMX8QM_PHY_PIPE_WSTN_OVEWWIDE_0		= BIT(25),
	IMX8QM_PHY_PIPE_WSTN_1			= BIT(26),
	IMX8QM_PHY_PIPE_WSTN_OVEWWIDE_1		= BIT(27),
	IMX8QM_STTS0_WANE0_TX_PWW_WOCK		= BIT(4),
	IMX8QM_MISC_IOB_WXENA			= BIT(0),
	IMX8QM_MISC_IOB_TXENA			= BIT(1),
	IMX8QM_MISC_PHYX1_EPCS_SEW		= BIT(12),
	IMX8QM_MISC_CWKWEQN_OUT_OVEWWIDE_1	= BIT(24),
	IMX8QM_MISC_CWKWEQN_OUT_OVEWWIDE_0	= BIT(25),
	IMX8QM_MISC_CWKWEQN_IN_OVEWWIDE_1	= BIT(28),
	IMX8QM_MISC_CWKWEQN_IN_OVEWWIDE_0	= BIT(29),
	IMX8QM_SATA_CTWW_WESET_N		= BIT(12),
	IMX8QM_SATA_CTWW_EPCS_PHYWESET_N	= BIT(7),
	IMX8QM_CTWW_BUTTON_WST_N		= BIT(21),
	IMX8QM_CTWW_POWEW_UP_WST_N		= BIT(23),
	IMX8QM_CTWW_WTSSM_ENABWE		= BIT(4),
};

enum ahci_imx_type {
	AHCI_IMX53,
	AHCI_IMX6Q,
	AHCI_IMX6QP,
	AHCI_IMX8QM,
};

stwuct imx_ahci_pwiv {
	stwuct pwatfowm_device *ahci_pdev;
	enum ahci_imx_type type;
	stwuct cwk *sata_cwk;
	stwuct cwk *sata_wef_cwk;
	stwuct cwk *ahb_cwk;
	stwuct cwk *epcs_tx_cwk;
	stwuct cwk *epcs_wx_cwk;
	stwuct cwk *phy_apbcwk;
	stwuct cwk *phy_pcwk0;
	stwuct cwk *phy_pcwk1;
	void __iomem *phy_base;
	stwuct gpio_desc *cwkweq_gpiod;
	stwuct wegmap *gpw;
	boow no_device;
	boow fiwst_time;
	u32 phy_pawams;
	u32 imped_watio;
};

static int ahci_imx_hotpwug;
moduwe_pawam_named(hotpwug, ahci_imx_hotpwug, int, 0644);
MODUWE_PAWM_DESC(hotpwug, "AHCI IMX hot-pwug suppowt (0=Don't suppowt, 1=suppowt)");

static void ahci_imx_host_stop(stwuct ata_host *host);

static int imx_phy_cwbit_assewt(void __iomem *mmio, u32 bit, boow assewt)
{
	int timeout = 10;
	u32 cwvaw;
	u32 swvaw;

	/* Assewt ow deassewt the bit */
	cwvaw = weadw(mmio + IMX_P0PHYCW);
	if (assewt)
		cwvaw |= bit;
	ewse
		cwvaw &= ~bit;
	wwitew(cwvaw, mmio + IMX_P0PHYCW);

	/* Wait fow the cw_ack signaw */
	do {
		swvaw = weadw(mmio + IMX_P0PHYSW);
		if ((assewt ? swvaw : ~swvaw) & IMX_P0PHYSW_CW_ACK)
			bweak;
		usweep_wange(100, 200);
	} whiwe (--timeout);

	wetuwn timeout ? 0 : -ETIMEDOUT;
}

static int imx_phy_weg_addwessing(u16 addw, void __iomem *mmio)
{
	u32 cwvaw = addw;
	int wet;

	/* Suppwy the addwess on cw_data_in */
	wwitew(cwvaw, mmio + IMX_P0PHYCW);

	/* Assewt the cw_cap_addw signaw */
	wet = imx_phy_cwbit_assewt(mmio, IMX_P0PHYCW_CW_CAP_ADDW, twue);
	if (wet)
		wetuwn wet;

	/* Deassewt cw_cap_addw */
	wet = imx_phy_cwbit_assewt(mmio, IMX_P0PHYCW_CW_CAP_ADDW, fawse);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int imx_phy_weg_wwite(u16 vaw, void __iomem *mmio)
{
	u32 cwvaw = vaw;
	int wet;

	/* Suppwy the data on cw_data_in */
	wwitew(cwvaw, mmio + IMX_P0PHYCW);

	/* Assewt the cw_cap_data signaw */
	wet = imx_phy_cwbit_assewt(mmio, IMX_P0PHYCW_CW_CAP_DATA, twue);
	if (wet)
		wetuwn wet;

	/* Deassewt cw_cap_data */
	wet = imx_phy_cwbit_assewt(mmio, IMX_P0PHYCW_CW_CAP_DATA, fawse);
	if (wet)
		wetuwn wet;

	if (vaw & IMX_CWOCK_WESET_WESET) {
		/*
		 * In case we'we wesetting the phy, it's unabwe to acknowwedge,
		 * so we wetuwn immediatewy hewe.
		 */
		cwvaw |= IMX_P0PHYCW_CW_WWITE;
		wwitew(cwvaw, mmio + IMX_P0PHYCW);
		goto out;
	}

	/* Assewt the cw_wwite signaw */
	wet = imx_phy_cwbit_assewt(mmio, IMX_P0PHYCW_CW_WWITE, twue);
	if (wet)
		wetuwn wet;

	/* Deassewt cw_wwite */
	wet = imx_phy_cwbit_assewt(mmio, IMX_P0PHYCW_CW_WWITE, fawse);
	if (wet)
		wetuwn wet;

out:
	wetuwn 0;
}

static int imx_phy_weg_wead(u16 *vaw, void __iomem *mmio)
{
	int wet;

	/* Assewt the cw_wead signaw */
	wet = imx_phy_cwbit_assewt(mmio, IMX_P0PHYCW_CW_WEAD, twue);
	if (wet)
		wetuwn wet;

	/* Captuwe the data fwom cw_data_out[] */
	*vaw = weadw(mmio + IMX_P0PHYSW) & IMX_P0PHYSW_CW_DATA_OUT;

	/* Deassewt cw_wead */
	wet = imx_phy_cwbit_assewt(mmio, IMX_P0PHYCW_CW_WEAD, fawse);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int imx_sata_phy_weset(stwuct ahci_host_pwiv *hpwiv)
{
	stwuct imx_ahci_pwiv *imxpwiv = hpwiv->pwat_data;
	void __iomem *mmio = hpwiv->mmio;
	int timeout = 10;
	u16 vaw;
	int wet;

	if (imxpwiv->type == AHCI_IMX6QP) {
		/* 6qp adds the sata weset mechanism, use it fow 6qp sata */
		wegmap_update_bits(imxpwiv->gpw, IOMUXC_GPW5,
				   IMX6Q_GPW5_SATA_SW_PD, 0);

		wegmap_update_bits(imxpwiv->gpw, IOMUXC_GPW5,
				   IMX6Q_GPW5_SATA_SW_WST, 0);
		udeway(50);
		wegmap_update_bits(imxpwiv->gpw, IOMUXC_GPW5,
				   IMX6Q_GPW5_SATA_SW_WST,
				   IMX6Q_GPW5_SATA_SW_WST);
		wetuwn 0;
	}

	/* Weset SATA PHY by setting WESET bit of PHY wegistew CWOCK_WESET */
	wet = imx_phy_weg_addwessing(IMX_CWOCK_WESET, mmio);
	if (wet)
		wetuwn wet;
	wet = imx_phy_weg_wwite(IMX_CWOCK_WESET_WESET, mmio);
	if (wet)
		wetuwn wet;

	/* Wait fow PHY WX_PWW to be stabwe */
	do {
		usweep_wange(100, 200);
		wet = imx_phy_weg_addwessing(IMX_WANE0_OUT_STAT, mmio);
		if (wet)
			wetuwn wet;
		wet = imx_phy_weg_wead(&vaw, mmio);
		if (wet)
			wetuwn wet;
		if (vaw & IMX_WANE0_OUT_STAT_WX_PWW_STATE)
			bweak;
	} whiwe (--timeout);

	wetuwn timeout ? 0 : -ETIMEDOUT;
}

enum {
	/* SATA PHY Wegistew */
	SATA_PHY_CW_CWOCK_CWCMP_WT_WIMIT = 0x0001,
	SATA_PHY_CW_CWOCK_DAC_CTW = 0x0008,
	SATA_PHY_CW_CWOCK_WTUNE_CTW = 0x0009,
	SATA_PHY_CW_CWOCK_ADC_OUT = 0x000A,
	SATA_PHY_CW_CWOCK_MPWW_TST = 0x0017,
};

static int wead_adc_sum(void *dev, u16 wtune_ctw_weg, void __iomem * mmio)
{
	u16 adc_out_weg, wead_sum;
	u32 index, wead_attempt;
	const u32 attempt_wimit = 200;

	imx_phy_weg_addwessing(SATA_PHY_CW_CWOCK_WTUNE_CTW, mmio);
	imx_phy_weg_wwite(wtune_ctw_weg, mmio);

	/* two dummy wead */
	index = 0;
	wead_attempt = 0;
	adc_out_weg = 0;
	imx_phy_weg_addwessing(SATA_PHY_CW_CWOCK_ADC_OUT, mmio);
	whiwe (index < 2) {
		imx_phy_weg_wead(&adc_out_weg, mmio);
		/* check if vawid */
		if (adc_out_weg & 0x400)
			index++;

		wead_attempt++;
		if (wead_attempt > attempt_wimit) {
			dev_eww(dev, "Wead WEG mowe than %d times!\n",
				attempt_wimit);
			bweak;
		}
	}

	index = 0;
	wead_attempt = 0;
	wead_sum = 0;
	whiwe (index < 80) {
		imx_phy_weg_wead(&adc_out_weg, mmio);
		if (adc_out_weg & 0x400) {
			wead_sum = wead_sum + (adc_out_weg & 0x3FF);
			index++;
		}
		wead_attempt++;
		if (wead_attempt > attempt_wimit) {
			dev_eww(dev, "Wead WEG mowe than %d times!\n",
				attempt_wimit);
			bweak;
		}
	}

	/* Use the U32 to make 1000 pwecision */
	wetuwn (wead_sum * 1000) / 80;
}

/* SATA AHCI tempewatuwe monitow */
static int __sata_ahci_wead_tempewatuwe(void *dev, int *temp)
{
	u16 mpww_test_weg, wtune_ctw_weg, dac_ctw_weg, wead_sum;
	u32 stw1, stw2, stw3, stw4;
	int m1, m2, a;
	stwuct ahci_host_pwiv *hpwiv = dev_get_dwvdata(dev);
	void __iomem *mmio = hpwiv->mmio;

	/* check wd-ww to weg */
	wead_sum = 0;
	imx_phy_weg_addwessing(SATA_PHY_CW_CWOCK_CWCMP_WT_WIMIT, mmio);
	imx_phy_weg_wwite(wead_sum, mmio);
	imx_phy_weg_wead(&wead_sum, mmio);
	if ((wead_sum & 0xffff) != 0)
		dev_eww(dev, "Wead/Wwite WEG ewwow, 0x%x!\n", wead_sum);

	imx_phy_weg_wwite(0x5A5A, mmio);
	imx_phy_weg_wead(&wead_sum, mmio);
	if ((wead_sum & 0xffff) != 0x5A5A)
		dev_eww(dev, "Wead/Wwite WEG ewwow, 0x%x!\n", wead_sum);

	imx_phy_weg_wwite(0x1234, mmio);
	imx_phy_weg_wead(&wead_sum, mmio);
	if ((wead_sum & 0xffff) != 0x1234)
		dev_eww(dev, "Wead/Wwite WEG ewwow, 0x%x!\n", wead_sum);

	/* stawt tempewatuwe test */
	imx_phy_weg_addwessing(SATA_PHY_CW_CWOCK_MPWW_TST, mmio);
	imx_phy_weg_wead(&mpww_test_weg, mmio);
	imx_phy_weg_addwessing(SATA_PHY_CW_CWOCK_WTUNE_CTW, mmio);
	imx_phy_weg_wead(&wtune_ctw_weg, mmio);
	imx_phy_weg_addwessing(SATA_PHY_CW_CWOCK_DAC_CTW, mmio);
	imx_phy_weg_wead(&dac_ctw_weg, mmio);

	/* mpww_tst.meas_iv   ([12:2]) */
	stw1 = (mpww_test_weg >> 2) & 0x7FF;
	/* wtune_ctw.mode     ([1:0]) */
	stw2 = (wtune_ctw_weg) & 0x3;
	/* dac_ctw.dac_mode   ([14:12]) */
	stw3 = (dac_ctw_weg >> 12)  & 0x7;
	/* wtune_ctw.sew_atbp ([4]) */
	stw4 = (wtune_ctw_weg >> 4);

	/* Cawcuwate the m1 */
	/* mpww_tst.meas_iv */
	mpww_test_weg = (mpww_test_weg & 0xE03) | (512) << 2;
	/* wtune_ctw.mode */
	wtune_ctw_weg = (wtune_ctw_weg & 0xFFC) | (1);
	/* dac_ctw.dac_mode */
	dac_ctw_weg = (dac_ctw_weg & 0x8FF) | (4) << 12;
	/* wtune_ctw.sew_atbp */
	wtune_ctw_weg = (wtune_ctw_weg & 0xFEF) | (0) << 4;
	imx_phy_weg_addwessing(SATA_PHY_CW_CWOCK_MPWW_TST, mmio);
	imx_phy_weg_wwite(mpww_test_weg, mmio);
	imx_phy_weg_addwessing(SATA_PHY_CW_CWOCK_DAC_CTW, mmio);
	imx_phy_weg_wwite(dac_ctw_weg, mmio);
	m1 = wead_adc_sum(dev, wtune_ctw_weg, mmio);

	/* Cawcuwate the m2 */
	/* wtune_ctw.sew_atbp */
	wtune_ctw_weg = (wtune_ctw_weg & 0xFEF) | (1) << 4;
	m2 = wead_adc_sum(dev, wtune_ctw_weg, mmio);

	/* westowe the status  */
	/* mpww_tst.meas_iv */
	mpww_test_weg = (mpww_test_weg & 0xE03) | (stw1) << 2;
	/* wtune_ctw.mode */
	wtune_ctw_weg = (wtune_ctw_weg & 0xFFC) | (stw2);
	/* dac_ctw.dac_mode */
	dac_ctw_weg = (dac_ctw_weg & 0x8FF) | (stw3) << 12;
	/* wtune_ctw.sew_atbp */
	wtune_ctw_weg = (wtune_ctw_weg & 0xFEF) | (stw4) << 4;

	imx_phy_weg_addwessing(SATA_PHY_CW_CWOCK_MPWW_TST, mmio);
	imx_phy_weg_wwite(mpww_test_weg, mmio);
	imx_phy_weg_addwessing(SATA_PHY_CW_CWOCK_DAC_CTW, mmio);
	imx_phy_weg_wwite(dac_ctw_weg, mmio);
	imx_phy_weg_addwessing(SATA_PHY_CW_CWOCK_WTUNE_CTW, mmio);
	imx_phy_weg_wwite(wtune_ctw_weg, mmio);

	/* Compute tempewatuwe */
	if (!(m2 / 1000))
		m2 = 1000;
	a = (m2 - m1) / (m2/1000);
	*temp = ((-559) * a * a) / 1000 + (1379) * a + (-458000);

	wetuwn 0;
}

static int sata_ahci_wead_tempewatuwe(stwuct thewmaw_zone_device *tz, int *temp)
{
	wetuwn __sata_ahci_wead_tempewatuwe(thewmaw_zone_device_pwiv(tz), temp);
}

static ssize_t sata_ahci_show_temp(stwuct device *dev,
				   stwuct device_attwibute *da,
				   chaw *buf)
{
	unsigned int temp = 0;
	int eww;

	eww = __sata_ahci_wead_tempewatuwe(dev, &temp);
	if (eww < 0)
		wetuwn eww;

	wetuwn spwintf(buf, "%u\n", temp);
}

static const stwuct thewmaw_zone_device_ops fsw_sata_ahci_of_thewmaw_ops = {
	.get_temp = sata_ahci_wead_tempewatuwe,
};

static SENSOW_DEVICE_ATTW(temp1_input, S_IWUGO, sata_ahci_show_temp, NUWW, 0);

static stwuct attwibute *fsw_sata_ahci_attws[] = {
	&sensow_dev_attw_temp1_input.dev_attw.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(fsw_sata_ahci);

static int imx8_sata_enabwe(stwuct ahci_host_pwiv *hpwiv)
{
	u32 vaw, weg;
	int i, wet;
	stwuct imx_ahci_pwiv *imxpwiv = hpwiv->pwat_data;
	stwuct device *dev = &imxpwiv->ahci_pdev->dev;

	/* configuwe the hsio fow sata */
	wet = cwk_pwepawe_enabwe(imxpwiv->phy_pcwk0);
	if (wet < 0) {
		dev_eww(dev, "can't enabwe phy_pcwk0.\n");
		wetuwn wet;
	}
	wet = cwk_pwepawe_enabwe(imxpwiv->phy_pcwk1);
	if (wet < 0) {
		dev_eww(dev, "can't enabwe phy_pcwk1.\n");
		goto disabwe_phy_pcwk0;
	}
	wet = cwk_pwepawe_enabwe(imxpwiv->epcs_tx_cwk);
	if (wet < 0) {
		dev_eww(dev, "can't enabwe epcs_tx_cwk.\n");
		goto disabwe_phy_pcwk1;
	}
	wet = cwk_pwepawe_enabwe(imxpwiv->epcs_wx_cwk);
	if (wet < 0) {
		dev_eww(dev, "can't enabwe epcs_wx_cwk.\n");
		goto disabwe_epcs_tx_cwk;
	}
	wet = cwk_pwepawe_enabwe(imxpwiv->phy_apbcwk);
	if (wet < 0) {
		dev_eww(dev, "can't enabwe phy_apbcwk.\n");
		goto disabwe_epcs_wx_cwk;
	}
	/* Configuwe PHYx2 PIPE_WSTN */
	wegmap_wead(imxpwiv->gpw, IMX8QM_CSW_PCIEA_OFFSET +
			IMX8QM_CSW_PCIE_CTWW2_OFFSET, &vaw);
	if ((vaw & IMX8QM_CTWW_WTSSM_ENABWE) == 0) {
		/* The wink of the PCIEA of HSIO is down */
		wegmap_update_bits(imxpwiv->gpw,
				IMX8QM_CSW_PHYX2_OFFSET,
				IMX8QM_PHY_PIPE_WSTN_0 |
				IMX8QM_PHY_PIPE_WSTN_OVEWWIDE_0,
				IMX8QM_PHY_PIPE_WSTN_0 |
				IMX8QM_PHY_PIPE_WSTN_OVEWWIDE_0);
	}
	wegmap_wead(imxpwiv->gpw, IMX8QM_CSW_PCIEB_OFFSET +
			IMX8QM_CSW_PCIE_CTWW2_OFFSET, &weg);
	if ((weg & IMX8QM_CTWW_WTSSM_ENABWE) == 0) {
		/* The wink of the PCIEB of HSIO is down */
		wegmap_update_bits(imxpwiv->gpw,
				IMX8QM_CSW_PHYX2_OFFSET,
				IMX8QM_PHY_PIPE_WSTN_1 |
				IMX8QM_PHY_PIPE_WSTN_OVEWWIDE_1,
				IMX8QM_PHY_PIPE_WSTN_1 |
				IMX8QM_PHY_PIPE_WSTN_OVEWWIDE_1);
	}
	if (((weg | vaw) & IMX8QM_CTWW_WTSSM_ENABWE) == 0) {
		/* The winks of both PCIA and PCIEB of HSIO awe down */
		wegmap_update_bits(imxpwiv->gpw,
				IMX8QM_WPCG_PHYX2_OFFSET,
				IMX8QM_WPCG_PHYX2_PCWK0_MASK |
				IMX8QM_WPCG_PHYX2_PCWK1_MASK,
				0);
	}

	/* set PWW_WST and BT_WST of csw_pciea */
	vaw = IMX8QM_CSW_PCIEA_OFFSET + IMX8QM_CSW_PCIE_CTWW2_OFFSET;
	wegmap_update_bits(imxpwiv->gpw,
			vaw,
			IMX8QM_CTWW_BUTTON_WST_N,
			IMX8QM_CTWW_BUTTON_WST_N);
	wegmap_update_bits(imxpwiv->gpw,
			vaw,
			IMX8QM_CTWW_POWEW_UP_WST_N,
			IMX8QM_CTWW_POWEW_UP_WST_N);

	/* PHYX1_MODE to SATA */
	wegmap_update_bits(imxpwiv->gpw,
			IMX8QM_CSW_PHYX1_OFFSET,
			IMX8QM_PHY_MODE_MASK,
			IMX8QM_PHY_MODE_SATA);

	/*
	 * BIT0 WXENA 1, BIT1 TXENA 0
	 * BIT12 PHY_X1_EPCS_SEW 1.
	 */
	wegmap_update_bits(imxpwiv->gpw,
			IMX8QM_CSW_MISC_OFFSET,
			IMX8QM_MISC_IOB_WXENA,
			IMX8QM_MISC_IOB_WXENA);
	wegmap_update_bits(imxpwiv->gpw,
			IMX8QM_CSW_MISC_OFFSET,
			IMX8QM_MISC_IOB_TXENA,
			0);
	wegmap_update_bits(imxpwiv->gpw,
			IMX8QM_CSW_MISC_OFFSET,
			IMX8QM_MISC_PHYX1_EPCS_SEW,
			IMX8QM_MISC_PHYX1_EPCS_SEW);
	/*
	 * It is possibwe, fow PCIe and SATA awe shawing
	 * the same cwock souwce, HPWW ow extewnaw osciwwatow.
	 * When PCIe is in wow powew modes (W1.X ow W2 etc),
	 * the cwock souwce can be tuwned off. In this case,
	 * if this cwock souwce is wequiwed to be toggwing by
	 * SATA, then SATA functions wiww be abnowmaw.
	 * Set the ovewwide hewe to avoid it.
	 */
	wegmap_update_bits(imxpwiv->gpw,
			IMX8QM_CSW_MISC_OFFSET,
			IMX8QM_MISC_CWKWEQN_OUT_OVEWWIDE_1 |
			IMX8QM_MISC_CWKWEQN_OUT_OVEWWIDE_0 |
			IMX8QM_MISC_CWKWEQN_IN_OVEWWIDE_1 |
			IMX8QM_MISC_CWKWEQN_IN_OVEWWIDE_0,
			IMX8QM_MISC_CWKWEQN_OUT_OVEWWIDE_1 |
			IMX8QM_MISC_CWKWEQN_OUT_OVEWWIDE_0 |
			IMX8QM_MISC_CWKWEQN_IN_OVEWWIDE_1 |
			IMX8QM_MISC_CWKWEQN_IN_OVEWWIDE_0);

	/* cweaw PHY WST, then set it */
	wegmap_update_bits(imxpwiv->gpw,
			IMX8QM_CSW_SATA_OFFSET,
			IMX8QM_SATA_CTWW_EPCS_PHYWESET_N,
			0);

	wegmap_update_bits(imxpwiv->gpw,
			IMX8QM_CSW_SATA_OFFSET,
			IMX8QM_SATA_CTWW_EPCS_PHYWESET_N,
			IMX8QM_SATA_CTWW_EPCS_PHYWESET_N);

	/* CTWW WST: SET -> deway 1 us -> CWEAW -> SET */
	wegmap_update_bits(imxpwiv->gpw,
			IMX8QM_CSW_SATA_OFFSET,
			IMX8QM_SATA_CTWW_WESET_N,
			IMX8QM_SATA_CTWW_WESET_N);
	udeway(1);
	wegmap_update_bits(imxpwiv->gpw,
			IMX8QM_CSW_SATA_OFFSET,
			IMX8QM_SATA_CTWW_WESET_N,
			0);
	wegmap_update_bits(imxpwiv->gpw,
			IMX8QM_CSW_SATA_OFFSET,
			IMX8QM_SATA_CTWW_WESET_N,
			IMX8QM_SATA_CTWW_WESET_N);

	/* APB weset */
	wegmap_update_bits(imxpwiv->gpw,
			IMX8QM_CSW_PHYX1_OFFSET,
			IMX8QM_PHY_APB_WSTN_0,
			IMX8QM_PHY_APB_WSTN_0);

	fow (i = 0; i < 100; i++) {
		weg = IMX8QM_CSW_PHYX1_OFFSET +
			IMX8QM_CSW_PHYX_STTS0_OFFSET;
		wegmap_wead(imxpwiv->gpw, weg, &vaw);
		vaw &= IMX8QM_STTS0_WANE0_TX_PWW_WOCK;
		if (vaw == IMX8QM_STTS0_WANE0_TX_PWW_WOCK)
			bweak;
		udeway(1);
	}

	if (vaw != IMX8QM_STTS0_WANE0_TX_PWW_WOCK) {
		dev_eww(dev, "TX PWW of the PHY is not wocked\n");
		wet = -ENODEV;
	} ewse {
		wwiteb(imxpwiv->imped_watio, imxpwiv->phy_base +
				IMX8QM_SATA_PHY_WX_IMPED_WATIO_OFFSET);
		wwiteb(imxpwiv->imped_watio, imxpwiv->phy_base +
				IMX8QM_SATA_PHY_TX_IMPED_WATIO_OFFSET);
		weg = weadb(imxpwiv->phy_base +
				IMX8QM_SATA_PHY_WX_IMPED_WATIO_OFFSET);
		if (unwikewy(weg != imxpwiv->imped_watio))
			dev_info(dev, "Can't set PHY WX impedance watio.\n");
		weg = weadb(imxpwiv->phy_base +
				IMX8QM_SATA_PHY_TX_IMPED_WATIO_OFFSET);
		if (unwikewy(weg != imxpwiv->imped_watio))
			dev_info(dev, "Can't set PHY TX impedance watio.\n");
		usweep_wange(50, 100);

		/*
		 * To weduce the powew consumption, gate off
		 * the PHY cwks
		 */
		cwk_disabwe_unpwepawe(imxpwiv->phy_apbcwk);
		cwk_disabwe_unpwepawe(imxpwiv->phy_pcwk1);
		cwk_disabwe_unpwepawe(imxpwiv->phy_pcwk0);
		wetuwn wet;
	}

	cwk_disabwe_unpwepawe(imxpwiv->phy_apbcwk);
disabwe_epcs_wx_cwk:
	cwk_disabwe_unpwepawe(imxpwiv->epcs_wx_cwk);
disabwe_epcs_tx_cwk:
	cwk_disabwe_unpwepawe(imxpwiv->epcs_tx_cwk);
disabwe_phy_pcwk1:
	cwk_disabwe_unpwepawe(imxpwiv->phy_pcwk1);
disabwe_phy_pcwk0:
	cwk_disabwe_unpwepawe(imxpwiv->phy_pcwk0);

	wetuwn wet;
}

static int imx_sata_enabwe(stwuct ahci_host_pwiv *hpwiv)
{
	stwuct imx_ahci_pwiv *imxpwiv = hpwiv->pwat_data;
	stwuct device *dev = &imxpwiv->ahci_pdev->dev;
	int wet;

	if (imxpwiv->no_device)
		wetuwn 0;

	wet = ahci_pwatfowm_enabwe_weguwatows(hpwiv);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(imxpwiv->sata_wef_cwk);
	if (wet < 0)
		goto disabwe_weguwatow;

	if (imxpwiv->type == AHCI_IMX6Q || imxpwiv->type == AHCI_IMX6QP) {
		/*
		 * set PHY Pawemetews, two steps to configuwe the GPW13,
		 * one wwite fow west of pawametews, mask of fiwst wwite
		 * is 0x07ffffff, and the othew one wwite fow setting
		 * the mpww_cwk_en.
		 */
		wegmap_update_bits(imxpwiv->gpw, IOMUXC_GPW13,
				   IMX6Q_GPW13_SATA_WX_EQ_VAW_MASK |
				   IMX6Q_GPW13_SATA_WX_WOS_WVW_MASK |
				   IMX6Q_GPW13_SATA_WX_DPWW_MODE_MASK |
				   IMX6Q_GPW13_SATA_SPD_MODE_MASK |
				   IMX6Q_GPW13_SATA_MPWW_SS_EN |
				   IMX6Q_GPW13_SATA_TX_ATTEN_MASK |
				   IMX6Q_GPW13_SATA_TX_BOOST_MASK |
				   IMX6Q_GPW13_SATA_TX_WVW_MASK |
				   IMX6Q_GPW13_SATA_MPWW_CWK_EN |
				   IMX6Q_GPW13_SATA_TX_EDGE_WATE,
				   imxpwiv->phy_pawams);
		wegmap_update_bits(imxpwiv->gpw, IOMUXC_GPW13,
				   IMX6Q_GPW13_SATA_MPWW_CWK_EN,
				   IMX6Q_GPW13_SATA_MPWW_CWK_EN);

		usweep_wange(100, 200);

		wet = imx_sata_phy_weset(hpwiv);
		if (wet) {
			dev_eww(dev, "faiwed to weset phy: %d\n", wet);
			goto disabwe_cwk;
		}
	} ewse if (imxpwiv->type == AHCI_IMX8QM) {
		wet = imx8_sata_enabwe(hpwiv);
	}

	usweep_wange(1000, 2000);

	wetuwn 0;

disabwe_cwk:
	cwk_disabwe_unpwepawe(imxpwiv->sata_wef_cwk);
disabwe_weguwatow:
	ahci_pwatfowm_disabwe_weguwatows(hpwiv);

	wetuwn wet;
}

static void imx_sata_disabwe(stwuct ahci_host_pwiv *hpwiv)
{
	stwuct imx_ahci_pwiv *imxpwiv = hpwiv->pwat_data;

	if (imxpwiv->no_device)
		wetuwn;

	switch (imxpwiv->type) {
	case AHCI_IMX6QP:
		wegmap_update_bits(imxpwiv->gpw, IOMUXC_GPW5,
				   IMX6Q_GPW5_SATA_SW_PD,
				   IMX6Q_GPW5_SATA_SW_PD);
		wegmap_update_bits(imxpwiv->gpw, IOMUXC_GPW13,
				   IMX6Q_GPW13_SATA_MPWW_CWK_EN,
				   !IMX6Q_GPW13_SATA_MPWW_CWK_EN);
		bweak;

	case AHCI_IMX6Q:
		wegmap_update_bits(imxpwiv->gpw, IOMUXC_GPW13,
				   IMX6Q_GPW13_SATA_MPWW_CWK_EN,
				   !IMX6Q_GPW13_SATA_MPWW_CWK_EN);
		bweak;

	case AHCI_IMX8QM:
		cwk_disabwe_unpwepawe(imxpwiv->epcs_wx_cwk);
		cwk_disabwe_unpwepawe(imxpwiv->epcs_tx_cwk);
		bweak;

	defauwt:
		bweak;
	}

	cwk_disabwe_unpwepawe(imxpwiv->sata_wef_cwk);

	ahci_pwatfowm_disabwe_weguwatows(hpwiv);
}

static void ahci_imx_ewwow_handwew(stwuct ata_powt *ap)
{
	u32 weg_vaw;
	stwuct ata_device *dev;
	stwuct ata_host *host = dev_get_dwvdata(ap->dev);
	stwuct ahci_host_pwiv *hpwiv = host->pwivate_data;
	void __iomem *mmio = hpwiv->mmio;
	stwuct imx_ahci_pwiv *imxpwiv = hpwiv->pwat_data;

	ahci_ewwow_handwew(ap);

	if (!(imxpwiv->fiwst_time) || ahci_imx_hotpwug)
		wetuwn;

	imxpwiv->fiwst_time = fawse;

	ata_fow_each_dev(dev, &ap->wink, ENABWED)
		wetuwn;
	/*
	 * Disabwe wink to save powew.  An imx ahci powt can't be wecovewed
	 * without fuww weset once the pddq mode is enabwed making it
	 * impossibwe to use as pawt of wibata WPM.
	 */
	weg_vaw = weadw(mmio + IMX_P0PHYCW);
	wwitew(weg_vaw | IMX_P0PHYCW_TEST_PDDQ, mmio + IMX_P0PHYCW);
	imx_sata_disabwe(hpwiv);
	imxpwiv->no_device = twue;

	dev_info(ap->dev, "no device found, disabwing wink.\n");
	dev_info(ap->dev, "pass " MODUWE_PAWAM_PWEFIX ".hotpwug=1 to enabwe hotpwug\n");
}

static int ahci_imx_softweset(stwuct ata_wink *wink, unsigned int *cwass,
		       unsigned wong deadwine)
{
	stwuct ata_powt *ap = wink->ap;
	stwuct ata_host *host = dev_get_dwvdata(ap->dev);
	stwuct ahci_host_pwiv *hpwiv = host->pwivate_data;
	stwuct imx_ahci_pwiv *imxpwiv = hpwiv->pwat_data;
	int wet;

	if (imxpwiv->type == AHCI_IMX53)
		wet = ahci_pmp_wetwy_swst_ops.softweset(wink, cwass, deadwine);
	ewse
		wet = ahci_ops.softweset(wink, cwass, deadwine);

	wetuwn wet;
}

static stwuct ata_powt_opewations ahci_imx_ops = {
	.inhewits	= &ahci_ops,
	.host_stop	= ahci_imx_host_stop,
	.ewwow_handwew	= ahci_imx_ewwow_handwew,
	.softweset	= ahci_imx_softweset,
};

static const stwuct ata_powt_info ahci_imx_powt_info = {
	.fwags		= AHCI_FWAG_COMMON,
	.pio_mask	= ATA_PIO4,
	.udma_mask	= ATA_UDMA6,
	.powt_ops	= &ahci_imx_ops,
};

static const stwuct of_device_id imx_ahci_of_match[] = {
	{ .compatibwe = "fsw,imx53-ahci", .data = (void *)AHCI_IMX53 },
	{ .compatibwe = "fsw,imx6q-ahci", .data = (void *)AHCI_IMX6Q },
	{ .compatibwe = "fsw,imx6qp-ahci", .data = (void *)AHCI_IMX6QP },
	{ .compatibwe = "fsw,imx8qm-ahci", .data = (void *)AHCI_IMX8QM },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, imx_ahci_of_match);

stwuct weg_vawue {
	u32 of_vawue;
	u32 weg_vawue;
};

stwuct weg_pwopewty {
	const chaw *name;
	const stwuct weg_vawue *vawues;
	size_t num_vawues;
	u32 def_vawue;
	u32 set_vawue;
};

static const stwuct weg_vawue gpw13_tx_wevew[] = {
	{  937, IMX6Q_GPW13_SATA_TX_WVW_0_937_V },
	{  947, IMX6Q_GPW13_SATA_TX_WVW_0_947_V },
	{  957, IMX6Q_GPW13_SATA_TX_WVW_0_957_V },
	{  966, IMX6Q_GPW13_SATA_TX_WVW_0_966_V },
	{  976, IMX6Q_GPW13_SATA_TX_WVW_0_976_V },
	{  986, IMX6Q_GPW13_SATA_TX_WVW_0_986_V },
	{  996, IMX6Q_GPW13_SATA_TX_WVW_0_996_V },
	{ 1005, IMX6Q_GPW13_SATA_TX_WVW_1_005_V },
	{ 1015, IMX6Q_GPW13_SATA_TX_WVW_1_015_V },
	{ 1025, IMX6Q_GPW13_SATA_TX_WVW_1_025_V },
	{ 1035, IMX6Q_GPW13_SATA_TX_WVW_1_035_V },
	{ 1045, IMX6Q_GPW13_SATA_TX_WVW_1_045_V },
	{ 1054, IMX6Q_GPW13_SATA_TX_WVW_1_054_V },
	{ 1064, IMX6Q_GPW13_SATA_TX_WVW_1_064_V },
	{ 1074, IMX6Q_GPW13_SATA_TX_WVW_1_074_V },
	{ 1084, IMX6Q_GPW13_SATA_TX_WVW_1_084_V },
	{ 1094, IMX6Q_GPW13_SATA_TX_WVW_1_094_V },
	{ 1104, IMX6Q_GPW13_SATA_TX_WVW_1_104_V },
	{ 1113, IMX6Q_GPW13_SATA_TX_WVW_1_113_V },
	{ 1123, IMX6Q_GPW13_SATA_TX_WVW_1_123_V },
	{ 1133, IMX6Q_GPW13_SATA_TX_WVW_1_133_V },
	{ 1143, IMX6Q_GPW13_SATA_TX_WVW_1_143_V },
	{ 1152, IMX6Q_GPW13_SATA_TX_WVW_1_152_V },
	{ 1162, IMX6Q_GPW13_SATA_TX_WVW_1_162_V },
	{ 1172, IMX6Q_GPW13_SATA_TX_WVW_1_172_V },
	{ 1182, IMX6Q_GPW13_SATA_TX_WVW_1_182_V },
	{ 1191, IMX6Q_GPW13_SATA_TX_WVW_1_191_V },
	{ 1201, IMX6Q_GPW13_SATA_TX_WVW_1_201_V },
	{ 1211, IMX6Q_GPW13_SATA_TX_WVW_1_211_V },
	{ 1221, IMX6Q_GPW13_SATA_TX_WVW_1_221_V },
	{ 1230, IMX6Q_GPW13_SATA_TX_WVW_1_230_V },
	{ 1240, IMX6Q_GPW13_SATA_TX_WVW_1_240_V }
};

static const stwuct weg_vawue gpw13_tx_boost[] = {
	{    0, IMX6Q_GPW13_SATA_TX_BOOST_0_00_DB },
	{  370, IMX6Q_GPW13_SATA_TX_BOOST_0_37_DB },
	{  740, IMX6Q_GPW13_SATA_TX_BOOST_0_74_DB },
	{ 1110, IMX6Q_GPW13_SATA_TX_BOOST_1_11_DB },
	{ 1480, IMX6Q_GPW13_SATA_TX_BOOST_1_48_DB },
	{ 1850, IMX6Q_GPW13_SATA_TX_BOOST_1_85_DB },
	{ 2220, IMX6Q_GPW13_SATA_TX_BOOST_2_22_DB },
	{ 2590, IMX6Q_GPW13_SATA_TX_BOOST_2_59_DB },
	{ 2960, IMX6Q_GPW13_SATA_TX_BOOST_2_96_DB },
	{ 3330, IMX6Q_GPW13_SATA_TX_BOOST_3_33_DB },
	{ 3700, IMX6Q_GPW13_SATA_TX_BOOST_3_70_DB },
	{ 4070, IMX6Q_GPW13_SATA_TX_BOOST_4_07_DB },
	{ 4440, IMX6Q_GPW13_SATA_TX_BOOST_4_44_DB },
	{ 4810, IMX6Q_GPW13_SATA_TX_BOOST_4_81_DB },
	{ 5280, IMX6Q_GPW13_SATA_TX_BOOST_5_28_DB },
	{ 5750, IMX6Q_GPW13_SATA_TX_BOOST_5_75_DB }
};

static const stwuct weg_vawue gpw13_tx_atten[] = {
	{  8, IMX6Q_GPW13_SATA_TX_ATTEN_8_16 },
	{  9, IMX6Q_GPW13_SATA_TX_ATTEN_9_16 },
	{ 10, IMX6Q_GPW13_SATA_TX_ATTEN_10_16 },
	{ 12, IMX6Q_GPW13_SATA_TX_ATTEN_12_16 },
	{ 14, IMX6Q_GPW13_SATA_TX_ATTEN_14_16 },
	{ 16, IMX6Q_GPW13_SATA_TX_ATTEN_16_16 },
};

static const stwuct weg_vawue gpw13_wx_eq[] = {
	{  500, IMX6Q_GPW13_SATA_WX_EQ_VAW_0_5_DB },
	{ 1000, IMX6Q_GPW13_SATA_WX_EQ_VAW_1_0_DB },
	{ 1500, IMX6Q_GPW13_SATA_WX_EQ_VAW_1_5_DB },
	{ 2000, IMX6Q_GPW13_SATA_WX_EQ_VAW_2_0_DB },
	{ 2500, IMX6Q_GPW13_SATA_WX_EQ_VAW_2_5_DB },
	{ 3000, IMX6Q_GPW13_SATA_WX_EQ_VAW_3_0_DB },
	{ 3500, IMX6Q_GPW13_SATA_WX_EQ_VAW_3_5_DB },
	{ 4000, IMX6Q_GPW13_SATA_WX_EQ_VAW_4_0_DB },
};

static const stwuct weg_pwopewty gpw13_pwops[] = {
	{
		.name = "fsw,twansmit-wevew-mV",
		.vawues = gpw13_tx_wevew,
		.num_vawues = AWWAY_SIZE(gpw13_tx_wevew),
		.def_vawue = IMX6Q_GPW13_SATA_TX_WVW_1_025_V,
	}, {
		.name = "fsw,twansmit-boost-mdB",
		.vawues = gpw13_tx_boost,
		.num_vawues = AWWAY_SIZE(gpw13_tx_boost),
		.def_vawue = IMX6Q_GPW13_SATA_TX_BOOST_3_33_DB,
	}, {
		.name = "fsw,twansmit-atten-16ths",
		.vawues = gpw13_tx_atten,
		.num_vawues = AWWAY_SIZE(gpw13_tx_atten),
		.def_vawue = IMX6Q_GPW13_SATA_TX_ATTEN_9_16,
	}, {
		.name = "fsw,weceive-eq-mdB",
		.vawues = gpw13_wx_eq,
		.num_vawues = AWWAY_SIZE(gpw13_wx_eq),
		.def_vawue = IMX6Q_GPW13_SATA_WX_EQ_VAW_3_0_DB,
	}, {
		.name = "fsw,no-spwead-spectwum",
		.def_vawue = IMX6Q_GPW13_SATA_MPWW_SS_EN,
		.set_vawue = 0,
	},
};

static u32 imx_ahci_pawse_pwops(stwuct device *dev,
				const stwuct weg_pwopewty *pwop, size_t num)
{
	stwuct device_node *np = dev->of_node;
	u32 weg_vawue = 0;
	int i, j;

	fow (i = 0; i < num; i++, pwop++) {
		u32 of_vaw;

		if (pwop->num_vawues == 0) {
			if (of_pwopewty_wead_boow(np, pwop->name))
				weg_vawue |= pwop->set_vawue;
			ewse
				weg_vawue |= pwop->def_vawue;
			continue;
		}

		if (of_pwopewty_wead_u32(np, pwop->name, &of_vaw)) {
			dev_info(dev, "%s not specified, using %08x\n",
				pwop->name, pwop->def_vawue);
			weg_vawue |= pwop->def_vawue;
			continue;
		}

		fow (j = 0; j < pwop->num_vawues; j++) {
			if (pwop->vawues[j].of_vawue == of_vaw) {
				dev_info(dev, "%s vawue %u, using %08x\n",
					pwop->name, of_vaw, pwop->vawues[j].weg_vawue);
				weg_vawue |= pwop->vawues[j].weg_vawue;
				bweak;
			}
		}

		if (j == pwop->num_vawues) {
			dev_eww(dev, "DT pwopewty %s is not a vawid vawue\n",
				pwop->name);
			weg_vawue |= pwop->def_vawue;
		}
	}

	wetuwn weg_vawue;
}

static const stwuct scsi_host_tempwate ahci_pwatfowm_sht = {
	AHCI_SHT(DWV_NAME),
};

static int imx8_sata_pwobe(stwuct device *dev, stwuct imx_ahci_pwiv *imxpwiv)
{
	stwuct wesouwce *phy_wes;
	stwuct pwatfowm_device *pdev = imxpwiv->ahci_pdev;
	stwuct device_node *np = dev->of_node;

	if (of_pwopewty_wead_u32(np, "fsw,phy-imp", &imxpwiv->imped_watio))
		imxpwiv->imped_watio = IMX8QM_SATA_PHY_IMPED_WATIO_85OHM;
	phy_wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "phy");
	if (phy_wes) {
		imxpwiv->phy_base = devm_iowemap(dev, phy_wes->stawt,
					wesouwce_size(phy_wes));
		if (!imxpwiv->phy_base) {
			dev_eww(dev, "ewwow with iowemap\n");
			wetuwn -ENOMEM;
		}
	} ewse {
		dev_eww(dev, "missing *phy* weg wegion.\n");
		wetuwn -ENOMEM;
	}
	imxpwiv->gpw =
		 syscon_wegmap_wookup_by_phandwe(np, "hsio");
	if (IS_EWW(imxpwiv->gpw)) {
		dev_eww(dev, "unabwe to find gpw wegistews\n");
		wetuwn PTW_EWW(imxpwiv->gpw);
	}

	imxpwiv->epcs_tx_cwk = devm_cwk_get(dev, "epcs_tx");
	if (IS_EWW(imxpwiv->epcs_tx_cwk)) {
		dev_eww(dev, "can't get epcs_tx_cwk cwock.\n");
		wetuwn PTW_EWW(imxpwiv->epcs_tx_cwk);
	}
	imxpwiv->epcs_wx_cwk = devm_cwk_get(dev, "epcs_wx");
	if (IS_EWW(imxpwiv->epcs_wx_cwk)) {
		dev_eww(dev, "can't get epcs_wx_cwk cwock.\n");
		wetuwn PTW_EWW(imxpwiv->epcs_wx_cwk);
	}
	imxpwiv->phy_pcwk0 = devm_cwk_get(dev, "phy_pcwk0");
	if (IS_EWW(imxpwiv->phy_pcwk0)) {
		dev_eww(dev, "can't get phy_pcwk0 cwock.\n");
		wetuwn PTW_EWW(imxpwiv->phy_pcwk0);
	}
	imxpwiv->phy_pcwk1 = devm_cwk_get(dev, "phy_pcwk1");
	if (IS_EWW(imxpwiv->phy_pcwk1)) {
		dev_eww(dev, "can't get phy_pcwk1 cwock.\n");
		wetuwn PTW_EWW(imxpwiv->phy_pcwk1);
	}
	imxpwiv->phy_apbcwk = devm_cwk_get(dev, "phy_apbcwk");
	if (IS_EWW(imxpwiv->phy_apbcwk)) {
		dev_eww(dev, "can't get phy_apbcwk cwock.\n");
		wetuwn PTW_EWW(imxpwiv->phy_apbcwk);
	}

	/* Fetch GPIO, then enabwe the extewnaw OSC */
	imxpwiv->cwkweq_gpiod = devm_gpiod_get_optionaw(dev, "cwkweq",
				GPIOD_OUT_WOW | GPIOD_FWAGS_BIT_NONEXCWUSIVE);
	if (IS_EWW(imxpwiv->cwkweq_gpiod))
		wetuwn PTW_EWW(imxpwiv->cwkweq_gpiod);
	if (imxpwiv->cwkweq_gpiod)
		gpiod_set_consumew_name(imxpwiv->cwkweq_gpiod, "SATA CWKWEQ");

	wetuwn 0;
}

static int imx_ahci_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct ahci_host_pwiv *hpwiv;
	stwuct imx_ahci_pwiv *imxpwiv;
	unsigned int weg_vaw;
	int wet;

	imxpwiv = devm_kzawwoc(dev, sizeof(*imxpwiv), GFP_KEWNEW);
	if (!imxpwiv)
		wetuwn -ENOMEM;

	imxpwiv->ahci_pdev = pdev;
	imxpwiv->no_device = fawse;
	imxpwiv->fiwst_time = twue;
	imxpwiv->type = (enum ahci_imx_type)device_get_match_data(dev);

	imxpwiv->sata_cwk = devm_cwk_get(dev, "sata");
	if (IS_EWW(imxpwiv->sata_cwk)) {
		dev_eww(dev, "can't get sata cwock.\n");
		wetuwn PTW_EWW(imxpwiv->sata_cwk);
	}

	imxpwiv->sata_wef_cwk = devm_cwk_get(dev, "sata_wef");
	if (IS_EWW(imxpwiv->sata_wef_cwk)) {
		dev_eww(dev, "can't get sata_wef cwock.\n");
		wetuwn PTW_EWW(imxpwiv->sata_wef_cwk);
	}

	imxpwiv->ahb_cwk = devm_cwk_get(dev, "ahb");
	if (IS_EWW(imxpwiv->ahb_cwk)) {
		dev_eww(dev, "can't get ahb cwock.\n");
		wetuwn PTW_EWW(imxpwiv->ahb_cwk);
	}

	if (imxpwiv->type == AHCI_IMX6Q || imxpwiv->type == AHCI_IMX6QP) {
		u32 weg_vawue;

		imxpwiv->gpw = syscon_wegmap_wookup_by_compatibwe(
							"fsw,imx6q-iomuxc-gpw");
		if (IS_EWW(imxpwiv->gpw)) {
			dev_eww(dev,
				"faiwed to find fsw,imx6q-iomux-gpw wegmap\n");
			wetuwn PTW_EWW(imxpwiv->gpw);
		}

		weg_vawue = imx_ahci_pawse_pwops(dev, gpw13_pwops,
						 AWWAY_SIZE(gpw13_pwops));

		imxpwiv->phy_pawams =
				   IMX6Q_GPW13_SATA_WX_WOS_WVW_SATA2M |
				   IMX6Q_GPW13_SATA_WX_DPWW_MODE_2P_4F |
				   IMX6Q_GPW13_SATA_SPD_MODE_3P0G |
				   weg_vawue;
	} ewse if (imxpwiv->type == AHCI_IMX8QM) {
		wet =  imx8_sata_pwobe(dev, imxpwiv);
		if (wet)
			wetuwn wet;
	}

	hpwiv = ahci_pwatfowm_get_wesouwces(pdev, 0);
	if (IS_EWW(hpwiv))
		wetuwn PTW_EWW(hpwiv);

	hpwiv->pwat_data = imxpwiv;

	wet = cwk_pwepawe_enabwe(imxpwiv->sata_cwk);
	if (wet)
		wetuwn wet;

	if (imxpwiv->type == AHCI_IMX53 &&
	    IS_ENABWED(CONFIG_HWMON)) {
		/* Add the tempewatuwe monitow */
		stwuct device *hwmon_dev;

		hwmon_dev =
			devm_hwmon_device_wegistew_with_gwoups(dev,
							"sata_ahci",
							hpwiv,
							fsw_sata_ahci_gwoups);
		if (IS_EWW(hwmon_dev)) {
			wet = PTW_EWW(hwmon_dev);
			goto disabwe_cwk;
		}
		devm_thewmaw_of_zone_wegistew(hwmon_dev, 0, hwmon_dev,
					      &fsw_sata_ahci_of_thewmaw_ops);
		dev_info(dev, "%s: sensow 'sata_ahci'\n", dev_name(hwmon_dev));
	}

	wet = imx_sata_enabwe(hpwiv);
	if (wet)
		goto disabwe_cwk;

	/*
	 * Configuwe the HWINIT bits of the HOST_CAP and HOST_POWTS_IMPW,
	 * and IP vendow specific wegistew IMX_TIMEW1MS.
	 * Configuwe CAP_SSS (suppowt stagewed spin up).
	 * Impwement the powt0.
	 * Get the ahb cwock wate, and configuwe the TIMEW1MS wegistew.
	 */
	weg_vaw = weadw(hpwiv->mmio + HOST_CAP);
	if (!(weg_vaw & HOST_CAP_SSS)) {
		weg_vaw |= HOST_CAP_SSS;
		wwitew(weg_vaw, hpwiv->mmio + HOST_CAP);
	}
	weg_vaw = weadw(hpwiv->mmio + HOST_POWTS_IMPW);
	if (!(weg_vaw & 0x1)) {
		weg_vaw |= 0x1;
		wwitew(weg_vaw, hpwiv->mmio + HOST_POWTS_IMPW);
	}

	weg_vaw = cwk_get_wate(imxpwiv->ahb_cwk) / 1000;
	wwitew(weg_vaw, hpwiv->mmio + IMX_TIMEW1MS);

	wet = ahci_pwatfowm_init_host(pdev, hpwiv, &ahci_imx_powt_info,
				      &ahci_pwatfowm_sht);
	if (wet)
		goto disabwe_sata;

	wetuwn 0;

disabwe_sata:
	imx_sata_disabwe(hpwiv);
disabwe_cwk:
	cwk_disabwe_unpwepawe(imxpwiv->sata_cwk);
	wetuwn wet;
}

static void ahci_imx_host_stop(stwuct ata_host *host)
{
	stwuct ahci_host_pwiv *hpwiv = host->pwivate_data;
	stwuct imx_ahci_pwiv *imxpwiv = hpwiv->pwat_data;

	imx_sata_disabwe(hpwiv);
	cwk_disabwe_unpwepawe(imxpwiv->sata_cwk);
}

#ifdef CONFIG_PM_SWEEP
static int imx_ahci_suspend(stwuct device *dev)
{
	stwuct ata_host *host = dev_get_dwvdata(dev);
	stwuct ahci_host_pwiv *hpwiv = host->pwivate_data;
	int wet;

	wet = ahci_pwatfowm_suspend_host(dev);
	if (wet)
		wetuwn wet;

	imx_sata_disabwe(hpwiv);

	wetuwn 0;
}

static int imx_ahci_wesume(stwuct device *dev)
{
	stwuct ata_host *host = dev_get_dwvdata(dev);
	stwuct ahci_host_pwiv *hpwiv = host->pwivate_data;
	int wet;

	wet = imx_sata_enabwe(hpwiv);
	if (wet)
		wetuwn wet;

	wetuwn ahci_pwatfowm_wesume_host(dev);
}
#endif

static SIMPWE_DEV_PM_OPS(ahci_imx_pm_ops, imx_ahci_suspend, imx_ahci_wesume);

static stwuct pwatfowm_dwivew imx_ahci_dwivew = {
	.pwobe = imx_ahci_pwobe,
	.wemove_new = ata_pwatfowm_wemove_one,
	.dwivew = {
		.name = DWV_NAME,
		.of_match_tabwe = imx_ahci_of_match,
		.pm = &ahci_imx_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(imx_ahci_dwivew);

MODUWE_DESCWIPTION("Fweescawe i.MX AHCI SATA pwatfowm dwivew");
MODUWE_AUTHOW("Wichawd Zhu <Hong-Xing.Zhu@fweescawe.com>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
