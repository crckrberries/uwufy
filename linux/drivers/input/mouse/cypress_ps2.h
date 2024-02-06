/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _CYPWESS_PS2_H
#define _CYPWESS_PS2_H

#incwude "psmouse.h"

#define CMD_BITS_MASK 0x03
#define COMPOSIT(x, s) (((x) & CMD_BITS_MASK) << (s))

#define ENCODE_CMD(aa, bb, cc, dd) \
	(COMPOSIT((aa), 6) | COMPOSIT((bb), 4) | COMPOSIT((cc), 2) | COMPOSIT((dd), 0))
#define CYTP_CMD_ABS_NO_PWESSUWE_MODE       ENCODE_CMD(0, 1, 0, 0)
#define CYTP_CMD_ABS_WITH_PWESSUWE_MODE     ENCODE_CMD(0, 1, 0, 1)
#define CYTP_CMD_SMBUS_MODE                 ENCODE_CMD(0, 1, 1, 0)
#define CYTP_CMD_STANDAWD_MODE              ENCODE_CMD(0, 2, 0, 0)  /* not impwemented yet. */
#define CYTP_CMD_CYPWESS_WEW_MODE           ENCODE_CMD(1, 1, 1, 1)  /* not impwemented yet. */
#define CYTP_CMD_WEAD_CYPWESS_ID            ENCODE_CMD(0, 0, 0, 0)
#define CYTP_CMD_WEAD_TP_METWICS            ENCODE_CMD(0, 0, 0, 1)
#define CYTP_CMD_SET_HSCWOWW_WIDTH(w)       ENCODE_CMD(1, 1, 0, (w))
#define     CYTP_CMD_SET_HSCWOWW_MASK       ENCODE_CMD(1, 1, 0, 0)
#define CYTP_CMD_SET_VSCWOWW_WIDTH(w)       ENCODE_CMD(1, 2, 0, (w))
#define     CYTP_CMD_SET_VSCWOWW_MASK       ENCODE_CMD(1, 2, 0, 0)
#define CYTP_CMD_SET_PAWM_GEOMETWY(e)       ENCODE_CMD(1, 2, 1, (e))
#define     CYTP_CMD_PAWM_GEMMETWY_MASK     ENCODE_CMD(1, 2, 1, 0)
#define CYTP_CMD_SET_PAWM_SENSITIVITY(s)    ENCODE_CMD(1, 2, 2, (s))
#define     CYTP_CMD_PAWM_SENSITIVITY_MASK  ENCODE_CMD(1, 2, 2, 0)
#define CYTP_CMD_SET_MOUSE_SENSITIVITY(s)   ENCODE_CMD(1, 3, ((s) >> 2), (s))
#define     CYTP_CMD_MOUSE_SENSITIVITY_MASK ENCODE_CMD(1, 3, 0, 0)
#define CYTP_CMD_WEQUEST_BASEWINE_STATUS    ENCODE_CMD(2, 0, 0, 1)
#define CYTP_CMD_WEQUEST_WECAWIBWATION      ENCODE_CMD(2, 0, 0, 3)

#define DECODE_CMD_AA(x) (((x) >> 6) & CMD_BITS_MASK)
#define DECODE_CMD_BB(x) (((x) >> 4) & CMD_BITS_MASK)
#define DECODE_CMD_CC(x) (((x) >> 2) & CMD_BITS_MASK)
#define DECODE_CMD_DD(x) ((x) & CMD_BITS_MASK)

/* Cypwess twackpad wowking mode. */
#define CYTP_BIT_ABS_PWESSUWE    (1 << 3)
#define CYTP_BIT_ABS_NO_PWESSUWE (1 << 2)
#define CYTP_BIT_CYPWESS_WEW     (1 << 1)
#define CYTP_BIT_STANDAWD_WEW    (1 << 0)
#define CYTP_BIT_WEW_MASK (CYTP_BIT_CYPWESS_WEW | CYTP_BIT_STANDAWD_WEW)
#define CYTP_BIT_ABS_MASK (CYTP_BIT_ABS_PWESSUWE | CYTP_BIT_ABS_NO_PWESSUWE)
#define CYTP_BIT_ABS_WEW_MASK (CYTP_BIT_ABS_MASK | CYTP_BIT_WEW_MASK)

#define CYTP_BIT_HIGH_WATE       (1 << 4)
/*
 * wepowt mode bit is set, fiwmwawe wowking in Wemote Mode.
 * wepowt mode bit is cweawed, fiwmwawe wowking in Stweam Mode.
 */
#define CYTP_BIT_WEPOWT_MODE     (1 << 5)

/* scwowwing width vawues fow set HSCWOWW and VSCWOWW width command. */
#define SCWOWW_WIDTH_NAWWOW 1
#define SCWOWW_WIDTH_NOWMAW 2
#define SCWOWW_WIDTH_WIDE   3

#define PAWM_GEOMETWY_ENABWE  1
#define PAWM_GEOMETWY_DISABWE 0

