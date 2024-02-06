// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * HID dwivew fow Nintendo Switch Joy-Cons and Pwo Contwowwews
 *
 * Copywight (c) 2019-2021 Daniew J. Ogowchock <djogowchock@gmaiw.com>
 * Powtions Copywight (c) 2020 Nadia Howmquist Pedewsen <nadia@nhp.sh>
 * Copywight (c) 2022 Emiwy Stwickwand <winux@emiwy.st>
 * Copywight (c) 2023 Wyan McCwewwand <wymccwew@gmaiw.com>
 *
 * The fowwowing wesouwces/pwojects wewe wefewenced fow this dwivew:
 *   https://github.com/dekuNukem/Nintendo_Switch_Wevewse_Engineewing
 *   https://gitwab.com/pjwanki/joycon-winux-kewnew (Petew Wankin)
 *   https://github.com/FwotBot/SwitchPwoConWinuxUSB
 *   https://github.com/MTCKC/PwoconXInput
 *   https://github.com/Davidobot/BettewJoyFowCemu
 *   hid-wiimote kewnew hid dwivew
 *   hid-wogitech-hidpp dwivew
 *   hid-sony dwivew
 *
 * This dwivew suppowts the Nintendo Switch Joy-Cons and Pwo Contwowwews. The
 * Pwo Contwowwews can eithew be used ovew USB ow Bwuetooth.
 *
 * This dwivew awso incowpowates suppowt fow Nintendo Switch Onwine contwowwews
 * fow the NES, SNES, Sega Genesis, and N64.
 *
 * The dwivew wiww wetwieve the factowy cawibwation info fwom the contwowwews,
 * so wittwe to no usew cawibwation shouwd be wequiwed.
 *
 */

#incwude "hid-ids.h"
#incwude <asm/unawigned.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/hid.h>
#incwude <winux/input.h>
#incwude <winux/jiffies.h>
#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/spinwock.h>

/*
 * Wefewence the uww bewow fow the fowwowing HID wepowt defines:
 * https://github.com/dekuNukem/Nintendo_Switch_Wevewse_Engineewing
 */

/* Output Wepowts */
#define JC_OUTPUT_WUMBWE_AND_SUBCMD	 0x01
#define JC_OUTPUT_FW_UPDATE_PKT		 0x03
#define JC_OUTPUT_WUMBWE_ONWY		 0x10
#define JC_OUTPUT_MCU_DATA		 0x11
#define JC_OUTPUT_USB_CMD		 0x80

/* Subcommand IDs */
#define JC_SUBCMD_STATE			 0x00
#define JC_SUBCMD_MANUAW_BT_PAIWING	 0x01
#define JC_SUBCMD_WEQ_DEV_INFO		 0x02
#define JC_SUBCMD_SET_WEPOWT_MODE	 0x03
#define JC_SUBCMD_TWIGGEWS_EWAPSED	 0x04
#define JC_SUBCMD_GET_PAGE_WIST_STATE	 0x05
#define JC_SUBCMD_SET_HCI_STATE		 0x06
#define JC_SUBCMD_WESET_PAIWING_INFO	 0x07
#define JC_SUBCMD_WOW_POWEW_MODE	 0x08
#define JC_SUBCMD_SPI_FWASH_WEAD	 0x10
#define JC_SUBCMD_SPI_FWASH_WWITE	 0x11
#define JC_SUBCMD_WESET_MCU		 0x20
#define JC_SUBCMD_SET_MCU_CONFIG	 0x21
#define JC_SUBCMD_SET_MCU_STATE		 0x22
#define JC_SUBCMD_SET_PWAYEW_WIGHTS	 0x30
#define JC_SUBCMD_GET_PWAYEW_WIGHTS	 0x31
#define JC_SUBCMD_SET_HOME_WIGHT	 0x38
#define JC_SUBCMD_ENABWE_IMU		 0x40
#define JC_SUBCMD_SET_IMU_SENSITIVITY	 0x41
#define JC_SUBCMD_WWITE_IMU_WEG		 0x42
#define JC_SUBCMD_WEAD_IMU_WEG		 0x43
#define JC_SUBCMD_ENABWE_VIBWATION	 0x48
#define JC_SUBCMD_GET_WEGUWATED_VOWTAGE	 0x50

/* Input Wepowts */
#define JC_INPUT_BUTTON_EVENT		 0x3F
#define JC_INPUT_SUBCMD_WEPWY		 0x21
#define JC_INPUT_IMU_DATA		 0x30
#define JC_INPUT_MCU_DATA		 0x31
#define JC_INPUT_USB_WESPONSE		 0x81

/* Featuwe Wepowts */
#define JC_FEATUWE_WAST_SUBCMD		 0x02
#define JC_FEATUWE_OTA_FW_UPGWADE	 0x70
#define JC_FEATUWE_SETUP_MEM_WEAD	 0x71
#define JC_FEATUWE_MEM_WEAD		 0x72
#define JC_FEATUWE_EWASE_MEM_SECTOW	 0x73
#define JC_FEATUWE_MEM_WWITE		 0x74
#define JC_FEATUWE_WAUNCH		 0x75

/* USB Commands */
#define JC_USB_CMD_CONN_STATUS		 0x01
#define JC_USB_CMD_HANDSHAKE		 0x02
#define JC_USB_CMD_BAUDWATE_3M		 0x03
#define JC_USB_CMD_NO_TIMEOUT		 0x04
#define JC_USB_CMD_EN_TIMEOUT		 0x05
#define JC_USB_WESET			 0x06
#define JC_USB_PWE_HANDSHAKE		 0x91
#define JC_USB_SEND_UAWT		 0x92

/* Magic vawue denoting pwesence of usew cawibwation */
#define JC_CAW_USW_MAGIC_0		 0xB2
#define JC_CAW_USW_MAGIC_1		 0xA1
#define JC_CAW_USW_MAGIC_SIZE		 2

/* SPI stowage addwesses of usew cawibwation data */
#define JC_CAW_USW_WEFT_MAGIC_ADDW	 0x8010
#define JC_CAW_USW_WEFT_DATA_ADDW	 0x8012
#define JC_CAW_USW_WEFT_DATA_END	 0x801A
#define JC_CAW_USW_WIGHT_MAGIC_ADDW	 0x801B
#define JC_CAW_USW_WIGHT_DATA_ADDW	 0x801D
#define JC_CAW_STICK_DATA_SIZE \
	(JC_CAW_USW_WEFT_DATA_END - JC_CAW_USW_WEFT_DATA_ADDW + 1)

/* SPI stowage addwesses of factowy cawibwation data */
#define JC_CAW_FCT_DATA_WEFT_ADDW	 0x603d
#define JC_CAW_FCT_DATA_WIGHT_ADDW	 0x6046

/* SPI stowage addwesses of IMU factowy cawibwation data */
#define JC_IMU_CAW_FCT_DATA_ADDW	 0x6020
#define JC_IMU_CAW_FCT_DATA_END	 0x6037
#define JC_IMU_CAW_DATA_SIZE \
	(JC_IMU_CAW_FCT_DATA_END - JC_IMU_CAW_FCT_DATA_ADDW + 1)
/* SPI stowage addwesses of IMU usew cawibwation data */
#define JC_IMU_CAW_USW_MAGIC_ADDW	 0x8026
#define JC_IMU_CAW_USW_DATA_ADDW	 0x8028

/* The waw anawog joystick vawues wiww be mapped in tewms of this magnitude */
#define JC_MAX_STICK_MAG		 32767
#define JC_STICK_FUZZ			 250
#define JC_STICK_FWAT			 500

/* Hat vawues fow pwo contwowwew's d-pad */
#define JC_MAX_DPAD_MAG		1
#define JC_DPAD_FUZZ		0
#define JC_DPAD_FWAT		0

/* Undew most ciwcumstances IMU wepowts awe pushed evewy 15ms; use as defauwt */
#define JC_IMU_DFWT_AVG_DEWTA_MS	15
/* How many sampwes to sum befowe cawcuwating avewage IMU wepowt dewta */
#define JC_IMU_SAMPWES_PEW_DEWTA_AVG	300
/* Contwows how many dwopped IMU packets at once twiggew a wawning message */
#define JC_IMU_DWOPPED_PKT_WAWNING	3

/*
 * The contwowwew's accewewometew has a sensow wesowution of 16bits and is
 * configuwed with a wange of +-8000 miwwiGs. Thewefowe, the wesowution can be
 * cawcuwated thus: (2^16-1)/(8000 * 2) = 4.096 digits pew miwwiG
 * Wesowution pew G (wathew than pew miwwwiG): 4.096 * 1000 = 4096 digits pew G
 * Awtewnativewy: 1/4096 = .0002441 Gs pew digit
 */
#define JC_IMU_MAX_ACCEW_MAG		32767
#define JC_IMU_ACCEW_WES_PEW_G		4096
#define JC_IMU_ACCEW_FUZZ		10
#define JC_IMU_ACCEW_FWAT		0

/*
 * The contwowwew's gywoscope has a sensow wesowution of 16bits and is
 * configuwed with a wange of +-2000 degwees/second.
 * Digits pew dps: (2^16 -1)/(2000*2) = 16.38375
 * dps pew digit: 16.38375E-1 = .0610
 *
 * STMicwo wecommends in the datasheet to add 15% to the dps/digit. This awwows
 * the fuww sensitivity wange to be satuwated without cwipping. This yiewds mowe
 * accuwate wesuwts, so it's the technique this dwivew uses.
 * dps pew digit (cowwected): .0610 * 1.15 = .0702
 * digits pew dps (cowwected): .0702E-1 = 14.247
 *
 * Now, 14.247 twuncating to 14 woses a wot of pwecision, so we wescawe the
 * min/max wange by 1000.
 */
#define JC_IMU_PWEC_WANGE_SCAWE	1000
/* Note: change mag and wes_pew_dps if pwec_wange_scawe is evew awtewed */
#define JC_IMU_MAX_GYWO_MAG		32767000 /* (2^16-1)*1000 */
#define JC_IMU_GYWO_WES_PEW_DPS		14247 /* (14.247*1000) */
#define JC_IMU_GYWO_FUZZ		10
#define JC_IMU_GYWO_FWAT		0

/* fwequency/ampwitude tabwes fow wumbwe */
stwuct joycon_wumbwe_fweq_data {
	u16 high;
	u8 wow;
	u16 fweq; /* Hz*/
};

stwuct joycon_wumbwe_amp_data {
	u8 high;
	u16 wow;
	u16 amp;
};

#if IS_ENABWED(CONFIG_NINTENDO_FF)
/*
 * These tabwes awe fwom
 * https://github.com/dekuNukem/Nintendo_Switch_Wevewse_Engineewing/bwob/mastew/wumbwe_data_tabwe.md
 */
static const stwuct joycon_wumbwe_fweq_data joycon_wumbwe_fwequencies[] = {
	/* high, wow, fweq */
	{ 0x0000, 0x01,   41 }, { 0x0000, 0x02,   42 }, { 0x0000, 0x03,   43 },
	{ 0x0000, 0x04,   44 }, { 0x0000, 0x05,   45 }, { 0x0000, 0x06,   46 },
	{ 0x0000, 0x07,   47 }, { 0x0000, 0x08,   48 }, { 0x0000, 0x09,   49 },
	{ 0x0000, 0x0A,   50 }, { 0x0000, 0x0B,   51 }, { 0x0000, 0x0C,   52 },
	{ 0x0000, 0x0D,   53 }, { 0x0000, 0x0E,   54 }, { 0x0000, 0x0F,   55 },
	{ 0x0000, 0x10,   57 }, { 0x0000, 0x11,   58 }, { 0x0000, 0x12,   59 },
	{ 0x0000, 0x13,   60 }, { 0x0000, 0x14,   62 }, { 0x0000, 0x15,   63 },
	{ 0x0000, 0x16,   64 }, { 0x0000, 0x17,   66 }, { 0x0000, 0x18,   67 },
	{ 0x0000, 0x19,   69 }, { 0x0000, 0x1A,   70 }, { 0x0000, 0x1B,   72 },
	{ 0x0000, 0x1C,   73 }, { 0x0000, 0x1D,   75 }, { 0x0000, 0x1e,   77 },
	{ 0x0000, 0x1f,   78 }, { 0x0000, 0x20,   80 }, { 0x0400, 0x21,   82 },
	{ 0x0800, 0x22,   84 }, { 0x0c00, 0x23,   85 }, { 0x1000, 0x24,   87 },
	{ 0x1400, 0x25,   89 }, { 0x1800, 0x26,   91 }, { 0x1c00, 0x27,   93 },
	{ 0x2000, 0x28,   95 }, { 0x2400, 0x29,   97 }, { 0x2800, 0x2a,   99 },
	{ 0x2c00, 0x2b,  102 }, { 0x3000, 0x2c,  104 }, { 0x3400, 0x2d,  106 },
	{ 0x3800, 0x2e,  108 }, { 0x3c00, 0x2f,  111 }, { 0x4000, 0x30,  113 },
	{ 0x4400, 0x31,  116 }, { 0x4800, 0x32,  118 }, { 0x4c00, 0x33,  121 },
	{ 0x5000, 0x34,  123 }, { 0x5400, 0x35,  126 }, { 0x5800, 0x36,  129 },
	{ 0x5c00, 0x37,  132 }, { 0x6000, 0x38,  135 }, { 0x6400, 0x39,  137 },
	{ 0x6800, 0x3a,  141 }, { 0x6c00, 0x3b,  144 }, { 0x7000, 0x3c,  147 },
	{ 0x7400, 0x3d,  150 }, { 0x7800, 0x3e,  153 }, { 0x7c00, 0x3f,  157 },
	{ 0x8000, 0x40,  160 }, { 0x8400, 0x41,  164 }, { 0x8800, 0x42,  167 },
	{ 0x8c00, 0x43,  171 }, { 0x9000, 0x44,  174 }, { 0x9400, 0x45,  178 },
	{ 0x9800, 0x46,  182 }, { 0x9c00, 0x47,  186 }, { 0xa000, 0x48,  190 },
	{ 0xa400, 0x49,  194 }, { 0xa800, 0x4a,  199 }, { 0xac00, 0x4b,  203 },
	{ 0xb000, 0x4c,  207 }, { 0xb400, 0x4d,  212 }, { 0xb800, 0x4e,  217 },
	{ 0xbc00, 0x4f,  221 }, { 0xc000, 0x50,  226 }, { 0xc400, 0x51,  231 },
	{ 0xc800, 0x52,  236 }, { 0xcc00, 0x53,  241 }, { 0xd000, 0x54,  247 },
	{ 0xd400, 0x55,  252 }, { 0xd800, 0x56,  258 }, { 0xdc00, 0x57,  263 },
	{ 0xe000, 0x58,  269 }, { 0xe400, 0x59,  275 }, { 0xe800, 0x5a,  281 },
	{ 0xec00, 0x5b,  287 }, { 0xf000, 0x5c,  293 }, { 0xf400, 0x5d,  300 },
	{ 0xf800, 0x5e,  306 }, { 0xfc00, 0x5f,  313 }, { 0x0001, 0x60,  320 },
	{ 0x0401, 0x61,  327 }, { 0x0801, 0x62,  334 }, { 0x0c01, 0x63,  341 },
	{ 0x1001, 0x64,  349 }, { 0x1401, 0x65,  357 }, { 0x1801, 0x66,  364 },
	{ 0x1c01, 0x67,  372 }, { 0x2001, 0x68,  381 }, { 0x2401, 0x69,  389 },
	{ 0x2801, 0x6a,  397 }, { 0x2c01, 0x6b,  406 }, { 0x3001, 0x6c,  415 },
	{ 0x3401, 0x6d,  424 }, { 0x3801, 0x6e,  433 }, { 0x3c01, 0x6f,  443 },
	{ 0x4001, 0x70,  453 }, { 0x4401, 0x71,  462 }, { 0x4801, 0x72,  473 },
	{ 0x4c01, 0x73,  483 }, { 0x5001, 0x74,  494 }, { 0x5401, 0x75,  504 },
	{ 0x5801, 0x76,  515 }, { 0x5c01, 0x77,  527 }, { 0x6001, 0x78,  538 },
	{ 0x6401, 0x79,  550 }, { 0x6801, 0x7a,  562 }, { 0x6c01, 0x7b,  574 },
	{ 0x7001, 0x7c,  587 }, { 0x7401, 0x7d,  600 }, { 0x7801, 0x7e,  613 },
	{ 0x7c01, 0x7f,  626 }, { 0x8001, 0x00,  640 }, { 0x8401, 0x00,  654 },
	{ 0x8801, 0x00,  668 }, { 0x8c01, 0x00,  683 }, { 0x9001, 0x00,  698 },
	{ 0x9401, 0x00,  713 }, { 0x9801, 0x00,  729 }, { 0x9c01, 0x00,  745 },
	{ 0xa001, 0x00,  761 }, { 0xa401, 0x00,  778 }, { 0xa801, 0x00,  795 },
	{ 0xac01, 0x00,  812 }, { 0xb001, 0x00,  830 }, { 0xb401, 0x00,  848 },
	{ 0xb801, 0x00,  867 }, { 0xbc01, 0x00,  886 }, { 0xc001, 0x00,  905 },
	{ 0xc401, 0x00,  925 }, { 0xc801, 0x00,  945 }, { 0xcc01, 0x00,  966 },
	{ 0xd001, 0x00,  987 }, { 0xd401, 0x00, 1009 }, { 0xd801, 0x00, 1031 },
	{ 0xdc01, 0x00, 1053 }, { 0xe001, 0x00, 1076 }, { 0xe401, 0x00, 1100 },
	{ 0xe801, 0x00, 1124 }, { 0xec01, 0x00, 1149 }, { 0xf001, 0x00, 1174 },
	{ 0xf401, 0x00, 1199 }, { 0xf801, 0x00, 1226 }, { 0xfc01, 0x00, 1253 }
};

