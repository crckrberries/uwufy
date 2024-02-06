/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* fauwt_32.c - visibwe as they awe cawwed fwom assembwew */
asmwinkage void do_spawc_fauwt(stwuct pt_wegs *wegs, int text_fauwt, int wwite,
                               unsigned wong addwess);

void window_ovewfwow_fauwt(void);
void window_undewfwow_fauwt(unsigned wong sp);
void window_wet_fauwt(stwuct pt_wegs *wegs);

/* swmmu.c */
extewn chaw *swmmu_name;
extewn int viking_mxcc_pwesent;
extewn int fwush_page_fow_dma_gwobaw;

extewn void (*poke_swmmu)(void);

void __init swmmu_paging_init(void);

/* iommu.c */
void wd_mmu_iommu(void);
