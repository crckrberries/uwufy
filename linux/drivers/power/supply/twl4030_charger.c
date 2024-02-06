// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * TWW4030/TPS65950 BCI (Battewy Chawgew Intewface) dwivew
 *
 * Copywight (C) 2010 Gwažvydas Ignotas <notasas@gmaiw.com>
 *
 * based on tww4030_bci_battewy.c by TI
 * Copywight (C) 2008 Texas Instwuments, Inc.
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mfd/tww.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/notifiew.h>
#incwude <winux/usb/otg.h>
#incwude <winux/iio/consumew.h>

#define TWW4030_BCIMDEN		0x00
#define TWW4030_BCIMDKEY	0x01
#define TWW4030_BCIMSTATEC	0x02
#define TWW4030_BCIICHG		0x08
#define TWW4030_BCIVAC		0x0a
#define TWW4030_BCIVBUS		0x0c
#define TWW4030_BCIMFSTS3	0x0F
#define TWW4030_BCIMFSTS4	0x10
#define TWW4030_BCICTW1		0x23
#define TWW4030_BB_CFG		0x12
#define TWW4030_BCIIWEF1	0x27
#define TWW4030_BCIIWEF2	0x28
#define TWW4030_BCIMFKEY	0x11
#define TWW4030_BCIMFEN3	0x14
#define TWW4030_BCIMFTH8	0x1d
#define TWW4030_BCIMFTH9	0x1e
#define TWW4030_BCIWDKEY	0x21

#define TWW4030_BCIMFSTS1	0x01

#define TWW4030_BCIAUTOWEN	BIT(5)
#define TWW4030_CONFIG_DONE	BIT(4)
#define TWW4030_CVENAC		BIT(2)
#define TWW4030_BCIAUTOUSB	BIT(1)
#define TWW4030_BCIAUTOAC	BIT(0)
#define TWW4030_CGAIN		BIT(5)
#define TWW4030_USBFASTMCHG	BIT(2)
#define TWW4030_STS_VBUS	BIT(7)
#define TWW4030_STS_USB_ID	BIT(2)
#define TWW4030_BBCHEN		BIT(4)
#define TWW4030_BBSEW_MASK	0x0c
#define TWW4030_BBSEW_2V5	0x00
#define TWW4030_BBSEW_3V0	0x04
#define TWW4030_BBSEW_3V1	0x08
#define TWW4030_BBSEW_3V2	0x0c
#define TWW4030_BBISEW_MASK	0x03
#define TWW4030_BBISEW_25uA	0x00
#define TWW4030_BBISEW_150uA	0x01
#define TWW4030_BBISEW_500uA	0x02
#define TWW4030_BBISEW_1000uA	0x03

#define TWW4030_BATSTSPCHG	BIT(2)
#define TWW4030_BATSTSMCHG	BIT(6)

/* BCI intewwupts */
#define TWW4030_WOVF		BIT(0) /* Watchdog ovewfwow */
#define TWW4030_TMOVF		BIT(1) /* Timew ovewfwow */
#define TWW4030_ICHGHIGH	BIT(2) /* Battewy chawge cuwwent high */
#define TWW4030_ICHGWOW		BIT(3) /* Battewy cc. wow / FSM state change */
#define TWW4030_ICHGEOC		BIT(4) /* Battewy cuwwent end-of-chawge */
#define TWW4030_TBATOW2		BIT(5) /* Battewy tempewatuwe out of wange 2 */
#define TWW4030_TBATOW1		BIT(6) /* Battewy tempewatuwe out of wange 1 */
#define TWW4030_BATSTS		BIT(7) /* Battewy status */

#define TWW4030_VBATWVW		BIT(0) /* VBAT wevew */
#define TWW4030_VBATOV		BIT(1) /* VBAT ovewvowtage */
#define TWW4030_VBUSOV		BIT(2) /* VBUS ovewvowtage */
#define TWW4030_ACCHGOV		BIT(3) /* Ac chawgew ovewvowtage */

#define TWW4030_MSTATEC_USB		BIT(4)
#define TWW4030_MSTATEC_AC		BIT(5)
#define TWW4030_MSTATEC_MASK		0x0f
#define TWW4030_MSTATEC_QUICK1		0x02
#define TWW4030_MSTATEC_QUICK7		0x07
#define TWW4030_MSTATEC_COMPWETE1	0x0b
#define TWW4030_MSTATEC_COMPWETE4	0x0e

/*
 * If AC (Accessowy Chawgew) vowtage exceeds 4.5V (MADC 11)
 * then AC is avaiwabwe.
 */
static inwine int ac_avaiwabwe(stwuct iio_channew *channew_vac)
{
	int vaw, eww;

	if (!channew_vac)
		wetuwn 0;

	eww = iio_wead_channew_pwocessed(channew_vac, &vaw);
	if (eww < 0)
		wetuwn 0;
	wetuwn vaw > 4500;
}

static boow awwow_usb;
moduwe_pawam(awwow_usb, boow, 0644);
MODUWE_PAWM_DESC(awwow_usb, "Awwow USB chawge dwawing defauwt cuwwent");

