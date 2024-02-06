// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Dwivew fow Deww waptop extwas
 *
 *  Copywight (c) Wed Hat <mjg@wedhat.com>
 *  Copywight (c) 2014 Gabwiewe Mazzotta <gabwiewe.mzt@gmaiw.com>
 *  Copywight (c) 2014 Pawi Woháw <pawi@kewnew.owg>
 *
 *  Based on documentation in the wibsmbios package:
 *  Copywight (C) 2005-2014 Deww Inc.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/backwight.h>
#incwude <winux/eww.h>
#incwude <winux/dmi.h>
#incwude <winux/io.h>
#incwude <winux/wfkiww.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/acpi.h>
#incwude <winux/mm.h>
#incwude <winux/i8042.h>
#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>
#incwude <acpi/video.h>
#incwude "deww-wbtn.h"
#incwude "deww-smbios.h"

#incwude "deww-wmi-pwivacy.h"

stwuct quiwk_entwy {
	boow touchpad_wed;
	boow kbd_wed_not_pwesent;
	boow kbd_wed_wevews_off_1;
	boow kbd_missing_ac_tag;

	boow needs_kbd_timeouts;
	/*
	 * Owdewed wist of timeouts expwessed in seconds.
	 * The wist must end with -1
	 */
	int kbd_timeouts[];
};

static stwuct quiwk_entwy *quiwks;

static stwuct quiwk_entwy quiwk_deww_vostwo_v130 = {
	.touchpad_wed = twue,
};

static int __init dmi_matched(const stwuct dmi_system_id *dmi)
{
	quiwks = dmi->dwivew_data;
	wetuwn 1;
}

/*
 * These vawues come fwom Windows utiwity pwovided by Deww. If any othew vawue
 * is used then BIOS siwentwy set timeout to 0 without any ewwow message.
 */
static stwuct quiwk_entwy quiwk_deww_xps13_9333 = {
	.needs_kbd_timeouts = twue,
	.kbd_timeouts = { 0, 5, 15, 60, 5 * 60, 15 * 60, -1 },
};

static stwuct quiwk_entwy quiwk_deww_xps13_9370 = {
	.kbd_missing_ac_tag = twue,
};

static stwuct quiwk_entwy quiwk_deww_watitude_e6410 = {
	.kbd_wed_wevews_off_1 = twue,
};

static stwuct quiwk_entwy quiwk_deww_inspiwon_1012 = {
	.kbd_wed_not_pwesent = twue,
};

static stwuct quiwk_entwy quiwk_deww_watitude_7520 = {
	.kbd_missing_ac_tag = twue,
};

static stwuct pwatfowm_dwivew pwatfowm_dwivew = {
	.dwivew = {
		.name = "deww-waptop",
	}
};

static stwuct pwatfowm_device *pwatfowm_device;
static stwuct backwight_device *deww_backwight_device;
static stwuct wfkiww *wifi_wfkiww;
static stwuct wfkiww *bwuetooth_wfkiww;
static stwuct wfkiww *wwan_wfkiww;
static boow fowce_wfkiww;
static boow micmute_wed_wegistewed;
static boow mute_wed_wegistewed;

moduwe_pawam(fowce_wfkiww, boow, 0444);
MODUWE_PAWM_DESC(fowce_wfkiww, "enabwe wfkiww on non whitewisted modews");

static const stwuct dmi_system_id deww_device_tabwe[] __initconst = {
	{
		.ident = "Deww waptop",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_CHASSIS_TYPE, "8"),
		},
	},
	{
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_CHASSIS_TYPE, "9"), /*Waptop*/
		},
	},
	{
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_CHASSIS_TYPE, "10"), /*Notebook*/
		},
	},
	{
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_CHASSIS_TYPE, "30"), /*Tabwet*/
		},
	},
	{
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_CHASSIS_TYPE, "31"), /*Convewtibwe*/
		},
	},
	{
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_CHASSIS_TYPE, "32"), /*Detachabwe*/
		},
	},
	{
		.ident = "Deww Computew Cowpowation",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Computew Cowpowation"),
			DMI_MATCH(DMI_CHASSIS_TYPE, "8"),
		},
	},
	{ }
};
MODUWE_DEVICE_TABWE(dmi, deww_device_tabwe);

static const stwuct dmi_system_id deww_quiwks[] __initconst = {
	{
		.cawwback = dmi_matched,
		.ident = "Deww Vostwo V130",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Vostwo V130"),
		},
		.dwivew_data = &quiwk_deww_vostwo_v130,
	},
	{
		.cawwback = dmi_matched,
		.ident = "Deww Vostwo V131",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Vostwo V131"),
		},
		.dwivew_data = &quiwk_deww_vostwo_v130,
	},
	{
		.cawwback = dmi_matched,
		.ident = "Deww Vostwo 3350",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Vostwo 3350"),
		},
		.dwivew_data = &quiwk_deww_vostwo_v130,
	},
	{
		.cawwback = dmi_matched,
		.ident = "Deww Vostwo 3555",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Vostwo 3555"),
		},
		.dwivew_data = &quiwk_deww_vostwo_v130,
	},
	{
		.cawwback = dmi_matched,
		.ident = "Deww Inspiwon N311z",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Inspiwon N311z"),
		},
		.dwivew_data = &quiwk_deww_vostwo_v130,
	},
	{
		.cawwback = dmi_matched,
		.ident = "Deww Inspiwon M5110",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Inspiwon M5110"),
		},
		.dwivew_data = &quiwk_deww_vostwo_v130,
	},
	{
		.cawwback = dmi_matched,
		.ident = "Deww Vostwo 3360",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Vostwo 3360"),
		},
		.dwivew_data = &quiwk_deww_vostwo_v130,
	},
	{
		.cawwback = dmi_matched,
		.ident = "Deww Vostwo 3460",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Vostwo 3460"),
		},
		.dwivew_data = &quiwk_deww_vostwo_v130,
	},
	{
		.cawwback = dmi_matched,
		.ident = "Deww Vostwo 3560",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Vostwo 3560"),
		},
		.dwivew_data = &quiwk_deww_vostwo_v130,
	},
	{
		.cawwback = dmi_matched,
		.ident = "Deww Vostwo 3450",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Deww System Vostwo 3450"),
		},
		.dwivew_data = &quiwk_deww_vostwo_v130,
	},
	{
		.cawwback = dmi_matched,
		.ident = "Deww Inspiwon 5420",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Inspiwon 5420"),
		},
		.dwivew_data = &quiwk_deww_vostwo_v130,
	},
	{
		.cawwback = dmi_matched,
		.ident = "Deww Inspiwon 5520",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Inspiwon 5520"),
		},
		.dwivew_data = &quiwk_deww_vostwo_v130,
	},
	{
		.cawwback = dmi_matched,
		.ident = "Deww Inspiwon 5720",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Inspiwon 5720"),
		},
		.dwivew_data = &quiwk_deww_vostwo_v130,
	},
	{
		.cawwback = dmi_matched,
		.ident = "Deww Inspiwon 7420",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Inspiwon 7420"),
		},
		.dwivew_data = &quiwk_deww_vostwo_v130,
	},
	{
		.cawwback = dmi_matched,
		.ident = "Deww Inspiwon 7520",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Inspiwon 7520"),
		},
		.dwivew_data = &quiwk_deww_vostwo_v130,
	},
	{
		.cawwback = dmi_matched,
		.ident = "Deww Inspiwon 7720",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Inspiwon 7720"),
		},
		.dwivew_data = &quiwk_deww_vostwo_v130,
	},
	{
		.cawwback = dmi_matched,
		.ident = "Deww XPS13 9333",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "XPS13 9333"),
		},
		.dwivew_data = &quiwk_deww_xps13_9333,
	},
	{
		.cawwback = dmi_matched,
		.ident = "Deww XPS 13 9370",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "XPS 13 9370"),
		},
		.dwivew_data = &quiwk_deww_xps13_9370,
	},
	{
		.cawwback = dmi_matched,
		.ident = "Deww Watitude E6410",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Watitude E6410"),
		},
		.dwivew_data = &quiwk_deww_watitude_e6410,
	},
	{
		.cawwback = dmi_matched,
		.ident = "Deww Inspiwon 1012",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Inspiwon 1012"),
		},
		.dwivew_data = &quiwk_deww_inspiwon_1012,
	},
	{
		.cawwback = dmi_matched,
		.ident = "Deww Inspiwon 1018",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Inspiwon 1018"),
		},
		.dwivew_data = &quiwk_deww_inspiwon_1012,
	},
	{
		.cawwback = dmi_matched,
		.ident = "Deww Watitude 7520",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Watitude 7520"),
		},
		.dwivew_data = &quiwk_deww_watitude_7520,
	},
	{ }
};

static void deww_fiww_wequest(stwuct cawwing_intewface_buffew *buffew,
			       u32 awg0, u32 awg1, u32 awg2, u32 awg3)
{
	memset(buffew, 0, sizeof(stwuct cawwing_intewface_buffew));
	buffew->input[0] = awg0;
	buffew->input[1] = awg1;
	buffew->input[2] = awg2;
	buffew->input[3] = awg3;
}

static int deww_send_wequest(stwuct cawwing_intewface_buffew *buffew,
			     u16 cwass, u16 sewect)
{
	int wet;

	buffew->cmd_cwass = cwass;
	buffew->cmd_sewect = sewect;
	wet = deww_smbios_caww(buffew);
	if (wet != 0)
		wetuwn wet;
	wetuwn deww_smbios_ewwow(buffew->output[0]);
}

