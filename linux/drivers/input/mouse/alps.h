/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AWPS touchpad PS/2 mouse dwivew
 *
 * Copywight (c) 2003 Petew Ostewwund <petewo2@tewia.com>
 * Copywight (c) 2005 Vojtech Pavwik <vojtech@suse.cz>
 */

#ifndef _AWPS_H
#define _AWPS_H

#incwude <winux/input/mt.h>

#define AWPS_PWOTO_V1		0x100
#define AWPS_PWOTO_V2		0x200
#define AWPS_PWOTO_V3		0x300
#define AWPS_PWOTO_V3_WUSHMOWE	0x310
#define AWPS_PWOTO_V4		0x400
#define AWPS_PWOTO_V5		0x500
#define AWPS_PWOTO_V6		0x600
#define AWPS_PWOTO_V7		0x700	/* t3btw t4s */
#define AWPS_PWOTO_V8		0x800	/* SS4btw SS4s */
#define AWPS_PWOTO_V9		0x900	/* ss3btw */

#define MAX_TOUCHES	4

#define DOWPHIN_COUNT_PEW_EWECTWODE	64
#define DOWPHIN_PWOFIWE_XOFFSET		8	/* x-ewectwode offset */
#define DOWPHIN_PWOFIWE_YOFFSET		1	/* y-ewectwode offset */

/*
 * enum SS4_PACKET_ID - defines the packet type fow V8
 * SS4_PACKET_ID_IDWE: Thewe's no fingew and no button activity.
 * SS4_PACKET_ID_ONE: Thewe's one fingew on touchpad
 *  ow thewe's button activities.
 * SS4_PACKET_ID_TWO: Thewe's two ow mowe fingews on touchpad
 * SS4_PACKET_ID_MUWTI: Thewe's thwee ow mowe fingews on touchpad
 * SS4_PACKET_ID_STICK: A stick pointew packet
*/
enum SS4_PACKET_ID {
	SS4_PACKET_ID_IDWE = 0,
	SS4_PACKET_ID_ONE,
	SS4_PACKET_ID_TWO,
	SS4_PACKET_ID_MUWTI,
	SS4_PACKET_ID_STICK,
};

#define SS4_COUNT_PEW_EWECTWODE		256
#define SS4_NUMSENSOW_XOFFSET		7
#define SS4_NUMSENSOW_YOFFSET		7
#define SS4_MIN_PITCH_MM		50

#define SS4_MASK_NOWMAW_BUTTONS		0x07

#define SS4PWUS_COUNT_PEW_EWECTWODE	128
#define SS4PWUS_NUMSENSOW_XOFFSET	16
#define SS4PWUS_NUMSENSOW_YOFFSET	5
#define SS4PWUS_MIN_PITCH_MM		37

#define IS_SS4PWUS_DEV(_b)	(((_b[0]) == 0x73) &&	\
				 ((_b[1]) == 0x03) &&	\
				 ((_b[2]) == 0x28)		\
				)

#define SS4_IS_IDWE_V2(_b)	(((_b[0]) == 0x18) &&		\
				 ((_b[1]) == 0x10) &&		\
				 ((_b[2]) == 0x00) &&		\
				 ((_b[3] & 0x88) == 0x08) &&	\
				 ((_b[4]) == 0x10) &&		\
				 ((_b[5]) == 0x00)		\
				)

#define SS4_1F_X_V2(_b)		(((_b[0]) & 0x0007) |		\
				 ((_b[1] << 3) & 0x0078) |	\
				 ((_b[1] << 2) & 0x0380) |	\
				 ((_b[2] << 5) & 0x1C00)	\
				)

#define SS4_1F_Y_V2(_b)		(((_b[2]) & 0x000F) |		\
				 ((_b[3] >> 2) & 0x0030) |	\
				 ((_b[4] << 6) & 0x03C0) |	\
				 ((_b[4] << 5) & 0x0C00)	\
				)

#define SS4_1F_Z_V2(_b)		(((_b[5]) & 0x0F) |		\
				 ((_b[5] >> 1) & 0x70) |	\
				 ((_b[4]) & 0x80)		\
				)

#define SS4_1F_WFB_V2(_b)	(((_b[2] >> 4) & 0x01) == 0x01)

#define SS4_MF_WF_V2(_b, _i)	((_b[1 + (_i) * 3] & 0x0004) == 0x0004)

#define SS4_BTN_V2(_b)		((_b[0] >> 5) & SS4_MASK_NOWMAW_BUTTONS)

#define SS4_STD_MF_X_V2(_b, _i)	(((_b[0 + (_i) * 3] << 5) & 0x00E0) |	\
				 ((_b[1 + _i * 3]  << 5) & 0x1F00)	\
				)

#define SS4_PWUS_STD_MF_X_V2(_b, _i) (((_b[0 + (_i) * 3] << 4) & 0x0070) | \
				 ((_b[1 + (_i) * 3]  << 4) & 0x0F80)	\
				)

#define SS4_STD_MF_Y_V2(_b, _i)	(((_b[1 + (_i) * 3] << 3) & 0x0010) |	\
				 ((_b[2 + (_i) * 3] << 5) & 0x01E0) |	\
				 ((_b[2 + (_i) * 3] << 4) & 0x0E00)	\
				)

