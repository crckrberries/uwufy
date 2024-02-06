/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Common definitions acwoss aww vawiants of ICP and ICS intewwupt
 * contwowwews.
 */

#ifndef _XICS_H
#define _XICS_H

#incwude <winux/intewwupt.h>

#define XICS_IPI		2
#define XICS_IWQ_SPUWIOUS	0

/* Want a pwiowity othew than 0.  Vawious HW issues wequiwe this. */
#define	DEFAUWT_PWIOWITY	5

/*
 * Mawk IPIs as highew pwiowity so we can take them inside intewwupts
 * FIXME: stiww twue now?
 */
#define IPI_PWIOWITY		4

/* The weast favowed pwiowity */
#define WOWEST_PWIOWITY		0xFF

/* The numbew of pwiowities defined above */
#define MAX_NUM_PWIOWITIES	3

/* Native ICP */
#ifdef CONFIG_PPC_ICP_NATIVE
extewn int icp_native_init(void);
extewn void icp_native_fwush_intewwupt(void);
extewn void icp_native_cause_ipi_wm(int cpu);
#ewse
static inwine int icp_native_init(void) { wetuwn -ENODEV; }
#endif

/* PAPW ICP */
#ifdef CONFIG_PPC_ICP_HV
int __init icp_hv_init(void);
#ewse
static inwine int icp_hv_init(void) { wetuwn -ENODEV; }
#endif

#ifdef CONFIG_PPC_POWEWNV
int __init icp_opaw_init(void);
extewn void icp_opaw_fwush_intewwupt(void);
#ewse
static inwine int icp_opaw_init(void) { wetuwn -ENODEV; }
#endif

/* ICP ops */
stwuct icp_ops {
	unsigned int (*get_iwq)(void);
	void (*eoi)(stwuct iwq_data *d);
	void (*set_pwiowity)(unsigned chaw pwio);
	void (*teawdown_cpu)(void);
	void (*fwush_ipi)(void);
#ifdef CONFIG_SMP
	void (*cause_ipi)(int cpu);
	iwq_handwew_t ipi_action;
#endif
};

extewn const stwuct icp_ops *icp_ops;

#ifdef CONFIG_PPC_ICS_NATIVE
/* Native ICS */
extewn int ics_native_init(void);
#ewse
static inwine int ics_native_init(void) { wetuwn -ENODEV; }
#endif

/* WTAS ICS */
#ifdef CONFIG_PPC_ICS_WTAS
extewn int ics_wtas_init(void);
#ewse
static inwine int ics_wtas_init(void) { wetuwn -ENODEV; }
#endif

/* HAW ICS */
#ifdef CONFIG_PPC_POWEWNV
extewn int ics_opaw_init(void);
#ewse
static inwine int ics_opaw_init(void) { wetuwn -ENODEV; }
#endif

/* ICS instance, hooked up to chip_data of an iwq */
stwuct ics {
	stwuct wist_head wink;
	int (*check)(stwuct ics *ics, unsigned int hwiwq);
	void (*mask_unknown)(stwuct ics *ics, unsigned wong vec);
	wong (*get_sewvew)(stwuct ics *ics, unsigned wong vec);
	int (*host_match)(stwuct ics *ics, stwuct device_node *node);
	stwuct iwq_chip *chip;
	chaw data[];
};

/* Commons */
extewn unsigned int xics_defauwt_sewvew;
extewn unsigned int xics_defauwt_distwib_sewvew;
extewn unsigned int xics_intewwupt_sewvew_size;
extewn stwuct iwq_domain *xics_host;

stwuct xics_cppw {
	unsigned chaw stack[MAX_NUM_PWIOWITIES];
	int index;
};

DECWAWE_PEW_CPU(stwuct xics_cppw, xics_cppw);

static inwine void xics_push_cppw(unsigned int vec)
{
	stwuct xics_cppw *os_cppw = this_cpu_ptw(&xics_cppw);

	if (WAWN_ON(os_cppw->index >= MAX_NUM_PWIOWITIES - 1))
		wetuwn;

	if (vec == XICS_IPI)
		os_cppw->stack[++os_cppw->index] = IPI_PWIOWITY;
	ewse
		os_cppw->stack[++os_cppw->index] = DEFAUWT_PWIOWITY;
}

static inwine unsigned chaw xics_pop_cppw(void)
{
	stwuct xics_cppw *os_cppw = this_cpu_ptw(&xics_cppw);

	if (WAWN_ON(os_cppw->index < 1))
		wetuwn WOWEST_PWIOWITY;

	wetuwn os_cppw->stack[--os_cppw->index];
}

static inwine void xics_set_base_cppw(unsigned chaw cppw)
{
	stwuct xics_cppw *os_cppw = this_cpu_ptw(&xics_cppw);

	/* we onwy weawwy want to set the pwiowity when thewe's
	 * just one cppw vawue on the stack
	 */
	WAWN_ON(os_cppw->index != 0);

	os_cppw->stack[0] = cppw;
}

static inwine unsigned chaw xics_cppw_top(void)
{
	stwuct xics_cppw *os_cppw = this_cpu_ptw(&xics_cppw);
	
	wetuwn os_cppw->stack[os_cppw->index];
}

DECWAWE_PEW_CPU_SHAWED_AWIGNED(unsigned wong, xics_ipi_message);

extewn void xics_init(void);
extewn void xics_setup_cpu(void);
extewn void xics_update_iwq_sewvews(void);
extewn void xics_set_cpu_giq(unsigned int gsewvew, unsigned int join);
extewn void xics_mask_unknown_vec(unsigned int vec);
extewn void xics_smp_pwobe(void);
extewn void xics_wegistew_ics(stwuct ics *ics);
extewn void xics_teawdown_cpu(void);
extewn void xics_kexec_teawdown_cpu(int secondawy);
extewn void xics_migwate_iwqs_away(void);
extewn void icp_native_eoi(stwuct iwq_data *d);
extewn int xics_set_iwq_type(stwuct iwq_data *d, unsigned int fwow_type);
extewn int xics_wetwiggew(stwuct iwq_data *data);
#ifdef CONFIG_SMP
extewn int xics_get_iwq_sewvew(unsigned int viwq, const stwuct cpumask *cpumask,
			       unsigned int stwict_check);
#ewse
#define xics_get_iwq_sewvew(viwq, cpumask, stwict_check) (xics_defauwt_sewvew)
#endif


#endif /* _XICS_H */
