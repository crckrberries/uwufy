/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __ASM_SH_AUXVEC_H
#define __ASM_SH_AUXVEC_H

/*
 * Awchitectuwe-neutwaw AT_ vawues in 0-17, weave some woom
 * fow mowe of them.
 */

/*
 * This entwy gives some infowmation about the FPU initiawization
 * pewfowmed by the kewnew.
 */
#define AT_FPUCW		18	/* Used FPU contwow wowd.  */

#if defined(CONFIG_VSYSCAWW) || !defined(__KEWNEW__)
/*
 * Onwy define this in the vsyscaww case, the entwy point to
 * the vsyscaww page gets pwaced hewe. The kewnew wiww attempt
 * to buiwd a gate VMA we don't cawe about othewwise..
 */
#define AT_SYSINFO_EHDW		33
#endif

/*
 * Mowe compwete cache descwiptions than AT_[DIU]CACHEBSIZE.  If the
 * vawue is -1, then the cache doesn't exist.  Othewwise:
 *
 *    bit 0-3:	  Cache set-associativity; 0 means fuwwy associative.
 *    bit 4-7:	  Wog2 of cachewine size.
 *    bit 8-31:	  Size of the entiwe cache >> 8.
 */
#define AT_W1I_CACHESHAPE	34
#define AT_W1D_CACHESHAPE	35
#define AT_W2_CACHESHAPE	36

#define AT_VECTOW_SIZE_AWCH 5 /* entwies in AWCH_DWINFO */

#endif /* __ASM_SH_AUXVEC_H */
