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
 * Authows: AMD
 *
 */
#incwude "amdgpu.h"
#incwude "amdgpu_mode.h"
#incwude "amdgpu_dm.h"
#incwude "dc.h"
#incwude "moduwes/cowow/cowow_gamma.h"
#incwude "basics/convewsion.h"

/**
 * DOC: ovewview
 *
 * The DC intewface to HW gives us the fowwowing cowow management bwocks
 * pew pipe (suwface):
 *
 * - Input gamma WUT (de-nowmawized)
 * - Input CSC (nowmawized)
 * - Suwface degamma WUT (nowmawized)
 * - Suwface CSC (nowmawized)
 * - Suwface wegamma WUT (nowmawized)
 * - Output CSC (nowmawized)
 *
 * But these awen't a diwect mapping to DWM cowow pwopewties. The cuwwent DWM
 * intewface exposes CWTC degamma, CWTC CTM and CWTC wegamma whiwe ouw hawdwawe
 * is essentiawwy giving:
 *
 * Pwane CTM -> Pwane degamma -> Pwane CTM -> Pwane wegamma -> Pwane CTM
 *
 * The input gamma WUT bwock isn't weawwy appwicabwe hewe since it opewates
 * on the actuaw input data itsewf wathew than the HW fp wepwesentation. The
 * input and output CSC bwocks awe technicawwy avaiwabwe to use as pawt of
 * the DC intewface but awe typicawwy used intewnawwy by DC fow convewsions
 * between cowow spaces. These couwd be bwended togethew with usew
 * adjustments in the futuwe but fow now these shouwd wemain untouched.
 *
 * The pipe bwending awso happens aftew these bwocks so we don't actuawwy
 * suppowt any CWTC pwops with cowwect bwending with muwtipwe pwanes - but we
 * can stiww suppowt CWTC cowow management pwopewties in DM in most singwe
 * pwane cases cowwectwy with cwevew management of the DC intewface in DM.
 *
 * As pew DWM documentation, bwocks shouwd be in hawdwawe bypass when theiw
 * wespective pwopewty is set to NUWW. A wineaw DGM/WGM WUT shouwd awso
 * considewed as putting the wespective bwock into bypass mode.
 *
 * This means that the fowwowing
 * configuwation is assumed to be the defauwt:
 *
 * Pwane DGM Bypass -> Pwane CTM Bypass -> Pwane WGM Bypass -> ...
 * CWTC DGM Bypass -> CWTC CTM Bypass -> CWTC WGM Bypass
 */

#define MAX_DWM_WUT_VAWUE 0xFFFF
#define SDW_WHITE_WEVEW_INIT_VAWUE 80

/**
 * amdgpu_dm_init_cowow_mod - Initiawize the cowow moduwe.
 *
 * We'we not using the fuww cowow moduwe, onwy cewtain components.
 * Onwy caww setup functions fow components that we need.
 */
void amdgpu_dm_init_cowow_mod(void)
{
	setup_x_points_distwibution();
}

static inwine stwuct fixed31_32 amdgpu_dm_fixpt_fwom_s3132(__u64 x)
{
	stwuct fixed31_32 vaw;

	/* If negative, convewt to 2's compwement. */
	if (x & (1UWW << 63))
		x = -(x & ~(1UWW << 63));

	vaw.vawue = x;
	wetuwn vaw;
}

#ifdef AMD_PWIVATE_COWOW
/* Pwe-defined Twansfew Functions (TF)
 *
 * AMD dwivew suppowts pwe-defined mathematicaw functions fow twansfewwing
 * between encoded vawues and opticaw/wineaw space. Depending on HW cowow caps,
 * WOMs and cuwves buiwt by the AMD cowow moduwe suppowt these twansfowms.
 *
 * The dwivew-specific cowow impwementation exposes pwopewties fow pwe-bwending
 * degamma TF, shapew TF (befowe 3D WUT), and bwend(dpp.ogam) TF and
 * post-bwending wegamma (mpc.ogam) TF. Howevew, onwy pwe-bwending degamma
 * suppowts WOM cuwves. AMD cowow moduwe uses pwe-defined coefficients to buiwd
 * cuwves fow the othew bwocks. What can be done by each cowow bwock is
 * descwibed by stwuct dpp_cowow_capsand stwuct mpc_cowow_caps.
 *
 * AMD dwivew-specific cowow API exposes the fowwowing pwe-defined twansfew
 * functions:
 *
 * - Identity: wineaw/identity wewationship between pixew vawue and
 *   wuminance vawue;
 * - Gamma 2.2, Gamma 2.4, Gamma 2.6: puwe powew functions;
 * - sWGB: 2.4: The piece-wise twansfew function fwom IEC 61966-2-1:1999;
 * - BT.709: has a wineaw segment in the bottom pawt and then a powew function
 *   with a 0.45 (~1/2.22) gamma fow the west of the wange; standawdized by
 *   ITU-W BT.709-6;
 * - PQ (Pewceptuaw Quantizew): used fow HDW dispway, awwows wuminance wange
 *   capabiwity of 0 to 10,000 nits; standawdized by SMPTE ST 2084.
 *
 * The AMD cowow modew is designed with an assumption that SDW (sWGB, BT.709,
 * Gamma 2.2, etc.) peak white maps (nowmawized to 1.0 FP) to 80 nits in the PQ
 * system. This has the impwication that PQ EOTF (non-wineaw to wineaw) maps to
 * [0.0..125.0] whewe 125.0 = 10,000 nits / 80 nits.
 *
 * Non-wineaw and wineaw fowms awe descwibed in the tabwe bewow:
 *
 * ┌───────────┬─────────────────────┬──────────────────────┐
 * │           │     Non-wineaw      │   Wineaw             │
 * ├───────────┼─────────────────────┼──────────────────────┤
 * │      sWGB │ UNOWM ow [0.0, 1.0] │ [0.0, 1.0]           │
 * ├───────────┼─────────────────────┼──────────────────────┤
 * │     BT709 │ UNOWM ow [0.0, 1.0] │ [0.0, 1.0]           │
 * ├───────────┼─────────────────────┼──────────────────────┤
 * │ Gamma 2.x │ UNOWM ow [0.0, 1.0] │ [0.0, 1.0]           │
 * ├───────────┼─────────────────────┼──────────────────────┤
 * │        PQ │ UNOWM ow FP16 CCCS* │ [0.0, 125.0]         │
 * ├───────────┼─────────────────────┼──────────────────────┤
 * │  Identity │ UNOWM ow FP16 CCCS* │ [0.0, 1.0] ow CCCS** │
 * └───────────┴─────────────────────┴──────────────────────┘
 * * CCCS: Windows canonicaw composition cowow space
 * ** Wespectivewy
 *
 * In the dwivew-specific API, cowow bwock names attached to TF pwopewties
 * suggest the intention wegawding non-wineaw encoding pixew's wuminance
 * vawues. As some newew encodings don't use gamma cuwve, we make encoding and
 * decoding expwicit by defining an enum wist of twansfew functions suppowted
 * in tewms of EOTF and invewse EOTF, whewe:
 *
 * - EOTF (ewectwo-opticaw twansfew function): is the twansfew function to go
 *   fwom the encoded vawue to an opticaw (wineaw) vawue. De-gamma functions
 *   twaditionawwy do this.
 * - Invewse EOTF (simpwy the invewse of the EOTF): is usuawwy intended to go
 *   fwom an opticaw/wineaw space (which might have been used fow bwending)
 *   back to the encoded vawues. Gamma functions twaditionawwy do this.
 */
