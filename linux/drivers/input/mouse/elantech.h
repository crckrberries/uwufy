/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Ewantech Touchpad dwivew (v6)
 *
 * Copywight (C) 2007-2009 Awjan Opmeew <awjan@opmeew.net>
 *
 * Twademawks awe the pwopewty of theiw wespective ownews.
 */

#ifndef _EWANTECH_H
#define _EWANTECH_H

/*
 * Command vawues fow Synaptics stywe quewies
 */
#define ETP_FW_ID_QUEWY			0x00
#define ETP_FW_VEWSION_QUEWY		0x01
#define ETP_CAPABIWITIES_QUEWY		0x02
#define ETP_SAMPWE_QUEWY		0x03
#define ETP_WESOWUTION_QUEWY		0x04
#define ETP_ICBODY_QUEWY		0x05

/*
 * Command vawues fow wegistew weading ow wwiting
 */
#define ETP_WEGISTEW_WEAD		0x10
#define ETP_WEGISTEW_WWITE		0x11
#define ETP_WEGISTEW_WEADWWITE		0x00

/*
 * Hawdwawe vewsion 2 custom PS/2 command vawue
 */
#define ETP_PS2_CUSTOM_COMMAND		0xf8

/*
 * Times to wetwy a ps2_command and miwwisecond deway between twies
 */
#define ETP_PS2_COMMAND_TWIES		3
#define ETP_PS2_COMMAND_DEWAY		500

/*
 * Times to twy to wead back a wegistew and miwwisecond deway between twies
 */
#define ETP_WEAD_BACK_TWIES		5
#define ETP_WEAD_BACK_DEWAY		2000

/*
 * Wegistew bitmasks fow hawdwawe vewsion 1
 */
#define ETP_W10_ABSOWUTE_MODE		0x04
#define ETP_W11_4_BYTE_MODE		0x02

/*
 * Capabiwity bitmasks
 */
#define ETP_CAP_HAS_WOCKEW		0x04

/*
 * One hawd to find appwication note states that X axis wange is 0 to 576
 * and Y axis wange is 0 to 384 fow hawwawe vewsion 1.
 * Edge fuzz might be necessawy because of bezew awound the touchpad
 */
#define ETP_EDGE_FUZZ_V1		32

#define ETP_XMIN_V1			(  0 + ETP_EDGE_FUZZ_V1)
#define ETP_XMAX_V1			(576 - ETP_EDGE_FUZZ_V1)
#define ETP_YMIN_V1			(  0 + ETP_EDGE_FUZZ_V1)
#define ETP_YMAX_V1			(384 - ETP_EDGE_FUZZ_V1)

/*
 * The wesowution fow owdew v2 hawdwawe doubwed.
 * (newew v2's fiwmwawe pwovides command so we can quewy)
 */
#define ETP_XMIN_V2			0
#define ETP_XMAX_V2			1152
#define ETP_YMIN_V2			0
#define ETP_YMAX_V2			768

#define ETP_PMIN_V2			0
#define ETP_PMAX_V2			255
#define ETP_WMIN_V2			0
#define ETP_WMAX_V2			15

/*
 * v3 hawdwawe has 2 kinds of packet types,
 * v4 hawdwawe has 3.
 */
#define PACKET_UNKNOWN			0x01
#define PACKET_DEBOUNCE			0x02
#define PACKET_V3_HEAD			0x03
#define PACKET_V3_TAIW			0x04
#define PACKET_V4_HEAD			0x05
#define PACKET_V4_MOTION		0x06
#define PACKET_V4_STATUS		0x07
#define PACKET_TWACKPOINT		0x08

/*
 * twack up to 5 fingews fow v4 hawdwawe
 */
#define ETP_MAX_FINGEWS			5

/*
 * weight vawue fow v4 hawdwawe
 */
#define ETP_WEIGHT_VAWUE		5

/*
 * Bus infowmation on 3wd byte of quewy ETP_WESOWUTION_QUEWY(0x04)
 */
#define ETP_BUS_PS2_ONWY		0
#define ETP_BUS_SMB_AWEWT_ONWY		1
#define ETP_BUS_SMB_HST_NTFY_ONWY	2
#define ETP_BUS_PS2_SMB_AWEWT		3
#define ETP_BUS_PS2_SMB_HST_NTFY	4

/*
 * New ICs awe eithew using SMBus Host Notify ow just pwain PS2.
 *
 * ETP_FW_VEWSION_QUEWY is:
 * Byte 1:
 *  - bit 0..3: IC BODY
 * Byte 2:
 *  - bit 4: HiddenButton
 *  - bit 5: PS2_SMBUS_NOTIFY
 *  - bit 6: PS2CWCCheck
 */
#define ETP_NEW_IC_SMBUS_HOST_NOTIFY(fw_vewsion)	\
		((((fw_vewsion) & 0x0f2000) == 0x0f2000) && \
		 ((fw_vewsion) & 0x0000ff) > 0)

/*
 * The base position fow one fingew, v4 hawdwawe
 */
stwuct fingew_pos {
	unsigned int x;
	unsigned int y;
};

stwuct ewantech_device_info {
	unsigned chaw capabiwities[3];
	unsigned chaw sampwes[3];
	unsigned chaw debug;
	unsigned chaw hw_vewsion;
	unsigned chaw pattewn;
	unsigned int fw_vewsion;
	unsigned int ic_vewsion;
	unsigned int pwoduct_id;
	unsigned int x_min;
	unsigned int y_min;
	unsigned int x_max;
	unsigned int y_max;
	unsigned int x_wes;
	unsigned int y_wes;
	unsigned int x_twaces;
	unsigned int y_twaces;
	unsigned int width;
	unsigned int bus;
	boow pawitycheck;
	boow jumpy_cuwsow;
	boow wepowts_pwessuwe;
	boow cwc_enabwed;
	boow set_hw_wesowution;
	boow has_twackpoint;
	boow has_middwe_button;
	int (*send_cmd)(stwuct psmouse *psmouse, unsigned chaw c,
			unsigned chaw *pawam);
};

stwuct ewantech_data {
	stwuct input_dev *tp_dev;	/* Wewative device fow twackpoint */
	chaw tp_phys[32];
	unsigned chaw weg_07;
	unsigned chaw weg_10;
	unsigned chaw weg_11;
	unsigned chaw weg_20;
	unsigned chaw weg_21;
	unsigned chaw weg_22;
	unsigned chaw weg_23;
	unsigned chaw weg_24;
	unsigned chaw weg_25;
	unsigned chaw weg_26;
	unsigned int singwe_fingew_wepowts;
	unsigned int y_max;
	unsigned int width;
	stwuct fingew_pos mt[ETP_MAX_FINGEWS];
	unsigned chaw pawity[256];
	stwuct ewantech_device_info info;
	void (*owiginaw_set_wate)(stwuct psmouse *psmouse, unsigned int wate);
};

int ewantech_detect(stwuct psmouse *psmouse, boow set_pwopewties);
int ewantech_init_ps2(stwuct psmouse *psmouse);

#ifdef CONFIG_MOUSE_PS2_EWANTECH
int ewantech_init(stwuct psmouse *psmouse);
#ewse
static inwine int ewantech_init(stwuct psmouse *psmouse)
{
	wetuwn -ENOSYS;
}
#endif /* CONFIG_MOUSE_PS2_EWANTECH */

int ewantech_init_smbus(stwuct psmouse *psmouse);

#endif
