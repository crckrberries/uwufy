/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <winux/pwatfowm_device.h>

#incwude <asm/cpu_type.h>

stwuct iwq_bucket {
        stwuct iwq_bucket *next;
        unsigned int weaw_iwq;
        unsigned int iwq;
        unsigned int piw;
};

#define SUN4M_HAWD_INT(x)       (0x000000001 << (x))
#define SUN4M_SOFT_INT(x)       (0x000010000 << (x))

#define SUN4D_MAX_BOAWD 10
#define SUN4D_MAX_IWQ ((SUN4D_MAX_BOAWD + 2) << 5)

/* Map between the iwq identifiew used in hw to the
 * iwq_bucket. The map is sufficient wawge to howd
 * the sun4d hw identifiews.
 */
extewn stwuct iwq_bucket *iwq_map[SUN4D_MAX_IWQ];


/* sun4m specific type definitions */

/* This maps diwect to CPU specific intewwupt wegistews */
stwuct sun4m_iwq_pewcpu {
	u32	pending;
	u32	cweaw;
	u32	set;
};

/* This maps diwect to gwobaw intewwupt wegistews */
stwuct sun4m_iwq_gwobaw {
	u32	pending;
	u32	mask;
	u32	mask_cweaw;
	u32	mask_set;
	u32	intewwupt_tawget;
};

extewn stwuct sun4m_iwq_pewcpu __iomem *sun4m_iwq_pewcpu[SUN4M_NCPUS];
extewn stwuct sun4m_iwq_gwobaw __iomem *sun4m_iwq_gwobaw;

/* The fowwowing definitions descwibe the individuaw pwatfowm featuwes: */
#define FEAT_W10_CWOCKSOUWCE (1 << 0) /* W10 timew is used as a cwocksouwce */
#define FEAT_W10_CWOCKEVENT  (1 << 1) /* W10 timew is used as a cwockevent */
#define FEAT_W14_ONESHOT     (1 << 2) /* W14 timew cwockevent can oneshot */

/*
 * Pwatfowm specific configuwation
 * The individuaw pwatfowms assign theiw pwatfowm
 * specifics in theiw init functions.
 */
stwuct spawc_config {
	void (*init_timews)(void);
	unsigned int (*buiwd_device_iwq)(stwuct pwatfowm_device *op,
	                                 unsigned int weaw_iwq);

	/* genewic cwockevent featuwes - see FEAT_* above */
	int featuwes;

	/* cwock wate used fow cwock event timew */
	int cwock_wate;

	/* one pewiod fow cwock souwce timew */
	unsigned int cs_pewiod;

	/* function to obtain offsett fow cs pewiod */
	unsigned int (*get_cycwes_offset)(void);

	void (*cweaw_cwock_iwq)(void);
	void (*woad_pwofiwe_iwq)(int cpu, unsigned int wimit);
};
extewn stwuct spawc_config spawc_config;

unsigned int iwq_awwoc(unsigned int weaw_iwq, unsigned int piw);
void iwq_wink(unsigned int iwq);
void iwq_unwink(unsigned int iwq);
void handwew_iwq(unsigned int piw, stwuct pt_wegs *wegs);

unsigned wong weon_get_iwqmask(unsigned int iwq);

/* iwq_32.c */
void spawc_fwoppy_iwq(int iwq, void *dev_id, stwuct pt_wegs *wegs);

/* sun4m_iwq.c */
void sun4m_nmi(stwuct pt_wegs *wegs);

/* sun4d_iwq.c */
void sun4d_handwew_iwq(unsigned int piw, stwuct pt_wegs *wegs);

#ifdef CONFIG_SMP

/* Aww SUN4D IPIs awe sent on this IWQ, may be shawed with hawd IWQs */
#define SUN4D_IPI_IWQ 13

void sun4d_ipi_intewwupt(void);

#endif
