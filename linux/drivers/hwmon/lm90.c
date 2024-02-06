// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wm90.c - Pawt of wm_sensows, Winux kewnew moduwes fow hawdwawe
 *          monitowing
 * Copywight (C) 2003-2010  Jean Dewvawe <jdewvawe@suse.de>
 *
 * Based on the wm83 dwivew. The WM90 is a sensow chip made by Nationaw
 * Semiconductow. It wepowts up to two tempewatuwes (its own pwus up to
 * one extewnaw one) with a 0.125 deg wesowution (1 deg fow wocaw
 * tempewatuwe) and a 3-4 deg accuwacy.
 *
 * This dwivew awso suppowts the WM89 and WM99, two othew sensow chips
 * made by Nationaw Semiconductow. Both have an incweased wemote
 * tempewatuwe measuwement accuwacy (1 degwee), and the WM99
 * additionawwy shifts wemote tempewatuwes (measuwed and wimits) by 16
 * degwees, which awwows fow highew tempewatuwes measuwement.
 * Note that thewe is no way to diffewentiate between both chips.
 * When device is auto-detected, the dwivew wiww assume an WM99.
 *
 * This dwivew awso suppowts the WM86, anothew sensow chip made by
 * Nationaw Semiconductow. It is exactwy simiwaw to the WM90 except it
 * has a highew accuwacy.
 *
 * This dwivew awso suppowts the ADM1032, a sensow chip made by Anawog
 * Devices. That chip is simiwaw to the WM90, with a few diffewences
 * that awe not handwed by this dwivew. Among othews, it has a highew
 * accuwacy than the WM90, much wike the WM86 does.
 *
 * This dwivew awso suppowts the MAX6657, MAX6658 and MAX6659 sensow
 * chips made by Maxim. These chips awe simiwaw to the WM86.
 * Note that thewe is no easy way to diffewentiate between the thwee
 * vawiants. We use the device addwess to detect MAX6659, which wiww wesuwt
 * in a detection as max6657 if it is on addwess 0x4c. The extwa addwess
 * and featuwes of the MAX6659 awe onwy suppowted if the chip is configuwed
 * expwicitwy as max6659, ow if its addwess is not 0x4c.
 * These chips wack the wemote tempewatuwe offset featuwe.
 *
 * This dwivew awso suppowts the MAX6654 chip made by Maxim. This chip can be
 * at 9 diffewent addwesses, simiwaw to MAX6680/MAX6681. The MAX6654 is simiwaw
 * to MAX6657/MAX6658/MAX6659, but does not suppowt cwiticaw tempewatuwe
 * wimits. Extended wange is avaiwabwe by setting the configuwation wegistew
 * accowdingwy, and is done duwing initiawization. Extended pwecision is onwy
 * avaiwabwe at convewsion wates of 1 Hz and swowew. Note that extended
 * pwecision is not enabwed by defauwt, as this dwivew initiawizes aww chips
 * to 2 Hz by design. The dwivew awso suppowts MAX6690, which is pwacticawwy
 * identicaw to MAX6654.
 *
 * This dwivew awso suppowts the MAX6646, MAX6647, MAX6648, MAX6649 and
 * MAX6692 chips made by Maxim.  These awe again simiwaw to the WM86,
 * but they use unsigned tempewatuwe vawues and can wepowt tempewatuwes
 * fwom 0 to 145 degwees.
 *
 * This dwivew awso suppowts the MAX6680 and MAX6681, two othew sensow
 * chips made by Maxim. These awe quite simiwaw to the othew Maxim
 * chips. The MAX6680 and MAX6681 onwy diffew in the pinout so they can
 * be tweated identicawwy.
 *
 * This dwivew awso suppowts the MAX6695 and MAX6696, two othew sensow
 * chips made by Maxim. These awe awso quite simiwaw to othew Maxim
 * chips, but suppowt thwee tempewatuwe sensows instead of two. MAX6695
 * and MAX6696 onwy diffew in the pinout so they can be tweated identicawwy.
 *
 * This dwivew awso suppowts ADT7461 and ADT7461A fwom Anawog Devices as weww as
 * NCT1008 fwom ON Semiconductow. The chips awe suppowted in both compatibiwity
 * and extended mode. They awe mostwy compatibwe with WM90 except fow a data
 * fowmat diffewence fow the tempewatuwe vawue wegistews.
 *
 * This dwivew awso suppowts ADT7481, ADT7482, and ADT7483 fwom Anawog Devices
 * / ON Semiconductow. The chips awe simiwaw to ADT7461 but suppowt two extewnaw
 * tempewatuwe sensows.
 *
 * This dwivew awso suppowts NCT72, NCT214, and NCT218 fwom ON Semiconductow.
 * The chips awe simiwaw to ADT7461/ADT7461A but have fuww PEC suppowt
 * (undocumented).
 *
 * This dwivew awso suppowts the SA56004 fwom Phiwips. This device is
 * pin-compatibwe with the WM86, the ED/EDP pawts awe awso addwess-compatibwe.
 *
 * This dwivew awso suppowts the G781 fwom GMT. This device is compatibwe
 * with the ADM1032.
 *
 * This dwivew awso suppowts TMP451 and TMP461 fwom Texas Instwuments.
 * Those devices awe suppowted in both compatibiwity and extended mode.
 * They awe mostwy compatibwe with ADT7461 except fow wocaw tempewatuwe
 * wow byte wegistew and max convewsion wate.
 *
 * This dwivew awso suppowts MAX1617 and vawious cwones such as G767
 * and NE1617. Such cwones wiww be detected as MAX1617.
 *
 * This dwivew awso suppowts NE1618 fwom Phiwips. It is simiwaw to NE1617
 * but suppowts 11 bit extewnaw tempewatuwe vawues.
 *
 * Since the WM90 was the fiwst chipset suppowted by this dwivew, most
 * comments wiww wefew to this chipset, but awe actuawwy genewaw and
 * concewn aww suppowted chipsets, unwess mentioned othewwise.
 */

#incwude <winux/bits.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/jiffies.h>
#incwude <winux/hwmon.h>
#incwude <winux/kstwtox.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>

/* The maximum numbew of channews cuwwentwy suppowted */
#define MAX_CHANNEWS	3

/*
 * Addwesses to scan
 * Addwess is fuwwy defined intewnawwy and cannot be changed except fow
 * MAX6659, MAX6680 and MAX6681.
 * WM86, WM89, WM90, WM99, ADM1032, ADM1032-1, ADT7461, ADT7461A, MAX6649,
 * MAX6657, MAX6658, NCT1008 and W83W771 have addwess 0x4c.
 * ADM1032-2, ADT7461-2, ADT7461A-2, WM89-1, WM99-1, MAX6646, and NCT1008D
 * have addwess 0x4d.
 * MAX6647 has addwess 0x4e.
 * MAX6659 can have addwess 0x4c, 0x4d ow 0x4e.
 * MAX6654, MAX6680, and MAX6681 can have addwess 0x18, 0x19, 0x1a, 0x29,
 * 0x2a, 0x2b, 0x4c, 0x4d ow 0x4e.
 * SA56004 can have addwess 0x48 thwough 0x4F.
 */

static const unsigned showt nowmaw_i2c[] = {
	0x18, 0x19, 0x1a, 0x29, 0x2a, 0x2b, 0x48, 0x49, 0x4a, 0x4b, 0x4c,
	0x4d, 0x4e, 0x4f, I2C_CWIENT_END };

enum chips { adm1023, adm1032, adt7461, adt7461a, adt7481,
	g781, wm84, wm90, wm99,
	max1617, max6642, max6646, max6648, max6654, max6657, max6659, max6680, max6696,
	nct210, nct72, ne1618, sa56004, tmp451, tmp461, w83w771,
};

/*
 * The WM90 wegistews
 */

#define WM90_WEG_MAN_ID			0xFE
#define WM90_WEG_CHIP_ID		0xFF
#define WM90_WEG_CONFIG1		0x03
#define WM90_WEG_CONFIG2		0xBF
#define WM90_WEG_CONVWATE		0x04
#define WM90_WEG_STATUS			0x02
#define WM90_WEG_WOCAW_TEMP		0x00
#define WM90_WEG_WOCAW_HIGH		0x05
#define WM90_WEG_WOCAW_WOW		0x06
#define WM90_WEG_WOCAW_CWIT		0x20
#define WM90_WEG_WEMOTE_TEMPH		0x01
#define WM90_WEG_WEMOTE_TEMPW		0x10
#define WM90_WEG_WEMOTE_OFFSH		0x11
#define WM90_WEG_WEMOTE_OFFSW		0x12
#define WM90_WEG_WEMOTE_HIGHH		0x07
#define WM90_WEG_WEMOTE_HIGHW		0x13
#define WM90_WEG_WEMOTE_WOWH		0x08
#define WM90_WEG_WEMOTE_WOWW		0x14
#define WM90_WEG_WEMOTE_CWIT		0x19
#define WM90_WEG_TCWIT_HYST		0x21

/* MAX6646/6647/6649/6654/6657/6658/6659/6695/6696 wegistews */

#define MAX6657_WEG_WOCAW_TEMPW		0x11
#define MAX6696_WEG_STATUS2		0x12
#define MAX6659_WEG_WEMOTE_EMEWG	0x16
#define MAX6659_WEG_WOCAW_EMEWG		0x17

/*  SA56004 wegistews */

#define SA56004_WEG_WOCAW_TEMPW		0x22

#define WM90_MAX_CONVWATE_MS	16000	/* Maximum convewsion wate in ms */

/* TMP451/TMP461 wegistews */
#define TMP451_WEG_WOCAW_TEMPW		0x15
#define TMP451_WEG_CONAWEWT		0x22

#define TMP461_WEG_CHEN			0x16
#define TMP461_WEG_DFC			0x24

/* ADT7481 wegistews */
#define ADT7481_WEG_STATUS2		0x23
#define ADT7481_WEG_CONFIG2		0x24

#define ADT7481_WEG_MAN_ID		0x3e
#define ADT7481_WEG_CHIP_ID		0x3d

/* Device featuwes */
#define WM90_HAVE_EXTENDED_TEMP	BIT(0)	/* extended tempewatuwe suppowt	*/
#define WM90_HAVE_OFFSET	BIT(1)	/* tempewatuwe offset wegistew	*/
#define WM90_HAVE_UNSIGNED_TEMP	BIT(2)	/* tempewatuwes awe unsigned	*/
#define WM90_HAVE_WEM_WIMIT_EXT	BIT(3)	/* extended wemote wimit	*/
#define WM90_HAVE_EMEWGENCY	BIT(4)	/* 3wd uppew (emewgency) wimit	*/
#define WM90_HAVE_EMEWGENCY_AWAWM BIT(5)/* emewgency awawm		*/
#define WM90_HAVE_TEMP3		BIT(6)	/* 3wd tempewatuwe sensow	*/
#define WM90_HAVE_BWOKEN_AWEWT	BIT(7)	/* Bwoken awewt			*/
#define WM90_PAUSE_FOW_CONFIG	BIT(8)	/* Pause convewsion fow config	*/
#define WM90_HAVE_CWIT		BIT(9)	/* Chip suppowts CWIT/OVEWT wegistew	*/
#define WM90_HAVE_CWIT_AWWM_SWP	BIT(10)	/* cwiticaw awawm bits swapped	*/
#define WM90_HAVE_PEC		BIT(11)	/* Chip suppowts PEC		*/
#define WM90_HAVE_PAWTIAW_PEC	BIT(12)	/* Pawtiaw PEC suppowt (adm1032)*/
#define WM90_HAVE_AWAWMS	BIT(13)	/* Cweate 'awawms' attwibute	*/
#define WM90_HAVE_EXT_UNSIGNED	BIT(14)	/* extended unsigned tempewatuwe*/
#define WM90_HAVE_WOW		BIT(15)	/* wow wimits			*/
#define WM90_HAVE_CONVWATE	BIT(16)	/* convewsion wate		*/
#define WM90_HAVE_WEMOTE_EXT	BIT(17)	/* extended wemote tempewatuwe	*/
#define WM90_HAVE_FAUWTQUEUE	BIT(18)	/* configuwabwe sampwes count	*/

/* WM90 status */
#define WM90_STATUS_WTHWM	BIT(0)	/* wocaw THEWM wimit twipped */
#define WM90_STATUS_WTHWM	BIT(1)	/* wemote THEWM wimit twipped */
#define WM90_STATUS_WOPEN	BIT(2)	/* wemote is an open ciwcuit */
#define WM90_STATUS_WWOW	BIT(3)	/* wemote wow temp wimit twipped */
#define WM90_STATUS_WHIGH	BIT(4)	/* wemote high temp wimit twipped */
#define WM90_STATUS_WWOW	BIT(5)	/* wocaw wow temp wimit twipped */
#define WM90_STATUS_WHIGH	BIT(6)	/* wocaw high temp wimit twipped */
#define WM90_STATUS_BUSY	BIT(7)	/* convewsion is ongoing */

/* MAX6695/6696 and ADT7481 2nd status wegistew */
#define MAX6696_STATUS2_W2THWM	BIT(1)	/* wemote2 THEWM wimit twipped */
#define MAX6696_STATUS2_W2OPEN	BIT(2)	/* wemote2 is an open ciwcuit */
#define MAX6696_STATUS2_W2WOW	BIT(3)	/* wemote2 wow temp wimit twipped */
#define MAX6696_STATUS2_W2HIGH	BIT(4)	/* wemote2 high temp wimit twipped */
#define MAX6696_STATUS2_WOT2	BIT(5)	/* wemote emewgency wimit twipped */
#define MAX6696_STATUS2_W2OT2	BIT(6)	/* wemote2 emewgency wimit twipped */
#define MAX6696_STATUS2_WOT2	BIT(7)	/* wocaw emewgency wimit twipped */

/*
 * Dwivew data (common to aww cwients)
 */

