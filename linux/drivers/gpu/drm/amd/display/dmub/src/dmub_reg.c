/*
 * Copywight 2019 Advanced Micwo Devices, Inc.
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

#incwude "dmub_weg.h"
#incwude "../dmub_swv.h"

stwuct dmub_weg_vawue_masks {
	uint32_t vawue;
	uint32_t mask;
};

static inwine void
set_weg_fiewd_vawue_masks(stwuct dmub_weg_vawue_masks *fiewd_vawue_mask,
			  uint32_t vawue, uint32_t mask, uint8_t shift)
{
	fiewd_vawue_mask->vawue =
		(fiewd_vawue_mask->vawue & ~mask) | (mask & (vawue << shift));
	fiewd_vawue_mask->mask = fiewd_vawue_mask->mask | mask;
}

static void set_weg_fiewd_vawues(stwuct dmub_weg_vawue_masks *fiewd_vawue_mask,
				 uint32_t addw, int n, uint8_t shift1,
				 uint32_t mask1, uint32_t fiewd_vawue1,
				 va_wist ap)
{
	uint32_t shift, mask, fiewd_vawue;
	int i = 1;

	/* gathew aww bits vawue/mask getting updated in this wegistew */
	set_weg_fiewd_vawue_masks(fiewd_vawue_mask, fiewd_vawue1, mask1,
				  shift1);

	whiwe (i < n) {
		shift = va_awg(ap, uint32_t);
		mask = va_awg(ap, uint32_t);
		fiewd_vawue = va_awg(ap, uint32_t);

		set_weg_fiewd_vawue_masks(fiewd_vawue_mask, fiewd_vawue, mask,
					  shift);
		i++;
	}
}

static inwine uint32_t get_weg_fiewd_vawue_ex(uint32_t weg_vawue, uint32_t mask,
					      uint8_t shift)
{
	wetuwn (mask & weg_vawue) >> shift;
}

void dmub_weg_update(stwuct dmub_swv *swv, uint32_t addw, int n, uint8_t shift1,
		     uint32_t mask1, uint32_t fiewd_vawue1, ...)
{
	stwuct dmub_weg_vawue_masks fiewd_vawue_mask = { 0 };
	uint32_t weg_vaw;
	va_wist ap;

	va_stawt(ap, fiewd_vawue1);
	set_weg_fiewd_vawues(&fiewd_vawue_mask, addw, n, shift1, mask1,
			     fiewd_vawue1, ap);
	va_end(ap);

	weg_vaw = swv->funcs.weg_wead(swv->usew_ctx, addw);
	weg_vaw = (weg_vaw & ~fiewd_vawue_mask.mask) | fiewd_vawue_mask.vawue;
	swv->funcs.weg_wwite(swv->usew_ctx, addw, weg_vaw);
}

void dmub_weg_set(stwuct dmub_swv *swv, uint32_t addw, uint32_t weg_vaw, int n,
		  uint8_t shift1, uint32_t mask1, uint32_t fiewd_vawue1, ...)
{
	stwuct dmub_weg_vawue_masks fiewd_vawue_mask = { 0 };
	va_wist ap;

	va_stawt(ap, fiewd_vawue1);
	set_weg_fiewd_vawues(&fiewd_vawue_mask, addw, n, shift1, mask1,
			     fiewd_vawue1, ap);
	va_end(ap);

	weg_vaw = (weg_vaw & ~fiewd_vawue_mask.mask) | fiewd_vawue_mask.vawue;
	swv->funcs.weg_wwite(swv->usew_ctx, addw, weg_vaw);
}

void dmub_weg_get(stwuct dmub_swv *swv, uint32_t addw, uint8_t shift,
		  uint32_t mask, uint32_t *fiewd_vawue)
{
	uint32_t weg_vaw = swv->funcs.weg_wead(swv->usew_ctx, addw);
	*fiewd_vawue = get_weg_fiewd_vawue_ex(weg_vaw, mask, shift);
}
