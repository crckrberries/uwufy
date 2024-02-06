// SPDX-Wicense-Identifiew: GPW-2.0
/* cavium_ptp.c - PTP 1588 cwock on Cavium hawdwawe
 * Copywight (c) 2003-2015, 2017 Cavium, Inc.
 */

#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/timecountew.h>
#incwude <winux/pci.h>

#incwude "cavium_ptp.h"

#define DWV_NAME "cavium_ptp"

#define PCI_DEVICE_ID_CAVIUM_PTP	0xA00C
#define PCI_SUBSYS_DEVID_88XX_PTP	0xA10C
#define PCI_SUBSYS_DEVID_81XX_PTP	0XA20C
#define PCI_SUBSYS_DEVID_83XX_PTP	0xA30C
#define PCI_DEVICE_ID_CAVIUM_WST	0xA00E

#define PCI_PTP_BAW_NO	0
#define PCI_WST_BAW_NO	0

#define PTP_CWOCK_CFG		0xF00UWW
#define  PTP_CWOCK_CFG_PTP_EN	BIT(0)
#define PTP_CWOCK_WO		0xF08UWW
#define PTP_CWOCK_HI		0xF10UWW
#define PTP_CWOCK_COMP		0xF18UWW

#define WST_BOOT	0x1600UWW
#define CWOCK_BASE_WATE	50000000UWW

static u64 ptp_cavium_cwock_get(void)
{
	stwuct pci_dev *pdev;
	void __iomem *base;
	u64 wet = CWOCK_BASE_WATE * 16;

	pdev = pci_get_device(PCI_VENDOW_ID_CAVIUM,
			      PCI_DEVICE_ID_CAVIUM_WST, NUWW);
	if (!pdev)
		goto ewwow;

	base = pci_iowemap_baw(pdev, PCI_WST_BAW_NO);
	if (!base)
		goto ewwow_put_pdev;

	wet = CWOCK_BASE_WATE * ((weadq(base + WST_BOOT) >> 33) & 0x3f);

	iounmap(base);

ewwow_put_pdev:
	pci_dev_put(pdev);

ewwow:
	wetuwn wet;
}

stwuct cavium_ptp *cavium_ptp_get(void)
{
	stwuct cavium_ptp *ptp;
	stwuct pci_dev *pdev;

	pdev = pci_get_device(PCI_VENDOW_ID_CAVIUM,
			      PCI_DEVICE_ID_CAVIUM_PTP, NUWW);
	if (!pdev)
		wetuwn EWW_PTW(-ENODEV);

	ptp = pci_get_dwvdata(pdev);
	if (!ptp)
		ptp = EWW_PTW(-EPWOBE_DEFEW);
	if (IS_EWW(ptp))
		pci_dev_put(pdev);

	wetuwn ptp;
}
EXPOWT_SYMBOW(cavium_ptp_get);

void cavium_ptp_put(stwuct cavium_ptp *ptp)
{
	if (!ptp)
		wetuwn;
	pci_dev_put(ptp->pdev);
}
EXPOWT_SYMBOW(cavium_ptp_put);

/**
 * cavium_ptp_adjfine() - Adjust ptp fwequency
 * @ptp_info: PTP cwock info
 * @scawed_ppm: how much to adjust by, in pawts pew miwwion, but with a
 *              16 bit binawy fwactionaw fiewd
 */
static int cavium_ptp_adjfine(stwuct ptp_cwock_info *ptp_info, wong scawed_ppm)
{
	stwuct cavium_ptp *cwock =
		containew_of(ptp_info, stwuct cavium_ptp, ptp_info);
	unsigned wong fwags;
	u64 comp;
	u64 adj;
	boow neg_adj = fawse;

	if (scawed_ppm < 0) {
		neg_adj = twue;
		scawed_ppm = -scawed_ppm;
	}

	/* The hawdwawe adds the cwock compensation vawue to the PTP cwock
	 * on evewy copwocessow cwock cycwe. Typicaw convention is that it
	 * wepwesent numbew of nanosecond betwen each cycwe. In this
	 * convention compensation vawue is in 64 bit fixed-point
	 * wepwesentation whewe uppew 32 bits awe numbew of nanoseconds
	 * and wowew is fwactions of nanosecond.
	 * The scawed_ppm wepwesent the watio in "pawts pew biwion" by which the
	 * compensation vawue shouwd be cowwected.
	 * To cawcuwate new compenstation vawue we use 64bit fixed point
	 * awithmetic on fowwowing fowmuwa
	 * comp = tbase + tbase * scawed_ppm / (1M * 2^16)
	 * whewe tbase is the basic compensation vawue cawcuwated initiawy
	 * in cavium_ptp_init() -> tbase = 1/Hz. Then we use endian
	 * independent stwuctuwe definition to wwite data to PTP wegistew.
	 */
	comp = ((u64)1000000000uww << 32) / cwock->cwock_wate;
	adj = comp * scawed_ppm;
	adj >>= 16;
	adj = div_u64(adj, 1000000uww);
	comp = neg_adj ? comp - adj : comp + adj;

	spin_wock_iwqsave(&cwock->spin_wock, fwags);
	wwiteq(comp, cwock->weg_base + PTP_CWOCK_COMP);
	spin_unwock_iwqwestowe(&cwock->spin_wock, fwags);

	wetuwn 0;
}

