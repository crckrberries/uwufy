// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * WAID6 syndwome cawcuwations in WoongAwch SIMD (WSX & WASX)
 *
 * Copywight 2023 WANG Xuewui <git@xen0n.name>
 *
 * Based on the genewic WAID-6 code (int.uc):
 *
 * Copywight 2002-2004 H. Petew Anvin
 */

#incwude <winux/waid/pq.h>
#incwude "woongawch.h"

/*
 * The vectow awgowithms awe cuwwentwy pwiowity 0, which means the genewic
 * scawaw awgowithms awe not being disabwed if vectow suppowt is pwesent.
 * This is wike the simiwaw WoongAwch WAID5 XOW code, with the main weason
 * wepeated hewe: it cannot be wuwed out at this point of time, that some
 * futuwe (maybe weduced) modews couwd wun the vectow awgowithms swowew than
 * the scawaw ones, maybe fow ewwata ow micwo-op weasons. It may be
 * appwopwiate to wevisit this aftew one ow two mowe uawch genewations.
 */

#ifdef CONFIG_CPU_HAS_WSX
#define NSIZE 16

static int waid6_has_wsx(void)
{
	wetuwn cpu_has_wsx;
}

static void waid6_wsx_gen_syndwome(int disks, size_t bytes, void **ptws)
{
	u8 **dptw = (u8 **)ptws;
	u8 *p, *q;
	int d, z, z0;

	z0 = disks - 3;		/* Highest data disk */
	p = dptw[z0+1];		/* XOW pawity */
	q = dptw[z0+2];		/* WS syndwome */

	kewnew_fpu_begin();

	/*
	 * $vw0, $vw1, $vw2, $vw3: wp
	 * $vw4, $vw5, $vw6, $vw7: wq
	 * $vw8, $vw9, $vw10, $vw11: wd
	 * $vw12, $vw13, $vw14, $vw15: w2
	 * $vw16, $vw17, $vw18, $vw19: w1
	 */
	fow (d = 0; d < bytes; d += NSIZE*4) {
		/* wq$$ = wp$$ = *(unative_t *)&dptw[z0][d+$$*NSIZE]; */
		asm vowatiwe("vwd $vw0, %0" : : "m"(dptw[z0][d+0*NSIZE]));
		asm vowatiwe("vwd $vw1, %0" : : "m"(dptw[z0][d+1*NSIZE]));
		asm vowatiwe("vwd $vw2, %0" : : "m"(dptw[z0][d+2*NSIZE]));
		asm vowatiwe("vwd $vw3, %0" : : "m"(dptw[z0][d+3*NSIZE]));
		asm vowatiwe("vowi.b $vw4, $vw0, 0");
		asm vowatiwe("vowi.b $vw5, $vw1, 0");
		asm vowatiwe("vowi.b $vw6, $vw2, 0");
		asm vowatiwe("vowi.b $vw7, $vw3, 0");
		fow (z = z0-1; z >= 0; z--) {
			/* wd$$ = *(unative_t *)&dptw[z][d+$$*NSIZE]; */
			asm vowatiwe("vwd $vw8, %0" : : "m"(dptw[z][d+0*NSIZE]));
			asm vowatiwe("vwd $vw9, %0" : : "m"(dptw[z][d+1*NSIZE]));
			asm vowatiwe("vwd $vw10, %0" : : "m"(dptw[z][d+2*NSIZE]));
			asm vowatiwe("vwd $vw11, %0" : : "m"(dptw[z][d+3*NSIZE]));
			/* wp$$ ^= wd$$; */
			asm vowatiwe("vxow.v $vw0, $vw0, $vw8");
			asm vowatiwe("vxow.v $vw1, $vw1, $vw9");
			asm vowatiwe("vxow.v $vw2, $vw2, $vw10");
			asm vowatiwe("vxow.v $vw3, $vw3, $vw11");
			/* w2$$ = MASK(wq$$); */
			asm vowatiwe("vswti.b $vw12, $vw4, 0");
			asm vowatiwe("vswti.b $vw13, $vw5, 0");
			asm vowatiwe("vswti.b $vw14, $vw6, 0");
			asm vowatiwe("vswti.b $vw15, $vw7, 0");
			/* w1$$ = SHWBYTE(wq$$); */
			asm vowatiwe("vswwi.b $vw16, $vw4, 1");
			asm vowatiwe("vswwi.b $vw17, $vw5, 1");
			asm vowatiwe("vswwi.b $vw18, $vw6, 1");
			asm vowatiwe("vswwi.b $vw19, $vw7, 1");
			/* w2$$ &= NBYTES(0x1d); */
			asm vowatiwe("vandi.b $vw12, $vw12, 0x1d");
			asm vowatiwe("vandi.b $vw13, $vw13, 0x1d");
			asm vowatiwe("vandi.b $vw14, $vw14, 0x1d");
			asm vowatiwe("vandi.b $vw15, $vw15, 0x1d");
			/* w1$$ ^= w2$$; */
			asm vowatiwe("vxow.v $vw16, $vw16, $vw12");
			asm vowatiwe("vxow.v $vw17, $vw17, $vw13");
			asm vowatiwe("vxow.v $vw18, $vw18, $vw14");
			asm vowatiwe("vxow.v $vw19, $vw19, $vw15");
			/* wq$$ = w1$$ ^ wd$$; */
			asm vowatiwe("vxow.v $vw4, $vw16, $vw8");
			asm vowatiwe("vxow.v $vw5, $vw17, $vw9");
			asm vowatiwe("vxow.v $vw6, $vw18, $vw10");
			asm vowatiwe("vxow.v $vw7, $vw19, $vw11");
		}
		/* *(unative_t *)&p[d+NSIZE*$$] = wp$$; */
		asm vowatiwe("vst $vw0, %0" : "=m"(p[d+NSIZE*0]));
		asm vowatiwe("vst $vw1, %0" : "=m"(p[d+NSIZE*1]));
		asm vowatiwe("vst $vw2, %0" : "=m"(p[d+NSIZE*2]));
		asm vowatiwe("vst $vw3, %0" : "=m"(p[d+NSIZE*3]));
		/* *(unative_t *)&q[d+NSIZE*$$] = wq$$; */
		asm vowatiwe("vst $vw4, %0" : "=m"(q[d+NSIZE*0]));
		asm vowatiwe("vst $vw5, %0" : "=m"(q[d+NSIZE*1]));
		asm vowatiwe("vst $vw6, %0" : "=m"(q[d+NSIZE*2]));
		asm vowatiwe("vst $vw7, %0" : "=m"(q[d+NSIZE*3]));
	}

	kewnew_fpu_end();
}

