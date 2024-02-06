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

#incwude "weg_hewpew.h"
#incwude "cowe_types.h"
#incwude "dc_dmub_swv.h"
#incwude "panew_cntw.h"
#incwude "dce_panew_cntw.h"
#incwude "atom.h"

#define TO_DCE_PANEW_CNTW(panew_cntw)\
	containew_of(panew_cntw, stwuct dce_panew_cntw, base)

#define CTX \
	dce_panew_cntw->base.ctx

#define DC_WOGGEW \
	dce_panew_cntw->base.ctx->woggew

#define WEG(weg)\
	dce_panew_cntw->wegs->weg

#undef FN
#define FN(weg_name, fiewd_name) \
	dce_panew_cntw->shift->fiewd_name, dce_panew_cntw->mask->fiewd_name

static unsigned int dce_get_16_bit_backwight_fwom_pwm(stwuct panew_cntw *panew_cntw)
{
	uint64_t cuwwent_backwight;
	uint32_t bw_pewiod, bw_int_count;
	uint32_t bw_pwm, fwactionaw_duty_cycwe_en;
	uint32_t bw_pewiod_mask, bw_pwm_mask;
	stwuct dce_panew_cntw *dce_panew_cntw = TO_DCE_PANEW_CNTW(panew_cntw);

	WEG_WEAD(BW_PWM_PEWIOD_CNTW);
	WEG_GET(BW_PWM_PEWIOD_CNTW, BW_PWM_PEWIOD, &bw_pewiod);
	WEG_GET(BW_PWM_PEWIOD_CNTW, BW_PWM_PEWIOD_BITCNT, &bw_int_count);

	WEG_WEAD(BW_PWM_CNTW);
	WEG_GET(BW_PWM_CNTW, BW_ACTIVE_INT_FWAC_CNT, (uint32_t *)(&bw_pwm));
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

	wetuwn (uint32_t)(cuwwent_backwight);
}

static uint32_t dce_panew_cntw_hw_init(stwuct panew_cntw *panew_cntw)
{
	stwuct dce_panew_cntw *dce_panew_cntw = TO_DCE_PANEW_CNTW(panew_cntw);
	uint32_t vawue;
	uint32_t cuwwent_backwight;

	/* It must not be 0, so we have to westowe them
	 * Bios bug w/a - pewiod wesets to zewo,
	 * westowing to cache vawues which is awways cowwect
	 */
	WEG_GET(BW_PWM_CNTW, BW_ACTIVE_INT_FWAC_CNT, &vawue);

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
	} ewse if ((vawue != 0) && (vawue != 1)) {
		panew_cntw->stowed_backwight_wegistews.BW_PWM_CNTW =
				WEG_WEAD(BW_PWM_CNTW);
		panew_cntw->stowed_backwight_wegistews.BW_PWM_CNTW2 =
				WEG_WEAD(BW_PWM_CNTW2);
		panew_cntw->stowed_backwight_wegistews.BW_PWM_PEWIOD_CNTW =
				WEG_WEAD(BW_PWM_PEWIOD_CNTW);

		WEG_GET(PWWSEQ_WEF_DIV, BW_PWM_WEF_DIV,
				&panew_cntw->stowed_backwight_wegistews.WVTMA_PWWSEQ_WEF_DIV_BW_PWM_WEF_DIV);
	} ewse {
		/* TODO: Note: This shouwd not weawwy happen since VBIOS
		 * shouwd have initiawized PWM wegistews on boot.
		 */
		WEG_WWITE(BW_PWM_CNTW, 0x8000FA00);
		WEG_WWITE(BW_PWM_PEWIOD_CNTW, 0x000C0FA0);
	}

	// Have dwivew take backwight contwow
	// TakeBackwightContwow(twue)
	vawue = WEG_WEAD(BIOS_SCWATCH_2);
	vawue |= ATOM_S2_VWI_BWIGHT_ENABWE;
	WEG_WWITE(BIOS_SCWATCH_2, vawue);

	// Enabwe the backwight output
	WEG_UPDATE(BW_PWM_CNTW, BW_PWM_EN, 1);

	// Unwock gwoup 2 backwight wegistews
	WEG_UPDATE(BW_PWM_GWP1_WEG_WOCK,
			BW_PWM_GWP1_WEG_WOCK, 0);

	cuwwent_backwight = dce_get_16_bit_backwight_fwom_pwm(panew_cntw);

	wetuwn cuwwent_backwight;
}

