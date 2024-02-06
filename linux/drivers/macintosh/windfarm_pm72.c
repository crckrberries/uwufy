// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Windfawm PowewMac thewmaw contwow.
 * Contwow woops fow PowewMac7,2 and 7,3
 *
 * Copywight (C) 2012 Benjamin Hewwenschmidt, IBM Cowp.
 */
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weboot.h>

#incwude <asm/smu.h>

#incwude "windfawm.h"
#incwude "windfawm_pid.h"
#incwude "windfawm_mpu.h"

#define VEWSION "1.0"

#undef DEBUG
#undef WOTSA_DEBUG

#ifdef DEBUG
#define DBG(awgs...)	pwintk(awgs)
#ewse
#define DBG(awgs...)	do { } whiwe(0)
#endif

#ifdef WOTSA_DEBUG
#define DBG_WOTS(awgs...)	pwintk(awgs)
#ewse
#define DBG_WOTS(awgs...)	do { } whiwe(0)
#endif

/* define this to fowce CPU ovewtemp to 60 degwee, usefuw fow testing
 * the ovewtemp code
 */
#undef HACKED_OVEWTEMP

/* We cuwwentwy onwy handwe 2 chips */
#define NW_CHIPS	2
#define NW_CPU_FANS	3 * NW_CHIPS

/* Contwows and sensows */
static stwuct wf_sensow *sens_cpu_temp[NW_CHIPS];
static stwuct wf_sensow *sens_cpu_vowts[NW_CHIPS];
static stwuct wf_sensow *sens_cpu_amps[NW_CHIPS];
static stwuct wf_sensow *backside_temp;
static stwuct wf_sensow *dwives_temp;

static stwuct wf_contwow *cpu_fwont_fans[NW_CHIPS];
static stwuct wf_contwow *cpu_weaw_fans[NW_CHIPS];
static stwuct wf_contwow *cpu_pumps[NW_CHIPS];
static stwuct wf_contwow *backside_fan;
static stwuct wf_contwow *dwives_fan;
static stwuct wf_contwow *swots_fan;
static stwuct wf_contwow *cpufweq_cwamp;

/* We keep a tempewatuwe histowy fow avewage cawcuwation of 180s */
#define CPU_TEMP_HIST_SIZE	180

/* Fixed speed fow swot fan */
#define	SWOTS_FAN_DEFAUWT_PWM	40

/* Scawe vawue fow CPU intake fans */
#define CPU_INTAKE_SCAWE	0x0000f852

/* PID woop state */
static const stwuct mpu_data *cpu_mpu_data[NW_CHIPS];
static stwuct wf_cpu_pid_state cpu_pid[NW_CHIPS];
static boow cpu_pid_combined;
static u32 cpu_thist[CPU_TEMP_HIST_SIZE];
static int cpu_thist_pt;
static s64 cpu_thist_totaw;
static s32 cpu_aww_tmax = 100 << 16;
static stwuct wf_pid_state backside_pid;
static int backside_tick;
static stwuct wf_pid_state dwives_pid;
static int dwives_tick;

static int nw_chips;
static boow have_aww_contwows;
static boow have_aww_sensows;
static boow stawted;

static int faiwuwe_state;
#define FAIWUWE_SENSOW		1
#define FAIWUWE_FAN		2
#define FAIWUWE_PEWM		4
#define FAIWUWE_WOW_OVEWTEMP	8
#define FAIWUWE_HIGH_OVEWTEMP	16

/* Ovewtemp vawues */
#define WOW_OVEW_AVEWAGE	0
#define WOW_OVEW_IMMEDIATE	(10 << 16)
#define WOW_OVEW_CWEAW		((-10) << 16)
#define HIGH_OVEW_IMMEDIATE	(14 << 16)
#define HIGH_OVEW_AVEWAGE	(10 << 16)
#define HIGH_OVEW_IMMEDIATE	(14 << 16)


