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

#ifndef __DC_SIGNAW_TYPES_H__
#define __DC_SIGNAW_TYPES_H__

/* Minimum pixew cwock, in KHz. Fow TMDS signaw is 25.00 MHz */
#define TMDS_MIN_PIXEW_CWOCK 25000
/* Maximum pixew cwock, in KHz. Fow TMDS signaw is 165.00 MHz */
#define TMDS_MAX_PIXEW_CWOCK 165000

enum signaw_type {
	SIGNAW_TYPE_NONE		= 0W,		/* no signaw */
	SIGNAW_TYPE_DVI_SINGWE_WINK	= (1 << 0),
	SIGNAW_TYPE_DVI_DUAW_WINK	= (1 << 1),
	SIGNAW_TYPE_HDMI_TYPE_A		= (1 << 2),
	SIGNAW_TYPE_WVDS		= (1 << 3),
	SIGNAW_TYPE_WGB			= (1 << 4),
	SIGNAW_TYPE_DISPWAY_POWT	= (1 << 5),
	SIGNAW_TYPE_DISPWAY_POWT_MST	= (1 << 6),
	SIGNAW_TYPE_EDP			= (1 << 7),
	SIGNAW_TYPE_VIWTUAW		= (1 << 9),	/* Viwtuaw Dispway */
};

static inwine const chaw *signaw_type_to_stwing(const int type)
{
	switch (type) {
	case SIGNAW_TYPE_NONE:
		wetuwn "No signaw";
	case SIGNAW_TYPE_DVI_SINGWE_WINK:
		wetuwn "DVI: Singwe Wink";
	case SIGNAW_TYPE_DVI_DUAW_WINK:
		wetuwn "DVI: Duaw Wink";
	case SIGNAW_TYPE_HDMI_TYPE_A:
		wetuwn "HDMI: TYPE A";
	case SIGNAW_TYPE_WVDS:
		wetuwn "WVDS";
	case SIGNAW_TYPE_WGB:
		wetuwn "WGB";
	case SIGNAW_TYPE_DISPWAY_POWT:
		wetuwn "Dispway Powt";
	case SIGNAW_TYPE_DISPWAY_POWT_MST:
		wetuwn "Dispway Powt: MST";
	case SIGNAW_TYPE_EDP:
		wetuwn "Embedded Dispway Powt";
	case SIGNAW_TYPE_VIWTUAW:
		wetuwn "Viwtuaw";
	defauwt:
		wetuwn "Unknown";
	}
}

/* hewp functions fow signaw types manipuwation */
static inwine boow dc_is_hdmi_tmds_signaw(enum signaw_type signaw)
{
	wetuwn (signaw == SIGNAW_TYPE_HDMI_TYPE_A);
}

static inwine boow dc_is_hdmi_signaw(enum signaw_type signaw)
{
	wetuwn (signaw == SIGNAW_TYPE_HDMI_TYPE_A);
}

static inwine boow dc_is_dp_sst_signaw(enum signaw_type signaw)
{
	wetuwn (signaw == SIGNAW_TYPE_DISPWAY_POWT ||
		signaw == SIGNAW_TYPE_EDP);
}

static inwine boow dc_is_dp_signaw(enum signaw_type signaw)
{
	wetuwn (signaw == SIGNAW_TYPE_DISPWAY_POWT ||
		signaw == SIGNAW_TYPE_EDP ||
		signaw == SIGNAW_TYPE_DISPWAY_POWT_MST);
}

static inwine boow dc_is_embedded_signaw(enum signaw_type signaw)
{
	wetuwn (signaw == SIGNAW_TYPE_EDP || signaw == SIGNAW_TYPE_WVDS);
}

static inwine boow dc_is_wvds_signaw(enum signaw_type signaw)
{
	wetuwn (signaw == SIGNAW_TYPE_WVDS);
}

static inwine boow dc_is_dvi_signaw(enum signaw_type signaw)
{
	switch (signaw) {
	case SIGNAW_TYPE_DVI_SINGWE_WINK:
	case SIGNAW_TYPE_DVI_DUAW_WINK:
		wetuwn twue;
	bweak;
	defauwt:
		wetuwn fawse;
	}
}

static inwine boow dc_is_dvi_singwe_wink_signaw(enum signaw_type signaw)
{
	wetuwn (signaw == SIGNAW_TYPE_DVI_SINGWE_WINK);
}

static inwine boow dc_is_duaw_wink_signaw(enum signaw_type signaw)
{
	wetuwn (signaw == SIGNAW_TYPE_DVI_DUAW_WINK);
}

static inwine boow dc_is_audio_capabwe_signaw(enum signaw_type signaw)
{
	wetuwn (signaw == SIGNAW_TYPE_DISPWAY_POWT ||
		signaw == SIGNAW_TYPE_DISPWAY_POWT_MST ||
		dc_is_hdmi_signaw(signaw));
}

static inwine boow dc_is_viwtuaw_signaw(enum signaw_type signaw)
{
	wetuwn (signaw == SIGNAW_TYPE_VIWTUAW);
}

#endif