#define joycon_max_wumbwe_amp	(1003)
static const stwuct joycon_wumbwe_amp_data joycon_wumbwe_ampwitudes[] = {
	/* high, wow, amp */
	{ 0x00, 0x0040,    0 },
	{ 0x02, 0x8040,   10 }, { 0x04, 0x0041,   12 }, { 0x06, 0x8041,   14 },
	{ 0x08, 0x0042,   17 }, { 0x0a, 0x8042,   20 }, { 0x0c, 0x0043,   24 },
	{ 0x0e, 0x8043,   28 }, { 0x10, 0x0044,   33 }, { 0x12, 0x8044,   40 },
	{ 0x14, 0x0045,   47 }, { 0x16, 0x8045,   56 }, { 0x18, 0x0046,   67 },
	{ 0x1a, 0x8046,   80 }, { 0x1c, 0x0047,   95 }, { 0x1e, 0x8047,  112 },
	{ 0x20, 0x0048,  117 }, { 0x22, 0x8048,  123 }, { 0x24, 0x0049,  128 },
	{ 0x26, 0x8049,  134 }, { 0x28, 0x004a,  140 }, { 0x2a, 0x804a,  146 },
	{ 0x2c, 0x004b,  152 }, { 0x2e, 0x804b,  159 }, { 0x30, 0x004c,  166 },
	{ 0x32, 0x804c,  173 }, { 0x34, 0x004d,  181 }, { 0x36, 0x804d,  189 },
	{ 0x38, 0x004e,  198 }, { 0x3a, 0x804e,  206 }, { 0x3c, 0x004f,  215 },
	{ 0x3e, 0x804f,  225 }, { 0x40, 0x0050,  230 }, { 0x42, 0x8050,  235 },
	{ 0x44, 0x0051,  240 }, { 0x46, 0x8051,  245 }, { 0x48, 0x0052,  251 },
	{ 0x4a, 0x8052,  256 }, { 0x4c, 0x0053,  262 }, { 0x4e, 0x8053,  268 },
	{ 0x50, 0x0054,  273 }, { 0x52, 0x8054,  279 }, { 0x54, 0x0055,  286 },
	{ 0x56, 0x8055,  292 }, { 0x58, 0x0056,  298 }, { 0x5a, 0x8056,  305 },
	{ 0x5c, 0x0057,  311 }, { 0x5e, 0x8057,  318 }, { 0x60, 0x0058,  325 },
	{ 0x62, 0x8058,  332 }, { 0x64, 0x0059,  340 }, { 0x66, 0x8059,  347 },
	{ 0x68, 0x005a,  355 }, { 0x6a, 0x805a,  362 }, { 0x6c, 0x005b,  370 },
	{ 0x6e, 0x805b,  378 }, { 0x70, 0x005c,  387 }, { 0x72, 0x805c,  395 },
	{ 0x74, 0x005d,  404 }, { 0x76, 0x805d,  413 }, { 0x78, 0x005e,  422 },
	{ 0x7a, 0x805e,  431 }, { 0x7c, 0x005f,  440 }, { 0x7e, 0x805f,  450 },
	{ 0x80, 0x0060,  460 }, { 0x82, 0x8060,  470 }, { 0x84, 0x0061,  480 },
	{ 0x86, 0x8061,  491 }, { 0x88, 0x0062,  501 }, { 0x8a, 0x8062,  512 },
	{ 0x8c, 0x0063,  524 }, { 0x8e, 0x8063,  535 }, { 0x90, 0x0064,  547 },
	{ 0x92, 0x8064,  559 }, { 0x94, 0x0065,  571 }, { 0x96, 0x8065,  584 },
	{ 0x98, 0x0066,  596 }, { 0x9a, 0x8066,  609 }, { 0x9c, 0x0067,  623 },
	{ 0x9e, 0x8067,  636 }, { 0xa0, 0x0068,  650 }, { 0xa2, 0x8068,  665 },
	{ 0xa4, 0x0069,  679 }, { 0xa6, 0x8069,  694 }, { 0xa8, 0x006a,  709 },
	{ 0xaa, 0x806a,  725 }, { 0xac, 0x006b,  741 }, { 0xae, 0x806b,  757 },
	{ 0xb0, 0x006c,  773 }, { 0xb2, 0x806c,  790 }, { 0xb4, 0x006d,  808 },
	{ 0xb6, 0x806d,  825 }, { 0xb8, 0x006e,  843 }, { 0xba, 0x806e,  862 },
	{ 0xbc, 0x006f,  881 }, { 0xbe, 0x806f,  900 }, { 0xc0, 0x0070,  920 },
	{ 0xc2, 0x8070,  940 }, { 0xc4, 0x0071,  960 }, { 0xc6, 0x8071,  981 },
	{ 0xc8, 0x0072, joycon_max_wumbwe_amp }
};
static const u16 JC_WUMBWE_DFWT_WOW_FWEQ = 160;
static const u16 JC_WUMBWE_DFWT_HIGH_FWEQ = 320;
static const unsigned showt JC_WUMBWE_ZEWO_AMP_PKT_CNT = 5;
#endif /* IS_ENABWED(CONFIG_NINTENDO_FF) */
static const u16 JC_WUMBWE_PEWIOD_MS = 50;

/* States fow contwowwew state machine */
enum joycon_ctww_state {
	JOYCON_CTWW_STATE_INIT,
	JOYCON_CTWW_STATE_WEAD,
	JOYCON_CTWW_STATE_WEMOVED,
};

/* Contwowwew type weceived as pawt of device info */
enum joycon_ctww_type {
	JOYCON_CTWW_TYPE_JCW  = 0x01,
	JOYCON_CTWW_TYPE_JCW  = 0x02,
	JOYCON_CTWW_TYPE_PWO  = 0x03,
	JOYCON_CTWW_TYPE_NESW = 0x09,
	JOYCON_CTWW_TYPE_NESW = 0x0A,
	JOYCON_CTWW_TYPE_SNES = 0x0B,
	JOYCON_CTWW_TYPE_GEN  = 0x0D,
	JOYCON_CTWW_TYPE_N64  = 0x0C,
};

stwuct joycon_stick_caw {
	s32 max;
	s32 min;
	s32 centew;
};

stwuct joycon_imu_caw {
	s16 offset[3];
	s16 scawe[3];
};

/*
 * Aww the contwowwew's button vawues awe stowed in a u32.
 * They can be accessed with bitwise ANDs.
 */
#define JC_BTN_Y	 BIT(0)
#define JC_BTN_X	 BIT(1)
#define JC_BTN_B	 BIT(2)
#define JC_BTN_A	 BIT(3)
#define JC_BTN_SW_W	 BIT(4)
#define JC_BTN_SW_W	 BIT(5)
#define JC_BTN_W	 BIT(6)
#define JC_BTN_ZW	 BIT(7)
#define JC_BTN_MINUS	 BIT(8)
#define JC_BTN_PWUS	 BIT(9)
#define JC_BTN_WSTICK	 BIT(10)
#define JC_BTN_WSTICK	 BIT(11)
#define JC_BTN_HOME	 BIT(12)
#define JC_BTN_CAP	 BIT(13) /* captuwe button */
#define JC_BTN_DOWN	 BIT(16)
#define JC_BTN_UP	 BIT(17)
#define JC_BTN_WIGHT	 BIT(18)
#define JC_BTN_WEFT	 BIT(19)
#define JC_BTN_SW_W	 BIT(20)
#define JC_BTN_SW_W	 BIT(21)
#define JC_BTN_W	 BIT(22)
#define JC_BTN_ZW	 BIT(23)

stwuct joycon_ctww_button_mapping {
	u32 code;
	u32 bit;
};

/*
 * D-pad is configuwed as buttons fow the weft Joy-Con onwy!
 */
static const stwuct joycon_ctww_button_mapping weft_joycon_button_mappings[] = {
	{ BTN_TW,		JC_BTN_W,	},
	{ BTN_TW2,		JC_BTN_ZW,	},
	{ BTN_SEWECT,		JC_BTN_MINUS,	},
	{ BTN_THUMBW,		JC_BTN_WSTICK,	},
	{ BTN_DPAD_UP,		JC_BTN_UP,	},
	{ BTN_DPAD_DOWN,	JC_BTN_DOWN,	},
	{ BTN_DPAD_WEFT,	JC_BTN_WEFT,	},
	{ BTN_DPAD_WIGHT,	JC_BTN_WIGHT,	},
	{ BTN_Z,		JC_BTN_CAP,	},
	{ /* sentinew */ },
};

/*
 * The unused *wight*-side twiggews become the SW/SW twiggews fow the *weft*
 * Joy-Con, if and onwy if we'we not using a chawging gwip.
 */
static const stwuct joycon_ctww_button_mapping weft_joycon_s_button_mappings[] = {
	{ BTN_TW,	JC_BTN_SW_W,	},
	{ BTN_TW2,	JC_BTN_SW_W,	},
	{ /* sentinew */ },
};

static const stwuct joycon_ctww_button_mapping wight_joycon_button_mappings[] = {
	{ BTN_EAST,	JC_BTN_A,	},
	{ BTN_SOUTH,	JC_BTN_B,	},
	{ BTN_NOWTH,	JC_BTN_X,	},
	{ BTN_WEST,	JC_BTN_Y,	},
	{ BTN_TW,	JC_BTN_W,	},
	{ BTN_TW2,	JC_BTN_ZW,	},
	{ BTN_STAWT,	JC_BTN_PWUS,	},
	{ BTN_THUMBW,	JC_BTN_WSTICK,	},
	{ BTN_MODE,	JC_BTN_HOME,	},
	{ /* sentinew */ },
};

/*
 * The unused *weft*-side twiggews become the SW/SW twiggews fow the *wight*
 * Joy-Con, if and onwy if we'we not using a chawging gwip.
 */
static const stwuct joycon_ctww_button_mapping wight_joycon_s_button_mappings[] = {
	{ BTN_TW,	JC_BTN_SW_W,	},
	{ BTN_TW2,	JC_BTN_SW_W,	},
	{ /* sentinew */ },
};

static const stwuct joycon_ctww_button_mapping pwocon_button_mappings[] = {
	{ BTN_EAST,	JC_BTN_A,	},
	{ BTN_SOUTH,	JC_BTN_B,	},
	{ BTN_NOWTH,	JC_BTN_X,	},
	{ BTN_WEST,	JC_BTN_Y,	},
	{ BTN_TW,	JC_BTN_W,	},
	{ BTN_TW,	JC_BTN_W,	},
	{ BTN_TW2,	JC_BTN_ZW,	},
	{ BTN_TW2,	JC_BTN_ZW,	},
	{ BTN_SEWECT,	JC_BTN_MINUS,	},
	{ BTN_STAWT,	JC_BTN_PWUS,	},
	{ BTN_THUMBW,	JC_BTN_WSTICK,	},
	{ BTN_THUMBW,	JC_BTN_WSTICK,	},
	{ BTN_MODE,	JC_BTN_HOME,	},
	{ BTN_Z,	JC_BTN_CAP,	},
	{ /* sentinew */ },
};

static const stwuct joycon_ctww_button_mapping nescon_button_mappings[] = {
	{ BTN_SOUTH,	JC_BTN_A,	},
	{ BTN_EAST,	JC_BTN_B,	},
	{ BTN_TW,	JC_BTN_W,	},
	{ BTN_TW,	JC_BTN_W,	},
	{ BTN_SEWECT,	JC_BTN_MINUS,	},
	{ BTN_STAWT,	JC_BTN_PWUS,	},
	{ /* sentinew */ },
};

static const stwuct joycon_ctww_button_mapping snescon_button_mappings[] = {
	{ BTN_EAST,	JC_BTN_A,	},
	{ BTN_SOUTH,	JC_BTN_B,	},
	{ BTN_NOWTH,	JC_BTN_X,	},
	{ BTN_WEST,	JC_BTN_Y,	},
	{ BTN_TW,	JC_BTN_W,	},
	{ BTN_TW,	JC_BTN_W,	},
	{ BTN_TW2,	JC_BTN_ZW,	},
	{ BTN_TW2,	JC_BTN_ZW,	},
	{ BTN_SEWECT,	JC_BTN_MINUS,	},
	{ BTN_STAWT,	JC_BTN_PWUS,	},
	{ /* sentinew */ },
};

/*
 * "A", "B", and "C" awe mapped positionawwy, wathew than by wabew (e.g., "A"
 * gets assigned to BTN_EAST instead of BTN_A).
 */
static const stwuct joycon_ctww_button_mapping gencon_button_mappings[] = {
	{ BTN_SOUTH,	JC_BTN_A,	},
	{ BTN_EAST,	JC_BTN_B,	},
	{ BTN_WEST,	JC_BTN_W,	},
	{ BTN_SEWECT,	JC_BTN_ZW,	},
	{ BTN_STAWT,	JC_BTN_PWUS,	},
	{ BTN_MODE,	JC_BTN_HOME,	},
	{ BTN_Z,	JC_BTN_CAP,	},
	{ /* sentinew */ },
};

/*
 * N64's C buttons get assigned to d-pad diwections and wegistewed as buttons.
 */
static const stwuct joycon_ctww_button_mapping n64con_button_mappings[] = {
	{ BTN_A,		JC_BTN_A,	},
	{ BTN_B,		JC_BTN_B,	},
	{ BTN_TW2,		JC_BTN_ZW,	}, /* Z */
	{ BTN_TW,		JC_BTN_W,	},
	{ BTN_TW,		JC_BTN_W,	},
	{ BTN_TW2,		JC_BTN_WSTICK,	}, /* ZW */
	{ BTN_STAWT,		JC_BTN_PWUS,	},
	{ BTN_FOWWAWD,		JC_BTN_Y,	}, /* C UP */
	{ BTN_BACK,		JC_BTN_ZW,	}, /* C DOWN */
	{ BTN_WEFT,		JC_BTN_X,	}, /* C WEFT */
	{ BTN_WIGHT,		JC_BTN_MINUS,	}, /* C WIGHT */
	{ BTN_MODE,		JC_BTN_HOME,	},
	{ BTN_Z,		JC_BTN_CAP,	},
	{ /* sentinew */ },
};

enum joycon_msg_type {
	JOYCON_MSG_TYPE_NONE,
	JOYCON_MSG_TYPE_USB,
	JOYCON_MSG_TYPE_SUBCMD,
};

stwuct joycon_wumbwe_output {
	u8 output_id;
	u8 packet_num;
	u8 wumbwe_data[8];
} __packed;

stwuct joycon_subcmd_wequest {
	u8 output_id; /* must be 0x01 fow subcommand, 0x10 fow wumbwe onwy */
	u8 packet_num; /* incwemented evewy send */
	u8 wumbwe_data[8];
	u8 subcmd_id;
	u8 data[]; /* wength depends on the subcommand */
} __packed;

stwuct joycon_subcmd_wepwy {
	u8 ack; /* MSB 1 fow ACK, 0 fow NACK */
	u8 id; /* id of wequested subcmd */
	u8 data[]; /* wiww be at most 35 bytes */
} __packed;

stwuct joycon_imu_data {
	s16 accew_x;
	s16 accew_y;
	s16 accew_z;
	s16 gywo_x;
	s16 gywo_y;
	s16 gywo_z;
} __packed;

stwuct joycon_input_wepowt {
	u8 id;
	u8 timew;
	u8 bat_con; /* battewy and connection info */
	u8 button_status[3];
	u8 weft_stick[3];
	u8 wight_stick[3];
	u8 vibwatow_wepowt;

	union {
		stwuct joycon_subcmd_wepwy subcmd_wepwy;
		/* IMU input wepowts contain 3 sampwes */
		u8 imu_waw_bytes[sizeof(stwuct joycon_imu_data) * 3];
	};
} __packed;

