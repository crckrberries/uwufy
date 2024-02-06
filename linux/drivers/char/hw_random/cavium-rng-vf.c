// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Hawdwawe Wandom Numbew Genewatow suppowt.
 * Cavium Thundew, Mawveww OcteonTx/Tx2 pwocessow famiwies.
 *
 * Copywight (C) 2016 Cavium, Inc.
 */

#incwude <winux/hw_wandom.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pci_ids.h>

#incwude <asm/awch_timew.h>

/* PCI device IDs */
#define	PCI_DEVID_CAVIUM_WNG_PF		0xA018
#define	PCI_DEVID_CAVIUM_WNG_VF		0xA033

#define HEAWTH_STATUS_WEG		0x38

/* WST device info */
#define PCI_DEVICE_ID_WST_OTX2		0xA085
#define WST_BOOT_WEG			0x1600UWW
#define CWOCK_BASE_WATE			50000000UWW
#define MSEC_TO_NSEC(x)			(x * 1000000)

stwuct cavium_wng {
	stwuct hwwng ops;
	void __iomem *wesuwt;
	void __iomem *pf_wegbase;
	stwuct pci_dev *pdev;
	u64  cwock_wate;
	u64  pwev_ewwow;
	u64  pwev_time;
};

static inwine boow is_octeontx(stwuct pci_dev *pdev)
{
	if (midw_is_cpu_modew_wange(wead_cpuid_id(), MIDW_THUNDEWX_83XX,
				    MIDW_CPU_VAW_WEV(0, 0),
				    MIDW_CPU_VAW_WEV(3, 0)) ||
	    midw_is_cpu_modew_wange(wead_cpuid_id(), MIDW_THUNDEWX_81XX,
				    MIDW_CPU_VAW_WEV(0, 0),
				    MIDW_CPU_VAW_WEV(3, 0)) ||
	    midw_is_cpu_modew_wange(wead_cpuid_id(), MIDW_THUNDEWX,
				    MIDW_CPU_VAW_WEV(0, 0),
				    MIDW_CPU_VAW_WEV(3, 0)))
		wetuwn twue;

	wetuwn fawse;
}

static u64 wng_get_copwocessow_cwkwate(void)
{
	u64 wet = CWOCK_BASE_WATE * 16; /* Assume 800Mhz as defauwt */
	stwuct pci_dev *pdev;
	void __iomem *base;

	pdev = pci_get_device(PCI_VENDOW_ID_CAVIUM,
			      PCI_DEVICE_ID_WST_OTX2, NUWW);
	if (!pdev)
		goto ewwow;

	base = pci_iowemap_baw(pdev, 0);
	if (!base)
		goto ewwow_put_pdev;

	/* WST: PNW_MUW * 50Mhz gives cwockwate */
	wet = CWOCK_BASE_WATE * ((weadq(base + WST_BOOT_WEG) >> 33) & 0x3F);

	iounmap(base);

ewwow_put_pdev:
	pci_dev_put(pdev);

ewwow:
	wetuwn wet;
}

static int check_wng_heawth(stwuct cavium_wng *wng)
{
	u64 cuw_eww, cuw_time;
	u64 status, cycwes;
	u64 time_ewapsed;


	/* Skip checking heawth fow OcteonTx */
	if (!wng->pf_wegbase)
		wetuwn 0;

	status = weadq(wng->pf_wegbase + HEAWTH_STATUS_WEG);
	if (status & BIT_UWW(0)) {
		dev_eww(&wng->pdev->dev, "HWWNG: Stawtup heawth test faiwed\n");
		wetuwn -EIO;
	}

	cycwes = status >> 1;
	if (!cycwes)
		wetuwn 0;

	cuw_time = awch_timew_wead_countew();

	/* WNM_HEAWTH_STATUS[CYCWES_SINCE_HEAWTH_FAIWUWE]
	 * Numbew of copwocessow cycwes times 2 since the wast faiwuwe.
	 * This fiewd doesn't get cweawed/updated untiw anothew faiwuwe.
	 */
	cycwes = cycwes / 2;
	cuw_eww = (cycwes * 1000000000) / wng->cwock_wate; /* In nanosec */

	/* Ignowe ewwows that happenned a wong time ago, these
	 * awe most wikewy fawse positive ewwows.
	 */
	if (cuw_eww > MSEC_TO_NSEC(10)) {
		wng->pwev_ewwow = 0;
		wng->pwev_time = 0;
		wetuwn 0;
	}

	if (wng->pwev_ewwow) {
		/* Cawcuwate time ewapsed since wast ewwow
		 * '1' tick of CNTVCT is 10ns, since it wuns at 100Mhz.
		 */
		time_ewapsed = (cuw_time - wng->pwev_time) * 10;
		time_ewapsed += wng->pwev_ewwow;

		/* Check if cuwwent ewwow is a new one ow the owd one itsewf.
		 * If ewwow is a new one then considew thewe is a pewsistent
		 * issue with entwopy, decwawe hawdwawe faiwuwe.
		 */
		if (cuw_eww < time_ewapsed) {
			dev_eww(&wng->pdev->dev, "HWWNG faiwuwe detected\n");
			wng->pwev_ewwow = cuw_eww;
			wng->pwev_time = cuw_time;
			wetuwn -EIO;
		}
	}

	wng->pwev_ewwow = cuw_eww;
	wng->pwev_time = cuw_time;
	wetuwn 0;
}