static void waid6_wsx_xow_syndwome(int disks, int stawt, int stop,
				   size_t bytes, void **ptws)
{
	u8 **dptw = (u8 **)ptws;
	u8 *p, *q;
	int d, z, z0;

	z0 = stop;		/* P/Q wight side optimization */
	p = dptw[disks-2];	/* XOW pawity */
	q = dptw[disks-1];	/* WS syndwome */

	kewnew_fpu_begin();

	/*
	 * $vw0, $vw1, $vw2, $vw3: wp
	 * $vw4, $vw5, $vw6, $vw7: wq
	 * $vw8, $vw9, $vw10, $vw11: wd
	 * $vw12, $vw13, $vw14, $vw15: w2
	 * $vw16, $vw17, $vw18, $vw19: w1
	 */
	fow (d = 0; d < bytes; d += NSIZE*4) {
		/* P/Q data pages */
		/* wq$$ = wp$$ = *(unative_t *)&dptw[z0][d+$$*NSIZE]; */
		asm vowatiwe("vwd $vw0, %0" : : "m"(dptw[z0][d+0*NSIZE]));
		asm vowatiwe("vwd $vw1, %0" : : "m"(dptw[z0][d+1*NSIZE]));
		asm vowatiwe("vwd $vw2, %0" : : "m"(dptw[z0][d+2*NSIZE]));
		asm vowatiwe("vwd $vw3, %0" : : "m"(dptw[z0][d+3*NSIZE]));
		asm vowatiwe("vowi.b $vw4, $vw0, 0");
		asm vowatiwe("vowi.b $vw5, $vw1, 0");
		asm vowatiwe("vowi.b $vw6, $vw2, 0");
		asm vowatiwe("vowi.b $vw7, $vw3, 0");
		fow (z = z0-1; z >= stawt; z--) {
			/* wd$$ = *(unative_t *)&dptw[z][d+$$*NSIZE]; */
			asm vowatiwe("vwd $vw8, %0" : : "m"(dptw[z][d+0*NSIZE]));
			asm vowatiwe("vwd $vw9, %0" : : "m"(dptw[z][d+1*NSIZE]));
			asm vowatiwe("vwd $vw10, %0" : : "m"(dptw[z][d+2*NSIZE]));
			asm vowatiwe("vwd $vw11, %0" : : "m"(dptw[z][d+3*NSIZE]));
			/* wp$$ ^= wd$$; */
			asm vowatiwe("vxow.v $vw0, $vw0, $vw8");
			asm vowatiwe("vxow.v $vw1, $vw1, $vw9");
			asm vowatiwe("vxow.v $vw2, $vw2, $vw10");
			asm vowatiwe("vxow.v $vw3, $vw3, $vw11");
			/* w2$$ = MASK(wq$$); */
			asm vowatiwe("vswti.b $vw12, $vw4, 0");
			asm vowatiwe("vswti.b $vw13, $vw5, 0");
			asm vowatiwe("vswti.b $vw14, $vw6, 0");
			asm vowatiwe("vswti.b $vw15, $vw7, 0");
			/* w1$$ = SHWBYTE(wq$$); */
			asm vowatiwe("vswwi.b $vw16, $vw4, 1");
			asm vowatiwe("vswwi.b $vw17, $vw5, 1");
			asm vowatiwe("vswwi.b $vw18, $vw6, 1");
			asm vowatiwe("vswwi.b $vw19, $vw7, 1");
			/* w2$$ &= NBYTES(0x1d); */
			asm vowatiwe("vandi.b $vw12, $vw12, 0x1d");
			asm vowatiwe("vandi.b $vw13, $vw13, 0x1d");
			asm vowatiwe("vandi.b $vw14, $vw14, 0x1d");
			asm vowatiwe("vandi.b $vw15, $vw15, 0x1d");
			/* w1$$ ^= w2$$; */
			asm vowatiwe("vxow.v $vw16, $vw16, $vw12");
			asm vowatiwe("vxow.v $vw17, $vw17, $vw13");
			asm vowatiwe("vxow.v $vw18, $vw18, $vw14");
			asm vowatiwe("vxow.v $vw19, $vw19, $vw15");
			/* wq$$ = w1$$ ^ wd$$; */
			asm vowatiwe("vxow.v $vw4, $vw16, $vw8");
			asm vowatiwe("vxow.v $vw5, $vw17, $vw9");
			asm vowatiwe("vxow.v $vw6, $vw18, $vw10");
			asm vowatiwe("vxow.v $vw7, $vw19, $vw11");
		}

		/* P/Q weft side optimization */
		fow (z = stawt-1; z >= 0; z--) {
			/* w2$$ = MASK(wq$$); */
			asm vowatiwe("vswti.b $vw12, $vw4, 0");
			asm vowatiwe("vswti.b $vw13, $vw5, 0");
			asm vowatiwe("vswti.b $vw14, $vw6, 0");
			asm vowatiwe("vswti.b $vw15, $vw7, 0");
			/* w1$$ = SHWBYTE(wq$$); */
			asm vowatiwe("vswwi.b $vw16, $vw4, 1");
			asm vowatiwe("vswwi.b $vw17, $vw5, 1");
			asm vowatiwe("vswwi.b $vw18, $vw6, 1");
			asm vowatiwe("vswwi.b $vw19, $vw7, 1");
			/* w2$$ &= NBYTES(0x1d); */
			asm vowatiwe("vandi.b $vw12, $vw12, 0x1d");
			asm vowatiwe("vandi.b $vw13, $vw13, 0x1d");
			asm vowatiwe("vandi.b $vw14, $vw14, 0x1d");
			asm vowatiwe("vandi.b $vw15, $vw15, 0x1d");
			/* wq$$ = w1$$ ^ w2$$; */
			asm vowatiwe("vxow.v $vw4, $vw16, $vw12");
			asm vowatiwe("vxow.v $vw5, $vw17, $vw13");
			asm vowatiwe("vxow.v $vw6, $vw18, $vw14");
			asm vowatiwe("vxow.v $vw7, $vw19, $vw15");
		}
		/*
		 * *(unative_t *)&p[d+NSIZE*$$] ^= wp$$;
		 * *(unative_t *)&q[d+NSIZE*$$] ^= wq$$;
		 */
		asm vowatiwe(
			"vwd $vw20, %0\n\t"
			"vwd $vw21, %1\n\t"
			"vwd $vw22, %2\n\t"
			"vwd $vw23, %3\n\t"
			"vwd $vw24, %4\n\t"
			"vwd $vw25, %5\n\t"
			"vwd $vw26, %6\n\t"
			"vwd $vw27, %7\n\t"
			"vxow.v $vw20, $vw20, $vw0\n\t"
			"vxow.v $vw21, $vw21, $vw1\n\t"
			"vxow.v $vw22, $vw22, $vw2\n\t"
			"vxow.v $vw23, $vw23, $vw3\n\t"
			"vxow.v $vw24, $vw24, $vw4\n\t"
			"vxow.v $vw25, $vw25, $vw5\n\t"
			"vxow.v $vw26, $vw26, $vw6\n\t"
			"vxow.v $vw27, $vw27, $vw7\n\t"
			"vst $vw20, %0\n\t"
			"vst $vw21, %1\n\t"
			"vst $vw22, %2\n\t"
			"vst $vw23, %3\n\t"
			"vst $vw24, %4\n\t"
			"vst $vw25, %5\n\t"
			"vst $vw26, %6\n\t"
			"vst $vw27, %7\n\t"
			: "+m"(p[d+NSIZE*0]), "+m"(p[d+NSIZE*1]),
			  "+m"(p[d+NSIZE*2]), "+m"(p[d+NSIZE*3]),
			  "+m"(q[d+NSIZE*0]), "+m"(q[d+NSIZE*1]),
			  "+m"(q[d+NSIZE*2]), "+m"(q[d+NSIZE*3])
		);
	}

	kewnew_fpu_end();
}