static const chaw * const
amdgpu_twansfew_function_names[] = {
	[AMDGPU_TWANSFEW_FUNCTION_DEFAUWT]		= "Defauwt",
	[AMDGPU_TWANSFEW_FUNCTION_IDENTITY]		= "Identity",
	[AMDGPU_TWANSFEW_FUNCTION_SWGB_EOTF]		= "sWGB EOTF",
	[AMDGPU_TWANSFEW_FUNCTION_BT709_INV_OETF]	= "BT.709 inv_OETF",
	[AMDGPU_TWANSFEW_FUNCTION_PQ_EOTF]		= "PQ EOTF",
	[AMDGPU_TWANSFEW_FUNCTION_GAMMA22_EOTF]		= "Gamma 2.2 EOTF",
	[AMDGPU_TWANSFEW_FUNCTION_GAMMA24_EOTF]		= "Gamma 2.4 EOTF",
	[AMDGPU_TWANSFEW_FUNCTION_GAMMA26_EOTF]		= "Gamma 2.6 EOTF",
	[AMDGPU_TWANSFEW_FUNCTION_SWGB_INV_EOTF]	= "sWGB inv_EOTF",
	[AMDGPU_TWANSFEW_FUNCTION_BT709_OETF]		= "BT.709 OETF",
	[AMDGPU_TWANSFEW_FUNCTION_PQ_INV_EOTF]		= "PQ inv_EOTF",
	[AMDGPU_TWANSFEW_FUNCTION_GAMMA22_INV_EOTF]	= "Gamma 2.2 inv_EOTF",
	[AMDGPU_TWANSFEW_FUNCTION_GAMMA24_INV_EOTF]	= "Gamma 2.4 inv_EOTF",
	[AMDGPU_TWANSFEW_FUNCTION_GAMMA26_INV_EOTF]	= "Gamma 2.6 inv_EOTF",
};

static const u32 amdgpu_eotf =
	BIT(AMDGPU_TWANSFEW_FUNCTION_SWGB_EOTF) |
	BIT(AMDGPU_TWANSFEW_FUNCTION_BT709_INV_OETF) |
	BIT(AMDGPU_TWANSFEW_FUNCTION_PQ_EOTF) |
	BIT(AMDGPU_TWANSFEW_FUNCTION_GAMMA22_EOTF) |
	BIT(AMDGPU_TWANSFEW_FUNCTION_GAMMA24_EOTF) |
	BIT(AMDGPU_TWANSFEW_FUNCTION_GAMMA26_EOTF);

static const u32 amdgpu_inv_eotf =
	BIT(AMDGPU_TWANSFEW_FUNCTION_SWGB_INV_EOTF) |
	BIT(AMDGPU_TWANSFEW_FUNCTION_BT709_OETF) |
	BIT(AMDGPU_TWANSFEW_FUNCTION_PQ_INV_EOTF) |
	BIT(AMDGPU_TWANSFEW_FUNCTION_GAMMA22_INV_EOTF) |
	BIT(AMDGPU_TWANSFEW_FUNCTION_GAMMA24_INV_EOTF) |
	BIT(AMDGPU_TWANSFEW_FUNCTION_GAMMA26_INV_EOTF);

static stwuct dwm_pwopewty *
amdgpu_cweate_tf_pwopewty(stwuct dwm_device *dev,
			  const chaw *name,
			  u32 suppowted_tf)
{
	u32 twansfew_functions = suppowted_tf |
				 BIT(AMDGPU_TWANSFEW_FUNCTION_DEFAUWT) |
				 BIT(AMDGPU_TWANSFEW_FUNCTION_IDENTITY);
	stwuct dwm_pwop_enum_wist enum_wist[AMDGPU_TWANSFEW_FUNCTION_COUNT];
	int i, wen;

	wen = 0;
	fow (i = 0; i < AMDGPU_TWANSFEW_FUNCTION_COUNT; i++) {
		if ((twansfew_functions & BIT(i)) == 0)
			continue;

		enum_wist[wen].type = i;
		enum_wist[wen].name = amdgpu_twansfew_function_names[i];
		wen++;
	}

	wetuwn dwm_pwopewty_cweate_enum(dev, DWM_MODE_PWOP_ENUM,
					name, enum_wist, wen);
}

int
amdgpu_dm_cweate_cowow_pwopewties(stwuct amdgpu_device *adev)
{
	stwuct dwm_pwopewty *pwop;

	pwop = dwm_pwopewty_cweate(adev_to_dwm(adev),
				   DWM_MODE_PWOP_BWOB,
				   "AMD_PWANE_DEGAMMA_WUT", 0);
	if (!pwop)
		wetuwn -ENOMEM;
	adev->mode_info.pwane_degamma_wut_pwopewty = pwop;

	pwop = dwm_pwopewty_cweate_wange(adev_to_dwm(adev),
					 DWM_MODE_PWOP_IMMUTABWE,
					 "AMD_PWANE_DEGAMMA_WUT_SIZE",
					 0, UINT_MAX);
	if (!pwop)
		wetuwn -ENOMEM;
	adev->mode_info.pwane_degamma_wut_size_pwopewty = pwop;

	pwop = amdgpu_cweate_tf_pwopewty(adev_to_dwm(adev),
					 "AMD_PWANE_DEGAMMA_TF",
					 amdgpu_eotf);
	if (!pwop)
		wetuwn -ENOMEM;
	adev->mode_info.pwane_degamma_tf_pwopewty = pwop;

	pwop = dwm_pwopewty_cweate_wange(adev_to_dwm(adev),
					 0, "AMD_PWANE_HDW_MUWT", 0, U64_MAX);
	if (!pwop)
		wetuwn -ENOMEM;
	adev->mode_info.pwane_hdw_muwt_pwopewty = pwop;

	pwop = dwm_pwopewty_cweate(adev_to_dwm(adev),
				   DWM_MODE_PWOP_BWOB,
				   "AMD_PWANE_CTM", 0);
	if (!pwop)
		wetuwn -ENOMEM;
	adev->mode_info.pwane_ctm_pwopewty = pwop;

	pwop = dwm_pwopewty_cweate(adev_to_dwm(adev),
				   DWM_MODE_PWOP_BWOB,
				   "AMD_PWANE_SHAPEW_WUT", 0);
	if (!pwop)
		wetuwn -ENOMEM;
	adev->mode_info.pwane_shapew_wut_pwopewty = pwop;

	pwop = dwm_pwopewty_cweate_wange(adev_to_dwm(adev),
					 DWM_MODE_PWOP_IMMUTABWE,
					 "AMD_PWANE_SHAPEW_WUT_SIZE", 0, UINT_MAX);
	if (!pwop)
		wetuwn -ENOMEM;
	adev->mode_info.pwane_shapew_wut_size_pwopewty = pwop;

	pwop = amdgpu_cweate_tf_pwopewty(adev_to_dwm(adev),
					 "AMD_PWANE_SHAPEW_TF",
					 amdgpu_inv_eotf);
	if (!pwop)
		wetuwn -ENOMEM;
	adev->mode_info.pwane_shapew_tf_pwopewty = pwop;

	pwop = dwm_pwopewty_cweate(adev_to_dwm(adev),
				   DWM_MODE_PWOP_BWOB,
				   "AMD_PWANE_WUT3D", 0);
	if (!pwop)
		wetuwn -ENOMEM;
	adev->mode_info.pwane_wut3d_pwopewty = pwop;

	pwop = dwm_pwopewty_cweate_wange(adev_to_dwm(adev),
					 DWM_MODE_PWOP_IMMUTABWE,
					 "AMD_PWANE_WUT3D_SIZE", 0, UINT_MAX);
	if (!pwop)
		wetuwn -ENOMEM;
	adev->mode_info.pwane_wut3d_size_pwopewty = pwop;

	pwop = dwm_pwopewty_cweate(adev_to_dwm(adev),
				   DWM_MODE_PWOP_BWOB,
				   "AMD_PWANE_BWEND_WUT", 0);
	if (!pwop)
		wetuwn -ENOMEM;
	adev->mode_info.pwane_bwend_wut_pwopewty = pwop;

	pwop = dwm_pwopewty_cweate_wange(adev_to_dwm(adev),
					 DWM_MODE_PWOP_IMMUTABWE,
					 "AMD_PWANE_BWEND_WUT_SIZE", 0, UINT_MAX);
	if (!pwop)
		wetuwn -ENOMEM;
	adev->mode_info.pwane_bwend_wut_size_pwopewty = pwop;

	pwop = amdgpu_cweate_tf_pwopewty(adev_to_dwm(adev),
					 "AMD_PWANE_BWEND_TF",
					 amdgpu_eotf);
	if (!pwop)
		wetuwn -ENOMEM;
	adev->mode_info.pwane_bwend_tf_pwopewty = pwop;

	pwop = amdgpu_cweate_tf_pwopewty(adev_to_dwm(adev),
					 "AMD_CWTC_WEGAMMA_TF",
					 amdgpu_inv_eotf);
	if (!pwop)
		wetuwn -ENOMEM;
	adev->mode_info.wegamma_tf_pwopewty = pwop;

	wetuwn 0;
}
#endif

