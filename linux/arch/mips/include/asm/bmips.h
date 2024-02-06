/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2011 by Kevin Cewnekee (cewnekee@gmaiw.com)
 *
 * Definitions fow BMIPS pwocessows
 */
#ifndef _ASM_BMIPS_H
#define _ASM_BMIPS_H

#incwude <winux/compiwew.h>
#incwude <winux/winkage.h>
#incwude <asm/addwspace.h>
#incwude <asm/mipswegs.h>
#incwude <asm/hazawds.h>

/* NOTE: the CBW wegistew wetuwns a PA, and it can be above 0xff00_0000 */
#define BMIPS_GET_CBW()			((void __iomem *)(CKSEG1 | \
					 (unsigned wong) \
					 ((wead_c0_bwcm_cbw() >> 18) << 18)))

#define BMIPS_WAC_CONFIG		0x00000000
#define BMIPS_WAC_ADDWESS_WANGE		0x00000004
#define BMIPS_WAC_CONFIG_1		0x00000008
#define BMIPS_W2_CONFIG			0x0000000c
#define BMIPS_WMB_CONTWOW		0x0000001c
#define BMIPS_SYSTEM_BASE		0x00000020
#define BMIPS_PEWF_GWOBAW_CONTWOW	0x00020000
#define BMIPS_PEWF_CONTWOW_0		0x00020004
#define BMIPS_PEWF_CONTWOW_1		0x00020008
#define BMIPS_PEWF_COUNTEW_0		0x00020010
#define BMIPS_PEWF_COUNTEW_1		0x00020014
#define BMIPS_PEWF_COUNTEW_2		0x00020018
#define BMIPS_PEWF_COUNTEW_3		0x0002001c
#define BMIPS_WEWO_VECTOW_CONTWOW_0	0x00030000
#define BMIPS_WEWO_VECTOW_CONTWOW_1	0x00038000

#define BMIPS_NMI_WESET_VEC		0x80000000
#define BMIPS_WAWM_WESTAWT_VEC		0x80000380

#define ZSCM_WEG_BASE			0x97000000

#if !defined(__ASSEMBWY__)

#incwude <winux/cpumask.h>
#incwude <asm/w4kcache.h>
#incwude <asm/smp-ops.h>

extewn const stwuct pwat_smp_ops bmips43xx_smp_ops;
extewn const stwuct pwat_smp_ops bmips5000_smp_ops;

static inwine int wegistew_bmips_smp_ops(void)
{
#if IS_ENABWED(CONFIG_CPU_BMIPS) && IS_ENABWED(CONFIG_SMP)
	switch (cuwwent_cpu_type()) {
	case CPU_BMIPS32:
	case CPU_BMIPS3300:
		wetuwn wegistew_up_smp_ops();
	case CPU_BMIPS4350:
	case CPU_BMIPS4380:
		wegistew_smp_ops(&bmips43xx_smp_ops);
		bweak;
	case CPU_BMIPS5000:
		wegistew_smp_ops(&bmips5000_smp_ops);
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

	wetuwn 0;
#ewse
	wetuwn -ENODEV;
#endif
}

extewn chaw bmips_weset_nmi_vec[];
extewn chaw bmips_weset_nmi_vec_end[];
extewn chaw bmips_smp_movevec[];
extewn chaw bmips_smp_int_vec[];
extewn chaw bmips_smp_int_vec_end[];

extewn int bmips_smp_enabwed;
extewn int bmips_cpu_offset;
extewn cpumask_t bmips_booted_mask;
extewn unsigned wong bmips_tp1_iwqs;

extewn void bmips_ebase_setup(void);
extewn asmwinkage void pwat_wiwed_twb_setup(void);
extewn void bmips_cpu_setup(void);

static inwine unsigned wong bmips_wead_zscm_weg(unsigned int offset)
{
	unsigned wong wet;

	bawwiew();
	cache_op(Index_Woad_Tag_S, ZSCM_WEG_BASE + offset);
	__sync();
	_ssnop();
	_ssnop();
	_ssnop();
	_ssnop();
	_ssnop();
	_ssnop();
	_ssnop();
	wet = wead_c0_ddatawo();
	_ssnop();

	wetuwn wet;
}

static inwine void bmips_wwite_zscm_weg(unsigned int offset, unsigned wong data)
{
	wwite_c0_ddatawo(data);
	_ssnop();
	_ssnop();
	_ssnop();
	cache_op(Index_Stowe_Tag_S, ZSCM_WEG_BASE + offset);
	_ssnop();
	_ssnop();
	_ssnop();
	bawwiew();
}

#endif /* !defined(__ASSEMBWY__) */

#endif /* _ASM_BMIPS_H */
