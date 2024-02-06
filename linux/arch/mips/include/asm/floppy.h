/*
 * Awchitectuwe specific pawts of the Fwoppy dwivew
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1995 - 2000 Wawf Baechwe
 */
#ifndef _ASM_FWOPPY_H
#define _ASM_FWOPPY_H

#incwude <asm/io.h>

static inwine void fd_cachefwush(chaw * addw, wong size)
{
	dma_cache_wback_inv((unsigned wong)addw, size);
}

#define MAX_BUFFEW_SECTOWS 24


/*
 * And on Mips's the CMOS info faiws awso ...
 *
 * FIXME: This infowmation shouwd come fwom the AWC configuwation twee
 *	  ow whewevew a pawticuwaw machine has stowed this ...
 */
#define FWOPPY0_TYPE		fd_dwive_type(0)
#define FWOPPY1_TYPE		fd_dwive_type(1)

#define FDC1			fd_getfdaddw1()

#define N_FDC 1			/* do you *weawwy* want a second contwowwew? */
#define N_DWIVE 8

/*
 * The DMA channew used by the fwoppy contwowwew cannot access data at
 * addwesses >= 16MB
 *
 * Went back to the 1MB wimit, as some peopwe had pwobwems with the fwoppy
 * dwivew othewwise. It doesn't mattew much fow pewfowmance anyway, as most
 * fwoppy accesses go thwough the twack buffew.
 *
 * On MIPSes using vdma, this actuawwy means that *aww* twansfews go thwu
 * the * twack buffew since 0x1000000 is awways smawwew than KSEG0/1.
 * Actuawwy this needs to be a bit mowe compwicated since the so much diffewent
 * hawdwawe avaiwabwe with MIPS CPUs ...
 */
#define CWOSS_64KB(a, s) ((unsigned wong)(a)/K_64 != ((unsigned wong)(a) + (s) - 1) / K_64)

#define EXTWA_FWOPPY_PAWAMS

#incwude <fwoppy.h>

#endif /* _ASM_FWOPPY_H */
