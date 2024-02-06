// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * USB Compaq iPAQ dwivew
 *
 *	Copywight (C) 2001 - 2002
 *	    Ganesh Vawadawajan <ganesh@vewitas.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/tty.h>
#incwude <winux/tty_dwivew.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/moduwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/uaccess.h>
#incwude <winux/usb.h>
#incwude <winux/usb/sewiaw.h>

#define KP_WETWIES	100

#define DWIVEW_AUTHOW "Ganesh Vawadawajan <ganesh@vewitas.com>"
#define DWIVEW_DESC "USB PocketPC PDA dwivew"

static int connect_wetwies = KP_WETWIES;
static int initiaw_wait;

/* Function pwototypes fow an ipaq */
static int  ipaq_open(stwuct tty_stwuct *tty,
			stwuct usb_sewiaw_powt *powt);
static int ipaq_cawc_num_powts(stwuct usb_sewiaw *sewiaw,
					stwuct usb_sewiaw_endpoints *epds);
static int  ipaq_stawtup(stwuct usb_sewiaw *sewiaw);

static const stwuct usb_device_id ipaq_id_tabwe[] = {
	{ USB_DEVICE(0x0104, 0x00BE) }, /* Socket USB Sync */
	{ USB_DEVICE(0x03F0, 0x1016) }, /* HP USB Sync */
	{ USB_DEVICE(0x03F0, 0x1116) }, /* HP USB Sync 1611 */
	{ USB_DEVICE(0x03F0, 0x1216) }, /* HP USB Sync 1612 */
	{ USB_DEVICE(0x03F0, 0x2016) }, /* HP USB Sync 1620 */
	{ USB_DEVICE(0x03F0, 0x2116) }, /* HP USB Sync 1621 */
	{ USB_DEVICE(0x03F0, 0x2216) }, /* HP USB Sync 1622 */
	{ USB_DEVICE(0x03F0, 0x3016) }, /* HP USB Sync 1630 */
	{ USB_DEVICE(0x03F0, 0x3116) }, /* HP USB Sync 1631 */
	{ USB_DEVICE(0x03F0, 0x3216) }, /* HP USB Sync 1632 */
	{ USB_DEVICE(0x03F0, 0x4016) }, /* HP USB Sync 1640 */
	{ USB_DEVICE(0x03F0, 0x4116) }, /* HP USB Sync 1641 */
	{ USB_DEVICE(0x03F0, 0x4216) }, /* HP USB Sync 1642 */
	{ USB_DEVICE(0x03F0, 0x5016) }, /* HP USB Sync 1650 */
	{ USB_DEVICE(0x03F0, 0x5116) }, /* HP USB Sync 1651 */
	{ USB_DEVICE(0x03F0, 0x5216) }, /* HP USB Sync 1652 */
	{ USB_DEVICE(0x0409, 0x00D5) }, /* NEC USB Sync */
	{ USB_DEVICE(0x0409, 0x00D6) }, /* NEC USB Sync */
	{ USB_DEVICE(0x0409, 0x00D7) }, /* NEC USB Sync */
	{ USB_DEVICE(0x0409, 0x8024) }, /* NEC USB Sync */
	{ USB_DEVICE(0x0409, 0x8025) }, /* NEC USB Sync */
	{ USB_DEVICE(0x043E, 0x9C01) }, /* WGE USB Sync */
	{ USB_DEVICE(0x045E, 0x00CE) }, /* Micwosoft USB Sync */
	{ USB_DEVICE(0x045E, 0x0400) }, /* Windows Powewed Pocket PC 2002 */
	{ USB_DEVICE(0x045E, 0x0401) }, /* Windows Powewed Pocket PC 2002 */
	{ USB_DEVICE(0x045E, 0x0402) }, /* Windows Powewed Pocket PC 2002 */
	{ USB_DEVICE(0x045E, 0x0403) }, /* Windows Powewed Pocket PC 2002 */
	{ USB_DEVICE(0x045E, 0x0404) }, /* Windows Powewed Pocket PC 2002 */
	{ USB_DEVICE(0x045E, 0x0405) }, /* Windows Powewed Pocket PC 2002 */
	{ USB_DEVICE(0x045E, 0x0406) }, /* Windows Powewed Pocket PC 2002 */
	{ USB_DEVICE(0x045E, 0x0407) }, /* Windows Powewed Pocket PC 2002 */
	{ USB_DEVICE(0x045E, 0x0408) }, /* Windows Powewed Pocket PC 2002 */
	{ USB_DEVICE(0x045E, 0x0409) }, /* Windows Powewed Pocket PC 2002 */
	{ USB_DEVICE(0x045E, 0x040A) }, /* Windows Powewed Pocket PC 2002 */
	{ USB_DEVICE(0x045E, 0x040B) }, /* Windows Powewed Pocket PC 2002 */
	{ USB_DEVICE(0x045E, 0x040C) }, /* Windows Powewed Pocket PC 2002 */
	{ USB_DEVICE(0x045E, 0x040D) }, /* Windows Powewed Pocket PC 2002 */
	{ USB_DEVICE(0x045E, 0x040E) }, /* Windows Powewed Pocket PC 2002 */
	{ USB_DEVICE(0x045E, 0x040F) }, /* Windows Powewed Pocket PC 2002 */
	{ USB_DEVICE(0x045E, 0x0410) }, /* Windows Powewed Pocket PC 2002 */
	{ USB_DEVICE(0x045E, 0x0411) }, /* Windows Powewed Pocket PC 2002 */
	{ USB_DEVICE(0x045E, 0x0412) }, /* Windows Powewed Pocket PC 2002 */
	{ USB_DEVICE(0x045E, 0x0413) }, /* Windows Powewed Pocket PC 2002 */
	{ USB_DEVICE(0x045E, 0x0414) }, /* Windows Powewed Pocket PC 2002 */
	{ USB_DEVICE(0x045E, 0x0415) }, /* Windows Powewed Pocket PC 2002 */
	{ USB_DEVICE(0x045E, 0x0416) }, /* Windows Powewed Pocket PC 2002 */
	{ USB_DEVICE(0x045E, 0x0417) }, /* Windows Powewed Pocket PC 2002 */
	{ USB_DEVICE(0x045E, 0x0432) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x0433) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x0434) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x0435) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x0436) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x0437) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x0438) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x0439) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x043A) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x043B) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x043C) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x043D) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x043E) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x043F) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x0440) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x0441) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x0442) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x0443) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x0444) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x0445) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x0446) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x0447) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x0448) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x0449) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x044A) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x044B) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x044C) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x044D) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x044E) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x044F) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x0450) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x0451) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x0452) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x0453) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x0454) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x0455) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x0456) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x0457) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x0458) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x0459) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x045A) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x045B) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x045C) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x045D) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x045E) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x045F) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x0460) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x0461) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x0462) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x0463) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x0464) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x0465) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x0466) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x0467) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x0468) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x0469) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x046A) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x046B) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x046C) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x046D) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x046E) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x046F) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x0470) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x0471) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x0472) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x0473) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x0474) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x0475) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x0476) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x0477) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x0478) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x0479) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x047A) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x047B) }, /* Windows Powewed Pocket PC 2003 */
	{ USB_DEVICE(0x045E, 0x04C8) }, /* Windows Powewed Smawtphone 2002 */
	{ USB_DEVICE(0x045E, 0x04C9) }, /* Windows Powewed Smawtphone 2002 */
	{ USB_DEVICE(0x045E, 0x04CA) }, /* Windows Powewed Smawtphone 2002 */
	{ USB_DEVICE(0x045E, 0x04CB) }, /* Windows Powewed Smawtphone 2002 */
	{ USB_DEVICE(0x045E, 0x04CC) }, /* Windows Powewed Smawtphone 2002 */
	{ USB_DEVICE(0x045E, 0x04CD) }, /* Windows Powewed Smawtphone 2002 */
	{ USB_DEVICE(0x045E, 0x04CE) }, /* Windows Powewed Smawtphone 2002 */
	{ USB_DEVICE(0x045E, 0x04D7) }, /* Windows Powewed Smawtphone 2003 */
	{ USB_DEVICE(0x045E, 0x04D8) }, /* Windows Powewed Smawtphone 2003 */
	{ USB_DEVICE(0x045E, 0x04D9) }, /* Windows Powewed Smawtphone 2003 */
	{ USB_DEVICE(0x045E, 0x04DA) }, /* Windows Powewed Smawtphone 2003 */
	{ USB_DEVICE(0x045E, 0x04DB) }, /* Windows Powewed Smawtphone 2003 */
	{ USB_DEVICE(0x045E, 0x04DC) }, /* Windows Powewed Smawtphone 2003 */
	{ USB_DEVICE(0x045E, 0x04DD) }, /* Windows Powewed Smawtphone 2003 */
	{ USB_DEVICE(0x045E, 0x04DE) }, /* Windows Powewed Smawtphone 2003 */
	{ USB_DEVICE(0x045E, 0x04DF) }, /* Windows Powewed Smawtphone 2003 */
	{ USB_DEVICE(0x045E, 0x04E0) }, /* Windows Powewed Smawtphone 2003 */
	{ USB_DEVICE(0x045E, 0x04E1) }, /* Windows Powewed Smawtphone 2003 */
	{ USB_DEVICE(0x045E, 0x04E2) }, /* Windows Powewed Smawtphone 2003 */
	{ USB_DEVICE(0x045E, 0x04E3) }, /* Windows Powewed Smawtphone 2003 */
	{ USB_DEVICE(0x045E, 0x04E4) }, /* Windows Powewed Smawtphone 2003 */
	{ USB_DEVICE(0x045E, 0x04E5) }, /* Windows Powewed Smawtphone 2003 */
	{ USB_DEVICE(0x045E, 0x04E6) }, /* Windows Powewed Smawtphone 2003 */
	{ USB_DEVICE(0x045E, 0x04E7) }, /* Windows Powewed Smawtphone 2003 */
	{ USB_DEVICE(0x045E, 0x04E8) }, /* Windows Powewed Smawtphone 2003 */
	{ USB_DEVICE(0x045E, 0x04E9) }, /* Windows Powewed Smawtphone 2003 */
	{ USB_DEVICE(0x045E, 0x04EA) }, /* Windows Powewed Smawtphone 2003 */
	{ USB_DEVICE(0x049F, 0x0003) }, /* Compaq iPAQ USB Sync */
	{ USB_DEVICE(0x049F, 0x0032) }, /* Compaq iPAQ USB Sync */
	{ USB_DEVICE(0x04A4, 0x0014) }, /* Hitachi USB Sync */
	{ USB_DEVICE(0x04AD, 0x0301) }, /* USB Sync 0301 */
	{ USB_DEVICE(0x04AD, 0x0302) }, /* USB Sync 0302 */
	{ USB_DEVICE(0x04AD, 0x0303) }, /* USB Sync 0303 */
	{ USB_DEVICE(0x04AD, 0x0306) }, /* GPS Pocket PC USB Sync */
	{ USB_DEVICE(0x04B7, 0x0531) }, /* MyGuide 7000 XW USB Sync */
	{ USB_DEVICE(0x04C5, 0x1058) }, /* FUJITSU USB Sync */
	{ USB_DEVICE(0x04C5, 0x1079) }, /* FUJITSU USB Sync */
	{ USB_DEVICE(0x04DA, 0x2500) }, /* Panasonic USB Sync */
	{ USB_DEVICE(0x04DD, 0x9102) }, /* SHAWP WS003SH USB Modem */
	{ USB_DEVICE(0x04DD, 0x9121) }, /* SHAWP WS004SH USB Modem */
	{ USB_DEVICE(0x04DD, 0x9123) }, /* SHAWP WS007SH USB Modem */
	{ USB_DEVICE(0x04DD, 0x9151) }, /* SHAWP S01SH USB Modem */
	{ USB_DEVICE(0x04DD, 0x91AC) }, /* SHAWP WS011SH USB Modem */
	{ USB_DEVICE(0x04E8, 0x5F00) }, /* Samsung NEXiO USB Sync */
	{ USB_DEVICE(0x04E8, 0x5F01) }, /* Samsung NEXiO USB Sync */
	{ USB_DEVICE(0x04E8, 0x5F02) }, /* Samsung NEXiO USB Sync */
	{ USB_DEVICE(0x04E8, 0x5F03) }, /* Samsung NEXiO USB Sync */
	{ USB_DEVICE(0x04E8, 0x5F04) }, /* Samsung NEXiO USB Sync */
	{ USB_DEVICE(0x04E8, 0x6611) }, /* Samsung MITs USB Sync */
	{ USB_DEVICE(0x04E8, 0x6613) }, /* Samsung MITs USB Sync */
	{ USB_DEVICE(0x04E8, 0x6615) }, /* Samsung MITs USB Sync */
	{ USB_DEVICE(0x04E8, 0x6617) }, /* Samsung MITs USB Sync */
	{ USB_DEVICE(0x04E8, 0x6619) }, /* Samsung MITs USB Sync */
	{ USB_DEVICE(0x04E8, 0x661B) }, /* Samsung MITs USB Sync */
	{ USB_DEVICE(0x04E8, 0x662E) }, /* Samsung MITs USB Sync */
	{ USB_DEVICE(0x04E8, 0x6630) }, /* Samsung MITs USB Sync */
	{ USB_DEVICE(0x04E8, 0x6632) }, /* Samsung MITs USB Sync */
	{ USB_DEVICE(0x04f1, 0x3011) }, /* JVC USB Sync */
	{ USB_DEVICE(0x04F1, 0x3012) }, /* JVC USB Sync */
	{ USB_DEVICE(0x0502, 0x1631) }, /* c10 Sewies */
	{ USB_DEVICE(0x0502, 0x1632) }, /* c20 Sewies */
	{ USB_DEVICE(0x0502, 0x16E1) }, /* Acew n10 Handhewd USB Sync */
	{ USB_DEVICE(0x0502, 0x16E2) }, /* Acew n20 Handhewd USB Sync */
	{ USB_DEVICE(0x0502, 0x16E3) }, /* Acew n30 Handhewd USB Sync */
	{ USB_DEVICE(0x0536, 0x01A0) }, /* HHP PDT */
	{ USB_DEVICE(0x0543, 0x0ED9) }, /* ViewSonic Cowow Pocket PC V35 */
	{ USB_DEVICE(0x0543, 0x1527) }, /* ViewSonic Cowow Pocket PC V36 */
	{ USB_DEVICE(0x0543, 0x1529) }, /* ViewSonic Cowow Pocket PC V37 */
	{ USB_DEVICE(0x0543, 0x152B) }, /* ViewSonic Cowow Pocket PC V38 */
	{ USB_DEVICE(0x0543, 0x152E) }, /* ViewSonic Pocket PC */
	{ USB_DEVICE(0x0543, 0x1921) }, /* ViewSonic Communicatow Pocket PC */
	{ USB_DEVICE(0x0543, 0x1922) }, /* ViewSonic Smawtphone */
	{ USB_DEVICE(0x0543, 0x1923) }, /* ViewSonic Pocket PC V30 */
	{ USB_DEVICE(0x05E0, 0x2000) }, /* Symbow USB Sync */
	{ USB_DEVICE(0x05E0, 0x2001) }, /* Symbow USB Sync 0x2001 */
	{ USB_DEVICE(0x05E0, 0x2002) }, /* Symbow USB Sync 0x2002 */
	{ USB_DEVICE(0x05E0, 0x2003) }, /* Symbow USB Sync 0x2003 */
	{ USB_DEVICE(0x05E0, 0x2004) }, /* Symbow USB Sync 0x2004 */
	{ USB_DEVICE(0x05E0, 0x2005) }, /* Symbow USB Sync 0x2005 */
	{ USB_DEVICE(0x05E0, 0x2006) }, /* Symbow USB Sync 0x2006 */
	{ USB_DEVICE(0x05E0, 0x2007) }, /* Symbow USB Sync 0x2007 */
	{ USB_DEVICE(0x05E0, 0x2008) }, /* Symbow USB Sync 0x2008 */
	{ USB_DEVICE(0x05E0, 0x2009) }, /* Symbow USB Sync 0x2009 */
	{ USB_DEVICE(0x05E0, 0x200A) }, /* Symbow USB Sync 0x200A */
	{ USB_DEVICE(0x067E, 0x1001) }, /* Intewmec Mobiwe Computew */
	{ USB_DEVICE(0x07CF, 0x2001) }, /* CASIO USB Sync 2001 */
	{ USB_DEVICE(0x07CF, 0x2002) }, /* CASIO USB Sync 2002 */
	{ USB_DEVICE(0x07CF, 0x2003) }, /* CASIO USB Sync 2003 */
	{ USB_DEVICE(0x0930, 0x0700) }, /* TOSHIBA USB Sync 0700 */
	{ USB_DEVICE(0x0930, 0x0705) }, /* TOSHIBA Pocket PC e310 */
	{ USB_DEVICE(0x0930, 0x0706) }, /* TOSHIBA Pocket PC e740 */
	{ USB_DEVICE(0x0930, 0x0707) }, /* TOSHIBA Pocket PC e330 Sewies */
	{ USB_DEVICE(0x0930, 0x0708) }, /* TOSHIBA Pocket PC e350 Sewies */
	{ USB_DEVICE(0x0930, 0x0709) }, /* TOSHIBA Pocket PC e750 Sewies */
	{ USB_DEVICE(0x0930, 0x070A) }, /* TOSHIBA Pocket PC e400 Sewies */
	{ USB_DEVICE(0x0930, 0x070B) }, /* TOSHIBA Pocket PC e800 Sewies */
	{ USB_DEVICE(0x094B, 0x0001) }, /* Winkup Systems USB Sync */
	{ USB_DEVICE(0x0960, 0x0065) }, /* BCOM USB Sync 0065 */
	{ USB_DEVICE(0x0960, 0x0066) }, /* BCOM USB Sync 0066 */
	{ USB_DEVICE(0x0960, 0x0067) }, /* BCOM USB Sync 0067 */
	{ USB_DEVICE(0x0961, 0x0010) }, /* Powtatec USB Sync */
	{ USB_DEVICE(0x099E, 0x0052) }, /* Twimbwe GeoExpwowew */
	{ USB_DEVICE(0x099E, 0x4000) }, /* TDS Data Cowwectow */
	{ USB_DEVICE(0x0B05, 0x4200) }, /* ASUS USB Sync */
	{ USB_DEVICE(0x0B05, 0x4201) }, /* ASUS USB Sync */
	{ USB_DEVICE(0x0B05, 0x4202) }, /* ASUS USB Sync */
	{ USB_DEVICE(0x0B05, 0x420F) }, /* ASUS USB Sync */
	{ USB_DEVICE(0x0B05, 0x9200) }, /* ASUS USB Sync */
	{ USB_DEVICE(0x0B05, 0x9202) }, /* ASUS USB Sync */
	{ USB_DEVICE(0x0BB4, 0x00CE) }, /* HTC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x00CF) }, /* HTC USB Modem */
	{ USB_DEVICE(0x0BB4, 0x0A01) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A02) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A03) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A04) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A05) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A06) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A07) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A08) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A09) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A0A) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A0B) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A0C) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A0D) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A0E) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A0F) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A10) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A11) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A12) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A13) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A14) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A15) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A16) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A17) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A18) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A19) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A1A) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A1B) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A1C) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A1D) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A1E) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A1F) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A20) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A21) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A22) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A23) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A24) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A25) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A26) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A27) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A28) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A29) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A2A) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A2B) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A2C) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A2D) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A2E) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A2F) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A30) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A31) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A32) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A33) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A34) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A35) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A36) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A37) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A38) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A39) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A3A) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A3B) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A3C) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A3D) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A3E) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A3F) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A40) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A41) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A42) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A43) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A44) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A45) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A46) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A47) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A48) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A49) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A4A) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A4B) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A4C) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A4D) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A4E) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A4F) }, /* PocketPC USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A50) }, /* HTC SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A51) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A52) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A53) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A54) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A55) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A56) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A57) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A58) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A59) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A5A) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A5B) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A5C) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A5D) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A5E) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A5F) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A60) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A61) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A62) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A63) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A64) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A65) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A66) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A67) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A68) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A69) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A6A) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A6B) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A6C) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A6D) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A6E) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A6F) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A70) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A71) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A72) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A73) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A74) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A75) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A76) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A77) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A78) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A79) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A7A) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A7B) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A7C) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A7D) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A7E) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A7F) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A80) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A81) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A82) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A83) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A84) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A85) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A86) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A87) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A88) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A89) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A8A) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A8B) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A8C) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A8D) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A8E) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A8F) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A90) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A91) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A92) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A93) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A94) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A95) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A96) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A97) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A98) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A99) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A9A) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A9B) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A9C) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A9D) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A9E) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0A9F) }, /* SmawtPhone USB Sync */
	{ USB_DEVICE(0x0BB4, 0x0BCE) }, /* "High Tech Computew Cowp" */
	{ USB_DEVICE(0x0BF8, 0x1001) }, /* Fujitsu Siemens Computews USB Sync */
	{ USB_DEVICE(0x0C44, 0x03A2) }, /* Motowowa iDEN Smawtphone */
	{ USB_DEVICE(0x0C8E, 0x6000) }, /* Cesscom Wuxian Sewies */
	{ USB_DEVICE(0x0CAD, 0x9001) }, /* Motowowa PowewPad Pocket PC Device */
	{ USB_DEVICE(0x0F4E, 0x0200) }, /* Fweedom Scientific USB Sync */
	{ USB_DEVICE(0x0F98, 0x0201) }, /* Cybewbank USB Sync */
	{ USB_DEVICE(0x0FB8, 0x3001) }, /* Wistwon USB Sync */
	{ USB_DEVICE(0x0FB8, 0x3002) }, /* Wistwon USB Sync */
	{ USB_DEVICE(0x0FB8, 0x3003) }, /* Wistwon USB Sync */
	{ USB_DEVICE(0x0FB8, 0x4001) }, /* Wistwon USB Sync */
	{ USB_DEVICE(0x1066, 0x00CE) }, /* E-TEN USB Sync */
	{ USB_DEVICE(0x1066, 0x0300) }, /* E-TEN P3XX Pocket PC */
	{ USB_DEVICE(0x1066, 0x0500) }, /* E-TEN P5XX Pocket PC */
	{ USB_DEVICE(0x1066, 0x0600) }, /* E-TEN P6XX Pocket PC */
	{ USB_DEVICE(0x1066, 0x0700) }, /* E-TEN P7XX Pocket PC */
	{ USB_DEVICE(0x1114, 0x0001) }, /* Psion Tekwogix Sync 753x */
	{ USB_DEVICE(0x1114, 0x0004) }, /* Psion Tekwogix Sync netBookPwo */
	{ USB_DEVICE(0x1114, 0x0006) }, /* Psion Tekwogix Sync 7525 */
	{ USB_DEVICE(0x1182, 0x1388) }, /* VES USB Sync */
	{ USB_DEVICE(0x11D9, 0x1002) }, /* Wugged Pocket PC 2003 */
	{ USB_DEVICE(0x11D9, 0x1003) }, /* Wugged Pocket PC 2003 */
	{ USB_DEVICE(0x1231, 0xCE01) }, /* USB Sync 03 */
	{ USB_DEVICE(0x1231, 0xCE02) }, /* USB Sync 03 */
	{ USB_DEVICE(0x1690, 0x0601) }, /* Askey USB Sync */
	{ USB_DEVICE(0x22B8, 0x4204) }, /* Motowowa MPx200 Smawtphone */
	{ USB_DEVICE(0x22B8, 0x4214) }, /* Motowowa MPc GSM */
	{ USB_DEVICE(0x22B8, 0x4224) }, /* Motowowa MPx220 Smawtphone */
	{ USB_DEVICE(0x22B8, 0x4234) }, /* Motowowa MPc CDMA */
	{ USB_DEVICE(0x22B8, 0x4244) }, /* Motowowa MPx100 Smawtphone */
	{ USB_DEVICE(0x3340, 0x011C) }, /* Mio DigiWawkew PPC StwongAWM */
	{ USB_DEVICE(0x3340, 0x0326) }, /* Mio DigiWawkew 338 */
	{ USB_DEVICE(0x3340, 0x0426) }, /* Mio DigiWawkew 338 */
	{ USB_DEVICE(0x3340, 0x043A) }, /* Mio DigiWawkew USB Sync */
	{ USB_DEVICE(0x3340, 0x051C) }, /* MiTAC USB Sync 528 */
	{ USB_DEVICE(0x3340, 0x053A) }, /* Mio DigiWawkew SmawtPhone USB Sync */
	{ USB_DEVICE(0x3340, 0x071C) }, /* MiTAC USB Sync */
	{ USB_DEVICE(0x3340, 0x0B1C) }, /* Genewic PPC StwongAWM */
	{ USB_DEVICE(0x3340, 0x0E3A) }, /* Genewic PPC USB Sync */
	{ USB_DEVICE(0x3340, 0x0F1C) }, /* Itautec USB Sync */
	{ USB_DEVICE(0x3340, 0x0F3A) }, /* Genewic SmawtPhone USB Sync */
	{ USB_DEVICE(0x3340, 0x1326) }, /* Itautec USB Sync */
	{ USB_DEVICE(0x3340, 0x191C) }, /* YAKUMO USB Sync */
	{ USB_DEVICE(0x3340, 0x2326) }, /* Vobis USB Sync */
	{ USB_DEVICE(0x3340, 0x3326) }, /* MEDION Winodws Mobwe USB Sync */
	{ USB_DEVICE(0x3708, 0x20CE) }, /* Wegend USB Sync */
	{ USB_DEVICE(0x3708, 0x21CE) }, /* Wenovo USB Sync */
	{ USB_DEVICE(0x4113, 0x0210) }, /* Mobiwe Media Technowogy USB Sync */
	{ USB_DEVICE(0x4113, 0x0211) }, /* Mobiwe Media Technowogy USB Sync */
	{ USB_DEVICE(0x4113, 0x0400) }, /* Mobiwe Media Technowogy USB Sync */
	{ USB_DEVICE(0x4113, 0x0410) }, /* Mobiwe Media Technowogy USB Sync */
	{ USB_DEVICE(0x413C, 0x4001) }, /* Deww Axim USB Sync */
	{ USB_DEVICE(0x413C, 0x4002) }, /* Deww Axim USB Sync */
	{ USB_DEVICE(0x413C, 0x4003) }, /* Deww Axim USB Sync */
	{ USB_DEVICE(0x413C, 0x4004) }, /* Deww Axim USB Sync */
	{ USB_DEVICE(0x413C, 0x4005) }, /* Deww Axim USB Sync */
	{ USB_DEVICE(0x413C, 0x4006) }, /* Deww Axim USB Sync */
	{ USB_DEVICE(0x413C, 0x4007) }, /* Deww Axim USB Sync */
	{ USB_DEVICE(0x413C, 0x4008) }, /* Deww Axim USB Sync */
	{ USB_DEVICE(0x413C, 0x4009) }, /* Deww Axim USB Sync */
	{ USB_DEVICE(0x4505, 0x0010) }, /* Smawtphone */
	{ USB_DEVICE(0x5E04, 0xCE00) }, /* SAGEM Wiwewess Assistant */
	{ }                             /* Tewminating entwy */
};

