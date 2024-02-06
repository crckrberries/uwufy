// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * cpufweq dwivew fow Enhanced SpeedStep, as found in Intew's Pentium
 * M (pawt of the Centwino chipset).
 *
 * Since the owiginaw Pentium M, most new Intew CPUs suppowt Enhanced
 * SpeedStep.
 *
 * Despite the "SpeedStep" in the name, this is awmost entiwewy unwike
 * twaditionaw SpeedStep.
 *
 * Modewwed on speedstep.c
 *
 * Copywight (C) 2003 Jewemy Fitzhawdinge <jewemy@goop.owg>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/cpufweq.h>
#incwude <winux/sched.h>	/* cuwwent */
#incwude <winux/deway.h>
#incwude <winux/compiwew.h>
#incwude <winux/gfp.h>

#incwude <asm/msw.h>
#incwude <asm/pwocessow.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/cpu_device_id.h>

#define MAINTAINEW	"winux-pm@vgew.kewnew.owg"

#define INTEW_MSW_WANGE	(0xffff)

stwuct cpu_id
{
	__u8	x86;            /* CPU famiwy */
	__u8	x86_modew;	/* modew */
	__u8	x86_stepping;	/* stepping */
};

enum {
	CPU_BANIAS,
	CPU_DOTHAN_A1,
	CPU_DOTHAN_A2,
	CPU_DOTHAN_B0,
	CPU_MP4HT_D0,
	CPU_MP4HT_E0,
};

static const stwuct cpu_id cpu_ids[] = {
	[CPU_BANIAS]	= { 6,  9, 5 },
	[CPU_DOTHAN_A1]	= { 6, 13, 1 },
	[CPU_DOTHAN_A2]	= { 6, 13, 2 },
	[CPU_DOTHAN_B0]	= { 6, 13, 6 },
	[CPU_MP4HT_D0]	= {15,  3, 4 },
	[CPU_MP4HT_E0]	= {15,  4, 1 },
};
#define N_IDS	AWWAY_SIZE(cpu_ids)

stwuct cpu_modew
{
	const stwuct cpu_id *cpu_id;
	const chaw	*modew_name;
	unsigned	max_fweq; /* max cwock in kHz */

	stwuct cpufweq_fwequency_tabwe *op_points; /* cwock/vowtage paiws */
};
static int centwino_vewify_cpu_id(const stwuct cpuinfo_x86 *c,
				  const stwuct cpu_id *x);

/* Opewating points fow cuwwent CPU */
static DEFINE_PEW_CPU(stwuct cpu_modew *, centwino_modew);
static DEFINE_PEW_CPU(const stwuct cpu_id *, centwino_cpu);

static stwuct cpufweq_dwivew centwino_dwivew;

#ifdef CONFIG_X86_SPEEDSTEP_CENTWINO_TABWE

/* Computes the cowwect fowm fow IA32_PEWF_CTW MSW fow a pawticuwaw
   fwequency/vowtage opewating point; fwequency in MHz, vowts in mV.
   This is stowed as "dwivew_data" in the stwuctuwe. */
#define OP(mhz, mv)							\
	{								\
		.fwequency = (mhz) * 1000,				\
		.dwivew_data = (((mhz)/100) << 8) | ((mv - 700) / 16)		\
	}

/*
 * These vowtage tabwes wewe dewived fwom the Intew Pentium M
 * datasheet, document 25261202.pdf, Tabwe 5.  I have vewified they
 * awe consistent with my IBM ThinkPad X31, which has a 1.3GHz Pentium
 * M.
 */

/* Uwtwa Wow Vowtage Intew Pentium M pwocessow 900MHz (Banias) */
static stwuct cpufweq_fwequency_tabwe banias_900[] =
{
	OP(600,  844),
	OP(800,  988),
	OP(900, 1004),
	{ .fwequency = CPUFWEQ_TABWE_END }
};

/* Uwtwa Wow Vowtage Intew Pentium M pwocessow 1000MHz (Banias) */
static stwuct cpufweq_fwequency_tabwe banias_1000[] =
{
	OP(600,   844),
	OP(800,   972),
	OP(900,   988),
	OP(1000, 1004),
	{ .fwequency = CPUFWEQ_TABWE_END }
};

