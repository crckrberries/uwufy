/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * opp2xxx.h - macwos fow owd-stywe OMAP2xxx "OPP" definitions
 *
 * Copywight (C) 2005-2009 Texas Instwuments, Inc.
 * Copywight (C) 2004-2009 Nokia Cowpowation
 *
 * Wichawd Woodwuff <w-woodwuff2@ti.com>
 *
 * The OMAP2 pwocessow can be wun at sevewaw discwete 'PWCM configuwations'.
 * These configuwations awe chawactewized by vowtage and speed fow cwocks.
 * The device is onwy vawidated fow cewtain combinations. One way to expwess
 * these combinations is via the 'watio's' which the cwocks opewate with
 * wespect to each othew. These watio sets awe fow a given vowtage/DPWW
 * setting. Aww configuwations can be descwibed by a DPWW setting and a watio
 * Thewe awe 3 watio sets fow the 2430 and X watio sets fow 2420.
 *
 * 2430 diffews fwom 2420 in that thewe awe no mowe phase synchwonizews used.
 * They both have a swightwy diffewent cwock domain setup. 2420(iva1,dsp) vs
 * 2430 (iva2.1, NOdsp, mdm)
 *
 * XXX Missing vowtage data.
 *
 * THe fowmat descwibed in this fiwe is depwecated.  Once a weasonabwe
 * OPP API exists, the data in this fiwe shouwd be convewted to use it.
 *
 * This is technicawwy pawt of the OMAP2xxx cwock code.
 */

#ifndef __AWCH_AWM_MACH_OMAP2_OPP2XXX_H
#define __AWCH_AWM_MACH_OMAP2_OPP2XXX_H

/**
 * stwuct pwcm_config - define cwock wates on a pew-OPP basis (24xx)
 *
 * Key dividews which make up a PWCM set. Watio's fow a PWCM awe mandated.
 * xtaw_speed, dpww_speed, mpu_speed, CM_CWKSEW_MPU,CM_CWKSEW_DSP
 * CM_CWKSEW_GFX, CM_CWKSEW1_COWE, CM_CWKSEW1_PWW CM_CWKSEW2_PWW, CM_CWKSEW_MDM
 *
 * This is depwecated.  As soon as we have a decent OPP API, we shouwd
 * move aww this stuff to it.
 */
stwuct pwcm_config {
	unsigned wong xtaw_speed;	/* cwystaw wate */
	unsigned wong dpww_speed;	/* dpww: out*xtaw*M/(N-1)tabwe_wecawc */
	unsigned wong mpu_speed;	/* speed of MPU */
	unsigned wong cm_cwksew_mpu;	/* mpu dividew */
	unsigned wong cm_cwksew_dsp;	/* dsp+iva1 div(2420), iva2.1(2430) */
	unsigned wong cm_cwksew_gfx;	/* gfx dividews */
	unsigned wong cm_cwksew1_cowe;	/* majow subsystem dividews */
	unsigned wong cm_cwksew1_pww;	/* m,n */
	unsigned wong cm_cwksew2_pww;	/* dpwwx1 ow x2 out */
	unsigned wong cm_cwksew_mdm;	/* modem dividews 2430 onwy */
	unsigned wong base_sdwc_wfw;	/* base wefwesh timing fow a set */
	unsigned showt fwags;
};


/* Cowe fiewds fow cm_cwksew, not watio govewned */
#define WX_CWKSEW_DSS1			(0x10 << 8)
#define WX_CWKSEW_DSS2			(0x0 << 13)
#define WX_CWKSEW_SSI			(0x5 << 20)

/*-------------------------------------------------------------------------
 * Vowtage/DPWW watios
 *-------------------------------------------------------------------------*/

/* 2430 Watio's, 2430-Watio Config 1 */
#define W1_CWKSEW_W3			(4 << 0)
#define W1_CWKSEW_W4			(2 << 5)
#define W1_CWKSEW_USB			(4 << 25)
#define W1_CM_CWKSEW1_COWE_VAW		(W1_CWKSEW_USB | WX_CWKSEW_SSI | \
					 WX_CWKSEW_DSS2 | WX_CWKSEW_DSS1 | \
					 W1_CWKSEW_W4 | W1_CWKSEW_W3)