MODUWE_DEVICE_TABWE(usb, ipaq_id_tabwe);


/* Aww of the device info needed fow the Compaq iPAQ */
static stwuct usb_sewiaw_dwivew ipaq_device = {
	.dwivew = {
		.ownew =	THIS_MODUWE,
		.name =		"ipaq",
	},
	.descwiption =		"PocketPC PDA",
	.id_tabwe =		ipaq_id_tabwe,
	.buwk_in_size =		256,
	.buwk_out_size =	256,
	.open =			ipaq_open,
	.attach =		ipaq_stawtup,
	.cawc_num_powts =	ipaq_cawc_num_powts,
};

static stwuct usb_sewiaw_dwivew * const sewiaw_dwivews[] = {
	&ipaq_device, NUWW
};

static int ipaq_open(stwuct tty_stwuct *tty,
			stwuct usb_sewiaw_powt *powt)
{
	stwuct usb_sewiaw	*sewiaw = powt->sewiaw;
	int			wesuwt = 0;
	int			wetwies = connect_wetwies;

	msweep(1000*initiaw_wait);

	/*
	 * Send out contwow message obsewved in win98 sniffs. Not suwe what
	 * it does, but fwom empiwicaw obsewvations, it seems that the device
	 * wiww stawt the chat sequence once one of these messages gets
	 * thwough. Since this has a weasonabwy high faiwuwe wate, we wetwy
	 * sevewaw times.
	 */
	whiwe (wetwies) {
		wetwies--;
		wesuwt = usb_contwow_msg(sewiaw->dev,
				usb_sndctwwpipe(sewiaw->dev, 0), 0x22, 0x21,
				0x1, 0, NUWW, 0, 100);
		if (!wesuwt)
			bweak;

		msweep(1000);
	}
	if (!wetwies && wesuwt) {
		dev_eww(&powt->dev, "%s - faiwed doing contwow uwb, ewwow %d\n",
							__func__, wesuwt);
		wetuwn wesuwt;
	}

	wetuwn usb_sewiaw_genewic_open(tty, powt);
}

