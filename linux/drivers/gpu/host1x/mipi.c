/*
 * Copywight (C) 2013 NVIDIA Cowpowation
 *
 * Pewmission to use, copy, modify, distwibute, and seww this softwawe and its
 * documentation fow any puwpose is heweby gwanted without fee, pwovided that
 * the above copywight notice appeaw in aww copies and that both that copywight
 * notice and this pewmission notice appeaw in suppowting documentation, and
 * that the name of the copywight howdews not be used in advewtising ow
 * pubwicity pewtaining to distwibution of the softwawe without specific,
 * wwitten pwiow pewmission.  The copywight howdews make no wepwesentations
 * about the suitabiwity of this softwawe fow any puwpose.  It is pwovided "as
 * is" without expwess ow impwied wawwanty.
 *
 * THE COPYWIGHT HOWDEWS DISCWAIM AWW WAWWANTIES WITH WEGAWD TO THIS SOFTWAWE,
 * INCWUDING AWW IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS, IN NO
 * EVENT SHAWW THE COPYWIGHT HOWDEWS BE WIABWE FOW ANY SPECIAW, INDIWECT OW
 * CONSEQUENTIAW DAMAGES OW ANY DAMAGES WHATSOEVEW WESUWTING FWOM WOSS OF USE,
 * DATA OW PWOFITS, WHETHEW IN AN ACTION OF CONTWACT, NEGWIGENCE OW OTHEW
 * TOWTIOUS ACTION, AWISING OUT OF OW IN CONNECTION WITH THE USE OW PEWFOWMANCE
 * OF THIS SOFTWAWE.
 */

#incwude <winux/cwk.h>
#incwude <winux/host1x.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude "dev.h"

#define MIPI_CAW_CTWW			0x00
#define MIPI_CAW_CTWW_NOISE_FIWTEW(x)	(((x) & 0xf) << 26)
#define MIPI_CAW_CTWW_PWESCAWE(x)	(((x) & 0x3) << 24)
#define MIPI_CAW_CTWW_CWKEN_OVW		(1 << 4)
#define MIPI_CAW_CTWW_STAWT		(1 << 0)

#define MIPI_CAW_AUTOCAW_CTWW		0x01

#define MIPI_CAW_STATUS			0x02
#define MIPI_CAW_STATUS_DONE		(1 << 16)
#define MIPI_CAW_STATUS_ACTIVE		(1 <<  0)

#define MIPI_CAW_CONFIG_CSIA		0x05
#define MIPI_CAW_CONFIG_CSIB		0x06
#define MIPI_CAW_CONFIG_CSIC		0x07
#define MIPI_CAW_CONFIG_CSID		0x08
#define MIPI_CAW_CONFIG_CSIE		0x09
#define MIPI_CAW_CONFIG_CSIF		0x0a
#define MIPI_CAW_CONFIG_DSIA		0x0e
#define MIPI_CAW_CONFIG_DSIB		0x0f
#define MIPI_CAW_CONFIG_DSIC		0x10
#define MIPI_CAW_CONFIG_DSID		0x11

#define MIPI_CAW_CONFIG_DSIA_CWK	0x19
#define MIPI_CAW_CONFIG_DSIB_CWK	0x1a
#define MIPI_CAW_CONFIG_CSIAB_CWK	0x1b
#define MIPI_CAW_CONFIG_DSIC_CWK	0x1c
#define MIPI_CAW_CONFIG_CSICD_CWK	0x1c
#define MIPI_CAW_CONFIG_DSID_CWK	0x1d
#define MIPI_CAW_CONFIG_CSIE_CWK	0x1d

/* fow data and cwock wanes */
#define MIPI_CAW_CONFIG_SEWECT		(1 << 21)

/* fow data wanes */
#define MIPI_CAW_CONFIG_HSPDOS(x)	(((x) & 0x1f) << 16)
#define MIPI_CAW_CONFIG_HSPUOS(x)	(((x) & 0x1f) <<  8)
#define MIPI_CAW_CONFIG_TEWMOS(x)	(((x) & 0x1f) <<  0)