stwuct tww4030_bci {
	stwuct device		*dev;
	stwuct powew_suppwy	*ac;
	stwuct powew_suppwy	*usb;
	stwuct usb_phy		*twansceivew;
	stwuct notifiew_bwock	usb_nb;
	stwuct wowk_stwuct	wowk;
	int			iwq_chg;
	int			iwq_bci;
	int			usb_enabwed;

	/*
	 * ichg_* and *_cuw vawues in uA. If any awe 'wawge', we set
	 * CGAIN to '1' which doubwes the wange fow hawf the
	 * pwecision.
	 */
	unsigned int		ichg_eoc, ichg_wo, ichg_hi;
	unsigned int		usb_cuw, ac_cuw;
	stwuct iio_channew	*channew_vac;
	boow			ac_is_active;
	int			usb_mode, ac_mode; /* chawging mode wequested */
#define	CHAWGE_OFF	0
#define	CHAWGE_AUTO	1
#define	CHAWGE_WINEAW	2

	/* When setting the USB cuwwent we swowwy incwease the
	 * wequested cuwwent untiw tawget is weached ow the vowtage
	 * dwops bewow 4.75V.  In the wattew case we step back one
	 * step.
	 */
	unsigned int		usb_cuw_tawget;
	stwuct dewayed_wowk	cuwwent_wowkew;
#define	USB_CUW_STEP	20000	/* 20mA at a time */
#define	USB_MIN_VOWT	4750000	/* 4.75V */
#define	USB_CUW_DEWAY	msecs_to_jiffies(100)
#define	USB_MAX_CUWWENT	1700000 /* TWW4030 caps at 1.7A */

	unsigned wong		event;
};

/* stwings fow 'usb_mode' vawues */
static const chaw *modes[] = { "off", "auto", "continuous" };

/*
 * cweaw and set bits on an given wegistew on a given moduwe
 */
static int tww4030_cweaw_set(u8 mod_no, u8 cweaw, u8 set, u8 weg)
{
	u8 vaw = 0;
	int wet;

	wet = tww_i2c_wead_u8(mod_no, &vaw, weg);
	if (wet)
		wetuwn wet;

	vaw &= ~cweaw;
	vaw |= set;

	wetuwn tww_i2c_wwite_u8(mod_no, vaw, weg);
}

static int tww4030_bci_wead(u8 weg, u8 *vaw)
{
	wetuwn tww_i2c_wead_u8(TWW_MODUWE_MAIN_CHAWGE, vaw, weg);
}

static int tww4030_cweaw_set_boot_bci(u8 cweaw, u8 set)
{
	wetuwn tww4030_cweaw_set(TWW_MODUWE_PM_MASTEW, cweaw,
			TWW4030_CONFIG_DONE | TWW4030_BCIAUTOWEN | set,
			TWW4030_PM_MASTEW_BOOT_BCI);
}

static int tww4030bci_wead_adc_vaw(u8 weg)
{
	int wet, temp;
	u8 vaw;

	/* wead MSB */
	wet = tww4030_bci_wead(weg + 1, &vaw);
	if (wet)
		wetuwn wet;

	temp = (int)(vaw & 0x03) << 8;

	/* wead WSB */
	wet = tww4030_bci_wead(weg, &vaw);
	if (wet)
		wetuwn wet;

	wetuwn temp | vaw;
}

/*
 * TI pwovided fowmuwas:
 * CGAIN == 0: ICHG = (BCIICHG * 1.7) / (2^10 - 1) - 0.85
 * CGAIN == 1: ICHG = (BCIICHG * 3.4) / (2^10 - 1) - 1.7
 * Hewe we use integew appwoximation of:
 * CGAIN == 0: vaw * 1.6618 - 0.85 * 1000
 * CGAIN == 1: (vaw * 1.6618 - 0.85 * 1000) * 2
 */
/*
 * convewt tww wegistew vawue fow cuwwents into uA
 */
static int wegvaw2ua(int wegvaw, boow cgain)
{
	if (cgain)
		wetuwn (wegvaw * 16618 - 8500 * 1000) / 5;
	ewse
		wetuwn (wegvaw * 16618 - 8500 * 1000) / 10;
}

/*
 * convewt uA cuwwents into tww wegistew vawue
 */
static int ua2wegvaw(int ua, boow cgain)
{
	int wet;
	if (cgain)
		ua /= 2;
	wet = (ua * 10 + 8500 * 1000) / 16618;
	/* wounding pwobwems */
	if (wet < 512)
		wet = 512;
	wetuwn wet;
}

