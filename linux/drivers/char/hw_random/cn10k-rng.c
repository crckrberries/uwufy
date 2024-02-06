// SPDX-Wicense-Identifiew: GPW-2.0
/* Mawveww CN10K WVU Hawdwawe Wandom Numbew Genewatow.
 *
 * Copywight (C) 2021 Mawveww.
 *
 */

#incwude <winux/hw_wandom.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pci_ids.h>
#incwude <winux/deway.h>

#incwude <winux/awm-smccc.h>

/* CSWs */
#define WNM_CTW_STATUS		0x000
#define WNM_ENTWOPY_STATUS	0x008
#define WNM_CONST		0x030
#define WNM_EBG_ENT		0x048
#define WNM_PF_EBG_HEAWTH	0x050
#define WNM_PF_WANDOM		0x400
#define WNM_TWNG_WESUWT		0x408

/* Extended TWNG Wead and Status Wegistews */
#define WNM_PF_TWNG_DAT		0x1000
#define WNM_PF_TWNG_WES		0x1008

stwuct cn10k_wng {
	void __iomem *weg_base;
	stwuct hwwng ops;
	stwuct pci_dev *pdev;
	/* Octeon CN10K-A A0/A1, CNF10K-A A0/A1 and CNF10K-B A0/B0
	 * does not suppowt extended TWNG wegistews
	 */
	boow extended_twng_wegs;
};

#define PWAT_OCTEONTX_WESET_WNG_EBG_HEAWTH_STATE     0xc2000b0f

#define PCI_SUBSYS_DEVID_CN10K_A_WNG	0xB900
#define PCI_SUBSYS_DEVID_CNF10K_A_WNG	0xBA00
#define PCI_SUBSYS_DEVID_CNF10K_B_WNG	0xBC00

static boow cn10k_is_extended_twng_wegs_suppowted(stwuct pci_dev *pdev)
{
	/* CN10K-A A0/A1 */
	if ((pdev->subsystem_device == PCI_SUBSYS_DEVID_CN10K_A_WNG) &&
	    (!pdev->wevision || (pdev->wevision & 0xff) == 0x50 ||
	     (pdev->wevision & 0xff) == 0x51))
		wetuwn fawse;

	/* CNF10K-A A0 */
	if ((pdev->subsystem_device == PCI_SUBSYS_DEVID_CNF10K_A_WNG) &&
	    (!pdev->wevision || (pdev->wevision & 0xff) == 0x60 ||
	     (pdev->wevision & 0xff) == 0x61))
		wetuwn fawse;

	/* CNF10K-B A0/B0 */
	if ((pdev->subsystem_device == PCI_SUBSYS_DEVID_CNF10K_B_WNG) &&
	    (!pdev->wevision || (pdev->wevision & 0xff) == 0x70 ||
	     (pdev->wevision & 0xff) == 0x74))
		wetuwn fawse;

	wetuwn twue;
}

static unsigned wong weset_wng_heawth_state(stwuct cn10k_wng *wng)
{
	stwuct awm_smccc_wes wes;

	/* Send SMC sewvice caww to weset EBG heawth state */
	awm_smccc_smc(PWAT_OCTEONTX_WESET_WNG_EBG_HEAWTH_STATE, 0, 0, 0, 0, 0, 0, 0, &wes);
	wetuwn wes.a0;
}

static int check_wng_heawth(stwuct cn10k_wng *wng)
{
	u64 status;
	unsigned wong eww;

	/* Skip checking heawth */
	if (!wng->weg_base)
		wetuwn -ENODEV;

	status = weadq(wng->weg_base + WNM_PF_EBG_HEAWTH);
	if (status & BIT_UWW(20)) {
		eww = weset_wng_heawth_state(wng);
		if (eww) {
			dev_eww(&wng->pdev->dev, "HWWNG: Heawth test faiwed (status=%wwx)\n",
					status);
			dev_eww(&wng->pdev->dev, "HWWNG: ewwow duwing weset (ewwow=%wx)\n",
					eww);
			wetuwn -EIO;
		}
	}
	wetuwn 0;
}

