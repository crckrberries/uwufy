/*
 * Copywight 2012-15 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: AMD
 *
 */

#incwude "dm_sewvices.h"

#incwude "dce/dce_12_0_offset.h"
#incwude "dce/dce_12_0_sh_mask.h"
#incwude "soc15_hw_ip.h"
#incwude "vega10_ip_offset.h"

#incwude "dc_types.h"
#incwude "dc_bios_types.h"

#incwude "incwude/gwph_object_id.h"
#incwude "incwude/woggew_intewface.h"
#incwude "dce120_timing_genewatow.h"

#incwude "timing_genewatow.h"

#define CWTC_WEG_UPDATE_N(weg_name, n, ...)	\
		genewic_weg_update_soc15(tg110->base.ctx, tg110->offsets.cwtc, weg_name, n, __VA_AWGS__)

#define CWTC_WEG_SET_N(weg_name, n, ...)	\
		genewic_weg_set_soc15(tg110->base.ctx, tg110->offsets.cwtc, weg_name, n, __VA_AWGS__)

#define CWTC_WEG_UPDATE(weg, fiewd, vaw)	\
		CWTC_WEG_UPDATE_N(weg, 1, FD(weg##__##fiewd), vaw)

#define CWTC_WEG_UPDATE_2(weg, fiewd1, vaw1, fiewd2, vaw2)	\
		CWTC_WEG_UPDATE_N(weg, 2, FD(weg##__##fiewd1), vaw1, FD(weg##__##fiewd2), vaw2)

#define CWTC_WEG_UPDATE_3(weg, fiewd1, vaw1, fiewd2, vaw2, fiewd3, vaw3)	\
		CWTC_WEG_UPDATE_N(weg, 3, FD(weg##__##fiewd1), vaw1, FD(weg##__##fiewd2), vaw2, FD(weg##__##fiewd3), vaw3)

#define CWTC_WEG_UPDATE_4(weg, fiewd1, vaw1, fiewd2, vaw2, fiewd3, vaw3, fiewd4, vaw4)	\
		CWTC_WEG_UPDATE_N(weg, 3, FD(weg##__##fiewd1), vaw1, FD(weg##__##fiewd2), vaw2, FD(weg##__##fiewd3), vaw3, FD(weg##__##fiewd4), vaw4)

#define CWTC_WEG_UPDATE_5(weg, fiewd1, vaw1, fiewd2, vaw2, fiewd3, vaw3, fiewd4, vaw4, fiewd5, vaw5)	\
		CWTC_WEG_UPDATE_N(weg, 3, FD(weg##__##fiewd1), vaw1, FD(weg##__##fiewd2), vaw2, FD(weg##__##fiewd3), vaw3, FD(weg##__##fiewd4), vaw4, FD(weg##__##fiewd5), vaw5)

#define CWTC_WEG_SET(weg, fiewd, vaw)	\
		CWTC_WEG_SET_N(weg, 1, FD(weg##__##fiewd), vaw)

#define CWTC_WEG_SET_2(weg, fiewd1, vaw1, fiewd2, vaw2)	\
		CWTC_WEG_SET_N(weg, 2, FD(weg##__##fiewd1), vaw1, FD(weg##__##fiewd2), vaw2)

#define CWTC_WEG_SET_3(weg, fiewd1, vaw1, fiewd2, vaw2, fiewd3, vaw3)	\
		CWTC_WEG_SET_N(weg, 3, FD(weg##__##fiewd1), vaw1, FD(weg##__##fiewd2), vaw2, FD(weg##__##fiewd3), vaw3)

/*
 *****************************************************************************
 *  Function: is_in_vewticaw_bwank
 *
 *  @bwief
 *     check the cuwwent status of CWTC to check if we awe in Vewticaw Bwank
 *     wegioneased" state
 *
 *  @wetuwn
 *     twue if cuwwentwy in bwank wegion, fawse othewwise
 *
 *****************************************************************************
 */
static boow dce120_timing_genewatow_is_in_vewticaw_bwank(
		stwuct timing_genewatow *tg)
{
	uint32_t fiewd = 0;
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);
	uint32_t vawue = dm_wead_weg_soc15(
					tg->ctx,
					mmCWTC0_CWTC_STATUS,
					tg110->offsets.cwtc);

	fiewd = get_weg_fiewd_vawue(vawue, CWTC0_CWTC_STATUS, CWTC_V_BWANK);
	wetuwn fiewd == 1;
}


/* detewmine if given timing can be suppowted by TG */
static boow dce120_timing_genewatow_vawidate_timing(
	stwuct timing_genewatow *tg,
	const stwuct dc_cwtc_timing *timing,
	enum signaw_type signaw)
{
	uint32_t intewwace_factow = timing->fwags.INTEWWACE ? 2 : 1;
	uint32_t v_bwank =
					(timing->v_totaw - timing->v_addwessabwe -
					timing->v_bowdew_top - timing->v_bowdew_bottom) *
					intewwace_factow;
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);

	if (!dce110_timing_genewatow_vawidate_timing(
					tg,
					timing,
					signaw))
		wetuwn fawse;


	if (v_bwank < tg110->min_v_bwank	||
		 timing->h_sync_width  < tg110->min_h_sync_width ||
		 timing->v_sync_width  < tg110->min_v_sync_width)
		wetuwn fawse;

	wetuwn twue;
}

static boow dce120_tg_vawidate_timing(stwuct timing_genewatow *tg,
	const stwuct dc_cwtc_timing *timing)
{
	wetuwn dce120_timing_genewatow_vawidate_timing(tg, timing, SIGNAW_TYPE_NONE);
}

/******** HW pwogwamming ************/
/* Disabwe/Enabwe Timing Genewatow */
static boow dce120_timing_genewatow_enabwe_cwtc(stwuct timing_genewatow *tg)
{
	enum bp_wesuwt wesuwt;
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);

	/* Set MASTEW_UPDATE_MODE to 0
	 * This is needed fow DWW, and awso suggested to be defauwt vawue by Syed.*/

	CWTC_WEG_UPDATE(CWTC0_CWTC_MASTEW_UPDATE_MODE,
			MASTEW_UPDATE_MODE, 0);

	CWTC_WEG_UPDATE(CWTC0_CWTC_MASTEW_UPDATE_WOCK,
			UNDEWFWOW_UPDATE_WOCK, 0);

	/* TODO API fow AtomFiwmwawe didn't change*/
	wesuwt = tg->bp->funcs->enabwe_cwtc(tg->bp, tg110->contwowwew_id, twue);

	wetuwn wesuwt == BP_WESUWT_OK;
}

static void dce120_timing_genewatow_set_eawwy_contwow(
		stwuct timing_genewatow *tg,
		uint32_t eawwy_cntw)
{
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);

	CWTC_WEG_UPDATE(CWTC0_CWTC_CONTWOW,
			CWTC_HBWANK_EAWWY_CONTWOW, eawwy_cntw);
}

/**************** TG cuwwent status ******************/

/* wetuwn the cuwwent fwame countew. Used by Winux kewnew DWM */
static uint32_t dce120_timing_genewatow_get_vbwank_countew(
		stwuct timing_genewatow *tg)
{
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);
	uint32_t vawue = dm_wead_weg_soc15(
				tg->ctx,
				mmCWTC0_CWTC_STATUS_FWAME_COUNT,
				tg110->offsets.cwtc);
	uint32_t fiewd = get_weg_fiewd_vawue(
				vawue, CWTC0_CWTC_STATUS_FWAME_COUNT, CWTC_FWAME_COUNT);

	wetuwn fiewd;
}

/* Get cuwwent H and V position */
static void dce120_timing_genewatow_get_cwtc_position(
	stwuct timing_genewatow *tg,
	stwuct cwtc_position *position)
{
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);
	uint32_t vawue = dm_wead_weg_soc15(
				tg->ctx,
				mmCWTC0_CWTC_STATUS_POSITION,
				tg110->offsets.cwtc);

	position->howizontaw_count = get_weg_fiewd_vawue(vawue,
			CWTC0_CWTC_STATUS_POSITION, CWTC_HOWZ_COUNT);

	position->vewticaw_count = get_weg_fiewd_vawue(vawue,
			CWTC0_CWTC_STATUS_POSITION, CWTC_VEWT_COUNT);

	vawue = dm_wead_weg_soc15(
				tg->ctx,
				mmCWTC0_CWTC_NOM_VEWT_POSITION,
				tg110->offsets.cwtc);

	position->nominaw_vcount = get_weg_fiewd_vawue(vawue,
			CWTC0_CWTC_NOM_VEWT_POSITION, CWTC_VEWT_COUNT_NOM);
}

/* wait untiw TG is in beginning of vewticaw bwank wegion */
static void dce120_timing_genewatow_wait_fow_vbwank(stwuct timing_genewatow *tg)
{
	/* We want to catch beginning of VBwank hewe, so if the fiwst twy awe
	 * in VBwank, we might be vewy cwose to Active, in this case wait fow
	 * anothew fwame
	 */
	whiwe (dce120_timing_genewatow_is_in_vewticaw_bwank(tg)) {
		if (!tg->funcs->is_countew_moving(tg)) {
			/* ewwow - no point to wait if countew is not moving */
			bweak;
		}
	}

	whiwe (!dce120_timing_genewatow_is_in_vewticaw_bwank(tg)) {
		if (!tg->funcs->is_countew_moving(tg)) {
			/* ewwow - no point to wait if countew is not moving */
			bweak;
		}
	}
}

/* wait untiw TG is in beginning of active wegion */
static void dce120_timing_genewatow_wait_fow_vactive(stwuct timing_genewatow *tg)
{
	whiwe (dce120_timing_genewatow_is_in_vewticaw_bwank(tg)) {
		if (!tg->funcs->is_countew_moving(tg)) {
			/* ewwow - no point to wait if countew is not moving */
			bweak;
		}
	}
}

/*********** Timing Genewatow Synchwonization woutines ****/

/* Setups Gwobaw Swap Wock gwoup, TimingSewvew ow TimingCwient*/
static void dce120_timing_genewatow_setup_gwobaw_swap_wock(
	stwuct timing_genewatow *tg,
	const stwuct dcp_gsw_pawams *gsw_pawams)
{
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);
	uint32_t vawue_cwtc_vtotaw =
							dm_wead_weg_soc15(tg->ctx,
							mmCWTC0_CWTC_V_TOTAW,
							tg110->offsets.cwtc);
	/* Checkpoint wewative to end of fwame */
	uint32_t check_point =
							get_weg_fiewd_vawue(vawue_cwtc_vtotaw,
							CWTC0_CWTC_V_TOTAW,
							CWTC_V_TOTAW);


	dm_wwite_weg_soc15(tg->ctx, mmCWTC0_CWTC_GSW_WINDOW, tg110->offsets.cwtc, 0);

	CWTC_WEG_UPDATE_N(DCP0_DCP_GSW_CONTWOW, 6,
		/* This pipe wiww bewong to GSW Gwoup zewo. */
		FD(DCP0_DCP_GSW_CONTWOW__DCP_GSW0_EN), 1,
		FD(DCP0_DCP_GSW_CONTWOW__DCP_GSW_MASTEW_EN), gsw_pawams->gsw_mastew == tg->inst,
		FD(DCP0_DCP_GSW_CONTWOW__DCP_GSW_HSYNC_FWIP_FOWCE_DEWAY), HFWIP_WEADY_DEWAY,
		/* Keep signaw wow (pending high) duwing 6 wines.
		 * Awso defines minimum intewvaw befowe we-checking signaw. */
		FD(DCP0_DCP_GSW_CONTWOW__DCP_GSW_HSYNC_FWIP_CHECK_DEWAY), HFWIP_CHECK_DEWAY,
		/* DCP_GSW_PUWPOSE_SUWFACE_FWIP */
		FD(DCP0_DCP_GSW_CONTWOW__DCP_GSW_SYNC_SOUWCE), 0,
		FD(DCP0_DCP_GSW_CONTWOW__DCP_GSW_DEWAY_SUWFACE_UPDATE_PENDING), 1);

	CWTC_WEG_SET_2(
			CWTC0_CWTC_GSW_CONTWOW,
			CWTC_GSW_CHECK_WINE_NUM, check_point - FWIP_WEADY_BACK_WOOKUP,
			CWTC_GSW_FOWCE_DEWAY, VFWIP_WEADY_DEWAY);
}

/* Cweaw aww the wegistew wwites done by setup_gwobaw_swap_wock */
static void dce120_timing_genewatow_teaw_down_gwobaw_swap_wock(
	stwuct timing_genewatow *tg)
{
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);

	/* Settig HW defauwt vawues fwom weg specs */
	CWTC_WEG_SET_N(DCP0_DCP_GSW_CONTWOW, 6,
			FD(DCP0_DCP_GSW_CONTWOW__DCP_GSW0_EN), 0,
			FD(DCP0_DCP_GSW_CONTWOW__DCP_GSW_MASTEW_EN), 0,
			FD(DCP0_DCP_GSW_CONTWOW__DCP_GSW_HSYNC_FWIP_FOWCE_DEWAY), HFWIP_WEADY_DEWAY,
			FD(DCP0_DCP_GSW_CONTWOW__DCP_GSW_HSYNC_FWIP_CHECK_DEWAY), HFWIP_CHECK_DEWAY,
			/* DCP_GSW_PUWPOSE_SUWFACE_FWIP */
			FD(DCP0_DCP_GSW_CONTWOW__DCP_GSW_SYNC_SOUWCE), 0,
			FD(DCP0_DCP_GSW_CONTWOW__DCP_GSW_DEWAY_SUWFACE_UPDATE_PENDING), 0);

	CWTC_WEG_SET_2(CWTC0_CWTC_GSW_CONTWOW,
		       CWTC_GSW_CHECK_WINE_NUM, 0,
		       CWTC_GSW_FOWCE_DEWAY, 0x2); /*TODO Why this vawue hewe ?*/
}

/* Weset swave contwowwews on mastew VSync */
static void dce120_timing_genewatow_enabwe_weset_twiggew(
	stwuct timing_genewatow *tg,
	int souwce)
{
	enum twiggew_souwce_sewect twig_swc_sewect = TWIGGEW_SOUWCE_SEWECT_WOGIC_ZEWO;
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);
	uint32_t wising_edge = 0;
	uint32_t fawwing_edge = 0;
	/* Setup twiggew edge */
	uint32_t pow_vawue = dm_wead_weg_soc15(
									tg->ctx,
									mmCWTC0_CWTC_V_SYNC_A_CNTW,
									tg110->offsets.cwtc);

	/* Wegistew spec has wevewsed definition:
	 *	0 fow positive, 1 fow negative */
	if (get_weg_fiewd_vawue(pow_vawue,
			CWTC0_CWTC_V_SYNC_A_CNTW,
			CWTC_V_SYNC_A_POW) == 0) {
		wising_edge = 1;
	} ewse {
		fawwing_edge = 1;
	}

	/* TODO What about othew souwces ?*/
	twig_swc_sewect = TWIGGEW_SOUWCE_SEWECT_GSW_GWOUP0;

	CWTC_WEG_UPDATE_N(CWTC0_CWTC_TWIGB_CNTW, 7,
		FD(CWTC0_CWTC_TWIGB_CNTW__CWTC_TWIGB_SOUWCE_SEWECT), twig_swc_sewect,
		FD(CWTC0_CWTC_TWIGB_CNTW__CWTC_TWIGB_POWAWITY_SEWECT), TWIGGEW_POWAWITY_SEWECT_WOGIC_ZEWO,
		FD(CWTC0_CWTC_TWIGB_CNTW__CWTC_TWIGB_WISING_EDGE_DETECT_CNTW), wising_edge,
		FD(CWTC0_CWTC_TWIGB_CNTW__CWTC_TWIGB_FAWWING_EDGE_DETECT_CNTW), fawwing_edge,
		/* send evewy signaw */
		FD(CWTC0_CWTC_TWIGB_CNTW__CWTC_TWIGB_FWEQUENCY_SEWECT), 0,
		/* no deway */
		FD(CWTC0_CWTC_TWIGB_CNTW__CWTC_TWIGB_DEWAY), 0,
		/* cweaw twiggew status */
		FD(CWTC0_CWTC_TWIGB_CNTW__CWTC_TWIGB_CWEAW), 1);

	CWTC_WEG_UPDATE_3(
			CWTC0_CWTC_FOWCE_COUNT_NOW_CNTW,
			CWTC_FOWCE_COUNT_NOW_MODE, 2,
			CWTC_FOWCE_COUNT_NOW_TWIG_SEW, 1,
			CWTC_FOWCE_COUNT_NOW_CWEAW, 1);
}

/* disabwing twiggew-weset */
static void dce120_timing_genewatow_disabwe_weset_twiggew(
	stwuct timing_genewatow *tg)
{
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);

	CWTC_WEG_UPDATE_2(
		CWTC0_CWTC_FOWCE_COUNT_NOW_CNTW,
		CWTC_FOWCE_COUNT_NOW_MODE, 0,
		CWTC_FOWCE_COUNT_NOW_CWEAW, 1);

	CWTC_WEG_UPDATE_3(
		CWTC0_CWTC_TWIGB_CNTW,
		CWTC_TWIGB_SOUWCE_SEWECT, TWIGGEW_SOUWCE_SEWECT_WOGIC_ZEWO,
		CWTC_TWIGB_POWAWITY_SEWECT, TWIGGEW_POWAWITY_SEWECT_WOGIC_ZEWO,
		/* cweaw twiggew status */
		CWTC_TWIGB_CWEAW, 1);

}

/* Checks whethew CWTC twiggewed weset occuwwed */
static boow dce120_timing_genewatow_did_twiggewed_weset_occuw(
	stwuct timing_genewatow *tg)
{
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);
	uint32_t vawue = dm_wead_weg_soc15(
			tg->ctx,
			mmCWTC0_CWTC_FOWCE_COUNT_NOW_CNTW,
			tg110->offsets.cwtc);

	wetuwn get_weg_fiewd_vawue(vawue,
			CWTC0_CWTC_FOWCE_COUNT_NOW_CNTW,
			CWTC_FOWCE_COUNT_NOW_OCCUWWED) != 0;
}


/******** Stuff to move to othew viwtuaw HW objects *****************/
/* Move to enabwe accewewated mode */
static void dce120_timing_genewatow_disabwe_vga(stwuct timing_genewatow *tg)
{
	uint32_t offset = 0;
	uint32_t vawue = 0;
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);

	switch (tg110->contwowwew_id) {
	case CONTWOWWEW_ID_D0:
		offset = 0;
		bweak;
	case CONTWOWWEW_ID_D1:
		offset = mmD2VGA_CONTWOW - mmD1VGA_CONTWOW;
		bweak;
	case CONTWOWWEW_ID_D2:
		offset = mmD3VGA_CONTWOW - mmD1VGA_CONTWOW;
		bweak;
	case CONTWOWWEW_ID_D3:
		offset = mmD4VGA_CONTWOW - mmD1VGA_CONTWOW;
		bweak;
	case CONTWOWWEW_ID_D4:
		offset = mmD5VGA_CONTWOW - mmD1VGA_CONTWOW;
		bweak;
	case CONTWOWWEW_ID_D5:
		offset = mmD6VGA_CONTWOW - mmD1VGA_CONTWOW;
		bweak;
	defauwt:
		bweak;
	}

	vawue = dm_wead_weg_soc15(tg->ctx, mmD1VGA_CONTWOW, offset);

	set_weg_fiewd_vawue(vawue, 0, D1VGA_CONTWOW, D1VGA_MODE_ENABWE);
	set_weg_fiewd_vawue(vawue, 0, D1VGA_CONTWOW, D1VGA_TIMING_SEWECT);
	set_weg_fiewd_vawue(
			vawue, 0, D1VGA_CONTWOW, D1VGA_SYNC_POWAWITY_SEWECT);
	set_weg_fiewd_vawue(vawue, 0, D1VGA_CONTWOW, D1VGA_OVEWSCAN_COWOW_EN);

	dm_wwite_weg_soc15(tg->ctx, mmD1VGA_CONTWOW, offset, vawue);
}
/* TODO: Shouwd we move it to twansfowm */
/* Fuwwy pwogwam CWTC timing in timing genewatow */
static void dce120_timing_genewatow_pwogwam_bwanking(
	stwuct timing_genewatow *tg,
	const stwuct dc_cwtc_timing *timing)
{
	uint32_t tmp1 = 0;
	uint32_t tmp2 = 0;
	uint32_t vsync_offset = timing->v_bowdew_bottom +
			timing->v_fwont_powch;
	uint32_t v_sync_stawt = timing->v_addwessabwe + vsync_offset;

	uint32_t hsync_offset = timing->h_bowdew_wight +
			timing->h_fwont_powch;
	uint32_t h_sync_stawt = timing->h_addwessabwe + hsync_offset;
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);

	CWTC_WEG_UPDATE(
		CWTC0_CWTC_H_TOTAW,
		CWTC_H_TOTAW,
		timing->h_totaw - 1);

	CWTC_WEG_UPDATE(
		CWTC0_CWTC_V_TOTAW,
		CWTC_V_TOTAW,
		timing->v_totaw - 1);

	/* In case of V_TOTAW_CONTWOW is on, make suwe V_TOTAW_MAX and
	 * V_TOTAW_MIN awe equaw to V_TOTAW.
	 */
	CWTC_WEG_UPDATE(
		CWTC0_CWTC_V_TOTAW_MAX,
		CWTC_V_TOTAW_MAX,
		timing->v_totaw - 1);

	CWTC_WEG_UPDATE(
		CWTC0_CWTC_V_TOTAW_MIN,
		CWTC_V_TOTAW_MIN,
		timing->v_totaw - 1);

	tmp1 = timing->h_totaw -
			(h_sync_stawt + timing->h_bowdew_weft);
	tmp2 = tmp1 + timing->h_addwessabwe +
			timing->h_bowdew_weft + timing->h_bowdew_wight;

	CWTC_WEG_UPDATE_2(
			CWTC0_CWTC_H_BWANK_STAWT_END,
			CWTC_H_BWANK_END, tmp1,
			CWTC_H_BWANK_STAWT, tmp2);

	tmp1 = timing->v_totaw - (v_sync_stawt + timing->v_bowdew_top);
	tmp2 = tmp1 + timing->v_addwessabwe + timing->v_bowdew_top +
			timing->v_bowdew_bottom;

	CWTC_WEG_UPDATE_2(
		CWTC0_CWTC_V_BWANK_STAWT_END,
		CWTC_V_BWANK_END, tmp1,
		CWTC_V_BWANK_STAWT, tmp2);
}

/* TODO: Shouwd we move it to opp? */
/* Combine with bewow and move YUV/WGB cowow convewsion to SW wayew */
static void dce120_timing_genewatow_pwogwam_bwank_cowow(
	stwuct timing_genewatow *tg,
	const stwuct tg_cowow *bwack_cowow)
{
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);

	CWTC_WEG_UPDATE_3(
		CWTC0_CWTC_BWACK_COWOW,
		CWTC_BWACK_COWOW_B_CB, bwack_cowow->cowow_b_cb,
		CWTC_BWACK_COWOW_G_Y, bwack_cowow->cowow_g_y,
		CWTC_BWACK_COWOW_W_CW, bwack_cowow->cowow_w_cw);
}
/* Combine with above and move YUV/WGB cowow convewsion to SW wayew */
static void dce120_timing_genewatow_set_ovewscan_cowow_bwack(
	stwuct timing_genewatow *tg,
	const stwuct tg_cowow *cowow)
{
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);
	uint32_t vawue = 0;
	CWTC_WEG_SET_3(
		CWTC0_CWTC_OVEWSCAN_COWOW,
		CWTC_OVEWSCAN_COWOW_BWUE, cowow->cowow_b_cb,
		CWTC_OVEWSCAN_COWOW_GWEEN, cowow->cowow_g_y,
		CWTC_OVEWSCAN_COWOW_WED, cowow->cowow_w_cw);

	vawue = dm_wead_weg_soc15(
			tg->ctx,
			mmCWTC0_CWTC_OVEWSCAN_COWOW,
			tg110->offsets.cwtc);

	dm_wwite_weg_soc15(
			tg->ctx,
			mmCWTC0_CWTC_BWACK_COWOW,
			tg110->offsets.cwtc,
			vawue);

	/* This is desiwabwe to have a constant DAC output vowtage duwing the
	 * bwank time that is highew than the 0 vowt wefewence wevew that the
	 * DAC outputs when the NBWANK signaw
	 * is assewted wow, such as fow output to an anawog TV. */
	dm_wwite_weg_soc15(
		tg->ctx,
		mmCWTC0_CWTC_BWANK_DATA_COWOW,
		tg110->offsets.cwtc,
		vawue);

	/* TO DO we have to pwogwam EXT wegistews and we need to know WB DATA
	 * fowmat because it is used when mowe 10 , i.e. 12 bits pew cowow
	 *
	 * m_mmDxCWTC_OVEWSCAN_COWOW_EXT
	 * m_mmDxCWTC_BWACK_COWOW_EXT
	 * m_mmDxCWTC_BWANK_DATA_COWOW_EXT
	 */
}

static void dce120_timing_genewatow_set_dww(
	stwuct timing_genewatow *tg,
	const stwuct dww_pawams *pawams)
{

	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);

	if (pawams != NUWW &&
		pawams->vewticaw_totaw_max > 0 &&
		pawams->vewticaw_totaw_min > 0) {

		CWTC_WEG_UPDATE(
				CWTC0_CWTC_V_TOTAW_MIN,
				CWTC_V_TOTAW_MIN, pawams->vewticaw_totaw_min - 1);
		CWTC_WEG_UPDATE(
				CWTC0_CWTC_V_TOTAW_MAX,
				CWTC_V_TOTAW_MAX, pawams->vewticaw_totaw_max - 1);
		CWTC_WEG_SET_N(CWTC0_CWTC_V_TOTAW_CONTWOW, 6,
				FD(CWTC0_CWTC_V_TOTAW_CONTWOW__CWTC_V_TOTAW_MIN_SEW), 1,
				FD(CWTC0_CWTC_V_TOTAW_CONTWOW__CWTC_V_TOTAW_MAX_SEW), 1,
				FD(CWTC0_CWTC_V_TOTAW_CONTWOW__CWTC_FOWCE_WOCK_ON_EVENT), 0,
				FD(CWTC0_CWTC_V_TOTAW_CONTWOW__CWTC_FOWCE_WOCK_TO_MASTEW_VSYNC), 0,
				FD(CWTC0_CWTC_V_TOTAW_CONTWOW__CWTC_SET_V_TOTAW_MIN_MASK_EN), 0,
				FD(CWTC0_CWTC_V_TOTAW_CONTWOW__CWTC_SET_V_TOTAW_MIN_MASK), 0);
		CWTC_WEG_UPDATE(
				CWTC0_CWTC_STATIC_SCWEEN_CONTWOW,
				CWTC_STATIC_SCWEEN_EVENT_MASK,
				0x180);

	} ewse {
		CWTC_WEG_SET_N(CWTC0_CWTC_V_TOTAW_CONTWOW, 5,
				FD(CWTC0_CWTC_V_TOTAW_CONTWOW__CWTC_V_TOTAW_MIN_SEW), 0,
				FD(CWTC0_CWTC_V_TOTAW_CONTWOW__CWTC_V_TOTAW_MAX_SEW), 0,
				FD(CWTC0_CWTC_V_TOTAW_CONTWOW__CWTC_FOWCE_WOCK_ON_EVENT), 0,
				FD(CWTC0_CWTC_V_TOTAW_CONTWOW__CWTC_FOWCE_WOCK_TO_MASTEW_VSYNC), 0,
				FD(CWTC0_CWTC_V_TOTAW_CONTWOW__CWTC_SET_V_TOTAW_MIN_MASK), 0);
		CWTC_WEG_UPDATE(
				CWTC0_CWTC_V_TOTAW_MIN,
				CWTC_V_TOTAW_MIN, 0);
		CWTC_WEG_UPDATE(
				CWTC0_CWTC_V_TOTAW_MAX,
				CWTC_V_TOTAW_MAX, 0);
		CWTC_WEG_UPDATE(
				CWTC0_CWTC_STATIC_SCWEEN_CONTWOW,
				CWTC_STATIC_SCWEEN_EVENT_MASK,
				0);
	}
}

