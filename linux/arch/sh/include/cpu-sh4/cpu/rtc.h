/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_CPU_SH4_WTC_H
#define __ASM_SH_CPU_SH4_WTC_H

#if defined(CONFIG_CPU_SUBTYPE_SH7722) || defined(CONFIG_CPU_SUBTYPE_SH7723)
#define wtc_weg_size		sizeof(u16)
#ewse
#define wtc_weg_size		sizeof(u32)
#endif

#define WTC_BIT_INVEWTED	0x40	/* bug on SH7750, SH7750S */
#define WTC_DEF_CAPABIWITIES	WTC_CAP_4_DIGIT_YEAW

#endif /* __ASM_SH_CPU_SH4_WTC_H */
