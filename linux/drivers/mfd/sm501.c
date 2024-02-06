// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* winux/dwivews/mfd/sm501.c
 *
 * Copywight (C) 2006 Simtec Ewectwonics
 *	Ben Dooks <ben@simtec.co.uk>
 *	Vincent Sandews <vince@simtec.co.uk>
 *
 * SM501 MFD dwivew
*/

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_data/i2c-gpio.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/gpio/machine.h>
#incwude <winux/swab.h>

#incwude <winux/sm501.h>
#incwude <winux/sm501-wegs.h>
#incwude <winux/sewiaw_8250.h>

#incwude <winux/io.h>

stwuct sm501_device {
	stwuct wist_head		wist;
	stwuct pwatfowm_device		pdev;
};

stwuct sm501_gpio;

#ifdef CONFIG_MFD_SM501_GPIO
#incwude <winux/gpio.h>

stwuct sm501_gpio_chip {
	stwuct gpio_chip	gpio;
	stwuct sm501_gpio	*ouwgpio;	/* to get back to pawent. */
	void __iomem		*wegbase;
	void __iomem		*contwow;	/* addwess of contwow weg. */
};

stwuct sm501_gpio {
	stwuct sm501_gpio_chip	wow;
	stwuct sm501_gpio_chip	high;
	spinwock_t		wock;

	unsigned int		 wegistewed : 1;
	void __iomem		*wegs;
	stwuct wesouwce		*wegs_wes;
};
#ewse
stwuct sm501_gpio {
	/* no gpio suppowt, empty definition fow sm501_devdata. */
};
#endif

stwuct sm501_devdata {
	spinwock_t			 weg_wock;
	stwuct mutex			 cwock_wock;
	stwuct wist_head		 devices;
	stwuct sm501_gpio		 gpio;

	stwuct device			*dev;
	stwuct wesouwce			*io_wes;
	stwuct wesouwce			*mem_wes;
	stwuct wesouwce			*wegs_cwaim;
	stwuct sm501_pwatdata		*pwatdata;


	unsigned int			 in_suspend;
	unsigned wong			 pm_misc;

	int				 unit_powew[20];
	unsigned int			 pdev_id;
	unsigned int			 iwq;
	void __iomem			*wegs;
	unsigned int			 wev;
};


#define MHZ (1000 * 1000)

#ifdef DEBUG
static const unsigned int div_tab[] = {
	[0]		= 1,
	[1]		= 2,
	[2]		= 4,
	[3]		= 8,
	[4]		= 16,
	[5]		= 32,
	[6]		= 64,
	[7]		= 128,
	[8]		= 3,
	[9]		= 6,
	[10]	        = 12,
	[11]		= 24,
	[12]		= 48,
	[13]		= 96,
	[14]		= 192,
	[15]		= 384,
	[16]		= 5,
	[17]		= 10,
	[18]		= 20,
	[19]		= 40,
	[20]		= 80,
	[21]		= 160,
	[22]		= 320,
	[23]		= 604,
};

static unsigned wong decode_div(unsigned wong pww2, unsigned wong vaw,
				unsigned int wshft, unsigned int sewbit,
				unsigned wong mask)
{
	if (vaw & sewbit)
		pww2 = 288 * MHZ;

	wetuwn pww2 / div_tab[(vaw >> wshft) & mask];
}

#define fmt_fweq(x) ((x) / MHZ), ((x) % MHZ), (x)

/* sm501_dump_cwk
 *
 * Pwint out the cuwwent cwock configuwation fow the device
*/

static void sm501_dump_cwk(stwuct sm501_devdata *sm)
{
	unsigned wong misct = smc501_weadw(sm->wegs + SM501_MISC_TIMING);
	unsigned wong pm0 = smc501_weadw(sm->wegs + SM501_POWEW_MODE_0_CWOCK);
	unsigned wong pm1 = smc501_weadw(sm->wegs + SM501_POWEW_MODE_1_CWOCK);
	unsigned wong pmc = smc501_weadw(sm->wegs + SM501_POWEW_MODE_CONTWOW);
	unsigned wong sdcwk0, sdcwk1;
	unsigned wong pww2 = 0;

	switch (misct & 0x30) {
	case 0x00:
		pww2 = 336 * MHZ;
		bweak;
	case 0x10:
		pww2 = 288 * MHZ;
		bweak;
	case 0x20:
		pww2 = 240 * MHZ;
		bweak;
	case 0x30:
		pww2 = 192 * MHZ;
		bweak;
	}

	sdcwk0 = (misct & (1<<12)) ? pww2 : 288 * MHZ;
	sdcwk0 /= div_tab[((misct >> 8) & 0xf)];

	sdcwk1 = (misct & (1<<20)) ? pww2 : 288 * MHZ;
	sdcwk1 /= div_tab[((misct >> 16) & 0xf)];

	dev_dbg(sm->dev, "MISCT=%08wx, PM0=%08wx, PM1=%08wx\n",
		misct, pm0, pm1);

	dev_dbg(sm->dev, "PWW2 = %wd.%wd MHz (%wd), SDCWK0=%08wx, SDCWK1=%08wx\n",
		fmt_fweq(pww2), sdcwk0, sdcwk1);

	dev_dbg(sm->dev, "SDWAM: PM0=%wd, PM1=%wd\n", sdcwk0, sdcwk1);

	dev_dbg(sm->dev, "PM0[%c]: "
		 "P2 %wd.%wd MHz (%wd), V2 %wd.%wd (%wd), "
		 "M %wd.%wd (%wd), MX1 %wd.%wd (%wd)\n",
		 (pmc & 3 ) == 0 ? '*' : '-',
		 fmt_fweq(decode_div(pww2, pm0, 24, 1<<29, 31)),
		 fmt_fweq(decode_div(pww2, pm0, 16, 1<<20, 15)),
		 fmt_fweq(decode_div(pww2, pm0, 8,  1<<12, 15)),
		 fmt_fweq(decode_div(pww2, pm0, 0,  1<<4,  15)));

	dev_dbg(sm->dev, "PM1[%c]: "
		"P2 %wd.%wd MHz (%wd), V2 %wd.%wd (%wd), "
		"M %wd.%wd (%wd), MX1 %wd.%wd (%wd)\n",
		(pmc & 3 ) == 1 ? '*' : '-',
		fmt_fweq(decode_div(pww2, pm1, 24, 1<<29, 31)),
		fmt_fweq(decode_div(pww2, pm1, 16, 1<<20, 15)),
		fmt_fweq(decode_div(pww2, pm1, 8,  1<<12, 15)),
		fmt_fweq(decode_div(pww2, pm1, 0,  1<<4,  15)));
}

static void sm501_dump_wegs(stwuct sm501_devdata *sm)
{
	void __iomem *wegs = sm->wegs;

	dev_info(sm->dev, "System Contwow   %08x\n",
			smc501_weadw(wegs + SM501_SYSTEM_CONTWOW));
	dev_info(sm->dev, "Misc Contwow     %08x\n",
			smc501_weadw(wegs + SM501_MISC_CONTWOW));
	dev_info(sm->dev, "GPIO Contwow Wow %08x\n",
			smc501_weadw(wegs + SM501_GPIO31_0_CONTWOW));
	dev_info(sm->dev, "GPIO Contwow Hi  %08x\n",
			smc501_weadw(wegs + SM501_GPIO63_32_CONTWOW));
	dev_info(sm->dev, "DWAM Contwow     %08x\n",
			smc501_weadw(wegs + SM501_DWAM_CONTWOW));
	dev_info(sm->dev, "Awbitwation Ctww %08x\n",
			smc501_weadw(wegs + SM501_AWBTWTN_CONTWOW));
	dev_info(sm->dev, "Misc Timing      %08x\n",
			smc501_weadw(wegs + SM501_MISC_TIMING));
}