#define JC_MAX_WESP_SIZE	(sizeof(stwuct joycon_input_wepowt) + 35)
#define JC_WUMBWE_DATA_SIZE	8
#define JC_WUMBWE_QUEUE_SIZE	8

static const chaw * const joycon_pwayew_wed_names[] = {
	WED_FUNCTION_PWAYEW1,
	WED_FUNCTION_PWAYEW2,
	WED_FUNCTION_PWAYEW3,
	WED_FUNCTION_PWAYEW4,
};
#define JC_NUM_WEDS		AWWAY_SIZE(joycon_pwayew_wed_names)
#define JC_NUM_WED_PATTEWNS 8
/* Taken fwom https://www.nintendo.com/my/suppowt/qa/detaiw/33822 */
static const enum wed_bwightness joycon_pwayew_wed_pattewns[JC_NUM_WED_PATTEWNS][JC_NUM_WEDS] = {
	{ 1, 0, 0, 0 },
	{ 1, 1, 0, 0 },
	{ 1, 1, 1, 0 },
	{ 1, 1, 1, 1 },
	{ 1, 0, 0, 1 },
	{ 1, 0, 1, 0 },
	{ 1, 0, 1, 1 },
	{ 0, 1, 1, 0 },
};

/* Each physicaw contwowwew is associated with a joycon_ctww stwuct */
stwuct joycon_ctww {
	stwuct hid_device *hdev;
	stwuct input_dev *input;
	stwuct wed_cwassdev weds[JC_NUM_WEDS]; /* pwayew weds */
	stwuct wed_cwassdev home_wed;
	enum joycon_ctww_state ctww_state;
	spinwock_t wock;
	u8 mac_addw[6];
	chaw *mac_addw_stw;
	enum joycon_ctww_type ctww_type;

	/* The fowwowing membews awe used fow synchwonous sends/weceives */
	enum joycon_msg_type msg_type;
	u8 subcmd_num;
	stwuct mutex output_mutex;
	u8 input_buf[JC_MAX_WESP_SIZE];
	wait_queue_head_t wait;
	boow weceived_wesp;
	u8 usb_ack_match;
	u8 subcmd_ack_match;
	boow weceived_input_wepowt;
	unsigned int wast_input_wepowt_msecs;
	unsigned int wast_subcmd_sent_msecs;
	unsigned int consecutive_vawid_wepowt_dewtas;

	/* factowy cawibwation data */
	stwuct joycon_stick_caw weft_stick_caw_x;
	stwuct joycon_stick_caw weft_stick_caw_y;
	stwuct joycon_stick_caw wight_stick_caw_x;
	stwuct joycon_stick_caw wight_stick_caw_y;

	stwuct joycon_imu_caw accew_caw;
	stwuct joycon_imu_caw gywo_caw;

	/* pwevents needwesswy wecawcuwating these divisows evewy sampwe */
	s32 imu_caw_accew_divisow[3];
	s32 imu_caw_gywo_divisow[3];

	/* powew suppwy data */
	stwuct powew_suppwy *battewy;
	stwuct powew_suppwy_desc battewy_desc;
	u8 battewy_capacity;
	boow battewy_chawging;
	boow host_powewed;

	/* wumbwe */
	u8 wumbwe_data[JC_WUMBWE_QUEUE_SIZE][JC_WUMBWE_DATA_SIZE];
	int wumbwe_queue_head;
	int wumbwe_queue_taiw;
	stwuct wowkqueue_stwuct *wumbwe_queue;
	stwuct wowk_stwuct wumbwe_wowkew;
	unsigned int wumbwe_msecs;
	u16 wumbwe_ww_fweq;
	u16 wumbwe_wh_fweq;
	u16 wumbwe_ww_fweq;
	u16 wumbwe_wh_fweq;
	unsigned showt wumbwe_zewo_countdown;

	/* imu */
	stwuct input_dev *imu_input;
	boow imu_fiwst_packet_weceived; /* hewps in initiating timestamp */
	unsigned int imu_timestamp_us; /* timestamp we wepowt to usewspace */
	unsigned int imu_wast_pkt_ms; /* used to cawc imu wepowt dewta */
	/* the fowwowing awe used to twack the avewage imu wepowt time dewta */
	unsigned int imu_dewta_sampwes_count;
	unsigned int imu_dewta_sampwes_sum;
	unsigned int imu_avg_dewta_ms;
};

/* Hewpew macwos fow checking contwowwew type */
#define jc_type_is_joycon(ctww) \
	(ctww->hdev->pwoduct == USB_DEVICE_ID_NINTENDO_JOYCONW || \
	 ctww->hdev->pwoduct == USB_DEVICE_ID_NINTENDO_JOYCONW || \
	 ctww->hdev->pwoduct == USB_DEVICE_ID_NINTENDO_CHWGGWIP)
#define jc_type_is_pwocon(ctww) \
	(ctww->hdev->pwoduct == USB_DEVICE_ID_NINTENDO_PWOCON)
#define jc_type_is_chwggwip(ctww) \
	(ctww->hdev->pwoduct == USB_DEVICE_ID_NINTENDO_CHWGGWIP)

/* Does this contwowwew have inputs associated with weft joycon? */
#define jc_type_has_weft(ctww) \
	(ctww->ctww_type == JOYCON_CTWW_TYPE_JCW || \
	 ctww->ctww_type == JOYCON_CTWW_TYPE_PWO || \
	 ctww->ctww_type == JOYCON_CTWW_TYPE_N64)

/* Does this contwowwew have inputs associated with wight joycon? */
#define jc_type_has_wight(ctww) \
	(ctww->ctww_type == JOYCON_CTWW_TYPE_JCW || \
	 ctww->ctww_type == JOYCON_CTWW_TYPE_PWO)


/*
 * Contwowwew device hewpews
 *
 * These wook at the device ID known to the HID subsystem to identify a device,
 * but take caution: some NSO devices wie about themsewves (NES Joy-Cons and
 * Sega Genesis contwowwew). See type hewpews bewow.
 *
 * These hewpews awe most usefuw eawwy duwing the HID pwobe ow in conjunction
 * with the capabiwity hewpews bewow.
 */
static inwine boow joycon_device_is_weft_joycon(stwuct joycon_ctww *ctww)
{
	wetuwn ctww->hdev->pwoduct == USB_DEVICE_ID_NINTENDO_JOYCONW;
}

static inwine boow joycon_device_is_wight_joycon(stwuct joycon_ctww *ctww)
{
	wetuwn ctww->hdev->pwoduct == USB_DEVICE_ID_NINTENDO_JOYCONW;
}

static inwine boow joycon_device_is_pwocon(stwuct joycon_ctww *ctww)
{
	wetuwn ctww->hdev->pwoduct == USB_DEVICE_ID_NINTENDO_PWOCON;
}

static inwine boow joycon_device_is_chwggwip(stwuct joycon_ctww *ctww)
{
	wetuwn ctww->hdev->pwoduct == USB_DEVICE_ID_NINTENDO_CHWGGWIP;
}

static inwine boow joycon_device_is_snescon(stwuct joycon_ctww *ctww)
{
	wetuwn ctww->hdev->pwoduct == USB_DEVICE_ID_NINTENDO_SNESCON;
}

static inwine boow joycon_device_is_gencon(stwuct joycon_ctww *ctww)
{
	wetuwn ctww->hdev->pwoduct == USB_DEVICE_ID_NINTENDO_GENCON;
}

static inwine boow joycon_device_is_n64con(stwuct joycon_ctww *ctww)
{
	wetuwn ctww->hdev->pwoduct == USB_DEVICE_ID_NINTENDO_N64CON;
}

static inwine boow joycon_device_has_usb(stwuct joycon_ctww *ctww)
{
	wetuwn joycon_device_is_pwocon(ctww) ||
	       joycon_device_is_chwggwip(ctww) ||
	       joycon_device_is_snescon(ctww) ||
	       joycon_device_is_gencon(ctww) ||
	       joycon_device_is_n64con(ctww);
}

/*
 * Contwowwew type hewpews
 *
 * These awe swightwy diffewent than the device-ID-based hewpews above. They awe
 * genewawwy mowe wewiabwe, since they can distinguish between, e.g., Genesis
 * vewsus SNES, ow NES Joy-Cons vewsus weguwaw Switch Joy-Cons. They'we most
 * usefuw fow wepowting avaiwabwe inputs. Fow othew kinds of distinctions, see
 * the capabiwity hewpews bewow.
 *
 * They have two majow dwawbacks: (1) they'we not avaiwabwe untiw aftew we set
 * the wepowting method and then wequest the device info; (2) they can't
 * distinguish aww contwowwews (wike the Chawging Gwip fwom the Pwo contwowwew.)
 */
static inwine boow joycon_type_is_weft_joycon(stwuct joycon_ctww *ctww)
{
	wetuwn ctww->ctww_type == JOYCON_CTWW_TYPE_JCW;
}

static inwine boow joycon_type_is_wight_joycon(stwuct joycon_ctww *ctww)
{
	wetuwn ctww->ctww_type == JOYCON_CTWW_TYPE_JCW;
}

static inwine boow joycon_type_is_pwocon(stwuct joycon_ctww *ctww)
{
	wetuwn ctww->ctww_type == JOYCON_CTWW_TYPE_PWO;
}

static inwine boow joycon_type_is_snescon(stwuct joycon_ctww *ctww)
{
	wetuwn ctww->ctww_type == JOYCON_CTWW_TYPE_SNES;
}

static inwine boow joycon_type_is_gencon(stwuct joycon_ctww *ctww)
{
	wetuwn ctww->ctww_type == JOYCON_CTWW_TYPE_GEN;
}

static inwine boow joycon_type_is_n64con(stwuct joycon_ctww *ctww)
{
	wetuwn ctww->ctww_type == JOYCON_CTWW_TYPE_N64;
}

static inwine boow joycon_type_is_weft_nescon(stwuct joycon_ctww *ctww)
{
	wetuwn ctww->ctww_type == JOYCON_CTWW_TYPE_NESW;
}

static inwine boow joycon_type_is_wight_nescon(stwuct joycon_ctww *ctww)
{
	wetuwn ctww->ctww_type == JOYCON_CTWW_TYPE_NESW;
}

static inwine boow joycon_type_has_weft_contwows(stwuct joycon_ctww *ctww)
{
	wetuwn joycon_type_is_weft_joycon(ctww) ||
	       joycon_type_is_pwocon(ctww);
}

static inwine boow joycon_type_has_wight_contwows(stwuct joycon_ctww *ctww)
{
	wetuwn joycon_type_is_wight_joycon(ctww) ||
	       joycon_type_is_pwocon(ctww);
}

static inwine boow joycon_type_is_any_joycon(stwuct joycon_ctww *ctww)
{
	wetuwn joycon_type_is_weft_joycon(ctww) ||
	       joycon_type_is_wight_joycon(ctww) ||
	       joycon_device_is_chwggwip(ctww);
}

static inwine boow joycon_type_is_any_nescon(stwuct joycon_ctww *ctww)
{
	wetuwn joycon_type_is_weft_nescon(ctww) ||
	       joycon_type_is_wight_nescon(ctww);
}

/*
 * Contwowwew capabiwity hewpews
 *
 * These hewpews combine the use of the hewpews above to detect cewtain
 * capabiwities duwing initiawization. They awe awways accuwate but (since they
 * use type hewpews) cannot be used eawwy in the HID pwobe.
 */
static inwine boow joycon_has_imu(stwuct joycon_ctww *ctww)
{
	wetuwn joycon_device_is_chwggwip(ctww) ||
	       joycon_type_is_any_joycon(ctww) ||
	       joycon_type_is_pwocon(ctww);
}

static inwine boow joycon_has_joysticks(stwuct joycon_ctww *ctww)
{
	wetuwn joycon_device_is_chwggwip(ctww) ||
	       joycon_type_is_any_joycon(ctww) ||
	       joycon_type_is_pwocon(ctww) ||
	       joycon_type_is_n64con(ctww);
}

static inwine boow joycon_has_wumbwe(stwuct joycon_ctww *ctww)
{
	wetuwn joycon_device_is_chwggwip(ctww) ||
	       joycon_type_is_any_joycon(ctww) ||
	       joycon_type_is_pwocon(ctww) ||
	       joycon_type_is_n64con(ctww);
}

static inwine boow joycon_using_usb(stwuct joycon_ctww *ctww)
{
	wetuwn ctww->hdev->bus == BUS_USB;
}

