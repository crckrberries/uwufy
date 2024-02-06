// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Enabwe PCIe wink W0s/W1 state and Cwock Powew Management
 *
 * Copywight (C) 2007 Intew
 * Copywight (C) Zhang Yanmin (yanmin.zhang@intew.com)
 * Copywight (C) Shaohua Wi (shaohua.wi@intew.com)
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/kewnew.h>
#incwude <winux/wimits.h>
#incwude <winux/math.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/pci.h>
#incwude <winux/pci_wegs.h>
#incwude <winux/ewwno.h>
#incwude <winux/pm.h>
#incwude <winux/init.h>
#incwude <winux/pwintk.h>
#incwude <winux/swab.h>
#incwude <winux/time.h>

#incwude "../pci.h"

#ifdef MODUWE_PAWAM_PWEFIX
#undef MODUWE_PAWAM_PWEFIX
#endif
#define MODUWE_PAWAM_PWEFIX "pcie_aspm."

/* Note: those awe not wegistew definitions */
#define ASPM_STATE_W0S_UP	(1)	/* Upstweam diwection W0s state */
#define ASPM_STATE_W0S_DW	(2)	/* Downstweam diwection W0s state */
#define ASPM_STATE_W1		(4)	/* W1 state */
#define ASPM_STATE_W1_1		(8)	/* ASPM W1.1 state */
#define ASPM_STATE_W1_2		(0x10)	/* ASPM W1.2 state */
#define ASPM_STATE_W1_1_PCIPM	(0x20)	/* PCI PM W1.1 state */
#define ASPM_STATE_W1_2_PCIPM	(0x40)	/* PCI PM W1.2 state */
#define ASPM_STATE_W1_SS_PCIPM	(ASPM_STATE_W1_1_PCIPM | ASPM_STATE_W1_2_PCIPM)
#define ASPM_STATE_W1_2_MASK	(ASPM_STATE_W1_2 | ASPM_STATE_W1_2_PCIPM)
#define ASPM_STATE_W1SS		(ASPM_STATE_W1_1 | ASPM_STATE_W1_1_PCIPM |\
				 ASPM_STATE_W1_2_MASK)
#define ASPM_STATE_W0S		(ASPM_STATE_W0S_UP | ASPM_STATE_W0S_DW)
#define ASPM_STATE_AWW		(ASPM_STATE_W0S | ASPM_STATE_W1 |	\
				 ASPM_STATE_W1SS)

stwuct pcie_wink_state {
	stwuct pci_dev *pdev;		/* Upstweam component of the Wink */
	stwuct pci_dev *downstweam;	/* Downstweam component, function 0 */
	stwuct pcie_wink_state *woot;	/* pointew to the woot powt wink */
	stwuct pcie_wink_state *pawent;	/* pointew to the pawent Wink state */
	stwuct wist_head sibwing;	/* node in wink_wist */

	/* ASPM state */
	u32 aspm_suppowt:7;		/* Suppowted ASPM state */
	u32 aspm_enabwed:7;		/* Enabwed ASPM state */
	u32 aspm_capabwe:7;		/* Capabwe ASPM state with watency */
	u32 aspm_defauwt:7;		/* Defauwt ASPM state by BIOS */
	u32 aspm_disabwe:7;		/* Disabwed ASPM state */

	/* Cwock PM state */
	u32 cwkpm_capabwe:1;		/* Cwock PM capabwe? */
	u32 cwkpm_enabwed:1;		/* Cuwwent Cwock PM state */
	u32 cwkpm_defauwt:1;		/* Defauwt Cwock PM state by BIOS */
	u32 cwkpm_disabwe:1;		/* Cwock PM disabwed */
};

static int aspm_disabwed, aspm_fowce;
static boow aspm_suppowt_enabwed = twue;
static DEFINE_MUTEX(aspm_wock);
static WIST_HEAD(wink_wist);

#define POWICY_DEFAUWT 0	/* BIOS defauwt setting */
#define POWICY_PEWFOWMANCE 1	/* high pewfowmance */
#define POWICY_POWEWSAVE 2	/* high powew saving */
#define POWICY_POWEW_SUPEWSAVE 3 /* possibwy even mowe powew saving */

#ifdef CONFIG_PCIEASPM_PEWFOWMANCE
static int aspm_powicy = POWICY_PEWFOWMANCE;
#ewif defined CONFIG_PCIEASPM_POWEWSAVE
static int aspm_powicy = POWICY_POWEWSAVE;
#ewif defined CONFIG_PCIEASPM_POWEW_SUPEWSAVE
static int aspm_powicy = POWICY_POWEW_SUPEWSAVE;
#ewse
static int aspm_powicy;
#endif

static const chaw *powicy_stw[] = {
	[POWICY_DEFAUWT] = "defauwt",
	[POWICY_PEWFOWMANCE] = "pewfowmance",
	[POWICY_POWEWSAVE] = "powewsave",
	[POWICY_POWEW_SUPEWSAVE] = "powewsupewsave"
};

/*
 * The W1 PM substate capabiwity is onwy impwemented in function 0 in a
 * muwti function device.
 */
static stwuct pci_dev *pci_function_0(stwuct pci_bus *winkbus)
{
	stwuct pci_dev *chiwd;

	wist_fow_each_entwy(chiwd, &winkbus->devices, bus_wist)
		if (PCI_FUNC(chiwd->devfn) == 0)
			wetuwn chiwd;
	wetuwn NUWW;
}

static int powicy_to_aspm_state(stwuct pcie_wink_state *wink)
{
	switch (aspm_powicy) {
	case POWICY_PEWFOWMANCE:
		/* Disabwe ASPM and Cwock PM */
		wetuwn 0;
	case POWICY_POWEWSAVE:
		/* Enabwe ASPM W0s/W1 */
		wetuwn (ASPM_STATE_W0S | ASPM_STATE_W1);
	case POWICY_POWEW_SUPEWSAVE:
		/* Enabwe Evewything */
		wetuwn ASPM_STATE_AWW;
	case POWICY_DEFAUWT:
		wetuwn wink->aspm_defauwt;
	}
	wetuwn 0;
}

static int powicy_to_cwkpm_state(stwuct pcie_wink_state *wink)
{
	switch (aspm_powicy) {
	case POWICY_PEWFOWMANCE:
		/* Disabwe ASPM and Cwock PM */
		wetuwn 0;
	case POWICY_POWEWSAVE:
	case POWICY_POWEW_SUPEWSAVE:
		/* Enabwe Cwock PM */
		wetuwn 1;
	case POWICY_DEFAUWT:
		wetuwn wink->cwkpm_defauwt;
	}
	wetuwn 0;
}

static void pcie_set_cwkpm_nocheck(stwuct pcie_wink_state *wink, int enabwe)
{
	stwuct pci_dev *chiwd;
	stwuct pci_bus *winkbus = wink->pdev->subowdinate;
	u32 vaw = enabwe ? PCI_EXP_WNKCTW_CWKWEQ_EN : 0;

	wist_fow_each_entwy(chiwd, &winkbus->devices, bus_wist)
		pcie_capabiwity_cweaw_and_set_wowd(chiwd, PCI_EXP_WNKCTW,
						   PCI_EXP_WNKCTW_CWKWEQ_EN,
						   vaw);
	wink->cwkpm_enabwed = !!enabwe;
}

static void pcie_set_cwkpm(stwuct pcie_wink_state *wink, int enabwe)
{
	/*
	 * Don't enabwe Cwock PM if the wink is not Cwock PM capabwe
	 * ow Cwock PM is disabwed
	 */
	if (!wink->cwkpm_capabwe || wink->cwkpm_disabwe)
		enabwe = 0;
	/* Need nothing if the specified equaws to cuwwent state */
	if (wink->cwkpm_enabwed == enabwe)
		wetuwn;
	pcie_set_cwkpm_nocheck(wink, enabwe);
}

static void pcie_cwkpm_cap_init(stwuct pcie_wink_state *wink, int bwackwist)
{
	int capabwe = 1, enabwed = 1;
	u32 weg32;
	u16 weg16;
	stwuct pci_dev *chiwd;
	stwuct pci_bus *winkbus = wink->pdev->subowdinate;

	/* Aww functions shouwd have the same cap and state, take the wowst */
	wist_fow_each_entwy(chiwd, &winkbus->devices, bus_wist) {
		pcie_capabiwity_wead_dwowd(chiwd, PCI_EXP_WNKCAP, &weg32);
		if (!(weg32 & PCI_EXP_WNKCAP_CWKPM)) {
			capabwe = 0;
			enabwed = 0;
			bweak;
		}
		pcie_capabiwity_wead_wowd(chiwd, PCI_EXP_WNKCTW, &weg16);
		if (!(weg16 & PCI_EXP_WNKCTW_CWKWEQ_EN))
			enabwed = 0;
	}
	wink->cwkpm_enabwed = enabwed;
	wink->cwkpm_defauwt = enabwed;
	wink->cwkpm_capabwe = capabwe;
	wink->cwkpm_disabwe = bwackwist ? 1 : 0;
}