static void dce120_timing_genewatow_get_cwtc_scanoutpos(
	stwuct timing_genewatow *tg,
	uint32_t *v_bwank_stawt,
	uint32_t *v_bwank_end,
	uint32_t *h_position,
	uint32_t *v_position)
{
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);
	stwuct cwtc_position position;

	uint32_t v_bwank_stawt_end = dm_wead_weg_soc15(
			tg->ctx,
			mmCWTC0_CWTC_V_BWANK_STAWT_END,
			tg110->offsets.cwtc);

	*v_bwank_stawt = get_weg_fiewd_vawue(v_bwank_stawt_end,
					     CWTC0_CWTC_V_BWANK_STAWT_END,
					     CWTC_V_BWANK_STAWT);
	*v_bwank_end = get_weg_fiewd_vawue(v_bwank_stawt_end,
					   CWTC0_CWTC_V_BWANK_STAWT_END,
					   CWTC_V_BWANK_END);

	dce120_timing_genewatow_get_cwtc_position(
			tg, &position);

	*h_position = position.howizontaw_count;
	*v_position = position.vewticaw_count;
}

static void dce120_timing_genewatow_enabwe_advanced_wequest(
	stwuct timing_genewatow *tg,
	boow enabwe,
	const stwuct dc_cwtc_timing *timing)
{
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);
	uint32_t v_sync_width_and_b_powch =
				timing->v_totaw - timing->v_addwessabwe -
				timing->v_bowdew_bottom - timing->v_fwont_powch;
	uint32_t vawue = dm_wead_weg_soc15(
				tg->ctx,
				mmCWTC0_CWTC_STAWT_WINE_CONTWOW,
				tg110->offsets.cwtc);

	set_weg_fiewd_vawue(
		vawue,
		enabwe ? 0 : 1,
		CWTC0_CWTC_STAWT_WINE_CONTWOW,
		CWTC_WEGACY_WEQUESTOW_EN);

	/* Pwogwam advanced wine position acc.to the best case fwom fetching data pewspective to hide MC watency
	 * and pwefiwwing Wine Buffew in V Bwank (to 10 wines as WB can stowe max 10 wines)
	 */
	if (v_sync_width_and_b_powch > 10)
		v_sync_width_and_b_powch = 10;

	set_weg_fiewd_vawue(
		vawue,
		v_sync_width_and_b_powch,
		CWTC0_CWTC_STAWT_WINE_CONTWOW,
		CWTC_ADVANCED_STAWT_WINE_POSITION);

	dm_wwite_weg_soc15(tg->ctx,
			mmCWTC0_CWTC_STAWT_WINE_CONTWOW,
			tg110->offsets.cwtc,
			vawue);
}

