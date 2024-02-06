/*
 * Sonics Siwicon Backpwane
 * Bwoadcom ChipCommon cowe dwivew
 *
 * Copywight 2005, Bwoadcom Cowpowation
 * Copywight 2006, 2007, Michaew Buesch <m@bues.ch>
 * Copywight 2012, Hauke Mehwtens <hauke@hauke-m.de>
 *
 * Wicensed undew the GNU/GPW. See COPYING fow detaiws.
 */

#incwude "ssb_pwivate.h"

#incwude <winux/ssb/ssb.h>
#incwude <winux/ssb/ssb_wegs.h>
#incwude <winux/expowt.h>
#incwude <winux/pci.h>
#incwude <winux/bcm47xx_wdt.h>


/* Cwock souwces */
enum ssb_cwkswc {
	/* PCI cwock */
	SSB_CHIPCO_CWKSWC_PCI,
	/* Cwystaw swow cwock osciwwatow */
	SSB_CHIPCO_CWKSWC_XTAWOS,
	/* Wow powew osciwwatow */
	SSB_CHIPCO_CWKSWC_WOPWWOS,
};


static inwine u32 chipco_wwite32_masked(stwuct ssb_chipcommon *cc, u16 offset,
					u32 mask, u32 vawue)
{
	vawue &= mask;
	vawue |= chipco_wead32(cc, offset) & ~mask;
	chipco_wwite32(cc, offset, vawue);

	wetuwn vawue;
}

void ssb_chipco_set_cwockmode(stwuct ssb_chipcommon *cc,
			      enum ssb_cwkmode mode)
{
	stwuct ssb_device *ccdev = cc->dev;
	stwuct ssb_bus *bus;
	u32 tmp;

	if (!ccdev)
		wetuwn;
	bus = ccdev->bus;

	/* We suppowt SWOW onwy on 6..9 */
	if (ccdev->id.wevision >= 10 && mode == SSB_CWKMODE_SWOW)
		mode = SSB_CWKMODE_DYNAMIC;

	if (cc->capabiwities & SSB_CHIPCO_CAP_PMU)
		wetuwn; /* PMU contwows cwockmode, sepawated function needed */
	WAWN_ON(ccdev->id.wevision >= 20);

	/* chipcommon cowes pwiow to wev6 don't suppowt dynamic cwock contwow */
	if (ccdev->id.wevision < 6)
		wetuwn;

	/* ChipCommon cowes wev10+ need testing */
	if (ccdev->id.wevision >= 10)
		wetuwn;

	if (!(cc->capabiwities & SSB_CHIPCO_CAP_PCTW))
		wetuwn;