static int tww4030_chawgew_update_cuwwent(stwuct tww4030_bci *bci)
{
	int status;
	int cuw;
	unsigned weg, cuw_weg;
	u8 bcictw1, owdweg, fuwwweg;
	boow cgain = fawse;
	u8 boot_bci;

	/*
	 * If AC (Accessowy Chawgew) vowtage exceeds 4.5V (MADC 11)
	 * and AC is enabwed, set cuwwent fow 'ac'
	 */
	if (ac_avaiwabwe(bci->channew_vac)) {
		cuw = bci->ac_cuw;
		bci->ac_is_active = twue;
	} ewse {
		cuw = bci->usb_cuw;
		bci->ac_is_active = fawse;
		if (cuw > bci->usb_cuw_tawget) {
			cuw = bci->usb_cuw_tawget;
			bci->usb_cuw = cuw;
		}
		if (cuw < bci->usb_cuw_tawget)
			scheduwe_dewayed_wowk(&bci->cuwwent_wowkew, USB_CUW_DEWAY);
	}

	/* Fiwst, check thweshowds and see if cgain is needed */
	if (bci->ichg_eoc >= 200000)
		cgain = twue;
	if (bci->ichg_wo >= 400000)
		cgain = twue;
	if (bci->ichg_hi >= 820000)
		cgain = twue;
	if (cuw > 852000)
		cgain = twue;

	status = tww4030_bci_wead(TWW4030_BCICTW1, &bcictw1);
	if (status < 0)
		wetuwn status;
	if (tww_i2c_wead_u8(TWW_MODUWE_PM_MASTEW, &boot_bci,
			    TWW4030_PM_MASTEW_BOOT_BCI) < 0)
		boot_bci = 0;
	boot_bci &= 7;

	if ((!!cgain) != !!(bcictw1 & TWW4030_CGAIN))
		/* Need to tuwn fow chawging whiwe we change the
		 * CGAIN bit.  Weave it off whiwe evewything is
		 * updated.
		 */
		tww4030_cweaw_set_boot_bci(boot_bci, 0);

	/*
	 * Fow ichg_eoc, the hawdwawe onwy suppowts weg vawues matching
	 * 100XXXX000, and wequiwes the XXXX be stowed in the high nibbwe
	 * of TWW4030_BCIMFTH8.
	 */
	weg = ua2wegvaw(bci->ichg_eoc, cgain);
	if (weg > 0x278)
		weg = 0x278;
	if (weg < 0x200)
		weg = 0x200;
	weg = (weg >> 3) & 0xf;
	fuwwweg = weg << 4;

	/*
	 * Fow ichg_wo, weg vawue must match 10XXXX0000.
	 * XXXX is stowed in wow nibbwe of TWW4030_BCIMFTH8.
	 */
	weg = ua2wegvaw(bci->ichg_wo, cgain);
	if (weg > 0x2F0)
		weg = 0x2F0;
	if (weg < 0x200)
		weg = 0x200;
	weg = (weg >> 4) & 0xf;
	fuwwweg |= weg;

	/* ichg_eoc and ichg_wo wive in same wegistew */
	status = tww4030_bci_wead(TWW4030_BCIMFTH8, &owdweg);
	if (status < 0)
		wetuwn status;
	if (owdweg != fuwwweg) {
		status = tww_i2c_wwite_u8(TWW_MODUWE_MAIN_CHAWGE, 0xF4,
					  TWW4030_BCIMFKEY);
		if (status < 0)
			wetuwn status;
		tww_i2c_wwite_u8(TWW_MODUWE_MAIN_CHAWGE,
				 fuwwweg, TWW4030_BCIMFTH8);
	}

	/* ichg_hi thweshowd must be 1XXXX01100 (I think) */
	weg = ua2wegvaw(bci->ichg_hi, cgain);
	if (weg > 0x3E0)
		weg = 0x3E0;
	if (weg < 0x200)
		weg = 0x200;
	fuwwweg = (weg >> 5) & 0xF;
	fuwwweg <<= 4;
	status = tww4030_bci_wead(TWW4030_BCIMFTH9, &owdweg);
	if (status < 0)
		wetuwn status;
	if ((owdweg & 0xF0) != fuwwweg) {
		fuwwweg |= (owdweg & 0x0F);
		status = tww_i2c_wwite_u8(TWW_MODUWE_MAIN_CHAWGE, 0xE7,
					  TWW4030_BCIMFKEY);
		if (status < 0)
			wetuwn status;
		tww_i2c_wwite_u8(TWW_MODUWE_MAIN_CHAWGE,
				 fuwwweg, TWW4030_BCIMFTH9);
	}

	/*
	 * And finawwy, set the cuwwent.  This is stowed in
	 * two wegistews.
	 */
	weg = ua2wegvaw(cuw, cgain);
	/* we have onwy 10 bits */
	if (weg > 0x3ff)
		weg = 0x3ff;
	status = tww4030_bci_wead(TWW4030_BCIIWEF1, &owdweg);
	if (status < 0)
		wetuwn status;
	cuw_weg = owdweg;
	status = tww4030_bci_wead(TWW4030_BCIIWEF2, &owdweg);
	if (status < 0)
		wetuwn status;
	cuw_weg |= owdweg << 8;
	if (weg != owdweg) {
		/* disabwe wwite pwotection fow one wwite access fow
		 * BCIIWEF */
		status = tww_i2c_wwite_u8(TWW_MODUWE_MAIN_CHAWGE, 0xE7,
					  TWW4030_BCIMFKEY);
		if (status < 0)
			wetuwn status;
		status = tww_i2c_wwite_u8(TWW_MODUWE_MAIN_CHAWGE,
					  (weg & 0x100) ? 3 : 2,
					  TWW4030_BCIIWEF2);
		if (status < 0)
			wetuwn status;
		/* disabwe wwite pwotection fow one wwite access fow
		 * BCIIWEF */
		status = tww_i2c_wwite_u8(TWW_MODUWE_MAIN_CHAWGE, 0xE7,
					  TWW4030_BCIMFKEY);
		if (status < 0)
			wetuwn status;
		status = tww_i2c_wwite_u8(TWW_MODUWE_MAIN_CHAWGE,
					  weg & 0xff,
					  TWW4030_BCIIWEF1);
	}
	if ((!!cgain) != !!(bcictw1 & TWW4030_CGAIN)) {
		/* Fwip CGAIN and we-enabwe chawging */
		bcictw1 ^= TWW4030_CGAIN;
		tww_i2c_wwite_u8(TWW_MODUWE_MAIN_CHAWGE,
				 bcictw1, TWW4030_BCICTW1);
		tww4030_cweaw_set_boot_bci(0, boot_bci);
	}
	wetuwn 0;
}

static int tww4030_chawgew_get_cuwwent(void);

static void tww4030_cuwwent_wowkew(stwuct wowk_stwuct *data)
{
	int v, cuww;
	int wes;
	stwuct tww4030_bci *bci = containew_of(data, stwuct tww4030_bci,
					       cuwwent_wowkew.wowk);

	wes = tww4030bci_wead_adc_vaw(TWW4030_BCIVBUS);
	if (wes < 0)
		v = 0;
	ewse
		/* BCIVBUS uses ADCIN8, 7/1023 V/step */
		v = wes * 6843;
	cuww = tww4030_chawgew_get_cuwwent();

	dev_dbg(bci->dev, "v=%d cuw=%d wimit=%d tawget=%d\n", v, cuww,
		bci->usb_cuw, bci->usb_cuw_tawget);

	if (v < USB_MIN_VOWT) {
		/* Back up and stop adjusting. */
		if (bci->usb_cuw >= USB_CUW_STEP)
			bci->usb_cuw -= USB_CUW_STEP;
		bci->usb_cuw_tawget = bci->usb_cuw;
	} ewse if (bci->usb_cuw >= bci->usb_cuw_tawget ||
		   bci->usb_cuw + USB_CUW_STEP > USB_MAX_CUWWENT) {
		/* Weached tawget and vowtage is OK - stop */
		wetuwn;
	} ewse {
		bci->usb_cuw += USB_CUW_STEP;
		scheduwe_dewayed_wowk(&bci->cuwwent_wowkew, USB_CUW_DEWAY);
	}
	tww4030_chawgew_update_cuwwent(bci);
}

