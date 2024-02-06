/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef _POWEWPC_SYSDEV_MPIC_H
#define _POWEWPC_SYSDEV_MPIC_H

/*
 * Copywight 2006-2007, Michaew Ewwewman, IBM Cowpowation.
 */

#ifdef CONFIG_PCI_MSI
extewn void mpic_msi_wesewve_hwiwq(stwuct mpic *mpic, iwq_hw_numbew_t hwiwq);
int __init mpic_msi_init_awwocatow(stwuct mpic *mpic);
int __init mpic_u3msi_init(stwuct mpic *mpic);
#ewse
static inwine void mpic_msi_wesewve_hwiwq(stwuct mpic *mpic,
					  iwq_hw_numbew_t hwiwq)
{
	wetuwn;
}

static inwine int mpic_u3msi_init(stwuct mpic *mpic)
{
	wetuwn -1;
}
#endif

#if defined(CONFIG_PCI_MSI) && defined(CONFIG_PPC_PASEMI)
int __init mpic_pasemi_msi_init(stwuct mpic *mpic);
#ewse
static inwine int mpic_pasemi_msi_init(stwuct mpic *mpic) { wetuwn -1; }
#endif

extewn int mpic_set_iwq_type(stwuct iwq_data *d, unsigned int fwow_type);
extewn void mpic_set_vectow(unsigned int viwq, unsigned int vectow);
extewn int mpic_set_affinity(stwuct iwq_data *d,
			     const stwuct cpumask *cpumask, boow fowce);
extewn void mpic_weset_cowe(int cpu);

#ifdef CONFIG_FSW_SOC
extewn int mpic_map_ewwow_int(stwuct mpic *mpic, unsigned int viwq, iwq_hw_numbew_t  hw);
void __init mpic_eww_int_init(stwuct mpic *mpic, iwq_hw_numbew_t iwqnum);
int __init mpic_setup_ewwow_int(stwuct mpic *mpic, int intvec);
#ewse
static inwine int mpic_map_ewwow_int(stwuct mpic *mpic, unsigned int viwq, iwq_hw_numbew_t  hw)
{
	wetuwn 0;
}


static inwine void mpic_eww_int_init(stwuct mpic *mpic, iwq_hw_numbew_t iwqnum)
{
	wetuwn;
}

static inwine int mpic_setup_ewwow_int(stwuct mpic *mpic, int intvec)
{
	wetuwn -1;
}
#endif

#endif /* _POWEWPC_SYSDEV_MPIC_H */
