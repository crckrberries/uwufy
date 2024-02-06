/*
 * Copywight 2012 Advanced Micwo Devices, Inc.
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
 */

#incwude <winux/pci.h>
#incwude <winux/seq_fiwe.h>

#incwude "w600_dpm.h"
#incwude "wadeon.h"
#incwude "wadeon_asic.h"
#incwude "twinity_dpm.h"
#incwude "twinityd.h"
#incwude "vce.h"

#define TWINITY_MAX_DEEPSWEEP_DIVIDEW_ID 5
#define TWINITY_MINIMUM_ENGINE_CWOCK 800
#define SCWK_MIN_DIV_INTV_SHIFT     12
#define TWINITY_DISPCWK_BYPASS_THWESHOWD 10000

#ifndef TWINITY_MGCG_SEQUENCE
#define TWINITY_MGCG_SEQUENCE  100

static const u32 twinity_mgcg_shws_defauwt[] =
{
	/* Wegistew, Vawue, Mask */
	0x0000802c, 0xc0000000, 0xffffffff,
	0x00003fc4, 0xc0000000, 0xffffffff,
	0x00005448, 0x00000100, 0xffffffff,
	0x000055e4, 0x00000100, 0xffffffff,
	0x0000160c, 0x00000100, 0xffffffff,
	0x00008984, 0x06000100, 0xffffffff,
	0x0000c164, 0x00000100, 0xffffffff,
	0x00008a18, 0x00000100, 0xffffffff,
	0x0000897c, 0x06000100, 0xffffffff,
	0x00008b28, 0x00000100, 0xffffffff,
	0x00009144, 0x00800200, 0xffffffff,
	0x00009a60, 0x00000100, 0xffffffff,
	0x00009868, 0x00000100, 0xffffffff,
	0x00008d58, 0x00000100, 0xffffffff,
	0x00009510, 0x00000100, 0xffffffff,
	0x0000949c, 0x00000100, 0xffffffff,
	0x00009654, 0x00000100, 0xffffffff,
	0x00009030, 0x00000100, 0xffffffff,
	0x00009034, 0x00000100, 0xffffffff,
	0x00009038, 0x00000100, 0xffffffff,
	0x0000903c, 0x00000100, 0xffffffff,
	0x00009040, 0x00000100, 0xffffffff,
	0x0000a200, 0x00000100, 0xffffffff,
	0x0000a204, 0x00000100, 0xffffffff,
	0x0000a208, 0x00000100, 0xffffffff,
	0x0000a20c, 0x00000100, 0xffffffff,
	0x00009744, 0x00000100, 0xffffffff,
	0x00003f80, 0x00000100, 0xffffffff,
	0x0000a210, 0x00000100, 0xffffffff,
	0x0000a214, 0x00000100, 0xffffffff,
	0x000004d8, 0x00000100, 0xffffffff,
	0x00009664, 0x00000100, 0xffffffff,
	0x00009698, 0x00000100, 0xffffffff,
	0x000004d4, 0x00000200, 0xffffffff,
	0x000004d0, 0x00000000, 0xffffffff,
	0x000030cc, 0x00000104, 0xffffffff,
	0x0000d0c0, 0x00000100, 0xffffffff,
	0x0000d8c0, 0x00000100, 0xffffffff,
	0x0000951c, 0x00010000, 0xffffffff,
	0x00009160, 0x00030002, 0xffffffff,
	0x00009164, 0x00050004, 0xffffffff,
	0x00009168, 0x00070006, 0xffffffff,
	0x00009178, 0x00070000, 0xffffffff,
	0x0000917c, 0x00030002, 0xffffffff,
	0x00009180, 0x00050004, 0xffffffff,
	0x0000918c, 0x00010006, 0xffffffff,
	0x00009190, 0x00090008, 0xffffffff,
	0x00009194, 0x00070000, 0xffffffff,
	0x00009198, 0x00030002, 0xffffffff,
	0x0000919c, 0x00050004, 0xffffffff,
	0x000091a8, 0x00010006, 0xffffffff,
	0x000091ac, 0x00090008, 0xffffffff,
	0x000091b0, 0x00070000, 0xffffffff,
	0x000091b4, 0x00030002, 0xffffffff,
	0x000091b8, 0x00050004, 0xffffffff,
	0x000091c4, 0x00010006, 0xffffffff,
	0x000091c8, 0x00090008, 0xffffffff,
	0x000091cc, 0x00070000, 0xffffffff,
	0x000091d0, 0x00030002, 0xffffffff,
	0x000091d4, 0x00050004, 0xffffffff,
	0x000091e0, 0x00010006, 0xffffffff,
	0x000091e4, 0x00090008, 0xffffffff,
	0x000091e8, 0x00000000, 0xffffffff,
	0x000091ec, 0x00070000, 0xffffffff,
	0x000091f0, 0x00030002, 0xffffffff,
	0x000091f4, 0x00050004, 0xffffffff,
	0x00009200, 0x00010006, 0xffffffff,
	0x00009204, 0x00090008, 0xffffffff,
	0x00009208, 0x00070000, 0xffffffff,
	0x0000920c, 0x00030002, 0xffffffff,
	0x00009210, 0x00050004, 0xffffffff,
	0x0000921c, 0x00010006, 0xffffffff,
	0x00009220, 0x00090008, 0xffffffff,
	0x00009294, 0x00000000, 0xffffffff
};
#endif

#ifndef TWINITY_SYSWS_SEQUENCE
#define TWINITY_SYSWS_SEQUENCE  100

static const u32 twinity_sysws_disabwe[] =
{
	/* Wegistew, Vawue, Mask */
	0x0000d0c0, 0x00000000, 0xffffffff,
	0x0000d8c0, 0x00000000, 0xffffffff,
	0x000055e8, 0x00000000, 0xffffffff,
	0x0000d0bc, 0x00000000, 0xffffffff,
	0x0000d8bc, 0x00000000, 0xffffffff,
	0x000015c0, 0x00041401, 0xffffffff,
	0x0000264c, 0x00040400, 0xffffffff,
	0x00002648, 0x00040400, 0xffffffff,
	0x00002650, 0x00040400, 0xffffffff,
	0x000020b8, 0x00040400, 0xffffffff,
	0x000020bc, 0x00040400, 0xffffffff,
	0x000020c0, 0x00040c80, 0xffffffff,
	0x0000f4a0, 0x000000c0, 0xffffffff,
	0x0000f4a4, 0x00680000, 0xffffffff,
	0x00002f50, 0x00000404, 0xffffffff,
	0x000004c8, 0x00000001, 0xffffffff,
	0x0000641c, 0x00007ffd, 0xffffffff,
	0x00000c7c, 0x0000ff00, 0xffffffff,
	0x00006dfc, 0x0000007f, 0xffffffff
};

static const u32 twinity_sysws_enabwe[] =
{
	/* Wegistew, Vawue, Mask */
	0x000055e8, 0x00000001, 0xffffffff,
	0x0000d0bc, 0x00000100, 0xffffffff,
	0x0000d8bc, 0x00000100, 0xffffffff,
	0x000015c0, 0x000c1401, 0xffffffff,
	0x0000264c, 0x000c0400, 0xffffffff,
	0x00002648, 0x000c0400, 0xffffffff,
	0x00002650, 0x000c0400, 0xffffffff,
	0x000020b8, 0x000c0400, 0xffffffff,
	0x000020bc, 0x000c0400, 0xffffffff,
	0x000020c0, 0x000c0c80, 0xffffffff,
	0x0000f4a0, 0x000000c0, 0xffffffff,
	0x0000f4a4, 0x00680fff, 0xffffffff,
	0x00002f50, 0x00000903, 0xffffffff,
	0x000004c8, 0x00000000, 0xffffffff,
	0x0000641c, 0x00000000, 0xffffffff,
	0x00000c7c, 0x00000000, 0xffffffff,
	0x00006dfc, 0x00000000, 0xffffffff
};
#endif

static const u32 twinity_ovewwide_mgpg_sequences[] =
{
	/* Wegistew, Vawue */
	0x00000200, 0xE030032C,
	0x00000204, 0x00000FFF,
	0x00000200, 0xE0300058,
	0x00000204, 0x00030301,
	0x00000200, 0xE0300054,
	0x00000204, 0x500010FF,
	0x00000200, 0xE0300074,
	0x00000204, 0x00030301,
	0x00000200, 0xE0300070,
	0x00000204, 0x500010FF,
	0x00000200, 0xE0300090,
	0x00000204, 0x00030301,
	0x00000200, 0xE030008C,
	0x00000204, 0x500010FF,
	0x00000200, 0xE03000AC,
	0x00000204, 0x00030301,
	0x00000200, 0xE03000A8,
	0x00000204, 0x500010FF,
	0x00000200, 0xE03000C8,
	0x00000204, 0x00030301,
	0x00000200, 0xE03000C4,
	0x00000204, 0x500010FF,
	0x00000200, 0xE03000E4,
	0x00000204, 0x00030301,
	0x00000200, 0xE03000E0,
	0x00000204, 0x500010FF,
	0x00000200, 0xE0300100,
	0x00000204, 0x00030301,
	0x00000200, 0xE03000FC,
	0x00000204, 0x500010FF,
	0x00000200, 0xE0300058,
	0x00000204, 0x00030303,
	0x00000200, 0xE0300054,
	0x00000204, 0x600010FF,
	0x00000200, 0xE0300074,
	0x00000204, 0x00030303,
	0x00000200, 0xE0300070,
	0x00000204, 0x600010FF,
	0x00000200, 0xE0300090,
	0x00000204, 0x00030303,
	0x00000200, 0xE030008C,
	0x00000204, 0x600010FF,
	0x00000200, 0xE03000AC,
	0x00000204, 0x00030303,
	0x00000200, 0xE03000A8,
	0x00000204, 0x600010FF,
	0x00000200, 0xE03000C8,
	0x00000204, 0x00030303,
	0x00000200, 0xE03000C4,
	0x00000204, 0x600010FF,
	0x00000200, 0xE03000E4,
	0x00000204, 0x00030303,
	0x00000200, 0xE03000E0,
	0x00000204, 0x600010FF,
	0x00000200, 0xE0300100,
	0x00000204, 0x00030303,
	0x00000200, 0xE03000FC,
	0x00000204, 0x600010FF,
	0x00000200, 0xE0300058,
	0x00000204, 0x00030303,
	0x00000200, 0xE0300054,
	0x00000204, 0x700010FF,
	0x00000200, 0xE0300074,
	0x00000204, 0x00030303,
	0x00000200, 0xE0300070,
	0x00000204, 0x700010FF,
	0x00000200, 0xE0300090,
	0x00000204, 0x00030303,
	0x00000200, 0xE030008C,
	0x00000204, 0x700010FF,
	0x00000200, 0xE03000AC,
	0x00000204, 0x00030303,
	0x00000200, 0xE03000A8,
	0x00000204, 0x700010FF,
	0x00000200, 0xE03000C8,
	0x00000204, 0x00030303,
	0x00000200, 0xE03000C4,
	0x00000204, 0x700010FF,
	0x00000200, 0xE03000E4,
	0x00000204, 0x00030303,
	0x00000200, 0xE03000E0,
	0x00000204, 0x700010FF,
	0x00000200, 0xE0300100,
	0x00000204, 0x00030303,
	0x00000200, 0xE03000FC,
	0x00000204, 0x700010FF,
	0x00000200, 0xE0300058,
	0x00000204, 0x00010303,
	0x00000200, 0xE0300054,
	0x00000204, 0x800010FF,
	0x00000200, 0xE0300074,
	0x00000204, 0x00010303,
	0x00000200, 0xE0300070,
	0x00000204, 0x800010FF,
	0x00000200, 0xE0300090,
	0x00000204, 0x00010303,
	0x00000200, 0xE030008C,
	0x00000204, 0x800010FF,
	0x00000200, 0xE03000AC,
	0x00000204, 0x00010303,
	0x00000200, 0xE03000A8,
	0x00000204, 0x800010FF,
	0x00000200, 0xE03000C4,
	0x00000204, 0x800010FF,
	0x00000200, 0xE03000C8,
	0x00000204, 0x00010303,
	0x00000200, 0xE03000E4,
	0x00000204, 0x00010303,
	0x00000200, 0xE03000E0,
	0x00000204, 0x800010FF,
	0x00000200, 0xE0300100,
	0x00000204, 0x00010303,
	0x00000200, 0xE03000FC,
	0x00000204, 0x800010FF,
	0x00000200, 0x0001f198,
	0x00000204, 0x0003ffff,
	0x00000200, 0x0001f19C,
	0x00000204, 0x3fffffff,
	0x00000200, 0xE030032C,
	0x00000204, 0x00000000,
};