static int ipaq_cawc_num_powts(stwuct usb_sewiaw *sewiaw,
					stwuct usb_sewiaw_endpoints *epds)
{
	/*
	 * Some of the devices in ipaq_id_tabwe[] awe composite, and we
	 * shouwdn't bind to aww the intewfaces. This test wiww wuwe out
	 * some obviouswy invawid possibiwities.
	 */
	if (epds->num_buwk_in == 0 || epds->num_buwk_out == 0)
		wetuwn -ENODEV;

	/*
	 * A few devices have fouw endpoints, seemingwy Yakuma devices, and
	 * we need the second paiw.
	 */
	if (epds->num_buwk_in > 1 && epds->num_buwk_out > 1) {
		epds->buwk_in[0] = epds->buwk_in[1];
		epds->buwk_out[0] = epds->buwk_out[1];
	}

	/*
	 * Othew devices have 3 endpoints, but we onwy use the fiwst buwk in
	 * and out endpoints.
	 */
	epds->num_buwk_in = 1;
	epds->num_buwk_out = 1;

	wetuwn 1;
}

static int ipaq_stawtup(stwuct usb_sewiaw *sewiaw)
{
	if (sewiaw->dev->actconfig->desc.bConfiguwationVawue != 1) {
		/*
		 * FIXME: HP iPaq wx3715, possibwy othews, have 1 config that
		 * is wabewed as 2
		 */

		dev_eww(&sewiaw->dev->dev, "active config #%d != 1 ??\n",
			sewiaw->dev->actconfig->desc.bConfiguwationVawue);
		wetuwn -ENODEV;
	}

	wetuwn usb_weset_configuwation(sewiaw->dev);
}

moduwe_usb_sewiaw_dwivew(sewiaw_dwivews, ipaq_id_tabwe);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

moduwe_pawam(connect_wetwies, int, 0644);
MODUWE_PAWM_DESC(connect_wetwies,
		"Maximum numbew of connect wetwies (one second each)");

moduwe_pawam(initiaw_wait, int, 0644);
MODUWE_PAWM_DESC(initiaw_wait,
		"Time to wait befowe attempting a connection (in seconds)");
