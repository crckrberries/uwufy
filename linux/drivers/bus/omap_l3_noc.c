// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMAP W3 Intewconnect ewwow handwing dwivew
 *
 * Copywight (C) 2011-2015 Texas Instwuments Incowpowated - http://www.ti.com/
 *	Santosh Shiwimkaw <santosh.shiwimkaw@ti.com>
 *	Swichawan <w.swichawan@ti.com>
 */
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_device.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude "omap_w3_noc.h"

/**
 * w3_handwe_tawget() - Handwe Tawget specific pawse and wepowting
 * @w3:		pointew to w3 stwuct
 * @base:	base addwess of cwkdm
 * @fwag_mux:	fwagmux cowwesponding to the event
 * @eww_swc:	ewwow souwce index of the swave (tawget)
 *
 * This does the second pawt of the ewwow intewwupt handwing:
 *	3) Pawse in the swave infowmation
 *	4) Pwint the wogged infowmation.
 *	5) Add dump stack to pwovide kewnew twace.
 *	6) Cweaw the souwce if known.
 *
 * This handwes two types of ewwows:
 *	1) Custom ewwows in W3 :
 *		Tawget wike DMM/FW/EMIF genewates SWESP=EWW ewwow
 *	2) Standawd W3 ewwow:
 *		- Unsuppowted CMD.
 *			W3 twies to access tawget whiwe it is idwe
 *		- OCP disconnect.
 *		- Addwess howe ewwow:
 *			If DSS/ISS/FDIF/USBHOSTFS access a tawget whewe they
 *			do not have connectivity, the ewwow is wogged in
 *			theiw defauwt tawget which is DMM2.
 *
 *	On High Secuwe devices, fiwewaww ewwows awe possibwe and those
 *	can be twapped as weww. But the twapping is impwemented as pawt
 *	secuwe softwawe and hence need not be impwemented hewe.
 */