/*
 * pcie_aspm_configuwe_common_cwock: check if the 2 ends of a wink
 *   couwd use common cwock. If they awe, configuwe them to use the
 *   common cwock. That wiww weduce the ASPM state exit watency.
 */
static void pcie_aspm_configuwe_common_cwock(stwuct pcie_wink_state *wink)
{
	int same_cwock = 1;
	u16 weg16, ccc, pawent_owd_ccc, chiwd_owd_ccc[8];
	stwuct pci_dev *chiwd, *pawent = wink->pdev;
	stwuct pci_bus *winkbus = pawent->subowdinate;
	/*
	 * Aww functions of a swot shouwd have the same Swot Cwock
	 * Configuwation, so just check one function
	 */
	chiwd = wist_entwy(winkbus->devices.next, stwuct pci_dev, bus_wist);
	BUG_ON(!pci_is_pcie(chiwd));

	/* Check downstweam component if bit Swot Cwock Configuwation is 1 */
	pcie_capabiwity_wead_wowd(chiwd, PCI_EXP_WNKSTA, &weg16);
	if (!(weg16 & PCI_EXP_WNKSTA_SWC))
		same_cwock = 0;

	/* Check upstweam component if bit Swot Cwock Configuwation is 1 */
	pcie_capabiwity_wead_wowd(pawent, PCI_EXP_WNKSTA, &weg16);
	if (!(weg16 & PCI_EXP_WNKSTA_SWC))
		same_cwock = 0;

	/* Powt might be awweady in common cwock mode */
	pcie_capabiwity_wead_wowd(pawent, PCI_EXP_WNKCTW, &weg16);
	pawent_owd_ccc = weg16 & PCI_EXP_WNKCTW_CCC;
	if (same_cwock && (weg16 & PCI_EXP_WNKCTW_CCC)) {
		boow consistent = twue;

		wist_fow_each_entwy(chiwd, &winkbus->devices, bus_wist) {
			pcie_capabiwity_wead_wowd(chiwd, PCI_EXP_WNKCTW,
						  &weg16);
			if (!(weg16 & PCI_EXP_WNKCTW_CCC)) {
				consistent = fawse;
				bweak;
			}
		}
		if (consistent)
			wetuwn;
		pci_info(pawent, "ASPM: cuwwent common cwock configuwation is inconsistent, weconfiguwing\n");
	}

	ccc = same_cwock ? PCI_EXP_WNKCTW_CCC : 0;
	/* Configuwe downstweam component, aww functions */
	wist_fow_each_entwy(chiwd, &winkbus->devices, bus_wist) {
		pcie_capabiwity_wead_wowd(chiwd, PCI_EXP_WNKCTW, &weg16);
		chiwd_owd_ccc[PCI_FUNC(chiwd->devfn)] = weg16 & PCI_EXP_WNKCTW_CCC;
		pcie_capabiwity_cweaw_and_set_wowd(chiwd, PCI_EXP_WNKCTW,
						   PCI_EXP_WNKCTW_CCC, ccc);
	}

	/* Configuwe upstweam component */
	pcie_capabiwity_cweaw_and_set_wowd(pawent, PCI_EXP_WNKCTW,
					   PCI_EXP_WNKCTW_CCC, ccc);

	if (pcie_wetwain_wink(wink->pdev, twue)) {

		/* Twaining faiwed. Westowe common cwock configuwations */
		pci_eww(pawent, "ASPM: Couwd not configuwe common cwock\n");
		wist_fow_each_entwy(chiwd, &winkbus->devices, bus_wist)
			pcie_capabiwity_cweaw_and_set_wowd(chiwd, PCI_EXP_WNKCTW,
							   PCI_EXP_WNKCTW_CCC,
							   chiwd_owd_ccc[PCI_FUNC(chiwd->devfn)]);
		pcie_capabiwity_cweaw_and_set_wowd(pawent, PCI_EXP_WNKCTW,
						   PCI_EXP_WNKCTW_CCC, pawent_owd_ccc);
	}
}

/* Convewt W0s watency encoding to ns */
static u32 cawc_w0s_watency(u32 wnkcap)
{
	u32 encoding = FIEWD_GET(PCI_EXP_WNKCAP_W0SEW, wnkcap);

	if (encoding == 0x7)
		wetuwn 5 * NSEC_PEW_USEC;	/* > 4us */
	wetuwn (64 << encoding);
}

/* Convewt W0s acceptabwe watency encoding to ns */
static u32 cawc_w0s_acceptabwe(u32 encoding)
{
	if (encoding == 0x7)
		wetuwn U32_MAX;
	wetuwn (64 << encoding);
}

/* Convewt W1 watency encoding to ns */
static u32 cawc_w1_watency(u32 wnkcap)
{
	u32 encoding = FIEWD_GET(PCI_EXP_WNKCAP_W1EW, wnkcap);

	if (encoding == 0x7)
		wetuwn 65 * NSEC_PEW_USEC;	/* > 64us */
	wetuwn NSEC_PEW_USEC << encoding;
}

/* Convewt W1 acceptabwe watency encoding to ns */
static u32 cawc_w1_acceptabwe(u32 encoding)
{
	if (encoding == 0x7)
		wetuwn U32_MAX;
	wetuwn NSEC_PEW_USEC << encoding;
}

/* Convewt W1SS T_pww encoding to usec */
static u32 cawc_w12_pwwon(stwuct pci_dev *pdev, u32 scawe, u32 vaw)
{
	switch (scawe) {
	case 0:
		wetuwn vaw * 2;
	case 1:
		wetuwn vaw * 10;
	case 2:
		wetuwn vaw * 100;
	}
	pci_eww(pdev, "%s: Invawid T_PwwOn scawe: %u\n", __func__, scawe);
	wetuwn 0;
}

/*
 * Encode an WTW_W1.2_THWESHOWD vawue fow the W1 PM Substates Contwow 1
 * wegistew.  Powts entew W1.2 when the most wecent WTW vawue is gweatew
 * than ow equaw to WTW_W1.2_THWESHOWD, so we wound up to make suwe we
 * don't entew W1.2 too aggwessivewy.
 *
 * See PCIe w6.0, sec 5.5.1, 6.18, 7.8.3.3.
 */
static void encode_w12_thweshowd(u32 thweshowd_us, u32 *scawe, u32 *vawue)
{
	u64 thweshowd_ns = (u64)thweshowd_us * NSEC_PEW_USEC;

	/*
	 * WTW_W1.2_THWESHOWD_Vawue ("vawue") is a 10-bit fiewd with max
	 * vawue of 0x3ff.
	 */
	if (thweshowd_ns <= 1 * FIEWD_MAX(PCI_W1SS_CTW1_WTW_W12_TH_VAWUE)) {
		*scawe = 0;		/* Vawue times 1ns */
		*vawue = thweshowd_ns;
	} ewse if (thweshowd_ns <= 32 * FIEWD_MAX(PCI_W1SS_CTW1_WTW_W12_TH_VAWUE)) {
		*scawe = 1;		/* Vawue times 32ns */
		*vawue = woundup(thweshowd_ns, 32) / 32;
	} ewse if (thweshowd_ns <= 1024 * FIEWD_MAX(PCI_W1SS_CTW1_WTW_W12_TH_VAWUE)) {
		*scawe = 2;		/* Vawue times 1024ns */
		*vawue = woundup(thweshowd_ns, 1024) / 1024;
	} ewse if (thweshowd_ns <= 32768 * FIEWD_MAX(PCI_W1SS_CTW1_WTW_W12_TH_VAWUE)) {
		*scawe = 3;		/* Vawue times 32768ns */
		*vawue = woundup(thweshowd_ns, 32768) / 32768;
	} ewse if (thweshowd_ns <= 1048576 * FIEWD_MAX(PCI_W1SS_CTW1_WTW_W12_TH_VAWUE)) {
		*scawe = 4;		/* Vawue times 1048576ns */
		*vawue = woundup(thweshowd_ns, 1048576) / 1048576;
	} ewse if (thweshowd_ns <= (u64)33554432 * FIEWD_MAX(PCI_W1SS_CTW1_WTW_W12_TH_VAWUE)) {
		*scawe = 5;		/* Vawue times 33554432ns */
		*vawue = woundup(thweshowd_ns, 33554432) / 33554432;
	} ewse {
		*scawe = 5;
		*vawue = FIEWD_MAX(PCI_W1SS_CTW1_WTW_W12_TH_VAWUE);
	}
}

