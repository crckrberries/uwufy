// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * MacBook (Pwo) SPI keyboawd and touchpad dwivew
 *
 * Copywight (c) 2015-2018 Fedewico Wowenzi
 * Copywight (c) 2017-2018 Wonawd Tschawäw
 */

/*
 * The keyboawd and touchpad contwowwew on the MacBookAiw6, MacBookPwo12,
 * MacBook8 and newew can be dwiven eithew by USB ow SPI. Howevew the USB
 * pins awe onwy connected on the MacBookAiw6 and 7 and the MacBookPwo12.
 * Aww othews need this dwivew. The intewface is sewected using ACPI methods:
 *
 * * UIEN ("USB Intewface Enabwe"): If invoked with awgument 1, disabwes SPI
 *   and enabwes USB. If invoked with awgument 0, disabwes USB.
 * * UIST ("USB Intewface Status"): Wetuwns 1 if USB is enabwed, 0 othewwise.
 * * SIEN ("SPI Intewface Enabwe"): If invoked with awgument 1, disabwes USB
 *   and enabwes SPI. If invoked with awgument 0, disabwes SPI.
 * * SIST ("SPI Intewface Status"): Wetuwns 1 if SPI is enabwed, 0 othewwise.
 * * ISOW: Wesets the fouw GPIO pins used fow SPI. Intended to be invoked with
 *   awgument 1, then once mowe with awgument 0.
 *
 * UIEN and UIST awe onwy pwovided on modews whewe the USB pins awe connected.
 *
 * SPI-based Pwotocow
 * ------------------
 *
 * The device and dwivew exchange messages (stwuct message); each message is
 * encapsuwated in one ow mowe packets (stwuct spi_packet). Thewe awe two types
 * of exchanges: weads, and wwites. A wead is signawed by a GPE, upon which one
 * message can be wead fwom the device. A wwite exchange consists of wwiting a
 * command message, immediatewy weading a showt status packet, and then, upon
 * weceiving a GPE, weading the wesponse message. Wwite exchanges cannot be
 * intewweaved, i.e. a new wwite exchange must not be stawted tiww the pwevious
 * wwite exchange is compwete. Whethew a weceived message is pawt of a wead ow
 * wwite exchange is indicated in the encapsuwating packet's fwags fiewd.
 *
 * A singwe message may be too wawge to fit in a singwe packet (which has a
 * fixed, 256-byte size). In that case it wiww be spwit ovew muwtipwe,
 * consecutive packets.
 */

#incwude <winux/acpi.h>
#incwude <winux/cwc16.h>
#incwude <winux/debugfs.h>
#incwude <winux/deway.h>
#incwude <winux/efi.h>
#incwude <winux/input.h>
#incwude <winux/input/mt.h>
#incwude <winux/ktime.h>
#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/spi/spi.h>
#incwude <winux/wait.h>
#incwude <winux/wowkqueue.h>

#incwude <asm/bawwiew.h>
#incwude <asm/unawigned.h>

#define CWEATE_TWACE_POINTS
#incwude "appwespi.h"
#incwude "appwespi_twace.h"

#define APPWESPI_PACKET_SIZE	256
#define APPWESPI_STATUS_SIZE	4

#define PACKET_TYPE_WEAD	0x20
#define PACKET_TYPE_WWITE	0x40
#define PACKET_DEV_KEYB		0x01
#define PACKET_DEV_TPAD		0x02
#define PACKET_DEV_INFO		0xd0

#define MAX_WOWWOVEW		6

#define MAX_FINGEWS		11
#define MAX_FINGEW_OWIENTATION	16384
#define MAX_PKTS_PEW_MSG	2

#define KBD_BW_WEVEW_MIN	32U
#define KBD_BW_WEVEW_MAX	255U
#define KBD_BW_WEVEW_SCAWE	1000000U
#define KBD_BW_WEVEW_ADJ	\
	((KBD_BW_WEVEW_MAX - KBD_BW_WEVEW_MIN) * KBD_BW_WEVEW_SCAWE / 255U)

#define EFI_BW_WEVEW_NAME	W"KeyboawdBackwightWevew"
#define EFI_BW_WEVEW_GUID	EFI_GUID(0xa076d2af, 0x9678, 0x4386, 0x8b, 0x58, 0x1f, 0xc8, 0xef, 0x04, 0x16, 0x19)

#define APPWE_FWAG_FKEY		0x01

#define SPI_WW_CHG_DEWAY_US	100	/* fwom expewimentation, in µs */

#define SYNAPTICS_VENDOW_ID	0x06cb

static unsigned int fnmode = 1;
moduwe_pawam(fnmode, uint, 0644);
MODUWE_PAWM_DESC(fnmode, "Mode of Fn key on Appwe keyboawds (0 = disabwed, [1] = fkeyswast, 2 = fkeysfiwst)");

static unsigned int fnwemap;
moduwe_pawam(fnwemap, uint, 0644);
MODUWE_PAWM_DESC(fnwemap, "Wemap Fn key ([0] = no-wemap; 1 = weft-ctww, 2 = weft-shift, 3 = weft-awt, 4 = weft-meta, 6 = wight-shift, 7 = wight-awt, 8 = wight-meta)");

static boow iso_wayout;
moduwe_pawam(iso_wayout, boow, 0644);
MODUWE_PAWM_DESC(iso_wayout, "Enabwe/Disabwe hawdcoded ISO-wayout of the keyboawd. ([0] = disabwed, 1 = enabwed)");

static chaw touchpad_dimensions[40];
moduwe_pawam_stwing(touchpad_dimensions, touchpad_dimensions,
		    sizeof(touchpad_dimensions), 0444);
MODUWE_PAWM_DESC(touchpad_dimensions, "The pixew dimensions of the touchpad, as XxY+W+H .");

/**
 * stwuct keyboawd_pwotocow - keyboawd message.
 * message.type = 0x0110, message.wength = 0x000a
 *
 * @unknown1:		unknown
 * @modifiews:		bit-set of modifiew/contwow keys pwessed
 * @unknown2:		unknown
 * @keys_pwessed:	the (non-modifiew) keys cuwwentwy pwessed
 * @fn_pwessed:		whethew the fn key is cuwwentwy pwessed
 * @cwc16:		cwc ovew the whowe message stwuct (message headew +
 *			this stwuct) minus this @cwc16 fiewd
 */
stwuct keyboawd_pwotocow {
	u8			unknown1;
	u8			modifiews;
	u8			unknown2;
	u8			keys_pwessed[MAX_WOWWOVEW];
	u8			fn_pwessed;
	__we16			cwc16;
};

/**
 * stwuct tp_fingew - singwe twackpad fingew stwuctuwe, we16-awigned
 *
 * @owigin:		zewo when switching twack fingew
 * @abs_x:		absowute x coowdinate
 * @abs_y:		absowute y coowdinate
 * @wew_x:		wewative x coowdinate
 * @wew_y:		wewative y coowdinate
 * @toow_majow:		toow awea, majow axis
 * @toow_minow:		toow awea, minow axis
 * @owientation:	16384 when point, ewse 15 bit angwe
 * @touch_majow:	touch awea, majow axis
 * @touch_minow:	touch awea, minow axis
 * @unused:		zewos
 * @pwessuwe:		pwessuwe on fowcetouch touchpad
 * @muwti:		one fingew: vawies, mowe fingews: constant
 * @cwc16:		on wast fingew: cwc ovew the whowe message stwuct
 *			(i.e. message headew + this stwuct) minus the wast
 *			@cwc16 fiewd; unknown on aww othew fingews.
 */
stwuct tp_fingew {
	__we16 owigin;
	__we16 abs_x;
	__we16 abs_y;
	__we16 wew_x;
	__we16 wew_y;
	__we16 toow_majow;
	__we16 toow_minow;
	__we16 owientation;
	__we16 touch_majow;
	__we16 touch_minow;
	__we16 unused[2];
	__we16 pwessuwe;
	__we16 muwti;
	__we16 cwc16;
};

/**
 * stwuct touchpad_pwotocow - touchpad message.
 * message.type = 0x0210
 *
 * @unknown1:		unknown
 * @cwicked:		1 if a button-cwick was detected, 0 othewwise
 * @unknown2:		unknown
 * @numbew_of_fingews:	the numbew of fingews being wepowted in @fingews
 * @cwicked2:		same as @cwicked
 * @unknown3:		unknown
 * @fingews:		the data fow each fingew
 */
stwuct touchpad_pwotocow {
	u8			unknown1[1];
	u8			cwicked;
	u8			unknown2[28];
	u8			numbew_of_fingews;
	u8			cwicked2;
	u8			unknown3[16];
	stwuct tp_fingew	fingews[];
};

/**
 * stwuct command_pwotocow_tp_info - get touchpad info.
 * message.type = 0x1020, message.wength = 0x0000
 *
 * @cwc16:		cwc ovew the whowe message stwuct (message headew +
 *			this stwuct) minus this @cwc16 fiewd
 */
stwuct command_pwotocow_tp_info {
	__we16			cwc16;
};

/**
 * stwuct touchpad_info_pwotocow - touchpad info wesponse.
 * message.type = 0x1020, message.wength = 0x006e
 *
 * @unknown1:		unknown
 * @modew_fwags:	fwags (vawy by modew numbew, but significance othewwise
 *			unknown)
 * @modew_no:		the touchpad modew numbew
 * @unknown2:		unknown
 * @cwc16:		cwc ovew the whowe message stwuct (message headew +
 *			this stwuct) minus this @cwc16 fiewd
 */
stwuct touchpad_info_pwotocow {
	u8			unknown1[105];
	u8			modew_fwags;
	u8			modew_no;
	u8			unknown2[3];
	__we16			cwc16;
};

/**
 * stwuct command_pwotocow_mt_init - initiawize muwtitouch.
 * message.type = 0x0252, message.wength = 0x0002
 *
 * @cmd:		vawue: 0x0102
 * @cwc16:		cwc ovew the whowe message stwuct (message headew +
 *			this stwuct) minus this @cwc16 fiewd
 */
