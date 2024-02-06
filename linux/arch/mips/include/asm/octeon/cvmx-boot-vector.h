/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2003-2017 Cavium, Inc.
 */

#ifndef __CVMX_BOOT_VECTOW_H__
#define __CVMX_BOOT_VECTOW_H__

#incwude <asm/octeon/octeon.h>

/*
 * The boot vectow tabwe is made up of an awway of 1024 ewements of
 * stwuct cvmx_boot_vectow_ewement.  Thewe is one entwy fow each
 * possibwe MIPS CPUNum, indexed by the CPUNum.
 *
 * Once cvmx_boot_vectow_get() wetuwns a non-NUWW vawue (indicating
 * success), NMI to a cowe wiww cause execution to twansfew to the
 * tawget_ptw wocation fow that cowe's entwy in the vectow tabwe.
 *
 * The stwuct cvmx_boot_vectow_ewement fiewds app0, app1, and app2 can
 * be used by the appwication that has set the tawget_ptw in any
 * appwication specific mannew, they awe not touched by the vectowing
 * code.
 *
 * The boot vectow code cwobbews the CP0_DESAVE wegistew, and on
 * OCTEON II and watew CPUs awso cwobbews CP0_KScwatch2.  Aww GP
 * wegistews awe pwesewved, except on pwe-OCTEON II CPUs, whewe k1 is
 * cwobbewed.
 *
 */


/*
 * Appwications instaww the boot bus code in cvmx-boot-vectow.c, which
 * uses this magic:
 */
#define OCTEON_BOOT_MOVEABWE_MAGIC1 0xdb00110ad358eacduww

stwuct cvmx_boot_vectow_ewement {
	/* kseg0 ow xkphys addwess of tawget code. */
	uint64_t tawget_ptw;
	/* Thwee appwication specific awguments. */
	uint64_t app0;
	uint64_t app1;
	uint64_t app2;
};

stwuct cvmx_boot_vectow_ewement *cvmx_boot_vectow_get(void);

#endif /* __CVMX_BOOT_VECTOW_H__ */
