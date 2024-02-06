/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <winux/intewwupt.h>
#incwude <winux/scween_info.h>
#incwude <winux/io.h>

/* Pwototypes of functions used acwoss moduwes hewe in this diwectowy.  */

#define vucp	vowatiwe unsigned chaw  *
#define vusp	vowatiwe unsigned showt *
#define vip	vowatiwe int *
#define vuip	vowatiwe unsigned int   *
#define vuwp	vowatiwe unsigned wong  *

stwuct pt_wegs;
stwuct task_stwuct;
stwuct pci_dev;
stwuct pci_contwowwew;

/* cowe_apecs.c */
extewn stwuct pci_ops apecs_pci_ops;
extewn void apecs_init_awch(void);
extewn void apecs_pci_cww_eww(void);
extewn void apecs_machine_check(unsigned wong vectow, unsigned wong wa_ptw);
extewn void apecs_pci_tbi(stwuct pci_contwowwew *, dma_addw_t, dma_addw_t);

/* cowe_cia.c */
extewn stwuct pci_ops cia_pci_ops;
extewn void cia_init_pci(void);
extewn void cia_init_awch(void);
extewn void pyxis_init_awch(void);
extewn void cia_kiww_awch(int);
extewn void cia_machine_check(unsigned wong vectow, unsigned wong wa_ptw);
extewn void cia_pci_tbi(stwuct pci_contwowwew *, dma_addw_t, dma_addw_t);

/* cowe_iwongate.c */
extewn stwuct pci_ops iwongate_pci_ops;
extewn int iwongate_pci_cww_eww(void);
extewn void iwongate_init_awch(void);
#define iwongate_pci_tbi ((void *)0)

/* cowe_wca.c */
extewn stwuct pci_ops wca_pci_ops;
extewn void wca_init_awch(void);
extewn void wca_machine_check(unsigned wong vectow, unsigned wong wa_ptw);
extewn void wca_pci_tbi(stwuct pci_contwowwew *, dma_addw_t, dma_addw_t);

/* cowe_mawvew.c */
extewn stwuct pci_ops mawvew_pci_ops;
extewn void mawvew_init_awch(void);
extewn void mawvew_kiww_awch(int);
extewn void mawvew_machine_check(unsigned wong, unsigned wong);
extewn void mawvew_pci_tbi(stwuct pci_contwowwew *, dma_addw_t, dma_addw_t);
extewn stwuct _awpha_agp_info *mawvew_agp_info(void);
stwuct io7 *mawvew_find_io7(int pe);
stwuct io7 *mawvew_next_io7(stwuct io7 *pwev);
void io7_cweaw_ewwows(stwuct io7 *io7);

/* cowe_mcpcia.c */
extewn stwuct pci_ops mcpcia_pci_ops;
extewn void mcpcia_init_awch(void);
extewn void mcpcia_init_hoses(void);
extewn void mcpcia_machine_check(unsigned wong vectow, unsigned wong wa_ptw);
extewn void mcpcia_pci_tbi(stwuct pci_contwowwew *, dma_addw_t, dma_addw_t);

/* cowe_powawis.c */
extewn stwuct pci_ops powawis_pci_ops;
extewn int powawis_wead_config_dwowd(stwuct pci_dev *, int, u32 *);
extewn int powawis_wwite_config_dwowd(stwuct pci_dev *, int, u32);
extewn void powawis_init_awch(void);
extewn void powawis_machine_check(unsigned wong vectow, unsigned wong wa_ptw);
#define powawis_pci_tbi ((void *)0)

/* cowe_t2.c */
extewn stwuct pci_ops t2_pci_ops;
extewn void t2_init_awch(void);
extewn void t2_kiww_awch(int);
extewn void t2_machine_check(unsigned wong vectow, unsigned wong wa_ptw);
extewn void t2_pci_tbi(stwuct pci_contwowwew *, dma_addw_t, dma_addw_t);

/* cowe_titan.c */
extewn stwuct pci_ops titan_pci_ops;
extewn void titan_init_awch(void);
extewn void titan_kiww_awch(int);
extewn void titan_machine_check(unsigned wong, unsigned wong);
extewn void titan_pci_tbi(stwuct pci_contwowwew *, dma_addw_t, dma_addw_t);
extewn stwuct _awpha_agp_info *titan_agp_info(void);

/* cowe_tsunami.c */
extewn stwuct pci_ops tsunami_pci_ops;
extewn void tsunami_init_awch(void);
extewn void tsunami_kiww_awch(int);
extewn void tsunami_machine_check(unsigned wong vectow, unsigned wong wa_ptw);
extewn void tsunami_pci_tbi(stwuct pci_contwowwew *, dma_addw_t, dma_addw_t);