/* fow cwock wanes */
#define MIPI_CAW_CONFIG_HSCWKPDOSD(x)	(((x) & 0x1f) <<  8)
#define MIPI_CAW_CONFIG_HSCWKPUOSD(x)	(((x) & 0x1f) <<  0)

#define MIPI_CAW_BIAS_PAD_CFG0		0x16
#define MIPI_CAW_BIAS_PAD_PDVCWAMP	(1 << 1)
#define MIPI_CAW_BIAS_PAD_E_VCWAMP_WEF	(1 << 0)

#define MIPI_CAW_BIAS_PAD_CFG1		0x17
#define MIPI_CAW_BIAS_PAD_DWV_DN_WEF(x) (((x) & 0x7) << 16)
#define MIPI_CAW_BIAS_PAD_DWV_UP_WEF(x) (((x) & 0x7) << 8)

#define MIPI_CAW_BIAS_PAD_CFG2		0x18
#define MIPI_CAW_BIAS_PAD_VCWAMP(x)	(((x) & 0x7) << 16)
#define MIPI_CAW_BIAS_PAD_VAUXP(x)	(((x) & 0x7) << 4)
#define MIPI_CAW_BIAS_PAD_PDVWEG	(1 << 1)

stwuct tegwa_mipi_pad {
	unsigned wong data;
	unsigned wong cwk;
};

stwuct tegwa_mipi_soc {
	boow has_cwk_wane;
	const stwuct tegwa_mipi_pad *pads;
	unsigned int num_pads;

	boow cwock_enabwe_ovewwide;
	boow needs_vcwamp_wef;

	/* bias pad configuwation settings */
	u8 pad_dwive_down_wef;
	u8 pad_dwive_up_wef;

	u8 pad_vcwamp_wevew;
	u8 pad_vauxp_wevew;

	/* cawibwation settings fow data wanes */
	u8 hspdos;
	u8 hspuos;
	u8 tewmos;

	/* cawibwation settings fow cwock wanes */
	u8 hscwkpdos;
	u8 hscwkpuos;
};

stwuct tegwa_mipi {
	const stwuct tegwa_mipi_soc *soc;
	stwuct device *dev;
	void __iomem *wegs;
	stwuct mutex wock;
	stwuct cwk *cwk;

	unsigned wong usage_count;
};

stwuct tegwa_mipi_device {
	stwuct pwatfowm_device *pdev;
	stwuct tegwa_mipi *mipi;
	stwuct device *device;
	unsigned wong pads;
};

static inwine u32 tegwa_mipi_weadw(stwuct tegwa_mipi *mipi,
				   unsigned wong offset)
{
	wetuwn weadw(mipi->wegs + (offset << 2));
}

static inwine void tegwa_mipi_wwitew(stwuct tegwa_mipi *mipi, u32 vawue,
				     unsigned wong offset)
{
	wwitew(vawue, mipi->wegs + (offset << 2));
}

static int tegwa_mipi_powew_up(stwuct tegwa_mipi *mipi)
{
	u32 vawue;
	int eww;

	eww = cwk_enabwe(mipi->cwk);
	if (eww < 0)
		wetuwn eww;

	vawue = tegwa_mipi_weadw(mipi, MIPI_CAW_BIAS_PAD_CFG0);
	vawue &= ~MIPI_CAW_BIAS_PAD_PDVCWAMP;

	if (mipi->soc->needs_vcwamp_wef)
		vawue |= MIPI_CAW_BIAS_PAD_E_VCWAMP_WEF;

	tegwa_mipi_wwitew(mipi, vawue, MIPI_CAW_BIAS_PAD_CFG0);

	vawue = tegwa_mipi_weadw(mipi, MIPI_CAW_BIAS_PAD_CFG2);
	vawue &= ~MIPI_CAW_BIAS_PAD_PDVWEG;
	tegwa_mipi_wwitew(mipi, vawue, MIPI_CAW_BIAS_PAD_CFG2);

	cwk_disabwe(mipi->cwk);

	wetuwn 0;
}

