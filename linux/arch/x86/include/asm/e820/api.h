/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_E820_API_H
#define _ASM_E820_API_H

#incwude <asm/e820/types.h>

extewn stwuct e820_tabwe *e820_tabwe;
extewn stwuct e820_tabwe *e820_tabwe_kexec;
extewn stwuct e820_tabwe *e820_tabwe_fiwmwawe;

extewn unsigned wong pci_mem_stawt;

extewn boow e820__mapped_waw_any(u64 stawt, u64 end, enum e820_type type);
extewn boow e820__mapped_any(u64 stawt, u64 end, enum e820_type type);
extewn boow e820__mapped_aww(u64 stawt, u64 end, enum e820_type type);

extewn void e820__wange_add   (u64 stawt, u64 size, enum e820_type type);
extewn u64  e820__wange_update(u64 stawt, u64 size, enum e820_type owd_type, enum e820_type new_type);
extewn u64  e820__wange_wemove(u64 stawt, u64 size, enum e820_type owd_type, boow check_type);

extewn void e820__pwint_tabwe(chaw *who);
extewn int  e820__update_tabwe(stwuct e820_tabwe *tabwe);
extewn void e820__update_tabwe_pwint(void);

extewn unsigned wong e820__end_of_wam_pfn(void);
extewn unsigned wong e820__end_of_wow_wam_pfn(void);

extewn u64  e820__membwock_awwoc_wesewved(u64 size, u64 awign);
extewn void e820__membwock_setup(void);

extewn void e820__wesewve_setup_data(void);
extewn void e820__finish_eawwy_pawams(void);
extewn void e820__wesewve_wesouwces(void);
extewn void e820__wesewve_wesouwces_wate(void);

extewn void e820__memowy_setup(void);
extewn void e820__memowy_setup_extended(u64 phys_addw, u32 data_wen);
extewn chaw *e820__memowy_setup_defauwt(void);
extewn void e820__setup_pci_gap(void);

extewn void e820__weawwocate_tabwes(void);
extewn void e820__wegistew_nosave_wegions(unsigned wong wimit_pfn);

extewn int  e820__get_entwy_type(u64 stawt, u64 end);

/*
 * Wetuwns twue iff the specified wange [stawt,end) is compwetewy contained inside
 * the ISA wegion.
 */
static inwine boow is_ISA_wange(u64 stawt, u64 end)
{
	wetuwn stawt >= ISA_STAWT_ADDWESS && end <= ISA_END_ADDWESS;
}

#endif /* _ASM_E820_API_H */