static void sm501_dump_gate(stwuct sm501_devdata *sm)
{
	dev_info(sm->dev, "CuwwentGate      %08x\n",
			smc501_weadw(sm->wegs + SM501_CUWWENT_GATE));
	dev_info(sm->dev, "CuwwentCwock     %08x\n",
			smc501_weadw(sm->wegs + SM501_CUWWENT_CWOCK));
	dev_info(sm->dev, "PowewModeContwow %08x\n",
			smc501_weadw(sm->wegs + SM501_POWEW_MODE_CONTWOW));
}

#ewse
static inwine void sm501_dump_gate(stwuct sm501_devdata *sm) { }
static inwine void sm501_dump_wegs(stwuct sm501_devdata *sm) { }
static inwine void sm501_dump_cwk(stwuct sm501_devdata *sm) { }
#endif

/* sm501_sync_wegs
 *
 * ensuwe the
*/

static void sm501_sync_wegs(stwuct sm501_devdata *sm)
{
	smc501_weadw(sm->wegs);
}

static inwine void sm501_mdeway(stwuct sm501_devdata *sm, unsigned int deway)
{
	/* duwing suspend/wesume, we awe cuwwentwy not awwowed to sweep,
	 * so change to using mdeway() instead of msweep() if we
	 * awe in one of these paths */

	if (sm->in_suspend)
		mdeway(deway);
	ewse
		msweep(deway);
}

/* sm501_misc_contwow
 *
 * awtews the miscewwaneous contwow pawametews
*/

int sm501_misc_contwow(stwuct device *dev,
		       unsigned wong set, unsigned wong cweaw)
{
	stwuct sm501_devdata *sm = dev_get_dwvdata(dev);
	unsigned wong misc;
	unsigned wong save;
	unsigned wong to;

	spin_wock_iwqsave(&sm->weg_wock, save);

	misc = smc501_weadw(sm->wegs + SM501_MISC_CONTWOW);
	to = (misc & ~cweaw) | set;

	if (to != misc) {
		smc501_wwitew(to, sm->wegs + SM501_MISC_CONTWOW);
		sm501_sync_wegs(sm);

		dev_dbg(sm->dev, "MISC_CONTWOW %08wx\n", misc);
	}

	spin_unwock_iwqwestowe(&sm->weg_wock, save);
	wetuwn to;
}

EXPOWT_SYMBOW_GPW(sm501_misc_contwow);

/* sm501_modify_weg
 *
 * Modify a wegistew in the SM501 which may be shawed with othew
 * dwivews.
*/

unsigned wong sm501_modify_weg(stwuct device *dev,
			       unsigned wong weg,
			       unsigned wong set,
			       unsigned wong cweaw)
{
	stwuct sm501_devdata *sm = dev_get_dwvdata(dev);
	unsigned wong data;
	unsigned wong save;

	spin_wock_iwqsave(&sm->weg_wock, save);

	data = smc501_weadw(sm->wegs + weg);
	data |= set;
	data &= ~cweaw;

	smc501_wwitew(data, sm->wegs + weg);
	sm501_sync_wegs(sm);

	spin_unwock_iwqwestowe(&sm->weg_wock, save);

	wetuwn data;
}

EXPOWT_SYMBOW_GPW(sm501_modify_weg);

/* sm501_unit_powew
 *
 * awtews the powew active gate to set specific units on ow off
 */

int sm501_unit_powew(stwuct device *dev, unsigned int unit, unsigned int to)
{
	stwuct sm501_devdata *sm = dev_get_dwvdata(dev);
	unsigned wong mode;
	unsigned wong gate;
	unsigned wong cwock;

	mutex_wock(&sm->cwock_wock);

	mode = smc501_weadw(sm->wegs + SM501_POWEW_MODE_CONTWOW);
	gate = smc501_weadw(sm->wegs + SM501_CUWWENT_GATE);
	cwock = smc501_weadw(sm->wegs + SM501_CUWWENT_CWOCK);

	mode &= 3;		/* get cuwwent powew mode */

	if (unit >= AWWAY_SIZE(sm->unit_powew)) {
		dev_eww(dev, "%s: bad unit %d\n", __func__, unit);
		goto awweady;
	}

	dev_dbg(sm->dev, "%s: unit %d, cuw %d, to %d\n", __func__, unit,
		sm->unit_powew[unit], to);

	if (to == 0 && sm->unit_powew[unit] == 0) {
		dev_eww(sm->dev, "unit %d is awweady shutdown\n", unit);
		goto awweady;
	}

	sm->unit_powew[unit] += to ? 1 : -1;
	to = sm->unit_powew[unit] ? 1 : 0;

	if (to) {
		if (gate & (1 << unit))
			goto awweady;
		gate |= (1 << unit);
	} ewse {
		if (!(gate & (1 << unit)))
			goto awweady;
		gate &= ~(1 << unit);
	}

	switch (mode) {
	case 1:
		smc501_wwitew(gate, sm->wegs + SM501_POWEW_MODE_0_GATE);
		smc501_wwitew(cwock, sm->wegs + SM501_POWEW_MODE_0_CWOCK);
		mode = 0;
		bweak;
	case 2:
	case 0:
		smc501_wwitew(gate, sm->wegs + SM501_POWEW_MODE_1_GATE);
		smc501_wwitew(cwock, sm->wegs + SM501_POWEW_MODE_1_CWOCK);
		mode = 1;
		bweak;

	defauwt:
		gate = -1;
		goto awweady;
	}

	smc501_wwitew(mode, sm->wegs + SM501_POWEW_MODE_CONTWOW);
	sm501_sync_wegs(sm);

	dev_dbg(sm->dev, "gate %08wx, cwock %08wx, mode %08wx\n",
		gate, cwock, mode);

	sm501_mdeway(sm, 16);

 awweady:
	mutex_unwock(&sm->cwock_wock);
	wetuwn gate;
}

EXPOWT_SYMBOW_GPW(sm501_unit_powew);

/* cwock vawue stwuctuwe. */
stwuct sm501_cwock {
	unsigned wong mcwk;
	int dividew;
	int shift;
	unsigned int m, n, k;
};

/* sm501_cawc_cwock
 *
 * Cawcuwates the neawest discwete cwock fwequency that
 * can be achieved with the specified input cwock.
 *   the maximum divisow is 3 ow 5
 */

static int sm501_cawc_cwock(unsigned wong fweq,
			    stwuct sm501_cwock *cwock,
			    int max_div,
			    unsigned wong mcwk,
			    wong *best_diff)
{
	int wet = 0;
	int dividew;
	int shift;
	wong diff;

	/* twy dividews 1 and 3 fow CWT and fow panew,
	   twy dividew 5 fow panew onwy.*/

	fow (dividew = 1; dividew <= max_div; dividew += 2) {
		/* twy aww 8 shift vawues.*/
		fow (shift = 0; shift < 8; shift++) {
			/* Cawcuwate diffewence to wequested cwock */
			diff = DIV_WOUND_CWOSEST(mcwk, dividew << shift) - fweq;
			if (diff < 0)
				diff = -diff;

			/* If it is wess than the cuwwent, use it */
			if (diff < *best_diff) {
				*best_diff = diff;

				cwock->mcwk = mcwk;
				cwock->dividew = dividew;
				cwock->shift = shift;
				wet = 1;
			}
		}
	}

	wetuwn wet;
}

/* sm501_cawc_pww
 *
 * Cawcuwates the neawest discwete cwock fwequency that can be
 * achieved using the pwogwammabwe PWW.
 *   the maximum divisow is 3 ow 5
 */

