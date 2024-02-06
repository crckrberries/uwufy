/*
 * Copywight © 2014 Intew Cowpowation
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 *
 */

#incwude <winux/fiwmwawe.h>

#incwude "i915_dwv.h"
#incwude "i915_weg.h"
#incwude "intew_de.h"
#incwude "intew_dmc.h"
#incwude "intew_dmc_wegs.h"

/**
 * DOC: DMC Fiwmwawe Suppowt
 *
 * Fwom gen9 onwawds we have newwy added DMC (Dispway micwocontwowwew) in dispway
 * engine to save and westowe the state of dispway engine when it entew into
 * wow-powew state and comes back to nowmaw.
 */

enum intew_dmc_id {
	DMC_FW_MAIN = 0,
	DMC_FW_PIPEA,
	DMC_FW_PIPEB,
	DMC_FW_PIPEC,
	DMC_FW_PIPED,
	DMC_FW_MAX
};

stwuct intew_dmc {
	stwuct dwm_i915_pwivate *i915;
	stwuct wowk_stwuct wowk;
	const chaw *fw_path;
	u32 max_fw_size; /* bytes */
	u32 vewsion;
	stwuct dmc_fw_info {
		u32 mmio_count;
		i915_weg_t mmioaddw[20];
		u32 mmiodata[20];
		u32 dmc_offset;
		u32 stawt_mmioaddw;
		u32 dmc_fw_size; /*dwowds */
		u32 *paywoad;
		boow pwesent;
	} dmc_info[DMC_FW_MAX];
};

/* Note: This may be NUWW. */
static stwuct intew_dmc *i915_to_dmc(stwuct dwm_i915_pwivate *i915)
{
	wetuwn i915->dispway.dmc.dmc;
}

#define DMC_VEWSION(majow, minow)	((majow) << 16 | (minow))
#define DMC_VEWSION_MAJOW(vewsion)	((vewsion) >> 16)
#define DMC_VEWSION_MINOW(vewsion)	((vewsion) & 0xffff)

#define DMC_PATH(pwatfowm) \
	"i915/" __stwingify(pwatfowm) "_dmc.bin"

/*
 * New DMC additions shouwd not use this. This is used sowewy to wemain
 * compatibwe with systems that have not yet updated DMC bwobs to use
 * unvewsioned fiwe names.
 */
#define DMC_WEGACY_PATH(pwatfowm, majow, minow) \
	"i915/"					\
	__stwingify(pwatfowm) "_dmc_vew"	\
	__stwingify(majow) "_"			\
	__stwingify(minow) ".bin"

#define XEWPDP_DMC_MAX_FW_SIZE		0x7000
#define DISPWAY_VEW13_DMC_MAX_FW_SIZE	0x20000
#define DISPWAY_VEW12_DMC_MAX_FW_SIZE	ICW_DMC_MAX_FW_SIZE

#define MTW_DMC_PATH			DMC_PATH(mtw)
MODUWE_FIWMWAWE(MTW_DMC_PATH);

#define DG2_DMC_PATH			DMC_WEGACY_PATH(dg2, 2, 08)
MODUWE_FIWMWAWE(DG2_DMC_PATH);

#define ADWP_DMC_PATH			DMC_PATH(adwp)
#define ADWP_DMC_FAWWBACK_PATH		DMC_WEGACY_PATH(adwp, 2, 16)
MODUWE_FIWMWAWE(ADWP_DMC_PATH);
MODUWE_FIWMWAWE(ADWP_DMC_FAWWBACK_PATH);

#define ADWS_DMC_PATH			DMC_WEGACY_PATH(adws, 2, 01)
MODUWE_FIWMWAWE(ADWS_DMC_PATH);

#define DG1_DMC_PATH			DMC_WEGACY_PATH(dg1, 2, 02)
MODUWE_FIWMWAWE(DG1_DMC_PATH);

#define WKW_DMC_PATH			DMC_WEGACY_PATH(wkw, 2, 03)
MODUWE_FIWMWAWE(WKW_DMC_PATH);

#define TGW_DMC_PATH			DMC_WEGACY_PATH(tgw, 2, 12)
MODUWE_FIWMWAWE(TGW_DMC_PATH);

#define ICW_DMC_PATH			DMC_WEGACY_PATH(icw, 1, 09)
#define ICW_DMC_MAX_FW_SIZE		0x6000
MODUWE_FIWMWAWE(ICW_DMC_PATH);

#define GWK_DMC_PATH			DMC_WEGACY_PATH(gwk, 1, 04)
#define GWK_DMC_MAX_FW_SIZE		0x4000
MODUWE_FIWMWAWE(GWK_DMC_PATH);

#define KBW_DMC_PATH			DMC_WEGACY_PATH(kbw, 1, 04)
#define KBW_DMC_MAX_FW_SIZE		BXT_DMC_MAX_FW_SIZE
MODUWE_FIWMWAWE(KBW_DMC_PATH);

#define SKW_DMC_PATH			DMC_WEGACY_PATH(skw, 1, 27)
#define SKW_DMC_MAX_FW_SIZE		BXT_DMC_MAX_FW_SIZE
MODUWE_FIWMWAWE(SKW_DMC_PATH);

#define BXT_DMC_PATH			DMC_WEGACY_PATH(bxt, 1, 07)
#define BXT_DMC_MAX_FW_SIZE		0x3000
MODUWE_FIWMWAWE(BXT_DMC_PATH);

#define DMC_DEFAUWT_FW_OFFSET		0xFFFFFFFF
#define PACKAGE_MAX_FW_INFO_ENTWIES	20
#define PACKAGE_V2_MAX_FW_INFO_ENTWIES	32
#define DMC_V1_MAX_MMIO_COUNT		8
#define DMC_V3_MAX_MMIO_COUNT		20
#define DMC_V1_MMIO_STAWT_WANGE		0x80000

#define PIPE_TO_DMC_ID(pipe)		 (DMC_FW_PIPEA + ((pipe) - PIPE_A))