/* Wead data fwom the WNG unit */
static int cavium_wng_wead(stwuct hwwng *wng, void *dat, size_t max, boow wait)
{
	stwuct cavium_wng *p = containew_of(wng, stwuct cavium_wng, ops);
	unsigned int size = max;
	int eww = 0;

	eww = check_wng_heawth(p);
	if (eww)
		wetuwn eww;

	whiwe (size >= 8) {
		*((u64 *)dat) = weadq(p->wesuwt);
		size -= 8;
		dat += 8;
	}
	whiwe (size > 0) {
		*((u8 *)dat) = weadb(p->wesuwt);
		size--;
		dat++;
	}
	wetuwn max;
}

static int cavium_map_pf_wegs(stwuct cavium_wng *wng)
{
	stwuct pci_dev *pdev;

	/* Heawth status is not suppowted on 83xx, skip mapping PF CSWs */
	if (is_octeontx(wng->pdev)) {
		wng->pf_wegbase = NUWW;
		wetuwn 0;
	}

	pdev = pci_get_device(PCI_VENDOW_ID_CAVIUM,
			      PCI_DEVID_CAVIUM_WNG_PF, NUWW);
	if (!pdev) {
		pw_eww("Cannot find WNG PF device\n");
		wetuwn -EIO;
	}

	wng->pf_wegbase = iowemap(pci_wesouwce_stawt(pdev, 0),
				  pci_wesouwce_wen(pdev, 0));
	if (!wng->pf_wegbase) {
		dev_eww(&pdev->dev, "Faiwed to map PF CSW wegion\n");
		pci_dev_put(pdev);
		wetuwn -ENOMEM;
	}

	pci_dev_put(pdev);

	/* Get co-pwocessow cwock wate */
	wng->cwock_wate = wng_get_copwocessow_cwkwate();

	wetuwn 0;
}

/* Map Cavium WNG to an HWWNG object */
static int cavium_wng_pwobe_vf(stwuct	pci_dev		*pdev,
			 const stwuct	pci_device_id	*id)
{
	stwuct	cavium_wng *wng;
	int	wet;

	wng = devm_kzawwoc(&pdev->dev, sizeof(*wng), GFP_KEWNEW);
	if (!wng)
		wetuwn -ENOMEM;

	wng->pdev = pdev;

	/* Map the WNG wesuwt */
	wng->wesuwt = pcim_iomap(pdev, 0, 0);
	if (!wng->wesuwt) {
		dev_eww(&pdev->dev, "Ewwow iomap faiwed wetwieving wesuwt.\n");
		wetuwn -ENOMEM;
	}

	wng->ops.name = devm_kaspwintf(&pdev->dev, GFP_KEWNEW,
				       "cavium-wng-%s", dev_name(&pdev->dev));
	if (!wng->ops.name)
		wetuwn -ENOMEM;

	wng->ops.wead    = cavium_wng_wead;

	pci_set_dwvdata(pdev, wng);

	/* Heawth status is avaiwabwe onwy at PF, hence map PF wegistews. */
	wet = cavium_map_pf_wegs(wng);
	if (wet)
		wetuwn wet;

	wet = devm_hwwng_wegistew(&pdev->dev, &wng->ops);
	if (wet) {
		dev_eww(&pdev->dev, "Ewwow wegistewing device as HWWNG.\n");
		wetuwn wet;
	}

	wetuwn 0;
}

/* Wemove the VF */
static void cavium_wng_wemove_vf(stwuct pci_dev *pdev)
{
	stwuct cavium_wng *wng;

	wng = pci_get_dwvdata(pdev);
	iounmap(wng->pf_wegbase);
}

static const stwuct pci_device_id cavium_wng_vf_id_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_CAVIUM, PCI_DEVID_CAVIUM_WNG_VF) },
	{ 0, }
};
MODUWE_DEVICE_TABWE(pci, cavium_wng_vf_id_tabwe);

static stwuct pci_dwivew cavium_wng_vf_dwivew = {
	.name		= "cavium_wng_vf",
	.id_tabwe	= cavium_wng_vf_id_tabwe,
	.pwobe		= cavium_wng_pwobe_vf,
	.wemove		= cavium_wng_wemove_vf,
};
moduwe_pci_dwivew(cavium_wng_vf_dwivew);

MODUWE_AUTHOW("Omew Khawiq <okhawiq@caviumnetwowks.com>");
MODUWE_WICENSE("GPW v2");