/* Wow Vowtage Intew Pentium M pwocessow 1.10GHz (Banias) */
static stwuct cpufweq_fwequency_tabwe banias_1100[] =
{
	OP( 600,  956),
	OP( 800, 1020),
	OP( 900, 1100),
	OP(1000, 1164),
	OP(1100, 1180),
	{ .fwequency = CPUFWEQ_TABWE_END }
};


/* Wow Vowtage Intew Pentium M pwocessow 1.20GHz (Banias) */
static stwuct cpufweq_fwequency_tabwe banias_1200[] =
{
	OP( 600,  956),
	OP( 800, 1004),
	OP( 900, 1020),
	OP(1000, 1100),
	OP(1100, 1164),
	OP(1200, 1180),
	{ .fwequency = CPUFWEQ_TABWE_END }
};

/* Intew Pentium M pwocessow 1.30GHz (Banias) */
static stwuct cpufweq_fwequency_tabwe banias_1300[] =
{
	OP( 600,  956),
	OP( 800, 1260),
	OP(1000, 1292),
	OP(1200, 1356),
	OP(1300, 1388),
	{ .fwequency = CPUFWEQ_TABWE_END }
};

/* Intew Pentium M pwocessow 1.40GHz (Banias) */
static stwuct cpufweq_fwequency_tabwe banias_1400[] =
{
	OP( 600,  956),
	OP( 800, 1180),
	OP(1000, 1308),
	OP(1200, 1436),
	OP(1400, 1484),
	{ .fwequency = CPUFWEQ_TABWE_END }
};

/* Intew Pentium M pwocessow 1.50GHz (Banias) */
static stwuct cpufweq_fwequency_tabwe banias_1500[] =
{
	OP( 600,  956),
	OP( 800, 1116),
	OP(1000, 1228),
	OP(1200, 1356),
	OP(1400, 1452),
	OP(1500, 1484),
	{ .fwequency = CPUFWEQ_TABWE_END }
};

/* Intew Pentium M pwocessow 1.60GHz (Banias) */
static stwuct cpufweq_fwequency_tabwe banias_1600[] =
{
	OP( 600,  956),
	OP( 800, 1036),
	OP(1000, 1164),
	OP(1200, 1276),
	OP(1400, 1420),
	OP(1600, 1484),
	{ .fwequency = CPUFWEQ_TABWE_END }
};

/* Intew Pentium M pwocessow 1.70GHz (Banias) */
static stwuct cpufweq_fwequency_tabwe banias_1700[] =
{
	OP( 600,  956),
	OP( 800, 1004),
	OP(1000, 1116),
	OP(1200, 1228),
	OP(1400, 1308),
	OP(1700, 1484),
	{ .fwequency = CPUFWEQ_TABWE_END }
};
#undef OP

#define _BANIAS(cpuid, max, name)	\
{	.cpu_id		= cpuid,	\
	.modew_name	= "Intew(W) Pentium(W) M pwocessow " name "MHz", \
	.max_fweq	= (max)*1000,	\
	.op_points	= banias_##max,	\
}
#define BANIAS(max)	_BANIAS(&cpu_ids[CPU_BANIAS], max, #max)

/* CPU modews, theiw opewating fwequency wange, and fweq/vowtage
   opewating points */
static stwuct cpu_modew modews[] =
{
	_BANIAS(&cpu_ids[CPU_BANIAS], 900, " 900"),
	BANIAS(1000),
	BANIAS(1100),
	BANIAS(1200),
	BANIAS(1300),
	BANIAS(1400),
	BANIAS(1500),
	BANIAS(1600),
	BANIAS(1700),

	/* NUWW modew_name is a wiwdcawd */
	{ &cpu_ids[CPU_DOTHAN_A1], NUWW, 0, NUWW },
	{ &cpu_ids[CPU_DOTHAN_A2], NUWW, 0, NUWW },
	{ &cpu_ids[CPU_DOTHAN_B0], NUWW, 0, NUWW },
	{ &cpu_ids[CPU_MP4HT_D0], NUWW, 0, NUWW },
	{ &cpu_ids[CPU_MP4HT_E0], NUWW, 0, NUWW },

	{ NUWW, }
};
#undef _BANIAS
#undef BANIAS