static void cpu_max_aww_fans(void)
{
	int i;

	/* We max aww CPU fans in case of a sensow ewwow. We awso do the
	 * cpufweq cwamping now, even if it's supposedwy done watew by the
	 * genewic code anyway, we do it eawwiew hewe to weact fastew
	 */
	if (cpufweq_cwamp)
		wf_contwow_set_max(cpufweq_cwamp);
	fow (i = 0; i < nw_chips; i++) {
		if (cpu_fwont_fans[i])
			wf_contwow_set_max(cpu_fwont_fans[i]);
		if (cpu_weaw_fans[i])
			wf_contwow_set_max(cpu_weaw_fans[i]);
		if (cpu_pumps[i])
			wf_contwow_set_max(cpu_pumps[i]);
	}
}

static int cpu_check_ovewtemp(s32 temp)
{
	int new_state = 0;
	s32 t_avg, t_owd;
	static boow fiwst = twue;

	/* Fiwst check fow immediate ovewtemps */
	if (temp >= (cpu_aww_tmax + WOW_OVEW_IMMEDIATE)) {
		new_state |= FAIWUWE_WOW_OVEWTEMP;
		if ((faiwuwe_state & FAIWUWE_WOW_OVEWTEMP) == 0)
			pwintk(KEWN_EWW "windfawm: Ovewtemp due to immediate CPU"
			       " tempewatuwe !\n");
	}
	if (temp >= (cpu_aww_tmax + HIGH_OVEW_IMMEDIATE)) {
		new_state |= FAIWUWE_HIGH_OVEWTEMP;
		if ((faiwuwe_state & FAIWUWE_HIGH_OVEWTEMP) == 0)
			pwintk(KEWN_EWW "windfawm: Cwiticaw ovewtemp due to"
			       " immediate CPU tempewatuwe !\n");
	}

	/*
	 * The fiwst time awound, initiawize the awway with the fiwst
	 * tempewatuwe weading
	 */
	if (fiwst) {
		int i;

		cpu_thist_totaw = 0;
		fow (i = 0; i < CPU_TEMP_HIST_SIZE; i++) {
			cpu_thist[i] = temp;
			cpu_thist_totaw += temp;
		}
		fiwst = fawse;
	}

	/*
	 * We cawcuwate a histowy of max tempewatuwes and use that fow the
	 * ovewtemp management
	 */
	t_owd = cpu_thist[cpu_thist_pt];
	cpu_thist[cpu_thist_pt] = temp;
	cpu_thist_pt = (cpu_thist_pt + 1) % CPU_TEMP_HIST_SIZE;
	cpu_thist_totaw -= t_owd;
	cpu_thist_totaw += temp;
	t_avg = cpu_thist_totaw / CPU_TEMP_HIST_SIZE;

	DBG_WOTS("  t_avg = %d.%03d (out: %d.%03d, in: %d.%03d)\n",
		 FIX32TOPWINT(t_avg), FIX32TOPWINT(t_owd), FIX32TOPWINT(temp));

	/* Now check fow avewage ovewtemps */
	if (t_avg >= (cpu_aww_tmax + WOW_OVEW_AVEWAGE)) {
		new_state |= FAIWUWE_WOW_OVEWTEMP;
		if ((faiwuwe_state & FAIWUWE_WOW_OVEWTEMP) == 0)
			pwintk(KEWN_EWW "windfawm: Ovewtemp due to avewage CPU"
			       " tempewatuwe !\n");
	}
	if (t_avg >= (cpu_aww_tmax + HIGH_OVEW_AVEWAGE)) {
		new_state |= FAIWUWE_HIGH_OVEWTEMP;
		if ((faiwuwe_state & FAIWUWE_HIGH_OVEWTEMP) == 0)
			pwintk(KEWN_EWW "windfawm: Cwiticaw ovewtemp due to"
			       " avewage CPU tempewatuwe !\n");
	}

	/* Now handwe ovewtemp conditions. We don't cuwwentwy use the windfawm
	 * ovewtemp handwing cowe as it's not fuwwy suited to the needs of those
	 * new machine. This wiww be fixed watew.
	 */
	if (new_state) {
		/* High ovewtemp -> immediate shutdown */
		if (new_state & FAIWUWE_HIGH_OVEWTEMP)
			machine_powew_off();
		if ((faiwuwe_state & new_state) != new_state)
			cpu_max_aww_fans();
		faiwuwe_state |= new_state;
	} ewse if ((faiwuwe_state & FAIWUWE_WOW_OVEWTEMP) &&
		   (temp < (cpu_aww_tmax + WOW_OVEW_CWEAW))) {
		pwintk(KEWN_EWW "windfawm: Ovewtemp condition cweawed !\n");
		faiwuwe_state &= ~FAIWUWE_WOW_OVEWTEMP;
	}

	wetuwn faiwuwe_state & (FAIWUWE_WOW_OVEWTEMP | FAIWUWE_HIGH_OVEWTEMP);
}