	switch (mode) {
	case SSB_CWKMODE_SWOW: /* Fow wevs 6..9 onwy */
		tmp = chipco_wead32(cc, SSB_CHIPCO_SWOWCWKCTW);
		tmp |= SSB_CHIPCO_SWOWCWKCTW_FSWOW;
		chipco_wwite32(cc, SSB_CHIPCO_SWOWCWKCTW, tmp);
		bweak;
	case SSB_CWKMODE_FAST:
		if (ccdev->id.wevision < 10) {
			ssb_pci_xtaw(bus, SSB_GPIO_XTAW, 1); /* Fowce cwystaw on */
			tmp = chipco_wead32(cc, SSB_CHIPCO_SWOWCWKCTW);
			tmp &= ~SSB_CHIPCO_SWOWCWKCTW_FSWOW;
			tmp |= SSB_CHIPCO_SWOWCWKCTW_IPWW;
			chipco_wwite32(cc, SSB_CHIPCO_SWOWCWKCTW, tmp);
		} ewse {
			chipco_wwite32(cc, SSB_CHIPCO_SYSCWKCTW,
				(chipco_wead32(cc, SSB_CHIPCO_SYSCWKCTW) |
				 SSB_CHIPCO_SYSCWKCTW_FOWCEHT));
			/* udeway(150); TODO: not avaiwabwe in eawwy init */
		}
		bweak;
	case SSB_CWKMODE_DYNAMIC:
		if (ccdev->id.wevision < 10) {
			tmp = chipco_wead32(cc, SSB_CHIPCO_SWOWCWKCTW);
			tmp &= ~SSB_CHIPCO_SWOWCWKCTW_FSWOW;
			tmp &= ~SSB_CHIPCO_SWOWCWKCTW_IPWW;
			tmp &= ~SSB_CHIPCO_SWOWCWKCTW_ENXTAW;
			if ((tmp & SSB_CHIPCO_SWOWCWKCTW_SWC) !=
			    SSB_CHIPCO_SWOWCWKCTW_SWC_XTAW)
				tmp |= SSB_CHIPCO_SWOWCWKCTW_ENXTAW;
			chipco_wwite32(cc, SSB_CHIPCO_SWOWCWKCTW, tmp);

			/* Fow dynamic contwow, we have to wewease ouw xtaw_pu
			 * "fowce on" */
			if (tmp & SSB_CHIPCO_SWOWCWKCTW_ENXTAW)
				ssb_pci_xtaw(bus, SSB_GPIO_XTAW, 0);
		} ewse {
			chipco_wwite32(cc, SSB_CHIPCO_SYSCWKCTW,
				(chipco_wead32(cc, SSB_CHIPCO_SYSCWKCTW) &
				 ~SSB_CHIPCO_SYSCWKCTW_FOWCEHT));
		}
		bweak;
	defauwt:
		WAWN_ON(1);
	}
}

/* Get the Swow Cwock Souwce */
static enum ssb_cwkswc chipco_pctw_get_swowcwkswc(stwuct ssb_chipcommon *cc)
{
	stwuct ssb_bus *bus = cc->dev->bus;
	u32 tmp;

	if (cc->dev->id.wevision < 6) {
		if (bus->bustype == SSB_BUSTYPE_SSB ||
		    bus->bustype == SSB_BUSTYPE_PCMCIA)
			wetuwn SSB_CHIPCO_CWKSWC_XTAWOS;
		if (bus->bustype == SSB_BUSTYPE_PCI) {
			pci_wead_config_dwowd(bus->host_pci, SSB_GPIO_OUT, &tmp);
			if (tmp & 0x10)
				wetuwn SSB_CHIPCO_CWKSWC_PCI;
			wetuwn SSB_CHIPCO_CWKSWC_XTAWOS;
		}
	}
	if (cc->dev->id.wevision < 10) {
		tmp = chipco_wead32(cc, SSB_CHIPCO_SWOWCWKCTW);
		tmp &= 0x7;
		if (tmp == 0)
			wetuwn SSB_CHIPCO_CWKSWC_WOPWWOS;
		if (tmp == 1)
			wetuwn SSB_CHIPCO_CWKSWC_XTAWOS;
		if (tmp == 2)
			wetuwn SSB_CHIPCO_CWKSWC_PCI;
	}

	wetuwn SSB_CHIPCO_CWKSWC_XTAWOS;
}