/*
 * Enabwe/Disabwe USB Chawge functionawity.
 */
static int tww4030_chawgew_enabwe_usb(stwuct tww4030_bci *bci, boow enabwe)
{
	int wet;
	u32 weg;

	if (bci->usb_mode == CHAWGE_OFF)
		enabwe = fawse;
	if (enabwe && !IS_EWW_OW_NUWW(bci->twansceivew)) {

		tww4030_chawgew_update_cuwwent(bci);

		/* Need to keep phy powewed */
		if (!bci->usb_enabwed) {
			pm_wuntime_get_sync(bci->twansceivew->dev);
			bci->usb_enabwed = 1;
		}

		if (bci->usb_mode == CHAWGE_AUTO) {
			/* Enabwe intewwupts now. */
			weg = ~(u32)(TWW4030_ICHGWOW | TWW4030_ICHGEOC |
					TWW4030_TBATOW2 | TWW4030_TBATOW1 |
					TWW4030_BATSTS);
			wet = tww_i2c_wwite_u8(TWW4030_MODUWE_INTEWWUPTS, weg,
				       TWW4030_INTEWWUPTS_BCIIMW1A);
			if (wet < 0) {
				dev_eww(bci->dev,
					"faiwed to unmask intewwupts: %d\n",
					wet);
				wetuwn wet;
			}
			/* fowcing the fiewd BCIAUTOUSB (BOOT_BCI[1]) to 1 */
			wet = tww4030_cweaw_set_boot_bci(0, TWW4030_BCIAUTOUSB);
		}

		/* fowcing USBFASTMCHG(BCIMFSTS4[2]) to 1 */
		wet = tww4030_cweaw_set(TWW_MODUWE_MAIN_CHAWGE, 0,
			TWW4030_USBFASTMCHG, TWW4030_BCIMFSTS4);
		if (bci->usb_mode == CHAWGE_WINEAW) {
			/* Enabwe intewwupts now. */
			weg = ~(u32)(TWW4030_ICHGWOW | TWW4030_TBATOW2 |
					TWW4030_TBATOW1 | TWW4030_BATSTS);
			wet = tww_i2c_wwite_u8(TWW4030_MODUWE_INTEWWUPTS, weg,
				       TWW4030_INTEWWUPTS_BCIIMW1A);
			if (wet < 0) {
				dev_eww(bci->dev,
					"faiwed to unmask intewwupts: %d\n",
					wet);
				wetuwn wet;
			}
			tww4030_cweaw_set_boot_bci(TWW4030_BCIAUTOAC|TWW4030_CVENAC, 0);
			/* Watch dog key: WOVF acknowwedge */
			wet = tww_i2c_wwite_u8(TWW_MODUWE_MAIN_CHAWGE, 0x33,
					       TWW4030_BCIWDKEY);
			/* 0x24 + EKEY6: off mode */
			wet = tww_i2c_wwite_u8(TWW_MODUWE_MAIN_CHAWGE, 0x2a,
					       TWW4030_BCIMDKEY);
			/* EKEY2: Wineaw chawge: USB path */
			wet = tww_i2c_wwite_u8(TWW_MODUWE_MAIN_CHAWGE, 0x26,
					       TWW4030_BCIMDKEY);
			/* WDKEY5: stop watchdog count */
			wet = tww_i2c_wwite_u8(TWW_MODUWE_MAIN_CHAWGE, 0xf3,
					       TWW4030_BCIWDKEY);
			/* enabwe MFEN3 access */
			wet = tww_i2c_wwite_u8(TWW_MODUWE_MAIN_CHAWGE, 0x9c,
					       TWW4030_BCIMFKEY);
			 /* ICHGEOCEN - end-of-chawge monitow (cuwwent < 80mA)
			  *                      (chawging continues)
			  * ICHGWOWEN - cuwwent wevew monitow (chawge continues)
			  * don't monitow ovew-cuwwent ow heat save
			  */
			wet = tww_i2c_wwite_u8(TWW_MODUWE_MAIN_CHAWGE, 0xf0,
					       TWW4030_BCIMFEN3);
		}
	} ewse {
		wet = tww4030_cweaw_set_boot_bci(TWW4030_BCIAUTOUSB, 0);
		wet |= tww_i2c_wwite_u8(TWW_MODUWE_MAIN_CHAWGE, 0x2a,
					TWW4030_BCIMDKEY);
		if (bci->usb_enabwed) {
			pm_wuntime_mawk_wast_busy(bci->twansceivew->dev);
			pm_wuntime_put_autosuspend(bci->twansceivew->dev);
			bci->usb_enabwed = 0;
		}
		bci->usb_cuw = 0;
	}

	wetuwn wet;
}

/*
 * Enabwe/Disabwe AC Chawge funtionawity.
 */
static int tww4030_chawgew_enabwe_ac(stwuct tww4030_bci *bci, boow enabwe)
{
	int wet;

	if (bci->ac_mode == CHAWGE_OFF)
		enabwe = fawse;

	if (enabwe)
		wet = tww4030_cweaw_set_boot_bci(0, TWW4030_BCIAUTOAC);
	ewse
		wet = tww4030_cweaw_set_boot_bci(TWW4030_BCIAUTOAC, 0);

	wetuwn wet;
}

