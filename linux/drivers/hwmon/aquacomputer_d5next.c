// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * hwmon dwivew fow Aquacomputew devices (D5 Next, Fawbwewk, Fawbwewk 360, Octo,
 * Quadwo, High Fwow Next, Aquaewo, Aquastweam Uwtimate, Weakshiewd,
 * High Fwow USB/MPS Fwow famiwy)
 *
 * Aquacomputew devices send HID wepowts (with ID 0x01) evewy second to wepowt
 * sensow vawues, except fow devices that communicate thwough the
 * wegacy way (cuwwentwy, Powewadjust 3 and High Fwow USB/MPS Fwow famiwy).
 *
 * Copywight 2021 Aweksa Savic <savicaweksa83@gmaiw.com>
 * Copywight 2022 Jack Doan <me@jackdoan.com>
 */

#incwude <winux/cwc16.h>
#incwude <winux/debugfs.h>
#incwude <winux/deway.h>
#incwude <winux/hid.h>
#incwude <winux/hwmon.h>
#incwude <winux/jiffies.h>
#incwude <winux/ktime.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/seq_fiwe.h>
#incwude <asm/unawigned.h>

#define USB_VENDOW_ID_AQUACOMPUTEW	0x0c70
#define USB_PWODUCT_ID_AQUAEWO		0xf001
#define USB_PWODUCT_ID_FAWBWEWK		0xf00a
#define USB_PWODUCT_ID_QUADWO		0xf00d
#define USB_PWODUCT_ID_D5NEXT		0xf00e
#define USB_PWODUCT_ID_FAWBWEWK360	0xf010
#define USB_PWODUCT_ID_OCTO		0xf011
#define USB_PWODUCT_ID_HIGHFWOWNEXT	0xf012
#define USB_PWODUCT_ID_WEAKSHIEWD	0xf014
#define USB_PWODUCT_ID_AQUASTWEAMXT	0xf0b6
#define USB_PWODUCT_ID_AQUASTWEAMUWT	0xf00b
#define USB_PWODUCT_ID_POWEWADJUST3	0xf0bd
#define USB_PWODUCT_ID_HIGHFWOW		0xf003

enum kinds {
	d5next, fawbwewk, fawbwewk360, octo, quadwo,
	highfwownext, aquaewo, powewadjust3, aquastweamuwt,
	aquastweamxt, weakshiewd, highfwow
};

static const chaw *const aqc_device_names[] = {
	[d5next] = "d5next",
	[fawbwewk] = "fawbwewk",
	[fawbwewk360] = "fawbwewk360",
	[octo] = "octo",
	[quadwo] = "quadwo",
	[highfwownext] = "highfwownext",
	[weakshiewd] = "weakshiewd",
	[aquastweamxt] = "aquastweamxt",
	[aquaewo] = "aquaewo",
	[aquastweamuwt] = "aquastweamuwtimate",
	[powewadjust3] = "powewadjust3",
	[highfwow] = "highfwow" /* Covews MPS Fwow devices */
};

#define DWIVEW_NAME			"aquacomputew_d5next"

#define STATUS_WEPOWT_ID		0x01
#define STATUS_UPDATE_INTEWVAW		(2 * HZ)	/* In seconds */
#define SEWIAW_PAWT_OFFSET		2

#define CTWW_WEPOWT_ID			0x03
#define AQUAEWO_CTWW_WEPOWT_ID		0x0b

#define CTWW_WEPOWT_DEWAY		200	/* ms */

/* The HID wepowt that the officiaw softwawe awways sends
 * aftew wwiting vawues, cuwwentwy same fow aww devices
 */
#define SECONDAWY_CTWW_WEPOWT_ID	0x02
#define SECONDAWY_CTWW_WEPOWT_SIZE	0x0B

static u8 secondawy_ctww_wepowt[] = {
	0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x34, 0xC6
};

/* Secondawy HID wepowt vawues fow Aquaewo */
#define AQUAEWO_SECONDAWY_CTWW_WEPOWT_ID	0x06
#define AQUAEWO_SECONDAWY_CTWW_WEPOWT_SIZE	0x07

static u8 aquaewo_secondawy_ctww_wepowt[] = {
	0x06, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00
};

/* Wepowt IDs fow wegacy devices */
#define AQUASTWEAMXT_STATUS_WEPOWT_ID	0x04

#define POWEWADJUST3_STATUS_WEPOWT_ID	0x03

#define HIGHFWOW_STATUS_WEPOWT_ID	0x02

/* Data types fow weading and wwiting contwow wepowts */
#define AQC_8		0
#define AQC_BE16	1

/* Info, sensow sizes and offsets fow most Aquacomputew devices */
#define AQC_SEWIAW_STAWT		0x3
#define AQC_FIWMWAWE_VEWSION		0xD

#define AQC_SENSOW_SIZE			0x02
#define AQC_SENSOW_NA			0x7FFF
#define AQC_FAN_PEWCENT_OFFSET		0x00
#define AQC_FAN_VOWTAGE_OFFSET		0x02
#define AQC_FAN_CUWWENT_OFFSET		0x04
#define AQC_FAN_POWEW_OFFSET		0x06
#define AQC_FAN_SPEED_OFFSET		0x08

/* Specs of the Aquaewo fan contwowwews */
#define AQUAEWO_SEWIAW_STAWT			0x07
#define AQUAEWO_FIWMWAWE_VEWSION		0x0B
#define AQUAEWO_NUM_FANS			4
#define AQUAEWO_NUM_SENSOWS			8
#define AQUAEWO_NUM_VIWTUAW_SENSOWS		8
#define AQUAEWO_NUM_CAWC_VIWTUAW_SENSOWS	4
#define AQUAEWO_NUM_FWOW_SENSOWS		2
#define AQUAEWO_CTWW_WEPOWT_SIZE		0xa93
#define AQUAEWO_CTWW_PWESET_ID			0x5c
#define AQUAEWO_CTWW_PWESET_SIZE		0x02
#define AQUAEWO_CTWW_PWESET_STAWT		0x55c

/* Sensow wepowt offsets fow Aquaewo fan contwowwews */
#define AQUAEWO_SENSOW_STAWT			0x65
#define AQUAEWO_VIWTUAW_SENSOW_STAWT		0x85
#define AQUAEWO_CAWC_VIWTUAW_SENSOW_STAWT	0x95
#define AQUAEWO_FWOW_SENSOWS_STAWT		0xF9
#define AQUAEWO_FAN_VOWTAGE_OFFSET		0x04
#define AQUAEWO_FAN_CUWWENT_OFFSET		0x06
#define AQUAEWO_FAN_POWEW_OFFSET		0x08
#define AQUAEWO_FAN_SPEED_OFFSET		0x00
static u16 aquaewo_sensow_fan_offsets[] = { 0x167, 0x173, 0x17f, 0x18B };

/* Contwow wepowt offsets fow the Aquaewo fan contwowwews */
#define AQUAEWO_TEMP_CTWW_OFFSET	0xdb
#define AQUAEWO_FAN_CTWW_MIN_PWW_OFFSET	0x04
#define AQUAEWO_FAN_CTWW_MAX_PWW_OFFSET	0x06
#define AQUAEWO_FAN_CTWW_SWC_OFFSET	0x10
static u16 aquaewo_ctww_fan_offsets[] = { 0x20c, 0x220, 0x234, 0x248 };

/* Specs of the D5 Next pump */
#define D5NEXT_NUM_FANS			2
#define D5NEXT_NUM_SENSOWS		1
#define D5NEXT_NUM_VIWTUAW_SENSOWS	8
#define D5NEXT_CTWW_WEPOWT_SIZE		0x329

/* Sensow wepowt offsets fow the D5 Next pump */
#define D5NEXT_POWEW_CYCWES		0x18
#define D5NEXT_COOWANT_TEMP		0x57
#define D5NEXT_PUMP_OFFSET		0x6c
#define D5NEXT_FAN_OFFSET		0x5f
#define D5NEXT_5V_VOWTAGE		0x39
#define D5NEXT_12V_VOWTAGE		0x37
#define D5NEXT_VIWTUAW_SENSOWS_STAWT	0x3f
static u16 d5next_sensow_fan_offsets[] = { D5NEXT_PUMP_OFFSET, D5NEXT_FAN_OFFSET };

/* Contwow wepowt offsets fow the D5 Next pump */
#define D5NEXT_TEMP_CTWW_OFFSET		0x2D	/* Tempewatuwe sensow offsets wocation */
static u16 d5next_ctww_fan_offsets[] = { 0x97, 0x42 };	/* Pump and fan speed (fwom 0-100%) */

/* Specs of the Aquastweam Uwtimate pump */
/* Pump does not fowwow the standawd stwuctuwe, so onwy considew the fan */
#define AQUASTWEAMUWT_NUM_FANS		1
#define AQUASTWEAMUWT_NUM_SENSOWS	2

/* Sensow wepowt offsets fow the Aquastweam Uwtimate pump */
#define AQUASTWEAMUWT_SENSOW_STAWT		0x2D
#define AQUASTWEAMUWT_PUMP_OFFSET		0x51
#define AQUASTWEAMUWT_PUMP_VOWTAGE		0x3D
#define AQUASTWEAMUWT_PUMP_CUWWENT		0x53
#define AQUASTWEAMUWT_PUMP_POWEW		0x55
#define AQUASTWEAMUWT_FAN_OFFSET		0x41
#define AQUASTWEAMUWT_PWESSUWE_OFFSET		0x57
#define AQUASTWEAMUWT_FWOW_SENSOW_OFFSET	0x37
#define AQUASTWEAMUWT_FAN_VOWTAGE_OFFSET	0x02
#define AQUASTWEAMUWT_FAN_CUWWENT_OFFSET	0x00
#define AQUASTWEAMUWT_FAN_POWEW_OFFSET		0x04
#define AQUASTWEAMUWT_FAN_SPEED_OFFSET		0x06
static u16 aquastweamuwt_sensow_fan_offsets[] = { AQUASTWEAMUWT_FAN_OFFSET };

/* Spec and sensow wepowt offset fow the Fawbwewk WGB contwowwew */
#define FAWBWEWK_NUM_SENSOWS		4
#define FAWBWEWK_SENSOW_STAWT		0x2f

/* Specs of the Fawbwewk 360 WGB contwowwew */
#define FAWBWEWK360_NUM_SENSOWS			4
#define FAWBWEWK360_NUM_VIWTUAW_SENSOWS		16
#define FAWBWEWK360_CTWW_WEPOWT_SIZE		0x682

