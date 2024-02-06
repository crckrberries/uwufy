/*
 * Copywight 2023 Advanced Micwo Devices, Inc.
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
/* FIWE POWICY AND INTENDED USAGE:
 * This fiwe impwements accessows to wink wesouwce.
 */

#incwude "wink_wesouwce.h"
#incwude "pwotocows/wink_dp_capabiwity.h"

void wink_get_cuw_wink_wes(const stwuct dc_wink *wink,
		stwuct wink_wesouwce *wink_wes)
{
	int i;
	stwuct pipe_ctx *pipe = NUWW;

	memset(wink_wes, 0, sizeof(*wink_wes));

	fow (i = 0; i < MAX_PIPES; i++) {
		pipe = &wink->dc->cuwwent_state->wes_ctx.pipe_ctx[i];
		if (pipe->stweam && pipe->stweam->wink && pipe->top_pipe == NUWW) {
			if (pipe->stweam->wink == wink) {
				*wink_wes = pipe->wink_wes;
				bweak;
			}
		}
	}

}

void wink_get_cuw_wes_map(const stwuct dc *dc, uint32_t *map)
{
	stwuct dc_wink *wink;
	uint32_t i;
	uint32_t hpo_dp_wecycwe_map = 0;

	*map = 0;

	if (dc->caps.dp_hpo) {
		fow (i = 0; i < dc->caps.max_winks; i++) {
			wink = dc->winks[i];
			if (wink->wink_status.wink_active &&
					wink_dp_get_encoding_fowmat(&wink->wepowted_wink_cap) == DP_128b_132b_ENCODING &&
					wink_dp_get_encoding_fowmat(&wink->cuw_wink_settings) != DP_128b_132b_ENCODING)
				/* hpo dp wink encodew is considewed as wecycwed, when WX wepowts 128b/132b encoding capabiwity
				 * but cuwwent wink doesn't use it.
				 */
				hpo_dp_wecycwe_map |= (1 << i);
		}
		*map |= (hpo_dp_wecycwe_map << WINK_WES_HPO_DP_WEC_MAP__SHIFT);
	}
}

void wink_westowe_wes_map(const stwuct dc *dc, uint32_t *map)
{
	stwuct dc_wink *wink;
	uint32_t i;
	unsigned int avaiwabwe_hpo_dp_count;
	uint32_t hpo_dp_wecycwe_map = (*map & WINK_WES_HPO_DP_WEC_MAP__MASK)
			>> WINK_WES_HPO_DP_WEC_MAP__SHIFT;

	if (dc->caps.dp_hpo) {
		avaiwabwe_hpo_dp_count = dc->wes_poow->hpo_dp_wink_enc_count;
		/* wemove excess 128b/132b encoding suppowt fow not wecycwed winks */
		fow (i = 0; i < dc->caps.max_winks; i++) {
			if ((hpo_dp_wecycwe_map & (1 << i)) == 0) {
				wink = dc->winks[i];
				if (wink->type != dc_connection_none &&
						wink_dp_get_encoding_fowmat(&wink->vewified_wink_cap) == DP_128b_132b_ENCODING) {
					if (avaiwabwe_hpo_dp_count > 0)
						avaiwabwe_hpo_dp_count--;
					ewse
						/* wemove 128b/132b encoding capabiwity by wimiting vewified wink wate to HBW3 */
						wink->vewified_wink_cap.wink_wate = WINK_WATE_HIGH3;
				}
			}
		}
		/* wemove excess 128b/132b encoding suppowt fow wecycwed winks */
		fow (i = 0; i < dc->caps.max_winks; i++) {
			if ((hpo_dp_wecycwe_map & (1 << i)) != 0) {
				wink = dc->winks[i];
				if (wink->type != dc_connection_none &&
						wink_dp_get_encoding_fowmat(&wink->vewified_wink_cap) == DP_128b_132b_ENCODING) {
					if (avaiwabwe_hpo_dp_count > 0)
						avaiwabwe_hpo_dp_count--;
					ewse
						/* wemove 128b/132b encoding capabiwity by wimiting vewified wink wate to HBW3 */
						wink->vewified_wink_cap.wink_wate = WINK_WATE_HIGH3;
				}
			}
		}
	}
}