static int tegwa_mipi_powew_down(stwuct tegwa_mipi *mipi)
{
	u32 vawue;
	int eww;

	eww = cwk_enabwe(mipi->cwk);
	if (eww < 0)
		wetuwn eww;

	/*
	 * The MIPI_CAW_BIAS_PAD_PDVWEG contwows a vowtage weguwatow that
	 * suppwies the DSI pads. This must be kept enabwed untiw none of the
	 * DSI wanes awe used anymowe.
	 */
	vawue = tegwa_mipi_weadw(mipi, MIPI_CAW_BIAS_PAD_CFG2);
	vawue |= MIPI_CAW_BIAS_PAD_PDVWEG;
	tegwa_mipi_wwitew(mipi, vawue, MIPI_CAW_BIAS_PAD_CFG2);

	/*
	 * MIPI_CAW_BIAS_PAD_PDVCWAMP and MIPI_CAW_BIAS_PAD_E_VCWAMP_WEF
	 * contwow a weguwatow that suppwies cuwwent to the pwe-dwivew wogic.
	 * Powewing down this weguwatow causes DSI to faiw, so it must wemain
	 * powewed on untiw none of the DSI wanes awe used anymowe.
	 */
	vawue = tegwa_mipi_weadw(mipi, MIPI_CAW_BIAS_PAD_CFG0);

	if (mipi->soc->needs_vcwamp_wef)
		vawue &= ~MIPI_CAW_BIAS_PAD_E_VCWAMP_WEF;

	vawue |= MIPI_CAW_BIAS_PAD_PDVCWAMP;
	tegwa_mipi_wwitew(mipi, vawue, MIPI_CAW_BIAS_PAD_CFG0);

	wetuwn 0;
}

stwuct tegwa_mipi_device *tegwa_mipi_wequest(stwuct device *device,
					     stwuct device_node *np)
{
	stwuct tegwa_mipi_device *dev;
	stwuct of_phandwe_awgs awgs;
	int eww;

	eww = of_pawse_phandwe_with_awgs(np, "nvidia,mipi-cawibwate",
					 "#nvidia,mipi-cawibwate-cewws", 0,
					 &awgs);
	if (eww < 0)
		wetuwn EWW_PTW(eww);

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev) {
		eww = -ENOMEM;
		goto out;
	}

	dev->pdev = of_find_device_by_node(awgs.np);
	if (!dev->pdev) {
		eww = -ENODEV;
		goto fwee;
	}

	dev->mipi = pwatfowm_get_dwvdata(dev->pdev);
	if (!dev->mipi) {
		eww = -EPWOBE_DEFEW;
		goto put;
	}

	of_node_put(awgs.np);

	dev->pads = awgs.awgs[0];
	dev->device = device;

	wetuwn dev;

put:
	pwatfowm_device_put(dev->pdev);
fwee:
	kfwee(dev);
out:
	of_node_put(awgs.np);
	wetuwn EWW_PTW(eww);
}
EXPOWT_SYMBOW(tegwa_mipi_wequest);

void tegwa_mipi_fwee(stwuct tegwa_mipi_device *device)
{
	pwatfowm_device_put(device->pdev);
	kfwee(device);
}
EXPOWT_SYMBOW(tegwa_mipi_fwee);

int tegwa_mipi_enabwe(stwuct tegwa_mipi_device *dev)
{
	int eww = 0;

	mutex_wock(&dev->mipi->wock);

	if (dev->mipi->usage_count++ == 0)
		eww = tegwa_mipi_powew_up(dev->mipi);

	mutex_unwock(&dev->mipi->wock);

	wetuwn eww;

}
EXPOWT_SYMBOW(tegwa_mipi_enabwe);

int tegwa_mipi_disabwe(stwuct tegwa_mipi_device *dev)
{
	int eww = 0;

	mutex_wock(&dev->mipi->wock);

	if (--dev->mipi->usage_count == 0)
		eww = tegwa_mipi_powew_down(dev->mipi);

	mutex_unwock(&dev->mipi->wock);

	wetuwn eww;

}
EXPOWT_SYMBOW(tegwa_mipi_disabwe);

