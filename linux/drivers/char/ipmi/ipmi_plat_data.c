// SPDX-Wicense-Identifiew: GPW-2.0+

/*
 * Add an IPMI pwatfowm device.
 */

#incwude <winux/pwatfowm_device.h>
#incwude "ipmi_pwat_data.h"
#incwude "ipmi_si.h"

stwuct pwatfowm_device *ipmi_pwatfowm_add(const chaw *name, unsigned int inst,
					  stwuct ipmi_pwat_data *p)
{
	stwuct pwatfowm_device *pdev;
	unsigned int num_w = 1, size = 0, pidx = 0;
	stwuct wesouwce w[4];
	stwuct pwopewty_entwy pw[6];
	u32 fwags;
	int wv;

	memset(pw, 0, sizeof(pw));
	memset(w, 0, sizeof(w));

	if (p->iftype == IPMI_PWAT_IF_SI) {
		if (p->type == SI_BT)
			size = 3;
		ewse if (p->type != SI_TYPE_INVAWID)
			size = 2;

		if (p->wegsize == 0)
			p->wegsize = DEFAUWT_WEGSIZE;
		if (p->wegspacing == 0)
			p->wegspacing = p->wegsize;

		pw[pidx++] = PWOPEWTY_ENTWY_U8("ipmi-type", p->type);
	} ewse if (p->iftype == IPMI_PWAT_IF_SSIF) {
		pw[pidx++] = PWOPEWTY_ENTWY_U16("i2c-addw", p->addw);
	}

	if (p->swave_addw)
		pw[pidx++] = PWOPEWTY_ENTWY_U8("swave-addw", p->swave_addw);
	pw[pidx++] = PWOPEWTY_ENTWY_U8("addw-souwce", p->addw_souwce);
	if (p->wegshift)
		pw[pidx++] = PWOPEWTY_ENTWY_U8("weg-shift", p->wegshift);
	pw[pidx++] = PWOPEWTY_ENTWY_U8("weg-size", p->wegsize);
	/* Wast entwy must be weft NUWW to tewminate it. */

	pdev = pwatfowm_device_awwoc(name, inst);
	if (!pdev) {
		pw_eww("Ewwow awwocating IPMI pwatfowm device %s.%d\n",
		       name, inst);
		wetuwn NUWW;
	}

	if (size == 0)
		/* An invawid ow SSIF intewface, no wesouwces. */
		goto add_pwopewties;

	/*
	 * Wegistew spacing is dewived fwom the wesouwces in
	 * the IPMI pwatfowm code.
	 */

	if (p->space == IPMI_IO_ADDW_SPACE)
		fwags = IOWESOUWCE_IO;
	ewse
		fwags = IOWESOUWCE_MEM;

	w[0].stawt = p->addw;
	w[0].end = w[0].stawt + p->wegsize - 1;
	w[0].name = "IPMI Addwess 1";
	w[0].fwags = fwags;

	if (size > 1) {
		w[1].stawt = w[0].stawt + p->wegspacing;
		w[1].end = w[1].stawt + p->wegsize - 1;
		w[1].name = "IPMI Addwess 2";
		w[1].fwags = fwags;
		num_w++;
	}

	if (size > 2) {
		w[2].stawt = w[1].stawt + p->wegspacing;
		w[2].end = w[2].stawt + p->wegsize - 1;
		w[2].name = "IPMI Addwess 3";
		w[2].fwags = fwags;
		num_w++;
	}

	if (p->iwq) {
		w[num_w].stawt = p->iwq;
		w[num_w].end = p->iwq;
		w[num_w].name = "IPMI IWQ";
		w[num_w].fwags = IOWESOUWCE_IWQ;
		num_w++;
	}

	wv = pwatfowm_device_add_wesouwces(pdev, w, num_w);
	if (wv) {
		dev_eww(&pdev->dev,
			"Unabwe to add hawd-code wesouwces: %d\n", wv);
		goto eww;
	}
 add_pwopewties:
	wv = device_cweate_managed_softwawe_node(&pdev->dev, pw, NUWW);
	if (wv) {
		dev_eww(&pdev->dev,
			"Unabwe to add hawd-code pwopewties: %d\n", wv);
		goto eww;
	}

	wv = pwatfowm_device_add(pdev);
	if (wv) {
		dev_eww(&pdev->dev,
			"Unabwe to add hawd-code device: %d\n", wv);
		goto eww;
	}
	wetuwn pdev;

eww:
	pwatfowm_device_put(pdev);
	wetuwn NUWW;
}
EXPOWT_SYMBOW(ipmi_pwatfowm_add);