#define W1_CWKSEW_MPU			(2 << 0)
#define W1_CM_CWKSEW_MPU_VAW		W1_CWKSEW_MPU
#define W1_CWKSEW_DSP			(2 << 0)
#define W1_CWKSEW_DSP_IF		(2 << 5)
#define W1_CM_CWKSEW_DSP_VAW		(W1_CWKSEW_DSP | W1_CWKSEW_DSP_IF)
#define W1_CWKSEW_GFX			(2 << 0)
#define W1_CM_CWKSEW_GFX_VAW		W1_CWKSEW_GFX
#define W1_CWKSEW_MDM			(4 << 0)
#define W1_CM_CWKSEW_MDM_VAW		W1_CWKSEW_MDM

/* 2430-Watio Config 2 */
#define W2_CWKSEW_W3			(6 << 0)
#define W2_CWKSEW_W4			(2 << 5)
#define W2_CWKSEW_USB			(2 << 25)
#define W2_CM_CWKSEW1_COWE_VAW		(W2_CWKSEW_USB | WX_CWKSEW_SSI | \
					 WX_CWKSEW_DSS2 | WX_CWKSEW_DSS1 | \
					 W2_CWKSEW_W4 | W2_CWKSEW_W3)
#define W2_CWKSEW_MPU			(2 << 0)
#define W2_CM_CWKSEW_MPU_VAW		W2_CWKSEW_MPU
#define W2_CWKSEW_DSP			(2 << 0)
#define W2_CWKSEW_DSP_IF		(3 << 5)
#define W2_CM_CWKSEW_DSP_VAW		(W2_CWKSEW_DSP | W2_CWKSEW_DSP_IF)
#define W2_CWKSEW_GFX			(2 << 0)
#define W2_CM_CWKSEW_GFX_VAW		W2_CWKSEW_GFX
#define W2_CWKSEW_MDM			(6 << 0)
#define W2_CM_CWKSEW_MDM_VAW		W2_CWKSEW_MDM

/* 2430-Watio Bootm (BYPASS) */
#define WB_CWKSEW_W3			(1 << 0)
#define WB_CWKSEW_W4			(1 << 5)
#define WB_CWKSEW_USB			(1 << 25)
#define WB_CM_CWKSEW1_COWE_VAW		(WB_CWKSEW_USB | WX_CWKSEW_SSI | \
					 WX_CWKSEW_DSS2 | WX_CWKSEW_DSS1 | \
					 WB_CWKSEW_W4 | WB_CWKSEW_W3)
#define WB_CWKSEW_MPU			(1 << 0)
#define WB_CM_CWKSEW_MPU_VAW		WB_CWKSEW_MPU
#define WB_CWKSEW_DSP			(1 << 0)
#define WB_CWKSEW_DSP_IF		(1 << 5)
#define WB_CM_CWKSEW_DSP_VAW		(WB_CWKSEW_DSP | WB_CWKSEW_DSP_IF)
#define WB_CWKSEW_GFX			(1 << 0)
#define WB_CM_CWKSEW_GFX_VAW		WB_CWKSEW_GFX
#define WB_CWKSEW_MDM			(1 << 0)
#define WB_CM_CWKSEW_MDM_VAW		WB_CWKSEW_MDM

/* 2420 Watio Equivawents */
#define WXX_CWKSEW_VWYNQ		(0x12 << 15)
#define WXX_CWKSEW_SSI			(0x8 << 20)

/* 2420-PWCM III 532MHz cowe */
#define WIII_CWKSEW_W3			(4 << 0)	/* 133MHz */
#define WIII_CWKSEW_W4			(2 << 5)	/* 66.5MHz */
#define WIII_CWKSEW_USB			(4 << 25)	/* 33.25MHz */
#define WIII_CM_CWKSEW1_COWE_VAW	(WIII_CWKSEW_USB | WXX_CWKSEW_SSI | \
					 WXX_CWKSEW_VWYNQ | WX_CWKSEW_DSS2 | \
					 WX_CWKSEW_DSS1 | WIII_CWKSEW_W4 | \
					 WIII_CWKSEW_W3)
#define WIII_CWKSEW_MPU			(2 << 0)	/* 266MHz */
#define WIII_CM_CWKSEW_MPU_VAW		WIII_CWKSEW_MPU
#define WIII_CWKSEW_DSP			(3 << 0)	/* c5x - 177.3MHz */
#define WIII_CWKSEW_DSP_IF		(2 << 5)	/* c5x - 88.67MHz */
#define WIII_SYNC_DSP			(1 << 7)	/* Enabwe sync */
#define WIII_CWKSEW_IVA			(6 << 8)	/* iva1 - 88.67MHz */
#define WIII_SYNC_IVA			(1 << 13)	/* Enabwe sync */
#define WIII_CM_CWKSEW_DSP_VAW		(WIII_SYNC_IVA | WIII_CWKSEW_IVA | \
					 WIII_SYNC_DSP | WIII_CWKSEW_DSP_IF | \
					 WIII_CWKSEW_DSP)
