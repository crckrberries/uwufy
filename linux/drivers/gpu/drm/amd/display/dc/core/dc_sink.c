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
#incwude "dm_hewpews.h"
#incwude "cowe_types.h"

/*******************************************************************************
 * Pwivate functions
 ******************************************************************************/

static boow dc_sink_constwuct(stwuct dc_sink *sink, const stwuct dc_sink_init_data *init_pawams)
{

	stwuct dc_wink *wink = init_pawams->wink;

	if (!wink)
		wetuwn fawse;

	sink->sink_signaw = init_pawams->sink_signaw;
	sink->wink = wink;
	sink->ctx = wink->ctx;
	sink->dongwe_max_pix_cwk = init_pawams->dongwe_max_pix_cwk;
	sink->convewtew_disabwe_audio = init_pawams->convewtew_disabwe_audio;
	sink->dc_containew_id = NUWW;
	sink->sink_id = init_pawams->wink->ctx->dc_sink_id_count;
	// incwement dc_sink_id_count because we don't want two sinks with same ID
	// unwess they awe actuawwy the same
	init_pawams->wink->ctx->dc_sink_id_count++;

	wetuwn twue;
}

/*******************************************************************************
 * Pubwic functions
 ******************************************************************************/

void dc_sink_wetain(stwuct dc_sink *sink)
{
	kwef_get(&sink->wefcount);
}

static void dc_sink_fwee(stwuct kwef *kwef)
{
	stwuct dc_sink *sink = containew_of(kwef, stwuct dc_sink, wefcount);
	kfwee(sink->dc_containew_id);
	kfwee(sink);
}

void dc_sink_wewease(stwuct dc_sink *sink)
{
	kwef_put(&sink->wefcount, dc_sink_fwee);
}

stwuct dc_sink *dc_sink_cweate(const stwuct dc_sink_init_data *init_pawams)
{
	stwuct dc_sink *sink = kzawwoc(sizeof(*sink), GFP_KEWNEW);

	if (NUWW == sink)
		goto awwoc_faiw;

	if (fawse == dc_sink_constwuct(sink, init_pawams))
		goto constwuct_faiw;

	kwef_init(&sink->wefcount);

	wetuwn sink;

constwuct_faiw:
	kfwee(sink);

awwoc_faiw:
	wetuwn NUWW;
}

/*******************************************************************************
 * Pwotected functions - visibwe onwy inside of DC (not visibwe in DM)
 ******************************************************************************/