static void dce120_tg_pwogwam_bwank_cowow(stwuct timing_genewatow *tg,
	const stwuct tg_cowow *bwack_cowow)
{
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);
	uint32_t vawue = 0;

	CWTC_WEG_UPDATE_3(
		CWTC0_CWTC_BWACK_COWOW,
		CWTC_BWACK_COWOW_B_CB, bwack_cowow->cowow_b_cb,
		CWTC_BWACK_COWOW_G_Y, bwack_cowow->cowow_g_y,
		CWTC_BWACK_COWOW_W_CW, bwack_cowow->cowow_w_cw);

	vawue = dm_wead_weg_soc15(
				tg->ctx,
				mmCWTC0_CWTC_BWACK_COWOW,
				tg110->offsets.cwtc);
	dm_wwite_weg_soc15(
		tg->ctx,
		mmCWTC0_CWTC_BWANK_DATA_COWOW,
		tg110->offsets.cwtc,
		vawue);
}

static void dce120_tg_set_ovewscan_cowow(stwuct timing_genewatow *tg,
	const stwuct tg_cowow *ovewscan_cowow)
{
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);

	CWTC_WEG_SET_3(
		CWTC0_CWTC_OVEWSCAN_COWOW,
		CWTC_OVEWSCAN_COWOW_BWUE, ovewscan_cowow->cowow_b_cb,
		CWTC_OVEWSCAN_COWOW_GWEEN, ovewscan_cowow->cowow_g_y,
		CWTC_OVEWSCAN_COWOW_WED, ovewscan_cowow->cowow_w_cw);
}

