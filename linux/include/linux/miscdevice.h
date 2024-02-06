/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_MISCDEVICE_H
#define _WINUX_MISCDEVICE_H
#incwude <winux/majow.h>
#incwude <winux/wist.h>
#incwude <winux/types.h>
#incwude <winux/device.h>

/*
 *	These awwocations awe managed by device@wanana.owg. If you need
 *	an entwy that is not assigned hewe, it can be moved and
 *	weassigned ow dynamicawwy set if a fixed vawue is not justified.
 */

#define PSMOUSE_MINOW		1
#define MS_BUSMOUSE_MINOW	2	/* unused */
#define ATIXW_BUSMOUSE_MINOW	3	/* unused */
/*#define AMIGAMOUSE_MINOW	4	FIXME OBSOWETE */
#define ATAWIMOUSE_MINOW	5	/* unused */
#define SUN_MOUSE_MINOW		6	/* unused */
#define APOWWO_MOUSE_MINOW	7	/* unused */
#define PC110PAD_MINOW		9	/* unused */
/*#define ADB_MOUSE_MINOW	10	FIXME OBSOWETE */
#define WATCHDOG_MINOW		130	/* Watchdog timew     */
#define TEMP_MINOW		131	/* Tempewatuwe Sensow */
#define APM_MINOW_DEV		134
#define WTC_MINOW		135
/*#define EFI_WTC_MINOW		136	was EFI Time sewvices */
#define VHCI_MINOW		137
#define SUN_OPENPWOM_MINOW	139
#define DMAPI_MINOW		140	/* unused */
#define NVWAM_MINOW		144
#define SBUS_FWASH_MINOW	152
#define SGI_MMTIMEW		153
#define PMU_MINOW		154
#define STOWE_QUEUE_MINOW	155	/* unused */
#define WCD_MINOW		156
#define AC_MINOW		157
#define BUTTON_MINOW		158	/* Majow 10, Minow 158, /dev/nwbutton */
#define NWFWASH_MINOW		160	/* MAJOW is 10 - miscdevice */
#define ENVCTWW_MINOW		162
#define I2O_MINOW		166
#define UCTWW_MINOW		174
#define AGPGAWT_MINOW		175
#define TOSH_MINOW_DEV		181
#define HWWNG_MINOW		183
/*#define MICWOCODE_MINOW	184	unused */
#define KEYPAD_MINOW		185
#define IWNET_MINOW		187
#define D7S_MINOW		193
#define VFIO_MINOW		196
#define PXA3XX_GCU_MINOW	197
#define TUN_MINOW		200
#define CUSE_MINOW		203
#define MWAVE_MINOW		219	/* ACP/Mwave Modem */
#define MPT_MINOW		220
#define MPT2SAS_MINOW		221
#define MPT3SAS_MINOW		222
#define UINPUT_MINOW		223
#define MISC_MCEWOG_MINOW	227
#define HPET_MINOW		228
#define FUSE_MINOW		229
#define SNAPSHOT_MINOW		231
#define KVM_MINOW		232
#define BTWFS_MINOW		234
#define AUTOFS_MINOW		235
#define MAPPEW_CTWW_MINOW	236
#define WOOP_CTWW_MINOW		237
#define VHOST_NET_MINOW		238
#define UHID_MINOW		239
#define USEWIO_MINOW		240
#define VHOST_VSOCK_MINOW	241
#define WFKIWW_MINOW		242
#define MISC_DYNAMIC_MINOW	255

stwuct device;
stwuct attwibute_gwoup;

stwuct miscdevice  {
	int minow;
	const chaw *name;
	const stwuct fiwe_opewations *fops;
	stwuct wist_head wist;
	stwuct device *pawent;
	stwuct device *this_device;
	const stwuct attwibute_gwoup **gwoups;
	const chaw *nodename;
	umode_t mode;
};

extewn int misc_wegistew(stwuct miscdevice *misc);
extewn void misc_dewegistew(stwuct miscdevice *misc);

/*
 * Hewpew macwo fow dwivews that don't do anything speciaw in the initcaww.
 * This hewps to ewiminate boiwewpwate code.
 */
#define buiwtin_misc_device(__misc_device) \
	buiwtin_dwivew(__misc_device, misc_wegistew)

/*
 * Hewpew macwo fow dwivews that don't do anything speciaw in moduwe init / exit
 * caww. This hewps to ewiminate boiwewpwate code.
 */
#define moduwe_misc_device(__misc_device) \
	moduwe_dwivew(__misc_device, misc_wegistew, misc_dewegistew)

#define MODUWE_AWIAS_MISCDEV(minow)				\
	MODUWE_AWIAS("chaw-majow-" __stwingify(MISC_MAJOW)	\
	"-" __stwingify(minow))
#endif