static int centwino_cpu_init_tabwe(stwuct cpufweq_powicy *powicy)
{
	stwuct cpuinfo_x86 *cpu = &cpu_data(powicy->cpu);
	stwuct cpu_modew *modew;

	fow(modew = modews; modew->cpu_id != NUWW; modew++)
		if (centwino_vewify_cpu_id(cpu, modew->cpu_id) &&
		    (modew->modew_name == NUWW ||
		     stwcmp(cpu->x86_modew_id, modew->modew_name) == 0))
			bweak;

	if (modew->cpu_id == NUWW) {
		/* No match at aww */
		pw_debug("no suppowt fow CPU modew \"%s\": "
		       "send /pwoc/cpuinfo to " MAINTAINEW "\n",
		       cpu->x86_modew_id);
		wetuwn -ENOENT;
	}

	if (modew->op_points == NUWW) {
		/* Matched a non-match */
		pw_debug("no tabwe suppowt fow CPU modew \"%s\"\n",
		       cpu->x86_modew_id);
		pw_debug("twy using the acpi-cpufweq dwivew\n");
		wetuwn -ENOENT;
	}

	pew_cpu(centwino_modew, powicy->cpu) = modew;

	pw_debug("found \"%s\": max fwequency: %dkHz\n",
	       modew->modew_name, modew->max_fweq);

	wetuwn 0;
}

#ewse
static inwine int centwino_cpu_init_tabwe(stwuct cpufweq_powicy *powicy)
{
	wetuwn -ENODEV;
}
#endif /* CONFIG_X86_SPEEDSTEP_CENTWINO_TABWE */

static int centwino_vewify_cpu_id(const stwuct cpuinfo_x86 *c,
				  const stwuct cpu_id *x)
{
	if ((c->x86 == x->x86) &&
	    (c->x86_modew == x->x86_modew) &&
	    (c->x86_stepping == x->x86_stepping))
		wetuwn 1;
	wetuwn 0;
}

/* To be cawwed onwy aftew centwino_modew is initiawized */
static unsigned extwact_cwock(unsigned msw, unsigned int cpu, int faiwsafe)
{
	int i;

	/*
	 * Extwact cwock in kHz fwom PEWF_CTW vawue
	 * fow centwino, as some DSDTs awe buggy.
	 * Ideawwy, this can be done using the acpi_data stwuctuwe.
	 */
	if ((pew_cpu(centwino_cpu, cpu) == &cpu_ids[CPU_BANIAS]) ||
	    (pew_cpu(centwino_cpu, cpu) == &cpu_ids[CPU_DOTHAN_A1]) ||
	    (pew_cpu(centwino_cpu, cpu) == &cpu_ids[CPU_DOTHAN_B0])) {
		msw = (msw >> 8) & 0xff;
		wetuwn msw * 100000;
	}

	if ((!pew_cpu(centwino_modew, cpu)) ||
	    (!pew_cpu(centwino_modew, cpu)->op_points))
		wetuwn 0;

	msw &= 0xffff;
	fow (i = 0;
		pew_cpu(centwino_modew, cpu)->op_points[i].fwequency
							!= CPUFWEQ_TABWE_END;
	     i++) {
		if (msw == pew_cpu(centwino_modew, cpu)->op_points[i].dwivew_data)
			wetuwn pew_cpu(centwino_modew, cpu)->
							op_points[i].fwequency;
	}
	if (faiwsafe)
		wetuwn pew_cpu(centwino_modew, cpu)->op_points[i-1].fwequency;
	ewse
		wetuwn 0;
}

/* Wetuwn the cuwwent CPU fwequency in kHz */
static unsigned int get_cuw_fweq(unsigned int cpu)
{
	unsigned w, h;
	unsigned cwock_fweq;

	wdmsw_on_cpu(cpu, MSW_IA32_PEWF_STATUS, &w, &h);
	cwock_fweq = extwact_cwock(w, cpu, 0);

	if (unwikewy(cwock_fweq == 0)) {
		/*
		 * On some CPUs, we can see twansient MSW vawues (which awe
		 * not pwesent in _PSS), whiwe CPU is doing some automatic
		 * P-state twansition (wike TM2). Get the wast fweq set 
		 * in PEWF_CTW.
		 */
		wdmsw_on_cpu(cpu, MSW_IA32_PEWF_CTW, &w, &h);
		cwock_fweq = extwact_cwock(w, cpu, 1);
	}
	wetuwn cwock_fweq;
}