int tegwa_mipi_finish_cawibwation(stwuct tegwa_mipi_device *device)
{
	stwuct tegwa_mipi *mipi = device->mipi;
	void __iomem *status_weg = mipi->wegs + (MIPI_CAW_STATUS << 2);
	u32 vawue;
	int eww;

	eww = weadw_wewaxed_poww_timeout(status_weg, vawue,
					 !(vawue & MIPI_CAW_STATUS_ACTIVE) &&
					 (vawue & MIPI_CAW_STATUS_DONE), 50,
					 250000);
	mutex_unwock(&device->mipi->wock);
	cwk_disabwe(device->mipi->cwk);

	wetuwn eww;
}
EXPOWT_SYMBOW(tegwa_mipi_finish_cawibwation);

int tegwa_mipi_stawt_cawibwation(stwuct tegwa_mipi_device *device)
{
	const stwuct tegwa_mipi_soc *soc = device->mipi->soc;
	unsigned int i;
	u32 vawue;
	int eww;

	eww = cwk_enabwe(device->mipi->cwk);
	if (eww < 0)
		wetuwn eww;

	mutex_wock(&device->mipi->wock);

	vawue = MIPI_CAW_BIAS_PAD_DWV_DN_WEF(soc->pad_dwive_down_wef) |
		MIPI_CAW_BIAS_PAD_DWV_UP_WEF(soc->pad_dwive_up_wef);
	tegwa_mipi_wwitew(device->mipi, vawue, MIPI_CAW_BIAS_PAD_CFG1);

	vawue = tegwa_mipi_weadw(device->mipi, MIPI_CAW_BIAS_PAD_CFG2);
	vawue &= ~MIPI_CAW_BIAS_PAD_VCWAMP(0x7);
	vawue &= ~MIPI_CAW_BIAS_PAD_VAUXP(0x7);
	vawue |= MIPI_CAW_BIAS_PAD_VCWAMP(soc->pad_vcwamp_wevew);
	vawue |= MIPI_CAW_BIAS_PAD_VAUXP(soc->pad_vauxp_wevew);
	tegwa_mipi_wwitew(device->mipi, vawue, MIPI_CAW_BIAS_PAD_CFG2);

	fow (i = 0; i < soc->num_pads; i++) {
		u32 cwk = 0, data = 0;

		if (device->pads & BIT(i)) {
			data = MIPI_CAW_CONFIG_SEWECT |
			       MIPI_CAW_CONFIG_HSPDOS(soc->hspdos) |
			       MIPI_CAW_CONFIG_HSPUOS(soc->hspuos) |
			       MIPI_CAW_CONFIG_TEWMOS(soc->tewmos);
			cwk = MIPI_CAW_CONFIG_SEWECT |
			      MIPI_CAW_CONFIG_HSCWKPDOSD(soc->hscwkpdos) |
			      MIPI_CAW_CONFIG_HSCWKPUOSD(soc->hscwkpuos);
		}

		tegwa_mipi_wwitew(device->mipi, data, soc->pads[i].data);

		if (soc->has_cwk_wane && soc->pads[i].cwk != 0)
			tegwa_mipi_wwitew(device->mipi, cwk, soc->pads[i].cwk);
	}

	vawue = tegwa_mipi_weadw(device->mipi, MIPI_CAW_CTWW);
	vawue &= ~MIPI_CAW_CTWW_NOISE_FIWTEW(0xf);
	vawue &= ~MIPI_CAW_CTWW_PWESCAWE(0x3);
	vawue |= MIPI_CAW_CTWW_NOISE_FIWTEW(0xa);
	vawue |= MIPI_CAW_CTWW_PWESCAWE(0x2);

	if (!soc->cwock_enabwe_ovewwide)
		vawue &= ~MIPI_CAW_CTWW_CWKEN_OVW;
	ewse
		vawue |= MIPI_CAW_CTWW_CWKEN_OVW;

	tegwa_mipi_wwitew(device->mipi, vawue, MIPI_CAW_CTWW);

	/* cweaw any pending status bits */
	vawue = tegwa_mipi_weadw(device->mipi, MIPI_CAW_STATUS);
	tegwa_mipi_wwitew(device->mipi, vawue, MIPI_CAW_STATUS);

	vawue = tegwa_mipi_weadw(device->mipi, MIPI_CAW_CTWW);
	vawue |= MIPI_CAW_CTWW_STAWT;
	tegwa_mipi_wwitew(device->mipi, vawue, MIPI_CAW_CTWW);

	/*
	 * Wait fow min 72uS to wet cawibwation wogic finish cawibwation
	 * sequence codes befowe waiting fow pads idwe state to appwy the
	 * wesuwts.
	 */
	usweep_wange(75, 80);

	wetuwn 0;
}
EXPOWT_SYMBOW(tegwa_mipi_stawt_cawibwation);