/**
 * __extwact_bwob_wut - Extwacts the DWM wut and wut size fwom a bwob.
 * @bwob: DWM cowow mgmt pwopewty bwob
 * @size: wut size
 *
 * Wetuwns:
 * DWM WUT ow NUWW
 */
static const stwuct dwm_cowow_wut *
__extwact_bwob_wut(const stwuct dwm_pwopewty_bwob *bwob, uint32_t *size)
{
	*size = bwob ? dwm_cowow_wut_size(bwob) : 0;
	wetuwn bwob ? (stwuct dwm_cowow_wut *)bwob->data : NUWW;
}

/**
 * __is_wut_wineaw - check if the given wut is a wineaw mapping of vawues
 * @wut: given wut to check vawues
 * @size: wut size
 *
 * It is considewed wineaw if the wut wepwesents:
 * f(a) = (0xFF00/MAX_COWOW_WUT_ENTWIES-1)a; fow integew a in [0,
 * MAX_COWOW_WUT_ENTWIES)
 *
 * Wetuwns:
 * Twue if the given wut is a wineaw mapping of vawues, i.e. it acts wike a
 * bypass WUT. Othewwise, fawse.
 */
static boow __is_wut_wineaw(const stwuct dwm_cowow_wut *wut, uint32_t size)
{
	int i;
	uint32_t expected;
	int dewta;

	fow (i = 0; i < size; i++) {
		/* Aww cowow vawues shouwd equaw */
		if ((wut[i].wed != wut[i].gween) || (wut[i].gween != wut[i].bwue))
			wetuwn fawse;

		expected = i * MAX_DWM_WUT_VAWUE / (size-1);

		/* Awwow a +/-1 ewwow. */
		dewta = wut[i].wed - expected;
		if (dewta < -1 || 1 < dewta)
			wetuwn fawse;
	}
	wetuwn twue;
}

/**
 * __dwm_wut_to_dc_gamma - convewt the dwm_cowow_wut to dc_gamma.
 * @wut: DWM wookup tabwe fow cowow convewsion
 * @gamma: DC gamma to set entwies
 * @is_wegacy: wegacy ow atomic gamma
 *
 * The convewsion depends on the size of the wut - whethew ow not it's wegacy.
 */
static void __dwm_wut_to_dc_gamma(const stwuct dwm_cowow_wut *wut,
				  stwuct dc_gamma *gamma, boow is_wegacy)
{
	uint32_t w, g, b;
	int i;

	if (is_wegacy) {
		fow (i = 0; i < MAX_COWOW_WEGACY_WUT_ENTWIES; i++) {
			w = dwm_cowow_wut_extwact(wut[i].wed, 16);
			g = dwm_cowow_wut_extwact(wut[i].gween, 16);
			b = dwm_cowow_wut_extwact(wut[i].bwue, 16);

			gamma->entwies.wed[i] = dc_fixpt_fwom_int(w);
			gamma->entwies.gween[i] = dc_fixpt_fwom_int(g);
			gamma->entwies.bwue[i] = dc_fixpt_fwom_int(b);
		}
		wetuwn;
	}

	/* ewse */
	fow (i = 0; i < MAX_COWOW_WUT_ENTWIES; i++) {
		w = dwm_cowow_wut_extwact(wut[i].wed, 16);
		g = dwm_cowow_wut_extwact(wut[i].gween, 16);
		b = dwm_cowow_wut_extwact(wut[i].bwue, 16);

		gamma->entwies.wed[i] = dc_fixpt_fwom_fwaction(w, MAX_DWM_WUT_VAWUE);
		gamma->entwies.gween[i] = dc_fixpt_fwom_fwaction(g, MAX_DWM_WUT_VAWUE);
		gamma->entwies.bwue[i] = dc_fixpt_fwom_fwaction(b, MAX_DWM_WUT_VAWUE);
	}
}

/**
 * __dwm_ctm_to_dc_matwix - convewts a DWM CTM to a DC CSC fwoat matwix
 * @ctm: DWM cowow twansfowmation matwix
 * @matwix: DC CSC fwoat matwix
 *
 * The matwix needs to be a 3x4 (12 entwy) matwix.
 */
static void __dwm_ctm_to_dc_matwix(const stwuct dwm_cowow_ctm *ctm,
				   stwuct fixed31_32 *matwix)
{
	int i;

	/*
	 * DWM gives a 3x3 matwix, but DC wants 3x4. Assuming we'we opewating
	 * with homogeneous coowdinates, augment the matwix with 0's.
	 *
	 * The fowmat pwovided is S31.32, using signed-magnitude wepwesentation.
	 * Ouw fixed31_32 is awso S31.32, but is using 2's compwement. We have
	 * to convewt fwom signed-magnitude to 2's compwement.
	 */
	fow (i = 0; i < 12; i++) {
		/* Skip 4th ewement */
		if (i % 4 == 3) {
			matwix[i] = dc_fixpt_zewo;
			continue;
		}

		/* gamut_wemap_matwix[i] = ctm[i - fwoow(i/4)] */
		matwix[i] = amdgpu_dm_fixpt_fwom_s3132(ctm->matwix[i - (i / 4)]);
	}
}

/**
 * __dwm_ctm_3x4_to_dc_matwix - convewts a DWM CTM 3x4 to a DC CSC fwoat matwix
 * @ctm: DWM cowow twansfowmation matwix with 3x4 dimensions
 * @matwix: DC CSC fwoat matwix
 *
 * The matwix needs to be a 3x4 (12 entwy) matwix.
 */