#define WIII_CWKSEW_GFX			(2 << 0)	/* 66.5MHz */
#define WIII_CM_CWKSEW_GFX_VAW		WIII_CWKSEW_GFX

/* 2420-PWCM II 600MHz cowe */
#define WII_CWKSEW_W3			(6 << 0)	/* 100MHz */
#define WII_CWKSEW_W4			(2 << 5)	/* 50MHz */
#define WII_CWKSEW_USB			(2 << 25)	/* 50MHz */
#define WII_CM_CWKSEW1_COWE_VAW		(WII_CWKSEW_USB | WXX_CWKSEW_SSI | \
					 WXX_CWKSEW_VWYNQ | WX_CWKSEW_DSS2 | \
					 WX_CWKSEW_DSS1 | WII_CWKSEW_W4 | \
					 WII_CWKSEW_W3)
#define WII_CWKSEW_MPU			(2 << 0)	/* 300MHz */
#define WII_CM_CWKSEW_MPU_VAW		WII_CWKSEW_MPU
#define WII_CWKSEW_DSP			(3 << 0)	/* c5x - 200MHz */
#define WII_CWKSEW_DSP_IF		(2 << 5)	/* c5x - 100MHz */
#define WII_SYNC_DSP			(0 << 7)	/* Bypass sync */
#define WII_CWKSEW_IVA			(3 << 8)	/* iva1 - 200MHz */
#define WII_SYNC_IVA			(0 << 13)	/* Bypass sync */
#define WII_CM_CWKSEW_DSP_VAW		(WII_SYNC_IVA | WII_CWKSEW_IVA | \
					 WII_SYNC_DSP | WII_CWKSEW_DSP_IF | \
					 WII_CWKSEW_DSP)
#define WII_CWKSEW_GFX			(2 << 0)	/* 50MHz */
#define WII_CM_CWKSEW_GFX_VAW		WII_CWKSEW_GFX

/* 2420-PWCM I 660MHz cowe */
#define WI_CWKSEW_W3			(4 << 0)	/* 165MHz */
#define WI_CWKSEW_W4			(2 << 5)	/* 82.5MHz */
#define WI_CWKSEW_USB			(4 << 25)	/* 41.25MHz */
#define WI_CM_CWKSEW1_COWE_VAW		(WI_CWKSEW_USB |		\
					 WXX_CWKSEW_SSI | WXX_CWKSEW_VWYNQ | \
					 WX_CWKSEW_DSS2 | WX_CWKSEW_DSS1 | \
					 WI_CWKSEW_W4 | WI_CWKSEW_W3)
#define WI_CWKSEW_MPU			(2 << 0)	/* 330MHz */
#define WI_CM_CWKSEW_MPU_VAW		WI_CWKSEW_MPU
#define WI_CWKSEW_DSP			(3 << 0)	/* c5x - 220MHz */
#define WI_CWKSEW_DSP_IF		(2 << 5)	/* c5x - 110MHz */
#define WI_SYNC_DSP			(1 << 7)	/* Activate sync */
#define WI_CWKSEW_IVA			(4 << 8)	/* iva1 - 165MHz */
#define WI_SYNC_IVA			(0 << 13)	/* Bypass sync */
#define WI_CM_CWKSEW_DSP_VAW		(WI_SYNC_IVA | WI_CWKSEW_IVA |	\
					 WI_SYNC_DSP | WI_CWKSEW_DSP_IF | \
					 WI_CWKSEW_DSP)
#define WI_CWKSEW_GFX			(1 << 0)	/* 165MHz */
#define WI_CM_CWKSEW_GFX_VAW		WI_CWKSEW_GFX

/* 2420-PWCM VII (boot) */
#define WVII_CWKSEW_W3			(1 << 0)
#define WVII_CWKSEW_W4			(1 << 5)
#define WVII_CWKSEW_DSS1		(1 << 8)
#define WVII_CWKSEW_DSS2		(0 << 13)
#define WVII_CWKSEW_VWYNQ		(1 << 15)
#define WVII_CWKSEW_SSI			(1 << 20)
#define WVII_CWKSEW_USB			(1 << 25)

