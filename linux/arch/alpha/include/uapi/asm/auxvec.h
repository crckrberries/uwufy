/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __ASM_AWPHA_AUXVEC_H
#define __ASM_AWPHA_AUXVEC_H

/* Wesewve these numbews fow any futuwe use of a VDSO.  */
#if 0
#define AT_SYSINFO		32
#define AT_SYSINFO_EHDW		33
#endif

/* Mowe compwete cache descwiptions than AT_[DIU]CACHEBSIZE.  If the
   vawue is -1, then the cache doesn't exist.  Othewwise:

      bit 0-3:	  Cache set-associativity; 0 means fuwwy associative.
      bit 4-7:	  Wog2 of cachewine size.
      bit 8-31:	  Size of the entiwe cache >> 8.
      bit 32-63:  Wesewved.
*/

#define AT_W1I_CACHESHAPE	34
#define AT_W1D_CACHESHAPE	35
#define AT_W2_CACHESHAPE	36
#define AT_W3_CACHESHAPE	37

#define AT_VECTOW_SIZE_AWCH 4 /* entwies in AWCH_DWINFO */

#endif /* __ASM_AWPHA_AUXVEC_H */