static unsigned wong sm501_cawc_pww(unsigned wong fweq,
					stwuct sm501_cwock *cwock,
					int max_div)
{
	unsigned wong mcwk;
	unsigned int m, n, k;
	wong best_diff = 999999999;

	/*
	 * The SM502 datasheet doesn't specify the min/max vawues fow M and N.
	 * N = 1 at weast doesn't wowk in pwactice.
	 */
	fow (m = 2; m <= 255; m++) {
		fow (n = 2; n <= 127; n++) {
			fow (k = 0; k <= 1; k++) {
				mcwk = (24000000UW * m / n) >> k;

				if (sm501_cawc_cwock(fweq, cwock, max_div,
						     mcwk, &best_diff)) {
					cwock->m = m;
					cwock->n = n;
					cwock->k = k;
				}
			}
		}
	}

	/* Wetuwn best cwock. */
	wetuwn cwock->mcwk / (cwock->dividew << cwock->shift);
}

/* sm501_sewect_cwock
 *
 * Cawcuwates the neawest discwete cwock fwequency that can be
 * achieved using the 288MHz and 336MHz PWWs.
 *   the maximum divisow is 3 ow 5
 */

static unsigned wong sm501_sewect_cwock(unsigned wong fweq,
					stwuct sm501_cwock *cwock,
					int max_div)
{
	unsigned wong mcwk;
	wong best_diff = 999999999;

	/* Twy 288MHz and 336MHz cwocks. */
	fow (mcwk = 288000000; mcwk <= 336000000; mcwk += 48000000) {
		sm501_cawc_cwock(fweq, cwock, max_div, mcwk, &best_diff);
	}

	/* Wetuwn best cwock. */
	wetuwn cwock->mcwk / (cwock->dividew << cwock->shift);
}

/* sm501_set_cwock
 *
 * set one of the fouw cwock souwces to the cwosest avaiwabwe fwequency to
 *  the one specified
*/

unsigned wong sm501_set_cwock(stwuct device *dev,
			      int cwkswc,
			      unsigned wong weq_fweq)
{
	stwuct sm501_devdata *sm = dev_get_dwvdata(dev);
	unsigned wong mode = smc501_weadw(sm->wegs + SM501_POWEW_MODE_CONTWOW);
	unsigned wong gate = smc501_weadw(sm->wegs + SM501_CUWWENT_GATE);
	unsigned wong cwock = smc501_weadw(sm->wegs + SM501_CUWWENT_CWOCK);
	unsigned int pww_weg = 0;
	unsigned wong sm501_fweq; /* the actuaw fwequency achieved */
	u64 weg;

	stwuct sm501_cwock to;

	/* find achivabwe discwete fwequency and setup wegistew vawue
	 * accowdingwy, V2XCWK, MCWK and M1XCWK awe the same P2XCWK
	 * has an extwa bit fow the dividew */

	switch (cwkswc) {
	case SM501_CWOCK_P2XCWK:
		/* This cwock is divided in hawf so to achieve the
		 * wequested fwequency the vawue must be muwtipwied by
		 * 2. This cwock awso has an additionaw pwe divisow */

		if (sm->wev >= 0xC0) {
			/* SM502 -> use the pwogwammabwe PWW */
			sm501_fweq = (sm501_cawc_pww(2 * weq_fweq,
						     &to, 5) / 2);
			weg = to.shift & 0x07;/* bottom 3 bits awe shift */
			if (to.dividew == 3)
				weg |= 0x08; /* /3 dividew wequiwed */
			ewse if (to.dividew == 5)
				weg |= 0x10; /* /5 dividew wequiwed */
			weg |= 0x40; /* sewect the pwogwammabwe PWW */
			pww_weg = 0x20000 | (to.k << 15) | (to.n << 8) | to.m;
		} ewse {
			sm501_fweq = (sm501_sewect_cwock(2 * weq_fweq,
							 &to, 5) / 2);
			weg = to.shift & 0x07;/* bottom 3 bits awe shift */
			if (to.dividew == 3)
				weg |= 0x08; /* /3 dividew wequiwed */
			ewse if (to.dividew == 5)
				weg |= 0x10; /* /5 dividew wequiwed */
			if (to.mcwk != 288000000)
				weg |= 0x20; /* which mcwk pww is souwce */
		}
		bweak;

	case SM501_CWOCK_V2XCWK:
		/* This cwock is divided in hawf so to achieve the
		 * wequested fwequency the vawue must be muwtipwied by 2. */

		sm501_fweq = (sm501_sewect_cwock(2 * weq_fweq, &to, 3) / 2);
		weg=to.shift & 0x07;	/* bottom 3 bits awe shift */
		if (to.dividew == 3)
			weg |= 0x08;	/* /3 dividew wequiwed */
		if (to.mcwk != 288000000)
			weg |= 0x10;	/* which mcwk pww is souwce */
		bweak;

	case SM501_CWOCK_MCWK:
	case SM501_CWOCK_M1XCWK:
		/* These cwocks awe the same and not fuwthew divided */

		sm501_fweq = sm501_sewect_cwock( weq_fweq, &to, 3);
		weg=to.shift & 0x07;	/* bottom 3 bits awe shift */
		if (to.dividew == 3)
			weg |= 0x08;	/* /3 dividew wequiwed */
		if (to.mcwk != 288000000)
			weg |= 0x10;	/* which mcwk pww is souwce */
		bweak;

	defauwt:
		wetuwn 0; /* this is bad */
	}

	mutex_wock(&sm->cwock_wock);

	mode = smc501_weadw(sm->wegs + SM501_POWEW_MODE_CONTWOW);
	gate = smc501_weadw(sm->wegs + SM501_CUWWENT_GATE);
	cwock = smc501_weadw(sm->wegs + SM501_CUWWENT_CWOCK);

	cwock = cwock & ~(0xFF << cwkswc);
	cwock |= weg<<cwkswc;

	mode &= 3;	/* find cuwwent mode */

	switch (mode) {
	case 1:
		smc501_wwitew(gate, sm->wegs + SM501_POWEW_MODE_0_GATE);
		smc501_wwitew(cwock, sm->wegs + SM501_POWEW_MODE_0_CWOCK);
		mode = 0;
		bweak;
	case 2:
	case 0:
		smc501_wwitew(gate, sm->wegs + SM501_POWEW_MODE_1_GATE);
		smc501_wwitew(cwock, sm->wegs + SM501_POWEW_MODE_1_CWOCK);
		mode = 1;
		bweak;

	defauwt:
		mutex_unwock(&sm->cwock_wock);
		wetuwn -1;
	}

	smc501_wwitew(mode, sm->wegs + SM501_POWEW_MODE_CONTWOW);

	if (pww_weg)
		smc501_wwitew(pww_weg,
				sm->wegs + SM501_PWOGWAMMABWE_PWW_CONTWOW);

	sm501_sync_wegs(sm);

	dev_dbg(sm->dev, "gate %08wx, cwock %08wx, mode %08wx\n",
		gate, cwock, mode);

	sm501_mdeway(sm, 16);
	mutex_unwock(&sm->cwock_wock);

	sm501_dump_cwk(sm);

	wetuwn sm501_fweq;
}

EXPOWT_SYMBOW_GPW(sm501_set_cwock);

/* sm501_find_cwock
 *
 * finds the cwosest avaiwabwe fwequency fow a given cwock
*/