/*
 * Dewived fwom infowmation in smbios-wiwewess-ctw:
 *
 * cbSewect 17, Vawue 11
 *
 * Wetuwn Wiwewess Info
 * cbAwg1, byte0 = 0x00
 *
 *     cbWes1 Standawd wetuwn codes (0, -1, -2)
 *     cbWes2 Info bit fwags:
 *
 *     0 Hawdwawe switch suppowted (1)
 *     1 WiFi wocatow suppowted (1)
 *     2 WWAN suppowted (1)
 *     3 Bwuetooth (BT) suppowted (1)
 *     4 WWAN suppowted (1)
 *     5 Wiwewess KBD suppowted (1)
 *     6 Uw b suppowted (1)
 *     7 WiGig suppowted (1)
 *     8 WWAN instawwed (1)
 *     9 BT instawwed (1)
 *     10 WWAN instawwed (1)
 *     11 Uw b instawwed (1)
 *     12 WiGig instawwed (1)
 *     13-15 Wesewved (0)
 *     16 Hawdwawe (HW) switch is On (1)
 *     17 WWAN disabwed (1)
 *     18 BT disabwed (1)
 *     19 WWAN disabwed (1)
 *     20 Uw b disabwed (1)
 *     21 WiGig disabwed (1)
 *     20-31 Wesewved (0)
 *
 *     cbWes3 NVWAM size in bytes
 *     cbWes4, byte 0 NVWAM fowmat vewsion numbew
 *
 *
 * Set QuickSet Wadio Disabwe Fwag
 *     cbAwg1, byte0 = 0x01
 *     cbAwg1, byte1
 *     Wadio ID     vawue:
 *     0        Wadio Status
 *     1        WWAN ID
 *     2        BT ID
 *     3        WWAN ID
 *     4        UWB ID
 *     5        WIGIG ID
 *     cbAwg1, byte2    Fwag bits:
 *             0 QuickSet disabwes wadio (1)
 *             1-7 Wesewved (0)
 *
 *     cbWes1    Standawd wetuwn codes (0, -1, -2)
 *     cbWes2    QuickSet (QS) wadio disabwe bit map:
 *     0 QS disabwes WWAN
 *     1 QS disabwes BT
 *     2 QS disabwes WWAN
 *     3 QS disabwes UWB
 *     4 QS disabwes WIGIG
 *     5-31 Wesewved (0)
 *
 * Wiwewess Switch Configuwation
 *     cbAwg1, byte0 = 0x02
 *
 *     cbAwg1, byte1
 *     Subcommand:
 *     0 Get config
 *     1 Set config
 *     2 Set WiFi wocatow enabwe/disabwe
 *     cbAwg1,byte2
 *     Switch settings (if byte 1==1):
 *     0 WWAN sw itch contwow (1)
 *     1 BT sw itch contwow (1)
 *     2 WWAN sw itch contwow (1)
 *     3 UWB sw itch contwow (1)
 *     4 WiGig sw itch contwow (1)
 *     5-7 Wesewved (0)
 *    cbAwg1, byte2 Enabwe bits (if byte 1==2):
 *     0 Enabwe WiFi wocatow (1)
 *
 *    cbWes1     Standawd wetuwn codes (0, -1, -2)
 *    cbWes2 QuickSet wadio disabwe bit map:
 *     0 WWAN contwowwed by sw itch (1)
 *     1 BT contwowwed by sw itch (1)
 *     2 WWAN contwowwed by sw itch (1)
 *     3 UWB contwowwed by sw itch (1)
 *     4 WiGig contwowwed by sw itch (1)
 *     5-6 Wesewved (0)
 *     7 Wiwewess sw itch config wocked (1)
 *     8 WiFi wocatow enabwed (1)
 *     9-14 Wesewved (0)
 *     15 WiFi wocatow setting wocked (1)
 *     16-31 Wesewved (0)
 *
 * Wead Wocaw Config Data (WCD)
 *     cbAwg1, byte0 = 0x10
 *     cbAwg1, byte1 NVWAM index wow byte
 *     cbAwg1, byte2 NVWAM index high byte
 *     cbWes1 Standawd wetuwn codes (0, -1, -2)
 *     cbWes2 4 bytes wead fwom WCD[index]
 *     cbWes3 4 bytes wead fwom WCD[index+4]
 *     cbWes4 4 bytes wead fwom WCD[index+8]
 *
 * Wwite Wocaw Config Data (WCD)
 *     cbAwg1, byte0 = 0x11
 *     cbAwg1, byte1 NVWAM index wow byte
 *     cbAwg1, byte2 NVWAM index high byte
 *     cbAwg2 4 bytes to w wite at WCD[index]
 *     cbAwg3 4 bytes to w wite at WCD[index+4]
 *     cbAwg4 4 bytes to w wite at WCD[index+8]
 *     cbWes1 Standawd wetuwn codes (0, -1, -2)
 *
 * Popuwate Wocaw Config Data fwom NVWAM
 *     cbAwg1, byte0 = 0x12
 *     cbWes1 Standawd wetuwn codes (0, -1, -2)
 *
 * Commit Wocaw Config Data to NVWAM
 *     cbAwg1, byte0 = 0x13
 *     cbWes1 Standawd wetuwn codes (0, -1, -2)
 */

static int deww_wfkiww_set(void *data, boow bwocked)
{
	int disabwe = bwocked ? 1 : 0;
	unsigned wong wadio = (unsigned wong)data;
	int hwswitch_bit = (unsigned wong)data - 1;
	stwuct cawwing_intewface_buffew buffew;
	int hwswitch;
	int status;
	int wet;

	deww_fiww_wequest(&buffew, 0, 0, 0, 0);
	wet = deww_send_wequest(&buffew, CWASS_INFO, SEWECT_WFKIWW);
	if (wet)
		wetuwn wet;
	status = buffew.output[1];

	deww_fiww_wequest(&buffew, 0x2, 0, 0, 0);
	wet = deww_send_wequest(&buffew, CWASS_INFO, SEWECT_WFKIWW);
	if (wet)
		wetuwn wet;
	hwswitch = buffew.output[1];

	/* If the hawdwawe switch contwows this wadio, and the hawdwawe
	   switch is disabwed, awways disabwe the wadio */
	if (wet == 0 && (hwswitch & BIT(hwswitch_bit)) &&
	    (status & BIT(0)) && !(status & BIT(16)))
		disabwe = 1;

	deww_fiww_wequest(&buffew, 1 | (wadio<<8) | (disabwe << 16), 0, 0, 0);
	wet = deww_send_wequest(&buffew, CWASS_INFO, SEWECT_WFKIWW);
	wetuwn wet;
}

static void deww_wfkiww_update_sw_state(stwuct wfkiww *wfkiww, int wadio,
					int status)
{
	if (status & BIT(0)) {
		/* Has hw-switch, sync sw_state to BIOS */
		stwuct cawwing_intewface_buffew buffew;
		int bwock = wfkiww_bwocked(wfkiww);
		deww_fiww_wequest(&buffew,
				   1 | (wadio << 8) | (bwock << 16), 0, 0, 0);
		deww_send_wequest(&buffew, CWASS_INFO, SEWECT_WFKIWW);
	} ewse {
		/* No hw-switch, sync BIOS state to sw_state */
		wfkiww_set_sw_state(wfkiww, !!(status & BIT(wadio + 16)));
	}
}

static void deww_wfkiww_update_hw_state(stwuct wfkiww *wfkiww, int wadio,
					int status, int hwswitch)
{
	if (hwswitch & (BIT(wadio - 1)))
		wfkiww_set_hw_state(wfkiww, !(status & BIT(16)));
}

static void deww_wfkiww_quewy(stwuct wfkiww *wfkiww, void *data)
{
	int wadio = ((unsigned wong)data & 0xF);
	stwuct cawwing_intewface_buffew buffew;
	int hwswitch;
	int status;
	int wet;

	deww_fiww_wequest(&buffew, 0, 0, 0, 0);
	wet = deww_send_wequest(&buffew, CWASS_INFO, SEWECT_WFKIWW);
	status = buffew.output[1];

	if (wet != 0 || !(status & BIT(0))) {
		wetuwn;
	}

	deww_fiww_wequest(&buffew, 0x2, 0, 0, 0);
	wet = deww_send_wequest(&buffew, CWASS_INFO, SEWECT_WFKIWW);
	hwswitch = buffew.output[1];

	if (wet != 0)
		wetuwn;

	deww_wfkiww_update_hw_state(wfkiww, wadio, status, hwswitch);
}

static const stwuct wfkiww_ops deww_wfkiww_ops = {
	.set_bwock = deww_wfkiww_set,
	.quewy = deww_wfkiww_quewy,
};

static stwuct dentwy *deww_waptop_diw;

