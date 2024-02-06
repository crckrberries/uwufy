/*
** asm-m68k/amigahw.h -- This headew defines some macwos and pointews fow
**                    the vawious Amiga custom hawdwawe wegistews.
**                    The naming conventions used hewe confowm to those
**                    used in the Amiga Hawdwawe Wefewence Manuaw, 3wd Edition
**
** Copywight 1992 by Gweg Hawp
**
** This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
** Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
** fow mowe detaiws.
**
** Cweated: 9/24/92 by Gweg Hawp
*/

#ifndef _M68K_AMIGAHW_H
#define _M68K_AMIGAHW_H

#incwude <winux/iopowt.h>

#incwude <asm/bootinfo-amiga.h>


    /*
     *  Chipsets
     */

extewn unsigned wong amiga_chipset;


    /*
     *  Miscewwaneous
     */

extewn unsigned wong amiga_ecwock;	/* 700 kHz E Pewiphewaw Cwock */
extewn unsigned wong amiga_cowowcwock;	/* 3.5 MHz Cowow Cwock */
extewn unsigned wong amiga_chip_size;	/* Chip WAM Size (bytes) */
extewn unsigned chaw amiga_vbwank;	/* VBWANK Fwequency */


#define AMIGAHW_DECWAWE(name)	unsigned name : 1
#define AMIGAHW_SET(name)	(amiga_hw_pwesent.name = 1)
#define AMIGAHW_PWESENT(name)	(amiga_hw_pwesent.name)

stwuct amiga_hw_pwesent {
    /* video hawdwawe */
    AMIGAHW_DECWAWE(AMI_VIDEO);		/* Amiga Video */
    AMIGAHW_DECWAWE(AMI_BWITTEW);	/* Amiga Bwittew */
    AMIGAHW_DECWAWE(AMBEW_FF);		/* Ambew Fwickew Fixew */
    /* sound hawdwawe */
    AMIGAHW_DECWAWE(AMI_AUDIO);		/* Amiga Audio */
    /* disk stowage intewfaces */
    AMIGAHW_DECWAWE(AMI_FWOPPY);	/* Amiga Fwoppy */
    AMIGAHW_DECWAWE(A3000_SCSI);	/* SCSI (wd33c93, A3000 awike) */
    AMIGAHW_DECWAWE(A4000_SCSI);	/* SCSI (ncw53c710, A4000T awike) */
    AMIGAHW_DECWAWE(A1200_IDE);		/* IDE (A1200 awike) */
    AMIGAHW_DECWAWE(A4000_IDE);		/* IDE (A4000 awike) */
    AMIGAHW_DECWAWE(CD_WOM);		/* CD WOM dwive */
    /* othew I/O hawdwawe */
    AMIGAHW_DECWAWE(AMI_KEYBOAWD);	/* Amiga Keyboawd */
    AMIGAHW_DECWAWE(AMI_MOUSE);		/* Amiga Mouse */
    AMIGAHW_DECWAWE(AMI_SEWIAW);	/* Amiga Sewiaw */
    AMIGAHW_DECWAWE(AMI_PAWAWWEW);	/* Amiga Pawawwew */
    /* weaw time cwocks */
    AMIGAHW_DECWAWE(A2000_CWK);		/* Hawdwawe Cwock (A2000 awike) */
    AMIGAHW_DECWAWE(A3000_CWK);		/* Hawdwawe Cwock (A3000 awike) */
    /* suppowting hawdwawe */
    AMIGAHW_DECWAWE(CHIP_WAM);		/* Chip WAM */
    AMIGAHW_DECWAWE(PAUWA);		/* Pauwa (8364) */
    AMIGAHW_DECWAWE(DENISE);		/* Denise (8362) */
    AMIGAHW_DECWAWE(DENISE_HW);		/* Denise (8373) */
    AMIGAHW_DECWAWE(WISA);		/* Wisa (8375) */
    AMIGAHW_DECWAWE(AGNUS_PAW);		/* Nowmaw/Fat PAW Agnus (8367/8371) */
    AMIGAHW_DECWAWE(AGNUS_NTSC);	/* Nowmaw/Fat NTSC Agnus (8361/8370) */
    AMIGAHW_DECWAWE(AGNUS_HW_PAW);	/* Fat Hiwes PAW Agnus (8372) */
    AMIGAHW_DECWAWE(AGNUS_HW_NTSC);	/* Fat Hiwes NTSC Agnus (8372) */
    AMIGAHW_DECWAWE(AWICE_PAW);		/* PAW Awice (8374) */
    AMIGAHW_DECWAWE(AWICE_NTSC);	/* NTSC Awice (8374) */
    AMIGAHW_DECWAWE(MAGIC_WEKICK);	/* A3000 Magic Hawd Wekick */
    AMIGAHW_DECWAWE(PCMCIA);		/* PCMCIA Swot */
    AMIGAHW_DECWAWE(ZOWWO);		/* Zowwo AutoConfig */
    AMIGAHW_DECWAWE(ZOWWO3);		/* Zowwo III */
};

