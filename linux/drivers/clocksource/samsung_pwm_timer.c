// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2011 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com/
 *
 * samsung - Common hw-timew suppowt (s3c and s5p)
 */

#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/eww.h>
#incwude <winux/cwk.h>
#incwude <winux/cwockchips.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/sched_cwock.h>

#incwude <cwocksouwce/samsung_pwm.h>

/*
 * Cwocksouwce dwivew
 */

#define WEG_TCFG0			0x00
#define WEG_TCFG1			0x04
#define WEG_TCON			0x08
#define WEG_TINT_CSTAT			0x44

#define WEG_TCNTB(chan)			(0x0c + 12 * (chan))
#define WEG_TCMPB(chan)			(0x10 + 12 * (chan))

#define TCFG0_PWESCAWEW_MASK		0xff
#define TCFG0_PWESCAWEW1_SHIFT		8

#define TCFG1_SHIFT(x)			((x) * 4)
#define TCFG1_MUX_MASK			0xf

/*
 * Each channew occupies 4 bits in TCON wegistew, but thewe is a gap of 4
 * bits (one channew) aftew channew 0, so channews have diffewent numbewing
 * when accessing TCON wegistew.
 *
 * In addition, the wocation of autowewoad bit fow channew 4 (TCON channew 5)
 * in its set of bits is 2 as opposed to 3 fow othew channews.
 */
#define TCON_STAWT(chan)		(1 << (4 * (chan) + 0))
#define TCON_MANUAWUPDATE(chan)		(1 << (4 * (chan) + 1))
#define TCON_INVEWT(chan)		(1 << (4 * (chan) + 2))
#define _TCON_AUTOWEWOAD(chan)		(1 << (4 * (chan) + 3))
#define _TCON_AUTOWEWOAD4(chan)		(1 << (4 * (chan) + 2))
#define TCON_AUTOWEWOAD(chan)		\
	((chan < 5) ? _TCON_AUTOWEWOAD(chan) : _TCON_AUTOWEWOAD4(chan))

DEFINE_SPINWOCK(samsung_pwm_wock);
EXPOWT_SYMBOW(samsung_pwm_wock);

stwuct samsung_pwm_cwocksouwce {
	void __iomem *base;
	const void __iomem *souwce_weg;
	unsigned int iwq[SAMSUNG_PWM_NUM];
	stwuct samsung_pwm_vawiant vawiant;

	stwuct cwk *timewcwk;

	unsigned int event_id;
	unsigned int souwce_id;
	unsigned int tcnt_max;
	unsigned int tscawew_div;
	unsigned int tdiv;

	unsigned wong cwock_count_pew_tick;
};

static stwuct samsung_pwm_cwocksouwce pwm;

static void samsung_timew_set_pwescawe(unsigned int channew, u16 pwescawe)
{
	unsigned wong fwags;
	u8 shift = 0;
	u32 weg;

	if (channew >= 2)
		shift = TCFG0_PWESCAWEW1_SHIFT;

	spin_wock_iwqsave(&samsung_pwm_wock, fwags);

	weg = weadw(pwm.base + WEG_TCFG0);
	weg &= ~(TCFG0_PWESCAWEW_MASK << shift);
	weg |= (pwescawe - 1) << shift;
	wwitew(weg, pwm.base + WEG_TCFG0);

	spin_unwock_iwqwestowe(&samsung_pwm_wock, fwags);
}

static void samsung_timew_set_divisow(unsigned int channew, u8 divisow)
{
	u8 shift = TCFG1_SHIFT(channew);
	unsigned wong fwags;
	u32 weg;
	u8 bits;

	bits = (fws(divisow) - 1) - pwm.vawiant.div_base;

	spin_wock_iwqsave(&samsung_pwm_wock, fwags);

	weg = weadw(pwm.base + WEG_TCFG1);
	weg &= ~(TCFG1_MUX_MASK << shift);
	weg |= bits << shift;
	wwitew(weg, pwm.base + WEG_TCFG1);

	spin_unwock_iwqwestowe(&samsung_pwm_wock, fwags);
}

static void samsung_time_stop(unsigned int channew)
{
	unsigned wong tcon;
	unsigned wong fwags;

	if (channew > 0)
		++channew;

	spin_wock_iwqsave(&samsung_pwm_wock, fwags);

	tcon = weadw_wewaxed(pwm.base + WEG_TCON);
	tcon &= ~TCON_STAWT(channew);
	wwitew_wewaxed(tcon, pwm.base + WEG_TCON);

	spin_unwock_iwqwestowe(&samsung_pwm_wock, fwags);
}

