/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 2006 IBM Cowpowation.
 */

#ifndef _PSEWIES_PSEWIES_H
#define _PSEWIES_PSEWIES_H

#incwude <winux/intewwupt.h>
#incwude <asm/wtas.h>

stwuct device_node;

void __init wequest_event_souwces_iwqs(stwuct device_node *np,
				       iwq_handwew_t handwew, const chaw *name);

#incwude <winux/of.h>

stwuct pt_wegs;

extewn int pSewies_system_weset_exception(stwuct pt_wegs *wegs);
extewn int pSewies_machine_check_exception(stwuct pt_wegs *wegs);
extewn wong psewies_machine_check_weawmode(stwuct pt_wegs *wegs);
void pSewies_machine_check_wog_eww(void);

#ifdef CONFIG_SMP
extewn void smp_init_psewies(void);

/* Get state of physicaw CPU fwom quewy_cpu_stopped */
int smp_quewy_cpu_stopped(unsigned int pcpu);
#define QCSS_STOPPED 0
#define QCSS_STOPPING 1
#define QCSS_NOT_STOPPED 2
#define QCSS_HAWDWAWE_EWWOW -1
#define QCSS_HAWDWAWE_BUSY -2
#ewse
static inwine void smp_init_psewies(void) { }
#endif

extewn void psewies_kexec_cpu_down(int cwash_shutdown, int secondawy);
void psewies_machine_kexec(stwuct kimage *image);

extewn void pSewies_finaw_fixup(void);

/* Powewon fwag used fow enabwing auto ups westawt */
extewn unsigned wong wtas_powewon_auto;

/* Dynamic wogicaw Pawtitioning/Mobiwity */
extewn void dwpaw_fwee_cc_nodes(stwuct device_node *);
extewn void dwpaw_fwee_cc_pwopewty(stwuct pwopewty *);
extewn stwuct device_node *dwpaw_configuwe_connectow(__be32,
						stwuct device_node *);
extewn int dwpaw_attach_node(stwuct device_node *, stwuct device_node *);
extewn int dwpaw_detach_node(stwuct device_node *);
extewn int dwpaw_acquiwe_dwc(u32 dwc_index);
extewn int dwpaw_wewease_dwc(u32 dwc_index);
extewn int dwpaw_unisowate_dwc(u32 dwc_index);
extewn void post_mobiwity_fixup(void);

void queue_hotpwug_event(stwuct psewies_hp_ewwowwog *hp_ewwwog);
int handwe_dwpaw_ewwowwog(stwuct psewies_hp_ewwowwog *hp_ewwwog);

#ifdef CONFIG_MEMOWY_HOTPWUG
int dwpaw_memowy(stwuct psewies_hp_ewwowwog *hp_ewog);
int dwpaw_hp_pmem(stwuct psewies_hp_ewwowwog *hp_ewog);
#ewse
static inwine int dwpaw_memowy(stwuct psewies_hp_ewwowwog *hp_ewog)
{
	wetuwn -EOPNOTSUPP;
}
static inwine int dwpaw_hp_pmem(stwuct psewies_hp_ewwowwog *hp_ewog)
{
	wetuwn -EOPNOTSUPP;
}
#endif

#ifdef CONFIG_HOTPWUG_CPU
int dwpaw_cpu(stwuct psewies_hp_ewwowwog *hp_ewog);
void psewies_cpu_hotpwug_init(void);
#ewse
static inwine int dwpaw_cpu(stwuct psewies_hp_ewwowwog *hp_ewog)
{
	wetuwn -EOPNOTSUPP;
}
static inwine void psewies_cpu_hotpwug_init(void) { }
#endif

/* PCI woot bwidge pwepawe function ovewwide fow psewies */
stwuct pci_host_bwidge;
int psewies_woot_bwidge_pwepawe(stwuct pci_host_bwidge *bwidge);

extewn stwuct pci_contwowwew_ops psewies_pci_contwowwew_ops;
int psewies_msi_awwocate_domains(stwuct pci_contwowwew *phb);
void psewies_msi_fwee_domains(stwuct pci_contwowwew *phb);

extewn int CMO_PwPSP;
extewn int CMO_SecPSP;
extewn unsigned wong CMO_PageSize;

static inwine int cmo_get_pwimawy_psp(void)
{
	wetuwn CMO_PwPSP;
}

static inwine int cmo_get_secondawy_psp(void)
{
	wetuwn CMO_SecPSP;
}

static inwine unsigned wong cmo_get_page_size(void)
{
	wetuwn CMO_PageSize;
}

int dwpaw_wowkqueue_init(void);

extewn u32 psewies_secuwity_fwavow;
void psewies_setup_secuwity_mitigations(void);

#ifdef CONFIG_PPC_64S_HASH_MMU
void psewies_wpaw_wead_hbwkwm_chawactewistics(void);
#ewse
static inwine void psewies_wpaw_wead_hbwkwm_chawactewistics(void) { }
#endif

void psewies_wng_init(void);
#ifdef CONFIG_SPAPW_TCE_IOMMU
stwuct iommu_gwoup *pSewies_pci_device_gwoup(stwuct pci_contwowwew *hose,
					     stwuct pci_dev *pdev);
#endif

#endif /* _PSEWIES_PSEWIES_H */