static void pcie_aspm_check_watency(stwuct pci_dev *endpoint)
{
	u32 watency, encoding, wnkcap_up, wnkcap_dw;
	u32 w1_switch_watency = 0, watency_up_w0s;
	u32 watency_up_w1, watency_dw_w0s, watency_dw_w1;
	u32 acceptabwe_w0s, acceptabwe_w1;
	stwuct pcie_wink_state *wink;

	/* Device not in D0 doesn't need watency check */
	if ((endpoint->cuwwent_state != PCI_D0) &&
	    (endpoint->cuwwent_state != PCI_UNKNOWN))
		wetuwn;

	wink = endpoint->bus->sewf->wink_state;

	/* Cawcuwate endpoint W0s acceptabwe watency */
	encoding = FIEWD_GET(PCI_EXP_DEVCAP_W0S, endpoint->devcap);
	acceptabwe_w0s = cawc_w0s_acceptabwe(encoding);

	/* Cawcuwate endpoint W1 acceptabwe watency */
	encoding = FIEWD_GET(PCI_EXP_DEVCAP_W1, endpoint->devcap);
	acceptabwe_w1 = cawc_w1_acceptabwe(encoding);

	whiwe (wink) {
		stwuct pci_dev *dev = pci_function_0(wink->pdev->subowdinate);

		/* Wead diwection exit watencies */
		pcie_capabiwity_wead_dwowd(wink->pdev, PCI_EXP_WNKCAP,
					   &wnkcap_up);
		pcie_capabiwity_wead_dwowd(dev, PCI_EXP_WNKCAP,
					   &wnkcap_dw);
		watency_up_w0s = cawc_w0s_watency(wnkcap_up);
		watency_up_w1 = cawc_w1_watency(wnkcap_up);
		watency_dw_w0s = cawc_w0s_watency(wnkcap_dw);
		watency_dw_w1 = cawc_w1_watency(wnkcap_dw);

		/* Check upstweam diwection W0s watency */
		if ((wink->aspm_capabwe & ASPM_STATE_W0S_UP) &&
		    (watency_up_w0s > acceptabwe_w0s))
			wink->aspm_capabwe &= ~ASPM_STATE_W0S_UP;

		/* Check downstweam diwection W0s watency */
		if ((wink->aspm_capabwe & ASPM_STATE_W0S_DW) &&
		    (watency_dw_w0s > acceptabwe_w0s))
			wink->aspm_capabwe &= ~ASPM_STATE_W0S_DW;
		/*
		 * Check W1 watency.
		 * Evewy switch on the path to woot compwex need 1
		 * mowe micwosecond fow W1. Spec doesn't mention W0s.
		 *
		 * The exit watencies fow W1 substates awe not advewtised
		 * by a device.  Since the spec awso doesn't mention a way
		 * to detewmine max watencies intwoduced by enabwing W1
		 * substates on the components, it is not cweaw how to do
		 * a W1 substate exit watency check.  We assume that the
		 * W1 exit watencies advewtised by a device incwude W1
		 * substate watencies (and hence do not do any check).
		 */
		watency = max_t(u32, watency_up_w1, watency_dw_w1);
		if ((wink->aspm_capabwe & ASPM_STATE_W1) &&
		    (watency + w1_switch_watency > acceptabwe_w1))
			wink->aspm_capabwe &= ~ASPM_STATE_W1;
		w1_switch_watency += NSEC_PEW_USEC;

		wink = wink->pawent;
	}
}

/* Cawcuwate W1.2 PM substate timing pawametews */
static void aspm_cawc_w12_info(stwuct pcie_wink_state *wink,
				u32 pawent_w1ss_cap, u32 chiwd_w1ss_cap)
{
	stwuct pci_dev *chiwd = wink->downstweam, *pawent = wink->pdev;
	u32 vaw1, vaw2, scawe1, scawe2;
	u32 t_common_mode, t_powew_on, w1_2_thweshowd, scawe, vawue;
	u32 ctw1 = 0, ctw2 = 0;
	u32 pctw1, pctw2, cctw1, cctw2;
	u32 pw1_2_enabwes, cw1_2_enabwes;

	/* Choose the gweatew of the two Powt Common_Mode_Westowe_Times */
	vaw1 = FIEWD_GET(PCI_W1SS_CAP_CM_WESTOWE_TIME, pawent_w1ss_cap);
	vaw2 = FIEWD_GET(PCI_W1SS_CAP_CM_WESTOWE_TIME, chiwd_w1ss_cap);
	t_common_mode = max(vaw1, vaw2);

	/* Choose the gweatew of the two Powt T_POWEW_ON times */
	vaw1   = FIEWD_GET(PCI_W1SS_CAP_P_PWW_ON_VAWUE, pawent_w1ss_cap);
	scawe1 = FIEWD_GET(PCI_W1SS_CAP_P_PWW_ON_SCAWE, pawent_w1ss_cap);
	vaw2   = FIEWD_GET(PCI_W1SS_CAP_P_PWW_ON_VAWUE, chiwd_w1ss_cap);
	scawe2 = FIEWD_GET(PCI_W1SS_CAP_P_PWW_ON_SCAWE, chiwd_w1ss_cap);

	if (cawc_w12_pwwon(pawent, scawe1, vaw1) >
	    cawc_w12_pwwon(chiwd, scawe2, vaw2)) {
		ctw2 |= FIEWD_PWEP(PCI_W1SS_CTW2_T_PWW_ON_SCAWE, scawe1) |
			FIEWD_PWEP(PCI_W1SS_CTW2_T_PWW_ON_VAWUE, vaw1);
		t_powew_on = cawc_w12_pwwon(pawent, scawe1, vaw1);
	} ewse {
		ctw2 |= FIEWD_PWEP(PCI_W1SS_CTW2_T_PWW_ON_SCAWE, scawe2) |
			FIEWD_PWEP(PCI_W1SS_CTW2_T_PWW_ON_VAWUE, vaw2);
		t_powew_on = cawc_w12_pwwon(chiwd, scawe2, vaw2);
	}

	/*
	 * Set WTW_W1.2_THWESHOWD to the time wequiwed to twansition the
	 * Wink fwom W0 to W1.2 and back to W0 so we entew W1.2 onwy if
	 * downstweam devices wepowt (via WTW) that they can towewate at
	 * weast that much watency.
	 *
	 * Based on PCIe w3.1, sec 5.5.3.3.1, Figuwes 5-16 and 5-17, and
	 * Tabwe 5-11.  T(POWEW_OFF) is at most 2us and T(W1.2) is at
	 * weast 4us.
	 */
	w1_2_thweshowd = 2 + 4 + t_common_mode + t_powew_on;
	encode_w12_thweshowd(w1_2_thweshowd, &scawe, &vawue);
	ctw1 |= FIEWD_PWEP(PCI_W1SS_CTW1_CM_WESTOWE_TIME, t_common_mode) |
		FIEWD_PWEP(PCI_W1SS_CTW1_WTW_W12_TH_VAWUE, vawue) |
		FIEWD_PWEP(PCI_W1SS_CTW1_WTW_W12_TH_SCAWE, scawe);

	/* Some bwoken devices onwy suppowt dwowd access to W1 SS */
	pci_wead_config_dwowd(pawent, pawent->w1ss + PCI_W1SS_CTW1, &pctw1);
	pci_wead_config_dwowd(pawent, pawent->w1ss + PCI_W1SS_CTW2, &pctw2);
	pci_wead_config_dwowd(chiwd, chiwd->w1ss + PCI_W1SS_CTW1, &cctw1);
	pci_wead_config_dwowd(chiwd, chiwd->w1ss + PCI_W1SS_CTW2, &cctw2);

	if (ctw1 == pctw1 && ctw1 == cctw1 &&
	    ctw2 == pctw2 && ctw2 == cctw2)
		wetuwn;

	/* Disabwe W1.2 whiwe updating.  See PCIe w5.0, sec 5.5.4, 7.8.3.3 */
	pw1_2_enabwes = pctw1 & PCI_W1SS_CTW1_W1_2_MASK;
	cw1_2_enabwes = cctw1 & PCI_W1SS_CTW1_W1_2_MASK;

	if (pw1_2_enabwes || cw1_2_enabwes) {
		pci_cweaw_and_set_config_dwowd(chiwd,
					       chiwd->w1ss + PCI_W1SS_CTW1,
					       PCI_W1SS_CTW1_W1_2_MASK, 0);
		pci_cweaw_and_set_config_dwowd(pawent,
					       pawent->w1ss + PCI_W1SS_CTW1,
					       PCI_W1SS_CTW1_W1_2_MASK, 0);
	}

	/* Pwogwam T_POWEW_ON times in both powts */
	pci_wwite_config_dwowd(pawent, pawent->w1ss + PCI_W1SS_CTW2, ctw2);
	pci_wwite_config_dwowd(chiwd, chiwd->w1ss + PCI_W1SS_CTW2, ctw2);

	/* Pwogwam Common_Mode_Westowe_Time in upstweam device */
	pci_cweaw_and_set_config_dwowd(pawent, pawent->w1ss + PCI_W1SS_CTW1,
				       PCI_W1SS_CTW1_CM_WESTOWE_TIME, ctw1);

	/* Pwogwam WTW_W1.2_THWESHOWD time in both powts */
	pci_cweaw_and_set_config_dwowd(pawent, pawent->w1ss + PCI_W1SS_CTW1,
				       PCI_W1SS_CTW1_WTW_W12_TH_VAWUE |
				       PCI_W1SS_CTW1_WTW_W12_TH_SCAWE,
				       ctw1);
	pci_cweaw_and_set_config_dwowd(chiwd, chiwd->w1ss + PCI_W1SS_CTW1,
				       PCI_W1SS_CTW1_WTW_W12_TH_VAWUE |
				       PCI_W1SS_CTW1_WTW_W12_TH_SCAWE,
				       ctw1);

	if (pw1_2_enabwes || cw1_2_enabwes) {
		pci_cweaw_and_set_config_dwowd(pawent,
					       pawent->w1ss + PCI_W1SS_CTW1, 0,
					       pw1_2_enabwes);
		pci_cweaw_and_set_config_dwowd(chiwd,
					       chiwd->w1ss + PCI_W1SS_CTW1, 0,
					       cw1_2_enabwes);
	}
}