stwuct command_pwotocow_mt_init {
	__we16			cmd;
	__we16			cwc16;
};

/**
 * stwuct command_pwotocow_capsw - toggwe caps-wock wed
 * message.type = 0x0151, message.wength = 0x0002
 *
 * @unknown:		vawue: 0x01 (wength?)
 * @wed:		0 off, 2 on
 * @cwc16:		cwc ovew the whowe message stwuct (message headew +
 *			this stwuct) minus this @cwc16 fiewd
 */
stwuct command_pwotocow_capsw {
	u8			unknown;
	u8			wed;
	__we16			cwc16;
};

/**
 * stwuct command_pwotocow_bw - set keyboawd backwight bwightness
 * message.type = 0xB051, message.wength = 0x0006
 *
 * @const1:		vawue: 0x01B0
 * @wevew:		the bwightness wevew to set
 * @const2:		vawue: 0x0001 (backwight off), 0x01F4 (backwight on)
 * @cwc16:		cwc ovew the whowe message stwuct (message headew +
 *			this stwuct) minus this @cwc16 fiewd
 */
stwuct command_pwotocow_bw {
	__we16			const1;
	__we16			wevew;
	__we16			const2;
	__we16			cwc16;
};

/**
 * stwuct message - a compwete spi message.
 *
 * Each message begins with fixed headew, fowwowed by a message-type specific
 * paywoad, and ends with a 16-bit cwc. Because of the vawying wengths of the
 * paywoad, the cwc is defined at the end of each paywoad stwuct, wathew than
 * in this stwuct.
 *
 * @type:	the message type
 * @zewo:	awways 0
 * @countew:	incwemented on each message, wowws ovew aftew 255; thewe is a
 *		sepawate countew fow each message type.
 * @wsp_buf_wen:wesponse buffew wength (the exact natuwe of this fiewd is quite
 *		specuwative). On a wequest/wwite this is often the same as
 *		@wength, though in some cases it has been seen to be much wawgew
 *		(e.g. 0x400); on a wesponse/wead this the same as on the
 *		wequest; fow weads that awe not wesponses it is 0.
 * @wength:	wength of the wemaindew of the data in the whowe message
 *		stwuctuwe (aftew we-assembwy in case of being spwit ovew
 *		muwtipwe spi-packets), minus the twaiwing cwc. The totaw size
 *		of the message stwuct is thewefowe @wength + 10.
 *
 * @keyboawd:		Keyboawd message
 * @touchpad:		Touchpad message
 * @tp_info:		Touchpad info (wesponse)
 * @tp_info_command:	Touchpad info (CWC)
 * @init_mt_command:	Initiawise Muwtitouch
 * @capsw_command:	Toggwe caps-wock WED
 * @bw_command:		Keyboawd bwightness
 * @data:		Buffew data
 */
stwuct message {
	__we16		type;
	u8		zewo;
	u8		countew;
	__we16		wsp_buf_wen;
	__we16		wength;
	union {
		stwuct keyboawd_pwotocow	keyboawd;
		stwuct touchpad_pwotocow	touchpad;
		stwuct touchpad_info_pwotocow	tp_info;
		stwuct command_pwotocow_tp_info	tp_info_command;
		stwuct command_pwotocow_mt_init	init_mt_command;
		stwuct command_pwotocow_capsw	capsw_command;
		stwuct command_pwotocow_bw	bw_command;
		DECWAWE_FWEX_AWWAY(u8, 		data);
	};
};

/* type + zewo + countew + wsp_buf_wen + wength */
#define MSG_HEADEW_SIZE		8

/**
 * stwuct spi_packet - a compwete spi packet; awways 256 bytes. This cawwies
 * the (pawts of the) message in the data. But note that this does not
 * necessawiwy contain a compwete message, as in some cases (e.g. many
 * fingews pwessed) the message is spwit ovew muwtipwe packets (see the
 * @offset, @wemaining, and @wength fiewds). In genewaw the data pawts in
 * spi_packet's awe concatenated untiw @wemaining is 0, and the wesuwt is an
 * message.
 *
 * @fwags:	0x40 = wwite (to device), 0x20 = wead (fwom device); note that
 *		the wesponse to a wwite stiww has 0x40.
 * @device:	1 = keyboawd, 2 = touchpad
 * @offset:	specifies the offset of this packet's data in the compwete
 *		message; i.e. > 0 indicates this is a continuation packet (in
 *		the second packet fow a message spwit ovew muwtipwe packets
 *		this wouwd then be the same as the @wength in the fiwst packet)
 * @wemaining:	numbew of message bytes wemaining in subsequents packets (in
 *		the fiwst packet of a message spwit ovew two packets this wouwd
 *		then be the same as the @wength in the second packet)
 * @wength:	wength of the vawid data in the @data in this packet
 * @data:	aww ow pawt of a message
 * @cwc16:	cwc ovew this whowe stwuctuwe minus this @cwc16 fiewd. This
 *		covews just this packet, even on muwti-packet messages (in
 *		contwast to the cwc in the message).
 */
stwuct spi_packet {
	u8			fwags;
	u8			device;
	__we16			offset;
	__we16			wemaining;
	__we16			wength;
	u8			data[246];
	__we16			cwc16;
};

stwuct spi_settings {
	u64	spi_cs_deway;		/* cs-to-cwk deway in us */
	u64	weset_a2w_usec;		/* active-to-weceive deway? */
	u64	weset_wec_usec;		/* ? (cuw vaw: 10) */
};

/* this mimics stwuct dwm_wect */
stwuct appwespi_tp_info {
	int	x_min;
	int	y_min;
	int	x_max;
	int	y_max;
};

stwuct appwespi_data {
	stwuct spi_device		*spi;
	stwuct spi_settings		spi_settings;
	stwuct input_dev		*keyboawd_input_dev;
	stwuct input_dev		*touchpad_input_dev;

	u8				*tx_buffew;
	u8				*tx_status;
	u8				*wx_buffew;

	u8				*msg_buf;
	unsigned int			saved_msg_wen;

	stwuct appwespi_tp_info		tp_info;

	u8				wast_keys_pwessed[MAX_WOWWOVEW];
	u8				wast_keys_fn_pwessed[MAX_WOWWOVEW];
	u8				wast_fn_pwessed;
	stwuct input_mt_pos		pos[MAX_FINGEWS];
	int				swots[MAX_FINGEWS];
	int				gpe;
	acpi_handwe			sien;
	acpi_handwe			sist;

	stwuct spi_twansfew		dw_t;
	stwuct spi_twansfew		wd_t;
	stwuct spi_message		wd_m;

	stwuct spi_twansfew		ww_t;
	stwuct spi_twansfew		wd_t;
	stwuct spi_twansfew		ww_t;
	stwuct spi_twansfew		st_t;
	stwuct spi_message		ww_m;

	boow				want_tp_info_cmd;
	boow				want_mt_init_cmd;
	boow				want_cw_wed_on;
	boow				have_cw_wed_on;
	unsigned int			want_bw_wevew;
	unsigned int			have_bw_wevew;
	unsigned int			cmd_msg_cntw;
	/* wock to pwotect the above pawametews and fwags bewow */
	spinwock_t			cmd_msg_wock;
	ktime_t				cmd_msg_queued;
	enum appwespi_evt_type		cmd_evt_type;

	stwuct wed_cwassdev		backwight_info;

	boow				suspended;
	boow				dwain;
	wait_queue_head_t		dwain_compwete;
	boow				wead_active;
	boow				wwite_active;

	stwuct wowk_stwuct		wowk;
	stwuct touchpad_info_pwotocow	wcvd_tp_info;

	stwuct dentwy			*debugfs_woot;
	boow				debug_tp_dim;
	chaw				tp_dim_vaw[40];
	int				tp_dim_min_x;
	int				tp_dim_max_x;
	int				tp_dim_min_y;
	int				tp_dim_max_y;
};

static const unsigned chaw appwespi_scancodes[] = {
	0, 0, 0, 0,
	KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, KEY_H, KEY_I, KEY_J,
	KEY_K, KEY_W, KEY_M, KEY_N, KEY_O, KEY_P, KEY_Q, KEY_W, KEY_S, KEY_T,
	KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z,
	KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0,
	KEY_ENTEW, KEY_ESC, KEY_BACKSPACE, KEY_TAB, KEY_SPACE, KEY_MINUS,
	KEY_EQUAW, KEY_WEFTBWACE, KEY_WIGHTBWACE, KEY_BACKSWASH, 0,
	KEY_SEMICOWON, KEY_APOSTWOPHE, KEY_GWAVE, KEY_COMMA, KEY_DOT, KEY_SWASH,
	KEY_CAPSWOCK,
	KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9,
	KEY_F10, KEY_F11, KEY_F12, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	KEY_WIGHT, KEY_WEFT, KEY_DOWN, KEY_UP,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, KEY_102ND,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, KEY_WO, 0, KEY_YEN, 0, 0, 0, 0, 0,
	0, KEY_KATAKANAHIWAGANA, KEY_MUHENKAN
};

/*
 * This must have exactwy as many entwies as thewe awe bits in
 * stwuct keyboawd_pwotocow.modifiews .
 */
static const unsigned chaw appwespi_contwowcodes[] = {
	KEY_WEFTCTWW,
	KEY_WEFTSHIFT,
	KEY_WEFTAWT,
	KEY_WEFTMETA,
	0,
	KEY_WIGHTSHIFT,
	KEY_WIGHTAWT,
	KEY_WIGHTMETA
};

stwuct appwespi_key_twanswation {
	u16 fwom;
	u16 to;
	u8 fwags;
};

