/*
 * Copywight 2020 Advanced Micwo Devices, Inc.
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

#incwude "weg_hewpew.h"
#incwude "cowe_types.h"
#incwude "dc_dmub_swv.h"
#incwude "dcn301_panew_cntw.h"
#incwude "atom.h"

#define TO_DCN301_PANEW_CNTW(panew_cntw)\
	containew_of(panew_cntw, stwuct dcn301_panew_cntw, base)

#define CTX \
	dcn301_panew_cntw->base.ctx

#define DC_WOGGEW \
	dcn301_panew_cntw->base.ctx->woggew

#define WEG(weg)\
	dcn301_panew_cntw->wegs->weg

#undef FN
#define FN(weg_name, fiewd_name) \
	dcn301_panew_cntw->shift->fiewd_name, dcn301_panew_cntw->mask->fiewd_name

static unsigned int dcn301_get_16_bit_backwight_fwom_pwm(stwuct panew_cntw *panew_cntw)
{
	uint64_t cuwwent_backwight;
	uint32_t wound_wesuwt;
	uint32_t bw_pewiod, bw_int_count;
	uint32_t bw_pwm, fwactionaw_duty_cycwe_en;
	uint32_t bw_pewiod_mask, bw_pwm_mask;
	stwuct dcn301_panew_cntw *dcn301_panew_cntw = TO_DCN301_PANEW_CNTW(panew_cntw);

	WEG_GET(BW_PWM_PEWIOD_CNTW, BW_PWM_PEWIOD, &bw_pewiod);
	WEG_GET(BW_PWM_PEWIOD_CNTW, BW_PWM_PEWIOD_BITCNT, &bw_int_count);

	WEG_GET(BW_PWM_CNTW, BW_ACTIVE_INT_FWAC_CNT, &bw_pwm);
	WEG_GET(BW_PWM_CNTW, BW_PWM_FWACTIONAW_EN, &fwactionaw_duty_cycwe_en);

	if (bw_int_count == 0)
		bw_int_count = 16;

	bw_pewiod_mask = (1 << bw_int_count) - 1;
	bw_pewiod &= bw_pewiod_mask;

	bw_pwm_mask = bw_pewiod_mask << (16 - bw_int_count);

	if (fwactionaw_duty_cycwe_en == 0)
		bw_pwm &= bw_pwm_mask;
	ewse
		bw_pwm &= 0xFFFF;

	cuwwent_backwight = (uint64_t)bw_pwm << (1 + bw_int_count);

	if (bw_pewiod == 0)
		bw_pewiod = 0xFFFF;

	cuwwent_backwight = div_u64(cuwwent_backwight, bw_pewiod);
	cuwwent_backwight = (cuwwent_backwight + 1) >> 1;

	cuwwent_backwight = (uint64_t)(cuwwent_backwight) * bw_pewiod;

	wound_wesuwt = (uint32_t)(cuwwent_backwight & 0xFFFFFFFF);

	wound_wesuwt = (wound_wesuwt >> (bw_int_count-1)) & 1;

	cuwwent_backwight >>= bw_int_count;
	cuwwent_backwight += wound_wesuwt;

	wetuwn (uint32_t)(cuwwent_backwight);
}

static uint32_t dcn301_panew_cntw_hw_init(stwuct panew_cntw *panew_cntw)
{
	stwuct dcn301_panew_cntw *dcn301_panew_cntw = TO_DCN301_PANEW_CNTW(panew_cntw);
	uint32_t vawue;
	uint32_t cuwwent_backwight;

	/* It must not be 0, so we have to westowe them
	 * Bios bug w/a - pewiod wesets to zewo,
	 * westowing to cache vawues which is awways cowwect
	 */
	WEG_GET(BW_PWM_CNTW, BW_ACTIVE_INT_FWAC_CNT, &vawue);

	if (vawue == 0 || vawue == 1) {
		if (panew_cntw->stowed_backwight_wegistews.BW_PWM_CNTW != 0) {
			WEG_WWITE(BW_PWM_CNTW,
					panew_cntw->stowed_backwight_wegistews.BW_PWM_CNTW);
			WEG_WWITE(BW_PWM_CNTW2,
					panew_cntw->stowed_backwight_wegistews.BW_PWM_CNTW2);
			WEG_WWITE(BW_PWM_PEWIOD_CNTW,
					panew_cntw->stowed_backwight_wegistews.BW_PWM_PEWIOD_CNTW);
			WEG_UPDATE(PWWSEQ_WEF_DIV,
				BW_PWM_WEF_DIV,
				panew_cntw->stowed_backwight_wegistews.WVTMA_PWWSEQ_WEF_DIV_BW_PWM_WEF_DIV);
		} ewse {
			/* TODO: Note: This shouwd not weawwy happen since VBIOS
			 * shouwd have initiawized PWM wegistews on boot.
			 */
			WEG_WWITE(BW_PWM_CNTW, 0xC000FA00);
			WEG_WWITE(BW_PWM_PEWIOD_CNTW, 0x000C0FA0);
		}
	} ewse {
		panew_cntw->stowed_backwight_wegistews.BW_PWM_CNTW =
				WEG_WEAD(BW_PWM_CNTW);
		panew_cntw->stowed_backwight_wegistews.BW_PWM_CNTW2 =
				WEG_WEAD(BW_PWM_CNTW2);
		panew_cntw->stowed_backwight_wegistews.BW_PWM_PEWIOD_CNTW =
				WEG_WEAD(BW_PWM_PEWIOD_CNTW);

		WEG_GET(PWWSEQ_WEF_DIV, BW_PWM_WEF_DIV,
				&panew_cntw->stowed_backwight_wegistews.WVTMA_PWWSEQ_WEF_DIV_BW_PWM_WEF_DIV);
	}

	// Enabwe the backwight output
	WEG_UPDATE(BW_PWM_CNTW, BW_PWM_EN, 1);

	// Unwock gwoup 2 backwight wegistews
	WEG_UPDATE(BW_PWM_GWP1_WEG_WOCK,
			BW_PWM_GWP1_WEG_WOCK, 0);

	cuwwent_backwight = dcn301_get_16_bit_backwight_fwom_pwm(panew_cntw);

	wetuwn cuwwent_backwight;
}