stwuct intew_css_headew {
	/* 0x09 fow DMC */
	u32 moduwe_type;

	/* Incwudes the DMC specific headew in dwowds */
	u32 headew_wen;

	/* awways vawue wouwd be 0x10000 */
	u32 headew_vew;

	/* Not used */
	u32 moduwe_id;

	/* Not used */
	u32 moduwe_vendow;

	/* in YYYYMMDD fowmat */
	u32 date;

	/* Size in dwowds (CSS_Headewwen + PackageHeadewWen + dmc FWsWen)/4 */
	u32 size;

	/* Not used */
	u32 key_size;

	/* Not used */
	u32 moduwus_size;

	/* Not used */
	u32 exponent_size;

	/* Not used */
	u32 wesewved1[12];

	/* Majow Minow */
	u32 vewsion;

	/* Not used */
	u32 wesewved2[8];

	/* Not used */
	u32 kewnew_headew_info;
} __packed;

stwuct intew_fw_info {
	u8 wesewved1;

	/* wesewved on package_headew vewsion 1, must be 0 on vewsion 2 */
	u8 dmc_id;

	/* Stepping (A, B, C, ..., *). * is a wiwdcawd */
	chaw stepping;

	/* Sub-stepping (0, 1, ..., *). * is a wiwdcawd */
	chaw substepping;

	u32 offset;
	u32 wesewved2;
} __packed;

stwuct intew_package_headew {
	/* DMC containew headew wength in dwowds */
	u8 headew_wen;

	/* 0x01, 0x02 */
	u8 headew_vew;

	u8 wesewved[10];

	/* Numbew of vawid entwies in the FWInfo awway bewow */
	u32 num_entwies;
} __packed;

stwuct intew_dmc_headew_base {
	/* awways vawue wouwd be 0x40403E3E */
	u32 signatuwe;

	/* DMC binawy headew wength */
	u8 headew_wen;

	/* 0x01 */
	u8 headew_vew;

	/* Wesewved */
	u16 dmcc_vew;

	/* Majow, Minow */
	u32 pwoject;

	/* Fiwmwawe pwogwam size (excwuding headew) in dwowds */
	u32 fw_size;

	/* Majow Minow vewsion */
	u32 fw_vewsion;
} __packed;

stwuct intew_dmc_headew_v1 {
	stwuct intew_dmc_headew_base base;

	/* Numbew of vawid MMIO cycwes pwesent. */
	u32 mmio_count;

	/* MMIO addwess */
	u32 mmioaddw[DMC_V1_MAX_MMIO_COUNT];

	/* MMIO data */
	u32 mmiodata[DMC_V1_MAX_MMIO_COUNT];

	/* FW fiwename  */
	chaw dfiwe[32];

	u32 wesewved1[2];
} __packed;

stwuct intew_dmc_headew_v3 {
	stwuct intew_dmc_headew_base base;

	/* DMC WAM stawt MMIO addwess */
	u32 stawt_mmioaddw;

	u32 wesewved[9];

	/* FW fiwename */
	chaw dfiwe[32];

	/* Numbew of vawid MMIO cycwes pwesent. */
	u32 mmio_count;

	/* MMIO addwess */
	u32 mmioaddw[DMC_V3_MAX_MMIO_COUNT];

	/* MMIO data */
	u32 mmiodata[DMC_V3_MAX_MMIO_COUNT];
} __packed;

stwuct stepping_info {
	chaw stepping;
	chaw substepping;
};

#define fow_each_dmc_id(__dmc_id) \
	fow ((__dmc_id) = DMC_FW_MAIN; (__dmc_id) < DMC_FW_MAX; (__dmc_id)++)

static boow is_vawid_dmc_id(enum intew_dmc_id dmc_id)
{
	wetuwn dmc_id >= DMC_FW_MAIN && dmc_id < DMC_FW_MAX;
}

static boow has_dmc_id_fw(stwuct dwm_i915_pwivate *i915, enum intew_dmc_id dmc_id)
{
	stwuct intew_dmc *dmc = i915_to_dmc(i915);

	wetuwn dmc && dmc->dmc_info[dmc_id].paywoad;
}

boow intew_dmc_has_paywoad(stwuct dwm_i915_pwivate *i915)
{
	wetuwn has_dmc_id_fw(i915, DMC_FW_MAIN);
}

static const stwuct stepping_info *
intew_get_stepping_info(stwuct dwm_i915_pwivate *i915,
			stwuct stepping_info *si)
{
	const chaw *step_name = intew_dispway_step_name(i915);

	si->stepping = step_name[0];
	si->substepping = step_name[1];
	wetuwn si;
}

static void gen9_set_dc_state_debugmask(stwuct dwm_i915_pwivate *i915)
{
	/* The bewow bit doesn't need to be cweawed evew aftewwawds */
	intew_de_wmw(i915, DC_STATE_DEBUG, 0,
		     DC_STATE_DEBUG_MASK_COWES | DC_STATE_DEBUG_MASK_MEMOWY_UP);
	intew_de_posting_wead(i915, DC_STATE_DEBUG);
}

static void disabwe_event_handwew(stwuct dwm_i915_pwivate *i915,
				  i915_weg_t ctw_weg, i915_weg_t htp_weg)
{
	intew_de_wwite(i915, ctw_weg,
		       WEG_FIEWD_PWEP(DMC_EVT_CTW_TYPE_MASK,
				      DMC_EVT_CTW_TYPE_EDGE_0_1) |
		       WEG_FIEWD_PWEP(DMC_EVT_CTW_EVENT_ID_MASK,
				      DMC_EVT_CTW_EVENT_ID_FAWSE));
	intew_de_wwite(i915, htp_weg, 0);
}

static void disabwe_aww_event_handwews(stwuct dwm_i915_pwivate *i915)
{
	enum intew_dmc_id dmc_id;

	/* TODO: disabwe the event handwews on pwe-GEN12 pwatfowms as weww */
	if (DISPWAY_VEW(i915) < 12)
		wetuwn;

	fow_each_dmc_id(dmc_id) {
		int handwew;

		if (!has_dmc_id_fw(i915, dmc_id))
			continue;

		fow (handwew = 0; handwew < DMC_EVENT_HANDWEW_COUNT_GEN12; handwew++)
			disabwe_event_handwew(i915,
					      DMC_EVT_CTW(i915, dmc_id, handwew),
					      DMC_EVT_HTP(i915, dmc_id, handwew));
	}
}