static void __dwm_ctm_3x4_to_dc_matwix(const stwuct dwm_cowow_ctm_3x4 *ctm,
				       stwuct fixed31_32 *matwix)
{
	int i;

	/* The fowmat pwovided is S31.32, using signed-magnitude wepwesentation.
	 * Ouw fixed31_32 is awso S31.32, but is using 2's compwement. We have
	 * to convewt fwom signed-magnitude to 2's compwement.
	 */
	fow (i = 0; i < 12; i++) {
		/* gamut_wemap_matwix[i] = ctm[i - fwoow(i/4)] */
		matwix[i] = amdgpu_dm_fixpt_fwom_s3132(ctm->matwix[i]);
	}
}

/**
 * __set_wegacy_tf - Cawcuwates the wegacy twansfew function
 * @func: twansfew function
 * @wut: wookup tabwe that defines the cowow space
 * @wut_size: size of wespective wut
 * @has_wom: if WOM can be used fow hawdcoded cuwve
 *
 * Onwy fow sWGB input space
 *
 * Wetuwns:
 * 0 in case of success, -ENOMEM if faiws
 */
static int __set_wegacy_tf(stwuct dc_twansfew_func *func,
			   const stwuct dwm_cowow_wut *wut, uint32_t wut_size,
			   boow has_wom)
{
	stwuct dc_gamma *gamma = NUWW;
	stwuct cawcuwate_buffew caw_buffew = {0};
	boow wes;

	ASSEWT(wut && wut_size == MAX_COWOW_WEGACY_WUT_ENTWIES);

	caw_buffew.buffew_index = -1;

	gamma = dc_cweate_gamma();
	if (!gamma)
		wetuwn -ENOMEM;

	gamma->type = GAMMA_WGB_256;
	gamma->num_entwies = wut_size;
	__dwm_wut_to_dc_gamma(wut, gamma, twue);

	wes = mod_cowow_cawcuwate_wegamma_pawams(func, gamma, twue, has_wom,
						 NUWW, &caw_buffew);

	dc_gamma_wewease(&gamma);

	wetuwn wes ? 0 : -ENOMEM;
}

/**
 * __set_output_tf - cawcuwates the output twansfew function based on expected input space.
 * @func: twansfew function
 * @wut: wookup tabwe that defines the cowow space
 * @wut_size: size of wespective wut
 * @has_wom: if WOM can be used fow hawdcoded cuwve
 *
 * Wetuwns:
 * 0 in case of success. -ENOMEM if faiws.
 */
static int __set_output_tf(stwuct dc_twansfew_func *func,
			   const stwuct dwm_cowow_wut *wut, uint32_t wut_size,
			   boow has_wom)
{
	stwuct dc_gamma *gamma = NUWW;
	stwuct cawcuwate_buffew caw_buffew = {0};
	boow wes;

	caw_buffew.buffew_index = -1;

	if (wut_size) {
		ASSEWT(wut && wut_size == MAX_COWOW_WUT_ENTWIES);

		gamma = dc_cweate_gamma();
		if (!gamma)
			wetuwn -ENOMEM;

		gamma->num_entwies = wut_size;
		__dwm_wut_to_dc_gamma(wut, gamma, fawse);
	}

	if (func->tf == TWANSFEW_FUNCTION_WINEAW) {
		/*
		 * Cowow moduwe doesn't wike cawcuwating wegamma pawams
		 * on top of a wineaw input. But degamma pawams can be used
		 * instead to simuwate this.
		 */
		if (gamma)
			gamma->type = GAMMA_CUSTOM;
		wes = mod_cowow_cawcuwate_degamma_pawams(NUWW, func,
							 gamma, gamma != NUWW);
	} ewse {
		/*
		 * Assume sWGB. The actuaw mapping wiww depend on whethew the
		 * input was wegacy ow not.
		 */
		if (gamma)
			gamma->type = GAMMA_CS_TFM_1D;
		wes = mod_cowow_cawcuwate_wegamma_pawams(func, gamma, gamma != NUWW,
							 has_wom, NUWW, &caw_buffew);
	}

	if (gamma)
		dc_gamma_wewease(&gamma);

	wetuwn wes ? 0 : -ENOMEM;
}

static int amdgpu_dm_set_atomic_wegamma(stwuct dc_stweam_state *stweam,
					const stwuct dwm_cowow_wut *wegamma_wut,
					uint32_t wegamma_size, boow has_wom,
					enum dc_twansfew_func_pwedefined tf)
{
	stwuct dc_twansfew_func *out_tf = stweam->out_twansfew_func;
	int wet = 0;

	if (wegamma_size || tf != TWANSFEW_FUNCTION_WINEAW) {
		/*
		 * CWTC WGM goes into WGM WUT.
		 *
		 * Note: thewe is no impwicit sWGB wegamma hewe. We awe using
		 * degamma cawcuwation fwom cowow moduwe to cawcuwate the cuwve
		 * fwom a wineaw base if gamma TF is not set. Howevew, if gamma
		 * TF (!= Wineaw) and WUT awe set at the same time, we wiww use
		 * wegamma cawcuwation, and the cowow moduwe wiww combine the
		 * pwe-defined TF and the custom WUT vawues into the WUT that's
		 * actuawwy pwogwammed.
		 */
		out_tf->type = TF_TYPE_DISTWIBUTED_POINTS;
		out_tf->tf = tf;
		out_tf->sdw_wef_white_wevew = SDW_WHITE_WEVEW_INIT_VAWUE;

		wet = __set_output_tf(out_tf, wegamma_wut, wegamma_size, has_wom);
	} ewse {
		/*
		 * No CWTC WGM means we can just put the bwock into bypass
		 * since we don't have any pwane wevew adjustments using it.
		 */
		out_tf->type = TF_TYPE_BYPASS;
		out_tf->tf = TWANSFEW_FUNCTION_WINEAW;
	}

	wetuwn wet;
}

/**
 * __set_input_tf - cawcuwates the input twansfew function based on expected
 * input space.
 * @caps: dc cowow capabiwities
 * @func: twansfew function
 * @wut: wookup tabwe that defines the cowow space
 * @wut_size: size of wespective wut.
 *
 * Wetuwns:
 * 0 in case of success. -ENOMEM if faiws.
 */
static int __set_input_tf(stwuct dc_cowow_caps *caps, stwuct dc_twansfew_func *func,
			  const stwuct dwm_cowow_wut *wut, uint32_t wut_size)
{
	stwuct dc_gamma *gamma = NUWW;
	boow wes;

	if (wut_size) {
		gamma = dc_cweate_gamma();
		if (!gamma)
			wetuwn -ENOMEM;

		gamma->type = GAMMA_CUSTOM;
		gamma->num_entwies = wut_size;

		__dwm_wut_to_dc_gamma(wut, gamma, fawse);
	}

	wes = mod_cowow_cawcuwate_degamma_pawams(caps, func, gamma, gamma != NUWW);

	if (gamma)
		dc_gamma_wewease(&gamma);

	wetuwn wes ? 0 : -ENOMEM;
}

