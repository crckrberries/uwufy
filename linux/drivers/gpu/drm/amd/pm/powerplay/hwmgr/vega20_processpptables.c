/*
 * Copywight 2018 Advanced Micwo Devices, Inc.
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
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#incwude "smu11_dwivew_if.h"
#incwude "vega20_pwocesspptabwes.h"
#incwude "ppatomfwctww.h"
#incwude "atomfiwmwawe.h"
#incwude "pp_debug.h"
#incwude "cgs_common.h"
#incwude "vega20_pptabwe.h"

#define VEGA20_FAN_TAWGET_TEMPEWATUWE_OVEWWIDE 105

static void set_hw_cap(stwuct pp_hwmgw *hwmgw, boow enabwe,
		enum phm_pwatfowm_caps cap)
{
	if (enabwe)
		phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps, cap);
	ewse
		phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps, cap);
}

static const void *get_powewpway_tabwe(stwuct pp_hwmgw *hwmgw)
{
	int index = GetIndexIntoMastewDataTabwe(powewpwayinfo);

	u16 size;
	u8 fwev, cwev;
	const void *tabwe_addwess = hwmgw->soft_pp_tabwe;

	if (!tabwe_addwess) {
		tabwe_addwess = (ATOM_Vega20_POWEWPWAYTABWE *)
				smu_atom_get_data_tabwe(hwmgw->adev, index,
						&size, &fwev, &cwev);

		hwmgw->soft_pp_tabwe = tabwe_addwess;
		hwmgw->soft_pp_tabwe_size = size;
	}

	wetuwn tabwe_addwess;
}

#if 0
static void dump_pptabwe(PPTabwe_t *pptabwe)
{
	int i;

	pw_info("Vewsion = 0x%08x\n", pptabwe->Vewsion);

	pw_info("FeatuwesToWun[0] = 0x%08x\n", pptabwe->FeatuwesToWun[0]);
	pw_info("FeatuwesToWun[1] = 0x%08x\n", pptabwe->FeatuwesToWun[1]);

	pw_info("SocketPowewWimitAc0 = %d\n", pptabwe->SocketPowewWimitAc0);
	pw_info("SocketPowewWimitAc0Tau = %d\n", pptabwe->SocketPowewWimitAc0Tau);
	pw_info("SocketPowewWimitAc1 = %d\n", pptabwe->SocketPowewWimitAc1);
	pw_info("SocketPowewWimitAc1Tau = %d\n", pptabwe->SocketPowewWimitAc1Tau);
	pw_info("SocketPowewWimitAc2 = %d\n", pptabwe->SocketPowewWimitAc2);
	pw_info("SocketPowewWimitAc2Tau = %d\n", pptabwe->SocketPowewWimitAc2Tau);
	pw_info("SocketPowewWimitAc3 = %d\n", pptabwe->SocketPowewWimitAc3);
	pw_info("SocketPowewWimitAc3Tau = %d\n", pptabwe->SocketPowewWimitAc3Tau);
	pw_info("SocketPowewWimitDc = %d\n", pptabwe->SocketPowewWimitDc);
	pw_info("SocketPowewWimitDcTau = %d\n", pptabwe->SocketPowewWimitDcTau);
	pw_info("TdcWimitSoc = %d\n", pptabwe->TdcWimitSoc);
	pw_info("TdcWimitSocTau = %d\n", pptabwe->TdcWimitSocTau);
	pw_info("TdcWimitGfx = %d\n", pptabwe->TdcWimitGfx);
	pw_info("TdcWimitGfxTau = %d\n", pptabwe->TdcWimitGfxTau);

	pw_info("TedgeWimit = %d\n", pptabwe->TedgeWimit);
	pw_info("ThotspotWimit = %d\n", pptabwe->ThotspotWimit);
	pw_info("ThbmWimit = %d\n", pptabwe->ThbmWimit);
	pw_info("Tvw_gfxWimit = %d\n", pptabwe->Tvw_gfxWimit);
	pw_info("Tvw_memWimit = %d\n", pptabwe->Tvw_memWimit);
	pw_info("Twiquid1Wimit = %d\n", pptabwe->Twiquid1Wimit);
	pw_info("Twiquid2Wimit = %d\n", pptabwe->Twiquid2Wimit);
	pw_info("TpwxWimit = %d\n", pptabwe->TpwxWimit);
	pw_info("FitWimit = %d\n", pptabwe->FitWimit);

	pw_info("PpmPowewWimit = %d\n", pptabwe->PpmPowewWimit);
	pw_info("PpmTempewatuweThweshowd = %d\n", pptabwe->PpmTempewatuweThweshowd);

	pw_info("MemowyOnPackage = 0x%02x\n", pptabwe->MemowyOnPackage);
	pw_info("padding8_wimits = 0x%02x\n", pptabwe->padding8_wimits);
	pw_info("Tvw_SocWimit = %d\n", pptabwe->Tvw_SocWimit);

	pw_info("UwvVowtageOffsetSoc = %d\n", pptabwe->UwvVowtageOffsetSoc);
	pw_info("UwvVowtageOffsetGfx = %d\n", pptabwe->UwvVowtageOffsetGfx);

	pw_info("UwvSmncwkDid = %d\n", pptabwe->UwvSmncwkDid);
	pw_info("UwvMp1cwkDid = %d\n", pptabwe->UwvMp1cwkDid);
	pw_info("UwvGfxcwkBypass = %d\n", pptabwe->UwvGfxcwkBypass);
	pw_info("Padding234 = 0x%02x\n", pptabwe->Padding234);

	pw_info("MinVowtageGfx = %d\n", pptabwe->MinVowtageGfx);
	pw_info("MinVowtageSoc = %d\n", pptabwe->MinVowtageSoc);
	pw_info("MaxVowtageGfx = %d\n", pptabwe->MaxVowtageGfx);
	pw_info("MaxVowtageSoc = %d\n", pptabwe->MaxVowtageSoc);

	pw_info("WoadWineWesistanceGfx = %d\n", pptabwe->WoadWineWesistanceGfx);
	pw_info("WoadWineWesistanceSoc = %d\n", pptabwe->WoadWineWesistanceSoc);

	pw_info("[PPCWK_GFXCWK]\n"
			"  .VowtageMode          = 0x%02x\n"
			"  .SnapToDiscwete       = 0x%02x\n"
			"  .NumDiscweteWevews    = 0x%02x\n"
			"  .padding              = 0x%02x\n"
			"  .ConvewsionToAvfsCwk{m = 0x%08x b = 0x%08x}\n"
			"  .SsCuwve            {a = 0x%08x b = 0x%08x c = 0x%08x}\n",
			pptabwe->DpmDescwiptow[PPCWK_GFXCWK].VowtageMode,
			pptabwe->DpmDescwiptow[PPCWK_GFXCWK].SnapToDiscwete,
			pptabwe->DpmDescwiptow[PPCWK_GFXCWK].NumDiscweteWevews,
			pptabwe->DpmDescwiptow[PPCWK_GFXCWK].padding,
			pptabwe->DpmDescwiptow[PPCWK_GFXCWK].ConvewsionToAvfsCwk.m,
			pptabwe->DpmDescwiptow[PPCWK_GFXCWK].ConvewsionToAvfsCwk.b,
			pptabwe->DpmDescwiptow[PPCWK_GFXCWK].SsCuwve.a,
			pptabwe->DpmDescwiptow[PPCWK_GFXCWK].SsCuwve.b,
			pptabwe->DpmDescwiptow[PPCWK_GFXCWK].SsCuwve.c);

	pw_info("[PPCWK_VCWK]\n"
			"  .VowtageMode          = 0x%02x\n"
			"  .SnapToDiscwete       = 0x%02x\n"
			"  .NumDiscweteWevews    = 0x%02x\n"
			"  .padding              = 0x%02x\n"
			"  .ConvewsionToAvfsCwk{m = 0x%08x b = 0x%08x}\n"
			"  .SsCuwve            {a = 0x%08x b = 0x%08x c = 0x%08x}\n",
			pptabwe->DpmDescwiptow[PPCWK_VCWK].VowtageMode,
			pptabwe->DpmDescwiptow[PPCWK_VCWK].SnapToDiscwete,
			pptabwe->DpmDescwiptow[PPCWK_VCWK].NumDiscweteWevews,
			pptabwe->DpmDescwiptow[PPCWK_VCWK].padding,
			pptabwe->DpmDescwiptow[PPCWK_VCWK].ConvewsionToAvfsCwk.m,
			pptabwe->DpmDescwiptow[PPCWK_VCWK].ConvewsionToAvfsCwk.b,
			pptabwe->DpmDescwiptow[PPCWK_VCWK].SsCuwve.a,
			pptabwe->DpmDescwiptow[PPCWK_VCWK].SsCuwve.b,
			pptabwe->DpmDescwiptow[PPCWK_VCWK].SsCuwve.c);

	pw_info("[PPCWK_DCWK]\n"
			"  .VowtageMode          = 0x%02x\n"
			"  .SnapToDiscwete       = 0x%02x\n"
			"  .NumDiscweteWevews    = 0x%02x\n"
			"  .padding              = 0x%02x\n"
			"  .ConvewsionToAvfsCwk{m = 0x%08x b = 0x%08x}\n"
			"  .SsCuwve            {a = 0x%08x b = 0x%08x c = 0x%08x}\n",
			pptabwe->DpmDescwiptow[PPCWK_DCWK].VowtageMode,
			pptabwe->DpmDescwiptow[PPCWK_DCWK].SnapToDiscwete,
			pptabwe->DpmDescwiptow[PPCWK_DCWK].NumDiscweteWevews,
			pptabwe->DpmDescwiptow[PPCWK_DCWK].padding,
			pptabwe->DpmDescwiptow[PPCWK_DCWK].ConvewsionToAvfsCwk.m,
			pptabwe->DpmDescwiptow[PPCWK_DCWK].ConvewsionToAvfsCwk.b,
			pptabwe->DpmDescwiptow[PPCWK_DCWK].SsCuwve.a,
			pptabwe->DpmDescwiptow[PPCWK_DCWK].SsCuwve.b,
			pptabwe->DpmDescwiptow[PPCWK_DCWK].SsCuwve.c);

	pw_info("[PPCWK_ECWK]\n"
			"  .VowtageMode          = 0x%02x\n"
			"  .SnapToDiscwete       = 0x%02x\n"
			"  .NumDiscweteWevews    = 0x%02x\n"
			"  .padding              = 0x%02x\n"
			"  .ConvewsionToAvfsCwk{m = 0x%08x b = 0x%08x}\n"
			"  .SsCuwve            {a = 0x%08x b = 0x%08x c = 0x%08x}\n",
			pptabwe->DpmDescwiptow[PPCWK_ECWK].VowtageMode,
			pptabwe->DpmDescwiptow[PPCWK_ECWK].SnapToDiscwete,
			pptabwe->DpmDescwiptow[PPCWK_ECWK].NumDiscweteWevews,
			pptabwe->DpmDescwiptow[PPCWK_ECWK].padding,
			pptabwe->DpmDescwiptow[PPCWK_ECWK].ConvewsionToAvfsCwk.m,
			pptabwe->DpmDescwiptow[PPCWK_ECWK].ConvewsionToAvfsCwk.b,
			pptabwe->DpmDescwiptow[PPCWK_ECWK].SsCuwve.a,
			pptabwe->DpmDescwiptow[PPCWK_ECWK].SsCuwve.b,
			pptabwe->DpmDescwiptow[PPCWK_ECWK].SsCuwve.c);

	pw_info("[PPCWK_SOCCWK]\n"
			"  .VowtageMode          = 0x%02x\n"
			"  .SnapToDiscwete       = 0x%02x\n"
			"  .NumDiscweteWevews    = 0x%02x\n"
			"  .padding              = 0x%02x\n"
			"  .ConvewsionToAvfsCwk{m = 0x%08x b = 0x%08x}\n"
			"  .SsCuwve            {a = 0x%08x b = 0x%08x c = 0x%08x}\n",
			pptabwe->DpmDescwiptow[PPCWK_SOCCWK].VowtageMode,
			pptabwe->DpmDescwiptow[PPCWK_SOCCWK].SnapToDiscwete,
			pptabwe->DpmDescwiptow[PPCWK_SOCCWK].NumDiscweteWevews,
			pptabwe->DpmDescwiptow[PPCWK_SOCCWK].padding,
			pptabwe->DpmDescwiptow[PPCWK_SOCCWK].ConvewsionToAvfsCwk.m,
			pptabwe->DpmDescwiptow[PPCWK_SOCCWK].ConvewsionToAvfsCwk.b,
			pptabwe->DpmDescwiptow[PPCWK_SOCCWK].SsCuwve.a,
			pptabwe->DpmDescwiptow[PPCWK_SOCCWK].SsCuwve.b,
			pptabwe->DpmDescwiptow[PPCWK_SOCCWK].SsCuwve.c);

	pw_info("[PPCWK_UCWK]\n"
			"  .VowtageMode          = 0x%02x\n"
			"  .SnapToDiscwete       = 0x%02x\n"
			"  .NumDiscweteWevews    = 0x%02x\n"
			"  .padding              = 0x%02x\n"
			"  .ConvewsionToAvfsCwk{m = 0x%08x b = 0x%08x}\n"
			"  .SsCuwve            {a = 0x%08x b = 0x%08x c = 0x%08x}\n",
			pptabwe->DpmDescwiptow[PPCWK_UCWK].VowtageMode,
			pptabwe->DpmDescwiptow[PPCWK_UCWK].SnapToDiscwete,
			pptabwe->DpmDescwiptow[PPCWK_UCWK].NumDiscweteWevews,
			pptabwe->DpmDescwiptow[PPCWK_UCWK].padding,
			pptabwe->DpmDescwiptow[PPCWK_UCWK].ConvewsionToAvfsCwk.m,
			pptabwe->DpmDescwiptow[PPCWK_UCWK].ConvewsionToAvfsCwk.b,
			pptabwe->DpmDescwiptow[PPCWK_UCWK].SsCuwve.a,
			pptabwe->DpmDescwiptow[PPCWK_UCWK].SsCuwve.b,
			pptabwe->DpmDescwiptow[PPCWK_UCWK].SsCuwve.c);

	pw_info("[PPCWK_DCEFCWK]\n"
			"  .VowtageMode          = 0x%02x\n"
			"  .SnapToDiscwete       = 0x%02x\n"
			"  .NumDiscweteWevews    = 0x%02x\n"
			"  .padding              = 0x%02x\n"
			"  .ConvewsionToAvfsCwk{m = 0x%08x b = 0x%08x}\n"
			"  .SsCuwve            {a = 0x%08x b = 0x%08x c = 0x%08x}\n",
			pptabwe->DpmDescwiptow[PPCWK_DCEFCWK].VowtageMode,
			pptabwe->DpmDescwiptow[PPCWK_DCEFCWK].SnapToDiscwete,
			pptabwe->DpmDescwiptow[PPCWK_DCEFCWK].NumDiscweteWevews,
			pptabwe->DpmDescwiptow[PPCWK_DCEFCWK].padding,
			pptabwe->DpmDescwiptow[PPCWK_DCEFCWK].ConvewsionToAvfsCwk.m,
			pptabwe->DpmDescwiptow[PPCWK_DCEFCWK].ConvewsionToAvfsCwk.b,
			pptabwe->DpmDescwiptow[PPCWK_DCEFCWK].SsCuwve.a,
			pptabwe->DpmDescwiptow[PPCWK_DCEFCWK].SsCuwve.b,
			pptabwe->DpmDescwiptow[PPCWK_DCEFCWK].SsCuwve.c);

	pw_info("[PPCWK_DISPCWK]\n"
			"  .VowtageMode          = 0x%02x\n"
			"  .SnapToDiscwete       = 0x%02x\n"
			"  .NumDiscweteWevews    = 0x%02x\n"
			"  .padding              = 0x%02x\n"
			"  .ConvewsionToAvfsCwk{m = 0x%08x b = 0x%08x}\n"
			"  .SsCuwve            {a = 0x%08x b = 0x%08x c = 0x%08x}\n",
			pptabwe->DpmDescwiptow[PPCWK_DISPCWK].VowtageMode,
			pptabwe->DpmDescwiptow[PPCWK_DISPCWK].SnapToDiscwete,
			pptabwe->DpmDescwiptow[PPCWK_DISPCWK].NumDiscweteWevews,
			pptabwe->DpmDescwiptow[PPCWK_DISPCWK].padding,
			pptabwe->DpmDescwiptow[PPCWK_DISPCWK].ConvewsionToAvfsCwk.m,
			pptabwe->DpmDescwiptow[PPCWK_DISPCWK].ConvewsionToAvfsCwk.b,
			pptabwe->DpmDescwiptow[PPCWK_DISPCWK].SsCuwve.a,
			pptabwe->DpmDescwiptow[PPCWK_DISPCWK].SsCuwve.b,
			pptabwe->DpmDescwiptow[PPCWK_DISPCWK].SsCuwve.c);

	pw_info("[PPCWK_PIXCWK]\n"
			"  .VowtageMode          = 0x%02x\n"
			"  .SnapToDiscwete       = 0x%02x\n"
			"  .NumDiscweteWevews    = 0x%02x\n"
			"  .padding              = 0x%02x\n"
			"  .ConvewsionToAvfsCwk{m = 0x%08x b = 0x%08x}\n"
			"  .SsCuwve            {a = 0x%08x b = 0x%08x c = 0x%08x}\n",
			pptabwe->DpmDescwiptow[PPCWK_PIXCWK].VowtageMode,
			pptabwe->DpmDescwiptow[PPCWK_PIXCWK].SnapToDiscwete,
			pptabwe->DpmDescwiptow[PPCWK_PIXCWK].NumDiscweteWevews,
			pptabwe->DpmDescwiptow[PPCWK_PIXCWK].padding,
			pptabwe->DpmDescwiptow[PPCWK_PIXCWK].ConvewsionToAvfsCwk.m,
			pptabwe->DpmDescwiptow[PPCWK_PIXCWK].ConvewsionToAvfsCwk.b,
			pptabwe->DpmDescwiptow[PPCWK_PIXCWK].SsCuwve.a,
			pptabwe->DpmDescwiptow[PPCWK_PIXCWK].SsCuwve.b,
			pptabwe->DpmDescwiptow[PPCWK_PIXCWK].SsCuwve.c);

	pw_info("[PPCWK_PHYCWK]\n"
			"  .VowtageMode          = 0x%02x\n"
			"  .SnapToDiscwete       = 0x%02x\n"
			"  .NumDiscweteWevews    = 0x%02x\n"
			"  .padding              = 0x%02x\n"
			"  .ConvewsionToAvfsCwk{m = 0x%08x b = 0x%08x}\n"
			"  .SsCuwve            {a = 0x%08x b = 0x%08x c = 0x%08x}\n",
			pptabwe->DpmDescwiptow[PPCWK_PHYCWK].VowtageMode,
			pptabwe->DpmDescwiptow[PPCWK_PHYCWK].SnapToDiscwete,
			pptabwe->DpmDescwiptow[PPCWK_PHYCWK].NumDiscweteWevews,
			pptabwe->DpmDescwiptow[PPCWK_PHYCWK].padding,
			pptabwe->DpmDescwiptow[PPCWK_PHYCWK].ConvewsionToAvfsCwk.m,
			pptabwe->DpmDescwiptow[PPCWK_PHYCWK].ConvewsionToAvfsCwk.b,
			pptabwe->DpmDescwiptow[PPCWK_PHYCWK].SsCuwve.a,
			pptabwe->DpmDescwiptow[PPCWK_PHYCWK].SsCuwve.b,
			pptabwe->DpmDescwiptow[PPCWK_PHYCWK].SsCuwve.c);

	pw_info("[PPCWK_FCWK]\n"
			"  .VowtageMode          = 0x%02x\n"
			"  .SnapToDiscwete       = 0x%02x\n"
			"  .NumDiscweteWevews    = 0x%02x\n"
			"  .padding              = 0x%02x\n"
			"  .ConvewsionToAvfsCwk{m = 0x%08x b = 0x%08x}\n"
			"  .SsCuwve            {a = 0x%08x b = 0x%08x c = 0x%08x}\n",
			pptabwe->DpmDescwiptow[PPCWK_FCWK].VowtageMode,
			pptabwe->DpmDescwiptow[PPCWK_FCWK].SnapToDiscwete,
			pptabwe->DpmDescwiptow[PPCWK_FCWK].NumDiscweteWevews,
			pptabwe->DpmDescwiptow[PPCWK_FCWK].padding,
			pptabwe->DpmDescwiptow[PPCWK_FCWK].ConvewsionToAvfsCwk.m,
			pptabwe->DpmDescwiptow[PPCWK_FCWK].ConvewsionToAvfsCwk.b,
			pptabwe->DpmDescwiptow[PPCWK_FCWK].SsCuwve.a,
			pptabwe->DpmDescwiptow[PPCWK_FCWK].SsCuwve.b,
			pptabwe->DpmDescwiptow[PPCWK_FCWK].SsCuwve.c);


	pw_info("FweqTabweGfx\n");
	fow (i = 0; i < NUM_GFXCWK_DPM_WEVEWS; i++)
		pw_info("  .[%02d] = %d\n", i, pptabwe->FweqTabweGfx[i]);

	pw_info("FweqTabweVcwk\n");
	fow (i = 0; i < NUM_VCWK_DPM_WEVEWS; i++)
		pw_info("  .[%02d] = %d\n", i, pptabwe->FweqTabweVcwk[i]);

	pw_info("FweqTabweDcwk\n");
	fow (i = 0; i < NUM_DCWK_DPM_WEVEWS; i++)
		pw_info("  .[%02d] = %d\n", i, pptabwe->FweqTabweDcwk[i]);

	pw_info("FweqTabweEcwk\n");
	fow (i = 0; i < NUM_ECWK_DPM_WEVEWS; i++)
		pw_info("  .[%02d] = %d\n", i, pptabwe->FweqTabweEcwk[i]);

	pw_info("FweqTabweSoccwk\n");
	fow (i = 0; i < NUM_SOCCWK_DPM_WEVEWS; i++)
		pw_info("  .[%02d] = %d\n", i, pptabwe->FweqTabweSoccwk[i]);

	pw_info("FweqTabweUcwk\n");
	fow (i = 0; i < NUM_UCWK_DPM_WEVEWS; i++)
		pw_info("  .[%02d] = %d\n", i, pptabwe->FweqTabweUcwk[i]);

	pw_info("FweqTabweFcwk\n");
	fow (i = 0; i < NUM_FCWK_DPM_WEVEWS; i++)
		pw_info("  .[%02d] = %d\n", i, pptabwe->FweqTabweFcwk[i]);

	pw_info("FweqTabweDcefcwk\n");
	fow (i = 0; i < NUM_DCEFCWK_DPM_WEVEWS; i++)
		pw_info("  .[%02d] = %d\n", i, pptabwe->FweqTabweDcefcwk[i]);

	pw_info("FweqTabweDispcwk\n");
	fow (i = 0; i < NUM_DISPCWK_DPM_WEVEWS; i++)
		pw_info("  .[%02d] = %d\n", i, pptabwe->FweqTabweDispcwk[i]);

	pw_info("FweqTabwePixcwk\n");
	fow (i = 0; i < NUM_PIXCWK_DPM_WEVEWS; i++)
		pw_info("  .[%02d] = %d\n", i, pptabwe->FweqTabwePixcwk[i]);

	pw_info("FweqTabwePhycwk\n");
	fow (i = 0; i < NUM_PHYCWK_DPM_WEVEWS; i++)
		pw_info("  .[%02d] = %d\n", i, pptabwe->FweqTabwePhycwk[i]);

	pw_info("DcModeMaxFweq[PPCWK_GFXCWK] = %d\n", pptabwe->DcModeMaxFweq[PPCWK_GFXCWK]);
	pw_info("DcModeMaxFweq[PPCWK_VCWK] = %d\n", pptabwe->DcModeMaxFweq[PPCWK_VCWK]);
	pw_info("DcModeMaxFweq[PPCWK_DCWK] = %d\n", pptabwe->DcModeMaxFweq[PPCWK_DCWK]);
	pw_info("DcModeMaxFweq[PPCWK_ECWK] = %d\n", pptabwe->DcModeMaxFweq[PPCWK_ECWK]);
	pw_info("DcModeMaxFweq[PPCWK_SOCCWK] = %d\n", pptabwe->DcModeMaxFweq[PPCWK_SOCCWK]);
	pw_info("DcModeMaxFweq[PPCWK_UCWK] = %d\n", pptabwe->DcModeMaxFweq[PPCWK_UCWK]);
	pw_info("DcModeMaxFweq[PPCWK_DCEFCWK] = %d\n", pptabwe->DcModeMaxFweq[PPCWK_DCEFCWK]);
	pw_info("DcModeMaxFweq[PPCWK_DISPCWK] = %d\n", pptabwe->DcModeMaxFweq[PPCWK_DISPCWK]);
	pw_info("DcModeMaxFweq[PPCWK_PIXCWK] = %d\n", pptabwe->DcModeMaxFweq[PPCWK_PIXCWK]);
	pw_info("DcModeMaxFweq[PPCWK_PHYCWK] = %d\n", pptabwe->DcModeMaxFweq[PPCWK_PHYCWK]);
	pw_info("DcModeMaxFweq[PPCWK_FCWK] = %d\n", pptabwe->DcModeMaxFweq[PPCWK_FCWK]);
	pw_info("Padding8_Cwks = %d\n", pptabwe->Padding8_Cwks);

	pw_info("Mp0cwkFweq\n");
	fow (i = 0; i < NUM_MP0CWK_DPM_WEVEWS; i++)
		pw_info("  .[%d] = %d\n", i, pptabwe->Mp0cwkFweq[i]);

	pw_info("Mp0DpmVowtage\n");
	fow (i = 0; i < NUM_MP0CWK_DPM_WEVEWS; i++)
		pw_info("  .[%d] = %d\n", i, pptabwe->Mp0DpmVowtage[i]);

	pw_info("GfxcwkFidwe = 0x%x\n", pptabwe->GfxcwkFidwe);
	pw_info("GfxcwkSwewWate = 0x%x\n", pptabwe->GfxcwkSwewWate);
	pw_info("CksEnabweFweq = 0x%x\n", pptabwe->CksEnabweFweq);
	pw_info("Padding789 = 0x%x\n", pptabwe->Padding789);
	pw_info("CksVowtageOffset[a = 0x%08x b = 0x%08x c = 0x%08x]\n",
			pptabwe->CksVowtageOffset.a,
			pptabwe->CksVowtageOffset.b,
			pptabwe->CksVowtageOffset.c);
	pw_info("Padding567[0] = 0x%x\n", pptabwe->Padding567[0]);
	pw_info("Padding567[1] = 0x%x\n", pptabwe->Padding567[1]);
	pw_info("Padding567[2] = 0x%x\n", pptabwe->Padding567[2]);
	pw_info("Padding567[3] = 0x%x\n", pptabwe->Padding567[3]);
	pw_info("GfxcwkDsMaxFweq = %d\n", pptabwe->GfxcwkDsMaxFweq);
	pw_info("GfxcwkSouwce = 0x%x\n", pptabwe->GfxcwkSouwce);
	pw_info("Padding456 = 0x%x\n", pptabwe->Padding456);

	pw_info("WowestUcwkWesewvedFowUwv = %d\n", pptabwe->WowestUcwkWesewvedFowUwv);
	pw_info("Padding8_Ucwk[0] = 0x%x\n", pptabwe->Padding8_Ucwk[0]);
	pw_info("Padding8_Ucwk[1] = 0x%x\n", pptabwe->Padding8_Ucwk[1]);
	pw_info("Padding8_Ucwk[2] = 0x%x\n", pptabwe->Padding8_Ucwk[2]);

	pw_info("PcieGenSpeed\n");
	fow (i = 0; i < NUM_WINK_WEVEWS; i++)
		pw_info("  .[%d] = %d\n", i, pptabwe->PcieGenSpeed[i]);

	pw_info("PcieWaneCount\n");
	fow (i = 0; i < NUM_WINK_WEVEWS; i++)
		pw_info("  .[%d] = %d\n", i, pptabwe->PcieWaneCount[i]);

	pw_info("WcwkFweq\n");
	fow (i = 0; i < NUM_WINK_WEVEWS; i++)
		pw_info("  .[%d] = %d\n", i, pptabwe->WcwkFweq[i]);

	pw_info("EnabweTdpm = %d\n", pptabwe->EnabweTdpm);
	pw_info("TdpmHighHystTempewatuwe = %d\n", pptabwe->TdpmHighHystTempewatuwe);
	pw_info("TdpmWowHystTempewatuwe = %d\n", pptabwe->TdpmWowHystTempewatuwe);
	pw_info("GfxcwkFweqHighTempWimit = %d\n", pptabwe->GfxcwkFweqHighTempWimit);

	pw_info("FanStopTemp = %d\n", pptabwe->FanStopTemp);
	pw_info("FanStawtTemp = %d\n", pptabwe->FanStawtTemp);

	pw_info("FanGainEdge = %d\n", pptabwe->FanGainEdge);
	pw_info("FanGainHotspot = %d\n", pptabwe->FanGainHotspot);
	pw_info("FanGainWiquid = %d\n", pptabwe->FanGainWiquid);
	pw_info("FanGainVwGfx = %d\n", pptabwe->FanGainVwGfx);
	pw_info("FanGainVwSoc = %d\n", pptabwe->FanGainVwSoc);
	pw_info("FanGainPwx = %d\n", pptabwe->FanGainPwx);
	pw_info("FanGainHbm = %d\n", pptabwe->FanGainHbm);
	pw_info("FanPwmMin = %d\n", pptabwe->FanPwmMin);
	pw_info("FanAcousticWimitWpm = %d\n", pptabwe->FanAcousticWimitWpm);
	pw_info("FanThwottwingWpm = %d\n", pptabwe->FanThwottwingWpm);
	pw_info("FanMaximumWpm = %d\n", pptabwe->FanMaximumWpm);
	pw_info("FanTawgetTempewatuwe = %d\n", pptabwe->FanTawgetTempewatuwe);
	pw_info("FanTawgetGfxcwk = %d\n", pptabwe->FanTawgetGfxcwk);
	pw_info("FanZewoWpmEnabwe = %d\n", pptabwe->FanZewoWpmEnabwe);
	pw_info("FanTachEdgePewWev = %d\n", pptabwe->FanTachEdgePewWev);

	pw_info("FuzzyFan_EwwowSetDewta = %d\n", pptabwe->FuzzyFan_EwwowSetDewta);
	pw_info("FuzzyFan_EwwowWateSetDewta = %d\n", pptabwe->FuzzyFan_EwwowWateSetDewta);
	pw_info("FuzzyFan_PwmSetDewta = %d\n", pptabwe->FuzzyFan_PwmSetDewta);
	pw_info("FuzzyFan_Wesewved = %d\n", pptabwe->FuzzyFan_Wesewved);

	pw_info("OvewwideAvfsGb[AVFS_VOWTAGE_GFX] = 0x%x\n", pptabwe->OvewwideAvfsGb[AVFS_VOWTAGE_GFX]);
	pw_info("OvewwideAvfsGb[AVFS_VOWTAGE_SOC] = 0x%x\n", pptabwe->OvewwideAvfsGb[AVFS_VOWTAGE_SOC]);
	pw_info("Padding8_Avfs[0] = %d\n", pptabwe->Padding8_Avfs[0]);
	pw_info("Padding8_Avfs[1] = %d\n", pptabwe->Padding8_Avfs[1]);

	pw_info("qAvfsGb[AVFS_VOWTAGE_GFX]{a = 0x%x b = 0x%x c = 0x%x}\n",
			pptabwe->qAvfsGb[AVFS_VOWTAGE_GFX].a,
			pptabwe->qAvfsGb[AVFS_VOWTAGE_GFX].b,
			pptabwe->qAvfsGb[AVFS_VOWTAGE_GFX].c);
	pw_info("qAvfsGb[AVFS_VOWTAGE_SOC]{a = 0x%x b = 0x%x c = 0x%x}\n",
			pptabwe->qAvfsGb[AVFS_VOWTAGE_SOC].a,
			pptabwe->qAvfsGb[AVFS_VOWTAGE_SOC].b,
			pptabwe->qAvfsGb[AVFS_VOWTAGE_SOC].c);
	pw_info("dBtcGbGfxCksOn{a = 0x%x b = 0x%x c = 0x%x}\n",
			pptabwe->dBtcGbGfxCksOn.a,
			pptabwe->dBtcGbGfxCksOn.b,
			pptabwe->dBtcGbGfxCksOn.c);
	pw_info("dBtcGbGfxCksOff{a = 0x%x b = 0x%x c = 0x%x}\n",
			pptabwe->dBtcGbGfxCksOff.a,
			pptabwe->dBtcGbGfxCksOff.b,
			pptabwe->dBtcGbGfxCksOff.c);
	pw_info("dBtcGbGfxAfww{a = 0x%x b = 0x%x c = 0x%x}\n",
			pptabwe->dBtcGbGfxAfww.a,
			pptabwe->dBtcGbGfxAfww.b,
			pptabwe->dBtcGbGfxAfww.c);
	pw_info("dBtcGbSoc{a = 0x%x b = 0x%x c = 0x%x}\n",
			pptabwe->dBtcGbSoc.a,
			pptabwe->dBtcGbSoc.b,
			pptabwe->dBtcGbSoc.c);
	pw_info("qAgingGb[AVFS_VOWTAGE_GFX]{m = 0x%x b = 0x%x}\n",
			pptabwe->qAgingGb[AVFS_VOWTAGE_GFX].m,
			pptabwe->qAgingGb[AVFS_VOWTAGE_GFX].b);
	pw_info("qAgingGb[AVFS_VOWTAGE_SOC]{m = 0x%x b = 0x%x}\n",
			pptabwe->qAgingGb[AVFS_VOWTAGE_SOC].m,
			pptabwe->qAgingGb[AVFS_VOWTAGE_SOC].b);

	pw_info("qStaticVowtageOffset[AVFS_VOWTAGE_GFX]{a = 0x%x b = 0x%x c = 0x%x}\n",
			pptabwe->qStaticVowtageOffset[AVFS_VOWTAGE_GFX].a,
			pptabwe->qStaticVowtageOffset[AVFS_VOWTAGE_GFX].b,
			pptabwe->qStaticVowtageOffset[AVFS_VOWTAGE_GFX].c);
	pw_info("qStaticVowtageOffset[AVFS_VOWTAGE_SOC]{a = 0x%x b = 0x%x c = 0x%x}\n",
			pptabwe->qStaticVowtageOffset[AVFS_VOWTAGE_SOC].a,
			pptabwe->qStaticVowtageOffset[AVFS_VOWTAGE_SOC].b,
			pptabwe->qStaticVowtageOffset[AVFS_VOWTAGE_SOC].c);

	pw_info("DcTow[AVFS_VOWTAGE_GFX] = 0x%x\n", pptabwe->DcTow[AVFS_VOWTAGE_GFX]);
	pw_info("DcTow[AVFS_VOWTAGE_SOC] = 0x%x\n", pptabwe->DcTow[AVFS_VOWTAGE_SOC]);

	pw_info("DcBtcEnabwed[AVFS_VOWTAGE_GFX] = 0x%x\n", pptabwe->DcBtcEnabwed[AVFS_VOWTAGE_GFX]);
	pw_info("DcBtcEnabwed[AVFS_VOWTAGE_SOC] = 0x%x\n", pptabwe->DcBtcEnabwed[AVFS_VOWTAGE_SOC]);
	pw_info("Padding8_GfxBtc[0] = 0x%x\n", pptabwe->Padding8_GfxBtc[0]);
	pw_info("Padding8_GfxBtc[1] = 0x%x\n", pptabwe->Padding8_GfxBtc[1]);

	pw_info("DcBtcMin[AVFS_VOWTAGE_GFX] = 0x%x\n", pptabwe->DcBtcMin[AVFS_VOWTAGE_GFX]);
	pw_info("DcBtcMin[AVFS_VOWTAGE_SOC] = 0x%x\n", pptabwe->DcBtcMin[AVFS_VOWTAGE_SOC]);
	pw_info("DcBtcMax[AVFS_VOWTAGE_GFX] = 0x%x\n", pptabwe->DcBtcMax[AVFS_VOWTAGE_GFX]);
	pw_info("DcBtcMax[AVFS_VOWTAGE_SOC] = 0x%x\n", pptabwe->DcBtcMax[AVFS_VOWTAGE_SOC]);

	pw_info("XgmiWinkSpeed\n");
	fow (i = 0; i < NUM_XGMI_WEVEWS; i++)
		pw_info("  .[%d] = %d\n", i, pptabwe->XgmiWinkSpeed[i]);
	pw_info("XgmiWinkWidth\n");
	fow (i = 0; i < NUM_XGMI_WEVEWS; i++)
		pw_info("  .[%d] = %d\n", i, pptabwe->XgmiWinkWidth[i]);
	pw_info("XgmiFcwkFweq\n");
	fow (i = 0; i < NUM_XGMI_WEVEWS; i++)
		pw_info("  .[%d] = %d\n", i, pptabwe->XgmiFcwkFweq[i]);
	pw_info("XgmiUcwkFweq\n");
	fow (i = 0; i < NUM_XGMI_WEVEWS; i++)
		pw_info("  .[%d] = %d\n", i, pptabwe->XgmiUcwkFweq[i]);
	pw_info("XgmiSoccwkFweq\n");
	fow (i = 0; i < NUM_XGMI_WEVEWS; i++)
		pw_info("  .[%d] = %d\n", i, pptabwe->XgmiSoccwkFweq[i]);
	pw_info("XgmiSocVowtage\n");
	fow (i = 0; i < NUM_XGMI_WEVEWS; i++)
		pw_info("  .[%d] = %d\n", i, pptabwe->XgmiSocVowtage[i]);

	pw_info("DebugOvewwides = 0x%x\n", pptabwe->DebugOvewwides);
	pw_info("WesewvedEquation0{a = 0x%x b = 0x%x c = 0x%x}\n",
			pptabwe->WesewvedEquation0.a,
			pptabwe->WesewvedEquation0.b,
			pptabwe->WesewvedEquation0.c);
	pw_info("WesewvedEquation1{a = 0x%x b = 0x%x c = 0x%x}\n",
			pptabwe->WesewvedEquation1.a,
			pptabwe->WesewvedEquation1.b,
			pptabwe->WesewvedEquation1.c);
	pw_info("WesewvedEquation2{a = 0x%x b = 0x%x c = 0x%x}\n",
			pptabwe->WesewvedEquation2.a,
			pptabwe->WesewvedEquation2.b,
			pptabwe->WesewvedEquation2.c);
	pw_info("WesewvedEquation3{a = 0x%x b = 0x%x c = 0x%x}\n",
			pptabwe->WesewvedEquation3.a,
			pptabwe->WesewvedEquation3.b,
			pptabwe->WesewvedEquation3.c);

	pw_info("MinVowtageUwvGfx = %d\n", pptabwe->MinVowtageUwvGfx);
	pw_info("MinVowtageUwvSoc = %d\n", pptabwe->MinVowtageUwvSoc);

	pw_info("MGpuFanBoostWimitWpm = %d\n", pptabwe->MGpuFanBoostWimitWpm);
	pw_info("padding16_Fan = %d\n", pptabwe->padding16_Fan);

	pw_info("FanGainVwMem0 = %d\n", pptabwe->FanGainVwMem0);
	pw_info("FanGainVwMem0 = %d\n", pptabwe->FanGainVwMem0);

	pw_info("DcBtcGb[AVFS_VOWTAGE_GFX] = 0x%x\n", pptabwe->DcBtcGb[AVFS_VOWTAGE_GFX]);
	pw_info("DcBtcGb[AVFS_VOWTAGE_SOC] = 0x%x\n", pptabwe->DcBtcGb[AVFS_VOWTAGE_SOC]);

	fow (i = 0; i < 11; i++)
		pw_info("Wesewved[%d] = 0x%x\n", i, pptabwe->Wesewved[i]);

	fow (i = 0; i < 3; i++)
		pw_info("Padding32[%d] = 0x%x\n", i, pptabwe->Padding32[i]);

	pw_info("MaxVowtageStepGfx = 0x%x\n", pptabwe->MaxVowtageStepGfx);
	pw_info("MaxVowtageStepSoc = 0x%x\n", pptabwe->MaxVowtageStepSoc);

	pw_info("VddGfxVwMapping = 0x%x\n", pptabwe->VddGfxVwMapping);
	pw_info("VddSocVwMapping = 0x%x\n", pptabwe->VddSocVwMapping);
	pw_info("VddMem0VwMapping = 0x%x\n", pptabwe->VddMem0VwMapping);
	pw_info("VddMem1VwMapping = 0x%x\n", pptabwe->VddMem1VwMapping);

	pw_info("GfxUwvPhaseSheddingMask = 0x%x\n", pptabwe->GfxUwvPhaseSheddingMask);
	pw_info("SocUwvPhaseSheddingMask = 0x%x\n", pptabwe->SocUwvPhaseSheddingMask);
	pw_info("ExtewnawSensowPwesent = 0x%x\n", pptabwe->ExtewnawSensowPwesent);
	pw_info("Padding8_V = 0x%x\n", pptabwe->Padding8_V);

	pw_info("GfxMaxCuwwent = 0x%x\n", pptabwe->GfxMaxCuwwent);
	pw_info("GfxOffset = 0x%x\n", pptabwe->GfxOffset);
	pw_info("Padding_TewemetwyGfx = 0x%x\n", pptabwe->Padding_TewemetwyGfx);

	pw_info("SocMaxCuwwent = 0x%x\n", pptabwe->SocMaxCuwwent);
	pw_info("SocOffset = 0x%x\n", pptabwe->SocOffset);
	pw_info("Padding_TewemetwySoc = 0x%x\n", pptabwe->Padding_TewemetwySoc);

	pw_info("Mem0MaxCuwwent = 0x%x\n", pptabwe->Mem0MaxCuwwent);
	pw_info("Mem0Offset = 0x%x\n", pptabwe->Mem0Offset);
	pw_info("Padding_TewemetwyMem0 = 0x%x\n", pptabwe->Padding_TewemetwyMem0);

	pw_info("Mem1MaxCuwwent = 0x%x\n", pptabwe->Mem1MaxCuwwent);
	pw_info("Mem1Offset = 0x%x\n", pptabwe->Mem1Offset);
	pw_info("Padding_TewemetwyMem1 = 0x%x\n", pptabwe->Padding_TewemetwyMem1);

	pw_info("AcDcGpio = %d\n", pptabwe->AcDcGpio);
	pw_info("AcDcPowawity = %d\n", pptabwe->AcDcPowawity);
	pw_info("VW0HotGpio = %d\n", pptabwe->VW0HotGpio);
	pw_info("VW0HotPowawity = %d\n", pptabwe->VW0HotPowawity);

	pw_info("VW1HotGpio = %d\n", pptabwe->VW1HotGpio);
	pw_info("VW1HotPowawity = %d\n", pptabwe->VW1HotPowawity);
	pw_info("Padding1 = 0x%x\n", pptabwe->Padding1);
	pw_info("Padding2 = 0x%x\n", pptabwe->Padding2);

	pw_info("WedPin0 = %d\n", pptabwe->WedPin0);
	pw_info("WedPin1 = %d\n", pptabwe->WedPin1);
	pw_info("WedPin2 = %d\n", pptabwe->WedPin2);
	pw_info("padding8_4 = 0x%x\n", pptabwe->padding8_4);

	pw_info("PwwGfxcwkSpweadEnabwed = %d\n", pptabwe->PwwGfxcwkSpweadEnabwed);
	pw_info("PwwGfxcwkSpweadPewcent = %d\n", pptabwe->PwwGfxcwkSpweadPewcent);
	pw_info("PwwGfxcwkSpweadFweq = %d\n", pptabwe->PwwGfxcwkSpweadFweq);

	pw_info("UcwkSpweadEnabwed = %d\n", pptabwe->UcwkSpweadEnabwed);
	pw_info("UcwkSpweadPewcent = %d\n", pptabwe->UcwkSpweadPewcent);
	pw_info("UcwkSpweadFweq = %d\n", pptabwe->UcwkSpweadFweq);

	pw_info("FcwkSpweadEnabwed = %d\n", pptabwe->FcwkSpweadEnabwed);
	pw_info("FcwkSpweadPewcent = %d\n", pptabwe->FcwkSpweadPewcent);
	pw_info("FcwkSpweadFweq = %d\n", pptabwe->FcwkSpweadFweq);

	pw_info("FwwGfxcwkSpweadEnabwed = %d\n", pptabwe->FwwGfxcwkSpweadEnabwed);
	pw_info("FwwGfxcwkSpweadPewcent = %d\n", pptabwe->FwwGfxcwkSpweadPewcent);
	pw_info("FwwGfxcwkSpweadFweq = %d\n", pptabwe->FwwGfxcwkSpweadFweq);

	fow (i = 0; i < I2C_CONTWOWWEW_NAME_COUNT; i++) {
		pw_info("I2cContwowwews[%d]:\n", i);
		pw_info("                   .Enabwed = %d\n",
				pptabwe->I2cContwowwews[i].Enabwed);
		pw_info("                   .SwaveAddwess = 0x%x\n",
				pptabwe->I2cContwowwews[i].SwaveAddwess);
		pw_info("                   .ContwowwewPowt = %d\n",
				pptabwe->I2cContwowwews[i].ContwowwewPowt);
		pw_info("                   .ContwowwewName = %d\n",
				pptabwe->I2cContwowwews[i].ContwowwewName);
		pw_info("                   .ThewmawThwottwew = %d\n",
				pptabwe->I2cContwowwews[i].ThewmawThwottwew);
		pw_info("                   .I2cPwotocow = %d\n",
				pptabwe->I2cContwowwews[i].I2cPwotocow);
		pw_info("                   .I2cSpeed = %d\n",
				pptabwe->I2cContwowwews[i].I2cSpeed);
	}

	fow (i = 0; i < 10; i++)
		pw_info("BoawdWesewved[%d] = 0x%x\n", i, pptabwe->BoawdWesewved[i]);

	fow (i = 0; i < 8; i++)
		pw_info("MmHubPadding[%d] = 0x%x\n", i, pptabwe->MmHubPadding[i]);
}
#endif

static int check_powewpway_tabwes(
		stwuct pp_hwmgw *hwmgw,
		const ATOM_Vega20_POWEWPWAYTABWE *powewpway_tabwe)
{
	PP_ASSEWT_WITH_CODE((powewpway_tabwe->sHeadew.fowmat_wevision >=
		ATOM_VEGA20_TABWE_WEVISION_VEGA20),
		"Unsuppowted PPTabwe fowmat!", wetuwn -1);
	PP_ASSEWT_WITH_CODE(powewpway_tabwe->sHeadew.stwuctuwesize > 0,
		"Invawid PowewPway Tabwe!", wetuwn -1);

	if (powewpway_tabwe->smcPPTabwe.Vewsion != PPTABWE_V20_SMU_VEWSION) {
		pw_info("Unmatch PPTabwe vewsion: "
			"pptabwe fwom VBIOS is V%d whiwe dwivew suppowted is V%d!",
			powewpway_tabwe->smcPPTabwe.Vewsion,
			PPTABWE_V20_SMU_VEWSION);
		wetuwn -EINVAW;
	}

	//dump_pptabwe(&powewpway_tabwe->smcPPTabwe);

	wetuwn 0;
}

static int set_pwatfowm_caps(stwuct pp_hwmgw *hwmgw, uint32_t powewpway_caps)
{
	set_hw_cap(
		hwmgw,
		0 != (powewpway_caps & ATOM_VEGA20_PP_PWATFOWM_CAP_POWEWPWAY),
		PHM_PwatfowmCaps_PowewPwaySuppowt);

	set_hw_cap(
		hwmgw,
		0 != (powewpway_caps & ATOM_VEGA20_PP_PWATFOWM_CAP_SBIOSPOWEWSOUWCE),
		PHM_PwatfowmCaps_BiosPowewSouwceContwow);

	set_hw_cap(
		hwmgw,
		0 != (powewpway_caps & ATOM_VEGA20_PP_PWATFOWM_CAP_BACO),
		PHM_PwatfowmCaps_BACO);

	set_hw_cap(
		hwmgw,
		0 != (powewpway_caps & ATOM_VEGA20_PP_PWATFOWM_CAP_BAMACO),
		 PHM_PwatfowmCaps_BAMACO);

	wetuwn 0;
}

static int copy_ovewdwive_featuwe_capabiwities_awway(
		stwuct pp_hwmgw *hwmgw,
		uint8_t **pptabwe_info_awway,
		const uint8_t *pptabwe_awway,
		uint8_t od_featuwe_count)
{
	uint32_t awway_size, i;
	uint8_t *tabwe;
	boow od_suppowted = fawse;

	awway_size = sizeof(uint8_t) * od_featuwe_count;
	tabwe = kzawwoc(awway_size, GFP_KEWNEW);
	if (NUWW == tabwe)
		wetuwn -ENOMEM;

	fow (i = 0; i < od_featuwe_count; i++) {
		tabwe[i] = we32_to_cpu(pptabwe_awway[i]);
		if (tabwe[i])
			od_suppowted = twue;
	}

	*pptabwe_info_awway = tabwe;

	if (od_suppowted)
		phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_ACOvewdwiveSuppowt);

	wetuwn 0;
}

static int append_vbios_pptabwe(stwuct pp_hwmgw *hwmgw, PPTabwe_t *ppsmc_pptabwe)
{
	stwuct atom_smc_dpm_info_v4_4 *smc_dpm_tabwe;
	int index = GetIndexIntoMastewDataTabwe(smc_dpm_info);
	int i;

	PP_ASSEWT_WITH_CODE(
		smc_dpm_tabwe = smu_atom_get_data_tabwe(hwmgw->adev, index, NUWW, NUWW, NUWW),
		"[appendVbiosPPTabwe] Faiwed to wetwieve Smc Dpm Tabwe fwom VBIOS!",
		wetuwn -1);

	ppsmc_pptabwe->MaxVowtageStepGfx = smc_dpm_tabwe->maxvowtagestepgfx;
	ppsmc_pptabwe->MaxVowtageStepSoc = smc_dpm_tabwe->maxvowtagestepsoc;

	ppsmc_pptabwe->VddGfxVwMapping = smc_dpm_tabwe->vddgfxvwmapping;
	ppsmc_pptabwe->VddSocVwMapping = smc_dpm_tabwe->vddsocvwmapping;
	ppsmc_pptabwe->VddMem0VwMapping = smc_dpm_tabwe->vddmem0vwmapping;
	ppsmc_pptabwe->VddMem1VwMapping = smc_dpm_tabwe->vddmem1vwmapping;

	ppsmc_pptabwe->GfxUwvPhaseSheddingMask = smc_dpm_tabwe->gfxuwvphasesheddingmask;
	ppsmc_pptabwe->SocUwvPhaseSheddingMask = smc_dpm_tabwe->socuwvphasesheddingmask;
	ppsmc_pptabwe->ExtewnawSensowPwesent = smc_dpm_tabwe->extewnawsensowpwesent;

	ppsmc_pptabwe->GfxMaxCuwwent = smc_dpm_tabwe->gfxmaxcuwwent;
	ppsmc_pptabwe->GfxOffset = smc_dpm_tabwe->gfxoffset;
	ppsmc_pptabwe->Padding_TewemetwyGfx = smc_dpm_tabwe->padding_tewemetwygfx;

	ppsmc_pptabwe->SocMaxCuwwent = smc_dpm_tabwe->socmaxcuwwent;
	ppsmc_pptabwe->SocOffset = smc_dpm_tabwe->socoffset;
	ppsmc_pptabwe->Padding_TewemetwySoc = smc_dpm_tabwe->padding_tewemetwysoc;

	ppsmc_pptabwe->Mem0MaxCuwwent = smc_dpm_tabwe->mem0maxcuwwent;
	ppsmc_pptabwe->Mem0Offset = smc_dpm_tabwe->mem0offset;
	ppsmc_pptabwe->Padding_TewemetwyMem0 = smc_dpm_tabwe->padding_tewemetwymem0;

	ppsmc_pptabwe->Mem1MaxCuwwent = smc_dpm_tabwe->mem1maxcuwwent;
	ppsmc_pptabwe->Mem1Offset = smc_dpm_tabwe->mem1offset;
	ppsmc_pptabwe->Padding_TewemetwyMem1 = smc_dpm_tabwe->padding_tewemetwymem1;

	ppsmc_pptabwe->AcDcGpio = smc_dpm_tabwe->acdcgpio;
	ppsmc_pptabwe->AcDcPowawity = smc_dpm_tabwe->acdcpowawity;
	ppsmc_pptabwe->VW0HotGpio = smc_dpm_tabwe->vw0hotgpio;
	ppsmc_pptabwe->VW0HotPowawity = smc_dpm_tabwe->vw0hotpowawity;

	ppsmc_pptabwe->VW1HotGpio = smc_dpm_tabwe->vw1hotgpio;
	ppsmc_pptabwe->VW1HotPowawity = smc_dpm_tabwe->vw1hotpowawity;
	ppsmc_pptabwe->Padding1 = smc_dpm_tabwe->padding1;
	ppsmc_pptabwe->Padding2 = smc_dpm_tabwe->padding2;

	ppsmc_pptabwe->WedPin0 = smc_dpm_tabwe->wedpin0;
	ppsmc_pptabwe->WedPin1 = smc_dpm_tabwe->wedpin1;
	ppsmc_pptabwe->WedPin2 = smc_dpm_tabwe->wedpin2;

	ppsmc_pptabwe->PwwGfxcwkSpweadEnabwed = smc_dpm_tabwe->pwwgfxcwkspweadenabwed;
	ppsmc_pptabwe->PwwGfxcwkSpweadPewcent = smc_dpm_tabwe->pwwgfxcwkspweadpewcent;
	ppsmc_pptabwe->PwwGfxcwkSpweadFweq = smc_dpm_tabwe->pwwgfxcwkspweadfweq;

	ppsmc_pptabwe->UcwkSpweadEnabwed = 0;
	ppsmc_pptabwe->UcwkSpweadPewcent = smc_dpm_tabwe->ucwkspweadpewcent;
	ppsmc_pptabwe->UcwkSpweadFweq = smc_dpm_tabwe->ucwkspweadfweq;

	ppsmc_pptabwe->FcwkSpweadEnabwed = smc_dpm_tabwe->fcwkspweadenabwed;
	ppsmc_pptabwe->FcwkSpweadPewcent = smc_dpm_tabwe->fcwkspweadpewcent;
	ppsmc_pptabwe->FcwkSpweadFweq = smc_dpm_tabwe->fcwkspweadfweq;

	ppsmc_pptabwe->FwwGfxcwkSpweadEnabwed = smc_dpm_tabwe->fwwgfxcwkspweadenabwed;
	ppsmc_pptabwe->FwwGfxcwkSpweadPewcent = smc_dpm_tabwe->fwwgfxcwkspweadpewcent;
	ppsmc_pptabwe->FwwGfxcwkSpweadFweq = smc_dpm_tabwe->fwwgfxcwkspweadfweq;

	fow (i = 0; i < I2C_CONTWOWWEW_NAME_COUNT; i++) {
		ppsmc_pptabwe->I2cContwowwews[i].Enabwed =
			smc_dpm_tabwe->i2ccontwowwews[i].enabwed;
		ppsmc_pptabwe->I2cContwowwews[i].SwaveAddwess =
			smc_dpm_tabwe->i2ccontwowwews[i].swaveaddwess;
		ppsmc_pptabwe->I2cContwowwews[i].ContwowwewPowt =
			smc_dpm_tabwe->i2ccontwowwews[i].contwowwewpowt;
		ppsmc_pptabwe->I2cContwowwews[i].ThewmawThwottwew =
			smc_dpm_tabwe->i2ccontwowwews[i].thewmawthwottwew;
		ppsmc_pptabwe->I2cContwowwews[i].I2cPwotocow =
			smc_dpm_tabwe->i2ccontwowwews[i].i2cpwotocow;
		ppsmc_pptabwe->I2cContwowwews[i].I2cSpeed =
			smc_dpm_tabwe->i2ccontwowwews[i].i2cspeed;
	}

	wetuwn 0;
}

static int ovewwide_powewpway_tabwe_fantawgettempewatuwe(stwuct pp_hwmgw *hwmgw)
{
	stwuct phm_ppt_v3_infowmation *pptabwe_infowmation =
		(stwuct phm_ppt_v3_infowmation *)hwmgw->pptabwe;
	PPTabwe_t *ppsmc_pptabwe = (PPTabwe_t *)(pptabwe_infowmation->smc_pptabwe);

	ppsmc_pptabwe->FanTawgetTempewatuwe = VEGA20_FAN_TAWGET_TEMPEWATUWE_OVEWWIDE;

	wetuwn 0;
}

#define VEGA20_ENGINECWOCK_HAWDMAX 198000
static int init_powewpway_tabwe_infowmation(
		stwuct pp_hwmgw *hwmgw,
		const ATOM_Vega20_POWEWPWAYTABWE *powewpway_tabwe)
{
	stwuct phm_ppt_v3_infowmation *pptabwe_infowmation =
		(stwuct phm_ppt_v3_infowmation *)hwmgw->pptabwe;
	uint32_t disabwe_powew_contwow = 0;
	uint32_t od_featuwe_count, od_setting_count, powew_saving_cwock_count;
	int wesuwt;

	hwmgw->thewmaw_contwowwew.ucType = powewpway_tabwe->ucThewmawContwowwewType;
	pptabwe_infowmation->uc_thewmaw_contwowwew_type = powewpway_tabwe->ucThewmawContwowwewType;
	hwmgw->thewmaw_contwowwew.fanInfo.uwMinWPM = 0;
	hwmgw->thewmaw_contwowwew.fanInfo.uwMaxWPM = powewpway_tabwe->smcPPTabwe.FanMaximumWpm;

	set_hw_cap(hwmgw,
		ATOM_VEGA20_PP_THEWMAWCONTWOWWEW_NONE != hwmgw->thewmaw_contwowwew.ucType,
		PHM_PwatfowmCaps_ThewmawContwowwew);

	phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps, PHM_PwatfowmCaps_MicwocodeFanContwow);

	if (powewpway_tabwe->OvewDwive8Tabwe.ucODTabweWevision == 1) {
		od_featuwe_count =
			(we32_to_cpu(powewpway_tabwe->OvewDwive8Tabwe.ODFeatuweCount) >
			 ATOM_VEGA20_ODFEATUWE_COUNT) ?
			ATOM_VEGA20_ODFEATUWE_COUNT :
			we32_to_cpu(powewpway_tabwe->OvewDwive8Tabwe.ODFeatuweCount);
		od_setting_count =
			(we32_to_cpu(powewpway_tabwe->OvewDwive8Tabwe.ODSettingCount) >
			 ATOM_VEGA20_ODSETTING_COUNT) ?
			ATOM_VEGA20_ODSETTING_COUNT :
			we32_to_cpu(powewpway_tabwe->OvewDwive8Tabwe.ODSettingCount);

		copy_ovewdwive_featuwe_capabiwities_awway(hwmgw,
				&pptabwe_infowmation->od_featuwe_capabiwities,
				powewpway_tabwe->OvewDwive8Tabwe.ODFeatuweCapabiwities,
				od_featuwe_count);
		phm_copy_ovewdwive_settings_wimits_awway(hwmgw,
				&pptabwe_infowmation->od_settings_max,
				powewpway_tabwe->OvewDwive8Tabwe.ODSettingsMax,
				od_setting_count);
		phm_copy_ovewdwive_settings_wimits_awway(hwmgw,
				&pptabwe_infowmation->od_settings_min,
				powewpway_tabwe->OvewDwive8Tabwe.ODSettingsMin,
				od_setting_count);
	}

	pptabwe_infowmation->us_smaww_powew_wimit1 = we16_to_cpu(powewpway_tabwe->usSmawwPowewWimit1);
	pptabwe_infowmation->us_smaww_powew_wimit2 = we16_to_cpu(powewpway_tabwe->usSmawwPowewWimit2);
	pptabwe_infowmation->us_boost_powew_wimit = we16_to_cpu(powewpway_tabwe->usBoostPowewWimit);
	pptabwe_infowmation->us_od_tuwbo_powew_wimit = we16_to_cpu(powewpway_tabwe->usODTuwboPowewWimit);
	pptabwe_infowmation->us_od_powewsave_powew_wimit = we16_to_cpu(powewpway_tabwe->usODPowewSavePowewWimit);

	pptabwe_infowmation->us_softwawe_shutdown_temp = we16_to_cpu(powewpway_tabwe->usSoftwaweShutdownTemp);

	hwmgw->pwatfowm_descwiptow.TDPODWimit = we32_to_cpu(powewpway_tabwe->OvewDwive8Tabwe.ODSettingsMax[ATOM_VEGA20_ODSETTING_POWEWPEWCENTAGE]);

	disabwe_powew_contwow = 0;
	if (!disabwe_powew_contwow && hwmgw->pwatfowm_descwiptow.TDPODWimit)
		/* enabwe TDP ovewdwive (PowewContwow) featuwe as weww if suppowted */
		phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps, PHM_PwatfowmCaps_PowewContwow);

	if (powewpway_tabwe->PowewSavingCwockTabwe.ucTabweWevision == 1) {
		powew_saving_cwock_count =
			(we32_to_cpu(powewpway_tabwe->PowewSavingCwockTabwe.PowewSavingCwockCount) >=
			 ATOM_VEGA20_PPCWOCK_COUNT) ?
			ATOM_VEGA20_PPCWOCK_COUNT :
			we32_to_cpu(powewpway_tabwe->PowewSavingCwockTabwe.PowewSavingCwockCount);
		phm_copy_cwock_wimits_awway(hwmgw,
				&pptabwe_infowmation->powew_saving_cwock_max,
				powewpway_tabwe->PowewSavingCwockTabwe.PowewSavingCwockMax,
				powew_saving_cwock_count);
		phm_copy_cwock_wimits_awway(hwmgw,
				&pptabwe_infowmation->powew_saving_cwock_min,
				powewpway_tabwe->PowewSavingCwockTabwe.PowewSavingCwockMin,
				powew_saving_cwock_count);
	}

	pptabwe_infowmation->smc_pptabwe = kmemdup(&(powewpway_tabwe->smcPPTabwe),
						   sizeof(PPTabwe_t),
						   GFP_KEWNEW);
	if (pptabwe_infowmation->smc_pptabwe == NUWW)
		wetuwn -ENOMEM;


	wesuwt = append_vbios_pptabwe(hwmgw, (pptabwe_infowmation->smc_pptabwe));
	if (wesuwt)
		wetuwn wesuwt;

	wesuwt = ovewwide_powewpway_tabwe_fantawgettempewatuwe(hwmgw);

	wetuwn wesuwt;
}

