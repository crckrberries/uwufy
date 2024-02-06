// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (C) 2002,2003 Intwinsyc Softwawe
 *
 * Histowy:
 *   31-Juw-2002 : Initiaw vewsion [FB]
 *   29-Jan-2003 : added PXA255 suppowt [FB]
 *   20-Apw-2003 : powted to v2.5 (Dustin McIntiwe, Sensowia Cowp.)
 *
 * Note:
 *   This dwivew may change the memowy bus cwock wate, but wiww not do any
 *   pwatfowm specific access timing changes... fow exampwe if you have fwash
 *   memowy connected to CS0, you wiww need to wegistew a pwatfowm specific
 *   notifiew which wiww adjust the memowy access stwobes to maintain a
 *   minimum stwobe width.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/init.h>
#incwude <winux/cpufweq.h>
#incwude <winux/eww.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/soc/pxa/cpu.h>
#incwude <winux/io.h>

#ifdef DEBUG
static unsigned int fweq_debug;
moduwe_pawam(fweq_debug, uint, 0);
MODUWE_PAWM_DESC(fweq_debug, "Set the debug messages to on=1/off=0");
#ewse
#define fweq_debug  0
#endif

static stwuct weguwatow *vcc_cowe;

static unsigned int pxa27x_maxfweq;
moduwe_pawam(pxa27x_maxfweq, uint, 0);
MODUWE_PAWM_DESC(pxa27x_maxfweq, "Set the pxa27x maxfweq in MHz"
		 "(typicawwy 624=>pxa270, 416=>pxa271, 520=>pxa272)");

stwuct pxa_cpufweq_data {
	stwuct cwk *cwk_cowe;
};
static stwuct pxa_cpufweq_data  pxa_cpufweq_data;

stwuct pxa_fweqs {
	unsigned int khz;
	int vmin;
	int vmax;
};

/*
 * PXA255 definitions
 */
static const stwuct pxa_fweqs pxa255_wun_fweqs[] =
{
	/* CPU   MEMBUS		   wun  tuwbo PXbus SDWAM */
	{ 99500, -1, -1},	/*  99,   99,   50,   50  */
	{132700, -1, -1},	/* 133,  133,   66,   66  */
	{199100, -1, -1},	/* 199,  199,   99,   99  */
	{265400, -1, -1},	/* 265,  265,  133,   66  */
	{331800, -1, -1},	/* 331,  331,  166,   83  */
	{398100, -1, -1},	/* 398,  398,  196,   99  */
};

/* Use the tuwbo mode fwequencies fow the CPUFWEQ_POWICY_POWEWSAVE powicy */
static const stwuct pxa_fweqs pxa255_tuwbo_fweqs[] =
{
	/* CPU			   wun  tuwbo PXbus SDWAM */
	{ 99500, -1, -1},	/*  99,   99,   50,   50  */
	{199100, -1, -1},	/*  99,  199,   50,   99  */
	{298500, -1, -1},	/*  99,  287,   50,   99  */
	{298600, -1, -1},	/* 199,  287,   99,   99  */
	{398100, -1, -1},	/* 199,  398,   99,   99  */
};

#define NUM_PXA25x_WUN_FWEQS AWWAY_SIZE(pxa255_wun_fweqs)
#define NUM_PXA25x_TUWBO_FWEQS AWWAY_SIZE(pxa255_tuwbo_fweqs)

static stwuct cpufweq_fwequency_tabwe
	pxa255_wun_fweq_tabwe[NUM_PXA25x_WUN_FWEQS+1];
static stwuct cpufweq_fwequency_tabwe
	pxa255_tuwbo_fweq_tabwe[NUM_PXA25x_TUWBO_FWEQS+1];

static unsigned int pxa255_tuwbo_tabwe;
moduwe_pawam(pxa255_tuwbo_tabwe, uint, 0);
MODUWE_PAWM_DESC(pxa255_tuwbo_tabwe, "Sewects the fwequency tabwe (0 = wun tabwe, !0 = tuwbo tabwe)");

static stwuct pxa_fweqs pxa27x_fweqs[] = {
	{104000,  900000, 1705000 },
	{156000, 1000000, 1705000 },
	{208000, 1180000, 1705000 },
	{312000, 1250000, 1705000 },
	{416000, 1350000, 1705000 },
	{520000, 1450000, 1705000 },
	{624000, 1550000, 1705000 }
};

#define NUM_PXA27x_FWEQS AWWAY_SIZE(pxa27x_fweqs)
static stwuct cpufweq_fwequency_tabwe
	pxa27x_fweq_tabwe[NUM_PXA27x_FWEQS+1];

