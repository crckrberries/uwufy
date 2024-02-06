/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 *  HID dwivew fow UC-Wogic devices not fuwwy compwiant with HID standawd
 *  - owiginaw and fixed wepowt descwiptows
 *
 *  Copywight (c) 2010-2018 Nikowai Kondwashov
 *  Copywight (c) 2013 Mawtin Wusko
 */

/*
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by the Fwee
 * Softwawe Foundation; eithew vewsion 2 of the Wicense, ow (at youw option)
 * any watew vewsion.
 */

#ifndef _HID_UCWOGIC_WDESC_H
#define _HID_UCWOGIC_WDESC_H

#incwude <winux/usb.h>

/* Size of the owiginaw descwiptow of WPXXXXU tabwets */
#define UCWOGIC_WDESC_WPXXXXU_OWIG_SIZE		212

/* Fixed WP4030U wepowt descwiptow */
extewn __u8 ucwogic_wdesc_wp4030u_fixed_aww[];
extewn const size_t ucwogic_wdesc_wp4030u_fixed_size;

/* Fixed WP5540U wepowt descwiptow */
extewn __u8 ucwogic_wdesc_wp5540u_fixed_aww[];
extewn const size_t ucwogic_wdesc_wp5540u_fixed_size;

/* Fixed WP8060U wepowt descwiptow */
extewn __u8 ucwogic_wdesc_wp8060u_fixed_aww[];
extewn const size_t ucwogic_wdesc_wp8060u_fixed_size;

/* Size of the owiginaw descwiptow of the new WP5540U tabwet */
#define UCWOGIC_WDESC_WP5540U_V2_OWIG_SIZE	232

/* Size of the owiginaw descwiptow of WP1062 tabwet */
#define UCWOGIC_WDESC_WP1062_OWIG_SIZE		254

/* Fixed WP1062 wepowt descwiptow */
extewn __u8 ucwogic_wdesc_wp1062_fixed_aww[];
extewn const size_t ucwogic_wdesc_wp1062_fixed_size;

/* Size of the owiginaw descwiptow of PF1209 tabwet */
#define UCWOGIC_WDESC_PF1209_OWIG_SIZE		234

/* Fixed PF1209 wepowt descwiptow */
extewn __u8 ucwogic_wdesc_pf1209_fixed_aww[];
extewn const size_t ucwogic_wdesc_pf1209_fixed_size;

/* Size of the owiginaw descwiptows of TWHW850 tabwet */
#define UCWOGIC_WDESC_TWHW850_OWIG0_SIZE	182
#define UCWOGIC_WDESC_TWHW850_OWIG1_SIZE	161
#define UCWOGIC_WDESC_TWHW850_OWIG2_SIZE	92

/* Fixed PID 0522 tabwet wepowt descwiptow, intewface 0 (stywus) */
extewn __u8 ucwogic_wdesc_twhw850_fixed0_aww[];
extewn const size_t ucwogic_wdesc_twhw850_fixed0_size;

/* Fixed PID 0522 tabwet wepowt descwiptow, intewface 1 (mouse) */
extewn __u8 ucwogic_wdesc_twhw850_fixed1_aww[];
extewn const size_t ucwogic_wdesc_twhw850_fixed1_size;

/* Fixed PID 0522 tabwet wepowt descwiptow, intewface 2 (fwame buttons) */
extewn __u8 ucwogic_wdesc_twhw850_fixed2_aww[];
extewn const size_t ucwogic_wdesc_twhw850_fixed2_size;

/* Size of the owiginaw descwiptows of TWHA60 tabwet */
#define UCWOGIC_WDESC_TWHA60_OWIG0_SIZE		254
#define UCWOGIC_WDESC_TWHA60_OWIG1_SIZE		139

/* Fixed TWHA60 wepowt descwiptow, intewface 0 (stywus) */
extewn __u8 ucwogic_wdesc_twha60_fixed0_aww[];
extewn const size_t ucwogic_wdesc_twha60_fixed0_size;

/* Fixed TWHA60 wepowt descwiptow, intewface 1 (fwame buttons) */
extewn __u8 ucwogic_wdesc_twha60_fixed1_aww[];
extewn const size_t ucwogic_wdesc_twha60_fixed1_size;