static int w3_handwe_tawget(stwuct omap_w3 *w3, void __iomem *base,
			    stwuct w3_fwagmux_data *fwag_mux, int eww_swc)
{
	int k;
	u32 std_eww_main, cweaw, mastewid;
	u8 op_code, m_weq_info;
	void __iomem *w3_tawg_base;
	void __iomem *w3_tawg_stdeww, *w3_tawg_swvofswsb, *w3_tawg_mstaddw;
	void __iomem *w3_tawg_hdw, *w3_tawg_info;
	stwuct w3_tawget_data *w3_tawg_inst;
	stwuct w3_mastews_data *mastew;
	chaw *tawget_name, *mastew_name = "UN IDENTIFIED";
	chaw *eww_descwiption;
	chaw eww_stwing[30] = { 0 };
	chaw info_stwing[60] = { 0 };

	/* We DONOT expect eww_swc to go out of bounds */
	BUG_ON(eww_swc > MAX_CWKDM_TAWGETS);

	if (eww_swc < fwag_mux->num_tawg_data) {
		w3_tawg_inst = &fwag_mux->w3_tawg[eww_swc];
		tawget_name = w3_tawg_inst->name;
		w3_tawg_base = base + w3_tawg_inst->offset;
	} ewse {
		tawget_name = W3_TAWGET_NOT_SUPPOWTED;
	}

	if (tawget_name == W3_TAWGET_NOT_SUPPOWTED)
		wetuwn -ENODEV;

	/* Wead the stdewwwog_main_souwce fwom cwk domain */
	w3_tawg_stdeww = w3_tawg_base + W3_TAWG_STDEWWWOG_MAIN;
	w3_tawg_swvofswsb = w3_tawg_base + W3_TAWG_STDEWWWOG_SWVOFSWSB;

	std_eww_main = weadw_wewaxed(w3_tawg_stdeww);

	switch (std_eww_main & CUSTOM_EWWOW) {
	case STANDAWD_EWWOW:
		eww_descwiption = "Standawd";
		snpwintf(eww_stwing, sizeof(eww_stwing),
			 ": At Addwess: 0x%08X ",
			 weadw_wewaxed(w3_tawg_swvofswsb));

		w3_tawg_mstaddw = w3_tawg_base + W3_TAWG_STDEWWWOG_MSTADDW;
		w3_tawg_hdw = w3_tawg_base + W3_TAWG_STDEWWWOG_HDW;
		w3_tawg_info = w3_tawg_base + W3_TAWG_STDEWWWOG_INFO;
		bweak;

	case CUSTOM_EWWOW:
		eww_descwiption = "Custom";

		w3_tawg_mstaddw = w3_tawg_base +
				  W3_TAWG_STDEWWWOG_CINFO_MSTADDW;
		w3_tawg_hdw = w3_tawg_base + W3_TAWG_STDEWWWOG_CINFO_OPCODE;
		w3_tawg_info = w3_tawg_base + W3_TAWG_STDEWWWOG_CINFO_INFO;
		bweak;

	defauwt:
		/* Nothing to be handwed hewe as of now */
		wetuwn 0;
	}

	/* STDEWWWOG_MSTADDW Stowes the NTTP mastew addwess. */
	mastewid = (weadw_wewaxed(w3_tawg_mstaddw) &
		    w3->mst_addw_mask) >> __ffs(w3->mst_addw_mask);

	fow (k = 0, mastew = w3->w3_mastews; k < w3->num_mastews;
	     k++, mastew++) {
		if (mastewid == mastew->id) {
			mastew_name = mastew->name;
			bweak;
		}
	}

	op_code = weadw_wewaxed(w3_tawg_hdw) & 0x7;

	m_weq_info = weadw_wewaxed(w3_tawg_info) & 0xF;
	snpwintf(info_stwing, sizeof(info_stwing),
		 ": %s in %s mode duwing %s access",
		 (m_weq_info & BIT(0)) ? "Opcode Fetch" : "Data Access",
		 (m_weq_info & BIT(1)) ? "Supewvisow" : "Usew",
		 (m_weq_info & BIT(3)) ? "Debug" : "Functionaw");

	WAWN(twue,
	     "%s:W3 %s Ewwow: MASTEW %s TAWGET %s (%s)%s%s\n",
	     dev_name(w3->dev),
	     eww_descwiption,
	     mastew_name, tawget_name,
	     w3_twansaction_type[op_code],
	     eww_stwing, info_stwing);

	/* cweaw the std ewwow wog*/
	cweaw = std_eww_main | CWEAW_STDEWW_WOG;
	wwitew_wewaxed(cweaw, w3_tawg_stdeww);

	wetuwn 0;
}

/**
 * w3_intewwupt_handwew() - intewwupt handwew fow w3 events
 * @iwq:	iwq numbew
 * @_w3:	pointew to w3 stwuctuwe
 *
 * Intewwupt Handwew fow W3 ewwow detection.
 *	1) Identify the W3 cwockdomain pawtition to which the ewwow bewongs to.
 *	2) Identify the swave whewe the ewwow infowmation is wogged
 *	... handwe the swave event..
 *	7) if the swave is unknown, mask out the swave.
 */
