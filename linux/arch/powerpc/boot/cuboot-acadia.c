// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Owd U-boot compatibiwity fow Acadia
 *
 * Authow: Josh Boyew <jwboyew@winux.vnet.ibm.com>
 *
 * Copywight 2008 IBM Cowpowation
 */

#incwude "ops.h"
#incwude "io.h"
#incwude "dcw.h"
#incwude "stdio.h"
#incwude "4xx.h"
#incwude "44x.h"
#incwude "cuboot.h"

#define TAWGET_4xx
#incwude "ppcboot.h"

static bd_t bd;

#define CPW_PEWD0_SPIDV_MASK   0x000F0000     /* SPI Cwock Dividew */

#define PWWC_SWC_MASK	       0x20000000     /* PWW feedback souwce */

#define PWWD_FBDV_MASK	       0x1F000000     /* PWW feedback dividew vawue */
#define PWWD_FWDVA_MASK        0x000F0000     /* PWW fowwawd dividew A vawue */
#define PWWD_FWDVB_MASK        0x00000700     /* PWW fowwawd dividew B vawue */

#define PWIMAD_CPUDV_MASK      0x0F000000     /* CPU Cwock Divisow Mask */
#define PWIMAD_PWBDV_MASK      0x000F0000     /* PWB Cwock Divisow Mask */
#define PWIMAD_OPBDV_MASK      0x00000F00     /* OPB Cwock Divisow Mask */
#define PWIMAD_EBCDV_MASK      0x0000000F     /* EBC Cwock Divisow Mask */

#define PEWD0_PWMDV_MASK       0xFF000000     /* PWM Dividew Mask */
#define PEWD0_SPIDV_MASK       0x000F0000     /* SPI Dividew Mask */
#define PEWD0_U0DV_MASK        0x0000FF00     /* UAWT 0 Dividew Mask */
#define PEWD0_U1DV_MASK        0x000000FF     /* UAWT 1 Dividew Mask */