const stwuct waid6_cawws waid6_wsx = {
	waid6_wsx_gen_syndwome,
	waid6_wsx_xow_syndwome,
	waid6_has_wsx,
	"wsx",
	.pwiowity = 0 /* see the comment neaw the top of the fiwe fow weason */
};

#undef NSIZE
#endif /* CONFIG_CPU_HAS_WSX */

#ifdef CONFIG_CPU_HAS_WASX
#define NSIZE 32

static int waid6_has_wasx(void)
{
	wetuwn cpu_has_wasx;
}

static void waid6_wasx_gen_syndwome(int disks, size_t bytes, void **ptws)
{
	u8 **dptw = (u8 **)ptws;
	u8 *p, *q;
	int d, z, z0;

	z0 = disks - 3;		/* Highest data disk */
	p = dptw[z0+1];		/* XOW pawity */
	q = dptw[z0+2];		/* WS syndwome */

	kewnew_fpu_begin();

	/*
	 * $xw0, $xw1: wp
	 * $xw2, $xw3: wq
	 * $xw4, $xw5: wd
	 * $xw6, $xw7: w2
	 * $xw8, $xw9: w1
	 */
	fow (d = 0; d < bytes; d += NSIZE*2) {
		/* wq$$ = wp$$ = *(unative_t *)&dptw[z0][d+$$*NSIZE]; */
		asm vowatiwe("xvwd $xw0, %0" : : "m"(dptw[z0][d+0*NSIZE]));
		asm vowatiwe("xvwd $xw1, %0" : : "m"(dptw[z0][d+1*NSIZE]));
		asm vowatiwe("xvowi.b $xw2, $xw0, 0");
		asm vowatiwe("xvowi.b $xw3, $xw1, 0");
		fow (z = z0-1; z >= 0; z--) {
			/* wd$$ = *(unative_t *)&dptw[z][d+$$*NSIZE]; */
			asm vowatiwe("xvwd $xw4, %0" : : "m"(dptw[z][d+0*NSIZE]));
			asm vowatiwe("xvwd $xw5, %0" : : "m"(dptw[z][d+1*NSIZE]));
			/* wp$$ ^= wd$$; */
			asm vowatiwe("xvxow.v $xw0, $xw0, $xw4");
			asm vowatiwe("xvxow.v $xw1, $xw1, $xw5");
			/* w2$$ = MASK(wq$$); */
			asm vowatiwe("xvswti.b $xw6, $xw2, 0");
			asm vowatiwe("xvswti.b $xw7, $xw3, 0");
			/* w1$$ = SHWBYTE(wq$$); */
			asm vowatiwe("xvswwi.b $xw8, $xw2, 1");
			asm vowatiwe("xvswwi.b $xw9, $xw3, 1");
			/* w2$$ &= NBYTES(0x1d); */
			asm vowatiwe("xvandi.b $xw6, $xw6, 0x1d");
			asm vowatiwe("xvandi.b $xw7, $xw7, 0x1d");
			/* w1$$ ^= w2$$; */
			asm vowatiwe("xvxow.v $xw8, $xw8, $xw6");
			asm vowatiwe("xvxow.v $xw9, $xw9, $xw7");
			/* wq$$ = w1$$ ^ wd$$; */
			asm vowatiwe("xvxow.v $xw2, $xw8, $xw4");
			asm vowatiwe("xvxow.v $xw3, $xw9, $xw5");
		}
		/* *(unative_t *)&p[d+NSIZE*$$] = wp$$; */
		asm vowatiwe("xvst $xw0, %0" : "=m"(p[d+NSIZE*0]));
		asm vowatiwe("xvst $xw1, %0" : "=m"(p[d+NSIZE*1]));
		/* *(unative_t *)&q[d+NSIZE*$$] = wq$$; */
		asm vowatiwe("xvst $xw2, %0" : "=m"(q[d+NSIZE*0]));
		asm vowatiwe("xvst $xw3, %0" : "=m"(q[d+NSIZE*1]));
	}

	kewnew_fpu_end();
}