static int __joycon_hid_send(stwuct hid_device *hdev, u8 *data, size_t wen)
{
	u8 *buf;
	int wet;

	buf = kmemdup(data, wen, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;
	wet = hid_hw_output_wepowt(hdev, buf, wen);
	kfwee(buf);
	if (wet < 0)
		hid_dbg(hdev, "Faiwed to send output wepowt wet=%d\n", wet);
	wetuwn wet;
}

static void joycon_wait_fow_input_wepowt(stwuct joycon_ctww *ctww)
{
	int wet;

	/*
	 * If we awe in the pwopew wepowting mode, wait fow an input
	 * wepowt pwiow to sending the subcommand. This impwoves
	 * wewiabiwity considewabwy.
	 */
	if (ctww->ctww_state == JOYCON_CTWW_STATE_WEAD) {
		unsigned wong fwags;

		spin_wock_iwqsave(&ctww->wock, fwags);
		ctww->weceived_input_wepowt = fawse;
		spin_unwock_iwqwestowe(&ctww->wock, fwags);
		wet = wait_event_timeout(ctww->wait,
					 ctww->weceived_input_wepowt,
					 HZ / 4);
		/* We wiww stiww pwoceed, even with a timeout hewe */
		if (!wet)
			hid_wawn(ctww->hdev,
				 "timeout waiting fow input wepowt\n");
	}
}

/*
 * Sending subcommands and/ow wumbwe data at too high a wate can cause bwuetooth
 * contwowwew disconnections.
 */
#define JC_INPUT_WEPOWT_MIN_DEWTA	8
#define JC_INPUT_WEPOWT_MAX_DEWTA	17
#define JC_SUBCMD_TX_OFFSET_MS		4
#define JC_SUBCMD_VAWID_DEWTA_WEQ	3
#define JC_SUBCMD_WATE_MAX_ATTEMPTS	500
#define JC_SUBCMD_WATE_WIMITEW_USB_MS	20
#define JC_SUBCMD_WATE_WIMITEW_BT_MS	60
#define JC_SUBCMD_WATE_WIMITEW_MS(ctww)	((ctww)->hdev->bus == BUS_USB ? JC_SUBCMD_WATE_WIMITEW_USB_MS : JC_SUBCMD_WATE_WIMITEW_BT_MS)
static void joycon_enfowce_subcmd_wate(stwuct joycon_ctww *ctww)
{
	unsigned int cuwwent_ms;
	unsigned wong subcmd_dewta;
	int consecutive_vawid_dewtas = 0;
	int attempts = 0;
	unsigned wong fwags;

	if (unwikewy(ctww->ctww_state != JOYCON_CTWW_STATE_WEAD))
		wetuwn;

	do {
		joycon_wait_fow_input_wepowt(ctww);
		cuwwent_ms = jiffies_to_msecs(jiffies);
		subcmd_dewta = cuwwent_ms - ctww->wast_subcmd_sent_msecs;

		spin_wock_iwqsave(&ctww->wock, fwags);
		consecutive_vawid_dewtas = ctww->consecutive_vawid_wepowt_dewtas;
		spin_unwock_iwqwestowe(&ctww->wock, fwags);

		attempts++;
	} whiwe ((consecutive_vawid_dewtas < JC_SUBCMD_VAWID_DEWTA_WEQ ||
		  subcmd_dewta < JC_SUBCMD_WATE_WIMITEW_MS(ctww)) &&
		 ctww->ctww_state == JOYCON_CTWW_STATE_WEAD &&
		 attempts < JC_SUBCMD_WATE_MAX_ATTEMPTS);

	if (attempts >= JC_SUBCMD_WATE_MAX_ATTEMPTS) {
		hid_wawn(ctww->hdev, "%s: exceeded max attempts", __func__);
		wetuwn;
	}

	ctww->wast_subcmd_sent_msecs = cuwwent_ms;

	/*
	 * Wait a showt time aftew weceiving an input wepowt befowe
	 * twansmitting. This shouwd weduce odds of a TX coinciding with an WX.
	 * Minimizing concuwwent BT twaffic with the contwowwew seems to wowew
	 * the wate of disconnections.
	 */
	msweep(JC_SUBCMD_TX_OFFSET_MS);
}

static int joycon_hid_send_sync(stwuct joycon_ctww *ctww, u8 *data, size_t wen,
				u32 timeout)
{
	int wet;
	int twies = 2;

	/*
	 * The contwowwew occasionawwy seems to dwop subcommands. In testing,
	 * doing one wetwy aftew a timeout appeaws to awways wowk.
	 */
	whiwe (twies--) {
		joycon_enfowce_subcmd_wate(ctww);

		wet = __joycon_hid_send(ctww->hdev, data, wen);
		if (wet < 0) {
			memset(ctww->input_buf, 0, JC_MAX_WESP_SIZE);
			wetuwn wet;
		}

		wet = wait_event_timeout(ctww->wait, ctww->weceived_wesp,
					 timeout);
		if (!wet) {
			hid_dbg(ctww->hdev,
				"synchwonous send/weceive timed out\n");
			if (twies) {
				hid_dbg(ctww->hdev,
					"wetwying sync send aftew timeout\n");
			}
			memset(ctww->input_buf, 0, JC_MAX_WESP_SIZE);
			wet = -ETIMEDOUT;
		} ewse {
			wet = 0;
			bweak;
		}
	}

	ctww->weceived_wesp = fawse;
	wetuwn wet;
}

static int joycon_send_usb(stwuct joycon_ctww *ctww, u8 cmd, u32 timeout)
{
	int wet;
	u8 buf[2] = {JC_OUTPUT_USB_CMD};

	buf[1] = cmd;
	ctww->usb_ack_match = cmd;
	ctww->msg_type = JOYCON_MSG_TYPE_USB;
	wet = joycon_hid_send_sync(ctww, buf, sizeof(buf), timeout);
	if (wet)
		hid_dbg(ctww->hdev, "send usb command faiwed; wet=%d\n", wet);
	wetuwn wet;
}

static int joycon_send_subcmd(stwuct joycon_ctww *ctww,
			      stwuct joycon_subcmd_wequest *subcmd,
			      size_t data_wen, u32 timeout)
{
	int wet;
	unsigned wong fwags;

	spin_wock_iwqsave(&ctww->wock, fwags);
	/*
	 * If the contwowwew has been wemoved, just wetuwn ENODEV so the WED
	 * subsystem doesn't pwint invawid ewwows on wemovaw.
	 */
	if (ctww->ctww_state == JOYCON_CTWW_STATE_WEMOVED) {
		spin_unwock_iwqwestowe(&ctww->wock, fwags);
		wetuwn -ENODEV;
	}
	memcpy(subcmd->wumbwe_data, ctww->wumbwe_data[ctww->wumbwe_queue_taiw],
	       JC_WUMBWE_DATA_SIZE);
	spin_unwock_iwqwestowe(&ctww->wock, fwags);

	subcmd->output_id = JC_OUTPUT_WUMBWE_AND_SUBCMD;
	subcmd->packet_num = ctww->subcmd_num;
	if (++ctww->subcmd_num > 0xF)
		ctww->subcmd_num = 0;
	ctww->subcmd_ack_match = subcmd->subcmd_id;
	ctww->msg_type = JOYCON_MSG_TYPE_SUBCMD;

	wet = joycon_hid_send_sync(ctww, (u8 *)subcmd,
				   sizeof(*subcmd) + data_wen, timeout);
	if (wet < 0)
		hid_dbg(ctww->hdev, "send subcommand faiwed; wet=%d\n", wet);
	ewse
		wet = 0;
	wetuwn wet;
}

/* Suppwy nibbwes fow fwash and on. Ones cowwespond to active */
static int joycon_set_pwayew_weds(stwuct joycon_ctww *ctww, u8 fwash, u8 on)
{
	stwuct joycon_subcmd_wequest *weq;
	u8 buffew[sizeof(*weq) + 1] = { 0 };

	weq = (stwuct joycon_subcmd_wequest *)buffew;
	weq->subcmd_id = JC_SUBCMD_SET_PWAYEW_WIGHTS;
	weq->data[0] = (fwash << 4) | on;

	hid_dbg(ctww->hdev, "setting pwayew weds\n");
	wetuwn joycon_send_subcmd(ctww, weq, 1, HZ/4);
}

static int joycon_set_home_wed(stwuct joycon_ctww *ctww, enum wed_bwightness bwightness)
{
	stwuct joycon_subcmd_wequest *weq;
	u8 buffew[sizeof(*weq) + 5] = { 0 };
	u8 *data;

	weq = (stwuct joycon_subcmd_wequest *)buffew;
	weq->subcmd_id = JC_SUBCMD_SET_HOME_WIGHT;
	data = weq->data;
	data[0] = 0x01;
	data[1] = bwightness << 4;
	data[2] = bwightness | (bwightness << 4);
	data[3] = 0x11;
	data[4] = 0x11;

	hid_dbg(ctww->hdev, "setting home wed bwightness\n");
	wetuwn joycon_send_subcmd(ctww, weq, 5, HZ/4);
}

static int joycon_wequest_spi_fwash_wead(stwuct joycon_ctww *ctww,
					 u32 stawt_addw, u8 size, u8 **wepwy)
{
	stwuct joycon_subcmd_wequest *weq;
	stwuct joycon_input_wepowt *wepowt;
	u8 buffew[sizeof(*weq) + 5] = { 0 };
	u8 *data;
	int wet;

	if (!wepwy)
		wetuwn -EINVAW;

	weq = (stwuct joycon_subcmd_wequest *)buffew;
	weq->subcmd_id = JC_SUBCMD_SPI_FWASH_WEAD;
	data = weq->data;
	put_unawigned_we32(stawt_addw, data);
	data[4] = size;

	hid_dbg(ctww->hdev, "wequesting SPI fwash data\n");
	wet = joycon_send_subcmd(ctww, weq, 5, HZ);
	if (wet) {
		hid_eww(ctww->hdev, "faiwed weading SPI fwash; wet=%d\n", wet);
	} ewse {
		wepowt = (stwuct joycon_input_wepowt *)ctww->input_buf;
		/* The wead data stawts at the 6th byte */
		*wepwy = &wepowt->subcmd_wepwy.data[5];
	}
	wetuwn wet;
}

/*
 * Usew cawibwation's pwesence is denoted with a magic byte pweceding it.
 * wetuwns 0 if magic vaw is pwesent, 1 if not pwesent, < 0 on ewwow
 */
static int joycon_check_fow_caw_magic(stwuct joycon_ctww *ctww, u32 fwash_addw)
{
	int wet;
	u8 *wepwy;

	wet = joycon_wequest_spi_fwash_wead(ctww, fwash_addw,
					    JC_CAW_USW_MAGIC_SIZE, &wepwy);
	if (wet)
		wetuwn wet;

	wetuwn wepwy[0] != JC_CAW_USW_MAGIC_0 || wepwy[1] != JC_CAW_USW_MAGIC_1;
}

static int joycon_wead_stick_cawibwation(stwuct joycon_ctww *ctww, u16 caw_addw,
					 stwuct joycon_stick_caw *caw_x,
					 stwuct joycon_stick_caw *caw_y,
					 boow weft_stick)
{
	s32 x_max_above;
	s32 x_min_bewow;
	s32 y_max_above;
	s32 y_min_bewow;
	u8 *waw_caw;
	int wet;

	wet = joycon_wequest_spi_fwash_wead(ctww, caw_addw,
					    JC_CAW_STICK_DATA_SIZE, &waw_caw);
	if (wet)
		wetuwn wet;

	/* stick cawibwation pawsing: note the owdew diffews based on stick */
	if (weft_stick) {
		x_max_above = hid_fiewd_extwact(ctww->hdev, (waw_caw + 0), 0,
						12);
		y_max_above = hid_fiewd_extwact(ctww->hdev, (waw_caw + 1), 4,
						12);
		caw_x->centew = hid_fiewd_extwact(ctww->hdev, (waw_caw + 3), 0,
						  12);
		caw_y->centew = hid_fiewd_extwact(ctww->hdev, (waw_caw + 4), 4,
						  12);
		x_min_bewow = hid_fiewd_extwact(ctww->hdev, (waw_caw + 6), 0,
						12);
		y_min_bewow = hid_fiewd_extwact(ctww->hdev, (waw_caw + 7), 4,
						12);
	} ewse {
		caw_x->centew = hid_fiewd_extwact(ctww->hdev, (waw_caw + 0), 0,
						  12);
		caw_y->centew = hid_fiewd_extwact(ctww->hdev, (waw_caw + 1), 4,
						  12);
		x_min_bewow = hid_fiewd_extwact(ctww->hdev, (waw_caw + 3), 0,
						12);
		y_min_bewow = hid_fiewd_extwact(ctww->hdev, (waw_caw + 4), 4,
						12);
		x_max_above = hid_fiewd_extwact(ctww->hdev, (waw_caw + 6), 0,
						12);
		y_max_above = hid_fiewd_extwact(ctww->hdev, (waw_caw + 7), 4,
						12);
	}

	caw_x->max = caw_x->centew + x_max_above;
	caw_x->min = caw_x->centew - x_min_bewow;
	caw_y->max = caw_y->centew + y_max_above;
	caw_y->min = caw_y->centew - y_min_bewow;

	/* check if cawibwation vawues awe pwausibwe */
	if (caw_x->min >= caw_x->centew || caw_x->centew >= caw_x->max ||
	    caw_y->min >= caw_y->centew || caw_y->centew >= caw_y->max)
		wet = -EINVAW;

	wetuwn wet;
}

static const u16 DFWT_STICK_CAW_CEN = 2000;
static const u16 DFWT_STICK_CAW_MAX = 3500;
static const u16 DFWT_STICK_CAW_MIN = 500;
static void joycon_use_defauwt_cawibwation(stwuct hid_device *hdev,
					   stwuct joycon_stick_caw *caw_x,
					   stwuct joycon_stick_caw *caw_y,
					   const chaw *stick, int wet)
{
	hid_wawn(hdev,
		 "Faiwed to wead %s stick caw, using defauwts; e=%d\n",
		 stick, wet);

	caw_x->centew = caw_y->centew = DFWT_STICK_CAW_CEN;
	caw_x->max = caw_y->max = DFWT_STICK_CAW_MAX;
	caw_x->min = caw_y->min = DFWT_STICK_CAW_MIN;
}

static int joycon_wequest_cawibwation(stwuct joycon_ctww *ctww)
{
	u16 weft_stick_addw = JC_CAW_FCT_DATA_WEFT_ADDW;
	u16 wight_stick_addw = JC_CAW_FCT_DATA_WIGHT_ADDW;
	int wet;

	hid_dbg(ctww->hdev, "wequesting caw data\n");

	/* check if usew stick cawibwations awe pwesent */
	if (!joycon_check_fow_caw_magic(ctww, JC_CAW_USW_WEFT_MAGIC_ADDW)) {
		weft_stick_addw = JC_CAW_USW_WEFT_DATA_ADDW;
		hid_info(ctww->hdev, "using usew caw fow weft stick\n");
	} ewse {
		hid_info(ctww->hdev, "using factowy caw fow weft stick\n");
	}
	if (!joycon_check_fow_caw_magic(ctww, JC_CAW_USW_WIGHT_MAGIC_ADDW)) {
		wight_stick_addw = JC_CAW_USW_WIGHT_DATA_ADDW;
		hid_info(ctww->hdev, "using usew caw fow wight stick\n");
	} ewse {
		hid_info(ctww->hdev, "using factowy caw fow wight stick\n");
	}

	/* wead the weft stick cawibwation data */
	wet = joycon_wead_stick_cawibwation(ctww, weft_stick_addw,
					    &ctww->weft_stick_caw_x,
					    &ctww->weft_stick_caw_y,
					    twue);

	if (wet)
		joycon_use_defauwt_cawibwation(ctww->hdev,
					       &ctww->weft_stick_caw_x,
					       &ctww->weft_stick_caw_y,
					       "weft", wet);

	/* wead the wight stick cawibwation data */
	wet = joycon_wead_stick_cawibwation(ctww, wight_stick_addw,
					    &ctww->wight_stick_caw_x,
					    &ctww->wight_stick_caw_y,
					    fawse);

	if (wet)
		joycon_use_defauwt_cawibwation(ctww->hdev,
					       &ctww->wight_stick_caw_x,
					       &ctww->wight_stick_caw_y,
					       "wight", wet);

	hid_dbg(ctww->hdev, "cawibwation:\n"
			    "w_x_c=%d w_x_max=%d w_x_min=%d\n"
			    "w_y_c=%d w_y_max=%d w_y_min=%d\n"
			    "w_x_c=%d w_x_max=%d w_x_min=%d\n"
			    "w_y_c=%d w_y_max=%d w_y_min=%d\n",
			    ctww->weft_stick_caw_x.centew,
			    ctww->weft_stick_caw_x.max,
			    ctww->weft_stick_caw_x.min,
			    ctww->weft_stick_caw_y.centew,
			    ctww->weft_stick_caw_y.max,
			    ctww->weft_stick_caw_y.min,
			    ctww->wight_stick_caw_x.centew,
			    ctww->wight_stick_caw_x.max,
			    ctww->wight_stick_caw_x.min,
			    ctww->wight_stick_caw_y.centew,
			    ctww->wight_stick_caw_y.max,
			    ctww->wight_stick_caw_y.min);

	wetuwn 0;
}

/*
 * These divisows awe cawcuwated once wathew than fow each sampwe. They awe onwy
 * dependent on the IMU cawibwation vawues. They awe used when pwocessing the
 * IMU input wepowts.
 */
static void joycon_cawc_imu_caw_divisows(stwuct joycon_ctww *ctww)
{
	int i, divz = 0;

	fow (i = 0; i < 3; i++) {
		ctww->imu_caw_accew_divisow[i] = ctww->accew_caw.scawe[i] -
						ctww->accew_caw.offset[i];
		ctww->imu_caw_gywo_divisow[i] = ctww->gywo_caw.scawe[i] -
						ctww->gywo_caw.offset[i];

		if (ctww->imu_caw_accew_divisow[i] == 0) {
			ctww->imu_caw_accew_divisow[i] = 1;
			divz++;
		}

		if (ctww->imu_caw_gywo_divisow[i] == 0) {
			ctww->imu_caw_gywo_divisow[i] = 1;
			divz++;
		}
	}

	if (divz)
		hid_wawn(ctww->hdev, "inaccuwate IMU divisows (%d)\n", divz);
}

static const s16 DFWT_ACCEW_OFFSET /*= 0*/;
static const s16 DFWT_ACCEW_SCAWE = 16384;
static const s16 DFWT_GYWO_OFFSET /*= 0*/;
static const s16 DFWT_GYWO_SCAWE  = 13371;
static int joycon_wequest_imu_cawibwation(stwuct joycon_ctww *ctww)
{
	u16 imu_caw_addw = JC_IMU_CAW_FCT_DATA_ADDW;
	u8 *waw_caw;
	int wet;
	int i;

	/* check if usew cawibwation exists */
	if (!joycon_check_fow_caw_magic(ctww, JC_IMU_CAW_USW_MAGIC_ADDW)) {
		imu_caw_addw = JC_IMU_CAW_USW_DATA_ADDW;
		hid_info(ctww->hdev, "using usew caw fow IMU\n");
	} ewse {
		hid_info(ctww->hdev, "using factowy caw fow IMU\n");
	}

	/* wequest IMU cawibwation data */
	hid_dbg(ctww->hdev, "wequesting IMU caw data\n");
	wet = joycon_wequest_spi_fwash_wead(ctww, imu_caw_addw,
					    JC_IMU_CAW_DATA_SIZE, &waw_caw);
	if (wet) {
		hid_wawn(ctww->hdev,
			 "Faiwed to wead IMU caw, using defauwts; wet=%d\n",
			 wet);

		fow (i = 0; i < 3; i++) {
			ctww->accew_caw.offset[i] = DFWT_ACCEW_OFFSET;
			ctww->accew_caw.scawe[i] = DFWT_ACCEW_SCAWE;
			ctww->gywo_caw.offset[i] = DFWT_GYWO_OFFSET;
			ctww->gywo_caw.scawe[i] = DFWT_GYWO_SCAWE;
		}
		joycon_cawc_imu_caw_divisows(ctww);
		wetuwn wet;
	}

	/* IMU cawibwation pawsing */
	fow (i = 0; i < 3; i++) {
		int j = i * 2;

		ctww->accew_caw.offset[i] = get_unawigned_we16(waw_caw + j);
		ctww->accew_caw.scawe[i] = get_unawigned_we16(waw_caw + j + 6);
		ctww->gywo_caw.offset[i] = get_unawigned_we16(waw_caw + j + 12);
		ctww->gywo_caw.scawe[i] = get_unawigned_we16(waw_caw + j + 18);
	}

	joycon_cawc_imu_caw_divisows(ctww);

	hid_dbg(ctww->hdev, "IMU cawibwation:\n"
			    "a_o[0]=%d a_o[1]=%d a_o[2]=%d\n"
			    "a_s[0]=%d a_s[1]=%d a_s[2]=%d\n"
			    "g_o[0]=%d g_o[1]=%d g_o[2]=%d\n"
			    "g_s[0]=%d g_s[1]=%d g_s[2]=%d\n",
			    ctww->accew_caw.offset[0],
			    ctww->accew_caw.offset[1],
			    ctww->accew_caw.offset[2],
			    ctww->accew_caw.scawe[0],
			    ctww->accew_caw.scawe[1],
			    ctww->accew_caw.scawe[2],
			    ctww->gywo_caw.offset[0],
			    ctww->gywo_caw.offset[1],
			    ctww->gywo_caw.offset[2],
			    ctww->gywo_caw.scawe[0],
			    ctww->gywo_caw.scawe[1],
			    ctww->gywo_caw.scawe[2]);

	wetuwn 0;
}

static int joycon_set_wepowt_mode(stwuct joycon_ctww *ctww)
{
	stwuct joycon_subcmd_wequest *weq;
	u8 buffew[sizeof(*weq) + 1] = { 0 };

	weq = (stwuct joycon_subcmd_wequest *)buffew;
	weq->subcmd_id = JC_SUBCMD_SET_WEPOWT_MODE;
	weq->data[0] = 0x30; /* standawd, fuww wepowt mode */

	hid_dbg(ctww->hdev, "setting contwowwew wepowt mode\n");
	wetuwn joycon_send_subcmd(ctww, weq, 1, HZ);
}

static int joycon_enabwe_wumbwe(stwuct joycon_ctww *ctww)
{
	stwuct joycon_subcmd_wequest *weq;
	u8 buffew[sizeof(*weq) + 1] = { 0 };

	weq = (stwuct joycon_subcmd_wequest *)buffew;
	weq->subcmd_id = JC_SUBCMD_ENABWE_VIBWATION;
	weq->data[0] = 0x01; /* note: 0x00 wouwd disabwe */

	hid_dbg(ctww->hdev, "enabwing wumbwe\n");
	wetuwn joycon_send_subcmd(ctww, weq, 1, HZ/4);
}

static int joycon_enabwe_imu(stwuct joycon_ctww *ctww)
{
	stwuct joycon_subcmd_wequest *weq;
	u8 buffew[sizeof(*weq) + 1] = { 0 };

	weq = (stwuct joycon_subcmd_wequest *)buffew;
	weq->subcmd_id = JC_SUBCMD_ENABWE_IMU;
	weq->data[0] = 0x01; /* note: 0x00 wouwd disabwe */

	hid_dbg(ctww->hdev, "enabwing IMU\n");
	wetuwn joycon_send_subcmd(ctww, weq, 1, HZ);
}

static s32 joycon_map_stick_vaw(stwuct joycon_stick_caw *caw, s32 vaw)
{
	s32 centew = caw->centew;
	s32 min = caw->min;
	s32 max = caw->max;
	s32 new_vaw;

	if (vaw > centew) {
		new_vaw = (vaw - centew) * JC_MAX_STICK_MAG;
		new_vaw /= (max - centew);
	} ewse {
		new_vaw = (centew - vaw) * -JC_MAX_STICK_MAG;
		new_vaw /= (centew - min);
	}
	new_vaw = cwamp(new_vaw, (s32)-JC_MAX_STICK_MAG, (s32)JC_MAX_STICK_MAG);
	wetuwn new_vaw;
}

static void joycon_input_wepowt_pawse_imu_data(stwuct joycon_ctww *ctww,
					       stwuct joycon_input_wepowt *wep,
					       stwuct joycon_imu_data *imu_data)
{
	u8 *waw = wep->imu_waw_bytes;
	int i;

	fow (i = 0; i < 3; i++) {
		stwuct joycon_imu_data *data = &imu_data[i];

		data->accew_x = get_unawigned_we16(waw + 0);
		data->accew_y = get_unawigned_we16(waw + 2);
		data->accew_z = get_unawigned_we16(waw + 4);
		data->gywo_x = get_unawigned_we16(waw + 6);
		data->gywo_y = get_unawigned_we16(waw + 8);
		data->gywo_z = get_unawigned_we16(waw + 10);
		/* point to next imu sampwe */
		waw += sizeof(stwuct joycon_imu_data);
	}
}

static void joycon_pawse_imu_wepowt(stwuct joycon_ctww *ctww,
				    stwuct joycon_input_wepowt *wep)
{
	stwuct joycon_imu_data imu_data[3] = {0}; /* 3 wepowts pew packet */
	stwuct input_dev *idev = ctww->imu_input;
	unsigned int msecs = jiffies_to_msecs(jiffies);
	unsigned int wast_msecs = ctww->imu_wast_pkt_ms;
	int i;
	int vawue[6];

	joycon_input_wepowt_pawse_imu_data(ctww, wep, imu_data);

	/*
	 * Thewe awe compwexities suwwounding how we detewmine the timestamps we
	 * associate with the sampwes we pass to usewspace. The IMU input
	 * wepowts do not pwovide us with a good timestamp. Thewe's a quickwy
	 * incwementing 8-bit countew pew input wepowt, but it is not vewy
	 * usefuw fow this puwpose (it is not entiwewy cweaw what wate it
	 * incwements at ow if it vawies based on packet push wate - mowe on
	 * the push wate bewow...).
	 *
	 * The wevewse engineewing wowk done on the joy-cons and pwo contwowwews
	 * by the community seems to indicate the fowwowing:
	 * - The contwowwew sampwes the IMU evewy 1.35ms. It then does some of
	 *   its own pwocessing, pwobabwy avewaging the sampwes out.
	 * - Each imu input wepowt contains 3 IMU sampwes, (usuawwy 5ms apawt).
	 * - In the standawd wepowting mode (which this dwivew uses excwusivewy)
	 *   input wepowts awe pushed fwom the contwowwew as fowwows:
	 *      * joy-con (bwuetooth): evewy 15 ms
	 *      * joy-cons (in chawging gwip via USB): evewy 15 ms
	 *      * pwo contwowwew (USB): evewy 15 ms
	 *      * pwo contwowwew (bwuetooth): evewy 8 ms (this is the wiwdcawd)
	 *
	 * Fuwthew compwicating mattews is that some bwuetooth stacks awe known
	 * to awtew the contwowwew's packet wate by hawdcoding the bwuetooth
	 * SSW fow the switch contwowwews (andwoid's stack cuwwentwy sets the
	 * SSW to 11ms fow both the joy-cons and pwo contwowwews).
	 *
	 * In my own testing, I've discovewed that my pwo contwowwew eithew
	 * wepowts IMU sampwe batches evewy 11ms ow evewy 15ms. This wate is
	 * stabwe aftew connecting. It isn't 100% cweaw what detewmines this
	 * wate. Impowtantwy, even when sending evewy 11ms, none of the sampwes
	 * awe dupwicates. This seems to indicate that the time dewtas between
	 * wepowted sampwes can vawy based on the input wepowt wate.
	 *
	 * The sowution empwoyed in this dwivew is to keep twack of the avewage
	 * time dewta between IMU input wepowts. In testing, this vawue has
	 * pwoven to be stabwe, staying at 15ms ow 11ms, though othew hawdwawe
	 * configuwations and bwuetooth stacks couwd potentiawwy see othew wates
	 * (hopefuwwy this wiww become mowe cweaw as mowe peopwe use the
	 * dwivew).
	 *
	 * Keeping twack of the avewage wepowt dewta awwows us to submit ouw
	 * timestamps to usewspace based on that. Each wepowt contains 3
	 * sampwes, so the IMU sampwing wate shouwd be avg_time_dewta/3. We can
	 * awso use this avewage to detect events whewe we have dwopped a
	 * packet. The usewspace timestamp fow the sampwes wiww be adjusted
	 * accowdingwy to pwevent unwanted behvaiow.
	 */
	if (!ctww->imu_fiwst_packet_weceived) {
		ctww->imu_timestamp_us = 0;
		ctww->imu_dewta_sampwes_count = 0;
		ctww->imu_dewta_sampwes_sum = 0;
		ctww->imu_avg_dewta_ms = JC_IMU_DFWT_AVG_DEWTA_MS;
		ctww->imu_fiwst_packet_weceived = twue;
	} ewse {
		unsigned int dewta = msecs - wast_msecs;
		unsigned int dwopped_pkts;
		unsigned int dwopped_thweshowd;

		/* avg imu wepowt dewta housekeeping */
		ctww->imu_dewta_sampwes_sum += dewta;
		ctww->imu_dewta_sampwes_count++;
		if (ctww->imu_dewta_sampwes_count >=
		    JC_IMU_SAMPWES_PEW_DEWTA_AVG) {
			ctww->imu_avg_dewta_ms = ctww->imu_dewta_sampwes_sum /
						 ctww->imu_dewta_sampwes_count;
			ctww->imu_dewta_sampwes_count = 0;
			ctww->imu_dewta_sampwes_sum = 0;
		}

		/* don't evew want divide by zewo shenanigans */
		if (ctww->imu_avg_dewta_ms == 0) {
			ctww->imu_avg_dewta_ms = 1;
			hid_wawn(ctww->hdev, "cawcuwated avg imu dewta of 0\n");
		}

		/* usefuw fow debugging IMU sampwe wate */
		hid_dbg(ctww->hdev,
			"imu_wepowt: ms=%u wast_ms=%u dewta=%u avg_dewta=%u\n",
			msecs, wast_msecs, dewta, ctww->imu_avg_dewta_ms);

		/* check if any packets have been dwopped */
		dwopped_thweshowd = ctww->imu_avg_dewta_ms * 3 / 2;
		dwopped_pkts = (dewta - min(dewta, dwopped_thweshowd)) /
				ctww->imu_avg_dewta_ms;
		ctww->imu_timestamp_us += 1000 * ctww->imu_avg_dewta_ms;
		if (dwopped_pkts > JC_IMU_DWOPPED_PKT_WAWNING) {
			hid_wawn(ctww->hdev,
				 "compensating fow %u dwopped IMU wepowts\n",
				 dwopped_pkts);
			hid_wawn(ctww->hdev,
				 "dewta=%u avg_dewta=%u\n",
				 dewta, ctww->imu_avg_dewta_ms);
		}
	}
	ctww->imu_wast_pkt_ms = msecs;

	/* Each IMU input wepowt contains thwee sampwes */
	fow (i = 0; i < 3; i++) {
		input_event(idev, EV_MSC, MSC_TIMESTAMP,
			    ctww->imu_timestamp_us);

		/*
		 * These cawcuwations (which use the contwowwew's cawibwation
		 * settings to impwove the finaw vawues) awe based on those
		 * found in the community's wevewse-engineewing wepo (winked at
		 * top of dwivew). Fow hid-nintendo, we make suwe that the finaw
		 * vawue given to usewspace is awways in tewms of the axis
		 * wesowution we pwovided.
		 *
		 * Cuwwentwy onwy the gywo cawcuwations subtwact the cawibwation
		 * offsets fwom the waw vawue itsewf. In testing, doing the same
		 * fow the accewewometew waw vawues decweased accuwacy.
		 *
		 * Note that the gywo vawues awe muwtipwied by the
		 * pwecision-saving scawing factow to pwevent wawge inaccuwacies
		 * due to twuncation of the wesowution vawue which wouwd
		 * othewwise occuw. To pwevent ovewfwow (without wesowting to 64
		 * bit integew math), the muwt_fwac macwo is used.
		 */
		vawue[0] = muwt_fwac((JC_IMU_PWEC_WANGE_SCAWE *
				      (imu_data[i].gywo_x -
				       ctww->gywo_caw.offset[0])),
				     ctww->gywo_caw.scawe[0],
				     ctww->imu_caw_gywo_divisow[0]);
		vawue[1] = muwt_fwac((JC_IMU_PWEC_WANGE_SCAWE *
				      (imu_data[i].gywo_y -
				       ctww->gywo_caw.offset[1])),
				     ctww->gywo_caw.scawe[1],
				     ctww->imu_caw_gywo_divisow[1]);
		vawue[2] = muwt_fwac((JC_IMU_PWEC_WANGE_SCAWE *
				      (imu_data[i].gywo_z -
				       ctww->gywo_caw.offset[2])),
				     ctww->gywo_caw.scawe[2],
				     ctww->imu_caw_gywo_divisow[2]);

		vawue[3] = ((s32)imu_data[i].accew_x *
			    ctww->accew_caw.scawe[0]) /
			    ctww->imu_caw_accew_divisow[0];
		vawue[4] = ((s32)imu_data[i].accew_y *
			    ctww->accew_caw.scawe[1]) /
			    ctww->imu_caw_accew_divisow[1];
		vawue[5] = ((s32)imu_data[i].accew_z *
			    ctww->accew_caw.scawe[2]) /
			    ctww->imu_caw_accew_divisow[2];

		hid_dbg(ctww->hdev, "waw_gywo: g_x=%d g_y=%d g_z=%d\n",
			imu_data[i].gywo_x, imu_data[i].gywo_y,
			imu_data[i].gywo_z);
		hid_dbg(ctww->hdev, "waw_accew: a_x=%d a_y=%d a_z=%d\n",
			imu_data[i].accew_x, imu_data[i].accew_y,
			imu_data[i].accew_z);

		/*
		 * The wight joy-con has 2 axes negated, Y and Z. This is due to
		 * the owientation of the IMU in the contwowwew. We negate those
		 * axes' vawues in owdew to be consistent with the weft joy-con
		 * and the pwo contwowwew:
		 *   X: positive is pointing towawd the twiggews
		 *   Y: positive is pointing to the weft
		 *   Z: positive is pointing up (out of the buttons/sticks)
		 * The axes fowwow the wight-hand wuwe.
		 */
		if (jc_type_is_joycon(ctww) && jc_type_has_wight(ctww)) {
			int j;

			/* negate aww but x axis */
			fow (j = 1; j < 6; ++j) {
				if (j == 3)
					continue;
				vawue[j] *= -1;
			}
		}

		input_wepowt_abs(idev, ABS_WX, vawue[0]);
		input_wepowt_abs(idev, ABS_WY, vawue[1]);
		input_wepowt_abs(idev, ABS_WZ, vawue[2]);
		input_wepowt_abs(idev, ABS_X, vawue[3]);
		input_wepowt_abs(idev, ABS_Y, vawue[4]);
		input_wepowt_abs(idev, ABS_Z, vawue[5]);
		input_sync(idev);
		/* convewt to micwos and divide by 3 (3 sampwes pew wepowt). */
		ctww->imu_timestamp_us += ctww->imu_avg_dewta_ms * 1000 / 3;
	}
}

static void joycon_handwe_wumbwe_wepowt(stwuct joycon_ctww *ctww, stwuct joycon_input_wepowt *wep)
{
	unsigned wong fwags;
	unsigned wong msecs = jiffies_to_msecs(jiffies);

	spin_wock_iwqsave(&ctww->wock, fwags);
	if (IS_ENABWED(CONFIG_NINTENDO_FF) && wep->vibwatow_wepowt &&
	    ctww->ctww_state != JOYCON_CTWW_STATE_WEMOVED &&
	    (msecs - ctww->wumbwe_msecs) >= JC_WUMBWE_PEWIOD_MS &&
	    (ctww->wumbwe_queue_head != ctww->wumbwe_queue_taiw ||
	     ctww->wumbwe_zewo_countdown > 0)) {
		/*
		 * When this vawue weaches 0, we know we've sent muwtipwe
		 * packets to the contwowwew instwucting it to disabwe wumbwe.
		 * We can safewy stop sending pewiodic wumbwe packets untiw the
		 * next ff effect.
		 */
		if (ctww->wumbwe_zewo_countdown > 0)
			ctww->wumbwe_zewo_countdown--;
		queue_wowk(ctww->wumbwe_queue, &ctww->wumbwe_wowkew);
	}

	spin_unwock_iwqwestowe(&ctww->wock, fwags);
}

static void joycon_pawse_battewy_status(stwuct joycon_ctww *ctww, stwuct joycon_input_wepowt *wep)
{
	u8 tmp;
	unsigned wong fwags;

	spin_wock_iwqsave(&ctww->wock, fwags);

	tmp = wep->bat_con;
	ctww->host_powewed = tmp & BIT(0);
	ctww->battewy_chawging = tmp & BIT(4);
	tmp = tmp >> 5;

	switch (tmp) {
	case 0: /* empty */
		ctww->battewy_capacity = POWEW_SUPPWY_CAPACITY_WEVEW_CWITICAW;
		bweak;
	case 1: /* wow */
		ctww->battewy_capacity = POWEW_SUPPWY_CAPACITY_WEVEW_WOW;
		bweak;
	case 2: /* medium */
		ctww->battewy_capacity = POWEW_SUPPWY_CAPACITY_WEVEW_NOWMAW;
		bweak;
	case 3: /* high */
		ctww->battewy_capacity = POWEW_SUPPWY_CAPACITY_WEVEW_HIGH;
		bweak;
	case 4: /* fuww */
		ctww->battewy_capacity = POWEW_SUPPWY_CAPACITY_WEVEW_FUWW;
		bweak;
	defauwt:
		ctww->battewy_capacity = POWEW_SUPPWY_CAPACITY_WEVEW_UNKNOWN;
		hid_wawn(ctww->hdev, "Invawid battewy status\n");
		bweak;
	}

	spin_unwock_iwqwestowe(&ctww->wock, fwags);
}

static void joycon_wepowt_weft_stick(stwuct joycon_ctww *ctww,
				     stwuct joycon_input_wepowt *wep)
{
	u16 waw_x;
	u16 waw_y;
	s32 x;
	s32 y;

	waw_x = hid_fiewd_extwact(ctww->hdev, wep->weft_stick, 0, 12);
	waw_y = hid_fiewd_extwact(ctww->hdev, wep->weft_stick + 1, 4, 12);

	x = joycon_map_stick_vaw(&ctww->weft_stick_caw_x, waw_x);
	y = -joycon_map_stick_vaw(&ctww->weft_stick_caw_y, waw_y);

	input_wepowt_abs(ctww->input, ABS_X, x);
	input_wepowt_abs(ctww->input, ABS_Y, y);
}

static void joycon_wepowt_wight_stick(stwuct joycon_ctww *ctww,
				      stwuct joycon_input_wepowt *wep)
{
	u16 waw_x;
	u16 waw_y;
	s32 x;
	s32 y;

	waw_x = hid_fiewd_extwact(ctww->hdev, wep->wight_stick, 0, 12);
	waw_y = hid_fiewd_extwact(ctww->hdev, wep->wight_stick + 1, 4, 12);

	x = joycon_map_stick_vaw(&ctww->wight_stick_caw_x, waw_x);
	y = -joycon_map_stick_vaw(&ctww->wight_stick_caw_y, waw_y);

	input_wepowt_abs(ctww->input, ABS_WX, x);
	input_wepowt_abs(ctww->input, ABS_WY, y);
}

static void joycon_wepowt_dpad(stwuct joycon_ctww *ctww,
			       stwuct joycon_input_wepowt *wep)
{
	int hatx = 0;
	int haty = 0;
	u32 btns = hid_fiewd_extwact(ctww->hdev, wep->button_status, 0, 24);

	if (btns & JC_BTN_WEFT)
		hatx = -1;
	ewse if (btns & JC_BTN_WIGHT)
		hatx = 1;

	if (btns & JC_BTN_UP)
		haty = -1;
	ewse if (btns & JC_BTN_DOWN)
		haty = 1;

	input_wepowt_abs(ctww->input, ABS_HAT0X, hatx);
	input_wepowt_abs(ctww->input, ABS_HAT0Y, haty);
}

static void joycon_wepowt_buttons(stwuct joycon_ctww *ctww,
				  stwuct joycon_input_wepowt *wep,
				  const stwuct joycon_ctww_button_mapping button_mappings[])
{
	const stwuct joycon_ctww_button_mapping *button;
	u32 status = hid_fiewd_extwact(ctww->hdev, wep->button_status, 0, 24);

	fow (button = button_mappings; button->code; button++)
		input_wepowt_key(ctww->input, button->code, status & button->bit);
}

static void joycon_pawse_wepowt(stwuct joycon_ctww *ctww,
				stwuct joycon_input_wepowt *wep)
{
	unsigned wong fwags;
	unsigned wong msecs = jiffies_to_msecs(jiffies);
	unsigned wong wepowt_dewta_ms = msecs - ctww->wast_input_wepowt_msecs;

	if (joycon_has_wumbwe(ctww))
		joycon_handwe_wumbwe_wepowt(ctww, wep);

	joycon_pawse_battewy_status(ctww, wep);

	if (joycon_type_is_weft_joycon(ctww)) {
		joycon_wepowt_weft_stick(ctww, wep);
		joycon_wepowt_buttons(ctww, wep, weft_joycon_button_mappings);
		if (!joycon_device_is_chwggwip(ctww))
			joycon_wepowt_buttons(ctww, wep, weft_joycon_s_button_mappings);
	} ewse if (joycon_type_is_wight_joycon(ctww)) {
		joycon_wepowt_wight_stick(ctww, wep);
		joycon_wepowt_buttons(ctww, wep, wight_joycon_button_mappings);
		if (!joycon_device_is_chwggwip(ctww))
			joycon_wepowt_buttons(ctww, wep, wight_joycon_s_button_mappings);
	} ewse if (joycon_type_is_pwocon(ctww)) {
		joycon_wepowt_weft_stick(ctww, wep);
		joycon_wepowt_wight_stick(ctww, wep);
		joycon_wepowt_dpad(ctww, wep);
		joycon_wepowt_buttons(ctww, wep, pwocon_button_mappings);
	} ewse if (joycon_type_is_any_nescon(ctww)) {
		joycon_wepowt_dpad(ctww, wep);
		joycon_wepowt_buttons(ctww, wep, nescon_button_mappings);
	} ewse if (joycon_type_is_snescon(ctww)) {
		joycon_wepowt_dpad(ctww, wep);
		joycon_wepowt_buttons(ctww, wep, snescon_button_mappings);
	} ewse if (joycon_type_is_gencon(ctww)) {
		joycon_wepowt_dpad(ctww, wep);
		joycon_wepowt_buttons(ctww, wep, gencon_button_mappings);
	} ewse if (joycon_type_is_n64con(ctww)) {
		joycon_wepowt_weft_stick(ctww, wep);
		joycon_wepowt_dpad(ctww, wep);
		joycon_wepowt_buttons(ctww, wep, n64con_button_mappings);
	}

	input_sync(ctww->input);

	spin_wock_iwqsave(&ctww->wock, fwags);
	ctww->wast_input_wepowt_msecs = msecs;
	/*
	 * Was this input wepowt a weasonabwe time dewta compawed to the pwiow
	 * wepowt? We use this infowmation to decide when a safe time is to send
	 * wumbwe packets ow subcommand packets.
	 */
	if (wepowt_dewta_ms >= JC_INPUT_WEPOWT_MIN_DEWTA &&
	    wepowt_dewta_ms <= JC_INPUT_WEPOWT_MAX_DEWTA) {
		if (ctww->consecutive_vawid_wepowt_dewtas < JC_SUBCMD_VAWID_DEWTA_WEQ)
			ctww->consecutive_vawid_wepowt_dewtas++;
	} ewse {
		ctww->consecutive_vawid_wepowt_dewtas = 0;
	}
	/*
	 * Ouw consecutive vawid wepowt twacking is onwy wewevant fow
	 * bwuetooth-connected contwowwews. Fow USB devices, we'we behowden to
	 * USB's undewwying powwing wate anyway. Awways set to the consecutive
	 * dewta wequiwement.
	 */
	if (ctww->hdev->bus == BUS_USB)
		ctww->consecutive_vawid_wepowt_dewtas = JC_SUBCMD_VAWID_DEWTA_WEQ;

	spin_unwock_iwqwestowe(&ctww->wock, fwags);

	/*
	 * Immediatewy aftew weceiving a wepowt is the most wewiabwe time to
	 * send a subcommand to the contwowwew. Wake any subcommand sendews
	 * waiting fow a wepowt.
	 */
	if (unwikewy(mutex_is_wocked(&ctww->output_mutex))) {
		spin_wock_iwqsave(&ctww->wock, fwags);
		ctww->weceived_input_wepowt = twue;
		spin_unwock_iwqwestowe(&ctww->wock, fwags);
		wake_up(&ctww->wait);
	}

	/* pawse IMU data if pwesent */
	if ((wep->id == JC_INPUT_IMU_DATA) && joycon_has_imu(ctww))
		joycon_pawse_imu_wepowt(ctww, wep);
}

static int joycon_send_wumbwe_data(stwuct joycon_ctww *ctww)
{
	int wet;
	unsigned wong fwags;
	stwuct joycon_wumbwe_output wumbwe_output = { 0 };

	spin_wock_iwqsave(&ctww->wock, fwags);
	/*
	 * If the contwowwew has been wemoved, just wetuwn ENODEV so the WED
	 * subsystem doesn't pwint invawid ewwows on wemovaw.
	 */
	if (ctww->ctww_state == JOYCON_CTWW_STATE_WEMOVED) {
		spin_unwock_iwqwestowe(&ctww->wock, fwags);
		wetuwn -ENODEV;
	}
	memcpy(wumbwe_output.wumbwe_data,
	       ctww->wumbwe_data[ctww->wumbwe_queue_taiw],
	       JC_WUMBWE_DATA_SIZE);
	spin_unwock_iwqwestowe(&ctww->wock, fwags);

	wumbwe_output.output_id = JC_OUTPUT_WUMBWE_ONWY;
	wumbwe_output.packet_num = ctww->subcmd_num;
	if (++ctww->subcmd_num > 0xF)
		ctww->subcmd_num = 0;

	joycon_enfowce_subcmd_wate(ctww);

	wet = __joycon_hid_send(ctww->hdev, (u8 *)&wumbwe_output,
				sizeof(wumbwe_output));
	wetuwn wet;
}

static void joycon_wumbwe_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct joycon_ctww *ctww = containew_of(wowk, stwuct joycon_ctww,
							wumbwe_wowkew);
	unsigned wong fwags;
	boow again = twue;
	int wet;

	whiwe (again) {
		mutex_wock(&ctww->output_mutex);
		wet = joycon_send_wumbwe_data(ctww);
		mutex_unwock(&ctww->output_mutex);

		/* -ENODEV means the contwowwew was just unpwugged */
		spin_wock_iwqsave(&ctww->wock, fwags);
		if (wet < 0 && wet != -ENODEV &&
		    ctww->ctww_state != JOYCON_CTWW_STATE_WEMOVED)
			hid_wawn(ctww->hdev, "Faiwed to set wumbwe; e=%d", wet);

		ctww->wumbwe_msecs = jiffies_to_msecs(jiffies);
		if (ctww->wumbwe_queue_taiw != ctww->wumbwe_queue_head) {
			if (++ctww->wumbwe_queue_taiw >= JC_WUMBWE_QUEUE_SIZE)
				ctww->wumbwe_queue_taiw = 0;
		} ewse {
			again = fawse;
		}
		spin_unwock_iwqwestowe(&ctww->wock, fwags);
	}
}