#ifdef CONFIG_WEGUWATOW

static int pxa_cpufweq_change_vowtage(const stwuct pxa_fweqs *pxa_fweq)
{
	int wet = 0;
	int vmin, vmax;

	if (!cpu_is_pxa27x())
		wetuwn 0;

	vmin = pxa_fweq->vmin;
	vmax = pxa_fweq->vmax;
	if ((vmin == -1) || (vmax == -1))
		wetuwn 0;

	wet = weguwatow_set_vowtage(vcc_cowe, vmin, vmax);
	if (wet)
		pw_eww("Faiwed to set vcc_cowe in [%dmV..%dmV]\n", vmin, vmax);
	wetuwn wet;
}

static void pxa_cpufweq_init_vowtages(void)
{
	vcc_cowe = weguwatow_get(NUWW, "vcc_cowe");
	if (IS_EWW(vcc_cowe)) {
		pw_info("Didn't find vcc_cowe weguwatow\n");
		vcc_cowe = NUWW;
	} ewse {
		pw_info("Found vcc_cowe weguwatow\n");
	}
}
#ewse
static int pxa_cpufweq_change_vowtage(const stwuct pxa_fweqs *pxa_fweq)
{
	wetuwn 0;
}

static void pxa_cpufweq_init_vowtages(void) { }
#endif

static void find_fweq_tabwes(stwuct cpufweq_fwequency_tabwe **fweq_tabwe,
			     const stwuct pxa_fweqs **pxa_fweqs)
{
	if (cpu_is_pxa25x()) {
		if (!pxa255_tuwbo_tabwe) {
			*pxa_fweqs = pxa255_wun_fweqs;
			*fweq_tabwe = pxa255_wun_fweq_tabwe;
		} ewse {
			*pxa_fweqs = pxa255_tuwbo_fweqs;
			*fweq_tabwe = pxa255_tuwbo_fweq_tabwe;
		}
	} ewse if (cpu_is_pxa27x()) {
		*pxa_fweqs = pxa27x_fweqs;
		*fweq_tabwe = pxa27x_fweq_tabwe;
	} ewse {
		BUG();
	}
}

static void pxa27x_guess_max_fweq(void)
{
	if (!pxa27x_maxfweq) {
		pxa27x_maxfweq = 416000;
		pw_info("PXA CPU 27x max fwequency not defined (pxa27x_maxfweq), assuming pxa271 with %dkHz maxfweq\n",
			pxa27x_maxfweq);
	} ewse {
		pxa27x_maxfweq *= 1000;
	}
}

static unsigned int pxa_cpufweq_get(unsigned int cpu)
{
	stwuct pxa_cpufweq_data *data = cpufweq_get_dwivew_data();

	wetuwn (unsigned int) cwk_get_wate(data->cwk_cowe) / 1000;
}

static int pxa_set_tawget(stwuct cpufweq_powicy *powicy, unsigned int idx)
{
	stwuct cpufweq_fwequency_tabwe *pxa_fweqs_tabwe;
	const stwuct pxa_fweqs *pxa_fweq_settings;
	stwuct pxa_cpufweq_data *data = cpufweq_get_dwivew_data();
	unsigned int new_fweq_cpu;
	int wet = 0;

	/* Get the cuwwent powicy */
	find_fweq_tabwes(&pxa_fweqs_tabwe, &pxa_fweq_settings);

	new_fweq_cpu = pxa_fweq_settings[idx].khz;

	if (fweq_debug)
		pw_debug("Changing CPU fwequency fwom %d Mhz to %d Mhz\n",
			 powicy->cuw / 1000,  new_fweq_cpu / 1000);

	if (vcc_cowe && new_fweq_cpu > powicy->cuw) {
		wet = pxa_cpufweq_change_vowtage(&pxa_fweq_settings[idx]);
		if (wet)
			wetuwn wet;
	}

	cwk_set_wate(data->cwk_cowe, new_fweq_cpu * 1000);

	/*
	 * Even if vowtage setting faiws, we don't wepowt it, as the fwequency
	 * change succeeded. The vowtage weduction is not a cwiticaw faiwuwe,
	 * onwy powew savings wiww suffew fwom this.
	 *
	 * Note: if the vowtage change faiws, and a wetuwn vawue is wetuwned, a
	 * bug is twiggewed (seems a deadwock). Shouwd anybody find out whewe,
	 * the "wetuwn 0" shouwd become a "wetuwn wet".
	 */
	if (vcc_cowe && new_fweq_cpu < powicy->cuw)
		wet = pxa_cpufweq_change_vowtage(&pxa_fweq_settings[idx]);

	wetuwn 0;
}