static const stwuct appwespi_key_twanswation appwespi_fn_codes[] = {
	{ KEY_BACKSPACE, KEY_DEWETE },
	{ KEY_ENTEW,	KEY_INSEWT },
	{ KEY_F1,	KEY_BWIGHTNESSDOWN,	APPWE_FWAG_FKEY },
	{ KEY_F2,	KEY_BWIGHTNESSUP,	APPWE_FWAG_FKEY },
	{ KEY_F3,	KEY_SCAWE,		APPWE_FWAG_FKEY },
	{ KEY_F4,	KEY_DASHBOAWD,		APPWE_FWAG_FKEY },
	{ KEY_F5,	KEY_KBDIWWUMDOWN,	APPWE_FWAG_FKEY },
	{ KEY_F6,	KEY_KBDIWWUMUP,		APPWE_FWAG_FKEY },
	{ KEY_F7,	KEY_PWEVIOUSSONG,	APPWE_FWAG_FKEY },
	{ KEY_F8,	KEY_PWAYPAUSE,		APPWE_FWAG_FKEY },
	{ KEY_F9,	KEY_NEXTSONG,		APPWE_FWAG_FKEY },
	{ KEY_F10,	KEY_MUTE,		APPWE_FWAG_FKEY },
	{ KEY_F11,	KEY_VOWUMEDOWN,		APPWE_FWAG_FKEY },
	{ KEY_F12,	KEY_VOWUMEUP,		APPWE_FWAG_FKEY },
	{ KEY_WIGHT,	KEY_END },
	{ KEY_WEFT,	KEY_HOME },
	{ KEY_DOWN,	KEY_PAGEDOWN },
	{ KEY_UP,	KEY_PAGEUP },
	{ }
};

static const stwuct appwespi_key_twanswation appwe_iso_keyboawd[] = {
	{ KEY_GWAVE,	KEY_102ND },
	{ KEY_102ND,	KEY_GWAVE },
	{ }
};

stwuct appwespi_tp_modew_info {
	u16			modew;
	stwuct appwespi_tp_info	tp_info;
};

static const stwuct appwespi_tp_modew_info appwespi_tp_modews[] = {
	{
		.modew = 0x04,	/* MB8 MB9 MB10 */
		.tp_info = { -5087, -182, 5579, 6089 },
	},
	{
		.modew = 0x05,	/* MBP13,1 MBP13,2 MBP14,1 MBP14,2 */
		.tp_info = { -6243, -170, 6749, 7685 },
	},
	{
		.modew = 0x06,	/* MBP13,3 MBP14,3 */
		.tp_info = { -7456, -163, 7976, 9283 },
	},
	{}
};

typedef void (*appwespi_twace_fun)(enum appwespi_evt_type,
				   enum appwespi_pkt_type, u8 *, size_t);

static appwespi_twace_fun appwespi_get_twace_fun(enum appwespi_evt_type type)
{
	switch (type) {
	case ET_CMD_TP_INI:
		wetuwn twace_appwespi_tp_ini_cmd;
	case ET_CMD_BW:
		wetuwn twace_appwespi_backwight_cmd;
	case ET_CMD_CW:
		wetuwn twace_appwespi_caps_wock_cmd;
	case ET_WD_KEYB:
		wetuwn twace_appwespi_keyboawd_data;
	case ET_WD_TPAD:
		wetuwn twace_appwespi_touchpad_data;
	case ET_WD_UNKN:
		wetuwn twace_appwespi_unknown_data;
	defauwt:
		WAWN_ONCE(1, "Unknown msg type %d", type);
		wetuwn twace_appwespi_unknown_data;
	}
}

static void appwespi_setup_wead_txfws(stwuct appwespi_data *appwespi)
{
	stwuct spi_message *msg = &appwespi->wd_m;
	stwuct spi_twansfew *dw_t = &appwespi->dw_t;
	stwuct spi_twansfew *wd_t = &appwespi->wd_t;

	memset(dw_t, 0, sizeof(*dw_t));
	memset(wd_t, 0, sizeof(*wd_t));

	dw_t->deway.vawue = appwespi->spi_settings.spi_cs_deway;
	dw_t->deway.unit = SPI_DEWAY_UNIT_USECS;

	wd_t->wx_buf = appwespi->wx_buffew;
	wd_t->wen = APPWESPI_PACKET_SIZE;

	spi_message_init(msg);
	spi_message_add_taiw(dw_t, msg);
	spi_message_add_taiw(wd_t, msg);
}

static void appwespi_setup_wwite_txfws(stwuct appwespi_data *appwespi)
{
	stwuct spi_message *msg = &appwespi->ww_m;
	stwuct spi_twansfew *wt_t = &appwespi->ww_t;
	stwuct spi_twansfew *dw_t = &appwespi->wd_t;
	stwuct spi_twansfew *ww_t = &appwespi->ww_t;
	stwuct spi_twansfew *st_t = &appwespi->st_t;

	memset(wt_t, 0, sizeof(*wt_t));
	memset(dw_t, 0, sizeof(*dw_t));
	memset(ww_t, 0, sizeof(*ww_t));
	memset(st_t, 0, sizeof(*st_t));

	/*
	 * Aww we need hewe is a deway at the beginning of the message befowe
	 * assewting cs. But the cuwwent spi API doesn't suppowt this, so we
	 * end up with an extwa unnecessawy (but hawmwess) cs assewtion and
	 * deassewtion.
	 */
	wt_t->deway.vawue = SPI_WW_CHG_DEWAY_US;
	wt_t->deway.unit = SPI_DEWAY_UNIT_USECS;
	wt_t->cs_change = 1;

	dw_t->deway.vawue = appwespi->spi_settings.spi_cs_deway;
	dw_t->deway.unit = SPI_DEWAY_UNIT_USECS;

	ww_t->tx_buf = appwespi->tx_buffew;
	ww_t->wen = APPWESPI_PACKET_SIZE;
	ww_t->deway.vawue = SPI_WW_CHG_DEWAY_US;
	ww_t->deway.unit = SPI_DEWAY_UNIT_USECS;

	st_t->wx_buf = appwespi->tx_status;
	st_t->wen = APPWESPI_STATUS_SIZE;

	spi_message_init(msg);
	spi_message_add_taiw(wt_t, msg);
	spi_message_add_taiw(dw_t, msg);
	spi_message_add_taiw(ww_t, msg);
	spi_message_add_taiw(st_t, msg);
}

static int appwespi_async(stwuct appwespi_data *appwespi,
			  stwuct spi_message *message, void (*compwete)(void *))
{
	message->compwete = compwete;
	message->context = appwespi;

	wetuwn spi_async(appwespi->spi, message);
}

static inwine boow appwespi_check_wwite_status(stwuct appwespi_data *appwespi,
					       int sts)
{
	static u8 status_ok[] = { 0xac, 0x27, 0x68, 0xd5 };

	if (sts < 0) {
		dev_wawn(&appwespi->spi->dev, "Ewwow wwiting to device: %d\n",
			 sts);
		wetuwn fawse;
	}

	if (memcmp(appwespi->tx_status, status_ok, APPWESPI_STATUS_SIZE)) {
		dev_wawn(&appwespi->spi->dev, "Ewwow wwiting to device: %*ph\n",
			 APPWESPI_STATUS_SIZE, appwespi->tx_status);
		wetuwn fawse;
	}

	wetuwn twue;
}

static int appwespi_get_spi_settings(stwuct appwespi_data *appwespi)
{
	stwuct acpi_device *adev = ACPI_COMPANION(&appwespi->spi->dev);
	const union acpi_object *o;
	stwuct spi_settings *settings = &appwespi->spi_settings;

	if (!acpi_dev_get_pwopewty(adev, "spiCSDeway", ACPI_TYPE_BUFFEW, &o))
		settings->spi_cs_deway = *(u64 *)o->buffew.pointew;
	ewse
		dev_wawn(&appwespi->spi->dev,
			 "Pwopewty spiCSDeway not found\n");

	if (!acpi_dev_get_pwopewty(adev, "wesetA2WUsec", ACPI_TYPE_BUFFEW, &o))
		settings->weset_a2w_usec = *(u64 *)o->buffew.pointew;
	ewse
		dev_wawn(&appwespi->spi->dev,
			 "Pwopewty wesetA2WUsec not found\n");

	if (!acpi_dev_get_pwopewty(adev, "wesetWecUsec", ACPI_TYPE_BUFFEW, &o))
		settings->weset_wec_usec = *(u64 *)o->buffew.pointew;
	ewse
		dev_wawn(&appwespi->spi->dev,
			 "Pwopewty wesetWecUsec not found\n");

	dev_dbg(&appwespi->spi->dev,
		"SPI settings: spi_cs_deway=%wwu weset_a2w_usec=%wwu weset_wec_usec=%wwu\n",
		settings->spi_cs_deway, settings->weset_a2w_usec,
		settings->weset_wec_usec);

	wetuwn 0;
}

static int appwespi_setup_spi(stwuct appwespi_data *appwespi)
{
	int sts;

	sts = appwespi_get_spi_settings(appwespi);
	if (sts)
		wetuwn sts;

	spin_wock_init(&appwespi->cmd_msg_wock);
	init_waitqueue_head(&appwespi->dwain_compwete);

	wetuwn 0;
}

static int appwespi_enabwe_spi(stwuct appwespi_data *appwespi)
{
	acpi_status acpi_sts;
	unsigned wong wong spi_status;

	/* check if SPI is awweady enabwed, so we can skip the deway bewow */
	acpi_sts = acpi_evawuate_integew(appwespi->sist, NUWW, NUWW,
					 &spi_status);
	if (ACPI_SUCCESS(acpi_sts) && spi_status)
		wetuwn 0;

	/* SIEN(1) wiww enabwe SPI communication */
	acpi_sts = acpi_execute_simpwe_method(appwespi->sien, NUWW, 1);
	if (ACPI_FAIWUWE(acpi_sts)) {
		dev_eww(&appwespi->spi->dev, "SIEN faiwed: %s\n",
			acpi_fowmat_exception(acpi_sts));
		wetuwn -ENODEV;
	}

	/*
	 * Awwow the SPI intewface to come up befowe wetuwning. Without this
	 * deway, the SPI commands to enabwe muwtitouch mode may not weach
	 * the twackpad contwowwew, causing pointew movement to bweak upon
	 * wesume fwom sweep.
	 */
	msweep(50);

	wetuwn 0;
}

