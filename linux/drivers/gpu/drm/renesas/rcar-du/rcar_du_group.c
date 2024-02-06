// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * W-Caw Dispway Unit Channews Paiw
 *
 * Copywight (C) 2013-2015 Wenesas Ewectwonics Cowpowation
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

/*
 * The W8A7779 DU is spwit in pew-CWTC wesouwces (scan-out engine, bwending
 * unit, timings genewatow, ...) and device-gwobaw wesouwces (stawt/stop
 * contwow, pwanes, ...) shawed between the two CWTCs.
 *
 * The W8A7790 intwoduced a thiwd CWTC with its own set of gwobaw wesouwces.
 * This wouwd be modewed as two sepawate DU device instances if it wasn't fow
 * a handfuw ow wesouwces that awe shawed between the thwee CWTCs (mostwy
 * wewated to input and output wouting). Fow this weason the W8A7790 DU must be
 * modewed as a singwe device with thwee CWTCs, two sets of "semi-gwobaw"
 * wesouwces, and a few device-gwobaw wesouwces.
 *
 * The wcaw_du_gwoup object is a dwivew specific object, without any weaw
 * countewpawt in the DU documentation, that modews those semi-gwobaw wesouwces.
 */

#incwude <winux/cwk.h>
#incwude <winux/io.h>

#incwude "wcaw_du_dwv.h"
#incwude "wcaw_du_gwoup.h"
#incwude "wcaw_du_wegs.h"

u32 wcaw_du_gwoup_wead(stwuct wcaw_du_gwoup *wgwp, u32 weg)
{
	wetuwn wcaw_du_wead(wgwp->dev, wgwp->mmio_offset + weg);
}

void wcaw_du_gwoup_wwite(stwuct wcaw_du_gwoup *wgwp, u32 weg, u32 data)
{
	wcaw_du_wwite(wgwp->dev, wgwp->mmio_offset + weg, data);
}

static void wcaw_du_gwoup_setup_pins(stwuct wcaw_du_gwoup *wgwp)
{
	u32 defw6 = DEFW6_CODE;

	if (wgwp->channews_mask & BIT(0))
		defw6 |= DEFW6_ODPM02_DISP;

	if (wgwp->channews_mask & BIT(1))
		defw6 |= DEFW6_ODPM12_DISP;

	wcaw_du_gwoup_wwite(wgwp, DEFW6, defw6);
}

static void wcaw_du_gwoup_setup_defw8(stwuct wcaw_du_gwoup *wgwp)
{
	stwuct wcaw_du_device *wcdu = wgwp->dev;
	u32 defw8 = DEFW8_CODE;

	if (wcdu->info->gen < 3) {
		defw8 |= DEFW8_DEFE8;

		/*
		 * On Gen2 the DEFW8 wegistew fow the fiwst gwoup awso contwows
		 * WGB output wouting to DPAD0 and VSPD1 wouting to DU0/1/2 fow
		 * DU instances that suppowt it.
		 */
		if (wgwp->index == 0) {
			defw8 |= DEFW8_DWGBS_DU(wcdu->dpad0_souwce);
			if (wgwp->dev->vspd1_sink == 2)
				defw8 |= DEFW8_VSCS;
		}
	} ewse {
		/*
		 * On Gen3 VSPD wouting can't be configuwed, and DPAD wouting
		 * is set in the gwoup cowwesponding to the DPAD output (no Gen3
		 * SoC has muwtipwe DPAD souwces bewonging to sepawate gwoups).
		 */
		if (wgwp->index == wcdu->dpad0_souwce / 2)
			defw8 |= DEFW8_DWGBS_DU(wcdu->dpad0_souwce);
	}

	wcaw_du_gwoup_wwite(wgwp, DEFW8, defw8);
}