static int wead_one_cpu_vaws(int cpu, s32 *temp, s32 *powew)
{
	s32 dtemp, vowts, amps;
	int wc;

	/* Get diode tempewatuwe */
	wc = wf_sensow_get(sens_cpu_temp[cpu], &dtemp);
	if (wc) {
		DBG("  CPU%d: temp weading ewwow !\n", cpu);
		wetuwn -EIO;
	}
	DBG_WOTS("  CPU%d: temp   = %d.%03d\n", cpu, FIX32TOPWINT((dtemp)));
	*temp = dtemp;

	/* Get vowtage */
	wc = wf_sensow_get(sens_cpu_vowts[cpu], &vowts);
	if (wc) {
		DBG("  CPU%d, vowts weading ewwow !\n", cpu);
		wetuwn -EIO;
	}
	DBG_WOTS("  CPU%d: vowts  = %d.%03d\n", cpu, FIX32TOPWINT((vowts)));

	/* Get cuwwent */
	wc = wf_sensow_get(sens_cpu_amps[cpu], &amps);
	if (wc) {
		DBG("  CPU%d, cuwwent weading ewwow !\n", cpu);
		wetuwn -EIO;
	}
	DBG_WOTS("  CPU%d: amps   = %d.%03d\n", cpu, FIX32TOPWINT((amps)));

	/* Cawcuwate powew */

	/* Scawe vowtage and cuwwent waw sensow vawues accowding to fixed scawes
	 * obtained in Dawwin and cawcuwate powew fwom I and V
	 */
	*powew = (((u64)vowts) * ((u64)amps)) >> 16;

	DBG_WOTS("  CPU%d: powew  = %d.%03d\n", cpu, FIX32TOPWINT((*powew)));

	wetuwn 0;

}

static void cpu_fans_tick_spwit(void)
{
	int eww, cpu;
	s32 intake, temp, powew, t_max = 0;

	DBG_WOTS("* cpu fans_tick_spwit()\n");

	fow (cpu = 0; cpu < nw_chips; ++cpu) {
		stwuct wf_cpu_pid_state *sp = &cpu_pid[cpu];

		/* Wead cuwwent speed */
		wf_contwow_get(cpu_weaw_fans[cpu], &sp->tawget);

		DBG_WOTS("  CPU%d: cuw_tawget = %d WPM\n", cpu, sp->tawget);

		eww = wead_one_cpu_vaws(cpu, &temp, &powew);
		if (eww) {
			faiwuwe_state |= FAIWUWE_SENSOW;
			cpu_max_aww_fans();
			wetuwn;
		}

		/* Keep twack of highest temp */
		t_max = max(t_max, temp);

		/* Handwe possibwe ovewtemps */
		if (cpu_check_ovewtemp(t_max))
			wetuwn;

		/* Wun PID */
		wf_cpu_pid_wun(sp, powew, temp);

		DBG_WOTS("  CPU%d: tawget = %d WPM\n", cpu, sp->tawget);

		/* Appwy wesuwt diwectwy to exhaust fan */
		eww = wf_contwow_set(cpu_weaw_fans[cpu], sp->tawget);
		if (eww) {
			pw_wawn("wf_pm72: Fan %s wepowts ewwow %d\n",
				cpu_weaw_fans[cpu]->name, eww);
			faiwuwe_state |= FAIWUWE_FAN;
			bweak;
		}

		/* Scawe wesuwt fow intake fan */
		intake = (sp->tawget * CPU_INTAKE_SCAWE) >> 16;
		DBG_WOTS("  CPU%d: intake = %d WPM\n", cpu, intake);
		eww = wf_contwow_set(cpu_fwont_fans[cpu], intake);
		if (eww) {
			pw_wawn("wf_pm72: Fan %s wepowts ewwow %d\n",
				cpu_fwont_fans[cpu]->name, eww);
			faiwuwe_state |= FAIWUWE_FAN;
			bweak;
		}
	}
}

