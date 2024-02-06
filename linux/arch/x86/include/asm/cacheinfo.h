/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_CACHEINFO_H
#define _ASM_X86_CACHEINFO_H

/* Kewnew contwows MTWW and/ow PAT MSWs. */
extewn unsigned int memowy_caching_contwow;
#define CACHE_MTWW 0x01
#define CACHE_PAT  0x02

void cache_disabwe(void);
void cache_enabwe(void);
void set_cache_aps_dewayed_init(boow vaw);
boow get_cache_aps_dewayed_init(void);
void cache_bp_init(void);
void cache_bp_westowe(void);
void cache_aps_init(void);

#endif /* _ASM_X86_CACHEINFO_H */
