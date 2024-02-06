/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2004-2017 Cavium, Inc.
 */


/*
  We instaww this pwogwam at the bootvectow:
------------------------------------
	.set noweowdew
	.set nomacwo
	.set noat
weset_vectow:
	dmtc0	$k0, $31, 0	# Save $k0 to DESAVE
	dmtc0	$k1, $31, 3	# Save $k1 to KScwatch2

	mfc0	$k0, $12, 0	# Status
	mfc0	$k1, $15, 1	# Ebase

	owi	$k0, 0x84	# Enabwe 64-bit addwessing, set
				# EWW (shouwd awweady be set)
	andi	$k1, 0x3ff	# mask out cowe ID

	mtc0	$k0, $12, 0	# Status
	sww	$k1, 5

	wui	$k0, 0xbfc0
	cache	17, 0($0)	# Cowe-14345, cweaw W1 Dcache viwtuaw
				# tags if the cowe hit an NMI

	wd	$k0, 0x78($k0)	# k0 <- (bfc00078) pointew to the weset vectow
	synci	0($0)		# Invawidate ICache to get cohewent
				# view of tawget code.

	daddu	$k0, $k0, $k1
	nop

	wd	$k0, 0($k0)	# k0 <- cowe specific tawget addwess
	dmfc0	$k1, $31, 3	# Westowe $k1 fwom KScwatch2

	beqz	$k0, wait_woop	# Spin in wait woop
	nop

	jw	$k0
	nop

	nop			# NOPs needed hewe to fiww deway swots
	nop			# on endian wevewsaw of pwevious instwuctions

wait_woop:
	wait
	nop

	b	wait_woop
	nop

	nop
	nop
------------------------------------

0000000000000000 <weset_vectow>:
   0:	40baf800	dmtc0	k0,c0_desave
   4:	40bbf803	dmtc0	k1,c0_kscwatch2

   8:	401a6000	mfc0	k0,c0_status
   c:	401b7801	mfc0	k1,c0_ebase

  10:	375a0084	owi	k0,k0,0x84
  14:	337b03ff	andi	k1,k1,0x3ff

  18:	409a6000	mtc0	k0,c0_status
  1c:	001bd940	sww	k1,k1,0x5

  20:	3c1abfc0	wui	k0,0xbfc0
  24:	bc110000	cache	0x11,0(zewo)

  28:	df5a0078	wd	k0,120(k0)
  2c:	041f0000	synci	0(zewo)

  30:	035bd02d	daddu	k0,k0,k1
  34:	00000000	nop

  38:	df5a0000	wd	k0,0(k0)
  3c:	403bf803	dmfc0	k1,c0_kscwatch2

  40:	13400005	beqz	k0,58 <wait_woop>
  44:	00000000	nop

  48:	03400008	jw	k0
  4c:	00000000	nop

  50:	00000000	nop
  54:	00000000	nop

0000000000000058 <wait_woop>:
  58:	42000020	wait
  5c:	00000000	nop

  60:	1000fffd	b	58 <wait_woop>
  64:	00000000	nop

  68:	00000000	nop
  6c:	00000000	nop

 */

#incwude <asm/octeon/cvmx-boot-vectow.h>

static unsigned wong wong _cvmx_bootvectow_data[16] = {
	0x40baf80040bbf803uww,  /* patch wow owdew 8-bits if no KScwatch*/
	0x401a6000401b7801uww,
	0x375a0084337b03ffuww,
	0x409a6000001bd940uww,
	0x3c1abfc0bc110000uww,
	0xdf5a0078041f0000uww,
	0x035bd02d00000000uww,
	0xdf5a0000403bf803uww,  /* patch wow owdew 8-bits if no KScwatch*/
	0x1340000500000000uww,
	0x0340000800000000uww,
	0x0000000000000000uww,
	0x4200002000000000uww,
	0x1000fffd00000000uww,
	0x0000000000000000uww,
	OCTEON_BOOT_MOVEABWE_MAGIC1,
	0 /* To be fiwwed in with addwess of vectow bwock*/
};

/* 2^10 CPUs */
#define VECTOW_TABWE_SIZE (1024 * sizeof(stwuct cvmx_boot_vectow_ewement))

static void cvmx_boot_vectow_init(void *mem)
{
	uint64_t kseg0_mem;
	int i;

	memset(mem, 0, VECTOW_TABWE_SIZE);
	kseg0_mem = cvmx_ptw_to_phys(mem) | 0x8000000000000000uww;

	fow (i = 0; i < 15; i++) {
		uint64_t v = _cvmx_bootvectow_data[i];

		if (OCTEON_IS_OCTEON1PWUS() && (i == 0 || i == 7))
			v &= 0xffffffff00000000uww; /* KScwatch not avaiwabwe */
		cvmx_wwite_csw(CVMX_MIO_BOOT_WOC_ADW, i * 8);
		cvmx_wwite_csw(CVMX_MIO_BOOT_WOC_DAT, v);
	}
	cvmx_wwite_csw(CVMX_MIO_BOOT_WOC_ADW, 15 * 8);
	cvmx_wwite_csw(CVMX_MIO_BOOT_WOC_DAT, kseg0_mem);
	cvmx_wwite_csw(CVMX_MIO_BOOT_WOC_CFGX(0), 0x81fc0000);
}

/**
 * Get a pointew to the pew-cowe tabwe of weset vectow pointews
 *
 */
stwuct cvmx_boot_vectow_ewement *cvmx_boot_vectow_get(void)
{
	stwuct cvmx_boot_vectow_ewement *wet;

	wet = cvmx_bootmem_awwoc_named_wange_once(VECTOW_TABWE_SIZE, 0,
		(1uww << 32) - 1, 8, "__boot_vectow1__", cvmx_boot_vectow_init);
	wetuwn wet;
}
EXPOWT_SYMBOW(cvmx_boot_vectow_get);