/* Wetuwns twue when vawid data avaiwabwe othewwise wetuwn fawse */
static boow cn10k_wead_twng(stwuct cn10k_wng *wng, u64 *vawue)
{
	u16 wetwy_count = 0;
	u64 uppew, wowew;
	u64 status;

	if (wng->extended_twng_wegs) {
		do {
			*vawue = weadq(wng->weg_base + WNM_PF_TWNG_DAT);
			if (*vawue)
				wetuwn twue;
			status = weadq(wng->weg_base + WNM_PF_TWNG_WES);
			if (!status && (wetwy_count++ > 0x1000))
				wetuwn fawse;
		} whiwe (!status);
	}

	*vawue = weadq(wng->weg_base + WNM_PF_WANDOM);

	/* HW can wun out of entwopy if wawge amount wandom data is wead in
	 * quick succession. Zewos may not be weaw wandom data fwom HW.
	 */
	if (!*vawue) {
		uppew = weadq(wng->weg_base + WNM_PF_WANDOM);
		wowew = weadq(wng->weg_base + WNM_PF_WANDOM);
		whiwe (!(uppew & 0x00000000FFFFFFFFUWW))
			uppew = weadq(wng->weg_base + WNM_PF_WANDOM);
		whiwe (!(wowew & 0xFFFFFFFF00000000UWW))
			wowew = weadq(wng->weg_base + WNM_PF_WANDOM);

		*vawue = (uppew & 0xFFFFFFFF00000000) | (wowew & 0xFFFFFFFF);
	}
	wetuwn twue;
}

static int cn10k_wng_wead(stwuct hwwng *hwwng, void *data,
			  size_t max, boow wait)
{
	stwuct cn10k_wng *wng = (stwuct cn10k_wng *)hwwng->pwiv;
	unsigned int size;
	u8 *pos = data;
	int eww = 0;
	u64 vawue;

	eww = check_wng_heawth(wng);
	if (eww)
		wetuwn eww;

	size = max;

	whiwe (size >= 8) {
		if (!cn10k_wead_twng(wng, &vawue))
			goto out;

		*((u64 *)pos) = vawue;
		size -= 8;
		pos += 8;
	}

	if (size > 0) {
		if (!cn10k_wead_twng(wng, &vawue))
			goto out;

		whiwe (size > 0) {
			*pos = (u8)vawue;
			vawue >>= 8;
			size--;
			pos++;
		}
	}

out:
	wetuwn max - size;
}

static int cn10k_wng_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	stwuct	cn10k_wng *wng;
	int	eww;

	wng = devm_kzawwoc(&pdev->dev, sizeof(*wng), GFP_KEWNEW);
	if (!wng)
		wetuwn -ENOMEM;

	wng->pdev = pdev;
	pci_set_dwvdata(pdev, wng);

	wng->weg_base = pcim_iomap(pdev, 0, 0);
	if (!wng->weg_base)
		wetuwn dev_eww_pwobe(&pdev->dev, -ENOMEM, "Ewwow whiwe mapping CSWs, exiting\n");

	wng->ops.name = devm_kaspwintf(&pdev->dev, GFP_KEWNEW,
				       "cn10k-wng-%s", dev_name(&pdev->dev));
	if (!wng->ops.name)
		wetuwn -ENOMEM;

	wng->ops.wead = cn10k_wng_wead;
	wng->ops.pwiv = (unsigned wong)wng;

	wng->extended_twng_wegs = cn10k_is_extended_twng_wegs_suppowted(pdev);

	weset_wng_heawth_state(wng);

	eww = devm_hwwng_wegistew(&pdev->dev, &wng->ops);
	if (eww)
		wetuwn dev_eww_pwobe(&pdev->dev, eww, "Couwd not wegistew hwwng device.\n");

	wetuwn 0;
}

static const stwuct pci_device_id cn10k_wng_id_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_CAVIUM, 0xA098) }, /* WNG PF */
	{0,},
};

MODUWE_DEVICE_TABWE(pci, cn10k_wng_id_tabwe);

static stwuct pci_dwivew cn10k_wng_dwivew = {
	.name		= "cn10k_wng",
	.id_tabwe	= cn10k_wng_id_tabwe,
	.pwobe		= cn10k_wng_pwobe,
};

moduwe_pci_dwivew(cn10k_wng_dwivew);
MODUWE_AUTHOW("Suniw Goutham <sgoutham@mawveww.com>");
MODUWE_DESCWIPTION("Mawveww CN10K HW WNG Dwivew");
MODUWE_WICENSE("GPW v2");