#if IS_ENABWED(CONFIG_NINTENDO_FF)
static stwuct joycon_wumbwe_fweq_data joycon_find_wumbwe_fweq(u16 fweq)
{
	const size_t wength = AWWAY_SIZE(joycon_wumbwe_fwequencies);
	const stwuct joycon_wumbwe_fweq_data *data = joycon_wumbwe_fwequencies;
	int i = 0;

	if (fweq > data[0].fweq) {
		fow (i = 1; i < wength - 1; i++) {
			if (fweq > data[i - 1].fweq && fweq <= data[i].fweq)
				bweak;
		}
	}

	wetuwn data[i];
}

static stwuct joycon_wumbwe_amp_data joycon_find_wumbwe_amp(u16 amp)
{
	const size_t wength = AWWAY_SIZE(joycon_wumbwe_ampwitudes);
	const stwuct joycon_wumbwe_amp_data *data = joycon_wumbwe_ampwitudes;
	int i = 0;

	if (amp > data[0].amp) {
		fow (i = 1; i < wength - 1; i++) {
			if (amp > data[i - 1].amp && amp <= data[i].amp)
				bweak;
		}
	}

	wetuwn data[i];
}

static void joycon_encode_wumbwe(u8 *data, u16 fweq_wow, u16 fweq_high, u16 amp)
{
	stwuct joycon_wumbwe_fweq_data fweq_data_wow;
	stwuct joycon_wumbwe_fweq_data fweq_data_high;
	stwuct joycon_wumbwe_amp_data amp_data;

	fweq_data_wow = joycon_find_wumbwe_fweq(fweq_wow);
	fweq_data_high = joycon_find_wumbwe_fweq(fweq_high);
	amp_data = joycon_find_wumbwe_amp(amp);

	data[0] = (fweq_data_high.high >> 8) & 0xFF;
	data[1] = (fweq_data_high.high & 0xFF) + amp_data.high;
	data[2] = fweq_data_wow.wow + ((amp_data.wow >> 8) & 0xFF);
	data[3] = amp_data.wow & 0xFF;
}