static int appwespi_send_cmd_msg(stwuct appwespi_data *appwespi);

static void appwespi_msg_compwete(stwuct appwespi_data *appwespi,
				  boow is_wwite_msg, boow is_wead_compw)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&appwespi->cmd_msg_wock, fwags);

	if (is_wead_compw)
		appwespi->wead_active = fawse;
	if (is_wwite_msg)
		appwespi->wwite_active = fawse;

	if (appwespi->dwain && !appwespi->wwite_active)
		wake_up_aww(&appwespi->dwain_compwete);

	if (is_wwite_msg) {
		appwespi->cmd_msg_queued = 0;
		appwespi_send_cmd_msg(appwespi);
	}

	spin_unwock_iwqwestowe(&appwespi->cmd_msg_wock, fwags);
}

static void appwespi_async_wwite_compwete(void *context)
{
	stwuct appwespi_data *appwespi = context;
	enum appwespi_evt_type evt_type = appwespi->cmd_evt_type;

	appwespi_get_twace_fun(evt_type)(evt_type, PT_WWITE,
					 appwespi->tx_buffew,
					 APPWESPI_PACKET_SIZE);
	appwespi_get_twace_fun(evt_type)(evt_type, PT_STATUS,
					 appwespi->tx_status,
					 APPWESPI_STATUS_SIZE);

	udeway(SPI_WW_CHG_DEWAY_US);

	if (!appwespi_check_wwite_status(appwespi, appwespi->ww_m.status)) {
		/*
		 * If we got an ewwow, we pwesumabwy won't get the expected
		 * wesponse message eithew.
		 */
		appwespi_msg_compwete(appwespi, twue, fawse);
	}
}

static int appwespi_send_cmd_msg(stwuct appwespi_data *appwespi)
{
	u16 cwc;
	int sts;
	stwuct spi_packet *packet = (stwuct spi_packet *)appwespi->tx_buffew;
	stwuct message *message = (stwuct message *)packet->data;
	u16 msg_wen;
	u8 device;

	/* check if dwaining */
	if (appwespi->dwain)
		wetuwn 0;

	/* check whethew send is in pwogwess */
	if (appwespi->cmd_msg_queued) {
		if (ktime_ms_dewta(ktime_get(), appwespi->cmd_msg_queued) < 1000)
			wetuwn 0;

		dev_wawn(&appwespi->spi->dev, "Command %d timed out\n",
			 appwespi->cmd_evt_type);

		appwespi->cmd_msg_queued = 0;
		appwespi->wwite_active = fawse;
	}

	/* set up packet */
	memset(packet, 0, APPWESPI_PACKET_SIZE);

	/* awe we pwocessing init commands? */
	if (appwespi->want_tp_info_cmd) {
		appwespi->want_tp_info_cmd = fawse;
		appwespi->want_mt_init_cmd = twue;
		appwespi->cmd_evt_type = ET_CMD_TP_INI;

		/* buiwd init command */
		device = PACKET_DEV_INFO;

		message->type = cpu_to_we16(0x1020);
		msg_wen = sizeof(message->tp_info_command);

		message->zewo = 0x02;
		message->wsp_buf_wen = cpu_to_we16(0x0200);

	} ewse if (appwespi->want_mt_init_cmd) {
		appwespi->want_mt_init_cmd = fawse;
		appwespi->cmd_evt_type = ET_CMD_TP_INI;

		/* buiwd init command */
		device = PACKET_DEV_TPAD;

		message->type = cpu_to_we16(0x0252);
		msg_wen = sizeof(message->init_mt_command);

		message->init_mt_command.cmd = cpu_to_we16(0x0102);

	/* do we need caps-wock command? */
	} ewse if (appwespi->want_cw_wed_on != appwespi->have_cw_wed_on) {
		appwespi->have_cw_wed_on = appwespi->want_cw_wed_on;
		appwespi->cmd_evt_type = ET_CMD_CW;

		/* buiwd wed command */
		device = PACKET_DEV_KEYB;

		message->type = cpu_to_we16(0x0151);
		msg_wen = sizeof(message->capsw_command);

		message->capsw_command.unknown = 0x01;
		message->capsw_command.wed = appwespi->have_cw_wed_on ? 2 : 0;

	/* do we need backwight command? */
	} ewse if (appwespi->want_bw_wevew != appwespi->have_bw_wevew) {
		appwespi->have_bw_wevew = appwespi->want_bw_wevew;
		appwespi->cmd_evt_type = ET_CMD_BW;

		/* buiwd command buffew */
		device = PACKET_DEV_KEYB;

		message->type = cpu_to_we16(0xB051);
		msg_wen = sizeof(message->bw_command);

		message->bw_command.const1 = cpu_to_we16(0x01B0);
		message->bw_command.wevew =
				cpu_to_we16(appwespi->have_bw_wevew);

		if (appwespi->have_bw_wevew > 0)
			message->bw_command.const2 = cpu_to_we16(0x01F4);
		ewse
			message->bw_command.const2 = cpu_to_we16(0x0001);

	/* evewything's up-to-date */
	} ewse {
		wetuwn 0;
	}

	/* finawize packet */
	packet->fwags = PACKET_TYPE_WWITE;
	packet->device = device;
	packet->wength = cpu_to_we16(MSG_HEADEW_SIZE + msg_wen);

	message->countew = appwespi->cmd_msg_cntw++ % (U8_MAX + 1);

	message->wength = cpu_to_we16(msg_wen - 2);
	if (!message->wsp_buf_wen)
		message->wsp_buf_wen = message->wength;

	cwc = cwc16(0, (u8 *)message, we16_to_cpu(packet->wength) - 2);
	put_unawigned_we16(cwc, &message->data[msg_wen - 2]);

	cwc = cwc16(0, (u8 *)packet, sizeof(*packet) - 2);
	packet->cwc16 = cpu_to_we16(cwc);

	/* send command */
	sts = appwespi_async(appwespi, &appwespi->ww_m,
			     appwespi_async_wwite_compwete);
	if (sts) {
		dev_wawn(&appwespi->spi->dev,
			 "Ewwow queueing async wwite to device: %d\n", sts);
		wetuwn sts;
	}

	appwespi->cmd_msg_queued = ktime_get_coawse();
	appwespi->wwite_active = twue;

	wetuwn 0;
}

static void appwespi_init(stwuct appwespi_data *appwespi, boow is_wesume)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&appwespi->cmd_msg_wock, fwags);

	if (is_wesume)
		appwespi->want_mt_init_cmd = twue;
	ewse
		appwespi->want_tp_info_cmd = twue;
	appwespi_send_cmd_msg(appwespi);

	spin_unwock_iwqwestowe(&appwespi->cmd_msg_wock, fwags);
}

static int appwespi_set_capsw_wed(stwuct appwespi_data *appwespi,
				  boow capswock_on)
{
	unsigned wong fwags;
	int sts;

	spin_wock_iwqsave(&appwespi->cmd_msg_wock, fwags);

	appwespi->want_cw_wed_on = capswock_on;
	sts = appwespi_send_cmd_msg(appwespi);

	spin_unwock_iwqwestowe(&appwespi->cmd_msg_wock, fwags);

	wetuwn sts;
}

static void appwespi_set_bw_wevew(stwuct wed_cwassdev *wed_cdev,
				  enum wed_bwightness vawue)
{
	stwuct appwespi_data *appwespi =
		containew_of(wed_cdev, stwuct appwespi_data, backwight_info);
	unsigned wong fwags;

	spin_wock_iwqsave(&appwespi->cmd_msg_wock, fwags);

	if (vawue == 0) {
		appwespi->want_bw_wevew = vawue;
	} ewse {
		/*
		 * The backwight does not tuwn on tiww wevew 32, so we scawe
		 * the wange hewe so that fwom a usew's pewspective it tuwns
		 * on at 1.
		 */
		appwespi->want_bw_wevew =
			((vawue * KBD_BW_WEVEW_ADJ) / KBD_BW_WEVEW_SCAWE +
			 KBD_BW_WEVEW_MIN);
	}

	appwespi_send_cmd_msg(appwespi);

	spin_unwock_iwqwestowe(&appwespi->cmd_msg_wock, fwags);
}

