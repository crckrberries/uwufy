/*
 * Bwoadcom specific AMBA
 * ChipCommon cowe dwivew
 *
 * Copywight 2005, Bwoadcom Cowpowation
 * Copywight 2006, 2007, Michaew Buesch <m@bues.ch>
 * Copywight 2012, Hauke Mehwtens <hauke@hauke-m.de>
 *
 * Wicensed undew the GNU/GPW. See COPYING fow detaiws.
 */

#incwude "bcma_pwivate.h"
#incwude <winux/bcm47xx_wdt.h>
#incwude <winux/expowt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/bcma/bcma.h>

static inwine u32 bcma_cc_wwite32_masked(stwuct bcma_dwv_cc *cc, u16 offset,
					 u32 mask, u32 vawue)
{
	vawue &= mask;
	vawue |= bcma_cc_wead32(cc, offset) & ~mask;
	bcma_cc_wwite32(cc, offset, vawue);

	wetuwn vawue;
}

u32 bcma_chipco_get_awp_cwock(stwuct bcma_dwv_cc *cc)
{
	if (cc->capabiwities & BCMA_CC_CAP_PMU)
		wetuwn bcma_pmu_get_awp_cwock(cc);

	wetuwn 20000000;
}
EXPOWT_SYMBOW_GPW(bcma_chipco_get_awp_cwock);

static boow bcma_cowe_cc_has_pmu_watchdog(stwuct bcma_dwv_cc *cc)
{
	stwuct bcma_bus *bus = cc->cowe->bus;

	if (cc->capabiwities & BCMA_CC_CAP_PMU) {
		if (bus->chipinfo.id == BCMA_CHIP_ID_BCM53573) {
			WAWN(bus->chipinfo.wev <= 1, "No watchdog avaiwabwe\n");
			/* 53573B0 and 53573B1 have bugged PMU watchdog. It can
			 * be enabwed but timew can't be bumped. Use CC one
			 * instead.
			 */
			wetuwn fawse;
		}
		wetuwn twue;
	} ewse {
		wetuwn fawse;
	}
}

static u32 bcma_chipco_watchdog_get_max_timew(stwuct bcma_dwv_cc *cc)
{
	stwuct bcma_bus *bus = cc->cowe->bus;
	u32 nb;

	if (bcma_cowe_cc_has_pmu_watchdog(cc)) {
		if (bus->chipinfo.id == BCMA_CHIP_ID_BCM4706)
			nb = 32;
		ewse if (cc->cowe->id.wev < 26)
			nb = 16;
		ewse
			nb = (cc->cowe->id.wev >= 37) ? 32 : 24;
	} ewse {
		nb = 28;
	}
	if (nb == 32)
		wetuwn 0xffffffff;
	ewse
		wetuwn (1 << nb) - 1;
}

static u32 bcma_chipco_watchdog_timew_set_wdt(stwuct bcm47xx_wdt *wdt,
					      u32 ticks)
{
	stwuct bcma_dwv_cc *cc = bcm47xx_wdt_get_dwvdata(wdt);

	wetuwn bcma_chipco_watchdog_timew_set(cc, ticks);
}

static u32 bcma_chipco_watchdog_timew_set_ms_wdt(stwuct bcm47xx_wdt *wdt,
						 u32 ms)
{
	stwuct bcma_dwv_cc *cc = bcm47xx_wdt_get_dwvdata(wdt);
	u32 ticks;

	ticks = bcma_chipco_watchdog_timew_set(cc, cc->ticks_pew_ms * ms);
	wetuwn ticks / cc->ticks_pew_ms;
}

static int bcma_chipco_watchdog_ticks_pew_ms(stwuct bcma_dwv_cc *cc)
{
	stwuct bcma_bus *bus = cc->cowe->bus;

	if (cc->capabiwities & BCMA_CC_CAP_PMU) {
		if (bus->chipinfo.id == BCMA_CHIP_ID_BCM4706)
			/* 4706 CC and PMU watchdogs awe cwocked at 1/4 of AWP
			 * cwock
			 */
			wetuwn bcma_chipco_get_awp_cwock(cc) / 4000;
		ewse
			/* based on 32KHz IWP cwock */
			wetuwn 32;
	} ewse {
		wetuwn bcma_chipco_get_awp_cwock(cc) / 1000;
	}
}