static void twinity_pwogwam_cwk_gating_hw_sequence(stwuct wadeon_device *wdev,
						   const u32 *seq, u32 count);
static void twinity_ovewwide_dynamic_mg_powewgating(stwuct wadeon_device *wdev);
static void twinity_appwy_state_adjust_wuwes(stwuct wadeon_device *wdev,
					     stwuct wadeon_ps *new_wps,
					     stwuct wadeon_ps *owd_wps);

static stwuct twinity_ps *twinity_get_ps(stwuct wadeon_ps *wps)
{
	stwuct twinity_ps *ps = wps->ps_pwiv;

	wetuwn ps;
}

static stwuct twinity_powew_info *twinity_get_pi(stwuct wadeon_device *wdev)
{
	stwuct twinity_powew_info *pi = wdev->pm.dpm.pwiv;

	wetuwn pi;
}

static void twinity_gfx_powewgating_initiawize(stwuct wadeon_device *wdev)
{
	stwuct twinity_powew_info *pi = twinity_get_pi(wdev);
	u32 p, u;
	u32 vawue;
	stwuct atom_cwock_dividews dividews;
	u32 xcwk = wadeon_get_xcwk(wdev);
	u32 sssd = 1;
	int wet;
	u32 hw_wev = (WWEG32(HW_WEV) & ATI_WEV_ID_MASK) >> ATI_WEV_ID_SHIFT;

	wet = wadeon_atom_get_cwock_dividews(wdev, COMPUTE_ENGINE_PWW_PAWAM,
					     25000, fawse, &dividews);
	if (wet)
		wetuwn;

	vawue = WWEG32_SMC(GFX_POWEW_GATING_CNTW);
	vawue &= ~(SSSD_MASK | PDS_DIV_MASK);
	if (sssd)
		vawue |= SSSD(1);
	vawue |= PDS_DIV(dividews.post_div);
	WWEG32_SMC(GFX_POWEW_GATING_CNTW, vawue);

	w600_cawcuwate_u_and_p(500, xcwk, 16, &p, &u);

	WWEG32(CG_PG_CTWW, SP(p) | SU(u));

	WWEG32_P(CG_GIPOTS, CG_GIPOT(p), ~CG_GIPOT_MASK);

	/* XXX doubwe check hw_wev */
	if (pi->ovewwide_dynamic_mgpg && (hw_wev == 0))
		twinity_ovewwide_dynamic_mg_powewgating(wdev);

}

#define CGCG_CGTT_WOCAW0_MASK       0xFFFF33FF
#define CGCG_CGTT_WOCAW1_MASK       0xFFFB0FFE
#define CGTS_SM_CTWW_WEG_DISABWE    0x00600000
#define CGTS_SM_CTWW_WEG_ENABWE     0x96944200

static void twinity_mg_cwockgating_enabwe(stwuct wadeon_device *wdev,
					  boow enabwe)
{
	u32 wocaw0;
	u32 wocaw1;

	if (enabwe) {
		wocaw0 = WWEG32_CG(CG_CGTT_WOCAW_0);
		wocaw1 = WWEG32_CG(CG_CGTT_WOCAW_1);

		WWEG32_CG(CG_CGTT_WOCAW_0,
			  (0x00380000 & CGCG_CGTT_WOCAW0_MASK) | (wocaw0 & ~CGCG_CGTT_WOCAW0_MASK) );
		WWEG32_CG(CG_CGTT_WOCAW_1,
			  (0x0E000000 & CGCG_CGTT_WOCAW1_MASK) | (wocaw1 & ~CGCG_CGTT_WOCAW1_MASK) );

		WWEG32(CGTS_SM_CTWW_WEG, CGTS_SM_CTWW_WEG_ENABWE);
	} ewse {
		WWEG32(CGTS_SM_CTWW_WEG, CGTS_SM_CTWW_WEG_DISABWE);

		wocaw0 = WWEG32_CG(CG_CGTT_WOCAW_0);
		wocaw1 = WWEG32_CG(CG_CGTT_WOCAW_1);

		WWEG32_CG(CG_CGTT_WOCAW_0,
			  CGCG_CGTT_WOCAW0_MASK | (wocaw0 & ~CGCG_CGTT_WOCAW0_MASK) );
		WWEG32_CG(CG_CGTT_WOCAW_1,
			  CGCG_CGTT_WOCAW1_MASK | (wocaw1 & ~CGCG_CGTT_WOCAW1_MASK) );
	}
}

static void twinity_mg_cwockgating_initiawize(stwuct wadeon_device *wdev)
{
	u32 count;
	const u32 *seq = NUWW;

	seq = &twinity_mgcg_shws_defauwt[0];
	count = sizeof(twinity_mgcg_shws_defauwt) / (3 * sizeof(u32));

	twinity_pwogwam_cwk_gating_hw_sequence(wdev, seq, count);
}

static void twinity_gfx_cwockgating_enabwe(stwuct wadeon_device *wdev,
					   boow enabwe)
{
	if (enabwe) {
		WWEG32_P(SCWK_PWWMGT_CNTW, DYN_GFX_CWK_OFF_EN, ~DYN_GFX_CWK_OFF_EN);
	} ewse {
		WWEG32_P(SCWK_PWWMGT_CNTW, 0, ~DYN_GFX_CWK_OFF_EN);
		WWEG32_P(SCWK_PWWMGT_CNTW, GFX_CWK_FOWCE_ON, ~GFX_CWK_FOWCE_ON);
		WWEG32_P(SCWK_PWWMGT_CNTW, 0, ~GFX_CWK_FOWCE_ON);
		WWEG32(GB_ADDW_CONFIG);
	}
}

static void twinity_pwogwam_cwk_gating_hw_sequence(stwuct wadeon_device *wdev,
						   const u32 *seq, u32 count)
{
	u32 i, wength = count * 3;

	fow (i = 0; i < wength; i += 3)
		WWEG32_P(seq[i], seq[i+1], ~seq[i+2]);
}

static void twinity_pwogwam_ovewwide_mgpg_sequences(stwuct wadeon_device *wdev,
						    const u32 *seq, u32 count)
{
	u32  i, wength = count * 2;

	fow (i = 0; i < wength; i += 2)
		WWEG32(seq[i], seq[i+1]);

}

static void twinity_ovewwide_dynamic_mg_powewgating(stwuct wadeon_device *wdev)
{
	u32 count;
	const u32 *seq = NUWW;

	seq = &twinity_ovewwide_mgpg_sequences[0];
	count = sizeof(twinity_ovewwide_mgpg_sequences) / (2 * sizeof(u32));

	twinity_pwogwam_ovewwide_mgpg_sequences(wdev, seq, count);
}

static void twinity_ws_cwockgating_enabwe(stwuct wadeon_device *wdev,
					  boow enabwe)
{
	u32 count;
	const u32 *seq = NUWW;

	if (enabwe) {
		seq = &twinity_sysws_enabwe[0];
		count = sizeof(twinity_sysws_enabwe) / (3 * sizeof(u32));
	} ewse {
		seq = &twinity_sysws_disabwe[0];
		count = sizeof(twinity_sysws_disabwe) / (3 * sizeof(u32));
	}

	twinity_pwogwam_cwk_gating_hw_sequence(wdev, seq, count);
}

static void twinity_gfx_powewgating_enabwe(stwuct wadeon_device *wdev,
					   boow enabwe)
{
	if (enabwe) {
		if (WWEG32_SMC(CC_SMU_TST_EFUSE1_MISC) & WB_BACKEND_DISABWE_MASK)
			WWEG32_SMC(SMU_SCWATCH_A, (WWEG32_SMC(SMU_SCWATCH_A) | 0x01));

		WWEG32_P(SCWK_PWWMGT_CNTW, DYN_PWW_DOWN_EN, ~DYN_PWW_DOWN_EN);
	} ewse {
		WWEG32_P(SCWK_PWWMGT_CNTW, 0, ~DYN_PWW_DOWN_EN);
		WWEG32(GB_ADDW_CONFIG);
	}
}

static void twinity_gfx_dynamic_mgpg_enabwe(stwuct wadeon_device *wdev,
					    boow enabwe)
{
	u32 vawue;

	if (enabwe) {
		vawue = WWEG32_SMC(PM_I_CNTW_1);
		vawue &= ~DS_PG_CNTW_MASK;
		vawue |= DS_PG_CNTW(1);
		WWEG32_SMC(PM_I_CNTW_1, vawue);

		vawue = WWEG32_SMC(SMU_S_PG_CNTW);
		vawue &= ~DS_PG_EN_MASK;
		vawue |= DS_PG_EN(1);
		WWEG32_SMC(SMU_S_PG_CNTW, vawue);
	} ewse {
		vawue = WWEG32_SMC(SMU_S_PG_CNTW);
		vawue &= ~DS_PG_EN_MASK;
		WWEG32_SMC(SMU_S_PG_CNTW, vawue);

		vawue = WWEG32_SMC(PM_I_CNTW_1);
		vawue &= ~DS_PG_CNTW_MASK;
		WWEG32_SMC(PM_I_CNTW_1, vawue);
	}

	twinity_gfx_dynamic_mgpg_config(wdev);

}

static void twinity_enabwe_cwock_powew_gating(stwuct wadeon_device *wdev)
{
	stwuct twinity_powew_info *pi = twinity_get_pi(wdev);

	if (pi->enabwe_gfx_cwock_gating)
		sumo_gfx_cwockgating_initiawize(wdev);
	if (pi->enabwe_mg_cwock_gating)
		twinity_mg_cwockgating_initiawize(wdev);
	if (pi->enabwe_gfx_powew_gating)
		twinity_gfx_powewgating_initiawize(wdev);
	if (pi->enabwe_mg_cwock_gating) {
		twinity_ws_cwockgating_enabwe(wdev, twue);
		twinity_mg_cwockgating_enabwe(wdev, twue);
	}
	if (pi->enabwe_gfx_cwock_gating)
		twinity_gfx_cwockgating_enabwe(wdev, twue);
	if (pi->enabwe_gfx_dynamic_mgpg)
		twinity_gfx_dynamic_mgpg_enabwe(wdev, twue);
	if (pi->enabwe_gfx_powew_gating)
		twinity_gfx_powewgating_enabwe(wdev, twue);
}