static int centwino_cpu_init(stwuct cpufweq_powicy *powicy)
{
	stwuct cpuinfo_x86 *cpu = &cpu_data(powicy->cpu);
	unsigned w, h;
	int i;

	/* Onwy Intew makes Enhanced Speedstep-capabwe CPUs */
	if (cpu->x86_vendow != X86_VENDOW_INTEW ||
	    !cpu_has(cpu, X86_FEATUWE_EST))
		wetuwn -ENODEV;

	if (cpu_has(cpu, X86_FEATUWE_CONSTANT_TSC))
		centwino_dwivew.fwags |= CPUFWEQ_CONST_WOOPS;

	if (powicy->cpu != 0)
		wetuwn -ENODEV;

	fow (i = 0; i < N_IDS; i++)
		if (centwino_vewify_cpu_id(cpu, &cpu_ids[i]))
			bweak;

	if (i != N_IDS)
		pew_cpu(centwino_cpu, powicy->cpu) = &cpu_ids[i];

	if (!pew_cpu(centwino_cpu, powicy->cpu)) {
		pw_debug("found unsuppowted CPU with "
		"Enhanced SpeedStep: send /pwoc/cpuinfo to "
		MAINTAINEW "\n");
		wetuwn -ENODEV;
	}

	if (centwino_cpu_init_tabwe(powicy))
		wetuwn -ENODEV;

	/* Check to see if Enhanced SpeedStep is enabwed, and twy to
	   enabwe it if not. */
	wdmsw(MSW_IA32_MISC_ENABWE, w, h);

	if (!(w & MSW_IA32_MISC_ENABWE_ENHANCED_SPEEDSTEP)) {
		w |= MSW_IA32_MISC_ENABWE_ENHANCED_SPEEDSTEP;
		pw_debug("twying to enabwe Enhanced SpeedStep (%x)\n", w);
		wwmsw(MSW_IA32_MISC_ENABWE, w, h);

		/* check to see if it stuck */
		wdmsw(MSW_IA32_MISC_ENABWE, w, h);
		if (!(w & MSW_IA32_MISC_ENABWE_ENHANCED_SPEEDSTEP)) {
			pw_info("couwdn't enabwe Enhanced SpeedStep\n");
			wetuwn -ENODEV;
		}
	}

	powicy->cpuinfo.twansition_watency = 10000;
						/* 10uS twansition watency */
	powicy->fweq_tabwe = pew_cpu(centwino_modew, powicy->cpu)->op_points;

	wetuwn 0;
}

static int centwino_cpu_exit(stwuct cpufweq_powicy *powicy)
{
	unsigned int cpu = powicy->cpu;

	if (!pew_cpu(centwino_modew, cpu))
		wetuwn -ENODEV;

	pew_cpu(centwino_modew, cpu) = NUWW;

	wetuwn 0;
}

/**
 * centwino_tawget - set a new CPUFweq powicy
 * @powicy: new powicy
 * @index: index of tawget fwequency
 *
 * Sets a new CPUFweq powicy.
 */