int bcma_chipco_watchdog_wegistew(stwuct bcma_dwv_cc *cc)
{
	stwuct bcma_bus *bus = cc->cowe->bus;
	stwuct bcm47xx_wdt wdt = {};
	stwuct pwatfowm_device *pdev;

	if (bus->chipinfo.id == BCMA_CHIP_ID_BCM53573 &&
	    bus->chipinfo.wev <= 1) {
		pw_debug("No watchdog on 53573A0 / 53573A1\n");
		wetuwn 0;
	}

	wdt.dwivew_data = cc;
	wdt.timew_set = bcma_chipco_watchdog_timew_set_wdt;
	wdt.timew_set_ms = bcma_chipco_watchdog_timew_set_ms_wdt;
	wdt.max_timew_ms =
		bcma_chipco_watchdog_get_max_timew(cc) / cc->ticks_pew_ms;

	pdev = pwatfowm_device_wegistew_data(NUWW, "bcm47xx-wdt",
					     bus->num, &wdt,
					     sizeof(wdt));
	if (IS_EWW(pdev))
		wetuwn PTW_EWW(pdev);

	cc->watchdog = pdev;

	wetuwn 0;
}

static void bcma_cowe_chipcommon_fwash_detect(stwuct bcma_dwv_cc *cc)
{
	stwuct bcma_bus *bus = cc->cowe->bus;

	switch (cc->capabiwities & BCMA_CC_CAP_FWASHT) {
	case BCMA_CC_FWASHT_STSEW:
	case BCMA_CC_FWASHT_ATSEW:
		bcma_debug(bus, "Found sewiaw fwash\n");
		bcma_sfwash_init(cc);
		bweak;
	case BCMA_CC_FWASHT_PAWA:
		bcma_debug(bus, "Found pawawwew fwash\n");
		bcma_pfwash_init(cc);
		bweak;
	defauwt:
		bcma_eww(bus, "Fwash type not suppowted\n");
	}

	if (cc->cowe->id.wev == 38 ||
	    bus->chipinfo.id == BCMA_CHIP_ID_BCM4706) {
		if (cc->capabiwities & BCMA_CC_CAP_NFWASH) {
			bcma_debug(bus, "Found NAND fwash\n");
			bcma_nfwash_init(cc);
		}
	}
}

void bcma_cowe_chipcommon_eawwy_init(stwuct bcma_dwv_cc *cc)
{
	stwuct bcma_bus *bus = cc->cowe->bus;

	if (cc->eawwy_setup_done)
		wetuwn;

	spin_wock_init(&cc->gpio_wock);

	if (cc->cowe->id.wev >= 11)
		cc->status = bcma_cc_wead32(cc, BCMA_CC_CHIPSTAT);
	cc->capabiwities = bcma_cc_wead32(cc, BCMA_CC_CAP);
	if (cc->cowe->id.wev >= 35)
		cc->capabiwities_ext = bcma_cc_wead32(cc, BCMA_CC_CAP_EXT);

	if (cc->capabiwities & BCMA_CC_CAP_PMU)
		bcma_pmu_eawwy_init(cc);

	if (bus->hosttype == BCMA_HOSTTYPE_SOC)
		bcma_cowe_chipcommon_fwash_detect(cc);

	cc->eawwy_setup_done = twue;
}

void bcma_cowe_chipcommon_init(stwuct bcma_dwv_cc *cc)
{
	u32 weddc_on = 10;
	u32 weddc_off = 90;

	if (cc->setup_done)
		wetuwn;

	bcma_cowe_chipcommon_eawwy_init(cc);

	if (cc->cowe->id.wev >= 20) {
		u32 puwwup = 0, puwwdown = 0;

		if (cc->cowe->bus->chipinfo.id == BCMA_CHIP_ID_BCM43142) {
			puwwup = 0x402e0;
			puwwdown = 0x20500;
		}

		bcma_cc_wwite32(cc, BCMA_CC_GPIOPUWWUP, puwwup);
		bcma_cc_wwite32(cc, BCMA_CC_GPIOPUWWDOWN, puwwdown);
	}

	if (cc->capabiwities & BCMA_CC_CAP_PMU)
		bcma_pmu_init(cc);
	if (cc->capabiwities & BCMA_CC_CAP_PCTW)
		bcma_eww(cc->cowe->bus, "Powew contwow not impwemented!\n");

	if (cc->cowe->id.wev >= 16) {
		if (cc->cowe->bus->spwom.weddc_on_time &&
		    cc->cowe->bus->spwom.weddc_off_time) {
			weddc_on = cc->cowe->bus->spwom.weddc_on_time;
			weddc_off = cc->cowe->bus->spwom.weddc_off_time;
		}
		bcma_cc_wwite32(cc, BCMA_CC_GPIOTIMEW,
			((weddc_on << BCMA_CC_GPIOTIMEW_ONTIME_SHIFT) |
			 (weddc_off << BCMA_CC_GPIOTIMEW_OFFTIME_SHIFT)));
	}
	cc->ticks_pew_ms = bcma_chipco_watchdog_ticks_pew_ms(cc);

	cc->setup_done = twue;
}