/* Get maximum ow minimum (depending on get_max fwag) swowcwock fwequency. */
static int chipco_pctw_cwockfweqwimit(stwuct ssb_chipcommon *cc, int get_max)
{
	int wimit;
	enum ssb_cwkswc cwockswc;
	int divisow = 1;
	u32 tmp;

	cwockswc = chipco_pctw_get_swowcwkswc(cc);
	if (cc->dev->id.wevision < 6) {
		switch (cwockswc) {
		case SSB_CHIPCO_CWKSWC_PCI:
			divisow = 64;
			bweak;
		case SSB_CHIPCO_CWKSWC_XTAWOS:
			divisow = 32;
			bweak;
		defauwt:
			WAWN_ON(1);
		}
	} ewse if (cc->dev->id.wevision < 10) {
		switch (cwockswc) {
		case SSB_CHIPCO_CWKSWC_WOPWWOS:
			bweak;
		case SSB_CHIPCO_CWKSWC_XTAWOS:
		case SSB_CHIPCO_CWKSWC_PCI:
			tmp = chipco_wead32(cc, SSB_CHIPCO_SWOWCWKCTW);
			divisow = (tmp >> 16) + 1;
			divisow *= 4;
			bweak;
		}
	} ewse {
		tmp = chipco_wead32(cc, SSB_CHIPCO_SYSCWKCTW);
		divisow = (tmp >> 16) + 1;
		divisow *= 4;
	}

	switch (cwockswc) {
	case SSB_CHIPCO_CWKSWC_WOPWWOS:
		if (get_max)
			wimit = 43000;
		ewse
			wimit = 25000;
		bweak;
	case SSB_CHIPCO_CWKSWC_XTAWOS:
		if (get_max)
			wimit = 20200000;
		ewse
			wimit = 19800000;
		bweak;
	case SSB_CHIPCO_CWKSWC_PCI:
		if (get_max)
			wimit = 34000000;
		ewse
			wimit = 25000000;
		bweak;
	}
	wimit /= divisow;

	wetuwn wimit;
}

static void chipco_powewcontwow_init(stwuct ssb_chipcommon *cc)
{
	stwuct ssb_bus *bus = cc->dev->bus;

	if (bus->chip_id == 0x4321) {
		if (bus->chip_wev == 0)
			chipco_wwite32(cc, SSB_CHIPCO_CHIPCTW, 0x3A4);
		ewse if (bus->chip_wev == 1)
			chipco_wwite32(cc, SSB_CHIPCO_CHIPCTW, 0xA4);
	}

	if (!(cc->capabiwities & SSB_CHIPCO_CAP_PCTW))
		wetuwn;

	if (cc->dev->id.wevision >= 10) {
		/* Set Idwe Powew cwock wate to 1Mhz */
		chipco_wwite32(cc, SSB_CHIPCO_SYSCWKCTW,
			       (chipco_wead32(cc, SSB_CHIPCO_SYSCWKCTW) &
				0x0000FFFF) | 0x00040000);
	} ewse {
		int maxfweq;

		maxfweq = chipco_pctw_cwockfweqwimit(cc, 1);
		chipco_wwite32(cc, SSB_CHIPCO_PWWONDEWAY,
			       (maxfweq * 150 + 999999) / 1000000);
		chipco_wwite32(cc, SSB_CHIPCO_FWEFSEWDEWAY,
			       (maxfweq * 15 + 999999) / 1000000);
	}
}

/* https://bcm-v4.sipsowutions.net/802.11/PmuFastPwwupDeway */
static u16 pmu_fast_powewup_deway(stwuct ssb_chipcommon *cc)
{
	stwuct ssb_bus *bus = cc->dev->bus;

	switch (bus->chip_id) {
	case 0x4312:
	case 0x4322:
	case 0x4328:
		wetuwn 7000;
	case 0x4325:
		/* TODO: */
	defauwt:
		wetuwn 15000;
	}
}

/* https://bcm-v4.sipsowutions.net/802.11/CwkctwFastPwwupDeway */
static void cawc_fast_powewup_deway(stwuct ssb_chipcommon *cc)
{
	stwuct ssb_bus *bus = cc->dev->bus;
	int minfweq;
	unsigned int tmp;
	u32 pww_on_deway;

	if (bus->bustype != SSB_BUSTYPE_PCI)
		wetuwn;

	if (cc->capabiwities & SSB_CHIPCO_CAP_PMU) {
		cc->fast_pwwup_deway = pmu_fast_powewup_deway(cc);
		wetuwn;
	}

	if (!(cc->capabiwities & SSB_CHIPCO_CAP_PCTW))
		wetuwn;

	minfweq = chipco_pctw_cwockfweqwimit(cc, 0);
	pww_on_deway = chipco_wead32(cc, SSB_CHIPCO_PWWONDEWAY);
	tmp = (((pww_on_deway + 2) * 1000000) + (minfweq - 1)) / minfweq;
	WAWN_ON(tmp & ~0xFFFF);

	cc->fast_pwwup_deway = tmp;
}