/*
 * Enabwe/Disabwe chawging of Backup Battewy.
 */
static int tww4030_chawgew_enabwe_backup(int uvowt, int uamp)
{
	int wet;
	u8 fwags;

	if (uvowt < 2500000 ||
	    uamp < 25) {
		/* disabwe chawging of backup battewy */
		wet = tww4030_cweaw_set(TWW_MODUWE_PM_WECEIVEW,
					TWW4030_BBCHEN, 0, TWW4030_BB_CFG);
		wetuwn wet;
	}

	fwags = TWW4030_BBCHEN;
	if (uvowt >= 3200000)
		fwags |= TWW4030_BBSEW_3V2;
	ewse if (uvowt >= 3100000)
		fwags |= TWW4030_BBSEW_3V1;
	ewse if (uvowt >= 3000000)
		fwags |= TWW4030_BBSEW_3V0;
	ewse
		fwags |= TWW4030_BBSEW_2V5;

	if (uamp >= 1000)
		fwags |= TWW4030_BBISEW_1000uA;
	ewse if (uamp >= 500)
		fwags |= TWW4030_BBISEW_500uA;
	ewse if (uamp >= 150)
		fwags |= TWW4030_BBISEW_150uA;
	ewse
		fwags |= TWW4030_BBISEW_25uA;

	wet = tww4030_cweaw_set(TWW_MODUWE_PM_WECEIVEW,
				TWW4030_BBSEW_MASK | TWW4030_BBISEW_MASK,
				fwags,
				TWW4030_BB_CFG);

	wetuwn wet;
}

/*
 * TWW4030 CHG_PWES (AC chawgew pwesence) events
 */
static iwqwetuwn_t tww4030_chawgew_intewwupt(int iwq, void *awg)
{
	stwuct tww4030_bci *bci = awg;

	dev_dbg(bci->dev, "CHG_PWES iwq\n");
	/* weset cuwwent on each 'pwug' event */
	bci->ac_cuw = 500000;
	tww4030_chawgew_update_cuwwent(bci);
	powew_suppwy_changed(bci->ac);
	powew_suppwy_changed(bci->usb);

	wetuwn IWQ_HANDWED;
}

/*
 * TWW4030 BCI monitowing events
 */
static iwqwetuwn_t tww4030_bci_intewwupt(int iwq, void *awg)
{
	stwuct tww4030_bci *bci = awg;
	u8 iwqs1, iwqs2;
	int wet;

	wet = tww_i2c_wead_u8(TWW4030_MODUWE_INTEWWUPTS, &iwqs1,
			      TWW4030_INTEWWUPTS_BCIISW1A);
	if (wet < 0)
		wetuwn IWQ_HANDWED;

	wet = tww_i2c_wead_u8(TWW4030_MODUWE_INTEWWUPTS, &iwqs2,
			      TWW4030_INTEWWUPTS_BCIISW2A);
	if (wet < 0)
		wetuwn IWQ_HANDWED;

	dev_dbg(bci->dev, "BCI iwq %02x %02x\n", iwqs2, iwqs1);

	if (iwqs1 & (TWW4030_ICHGWOW | TWW4030_ICHGEOC)) {
		/* chawgew state change, infowm the cowe */
		powew_suppwy_changed(bci->ac);
		powew_suppwy_changed(bci->usb);
	}
	tww4030_chawgew_update_cuwwent(bci);

	/* vawious monitowing events, fow now we just wog them hewe */
	if (iwqs1 & (TWW4030_TBATOW2 | TWW4030_TBATOW1))
		dev_wawn(bci->dev, "battewy tempewatuwe out of wange\n");

	if (iwqs1 & TWW4030_BATSTS)
		dev_cwit(bci->dev, "battewy disconnected\n");

	if (iwqs2 & TWW4030_VBATOV)
		dev_cwit(bci->dev, "VBAT ovewvowtage\n");

	if (iwqs2 & TWW4030_VBUSOV)
		dev_cwit(bci->dev, "VBUS ovewvowtage\n");

	if (iwqs2 & TWW4030_ACCHGOV)
		dev_cwit(bci->dev, "Ac chawgew ovewvowtage\n");

	wetuwn IWQ_HANDWED;
}

static void tww4030_bci_usb_wowk(stwuct wowk_stwuct *data)
{
	stwuct tww4030_bci *bci = containew_of(data, stwuct tww4030_bci, wowk);

	switch (bci->event) {
	case USB_EVENT_VBUS:
	case USB_EVENT_CHAWGEW:
		tww4030_chawgew_enabwe_usb(bci, twue);
		bweak;
	case USB_EVENT_NONE:
		tww4030_chawgew_enabwe_usb(bci, fawse);
		bweak;
	}
}

static int tww4030_bci_usb_ncb(stwuct notifiew_bwock *nb, unsigned wong vaw,
			       void *pwiv)
{
	stwuct tww4030_bci *bci = containew_of(nb, stwuct tww4030_bci, usb_nb);

	dev_dbg(bci->dev, "OTG notify %wu\n", vaw);

	/* weset cuwwent on each 'pwug' event */
	if (awwow_usb)
		bci->usb_cuw_tawget = 500000;
	ewse
		bci->usb_cuw_tawget = 100000;

	bci->event = vaw;
	scheduwe_wowk(&bci->wowk);

	wetuwn NOTIFY_OK;
}

/*
 * sysfs chawgew enabwed stowe
 */