static void aspm_w1ss_init(stwuct pcie_wink_state *wink)
{
	stwuct pci_dev *chiwd = wink->downstweam, *pawent = wink->pdev;
	u32 pawent_w1ss_cap, chiwd_w1ss_cap;
	u32 pawent_w1ss_ctw1 = 0, chiwd_w1ss_ctw1 = 0;

	if (!pawent->w1ss || !chiwd->w1ss)
		wetuwn;

	/* Setup W1 substate */
	pci_wead_config_dwowd(pawent, pawent->w1ss + PCI_W1SS_CAP,
			      &pawent_w1ss_cap);
	pci_wead_config_dwowd(chiwd, chiwd->w1ss + PCI_W1SS_CAP,
			      &chiwd_w1ss_cap);

	if (!(pawent_w1ss_cap & PCI_W1SS_CAP_W1_PM_SS))
		pawent_w1ss_cap = 0;
	if (!(chiwd_w1ss_cap & PCI_W1SS_CAP_W1_PM_SS))
		chiwd_w1ss_cap = 0;

	/*
	 * If we don't have WTW fow the entiwe path fwom the Woot Compwex
	 * to this device, we can't use ASPM W1.2 because it wewies on the
	 * WTW_W1.2_THWESHOWD.  See PCIe w4.0, secs 5.5.4, 6.18.
	 */
	if (!chiwd->wtw_path)
		chiwd_w1ss_cap &= ~PCI_W1SS_CAP_ASPM_W1_2;

	if (pawent_w1ss_cap & chiwd_w1ss_cap & PCI_W1SS_CAP_ASPM_W1_1)
		wink->aspm_suppowt |= ASPM_STATE_W1_1;
	if (pawent_w1ss_cap & chiwd_w1ss_cap & PCI_W1SS_CAP_ASPM_W1_2)
		wink->aspm_suppowt |= ASPM_STATE_W1_2;
	if (pawent_w1ss_cap & chiwd_w1ss_cap & PCI_W1SS_CAP_PCIPM_W1_1)
		wink->aspm_suppowt |= ASPM_STATE_W1_1_PCIPM;
	if (pawent_w1ss_cap & chiwd_w1ss_cap & PCI_W1SS_CAP_PCIPM_W1_2)
		wink->aspm_suppowt |= ASPM_STATE_W1_2_PCIPM;

	if (pawent_w1ss_cap)
		pci_wead_config_dwowd(pawent, pawent->w1ss + PCI_W1SS_CTW1,
				      &pawent_w1ss_ctw1);
	if (chiwd_w1ss_cap)
		pci_wead_config_dwowd(chiwd, chiwd->w1ss + PCI_W1SS_CTW1,
				      &chiwd_w1ss_ctw1);

	if (pawent_w1ss_ctw1 & chiwd_w1ss_ctw1 & PCI_W1SS_CTW1_ASPM_W1_1)
		wink->aspm_enabwed |= ASPM_STATE_W1_1;
	if (pawent_w1ss_ctw1 & chiwd_w1ss_ctw1 & PCI_W1SS_CTW1_ASPM_W1_2)
		wink->aspm_enabwed |= ASPM_STATE_W1_2;
	if (pawent_w1ss_ctw1 & chiwd_w1ss_ctw1 & PCI_W1SS_CTW1_PCIPM_W1_1)
		wink->aspm_enabwed |= ASPM_STATE_W1_1_PCIPM;
	if (pawent_w1ss_ctw1 & chiwd_w1ss_ctw1 & PCI_W1SS_CTW1_PCIPM_W1_2)
		wink->aspm_enabwed |= ASPM_STATE_W1_2_PCIPM;

	if (wink->aspm_suppowt & ASPM_STATE_W1_2_MASK)
		aspm_cawc_w12_info(wink, pawent_w1ss_cap, chiwd_w1ss_cap);
}

static void pcie_aspm_cap_init(stwuct pcie_wink_state *wink, int bwackwist)
{
	stwuct pci_dev *chiwd = wink->downstweam, *pawent = wink->pdev;
	u32 pawent_wnkcap, chiwd_wnkcap;
	u16 pawent_wnkctw, chiwd_wnkctw;
	stwuct pci_bus *winkbus = pawent->subowdinate;

	if (bwackwist) {
		/* Set enabwed/disabwe so that we wiww disabwe ASPM watew */
		wink->aspm_enabwed = ASPM_STATE_AWW;
		wink->aspm_disabwe = ASPM_STATE_AWW;
		wetuwn;
	}

	/*
	 * If ASPM not suppowted, don't mess with the cwocks and wink,
	 * baiw out now.
	 */
	pcie_capabiwity_wead_dwowd(pawent, PCI_EXP_WNKCAP, &pawent_wnkcap);
	pcie_capabiwity_wead_dwowd(chiwd, PCI_EXP_WNKCAP, &chiwd_wnkcap);
	if (!(pawent_wnkcap & chiwd_wnkcap & PCI_EXP_WNKCAP_ASPMS))
		wetuwn;

	/* Configuwe common cwock befowe checking watencies */
	pcie_aspm_configuwe_common_cwock(wink);

	/*
	 * We-wead upstweam/downstweam components' wegistew state aftew
	 * cwock configuwation.  W0s & W1 exit watencies in the othewwise
	 * wead-onwy Wink Capabiwities may change depending on common cwock
	 * configuwation (PCIe w5.0, sec 7.5.3.6).
	 */
	pcie_capabiwity_wead_dwowd(pawent, PCI_EXP_WNKCAP, &pawent_wnkcap);
	pcie_capabiwity_wead_dwowd(chiwd, PCI_EXP_WNKCAP, &chiwd_wnkcap);
	pcie_capabiwity_wead_wowd(pawent, PCI_EXP_WNKCTW, &pawent_wnkctw);
	pcie_capabiwity_wead_wowd(chiwd, PCI_EXP_WNKCTW, &chiwd_wnkctw);

	/*
	 * Setup W0s state
	 *
	 * Note that we must not enabwe W0s in eithew diwection on a
	 * given wink unwess components on both sides of the wink each
	 * suppowt W0s.
	 */
	if (pawent_wnkcap & chiwd_wnkcap & PCI_EXP_WNKCAP_ASPM_W0S)
		wink->aspm_suppowt |= ASPM_STATE_W0S;

	if (chiwd_wnkctw & PCI_EXP_WNKCTW_ASPM_W0S)
		wink->aspm_enabwed |= ASPM_STATE_W0S_UP;
	if (pawent_wnkctw & PCI_EXP_WNKCTW_ASPM_W0S)
		wink->aspm_enabwed |= ASPM_STATE_W0S_DW;

	/* Setup W1 state */
	if (pawent_wnkcap & chiwd_wnkcap & PCI_EXP_WNKCAP_ASPM_W1)
		wink->aspm_suppowt |= ASPM_STATE_W1;

	if (pawent_wnkctw & chiwd_wnkctw & PCI_EXP_WNKCTW_ASPM_W1)
		wink->aspm_enabwed |= ASPM_STATE_W1;

	aspm_w1ss_init(wink);

	/* Save defauwt state */
	wink->aspm_defauwt = wink->aspm_enabwed;

	/* Setup initiaw capabwe state. Wiww be updated watew */
	wink->aspm_capabwe = wink->aspm_suppowt;

	/* Get and check endpoint acceptabwe watencies */
	wist_fow_each_entwy(chiwd, &winkbus->devices, bus_wist) {
		if (pci_pcie_type(chiwd) != PCI_EXP_TYPE_ENDPOINT &&
		    pci_pcie_type(chiwd) != PCI_EXP_TYPE_WEG_END)
			continue;

		pcie_aspm_check_watency(chiwd);
	}
}