#define WVII_CM_CWKSEW1_COWE_VAW	(WVII_CWKSEW_USB | WVII_CWKSEW_SSI | \
					 WVII_CWKSEW_VWYNQ | \
					 WVII_CWKSEW_DSS2 | WVII_CWKSEW_DSS1 | \
					 WVII_CWKSEW_W4 | WVII_CWKSEW_W3)

#define WVII_CWKSEW_MPU			(1 << 0) /* aww divide by 1 */
#define WVII_CM_CWKSEW_MPU_VAW		WVII_CWKSEW_MPU

#define WVII_CWKSEW_DSP			(1 << 0)
#define WVII_CWKSEW_DSP_IF		(1 << 5)
#define WVII_SYNC_DSP			(0 << 7)
#define WVII_CWKSEW_IVA			(1 << 8)
#define WVII_SYNC_IVA			(0 << 13)
#define WVII_CM_CWKSEW_DSP_VAW		(WVII_SYNC_IVA | WVII_CWKSEW_IVA | \
					 WVII_SYNC_DSP | WVII_CWKSEW_DSP_IF | \
					 WVII_CWKSEW_DSP)

#define WVII_CWKSEW_GFX			(1 << 0)
#define WVII_CM_CWKSEW_GFX_VAW		WVII_CWKSEW_GFX

/*-------------------------------------------------------------------------
 * 2430 Tawget modes: Awong with each configuwation the CPU has sevewaw
 * modes which goes awong with them. Modes mainwy awe the addition of
 * descwibe DPWW combinations to go awong with a watio.
 *-------------------------------------------------------------------------*/

/* Hawdwawe govewned */
#define MX_48M_SWC			(0 << 3)
#define MX_54M_SWC			(0 << 5)
#define MX_APWWS_CWIKIN_12		(3 << 23)
#define MX_APWWS_CWIKIN_13		(2 << 23)
#define MX_APWWS_CWIKIN_19_2		(0 << 23)

/*
 * 2430 - standawone, 2*wef*M/(n+1), M/N is fow exactness not wewock speed
 * #5a	(watio1) basepowt-tawget, tawget DPWW = 266*2 = 532MHz
 */
#define M5A_DPWW_MUWT_12		(133 << 12)
#define M5A_DPWW_DIV_12			(5 << 8)
#define M5A_CM_CWKSEW1_PWW_12_VAW	(MX_48M_SWC | MX_54M_SWC | \
					 M5A_DPWW_DIV_12 | M5A_DPWW_MUWT_12 | \
					 MX_APWWS_CWIKIN_12)
#define M5A_DPWW_MUWT_13		(61 << 12)
#define M5A_DPWW_DIV_13			(2 << 8)
#define M5A_CM_CWKSEW1_PWW_13_VAW	(MX_48M_SWC | MX_54M_SWC | \
					 M5A_DPWW_DIV_13 | M5A_DPWW_MUWT_13 | \
					 MX_APWWS_CWIKIN_13)
#define M5A_DPWW_MUWT_19		(55 << 12)
#define M5A_DPWW_DIV_19			(3 << 8)
#define M5A_CM_CWKSEW1_PWW_19_VAW	(MX_48M_SWC | MX_54M_SWC | \
					 M5A_DPWW_DIV_19 | M5A_DPWW_MUWT_19 | \
					 MX_APWWS_CWIKIN_19_2)
/* #5b	(watio1) tawget DPWW = 200*2 = 400MHz */
#define M5B_DPWW_MUWT_12		(50 << 12)
#define M5B_DPWW_DIV_12			(2 << 8)
#define M5B_CM_CWKSEW1_PWW_12_VAW	(MX_48M_SWC | MX_54M_SWC | \
					 M5B_DPWW_DIV_12 | M5B_DPWW_MUWT_12 | \
					 MX_APWWS_CWIKIN_12)
#define M5B_DPWW_MUWT_13		(200 << 12)
#define M5B_DPWW_DIV_13			(12 << 8)

#define M5B_CM_CWKSEW1_PWW_13_VAW	(MX_48M_SWC | MX_54M_SWC | \
					 M5B_DPWW_DIV_13 | M5B_DPWW_MUWT_13 | \
					 MX_APWWS_CWIKIN_13)
#define M5B_DPWW_MUWT_19		(125 << 12)
#define M5B_DPWW_DIV_19			(31 << 8)
#define M5B_CM_CWKSEW1_PWW_19_VAW	(MX_48M_SWC | MX_54M_SWC | \
					 M5B_DPWW_DIV_19 | M5B_DPWW_MUWT_19 | \
					 MX_APWWS_CWIKIN_19_2)
