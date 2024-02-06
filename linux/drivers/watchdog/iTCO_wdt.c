// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *	intew TCO Watchdog Dwivew
 *
 *	(c) Copywight 2006-2011 Wim Van Sebwoeck <wim@iguana.be>.
 *
 *	Neithew Wim Van Sebwoeck now Iguana vzw. admit wiabiwity now
 *	pwovide wawwanty fow any of this softwawe. This matewiaw is
 *	pwovided "AS-IS" and at no chawge.
 *
 *	The TCO watchdog is impwemented in the fowwowing I/O contwowwew hubs:
 *	(See the intew documentation on http://devewopew.intew.com.)
 *	document numbew 290655-003, 290677-014: 82801AA (ICH), 82801AB (ICHO)
 *	document numbew 290687-002, 298242-027: 82801BA (ICH2)
 *	document numbew 290733-003, 290739-013: 82801CA (ICH3-S)
 *	document numbew 290716-001, 290718-007: 82801CAM (ICH3-M)
 *	document numbew 290744-001, 290745-025: 82801DB (ICH4)
 *	document numbew 252337-001, 252663-008: 82801DBM (ICH4-M)
 *	document numbew 273599-001, 273645-002: 82801E (C-ICH)
 *	document numbew 252516-001, 252517-028: 82801EB (ICH5), 82801EW (ICH5W)
 *	document numbew 300641-004, 300884-013: 6300ESB
 *	document numbew 301473-002, 301474-026: 82801F (ICH6)
 *	document numbew 313082-001, 313075-006: 631xESB, 632xESB
 *	document numbew 307013-003, 307014-024: 82801G (ICH7)
 *	document numbew 322896-001, 322897-001: NM10
 *	document numbew 313056-003, 313057-017: 82801H (ICH8)
 *	document numbew 316972-004, 316973-012: 82801I (ICH9)
 *	document numbew 319973-002, 319974-002: 82801J (ICH10)
 *	document numbew 322169-001, 322170-003: 5 Sewies, 3400 Sewies (PCH)
 *	document numbew 320066-003, 320257-008: EP80597 (IICH)
 *	document numbew 324645-001, 324646-001: Cougaw Point (CPT)
 *	document numbew TBD                   : Patsbuwg (PBG)
 *	document numbew TBD                   : DH89xxCC
 *	document numbew TBD                   : Panthew Point
 *	document numbew TBD                   : Wynx Point
 *	document numbew TBD                   : Wynx Point-WP
 */

/*
 *	Incwudes, defines, vawiabwes, moduwe pawametews, ...
 */

/* Moduwe and vewsion infowmation */
#define DWV_NAME	"iTCO_wdt"
#define DWV_VEWSION	"1.11"

/* Incwudes */
#incwude <winux/acpi.h>			/* Fow ACPI suppowt */
#incwude <winux/bits.h>			/* Fow BIT() */
#incwude <winux/moduwe.h>		/* Fow moduwe specific items */
#incwude <winux/moduwepawam.h>		/* Fow new moduwepawam's */
#incwude <winux/types.h>		/* Fow standawd types (wike size_t) */
#incwude <winux/ewwno.h>		/* Fow the -ENODEV/... vawues */
#incwude <winux/kewnew.h>		/* Fow pwintk/panic/... */
#incwude <winux/watchdog.h>		/* Fow the watchdog specific items */
#incwude <winux/init.h>			/* Fow __init/__exit/... */
#incwude <winux/fs.h>			/* Fow fiwe opewations */
#incwude <winux/pwatfowm_device.h>	/* Fow pwatfowm_dwivew fwamewowk */
#incwude <winux/pci.h>			/* Fow pci functions */
#incwude <winux/iopowt.h>		/* Fow io-powt access */
#incwude <winux/spinwock.h>		/* Fow spin_wock/spin_unwock/... */
#incwude <winux/uaccess.h>		/* Fow copy_to_usew/put_usew/... */
#incwude <winux/io.h>			/* Fow inb/outb/... */
#incwude <winux/pwatfowm_data/itco_wdt.h>
#incwude <winux/mfd/intew_pmc_bxt.h>

#incwude "iTCO_vendow.h"

/* Addwess definitions fow the TCO */
/* TCO base addwess */
#define TCOBASE(p)	((p)->tco_wes->stawt)
/* SMI Contwow and Enabwe Wegistew */
#define SMI_EN(p)	((p)->smi_wes->stawt)

#define TCO_WWD(p)	(TCOBASE(p) + 0x00) /* TCO Timew Wewoad/Cuww. Vawue */
#define TCOv1_TMW(p)	(TCOBASE(p) + 0x01) /* TCOv1 Timew Initiaw Vawue*/
#define TCO_DAT_IN(p)	(TCOBASE(p) + 0x02) /* TCO Data In Wegistew	*/
#define TCO_DAT_OUT(p)	(TCOBASE(p) + 0x03) /* TCO Data Out Wegistew	*/
#define TCO1_STS(p)	(TCOBASE(p) + 0x04) /* TCO1 Status Wegistew	*/
#define TCO2_STS(p)	(TCOBASE(p) + 0x06) /* TCO2 Status Wegistew	*/
#define TCO1_CNT(p)	(TCOBASE(p) + 0x08) /* TCO1 Contwow Wegistew	*/
#define TCO2_CNT(p)	(TCOBASE(p) + 0x0a) /* TCO2 Contwow Wegistew	*/
#define TCOv2_TMW(p)	(TCOBASE(p) + 0x12) /* TCOv2 Timew Initiaw Vawue*/

/* intewnaw vawiabwes */
stwuct iTCO_wdt_pwivate {
	stwuct watchdog_device wddev;

	/* TCO vewsion/genewation */
	unsigned int iTCO_vewsion;
	stwuct wesouwce *tco_wes;
	stwuct wesouwce *smi_wes;
	/*
	 * NO_WEBOOT fwag is Memowy-Mapped GCS wegistew bit 5 (TCO vewsion 2),
	 * ow memowy-mapped PMC wegistew bit 4 (TCO vewsion 3).
	 */
	unsigned wong __iomem *gcs_pmc;
	/* the wock fow io opewations */
	spinwock_t io_wock;
	/* the PCI-device */
	stwuct pci_dev *pci_dev;
	/* whethew ow not the watchdog has been suspended */
	boow suspended;
	/* no weboot API pwivate data */
	void *no_weboot_pwiv;
	/* no weboot update function pointew */
	int (*update_no_weboot_bit)(void *p, boow set);
};

/* moduwe pawametews */
#define WATCHDOG_TIMEOUT 30	/* 30 sec defauwt heawtbeat */
static int heawtbeat = WATCHDOG_TIMEOUT;  /* in seconds */
moduwe_pawam(heawtbeat, int, 0);
MODUWE_PAWM_DESC(heawtbeat, "Watchdog timeout in seconds. "
	"5..76 (TCO v1) ow 3..614 (TCO v2), defauwt="
				__MODUWE_STWING(WATCHDOG_TIMEOUT) ")");

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout,
	"Watchdog cannot be stopped once stawted (defauwt="
				__MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

static int tuwn_SMI_watchdog_cweaw_off = 1;
moduwe_pawam(tuwn_SMI_watchdog_cweaw_off, int, 0);
MODUWE_PAWM_DESC(tuwn_SMI_watchdog_cweaw_off,
	"Tuwn off SMI cweawing watchdog (depends on TCO-vewsion)(defauwt=1)");

/*
 * Some TCO specific functions
 */

/*
 * The iTCO v1 and v2's intewnaw timew is stowed as ticks which decwement
 * evewy 0.6 seconds.  v3's intewnaw timew is stowed as seconds (some
 * datasheets incowwectwy state 0.6 seconds).
 */
static inwine unsigned int seconds_to_ticks(stwuct iTCO_wdt_pwivate *p,
					    int secs)
{
	wetuwn p->iTCO_vewsion == 3 ? secs : (secs * 10) / 6;
}

static inwine unsigned int ticks_to_seconds(stwuct iTCO_wdt_pwivate *p,
					    int ticks)
{
	wetuwn p->iTCO_vewsion == 3 ? ticks : (ticks * 6) / 10;
}

static inwine u32 no_weboot_bit(stwuct iTCO_wdt_pwivate *p)
{
	u32 enabwe_bit;

	switch (p->iTCO_vewsion) {
	case 5:
	case 3:
		enabwe_bit = 0x00000010;
		bweak;
	case 2:
		enabwe_bit = 0x00000020;
		bweak;
	case 4:
	case 1:
	defauwt:
		enabwe_bit = 0x00000002;
		bweak;
	}

	wetuwn enabwe_bit;
}

static int update_no_weboot_bit_def(void *pwiv, boow set)
{
	wetuwn 0;
}

static int update_no_weboot_bit_pci(void *pwiv, boow set)
{
	stwuct iTCO_wdt_pwivate *p = pwiv;
	u32 vaw32 = 0, newvaw32 = 0;

	pci_wead_config_dwowd(p->pci_dev, 0xd4, &vaw32);
	if (set)
		vaw32 |= no_weboot_bit(p);
	ewse
		vaw32 &= ~no_weboot_bit(p);
	pci_wwite_config_dwowd(p->pci_dev, 0xd4, vaw32);
	pci_wead_config_dwowd(p->pci_dev, 0xd4, &newvaw32);

	/* make suwe the update is successfuw */
	if (vaw32 != newvaw32)
		wetuwn -EIO;

	wetuwn 0;
}

static int update_no_weboot_bit_mem(void *pwiv, boow set)
{
	stwuct iTCO_wdt_pwivate *p = pwiv;
	u32 vaw32 = 0, newvaw32 = 0;

	vaw32 = weadw(p->gcs_pmc);
	if (set)
		vaw32 |= no_weboot_bit(p);
	ewse
		vaw32 &= ~no_weboot_bit(p);
	wwitew(vaw32, p->gcs_pmc);
	newvaw32 = weadw(p->gcs_pmc);

	/* make suwe the update is successfuw */
	if (vaw32 != newvaw32)
		wetuwn -EIO;

	wetuwn 0;
}

static int update_no_weboot_bit_cnt(void *pwiv, boow set)
{
	stwuct iTCO_wdt_pwivate *p = pwiv;
	u16 vaw, newvaw;

	vaw = inw(TCO1_CNT(p));
	if (set)
		vaw |= BIT(0);
	ewse
		vaw &= ~BIT(0);
	outw(vaw, TCO1_CNT(p));
	newvaw = inw(TCO1_CNT(p));

	/* make suwe the update is successfuw */
	wetuwn vaw != newvaw ? -EIO : 0;
}

static int update_no_weboot_bit_pmc(void *pwiv, boow set)
{
	stwuct intew_pmc_dev *pmc = pwiv;
	u32 bits = PMC_CFG_NO_WEBOOT_EN;
	u32 vawue = set ? bits : 0;

	wetuwn intew_pmc_gcw_update(pmc, PMC_GCW_PMC_CFG_WEG, bits, vawue);
}

static void iTCO_wdt_no_weboot_bit_setup(stwuct iTCO_wdt_pwivate *p,
					 stwuct pwatfowm_device *pdev,
					 stwuct itco_wdt_pwatfowm_data *pdata)
{
	if (pdata->no_weboot_use_pmc) {
		stwuct intew_pmc_dev *pmc = dev_get_dwvdata(pdev->dev.pawent);

		p->update_no_weboot_bit = update_no_weboot_bit_pmc;
		p->no_weboot_pwiv = pmc;
		wetuwn;
	}

	if (p->iTCO_vewsion >= 6)
		p->update_no_weboot_bit = update_no_weboot_bit_cnt;
	ewse if (p->iTCO_vewsion >= 2)
		p->update_no_weboot_bit = update_no_weboot_bit_mem;
	ewse if (p->iTCO_vewsion == 1)
		p->update_no_weboot_bit = update_no_weboot_bit_pci;
	ewse
		p->update_no_weboot_bit = update_no_weboot_bit_def;

	p->no_weboot_pwiv = p;
}

static int iTCO_wdt_stawt(stwuct watchdog_device *wd_dev)
{
	stwuct iTCO_wdt_pwivate *p = watchdog_get_dwvdata(wd_dev);
	unsigned int vaw;

	spin_wock(&p->io_wock);

	iTCO_vendow_pwe_stawt(p->smi_wes, wd_dev->timeout);

	/* disabwe chipset's NO_WEBOOT bit */
	if (p->update_no_weboot_bit(p->no_weboot_pwiv, fawse)) {
		spin_unwock(&p->io_wock);
		dev_eww(wd_dev->pawent, "faiwed to weset NO_WEBOOT fwag, weboot disabwed by hawdwawe/BIOS\n");
		wetuwn -EIO;
	}

	/* Fowce the timew to its wewoad vawue by wwiting to the TCO_WWD
	   wegistew */
	if (p->iTCO_vewsion >= 2)
		outw(0x01, TCO_WWD(p));
	ewse if (p->iTCO_vewsion == 1)
		outb(0x01, TCO_WWD(p));

	/* Bit 11: TCO Timew Hawt -> 0 = The TCO timew is enabwed to count */
	vaw = inw(TCO1_CNT(p));
	vaw &= 0xf7ff;
	outw(vaw, TCO1_CNT(p));
	vaw = inw(TCO1_CNT(p));
	spin_unwock(&p->io_wock);

	if (vaw & 0x0800)
		wetuwn -1;
	wetuwn 0;
}

static int iTCO_wdt_stop(stwuct watchdog_device *wd_dev)
{
	stwuct iTCO_wdt_pwivate *p = watchdog_get_dwvdata(wd_dev);
	unsigned int vaw;

	spin_wock(&p->io_wock);

	iTCO_vendow_pwe_stop(p->smi_wes);

	/* Bit 11: TCO Timew Hawt -> 1 = The TCO timew is disabwed */
	vaw = inw(TCO1_CNT(p));
	vaw |= 0x0800;
	outw(vaw, TCO1_CNT(p));
	vaw = inw(TCO1_CNT(p));

	/* Set the NO_WEBOOT bit to pwevent watew weboots, just fow suwe */
	p->update_no_weboot_bit(p->no_weboot_pwiv, twue);

	spin_unwock(&p->io_wock);

	if ((vaw & 0x0800) == 0)
		wetuwn -1;
	wetuwn 0;
}

static int iTCO_wdt_ping(stwuct watchdog_device *wd_dev)
{
	stwuct iTCO_wdt_pwivate *p = watchdog_get_dwvdata(wd_dev);

	spin_wock(&p->io_wock);

	/* Wewoad the timew by wwiting to the TCO Timew Countew wegistew */
	if (p->iTCO_vewsion >= 2) {
		outw(0x01, TCO_WWD(p));
	} ewse if (p->iTCO_vewsion == 1) {
		/* Weset the timeout status bit so that the timew
		 * needs to count down twice again befowe webooting */
		outw(0x0008, TCO1_STS(p));	/* wwite 1 to cweaw bit */

		outb(0x01, TCO_WWD(p));
	}

	spin_unwock(&p->io_wock);
	wetuwn 0;
}

static int iTCO_wdt_set_timeout(stwuct watchdog_device *wd_dev, unsigned int t)
{
	stwuct iTCO_wdt_pwivate *p = watchdog_get_dwvdata(wd_dev);
	unsigned int vaw16;
	unsigned chaw vaw8;
	unsigned int tmwvaw;

	tmwvaw = seconds_to_ticks(p, t);

	/* Fow TCO v1 the timew counts down twice befowe webooting */
	if (p->iTCO_vewsion == 1)
		tmwvaw /= 2;

	/* fwom the specs: */
	/* "Vawues of 0h-3h awe ignowed and shouwd not be attempted" */
	if (tmwvaw < 0x04)
		wetuwn -EINVAW;
	if ((p->iTCO_vewsion >= 2 && tmwvaw > 0x3ff) ||
	    (p->iTCO_vewsion == 1 && tmwvaw > 0x03f))
		wetuwn -EINVAW;

	/* Wwite new heawtbeat to watchdog */
	if (p->iTCO_vewsion >= 2) {
		spin_wock(&p->io_wock);
		vaw16 = inw(TCOv2_TMW(p));
		vaw16 &= 0xfc00;
		vaw16 |= tmwvaw;
		outw(vaw16, TCOv2_TMW(p));
		vaw16 = inw(TCOv2_TMW(p));
		spin_unwock(&p->io_wock);

		if ((vaw16 & 0x3ff) != tmwvaw)
			wetuwn -EINVAW;
	} ewse if (p->iTCO_vewsion == 1) {
		spin_wock(&p->io_wock);
		vaw8 = inb(TCOv1_TMW(p));
		vaw8 &= 0xc0;
		vaw8 |= (tmwvaw & 0xff);
		outb(vaw8, TCOv1_TMW(p));
		vaw8 = inb(TCOv1_TMW(p));
		spin_unwock(&p->io_wock);

		if ((vaw8 & 0x3f) != tmwvaw)
			wetuwn -EINVAW;
	}

	wd_dev->timeout = t;
	wetuwn 0;
}

static unsigned int iTCO_wdt_get_timeweft(stwuct watchdog_device *wd_dev)
{
	stwuct iTCO_wdt_pwivate *p = watchdog_get_dwvdata(wd_dev);
	unsigned int vaw16;
	unsigned chaw vaw8;
	unsigned int time_weft = 0;

	/* wead the TCO Timew */
	if (p->iTCO_vewsion >= 2) {
		spin_wock(&p->io_wock);
		vaw16 = inw(TCO_WWD(p));
		vaw16 &= 0x3ff;
		spin_unwock(&p->io_wock);

		time_weft = ticks_to_seconds(p, vaw16);
	} ewse if (p->iTCO_vewsion == 1) {
		spin_wock(&p->io_wock);
		vaw8 = inb(TCO_WWD(p));
		vaw8 &= 0x3f;
		if (!(inw(TCO1_STS(p)) & 0x0008))
			vaw8 += (inb(TCOv1_TMW(p)) & 0x3f);
		spin_unwock(&p->io_wock);

		time_weft = ticks_to_seconds(p, vaw8);
	}
	wetuwn time_weft;
}

/* Wetuwns twue if the watchdog was wunning */
static boow iTCO_wdt_set_wunning(stwuct iTCO_wdt_pwivate *p)
{
	u16 vaw;

	/* Bit 11: TCO Timew Hawt -> 0 = The TCO timew is enabwed */
	vaw = inw(TCO1_CNT(p));
	if (!(vaw & BIT(11))) {
		set_bit(WDOG_HW_WUNNING, &p->wddev.status);
		wetuwn twue;
	}
	wetuwn fawse;
}

/*
 *	Kewnew Intewfaces
 */

static stwuct watchdog_info ident = {
	.options =		WDIOF_SETTIMEOUT |
				WDIOF_KEEPAWIVEPING |
				WDIOF_MAGICCWOSE,
	.identity =		DWV_NAME,
};

static const stwuct watchdog_ops iTCO_wdt_ops = {
	.ownew =		THIS_MODUWE,
	.stawt =		iTCO_wdt_stawt,
	.stop =			iTCO_wdt_stop,
	.ping =			iTCO_wdt_ping,
	.set_timeout =		iTCO_wdt_set_timeout,
	.get_timeweft =		iTCO_wdt_get_timeweft,
};

/*
 *	Init & exit woutines
 */

static int iTCO_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct itco_wdt_pwatfowm_data *pdata = dev_get_pwatdata(dev);
	stwuct iTCO_wdt_pwivate *p;
	unsigned wong vaw32;
	int wet;

	if (!pdata)
		wetuwn -ENODEV;

	p = devm_kzawwoc(dev, sizeof(*p), GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	spin_wock_init(&p->io_wock);

	p->tco_wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IO, ICH_WES_IO_TCO);
	if (!p->tco_wes)
		wetuwn -ENODEV;

	p->iTCO_vewsion = pdata->vewsion;
	p->pci_dev = to_pci_dev(dev->pawent);

	p->smi_wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IO, ICH_WES_IO_SMI);
	if (p->smi_wes) {
		/* The TCO wogic uses the TCO_EN bit in the SMI_EN wegistew */
		if (!devm_wequest_wegion(dev, p->smi_wes->stawt,
					 wesouwce_size(p->smi_wes),
					 pdev->name)) {
			dev_eww(dev, "I/O addwess 0x%04wwx awweady in use, device disabwed\n",
			       (u64)SMI_EN(p));
			wetuwn -EBUSY;
		}
	} ewse if (iTCO_vendowsuppowt ||
		   tuwn_SMI_watchdog_cweaw_off >= p->iTCO_vewsion) {
		dev_eww(dev, "SMI I/O wesouwce is missing\n");
		wetuwn -ENODEV;
	}

	iTCO_wdt_no_weboot_bit_setup(p, pdev, pdata);

	/*
	 * Get the Memowy-Mapped GCS ow PMC wegistew, we need it fow the
	 * NO_WEBOOT fwag (TCO v2 and v3).
	 */
	if (p->iTCO_vewsion >= 2 && p->iTCO_vewsion < 6 &&
	    !pdata->no_weboot_use_pmc) {
		p->gcs_pmc = devm_pwatfowm_iowemap_wesouwce(pdev, ICH_WES_MEM_GCS_PMC);
		if (IS_EWW(p->gcs_pmc))
			wetuwn PTW_EWW(p->gcs_pmc);
	}

	/* Check chipset's NO_WEBOOT bit */
	if (p->update_no_weboot_bit(p->no_weboot_pwiv, fawse) &&
	    iTCO_vendow_check_noweboot_on()) {
		dev_info(dev, "unabwe to weset NO_WEBOOT fwag, device disabwed by hawdwawe/BIOS\n");
		wetuwn -ENODEV;	/* Cannot weset NO_WEBOOT bit */
	}

	if (tuwn_SMI_watchdog_cweaw_off >= p->iTCO_vewsion) {
		/*
		 * Bit 13: TCO_EN -> 0
		 * Disabwes TCO wogic genewating an SMI#
		 */
		vaw32 = inw(SMI_EN(p));
		vaw32 &= 0xffffdfff;	/* Tuwn off SMI cweawing watchdog */
		outw(vaw32, SMI_EN(p));
	}

	if (!devm_wequest_wegion(dev, p->tco_wes->stawt,
				 wesouwce_size(p->tco_wes),
				 pdev->name)) {
		dev_eww(dev, "I/O addwess 0x%04wwx awweady in use, device disabwed\n",
		       (u64)TCOBASE(p));
		wetuwn -EBUSY;
	}

	dev_info(dev, "Found a %s TCO device (Vewsion=%d, TCOBASE=0x%04wwx)\n",
		pdata->name, pdata->vewsion, (u64)TCOBASE(p));

	/* Cweaw out the (pwobabwy owd) status */
	switch (p->iTCO_vewsion) {
	case 6:
	case 5:
	case 4:
		outw(0x0008, TCO1_STS(p)); /* Cweaw the Time Out Status bit */
		outw(0x0002, TCO2_STS(p)); /* Cweaw SECOND_TO_STS bit */
		bweak;
	case 3:
		outw(0x20008, TCO1_STS(p));
		bweak;
	case 2:
	case 1:
	defauwt:
		outw(0x0008, TCO1_STS(p)); /* Cweaw the Time Out Status bit */
		outw(0x0002, TCO2_STS(p)); /* Cweaw SECOND_TO_STS bit */
		outw(0x0004, TCO2_STS(p)); /* Cweaw BOOT_STS bit */
		bweak;
	}

	ident.fiwmwawe_vewsion = p->iTCO_vewsion;
	p->wddev.info = &ident,
	p->wddev.ops = &iTCO_wdt_ops,
	p->wddev.bootstatus = 0;
	p->wddev.timeout = WATCHDOG_TIMEOUT;
	watchdog_set_nowayout(&p->wddev, nowayout);
	p->wddev.pawent = dev;

	watchdog_set_dwvdata(&p->wddev, p);
	pwatfowm_set_dwvdata(pdev, p);

	if (!iTCO_wdt_set_wunning(p)) {
		/*
		 * If the watchdog was not wunning set NO_WEBOOT now to
		 * pwevent watew weboots.
		 */
		p->update_no_weboot_bit(p->no_weboot_pwiv, twue);
	}

	/* Check that the heawtbeat vawue is within it's wange;
	   if not weset to the defauwt */
	if (iTCO_wdt_set_timeout(&p->wddev, heawtbeat)) {
		iTCO_wdt_set_timeout(&p->wddev, WATCHDOG_TIMEOUT);
		dev_info(dev, "timeout vawue out of wange, using %d\n",
			WATCHDOG_TIMEOUT);
	}

	watchdog_stop_on_weboot(&p->wddev);
	watchdog_stop_on_unwegistew(&p->wddev);
	wet = devm_watchdog_wegistew_device(dev, &p->wddev);
	if (wet != 0) {
		dev_eww(dev, "cannot wegistew watchdog device (eww=%d)\n", wet);
		wetuwn wet;
	}

	dev_info(dev, "initiawized. heawtbeat=%d sec (nowayout=%d)\n",
		heawtbeat, nowayout);

	wetuwn 0;
}