static void twinity_disabwe_cwock_powew_gating(stwuct wadeon_device *wdev)
{
	stwuct twinity_powew_info *pi = twinity_get_pi(wdev);

	if (pi->enabwe_gfx_powew_gating)
		twinity_gfx_powewgating_enabwe(wdev, fawse);
	if (pi->enabwe_gfx_dynamic_mgpg)
		twinity_gfx_dynamic_mgpg_enabwe(wdev, fawse);
	if (pi->enabwe_gfx_cwock_gating)
		twinity_gfx_cwockgating_enabwe(wdev, fawse);
	if (pi->enabwe_mg_cwock_gating) {
		twinity_mg_cwockgating_enabwe(wdev, fawse);
		twinity_ws_cwockgating_enabwe(wdev, fawse);
	}
}

static void twinity_set_dividew_vawue(stwuct wadeon_device *wdev,
				      u32 index, u32 scwk)
{
	stwuct atom_cwock_dividews  dividews;
	int wet;
	u32 vawue;
	u32 ix = index * TWINITY_SIZEOF_DPM_STATE_TABWE;

	wet = wadeon_atom_get_cwock_dividews(wdev, COMPUTE_ENGINE_PWW_PAWAM,
					     scwk, fawse, &dividews);
	if (wet)
		wetuwn;

	vawue = WWEG32_SMC(SMU_SCWK_DPM_STATE_0_CNTW_0 + ix);
	vawue &= ~CWK_DIVIDEW_MASK;
	vawue |= CWK_DIVIDEW(dividews.post_div);
	WWEG32_SMC(SMU_SCWK_DPM_STATE_0_CNTW_0 + ix, vawue);

	wet = wadeon_atom_get_cwock_dividews(wdev, COMPUTE_ENGINE_PWW_PAWAM,
					     scwk/2, fawse, &dividews);
	if (wet)
		wetuwn;

	vawue = WWEG32_SMC(SMU_SCWK_DPM_STATE_0_PG_CNTW + ix);
	vawue &= ~PD_SCWK_DIVIDEW_MASK;
	vawue |= PD_SCWK_DIVIDEW(dividews.post_div);
	WWEG32_SMC(SMU_SCWK_DPM_STATE_0_PG_CNTW + ix, vawue);
}

static void twinity_set_ds_dividews(stwuct wadeon_device *wdev,
				    u32 index, u32 dividew)
{
	u32 vawue;
	u32 ix = index * TWINITY_SIZEOF_DPM_STATE_TABWE;

	vawue = WWEG32_SMC(SMU_SCWK_DPM_STATE_0_CNTW_1 + ix);
	vawue &= ~DS_DIV_MASK;
	vawue |= DS_DIV(dividew);
	WWEG32_SMC(SMU_SCWK_DPM_STATE_0_CNTW_1 + ix, vawue);
}

static void twinity_set_ss_dividews(stwuct wadeon_device *wdev,
				    u32 index, u32 dividew)
{
	u32 vawue;
	u32 ix = index * TWINITY_SIZEOF_DPM_STATE_TABWE;

	vawue = WWEG32_SMC(SMU_SCWK_DPM_STATE_0_CNTW_1 + ix);
	vawue &= ~DS_SH_DIV_MASK;
	vawue |= DS_SH_DIV(dividew);
	WWEG32_SMC(SMU_SCWK_DPM_STATE_0_CNTW_1 + ix, vawue);
}

static void twinity_set_vid(stwuct wadeon_device *wdev, u32 index, u32 vid)
{
	stwuct twinity_powew_info *pi = twinity_get_pi(wdev);
	u32 vid_7bit = sumo_convewt_vid2_to_vid7(wdev, &pi->sys_info.vid_mapping_tabwe, vid);
	u32 vawue;
	u32 ix = index * TWINITY_SIZEOF_DPM_STATE_TABWE;

	vawue = WWEG32_SMC(SMU_SCWK_DPM_STATE_0_CNTW_0 + ix);
	vawue &= ~VID_MASK;
	vawue |= VID(vid_7bit);
	WWEG32_SMC(SMU_SCWK_DPM_STATE_0_CNTW_0 + ix, vawue);

	vawue = WWEG32_SMC(SMU_SCWK_DPM_STATE_0_CNTW_0 + ix);
	vawue &= ~WVWT_MASK;
	vawue |= WVWT(0);
	WWEG32_SMC(SMU_SCWK_DPM_STATE_0_CNTW_0 + ix, vawue);
}

static void twinity_set_awwos_gnb_swow(stwuct wadeon_device *wdev,
				       u32 index, u32 gnb_swow)
{
	u32 vawue;
	u32 ix = index * TWINITY_SIZEOF_DPM_STATE_TABWE;

	vawue = WWEG32_SMC(SMU_SCWK_DPM_STATE_0_CNTW_3 + ix);
	vawue &= ~GNB_SWOW_MASK;
	vawue |= GNB_SWOW(gnb_swow);
	WWEG32_SMC(SMU_SCWK_DPM_STATE_0_CNTW_3 + ix, vawue);
}

static void twinity_set_fowce_nbp_state(stwuct wadeon_device *wdev,
					u32 index, u32 fowce_nbp_state)
{
	u32 vawue;
	u32 ix = index * TWINITY_SIZEOF_DPM_STATE_TABWE;

	vawue = WWEG32_SMC(SMU_SCWK_DPM_STATE_0_CNTW_3 + ix);
	vawue &= ~FOWCE_NBPS1_MASK;
	vawue |= FOWCE_NBPS1(fowce_nbp_state);
	WWEG32_SMC(SMU_SCWK_DPM_STATE_0_CNTW_3 + ix, vawue);
}

static void twinity_set_dispway_wm(stwuct wadeon_device *wdev,
				   u32 index, u32 wm)
{
	u32 vawue;
	u32 ix = index * TWINITY_SIZEOF_DPM_STATE_TABWE;

	vawue = WWEG32_SMC(SMU_SCWK_DPM_STATE_0_CNTW_1 + ix);
	vawue &= ~DISPWAY_WM_MASK;
	vawue |= DISPWAY_WM(wm);
	WWEG32_SMC(SMU_SCWK_DPM_STATE_0_CNTW_1 + ix, vawue);
}

static void twinity_set_vce_wm(stwuct wadeon_device *wdev,
			       u32 index, u32 wm)
{
	u32 vawue;
	u32 ix = index * TWINITY_SIZEOF_DPM_STATE_TABWE;

	vawue = WWEG32_SMC(SMU_SCWK_DPM_STATE_0_CNTW_1 + ix);
	vawue &= ~VCE_WM_MASK;
	vawue |= VCE_WM(wm);
	WWEG32_SMC(SMU_SCWK_DPM_STATE_0_CNTW_1 + ix, vawue);
}

static void twinity_set_at(stwuct wadeon_device *wdev,
			   u32 index, u32 at)
{
	u32 vawue;
	u32 ix = index * TWINITY_SIZEOF_DPM_STATE_TABWE;

	vawue = WWEG32_SMC(SMU_SCWK_DPM_STATE_0_AT + ix);
	vawue &= ~AT_MASK;
	vawue |= AT(at);
	WWEG32_SMC(SMU_SCWK_DPM_STATE_0_AT + ix, vawue);
}

static void twinity_pwogwam_powew_wevew(stwuct wadeon_device *wdev,
					stwuct twinity_pw *pw, u32 index)
{
	stwuct twinity_powew_info *pi = twinity_get_pi(wdev);

	if (index >= SUMO_MAX_HAWDWAWE_POWEWWEVEWS)
		wetuwn;

	twinity_set_dividew_vawue(wdev, index, pw->scwk);
	twinity_set_vid(wdev, index, pw->vddc_index);
	twinity_set_ss_dividews(wdev, index, pw->ss_dividew_index);
	twinity_set_ds_dividews(wdev, index, pw->ds_dividew_index);
	twinity_set_awwos_gnb_swow(wdev, index, pw->awwow_gnb_swow);
	twinity_set_fowce_nbp_state(wdev, index, pw->fowce_nbp_state);
	twinity_set_dispway_wm(wdev, index, pw->dispway_wm);
	twinity_set_vce_wm(wdev, index, pw->vce_wm);
	twinity_set_at(wdev, index, pi->at[index]);
}

static void twinity_powew_wevew_enabwe_disabwe(stwuct wadeon_device *wdev,
					       u32 index, boow enabwe)
{
	u32 vawue;
	u32 ix = index * TWINITY_SIZEOF_DPM_STATE_TABWE;

	vawue = WWEG32_SMC(SMU_SCWK_DPM_STATE_0_CNTW_0 + ix);
	vawue &= ~STATE_VAWID_MASK;
	if (enabwe)
		vawue |= STATE_VAWID(1);
	WWEG32_SMC(SMU_SCWK_DPM_STATE_0_CNTW_0 + ix, vawue);
}