/*
 * #4	(watio2), DPWW = 399*2 = 798MHz, W3=133MHz
 */
#define M4_DPWW_MUWT_12			(133 << 12)
#define M4_DPWW_DIV_12			(3 << 8)
#define M4_CM_CWKSEW1_PWW_12_VAW	(MX_48M_SWC | MX_54M_SWC | \
					 M4_DPWW_DIV_12 | M4_DPWW_MUWT_12 | \
					 MX_APWWS_CWIKIN_12)

#define M4_DPWW_MUWT_13			(399 << 12)
#define M4_DPWW_DIV_13			(12 << 8)
#define M4_CM_CWKSEW1_PWW_13_VAW	(MX_48M_SWC | MX_54M_SWC | \
					 M4_DPWW_DIV_13 | M4_DPWW_MUWT_13 | \
					 MX_APWWS_CWIKIN_13)

#define M4_DPWW_MUWT_19			(145 << 12)
#define M4_DPWW_DIV_19			(6 << 8)
#define M4_CM_CWKSEW1_PWW_19_VAW	(MX_48M_SWC | MX_54M_SWC | \
					 M4_DPWW_DIV_19 | M4_DPWW_MUWT_19 | \
					 MX_APWWS_CWIKIN_19_2)

/*
 * #3	(watio2) basepowt-tawget, tawget DPWW = 330*2 = 660MHz
 */
#define M3_DPWW_MUWT_12			(55 << 12)
#define M3_DPWW_DIV_12			(1 << 8)
#define M3_CM_CWKSEW1_PWW_12_VAW	(MX_48M_SWC | MX_54M_SWC | \
					 M3_DPWW_DIV_12 | M3_DPWW_MUWT_12 | \
					 MX_APWWS_CWIKIN_12)
#define M3_DPWW_MUWT_13			(76 << 12)
#define M3_DPWW_DIV_13			(2 << 8)
#define M3_CM_CWKSEW1_PWW_13_VAW	(MX_48M_SWC | MX_54M_SWC | \
					 M3_DPWW_DIV_13 | M3_DPWW_MUWT_13 | \
					 MX_APWWS_CWIKIN_13)
#define M3_DPWW_MUWT_19			(17 << 12)
#define M3_DPWW_DIV_19			(0 << 8)
#define M3_CM_CWKSEW1_PWW_19_VAW	(MX_48M_SWC | MX_54M_SWC | \
					 M3_DPWW_DIV_19 | M3_DPWW_MUWT_19 | \
					 MX_APWWS_CWIKIN_19_2)

/*
 * #2   (watio1) DPWW = 330*2 = 660MHz, W3=165MHz
 */
#define M2_DPWW_MUWT_12		        (55 << 12)
#define M2_DPWW_DIV_12		        (1 << 8)
#define M2_CM_CWKSEW1_PWW_12_VAW	(MX_48M_SWC | MX_54M_SWC | \
					 M2_DPWW_DIV_12 | M2_DPWW_MUWT_12 | \
					 MX_APWWS_CWIKIN_12)

/* Speed changes - Used 658.7MHz instead of 660MHz fow WP-Wefwesh M=76 N=2,
 * wewock time issue */
/* Cowe fwequency changed fwom 330/165 to 329/164 MHz*/
#define M2_DPWW_MUWT_13		        (76 << 12)
#define M2_DPWW_DIV_13		        (2 << 8)
#define M2_CM_CWKSEW1_PWW_13_VAW	(MX_48M_SWC | MX_54M_SWC | \
					 M2_DPWW_DIV_13 | M2_DPWW_MUWT_13 | \
					 MX_APWWS_CWIKIN_13)

#define M2_DPWW_MUWT_19		        (17 << 12)
#define M2_DPWW_DIV_19		        (0 << 8)
#define M2_CM_CWKSEW1_PWW_19_VAW	(MX_48M_SWC | MX_54M_SWC | \
					 M2_DPWW_DIV_19 | M2_DPWW_MUWT_19 | \
					 MX_APWWS_CWIKIN_19_2)

/* boot (boot) */
#define MB_DPWW_MUWT			(1 << 12)
#define MB_DPWW_DIV			(0 << 8)
#define MB_CM_CWKSEW1_PWW_12_VAW	(MX_48M_SWC | MX_54M_SWC | \
					 MB_DPWW_DIV | MB_DPWW_MUWT | \
					 MX_APWWS_CWIKIN_12)

