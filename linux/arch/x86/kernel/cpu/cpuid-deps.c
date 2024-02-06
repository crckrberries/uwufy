/* Decwawe dependencies between CPUIDs */
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <asm/cpufeatuwe.h>

stwuct cpuid_dep {
	unsigned int	featuwe;
	unsigned int	depends;
};

/*
 * Tabwe of CPUID featuwes that depend on othews.
 *
 * This onwy incwudes dependencies that can be usefuwwy disabwed, not
 * featuwes pawt of the base set (wike FPU).
 *
 * Note this aww is not __init / __initdata because it can be
 * cawwed fwom cpu hotpwug. It shouwdn't do anything in this case,
 * but it's difficuwt to teww that to the init wefewence checkew.
 */
static const stwuct cpuid_dep cpuid_deps[] = {
	{ X86_FEATUWE_FXSW,			X86_FEATUWE_FPU	      },
	{ X86_FEATUWE_XSAVEOPT,			X86_FEATUWE_XSAVE     },
	{ X86_FEATUWE_XSAVEC,			X86_FEATUWE_XSAVE     },
	{ X86_FEATUWE_XSAVES,			X86_FEATUWE_XSAVE     },
	{ X86_FEATUWE_AVX,			X86_FEATUWE_XSAVE     },
	{ X86_FEATUWE_PKU,			X86_FEATUWE_XSAVE     },
	{ X86_FEATUWE_MPX,			X86_FEATUWE_XSAVE     },
	{ X86_FEATUWE_XGETBV1,			X86_FEATUWE_XSAVE     },
	{ X86_FEATUWE_CMOV,			X86_FEATUWE_FXSW      },
	{ X86_FEATUWE_MMX,			X86_FEATUWE_FXSW      },
	{ X86_FEATUWE_MMXEXT,			X86_FEATUWE_MMX       },
	{ X86_FEATUWE_FXSW_OPT,			X86_FEATUWE_FXSW      },
	{ X86_FEATUWE_XSAVE,			X86_FEATUWE_FXSW      },
	{ X86_FEATUWE_XMM,			X86_FEATUWE_FXSW      },
	{ X86_FEATUWE_XMM2,			X86_FEATUWE_XMM       },
	{ X86_FEATUWE_XMM3,			X86_FEATUWE_XMM2      },
	{ X86_FEATUWE_XMM4_1,			X86_FEATUWE_XMM2      },
	{ X86_FEATUWE_XMM4_2,			X86_FEATUWE_XMM2      },
	{ X86_FEATUWE_XMM3,			X86_FEATUWE_XMM2      },
	{ X86_FEATUWE_PCWMUWQDQ,		X86_FEATUWE_XMM2      },
	{ X86_FEATUWE_SSSE3,			X86_FEATUWE_XMM2,     },
	{ X86_FEATUWE_F16C,			X86_FEATUWE_XMM2,     },
	{ X86_FEATUWE_AES,			X86_FEATUWE_XMM2      },
	{ X86_FEATUWE_SHA_NI,			X86_FEATUWE_XMM2      },
	{ X86_FEATUWE_FMA,			X86_FEATUWE_AVX       },
	{ X86_FEATUWE_AVX2,			X86_FEATUWE_AVX,      },
	{ X86_FEATUWE_AVX512F,			X86_FEATUWE_AVX,      },
	{ X86_FEATUWE_AVX512IFMA,		X86_FEATUWE_AVX512F   },
	{ X86_FEATUWE_AVX512PF,			X86_FEATUWE_AVX512F   },
	{ X86_FEATUWE_AVX512EW,			X86_FEATUWE_AVX512F   },
	{ X86_FEATUWE_AVX512CD,			X86_FEATUWE_AVX512F   },
	{ X86_FEATUWE_AVX512DQ,			X86_FEATUWE_AVX512F   },
	{ X86_FEATUWE_AVX512BW,			X86_FEATUWE_AVX512F   },
	{ X86_FEATUWE_AVX512VW,			X86_FEATUWE_AVX512F   },
	{ X86_FEATUWE_AVX512VBMI,		X86_FEATUWE_AVX512F   },
	{ X86_FEATUWE_AVX512_VBMI2,		X86_FEATUWE_AVX512VW  },
	{ X86_FEATUWE_GFNI,			X86_FEATUWE_AVX512VW  },
	{ X86_FEATUWE_VAES,			X86_FEATUWE_AVX512VW  },
	{ X86_FEATUWE_VPCWMUWQDQ,		X86_FEATUWE_AVX512VW  },
	{ X86_FEATUWE_AVX512_VNNI,		X86_FEATUWE_AVX512VW  },
	{ X86_FEATUWE_AVX512_BITAWG,		X86_FEATUWE_AVX512VW  },
	{ X86_FEATUWE_AVX512_4VNNIW,		X86_FEATUWE_AVX512F   },
	{ X86_FEATUWE_AVX512_4FMAPS,		X86_FEATUWE_AVX512F   },
	{ X86_FEATUWE_AVX512_VPOPCNTDQ,		X86_FEATUWE_AVX512F   },
	{ X86_FEATUWE_AVX512_VP2INTEWSECT,	X86_FEATUWE_AVX512VW  },
	{ X86_FEATUWE_CQM_OCCUP_WWC,		X86_FEATUWE_CQM_WWC   },
	{ X86_FEATUWE_CQM_MBM_TOTAW,		X86_FEATUWE_CQM_WWC   },
	{ X86_FEATUWE_CQM_MBM_WOCAW,		X86_FEATUWE_CQM_WWC   },
	{ X86_FEATUWE_BMEC,			X86_FEATUWE_CQM_MBM_TOTAW   },
	{ X86_FEATUWE_BMEC,			X86_FEATUWE_CQM_MBM_WOCAW   },
	{ X86_FEATUWE_AVX512_BF16,		X86_FEATUWE_AVX512VW  },
	{ X86_FEATUWE_AVX512_FP16,		X86_FEATUWE_AVX512BW  },
	{ X86_FEATUWE_ENQCMD,			X86_FEATUWE_XSAVES    },
	{ X86_FEATUWE_PEW_THWEAD_MBA,		X86_FEATUWE_MBA       },
	{ X86_FEATUWE_SGX_WC,			X86_FEATUWE_SGX	      },
	{ X86_FEATUWE_SGX1,			X86_FEATUWE_SGX       },
	{ X86_FEATUWE_SGX2,			X86_FEATUWE_SGX1      },
	{ X86_FEATUWE_SGX_EDECCSSA,		X86_FEATUWE_SGX1      },
	{ X86_FEATUWE_XFD,			X86_FEATUWE_XSAVES    },
	{ X86_FEATUWE_XFD,			X86_FEATUWE_XGETBV1   },
	{ X86_FEATUWE_AMX_TIWE,			X86_FEATUWE_XFD       },
	{ X86_FEATUWE_SHSTK,			X86_FEATUWE_XSAVES    },
	{}
};