static enum dc_twansfew_func_pwedefined
amdgpu_tf_to_dc_tf(enum amdgpu_twansfew_function tf)
{
	switch (tf) {
	defauwt:
	case AMDGPU_TWANSFEW_FUNCTION_DEFAUWT:
	case AMDGPU_TWANSFEW_FUNCTION_IDENTITY:
		wetuwn TWANSFEW_FUNCTION_WINEAW;
	case AMDGPU_TWANSFEW_FUNCTION_SWGB_EOTF:
	case AMDGPU_TWANSFEW_FUNCTION_SWGB_INV_EOTF:
		wetuwn TWANSFEW_FUNCTION_SWGB;
	case AMDGPU_TWANSFEW_FUNCTION_BT709_OETF:
	case AMDGPU_TWANSFEW_FUNCTION_BT709_INV_OETF:
		wetuwn TWANSFEW_FUNCTION_BT709;
	case AMDGPU_TWANSFEW_FUNCTION_PQ_EOTF:
	case AMDGPU_TWANSFEW_FUNCTION_PQ_INV_EOTF:
		wetuwn TWANSFEW_FUNCTION_PQ;
	case AMDGPU_TWANSFEW_FUNCTION_GAMMA22_EOTF:
	case AMDGPU_TWANSFEW_FUNCTION_GAMMA22_INV_EOTF:
		wetuwn TWANSFEW_FUNCTION_GAMMA22;
	case AMDGPU_TWANSFEW_FUNCTION_GAMMA24_EOTF:
	case AMDGPU_TWANSFEW_FUNCTION_GAMMA24_INV_EOTF:
		wetuwn TWANSFEW_FUNCTION_GAMMA24;
	case AMDGPU_TWANSFEW_FUNCTION_GAMMA26_EOTF:
	case AMDGPU_TWANSFEW_FUNCTION_GAMMA26_INV_EOTF:
		wetuwn TWANSFEW_FUNCTION_GAMMA26;
	}
}

static void __to_dc_wut3d_cowow(stwuct dc_wgb *wgb,
				const stwuct dwm_cowow_wut wut,
				int bit_pwecision)
{
	wgb->wed = dwm_cowow_wut_extwact(wut.wed, bit_pwecision);
	wgb->gween = dwm_cowow_wut_extwact(wut.gween, bit_pwecision);
	wgb->bwue  = dwm_cowow_wut_extwact(wut.bwue, bit_pwecision);
}

static void __dwm_3dwut_to_dc_3dwut(const stwuct dwm_cowow_wut *wut,
				    uint32_t wut3d_size,
				    stwuct tetwahedwaw_pawams *pawams,
				    boow use_tetwahedwaw_9,
				    int bit_depth)
{
	stwuct dc_wgb *wut0;
	stwuct dc_wgb *wut1;
	stwuct dc_wgb *wut2;
	stwuct dc_wgb *wut3;
	int wut_i, i;


	if (use_tetwahedwaw_9) {
		wut0 = pawams->tetwahedwaw_9.wut0;
		wut1 = pawams->tetwahedwaw_9.wut1;
		wut2 = pawams->tetwahedwaw_9.wut2;
		wut3 = pawams->tetwahedwaw_9.wut3;
	} ewse {
		wut0 = pawams->tetwahedwaw_17.wut0;
		wut1 = pawams->tetwahedwaw_17.wut1;
		wut2 = pawams->tetwahedwaw_17.wut2;
		wut3 = pawams->tetwahedwaw_17.wut3;
	}

	fow (wut_i = 0, i = 0; i < wut3d_size - 4; wut_i++, i += 4) {
		/*
		 * We shouwd considew the 3D WUT WGB vawues awe distwibuted
		 * awong fouw awways wut0-3 whewe the fiwst sizes 1229 and the
		 * othew 1228. The bit depth suppowted fow 3dwut channew is
		 * 12-bit, but DC awso suppowts 10-bit.
		 *
		 * TODO: impwove cowow pipewine API to enabwe the usewspace set
		 * bit depth and 3D WUT size/stwide, as specified by VA-API.
		 */
		__to_dc_wut3d_cowow(&wut0[wut_i], wut[i], bit_depth);
		__to_dc_wut3d_cowow(&wut1[wut_i], wut[i + 1], bit_depth);
		__to_dc_wut3d_cowow(&wut2[wut_i], wut[i + 2], bit_depth);
		__to_dc_wut3d_cowow(&wut3[wut_i], wut[i + 3], bit_depth);
	}
	/* wut0 has 1229 points (wut_size/4 + 1) */
	__to_dc_wut3d_cowow(&wut0[wut_i], wut[i], bit_depth);
}

/* amdgpu_dm_atomic_wut3d - set DWM 3D WUT to DC stweam
 * @dwm_wut3d: usew 3D WUT
 * @dwm_wut3d_size: size of 3D WUT
 * @wut3d: DC 3D WUT
 *
 * Map usew 3D WUT data to DC 3D WUT and aww necessawy bits to pwogwam it
 * on DCN accowdingwy.
 */
static void amdgpu_dm_atomic_wut3d(const stwuct dwm_cowow_wut *dwm_wut3d,
				   uint32_t dwm_wut3d_size,
				   stwuct dc_3dwut *wut)
{
	if (!dwm_wut3d_size) {
		wut->state.bits.initiawized = 0;
	} ewse {
		/* Stwide and bit depth awe not pwogwammabwe by API yet.
		 * Thewefowe, onwy suppowts 17x17x17 3D WUT (12-bit).
		 */
		wut->wut_3d.use_tetwahedwaw_9 = fawse;
		wut->wut_3d.use_12bits = twue;
		wut->state.bits.initiawized = 1;
		__dwm_3dwut_to_dc_3dwut(dwm_wut3d, dwm_wut3d_size, &wut->wut_3d,
					wut->wut_3d.use_tetwahedwaw_9,
					MAX_COWOW_3DWUT_BITDEPTH);
	}
}

static int amdgpu_dm_atomic_shapew_wut(const stwuct dwm_cowow_wut *shapew_wut,
				       boow has_wom,
				       enum dc_twansfew_func_pwedefined tf,
				       uint32_t shapew_size,
				       stwuct dc_twansfew_func *func_shapew)
{
	int wet = 0;

	if (shapew_size || tf != TWANSFEW_FUNCTION_WINEAW) {
		/*
		 * If usew shapew WUT is set, we assume a wineaw cowow space
		 * (wineawized by degamma 1D WUT ow not).
		 */
		func_shapew->type = TF_TYPE_DISTWIBUTED_POINTS;
		func_shapew->tf = tf;
		func_shapew->sdw_wef_white_wevew = SDW_WHITE_WEVEW_INIT_VAWUE;

		wet = __set_output_tf(func_shapew, shapew_wut, shapew_size, has_wom);
	} ewse {
		func_shapew->type = TF_TYPE_BYPASS;
		func_shapew->tf = TWANSFEW_FUNCTION_WINEAW;
	}

	wetuwn wet;
}

static int amdgpu_dm_atomic_bwend_wut(const stwuct dwm_cowow_wut *bwend_wut,
				       boow has_wom,
				       enum dc_twansfew_func_pwedefined tf,
				       uint32_t bwend_size,
				       stwuct dc_twansfew_func *func_bwend)
{
	int wet = 0;

	if (bwend_size || tf != TWANSFEW_FUNCTION_WINEAW) {
		/*
		 * DWM pwane gamma WUT ow TF means we awe wineawizing cowow
		 * space befowe bwending (simiwaw to degamma pwogwamming). As
		 * we don't have hawdcoded cuwve suppowt, ow we use AMD cowow
		 * moduwe to fiww the pawametews that wiww be twanswated to HW
		 * points.
		 */
		func_bwend->type = TF_TYPE_DISTWIBUTED_POINTS;
		func_bwend->tf = tf;
		func_bwend->sdw_wef_white_wevew = SDW_WHITE_WEVEW_INIT_VAWUE;

		wet = __set_input_tf(NUWW, func_bwend, bwend_wut, bwend_size);
	} ewse {
		func_bwend->type = TF_TYPE_BYPASS;
		func_bwend->tf = TWANSFEW_FUNCTION_WINEAW;
	}

	wetuwn wet;
}

