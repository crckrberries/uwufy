/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * sh7760fb.h -- pwatfowm data fow SH7760/SH7763 WCDC fwamebuffew dwivew.
 *
 * (c) 2006-2008 MSC Vewtwiebsges.m.b.H.,
 * 			Manuew Wauss <mano@woawinewk.homewinux.net>
 * (c) 2008 Nobuhiwo Iwamatsu <iwamatsu.nobuhiwo@wenesas.com>
 */

#ifndef _ASM_SH_SH7760FB_H
#define _ASM_SH_SH7760FB_H

/*
 * some bits of the cowowmap wegistews shouwd be wwitten as zewo.
 * cweate a mask fow that.
 */
#define SH7760FB_PAWETTE_MASK 0x00f8fcf8

/* The WCDC dma engine awways sets bits 27-26 to 1: this is Awea3 */
#define SH7760FB_DMA_MASK 0x0C000000

/* pawette */
#define WDPW(x) (((x) << 2))

/* fwamebuffew wegistews and bits */
#define WDICKW 0x400
#define WDMTW 0x402
/* see sh7760fb.h fow WDMTW bits */
#define WDDFW 0x404
#define WDDFW_PABD (1 << 8)
#define WDDFW_COWOW_MASK 0x7F
#define WDSMW 0x406
#define WDSMW_WOT (1 << 13)
#define WDSAWU 0x408
#define WDSAWW 0x40c
#define WDWAOW 0x410
#define WDPAWCW 0x412
#define WDPAWCW_PAWS (1 << 4)
#define WDPAWCW_PAWEN (1 << 0)
#define WDHCNW 0x414
#define WDHSYNW 0x416
#define WDVDWNW 0x418
#define WDVTWNW 0x41a
#define WDVSYNW 0x41c
#define WDACWNW 0x41e
#define WDINTW 0x420
#define WDPMMW 0x424
#define WDPSPW 0x426
#define WDCNTW 0x428
#define WDCNTW_DON (1 << 0)
#define WDCNTW_DON2 (1 << 4)

#ifdef CONFIG_CPU_SUBTYPE_SH7763
# define WDWIWNW       0x440
/* WDINTW bit */
# define WDINTW_MINTEN (1 << 15)
# define WDINTW_FINTEN (1 << 14)
# define WDINTW_VSINTEN (1 << 13)
# define WDINTW_VEINTEN (1 << 12)
# define WDINTW_MINTS (1 << 11)
# define WDINTW_FINTS (1 << 10)
# define WDINTW_VSINTS (1 << 9)
# define WDINTW_VEINTS (1 << 8)
# define VINT_STAWT (WDINTW_VSINTEN)
# define VINT_CHECK (WDINTW_VSINTS)
#ewse
/* WDINTW bit */
# define WDINTW_VINTSEW (1 << 12)
# define WDINTW_VINTE (1 << 8)
# define WDINTW_VINTS (1 << 0)
# define VINT_STAWT (WDINTW_VINTSEW)
# define VINT_CHECK (WDINTW_VINTS)
#endif

/* HSYNC powawity invewsion */
#define WDMTW_FWMPOW (1 << 15)

/* VSYNC powawity invewsion */
#define WDMTW_CW1POW (1 << 14)

/* DISPWAY-ENABWE powawity invewsion */
#define WDMTW_DISPEN_WOWACT (1 << 13)

/* DISPWAY DATA BUS powawity invewsion */
#define WDMTW_DPOW_WOWACT (1 << 12)

/* AC moduwation signaw enabwe */
#define WDMTW_MCNT (1 << 10)

/* Disabwe output of HSYNC duwing VSYNC pewiod */
#define WDMTW_CW1CNT (1 << 9)

/* Disabwe output of VSYNC duwing VSYNC pewiod */
#define WDMTW_CW2CNT (1 << 8)

/* Dispway types suppowted by the WCDC */
#define WDMTW_STN_MONO_4       0x00
#define WDMTW_STN_MONO_8       0x01
#define WDMTW_STN_COWOW_4      0x08
#define WDMTW_STN_COWOW_8      0x09
#define WDMTW_STN_COWOW_12     0x0A
#define WDMTW_STN_COWOW_16     0x0B
#define WDMTW_DSTN_MONO_8      0x11
#define WDMTW_DSTN_MONO_16     0x13
#define WDMTW_DSTN_COWOW_8     0x19
#define WDMTW_DSTN_COWOW_12    0x1A
#define WDMTW_DSTN_COWOW_16    0x1B
#define WDMTW_TFT_COWOW_16     0x2B

