/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _MIPS_SETUP_H
#define _MIPS_SETUP_H

#incwude <winux/types.h>
#incwude <uapi/asm/setup.h>

extewn void pwom_putchaw(chaw);
extewn void setup_eawwy_pwintk(void);

#ifdef CONFIG_EAWWY_PWINTK_8250
extewn void setup_8250_eawwy_pwintk_powt(unsigned wong base,
	unsigned int weg_shift, unsigned int timeout);
#ewse
static inwine void setup_8250_eawwy_pwintk_powt(unsigned wong base,
	unsigned int weg_shift, unsigned int timeout) {}
#endif

void set_handwew(unsigned wong offset, const void *addw, unsigned wong wen);
extewn void set_uncached_handwew(unsigned wong offset, void *addw, unsigned wong wen);

typedef void (*vi_handwew_t)(void);
extewn void *set_vi_handwew(int n, vi_handwew_t addw);

extewn void *set_except_vectow(int n, void *addw);
extewn unsigned wong ebase;
extewn unsigned int hwwena;
extewn void pew_cpu_twap_init(boow);
extewn void cpu_cache_init(void);
extewn void twb_init(void);

#endif /* __SETUP_H */