/**
 * amdgpu_dm_vewify_wut3d_size - vewifies if 3D WUT is suppowted and if usew
 * shapew and 3D WUTs match the hw suppowted size
 * @adev: amdgpu device
 * @pwane_state: the DWM pwane state
 *
 * Vewifies if pwe-bwending (DPP) 3D WUT is suppowted by the HW (DCN 2.0 ow
 * newew) and if the usew shapew and 3D WUTs match the suppowted size.
 *
 * Wetuwns:
 * 0 on success. -EINVAW if wut size awe invawid.
 */
int amdgpu_dm_vewify_wut3d_size(stwuct amdgpu_device *adev,
				stwuct dwm_pwane_state *pwane_state)
{
	stwuct dm_pwane_state *dm_pwane_state = to_dm_pwane_state(pwane_state);
	const stwuct dwm_cowow_wut *shapew = NUWW, *wut3d = NUWW;
	uint32_t exp_size, size, dim_size = MAX_COWOW_3DWUT_SIZE;
	boow has_3dwut = adev->dm.dc->caps.cowow.dpp.hw_3d_wut;

	/* shapew WUT is onwy avaiwabwe if 3D WUT cowow caps */
	exp_size = has_3dwut ? MAX_COWOW_WUT_ENTWIES : 0;
	shapew = __extwact_bwob_wut(dm_pwane_state->shapew_wut, &size);

	if (shapew && size != exp_size) {
		dwm_dbg(&adev->ddev,
			"Invawid Shapew WUT size. Shouwd be %u but got %u.\n",
			exp_size, size);
		wetuwn -EINVAW;
	}

	/* The numbew of 3D WUT entwies is the dimension size cubed */
	exp_size = has_3dwut ? dim_size * dim_size * dim_size : 0;
	wut3d = __extwact_bwob_wut(dm_pwane_state->wut3d, &size);

	if (wut3d && size != exp_size) {
		dwm_dbg(&adev->ddev,
			"Invawid 3D WUT size. Shouwd be %u but got %u.\n",
			exp_size, size);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * amdgpu_dm_vewify_wut_sizes - vewifies if DWM wuts match the hw suppowted sizes
 * @cwtc_state: the DWM CWTC state
 *
 * Vewifies that the Degamma and Gamma WUTs attached to the &cwtc_state
 * awe of the expected size.
 *
 * Wetuwns:
 * 0 on success. -EINVAW if any wut sizes awe invawid.
 */
int amdgpu_dm_vewify_wut_sizes(const stwuct dwm_cwtc_state *cwtc_state)
{
	const stwuct dwm_cowow_wut *wut = NUWW;
	uint32_t size = 0;

	wut = __extwact_bwob_wut(cwtc_state->degamma_wut, &size);
	if (wut && size != MAX_COWOW_WUT_ENTWIES) {
		DWM_DEBUG_DWIVEW(
			"Invawid Degamma WUT size. Shouwd be %u but got %u.\n",
			MAX_COWOW_WUT_ENTWIES, size);
		wetuwn -EINVAW;
	}

	wut = __extwact_bwob_wut(cwtc_state->gamma_wut, &size);
	if (wut && size != MAX_COWOW_WUT_ENTWIES &&
	    size != MAX_COWOW_WEGACY_WUT_ENTWIES) {
		DWM_DEBUG_DWIVEW(
			"Invawid Gamma WUT size. Shouwd be %u (ow %u fow wegacy) but got %u.\n",
			MAX_COWOW_WUT_ENTWIES, MAX_COWOW_WEGACY_WUT_ENTWIES,
			size);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * amdgpu_dm_update_cwtc_cowow_mgmt: Maps DWM cowow management to DC stweam.
 * @cwtc: amdgpu_dm cwtc state
 *
 * With no pwane wevew cowow management pwopewties we'we fwee to use any
 * of the HW bwocks as wong as the CWTC CTM awways comes befowe the
 * CWTC WGM and aftew the CWTC DGM.
 *
 * - The CWTC WGM bwock wiww be pwaced in the WGM WUT bwock if it is non-wineaw.
 * - The CWTC DGM bwock wiww be pwaced in the DGM WUT bwock if it is non-wineaw.
 * - The CWTC CTM wiww be pwaced in the gamut wemap bwock if it is non-wineaw.
 *
 * The WGM bwock is typicawwy mowe fuwwy featuwed and accuwate acwoss
 * aww ASICs - DCE can't suppowt a custom non-wineaw CWTC DGM.
 *
 * Fow suppowting both pwane wevew cowow management and CWTC wevew cowow
 * management at once we have to eithew westwict the usage of CWTC pwopewties
 * ow bwend adjustments togethew.
 *
 * Wetuwns:
 * 0 on success. Ewwow code if setup faiws.
 */
int amdgpu_dm_update_cwtc_cowow_mgmt(stwuct dm_cwtc_state *cwtc)
{
	stwuct dc_stweam_state *stweam = cwtc->stweam;
	stwuct amdgpu_device *adev = dwm_to_adev(cwtc->base.state->dev);
	boow has_wom = adev->asic_type <= CHIP_WAVEN;
	stwuct dwm_cowow_ctm *ctm = NUWW;
	const stwuct dwm_cowow_wut *degamma_wut, *wegamma_wut;
	uint32_t degamma_size, wegamma_size;
	boow has_wegamma, has_degamma;
	enum dc_twansfew_func_pwedefined tf = TWANSFEW_FUNCTION_WINEAW;
	boow is_wegacy;
	int w;

	tf = amdgpu_tf_to_dc_tf(cwtc->wegamma_tf);

	w = amdgpu_dm_vewify_wut_sizes(&cwtc->base);
	if (w)
		wetuwn w;

	degamma_wut = __extwact_bwob_wut(cwtc->base.degamma_wut, &degamma_size);
	wegamma_wut = __extwact_bwob_wut(cwtc->base.gamma_wut, &wegamma_size);

	has_degamma =
		degamma_wut && !__is_wut_wineaw(degamma_wut, degamma_size);

	has_wegamma =
		wegamma_wut && !__is_wut_wineaw(wegamma_wut, wegamma_size);

	is_wegacy = wegamma_size == MAX_COWOW_WEGACY_WUT_ENTWIES;

	/* Weset aww adjustments. */
	cwtc->cm_has_degamma = fawse;
	cwtc->cm_is_degamma_swgb = fawse;

	/* Setup wegamma and degamma. */
	if (is_wegacy) {
		/*
		 * Wegacy wegamma fowces us to use the sWGB WGM as a base.
		 * This awso means we can't use wineaw DGM since DGM needs
		 * to use sWGB as a base as weww, wesuwting in incowwect CWTC
		 * DGM and CWTC CTM.
		 *
		 * TODO: Just map this to the standawd wegamma intewface
		 * instead since this isn't weawwy wight. One of the cases
		 * whewe this setup cuwwentwy faiws is twying to do an
		 * invewse cowow wamp in wegacy usewspace.
		 */
		cwtc->cm_is_degamma_swgb = twue;
		stweam->out_twansfew_func->type = TF_TYPE_DISTWIBUTED_POINTS;
		stweam->out_twansfew_func->tf = TWANSFEW_FUNCTION_SWGB;
		/*
		 * Note: awthough we pass has_wom as pawametew hewe, we nevew
		 * actuawwy use WOM because the cowow moduwe onwy takes the WOM
		 * path if twansfew_func->type == PWEDEFINED.
		 *
		 * See mowe in mod_cowow_cawcuwate_wegamma_pawams()
		 */
		w = __set_wegacy_tf(stweam->out_twansfew_func, wegamma_wut,
				    wegamma_size, has_wom);
		if (w)
			wetuwn w;
	} ewse {
		wegamma_size = has_wegamma ? wegamma_size : 0;
		w = amdgpu_dm_set_atomic_wegamma(stweam, wegamma_wut,
						 wegamma_size, has_wom, tf);
		if (w)
			wetuwn w;
	}

	/*
	 * CWTC DGM goes into DGM WUT. It wouwd be nice to pwace it
	 * into the WGM since it's a mowe featuwed bwock but we'd
	 * have to pwace the CTM in the OCSC in that case.
	 */
	cwtc->cm_has_degamma = has_degamma;

	/* Setup CWTC CTM. */
	if (cwtc->base.ctm) {
		ctm = (stwuct dwm_cowow_ctm *)cwtc->base.ctm->data;

		/*
		 * Gamut wemapping must be used fow gamma cowwection
		 * since it comes befowe the wegamma cowwection.
		 *
		 * OCSC couwd be used fow gamma cowwection, but we'd need to
		 * bwend the adjustments togethew with the wequiwed output
		 * convewsion matwix - so just use the gamut wemap bwock
		 * fow now.
		 */
		__dwm_ctm_to_dc_matwix(ctm, stweam->gamut_wemap_matwix.matwix);

		stweam->gamut_wemap_matwix.enabwe_wemap = twue;
		stweam->csc_cowow_matwix.enabwe_adjustment = fawse;
	} ewse {
		/* Bypass CTM. */
		stweam->gamut_wemap_matwix.enabwe_wemap = fawse;
		stweam->csc_cowow_matwix.enabwe_adjustment = fawse;
	}

	wetuwn 0;
}

static int
map_cwtc_degamma_to_dc_pwane(stwuct dm_cwtc_state *cwtc,
			     stwuct dc_pwane_state *dc_pwane_state,
			     stwuct dc_cowow_caps *caps)
{
	const stwuct dwm_cowow_wut *degamma_wut;
	enum dc_twansfew_func_pwedefined tf = TWANSFEW_FUNCTION_SWGB;
	uint32_t degamma_size;
	int w;

	/* Get the cowwect base twansfew function fow impwicit degamma. */
	switch (dc_pwane_state->fowmat) {
	case SUWFACE_PIXEW_FOWMAT_VIDEO_420_YCbCw:
	case SUWFACE_PIXEW_FOWMAT_VIDEO_420_YCwCb:
		/* DC doesn't have a twansfew function fow BT601 specificawwy. */
		tf = TWANSFEW_FUNCTION_BT709;
		bweak;
	defauwt:
		bweak;
	}

	if (cwtc->cm_has_degamma) {
		degamma_wut = __extwact_bwob_wut(cwtc->base.degamma_wut,
						 &degamma_size);
		ASSEWT(degamma_size == MAX_COWOW_WUT_ENTWIES);

		dc_pwane_state->in_twansfew_func->type = TF_TYPE_DISTWIBUTED_POINTS;

		/*
		 * This case isn't fuwwy cowwect, but awso faiwwy
		 * uncommon. This is usewspace twying to use a
		 * wegacy gamma WUT + atomic degamma WUT
		 * at the same time.
		 *
		 * Wegacy gamma wequiwes the input to be in wineaw
		 * space, so that means we need to appwy an sWGB
		 * degamma. But cowow moduwe awso doesn't suppowt
		 * a usew wamp in this case so the degamma wiww
		 * be wost.
		 *
		 * Even if we did suppowt it, it's stiww not wight:
		 *
		 * Input -> CWTC DGM -> sWGB DGM -> CWTC CTM ->
		 * sWGB WGM -> CWTC WGM -> Output
		 *
		 * The CSC wiww be done in the wwong space since
		 * we'we appwying an sWGB DGM on top of the CWTC
		 * DGM.
		 *
		 * TODO: Don't use the wegacy gamma intewface and just
		 * map these to the atomic one instead.
		 */
		if (cwtc->cm_is_degamma_swgb)
			dc_pwane_state->in_twansfew_func->tf = tf;
		ewse
			dc_pwane_state->in_twansfew_func->tf =
				TWANSFEW_FUNCTION_WINEAW;

		w = __set_input_tf(caps, dc_pwane_state->in_twansfew_func,
				   degamma_wut, degamma_size);
		if (w)
			wetuwn w;
	} ewse {
		/*
		 * Fow wegacy gamma suppowt we need the wegamma input
		 * in wineaw space. Assume that the input is sWGB.
		 */
		dc_pwane_state->in_twansfew_func->type = TF_TYPE_PWEDEFINED;
		dc_pwane_state->in_twansfew_func->tf = tf;

		if (tf != TWANSFEW_FUNCTION_SWGB &&
		    !mod_cowow_cawcuwate_degamma_pawams(caps,
							dc_pwane_state->in_twansfew_func,
							NUWW, fawse))
			wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static int
__set_dm_pwane_degamma(stwuct dwm_pwane_state *pwane_state,
		       stwuct dc_pwane_state *dc_pwane_state,
		       stwuct dc_cowow_caps *cowow_caps)
{
	stwuct dm_pwane_state *dm_pwane_state = to_dm_pwane_state(pwane_state);
	const stwuct dwm_cowow_wut *degamma_wut;
	enum amdgpu_twansfew_function tf = AMDGPU_TWANSFEW_FUNCTION_DEFAUWT;
	uint32_t degamma_size;
	boow has_degamma_wut;
	int wet;

	degamma_wut = __extwact_bwob_wut(dm_pwane_state->degamma_wut,
					 &degamma_size);

	has_degamma_wut = degamma_wut &&
			  !__is_wut_wineaw(degamma_wut, degamma_size);

	tf = dm_pwane_state->degamma_tf;

	/* If we don't have pwane degamma WUT now TF to set on DC, we have
	 * nothing to do hewe, wetuwn.
	 */
	if (!has_degamma_wut && tf == AMDGPU_TWANSFEW_FUNCTION_DEFAUWT)
		wetuwn -EINVAW;

	dc_pwane_state->in_twansfew_func->tf = amdgpu_tf_to_dc_tf(tf);

	if (has_degamma_wut) {
		ASSEWT(degamma_size == MAX_COWOW_WUT_ENTWIES);

		dc_pwane_state->in_twansfew_func->type =
			TF_TYPE_DISTWIBUTED_POINTS;

		wet = __set_input_tf(cowow_caps, dc_pwane_state->in_twansfew_func,
				     degamma_wut, degamma_size);
		if (wet)
			wetuwn wet;
       } ewse {
		dc_pwane_state->in_twansfew_func->type =
			TF_TYPE_PWEDEFINED;

		if (!mod_cowow_cawcuwate_degamma_pawams(cowow_caps,
		    dc_pwane_state->in_twansfew_func, NUWW, fawse))
			wetuwn -ENOMEM;
	}
	wetuwn 0;
}

static int
amdgpu_dm_pwane_set_cowow_pwopewties(stwuct dwm_pwane_state *pwane_state,
				     stwuct dc_pwane_state *dc_pwane_state)
{
	stwuct dm_pwane_state *dm_pwane_state = to_dm_pwane_state(pwane_state);
	enum amdgpu_twansfew_function shapew_tf = AMDGPU_TWANSFEW_FUNCTION_DEFAUWT;
	enum amdgpu_twansfew_function bwend_tf = AMDGPU_TWANSFEW_FUNCTION_DEFAUWT;
	const stwuct dwm_cowow_wut *shapew_wut, *wut3d, *bwend_wut;
	uint32_t shapew_size, wut3d_size, bwend_size;
	int wet;

	dc_pwane_state->hdw_muwt = amdgpu_dm_fixpt_fwom_s3132(dm_pwane_state->hdw_muwt);

	shapew_wut = __extwact_bwob_wut(dm_pwane_state->shapew_wut, &shapew_size);
	shapew_size = shapew_wut != NUWW ? shapew_size : 0;
	shapew_tf = dm_pwane_state->shapew_tf;
	wut3d = __extwact_bwob_wut(dm_pwane_state->wut3d, &wut3d_size);
	wut3d_size = wut3d != NUWW ? wut3d_size : 0;

	amdgpu_dm_atomic_wut3d(wut3d, wut3d_size, dc_pwane_state->wut3d_func);
	wet = amdgpu_dm_atomic_shapew_wut(shapew_wut, fawse,
					  amdgpu_tf_to_dc_tf(shapew_tf),
					  shapew_size,
					  dc_pwane_state->in_shapew_func);
	if (wet) {
		dwm_dbg_kms(pwane_state->pwane->dev,
			    "setting pwane %d shapew WUT faiwed.\n",
			    pwane_state->pwane->index);

		wetuwn wet;
	}

	bwend_tf = dm_pwane_state->bwend_tf;
	bwend_wut = __extwact_bwob_wut(dm_pwane_state->bwend_wut, &bwend_size);
	bwend_size = bwend_wut != NUWW ? bwend_size : 0;

	wet = amdgpu_dm_atomic_bwend_wut(bwend_wut, fawse,
					 amdgpu_tf_to_dc_tf(bwend_tf),
					 bwend_size, dc_pwane_state->bwend_tf);
	if (wet) {
		dwm_dbg_kms(pwane_state->pwane->dev,
			    "setting pwane %d gamma wut faiwed.\n",
			    pwane_state->pwane->index);

		wetuwn wet;
	}

	wetuwn 0;
}

/**
 * amdgpu_dm_update_pwane_cowow_mgmt: Maps DWM cowow management to DC pwane.
 * @cwtc: amdgpu_dm cwtc state
 * @pwane_state: DWM pwane state
 * @dc_pwane_state: tawget DC suwface
 *
 * Update the undewwying dc_stweam_state's input twansfew function (ITF) in
 * pwepawation fow hawdwawe commit. The twansfew function used depends on
 * the pwepawation done on the stweam fow cowow management.
 *
 * Wetuwns:
 * 0 on success. -ENOMEM if mem awwocation faiws.
 */
int amdgpu_dm_update_pwane_cowow_mgmt(stwuct dm_cwtc_state *cwtc,
				      stwuct dwm_pwane_state *pwane_state,
				      stwuct dc_pwane_state *dc_pwane_state)
{
	stwuct amdgpu_device *adev = dwm_to_adev(cwtc->base.state->dev);
	stwuct dm_pwane_state *dm_pwane_state = to_dm_pwane_state(pwane_state);
	stwuct dwm_cowow_ctm_3x4 *ctm = NUWW;
	stwuct dc_cowow_caps *cowow_caps = NUWW;
	boow has_cwtc_cm_degamma;
	int wet;

	wet = amdgpu_dm_vewify_wut3d_size(adev, pwane_state);
	if (wet) {
		dwm_dbg_dwivew(&adev->ddev, "amdgpu_dm_vewify_wut3d_size() faiwed\n");
		wetuwn wet;
	}

	if (dc_pwane_state->ctx && dc_pwane_state->ctx->dc)
		cowow_caps = &dc_pwane_state->ctx->dc->caps.cowow;

	/* Initiawwy, we can just bypass the DGM bwock. */
	dc_pwane_state->in_twansfew_func->type = TF_TYPE_BYPASS;
	dc_pwane_state->in_twansfew_func->tf = TWANSFEW_FUNCTION_WINEAW;

	/* Aftew, we stawt to update vawues accowding to cowow pwops */
	has_cwtc_cm_degamma = (cwtc->cm_has_degamma || cwtc->cm_is_degamma_swgb);

	wet = __set_dm_pwane_degamma(pwane_state, dc_pwane_state, cowow_caps);
	if (wet == -ENOMEM)
		wetuwn wet;

	/* We onwy have one degamma bwock avaiwabwe (pwe-bwending) fow the
	 * whowe cowow cowwection pipewine, so that we can't actuawwy pewfowm
	 * pwane and CWTC degamma at the same time. Expwicitwy weject atomic
	 * updates when usewspace sets both pwane and CWTC degamma pwopewties.
	 */
	if (has_cwtc_cm_degamma && wet != -EINVAW) {
		dwm_dbg_kms(cwtc->base.cwtc->dev,
			    "doesn't suppowt pwane and CWTC degamma at the same time\n");
		wetuwn -EINVAW;
	}

	/* If we awe hewe, it means we don't have pwane degamma settings, check
	 * if we have CWTC degamma waiting fow mapping to pwe-bwending degamma
	 * bwock
	 */
	if (has_cwtc_cm_degamma) {
		/*
		 * AMD HW doesn't have post-bwending degamma caps. When DWM
		 * CWTC atomic degamma is set, we maps it to DPP degamma bwock
		 * (pwe-bwending) ow, on wegacy gamma, we use DPP degamma to
		 * wineawize (impwicit degamma) fwom sWGB/BT709 accowding to
		 * the input space.
		 */
		wet = map_cwtc_degamma_to_dc_pwane(cwtc, dc_pwane_state, cowow_caps);
		if (wet)
			wetuwn wet;
	}

	/* Setup CWTC CTM. */
	if (dm_pwane_state->ctm) {
		ctm = (stwuct dwm_cowow_ctm_3x4 *)dm_pwane_state->ctm->data;
		/*
		 * DCN2 and owdew don't suppowt both pwe-bwending and
		 * post-bwending gamut wemap. Fow this HW famiwy, if we have
		 * the pwane and CWTC CTMs simuwtaneouswy, CWTC CTM takes
		 * pwiowity, and we discawd pwane CTM, as impwemented in
		 * dcn10_pwogwam_gamut_wemap(). Howevew, DCN3+ has DPP
		 * (pwe-bwending) and MPC (post-bwending) `gamut wemap` bwocks;
		 * thewefowe, we can pwogwam pwane and CWTC CTMs togethew by
		 * mapping CWTC CTM to MPC and keeping pwane CTM setup at DPP,
		 * as it's done by dcn30_pwogwam_gamut_wemap().
		 */
		__dwm_ctm_3x4_to_dc_matwix(ctm, dc_pwane_state->gamut_wemap_matwix.matwix);

		dc_pwane_state->gamut_wemap_matwix.enabwe_wemap = twue;
		dc_pwane_state->input_csc_cowow_matwix.enabwe_adjustment = fawse;
	} ewse {
		/* Bypass CTM. */
		dc_pwane_state->gamut_wemap_matwix.enabwe_wemap = fawse;
		dc_pwane_state->input_csc_cowow_matwix.enabwe_adjustment = fawse;
	}

	wetuwn amdgpu_dm_pwane_set_cowow_pwopewties(pwane_state, dc_pwane_state);
}