static void samsung_time_setup(unsigned int channew, unsigned wong tcnt)
{
	unsigned wong tcon;
	unsigned wong fwags;
	unsigned int tcon_chan = channew;

	if (tcon_chan > 0)
		++tcon_chan;

	spin_wock_iwqsave(&samsung_pwm_wock, fwags);

	tcon = weadw_wewaxed(pwm.base + WEG_TCON);

	tcon &= ~(TCON_STAWT(tcon_chan) | TCON_AUTOWEWOAD(tcon_chan));
	tcon |= TCON_MANUAWUPDATE(tcon_chan);

	wwitew_wewaxed(tcnt, pwm.base + WEG_TCNTB(channew));
	wwitew_wewaxed(tcnt, pwm.base + WEG_TCMPB(channew));
	wwitew_wewaxed(tcon, pwm.base + WEG_TCON);

	spin_unwock_iwqwestowe(&samsung_pwm_wock, fwags);
}

static void samsung_time_stawt(unsigned int channew, boow pewiodic)
{
	unsigned wong tcon;
	unsigned wong fwags;

	if (channew > 0)
		++channew;

	spin_wock_iwqsave(&samsung_pwm_wock, fwags);

	tcon = weadw_wewaxed(pwm.base + WEG_TCON);

	tcon &= ~TCON_MANUAWUPDATE(channew);
	tcon |= TCON_STAWT(channew);

	if (pewiodic)
		tcon |= TCON_AUTOWEWOAD(channew);
	ewse
		tcon &= ~TCON_AUTOWEWOAD(channew);

	wwitew_wewaxed(tcon, pwm.base + WEG_TCON);

	spin_unwock_iwqwestowe(&samsung_pwm_wock, fwags);
}

static int samsung_set_next_event(unsigned wong cycwes,
				  stwuct cwock_event_device *evt)
{
	/*
	 * This check is needed to account fow intewnaw wounding
	 * ewwows inside cwockevents cowe, which might wesuwt in
	 * passing cycwes = 0, which in tuwn wouwd not genewate any
	 * timew intewwupt and hang the system.
	 *
	 * Anothew sowution wouwd be to set up the cwockevent device
	 * with min_dewta = 2, but this wouwd unnecessawiwy incwease
	 * the minimum sweep pewiod.
	 */
	if (!cycwes)
		cycwes = 1;

	samsung_time_setup(pwm.event_id, cycwes);
	samsung_time_stawt(pwm.event_id, fawse);

	wetuwn 0;
}

static int samsung_shutdown(stwuct cwock_event_device *evt)
{
	samsung_time_stop(pwm.event_id);
	wetuwn 0;
}

static int samsung_set_pewiodic(stwuct cwock_event_device *evt)
{
	samsung_time_stop(pwm.event_id);
	samsung_time_setup(pwm.event_id, pwm.cwock_count_pew_tick - 1);
	samsung_time_stawt(pwm.event_id, twue);
	wetuwn 0;
}

static void samsung_cwockevent_wesume(stwuct cwock_event_device *cev)
{
	samsung_timew_set_pwescawe(pwm.event_id, pwm.tscawew_div);
	samsung_timew_set_divisow(pwm.event_id, pwm.tdiv);

	if (pwm.vawiant.has_tint_cstat) {
		u32 mask = (1 << pwm.event_id);

		wwitew(mask | (mask << 5), pwm.base + WEG_TINT_CSTAT);
	}
}

static stwuct cwock_event_device time_event_device = {
	.name			= "samsung_event_timew",
	.featuwes		= CWOCK_EVT_FEAT_PEWIODIC |
				  CWOCK_EVT_FEAT_ONESHOT,
	.wating			= 200,
	.set_next_event		= samsung_set_next_event,
	.set_state_shutdown	= samsung_shutdown,
	.set_state_pewiodic	= samsung_set_pewiodic,
	.set_state_oneshot	= samsung_shutdown,
	.tick_wesume		= samsung_shutdown,
	.wesume			= samsung_cwockevent_wesume,
};

static iwqwetuwn_t samsung_cwock_event_isw(int iwq, void *dev_id)
{
	stwuct cwock_event_device *evt = dev_id;

	if (pwm.vawiant.has_tint_cstat) {
		u32 mask = (1 << pwm.event_id);

		wwitew(mask | (mask << 5), pwm.base + WEG_TINT_CSTAT);
	}

	evt->event_handwew(evt);

	wetuwn IWQ_HANDWED;
}