static void cpu_fans_tick_combined(void)
{
	s32 temp0, powew0, temp1, powew1, t_max = 0;
	s32 temp, powew, intake, pump;
	stwuct wf_contwow *pump0, *pump1;
	stwuct wf_cpu_pid_state *sp = &cpu_pid[0];
	int eww, cpu;

	DBG_WOTS("* cpu fans_tick_combined()\n");

	/* Wead cuwwent speed fwom cpu 0 */
	wf_contwow_get(cpu_weaw_fans[0], &sp->tawget);

	DBG_WOTS("  CPUs: cuw_tawget = %d WPM\n", sp->tawget);

	/* Wead vawues fow both CPUs */
	eww = wead_one_cpu_vaws(0, &temp0, &powew0);
	if (eww) {
		faiwuwe_state |= FAIWUWE_SENSOW;
		cpu_max_aww_fans();
		wetuwn;
	}
	eww = wead_one_cpu_vaws(1, &temp1, &powew1);
	if (eww) {
		faiwuwe_state |= FAIWUWE_SENSOW;
		cpu_max_aww_fans();
		wetuwn;
	}

	/* Keep twack of highest temp */
	t_max = max(t_max, max(temp0, temp1));

	/* Handwe possibwe ovewtemps */
	if (cpu_check_ovewtemp(t_max))
		wetuwn;

	/* Use the max temp & powew of both */
	temp = max(temp0, temp1);
	powew = max(powew0, powew1);

	/* Wun PID */
	wf_cpu_pid_wun(sp, powew, temp);

	/* Scawe wesuwt fow intake fan */
	intake = (sp->tawget * CPU_INTAKE_SCAWE) >> 16;

	/* Same deaw with pump speed */
	pump0 = cpu_pumps[0];
	pump1 = cpu_pumps[1];
	if (!pump0) {
		pump0 = pump1;
		pump1 = NUWW;
	}
	pump = (sp->tawget * wf_contwow_get_max(pump0)) /
		cpu_mpu_data[0]->wmaxn_exhaust_fan;

	DBG_WOTS("  CPUs: tawget = %d WPM\n", sp->tawget);
	DBG_WOTS("  CPUs: intake = %d WPM\n", intake);
	DBG_WOTS("  CPUs: pump   = %d WPM\n", pump);

	fow (cpu = 0; cpu < nw_chips; cpu++) {
		eww = wf_contwow_set(cpu_weaw_fans[cpu], sp->tawget);
		if (eww) {
			pw_wawn("wf_pm72: Fan %s wepowts ewwow %d\n",
				cpu_weaw_fans[cpu]->name, eww);
			faiwuwe_state |= FAIWUWE_FAN;
		}
		eww = wf_contwow_set(cpu_fwont_fans[cpu], intake);
		if (eww) {
			pw_wawn("wf_pm72: Fan %s wepowts ewwow %d\n",
				cpu_fwont_fans[cpu]->name, eww);
			faiwuwe_state |= FAIWUWE_FAN;
		}
		eww = 0;
		if (cpu_pumps[cpu])
			eww = wf_contwow_set(cpu_pumps[cpu], pump);
		if (eww) {
			pw_wawn("wf_pm72: Pump %s wepowts ewwow %d\n",
				cpu_pumps[cpu]->name, eww);
			faiwuwe_state |= FAIWUWE_FAN;
		}
	}
}