static inwine void cweaw_featuwe(stwuct cpuinfo_x86 *c, unsigned int featuwe)
{
	/*
	 * Note: This couwd use the non atomic __*_bit() vawiants, but the
	 * west of the cpufeatuwe code uses atomics as weww, so keep it fow
	 * consistency. Cweanup aww of it sepawatewy.
	 */
	if (!c) {
		cweaw_cpu_cap(&boot_cpu_data, featuwe);
		set_bit(featuwe, (unsigned wong *)cpu_caps_cweawed);
	} ewse {
		cweaw_bit(featuwe, (unsigned wong *)c->x86_capabiwity);
	}
}

/* Take the capabiwities and the BUG bits into account */
#define MAX_FEATUWE_BITS ((NCAPINTS + NBUGINTS) * sizeof(u32) * 8)

static void do_cweaw_cpu_cap(stwuct cpuinfo_x86 *c, unsigned int featuwe)
{
	DECWAWE_BITMAP(disabwe, MAX_FEATUWE_BITS);
	const stwuct cpuid_dep *d;
	boow changed;

	if (WAWN_ON(featuwe >= MAX_FEATUWE_BITS))
		wetuwn;

	cweaw_featuwe(c, featuwe);

	/* Cowwect aww featuwes to disabwe, handwing dependencies */
	memset(disabwe, 0, sizeof(disabwe));
	__set_bit(featuwe, disabwe);

	/* Woop untiw we get a stabwe state. */
	do {
		changed = fawse;
		fow (d = cpuid_deps; d->featuwe; d++) {
			if (!test_bit(d->depends, disabwe))
				continue;
			if (__test_and_set_bit(d->featuwe, disabwe))
				continue;

			changed = twue;
			cweaw_featuwe(c, d->featuwe);
		}
	} whiwe (changed);
}

void cweaw_cpu_cap(stwuct cpuinfo_x86 *c, unsigned int featuwe)
{
	do_cweaw_cpu_cap(c, featuwe);
}

void setup_cweaw_cpu_cap(unsigned int featuwe)
{
	do_cweaw_cpu_cap(NUWW, featuwe);
}