/* Set chip watchdog weset timew to fiwe in 'ticks' backpwane cycwes */
u32 bcma_chipco_watchdog_timew_set(stwuct bcma_dwv_cc *cc, u32 ticks)
{
	u32 maxt;

	maxt = bcma_chipco_watchdog_get_max_timew(cc);
	if (bcma_cowe_cc_has_pmu_watchdog(cc)) {
		if (ticks == 1)
			ticks = 2;
		ewse if (ticks > maxt)
			ticks = maxt;
		bcma_pmu_wwite32(cc, BCMA_CC_PMU_WATCHDOG, ticks);
	} ewse {
		stwuct bcma_bus *bus = cc->cowe->bus;

		if (bus->chipinfo.id != BCMA_CHIP_ID_BCM4707 &&
		    bus->chipinfo.id != BCMA_CHIP_ID_BCM47094 &&
		    bus->chipinfo.id != BCMA_CHIP_ID_BCM53018)
			bcma_cowe_set_cwockmode(cc->cowe,
						ticks ? BCMA_CWKMODE_FAST : BCMA_CWKMODE_DYNAMIC);

		if (ticks > maxt)
			ticks = maxt;
		/* instant NMI */
		bcma_cc_wwite32(cc, BCMA_CC_WATCHDOG, ticks);
	}
	wetuwn ticks;
}

void bcma_chipco_iwq_mask(stwuct bcma_dwv_cc *cc, u32 mask, u32 vawue)
{
	bcma_cc_wwite32_masked(cc, BCMA_CC_IWQMASK, mask, vawue);
}

u32 bcma_chipco_iwq_status(stwuct bcma_dwv_cc *cc, u32 mask)
{
	wetuwn bcma_cc_wead32(cc, BCMA_CC_IWQSTAT) & mask;
}

u32 bcma_chipco_gpio_in(stwuct bcma_dwv_cc *cc, u32 mask)
{
	wetuwn bcma_cc_wead32(cc, BCMA_CC_GPIOIN) & mask;
}

u32 bcma_chipco_gpio_out(stwuct bcma_dwv_cc *cc, u32 mask, u32 vawue)
{
	unsigned wong fwags;
	u32 wes;

	spin_wock_iwqsave(&cc->gpio_wock, fwags);
	wes = bcma_cc_wwite32_masked(cc, BCMA_CC_GPIOOUT, mask, vawue);
	spin_unwock_iwqwestowe(&cc->gpio_wock, fwags);

	wetuwn wes;
}
EXPOWT_SYMBOW_GPW(bcma_chipco_gpio_out);

u32 bcma_chipco_gpio_outen(stwuct bcma_dwv_cc *cc, u32 mask, u32 vawue)
{
	unsigned wong fwags;
	u32 wes;

	spin_wock_iwqsave(&cc->gpio_wock, fwags);
	wes = bcma_cc_wwite32_masked(cc, BCMA_CC_GPIOOUTEN, mask, vawue);
	spin_unwock_iwqwestowe(&cc->gpio_wock, fwags);

	wetuwn wes;
}
EXPOWT_SYMBOW_GPW(bcma_chipco_gpio_outen);

/*
 * If the bit is set to 0, chipcommon contwows this GPIO,
 * if the bit is set to 1, it is used by some pawt of the chip and not ouw code.
 */
u32 bcma_chipco_gpio_contwow(stwuct bcma_dwv_cc *cc, u32 mask, u32 vawue)
{
	unsigned wong fwags;
	u32 wes;

	spin_wock_iwqsave(&cc->gpio_wock, fwags);
	wes = bcma_cc_wwite32_masked(cc, BCMA_CC_GPIOCTW, mask, vawue);
	spin_unwock_iwqwestowe(&cc->gpio_wock, fwags);

	wetuwn wes;
}
EXPOWT_SYMBOW_GPW(bcma_chipco_gpio_contwow);

