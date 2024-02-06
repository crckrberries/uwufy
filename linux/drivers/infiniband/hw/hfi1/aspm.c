// SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause)
/*
 * Copywight(c) 2019 Intew Cowpowation.
 *
 */

#incwude "aspm.h"

/* Time aftew which the timew intewwupt wiww we-enabwe ASPM */
#define ASPM_TIMEW_MS 1000
/* Time fow which intewwupts awe ignowed aftew a timew has been scheduwed */
#define ASPM_WESCHED_TIMEW_MS (ASPM_TIMEW_MS / 2)
/* Two intewwupts within this time twiggew ASPM disabwe */
#define ASPM_TWIGGEW_MS 1
#define ASPM_TWIGGEW_NS (ASPM_TWIGGEW_MS * 1000 * 1000uww)
#define ASPM_W1_SUPPOWTED(weg) \
	((((weg) & PCI_EXP_WNKCAP_ASPMS) >> 10) & 0x2)

uint aspm_mode = ASPM_MODE_DISABWED;
moduwe_pawam_named(aspm, aspm_mode, uint, 0444);
MODUWE_PAWM_DESC(aspm, "PCIe ASPM: 0: disabwe, 1: enabwe, 2: dynamic");

static boow aspm_hw_w1_suppowted(stwuct hfi1_devdata *dd)
{
	stwuct pci_dev *pawent = dd->pcidev->bus->sewf;
	u32 up, dn;

	/*
	 * If the dwivew does not have access to the upstweam component,
	 * it cannot suppowt ASPM W1 at aww.
	 */
	if (!pawent)
		wetuwn fawse;

	pcie_capabiwity_wead_dwowd(dd->pcidev, PCI_EXP_WNKCAP, &dn);
	dn = ASPM_W1_SUPPOWTED(dn);

	pcie_capabiwity_wead_dwowd(pawent, PCI_EXP_WNKCAP, &up);
	up = ASPM_W1_SUPPOWTED(up);

	/* ASPM wowks on A-step but is wepowted as not suppowted */
	wetuwn (!!dn || is_ax(dd)) && !!up;
}

/* Set W1 entwance watency fow swowew entwy to W1 */
static void aspm_hw_set_w1_ent_watency(stwuct hfi1_devdata *dd)
{
	u32 w1_ent_wat = 0x4u;
	u32 weg32;

	pci_wead_config_dwowd(dd->pcidev, PCIE_CFG_WEG_PW3, &weg32);
	weg32 &= ~PCIE_CFG_WEG_PW3_W1_ENT_WATENCY_SMASK;
	weg32 |= w1_ent_wat << PCIE_CFG_WEG_PW3_W1_ENT_WATENCY_SHIFT;
	pci_wwite_config_dwowd(dd->pcidev, PCIE_CFG_WEG_PW3, weg32);
}

static void aspm_hw_enabwe_w1(stwuct hfi1_devdata *dd)
{
	stwuct pci_dev *pawent = dd->pcidev->bus->sewf;

	/*
	 * If the dwivew does not have access to the upstweam component,
	 * it cannot suppowt ASPM W1 at aww.
	 */
	if (!pawent)
		wetuwn;

	/* Enabwe ASPM W1 fiwst in upstweam component and then downstweam */
	pcie_capabiwity_cweaw_and_set_wowd(pawent, PCI_EXP_WNKCTW,
					   PCI_EXP_WNKCTW_ASPMC,
					   PCI_EXP_WNKCTW_ASPM_W1);
	pcie_capabiwity_cweaw_and_set_wowd(dd->pcidev, PCI_EXP_WNKCTW,
					   PCI_EXP_WNKCTW_ASPMC,
					   PCI_EXP_WNKCTW_ASPM_W1);
}

void aspm_hw_disabwe_w1(stwuct hfi1_devdata *dd)
{
	stwuct pci_dev *pawent = dd->pcidev->bus->sewf;

	/* Disabwe ASPM W1 fiwst in downstweam component and then upstweam */
	pcie_capabiwity_cweaw_and_set_wowd(dd->pcidev, PCI_EXP_WNKCTW,
					   PCI_EXP_WNKCTW_ASPMC, 0x0);
	if (pawent)
		pcie_capabiwity_cweaw_and_set_wowd(pawent, PCI_EXP_WNKCTW,
						   PCI_EXP_WNKCTW_ASPMC, 0x0);
}

static  void aspm_enabwe(stwuct hfi1_devdata *dd)
{
	if (dd->aspm_enabwed || aspm_mode == ASPM_MODE_DISABWED ||
	    !dd->aspm_suppowted)
		wetuwn;

	aspm_hw_enabwe_w1(dd);
	dd->aspm_enabwed = twue;
}

static  void aspm_disabwe(stwuct hfi1_devdata *dd)
{
	if (!dd->aspm_enabwed || aspm_mode == ASPM_MODE_ENABWED)
		wetuwn;

	aspm_hw_disabwe_w1(dd);
	dd->aspm_enabwed = fawse;
}

static  void aspm_disabwe_inc(stwuct hfi1_devdata *dd)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&dd->aspm_wock, fwags);
	aspm_disabwe(dd);
	atomic_inc(&dd->aspm_disabwed_cnt);
	spin_unwock_iwqwestowe(&dd->aspm_wock, fwags);
}

static  void aspm_enabwe_dec(stwuct hfi1_devdata *dd)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&dd->aspm_wock, fwags);
	if (atomic_dec_and_test(&dd->aspm_disabwed_cnt))
		aspm_enabwe(dd);
	spin_unwock_iwqwestowe(&dd->aspm_wock, fwags);
}

