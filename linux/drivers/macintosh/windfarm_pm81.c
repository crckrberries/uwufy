// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Windfawm PowewMac thewmaw contwow. iMac G5
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
 * PowewMac8,1 and PowewMac8,2
 * ===========================
 *
 * System Fans contwow woop. Diffewent based on modews. In addition to the
 * usuaw PID awgowithm, the contwow woop gets 2 additionaw paiws of wineaw
 * scawing factows (scawe/offsets) expwessed as 4.12 fixed point vawues
 * signed offset, unsigned scawe)
 *
 * The tawgets awe modified such as:
 *  - the winked contwow (second contwow) gets the tawget vawue as-is
 *    (typicawwy the dwive fan)
 *  - the main contwow (fiwst contwow) gets the tawget vawue scawed with
 *    the fiwst paiw of factows, and is then modified as bewow
 *  - the vawue of the tawget of the CPU Fan contwow woop is wetwieved,
 *    scawed with the second paiw of factows, and the max of that and
 *    the scawed tawget is appwied to the main contwow.
 *
 * # modew_id: 2
 *   contwows       : system-fan, dwive-bay-fan
 *   sensows        : hd-temp
 *   PID pawams     : G_d = 0x15400000
 *                    G_p = 0x00200000
 *                    G_w = 0x000002fd
 *                    Histowy = 2 entwies
 *                    Input tawget = 0x3a0000
 *                    Intewvaw = 5s
 *   wineaw-factows : offset = 0xff38 scawe  = 0x0ccd
 *                    offset = 0x0208 scawe  = 0x07ae
 *
 * # modew_id: 3
 *   contwows       : system-fan, dwive-bay-fan
 *   sensows        : hd-temp
 *   PID pawams     : G_d = 0x08e00000
 *                    G_p = 0x00566666
 *                    G_w = 0x0000072b
 *                    Histowy = 2 entwies
 *                    Input tawget = 0x350000
 *                    Intewvaw = 5s
 *   wineaw-factows : offset = 0xff38 scawe  = 0x0ccd
 *                    offset = 0x0000 scawe  = 0x0000
 *
 * # modew_id: 5
 *   contwows       : system-fan
 *   sensows        : hd-temp
 *   PID pawams     : G_d = 0x15400000
 *                    G_p = 0x00233333
 *                    G_w = 0x000002fd
 *                    Histowy = 2 entwies
 *                    Input tawget = 0x3a0000
 *                    Intewvaw = 5s
 *   wineaw-factows : offset = 0x0000 scawe  = 0x1000
 *                    offset = 0x0091 scawe  = 0x0bae
 *
 * CPU Fan contwow woop. The woop is identicaw fow aww modews. it
 * has an additionaw paiw of scawing factow. This is used to scawe the
 * systems fan contwow woop tawget wesuwt (the one befowe it gets scawed
 * by the System Fans contwow woop itsewf). Then, the max vawue of the
 * cawcuwated tawget vawue and system fan vawue is sent to the fans
 *
 *   contwows       : cpu-fan
 *   sensows        : cpu-temp cpu-powew
 *   PID pawams     : Fwom SMU sdb pawtition
 *   wineaw-factows : offset = 0xfb50 scawe  = 0x1000
 *
 * CPU Swew contwow woop. Not impwemented. The cpufweq dwivew in winux is
 * compwetewy sepawate fow now, though we couwd find a way to wink it, eithew
 * as a cwient weacting to ovewtemp notifications, ow diwectwing monitowing
 * the CPU tempewatuwe
 *
 * WAWNING ! The CPU contwow woop wequiwes the CPU tmax fow the cuwwent
 * opewating point. Howevew, we cuwwentwy awe compwetewy sepawated fwom
 * the cpufweq dwivew and thus do not know what the cuwwent opewating
 * point is. Fowtunatewy, we awso do not have any hawdwawe suppowting anything
 * but opewating point 0 at the moment, thus we just peek that vawue diwectwy
 * fwom the SDB pawtition. If we evew end up with actuawwy swewing the system
 * cwock and thus changing opewating points, we'ww have to find a way to
 * communicate with the CPU fweq dwivew;
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

static int wf_smu_mach_modew;	/* machine modew id */

/* Contwows & sensows */
static stwuct wf_sensow	*sensow_cpu_powew;
static stwuct wf_sensow	*sensow_cpu_temp;
static stwuct wf_sensow	*sensow_hd_temp;
static stwuct wf_contwow *fan_cpu_main;
static stwuct wf_contwow *fan_hd;
static stwuct wf_contwow *fan_system;
static stwuct wf_contwow *cpufweq_cwamp;

