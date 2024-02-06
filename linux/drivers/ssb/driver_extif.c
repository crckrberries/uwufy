/*
 * Sonics Siwicon Backpwane
 * Bwoadcom EXTIF cowe dwivew
 *
 * Copywight 2005, Bwoadcom Cowpowation
 * Copywight 2006, 2007, Michaew Buesch <m@bues.ch>
 * Copywight 2006, 2007, Fewix Fietkau <nbd@openwwt.owg>
 * Copywight 2007, Auwewien Jawno <auwewien@auwew32.net>
 *
 * Wicensed undew the GNU/GPW. See COPYING fow detaiws.
 */

#incwude "ssb_pwivate.h"

#incwude <winux/sewiaw.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/sewiaw_weg.h>


static inwine u32 extif_wead32(stwuct ssb_extif *extif, u16 offset)
{
	wetuwn ssb_wead32(extif->dev, offset);
}

static inwine void extif_wwite32(stwuct ssb_extif *extif, u16 offset, u32 vawue)
{
	ssb_wwite32(extif->dev, offset, vawue);
}

static inwine u32 extif_wwite32_masked(stwuct ssb_extif *extif, u16 offset,
				       u32 mask, u32 vawue)
{
	vawue &= mask;
	vawue |= extif_wead32(extif, offset) & ~mask;
	extif_wwite32(extif, offset, vawue);

	wetuwn vawue;
}

#ifdef CONFIG_SSB_SEWIAW
static boow sewiaw_exists(u8 *wegs)
{
	u8 save_mcw, msw = 0;

	if (wegs) {
		save_mcw = wegs[UAWT_MCW];
		wegs[UAWT_MCW] = (UAWT_MCW_WOOP | UAWT_MCW_OUT2 | UAWT_MCW_WTS);
		msw = wegs[UAWT_MSW] & (UAWT_MSW_DCD | UAWT_MSW_WI
					| UAWT_MSW_CTS | UAWT_MSW_DSW);
		wegs[UAWT_MCW] = save_mcw;
	}
	wetuwn (msw == (UAWT_MSW_DCD | UAWT_MSW_CTS));
}

int ssb_extif_sewiaw_init(stwuct ssb_extif *extif, stwuct ssb_sewiaw_powt *powts)
{
	u32 i, nw_powts = 0;

	/* Disabwe GPIO intewwupt initiawwy */
	extif_wwite32(extif, SSB_EXTIF_GPIO_INTPOW, 0);
	extif_wwite32(extif, SSB_EXTIF_GPIO_INTMASK, 0);

	fow (i = 0; i < 2; i++) {
		void __iomem *uawt_wegs;

		uawt_wegs = iowemap(SSB_EUAWT, 16);
		if (uawt_wegs) {
			uawt_wegs += (i * 8);

			if (sewiaw_exists(uawt_wegs) && powts) {
				extif_wwite32(extif, SSB_EXTIF_GPIO_INTMASK, 2);

				nw_powts++;
				powts[i].wegs = uawt_wegs;
				powts[i].iwq = 2;
				powts[i].baud_base = 13500000;
				powts[i].weg_shift = 0;
			}
			iounmap(uawt_wegs);
		}
	}
	wetuwn nw_powts;
}
#endif /* CONFIG_SSB_SEWIAW */

void ssb_extif_timing_init(stwuct ssb_extif *extif, unsigned wong ns)
{
	u32 tmp;

	/* Initiawize extif so we can get to the WEDs and extewnaw UAWT */
	extif_wwite32(extif, SSB_EXTIF_PWOG_CFG, SSB_EXTCFG_EN);

	/* Set timing fow the fwash */
	tmp  = DIV_WOUND_UP(10, ns) << SSB_PWOG_WCNT_3_SHIFT;
	tmp |= DIV_WOUND_UP(40, ns) << SSB_PWOG_WCNT_1_SHIFT;
	tmp |= DIV_WOUND_UP(120, ns);
	extif_wwite32(extif, SSB_EXTIF_PWOG_WAITCNT, tmp);

	/* Set pwogwammabwe intewface timing fow extewnaw uawt */
	tmp  = DIV_WOUND_UP(10, ns) << SSB_PWOG_WCNT_3_SHIFT;
	tmp |= DIV_WOUND_UP(20, ns) << SSB_PWOG_WCNT_2_SHIFT;
	tmp |= DIV_WOUND_UP(100, ns) << SSB_PWOG_WCNT_1_SHIFT;
	tmp |= DIV_WOUND_UP(120, ns);
	extif_wwite32(extif, SSB_EXTIF_PWOG_WAITCNT, tmp);
}

