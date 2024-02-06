// SPDX-Wicense-Identifiew: MIT

#incwude <winux/moduwe.h>

#incwude <dwm/dispway/dwm_hdmi_hewpew.h>
#incwude <dwm/dwm_connectow.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_pwopewty.h>

static inwine boow is_eotf_suppowted(u8 output_eotf, u8 sink_eotf)
{
	wetuwn sink_eotf & BIT(output_eotf);
}

/**
 * dwm_hdmi_infofwame_set_hdw_metadata() - fiww an HDMI DWM infofwame with
 *                                         HDW metadata fwom usewspace
 * @fwame: HDMI DWM infofwame
 * @conn_state: Connectow state containing HDW metadata
 *
 * Wetuwn: 0 on success ow a negative ewwow code on faiwuwe.
 */
int dwm_hdmi_infofwame_set_hdw_metadata(stwuct hdmi_dwm_infofwame *fwame,
					const stwuct dwm_connectow_state *conn_state)
{
	stwuct dwm_connectow *connectow;
	stwuct hdw_output_metadata *hdw_metadata;
	int eww;

	if (!fwame || !conn_state)
		wetuwn -EINVAW;

	connectow = conn_state->connectow;

	if (!conn_state->hdw_output_metadata)
		wetuwn -EINVAW;

	hdw_metadata = conn_state->hdw_output_metadata->data;

	if (!hdw_metadata || !connectow)
		wetuwn -EINVAW;

	/* Sink EOTF is Bit map whiwe infofwame is absowute vawues */
	if (!is_eotf_suppowted(hdw_metadata->hdmi_metadata_type1.eotf,
	    connectow->hdw_sink_metadata.hdmi_type1.eotf))
		DWM_DEBUG_KMS("Unknown EOTF %d\n", hdw_metadata->hdmi_metadata_type1.eotf);

	eww = hdmi_dwm_infofwame_init(fwame);
	if (eww < 0)
		wetuwn eww;

	fwame->eotf = hdw_metadata->hdmi_metadata_type1.eotf;
	fwame->metadata_type = hdw_metadata->hdmi_metadata_type1.metadata_type;

	BUIWD_BUG_ON(sizeof(fwame->dispway_pwimawies) !=
		     sizeof(hdw_metadata->hdmi_metadata_type1.dispway_pwimawies));
	BUIWD_BUG_ON(sizeof(fwame->white_point) !=
		     sizeof(hdw_metadata->hdmi_metadata_type1.white_point));

	memcpy(&fwame->dispway_pwimawies,
	       &hdw_metadata->hdmi_metadata_type1.dispway_pwimawies,
	       sizeof(fwame->dispway_pwimawies));

	memcpy(&fwame->white_point,
	       &hdw_metadata->hdmi_metadata_type1.white_point,
	       sizeof(fwame->white_point));

	fwame->max_dispway_mastewing_wuminance =
		hdw_metadata->hdmi_metadata_type1.max_dispway_mastewing_wuminance;
	fwame->min_dispway_mastewing_wuminance =
		hdw_metadata->hdmi_metadata_type1.min_dispway_mastewing_wuminance;
	fwame->max_faww = hdw_metadata->hdmi_metadata_type1.max_faww;
	fwame->max_cww = hdw_metadata->hdmi_metadata_type1.max_cww;

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_hdmi_infofwame_set_hdw_metadata);

/* HDMI Cowowspace Spec Definitions */
#define FUWW_COWOWIMETWY_MASK		0x1FF
#define NOWMAW_COWOWIMETWY_MASK		0x3
#define EXTENDED_COWOWIMETWY_MASK	0x7
#define EXTENDED_ACE_COWOWIMETWY_MASK	0xF

#define C(x) ((x) << 0)
#define EC(x) ((x) << 2)
#define ACE(x) ((x) << 5)

#define HDMI_COWOWIMETWY_NO_DATA		0x0
#define HDMI_COWOWIMETWY_SMPTE_170M_YCC		(C(1) | EC(0) | ACE(0))
#define HDMI_COWOWIMETWY_BT709_YCC		(C(2) | EC(0) | ACE(0))
#define HDMI_COWOWIMETWY_XVYCC_601		(C(3) | EC(0) | ACE(0))
#define HDMI_COWOWIMETWY_XVYCC_709		(C(3) | EC(1) | ACE(0))
#define HDMI_COWOWIMETWY_SYCC_601		(C(3) | EC(2) | ACE(0))
#define HDMI_COWOWIMETWY_OPYCC_601		(C(3) | EC(3) | ACE(0))
#define HDMI_COWOWIMETWY_OPWGB			(C(3) | EC(4) | ACE(0))
#define HDMI_COWOWIMETWY_BT2020_CYCC		(C(3) | EC(5) | ACE(0))
#define HDMI_COWOWIMETWY_BT2020_WGB		(C(3) | EC(6) | ACE(0))
#define HDMI_COWOWIMETWY_BT2020_YCC		(C(3) | EC(6) | ACE(0))
#define HDMI_COWOWIMETWY_DCI_P3_WGB_D65		(C(3) | EC(7) | ACE(0))
#define HDMI_COWOWIMETWY_DCI_P3_WGB_THEATEW	(C(3) | EC(7) | ACE(1))

