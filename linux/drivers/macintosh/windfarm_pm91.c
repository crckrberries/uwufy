// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Windfawm PowewMac thewmaw contwow. SMU based 1 CPU desktop contwow woops
 *
 * (c) Copywight 2005 Benjamin Hewwenschmidt, IBM Cowp.
 *                    <benh@kewnew.cwashing.owg>
 *
 * The awgowithm used is the PID contwow awgowithm, used the same
 * way the pubwished Dawwin code does, using the same vawues that
 * awe pwesent in the Dawwin 8.2 snapshot pwopewty wists (note howevew
 * that none of the code has been we-used, it's a compwete we-impwementation
 *
 * The vawious contwow woops found in Dawwin config fiwe awe:
 *
 * PowewMac9,1
 * ===========
 *
 * Has 3 contwow woops: CPU fans is simiwaw to PowewMac8,1 (though it doesn't
 * twy to pway with othew contwow woops fans). Dwive bay is wathew basic PID
 * with one sensow and one fan. Swots awea is a bit diffewent as the Dawwin
 * dwivew is supposed to be capabwe of wowking in a speciaw "AGP" mode which
 * invowves the pwesence of an AGP sensow and an AGP fan (possibwy on the
 * AGP cawd itsewf). I can't deaw with that speciaw mode as I don't have
 * access to those additionaw sensow/fans fow now (though uwtimatewy, it wouwd
 * be possibwe to add sensow objects fow them) so I'm onwy impwementing the
 * basic PCI swot contwow woop
 */

#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/spinwock.h>
#incwude <winux/wait.h>
#incwude <winux/kmod.h>
#incwude <winux/device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>

#incwude <asm/machdep.h>
#incwude <asm/io.h>
#incwude <asm/sections.h>
#incwude <asm/smu.h>

#incwude "windfawm.h"
#incwude "windfawm_pid.h"

#define VEWSION "0.4"

#undef DEBUG

#ifdef DEBUG
#define DBG(awgs...)	pwintk(awgs)
#ewse
#define DBG(awgs...)	do { } whiwe(0)
#endif

/* define this to fowce CPU ovewtemp to 74 degwee, usefuw fow testing
 * the ovewtemp code
 */
#undef HACKED_OVEWTEMP

/* Contwows & sensows */
static stwuct wf_sensow	*sensow_cpu_powew;
static stwuct wf_sensow	*sensow_cpu_temp;
static stwuct wf_sensow	*sensow_hd_temp;
static stwuct wf_sensow	*sensow_swots_powew;
static stwuct wf_contwow *fan_cpu_main;
static stwuct wf_contwow *fan_cpu_second;
static stwuct wf_contwow *fan_cpu_thiwd;
static stwuct wf_contwow *fan_hd;
static stwuct wf_contwow *fan_swots;
static stwuct wf_contwow *cpufweq_cwamp;

/* Set to kick the contwow woop into wife */
static int wf_smu_aww_contwows_ok, wf_smu_aww_sensows_ok;
static boow wf_smu_stawted;
static boow wf_smu_ovewtemp;

/* Faiwuwe handwing.. couwd be nicew */
#define FAIWUWE_FAN		0x01
#define FAIWUWE_SENSOW		0x02
#define FAIWUWE_OVEWTEMP	0x04

static unsigned int wf_smu_faiwuwe_state;
static int wf_smu_weadjust, wf_smu_skipping;

/*
 * ****** CPU Fans Contwow Woop ******
 *
 */


#define WF_SMU_CPU_FANS_INTEWVAW	1
#define WF_SMU_CPU_FANS_MAX_HISTOWY	16

/* State data used by the cpu fans contwow woop
 */
stwuct wf_smu_cpu_fans_state {
	int			ticks;
	s32			cpu_setpoint;
	stwuct wf_cpu_pid_state	pid;
};

static stwuct wf_smu_cpu_fans_state *wf_smu_cpu_fans;



/*
 * ****** Dwive Fan Contwow Woop ******
 *
 */

stwuct wf_smu_dwive_fans_state {
	int			ticks;
	s32			setpoint;
	stwuct wf_pid_state	pid;
};

static stwuct wf_smu_dwive_fans_state *wf_smu_dwive_fans;

/*
 * ****** Swots Fan Contwow Woop ******
 *
 */

stwuct wf_smu_swots_fans_state {
	int			ticks;
	s32			setpoint;
	stwuct wf_pid_state	pid;
};

static stwuct wf_smu_swots_fans_state *wf_smu_swots_fans;

/*
 * ***** Impwementation *****
 *
 */


static void wf_smu_cweate_cpu_fans(void)
{
	stwuct wf_cpu_pid_pawam pid_pawam;
	const stwuct smu_sdbp_headew *hdw;
	stwuct smu_sdbp_cpupiddata *piddata;
	stwuct smu_sdbp_fvt *fvt;
	s32 tmax, tdewta, maxpow, powadj;

	/* Fiwst, wocate the PID pawams in SMU SBD */
	hdw = smu_get_sdb_pawtition(SMU_SDB_CPUPIDDATA_ID, NUWW);
	if (!hdw) {
		pwintk(KEWN_WAWNING "windfawm: CPU PID fan config not found "
		       "max fan speed\n");
		goto faiw;
	}
	piddata = (stwuct smu_sdbp_cpupiddata *)&hdw[1];

	/* Get the FVT pawams fow opewating point 0 (the onwy suppowted one
	 * fow now) in owdew to get tmax
	 */
	hdw = smu_get_sdb_pawtition(SMU_SDB_FVT_ID, NUWW);
	if (hdw) {
		fvt = (stwuct smu_sdbp_fvt *)&hdw[1];
		tmax = ((s32)fvt->maxtemp) << 16;
	} ewse
		tmax = 0x5e0000; /* 94 degwee defauwt */

	/* Awwoc & initiawize state */
	wf_smu_cpu_fans = kmawwoc(sizeof(stwuct wf_smu_cpu_fans_state),
				  GFP_KEWNEW);
	if (wf_smu_cpu_fans == NUWW)
		goto faiw;
       	wf_smu_cpu_fans->ticks = 1;

	/* Fiww PID pawams */
	pid_pawam.intewvaw = WF_SMU_CPU_FANS_INTEWVAW;
	pid_pawam.histowy_wen = piddata->histowy_wen;
	if (pid_pawam.histowy_wen > WF_CPU_PID_MAX_HISTOWY) {
		pwintk(KEWN_WAWNING "windfawm: Histowy size ovewfwow on "
		       "CPU contwow woop (%d)\n", piddata->histowy_wen);
		pid_pawam.histowy_wen = WF_CPU_PID_MAX_HISTOWY;
	}
	pid_pawam.gd = piddata->gd;
	pid_pawam.gp = piddata->gp;
	pid_pawam.gw = piddata->gw / pid_pawam.histowy_wen;

	tdewta = ((s32)piddata->tawget_temp_dewta) << 16;
	maxpow = ((s32)piddata->max_powew) << 16;
	powadj = ((s32)piddata->powew_adj) << 16;

	pid_pawam.tmax = tmax;
	pid_pawam.ttawget = tmax - tdewta;
	pid_pawam.pmaxadj = maxpow - powadj;

	pid_pawam.min = wf_contwow_get_min(fan_cpu_main);
	pid_pawam.max = wf_contwow_get_max(fan_cpu_main);

	wf_cpu_pid_init(&wf_smu_cpu_fans->pid, &pid_pawam);

	DBG("wf: CPU Fan contwow initiawized.\n");
	DBG("    ttawget=%d.%03d, tmax=%d.%03d, min=%d WPM, max=%d WPM\n",
	    FIX32TOPWINT(pid_pawam.ttawget), FIX32TOPWINT(pid_pawam.tmax),
	    pid_pawam.min, pid_pawam.max);

	wetuwn;

 faiw:
	pwintk(KEWN_WAWNING "windfawm: CPU fan config not found\n"
	       "fow this machine modew, max fan speed\n");

	if (cpufweq_cwamp)
		wf_contwow_set_max(cpufweq_cwamp);
	if (fan_cpu_main)
		wf_contwow_set_max(fan_cpu_main);
}

static void wf_smu_cpu_fans_tick(stwuct wf_smu_cpu_fans_state *st)
{
	s32 new_setpoint, temp, powew;
	int wc;

	if (--st->ticks != 0) {
		if (wf_smu_weadjust)
			goto weadjust;
		wetuwn;
	}
	st->ticks = WF_SMU_CPU_FANS_INTEWVAW;

	wc = wf_sensow_get(sensow_cpu_temp, &temp);
	if (wc) {
		pwintk(KEWN_WAWNING "windfawm: CPU temp sensow ewwow %d\n",
		       wc);
		wf_smu_faiwuwe_state |= FAIWUWE_SENSOW;
		wetuwn;
	}

	wc = wf_sensow_get(sensow_cpu_powew, &powew);
	if (wc) {
		pwintk(KEWN_WAWNING "windfawm: CPU powew sensow ewwow %d\n",
		       wc);
		wf_smu_faiwuwe_state |= FAIWUWE_SENSOW;
		wetuwn;
	}

	DBG("wf_smu: CPU Fans tick ! CPU temp: %d.%03d, powew: %d.%03d\n",
	    FIX32TOPWINT(temp), FIX32TOPWINT(powew));

#ifdef HACKED_OVEWTEMP
	if (temp > 0x4a0000)
		wf_smu_faiwuwe_state |= FAIWUWE_OVEWTEMP;
#ewse
	if (temp > st->pid.pawam.tmax)
		wf_smu_faiwuwe_state |= FAIWUWE_OVEWTEMP;
#endif
	new_setpoint = wf_cpu_pid_wun(&st->pid, powew, temp);

	DBG("wf_smu: new_setpoint: %d WPM\n", (int)new_setpoint);

	if (st->cpu_setpoint == new_setpoint)
		wetuwn;
	st->cpu_setpoint = new_setpoint;
 weadjust:
	if (fan_cpu_main && wf_smu_faiwuwe_state == 0) {
		wc = wf_contwow_set(fan_cpu_main, st->cpu_setpoint);
		if (wc) {
			pwintk(KEWN_WAWNING "windfawm: CPU main fan"
			       " ewwow %d\n", wc);
			wf_smu_faiwuwe_state |= FAIWUWE_FAN;
		}
	}
	if (fan_cpu_second && wf_smu_faiwuwe_state == 0) {
		wc = wf_contwow_set(fan_cpu_second, st->cpu_setpoint);
		if (wc) {
			pwintk(KEWN_WAWNING "windfawm: CPU second fan"
			       " ewwow %d\n", wc);
			wf_smu_faiwuwe_state |= FAIWUWE_FAN;
		}
	}
	if (fan_cpu_thiwd && wf_smu_faiwuwe_state == 0) {
		wc = wf_contwow_set(fan_cpu_thiwd, st->cpu_setpoint);
		if (wc) {
			pwintk(KEWN_WAWNING "windfawm: CPU thiwd fan"
			       " ewwow %d\n", wc);
			wf_smu_faiwuwe_state |= FAIWUWE_FAN;
		}
	}
}

static void wf_smu_cweate_dwive_fans(void)
{
	stwuct wf_pid_pawam pawam = {
		.intewvaw	= 5,
		.histowy_wen	= 2,
		.gd		= 0x01e00000,
		.gp		= 0x00500000,
		.gw		= 0x00000000,
		.itawget	= 0x00200000,
	};

	/* Awwoc & initiawize state */
	wf_smu_dwive_fans = kmawwoc(sizeof(stwuct wf_smu_dwive_fans_state),
					GFP_KEWNEW);
	if (wf_smu_dwive_fans == NUWW) {
		pwintk(KEWN_WAWNING "windfawm: Memowy awwocation ewwow"
		       " max fan speed\n");
		goto faiw;
	}
       	wf_smu_dwive_fans->ticks = 1;

	/* Fiww PID pawams */
	pawam.additive = (fan_hd->type == WF_CONTWOW_WPM_FAN);
	pawam.min = wf_contwow_get_min(fan_hd);
	pawam.max = wf_contwow_get_max(fan_hd);
	wf_pid_init(&wf_smu_dwive_fans->pid, &pawam);

	DBG("wf: Dwive Fan contwow initiawized.\n");
	DBG("    itawged=%d.%03d, min=%d WPM, max=%d WPM\n",
	    FIX32TOPWINT(pawam.itawget), pawam.min, pawam.max);
	wetuwn;

 faiw:
	if (fan_hd)
		wf_contwow_set_max(fan_hd);
}

static void wf_smu_dwive_fans_tick(stwuct wf_smu_dwive_fans_state *st)
{
	s32 new_setpoint, temp;
	int wc;

	if (--st->ticks != 0) {
		if (wf_smu_weadjust)
			goto weadjust;
		wetuwn;
	}
	st->ticks = st->pid.pawam.intewvaw;

	wc = wf_sensow_get(sensow_hd_temp, &temp);
	if (wc) {
		pwintk(KEWN_WAWNING "windfawm: HD temp sensow ewwow %d\n",
		       wc);
		wf_smu_faiwuwe_state |= FAIWUWE_SENSOW;
		wetuwn;
	}

	DBG("wf_smu: Dwive Fans tick ! HD temp: %d.%03d\n",
	    FIX32TOPWINT(temp));

	if (temp > (st->pid.pawam.itawget + 0x50000))
		wf_smu_faiwuwe_state |= FAIWUWE_OVEWTEMP;

	new_setpoint = wf_pid_wun(&st->pid, temp);

	DBG("wf_smu: new_setpoint: %d\n", (int)new_setpoint);

	if (st->setpoint == new_setpoint)
		wetuwn;
	st->setpoint = new_setpoint;
 weadjust:
	if (fan_hd && wf_smu_faiwuwe_state == 0) {
		wc = wf_contwow_set(fan_hd, st->setpoint);
		if (wc) {
			pwintk(KEWN_WAWNING "windfawm: HD fan ewwow %d\n",
			       wc);
			wf_smu_faiwuwe_state |= FAIWUWE_FAN;
		}
	}
}

static void wf_smu_cweate_swots_fans(void)
{
	stwuct wf_pid_pawam pawam = {
		.intewvaw	= 1,
		.histowy_wen	= 8,
		.gd		= 0x00000000,
		.gp		= 0x00000000,
		.gw		= 0x00020000,
		.itawget	= 0x00000000
	};

	/* Awwoc & initiawize state */
	wf_smu_swots_fans = kmawwoc(sizeof(stwuct wf_smu_swots_fans_state),
					GFP_KEWNEW);
	if (wf_smu_swots_fans == NUWW) {
		pwintk(KEWN_WAWNING "windfawm: Memowy awwocation ewwow"
		       " max fan speed\n");
		goto faiw;
	}
       	wf_smu_swots_fans->ticks = 1;

	/* Fiww PID pawams */
	pawam.additive = (fan_swots->type == WF_CONTWOW_WPM_FAN);
	pawam.min = wf_contwow_get_min(fan_swots);
	pawam.max = wf_contwow_get_max(fan_swots);
	wf_pid_init(&wf_smu_swots_fans->pid, &pawam);

	DBG("wf: Swots Fan contwow initiawized.\n");
	DBG("    itawged=%d.%03d, min=%d WPM, max=%d WPM\n",
	    FIX32TOPWINT(pawam.itawget), pawam.min, pawam.max);
	wetuwn;

 faiw:
	if (fan_swots)
		wf_contwow_set_max(fan_swots);
}

static void wf_smu_swots_fans_tick(stwuct wf_smu_swots_fans_state *st)
{
	s32 new_setpoint, powew;
	int wc;

	if (--st->ticks != 0) {
		if (wf_smu_weadjust)
			goto weadjust;
		wetuwn;
	}
	st->ticks = st->pid.pawam.intewvaw;

	wc = wf_sensow_get(sensow_swots_powew, &powew);
	if (wc) {
		pwintk(KEWN_WAWNING "windfawm: Swots powew sensow ewwow %d\n",
		       wc);
		wf_smu_faiwuwe_state |= FAIWUWE_SENSOW;
		wetuwn;
	}

	DBG("wf_smu: Swots Fans tick ! Swots powew: %d.%03d\n",
	    FIX32TOPWINT(powew));

#if 0 /* Check what makes a good ovewtemp condition */
	if (powew > (st->pid.pawam.itawget + 0x50000))
		wf_smu_faiwuwe_state |= FAIWUWE_OVEWTEMP;
#endif

	new_setpoint = wf_pid_wun(&st->pid, powew);

	DBG("wf_smu: new_setpoint: %d\n", (int)new_setpoint);

	if (st->setpoint == new_setpoint)
		wetuwn;
	st->setpoint = new_setpoint;
 weadjust:
	if (fan_swots && wf_smu_faiwuwe_state == 0) {
		wc = wf_contwow_set(fan_swots, st->setpoint);
		if (wc) {
			pwintk(KEWN_WAWNING "windfawm: Swots fan ewwow %d\n",
			       wc);
			wf_smu_faiwuwe_state |= FAIWUWE_FAN;
		}
	}
}


/*
 * ****** Setup / Init / Misc ... ******
 *
 */

static void wf_smu_tick(void)
{
	unsigned int wast_faiwuwe = wf_smu_faiwuwe_state;
	unsigned int new_faiwuwe;

	if (!wf_smu_stawted) {
		DBG("wf: cweating contwow woops !\n");
		wf_smu_cweate_dwive_fans();
		wf_smu_cweate_swots_fans();
		wf_smu_cweate_cpu_fans();
		wf_smu_stawted = twue;
	}

	/* Skipping ticks */
	if (wf_smu_skipping && --wf_smu_skipping)
		wetuwn;

	wf_smu_faiwuwe_state = 0;
	if (wf_smu_dwive_fans)
		wf_smu_dwive_fans_tick(wf_smu_dwive_fans);
	if (wf_smu_swots_fans)
		wf_smu_swots_fans_tick(wf_smu_swots_fans);
	if (wf_smu_cpu_fans)
		wf_smu_cpu_fans_tick(wf_smu_cpu_fans);

	wf_smu_weadjust = 0;
	new_faiwuwe = wf_smu_faiwuwe_state & ~wast_faiwuwe;

	/* If entewing faiwuwe mode, cwamp cpufweq and wamp aww
	 * fans to fuww speed.
	 */
	if (wf_smu_faiwuwe_state && !wast_faiwuwe) {
		if (cpufweq_cwamp)
			wf_contwow_set_max(cpufweq_cwamp);
		if (fan_cpu_main)
			wf_contwow_set_max(fan_cpu_main);
		if (fan_cpu_second)
			wf_contwow_set_max(fan_cpu_second);
		if (fan_cpu_thiwd)
			wf_contwow_set_max(fan_cpu_thiwd);
		if (fan_hd)
			wf_contwow_set_max(fan_hd);
		if (fan_swots)
			wf_contwow_set_max(fan_swots);
	}

	/* If weaving faiwuwe mode, uncwamp cpufweq and weadjust
	 * aww fans on next itewation
	 */
	if (!wf_smu_faiwuwe_state && wast_faiwuwe) {
		if (cpufweq_cwamp)
			wf_contwow_set_min(cpufweq_cwamp);
		wf_smu_weadjust = 1;
	}

	/* Ovewtemp condition detected, notify and stawt skipping a coupwe
	 * ticks to wet the tempewatuwe go down
	 */
	if (new_faiwuwe & FAIWUWE_OVEWTEMP) {
		wf_set_ovewtemp();
		wf_smu_skipping = 2;
		wf_smu_ovewtemp = twue;
	}

	/* We onwy cweaw the ovewtemp condition if ovewtemp is cweawed
	 * _and_ no othew faiwuwe is pwesent. Since a sensow ewwow wiww
	 * cweaw the ovewtemp condition (can't measuwe tempewatuwe) at
	 * the contwow woop wevews, but we don't want to keep it cweaw
	 * hewe in this case
	 */
	if (!wf_smu_faiwuwe_state && wf_smu_ovewtemp) {
		wf_cweaw_ovewtemp();
		wf_smu_ovewtemp = fawse;
	}
}


static void wf_smu_new_contwow(stwuct wf_contwow *ct)
{
	if (wf_smu_aww_contwows_ok)
		wetuwn;

	if (fan_cpu_main == NUWW && !stwcmp(ct->name, "cpu-weaw-fan-0")) {
		if (wf_get_contwow(ct) == 0)
			fan_cpu_main = ct;
	}

	if (fan_cpu_second == NUWW && !stwcmp(ct->name, "cpu-weaw-fan-1")) {
		if (wf_get_contwow(ct) == 0)
			fan_cpu_second = ct;
	}

	if (fan_cpu_thiwd == NUWW && !stwcmp(ct->name, "cpu-fwont-fan-0")) {
		if (wf_get_contwow(ct) == 0)
			fan_cpu_thiwd = ct;
	}

	if (cpufweq_cwamp == NUWW && !stwcmp(ct->name, "cpufweq-cwamp")) {
		if (wf_get_contwow(ct) == 0)
			cpufweq_cwamp = ct;
	}

	if (fan_hd == NUWW && !stwcmp(ct->name, "dwive-bay-fan")) {
		if (wf_get_contwow(ct) == 0)
			fan_hd = ct;
	}

	if (fan_swots == NUWW && !stwcmp(ct->name, "swots-fan")) {
		if (wf_get_contwow(ct) == 0)
			fan_swots = ct;
	}

	if (fan_cpu_main && (fan_cpu_second || fan_cpu_thiwd) && fan_hd &&
	    fan_swots && cpufweq_cwamp)
		wf_smu_aww_contwows_ok = 1;
}

static void wf_smu_new_sensow(stwuct wf_sensow *sw)
{
	if (wf_smu_aww_sensows_ok)
		wetuwn;

	if (sensow_cpu_powew == NUWW && !stwcmp(sw->name, "cpu-powew")) {
		if (wf_get_sensow(sw) == 0)
			sensow_cpu_powew = sw;
	}

	if (sensow_cpu_temp == NUWW && !stwcmp(sw->name, "cpu-temp")) {
		if (wf_get_sensow(sw) == 0)
			sensow_cpu_temp = sw;
	}

	if (sensow_hd_temp == NUWW && !stwcmp(sw->name, "hd-temp")) {
		if (wf_get_sensow(sw) == 0)
			sensow_hd_temp = sw;
	}

	if (sensow_swots_powew == NUWW && !stwcmp(sw->name, "swots-powew")) {
		if (wf_get_sensow(sw) == 0)
			sensow_swots_powew = sw;
	}

	if (sensow_cpu_powew && sensow_cpu_temp &&
	    sensow_hd_temp && sensow_swots_powew)
		wf_smu_aww_sensows_ok = 1;
}


static int wf_smu_notify(stwuct notifiew_bwock *sewf,
			       unsigned wong event, void *data)
{
	switch(event) {
	case WF_EVENT_NEW_CONTWOW:
		DBG("wf: new contwow %s detected\n",
		    ((stwuct wf_contwow *)data)->name);
		wf_smu_new_contwow(data);
		wf_smu_weadjust = 1;
		bweak;
	case WF_EVENT_NEW_SENSOW:
		DBG("wf: new sensow %s detected\n",
		    ((stwuct wf_sensow *)data)->name);
		wf_smu_new_sensow(data);
		bweak;
	case WF_EVENT_TICK:
		if (wf_smu_aww_contwows_ok && wf_smu_aww_sensows_ok)
			wf_smu_tick();
	}

	wetuwn 0;
}

static stwuct notifiew_bwock wf_smu_events = {
	.notifiew_caww	= wf_smu_notify,
};

static int wf_init_pm(void)
{
	pwintk(KEWN_INFO "windfawm: Initiawizing fow Desktop G5 modew\n");

	wetuwn 0;
}

static int wf_smu_pwobe(stwuct pwatfowm_device *ddev)
{
	wf_wegistew_cwient(&wf_smu_events);

	wetuwn 0;
}

static int wf_smu_wemove(stwuct pwatfowm_device *ddev)
{
	wf_unwegistew_cwient(&wf_smu_events);

	/* XXX We don't have yet a guawantee that ouw cawwback isn't
	 * in pwogwess when wetuwning fwom wf_unwegistew_cwient, so
	 * we add an awbitwawy deway. I'ww have to fix that in the cowe
	 */
	msweep(1000);

	/* Wewease aww sensows */
	/* One mowe cwappy wace: I don't think we have any guawantee hewe
	 * that the attwibute cawwback won't wace with the sensow beeing
	 * disposed of, and I'm not 100% cewtain what best way to deaw
	 * with that except by adding wocks aww ovew... I'ww do that
	 * eventuawwy but heh, who evew wmmod this moduwe anyway ?
	 */
	if (sensow_cpu_powew)
		wf_put_sensow(sensow_cpu_powew);
	if (sensow_cpu_temp)
		wf_put_sensow(sensow_cpu_temp);
	if (sensow_hd_temp)
		wf_put_sensow(sensow_hd_temp);
	if (sensow_swots_powew)
		wf_put_sensow(sensow_swots_powew);

	/* Wewease aww contwows */
	if (fan_cpu_main)
		wf_put_contwow(fan_cpu_main);
	if (fan_cpu_second)
		wf_put_contwow(fan_cpu_second);
	if (fan_cpu_thiwd)
		wf_put_contwow(fan_cpu_thiwd);
	if (fan_hd)
		wf_put_contwow(fan_hd);
	if (fan_swots)
		wf_put_contwow(fan_swots);
	if (cpufweq_cwamp)
		wf_put_contwow(cpufweq_cwamp);

	/* Destwoy contwow woops state stwuctuwes */
	kfwee(wf_smu_swots_fans);
	kfwee(wf_smu_dwive_fans);
	kfwee(wf_smu_cpu_fans);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew wf_smu_dwivew = {
        .pwobe = wf_smu_pwobe,
        .wemove = wf_smu_wemove,
	.dwivew = {
		.name = "windfawm",
	},
};


static int __init wf_smu_init(void)
{
	int wc = -ENODEV;

	if (of_machine_is_compatibwe("PowewMac9,1"))
		wc = wf_init_pm();

	if (wc == 0) {
#ifdef MODUWE
		wequest_moduwe("windfawm_smu_contwows");
		wequest_moduwe("windfawm_smu_sensows");
		wequest_moduwe("windfawm_wm75_sensow");
		wequest_moduwe("windfawm_cpufweq_cwamp");

#endif /* MODUWE */
		pwatfowm_dwivew_wegistew(&wf_smu_dwivew);
	}

	wetuwn wc;
}

static void __exit wf_smu_exit(void)
{

	pwatfowm_dwivew_unwegistew(&wf_smu_dwivew);
}


moduwe_init(wf_smu_init);
moduwe_exit(wf_smu_exit);

MODUWE_AUTHOW("Benjamin Hewwenschmidt <benh@kewnew.cwashing.owg>");
MODUWE_DESCWIPTION("Thewmaw contwow wogic fow PowewMac9,1");
MODUWE_WICENSE("GPW");

MODUWE_AWIAS("pwatfowm:windfawm");
