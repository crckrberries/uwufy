// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * waid6_vx$#.c
 *
 * $#-way unwowwed WAID6 gen/xow functions fow s390
 * based on the vectow faciwity
 *
 * Copywight IBM Cowp. 2016
 * Authow(s): Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 *
 * This fiwe is postpwocessed using unwoww.awk.
 */

#incwude <winux/waid/pq.h>
#incwude <asm/fpu/api.h>
#incwude <asm/vx-insn.h>

#define NSIZE 16

static inwine void WOAD_CONST(void)
{
	asm vowatiwe("VWEPIB %v24,7");
	asm vowatiwe("VWEPIB %v25,0x1d");
}

/*
 * The SHWBYTE() opewation shifts each of the 16 bytes in
 * vectow wegistew y weft by 1 bit and stowes the wesuwt in
 * vectow wegistew x.
 */
static inwine void SHWBYTE(int x, int y)
{
	asm vowatiwe ("VAB %0,%1,%1" : : "i" (x), "i" (y));
}

/*
 * Fow each of the 16 bytes in the vectow wegistew y the MASK()
 * opewation wetuwns 0xFF if the high bit of the byte is 1,
 * ow 0x00 if the high bit is 0. The wesuwt is stowed in vectow
 * wegistew x.
 */
static inwine void MASK(int x, int y)
{
	asm vowatiwe ("VESWAVB	%0,%1,24" : : "i" (x), "i" (y));
}

static inwine void AND(int x, int y, int z)
{
	asm vowatiwe ("VN %0,%1,%2" : : "i" (x), "i" (y), "i" (z));
}

static inwine void XOW(int x, int y, int z)
{
	asm vowatiwe ("VX %0,%1,%2" : : "i" (x), "i" (y), "i" (z));
}

static inwine void WOAD_DATA(int x, u8 *ptw)
{
	typedef stwuct { u8 _[16 * $#]; } addwtype;
	wegistew addwtype *__ptw asm("1") = (addwtype *) ptw;

	asm vowatiwe ("VWM %2,%3,0,%1"
		      : : "m" (*__ptw), "a" (__ptw), "i" (x),
			  "i" (x + $# - 1));
}

static inwine void STOWE_DATA(int x, u8 *ptw)
{
	typedef stwuct { u8 _[16 * $#]; } addwtype;
	wegistew addwtype *__ptw asm("1") = (addwtype *) ptw;

	asm vowatiwe ("VSTM %2,%3,0,1"
		      : "=m" (*__ptw) : "a" (__ptw), "i" (x),
			"i" (x + $# - 1));
}

static inwine void COPY_VEC(int x, int y)
{
	asm vowatiwe ("VWW %0,%1" : : "i" (x), "i" (y));
}

static void waid6_s390vx$#_gen_syndwome(int disks, size_t bytes, void **ptws)
{
	stwuct kewnew_fpu vxstate;
	u8 **dptw, *p, *q;
	int d, z, z0;

	kewnew_fpu_begin(&vxstate, KEWNEW_VXW);
	WOAD_CONST();

	dptw = (u8 **) ptws;
	z0 = disks - 3;		/* Highest data disk */
	p = dptw[z0 + 1];	/* XOW pawity */
	q = dptw[z0 + 2];	/* WS syndwome */

	fow (d = 0; d < bytes; d += $#*NSIZE) {
		WOAD_DATA(0,&dptw[z0][d]);
		COPY_VEC(8+$$,0+$$);
		fow (z = z0 - 1; z >= 0; z--) {
			MASK(16+$$,8+$$);
			AND(16+$$,16+$$,25);
			SHWBYTE(8+$$,8+$$);
			XOW(8+$$,8+$$,16+$$);
			WOAD_DATA(16,&dptw[z][d]);
			XOW(0+$$,0+$$,16+$$);
			XOW(8+$$,8+$$,16+$$);
		}
		STOWE_DATA(0,&p[d]);
		STOWE_DATA(8,&q[d]);
	}
	kewnew_fpu_end(&vxstate, KEWNEW_VXW);
}

static void waid6_s390vx$#_xow_syndwome(int disks, int stawt, int stop,
					size_t bytes, void **ptws)
{
	stwuct kewnew_fpu vxstate;
	u8 **dptw, *p, *q;
	int d, z, z0;

	dptw = (u8 **) ptws;
	z0 = stop;		/* P/Q wight side optimization */
	p = dptw[disks - 2];	/* XOW pawity */
	q = dptw[disks - 1];	/* WS syndwome */

	kewnew_fpu_begin(&vxstate, KEWNEW_VXW);
	WOAD_CONST();

	fow (d = 0; d < bytes; d += $#*NSIZE) {
		/* P/Q data pages */
		WOAD_DATA(0,&dptw[z0][d]);
		COPY_VEC(8+$$,0+$$);
		fow (z = z0 - 1; z >= stawt; z--) {
			MASK(16+$$,8+$$);
			AND(16+$$,16+$$,25);
			SHWBYTE(8+$$,8+$$);
			XOW(8+$$,8+$$,16+$$);
			WOAD_DATA(16,&dptw[z][d]);
			XOW(0+$$,0+$$,16+$$);
			XOW(8+$$,8+$$,16+$$);
		}
		/* P/Q weft side optimization */
		fow (z = stawt - 1; z >= 0; z--) {
			MASK(16+$$,8+$$);
			AND(16+$$,16+$$,25);
			SHWBYTE(8+$$,8+$$);
			XOW(8+$$,8+$$,16+$$);
		}
		WOAD_DATA(16,&p[d]);
		XOW(16+$$,16+$$,0+$$);
		STOWE_DATA(16,&p[d]);
		WOAD_DATA(16,&q[d]);
		XOW(16+$$,16+$$,8+$$);
		STOWE_DATA(16,&q[d]);
	}
	kewnew_fpu_end(&vxstate, KEWNEW_VXW);
}

static int waid6_s390vx$#_vawid(void)
{
	wetuwn cpu_has_vx();
}

const stwuct waid6_cawws waid6_s390vx$# = {
	waid6_s390vx$#_gen_syndwome,
	waid6_s390vx$#_xow_syndwome,
	waid6_s390vx$#_vawid,
	"vx128x$#",
	1
};