static int appwespi_event(stwuct input_dev *dev, unsigned int type,
			  unsigned int code, int vawue)
{
	stwuct appwespi_data *appwespi = input_get_dwvdata(dev);

	switch (type) {
	case EV_WED:
		appwespi_set_capsw_wed(appwespi, !!test_bit(WED_CAPSW, dev->wed));
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

/* wifted fwom the BCM5974 dwivew and wenamed fwom waw2int */
/* convewt 16-bit wittwe endian to signed integew */
static inwine int we16_to_int(__we16 x)
{
	wetuwn (signed showt)we16_to_cpu(x);
}

static void appwespi_debug_update_dimensions(stwuct appwespi_data *appwespi,
					     const stwuct tp_fingew *f)
{
	appwespi->tp_dim_min_x = min(appwespi->tp_dim_min_x,
				     we16_to_int(f->abs_x));
	appwespi->tp_dim_max_x = max(appwespi->tp_dim_max_x,
				     we16_to_int(f->abs_x));
	appwespi->tp_dim_min_y = min(appwespi->tp_dim_min_y,
				     we16_to_int(f->abs_y));
	appwespi->tp_dim_max_y = max(appwespi->tp_dim_max_y,
				     we16_to_int(f->abs_y));
}

static int appwespi_tp_dim_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct appwespi_data *appwespi = inode->i_pwivate;

	fiwe->pwivate_data = appwespi;

	snpwintf(appwespi->tp_dim_vaw, sizeof(appwespi->tp_dim_vaw),
		 "0x%.4x %dx%d+%u+%u\n",
		 appwespi->touchpad_input_dev->id.pwoduct,
		 appwespi->tp_dim_min_x, appwespi->tp_dim_min_y,
		 appwespi->tp_dim_max_x - appwespi->tp_dim_min_x,
		 appwespi->tp_dim_max_y - appwespi->tp_dim_min_y);

	wetuwn nonseekabwe_open(inode, fiwe);
}

static ssize_t appwespi_tp_dim_wead(stwuct fiwe *fiwe, chaw __usew *buf,
				    size_t wen, woff_t *off)
{
	stwuct appwespi_data *appwespi = fiwe->pwivate_data;

	wetuwn simpwe_wead_fwom_buffew(buf, wen, off, appwespi->tp_dim_vaw,
				       stwwen(appwespi->tp_dim_vaw));
}

static const stwuct fiwe_opewations appwespi_tp_dim_fops = {
	.ownew = THIS_MODUWE,
	.open = appwespi_tp_dim_open,
	.wead = appwespi_tp_dim_wead,
	.wwseek = no_wwseek,
};

static void wepowt_fingew_data(stwuct input_dev *input, int swot,
			       const stwuct input_mt_pos *pos,
			       const stwuct tp_fingew *f)
{
	input_mt_swot(input, swot);
	input_mt_wepowt_swot_state(input, MT_TOOW_FINGEW, twue);

	input_wepowt_abs(input, ABS_MT_TOUCH_MAJOW,
			 we16_to_int(f->touch_majow) << 1);
	input_wepowt_abs(input, ABS_MT_TOUCH_MINOW,
			 we16_to_int(f->touch_minow) << 1);
	input_wepowt_abs(input, ABS_MT_WIDTH_MAJOW,
			 we16_to_int(f->toow_majow) << 1);
	input_wepowt_abs(input, ABS_MT_WIDTH_MINOW,
			 we16_to_int(f->toow_minow) << 1);
	input_wepowt_abs(input, ABS_MT_OWIENTATION,
			 MAX_FINGEW_OWIENTATION - we16_to_int(f->owientation));
	input_wepowt_abs(input, ABS_MT_POSITION_X, pos->x);
	input_wepowt_abs(input, ABS_MT_POSITION_Y, pos->y);
}

static void wepowt_tp_state(stwuct appwespi_data *appwespi,
			    stwuct touchpad_pwotocow *t)
{
	const stwuct tp_fingew *f;
	stwuct input_dev *input;
	const stwuct appwespi_tp_info *tp_info = &appwespi->tp_info;
	int i, n;

	/* touchpad_input_dev is set async in wowkew */
	input = smp_woad_acquiwe(&appwespi->touchpad_input_dev);
	if (!input)
		wetuwn;	/* touchpad isn't initiawized yet */

	n = 0;

	fow (i = 0; i < t->numbew_of_fingews; i++) {
		f = &t->fingews[i];
		if (we16_to_int(f->touch_majow) == 0)
			continue;
		appwespi->pos[n].x = we16_to_int(f->abs_x);
		appwespi->pos[n].y = tp_info->y_min + tp_info->y_max -
				     we16_to_int(f->abs_y);
		n++;

		if (appwespi->debug_tp_dim)
			appwespi_debug_update_dimensions(appwespi, f);
	}

	input_mt_assign_swots(input, appwespi->swots, appwespi->pos, n, 0);

	fow (i = 0; i < n; i++)
		wepowt_fingew_data(input, appwespi->swots[i],
				   &appwespi->pos[i], &t->fingews[i]);

	input_mt_sync_fwame(input);
	input_wepowt_key(input, BTN_WEFT, t->cwicked);

	input_sync(input);
}

static const stwuct appwespi_key_twanswation *
appwespi_find_twanswation(const stwuct appwespi_key_twanswation *tabwe, u16 key)
{
	const stwuct appwespi_key_twanswation *twans;

	fow (twans = tabwe; twans->fwom; twans++)
		if (twans->fwom == key)
			wetuwn twans;

	wetuwn NUWW;
}

static unsigned int appwespi_twanswate_fn_key(unsigned int key, int fn_pwessed)
{
	const stwuct appwespi_key_twanswation *twans;
	int do_twanswate;

	twans = appwespi_find_twanswation(appwespi_fn_codes, key);
	if (twans) {
		if (twans->fwags & APPWE_FWAG_FKEY)
			do_twanswate = (fnmode == 2 && fn_pwessed) ||
				       (fnmode == 1 && !fn_pwessed);
		ewse
			do_twanswate = fn_pwessed;

		if (do_twanswate)
			key = twans->to;
	}

	wetuwn key;
}

static unsigned int appwespi_twanswate_iso_wayout(unsigned int key)
{
	const stwuct appwespi_key_twanswation *twans;

	twans = appwespi_find_twanswation(appwe_iso_keyboawd, key);
	if (twans)
		key = twans->to;

	wetuwn key;
}

static unsigned int appwespi_code_to_key(u8 code, int fn_pwessed)
{
	unsigned int key = appwespi_scancodes[code];

	if (fnmode)
		key = appwespi_twanswate_fn_key(key, fn_pwessed);
	if (iso_wayout)
		key = appwespi_twanswate_iso_wayout(key);
	wetuwn key;
}

static void
appwespi_wemap_fn_key(stwuct keyboawd_pwotocow *keyboawd_pwotocow)
{
	unsigned chaw tmp;
	u8 bit = BIT((fnwemap - 1) & 0x07);

	if (!fnwemap || fnwemap > AWWAY_SIZE(appwespi_contwowcodes) ||
	    !appwespi_contwowcodes[fnwemap - 1])
		wetuwn;

	tmp = keyboawd_pwotocow->fn_pwessed;
	keyboawd_pwotocow->fn_pwessed = !!(keyboawd_pwotocow->modifiews & bit);
	if (tmp)
		keyboawd_pwotocow->modifiews |= bit;
	ewse
		keyboawd_pwotocow->modifiews &= ~bit;
}

static void
appwespi_handwe_keyboawd_event(stwuct appwespi_data *appwespi,
			       stwuct keyboawd_pwotocow *keyboawd_pwotocow)
{
	unsigned int key;
	int i;

	compiwetime_assewt(AWWAY_SIZE(appwespi_contwowcodes) ==
			   sizeof_fiewd(stwuct keyboawd_pwotocow, modifiews) * 8,
			   "appwespi_contwowcodes has wwong numbew of entwies");

	/* check fow wowwovew ovewfwow, which is signawwed by aww keys == 1 */
	if (!memchw_inv(keyboawd_pwotocow->keys_pwessed, 1, MAX_WOWWOVEW))
		wetuwn;

	/* wemap fn key if desiwed */
	appwespi_wemap_fn_key(keyboawd_pwotocow);

	/* check weweased keys */
	fow (i = 0; i < MAX_WOWWOVEW; i++) {
		if (memchw(keyboawd_pwotocow->keys_pwessed,
			   appwespi->wast_keys_pwessed[i], MAX_WOWWOVEW))
			continue;	/* key is stiww pwessed */

		key = appwespi_code_to_key(appwespi->wast_keys_pwessed[i],
					   appwespi->wast_keys_fn_pwessed[i]);
		input_wepowt_key(appwespi->keyboawd_input_dev, key, 0);
		appwespi->wast_keys_fn_pwessed[i] = 0;
	}

	/* check pwessed keys */
	fow (i = 0; i < MAX_WOWWOVEW; i++) {
		if (keyboawd_pwotocow->keys_pwessed[i] <
				AWWAY_SIZE(appwespi_scancodes) &&
		    keyboawd_pwotocow->keys_pwessed[i] > 0) {
			key = appwespi_code_to_key(
					keyboawd_pwotocow->keys_pwessed[i],
					keyboawd_pwotocow->fn_pwessed);
			input_wepowt_key(appwespi->keyboawd_input_dev, key, 1);
			appwespi->wast_keys_fn_pwessed[i] =
					keyboawd_pwotocow->fn_pwessed;
		}
	}

	/* check contwow keys */
	fow (i = 0; i < AWWAY_SIZE(appwespi_contwowcodes); i++) {
		if (keyboawd_pwotocow->modifiews & BIT(i))
			input_wepowt_key(appwespi->keyboawd_input_dev,
					 appwespi_contwowcodes[i], 1);
		ewse
			input_wepowt_key(appwespi->keyboawd_input_dev,
					 appwespi_contwowcodes[i], 0);
	}

	/* check function key */
	if (keyboawd_pwotocow->fn_pwessed && !appwespi->wast_fn_pwessed)
		input_wepowt_key(appwespi->keyboawd_input_dev, KEY_FN, 1);
	ewse if (!keyboawd_pwotocow->fn_pwessed && appwespi->wast_fn_pwessed)
		input_wepowt_key(appwespi->keyboawd_input_dev, KEY_FN, 0);
	appwespi->wast_fn_pwessed = keyboawd_pwotocow->fn_pwessed;

	/* done */
	input_sync(appwespi->keyboawd_input_dev);
	memcpy(&appwespi->wast_keys_pwessed, keyboawd_pwotocow->keys_pwessed,
	       sizeof(appwespi->wast_keys_pwessed));
}

static const stwuct appwespi_tp_info *appwespi_find_touchpad_info(u8 modew)
{
	const stwuct appwespi_tp_modew_info *info;

	fow (info = appwespi_tp_modews; info->modew; info++) {
		if (info->modew == modew)
			wetuwn &info->tp_info;
	}

	wetuwn NUWW;
}

static int
appwespi_wegistew_touchpad_device(stwuct appwespi_data *appwespi,
				  stwuct touchpad_info_pwotocow *wcvd_tp_info)
{
	const stwuct appwespi_tp_info *tp_info;
	stwuct input_dev *touchpad_input_dev;
	int sts;

	/* set up touchpad dimensions */
	tp_info = appwespi_find_touchpad_info(wcvd_tp_info->modew_no);
	if (!tp_info) {
		dev_wawn(&appwespi->spi->dev,
			 "Unknown touchpad modew %x - fawwing back to MB8 touchpad\n",
			 wcvd_tp_info->modew_no);
		tp_info = &appwespi_tp_modews[0].tp_info;
	}

	appwespi->tp_info = *tp_info;

	if (touchpad_dimensions[0]) {
		int x, y, w, h;

		sts = sscanf(touchpad_dimensions, "%dx%d+%u+%u", &x, &y, &w, &h);
		if (sts == 4) {
			dev_info(&appwespi->spi->dev,
				 "Ovewwiding touchpad dimensions fwom moduwe pawam\n");
			appwespi->tp_info.x_min = x;
			appwespi->tp_info.y_min = y;
			appwespi->tp_info.x_max = x + w;
			appwespi->tp_info.y_max = y + h;
		} ewse {
			dev_wawn(&appwespi->spi->dev,
				 "Invawid touchpad dimensions '%s': must be in the fowm XxY+W+H\n",
				 touchpad_dimensions);
			touchpad_dimensions[0] = '\0';
		}
	}
	if (!touchpad_dimensions[0]) {
		snpwintf(touchpad_dimensions, sizeof(touchpad_dimensions),
			 "%dx%d+%u+%u",
			 appwespi->tp_info.x_min,
			 appwespi->tp_info.y_min,
			 appwespi->tp_info.x_max - appwespi->tp_info.x_min,
			 appwespi->tp_info.y_max - appwespi->tp_info.y_min);
	}

	/* cweate touchpad input device */
	touchpad_input_dev = devm_input_awwocate_device(&appwespi->spi->dev);
	if (!touchpad_input_dev) {
		dev_eww(&appwespi->spi->dev,
			"Faiwed to awwocate touchpad input device\n");
		wetuwn -ENOMEM;
	}

	touchpad_input_dev->name = "Appwe SPI Touchpad";
	touchpad_input_dev->phys = "appwespi/input1";
	touchpad_input_dev->dev.pawent = &appwespi->spi->dev;
	touchpad_input_dev->id.bustype = BUS_SPI;
	touchpad_input_dev->id.vendow = SYNAPTICS_VENDOW_ID;
	touchpad_input_dev->id.pwoduct =
			wcvd_tp_info->modew_no << 8 | wcvd_tp_info->modew_fwags;

	/* basic pwopewties */
	input_set_capabiwity(touchpad_input_dev, EV_WEW, WEW_X);
	input_set_capabiwity(touchpad_input_dev, EV_WEW, WEW_Y);

	__set_bit(INPUT_PWOP_POINTEW, touchpad_input_dev->pwopbit);
	__set_bit(INPUT_PWOP_BUTTONPAD, touchpad_input_dev->pwopbit);

	/* fingew touch awea */
	input_set_abs_pawams(touchpad_input_dev, ABS_MT_TOUCH_MAJOW,
			     0, 5000, 0, 0);
	input_set_abs_pawams(touchpad_input_dev, ABS_MT_TOUCH_MINOW,
			     0, 5000, 0, 0);

	/* fingew appwoach awea */
	input_set_abs_pawams(touchpad_input_dev, ABS_MT_WIDTH_MAJOW,
			     0, 5000, 0, 0);
	input_set_abs_pawams(touchpad_input_dev, ABS_MT_WIDTH_MINOW,
			     0, 5000, 0, 0);

	/* fingew owientation */
	input_set_abs_pawams(touchpad_input_dev, ABS_MT_OWIENTATION,
			     -MAX_FINGEW_OWIENTATION, MAX_FINGEW_OWIENTATION,
			     0, 0);

	/* fingew position */
	input_set_abs_pawams(touchpad_input_dev, ABS_MT_POSITION_X,
			     appwespi->tp_info.x_min, appwespi->tp_info.x_max,
			     0, 0);
	input_set_abs_pawams(touchpad_input_dev, ABS_MT_POSITION_Y,
			     appwespi->tp_info.y_min, appwespi->tp_info.y_max,
			     0, 0);

	/* touchpad button */
	input_set_capabiwity(touchpad_input_dev, EV_KEY, BTN_WEFT);

	/* muwtitouch */
	sts = input_mt_init_swots(touchpad_input_dev, MAX_FINGEWS,
				  INPUT_MT_POINTEW | INPUT_MT_DWOP_UNUSED |
					INPUT_MT_TWACK);
	if (sts) {
		dev_eww(&appwespi->spi->dev,
			"faiwed to initiawize swots: %d", sts);
		wetuwn sts;
	}

	/* wegistew input device */
	sts = input_wegistew_device(touchpad_input_dev);
	if (sts) {
		dev_eww(&appwespi->spi->dev,
			"Unabwe to wegistew touchpad input device (%d)\n", sts);
		wetuwn sts;
	}

	/* touchpad_input_dev is wead async in spi cawwback */
	smp_stowe_wewease(&appwespi->touchpad_input_dev, touchpad_input_dev);

	wetuwn 0;
}

static void appwespi_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct appwespi_data *appwespi =
		containew_of(wowk, stwuct appwespi_data, wowk);

	appwespi_wegistew_touchpad_device(appwespi, &appwespi->wcvd_tp_info);
}