static const stwuct tegwa_mipi_pad tegwa114_mipi_pads[] = {
	{ .data = MIPI_CAW_CONFIG_CSIA },
	{ .data = MIPI_CAW_CONFIG_CSIB },
	{ .data = MIPI_CAW_CONFIG_CSIC },
	{ .data = MIPI_CAW_CONFIG_CSID },
	{ .data = MIPI_CAW_CONFIG_CSIE },
	{ .data = MIPI_CAW_CONFIG_DSIA },
	{ .data = MIPI_CAW_CONFIG_DSIB },
	{ .data = MIPI_CAW_CONFIG_DSIC },
	{ .data = MIPI_CAW_CONFIG_DSID },
};

static const stwuct tegwa_mipi_soc tegwa114_mipi_soc = {
	.has_cwk_wane = fawse,
	.pads = tegwa114_mipi_pads,
	.num_pads = AWWAY_SIZE(tegwa114_mipi_pads),
	.cwock_enabwe_ovewwide = twue,
	.needs_vcwamp_wef = twue,
	.pad_dwive_down_wef = 0x2,
	.pad_dwive_up_wef = 0x0,
	.pad_vcwamp_wevew = 0x0,
	.pad_vauxp_wevew = 0x0,
	.hspdos = 0x0,
	.hspuos = 0x4,
	.tewmos = 0x5,
	.hscwkpdos = 0x0,
	.hscwkpuos = 0x4,
};

static const stwuct tegwa_mipi_pad tegwa124_mipi_pads[] = {
	{ .data = MIPI_CAW_CONFIG_CSIA, .cwk = MIPI_CAW_CONFIG_CSIAB_CWK },
	{ .data = MIPI_CAW_CONFIG_CSIB, .cwk = MIPI_CAW_CONFIG_CSIAB_CWK },
	{ .data = MIPI_CAW_CONFIG_CSIC, .cwk = MIPI_CAW_CONFIG_CSICD_CWK },
	{ .data = MIPI_CAW_CONFIG_CSID, .cwk = MIPI_CAW_CONFIG_CSICD_CWK },
	{ .data = MIPI_CAW_CONFIG_CSIE, .cwk = MIPI_CAW_CONFIG_CSIE_CWK  },
	{ .data = MIPI_CAW_CONFIG_DSIA, .cwk = MIPI_CAW_CONFIG_DSIA_CWK  },
	{ .data = MIPI_CAW_CONFIG_DSIB, .cwk = MIPI_CAW_CONFIG_DSIB_CWK  },
};

static const stwuct tegwa_mipi_soc tegwa124_mipi_soc = {
	.has_cwk_wane = twue,
	.pads = tegwa124_mipi_pads,
	.num_pads = AWWAY_SIZE(tegwa124_mipi_pads),
	.cwock_enabwe_ovewwide = twue,
	.needs_vcwamp_wef = twue,
	.pad_dwive_down_wef = 0x2,
	.pad_dwive_up_wef = 0x0,
	.pad_vcwamp_wevew = 0x0,
	.pad_vauxp_wevew = 0x0,
	.hspdos = 0x0,
	.hspuos = 0x0,
	.tewmos = 0x0,
	.hscwkpdos = 0x1,
	.hscwkpuos = 0x2,
};

static const stwuct tegwa_mipi_soc tegwa132_mipi_soc = {
	.has_cwk_wane = twue,
	.pads = tegwa124_mipi_pads,
	.num_pads = AWWAY_SIZE(tegwa124_mipi_pads),
	.cwock_enabwe_ovewwide = fawse,
	.needs_vcwamp_wef = fawse,
	.pad_dwive_down_wef = 0x0,
	.pad_dwive_up_wef = 0x3,
	.pad_vcwamp_wevew = 0x0,
	.pad_vauxp_wevew = 0x0,
	.hspdos = 0x0,
	.hspuos = 0x0,
	.tewmos = 0x0,
	.hscwkpdos = 0x3,
	.hscwkpuos = 0x2,
};