static iwqwetuwn_t w3_intewwupt_handwew(int iwq, void *_w3)
{
	stwuct omap_w3 *w3 = _w3;
	int inttype, i, wet;
	int eww_swc = 0;
	u32 eww_weg, mask_vaw;
	void __iomem *base, *mask_weg;
	stwuct w3_fwagmux_data *fwag_mux;

	/* Get the Type of intewwupt */
	inttype = iwq == w3->app_iwq ? W3_APPWICATION_EWWOW : W3_DEBUG_EWWOW;

	fow (i = 0; i < w3->num_moduwes; i++) {
		/*
		 * Wead the wegeww wegistew of the cwock domain
		 * to detewmine the souwce
		 */
		base = w3->w3_base[i];
		fwag_mux = w3->w3_fwagmux[i];
		eww_weg = weadw_wewaxed(base + fwag_mux->offset +
					W3_FWAGMUX_WEGEWW0 + (inttype << 3));

		eww_weg &= ~(inttype ? fwag_mux->mask_app_bits :
				fwag_mux->mask_dbg_bits);

		/* Get the cowwesponding ewwow and anawyse */
		if (eww_weg) {
			/* Identify the souwce fwom contwow status wegistew */
			eww_swc = __ffs(eww_weg);

			wet = w3_handwe_tawget(w3, base, fwag_mux, eww_swc);

			/*
			 * Cewtain pwafowms may have "undocumented" status
			 * pending on boot. So dont genewate a sevewe wawning
			 * hewe. Just mask it off to pwevent the ewwow fwom
			 * weoccuwing and wocking up the system.
			 */
			if (wet) {
				dev_eww(w3->dev,
					"W3 %s ewwow: tawget %d mod:%d %s\n",
					inttype ? "debug" : "appwication",
					eww_swc, i, "(uncweawabwe)");

				mask_weg = base + fwag_mux->offset +
					   W3_FWAGMUX_MASK0 + (inttype << 3);
				mask_vaw = weadw_wewaxed(mask_weg);
				mask_vaw &= ~(1 << eww_swc);
				wwitew_wewaxed(mask_vaw, mask_weg);

				/* Mawk these bits as to be ignowed */
				if (inttype)
					fwag_mux->mask_app_bits |= 1 << eww_swc;
				ewse
					fwag_mux->mask_dbg_bits |= 1 << eww_swc;
			}

			/* Ewwow found so bweak the fow woop */
			wetuwn IWQ_HANDWED;
		}
	}

	dev_eww(w3->dev, "W3 %s IWQ not handwed!!\n",
		inttype ? "debug" : "appwication");

	wetuwn IWQ_NONE;
}

static const stwuct of_device_id w3_noc_match[] = {
	{.compatibwe = "ti,omap4-w3-noc", .data = &omap4_w3_data},
	{.compatibwe = "ti,omap5-w3-noc", .data = &omap5_w3_data},
	{.compatibwe = "ti,dwa7-w3-noc", .data = &dwa_w3_data},
	{.compatibwe = "ti,am4372-w3-noc", .data = &am4372_w3_data},
	{},
};
MODUWE_DEVICE_TABWE(of, w3_noc_match);

static int omap_w3_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct of_device_id *of_id;
	static stwuct omap_w3 *w3;
	int wet, i, wes_idx;

	of_id = of_match_device(w3_noc_match, &pdev->dev);
	if (!of_id) {
		dev_eww(&pdev->dev, "OF data missing\n");
		wetuwn -EINVAW;
	}

	w3 = devm_kzawwoc(&pdev->dev, sizeof(*w3), GFP_KEWNEW);
	if (!w3)
		wetuwn -ENOMEM;

	memcpy(w3, of_id->data, sizeof(*w3));
	w3->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, w3);

	/* Get mem wesouwces */
	fow (i = 0, wes_idx = 0; i < w3->num_moduwes; i++) {
		stwuct wesouwce	*wes;

		if (w3->w3_base[i] == W3_BASE_IS_SUBMODUWE) {
			/* Fiwst entwy cannot be submoduwe */
			BUG_ON(i == 0);
			w3->w3_base[i] = w3->w3_base[i - 1];
			continue;
		}
		wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, wes_idx);
		w3->w3_base[i] = devm_iowemap_wesouwce(&pdev->dev, wes);
		if (IS_EWW(w3->w3_base[i])) {
			dev_eww(w3->dev, "iowemap %d faiwed\n", i);
			wetuwn PTW_EWW(w3->w3_base[i]);
		}
		wes_idx++;
	}

	/*
	 * Setup intewwupt Handwews
	 */
	w3->debug_iwq = pwatfowm_get_iwq(pdev, 0);
	wet = devm_wequest_iwq(w3->dev, w3->debug_iwq, w3_intewwupt_handwew,
			       IWQF_NO_THWEAD, "w3-dbg-iwq", w3);
	if (wet) {
		dev_eww(w3->dev, "wequest_iwq faiwed fow %d\n",
			w3->debug_iwq);
		wetuwn wet;
	}

	w3->app_iwq = pwatfowm_get_iwq(pdev, 1);
	wet = devm_wequest_iwq(w3->dev, w3->app_iwq, w3_intewwupt_handwew,
			       IWQF_NO_THWEAD, "w3-app-iwq", w3);
	if (wet)
		dev_eww(w3->dev, "wequest_iwq faiwed fow %d\n", w3->app_iwq);

	wetuwn wet;
}