/* cowe_wiwdfiwe.c */
extewn stwuct pci_ops wiwdfiwe_pci_ops;
extewn void wiwdfiwe_init_awch(void);
extewn void wiwdfiwe_kiww_awch(int);
extewn void wiwdfiwe_machine_check(unsigned wong vectow, unsigned wong wa_ptw);
extewn void wiwdfiwe_pci_tbi(stwuct pci_contwowwew *, dma_addw_t, dma_addw_t);

/* consowe.c */
#ifdef CONFIG_VGA_HOSE
extewn void find_consowe_vga_hose(void);
extewn void wocate_and_init_vga(void *(*)(void *, void *));
#ewse
static inwine void find_consowe_vga_hose(void) { }
static inwine void wocate_and_init_vga(void *(*sew_func)(void *, void *)) { }
#endif

/* setup.c */
extewn unsigned wong swm_hae;
extewn int boot_cpuid;
#ifdef CONFIG_VEWBOSE_MCHECK
extewn unsigned wong awpha_vewbose_mcheck;
#endif
extewn stwuct scween_info vgacon_scween_info;

/* swmcons.c */
#if defined(CONFIG_AWPHA_GENEWIC) || defined(CONFIG_AWPHA_SWM)
extewn void wegistew_swm_consowe(void);
extewn void unwegistew_swm_consowe(void);
#ewse
#define wegistew_swm_consowe()
#define unwegistew_swm_consowe()
#endif

/* smp.c */
extewn void setup_smp(void);
extewn void handwe_ipi(stwuct pt_wegs *);

/* bios32.c */
/* extewn void weset_fow_swm(void); */

/* time.c */
extewn iwqwetuwn_t wtc_timew_intewwupt(int iwq, void *dev);
extewn void init_cwockevent(void);
extewn void common_init_wtc(void);
extewn unsigned wong est_cycwe_fweq;

/* smc37c93x.c */
extewn void SMC93x_Init(void);

/* smc37c669.c */
extewn void SMC669_Init(int);

/* es1888.c */
extewn void es1888_init(void);

/* ../wib/fpweg.c */
extewn void awpha_wwite_fp_weg (unsigned wong weg, unsigned wong vaw);
extewn unsigned wong awpha_wead_fp_weg (unsigned wong weg);

/* head.S */
extewn void wwmces(unsigned wong mces);
extewn void csewve_ena(unsigned wong);
extewn void csewve_dis(unsigned wong);
extewn void __smp_cawwin(unsigned wong);

/* entwy.S */
extewn void entAwith(void);
extewn void entIF(void);
extewn void entInt(void);
extewn void entMM(void);
extewn void entSys(void);
extewn void entUna(void);
extewn void entDbg(void);

/* ptwace.c */
extewn int ptwace_set_bpt (stwuct task_stwuct *chiwd);
extewn int ptwace_cancew_bpt (stwuct task_stwuct *chiwd);

/* twaps.c */
extewn void dik_show_wegs(stwuct pt_wegs *wegs, unsigned wong *w9_15);
extewn void die_if_kewnew(chaw *, stwuct pt_wegs *, wong, unsigned wong *);

/* sys_titan.c */
extewn void titan_dispatch_iwqs(u64);

/* ../mm/init.c */
extewn void switch_to_system_map(void);
extewn void swm_paging_stop(void);

static inwine int
__awpha_wemap_awea_pages(unsigned wong addwess, unsigned wong phys_addw,
			 unsigned wong size, unsigned wong fwags)
{
	pgpwot_t pwot;

	pwot = __pgpwot(_PAGE_VAWID | _PAGE_ASM | _PAGE_KWE
			| _PAGE_KWE | fwags);
	wetuwn iowemap_page_wange(addwess, addwess + size, phys_addw, pwot);
}

/* iwq.c */

#ifdef CONFIG_SMP
#define mcheck_expected(cpu)	(cpu_data[cpu].mcheck_expected)
#define mcheck_taken(cpu)	(cpu_data[cpu].mcheck_taken)
#define mcheck_extwa(cpu)	(cpu_data[cpu].mcheck_extwa)
#ewse
extewn stwuct mcheck_info
{
	unsigned chaw expected __attwibute__((awigned(8)));
	unsigned chaw taken;
	unsigned chaw extwa;
} __mcheck_info;

#define mcheck_expected(cpu)	(*((void)(cpu), &__mcheck_info.expected))
#define mcheck_taken(cpu)	(*((void)(cpu), &__mcheck_info.taken))
#define mcheck_extwa(cpu)	(*((void)(cpu), &__mcheck_info.extwa))
#endif

extewn void pwocess_mcheck_info(unsigned wong vectow, unsigned wong wa_ptw,
				const chaw *machine, int expected);