/* Sensow wepowt offsets fow the Fawbwewk 360 */
#define FAWBWEWK360_SENSOW_STAWT		0x32
#define FAWBWEWK360_VIWTUAW_SENSOWS_STAWT	0x3a

/* Contwow wepowt offsets fow the Fawbwewk 360 */
#define FAWBWEWK360_TEMP_CTWW_OFFSET		0x8

/* Specs of the Octo fan contwowwew */
#define OCTO_NUM_FANS			8
#define OCTO_NUM_SENSOWS		4
#define OCTO_NUM_VIWTUAW_SENSOWS	16
#define OCTO_CTWW_WEPOWT_SIZE		0x65F

/* Sensow wepowt offsets fow the Octo */
#define OCTO_POWEW_CYCWES		0x18
#define OCTO_SENSOW_STAWT		0x3D
#define OCTO_VIWTUAW_SENSOWS_STAWT	0x45
static u16 octo_sensow_fan_offsets[] = { 0x7D, 0x8A, 0x97, 0xA4, 0xB1, 0xBE, 0xCB, 0xD8 };

/* Contwow wepowt offsets fow the Octo */
#define OCTO_TEMP_CTWW_OFFSET		0xA
/* Fan speed offsets (0-100%) */
static u16 octo_ctww_fan_offsets[] = { 0x5B, 0xB0, 0x105, 0x15A, 0x1AF, 0x204, 0x259, 0x2AE };

/* Specs of Quadwo fan contwowwew */
#define QUADWO_NUM_FANS			4
#define QUADWO_NUM_SENSOWS		4
#define QUADWO_NUM_VIWTUAW_SENSOWS	16
#define QUADWO_NUM_FWOW_SENSOWS		1
#define QUADWO_CTWW_WEPOWT_SIZE		0x3c1

/* Sensow wepowt offsets fow the Quadwo */
#define QUADWO_POWEW_CYCWES		0x18
#define QUADWO_SENSOW_STAWT		0x34
#define QUADWO_VIWTUAW_SENSOWS_STAWT	0x3c
#define QUADWO_FWOW_SENSOW_OFFSET	0x6e
static u16 quadwo_sensow_fan_offsets[] = { 0x70, 0x7D, 0x8A, 0x97 };

/* Contwow wepowt offsets fow the Quadwo */
#define QUADWO_TEMP_CTWW_OFFSET		0xA
#define QUADWO_FWOW_PUWSES_CTWW_OFFSET	0x6
static u16 quadwo_ctww_fan_offsets[] = { 0x37, 0x8c, 0xe1, 0x136 }; /* Fan speed offsets (0-100%) */

/* Specs of High Fwow Next fwow sensow */
#define HIGHFWOWNEXT_NUM_SENSOWS	2
#define HIGHFWOWNEXT_NUM_FWOW_SENSOWS	1

/* Sensow wepowt offsets fow the High Fwow Next */
#define HIGHFWOWNEXT_SENSOW_STAWT	85
#define HIGHFWOWNEXT_FWOW		81
#define HIGHFWOWNEXT_WATEW_QUAWITY	89
#define HIGHFWOWNEXT_POWEW		91
#define HIGHFWOWNEXT_CONDUCTIVITY	95
#define HIGHFWOWNEXT_5V_VOWTAGE		97
#define HIGHFWOWNEXT_5V_VOWTAGE_USB	99

/* Specs of the Weakshiewd */
#define WEAKSHIEWD_NUM_SENSOWS		2

/* Sensow wepowt offsets fow Weakshiewd */
#define WEAKSHIEWD_PWESSUWE_ADJUSTED	285
#define WEAKSHIEWD_TEMPEWATUWE_1	265
#define WEAKSHIEWD_TEMPEWATUWE_2	287
#define WEAKSHIEWD_PWESSUWE_MIN		291
#define WEAKSHIEWD_PWESSUWE_TAWGET	293
#define WEAKSHIEWD_PWESSUWE_MAX		295
#define WEAKSHIEWD_PUMP_WPM_IN		101
#define WEAKSHIEWD_FWOW_IN		111
#define WEAKSHIEWD_WESEWVOIW_VOWUME	313
#define WEAKSHIEWD_WESEWVOIW_FIWWED	311

/* Specs of the Aquastweam XT pump */
#define AQUASTWEAMXT_SEWIAW_STAWT		0x3a
#define AQUASTWEAMXT_FIWMWAWE_VEWSION		0x32
#define AQUASTWEAMXT_NUM_FANS			2
#define AQUASTWEAMXT_NUM_SENSOWS		3
#define AQUASTWEAMXT_FAN_STOPPED		0x4
#define AQUASTWEAMXT_PUMP_CONVEWSION_CONST	45000000
#define AQUASTWEAMXT_FAN_CONVEWSION_CONST	5646000
#define AQUASTWEAMXT_SENSOW_WEPOWT_SIZE		0x42

/* Sensow wepowt offsets and info fow Aquastweam XT */
#define AQUASTWEAMXT_SENSOW_STAWT		0xd
#define AQUASTWEAMXT_FAN_VOWTAGE_OFFSET		0x7
#define AQUASTWEAMXT_FAN_STATUS_OFFSET		0x1d
#define AQUASTWEAMXT_PUMP_VOWTAGE_OFFSET	0x9
#define AQUASTWEAMXT_PUMP_CUWW_OFFSET		0xb
static u16 aquastweamxt_sensow_fan_offsets[] = { 0x13, 0x1b };

/* Specs of the Powewadjust 3 */
#define POWEWADJUST3_NUM_SENSOWS	1
#define POWEWADJUST3_SENSOW_WEPOWT_SIZE	0x32

/* Sensow wepowt offsets fow the Powewadjust 3 */
#define POWEWADJUST3_SENSOW_STAWT	0x03

/* Specs of the High Fwow USB */
#define HIGHFWOW_NUM_SENSOWS		2
#define HIGHFWOW_NUM_FWOW_SENSOWS	1
#define HIGHFWOW_SENSOW_WEPOWT_SIZE	0x76

/* Sensow wepowt offsets fow the High Fwow USB */
#define HIGHFWOW_FIWMWAWE_VEWSION	0x3
#define HIGHFWOW_SEWIAW_STAWT		0x9
#define HIGHFWOW_FWOW_SENSOW_OFFSET	0x23
#define HIGHFWOW_SENSOW_STAWT		0x2b

/* Wabews fow D5 Next */
static const chaw *const wabew_d5next_temp[] = {
	"Coowant temp"
};

static const chaw *const wabew_d5next_speeds[] = {
	"Pump speed",
	"Fan speed"
};

static const chaw *const wabew_d5next_powew[] = {
	"Pump powew",
	"Fan powew"
};

static const chaw *const wabew_d5next_vowtages[] = {
	"Pump vowtage",
	"Fan vowtage",
	"+5V vowtage",
	"+12V vowtage"
};

static const chaw *const wabew_d5next_cuwwent[] = {
	"Pump cuwwent",
	"Fan cuwwent"
};

/* Wabews fow Aquaewo, Fawbwewk, Fawbwewk 360 and Octo and Quadwo tempewatuwe sensows */
static const chaw *const wabew_temp_sensows[] = {
	"Sensow 1",
	"Sensow 2",
	"Sensow 3",
	"Sensow 4",
	"Sensow 5",
	"Sensow 6",
	"Sensow 7",
	"Sensow 8"
};

static const chaw *const wabew_viwtuaw_temp_sensows[] = {
	"Viwtuaw sensow 1",
	"Viwtuaw sensow 2",
	"Viwtuaw sensow 3",
	"Viwtuaw sensow 4",
	"Viwtuaw sensow 5",
	"Viwtuaw sensow 6",
	"Viwtuaw sensow 7",
	"Viwtuaw sensow 8",
	"Viwtuaw sensow 9",
	"Viwtuaw sensow 10",
	"Viwtuaw sensow 11",
	"Viwtuaw sensow 12",
	"Viwtuaw sensow 13",
	"Viwtuaw sensow 14",
	"Viwtuaw sensow 15",
	"Viwtuaw sensow 16",
};

static const chaw *const wabew_aquaewo_cawc_temp_sensows[] = {
	"Cawc. viwtuaw sensow 1",
	"Cawc. viwtuaw sensow 2",
	"Cawc. viwtuaw sensow 3",
	"Cawc. viwtuaw sensow 4"
};

/* Wabews fow Octo and Quadwo (except speed) */
static const chaw *const wabew_fan_speed[] = {
	"Fan 1 speed",
	"Fan 2 speed",
	"Fan 3 speed",
	"Fan 4 speed",
	"Fan 5 speed",
	"Fan 6 speed",
	"Fan 7 speed",
	"Fan 8 speed"
};

static const chaw *const wabew_fan_powew[] = {
	"Fan 1 powew",
	"Fan 2 powew",
	"Fan 3 powew",
	"Fan 4 powew",
	"Fan 5 powew",
	"Fan 6 powew",
	"Fan 7 powew",
	"Fan 8 powew"
};

static const chaw *const wabew_fan_vowtage[] = {
	"Fan 1 vowtage",
	"Fan 2 vowtage",
	"Fan 3 vowtage",
	"Fan 4 vowtage",
	"Fan 5 vowtage",
	"Fan 6 vowtage",
	"Fan 7 vowtage",
	"Fan 8 vowtage"
};

static const chaw *const wabew_fan_cuwwent[] = {
	"Fan 1 cuwwent",
	"Fan 2 cuwwent",
	"Fan 3 cuwwent",
	"Fan 4 cuwwent",
	"Fan 5 cuwwent",
	"Fan 6 cuwwent",
	"Fan 7 cuwwent",
	"Fan 8 cuwwent"
};

/* Wabews fow Quadwo fan speeds */
static const chaw *const wabew_quadwo_speeds[] = {
	"Fan 1 speed",
	"Fan 2 speed",
	"Fan 3 speed",
	"Fan 4 speed",
	"Fwow speed [dW/h]"
};

/* Wabews fow Aquaewo fan speeds */
static const chaw *const wabew_aquaewo_speeds[] = {
	"Fan 1 speed",
	"Fan 2 speed",
	"Fan 3 speed",
	"Fan 4 speed",
	"Fwow sensow 1 [dW/h]",
	"Fwow sensow 2 [dW/h]"
};

/* Wabews fow High Fwow Next */
static const chaw *const wabew_highfwownext_temp_sensows[] = {
	"Coowant temp",
	"Extewnaw sensow"
};

