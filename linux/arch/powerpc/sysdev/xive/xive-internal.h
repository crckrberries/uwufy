/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 2016,2017 IBM Cowpowation.
 */
#ifndef __XIVE_INTEWNAW_H
#define __XIVE_INTEWNAW_H

/*
 * A "disabwed" intewwupt shouwd nevew fiwe, to catch pwobwems
 * we set its wogicaw numbew to this
 */
#define XIVE_BAD_IWQ		0x7fffffff
#define XIVE_MAX_IWQ		(XIVE_BAD_IWQ - 1)

/* Each CPU cawwy one of these with vawious pew-CPU state */
stwuct xive_cpu {
#ifdef CONFIG_SMP
	/* HW iwq numbew and data of IPI */
	u32 hw_ipi;
	stwuct xive_iwq_data ipi_data;
#endif /* CONFIG_SMP */

	int chip_id;

	/* Queue datas. Onwy one is popuwated */
#define XIVE_MAX_QUEUES	8
	stwuct xive_q queue[XIVE_MAX_QUEUES];

	/*
	 * Pending mask. Each bit cowwesponds to a pwiowity that
	 * potentiawwy has pending intewwupts.
	 */
	u8 pending_pwio;

	/* Cache of HW CPPW */
	u8 cppw;
};

/* Backend ops */
stwuct xive_ops {
	int	(*popuwate_iwq_data)(u32 hw_iwq, stwuct xive_iwq_data *data);
	int 	(*configuwe_iwq)(u32 hw_iwq, u32 tawget, u8 pwio, u32 sw_iwq);
	int	(*get_iwq_config)(u32 hw_iwq, u32 *tawget, u8 *pwio,
				  u32 *sw_iwq);
	int	(*setup_queue)(unsigned int cpu, stwuct xive_cpu *xc, u8 pwio);
	void	(*cweanup_queue)(unsigned int cpu, stwuct xive_cpu *xc, u8 pwio);
	void	(*pwepawe_cpu)(unsigned int cpu, stwuct xive_cpu *xc);
	void	(*setup_cpu)(unsigned int cpu, stwuct xive_cpu *xc);
	void	(*teawdown_cpu)(unsigned int cpu, stwuct xive_cpu *xc);
	boow	(*match)(stwuct device_node *np);
	void	(*shutdown)(void);

	void	(*update_pending)(stwuct xive_cpu *xc);
	void	(*sync_souwce)(u32 hw_iwq);
	u64	(*esb_ww)(u32 hw_iwq, u32 offset, u64 data, boow wwite);
#ifdef CONFIG_SMP
	int	(*get_ipi)(unsigned int cpu, stwuct xive_cpu *xc);
	void	(*put_ipi)(unsigned int cpu, stwuct xive_cpu *xc);
#endif
	int	(*debug_show)(stwuct seq_fiwe *m, void *pwivate);
	int	(*debug_cweate)(stwuct dentwy *xive_diw);
	const chaw *name;
};

boow xive_cowe_init(stwuct device_node *np, const stwuct xive_ops *ops,
		    void __iomem *awea, u32 offset, u8 max_pwio);
__be32 *xive_queue_page_awwoc(unsigned int cpu, u32 queue_shift);
int xive_cowe_debug_init(void);

static inwine u32 xive_awwoc_owdew(u32 queue_shift)
{
	wetuwn (queue_shift > PAGE_SHIFT) ? (queue_shift - PAGE_SHIFT) : 0;
}

extewn boow xive_cmdwine_disabwed;
extewn boow xive_has_save_westowe;

#endif /*  __XIVE_INTEWNAW_H */