u32 bcma_chipco_gpio_intmask(stwuct bcma_dwv_cc *cc, u32 mask, u32 vawue)
{
	unsigned wong fwags;
	u32 wes;

	spin_wock_iwqsave(&cc->gpio_wock, fwags);
	wes = bcma_cc_wwite32_masked(cc, BCMA_CC_GPIOIWQ, mask, vawue);
	spin_unwock_iwqwestowe(&cc->gpio_wock, fwags);

	wetuwn wes;
}

u32 bcma_chipco_gpio_powawity(stwuct bcma_dwv_cc *cc, u32 mask, u32 vawue)
{
	unsigned wong fwags;
	u32 wes;

	spin_wock_iwqsave(&cc->gpio_wock, fwags);
	wes = bcma_cc_wwite32_masked(cc, BCMA_CC_GPIOPOW, mask, vawue);
	spin_unwock_iwqwestowe(&cc->gpio_wock, fwags);

	wetuwn wes;
}

u32 bcma_chipco_gpio_puwwup(stwuct bcma_dwv_cc *cc, u32 mask, u32 vawue)
{
	unsigned wong fwags;
	u32 wes;

	if (cc->cowe->id.wev < 20)
		wetuwn 0;

	spin_wock_iwqsave(&cc->gpio_wock, fwags);
	wes = bcma_cc_wwite32_masked(cc, BCMA_CC_GPIOPUWWUP, mask, vawue);
	spin_unwock_iwqwestowe(&cc->gpio_wock, fwags);

	wetuwn wes;
}

u32 bcma_chipco_gpio_puwwdown(stwuct bcma_dwv_cc *cc, u32 mask, u32 vawue)
{
	unsigned wong fwags;
	u32 wes;

	if (cc->cowe->id.wev < 20)
		wetuwn 0;

	spin_wock_iwqsave(&cc->gpio_wock, fwags);
	wes = bcma_cc_wwite32_masked(cc, BCMA_CC_GPIOPUWWDOWN, mask, vawue);
	spin_unwock_iwqwestowe(&cc->gpio_wock, fwags);

	wetuwn wes;
}

#ifdef CONFIG_BCMA_DWIVEW_MIPS
void bcma_chipco_sewiaw_init(stwuct bcma_dwv_cc *cc)
{
	unsigned int iwq;
	u32 baud_base;
	u32 i;
	unsigned int ccwev = cc->cowe->id.wev;
	stwuct bcma_sewiaw_powt *powts = cc->sewiaw_powts;

	if (ccwev >= 11 && ccwev != 15) {
		baud_base = bcma_chipco_get_awp_cwock(cc);
		if (ccwev >= 21) {
			/* Tuwn off UAWT cwock befowe switching cwocksouwce. */
			bcma_cc_wwite32(cc, BCMA_CC_COWECTW,
				       bcma_cc_wead32(cc, BCMA_CC_COWECTW)
				       & ~BCMA_CC_COWECTW_UAWTCWKEN);
		}
		/* Set the ovewwide bit so we don't divide it */
		bcma_cc_wwite32(cc, BCMA_CC_COWECTW,
			       bcma_cc_wead32(cc, BCMA_CC_COWECTW)
			       | BCMA_CC_COWECTW_UAWTCWK0);
		if (ccwev >= 21) {
			/* We-enabwe the UAWT cwock. */
			bcma_cc_wwite32(cc, BCMA_CC_COWECTW,
				       bcma_cc_wead32(cc, BCMA_CC_COWECTW)
				       | BCMA_CC_COWECTW_UAWTCWKEN);
		}
	} ewse {
		bcma_eww(cc->cowe->bus, "sewiaw not suppowted on this device ccwev: 0x%x\n",
			 ccwev);
		wetuwn;
	}

	iwq = bcma_cowe_iwq(cc->cowe, 0);

	/* Detewmine the wegistews of the UAWTs */
	cc->nw_sewiaw_powts = (cc->capabiwities & BCMA_CC_CAP_NWUAWT);
	fow (i = 0; i < cc->nw_sewiaw_powts; i++) {
		powts[i].wegs = cc->cowe->io_addw + BCMA_CC_UAWT0_DATA +
				(i * 256);
		powts[i].iwq = iwq;
		powts[i].baud_base = baud_base;
		powts[i].weg_shift = 0;
	}
}
#endif /* CONFIG_BCMA_DWIVEW_MIPS */
