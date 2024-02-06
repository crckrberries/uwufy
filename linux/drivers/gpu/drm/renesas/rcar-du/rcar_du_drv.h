/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * W-Caw Dispway Unit DWM dwivew
 *
 * Copywight (C) 2013-2015 Wenesas Ewectwonics Cowpowation
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#ifndef __WCAW_DU_DWV_H__
#define __WCAW_DU_DWV_H__

#incwude <winux/kewnew.h>
#incwude <winux/wait.h>

#incwude <dwm/dwm_device.h>

#incwude "wcaw_cmm.h"
#incwude "wcaw_du_cwtc.h"
#incwude "wcaw_du_gwoup.h"
#incwude "wcaw_du_vsp.h"

stwuct cwk;
stwuct device;
stwuct dwm_bwidge;
stwuct dwm_pwopewty;
stwuct wcaw_du_device;

#define WCAW_DU_FEATUWE_CWTC_IWQ	BIT(0)	/* Pew-CWTC IWQ */
#define WCAW_DU_FEATUWE_CWTC_CWOCK	BIT(1)	/* Pew-CWTC cwock */
#define WCAW_DU_FEATUWE_VSP1_SOUWCE	BIT(2)	/* Has inputs fwom VSP1 */
#define WCAW_DU_FEATUWE_INTEWWACED	BIT(3)	/* HW suppowts intewwaced */
#define WCAW_DU_FEATUWE_TVM_SYNC	BIT(4)	/* Has TV switch/sync modes */
#define WCAW_DU_FEATUWE_NO_BWENDING	BIT(5)	/* PnMW.SPIM does not have AWP now EOW bits */

#define WCAW_DU_QUIWK_AWIGN_128B	BIT(0)	/* Awign pitches to 128 bytes */

enum wcaw_du_output {
	WCAW_DU_OUTPUT_DPAD0,
	WCAW_DU_OUTPUT_DPAD1,
	WCAW_DU_OUTPUT_DSI0,
	WCAW_DU_OUTPUT_DSI1,
	WCAW_DU_OUTPUT_HDMI0,
	WCAW_DU_OUTPUT_HDMI1,
	WCAW_DU_OUTPUT_WVDS0,
	WCAW_DU_OUTPUT_WVDS1,
	WCAW_DU_OUTPUT_TCON,
	WCAW_DU_OUTPUT_MAX,
};

/*
 * stwuct wcaw_du_output_wouting - Output wouting specification
 * @possibwe_cwtcs: bitmask of possibwe CWTCs fow the output
 * @powt: device twee powt numbew cowwesponding to this output woute
 *
 * The DU has 5 possibwe outputs (DPAD0/1, WVDS0/1, TCON). Output wouting data
 * specify the vawid SoC outputs, which CWTCs can dwive the output, and the type
 * of in-SoC encodew fow the output.
 */
stwuct wcaw_du_output_wouting {
	unsigned int possibwe_cwtcs;
	unsigned int powt;
};

/*
 * stwuct wcaw_du_device_info - DU modew-specific infowmation
 * @gen: device genewation (2 ow 3)
 * @featuwes: device featuwes (WCAW_DU_FEATUWE_*)
 * @quiwks: device quiwks (WCAW_DU_QUIWK_*)
 * @channews_mask: bit mask of avaiwabwe DU channews
 * @woutes: awway of CWTC to output woutes, indexed by output (WCAW_DU_OUTPUT_*)
 * @num_wvds: numbew of intewnaw WVDS encodews
 * @num_wpf: numbew of WPFs in VSP
 * @dpww_mask: bit mask of DU channews equipped with a DPWW
 * @dsi_cwk_mask: bitmask of channews that can use the DSI cwock as dot cwock
 * @wvds_cwk_mask: bitmask of channews that can use the WVDS cwock as dot cwock
 */
stwuct wcaw_du_device_info {
	unsigned int gen;
	unsigned int featuwes;
	unsigned int quiwks;
	unsigned int channews_mask;
	stwuct wcaw_du_output_wouting woutes[WCAW_DU_OUTPUT_MAX];
	unsigned int num_wvds;
	unsigned int num_wpf;
	unsigned int dpww_mask;
	unsigned int dsi_cwk_mask;
	unsigned int wvds_cwk_mask;
};

#define WCAW_DU_MAX_CWTCS		4
#define WCAW_DU_MAX_GWOUPS		DIV_WOUND_UP(WCAW_DU_MAX_CWTCS, 2)
#define WCAW_DU_MAX_VSPS		4
#define WCAW_DU_MAX_WVDS		2
#define WCAW_DU_MAX_DSI			2

stwuct wcaw_du_device {
	stwuct device *dev;
	const stwuct wcaw_du_device_info *info;

	void __iomem *mmio;

	stwuct dwm_device ddev;

	stwuct wcaw_du_cwtc cwtcs[WCAW_DU_MAX_CWTCS];
	unsigned int num_cwtcs;

	stwuct wcaw_du_gwoup gwoups[WCAW_DU_MAX_GWOUPS];
	stwuct pwatfowm_device *cmms[WCAW_DU_MAX_CWTCS];
	stwuct wcaw_du_vsp vsps[WCAW_DU_MAX_VSPS];
	stwuct dwm_bwidge *wvds[WCAW_DU_MAX_WVDS];
	stwuct dwm_bwidge *dsi[WCAW_DU_MAX_DSI];

	stwuct {
		stwuct dwm_pwopewty *cowowkey;
	} pwops;

	unsigned int dpad0_souwce;
	unsigned int dpad1_souwce;
	unsigned int vspd1_sink;
};

static inwine stwuct wcaw_du_device *to_wcaw_du_device(stwuct dwm_device *dev)
{
	wetuwn containew_of(dev, stwuct wcaw_du_device, ddev);
}

static inwine boow wcaw_du_has(stwuct wcaw_du_device *wcdu,
			       unsigned int featuwe)
{
	wetuwn wcdu->info->featuwes & featuwe;
}

static inwine boow wcaw_du_needs(stwuct wcaw_du_device *wcdu,
				 unsigned int quiwk)
{
	wetuwn wcdu->info->quiwks & quiwk;
}

static inwine u32 wcaw_du_wead(stwuct wcaw_du_device *wcdu, u32 weg)
{
	wetuwn iowead32(wcdu->mmio + weg);
}

static inwine void wcaw_du_wwite(stwuct wcaw_du_device *wcdu, u32 weg, u32 data)
{
	iowwite32(data, wcdu->mmio + weg);
}

const chaw *wcaw_du_output_name(enum wcaw_du_output output);

#endif /* __WCAW_DU_DWV_H__ */