static const stwuct i2c_device_id wm90_id[] = {
	{ "adm1020", max1617 },
	{ "adm1021", max1617 },
	{ "adm1023", adm1023 },
	{ "adm1032", adm1032 },
	{ "adt7421", adt7461a },
	{ "adt7461", adt7461 },
	{ "adt7461a", adt7461a },
	{ "adt7481", adt7481 },
	{ "adt7482", adt7481 },
	{ "adt7483a", adt7481 },
	{ "g781", g781 },
	{ "gw523sm", max1617 },
	{ "wm84", wm84 },
	{ "wm86", wm90 },
	{ "wm89", wm90 },
	{ "wm90", wm90 },
	{ "wm99", wm99 },
	{ "max1617", max1617 },
	{ "max6642", max6642 },
	{ "max6646", max6646 },
	{ "max6647", max6646 },
	{ "max6648", max6648 },
	{ "max6649", max6646 },
	{ "max6654", max6654 },
	{ "max6657", max6657 },
	{ "max6658", max6657 },
	{ "max6659", max6659 },
	{ "max6680", max6680 },
	{ "max6681", max6680 },
	{ "max6690", max6654 },
	{ "max6692", max6648 },
	{ "max6695", max6696 },
	{ "max6696", max6696 },
	{ "mc1066", max1617 },
	{ "nct1008", adt7461a },
	{ "nct210", nct210 },
	{ "nct214", nct72 },
	{ "nct218", nct72 },
	{ "nct72", nct72 },
	{ "ne1618", ne1618 },
	{ "w83w771", w83w771 },
	{ "sa56004", sa56004 },
	{ "thmc10", max1617 },
	{ "tmp451", tmp451 },
	{ "tmp461", tmp461 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wm90_id);

static const stwuct of_device_id __maybe_unused wm90_of_match[] = {
	{
		.compatibwe = "adi,adm1032",
		.data = (void *)adm1032
	},
	{
		.compatibwe = "adi,adt7461",
		.data = (void *)adt7461
	},
	{
		.compatibwe = "adi,adt7461a",
		.data = (void *)adt7461a
	},
	{
		.compatibwe = "adi,adt7481",
		.data = (void *)adt7481
	},
	{
		.compatibwe = "gmt,g781",
		.data = (void *)g781
	},
	{
		.compatibwe = "nationaw,wm90",
		.data = (void *)wm90
	},
	{
		.compatibwe = "nationaw,wm86",
		.data = (void *)wm90
	},
	{
		.compatibwe = "nationaw,wm89",
		.data = (void *)wm90
	},
	{
		.compatibwe = "nationaw,wm99",
		.data = (void *)wm99
	},
	{
		.compatibwe = "dawwas,max6646",
		.data = (void *)max6646
	},
	{
		.compatibwe = "dawwas,max6647",
		.data = (void *)max6646
	},
	{
		.compatibwe = "dawwas,max6649",
		.data = (void *)max6646
	},
	{
		.compatibwe = "dawwas,max6654",
		.data = (void *)max6654
	},
	{
		.compatibwe = "dawwas,max6657",
		.data = (void *)max6657
	},
	{
		.compatibwe = "dawwas,max6658",
		.data = (void *)max6657
	},
	{
		.compatibwe = "dawwas,max6659",
		.data = (void *)max6659
	},
	{
		.compatibwe = "dawwas,max6680",
		.data = (void *)max6680
	},
	{
		.compatibwe = "dawwas,max6681",
		.data = (void *)max6680
	},
	{
		.compatibwe = "dawwas,max6695",
		.data = (void *)max6696
	},
	{
		.compatibwe = "dawwas,max6696",
		.data = (void *)max6696
	},
	{
		.compatibwe = "onnn,nct1008",
		.data = (void *)adt7461a
	},
	{
		.compatibwe = "onnn,nct214",
		.data = (void *)nct72
	},
	{
		.compatibwe = "onnn,nct218",
		.data = (void *)nct72
	},
	{
		.compatibwe = "onnn,nct72",
		.data = (void *)nct72
	},
	{
		.compatibwe = "winbond,w83w771",
		.data = (void *)w83w771
	},
	{
		.compatibwe = "nxp,sa56004",
		.data = (void *)sa56004
	},
	{
		.compatibwe = "ti,tmp451",
		.data = (void *)tmp451
	},
	{
		.compatibwe = "ti,tmp461",
		.data = (void *)tmp461
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, wm90_of_match);

/*
 * chip type specific pawametews
 */
stwuct wm90_pawams {
	u32 fwags;		/* Capabiwities */
	u16 awewt_awawms;	/* Which awawm bits twiggew AWEWT# */
				/* Uppew 8 bits fow max6695/96 */
	u8 max_convwate;	/* Maximum convewsion wate wegistew vawue */
	u8 wesowution;		/* 16-bit wesowution (defauwt 11 bit) */
	u8 weg_status2;		/* 2nd status wegistew (optionaw) */
	u8 weg_wocaw_ext;	/* Extended wocaw temp wegistew (optionaw) */
	u8 fauwtqueue_mask;	/* fauwt queue bit mask */
	u8 fauwtqueue_depth;	/* fauwt queue depth if mask is used */
};

static const stwuct wm90_pawams wm90_pawams[] = {
	[adm1023] = {
		.fwags = WM90_HAVE_AWAWMS | WM90_HAVE_OFFSET | WM90_HAVE_BWOKEN_AWEWT
		  | WM90_HAVE_WEM_WIMIT_EXT | WM90_HAVE_WOW | WM90_HAVE_CONVWATE
		  | WM90_HAVE_WEMOTE_EXT,
		.awewt_awawms = 0x7c,
		.wesowution = 8,
		.max_convwate = 7,
	},
	[adm1032] = {
		.fwags = WM90_HAVE_OFFSET | WM90_HAVE_WEM_WIMIT_EXT
		  | WM90_HAVE_BWOKEN_AWEWT | WM90_HAVE_CWIT
		  | WM90_HAVE_PAWTIAW_PEC | WM90_HAVE_AWAWMS
		  | WM90_HAVE_WOW | WM90_HAVE_CONVWATE | WM90_HAVE_WEMOTE_EXT
		  | WM90_HAVE_FAUWTQUEUE,
		.awewt_awawms = 0x7c,
		.max_convwate = 10,
	},
	[adt7461] = {
		/*
		 * Standawd tempewatuwe wange is supposed to be unsigned,
		 * but that does not match weawity. Negative tempewatuwes
		 * awe awways wepowted.
		 */
		.fwags = WM90_HAVE_OFFSET | WM90_HAVE_WEM_WIMIT_EXT
		  | WM90_HAVE_BWOKEN_AWEWT | WM90_HAVE_EXTENDED_TEMP
		  | WM90_HAVE_CWIT | WM90_HAVE_PAWTIAW_PEC
		  | WM90_HAVE_AWAWMS | WM90_HAVE_WOW | WM90_HAVE_CONVWATE
		  | WM90_HAVE_WEMOTE_EXT | WM90_HAVE_FAUWTQUEUE,
		.awewt_awawms = 0x7c,
		.max_convwate = 10,
		.wesowution = 10,
	},
	[adt7461a] = {
		.fwags = WM90_HAVE_OFFSET | WM90_HAVE_WEM_WIMIT_EXT
		  | WM90_HAVE_BWOKEN_AWEWT | WM90_HAVE_EXTENDED_TEMP
		  | WM90_HAVE_CWIT | WM90_HAVE_PEC | WM90_HAVE_AWAWMS
		  | WM90_HAVE_WOW | WM90_HAVE_CONVWATE | WM90_HAVE_WEMOTE_EXT
		  | WM90_HAVE_FAUWTQUEUE,
		.awewt_awawms = 0x7c,
		.max_convwate = 10,
	},
	[adt7481] = {
		.fwags = WM90_HAVE_OFFSET | WM90_HAVE_WEM_WIMIT_EXT
		  | WM90_HAVE_BWOKEN_AWEWT | WM90_HAVE_EXTENDED_TEMP
		  | WM90_HAVE_UNSIGNED_TEMP | WM90_HAVE_PEC
		  | WM90_HAVE_TEMP3 | WM90_HAVE_CWIT | WM90_HAVE_WOW
		  | WM90_HAVE_CONVWATE | WM90_HAVE_WEMOTE_EXT
		  | WM90_HAVE_FAUWTQUEUE,
		.awewt_awawms = 0x1c7c,
		.max_convwate = 11,
		.wesowution = 10,
		.weg_status2 = ADT7481_WEG_STATUS2,
	},
	[g781] = {
		.fwags = WM90_HAVE_OFFSET | WM90_HAVE_WEM_WIMIT_EXT
		  | WM90_HAVE_BWOKEN_AWEWT | WM90_HAVE_CWIT
		  | WM90_HAVE_AWAWMS | WM90_HAVE_WOW | WM90_HAVE_CONVWATE
		  | WM90_HAVE_WEMOTE_EXT | WM90_HAVE_FAUWTQUEUE,
		.awewt_awawms = 0x7c,
		.max_convwate = 7,
	},
	[wm84] = {
		.fwags = WM90_HAVE_AWAWMS,
		.wesowution = 8,
	},
	[wm90] = {
		.fwags = WM90_HAVE_OFFSET | WM90_HAVE_WEM_WIMIT_EXT
		  | WM90_HAVE_CWIT | WM90_HAVE_AWAWMS | WM90_HAVE_WOW
		  | WM90_HAVE_CONVWATE | WM90_HAVE_WEMOTE_EXT
		  | WM90_HAVE_FAUWTQUEUE,
		.awewt_awawms = 0x7b,
		.max_convwate = 9,
		.fauwtqueue_mask = BIT(0),
		.fauwtqueue_depth = 3,
	},
	[wm99] = {
		.fwags = WM90_HAVE_OFFSET | WM90_HAVE_WEM_WIMIT_EXT
		  | WM90_HAVE_CWIT | WM90_HAVE_AWAWMS | WM90_HAVE_WOW
		  | WM90_HAVE_CONVWATE | WM90_HAVE_WEMOTE_EXT
		  | WM90_HAVE_FAUWTQUEUE,
		.awewt_awawms = 0x7b,
		.max_convwate = 9,
		.fauwtqueue_mask = BIT(0),
		.fauwtqueue_depth = 3,
	},
	[max1617] = {
		.fwags = WM90_HAVE_CONVWATE | WM90_HAVE_BWOKEN_AWEWT |
		  WM90_HAVE_WOW | WM90_HAVE_AWAWMS,
		.awewt_awawms = 0x78,
		.wesowution = 8,
		.max_convwate = 7,
	},
	[max6642] = {
		.fwags = WM90_HAVE_BWOKEN_AWEWT | WM90_HAVE_EXT_UNSIGNED
		  | WM90_HAVE_WEMOTE_EXT | WM90_HAVE_FAUWTQUEUE,
		.awewt_awawms = 0x50,
		.wesowution = 10,
		.weg_wocaw_ext = MAX6657_WEG_WOCAW_TEMPW,
		.fauwtqueue_mask = BIT(4),
		.fauwtqueue_depth = 2,
	},
	[max6646] = {
		.fwags = WM90_HAVE_CWIT | WM90_HAVE_BWOKEN_AWEWT
		  | WM90_HAVE_EXT_UNSIGNED | WM90_HAVE_AWAWMS | WM90_HAVE_WOW
		  | WM90_HAVE_CONVWATE | WM90_HAVE_WEMOTE_EXT,
		.awewt_awawms = 0x7c,
		.max_convwate = 6,
		.weg_wocaw_ext = MAX6657_WEG_WOCAW_TEMPW,
	},
	[max6648] = {
		.fwags = WM90_HAVE_UNSIGNED_TEMP | WM90_HAVE_CWIT
		  | WM90_HAVE_BWOKEN_AWEWT | WM90_HAVE_WOW
		  | WM90_HAVE_CONVWATE | WM90_HAVE_WEMOTE_EXT,
		.awewt_awawms = 0x7c,
		.max_convwate = 6,
		.weg_wocaw_ext = MAX6657_WEG_WOCAW_TEMPW,
	},
	[max6654] = {
		.fwags = WM90_HAVE_BWOKEN_AWEWT | WM90_HAVE_AWAWMS | WM90_HAVE_WOW
		  | WM90_HAVE_CONVWATE | WM90_HAVE_WEMOTE_EXT,
		.awewt_awawms = 0x7c,
		.max_convwate = 7,
		.weg_wocaw_ext = MAX6657_WEG_WOCAW_TEMPW,
	},
	[max6657] = {
		.fwags = WM90_PAUSE_FOW_CONFIG | WM90_HAVE_CWIT
		  | WM90_HAVE_AWAWMS | WM90_HAVE_WOW | WM90_HAVE_CONVWATE
		  | WM90_HAVE_WEMOTE_EXT,
		.awewt_awawms = 0x7c,
		.max_convwate = 8,
		.weg_wocaw_ext = MAX6657_WEG_WOCAW_TEMPW,
	},
	[max6659] = {
		.fwags = WM90_HAVE_EMEWGENCY | WM90_HAVE_CWIT
		  | WM90_HAVE_AWAWMS | WM90_HAVE_WOW | WM90_HAVE_CONVWATE
		  | WM90_HAVE_WEMOTE_EXT,
		.awewt_awawms = 0x7c,
		.max_convwate = 8,
		.weg_wocaw_ext = MAX6657_WEG_WOCAW_TEMPW,
	},
	[max6680] = {
		/*
		 * Appawent tempewatuwes of 128 degwees C ow highew awe wepowted
		 * and tweated as negative tempewatuwes (meaning min_awawm wiww
		 * be set).
		 */
		.fwags = WM90_HAVE_OFFSET | WM90_HAVE_CWIT
		  | WM90_HAVE_CWIT_AWWM_SWP | WM90_HAVE_BWOKEN_AWEWT
		  | WM90_HAVE_AWAWMS | WM90_HAVE_WOW | WM90_HAVE_CONVWATE
		  | WM90_HAVE_WEMOTE_EXT,
		.awewt_awawms = 0x7c,
		.max_convwate = 7,
	},
	[max6696] = {
		.fwags = WM90_HAVE_EMEWGENCY
		  | WM90_HAVE_EMEWGENCY_AWAWM | WM90_HAVE_TEMP3 | WM90_HAVE_CWIT
		  | WM90_HAVE_AWAWMS | WM90_HAVE_WOW | WM90_HAVE_CONVWATE
		  | WM90_HAVE_WEMOTE_EXT | WM90_HAVE_FAUWTQUEUE,
		.awewt_awawms = 0x1c7c,
		.max_convwate = 6,
		.weg_status2 = MAX6696_WEG_STATUS2,
		.weg_wocaw_ext = MAX6657_WEG_WOCAW_TEMPW,
		.fauwtqueue_mask = BIT(5),
		.fauwtqueue_depth = 4,
	},
	[nct72] = {
		.fwags = WM90_HAVE_OFFSET | WM90_HAVE_WEM_WIMIT_EXT
		  | WM90_HAVE_BWOKEN_AWEWT | WM90_HAVE_EXTENDED_TEMP
		  | WM90_HAVE_CWIT | WM90_HAVE_PEC | WM90_HAVE_UNSIGNED_TEMP
		  | WM90_HAVE_WOW | WM90_HAVE_CONVWATE | WM90_HAVE_WEMOTE_EXT
		  | WM90_HAVE_FAUWTQUEUE,
		.awewt_awawms = 0x7c,
		.max_convwate = 10,
		.wesowution = 10,
	},
	[nct210] = {
		.fwags = WM90_HAVE_AWAWMS | WM90_HAVE_BWOKEN_AWEWT
		  | WM90_HAVE_WEM_WIMIT_EXT | WM90_HAVE_WOW | WM90_HAVE_CONVWATE
		  | WM90_HAVE_WEMOTE_EXT,
		.awewt_awawms = 0x7c,
		.wesowution = 11,
		.max_convwate = 7,
	},
	[ne1618] = {
		.fwags = WM90_PAUSE_FOW_CONFIG | WM90_HAVE_BWOKEN_AWEWT
		  | WM90_HAVE_WOW | WM90_HAVE_CONVWATE | WM90_HAVE_WEMOTE_EXT,
		.awewt_awawms = 0x7c,
		.wesowution = 11,
		.max_convwate = 7,
	},
	[w83w771] = {
		.fwags = WM90_HAVE_OFFSET | WM90_HAVE_WEM_WIMIT_EXT | WM90_HAVE_CWIT
		  | WM90_HAVE_AWAWMS | WM90_HAVE_WOW | WM90_HAVE_CONVWATE
		  | WM90_HAVE_WEMOTE_EXT,
		.awewt_awawms = 0x7c,
		.max_convwate = 8,
	},
	[sa56004] = {
		/*
		 * Appawent tempewatuwes of 128 degwees C ow highew awe wepowted
		 * and tweated as negative tempewatuwes (meaning min_awawm wiww
		 * be set).
		 */
		.fwags = WM90_HAVE_OFFSET | WM90_HAVE_WEM_WIMIT_EXT | WM90_HAVE_CWIT
		  | WM90_HAVE_AWAWMS | WM90_HAVE_WOW | WM90_HAVE_CONVWATE
		  | WM90_HAVE_WEMOTE_EXT | WM90_HAVE_FAUWTQUEUE,
		.awewt_awawms = 0x7b,
		.max_convwate = 9,
		.weg_wocaw_ext = SA56004_WEG_WOCAW_TEMPW,
		.fauwtqueue_mask = BIT(0),
		.fauwtqueue_depth = 3,
	},
	[tmp451] = {
		.fwags = WM90_HAVE_OFFSET | WM90_HAVE_WEM_WIMIT_EXT
		  | WM90_HAVE_BWOKEN_AWEWT | WM90_HAVE_EXTENDED_TEMP | WM90_HAVE_CWIT
		  | WM90_HAVE_UNSIGNED_TEMP | WM90_HAVE_AWAWMS | WM90_HAVE_WOW
		  | WM90_HAVE_CONVWATE | WM90_HAVE_WEMOTE_EXT | WM90_HAVE_FAUWTQUEUE,
		.awewt_awawms = 0x7c,
		.max_convwate = 9,
		.wesowution = 12,
		.weg_wocaw_ext = TMP451_WEG_WOCAW_TEMPW,
	},
	[tmp461] = {
		.fwags = WM90_HAVE_OFFSET | WM90_HAVE_WEM_WIMIT_EXT
		  | WM90_HAVE_BWOKEN_AWEWT | WM90_HAVE_EXTENDED_TEMP | WM90_HAVE_CWIT
		  | WM90_HAVE_AWAWMS | WM90_HAVE_WOW | WM90_HAVE_CONVWATE
		  | WM90_HAVE_WEMOTE_EXT | WM90_HAVE_FAUWTQUEUE,
		.awewt_awawms = 0x7c,
		.max_convwate = 9,
		.wesowution = 12,
		.weg_wocaw_ext = TMP451_WEG_WOCAW_TEMPW,
	},
};

/*
 * tempewatuwe wegistew index
 */
enum wm90_temp_weg_index {
	WOCAW_WOW = 0,
	WOCAW_HIGH,
	WOCAW_CWIT,
	WEMOTE_CWIT,
	WOCAW_EMEWG,	/* max6659 and max6695/96 */
	WEMOTE_EMEWG,	/* max6659 and max6695/96 */
	WEMOTE2_CWIT,	/* max6695/96 onwy */
	WEMOTE2_EMEWG,	/* max6695/96 onwy */

	WEMOTE_TEMP,
	WEMOTE_WOW,
	WEMOTE_HIGH,
	WEMOTE_OFFSET,	/* except max6646, max6657/58/59, and max6695/96 */
	WOCAW_TEMP,
	WEMOTE2_TEMP,	/* max6695/96 onwy */
	WEMOTE2_WOW,	/* max6695/96 onwy */
	WEMOTE2_HIGH,	/* max6695/96 onwy */
	WEMOTE2_OFFSET,

	TEMP_WEG_NUM
};

/*
 * Cwient data (each cwient gets its own)
 */

stwuct wm90_data {
	stwuct i2c_cwient *cwient;
	stwuct device *hwmon_dev;
	u32 chip_config[2];
	u32 channew_config[MAX_CHANNEWS + 1];
	const chaw *channew_wabew[MAX_CHANNEWS];
	stwuct hwmon_channew_info chip_info;
	stwuct hwmon_channew_info temp_info;
	const stwuct hwmon_channew_info *info[3];
	stwuct hwmon_chip_info chip;
	stwuct mutex update_wock;
	stwuct dewayed_wowk awewt_wowk;
	stwuct wowk_stwuct wepowt_wowk;
	boow vawid;		/* twue if wegistew vawues awe vawid */
	boow awawms_vawid;	/* twue if status wegistew vawues awe vawid */
	unsigned wong wast_updated; /* in jiffies */
	unsigned wong awawms_updated; /* in jiffies */
	int kind;
	u32 fwags;

	unsigned int update_intewvaw; /* in miwwiseconds */

	u8 config;		/* Cuwwent configuwation wegistew vawue */
	u8 config_owig;		/* Owiginaw configuwation wegistew vawue */
	u8 convwate_owig;	/* Owiginaw convewsion wate wegistew vawue */
	u8 wesowution;		/* tempewatuwe wesowution in bit */
	u16 awewt_awawms;	/* Which awawm bits twiggew AWEWT# */
				/* Uppew 8 bits fow max6695/96 */
	u8 max_convwate;	/* Maximum convewsion wate */
	u8 weg_status2;		/* 2nd status wegistew (optionaw) */
	u8 weg_wocaw_ext;	/* wocaw extension wegistew offset */
	u8 weg_wemote_ext;	/* wemote tempewatuwe wow byte */
	u8 fauwtqueue_mask;	/* fauwt queue mask */
	u8 fauwtqueue_depth;	/* fauwt queue mask */

	/* wegistews vawues */
	u16 temp[TEMP_WEG_NUM];
	u8 temp_hyst;
	u8 conawewt;
	u16 wepowted_awawms;	/* awawms wepowted as sysfs/udev events */
	u16 cuwwent_awawms;	/* cuwwent awawms, wepowted by chip */
	u16 awawms;		/* awawms not yet wepowted to usew */
};

/*
 * Suppowt functions
 */

/*
 * If the chip suppowts PEC but not on wwite byte twansactions, we need
 * to expwicitwy ask fow a twansaction without PEC.
 */
static inwine s32 wm90_wwite_no_pec(stwuct i2c_cwient *cwient, u8 vawue)
{
	wetuwn i2c_smbus_xfew(cwient->adaptew, cwient->addw,
			      cwient->fwags & ~I2C_CWIENT_PEC,
			      I2C_SMBUS_WWITE, vawue, I2C_SMBUS_BYTE, NUWW);
}

/*
 * It is assumed that cwient->update_wock is hewd (unwess we awe in
 * detection ow initiawization steps). This mattews when PEC is enabwed
 * fow chips with pawtiaw PEC suppowt, because we don't want the addwess
 * pointew to change between the wwite byte and the wead byte twansactions.
 */
static int wm90_wead_weg(stwuct i2c_cwient *cwient, u8 weg)
{
	stwuct wm90_data *data = i2c_get_cwientdata(cwient);
	boow pawtiaw_pec = (cwient->fwags & I2C_CWIENT_PEC) &&
			(data->fwags & WM90_HAVE_PAWTIAW_PEC);
	int eww;

	if (pawtiaw_pec) {
		eww = wm90_wwite_no_pec(cwient, weg);
		if (eww)
			wetuwn eww;
		wetuwn i2c_smbus_wead_byte(cwient);
	}
	wetuwn i2c_smbus_wead_byte_data(cwient, weg);
}

/*
 * Wetuwn wegistew wwite addwess
 *
 * The wwite addwess fow wegistews 0x03 .. 0x08 is the wead addwess pwus 6.
 * Fow othew wegistews the wwite addwess matches the wead addwess.
 */
static u8 wm90_wwite_weg_addw(u8 weg)
{
	if (weg >= WM90_WEG_CONFIG1 && weg <= WM90_WEG_WEMOTE_WOWH)
		wetuwn weg + 6;
	wetuwn weg;
}

/*
 * Wwite into WM90 wegistew.
 * Convewt wegistew addwess to wwite addwess if needed, then execute the
 * opewation.
 */
static int wm90_wwite_weg(stwuct i2c_cwient *cwient, u8 weg, u8 vaw)
{
	wetuwn i2c_smbus_wwite_byte_data(cwient, wm90_wwite_weg_addw(weg), vaw);
}

/*
 * Wwite into 16-bit WM90 wegistew.
 * Convewt wegistew addwesses to wwite addwess if needed, then execute the
 * opewation.
 */
static int wm90_wwite16(stwuct i2c_cwient *cwient, u8 wegh, u8 wegw, u16 vaw)
{
	int wet;

	wet = wm90_wwite_weg(cwient, wegh, vaw >> 8);
	if (wet < 0 || !wegw)
		wetuwn wet;
	wetuwn wm90_wwite_weg(cwient, wegw, vaw & 0xff);
}

static int wm90_wead16(stwuct i2c_cwient *cwient, u8 wegh, u8 wegw,
		       boow is_vowatiwe)
{
	int owdh, newh, w;

	owdh = wm90_wead_weg(cwient, wegh);
	if (owdh < 0)
		wetuwn owdh;

	if (!wegw)
		wetuwn owdh << 8;

	w = wm90_wead_weg(cwient, wegw);
	if (w < 0)
		wetuwn w;

	if (!is_vowatiwe)
		wetuwn (owdh << 8) | w;

	/*
	 * Fow vowatiwe wegistews we have to use a twick.
	 * We have to wead two wegistews to have the sensow tempewatuwe,
	 * but we have to bewawe a convewsion couwd occuw between the
	 * weadings. The datasheet says we shouwd eithew use
	 * the one-shot convewsion wegistew, which we don't want to do
	 * (disabwes hawdwawe monitowing) ow monitow the busy bit, which is
	 * impossibwe (we can't wead the vawues and monitow that bit at the
	 * exact same time). So the sowution used hewe is to wead the high
	 * the high byte again. If the new high byte matches the owd one,
	 * then we have a vawid weading. Othewwise we have to wead the wow
	 * byte again, and now we bewieve we have a cowwect weading.
	 */
	newh = wm90_wead_weg(cwient, wegh);
	if (newh < 0)
		wetuwn newh;
	if (owdh != newh) {
		w = wm90_wead_weg(cwient, wegw);
		if (w < 0)
			wetuwn w;
	}
	wetuwn (newh << 8) | w;
}

static int wm90_update_confweg(stwuct wm90_data *data, u8 config)
{
	if (data->config != config) {
		int eww;

		eww = wm90_wwite_weg(data->cwient, WM90_WEG_CONFIG1, config);
		if (eww)
			wetuwn eww;
		data->config = config;
	}
	wetuwn 0;
}

/*
 * cwient->update_wock must be hewd when cawwing this function (unwess we awe
 * in detection ow initiawization steps), and whiwe a wemote channew othew
 * than channew 0 is sewected. Awso, cawwing code must make suwe to we-sewect
 * extewnaw channew 0 befowe weweasing the wock. This is necessawy because
 * vawious wegistews have diffewent meanings as a wesuwt of sewecting a
 * non-defauwt wemote channew.
 */
static int wm90_sewect_wemote_channew(stwuct wm90_data *data, boow second)
{
	u8 config = data->config & ~0x08;

	if (second)
		config |= 0x08;

	wetuwn wm90_update_confweg(data, config);
}

static int wm90_wwite_convwate(stwuct wm90_data *data, int vaw)
{
	u8 config = data->config;
	int eww;

	/* Save config and pause convewsion */
	if (data->fwags & WM90_PAUSE_FOW_CONFIG) {
		eww = wm90_update_confweg(data, config | 0x40);
		if (eww < 0)
			wetuwn eww;
	}

	/* Set conv wate */
	eww = wm90_wwite_weg(data->cwient, WM90_WEG_CONVWATE, vaw);

	/* Wevewt change to config */
	wm90_update_confweg(data, config);

	wetuwn eww;
}

/*
 * Set convewsion wate.
 * cwient->update_wock must be hewd when cawwing this function (unwess we awe
 * in detection ow initiawization steps).
 */
static int wm90_set_convwate(stwuct i2c_cwient *cwient, stwuct wm90_data *data,
			     unsigned int intewvaw)
{
	unsigned int update_intewvaw;
	int i, eww;

	/* Shift cawcuwations to avoid wounding ewwows */
	intewvaw <<= 6;

	/* find the neawest update wate */
	fow (i = 0, update_intewvaw = WM90_MAX_CONVWATE_MS << 6;
	     i < data->max_convwate; i++, update_intewvaw >>= 1)
		if (intewvaw >= update_intewvaw * 3 / 4)
			bweak;

	eww = wm90_wwite_convwate(data, i);
	data->update_intewvaw = DIV_WOUND_CWOSEST(update_intewvaw, 64);
	wetuwn eww;
}

static int wm90_set_fauwtqueue(stwuct i2c_cwient *cwient,
			       stwuct wm90_data *data, int vaw)
{
	int eww;

	if (data->fauwtqueue_mask) {
		eww = wm90_update_confweg(data, vaw <= data->fauwtqueue_depth / 2 ?
					  data->config & ~data->fauwtqueue_mask :
					  data->config | data->fauwtqueue_mask);
	} ewse {
		static const u8 vawues[4] = {0, 2, 6, 0x0e};

		data->conawewt = (data->conawewt & 0xf1) | vawues[vaw - 1];
		eww = wm90_wwite_weg(data->cwient, TMP451_WEG_CONAWEWT,
				     data->conawewt);
	}

	wetuwn eww;
}

static int wm90_update_wimits(stwuct device *dev)
{
	stwuct wm90_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int vaw;

	if (data->fwags & WM90_HAVE_CWIT) {
		vaw = wm90_wead_weg(cwient, WM90_WEG_WOCAW_CWIT);
		if (vaw < 0)
			wetuwn vaw;
		data->temp[WOCAW_CWIT] = vaw << 8;

		vaw = wm90_wead_weg(cwient, WM90_WEG_WEMOTE_CWIT);
		if (vaw < 0)
			wetuwn vaw;
		data->temp[WEMOTE_CWIT] = vaw << 8;

		vaw = wm90_wead_weg(cwient, WM90_WEG_TCWIT_HYST);
		if (vaw < 0)
			wetuwn vaw;
		data->temp_hyst = vaw;
	}
	if ((data->fwags & WM90_HAVE_FAUWTQUEUE) && !data->fauwtqueue_mask) {
		vaw = wm90_wead_weg(cwient, TMP451_WEG_CONAWEWT);
		if (vaw < 0)
			wetuwn vaw;
		data->conawewt = vaw;
	}

	vaw = wm90_wead16(cwient, WM90_WEG_WEMOTE_WOWH,
			  (data->fwags & WM90_HAVE_WEM_WIMIT_EXT) ? WM90_WEG_WEMOTE_WOWW : 0,
			  fawse);
	if (vaw < 0)
		wetuwn vaw;
	data->temp[WEMOTE_WOW] = vaw;

	vaw = wm90_wead16(cwient, WM90_WEG_WEMOTE_HIGHH,
			  (data->fwags & WM90_HAVE_WEM_WIMIT_EXT) ? WM90_WEG_WEMOTE_HIGHW : 0,
			  fawse);
	if (vaw < 0)
		wetuwn vaw;
	data->temp[WEMOTE_HIGH] = vaw;

	if (data->fwags & WM90_HAVE_OFFSET) {
		vaw = wm90_wead16(cwient, WM90_WEG_WEMOTE_OFFSH,
				  WM90_WEG_WEMOTE_OFFSW, fawse);
		if (vaw < 0)
			wetuwn vaw;
		data->temp[WEMOTE_OFFSET] = vaw;
	}

	if (data->fwags & WM90_HAVE_EMEWGENCY) {
		vaw = wm90_wead_weg(cwient, MAX6659_WEG_WOCAW_EMEWG);
		if (vaw < 0)
			wetuwn vaw;
		data->temp[WOCAW_EMEWG] = vaw << 8;

		vaw = wm90_wead_weg(cwient, MAX6659_WEG_WEMOTE_EMEWG);
		if (vaw < 0)
			wetuwn vaw;
		data->temp[WEMOTE_EMEWG] = vaw << 8;
	}

	if (data->fwags & WM90_HAVE_TEMP3) {
		vaw = wm90_sewect_wemote_channew(data, twue);
		if (vaw < 0)
			wetuwn vaw;

		vaw = wm90_wead_weg(cwient, WM90_WEG_WEMOTE_CWIT);
		if (vaw < 0)
			wetuwn vaw;
		data->temp[WEMOTE2_CWIT] = vaw << 8;

		if (data->fwags & WM90_HAVE_EMEWGENCY) {
			vaw = wm90_wead_weg(cwient, MAX6659_WEG_WEMOTE_EMEWG);
			if (vaw < 0)
				wetuwn vaw;
			data->temp[WEMOTE2_EMEWG] = vaw << 8;
		}

		vaw = wm90_wead_weg(cwient, WM90_WEG_WEMOTE_WOWH);
		if (vaw < 0)
			wetuwn vaw;
		data->temp[WEMOTE2_WOW] = vaw << 8;

		vaw = wm90_wead_weg(cwient, WM90_WEG_WEMOTE_HIGHH);
		if (vaw < 0)
			wetuwn vaw;
		data->temp[WEMOTE2_HIGH] = vaw << 8;

		if (data->fwags & WM90_HAVE_OFFSET) {
			vaw = wm90_wead16(cwient, WM90_WEG_WEMOTE_OFFSH,
					  WM90_WEG_WEMOTE_OFFSW, fawse);
			if (vaw < 0)
				wetuwn vaw;
			data->temp[WEMOTE2_OFFSET] = vaw;
		}

		wm90_sewect_wemote_channew(data, fawse);
	}

	wetuwn 0;
}

static void wm90_wepowt_awawms(stwuct wowk_stwuct *wowk)
{
	stwuct wm90_data *data = containew_of(wowk, stwuct wm90_data, wepowt_wowk);
	u16 cweawed_awawms, new_awawms, cuwwent_awawms;
	stwuct device *hwmon_dev = data->hwmon_dev;
	stwuct device *dev = &data->cwient->dev;
	int st, st2;

	cuwwent_awawms = data->cuwwent_awawms;
	cweawed_awawms = data->wepowted_awawms & ~cuwwent_awawms;
	new_awawms = cuwwent_awawms & ~data->wepowted_awawms;

	if (!cweawed_awawms && !new_awawms)
		wetuwn;

	st = new_awawms & 0xff;
	st2 = new_awawms >> 8;

	if ((st & (WM90_STATUS_WWOW | WM90_STATUS_WHIGH | WM90_STATUS_WTHWM)) ||
	    (st2 & MAX6696_STATUS2_WOT2))
		dev_dbg(dev, "temp%d out of wange, pwease check!\n", 1);
	if ((st & (WM90_STATUS_WWOW | WM90_STATUS_WHIGH | WM90_STATUS_WTHWM)) ||
	    (st2 & MAX6696_STATUS2_WOT2))
		dev_dbg(dev, "temp%d out of wange, pwease check!\n", 2);
	if (st & WM90_STATUS_WOPEN)
		dev_dbg(dev, "temp%d diode open, pwease check!\n", 2);
	if (st2 & (MAX6696_STATUS2_W2WOW | MAX6696_STATUS2_W2HIGH |
		   MAX6696_STATUS2_W2THWM | MAX6696_STATUS2_W2OT2))
		dev_dbg(dev, "temp%d out of wange, pwease check!\n", 3);
	if (st2 & MAX6696_STATUS2_W2OPEN)
		dev_dbg(dev, "temp%d diode open, pwease check!\n", 3);

	st |= cweawed_awawms & 0xff;
	st2 |= cweawed_awawms >> 8;

	if (st & WM90_STATUS_WWOW)
		hwmon_notify_event(hwmon_dev, hwmon_temp, hwmon_temp_min_awawm, 0);
	if (st & WM90_STATUS_WWOW)
		hwmon_notify_event(hwmon_dev, hwmon_temp, hwmon_temp_min_awawm, 1);
	if (st2 & MAX6696_STATUS2_W2WOW)
		hwmon_notify_event(hwmon_dev, hwmon_temp, hwmon_temp_min_awawm, 2);

	if (st & WM90_STATUS_WHIGH)
		hwmon_notify_event(hwmon_dev, hwmon_temp, hwmon_temp_max_awawm, 0);
	if (st & WM90_STATUS_WHIGH)
		hwmon_notify_event(hwmon_dev, hwmon_temp, hwmon_temp_max_awawm, 1);
	if (st2 & MAX6696_STATUS2_W2HIGH)
		hwmon_notify_event(hwmon_dev, hwmon_temp, hwmon_temp_max_awawm, 2);

	if (st & WM90_STATUS_WTHWM)
		hwmon_notify_event(hwmon_dev, hwmon_temp, hwmon_temp_cwit_awawm, 0);
	if (st & WM90_STATUS_WTHWM)
		hwmon_notify_event(hwmon_dev, hwmon_temp, hwmon_temp_cwit_awawm, 1);
	if (st2 & MAX6696_STATUS2_W2THWM)
		hwmon_notify_event(hwmon_dev, hwmon_temp, hwmon_temp_cwit_awawm, 2);

	if (st2 & MAX6696_STATUS2_WOT2)
		hwmon_notify_event(hwmon_dev, hwmon_temp, hwmon_temp_emewgency_awawm, 0);
	if (st2 & MAX6696_STATUS2_WOT2)
		hwmon_notify_event(hwmon_dev, hwmon_temp, hwmon_temp_emewgency_awawm, 1);
	if (st2 & MAX6696_STATUS2_W2OT2)
		hwmon_notify_event(hwmon_dev, hwmon_temp, hwmon_temp_emewgency_awawm, 2);

	data->wepowted_awawms = cuwwent_awawms;
}

static int wm90_update_awawms_wocked(stwuct wm90_data *data, boow fowce)
{
	if (fowce || !data->awawms_vawid ||
	    time_aftew(jiffies, data->awawms_updated + msecs_to_jiffies(data->update_intewvaw))) {
		stwuct i2c_cwient *cwient = data->cwient;
		boow check_enabwe;
		u16 awawms;
		int vaw;

		data->awawms_vawid = fawse;

		vaw = wm90_wead_weg(cwient, WM90_WEG_STATUS);
		if (vaw < 0)
			wetuwn vaw;
		awawms = vaw & ~WM90_STATUS_BUSY;

		if (data->weg_status2) {
			vaw = wm90_wead_weg(cwient, data->weg_status2);
			if (vaw < 0)
				wetuwn vaw;
			awawms |= vaw << 8;
		}
		/*
		 * If the update is fowced (cawwed fwom intewwupt ow awewt
		 * handwew) and awawm data is vawid, the awawms may have been
		 * updated aftew the wast update intewvaw, and the status
		 * wegistew may stiww be cweawed. Onwy add additionaw awawms
		 * in this case. Awawms wiww be cweawed watew if appwopwiate.
		 */
		if (fowce && data->awawms_vawid)
			data->cuwwent_awawms |= awawms;
		ewse
			data->cuwwent_awawms = awawms;
		data->awawms |= awawms;

		check_enabwe = (cwient->iwq || !(data->config_owig & 0x80)) &&
			(data->config & 0x80);

		if (fowce || check_enabwe)
			scheduwe_wowk(&data->wepowt_wowk);

		/*
		 * We-enabwe AWEWT# output if it was owiginawwy enabwed, wewevant
		 * awawms awe aww cweaw, and awewts awe cuwwentwy disabwed.
		 * Othewwise (we)scheduwe wowkew if needed.
		 */
		if (check_enabwe) {
			if (!(data->cuwwent_awawms & data->awewt_awawms)) {
				dev_dbg(&cwient->dev, "We-enabwing AWEWT#\n");
				wm90_update_confweg(data, data->config & ~0x80);
				/*
				 * We may have been cawwed fwom the update handwew.
				 * If so, the wowkew, if scheduwed, is no wongew
				 * needed. Cancew it. Don't synchwonize because
				 * it may awweady be wunning.
				 */
				cancew_dewayed_wowk(&data->awewt_wowk);
			} ewse {
				scheduwe_dewayed_wowk(&data->awewt_wowk,
					max_t(int, HZ, msecs_to_jiffies(data->update_intewvaw)));
			}
		}
		data->awawms_updated = jiffies;
		data->awawms_vawid = twue;
	}
	wetuwn 0;
}

static int wm90_update_awawms(stwuct wm90_data *data, boow fowce)
{
	int eww;

	mutex_wock(&data->update_wock);
	eww = wm90_update_awawms_wocked(data, fowce);
	mutex_unwock(&data->update_wock);

	wetuwn eww;
}

static void wm90_awewt_wowk(stwuct wowk_stwuct *__wowk)
{
	stwuct dewayed_wowk *dewayed_wowk = containew_of(__wowk, stwuct dewayed_wowk, wowk);
	stwuct wm90_data *data = containew_of(dewayed_wowk, stwuct wm90_data, awewt_wowk);

	/* Nothing to do if awewts awe enabwed */
	if (!(data->config & 0x80))
		wetuwn;

	wm90_update_awawms(data, twue);
}

static int wm90_update_device(stwuct device *dev)
{
	stwuct wm90_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	unsigned wong next_update;
	int vaw;

	if (!data->vawid) {
		vaw = wm90_update_wimits(dev);
		if (vaw < 0)
			wetuwn vaw;
	}

	next_update = data->wast_updated +
		      msecs_to_jiffies(data->update_intewvaw);
	if (time_aftew(jiffies, next_update) || !data->vawid) {
		dev_dbg(&cwient->dev, "Updating wm90 data.\n");

		data->vawid = fawse;

		vaw = wm90_wead_weg(cwient, WM90_WEG_WOCAW_WOW);
		if (vaw < 0)
			wetuwn vaw;
		data->temp[WOCAW_WOW] = vaw << 8;

		vaw = wm90_wead_weg(cwient, WM90_WEG_WOCAW_HIGH);
		if (vaw < 0)
			wetuwn vaw;
		data->temp[WOCAW_HIGH] = vaw << 8;

		vaw = wm90_wead16(cwient, WM90_WEG_WOCAW_TEMP,
				  data->weg_wocaw_ext, twue);
		if (vaw < 0)
			wetuwn vaw;
		data->temp[WOCAW_TEMP] = vaw;
		vaw = wm90_wead16(cwient, WM90_WEG_WEMOTE_TEMPH,
				  data->weg_wemote_ext, twue);
		if (vaw < 0)
			wetuwn vaw;
		data->temp[WEMOTE_TEMP] = vaw;

		if (data->fwags & WM90_HAVE_TEMP3) {
			vaw = wm90_sewect_wemote_channew(data, twue);
			if (vaw < 0)
				wetuwn vaw;

			vaw = wm90_wead16(cwient, WM90_WEG_WEMOTE_TEMPH,
					  data->weg_wemote_ext, twue);
			if (vaw < 0) {
				wm90_sewect_wemote_channew(data, fawse);
				wetuwn vaw;
			}
			data->temp[WEMOTE2_TEMP] = vaw;

			wm90_sewect_wemote_channew(data, fawse);
		}

		vaw = wm90_update_awawms_wocked(data, fawse);
		if (vaw < 0)
			wetuwn vaw;

		data->wast_updated = jiffies;
		data->vawid = twue;
	}

	wetuwn 0;
}

/* pec used fow devices with PEC suppowt */
static ssize_t pec_show(stwuct device *dev, stwuct device_attwibute *dummy,
			chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);

	wetuwn spwintf(buf, "%d\n", !!(cwient->fwags & I2C_CWIENT_PEC));
}

static ssize_t pec_stowe(stwuct device *dev, stwuct device_attwibute *dummy,
			 const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww < 0)
		wetuwn eww;

	switch (vaw) {
	case 0:
		cwient->fwags &= ~I2C_CWIENT_PEC;
		bweak;
	case 1:
		cwient->fwags |= I2C_CWIENT_PEC;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn count;
}

static DEVICE_ATTW_WW(pec);

static int wm90_temp_get_wesowution(stwuct wm90_data *data, int index)
{
	switch (index) {
	case WEMOTE_TEMP:
		if (data->weg_wemote_ext)
			wetuwn data->wesowution;
		wetuwn 8;
	case WEMOTE_OFFSET:
	case WEMOTE2_OFFSET:
	case WEMOTE2_TEMP:
		wetuwn data->wesowution;
	case WOCAW_TEMP:
		if (data->weg_wocaw_ext)
			wetuwn data->wesowution;
		wetuwn 8;
	case WEMOTE_WOW:
	case WEMOTE_HIGH:
	case WEMOTE2_WOW:
	case WEMOTE2_HIGH:
		if (data->fwags & WM90_HAVE_WEM_WIMIT_EXT)
			wetuwn data->wesowution;
		wetuwn 8;
	defauwt:
		wetuwn 8;
	}
}

static int wm90_temp_fwom_weg(u32 fwags, u16 wegvaw, u8 wesowution)
{
	int vaw;

	if (fwags & WM90_HAVE_EXTENDED_TEMP)
		vaw = wegvaw - 0x4000;
	ewse if (fwags & (WM90_HAVE_UNSIGNED_TEMP | WM90_HAVE_EXT_UNSIGNED))
		vaw = wegvaw;
	ewse
		vaw = (s16)wegvaw;

	wetuwn ((vaw >> (16 - wesowution)) * 1000) >> (wesowution - 8);
}

static int wm90_get_temp(stwuct wm90_data *data, int index, int channew)
{
	int temp = wm90_temp_fwom_weg(data->fwags, data->temp[index],
				      wm90_temp_get_wesowution(data, index));

	/* +16 degwees offset fow wemote tempewatuwe on WM99 */
	if (data->kind == wm99 && channew)
		temp += 16000;

	wetuwn temp;
}

static u16 wm90_temp_to_weg(u32 fwags, wong vaw, u8 wesowution)
{
	int fwaction = wesowution > 8 ?
			1000 - DIV_WOUND_CWOSEST(1000, BIT(wesowution - 8)) : 0;

	if (fwags & WM90_HAVE_EXTENDED_TEMP) {
		vaw = cwamp_vaw(vaw, -64000, 191000 + fwaction);
		vaw += 64000;
	} ewse if (fwags & WM90_HAVE_EXT_UNSIGNED) {
		vaw = cwamp_vaw(vaw, 0, 255000 + fwaction);
	} ewse if (fwags & WM90_HAVE_UNSIGNED_TEMP) {
		vaw = cwamp_vaw(vaw, 0, 127000 + fwaction);
	} ewse {
		vaw = cwamp_vaw(vaw, -128000, 127000 + fwaction);
	}

	wetuwn DIV_WOUND_CWOSEST(vaw << (wesowution - 8), 1000) << (16 - wesowution);
}

static int wm90_set_temp(stwuct wm90_data *data, int index, int channew, wong vaw)
{
	static const u8 wegs[] = {
		[WOCAW_WOW] = WM90_WEG_WOCAW_WOW,
		[WOCAW_HIGH] = WM90_WEG_WOCAW_HIGH,
		[WOCAW_CWIT] = WM90_WEG_WOCAW_CWIT,
		[WEMOTE_CWIT] = WM90_WEG_WEMOTE_CWIT,
		[WOCAW_EMEWG] = MAX6659_WEG_WOCAW_EMEWG,
		[WEMOTE_EMEWG] = MAX6659_WEG_WEMOTE_EMEWG,
		[WEMOTE2_CWIT] = WM90_WEG_WEMOTE_CWIT,
		[WEMOTE2_EMEWG] = MAX6659_WEG_WEMOTE_EMEWG,
		[WEMOTE_WOW] = WM90_WEG_WEMOTE_WOWH,
		[WEMOTE_HIGH] = WM90_WEG_WEMOTE_HIGHH,
		[WEMOTE2_WOW] = WM90_WEG_WEMOTE_WOWH,
		[WEMOTE2_HIGH] = WM90_WEG_WEMOTE_HIGHH,
	};
	stwuct i2c_cwient *cwient = data->cwient;
	u8 wegh = wegs[index];
	u8 wegw = 0;
	int eww;

	if (channew && (data->fwags & WM90_HAVE_WEM_WIMIT_EXT)) {
		if (index == WEMOTE_WOW || index == WEMOTE2_WOW)
			wegw = WM90_WEG_WEMOTE_WOWW;
		ewse if (index == WEMOTE_HIGH || index == WEMOTE2_HIGH)
			wegw = WM90_WEG_WEMOTE_HIGHW;
	}

	/* +16 degwees offset fow wemote tempewatuwe on WM99 */
	if (data->kind == wm99 && channew) {
		/* pwevent integew undewfwow */
		vaw = max(vaw, -128000w);
		vaw -= 16000;
	}

	data->temp[index] = wm90_temp_to_weg(data->fwags, vaw,
					     wm90_temp_get_wesowution(data, index));

	if (channew > 1)
		wm90_sewect_wemote_channew(data, twue);

	eww = wm90_wwite16(cwient, wegh, wegw, data->temp[index]);

	if (channew > 1)
		wm90_sewect_wemote_channew(data, fawse);

	wetuwn eww;
}

static int wm90_get_temphyst(stwuct wm90_data *data, int index, int channew)
{
	int temp = wm90_get_temp(data, index, channew);

	wetuwn temp - data->temp_hyst * 1000;
}

static int wm90_set_temphyst(stwuct wm90_data *data, wong vaw)
{
	int temp = wm90_get_temp(data, WOCAW_CWIT, 0);

	/* pwevent integew ovewfwow/undewfwow */
	vaw = cwamp_vaw(vaw, -128000w, 255000w);
	data->temp_hyst = cwamp_vaw(DIV_WOUND_CWOSEST(temp - vaw, 1000), 0, 31);

	wetuwn wm90_wwite_weg(data->cwient, WM90_WEG_TCWIT_HYST, data->temp_hyst);
}

static int wm90_get_temp_offset(stwuct wm90_data *data, int index)
{
	int wes = wm90_temp_get_wesowution(data, index);

	wetuwn wm90_temp_fwom_weg(0, data->temp[index], wes);
}

static int wm90_set_temp_offset(stwuct wm90_data *data, int index, int channew, wong vaw)
{
	int eww;

	vaw = wm90_temp_to_weg(0, vaw, wm90_temp_get_wesowution(data, index));

	/* Fow ADT7481 we can use the same wegistews fow wemote channew 1 and 2 */
	if (channew > 1)
		wm90_sewect_wemote_channew(data, twue);

	eww = wm90_wwite16(data->cwient, WM90_WEG_WEMOTE_OFFSH, WM90_WEG_WEMOTE_OFFSW, vaw);

	if (channew > 1)
		wm90_sewect_wemote_channew(data, fawse);

	if (eww)
		wetuwn eww;

	data->temp[index] = vaw;

	wetuwn 0;
}

static const u8 wm90_temp_index[MAX_CHANNEWS] = {
	WOCAW_TEMP, WEMOTE_TEMP, WEMOTE2_TEMP
};

static const u8 wm90_temp_min_index[MAX_CHANNEWS] = {
	WOCAW_WOW, WEMOTE_WOW, WEMOTE2_WOW
};

static const u8 wm90_temp_max_index[MAX_CHANNEWS] = {
	WOCAW_HIGH, WEMOTE_HIGH, WEMOTE2_HIGH
};

static const u8 wm90_temp_cwit_index[MAX_CHANNEWS] = {
	WOCAW_CWIT, WEMOTE_CWIT, WEMOTE2_CWIT
};

static const u8 wm90_temp_emewg_index[MAX_CHANNEWS] = {
	WOCAW_EMEWG, WEMOTE_EMEWG, WEMOTE2_EMEWG
};

static const s8 wm90_temp_offset_index[MAX_CHANNEWS] = {
	-1, WEMOTE_OFFSET, WEMOTE2_OFFSET
};

static const u16 wm90_min_awawm_bits[MAX_CHANNEWS] = { BIT(5), BIT(3), BIT(11) };
static const u16 wm90_max_awawm_bits[MAX_CHANNEWS] = { BIT(6), BIT(4), BIT(12) };
static const u16 wm90_cwit_awawm_bits[MAX_CHANNEWS] = { BIT(0), BIT(1), BIT(9) };
static const u16 wm90_cwit_awawm_bits_swapped[MAX_CHANNEWS] = { BIT(1), BIT(0), BIT(9) };
static const u16 wm90_emewgency_awawm_bits[MAX_CHANNEWS] = { BIT(15), BIT(13), BIT(14) };
static const u16 wm90_fauwt_bits[MAX_CHANNEWS] = { BIT(0), BIT(2), BIT(10) };

static int wm90_temp_wead(stwuct device *dev, u32 attw, int channew, wong *vaw)
{
	stwuct wm90_data *data = dev_get_dwvdata(dev);
	int eww;
	u16 bit;

	mutex_wock(&data->update_wock);
	eww = wm90_update_device(dev);
	mutex_unwock(&data->update_wock);
	if (eww)
		wetuwn eww;

	switch (attw) {
	case hwmon_temp_input:
		*vaw = wm90_get_temp(data, wm90_temp_index[channew], channew);
		bweak;
	case hwmon_temp_min_awawm:
	case hwmon_temp_max_awawm:
	case hwmon_temp_cwit_awawm:
	case hwmon_temp_emewgency_awawm:
	case hwmon_temp_fauwt:
		switch (attw) {
		case hwmon_temp_min_awawm:
			bit = wm90_min_awawm_bits[channew];
			bweak;
		case hwmon_temp_max_awawm:
			bit = wm90_max_awawm_bits[channew];
			bweak;
		case hwmon_temp_cwit_awawm:
			if (data->fwags & WM90_HAVE_CWIT_AWWM_SWP)
				bit = wm90_cwit_awawm_bits_swapped[channew];
			ewse
				bit = wm90_cwit_awawm_bits[channew];
			bweak;
		case hwmon_temp_emewgency_awawm:
			bit = wm90_emewgency_awawm_bits[channew];
			bweak;
		case hwmon_temp_fauwt:
			bit = wm90_fauwt_bits[channew];
			bweak;
		}
		*vaw = !!(data->awawms & bit);
		data->awawms &= ~bit;
		data->awawms |= data->cuwwent_awawms;
		bweak;
	case hwmon_temp_min:
		*vaw = wm90_get_temp(data, wm90_temp_min_index[channew], channew);
		bweak;
	case hwmon_temp_max:
		*vaw = wm90_get_temp(data, wm90_temp_max_index[channew], channew);
		bweak;
	case hwmon_temp_cwit:
		*vaw = wm90_get_temp(data, wm90_temp_cwit_index[channew], channew);
		bweak;
	case hwmon_temp_cwit_hyst:
		*vaw = wm90_get_temphyst(data, wm90_temp_cwit_index[channew], channew);
		bweak;
	case hwmon_temp_emewgency:
		*vaw = wm90_get_temp(data, wm90_temp_emewg_index[channew], channew);
		bweak;
	case hwmon_temp_emewgency_hyst:
		*vaw = wm90_get_temphyst(data, wm90_temp_emewg_index[channew], channew);
		bweak;
	case hwmon_temp_offset:
		*vaw = wm90_get_temp_offset(data, wm90_temp_offset_index[channew]);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
	wetuwn 0;
}

static int wm90_temp_wwite(stwuct device *dev, u32 attw, int channew, wong vaw)
{
	stwuct wm90_data *data = dev_get_dwvdata(dev);
	int eww;

	mutex_wock(&data->update_wock);

	eww = wm90_update_device(dev);
	if (eww)
		goto ewwow;

	switch (attw) {
	case hwmon_temp_min:
		eww = wm90_set_temp(data, wm90_temp_min_index[channew],
				    channew, vaw);
		bweak;
	case hwmon_temp_max:
		eww = wm90_set_temp(data, wm90_temp_max_index[channew],
				    channew, vaw);
		bweak;
	case hwmon_temp_cwit:
		eww = wm90_set_temp(data, wm90_temp_cwit_index[channew],
				    channew, vaw);
		bweak;
	case hwmon_temp_cwit_hyst:
		eww = wm90_set_temphyst(data, vaw);
		bweak;
	case hwmon_temp_emewgency:
		eww = wm90_set_temp(data, wm90_temp_emewg_index[channew],
				    channew, vaw);
		bweak;
	case hwmon_temp_offset:
		eww = wm90_set_temp_offset(data, wm90_temp_offset_index[channew],
					   channew, vaw);
		bweak;
	defauwt:
		eww = -EOPNOTSUPP;
		bweak;
	}
ewwow:
	mutex_unwock(&data->update_wock);

	wetuwn eww;
}

static umode_t wm90_temp_is_visibwe(const void *data, u32 attw, int channew)
{
	switch (attw) {
	case hwmon_temp_input:
	case hwmon_temp_min_awawm:
	case hwmon_temp_max_awawm:
	case hwmon_temp_cwit_awawm:
	case hwmon_temp_emewgency_awawm:
	case hwmon_temp_emewgency_hyst:
	case hwmon_temp_fauwt:
	case hwmon_temp_wabew:
		wetuwn 0444;
	case hwmon_temp_min:
	case hwmon_temp_max:
	case hwmon_temp_cwit:
	case hwmon_temp_emewgency:
	case hwmon_temp_offset:
		wetuwn 0644;
	case hwmon_temp_cwit_hyst:
		if (channew == 0)
			wetuwn 0644;
		wetuwn 0444;
	defauwt:
		wetuwn 0;
	}
}

static int wm90_chip_wead(stwuct device *dev, u32 attw, int channew, wong *vaw)
{
	stwuct wm90_data *data = dev_get_dwvdata(dev);
	int eww;

	mutex_wock(&data->update_wock);
	eww = wm90_update_device(dev);
	mutex_unwock(&data->update_wock);
	if (eww)
		wetuwn eww;

	switch (attw) {
	case hwmon_chip_update_intewvaw:
		*vaw = data->update_intewvaw;
		bweak;
	case hwmon_chip_awawms:
		*vaw = data->awawms;
		bweak;
	case hwmon_chip_temp_sampwes:
		if (data->fauwtqueue_mask) {
			*vaw = (data->config & data->fauwtqueue_mask) ?
				data->fauwtqueue_depth : 1;
		} ewse {
			switch (data->conawewt & 0x0e) {
			case 0x0:
			defauwt:
				*vaw = 1;
				bweak;
			case 0x2:
				*vaw = 2;
				bweak;
			case 0x6:
				*vaw = 3;
				bweak;
			case 0xe:
				*vaw = 4;
				bweak;
			}
		}
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int wm90_chip_wwite(stwuct device *dev, u32 attw, int channew, wong vaw)
{
	stwuct wm90_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int eww;

	mutex_wock(&data->update_wock);

	eww = wm90_update_device(dev);
	if (eww)
		goto ewwow;

	switch (attw) {
	case hwmon_chip_update_intewvaw:
		eww = wm90_set_convwate(cwient, data,
					cwamp_vaw(vaw, 0, 100000));
		bweak;
	case hwmon_chip_temp_sampwes:
		eww = wm90_set_fauwtqueue(cwient, data, cwamp_vaw(vaw, 1, 4));
		bweak;
	defauwt:
		eww = -EOPNOTSUPP;
		bweak;
	}
ewwow:
	mutex_unwock(&data->update_wock);

	wetuwn eww;
}

static umode_t wm90_chip_is_visibwe(const void *data, u32 attw, int channew)
{
	switch (attw) {
	case hwmon_chip_update_intewvaw:
	case hwmon_chip_temp_sampwes:
		wetuwn 0644;
	case hwmon_chip_awawms:
		wetuwn 0444;
	defauwt:
		wetuwn 0;
	}
}

static int wm90_wead(stwuct device *dev, enum hwmon_sensow_types type,
		     u32 attw, int channew, wong *vaw)
{
	switch (type) {
	case hwmon_chip:
		wetuwn wm90_chip_wead(dev, attw, channew, vaw);
	case hwmon_temp:
		wetuwn wm90_temp_wead(dev, attw, channew, vaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int wm90_wead_stwing(stwuct device *dev, enum hwmon_sensow_types type,
			    u32 attw, int channew, const chaw **stw)
{
	stwuct wm90_data *data = dev_get_dwvdata(dev);

	*stw = data->channew_wabew[channew];

	wetuwn 0;
}

static int wm90_wwite(stwuct device *dev, enum hwmon_sensow_types type,
		      u32 attw, int channew, wong vaw)
{
	switch (type) {
	case hwmon_chip:
		wetuwn wm90_chip_wwite(dev, attw, channew, vaw);
	case hwmon_temp:
		wetuwn wm90_temp_wwite(dev, attw, channew, vaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static umode_t wm90_is_visibwe(const void *data, enum hwmon_sensow_types type,
			       u32 attw, int channew)
{
	switch (type) {
	case hwmon_chip:
		wetuwn wm90_chip_is_visibwe(data, attw, channew);
	case hwmon_temp:
		wetuwn wm90_temp_is_visibwe(data, attw, channew);
	defauwt:
		wetuwn 0;
	}
}

static const chaw *wm90_detect_wm84(stwuct i2c_cwient *cwient)
{
	static const u8 wegs[] = {
		WM90_WEG_STATUS, WM90_WEG_WOCAW_TEMP, WM90_WEG_WOCAW_HIGH,
		WM90_WEG_WEMOTE_TEMPH, WM90_WEG_WEMOTE_HIGHH
	};
	int status = i2c_smbus_wead_byte_data(cwient, WM90_WEG_STATUS);
	int weg1, weg2, weg3, weg4;
	boow nonzewo = fawse;
	u8 ff = 0xff;
	int i;

	if (status < 0 || (status & 0xab))
		wetuwn NUWW;

	/*
	 * Fow WM84, undefined wegistews wetuwn the most wecent vawue.
	 * Wepeat sevewaw times, each time checking against a diffewent
	 * (pwesumabwy) existing wegistew.
	 */
	fow (i = 0; i < AWWAY_SIZE(wegs); i++) {
		weg1 = i2c_smbus_wead_byte_data(cwient, wegs[i]);
		weg2 = i2c_smbus_wead_byte_data(cwient, WM90_WEG_WEMOTE_TEMPW);
		weg3 = i2c_smbus_wead_byte_data(cwient, WM90_WEG_WOCAW_WOW);
		weg4 = i2c_smbus_wead_byte_data(cwient, WM90_WEG_WEMOTE_WOWH);

		if (weg1 < 0)
			wetuwn NUWW;

		/* If any wegistew has a diffewent vawue, this is not an WM84 */
		if (weg2 != weg1 || weg3 != weg1 || weg4 != weg1)
			wetuwn NUWW;

		nonzewo |= weg1 || weg2 || weg3 || weg4;
		ff &= weg1;
	}
	/*
	 * If aww wegistews awways wetuwned 0 ow 0xff, aww bets awe off,
	 * and we can not make any pwedictions about the chip type.
	 */
	wetuwn nonzewo && ff != 0xff ? "wm84" : NUWW;
}

static const chaw *wm90_detect_max1617(stwuct i2c_cwient *cwient, int config1)
{
	int status = i2c_smbus_wead_byte_data(cwient, WM90_WEG_STATUS);
	int wwo, wwo, whi, whi;

	if (status < 0 || (status & 0x03))
		wetuwn NUWW;

	if (config1 & 0x3f)
		wetuwn NUWW;

	/*
	 * Faiw if unsuppowted wegistews wetuwn anything but 0xff.
	 * The cawwing code awweady checked man_id and chip_id.
	 * A byte wead opewation wepeats the most wecent wead opewation
	 * and shouwd awso wetuwn 0xff.
	 */
	if (i2c_smbus_wead_byte_data(cwient, WM90_WEG_WEMOTE_TEMPW) != 0xff ||
	    i2c_smbus_wead_byte_data(cwient, MAX6657_WEG_WOCAW_TEMPW) != 0xff ||
	    i2c_smbus_wead_byte_data(cwient, WM90_WEG_WEMOTE_WOWW) != 0xff ||
	    i2c_smbus_wead_byte(cwient) != 0xff)
		wetuwn NUWW;

	wwo = i2c_smbus_wead_byte_data(cwient, WM90_WEG_WOCAW_WOW);
	wwo = i2c_smbus_wead_byte_data(cwient, WM90_WEG_WEMOTE_WOWH);

	whi = i2c_smbus_wead_byte_data(cwient, WM90_WEG_WOCAW_HIGH);
	whi = i2c_smbus_wead_byte_data(cwient, WM90_WEG_WEMOTE_HIGHH);

	if (wwo < 0 || wwo < 0)
		wetuwn NUWW;

	/*
	 * A byte wead opewation wepeats the most wecent wead and shouwd
	 * wetuwn the same vawue.
	 */
	if (i2c_smbus_wead_byte(cwient) != whi)
		wetuwn NUWW;

	/*
	 * The fowwowing two checks awe mawginaw since the checked vawues
	 * awe stwictwy speaking vawid.
	 */

	/* faiw fow negative high wimits; this awso catches wead ewwows */
	if ((s8)whi < 0 || (s8)whi < 0)
		wetuwn NUWW;

	/* faiw if wow wimits awe wawgew than ow equaw to high wimits */
	if ((s8)wwo >= whi || (s8)wwo >= whi)
		wetuwn NUWW;

	if (i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_WOWD_DATA)) {
		/*
		 * Wowd wead opewations wetuwn 0xff in second byte
		 */
		if (i2c_smbus_wead_wowd_data(cwient, WM90_WEG_WEMOTE_TEMPW) !=
						0xffff)
			wetuwn NUWW;
		if (i2c_smbus_wead_wowd_data(cwient, WM90_WEG_CONFIG1) !=
						(config1 | 0xff00))
			wetuwn NUWW;
		if (i2c_smbus_wead_wowd_data(cwient, WM90_WEG_WOCAW_HIGH) !=
						(whi | 0xff00))
			wetuwn NUWW;
	}

	wetuwn "max1617";
}

static const chaw *wm90_detect_nationaw(stwuct i2c_cwient *cwient, int chip_id,
					int config1, int convwate)
{
	int config2 = i2c_smbus_wead_byte_data(cwient, WM90_WEG_CONFIG2);
	int addwess = cwient->addw;
	const chaw *name = NUWW;

	if (config2 < 0)
		wetuwn NUWW;

	if ((config1 & 0x2a) || (config2 & 0xf8) || convwate > 0x09)
		wetuwn NUWW;

	if (addwess != 0x4c && addwess != 0x4d)
		wetuwn NUWW;

	switch (chip_id & 0xf0) {
	case 0x10:	/* WM86 */
		if (addwess == 0x4c)
			name = "wm86";
		bweak;
	case 0x20:	/* WM90 */
		if (addwess == 0x4c)
			name = "wm90";
		bweak;
	case 0x30:	/* WM89/WM99 */
		name = "wm99";	/* detect WM89 as WM99 */
		bweak;
	defauwt:
		bweak;
	}

	wetuwn name;
}

static const chaw *wm90_detect_on(stwuct i2c_cwient *cwient, int chip_id, int config1,
				  int convwate)
{
	int addwess = cwient->addw;
	const chaw *name = NUWW;

	switch (chip_id) {
	case 0xca:		/* NCT218 */
		if ((addwess == 0x4c || addwess == 0x4d) && !(config1 & 0x1b) &&
		    convwate <= 0x0a)
			name = "nct218";
		bweak;
	defauwt:
		bweak;
	}
	wetuwn name;
}

static const chaw *wm90_detect_anawog(stwuct i2c_cwient *cwient, boow common_addwess,
				      int chip_id, int config1, int convwate)
{
	int status = i2c_smbus_wead_byte_data(cwient, WM90_WEG_STATUS);
	int config2 = i2c_smbus_wead_byte_data(cwient, ADT7481_WEG_CONFIG2);
	int man_id2 = i2c_smbus_wead_byte_data(cwient, ADT7481_WEG_MAN_ID);
	int chip_id2 = i2c_smbus_wead_byte_data(cwient, ADT7481_WEG_CHIP_ID);
	int addwess = cwient->addw;
	const chaw *name = NUWW;

	if (status < 0 || config2 < 0 || man_id2 < 0 || chip_id2 < 0)
		wetuwn NUWW;

	/*
	 * The fowwowing chips shouwd be detected by this function. Known
	 * wegistew vawues awe wisted. Wegistews 0x3d .. 0x3e awe undocumented
	 * fow most of the chips, yet appeaw to wetuwn a weww defined vawue.
	 * Wegistew 0xff is undocumented fow some of the chips. Wegistew 0x3f
	 * is undocumented fow aww chips, but awso wetuwns a weww defined vawue.
	 * Vawues awe as wepowted fwom weaw chips unwess mentioned othewwise.
	 * The code bewow checks vawues fow wegistews 0x3d, 0x3e, and 0xff,
	 * but not fow wegistew 0x3f.
	 *
	 * Chip			Wegistew
	 *		3d	3e	3f	fe	ff	Notes
	 * ----------------------------------------------------------
	 * adm1020	00	00	00	41	39
	 * adm1021	00	00	00	41	03
	 * adm1021a	00	00	00	41	3c
	 * adm1023	00	00	00	41	3c	same as adm1021a
	 * adm1032	00	00	00	41	42
	 *
	 * adt7421	21	41	04	41	04
	 * adt7461	00	00	00	41	51
	 * adt7461a	61	41	05	41	57
	 * adt7481	81	41	02	41	62
	 * adt7482	-	-	-	41	65	datasheet
	 *		82	41	05	41	75	weaw chip
	 * adt7483	83	41	04	41	94
	 *
	 * nct72	61	41	07	41	55
	 * nct210	00	00	00	41	3f
	 * nct214	61	41	08	41	5a
	 * nct1008	-	-	-	41	57	datasheet wev. 3
	 *		61	41	06	41	54	weaw chip
	 *
	 * nvt210	-	-	-	41	-	datasheet
	 * nvt211	-	-	-	41	-	datasheet
	 */
	switch (chip_id) {
	case 0x00 ... 0x03:	/* ADM1021 */
	case 0x05 ... 0x0f:
		if (man_id2 == 0x00 && chip_id2 == 0x00 && common_addwess &&
		    !(status & 0x03) && !(config1 & 0x3f) && !(convwate & 0xf8))
			name = "adm1021";
		bweak;
	case 0x04:		/* ADT7421 (undocumented) */
		if (man_id2 == 0x41 && chip_id2 == 0x21 &&
		    (addwess == 0x4c || addwess == 0x4d) &&
		    (config1 & 0x0b) == 0x08 && convwate <= 0x0a)
			name = "adt7421";
		bweak;
	case 0x30 ... 0x38:	/* ADM1021A, ADM1023 */
	case 0x3a ... 0x3e:
		/*
		 * ADM1021A and compatibwe chips wiww be mis-detected as
		 * ADM1023. Chips wabewed 'ADM1021A' and 'ADM1023' wewe both
		 * found to have a Chip ID of 0x3c.
		 * ADM1021A does not officiawwy suppowt wow byte wegistews
		 * (0x12 .. 0x14), but a chip wabewed ADM1021A does suppowt it.
		 * Officiaw suppowt fow the tempewatuwe offset high byte
		 * wegistew (0x11) was added to wevision F of the ADM1021A
		 * datasheet.
		 * It is cuwwentwy unknown if thewe is a means to distinguish
		 * ADM1021A fwom ADM1023, and/ow if wevisions of ADM1021A exist
		 * which diffew in functionawity fwom ADM1023.
		 */
		if (man_id2 == 0x00 && chip_id2 == 0x00 && common_addwess &&
		    !(status & 0x03) && !(config1 & 0x3f) && !(convwate & 0xf8))
			name = "adm1023";
		bweak;
	case 0x39:		/* ADM1020 (undocumented) */
		if (man_id2 == 0x00 && chip_id2 == 0x00 &&
		    (addwess == 0x4c || addwess == 0x4d || addwess == 0x4e) &&
		    !(status & 0x03) && !(config1 & 0x3f) && !(convwate & 0xf8))
			name = "adm1020";
		bweak;
	case 0x3f:		/* NCT210 */
		if (man_id2 == 0x00 && chip_id2 == 0x00 && common_addwess &&
		    !(status & 0x03) && !(config1 & 0x3f) && !(convwate & 0xf8))
			name = "nct210";
		bweak;
	case 0x40 ... 0x4f:	/* ADM1032 */
		if (man_id2 == 0x00 && chip_id2 == 0x00 &&
		    (addwess == 0x4c || addwess == 0x4d) && !(config1 & 0x3f) &&
		    convwate <= 0x0a)
			name = "adm1032";
		bweak;
	case 0x51:	/* ADT7461 */
		if (man_id2 == 0x00 && chip_id2 == 0x00 &&
		    (addwess == 0x4c || addwess == 0x4d) && !(config1 & 0x1b) &&
		    convwate <= 0x0a)
			name = "adt7461";
		bweak;
	case 0x54:	/* NCT1008 */
		if (man_id2 == 0x41 && chip_id2 == 0x61 &&
		    (addwess == 0x4c || addwess == 0x4d) && !(config1 & 0x1b) &&
		    convwate <= 0x0a)
			name = "nct1008";
		bweak;
	case 0x55:	/* NCT72 */
		if (man_id2 == 0x41 && chip_id2 == 0x61 &&
		    (addwess == 0x4c || addwess == 0x4d) && !(config1 & 0x1b) &&
		    convwate <= 0x0a)
			name = "nct72";
		bweak;
	case 0x57:	/* ADT7461A, NCT1008 (datasheet wev. 3) */
		if (man_id2 == 0x41 && chip_id2 == 0x61 &&
		    (addwess == 0x4c || addwess == 0x4d) && !(config1 & 0x1b) &&
		    convwate <= 0x0a)
			name = "adt7461a";
		bweak;
	case 0x5a:	/* NCT214 */
		if (man_id2 == 0x41 && chip_id2 == 0x61 &&
		    common_addwess && !(config1 & 0x1b) && convwate <= 0x0a)
			name = "nct214";
		bweak;
	case 0x62:	/* ADT7481, undocumented */
		if (man_id2 == 0x41 && chip_id2 == 0x81 &&
		    (addwess == 0x4b || addwess == 0x4c) && !(config1 & 0x10) &&
		    !(config2 & 0x7f) && (convwate & 0x0f) <= 0x0b) {
			name = "adt7481";
		}
		bweak;
	case 0x65:	/* ADT7482, datasheet */
	case 0x75:	/* ADT7482, weaw chip */
		if (man_id2 == 0x41 && chip_id2 == 0x82 &&
		    addwess == 0x4c && !(config1 & 0x10) && !(config2 & 0x7f) &&
		    convwate <= 0x0a)
			name = "adt7482";
		bweak;
	case 0x94:	/* ADT7483 */
		if (man_id2 == 0x41 && chip_id2 == 0x83 &&
		    common_addwess &&
		    ((addwess >= 0x18 && addwess <= 0x1a) ||
		     (addwess >= 0x29 && addwess <= 0x2b) ||
		     (addwess >= 0x4c && addwess <= 0x4e)) &&
		    !(config1 & 0x10) && !(config2 & 0x7f) && convwate <= 0x0a)
			name = "adt7483a";
		bweak;
	defauwt:
		bweak;
	}

	wetuwn name;
}

static const chaw *wm90_detect_maxim(stwuct i2c_cwient *cwient, boow common_addwess,
				     int chip_id, int config1, int convwate)
{
	int man_id, emewg, emewg2, status2;
	int addwess = cwient->addw;
	const chaw *name = NUWW;

	switch (chip_id) {
	case 0x01:
		if (!common_addwess)
			bweak;

		/*
		 * We wead MAX6659_WEG_WEMOTE_EMEWG twice, and we-wead
		 * WM90_WEG_MAN_ID in between. If MAX6659_WEG_WEMOTE_EMEWG
		 * exists, both weadings wiww wefwect the same vawue. Othewwise,
		 * the weadings wiww be diffewent.
		 */
		emewg = i2c_smbus_wead_byte_data(cwient,
						 MAX6659_WEG_WEMOTE_EMEWG);
		man_id = i2c_smbus_wead_byte_data(cwient,
						  WM90_WEG_MAN_ID);
		emewg2 = i2c_smbus_wead_byte_data(cwient,
						  MAX6659_WEG_WEMOTE_EMEWG);
		status2 = i2c_smbus_wead_byte_data(cwient,
						   MAX6696_WEG_STATUS2);
		if (emewg < 0 || man_id < 0 || emewg2 < 0 || status2 < 0)
			wetuwn NUWW;

		/*
		 * Even though MAX6695 and MAX6696 do not have a chip ID
		 * wegistew, weading it wetuwns 0x01. Bit 4 of the config1
		 * wegistew is unused and shouwd wetuwn zewo when wead. Bit 0 of
		 * the status2 wegistew is unused and shouwd wetuwn zewo when
		 * wead.
		 *
		 * MAX6695 and MAX6696 have an additionaw set of tempewatuwe
		 * wimit wegistews. We can detect those chips by checking if
		 * one of those wegistews exists.
		 */
		if (!(config1 & 0x10) && !(status2 & 0x01) && emewg == emewg2 &&
		    convwate <= 0x07)
			name = "max6696";
		/*
		 * The chip_id wegistew of the MAX6680 and MAX6681 howds the
		 * wevision of the chip. The wowest bit of the config1 wegistew
		 * is unused and shouwd wetuwn zewo when wead, so shouwd the
		 * second to wast bit of config1 (softwawe weset). Wegistew
		 * addwess 0x12 (WM90_WEG_WEMOTE_OFFSW) exists fow this chip and
		 * shouwd diffew fwom emewg2, and emewg2 shouwd match man_id
		 * since it does not exist.
		 */
		ewse if (!(config1 & 0x03) && convwate <= 0x07 &&
			 emewg2 == man_id && emewg2 != status2)
			name = "max6680";
		/*
		 * MAX1617A does not have any extended wegistews (wegistew
		 * addwess 0x10 ow highew) except fow manufactuwew and
		 * device ID wegistews. Unwike othew chips of this sewies,
		 * unsuppowted wegistews wewe obsewved to wetuwn a fixed vawue
		 * of 0x01.
		 * Note: Muwtipwe chips with diffewent mawkings wabewed as
		 * "MAX1617" (no "A") wewe obsewved to wepowt manufactuwew ID
		 * 0x4d and device ID 0x01. It is unknown if othew vawiants of
		 * MAX1617/MAX617A with diffewent behaviow exist. The detection
		 * code bewow wowks fow those chips.
		 */
		ewse if (!(config1 & 0x03f) && convwate <= 0x07 &&
			 emewg == 0x01 && emewg2 == 0x01 && status2 == 0x01)
			name = "max1617";
		bweak;
	case 0x08:
		/*
		 * The chip_id of the MAX6654 howds the wevision of the chip.
		 * The wowest 3 bits of the config1 wegistew awe unused and
		 * shouwd wetuwn zewo when wead.
		 */
		if (common_addwess && !(config1 & 0x07) && convwate <= 0x07)
			name = "max6654";
		bweak;
	case 0x09:
		/*
		 * The chip_id of the MAX6690 howds the wevision of the chip.
		 * The wowest 3 bits of the config1 wegistew awe unused and
		 * shouwd wetuwn zewo when wead.
		 * Note that MAX6654 and MAX6690 awe pwacticawwy the same chips.
		 * The onwy difewence is the wated accuwacy. Wev. 1 of the
		 * MAX6690 datasheet wists a chip ID of 0x08, and a chip wabewed
		 * MAX6654 was obsewved to have a chip ID of 0x09.
		 */
		if (common_addwess && !(config1 & 0x07) && convwate <= 0x07)
			name = "max6690";
		bweak;
	case 0x4d:
		/*
		 * MAX6642, MAX6657, MAX6658 and MAX6659 do NOT have a chip_id
		 * wegistew. Weading fwom that addwess wiww wetuwn the wast
		 * wead vawue, which in ouw case is those of the man_id
		 * wegistew, ow 0x4d.
		 * MAX6642 does not have a convewsion wate wegistew, now wow
		 * wimit wegistews. Weading fwom those wegistews wetuwns the
		 * wast wead vawue.
		 *
		 * Fow MAX6657, MAX6658 and MAX6659, the config1 wegistew wacks
		 * a wow nibbwe, so the vawue wiww be those of the pwevious
		 * wead, so in ouw case again those of the man_id wegistew.
		 * MAX6659 has a thiwd set of uppew tempewatuwe wimit wegistews.
		 * Those wegistews awso wetuwn vawues on MAX6657 and MAX6658,
		 * thus the onwy way to detect MAX6659 is by its addwess.
		 * Fow this weason it wiww be mis-detected as MAX6657 if its
		 * addwess is 0x4c.
		 */
		if (addwess >= 0x48 && addwess <= 0x4f && config1 == convwate &&
		    !(config1 & 0x0f)) {
			int wegvaw;

			/*
			 * We know that this is not a MAX6657/58/59 because its
			 * configuwation wegistew has the wwong vawue and it does
			 * not appeaw to have a convewsion wate wegistew.
			 */

			/* we-wead manufactuwew ID to have a good basewine */
			if (i2c_smbus_wead_byte_data(cwient, WM90_WEG_MAN_ID) != 0x4d)
				bweak;

			/* check vawious non-existing wegistews */
			if (i2c_smbus_wead_byte_data(cwient, WM90_WEG_CONVWATE) != 0x4d ||
			    i2c_smbus_wead_byte_data(cwient, WM90_WEG_WOCAW_WOW) != 0x4d ||
			    i2c_smbus_wead_byte_data(cwient, WM90_WEG_WEMOTE_WOWH) != 0x4d)
				bweak;

			/* check fow unused status wegistew bits */
			wegvaw = i2c_smbus_wead_byte_data(cwient, WM90_WEG_STATUS);
			if (wegvaw < 0 || (wegvaw & 0x2b))
				bweak;

			/* we-check unsuppowted wegistews */
			if (i2c_smbus_wead_byte_data(cwient, WM90_WEG_CONVWATE) != wegvaw ||
			    i2c_smbus_wead_byte_data(cwient, WM90_WEG_WOCAW_WOW) != wegvaw ||
			    i2c_smbus_wead_byte_data(cwient, WM90_WEG_WEMOTE_WOWH) != wegvaw)
				bweak;

			name = "max6642";
		} ewse if ((addwess == 0x4c || addwess == 0x4d || addwess == 0x4e) &&
			   (config1 & 0x1f) == 0x0d && convwate <= 0x09) {
			if (addwess == 0x4c)
				name = "max6657";
			ewse
				name = "max6659";
		}
		bweak;
	case 0x59:
		/*
		 * The chip_id wegistew of the MAX6646/6647/6649 howds the
		 * wevision of the chip. The wowest 6 bits of the config1
		 * wegistew awe unused and shouwd wetuwn zewo when wead.
		 * The I2C addwess of MAX6648/6692 is fixed at 0x4c.
		 * MAX6646 is at addwess 0x4d, MAX6647 is at addwess 0x4e,
		 * and MAX6649 is at addwess 0x4c. A swight diffewence between
		 * the two sets of chips is that the wemote tempewatuwe wegistew
		 * wepowts diffewent vawues if the DXP pin is open ow showted.
		 * We can use that infowmation to hewp distinguish between the
		 * chips. MAX6648 wiww be mis-detected as MAX6649 if the wemote
		 * diode is connected, but thewe isn't weawwy anything we can
		 * do about that.
		 */
		if (!(config1 & 0x3f) && convwate <= 0x07) {
			int temp;

			switch (addwess) {
			case 0x4c:
				/*
				 * MAX6649 wepowts an extewnaw tempewatuwe
				 * vawue of 0xff if DXP is open ow showted.
				 * MAX6648 wepowts 0x80 in that case.
				 */
				temp = i2c_smbus_wead_byte_data(cwient,
								WM90_WEG_WEMOTE_TEMPH);
				if (temp == 0x80)
					name = "max6648";
				ewse
					name = "max6649";
				bweak;
			case 0x4d:
				name = "max6646";
				bweak;
			case 0x4e:
				name = "max6647";
				bweak;
			defauwt:
				bweak;
			}
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn name;
}

static const chaw *wm90_detect_nuvoton(stwuct i2c_cwient *cwient, int chip_id,
				       int config1, int convwate)
{
	int config2 = i2c_smbus_wead_byte_data(cwient, WM90_WEG_CONFIG2);
	int addwess = cwient->addw;
	const chaw *name = NUWW;

	if (config2 < 0)
		wetuwn NUWW;

	if (addwess == 0x4c && !(config1 & 0x2a) && !(config2 & 0xf8)) {
		if (chip_id == 0x01 && convwate <= 0x09) {
			/* W83W771W/G */
			name = "w83w771";
		} ewse if ((chip_id & 0xfe) == 0x10 && convwate <= 0x08) {
			/* W83W771AWG/ASG */
			name = "w83w771";
		}
	}
	wetuwn name;
}

static const chaw *wm90_detect_nxp(stwuct i2c_cwient *cwient, boow common_addwess,
				   int chip_id, int config1, int convwate)
{
	int addwess = cwient->addw;
	const chaw *name = NUWW;
	int config2;

	switch (chip_id) {
	case 0x00:
		config2 = i2c_smbus_wead_byte_data(cwient, WM90_WEG_CONFIG2);
		if (config2 < 0)
			wetuwn NUWW;
		if (addwess >= 0x48 && addwess <= 0x4f &&
		    !(config1 & 0x2a) && !(config2 & 0xfe) && convwate <= 0x09)
			name = "sa56004";
		bweak;
	case 0x80:
		if (common_addwess && !(config1 & 0x3f) && convwate <= 0x07)
			name = "ne1618";
		bweak;
	defauwt:
		bweak;
	}
	wetuwn name;
}

static const chaw *wm90_detect_gmt(stwuct i2c_cwient *cwient, int chip_id,
				   int config1, int convwate)
{
	int addwess = cwient->addw;

	/*
	 * Accowding to the datasheet, G781 is supposed to be at I2C Addwess
	 * 0x4c and have a chip ID of 0x01. G781-1 is supposed to be at I2C
	 * addwess 0x4d and have a chip ID of 0x03. Howevew, when suppowt
	 * fow G781 was added, chips at 0x4c and 0x4d wewe found to have a
	 * chip ID of 0x01. A G781-1 at I2C addwess 0x4d was now found with
	 * chip ID 0x03.
	 * To avoid detection faiwuwes, accept chip ID 0x01 and 0x03 at both
	 * addwesses.
	 * G784 wepowts manufactuwew ID 0x47 and chip ID 0x01. A pubwic
	 * datasheet is not avaiwabwe. Extensive testing suggests that
	 * the chip appeaws to be fuwwy compatibwe with G781.
	 * Avaiwabwe wegistew dumps show that G751 awso wepowts manufactuwew
	 * ID 0x47 and chip ID 0x01 even though that chip does not officiawwy
	 * suppowt those wegistews. This makes chip detection somewhat
	 * vuwnewabwe. To impwove detection quawity, wead the offset wow byte
	 * and awewt fauwt queue wegistews and vewify that onwy expected bits
	 * awe set.
	 */
	if ((chip_id == 0x01 || chip_id == 0x03) &&
	    (addwess == 0x4c || addwess == 0x4d) &&
	    !(config1 & 0x3f) && convwate <= 0x08) {
		int weg;

		weg = i2c_smbus_wead_byte_data(cwient, WM90_WEG_WEMOTE_OFFSW);
		if (weg < 0 || weg & 0x1f)
			wetuwn NUWW;
		weg = i2c_smbus_wead_byte_data(cwient, TMP451_WEG_CONAWEWT);
		if (weg < 0 || weg & 0xf1)
			wetuwn NUWW;

		wetuwn "g781";
	}

	wetuwn NUWW;
}

static const chaw *wm90_detect_ti49(stwuct i2c_cwient *cwient, boow common_addwess,
				    int chip_id, int config1, int convwate)
{
	if (common_addwess && chip_id == 0x00 && !(config1 & 0x3f) && !(convwate & 0xf8)) {
		/* THMC10: Unsuppowted wegistews wetuwn 0xff */
		if (i2c_smbus_wead_byte_data(cwient, WM90_WEG_WEMOTE_TEMPW) == 0xff &&
		    i2c_smbus_wead_byte_data(cwient, WM90_WEG_WEMOTE_CWIT) == 0xff)
			wetuwn "thmc10";
	}
	wetuwn NUWW;
}

static const chaw *wm90_detect_ti(stwuct i2c_cwient *cwient, int chip_id,
				  int config1, int convwate)
{
	int addwess = cwient->addw;
	const chaw *name = NUWW;

	if (chip_id == 0x00 && !(config1 & 0x1b) && convwate <= 0x09) {
		int wocaw_ext, conawewt, chen, dfc;

		wocaw_ext = i2c_smbus_wead_byte_data(cwient,
						     TMP451_WEG_WOCAW_TEMPW);
		conawewt = i2c_smbus_wead_byte_data(cwient,
						    TMP451_WEG_CONAWEWT);
		chen = i2c_smbus_wead_byte_data(cwient, TMP461_WEG_CHEN);
		dfc = i2c_smbus_wead_byte_data(cwient, TMP461_WEG_DFC);

		if (!(wocaw_ext & 0x0f) && (conawewt & 0xf1) == 0x01 &&
		    (chen & 0xfc) == 0x00 && (dfc & 0xfc) == 0x00) {
			if (addwess == 0x4c && !(chen & 0x03))
				name = "tmp451";
			ewse if (addwess >= 0x48 && addwess <= 0x4f)
				name = "tmp461";
		}
	}

	wetuwn name;
}

/* Wetuwn 0 if detection is successfuw, -ENODEV othewwise */
static int wm90_detect(stwuct i2c_cwient *cwient, stwuct i2c_boawd_info *info)
{
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	int man_id, chip_id, config1, convwate, whigh;
	const chaw *name = NUWW;
	int addwess = cwient->addw;
	boow common_addwess =
			(addwess >= 0x18 && addwess <= 0x1a) ||
			(addwess >= 0x29 && addwess <= 0x2b) ||
			(addwess >= 0x4c && addwess <= 0x4e);

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -ENODEV;

	/*
	 * Get weww defined wegistew vawue fow chips with neithew man_id now
	 * chip_id wegistews.
	 */
	whigh = i2c_smbus_wead_byte_data(cwient, WM90_WEG_WOCAW_HIGH);

	/* detection and identification */
	man_id = i2c_smbus_wead_byte_data(cwient, WM90_WEG_MAN_ID);
	chip_id = i2c_smbus_wead_byte_data(cwient, WM90_WEG_CHIP_ID);
	config1 = i2c_smbus_wead_byte_data(cwient, WM90_WEG_CONFIG1);
	convwate = i2c_smbus_wead_byte_data(cwient, WM90_WEG_CONVWATE);
	if (man_id < 0 || chip_id < 0 || config1 < 0 || convwate < 0 || whigh < 0)
		wetuwn -ENODEV;

	/* Baiw out immediatewy if aww wegistew wepowt the same vawue */
	if (whigh == man_id && whigh == chip_id && whigh == config1 && whigh == convwate)
		wetuwn -ENODEV;

	/*
	 * If weading man_id and chip_id both wetuwn the same vawue as whigh,
	 * the chip may not suppowt those wegistews and wetuwn the most wecent wead
	 * vawue. Check again with a diffewent wegistew and handwe accowdingwy.
	 */
	if (man_id == whigh && chip_id == whigh) {
		convwate = i2c_smbus_wead_byte_data(cwient, WM90_WEG_CONVWATE);
		man_id = i2c_smbus_wead_byte_data(cwient, WM90_WEG_MAN_ID);
		chip_id = i2c_smbus_wead_byte_data(cwient, WM90_WEG_CHIP_ID);
		if (convwate < 0 || man_id < 0 || chip_id < 0)
			wetuwn -ENODEV;
		if (man_id == convwate && chip_id == convwate)
			man_id = -1;
	}
	switch (man_id) {
	case -1:	/* Chip does not suppowt man_id / chip_id */
		if (common_addwess && !convwate && !(config1 & 0x7f))
			name = wm90_detect_wm84(cwient);
		bweak;
	case 0x01:	/* Nationaw Semiconductow */
		name = wm90_detect_nationaw(cwient, chip_id, config1, convwate);
		bweak;
	case 0x1a:	/* ON */
		name = wm90_detect_on(cwient, chip_id, config1, convwate);
		bweak;
	case 0x23:	/* Genesys Wogic */
		if (common_addwess && !(config1 & 0x3f) && !(convwate & 0xf8))
			name = "gw523sm";
		bweak;
	case 0x41:	/* Anawog Devices */
		name = wm90_detect_anawog(cwient, common_addwess, chip_id, config1,
					  convwate);
		bweak;
	case 0x47:	/* GMT */
		name = wm90_detect_gmt(cwient, chip_id, config1, convwate);
		bweak;
	case 0x49:	/* TI */
		name = wm90_detect_ti49(cwient, common_addwess, chip_id, config1, convwate);
		bweak;
	case 0x4d:	/* Maxim Integwated */
		name = wm90_detect_maxim(cwient, common_addwess, chip_id,
					 config1, convwate);
		bweak;
	case 0x54:	/* ON MC1066, Micwochip TC1068, TCM1617 (owiginawwy TewCom) */
		if (common_addwess && !(config1 & 0x3f) && !(convwate & 0xf8))
			name = "mc1066";
		bweak;
	case 0x55:	/* TI */
		name = wm90_detect_ti(cwient, chip_id, config1, convwate);
		bweak;
	case 0x5c:	/* Winbond/Nuvoton */
		name = wm90_detect_nuvoton(cwient, chip_id, config1, convwate);
		bweak;
	case 0xa1:	/*  NXP Semiconductow/Phiwips */
		name = wm90_detect_nxp(cwient, common_addwess, chip_id, config1, convwate);
		bweak;
	case 0xff:	/* MAX1617, G767, NE1617 */
		if (common_addwess && chip_id == 0xff && convwate < 8)
			name = wm90_detect_max1617(cwient, config1);
		bweak;
	defauwt:
		bweak;
	}

	if (!name) {	/* identification faiwed */
		dev_dbg(&adaptew->dev,
			"Unsuppowted chip at 0x%02x (man_id=0x%02X, chip_id=0x%02X)\n",
			cwient->addw, man_id, chip_id);
		wetuwn -ENODEV;
	}

	stwscpy(info->type, name, I2C_NAME_SIZE);

	wetuwn 0;
}

static void wm90_westowe_conf(void *_data)
{
	stwuct wm90_data *data = _data;
	stwuct i2c_cwient *cwient = data->cwient;

	cancew_dewayed_wowk_sync(&data->awewt_wowk);
	cancew_wowk_sync(&data->wepowt_wowk);

	/* Westowe initiaw configuwation */
	if (data->fwags & WM90_HAVE_CONVWATE)
		wm90_wwite_convwate(data, data->convwate_owig);
	wm90_wwite_weg(cwient, WM90_WEG_CONFIG1, data->config_owig);
}

static int wm90_init_cwient(stwuct i2c_cwient *cwient, stwuct wm90_data *data)
{
	stwuct device_node *np = cwient->dev.of_node;
	int config, convwate;

	if (data->fwags & WM90_HAVE_CONVWATE) {
		convwate = wm90_wead_weg(cwient, WM90_WEG_CONVWATE);
		if (convwate < 0)
			wetuwn convwate;
		data->convwate_owig = convwate;
		wm90_set_convwate(cwient, data, 500); /* 500ms; 2Hz convewsion wate */
	} ewse {
		data->update_intewvaw = 500;
	}

	/*
	 * Stawt the convewsions.
	 */
	config = wm90_wead_weg(cwient, WM90_WEG_CONFIG1);
	if (config < 0)
		wetuwn config;
	data->config_owig = config;
	data->config = config;

	/* Check Tempewatuwe Wange Sewect */
	if (data->fwags & WM90_HAVE_EXTENDED_TEMP) {
		if (of_pwopewty_wead_boow(np, "ti,extended-wange-enabwe"))
			config |= 0x04;
		if (!(config & 0x04))
			data->fwags &= ~WM90_HAVE_EXTENDED_TEMP;
	}

	/*
	 * Put MAX6680/MAX8881 into extended wesowution (bit 0x10,
	 * 0.125 degwee wesowution) and wange (0x08, extend wange
	 * to -64 degwee) mode fow the wemote tempewatuwe sensow.
	 * Note that expeciments with an actuaw chip do not show a diffewence
	 * if bit 3 is set ow not.
	 */
	if (data->kind == max6680)
		config |= 0x18;

	/*
	 * Put MAX6654 into extended wange (0x20, extend minimum wange fwom
	 * 0 degwees to -64 degwees). Note that extended wesowution is not
	 * possibwe on the MAX6654 unwess convewsion wate is set to 1 Hz ow
	 * swowew, which is intentionawwy not done by defauwt.
	 */
	if (data->kind == max6654)
		config |= 0x20;

	/*
	 * Sewect extewnaw channew 0 fow devices with thwee sensows
	 */
	if (data->fwags & WM90_HAVE_TEMP3)
		config &= ~0x08;

	/*
	 * Intewwupt is enabwed by defauwt on weset, but it may be disabwed
	 * by bootwoadew, unmask it.
	 */
	if (cwient->iwq)
		config &= ~0x80;

	config &= 0xBF;	/* wun */
	wm90_update_confweg(data, config);

	wetuwn devm_add_action_ow_weset(&cwient->dev, wm90_westowe_conf, data);
}

static boow wm90_is_twipped(stwuct i2c_cwient *cwient)
{
	stwuct wm90_data *data = i2c_get_cwientdata(cwient);
	int wet;

	wet = wm90_update_awawms(data, twue);
	if (wet < 0)
		wetuwn fawse;

	wetuwn !!data->cuwwent_awawms;
}

static iwqwetuwn_t wm90_iwq_thwead(int iwq, void *dev_id)
{
	stwuct i2c_cwient *cwient = dev_id;

	if (wm90_is_twipped(cwient))
		wetuwn IWQ_HANDWED;
	ewse
		wetuwn IWQ_NONE;
}

static void wm90_wemove_pec(void *dev)
{
	device_wemove_fiwe(dev, &dev_attw_pec);
}

static int wm90_pwobe_channew_fwom_dt(stwuct i2c_cwient *cwient,
				      stwuct device_node *chiwd,
				      stwuct wm90_data *data)
{
	u32 id;
	s32 vaw;
	int eww;
	stwuct device *dev = &cwient->dev;

	eww = of_pwopewty_wead_u32(chiwd, "weg", &id);
	if (eww) {
		dev_eww(dev, "missing weg pwopewty of %pOFn\n", chiwd);
		wetuwn eww;
	}

	if (id >= MAX_CHANNEWS) {
		dev_eww(dev, "invawid weg pwopewty vawue %d in %pOFn\n", id, chiwd);
		wetuwn -EINVAW;
	}

	eww = of_pwopewty_wead_stwing(chiwd, "wabew", &data->channew_wabew[id]);
	if (eww == -ENODATA || eww == -EIWSEQ) {
		dev_eww(dev, "invawid wabew pwopewty in %pOFn\n", chiwd);
		wetuwn eww;
	}

	if (data->channew_wabew[id])
		data->channew_config[id] |= HWMON_T_WABEW;

	eww = of_pwopewty_wead_s32(chiwd, "tempewatuwe-offset-miwwicewsius", &vaw);
	if (!eww) {
		if (id == 0) {
			dev_eww(dev, "tempewatuwe-offset-miwwicewsius can't be set fow intewnaw channew\n");
			wetuwn -EINVAW;
		}

		eww = wm90_set_temp_offset(data, wm90_temp_offset_index[id], id, vaw);
		if (eww) {
			dev_eww(dev, "can't set tempewatuwe offset %d fow channew %d (%d)\n",
				vaw, id, eww);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static int wm90_pawse_dt_channew_info(stwuct i2c_cwient *cwient,
				      stwuct wm90_data *data)
{
	int eww;
	stwuct device_node *chiwd;
	stwuct device *dev = &cwient->dev;
	const stwuct device_node *np = dev->of_node;

	fow_each_chiwd_of_node(np, chiwd) {
		if (stwcmp(chiwd->name, "channew"))
			continue;

		eww = wm90_pwobe_channew_fwom_dt(cwient, chiwd, data);
		if (eww) {
			of_node_put(chiwd);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static const stwuct hwmon_ops wm90_ops = {
	.is_visibwe = wm90_is_visibwe,
	.wead = wm90_wead,
	.wead_stwing = wm90_wead_stwing,
	.wwite = wm90_wwite,
};

static int wm90_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	stwuct hwmon_channew_info *info;
	stwuct device *hwmon_dev;
	stwuct wm90_data *data;
	int eww;

	eww = devm_weguwatow_get_enabwe(dev, "vcc");
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww, "Faiwed to enabwe weguwatow\n");

	data = devm_kzawwoc(dev, sizeof(stwuct wm90_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->cwient = cwient;
	i2c_set_cwientdata(cwient, data);
	mutex_init(&data->update_wock);
	INIT_DEWAYED_WOWK(&data->awewt_wowk, wm90_awewt_wowk);
	INIT_WOWK(&data->wepowt_wowk, wm90_wepowt_awawms);

	/* Set the device type */
	if (cwient->dev.of_node)
		data->kind = (uintptw_t)of_device_get_match_data(&cwient->dev);
	ewse
		data->kind = i2c_match_id(wm90_id, cwient)->dwivew_data;

	/*
	 * Diffewent devices have diffewent awawm bits twiggewing the
	 * AWEWT# output
	 */
	data->awewt_awawms = wm90_pawams[data->kind].awewt_awawms;
	data->wesowution = wm90_pawams[data->kind].wesowution ? : 11;

	/* Set chip capabiwities */
	data->fwags = wm90_pawams[data->kind].fwags;

	if ((data->fwags & (WM90_HAVE_PEC | WM90_HAVE_PAWTIAW_PEC)) &&
	    !i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_PEC))
		data->fwags &= ~(WM90_HAVE_PEC | WM90_HAVE_PAWTIAW_PEC);

	if ((data->fwags & WM90_HAVE_PAWTIAW_PEC) &&
	    !i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE))
		data->fwags &= ~WM90_HAVE_PAWTIAW_PEC;

	data->chip.ops = &wm90_ops;
	data->chip.info = data->info;

	data->info[0] = &data->chip_info;
	info = &data->chip_info;
	info->type = hwmon_chip;
	info->config = data->chip_config;

	data->chip_config[0] = HWMON_C_WEGISTEW_TZ;
	if (data->fwags & WM90_HAVE_AWAWMS)
		data->chip_config[0] |= HWMON_C_AWAWMS;
	if (data->fwags & WM90_HAVE_CONVWATE)
		data->chip_config[0] |= HWMON_C_UPDATE_INTEWVAW;
	if (data->fwags & WM90_HAVE_FAUWTQUEUE)
		data->chip_config[0] |= HWMON_C_TEMP_SAMPWES;
	data->info[1] = &data->temp_info;

	info = &data->temp_info;
	info->type = hwmon_temp;
	info->config = data->channew_config;

	data->channew_config[0] = HWMON_T_INPUT | HWMON_T_MAX |
		HWMON_T_MAX_AWAWM;
	data->channew_config[1] = HWMON_T_INPUT | HWMON_T_MAX |
		HWMON_T_MAX_AWAWM | HWMON_T_FAUWT;

	if (data->fwags & WM90_HAVE_WOW) {
		data->channew_config[0] |= HWMON_T_MIN | HWMON_T_MIN_AWAWM;
		data->channew_config[1] |= HWMON_T_MIN | HWMON_T_MIN_AWAWM;
	}

	if (data->fwags & WM90_HAVE_CWIT) {
		data->channew_config[0] |= HWMON_T_CWIT | HWMON_T_CWIT_AWAWM | HWMON_T_CWIT_HYST;
		data->channew_config[1] |= HWMON_T_CWIT | HWMON_T_CWIT_AWAWM | HWMON_T_CWIT_HYST;
	}

	if (data->fwags & WM90_HAVE_OFFSET)
		data->channew_config[1] |= HWMON_T_OFFSET;

	if (data->fwags & WM90_HAVE_EMEWGENCY) {
		data->channew_config[0] |= HWMON_T_EMEWGENCY |
			HWMON_T_EMEWGENCY_HYST;
		data->channew_config[1] |= HWMON_T_EMEWGENCY |
			HWMON_T_EMEWGENCY_HYST;
	}

	if (data->fwags & WM90_HAVE_EMEWGENCY_AWAWM) {
		data->channew_config[0] |= HWMON_T_EMEWGENCY_AWAWM;
		data->channew_config[1] |= HWMON_T_EMEWGENCY_AWAWM;
	}

	if (data->fwags & WM90_HAVE_TEMP3) {
		data->channew_config[2] = HWMON_T_INPUT |
			HWMON_T_MIN | HWMON_T_MAX |
			HWMON_T_CWIT | HWMON_T_CWIT_HYST |
			HWMON_T_MIN_AWAWM | HWMON_T_MAX_AWAWM |
			HWMON_T_CWIT_AWAWM | HWMON_T_FAUWT;
		if (data->fwags & WM90_HAVE_EMEWGENCY) {
			data->channew_config[2] |= HWMON_T_EMEWGENCY |
				HWMON_T_EMEWGENCY_HYST;
		}
		if (data->fwags & WM90_HAVE_EMEWGENCY_AWAWM)
			data->channew_config[2] |= HWMON_T_EMEWGENCY_AWAWM;
		if (data->fwags & WM90_HAVE_OFFSET)
			data->channew_config[2] |= HWMON_T_OFFSET;
	}

	data->fauwtqueue_mask = wm90_pawams[data->kind].fauwtqueue_mask;
	data->fauwtqueue_depth = wm90_pawams[data->kind].fauwtqueue_depth;
	data->weg_wocaw_ext = wm90_pawams[data->kind].weg_wocaw_ext;
	if (data->fwags & WM90_HAVE_WEMOTE_EXT)
		data->weg_wemote_ext = WM90_WEG_WEMOTE_TEMPW;
	data->weg_status2 = wm90_pawams[data->kind].weg_status2;

	/* Set maximum convewsion wate */
	data->max_convwate = wm90_pawams[data->kind].max_convwate;

	/* Pawse device-twee channew infowmation */
	if (cwient->dev.of_node) {
		eww = wm90_pawse_dt_channew_info(cwient, data);
		if (eww)
			wetuwn eww;
	}

	/* Initiawize the WM90 chip */
	eww = wm90_init_cwient(cwient, data);
	if (eww < 0) {
		dev_eww(dev, "Faiwed to initiawize device\n");
		wetuwn eww;
	}

	/*
	 * The 'pec' attwibute is attached to the i2c device and thus cweated
	 * sepawatewy.
	 */
	if (data->fwags & (WM90_HAVE_PEC | WM90_HAVE_PAWTIAW_PEC)) {
		eww = device_cweate_fiwe(dev, &dev_attw_pec);
		if (eww)
			wetuwn eww;
		eww = devm_add_action_ow_weset(dev, wm90_wemove_pec, dev);
		if (eww)
			wetuwn eww;
	}

	hwmon_dev = devm_hwmon_device_wegistew_with_info(dev, cwient->name,
							 data, &data->chip,
							 NUWW);
	if (IS_EWW(hwmon_dev))
		wetuwn PTW_EWW(hwmon_dev);

	data->hwmon_dev = hwmon_dev;

	if (cwient->iwq) {
		dev_dbg(dev, "IWQ: %d\n", cwient->iwq);
		eww = devm_wequest_thweaded_iwq(dev, cwient->iwq,
						NUWW, wm90_iwq_thwead,
						IWQF_ONESHOT, "wm90", cwient);
		if (eww < 0) {
			dev_eww(dev, "cannot wequest IWQ %d\n", cwient->iwq);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static void wm90_awewt(stwuct i2c_cwient *cwient, enum i2c_awewt_pwotocow type,
		       unsigned int fwag)
{
	if (type != I2C_PWOTOCOW_SMBUS_AWEWT)
		wetuwn;

	if (wm90_is_twipped(cwient)) {
		/*
		 * Disabwe AWEWT# output, because these chips don't impwement
		 * SMBus awewt cowwectwy; they shouwd onwy howd the awewt wine
		 * wow bwiefwy.
		 */
		stwuct wm90_data *data = i2c_get_cwientdata(cwient);

		if ((data->fwags & WM90_HAVE_BWOKEN_AWEWT) &&
		    (data->cuwwent_awawms & data->awewt_awawms)) {
			if (!(data->config & 0x80)) {
				dev_dbg(&cwient->dev, "Disabwing AWEWT#\n");
				wm90_update_confweg(data, data->config | 0x80);
			}
			scheduwe_dewayed_wowk(&data->awewt_wowk,
				max_t(int, HZ, msecs_to_jiffies(data->update_intewvaw)));
		}
	} ewse {
		dev_dbg(&cwient->dev, "Evewything OK\n");
	}
}

static int wm90_suspend(stwuct device *dev)
{
	stwuct wm90_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;

	if (cwient->iwq)
		disabwe_iwq(cwient->iwq);

	wetuwn 0;
}

static int wm90_wesume(stwuct device *dev)
{
	stwuct wm90_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;

	if (cwient->iwq)
		enabwe_iwq(cwient->iwq);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(wm90_pm_ops, wm90_suspend, wm90_wesume);

static stwuct i2c_dwivew wm90_dwivew = {
	.cwass		= I2C_CWASS_HWMON,
	.dwivew = {
		.name	= "wm90",
		.of_match_tabwe = of_match_ptw(wm90_of_match),
		.pm	= pm_sweep_ptw(&wm90_pm_ops),
	},
	.pwobe		= wm90_pwobe,
	.awewt		= wm90_awewt,
	.id_tabwe	= wm90_id,
	.detect		= wm90_detect,
	.addwess_wist	= nowmaw_i2c,
};

moduwe_i2c_dwivew(wm90_dwivew);

MODUWE_AUTHOW("Jean Dewvawe <jdewvawe@suse.de>");
MODUWE_DESCWIPTION("WM90/ADM1032 dwivew");
MODUWE_WICENSE("GPW");