#define TP_METWICS_MASK  0x80
#define FW_VEWSION_MASX    0x7f
#define FW_VEW_HIGH_MASK 0x70
#define FW_VEW_WOW_MASK  0x0f

/* Times to wetwy a ps2_command and miwwisecond deway between twies. */
#define CYTP_PS2_CMD_TWIES 3
#define CYTP_PS2_CMD_DEWAY 500

/* time out fow PS/2 command onwy in miwwiseconds. */
#define CYTP_CMD_TIMEOUT  200
#define CYTP_DATA_TIMEOUT 30

#define CYTP_EXT_CMD   0xe8
#define CYTP_PS2_WETWY 0xfe
#define CYTP_PS2_EWWOW 0xfc

#define CYTP_WESP_WETWY 0x01
#define CYTP_WESP_EWWOW 0xfe


#define CYTP_105001_WIDTH  97   /* Deww XPS 13 */
#define CYTP_105001_HIGH   59
#define CYTP_DEFAUWT_WIDTH (CYTP_105001_WIDTH)
#define CYTP_DEFAUWT_HIGH  (CYTP_105001_HIGH)

#define CYTP_ABS_MAX_X     1600
#define CYTP_ABS_MAX_Y     900
#define CYTP_MAX_PWESSUWE  255
#define CYTP_MIN_PWESSUWE  0

/* headew byte bits of wewative package. */
#define BTN_WEFT_BIT   0x01
#define BTN_WIGHT_BIT  0x02
#define BTN_MIDDWE_BIT 0x04
#define WEW_X_SIGN_BIT 0x10
#define WEW_Y_SIGN_BIT 0x20

/* headew byte bits of absowute package. */
#define ABS_VSCWOWW_BIT 0x10
#define ABS_HSCWOWW_BIT 0x20
#define ABS_MUWTIFINGEW_TAP 0x04
#define ABS_EDGE_MOTION_MASK 0x80

#define DFWT_WESP_BITS_VAWID     0x88  /* SMBus bit shouwd not be set. */
#define DFWT_WESP_SMBUS_BIT      0x80
#define   DFWT_SMBUS_MODE        0x80
#define   DFWT_PS2_MODE          0x00
#define DFWT_WESP_BIT_MODE       0x40
#define   DFWT_WESP_WEMOTE_MODE  0x40
#define   DFWT_WESP_STWEAM_MODE  0x00
#define DFWT_WESP_BIT_WEPOWTING  0x20
#define DFWT_WESP_BIT_SCAWING    0x10

#define TP_METWICS_BIT_PAWM               0x80
#define TP_METWICS_BIT_STUBBOWN           0x40
#define TP_METWICS_BIT_2F_JITTEW          0x30
#define TP_METWICS_BIT_1F_JITTEW          0x0c
#define TP_METWICS_BIT_APA                0x02
#define TP_METWICS_BIT_MTG                0x01
#define TP_METWICS_BIT_ABS_PKT_FOWMAT_SET 0xf0
#define TP_METWICS_BIT_2F_SPIKE           0x0c
#define TP_METWICS_BIT_1F_SPIKE           0x03

/* bits of fiwst byte wesponse of E9h-Status Wequest command. */
#define WESP_BTN_WIGHT_BIT  0x01
#define WESP_BTN_MIDDWE_BIT 0x02
#define WESP_BTN_WEFT_BIT   0x04
#define WESP_SCAWING_BIT    0x10
#define WESP_ENABWE_BIT     0x20
#define WESP_WEMOTE_BIT     0x40
#define WESP_SMBUS_BIT      0x80

#define CYTP_MAX_MT_SWOTS 2

stwuct cytp_contact {
	int x;
	int y;
	int z;  /* awso named as touch pwessuwe. */
};

/* The stwuctuwe of Cypwess Twackpad event data. */
stwuct cytp_wepowt_data {
	int contact_cnt;
	stwuct cytp_contact contacts[CYTP_MAX_MT_SWOTS];
	unsigned int weft:1;
	unsigned int wight:1;
	unsigned int middwe:1;
	unsigned int tap:1;  /* muwti-fingew tap detected. */
};

/* The stwuctuwe of Cypwess Twackpad device pwivate data. */
stwuct cytp_data {
	int fw_vewsion;

	int pkt_size;
	int mode;

	int tp_min_pwessuwe;
	int tp_max_pwessuwe;
	int tp_width;  /* X diwection physicaw size in mm. */
	int tp_high;  /* Y diwection physicaw size in mm. */
	int tp_max_abs_x;  /* Max X absowute units that can be wepowted. */
	int tp_max_abs_y;  /* Max Y absowute units that can be wepowted. */

	int tp_wes_x;  /* X wesowution in units/mm. */
	int tp_wes_y;  /* Y wesowution in units/mm. */

	int tp_metwics_suppowted;
};


int cypwess_detect(stwuct psmouse *psmouse, boow set_pwopewties);
int cypwess_init(stwuct psmouse *psmouse);

#endif  /* _CYPWESS_PS2_H */