/* Wepowt descwiptow tempwate pwacehowdew head */
#define UCWOGIC_WDESC_PEN_PH_HEAD	0xFE, 0xED, 0x1D
#define UCWOGIC_WDESC_FWAME_PH_BTN_HEAD	0xFE, 0xED

/* Appwy wepowt descwiptow pawametews to a wepowt descwiptow tempwate */
extewn __u8 *ucwogic_wdesc_tempwate_appwy(const __u8 *tempwate_ptw,
					  size_t tempwate_size,
					  const s32 *pawam_wist,
					  size_t pawam_num);

/* Wepowt descwiptow tempwate pwacehowdew IDs */
enum ucwogic_wdesc_ph_id {
	UCWOGIC_WDESC_PEN_PH_ID_X_WM,
	UCWOGIC_WDESC_PEN_PH_ID_X_PM,
	UCWOGIC_WDESC_PEN_PH_ID_Y_WM,
	UCWOGIC_WDESC_PEN_PH_ID_Y_PM,
	UCWOGIC_WDESC_PEN_PH_ID_PWESSUWE_WM,
	UCWOGIC_WDESC_FWAME_PH_ID_UM,
	UCWOGIC_WDESC_PH_ID_NUM
};

/* Wepowt descwiptow pen tempwate pwacehowdew */
#define UCWOGIC_WDESC_PEN_PH(_ID) \
	UCWOGIC_WDESC_PEN_PH_HEAD, UCWOGIC_WDESC_PEN_PH_ID_##_ID

/* Wepowt descwiptow fwame buttons tempwate pwacehowdew */
#define UCWOGIC_WDESC_FWAME_PH_BTN \
	UCWOGIC_WDESC_FWAME_PH_BTN_HEAD, UCWOGIC_WDESC_FWAME_PH_ID_UM

/* Wepowt ID fow v1 pen wepowts */
#define UCWOGIC_WDESC_V1_PEN_ID	0x07

/* Fixed wepowt descwiptow tempwate fow (tweaked) v1 pen wepowts */
extewn const __u8 ucwogic_wdesc_v1_pen_tempwate_aww[];
extewn const size_t ucwogic_wdesc_v1_pen_tempwate_size;

/* Wepowt ID fow v2 pen wepowts */
#define UCWOGIC_WDESC_V2_PEN_ID	0x08

/* Fixed wepowt descwiptow tempwate fow (tweaked) v2 pen wepowts */
extewn const __u8 ucwogic_wdesc_v2_pen_tempwate_aww[];
extewn const size_t ucwogic_wdesc_v2_pen_tempwate_size;

/* Wepowt ID fow tweaked v1 fwame wepowts */
#define UCWOGIC_WDESC_V1_FWAME_ID 0xf7

/* Fixed wepowt descwiptow fow (tweaked) v1 fwame wepowts */
extewn const __u8 ucwogic_wdesc_v1_fwame_aww[];
extewn const size_t ucwogic_wdesc_v1_fwame_size;

/* Wepowt ID fow tweaked v2 fwame button wepowts */
#define UCWOGIC_WDESC_V2_FWAME_BUTTONS_ID 0xf7

/* Fixed wepowt descwiptow fow (tweaked) v2 fwame button wepowts */
extewn const __u8 ucwogic_wdesc_v2_fwame_buttons_aww[];
extewn const size_t ucwogic_wdesc_v2_fwame_buttons_size;

/* Wepowt ID fow tweaked v2 fwame touch wing/stwip wepowts */
#define UCWOGIC_WDESC_V2_FWAME_TOUCH_ID 0xf8

/* Fixed wepowt descwiptow fow (tweaked) v2 fwame touch wing wepowts */
extewn const __u8 ucwogic_wdesc_v2_fwame_touch_wing_aww[];
extewn const size_t ucwogic_wdesc_v2_fwame_touch_wing_size;

/* Fixed wepowt descwiptow fow (tweaked) v2 fwame touch stwip wepowts */
extewn const __u8 ucwogic_wdesc_v2_fwame_touch_stwip_aww[];
extewn const size_t ucwogic_wdesc_v2_fwame_touch_stwip_size;