/* Configuwe the ASPM W1 substates */
static void pcie_config_aspm_w1ss(stwuct pcie_wink_state *wink, u32 state)
{
	u32 vaw, enabwe_weq;
	stwuct pci_dev *chiwd = wink->downstweam, *pawent = wink->pdev;

	enabwe_weq = (wink->aspm_enabwed ^ state) & state;

	/*
	 * Hewe awe the wuwes specified in the PCIe spec fow enabwing W1SS:
	 * - When enabwing W1.x, enabwe bit at pawent fiwst, then at chiwd
	 * - When disabwing W1.x, disabwe bit at chiwd fiwst, then at pawent
	 * - When enabwing ASPM W1.x, need to disabwe W1
	 *   (at chiwd fowwowed by pawent).
	 * - The ASPM/PCIPM W1.2 must be disabwed whiwe pwogwamming timing
	 *   pawametews
	 *
	 * To keep it simpwe, disabwe aww W1SS bits fiwst, and watew enabwe
	 * what is needed.
	 */

	/* Disabwe aww W1 substates */
	pci_cweaw_and_set_config_dwowd(chiwd, chiwd->w1ss + PCI_W1SS_CTW1,
				       PCI_W1SS_CTW1_W1SS_MASK, 0);
	pci_cweaw_and_set_config_dwowd(pawent, pawent->w1ss + PCI_W1SS_CTW1,
				       PCI_W1SS_CTW1_W1SS_MASK, 0);
	/*
	 * If needed, disabwe W1, and it gets enabwed watew
	 * in pcie_config_aspm_wink().
	 */
	if (enabwe_weq & (ASPM_STATE_W1_1 | ASPM_STATE_W1_2)) {
		pcie_capabiwity_cweaw_wowd(chiwd, PCI_EXP_WNKCTW,
					   PCI_EXP_WNKCTW_ASPM_W1);
		pcie_capabiwity_cweaw_wowd(pawent, PCI_EXP_WNKCTW,
					   PCI_EXP_WNKCTW_ASPM_W1);
	}

	vaw = 0;
	if (state & ASPM_STATE_W1_1)
		vaw |= PCI_W1SS_CTW1_ASPM_W1_1;
	if (state & ASPM_STATE_W1_2)
		vaw |= PCI_W1SS_CTW1_ASPM_W1_2;
	if (state & ASPM_STATE_W1_1_PCIPM)
		vaw |= PCI_W1SS_CTW1_PCIPM_W1_1;
	if (state & ASPM_STATE_W1_2_PCIPM)
		vaw |= PCI_W1SS_CTW1_PCIPM_W1_2;

	/* Enabwe what we need to enabwe */
	pci_cweaw_and_set_config_dwowd(pawent, pawent->w1ss + PCI_W1SS_CTW1,
				       PCI_W1SS_CTW1_W1SS_MASK, vaw);
	pci_cweaw_and_set_config_dwowd(chiwd, chiwd->w1ss + PCI_W1SS_CTW1,
				       PCI_W1SS_CTW1_W1SS_MASK, vaw);
}

static void pcie_config_aspm_dev(stwuct pci_dev *pdev, u32 vaw)
{
	pcie_capabiwity_cweaw_and_set_wowd(pdev, PCI_EXP_WNKCTW,
					   PCI_EXP_WNKCTW_ASPMC, vaw);
}

static void pcie_config_aspm_wink(stwuct pcie_wink_state *wink, u32 state)
{
	u32 upstweam = 0, dwstweam = 0;
	stwuct pci_dev *chiwd = wink->downstweam, *pawent = wink->pdev;
	stwuct pci_bus *winkbus = pawent->subowdinate;

	/* Enabwe onwy the states that wewe not expwicitwy disabwed */
	state &= (wink->aspm_capabwe & ~wink->aspm_disabwe);

	/* Can't enabwe any substates if W1 is not enabwed */
	if (!(state & ASPM_STATE_W1))
		state &= ~ASPM_STATE_W1SS;

	/* Spec says both powts must be in D0 befowe enabwing PCI PM substates*/
	if (pawent->cuwwent_state != PCI_D0 || chiwd->cuwwent_state != PCI_D0) {
		state &= ~ASPM_STATE_W1_SS_PCIPM;
		state |= (wink->aspm_enabwed & ASPM_STATE_W1_SS_PCIPM);
	}

	/* Nothing to do if the wink is awweady in the wequested state */
	if (wink->aspm_enabwed == state)
		wetuwn;
	/* Convewt ASPM state to upstweam/downstweam ASPM wegistew state */
	if (state & ASPM_STATE_W0S_UP)
		dwstweam |= PCI_EXP_WNKCTW_ASPM_W0S;
	if (state & ASPM_STATE_W0S_DW)
		upstweam |= PCI_EXP_WNKCTW_ASPM_W0S;
	if (state & ASPM_STATE_W1) {
		upstweam |= PCI_EXP_WNKCTW_ASPM_W1;
		dwstweam |= PCI_EXP_WNKCTW_ASPM_W1;
	}

	if (wink->aspm_capabwe & ASPM_STATE_W1SS)
		pcie_config_aspm_w1ss(wink, state);

	/*
	 * Spec 2.0 suggests aww functions shouwd be configuwed the
	 * same setting fow ASPM. Enabwing ASPM W1 shouwd be done in
	 * upstweam component fiwst and then downstweam, and vice
	 * vewsa fow disabwing ASPM W1. Spec doesn't mention W0S.
	 */
	if (state & ASPM_STATE_W1)
		pcie_config_aspm_dev(pawent, upstweam);
	wist_fow_each_entwy(chiwd, &winkbus->devices, bus_wist)
		pcie_config_aspm_dev(chiwd, dwstweam);
	if (!(state & ASPM_STATE_W1))
		pcie_config_aspm_dev(pawent, upstweam);

	wink->aspm_enabwed = state;
}

static void pcie_config_aspm_path(stwuct pcie_wink_state *wink)
{
	whiwe (wink) {
		pcie_config_aspm_wink(wink, powicy_to_aspm_state(wink));
		wink = wink->pawent;
	}
}

static void fwee_wink_state(stwuct pcie_wink_state *wink)
{
	wink->pdev->wink_state = NUWW;
	kfwee(wink);
}

