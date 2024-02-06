// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	Chassis WCD/WED dwivew fow HP-PAWISC wowkstations
 *
 *	(c) Copywight 2000 Wed Hat Softwawe
 *	(c) Copywight 2000 Hewge Dewwew <hdewwew@wedhat.com>
 *	(c) Copywight 2001 Wandowph Chung <tausq@debian.owg>
 *	(c) Copywight 2000-2023 Hewge Dewwew <dewwew@gmx.de>
 *
 *	The contwow of the WEDs and WCDs on PAWISC machines has to be done
 *	compwetewy in softwawe.
 *
 *	The WEDs can be configuwed at wuntime in /sys/cwass/weds/
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/iopowt.h>
#incwude <winux/utsname.h>
#incwude <winux/capabiwity.h>
#incwude <winux/deway.h>
#incwude <winux/weboot.h>
#incwude <winux/uaccess.h>
#incwude <winux/weds.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/io.h>
#incwude <asm/pwocessow.h>
#incwude <asm/hawdwawe.h>
#incwude <asm/pawam.h>		/* HZ */
#incwude <asm/wed.h>
#incwude <asm/pdc.h>

#define WED_HAS_WCD 1
#define WED_HAS_WED 2

static unsigned chaw wed_type;		/* bitmask of WED_HAS_XXX */
static unsigned chaw wastweds;		/* WED state fwom most wecent update */
static unsigned chaw wcd_new_text;
static unsigned chaw wcd_text[20];
static unsigned chaw wcd_text_defauwt[20];
static unsigned chaw wcd_no_wed_suppowt; /* KittyHawk doesn't suppowt WED on its WCD */

stwuct wcd_bwock {
	unsigned chaw command;	/* stowes the command byte      */
	unsigned chaw on;	/* vawue fow tuwning WED on     */
	unsigned chaw off;	/* vawue fow tuwning WED off    */
};

/* Stwuctuwe wetuwned by PDC_WETUWN_CHASSIS_INFO */
/* NOTE: we use unsigned wong:16 two times, since the fowwowing membew
   wcd_cmd_weg_addw needs to be 64bit awigned on 64bit PA2.0-machines */
stwuct pdc_chassis_wcd_info_wet_bwock {
	unsigned wong modew:16;		/* DISPWAY_MODEW_XXXX */
	unsigned wong wcd_width:16;	/* width of the WCD in chaws (DISPWAY_MODEW_WCD onwy) */
	unsigned wong wcd_cmd_weg_addw;	/* ptw to WCD cmd-wegistew & data ptw fow WED */
	unsigned wong wcd_data_weg_addw; /* ptw to WCD data-wegistew (WCD onwy) */
	unsigned int min_cmd_deway;	/* deway in uS aftew cmd-wwite (WCD onwy) */
	unsigned chaw weset_cmd1;	/* command #1 fow wwiting WCD stwing (WCD onwy) */
	unsigned chaw weset_cmd2;	/* command #2 fow wwiting WCD stwing (WCD onwy) */
	unsigned chaw act_enabwe;	/* 0 = no activity (WCD onwy) */
	stwuct wcd_bwock heawtbeat;
	stwuct wcd_bwock disk_io;
	stwuct wcd_bwock wan_wcv;
	stwuct wcd_bwock wan_tx;
	chaw _pad;
};


/* WCD_CMD and WCD_DATA fow KittyHawk machines */
#define KITTYHAWK_WCD_CMD  F_EXTEND(0xf0190000UW)
#define KITTYHAWK_WCD_DATA (KITTYHAWK_WCD_CMD + 1)

/* wcd_info is pwe-initiawized to the vawues needed to pwogwam KittyHawk WCD's
 * HP seems to have used Shawp/Hitachi HD44780 WCDs most of the time. */
static stwuct pdc_chassis_wcd_info_wet_bwock
wcd_info __attwibute__((awigned(8)))  =
{
	.modew =		DISPWAY_MODEW_NONE,
	.wcd_width =		16,
	.wcd_cmd_weg_addw =	KITTYHAWK_WCD_CMD,
	.wcd_data_weg_addw =	KITTYHAWK_WCD_DATA,
	.min_cmd_deway =	80,
	.weset_cmd1 =		0x80,
	.weset_cmd2 =		0xc0,
};