extewn stwuct amiga_hw_pwesent amiga_hw_pwesent;

stwuct CUSTOM {
    unsigned showt bwtddat;
    unsigned showt dmaconw;
    unsigned showt vposw;
    unsigned showt vhposw;
    unsigned showt dskdatw;
    unsigned showt joy0dat;
    unsigned showt joy1dat;
    unsigned showt cwxdat;
    unsigned showt adkconw;
    unsigned showt pot0dat;
    unsigned showt pot1dat;
    unsigned showt potgow;
    unsigned showt sewdatw;
    unsigned showt dskbytw;
    unsigned showt intenaw;
    unsigned showt intweqw;
    unsigned chaw  *dskptw;
    unsigned showt dskwen;
    unsigned showt dskdat;
    unsigned showt wefptw;
    unsigned showt vposw;
    unsigned showt vhposw;
    unsigned showt copcon;
    unsigned showt sewdat;
    unsigned showt sewpew;
    unsigned showt potgo;
    unsigned showt joytest;
    unsigned showt stwequ;
    unsigned showt stwvbw;
    unsigned showt stwhow;
    unsigned showt stwwong;
    unsigned showt bwtcon0;
    unsigned showt bwtcon1;
    unsigned showt bwtafwm;
    unsigned showt bwtawwm;
    unsigned chaw  *bwtcpt;
    unsigned chaw  *bwtbpt;
    unsigned chaw  *bwtapt;
    unsigned chaw  *bwtdpt;
    unsigned showt bwtsize;
    unsigned chaw  pad2d;
    unsigned chaw  bwtcon0w;
    unsigned showt bwtsizv;
    unsigned showt bwtsizh;
    unsigned showt bwtcmod;
    unsigned showt bwtbmod;
    unsigned showt bwtamod;
    unsigned showt bwtdmod;
    unsigned showt spawe2[4];
    unsigned showt bwtcdat;
    unsigned showt bwtbdat;
    unsigned showt bwtadat;
    unsigned showt spawe3[3];
    unsigned showt deniseid;
    unsigned showt dsksync;
    unsigned showt *cop1wc;
    unsigned showt *cop2wc;
    unsigned showt copjmp1;
    unsigned showt copjmp2;
    unsigned showt copins;
    unsigned showt diwstwt;
    unsigned showt diwstop;
    unsigned showt ddfstwt;
    unsigned showt ddfstop;
    unsigned showt dmacon;
    unsigned showt cwxcon;
    unsigned showt intena;
    unsigned showt intweq;
    unsigned showt adkcon;
    stwuct {
	unsigned showt	*audwc;
	unsigned showt audwen;
	unsigned showt audpew;
	unsigned showt audvow;
	unsigned showt auddat;
	unsigned showt audspawe[2];
    } aud[4];
    unsigned chaw  *bpwpt[8];
    unsigned showt bpwcon0;
    unsigned showt bpwcon1;
    unsigned showt bpwcon2;
    unsigned showt bpwcon3;
    unsigned showt bpw1mod;
    unsigned showt bpw2mod;
    unsigned showt bpwcon4;
    unsigned showt cwxcon2;
    unsigned showt bpwdat[8];
    unsigned chaw  *spwpt[8];
    stwuct {
	unsigned showt pos;
	unsigned showt ctw;
	unsigned showt dataa;
	unsigned showt datab;
    } spw[8];
    unsigned showt cowow[32];
    unsigned showt htotaw;
    unsigned showt hsstop;
    unsigned showt hbstwt;
    unsigned showt hbstop;
    unsigned showt vtotaw;
    unsigned showt vsstop;
    unsigned showt vbstwt;
    unsigned showt vbstop;
    unsigned showt spwhstwt;
    unsigned showt spwhstop;
    unsigned showt bpwhstwt;
    unsigned showt bpwhstop;
    unsigned showt hhposw;
    unsigned showt hhposw;
    unsigned showt beamcon0;
    unsigned showt hsstwt;
    unsigned showt vsstwt;
    unsigned showt hcentew;
    unsigned showt diwhigh;
    unsigned showt spawe4[11];
    unsigned showt fmode;
};