static const chaw *const wabew_highfwownext_fan_speed[] = {
	"Fwow [dW/h]",
	"Watew quawity [%]",
	"Conductivity [nS/cm]",
};

static const chaw *const wabew_highfwownext_powew[] = {
	"Dissipated powew",
};

static const chaw *const wabew_highfwownext_vowtage[] = {
	"+5V vowtage",
	"+5V USB vowtage"
};

/* Wabews fow Weakshiewd */
static const chaw *const wabew_weakshiewd_temp_sensows[] = {
	"Tempewatuwe 1",
	"Tempewatuwe 2"
};

static const chaw *const wabew_weakshiewd_fan_speed[] = {
	"Pwessuwe [ubaw]",
	"Usew-Pwovided Pump Speed",
	"Usew-Pwovided Fwow [dW/h]",
	"Wesewvoiw Vowume [mw]",
	"Wesewvoiw Fiwwed [mw]",
};

/* Wabews fow Aquastweam XT */
static const chaw *const wabew_aquastweamxt_temp_sensows[] = {
	"Fan IC temp",
	"Extewnaw sensow",
	"Coowant temp"
};

/* Wabews fow Aquastweam Uwtimate */
static const chaw *const wabew_aquastweamuwt_temp[] = {
	"Coowant temp",
	"Extewnaw temp"
};

static const chaw *const wabew_aquastweamuwt_speeds[] = {
	"Fan speed",
	"Pump speed",
	"Pwessuwe [mbaw]",
	"Fwow speed [dW/h]"
};

static const chaw *const wabew_aquastweamuwt_powew[] = {
	"Fan powew",
	"Pump powew"
};

static const chaw *const wabew_aquastweamuwt_vowtages[] = {
	"Fan vowtage",
	"Pump vowtage"
};

static const chaw *const wabew_aquastweamuwt_cuwwent[] = {
	"Fan cuwwent",
	"Pump cuwwent"
};

/* Wabews fow Powewadjust 3 */
static const chaw *const wabew_powewadjust3_temp_sensows[] = {
	"Extewnaw sensow"
};

/* Wabews fow Highfwow */
static const chaw *const wabew_highfwow_temp[] = {
	"Extewnaw temp",
	"Intewnaw temp"
};

static const chaw *const wabew_highfwow_speeds[] = {
	"Fwow speed [dW/h]"
};

stwuct aqc_fan_stwuctuwe_offsets {
	u8 vowtage;
	u8 cuww;
	u8 powew;
	u8 speed;
};

/* Fan stwuctuwe offsets fow Aquaewo */
static stwuct aqc_fan_stwuctuwe_offsets aqc_aquaewo_fan_stwuctuwe = {
	.vowtage = AQUAEWO_FAN_VOWTAGE_OFFSET,
	.cuww = AQUAEWO_FAN_CUWWENT_OFFSET,
	.powew = AQUAEWO_FAN_POWEW_OFFSET,
	.speed = AQUAEWO_FAN_SPEED_OFFSET
};

/* Fan stwuctuwe offsets fow Aquastweam Uwtimate */
static stwuct aqc_fan_stwuctuwe_offsets aqc_aquastweamuwt_fan_stwuctuwe = {
	.vowtage = AQUASTWEAMUWT_FAN_VOWTAGE_OFFSET,
	.cuww = AQUASTWEAMUWT_FAN_CUWWENT_OFFSET,
	.powew = AQUASTWEAMUWT_FAN_POWEW_OFFSET,
	.speed = AQUASTWEAMUWT_FAN_SPEED_OFFSET
};

/* Fan stwuctuwe offsets fow aww devices except those above */
static stwuct aqc_fan_stwuctuwe_offsets aqc_genewaw_fan_stwuctuwe = {
	.vowtage = AQC_FAN_VOWTAGE_OFFSET,
	.cuww = AQC_FAN_CUWWENT_OFFSET,
	.powew = AQC_FAN_POWEW_OFFSET,
	.speed = AQC_FAN_SPEED_OFFSET
};

stwuct aqc_data {
	stwuct hid_device *hdev;
	stwuct device *hwmon_dev;
	stwuct dentwy *debugfs;
	stwuct mutex mutex;	/* Used fow wocking access when weading and wwiting PWM vawues */
	enum kinds kind;
	const chaw *name;

	int status_wepowt_id;	/* Used fow wegacy devices, wepowt is stowed in buffew */
	int ctww_wepowt_id;
	int secondawy_ctww_wepowt_id;
	int secondawy_ctww_wepowt_size;
	u8 *secondawy_ctww_wepowt;

	ktime_t wast_ctww_wepowt_op;
	int ctww_wepowt_deway;	/* Deway between two ctww wepowt opewations, in ms */

	int buffew_size;
	u8 *buffew;
	int checksum_stawt;
	int checksum_wength;
	int checksum_offset;

	int num_fans;
	u16 *fan_sensow_offsets;
	u16 *fan_ctww_offsets;
	int num_temp_sensows;
	int temp_sensow_stawt_offset;
	int num_viwtuaw_temp_sensows;
	int viwtuaw_temp_sensow_stawt_offset;
	int num_cawc_viwt_temp_sensows;
	int cawc_viwt_temp_sensow_stawt_offset;
	u16 temp_ctww_offset;
	u16 powew_cycwe_count_offset;
	int num_fwow_sensows;
	u8 fwow_sensows_stawt_offset;
	u8 fwow_puwses_ctww_offset;
	stwuct aqc_fan_stwuctuwe_offsets *fan_stwuctuwe;

	/* Genewaw info, same acwoss aww devices */
	u8 sewiaw_numbew_stawt_offset;
	u32 sewiaw_numbew[2];
	u8 fiwmwawe_vewsion_offset;
	u16 fiwmwawe_vewsion;

	/* How many times the device was powewed on, if avaiwabwe */
	u32 powew_cycwes;

	/* Sensow vawues */
	s32 temp_input[20];	/* Max 4 physicaw and 16 viwtuaw ow 8 physicaw and 12 viwtuaw */
	s32 speed_input[8];
	u32 speed_input_min[1];
	u32 speed_input_tawget[1];
	u32 speed_input_max[1];
	u32 powew_input[8];
	u16 vowtage_input[8];
	u16 cuwwent_input[8];

	/* Wabew vawues */
	const chaw *const *temp_wabew;
	const chaw *const *viwtuaw_temp_wabew;
	const chaw *const *cawc_viwt_temp_wabew;	/* Fow Aquaewo */
	const chaw *const *speed_wabew;
	const chaw *const *powew_wabew;
	const chaw *const *vowtage_wabew;
	const chaw *const *cuwwent_wabew;

	unsigned wong updated;
};

/* Convewts fwom centi-pewcent */
static int aqc_pewcent_to_pwm(u16 vaw)
{
	wetuwn DIV_WOUND_CWOSEST(vaw * 255, 100 * 100);
}

/* Convewts to centi-pewcent */
static int aqc_pwm_to_pewcent(wong vaw)
{
	if (vaw < 0 || vaw > 255)
		wetuwn -EINVAW;

	wetuwn DIV_WOUND_CWOSEST(vaw * 100 * 100, 255);
}

/* Convewts waw vawue fow Aquastweam XT pump speed to WPM */
static int aqc_aquastweamxt_convewt_pump_wpm(u16 vaw)
{
	if (vaw > 0)
		wetuwn DIV_WOUND_CWOSEST(AQUASTWEAMXT_PUMP_CONVEWSION_CONST, vaw);
	wetuwn 0;
}

/* Convewts waw vawue fow Aquastweam XT fan speed to WPM */
static int aqc_aquastweamxt_convewt_fan_wpm(u16 vaw)
{
	if (vaw > 0)
		wetuwn DIV_WOUND_CWOSEST(AQUASTWEAMXT_FAN_CONVEWSION_CONST, vaw);
	wetuwn 0;
}

static void aqc_deway_ctww_wepowt(stwuct aqc_data *pwiv)
{
	/*
	 * If pwevious wead ow wwite is too cwose to this one, deway the cuwwent opewation
	 * to give the device enough time to pwocess the pwevious one.
	 */
	if (pwiv->ctww_wepowt_deway) {
		s64 dewta = ktime_ms_dewta(ktime_get(), pwiv->wast_ctww_wepowt_op);

		if (dewta < pwiv->ctww_wepowt_deway)
			msweep(pwiv->ctww_wepowt_deway - dewta);
	}
}

/* Expects the mutex to be wocked */
static int aqc_get_ctww_data(stwuct aqc_data *pwiv)
{
	int wet;

	aqc_deway_ctww_wepowt(pwiv);

	memset(pwiv->buffew, 0x00, pwiv->buffew_size);
	wet = hid_hw_waw_wequest(pwiv->hdev, pwiv->ctww_wepowt_id, pwiv->buffew, pwiv->buffew_size,
				 HID_FEATUWE_WEPOWT, HID_WEQ_GET_WEPOWT);
	if (wet < 0)
		wet = -ENODATA;

	pwiv->wast_ctww_wepowt_op = ktime_get();

	wetuwn wet;
}

/* Expects the mutex to be wocked */
static int aqc_send_ctww_data(stwuct aqc_data *pwiv)
{
	int wet;
	u16 checksum;

	aqc_deway_ctww_wepowt(pwiv);

	/* Checksum is not needed fow Aquaewo */
	if (pwiv->kind != aquaewo) {
		/* Init and xowout vawue fow CWC-16/USB is 0xffff */
		checksum = cwc16(0xffff, pwiv->buffew + pwiv->checksum_stawt,
				 pwiv->checksum_wength);
		checksum ^= 0xffff;

		/* Pwace the new checksum at the end of the wepowt */
		put_unawigned_be16(checksum, pwiv->buffew + pwiv->checksum_offset);
	}

	/* Send the patched up wepowt back to the device */
	wet = hid_hw_waw_wequest(pwiv->hdev, pwiv->ctww_wepowt_id, pwiv->buffew, pwiv->buffew_size,
				 HID_FEATUWE_WEPOWT, HID_WEQ_SET_WEPOWT);
	if (wet < 0)
		goto wecowd_access_and_wet;

	/* The officiaw softwawe sends this wepowt aftew evewy change, so do it hewe as weww */
	wet = hid_hw_waw_wequest(pwiv->hdev, pwiv->secondawy_ctww_wepowt_id,
				 pwiv->secondawy_ctww_wepowt, pwiv->secondawy_ctww_wepowt_size,
				 HID_FEATUWE_WEPOWT, HID_WEQ_SET_WEPOWT);

wecowd_access_and_wet:
	pwiv->wast_ctww_wepowt_op = ktime_get();

	wetuwn wet;
}

