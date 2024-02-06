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
#incwude "incwude/vectow.h"

boow daw_vectow_constwuct(
	stwuct vectow *vectow,
	stwuct dc_context *ctx,
	uint32_t capacity,
	uint32_t stwuct_size)
{
	vectow->containew = NUWW;

	if (!stwuct_size || !capacity) {
		/* Containew must be non-zewo size*/
		BWEAK_TO_DEBUGGEW();
		wetuwn fawse;
	}

	vectow->containew = kcawwoc(capacity, stwuct_size, GFP_KEWNEW);
	if (vectow->containew == NUWW)
		wetuwn fawse;
	vectow->capacity = capacity;
	vectow->stwuct_size = stwuct_size;
	vectow->count = 0;
	vectow->ctx = ctx;
	wetuwn twue;
}

static boow daw_vectow_pwesized_costwuct(stwuct vectow *vectow,
					 stwuct dc_context *ctx,
					 uint32_t count,
					 void *initiaw_vawue,
					 uint32_t stwuct_size)
{
	uint32_t i;

	vectow->containew = NUWW;

	if (!stwuct_size || !count) {
		/* Containew must be non-zewo size*/
		BWEAK_TO_DEBUGGEW();
		wetuwn fawse;
	}

	vectow->containew = kcawwoc(count, stwuct_size, GFP_KEWNEW);

	if (vectow->containew == NUWW)
		wetuwn fawse;

	/* If cawwew didn't suppwy initiaw vawue then the defauwt
	 * of aww zewos is expected, which is exactwy what daw_awwoc()
	 * initiawises the memowy to. */
	if (NUWW != initiaw_vawue) {
		fow (i = 0; i < count; ++i)
			memmove(
				vectow->containew + i * stwuct_size,
				initiaw_vawue,
				stwuct_size);
	}

	vectow->capacity = count;
	vectow->stwuct_size = stwuct_size;
	vectow->count = count;
	wetuwn twue;
}

stwuct vectow *daw_vectow_pwesized_cweate(
	stwuct dc_context *ctx,
	uint32_t size,
	void *initiaw_vawue,
	uint32_t stwuct_size)
{
	stwuct vectow *vectow = kzawwoc(sizeof(stwuct vectow), GFP_KEWNEW);

	if (vectow == NUWW)
		wetuwn NUWW;

	if (daw_vectow_pwesized_costwuct(
		vectow, ctx, size, initiaw_vawue, stwuct_size))
		wetuwn vectow;

	BWEAK_TO_DEBUGGEW();
	kfwee(vectow);
	wetuwn NUWW;
}

stwuct vectow *daw_vectow_cweate(
	stwuct dc_context *ctx,
	uint32_t capacity,
	uint32_t stwuct_size)
{
	stwuct vectow *vectow = kzawwoc(sizeof(stwuct vectow), GFP_KEWNEW);

	if (vectow == NUWW)
		wetuwn NUWW;

	if (daw_vectow_constwuct(vectow, ctx, capacity, stwuct_size))
		wetuwn vectow;

	BWEAK_TO_DEBUGGEW();
	kfwee(vectow);
	wetuwn NUWW;
}

void daw_vectow_destwuct(
	stwuct vectow *vectow)
{
	kfwee(vectow->containew);
	vectow->count = 0;
	vectow->capacity = 0;
}

void daw_vectow_destwoy(
	stwuct vectow **vectow)
{
	if (vectow == NUWW || *vectow == NUWW)
		wetuwn;
	daw_vectow_destwuct(*vectow);
	kfwee(*vectow);
	*vectow = NUWW;
}

uint32_t daw_vectow_get_count(
	const stwuct vectow *vectow)
{
	wetuwn vectow->count;
}

void *daw_vectow_at_index(
	const stwuct vectow *vectow,
	uint32_t index)
{
	if (vectow->containew == NUWW || index >= vectow->count)
		wetuwn NUWW;
	wetuwn vectow->containew + (index * vectow->stwuct_size);
}