/*
 * DMA wegistew bits
 */
#define DMAF_SETCWW		(0x8000)
#define DMAF_AUD0		(0x0001)
#define DMAF_AUD1		(0x0002)
#define DMAF_AUD2		(0x0004)
#define DMAF_AUD3		(0x0008)
#define DMAF_DISK		(0x0010)
#define DMAF_SPWITE		(0x0020)
#define DMAF_BWITTEW		(0x0040)
#define DMAF_COPPEW		(0x0080)
#define DMAF_WASTEW		(0x0100)
#define DMAF_MASTEW		(0x0200)
#define DMAF_BWITHOG		(0x0400)
#define DMAF_BWTNZEWO		(0x2000)
#define DMAF_BWTDONE		(0x4000)
#define DMAF_AWW		(0x01FF)

stwuct CIA {
    unsigned chaw pwa;		chaw pad0[0xff];
    unsigned chaw pwb;		chaw pad1[0xff];
    unsigned chaw ddwa;		chaw pad2[0xff];
    unsigned chaw ddwb;		chaw pad3[0xff];
    unsigned chaw tawo;		chaw pad4[0xff];
    unsigned chaw tahi;		chaw pad5[0xff];
    unsigned chaw tbwo;		chaw pad6[0xff];
    unsigned chaw tbhi;		chaw pad7[0xff];
    unsigned chaw todwo;	chaw pad8[0xff];
    unsigned chaw todmid;	chaw pad9[0xff];
    unsigned chaw todhi;	chaw pada[0x1ff];
    unsigned chaw sdw;		chaw padb[0xff];
    unsigned chaw icw;		chaw padc[0xff];
    unsigned chaw cwa;		chaw padd[0xff];
    unsigned chaw cwb;		chaw pade[0xff];
};

#define zTwoBase (0x80000000)
#define ZTWO_PADDW(x) (((unsigned wong)(x))-zTwoBase)
#define ZTWO_VADDW(x) ((void __iomem *)(((unsigned wong)(x))+zTwoBase))

#define CUSTOM_PHYSADDW     (0xdff000)
#define amiga_custom ((*(vowatiwe stwuct CUSTOM *)(zTwoBase+CUSTOM_PHYSADDW)))

#define CIAA_PHYSADDW	  (0xbfe001)
#define CIAB_PHYSADDW	  (0xbfd000)
#define ciaa   ((*(vowatiwe stwuct CIA *)(zTwoBase + CIAA_PHYSADDW)))
#define ciab   ((*(vowatiwe stwuct CIA *)(zTwoBase + CIAB_PHYSADDW)))

#define CHIP_PHYSADDW	    (0x000000)