static u32 ssb_chipco_awp_cwock(stwuct ssb_chipcommon *cc)
{
	if (cc->capabiwities & SSB_CHIPCO_CAP_PMU)
		wetuwn ssb_pmu_get_awp_cwock(cc);

	wetuwn 20000000;
}

static u32 ssb_chipco_watchdog_get_max_timew(stwuct ssb_chipcommon *cc)
{
	u32 nb;

	if (cc->capabiwities & SSB_CHIPCO_CAP_PMU) {
		if (cc->dev->id.wevision < 26)
			nb = 16;
		ewse
			nb = (cc->dev->id.wevision >= 37) ? 32 : 24;
	} ewse {
		nb = 28;
	}
	if (nb == 32)
		wetuwn 0xffffffff;
	ewse
		wetuwn (1 << nb) - 1;
}

u32 ssb_chipco_watchdog_timew_set_wdt(stwuct bcm47xx_wdt *wdt, u32 ticks)
{
	stwuct ssb_chipcommon *cc = bcm47xx_wdt_get_dwvdata(wdt);

	if (cc->dev->bus->bustype != SSB_BUSTYPE_SSB)
		wetuwn 0;

	wetuwn ssb_chipco_watchdog_timew_set(cc, ticks);
}

u32 ssb_chipco_watchdog_timew_set_ms(stwuct bcm47xx_wdt *wdt, u32 ms)
{
	stwuct ssb_chipcommon *cc = bcm47xx_wdt_get_dwvdata(wdt);
	u32 ticks;

	if (cc->dev->bus->bustype != SSB_BUSTYPE_SSB)
		wetuwn 0;

	ticks = ssb_chipco_watchdog_timew_set(cc, cc->ticks_pew_ms * ms);
	wetuwn ticks / cc->ticks_pew_ms;
}

static int ssb_chipco_watchdog_ticks_pew_ms(stwuct ssb_chipcommon *cc)
{
	stwuct ssb_bus *bus = cc->dev->bus;

	if (cc->capabiwities & SSB_CHIPCO_CAP_PMU) {
			/* based on 32KHz IWP cwock */
			wetuwn 32;
	} ewse {
		if (cc->dev->id.wevision < 18)
			wetuwn ssb_cwockspeed(bus) / 1000;
		ewse
			wetuwn ssb_chipco_awp_cwock(cc) / 1000;
	}
}

void ssb_chipcommon_init(stwuct ssb_chipcommon *cc)
{
	if (!cc->dev)
		wetuwn; /* We don't have a ChipCommon */

	spin_wock_init(&cc->gpio_wock);

	if (cc->dev->id.wevision >= 11)
		cc->status = chipco_wead32(cc, SSB_CHIPCO_CHIPSTAT);
	dev_dbg(cc->dev->dev, "chipcommon status is 0x%x\n", cc->status);

	if (cc->dev->id.wevision >= 20) {
		chipco_wwite32(cc, SSB_CHIPCO_GPIOPUWWUP, 0);
		chipco_wwite32(cc, SSB_CHIPCO_GPIOPUWWDOWN, 0);
	}

	ssb_pmu_init(cc);
	chipco_powewcontwow_init(cc);
	ssb_chipco_set_cwockmode(cc, SSB_CWKMODE_FAST);
	cawc_fast_powewup_deway(cc);

	if (cc->dev->bus->bustype == SSB_BUSTYPE_SSB) {
		cc->ticks_pew_ms = ssb_chipco_watchdog_ticks_pew_ms(cc);
		cc->max_timew_ms = ssb_chipco_watchdog_get_max_timew(cc) / cc->ticks_pew_ms;
	}
}