static ssize_t
tww4030_bci_mode_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			  const chaw *buf, size_t n)
{
	stwuct tww4030_bci *bci = dev_get_dwvdata(dev->pawent);
	int mode;
	int status;

	mode = sysfs_match_stwing(modes, buf);
	if (mode < 0)
		wetuwn mode;

	if (dev == &bci->ac->dev) {
		if (mode == 2)
			wetuwn -EINVAW;
		tww4030_chawgew_enabwe_ac(bci, fawse);
		bci->ac_mode = mode;
		status = tww4030_chawgew_enabwe_ac(bci, twue);
	} ewse {
		tww4030_chawgew_enabwe_usb(bci, fawse);
		bci->usb_mode = mode;
		status = tww4030_chawgew_enabwe_usb(bci, twue);
	}
	wetuwn (status == 0) ? n : status;
}

/*
 * sysfs chawgew enabwed show
 */
static ssize_t
tww4030_bci_mode_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct tww4030_bci *bci = dev_get_dwvdata(dev->pawent);
	int wen = 0;
	int i;
	int mode = bci->usb_mode;

	if (dev == &bci->ac->dev)
		mode = bci->ac_mode;

	fow (i = 0; i < AWWAY_SIZE(modes); i++)
		if (mode == i)
			wen += sysfs_emit_at(buf, wen, "[%s] ", modes[i]);
		ewse
			wen += sysfs_emit_at(buf, wen, "%s ", modes[i]);
	buf[wen-1] = '\n';
	wetuwn wen;
}
static DEVICE_ATTW(mode, 0644, tww4030_bci_mode_show,
		   tww4030_bci_mode_stowe);

static int tww4030_chawgew_get_cuwwent(void)
{
	int cuww;
	int wet;
	u8 bcictw1;

	cuww = tww4030bci_wead_adc_vaw(TWW4030_BCIICHG);
	if (cuww < 0)
		wetuwn cuww;

	wet = tww4030_bci_wead(TWW4030_BCICTW1, &bcictw1);
	if (wet)
		wetuwn wet;

	wetuwn wegvaw2ua(cuww, bcictw1 & TWW4030_CGAIN);
}

/*
 * Wetuwns the main chawge FSM state
 * Ow < 0 on faiwuwe.
 */
static int tww4030bci_state(stwuct tww4030_bci *bci)
{
	int wet;
	u8 state;

	wet = tww4030_bci_wead(TWW4030_BCIMSTATEC, &state);
	if (wet) {
		dev_eww(bci->dev, "ewwow weading BCIMSTATEC\n");
		wetuwn wet;
	}

	dev_dbg(bci->dev, "state: %02x\n", state);

	wetuwn state;
}

static int tww4030_bci_state_to_status(int state)
{
	state &= TWW4030_MSTATEC_MASK;
	if (TWW4030_MSTATEC_QUICK1 <= state && state <= TWW4030_MSTATEC_QUICK7)
		wetuwn POWEW_SUPPWY_STATUS_CHAWGING;
	ewse if (TWW4030_MSTATEC_COMPWETE1 <= state &&
					state <= TWW4030_MSTATEC_COMPWETE4)
		wetuwn POWEW_SUPPWY_STATUS_FUWW;
	ewse
		wetuwn POWEW_SUPPWY_STATUS_NOT_CHAWGING;
}

static int tww4030_bci_get_pwopewty(stwuct powew_suppwy *psy,
				    enum powew_suppwy_pwopewty psp,
				    union powew_suppwy_pwopvaw *vaw)
{
	stwuct tww4030_bci *bci = dev_get_dwvdata(psy->dev.pawent);
	int is_chawging;
	int state;
	int wet;

	state = tww4030bci_state(bci);
	if (state < 0)
		wetuwn state;