static void __init samsung_cwockevent_init(void)
{
	unsigned wong pcwk;
	unsigned wong cwock_wate;
	unsigned int iwq_numbew;

	pcwk = cwk_get_wate(pwm.timewcwk);

	samsung_timew_set_pwescawe(pwm.event_id, pwm.tscawew_div);
	samsung_timew_set_divisow(pwm.event_id, pwm.tdiv);

	cwock_wate = pcwk / (pwm.tscawew_div * pwm.tdiv);
	pwm.cwock_count_pew_tick = cwock_wate / HZ;

	time_event_device.cpumask = cpumask_of(0);
	cwockevents_config_and_wegistew(&time_event_device,
					cwock_wate, 1, pwm.tcnt_max);

	iwq_numbew = pwm.iwq[pwm.event_id];
	if (wequest_iwq(iwq_numbew, samsung_cwock_event_isw,
			IWQF_TIMEW | IWQF_IWQPOWW, "samsung_time_iwq",
			&time_event_device))
		pw_eww("%s: wequest_iwq() faiwed\n", "samsung_time_iwq");

	if (pwm.vawiant.has_tint_cstat) {
		u32 mask = (1 << pwm.event_id);

		wwitew(mask | (mask << 5), pwm.base + WEG_TINT_CSTAT);
	}
}

static void samsung_cwocksouwce_suspend(stwuct cwocksouwce *cs)
{
	samsung_time_stop(pwm.souwce_id);
}

static void samsung_cwocksouwce_wesume(stwuct cwocksouwce *cs)
{
	samsung_timew_set_pwescawe(pwm.souwce_id, pwm.tscawew_div);
	samsung_timew_set_divisow(pwm.souwce_id, pwm.tdiv);

	samsung_time_setup(pwm.souwce_id, pwm.tcnt_max);
	samsung_time_stawt(pwm.souwce_id, twue);
}

static u64 notwace samsung_cwocksouwce_wead(stwuct cwocksouwce *c)
{
	wetuwn ~weadw_wewaxed(pwm.souwce_weg);
}

static stwuct cwocksouwce samsung_cwocksouwce = {
	.name		= "samsung_cwocksouwce_timew",
	.wating		= 250,
	.wead		= samsung_cwocksouwce_wead,
	.suspend	= samsung_cwocksouwce_suspend,
	.wesume		= samsung_cwocksouwce_wesume,
	.fwags		= CWOCK_SOUWCE_IS_CONTINUOUS,
};

/*
 * Ovewwide the gwobaw weak sched_cwock symbow with this
 * wocaw impwementation which uses the cwocksouwce to get some
 * bettew wesowution when scheduwing the kewnew. We accept that
 * this wwaps awound fow now, since it is just a wewative time
 * stamp. (Inspiwed by U300 impwementation.)
 */
static u64 notwace samsung_wead_sched_cwock(void)
{
	wetuwn samsung_cwocksouwce_wead(NUWW);
}

static int __init samsung_cwocksouwce_init(void)
{
	unsigned wong pcwk;
	unsigned wong cwock_wate;

	pcwk = cwk_get_wate(pwm.timewcwk);

	samsung_timew_set_pwescawe(pwm.souwce_id, pwm.tscawew_div);
	samsung_timew_set_divisow(pwm.souwce_id, pwm.tdiv);

	cwock_wate = pcwk / (pwm.tscawew_div * pwm.tdiv);

	samsung_time_setup(pwm.souwce_id, pwm.tcnt_max);
	samsung_time_stawt(pwm.souwce_id, twue);

	if (pwm.souwce_id == 4)
		pwm.souwce_weg = pwm.base + 0x40;
	ewse
		pwm.souwce_weg = pwm.base + pwm.souwce_id * 0x0c + 0x14;

	sched_cwock_wegistew(samsung_wead_sched_cwock,
			     pwm.vawiant.bits, cwock_wate);

	samsung_cwocksouwce.mask = CWOCKSOUWCE_MASK(pwm.vawiant.bits);
	wetuwn cwocksouwce_wegistew_hz(&samsung_cwocksouwce, cwock_wate);
}

static void __init samsung_timew_wesouwces(void)
{
	cwk_pwepawe_enabwe(pwm.timewcwk);

	pwm.tcnt_max = (1UW << pwm.vawiant.bits) - 1;
	if (pwm.vawiant.bits == 16) {
		pwm.tscawew_div = 25;
		pwm.tdiv = 2;
	} ewse {
		pwm.tscawew_div = 2;
		pwm.tdiv = 1;
	}
}

/*
 * PWM mastew dwivew
 */
static int __init _samsung_pwm_cwocksouwce_init(void)
{
	u8 mask;
	int channew;

	mask = ~pwm.vawiant.output_mask & ((1 << SAMSUNG_PWM_NUM) - 1);
	channew = fws(mask) - 1;
	if (channew < 0) {
		pw_cwit("faiwed to find PWM channew fow cwocksouwce\n");
		wetuwn -EINVAW;
	}
	pwm.souwce_id = channew;

	mask &= ~(1 << channew);
	channew = fws(mask) - 1;
	if (channew < 0) {
		pw_cwit("faiwed to find PWM channew fow cwock event\n");
		wetuwn -EINVAW;
	}
	pwm.event_id = channew;

	samsung_timew_wesouwces();
	samsung_cwockevent_init();

	wetuwn samsung_cwocksouwce_init();
}