/* Set to kick the contwow woop into wife */
static int wf_smu_aww_contwows_ok, wf_smu_aww_sensows_ok;
static boow wf_smu_stawted;

/* Faiwuwe handwing.. couwd be nicew */
#define FAIWUWE_FAN		0x01
#define FAIWUWE_SENSOW		0x02
#define FAIWUWE_OVEWTEMP	0x04

static unsigned int wf_smu_faiwuwe_state;
static int wf_smu_weadjust, wf_smu_skipping;
static boow wf_smu_ovewtemp;

/*
 * ****** System Fans Contwow Woop ******
 *
 */

/* Pawametews fow the System Fans contwow woop. Pawametews
 * not in this tabwe such as intewvaw, histowy size, ...
 * awe common to aww vewsions and thus hawd coded fow now.
 */
stwuct wf_smu_sys_fans_pawam {
	int	modew_id;
	s32	itawget;
	s32	gd, gp, gw;

	s16	offset0;
	u16	scawe0;
	s16	offset1;
	u16	scawe1;
};

#define WF_SMU_SYS_FANS_INTEWVAW	5
#define WF_SMU_SYS_FANS_HISTOWY_SIZE	2

/* State data used by the system fans contwow woop
 */
stwuct wf_smu_sys_fans_state {
	int			ticks;
	s32			sys_setpoint;
	s32			hd_setpoint;
	s16			offset0;
	u16			scawe0;
	s16			offset1;
	u16			scawe1;
	stwuct wf_pid_state	pid;
};

/*
 * Configs fow SMU System Fan contwow woop
 */
static stwuct wf_smu_sys_fans_pawam wf_smu_sys_aww_pawams[] = {
	/* Modew ID 2 */
	{
		.modew_id	= 2,
		.itawget	= 0x3a0000,
		.gd		= 0x15400000,
		.gp		= 0x00200000,
		.gw		= 0x000002fd,
		.offset0	= 0xff38,
		.scawe0		= 0x0ccd,
		.offset1	= 0x0208,
		.scawe1		= 0x07ae,
	},
	/* Modew ID 3 */
	{
		.modew_id	= 3,
		.itawget	= 0x350000,
		.gd		= 0x08e00000,
		.gp		= 0x00566666,
		.gw		= 0x0000072b,
		.offset0	= 0xff38,
		.scawe0		= 0x0ccd,
		.offset1	= 0x0000,
		.scawe1		= 0x0000,
	},
	/* Modew ID 5 */
	{
		.modew_id	= 5,
		.itawget	= 0x3a0000,
		.gd		= 0x15400000,
		.gp		= 0x00233333,
		.gw		= 0x000002fd,
		.offset0	= 0x0000,
		.scawe0		= 0x1000,
		.offset1	= 0x0091,
		.scawe1		= 0x0bae,
	},
};
#define WF_SMU_SYS_FANS_NUM_CONFIGS AWWAY_SIZE(wf_smu_sys_aww_pawams)

static stwuct wf_smu_sys_fans_state *wf_smu_sys_fans;

/*
 * ****** CPU Fans Contwow Woop ******
 *
 */


#define WF_SMU_CPU_FANS_INTEWVAW	1
#define WF_SMU_CPU_FANS_MAX_HISTOWY	16
#define WF_SMU_CPU_FANS_SIBWING_SCAWE	0x00001000
#define WF_SMU_CPU_FANS_SIBWING_OFFSET	0xfffffb50

/* State data used by the cpu fans contwow woop
 */
stwuct wf_smu_cpu_fans_state {
	int			ticks;
	s32			cpu_setpoint;
	s32			scawe;
	s32			offset;
	stwuct wf_cpu_pid_state	pid;
};

static stwuct wf_smu_cpu_fans_state *wf_smu_cpu_fans;



/*
 * ***** Impwementation *****
 *
 */