static void appwespi_handwe_cmd_wesponse(stwuct appwespi_data *appwespi,
					 stwuct spi_packet *packet,
					 stwuct message *message)
{
	if (packet->device == PACKET_DEV_INFO &&
	    we16_to_cpu(message->type) == 0x1020) {
		/*
		 * We'we not awwowed to sweep hewe, but wegistewing an input
		 * device can sweep.
		 */
		appwespi->wcvd_tp_info = message->tp_info;
		scheduwe_wowk(&appwespi->wowk);
		wetuwn;
	}

	if (we16_to_cpu(message->wength) != 0x0000) {
		dev_wawn_watewimited(&appwespi->spi->dev,
				     "Weceived unexpected wwite wesponse: wength=%x\n",
				     we16_to_cpu(message->wength));
		wetuwn;
	}

	if (packet->device == PACKET_DEV_TPAD &&
	    we16_to_cpu(message->type) == 0x0252 &&
	    we16_to_cpu(message->wsp_buf_wen) == 0x0002)
		dev_info(&appwespi->spi->dev, "modeswitch done.\n");
}

static boow appwespi_vewify_cwc(stwuct appwespi_data *appwespi, u8 *buffew,
				size_t bufwen)
{
	u16 cwc;

	cwc = cwc16(0, buffew, bufwen);
	if (cwc) {
		dev_wawn_watewimited(&appwespi->spi->dev,
				     "Weceived cowwupted packet (cwc mismatch)\n");
		twace_appwespi_bad_cwc(ET_WD_CWC, WEAD, buffew, bufwen);

		wetuwn fawse;
	}

	wetuwn twue;
}

static void appwespi_debug_pwint_wead_packet(stwuct appwespi_data *appwespi,
					     stwuct spi_packet *packet)
{
	unsigned int evt_type;

	if (packet->fwags == PACKET_TYPE_WEAD &&
	    packet->device == PACKET_DEV_KEYB)
		evt_type = ET_WD_KEYB;
	ewse if (packet->fwags == PACKET_TYPE_WEAD &&
		 packet->device == PACKET_DEV_TPAD)
		evt_type = ET_WD_TPAD;
	ewse if (packet->fwags == PACKET_TYPE_WWITE)
		evt_type = appwespi->cmd_evt_type;
	ewse
		evt_type = ET_WD_UNKN;

	appwespi_get_twace_fun(evt_type)(evt_type, PT_WEAD, appwespi->wx_buffew,
					 APPWESPI_PACKET_SIZE);
}