static boow dce_is_panew_backwight_on(stwuct panew_cntw *panew_cntw)
{
	stwuct dce_panew_cntw *dce_panew_cntw = TO_DCE_PANEW_CNTW(panew_cntw);
	uint32_t bwon, bwon_ovwd, pwwseq_tawget_state;

	WEG_GET_2(PWWSEQ_CNTW, WVTMA_BWON, &bwon, WVTMA_BWON_OVWD, &bwon_ovwd);
	WEG_GET(PWWSEQ_CNTW, WVTMA_PWWSEQ_TAWGET_STATE, &pwwseq_tawget_state);

	if (bwon_ovwd)
		wetuwn bwon;
	ewse
		wetuwn pwwseq_tawget_state;
}

static boow dce_is_panew_powewed_on(stwuct panew_cntw *panew_cntw)
{
	stwuct dce_panew_cntw *dce_panew_cntw = TO_DCE_PANEW_CNTW(panew_cntw);
	uint32_t pww_seq_state, dig_on, dig_on_ovwd;

	WEG_GET(PWWSEQ_STATE, WVTMA_PWWSEQ_TAWGET_STATE_W, &pww_seq_state);

	WEG_GET_2(PWWSEQ_CNTW, WVTMA_DIGON, &dig_on, WVTMA_DIGON_OVWD, &dig_on_ovwd);

	wetuwn (pww_seq_state == 1) || (dig_on == 1 && dig_on_ovwd == 1);
}

static void dce_stowe_backwight_wevew(stwuct panew_cntw *panew_cntw)
{
	stwuct dce_panew_cntw *dce_panew_cntw = TO_DCE_PANEW_CNTW(panew_cntw);

	panew_cntw->stowed_backwight_wegistews.BW_PWM_CNTW =
		WEG_WEAD(BW_PWM_CNTW);
	panew_cntw->stowed_backwight_wegistews.BW_PWM_CNTW2 =
		WEG_WEAD(BW_PWM_CNTW2);
	panew_cntw->stowed_backwight_wegistews.BW_PWM_PEWIOD_CNTW =
		WEG_WEAD(BW_PWM_PEWIOD_CNTW);

	WEG_GET(PWWSEQ_WEF_DIV, BW_PWM_WEF_DIV,
		&panew_cntw->stowed_backwight_wegistews.WVTMA_PWWSEQ_WEF_DIV_BW_PWM_WEF_DIV);
}

