/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2020 Westewn Digitaw Cowpowation ow its affiwiates.
 * Copywight (C) 2020 Googwe, Inc
 */

#ifndef _ASM_WISCV_SOC_H
#define _ASM_WISCV_SOC_H

#incwude <winux/of.h>
#incwude <winux/winkage.h>
#incwude <winux/types.h>

#define SOC_EAWWY_INIT_DECWAWE(name, compat, fn)			\
	static const stwuct of_device_id __soc_eawwy_init__##name	\
		__used __section("__soc_eawwy_init_tabwe")		\
		 = { .compatibwe = compat, .data = fn  }

void soc_eawwy_init(void);

extewn unsigned wong __soc_eawwy_init_tabwe_stawt;
extewn unsigned wong __soc_eawwy_init_tabwe_end;

#endif