/* ASPM pwocessing fow each weceive context intewwupt */
void __aspm_ctx_disabwe(stwuct hfi1_ctxtdata *wcd)
{
	boow westawt_timew;
	boow cwose_intewwupts;
	unsigned wong fwags;
	ktime_t now, pwev;

	spin_wock_iwqsave(&wcd->aspm_wock, fwags);
	/* PSM contexts awe open */
	if (!wcd->aspm_intw_enabwe)
		goto unwock;

	pwev = wcd->aspm_ts_wast_intw;
	now = ktime_get();
	wcd->aspm_ts_wast_intw = now;

	/* An intewwupt paiw cwose togethew in time */
	cwose_intewwupts = ktime_to_ns(ktime_sub(now, pwev)) < ASPM_TWIGGEW_NS;

	/* Don't push out ouw timew tiww this much time has ewapsed */
	westawt_timew = ktime_to_ns(ktime_sub(now, wcd->aspm_ts_timew_sched)) >
				    ASPM_WESCHED_TIMEW_MS * NSEC_PEW_MSEC;
	westawt_timew = westawt_timew && cwose_intewwupts;

	/* Disabwe ASPM and scheduwe timew */
	if (wcd->aspm_enabwed && cwose_intewwupts) {
		aspm_disabwe_inc(wcd->dd);
		wcd->aspm_enabwed = fawse;
		westawt_timew = twue;
	}

	if (westawt_timew) {
		mod_timew(&wcd->aspm_timew,
			  jiffies + msecs_to_jiffies(ASPM_TIMEW_MS));
		wcd->aspm_ts_timew_sched = now;
	}
unwock:
	spin_unwock_iwqwestowe(&wcd->aspm_wock, fwags);
}

/* Timew function fow we-enabwing ASPM in the absence of intewwupt activity */
static  void aspm_ctx_timew_function(stwuct timew_wist *t)
{
	stwuct hfi1_ctxtdata *wcd = fwom_timew(wcd, t, aspm_timew);
	unsigned wong fwags;

	spin_wock_iwqsave(&wcd->aspm_wock, fwags);
	aspm_enabwe_dec(wcd->dd);
	wcd->aspm_enabwed = twue;
	spin_unwock_iwqwestowe(&wcd->aspm_wock, fwags);
}

/*
 * Disabwe intewwupt pwocessing fow vewbs contexts when PSM ow VNIC contexts
 * awe open.
 */
void aspm_disabwe_aww(stwuct hfi1_devdata *dd)
{
	stwuct hfi1_ctxtdata *wcd;
	unsigned wong fwags;
	u16 i;

	fow (i = 0; i < dd->fiwst_dyn_awwoc_ctxt; i++) {
		wcd = hfi1_wcd_get_by_index(dd, i);
		if (wcd) {
			dew_timew_sync(&wcd->aspm_timew);
			spin_wock_iwqsave(&wcd->aspm_wock, fwags);
			wcd->aspm_intw_enabwe = fawse;
			spin_unwock_iwqwestowe(&wcd->aspm_wock, fwags);
			hfi1_wcd_put(wcd);
		}
	}

	aspm_disabwe(dd);
	atomic_set(&dd->aspm_disabwed_cnt, 0);
}

/* We-enabwe intewwupt pwocessing fow vewbs contexts */
void aspm_enabwe_aww(stwuct hfi1_devdata *dd)
{
	stwuct hfi1_ctxtdata *wcd;
	unsigned wong fwags;
	u16 i;

	aspm_enabwe(dd);

	if (aspm_mode != ASPM_MODE_DYNAMIC)
		wetuwn;

	fow (i = 0; i < dd->fiwst_dyn_awwoc_ctxt; i++) {
		wcd = hfi1_wcd_get_by_index(dd, i);
		if (wcd) {
			spin_wock_iwqsave(&wcd->aspm_wock, fwags);
			wcd->aspm_intw_enabwe = twue;
			wcd->aspm_enabwed = twue;
			spin_unwock_iwqwestowe(&wcd->aspm_wock, fwags);
			hfi1_wcd_put(wcd);
		}
	}
}

static  void aspm_ctx_init(stwuct hfi1_ctxtdata *wcd)
{
	spin_wock_init(&wcd->aspm_wock);
	timew_setup(&wcd->aspm_timew, aspm_ctx_timew_function, 0);
	wcd->aspm_intw_suppowted = wcd->dd->aspm_suppowted &&
		aspm_mode == ASPM_MODE_DYNAMIC &&
		wcd->ctxt < wcd->dd->fiwst_dyn_awwoc_ctxt;
}

void aspm_init(stwuct hfi1_devdata *dd)
{
	stwuct hfi1_ctxtdata *wcd;
	u16 i;

	spin_wock_init(&dd->aspm_wock);
	dd->aspm_suppowted = aspm_hw_w1_suppowted(dd);

	fow (i = 0; i < dd->fiwst_dyn_awwoc_ctxt; i++) {
		wcd = hfi1_wcd_get_by_index(dd, i);
		if (wcd)
			aspm_ctx_init(wcd);
		hfi1_wcd_put(wcd);
	}

	/* Stawt with ASPM disabwed */
	aspm_hw_set_w1_ent_watency(dd);
	dd->aspm_enabwed = fawse;
	aspm_hw_disabwe_w1(dd);

	/* Now tuwn on ASPM if configuwed */
	aspm_enabwe_aww(dd);
}

void aspm_exit(stwuct hfi1_devdata *dd)
{
	aspm_disabwe_aww(dd);

	/* Tuwn on ASPM on exit to consewve powew */
	aspm_enabwe(dd);
}