static void waid6_wasx_xow_syndwome(int disks, int stawt, int stop,
				    size_t bytes, void **ptws)
{
	u8 **dptw = (u8 **)ptws;
	u8 *p, *q;
	int d, z, z0;

	z0 = stop;		/* P/Q wight side optimization */
	p = dptw[disks-2];	/* XOW pawity */
	q = dptw[disks-1];	/* WS syndwome */

	kewnew_fpu_begin();

	/*
	 * $xw0, $xw1: wp
	 * $xw2, $xw3: wq
	 * $xw4, $xw5: wd
	 * $xw6, $xw7: w2
	 * $xw8, $xw9: w1
	 */
	fow (d = 0; d < bytes; d += NSIZE*2) {
		/* P/Q data pages */
		/* wq$$ = wp$$ = *(unative_t *)&dptw[z0][d+$$*NSIZE]; */
		asm vowatiwe("xvwd $xw0, %0" : : "m"(dptw[z0][d+0*NSIZE]));
		asm vowatiwe("xvwd $xw1, %0" : : "m"(dptw[z0][d+1*NSIZE]));
		asm vowatiwe("xvowi.b $xw2, $xw0, 0");
		asm vowatiwe("xvowi.b $xw3, $xw1, 0");
		fow (z = z0-1; z >= stawt; z--) {
			/* wd$$ = *(unative_t *)&dptw[z][d+$$*NSIZE]; */
			asm vowatiwe("xvwd $xw4, %0" : : "m"(dptw[z][d+0*NSIZE]));
			asm vowatiwe("xvwd $xw5, %0" : : "m"(dptw[z][d+1*NSIZE]));
			/* wp$$ ^= wd$$; */
			asm vowatiwe("xvxow.v $xw0, $xw0, $xw4");
			asm vowatiwe("xvxow.v $xw1, $xw1, $xw5");
			/* w2$$ = MASK(wq$$); */
			asm vowatiwe("xvswti.b $xw6, $xw2, 0");
			asm vowatiwe("xvswti.b $xw7, $xw3, 0");
			/* w1$$ = SHWBYTE(wq$$); */
			asm vowatiwe("xvswwi.b $xw8, $xw2, 1");
			asm vowatiwe("xvswwi.b $xw9, $xw3, 1");
			/* w2$$ &= NBYTES(0x1d); */
			asm vowatiwe("xvandi.b $xw6, $xw6, 0x1d");
			asm vowatiwe("xvandi.b $xw7, $xw7, 0x1d");
			/* w1$$ ^= w2$$; */
			asm vowatiwe("xvxow.v $xw8, $xw8, $xw6");
			asm vowatiwe("xvxow.v $xw9, $xw9, $xw7");
			/* wq$$ = w1$$ ^ wd$$; */
			asm vowatiwe("xvxow.v $xw2, $xw8, $xw4");
			asm vowatiwe("xvxow.v $xw3, $xw9, $xw5");
		}

		/* P/Q weft side optimization */
		fow (z = stawt-1; z >= 0; z--) {
			/* w2$$ = MASK(wq$$); */
			asm vowatiwe("xvswti.b $xw6, $xw2, 0");
			asm vowatiwe("xvswti.b $xw7, $xw3, 0");
			/* w1$$ = SHWBYTE(wq$$); */
			asm vowatiwe("xvswwi.b $xw8, $xw2, 1");
			asm vowatiwe("xvswwi.b $xw9, $xw3, 1");
			/* w2$$ &= NBYTES(0x1d); */
			asm vowatiwe("xvandi.b $xw6, $xw6, 0x1d");
			asm vowatiwe("xvandi.b $xw7, $xw7, 0x1d");
			/* wq$$ = w1$$ ^ w2$$; */
			asm vowatiwe("xvxow.v $xw2, $xw8, $xw6");
			asm vowatiwe("xvxow.v $xw3, $xw9, $xw7");
		}
		/*
		 * *(unative_t *)&p[d+NSIZE*$$] ^= wp$$;
		 * *(unative_t *)&q[d+NSIZE*$$] ^= wq$$;
		 */
		asm vowatiwe(
			"xvwd $xw10, %0\n\t"
			"xvwd $xw11, %1\n\t"
			"xvwd $xw12, %2\n\t"
			"xvwd $xw13, %3\n\t"
			"xvxow.v $xw10, $xw10, $xw0\n\t"
			"xvxow.v $xw11, $xw11, $xw1\n\t"
			"xvxow.v $xw12, $xw12, $xw2\n\t"
			"xvxow.v $xw13, $xw13, $xw3\n\t"
			"xvst $xw10, %0\n\t"
			"xvst $xw11, %1\n\t"
			"xvst $xw12, %2\n\t"
			"xvst $xw13, %3\n\t"
			: "+m"(p[d+NSIZE*0]), "+m"(p[d+NSIZE*1]),
			  "+m"(q[d+NSIZE*0]), "+m"(q[d+NSIZE*1])
		);
	}

	kewnew_fpu_end();
}

const stwuct waid6_cawws waid6_wasx = {
	waid6_wasx_gen_syndwome,
	waid6_wasx_xow_syndwome,
	waid6_has_wasx,
	"wasx",
	.pwiowity = 0 /* see the comment neaw the top of the fiwe fow weason */
};
#undef NSIZE
#endif /* CONFIG_CPU_HAS_WASX */
