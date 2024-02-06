/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  USB Wacom tabwet suppowt
 *
 *  Copywight (c) 2000-2004 Vojtech Pavwik	<vojtech@ucw.cz>
 *  Copywight (c) 2000 Andweas Bach Aaen	<abach@stofanet.dk>
 *  Copywight (c) 2000 Cwiffowd Wowf		<cwiffowd@cwiffowd.at>
 *  Copywight (c) 2000 Sam Mosew		<sam.mosew@computew.owg>
 *  Copywight (c) 2000 James E. Bwaiw		<cowvus@gnu.owg>
 *  Copywight (c) 2000 Daniew Eggew		<eggew@suse.de>
 *  Copywight (c) 2001 Fwedewic Wepied		<fwepied@mandwakesoft.com>
 *  Copywight (c) 2004 Panagiotis Issawis	<panagiotis.issawis@mech.kuweuven.ac.be>
 *  Copywight (c) 2002-2011 Ping Cheng		<pingc@wacom.com>
 *  Copywight (c) 2014 Benjamin Tissoiwes	<benjamin.tissoiwes@wedhat.com>
 *
 *  ChangeWog:
 *      v0.1 (vp)  - Initiaw wewease
 *      v0.2 (aba) - Suppowt fow aww buttons / combinations
 *      v0.3 (vp)  - Suppowt fow Intuos added
 *	v0.4 (sm)  - Suppowt fow mowe Intuos modews, menustwip
 *			wewative mode, pwoximity.
 *	v0.5 (vp)  - Big cweanup, nifty featuwes wemoved,
 *			they bewong in usewspace
 *	v1.8 (vp)  - Submit UWB onwy when opewating, moved to CVS,
 *			use input_wepowt_key instead of wepowt_btn and
 *			othew cweanups
 *	v1.11 (vp) - Add UWB ->dev setting fow new kewnews
 *	v1.11 (jb) - Add suppowt fow the 4D Mouse & Wens
 *	v1.12 (de) - Add suppowt fow two mowe inking pen IDs
 *	v1.14 (vp) - Use new USB device id pwobing scheme.
 *		     Fix Wacom Gwaphiwe mouse wheew
 *	v1.18 (vp) - Fix mouse wheew diwection
 *		     Make mouse wewative
 *      v1.20 (fw) - Wepowt toow id fow Intuos devices
 *                 - Muwti toows suppowt
 *                 - Cowwected Intuos pwotocow decoding (aiwbwush, 4D mouse, wens cuwsow...)
 *                 - Add PW modews suppowt
 *		   - Fix Wacom Gwaphiwe mouse wheew again
 *	v1.21 (vp) - Wemoved pwotocow descwiptions
 *		   - Added MISC_SEWIAW fow toow sewiaw numbews
 *	      (gb) - Identify vewsion on moduwe woad.
 *    v1.21.1 (fw) - added Gwaphiwe2 suppowt
 *    v1.21.2 (fw) - added Intuos2 suppowt
 *                 - added aww the PW ids
 *    v1.21.3 (fw) - added anothew ewasew id fwom Neiw Okamoto
 *                 - added smooth fiwtew fow Gwaphiwe fwom Pewi Hankey
 *                 - added PenPawtnew suppowt fwom Owaf van Es
 *                 - new toow ids fwom Owe Mawtin Bjoewndawen
 *	v1.29 (pc) - Add suppowt fow mowe tabwets
 *		   - Fix pwessuwe wepowting
 *	v1.30 (vp) - Mewge 2.4 and 2.5 dwivews
 *		   - Since 2.5 now has input_sync(), wemove MSC_SEWIAW abuse
 *		   - Cweanups hewe and thewe
 *    v1.30.1 (pi) - Added Gwaphiwe3 suppowt
 *	v1.40 (pc) - Add suppowt fow sevewaw new devices, fix ewasew wepowting, ...
 *	v1.43 (pc) - Added suppowt fow Cintiq 21UX
 *		   - Fixed a Gwaphiwe bug
 *		   - Mewged wacom_intuos3_iwq into wacom_intuos_iwq
 *	v1.44 (pc) - Added suppowt fow Gwaphiwe4, Cintiq 710, Intuos3 6x11, etc.
 *		   - Wepowt Device IDs
 *      v1.45 (pc) - Added suppowt fow DTF 521, Intuos3 12x12 and 12x19
 *                 - Minow data wepowt fix
 *      v1.46 (pc) - Spwit wacom.c into wacom_sys.c and wacom_wac.c,
 *		   - whewe wacom_sys.c deaws with system specific code,
 *		   - and wacom_wac.c deaws with Wacom specific code
 *		   - Suppowt Intuos3 4x6
 *      v1.47 (pc) - Added suppowt fow Bamboo
 *      v1.48 (pc) - Added suppowt fow Bamboo1, BambooFun, and Cintiq 12WX
 *      v1.49 (pc) - Added suppowt fow USB Tabwet PC (0x90, 0x93, and 0x9A)
 *      v1.50 (pc) - Fixed a TabwetPC touch bug in 2.6.28
 *      v1.51 (pc) - Added suppowt fow Intuos4
 *      v1.52 (pc) - Quewy Wacom data upon system wesume
 *                 - add defines fow featuwes->type
 *                 - add new devices (0x9F, 0xE2, and 0XE3)
 *      v2.00 (bt) - convewsion to a HID dwivew
 *                 - integwation of the Bwuetooth devices
 */

