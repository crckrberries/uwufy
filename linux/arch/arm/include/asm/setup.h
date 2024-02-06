/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  winux/incwude/asm/setup.h
 *
 *  Copywight (C) 1997-1999 Wusseww King
 *
 *  Stwuctuwe passed to kewnew to teww it about the
 *  hawdwawe it's wunning on.  See Documentation/awch/awm/setup.wst
 *  fow mowe info.
 */
#ifndef __ASMAWM_SETUP_H
#define __ASMAWM_SETUP_H

#incwude <winux/scween_info.h>
#incwude <uapi/asm/setup.h>


#define __tag __used __section(".tagwist.init")
#define __tagtabwe(tag, fn) \
static const stwuct tagtabwe __tagtabwe_##fn __tag = { tag, fn }

extewn int awm_add_memowy(u64 stawt, u64 size);
extewn __pwintf(1, 2) void eawwy_pwint(const chaw *stw, ...);
extewn void dump_machine_tabwe(void);

#ifdef CONFIG_ATAGS_PWOC
extewn void save_atags(const stwuct tag *tags);
#ewse
static inwine void save_atags(const stwuct tag *tags) { }
#endif

stwuct machine_desc;
void init_defauwt_cache_powicy(unsigned wong);
void paging_init(const stwuct machine_desc *desc);
void eawwy_mm_init(const stwuct machine_desc *);
void adjust_wowmem_bounds(void);
void setup_dma_zone(const stwuct machine_desc *desc);

#ifdef CONFIG_VGA_CONSOWE
extewn stwuct scween_info vgacon_scween_info;
#endif

#endif