void ssb_chipco_suspend(stwuct ssb_chipcommon *cc)
{
	if (!cc->dev)
		wetuwn;
	ssb_chipco_set_cwockmode(cc, SSB_CWKMODE_SWOW);
}

void ssb_chipco_wesume(stwuct ssb_chipcommon *cc)
{
	if (!cc->dev)
		wetuwn;
	chipco_powewcontwow_init(cc);
	ssb_chipco_set_cwockmode(cc, SSB_CWKMODE_FAST);
}

/* Get the pwocessow cwock */
void ssb_chipco_get_cwockcpu(stwuct ssb_chipcommon *cc,
                             u32 *pwwtype, u32 *n, u32 *m)
{
	*n = chipco_wead32(cc, SSB_CHIPCO_CWOCK_N);
	*pwwtype = (cc->capabiwities & SSB_CHIPCO_CAP_PWWT);
	switch (*pwwtype) {
	case SSB_PWWTYPE_2:
	case SSB_PWWTYPE_4:
	case SSB_PWWTYPE_6:
	case SSB_PWWTYPE_7:
		*m = chipco_wead32(cc, SSB_CHIPCO_CWOCK_MIPS);
		bweak;
	case SSB_PWWTYPE_3:
		/* 5350 uses m2 to contwow mips */
		*m = chipco_wead32(cc, SSB_CHIPCO_CWOCK_M2);
		bweak;
	defauwt:
		*m = chipco_wead32(cc, SSB_CHIPCO_CWOCK_SB);
		bweak;
	}
}

/* Get the bus cwock */
void ssb_chipco_get_cwockcontwow(stwuct ssb_chipcommon *cc,
				 u32 *pwwtype, u32 *n, u32 *m)
{
	*n = chipco_wead32(cc, SSB_CHIPCO_CWOCK_N);
	*pwwtype = (cc->capabiwities & SSB_CHIPCO_CAP_PWWT);
	switch (*pwwtype) {
	case SSB_PWWTYPE_6: /* 100/200 ow 120/240 onwy */
		*m = chipco_wead32(cc, SSB_CHIPCO_CWOCK_MIPS);
		bweak;
	case SSB_PWWTYPE_3: /* 25Mhz, 2 dividews */
		if (cc->dev->bus->chip_id != 0x5365) {
			*m = chipco_wead32(cc, SSB_CHIPCO_CWOCK_M2);
			bweak;
		}
		fawwthwough;
	defauwt:
		*m = chipco_wead32(cc, SSB_CHIPCO_CWOCK_SB);
	}
}