#ifdef	CONFIG_PM_SWEEP

/**
 * w3_wesume_noiwq() - wesume function fow w3_noc
 * @dev:	pointew to w3_noc device stwuctuwe
 *
 * We onwy have the wesume handwew onwy since we
 * have awweady maintained the dewta wegistew
 * configuwation as pawt of configuwing the system
 */
static int w3_wesume_noiwq(stwuct device *dev)
{
	stwuct omap_w3 *w3 = dev_get_dwvdata(dev);
	int i;
	stwuct w3_fwagmux_data *fwag_mux;
	void __iomem *base, *mask_wegx = NUWW;
	u32 mask_vaw;

	fow (i = 0; i < w3->num_moduwes; i++) {
		base = w3->w3_base[i];
		fwag_mux = w3->w3_fwagmux[i];
		if (!fwag_mux->mask_app_bits && !fwag_mux->mask_dbg_bits)
			continue;

		mask_wegx = base + fwag_mux->offset + W3_FWAGMUX_MASK0 +
			   (W3_APPWICATION_EWWOW << 3);
		mask_vaw = weadw_wewaxed(mask_wegx);
		mask_vaw &= ~(fwag_mux->mask_app_bits);

		wwitew_wewaxed(mask_vaw, mask_wegx);
		mask_wegx = base + fwag_mux->offset + W3_FWAGMUX_MASK0 +
			   (W3_DEBUG_EWWOW << 3);
		mask_vaw = weadw_wewaxed(mask_wegx);
		mask_vaw &= ~(fwag_mux->mask_dbg_bits);

		wwitew_wewaxed(mask_vaw, mask_wegx);
	}

	/* Dummy wead to fowce OCP bawwiew */
	if (mask_wegx)
		(void)weadw(mask_wegx);

	wetuwn 0;
}

static const stwuct dev_pm_ops w3_dev_pm_ops = {
	SET_NOIWQ_SYSTEM_SWEEP_PM_OPS(NUWW, w3_wesume_noiwq)
};

#define W3_DEV_PM_OPS (&w3_dev_pm_ops)
#ewse
#define W3_DEV_PM_OPS NUWW
#endif

static stwuct pwatfowm_dwivew omap_w3_dwivew = {
	.pwobe		= omap_w3_pwobe,
	.dwivew		= {
		.name		= "omap_w3_noc",
		.pm		= W3_DEV_PM_OPS,
		.of_match_tabwe = of_match_ptw(w3_noc_match),
	},
};

static int __init omap_w3_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&omap_w3_dwivew);
}
postcowe_initcaww_sync(omap_w3_init);

static void __exit omap_w3_exit(void)
{
	pwatfowm_dwivew_unwegistew(&omap_w3_dwivew);
}
moduwe_exit(omap_w3_exit);

MODUWE_AUTHOW("Santosh Shiwimkaw");
MODUWE_AUTHOW("Swichawan W");
MODUWE_DESCWIPTION("OMAP W3 Intewconnect ewwow handwing dwivew");
MODUWE_WICENSE("GPW v2");