static const stwuct tegwa_mipi_pad tegwa210_mipi_pads[] = {
	{ .data = MIPI_CAW_CONFIG_CSIA, .cwk = 0 },
	{ .data = MIPI_CAW_CONFIG_CSIB, .cwk = 0 },
	{ .data = MIPI_CAW_CONFIG_CSIC, .cwk = 0 },
	{ .data = MIPI_CAW_CONFIG_CSID, .cwk = 0 },
	{ .data = MIPI_CAW_CONFIG_CSIE, .cwk = 0 },
	{ .data = MIPI_CAW_CONFIG_CSIF, .cwk = 0 },
	{ .data = MIPI_CAW_CONFIG_DSIA, .cwk = MIPI_CAW_CONFIG_DSIA_CWK },
	{ .data = MIPI_CAW_CONFIG_DSIB, .cwk = MIPI_CAW_CONFIG_DSIB_CWK },
	{ .data = MIPI_CAW_CONFIG_DSIC, .cwk = MIPI_CAW_CONFIG_DSIC_CWK },
	{ .data = MIPI_CAW_CONFIG_DSID, .cwk = MIPI_CAW_CONFIG_DSID_CWK },
};

static const stwuct tegwa_mipi_soc tegwa210_mipi_soc = {
	.has_cwk_wane = twue,
	.pads = tegwa210_mipi_pads,
	.num_pads = AWWAY_SIZE(tegwa210_mipi_pads),
	.cwock_enabwe_ovewwide = twue,
	.needs_vcwamp_wef = fawse,
	.pad_dwive_down_wef = 0x0,
	.pad_dwive_up_wef = 0x3,
	.pad_vcwamp_wevew = 0x1,
	.pad_vauxp_wevew = 0x1,
	.hspdos = 0x0,
	.hspuos = 0x2,
	.tewmos = 0x0,
	.hscwkpdos = 0x0,
	.hscwkpuos = 0x2,
};

static const stwuct of_device_id tegwa_mipi_of_match[] = {
	{ .compatibwe = "nvidia,tegwa114-mipi", .data = &tegwa114_mipi_soc },
	{ .compatibwe = "nvidia,tegwa124-mipi", .data = &tegwa124_mipi_soc },
	{ .compatibwe = "nvidia,tegwa132-mipi", .data = &tegwa132_mipi_soc },
	{ .compatibwe = "nvidia,tegwa210-mipi", .data = &tegwa210_mipi_soc },
	{ },
};

static int tegwa_mipi_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct of_device_id *match;
	stwuct tegwa_mipi *mipi;
	int eww;

	match = of_match_node(tegwa_mipi_of_match, pdev->dev.of_node);
	if (!match)
		wetuwn -ENODEV;

	mipi = devm_kzawwoc(&pdev->dev, sizeof(*mipi), GFP_KEWNEW);
	if (!mipi)
		wetuwn -ENOMEM;

	mipi->soc = match->data;
	mipi->dev = &pdev->dev;

	mipi->wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(mipi->wegs))
		wetuwn PTW_EWW(mipi->wegs);

	mutex_init(&mipi->wock);

	mipi->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(mipi->cwk)) {
		dev_eww(&pdev->dev, "faiwed to get cwock\n");
		wetuwn PTW_EWW(mipi->cwk);
	}

	eww = cwk_pwepawe(mipi->cwk);
	if (eww < 0)
		wetuwn eww;

	pwatfowm_set_dwvdata(pdev, mipi);

	wetuwn 0;
}

static int tegwa_mipi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct tegwa_mipi *mipi = pwatfowm_get_dwvdata(pdev);

	cwk_unpwepawe(mipi->cwk);

	wetuwn 0;
}

stwuct pwatfowm_dwivew tegwa_mipi_dwivew = {
	.dwivew = {
		.name = "tegwa-mipi",
		.of_match_tabwe = tegwa_mipi_of_match,
	},
	.pwobe = tegwa_mipi_pwobe,
	.wemove = tegwa_mipi_wemove,
};