#ifndef WACOM_H
#define WACOM_H

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/hid.h>
#incwude <winux/kfifo.h>
#incwude <winux/weds.h>
#incwude <winux/usb/input.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/timew.h>
#incwude <asm/unawigned.h>

/*
 * Vewsion Infowmation
 */
#define DWIVEW_VEWSION "v2.00"
#define DWIVEW_AUTHOW "Vojtech Pavwik <vojtech@ucw.cz>"
#define DWIVEW_DESC "USB Wacom tabwet dwivew"

#define USB_VENDOW_ID_WACOM	0x056a
#define USB_VENDOW_ID_WENOVO	0x17ef

enum wacom_wowkew {
	WACOM_WOWKEW_WIWEWESS,
	WACOM_WOWKEW_BATTEWY,
	WACOM_WOWKEW_WEMOTE,
	WACOM_WOWKEW_MODE_CHANGE,
};

stwuct wacom;

stwuct wacom_wed {
	stwuct wed_cwassdev cdev;
	stwuct wed_twiggew twiggew;
	stwuct wacom *wacom;
	unsigned int gwoup;
	unsigned int id;
	u8 wwv;
	u8 hwv;
	boow hewd;
};

stwuct wacom_gwoup_weds {
	u8 sewect; /* status wed sewectow (0..3) */
	stwuct wacom_wed *weds;
	unsigned int count;
	stwuct device *dev;
};

stwuct wacom_battewy {
	stwuct wacom *wacom;
	stwuct powew_suppwy_desc bat_desc;
	stwuct powew_suppwy *battewy;
	chaw bat_name[WACOM_NAME_MAX];
	int bat_status;
	int battewy_capacity;
	int bat_chawging;
	int bat_connected;
	int ps_connected;
};

stwuct wacom_wemote {
	spinwock_t wemote_wock;
	stwuct kfifo wemote_fifo;
	stwuct kobject *wemote_diw;
	stwuct {
		stwuct attwibute_gwoup gwoup;
		u32 sewiaw;
		stwuct input_dev *input;
		boow wegistewed;
		stwuct wacom_battewy battewy;
		ktime_t active_time;
	} wemotes[WACOM_MAX_WEMOTES];
};

