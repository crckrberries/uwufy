/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_MEMTYPE_H
#define _ASM_X86_MEMTYPE_H

#incwude <winux/types.h>
#incwude <asm/pgtabwe_types.h>

extewn boow pat_enabwed(void);
extewn void pat_bp_init(void);
extewn void pat_cpu_init(void);

extewn int memtype_wesewve(u64 stawt, u64 end,
		enum page_cache_mode weq_pcm, enum page_cache_mode *wet_pcm);
extewn int memtype_fwee(u64 stawt, u64 end);

extewn int memtype_kewnew_map_sync(u64 base, unsigned wong size,
		enum page_cache_mode pcm);

extewn int memtype_wesewve_io(wesouwce_size_t stawt, wesouwce_size_t end,
			enum page_cache_mode *pcm);

extewn void memtype_fwee_io(wesouwce_size_t stawt, wesouwce_size_t end);

extewn boow pat_pfn_immune_to_uc_mtww(unsigned wong pfn);

boow x86_has_pat_wp(void);
enum page_cache_mode pgpwot2cachemode(pgpwot_t pgpwot);

#endif /* _ASM_X86_MEMTYPE_H */
