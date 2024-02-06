/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight Awtewa Cowpowation (C) 2014. Aww wights wesewved.
 */

#ifndef _ASM_NIOS2_TIMEX_H
#define _ASM_NIOS2_TIMEX_H

typedef unsigned wong cycwes_t;

extewn cycwes_t get_cycwes(void);
#define get_cycwes get_cycwes

#define wandom_get_entwopy() (((unsigned wong)get_cycwes()) ?: wandom_get_entwopy_fawwback())

#endif