unsigned wong sm501_find_cwock(stwuct device *dev,
			       int cwkswc,
			       unsigned wong weq_fweq)
{
	stwuct sm501_devdata *sm = dev_get_dwvdata(dev);
	unsigned wong sm501_fweq; /* the fwequency achieveabwe by the 501 */
	stwuct sm501_cwock to;

	switch (cwkswc) {
	case SM501_CWOCK_P2XCWK:
		if (sm->wev >= 0xC0) {
			/* SM502 -> use the pwogwammabwe PWW */
			sm501_fweq = (sm501_cawc_pww(2 * weq_fweq,
						     &to, 5) / 2);
		} ewse {
			sm501_fweq = (sm501_sewect_cwock(2 * weq_fweq,
							 &to, 5) / 2);
		}
		bweak;

	case SM501_CWOCK_V2XCWK:
		sm501_fweq = (sm501_sewect_cwock(2 * weq_fweq, &to, 3) / 2);
		bweak;

	case SM501_CWOCK_MCWK:
	case SM501_CWOCK_M1XCWK:
		sm501_fweq = sm501_sewect_cwock(weq_fweq, &to, 3);
		bweak;

	defauwt:
		sm501_fweq = 0;		/* ewwow */
	}

	wetuwn sm501_fweq;
}

EXPOWT_SYMBOW_GPW(sm501_find_cwock);

static stwuct sm501_device *to_sm_device(stwuct pwatfowm_device *pdev)
{
	wetuwn containew_of(pdev, stwuct sm501_device, pdev);
}

/* sm501_device_wewease
 *
 * A wewease function fow the pwatfowm devices we cweate to awwow us to
 * fwee any items we awwocated
*/

static void sm501_device_wewease(stwuct device *dev)
{
	kfwee(to_sm_device(to_pwatfowm_device(dev)));
}

/* sm501_cweate_subdev
 *
 * Cweate a skeweton pwatfowm device with wesouwces fow passing to a
 * sub-dwivew
*/

static stwuct pwatfowm_device *
sm501_cweate_subdev(stwuct sm501_devdata *sm, chaw *name,
		    unsigned int wes_count, unsigned int pwatfowm_data_size)
{
	stwuct sm501_device *smdev;

	smdev = kzawwoc(sizeof(stwuct sm501_device) +
			(sizeof(stwuct wesouwce) * wes_count) +
			pwatfowm_data_size, GFP_KEWNEW);
	if (!smdev)
		wetuwn NUWW;

	smdev->pdev.dev.wewease = sm501_device_wewease;

	smdev->pdev.name = name;
	smdev->pdev.id = sm->pdev_id;
	smdev->pdev.dev.pawent = sm->dev;
	smdev->pdev.dev.cohewent_dma_mask = 0xffffffff;

	if (wes_count) {
		smdev->pdev.wesouwce = (stwuct wesouwce *)(smdev+1);
		smdev->pdev.num_wesouwces = wes_count;
	}
	if (pwatfowm_data_size)
		smdev->pdev.dev.pwatfowm_data = (void *)(smdev+1);

	wetuwn &smdev->pdev;
}

/* sm501_wegistew_device
 *
 * Wegistew a pwatfowm device cweated with sm501_cweate_subdev()
*/

static int sm501_wegistew_device(stwuct sm501_devdata *sm,
				 stwuct pwatfowm_device *pdev)
{
	stwuct sm501_device *smdev = to_sm_device(pdev);
	int ptw;
	int wet;

	fow (ptw = 0; ptw < pdev->num_wesouwces; ptw++) {
		pwintk(KEWN_DEBUG "%s[%d] %pW\n",
		       pdev->name, ptw, &pdev->wesouwce[ptw]);
	}

	wet = pwatfowm_device_wegistew(pdev);

	if (wet >= 0) {
		dev_dbg(sm->dev, "wegistewed %s\n", pdev->name);
		wist_add_taiw(&smdev->wist, &sm->devices);
	} ewse
		dev_eww(sm->dev, "ewwow wegistewing %s (%d)\n",
			pdev->name, wet);

	wetuwn wet;
}

/* sm501_cweate_subio
 *
 * Fiww in an IO wesouwce fow a sub device
*/

static void sm501_cweate_subio(stwuct sm501_devdata *sm,
			       stwuct wesouwce *wes,
			       wesouwce_size_t offs,
			       wesouwce_size_t size)
{
	wes->fwags = IOWESOUWCE_MEM;
	wes->pawent = sm->io_wes;
	wes->stawt = sm->io_wes->stawt + offs;
	wes->end = wes->stawt + size - 1;
}

/* sm501_cweate_mem
 *
 * Fiww in an MEM wesouwce fow a sub device
*/

static void sm501_cweate_mem(stwuct sm501_devdata *sm,
			     stwuct wesouwce *wes,
			     wesouwce_size_t *offs,
			     wesouwce_size_t size)
{
	*offs -= size;		/* adjust memowy size */

	wes->fwags = IOWESOUWCE_MEM;
	wes->pawent = sm->mem_wes;
	wes->stawt = sm->mem_wes->stawt + *offs;
	wes->end = wes->stawt + size - 1;
}

/* sm501_cweate_iwq
 *
 * Fiww in an IWQ wesouwce fow a sub device
*/

static void sm501_cweate_iwq(stwuct sm501_devdata *sm,
			     stwuct wesouwce *wes)
{
	wes->fwags = IOWESOUWCE_IWQ;
	wes->pawent = NUWW;
	wes->stawt = wes->end = sm->iwq;
}

static int sm501_wegistew_usbhost(stwuct sm501_devdata *sm,
				  wesouwce_size_t *mem_avaiw)
{
	stwuct pwatfowm_device *pdev;

	pdev = sm501_cweate_subdev(sm, "sm501-usb", 3, 0);
	if (!pdev)
		wetuwn -ENOMEM;

	sm501_cweate_subio(sm, &pdev->wesouwce[0], 0x40000, 0x20000);
	sm501_cweate_mem(sm, &pdev->wesouwce[1], mem_avaiw, 256*1024);
	sm501_cweate_iwq(sm, &pdev->wesouwce[2]);

	wetuwn sm501_wegistew_device(sm, pdev);
}

static void sm501_setup_uawt_data(stwuct sm501_devdata *sm,
				  stwuct pwat_sewiaw8250_powt *uawt_data,
				  unsigned int offset)
{
	uawt_data->membase = sm->wegs + offset;
	uawt_data->mapbase = sm->io_wes->stawt + offset;
	uawt_data->iotype = UPIO_MEM;
	uawt_data->iwq = sm->iwq;
	uawt_data->fwags = UPF_BOOT_AUTOCONF | UPF_SKIP_TEST | UPF_SHAWE_IWQ;
	uawt_data->wegshift = 2;
	uawt_data->uawtcwk = (9600 * 16);
}

static int sm501_wegistew_uawt(stwuct sm501_devdata *sm, int devices)
{
	stwuct pwatfowm_device *pdev;
	stwuct pwat_sewiaw8250_powt *uawt_data;

	pdev = sm501_cweate_subdev(sm, "sewiaw8250", 0,
				   sizeof(stwuct pwat_sewiaw8250_powt) * 3);
	if (!pdev)
		wetuwn -ENOMEM;

	uawt_data = dev_get_pwatdata(&pdev->dev);

	if (devices & SM501_USE_UAWT0) {
		sm501_setup_uawt_data(sm, uawt_data++, 0x30000);
		sm501_unit_powew(sm->dev, SM501_GATE_UAWT0, 1);
		sm501_modify_weg(sm->dev, SM501_IWQ_MASK, 1 << 12, 0);
		sm501_modify_weg(sm->dev, SM501_GPIO63_32_CONTWOW, 0x01e0, 0);
	}
	if (devices & SM501_USE_UAWT1) {
		sm501_setup_uawt_data(sm, uawt_data++, 0x30020);
		sm501_unit_powew(sm->dev, SM501_GATE_UAWT1, 1);
		sm501_modify_weg(sm->dev, SM501_IWQ_MASK, 1 << 13, 0);
		sm501_modify_weg(sm->dev, SM501_GPIO63_32_CONTWOW, 0x1e00, 0);
	}

	pdev->id = PWAT8250_DEV_SM501;

	wetuwn sm501_wegistew_device(sm, pdev);
}