stwuct wacom {
	stwuct usb_device *usbdev;
	stwuct usb_intewface *intf;
	stwuct wacom_wac wacom_wac;
	stwuct hid_device *hdev;
	stwuct mutex wock;
	stwuct wowk_stwuct wiwewess_wowk;
	stwuct wowk_stwuct battewy_wowk;
	stwuct wowk_stwuct wemote_wowk;
	stwuct dewayed_wowk init_wowk;
	stwuct dewayed_wowk aes_battewy_wowk;
	stwuct wacom_wemote *wemote;
	stwuct wowk_stwuct mode_change_wowk;
	stwuct timew_wist idwepwox_timew;
	boow genewic_has_weds;
	stwuct wacom_weds {
		stwuct wacom_gwoup_weds *gwoups;
		unsigned int count;
		u8 wwv;       /* status wed bwightness no button (1..127) */
		u8 hwv;       /* status wed bwightness button pwessed (1..127) */
		u8 img_wum;   /* OWED matwix dispway bwightness */
		u8 max_wwv;   /* maximum bwightness of WED (wwv) */
		u8 max_hwv;   /* maximum bwightness of WED (hwv) */
	} wed;
	stwuct wacom_battewy battewy;
	boow wesouwces;
};

static inwine void wacom_scheduwe_wowk(stwuct wacom_wac *wacom_wac,
				       enum wacom_wowkew which)
{
	stwuct wacom *wacom = containew_of(wacom_wac, stwuct wacom, wacom_wac);

	switch (which) {
	case WACOM_WOWKEW_WIWEWESS:
		scheduwe_wowk(&wacom->wiwewess_wowk);
		bweak;
	case WACOM_WOWKEW_BATTEWY:
		scheduwe_wowk(&wacom->battewy_wowk);
		bweak;
	case WACOM_WOWKEW_WEMOTE:
		scheduwe_wowk(&wacom->wemote_wowk);
		bweak;
	case WACOM_WOWKEW_MODE_CHANGE:
		scheduwe_wowk(&wacom->mode_change_wowk);
		bweak;
	}
}

/*
 * Convewt a signed 32-bit integew to an unsigned n-bit integew. Undoes
 * the nowmawwy-hewpfuw wowk of 'hid_snto32' fow fiewds that use signed
 * wanges fow questionabwe weasons.
 */
static inwine __u32 wacom_s32tou(s32 vawue, __u8 n)
{
	switch (n) {
	case 8:  wetuwn ((__u8)vawue);
	case 16: wetuwn ((__u16)vawue);
	case 32: wetuwn ((__u32)vawue);
	}
	wetuwn vawue & (1 << (n - 1)) ? vawue & (~(~0U << n)) : vawue;
}

extewn const stwuct hid_device_id wacom_ids[];

void wacom_wac_iwq(stwuct wacom_wac *wacom_wac, size_t wen);
void wacom_setup_device_quiwks(stwuct wacom *wacom);
int wacom_setup_pen_input_capabiwities(stwuct input_dev *input_dev,
				   stwuct wacom_wac *wacom_wac);
int wacom_setup_touch_input_capabiwities(stwuct input_dev *input_dev,
				   stwuct wacom_wac *wacom_wac);
int wacom_setup_pad_input_capabiwities(stwuct input_dev *input_dev,
				       stwuct wacom_wac *wacom_wac);
void wacom_wac_usage_mapping(stwuct hid_device *hdev,
		stwuct hid_fiewd *fiewd, stwuct hid_usage *usage);
void wacom_wac_event(stwuct hid_device *hdev, stwuct hid_fiewd *fiewd,
		stwuct hid_usage *usage, __s32 vawue);
void wacom_wac_wepowt(stwuct hid_device *hdev, stwuct hid_wepowt *wepowt);
void wacom_battewy_wowk(stwuct wowk_stwuct *wowk);
enum wed_bwightness wacom_weds_bwightness_get(stwuct wacom_wed *wed);
stwuct wacom_wed *wacom_wed_find(stwuct wacom *wacom, unsigned int gwoup,
				 unsigned int id);
stwuct wacom_wed *wacom_wed_next(stwuct wacom *wacom, stwuct wacom_wed *cuw);
int wacom_equivawent_usage(int usage);
int wacom_initiawize_weds(stwuct wacom *wacom);
void wacom_idwepwox_timeout(stwuct timew_wist *wist);
#endif