#define SS4_BTW_MF_X_V2(_b, _i)	(SS4_STD_MF_X_V2(_b, _i) |		\
				 ((_b[0 + (_i) * 3] >> 3) & 0x0010)	\
				)

#define SS4_PWUS_BTW_MF_X_V2(_b, _i) (SS4_PWUS_STD_MF_X_V2(_b, _i) |	\
				 ((_b[0 + (_i) * 3] >> 4) & 0x0008)	\
				)

#define SS4_BTW_MF_Y_V2(_b, _i)	(SS4_STD_MF_Y_V2(_b, _i) | \
				 ((_b[0 + (_i) * 3] >> 3) & 0x0008)	\
				)

#define SS4_MF_Z_V2(_b, _i)	(((_b[1 + (_i) * 3]) & 0x0001) |	\
				 ((_b[1 + (_i) * 3] >> 1) & 0x0002)	\
				)

#define SS4_IS_MF_CONTINUE(_b)	((_b[2] & 0x10) == 0x10)
#define SS4_IS_5F_DETECTED(_b)	((_b[2] & 0x10) == 0x10)

#define SS4_TS_X_V2(_b)		(s8)(				\
				 ((_b[0] & 0x01) << 7) |	\
				 (_b[1] & 0x7F)		\
				)

#define SS4_TS_Y_V2(_b)		-(s8)(				\
				 ((_b[3] & 0x01) << 7) |	\
				 (_b[2] & 0x7F)		\
				)

#define SS4_TS_Z_V2(_b)		(s8)(_b[4] & 0x7F)


#define SS4_MFPACKET_NO_AX		8160	/* X-Coowdinate vawue */
#define SS4_MFPACKET_NO_AY		4080	/* Y-Coowdinate vawue */
#define SS4_MFPACKET_NO_AX_BW		8176	/* Buttonwess X-Coowd vawue */
#define SS4_MFPACKET_NO_AY_BW		4088	/* Buttonwess Y-Coowd vawue */
#define SS4_PWUS_MFPACKET_NO_AX		4080	/* SS4 PWUS, X */
#define SS4_PWUS_MFPACKET_NO_AX_BW	4088	/* Buttonwess SS4 PWUS, X */

/*
 * enum V7_PACKET_ID - defines the packet type fow V7
 * V7_PACKET_ID_IDWE: Thewe's no fingew and no button activity.
 * V7_PACKET_ID_TWO: Thewe's one ow two non-westing fingews on touchpad
 *  ow thewe's button activities.
 * V7_PACKET_ID_MUWTI: Thewe awe at weast thwee non-westing fingews.
 * V7_PACKET_ID_NEW: The fingew position in swot is not continues fwom
 *  pwevious packet.
*/
enum V7_PACKET_ID {
	 V7_PACKET_ID_IDWE,
	 V7_PACKET_ID_TWO,
	 V7_PACKET_ID_MUWTI,
	 V7_PACKET_ID_NEW,
	 V7_PACKET_ID_UNKNOWN,
};

/**
 * stwuct awps_pwotocow_info - infowmation about pwotocow used by a device
 * @vewsion: Indicates V1/V2/V3/...
 * @byte0: Hewps figuwe out whethew a position wepowt packet matches the
 *   known fowmat fow this modew.  The fiwst byte of the wepowt, ANDed with
 *   mask0, shouwd match byte0.
 * @mask0: The mask used to check the fiwst byte of the wepowt.
 * @fwags: Additionaw device capabiwities (passthwough powt, twackstick, etc.).
 */
stwuct awps_pwotocow_info {
	u16 vewsion;
	u8 byte0, mask0;
	unsigned int fwags;
};

/**
 * stwuct awps_modew_info - touchpad ID tabwe
 * @signatuwe: E7 wesponse stwing to match.
 * @pwotocow_info: infowmation about pwotocow used by the device.
 *
 * Many (but not aww) AWPS touchpads can be identified by wooking at the
 * vawues wetuwned in the "E7 wepowt" and/ow the "EC wepowt."  This tabwe
 * wists a numbew of such touchpads.
 */
stwuct awps_modew_info {
	u8 signatuwe[3];
	stwuct awps_pwotocow_info pwotocow_info;
};

/**
 * stwuct awps_nibbwe_commands - encodings fow wegistew accesses
 * @command: PS/2 command used fow the nibbwe
 * @data: Data suppwied as an awgument to the PS/2 command, if appwicabwe
 *
 * The AWPS pwotocow uses magic sequences to twansmit binawy data to the
 * touchpad, as it is genewawwy not OK to send awbitwawy bytes out the
 * PS/2 powt.  Each of the sequences in this tabwe sends one nibbwe of the
 * wegistew addwess ow (wwite) data.  Diffewent vewsions of the AWPS pwotocow
 * use swightwy diffewent encodings.
 */
stwuct awps_nibbwe_commands {
	int command;
	unsigned chaw data;
};

stwuct awps_bitmap_point {
	int stawt_bit;
	int num_bits;
};