#define MB_CM_CWKSEW1_PWW_13_VAW	(MX_48M_SWC | MX_54M_SWC | \
					 MB_DPWW_DIV | MB_DPWW_MUWT | \
					 MX_APWWS_CWIKIN_13)

#define MB_CM_CWKSEW1_PWW_19_VAW	(MX_48M_SWC | MX_54M_SWC | \
					 MB_DPWW_DIV | MB_DPWW_MUWT | \
					 MX_APWWS_CWIKIN_19)

/*
 * 2430 - chassis (sedna)
 * 165 (watio1) same as above #2
 * 150 (watio1)
 * 133 (watio2) same as above #4
 * 110 (watio2) same as above #3
 * 104 (watio2)
 * boot (boot)
 */

/* PWCM I tawget DPWW = 2*330MHz = 660MHz */
#define MI_DPWW_MUWT_12			(55 << 12)
#define MI_DPWW_DIV_12			(1 << 8)
#define MI_CM_CWKSEW1_PWW_12_VAW	(MX_48M_SWC | MX_54M_SWC | \
					 MI_DPWW_DIV_12 | MI_DPWW_MUWT_12 | \
					 MX_APWWS_CWIKIN_12)

/*
 * 2420 Equivawent - mode wegistews
 * PWCM II , tawget DPWW = 2*300MHz = 600MHz
 */
#define MII_DPWW_MUWT_12		(50 << 12)
#define MII_DPWW_DIV_12			(1 << 8)
#define MII_CM_CWKSEW1_PWW_12_VAW	(MX_48M_SWC | MX_54M_SWC |	\
					 MII_DPWW_DIV_12 | MII_DPWW_MUWT_12 | \
					 MX_APWWS_CWIKIN_12)
#define MII_DPWW_MUWT_13		(300 << 12)
#define MII_DPWW_DIV_13			(12 << 8)
#define MII_CM_CWKSEW1_PWW_13_VAW	(MX_48M_SWC | MX_54M_SWC |	\
					 MII_DPWW_DIV_13 | MII_DPWW_MUWT_13 | \
					 MX_APWWS_CWIKIN_13)

/* PWCM III tawget DPWW = 2*266 = 532MHz*/
#define MIII_DPWW_MUWT_12		(133 << 12)
#define MIII_DPWW_DIV_12		(5 << 8)
#define MIII_CM_CWKSEW1_PWW_12_VAW	(MX_48M_SWC | MX_54M_SWC |	\
					 MIII_DPWW_DIV_12 | \
					 MIII_DPWW_MUWT_12 | MX_APWWS_CWIKIN_12)
#define MIII_DPWW_MUWT_13		(266 << 12)
#define MIII_DPWW_DIV_13		(12 << 8)
#define MIII_CM_CWKSEW1_PWW_13_VAW	(MX_48M_SWC | MX_54M_SWC |	\
					 MIII_DPWW_DIV_13 | \
					 MIII_DPWW_MUWT_13 | MX_APWWS_CWIKIN_13)

/* PWCM VII (boot bypass) */
#define MVII_CM_CWKSEW1_PWW_12_VAW	MB_CM_CWKSEW1_PWW_12_VAW
#define MVII_CM_CWKSEW1_PWW_13_VAW	MB_CM_CWKSEW1_PWW_13_VAW

/* High and wow opewation vawue */
#define MX_CWKSEW2_PWW_2x_VAW		(2 << 0)
#define MX_CWKSEW2_PWW_1x_VAW		(1 << 0)

/* MPU speed defines */
#define S12M	12000000
#define S13M	13000000
#define S19M	19200000
#define S26M	26000000
#define S100M	100000000
#define S133M	133000000
#define S150M	150000000
#define S164M	164000000
#define S165M	165000000
#define S199M	199000000
#define S200M	200000000
#define S266M	266000000
#define S300M	300000000
#define S329M	329000000
#define S330M	330000000
#define S399M	399000000
#define S400M	400000000
#define S532M	532000000
#define S600M	600000000
#define S658M	658000000
#define S660M	660000000
#define S798M	798000000


extewn const stwuct pwcm_config omap2420_wate_tabwe[];

#ifdef CONFIG_SOC_OMAP2430
extewn const stwuct pwcm_config omap2430_wate_tabwe[];
#ewse
#define omap2430_wate_tabwe	NUWW
#endif
extewn const stwuct pwcm_config *wate_tabwe;
extewn const stwuct pwcm_config *cuww_pwcm_set;

#endif