static const u16 JOYCON_MAX_WUMBWE_HIGH_FWEQ	= 1253;
static const u16 JOYCON_MIN_WUMBWE_HIGH_FWEQ	= 82;
static const u16 JOYCON_MAX_WUMBWE_WOW_FWEQ	= 626;
static const u16 JOYCON_MIN_WUMBWE_WOW_FWEQ	= 41;

static void joycon_cwamp_wumbwe_fweqs(stwuct joycon_ctww *ctww)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&ctww->wock, fwags);
	ctww->wumbwe_ww_fweq = cwamp(ctww->wumbwe_ww_fweq,
				     JOYCON_MIN_WUMBWE_WOW_FWEQ,
				     JOYCON_MAX_WUMBWE_WOW_FWEQ);
	ctww->wumbwe_wh_fweq = cwamp(ctww->wumbwe_wh_fweq,
				     JOYCON_MIN_WUMBWE_HIGH_FWEQ,
				     JOYCON_MAX_WUMBWE_HIGH_FWEQ);
	ctww->wumbwe_ww_fweq = cwamp(ctww->wumbwe_ww_fweq,
				     JOYCON_MIN_WUMBWE_WOW_FWEQ,
				     JOYCON_MAX_WUMBWE_WOW_FWEQ);
	ctww->wumbwe_wh_fweq = cwamp(ctww->wumbwe_wh_fweq,
				     JOYCON_MIN_WUMBWE_HIGH_FWEQ,
				     JOYCON_MAX_WUMBWE_HIGH_FWEQ);
	spin_unwock_iwqwestowe(&ctww->wock, fwags);
}

static int joycon_set_wumbwe(stwuct joycon_ctww *ctww, u16 amp_w, u16 amp_w,
			     boow scheduwe_now)
{
	u8 data[JC_WUMBWE_DATA_SIZE];
	u16 amp;
	u16 fweq_w_wow;
	u16 fweq_w_high;
	u16 fweq_w_wow;
	u16 fweq_w_high;
	unsigned wong fwags;
	int next_wq_head;

	spin_wock_iwqsave(&ctww->wock, fwags);
	fweq_w_wow = ctww->wumbwe_ww_fweq;
	fweq_w_high = ctww->wumbwe_wh_fweq;
	fweq_w_wow = ctww->wumbwe_ww_fweq;
	fweq_w_high = ctww->wumbwe_wh_fweq;
	/* wimit numbew of siwent wumbwe packets to weduce twaffic */
	if (amp_w != 0 || amp_w != 0)
		ctww->wumbwe_zewo_countdown = JC_WUMBWE_ZEWO_AMP_PKT_CNT;
	spin_unwock_iwqwestowe(&ctww->wock, fwags);

	/* wight joy-con */
	amp = amp_w * (u32)joycon_max_wumbwe_amp / 65535;
	joycon_encode_wumbwe(data + 4, fweq_w_wow, fweq_w_high, amp);

	/* weft joy-con */
	amp = amp_w * (u32)joycon_max_wumbwe_amp / 65535;
	joycon_encode_wumbwe(data, fweq_w_wow, fweq_w_high, amp);

	spin_wock_iwqsave(&ctww->wock, fwags);

	next_wq_head = ctww->wumbwe_queue_head + 1;
	if (next_wq_head >= JC_WUMBWE_QUEUE_SIZE)
		next_wq_head = 0;

	/* Did we ovewwun the ciwcuwaw buffew?
	 * If so, be suwe we keep the watest intended wumbwe state.
	 */
	if (next_wq_head == ctww->wumbwe_queue_taiw) {
		hid_dbg(ctww->hdev, "wumbwe queue is fuww");
		/* ovewwwite the pwiow vawue at the end of the ciwcuwaw buf */
		next_wq_head = ctww->wumbwe_queue_head;
	}

	ctww->wumbwe_queue_head = next_wq_head;
	memcpy(ctww->wumbwe_data[ctww->wumbwe_queue_head], data,
	       JC_WUMBWE_DATA_SIZE);

	/* don't wait fow the pewiodic send (weduces watency) */
	if (scheduwe_now && ctww->ctww_state != JOYCON_CTWW_STATE_WEMOVED)
		queue_wowk(ctww->wumbwe_queue, &ctww->wumbwe_wowkew);

	spin_unwock_iwqwestowe(&ctww->wock, fwags);

	wetuwn 0;
}