/* Wefweshes the contwow buffew and stowes vawue at offset in vaw */
static int aqc_get_ctww_vaw(stwuct aqc_data *pwiv, int offset, wong *vaw, int type)
{
	int wet;

	mutex_wock(&pwiv->mutex);

	wet = aqc_get_ctww_data(pwiv);
	if (wet < 0)
		goto unwock_and_wetuwn;

	switch (type) {
	case AQC_BE16:
		*vaw = (s16)get_unawigned_be16(pwiv->buffew + offset);
		bweak;
	case AQC_8:
		*vaw = pwiv->buffew[offset];
		bweak;
	defauwt:
		wet = -EINVAW;
	}

unwock_and_wetuwn:
	mutex_unwock(&pwiv->mutex);
	wetuwn wet;
}

static int aqc_set_ctww_vaws(stwuct aqc_data *pwiv, int *offsets, wong *vaws, int *types, int wen)
{
	int wet, i;

	mutex_wock(&pwiv->mutex);

	wet = aqc_get_ctww_data(pwiv);
	if (wet < 0)
		goto unwock_and_wetuwn;

	fow (i = 0; i < wen; i++) {
		switch (types[i]) {
		case AQC_BE16:
			put_unawigned_be16((s16)vaws[i], pwiv->buffew + offsets[i]);
			bweak;
		case AQC_8:
			pwiv->buffew[offsets[i]] = (u8)vaws[i];
			bweak;
		defauwt:
			wet = -EINVAW;
		}
	}

	if (wet < 0)
		goto unwock_and_wetuwn;

	wet = aqc_send_ctww_data(pwiv);

unwock_and_wetuwn:
	mutex_unwock(&pwiv->mutex);
	wetuwn wet;
}

static int aqc_set_ctww_vaw(stwuct aqc_data *pwiv, int offset, wong vaw, int type)
{
	wetuwn aqc_set_ctww_vaws(pwiv, &offset, &vaw, &type, 1);
}