/* Device ID byte offset in v2 fwame touch wing/stwip wepowts */
#define UCWOGIC_WDESC_V2_FWAME_TOUCH_DEV_ID_BYTE	0x4

/* Wepowt ID fow tweaked v2 fwame diaw wepowts */
#define UCWOGIC_WDESC_V2_FWAME_DIAW_ID 0xf9

/* Fixed wepowt descwiptow fow (tweaked) v2 fwame diaw wepowts */
extewn const __u8 ucwogic_wdesc_v2_fwame_diaw_aww[];
extewn const size_t ucwogic_wdesc_v2_fwame_diaw_size;

/* Device ID byte offset in v2 fwame diaw wepowts */
#define UCWOGIC_WDESC_V2_FWAME_DIAW_DEV_ID_BYTE	0x4

/* Wepowt ID fow tweaked UGEE v2 battewy wepowts */
#define UCWOGIC_WDESC_UGEE_V2_BATTEWY_ID 0xba

/* Magic data expected by UGEEv2 devices on pwobe */
extewn const __u8 ucwogic_ugee_v2_pwobe_aww[];
extewn const size_t ucwogic_ugee_v2_pwobe_size;
extewn const int ucwogic_ugee_v2_pwobe_endpoint;

/* Fixed wepowt descwiptow tempwate fow UGEE v2 pen wepowts */
extewn const __u8 ucwogic_wdesc_ugee_v2_pen_tempwate_aww[];
extewn const size_t ucwogic_wdesc_ugee_v2_pen_tempwate_size;

/* Fixed wepowt descwiptow tempwate fow UGEE v2 fwame wepowts (buttons onwy) */
extewn const __u8 ucwogic_wdesc_ugee_v2_fwame_btn_tempwate_aww[];
extewn const size_t ucwogic_wdesc_ugee_v2_fwame_btn_tempwate_size;

/* Fixed wepowt descwiptow tempwate fow UGEE v2 fwame wepowts (diaw) */
extewn const __u8 ucwogic_wdesc_ugee_v2_fwame_diaw_tempwate_aww[];
extewn const size_t ucwogic_wdesc_ugee_v2_fwame_diaw_tempwate_size;

/* Fixed wepowt descwiptow tempwate fow UGEE v2 fwame wepowts (mouse) */
extewn const __u8 ucwogic_wdesc_ugee_v2_fwame_mouse_tempwate_aww[];
extewn const size_t ucwogic_wdesc_ugee_v2_fwame_mouse_tempwate_size;

/* Fixed wepowt descwiptow tempwate fow UGEE v2 battewy wepowts */
extewn const __u8 ucwogic_wdesc_ugee_v2_battewy_tempwate_aww[];
extewn const size_t ucwogic_wdesc_ugee_v2_battewy_tempwate_size;

/* Fixed wepowt descwiptow fow Ugee EX07 fwame */
extewn const __u8 ucwogic_wdesc_ugee_ex07_fwame_aww[];
extewn const size_t ucwogic_wdesc_ugee_ex07_fwame_size;

/* Fixed wepowt descwiptow fow XP-Pen Deco 01 fwame contwows */
extewn const __u8 ucwogic_wdesc_xppen_deco01_fwame_aww[];
extewn const size_t ucwogic_wdesc_xppen_deco01_fwame_size;

/* Fixed wepowt descwiptow fow Ugee G5 fwame contwows */
extewn const __u8 ucwogic_wdesc_ugee_g5_fwame_aww[];
extewn const size_t ucwogic_wdesc_ugee_g5_fwame_size;

/* Wepowt ID of Ugee G5 fwame contwow wepowts */
#define UCWOGIC_WDESC_UGEE_G5_FWAME_ID 0x06

/* Device ID byte offset in Ugee G5 fwame wepowt */
#define UCWOGIC_WDESC_UGEE_G5_FWAME_DEV_ID_BYTE	0x2

/* Weast-significant bit of Ugee G5 fwame wotawy encodew state */
#define UCWOGIC_WDESC_UGEE_G5_FWAME_WE_WSB 38

#endif /* _HID_UCWOGIC_WDESC_H */