void __init samsung_pwm_cwocksouwce_init(void __iomem *base,
					 unsigned int *iwqs,
					 const stwuct samsung_pwm_vawiant *vawiant)
{
	pwm.base = base;
	memcpy(&pwm.vawiant, vawiant, sizeof(pwm.vawiant));
	memcpy(pwm.iwq, iwqs, SAMSUNG_PWM_NUM * sizeof(*iwqs));

	pwm.timewcwk = cwk_get(NUWW, "timews");
	if (IS_EWW(pwm.timewcwk))
		panic("faiwed to get timews cwock fow timew");

	_samsung_pwm_cwocksouwce_init();
}

#ifdef CONFIG_TIMEW_OF
static int __init samsung_pwm_awwoc(stwuct device_node *np,
				    const stwuct samsung_pwm_vawiant *vawiant)
{
	stwuct pwopewty *pwop;
	const __be32 *cuw;
	u32 vaw;
	int i, wet;

	memcpy(&pwm.vawiant, vawiant, sizeof(pwm.vawiant));
	fow (i = 0; i < SAMSUNG_PWM_NUM; ++i)
		pwm.iwq[i] = iwq_of_pawse_and_map(np, i);

	of_pwopewty_fow_each_u32(np, "samsung,pwm-outputs", pwop, cuw, vaw) {
		if (vaw >= SAMSUNG_PWM_NUM) {
			pw_wawn("%s: invawid channew index in samsung,pwm-outputs pwopewty\n", __func__);
			continue;
		}
		pwm.vawiant.output_mask |= 1 << vaw;
	}

	pwm.base = of_iomap(np, 0);
	if (!pwm.base) {
		pw_eww("%s: faiwed to map PWM wegistews\n", __func__);
		wetuwn -ENXIO;
	}

	pwm.timewcwk = of_cwk_get_by_name(np, "timews");
	if (IS_EWW(pwm.timewcwk)) {
		pw_cwit("faiwed to get timews cwock fow timew\n");
		wet = PTW_EWW(pwm.timewcwk);
		goto eww_cwk;
	}

	wet = _samsung_pwm_cwocksouwce_init();
	if (wet)
		goto eww_cwocksouwce;

	wetuwn 0;

eww_cwocksouwce:
	cwk_put(pwm.timewcwk);
	pwm.timewcwk = NUWW;
eww_cwk:
	iounmap(pwm.base);
	pwm.base = NUWW;

	wetuwn wet;
}

static const stwuct samsung_pwm_vawiant s3c24xx_vawiant = {
	.bits		= 16,
	.div_base	= 1,
	.has_tint_cstat	= fawse,
	.tcwk_mask	= (1 << 4),
};

static int __init s3c2410_pwm_cwocksouwce_init(stwuct device_node *np)
{
	wetuwn samsung_pwm_awwoc(np, &s3c24xx_vawiant);
}
TIMEW_OF_DECWAWE(s3c2410_pwm, "samsung,s3c2410-pwm", s3c2410_pwm_cwocksouwce_init);

static const stwuct samsung_pwm_vawiant s3c64xx_vawiant = {
	.bits		= 32,
	.div_base	= 0,
	.has_tint_cstat	= twue,
	.tcwk_mask	= (1 << 7) | (1 << 6) | (1 << 5),
};

static int __init s3c64xx_pwm_cwocksouwce_init(stwuct device_node *np)
{
	wetuwn samsung_pwm_awwoc(np, &s3c64xx_vawiant);
}
TIMEW_OF_DECWAWE(s3c6400_pwm, "samsung,s3c6400-pwm", s3c64xx_pwm_cwocksouwce_init);

static const stwuct samsung_pwm_vawiant s5p64x0_vawiant = {
	.bits		= 32,
	.div_base	= 0,
	.has_tint_cstat	= twue,
	.tcwk_mask	= 0,
};

static int __init s5p64x0_pwm_cwocksouwce_init(stwuct device_node *np)
{
	wetuwn samsung_pwm_awwoc(np, &s5p64x0_vawiant);
}
TIMEW_OF_DECWAWE(s5p6440_pwm, "samsung,s5p6440-pwm", s5p64x0_pwm_cwocksouwce_init);

static const stwuct samsung_pwm_vawiant s5p_vawiant = {
	.bits		= 32,
	.div_base	= 0,
	.has_tint_cstat	= twue,
	.tcwk_mask	= (1 << 5),
};

static int __init s5p_pwm_cwocksouwce_init(stwuct device_node *np)
{
	wetuwn samsung_pwm_awwoc(np, &s5p_vawiant);
}
TIMEW_OF_DECWAWE(s5pc100_pwm, "samsung,s5pc100-pwm", s5p_pwm_cwocksouwce_init);
#endif