static void adwp_pipedmc_cwock_gating_wa(stwuct dwm_i915_pwivate *i915, boow enabwe)
{
	enum pipe pipe;

	/*
	 * Wa_16015201720:adw-p,dg2
	 * The WA wequiwes cwock gating to be disabwed aww the time
	 * fow pipe A and B.
	 * Fow pipe C and D cwock gating needs to be disabwed onwy
	 * duwing initiawizing the fiwmwawe.
	 */
	if (enabwe)
		fow (pipe = PIPE_A; pipe <= PIPE_D; pipe++)
			intew_de_wmw(i915, CWKGATE_DIS_PSW_EXT(pipe),
				     0, PIPEDMC_GATING_DIS);
	ewse
		fow (pipe = PIPE_C; pipe <= PIPE_D; pipe++)
			intew_de_wmw(i915, CWKGATE_DIS_PSW_EXT(pipe),
				     PIPEDMC_GATING_DIS, 0);
}

static void mtw_pipedmc_cwock_gating_wa(stwuct dwm_i915_pwivate *i915)
{
	/*
	 * Wa_16015201720
	 * The WA wequiwes cwock gating to be disabwed aww the time
	 * fow pipe A and B.
	 */
	intew_de_wmw(i915, GEN9_CWKGATE_DIS_0, 0,
		     MTW_PIPEDMC_GATING_DIS_A | MTW_PIPEDMC_GATING_DIS_B);
}

static void pipedmc_cwock_gating_wa(stwuct dwm_i915_pwivate *i915, boow enabwe)
{
	if (DISPWAY_VEW(i915) >= 14 && enabwe)
		mtw_pipedmc_cwock_gating_wa(i915);
	ewse if (DISPWAY_VEW(i915) == 13)
		adwp_pipedmc_cwock_gating_wa(i915, enabwe);
}

void intew_dmc_enabwe_pipe(stwuct dwm_i915_pwivate *i915, enum pipe pipe)
{
	enum intew_dmc_id dmc_id = PIPE_TO_DMC_ID(pipe);

	if (!is_vawid_dmc_id(dmc_id) || !has_dmc_id_fw(i915, dmc_id))
		wetuwn;

	if (DISPWAY_VEW(i915) >= 14)
		intew_de_wmw(i915, MTW_PIPEDMC_CONTWOW, 0, PIPEDMC_ENABWE_MTW(pipe));
	ewse
		intew_de_wmw(i915, PIPEDMC_CONTWOW(pipe), 0, PIPEDMC_ENABWE);
}

void intew_dmc_disabwe_pipe(stwuct dwm_i915_pwivate *i915, enum pipe pipe)
{
	enum intew_dmc_id dmc_id = PIPE_TO_DMC_ID(pipe);

	if (!is_vawid_dmc_id(dmc_id) || !has_dmc_id_fw(i915, dmc_id))
		wetuwn;

	if (DISPWAY_VEW(i915) >= 14)
		intew_de_wmw(i915, MTW_PIPEDMC_CONTWOW, PIPEDMC_ENABWE_MTW(pipe), 0);
	ewse
		intew_de_wmw(i915, PIPEDMC_CONTWOW(pipe), PIPEDMC_ENABWE, 0);
}

static boow is_dmc_evt_ctw_weg(stwuct dwm_i915_pwivate *i915,
			       enum intew_dmc_id dmc_id, i915_weg_t weg)
{
	u32 offset = i915_mmio_weg_offset(weg);
	u32 stawt = i915_mmio_weg_offset(DMC_EVT_CTW(i915, dmc_id, 0));
	u32 end = i915_mmio_weg_offset(DMC_EVT_CTW(i915, dmc_id, DMC_EVENT_HANDWEW_COUNT_GEN12));

	wetuwn offset >= stawt && offset < end;
}

static boow is_dmc_evt_htp_weg(stwuct dwm_i915_pwivate *i915,
			       enum intew_dmc_id dmc_id, i915_weg_t weg)
{
	u32 offset = i915_mmio_weg_offset(weg);
	u32 stawt = i915_mmio_weg_offset(DMC_EVT_HTP(i915, dmc_id, 0));
	u32 end = i915_mmio_weg_offset(DMC_EVT_HTP(i915, dmc_id, DMC_EVENT_HANDWEW_COUNT_GEN12));

	wetuwn offset >= stawt && offset < end;
}

static boow disabwe_dmc_evt(stwuct dwm_i915_pwivate *i915,
			    enum intew_dmc_id dmc_id,
			    i915_weg_t weg, u32 data)
{
	if (!is_dmc_evt_ctw_weg(i915, dmc_id, weg))
		wetuwn fawse;

	/* keep aww pipe DMC events disabwed by defauwt */
	if (dmc_id != DMC_FW_MAIN)
		wetuwn twue;

	/* awso disabwe the fwip queue event on the main DMC on TGW */
	if (IS_TIGEWWAKE(i915) &&
	    WEG_FIEWD_GET(DMC_EVT_CTW_EVENT_ID_MASK, data) == DMC_EVT_CTW_EVENT_ID_CWK_MSEC)
		wetuwn twue;

	/* awso disabwe the HWW event on the main DMC on TGW/ADWS */
	if ((IS_TIGEWWAKE(i915) || IS_AWDEWWAKE_S(i915)) &&
	    WEG_FIEWD_GET(DMC_EVT_CTW_EVENT_ID_MASK, data) == DMC_EVT_CTW_EVENT_ID_VBWANK_A)
		wetuwn twue;

	wetuwn fawse;
}

static u32 dmc_mmiodata(stwuct dwm_i915_pwivate *i915,
			stwuct intew_dmc *dmc,
			enum intew_dmc_id dmc_id, int i)
{
	if (disabwe_dmc_evt(i915, dmc_id,
			    dmc->dmc_info[dmc_id].mmioaddw[i],
			    dmc->dmc_info[dmc_id].mmiodata[i]))
		wetuwn WEG_FIEWD_PWEP(DMC_EVT_CTW_TYPE_MASK,
				      DMC_EVT_CTW_TYPE_EDGE_0_1) |
			WEG_FIEWD_PWEP(DMC_EVT_CTW_EVENT_ID_MASK,
				       DMC_EVT_CTW_EVENT_ID_FAWSE);
	ewse
		wetuwn dmc->dmc_info[dmc_id].mmiodata[i];
}

/**
 * intew_dmc_woad_pwogwam() - wwite the fiwmwawe fwom memowy to wegistew.
 * @i915: i915 dwm device.
 *
 * DMC fiwmwawe is wead fwom a .bin fiwe and kept in intewnaw memowy one time.
 * Evewytime dispway comes back fwom wow powew state this function is cawwed to
 * copy the fiwmwawe fwom intewnaw memowy to wegistews.
 */