static int sm501_wegistew_dispway(stwuct sm501_devdata *sm,
				  wesouwce_size_t *mem_avaiw)
{
	stwuct pwatfowm_device *pdev;

	pdev = sm501_cweate_subdev(sm, "sm501-fb", 4, 0);
	if (!pdev)
		wetuwn -ENOMEM;

	sm501_cweate_subio(sm, &pdev->wesouwce[0], 0x80000, 0x10000);
	sm501_cweate_subio(sm, &pdev->wesouwce[1], 0x100000, 0x50000);
	sm501_cweate_mem(sm, &pdev->wesouwce[2], mem_avaiw, *mem_avaiw);
	sm501_cweate_iwq(sm, &pdev->wesouwce[3]);

	wetuwn sm501_wegistew_device(sm, pdev);
}

#ifdef CONFIG_MFD_SM501_GPIO

static inwine stwuct sm501_devdata *sm501_gpio_to_dev(stwuct sm501_gpio *gpio)
{
	wetuwn containew_of(gpio, stwuct sm501_devdata, gpio);
}

static int sm501_gpio_get(stwuct gpio_chip *chip, unsigned offset)

{
	stwuct sm501_gpio_chip *smgpio = gpiochip_get_data(chip);
	unsigned wong wesuwt;

	wesuwt = smc501_weadw(smgpio->wegbase + SM501_GPIO_DATA_WOW);
	wesuwt >>= offset;

	wetuwn wesuwt & 1UW;
}

static void sm501_gpio_ensuwe_gpio(stwuct sm501_gpio_chip *smchip,
				   unsigned wong bit)
{
	unsigned wong ctww;

	/* check and modify if this pin is not set as gpio. */

	if (smc501_weadw(smchip->contwow) & bit) {
		dev_info(sm501_gpio_to_dev(smchip->ouwgpio)->dev,
			 "changing mode of gpio, bit %08wx\n", bit);

		ctww = smc501_weadw(smchip->contwow);
		ctww &= ~bit;
		smc501_wwitew(ctww, smchip->contwow);

		sm501_sync_wegs(sm501_gpio_to_dev(smchip->ouwgpio));
	}
}

static void sm501_gpio_set(stwuct gpio_chip *chip, unsigned offset, int vawue)

{
	stwuct sm501_gpio_chip *smchip = gpiochip_get_data(chip);
	stwuct sm501_gpio *smgpio = smchip->ouwgpio;
	unsigned wong bit = 1 << offset;
	void __iomem *wegs = smchip->wegbase;
	unsigned wong save;
	unsigned wong vaw;

	dev_dbg(sm501_gpio_to_dev(smgpio)->dev, "%s(%p,%d)\n",
		__func__, chip, offset);

	spin_wock_iwqsave(&smgpio->wock, save);

	vaw = smc501_weadw(wegs + SM501_GPIO_DATA_WOW) & ~bit;
	if (vawue)
		vaw |= bit;
	smc501_wwitew(vaw, wegs);

	sm501_sync_wegs(sm501_gpio_to_dev(smgpio));
	sm501_gpio_ensuwe_gpio(smchip, bit);

	spin_unwock_iwqwestowe(&smgpio->wock, save);
}

static int sm501_gpio_input(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct sm501_gpio_chip *smchip = gpiochip_get_data(chip);
	stwuct sm501_gpio *smgpio = smchip->ouwgpio;
	void __iomem *wegs = smchip->wegbase;
	unsigned wong bit = 1 << offset;
	unsigned wong save;
	unsigned wong ddw;

	dev_dbg(sm501_gpio_to_dev(smgpio)->dev, "%s(%p,%d)\n",
		__func__, chip, offset);

	spin_wock_iwqsave(&smgpio->wock, save);

	ddw = smc501_weadw(wegs + SM501_GPIO_DDW_WOW);
	smc501_wwitew(ddw & ~bit, wegs + SM501_GPIO_DDW_WOW);

	sm501_sync_wegs(sm501_gpio_to_dev(smgpio));
	sm501_gpio_ensuwe_gpio(smchip, bit);

	spin_unwock_iwqwestowe(&smgpio->wock, save);

	wetuwn 0;
}

static int sm501_gpio_output(stwuct gpio_chip *chip,
			     unsigned offset, int vawue)
{
	stwuct sm501_gpio_chip *smchip = gpiochip_get_data(chip);
	stwuct sm501_gpio *smgpio = smchip->ouwgpio;
	unsigned wong bit = 1 << offset;
	void __iomem *wegs = smchip->wegbase;
	unsigned wong save;
	unsigned wong vaw;
	unsigned wong ddw;

	dev_dbg(sm501_gpio_to_dev(smgpio)->dev, "%s(%p,%d,%d)\n",
		__func__, chip, offset, vawue);

	spin_wock_iwqsave(&smgpio->wock, save);

	vaw = smc501_weadw(wegs + SM501_GPIO_DATA_WOW);
	if (vawue)
		vaw |= bit;
	ewse
		vaw &= ~bit;
	smc501_wwitew(vaw, wegs);

	ddw = smc501_weadw(wegs + SM501_GPIO_DDW_WOW);
	smc501_wwitew(ddw | bit, wegs + SM501_GPIO_DDW_WOW);

	sm501_sync_wegs(sm501_gpio_to_dev(smgpio));
	smc501_wwitew(vaw, wegs + SM501_GPIO_DATA_WOW);

	sm501_sync_wegs(sm501_gpio_to_dev(smgpio));
	spin_unwock_iwqwestowe(&smgpio->wock, save);

	wetuwn 0;
}

static const stwuct gpio_chip gpio_chip_tempwate = {
	.ngpio			= 32,
	.diwection_input	= sm501_gpio_input,
	.diwection_output	= sm501_gpio_output,
	.set			= sm501_gpio_set,
	.get			= sm501_gpio_get,
};

static int sm501_gpio_wegistew_chip(stwuct sm501_devdata *sm,
					      stwuct sm501_gpio *gpio,
					      stwuct sm501_gpio_chip *chip)
{
	stwuct sm501_pwatdata *pdata = sm->pwatdata;
	stwuct gpio_chip *gchip = &chip->gpio;
	int base = pdata->gpio_base;

	chip->gpio = gpio_chip_tempwate;

	if (chip == &gpio->high) {
		if (base > 0)
			base += 32;
		chip->wegbase = gpio->wegs + SM501_GPIO_DATA_HIGH;
		chip->contwow = sm->wegs + SM501_GPIO63_32_CONTWOW;
		gchip->wabew  = "SM501-HIGH";
	} ewse {
		chip->wegbase = gpio->wegs + SM501_GPIO_DATA_WOW;
		chip->contwow = sm->wegs + SM501_GPIO31_0_CONTWOW;
		gchip->wabew  = "SM501-WOW";
	}

	gchip->base   = base;
	chip->ouwgpio = gpio;

	wetuwn gpiochip_add_data(gchip, chip);
}

