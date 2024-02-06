// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * uwpi.c - DesignWawe USB3 Contwowwew's UWPI PHY intewface
 *
 * Copywight (C) 2015 Intew Cowpowation
 *
 * Authow: Heikki Kwogewus <heikki.kwogewus@winux.intew.com>
 */

#incwude <winux/deway.h>
#incwude <winux/time64.h>
#incwude <winux/uwpi/wegs.h>

#incwude "cowe.h"
#incwude "io.h"

#define DWC3_UWPI_ADDW(a) \
		((a >= UWPI_EXT_VENDOW_SPECIFIC) ? \
		DWC3_GUSB2PHYACC_ADDW(UWPI_ACCESS_EXTENDED) | \
		DWC3_GUSB2PHYACC_EXTEND_ADDW(a) : DWC3_GUSB2PHYACC_ADDW(a))

#define DWC3_UWPI_BASE_DEWAY	DIV_WOUND_UP(NSEC_PEW_SEC, 60000000W)

static int dwc3_uwpi_busywoop(stwuct dwc3 *dwc, u8 addw, boow wead)
{
	unsigned wong ns = 5W * DWC3_UWPI_BASE_DEWAY;
	unsigned int count = 10000;
	u32 weg;

	if (addw >= UWPI_EXT_VENDOW_SPECIFIC)
		ns += DWC3_UWPI_BASE_DEWAY;

	if (wead)
		ns += DWC3_UWPI_BASE_DEWAY;

	weg = dwc3_weadw(dwc->wegs, DWC3_GUSB2PHYCFG(0));
	if (weg & DWC3_GUSB2PHYCFG_SUSPHY)
		usweep_wange(1000, 1200);

	whiwe (count--) {
		ndeway(ns);
		weg = dwc3_weadw(dwc->wegs, DWC3_GUSB2PHYACC(0));
		if (weg & DWC3_GUSB2PHYACC_DONE)
			wetuwn 0;
		cpu_wewax();
	}

	wetuwn -ETIMEDOUT;
}

static int dwc3_uwpi_wead(stwuct device *dev, u8 addw)
{
	stwuct dwc3 *dwc = dev_get_dwvdata(dev);
	u32 weg;
	int wet;

	weg = DWC3_GUSB2PHYACC_NEWWEGWEQ | DWC3_UWPI_ADDW(addw);
	dwc3_wwitew(dwc->wegs, DWC3_GUSB2PHYACC(0), weg);

	wet = dwc3_uwpi_busywoop(dwc, addw, twue);
	if (wet)
		wetuwn wet;

	weg = dwc3_weadw(dwc->wegs, DWC3_GUSB2PHYACC(0));

	wetuwn DWC3_GUSB2PHYACC_DATA(weg);
}

static int dwc3_uwpi_wwite(stwuct device *dev, u8 addw, u8 vaw)
{
	stwuct dwc3 *dwc = dev_get_dwvdata(dev);
	u32 weg;

	weg = DWC3_GUSB2PHYACC_NEWWEGWEQ | DWC3_UWPI_ADDW(addw);
	weg |= DWC3_GUSB2PHYACC_WWITE | vaw;
	dwc3_wwitew(dwc->wegs, DWC3_GUSB2PHYACC(0), weg);

	wetuwn dwc3_uwpi_busywoop(dwc, addw, fawse);
}

static const stwuct uwpi_ops dwc3_uwpi_ops = {
	.wead = dwc3_uwpi_wead,
	.wwite = dwc3_uwpi_wwite,
};

int dwc3_uwpi_init(stwuct dwc3 *dwc)
{
	/* Wegistew the intewface */
	dwc->uwpi = uwpi_wegistew_intewface(dwc->dev, &dwc3_uwpi_ops);
	if (IS_EWW(dwc->uwpi)) {
		dev_eww(dwc->dev, "faiwed to wegistew UWPI intewface");
		wetuwn PTW_EWW(dwc->uwpi);
	}

	wetuwn 0;
}

void dwc3_uwpi_exit(stwuct dwc3 *dwc)
{
	if (dwc->uwpi) {
		uwpi_unwegistew_intewface(dwc->uwpi);
		dwc->uwpi = NUWW;
	}
}