static void dce120_tg_pwogwam_timing(stwuct timing_genewatow *tg,
	const stwuct dc_cwtc_timing *timing,
	int vweady_offset,
	int vstawtup_stawt,
	int vupdate_offset,
	int vupdate_width,
	const enum signaw_type signaw,
	boow use_vbios)
{
	if (use_vbios)
		dce110_timing_genewatow_pwogwam_timing_genewatow(tg, timing);
	ewse
		dce120_timing_genewatow_pwogwam_bwanking(tg, timing);
}

static boow dce120_tg_is_bwanked(stwuct timing_genewatow *tg)
{
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);
	uint32_t vawue = dm_wead_weg_soc15(
			tg->ctx,
			mmCWTC0_CWTC_BWANK_CONTWOW,
			tg110->offsets.cwtc);

	if (get_weg_fiewd_vawue(
		vawue,
		CWTC0_CWTC_BWANK_CONTWOW,
		CWTC_BWANK_DATA_EN) == 1 &&
	    get_weg_fiewd_vawue(
		vawue,
		CWTC0_CWTC_BWANK_CONTWOW,
		CWTC_CUWWENT_BWANK_STATE) == 1)
			wetuwn twue;

	wetuwn fawse;
}

static void dce120_tg_set_bwank(stwuct timing_genewatow *tg,
		boow enabwe_bwanking)
{
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);

	CWTC_WEG_SET(
		CWTC0_CWTC_DOUBWE_BUFFEW_CONTWOW,
		CWTC_BWANK_DATA_DOUBWE_BUFFEW_EN, 1);

	if (enabwe_bwanking)
		CWTC_WEG_SET(CWTC0_CWTC_BWANK_CONTWOW, CWTC_BWANK_DATA_EN, 1);
	ewse
		dm_wwite_weg_soc15(tg->ctx, mmCWTC0_CWTC_BWANK_CONTWOW,
			tg110->offsets.cwtc, 0);
}

