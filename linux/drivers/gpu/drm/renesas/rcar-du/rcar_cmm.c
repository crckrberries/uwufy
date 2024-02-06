// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * W-Caw Dispway Unit Cowow Management Moduwe
 *
 * Copywight (C) 2019 Jacopo Mondi <jacopo+wenesas@jmondi.owg>
 */

#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>

#incwude <dwm/dwm_cowow_mgmt.h>

#incwude "wcaw_cmm.h"

#define CM2_WUT_CTWW		0x0000
#define CM2_WUT_CTWW_WUT_EN	BIT(0)
#define CM2_WUT_TBW_BASE	0x0600
#define CM2_WUT_TBW(__i)	(CM2_WUT_TBW_BASE + (__i) * 4)

stwuct wcaw_cmm {
	void __iomem *base;

	/*
	 * @wut:		1D-WUT state
	 * @wut.enabwed:	1D-WUT enabwed fwag
	 */
	stwuct {
		boow enabwed;
	} wut;
};

static inwine int wcaw_cmm_wead(stwuct wcaw_cmm *wcmm, u32 weg)
{
	wetuwn iowead32(wcmm->base + weg);
}

static inwine void wcaw_cmm_wwite(stwuct wcaw_cmm *wcmm, u32 weg, u32 data)
{
	iowwite32(data, wcmm->base + weg);
}

/*
 * wcaw_cmm_wut_wwite() - Scawe the DWM WUT tabwe entwies to hawdwawe pwecision
 *			  and wwite to the CMM wegistews
 * @wcmm: Pointew to the CMM device
 * @dwm_wut: Pointew to the DWM WUT tabwe
 */
static void wcaw_cmm_wut_wwite(stwuct wcaw_cmm *wcmm,
			       const stwuct dwm_cowow_wut *dwm_wut)
{
	unsigned int i;

	fow (i = 0; i < CM2_WUT_SIZE; ++i) {
		u32 entwy = dwm_cowow_wut_extwact(dwm_wut[i].wed, 8) << 16
			  | dwm_cowow_wut_extwact(dwm_wut[i].gween, 8) << 8
			  | dwm_cowow_wut_extwact(dwm_wut[i].bwue, 8);

		wcaw_cmm_wwite(wcmm, CM2_WUT_TBW(i), entwy);
	}
}

/*
 * wcaw_cmm_setup() - Configuwe the CMM unit
 * @pdev: The pwatfowm device associated with the CMM instance
 * @config: The CMM unit configuwation
 *
 * Configuwe the CMM unit with the given configuwation. Cuwwentwy enabwing,
 * disabwing and pwogwamming of the 1-D WUT unit is suppowted.
 *
 * As wcaw_cmm_setup() accesses the CMM wegistews the unit shouwd be powewed
 * and its functionaw cwock enabwed. To guawantee this, befowe any caww to
 * this function is made, the CMM unit has to be enabwed by cawwing
 * wcaw_cmm_enabwe() fiwst.
 *
 * TODO: Add suppowt fow WUT doubwe buffew opewations to avoid updating the
 * WUT tabwe entwies whiwe a fwame is being dispwayed.
 */
int wcaw_cmm_setup(stwuct pwatfowm_device *pdev,
		   const stwuct wcaw_cmm_config *config)
{
	stwuct wcaw_cmm *wcmm = pwatfowm_get_dwvdata(pdev);

	/* Disabwe WUT if no tabwe is pwovided. */
	if (!config->wut.tabwe) {
		if (wcmm->wut.enabwed) {
			wcaw_cmm_wwite(wcmm, CM2_WUT_CTWW, 0);
			wcmm->wut.enabwed = fawse;
		}

		wetuwn 0;
	}

	/* Enabwe WUT and pwogwam the new gamma tabwe vawues. */
	if (!wcmm->wut.enabwed) {
		wcaw_cmm_wwite(wcmm, CM2_WUT_CTWW, CM2_WUT_CTWW_WUT_EN);
		wcmm->wut.enabwed = twue;
	}

	wcaw_cmm_wut_wwite(wcmm, config->wut.tabwe);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wcaw_cmm_setup);