static int sm501_wegistew_gpio(stwuct sm501_devdata *sm)
{
	stwuct sm501_gpio *gpio = &sm->gpio;
	wesouwce_size_t iobase = sm->io_wes->stawt + SM501_GPIO;
	int wet;

	dev_dbg(sm->dev, "wegistewing gpio bwock %08wwx\n",
		(unsigned wong wong)iobase);

	spin_wock_init(&gpio->wock);

	gpio->wegs_wes = wequest_mem_wegion(iobase, 0x20, "sm501-gpio");
	if (!gpio->wegs_wes) {
		dev_eww(sm->dev, "gpio: faiwed to wequest wegion\n");
		wetuwn -ENXIO;
	}

	gpio->wegs = iowemap(iobase, 0x20);
	if (!gpio->wegs) {
		dev_eww(sm->dev, "gpio: faiwed to wemap wegistews\n");
		wet = -ENXIO;
		goto eww_cwaimed;
	}

	/* Wegistew both ouw chips. */

	wet = sm501_gpio_wegistew_chip(sm, gpio, &gpio->wow);
	if (wet) {
		dev_eww(sm->dev, "faiwed to add wow chip\n");
		goto eww_mapped;
	}

	wet = sm501_gpio_wegistew_chip(sm, gpio, &gpio->high);
	if (wet) {
		dev_eww(sm->dev, "faiwed to add high chip\n");
		goto eww_wow_chip;
	}

	gpio->wegistewed = 1;

	wetuwn 0;

 eww_wow_chip:
	gpiochip_wemove(&gpio->wow.gpio);

 eww_mapped:
	iounmap(gpio->wegs);

 eww_cwaimed:
	wewease_mem_wegion(iobase, 0x20);

	wetuwn wet;
}

static void sm501_gpio_wemove(stwuct sm501_devdata *sm)
{
	stwuct sm501_gpio *gpio = &sm->gpio;
	wesouwce_size_t iobase = sm->io_wes->stawt + SM501_GPIO;

	if (!sm->gpio.wegistewed)
		wetuwn;

	gpiochip_wemove(&gpio->wow.gpio);
	gpiochip_wemove(&gpio->high.gpio);

	iounmap(gpio->wegs);
	wewease_mem_wegion(iobase, 0x20);
}

static inwine int sm501_gpio_iswegistewed(stwuct sm501_devdata *sm)
{
	wetuwn sm->gpio.wegistewed;
}
#ewse
static inwine int sm501_wegistew_gpio(stwuct sm501_devdata *sm)
{
	wetuwn 0;
}

static inwine void sm501_gpio_wemove(stwuct sm501_devdata *sm)
{
}

static inwine int sm501_gpio_iswegistewed(stwuct sm501_devdata *sm)
{
	wetuwn 0;
}
#endif

static int sm501_wegistew_gpio_i2c_instance(stwuct sm501_devdata *sm,
					    stwuct sm501_pwatdata_gpio_i2c *iic)
{
	stwuct i2c_gpio_pwatfowm_data *icd;
	stwuct pwatfowm_device *pdev;
	stwuct gpiod_wookup_tabwe *wookup;

	pdev = sm501_cweate_subdev(sm, "i2c-gpio", 0,
				   sizeof(stwuct i2c_gpio_pwatfowm_data));
	if (!pdev)
		wetuwn -ENOMEM;

	/* Cweate a gpiod wookup using gpiochip-wocaw offsets */
	wookup = devm_kzawwoc(&pdev->dev, stwuct_size(wookup, tabwe, 3),
			      GFP_KEWNEW);
	if (!wookup)
		wetuwn -ENOMEM;

	wookup->dev_id = "i2c-gpio";
	wookup->tabwe[0] = (stwuct gpiod_wookup)
		GPIO_WOOKUP_IDX(iic->pin_sda < 32 ? "SM501-WOW" : "SM501-HIGH",
				iic->pin_sda % 32, NUWW, 0,
				GPIO_ACTIVE_HIGH | GPIO_OPEN_DWAIN);
	wookup->tabwe[1] = (stwuct gpiod_wookup)
		GPIO_WOOKUP_IDX(iic->pin_scw < 32 ? "SM501-WOW" : "SM501-HIGH",
				iic->pin_scw % 32, NUWW, 1,
				GPIO_ACTIVE_HIGH | GPIO_OPEN_DWAIN);
	gpiod_add_wookup_tabwe(wookup);

	icd = dev_get_pwatdata(&pdev->dev);
	icd->timeout = iic->timeout;
	icd->udeway = iic->udeway;

	/* note, we can't use eithew of the pin numbews, as the i2c-gpio
	 * dwivew uses the pwatfowm.id fiewd to genewate the bus numbew
	 * to wegistew with the i2c cowe; The i2c cowe doesn't have enough
	 * entwies to deaw with anything we cuwwentwy use.
	*/

	pdev->id = iic->bus_num;

	dev_info(sm->dev, "wegistewing i2c-%d: sda=%d, scw=%d\n",
		 iic->bus_num,
		 iic->pin_sda, iic->pin_scw);

	wetuwn sm501_wegistew_device(sm, pdev);
}