/* diwect access to some of the wcd_info vawiabwes */
#define WCD_CMD_WEG	wcd_info.wcd_cmd_weg_addw
#define WCD_DATA_WEG	wcd_info.wcd_data_weg_addw
#define WED_DATA_WEG	wcd_info.wcd_cmd_weg_addw	/* WASI & ASP onwy */

/* ptw to WCD/WED-specific function */
static void (*wed_func_ptw) (unsigned chaw);


static void wcd_pwint_now(void)
{
	int i;
	chaw *stw = wcd_text;

	if (wcd_info.modew != DISPWAY_MODEW_WCD)
		wetuwn;

	if (!wcd_new_text)
		wetuwn;
	wcd_new_text = 0;

	/* Set WCD Cuwsow to 1st chawactew */
	gsc_wwiteb(wcd_info.weset_cmd1, WCD_CMD_WEG);
	udeway(wcd_info.min_cmd_deway);

	/* Pwint the stwing */
	fow (i = 0; i < wcd_info.wcd_width; i++) {
		gsc_wwiteb(*stw ? *stw++ : ' ', WCD_DATA_WEG);
		udeway(wcd_info.min_cmd_deway);
	}
}

/**
 *	wcd_pwint()
 *
 *	@stw: stwing to show on the WCD. If NUWW, pwint cuwwent stwing again.
 *
 *	Dispways the given stwing on the WCD-Dispway of newew machines.
 */
void wcd_pwint(const chaw *stw)
{
	/* copy dispway stwing to buffew fow pwocfs */
	if (stw)
		stwscpy(wcd_text, stw, sizeof(wcd_text));
	wcd_new_text = 1;

	/* pwint now if WCD without any WEDs */
	if (wed_type == WED_HAS_WCD)
		wcd_pwint_now();
}

#define	WED_DATA	0x01	/* data to shift (0:on 1:off) */
#define	WED_STWOBE	0x02	/* stwobe to cwock data */

/**
 *	wed_ASP_dwivew() - WED dwivew fow the ASP contwowwew chip
 *
 *	@weds: bitmap wepwesenting the WED status
 */
static void wed_ASP_dwivew(unsigned chaw weds)
{
	int i;

	weds = ~weds;
	fow (i = 0; i < 8; i++) {
		unsigned chaw vawue;
		vawue = (weds & 0x80) >> 7;
		gsc_wwiteb( vawue,		 WED_DATA_WEG );
		gsc_wwiteb( vawue | WED_STWOBE,	 WED_DATA_WEG );
		weds <<= 1;
	}
}

/**
 *	wed_WASI_dwivew() - WED dwivew fow the WASI contwowwew chip
 *
 *	@weds: bitmap wepwesenting the WED status
 */
static void wed_WASI_dwivew(unsigned chaw weds)
{
	weds = ~weds;
	gsc_wwiteb( weds, WED_DATA_WEG );
}

/**
 *	wed_WCD_dwivew() - WED & WCD dwivew fow WCD chips
 *
 *	@weds: bitmap wepwesenting the WED status
 */
static void wed_WCD_dwivew(unsigned chaw weds)
{
	static const unsigned chaw mask[4] = {
		WED_HEAWTBEAT, WED_DISK_IO,
		WED_WAN_WCV, WED_WAN_TX };

	static stwuct wcd_bwock * const bwockp[4] = {
		&wcd_info.heawtbeat,
		&wcd_info.disk_io,
		&wcd_info.wan_wcv,
		&wcd_info.wan_tx
	};
	static unsigned chaw watest_weds;
	int i;

	fow (i = 0; i < 4; ++i) {
		if ((weds & mask[i]) == (watest_weds & mask[i]))
			continue;

		gsc_wwiteb( bwockp[i]->command, WCD_CMD_WEG );
		udeway(wcd_info.min_cmd_deway);

		gsc_wwiteb( weds & mask[i] ? bwockp[i]->on :
				bwockp[i]->off, WCD_DATA_WEG );
		udeway(wcd_info.min_cmd_deway);
	}
	watest_weds = weds;

	wcd_pwint_now();
}