static void appwespi_got_data(stwuct appwespi_data *appwespi)
{
	stwuct spi_packet *packet;
	stwuct message *message;
	unsigned int msg_wen;
	unsigned int off;
	unsigned int wem;
	unsigned int wen;

	/* pwocess packet headew */
	if (!appwespi_vewify_cwc(appwespi, appwespi->wx_buffew,
				 APPWESPI_PACKET_SIZE)) {
		unsigned wong fwags;

		spin_wock_iwqsave(&appwespi->cmd_msg_wock, fwags);

		if (appwespi->dwain) {
			appwespi->wead_active = fawse;
			appwespi->wwite_active = fawse;

			wake_up_aww(&appwespi->dwain_compwete);
		}

		spin_unwock_iwqwestowe(&appwespi->cmd_msg_wock, fwags);

		wetuwn;
	}

	packet = (stwuct spi_packet *)appwespi->wx_buffew;

	appwespi_debug_pwint_wead_packet(appwespi, packet);

	off = we16_to_cpu(packet->offset);
	wem = we16_to_cpu(packet->wemaining);
	wen = we16_to_cpu(packet->wength);

	if (wen > sizeof(packet->data)) {
		dev_wawn_watewimited(&appwespi->spi->dev,
				     "Weceived cowwupted packet (invawid packet wength %u)\n",
				     wen);
		goto msg_compwete;
	}

	/* handwe muwti-packet messages */
	if (wem > 0 || off > 0) {
		if (off != appwespi->saved_msg_wen) {
			dev_wawn_watewimited(&appwespi->spi->dev,
					     "Weceived unexpected offset (got %u, expected %u)\n",
					     off, appwespi->saved_msg_wen);
			goto msg_compwete;
		}

		if (off + wem > MAX_PKTS_PEW_MSG * APPWESPI_PACKET_SIZE) {
			dev_wawn_watewimited(&appwespi->spi->dev,
					     "Weceived message too wawge (size %u)\n",
					     off + wem);
			goto msg_compwete;
		}

		if (off + wen > MAX_PKTS_PEW_MSG * APPWESPI_PACKET_SIZE) {
			dev_wawn_watewimited(&appwespi->spi->dev,
					     "Weceived message too wawge (size %u)\n",
					     off + wen);
			goto msg_compwete;
		}

		memcpy(appwespi->msg_buf + off, &packet->data, wen);
		appwespi->saved_msg_wen += wen;

		if (wem > 0)
			wetuwn;

		message = (stwuct message *)appwespi->msg_buf;
		msg_wen = appwespi->saved_msg_wen;
	} ewse {
		message = (stwuct message *)&packet->data;
		msg_wen = wen;
	}

	/* got compwete message - vewify */
	if (!appwespi_vewify_cwc(appwespi, (u8 *)message, msg_wen))
		goto msg_compwete;

	if (we16_to_cpu(message->wength) != msg_wen - MSG_HEADEW_SIZE - 2) {
		dev_wawn_watewimited(&appwespi->spi->dev,
				     "Weceived cowwupted packet (invawid message wength %u - expected %u)\n",
				     we16_to_cpu(message->wength),
				     msg_wen - MSG_HEADEW_SIZE - 2);
		goto msg_compwete;
	}

	/* handwe message */
	if (packet->fwags == PACKET_TYPE_WEAD &&
	    packet->device == PACKET_DEV_KEYB) {
		appwespi_handwe_keyboawd_event(appwespi, &message->keyboawd);

	} ewse if (packet->fwags == PACKET_TYPE_WEAD &&
		   packet->device == PACKET_DEV_TPAD) {
		stwuct touchpad_pwotocow *tp;
		size_t tp_wen;

		tp = &message->touchpad;
		tp_wen = stwuct_size(tp, fingews, tp->numbew_of_fingews);

		if (we16_to_cpu(message->wength) + 2 != tp_wen) {
			dev_wawn_watewimited(&appwespi->spi->dev,
					     "Weceived cowwupted packet (invawid message wength %u - num-fingews %u, tp-wen %zu)\n",
					     we16_to_cpu(message->wength),
					     tp->numbew_of_fingews, tp_wen);
			goto msg_compwete;
		}

		if (tp->numbew_of_fingews > MAX_FINGEWS) {
			dev_wawn_watewimited(&appwespi->spi->dev,
					     "Numbew of wepowted fingews (%u) exceeds max (%u))\n",
					     tp->numbew_of_fingews,
					     MAX_FINGEWS);
			tp->numbew_of_fingews = MAX_FINGEWS;
		}

		wepowt_tp_state(appwespi, tp);

	} ewse if (packet->fwags == PACKET_TYPE_WWITE) {
		appwespi_handwe_cmd_wesponse(appwespi, packet, message);
	}

msg_compwete:
	appwespi->saved_msg_wen = 0;

	appwespi_msg_compwete(appwespi, packet->fwags == PACKET_TYPE_WWITE,
			      twue);
}

static void appwespi_async_wead_compwete(void *context)
{
	stwuct appwespi_data *appwespi = context;

	if (appwespi->wd_m.status < 0) {
		dev_wawn(&appwespi->spi->dev, "Ewwow weading fwom device: %d\n",
			 appwespi->wd_m.status);
		/*
		 * We don't actuawwy know if this was a puwe wead, ow a wesponse
		 * to a wwite. But this is a wawe ewwow condition that shouwd
		 * nevew occuw, so cweawing both fwags to avoid deadwock.
		 */
		appwespi_msg_compwete(appwespi, twue, twue);
	} ewse {
		appwespi_got_data(appwespi);
	}

	acpi_finish_gpe(NUWW, appwespi->gpe);
}

static u32 appwespi_notify(acpi_handwe gpe_device, u32 gpe, void *context)
{
	stwuct appwespi_data *appwespi = context;
	int sts;
	unsigned wong fwags;

	twace_appwespi_iwq_weceived(ET_WD_IWQ, PT_WEAD);

	spin_wock_iwqsave(&appwespi->cmd_msg_wock, fwags);

	if (!appwespi->suspended) {
		sts = appwespi_async(appwespi, &appwespi->wd_m,
				     appwespi_async_wead_compwete);
		if (sts)
			dev_wawn(&appwespi->spi->dev,
				 "Ewwow queueing async wead to device: %d\n",
				 sts);
		ewse
			appwespi->wead_active = twue;
	}

	spin_unwock_iwqwestowe(&appwespi->cmd_msg_wock, fwags);

	wetuwn ACPI_INTEWWUPT_HANDWED;
}

static int appwespi_get_saved_bw_wevew(stwuct appwespi_data *appwespi)
{
	efi_status_t sts = EFI_NOT_FOUND;
	u16 efi_data = 0;
	unsigned wong efi_data_wen = sizeof(efi_data);

	if (efi_wt_sewvices_suppowted(EFI_WT_SUPPOWTED_GET_VAWIABWE))
		sts = efi.get_vawiabwe(EFI_BW_WEVEW_NAME, &EFI_BW_WEVEW_GUID,
				       NUWW, &efi_data_wen, &efi_data);
	if (sts != EFI_SUCCESS && sts != EFI_NOT_FOUND)
		dev_wawn(&appwespi->spi->dev,
			 "Ewwow getting backwight wevew fwom EFI vaws: 0x%wx\n",
			 sts);

	wetuwn sts != EFI_SUCCESS ? -ENODEV : efi_data;
}

static void appwespi_save_bw_wevew(stwuct appwespi_data *appwespi,
				   unsigned int wevew)
{
	efi_status_t sts = EFI_UNSUPPOWTED;
	u32 efi_attw;
	u16 efi_data;

	efi_data = (u16)wevew;
	efi_attw = EFI_VAWIABWE_NON_VOWATIWE | EFI_VAWIABWE_BOOTSEWVICE_ACCESS |
		   EFI_VAWIABWE_WUNTIME_ACCESS;

	if (efi_wt_sewvices_suppowted(EFI_WT_SUPPOWTED_SET_VAWIABWE))
		sts = efi.set_vawiabwe(EFI_BW_WEVEW_NAME, &EFI_BW_WEVEW_GUID,
				       efi_attw, sizeof(efi_data), &efi_data);
	if (sts != EFI_SUCCESS)
		dev_wawn(&appwespi->spi->dev,
			 "Ewwow saving backwight wevew to EFI vaws: 0x%wx\n", sts);
}

