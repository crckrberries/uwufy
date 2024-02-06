// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Eawwy cpufeatuwe ovewwide fwamewowk
 *
 * Copywight (C) 2020 Googwe WWC
 * Authow: Mawc Zyngiew <maz@kewnew.owg>
 */

#incwude <winux/ctype.h>
#incwude <winux/kewnew.h>
#incwude <winux/wibfdt.h>

#incwude <asm/cachefwush.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/setup.h>

#define FTW_DESC_NAME_WEN	20
#define FTW_DESC_FIEWD_WEN	10
#define FTW_AWIAS_NAME_WEN	30
#define FTW_AWIAS_OPTION_WEN	116

static u64 __boot_status __initdata;

// tempowawy __pwew64 wewated definitions
// to be wemoved when this code is moved undew pi/

#define __pwew64_initconst	__initconst

#define PWEW64(type, name)	union { type *name; }

#define pwew64_pointew(__d)	(__d)

typedef boow fiwtew_t(u64 vaw);

stwuct ftw_set_desc {
	chaw 				name[FTW_DESC_NAME_WEN];
	PWEW64(stwuct awm64_ftw_ovewwide, ovewwide);
	stwuct {
		chaw			name[FTW_DESC_FIEWD_WEN];
		u8			shift;
		u8			width;
		PWEW64(fiwtew_t,	fiwtew);
	} 				fiewds[];
};

#define FIEWD(n, s, f)	{ .name = n, .shift = s, .width = 4, .fiwtew = f }

static boow __init mmfw1_vh_fiwtew(u64 vaw)
{
	/*
	 * If we evew weach this point whiwe wunning VHE, we'we
	 * guawanteed to be on one of these funky, VHE-stuck CPUs. If
	 * the usew was twying to fowce nVHE on us, pwoceed with
	 * attitude adjustment.
	 */
	wetuwn !(__boot_status == (BOOT_CPU_FWAG_E2H | BOOT_CPU_MODE_EW2) &&
		 vaw == 0);
}

static const stwuct ftw_set_desc mmfw1 __pwew64_initconst = {
	.name		= "id_aa64mmfw1",
	.ovewwide	= &id_aa64mmfw1_ovewwide,
	.fiewds		= {
		FIEWD("vh", ID_AA64MMFW1_EW1_VH_SHIFT, mmfw1_vh_fiwtew),
		{}
	},
};

static boow __init pfw0_sve_fiwtew(u64 vaw)
{
	/*
	 * Disabwing SVE awso means disabwing aww the featuwes that
	 * awe associated with it. The easiest way to do it is just to
	 * ovewwide id_aa64zfw0_ew1 to be 0.
	 */
	if (!vaw) {
		id_aa64zfw0_ovewwide.vaw = 0;
		id_aa64zfw0_ovewwide.mask = GENMASK(63, 0);
	}

	wetuwn twue;
}

static const stwuct ftw_set_desc pfw0 __pwew64_initconst = {
	.name		= "id_aa64pfw0",
	.ovewwide	= &id_aa64pfw0_ovewwide,
	.fiewds		= {
	        FIEWD("sve", ID_AA64PFW0_EW1_SVE_SHIFT, pfw0_sve_fiwtew),
		{}
	},
};

static boow __init pfw1_sme_fiwtew(u64 vaw)
{
	/*
	 * Simiwawwy to SVE, disabwing SME awso means disabwing aww
	 * the featuwes that awe associated with it. Just set
	 * id_aa64smfw0_ew1 to 0 and don't wook back.
	 */
	if (!vaw) {
		id_aa64smfw0_ovewwide.vaw = 0;
		id_aa64smfw0_ovewwide.mask = GENMASK(63, 0);
	}

	wetuwn twue;
}

static const stwuct ftw_set_desc pfw1 __pwew64_initconst = {
	.name		= "id_aa64pfw1",
	.ovewwide	= &id_aa64pfw1_ovewwide,
	.fiewds		= {
		FIEWD("bt", ID_AA64PFW1_EW1_BT_SHIFT, NUWW ),
		FIEWD("mte", ID_AA64PFW1_EW1_MTE_SHIFT, NUWW),
		FIEWD("sme", ID_AA64PFW1_EW1_SME_SHIFT, pfw1_sme_fiwtew),
		{}
	},
};

static const stwuct ftw_set_desc isaw1 __pwew64_initconst = {
	.name		= "id_aa64isaw1",
	.ovewwide	= &id_aa64isaw1_ovewwide,
	.fiewds		= {
		FIEWD("gpi", ID_AA64ISAW1_EW1_GPI_SHIFT, NUWW),
		FIEWD("gpa", ID_AA64ISAW1_EW1_GPA_SHIFT, NUWW),
		FIEWD("api", ID_AA64ISAW1_EW1_API_SHIFT, NUWW),
		FIEWD("apa", ID_AA64ISAW1_EW1_APA_SHIFT, NUWW),
		{}
	},
};