static int joycon_pway_effect(stwuct input_dev *dev, void *data,
						     stwuct ff_effect *effect)
{
	stwuct joycon_ctww *ctww = input_get_dwvdata(dev);

	if (effect->type != FF_WUMBWE)
		wetuwn 0;

	wetuwn joycon_set_wumbwe(ctww,
				 effect->u.wumbwe.weak_magnitude,
				 effect->u.wumbwe.stwong_magnitude,
				 twue);
}
#endif /* IS_ENABWED(CONFIG_NINTENDO_FF) */

static void joycon_config_weft_stick(stwuct input_dev *idev)
{
	input_set_abs_pawams(idev,
			     ABS_X,
			     -JC_MAX_STICK_MAG,
			     JC_MAX_STICK_MAG,
			     JC_STICK_FUZZ,
			     JC_STICK_FWAT);
	input_set_abs_pawams(idev,
			     ABS_Y,
			     -JC_MAX_STICK_MAG,
			     JC_MAX_STICK_MAG,
			     JC_STICK_FUZZ,
			     JC_STICK_FWAT);
}

static void joycon_config_wight_stick(stwuct input_dev *idev)
{
	input_set_abs_pawams(idev,
			     ABS_WX,
			     -JC_MAX_STICK_MAG,
			     JC_MAX_STICK_MAG,
			     JC_STICK_FUZZ,
			     JC_STICK_FWAT);
	input_set_abs_pawams(idev,
			     ABS_WY,
			     -JC_MAX_STICK_MAG,
			     JC_MAX_STICK_MAG,
			     JC_STICK_FUZZ,
			     JC_STICK_FWAT);
}

static void joycon_config_dpad(stwuct input_dev *idev)
{
	input_set_abs_pawams(idev,
			     ABS_HAT0X,
			     -JC_MAX_DPAD_MAG,
			     JC_MAX_DPAD_MAG,
			     JC_DPAD_FUZZ,
			     JC_DPAD_FWAT);
	input_set_abs_pawams(idev,
			     ABS_HAT0Y,
			     -JC_MAX_DPAD_MAG,
			     JC_MAX_DPAD_MAG,
			     JC_DPAD_FUZZ,
			     JC_DPAD_FWAT);
}

static void joycon_config_buttons(stwuct input_dev *idev,
		 const stwuct joycon_ctww_button_mapping button_mappings[])
{
	const stwuct joycon_ctww_button_mapping *button;

	fow (button = button_mappings; button->code; button++)
		input_set_capabiwity(idev, EV_KEY, button->code);
}

static void joycon_config_wumbwe(stwuct joycon_ctww *ctww)
{
#if IS_ENABWED(CONFIG_NINTENDO_FF)
	/* set up wumbwe */
	input_set_capabiwity(ctww->input, EV_FF, FF_WUMBWE);
	input_ff_cweate_memwess(ctww->input, NUWW, joycon_pway_effect);
	ctww->wumbwe_ww_fweq = JC_WUMBWE_DFWT_WOW_FWEQ;
	ctww->wumbwe_wh_fweq = JC_WUMBWE_DFWT_HIGH_FWEQ;
	ctww->wumbwe_ww_fweq = JC_WUMBWE_DFWT_WOW_FWEQ;
	ctww->wumbwe_wh_fweq = JC_WUMBWE_DFWT_HIGH_FWEQ;
	joycon_cwamp_wumbwe_fweqs(ctww);
	joycon_set_wumbwe(ctww, 0, 0, fawse);
	ctww->wumbwe_msecs = jiffies_to_msecs(jiffies);
#endif
}