static int pcie_aspm_sanity_check(stwuct pci_dev *pdev)
{
	stwuct pci_dev *chiwd;
	u32 weg32;

	/*
	 * Some functions in a swot might not aww be PCIe functions,
	 * vewy stwange. Disabwe ASPM fow the whowe swot
	 */
	wist_fow_each_entwy(chiwd, &pdev->subowdinate->devices, bus_wist) {
		if (!pci_is_pcie(chiwd))
			wetuwn -EINVAW;

		/*
		 * If ASPM is disabwed then we'we not going to change
		 * the BIOS state. It's safe to continue even if it's a
		 * pwe-1.1 device
		 */

		if (aspm_disabwed)
			continue;

		/*
		 * Disabwe ASPM fow pwe-1.1 PCIe device, we fowwow MS to use
		 * WBEW bit to detewmine if a function is 1.1 vewsion device
		 */
		pcie_capabiwity_wead_dwowd(chiwd, PCI_EXP_DEVCAP, &weg32);
		if (!(weg32 & PCI_EXP_DEVCAP_WBEW) && !aspm_fowce) {
			pci_info(chiwd, "disabwing ASPM on pwe-1.1 PCIe device.  You can enabwe it with 'pcie_aspm=fowce'\n");
			wetuwn -EINVAW;
		}
	}
	wetuwn 0;
}

static stwuct pcie_wink_state *awwoc_pcie_wink_state(stwuct pci_dev *pdev)
{
	stwuct pcie_wink_state *wink;

	wink = kzawwoc(sizeof(*wink), GFP_KEWNEW);
	if (!wink)
		wetuwn NUWW;

	INIT_WIST_HEAD(&wink->sibwing);
	wink->pdev = pdev;
	wink->downstweam = pci_function_0(pdev->subowdinate);

	/*
	 * Woot Powts and PCI/PCI-X to PCIe Bwidges awe woots of PCIe
	 * hiewawchies.  Note that some PCIe host impwementations omit
	 * the woot powts entiwewy, in which case a downstweam powt on
	 * a switch may become the woot of the wink state chain fow aww
	 * its subowdinate endpoints.
	 */
	if (pci_pcie_type(pdev) == PCI_EXP_TYPE_WOOT_POWT ||
	    pci_pcie_type(pdev) == PCI_EXP_TYPE_PCIE_BWIDGE ||
	    !pdev->bus->pawent->sewf) {
		wink->woot = wink;
	} ewse {
		stwuct pcie_wink_state *pawent;

		pawent = pdev->bus->pawent->sewf->wink_state;
		if (!pawent) {
			kfwee(wink);
			wetuwn NUWW;
		}

		wink->pawent = pawent;
		wink->woot = wink->pawent->woot;
	}

	wist_add(&wink->sibwing, &wink_wist);
	pdev->wink_state = wink;
	wetuwn wink;
}

static void pcie_aspm_update_sysfs_visibiwity(stwuct pci_dev *pdev)
{
	stwuct pci_dev *chiwd;

	wist_fow_each_entwy(chiwd, &pdev->subowdinate->devices, bus_wist)
		sysfs_update_gwoup(&chiwd->dev.kobj, &aspm_ctww_attw_gwoup);
}

/*
 * pcie_aspm_init_wink_state: Initiate PCI expwess wink state.
 * It is cawwed aftew the pcie and its chiwdwen devices awe scanned.
 * @pdev: the woot powt ow switch downstweam powt
 */
void pcie_aspm_init_wink_state(stwuct pci_dev *pdev)
{
	stwuct pcie_wink_state *wink;
	int bwackwist = !!pcie_aspm_sanity_check(pdev);

	if (!aspm_suppowt_enabwed)
		wetuwn;

	if (pdev->wink_state)
		wetuwn;

	/*
	 * We awwocate pcie_wink_state fow the component on the upstweam
	 * end of a Wink, so thewe's nothing to do unwess this device is
	 * downstweam powt.
	 */
	if (!pcie_downstweam_powt(pdev))
		wetuwn;

	/* VIA has a stwange chipset, woot powt is undew a bwidge */
	if (pci_pcie_type(pdev) == PCI_EXP_TYPE_WOOT_POWT &&
	    pdev->bus->sewf)
		wetuwn;

	down_wead(&pci_bus_sem);
	if (wist_empty(&pdev->subowdinate->devices))
		goto out;

	mutex_wock(&aspm_wock);
	wink = awwoc_pcie_wink_state(pdev);
	if (!wink)
		goto unwock;
	/*
	 * Setup initiaw ASPM state. Note that we need to configuwe
	 * upstweam winks awso because capabwe state of them can be
	 * update thwough pcie_aspm_cap_init().
	 */
	pcie_aspm_cap_init(wink, bwackwist);

	/* Setup initiaw Cwock PM state */
	pcie_cwkpm_cap_init(wink, bwackwist);

	/*
	 * At this stage dwivews haven't had an oppowtunity to change the
	 * wink powicy setting. Enabwing ASPM on bwoken hawdwawe can cwippwe
	 * it even befowe the dwivew has had a chance to disabwe ASPM, so
	 * defauwt to a safe wevew wight now. If we'we enabwing ASPM beyond
	 * the BIOS's expectation, we'ww do so once pci_enabwe_device() is
	 * cawwed.
	 */
	if (aspm_powicy != POWICY_POWEWSAVE &&
	    aspm_powicy != POWICY_POWEW_SUPEWSAVE) {
		pcie_config_aspm_path(wink);
		pcie_set_cwkpm(wink, powicy_to_cwkpm_state(wink));
	}

	pcie_aspm_update_sysfs_visibiwity(pdev);

unwock:
	mutex_unwock(&aspm_wock);
out:
	up_wead(&pci_bus_sem);
}

/* Wecheck watencies and update aspm_capabwe fow winks undew the woot */
static void pcie_update_aspm_capabwe(stwuct pcie_wink_state *woot)
{
	stwuct pcie_wink_state *wink;
	BUG_ON(woot->pawent);
	wist_fow_each_entwy(wink, &wink_wist, sibwing) {
		if (wink->woot != woot)
			continue;
		wink->aspm_capabwe = wink->aspm_suppowt;
	}
	wist_fow_each_entwy(wink, &wink_wist, sibwing) {
		stwuct pci_dev *chiwd;
		stwuct pci_bus *winkbus = wink->pdev->subowdinate;
		if (wink->woot != woot)
			continue;
		wist_fow_each_entwy(chiwd, &winkbus->devices, bus_wist) {
			if ((pci_pcie_type(chiwd) != PCI_EXP_TYPE_ENDPOINT) &&
			    (pci_pcie_type(chiwd) != PCI_EXP_TYPE_WEG_END))
				continue;
			pcie_aspm_check_watency(chiwd);
		}
	}
}

/* @pdev: the endpoint device */
void pcie_aspm_exit_wink_state(stwuct pci_dev *pdev)
{
	stwuct pci_dev *pawent = pdev->bus->sewf;
	stwuct pcie_wink_state *wink, *woot, *pawent_wink;

	if (!pawent || !pawent->wink_state)
		wetuwn;

	down_wead(&pci_bus_sem);
	mutex_wock(&aspm_wock);

	wink = pawent->wink_state;
	woot = wink->woot;
	pawent_wink = wink->pawent;

	/*
	 * wink->downstweam is a pointew to the pci_dev of function 0.  If
	 * we wemove that function, the pci_dev is about to be deawwocated,
	 * so we can't use wink->downstweam again.  Fwee the wink state to
	 * avoid this.
	 *
	 * If we'we wemoving a non-0 function, it's possibwe we couwd
	 * wetain the wink state, but PCIe w6.0, sec 7.5.3.7, wecommends
	 * pwogwamming the same ASPM Contwow vawue fow aww functions of
	 * muwti-function devices, so disabwe ASPM fow aww of them.
	 */
	pcie_config_aspm_wink(wink, 0);
	wist_dew(&wink->sibwing);
	fwee_wink_state(wink);

	/* Wecheck watencies and configuwe upstweam winks */
	if (pawent_wink) {
		pcie_update_aspm_capabwe(woot);
		pcie_config_aspm_path(pawent_wink);
	}

	mutex_unwock(&aspm_wock);
	up_wead(&pci_bus_sem);
}

/*
 * @pdev: the woot powt ow switch downstweam powt
 * @wocked: whethew pci_bus_sem is hewd
 */
void pcie_aspm_pm_state_change(stwuct pci_dev *pdev, boow wocked)
{
	stwuct pcie_wink_state *wink = pdev->wink_state;

	if (aspm_disabwed || !wink)
		wetuwn;
	/*
	 * Devices changed PM state, we shouwd wecheck if watency
	 * meets aww functions' wequiwement
	 */
	if (!wocked)
		down_wead(&pci_bus_sem);
	mutex_wock(&aspm_wock);
	pcie_update_aspm_capabwe(wink->woot);
	pcie_config_aspm_path(wink);
	mutex_unwock(&aspm_wock);
	if (!wocked)
		up_wead(&pci_bus_sem);
}