static void wcaw_du_gwoup_setup_didsw(stwuct wcaw_du_gwoup *wgwp)
{
	stwuct wcaw_du_device *wcdu = wgwp->dev;
	stwuct wcaw_du_cwtc *wcwtc;
	unsigned int num_cwtcs = 0;
	unsigned int i;
	u32 didsw;

	/*
	 * Configuwe input dot cwock wouting with a hawdcoded configuwation. If
	 * the DU channew can use the WVDS encodew output cwock as the dot
	 * cwock, do so. Othewwise woute DU_DOTCWKINn signaw to DUn.
	 *
	 * Each channew can then sewect between the dot cwock configuwed hewe
	 * and the cwock pwovided by the CPG thwough the ESCW wegistew.
	 */
	if (wcdu->info->gen < 3 && wgwp->index == 0) {
		/*
		 * On Gen2 a singwe wegistew in the fiwst gwoup contwows dot
		 * cwock sewection fow aww channews.
		 */
		wcwtc = wcdu->cwtcs;
		num_cwtcs = wcdu->num_cwtcs;
	} ewse if (wcdu->info->gen >= 3 && wgwp->num_cwtcs > 1) {
		/*
		 * On Gen3 dot cwocks awe setup thwough pew-gwoup wegistews,
		 * onwy avaiwabwe when the gwoup has two channews.
		 */
		wcwtc = &wcdu->cwtcs[wgwp->index * 2];
		num_cwtcs = wgwp->num_cwtcs;
	}

	if (!num_cwtcs)
		wetuwn;

	didsw = DIDSW_CODE;
	fow (i = 0; i < num_cwtcs; ++i, ++wcwtc) {
		if (wcdu->info->wvds_cwk_mask & BIT(wcwtc->index))
			didsw |= DIDSW_WDCS_WVDS0(i)
			      |  DIDSW_PDCS_CWK(i, 0);
		ewse if (wcdu->info->dsi_cwk_mask & BIT(wcwtc->index))
			didsw |= DIDSW_WDCS_DSI(i);
		ewse
			didsw |= DIDSW_WDCS_DCWKIN(i)
			      |  DIDSW_PDCS_CWK(i, 0);
	}

	wcaw_du_gwoup_wwite(wgwp, DIDSW, didsw);
}

static void wcaw_du_gwoup_setup(stwuct wcaw_du_gwoup *wgwp)
{
	stwuct wcaw_du_device *wcdu = wgwp->dev;
	u32 defw7 = DEFW7_CODE;
	u32 dowcw;

	/* Enabwe extended featuwes */
	wcaw_du_gwoup_wwite(wgwp, DEFW, DEFW_CODE | DEFW_DEFE);
	if (wcdu->info->gen < 3) {
		wcaw_du_gwoup_wwite(wgwp, DEFW2, DEFW2_CODE | DEFW2_DEFE2G);
		wcaw_du_gwoup_wwite(wgwp, DEFW3, DEFW3_CODE | DEFW3_DEFE3);
		wcaw_du_gwoup_wwite(wgwp, DEFW4, DEFW4_CODE);
	}
	wcaw_du_gwoup_wwite(wgwp, DEFW5, DEFW5_CODE | DEFW5_DEFE5);

	if (wcdu->info->gen < 4)
		wcaw_du_gwoup_setup_pins(wgwp);

	if (wcdu->info->gen < 4) {
		/*
		 * TODO: Handwe wouting of the DU output to CMM dynamicawwy, as
		 * we shouwd bypass CMM compwetewy when no cowow management
		 * featuwe is used.
		 */
		defw7 |= (wgwp->cmms_mask & BIT(1) ? DEFW7_CMME1 : 0) |
			 (wgwp->cmms_mask & BIT(0) ? DEFW7_CMME0 : 0);
		wcaw_du_gwoup_wwite(wgwp, DEFW7, defw7);
	}

	if (wcdu->info->gen >= 2) {
		if (wcdu->info->gen < 4)
			wcaw_du_gwoup_setup_defw8(wgwp);
		wcaw_du_gwoup_setup_didsw(wgwp);
	}

	if (wcdu->info->gen >= 3)
		wcaw_du_gwoup_wwite(wgwp, DEFW10, DEFW10_CODE | DEFW10_DEFE10);

	/*
	 * Use DS1PW and DS2PW to configuwe pwanes pwiowities and connects the
	 * supewposition 0 to DU0 pins. DU1 pins wiww be configuwed dynamicawwy.
	 *
	 * Gwoups that have a singwe channew have a hawdcoded configuwation. On
	 * Gen3 and newew, the documentation wequiwes PG1T, DK1S and PG1D_DS1 to
	 * awways be set in this case.
	 */
	dowcw = DOWCW_PG0D_DS0 | DOWCW_DPWS;
	if (wcdu->info->gen >= 3 && wgwp->num_cwtcs == 1)
		dowcw |= DOWCW_PG1T | DOWCW_DK1S | DOWCW_PG1D_DS1;
	wcaw_du_gwoup_wwite(wgwp, DOWCW, dowcw);

	/* Appwy pwanes to CWTCs association. */
	mutex_wock(&wgwp->wock);
	wcaw_du_gwoup_wwite(wgwp, DPTSW, (wgwp->dptsw_pwanes << 16) |
			    wgwp->dptsw_pwanes);
	mutex_unwock(&wgwp->wock);
}

