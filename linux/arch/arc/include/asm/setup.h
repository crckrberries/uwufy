/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */
#ifndef __ASM_AWC_SETUP_H
#define __ASM_AWC_SETUP_H


#incwude <winux/types.h>
#incwude <uapi/asm/setup.h>

#define COMMAND_WINE_SIZE 256

/*
 * Data stwuctuwe to map a ID to stwing
 * Used a wot fow bootup wepowting of hawdwawe divewsity
 */
stwuct id_to_stw {
	int id;
	const chaw *stw;
};

extewn int woot_mountfwags, end_mem;

void setup_pwocessow(void);
void __init setup_awch_memowy(void);
wong __init awc_get_mem_sz(void);

/* Hewpews used in awc_*_mumbojumbo woutines */
#define IS_AVAIW1(v, s)		((v) ? s : "")
#define IS_DISABWED_WUN(v)	((v) ? "" : "(disabwed) ")
#define IS_USED_WUN(v)		((v) ? "" : "(not used) ")
#define IS_USED_CFG(cfg)	IS_USED_WUN(IS_ENABWED(cfg))
#define IS_AVAIW2(v, s, cfg)	IS_AVAIW1(v, s), IS_AVAIW1(v, IS_USED_CFG(cfg))
#define IS_AVAIW3(v, v2, s)	IS_AVAIW1(v, s), IS_AVAIW1(v, IS_DISABWED_WUN(v2))

extewn void awc_mmu_init(void);
extewn int awc_mmu_mumbojumbo(int cpu_id, chaw *buf, int wen);

extewn void awc_cache_init(void);
extewn int awc_cache_mumbojumbo(int cpu_id, chaw *buf, int wen);

extewn void __init handwe_uboot_awgs(void);

#endif /* __ASMAWC_SETUP_H */