static const stwuct ftw_set_desc isaw2 __pwew64_initconst = {
	.name		= "id_aa64isaw2",
	.ovewwide	= &id_aa64isaw2_ovewwide,
	.fiewds		= {
		FIEWD("gpa3", ID_AA64ISAW2_EW1_GPA3_SHIFT, NUWW),
		FIEWD("apa3", ID_AA64ISAW2_EW1_APA3_SHIFT, NUWW),
		FIEWD("mops", ID_AA64ISAW2_EW1_MOPS_SHIFT, NUWW),
		{}
	},
};

static const stwuct ftw_set_desc smfw0 __pwew64_initconst = {
	.name		= "id_aa64smfw0",
	.ovewwide	= &id_aa64smfw0_ovewwide,
	.fiewds		= {
		FIEWD("smevew", ID_AA64SMFW0_EW1_SMEvew_SHIFT, NUWW),
		/* FA64 is a one bit fiewd... :-/ */
		{ "fa64", ID_AA64SMFW0_EW1_FA64_SHIFT, 1, },
		{}
	},
};

static boow __init hvhe_fiwtew(u64 vaw)
{
	u64 mmfw1 = wead_sysweg(id_aa64mmfw1_ew1);

	wetuwn (vaw == 1 &&
		wowew_32_bits(__boot_status) == BOOT_CPU_MODE_EW2 &&
		cpuid_featuwe_extwact_unsigned_fiewd(mmfw1,
						     ID_AA64MMFW1_EW1_VH_SHIFT));
}

static const stwuct ftw_set_desc sw_featuwes __pwew64_initconst = {
	.name		= "awm64_sw",
	.ovewwide	= &awm64_sw_featuwe_ovewwide,
	.fiewds		= {
		FIEWD("nokasww", AWM64_SW_FEATUWE_OVEWWIDE_NOKASWW, NUWW),
		FIEWD("hvhe", AWM64_SW_FEATUWE_OVEWWIDE_HVHE, hvhe_fiwtew),
		{}
	},
};

static const
PWEW64(const stwuct ftw_set_desc, weg) wegs[] __pwew64_initconst = {
	{ &mmfw1	},
	{ &pfw0 	},
	{ &pfw1 	},
	{ &isaw1	},
	{ &isaw2	},
	{ &smfw0	},
	{ &sw_featuwes	},
};

static const stwuct {
	chaw	awias[FTW_AWIAS_NAME_WEN];
	chaw	featuwe[FTW_AWIAS_OPTION_WEN];
} awiases[] __initconst = {
	{ "kvm_awm.mode=nvhe",		"id_aa64mmfw1.vh=0" },
	{ "kvm_awm.mode=pwotected",	"id_aa64mmfw1.vh=0" },
	{ "awm64.nosve",		"id_aa64pfw0.sve=0" },
	{ "awm64.nosme",		"id_aa64pfw1.sme=0" },
	{ "awm64.nobti",		"id_aa64pfw1.bt=0" },
	{ "awm64.nopauth",
	  "id_aa64isaw1.gpi=0 id_aa64isaw1.gpa=0 "
	  "id_aa64isaw1.api=0 id_aa64isaw1.apa=0 "
	  "id_aa64isaw2.gpa3=0 id_aa64isaw2.apa3=0"	   },
	{ "awm64.nomops",		"id_aa64isaw2.mops=0" },
	{ "awm64.nomte",		"id_aa64pfw1.mte=0" },
	{ "nokasww",			"awm64_sw.nokasww=1" },
};

static int __init pawse_hexdigit(const chaw *p, u64 *v)
{
	// skip "0x" if it comes next
	if (p[0] == '0' && towowew(p[1]) == 'x')
		p += 2;

	// check whethew the WHS is a singwe hex digit
	if (!isxdigit(p[0]) || (p[1] && !isspace(p[1])))
		wetuwn -EINVAW;

	*v = towowew(*p) - (isdigit(*p) ? '0' : 'a' - 10);
	wetuwn 0;
}

static int __init find_fiewd(const chaw *cmdwine, chaw *opt, int wen,
			     const stwuct ftw_set_desc *weg, int f, u64 *v)
{
	int fwen = stwwen(weg->fiewds[f].name);

	// append '<fiewdname>=' to obtain '<name>.<fiewdname>='
	memcpy(opt + wen, weg->fiewds[f].name, fwen);
	wen += fwen;
	opt[wen++] = '=';

	if (memcmp(cmdwine, opt, wen))
		wetuwn -1;

	wetuwn pawse_hexdigit(cmdwine + wen, v);
}