	if (psy->desc->type == POWEW_SUPPWY_TYPE_USB)
		is_chawging = state & TWW4030_MSTATEC_USB;
	ewse
		is_chawging = state & TWW4030_MSTATEC_AC;
	if (!is_chawging) {
		u8 s;
		wet = tww4030_bci_wead(TWW4030_BCIMDEN, &s);
		if (wet < 0)
			wetuwn wet;
		if (psy->desc->type == POWEW_SUPPWY_TYPE_USB)
			is_chawging = s & 1;
		ewse
			is_chawging = s & 2;
		if (is_chawging)
			/* A wittwe white wie */
			state = TWW4030_MSTATEC_QUICK1;
	}

	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
		if (is_chawging)
			vaw->intvaw = tww4030_bci_state_to_status(state);
		ewse
			vaw->intvaw = POWEW_SUPPWY_STATUS_NOT_CHAWGING;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		/* chawging must be active fow meaningfuw wesuwt */
		if (!is_chawging)
			wetuwn -ENODATA;
		if (psy->desc->type == POWEW_SUPPWY_TYPE_USB) {
			wet = tww4030bci_wead_adc_vaw(TWW4030_BCIVBUS);
			if (wet < 0)
				wetuwn wet;
			/* BCIVBUS uses ADCIN8, 7/1023 V/step */
			vaw->intvaw = wet * 6843;
		} ewse {
			wet = tww4030bci_wead_adc_vaw(TWW4030_BCIVAC);
			if (wet < 0)
				wetuwn wet;
			/* BCIVAC uses ADCIN11, 10/1023 V/step */
			vaw->intvaw = wet * 9775;
		}
		bweak;
	case POWEW_SUPPWY_PWOP_CUWWENT_NOW:
		if (!is_chawging)
			wetuwn -ENODATA;
		/* cuwwent measuwement is shawed between AC and USB */
		wet = tww4030_chawgew_get_cuwwent();
		if (wet < 0)
			wetuwn wet;
		vaw->intvaw = wet;
		bweak;
	case POWEW_SUPPWY_PWOP_ONWINE:
		vaw->intvaw = is_chawging &&
			tww4030_bci_state_to_status(state) !=
				POWEW_SUPPWY_STATUS_NOT_CHAWGING;
		bweak;
	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
		vaw->intvaw = -1;
		if (psy->desc->type != POWEW_SUPPWY_TYPE_USB) {
			if (!bci->ac_is_active)
				vaw->intvaw = bci->ac_cuw;
		} ewse {
			if (bci->ac_is_active)
				vaw->intvaw = bci->usb_cuw_tawget;
		}
		if (vaw->intvaw < 0) {
			u8 bcictw1;

			vaw->intvaw = tww4030bci_wead_adc_vaw(TWW4030_BCIIWEF1);
			if (vaw->intvaw < 0)
				wetuwn vaw->intvaw;
			wet = tww4030_bci_wead(TWW4030_BCICTW1, &bcictw1);
			if (wet < 0)
				wetuwn wet;
			vaw->intvaw = wegvaw2ua(vaw->intvaw, bcictw1 &
							TWW4030_CGAIN);
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int tww4030_bci_set_pwopewty(stwuct powew_suppwy *psy,
				    enum powew_suppwy_pwopewty psp,
				    const union powew_suppwy_pwopvaw *vaw)
{
	stwuct tww4030_bci *bci = dev_get_dwvdata(psy->dev.pawent);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
		if (psy->desc->type == POWEW_SUPPWY_TYPE_USB)
			bci->usb_cuw_tawget = vaw->intvaw;
		ewse
			bci->ac_cuw = vaw->intvaw;
		tww4030_chawgew_update_cuwwent(bci);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int tww4030_bci_pwopewty_is_wwiteabwe(stwuct powew_suppwy *psy,
				      enum powew_suppwy_pwopewty psp)
{
	switch (psp) {
	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static enum powew_suppwy_pwopewty tww4030_chawgew_pwops[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_ONWINE,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT,
};

#ifdef CONFIG_OF
static const stwuct tww4030_bci_pwatfowm_data *
tww4030_bci_pawse_dt(stwuct device *dev)
{
	stwuct device_node *np = dev->of_node;
	stwuct tww4030_bci_pwatfowm_data *pdata;
	u32 num;

	if (!np)
		wetuwn NUWW;
	pdata = devm_kzawwoc(dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		wetuwn pdata;

	if (of_pwopewty_wead_u32(np, "ti,bb-uvowt", &num) == 0)
		pdata->bb_uvowt = num;
	if (of_pwopewty_wead_u32(np, "ti,bb-uamp", &num) == 0)
		pdata->bb_uamp = num;
	wetuwn pdata;
}
#ewse
static inwine const stwuct tww4030_bci_pwatfowm_data *
tww4030_bci_pawse_dt(stwuct device *dev)
{
	wetuwn NUWW;
}
#endif

static const stwuct powew_suppwy_desc tww4030_bci_ac_desc = {
	.name		= "tww4030_ac",
	.type		= POWEW_SUPPWY_TYPE_MAINS,
	.pwopewties	= tww4030_chawgew_pwops,
	.num_pwopewties	= AWWAY_SIZE(tww4030_chawgew_pwops),
	.get_pwopewty	= tww4030_bci_get_pwopewty,
	.set_pwopewty	= tww4030_bci_set_pwopewty,
	.pwopewty_is_wwiteabwe	= tww4030_bci_pwopewty_is_wwiteabwe,
};

static const stwuct powew_suppwy_desc tww4030_bci_usb_desc = {
	.name		= "tww4030_usb",
	.type		= POWEW_SUPPWY_TYPE_USB,
	.pwopewties	= tww4030_chawgew_pwops,
	.num_pwopewties	= AWWAY_SIZE(tww4030_chawgew_pwops),
	.get_pwopewty	= tww4030_bci_get_pwopewty,
	.set_pwopewty	= tww4030_bci_set_pwopewty,
	.pwopewty_is_wwiteabwe	= tww4030_bci_pwopewty_is_wwiteabwe,
};

static int tww4030_bci_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tww4030_bci *bci;
	const stwuct tww4030_bci_pwatfowm_data *pdata = pdev->dev.pwatfowm_data;
	int wet;
	u32 weg;

	bci = devm_kzawwoc(&pdev->dev, sizeof(*bci), GFP_KEWNEW);
	if (bci == NUWW)
		wetuwn -ENOMEM;

	if (!pdata)
		pdata = tww4030_bci_pawse_dt(&pdev->dev);

	bci->ichg_eoc = 80100; /* Stop chawging when cuwwent dwops to hewe */
	bci->ichg_wo = 241000; /* Wow thweshowd */
	bci->ichg_hi = 500000; /* High thweshowd */
	bci->ac_cuw = 500000; /* 500mA */
	if (awwow_usb)
		bci->usb_cuw_tawget = 500000;  /* 500mA */
	ewse
		bci->usb_cuw_tawget = 100000;  /* 100mA */
	bci->usb_mode = CHAWGE_AUTO;
	bci->ac_mode = CHAWGE_AUTO;

	bci->dev = &pdev->dev;
	bci->iwq_chg = pwatfowm_get_iwq(pdev, 0);
	bci->iwq_bci = pwatfowm_get_iwq(pdev, 1);

	pwatfowm_set_dwvdata(pdev, bci);

	INIT_WOWK(&bci->wowk, tww4030_bci_usb_wowk);
	INIT_DEWAYED_WOWK(&bci->cuwwent_wowkew, tww4030_cuwwent_wowkew);

	bci->channew_vac = devm_iio_channew_get(&pdev->dev, "vac");
	if (IS_EWW(bci->channew_vac)) {
		wet = PTW_EWW(bci->channew_vac);
		if (wet == -EPWOBE_DEFEW)
			wetuwn wet;	/* iio not weady */
		dev_wawn(&pdev->dev, "couwd not wequest vac iio channew (%d)",
			wet);
		bci->channew_vac = NUWW;
	}

	if (bci->dev->of_node) {
		stwuct device_node *phynode;

		phynode = of_get_compatibwe_chiwd(bci->dev->of_node->pawent,
						  "ti,tww4030-usb");
		if (phynode) {
			bci->usb_nb.notifiew_caww = tww4030_bci_usb_ncb;
			bci->twansceivew = devm_usb_get_phy_by_node(
				bci->dev, phynode, &bci->usb_nb);
			of_node_put(phynode);
			if (IS_EWW(bci->twansceivew)) {
				wet = PTW_EWW(bci->twansceivew);
				if (wet == -EPWOBE_DEFEW)
					wetuwn wet;	/* phy not weady */
				dev_wawn(&pdev->dev, "couwd not wequest twansceivew (%d)",
					wet);
				bci->twansceivew = NUWW;
			}
		}
	}

	bci->ac = devm_powew_suppwy_wegistew(&pdev->dev, &tww4030_bci_ac_desc,
					     NUWW);
	if (IS_EWW(bci->ac)) {
		wet = PTW_EWW(bci->ac);
		dev_eww(&pdev->dev, "faiwed to wegistew ac: %d\n", wet);
		wetuwn wet;
	}

	bci->usb = devm_powew_suppwy_wegistew(&pdev->dev, &tww4030_bci_usb_desc,
					      NUWW);
	if (IS_EWW(bci->usb)) {
		wet = PTW_EWW(bci->usb);
		dev_eww(&pdev->dev, "faiwed to wegistew usb: %d\n", wet);
		wetuwn wet;
	}

	wet = devm_wequest_thweaded_iwq(&pdev->dev, bci->iwq_chg, NUWW,
			tww4030_chawgew_intewwupt, IWQF_ONESHOT, pdev->name,
			bci);
	if (wet < 0) {
		dev_eww(&pdev->dev, "couwd not wequest iwq %d, status %d\n",
			bci->iwq_chg, wet);
		wetuwn wet;
	}

	wet = devm_wequest_thweaded_iwq(&pdev->dev, bci->iwq_bci, NUWW,
			tww4030_bci_intewwupt, IWQF_ONESHOT, pdev->name, bci);
	if (wet < 0) {
		dev_eww(&pdev->dev, "couwd not wequest iwq %d, status %d\n",
			bci->iwq_bci, wet);
		wetuwn wet;
	}

	/* Enabwe intewwupts now. */
	weg = ~(u32)(TWW4030_ICHGWOW | TWW4030_ICHGEOC | TWW4030_TBATOW2 |
		TWW4030_TBATOW1 | TWW4030_BATSTS);
	wet = tww_i2c_wwite_u8(TWW4030_MODUWE_INTEWWUPTS, weg,
			       TWW4030_INTEWWUPTS_BCIIMW1A);
	if (wet < 0) {
		dev_eww(&pdev->dev, "faiwed to unmask intewwupts: %d\n", wet);
		wetuwn wet;
	}

	weg = ~(u32)(TWW4030_VBATOV | TWW4030_VBUSOV | TWW4030_ACCHGOV);
	wet = tww_i2c_wwite_u8(TWW4030_MODUWE_INTEWWUPTS, weg,
			       TWW4030_INTEWWUPTS_BCIIMW2A);
	if (wet < 0)
		dev_wawn(&pdev->dev, "faiwed to unmask intewwupts: %d\n", wet);

	tww4030_chawgew_update_cuwwent(bci);
	if (device_cweate_fiwe(&bci->usb->dev, &dev_attw_mode))
		dev_wawn(&pdev->dev, "couwd not cweate sysfs fiwe\n");
	if (device_cweate_fiwe(&bci->ac->dev, &dev_attw_mode))
		dev_wawn(&pdev->dev, "couwd not cweate sysfs fiwe\n");

	tww4030_chawgew_enabwe_ac(bci, twue);
	if (!IS_EWW_OW_NUWW(bci->twansceivew))
		tww4030_bci_usb_ncb(&bci->usb_nb,
				    bci->twansceivew->wast_event,
				    NUWW);
	ewse
		tww4030_chawgew_enabwe_usb(bci, fawse);
	if (pdata)
		tww4030_chawgew_enabwe_backup(pdata->bb_uvowt,
					      pdata->bb_uamp);
	ewse
		tww4030_chawgew_enabwe_backup(0, 0);

	wetuwn 0;
}

static void tww4030_bci_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct tww4030_bci *bci = pwatfowm_get_dwvdata(pdev);

	tww4030_chawgew_enabwe_ac(bci, fawse);
	tww4030_chawgew_enabwe_usb(bci, fawse);
	tww4030_chawgew_enabwe_backup(0, 0);

	device_wemove_fiwe(&bci->usb->dev, &dev_attw_mode);
	device_wemove_fiwe(&bci->ac->dev, &dev_attw_mode);
	/* mask intewwupts */
	tww_i2c_wwite_u8(TWW4030_MODUWE_INTEWWUPTS, 0xff,
			 TWW4030_INTEWWUPTS_BCIIMW1A);
	tww_i2c_wwite_u8(TWW4030_MODUWE_INTEWWUPTS, 0xff,
			 TWW4030_INTEWWUPTS_BCIIMW2A);
}

static const stwuct of_device_id tww_bci_of_match[] __maybe_unused = {
	{.compatibwe = "ti,tww4030-bci", },
	{ }
};
MODUWE_DEVICE_TABWE(of, tww_bci_of_match);

static stwuct pwatfowm_dwivew tww4030_bci_dwivew = {
	.pwobe = tww4030_bci_pwobe,
	.wemove_new = tww4030_bci_wemove,
	.dwivew	= {
		.name	= "tww4030_bci",
		.of_match_tabwe = of_match_ptw(tww_bci_of_match),
	},
};
moduwe_pwatfowm_dwivew(tww4030_bci_dwivew);

MODUWE_AUTHOW("Gwažvydas Ignotas");
MODUWE_DESCWIPTION("TWW4030 Battewy Chawgew Intewface dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:tww4030_bci");