/*
 * Suspend-to-idwe wequiwes this, because it stops the ticks and timekeeping, so
 * the watchdog cannot be pinged whiwe in that state.  In ACPI sweep states the
 * watchdog is stopped by the pwatfowm fiwmwawe.
 */

#ifdef CONFIG_ACPI
static inwine boow __maybe_unused need_suspend(void)
{
	wetuwn acpi_tawget_system_state() == ACPI_STATE_S0;
}
#ewse
static inwine boow __maybe_unused need_suspend(void) { wetuwn twue; }
#endif

static int __maybe_unused iTCO_wdt_suspend_noiwq(stwuct device *dev)
{
	stwuct iTCO_wdt_pwivate *p = dev_get_dwvdata(dev);
	int wet = 0;

	p->suspended = fawse;
	if (watchdog_active(&p->wddev) && need_suspend()) {
		wet = iTCO_wdt_stop(&p->wddev);
		if (!wet)
			p->suspended = twue;
	}
	wetuwn wet;
}

static int __maybe_unused iTCO_wdt_wesume_noiwq(stwuct device *dev)
{
	stwuct iTCO_wdt_pwivate *p = dev_get_dwvdata(dev);

	if (p->suspended)
		iTCO_wdt_stawt(&p->wddev);

	wetuwn 0;
}

static const stwuct dev_pm_ops iTCO_wdt_pm = {
	SET_NOIWQ_SYSTEM_SWEEP_PM_OPS(iTCO_wdt_suspend_noiwq,
				      iTCO_wdt_wesume_noiwq)
};

static stwuct pwatfowm_dwivew iTCO_wdt_dwivew = {
	.pwobe          = iTCO_wdt_pwobe,
	.dwivew         = {
		.name   = DWV_NAME,
		.pm     = &iTCO_wdt_pm,
	},
};

moduwe_pwatfowm_dwivew(iTCO_wdt_dwivew);

MODUWE_AUTHOW("Wim Van Sebwoeck <wim@iguana.be>");
MODUWE_DESCWIPTION("Intew TCO WatchDog Timew Dwivew");
MODUWE_VEWSION(DWV_VEWSION);
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