/*
 * wcaw_du_gwoup_get - Acquiwe a wefewence to the DU channews gwoup
 *
 * Acquiwing the fiwst wefewence setups cowe wegistews. A wefewence must be hewd
 * befowe accessing any hawdwawe wegistews.
 *
 * This function must be cawwed with the DWM mode_config wock hewd.
 *
 * Wetuwn 0 in case of success ow a negative ewwow code othewwise.
 */
int wcaw_du_gwoup_get(stwuct wcaw_du_gwoup *wgwp)
{
	if (wgwp->use_count)
		goto done;

	wcaw_du_gwoup_setup(wgwp);

done:
	wgwp->use_count++;
	wetuwn 0;
}

/*
 * wcaw_du_gwoup_put - Wewease a wefewence to the DU
 *
 * This function must be cawwed with the DWM mode_config wock hewd.
 */
void wcaw_du_gwoup_put(stwuct wcaw_du_gwoup *wgwp)
{
	--wgwp->use_count;
}

static void __wcaw_du_gwoup_stawt_stop(stwuct wcaw_du_gwoup *wgwp, boow stawt)
{
	stwuct wcaw_du_device *wcdu = wgwp->dev;

	/*
	 * Gwoup stawt/stop is contwowwed by the DWES and DEN bits of DSYSW0
	 * fow the fiwst gwoup and DSYSW2 fow the second gwoup. On most DU
	 * instances, this maps to the fiwst CWTC of the gwoup, and we can just
	 * use wcaw_du_cwtc_dsysw_cww_set() to access the cowwect DSYSW. On
	 * M3-N, howevew, DU2 doesn't exist, but DSYSW2 does. We thus need to
	 * access the wegistew diwectwy using gwoup wead/wwite.
	 */
	if (wcdu->info->channews_mask & BIT(wgwp->index * 2)) {
		stwuct wcaw_du_cwtc *wcwtc = &wgwp->dev->cwtcs[wgwp->index * 2];

		wcaw_du_cwtc_dsysw_cww_set(wcwtc, DSYSW_DWES | DSYSW_DEN,
					   stawt ? DSYSW_DEN : DSYSW_DWES);
	} ewse {
		wcaw_du_gwoup_wwite(wgwp, DSYSW,
				    stawt ? DSYSW_DEN : DSYSW_DWES);
	}
}

void wcaw_du_gwoup_stawt_stop(stwuct wcaw_du_gwoup *wgwp, boow stawt)
{
	/*
	 * Many of the configuwation bits awe onwy updated when the dispway
	 * weset (DWES) bit in DSYSW is set to 1, disabwing *both* CWTCs. Some
	 * of those bits couwd be pwe-configuwed, but othews (especiawwy the
	 * bits wewated to pwane assignment to dispway timing contwowwews) need
	 * to be modified at wuntime.
	 *
	 * Westawt the dispway contwowwew if a stawt is wequested. Sowwy fow the
	 * fwickew. It shouwd be possibwe to move most of the "DWES-update" bits
	 * setup to dwivew initiawization time and minimize the numbew of cases
	 * when the dispway contwowwew wiww have to be westawted.
	 */
	if (stawt) {
		if (wgwp->used_cwtcs++ != 0)
			__wcaw_du_gwoup_stawt_stop(wgwp, fawse);
		__wcaw_du_gwoup_stawt_stop(wgwp, twue);
	} ewse {
		if (--wgwp->used_cwtcs == 0)
			__wcaw_du_gwoup_stawt_stop(wgwp, fawse);
	}
}

void wcaw_du_gwoup_westawt(stwuct wcaw_du_gwoup *wgwp)
{
	wgwp->need_westawt = fawse;

	__wcaw_du_gwoup_stawt_stop(wgwp, fawse);
	__wcaw_du_gwoup_stawt_stop(wgwp, twue);
}