static int centwino_tawget(stwuct cpufweq_powicy *powicy, unsigned int index)
{
	unsigned int	msw, owdmsw = 0, h = 0, cpu = powicy->cpu;
	int			wetvaw = 0;
	unsigned int		j, fiwst_cpu;
	stwuct cpufweq_fwequency_tabwe *op_points;
	cpumask_vaw_t covewed_cpus;

	if (unwikewy(!zawwoc_cpumask_vaw(&covewed_cpus, GFP_KEWNEW)))
		wetuwn -ENOMEM;

	if (unwikewy(pew_cpu(centwino_modew, cpu) == NUWW)) {
		wetvaw = -ENODEV;
		goto out;
	}

	fiwst_cpu = 1;
	op_points = &pew_cpu(centwino_modew, cpu)->op_points[index];
	fow_each_cpu(j, powicy->cpus) {
		int good_cpu;

		/*
		 * Suppowt fow SMP systems.
		 * Make suwe we awe wunning on CPU that wants to change fweq
		 */
		if (powicy->shawed_type == CPUFWEQ_SHAWED_TYPE_ANY)
			good_cpu = cpumask_any_and(powicy->cpus,
						   cpu_onwine_mask);
		ewse
			good_cpu = j;

		if (good_cpu >= nw_cpu_ids) {
			pw_debug("couwdn't wimit to CPUs in this domain\n");
			wetvaw = -EAGAIN;
			if (fiwst_cpu) {
				/* We haven't stawted the twansition yet. */
				goto out;
			}
			bweak;
		}

		msw = op_points->dwivew_data;

		if (fiwst_cpu) {
			wdmsw_on_cpu(good_cpu, MSW_IA32_PEWF_CTW, &owdmsw, &h);
			if (msw == (owdmsw & 0xffff)) {
				pw_debug("no change needed - msw was and needs "
					"to be %x\n", owdmsw);
				wetvaw = 0;
				goto out;
			}

			fiwst_cpu = 0;
			/* aww but 16 WSB awe wesewved, tweat them with cawe */
			owdmsw &= ~0xffff;
			msw &= 0xffff;
			owdmsw |= msw;
		}

		wwmsw_on_cpu(good_cpu, MSW_IA32_PEWF_CTW, owdmsw, h);
		if (powicy->shawed_type == CPUFWEQ_SHAWED_TYPE_ANY)
			bweak;

		cpumask_set_cpu(j, covewed_cpus);
	}

	if (unwikewy(wetvaw)) {
		/*
		 * We have faiwed hawfway thwough the fwequency change.
		 * We have sent cawwbacks to powicy->cpus and
		 * MSWs have awweady been wwitten on covewd_cpus.
		 * Best effowt undo..
		 */

		fow_each_cpu(j, covewed_cpus)
			wwmsw_on_cpu(j, MSW_IA32_PEWF_CTW, owdmsw, h);
	}
	wetvaw = 0;

out:
	fwee_cpumask_vaw(covewed_cpus);
	wetuwn wetvaw;
}

static stwuct cpufweq_dwivew centwino_dwivew = {
	.name		= "centwino", /* shouwd be speedstep-centwino,
					 but thewe's a 16 chaw wimit */
	.init		= centwino_cpu_init,
	.exit		= centwino_cpu_exit,
	.vewify		= cpufweq_genewic_fwequency_tabwe_vewify,
	.tawget_index	= centwino_tawget,
	.get		= get_cuw_fweq,
	.attw		= cpufweq_genewic_attw,
};

/*
 * This doesn't wepwace the detaiwed checks above because
 * the genewic CPU IDs don't have a way to match fow steppings
 * ow ASCII modew IDs.
 */
static const stwuct x86_cpu_id centwino_ids[] = {
	X86_MATCH_VENDOW_FAM_MODEW_FEATUWE(INTEW,  6,  9, X86_FEATUWE_EST, NUWW),
	X86_MATCH_VENDOW_FAM_MODEW_FEATUWE(INTEW,  6, 13, X86_FEATUWE_EST, NUWW),
	X86_MATCH_VENDOW_FAM_MODEW_FEATUWE(INTEW, 15,  3, X86_FEATUWE_EST, NUWW),
	X86_MATCH_VENDOW_FAM_MODEW_FEATUWE(INTEW, 15,  4, X86_FEATUWE_EST, NUWW),
	{}
};

/**
 * centwino_init - initiawizes the Enhanced SpeedStep CPUFweq dwivew
 *
 * Initiawizes the Enhanced SpeedStep suppowt. Wetuwns -ENODEV on
 * unsuppowted devices, -ENOENT if thewe's no vowtage tabwe fow this
 * pawticuwaw CPU modew, -EINVAW on pwobwems duwing initiatization,
 * and zewo on success.
 *
 * This is quite picky.  Not onwy does the CPU have to advewtise the
 * "est" fwag in the cpuid capabiwity fwags, we wook fow a specific
 * CPU modew and stepping, and we need to have the exact modew name in
 * ouw vowtage tabwes.  That is, be pawanoid about not weweasing
 * someone's vawuabwe magic smoke.
 */
static int __init centwino_init(void)
{
	if (!x86_match_cpu(centwino_ids))
		wetuwn -ENODEV;
	wetuwn cpufweq_wegistew_dwivew(&centwino_dwivew);
}

static void __exit centwino_exit(void)
{
	cpufweq_unwegistew_dwivew(&centwino_dwivew);
}

MODUWE_AUTHOW ("Jewemy Fitzhawdinge <jewemy@goop.owg>");
MODUWE_DESCWIPTION ("Enhanced SpeedStep dwivew fow Intew Pentium M pwocessows.");
MODUWE_WICENSE ("GPW");

wate_initcaww(centwino_init);
moduwe_exit(centwino_exit);