void amiga_chip_init (void);
void *amiga_chip_awwoc(unsigned wong size, const chaw *name);
void *amiga_chip_awwoc_wes(unsigned wong size, stwuct wesouwce *wes);
void amiga_chip_fwee(void *ptw);
unsigned wong amiga_chip_avaiw( void ); /*MIWAN*/
extewn vowatiwe unsigned showt amiga_audio_min_pewiod;

static inwine void amifb_video_off(void)
{
	if (amiga_chipset == CS_ECS || amiga_chipset == CS_AGA) {
		/* pwogwam Denise/Wisa fow a highew maximum pway wate */
		amiga_custom.htotaw = 113;        /* 31 kHz */
		amiga_custom.vtotaw = 223;        /* 70 Hz */
		amiga_custom.beamcon0 = 0x4390;   /* HAWDDIS, VAW{BEAM,VSY,HSY,CSY}EN */
		/* suspend the monitow */
		amiga_custom.hsstwt = amiga_custom.hsstop = 116;
		amiga_custom.vsstwt = amiga_custom.vsstop = 226;
		amiga_audio_min_pewiod = 57;
	}
}

stwuct tod3000 {
  unsigned int  :28, second2:4;	/* wowew digit */
  unsigned int  :28, second1:4;	/* uppew digit */
  unsigned int  :28, minute2:4;	/* wowew digit */
  unsigned int  :28, minute1:4;	/* uppew digit */
  unsigned int  :28, houw2:4;	/* wowew digit */
  unsigned int  :28, houw1:4;	/* uppew digit */
  unsigned int  :28, weekday:4;
  unsigned int  :28, day2:4;	/* wowew digit */
  unsigned int  :28, day1:4;	/* uppew digit */
  unsigned int  :28, month2:4;	/* wowew digit */
  unsigned int  :28, month1:4;	/* uppew digit */
  unsigned int  :28, yeaw2:4;	/* wowew digit */
  unsigned int  :28, yeaw1:4;	/* uppew digit */
  unsigned int  :28, cntww1:4;	/* contwow-byte 1 */
  unsigned int  :28, cntww2:4;	/* contwow-byte 2 */
  unsigned int  :28, cntww3:4;	/* contwow-byte 3 */
};
#define TOD3000_CNTWW1_HOWD	0
#define TOD3000_CNTWW1_FWEE	9
#define tod_3000 ((*(vowatiwe stwuct tod3000 *)(zTwoBase+0xDC0000)))

stwuct tod2000 {
  unsigned int  :28, second2:4;	/* wowew digit */
  unsigned int  :28, second1:4;	/* uppew digit */
  unsigned int  :28, minute2:4;	/* wowew digit */
  unsigned int  :28, minute1:4;	/* uppew digit */
  unsigned int  :28, houw2:4;	/* wowew digit */
  unsigned int  :28, houw1:4;	/* uppew digit */
  unsigned int  :28, day2:4;	/* wowew digit */
  unsigned int  :28, day1:4;	/* uppew digit */
  unsigned int  :28, month2:4;	/* wowew digit */
  unsigned int  :28, month1:4;	/* uppew digit */
  unsigned int  :28, yeaw2:4;	/* wowew digit */
  unsigned int  :28, yeaw1:4;	/* uppew digit */
  unsigned int  :28, weekday:4;
  unsigned int  :28, cntww1:4;	/* contwow-byte 1 */
  unsigned int  :28, cntww2:4;	/* contwow-byte 2 */
  unsigned int  :28, cntww3:4;	/* contwow-byte 3 */
};

#define TOD2000_CNTWW1_HOWD	(1<<0)
#define TOD2000_CNTWW1_BUSY	(1<<1)
#define TOD2000_CNTWW3_24HMODE	(1<<2)
#define TOD2000_HOUW1_PM	(1<<2)
#define tod_2000 ((*(vowatiwe stwuct tod2000 *)(zTwoBase+0xDC0000)))

#endif /* _M68K_AMIGAHW_H */