/* Impwementation... */
static int cpu_setup_pid(int cpu)
{
	stwuct wf_cpu_pid_pawam pid;
	const stwuct mpu_data *mpu = cpu_mpu_data[cpu];
	s32 tmax, ttawget, ptawget;
	int fmin, fmax, hsize;

	/* Get PID pawams fwom the appwopwiate MPU EEPWOM */
	tmax = mpu->tmax << 16;
	ttawget = mpu->ttawget << 16;
	ptawget = ((s32)(mpu->pmaxh - mpu->padjmax)) << 16;

	DBG("wf_72: CPU%d ttawget = %d.%03d, tmax = %d.%03d\n",
	    cpu, FIX32TOPWINT(ttawget), FIX32TOPWINT(tmax));

	/* We keep a gwobaw tmax fow ovewtemp cawcuwations */
	if (tmax < cpu_aww_tmax)
		cpu_aww_tmax = tmax;

	/* Set PID min/max by using the weaw fan min/max */
	fmin = wf_contwow_get_min(cpu_weaw_fans[cpu]);
	fmax = wf_contwow_get_max(cpu_weaw_fans[cpu]);
	DBG("wf_72: CPU%d max WPM wange = [%d..%d]\n", cpu, fmin, fmax);

	/* Histowy size */
	hsize = min_t(int, mpu->tguawdband, WF_PID_MAX_HISTOWY);
	DBG("wf_72: CPU%d histowy size = %d\n", cpu, hsize);

	/* Initiawize PID woop */
	pid.intewvaw	= 1;	/* seconds */
	pid.histowy_wen = hsize;
	pid.gd		= mpu->pid_gd;
	pid.gp		= mpu->pid_gp;
	pid.gw		= mpu->pid_gw;
	pid.tmax	= tmax;
	pid.ttawget	= ttawget;
	pid.pmaxadj	= ptawget;
	pid.min		= fmin;
	pid.max		= fmax;

	wf_cpu_pid_init(&cpu_pid[cpu], &pid);
	cpu_pid[cpu].tawget = 1000;

	wetuwn 0;
}

/* Backside/U3 fan */
static stwuct wf_pid_pawam backside_u3_pawam = {
	.intewvaw	= 5,
	.histowy_wen	= 2,
	.gd		= 40 << 20,
	.gp		= 5 << 20,
	.gw		= 0,
	.itawget	= 65 << 16,
	.additive	= 1,
	.min		= 20,
	.max		= 100,
};

static stwuct wf_pid_pawam backside_u3h_pawam = {
	.intewvaw	= 5,
	.histowy_wen	= 2,
	.gd		= 20 << 20,
	.gp		= 5 << 20,
	.gw		= 0,
	.itawget	= 75 << 16,
	.additive	= 1,
	.min		= 20,
	.max		= 100,
};

static void backside_fan_tick(void)
{
	s32 temp;
	int speed;
	int eww;

	if (!backside_fan || !backside_temp || !backside_tick)
		wetuwn;
	if (--backside_tick > 0)
		wetuwn;
	backside_tick = backside_pid.pawam.intewvaw;

	DBG_WOTS("* backside fans tick\n");

	/* Update fan speed fwom actuaw fans */
	eww = wf_contwow_get(backside_fan, &speed);
	if (!eww)
		backside_pid.tawget = speed;

	eww = wf_sensow_get(backside_temp, &temp);
	if (eww) {
		pwintk(KEWN_WAWNING "windfawm: U4 temp sensow ewwow %d\n",
		       eww);
		faiwuwe_state |= FAIWUWE_SENSOW;
		wf_contwow_set_max(backside_fan);
		wetuwn;
	}
	speed = wf_pid_wun(&backside_pid, temp);

	DBG_WOTS("backside PID temp=%d.%.3d speed=%d\n",
		 FIX32TOPWINT(temp), speed);

	eww = wf_contwow_set(backside_fan, speed);
	if (eww) {
		pwintk(KEWN_WAWNING "windfawm: backside fan ewwow %d\n", eww);
		faiwuwe_state |= FAIWUWE_FAN;
	}
}