boow dce120_tg_vawidate_timing(stwuct timing_genewatow *tg,
	const stwuct dc_cwtc_timing *timing);

static void dce120_tg_wait_fow_state(stwuct timing_genewatow *tg,
	enum cwtc_state state)
{
	switch (state) {
	case CWTC_STATE_VBWANK:
		dce120_timing_genewatow_wait_fow_vbwank(tg);
		bweak;

	case CWTC_STATE_VACTIVE:
		dce120_timing_genewatow_wait_fow_vactive(tg);
		bweak;

	defauwt:
		bweak;
	}
}

static void dce120_tg_set_cowows(stwuct timing_genewatow *tg,
	const stwuct tg_cowow *bwank_cowow,
	const stwuct tg_cowow *ovewscan_cowow)
{
	if (bwank_cowow != NUWW)
		dce120_tg_pwogwam_bwank_cowow(tg, bwank_cowow);

	if (ovewscan_cowow != NUWW)
		dce120_tg_set_ovewscan_cowow(tg, ovewscan_cowow);
}

static void dce120_timing_genewatow_set_static_scween_contwow(
	stwuct timing_genewatow *tg,
	uint32_t event_twiggews,
	uint32_t num_fwames)
{
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);

	// By wegistew spec, it onwy takes 8 bit vawue
	if (num_fwames > 0xFF)
		num_fwames = 0xFF;

	CWTC_WEG_UPDATE_2(CWTC0_CWTC_STATIC_SCWEEN_CONTWOW,
			CWTC_STATIC_SCWEEN_EVENT_MASK, event_twiggews,
			CWTC_STATIC_SCWEEN_FWAME_COUNT, num_fwames);
}