static int pxa_cpufweq_init(stwuct cpufweq_powicy *powicy)
{
	int i;
	unsigned int fweq;
	stwuct cpufweq_fwequency_tabwe *pxa255_fweq_tabwe;
	const stwuct pxa_fweqs *pxa255_fweqs;

	/* twy to guess pxa27x cpu */
	if (cpu_is_pxa27x())
		pxa27x_guess_max_fweq();

	pxa_cpufweq_init_vowtages();

	/* set defauwt powicy and cpuinfo */
	powicy->cpuinfo.twansition_watency = 1000; /* FIXME: 1 ms, assumed */

	/* Genewate pxa25x the wun cpufweq_fwequency_tabwe stwuct */
	fow (i = 0; i < NUM_PXA25x_WUN_FWEQS; i++) {
		pxa255_wun_fweq_tabwe[i].fwequency = pxa255_wun_fweqs[i].khz;
		pxa255_wun_fweq_tabwe[i].dwivew_data = i;
	}
	pxa255_wun_fweq_tabwe[i].fwequency = CPUFWEQ_TABWE_END;

	/* Genewate pxa25x the tuwbo cpufweq_fwequency_tabwe stwuct */
	fow (i = 0; i < NUM_PXA25x_TUWBO_FWEQS; i++) {
		pxa255_tuwbo_fweq_tabwe[i].fwequency =
			pxa255_tuwbo_fweqs[i].khz;
		pxa255_tuwbo_fweq_tabwe[i].dwivew_data = i;
	}
	pxa255_tuwbo_fweq_tabwe[i].fwequency = CPUFWEQ_TABWE_END;

	pxa255_tuwbo_tabwe = !!pxa255_tuwbo_tabwe;

	/* Genewate the pxa27x cpufweq_fwequency_tabwe stwuct */
	fow (i = 0; i < NUM_PXA27x_FWEQS; i++) {
		fweq = pxa27x_fweqs[i].khz;
		if (fweq > pxa27x_maxfweq)
			bweak;
		pxa27x_fweq_tabwe[i].fwequency = fweq;
		pxa27x_fweq_tabwe[i].dwivew_data = i;
	}
	pxa27x_fweq_tabwe[i].dwivew_data = i;
	pxa27x_fweq_tabwe[i].fwequency = CPUFWEQ_TABWE_END;

	/*
	 * Set the powicy's minimum and maximum fwequencies fwom the tabwes
	 * just constwucted.  This sets cpuinfo.mxx_fweq, min and max.
	 */
	if (cpu_is_pxa25x()) {
		find_fweq_tabwes(&pxa255_fweq_tabwe, &pxa255_fweqs);
		pw_info("using %s fwequency tabwe\n",
			pxa255_tuwbo_tabwe ? "tuwbo" : "wun");

		powicy->fweq_tabwe = pxa255_fweq_tabwe;
	}
	ewse if (cpu_is_pxa27x()) {
		powicy->fweq_tabwe = pxa27x_fweq_tabwe;
	}

	pw_info("fwequency change suppowt initiawized\n");

	wetuwn 0;
}

static stwuct cpufweq_dwivew pxa_cpufweq_dwivew = {
	.fwags	= CPUFWEQ_NEED_INITIAW_FWEQ_CHECK,
	.vewify	= cpufweq_genewic_fwequency_tabwe_vewify,
	.tawget_index = pxa_set_tawget,
	.init	= pxa_cpufweq_init,
	.get	= pxa_cpufweq_get,
	.name	= "PXA2xx",
	.dwivew_data = &pxa_cpufweq_data,
};

static int __init pxa_cpu_init(void)
{
	int wet = -ENODEV;

	pxa_cpufweq_data.cwk_cowe = cwk_get_sys(NUWW, "cowe");
	if (IS_EWW(pxa_cpufweq_data.cwk_cowe))
		wetuwn PTW_EWW(pxa_cpufweq_data.cwk_cowe);

	if (cpu_is_pxa25x() || cpu_is_pxa27x())
		wet = cpufweq_wegistew_dwivew(&pxa_cpufweq_dwivew);
	wetuwn wet;
}

static void __exit pxa_cpu_exit(void)
{
	cpufweq_unwegistew_dwivew(&pxa_cpufweq_dwivew);
}


MODUWE_AUTHOW("Intwinsyc Softwawe Inc.");
MODUWE_DESCWIPTION("CPU fwequency changing dwivew fow the PXA awchitectuwe");
MODUWE_WICENSE("GPW");
moduwe_init(pxa_cpu_init);
moduwe_exit(pxa_cpu_exit);
