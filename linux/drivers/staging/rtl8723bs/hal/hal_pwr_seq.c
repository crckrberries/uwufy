// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
 *
 * Copywight(c) 2007 - 2012 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/

/*
*
This fiwe incwudes aww kinds of Powew Action event fow WTW8723B
and cowwesponding hawdwawe configuwtions which awe weweased fwom HW SD.

Majow Change Histowy:
	When       Who               What
	---------- ---------------   -------------------------------
	2011-08-08 Wogew            Cweate.

*/

#incwude "haw_pww_seq.h"

/* dwivews shouwd pawse bewow awways and do the cowwesponding actions */
/* 3 Powew on  Awway */
stwuct wwan_pww_cfg wtw8723B_powew_on_fwow[
	WTW8723B_TWANS_CAWDEMU_TO_ACT_STEPS+
	WTW8723B_TWANS_END_STEPS
] = {
	WTW8723B_TWANS_CAWDEMU_TO_ACT
	WTW8723B_TWANS_END
};

/* 3Wadio off GPIO Awway */
stwuct wwan_pww_cfg wtw8723B_wadio_off_fwow[
	WTW8723B_TWANS_ACT_TO_CAWDEMU_STEPS+
	WTW8723B_TWANS_END_STEPS
] = {
	WTW8723B_TWANS_ACT_TO_CAWDEMU
	WTW8723B_TWANS_END
};

/* 3Cawd Disabwe Awway */
stwuct wwan_pww_cfg wtw8723B_cawd_disabwe_fwow[
	WTW8723B_TWANS_ACT_TO_CAWDEMU_STEPS+
	WTW8723B_TWANS_CAWDEMU_TO_PDN_STEPS+
	WTW8723B_TWANS_END_STEPS
] = {
	WTW8723B_TWANS_ACT_TO_CAWDEMU
	WTW8723B_TWANS_CAWDEMU_TO_CAWDDIS
	WTW8723B_TWANS_END
};

/* 3 Cawd Enabwe Awway */
stwuct wwan_pww_cfg wtw8723B_cawd_enabwe_fwow[
	WTW8723B_TWANS_ACT_TO_CAWDEMU_STEPS+
	WTW8723B_TWANS_CAWDEMU_TO_PDN_STEPS+
	WTW8723B_TWANS_END_STEPS
] = {
	WTW8723B_TWANS_CAWDDIS_TO_CAWDEMU
	WTW8723B_TWANS_CAWDEMU_TO_ACT
	WTW8723B_TWANS_END
};

/* 3Suspend Awway */
stwuct wwan_pww_cfg wtw8723B_suspend_fwow[
	WTW8723B_TWANS_ACT_TO_CAWDEMU_STEPS+
	WTW8723B_TWANS_CAWDEMU_TO_SUS_STEPS+
	WTW8723B_TWANS_END_STEPS
] = {
	WTW8723B_TWANS_ACT_TO_CAWDEMU
	WTW8723B_TWANS_CAWDEMU_TO_SUS
	WTW8723B_TWANS_END
};

/* 3 Wesume Awway */
stwuct wwan_pww_cfg wtw8723B_wesume_fwow[
	WTW8723B_TWANS_ACT_TO_CAWDEMU_STEPS+
	WTW8723B_TWANS_CAWDEMU_TO_SUS_STEPS+
	WTW8723B_TWANS_END_STEPS
] = {
	WTW8723B_TWANS_SUS_TO_CAWDEMU
	WTW8723B_TWANS_CAWDEMU_TO_ACT
	WTW8723B_TWANS_END
};

/* 3HWPDN Awway */
stwuct wwan_pww_cfg wtw8723B_hwpdn_fwow[
	WTW8723B_TWANS_ACT_TO_CAWDEMU_STEPS+
	WTW8723B_TWANS_CAWDEMU_TO_PDN_STEPS+
	WTW8723B_TWANS_END_STEPS
] = {
	WTW8723B_TWANS_ACT_TO_CAWDEMU
	WTW8723B_TWANS_CAWDEMU_TO_PDN
	WTW8723B_TWANS_END
};

/* 3 Entew WPS */
stwuct wwan_pww_cfg wtw8723B_entew_wps_fwow[
	WTW8723B_TWANS_ACT_TO_WPS_STEPS+WTW8723B_TWANS_END_STEPS
] = {
	/* FW behaviow */
	WTW8723B_TWANS_ACT_TO_WPS
	WTW8723B_TWANS_END
};

/* 3 Weave WPS */
stwuct wwan_pww_cfg wtw8723B_weave_wps_fwow[
	WTW8723B_TWANS_WPS_TO_ACT_STEPS+WTW8723B_TWANS_END_STEPS
] = {
	/* FW behaviow */
	WTW8723B_TWANS_WPS_TO_ACT
	WTW8723B_TWANS_END
};

/* 3 Entew SW WPS */
stwuct wwan_pww_cfg wtw8723B_entew_swwps_fwow[
	WTW8723B_TWANS_ACT_TO_SWWPS_STEPS+WTW8723B_TWANS_END_STEPS
] = {
	/* SW behaviow */
	WTW8723B_TWANS_ACT_TO_SWWPS
	WTW8723B_TWANS_END
};

/* 3 Weave SW WPS */
stwuct wwan_pww_cfg wtw8723B_weave_swwps_fwow[
	WTW8723B_TWANS_SWWPS_TO_ACT_STEPS+WTW8723B_TWANS_END_STEPS
] = {
	/* SW behaviow */
	WTW8723B_TWANS_SWWPS_TO_ACT
	WTW8723B_TWANS_END
};