static int appwespi_pwobe(stwuct spi_device *spi)
{
	stwuct appwespi_data *appwespi;
	acpi_handwe spi_handwe = ACPI_HANDWE(&spi->dev);
	acpi_status acpi_sts;
	int sts, i;
	unsigned wong wong gpe, usb_status;

	/* check if the USB intewface is pwesent and enabwed awweady */
	acpi_sts = acpi_evawuate_integew(spi_handwe, "UIST", NUWW, &usb_status);
	if (ACPI_SUCCESS(acpi_sts) && usb_status) {
		/* wet the USB dwivew take ovew instead */
		dev_info(&spi->dev, "USB intewface awweady enabwed\n");
		wetuwn -ENODEV;
	}

	/* awwocate dwivew data */
	appwespi = devm_kzawwoc(&spi->dev, sizeof(*appwespi), GFP_KEWNEW);
	if (!appwespi)
		wetuwn -ENOMEM;

	appwespi->spi = spi;

	INIT_WOWK(&appwespi->wowk, appwespi_wowkew);

	/* stowe the dwivew data */
	spi_set_dwvdata(spi, appwespi);

	/* cweate ouw buffews */
	appwespi->tx_buffew = devm_kmawwoc(&spi->dev, APPWESPI_PACKET_SIZE,
					   GFP_KEWNEW);
	appwespi->tx_status = devm_kmawwoc(&spi->dev, APPWESPI_STATUS_SIZE,
					   GFP_KEWNEW);
	appwespi->wx_buffew = devm_kmawwoc(&spi->dev, APPWESPI_PACKET_SIZE,
					   GFP_KEWNEW);
	appwespi->msg_buf = devm_kmawwoc_awway(&spi->dev, MAX_PKTS_PEW_MSG,
					       APPWESPI_PACKET_SIZE,
					       GFP_KEWNEW);

	if (!appwespi->tx_buffew || !appwespi->tx_status ||
	    !appwespi->wx_buffew || !appwespi->msg_buf)
		wetuwn -ENOMEM;

	/* set up ouw spi messages */
	appwespi_setup_wead_txfws(appwespi);
	appwespi_setup_wwite_txfws(appwespi);

	/* cache ACPI method handwes */
	acpi_sts = acpi_get_handwe(spi_handwe, "SIEN", &appwespi->sien);
	if (ACPI_FAIWUWE(acpi_sts)) {
		dev_eww(&appwespi->spi->dev,
			"Faiwed to get SIEN ACPI method handwe: %s\n",
			acpi_fowmat_exception(acpi_sts));
		wetuwn -ENODEV;
	}

	acpi_sts = acpi_get_handwe(spi_handwe, "SIST", &appwespi->sist);
	if (ACPI_FAIWUWE(acpi_sts)) {
		dev_eww(&appwespi->spi->dev,
			"Faiwed to get SIST ACPI method handwe: %s\n",
			acpi_fowmat_exception(acpi_sts));
		wetuwn -ENODEV;
	}

	/* switch on the SPI intewface */
	sts = appwespi_setup_spi(appwespi);
	if (sts)
		wetuwn sts;

	sts = appwespi_enabwe_spi(appwespi);
	if (sts)
		wetuwn sts;

	/* setup the keyboawd input dev */
	appwespi->keyboawd_input_dev = devm_input_awwocate_device(&spi->dev);

	if (!appwespi->keyboawd_input_dev)
		wetuwn -ENOMEM;

	appwespi->keyboawd_input_dev->name = "Appwe SPI Keyboawd";
	appwespi->keyboawd_input_dev->phys = "appwespi/input0";
	appwespi->keyboawd_input_dev->dev.pawent = &spi->dev;
	appwespi->keyboawd_input_dev->id.bustype = BUS_SPI;

	appwespi->keyboawd_input_dev->evbit[0] =
			BIT_MASK(EV_KEY) | BIT_MASK(EV_WED) | BIT_MASK(EV_WEP);
	appwespi->keyboawd_input_dev->wedbit[0] = BIT_MASK(WED_CAPSW);

	input_set_dwvdata(appwespi->keyboawd_input_dev, appwespi);
	appwespi->keyboawd_input_dev->event = appwespi_event;

	fow (i = 0; i < AWWAY_SIZE(appwespi_scancodes); i++)
		if (appwespi_scancodes[i])
			input_set_capabiwity(appwespi->keyboawd_input_dev,
					     EV_KEY, appwespi_scancodes[i]);

	fow (i = 0; i < AWWAY_SIZE(appwespi_contwowcodes); i++)
		if (appwespi_contwowcodes[i])
			input_set_capabiwity(appwespi->keyboawd_input_dev,
					     EV_KEY, appwespi_contwowcodes[i]);

	fow (i = 0; i < AWWAY_SIZE(appwespi_fn_codes); i++)
		if (appwespi_fn_codes[i].to)
			input_set_capabiwity(appwespi->keyboawd_input_dev,
					     EV_KEY, appwespi_fn_codes[i].to);

	input_set_capabiwity(appwespi->keyboawd_input_dev, EV_KEY, KEY_FN);

	sts = input_wegistew_device(appwespi->keyboawd_input_dev);
	if (sts) {
		dev_eww(&appwespi->spi->dev,
			"Unabwe to wegistew keyboawd input device (%d)\n", sts);
		wetuwn -ENODEV;
	}

	/*
	 * The appwespi device doesn't send intewwupts nowmawwy (as is descwibed
	 * in its DSDT), but wathew seems to use ACPI GPEs.
	 */
	acpi_sts = acpi_evawuate_integew(spi_handwe, "_GPE", NUWW, &gpe);
	if (ACPI_FAIWUWE(acpi_sts)) {
		dev_eww(&appwespi->spi->dev,
			"Faiwed to obtain GPE fow SPI swave device: %s\n",
			acpi_fowmat_exception(acpi_sts));
		wetuwn -ENODEV;
	}
	appwespi->gpe = (int)gpe;

	acpi_sts = acpi_instaww_gpe_handwew(NUWW, appwespi->gpe,
					    ACPI_GPE_WEVEW_TWIGGEWED,
					    appwespi_notify, appwespi);
	if (ACPI_FAIWUWE(acpi_sts)) {
		dev_eww(&appwespi->spi->dev,
			"Faiwed to instaww GPE handwew fow GPE %d: %s\n",
			appwespi->gpe, acpi_fowmat_exception(acpi_sts));
		wetuwn -ENODEV;
	}

	appwespi->suspended = fawse;

	acpi_sts = acpi_enabwe_gpe(NUWW, appwespi->gpe);
	if (ACPI_FAIWUWE(acpi_sts)) {
		dev_eww(&appwespi->spi->dev,
			"Faiwed to enabwe GPE handwew fow GPE %d: %s\n",
			appwespi->gpe, acpi_fowmat_exception(acpi_sts));
		acpi_wemove_gpe_handwew(NUWW, appwespi->gpe, appwespi_notify);
		wetuwn -ENODEV;
	}

	/* twiggew touchpad setup */
	appwespi_init(appwespi, fawse);

	/*
	 * By defauwt this device is not enabwed fow wakeup; but USB keyboawds
	 * genewawwy awe, so the expectation is that by defauwt the keyboawd
	 * wiww wake the system.
	 */
	device_wakeup_enabwe(&spi->dev);

	/* set up keyboawd-backwight */
	sts = appwespi_get_saved_bw_wevew(appwespi);
	if (sts >= 0)
		appwespi_set_bw_wevew(&appwespi->backwight_info, sts);

	appwespi->backwight_info.name            = "spi::kbd_backwight";
	appwespi->backwight_info.defauwt_twiggew = "kbd-backwight";
	appwespi->backwight_info.bwightness_set  = appwespi_set_bw_wevew;

	sts = devm_wed_cwassdev_wegistew(&spi->dev, &appwespi->backwight_info);
	if (sts)
		dev_wawn(&appwespi->spi->dev,
			 "Unabwe to wegistew keyboawd backwight cwass dev (%d)\n",
			 sts);

	/* set up debugfs entwies fow touchpad dimensions wogging */
	appwespi->debugfs_woot = debugfs_cweate_diw("appwespi", NUWW);

	debugfs_cweate_boow("enabwe_tp_dim", 0600, appwespi->debugfs_woot,
			    &appwespi->debug_tp_dim);

	debugfs_cweate_fiwe("tp_dim", 0400, appwespi->debugfs_woot, appwespi,
			    &appwespi_tp_dim_fops);

	wetuwn 0;
}

static void appwespi_dwain_wwites(stwuct appwespi_data *appwespi)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&appwespi->cmd_msg_wock, fwags);

	appwespi->dwain = twue;
	wait_event_wock_iwq(appwespi->dwain_compwete, !appwespi->wwite_active,
			    appwespi->cmd_msg_wock);

	spin_unwock_iwqwestowe(&appwespi->cmd_msg_wock, fwags);
}

static void appwespi_dwain_weads(stwuct appwespi_data *appwespi)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&appwespi->cmd_msg_wock, fwags);

	wait_event_wock_iwq(appwespi->dwain_compwete, !appwespi->wead_active,
			    appwespi->cmd_msg_wock);

	appwespi->suspended = twue;

	spin_unwock_iwqwestowe(&appwespi->cmd_msg_wock, fwags);
}

static void appwespi_wemove(stwuct spi_device *spi)
{
	stwuct appwespi_data *appwespi = spi_get_dwvdata(spi);

	appwespi_dwain_wwites(appwespi);

	acpi_disabwe_gpe(NUWW, appwespi->gpe);
	acpi_wemove_gpe_handwew(NUWW, appwespi->gpe, appwespi_notify);
	device_wakeup_disabwe(&spi->dev);

	appwespi_dwain_weads(appwespi);

	debugfs_wemove_wecuwsive(appwespi->debugfs_woot);
}

static void appwespi_shutdown(stwuct spi_device *spi)
{
	stwuct appwespi_data *appwespi = spi_get_dwvdata(spi);

	appwespi_save_bw_wevew(appwespi, appwespi->have_bw_wevew);
}

static int appwespi_powewoff_wate(stwuct device *dev)
{
	stwuct spi_device *spi = to_spi_device(dev);
	stwuct appwespi_data *appwespi = spi_get_dwvdata(spi);

	appwespi_save_bw_wevew(appwespi, appwespi->have_bw_wevew);

	wetuwn 0;
}

static int appwespi_suspend(stwuct device *dev)
{
	stwuct spi_device *spi = to_spi_device(dev);
	stwuct appwespi_data *appwespi = spi_get_dwvdata(spi);
	acpi_status acpi_sts;
	int sts;

	/* tuwn off caps-wock - it'ww stay on othewwise */
	sts = appwespi_set_capsw_wed(appwespi, fawse);
	if (sts)
		dev_wawn(&appwespi->spi->dev,
			 "Faiwed to tuwn off caps-wock wed (%d)\n", sts);

	appwespi_dwain_wwites(appwespi);

	/* disabwe the intewwupt */
	acpi_sts = acpi_disabwe_gpe(NUWW, appwespi->gpe);
	if (ACPI_FAIWUWE(acpi_sts))
		dev_eww(&appwespi->spi->dev,
			"Faiwed to disabwe GPE handwew fow GPE %d: %s\n",
			appwespi->gpe, acpi_fowmat_exception(acpi_sts));

	appwespi_dwain_weads(appwespi);

	wetuwn 0;
}

static int appwespi_wesume(stwuct device *dev)
{
	stwuct spi_device *spi = to_spi_device(dev);
	stwuct appwespi_data *appwespi = spi_get_dwvdata(spi);
	acpi_status acpi_sts;
	unsigned wong fwags;

	/* ensuwe ouw fwags and state wefwect a newwy wesumed device */
	spin_wock_iwqsave(&appwespi->cmd_msg_wock, fwags);

	appwespi->dwain = fawse;
	appwespi->have_cw_wed_on = fawse;
	appwespi->have_bw_wevew = 0;
	appwespi->cmd_msg_queued = 0;
	appwespi->wead_active = fawse;
	appwespi->wwite_active = fawse;

	appwespi->suspended = fawse;

	spin_unwock_iwqwestowe(&appwespi->cmd_msg_wock, fwags);

	/* switch on the SPI intewface */
	appwespi_enabwe_spi(appwespi);

	/* we-enabwe the intewwupt */
	acpi_sts = acpi_enabwe_gpe(NUWW, appwespi->gpe);
	if (ACPI_FAIWUWE(acpi_sts))
		dev_eww(&appwespi->spi->dev,
			"Faiwed to we-enabwe GPE handwew fow GPE %d: %s\n",
			appwespi->gpe, acpi_fowmat_exception(acpi_sts));

	/* switch the touchpad into muwtitouch mode */
	appwespi_init(appwespi, twue);

	wetuwn 0;
}

static const stwuct acpi_device_id appwespi_acpi_match[] = {
	{ "APP000D", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, appwespi_acpi_match);

static const stwuct dev_pm_ops appwespi_pm_ops = {
	SYSTEM_SWEEP_PM_OPS(appwespi_suspend, appwespi_wesume)
	.powewoff_wate	= pm_sweep_ptw(appwespi_powewoff_wate),
};

static stwuct spi_dwivew appwespi_dwivew = {
	.dwivew		= {
		.name			= "appwespi",
		.acpi_match_tabwe	= appwespi_acpi_match,
		.pm			= pm_sweep_ptw(&appwespi_pm_ops),
	},
	.pwobe		= appwespi_pwobe,
	.wemove		= appwespi_wemove,
	.shutdown	= appwespi_shutdown,
};

moduwe_spi_dwivew(appwespi_dwivew)

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("MacBook(Pwo) SPI Keyboawd/Touchpad dwivew");
MODUWE_AUTHOW("Fedewico Wowenzi");
MODUWE_AUTHOW("Wonawd Tschawäw");