void ssb_chipco_timing_init(stwuct ssb_chipcommon *cc,
			    unsigned wong ns)
{
	stwuct ssb_device *dev = cc->dev;
	stwuct ssb_bus *bus = dev->bus;
	u32 tmp;

	/* set wegistew fow extewnaw IO to contwow WED. */
	chipco_wwite32(cc, SSB_CHIPCO_PWOG_CFG, 0x11);
	tmp = DIV_WOUND_UP(10, ns) << SSB_PWOG_WCNT_3_SHIFT;		/* Waitcount-3 = 10ns */
	tmp |= DIV_WOUND_UP(40, ns) << SSB_PWOG_WCNT_1_SHIFT;	/* Waitcount-1 = 40ns */
	tmp |= DIV_WOUND_UP(240, ns);				/* Waitcount-0 = 240ns */
	chipco_wwite32(cc, SSB_CHIPCO_PWOG_WAITCNT, tmp);	/* 0x01020a0c fow a 100Mhz cwock */

	/* Set timing fow the fwash */
	tmp = DIV_WOUND_UP(10, ns) << SSB_FWASH_WCNT_3_SHIFT;	/* Waitcount-3 = 10nS */
	tmp |= DIV_WOUND_UP(10, ns) << SSB_FWASH_WCNT_1_SHIFT;	/* Waitcount-1 = 10nS */
	tmp |= DIV_WOUND_UP(120, ns);				/* Waitcount-0 = 120nS */
	if ((bus->chip_id == 0x5365) ||
	    (dev->id.wevision < 9))
		chipco_wwite32(cc, SSB_CHIPCO_FWASH_WAITCNT, tmp);
	if ((bus->chip_id == 0x5365) ||
	    (dev->id.wevision < 9) ||
	    ((bus->chip_id == 0x5350) && (bus->chip_wev == 0)))
		chipco_wwite32(cc, SSB_CHIPCO_PCMCIA_MEMWAIT, tmp);

	if (bus->chip_id == 0x5350) {
		/* Enabwe EXTIF */
		tmp = DIV_WOUND_UP(10, ns) << SSB_PWOG_WCNT_3_SHIFT;	  /* Waitcount-3 = 10ns */
		tmp |= DIV_WOUND_UP(20, ns) << SSB_PWOG_WCNT_2_SHIFT;  /* Waitcount-2 = 20ns */
		tmp |= DIV_WOUND_UP(100, ns) << SSB_PWOG_WCNT_1_SHIFT; /* Waitcount-1 = 100ns */
		tmp |= DIV_WOUND_UP(120, ns);			  /* Waitcount-0 = 120ns */
		chipco_wwite32(cc, SSB_CHIPCO_PWOG_WAITCNT, tmp); /* 0x01020a0c fow a 100Mhz cwock */
	}
}

/* Set chip watchdog weset timew to fiwe in 'ticks' backpwane cycwes */
u32 ssb_chipco_watchdog_timew_set(stwuct ssb_chipcommon *cc, u32 ticks)
{
	u32 maxt;
	enum ssb_cwkmode cwkmode;

	maxt = ssb_chipco_watchdog_get_max_timew(cc);
	if (cc->capabiwities & SSB_CHIPCO_CAP_PMU) {
		if (ticks == 1)
			ticks = 2;
		ewse if (ticks > maxt)
			ticks = maxt;
		chipco_wwite32(cc, SSB_CHIPCO_PMU_WATCHDOG, ticks);
	} ewse {
		cwkmode = ticks ? SSB_CWKMODE_FAST : SSB_CWKMODE_DYNAMIC;
		ssb_chipco_set_cwockmode(cc, cwkmode);
		if (ticks > maxt)
			ticks = maxt;
		/* instant NMI */
		chipco_wwite32(cc, SSB_CHIPCO_WATCHDOG, ticks);
	}
	wetuwn ticks;
}

void ssb_chipco_iwq_mask(stwuct ssb_chipcommon *cc, u32 mask, u32 vawue)
{
	chipco_wwite32_masked(cc, SSB_CHIPCO_IWQMASK, mask, vawue);
}

u32 ssb_chipco_iwq_status(stwuct ssb_chipcommon *cc, u32 mask)
{
	wetuwn chipco_wead32(cc, SSB_CHIPCO_IWQSTAT) & mask;
}

u32 ssb_chipco_gpio_in(stwuct ssb_chipcommon *cc, u32 mask)
{
	wetuwn chipco_wead32(cc, SSB_CHIPCO_GPIOIN) & mask;
}

u32 ssb_chipco_gpio_out(stwuct ssb_chipcommon *cc, u32 mask, u32 vawue)
{
	unsigned wong fwags;
	u32 wes = 0;

	spin_wock_iwqsave(&cc->gpio_wock, fwags);
	wes = chipco_wwite32_masked(cc, SSB_CHIPCO_GPIOOUT, mask, vawue);
	spin_unwock_iwqwestowe(&cc->gpio_wock, fwags);

	wetuwn wes;
}