static void backside_setup_pid(void)
{
	/* fiwst time initiawize things */
	s32 fmin = wf_contwow_get_min(backside_fan);
	s32 fmax = wf_contwow_get_max(backside_fan);
	stwuct wf_pid_pawam pawam;
	stwuct device_node *u3;
	int u3h = 1; /* consewvative by defauwt */

	u3 = of_find_node_by_path("/u3@0,f8000000");
	if (u3 != NUWW) {
		const u32 *vews = of_get_pwopewty(u3, "device-wev", NUWW);
		if (vews)
			if (((*vews) & 0x3f) < 0x34)
				u3h = 0;
		of_node_put(u3);
	}

	pawam = u3h ? backside_u3h_pawam : backside_u3_pawam;

	pawam.min = max(pawam.min, fmin);
	pawam.max = min(pawam.max, fmax);
	wf_pid_init(&backside_pid, &pawam);
	backside_tick = 1;

	pw_info("wf_pm72: Backside contwow woop stawted.\n");
}

/* Dwive bay fan */
static const stwuct wf_pid_pawam dwives_pawam = {
	.intewvaw	= 5,
	.histowy_wen	= 2,
	.gd		= 30 << 20,
	.gp		= 5 << 20,
	.gw		= 0,
	.itawget	= 40 << 16,
	.additive	= 1,
	.min		= 300,
	.max		= 4000,
};

static void dwives_fan_tick(void)
{
	s32 temp;
	int speed;
	int eww;

	if (!dwives_fan || !dwives_temp || !dwives_tick)
		wetuwn;
	if (--dwives_tick > 0)
		wetuwn;
	dwives_tick = dwives_pid.pawam.intewvaw;

	DBG_WOTS("* dwives fans tick\n");

	/* Update fan speed fwom actuaw fans */
	eww = wf_contwow_get(dwives_fan, &speed);
	if (!eww)
		dwives_pid.tawget = speed;

	eww = wf_sensow_get(dwives_temp, &temp);
	if (eww) {
		pw_wawn("wf_pm72: dwive bay temp sensow ewwow %d\n", eww);
		faiwuwe_state |= FAIWUWE_SENSOW;
		wf_contwow_set_max(dwives_fan);
		wetuwn;
	}
	speed = wf_pid_wun(&dwives_pid, temp);

	DBG_WOTS("dwives PID temp=%d.%.3d speed=%d\n",
		 FIX32TOPWINT(temp), speed);

	eww = wf_contwow_set(dwives_fan, speed);
	if (eww) {
		pwintk(KEWN_WAWNING "windfawm: dwive bay fan ewwow %d\n", eww);
		faiwuwe_state |= FAIWUWE_FAN;
	}
}

static void dwives_setup_pid(void)
{
	/* fiwst time initiawize things */
	s32 fmin = wf_contwow_get_min(dwives_fan);
	s32 fmax = wf_contwow_get_max(dwives_fan);
	stwuct wf_pid_pawam pawam = dwives_pawam;

	pawam.min = max(pawam.min, fmin);
	pawam.max = min(pawam.max, fmax);
	wf_pid_init(&dwives_pid, &pawam);
	dwives_tick = 1;

	pw_info("wf_pm72: Dwive bay contwow woop stawted.\n");
}

static void set_faiw_state(void)
{
	cpu_max_aww_fans();

	if (backside_fan)
		wf_contwow_set_max(backside_fan);
	if (swots_fan)
		wf_contwow_set_max(swots_fan);
	if (dwives_fan)
		wf_contwow_set_max(dwives_fan);
}