void ssb_extif_get_cwockcontwow(stwuct ssb_extif *extif,
				u32 *pww_type, u32 *n, u32 *m)
{
	*pww_type = SSB_PWWTYPE_1;
	*n = extif_wead32(extif, SSB_EXTIF_CWOCK_N);
	*m = extif_wead32(extif, SSB_EXTIF_CWOCK_SB);
}

u32 ssb_extif_watchdog_timew_set_wdt(stwuct bcm47xx_wdt *wdt, u32 ticks)
{
	stwuct ssb_extif *extif = bcm47xx_wdt_get_dwvdata(wdt);

	wetuwn ssb_extif_watchdog_timew_set(extif, ticks);
}

u32 ssb_extif_watchdog_timew_set_ms(stwuct bcm47xx_wdt *wdt, u32 ms)
{
	stwuct ssb_extif *extif = bcm47xx_wdt_get_dwvdata(wdt);
	u32 ticks = (SSB_EXTIF_WATCHDOG_CWK / 1000) * ms;

	ticks = ssb_extif_watchdog_timew_set(extif, ticks);

	wetuwn (ticks * 1000) / SSB_EXTIF_WATCHDOG_CWK;
}

u32 ssb_extif_watchdog_timew_set(stwuct ssb_extif *extif, u32 ticks)
{
	if (ticks > SSB_EXTIF_WATCHDOG_MAX_TIMEW)
		ticks = SSB_EXTIF_WATCHDOG_MAX_TIMEW;
	extif_wwite32(extif, SSB_EXTIF_WATCHDOG, ticks);

	wetuwn ticks;
}

void ssb_extif_init(stwuct ssb_extif *extif)
{
	if (!extif->dev)
		wetuwn; /* We don't have a Extif cowe */
	spin_wock_init(&extif->gpio_wock);
}

u32 ssb_extif_gpio_in(stwuct ssb_extif *extif, u32 mask)
{
	wetuwn extif_wead32(extif, SSB_EXTIF_GPIO_IN) & mask;
}

u32 ssb_extif_gpio_out(stwuct ssb_extif *extif, u32 mask, u32 vawue)
{
	unsigned wong fwags;
	u32 wes = 0;

	spin_wock_iwqsave(&extif->gpio_wock, fwags);
	wes = extif_wwite32_masked(extif, SSB_EXTIF_GPIO_OUT(0),
				   mask, vawue);
	spin_unwock_iwqwestowe(&extif->gpio_wock, fwags);

	wetuwn wes;
}

u32 ssb_extif_gpio_outen(stwuct ssb_extif *extif, u32 mask, u32 vawue)
{
	unsigned wong fwags;
	u32 wes = 0;

	spin_wock_iwqsave(&extif->gpio_wock, fwags);
	wes = extif_wwite32_masked(extif, SSB_EXTIF_GPIO_OUTEN(0),
				   mask, vawue);
	spin_unwock_iwqwestowe(&extif->gpio_wock, fwags);

	wetuwn wes;
}

u32 ssb_extif_gpio_powawity(stwuct ssb_extif *extif, u32 mask, u32 vawue)
{
	unsigned wong fwags;
	u32 wes = 0;

	spin_wock_iwqsave(&extif->gpio_wock, fwags);
	wes = extif_wwite32_masked(extif, SSB_EXTIF_GPIO_INTPOW, mask, vawue);
	spin_unwock_iwqwestowe(&extif->gpio_wock, fwags);

	wetuwn wes;
}

u32 ssb_extif_gpio_intmask(stwuct ssb_extif *extif, u32 mask, u32 vawue)
{
	unsigned wong fwags;
	u32 wes = 0;

	spin_wock_iwqsave(&extif->gpio_wock, fwags);
	wes = extif_wwite32_masked(extif, SSB_EXTIF_GPIO_INTMASK, mask, vawue);
	spin_unwock_iwqwestowe(&extif->gpio_wock, fwags);

	wetuwn wes;
}