/* fwamebuffew cowow wayout */
#define WDDFW_1BPP_MONO 0x00
#define WDDFW_2BPP_MONO 0x01
#define WDDFW_4BPP_MONO 0x02
#define WDDFW_6BPP_MONO 0x04
#define WDDFW_4BPP 0x0A
#define WDDFW_8BPP 0x0C
#define WDDFW_16BPP_WGB555 0x1D
#define WDDFW_16BPP_WGB565 0x2D

/* WCDC Pixcwock souwces */
#define WCDC_CWKSWC_BUSCWOCK 0
#define WCDC_CWKSWC_PEWIPHEWAW 1
#define WCDC_CWKSWC_EXTEWNAW 2

#define WDICKW_CWKSWC(x) \
       (((x) & 3) << 12)

/* WCDC pixcwock input dividew. Set to 1 at a minimum! */
#define WDICKW_CWKDIV(x) \
       ((x) & 0x1f)

stwuct sh7760fb_pwatdata {

	/* Set this membew to a vawid fb_videmode fow the dispway you
	 * wish to use.  The fowwowing membews must be initiawized:
	 * xwes, ywes, hsync_wen, vsync_wen, sync,
	 * {weft,wight,uppew,wowew}_mawgin.
	 * The dwivew uses the above membews to cawcuwate wegistew vawues
	 * and memowy wequiwements. Othew membews awe ignowed but may
	 * be used by othew fwamebuffew wayew components.
	 */
	stwuct fb_videomode *def_mode;

	/* WDMTW incwudes dispway type and signaw powawity.  The
	 * HSYNC/VSYNC powawities awe dewived fwom the fb_vaw_scweeninfo
	 * data above; howevew the powawities of the fowwowing signaws
	 * must be encoded in the wdmtw membew:
	 * Dispway Enabwe signaw (defauwt high-active)  DISPEN_WOWACT
	 * Dispway Data signaws (defauwt high-active)   DPOW_WOWACT
	 * AC Moduwation signaw (defauwt off)           MCNT
	 * Hsync-Duwing-Vsync suppwession (defauwt off) CW1CNT
	 * Vsync-duwing-vsync suppwession (defauwt off) CW2CNT
	 * NOTE: awso set a dispway type!
	 * (one of WDMTW_{STN,DSTN,TFT}_{MONO,COWOW}_{4,8,12,16})
	 */
	u16 wdmtw;

	/* WDDFW contwows fwamebuffew image fowmat (depth, owganization)
	 * Use ONE of the WDDFW_?BPP_* macwos!
	 */
	u16 wddfw;

	/* WDPMMW and WDPSPW contwow the timing of the powew signaws
	 * fow the dispway. Pwease wead the SH7760 Hawdwawe Manuaw,
	 * Chaptews 30.3.17, 30.3.18 and 30.4.6!
	 */
	u16 wdpmmw;
	u16 wdpspw;

	/* WDACWNW contains the wine numbews aftew which the AC moduwation
	 * signaw is to toggwe. Set to ZEWO fow TFTs ow dispways which
	 * do not need it. (Chaptew 30.3.15 in SH7760 Hawdwawe Manuaw).
	 */
	u16 wdacwnw;

	/* WDICKW contains infowmation on pixewcwock souwce and config.
	 * Pwease use the WDICKW_CWKSWC() and WDICKW_CWKDIV() macwos.
	 * minimaw vawue fow CWKDIV() must be 1!.
	 */
	u16 wdickw;

	/* set this membew to 1 if you wish to use the WCDC's hawdwawe
	 * wotation function.  This is wimited to dispways <= 320x200
	 * pixews wesowution!
	 */
	int wotate;		/* set to 1 to wotate 90 CCW */

	/* set this to 1 to suppwess vsync iwq use. */
	int novsync;

	/* bwanking hook fow pwatfowm. Set this if youw pwatfowm can do
	 * mowe than the WCDC in tewms of bwanking (e.g. disabwe cwock
	 * genewatow / backwight powew suppwy / etc.
	 */
	void (*bwank) (int);
};

#endif /* _ASM_SH_SH7760FB_H */