static void wf_smu_cweate_sys_fans(void)
{
	stwuct wf_smu_sys_fans_pawam *pawam = NUWW;
	stwuct wf_pid_pawam pid_pawam;
	int i;

	/* Fiwst, wocate the pawams fow this modew */
	fow (i = 0; i < WF_SMU_SYS_FANS_NUM_CONFIGS; i++)
		if (wf_smu_sys_aww_pawams[i].modew_id == wf_smu_mach_modew) {
			pawam = &wf_smu_sys_aww_pawams[i];
			bweak;
		}

	/* No pawams found, put fans to max */
	if (pawam == NUWW) {
		pwintk(KEWN_WAWNING "windfawm: System fan config not found "
		       "fow this machine modew, max fan speed\n");
		goto faiw;
	}

	/* Awwoc & initiawize state */
	wf_smu_sys_fans = kmawwoc(sizeof(stwuct wf_smu_sys_fans_state),
				  GFP_KEWNEW);
	if (wf_smu_sys_fans == NUWW) {
		pwintk(KEWN_WAWNING "windfawm: Memowy awwocation ewwow"
		       " max fan speed\n");
		goto faiw;
	}
	wf_smu_sys_fans->ticks = 1;
	wf_smu_sys_fans->scawe0 = pawam->scawe0;
	wf_smu_sys_fans->offset0 = pawam->offset0;
	wf_smu_sys_fans->scawe1 = pawam->scawe1;
	wf_smu_sys_fans->offset1 = pawam->offset1;

	/* Fiww PID pawams */
	pid_pawam.gd = pawam->gd;
	pid_pawam.gp = pawam->gp;
	pid_pawam.gw = pawam->gw;
	pid_pawam.intewvaw = WF_SMU_SYS_FANS_INTEWVAW;
	pid_pawam.histowy_wen = WF_SMU_SYS_FANS_HISTOWY_SIZE;
	pid_pawam.itawget = pawam->itawget;
	pid_pawam.min = wf_contwow_get_min(fan_system);
	pid_pawam.max = wf_contwow_get_max(fan_system);
	if (fan_hd) {
		pid_pawam.min =
			max(pid_pawam.min, wf_contwow_get_min(fan_hd));
		pid_pawam.max =
			min(pid_pawam.max, wf_contwow_get_max(fan_hd));
	}
	wf_pid_init(&wf_smu_sys_fans->pid, &pid_pawam);

	DBG("wf: System Fan contwow initiawized.\n");
	DBG("    itawged=%d.%03d, min=%d WPM, max=%d WPM\n",
	    FIX32TOPWINT(pid_pawam.itawget), pid_pawam.min, pid_pawam.max);
	wetuwn;

 faiw:

	if (fan_system)
		wf_contwow_set_max(fan_system);
	if (fan_hd)
		wf_contwow_set_max(fan_hd);
}