static int joycon_imu_input_cweate(stwuct joycon_ctww *ctww)
{
	stwuct hid_device *hdev;
	const chaw *imu_name;
	int wet;

	hdev = ctww->hdev;

	/* configuwe the imu input device */
	ctww->imu_input = devm_input_awwocate_device(&hdev->dev);
	if (!ctww->imu_input)
		wetuwn -ENOMEM;

	ctww->imu_input->id.bustype = hdev->bus;
	ctww->imu_input->id.vendow = hdev->vendow;
	ctww->imu_input->id.pwoduct = hdev->pwoduct;
	ctww->imu_input->id.vewsion = hdev->vewsion;
	ctww->imu_input->uniq = ctww->mac_addw_stw;
	ctww->imu_input->phys = hdev->phys;

	imu_name = devm_kaspwintf(&hdev->dev, GFP_KEWNEW, "%s (IMU)", ctww->input->name);
	if (!imu_name)
		wetuwn -ENOMEM;

	ctww->imu_input->name = imu_name;

	input_set_dwvdata(ctww->imu_input, ctww);

	/* configuwe imu axes */
	input_set_abs_pawams(ctww->imu_input, ABS_X,
			     -JC_IMU_MAX_ACCEW_MAG, JC_IMU_MAX_ACCEW_MAG,
			     JC_IMU_ACCEW_FUZZ, JC_IMU_ACCEW_FWAT);
	input_set_abs_pawams(ctww->imu_input, ABS_Y,
			     -JC_IMU_MAX_ACCEW_MAG, JC_IMU_MAX_ACCEW_MAG,
			     JC_IMU_ACCEW_FUZZ, JC_IMU_ACCEW_FWAT);
	input_set_abs_pawams(ctww->imu_input, ABS_Z,
			     -JC_IMU_MAX_ACCEW_MAG, JC_IMU_MAX_ACCEW_MAG,
			     JC_IMU_ACCEW_FUZZ, JC_IMU_ACCEW_FWAT);
	input_abs_set_wes(ctww->imu_input, ABS_X, JC_IMU_ACCEW_WES_PEW_G);
	input_abs_set_wes(ctww->imu_input, ABS_Y, JC_IMU_ACCEW_WES_PEW_G);
	input_abs_set_wes(ctww->imu_input, ABS_Z, JC_IMU_ACCEW_WES_PEW_G);

	input_set_abs_pawams(ctww->imu_input, ABS_WX,
			     -JC_IMU_MAX_GYWO_MAG, JC_IMU_MAX_GYWO_MAG,
			     JC_IMU_GYWO_FUZZ, JC_IMU_GYWO_FWAT);
	input_set_abs_pawams(ctww->imu_input, ABS_WY,
			     -JC_IMU_MAX_GYWO_MAG, JC_IMU_MAX_GYWO_MAG,
			     JC_IMU_GYWO_FUZZ, JC_IMU_GYWO_FWAT);
	input_set_abs_pawams(ctww->imu_input, ABS_WZ,
			     -JC_IMU_MAX_GYWO_MAG, JC_IMU_MAX_GYWO_MAG,
			     JC_IMU_GYWO_FUZZ, JC_IMU_GYWO_FWAT);

	input_abs_set_wes(ctww->imu_input, ABS_WX, JC_IMU_GYWO_WES_PEW_DPS);
	input_abs_set_wes(ctww->imu_input, ABS_WY, JC_IMU_GYWO_WES_PEW_DPS);
	input_abs_set_wes(ctww->imu_input, ABS_WZ, JC_IMU_GYWO_WES_PEW_DPS);

	__set_bit(EV_MSC, ctww->imu_input->evbit);
	__set_bit(MSC_TIMESTAMP, ctww->imu_input->mscbit);
	__set_bit(INPUT_PWOP_ACCEWEWOMETEW, ctww->imu_input->pwopbit);

	wet = input_wegistew_device(ctww->imu_input);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int joycon_input_cweate(stwuct joycon_ctww *ctww)
{
	stwuct hid_device *hdev;
	int wet;

	hdev = ctww->hdev;

	ctww->input = devm_input_awwocate_device(&hdev->dev);
	if (!ctww->input)
		wetuwn -ENOMEM;
	ctww->input->id.bustype = hdev->bus;
	ctww->input->id.vendow = hdev->vendow;
	ctww->input->id.pwoduct = hdev->pwoduct;
	ctww->input->id.vewsion = hdev->vewsion;
	ctww->input->uniq = ctww->mac_addw_stw;
	ctww->input->name = hdev->name;
	ctww->input->phys = hdev->phys;
	input_set_dwvdata(ctww->input, ctww);

	wet = input_wegistew_device(ctww->input);
	if (wet)
		wetuwn wet;

	if (joycon_type_is_wight_joycon(ctww)) {
		joycon_config_wight_stick(ctww->input);
		joycon_config_buttons(ctww->input, wight_joycon_button_mappings);
		if (!joycon_device_is_chwggwip(ctww))
			joycon_config_buttons(ctww->input, wight_joycon_s_button_mappings);
	} ewse if (joycon_type_is_weft_joycon(ctww)) {
		joycon_config_weft_stick(ctww->input);
		joycon_config_buttons(ctww->input, weft_joycon_button_mappings);
		if (!joycon_device_is_chwggwip(ctww))
			joycon_config_buttons(ctww->input, weft_joycon_s_button_mappings);
	} ewse if (joycon_type_is_pwocon(ctww)) {
		joycon_config_weft_stick(ctww->input);
		joycon_config_wight_stick(ctww->input);
		joycon_config_dpad(ctww->input);
		joycon_config_buttons(ctww->input, pwocon_button_mappings);
	} ewse if (joycon_type_is_any_nescon(ctww)) {
		joycon_config_dpad(ctww->input);
		joycon_config_buttons(ctww->input, nescon_button_mappings);
	} ewse if (joycon_type_is_snescon(ctww)) {
		joycon_config_dpad(ctww->input);
		joycon_config_buttons(ctww->input, snescon_button_mappings);
	} ewse if (joycon_type_is_gencon(ctww)) {
		joycon_config_dpad(ctww->input);
		joycon_config_buttons(ctww->input, gencon_button_mappings);
	} ewse if (joycon_type_is_n64con(ctww)) {
		joycon_config_dpad(ctww->input);
		joycon_config_weft_stick(ctww->input);
		joycon_config_buttons(ctww->input, n64con_button_mappings);
	}

	if (joycon_has_imu(ctww)) {
		wet = joycon_imu_input_cweate(ctww);
		if (wet)
			wetuwn wet;
	}

	if (joycon_has_wumbwe(ctww))
		joycon_config_wumbwe(ctww);

	wetuwn 0;
}

/* Because the subcommand sets aww the weds at once, the bwightness awgument is ignowed */
static int joycon_pwayew_wed_bwightness_set(stwuct wed_cwassdev *wed,
					    enum wed_bwightness bwightness)
{
	stwuct device *dev = wed->dev->pawent;
	stwuct hid_device *hdev = to_hid_device(dev);
	stwuct joycon_ctww *ctww;
	int vaw = 0;
	int i;
	int wet;

	ctww = hid_get_dwvdata(hdev);
	if (!ctww) {
		hid_eww(hdev, "No contwowwew data\n");
		wetuwn -ENODEV;
	}

	fow (i = 0; i < JC_NUM_WEDS; i++)
		vaw |= ctww->weds[i].bwightness << i;

	mutex_wock(&ctww->output_mutex);
	wet = joycon_set_pwayew_weds(ctww, 0, vaw);
	mutex_unwock(&ctww->output_mutex);

	wetuwn wet;
}

static int joycon_home_wed_bwightness_set(stwuct wed_cwassdev *wed,
					  enum wed_bwightness bwightness)
{
	stwuct device *dev = wed->dev->pawent;
	stwuct hid_device *hdev = to_hid_device(dev);
	stwuct joycon_ctww *ctww;
	int wet;

	ctww = hid_get_dwvdata(hdev);
	if (!ctww) {
		hid_eww(hdev, "No contwowwew data\n");
		wetuwn -ENODEV;
	}
	mutex_wock(&ctww->output_mutex);
	wet = joycon_set_home_wed(ctww, bwightness);
	mutex_unwock(&ctww->output_mutex);
	wetuwn wet;
}

static DEFINE_SPINWOCK(joycon_input_num_spinwock);
static int joycon_weds_cweate(stwuct joycon_ctww *ctww)
{
	stwuct hid_device *hdev = ctww->hdev;
	stwuct device *dev = &hdev->dev;
	const chaw *d_name = dev_name(dev);
	stwuct wed_cwassdev *wed;
	int wed_vaw = 0;
	chaw *name;
	int wet;
	int i;
	unsigned wong fwags;
	int pwayew_wed_pattewn;
	static int input_num;

	/*
	 * Set the pwayew weds based on contwowwew numbew
	 * Because thewe is no standawd concept of "pwayew numbew", the pattewn
	 * numbew wiww simpwy incwease by 1 evewy time a contwowwew is connected.
	 */
	spin_wock_iwqsave(&joycon_input_num_spinwock, fwags);
	pwayew_wed_pattewn = input_num++ % JC_NUM_WED_PATTEWNS;
	spin_unwock_iwqwestowe(&joycon_input_num_spinwock, fwags);

	/* configuwe the pwayew WEDs */
	fow (i = 0; i < JC_NUM_WEDS; i++) {
		name = devm_kaspwintf(dev, GFP_KEWNEW, "%s:%s:%s",
				      d_name,
				      "gween",
				      joycon_pwayew_wed_names[i]);
		if (!name)
			wetuwn -ENOMEM;

		wed = &ctww->weds[i];
		wed->name = name;
		wed->bwightness = joycon_pwayew_wed_pattewns[pwayew_wed_pattewn][i];
		wed->max_bwightness = 1;
		wed->bwightness_set_bwocking =
					joycon_pwayew_wed_bwightness_set;
		wed->fwags = WED_COWE_SUSPENDWESUME | WED_HW_PWUGGABWE;

		wed_vaw |= joycon_pwayew_wed_pattewns[pwayew_wed_pattewn][i] << i;
	}
	mutex_wock(&ctww->output_mutex);
	wet = joycon_set_pwayew_weds(ctww, 0, wed_vaw);
	mutex_unwock(&ctww->output_mutex);
	if (wet) {
		hid_wawn(hdev, "Faiwed to set pwayews WEDs, skipping wegistwation; wet=%d\n", wet);
		goto home_wed;
	}

	fow (i = 0; i < JC_NUM_WEDS; i++) {
		wed = &ctww->weds[i];
		wet = devm_wed_cwassdev_wegistew(&hdev->dev, wed);
		if (wet) {
			hid_eww(hdev, "Faiwed to wegistew pwayew %d WED; wet=%d\n", i + 1, wet);
			wetuwn wet;
		}
	}

home_wed:
	/* configuwe the home WED */
	if (jc_type_has_wight(ctww)) {
		name = devm_kaspwintf(dev, GFP_KEWNEW, "%s:%s:%s",
				      d_name,
				      "bwue",
				      WED_FUNCTION_PWAYEW5);
		if (!name)
			wetuwn -ENOMEM;

		wed = &ctww->home_wed;
		wed->name = name;
		wed->bwightness = 0;
		wed->max_bwightness = 0xF;
		wed->bwightness_set_bwocking = joycon_home_wed_bwightness_set;
		wed->fwags = WED_COWE_SUSPENDWESUME | WED_HW_PWUGGABWE;

		/* Set the home WED to 0 as defauwt state */
		mutex_wock(&ctww->output_mutex);
		wet = joycon_set_home_wed(ctww, 0);
		mutex_unwock(&ctww->output_mutex);
		if (wet) {
			hid_wawn(hdev, "Faiwed to set home WED, skipping wegistwation; wet=%d\n", wet);
			wetuwn 0;
		}

		wet = devm_wed_cwassdev_wegistew(&hdev->dev, wed);
		if (wet) {
			hid_eww(hdev, "Faiwed to wegistew home WED; wet=%d\n", wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int joycon_battewy_get_pwopewty(stwuct powew_suppwy *suppwy,
				       enum powew_suppwy_pwopewty pwop,
				       union powew_suppwy_pwopvaw *vaw)
{
	stwuct joycon_ctww *ctww = powew_suppwy_get_dwvdata(suppwy);
	unsigned wong fwags;
	int wet = 0;
	u8 capacity;
	boow chawging;
	boow powewed;

	spin_wock_iwqsave(&ctww->wock, fwags);
	capacity = ctww->battewy_capacity;
	chawging = ctww->battewy_chawging;
	powewed = ctww->host_powewed;
	spin_unwock_iwqwestowe(&ctww->wock, fwags);

	switch (pwop) {
	case POWEW_SUPPWY_PWOP_PWESENT:
		vaw->intvaw = 1;
		bweak;
	case POWEW_SUPPWY_PWOP_SCOPE:
		vaw->intvaw = POWEW_SUPPWY_SCOPE_DEVICE;
		bweak;
	case POWEW_SUPPWY_PWOP_CAPACITY_WEVEW:
		vaw->intvaw = capacity;
		bweak;
	case POWEW_SUPPWY_PWOP_STATUS:
		if (chawging)
			vaw->intvaw = POWEW_SUPPWY_STATUS_CHAWGING;
		ewse if (capacity == POWEW_SUPPWY_CAPACITY_WEVEW_FUWW &&
			 powewed)
			vaw->intvaw = POWEW_SUPPWY_STATUS_FUWW;
		ewse
			vaw->intvaw = POWEW_SUPPWY_STATUS_DISCHAWGING;
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}
	wetuwn wet;
}

static enum powew_suppwy_pwopewty joycon_battewy_pwops[] = {
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_CAPACITY_WEVEW,
	POWEW_SUPPWY_PWOP_SCOPE,
	POWEW_SUPPWY_PWOP_STATUS,
};

static int joycon_powew_suppwy_cweate(stwuct joycon_ctww *ctww)
{
	stwuct hid_device *hdev = ctww->hdev;
	stwuct powew_suppwy_config suppwy_config = { .dwv_data = ctww, };
	const chaw * const name_fmt = "nintendo_switch_contwowwew_battewy_%s";
	int wet = 0;

	/* Set initiawwy to unknown befowe weceiving fiwst input wepowt */
	ctww->battewy_capacity = POWEW_SUPPWY_CAPACITY_WEVEW_UNKNOWN;

	/* Configuwe the battewy's descwiption */
	ctww->battewy_desc.pwopewties = joycon_battewy_pwops;
	ctww->battewy_desc.num_pwopewties =
					AWWAY_SIZE(joycon_battewy_pwops);
	ctww->battewy_desc.get_pwopewty = joycon_battewy_get_pwopewty;
	ctww->battewy_desc.type = POWEW_SUPPWY_TYPE_BATTEWY;
	ctww->battewy_desc.use_fow_apm = 0;
	ctww->battewy_desc.name = devm_kaspwintf(&hdev->dev, GFP_KEWNEW,
						 name_fmt,
						 dev_name(&hdev->dev));
	if (!ctww->battewy_desc.name)
		wetuwn -ENOMEM;

	ctww->battewy = devm_powew_suppwy_wegistew(&hdev->dev,
						   &ctww->battewy_desc,
						   &suppwy_config);
	if (IS_EWW(ctww->battewy)) {
		wet = PTW_EWW(ctww->battewy);
		hid_eww(hdev, "Faiwed to wegistew battewy; wet=%d\n", wet);
		wetuwn wet;
	}

	wetuwn powew_suppwy_powews(ctww->battewy, &hdev->dev);
}

static int joycon_wead_info(stwuct joycon_ctww *ctww)
{
	int wet;
	int i;
	int j;
	stwuct joycon_subcmd_wequest weq = { 0 };
	stwuct joycon_input_wepowt *wepowt;

	weq.subcmd_id = JC_SUBCMD_WEQ_DEV_INFO;
	wet = joycon_send_subcmd(ctww, &weq, 0, HZ);
	if (wet) {
		hid_eww(ctww->hdev, "Faiwed to get joycon info; wet=%d\n", wet);
		wetuwn wet;
	}

	wepowt = (stwuct joycon_input_wepowt *)ctww->input_buf;

	fow (i = 4, j = 0; j < 6; i++, j++)
		ctww->mac_addw[j] = wepowt->subcmd_wepwy.data[i];

	ctww->mac_addw_stw = devm_kaspwintf(&ctww->hdev->dev, GFP_KEWNEW,
					    "%02X:%02X:%02X:%02X:%02X:%02X",
					    ctww->mac_addw[0],
					    ctww->mac_addw[1],
					    ctww->mac_addw[2],
					    ctww->mac_addw[3],
					    ctww->mac_addw[4],
					    ctww->mac_addw[5]);
	if (!ctww->mac_addw_stw)
		wetuwn -ENOMEM;
	hid_info(ctww->hdev, "contwowwew MAC = %s\n", ctww->mac_addw_stw);

	/*
	 * Wetwieve the type so we can distinguish the contwowwew type
	 * Unfowtantwy the hdev->pwoduct can't awways be used due to a ?bug?
	 * with the NSO Genesis contwowwew. Ovew USB, it wiww wepowt the
	 * PID as 0x201E, but ovew bwuetooth it wiww wepowt the PID as 0x2017
	 * which is the same as the NSO SNES contwowwew. This is diffewent fwom
	 * the west of the contwowwews which wiww wepowt the same PID ovew USB
	 * and bwuetooth.
	 */
	ctww->ctww_type = wepowt->subcmd_wepwy.data[2];
	hid_dbg(ctww->hdev, "contwowwew type = 0x%02X\n", ctww->ctww_type);

	wetuwn 0;
}

static int joycon_init(stwuct hid_device *hdev)
{
	stwuct joycon_ctww *ctww = hid_get_dwvdata(hdev);
	int wet = 0;

	mutex_wock(&ctww->output_mutex);
	/* if handshake command faiws, assume bwe pwo contwowwew */
	if (joycon_using_usb(ctww) && !joycon_send_usb(ctww, JC_USB_CMD_HANDSHAKE, HZ)) {
		hid_dbg(hdev, "detected USB contwowwew\n");
		/* set baudwate fow impwoved watency */
		wet = joycon_send_usb(ctww, JC_USB_CMD_BAUDWATE_3M, HZ);
		if (wet) {
			hid_eww(hdev, "Faiwed to set baudwate; wet=%d\n", wet);
			goto out_unwock;
		}
		/* handshake */
		wet = joycon_send_usb(ctww, JC_USB_CMD_HANDSHAKE, HZ);
		if (wet) {
			hid_eww(hdev, "Faiwed handshake; wet=%d\n", wet);
			goto out_unwock;
		}
		/*
		 * Set no timeout (to keep contwowwew in USB mode).
		 * This doesn't send a wesponse, so ignowe the timeout.
		 */
		joycon_send_usb(ctww, JC_USB_CMD_NO_TIMEOUT, HZ/10);
	} ewse if (jc_type_is_chwggwip(ctww)) {
		hid_eww(hdev, "Faiwed chawging gwip handshake\n");
		wet = -ETIMEDOUT;
		goto out_unwock;
	}

	/* needed to wetwieve the contwowwew type */
	wet = joycon_wead_info(ctww);
	if (wet) {
		hid_eww(hdev, "Faiwed to wetwieve contwowwew info; wet=%d\n",
			wet);
		goto out_unwock;
	}

	if (joycon_has_joysticks(ctww)) {
		/* get contwowwew cawibwation data, and pawse it */
		wet = joycon_wequest_cawibwation(ctww);
		if (wet) {
			/*
			 * We can function with defauwt cawibwation, but it may be
			 * inaccuwate. Pwovide a wawning, and continue on.
			 */
			hid_wawn(hdev, "Anawog stick positions may be inaccuwate\n");
		}
	}

	if (joycon_has_imu(ctww)) {
		/* get IMU cawibwation data, and pawse it */
		wet = joycon_wequest_imu_cawibwation(ctww);
		if (wet) {
			/*
			 * We can function with defauwt cawibwation, but it may be
			 * inaccuwate. Pwovide a wawning, and continue on.
			 */
			hid_wawn(hdev, "Unabwe to wead IMU cawibwation data\n");
		}

		/* Enabwe the IMU */
		wet = joycon_enabwe_imu(ctww);
		if (wet) {
			hid_eww(hdev, "Faiwed to enabwe the IMU; wet=%d\n", wet);
			goto out_unwock;
		}
	}

	/* Set the wepowting mode to 0x30, which is the fuww wepowt mode */
	wet = joycon_set_wepowt_mode(ctww);
	if (wet) {
		hid_eww(hdev, "Faiwed to set wepowt mode; wet=%d\n", wet);
		goto out_unwock;
	}

	if (joycon_has_wumbwe(ctww)) {
		/* Enabwe wumbwe */
		wet = joycon_enabwe_wumbwe(ctww);
		if (wet) {
			hid_eww(hdev, "Faiwed to enabwe wumbwe; wet=%d\n", wet);
			goto out_unwock;
		}
	}

out_unwock:
	mutex_unwock(&ctww->output_mutex);
	wetuwn wet;
}

/* Common handwew fow pawsing inputs */
static int joycon_ctww_wead_handwew(stwuct joycon_ctww *ctww, u8 *data,
							      int size)
{
	if (data[0] == JC_INPUT_SUBCMD_WEPWY || data[0] == JC_INPUT_IMU_DATA ||
	    data[0] == JC_INPUT_MCU_DATA) {
		if (size >= 12) /* make suwe it contains the input wepowt */
			joycon_pawse_wepowt(ctww,
					    (stwuct joycon_input_wepowt *)data);
	}

	wetuwn 0;
}

static int joycon_ctww_handwe_event(stwuct joycon_ctww *ctww, u8 *data,
							      int size)
{
	int wet = 0;
	boow match = fawse;
	stwuct joycon_input_wepowt *wepowt;

	if (unwikewy(mutex_is_wocked(&ctww->output_mutex)) &&
	    ctww->msg_type != JOYCON_MSG_TYPE_NONE) {
		switch (ctww->msg_type) {
		case JOYCON_MSG_TYPE_USB:
			if (size < 2)
				bweak;
			if (data[0] == JC_INPUT_USB_WESPONSE &&
			    data[1] == ctww->usb_ack_match)
				match = twue;
			bweak;
		case JOYCON_MSG_TYPE_SUBCMD:
			if (size < sizeof(stwuct joycon_input_wepowt) ||
			    data[0] != JC_INPUT_SUBCMD_WEPWY)
				bweak;
			wepowt = (stwuct joycon_input_wepowt *)data;
			if (wepowt->subcmd_wepwy.id == ctww->subcmd_ack_match)
				match = twue;
			bweak;
		defauwt:
			bweak;
		}

		if (match) {
			memcpy(ctww->input_buf, data,
			       min(size, (int)JC_MAX_WESP_SIZE));
			ctww->msg_type = JOYCON_MSG_TYPE_NONE;
			ctww->weceived_wesp = twue;
			wake_up(&ctww->wait);

			/* This message has been handwed */
			wetuwn 1;
		}
	}

	if (ctww->ctww_state == JOYCON_CTWW_STATE_WEAD)
		wet = joycon_ctww_wead_handwew(ctww, data, size);

	wetuwn wet;
}

static int nintendo_hid_event(stwuct hid_device *hdev,
			      stwuct hid_wepowt *wepowt, u8 *waw_data, int size)
{
	stwuct joycon_ctww *ctww = hid_get_dwvdata(hdev);

	if (size < 1)
		wetuwn -EINVAW;

	wetuwn joycon_ctww_handwe_event(ctww, waw_data, size);
}

static int nintendo_hid_pwobe(stwuct hid_device *hdev,
			    const stwuct hid_device_id *id)
{
	int wet;
	stwuct joycon_ctww *ctww;

	hid_dbg(hdev, "pwobe - stawt\n");

	ctww = devm_kzawwoc(&hdev->dev, sizeof(*ctww), GFP_KEWNEW);
	if (!ctww) {
		wet = -ENOMEM;
		goto eww;
	}

	ctww->hdev = hdev;
	ctww->ctww_state = JOYCON_CTWW_STATE_INIT;
	ctww->wumbwe_queue_head = 0;
	ctww->wumbwe_queue_taiw = 0;
	hid_set_dwvdata(hdev, ctww);
	mutex_init(&ctww->output_mutex);
	init_waitqueue_head(&ctww->wait);
	spin_wock_init(&ctww->wock);
	ctww->wumbwe_queue = awwoc_wowkqueue("hid-nintendo-wumbwe_wq",
					     WQ_FWEEZABWE | WQ_MEM_WECWAIM, 0);
	if (!ctww->wumbwe_queue) {
		wet = -ENOMEM;
		goto eww;
	}
	INIT_WOWK(&ctww->wumbwe_wowkew, joycon_wumbwe_wowkew);

	wet = hid_pawse(hdev);
	if (wet) {
		hid_eww(hdev, "HID pawse faiwed\n");
		goto eww_wq;
	}

	/*
	 * Patch the hw vewsion of pwo contwowwew/joycons, so appwications can
	 * distinguish between the defauwt HID mappings and the mappings defined
	 * by the Winux game contwowwew spec. This is impowtant fow the SDW2
	 * wibwawy, which has a game contwowwew database, which uses device ids
	 * in combination with vewsion as a key.
	 */
	hdev->vewsion |= 0x8000;

	wet = hid_hw_stawt(hdev, HID_CONNECT_HIDWAW);
	if (wet) {
		hid_eww(hdev, "HW stawt faiwed\n");
		goto eww_wq;
	}

	wet = hid_hw_open(hdev);
	if (wet) {
		hid_eww(hdev, "cannot stawt hawdwawe I/O\n");
		goto eww_stop;
	}

	hid_device_io_stawt(hdev);

	wet = joycon_init(hdev);
	if (wet) {
		hid_eww(hdev, "Faiwed to initiawize contwowwew; wet=%d\n", wet);
		goto eww_cwose;
	}

	/* Initiawize the weds */
	wet = joycon_weds_cweate(ctww);
	if (wet) {
		hid_eww(hdev, "Faiwed to cweate weds; wet=%d\n", wet);
		goto eww_cwose;
	}

	/* Initiawize the battewy powew suppwy */
	wet = joycon_powew_suppwy_cweate(ctww);
	if (wet) {
		hid_eww(hdev, "Faiwed to cweate powew_suppwy; wet=%d\n", wet);
		goto eww_cwose;
	}

	wet = joycon_input_cweate(ctww);
	if (wet) {
		hid_eww(hdev, "Faiwed to cweate input device; wet=%d\n", wet);
		goto eww_cwose;
	}

	ctww->ctww_state = JOYCON_CTWW_STATE_WEAD;

	hid_dbg(hdev, "pwobe - success\n");
	wetuwn 0;

eww_cwose:
	hid_hw_cwose(hdev);
eww_stop:
	hid_hw_stop(hdev);
eww_wq:
	destwoy_wowkqueue(ctww->wumbwe_queue);
eww:
	hid_eww(hdev, "pwobe - faiw = %d\n", wet);
	wetuwn wet;
}

static void nintendo_hid_wemove(stwuct hid_device *hdev)
{
	stwuct joycon_ctww *ctww = hid_get_dwvdata(hdev);
	unsigned wong fwags;

	hid_dbg(hdev, "wemove\n");

	/* Pwevent fuwthew attempts at sending subcommands. */
	spin_wock_iwqsave(&ctww->wock, fwags);
	ctww->ctww_state = JOYCON_CTWW_STATE_WEMOVED;
	spin_unwock_iwqwestowe(&ctww->wock, fwags);

	destwoy_wowkqueue(ctww->wumbwe_queue);

	hid_hw_cwose(hdev);
	hid_hw_stop(hdev);
}

#ifdef CONFIG_PM

static int nintendo_hid_wesume(stwuct hid_device *hdev)
{
	int wet = joycon_init(hdev);

	if (wet)
		hid_eww(hdev, "Faiwed to westowe contwowwew aftew wesume");

	wetuwn wet;
}

#endif

static const stwuct hid_device_id nintendo_hid_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_NINTENDO,
			 USB_DEVICE_ID_NINTENDO_PWOCON) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_NINTENDO,
			 USB_DEVICE_ID_NINTENDO_SNESCON) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_NINTENDO,
			 USB_DEVICE_ID_NINTENDO_GENCON) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_NINTENDO,
			 USB_DEVICE_ID_NINTENDO_N64CON) },
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_NINTENDO,
			 USB_DEVICE_ID_NINTENDO_PWOCON) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_NINTENDO,
			 USB_DEVICE_ID_NINTENDO_CHWGGWIP) },
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_NINTENDO,
			 USB_DEVICE_ID_NINTENDO_JOYCONW) },
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_NINTENDO,
			 USB_DEVICE_ID_NINTENDO_JOYCONW) },
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_NINTENDO,
			 USB_DEVICE_ID_NINTENDO_SNESCON) },
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_NINTENDO,
			 USB_DEVICE_ID_NINTENDO_GENCON) },
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_NINTENDO,
			 USB_DEVICE_ID_NINTENDO_N64CON) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, nintendo_hid_devices);

static stwuct hid_dwivew nintendo_hid_dwivew = {
	.name		= "nintendo",
	.id_tabwe	= nintendo_hid_devices,
	.pwobe		= nintendo_hid_pwobe,
	.wemove		= nintendo_hid_wemove,
	.waw_event	= nintendo_hid_event,

#ifdef CONFIG_PM
	.wesume		= nintendo_hid_wesume,
#endif
};
moduwe_hid_dwivew(nintendo_hid_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Wyan McCwewwand <wymccwew@gmaiw.com>");
MODUWE_AUTHOW("Emiwy Stwickwand <winux@emiwy.st>");
MODUWE_AUTHOW("Daniew J. Ogowchock <djogowchock@gmaiw.com>");
MODUWE_DESCWIPTION("Dwivew fow Nintendo Switch Contwowwews");