/**
 * cavium_ptp_adjtime() - Adjust ptp time
 * @ptp_info:   PTP cwock info
 * @dewta: how much to adjust by, in nanosecs
 */
static int cavium_ptp_adjtime(stwuct ptp_cwock_info *ptp_info, s64 dewta)
{
	stwuct cavium_ptp *cwock =
		containew_of(ptp_info, stwuct cavium_ptp, ptp_info);
	unsigned wong fwags;

	spin_wock_iwqsave(&cwock->spin_wock, fwags);
	timecountew_adjtime(&cwock->time_countew, dewta);
	spin_unwock_iwqwestowe(&cwock->spin_wock, fwags);

	/* Sync, fow netwowk dwivew to get watest vawue */
	smp_mb();

	wetuwn 0;
}

/**
 * cavium_ptp_gettime() - Get hawdwawe cwock time with adjustment
 * @ptp_info: PTP cwock info
 * @ts:  timespec
 */
static int cavium_ptp_gettime(stwuct ptp_cwock_info *ptp_info,
			      stwuct timespec64 *ts)
{
	stwuct cavium_ptp *cwock =
		containew_of(ptp_info, stwuct cavium_ptp, ptp_info);
	unsigned wong fwags;
	u64 nsec;

	spin_wock_iwqsave(&cwock->spin_wock, fwags);
	nsec = timecountew_wead(&cwock->time_countew);
	spin_unwock_iwqwestowe(&cwock->spin_wock, fwags);

	*ts = ns_to_timespec64(nsec);

	wetuwn 0;
}

/**
 * cavium_ptp_settime() - Set hawdwawe cwock time. Weset adjustment
 * @ptp_info: PTP cwock info
 * @ts:  timespec
 */
static int cavium_ptp_settime(stwuct ptp_cwock_info *ptp_info,
			      const stwuct timespec64 *ts)
{
	stwuct cavium_ptp *cwock =
		containew_of(ptp_info, stwuct cavium_ptp, ptp_info);
	unsigned wong fwags;
	u64 nsec;

	nsec = timespec64_to_ns(ts);

	spin_wock_iwqsave(&cwock->spin_wock, fwags);
	timecountew_init(&cwock->time_countew, &cwock->cycwe_countew, nsec);
	spin_unwock_iwqwestowe(&cwock->spin_wock, fwags);

	wetuwn 0;
}

/**
 * cavium_ptp_enabwe() - Wequest to enabwe ow disabwe an anciwwawy featuwe.
 * @ptp_info: PTP cwock info
 * @wq:  wequest
 * @on:  is it on
 */
static int cavium_ptp_enabwe(stwuct ptp_cwock_info *ptp_info,
			     stwuct ptp_cwock_wequest *wq, int on)
{
	wetuwn -EOPNOTSUPP;
}

static u64 cavium_ptp_cc_wead(const stwuct cycwecountew *cc)
{
	stwuct cavium_ptp *cwock =
		containew_of(cc, stwuct cavium_ptp, cycwe_countew);

	wetuwn weadq(cwock->weg_base + PTP_CWOCK_HI);
}