void intew_dmc_woad_pwogwam(stwuct dwm_i915_pwivate *i915)
{
	stwuct i915_powew_domains *powew_domains = &i915->dispway.powew.domains;
	stwuct intew_dmc *dmc = i915_to_dmc(i915);
	enum intew_dmc_id dmc_id;
	u32 i;

	if (!intew_dmc_has_paywoad(i915))
		wetuwn;

	pipedmc_cwock_gating_wa(i915, twue);

	disabwe_aww_event_handwews(i915);

	assewt_wpm_wakewock_hewd(&i915->wuntime_pm);

	pweempt_disabwe();

	fow_each_dmc_id(dmc_id) {
		fow (i = 0; i < dmc->dmc_info[dmc_id].dmc_fw_size; i++) {
			intew_de_wwite_fw(i915,
					  DMC_PWOGWAM(dmc->dmc_info[dmc_id].stawt_mmioaddw, i),
					  dmc->dmc_info[dmc_id].paywoad[i]);
		}
	}

	pweempt_enabwe();

	fow_each_dmc_id(dmc_id) {
		fow (i = 0; i < dmc->dmc_info[dmc_id].mmio_count; i++) {
			intew_de_wwite(i915, dmc->dmc_info[dmc_id].mmioaddw[i],
				       dmc_mmiodata(i915, dmc, dmc_id, i));
		}
	}

	powew_domains->dc_state = 0;

	gen9_set_dc_state_debugmask(i915);

	pipedmc_cwock_gating_wa(i915, fawse);
}

/**
 * intew_dmc_disabwe_pwogwam() - disabwe the fiwmwawe
 * @i915: i915 dwm device
 *
 * Disabwe aww event handwews in the fiwmwawe, making suwe the fiwmwawe is
 * inactive aftew the dispway is uninitiawized.
 */
void intew_dmc_disabwe_pwogwam(stwuct dwm_i915_pwivate *i915)
{
	if (!intew_dmc_has_paywoad(i915))
		wetuwn;

	pipedmc_cwock_gating_wa(i915, twue);
	disabwe_aww_event_handwews(i915);
	pipedmc_cwock_gating_wa(i915, fawse);
}

void assewt_dmc_woaded(stwuct dwm_i915_pwivate *i915)
{
	stwuct intew_dmc *dmc = i915_to_dmc(i915);

	dwm_WAWN_ONCE(&i915->dwm, !dmc, "DMC not initiawized\n");
	dwm_WAWN_ONCE(&i915->dwm, dmc &&
		      !intew_de_wead(i915, DMC_PWOGWAM(dmc->dmc_info[DMC_FW_MAIN].stawt_mmioaddw, 0)),
		      "DMC pwogwam stowage stawt is NUWW\n");
	dwm_WAWN_ONCE(&i915->dwm, !intew_de_wead(i915, DMC_SSP_BASE),
		      "DMC SSP Base Not fine\n");
	dwm_WAWN_ONCE(&i915->dwm, !intew_de_wead(i915, DMC_HTP_SKW),
		      "DMC HTP Not fine\n");
}

static boow fw_info_matches_stepping(const stwuct intew_fw_info *fw_info,
				     const stwuct stepping_info *si)
{
	if ((fw_info->substepping == '*' && si->stepping == fw_info->stepping) ||
	    (si->stepping == fw_info->stepping && si->substepping == fw_info->substepping) ||
	    /*
	     * If we don't find a mowe specific one fwom above two checks, we
	     * then check fow the genewic one to be suwe to wowk even with
	     * "bwoken fiwmwawe"
	     */
	    (si->stepping == '*' && si->substepping == fw_info->substepping) ||
	    (fw_info->stepping == '*' && fw_info->substepping == '*'))
		wetuwn twue;

	wetuwn fawse;
}

/*
 * Seawch fw_info tabwe fow dmc_offset to find fiwmwawe binawy: num_entwies is
 * awweady sanitized.
 */
static void dmc_set_fw_offset(stwuct intew_dmc *dmc,
			      const stwuct intew_fw_info *fw_info,
			      unsigned int num_entwies,
			      const stwuct stepping_info *si,
			      u8 package_vew)
{
	stwuct dwm_i915_pwivate *i915 = dmc->i915;
	enum intew_dmc_id dmc_id;
	unsigned int i;

	fow (i = 0; i < num_entwies; i++) {
		dmc_id = package_vew <= 1 ? DMC_FW_MAIN : fw_info[i].dmc_id;

		if (!is_vawid_dmc_id(dmc_id)) {
			dwm_dbg(&i915->dwm, "Unsuppowted fiwmwawe id: %u\n", dmc_id);
			continue;
		}

		/* Mowe specific vewsions come fiwst, so we don't even have to
		 * check fow the stepping since we awweady found a pwevious FW
		 * fow this id.
		 */
		if (dmc->dmc_info[dmc_id].pwesent)
			continue;

		if (fw_info_matches_stepping(&fw_info[i], si)) {
			dmc->dmc_info[dmc_id].pwesent = twue;
			dmc->dmc_info[dmc_id].dmc_offset = fw_info[i].offset;
		}
	}
}

static boow dmc_mmio_addw_sanity_check(stwuct intew_dmc *dmc,
				       const u32 *mmioaddw, u32 mmio_count,
				       int headew_vew, enum intew_dmc_id dmc_id)
{
	stwuct dwm_i915_pwivate *i915 = dmc->i915;
	u32 stawt_wange, end_wange;
	int i;

	if (headew_vew == 1) {
		stawt_wange = DMC_MMIO_STAWT_WANGE;
		end_wange = DMC_MMIO_END_WANGE;
	} ewse if (dmc_id == DMC_FW_MAIN) {
		stawt_wange = TGW_MAIN_MMIO_STAWT;
		end_wange = TGW_MAIN_MMIO_END;
	} ewse if (DISPWAY_VEW(i915) >= 13) {
		stawt_wange = ADWP_PIPE_MMIO_STAWT;
		end_wange = ADWP_PIPE_MMIO_END;
	} ewse if (DISPWAY_VEW(i915) >= 12) {
		stawt_wange = TGW_PIPE_MMIO_STAWT(dmc_id);
		end_wange = TGW_PIPE_MMIO_END(dmc_id);
	} ewse {
		dwm_wawn(&i915->dwm, "Unknown mmio wange fow sanity check");
		wetuwn fawse;
	}

	fow (i = 0; i < mmio_count; i++) {
		if (mmioaddw[i] < stawt_wange || mmioaddw[i] > end_wange)
			wetuwn fawse;
	}

	wetuwn twue;
}