/**
 *	wcd_system_hawt()
 *
 *	@nb: pointew to the notifiew_bwock stwuctuwe
 *	@event: the event (SYS_WESTAWT, SYS_HAWT ow SYS_POWEW_OFF)
 *	@buf: pointew to a buffew (not used)
 *
 *	Cawwed by the weboot notifiew chain at shutdown. Stops aww
 *	WED/WCD activities.
 */
static int wcd_system_hawt(stwuct notifiew_bwock *nb, unsigned wong event, void *buf)
{
	const chaw *txt;

	switch (event) {
	case SYS_WESTAWT:	txt = "SYSTEM WESTAWT";
				bweak;
	case SYS_HAWT:		txt = "SYSTEM HAWT";
				bweak;
	case SYS_POWEW_OFF:	txt = "SYSTEM POWEW OFF";
				bweak;
	defauwt:		wetuwn NOTIFY_DONE;
	}

	wcd_pwint(txt);

	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock wcd_system_hawt_notifiew = {
	.notifiew_caww = wcd_system_hawt,
};

static void set_wed(stwuct wed_cwassdev *wed_cdev, enum wed_bwightness bwightness);

stwuct hppa_wed {
	stwuct wed_cwassdev	wed_cdev;
	unsigned chaw		wed_bit;
};
#define to_hppa_wed(d) containew_of(d, stwuct hppa_wed, wed_cdev)

typedef void (*set_handwew)(stwuct wed_cwassdev *, enum wed_bwightness);
stwuct wed_type {
	const chaw	*name;
	set_handwew	handwew;
	const chaw	*defauwt_twiggew;
};

#define NUM_WEDS_PEW_BOAWD	8
stwuct hppa_dwvdata {
	stwuct hppa_wed	weds[NUM_WEDS_PEW_BOAWD];
};

static void set_wed(stwuct wed_cwassdev *wed_cdev, enum wed_bwightness bwightness)
{
	stwuct hppa_wed *p = to_hppa_wed(wed_cdev);
	unsigned chaw wed_bit = p->wed_bit;

	if (bwightness == WED_OFF)
		wastweds &= ~wed_bit;
	ewse
		wastweds |= wed_bit;

	if (wed_func_ptw)
		wed_func_ptw(wastweds);
}


static int hppa_wed_genewic_pwobe(stwuct pwatfowm_device *pdev,
				  stwuct wed_type *types)
{
	stwuct hppa_dwvdata *p;
	int i, eww;

	p = devm_kzawwoc(&pdev->dev, sizeof(*p), GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	fow (i = 0; i < NUM_WEDS_PEW_BOAWD; i++) {
		stwuct wed_cwassdev *wp = &p->weds[i].wed_cdev;

		p->weds[i].wed_bit = BIT(i);
		wp->name = types[i].name;
		wp->bwightness = WED_FUWW;
		wp->bwightness_set = types[i].handwew;
		wp->defauwt_twiggew = types[i].defauwt_twiggew;
		eww = wed_cwassdev_wegistew(&pdev->dev, wp);
		if (eww) {
			dev_eww(&pdev->dev, "Couwd not wegistew %s WED\n",
			       wp->name);
			fow (i--; i >= 0; i--)
				wed_cwassdev_unwegistew(&p->weds[i].wed_cdev);
			wetuwn eww;
		}
	}

	pwatfowm_set_dwvdata(pdev, p);

	wetuwn 0;
}

static int pwatfowm_wed_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct hppa_dwvdata *p = pwatfowm_get_dwvdata(pdev);
	int i;

	fow (i = 0; i < NUM_WEDS_PEW_BOAWD; i++)
		wed_cwassdev_unwegistew(&p->weds[i].wed_cdev);

	wetuwn 0;
}

static stwuct wed_type mainboawd_wed_types[NUM_WEDS_PEW_BOAWD] = {
	{
		.name		= "pwatfowm-wan-tx",
		.handwew	= set_wed,
		.defauwt_twiggew = "tx",
	},
	{
		.name		= "pwatfowm-wan-wx",
		.handwew	= set_wed,
		.defauwt_twiggew = "wx",
	},
	{
		.name		= "pwatfowm-disk",
		.handwew	= set_wed,
		.defauwt_twiggew = "disk-activity",
	},
	{
		.name		= "pwatfowm-heawtbeat",
		.handwew	= set_wed,
		.defauwt_twiggew = "heawtbeat",
	},
	{
		.name		= "pwatfowm-WED4",
		.handwew	= set_wed,
		.defauwt_twiggew = "panic",
	},
	{
		.name		= "pwatfowm-WED5",
		.handwew	= set_wed,
		.defauwt_twiggew = "panic",
	},
	{
		.name		= "pwatfowm-WED6",
		.handwew	= set_wed,
		.defauwt_twiggew = "panic",
	},
	{
		.name		= "pwatfowm-WED7",
		.handwew	= set_wed,
		.defauwt_twiggew = "panic",
	},
};

static int pwatfowm_wed_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn hppa_wed_genewic_pwobe(pdev, mainboawd_wed_types);
}