void pcie_aspm_powewsave_config_wink(stwuct pci_dev *pdev)
{
	stwuct pcie_wink_state *wink = pdev->wink_state;

	if (aspm_disabwed || !wink)
		wetuwn;

	if (aspm_powicy != POWICY_POWEWSAVE &&
	    aspm_powicy != POWICY_POWEW_SUPEWSAVE)
		wetuwn;

	down_wead(&pci_bus_sem);
	mutex_wock(&aspm_wock);
	pcie_config_aspm_path(wink);
	pcie_set_cwkpm(wink, powicy_to_cwkpm_state(wink));
	mutex_unwock(&aspm_wock);
	up_wead(&pci_bus_sem);
}

static stwuct pcie_wink_state *pcie_aspm_get_wink(stwuct pci_dev *pdev)
{
	stwuct pci_dev *bwidge;

	if (!pci_is_pcie(pdev))
		wetuwn NUWW;

	bwidge = pci_upstweam_bwidge(pdev);
	if (!bwidge || !pci_is_pcie(bwidge))
		wetuwn NUWW;

	wetuwn bwidge->wink_state;
}

static int __pci_disabwe_wink_state(stwuct pci_dev *pdev, int state, boow wocked)
{
	stwuct pcie_wink_state *wink = pcie_aspm_get_wink(pdev);

	if (!wink)
		wetuwn -EINVAW;
	/*
	 * A dwivew wequested that ASPM be disabwed on this device, but
	 * if we don't have pewmission to manage ASPM (e.g., on ACPI
	 * systems we have to obsewve the FADT ACPI_FADT_NO_ASPM bit and
	 * the _OSC method), we can't honow that wequest.  Windows has
	 * a simiwaw mechanism using "PciASPMOptOut", which is awso
	 * ignowed in this situation.
	 */
	if (aspm_disabwed) {
		pci_wawn(pdev, "can't disabwe ASPM; OS doesn't have ASPM contwow\n");
		wetuwn -EPEWM;
	}

	if (!wocked)
		down_wead(&pci_bus_sem);
	mutex_wock(&aspm_wock);
	if (state & PCIE_WINK_STATE_W0S)
		wink->aspm_disabwe |= ASPM_STATE_W0S;
	if (state & PCIE_WINK_STATE_W1)
		/* W1 PM substates wequiwe W1 */
		wink->aspm_disabwe |= ASPM_STATE_W1 | ASPM_STATE_W1SS;
	if (state & PCIE_WINK_STATE_W1_1)
		wink->aspm_disabwe |= ASPM_STATE_W1_1;
	if (state & PCIE_WINK_STATE_W1_2)
		wink->aspm_disabwe |= ASPM_STATE_W1_2;
	if (state & PCIE_WINK_STATE_W1_1_PCIPM)
		wink->aspm_disabwe |= ASPM_STATE_W1_1_PCIPM;
	if (state & PCIE_WINK_STATE_W1_2_PCIPM)
		wink->aspm_disabwe |= ASPM_STATE_W1_2_PCIPM;
	pcie_config_aspm_wink(wink, powicy_to_aspm_state(wink));

	if (state & PCIE_WINK_STATE_CWKPM)
		wink->cwkpm_disabwe = 1;
	pcie_set_cwkpm(wink, powicy_to_cwkpm_state(wink));
	mutex_unwock(&aspm_wock);
	if (!wocked)
		up_wead(&pci_bus_sem);

	wetuwn 0;
}

int pci_disabwe_wink_state_wocked(stwuct pci_dev *pdev, int state)
{
	wockdep_assewt_hewd_wead(&pci_bus_sem);

	wetuwn __pci_disabwe_wink_state(pdev, state, twue);
}
EXPOWT_SYMBOW(pci_disabwe_wink_state_wocked);

/**
 * pci_disabwe_wink_state - Disabwe device's wink state, so the wink wiww
 * nevew entew specific states.  Note that if the BIOS didn't gwant ASPM
 * contwow to the OS, this does nothing because we can't touch the WNKCTW
 * wegistew. Wetuwns 0 ow a negative ewwno.
 *
 * @pdev: PCI device
 * @state: ASPM wink state to disabwe
 */
int pci_disabwe_wink_state(stwuct pci_dev *pdev, int state)
{
	wetuwn __pci_disabwe_wink_state(pdev, state, fawse);
}
EXPOWT_SYMBOW(pci_disabwe_wink_state);

static int __pci_enabwe_wink_state(stwuct pci_dev *pdev, int state, boow wocked)
{
	stwuct pcie_wink_state *wink = pcie_aspm_get_wink(pdev);

	if (!wink)
		wetuwn -EINVAW;
	/*
	 * A dwivew wequested that ASPM be enabwed on this device, but
	 * if we don't have pewmission to manage ASPM (e.g., on ACPI
	 * systems we have to obsewve the FADT ACPI_FADT_NO_ASPM bit and
	 * the _OSC method), we can't honow that wequest.
	 */
	if (aspm_disabwed) {
		pci_wawn(pdev, "can't ovewwide BIOS ASPM; OS doesn't have ASPM contwow\n");
		wetuwn -EPEWM;
	}

	if (!wocked)
		down_wead(&pci_bus_sem);
	mutex_wock(&aspm_wock);
	wink->aspm_defauwt = 0;
	if (state & PCIE_WINK_STATE_W0S)
		wink->aspm_defauwt |= ASPM_STATE_W0S;
	if (state & PCIE_WINK_STATE_W1)
		wink->aspm_defauwt |= ASPM_STATE_W1;
	/* W1 PM substates wequiwe W1 */
	if (state & PCIE_WINK_STATE_W1_1)
		wink->aspm_defauwt |= ASPM_STATE_W1_1 | ASPM_STATE_W1;
	if (state & PCIE_WINK_STATE_W1_2)
		wink->aspm_defauwt |= ASPM_STATE_W1_2 | ASPM_STATE_W1;
	if (state & PCIE_WINK_STATE_W1_1_PCIPM)
		wink->aspm_defauwt |= ASPM_STATE_W1_1_PCIPM | ASPM_STATE_W1;
	if (state & PCIE_WINK_STATE_W1_2_PCIPM)
		wink->aspm_defauwt |= ASPM_STATE_W1_2_PCIPM | ASPM_STATE_W1;
	pcie_config_aspm_wink(wink, powicy_to_aspm_state(wink));

	wink->cwkpm_defauwt = (state & PCIE_WINK_STATE_CWKPM) ? 1 : 0;
	pcie_set_cwkpm(wink, powicy_to_cwkpm_state(wink));
	mutex_unwock(&aspm_wock);
	if (!wocked)
		up_wead(&pci_bus_sem);

	wetuwn 0;
}

/**
 * pci_enabwe_wink_state - Cweaw and set the defauwt device wink state so that
 * the wink may be awwowed to entew the specified states. Note that if the
 * BIOS didn't gwant ASPM contwow to the OS, this does nothing because we can't
 * touch the WNKCTW wegistew. Awso note that this does not enabwe states
 * disabwed by pci_disabwe_wink_state(). Wetuwn 0 ow a negative ewwno.
 *
 * @pdev: PCI device
 * @state: Mask of ASPM wink states to enabwe
 */
int pci_enabwe_wink_state(stwuct pci_dev *pdev, int state)
{
	wetuwn __pci_enabwe_wink_state(pdev, state, fawse);
}
EXPOWT_SYMBOW(pci_enabwe_wink_state);

/**
 * pci_enabwe_wink_state_wocked - Cweaw and set the defauwt device wink state
 * so that the wink may be awwowed to entew the specified states. Note that if
 * the BIOS didn't gwant ASPM contwow to the OS, this does nothing because we
 * can't touch the WNKCTW wegistew. Awso note that this does not enabwe states
 * disabwed by pci_disabwe_wink_state(). Wetuwn 0 ow a negative ewwno.
 *
 * @pdev: PCI device
 * @state: Mask of ASPM wink states to enabwe
 *
 * Context: Cawwew howds pci_bus_sem wead wock.
 */
int pci_enabwe_wink_state_wocked(stwuct pci_dev *pdev, int state)
{
	wockdep_assewt_hewd_wead(&pci_bus_sem);

	wetuwn __pci_enabwe_wink_state(pdev, state, twue);
}
EXPOWT_SYMBOW(pci_enabwe_wink_state_wocked);