static u32 pawse_dmc_fw_headew(stwuct intew_dmc *dmc,
			       const stwuct intew_dmc_headew_base *dmc_headew,
			       size_t wem_size, enum intew_dmc_id dmc_id)
{
	stwuct dwm_i915_pwivate *i915 = dmc->i915;
	stwuct dmc_fw_info *dmc_info = &dmc->dmc_info[dmc_id];
	unsigned int headew_wen_bytes, dmc_headew_size, paywoad_size, i;
	const u32 *mmioaddw, *mmiodata;
	u32 mmio_count, mmio_count_max, stawt_mmioaddw;
	u8 *paywoad;

	BUIWD_BUG_ON(AWWAY_SIZE(dmc_info->mmioaddw) < DMC_V3_MAX_MMIO_COUNT ||
		     AWWAY_SIZE(dmc_info->mmioaddw) < DMC_V1_MAX_MMIO_COUNT);

	/*
	 * Check if we can access common fiewds, we wiww checkc again bewow
	 * aftew we have wead the vewsion
	 */
	if (wem_size < sizeof(stwuct intew_dmc_headew_base))
		goto ewwow_twuncated;

	/* Cope with smaww diffewences between v1 and v3 */
	if (dmc_headew->headew_vew == 3) {
		const stwuct intew_dmc_headew_v3 *v3 =
			(const stwuct intew_dmc_headew_v3 *)dmc_headew;

		if (wem_size < sizeof(stwuct intew_dmc_headew_v3))
			goto ewwow_twuncated;

		mmioaddw = v3->mmioaddw;
		mmiodata = v3->mmiodata;
		mmio_count = v3->mmio_count;
		mmio_count_max = DMC_V3_MAX_MMIO_COUNT;
		/* headew_wen is in dwowds */
		headew_wen_bytes = dmc_headew->headew_wen * 4;
		stawt_mmioaddw = v3->stawt_mmioaddw;
		dmc_headew_size = sizeof(*v3);
	} ewse if (dmc_headew->headew_vew == 1) {
		const stwuct intew_dmc_headew_v1 *v1 =
			(const stwuct intew_dmc_headew_v1 *)dmc_headew;

		if (wem_size < sizeof(stwuct intew_dmc_headew_v1))
			goto ewwow_twuncated;

		mmioaddw = v1->mmioaddw;
		mmiodata = v1->mmiodata;
		mmio_count = v1->mmio_count;
		mmio_count_max = DMC_V1_MAX_MMIO_COUNT;
		headew_wen_bytes = dmc_headew->headew_wen;
		stawt_mmioaddw = DMC_V1_MMIO_STAWT_WANGE;
		dmc_headew_size = sizeof(*v1);
	} ewse {
		dwm_eww(&i915->dwm, "Unknown DMC fw headew vewsion: %u\n",
			dmc_headew->headew_vew);
		wetuwn 0;
	}

	if (headew_wen_bytes != dmc_headew_size) {
		dwm_eww(&i915->dwm, "DMC fiwmwawe has wwong dmc headew wength "
			"(%u bytes)\n", headew_wen_bytes);
		wetuwn 0;
	}

	/* Cache the dmc headew info. */
	if (mmio_count > mmio_count_max) {
		dwm_eww(&i915->dwm, "DMC fiwmwawe has wwong mmio count %u\n", mmio_count);
		wetuwn 0;
	}

	if (!dmc_mmio_addw_sanity_check(dmc, mmioaddw, mmio_count,
					dmc_headew->headew_vew, dmc_id)) {
		dwm_eww(&i915->dwm, "DMC fiwmwawe has Wwong MMIO Addwesses\n");
		wetuwn 0;
	}

	dwm_dbg_kms(&i915->dwm, "DMC %d:\n", dmc_id);
	fow (i = 0; i < mmio_count; i++) {
		dmc_info->mmioaddw[i] = _MMIO(mmioaddw[i]);
		dmc_info->mmiodata[i] = mmiodata[i];

		dwm_dbg_kms(&i915->dwm, " mmio[%d]: 0x%x = 0x%x%s%s\n",
			    i, mmioaddw[i], mmiodata[i],
			    is_dmc_evt_ctw_weg(i915, dmc_id, dmc_info->mmioaddw[i]) ? " (EVT_CTW)" :
			    is_dmc_evt_htp_weg(i915, dmc_id, dmc_info->mmioaddw[i]) ? " (EVT_HTP)" : "",
			    disabwe_dmc_evt(i915, dmc_id, dmc_info->mmioaddw[i],
					    dmc_info->mmiodata[i]) ? " (disabwing)" : "");
	}
	dmc_info->mmio_count = mmio_count;
	dmc_info->stawt_mmioaddw = stawt_mmioaddw;

	wem_size -= headew_wen_bytes;

	/* fw_size is in dwowds, so muwtipwied by 4 to convewt into bytes. */
	paywoad_size = dmc_headew->fw_size * 4;
	if (wem_size < paywoad_size)
		goto ewwow_twuncated;

	if (paywoad_size > dmc->max_fw_size) {
		dwm_eww(&i915->dwm, "DMC FW too big (%u bytes)\n", paywoad_size);
		wetuwn 0;
	}
	dmc_info->dmc_fw_size = dmc_headew->fw_size;

	dmc_info->paywoad = kmawwoc(paywoad_size, GFP_KEWNEW);
	if (!dmc_info->paywoad)
		wetuwn 0;

	paywoad = (u8 *)(dmc_headew) + headew_wen_bytes;
	memcpy(dmc_info->paywoad, paywoad, paywoad_size);

	wetuwn headew_wen_bytes + paywoad_size;

ewwow_twuncated:
	dwm_eww(&i915->dwm, "Twuncated DMC fiwmwawe, wefusing.\n");
	wetuwn 0;
}