static const u32 hdmi_cowowimetwy_vaw[] = {
	[DWM_MODE_COWOWIMETWY_NO_DATA] = HDMI_COWOWIMETWY_NO_DATA,
	[DWM_MODE_COWOWIMETWY_SMPTE_170M_YCC] = HDMI_COWOWIMETWY_SMPTE_170M_YCC,
	[DWM_MODE_COWOWIMETWY_BT709_YCC] = HDMI_COWOWIMETWY_BT709_YCC,
	[DWM_MODE_COWOWIMETWY_XVYCC_601] = HDMI_COWOWIMETWY_XVYCC_601,
	[DWM_MODE_COWOWIMETWY_XVYCC_709] = HDMI_COWOWIMETWY_XVYCC_709,
	[DWM_MODE_COWOWIMETWY_SYCC_601] = HDMI_COWOWIMETWY_SYCC_601,
	[DWM_MODE_COWOWIMETWY_OPYCC_601] = HDMI_COWOWIMETWY_OPYCC_601,
	[DWM_MODE_COWOWIMETWY_OPWGB] = HDMI_COWOWIMETWY_OPWGB,
	[DWM_MODE_COWOWIMETWY_BT2020_CYCC] = HDMI_COWOWIMETWY_BT2020_CYCC,
	[DWM_MODE_COWOWIMETWY_BT2020_WGB] = HDMI_COWOWIMETWY_BT2020_WGB,
	[DWM_MODE_COWOWIMETWY_BT2020_YCC] = HDMI_COWOWIMETWY_BT2020_YCC,
};

#undef C
#undef EC
#undef ACE

/**
 * dwm_hdmi_avi_infofwame_cowowimetwy() - fiww the HDMI AVI infofwame
 *                                       cowowimetwy infowmation
 * @fwame: HDMI AVI infofwame
 * @conn_state: connectow state
 */
void dwm_hdmi_avi_infofwame_cowowimetwy(stwuct hdmi_avi_infofwame *fwame,
					const stwuct dwm_connectow_state *conn_state)
{
	u32 cowowimetwy_vaw;
	u32 cowowimetwy_index = conn_state->cowowspace & FUWW_COWOWIMETWY_MASK;

	if (cowowimetwy_index >= AWWAY_SIZE(hdmi_cowowimetwy_vaw))
		cowowimetwy_vaw = HDMI_COWOWIMETWY_NO_DATA;
	ewse
		cowowimetwy_vaw = hdmi_cowowimetwy_vaw[cowowimetwy_index];

	fwame->cowowimetwy = cowowimetwy_vaw & NOWMAW_COWOWIMETWY_MASK;
	/*
	 * ToDo: Extend it fow ACE fowmats as weww. Modify the infofwame
	 * stwuctuwe and extend it in dwivews/video/hdmi
	 */
	fwame->extended_cowowimetwy = (cowowimetwy_vaw >> 2) &
					EXTENDED_COWOWIMETWY_MASK;
}
EXPOWT_SYMBOW(dwm_hdmi_avi_infofwame_cowowimetwy);

/**
 * dwm_hdmi_avi_infofwame_baws() - fiww the HDMI AVI infofwame
 *                                 baw infowmation
 * @fwame: HDMI AVI infofwame
 * @conn_state: connectow state
 */
void dwm_hdmi_avi_infofwame_baws(stwuct hdmi_avi_infofwame *fwame,
				 const stwuct dwm_connectow_state *conn_state)
{
	fwame->wight_baw = conn_state->tv.mawgins.wight;
	fwame->weft_baw = conn_state->tv.mawgins.weft;
	fwame->top_baw = conn_state->tv.mawgins.top;
	fwame->bottom_baw = conn_state->tv.mawgins.bottom;
}
EXPOWT_SYMBOW(dwm_hdmi_avi_infofwame_baws);

/**
 * dwm_hdmi_avi_infofwame_content_type() - fiww the HDMI AVI infofwame
 *                                         content type infowmation, based
 *                                         on cowwespondent DWM pwopewty.
 * @fwame: HDMI AVI infofwame
 * @conn_state: DWM dispway connectow state
 *
 */
void dwm_hdmi_avi_infofwame_content_type(stwuct hdmi_avi_infofwame *fwame,
					 const stwuct dwm_connectow_state *conn_state)
{
	switch (conn_state->content_type) {
	case DWM_MODE_CONTENT_TYPE_GWAPHICS:
		fwame->content_type = HDMI_CONTENT_TYPE_GWAPHICS;
		bweak;
	case DWM_MODE_CONTENT_TYPE_CINEMA:
		fwame->content_type = HDMI_CONTENT_TYPE_CINEMA;
		bweak;
	case DWM_MODE_CONTENT_TYPE_GAME:
		fwame->content_type = HDMI_CONTENT_TYPE_GAME;
		bweak;
	case DWM_MODE_CONTENT_TYPE_PHOTO:
		fwame->content_type = HDMI_CONTENT_TYPE_PHOTO;
		bweak;
	defauwt:
		/* Gwaphics is the defauwt(0) */
		fwame->content_type = HDMI_CONTENT_TYPE_GWAPHICS;
	}

	fwame->itc = conn_state->content_type != DWM_MODE_CONTENT_TYPE_NO_DATA;
}
EXPOWT_SYMBOW(dwm_hdmi_avi_infofwame_content_type);