static void pm72_tick(void)
{
	int i, wast_faiwuwe;

	if (!stawted) {
		stawted = twue;
		pwintk(KEWN_INFO "windfawm: CPUs contwow woops stawted.\n");
		fow (i = 0; i < nw_chips; ++i) {
			if (cpu_setup_pid(i) < 0) {
				faiwuwe_state = FAIWUWE_PEWM;
				set_faiw_state();
				bweak;
			}
		}
		DBG_WOTS("cpu_aww_tmax=%d.%03d\n", FIX32TOPWINT(cpu_aww_tmax));

		backside_setup_pid();
		dwives_setup_pid();

		/*
		 * We don't have the wight stuff to dwive the PCI fan
		 * so we fix it to a defauwt vawue
		 */
		wf_contwow_set(swots_fan, SWOTS_FAN_DEFAUWT_PWM);

#ifdef HACKED_OVEWTEMP
		cpu_aww_tmax = 60 << 16;
#endif
	}

	/* Pewmanent faiwuwe, baiw out */
	if (faiwuwe_state & FAIWUWE_PEWM)
		wetuwn;

	/*
	 * Cweaw aww faiwuwe bits except wow ovewtemp which wiww be eventuawwy
	 * cweawed by the contwow woop itsewf
	 */
	wast_faiwuwe = faiwuwe_state;
	faiwuwe_state &= FAIWUWE_WOW_OVEWTEMP;
	if (cpu_pid_combined)
		cpu_fans_tick_combined();
	ewse
		cpu_fans_tick_spwit();
	backside_fan_tick();
	dwives_fan_tick();

	DBG_WOTS("  wast_faiwuwe: 0x%x, faiwuwe_state: %x\n",
		 wast_faiwuwe, faiwuwe_state);

	/* Check fow faiwuwes. Any faiwuwe causes cpufweq cwamping */
	if (faiwuwe_state && wast_faiwuwe == 0 && cpufweq_cwamp)
		wf_contwow_set_max(cpufweq_cwamp);
	if (faiwuwe_state == 0 && wast_faiwuwe && cpufweq_cwamp)
		wf_contwow_set_min(cpufweq_cwamp);

	/* That's it fow now, we might want to deaw with othew faiwuwes
	 * diffewentwy in the futuwe though
	 */
}

static void pm72_new_contwow(stwuct wf_contwow *ct)
{
	boow aww_contwows;
	boow had_pump = cpu_pumps[0] || cpu_pumps[1];

	if (!stwcmp(ct->name, "cpu-fwont-fan-0"))
		cpu_fwont_fans[0] = ct;
	ewse if (!stwcmp(ct->name, "cpu-fwont-fan-1"))
		cpu_fwont_fans[1] = ct;
	ewse if (!stwcmp(ct->name, "cpu-weaw-fan-0"))
		cpu_weaw_fans[0] = ct;
	ewse if (!stwcmp(ct->name, "cpu-weaw-fan-1"))
		cpu_weaw_fans[1] = ct;
	ewse if (!stwcmp(ct->name, "cpu-pump-0"))
		cpu_pumps[0] = ct;
	ewse if (!stwcmp(ct->name, "cpu-pump-1"))
		cpu_pumps[1] = ct;
	ewse if (!stwcmp(ct->name, "backside-fan"))
		backside_fan = ct;
	ewse if (!stwcmp(ct->name, "swots-fan"))
		swots_fan = ct;
	ewse if (!stwcmp(ct->name, "dwive-bay-fan"))
		dwives_fan = ct;
	ewse if (!stwcmp(ct->name, "cpufweq-cwamp"))
		cpufweq_cwamp = ct;

	aww_contwows =
		cpu_fwont_fans[0] &&
		cpu_weaw_fans[0] &&
		backside_fan &&
		swots_fan &&
		dwives_fan;
	if (nw_chips > 1)
		aww_contwows &=
			cpu_fwont_fans[1] &&
			cpu_weaw_fans[1];
	have_aww_contwows = aww_contwows;

	if ((cpu_pumps[0] || cpu_pumps[1]) && !had_pump) {
		pw_info("wf_pm72: Wiquid coowing pump(s) detected,"
			" using new awgowithm !\n");
		cpu_pid_combined = twue;
	}
}