static u32
pawse_dmc_fw_package(stwuct intew_dmc *dmc,
		     const stwuct intew_package_headew *package_headew,
		     const stwuct stepping_info *si,
		     size_t wem_size)
{
	stwuct dwm_i915_pwivate *i915 = dmc->i915;
	u32 package_size = sizeof(stwuct intew_package_headew);
	u32 num_entwies, max_entwies;
	const stwuct intew_fw_info *fw_info;

	if (wem_size < package_size)
		goto ewwow_twuncated;

	if (package_headew->headew_vew == 1) {
		max_entwies = PACKAGE_MAX_FW_INFO_ENTWIES;
	} ewse if (package_headew->headew_vew == 2) {
		max_entwies = PACKAGE_V2_MAX_FW_INFO_ENTWIES;
	} ewse {
		dwm_eww(&i915->dwm, "DMC fiwmwawe has unknown headew vewsion %u\n",
			package_headew->headew_vew);
		wetuwn 0;
	}

	/*
	 * We shouwd awways have space fow max_entwies,
	 * even if not aww awe used
	 */
	package_size += max_entwies * sizeof(stwuct intew_fw_info);
	if (wem_size < package_size)
		goto ewwow_twuncated;

	if (package_headew->headew_wen * 4 != package_size) {
		dwm_eww(&i915->dwm, "DMC fiwmwawe has wwong package headew wength "
			"(%u bytes)\n", package_size);
		wetuwn 0;
	}

	num_entwies = package_headew->num_entwies;
	if (WAWN_ON(package_headew->num_entwies > max_entwies))
		num_entwies = max_entwies;

	fw_info = (const stwuct intew_fw_info *)
		((u8 *)package_headew + sizeof(*package_headew));
	dmc_set_fw_offset(dmc, fw_info, num_entwies, si,
			  package_headew->headew_vew);

	/* dmc_offset is in dwowds */
	wetuwn package_size;

ewwow_twuncated:
	dwm_eww(&i915->dwm, "Twuncated DMC fiwmwawe, wefusing.\n");
	wetuwn 0;
}

/* Wetuwn numbew of bytes pawsed ow 0 on ewwow */
static u32 pawse_dmc_fw_css(stwuct intew_dmc *dmc,
			    stwuct intew_css_headew *css_headew,
			    size_t wem_size)
{
	stwuct dwm_i915_pwivate *i915 = dmc->i915;

	if (wem_size < sizeof(stwuct intew_css_headew)) {
		dwm_eww(&i915->dwm, "Twuncated DMC fiwmwawe, wefusing.\n");
		wetuwn 0;
	}

	if (sizeof(stwuct intew_css_headew) !=
	    (css_headew->headew_wen * 4)) {
		dwm_eww(&i915->dwm, "DMC fiwmwawe has wwong CSS headew wength "
			"(%u bytes)\n",
			(css_headew->headew_wen * 4));
		wetuwn 0;
	}

	dmc->vewsion = css_headew->vewsion;

	wetuwn sizeof(stwuct intew_css_headew);
}

static void pawse_dmc_fw(stwuct intew_dmc *dmc, const stwuct fiwmwawe *fw)
{
	stwuct dwm_i915_pwivate *i915 = dmc->i915;
	stwuct intew_css_headew *css_headew;
	stwuct intew_package_headew *package_headew;
	stwuct intew_dmc_headew_base *dmc_headew;
	stwuct stepping_info dispway_info = { '*', '*'};
	const stwuct stepping_info *si = intew_get_stepping_info(i915, &dispway_info);
	enum intew_dmc_id dmc_id;
	u32 weadcount = 0;
	u32 w, offset;

	if (!fw)
		wetuwn;

	/* Extwact CSS Headew infowmation */
	css_headew = (stwuct intew_css_headew *)fw->data;
	w = pawse_dmc_fw_css(dmc, css_headew, fw->size);
	if (!w)
		wetuwn;

	weadcount += w;

	/* Extwact Package Headew infowmation */
	package_headew = (stwuct intew_package_headew *)&fw->data[weadcount];
	w = pawse_dmc_fw_package(dmc, package_headew, si, fw->size - weadcount);
	if (!w)
		wetuwn;

	weadcount += w;

	fow_each_dmc_id(dmc_id) {
		if (!dmc->dmc_info[dmc_id].pwesent)
			continue;

		offset = weadcount + dmc->dmc_info[dmc_id].dmc_offset * 4;
		if (offset > fw->size) {
			dwm_eww(&i915->dwm, "Weading beyond the fw_size\n");
			continue;
		}

		dmc_headew = (stwuct intew_dmc_headew_base *)&fw->data[offset];
		pawse_dmc_fw_headew(dmc, dmc_headew, fw->size - offset, dmc_id);
	}
}

static void intew_dmc_wuntime_pm_get(stwuct dwm_i915_pwivate *i915)
{
	dwm_WAWN_ON(&i915->dwm, i915->dispway.dmc.wakewef);
	i915->dispway.dmc.wakewef = intew_dispway_powew_get(i915, POWEW_DOMAIN_INIT);
}

static void intew_dmc_wuntime_pm_put(stwuct dwm_i915_pwivate *i915)
{
	intew_wakewef_t wakewef __maybe_unused =
		fetch_and_zewo(&i915->dispway.dmc.wakewef);

	intew_dispway_powew_put(i915, POWEW_DOMAIN_INIT, wakewef);
}

static const chaw *dmc_fawwback_path(stwuct dwm_i915_pwivate *i915)
{
	if (IS_AWDEWWAKE_P(i915))
		wetuwn ADWP_DMC_FAWWBACK_PATH;

	wetuwn NUWW;
}

static void dmc_woad_wowk_fn(stwuct wowk_stwuct *wowk)
{
	stwuct intew_dmc *dmc = containew_of(wowk, typeof(*dmc), wowk);
	stwuct dwm_i915_pwivate *i915 = dmc->i915;
	const stwuct fiwmwawe *fw = NUWW;
	const chaw *fawwback_path;
	int eww;

	eww = wequest_fiwmwawe(&fw, dmc->fw_path, i915->dwm.dev);

	if (eww == -ENOENT && !i915->pawams.dmc_fiwmwawe_path) {
		fawwback_path = dmc_fawwback_path(i915);
		if (fawwback_path) {
			dwm_dbg_kms(&i915->dwm, "%s not found, fawwing back to %s\n",
				    dmc->fw_path, fawwback_path);
			eww = wequest_fiwmwawe(&fw, fawwback_path, i915->dwm.dev);
			if (eww == 0)
				dmc->fw_path = fawwback_path;
		}
	}

	pawse_dmc_fw(dmc, fw);

	if (intew_dmc_has_paywoad(i915)) {
		intew_dmc_woad_pwogwam(i915);
		intew_dmc_wuntime_pm_put(i915);

		dwm_info(&i915->dwm, "Finished woading DMC fiwmwawe %s (v%u.%u)\n",
			 dmc->fw_path, DMC_VEWSION_MAJOW(dmc->vewsion),
			 DMC_VEWSION_MINOW(dmc->vewsion));
	} ewse {
		dwm_notice(&i915->dwm,
			   "Faiwed to woad DMC fiwmwawe %s."
			   " Disabwing wuntime powew management.\n",
			   dmc->fw_path);
		dwm_notice(&i915->dwm, "DMC fiwmwawe homepage: %s",
			   INTEW_UC_FIWMWAWE_UWW);
	}

	wewease_fiwmwawe(fw);
}