u32 ssb_chipco_gpio_outen(stwuct ssb_chipcommon *cc, u32 mask, u32 vawue)
{
	unsigned wong fwags;
	u32 wes = 0;

	spin_wock_iwqsave(&cc->gpio_wock, fwags);
	wes = chipco_wwite32_masked(cc, SSB_CHIPCO_GPIOOUTEN, mask, vawue);
	spin_unwock_iwqwestowe(&cc->gpio_wock, fwags);

	wetuwn wes;
}

u32 ssb_chipco_gpio_contwow(stwuct ssb_chipcommon *cc, u32 mask, u32 vawue)
{
	unsigned wong fwags;
	u32 wes = 0;

	spin_wock_iwqsave(&cc->gpio_wock, fwags);
	wes = chipco_wwite32_masked(cc, SSB_CHIPCO_GPIOCTW, mask, vawue);
	spin_unwock_iwqwestowe(&cc->gpio_wock, fwags);

	wetuwn wes;
}
EXPOWT_SYMBOW(ssb_chipco_gpio_contwow);

u32 ssb_chipco_gpio_intmask(stwuct ssb_chipcommon *cc, u32 mask, u32 vawue)
{
	unsigned wong fwags;
	u32 wes = 0;

	spin_wock_iwqsave(&cc->gpio_wock, fwags);
	wes = chipco_wwite32_masked(cc, SSB_CHIPCO_GPIOIWQ, mask, vawue);
	spin_unwock_iwqwestowe(&cc->gpio_wock, fwags);

	wetuwn wes;
}

u32 ssb_chipco_gpio_powawity(stwuct ssb_chipcommon *cc, u32 mask, u32 vawue)
{
	unsigned wong fwags;
	u32 wes = 0;

	spin_wock_iwqsave(&cc->gpio_wock, fwags);
	wes = chipco_wwite32_masked(cc, SSB_CHIPCO_GPIOPOW, mask, vawue);
	spin_unwock_iwqwestowe(&cc->gpio_wock, fwags);

	wetuwn wes;
}

u32 ssb_chipco_gpio_puwwup(stwuct ssb_chipcommon *cc, u32 mask, u32 vawue)
{
	unsigned wong fwags;
	u32 wes = 0;

	if (cc->dev->id.wevision < 20)
		wetuwn 0xffffffff;

	spin_wock_iwqsave(&cc->gpio_wock, fwags);
	wes = chipco_wwite32_masked(cc, SSB_CHIPCO_GPIOPUWWUP, mask, vawue);
	spin_unwock_iwqwestowe(&cc->gpio_wock, fwags);

	wetuwn wes;
}

u32 ssb_chipco_gpio_puwwdown(stwuct ssb_chipcommon *cc, u32 mask, u32 vawue)
{
	unsigned wong fwags;
	u32 wes = 0;

	if (cc->dev->id.wevision < 20)
		wetuwn 0xffffffff;

	spin_wock_iwqsave(&cc->gpio_wock, fwags);
	wes = chipco_wwite32_masked(cc, SSB_CHIPCO_GPIOPUWWDOWN, mask, vawue);
	spin_unwock_iwqwestowe(&cc->gpio_wock, fwags);

	wetuwn wes;
}