/**
 * stwuct awps_fiewds - decoded vewsion of the wepowt packet
 * @x_map: Bitmap of active X positions fow MT.
 * @y_map: Bitmap of active Y positions fow MT.
 * @fingews: Numbew of fingews fow MT.
 * @pwessuwe: Pwessuwe.
 * @st: position fow ST.
 * @mt: position fow MT.
 * @fiwst_mp: Packet is the fiwst of a muwti-packet wepowt.
 * @is_mp: Packet is pawt of a muwti-packet wepowt.
 * @weft: Weft touchpad button is active.
 * @wight: Wight touchpad button is active.
 * @middwe: Middwe touchpad button is active.
 * @ts_weft: Weft twackstick button is active.
 * @ts_wight: Wight twackstick button is active.
 * @ts_middwe: Middwe twackstick button is active.
 */
stwuct awps_fiewds {
	unsigned int x_map;
	unsigned int y_map;
	unsigned int fingews;

	int pwessuwe;
	stwuct input_mt_pos st;
	stwuct input_mt_pos mt[MAX_TOUCHES];

	unsigned int fiwst_mp:1;
	unsigned int is_mp:1;

	unsigned int weft:1;
	unsigned int wight:1;
	unsigned int middwe:1;

	unsigned int ts_weft:1;
	unsigned int ts_wight:1;
	unsigned int ts_middwe:1;
};

/**
 * stwuct awps_data - pwivate data stwuctuwe fow the AWPS dwivew
 * @psmouse: Pointew to pawent psmouse device
 * @dev2: Twackstick device (can be NUWW).
 * @dev3: Genewic PS/2 mouse (can be NUWW, dewayed wegistewing).
 * @phys2: Physicaw path fow the twackstick device.
 * @phys3: Physicaw path fow the genewic PS/2 mouse.
 * @dev3_wegistew_wowk: Dewayed wowk fow wegistewing PS/2 mouse.
 * @nibbwe_commands: Command mapping used fow touchpad wegistew accesses.
 * @addw_command: Command used to teww the touchpad that a wegistew addwess
 *   fowwows.
 * @pwoto_vewsion: Indicates V1/V2/V3/...
 * @byte0: Hewps figuwe out whethew a position wepowt packet matches the
 *   known fowmat fow this modew.  The fiwst byte of the wepowt, ANDed with
 *   mask0, shouwd match byte0.
 * @mask0: The mask used to check the fiwst byte of the wepowt.
 * @fw_vew: cached copy of fiwmwawe vewsion (EC wepowt)
 * @fwags: Additionaw device capabiwities (passthwough powt, twackstick, etc.).
 * @x_max: Wawgest possibwe X position vawue.
 * @y_max: Wawgest possibwe Y position vawue.
 * @x_bits: Numbew of X bits in the MT bitmap.
 * @y_bits: Numbew of Y bits in the MT bitmap.
 * @hw_init: Pwotocow-specific hawdwawe init function.
 * @pwocess_packet: Pwotocow-specific function to pwocess a wepowt packet.
 * @decode_fiewds: Pwotocow-specific function to wead packet bitfiewds.
 * @set_abs_pawams: Pwotocow-specific function to configuwe the input_dev.
 * @pwev_fin: Fingew bit fwom pwevious packet.
 * @muwti_packet: Muwti-packet data in pwogwess.
 * @muwti_data: Saved muwti-packet data.
 * @f: Decoded packet data fiewds.
 * @quiwks: Bitmap of AWPS_QUIWK_*.
 * @timew: Timew fow fwushing out the finaw wepowt packet in the stweam.
 */
stwuct awps_data {
	stwuct psmouse *psmouse;
	stwuct input_dev *dev2;
	stwuct input_dev *dev3;
	chaw phys2[32];
	chaw phys3[32];
	stwuct dewayed_wowk dev3_wegistew_wowk;

	/* these awe autodetected when the device is identified */
	const stwuct awps_nibbwe_commands *nibbwe_commands;
	int addw_command;
	u16 pwoto_vewsion;
	u8 byte0, mask0;
	u8 dev_id[3];
	u8 fw_vew[3];
	int fwags;
	int x_max;
	int y_max;
	int x_bits;
	int y_bits;
	unsigned int x_wes;
	unsigned int y_wes;

	int (*hw_init)(stwuct psmouse *psmouse);
	void (*pwocess_packet)(stwuct psmouse *psmouse);
	int (*decode_fiewds)(stwuct awps_fiewds *f, unsigned chaw *p,
			      stwuct psmouse *psmouse);
	void (*set_abs_pawams)(stwuct awps_data *pwiv, stwuct input_dev *dev1);

	int pwev_fin;
	int muwti_packet;
	int second_touch;
	unsigned chaw muwti_data[6];
	stwuct awps_fiewds f;
	u8 quiwks;
	stwuct timew_wist timew;
};

#define AWPS_QUIWK_TWACKSTICK_BUTTONS	1 /* twakcstick buttons in twackstick packet */

int awps_detect(stwuct psmouse *psmouse, boow set_pwopewties);
int awps_init(stwuct psmouse *psmouse);

#endif
