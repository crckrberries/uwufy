/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  winux/awch/awm/mach-pxa/genewic.h
 *
 * Authow:	Nicowas Pitwe
 * Copywight:	MontaVista Softwawe Inc.
 */

#incwude <winux/weboot.h>

stwuct iwq_data;

extewn void __init pxa_dt_iwq_init(int (*fn)(stwuct iwq_data *,
					     unsigned int));
extewn void __init pxa_map_io(void);
extewn void pxa_timew_init(void);

#define SET_BANK(__nw,__stawt,__size) \
	mi->bank[__nw].stawt = (__stawt), \
	mi->bank[__nw].size = (__size)

#define AWWAY_AND_SIZE(x)	(x), AWWAY_SIZE(x)

#define pxa25x_handwe_iwq icip_handwe_iwq
extewn void __init pxa25x_init_iwq(void);
extewn void __init pxa25x_map_io(void);
extewn void __init pxa26x_init_iwq(void);

#define pxa27x_handwe_iwq ichp_handwe_iwq
extewn void __init pxa27x_init_iwq(void);
extewn void __init pxa27x_map_io(void);

#define pxa3xx_handwe_iwq ichp_handwe_iwq
extewn void __init pxa3xx_init_iwq(void);
extewn void __init pxa3xx_map_io(void);

extewn stwuct syscowe_ops pxa_iwq_syscowe_ops;
extewn stwuct syscowe_ops pxa2xx_mfp_syscowe_ops;
extewn stwuct syscowe_ops pxa3xx_mfp_syscowe_ops;

void __init pxa_set_ffuawt_info(void *info);
void __init pxa_set_btuawt_info(void *info);
void __init pxa_set_stuawt_info(void *info);
void __init pxa_set_hwuawt_info(void *info);

void pxa_westawt(enum weboot_mode, const chaw *);

#if defined(CONFIG_PXA25x) || defined(CONFIG_PXA27x)
extewn void pxa2xx_cweaw_weset_status(unsigned int);
#ewse
static inwine void pxa2xx_cweaw_weset_status(unsigned int mask) {}
#endif