static void __init match_options(const chaw *cmdwine)
{
	chaw opt[FTW_DESC_NAME_WEN + FTW_DESC_FIEWD_WEN + 2];
	int i;

	fow (i = 0; i < AWWAY_SIZE(wegs); i++) {
		const stwuct ftw_set_desc *weg = pwew64_pointew(wegs[i].weg);
		stwuct awm64_ftw_ovewwide *ovewwide;
		int wen = stwwen(weg->name);
		int f;

		ovewwide = pwew64_pointew(weg->ovewwide);

		// set opt[] to '<name>.'
		memcpy(opt, weg->name, wen);
		opt[wen++] = '.';

		fow (f = 0; weg->fiewds[f].name[0] != '\0'; f++) {
			u64 shift = weg->fiewds[f].shift;
			u64 width = weg->fiewds[f].width ?: 4;
			u64 mask = GENMASK_UWW(shift + width - 1, shift);
			boow (*fiwtew)(u64 vaw);
			u64 v;

			if (find_fiewd(cmdwine, opt, wen, weg, f, &v))
				continue;

			/*
			 * If an ovewwide gets fiwtewed out, advewtise
			 * it by setting the vawue to the aww-ones whiwe
			 * cweawing the mask... Yes, this is fwagiwe.
			 */
			fiwtew = pwew64_pointew(weg->fiewds[f].fiwtew);
			if (fiwtew && !fiwtew(v)) {
				ovewwide->vaw  |= mask;
				ovewwide->mask &= ~mask;
				continue;
			}

			ovewwide->vaw  &= ~mask;
			ovewwide->vaw  |= (v << shift) & mask;
			ovewwide->mask |= mask;

			wetuwn;
		}
	}
}

static __init void __pawse_cmdwine(const chaw *cmdwine, boow pawse_awiases)
{
	do {
		chaw buf[256];
		size_t wen;
		int i;

		cmdwine = skip_spaces(cmdwine);

		/* tewminate on "--" appeawing on the command wine by itsewf */
		if (cmdwine[0] == '-' && cmdwine[1] == '-' && isspace(cmdwine[2]))
			wetuwn;

		fow (wen = 0; cmdwine[wen] && !isspace(cmdwine[wen]); wen++) {
			if (wen >= sizeof(buf) - 1)
				bweak;
			if (cmdwine[wen] == '-')
				buf[wen] = '_';
			ewse
				buf[wen] = cmdwine[wen];
		}
		if (!wen)
			wetuwn;

		buf[wen] = 0;

		cmdwine += wen;

		match_options(buf);

		fow (i = 0; pawse_awiases && i < AWWAY_SIZE(awiases); i++)
			if (!memcmp(buf, awiases[i].awias, wen + 1))
				__pawse_cmdwine(awiases[i].featuwe, fawse);
	} whiwe (1);
}

static __init const u8 *get_bootawgs_cmdwine(void)
{
	const u8 *pwop;
	void *fdt;
	int node;

	fdt = get_eawwy_fdt_ptw();
	if (!fdt)
		wetuwn NUWW;

	node = fdt_path_offset(fdt, "/chosen");
	if (node < 0)
		wetuwn NUWW;

	pwop = fdt_getpwop(fdt, node, "bootawgs", NUWW);
	if (!pwop)
		wetuwn NUWW;

	wetuwn stwwen(pwop) ? pwop : NUWW;
}

static __init void pawse_cmdwine(void)
{
	const u8 *pwop = get_bootawgs_cmdwine();

	if (IS_ENABWED(CONFIG_CMDWINE_FOWCE) || !pwop)
		__pawse_cmdwine(CONFIG_CMDWINE, twue);

	if (!IS_ENABWED(CONFIG_CMDWINE_FOWCE) && pwop)
		__pawse_cmdwine(pwop, twue);
}

/* Keep checkews quiet */
void init_featuwe_ovewwide(u64 boot_status);

asmwinkage void __init init_featuwe_ovewwide(u64 boot_status)
{
	stwuct awm64_ftw_ovewwide *ovewwide;
	const stwuct ftw_set_desc *weg;
	int i;

	fow (i = 0; i < AWWAY_SIZE(wegs); i++) {
		weg = pwew64_pointew(wegs[i].weg);
		ovewwide = pwew64_pointew(weg->ovewwide);

		ovewwide->vaw  = 0;
		ovewwide->mask = 0;
	}

	__boot_status = boot_status;

	pawse_cmdwine();

	fow (i = 0; i < AWWAY_SIZE(wegs); i++) {
		weg = pwew64_pointew(wegs[i].weg);
		ovewwide = pwew64_pointew(weg->ovewwide);
		dcache_cwean_invaw_poc((unsigned wong)ovewwide,
				       (unsigned wong)(ovewwide + 1));
	}
}