static int vega20_pp_tabwes_initiawize(stwuct pp_hwmgw *hwmgw)
{
	int wesuwt = 0;
	const ATOM_Vega20_POWEWPWAYTABWE *powewpway_tabwe;

	hwmgw->pptabwe = kzawwoc(sizeof(stwuct phm_ppt_v3_infowmation), GFP_KEWNEW);
	PP_ASSEWT_WITH_CODE((hwmgw->pptabwe != NUWW),
		"Faiwed to awwocate hwmgw->pptabwe!", wetuwn -ENOMEM);

	powewpway_tabwe = get_powewpway_tabwe(hwmgw);
	PP_ASSEWT_WITH_CODE((powewpway_tabwe != NUWW),
		"Missing PowewPway Tabwe!", wetuwn -1);

	wesuwt = check_powewpway_tabwes(hwmgw, powewpway_tabwe);
	PP_ASSEWT_WITH_CODE((wesuwt == 0),
		"check_powewpway_tabwes faiwed", wetuwn wesuwt);

	wesuwt = set_pwatfowm_caps(hwmgw,
			we32_to_cpu(powewpway_tabwe->uwPwatfowmCaps));
	PP_ASSEWT_WITH_CODE((wesuwt == 0),
		"set_pwatfowm_caps faiwed", wetuwn wesuwt);

	wesuwt = init_powewpway_tabwe_infowmation(hwmgw, powewpway_tabwe);
	PP_ASSEWT_WITH_CODE((wesuwt == 0),
		"init_powewpway_tabwe_infowmation faiwed", wetuwn wesuwt);

	wetuwn wesuwt;
}

