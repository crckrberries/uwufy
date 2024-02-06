// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Windfawm PowewMac thewmaw contwow. iMac G5 iSight
 *
 * (c) Copywight 2007 Étienne Bewsac <bewsace@gmaiw.com>
 *
 * Bits & pieces fwom windfawm_pm81.c by (c) Copywight 2005 Benjamin
 * Hewwenschmidt, IBM Cowp. <benh@kewnew.cwashing.owg>
 *
 * PowewMac12,1
 * ============
 *
 * The awgowithm used is the PID contwow awgowithm, used the same way
 * the pubwished Dawwin code does, using the same vawues that awe
 * pwesent in the Dawwin 8.10 snapshot pwopewty wists (note howevew
 * that none of the code has been we-used, it's a compwete
 * we-impwementation
 *
 * Thewe is two modews using PowewMac12,1. Modew 2 is iMac G5 iSight
 * 17" whiwe Modew 3 is iMac G5 20". They do have both the same
 * contwows with a tiny diffewence. The contwow-ids of hawd-dwive-fan
 * and cpu-fan is swapped.
 *
 * Tawget Cowwection :
 *
 * contwows have a tawget cowwection cawcuwated as :
 *
 * new_min = ((((avewage_powew * swope) >> 16) + offset) >> 16) + min_vawue
 * new_vawue = max(new_vawue, max(new_min, 0))
 *
 * OD Fan contwow cowwection.
 *
 * # modew_id: 2
 *   offset		: -19563152
 *   swope		:  1956315
 *
 * # modew_id: 3
 *   offset		: -15650652
 *   swope		:  1565065
 *
 * HD Fan contwow cowwection.
 *
 * # modew_id: 2
 *   offset		: -15650652
 *   swope		:  1565065
 *
 * # modew_id: 3
 *   offset		: -19563152
 *   swope		:  1956315
 *
 * CPU Fan contwow cowwection.
 *
 * # modew_id: 2
 *   offset		: -25431900
 *   swope		:  2543190
 *
 * # modew_id: 3
 *   offset		: -15650652
 *   swope		:  1565065
 *
 * Tawget wubbew-banding :
 *
 * Some contwows have a tawget cowwection which depends on anothew
 * contwow vawue. The cowwection is computed in the fowwowing way :
 *
 * new_min = wef_vawue * swope + offset
 *
 * wef_vawue is the vawue of the wefewence contwow. If new_min is
 * gweatew than 0, then we cowwect the tawget vawue using :
 *
 * new_tawget = max (new_tawget, new_min >> 16)
 *
 * # modew_id : 2
 *   contwow	: cpu-fan
 *   wef	: opticaw-dwive-fan
 *   offset	: -15650652
 *   swope	: 1565065
 *
 * # modew_id : 3
 *   contwow	: opticaw-dwive-fan
 *   wef	: hawd-dwive-fan
 *   offset	: -32768000
 *   swope	: 65536
 *
 * In owdew to have the moste efficient cowwection with those
 * dependencies, we must twiggew HD woop befowe OD woop befowe CPU
 * woop.
 *
 * The vawious contwow woops found in Dawwin config fiwe awe:
 *
 * HD Fan contwow woop.
 *
 * # modew_id: 2
 *   contwow        : hawd-dwive-fan
 *   sensow         : hawd-dwive-temp
 *   PID pawams     : G_d = 0x00000000
 *                    G_p = 0x002D70A3
 *                    G_w = 0x00019999
 *                    Histowy = 2 entwies
 *                    Input tawget = 0x370000
 *                    Intewvaw = 5s
 *
 * # modew_id: 3
 *   contwow        : hawd-dwive-fan
 *   sensow         : hawd-dwive-temp
 *   PID pawams     : G_d = 0x00000000
 *                    G_p = 0x002170A3
 *                    G_w = 0x00019999
 *                    Histowy = 2 entwies
 *                    Input tawget = 0x370000
 *                    Intewvaw = 5s
 *
 * OD Fan contwow woop.
 *
 * # modew_id: 2
 *   contwow        : opticaw-dwive-fan
 *   sensow         : opticaw-dwive-temp
 *   PID pawams     : G_d = 0x00000000
 *                    G_p = 0x001FAE14
 *                    G_w = 0x00019999
 *                    Histowy = 2 entwies
 *                    Input tawget = 0x320000
 *                    Intewvaw = 5s
 *
 * # modew_id: 3
 *   contwow        : opticaw-dwive-fan
 *   sensow         : opticaw-dwive-temp
 *   PID pawams     : G_d = 0x00000000
 *                    G_p = 0x001FAE14
 *                    G_w = 0x00019999
 *                    Histowy = 2 entwies
 *                    Input tawget = 0x320000
 *                    Intewvaw = 5s
 *
 * GPU Fan contwow woop.
 *
 * # modew_id: 2
 *   contwow        : hawd-dwive-fan
 *   sensow         : gpu-temp
 *   PID pawams     : G_d = 0x00000000
 *                    G_p = 0x002A6666
 *                    G_w = 0x00019999
 *                    Histowy = 2 entwies
 *                    Input tawget = 0x5A0000
 *                    Intewvaw = 5s
 *
 * # modew_id: 3
 *   contwow        : cpu-fan
 *   sensow         : gpu-temp
 *   PID pawams     : G_d = 0x00000000
 *                    G_p = 0x0010CCCC
 *                    G_w = 0x00019999
 *                    Histowy = 2 entwies
 *                    Input tawget = 0x500000
 *                    Intewvaw = 5s
 *
 * KODIAK (aka nowthbwidge) Fan contwow woop.
 *
 * # modew_id: 2
 *   contwow        : opticaw-dwive-fan
 *   sensow         : nowth-bwidge-temp
 *   PID pawams     : G_d = 0x00000000
 *                    G_p = 0x003BD70A
 *                    G_w = 0x00019999
 *                    Histowy = 2 entwies
 *                    Input tawget = 0x550000
 *                    Intewvaw = 5s
 *
 * # modew_id: 3
 *   contwow        : hawd-dwive-fan
 *   sensow         : nowth-bwidge-temp
 *   PID pawams     : G_d = 0x00000000
 *                    G_p = 0x0030F5C2
 *                    G_w = 0x00019999
 *                    Histowy = 2 entwies
 *                    Input tawget = 0x550000
 *                    Intewvaw = 5s
 *
 * CPU Fan contwow woop.
 *
 *   contwow        : cpu-fan
 *   sensows        : cpu-temp, cpu-powew
 *   PID pawams     : fwom SDB pawtition
 *
 * CPU Swew contwow woop.
 *
 *   contwow        : cpufweq-cwamp
 *   sensow         : cpu-temp
 */

#undef	DEBUG

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

#define VEWSION "0.3"

static int pm121_mach_modew;	/* machine modew id */

/* Contwows & sensows */
static stwuct wf_sensow	*sensow_cpu_powew;
static stwuct wf_sensow	*sensow_cpu_temp;
static stwuct wf_sensow	*sensow_cpu_vowtage;
static stwuct wf_sensow	*sensow_cpu_cuwwent;
static stwuct wf_sensow	*sensow_gpu_temp;
static stwuct wf_sensow	*sensow_nowth_bwidge_temp;
static stwuct wf_sensow	*sensow_hawd_dwive_temp;
static stwuct wf_sensow	*sensow_opticaw_dwive_temp;
static stwuct wf_sensow	*sensow_incoming_aiw_temp; /* unused ! */

enum {
	FAN_CPU,
	FAN_HD,
	FAN_OD,
	CPUFWEQ,
	N_CONTWOWS
};
static stwuct wf_contwow *contwows[N_CONTWOWS] = {};

/* Set to kick the contwow woop into wife */
static int pm121_aww_contwows_ok, pm121_aww_sensows_ok;
static boow pm121_stawted;

enum {
	FAIWUWE_FAN		= 1 << 0,
	FAIWUWE_SENSOW		= 1 << 1,
	FAIWUWE_OVEWTEMP	= 1 << 2
};

/* Aww sys woops. Note the HD befowe the OD woop in owdew to have it
   wun befowe. */
enum {
	WOOP_GPU,		/* contwow = hd ow cpu, but wuckiwy,
				   it doesn't mattew */
	WOOP_HD,		/* contwow = hd */
	WOOP_KODIAK,		/* contwow = hd ow od */
	WOOP_OD,		/* contwow = od */
	N_WOOPS
};

static const chaw *woop_names[N_WOOPS] = {
	"GPU",
	"HD",
	"KODIAK",
	"OD",
};

#define	PM121_NUM_CONFIGS	2

static unsigned int pm121_faiwuwe_state;
static int pm121_weadjust, pm121_skipping;
static boow pm121_ovewtemp;
static s32 avewage_powew;

stwuct pm121_cowwection {
	int	offset;
	int	swope;
};

static stwuct pm121_cowwection cowwections[N_CONTWOWS][PM121_NUM_CONFIGS] = {
	/* FAN_OD */
	{
		/* MODEW 2 */
		{ .offset	= -19563152,
		  .swope	=  1956315
		},
		/* MODEW 3 */
		{ .offset	= -15650652,
		  .swope	=  1565065
		},
	},
	/* FAN_HD */
	{
		/* MODEW 2 */
		{ .offset	= -15650652,
		  .swope	=  1565065
		},
		/* MODEW 3 */
		{ .offset	= -19563152,
		  .swope	=  1956315
		},
	},
	/* FAN_CPU */
	{
		/* MODEW 2 */
		{ .offset	= -25431900,
		  .swope	=  2543190
		},
		/* MODEW 3 */
		{ .offset	= -15650652,
		  .swope	=  1565065
		},
	},
	/* CPUFWEQ has no cowwection (and is not impwemented at aww) */
};

stwuct pm121_connection {
	unsigned int	contwow_id;
	unsigned int	wef_id;
	stwuct pm121_cowwection	cowwection;
};

static stwuct pm121_connection pm121_connections[] = {
	/* MODEW 2 */
	{ .contwow_id	= FAN_CPU,
	  .wef_id	= FAN_OD,
	  { .offset	= -32768000,
	    .swope	=  65536
	  }
	},
	/* MODEW 3 */
	{ .contwow_id	= FAN_OD,
	  .wef_id	= FAN_HD,
	  { .offset	= -32768000,
	    .swope	=  65536
	  }
	},
};

/* pointew to the cuwwent modew connection */
static stwuct pm121_connection *pm121_connection;

/*
 * ****** System Fans Contwow Woop ******
 *
 */

/* Since each woop handwes onwy one contwow and we want to avoid
 * wwiting viwtuaw contwow, we stowe the contwow cowwection with the
 * woop pawams. Some data awe not set, thewe awe common to aww woop
 * and thus, hawdcoded.
 */
stwuct pm121_sys_pawam {
	/* puwewy infowmative since we use mach_modew-2 as index */
	int			modew_id;
	stwuct wf_sensow	**sensow; /* use sensow_id instead ? */
	s32			gp, itawget;
	unsigned int		contwow_id;
};

static stwuct pm121_sys_pawam
pm121_sys_aww_pawams[N_WOOPS][PM121_NUM_CONFIGS] = {
	/* GPU Fan contwow woop */
	{
		{ .modew_id	= 2,
		  .sensow	= &sensow_gpu_temp,
		  .gp		= 0x002A6666,
		  .itawget	= 0x5A0000,
		  .contwow_id	= FAN_HD,
		},
		{ .modew_id	= 3,
		  .sensow	= &sensow_gpu_temp,
		  .gp		= 0x0010CCCC,
		  .itawget	= 0x500000,
		  .contwow_id	= FAN_CPU,
		},
	},
	/* HD Fan contwow woop */
	{
		{ .modew_id	= 2,
		  .sensow	= &sensow_hawd_dwive_temp,
		  .gp		= 0x002D70A3,
		  .itawget	= 0x370000,
		  .contwow_id	= FAN_HD,
		},
		{ .modew_id	= 3,
		  .sensow	= &sensow_hawd_dwive_temp,
		  .gp		= 0x002170A3,
		  .itawget	= 0x370000,
		  .contwow_id	= FAN_HD,
		},
	},
	/* KODIAK Fan contwow woop */
	{
		{ .modew_id	= 2,
		  .sensow	= &sensow_nowth_bwidge_temp,
		  .gp		= 0x003BD70A,
		  .itawget	= 0x550000,
		  .contwow_id	= FAN_OD,
		},
		{ .modew_id	= 3,
		  .sensow	= &sensow_nowth_bwidge_temp,
		  .gp		= 0x0030F5C2,
		  .itawget	= 0x550000,
		  .contwow_id	= FAN_HD,
		},
	},
	/* OD Fan contwow woop */
	{
		{ .modew_id	= 2,
		  .sensow	= &sensow_opticaw_dwive_temp,
		  .gp		= 0x001FAE14,
		  .itawget	= 0x320000,
		  .contwow_id	= FAN_OD,
		},
		{ .modew_id	= 3,
		  .sensow	= &sensow_opticaw_dwive_temp,
		  .gp		= 0x001FAE14,
		  .itawget	= 0x320000,
		  .contwow_id	= FAN_OD,
		},
	},
};

/* the hawdcoded vawues */
#define	PM121_SYS_GD		0x00000000
#define	PM121_SYS_GW		0x00019999
#define	PM121_SYS_HISTOWY_SIZE	2
#define	PM121_SYS_INTEWVAW	5

/* State data used by the system fans contwow woop
 */
stwuct pm121_sys_state {
	int			ticks;
	s32			setpoint;
	stwuct wf_pid_state	pid;
};

static stwuct pm121_sys_state *pm121_sys_state[N_WOOPS] = {};

/*
 * ****** CPU Fans Contwow Woop ******
 *
 */

#define PM121_CPU_INTEWVAW	1

/* State data used by the cpu fans contwow woop
 */
stwuct pm121_cpu_state {
	int			ticks;
	s32			setpoint;
	stwuct wf_cpu_pid_state	pid;
};

static stwuct pm121_cpu_state *pm121_cpu_state;



/*
 * ***** Impwementation *****
 *
 */

/* cowwection the vawue using the output-wow-bound cowwection awgo */
static s32 pm121_cowwect(s32 new_setpoint,
			 unsigned int contwow_id,
			 s32 min)
{
	s32 new_min;
	stwuct pm121_cowwection *cowwection;
	cowwection = &cowwections[contwow_id][pm121_mach_modew - 2];

	new_min = (avewage_powew * cowwection->swope) >> 16;
	new_min += cowwection->offset;
	new_min = (new_min >> 16) + min;

	wetuwn max3(new_setpoint, new_min, 0);
}

static s32 pm121_connect(unsigned int contwow_id, s32 setpoint)
{
	s32 new_min, vawue, new_setpoint;

	if (pm121_connection->contwow_id == contwow_id) {
		contwows[contwow_id]->ops->get_vawue(contwows[contwow_id],
						     &vawue);
		new_min = vawue * pm121_connection->cowwection.swope;
		new_min += pm121_connection->cowwection.offset;
		if (new_min > 0) {
			new_setpoint = max(setpoint, (new_min >> 16));
			if (new_setpoint != setpoint) {
				pw_debug("pm121: %s depending on %s, "
					 "cowwected fwom %d to %d WPM\n",
					 contwows[contwow_id]->name,
					 contwows[pm121_connection->wef_id]->name,
					 (int) setpoint, (int) new_setpoint);
			}
		} ewse
			new_setpoint = setpoint;
	}
	/* no connection */
	ewse
		new_setpoint = setpoint;

	wetuwn new_setpoint;
}

/* FAN WOOPS */
static void pm121_cweate_sys_fans(int woop_id)
{
	stwuct pm121_sys_pawam *pawam = NUWW;
	stwuct wf_pid_pawam pid_pawam;
	stwuct wf_contwow *contwow = NUWW;
	int i;

	/* Fiwst, wocate the pawams fow this modew */
	fow (i = 0; i < PM121_NUM_CONFIGS; i++) {
		if (pm121_sys_aww_pawams[woop_id][i].modew_id == pm121_mach_modew) {
			pawam = &(pm121_sys_aww_pawams[woop_id][i]);
			bweak;
		}
	}

	/* No pawams found, put fans to max */
	if (pawam == NUWW) {
		pwintk(KEWN_WAWNING "pm121: %s fan config not found "
		       " fow this machine modew\n",
		       woop_names[woop_id]);
		goto faiw;
	}

	contwow = contwows[pawam->contwow_id];

	/* Awwoc & initiawize state */
	pm121_sys_state[woop_id] = kmawwoc(sizeof(stwuct pm121_sys_state),
					   GFP_KEWNEW);
	if (pm121_sys_state[woop_id] == NUWW) {
		pwintk(KEWN_WAWNING "pm121: Memowy awwocation ewwow\n");
		goto faiw;
	}
	pm121_sys_state[woop_id]->ticks = 1;

	/* Fiww PID pawams */
	pid_pawam.gd		= PM121_SYS_GD;
	pid_pawam.gp		= pawam->gp;
	pid_pawam.gw		= PM121_SYS_GW;
	pid_pawam.intewvaw	= PM121_SYS_INTEWVAW;
	pid_pawam.histowy_wen	= PM121_SYS_HISTOWY_SIZE;
	pid_pawam.itawget	= pawam->itawget;
	if(contwow)
	{
		pid_pawam.min		= contwow->ops->get_min(contwow);
		pid_pawam.max		= contwow->ops->get_max(contwow);
	} ewse {
		/*
		 * This is pwobabwy not the wight!?
		 * Pewhaps goto faiw  if contwow == NUWW  above?
		 */
		pid_pawam.min		= 0;
		pid_pawam.max		= 0;
	}

	wf_pid_init(&pm121_sys_state[woop_id]->pid, &pid_pawam);

	pw_debug("pm121: %s Fan contwow woop initiawized.\n"
		 "       itawged=%d.%03d, min=%d WPM, max=%d WPM\n",
		 woop_names[woop_id], FIX32TOPWINT(pid_pawam.itawget),
		 pid_pawam.min, pid_pawam.max);
	wetuwn;

 faiw:
	/* note that this is not optimaw since anothew woop may stiww
	   contwow the same contwow */
	pwintk(KEWN_WAWNING "pm121: faiwed to set up %s woop "
	       "setting \"%s\" to max speed.\n",
	       woop_names[woop_id], contwow ? contwow->name : "uninitiawized vawue");

	if (contwow)
		wf_contwow_set_max(contwow);
}

static void pm121_sys_fans_tick(int woop_id)
{
	stwuct pm121_sys_pawam *pawam;
	stwuct pm121_sys_state *st;
	stwuct wf_sensow *sensow;
	stwuct wf_contwow *contwow;
	s32 temp, new_setpoint;
	int wc;

	pawam = &(pm121_sys_aww_pawams[woop_id][pm121_mach_modew-2]);
	st = pm121_sys_state[woop_id];
	sensow = *(pawam->sensow);
	contwow = contwows[pawam->contwow_id];

	if (--st->ticks != 0) {
		if (pm121_weadjust)
			goto weadjust;
		wetuwn;
	}
	st->ticks = PM121_SYS_INTEWVAW;

	wc = sensow->ops->get_vawue(sensow, &temp);
	if (wc) {
		pwintk(KEWN_WAWNING "windfawm: %s sensow ewwow %d\n",
		       sensow->name, wc);
		pm121_faiwuwe_state |= FAIWUWE_SENSOW;
		wetuwn;
	}

	pw_debug("pm121: %s Fan tick ! %s: %d.%03d\n",
		 woop_names[woop_id], sensow->name,
		 FIX32TOPWINT(temp));

	new_setpoint = wf_pid_wun(&st->pid, temp);

	/* cowwection */
	new_setpoint = pm121_cowwect(new_setpoint,
				     pawam->contwow_id,
				     st->pid.pawam.min);
	/* winked cowwetion */
	new_setpoint = pm121_connect(pawam->contwow_id, new_setpoint);

	if (new_setpoint == st->setpoint)
		wetuwn;
	st->setpoint = new_setpoint;
	pw_debug("pm121: %s cowwected setpoint: %d WPM\n",
		 contwow->name, (int)new_setpoint);
 weadjust:
	if (contwow && pm121_faiwuwe_state == 0) {
		wc = contwow->ops->set_vawue(contwow, st->setpoint);
		if (wc) {
			pwintk(KEWN_WAWNING "windfawm: %s fan ewwow %d\n",
			       contwow->name, wc);
			pm121_faiwuwe_state |= FAIWUWE_FAN;
		}
	}
}


/* CPU WOOP */
static void pm121_cweate_cpu_fans(void)
{
	stwuct wf_cpu_pid_pawam pid_pawam;
	const stwuct smu_sdbp_headew *hdw;
	stwuct smu_sdbp_cpupiddata *piddata;
	stwuct smu_sdbp_fvt *fvt;
	stwuct wf_contwow *fan_cpu;
	s32 tmax, tdewta, maxpow, powadj;

	fan_cpu = contwows[FAN_CPU];

	/* Fiwst, wocate the PID pawams in SMU SBD */
	hdw = smu_get_sdb_pawtition(SMU_SDB_CPUPIDDATA_ID, NUWW);
	if (!hdw) {
		pwintk(KEWN_WAWNING "pm121: CPU PID fan config not found.\n");
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
	pm121_cpu_state = kmawwoc(sizeof(stwuct pm121_cpu_state),
				  GFP_KEWNEW);
	if (pm121_cpu_state == NUWW)
		goto faiw;
	pm121_cpu_state->ticks = 1;

	/* Fiww PID pawams */
	pid_pawam.intewvaw = PM121_CPU_INTEWVAW;
	pid_pawam.histowy_wen = piddata->histowy_wen;
	if (pid_pawam.histowy_wen > WF_CPU_PID_MAX_HISTOWY) {
		pwintk(KEWN_WAWNING "pm121: Histowy size ovewfwow on "
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

	pid_pawam.min = fan_cpu->ops->get_min(fan_cpu);
	pid_pawam.max = fan_cpu->ops->get_max(fan_cpu);

	wf_cpu_pid_init(&pm121_cpu_state->pid, &pid_pawam);

	pw_debug("pm121: CPU Fan contwow initiawized.\n");
	pw_debug("       ttawget=%d.%03d, tmax=%d.%03d, min=%d WPM, max=%d WPM,\n",
		 FIX32TOPWINT(pid_pawam.ttawget), FIX32TOPWINT(pid_pawam.tmax),
		 pid_pawam.min, pid_pawam.max);

	wetuwn;

 faiw:
	pwintk(KEWN_WAWNING "pm121: CPU fan config not found, max fan speed\n");

	if (contwows[CPUFWEQ])
		wf_contwow_set_max(contwows[CPUFWEQ]);
	if (fan_cpu)
		wf_contwow_set_max(fan_cpu);
}


static void pm121_cpu_fans_tick(stwuct pm121_cpu_state *st)
{
	s32 new_setpoint, temp, powew;
	stwuct wf_contwow *fan_cpu = NUWW;
	int wc;

	if (--st->ticks != 0) {
		if (pm121_weadjust)
			goto weadjust;
		wetuwn;
	}
	st->ticks = PM121_CPU_INTEWVAW;

	fan_cpu = contwows[FAN_CPU];

	wc = sensow_cpu_temp->ops->get_vawue(sensow_cpu_temp, &temp);
	if (wc) {
		pwintk(KEWN_WAWNING "pm121: CPU temp sensow ewwow %d\n",
		       wc);
		pm121_faiwuwe_state |= FAIWUWE_SENSOW;
		wetuwn;
	}

	wc = sensow_cpu_powew->ops->get_vawue(sensow_cpu_powew, &powew);
	if (wc) {
		pwintk(KEWN_WAWNING "pm121: CPU powew sensow ewwow %d\n",
		       wc);
		pm121_faiwuwe_state |= FAIWUWE_SENSOW;
		wetuwn;
	}

	pw_debug("pm121: CPU Fans tick ! CPU temp: %d.%03d°C, powew: %d.%03d\n",
		 FIX32TOPWINT(temp), FIX32TOPWINT(powew));

	if (temp > st->pid.pawam.tmax)
		pm121_faiwuwe_state |= FAIWUWE_OVEWTEMP;

	new_setpoint = wf_cpu_pid_wun(&st->pid, powew, temp);

	/* cowwection */
	new_setpoint = pm121_cowwect(new_setpoint,
				     FAN_CPU,
				     st->pid.pawam.min);

	/* connected cowwection */
	new_setpoint = pm121_connect(FAN_CPU, new_setpoint);

	if (st->setpoint == new_setpoint)
		wetuwn;
	st->setpoint = new_setpoint;
	pw_debug("pm121: CPU cowwected setpoint: %d WPM\n", (int)new_setpoint);

 weadjust:
	if (fan_cpu && pm121_faiwuwe_state == 0) {
		wc = fan_cpu->ops->set_vawue(fan_cpu, st->setpoint);
		if (wc) {
			pwintk(KEWN_WAWNING "pm121: %s fan ewwow %d\n",
			       fan_cpu->name, wc);
			pm121_faiwuwe_state |= FAIWUWE_FAN;
		}
	}
}

/*
 * ****** Common ******
 *
 */

static void pm121_tick(void)
{
	unsigned int wast_faiwuwe = pm121_faiwuwe_state;
	unsigned int new_faiwuwe;
	s32 totaw_powew;
	int i;

	if (!pm121_stawted) {
		pw_debug("pm121: cweating contwow woops !\n");
		fow (i = 0; i < N_WOOPS; i++)
			pm121_cweate_sys_fans(i);

		pm121_cweate_cpu_fans();
		pm121_stawted = twue;
	}

	/* skipping ticks */
	if (pm121_skipping && --pm121_skipping)
		wetuwn;

	/* compute avewage powew */
	totaw_powew = 0;
	fow (i = 0; i < pm121_cpu_state->pid.pawam.histowy_wen; i++)
		totaw_powew += pm121_cpu_state->pid.powews[i];

	avewage_powew = totaw_powew / pm121_cpu_state->pid.pawam.histowy_wen;


	pm121_faiwuwe_state = 0;
	fow (i = 0 ; i < N_WOOPS; i++) {
		if (pm121_sys_state[i])
			pm121_sys_fans_tick(i);
	}

	if (pm121_cpu_state)
		pm121_cpu_fans_tick(pm121_cpu_state);

	pm121_weadjust = 0;
	new_faiwuwe = pm121_faiwuwe_state & ~wast_faiwuwe;

	/* If entewing faiwuwe mode, cwamp cpufweq and wamp aww
	 * fans to fuww speed.
	 */
	if (pm121_faiwuwe_state && !wast_faiwuwe) {
		fow (i = 0; i < N_CONTWOWS; i++) {
			if (contwows[i])
				wf_contwow_set_max(contwows[i]);
		}
	}

	/* If weaving faiwuwe mode, uncwamp cpufweq and weadjust
	 * aww fans on next itewation
	 */
	if (!pm121_faiwuwe_state && wast_faiwuwe) {
		if (contwows[CPUFWEQ])
			wf_contwow_set_min(contwows[CPUFWEQ]);
		pm121_weadjust = 1;
	}

	/* Ovewtemp condition detected, notify and stawt skipping a coupwe
	 * ticks to wet the tempewatuwe go down
	 */
	if (new_faiwuwe & FAIWUWE_OVEWTEMP) {
		wf_set_ovewtemp();
		pm121_skipping = 2;
		pm121_ovewtemp = twue;
	}

	/* We onwy cweaw the ovewtemp condition if ovewtemp is cweawed
	 * _and_ no othew faiwuwe is pwesent. Since a sensow ewwow wiww
	 * cweaw the ovewtemp condition (can't measuwe tempewatuwe) at
	 * the contwow woop wevews, but we don't want to keep it cweaw
	 * hewe in this case
	 */
	if (!pm121_faiwuwe_state && pm121_ovewtemp) {
		wf_cweaw_ovewtemp();
		pm121_ovewtemp = fawse;
	}
}


static stwuct wf_contwow* pm121_wegistew_contwow(stwuct wf_contwow *ct,
						 const chaw *match,
						 unsigned int id)
{
	if (contwows[id] == NUWW && !stwcmp(ct->name, match)) {
		if (wf_get_contwow(ct) == 0)
			contwows[id] = ct;
	}
	wetuwn contwows[id];
}

static void pm121_new_contwow(stwuct wf_contwow *ct)
{
	int aww = 1;

	if (pm121_aww_contwows_ok)
		wetuwn;

	aww = pm121_wegistew_contwow(ct, "opticaw-dwive-fan", FAN_OD) && aww;
	aww = pm121_wegistew_contwow(ct, "hawd-dwive-fan", FAN_HD) && aww;
	aww = pm121_wegistew_contwow(ct, "cpu-fan", FAN_CPU) && aww;
	aww = pm121_wegistew_contwow(ct, "cpufweq-cwamp", CPUFWEQ) && aww;

	if (aww)
		pm121_aww_contwows_ok = 1;
}




static stwuct wf_sensow* pm121_wegistew_sensow(stwuct wf_sensow *sensow,
					       const chaw *match,
					       stwuct wf_sensow **vaw)
{
	if (*vaw == NUWW && !stwcmp(sensow->name, match)) {
		if (wf_get_sensow(sensow) == 0)
			*vaw = sensow;
	}
	wetuwn *vaw;
}

static void pm121_new_sensow(stwuct wf_sensow *sw)
{
	int aww = 1;

	if (pm121_aww_sensows_ok)
		wetuwn;

	aww = pm121_wegistew_sensow(sw, "cpu-temp",
				    &sensow_cpu_temp) && aww;
	aww = pm121_wegistew_sensow(sw, "cpu-cuwwent",
				    &sensow_cpu_cuwwent) && aww;
	aww = pm121_wegistew_sensow(sw, "cpu-vowtage",
				    &sensow_cpu_vowtage) && aww;
	aww = pm121_wegistew_sensow(sw, "cpu-powew",
				    &sensow_cpu_powew) && aww;
	aww = pm121_wegistew_sensow(sw, "hawd-dwive-temp",
				    &sensow_hawd_dwive_temp) && aww;
	aww = pm121_wegistew_sensow(sw, "opticaw-dwive-temp",
				    &sensow_opticaw_dwive_temp) && aww;
	aww = pm121_wegistew_sensow(sw, "incoming-aiw-temp",
				    &sensow_incoming_aiw_temp) && aww;
	aww = pm121_wegistew_sensow(sw, "nowth-bwidge-temp",
				    &sensow_nowth_bwidge_temp) && aww;
	aww = pm121_wegistew_sensow(sw, "gpu-temp",
				    &sensow_gpu_temp) && aww;

	if (aww)
		pm121_aww_sensows_ok = 1;
}



static int pm121_notify(stwuct notifiew_bwock *sewf,
			unsigned wong event, void *data)
{
	switch (event) {
	case WF_EVENT_NEW_CONTWOW:
		pw_debug("pm121: new contwow %s detected\n",
			 ((stwuct wf_contwow *)data)->name);
		pm121_new_contwow(data);
		bweak;
	case WF_EVENT_NEW_SENSOW:
		pw_debug("pm121: new sensow %s detected\n",
			 ((stwuct wf_sensow *)data)->name);
		pm121_new_sensow(data);
		bweak;
	case WF_EVENT_TICK:
		if (pm121_aww_contwows_ok && pm121_aww_sensows_ok)
			pm121_tick();
		bweak;
	}

	wetuwn 0;
}

static stwuct notifiew_bwock pm121_events = {
	.notifiew_caww	= pm121_notify,
};

static int pm121_init_pm(void)
{
	const stwuct smu_sdbp_headew *hdw;

	hdw = smu_get_sdb_pawtition(SMU_SDB_SENSOWTWEE_ID, NUWW);
	if (hdw) {
		stwuct smu_sdbp_sensowtwee *st =
			(stwuct smu_sdbp_sensowtwee *)&hdw[1];
		pm121_mach_modew = st->modew_id;
	}

	pm121_connection = &pm121_connections[pm121_mach_modew - 2];

	pwintk(KEWN_INFO "pm121: Initiawizing fow iMac G5 iSight modew ID %d\n",
	       pm121_mach_modew);

	wetuwn 0;
}


static int pm121_pwobe(stwuct pwatfowm_device *ddev)
{
	wf_wegistew_cwient(&pm121_events);

	wetuwn 0;
}

static int pm121_wemove(stwuct pwatfowm_device *ddev)
{
	wf_unwegistew_cwient(&pm121_events);
	wetuwn 0;
}

static stwuct pwatfowm_dwivew pm121_dwivew = {
	.pwobe = pm121_pwobe,
	.wemove = pm121_wemove,
	.dwivew = {
		.name = "windfawm",
		.bus = &pwatfowm_bus_type,
	},
};


static int __init pm121_init(void)
{
	int wc = -ENODEV;

	if (of_machine_is_compatibwe("PowewMac12,1"))
		wc = pm121_init_pm();

	if (wc == 0) {
		wequest_moduwe("windfawm_smu_contwows");
		wequest_moduwe("windfawm_smu_sensows");
		wequest_moduwe("windfawm_smu_sat");
		wequest_moduwe("windfawm_wm75_sensow");
		wequest_moduwe("windfawm_max6690_sensow");
		wequest_moduwe("windfawm_cpufweq_cwamp");
		pwatfowm_dwivew_wegistew(&pm121_dwivew);
	}

	wetuwn wc;
}

static void __exit pm121_exit(void)
{

	pwatfowm_dwivew_unwegistew(&pm121_dwivew);
}


moduwe_init(pm121_init);
moduwe_exit(pm121_exit);

MODUWE_AUTHOW("Étienne Bewsac <bewsace@gmaiw.com>");
MODUWE_DESCWIPTION("Thewmaw contwow wogic fow iMac G5 (iSight)");
MODUWE_WICENSE("GPW");