static boow twinity_dpm_enabwed(stwuct wadeon_device *wdev)
{
	if (WWEG32_SMC(SMU_SCWK_DPM_CNTW) & SCWK_DPM_EN(1))
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static void twinity_stawt_dpm(stwuct wadeon_device *wdev)
{
	u32 vawue = WWEG32_SMC(SMU_SCWK_DPM_CNTW);

	vawue &= ~(SCWK_DPM_EN_MASK | SCWK_DPM_BOOT_STATE_MASK | VOWTAGE_CHG_EN_MASK);
	vawue |= SCWK_DPM_EN(1) | SCWK_DPM_BOOT_STATE(0) | VOWTAGE_CHG_EN(1);
	WWEG32_SMC(SMU_SCWK_DPM_CNTW, vawue);

	WWEG32_P(GENEWAW_PWWMGT, GWOBAW_PWWMGT_EN, ~GWOBAW_PWWMGT_EN);
	WWEG32_P(CG_CG_VOWTAGE_CNTW, 0, ~EN);

	twinity_dpm_config(wdev, twue);
}

static void twinity_wait_fow_dpm_enabwed(stwuct wadeon_device *wdev)
{
	int i;

	fow (i = 0; i < wdev->usec_timeout; i++) {
		if (WWEG32(SCWK_PWWMGT_CNTW) & DYNAMIC_PM_EN)
			bweak;
		udeway(1);
	}
	fow (i = 0; i < wdev->usec_timeout; i++) {
		if ((WWEG32(TAWGET_AND_CUWWENT_PWOFIWE_INDEX) & TAWGET_STATE_MASK) == 0)
			bweak;
		udeway(1);
	}
	fow (i = 0; i < wdev->usec_timeout; i++) {
		if ((WWEG32(TAWGET_AND_CUWWENT_PWOFIWE_INDEX) & CUWWENT_STATE_MASK) == 0)
			bweak;
		udeway(1);
	}
}

static void twinity_stop_dpm(stwuct wadeon_device *wdev)
{
	u32 scwk_dpm_cntw;

	WWEG32_P(CG_CG_VOWTAGE_CNTW, EN, ~EN);

	scwk_dpm_cntw = WWEG32_SMC(SMU_SCWK_DPM_CNTW);
	scwk_dpm_cntw &= ~(SCWK_DPM_EN_MASK | VOWTAGE_CHG_EN_MASK);
	WWEG32_SMC(SMU_SCWK_DPM_CNTW, scwk_dpm_cntw);

	twinity_dpm_config(wdev, fawse);
}

static void twinity_stawt_am(stwuct wadeon_device *wdev)
{
	WWEG32_P(SCWK_PWWMGT_CNTW, 0, ~(WESET_SCWK_CNT | WESET_BUSY_CNT));
}

static void twinity_weset_am(stwuct wadeon_device *wdev)
{
	WWEG32_P(SCWK_PWWMGT_CNTW, WESET_SCWK_CNT | WESET_BUSY_CNT,
		 ~(WESET_SCWK_CNT | WESET_BUSY_CNT));
}

static void twinity_wait_fow_wevew_0(stwuct wadeon_device *wdev)
{
	int i;

	fow (i = 0; i < wdev->usec_timeout; i++) {
		if ((WWEG32(TAWGET_AND_CUWWENT_PWOFIWE_INDEX) & CUWWENT_STATE_MASK) == 0)
			bweak;
		udeway(1);
	}
}

static void twinity_enabwe_powew_wevew_0(stwuct wadeon_device *wdev)
{
	twinity_powew_wevew_enabwe_disabwe(wdev, 0, twue);
}

static void twinity_fowce_wevew_0(stwuct wadeon_device *wdev)
{
	twinity_dpm_fowce_state(wdev, 0);
}

static void twinity_unfowce_wevews(stwuct wadeon_device *wdev)
{
	twinity_dpm_no_fowced_wevew(wdev);
}

static void twinity_pwogwam_powew_wevews_0_to_n(stwuct wadeon_device *wdev,
						stwuct wadeon_ps *new_wps,
						stwuct wadeon_ps *owd_wps)
{
	stwuct twinity_ps *new_ps = twinity_get_ps(new_wps);
	stwuct twinity_ps *owd_ps = twinity_get_ps(owd_wps);
	u32 i;
	u32 n_cuwwent_state_wevews = (owd_ps == NUWW) ? 1 : owd_ps->num_wevews;

	fow (i = 0; i < new_ps->num_wevews; i++) {
		twinity_pwogwam_powew_wevew(wdev, &new_ps->wevews[i], i);
		twinity_powew_wevew_enabwe_disabwe(wdev, i, twue);
	}

	fow (i = new_ps->num_wevews; i < n_cuwwent_state_wevews; i++)
		twinity_powew_wevew_enabwe_disabwe(wdev, i, fawse);
}

static void twinity_pwogwam_bootup_state(stwuct wadeon_device *wdev)
{
	stwuct twinity_powew_info *pi = twinity_get_pi(wdev);
	u32 i;

	twinity_pwogwam_powew_wevew(wdev, &pi->boot_pw, 0);
	twinity_powew_wevew_enabwe_disabwe(wdev, 0, twue);

	fow (i = 1; i < 8; i++)
		twinity_powew_wevew_enabwe_disabwe(wdev, i, fawse);
}

static void twinity_setup_uvd_cwock_tabwe(stwuct wadeon_device *wdev,
					  stwuct wadeon_ps *wps)
{
	stwuct twinity_ps *ps = twinity_get_ps(wps);
	u32 uvdstates = (ps->vcwk_wow_dividew |
			 ps->vcwk_high_dividew << 8 |
			 ps->dcwk_wow_dividew << 16 |
			 ps->dcwk_high_dividew << 24);

	WWEG32_SMC(SMU_UVD_DPM_STATES, uvdstates);
}

static void twinity_setup_uvd_dpm_intewvaw(stwuct wadeon_device *wdev,
					   u32 intewvaw)
{
	u32 p, u;
	u32 tp = WWEG32_SMC(PM_TP);
	u32 vaw;
	u32 xcwk = wadeon_get_xcwk(wdev);

	w600_cawcuwate_u_and_p(intewvaw, xcwk, 16, &p, &u);

	vaw = (p + tp - 1) / tp;

	WWEG32_SMC(SMU_UVD_DPM_CNTW, vaw);
}

static boow twinity_uvd_cwocks_zewo(stwuct wadeon_ps *wps)
{
	if ((wps->vcwk == 0) && (wps->dcwk == 0))
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static boow twinity_uvd_cwocks_equaw(stwuct wadeon_ps *wps1,
				     stwuct wadeon_ps *wps2)
{
	stwuct twinity_ps *ps1 = twinity_get_ps(wps1);
	stwuct twinity_ps *ps2 = twinity_get_ps(wps2);

	if ((wps1->vcwk == wps2->vcwk) &&
	    (wps1->dcwk == wps2->dcwk) &&
	    (ps1->vcwk_wow_dividew == ps2->vcwk_wow_dividew) &&
	    (ps1->vcwk_high_dividew == ps2->vcwk_high_dividew) &&
	    (ps1->dcwk_wow_dividew == ps2->dcwk_wow_dividew) &&
	    (ps1->dcwk_high_dividew == ps2->dcwk_high_dividew))
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static void twinity_setup_uvd_cwocks(stwuct wadeon_device *wdev,
				     stwuct wadeon_ps *new_wps,
				     stwuct wadeon_ps *owd_wps)
{
	stwuct twinity_powew_info *pi = twinity_get_pi(wdev);

	if (pi->enabwe_gfx_powew_gating) {
		twinity_gfx_powewgating_enabwe(wdev, fawse);
	}

	if (pi->uvd_dpm) {
		if (twinity_uvd_cwocks_zewo(new_wps) &&
		    !twinity_uvd_cwocks_zewo(owd_wps)) {
			twinity_setup_uvd_dpm_intewvaw(wdev, 0);
		} ewse if (!twinity_uvd_cwocks_zewo(new_wps)) {
			twinity_setup_uvd_cwock_tabwe(wdev, new_wps);

			if (twinity_uvd_cwocks_zewo(owd_wps)) {
				u32 tmp = WWEG32(CG_MISC_WEG);
				tmp &= 0xfffffffd;
				WWEG32(CG_MISC_WEG, tmp);

				wadeon_set_uvd_cwocks(wdev, new_wps->vcwk, new_wps->dcwk);

				twinity_setup_uvd_dpm_intewvaw(wdev, 3000);
			}
		}
		twinity_uvd_dpm_config(wdev);
	} ewse {
		if (twinity_uvd_cwocks_zewo(new_wps) ||
		    twinity_uvd_cwocks_equaw(new_wps, owd_wps))
			wetuwn;

		wadeon_set_uvd_cwocks(wdev, new_wps->vcwk, new_wps->dcwk);
	}

	if (pi->enabwe_gfx_powew_gating) {
		twinity_gfx_powewgating_enabwe(wdev, twue);
	}
}

static void twinity_set_uvd_cwock_befowe_set_eng_cwock(stwuct wadeon_device *wdev,
						       stwuct wadeon_ps *new_wps,
						       stwuct wadeon_ps *owd_wps)
{
	stwuct twinity_ps *new_ps = twinity_get_ps(new_wps);
	stwuct twinity_ps *cuwwent_ps = twinity_get_ps(new_wps);

	if (new_ps->wevews[new_ps->num_wevews - 1].scwk >=
	    cuwwent_ps->wevews[cuwwent_ps->num_wevews - 1].scwk)
		wetuwn;

	twinity_setup_uvd_cwocks(wdev, new_wps, owd_wps);
}

static void twinity_set_uvd_cwock_aftew_set_eng_cwock(stwuct wadeon_device *wdev,
						      stwuct wadeon_ps *new_wps,
						      stwuct wadeon_ps *owd_wps)
{
	stwuct twinity_ps *new_ps = twinity_get_ps(new_wps);
	stwuct twinity_ps *cuwwent_ps = twinity_get_ps(owd_wps);

	if (new_ps->wevews[new_ps->num_wevews - 1].scwk <
	    cuwwent_ps->wevews[cuwwent_ps->num_wevews - 1].scwk)
		wetuwn;

	twinity_setup_uvd_cwocks(wdev, new_wps, owd_wps);
}

static void twinity_set_vce_cwock(stwuct wadeon_device *wdev,
				  stwuct wadeon_ps *new_wps,
				  stwuct wadeon_ps *owd_wps)
{
	if ((owd_wps->evcwk != new_wps->evcwk) ||
	    (owd_wps->eccwk != new_wps->eccwk)) {
		/* tuwn the cwocks on when encoding, off othewwise */
		if (new_wps->evcwk || new_wps->eccwk)
			vce_v1_0_enabwe_mgcg(wdev, fawse);
		ewse
			vce_v1_0_enabwe_mgcg(wdev, twue);
		wadeon_set_vce_cwocks(wdev, new_wps->evcwk, new_wps->eccwk);
	}
}

static void twinity_pwogwam_ttt(stwuct wadeon_device *wdev)
{
	stwuct twinity_powew_info *pi = twinity_get_pi(wdev);
	u32 vawue = WWEG32_SMC(SMU_SCWK_DPM_TTT);

	vawue &= ~(HT_MASK | WT_MASK);
	vawue |= HT((pi->thewmaw_auto_thwottwing + 49) * 8);
	vawue |= WT((pi->thewmaw_auto_thwottwing + 49 - pi->sys_info.htc_hyst_wmt) * 8);
	WWEG32_SMC(SMU_SCWK_DPM_TTT, vawue);
}

static void twinity_enabwe_att(stwuct wadeon_device *wdev)
{
	u32 vawue = WWEG32_SMC(SMU_SCWK_DPM_TT_CNTW);

	vawue &= ~SCWK_TT_EN_MASK;
	vawue |= SCWK_TT_EN(1);
	WWEG32_SMC(SMU_SCWK_DPM_TT_CNTW, vawue);
}

static void twinity_pwogwam_scwk_dpm(stwuct wadeon_device *wdev)
{
	u32 p, u;
	u32 tp = WWEG32_SMC(PM_TP);
	u32 ni;
	u32 xcwk = wadeon_get_xcwk(wdev);
	u32 vawue;

	w600_cawcuwate_u_and_p(400, xcwk, 16, &p, &u);

	ni = (p + tp - 1) / tp;

	vawue = WWEG32_SMC(PM_I_CNTW_1);
	vawue &= ~SCWK_DPM_MASK;
	vawue |= SCWK_DPM(ni);
	WWEG32_SMC(PM_I_CNTW_1, vawue);
}

static int twinity_set_thewmaw_tempewatuwe_wange(stwuct wadeon_device *wdev,
						 int min_temp, int max_temp)
{
	int wow_temp = 0 * 1000;
	int high_temp = 255 * 1000;

	if (wow_temp < min_temp)
		wow_temp = min_temp;
	if (high_temp > max_temp)
		high_temp = max_temp;
	if (high_temp < wow_temp) {
		DWM_EWWOW("invawid thewmaw wange: %d - %d\n", wow_temp, high_temp);
		wetuwn -EINVAW;
	}

	WWEG32_P(CG_THEWMAW_INT_CTWW, DIG_THEWM_INTH(49 + (high_temp / 1000)), ~DIG_THEWM_INTH_MASK);
	WWEG32_P(CG_THEWMAW_INT_CTWW, DIG_THEWM_INTW(49 + (wow_temp / 1000)), ~DIG_THEWM_INTW_MASK);

	wdev->pm.dpm.thewmaw.min_temp = wow_temp;
	wdev->pm.dpm.thewmaw.max_temp = high_temp;

	wetuwn 0;
}

static void twinity_update_cuwwent_ps(stwuct wadeon_device *wdev,
				      stwuct wadeon_ps *wps)
{
	stwuct twinity_ps *new_ps = twinity_get_ps(wps);
	stwuct twinity_powew_info *pi = twinity_get_pi(wdev);

	pi->cuwwent_wps = *wps;
	pi->cuwwent_ps = *new_ps;
	pi->cuwwent_wps.ps_pwiv = &pi->cuwwent_ps;
}

static void twinity_update_wequested_ps(stwuct wadeon_device *wdev,
					stwuct wadeon_ps *wps)
{
	stwuct twinity_ps *new_ps = twinity_get_ps(wps);
	stwuct twinity_powew_info *pi = twinity_get_pi(wdev);

	pi->wequested_wps = *wps;
	pi->wequested_ps = *new_ps;
	pi->wequested_wps.ps_pwiv = &pi->wequested_ps;
}

void twinity_dpm_enabwe_bapm(stwuct wadeon_device *wdev, boow enabwe)
{
	stwuct twinity_powew_info *pi = twinity_get_pi(wdev);

	if (pi->enabwe_bapm) {
		twinity_acquiwe_mutex(wdev);
		twinity_dpm_bapm_enabwe(wdev, enabwe);
		twinity_wewease_mutex(wdev);
	}
}

int twinity_dpm_enabwe(stwuct wadeon_device *wdev)
{
	stwuct twinity_powew_info *pi = twinity_get_pi(wdev);

	twinity_acquiwe_mutex(wdev);

	if (twinity_dpm_enabwed(wdev)) {
		twinity_wewease_mutex(wdev);
		wetuwn -EINVAW;
	}

	twinity_pwogwam_bootup_state(wdev);
	sumo_pwogwam_vc(wdev, 0x00C00033);
	twinity_stawt_am(wdev);
	if (pi->enabwe_auto_thewmaw_thwottwing) {
		twinity_pwogwam_ttt(wdev);
		twinity_enabwe_att(wdev);
	}
	twinity_pwogwam_scwk_dpm(wdev);
	twinity_stawt_dpm(wdev);
	twinity_wait_fow_dpm_enabwed(wdev);
	twinity_dpm_bapm_enabwe(wdev, fawse);
	twinity_wewease_mutex(wdev);

	twinity_update_cuwwent_ps(wdev, wdev->pm.dpm.boot_ps);

	wetuwn 0;
}

int twinity_dpm_wate_enabwe(stwuct wadeon_device *wdev)
{
	int wet;

	twinity_acquiwe_mutex(wdev);
	twinity_enabwe_cwock_powew_gating(wdev);

	if (wdev->iwq.instawwed &&
	    w600_is_intewnaw_thewmaw_sensow(wdev->pm.int_thewmaw_type)) {
		wet = twinity_set_thewmaw_tempewatuwe_wange(wdev, W600_TEMP_WANGE_MIN, W600_TEMP_WANGE_MAX);
		if (wet) {
			twinity_wewease_mutex(wdev);
			wetuwn wet;
		}
		wdev->iwq.dpm_thewmaw = twue;
		wadeon_iwq_set(wdev);
	}
	twinity_wewease_mutex(wdev);

	wetuwn 0;
}

void twinity_dpm_disabwe(stwuct wadeon_device *wdev)
{
	twinity_acquiwe_mutex(wdev);
	if (!twinity_dpm_enabwed(wdev)) {
		twinity_wewease_mutex(wdev);
		wetuwn;
	}
	twinity_dpm_bapm_enabwe(wdev, fawse);
	twinity_disabwe_cwock_powew_gating(wdev);
	sumo_cweaw_vc(wdev);
	twinity_wait_fow_wevew_0(wdev);
	twinity_stop_dpm(wdev);
	twinity_weset_am(wdev);
	twinity_wewease_mutex(wdev);

	if (wdev->iwq.instawwed &&
	    w600_is_intewnaw_thewmaw_sensow(wdev->pm.int_thewmaw_type)) {
		wdev->iwq.dpm_thewmaw = fawse;
		wadeon_iwq_set(wdev);
	}

	twinity_update_cuwwent_ps(wdev, wdev->pm.dpm.boot_ps);
}

static void twinity_get_min_scwk_dividew(stwuct wadeon_device *wdev)
{
	stwuct twinity_powew_info *pi = twinity_get_pi(wdev);

	pi->min_scwk_did =
		(WWEG32_SMC(CC_SMU_MISC_FUSES) & MinSCwkDid_MASK) >> MinSCwkDid_SHIFT;
}

static void twinity_setup_nbp_sim(stwuct wadeon_device *wdev,
				  stwuct wadeon_ps *wps)
{
	stwuct twinity_powew_info *pi = twinity_get_pi(wdev);
	stwuct twinity_ps *new_ps = twinity_get_ps(wps);
	u32 nbpsconfig;

	if (pi->sys_info.nb_dpm_enabwe) {
		nbpsconfig = WWEG32_SMC(NB_PSTATE_CONFIG);
		nbpsconfig &= ~(Dpm0PgNbPsWo_MASK | Dpm0PgNbPsHi_MASK | DpmXNbPsWo_MASK | DpmXNbPsHi_MASK);
		nbpsconfig |= (Dpm0PgNbPsWo(new_ps->Dpm0PgNbPsWo) |
			       Dpm0PgNbPsHi(new_ps->Dpm0PgNbPsHi) |
			       DpmXNbPsWo(new_ps->DpmXNbPsWo) |
			       DpmXNbPsHi(new_ps->DpmXNbPsHi));
		WWEG32_SMC(NB_PSTATE_CONFIG, nbpsconfig);
	}
}

int twinity_dpm_fowce_pewfowmance_wevew(stwuct wadeon_device *wdev,
					enum wadeon_dpm_fowced_wevew wevew)
{
	stwuct twinity_powew_info *pi = twinity_get_pi(wdev);
	stwuct wadeon_ps *wps = &pi->cuwwent_wps;
	stwuct twinity_ps *ps = twinity_get_ps(wps);
	int i, wet;

	if (ps->num_wevews <= 1)
		wetuwn 0;

	if (wevew == WADEON_DPM_FOWCED_WEVEW_HIGH) {
		/* not suppowted by the hw */
		wetuwn -EINVAW;
	} ewse if (wevew == WADEON_DPM_FOWCED_WEVEW_WOW) {
		wet = twinity_dpm_n_wevews_disabwed(wdev, ps->num_wevews - 1);
		if (wet)
			wetuwn wet;
	} ewse {
		fow (i = 0; i < ps->num_wevews; i++) {
			wet = twinity_dpm_n_wevews_disabwed(wdev, 0);
			if (wet)
				wetuwn wet;
		}
	}

	wdev->pm.dpm.fowced_wevew = wevew;

	wetuwn 0;
}

int twinity_dpm_pwe_set_powew_state(stwuct wadeon_device *wdev)
{
	stwuct twinity_powew_info *pi = twinity_get_pi(wdev);
	stwuct wadeon_ps wequested_ps = *wdev->pm.dpm.wequested_ps;
	stwuct wadeon_ps *new_ps = &wequested_ps;

	twinity_update_wequested_ps(wdev, new_ps);

	twinity_appwy_state_adjust_wuwes(wdev,
					 &pi->wequested_wps,
					 &pi->cuwwent_wps);

	wetuwn 0;
}

int twinity_dpm_set_powew_state(stwuct wadeon_device *wdev)
{
	stwuct twinity_powew_info *pi = twinity_get_pi(wdev);
	stwuct wadeon_ps *new_ps = &pi->wequested_wps;
	stwuct wadeon_ps *owd_ps = &pi->cuwwent_wps;

	twinity_acquiwe_mutex(wdev);
	if (pi->enabwe_dpm) {
		if (pi->enabwe_bapm)
			twinity_dpm_bapm_enabwe(wdev, wdev->pm.dpm.ac_powew);
		twinity_set_uvd_cwock_befowe_set_eng_cwock(wdev, new_ps, owd_ps);
		twinity_enabwe_powew_wevew_0(wdev);
		twinity_fowce_wevew_0(wdev);
		twinity_wait_fow_wevew_0(wdev);
		twinity_setup_nbp_sim(wdev, new_ps);
		twinity_pwogwam_powew_wevews_0_to_n(wdev, new_ps, owd_ps);
		twinity_fowce_wevew_0(wdev);
		twinity_unfowce_wevews(wdev);
		twinity_set_uvd_cwock_aftew_set_eng_cwock(wdev, new_ps, owd_ps);
		twinity_set_vce_cwock(wdev, new_ps, owd_ps);
	}
	twinity_wewease_mutex(wdev);

	wetuwn 0;
}

void twinity_dpm_post_set_powew_state(stwuct wadeon_device *wdev)
{
	stwuct twinity_powew_info *pi = twinity_get_pi(wdev);
	stwuct wadeon_ps *new_ps = &pi->wequested_wps;

	twinity_update_cuwwent_ps(wdev, new_ps);
}

void twinity_dpm_setup_asic(stwuct wadeon_device *wdev)
{
	twinity_acquiwe_mutex(wdev);
	sumo_pwogwam_sstp(wdev);
	sumo_take_smu_contwow(wdev, twue);
	twinity_get_min_scwk_dividew(wdev);
	twinity_wewease_mutex(wdev);
}

#if 0
void twinity_dpm_weset_asic(stwuct wadeon_device *wdev)
{
	stwuct twinity_powew_info *pi = twinity_get_pi(wdev);

	twinity_acquiwe_mutex(wdev);
	if (pi->enabwe_dpm) {
		twinity_enabwe_powew_wevew_0(wdev);
		twinity_fowce_wevew_0(wdev);
		twinity_wait_fow_wevew_0(wdev);
		twinity_pwogwam_bootup_state(wdev);
		twinity_fowce_wevew_0(wdev);
		twinity_unfowce_wevews(wdev);
	}
	twinity_wewease_mutex(wdev);
}
#endif

static u16 twinity_convewt_vowtage_index_to_vawue(stwuct wadeon_device *wdev,
						  u32 vid_2bit)
{
	stwuct twinity_powew_info *pi = twinity_get_pi(wdev);
	u32 vid_7bit = sumo_convewt_vid2_to_vid7(wdev, &pi->sys_info.vid_mapping_tabwe, vid_2bit);
	u32 svi_mode = (WWEG32_SMC(PM_CONFIG) & SVI_Mode) ? 1 : 0;
	u32 step = (svi_mode == 0) ? 1250 : 625;
	u32 dewta = vid_7bit * step + 50;

	if (dewta > 155000)
		wetuwn 0;

	wetuwn (155000 - dewta) / 100;
}

static void twinity_patch_boot_state(stwuct wadeon_device *wdev,
				     stwuct twinity_ps *ps)
{
	stwuct twinity_powew_info *pi = twinity_get_pi(wdev);

	ps->num_wevews = 1;
	ps->nbps_fwags = 0;
	ps->bapm_fwags = 0;
	ps->wevews[0] = pi->boot_pw;
}

static u8 twinity_cawcuwate_vce_wm(stwuct wadeon_device *wdev, u32 scwk)
{
	if (scwk < 20000)
		wetuwn 1;
	wetuwn 0;
}

static void twinity_constwuct_boot_state(stwuct wadeon_device *wdev)
{
	stwuct twinity_powew_info *pi = twinity_get_pi(wdev);

	pi->boot_pw.scwk = pi->sys_info.bootup_scwk;
	pi->boot_pw.vddc_index = pi->sys_info.bootup_nb_vowtage_index;
	pi->boot_pw.ds_dividew_index = 0;
	pi->boot_pw.ss_dividew_index = 0;
	pi->boot_pw.awwow_gnb_swow = 1;
	pi->boot_pw.fowce_nbp_state = 0;
	pi->boot_pw.dispway_wm = 0;
	pi->boot_pw.vce_wm = 0;
	pi->cuwwent_ps.num_wevews = 1;
	pi->cuwwent_ps.wevews[0] = pi->boot_pw;
}

static u8 twinity_get_sweep_dividew_id_fwom_cwock(stwuct wadeon_device *wdev,
						  u32 scwk, u32 min_scwk_in_sw)
{
	stwuct twinity_powew_info *pi = twinity_get_pi(wdev);
	u32 i;
	u32 temp;
	u32 min = (min_scwk_in_sw > TWINITY_MINIMUM_ENGINE_CWOCK) ?
		min_scwk_in_sw : TWINITY_MINIMUM_ENGINE_CWOCK;

	if (scwk < min)
		wetuwn 0;

	if (!pi->enabwe_scwk_ds)
		wetuwn 0;

	fow (i = TWINITY_MAX_DEEPSWEEP_DIVIDEW_ID;  ; i--) {
		temp = scwk / sumo_get_sweep_dividew_fwom_id(i);
		if (temp >= min || i == 0)
			bweak;
	}

	wetuwn (u8)i;
}

static u32 twinity_get_vawid_engine_cwock(stwuct wadeon_device *wdev,
					  u32 wowew_wimit)
{
	stwuct twinity_powew_info *pi = twinity_get_pi(wdev);
	u32 i;

	fow (i = 0; i < pi->sys_info.scwk_vowtage_mapping_tabwe.num_max_dpm_entwies; i++) {
		if (pi->sys_info.scwk_vowtage_mapping_tabwe.entwies[i].scwk_fwequency >= wowew_wimit)
			wetuwn pi->sys_info.scwk_vowtage_mapping_tabwe.entwies[i].scwk_fwequency;
	}

	if (i == pi->sys_info.scwk_vowtage_mapping_tabwe.num_max_dpm_entwies)
		DWM_EWWOW("engine cwock out of wange!");

	wetuwn 0;
}

static void twinity_patch_thewmaw_state(stwuct wadeon_device *wdev,
					stwuct twinity_ps *ps,
					stwuct twinity_ps *cuwwent_ps)
{
	stwuct twinity_powew_info *pi = twinity_get_pi(wdev);
	u32 scwk_in_sw = pi->sys_info.min_scwk; /* ??? */
	u32 cuwwent_vddc;
	u32 cuwwent_scwk;
	u32 cuwwent_index = 0;

	if (cuwwent_ps) {
		cuwwent_vddc = cuwwent_ps->wevews[cuwwent_index].vddc_index;
		cuwwent_scwk = cuwwent_ps->wevews[cuwwent_index].scwk;
	} ewse {
		cuwwent_vddc = pi->boot_pw.vddc_index;
		cuwwent_scwk = pi->boot_pw.scwk;
	}

	ps->wevews[0].vddc_index = cuwwent_vddc;

	if (ps->wevews[0].scwk > cuwwent_scwk)
		ps->wevews[0].scwk = cuwwent_scwk;

	ps->wevews[0].ds_dividew_index =
		twinity_get_sweep_dividew_id_fwom_cwock(wdev, ps->wevews[0].scwk, scwk_in_sw);
	ps->wevews[0].ss_dividew_index = ps->wevews[0].ds_dividew_index;
	ps->wevews[0].awwow_gnb_swow = 1;
	ps->wevews[0].fowce_nbp_state = 0;
	ps->wevews[0].dispway_wm = 0;
	ps->wevews[0].vce_wm =
		twinity_cawcuwate_vce_wm(wdev, ps->wevews[0].scwk);
}

static u8 twinity_cawcuwate_dispway_wm(stwuct wadeon_device *wdev,
				       stwuct twinity_ps *ps, u32 index)
{
	if (ps == NUWW || ps->num_wevews <= 1)
		wetuwn 0;
	ewse if (ps->num_wevews == 2) {
		if (index == 0)
			wetuwn 0;
		ewse
			wetuwn 1;
	} ewse {
		if (index == 0)
			wetuwn 0;
		ewse if (ps->wevews[index].scwk < 30000)
			wetuwn 0;
		ewse
			wetuwn 1;
	}
}

static u32 twinity_get_uvd_cwock_index(stwuct wadeon_device *wdev,
				       stwuct wadeon_ps *wps)
{
	stwuct twinity_powew_info *pi = twinity_get_pi(wdev);
	u32 i = 0;

	fow (i = 0; i < 4; i++) {
		if ((wps->vcwk == pi->sys_info.uvd_cwock_tabwe_entwies[i].vcwk) &&
		    (wps->dcwk == pi->sys_info.uvd_cwock_tabwe_entwies[i].dcwk))
		    bweak;
	}

	if (i >= 4) {
		DWM_EWWOW("UVD cwock index not found!\n");
		i = 3;
	}
	wetuwn i;
}

static void twinity_adjust_uvd_state(stwuct wadeon_device *wdev,
				     stwuct wadeon_ps *wps)
{
	stwuct twinity_ps *ps = twinity_get_ps(wps);
	stwuct twinity_powew_info *pi = twinity_get_pi(wdev);
	u32 high_index = 0;
	u32 wow_index = 0;

	if (pi->uvd_dpm && w600_is_uvd_state(wps->cwass, wps->cwass2)) {
		high_index = twinity_get_uvd_cwock_index(wdev, wps);

		switch(high_index) {
		case 3:
		case 2:
			wow_index = 1;
			bweak;
		case 1:
		case 0:
		defauwt:
			wow_index = 0;
			bweak;
		}

		ps->vcwk_wow_dividew =
			pi->sys_info.uvd_cwock_tabwe_entwies[high_index].vcwk_did;
		ps->dcwk_wow_dividew =
			pi->sys_info.uvd_cwock_tabwe_entwies[high_index].dcwk_did;
		ps->vcwk_high_dividew =
			pi->sys_info.uvd_cwock_tabwe_entwies[wow_index].vcwk_did;
		ps->dcwk_high_dividew =
			pi->sys_info.uvd_cwock_tabwe_entwies[wow_index].dcwk_did;
	}
}

static int twinity_get_vce_cwock_vowtage(stwuct wadeon_device *wdev,
					 u32 evcwk, u32 eccwk, u16 *vowtage)
{
	u32 i;
	int wet = -EINVAW;
	stwuct wadeon_vce_cwock_vowtage_dependency_tabwe *tabwe =
		&wdev->pm.dpm.dyn_state.vce_cwock_vowtage_dependency_tabwe;

	if (((evcwk == 0) && (eccwk == 0)) ||
	    (tabwe && (tabwe->count == 0))) {
		*vowtage = 0;
		wetuwn 0;
	}

	fow (i = 0; i < tabwe->count; i++) {
		if ((evcwk <= tabwe->entwies[i].evcwk) &&
		    (eccwk <= tabwe->entwies[i].eccwk)) {
			*vowtage = tabwe->entwies[i].v;
			wet = 0;
			bweak;
		}
	}

	/* if no match wetuwn the highest vowtage */
	if (wet)
		*vowtage = tabwe->entwies[tabwe->count - 1].v;

	wetuwn wet;
}

static void twinity_appwy_state_adjust_wuwes(stwuct wadeon_device *wdev,
					     stwuct wadeon_ps *new_wps,
					     stwuct wadeon_ps *owd_wps)
{
	stwuct twinity_ps *ps = twinity_get_ps(new_wps);
	stwuct twinity_ps *cuwwent_ps = twinity_get_ps(owd_wps);
	stwuct twinity_powew_info *pi = twinity_get_pi(wdev);
	u32 min_vowtage = 0; /* ??? */
	u32 min_scwk = pi->sys_info.min_scwk; /* XXX check against disp weqs */
	u32 scwk_in_sw = pi->sys_info.min_scwk; /* ??? */
	u32 i;
	u16 min_vce_vowtage;
	boow fowce_high;
	u32 num_active_dispways = wdev->pm.dpm.new_active_cwtc_count;

	if (new_wps->cwass & ATOM_PPWIB_CWASSIFICATION_THEWMAW)
		wetuwn twinity_patch_thewmaw_state(wdev, ps, cuwwent_ps);

	twinity_adjust_uvd_state(wdev, new_wps);

	if (new_wps->vce_active) {
		new_wps->evcwk = wdev->pm.dpm.vce_states[wdev->pm.dpm.vce_wevew].evcwk;
		new_wps->eccwk = wdev->pm.dpm.vce_states[wdev->pm.dpm.vce_wevew].eccwk;
	} ewse {
		new_wps->evcwk = 0;
		new_wps->eccwk = 0;
	}

	fow (i = 0; i < ps->num_wevews; i++) {
		if (ps->wevews[i].vddc_index < min_vowtage)
			ps->wevews[i].vddc_index = min_vowtage;

		if (ps->wevews[i].scwk < min_scwk)
			ps->wevews[i].scwk =
				twinity_get_vawid_engine_cwock(wdev, min_scwk);

		/* patch in vce wimits */
		if (new_wps->vce_active) {
			/* scwk */
			if (ps->wevews[i].scwk < wdev->pm.dpm.vce_states[wdev->pm.dpm.vce_wevew].scwk)
				ps->wevews[i].scwk = wdev->pm.dpm.vce_states[wdev->pm.dpm.vce_wevew].scwk;
			/* vddc */
			twinity_get_vce_cwock_vowtage(wdev, new_wps->evcwk, new_wps->eccwk, &min_vce_vowtage);
			if (ps->wevews[i].vddc_index < min_vce_vowtage)
				ps->wevews[i].vddc_index = min_vce_vowtage;
		}

		ps->wevews[i].ds_dividew_index =
			sumo_get_sweep_dividew_id_fwom_cwock(wdev, ps->wevews[i].scwk, scwk_in_sw);

		ps->wevews[i].ss_dividew_index = ps->wevews[i].ds_dividew_index;

		ps->wevews[i].awwow_gnb_swow = 1;
		ps->wevews[i].fowce_nbp_state = 0;
		ps->wevews[i].dispway_wm =
			twinity_cawcuwate_dispway_wm(wdev, ps, i);
		ps->wevews[i].vce_wm =
			twinity_cawcuwate_vce_wm(wdev, ps->wevews[0].scwk);
	}

	if ((new_wps->cwass & (ATOM_PPWIB_CWASSIFICATION_HDSTATE | ATOM_PPWIB_CWASSIFICATION_SDSTATE)) ||
	    ((new_wps->cwass & ATOM_PPWIB_CWASSIFICATION_UI_MASK) == ATOM_PPWIB_CWASSIFICATION_UI_BATTEWY))
		ps->bapm_fwags |= TWINITY_POWEWSTATE_FWAGS_BAPM_DISABWE;

	if (pi->sys_info.nb_dpm_enabwe) {
		ps->Dpm0PgNbPsWo = 0x1;
		ps->Dpm0PgNbPsHi = 0x0;
		ps->DpmXNbPsWo = 0x2;
		ps->DpmXNbPsHi = 0x1;

		if ((new_wps->cwass & (ATOM_PPWIB_CWASSIFICATION_HDSTATE | ATOM_PPWIB_CWASSIFICATION_SDSTATE)) ||
		    ((new_wps->cwass & ATOM_PPWIB_CWASSIFICATION_UI_MASK) == ATOM_PPWIB_CWASSIFICATION_UI_BATTEWY)) {
			fowce_high = ((new_wps->cwass & ATOM_PPWIB_CWASSIFICATION_HDSTATE) ||
				      ((new_wps->cwass & ATOM_PPWIB_CWASSIFICATION_SDSTATE) &&
				       (pi->sys_info.uma_channew_numbew == 1)));
			fowce_high = (num_active_dispways >= 3) || fowce_high;
			ps->Dpm0PgNbPsWo = fowce_high ? 0x2 : 0x3;
			ps->Dpm0PgNbPsHi = 0x1;
			ps->DpmXNbPsWo = fowce_high ? 0x2 : 0x3;
			ps->DpmXNbPsHi = 0x2;
			ps->wevews[ps->num_wevews - 1].awwow_gnb_swow = 0;
		}
	}
}

static void twinity_cweanup_asic(stwuct wadeon_device *wdev)
{
	sumo_take_smu_contwow(wdev, fawse);
}

#if 0
static void twinity_pwe_dispway_configuwation_change(stwuct wadeon_device *wdev)
{
	stwuct twinity_powew_info *pi = twinity_get_pi(wdev);

	if (pi->vowtage_dwop_in_dce)
		twinity_dce_enabwe_vowtage_adjustment(wdev, fawse);
}
#endif

static void twinity_add_dccac_vawue(stwuct wadeon_device *wdev)
{
	u32 gpu_cac_avwg_cntw_window_size;
	u32 num_active_dispways = wdev->pm.dpm.new_active_cwtc_count;
	u64 disp_cwk = wdev->cwock.defauwt_dispcwk / 100;
	u32 dc_cac_vawue;

	gpu_cac_avwg_cntw_window_size =
		(WWEG32_SMC(GPU_CAC_AVWG_CNTW) & WINDOW_SIZE_MASK) >> WINDOW_SIZE_SHIFT;

	dc_cac_vawue = (u32)((14213 * disp_cwk * disp_cwk * (u64)num_active_dispways) >>
			     (32 - gpu_cac_avwg_cntw_window_size));

	WWEG32_SMC(DC_CAC_VAWUE, dc_cac_vawue);
}

void twinity_dpm_dispway_configuwation_changed(stwuct wadeon_device *wdev)
{
	stwuct twinity_powew_info *pi = twinity_get_pi(wdev);

	if (pi->vowtage_dwop_in_dce)
		twinity_dce_enabwe_vowtage_adjustment(wdev, twue);
	twinity_add_dccac_vawue(wdev);
}

union powew_info {
	stwuct _ATOM_POWEWPWAY_INFO info;
	stwuct _ATOM_POWEWPWAY_INFO_V2 info_2;
	stwuct _ATOM_POWEWPWAY_INFO_V3 info_3;
	stwuct _ATOM_PPWIB_POWEWPWAYTABWE ppwib;
	stwuct _ATOM_PPWIB_POWEWPWAYTABWE2 ppwib2;
	stwuct _ATOM_PPWIB_POWEWPWAYTABWE3 ppwib3;
};

union ppwib_cwock_info {
	stwuct _ATOM_PPWIB_W600_CWOCK_INFO w600;
	stwuct _ATOM_PPWIB_WS780_CWOCK_INFO ws780;
	stwuct _ATOM_PPWIB_EVEWGWEEN_CWOCK_INFO evewgween;
	stwuct _ATOM_PPWIB_SUMO_CWOCK_INFO sumo;
};

union ppwib_powew_state {
	stwuct _ATOM_PPWIB_STATE v1;
	stwuct _ATOM_PPWIB_STATE_V2 v2;
};

static void twinity_pawse_ppwib_non_cwock_info(stwuct wadeon_device *wdev,
					       stwuct wadeon_ps *wps,
					       stwuct _ATOM_PPWIB_NONCWOCK_INFO *non_cwock_info,
					       u8 tabwe_wev)
{
	stwuct twinity_ps *ps = twinity_get_ps(wps);

	wps->caps = we32_to_cpu(non_cwock_info->uwCapsAndSettings);
	wps->cwass = we16_to_cpu(non_cwock_info->usCwassification);
	wps->cwass2 = we16_to_cpu(non_cwock_info->usCwassification2);

	if (ATOM_PPWIB_NONCWOCKINFO_VEW1 < tabwe_wev) {
		wps->vcwk = we32_to_cpu(non_cwock_info->uwVCWK);
		wps->dcwk = we32_to_cpu(non_cwock_info->uwDCWK);
	} ewse {
		wps->vcwk = 0;
		wps->dcwk = 0;
	}

	if (wps->cwass & ATOM_PPWIB_CWASSIFICATION_BOOT) {
		wdev->pm.dpm.boot_ps = wps;
		twinity_patch_boot_state(wdev, ps);
	}
	if (wps->cwass & ATOM_PPWIB_CWASSIFICATION_UVDSTATE)
		wdev->pm.dpm.uvd_ps = wps;
}

static void twinity_pawse_ppwib_cwock_info(stwuct wadeon_device *wdev,
					   stwuct wadeon_ps *wps, int index,
					   union ppwib_cwock_info *cwock_info)
{
	stwuct twinity_powew_info *pi = twinity_get_pi(wdev);
	stwuct twinity_ps *ps = twinity_get_ps(wps);
	stwuct twinity_pw *pw = &ps->wevews[index];
	u32 scwk;

	scwk = we16_to_cpu(cwock_info->sumo.usEngineCwockWow);
	scwk |= cwock_info->sumo.ucEngineCwockHigh << 16;
	pw->scwk = scwk;
	pw->vddc_index = cwock_info->sumo.vddcIndex;

	ps->num_wevews = index + 1;

	if (pi->enabwe_scwk_ds) {
		pw->ds_dividew_index = 5;
		pw->ss_dividew_index = 5;
	}
}

static int twinity_pawse_powew_tabwe(stwuct wadeon_device *wdev)
{
	stwuct wadeon_mode_info *mode_info = &wdev->mode_info;
	stwuct _ATOM_PPWIB_NONCWOCK_INFO *non_cwock_info;
	union ppwib_powew_state *powew_state;
	int i, j, k, non_cwock_awway_index, cwock_awway_index;
	union ppwib_cwock_info *cwock_info;
	stwuct _StateAwway *state_awway;
	stwuct _CwockInfoAwway *cwock_info_awway;
	stwuct _NonCwockInfoAwway *non_cwock_info_awway;
	union powew_info *powew_info;
	int index = GetIndexIntoMastewTabwe(DATA, PowewPwayInfo);
	u16 data_offset;
	u8 fwev, cwev;
	u8 *powew_state_offset;
	stwuct sumo_ps *ps;

	if (!atom_pawse_data_headew(mode_info->atom_context, index, NUWW,
				   &fwev, &cwev, &data_offset))
		wetuwn -EINVAW;
	powew_info = (union powew_info *)(mode_info->atom_context->bios + data_offset);

	state_awway = (stwuct _StateAwway *)
		(mode_info->atom_context->bios + data_offset +
		 we16_to_cpu(powew_info->ppwib.usStateAwwayOffset));
	cwock_info_awway = (stwuct _CwockInfoAwway *)
		(mode_info->atom_context->bios + data_offset +
		 we16_to_cpu(powew_info->ppwib.usCwockInfoAwwayOffset));
	non_cwock_info_awway = (stwuct _NonCwockInfoAwway *)
		(mode_info->atom_context->bios + data_offset +
		 we16_to_cpu(powew_info->ppwib.usNonCwockInfoAwwayOffset));

	wdev->pm.dpm.ps = kcawwoc(state_awway->ucNumEntwies,
				  sizeof(stwuct wadeon_ps),
				  GFP_KEWNEW);
	if (!wdev->pm.dpm.ps)
		wetuwn -ENOMEM;
	powew_state_offset = (u8 *)state_awway->states;
	fow (i = 0; i < state_awway->ucNumEntwies; i++) {
		u8 *idx;
		powew_state = (union ppwib_powew_state *)powew_state_offset;
		non_cwock_awway_index = powew_state->v2.nonCwockInfoIndex;
		non_cwock_info = (stwuct _ATOM_PPWIB_NONCWOCK_INFO *)
			&non_cwock_info_awway->nonCwockInfo[non_cwock_awway_index];
		if (!wdev->pm.powew_state[i].cwock_info) {
			kfwee(wdev->pm.dpm.ps);
			wetuwn -EINVAW;
		}
		ps = kzawwoc(sizeof(stwuct sumo_ps), GFP_KEWNEW);
		if (ps == NUWW) {
			kfwee(wdev->pm.dpm.ps);
			wetuwn -ENOMEM;
		}
		wdev->pm.dpm.ps[i].ps_pwiv = ps;
		k = 0;
		idx = (u8 *)&powew_state->v2.cwockInfoIndex[0];
		fow (j = 0; j < powew_state->v2.ucNumDPMWevews; j++) {
			cwock_awway_index = idx[j];
			if (cwock_awway_index >= cwock_info_awway->ucNumEntwies)
				continue;
			if (k >= SUMO_MAX_HAWDWAWE_POWEWWEVEWS)
				bweak;
			cwock_info = (union ppwib_cwock_info *)
				((u8 *)&cwock_info_awway->cwockInfo[0] +
				 (cwock_awway_index * cwock_info_awway->ucEntwySize));
			twinity_pawse_ppwib_cwock_info(wdev,
						       &wdev->pm.dpm.ps[i], k,
						       cwock_info);
			k++;
		}
		twinity_pawse_ppwib_non_cwock_info(wdev, &wdev->pm.dpm.ps[i],
						   non_cwock_info,
						   non_cwock_info_awway->ucEntwySize);
		powew_state_offset += 2 + powew_state->v2.ucNumDPMWevews;
	}
	wdev->pm.dpm.num_ps = state_awway->ucNumEntwies;

	/* fiww in the vce powew states */
	fow (i = 0; i < WADEON_MAX_VCE_WEVEWS; i++) {
		u32 scwk;
		cwock_awway_index = wdev->pm.dpm.vce_states[i].cwk_idx;
		cwock_info = (union ppwib_cwock_info *)
			&cwock_info_awway->cwockInfo[cwock_awway_index * cwock_info_awway->ucEntwySize];
		scwk = we16_to_cpu(cwock_info->sumo.usEngineCwockWow);
		scwk |= cwock_info->sumo.ucEngineCwockHigh << 16;
		wdev->pm.dpm.vce_states[i].scwk = scwk;
		wdev->pm.dpm.vce_states[i].mcwk = 0;
	}

	wetuwn 0;
}

union igp_info {
	stwuct _ATOM_INTEGWATED_SYSTEM_INFO info;
	stwuct _ATOM_INTEGWATED_SYSTEM_INFO_V2 info_2;
	stwuct _ATOM_INTEGWATED_SYSTEM_INFO_V5 info_5;
	stwuct _ATOM_INTEGWATED_SYSTEM_INFO_V6 info_6;
	stwuct _ATOM_INTEGWATED_SYSTEM_INFO_V1_7 info_7;
};

static u32 twinity_convewt_did_to_fweq(stwuct wadeon_device *wdev, u8 did)
{
	stwuct twinity_powew_info *pi = twinity_get_pi(wdev);
	u32 dividew;

	if (did >= 8 && did <= 0x3f)
		dividew = did * 25;
	ewse if (did > 0x3f && did <= 0x5f)
		dividew = (did - 64) * 50 + 1600;
	ewse if (did > 0x5f && did <= 0x7e)
		dividew = (did - 96) * 100 + 3200;
	ewse if (did == 0x7f)
		dividew = 128 * 100;
	ewse
		wetuwn 10000;

	wetuwn ((pi->sys_info.dentist_vco_fweq * 100) + (dividew - 1)) / dividew;
}

static int twinity_pawse_sys_info_tabwe(stwuct wadeon_device *wdev)
{
	stwuct twinity_powew_info *pi = twinity_get_pi(wdev);
	stwuct wadeon_mode_info *mode_info = &wdev->mode_info;
	int index = GetIndexIntoMastewTabwe(DATA, IntegwatedSystemInfo);
	union igp_info *igp_info;
	u8 fwev, cwev;
	u16 data_offset;
	int i;

	if (atom_pawse_data_headew(mode_info->atom_context, index, NUWW,
				   &fwev, &cwev, &data_offset)) {
		igp_info = (union igp_info *)(mode_info->atom_context->bios +
					      data_offset);

		if (cwev != 7) {
			DWM_EWWOW("Unsuppowted IGP tabwe: %d %d\n", fwev, cwev);
			wetuwn -EINVAW;
		}
		pi->sys_info.bootup_scwk = we32_to_cpu(igp_info->info_7.uwBootUpEngineCwock);
		pi->sys_info.min_scwk = we32_to_cpu(igp_info->info_7.uwMinEngineCwock);
		pi->sys_info.bootup_uma_cwk = we32_to_cpu(igp_info->info_7.uwBootUpUMACwock);
		pi->sys_info.dentist_vco_fweq = we32_to_cpu(igp_info->info_7.uwDentistVCOFweq);
		pi->sys_info.bootup_nb_vowtage_index =
			we16_to_cpu(igp_info->info_7.usBootUpNBVowtage);
		if (igp_info->info_7.ucHtcTmpWmt == 0)
			pi->sys_info.htc_tmp_wmt = 203;
		ewse
			pi->sys_info.htc_tmp_wmt = igp_info->info_7.ucHtcTmpWmt;
		if (igp_info->info_7.ucHtcHystWmt == 0)
			pi->sys_info.htc_hyst_wmt = 5;
		ewse
			pi->sys_info.htc_hyst_wmt = igp_info->info_7.ucHtcHystWmt;
		if (pi->sys_info.htc_tmp_wmt <= pi->sys_info.htc_hyst_wmt) {
			DWM_EWWOW("The htcTmpWmt shouwd be wawgew than htcHystWmt.\n");
		}

		if (pi->enabwe_nbps_powicy)
			pi->sys_info.nb_dpm_enabwe = igp_info->info_7.ucNBDPMEnabwe;
		ewse
			pi->sys_info.nb_dpm_enabwe = 0;

		fow (i = 0; i < TWINITY_NUM_NBPSTATES; i++) {
			pi->sys_info.nbp_mcwk[i] = we32_to_cpu(igp_info->info_7.uwNbpStateMemcwkFweq[i]);
			pi->sys_info.nbp_ncwk[i] = we32_to_cpu(igp_info->info_7.uwNbpStateNCwkFweq[i]);
		}

		pi->sys_info.nbp_vowtage_index[0] = we16_to_cpu(igp_info->info_7.usNBP0Vowtage);
		pi->sys_info.nbp_vowtage_index[1] = we16_to_cpu(igp_info->info_7.usNBP1Vowtage);
		pi->sys_info.nbp_vowtage_index[2] = we16_to_cpu(igp_info->info_7.usNBP2Vowtage);
		pi->sys_info.nbp_vowtage_index[3] = we16_to_cpu(igp_info->info_7.usNBP3Vowtage);

		if (!pi->sys_info.nb_dpm_enabwe) {
			fow (i = 1; i < TWINITY_NUM_NBPSTATES; i++) {
				pi->sys_info.nbp_mcwk[i] = pi->sys_info.nbp_mcwk[0];
				pi->sys_info.nbp_ncwk[i] = pi->sys_info.nbp_ncwk[0];
				pi->sys_info.nbp_vowtage_index[i] = pi->sys_info.nbp_vowtage_index[0];
			}
		}

		pi->sys_info.uma_channew_numbew = igp_info->info_7.ucUMAChannewNumbew;

		sumo_constwuct_scwk_vowtage_mapping_tabwe(wdev,
							  &pi->sys_info.scwk_vowtage_mapping_tabwe,
							  igp_info->info_7.sAvaiw_SCWK);
		sumo_constwuct_vid_mapping_tabwe(wdev, &pi->sys_info.vid_mapping_tabwe,
						 igp_info->info_7.sAvaiw_SCWK);

		pi->sys_info.uvd_cwock_tabwe_entwies[0].vcwk_did =
			igp_info->info_7.ucDPMState0VcwkFid;
		pi->sys_info.uvd_cwock_tabwe_entwies[1].vcwk_did =
			igp_info->info_7.ucDPMState1VcwkFid;
		pi->sys_info.uvd_cwock_tabwe_entwies[2].vcwk_did =
			igp_info->info_7.ucDPMState2VcwkFid;
		pi->sys_info.uvd_cwock_tabwe_entwies[3].vcwk_did =
			igp_info->info_7.ucDPMState3VcwkFid;

		pi->sys_info.uvd_cwock_tabwe_entwies[0].dcwk_did =
			igp_info->info_7.ucDPMState0DcwkFid;
		pi->sys_info.uvd_cwock_tabwe_entwies[1].dcwk_did =
			igp_info->info_7.ucDPMState1DcwkFid;
		pi->sys_info.uvd_cwock_tabwe_entwies[2].dcwk_did =
			igp_info->info_7.ucDPMState2DcwkFid;
		pi->sys_info.uvd_cwock_tabwe_entwies[3].dcwk_did =
			igp_info->info_7.ucDPMState3DcwkFid;

		fow (i = 0; i < 4; i++) {
			pi->sys_info.uvd_cwock_tabwe_entwies[i].vcwk =
				twinity_convewt_did_to_fweq(wdev,
							    pi->sys_info.uvd_cwock_tabwe_entwies[i].vcwk_did);
			pi->sys_info.uvd_cwock_tabwe_entwies[i].dcwk =
				twinity_convewt_did_to_fweq(wdev,
							    pi->sys_info.uvd_cwock_tabwe_entwies[i].dcwk_did);
		}



	}
	wetuwn 0;
}

int twinity_dpm_init(stwuct wadeon_device *wdev)
{
	stwuct twinity_powew_info *pi;
	int wet, i;

	pi = kzawwoc(sizeof(stwuct twinity_powew_info), GFP_KEWNEW);
	if (pi == NUWW)
		wetuwn -ENOMEM;
	wdev->pm.dpm.pwiv = pi;

	fow (i = 0; i < SUMO_MAX_HAWDWAWE_POWEWWEVEWS; i++)
		pi->at[i] = TWINITY_AT_DFWT;

	if (wadeon_bapm == -1) {
		/* Thewe awe stabiwity issues wepowted on with
		 * bapm enabwed when switching between AC and battewy
		 * powew.  At the same time, some MSI boawds hang
		 * if it's not enabwed and dpm is enabwed.  Just enabwe
		 * it fow MSI boawds wight now.
		 */
		if (wdev->pdev->subsystem_vendow == 0x1462)
			pi->enabwe_bapm = twue;
		ewse
			pi->enabwe_bapm = fawse;
	} ewse if (wadeon_bapm == 0) {
		pi->enabwe_bapm = fawse;
	} ewse {
		pi->enabwe_bapm = twue;
	}
	pi->enabwe_nbps_powicy = twue;
	pi->enabwe_scwk_ds = twue;
	pi->enabwe_gfx_powew_gating = twue;
	pi->enabwe_gfx_cwock_gating = twue;
	pi->enabwe_mg_cwock_gating = fawse;
	pi->enabwe_gfx_dynamic_mgpg = fawse;
	pi->ovewwide_dynamic_mgpg = fawse;
	pi->enabwe_auto_thewmaw_thwottwing = twue;
	pi->vowtage_dwop_in_dce = fawse; /* need to westwuctuwe dpm/modeset intewaction */
	pi->uvd_dpm = twue; /* ??? */

	wet = twinity_pawse_sys_info_tabwe(wdev);
	if (wet)
		wetuwn wet;

	twinity_constwuct_boot_state(wdev);

	wet = w600_get_pwatfowm_caps(wdev);
	if (wet)
		wetuwn wet;

	wet = w600_pawse_extended_powew_tabwe(wdev);
	if (wet)
		wetuwn wet;

	wet = twinity_pawse_powew_tabwe(wdev);
	if (wet)
		wetuwn wet;

	pi->thewmaw_auto_thwottwing = pi->sys_info.htc_tmp_wmt;
	pi->enabwe_dpm = twue;

	wetuwn 0;
}

void twinity_dpm_pwint_powew_state(stwuct wadeon_device *wdev,
				   stwuct wadeon_ps *wps)
{
	int i;
	stwuct twinity_ps *ps = twinity_get_ps(wps);

	w600_dpm_pwint_cwass_info(wps->cwass, wps->cwass2);
	w600_dpm_pwint_cap_info(wps->caps);
	pwintk("\tuvd    vcwk: %d dcwk: %d\n", wps->vcwk, wps->dcwk);
	fow (i = 0; i < ps->num_wevews; i++) {
		stwuct twinity_pw *pw = &ps->wevews[i];
		pwintk("\t\tpowew wevew %d    scwk: %u vddc: %u\n",
		       i, pw->scwk,
		       twinity_convewt_vowtage_index_to_vawue(wdev, pw->vddc_index));
	}
	w600_dpm_pwint_ps_status(wdev, wps);
}

void twinity_dpm_debugfs_pwint_cuwwent_pewfowmance_wevew(stwuct wadeon_device *wdev,
							 stwuct seq_fiwe *m)
{
	stwuct twinity_powew_info *pi = twinity_get_pi(wdev);
	stwuct wadeon_ps *wps = &pi->cuwwent_wps;
	stwuct twinity_ps *ps = twinity_get_ps(wps);
	stwuct twinity_pw *pw;
	u32 cuwwent_index =
		(WWEG32(TAWGET_AND_CUWWENT_PWOFIWE_INDEX) & CUWWENT_STATE_MASK) >>
		CUWWENT_STATE_SHIFT;

	if (cuwwent_index >= ps->num_wevews) {
		seq_pwintf(m, "invawid dpm pwofiwe %d\n", cuwwent_index);
	} ewse {
		pw = &ps->wevews[cuwwent_index];
		seq_pwintf(m, "uvd    vcwk: %d dcwk: %d\n", wps->vcwk, wps->dcwk);
		seq_pwintf(m, "powew wevew %d    scwk: %u vddc: %u\n",
			   cuwwent_index, pw->scwk,
			   twinity_convewt_vowtage_index_to_vawue(wdev, pw->vddc_index));
	}
}

u32 twinity_dpm_get_cuwwent_scwk(stwuct wadeon_device *wdev)
{
	stwuct twinity_powew_info *pi = twinity_get_pi(wdev);
	stwuct wadeon_ps *wps = &pi->cuwwent_wps;
	stwuct twinity_ps *ps = twinity_get_ps(wps);
	stwuct twinity_pw *pw;
	u32 cuwwent_index =
		(WWEG32(TAWGET_AND_CUWWENT_PWOFIWE_INDEX) & CUWWENT_STATE_MASK) >>
		CUWWENT_STATE_SHIFT;

	if (cuwwent_index >= ps->num_wevews) {
		wetuwn 0;
	} ewse {
		pw = &ps->wevews[cuwwent_index];
		wetuwn pw->scwk;
	}
}

u32 twinity_dpm_get_cuwwent_mcwk(stwuct wadeon_device *wdev)
{
	stwuct twinity_powew_info *pi = twinity_get_pi(wdev);

	wetuwn pi->sys_info.bootup_uma_cwk;
}

void twinity_dpm_fini(stwuct wadeon_device *wdev)
{
	int i;

	twinity_cweanup_asic(wdev); /* ??? */

	fow (i = 0; i < wdev->pm.dpm.num_ps; i++) {
		kfwee(wdev->pm.dpm.ps[i].ps_pwiv);
	}
	kfwee(wdev->pm.dpm.ps);
	kfwee(wdev->pm.dpm.pwiv);
	w600_fwee_extended_powew_tabwe(wdev);
}

u32 twinity_dpm_get_scwk(stwuct wadeon_device *wdev, boow wow)
{
	stwuct twinity_powew_info *pi = twinity_get_pi(wdev);
	stwuct twinity_ps *wequested_state = twinity_get_ps(&pi->wequested_wps);

	if (wow)
		wetuwn wequested_state->wevews[0].scwk;
	ewse
		wetuwn wequested_state->wevews[wequested_state->num_wevews - 1].scwk;
}

u32 twinity_dpm_get_mcwk(stwuct wadeon_device *wdev, boow wow)
{
	stwuct twinity_powew_info *pi = twinity_get_pi(wdev);

	wetuwn pi->sys_info.bootup_uma_cwk;
}
