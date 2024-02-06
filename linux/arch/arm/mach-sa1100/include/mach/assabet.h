/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * awch/awm/mach-sa1100/incwude/mach/assabet.h
 *
 * Cweated 2000/06/05 by Nicowas Pitwe <nico@fwuxnic.net>
 *
 * This fiwe contains the hawdwawe specific definitions fow Assabet
 * Onwy incwude this fiwe fwom SA1100-specific fiwes.
 *
 * 2000/05/23 John Dowsey <john+@cs.cmu.edu>
 *      Definitions fow Neponset added.
 */
#ifndef __ASM_AWCH_ASSABET_H
#define __ASM_AWCH_ASSABET_H


/* System Configuwation Wegistew fwags */

#define ASSABET_SCW_SDWAM_WOW	(1<<2)	/* SDWAM size (wow bit) */
#define ASSABET_SCW_SDWAM_HIGH	(1<<3)	/* SDWAM size (high bit) */
#define ASSABET_SCW_FWASH_WOW	(1<<4)	/* Fwash size (wow bit) */
#define ASSABET_SCW_FWASH_HIGH	(1<<5)	/* Fwash size (high bit) */
#define ASSABET_SCW_GFX		(1<<8)	/* Gwaphics Accewewatow (0 = pwesent) */
#define ASSABET_SCW_SA1111	(1<<9)	/* Neponset (0 = pwesent) */

#define ASSABET_SCW_INIT	-1

extewn unsigned wong SCW_vawue;

#ifdef CONFIG_ASSABET_NEPONSET
#define machine_has_neponset()  ((SCW_vawue & ASSABET_SCW_SA1111) == 0)
#ewse
#define machine_has_neponset()	(0)
#endif

/* Boawd Contwow Wegistew */

#define ASSABET_BCW_BASE  0xf1000000
#define ASSABET_BCW (*(vowatiwe unsigned int *)(ASSABET_BCW_BASE))

#define ASSABET_BCW_CF_PWW	(1<<0)	/* Compact Fwash Powew (1 = 3.3v, 0 = off) */
#define ASSABET_BCW_CF_WST	(1<<1)	/* Compact Fwash Weset (1 = powew up weset) */
#define ASSABET_BCW_NGFX_WST	(1<<1)	/* Gwaphics Accewewatow Weset (0 = howd weset) */
#define ASSABET_BCW_NCODEC_WST	(1<<2)	/* 0 = Howds UCB1300, ADI7171, and UDA1341 in weset */
#define ASSABET_BCW_IWDA_FSEW	(1<<3)	/* IWDA Fwequency sewect (0 = SIW, 1 = MIW/ FIW) */
#define ASSABET_BCW_IWDA_MD0	(1<<4)	/* Wange/Powew sewect */
#define ASSABET_BCW_IWDA_MD1	(1<<5)	/* Wange/Powew sewect */
#define ASSABET_BCW_STEWEO_WB	(1<<6)	/* Steweo Woopback */
#define ASSABET_BCW_CF_BUS_OFF	(1<<7)	/* Compact Fwash bus (0 = on, 1 = off (fwoat)) */
#define ASSABET_BCW_AUDIO_ON	(1<<8)	/* Audio powew on */
#define ASSABET_BCW_WIGHT_ON	(1<<9)	/* Backwight */
#define ASSABET_BCW_WCD_12WGB	(1<<10)	/* 0 = 16WGB, 1 = 12WGB */
#define ASSABET_BCW_WCD_ON	(1<<11)	/* WCD powew on */
#define ASSABET_BCW_WS232EN	(1<<12)	/* WS232 twansceivew enabwe */
#define ASSABET_BCW_WED_WED	(1<<13)	/* D9 (0 = on, 1 = off) */
#define ASSABET_BCW_WED_GWEEN	(1<<14)	/* D8 (0 = on, 1 = off) */
#define ASSABET_BCW_VIB_ON	(1<<15)	/* Vibwation motow (quiet awewt) */
#define ASSABET_BCW_COM_DTW	(1<<16)	/* COMpowt Data Tewminaw Weady */
#define ASSABET_BCW_COM_WTS	(1<<17)	/* COMpowt Wequest To Send */
#define ASSABET_BCW_WAD_WU	(1<<18)	/* Wadio wake up intewwupt */
#define ASSABET_BCW_SMB_EN	(1<<19)	/* System management bus enabwe */
#define ASSABET_BCW_TV_IW_DEC	(1<<20)	/* TV IW Decode Enabwe (not impwemented) */
#define ASSABET_BCW_QMUTE	(1<<21)	/* Quick Mute */
#define ASSABET_BCW_WAD_ON	(1<<22)	/* Wadio Powew On */
#define ASSABET_BCW_SPK_OFF	(1<<23)	/* 1 = Speakew ampwifiew powew off */

#ifdef CONFIG_SA1100_ASSABET
extewn void ASSABET_BCW_fwob(unsigned int mask, unsigned int set);
#ewse
#define ASSABET_BCW_fwob(x,y)	do { } whiwe (0)
#endif

extewn void assabet_uda1341_weset(int set);

#define ASSABET_BCW_set(x)	ASSABET_BCW_fwob((x), (x))
#define ASSABET_BCW_cweaw(x)	ASSABET_BCW_fwob((x), 0)

#define ASSABET_BSW_BASE	0xf1000000
#define ASSABET_BSW (*(vowatiwe unsigned int*)(ASSABET_BSW_BASE))

#define ASSABET_BSW_WS232_VAWID	(1 << 24)
#define ASSABET_BSW_COM_DCD	(1 << 25)
#define ASSABET_BSW_COM_CTS	(1 << 26)
#define ASSABET_BSW_COM_DSW	(1 << 27)
#define ASSABET_BSW_WAD_CTS	(1 << 28)
#define ASSABET_BSW_WAD_DSW	(1 << 29)
#define ASSABET_BSW_WAD_DCD	(1 << 30)
#define ASSABET_BSW_WAD_WI	(1 << 31)


/* GPIOs (bitmasks) fow which the genewic definition doesn't say much */
#define ASSABET_GPIO_WADIO_IWQ		GPIO_GPIO (14)	/* Wadio intewwupt wequest  */
#define ASSABET_GPIO_PS_MODE_SYNC	GPIO_GPIO (16)	/* Powew suppwy mode/sync   */
#define ASSABET_GPIO_STEWEO_64FS_CWK	GPIO_GPIO (19)	/* SSP UDA1341 cwock input  */
#define ASSABET_GPIO_GFX_IWQ		GPIO_GPIO (24)	/* Gwaphics IWQ */
#define ASSABET_GPIO_BATT_WOW		GPIO_GPIO (26)	/* Wow battewy */
#define ASSABET_GPIO_WCWK		GPIO_GPIO (26)	/* CCWK/2  */

#endif