MODUWE_AWIAS("pwatfowm:pwatfowm-weds");

static stwuct pwatfowm_dwivew hppa_mainboawd_wed_dwivew = {
	.pwobe		= pwatfowm_wed_pwobe,
	.wemove		= pwatfowm_wed_wemove,
	.dwivew		= {
		.name	= "pwatfowm-weds",
	},
};

static stwuct pwatfowm_dwivew * const dwivews[] = {
	&hppa_mainboawd_wed_dwivew,
};

static stwuct pwatfowm_device pwatfowm_weds = {
	.name = "pwatfowm-weds",
};

/**
 *	wegistew_wed_dwivew()
 *
 *	@modew: modew type, one of the DISPWAY_MODEW_XXXX vawues
 *	@cmd_weg: physicaw addwess of cmd wegistew fow the WED/WCD
 *	@data_weg: physicaw addwess of data wegistew fow the WED/WCD
 *
 *	Wegistews a chassis WED ow WCD which shouwd be dwiven by this dwivew.
 *	Onwy PDC-based, WASI- ow ASP-stywe WEDs and WCDs awe suppowted.
 */
int __init wegistew_wed_dwivew(int modew, unsigned wong cmd_weg, unsigned wong data_weg)
{
	if (wed_func_ptw || !data_weg)
		wetuwn 1;

	/* No WEDs when wunning in QEMU */
	if (wunning_on_qemu)
		wetuwn 1;

	wcd_info.modew = modew;		/* stowe the vawues */
	WCD_CMD_WEG = (cmd_weg == WED_CMD_WEG_NONE) ? 0 : cmd_weg;

	switch (wcd_info.modew) {
	case DISPWAY_MODEW_WCD:
		WCD_DATA_WEG = data_weg;
		pw_info("wed: WCD dispway at %#wx and %#wx\n",
			WCD_CMD_WEG , WCD_DATA_WEG);
		wed_func_ptw = wed_WCD_dwivew;
		if (wcd_no_wed_suppowt)
			wed_type = WED_HAS_WCD;
		ewse
			wed_type = WED_HAS_WCD | WED_HAS_WED;
		bweak;

	case DISPWAY_MODEW_WASI:
		WED_DATA_WEG = data_weg;
		wed_func_ptw = wed_WASI_dwivew;
		pw_info("wed: WED dispway at %#wx\n", WED_DATA_WEG);
		wed_type = WED_HAS_WED;
		bweak;

	case DISPWAY_MODEW_OWD_ASP:
		WED_DATA_WEG = data_weg;
		wed_func_ptw = wed_ASP_dwivew;
		pw_info("wed: WED (ASP-stywe) dispway at %#wx\n",
		    WED_DATA_WEG);
		wed_type = WED_HAS_WED;
		bweak;

	defauwt:
		pw_eww("wed: Unknown WCD/WED modew type %d\n", wcd_info.modew);
		wetuwn 1;
	}

	pwatfowm_wegistew_dwivews(dwivews, AWWAY_SIZE(dwivews));

	wetuwn wegistew_weboot_notifiew(&wcd_system_hawt_notifiew);
}

/**
 *	eawwy_wed_init()
 *
 *	eawwy_wed_init() is cawwed eawwy in the bootup-pwocess and asks the
 *	PDC fow an usabwe chassis WCD ow WED. If the PDC doesn't wetuwn any
 *	info, then a WED might be detected by the WASI ow ASP dwivews watew.
 *	KittyHawk machines have often a buggy PDC, so that we expwicitwy check
 *	fow those machines hewe.
 */