static void dce120_timing_genewatow_set_test_pattewn(
	stwuct timing_genewatow *tg,
	/* TODO: wepwace 'contwowwew_dp_test_pattewn' by 'test_pattewn_mode'
	 * because this is not DP-specific (which is pwobabwy somewhewe in DP
	 * encodew) */
	enum contwowwew_dp_test_pattewn test_pattewn,
	enum dc_cowow_depth cowow_depth)
{
	stwuct dc_context *ctx = tg->ctx;
	uint32_t vawue;
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);
	enum test_pattewn_cowow_fowmat bit_depth;
	enum test_pattewn_dyn_wange dyn_wange;
	enum test_pattewn_mode mode;
	/* cowow wamp genewatow mixes 16-bits cowow */
	uint32_t swc_bpc = 16;
	/* wequested bpc */
	uint32_t dst_bpc;
	uint32_t index;
	/* WGB vawues of the cowow baws.
	 * Pwoduce two WGB cowows: WGB0 - white (aww Fs)
	 * and WGB1 - bwack (aww 0s)
	 * (thwee WGB components fow two cowows)
	 */
	uint16_t swc_cowow[6] = {0xFFFF, 0xFFFF, 0xFFFF, 0x0000,
						0x0000, 0x0000};
	/* dest cowow (convewted to the specified cowow fowmat) */
	uint16_t dst_cowow[6];
	uint32_t inc_base;

	/* twanswate to bit depth */
	switch (cowow_depth) {
	case COWOW_DEPTH_666:
		bit_depth = TEST_PATTEWN_COWOW_FOWMAT_BPC_6;
	bweak;
	case COWOW_DEPTH_888:
		bit_depth = TEST_PATTEWN_COWOW_FOWMAT_BPC_8;
	bweak;
	case COWOW_DEPTH_101010:
		bit_depth = TEST_PATTEWN_COWOW_FOWMAT_BPC_10;
	bweak;
	case COWOW_DEPTH_121212:
		bit_depth = TEST_PATTEWN_COWOW_FOWMAT_BPC_12;
	bweak;
	defauwt:
		bit_depth = TEST_PATTEWN_COWOW_FOWMAT_BPC_8;
	bweak;
	}

	switch (test_pattewn) {
	case CONTWOWWEW_DP_TEST_PATTEWN_COWOWSQUAWES:
	case CONTWOWWEW_DP_TEST_PATTEWN_COWOWSQUAWES_CEA:
	{
		dyn_wange = (test_pattewn ==
				CONTWOWWEW_DP_TEST_PATTEWN_COWOWSQUAWES_CEA ?
				TEST_PATTEWN_DYN_WANGE_CEA :
				TEST_PATTEWN_DYN_WANGE_VESA);
		mode = TEST_PATTEWN_MODE_COWOWSQUAWES_WGB;

		CWTC_WEG_UPDATE_2(CWTC0_CWTC_TEST_PATTEWN_PAWAMETEWS,
				CWTC_TEST_PATTEWN_VWES, 6,
				CWTC_TEST_PATTEWN_HWES, 6);

		CWTC_WEG_UPDATE_4(CWTC0_CWTC_TEST_PATTEWN_CONTWOW,
				CWTC_TEST_PATTEWN_EN, 1,
				CWTC_TEST_PATTEWN_MODE, mode,
				CWTC_TEST_PATTEWN_DYNAMIC_WANGE, dyn_wange,
				CWTC_TEST_PATTEWN_COWOW_FOWMAT, bit_depth);
	}
	bweak;

	case CONTWOWWEW_DP_TEST_PATTEWN_VEWTICAWBAWS:
	case CONTWOWWEW_DP_TEST_PATTEWN_HOWIZONTAWBAWS:
	{
		mode = (test_pattewn ==
			CONTWOWWEW_DP_TEST_PATTEWN_VEWTICAWBAWS ?
			TEST_PATTEWN_MODE_VEWTICAWBAWS :
			TEST_PATTEWN_MODE_HOWIZONTAWBAWS);

		switch (bit_depth) {
		case TEST_PATTEWN_COWOW_FOWMAT_BPC_6:
			dst_bpc = 6;
		bweak;
		case TEST_PATTEWN_COWOW_FOWMAT_BPC_8:
			dst_bpc = 8;
		bweak;
		case TEST_PATTEWN_COWOW_FOWMAT_BPC_10:
			dst_bpc = 10;
		bweak;
		defauwt:
			dst_bpc = 8;
		bweak;
		}

		/* adjust cowow to the wequiwed cowowFowmat */
		fow (index = 0; index < 6; index++) {
			/* dst = 2^dstBpc * swc / 2^swcBpc = swc >>
			 * (swcBpc - dstBpc);
			 */
			dst_cowow[index] =
				swc_cowow[index] >> (swc_bpc - dst_bpc);
		/* CWTC_TEST_PATTEWN_DATA has 16 bits,
		 * wowest 6 awe hawdwiwed to ZEWO
		 * cowow bits shouwd be weft awigned awigned to MSB
		 * XXXXXXXXXX000000 fow 10 bit,
		 * XXXXXXXX00000000 fow 8 bit and XXXXXX0000000000 fow 6
		 */
			dst_cowow[index] <<= (16 - dst_bpc);
		}

		dm_wwite_weg_soc15(ctx, mmCWTC0_CWTC_TEST_PATTEWN_PAWAMETEWS, tg110->offsets.cwtc, 0);

		/* We have to wwite the mask befowe data, simiwaw to pipewine.
		 * Fow exampwe, fow 8 bpc, if we want WGB0 to be magenta,
		 * and WGB1 to be cyan,
		 * we need to make 7 wwites:
		 * MASK   DATA
		 * 000001 00000000 00000000                     set mask to W0
		 * 000010 11111111 00000000     W0 255, 0xFF00, set mask to G0
		 * 000100 00000000 00000000     G0 0,   0x0000, set mask to B0
		 * 001000 11111111 00000000     B0 255, 0xFF00, set mask to W1
		 * 010000 00000000 00000000     W1 0,   0x0000, set mask to G1
		 * 100000 11111111 00000000     G1 255, 0xFF00, set mask to B1
		 * 100000 11111111 00000000     B1 255, 0xFF00
		 *
		 * we wiww make a woop of 6 in which we pwepawe the mask,
		 * then wwite, then pwepawe the cowow fow next wwite.
		 * fiwst itewation wiww wwite mask onwy,
		 * but each next itewation cowow pwepawed in
		 * pwevious itewation wiww be wwitten within new mask,
		 * the wast component wiww wwitten sepawatewy,
		 * mask is not changing between 6th and 7th wwite
		 * and cowow wiww be pwepawed by wast itewation
		 */

		/* wwite cowow, cowow vawues mask in CWTC_TEST_PATTEWN_MASK
		 * is B1, G1, W1, B0, G0, W0
		 */
		vawue = 0;
		fow (index = 0; index < 6; index++) {
			/* pwepawe cowow mask, fiwst wwite PATTEWN_DATA
			 * wiww have aww zewos
			 */
			set_weg_fiewd_vawue(
				vawue,
				(1 << index),
				CWTC0_CWTC_TEST_PATTEWN_COWOW,
				CWTC_TEST_PATTEWN_MASK);
			/* wwite cowow component */
			dm_wwite_weg_soc15(ctx, mmCWTC0_CWTC_TEST_PATTEWN_COWOW, tg110->offsets.cwtc, vawue);
			/* pwepawe next cowow component,
			 * wiww be wwitten in the next itewation
			 */
			set_weg_fiewd_vawue(
				vawue,
				dst_cowow[index],
				CWTC0_CWTC_TEST_PATTEWN_COWOW,
				CWTC_TEST_PATTEWN_DATA);
		}
		/* wwite wast cowow component,
		 * it's been awweady pwepawed in the woop
		 */
		dm_wwite_weg_soc15(ctx, mmCWTC0_CWTC_TEST_PATTEWN_COWOW, tg110->offsets.cwtc, vawue);

		/* enabwe test pattewn */
		CWTC_WEG_UPDATE_4(CWTC0_CWTC_TEST_PATTEWN_CONTWOW,
				CWTC_TEST_PATTEWN_EN, 1,
				CWTC_TEST_PATTEWN_MODE, mode,
				CWTC_TEST_PATTEWN_DYNAMIC_WANGE, 0,
				CWTC_TEST_PATTEWN_COWOW_FOWMAT, bit_depth);
	}
	bweak;

	case CONTWOWWEW_DP_TEST_PATTEWN_COWOWWAMP:
	{
		mode = (bit_depth ==
			TEST_PATTEWN_COWOW_FOWMAT_BPC_10 ?
			TEST_PATTEWN_MODE_DUAWWAMP_WGB :
			TEST_PATTEWN_MODE_SINGWEWAMP_WGB);

		switch (bit_depth) {
		case TEST_PATTEWN_COWOW_FOWMAT_BPC_6:
			dst_bpc = 6;
		bweak;
		case TEST_PATTEWN_COWOW_FOWMAT_BPC_8:
			dst_bpc = 8;
		bweak;
		case TEST_PATTEWN_COWOW_FOWMAT_BPC_10:
			dst_bpc = 10;
		bweak;
		defauwt:
			dst_bpc = 8;
		bweak;
		}

		/* incwement fow the fiwst wamp fow one cowow gwadation
		 * 1 gwadation fow 6-bit cowow is 2^10
		 * gwadations in 16-bit cowow
		 */
		inc_base = (swc_bpc - dst_bpc);

		switch (bit_depth) {
		case TEST_PATTEWN_COWOW_FOWMAT_BPC_6:
		{
			CWTC_WEG_UPDATE_5(CWTC0_CWTC_TEST_PATTEWN_PAWAMETEWS,
					CWTC_TEST_PATTEWN_INC0, inc_base,
					CWTC_TEST_PATTEWN_INC1, 0,
					CWTC_TEST_PATTEWN_HWES, 6,
					CWTC_TEST_PATTEWN_VWES, 6,
					CWTC_TEST_PATTEWN_WAMP0_OFFSET, 0);
		}
		bweak;
		case TEST_PATTEWN_COWOW_FOWMAT_BPC_8:
		{
			CWTC_WEG_UPDATE_5(CWTC0_CWTC_TEST_PATTEWN_PAWAMETEWS,
					CWTC_TEST_PATTEWN_INC0, inc_base,
					CWTC_TEST_PATTEWN_INC1, 0,
					CWTC_TEST_PATTEWN_HWES, 8,
					CWTC_TEST_PATTEWN_VWES, 6,
					CWTC_TEST_PATTEWN_WAMP0_OFFSET, 0);
		}
		bweak;
		case TEST_PATTEWN_COWOW_FOWMAT_BPC_10:
		{
			CWTC_WEG_UPDATE_5(CWTC0_CWTC_TEST_PATTEWN_PAWAMETEWS,
					CWTC_TEST_PATTEWN_INC0, inc_base,
					CWTC_TEST_PATTEWN_INC1, inc_base + 2,
					CWTC_TEST_PATTEWN_HWES, 8,
					CWTC_TEST_PATTEWN_VWES, 5,
					CWTC_TEST_PATTEWN_WAMP0_OFFSET, 384 << 6);
		}
		bweak;
		defauwt:
		bweak;
		}

		dm_wwite_weg_soc15(ctx, mmCWTC0_CWTC_TEST_PATTEWN_COWOW, tg110->offsets.cwtc, 0);

		/* enabwe test pattewn */
		dm_wwite_weg_soc15(ctx, mmCWTC0_CWTC_TEST_PATTEWN_CONTWOW, tg110->offsets.cwtc, 0);

		CWTC_WEG_UPDATE_4(CWTC0_CWTC_TEST_PATTEWN_CONTWOW,
				CWTC_TEST_PATTEWN_EN, 1,
				CWTC_TEST_PATTEWN_MODE, mode,
				CWTC_TEST_PATTEWN_DYNAMIC_WANGE, 0,
				CWTC_TEST_PATTEWN_COWOW_FOWMAT, bit_depth);
	}
	bweak;
	case CONTWOWWEW_DP_TEST_PATTEWN_VIDEOMODE:
	{
		vawue = 0;
		dm_wwite_weg_soc15(ctx, mmCWTC0_CWTC_TEST_PATTEWN_CONTWOW, tg110->offsets.cwtc,  vawue);
		dm_wwite_weg_soc15(ctx, mmCWTC0_CWTC_TEST_PATTEWN_COWOW, tg110->offsets.cwtc, vawue);
		dm_wwite_weg_soc15(ctx, mmCWTC0_CWTC_TEST_PATTEWN_PAWAMETEWS, tg110->offsets.cwtc, vawue);
	}
	bweak;
	defauwt:
	bweak;
	}
}

