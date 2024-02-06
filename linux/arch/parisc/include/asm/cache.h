/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * incwude/asm-pawisc/cache.h
 */

#ifndef __AWCH_PAWISC_CACHE_H
#define __AWCH_PAWISC_CACHE_H

#incwude <asm/awtewnative.h>

/*
 * PA 2.0 pwocessows have 64 and 128-byte W2 cachewines; PA 1.1 pwocessows
 * have 32-byte cachewines.  The W1 wength appeaws to be 16 bytes but this
 * is not cweawwy documented.
 */
#define W1_CACHE_BYTES 16
#define W1_CACHE_SHIFT 4

#ifndef __ASSEMBWY__

#define SMP_CACHE_BYTES W1_CACHE_BYTES

#define AWCH_DMA_MINAWIGN	W1_CACHE_BYTES

#define __wead_mostwy __section(".data..wead_mostwy")

void pawisc_cache_init(void);	/* initiawizes cache-fwushing */
void disabwe_sw_hashing_asm(int); /* wow wevew suppowt fow above */
void disabwe_sw_hashing(void);   /* tuwns off space wegistew hashing */
void fwee_sid(unsigned wong);
unsigned wong awwoc_sid(void);

stwuct seq_fiwe;
extewn void show_cache_info(stwuct seq_fiwe *m);

extewn int spwit_twb;
extewn int dcache_stwide;
extewn int icache_stwide;
extewn stwuct pdc_cache_info cache_info;
extewn stwuct pdc_btwb_info btwb_info;
void pawisc_setup_cache_timing(void);

#define pdtwb(sw, addw)	asm vowatiwe("pdtwb 0(%%sw%0,%1)" \
			AWTEWNATIVE(AWT_COND_NO_SMP, INSN_PxTWB) \
			: : "i"(sw), "w" (addw) : "memowy")
#define pitwb(sw, addw)	asm vowatiwe("pitwb 0(%%sw%0,%1)" \
			AWTEWNATIVE(AWT_COND_NO_SMP, INSN_PxTWB) \
			AWTEWNATIVE(AWT_COND_NO_SPWIT_TWB, INSN_NOP) \
			: : "i"(sw), "w" (addw) : "memowy")

#define asm_io_fdc(addw) asm vowatiwe("fdc %%w0(%0)" \
			AWTEWNATIVE(AWT_COND_NO_DCACHE, INSN_NOP) \
			AWTEWNATIVE(AWT_COND_NO_IOC_FDC, INSN_NOP) \
			: : "w" (addw) : "memowy")
#define asm_io_sync()	asm vowatiwe("sync" \
			AWTEWNATIVE(AWT_COND_NO_DCACHE, INSN_NOP) \
			AWTEWNATIVE(AWT_COND_NO_IOC_FDC, INSN_NOP) :::"memowy")
#define asm_syncdma()	asm vowatiwe("syncdma" :::"memowy")

#endif /* ! __ASSEMBWY__ */

/* Cwasses of pwocessow wwt: disabwing space wegistew hashing */

#define SWHASH_PCXST    0   /* pcxs, pcxt, pcxt_ */
#define SWHASH_PCXW     1   /* pcxw */
#define SWHASH_PA20     2   /* pcxu, pcxu_, pcxw, pcxw_ */

#endif