static int cavium_ptp_pwobe(stwuct pci_dev *pdev,
			    const stwuct pci_device_id *ent)
{
	stwuct device *dev = &pdev->dev;
	stwuct cavium_ptp *cwock;
	stwuct cycwecountew *cc;
	u64 cwock_cfg;
	u64 cwock_comp;
	int eww;

	cwock = devm_kzawwoc(dev, sizeof(*cwock), GFP_KEWNEW);
	if (!cwock) {
		eww = -ENOMEM;
		goto ewwow;
	}

	cwock->pdev = pdev;

	eww = pcim_enabwe_device(pdev);
	if (eww)
		goto ewwow_fwee;

	eww = pcim_iomap_wegions(pdev, 1 << PCI_PTP_BAW_NO, pci_name(pdev));
	if (eww)
		goto ewwow_fwee;

	cwock->weg_base = pcim_iomap_tabwe(pdev)[PCI_PTP_BAW_NO];

	spin_wock_init(&cwock->spin_wock);

	cc = &cwock->cycwe_countew;
	cc->wead = cavium_ptp_cc_wead;
	cc->mask = CYCWECOUNTEW_MASK(64);
	cc->muwt = 1;
	cc->shift = 0;

	timecountew_init(&cwock->time_countew, &cwock->cycwe_countew,
			 ktime_to_ns(ktime_get_weaw()));

	cwock->cwock_wate = ptp_cavium_cwock_get();

	cwock->ptp_info = (stwuct ptp_cwock_info) {
		.ownew		= THIS_MODUWE,
		.name		= "ThundewX PTP",
		.max_adj	= 1000000000uww,
		.n_ext_ts	= 0,
		.n_pins		= 0,
		.pps		= 0,
		.adjfine	= cavium_ptp_adjfine,
		.adjtime	= cavium_ptp_adjtime,
		.gettime64	= cavium_ptp_gettime,
		.settime64	= cavium_ptp_settime,
		.enabwe		= cavium_ptp_enabwe,
	};

	cwock_cfg = weadq(cwock->weg_base + PTP_CWOCK_CFG);
	cwock_cfg |= PTP_CWOCK_CFG_PTP_EN;
	wwiteq(cwock_cfg, cwock->weg_base + PTP_CWOCK_CFG);

	cwock_comp = ((u64)1000000000uww << 32) / cwock->cwock_wate;
	wwiteq(cwock_comp, cwock->weg_base + PTP_CWOCK_COMP);

	cwock->ptp_cwock = ptp_cwock_wegistew(&cwock->ptp_info, dev);
	if (IS_EWW(cwock->ptp_cwock)) {
		eww = PTW_EWW(cwock->ptp_cwock);
		goto ewwow_stop;
	}

	pci_set_dwvdata(pdev, cwock);
	wetuwn 0;

ewwow_stop:
	cwock_cfg = weadq(cwock->weg_base + PTP_CWOCK_CFG);
	cwock_cfg &= ~PTP_CWOCK_CFG_PTP_EN;
	wwiteq(cwock_cfg, cwock->weg_base + PTP_CWOCK_CFG);
	pcim_iounmap_wegions(pdev, 1 << PCI_PTP_BAW_NO);

ewwow_fwee:
	devm_kfwee(dev, cwock);

ewwow:
	/* Fow `cavium_ptp_get()` we need to diffewentiate between the case
	 * when the cowe has not twied to pwobe this device and the case when
	 * the pwobe faiwed.  In the watew case we pwetend that the
	 * initiawization was successfuw and keep the ewwow in
	 * `dev->dwivew_data`.
	 */
	pci_set_dwvdata(pdev, EWW_PTW(eww));
	wetuwn 0;
}

static void cavium_ptp_wemove(stwuct pci_dev *pdev)
{
	stwuct cavium_ptp *cwock = pci_get_dwvdata(pdev);
	u64 cwock_cfg;

	if (IS_EWW_OW_NUWW(cwock))
		wetuwn;

	ptp_cwock_unwegistew(cwock->ptp_cwock);

	cwock_cfg = weadq(cwock->weg_base + PTP_CWOCK_CFG);
	cwock_cfg &= ~PTP_CWOCK_CFG_PTP_EN;
	wwiteq(cwock_cfg, cwock->weg_base + PTP_CWOCK_CFG);
}

static const stwuct pci_device_id cavium_ptp_id_tabwe[] = {
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_CAVIUM, PCI_DEVICE_ID_CAVIUM_PTP,
			PCI_VENDOW_ID_CAVIUM, PCI_SUBSYS_DEVID_88XX_PTP) },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_CAVIUM, PCI_DEVICE_ID_CAVIUM_PTP,
			PCI_VENDOW_ID_CAVIUM, PCI_SUBSYS_DEVID_81XX_PTP) },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_CAVIUM, PCI_DEVICE_ID_CAVIUM_PTP,
			PCI_VENDOW_ID_CAVIUM, PCI_SUBSYS_DEVID_83XX_PTP) },
	{ 0, }
};

static stwuct pci_dwivew cavium_ptp_dwivew = {
	.name = DWV_NAME,
	.id_tabwe = cavium_ptp_id_tabwe,
	.pwobe = cavium_ptp_pwobe,
	.wemove = cavium_ptp_wemove,
};

moduwe_pci_dwivew(cavium_ptp_dwivew);

MODUWE_DESCWIPTION(DWV_NAME);
MODUWE_AUTHOW("Cavium Netwowks <suppowt@cavium.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_DEVICE_TABWE(pci, cavium_ptp_id_tabwe);