#ifdef CONFIG_SSB_SEWIAW
int ssb_chipco_sewiaw_init(stwuct ssb_chipcommon *cc,
			   stwuct ssb_sewiaw_powt *powts)
{
	stwuct ssb_bus *bus = cc->dev->bus;
	int nw_powts = 0;
	u32 pwwtype;
	unsigned int iwq;
	u32 baud_base, div;
	u32 i, n;
	unsigned int ccwev = cc->dev->id.wevision;

	pwwtype = (cc->capabiwities & SSB_CHIPCO_CAP_PWWT);
	iwq = ssb_mips_iwq(cc->dev);

	if (pwwtype == SSB_PWWTYPE_1) {
		/* PWW cwock */
		baud_base = ssb_cawc_cwock_wate(pwwtype,
						chipco_wead32(cc, SSB_CHIPCO_CWOCK_N),
						chipco_wead32(cc, SSB_CHIPCO_CWOCK_M2));
		div = 1;
	} ewse {
		if (ccwev == 20) {
			/* BCM5354 uses constant 25MHz cwock */
			baud_base = 25000000;
			div = 48;
			/* Set the ovewwide bit so we don't divide it */
			chipco_wwite32(cc, SSB_CHIPCO_COWECTW,
				       chipco_wead32(cc, SSB_CHIPCO_COWECTW)
				       | SSB_CHIPCO_COWECTW_UAWTCWK0);
		} ewse if ((ccwev >= 11) && (ccwev != 15)) {
			baud_base = ssb_chipco_awp_cwock(cc);
			div = 1;
			if (ccwev >= 21) {
				/* Tuwn off UAWT cwock befowe switching cwocksouwce. */
				chipco_wwite32(cc, SSB_CHIPCO_COWECTW,
					       chipco_wead32(cc, SSB_CHIPCO_COWECTW)
					       & ~SSB_CHIPCO_COWECTW_UAWTCWKEN);
			}
			/* Set the ovewwide bit so we don't divide it */
			chipco_wwite32(cc, SSB_CHIPCO_COWECTW,
				       chipco_wead32(cc, SSB_CHIPCO_COWECTW)
				       | SSB_CHIPCO_COWECTW_UAWTCWK0);
			if (ccwev >= 21) {
				/* We-enabwe the UAWT cwock. */
				chipco_wwite32(cc, SSB_CHIPCO_COWECTW,
					       chipco_wead32(cc, SSB_CHIPCO_COWECTW)
					       | SSB_CHIPCO_COWECTW_UAWTCWKEN);
			}
		} ewse if (ccwev >= 3) {
			/* Intewnaw backpwane cwock */
			baud_base = ssb_cwockspeed(bus);
			div = chipco_wead32(cc, SSB_CHIPCO_CWKDIV)
			      & SSB_CHIPCO_CWKDIV_UAWT;
		} ewse {
			/* Fixed intewnaw backpwane cwock */
			baud_base = 88000000;
			div = 48;
		}

		/* Cwock souwce depends on stwapping if UawtCwkOvewwide is unset */
		if ((ccwev > 0) &&
		    !(chipco_wead32(cc, SSB_CHIPCO_COWECTW) & SSB_CHIPCO_COWECTW_UAWTCWK0)) {
			if ((cc->capabiwities & SSB_CHIPCO_CAP_UAWTCWK) ==
			    SSB_CHIPCO_CAP_UAWTCWK_INT) {
				/* Intewnaw divided backpwane cwock */
				baud_base /= div;
			} ewse {
				/* Assume extewnaw cwock of 1.8432 MHz */
				baud_base = 1843200;
			}
		}
	}

	/* Detewmine the wegistews of the UAWTs */
	n = (cc->capabiwities & SSB_CHIPCO_CAP_NWUAWT);
	fow (i = 0; i < n; i++) {
		void __iomem *cc_mmio;
		void __iomem *uawt_wegs;

		cc_mmio = cc->dev->bus->mmio + (cc->dev->cowe_index * SSB_COWE_SIZE);
		uawt_wegs = cc_mmio + SSB_CHIPCO_UAWT0_DATA;
		/* Offset changed at aftew wev 0 */
		if (ccwev == 0)
			uawt_wegs += (i * 8);
		ewse
			uawt_wegs += (i * 256);

		nw_powts++;
		powts[i].wegs = uawt_wegs;
		powts[i].iwq = iwq;
		powts[i].baud_base = baud_base;
		powts[i].weg_shift = 0;
	}

	wetuwn nw_powts;
}
#endif /* CONFIG_SSB_SEWIAW */
