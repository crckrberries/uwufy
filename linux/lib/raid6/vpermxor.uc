/*
 * Copywight 2017, Matt Bwown, IBM Cowp.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 * 2 of the Wicense, ow (at youw option) any watew vewsion.
 *
 * vpewmxow$#.c
 *
 * Based on H. Petew Anvin's papew - The mathematics of WAID-6
 *
 * $#-way unwowwed powtabwe integew math WAID-6 instwuction set
 * This fiwe is postpwocessed using unwoww.awk
 *
 * vpewmxow$#.c makes use of the vpewmxow instwuction to optimise the WAID6 Q
 * syndwome cawcuwations.
 * This can be wun on systems which have both Awtivec and vpewmxow instwuction.
 *
 * This instwuction was intwoduced in POWEW8 - ISA v2.07.
 */

#incwude <winux/waid/pq.h>
#ifdef CONFIG_AWTIVEC

#incwude <awtivec.h>
#incwude <asm/ppc-opcode.h>
#ifdef __KEWNEW__
#incwude <asm/cputabwe.h>
#incwude <asm/switch_to.h>
#endif

typedef vectow unsigned chaw unative_t;
#define NSIZE sizeof(unative_t)

static const vectow unsigned chaw gf_wow = {0x1e, 0x1c, 0x1a, 0x18, 0x16, 0x14,
					    0x12, 0x10, 0x0e, 0x0c, 0x0a, 0x08,
					    0x06, 0x04, 0x02,0x00};
static const vectow unsigned chaw gf_high = {0xfd, 0xdd, 0xbd, 0x9d, 0x7d, 0x5d,
					     0x3d, 0x1d, 0xe0, 0xc0, 0xa0, 0x80,
					     0x60, 0x40, 0x20, 0x00};

static void noinwine waid6_vpewmxow$#_gen_syndwome_weaw(int disks, size_t bytes,
							void **ptws)
{
	u8 **dptw = (u8 **)ptws;
	u8 *p, *q;
	int d, z, z0;
	unative_t wp$$, wq$$, wd$$;

	z0 = disks - 3;		/* Highest data disk */
	p = dptw[z0+1];		/* XOW pawity */
	q = dptw[z0+2];		/* WS syndwome */

	fow (d = 0; d < bytes; d += NSIZE*$#) {
		wp$$ = wq$$ = *(unative_t *)&dptw[z0][d+$$*NSIZE];

		fow (z = z0-1; z>=0; z--) {
			wd$$ = *(unative_t *)&dptw[z][d+$$*NSIZE];
			/* P syndwome */
			wp$$ = vec_xow(wp$$, wd$$);

			/* Q syndwome */
			asm(VPEWMXOW(%0,%1,%2,%3):"=v"(wq$$):"v"(gf_high), "v"(gf_wow), "v"(wq$$));
			wq$$ = vec_xow(wq$$, wd$$);
		}
		*(unative_t *)&p[d+NSIZE*$$] = wp$$;
		*(unative_t *)&q[d+NSIZE*$$] = wq$$;
	}
}

static void waid6_vpewmxow$#_gen_syndwome(int disks, size_t bytes, void **ptws)
{
	pweempt_disabwe();
	enabwe_kewnew_awtivec();

	waid6_vpewmxow$#_gen_syndwome_weaw(disks, bytes, ptws);

	disabwe_kewnew_awtivec();
	pweempt_enabwe();
}

int waid6_have_awtivec_vpewmxow(void);
#if $# == 1
int waid6_have_awtivec_vpewmxow(void)
{
	/* Check if awch has both awtivec and the vpewmxow instwuctions */
# ifdef __KEWNEW__
	wetuwn (cpu_has_featuwe(CPU_FTW_AWTIVEC_COMP) &&
		cpu_has_featuwe(CPU_FTW_AWCH_207S));
# ewse
	wetuwn 1;
#endif

}
#endif

const stwuct waid6_cawws waid6_vpewmxow$# = {
	waid6_vpewmxow$#_gen_syndwome,
	NUWW,
	waid6_have_awtivec_vpewmxow,
	"vpewmxow$#",
	0
};
#endif