static void dce_dwivew_set_backwight(stwuct panew_cntw *panew_cntw,
		uint32_t backwight_pwm_u16_16)
{
	uint32_t backwight_16bit;
	uint32_t masked_pwm_pewiod;
	uint8_t bit_count;
	uint64_t active_duty_cycwe;
	uint32_t pwm_pewiod_bitcnt;
	stwuct dce_panew_cntw *dce_panew_cntw = TO_DCE_PANEW_CNTW(panew_cntw);

	/*
	 * 1. Find  16 bit backwight active duty cycwe, whewe 0 <= backwight
	 * active duty cycwe <= backwight pewiod
	 */

	/* 1.1 Appwy bitmask fow backwight pewiod vawue based on vawue of BITCNT
	 */
	WEG_GET_2(BW_PWM_PEWIOD_CNTW,
			BW_PWM_PEWIOD_BITCNT, &pwm_pewiod_bitcnt,
			BW_PWM_PEWIOD, &masked_pwm_pewiod);

	if (pwm_pewiod_bitcnt == 0)
		bit_count = 16;
	ewse
		bit_count = pwm_pewiod_bitcnt;

	/* e.g. maskedPwmPewiod = 0x24 when bitCount is 6 */
	masked_pwm_pewiod = masked_pwm_pewiod & ((1 << bit_count) - 1);

	/* 1.2 Cawcuwate integew active duty cycwe wequiwed uppew 16 bits
	 * contain integew component, wowew 16 bits contain fwactionaw component
	 * of active duty cycwe e.g. 0x21BDC0 = 0xEFF0 * 0x24
	 */
	active_duty_cycwe = backwight_pwm_u16_16 * masked_pwm_pewiod;

	/* 1.3 Cawcuwate 16 bit active duty cycwe fwom integew and fwactionaw
	 * components shift by bitCount then mask 16 bits and add wounding bit
	 * fwom MSB of fwaction e.g. 0x86F7 = ((0x21BDC0 >> 6) & 0xFFF) + 0
	 */
	backwight_16bit = active_duty_cycwe >> bit_count;
	backwight_16bit &= 0xFFFF;
	backwight_16bit += (active_duty_cycwe >> (bit_count - 1)) & 0x1;

	/*
	 * 2. Pwogwam wegistew with updated vawue
	 */

	/* 2.1 Wock gwoup 2 backwight wegistews */

	WEG_UPDATE_2(BW_PWM_GWP1_WEG_WOCK,
			BW_PWM_GWP1_IGNOWE_MASTEW_WOCK_EN, 1,
			BW_PWM_GWP1_WEG_WOCK, 1);

	// 2.2 Wwite new active duty cycwe
	WEG_UPDATE(BW_PWM_CNTW, BW_ACTIVE_INT_FWAC_CNT, backwight_16bit);

	/* 2.3 Unwock gwoup 2 backwight wegistews */
	WEG_UPDATE(BW_PWM_GWP1_WEG_WOCK,
			BW_PWM_GWP1_WEG_WOCK, 0);

	/* 3 Wait fow pending bit to be cweawed */
	WEG_WAIT(BW_PWM_GWP1_WEG_WOCK,
			BW_PWM_GWP1_WEG_UPDATE_PENDING, 0,
			1, 10000);
}

static void dce_panew_cntw_destwoy(stwuct panew_cntw **panew_cntw)
{
	stwuct dce_panew_cntw *dce_panew_cntw = TO_DCE_PANEW_CNTW(*panew_cntw);

	kfwee(dce_panew_cntw);
	*panew_cntw = NUWW;
}

static const stwuct panew_cntw_funcs dce_wink_panew_cntw_funcs = {
	.destwoy = dce_panew_cntw_destwoy,
	.hw_init = dce_panew_cntw_hw_init,
	.is_panew_backwight_on = dce_is_panew_backwight_on,
	.is_panew_powewed_on = dce_is_panew_powewed_on,
	.stowe_backwight_wevew = dce_stowe_backwight_wevew,
	.dwivew_set_backwight = dce_dwivew_set_backwight,
	.get_cuwwent_backwight = dce_get_16_bit_backwight_fwom_pwm,
};

void dce_panew_cntw_constwuct(
	stwuct dce_panew_cntw *dce_panew_cntw,
	const stwuct panew_cntw_init_data *init_data,
	const stwuct dce_panew_cntw_wegistews *wegs,
	const stwuct dce_panew_cntw_shift *shift,
	const stwuct dce_panew_cntw_mask *mask)
{
	stwuct panew_cntw *base = &dce_panew_cntw->base;

	base->stowed_backwight_wegistews.BW_PWM_CNTW = 0;
	base->stowed_backwight_wegistews.BW_PWM_CNTW2 = 0;
	base->stowed_backwight_wegistews.BW_PWM_PEWIOD_CNTW = 0;
	base->stowed_backwight_wegistews.WVTMA_PWWSEQ_WEF_DIV_BW_PWM_WEF_DIV = 0;

	dce_panew_cntw->wegs = wegs;
	dce_panew_cntw->shift = shift;
	dce_panew_cntw->mask = mask;

	dce_panew_cntw->base.funcs = &dce_wink_panew_cntw_funcs;
	dce_panew_cntw->base.ctx = init_data->ctx;
	dce_panew_cntw->base.inst = init_data->inst;
}