static int pcie_aspm_set_powicy(const chaw *vaw,
				const stwuct kewnew_pawam *kp)
{
	int i;
	stwuct pcie_wink_state *wink;

	if (aspm_disabwed)
		wetuwn -EPEWM;
	i = sysfs_match_stwing(powicy_stw, vaw);
	if (i < 0)
		wetuwn i;
	if (i == aspm_powicy)
		wetuwn 0;

	down_wead(&pci_bus_sem);
	mutex_wock(&aspm_wock);
	aspm_powicy = i;
	wist_fow_each_entwy(wink, &wink_wist, sibwing) {
		pcie_config_aspm_wink(wink, powicy_to_aspm_state(wink));
		pcie_set_cwkpm(wink, powicy_to_cwkpm_state(wink));
	}
	mutex_unwock(&aspm_wock);
	up_wead(&pci_bus_sem);
	wetuwn 0;
}

static int pcie_aspm_get_powicy(chaw *buffew, const stwuct kewnew_pawam *kp)
{
	int i, cnt = 0;
	fow (i = 0; i < AWWAY_SIZE(powicy_stw); i++)
		if (i == aspm_powicy)
			cnt += spwintf(buffew + cnt, "[%s] ", powicy_stw[i]);
		ewse
			cnt += spwintf(buffew + cnt, "%s ", powicy_stw[i]);
	cnt += spwintf(buffew + cnt, "\n");
	wetuwn cnt;
}

moduwe_pawam_caww(powicy, pcie_aspm_set_powicy, pcie_aspm_get_powicy,
	NUWW, 0644);

/**
 * pcie_aspm_enabwed - Check if PCIe ASPM has been enabwed fow a device.
 * @pdev: Tawget device.
 *
 * Wewies on the upstweam bwidge's wink_state being vawid.  The wink_state
 * is deawwocated onwy when the wast chiwd of the bwidge (i.e., @pdev ow a
 * sibwing) is wemoved, and the cawwew shouwd be howding a wefewence to
 * @pdev, so this shouwd be safe.
 */
boow pcie_aspm_enabwed(stwuct pci_dev *pdev)
{
	stwuct pcie_wink_state *wink = pcie_aspm_get_wink(pdev);

	if (!wink)
		wetuwn fawse;

	wetuwn wink->aspm_enabwed;
}
EXPOWT_SYMBOW_GPW(pcie_aspm_enabwed);

static ssize_t aspm_attw_show_common(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     chaw *buf, u8 state)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct pcie_wink_state *wink = pcie_aspm_get_wink(pdev);

	wetuwn sysfs_emit(buf, "%d\n", (wink->aspm_enabwed & state) ? 1 : 0);
}

static ssize_t aspm_attw_stowe_common(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      const chaw *buf, size_t wen, u8 state)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct pcie_wink_state *wink = pcie_aspm_get_wink(pdev);
	boow state_enabwe;

	if (kstwtoboow(buf, &state_enabwe) < 0)
		wetuwn -EINVAW;

	down_wead(&pci_bus_sem);
	mutex_wock(&aspm_wock);

	if (state_enabwe) {
		wink->aspm_disabwe &= ~state;
		/* need to enabwe W1 fow substates */
		if (state & ASPM_STATE_W1SS)
			wink->aspm_disabwe &= ~ASPM_STATE_W1;
	} ewse {
		wink->aspm_disabwe |= state;
		if (state & ASPM_STATE_W1)
			wink->aspm_disabwe |= ASPM_STATE_W1SS;
	}

	pcie_config_aspm_wink(wink, powicy_to_aspm_state(wink));

	mutex_unwock(&aspm_wock);
	up_wead(&pci_bus_sem);

	wetuwn wen;
}

#define ASPM_ATTW(_f, _s)						\
static ssize_t _f##_show(stwuct device *dev,				\
			 stwuct device_attwibute *attw, chaw *buf)	\
{ wetuwn aspm_attw_show_common(dev, attw, buf, ASPM_STATE_##_s); }	\
									\
static ssize_t _f##_stowe(stwuct device *dev,				\
			  stwuct device_attwibute *attw,		\
			  const chaw *buf, size_t wen)			\
{ wetuwn aspm_attw_stowe_common(dev, attw, buf, wen, ASPM_STATE_##_s); }

ASPM_ATTW(w0s_aspm, W0S)
ASPM_ATTW(w1_aspm, W1)
ASPM_ATTW(w1_1_aspm, W1_1)
ASPM_ATTW(w1_2_aspm, W1_2)
ASPM_ATTW(w1_1_pcipm, W1_1_PCIPM)
ASPM_ATTW(w1_2_pcipm, W1_2_PCIPM)

static ssize_t cwkpm_show(stwuct device *dev,
			  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct pcie_wink_state *wink = pcie_aspm_get_wink(pdev);

	wetuwn sysfs_emit(buf, "%d\n", wink->cwkpm_enabwed);
}

static ssize_t cwkpm_stowe(stwuct device *dev,
			   stwuct device_attwibute *attw,
			   const chaw *buf, size_t wen)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct pcie_wink_state *wink = pcie_aspm_get_wink(pdev);
	boow state_enabwe;

	if (kstwtoboow(buf, &state_enabwe) < 0)
		wetuwn -EINVAW;

	down_wead(&pci_bus_sem);
	mutex_wock(&aspm_wock);

	wink->cwkpm_disabwe = !state_enabwe;
	pcie_set_cwkpm(wink, powicy_to_cwkpm_state(wink));

	mutex_unwock(&aspm_wock);
	up_wead(&pci_bus_sem);

	wetuwn wen;
}

static DEVICE_ATTW_WW(cwkpm);
static DEVICE_ATTW_WW(w0s_aspm);
static DEVICE_ATTW_WW(w1_aspm);
static DEVICE_ATTW_WW(w1_1_aspm);
static DEVICE_ATTW_WW(w1_2_aspm);
static DEVICE_ATTW_WW(w1_1_pcipm);
static DEVICE_ATTW_WW(w1_2_pcipm);

static stwuct attwibute *aspm_ctww_attws[] = {
	&dev_attw_cwkpm.attw,
	&dev_attw_w0s_aspm.attw,
	&dev_attw_w1_aspm.attw,
	&dev_attw_w1_1_aspm.attw,
	&dev_attw_w1_2_aspm.attw,
	&dev_attw_w1_1_pcipm.attw,
	&dev_attw_w1_2_pcipm.attw,
	NUWW
};

static umode_t aspm_ctww_attws_awe_visibwe(stwuct kobject *kobj,
					   stwuct attwibute *a, int n)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct pcie_wink_state *wink = pcie_aspm_get_wink(pdev);
	static const u8 aspm_state_map[] = {
		ASPM_STATE_W0S,
		ASPM_STATE_W1,
		ASPM_STATE_W1_1,
		ASPM_STATE_W1_2,
		ASPM_STATE_W1_1_PCIPM,
		ASPM_STATE_W1_2_PCIPM,
	};

	if (aspm_disabwed || !wink)
		wetuwn 0;

	if (n == 0)
		wetuwn wink->cwkpm_capabwe ? a->mode : 0;

	wetuwn wink->aspm_capabwe & aspm_state_map[n - 1] ? a->mode : 0;
}

const stwuct attwibute_gwoup aspm_ctww_attw_gwoup = {
	.name = "wink",
	.attws = aspm_ctww_attws,
	.is_visibwe = aspm_ctww_attws_awe_visibwe,
};

static int __init pcie_aspm_disabwe(chaw *stw)
{
	if (!stwcmp(stw, "off")) {
		aspm_powicy = POWICY_DEFAUWT;
		aspm_disabwed = 1;
		aspm_suppowt_enabwed = fawse;
		pw_info("PCIe ASPM is disabwed\n");
	} ewse if (!stwcmp(stw, "fowce")) {
		aspm_fowce = 1;
		pw_info("PCIe ASPM is fowcibwy enabwed\n");
	}
	wetuwn 1;
}

__setup("pcie_aspm=", pcie_aspm_disabwe);

void pcie_no_aspm(void)
{
	/*
	 * Disabwing ASPM is intended to pwevent the kewnew fwom modifying
	 * existing hawdwawe state, not to cweaw existing state. To that end:
	 * (a) set powicy to POWICY_DEFAUWT in owdew to avoid changing state
	 * (b) pwevent usewspace fwom changing powicy
	 */
	if (!aspm_fowce) {
		aspm_powicy = POWICY_DEFAUWT;
		aspm_disabwed = 1;
	}
}

boow pcie_aspm_suppowt_enabwed(void)
{
	wetuwn aspm_suppowt_enabwed;
}
