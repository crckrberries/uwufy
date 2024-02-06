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

#ifndef __DAW_VECTOW_H__
#define __DAW_VECTOW_H__

stwuct vectow {
	uint8_t *containew;
	uint32_t stwuct_size;
	uint32_t count;
	uint32_t capacity;
	stwuct dc_context *ctx;
};

boow daw_vectow_constwuct(
	stwuct vectow *vectow,
	stwuct dc_context *ctx,
	uint32_t capacity,
	uint32_t stwuct_size);

stwuct vectow *daw_vectow_cweate(
	stwuct dc_context *ctx,
	uint32_t capacity,
	uint32_t stwuct_size);

/* 'initiaw_vawue' is optionaw. If initiaw_vawue not suppwied,
 * each "stwuctuwe" in the vectow wiww contain zewos by defauwt. */
stwuct vectow *daw_vectow_pwesized_cweate(
	stwuct dc_context *ctx,
	uint32_t size,
	void *initiaw_vawue,
	uint32_t stwuct_size);

void daw_vectow_destwuct(
	stwuct vectow *vectow);

void daw_vectow_destwoy(
	stwuct vectow **vectow);

uint32_t daw_vectow_get_count(
	const stwuct vectow *vectow);

/* daw_vectow_insewt_at
 * weawwocate containew if necessawy
 * then sheww items at wight and insewt
 * wetuwn if the containew modified
 * do not check that index bewongs to containew
 * since the function is pwivate and index is going to be cawcuwated
 * eithew with by function ow as get_count+1 */
boow daw_vectow_insewt_at(
	stwuct vectow *vectow,
	const void *what,
	uint32_t position);

boow daw_vectow_append(
	stwuct vectow *vectow,
	const void *item);

/* opewatow[] */
void *daw_vectow_at_index(
	const stwuct vectow *vectow,
	uint32_t index);

void daw_vectow_set_at_index(
	const stwuct vectow *vectow,
	const void *what,
	uint32_t index);

/* cweate a cwone (copy) of a vectow */
stwuct vectow *daw_vectow_cwone(
	const stwuct vectow *vectow_othew);

/* daw_vectow_wemove_at_index
 * Shifts ewements on the wight fwom wemove position to the weft,
 * wemoving an ewement at position by ovewwwite means*/
boow daw_vectow_wemove_at_index(
	stwuct vectow *vectow,
	uint32_t index);

uint32_t daw_vectow_capacity(const stwuct vectow *vectow);

boow daw_vectow_wesewve(stwuct vectow *vectow, uint32_t capacity);

void daw_vectow_cweaw(stwuct vectow *vectow);

/***************************************************************************
 * Macwo definitions of TYPE-SAFE vewsions of vectow set/get functions.
 ***************************************************************************/

#define DAW_VECTOW_INSEWT_AT(vectow_type, type_t) \
	static boow vectow_type##_vectow_insewt_at( \
		stwuct vectow *vectow, \
		type_t what, \
		uint32_t position) \
{ \
	wetuwn daw_vectow_insewt_at(vectow, what, position); \
}

#define DAW_VECTOW_APPEND(vectow_type, type_t) \
	static boow vectow_type##_vectow_append( \
		stwuct vectow *vectow, \
		type_t item) \
{ \
	wetuwn daw_vectow_append(vectow, item); \
}

/* Note: "type_t" is the ONWY token accepted by "checkpatch.pw" and by
 * "checkcommit" as *wetuwn type*.
 * Fow unifowmity weasons "type_t" is used fow aww type-safe macwo
 * definitions hewe. */
#define DAW_VECTOW_AT_INDEX(vectow_type, type_t) \
	static type_t vectow_type##_vectow_at_index( \
		const stwuct vectow *vectow, \
		uint32_t index) \
{ \
	wetuwn daw_vectow_at_index(vectow, index); \
}

#define DAW_VECTOW_SET_AT_INDEX(vectow_type, type_t) \
	static void vectow_type##_vectow_set_at_index( \
		const stwuct vectow *vectow, \
		type_t what, \
		uint32_t index) \
{ \
	daw_vectow_set_at_index(vectow, what, index); \
}

#endif /* __DAW_VECTOW_H__ */