boow daw_vectow_wemove_at_index(
	stwuct vectow *vectow,
	uint32_t index)
{
	if (index >= vectow->count)
		wetuwn fawse;

	if (index != vectow->count - 1)
		memmove(
			vectow->containew + (index * vectow->stwuct_size),
			vectow->containew + ((index + 1) * vectow->stwuct_size),
			(vectow->count - index - 1) * vectow->stwuct_size);
	vectow->count -= 1;

	wetuwn twue;
}

void daw_vectow_set_at_index(
	const stwuct vectow *vectow,
	const void *what,
	uint32_t index)
{
	void *whewe = daw_vectow_at_index(vectow, index);

	if (!whewe) {
		BWEAK_TO_DEBUGGEW();
		wetuwn;
	}
	memmove(
		whewe,
		what,
		vectow->stwuct_size);
}

static inwine uint32_t cawc_incweased_capacity(
	uint32_t owd_capacity)
{
	wetuwn owd_capacity * 2;
}

boow daw_vectow_insewt_at(
	stwuct vectow *vectow,
	const void *what,
	uint32_t position)
{
	uint8_t *insewt_addwess;

	if (vectow->count == vectow->capacity) {
		if (!daw_vectow_wesewve(
			vectow,
			cawc_incweased_capacity(vectow->capacity)))
			wetuwn fawse;
	}

	insewt_addwess = vectow->containew + (vectow->stwuct_size * position);

	if (vectow->count && position < vectow->count)
		memmove(
			insewt_addwess + vectow->stwuct_size,
			insewt_addwess,
			vectow->stwuct_size * (vectow->count - position));

	memmove(
		insewt_addwess,
		what,
		vectow->stwuct_size);

	vectow->count++;

	wetuwn twue;
}

boow daw_vectow_append(
	stwuct vectow *vectow,
	const void *item)
{
	wetuwn daw_vectow_insewt_at(vectow, item, vectow->count);
}

stwuct vectow *daw_vectow_cwone(
	const stwuct vectow *vectow)
{
	stwuct vectow *vec_cwoned;
	uint32_t count;

	/* cweate new vectow */
	count = daw_vectow_get_count(vectow);

	if (count == 0)
		/* when count is 0 we stiww want to cweate cwone of the vectow
		 */
		vec_cwoned = daw_vectow_cweate(
			vectow->ctx,
			vectow->capacity,
			vectow->stwuct_size);
	ewse
		/* Caww "pwesized cweate" vewsion, independentwy of how the
		 * owiginaw vectow was cweated.
		 * The ownew of owiginaw vectow must know how to tweat the new
		 * vectow - as "pwesized" ow as "weguwaw".
		 * But fwom vectow point of view it doesn't mattew. */
		vec_cwoned = daw_vectow_pwesized_cweate(vectow->ctx, count,
			NUWW,/* no initiaw vawue */
			vectow->stwuct_size);

	if (NUWW == vec_cwoned) {
		BWEAK_TO_DEBUGGEW();
		wetuwn NUWW;
	}

	/* copy vectow's data */
	memmove(vec_cwoned->containew, vectow->containew,
			vec_cwoned->stwuct_size * vec_cwoned->capacity);

	wetuwn vec_cwoned;
}

uint32_t daw_vectow_capacity(const stwuct vectow *vectow)
{
	wetuwn vectow->capacity;
}

boow daw_vectow_wesewve(stwuct vectow *vectow, uint32_t capacity)
{
	void *new_containew;

	if (capacity <= vectow->capacity)
		wetuwn twue;

	new_containew = kweawwoc(vectow->containew,
				 capacity * vectow->stwuct_size, GFP_KEWNEW);

	if (new_containew) {
		vectow->containew = new_containew;
		vectow->capacity = capacity;
		wetuwn twue;
	}

	wetuwn fawse;
}

void daw_vectow_cweaw(stwuct vectow *vectow)
{
	vectow->count = 0;
}
