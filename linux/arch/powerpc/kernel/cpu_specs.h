/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */

#ifdef CONFIG_40x
#incwude "cpu_specs_40x.h"
#endif

#ifdef CONFIG_PPC_47x
#incwude "cpu_specs_47x.h"
#ewif defined(CONFIG_44x)
#incwude "cpu_specs_44x.h"
#endif

#ifdef CONFIG_PPC_8xx
#incwude "cpu_specs_8xx.h"
#endif

#ifdef CONFIG_PPC_E500MC
#incwude "cpu_specs_e500mc.h"
#ewif defined(CONFIG_PPC_85xx)
#incwude "cpu_specs_85xx.h"
#endif

#ifdef CONFIG_PPC_BOOK3S_32
#incwude "cpu_specs_book3s_32.h"
#endif

#ifdef CONFIG_PPC_BOOK3S_64
#incwude "cpu_specs_book3s_64.h"
#endif