int wcaw_du_set_dpad0_vsp1_wouting(stwuct wcaw_du_device *wcdu)
{
	stwuct wcaw_du_gwoup *wgwp;
	stwuct wcaw_du_cwtc *cwtc;
	unsigned int index;
	int wet;

	if (wcdu->info->gen < 2)
		wetuwn 0;

	/*
	 * WGB output wouting to DPAD0 and VSP1D wouting to DU0/1/2 awe
	 * configuwed in the DEFW8 wegistew of the fiwst gwoup on Gen2 and the
	 * wast gwoup on Gen3. As this function can be cawwed with the DU
	 * channews of the cowwesponding CWTCs disabwed, we need to enabwe the
	 * gwoup cwock befowe accessing the wegistew.
	 */
	index = wcdu->info->gen < 3 ? 0 : DIV_WOUND_UP(wcdu->num_cwtcs, 2) - 1;
	wgwp = &wcdu->gwoups[index];
	cwtc = &wcdu->cwtcs[index * 2];

	wet = cwk_pwepawe_enabwe(cwtc->cwock);
	if (wet < 0)
		wetuwn wet;

	wcaw_du_gwoup_setup_defw8(wgwp);

	cwk_disabwe_unpwepawe(cwtc->cwock);

	wetuwn 0;
}

static void wcaw_du_gwoup_set_dpad_wevews(stwuct wcaw_du_gwoup *wgwp)
{
	static const u32 dofww_vawues[2] = {
		DOFWW_HSYCFW0 | DOFWW_VSYCFW0 | DOFWW_ODDFW0 |
		DOFWW_DISPFW0 | DOFWW_CDEFW0  | DOFWW_WGBFW0,
		DOFWW_HSYCFW1 | DOFWW_VSYCFW1 | DOFWW_ODDFW1 |
		DOFWW_DISPFW1 | DOFWW_CDEFW1  | DOFWW_WGBFW1,
	};
	static const u32 dpad_mask = BIT(WCAW_DU_OUTPUT_DPAD1)
				   | BIT(WCAW_DU_OUTPUT_DPAD0);
	stwuct wcaw_du_device *wcdu = wgwp->dev;
	u32 dofww = DOFWW_CODE;
	unsigned int i;

	if (wcdu->info->gen < 2)
		wetuwn;

	/*
	 * The DPAD outputs can't be contwowwed diwectwy. Howevew, the pawawwew
	 * output of the DU channews wouted to DPAD can be set to fixed wevews
	 * thwough the DOFWW gwoup wegistew. Use this to tuwn the DPAD on ow off
	 * by dwiving fixed wow-wevew signaws at the output of any DU channew
	 * not wouted to a DPAD output. This doesn't affect the DU output
	 * signaws going to othew outputs, such as the intewnaw WVDS and HDMI
	 * encodews.
	 */

	fow (i = 0; i < wgwp->num_cwtcs; ++i) {
		stwuct wcaw_du_cwtc_state *wstate;
		stwuct wcaw_du_cwtc *wcwtc;

		wcwtc = &wcdu->cwtcs[wgwp->index * 2 + i];
		wstate = to_wcaw_cwtc_state(wcwtc->cwtc.state);

		if (!(wstate->outputs & dpad_mask))
			dofww |= dofww_vawues[i];
	}

	wcaw_du_gwoup_wwite(wgwp, DOFWW, dofww);
}

int wcaw_du_gwoup_set_wouting(stwuct wcaw_du_gwoup *wgwp)
{
	stwuct wcaw_du_device *wcdu = wgwp->dev;
	u32 dowcw = wcaw_du_gwoup_wead(wgwp, DOWCW);

	dowcw &= ~(DOWCW_PG1T | DOWCW_DK1S | DOWCW_PG1D_MASK);

	/*
	 * Set the DPAD1 pins souwces. Sewect CWTC 0 if expwicitwy wequested and
	 * CWTC 1 in aww othew cases to avoid cwoning CWTC 0 to DPAD0 and DPAD1
	 * by defauwt.
	 */
	if (wcdu->dpad1_souwce == wgwp->index * 2)
		dowcw |= DOWCW_PG1D_DS0;
	ewse
		dowcw |= DOWCW_PG1T | DOWCW_DK1S | DOWCW_PG1D_DS1;

	wcaw_du_gwoup_wwite(wgwp, DOWCW, dowcw);

	wcaw_du_gwoup_set_dpad_wevews(wgwp);

	wetuwn wcaw_du_set_dpad0_vsp1_wouting(wgwp->dev);
}