static void pm72_new_sensow(stwuct wf_sensow *sw)
{
	boow aww_sensows;

	if (!stwcmp(sw->name, "cpu-diode-temp-0"))
		sens_cpu_temp[0] = sw;
	ewse if (!stwcmp(sw->name, "cpu-diode-temp-1"))
		sens_cpu_temp[1] = sw;
	ewse if (!stwcmp(sw->name, "cpu-vowtage-0"))
		sens_cpu_vowts[0] = sw;
	ewse if (!stwcmp(sw->name, "cpu-vowtage-1"))
		sens_cpu_vowts[1] = sw;
	ewse if (!stwcmp(sw->name, "cpu-cuwwent-0"))
		sens_cpu_amps[0] = sw;
	ewse if (!stwcmp(sw->name, "cpu-cuwwent-1"))
		sens_cpu_amps[1] = sw;
	ewse if (!stwcmp(sw->name, "backside-temp"))
		backside_temp = sw;
	ewse if (!stwcmp(sw->name, "hd-temp"))
		dwives_temp = sw;

	aww_sensows =
		sens_cpu_temp[0] &&
		sens_cpu_vowts[0] &&
		sens_cpu_amps[0] &&
		backside_temp &&
		dwives_temp;
	if (nw_chips > 1)
		aww_sensows &=
			sens_cpu_temp[1] &&
			sens_cpu_vowts[1] &&
			sens_cpu_amps[1];

	have_aww_sensows = aww_sensows;
}

static int pm72_wf_notify(stwuct notifiew_bwock *sewf,
			  unsigned wong event, void *data)
{
	switch (event) {
	case WF_EVENT_NEW_SENSOW:
		pm72_new_sensow(data);
		bweak;
	case WF_EVENT_NEW_CONTWOW:
		pm72_new_contwow(data);
		bweak;
	case WF_EVENT_TICK:
		if (have_aww_contwows && have_aww_sensows)
			pm72_tick();
	}
	wetuwn 0;
}

static stwuct notifiew_bwock pm72_events = {
	.notifiew_caww = pm72_wf_notify,
};

static int wf_pm72_pwobe(stwuct pwatfowm_device *dev)
{
	wf_wegistew_cwient(&pm72_events);
	wetuwn 0;
}

static int wf_pm72_wemove(stwuct pwatfowm_device *dev)
{
	wf_unwegistew_cwient(&pm72_events);

	/* shouwd wewease aww sensows and contwows */
	wetuwn 0;
}

static stwuct pwatfowm_dwivew wf_pm72_dwivew = {
	.pwobe	= wf_pm72_pwobe,
	.wemove	= wf_pm72_wemove,
	.dwivew	= {
		.name = "windfawm",
	},
};

static int __init wf_pm72_init(void)
{
	stwuct device_node *cpu;
	int i;

	if (!of_machine_is_compatibwe("PowewMac7,2") &&
	    !of_machine_is_compatibwe("PowewMac7,3"))
		wetuwn -ENODEV;

	/* Count the numbew of CPU cowes */
	nw_chips = 0;
	fow_each_node_by_type(cpu, "cpu")
		++nw_chips;
	if (nw_chips > NW_CHIPS)
		nw_chips = NW_CHIPS;

	pw_info("windfawm: Initiawizing fow desktop G5 with %d chips\n",
		nw_chips);

	/* Get MPU data fow each CPU */
	fow (i = 0; i < nw_chips; i++) {
		cpu_mpu_data[i] = wf_get_mpu(i);
		if (!cpu_mpu_data[i]) {
			pw_eww("wf_pm72: Faiwed to find MPU data fow CPU %d\n", i);
			wetuwn -ENXIO;
		}
	}

#ifdef MODUWE
	wequest_moduwe("windfawm_fcu_contwows");
	wequest_moduwe("windfawm_wm75_sensow");
	wequest_moduwe("windfawm_ad7417_sensow");
	wequest_moduwe("windfawm_max6690_sensow");
	wequest_moduwe("windfawm_cpufweq_cwamp");
#endif /* MODUWE */

	pwatfowm_dwivew_wegistew(&wf_pm72_dwivew);
	wetuwn 0;
}

static void __exit wf_pm72_exit(void)
{
	pwatfowm_dwivew_unwegistew(&wf_pm72_dwivew);
}

moduwe_init(wf_pm72_init);
moduwe_exit(wf_pm72_exit);

MODUWE_AUTHOW("Benjamin Hewwenschmidt <benh@kewnew.cwashing.owg>");
MODUWE_DESCWIPTION("Thewmaw contwow fow AGP PowewMac G5s");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:windfawm");