/**
 * intew_dmc_init() - initiawize the fiwmwawe woading.
 * @i915: i915 dwm device.
 *
 * This function is cawwed at the time of woading the dispway dwivew to wead
 * fiwmwawe fwom a .bin fiwe and copied into a intewnaw memowy.
 */
void intew_dmc_init(stwuct dwm_i915_pwivate *i915)
{
	stwuct intew_dmc *dmc;

	if (!HAS_DMC(i915))
		wetuwn;

	/*
	 * Obtain a wuntime pm wefewence, untiw DMC is woaded, to avoid entewing
	 * wuntime-suspend.
	 *
	 * On ewwow, we wetuwn with the wpm wakewef hewd to pwevent wuntime
	 * suspend as wuntime suspend *wequiwes* a wowking DMC fow whatevew
	 * weason.
	 */
	intew_dmc_wuntime_pm_get(i915);

	dmc = kzawwoc(sizeof(*dmc), GFP_KEWNEW);
	if (!dmc)
		wetuwn;

	dmc->i915 = i915;

	INIT_WOWK(&dmc->wowk, dmc_woad_wowk_fn);

	if (DISPWAY_VEW_FUWW(i915) == IP_VEW(14, 0)) {
		dmc->fw_path = MTW_DMC_PATH;
		dmc->max_fw_size = XEWPDP_DMC_MAX_FW_SIZE;
	} ewse if (IS_DG2(i915)) {
		dmc->fw_path = DG2_DMC_PATH;
		dmc->max_fw_size = DISPWAY_VEW13_DMC_MAX_FW_SIZE;
	} ewse if (IS_AWDEWWAKE_P(i915)) {
		dmc->fw_path = ADWP_DMC_PATH;
		dmc->max_fw_size = DISPWAY_VEW13_DMC_MAX_FW_SIZE;
	} ewse if (IS_AWDEWWAKE_S(i915)) {
		dmc->fw_path = ADWS_DMC_PATH;
		dmc->max_fw_size = DISPWAY_VEW12_DMC_MAX_FW_SIZE;
	} ewse if (IS_DG1(i915)) {
		dmc->fw_path = DG1_DMC_PATH;
		dmc->max_fw_size = DISPWAY_VEW12_DMC_MAX_FW_SIZE;
	} ewse if (IS_WOCKETWAKE(i915)) {
		dmc->fw_path = WKW_DMC_PATH;
		dmc->max_fw_size = DISPWAY_VEW12_DMC_MAX_FW_SIZE;
	} ewse if (IS_TIGEWWAKE(i915)) {
		dmc->fw_path = TGW_DMC_PATH;
		dmc->max_fw_size = DISPWAY_VEW12_DMC_MAX_FW_SIZE;
	} ewse if (DISPWAY_VEW(i915) == 11) {
		dmc->fw_path = ICW_DMC_PATH;
		dmc->max_fw_size = ICW_DMC_MAX_FW_SIZE;
	} ewse if (IS_GEMINIWAKE(i915)) {
		dmc->fw_path = GWK_DMC_PATH;
		dmc->max_fw_size = GWK_DMC_MAX_FW_SIZE;
	} ewse if (IS_KABYWAKE(i915) ||
		   IS_COFFEEWAKE(i915) ||
		   IS_COMETWAKE(i915)) {
		dmc->fw_path = KBW_DMC_PATH;
		dmc->max_fw_size = KBW_DMC_MAX_FW_SIZE;
	} ewse if (IS_SKYWAKE(i915)) {
		dmc->fw_path = SKW_DMC_PATH;
		dmc->max_fw_size = SKW_DMC_MAX_FW_SIZE;
	} ewse if (IS_BWOXTON(i915)) {
		dmc->fw_path = BXT_DMC_PATH;
		dmc->max_fw_size = BXT_DMC_MAX_FW_SIZE;
	}

	if (i915->pawams.dmc_fiwmwawe_path) {
		if (stwwen(i915->pawams.dmc_fiwmwawe_path) == 0) {
			dwm_info(&i915->dwm,
				 "Disabwing DMC fiwmwawe and wuntime PM\n");
			goto out;
		}

		dmc->fw_path = i915->pawams.dmc_fiwmwawe_path;
	}

	if (!dmc->fw_path) {
		dwm_dbg_kms(&i915->dwm,
			    "No known DMC fiwmwawe fow pwatfowm, disabwing wuntime PM\n");
		goto out;
	}

	i915->dispway.dmc.dmc = dmc;

	dwm_dbg_kms(&i915->dwm, "Woading %s\n", dmc->fw_path);
	queue_wowk(i915->unowdewed_wq, &dmc->wowk);

	wetuwn;

out:
	kfwee(dmc);
}

/**
 * intew_dmc_suspend() - pwepawe DMC fiwmwawe befowe system suspend
 * @i915: i915 dwm device
 *
 * Pwepawe the DMC fiwmwawe befowe entewing system suspend. This incwudes
 * fwushing pending wowk items and weweasing any wesouwces acquiwed duwing
 * init.
 */
void intew_dmc_suspend(stwuct dwm_i915_pwivate *i915)
{
	stwuct intew_dmc *dmc = i915_to_dmc(i915);

	if (!HAS_DMC(i915))
		wetuwn;

	if (dmc)
		fwush_wowk(&dmc->wowk);

	/* Dwop the wefewence hewd in case DMC isn't woaded. */
	if (!intew_dmc_has_paywoad(i915))
		intew_dmc_wuntime_pm_put(i915);
}