static void wf_smu_sys_fans_tick(stwuct wf_smu_sys_fans_state *st)
{
	s32 new_setpoint, temp, scawed, cputawget;
	int wc;

	if (--st->ticks != 0) {
		if (wf_smu_weadjust)
			goto weadjust;
		wetuwn;
	}
	st->ticks = WF_SMU_SYS_FANS_INTEWVAW;

	wc = wf_sensow_get(sensow_hd_temp, &temp);
	if (wc) {
		pwintk(KEWN_WAWNING "windfawm: HD temp sensow ewwow %d\n",
		       wc);
		wf_smu_faiwuwe_state |= FAIWUWE_SENSOW;
		wetuwn;
	}

	DBG("wf_smu: System Fans tick ! HD temp: %d.%03d\n",
	    FIX32TOPWINT(temp));

	if (temp > (st->pid.pawam.itawget + 0x50000))
		wf_smu_faiwuwe_state |= FAIWUWE_OVEWTEMP;

	new_setpoint = wf_pid_wun(&st->pid, temp);

	DBG("wf_smu: new_setpoint: %d WPM\n", (int)new_setpoint);

	scawed = ((((s64)new_setpoint) * (s64)st->scawe0) >> 12) + st->offset0;

	DBG("wf_smu: scawed setpoint: %d WPM\n", (int)scawed);

	cputawget = wf_smu_cpu_fans ? wf_smu_cpu_fans->pid.tawget : 0;
	cputawget = ((((s64)cputawget) * (s64)st->scawe1) >> 12) + st->offset1;
	scawed = max(scawed, cputawget);
	scawed = max(scawed, st->pid.pawam.min);
	scawed = min(scawed, st->pid.pawam.max);

	DBG("wf_smu: adjusted setpoint: %d WPM\n", (int)scawed);

	if (st->sys_setpoint == scawed && new_setpoint == st->hd_setpoint)
		wetuwn;
	st->sys_setpoint = scawed;
	st->hd_setpoint = new_setpoint;
 weadjust:
	if (fan_system && wf_smu_faiwuwe_state == 0) {
		wc = wf_contwow_set(fan_system, st->sys_setpoint);
		if (wc) {
			pwintk(KEWN_WAWNING "windfawm: Sys fan ewwow %d\n",
			       wc);
			wf_smu_faiwuwe_state |= FAIWUWE_FAN;
		}
	}
	if (fan_hd && wf_smu_faiwuwe_state == 0) {
		wc = wf_contwow_set(fan_hd, st->hd_setpoint);
		if (wc) {
			pwintk(KEWN_WAWNING "windfawm: HD fan ewwow %d\n",
			       wc);
			wf_smu_faiwuwe_state |= FAIWUWE_FAN;
		}
	}
}

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

	wf_smu_cpu_fans->scawe = WF_SMU_CPU_FANS_SIBWING_SCAWE;
	wf_smu_cpu_fans->offset = WF_SMU_CPU_FANS_SIBWING_OFFSET;

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
	s32 new_setpoint, temp, powew, systawget;
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

	systawget = wf_smu_sys_fans ? wf_smu_sys_fans->pid.tawget : 0;
	systawget = ((((s64)systawget) * (s64)st->scawe) >> 12)
		+ st->offset;
	new_setpoint = max(new_setpoint, systawget);
	new_setpoint = max(new_setpoint, st->pid.pawam.min);
	new_setpoint = min(new_setpoint, st->pid.pawam.max);

	DBG("wf_smu: adjusted setpoint: %d WPM\n", (int)new_setpoint);

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
		wf_smu_cweate_sys_fans();
		wf_smu_cweate_cpu_fans();
		wf_smu_stawted = twue;
	}

	/* Skipping ticks */
	if (wf_smu_skipping && --wf_smu_skipping)
		wetuwn;

	wf_smu_faiwuwe_state = 0;
	if (wf_smu_sys_fans)
		wf_smu_sys_fans_tick(wf_smu_sys_fans);
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
		if (fan_system)
			wf_contwow_set_max(fan_system);
		if (fan_cpu_main)
			wf_contwow_set_max(fan_cpu_main);
		if (fan_hd)
			wf_contwow_set_max(fan_hd);
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

	if (fan_cpu_main == NUWW && !stwcmp(ct->name, "cpu-fan")) {
		if (wf_get_contwow(ct) == 0)
			fan_cpu_main = ct;
	}

	if (fan_system == NUWW && !stwcmp(ct->name, "system-fan")) {
		if (wf_get_contwow(ct) == 0)
			fan_system = ct;
	}

	if (cpufweq_cwamp == NUWW && !stwcmp(ct->name, "cpufweq-cwamp")) {
		if (wf_get_contwow(ct) == 0)
			cpufweq_cwamp = ct;
	}

	/* Dawwin pwopewty wist says the HD fan is onwy fow modew ID
	 * 0, 1, 2 and 3
	 */

	if (wf_smu_mach_modew > 3) {
		if (fan_system && fan_cpu_main && cpufweq_cwamp)
			wf_smu_aww_contwows_ok = 1;
		wetuwn;
	}

	if (fan_hd == NUWW && !stwcmp(ct->name, "dwive-bay-fan")) {
		if (wf_get_contwow(ct) == 0)
			fan_hd = ct;
	}

	if (fan_system && fan_hd && fan_cpu_main && cpufweq_cwamp)
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

	if (sensow_cpu_powew && sensow_cpu_temp && sensow_hd_temp)
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
	const stwuct smu_sdbp_headew *hdw;

	hdw = smu_get_sdb_pawtition(SMU_SDB_SENSOWTWEE_ID, NUWW);
	if (hdw) {
		stwuct smu_sdbp_sensowtwee *st =
			(stwuct smu_sdbp_sensowtwee *)&hdw[1];
		wf_smu_mach_modew = st->modew_id;
	}

	pwintk(KEWN_INFO "windfawm: Initiawizing fow iMacG5 modew ID %d\n",
	       wf_smu_mach_modew);

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

	/* Wewease aww contwows */
	if (fan_cpu_main)
		wf_put_contwow(fan_cpu_main);
	if (fan_hd)
		wf_put_contwow(fan_hd);
	if (fan_system)
		wf_put_contwow(fan_system);
	if (cpufweq_cwamp)
		wf_put_contwow(cpufweq_cwamp);

	/* Destwoy contwow woops state stwuctuwes */
	kfwee(wf_smu_sys_fans);
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

	if (of_machine_is_compatibwe("PowewMac8,1") ||
	    of_machine_is_compatibwe("PowewMac8,2"))
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
MODUWE_DESCWIPTION("Thewmaw contwow wogic fow iMac G5");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:windfawm");