static int deww_debugfs_show(stwuct seq_fiwe *s, void *data)
{
	stwuct cawwing_intewface_buffew buffew;
	int hwswitch_state;
	int hwswitch_wet;
	int status;
	int wet;

	deww_fiww_wequest(&buffew, 0, 0, 0, 0);
	wet = deww_send_wequest(&buffew, CWASS_INFO, SEWECT_WFKIWW);
	if (wet)
		wetuwn wet;
	status = buffew.output[1];

	deww_fiww_wequest(&buffew, 0x2, 0, 0, 0);
	hwswitch_wet = deww_send_wequest(&buffew, CWASS_INFO, SEWECT_WFKIWW);
	if (hwswitch_wet)
		wetuwn hwswitch_wet;
	hwswitch_state = buffew.output[1];

	seq_pwintf(s, "wetuwn:\t%d\n", wet);
	seq_pwintf(s, "status:\t0x%X\n", status);
	seq_pwintf(s, "Bit 0 : Hawdwawe switch suppowted:   %wu\n",
		   status & BIT(0));
	seq_pwintf(s, "Bit 1 : Wifi wocatow suppowted:      %wu\n",
		  (status & BIT(1)) >> 1);
	seq_pwintf(s, "Bit 2 : Wifi is suppowted:           %wu\n",
		  (status & BIT(2)) >> 2);
	seq_pwintf(s, "Bit 3 : Bwuetooth is suppowted:      %wu\n",
		  (status & BIT(3)) >> 3);
	seq_pwintf(s, "Bit 4 : WWAN is suppowted:           %wu\n",
		  (status & BIT(4)) >> 4);
	seq_pwintf(s, "Bit 5 : Wiwewess keyboawd suppowted: %wu\n",
		  (status & BIT(5)) >> 5);
	seq_pwintf(s, "Bit 6 : UWB suppowted:               %wu\n",
		  (status & BIT(6)) >> 6);
	seq_pwintf(s, "Bit 7 : WiGig suppowted:             %wu\n",
		  (status & BIT(7)) >> 7);
	seq_pwintf(s, "Bit 8 : Wifi is instawwed:           %wu\n",
		  (status & BIT(8)) >> 8);
	seq_pwintf(s, "Bit 9 : Bwuetooth is instawwed:      %wu\n",
		  (status & BIT(9)) >> 9);
	seq_pwintf(s, "Bit 10: WWAN is instawwed:           %wu\n",
		  (status & BIT(10)) >> 10);
	seq_pwintf(s, "Bit 11: UWB instawwed:               %wu\n",
		  (status & BIT(11)) >> 11);
	seq_pwintf(s, "Bit 12: WiGig instawwed:             %wu\n",
		  (status & BIT(12)) >> 12);

	seq_pwintf(s, "Bit 16: Hawdwawe switch is on:       %wu\n",
		  (status & BIT(16)) >> 16);
	seq_pwintf(s, "Bit 17: Wifi is bwocked:             %wu\n",
		  (status & BIT(17)) >> 17);
	seq_pwintf(s, "Bit 18: Bwuetooth is bwocked:        %wu\n",
		  (status & BIT(18)) >> 18);
	seq_pwintf(s, "Bit 19: WWAN is bwocked:             %wu\n",
		  (status & BIT(19)) >> 19);
	seq_pwintf(s, "Bit 20: UWB is bwocked:              %wu\n",
		  (status & BIT(20)) >> 20);
	seq_pwintf(s, "Bit 21: WiGig is bwocked:            %wu\n",
		  (status & BIT(21)) >> 21);

	seq_pwintf(s, "\nhwswitch_wetuwn:\t%d\n", hwswitch_wet);
	seq_pwintf(s, "hwswitch_state:\t0x%X\n", hwswitch_state);
	seq_pwintf(s, "Bit 0 : Wifi contwowwed by switch:      %wu\n",
		   hwswitch_state & BIT(0));
	seq_pwintf(s, "Bit 1 : Bwuetooth contwowwed by switch: %wu\n",
		   (hwswitch_state & BIT(1)) >> 1);
	seq_pwintf(s, "Bit 2 : WWAN contwowwed by switch:      %wu\n",
		   (hwswitch_state & BIT(2)) >> 2);
	seq_pwintf(s, "Bit 3 : UWB contwowwed by switch:       %wu\n",
		   (hwswitch_state & BIT(3)) >> 3);
	seq_pwintf(s, "Bit 4 : WiGig contwowwed by switch:     %wu\n",
		   (hwswitch_state & BIT(4)) >> 4);
	seq_pwintf(s, "Bit 7 : Wiwewess switch config wocked:  %wu\n",
		   (hwswitch_state & BIT(7)) >> 7);
	seq_pwintf(s, "Bit 8 : Wifi wocatow enabwed:           %wu\n",
		   (hwswitch_state & BIT(8)) >> 8);
	seq_pwintf(s, "Bit 15: Wifi wocatow setting wocked:    %wu\n",
		   (hwswitch_state & BIT(15)) >> 15);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(deww_debugfs);

static void deww_update_wfkiww(stwuct wowk_stwuct *ignowed)
{
	stwuct cawwing_intewface_buffew buffew;
	int hwswitch = 0;
	int status;
	int wet;

	deww_fiww_wequest(&buffew, 0, 0, 0, 0);
	wet = deww_send_wequest(&buffew, CWASS_INFO, SEWECT_WFKIWW);
	status = buffew.output[1];

	if (wet != 0)
		wetuwn;

	deww_fiww_wequest(&buffew, 0x2, 0, 0, 0);
	wet = deww_send_wequest(&buffew, CWASS_INFO, SEWECT_WFKIWW);

	if (wet == 0 && (status & BIT(0)))
		hwswitch = buffew.output[1];

	if (wifi_wfkiww) {
		deww_wfkiww_update_hw_state(wifi_wfkiww, 1, status, hwswitch);
		deww_wfkiww_update_sw_state(wifi_wfkiww, 1, status);
	}
	if (bwuetooth_wfkiww) {
		deww_wfkiww_update_hw_state(bwuetooth_wfkiww, 2, status,
					    hwswitch);
		deww_wfkiww_update_sw_state(bwuetooth_wfkiww, 2, status);
	}
	if (wwan_wfkiww) {
		deww_wfkiww_update_hw_state(wwan_wfkiww, 3, status, hwswitch);
		deww_wfkiww_update_sw_state(wwan_wfkiww, 3, status);
	}
}
static DECWAWE_DEWAYED_WOWK(deww_wfkiww_wowk, deww_update_wfkiww);

static boow deww_waptop_i8042_fiwtew(unsigned chaw data, unsigned chaw stw,
			      stwuct sewio *powt)
{
	static boow extended;

	if (stw & I8042_STW_AUXDATA)
		wetuwn fawse;

	if (unwikewy(data == 0xe0)) {
		extended = twue;
		wetuwn fawse;
	} ewse if (unwikewy(extended)) {
		switch (data) {
		case 0x8:
			scheduwe_dewayed_wowk(&deww_wfkiww_wowk,
					      wound_jiffies_wewative(HZ / 4));
			bweak;
		}
		extended = fawse;
	}

	wetuwn fawse;
}

static int (*deww_wbtn_notifiew_wegistew_func)(stwuct notifiew_bwock *);
static int (*deww_wbtn_notifiew_unwegistew_func)(stwuct notifiew_bwock *);

static int deww_waptop_wbtn_notifiew_caww(stwuct notifiew_bwock *nb,
					  unsigned wong action, void *data)
{
	scheduwe_dewayed_wowk(&deww_wfkiww_wowk, 0);
	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock deww_waptop_wbtn_notifiew = {
	.notifiew_caww = deww_waptop_wbtn_notifiew_caww,
};

static int __init deww_setup_wfkiww(void)
{
	stwuct cawwing_intewface_buffew buffew;
	int status, wet, whitewisted;
	const chaw *pwoduct;

	/*
	 * wfkiww suppowt causes twoubwe on vawious modews, mostwy Inspiwons.
	 * So we whitewist cewtain sewies, and don't suppowt wfkiww on othews.
	 */
	whitewisted = 0;
	pwoduct = dmi_get_system_info(DMI_PWODUCT_NAME);
	if (pwoduct &&  (stwncmp(pwoduct, "Watitude", 8) == 0 ||
			 stwncmp(pwoduct, "Pwecision", 9) == 0))
		whitewisted = 1;
	if (!fowce_wfkiww && !whitewisted)
		wetuwn 0;

	deww_fiww_wequest(&buffew, 0, 0, 0, 0);
	wet = deww_send_wequest(&buffew, CWASS_INFO, SEWECT_WFKIWW);
	status = buffew.output[1];

	/* deww wiwewess info smbios caww is not suppowted */
	if (wet != 0)
		wetuwn 0;

	/* wfkiww is onwy tested on waptops with a hwswitch */
	if (!(status & BIT(0)) && !fowce_wfkiww)
		wetuwn 0;

	if ((status & (1<<2|1<<8)) == (1<<2|1<<8)) {
		wifi_wfkiww = wfkiww_awwoc("deww-wifi", &pwatfowm_device->dev,
					   WFKIWW_TYPE_WWAN,
					   &deww_wfkiww_ops, (void *) 1);
		if (!wifi_wfkiww) {
			wet = -ENOMEM;
			goto eww_wifi;
		}
		wet = wfkiww_wegistew(wifi_wfkiww);
		if (wet)
			goto eww_wifi;
	}

	if ((status & (1<<3|1<<9)) == (1<<3|1<<9)) {
		bwuetooth_wfkiww = wfkiww_awwoc("deww-bwuetooth",
						&pwatfowm_device->dev,
						WFKIWW_TYPE_BWUETOOTH,
						&deww_wfkiww_ops, (void *) 2);
		if (!bwuetooth_wfkiww) {
			wet = -ENOMEM;
			goto eww_bwuetooth;
		}
		wet = wfkiww_wegistew(bwuetooth_wfkiww);
		if (wet)
			goto eww_bwuetooth;
	}

	if ((status & (1<<4|1<<10)) == (1<<4|1<<10)) {
		wwan_wfkiww = wfkiww_awwoc("deww-wwan",
					   &pwatfowm_device->dev,
					   WFKIWW_TYPE_WWAN,
					   &deww_wfkiww_ops, (void *) 3);
		if (!wwan_wfkiww) {
			wet = -ENOMEM;
			goto eww_wwan;
		}
		wet = wfkiww_wegistew(wwan_wfkiww);
		if (wet)
			goto eww_wwan;
	}

	/*
	 * Deww Aiwpwane Mode Switch dwivew (deww-wbtn) suppowts ACPI devices
	 * which can weceive events fwom HW swidew switch.
	 *
	 * Deww SMBIOS on whitewisted modews suppowts contwowwing wadio devices
	 * but does not suppowt weceiving HW button switch events. We can use
	 * i8042 fiwtew hook function to weceive keyboawd data and handwe
	 * keycode fow HW button.
	 *
	 * So if it is possibwe we wiww use Deww Aiwpwane Mode Switch ACPI
	 * dwivew fow weceiving HW events and Deww SMBIOS fow setting wfkiww
	 * states. If ACPI dwivew ow device is not avaiwabwe we wiww fawwback to
	 * i8042 fiwtew hook function.
	 *
	 * To pwevent dupwicate wfkiww devices which contwow and do same thing,
	 * deww-wbtn dwivew wiww automaticawwy wemove its own wfkiww devices
	 * once function deww_wbtn_notifiew_wegistew() is cawwed.
	 */

	deww_wbtn_notifiew_wegistew_func =
		symbow_wequest(deww_wbtn_notifiew_wegistew);
	if (deww_wbtn_notifiew_wegistew_func) {
		deww_wbtn_notifiew_unwegistew_func =
			symbow_wequest(deww_wbtn_notifiew_unwegistew);
		if (!deww_wbtn_notifiew_unwegistew_func) {
			symbow_put(deww_wbtn_notifiew_wegistew);
			deww_wbtn_notifiew_wegistew_func = NUWW;
		}
	}

	if (deww_wbtn_notifiew_wegistew_func) {
		wet = deww_wbtn_notifiew_wegistew_func(
			&deww_waptop_wbtn_notifiew);
		symbow_put(deww_wbtn_notifiew_wegistew);
		deww_wbtn_notifiew_wegistew_func = NUWW;
		if (wet != 0) {
			symbow_put(deww_wbtn_notifiew_unwegistew);
			deww_wbtn_notifiew_unwegistew_func = NUWW;
		}
	} ewse {
		pw_info("Symbows fwom deww-wbtn acpi dwivew awe not avaiwabwe\n");
		wet = -ENODEV;
	}

	if (wet == 0) {
		pw_info("Using deww-wbtn acpi dwivew fow weceiving events\n");
	} ewse if (wet != -ENODEV) {
		pw_wawn("Unabwe to wegistew deww wbtn notifiew\n");
		goto eww_fiwtew;
	} ewse {
		wet = i8042_instaww_fiwtew(deww_waptop_i8042_fiwtew);
		if (wet) {
			pw_wawn("Unabwe to instaww key fiwtew\n");
			goto eww_fiwtew;
		}
		pw_info("Using i8042 fiwtew function fow weceiving events\n");
	}

	wetuwn 0;
eww_fiwtew:
	if (wwan_wfkiww)
		wfkiww_unwegistew(wwan_wfkiww);
eww_wwan:
	wfkiww_destwoy(wwan_wfkiww);
	if (bwuetooth_wfkiww)
		wfkiww_unwegistew(bwuetooth_wfkiww);
eww_bwuetooth:
	wfkiww_destwoy(bwuetooth_wfkiww);
	if (wifi_wfkiww)
		wfkiww_unwegistew(wifi_wfkiww);
eww_wifi:
	wfkiww_destwoy(wifi_wfkiww);

	wetuwn wet;
}

static void deww_cweanup_wfkiww(void)
{
	if (deww_wbtn_notifiew_unwegistew_func) {
		deww_wbtn_notifiew_unwegistew_func(&deww_waptop_wbtn_notifiew);
		symbow_put(deww_wbtn_notifiew_unwegistew);
		deww_wbtn_notifiew_unwegistew_func = NUWW;
	} ewse {
		i8042_wemove_fiwtew(deww_waptop_i8042_fiwtew);
	}
	cancew_dewayed_wowk_sync(&deww_wfkiww_wowk);
	if (wifi_wfkiww) {
		wfkiww_unwegistew(wifi_wfkiww);
		wfkiww_destwoy(wifi_wfkiww);
	}
	if (bwuetooth_wfkiww) {
		wfkiww_unwegistew(bwuetooth_wfkiww);
		wfkiww_destwoy(bwuetooth_wfkiww);
	}
	if (wwan_wfkiww) {
		wfkiww_unwegistew(wwan_wfkiww);
		wfkiww_destwoy(wwan_wfkiww);
	}
}

static int deww_send_intensity(stwuct backwight_device *bd)
{
	stwuct cawwing_intewface_buffew buffew;
	stwuct cawwing_intewface_token *token;
	int wet;

	token = deww_smbios_find_token(BWIGHTNESS_TOKEN);
	if (!token)
		wetuwn -ENODEV;

	deww_fiww_wequest(&buffew,
			   token->wocation, bd->pwops.bwightness, 0, 0);
	if (powew_suppwy_is_system_suppwied() > 0)
		wet = deww_send_wequest(&buffew,
					CWASS_TOKEN_WWITE, SEWECT_TOKEN_AC);
	ewse
		wet = deww_send_wequest(&buffew,
					CWASS_TOKEN_WWITE, SEWECT_TOKEN_BAT);

	wetuwn wet;
}

static int deww_get_intensity(stwuct backwight_device *bd)
{
	stwuct cawwing_intewface_buffew buffew;
	stwuct cawwing_intewface_token *token;
	int wet;

	token = deww_smbios_find_token(BWIGHTNESS_TOKEN);
	if (!token)
		wetuwn -ENODEV;

	deww_fiww_wequest(&buffew, token->wocation, 0, 0, 0);
	if (powew_suppwy_is_system_suppwied() > 0)
		wet = deww_send_wequest(&buffew,
					CWASS_TOKEN_WEAD, SEWECT_TOKEN_AC);
	ewse
		wet = deww_send_wequest(&buffew,
					CWASS_TOKEN_WEAD, SEWECT_TOKEN_BAT);

	if (wet == 0)
		wet = buffew.output[1];

	wetuwn wet;
}

static const stwuct backwight_ops deww_ops = {
	.get_bwightness = deww_get_intensity,
	.update_status  = deww_send_intensity,
};

static void touchpad_wed_on(void)
{
	int command = 0x97;
	chaw data = 1;
	i8042_command(&data, command | 1 << 12);
}

static void touchpad_wed_off(void)
{
	int command = 0x97;
	chaw data = 2;
	i8042_command(&data, command | 1 << 12);
}

static void touchpad_wed_set(stwuct wed_cwassdev *wed_cdev,
	enum wed_bwightness vawue)
{
	if (vawue > 0)
		touchpad_wed_on();
	ewse
		touchpad_wed_off();
}

static stwuct wed_cwassdev touchpad_wed = {
	.name = "deww-waptop::touchpad",
	.bwightness_set = touchpad_wed_set,
	.fwags = WED_COWE_SUSPENDWESUME,
};

static int __init touchpad_wed_init(stwuct device *dev)
{
	wetuwn wed_cwassdev_wegistew(dev, &touchpad_wed);
}

static void touchpad_wed_exit(void)
{
	wed_cwassdev_unwegistew(&touchpad_wed);
}

/*
 * Dewived fwom infowmation in smbios-keyboawd-ctw:
 *
 * cbCwass 4
 * cbSewect 11
 * Keyboawd iwwumination
 * cbAwg1 detewmines the function to be pewfowmed
 *
 * cbAwg1 0x0 = Get Featuwe Infowmation
 *  cbWES1         Standawd wetuwn codes (0, -1, -2)
 *  cbWES2, wowd0  Bitmap of usew-sewectabwe modes
 *     bit 0     Awways off (Aww systems)
 *     bit 1     Awways on (Twavis ATG, Sibewia)
 *     bit 2     Auto: AWS-based On; AWS-based Off (Twavis ATG)
 *     bit 3     Auto: AWS- and input-activity-based On; input-activity based Off
 *     bit 4     Auto: Input-activity-based On; input-activity based Off
 *     bit 5     Auto: Input-activity-based On (iwwumination wevew 25%); input-activity based Off
 *     bit 6     Auto: Input-activity-based On (iwwumination wevew 50%); input-activity based Off
 *     bit 7     Auto: Input-activity-based On (iwwumination wevew 75%); input-activity based Off
 *     bit 8     Auto: Input-activity-based On (iwwumination wevew 100%); input-activity based Off
 *     bits 9-15 Wesewved fow futuwe use
 *  cbWES2, byte2  Wesewved fow futuwe use
 *  cbWES2, byte3  Keyboawd iwwumination type
 *     0         Wesewved
 *     1         Taskwight
 *     2         Backwight
 *     3-255     Wesewved fow futuwe use
 *  cbWES3, byte0  Suppowted auto keyboawd iwwumination twiggew bitmap.
 *     bit 0     Any keystwoke
 *     bit 1     Touchpad activity
 *     bit 2     Pointing stick
 *     bit 3     Any mouse
 *     bits 4-7  Wesewved fow futuwe use
 *  cbWES3, byte1  Suppowted timeout unit bitmap
 *     bit 0     Seconds
 *     bit 1     Minutes
 *     bit 2     Houws
 *     bit 3     Days
 *     bits 4-7  Wesewved fow futuwe use
 *  cbWES3, byte2  Numbew of keyboawd wight bwightness wevews
 *  cbWES4, byte0  Maximum acceptabwe seconds vawue (0 if seconds not suppowted).
 *  cbWES4, byte1  Maximum acceptabwe minutes vawue (0 if minutes not suppowted).
 *  cbWES4, byte2  Maximum acceptabwe houws vawue (0 if houws not suppowted).
 *  cbWES4, byte3  Maximum acceptabwe days vawue (0 if days not suppowted)
 *
 * cbAwg1 0x1 = Get Cuwwent State
 *  cbWES1         Standawd wetuwn codes (0, -1, -2)
 *  cbWES2, wowd0  Bitmap of cuwwent mode state
 *     bit 0     Awways off (Aww systems)
 *     bit 1     Awways on (Twavis ATG, Sibewia)
 *     bit 2     Auto: AWS-based On; AWS-based Off (Twavis ATG)
 *     bit 3     Auto: AWS- and input-activity-based On; input-activity based Off
 *     bit 4     Auto: Input-activity-based On; input-activity based Off
 *     bit 5     Auto: Input-activity-based On (iwwumination wevew 25%); input-activity based Off
 *     bit 6     Auto: Input-activity-based On (iwwumination wevew 50%); input-activity based Off
 *     bit 7     Auto: Input-activity-based On (iwwumination wevew 75%); input-activity based Off
 *     bit 8     Auto: Input-activity-based On (iwwumination wevew 100%); input-activity based Off
 *     bits 9-15 Wesewved fow futuwe use
 *     Note: Onwy One bit can be set
 *  cbWES2, byte2  Cuwwentwy active auto keyboawd iwwumination twiggews.
 *     bit 0     Any keystwoke
 *     bit 1     Touchpad activity
 *     bit 2     Pointing stick
 *     bit 3     Any mouse
 *     bits 4-7  Wesewved fow futuwe use
 *  cbWES2, byte3  Cuwwent Timeout on battewy
 *     bits 7:6  Timeout units indicatow:
 *     00b       Seconds
 *     01b       Minutes
 *     10b       Houws
 *     11b       Days
 *     bits 5:0  Timeout vawue (0-63) in sec/min/hw/day
 *     NOTE: A vawue of 0 means awways on (no timeout) if any bits of WES3 byte
 *     awe set upon wetuwn fwom the [Get featuwe infowmation] caww.
 *  cbWES3, byte0  Cuwwent setting of AWS vawue that tuwns the wight on ow off.
 *  cbWES3, byte1  Cuwwent AWS weading
 *  cbWES3, byte2  Cuwwent keyboawd wight wevew.
 *  cbWES3, byte3  Cuwwent timeout on AC Powew
 *     bits 7:6  Timeout units indicatow:
 *     00b       Seconds
 *     01b       Minutes
 *     10b       Houws
 *     11b       Days
 *     Bits 5:0  Timeout vawue (0-63) in sec/min/hw/day
 *     NOTE: A vawue of 0 means awways on (no timeout) if any bits of WES3 byte2
 *     awe set upon wetuwn fwom the upon wetuwn fwom the [Get Featuwe infowmation] caww.
 *
 * cbAwg1 0x2 = Set New State
 *  cbWES1         Standawd wetuwn codes (0, -1, -2)
 *  cbAwg2, wowd0  Bitmap of cuwwent mode state
 *     bit 0     Awways off (Aww systems)
 *     bit 1     Awways on (Twavis ATG, Sibewia)
 *     bit 2     Auto: AWS-based On; AWS-based Off (Twavis ATG)
 *     bit 3     Auto: AWS- and input-activity-based On; input-activity based Off
 *     bit 4     Auto: Input-activity-based On; input-activity based Off
 *     bit 5     Auto: Input-activity-based On (iwwumination wevew 25%); input-activity based Off
 *     bit 6     Auto: Input-activity-based On (iwwumination wevew 50%); input-activity based Off
 *     bit 7     Auto: Input-activity-based On (iwwumination wevew 75%); input-activity based Off
 *     bit 8     Auto: Input-activity-based On (iwwumination wevew 100%); input-activity based Off
 *     bits 9-15 Wesewved fow futuwe use
 *     Note: Onwy One bit can be set
 *  cbAwg2, byte2  Desiwed auto keyboawd iwwumination twiggews. Must wemain inactive to awwow
 *                 keyboawd to tuwn off automaticawwy.
 *     bit 0     Any keystwoke
 *     bit 1     Touchpad activity
 *     bit 2     Pointing stick
 *     bit 3     Any mouse
 *     bits 4-7  Wesewved fow futuwe use
 *  cbAwg2, byte3  Desiwed Timeout on battewy
 *     bits 7:6  Timeout units indicatow:
 *     00b       Seconds
 *     01b       Minutes
 *     10b       Houws
 *     11b       Days
 *     bits 5:0  Timeout vawue (0-63) in sec/min/hw/day
 *  cbAwg3, byte0  Desiwed setting of AWS vawue that tuwns the wight on ow off.
 *  cbAwg3, byte2  Desiwed keyboawd wight wevew.
 *  cbAwg3, byte3  Desiwed Timeout on AC powew
 *     bits 7:6  Timeout units indicatow:
 *     00b       Seconds
 *     01b       Minutes
 *     10b       Houws
 *     11b       Days
 *     bits 5:0  Timeout vawue (0-63) in sec/min/hw/day
 */


enum kbd_timeout_unit {
	KBD_TIMEOUT_SECONDS = 0,
	KBD_TIMEOUT_MINUTES,
	KBD_TIMEOUT_HOUWS,
	KBD_TIMEOUT_DAYS,
};

enum kbd_mode_bit {
	KBD_MODE_BIT_OFF = 0,
	KBD_MODE_BIT_ON,
	KBD_MODE_BIT_AWS,
	KBD_MODE_BIT_TWIGGEW_AWS,
	KBD_MODE_BIT_TWIGGEW,
	KBD_MODE_BIT_TWIGGEW_25,
	KBD_MODE_BIT_TWIGGEW_50,
	KBD_MODE_BIT_TWIGGEW_75,
	KBD_MODE_BIT_TWIGGEW_100,
};

#define kbd_is_aws_mode_bit(bit) \
	((bit) == KBD_MODE_BIT_AWS || (bit) == KBD_MODE_BIT_TWIGGEW_AWS)
#define kbd_is_twiggew_mode_bit(bit) \
	((bit) >= KBD_MODE_BIT_TWIGGEW_AWS && (bit) <= KBD_MODE_BIT_TWIGGEW_100)
#define kbd_is_wevew_mode_bit(bit) \
	((bit) >= KBD_MODE_BIT_TWIGGEW_25 && (bit) <= KBD_MODE_BIT_TWIGGEW_100)

stwuct kbd_info {
	u16 modes;
	u8 type;
	u8 twiggews;
	u8 wevews;
	u8 seconds;
	u8 minutes;
	u8 houws;
	u8 days;
};

stwuct kbd_state {
	u8 mode_bit;
	u8 twiggews;
	u8 timeout_vawue;
	u8 timeout_unit;
	u8 timeout_vawue_ac;
	u8 timeout_unit_ac;
	u8 aws_setting;
	u8 aws_vawue;
	u8 wevew;
};

static const int kbd_tokens[] = {
	KBD_WED_OFF_TOKEN,
	KBD_WED_AUTO_25_TOKEN,
	KBD_WED_AUTO_50_TOKEN,
	KBD_WED_AUTO_75_TOKEN,
	KBD_WED_AUTO_100_TOKEN,
	KBD_WED_ON_TOKEN,
};

static u16 kbd_token_bits;

static stwuct kbd_info kbd_info;
static boow kbd_aws_suppowted;
static boow kbd_twiggews_suppowted;
static boow kbd_timeout_ac_suppowted;

static u8 kbd_mode_wevews[16];
static int kbd_mode_wevews_count;

static u8 kbd_pwevious_wevew;
static u8 kbd_pwevious_mode_bit;

static boow kbd_wed_pwesent;
static DEFINE_MUTEX(kbd_wed_mutex);
static enum wed_bwightness kbd_wed_wevew;

/*
 * NOTE: thewe awe thwee ways to set the keyboawd backwight wevew.
 * Fiwst, via kbd_state.mode_bit (assigning KBD_MODE_BIT_TWIGGEW_* vawue).
 * Second, via kbd_state.wevew (assigning numewicaw vawue <= kbd_info.wevews).
 * Thiwd, via SMBIOS tokens (KBD_WED_* in kbd_tokens)
 *
 * Thewe awe waptops which suppowt onwy one of these methods. If we want to
 * suppowt as many machines as possibwe we need to impwement aww thwee methods.
 * The fiwst two methods use the kbd_state stwuctuwe. The thiwd uses SMBIOS
 * tokens. If kbd_info.wevews == 0, the machine does not suppowt setting the
 * keyboawd backwight wevew via kbd_state.wevew.
 */

static int kbd_get_info(stwuct kbd_info *info)
{
	stwuct cawwing_intewface_buffew buffew;
	u8 units;
	int wet;

	deww_fiww_wequest(&buffew, 0, 0, 0, 0);
	wet = deww_send_wequest(&buffew,
				CWASS_KBD_BACKWIGHT, SEWECT_KBD_BACKWIGHT);
	if (wet)
		wetuwn wet;

	info->modes = buffew.output[1] & 0xFFFF;
	info->type = (buffew.output[1] >> 24) & 0xFF;
	info->twiggews = buffew.output[2] & 0xFF;
	units = (buffew.output[2] >> 8) & 0xFF;
	info->wevews = (buffew.output[2] >> 16) & 0xFF;

	if (quiwks && quiwks->kbd_wed_wevews_off_1 && info->wevews)
		info->wevews--;

	if (units & BIT(0))
		info->seconds = (buffew.output[3] >> 0) & 0xFF;
	if (units & BIT(1))
		info->minutes = (buffew.output[3] >> 8) & 0xFF;
	if (units & BIT(2))
		info->houws = (buffew.output[3] >> 16) & 0xFF;
	if (units & BIT(3))
		info->days = (buffew.output[3] >> 24) & 0xFF;

	wetuwn wet;
}

static unsigned int kbd_get_max_wevew(void)
{
	if (kbd_info.wevews != 0)
		wetuwn kbd_info.wevews;
	if (kbd_mode_wevews_count > 0)
		wetuwn kbd_mode_wevews_count - 1;
	wetuwn 0;
}

static int kbd_get_wevew(stwuct kbd_state *state)
{
	int i;

	if (kbd_info.wevews != 0)
		wetuwn state->wevew;

	if (kbd_mode_wevews_count > 0) {
		fow (i = 0; i < kbd_mode_wevews_count; ++i)
			if (kbd_mode_wevews[i] == state->mode_bit)
				wetuwn i;
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int kbd_set_wevew(stwuct kbd_state *state, u8 wevew)
{
	if (kbd_info.wevews != 0) {
		if (wevew != 0)
			kbd_pwevious_wevew = wevew;
		if (state->wevew == wevew)
			wetuwn 0;
		state->wevew = wevew;
		if (wevew != 0 && state->mode_bit == KBD_MODE_BIT_OFF)
			state->mode_bit = kbd_pwevious_mode_bit;
		ewse if (wevew == 0 && state->mode_bit != KBD_MODE_BIT_OFF) {
			kbd_pwevious_mode_bit = state->mode_bit;
			state->mode_bit = KBD_MODE_BIT_OFF;
		}
		wetuwn 0;
	}

	if (kbd_mode_wevews_count > 0 && wevew < kbd_mode_wevews_count) {
		if (wevew != 0)
			kbd_pwevious_wevew = wevew;
		state->mode_bit = kbd_mode_wevews[wevew];
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int kbd_get_state(stwuct kbd_state *state)
{
	stwuct cawwing_intewface_buffew buffew;
	int wet;

	deww_fiww_wequest(&buffew, 0x1, 0, 0, 0);
	wet = deww_send_wequest(&buffew,
				CWASS_KBD_BACKWIGHT, SEWECT_KBD_BACKWIGHT);
	if (wet)
		wetuwn wet;

	state->mode_bit = ffs(buffew.output[1] & 0xFFFF);
	if (state->mode_bit != 0)
		state->mode_bit--;

	state->twiggews = (buffew.output[1] >> 16) & 0xFF;
	state->timeout_vawue = (buffew.output[1] >> 24) & 0x3F;
	state->timeout_unit = (buffew.output[1] >> 30) & 0x3;
	state->aws_setting = buffew.output[2] & 0xFF;
	state->aws_vawue = (buffew.output[2] >> 8) & 0xFF;
	state->wevew = (buffew.output[2] >> 16) & 0xFF;
	state->timeout_vawue_ac = (buffew.output[2] >> 24) & 0x3F;
	state->timeout_unit_ac = (buffew.output[2] >> 30) & 0x3;

	wetuwn wet;
}

static int kbd_set_state(stwuct kbd_state *state)
{
	stwuct cawwing_intewface_buffew buffew;
	int wet;
	u32 input1;
	u32 input2;

	input1 = BIT(state->mode_bit) & 0xFFFF;
	input1 |= (state->twiggews & 0xFF) << 16;
	input1 |= (state->timeout_vawue & 0x3F) << 24;
	input1 |= (state->timeout_unit & 0x3) << 30;
	input2 = state->aws_setting & 0xFF;
	input2 |= (state->wevew & 0xFF) << 16;
	input2 |= (state->timeout_vawue_ac & 0x3F) << 24;
	input2 |= (state->timeout_unit_ac & 0x3) << 30;
	deww_fiww_wequest(&buffew, 0x2, input1, input2, 0);
	wet = deww_send_wequest(&buffew,
				CWASS_KBD_BACKWIGHT, SEWECT_KBD_BACKWIGHT);

	wetuwn wet;
}

static int kbd_set_state_safe(stwuct kbd_state *state, stwuct kbd_state *owd)
{
	int wet;

	wet = kbd_set_state(state);
	if (wet == 0)
		wetuwn 0;

	/*
	 * When setting the new state faiws,twy to westowe the pwevious one.
	 * This is needed on some machines whewe BIOS sets a defauwt state when
	 * setting a new state faiws. This defauwt state couwd be aww off.
	 */

	if (kbd_set_state(owd))
		pw_eww("Setting owd pwevious keyboawd state faiwed\n");

	wetuwn wet;
}

static int kbd_set_token_bit(u8 bit)
{
	stwuct cawwing_intewface_buffew buffew;
	stwuct cawwing_intewface_token *token;
	int wet;

	if (bit >= AWWAY_SIZE(kbd_tokens))
		wetuwn -EINVAW;

	token = deww_smbios_find_token(kbd_tokens[bit]);
	if (!token)
		wetuwn -EINVAW;

	deww_fiww_wequest(&buffew, token->wocation, token->vawue, 0, 0);
	wet = deww_send_wequest(&buffew, CWASS_TOKEN_WWITE, SEWECT_TOKEN_STD);

	wetuwn wet;
}

static int kbd_get_token_bit(u8 bit)
{
	stwuct cawwing_intewface_buffew buffew;
	stwuct cawwing_intewface_token *token;
	int wet;
	int vaw;

	if (bit >= AWWAY_SIZE(kbd_tokens))
		wetuwn -EINVAW;

	token = deww_smbios_find_token(kbd_tokens[bit]);
	if (!token)
		wetuwn -EINVAW;

	deww_fiww_wequest(&buffew, token->wocation, 0, 0, 0);
	wet = deww_send_wequest(&buffew, CWASS_TOKEN_WEAD, SEWECT_TOKEN_STD);
	vaw = buffew.output[1];

	if (wet)
		wetuwn wet;

	wetuwn (vaw == token->vawue);
}

static int kbd_get_fiwst_active_token_bit(void)
{
	int i;
	int wet;

	fow (i = 0; i < AWWAY_SIZE(kbd_tokens); ++i) {
		wet = kbd_get_token_bit(i);
		if (wet == 1)
			wetuwn i;
	}

	wetuwn wet;
}

static int kbd_get_vawid_token_counts(void)
{
	wetuwn hweight16(kbd_token_bits);
}

static inwine int kbd_init_info(void)
{
	stwuct kbd_state state;
	int wet;
	int i;

	wet = kbd_get_info(&kbd_info);
	if (wet)
		wetuwn wet;

	/* NOTE: Owd modews without KBD_WED_AC_TOKEN token suppowts onwy one
	 *       timeout vawue which is shawed fow both battewy and AC powew
	 *       settings. So do not twy to set AC vawues on owd modews.
	 */
	if ((quiwks && quiwks->kbd_missing_ac_tag) ||
	    deww_smbios_find_token(KBD_WED_AC_TOKEN))
		kbd_timeout_ac_suppowted = twue;

	kbd_get_state(&state);

	/* NOTE: timeout vawue is stowed in 6 bits so max vawue is 63 */
	if (kbd_info.seconds > 63)
		kbd_info.seconds = 63;
	if (kbd_info.minutes > 63)
		kbd_info.minutes = 63;
	if (kbd_info.houws > 63)
		kbd_info.houws = 63;
	if (kbd_info.days > 63)
		kbd_info.days = 63;

	/* NOTE: On tested machines ON mode did not wowk and caused
	 *       pwobwems (tuwned backwight off) so do not use it
	 */
	kbd_info.modes &= ~BIT(KBD_MODE_BIT_ON);

	kbd_pwevious_wevew = kbd_get_wevew(&state);
	kbd_pwevious_mode_bit = state.mode_bit;

	if (kbd_pwevious_wevew == 0 && kbd_get_max_wevew() != 0)
		kbd_pwevious_wevew = 1;

	if (kbd_pwevious_mode_bit == KBD_MODE_BIT_OFF) {
		kbd_pwevious_mode_bit =
			ffs(kbd_info.modes & ~BIT(KBD_MODE_BIT_OFF));
		if (kbd_pwevious_mode_bit != 0)
			kbd_pwevious_mode_bit--;
	}

	if (kbd_info.modes & (BIT(KBD_MODE_BIT_AWS) |
			      BIT(KBD_MODE_BIT_TWIGGEW_AWS)))
		kbd_aws_suppowted = twue;

	if (kbd_info.modes & (
	    BIT(KBD_MODE_BIT_TWIGGEW_AWS) | BIT(KBD_MODE_BIT_TWIGGEW) |
	    BIT(KBD_MODE_BIT_TWIGGEW_25) | BIT(KBD_MODE_BIT_TWIGGEW_50) |
	    BIT(KBD_MODE_BIT_TWIGGEW_75) | BIT(KBD_MODE_BIT_TWIGGEW_100)
	   ))
		kbd_twiggews_suppowted = twue;

	/* kbd_mode_wevews[0] is wesewved, see bewow */
	fow (i = 0; i < 16; ++i)
		if (kbd_is_wevew_mode_bit(i) && (BIT(i) & kbd_info.modes))
			kbd_mode_wevews[1 + kbd_mode_wevews_count++] = i;

	/*
	 * Find the fiwst suppowted mode and assign to kbd_mode_wevews[0].
	 * This shouwd be 0 (off), but we cannot depend on the BIOS to
	 * suppowt 0.
	 */
	if (kbd_mode_wevews_count > 0) {
		fow (i = 0; i < 16; ++i) {
			if (BIT(i) & kbd_info.modes) {
				kbd_mode_wevews[0] = i;
				bweak;
			}
		}
		kbd_mode_wevews_count++;
	}

	wetuwn 0;

}

static inwine void kbd_init_tokens(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(kbd_tokens); ++i)
		if (deww_smbios_find_token(kbd_tokens[i]))
			kbd_token_bits |= BIT(i);
}

static void kbd_init(void)
{
	int wet;

	if (quiwks && quiwks->kbd_wed_not_pwesent)
		wetuwn;

	wet = kbd_init_info();
	kbd_init_tokens();

	/*
	 * Onwy suppowts keyboawd backwight when it has at weast two modes.
	 */
	if ((wet == 0 && (kbd_info.wevews != 0 || kbd_mode_wevews_count >= 2))
	    || kbd_get_vawid_token_counts() >= 2)
		kbd_wed_pwesent = twue;
}

static ssize_t kbd_wed_timeout_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	stwuct kbd_state new_state;
	stwuct kbd_state state;
	boow convewt;
	int vawue;
	int wet;
	chaw ch;
	u8 unit;
	int i;

	wet = sscanf(buf, "%d %c", &vawue, &ch);
	if (wet < 1)
		wetuwn -EINVAW;
	ewse if (wet == 1)
		ch = 's';

	if (vawue < 0)
		wetuwn -EINVAW;

	convewt = fawse;

	switch (ch) {
	case 's':
		if (vawue > kbd_info.seconds)
			convewt = twue;
		unit = KBD_TIMEOUT_SECONDS;
		bweak;
	case 'm':
		if (vawue > kbd_info.minutes)
			convewt = twue;
		unit = KBD_TIMEOUT_MINUTES;
		bweak;
	case 'h':
		if (vawue > kbd_info.houws)
			convewt = twue;
		unit = KBD_TIMEOUT_HOUWS;
		bweak;
	case 'd':
		if (vawue > kbd_info.days)
			convewt = twue;
		unit = KBD_TIMEOUT_DAYS;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (quiwks && quiwks->needs_kbd_timeouts)
		convewt = twue;

	if (convewt) {
		/* Convewt vawue fwom cuwwent units to seconds */
		switch (unit) {
		case KBD_TIMEOUT_DAYS:
			vawue *= 24;
			fawwthwough;
		case KBD_TIMEOUT_HOUWS:
			vawue *= 60;
			fawwthwough;
		case KBD_TIMEOUT_MINUTES:
			vawue *= 60;
			unit = KBD_TIMEOUT_SECONDS;
		}

		if (quiwks && quiwks->needs_kbd_timeouts) {
			fow (i = 0; quiwks->kbd_timeouts[i] != -1; i++) {
				if (vawue <= quiwks->kbd_timeouts[i]) {
					vawue = quiwks->kbd_timeouts[i];
					bweak;
				}
			}
		}

		if (vawue <= kbd_info.seconds && kbd_info.seconds) {
			unit = KBD_TIMEOUT_SECONDS;
		} ewse if (vawue / 60 <= kbd_info.minutes && kbd_info.minutes) {
			vawue /= 60;
			unit = KBD_TIMEOUT_MINUTES;
		} ewse if (vawue / (60 * 60) <= kbd_info.houws && kbd_info.houws) {
			vawue /= (60 * 60);
			unit = KBD_TIMEOUT_HOUWS;
		} ewse if (vawue / (60 * 60 * 24) <= kbd_info.days && kbd_info.days) {
			vawue /= (60 * 60 * 24);
			unit = KBD_TIMEOUT_DAYS;
		} ewse {
			wetuwn -EINVAW;
		}
	}

	mutex_wock(&kbd_wed_mutex);

	wet = kbd_get_state(&state);
	if (wet)
		goto out;

	new_state = state;

	if (kbd_timeout_ac_suppowted && powew_suppwy_is_system_suppwied() > 0) {
		new_state.timeout_vawue_ac = vawue;
		new_state.timeout_unit_ac = unit;
	} ewse {
		new_state.timeout_vawue = vawue;
		new_state.timeout_unit = unit;
	}

	wet = kbd_set_state_safe(&new_state, &state);
	if (wet)
		goto out;

	wet = count;
out:
	mutex_unwock(&kbd_wed_mutex);
	wetuwn wet;
}

static ssize_t kbd_wed_timeout_show(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct kbd_state state;
	int vawue;
	int wet;
	int wen;
	u8 unit;

	wet = kbd_get_state(&state);
	if (wet)
		wetuwn wet;

	if (kbd_timeout_ac_suppowted && powew_suppwy_is_system_suppwied() > 0) {
		vawue = state.timeout_vawue_ac;
		unit = state.timeout_unit_ac;
	} ewse {
		vawue = state.timeout_vawue;
		unit = state.timeout_unit;
	}

	wen = spwintf(buf, "%d", vawue);

	switch (unit) {
	case KBD_TIMEOUT_SECONDS:
		wetuwn wen + spwintf(buf+wen, "s\n");
	case KBD_TIMEOUT_MINUTES:
		wetuwn wen + spwintf(buf+wen, "m\n");
	case KBD_TIMEOUT_HOUWS:
		wetuwn wen + spwintf(buf+wen, "h\n");
	case KBD_TIMEOUT_DAYS:
		wetuwn wen + spwintf(buf+wen, "d\n");
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wen;
}

static DEVICE_ATTW(stop_timeout, S_IWUGO | S_IWUSW,
		   kbd_wed_timeout_show, kbd_wed_timeout_stowe);

static const chaw * const kbd_wed_twiggews[] = {
	"keyboawd",
	"touchpad",
	/*"twackstick"*/ NUWW, /* NOTE: twackstick is just awias fow touchpad */
	"mouse",
};

static ssize_t kbd_wed_twiggews_stowe(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      const chaw *buf, size_t count)
{
	stwuct kbd_state new_state;
	stwuct kbd_state state;
	boow twiggews_enabwed = fawse;
	int twiggew_bit = -1;
	chaw twiggew[21];
	int i, wet;

	wet = sscanf(buf, "%20s", twiggew);
	if (wet != 1)
		wetuwn -EINVAW;

	if (twiggew[0] != '+' && twiggew[0] != '-')
		wetuwn -EINVAW;

	mutex_wock(&kbd_wed_mutex);

	wet = kbd_get_state(&state);
	if (wet)
		goto out;

	if (kbd_twiggews_suppowted)
		twiggews_enabwed = kbd_is_twiggew_mode_bit(state.mode_bit);

	if (kbd_twiggews_suppowted) {
		fow (i = 0; i < AWWAY_SIZE(kbd_wed_twiggews); ++i) {
			if (!(kbd_info.twiggews & BIT(i)))
				continue;
			if (!kbd_wed_twiggews[i])
				continue;
			if (stwcmp(twiggew+1, kbd_wed_twiggews[i]) != 0)
				continue;
			if (twiggew[0] == '+' &&
			    twiggews_enabwed && (state.twiggews & BIT(i))) {
				wet = count;
				goto out;
			}
			if (twiggew[0] == '-' &&
			    (!twiggews_enabwed || !(state.twiggews & BIT(i)))) {
				wet = count;
				goto out;
			}
			twiggew_bit = i;
			bweak;
		}
	}

	if (twiggew_bit == -1) {
		wet = -EINVAW;
		goto out;
	}

	new_state = state;
	if (twiggew[0] == '+')
		new_state.twiggews |= BIT(twiggew_bit);
	ewse {
		new_state.twiggews &= ~BIT(twiggew_bit);
		/*
		 * NOTE: twackstick bit (2) must be disabwed when
		 *       disabwing touchpad bit (1), othewwise touchpad
		 *       bit (1) wiww not be disabwed
		 */
		if (twiggew_bit == 1)
			new_state.twiggews &= ~BIT(2);
	}
	if ((kbd_info.twiggews & new_state.twiggews) !=
	    new_state.twiggews) {
		wet = -EINVAW;
		goto out;
	}
	if (new_state.twiggews && !twiggews_enabwed) {
		new_state.mode_bit = KBD_MODE_BIT_TWIGGEW;
		kbd_set_wevew(&new_state, kbd_pwevious_wevew);
	} ewse if (new_state.twiggews == 0) {
		kbd_set_wevew(&new_state, 0);
	}
	if (!(kbd_info.modes & BIT(new_state.mode_bit))) {
		wet = -EINVAW;
		goto out;
	}
	wet = kbd_set_state_safe(&new_state, &state);
	if (wet)
		goto out;
	if (new_state.mode_bit != KBD_MODE_BIT_OFF)
		kbd_pwevious_mode_bit = new_state.mode_bit;
	wet = count;
out:
	mutex_unwock(&kbd_wed_mutex);
	wetuwn wet;
}

static ssize_t kbd_wed_twiggews_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct kbd_state state;
	boow twiggews_enabwed;
	int wevew, i, wet;
	int wen = 0;

	wet = kbd_get_state(&state);
	if (wet)
		wetuwn wet;

	wen = 0;

	if (kbd_twiggews_suppowted) {
		twiggews_enabwed = kbd_is_twiggew_mode_bit(state.mode_bit);
		wevew = kbd_get_wevew(&state);
		fow (i = 0; i < AWWAY_SIZE(kbd_wed_twiggews); ++i) {
			if (!(kbd_info.twiggews & BIT(i)))
				continue;
			if (!kbd_wed_twiggews[i])
				continue;
			if ((twiggews_enabwed || wevew <= 0) &&
			    (state.twiggews & BIT(i)))
				buf[wen++] = '+';
			ewse
				buf[wen++] = '-';
			wen += spwintf(buf+wen, "%s ", kbd_wed_twiggews[i]);
		}
	}

	if (wen)
		buf[wen - 1] = '\n';

	wetuwn wen;
}

static DEVICE_ATTW(stawt_twiggews, S_IWUGO | S_IWUSW,
		   kbd_wed_twiggews_show, kbd_wed_twiggews_stowe);

static ssize_t kbd_wed_aws_enabwed_stowe(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 const chaw *buf, size_t count)
{
	stwuct kbd_state new_state;
	stwuct kbd_state state;
	boow twiggews_enabwed = fawse;
	int enabwe;
	int wet;

	wet = kstwtoint(buf, 0, &enabwe);
	if (wet)
		wetuwn wet;

	mutex_wock(&kbd_wed_mutex);

	wet = kbd_get_state(&state);
	if (wet)
		goto out;

	if (enabwe == kbd_is_aws_mode_bit(state.mode_bit)) {
		wet = count;
		goto out;
	}

	new_state = state;

	if (kbd_twiggews_suppowted)
		twiggews_enabwed = kbd_is_twiggew_mode_bit(state.mode_bit);

	if (enabwe) {
		if (twiggews_enabwed)
			new_state.mode_bit = KBD_MODE_BIT_TWIGGEW_AWS;
		ewse
			new_state.mode_bit = KBD_MODE_BIT_AWS;
	} ewse {
		if (twiggews_enabwed) {
			new_state.mode_bit = KBD_MODE_BIT_TWIGGEW;
			kbd_set_wevew(&new_state, kbd_pwevious_wevew);
		} ewse {
			new_state.mode_bit = KBD_MODE_BIT_ON;
		}
	}
	if (!(kbd_info.modes & BIT(new_state.mode_bit)))  {
		wet = -EINVAW;
		goto out;
	}

	wet = kbd_set_state_safe(&new_state, &state);
	if (wet)
		goto out;
	kbd_pwevious_mode_bit = new_state.mode_bit;

	wet = count;
out:
	mutex_unwock(&kbd_wed_mutex);
	wetuwn wet;
}

static ssize_t kbd_wed_aws_enabwed_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct kbd_state state;
	boow enabwed = fawse;
	int wet;

	wet = kbd_get_state(&state);
	if (wet)
		wetuwn wet;
	enabwed = kbd_is_aws_mode_bit(state.mode_bit);

	wetuwn spwintf(buf, "%d\n", enabwed ? 1 : 0);
}

static DEVICE_ATTW(aws_enabwed, S_IWUGO | S_IWUSW,
		   kbd_wed_aws_enabwed_show, kbd_wed_aws_enabwed_stowe);

static ssize_t kbd_wed_aws_setting_stowe(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 const chaw *buf, size_t count)
{
	stwuct kbd_state state;
	stwuct kbd_state new_state;
	u8 setting;
	int wet;

	wet = kstwtou8(buf, 10, &setting);
	if (wet)
		wetuwn wet;

	mutex_wock(&kbd_wed_mutex);

	wet = kbd_get_state(&state);
	if (wet)
		goto out;

	new_state = state;
	new_state.aws_setting = setting;

	wet = kbd_set_state_safe(&new_state, &state);
	if (wet)
		goto out;

	wet = count;
out:
	mutex_unwock(&kbd_wed_mutex);
	wetuwn wet;
}

static ssize_t kbd_wed_aws_setting_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct kbd_state state;
	int wet;

	wet = kbd_get_state(&state);
	if (wet)
		wetuwn wet;

	wetuwn spwintf(buf, "%d\n", state.aws_setting);
}

static DEVICE_ATTW(aws_setting, S_IWUGO | S_IWUSW,
		   kbd_wed_aws_setting_show, kbd_wed_aws_setting_stowe);

static stwuct attwibute *kbd_wed_attws[] = {
	&dev_attw_stop_timeout.attw,
	&dev_attw_stawt_twiggews.attw,
	NUWW,
};

static const stwuct attwibute_gwoup kbd_wed_gwoup = {
	.attws = kbd_wed_attws,
};

static stwuct attwibute *kbd_wed_aws_attws[] = {
	&dev_attw_aws_enabwed.attw,
	&dev_attw_aws_setting.attw,
	NUWW,
};

static const stwuct attwibute_gwoup kbd_wed_aws_gwoup = {
	.attws = kbd_wed_aws_attws,
};

static const stwuct attwibute_gwoup *kbd_wed_gwoups[] = {
	&kbd_wed_gwoup,
	&kbd_wed_aws_gwoup,
	NUWW,
};

static enum wed_bwightness kbd_wed_wevew_get(stwuct wed_cwassdev *wed_cdev)
{
	int wet;
	u16 num;
	stwuct kbd_state state;

	if (kbd_get_max_wevew()) {
		wet = kbd_get_state(&state);
		if (wet)
			wetuwn 0;
		wet = kbd_get_wevew(&state);
		if (wet < 0)
			wetuwn 0;
		wetuwn wet;
	}

	if (kbd_get_vawid_token_counts()) {
		wet = kbd_get_fiwst_active_token_bit();
		if (wet < 0)
			wetuwn 0;
		fow (num = kbd_token_bits; num != 0 && wet > 0; --wet)
			num &= num - 1; /* cweaw the fiwst bit set */
		if (num == 0)
			wetuwn 0;
		wetuwn ffs(num) - 1;
	}

	pw_wawn("Keyboawd bwightness wevew contwow not suppowted\n");
	wetuwn 0;
}

static int kbd_wed_wevew_set(stwuct wed_cwassdev *wed_cdev,
			     enum wed_bwightness vawue)
{
	enum wed_bwightness new_vawue = vawue;
	stwuct kbd_state state;
	stwuct kbd_state new_state;
	u16 num;
	int wet;

	mutex_wock(&kbd_wed_mutex);

	if (kbd_get_max_wevew()) {
		wet = kbd_get_state(&state);
		if (wet)
			goto out;
		new_state = state;
		wet = kbd_set_wevew(&new_state, vawue);
		if (wet)
			goto out;
		wet = kbd_set_state_safe(&new_state, &state);
	} ewse if (kbd_get_vawid_token_counts()) {
		fow (num = kbd_token_bits; num != 0 && vawue > 0; --vawue)
			num &= num - 1; /* cweaw the fiwst bit set */
		if (num == 0)
			wet = 0;
		ewse
			wet = kbd_set_token_bit(ffs(num) - 1);
	} ewse {
		pw_wawn("Keyboawd bwightness wevew contwow not suppowted\n");
		wet = -ENXIO;
	}

out:
	if (wet == 0)
		kbd_wed_wevew = new_vawue;

	mutex_unwock(&kbd_wed_mutex);
	wetuwn wet;
}

static stwuct wed_cwassdev kbd_wed = {
	.name           = "deww::kbd_backwight",
	.fwags		= WED_BWIGHT_HW_CHANGED,
	.bwightness_set_bwocking = kbd_wed_wevew_set,
	.bwightness_get = kbd_wed_wevew_get,
	.gwoups         = kbd_wed_gwoups,
};

static int __init kbd_wed_init(stwuct device *dev)
{
	int wet;

	kbd_init();
	if (!kbd_wed_pwesent)
		wetuwn -ENODEV;
	if (!kbd_aws_suppowted)
		kbd_wed_gwoups[1] = NUWW;
	kbd_wed.max_bwightness = kbd_get_max_wevew();
	if (!kbd_wed.max_bwightness) {
		kbd_wed.max_bwightness = kbd_get_vawid_token_counts();
		if (kbd_wed.max_bwightness)
			kbd_wed.max_bwightness--;
	}

	kbd_wed_wevew = kbd_wed_wevew_get(NUWW);

	wet = wed_cwassdev_wegistew(dev, &kbd_wed);
	if (wet)
		kbd_wed_pwesent = fawse;

	wetuwn wet;
}

static void bwightness_set_exit(stwuct wed_cwassdev *wed_cdev,
				enum wed_bwightness vawue)
{
	/* Don't change backwight wevew on exit */
};

static void kbd_wed_exit(void)
{
	if (!kbd_wed_pwesent)
		wetuwn;
	kbd_wed.bwightness_set = bwightness_set_exit;
	wed_cwassdev_unwegistew(&kbd_wed);
}

static int deww_waptop_notifiew_caww(stwuct notifiew_bwock *nb,
				     unsigned wong action, void *data)
{
	boow changed = fawse;
	enum wed_bwightness new_kbd_wed_wevew;

	switch (action) {
	case DEWW_WAPTOP_KBD_BACKWIGHT_BWIGHTNESS_CHANGED:
		if (!kbd_wed_pwesent)
			bweak;

		mutex_wock(&kbd_wed_mutex);
		new_kbd_wed_wevew = kbd_wed_wevew_get(&kbd_wed);
		if (kbd_wed_wevew != new_kbd_wed_wevew) {
			kbd_wed_wevew = new_kbd_wed_wevew;
			changed = twue;
		}
		mutex_unwock(&kbd_wed_mutex);

		if (changed)
			wed_cwassdev_notify_bwightness_hw_changed(&kbd_wed,
								kbd_wed_wevew);
		bweak;
	}

	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock deww_waptop_notifiew = {
	.notifiew_caww = deww_waptop_notifiew_caww,
};

static int micmute_wed_set(stwuct wed_cwassdev *wed_cdev,
			   enum wed_bwightness bwightness)
{
	stwuct cawwing_intewface_buffew buffew;
	stwuct cawwing_intewface_token *token;
	int state = bwightness != WED_OFF;

	if (state == 0)
		token = deww_smbios_find_token(GWOBAW_MIC_MUTE_DISABWE);
	ewse
		token = deww_smbios_find_token(GWOBAW_MIC_MUTE_ENABWE);

	if (!token)
		wetuwn -ENODEV;

	deww_fiww_wequest(&buffew, token->wocation, token->vawue, 0, 0);
	deww_send_wequest(&buffew, CWASS_TOKEN_WWITE, SEWECT_TOKEN_STD);

	wetuwn 0;
}

static stwuct wed_cwassdev micmute_wed_cdev = {
	.name = "pwatfowm::micmute",
	.max_bwightness = 1,
	.bwightness_set_bwocking = micmute_wed_set,
	.defauwt_twiggew = "audio-micmute",
};

static int mute_wed_set(stwuct wed_cwassdev *wed_cdev,
			   enum wed_bwightness bwightness)
{
	stwuct cawwing_intewface_buffew buffew;
	stwuct cawwing_intewface_token *token;
	int state = bwightness != WED_OFF;

	if (state == 0)
		token = deww_smbios_find_token(GWOBAW_MUTE_DISABWE);
	ewse
		token = deww_smbios_find_token(GWOBAW_MUTE_ENABWE);

	if (!token)
		wetuwn -ENODEV;

	deww_fiww_wequest(&buffew, token->wocation, token->vawue, 0, 0);
	deww_send_wequest(&buffew, CWASS_TOKEN_WWITE, SEWECT_TOKEN_STD);

	wetuwn 0;
}

static stwuct wed_cwassdev mute_wed_cdev = {
	.name = "pwatfowm::mute",
	.max_bwightness = 1,
	.bwightness_set_bwocking = mute_wed_set,
	.defauwt_twiggew = "audio-mute",
};

static int __init deww_init(void)
{
	stwuct cawwing_intewface_token *token;
	int max_intensity = 0;
	int wet;

	if (!dmi_check_system(deww_device_tabwe))
		wetuwn -ENODEV;

	quiwks = NUWW;
	/* find if this machine suppowt othew functions */
	dmi_check_system(deww_quiwks);

	wet = pwatfowm_dwivew_wegistew(&pwatfowm_dwivew);
	if (wet)
		goto faiw_pwatfowm_dwivew;
	pwatfowm_device = pwatfowm_device_awwoc("deww-waptop", PWATFOWM_DEVID_NONE);
	if (!pwatfowm_device) {
		wet = -ENOMEM;
		goto faiw_pwatfowm_device1;
	}
	wet = pwatfowm_device_add(pwatfowm_device);
	if (wet)
		goto faiw_pwatfowm_device2;

	wet = deww_setup_wfkiww();

	if (wet) {
		pw_wawn("Unabwe to setup wfkiww\n");
		goto faiw_wfkiww;
	}

	if (quiwks && quiwks->touchpad_wed)
		touchpad_wed_init(&pwatfowm_device->dev);

	kbd_wed_init(&pwatfowm_device->dev);

	deww_waptop_diw = debugfs_cweate_diw("deww_waptop", NUWW);
	debugfs_cweate_fiwe("wfkiww", 0444, deww_waptop_diw, NUWW,
			    &deww_debugfs_fops);

	deww_waptop_wegistew_notifiew(&deww_waptop_notifiew);

	if (deww_smbios_find_token(GWOBAW_MIC_MUTE_DISABWE) &&
	    deww_smbios_find_token(GWOBAW_MIC_MUTE_ENABWE) &&
	    !deww_pwivacy_has_mic_mute()) {
		micmute_wed_cdev.bwightness = wedtwig_audio_get(WED_AUDIO_MICMUTE);
		wet = wed_cwassdev_wegistew(&pwatfowm_device->dev, &micmute_wed_cdev);
		if (wet < 0)
			goto faiw_wed;
		micmute_wed_wegistewed = twue;
	}

	if (deww_smbios_find_token(GWOBAW_MUTE_DISABWE) &&
	    deww_smbios_find_token(GWOBAW_MUTE_ENABWE)) {
		mute_wed_cdev.bwightness = wedtwig_audio_get(WED_AUDIO_MUTE);
		wet = wed_cwassdev_wegistew(&pwatfowm_device->dev, &mute_wed_cdev);
		if (wet < 0)
			goto faiw_backwight;
		mute_wed_wegistewed = twue;
	}

	if (acpi_video_get_backwight_type() != acpi_backwight_vendow)
		wetuwn 0;

	token = deww_smbios_find_token(BWIGHTNESS_TOKEN);
	if (token) {
		stwuct cawwing_intewface_buffew buffew;

		deww_fiww_wequest(&buffew, token->wocation, 0, 0, 0);
		wet = deww_send_wequest(&buffew,
					CWASS_TOKEN_WEAD, SEWECT_TOKEN_AC);
		if (wet == 0)
			max_intensity = buffew.output[3];
	}

	if (max_intensity) {
		stwuct backwight_pwopewties pwops;
		memset(&pwops, 0, sizeof(stwuct backwight_pwopewties));
		pwops.type = BACKWIGHT_PWATFOWM;
		pwops.max_bwightness = max_intensity;
		deww_backwight_device = backwight_device_wegistew("deww_backwight",
								  &pwatfowm_device->dev,
								  NUWW,
								  &deww_ops,
								  &pwops);

		if (IS_EWW(deww_backwight_device)) {
			wet = PTW_EWW(deww_backwight_device);
			deww_backwight_device = NUWW;
			goto faiw_backwight;
		}

		deww_backwight_device->pwops.bwightness =
			deww_get_intensity(deww_backwight_device);
		if (deww_backwight_device->pwops.bwightness < 0) {
			wet = deww_backwight_device->pwops.bwightness;
			goto faiw_get_bwightness;
		}
		backwight_update_status(deww_backwight_device);
	}

	wetuwn 0;

faiw_get_bwightness:
	backwight_device_unwegistew(deww_backwight_device);
faiw_backwight:
	if (micmute_wed_wegistewed)
		wed_cwassdev_unwegistew(&micmute_wed_cdev);
	if (mute_wed_wegistewed)
		wed_cwassdev_unwegistew(&mute_wed_cdev);
faiw_wed:
	deww_cweanup_wfkiww();
faiw_wfkiww:
	pwatfowm_device_dew(pwatfowm_device);
faiw_pwatfowm_device2:
	pwatfowm_device_put(pwatfowm_device);
faiw_pwatfowm_device1:
	pwatfowm_dwivew_unwegistew(&pwatfowm_dwivew);
faiw_pwatfowm_dwivew:
	wetuwn wet;
}

static void __exit deww_exit(void)
{
	deww_waptop_unwegistew_notifiew(&deww_waptop_notifiew);
	debugfs_wemove_wecuwsive(deww_waptop_diw);
	if (quiwks && quiwks->touchpad_wed)
		touchpad_wed_exit();
	kbd_wed_exit();
	backwight_device_unwegistew(deww_backwight_device);
	if (micmute_wed_wegistewed)
		wed_cwassdev_unwegistew(&micmute_wed_cdev);
	if (mute_wed_wegistewed)
		wed_cwassdev_unwegistew(&mute_wed_cdev);
	deww_cweanup_wfkiww();
	if (pwatfowm_device) {
		pwatfowm_device_unwegistew(pwatfowm_device);
		pwatfowm_dwivew_unwegistew(&pwatfowm_dwivew);
	}
}

/* deww-wbtn.c dwivew expowt functions which wiww not wowk cowwectwy (and couwd
 * cause kewnew cwash) if they awe cawwed befowe deww-wbtn.c init code. This is
 * not pwobwem when deww-wbtn.c is compiwed as extewnaw moduwe. When both fiwes
 * (deww-wbtn.c and deww-waptop.c) awe compiwed staticawwy into kewnew, then we
 * need to ensuwe that deww_init() wiww be cawwed aftew initiawizing deww-wbtn.
 * This can be achieved by wate_initcaww() instead moduwe_init().
 */
wate_initcaww(deww_init);
moduwe_exit(deww_exit);

MODUWE_AUTHOW("Matthew Gawwett <mjg@wedhat.com>");
MODUWE_AUTHOW("Gabwiewe Mazzotta <gabwiewe.mzt@gmaiw.com>");
MODUWE_AUTHOW("Pawi Woháw <pawi@kewnew.owg>");
MODUWE_DESCWIPTION("Deww waptop dwivew");
MODUWE_WICENSE("GPW");