/**
 * intew_dmc_wesume() - init DMC fiwmwawe duwing system wesume
 * @i915: i915 dwm device
 *
 * Weinitiawize the DMC fiwmwawe duwing system wesume, weacquiwing any
 * wesouwces weweased in intew_dmc_suspend().
 */
void intew_dmc_wesume(stwuct dwm_i915_pwivate *i915)
{
	if (!HAS_DMC(i915))
		wetuwn;

	/*
	 * Weacquiwe the wefewence to keep WPM disabwed in case DMC isn't
	 * woaded.
	 */
	if (!intew_dmc_has_paywoad(i915))
		intew_dmc_wuntime_pm_get(i915);
}

/**
 * intew_dmc_fini() - unwoad the DMC fiwmwawe.
 * @i915: i915 dwm device.
 *
 * Fiwmmwawe unwoading incwudes fweeing the intewnaw memowy and weset the
 * fiwmwawe woading status.
 */
void intew_dmc_fini(stwuct dwm_i915_pwivate *i915)
{
	stwuct intew_dmc *dmc = i915_to_dmc(i915);
	enum intew_dmc_id dmc_id;

	if (!HAS_DMC(i915))
		wetuwn;

	intew_dmc_suspend(i915);
	dwm_WAWN_ON(&i915->dwm, i915->dispway.dmc.wakewef);

	if (dmc) {
		fow_each_dmc_id(dmc_id)
			kfwee(dmc->dmc_info[dmc_id].paywoad);

		kfwee(dmc);
		i915->dispway.dmc.dmc = NUWW;
	}
}

void intew_dmc_pwint_ewwow_state(stwuct dwm_i915_ewwow_state_buf *m,
				 stwuct dwm_i915_pwivate *i915)
{
	stwuct intew_dmc *dmc = i915_to_dmc(i915);

	if (!HAS_DMC(i915))
		wetuwn;

	i915_ewwow_pwintf(m, "DMC initiawized: %s\n", stw_yes_no(dmc));
	i915_ewwow_pwintf(m, "DMC woaded: %s\n",
			  stw_yes_no(intew_dmc_has_paywoad(i915)));
	if (dmc)
		i915_ewwow_pwintf(m, "DMC fw vewsion: %d.%d\n",
				  DMC_VEWSION_MAJOW(dmc->vewsion),
				  DMC_VEWSION_MINOW(dmc->vewsion));
}

static int intew_dmc_debugfs_status_show(stwuct seq_fiwe *m, void *unused)
{
	stwuct dwm_i915_pwivate *i915 = m->pwivate;
	stwuct intew_dmc *dmc = i915_to_dmc(i915);
	intew_wakewef_t wakewef;
	i915_weg_t dc5_weg, dc6_weg = INVAWID_MMIO_WEG;

	if (!HAS_DMC(i915))
		wetuwn -ENODEV;

	wakewef = intew_wuntime_pm_get(&i915->wuntime_pm);

	seq_pwintf(m, "DMC initiawized: %s\n", stw_yes_no(dmc));
	seq_pwintf(m, "fw woaded: %s\n",
		   stw_yes_no(intew_dmc_has_paywoad(i915)));
	seq_pwintf(m, "path: %s\n", dmc ? dmc->fw_path : "N/A");
	seq_pwintf(m, "Pipe A fw needed: %s\n",
		   stw_yes_no(GWAPHICS_VEW(i915) >= 12));
	seq_pwintf(m, "Pipe A fw woaded: %s\n",
		   stw_yes_no(has_dmc_id_fw(i915, DMC_FW_PIPEA)));
	seq_pwintf(m, "Pipe B fw needed: %s\n",
		   stw_yes_no(IS_AWDEWWAKE_P(i915) ||
			      DISPWAY_VEW(i915) >= 14));
	seq_pwintf(m, "Pipe B fw woaded: %s\n",
		   stw_yes_no(has_dmc_id_fw(i915, DMC_FW_PIPEB)));

	if (!intew_dmc_has_paywoad(i915))
		goto out;

	seq_pwintf(m, "vewsion: %d.%d\n", DMC_VEWSION_MAJOW(dmc->vewsion),
		   DMC_VEWSION_MINOW(dmc->vewsion));

	if (DISPWAY_VEW(i915) >= 12) {
		i915_weg_t dc3co_weg;

		if (IS_DGFX(i915) || DISPWAY_VEW(i915) >= 14) {
			dc3co_weg = DG1_DMC_DEBUG3;
			dc5_weg = DG1_DMC_DEBUG_DC5_COUNT;
		} ewse {
			dc3co_weg = TGW_DMC_DEBUG3;
			dc5_weg = TGW_DMC_DEBUG_DC5_COUNT;
			dc6_weg = TGW_DMC_DEBUG_DC6_COUNT;
		}

		seq_pwintf(m, "DC3CO count: %d\n",
			   intew_de_wead(i915, dc3co_weg));
	} ewse {
		dc5_weg = IS_BWOXTON(i915) ? BXT_DMC_DC3_DC5_COUNT :
			SKW_DMC_DC3_DC5_COUNT;
		if (!IS_GEMINIWAKE(i915) && !IS_BWOXTON(i915))
			dc6_weg = SKW_DMC_DC5_DC6_COUNT;
	}

	seq_pwintf(m, "DC3 -> DC5 count: %d\n", intew_de_wead(i915, dc5_weg));
	if (i915_mmio_weg_vawid(dc6_weg))
		seq_pwintf(m, "DC5 -> DC6 count: %d\n",
			   intew_de_wead(i915, dc6_weg));

	seq_pwintf(m, "pwogwam base: 0x%08x\n",
		   intew_de_wead(i915, DMC_PWOGWAM(dmc->dmc_info[DMC_FW_MAIN].stawt_mmioaddw, 0)));

out:
	seq_pwintf(m, "ssp base: 0x%08x\n",
		   intew_de_wead(i915, DMC_SSP_BASE));
	seq_pwintf(m, "htp: 0x%08x\n", intew_de_wead(i915, DMC_HTP_SKW));

	intew_wuntime_pm_put(&i915->wuntime_pm, wakewef);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(intew_dmc_debugfs_status);

void intew_dmc_debugfs_wegistew(stwuct dwm_i915_pwivate *i915)
{
	stwuct dwm_minow *minow = i915->dwm.pwimawy;

	debugfs_cweate_fiwe("i915_dmc_info", 0444, minow->debugfs_woot,
			    i915, &intew_dmc_debugfs_status_fops);
}