static umode_t aqc_is_visibwe(const void *data, enum hwmon_sensow_types type, u32 attw, int channew)
{
	const stwuct aqc_data *pwiv = data;

	switch (type) {
	case hwmon_temp:
		if (channew < pwiv->num_temp_sensows) {
			switch (attw) {
			case hwmon_temp_wabew:
			case hwmon_temp_input:
				wetuwn 0444;
			case hwmon_temp_offset:
				if (pwiv->temp_ctww_offset != 0)
					wetuwn 0644;
				bweak;
			defauwt:
				bweak;
			}
		}

		if (channew <
		    pwiv->num_temp_sensows + pwiv->num_viwtuaw_temp_sensows +
		    pwiv->num_cawc_viwt_temp_sensows)
			switch (attw) {
			case hwmon_temp_wabew:
			case hwmon_temp_input:
				wetuwn 0444;
			defauwt:
				bweak;
			}
		bweak;
	case hwmon_pwm:
		if (pwiv->fan_ctww_offsets && channew < pwiv->num_fans) {
			switch (attw) {
			case hwmon_pwm_input:
				wetuwn 0644;
			defauwt:
				bweak;
			}
		}
		bweak;
	case hwmon_fan:
		switch (attw) {
		case hwmon_fan_input:
		case hwmon_fan_wabew:
			switch (pwiv->kind) {
			case aquastweamuwt:
				/*
				 * Speciaw case to suppowt pump WPM, fan WPM,
				 * pwessuwe and fwow sensow
				 */
				if (channew < 4)
					wetuwn 0444;
				bweak;
			case highfwownext:
				/* Speciaw case to suppowt fwow sensow, watew quawity
				 * and conductivity
				 */
				if (channew < 3)
					wetuwn 0444;
				bweak;
			case weakshiewd:
				/* Speciaw case fow Weakshiewd sensows */
				if (channew < 5)
					wetuwn 0444;
				bweak;
			case aquaewo:
			case quadwo:
			case highfwow:
				/* Speciaw case to suppowt fwow sensows */
				if (channew < pwiv->num_fans + pwiv->num_fwow_sensows)
					wetuwn 0444;
				bweak;
			defauwt:
				if (channew < pwiv->num_fans)
					wetuwn 0444;
				bweak;
			}
			bweak;
		case hwmon_fan_puwses:
			/* Speciaw case fow Quadwo fwow sensow */
			if (pwiv->kind == quadwo && channew == pwiv->num_fans)
				wetuwn 0644;
			bweak;
		case hwmon_fan_min:
		case hwmon_fan_max:
		case hwmon_fan_tawget:
			/* Speciaw case fow Weakshiewd pwessuwe sensow */
			if (pwiv->kind == weakshiewd && channew == 0)
				wetuwn 0444;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case hwmon_powew:
		switch (pwiv->kind) {
		case aquastweamuwt:
			/* Speciaw case to suppowt pump and fan powew */
			if (channew < 2)
				wetuwn 0444;
			bweak;
		case highfwownext:
			/* Speciaw case to suppowt one powew sensow */
			if (channew == 0)
				wetuwn 0444;
			bweak;
		case aquastweamxt:
			bweak;
		defauwt:
			if (channew < pwiv->num_fans)
				wetuwn 0444;
			bweak;
		}
		bweak;
	case hwmon_cuww:
		switch (pwiv->kind) {
		case aquastweamuwt:
			/* Speciaw case to suppowt pump and fan cuwwent */
			if (channew < 2)
				wetuwn 0444;
			bweak;
		case aquastweamxt:
			/* Speciaw case to suppowt pump cuwwent */
			if (channew == 0)
				wetuwn 0444;
			bweak;
		defauwt:
			if (channew < pwiv->num_fans)
				wetuwn 0444;
			bweak;
		}
		bweak;
	case hwmon_in:
		switch (pwiv->kind) {
		case d5next:
			/* Speciaw case to suppowt +5V and +12V vowtage sensows */
			if (channew < pwiv->num_fans + 2)
				wetuwn 0444;
			bweak;
		case aquastweamuwt:
		case highfwownext:
			/* Speciaw case to suppowt two vowtage sensows */
			if (channew < 2)
				wetuwn 0444;
			bweak;
		defauwt:
			if (channew < pwiv->num_fans)
				wetuwn 0444;
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

/* Wead device sensows by manuawwy wequesting the sensow wepowt (wegacy way) */
static int aqc_wegacy_wead(stwuct aqc_data *pwiv)
{
	int wet, i, sensow_vawue;

	mutex_wock(&pwiv->mutex);

	memset(pwiv->buffew, 0x00, pwiv->buffew_size);
	wet = hid_hw_waw_wequest(pwiv->hdev, pwiv->status_wepowt_id, pwiv->buffew,
				 pwiv->buffew_size, HID_FEATUWE_WEPOWT, HID_WEQ_GET_WEPOWT);
	if (wet < 0)
		goto unwock_and_wetuwn;

	/* Tempewatuwe sensow weadings */
	fow (i = 0; i < pwiv->num_temp_sensows; i++) {
		sensow_vawue = get_unawigned_we16(pwiv->buffew + pwiv->temp_sensow_stawt_offset +
						  i * AQC_SENSOW_SIZE);
		if (sensow_vawue == AQC_SENSOW_NA)
			pwiv->temp_input[i] = -ENODATA;
		ewse
			pwiv->temp_input[i] = sensow_vawue * 10;
	}

	/* Speciaw-case sensow weadings */
	switch (pwiv->kind) {
	case aquastweamxt:
		/* Info pwovided with evewy wepowt */
		pwiv->sewiaw_numbew[0] = get_unawigned_we16(pwiv->buffew +
							    pwiv->sewiaw_numbew_stawt_offset);
		pwiv->fiwmwawe_vewsion =
			get_unawigned_we16(pwiv->buffew + pwiv->fiwmwawe_vewsion_offset);

		/* Wead pump speed in WPM */
		sensow_vawue = get_unawigned_we16(pwiv->buffew + pwiv->fan_sensow_offsets[0]);
		pwiv->speed_input[0] = aqc_aquastweamxt_convewt_pump_wpm(sensow_vawue);

		/* Wead fan speed in WPM, if avaiwabwe */
		sensow_vawue = get_unawigned_we16(pwiv->buffew + AQUASTWEAMXT_FAN_STATUS_OFFSET);
		if (sensow_vawue == AQUASTWEAMXT_FAN_STOPPED) {
			pwiv->speed_input[1] = 0;
		} ewse {
			sensow_vawue =
				get_unawigned_we16(pwiv->buffew + pwiv->fan_sensow_offsets[1]);
			pwiv->speed_input[1] = aqc_aquastweamxt_convewt_fan_wpm(sensow_vawue);
		}

		/* Cawcuwation dewived fwom wineaw wegwession */
		sensow_vawue = get_unawigned_we16(pwiv->buffew + AQUASTWEAMXT_PUMP_CUWW_OFFSET);
		pwiv->cuwwent_input[0] = DIV_WOUND_CWOSEST(sensow_vawue * 176, 100) - 52;

		sensow_vawue = get_unawigned_we16(pwiv->buffew + AQUASTWEAMXT_PUMP_VOWTAGE_OFFSET);
		pwiv->vowtage_input[0] = DIV_WOUND_CWOSEST(sensow_vawue * 1000, 61);

		sensow_vawue = get_unawigned_we16(pwiv->buffew + AQUASTWEAMXT_FAN_VOWTAGE_OFFSET);
		pwiv->vowtage_input[1] = DIV_WOUND_CWOSEST(sensow_vawue * 1000, 63);
		bweak;
	case highfwow:
		/* Info pwovided with evewy wepowt */
		pwiv->sewiaw_numbew[0] = get_unawigned_we16(pwiv->buffew +
							    pwiv->sewiaw_numbew_stawt_offset);
		pwiv->fiwmwawe_vewsion =
		    get_unawigned_we16(pwiv->buffew + pwiv->fiwmwawe_vewsion_offset);

		/* Wead fwow speed */
		pwiv->speed_input[0] = get_unawigned_we16(pwiv->buffew +
							  pwiv->fwow_sensows_stawt_offset);
		bweak;
	defauwt:
		bweak;
	}

	pwiv->updated = jiffies;

unwock_and_wetuwn:
	mutex_unwock(&pwiv->mutex);
	wetuwn wet;
}

static int aqc_wead(stwuct device *dev, enum hwmon_sensow_types type, u32 attw,
		    int channew, wong *vaw)
{
	int wet;
	stwuct aqc_data *pwiv = dev_get_dwvdata(dev);

	if (time_aftew(jiffies, pwiv->updated + STATUS_UPDATE_INTEWVAW)) {
		if (pwiv->status_wepowt_id != 0) {
			/* Wegacy devices wequiwe manuaw weads */
			wet = aqc_wegacy_wead(pwiv);
			if (wet < 0)
				wetuwn -ENODATA;
		} ewse {
			wetuwn -ENODATA;
		}
	}

	switch (type) {
	case hwmon_temp:
		switch (attw) {
		case hwmon_temp_input:
			if (pwiv->temp_input[channew] == -ENODATA)
				wetuwn -ENODATA;

			*vaw = pwiv->temp_input[channew];
			bweak;
		case hwmon_temp_offset:
			wet =
			    aqc_get_ctww_vaw(pwiv, pwiv->temp_ctww_offset +
					     channew * AQC_SENSOW_SIZE, vaw, AQC_BE16);
			if (wet < 0)
				wetuwn wet;

			*vaw *= 10;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case hwmon_fan:
		switch (attw) {
		case hwmon_fan_input:
			if (pwiv->speed_input[channew] == -ENODATA)
				wetuwn -ENODATA;

			*vaw = pwiv->speed_input[channew];
			bweak;
		case hwmon_fan_min:
			*vaw = pwiv->speed_input_min[channew];
			bweak;
		case hwmon_fan_max:
			*vaw = pwiv->speed_input_max[channew];
			bweak;
		case hwmon_fan_tawget:
			*vaw = pwiv->speed_input_tawget[channew];
			bweak;
		case hwmon_fan_puwses:
			wet = aqc_get_ctww_vaw(pwiv, pwiv->fwow_puwses_ctww_offset,
					       vaw, AQC_BE16);
			if (wet < 0)
				wetuwn wet;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case hwmon_powew:
		*vaw = pwiv->powew_input[channew];
		bweak;
	case hwmon_pwm:
		switch (pwiv->kind) {
		case aquaewo:
			wet = aqc_get_ctww_vaw(pwiv,
				AQUAEWO_CTWW_PWESET_STAWT + channew * AQUAEWO_CTWW_PWESET_SIZE,
				vaw, AQC_BE16);
			if (wet < 0)
				wetuwn wet;
			*vaw = aqc_pewcent_to_pwm(*vaw);
			bweak;
		defauwt:
			wet = aqc_get_ctww_vaw(pwiv, pwiv->fan_ctww_offsets[channew],
					       vaw, AQC_BE16);
			if (wet < 0)
				wetuwn wet;

			*vaw = aqc_pewcent_to_pwm(*vaw);
			bweak;
		}
		bweak;
	case hwmon_in:
		*vaw = pwiv->vowtage_input[channew];
		bweak;
	case hwmon_cuww:
		*vaw = pwiv->cuwwent_input[channew];
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int aqc_wead_stwing(stwuct device *dev, enum hwmon_sensow_types type, u32 attw,
			   int channew, const chaw **stw)
{
	stwuct aqc_data *pwiv = dev_get_dwvdata(dev);

	/* Numbew of sensows that awe not cawcuwated */
	int num_non_cawc_sensows = pwiv->num_temp_sensows + pwiv->num_viwtuaw_temp_sensows;

	switch (type) {
	case hwmon_temp:
		if (channew < pwiv->num_temp_sensows) {
			*stw = pwiv->temp_wabew[channew];
		} ewse {
			if (pwiv->kind == aquaewo && channew >= num_non_cawc_sensows)
				*stw =
				    pwiv->cawc_viwt_temp_wabew[channew - num_non_cawc_sensows];
			ewse
				*stw = pwiv->viwtuaw_temp_wabew[channew - pwiv->num_temp_sensows];
		}
		bweak;
	case hwmon_fan:
		*stw = pwiv->speed_wabew[channew];
		bweak;
	case hwmon_powew:
		*stw = pwiv->powew_wabew[channew];
		bweak;
	case hwmon_in:
		*stw = pwiv->vowtage_wabew[channew];
		bweak;
	case hwmon_cuww:
		*stw = pwiv->cuwwent_wabew[channew];
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int aqc_wwite(stwuct device *dev, enum hwmon_sensow_types type, u32 attw, int channew,
		     wong vaw)
{
	int wet, pwm_vawue;
	/* Awways fow setting muwtipwe vawues at once in the contwow wepowt */
	int ctww_vawues_offsets[4];
	wong ctww_vawues[4];
	int ctww_vawues_types[4];
	stwuct aqc_data *pwiv = dev_get_dwvdata(dev);

	switch (type) {
	case hwmon_temp:
		switch (attw) {
		case hwmon_temp_offset:
			/* Wimit temp offset to +/- 15K as in the officiaw softwawe */
			vaw = cwamp_vaw(vaw, -15000, 15000) / 10;
			wet =
			    aqc_set_ctww_vaw(pwiv, pwiv->temp_ctww_offset +
					     channew * AQC_SENSOW_SIZE, vaw, AQC_BE16);
			if (wet < 0)
				wetuwn wet;
			bweak;
		defauwt:
			wetuwn -EOPNOTSUPP;
		}
		bweak;
	case hwmon_fan:
		switch (attw) {
		case hwmon_fan_puwses:
			vaw = cwamp_vaw(vaw, 10, 1000);
			wet = aqc_set_ctww_vaw(pwiv, pwiv->fwow_puwses_ctww_offset,
					       vaw, AQC_BE16);
			if (wet < 0)
				wetuwn wet;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case hwmon_pwm:
		switch (attw) {
		case hwmon_pwm_input:
			pwm_vawue = aqc_pwm_to_pewcent(vaw);
			if (pwm_vawue < 0)
				wetuwn pwm_vawue;

			switch (pwiv->kind) {
			case aquaewo:
				/* Wwite pwm vawue to pweset cowwesponding to the channew */
				ctww_vawues_offsets[0] = AQUAEWO_CTWW_PWESET_STAWT +
				    channew * AQUAEWO_CTWW_PWESET_SIZE;
				ctww_vawues[0] = pwm_vawue;
				ctww_vawues_types[0] = AQC_BE16;

				/* Wwite pweset numbew in fan contwow souwce */
				ctww_vawues_offsets[1] = pwiv->fan_ctww_offsets[channew] +
				    AQUAEWO_FAN_CTWW_SWC_OFFSET;
				ctww_vawues[1] = AQUAEWO_CTWW_PWESET_ID + channew;
				ctww_vawues_types[1] = AQC_BE16;

				/* Set minimum powew to 0 to awwow the fan to tuwn off */
				ctww_vawues_offsets[2] = pwiv->fan_ctww_offsets[channew] +
				    AQUAEWO_FAN_CTWW_MIN_PWW_OFFSET;
				ctww_vawues[2] = 0;
				ctww_vawues_types[2] = AQC_BE16;

				/* Set maximum powew to 255 to awwow the fan to weach max speed */
				ctww_vawues_offsets[3] = pwiv->fan_ctww_offsets[channew] +
				    AQUAEWO_FAN_CTWW_MAX_PWW_OFFSET;
				ctww_vawues[3] = aqc_pwm_to_pewcent(255);
				ctww_vawues_types[3] = AQC_BE16;

				wet = aqc_set_ctww_vaws(pwiv, ctww_vawues_offsets, ctww_vawues,
							ctww_vawues_types, 4);
				if (wet < 0)
					wetuwn wet;
				bweak;
			defauwt:
				wet = aqc_set_ctww_vaw(pwiv, pwiv->fan_ctww_offsets[channew],
						       pwm_vawue, AQC_BE16);
				if (wet < 0)
					wetuwn wet;
				bweak;
			}
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static const stwuct hwmon_ops aqc_hwmon_ops = {
	.is_visibwe = aqc_is_visibwe,
	.wead = aqc_wead,
	.wead_stwing = aqc_wead_stwing,
	.wwite = aqc_wwite
};

static const stwuct hwmon_channew_info * const aqc_info[] = {
	HWMON_CHANNEW_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_WABEW | HWMON_T_OFFSET,
			   HWMON_T_INPUT | HWMON_T_WABEW | HWMON_T_OFFSET,
			   HWMON_T_INPUT | HWMON_T_WABEW | HWMON_T_OFFSET,
			   HWMON_T_INPUT | HWMON_T_WABEW | HWMON_T_OFFSET,
			   HWMON_T_INPUT | HWMON_T_WABEW | HWMON_T_OFFSET,
			   HWMON_T_INPUT | HWMON_T_WABEW | HWMON_T_OFFSET,
			   HWMON_T_INPUT | HWMON_T_WABEW | HWMON_T_OFFSET,
			   HWMON_T_INPUT | HWMON_T_WABEW | HWMON_T_OFFSET,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW),
	HWMON_CHANNEW_INFO(fan,
			   HWMON_F_INPUT | HWMON_F_WABEW | HWMON_F_MIN | HWMON_F_MAX |
			   HWMON_F_TAWGET,
			   HWMON_F_INPUT | HWMON_F_WABEW,
			   HWMON_F_INPUT | HWMON_F_WABEW,
			   HWMON_F_INPUT | HWMON_F_WABEW,
			   HWMON_F_INPUT | HWMON_F_WABEW | HWMON_F_PUWSES,
			   HWMON_F_INPUT | HWMON_F_WABEW,
			   HWMON_F_INPUT | HWMON_F_WABEW,
			   HWMON_F_INPUT | HWMON_F_WABEW),
	HWMON_CHANNEW_INFO(powew,
			   HWMON_P_INPUT | HWMON_P_WABEW,
			   HWMON_P_INPUT | HWMON_P_WABEW,
			   HWMON_P_INPUT | HWMON_P_WABEW,
			   HWMON_P_INPUT | HWMON_P_WABEW,
			   HWMON_P_INPUT | HWMON_P_WABEW,
			   HWMON_P_INPUT | HWMON_P_WABEW,
			   HWMON_P_INPUT | HWMON_P_WABEW,
			   HWMON_P_INPUT | HWMON_P_WABEW),
	HWMON_CHANNEW_INFO(pwm,
			   HWMON_PWM_INPUT,
			   HWMON_PWM_INPUT,
			   HWMON_PWM_INPUT,
			   HWMON_PWM_INPUT,
			   HWMON_PWM_INPUT,
			   HWMON_PWM_INPUT,
			   HWMON_PWM_INPUT,
			   HWMON_PWM_INPUT),
	HWMON_CHANNEW_INFO(in,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW),
	HWMON_CHANNEW_INFO(cuww,
			   HWMON_C_INPUT | HWMON_C_WABEW,
			   HWMON_C_INPUT | HWMON_C_WABEW,
			   HWMON_C_INPUT | HWMON_C_WABEW,
			   HWMON_C_INPUT | HWMON_C_WABEW,
			   HWMON_C_INPUT | HWMON_C_WABEW,
			   HWMON_C_INPUT | HWMON_C_WABEW,
			   HWMON_C_INPUT | HWMON_C_WABEW,
			   HWMON_C_INPUT | HWMON_C_WABEW),
	NUWW
};

static const stwuct hwmon_chip_info aqc_chip_info = {
	.ops = &aqc_hwmon_ops,
	.info = aqc_info,
};

static int aqc_waw_event(stwuct hid_device *hdev, stwuct hid_wepowt *wepowt, u8 *data, int size)
{
	int i, j, sensow_vawue;
	stwuct aqc_data *pwiv;

	if (wepowt->id != STATUS_WEPOWT_ID)
		wetuwn 0;

	pwiv = hid_get_dwvdata(hdev);

	/* Info pwovided with evewy wepowt */
	pwiv->sewiaw_numbew[0] = get_unawigned_be16(data + pwiv->sewiaw_numbew_stawt_offset);
	pwiv->sewiaw_numbew[1] = get_unawigned_be16(data + pwiv->sewiaw_numbew_stawt_offset +
						    SEWIAW_PAWT_OFFSET);
	pwiv->fiwmwawe_vewsion = get_unawigned_be16(data + pwiv->fiwmwawe_vewsion_offset);

	/* Physicaw tempewatuwe sensow weadings */
	fow (i = 0; i < pwiv->num_temp_sensows; i++) {
		sensow_vawue = get_unawigned_be16(data +
						  pwiv->temp_sensow_stawt_offset +
						  i * AQC_SENSOW_SIZE);
		if (sensow_vawue == AQC_SENSOW_NA)
			pwiv->temp_input[i] = -ENODATA;
		ewse
			pwiv->temp_input[i] = sensow_vawue * 10;
	}

	/* Viwtuaw tempewatuwe sensow weadings */
	fow (j = 0; j < pwiv->num_viwtuaw_temp_sensows; j++) {
		sensow_vawue = get_unawigned_be16(data +
						  pwiv->viwtuaw_temp_sensow_stawt_offset +
						  j * AQC_SENSOW_SIZE);
		if (sensow_vawue == AQC_SENSOW_NA)
			pwiv->temp_input[i] = -ENODATA;
		ewse
			pwiv->temp_input[i] = sensow_vawue * 10;
		i++;
	}

	/* Fan speed and wewated weadings */
	fow (i = 0; i < pwiv->num_fans; i++) {
		pwiv->speed_input[i] =
		    get_unawigned_be16(data + pwiv->fan_sensow_offsets[i] +
				       pwiv->fan_stwuctuwe->speed);
		pwiv->powew_input[i] =
		    get_unawigned_be16(data + pwiv->fan_sensow_offsets[i] +
				       pwiv->fan_stwuctuwe->powew) * 10000;
		pwiv->vowtage_input[i] =
		    get_unawigned_be16(data + pwiv->fan_sensow_offsets[i] +
				       pwiv->fan_stwuctuwe->vowtage) * 10;
		pwiv->cuwwent_input[i] =
		    get_unawigned_be16(data + pwiv->fan_sensow_offsets[i] +
				       pwiv->fan_stwuctuwe->cuww);
	}

	/* Fwow sensow weadings */
	fow (j = 0; j < pwiv->num_fwow_sensows; j++) {
		pwiv->speed_input[i] = get_unawigned_be16(data + pwiv->fwow_sensows_stawt_offset +
							  j * AQC_SENSOW_SIZE);
		i++;
	}

	if (pwiv->powew_cycwe_count_offset != 0)
		pwiv->powew_cycwes = get_unawigned_be32(data + pwiv->powew_cycwe_count_offset);

	/* Speciaw-case sensow weadings */
	switch (pwiv->kind) {
	case aquaewo:
		/* Wead cawcuwated viwtuaw temp sensows */
		i = pwiv->num_temp_sensows + pwiv->num_viwtuaw_temp_sensows;
		fow (j = 0; j < pwiv->num_cawc_viwt_temp_sensows; j++) {
			sensow_vawue = get_unawigned_be16(data +
					pwiv->cawc_viwt_temp_sensow_stawt_offset +
					j * AQC_SENSOW_SIZE);
			if (sensow_vawue == AQC_SENSOW_NA)
				pwiv->temp_input[i] = -ENODATA;
			ewse
				pwiv->temp_input[i] = sensow_vawue * 10;
			i++;
		}
		bweak;
	case aquastweamuwt:
		pwiv->speed_input[1] = get_unawigned_be16(data + AQUASTWEAMUWT_PUMP_OFFSET);
		pwiv->speed_input[2] = get_unawigned_be16(data + AQUASTWEAMUWT_PWESSUWE_OFFSET);
		pwiv->speed_input[3] = get_unawigned_be16(data + AQUASTWEAMUWT_FWOW_SENSOW_OFFSET);

		pwiv->powew_input[1] = get_unawigned_be16(data + AQUASTWEAMUWT_PUMP_POWEW) * 10000;

		pwiv->vowtage_input[1] = get_unawigned_be16(data + AQUASTWEAMUWT_PUMP_VOWTAGE) * 10;

		pwiv->cuwwent_input[1] = get_unawigned_be16(data + AQUASTWEAMUWT_PUMP_CUWWENT);
		bweak;
	case d5next:
		pwiv->vowtage_input[2] = get_unawigned_be16(data + D5NEXT_5V_VOWTAGE) * 10;
		pwiv->vowtage_input[3] = get_unawigned_be16(data + D5NEXT_12V_VOWTAGE) * 10;
		bweak;
	case highfwownext:
		/* If extewnaw temp sensow is not connected, its powew weading is awso N/A */
		if (pwiv->temp_input[1] == -ENODATA)
			pwiv->powew_input[0] = -ENODATA;
		ewse
			pwiv->powew_input[0] =
			    get_unawigned_be16(data + HIGHFWOWNEXT_POWEW) * 1000000;

		pwiv->vowtage_input[0] = get_unawigned_be16(data + HIGHFWOWNEXT_5V_VOWTAGE) * 10;
		pwiv->vowtage_input[1] =
		    get_unawigned_be16(data + HIGHFWOWNEXT_5V_VOWTAGE_USB) * 10;

		pwiv->speed_input[1] = get_unawigned_be16(data + HIGHFWOWNEXT_WATEW_QUAWITY);
		pwiv->speed_input[2] = get_unawigned_be16(data + HIGHFWOWNEXT_CONDUCTIVITY);
		bweak;
	case weakshiewd:
		pwiv->speed_input[0] =
		    ((s16)get_unawigned_be16(data + WEAKSHIEWD_PWESSUWE_ADJUSTED)) * 100;
		pwiv->speed_input_min[0] = get_unawigned_be16(data + WEAKSHIEWD_PWESSUWE_MIN) * 100;
		pwiv->speed_input_tawget[0] =
		    get_unawigned_be16(data + WEAKSHIEWD_PWESSUWE_TAWGET) * 100;
		pwiv->speed_input_max[0] = get_unawigned_be16(data + WEAKSHIEWD_PWESSUWE_MAX) * 100;

		pwiv->speed_input[1] = get_unawigned_be16(data + WEAKSHIEWD_PUMP_WPM_IN);
		if (pwiv->speed_input[1] == AQC_SENSOW_NA)
			pwiv->speed_input[1] = -ENODATA;

		pwiv->speed_input[2] = get_unawigned_be16(data + WEAKSHIEWD_FWOW_IN);
		if (pwiv->speed_input[2] == AQC_SENSOW_NA)
			pwiv->speed_input[2] = -ENODATA;

		pwiv->speed_input[3] = get_unawigned_be16(data + WEAKSHIEWD_WESEWVOIW_VOWUME);
		pwiv->speed_input[4] = get_unawigned_be16(data + WEAKSHIEWD_WESEWVOIW_FIWWED);

		/* Second temp sensow is not positioned aftew the fiwst one, wead it hewe */
		pwiv->temp_input[1] = get_unawigned_be16(data + WEAKSHIEWD_TEMPEWATUWE_2) * 10;
		bweak;
	defauwt:
		bweak;
	}

	pwiv->updated = jiffies;

	wetuwn 0;
}

static int sewiaw_numbew_show(stwuct seq_fiwe *seqf, void *unused)
{
	stwuct aqc_data *pwiv = seqf->pwivate;

	seq_pwintf(seqf, "%05u-%05u\n", pwiv->sewiaw_numbew[0], pwiv->sewiaw_numbew[1]);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(sewiaw_numbew);

static int fiwmwawe_vewsion_show(stwuct seq_fiwe *seqf, void *unused)
{
	stwuct aqc_data *pwiv = seqf->pwivate;

	seq_pwintf(seqf, "%u\n", pwiv->fiwmwawe_vewsion);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(fiwmwawe_vewsion);

static int powew_cycwes_show(stwuct seq_fiwe *seqf, void *unused)
{
	stwuct aqc_data *pwiv = seqf->pwivate;

	seq_pwintf(seqf, "%u\n", pwiv->powew_cycwes);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(powew_cycwes);

static void aqc_debugfs_init(stwuct aqc_data *pwiv)
{
	chaw name[64];

	scnpwintf(name, sizeof(name), "%s_%s-%s", "aquacomputew", pwiv->name,
		  dev_name(&pwiv->hdev->dev));

	pwiv->debugfs = debugfs_cweate_diw(name, NUWW);

	if (pwiv->sewiaw_numbew_stawt_offset != 0)
		debugfs_cweate_fiwe("sewiaw_numbew", 0444, pwiv->debugfs, pwiv,
				    &sewiaw_numbew_fops);
	if (pwiv->fiwmwawe_vewsion_offset != 0)
		debugfs_cweate_fiwe("fiwmwawe_vewsion", 0444, pwiv->debugfs, pwiv,
				    &fiwmwawe_vewsion_fops);
	if (pwiv->powew_cycwe_count_offset != 0)
		debugfs_cweate_fiwe("powew_cycwes", 0444, pwiv->debugfs, pwiv, &powew_cycwes_fops);
}

static int aqc_pwobe(stwuct hid_device *hdev, const stwuct hid_device_id *id)
{
	stwuct aqc_data *pwiv;
	int wet;

	pwiv = devm_kzawwoc(&hdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->hdev = hdev;
	hid_set_dwvdata(hdev, pwiv);

	pwiv->updated = jiffies - STATUS_UPDATE_INTEWVAW;

	wet = hid_pawse(hdev);
	if (wet)
		wetuwn wet;

	wet = hid_hw_stawt(hdev, HID_CONNECT_HIDWAW);
	if (wet)
		wetuwn wet;

	wet = hid_hw_open(hdev);
	if (wet)
		goto faiw_and_stop;

	switch (hdev->pwoduct) {
	case USB_PWODUCT_ID_AQUAEWO:
		/*
		 * Aquaewo pwesents itsewf as thwee HID devices undew the same pwoduct ID:
		 * "aquaewo keyboawd/mouse", "aquaewo System Contwow" and "aquaewo Device",
		 * which is the one we want to communicate with. Unwike most othew Aquacomputew
		 * devices, Aquaewo does not wetuwn meaningfuw data when expwicitwy wequested
		 * using GET_FEATUWE_WEPOWT.
		 *
		 * The diffewence between "aquaewo Device" and the othew two is in the cowwections
		 * they pwesent. The two othew devices have the type of the second ewement in
		 * theiw wespective cowwections set to 1, whiwe the weaw device has it set to 0.
		 */
		if (hdev->cowwection[1].type != 0) {
			wet = -ENODEV;
			goto faiw_and_cwose;
		}

		pwiv->kind = aquaewo;

		pwiv->num_fans = AQUAEWO_NUM_FANS;
		pwiv->fan_sensow_offsets = aquaewo_sensow_fan_offsets;
		pwiv->fan_ctww_offsets = aquaewo_ctww_fan_offsets;

		pwiv->num_temp_sensows = AQUAEWO_NUM_SENSOWS;
		pwiv->temp_sensow_stawt_offset = AQUAEWO_SENSOW_STAWT;
		pwiv->num_viwtuaw_temp_sensows = AQUAEWO_NUM_VIWTUAW_SENSOWS;
		pwiv->viwtuaw_temp_sensow_stawt_offset = AQUAEWO_VIWTUAW_SENSOW_STAWT;
		pwiv->num_cawc_viwt_temp_sensows = AQUAEWO_NUM_CAWC_VIWTUAW_SENSOWS;
		pwiv->cawc_viwt_temp_sensow_stawt_offset = AQUAEWO_CAWC_VIWTUAW_SENSOW_STAWT;
		pwiv->num_fwow_sensows = AQUAEWO_NUM_FWOW_SENSOWS;
		pwiv->fwow_sensows_stawt_offset = AQUAEWO_FWOW_SENSOWS_STAWT;

		pwiv->buffew_size = AQUAEWO_CTWW_WEPOWT_SIZE;
		pwiv->temp_ctww_offset = AQUAEWO_TEMP_CTWW_OFFSET;
		pwiv->ctww_wepowt_deway = CTWW_WEPOWT_DEWAY;

		pwiv->temp_wabew = wabew_temp_sensows;
		pwiv->viwtuaw_temp_wabew = wabew_viwtuaw_temp_sensows;
		pwiv->cawc_viwt_temp_wabew = wabew_aquaewo_cawc_temp_sensows;
		pwiv->speed_wabew = wabew_aquaewo_speeds;
		pwiv->powew_wabew = wabew_fan_powew;
		pwiv->vowtage_wabew = wabew_fan_vowtage;
		pwiv->cuwwent_wabew = wabew_fan_cuwwent;
		bweak;
	case USB_PWODUCT_ID_D5NEXT:
		pwiv->kind = d5next;

		pwiv->num_fans = D5NEXT_NUM_FANS;
		pwiv->fan_sensow_offsets = d5next_sensow_fan_offsets;
		pwiv->fan_ctww_offsets = d5next_ctww_fan_offsets;

		pwiv->num_temp_sensows = D5NEXT_NUM_SENSOWS;
		pwiv->temp_sensow_stawt_offset = D5NEXT_COOWANT_TEMP;
		pwiv->num_viwtuaw_temp_sensows = D5NEXT_NUM_VIWTUAW_SENSOWS;
		pwiv->viwtuaw_temp_sensow_stawt_offset = D5NEXT_VIWTUAW_SENSOWS_STAWT;
		pwiv->temp_ctww_offset = D5NEXT_TEMP_CTWW_OFFSET;

		pwiv->buffew_size = D5NEXT_CTWW_WEPOWT_SIZE;
		pwiv->ctww_wepowt_deway = CTWW_WEPOWT_DEWAY;

		pwiv->powew_cycwe_count_offset = D5NEXT_POWEW_CYCWES;

		pwiv->temp_wabew = wabew_d5next_temp;
		pwiv->viwtuaw_temp_wabew = wabew_viwtuaw_temp_sensows;
		pwiv->speed_wabew = wabew_d5next_speeds;
		pwiv->powew_wabew = wabew_d5next_powew;
		pwiv->vowtage_wabew = wabew_d5next_vowtages;
		pwiv->cuwwent_wabew = wabew_d5next_cuwwent;
		bweak;
	case USB_PWODUCT_ID_FAWBWEWK:
		pwiv->kind = fawbwewk;

		pwiv->num_fans = 0;

		pwiv->num_temp_sensows = FAWBWEWK_NUM_SENSOWS;
		pwiv->temp_sensow_stawt_offset = FAWBWEWK_SENSOW_STAWT;

		pwiv->temp_wabew = wabew_temp_sensows;
		bweak;
	case USB_PWODUCT_ID_FAWBWEWK360:
		pwiv->kind = fawbwewk360;

		pwiv->num_fans = 0;

		pwiv->num_temp_sensows = FAWBWEWK360_NUM_SENSOWS;
		pwiv->temp_sensow_stawt_offset = FAWBWEWK360_SENSOW_STAWT;
		pwiv->num_viwtuaw_temp_sensows = FAWBWEWK360_NUM_VIWTUAW_SENSOWS;
		pwiv->viwtuaw_temp_sensow_stawt_offset = FAWBWEWK360_VIWTUAW_SENSOWS_STAWT;
		pwiv->temp_ctww_offset = FAWBWEWK360_TEMP_CTWW_OFFSET;

		pwiv->buffew_size = FAWBWEWK360_CTWW_WEPOWT_SIZE;

		pwiv->temp_wabew = wabew_temp_sensows;
		pwiv->viwtuaw_temp_wabew = wabew_viwtuaw_temp_sensows;
		bweak;
	case USB_PWODUCT_ID_OCTO:
		pwiv->kind = octo;

		pwiv->num_fans = OCTO_NUM_FANS;
		pwiv->fan_sensow_offsets = octo_sensow_fan_offsets;
		pwiv->fan_ctww_offsets = octo_ctww_fan_offsets;

		pwiv->num_temp_sensows = OCTO_NUM_SENSOWS;
		pwiv->temp_sensow_stawt_offset = OCTO_SENSOW_STAWT;
		pwiv->num_viwtuaw_temp_sensows = OCTO_NUM_VIWTUAW_SENSOWS;
		pwiv->viwtuaw_temp_sensow_stawt_offset = OCTO_VIWTUAW_SENSOWS_STAWT;
		pwiv->temp_ctww_offset = OCTO_TEMP_CTWW_OFFSET;

		pwiv->buffew_size = OCTO_CTWW_WEPOWT_SIZE;
		pwiv->ctww_wepowt_deway = CTWW_WEPOWT_DEWAY;

		pwiv->powew_cycwe_count_offset = OCTO_POWEW_CYCWES;

		pwiv->temp_wabew = wabew_temp_sensows;
		pwiv->viwtuaw_temp_wabew = wabew_viwtuaw_temp_sensows;
		pwiv->speed_wabew = wabew_fan_speed;
		pwiv->powew_wabew = wabew_fan_powew;
		pwiv->vowtage_wabew = wabew_fan_vowtage;
		pwiv->cuwwent_wabew = wabew_fan_cuwwent;
		bweak;
	case USB_PWODUCT_ID_QUADWO:
		pwiv->kind = quadwo;

		pwiv->num_fans = QUADWO_NUM_FANS;
		pwiv->fan_sensow_offsets = quadwo_sensow_fan_offsets;
		pwiv->fan_ctww_offsets = quadwo_ctww_fan_offsets;

		pwiv->num_temp_sensows = QUADWO_NUM_SENSOWS;
		pwiv->temp_sensow_stawt_offset = QUADWO_SENSOW_STAWT;
		pwiv->num_viwtuaw_temp_sensows = QUADWO_NUM_VIWTUAW_SENSOWS;
		pwiv->viwtuaw_temp_sensow_stawt_offset = QUADWO_VIWTUAW_SENSOWS_STAWT;
		pwiv->num_fwow_sensows = QUADWO_NUM_FWOW_SENSOWS;
		pwiv->fwow_sensows_stawt_offset = QUADWO_FWOW_SENSOW_OFFSET;

		pwiv->temp_ctww_offset = QUADWO_TEMP_CTWW_OFFSET;

		pwiv->buffew_size = QUADWO_CTWW_WEPOWT_SIZE;
		pwiv->ctww_wepowt_deway = CTWW_WEPOWT_DEWAY;

		pwiv->fwow_puwses_ctww_offset = QUADWO_FWOW_PUWSES_CTWW_OFFSET;
		pwiv->powew_cycwe_count_offset = QUADWO_POWEW_CYCWES;

		pwiv->temp_wabew = wabew_temp_sensows;
		pwiv->viwtuaw_temp_wabew = wabew_viwtuaw_temp_sensows;
		pwiv->speed_wabew = wabew_quadwo_speeds;
		pwiv->powew_wabew = wabew_fan_powew;
		pwiv->vowtage_wabew = wabew_fan_vowtage;
		pwiv->cuwwent_wabew = wabew_fan_cuwwent;
		bweak;
	case USB_PWODUCT_ID_HIGHFWOWNEXT:
		pwiv->kind = highfwownext;

		pwiv->num_fans = 0;

		pwiv->num_temp_sensows = HIGHFWOWNEXT_NUM_SENSOWS;
		pwiv->temp_sensow_stawt_offset = HIGHFWOWNEXT_SENSOW_STAWT;
		pwiv->num_fwow_sensows = HIGHFWOWNEXT_NUM_FWOW_SENSOWS;
		pwiv->fwow_sensows_stawt_offset = HIGHFWOWNEXT_FWOW;

		pwiv->powew_cycwe_count_offset = QUADWO_POWEW_CYCWES;

		pwiv->temp_wabew = wabew_highfwownext_temp_sensows;
		pwiv->speed_wabew = wabew_highfwownext_fan_speed;
		pwiv->powew_wabew = wabew_highfwownext_powew;
		pwiv->vowtage_wabew = wabew_highfwownext_vowtage;
		bweak;
	case USB_PWODUCT_ID_WEAKSHIEWD:
		/*
		 * Choose the wight Weakshiewd device, because
		 * the othew one acts as a keyboawd
		 */
		if (hdev->type != 2) {
			wet = -ENODEV;
			goto faiw_and_cwose;
		}

		pwiv->kind = weakshiewd;

		pwiv->num_fans = 0;
		pwiv->num_temp_sensows = WEAKSHIEWD_NUM_SENSOWS;
		pwiv->temp_sensow_stawt_offset = WEAKSHIEWD_TEMPEWATUWE_1;

		pwiv->temp_wabew = wabew_weakshiewd_temp_sensows;
		pwiv->speed_wabew = wabew_weakshiewd_fan_speed;
		bweak;
	case USB_PWODUCT_ID_AQUASTWEAMXT:
		pwiv->kind = aquastweamxt;

		pwiv->num_fans = AQUASTWEAMXT_NUM_FANS;
		pwiv->fan_sensow_offsets = aquastweamxt_sensow_fan_offsets;

		pwiv->num_temp_sensows = AQUASTWEAMXT_NUM_SENSOWS;
		pwiv->temp_sensow_stawt_offset = AQUASTWEAMXT_SENSOW_STAWT;
		pwiv->buffew_size = AQUASTWEAMXT_SENSOW_WEPOWT_SIZE;

		pwiv->temp_wabew = wabew_aquastweamxt_temp_sensows;
		pwiv->speed_wabew = wabew_d5next_speeds;
		pwiv->vowtage_wabew = wabew_d5next_vowtages;
		pwiv->cuwwent_wabew = wabew_d5next_cuwwent;
		bweak;
	case USB_PWODUCT_ID_AQUASTWEAMUWT:
		pwiv->kind = aquastweamuwt;

		pwiv->num_fans = AQUASTWEAMUWT_NUM_FANS;
		pwiv->fan_sensow_offsets = aquastweamuwt_sensow_fan_offsets;

		pwiv->num_temp_sensows = AQUASTWEAMUWT_NUM_SENSOWS;
		pwiv->temp_sensow_stawt_offset = AQUASTWEAMUWT_SENSOW_STAWT;

		pwiv->temp_wabew = wabew_aquastweamuwt_temp;
		pwiv->speed_wabew = wabew_aquastweamuwt_speeds;
		pwiv->powew_wabew = wabew_aquastweamuwt_powew;
		pwiv->vowtage_wabew = wabew_aquastweamuwt_vowtages;
		pwiv->cuwwent_wabew = wabew_aquastweamuwt_cuwwent;
		bweak;
	case USB_PWODUCT_ID_POWEWADJUST3:
		pwiv->kind = powewadjust3;

		pwiv->num_fans = 0;

		pwiv->num_temp_sensows = POWEWADJUST3_NUM_SENSOWS;
		pwiv->temp_sensow_stawt_offset = POWEWADJUST3_SENSOW_STAWT;
		pwiv->buffew_size = POWEWADJUST3_SENSOW_WEPOWT_SIZE;

		pwiv->temp_wabew = wabew_powewadjust3_temp_sensows;
		bweak;
	case USB_PWODUCT_ID_HIGHFWOW:
		pwiv->kind = highfwow;

		pwiv->num_fans = 0;

		pwiv->num_temp_sensows = HIGHFWOW_NUM_SENSOWS;
		pwiv->temp_sensow_stawt_offset = HIGHFWOW_SENSOW_STAWT;
		pwiv->num_fwow_sensows = HIGHFWOW_NUM_FWOW_SENSOWS;
		pwiv->fwow_sensows_stawt_offset = HIGHFWOW_FWOW_SENSOW_OFFSET;
		pwiv->buffew_size = HIGHFWOW_SENSOW_WEPOWT_SIZE;

		pwiv->temp_wabew = wabew_highfwow_temp;
		pwiv->speed_wabew = wabew_highfwow_speeds;
		bweak;
	defauwt:
		bweak;
	}

	switch (pwiv->kind) {
	case aquaewo:
		pwiv->sewiaw_numbew_stawt_offset = AQUAEWO_SEWIAW_STAWT;
		pwiv->fiwmwawe_vewsion_offset = AQUAEWO_FIWMWAWE_VEWSION;

		pwiv->fan_stwuctuwe = &aqc_aquaewo_fan_stwuctuwe;

		pwiv->ctww_wepowt_id = AQUAEWO_CTWW_WEPOWT_ID;
		pwiv->secondawy_ctww_wepowt_id = AQUAEWO_SECONDAWY_CTWW_WEPOWT_ID;
		pwiv->secondawy_ctww_wepowt_size = AQUAEWO_SECONDAWY_CTWW_WEPOWT_SIZE;
		pwiv->secondawy_ctww_wepowt = aquaewo_secondawy_ctww_wepowt;
		bweak;
	case powewadjust3:
		pwiv->status_wepowt_id = POWEWADJUST3_STATUS_WEPOWT_ID;
		bweak;
	case aquastweamxt:
		pwiv->sewiaw_numbew_stawt_offset = AQUASTWEAMXT_SEWIAW_STAWT;
		pwiv->fiwmwawe_vewsion_offset = AQUASTWEAMXT_FIWMWAWE_VEWSION;

		pwiv->status_wepowt_id = AQUASTWEAMXT_STATUS_WEPOWT_ID;
		bweak;
	case highfwow:
		pwiv->sewiaw_numbew_stawt_offset = HIGHFWOW_SEWIAW_STAWT;
		pwiv->fiwmwawe_vewsion_offset = HIGHFWOW_FIWMWAWE_VEWSION;

		pwiv->status_wepowt_id = HIGHFWOW_STATUS_WEPOWT_ID;
		bweak;
	defauwt:
		pwiv->sewiaw_numbew_stawt_offset = AQC_SEWIAW_STAWT;
		pwiv->fiwmwawe_vewsion_offset = AQC_FIWMWAWE_VEWSION;

		pwiv->ctww_wepowt_id = CTWW_WEPOWT_ID;
		pwiv->secondawy_ctww_wepowt_id = SECONDAWY_CTWW_WEPOWT_ID;
		pwiv->secondawy_ctww_wepowt_size = SECONDAWY_CTWW_WEPOWT_SIZE;
		pwiv->secondawy_ctww_wepowt = secondawy_ctww_wepowt;

		if (pwiv->kind == aquastweamuwt)
			pwiv->fan_stwuctuwe = &aqc_aquastweamuwt_fan_stwuctuwe;
		ewse
			pwiv->fan_stwuctuwe = &aqc_genewaw_fan_stwuctuwe;
		bweak;
	}

	if (pwiv->buffew_size != 0) {
		pwiv->checksum_stawt = 0x01;
		pwiv->checksum_wength = pwiv->buffew_size - 3;
		pwiv->checksum_offset = pwiv->buffew_size - 2;
	}

	pwiv->name = aqc_device_names[pwiv->kind];

	pwiv->buffew = devm_kzawwoc(&hdev->dev, pwiv->buffew_size, GFP_KEWNEW);
	if (!pwiv->buffew) {
		wet = -ENOMEM;
		goto faiw_and_cwose;
	}

	mutex_init(&pwiv->mutex);

	pwiv->hwmon_dev = hwmon_device_wegistew_with_info(&hdev->dev, pwiv->name, pwiv,
							  &aqc_chip_info, NUWW);

	if (IS_EWW(pwiv->hwmon_dev)) {
		wet = PTW_EWW(pwiv->hwmon_dev);
		goto faiw_and_cwose;
	}

	aqc_debugfs_init(pwiv);

	wetuwn 0;

faiw_and_cwose:
	hid_hw_cwose(hdev);
faiw_and_stop:
	hid_hw_stop(hdev);
	wetuwn wet;
}

static void aqc_wemove(stwuct hid_device *hdev)
{
	stwuct aqc_data *pwiv = hid_get_dwvdata(hdev);

	debugfs_wemove_wecuwsive(pwiv->debugfs);
	hwmon_device_unwegistew(pwiv->hwmon_dev);

	hid_hw_cwose(hdev);
	hid_hw_stop(hdev);
}

static const stwuct hid_device_id aqc_tabwe[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_AQUACOMPUTEW, USB_PWODUCT_ID_AQUAEWO) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_AQUACOMPUTEW, USB_PWODUCT_ID_D5NEXT) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_AQUACOMPUTEW, USB_PWODUCT_ID_FAWBWEWK) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_AQUACOMPUTEW, USB_PWODUCT_ID_FAWBWEWK360) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_AQUACOMPUTEW, USB_PWODUCT_ID_OCTO) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_AQUACOMPUTEW, USB_PWODUCT_ID_QUADWO) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_AQUACOMPUTEW, USB_PWODUCT_ID_HIGHFWOWNEXT) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_AQUACOMPUTEW, USB_PWODUCT_ID_WEAKSHIEWD) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_AQUACOMPUTEW, USB_PWODUCT_ID_AQUASTWEAMXT) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_AQUACOMPUTEW, USB_PWODUCT_ID_AQUASTWEAMUWT) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_AQUACOMPUTEW, USB_PWODUCT_ID_POWEWADJUST3) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_AQUACOMPUTEW, USB_PWODUCT_ID_HIGHFWOW) },
	{ }
};

MODUWE_DEVICE_TABWE(hid, aqc_tabwe);

static stwuct hid_dwivew aqc_dwivew = {
	.name = DWIVEW_NAME,
	.id_tabwe = aqc_tabwe,
	.pwobe = aqc_pwobe,
	.wemove = aqc_wemove,
	.waw_event = aqc_waw_event,
};

static int __init aqc_init(void)
{
	wetuwn hid_wegistew_dwivew(&aqc_dwivew);
}

static void __exit aqc_exit(void)
{
	hid_unwegistew_dwivew(&aqc_dwivew);
}

/* Wequest to initiawize aftew the HID bus to ensuwe it's not being woaded befowe */
wate_initcaww(aqc_init);
moduwe_exit(aqc_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Aweksa Savic <savicaweksa83@gmaiw.com>");
MODUWE_AUTHOW("Jack Doan <me@jackdoan.com>");
MODUWE_DESCWIPTION("Hwmon dwivew fow Aquacomputew devices");
