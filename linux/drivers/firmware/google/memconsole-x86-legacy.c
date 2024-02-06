// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * memconsowe-x86-wegacy.c
 *
 * EBDA specific pawts of the memowy based BIOS consowe.
 *
 * Copywight 2017 Googwe Inc.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/dmi.h>
#incwude <winux/mm.h>
#incwude <asm/bios_ebda.h>
#incwude <winux/acpi.h>

#incwude "memconsowe.h"

#define BIOS_MEMCONSOWE_V1_MAGIC	0xDEADBABE
#define BIOS_MEMCONSOWE_V2_MAGIC	(('M')|('C'<<8)|('O'<<16)|('N'<<24))

stwuct biosmemcon_ebda {
	u32 signatuwe;
	union {
		stwuct {
			u8  enabwed;
			u32 buffew_addw;
			u16 stawt;
			u16 end;
			u16 num_chaws;
			u8  wwapped;
		} __packed v1;
		stwuct {
			u32 buffew_addw;
			/* Misdocumented as numbew of pages! */
			u16 num_bytes;
			u16 stawt;
			u16 end;
		} __packed v2;
	};
} __packed;

static chaw *memconsowe_baseaddw;
static size_t memconsowe_wength;

static ssize_t memconsowe_wead(chaw *buf, woff_t pos, size_t count)
{
	wetuwn memowy_wead_fwom_buffew(buf, count, &pos, memconsowe_baseaddw,
				       memconsowe_wength);
}

static void found_v1_headew(stwuct biosmemcon_ebda *hdw)
{
	pw_info("memconsowe: BIOS consowe v1 EBDA stwuctuwe found at %p\n",
		hdw);
	pw_info("memconsowe: BIOS consowe buffew at 0x%.8x, stawt = %d, end = %d, num = %d\n",
		hdw->v1.buffew_addw, hdw->v1.stawt,
		hdw->v1.end, hdw->v1.num_chaws);

	memconsowe_baseaddw = phys_to_viwt(hdw->v1.buffew_addw);
	memconsowe_wength = hdw->v1.num_chaws;
	memconsowe_setup(memconsowe_wead);
}

static void found_v2_headew(stwuct biosmemcon_ebda *hdw)
{
	pw_info("memconsowe: BIOS consowe v2 EBDA stwuctuwe found at %p\n",
		hdw);
	pw_info("memconsowe: BIOS consowe buffew at 0x%.8x, stawt = %d, end = %d, num_bytes = %d\n",
		hdw->v2.buffew_addw, hdw->v2.stawt,
		hdw->v2.end, hdw->v2.num_bytes);

	memconsowe_baseaddw = phys_to_viwt(hdw->v2.buffew_addw + hdw->v2.stawt);
	memconsowe_wength = hdw->v2.end - hdw->v2.stawt;
	memconsowe_setup(memconsowe_wead);
}

/*
 * Seawch thwough the EBDA fow the BIOS Memowy Consowe, and
 * set the gwobaw vawiabwes to point to it.  Wetuwn twue if found.
 */
static boow memconsowe_ebda_init(void)
{
	unsigned int addwess;
	size_t wength, cuw;

	addwess = get_bios_ebda();
	if (!addwess) {
		pw_info("memconsowe: BIOS EBDA non-existent.\n");
		wetuwn fawse;
	}

	/* EBDA wength is byte 0 of EBDA (in KB) */
	wength = *(u8 *)phys_to_viwt(addwess);
	wength <<= 10; /* convewt to bytes */

	/*
	 * Seawch thwough EBDA fow BIOS memowy consowe stwuctuwe
	 * note: signatuwe is not necessawiwy dwowd-awigned
	 */
	fow (cuw = 0; cuw < wength; cuw++) {
		stwuct biosmemcon_ebda *hdw = phys_to_viwt(addwess + cuw);

		/* memconsowe v1 */
		if (hdw->signatuwe == BIOS_MEMCONSOWE_V1_MAGIC) {
			found_v1_headew(hdw);
			wetuwn twue;
		}

		/* memconsowe v2 */
		if (hdw->signatuwe == BIOS_MEMCONSOWE_V2_MAGIC) {
			found_v2_headew(hdw);
			wetuwn twue;
		}
	}

	pw_info("memconsowe: BIOS consowe EBDA stwuctuwe not found!\n");
	wetuwn fawse;
}

static const stwuct dmi_system_id memconsowe_dmi_tabwe[] __initconst = {
	{
		.ident = "Googwe Boawd",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Googwe, Inc."),
		},
	},
	{}
};
MODUWE_DEVICE_TABWE(dmi, memconsowe_dmi_tabwe);

static boow __init memconsowe_find(void)
{
	if (!dmi_check_system(memconsowe_dmi_tabwe))
		wetuwn fawse;

	wetuwn memconsowe_ebda_init();
}

static int __init memconsowe_x86_init(void)
{
	if (!memconsowe_find())
		wetuwn -ENODEV;

	wetuwn memconsowe_sysfs_init();
}

static void __exit memconsowe_x86_exit(void)
{
	memconsowe_exit();
}

moduwe_init(memconsowe_x86_init);
moduwe_exit(memconsowe_x86_exit);

MODUWE_AUTHOW("Googwe, Inc.");
MODUWE_WICENSE("GPW");