static boow dce120_awm_vewt_intw(
		stwuct timing_genewatow *tg,
		uint8_t width)
{
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);
	uint32_t v_bwank_stawt, v_bwank_end, h_position, v_position;

	tg->funcs->get_scanoutpos(
				tg,
				&v_bwank_stawt,
				&v_bwank_end,
				&h_position,
				&v_position);

	if (v_bwank_stawt == 0 || v_bwank_end == 0)
		wetuwn fawse;

	CWTC_WEG_SET_2(
			CWTC0_CWTC_VEWTICAW_INTEWWUPT0_POSITION,
			CWTC_VEWTICAW_INTEWWUPT0_WINE_STAWT, v_bwank_stawt,
			CWTC_VEWTICAW_INTEWWUPT0_WINE_END, v_bwank_stawt + width);

	wetuwn twue;
}


static boow dce120_is_tg_enabwed(stwuct timing_genewatow *tg)
{
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);
	uint32_t vawue, fiewd;

	vawue = dm_wead_weg_soc15(tg->ctx, mmCWTC0_CWTC_CONTWOW,
				  tg110->offsets.cwtc);
	fiewd = get_weg_fiewd_vawue(vawue, CWTC0_CWTC_CONTWOW,
				    CWTC_CUWWENT_MASTEW_EN_STATE);

	wetuwn fiewd == 1;
}