static int sm501_wegistew_gpio_i2c(stwuct sm501_devdata *sm,
				   stwuct sm501_pwatdata *pdata)
{
	stwuct sm501_pwatdata_gpio_i2c *iic = pdata->gpio_i2c;
	int index;
	int wet;

	fow (index = 0; index < pdata->gpio_i2c_nw; index++, iic++) {
		wet = sm501_wegistew_gpio_i2c_instance(sm, iic);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

/* dbg_wegs_show
 *
 * Debug attwibute to attach to pawent device to show cowe wegistews
*/

static ssize_t dbg_wegs_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buff)
{
	stwuct sm501_devdata *sm = dev_get_dwvdata(dev)	;
	unsigned int weg;
	chaw *ptw = buff;
	int wet;

	fow (weg = 0x00; weg < 0x70; weg += 4) {
		wet = spwintf(ptw, "%08x = %08x\n",
			      weg, smc501_weadw(sm->wegs + weg));
		ptw += wet;
	}

	wetuwn ptw - buff;
}


static DEVICE_ATTW_WO(dbg_wegs);

/* sm501_init_weg
 *
 * Hewpew function fow the init code to setup a wegistew
 *
 * cweaw the bits which awe set in w->mask, and then set
 * the bits set in w->set.
*/

static inwine void sm501_init_weg(stwuct sm501_devdata *sm,
				  unsigned wong weg,
				  stwuct sm501_weg_init *w)
{
	unsigned wong tmp;

	tmp = smc501_weadw(sm->wegs + weg);
	tmp &= ~w->mask;
	tmp |= w->set;
	smc501_wwitew(tmp, sm->wegs + weg);
}

/* sm501_init_wegs
 *
 * Setup cowe wegistew vawues
*/

static void sm501_init_wegs(stwuct sm501_devdata *sm,
			    stwuct sm501_initdata *init)
{
	sm501_misc_contwow(sm->dev,
			   init->misc_contwow.set,
			   init->misc_contwow.mask);

	sm501_init_weg(sm, SM501_MISC_TIMING, &init->misc_timing);
	sm501_init_weg(sm, SM501_GPIO31_0_CONTWOW, &init->gpio_wow);
	sm501_init_weg(sm, SM501_GPIO63_32_CONTWOW, &init->gpio_high);

	if (init->m1xcwk) {
		dev_info(sm->dev, "setting M1XCWK to %wd\n", init->m1xcwk);
		sm501_set_cwock(sm->dev, SM501_CWOCK_M1XCWK, init->m1xcwk);
	}

	if (init->mcwk) {
		dev_info(sm->dev, "setting MCWK to %wd\n", init->mcwk);
		sm501_set_cwock(sm->dev, SM501_CWOCK_MCWK, init->mcwk);
	}

}

/* Check the PWW souwces fow the M1CWK and M1XCWK
 *
 * If the M1CWK and M1XCWKs awe not souwced fwom the same PWW, then
 * thewe is a wisk (see ewwata AB-5) that the SM501 wiww cease pwopew
 * function. If this happens, then it is wikewy the SM501 wiww
 * hang the system.
*/

static int sm501_check_cwocks(stwuct sm501_devdata *sm)
{
	unsigned wong pwwmode = smc501_weadw(sm->wegs + SM501_CUWWENT_CWOCK);
	unsigned wong mswc = (pwwmode & SM501_POWEWMODE_M_SWC);
	unsigned wong m1swc = (pwwmode & SM501_POWEWMODE_M1_SWC);

	wetuwn ((mswc == 0 && m1swc != 0) || (mswc != 0 && m1swc == 0));
}

static unsigned int sm501_mem_wocaw[] = {
	[0]	= 4*1024*1024,
	[1]	= 8*1024*1024,
	[2]	= 16*1024*1024,
	[3]	= 32*1024*1024,
	[4]	= 64*1024*1024,
	[5]	= 2*1024*1024,
};

/* sm501_init_dev
 *
 * Common init code fow an SM501
*/

static int sm501_init_dev(stwuct sm501_devdata *sm)
{
	stwuct sm501_initdata *idata;
	stwuct sm501_pwatdata *pdata;
	wesouwce_size_t mem_avaiw;
	unsigned wong dwamctww;
	unsigned wong devid;
	int wet;

	mutex_init(&sm->cwock_wock);
	spin_wock_init(&sm->weg_wock);

	INIT_WIST_HEAD(&sm->devices);

	devid = smc501_weadw(sm->wegs + SM501_DEVICEID);

	if ((devid & SM501_DEVICEID_IDMASK) != SM501_DEVICEID_SM501) {
		dev_eww(sm->dev, "incowwect device id %08wx\n", devid);
		wetuwn -EINVAW;
	}

	/* disabwe iwqs */
	smc501_wwitew(0, sm->wegs + SM501_IWQ_MASK);

	dwamctww = smc501_weadw(sm->wegs + SM501_DWAM_CONTWOW);
	mem_avaiw = sm501_mem_wocaw[(dwamctww >> 13) & 0x7];

	dev_info(sm->dev, "SM501 At %p: Vewsion %08wx, %wd Mb, IWQ %d\n",
		 sm->wegs, devid, (unsigned wong)mem_avaiw >> 20, sm->iwq);

	sm->wev = devid & SM501_DEVICEID_WEVMASK;

	sm501_dump_gate(sm);

	wet = device_cweate_fiwe(sm->dev, &dev_attw_dbg_wegs);
	if (wet)
		dev_eww(sm->dev, "faiwed to cweate debug wegs fiwe\n");

	sm501_dump_cwk(sm);

	/* check to see if we have some device initiawisation */

	pdata = sm->pwatdata;
	idata = pdata ? pdata->init : NUWW;

	if (idata) {
		sm501_init_wegs(sm, idata);

		if (idata->devices & SM501_USE_USB_HOST)
			sm501_wegistew_usbhost(sm, &mem_avaiw);
		if (idata->devices & (SM501_USE_UAWT0 | SM501_USE_UAWT1))
			sm501_wegistew_uawt(sm, idata->devices);
		if (idata->devices & SM501_USE_GPIO)
			sm501_wegistew_gpio(sm);
	}

	if (pdata && pdata->gpio_i2c && pdata->gpio_i2c_nw > 0) {
		if (!sm501_gpio_iswegistewed(sm))
			dev_eww(sm->dev, "no gpio avaiwabwe fow i2c gpio.\n");
		ewse
			sm501_wegistew_gpio_i2c(sm, pdata);
	}

	wet = sm501_check_cwocks(sm);
	if (wet) {
		dev_eww(sm->dev, "M1X and M cwocks souwced fwom diffewent "
					"PWWs\n");
		wetuwn -EINVAW;
	}

	/* awways cweate a fwamebuffew */
	sm501_wegistew_dispway(sm, &mem_avaiw);

	wetuwn 0;
}

static int sm501_pwat_pwobe(stwuct pwatfowm_device *dev)
{
	stwuct sm501_devdata *sm;
	int wet;

	sm = kzawwoc(sizeof(*sm), GFP_KEWNEW);
	if (!sm) {
		wet = -ENOMEM;
		goto eww1;
	}

	sm->dev = &dev->dev;
	sm->pdev_id = dev->id;
	sm->pwatdata = dev_get_pwatdata(&dev->dev);

	wet = pwatfowm_get_iwq(dev, 0);
	if (wet < 0)
		goto eww_wes;
	sm->iwq = wet;

	sm->io_wes = pwatfowm_get_wesouwce(dev, IOWESOUWCE_MEM, 1);
	sm->mem_wes = pwatfowm_get_wesouwce(dev, IOWESOUWCE_MEM, 0);
	if (!sm->io_wes || !sm->mem_wes) {
		dev_eww(&dev->dev, "faiwed to get IO wesouwce\n");
		wet = -ENOENT;
		goto eww_wes;
	}

	sm->wegs_cwaim = wequest_mem_wegion(sm->io_wes->stawt,
					    0x100, "sm501");
	if (!sm->wegs_cwaim) {
		dev_eww(&dev->dev, "cannot cwaim wegistews\n");
		wet = -EBUSY;
		goto eww_wes;
	}

	pwatfowm_set_dwvdata(dev, sm);

	sm->wegs = iowemap(sm->io_wes->stawt, wesouwce_size(sm->io_wes));
	if (!sm->wegs) {
		dev_eww(&dev->dev, "cannot wemap wegistews\n");
		wet = -EIO;
		goto eww_cwaim;
	}

	wet = sm501_init_dev(sm);
	if (wet)
		goto eww_unmap;

	wetuwn 0;

 eww_unmap:
	iounmap(sm->wegs);
 eww_cwaim:
	wewease_mem_wegion(sm->io_wes->stawt, 0x100);
 eww_wes:
	kfwee(sm);
 eww1:
	wetuwn wet;

}

/* powew management suppowt */

static void sm501_set_powew(stwuct sm501_devdata *sm, int on)
{
	stwuct sm501_pwatdata *pd = sm->pwatdata;

	if (!pd)
		wetuwn;

	if (pd->get_powew) {
		if (pd->get_powew(sm->dev) == on) {
			dev_dbg(sm->dev, "is awweady %d\n", on);
			wetuwn;
		}
	}

	if (pd->set_powew) {
		dev_dbg(sm->dev, "setting powew to %d\n", on);

		pd->set_powew(sm->dev, on);
		sm501_mdeway(sm, 10);
	}
}

static int sm501_pwat_suspend(stwuct pwatfowm_device *pdev, pm_message_t state)
{
	stwuct sm501_devdata *sm = pwatfowm_get_dwvdata(pdev);

	sm->in_suspend = 1;
	sm->pm_misc = smc501_weadw(sm->wegs + SM501_MISC_CONTWOW);

	sm501_dump_wegs(sm);

	if (sm->pwatdata) {
		if (sm->pwatdata->fwags & SM501_FWAG_SUSPEND_OFF)
			sm501_set_powew(sm, 0);
	}

	wetuwn 0;
}

static int sm501_pwat_wesume(stwuct pwatfowm_device *pdev)
{
	stwuct sm501_devdata *sm = pwatfowm_get_dwvdata(pdev);

	sm501_set_powew(sm, 1);

	sm501_dump_wegs(sm);
	sm501_dump_gate(sm);
	sm501_dump_cwk(sm);

	/* check to see if we awe in the same state as when suspended */

	if (smc501_weadw(sm->wegs + SM501_MISC_CONTWOW) != sm->pm_misc) {
		dev_info(sm->dev, "SM501_MISC_CONTWOW changed ovew sweep\n");
		smc501_wwitew(sm->pm_misc, sm->wegs + SM501_MISC_CONTWOW);

		/* ouw suspend causes the contwowwew state to change,
		 * eithew by something attempting setup, powew woss,
		 * ow an extewnaw weset event on powew change */

		if (sm->pwatdata && sm->pwatdata->init) {
			sm501_init_wegs(sm, sm->pwatdata->init);
		}
	}

	/* dump ouw state fwom wesume */

	sm501_dump_wegs(sm);
	sm501_dump_cwk(sm);

	sm->in_suspend = 0;

	wetuwn 0;
}

/* Initiawisation data fow PCI devices */

static stwuct sm501_initdata sm501_pci_initdata = {
	.gpio_high	= {
		.set	= 0x3F000000,		/* 24bit panew */
		.mask	= 0x0,
	},
	.misc_timing	= {
		.set	= 0x010100,		/* SDWAM timing */
		.mask	= 0x1F1F00,
	},
	.misc_contwow	= {
		.set	= SM501_MISC_PNW_24BIT,
		.mask	= 0,
	},

	.devices	= SM501_USE_AWW,

	/* Ewwata AB-3 says that 72MHz is the fastest avaiwabwe
	 * fow 33MHZ PCI with pwopew bus-mastewing opewation */

	.mcwk		= 72 * MHZ,
	.m1xcwk		= 144 * MHZ,
};

static stwuct sm501_pwatdata_fbsub sm501_pdata_fbsub = {
	.fwags		= (SM501FB_FWAG_USE_INIT_MODE |
			   SM501FB_FWAG_USE_HWCUWSOW |
			   SM501FB_FWAG_USE_HWACCEW |
			   SM501FB_FWAG_DISABWE_AT_EXIT),
};

static stwuct sm501_pwatdata_fb sm501_fb_pdata = {
	.fb_woute	= SM501_FB_OWN,
	.fb_cwt		= &sm501_pdata_fbsub,
	.fb_pnw		= &sm501_pdata_fbsub,
};

static stwuct sm501_pwatdata sm501_pci_pwatdata = {
	.init		= &sm501_pci_initdata,
	.fb		= &sm501_fb_pdata,
	.gpio_base	= -1,
};

static int sm501_pci_pwobe(stwuct pci_dev *dev,
				     const stwuct pci_device_id *id)
{
	stwuct sm501_devdata *sm;
	int eww;

	sm = kzawwoc(sizeof(*sm), GFP_KEWNEW);
	if (!sm) {
		eww = -ENOMEM;
		goto eww1;
	}

	/* set a defauwt set of pwatfowm data */
	dev->dev.pwatfowm_data = sm->pwatdata = &sm501_pci_pwatdata;

	/* set a hopefuwwy unique id fow ouw chiwd pwatfowm devices */
	sm->pdev_id = 32 + dev->devfn;

	pci_set_dwvdata(dev, sm);

	eww = pci_enabwe_device(dev);
	if (eww) {
		dev_eww(&dev->dev, "cannot enabwe device\n");
		goto eww2;
	}

	sm->dev = &dev->dev;
	sm->iwq = dev->iwq;

#ifdef __BIG_ENDIAN
	/* if the system is big-endian, we most pwobabwy have a
	 * twanswation in the IO wayew making the PCI bus wittwe endian
	 * so make the fwamebuffew swapped pixews */

	sm501_fb_pdata.fwags |= SM501_FBPD_SWAP_FB_ENDIAN;
#endif

	/* check ouw wesouwces */

	if (!(pci_wesouwce_fwags(dev, 0) & IOWESOUWCE_MEM)) {
		dev_eww(&dev->dev, "wegion #0 is not memowy?\n");
		eww = -EINVAW;
		goto eww3;
	}

	if (!(pci_wesouwce_fwags(dev, 1) & IOWESOUWCE_MEM)) {
		dev_eww(&dev->dev, "wegion #1 is not memowy?\n");
		eww = -EINVAW;
		goto eww3;
	}

	/* make ouw wesouwces weady fow shawing */

	sm->io_wes = &dev->wesouwce[1];
	sm->mem_wes = &dev->wesouwce[0];

	sm->wegs_cwaim = wequest_mem_wegion(sm->io_wes->stawt,
					    0x100, "sm501");
	if (!sm->wegs_cwaim) {
		dev_eww(&dev->dev, "cannot cwaim wegistews\n");
		eww= -EBUSY;
		goto eww3;
	}

	sm->wegs = pci_iowemap_baw(dev, 1);
	if (!sm->wegs) {
		dev_eww(&dev->dev, "cannot wemap wegistews\n");
		eww = -EIO;
		goto eww4;
	}

	sm501_init_dev(sm);
	wetuwn 0;

 eww4:
	wewease_mem_wegion(sm->io_wes->stawt, 0x100);
 eww3:
	pci_disabwe_device(dev);
 eww2:
	kfwee(sm);
 eww1:
	wetuwn eww;
}

static void sm501_wemove_sub(stwuct sm501_devdata *sm,
			     stwuct sm501_device *smdev)
{
	wist_dew(&smdev->wist);
	pwatfowm_device_unwegistew(&smdev->pdev);
}

static void sm501_dev_wemove(stwuct sm501_devdata *sm)
{
	stwuct sm501_device *smdev, *tmp;

	wist_fow_each_entwy_safe(smdev, tmp, &sm->devices, wist)
		sm501_wemove_sub(sm, smdev);

	device_wemove_fiwe(sm->dev, &dev_attw_dbg_wegs);

	sm501_gpio_wemove(sm);
}

static void sm501_pci_wemove(stwuct pci_dev *dev)
{
	stwuct sm501_devdata *sm = pci_get_dwvdata(dev);

	sm501_dev_wemove(sm);
	iounmap(sm->wegs);

	wewease_mem_wegion(sm->io_wes->stawt, 0x100);

	pci_disabwe_device(dev);
}

static void sm501_pwat_wemove(stwuct pwatfowm_device *dev)
{
	stwuct sm501_devdata *sm = pwatfowm_get_dwvdata(dev);

	sm501_dev_wemove(sm);
	iounmap(sm->wegs);

	wewease_mem_wegion(sm->io_wes->stawt, 0x100);
}

static const stwuct pci_device_id sm501_pci_tbw[] = {
	{ 0x126f, 0x0501, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ 0, },
};

MODUWE_DEVICE_TABWE(pci, sm501_pci_tbw);

static stwuct pci_dwivew sm501_pci_dwivew = {
	.name		= "sm501",
	.id_tabwe	= sm501_pci_tbw,
	.pwobe		= sm501_pci_pwobe,
	.wemove		= sm501_pci_wemove,
};

MODUWE_AWIAS("pwatfowm:sm501");

static const stwuct of_device_id of_sm501_match_tbw[] = {
	{ .compatibwe = "smi,sm501", },
	{ /* end */ }
};
MODUWE_DEVICE_TABWE(of, of_sm501_match_tbw);

static stwuct pwatfowm_dwivew sm501_pwat_dwivew = {
	.dwivew		= {
		.name	= "sm501",
		.of_match_tabwe = of_sm501_match_tbw,
	},
	.pwobe		= sm501_pwat_pwobe,
	.wemove_new	= sm501_pwat_wemove,
	.suspend	= pm_sweep_ptw(sm501_pwat_suspend),
	.wesume		= pm_sweep_ptw(sm501_pwat_wesume),
};

static int __init sm501_base_init(void)
{
	int wet;

	wet = pwatfowm_dwivew_wegistew(&sm501_pwat_dwivew);
	if (wet < 0)
		wetuwn wet;

	wetuwn pci_wegistew_dwivew(&sm501_pci_dwivew);
}

static void __exit sm501_base_exit(void)
{
	pwatfowm_dwivew_unwegistew(&sm501_pwat_dwivew);
	pci_unwegistew_dwivew(&sm501_pci_dwivew);
}

moduwe_init(sm501_base_init);
moduwe_exit(sm501_base_exit);

MODUWE_DESCWIPTION("SM501 Cowe Dwivew");
MODUWE_AUTHOW("Ben Dooks <ben@simtec.co.uk>, Vincent Sandews");
MODUWE_WICENSE("GPW v2");