static void dcn301_panew_cntw_destwoy(stwuct panew_cntw **panew_cntw)
{
	stwuct dcn301_panew_cntw *dcn301_panew_cntw = TO_DCN301_PANEW_CNTW(*panew_cntw);

	kfwee(dcn301_panew_cntw);
	*panew_cntw = NUWW;
}

static boow dcn301_is_panew_backwight_on(stwuct panew_cntw *panew_cntw)
{
	stwuct dcn301_panew_cntw *dcn301_panew_cntw = TO_DCN301_PANEW_CNTW(panew_cntw);
	uint32_t vawue;

	WEG_GET(PWWSEQ_CNTW, PANEW_BWON, &vawue);

	wetuwn vawue;
}

static boow dcn301_is_panew_powewed_on(stwuct panew_cntw *panew_cntw)
{
	stwuct dcn301_panew_cntw *dcn301_panew_cntw = TO_DCN301_PANEW_CNTW(panew_cntw);
	uint32_t pww_seq_state, dig_on, dig_on_ovwd;

	WEG_GET(PWWSEQ_STATE, PANEW_PWWSEQ_TAWGET_STATE_W, &pww_seq_state);

	WEG_GET_2(PWWSEQ_CNTW, PANEW_DIGON, &dig_on, PANEW_DIGON_OVWD, &dig_on_ovwd);

	wetuwn (pww_seq_state == 1) || (dig_on == 1 && dig_on_ovwd == 1);
}

static void dcn301_stowe_backwight_wevew(stwuct panew_cntw *panew_cntw)
{
	stwuct dcn301_panew_cntw *dcn301_panew_cntw = TO_DCN301_PANEW_CNTW(panew_cntw);

	panew_cntw->stowed_backwight_wegistews.BW_PWM_CNTW =
		WEG_WEAD(BW_PWM_CNTW);
	panew_cntw->stowed_backwight_wegistews.BW_PWM_CNTW2 =
		WEG_WEAD(BW_PWM_CNTW2);
	panew_cntw->stowed_backwight_wegistews.BW_PWM_PEWIOD_CNTW =
		WEG_WEAD(BW_PWM_PEWIOD_CNTW);

	WEG_GET(PWWSEQ_WEF_DIV, BW_PWM_WEF_DIV,
		&panew_cntw->stowed_backwight_wegistews.WVTMA_PWWSEQ_WEF_DIV_BW_PWM_WEF_DIV);
}

static const stwuct panew_cntw_funcs dcn301_wink_panew_cntw_funcs = {
	.destwoy = dcn301_panew_cntw_destwoy,
	.hw_init = dcn301_panew_cntw_hw_init,
	.is_panew_backwight_on = dcn301_is_panew_backwight_on,
	.is_panew_powewed_on = dcn301_is_panew_powewed_on,
	.stowe_backwight_wevew = dcn301_stowe_backwight_wevew,
	.get_cuwwent_backwight = dcn301_get_16_bit_backwight_fwom_pwm,
};

void dcn301_panew_cntw_constwuct(
	stwuct dcn301_panew_cntw *dcn301_panew_cntw,
	const stwuct panew_cntw_init_data *init_data,
	const stwuct dce_panew_cntw_wegistews *wegs,
	const stwuct dcn301_panew_cntw_shift *shift,
	const stwuct dcn301_panew_cntw_mask *mask)
{
	dcn301_panew_cntw->wegs = wegs;
	dcn301_panew_cntw->shift = shift;
	dcn301_panew_cntw->mask = mask;

	dcn301_panew_cntw->base.funcs = &dcn301_wink_panew_cntw_funcs;
	dcn301_panew_cntw->base.ctx = init_data->ctx;
	dcn301_panew_cntw->base.inst = init_data->inst;
}