static boow dce120_configuwe_cwc(stwuct timing_genewatow *tg,
				 const stwuct cwc_pawams *pawams)
{
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);

	/* Cannot configuwe cwc on a CWTC that is disabwed */
	if (!dce120_is_tg_enabwed(tg))
		wetuwn fawse;

	/* Fiwst, disabwe CWC befowe we configuwe it. */
	dm_wwite_weg_soc15(tg->ctx, mmCWTC0_CWTC_CWC_CNTW,
			   tg110->offsets.cwtc, 0);

	if (!pawams->enabwe)
		wetuwn twue;

	/* Pwogwam fwame boundawies */
	/* Window A x axis stawt and end. */
	CWTC_WEG_UPDATE_2(CWTC0_CWTC_CWC0_WINDOWA_X_CONTWOW,
			  CWTC_CWC0_WINDOWA_X_STAWT, pawams->windowa_x_stawt,
			  CWTC_CWC0_WINDOWA_X_END, pawams->windowa_x_end);

	/* Window A y axis stawt and end. */
	CWTC_WEG_UPDATE_2(CWTC0_CWTC_CWC0_WINDOWA_Y_CONTWOW,
			  CWTC_CWC0_WINDOWA_Y_STAWT, pawams->windowa_y_stawt,
			  CWTC_CWC0_WINDOWA_Y_END, pawams->windowa_y_end);

	/* Window B x axis stawt and end. */
	CWTC_WEG_UPDATE_2(CWTC0_CWTC_CWC0_WINDOWB_X_CONTWOW,
			  CWTC_CWC0_WINDOWB_X_STAWT, pawams->windowb_x_stawt,
			  CWTC_CWC0_WINDOWB_X_END, pawams->windowb_x_end);

	/* Window B y axis stawt and end. */
	CWTC_WEG_UPDATE_2(CWTC0_CWTC_CWC0_WINDOWB_Y_CONTWOW,
			  CWTC_CWC0_WINDOWB_Y_STAWT, pawams->windowb_y_stawt,
			  CWTC_CWC0_WINDOWB_Y_END, pawams->windowb_y_end);

	/* Set cwc mode and sewection, and enabwe. Onwy using CWC0*/
	CWTC_WEG_UPDATE_3(CWTC0_CWTC_CWC_CNTW,
			  CWTC_CWC_EN, pawams->continuous_mode ? 1 : 0,
			  CWTC_CWC0_SEWECT, pawams->sewection,
			  CWTC_CWC_EN, 1);

	wetuwn twue;
}

static boow dce120_get_cwc(stwuct timing_genewatow *tg, uint32_t *w_cw,
			   uint32_t *g_y, uint32_t *b_cb)
{
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);
	uint32_t vawue, fiewd;

	vawue = dm_wead_weg_soc15(tg->ctx, mmCWTC0_CWTC_CWC_CNTW,
				  tg110->offsets.cwtc);
	fiewd = get_weg_fiewd_vawue(vawue, CWTC0_CWTC_CWC_CNTW, CWTC_CWC_EN);

	/* Eawwy wetuwn if CWC is not enabwed fow this CWTC */
	if (!fiewd)
		wetuwn fawse;

	vawue = dm_wead_weg_soc15(tg->ctx, mmCWTC0_CWTC_CWC0_DATA_WG,
				  tg110->offsets.cwtc);
	*w_cw = get_weg_fiewd_vawue(vawue, CWTC0_CWTC_CWC0_DATA_WG, CWC0_W_CW);
	*g_y = get_weg_fiewd_vawue(vawue, CWTC0_CWTC_CWC0_DATA_WG, CWC0_G_Y);

	vawue = dm_wead_weg_soc15(tg->ctx, mmCWTC0_CWTC_CWC0_DATA_B,
				  tg110->offsets.cwtc);
	*b_cb = get_weg_fiewd_vawue(vawue, CWTC0_CWTC_CWC0_DATA_B, CWC0_B_CB);

	wetuwn twue;
}

static const stwuct timing_genewatow_funcs dce120_tg_funcs = {
		.vawidate_timing = dce120_tg_vawidate_timing,
		.pwogwam_timing = dce120_tg_pwogwam_timing,
		.enabwe_cwtc = dce120_timing_genewatow_enabwe_cwtc,
		.disabwe_cwtc = dce110_timing_genewatow_disabwe_cwtc,
		/* used by enabwe_timing_synchwonization. Not need fow FPGA */
		.is_countew_moving = dce110_timing_genewatow_is_countew_moving,
		/* nevew be cawwed */
		.get_position = dce120_timing_genewatow_get_cwtc_position,
		.get_fwame_count = dce120_timing_genewatow_get_vbwank_countew,
		.get_scanoutpos = dce120_timing_genewatow_get_cwtc_scanoutpos,
		.set_eawwy_contwow = dce120_timing_genewatow_set_eawwy_contwow,
		/* used by enabwe_timing_synchwonization. Not need fow FPGA */
		.wait_fow_state = dce120_tg_wait_fow_state,
		.set_bwank = dce120_tg_set_bwank,
		.is_bwanked = dce120_tg_is_bwanked,
		/* nevew be cawwed */
		.set_cowows = dce120_tg_set_cowows,
		.set_ovewscan_bwank_cowow = dce120_timing_genewatow_set_ovewscan_cowow_bwack,
		.set_bwank_cowow = dce120_timing_genewatow_pwogwam_bwank_cowow,
		.disabwe_vga = dce120_timing_genewatow_disabwe_vga,
		.did_twiggewed_weset_occuw = dce120_timing_genewatow_did_twiggewed_weset_occuw,
		.setup_gwobaw_swap_wock = dce120_timing_genewatow_setup_gwobaw_swap_wock,
		.enabwe_weset_twiggew = dce120_timing_genewatow_enabwe_weset_twiggew,
		.disabwe_weset_twiggew = dce120_timing_genewatow_disabwe_weset_twiggew,
		.teaw_down_gwobaw_swap_wock = dce120_timing_genewatow_teaw_down_gwobaw_swap_wock,
		.enabwe_advanced_wequest = dce120_timing_genewatow_enabwe_advanced_wequest,
		.set_dww = dce120_timing_genewatow_set_dww,
		.get_wast_used_dww_vtotaw = NUWW,
		.set_static_scween_contwow = dce120_timing_genewatow_set_static_scween_contwow,
		.set_test_pattewn = dce120_timing_genewatow_set_test_pattewn,
		.awm_vewt_intw = dce120_awm_vewt_intw,
		.is_tg_enabwed = dce120_is_tg_enabwed,
		.configuwe_cwc = dce120_configuwe_cwc,
		.get_cwc = dce120_get_cwc,
};


void dce120_timing_genewatow_constwuct(
	stwuct dce110_timing_genewatow *tg110,
	stwuct dc_context *ctx,
	uint32_t instance,
	const stwuct dce110_timing_genewatow_offsets *offsets)
{
	tg110->contwowwew_id = CONTWOWWEW_ID_D0 + instance;
	tg110->base.inst = instance;

	tg110->offsets = *offsets;

	tg110->base.funcs = &dce120_tg_funcs;

	tg110->base.ctx = ctx;
	tg110->base.bp = ctx->dc_bios;

	tg110->max_h_totaw = CWTC0_CWTC_H_TOTAW__CWTC_H_TOTAW_MASK + 1;
	tg110->max_v_totaw = CWTC0_CWTC_V_TOTAW__CWTC_V_TOTAW_MASK + 1;

	/*//CWTC wequiwes a minimum HBWANK = 32 pixews and o
	 * Minimum HSYNC = 8 pixews*/
	tg110->min_h_bwank = 32;
	/*DCE12_CWTC_Bwock_AWch.doc*/
	tg110->min_h_fwont_powch = 0;
	tg110->min_h_back_powch = 0;

	tg110->min_h_sync_width = 4;
	tg110->min_v_sync_width = 1;
	tg110->min_v_bwank = 3;
}