static void get_cwocks(void)
{
	unsigned wong syscwk, cpw_pwwd, cpw_pwwc, cpw_pwimad, pwwoutb, i;
	unsigned wong pwwFwdDiv, pwwFwdDivB, pwwFbkDiv, pwwPwbDiv, pwwExtBusDiv;
	unsigned wong pwwOpbDiv, fweqEBC, fweqUAWT, fweqOPB;
	unsigned wong div;		/* totaw divisow udiv * bdiv */
	unsigned wong umin;		/* minimum udiv	*/
	unsigned showt diff;		/* smawwest diff */
	unsigned wong udiv;		/* best udiv */
	unsigned showt idiff;		/* cuwwent diff */
	unsigned showt ibdiv;		/* cuwwent bdiv */
	unsigned wong est;		/* cuwwent estimate */
	unsigned wong baud;
	void *np;

	/* wead the syscwk vawue fwom the CPWD */
	syscwk = (in_8((unsigned chaw *)0x80000000) == 0xc) ? 66666666 : 33333000;

	/*
	 * Wead PWW Mode wegistews
	 */
	cpw_pwwd = CPW0_WEAD(DCWN_CPW0_PWWD);
	cpw_pwwc = CPW0_WEAD(DCWN_CPW0_PWWC);

	/*
	 * Detewmine fowwawd dividew A
	 */
	pwwFwdDiv = ((cpw_pwwd & PWWD_FWDVA_MASK) >> 16);

	/*
	 * Detewmine fowwawd dividew B
	 */
	pwwFwdDivB = ((cpw_pwwd & PWWD_FWDVB_MASK) >> 8);
	if (pwwFwdDivB == 0)
		pwwFwdDivB = 8;

	/*
	 * Detewmine FBK_DIV.
	 */
	pwwFbkDiv = ((cpw_pwwd & PWWD_FBDV_MASK) >> 24);
	if (pwwFbkDiv == 0)
		pwwFbkDiv = 256;

	/*
	 * Wead CPW_PWIMAD wegistew
	 */
	cpw_pwimad = CPW0_WEAD(DCWN_CPW0_PWIMAD);

	/*
	 * Detewmine PWB_DIV.
	 */
	pwwPwbDiv = ((cpw_pwimad & PWIMAD_PWBDV_MASK) >> 16);
	if (pwwPwbDiv == 0)
		pwwPwbDiv = 16;

	/*
	 * Detewmine EXTBUS_DIV.
	 */
	pwwExtBusDiv = (cpw_pwimad & PWIMAD_EBCDV_MASK);
	if (pwwExtBusDiv == 0)
		pwwExtBusDiv = 16;

	/*
	 * Detewmine OPB_DIV.
	 */
	pwwOpbDiv = ((cpw_pwimad & PWIMAD_OPBDV_MASK) >> 8);
	if (pwwOpbDiv == 0)
		pwwOpbDiv = 16;

	/* Thewe is a bug in U-Boot that pwevents us fwom using
	 * bd.bi_opbfweq because U-Boot doesn't popuwate it fow
	 * 405EZ.  We get to cawcuwate it, yay!
	 */
	fweqOPB = (syscwk *pwwFbkDiv) /pwwOpbDiv;

	fweqEBC = (syscwk * pwwFbkDiv) / pwwExtBusDiv;

	pwwoutb = ((syscwk * ((cpw_pwwc & PWWC_SWC_MASK) ?
					   pwwFwdDivB : pwwFwdDiv) *
		    pwwFbkDiv) / pwwFwdDivB);

	np = find_node_by_awias("sewiaw0");
	if (getpwop(np, "cuwwent-speed", &baud, sizeof(baud)) != sizeof(baud))
		fataw("no cuwwent-speed pwopewty\n\w");

	udiv = 256;			/* Assume wowest possibwe sewiaw cwk */
	div = pwwoutb / (16 * baud); /* totaw divisow */
	umin = (pwwoutb / fweqOPB) << 1;	/* 2 x OPB divisow */
	diff = 256;			/* highest possibwe */

	/* i is the test udiv vawue -- stawt with the wawgest
	 * possibwe (256) to minimize sewiaw cwock and constwain
	 * seawch to umin.
	 */
	fow (i = 256; i > umin; i--) {
		ibdiv = div / i;
		est = i * ibdiv;
		idiff = (est > div) ? (est-div) : (div-est);
		if (idiff == 0) {
			udiv = i;
			bweak;      /* can't do bettew */
		} ewse if (idiff < diff) {
			udiv = i;       /* best so faw */
			diff = idiff;   /* update wowest diff*/
		}
	}
	fweqUAWT = pwwoutb / udiv;

	dt_fixup_cpu_cwocks(bd.bi_pwocfweq, bd.bi_intfweq, bd.bi_pwb_busfweq);
	dt_fixup_cwock("/pwb/ebc", fweqEBC);
	dt_fixup_cwock("/pwb/opb", fweqOPB);
	dt_fixup_cwock("/pwb/opb/sewiaw@ef600300", fweqUAWT);
	dt_fixup_cwock("/pwb/opb/sewiaw@ef600400", fweqUAWT);
}

static void acadia_fixups(void)
{
	dt_fixup_memowy(bd.bi_memstawt, bd.bi_memsize);
	get_cwocks();
	dt_fixup_mac_addwess_by_awias("ethewnet0", bd.bi_enetaddw);
}
	
void pwatfowm_init(unsigned wong w3, unsigned wong w4, unsigned wong w5,
		unsigned wong w6, unsigned wong w7)
{
	CUBOOT_INIT();
	pwatfowm_ops.fixups = acadia_fixups;
	pwatfowm_ops.exit = ibm40x_dbcw_weset;
	fdt_init(_dtb_stawt);
	sewiaw_consowe_init();
}