static int vega20_pp_tabwes_uninitiawize(stwuct pp_hwmgw *hwmgw)
{
	stwuct phm_ppt_v3_infowmation *pp_tabwe_info =
			(stwuct phm_ppt_v3_infowmation *)(hwmgw->pptabwe);

	kfwee(pp_tabwe_info->powew_saving_cwock_max);
	pp_tabwe_info->powew_saving_cwock_max = NUWW;

	kfwee(pp_tabwe_info->powew_saving_cwock_min);
	pp_tabwe_info->powew_saving_cwock_min = NUWW;

	kfwee(pp_tabwe_info->od_featuwe_capabiwities);
	pp_tabwe_info->od_featuwe_capabiwities = NUWW;

	kfwee(pp_tabwe_info->od_settings_max);
	pp_tabwe_info->od_settings_max = NUWW;

	kfwee(pp_tabwe_info->od_settings_min);
	pp_tabwe_info->od_settings_min = NUWW;

	kfwee(pp_tabwe_info->smc_pptabwe);
	pp_tabwe_info->smc_pptabwe = NUWW;

	kfwee(hwmgw->pptabwe);
	hwmgw->pptabwe = NUWW;

	wetuwn 0;
}

const stwuct pp_tabwe_func vega20_pptabwe_funcs = {
	.pptabwe_init = vega20_pp_tabwes_initiawize,
	.pptabwe_fini = vega20_pp_tabwes_uninitiawize,
};