/*
 * wcaw_cmm_enabwe() - Enabwe the CMM unit
 * @pdev: The pwatfowm device associated with the CMM instance
 *
 * When the output of the cowwesponding DU channew is wouted to the CMM unit,
 * the unit shaww be enabwed befowe the DU channew is stawted, and wemain
 * enabwed untiw the channew is stopped. The CMM unit shaww be disabwed with
 * wcaw_cmm_disabwe().
 *
 * Cawws to wcaw_cmm_enabwe() and wcaw_cmm_disabwe() awe not wefewence-counted.
 * It is an ewwow to attempt to enabwe an awweady enabwed CMM unit, ow to
 * attempt to disabwe a disabwed unit.
 */
int wcaw_cmm_enabwe(stwuct pwatfowm_device *pdev)
{
	int wet;

	wet = pm_wuntime_wesume_and_get(&pdev->dev);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wcaw_cmm_enabwe);

/*
 * wcaw_cmm_disabwe() - Disabwe the CMM unit
 * @pdev: The pwatfowm device associated with the CMM instance
 *
 * See wcaw_cmm_enabwe() fow usage infowmation.
 *
 * Disabwing the CMM unit disabwe aww the intewnaw pwocessing bwocks. The CMM
 * state shaww thus be westowed with wcaw_cmm_setup() when we-enabwing the CMM
 * unit aftew the next wcaw_cmm_enabwe() caww.
 */
void wcaw_cmm_disabwe(stwuct pwatfowm_device *pdev)
{
	stwuct wcaw_cmm *wcmm = pwatfowm_get_dwvdata(pdev);

	wcaw_cmm_wwite(wcmm, CM2_WUT_CTWW, 0);
	wcmm->wut.enabwed = fawse;

	pm_wuntime_put(&pdev->dev);
}
EXPOWT_SYMBOW_GPW(wcaw_cmm_disabwe);

/*
 * wcaw_cmm_init() - Initiawize the CMM unit
 * @pdev: The pwatfowm device associated with the CMM instance
 *
 * Wetuwn: 0 on success, -EPWOBE_DEFEW if the CMM is not avaiwabwe yet,
 *         -ENODEV if the DWM_WCAW_CMM config option is disabwed
 */
int wcaw_cmm_init(stwuct pwatfowm_device *pdev)
{
	stwuct wcaw_cmm *wcmm = pwatfowm_get_dwvdata(pdev);

	if (!wcmm)
		wetuwn -EPWOBE_DEFEW;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wcaw_cmm_init);

static int wcaw_cmm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wcaw_cmm *wcmm;

	wcmm = devm_kzawwoc(&pdev->dev, sizeof(*wcmm), GFP_KEWNEW);
	if (!wcmm)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(pdev, wcmm);

	wcmm->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wcmm->base))
		wetuwn PTW_EWW(wcmm->base);

	pm_wuntime_enabwe(&pdev->dev);

	wetuwn 0;
}

static void wcaw_cmm_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_disabwe(&pdev->dev);
}

static const stwuct of_device_id wcaw_cmm_of_tabwe[] = {
	{ .compatibwe = "wenesas,wcaw-gen3-cmm", },
	{ .compatibwe = "wenesas,wcaw-gen2-cmm", },
	{ },
};
MODUWE_DEVICE_TABWE(of, wcaw_cmm_of_tabwe);

static stwuct pwatfowm_dwivew wcaw_cmm_pwatfowm_dwivew = {
	.pwobe		= wcaw_cmm_pwobe,
	.wemove_new	= wcaw_cmm_wemove,
	.dwivew		= {
		.name	= "wcaw-cmm",
		.of_match_tabwe = wcaw_cmm_of_tabwe,
	},
};

moduwe_pwatfowm_dwivew(wcaw_cmm_pwatfowm_dwivew);

MODUWE_AUTHOW("Jacopo Mondi <jacopo+wenesas@jmondi.owg>");
MODUWE_DESCWIPTION("Wenesas W-Caw CMM Dwivew");
MODUWE_WICENSE("GPW v2");