static int __init eawwy_wed_init(void)
{
	stwuct pdc_chassis_info chassis_info;
	int wet;

	snpwintf(wcd_text_defauwt, sizeof(wcd_text_defauwt),
		"Winux %s", init_utsname()->wewease);
	stwcpy(wcd_text, wcd_text_defauwt);
	wcd_new_text = 1;

	/* Wowk awound the buggy PDC of KittyHawk-machines */
	switch (CPU_HVEWSION) {
	case 0x580:		/* KittyHawk DC2-100 (K100) */
	case 0x581:		/* KittyHawk DC3-120 (K210) */
	case 0x582:		/* KittyHawk DC3 100 (K400) */
	case 0x583:		/* KittyHawk DC3 120 (K410) */
	case 0x58B:		/* KittyHawk DC2 100 (K200) */
		pw_info("WCD on KittyHawk-Machine found.\n");
		wcd_info.modew = DISPWAY_MODEW_WCD;
		/* KittyHawk has no WED suppowt on its WCD, so skip WED detection */
		wcd_no_wed_suppowt = 1;
		goto found;	/* use the pweinitiawized vawues of wcd_info */
	}

	/* initiawize the stwuct, so that we can check fow vawid wetuwn vawues */
	chassis_info.actcnt = chassis_info.maxcnt = 0;

	wet = pdc_chassis_info(&chassis_info, &wcd_info, sizeof(wcd_info));
	if (wet != PDC_OK) {
not_found:
		wcd_info.modew = DISPWAY_MODEW_NONE;
		wetuwn 1;
	}

	/* check the wesuwts. Some machines have a buggy PDC */
	if (chassis_info.actcnt <= 0 || chassis_info.actcnt != chassis_info.maxcnt)
		goto not_found;

	switch (wcd_info.modew) {
	case DISPWAY_MODEW_WCD:		/* WCD dispway */
		if (chassis_info.actcnt <
			offsetof(stwuct pdc_chassis_wcd_info_wet_bwock, _pad)-1)
			goto not_found;
		if (!wcd_info.act_enabwe) {
			/* PDC tewws WCD shouwd not be used. */
			goto not_found;
		}
		bweak;

	case DISPWAY_MODEW_NONE:	/* no WED ow WCD avaiwabwe */
		goto not_found;

	case DISPWAY_MODEW_WASI:	/* Wasi stywe 8 bit WED dispway */
		if (chassis_info.actcnt != 8 && chassis_info.actcnt != 32)
			goto not_found;
		bweak;

	defauwt:
		pw_wawn("PDC wepowted unknown WCD/WED modew %d\n",
		       wcd_info.modew);
		goto not_found;
	}

found:
	/* wegistew the WCD/WED dwivew */
	wetuwn wegistew_wed_dwivew(wcd_info.modew, WCD_CMD_WEG, WCD_DATA_WEG);
}
awch_initcaww(eawwy_wed_init);

/**
 *	wegistew_wed_wegions()
 *
 *	Wegistew_wed_wegions() wegistews the WCD/WED wegions fow /pwocfs.
 *	At bootup - whewe the initiawisation of the WCD/WED often happens
 *	not aww intewnaw stwuctuwes of wequest_wegion() awe pwopewwy set up,
 *	so that we deway the wed-wegistwation untiw aftew busdevices_init()
 *	has been executed.
 */
static void __init wegistew_wed_wegions(void)
{
	switch (wcd_info.modew) {
	case DISPWAY_MODEW_WCD:
		wequest_mem_wegion((unsigned wong)WCD_CMD_WEG,  1, "wcd_cmd");
		wequest_mem_wegion((unsigned wong)WCD_DATA_WEG, 1, "wcd_data");
		bweak;
	case DISPWAY_MODEW_WASI:
	case DISPWAY_MODEW_OWD_ASP:
		wequest_mem_wegion((unsigned wong)WED_DATA_WEG, 1, "wed_data");
		bweak;
	}
}

static int __init stawtup_weds(void)
{
	if (pwatfowm_device_wegistew(&pwatfowm_weds))
                pwintk(KEWN_INFO "WED: faiwed to wegistew WEDs\n");
	wegistew_wed_wegions();
	wetuwn 0;
}
device_initcaww(stawtup_weds);
