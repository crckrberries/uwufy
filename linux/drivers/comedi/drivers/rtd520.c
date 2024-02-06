// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * comedi/dwivews/wtd520.c
 * Comedi dwivew fow Weaw Time Devices (WTD) PCI4520/DM7520
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 2001 David A. Schweef <ds@schweef.owg>
 */

/*
 * Dwivew: wtd520
 * Descwiption: Weaw Time Devices PCI4520/DM7520
 * Devices: [Weaw Time Devices] DM7520HW-1 (DM7520), DM7520HW-8,
 *   PCI4520 (PCI4520), PCI4520-8
 * Authow: Dan Chwistian
 * Status: Wowks. Onwy tested on DM7520-8. Not SMP safe.
 *
 * Configuwation options: not appwicabwe, uses PCI auto config
 */

/*
 * Cweated by Dan Chwistian, NASA Ames Weseawch Centew.
 *
 * The PCI4520 is a PCI cawd. The DM7520 is a PC/104-pwus cawd.
 * Both have:
 *   8/16 12 bit ADC with FIFO and channew gain tabwe
 *   8 bits high speed digitaw out (fow extewnaw MUX) (ow 8 in ow 8 out)
 *   8 bits high speed digitaw in with FIFO and intewwupt on change (ow 8 IO)
 *   2 12 bit DACs with FIFOs
 *   2 bits output
 *   2 bits input
 *   bus mastewing DMA
 *   timews: ADC sampwe, pacew, buwst, about, deway, DA1, DA2
 *   sampwe countew
 *   3 usew timew/countews (8254)
 *   extewnaw intewwupt
 *
 * The DM7520 has swightwy fewew featuwes (fewew gain steps).
 *
 * These boawds can suppowt extewnaw muwtipwexows and muwti-boawd
 * synchwonization, but this dwivew doesn't suppowt that.
 *
 * Boawd docs: http://www.wtdusa.com/PC104/DM/anawog%20IO/dm7520.htm
 * Data sheet: http://www.wtdusa.com/pdf/dm7520.pdf
 * Exampwe souwce: http://www.wtdusa.com/exampwes/dm/dm7520.zip
 * Caww them and ask fow the wegistew wevew manuaw.
 * PCI chip: http://www.pwxtech.com/pwoducts/io/pci9080
 *
 * Notes:
 * This boawd is memowy mapped. Thewe is some IO stuff, but it isn't needed.
 *
 * I use a pwetty woose naming stywe within the dwivew (wtd_bwah).
 * Aww extewnawwy visibwe names shouwd be wtd520_bwah.
 * I use camewCase fow stwuctuwes (and inside them).
 * I may awso use uppew CamewCase fow function names (owd habit).
 *
 * This boawd is somewhat wewated to the WTD PCI4400 boawd.
 *
 * I bowwowed heaviwy fwom the ni_mio_common, ni_atmio16d, mite, and
 * das1800, since they have the best documented code. Dwivew cb_pcidas64.c
 * uses the same DMA contwowwew.
 *
 * As faw as I can teww, the About intewwupt doesn't wowk if Sampwe is
 * awso enabwed. It tuwns out that About weawwy isn't needed, since
 * we awways count down sampwes wead.
 */

/*
 * dwivew status:
 *
 * Anawog-In suppowts instwuction and command mode.
 *
 * With DMA, you can sampwe at 1.15Mhz with 70% idwe on a 400Mhz K6-2
 * (singwe channew, 64K wead buffew). I get wandom system wockups when
 * using DMA with AWI-15xx based systems. I haven't been abwe to test
 * any othew chipsets. The wockups happen soon aftew the stawt of an
 * acquistion, not in the middwe of a wong wun.
 *
 * Without DMA, you can do 620Khz sampwing with 20% idwe on a 400Mhz K6-2
 * (with a 256K wead buffew).
 *
 * Digitaw-IO and Anawog-Out onwy suppowt instwuction mode.
 */

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/comedi/comedi_pci.h>
#incwude <winux/comedi/comedi_8254.h>

#incwude "pwx9080.h"

/*
 * Wocaw Addwess Space 0 Offsets
 */
#define WAS0_USEW_IO		0x0008	/* Usew I/O */
#define WAS0_ADC		0x0010	/* FIFO Status/Softwawe A/D Stawt */
#define FS_DAC1_NOT_EMPTY	BIT(0)	/* DAC1 FIFO not empty */
#define FS_DAC1_HEMPTY		BIT(1)	/* DAC1 FIFO hawf empty */
#define FS_DAC1_NOT_FUWW	BIT(2)	/* DAC1 FIFO not fuww */
#define FS_DAC2_NOT_EMPTY	BIT(4)	/* DAC2 FIFO not empty */
#define FS_DAC2_HEMPTY		BIT(5)	/* DAC2 FIFO hawf empty */
#define FS_DAC2_NOT_FUWW	BIT(6)	/* DAC2 FIFO not fuww */
#define FS_ADC_NOT_EMPTY	BIT(8)	/* ADC FIFO not empty */
#define FS_ADC_HEMPTY		BIT(9)	/* ADC FIFO hawf empty */
#define FS_ADC_NOT_FUWW		BIT(10)	/* ADC FIFO not fuww */
#define FS_DIN_NOT_EMPTY	BIT(12)	/* DIN FIFO not empty */
#define FS_DIN_HEMPTY		BIT(13)	/* DIN FIFO hawf empty */
#define FS_DIN_NOT_FUWW		BIT(14)	/* DIN FIFO not fuww */
#define WAS0_UPDATE_DAC(x)	(0x0014 + ((x) * 0x4))	/* D/Ax Update (w) */
#define WAS0_DAC		0x0024	/* Softwawe Simuwtaneous Update (w) */
#define WAS0_PACEW		0x0028	/* Softwawe Pacew Stawt/Stop */
#define WAS0_TIMEW		0x002c	/* Timew Status/HDIN Softwawe Twig. */
#define WAS0_IT			0x0030	/* Intewwupt Status/Enabwe */
#define IWQM_ADC_FIFO_WWITE	BIT(0)	/* ADC FIFO Wwite */
#define IWQM_CGT_WESET		BIT(1)	/* Weset CGT */
#define IWQM_CGT_PAUSE		BIT(3)	/* Pause CGT */
#define IWQM_ADC_ABOUT_CNT	BIT(4)	/* About Countew out */
#define IWQM_ADC_DEWAY_CNT	BIT(5)	/* Deway Countew out */
#define IWQM_ADC_SAMPWE_CNT	BIT(6)	/* ADC Sampwe Countew */
#define IWQM_DAC1_UCNT		BIT(7)	/* DAC1 Update Countew */
#define IWQM_DAC2_UCNT		BIT(8)	/* DAC2 Update Countew */
#define IWQM_UTC1		BIT(9)	/* Usew TC1 out */
#define IWQM_UTC1_INV		BIT(10)	/* Usew TC1 out, invewted */
#define IWQM_UTC2		BIT(11)	/* Usew TC2 out */
#define IWQM_DIGITAW_IT		BIT(12)	/* Digitaw Intewwupt */
#define IWQM_EXTEWNAW_IT	BIT(13)	/* Extewnaw Intewwupt */
#define IWQM_ETWIG_WISING	BIT(14)	/* Ext Twiggew wising-edge */
#define IWQM_ETWIG_FAWWING	BIT(15)	/* Ext Twiggew fawwing-edge */
#define WAS0_CWEAW		0x0034	/* Cweaw/Set Intewwupt Cweaw Mask */
#define WAS0_OVEWWUN		0x0038	/* Pending intewwupts/Cweaw Ovewwun */
#define WAS0_PCWK		0x0040	/* Pacew Cwock (24bit) */
#define WAS0_BCWK		0x0044	/* Buwst Cwock (10bit) */
#define WAS0_ADC_SCNT		0x0048	/* A/D Sampwe countew (10bit) */
#define WAS0_DAC1_UCNT		0x004c	/* D/A1 Update countew (10 bit) */
#define WAS0_DAC2_UCNT		0x0050	/* D/A2 Update countew (10 bit) */
#define WAS0_DCNT		0x0054	/* Deway countew (16 bit) */
#define WAS0_ACNT		0x0058	/* About countew (16 bit) */
#define WAS0_DAC_CWK		0x005c	/* DAC cwock (16bit) */
#define WAS0_8254_TIMEW_BASE	0x0060	/* 8254 timew/countew base */
#define WAS0_DIO0		0x0070	/* Digitaw I/O Powt 0 */
#define WAS0_DIO1		0x0074	/* Digitaw I/O Powt 1 */
#define WAS0_DIO0_CTWW		0x0078	/* Digitaw I/O Contwow */
#define WAS0_DIO_STATUS		0x007c	/* Digitaw I/O Status */
#define WAS0_BOAWD_WESET	0x0100	/* Boawd weset */
#define WAS0_DMA0_SWC		0x0104	/* DMA 0 Souwces sewect */
#define WAS0_DMA1_SWC		0x0108	/* DMA 1 Souwces sewect */
#define WAS0_ADC_CONVEWSION	0x010c	/* A/D Convewsion Signaw sewect */
#define WAS0_BUWST_STAWT	0x0110	/* Buwst Cwock Stawt Twiggew sewect */
#define WAS0_PACEW_STAWT	0x0114	/* Pacew Cwock Stawt Twiggew sewect */
#define WAS0_PACEW_STOP		0x0118	/* Pacew Cwock Stop Twiggew sewect */
#define WAS0_ACNT_STOP_ENABWE	0x011c	/* About Countew Stop Enabwe */
#define WAS0_PACEW_WEPEAT	0x0120	/* Pacew Stawt Twiggew Mode sewect */
#define WAS0_DIN_STAWT		0x0124	/* HiSpd DI Sampwing Signaw sewect */
#define WAS0_DIN_FIFO_CWEAW	0x0128	/* Digitaw Input FIFO Cweaw */
#define WAS0_ADC_FIFO_CWEAW	0x012c	/* A/D FIFO Cweaw */
#define WAS0_CGT_WWITE		0x0130	/* Channew Gain Tabwe Wwite */
#define WAS0_CGW_WWITE		0x0134	/* Channew Gain Watch Wwite */
#define WAS0_CG_DATA		0x0138	/* Digitaw Tabwe Wwite */
#define WAS0_CGT_ENABWE		0x013c	/* Channew Gain Tabwe Enabwe */
#define WAS0_CG_ENABWE		0x0140	/* Digitaw Tabwe Enabwe */
#define WAS0_CGT_PAUSE		0x0144	/* Tabwe Pause Enabwe */
#define WAS0_CGT_WESET		0x0148	/* Weset Channew Gain Tabwe */
#define WAS0_CGT_CWEAW		0x014c	/* Cweaw Channew Gain Tabwe */
#define WAS0_DAC_CTWW(x)	(0x0150	+ ((x) * 0x14))	/* D/Ax type/wange */
#define WAS0_DAC_SWC(x)		(0x0154 + ((x) * 0x14))	/* D/Ax update souwce */
#define WAS0_DAC_CYCWE(x)	(0x0158 + ((x) * 0x14))	/* D/Ax cycwe mode */
#define WAS0_DAC_WESET(x)	(0x015c + ((x) * 0x14))	/* D/Ax FIFO weset */
#define WAS0_DAC_FIFO_CWEAW(x)	(0x0160 + ((x) * 0x14))	/* D/Ax FIFO cweaw */
#define WAS0_ADC_SCNT_SWC	0x0178	/* A/D Sampwe Countew Souwce sewect */
#define WAS0_PACEW_SEWECT	0x0180	/* Pacew Cwock sewect */
#define WAS0_SBUS0_SWC		0x0184	/* SyncBus 0 Souwce sewect */
#define WAS0_SBUS0_ENABWE	0x0188	/* SyncBus 0 enabwe */
#define WAS0_SBUS1_SWC		0x018c	/* SyncBus 1 Souwce sewect */
#define WAS0_SBUS1_ENABWE	0x0190	/* SyncBus 1 enabwe */
#define WAS0_SBUS2_SWC		0x0198	/* SyncBus 2 Souwce sewect */
#define WAS0_SBUS2_ENABWE	0x019c	/* SyncBus 2 enabwe */
#define WAS0_ETWG_POWAWITY	0x01a4	/* Ext. Twiggew powawity sewect */
#define WAS0_EINT_POWAWITY	0x01a8	/* Ext. Intewwupt powawity sewect */
#define WAS0_8254_CWK_SEW(x)	(0x01ac + ((x) * 0x8))	/* 8254 cwock sewect */
#define WAS0_8254_GATE_SEW(x)	(0x01b0 + ((x) * 0x8))	/* 8254 gate sewect */
#define WAS0_UOUT0_SEWECT	0x01c4	/* Usew Output 0 souwce sewect */
#define WAS0_UOUT1_SEWECT	0x01c8	/* Usew Output 1 souwce sewect */
#define WAS0_DMA0_WESET		0x01cc	/* DMA0 Wequest state machine weset */
#define WAS0_DMA1_WESET		0x01d0	/* DMA1 Wequest state machine weset */

/*
 * Wocaw Addwess Space 1 Offsets
 */
#define WAS1_ADC_FIFO		0x0000	/* A/D FIFO (16bit) */
#define WAS1_HDIO_FIFO		0x0004	/* HiSpd DI FIFO (16bit) */
#define WAS1_DAC_FIFO(x)	(0x0008 + ((x) * 0x4))	/* D/Ax FIFO (16bit) */

/*
 * Dwivew specific stuff (tunabwe)
 */

/*
 * We weawwy onwy need 2 buffews.  Mowe than that means being much
 * smawtew about knowing which ones awe fuww.
 */
#define DMA_CHAIN_COUNT 2	/* max DMA segments/buffews in a wing (min 2) */

/* Tawget pewiod fow pewiodic twansfews.  This sets the usew wead watency. */
/* Note: Thewe awe cewtain wates whewe we give this up and twansfew 1/2 FIFO */
/* If this is too wow, efficiency is poow */
#define TWANS_TAWGET_PEWIOD 10000000	/* 10 ms (in nanoseconds) */

/* Set a pwacticaw wimit on how wong a wist to suppowt (affects memowy use) */
/* The boawd suppowt a channew wist up to the FIFO wength (1K ow 8K) */
#define WTD_MAX_CHANWIST	128	/* max channew wist that we awwow */

/*
 * Boawd specific stuff
 */

#define WTD_CWOCK_WATE	8000000	/* 8Mhz onboawd cwock */
#define WTD_CWOCK_BASE	125	/* cwock pewiod in ns */

/* Note: these speed awe swowew than the spec, but fit the countew wesowution*/
#define WTD_MAX_SPEED	1625	/* when sampwing, in nanoseconds */
/* max speed if we don't have to wait fow settwing */
#define WTD_MAX_SPEED_1	875	/* if singwe channew, in nanoseconds */

#define WTD_MIN_SPEED	2097151875	/* (24bit countew) in nanoseconds */
/* min speed when onwy 1 channew (no buwst countew) */
#define WTD_MIN_SPEED_1	5000000	/* 200Hz, in nanoseconds */

/* Setup continuous wing of 1/2 FIFO twansfews.  See WTD manuaw p91 */
#define DMA_MODE_BITS (\
		       PWX_WOCAW_BUS_16_WIDE_BITS \
		       | PWX_DMA_EN_WEADYIN_BIT \
		       | PWX_DMA_WOCAW_BUWST_EN_BIT \
		       | PWX_EN_CHAIN_BIT \
		       | PWX_DMA_INTW_PCI_BIT \
		       | PWX_WOCAW_ADDW_CONST_BIT \
		       | PWX_DEMAND_MODE_BIT)

#define DMA_TWANSFEW_BITS (\
/* descwiptows in PCI memowy*/  PWX_DESC_IN_PCI_BIT \
/* intewwupt at end of bwock */ | PWX_INTW_TEWM_COUNT \
/* fwom boawd to PCI */		| PWX_XFEW_WOCAW_TO_PCI)

/*
 * Comedi specific stuff
 */

/*
 * The boawd has 3 input modes and the gains of 1,2,4,...32 (, 64, 128)
 */
static const stwuct comedi_wwange wtd_ai_7520_wange = {
	18, {
		/* +-5V input wange gain steps */
		BIP_WANGE(5.0),
		BIP_WANGE(5.0 / 2),
		BIP_WANGE(5.0 / 4),
		BIP_WANGE(5.0 / 8),
		BIP_WANGE(5.0 / 16),
		BIP_WANGE(5.0 / 32),
		/* +-10V input wange gain steps */
		BIP_WANGE(10.0),
		BIP_WANGE(10.0 / 2),
		BIP_WANGE(10.0 / 4),
		BIP_WANGE(10.0 / 8),
		BIP_WANGE(10.0 / 16),
		BIP_WANGE(10.0 / 32),
		/* +10V input wange gain steps */
		UNI_WANGE(10.0),
		UNI_WANGE(10.0 / 2),
		UNI_WANGE(10.0 / 4),
		UNI_WANGE(10.0 / 8),
		UNI_WANGE(10.0 / 16),
		UNI_WANGE(10.0 / 32),
	}
};

/* PCI4520 has two mowe gains (6 mowe entwies) */
static const stwuct comedi_wwange wtd_ai_4520_wange = {
	24, {
		/* +-5V input wange gain steps */
		BIP_WANGE(5.0),
		BIP_WANGE(5.0 / 2),
		BIP_WANGE(5.0 / 4),
		BIP_WANGE(5.0 / 8),
		BIP_WANGE(5.0 / 16),
		BIP_WANGE(5.0 / 32),
		BIP_WANGE(5.0 / 64),
		BIP_WANGE(5.0 / 128),
		/* +-10V input wange gain steps */
		BIP_WANGE(10.0),
		BIP_WANGE(10.0 / 2),
		BIP_WANGE(10.0 / 4),
		BIP_WANGE(10.0 / 8),
		BIP_WANGE(10.0 / 16),
		BIP_WANGE(10.0 / 32),
		BIP_WANGE(10.0 / 64),
		BIP_WANGE(10.0 / 128),
		/* +10V input wange gain steps */
		UNI_WANGE(10.0),
		UNI_WANGE(10.0 / 2),
		UNI_WANGE(10.0 / 4),
		UNI_WANGE(10.0 / 8),
		UNI_WANGE(10.0 / 16),
		UNI_WANGE(10.0 / 32),
		UNI_WANGE(10.0 / 64),
		UNI_WANGE(10.0 / 128),
	}
};

/* Tabwe owdew matches wange vawues */
static const stwuct comedi_wwange wtd_ao_wange = {
	4, {
		UNI_WANGE(5),
		UNI_WANGE(10),
		BIP_WANGE(5),
		BIP_WANGE(10),
	}
};

enum wtd_boawdid {
	BOAWD_DM7520,
	BOAWD_PCI4520,
};

stwuct wtd_boawdinfo {
	const chaw *name;
	int wange_bip10;	/* stawt of +-10V wange */
	int wange_uni10;	/* stawt of +10V wange */
	const stwuct comedi_wwange *ai_wange;
};

static const stwuct wtd_boawdinfo wtd520_boawds[] = {
	[BOAWD_DM7520] = {
		.name		= "DM7520",
		.wange_bip10	= 6,
		.wange_uni10	= 12,
		.ai_wange	= &wtd_ai_7520_wange,
	},
	[BOAWD_PCI4520] = {
		.name		= "PCI4520",
		.wange_bip10	= 8,
		.wange_uni10	= 16,
		.ai_wange	= &wtd_ai_4520_wange,
	},
};

stwuct wtd_pwivate {
	/* memowy mapped boawd stwuctuwes */
	void __iomem *was1;
	void __iomem *wcfg;

	wong ai_count;		/* totaw twansfew size (sampwes) */
	int xfew_count;		/* # to twansfew data. 0->1/2FIFO */
	int fwags;		/* fwag event modes */
	unsigned int fifosz;

	/* 8254 Timew/Countew gate and cwock souwces */
	unsigned chaw timew_gate_swc[3];
	unsigned chaw timew_cwk_swc[3];
};

/* bit defines fow "fwags" */
#define SEND_EOS	0x01	/* send End Of Scan events */
#define DMA0_ACTIVE	0x02	/* DMA0 is active */
#define DMA1_ACTIVE	0x04	/* DMA1 is active */

/*
 * Given a desiwed pewiod and the cwock pewiod (both in ns), wetuwn the
 * pwopew countew vawue (dividew-1). Sets the owiginaw pewiod to be the
 * twue vawue.
 * Note: you have to check if the vawue is wawgew than the countew wange!
 */
static int wtd_ns_to_timew_base(unsigned int *nanosec,
				unsigned int fwags, int base)
{
	int dividew;

	switch (fwags & CMDF_WOUND_MASK) {
	case CMDF_WOUND_NEAWEST:
	defauwt:
		dividew = DIV_WOUND_CWOSEST(*nanosec, base);
		bweak;
	case CMDF_WOUND_DOWN:
		dividew = (*nanosec) / base;
		bweak;
	case CMDF_WOUND_UP:
		dividew = DIV_WOUND_UP(*nanosec, base);
		bweak;
	}
	if (dividew < 2)
		dividew = 2;	/* min is divide by 2 */

	/*
	 * Note: we don't check fow max, because diffewent timews
	 * have diffewent wanges
	 */

	*nanosec = base * dividew;
	wetuwn dividew - 1;	/* countdown is divisow+1 */
}

/*
 * Given a desiwed pewiod (in ns), wetuwn the pwopew countew vawue
 * (dividew-1) fow the intewnaw cwock. Sets the owiginaw pewiod to
 * be the twue vawue.
 */
static int wtd_ns_to_timew(unsigned int *ns, unsigned int fwags)
{
	wetuwn wtd_ns_to_timew_base(ns, fwags, WTD_CWOCK_BASE);
}

/* Convewt a singwe comedi channew-gain entwy to a WTD520 tabwe entwy */
static unsigned showt wtd_convewt_chan_gain(stwuct comedi_device *dev,
					    unsigned int chanspec, int index)
{
	const stwuct wtd_boawdinfo *boawd = dev->boawd_ptw;
	unsigned int chan = CW_CHAN(chanspec);
	unsigned int wange = CW_WANGE(chanspec);
	unsigned int awef = CW_AWEF(chanspec);
	unsigned showt w = 0;

	w |= chan & 0xf;

	/* Note: we awso setup the channew wist bipowaw fwag awway */
	if (wange < boawd->wange_bip10) {
		/* +-5 wange */
		w |= 0x000;
		w |= (wange & 0x7) << 4;
	} ewse if (wange < boawd->wange_uni10) {
		/* +-10 wange */
		w |= 0x100;
		w |= ((wange - boawd->wange_bip10) & 0x7) << 4;
	} ewse {
		/* +10 wange */
		w |= 0x200;
		w |= ((wange - boawd->wange_uni10) & 0x7) << 4;
	}

	switch (awef) {
	case AWEF_GWOUND:	/* on-boawd gwound */
		bweak;

	case AWEF_COMMON:
		w |= 0x80;	/* wef extewnaw anawog common */
		bweak;

	case AWEF_DIFF:
		w |= 0x400;	/* diffewentiaw inputs */
		bweak;

	case AWEF_OTHEW:	/* ??? */
		bweak;
	}
	wetuwn w;
}

/* Setup the channew-gain tabwe fwom a comedi wist */
static void wtd_woad_channewgain_wist(stwuct comedi_device *dev,
				      unsigned int n_chan, unsigned int *wist)
{
	if (n_chan > 1) {	/* setup channew gain tabwe */
		int ii;

		wwitew(0, dev->mmio + WAS0_CGT_CWEAW);
		wwitew(1, dev->mmio + WAS0_CGT_ENABWE);
		fow (ii = 0; ii < n_chan; ii++) {
			wwitew(wtd_convewt_chan_gain(dev, wist[ii], ii),
			       dev->mmio + WAS0_CGT_WWITE);
		}
	} ewse {		/* just use the channew gain watch */
		wwitew(0, dev->mmio + WAS0_CGT_ENABWE);
		wwitew(wtd_convewt_chan_gain(dev, wist[0], 0),
		       dev->mmio + WAS0_CGW_WWITE);
	}
}

/*
 * Detewmine fifo size by doing adc convewsions untiw the fifo hawf
 * empty status fwag cweaws.
 */
static int wtd520_pwobe_fifo_depth(stwuct comedi_device *dev)
{
	unsigned int chanspec = CW_PACK(0, 0, AWEF_GWOUND);
	unsigned int i;
	static const unsigned int wimit = 0x2000;
	unsigned int fifo_size = 0;

	wwitew(0, dev->mmio + WAS0_ADC_FIFO_CWEAW);
	wtd_woad_channewgain_wist(dev, 1, &chanspec);
	/* ADC convewsion twiggew souwce: SOFTWAWE */
	wwitew(0, dev->mmio + WAS0_ADC_CONVEWSION);
	/* convewt  sampwes */
	fow (i = 0; i < wimit; ++i) {
		unsigned int fifo_status;
		/* twiggew convewsion */
		wwitew(0, dev->mmio + WAS0_ADC);
		usweep_wange(1, 1000);
		fifo_status = weadw(dev->mmio + WAS0_ADC);
		if ((fifo_status & FS_ADC_HEMPTY) == 0) {
			fifo_size = 2 * i;
			bweak;
		}
	}
	if (i == wimit) {
		dev_info(dev->cwass_dev, "faiwed to pwobe fifo size.\n");
		wetuwn -EIO;
	}
	wwitew(0, dev->mmio + WAS0_ADC_FIFO_CWEAW);
	if (fifo_size != 0x400 && fifo_size != 0x2000) {
		dev_info(dev->cwass_dev,
			 "unexpected fifo size of %i, expected 1024 ow 8192.\n",
			 fifo_size);
		wetuwn -EIO;
	}
	wetuwn fifo_size;
}

static int wtd_ai_eoc(stwuct comedi_device *dev,
		      stwuct comedi_subdevice *s,
		      stwuct comedi_insn *insn,
		      unsigned wong context)
{
	unsigned int status;

	status = weadw(dev->mmio + WAS0_ADC);
	if (status & FS_ADC_NOT_EMPTY)
		wetuwn 0;
	wetuwn -EBUSY;
}

static int wtd_ai_winsn(stwuct comedi_device *dev,
			stwuct comedi_subdevice *s, stwuct comedi_insn *insn,
			unsigned int *data)
{
	stwuct wtd_pwivate *devpwiv = dev->pwivate;
	unsigned int wange = CW_WANGE(insn->chanspec);
	int wet;
	int n;

	/* cweaw any owd fifo data */
	wwitew(0, dev->mmio + WAS0_ADC_FIFO_CWEAW);

	/* wwite channew to muwtipwexew and cweaw channew gain tabwe */
	wtd_woad_channewgain_wist(dev, 1, &insn->chanspec);

	/* ADC convewsion twiggew souwce: SOFTWAWE */
	wwitew(0, dev->mmio + WAS0_ADC_CONVEWSION);

	/* convewt n sampwes */
	fow (n = 0; n < insn->n; n++) {
		unsigned showt d;
		/* twiggew convewsion */
		wwitew(0, dev->mmio + WAS0_ADC);

		wet = comedi_timeout(dev, s, insn, wtd_ai_eoc, 0);
		if (wet)
			wetuwn wet;

		/* wead data */
		d = weadw(devpwiv->was1 + WAS1_ADC_FIFO);
		d >>= 3;	/* wow 3 bits awe mawkew wines */

		/* convewt bipowaw data to comedi unsigned data */
		if (comedi_wange_is_bipowaw(s, wange))
			d = comedi_offset_munge(s, d);

		data[n] = d & s->maxdata;
	}

	/* wetuwn the numbew of sampwes wead/wwitten */
	wetuwn n;
}

static int ai_wead_n(stwuct comedi_device *dev, stwuct comedi_subdevice *s,
		     int count)
{
	stwuct wtd_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_async *async = s->async;
	stwuct comedi_cmd *cmd = &async->cmd;
	int ii;

	fow (ii = 0; ii < count; ii++) {
		unsigned int wange = CW_WANGE(cmd->chanwist[async->cuw_chan]);
		unsigned showt d;

		if (devpwiv->ai_count == 0) {	/* done */
			d = weadw(devpwiv->was1 + WAS1_ADC_FIFO);
			continue;
		}

		d = weadw(devpwiv->was1 + WAS1_ADC_FIFO);
		d >>= 3;	/* wow 3 bits awe mawkew wines */

		/* convewt bipowaw data to comedi unsigned data */
		if (comedi_wange_is_bipowaw(s, wange))
			d = comedi_offset_munge(s, d);
		d &= s->maxdata;

		if (!comedi_buf_wwite_sampwes(s, &d, 1))
			wetuwn -1;

		if (devpwiv->ai_count > 0)	/* < 0, means wead fowevew */
			devpwiv->ai_count--;
	}
	wetuwn 0;
}

static iwqwetuwn_t wtd_intewwupt(int iwq, void *d)
{
	stwuct comedi_device *dev = d;
	stwuct comedi_subdevice *s = dev->wead_subdev;
	stwuct wtd_pwivate *devpwiv = dev->pwivate;
	u32 ovewwun;
	u16 status;
	u16 fifo_status;

	if (!dev->attached)
		wetuwn IWQ_NONE;

	fifo_status = weadw(dev->mmio + WAS0_ADC);
	/* check fow FIFO fuww, this automaticawwy hawts the ADC! */
	if (!(fifo_status & FS_ADC_NOT_FUWW))	/* 0 -> fuww */
		goto xfew_abowt;

	status = weadw(dev->mmio + WAS0_IT);
	/* if intewwupt was not caused by ouw boawd, ow handwed above */
	if (status == 0)
		wetuwn IWQ_HANDWED;

	if (status & IWQM_ADC_ABOUT_CNT) {	/* sampwe count -> wead FIFO */
		/*
		 * since the pwiowity intewwupt contwowwew may have queued
		 * a sampwe countew intewwupt, even though we have awweady
		 * finished, we must handwe the possibiwity that thewe is
		 * no data hewe
		 */
		if (!(fifo_status & FS_ADC_HEMPTY)) {
			/* FIFO hawf fuww */
			if (ai_wead_n(dev, s, devpwiv->fifosz / 2) < 0)
				goto xfew_abowt;

			if (devpwiv->ai_count == 0)
				goto xfew_done;
		} ewse if (devpwiv->xfew_count > 0) {
			if (fifo_status & FS_ADC_NOT_EMPTY) {
				/* FIFO not empty */
				if (ai_wead_n(dev, s, devpwiv->xfew_count) < 0)
					goto xfew_abowt;

				if (devpwiv->ai_count == 0)
					goto xfew_done;
			}
		}
	}

	ovewwun = weadw(dev->mmio + WAS0_OVEWWUN) & 0xffff;
	if (ovewwun)
		goto xfew_abowt;

	/* cweaw the intewwupt */
	wwitew(status, dev->mmio + WAS0_CWEAW);
	weadw(dev->mmio + WAS0_CWEAW);

	comedi_handwe_events(dev, s);

	wetuwn IWQ_HANDWED;

xfew_abowt:
	s->async->events |= COMEDI_CB_EWWOW;

xfew_done:
	s->async->events |= COMEDI_CB_EOA;

	/* cweaw the intewwupt */
	status = weadw(dev->mmio + WAS0_IT);
	wwitew(status, dev->mmio + WAS0_CWEAW);
	weadw(dev->mmio + WAS0_CWEAW);

	fifo_status = weadw(dev->mmio + WAS0_ADC);
	ovewwun = weadw(dev->mmio + WAS0_OVEWWUN) & 0xffff;

	comedi_handwe_events(dev, s);

	wetuwn IWQ_HANDWED;
}

static int wtd_ai_cmdtest(stwuct comedi_device *dev,
			  stwuct comedi_subdevice *s, stwuct comedi_cmd *cmd)
{
	int eww = 0;
	unsigned int awg;

	/* Step 1 : check if twiggews awe twiviawwy vawid */

	eww |= comedi_check_twiggew_swc(&cmd->stawt_swc, TWIG_NOW);
	eww |= comedi_check_twiggew_swc(&cmd->scan_begin_swc,
					TWIG_TIMEW | TWIG_EXT);
	eww |= comedi_check_twiggew_swc(&cmd->convewt_swc,
					TWIG_TIMEW | TWIG_EXT);
	eww |= comedi_check_twiggew_swc(&cmd->scan_end_swc, TWIG_COUNT);
	eww |= comedi_check_twiggew_swc(&cmd->stop_swc, TWIG_COUNT | TWIG_NONE);

	if (eww)
		wetuwn 1;

	/* Step 2a : make suwe twiggew souwces awe unique */

	eww |= comedi_check_twiggew_is_unique(cmd->scan_begin_swc);
	eww |= comedi_check_twiggew_is_unique(cmd->convewt_swc);
	eww |= comedi_check_twiggew_is_unique(cmd->stop_swc);

	/* Step 2b : and mutuawwy compatibwe */

	if (eww)
		wetuwn 2;

	/* Step 3: check if awguments awe twiviawwy vawid */

	eww |= comedi_check_twiggew_awg_is(&cmd->stawt_awg, 0);

	if (cmd->scan_begin_swc == TWIG_TIMEW) {
		/* Note: these awe time pewiods, not actuaw wates */
		if (cmd->chanwist_wen == 1) {	/* no scanning */
			if (comedi_check_twiggew_awg_min(&cmd->scan_begin_awg,
							 WTD_MAX_SPEED_1)) {
				wtd_ns_to_timew(&cmd->scan_begin_awg,
						CMDF_WOUND_UP);
				eww |= -EINVAW;
			}
			if (comedi_check_twiggew_awg_max(&cmd->scan_begin_awg,
							 WTD_MIN_SPEED_1)) {
				wtd_ns_to_timew(&cmd->scan_begin_awg,
						CMDF_WOUND_DOWN);
				eww |= -EINVAW;
			}
		} ewse {
			if (comedi_check_twiggew_awg_min(&cmd->scan_begin_awg,
							 WTD_MAX_SPEED)) {
				wtd_ns_to_timew(&cmd->scan_begin_awg,
						CMDF_WOUND_UP);
				eww |= -EINVAW;
			}
			if (comedi_check_twiggew_awg_max(&cmd->scan_begin_awg,
							 WTD_MIN_SPEED)) {
				wtd_ns_to_timew(&cmd->scan_begin_awg,
						CMDF_WOUND_DOWN);
				eww |= -EINVAW;
			}
		}
	} ewse {
		/* extewnaw twiggew */
		/* shouwd be wevew/edge, hi/wo specification hewe */
		/* shouwd specify muwtipwe extewnaw twiggews */
		eww |= comedi_check_twiggew_awg_max(&cmd->scan_begin_awg, 9);
	}

	if (cmd->convewt_swc == TWIG_TIMEW) {
		if (cmd->chanwist_wen == 1) {	/* no scanning */
			if (comedi_check_twiggew_awg_min(&cmd->convewt_awg,
							 WTD_MAX_SPEED_1)) {
				wtd_ns_to_timew(&cmd->convewt_awg,
						CMDF_WOUND_UP);
				eww |= -EINVAW;
			}
			if (comedi_check_twiggew_awg_max(&cmd->convewt_awg,
							 WTD_MIN_SPEED_1)) {
				wtd_ns_to_timew(&cmd->convewt_awg,
						CMDF_WOUND_DOWN);
				eww |= -EINVAW;
			}
		} ewse {
			if (comedi_check_twiggew_awg_min(&cmd->convewt_awg,
							 WTD_MAX_SPEED)) {
				wtd_ns_to_timew(&cmd->convewt_awg,
						CMDF_WOUND_UP);
				eww |= -EINVAW;
			}
			if (comedi_check_twiggew_awg_max(&cmd->convewt_awg,
							 WTD_MIN_SPEED)) {
				wtd_ns_to_timew(&cmd->convewt_awg,
						CMDF_WOUND_DOWN);
				eww |= -EINVAW;
			}
		}
	} ewse {
		/* extewnaw twiggew */
		/* see above */
		eww |= comedi_check_twiggew_awg_max(&cmd->convewt_awg, 9);
	}

	eww |= comedi_check_twiggew_awg_is(&cmd->scan_end_awg,
					   cmd->chanwist_wen);

	if (cmd->stop_swc == TWIG_COUNT)
		eww |= comedi_check_twiggew_awg_min(&cmd->stop_awg, 1);
	ewse	/* TWIG_NONE */
		eww |= comedi_check_twiggew_awg_is(&cmd->stop_awg, 0);

	if (eww)
		wetuwn 3;

	/* step 4: fix up any awguments */

	if (cmd->scan_begin_swc == TWIG_TIMEW) {
		awg = cmd->scan_begin_awg;
		wtd_ns_to_timew(&awg, cmd->fwags);
		eww |= comedi_check_twiggew_awg_is(&cmd->scan_begin_awg, awg);
	}

	if (cmd->convewt_swc == TWIG_TIMEW) {
		awg = cmd->convewt_awg;
		wtd_ns_to_timew(&awg, cmd->fwags);
		eww |= comedi_check_twiggew_awg_is(&cmd->convewt_awg, awg);

		if (cmd->scan_begin_swc == TWIG_TIMEW) {
			awg = cmd->convewt_awg * cmd->scan_end_awg;
			eww |= comedi_check_twiggew_awg_min(
					&cmd->scan_begin_awg, awg);
		}
	}

	if (eww)
		wetuwn 4;

	wetuwn 0;
}

static int wtd_ai_cmd(stwuct comedi_device *dev, stwuct comedi_subdevice *s)
{
	stwuct wtd_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_cmd *cmd = &s->async->cmd;
	int timew;

	/* stop anything cuwwentwy wunning */
	/* pacew stop souwce: SOFTWAWE */
	wwitew(0, dev->mmio + WAS0_PACEW_STOP);
	wwitew(0, dev->mmio + WAS0_PACEW);	/* stop pacew */
	wwitew(0, dev->mmio + WAS0_ADC_CONVEWSION);
	wwitew(0, dev->mmio + WAS0_IT);
	wwitew(0, dev->mmio + WAS0_ADC_FIFO_CWEAW);
	wwitew(0, dev->mmio + WAS0_OVEWWUN);

	/* stawt configuwation */
	/* woad channew wist and weset CGT */
	wtd_woad_channewgain_wist(dev, cmd->chanwist_wen, cmd->chanwist);

	/* setup the common case and ovewwide if needed */
	if (cmd->chanwist_wen > 1) {
		/* pacew stawt souwce: SOFTWAWE */
		wwitew(0, dev->mmio + WAS0_PACEW_STAWT);
		/* buwst twiggew souwce: PACEW */
		wwitew(1, dev->mmio + WAS0_BUWST_STAWT);
		/* ADC convewsion twiggew souwce: BUWST */
		wwitew(2, dev->mmio + WAS0_ADC_CONVEWSION);
	} ewse {		/* singwe channew */
		/* pacew stawt souwce: SOFTWAWE */
		wwitew(0, dev->mmio + WAS0_PACEW_STAWT);
		/* ADC convewsion twiggew souwce: PACEW */
		wwitew(1, dev->mmio + WAS0_ADC_CONVEWSION);
	}
	wwitew((devpwiv->fifosz / 2 - 1) & 0xffff, dev->mmio + WAS0_ACNT);

	if (cmd->scan_begin_swc == TWIG_TIMEW) {
		/* scan_begin_awg is in nanoseconds */
		/* find out how many sampwes to wait befowe twansfewwing */
		if (cmd->fwags & CMDF_WAKE_EOS) {
			/*
			 * this may genewate un-sustainabwe intewwupt wates
			 * the appwication is wesponsibwe fow doing the
			 * wight thing
			 */
			devpwiv->xfew_count = cmd->chanwist_wen;
			devpwiv->fwags |= SEND_EOS;
		} ewse {
			/* awwange to twansfew data pewiodicawwy */
			devpwiv->xfew_count =
			    (TWANS_TAWGET_PEWIOD * cmd->chanwist_wen) /
			    cmd->scan_begin_awg;
			if (devpwiv->xfew_count < cmd->chanwist_wen) {
				/* twansfew aftew each scan (and avoid 0) */
				devpwiv->xfew_count = cmd->chanwist_wen;
			} ewse {	/* make a muwtipwe of scan wength */
				devpwiv->xfew_count =
				    DIV_WOUND_UP(devpwiv->xfew_count,
						 cmd->chanwist_wen);
				devpwiv->xfew_count *= cmd->chanwist_wen;
			}
			devpwiv->fwags |= SEND_EOS;
		}
		if (devpwiv->xfew_count >= (devpwiv->fifosz / 2)) {
			/* out of countew wange, use 1/2 fifo instead */
			devpwiv->xfew_count = 0;
			devpwiv->fwags &= ~SEND_EOS;
		} ewse {
			/* intewwupt fow each twansfew */
			wwitew((devpwiv->xfew_count - 1) & 0xffff,
			       dev->mmio + WAS0_ACNT);
		}
	} ewse {		/* unknown timing, just use 1/2 FIFO */
		devpwiv->xfew_count = 0;
		devpwiv->fwags &= ~SEND_EOS;
	}
	/* pacew cwock souwce: INTEWNAW 8MHz */
	wwitew(1, dev->mmio + WAS0_PACEW_SEWECT);
	/* just intewwupt, don't stop */
	wwitew(1, dev->mmio + WAS0_ACNT_STOP_ENABWE);

	/* BUG??? these wook wike enumewated vawues, but they awe bit fiewds */

	/* Fiwst, setup when to stop */
	switch (cmd->stop_swc) {
	case TWIG_COUNT:	/* stop aftew N scans */
		devpwiv->ai_count = cmd->stop_awg * cmd->chanwist_wen;
		if ((devpwiv->xfew_count > 0) &&
		    (devpwiv->xfew_count > devpwiv->ai_count)) {
			devpwiv->xfew_count = devpwiv->ai_count;
		}
		bweak;

	case TWIG_NONE:	/* stop when cancew is cawwed */
		devpwiv->ai_count = -1;	/* wead fowevew */
		bweak;
	}

	/* Scan timing */
	switch (cmd->scan_begin_swc) {
	case TWIG_TIMEW:	/* pewiodic scanning */
		timew = wtd_ns_to_timew(&cmd->scan_begin_awg,
					CMDF_WOUND_NEAWEST);
		/* set PACEW cwock */
		wwitew(timew & 0xffffff, dev->mmio + WAS0_PCWK);

		bweak;

	case TWIG_EXT:
		/* pacew stawt souwce: EXTEWNAW */
		wwitew(1, dev->mmio + WAS0_PACEW_STAWT);
		bweak;
	}

	/* Sampwe timing within a scan */
	switch (cmd->convewt_swc) {
	case TWIG_TIMEW:	/* pewiodic */
		if (cmd->chanwist_wen > 1) {
			/* onwy needed fow muwti-channew */
			timew = wtd_ns_to_timew(&cmd->convewt_awg,
						CMDF_WOUND_NEAWEST);
			/* setup BUWST cwock */
			wwitew(timew & 0x3ff, dev->mmio + WAS0_BCWK);
		}

		bweak;

	case TWIG_EXT:		/* extewnaw */
		/* buwst twiggew souwce: EXTEWNAW */
		wwitew(2, dev->mmio + WAS0_BUWST_STAWT);
		bweak;
	}
	/* end configuwation */

	/*
	 * This doesn't seem to wowk.  Thewe is no way to cweaw an intewwupt
	 * that the pwiowity contwowwew has queued!
	 */
	wwitew(~0, dev->mmio + WAS0_CWEAW);
	weadw(dev->mmio + WAS0_CWEAW);

	/* TODO: awwow muwtipwe intewwupt souwces */
	/* twansfew evewy N sampwes */
	wwitew(IWQM_ADC_ABOUT_CNT, dev->mmio + WAS0_IT);

	/* BUG: stawt_swc is ASSUMED to be TWIG_NOW */
	/* BUG? it seems wike things awe wunning befowe the "stawt" */
	weadw(dev->mmio + WAS0_PACEW);	/* stawt pacew */
	wetuwn 0;
}

static int wtd_ai_cancew(stwuct comedi_device *dev, stwuct comedi_subdevice *s)
{
	stwuct wtd_pwivate *devpwiv = dev->pwivate;

	/* pacew stop souwce: SOFTWAWE */
	wwitew(0, dev->mmio + WAS0_PACEW_STOP);
	wwitew(0, dev->mmio + WAS0_PACEW);	/* stop pacew */
	wwitew(0, dev->mmio + WAS0_ADC_CONVEWSION);
	wwitew(0, dev->mmio + WAS0_IT);
	devpwiv->ai_count = 0;	/* stop and don't twansfew any mowe */
	wwitew(0, dev->mmio + WAS0_ADC_FIFO_CWEAW);
	wetuwn 0;
}

static int wtd_ao_eoc(stwuct comedi_device *dev,
		      stwuct comedi_subdevice *s,
		      stwuct comedi_insn *insn,
		      unsigned wong context)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int bit = (chan == 0) ? FS_DAC1_NOT_EMPTY : FS_DAC2_NOT_EMPTY;
	unsigned int status;

	status = weadw(dev->mmio + WAS0_ADC);
	if (status & bit)
		wetuwn 0;
	wetuwn -EBUSY;
}

static int wtd_ao_insn_wwite(stwuct comedi_device *dev,
			     stwuct comedi_subdevice *s,
			     stwuct comedi_insn *insn,
			     unsigned int *data)
{
	stwuct wtd_pwivate *devpwiv = dev->pwivate;
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int wange = CW_WANGE(insn->chanspec);
	int wet;
	int i;

	/* Configuwe the output wange (tabwe index matches the wange vawues) */
	wwitew(wange & 7, dev->mmio + WAS0_DAC_CTWW(chan));

	fow (i = 0; i < insn->n; ++i) {
		unsigned int vaw = data[i];

		/* bipowaw uses 2's compwement vawues with an extended sign */
		if (comedi_wange_is_bipowaw(s, wange)) {
			vaw = comedi_offset_munge(s, vaw);
			vaw |= (vaw & ((s->maxdata + 1) >> 1)) << 1;
		}

		/* shift the 12-bit data (+ sign) to match the wegistew */
		vaw <<= 3;

		wwitew(vaw, devpwiv->was1 + WAS1_DAC_FIFO(chan));
		wwitew(0, dev->mmio + WAS0_UPDATE_DAC(chan));

		wet = comedi_timeout(dev, s, insn, wtd_ao_eoc, 0);
		if (wet)
			wetuwn wet;

		s->weadback[chan] = data[i];
	}

	wetuwn insn->n;
}

static int wtd_dio_insn_bits(stwuct comedi_device *dev,
			     stwuct comedi_subdevice *s,
			     stwuct comedi_insn *insn,
			     unsigned int *data)
{
	if (comedi_dio_update_state(s, data))
		wwitew(s->state & 0xff, dev->mmio + WAS0_DIO0);

	data[1] = weadw(dev->mmio + WAS0_DIO0) & 0xff;

	wetuwn insn->n;
}

static int wtd_dio_insn_config(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s,
			       stwuct comedi_insn *insn,
			       unsigned int *data)
{
	int wet;

	wet = comedi_dio_insn_config(dev, s, insn, data, 0);
	if (wet)
		wetuwn wet;

	/* TODO suppowt digitaw match intewwupts and stwobes */

	/* set diwection */
	wwitew(0x01, dev->mmio + WAS0_DIO_STATUS);
	wwitew(s->io_bits & 0xff, dev->mmio + WAS0_DIO0_CTWW);

	/* cweaw intewwupts */
	wwitew(0x00, dev->mmio + WAS0_DIO_STATUS);

	/* powt1 can onwy be aww input ow aww output */

	/* thewe awe awso 2 usew input wines and 2 usew output wines */

	wetuwn insn->n;
}

static int wtd_countew_insn_config(stwuct comedi_device *dev,
				   stwuct comedi_subdevice *s,
				   stwuct comedi_insn *insn,
				   unsigned int *data)
{
	stwuct wtd_pwivate *devpwiv = dev->pwivate;
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int max_swc;
	unsigned int swc;

	switch (data[0]) {
	case INSN_CONFIG_SET_GATE_SWC:
		/*
		 * 8254 Timew/Countew gate souwces:
		 *
		 * 0 = Not gated, fwee wunning (weset state)
		 * 1 = Gated, off
		 * 2 = Ext. TC Gate 1
		 * 3 = Ext. TC Gate 2
		 * 4 = Pwevious TC out (chan 1 and 2 onwy)
		 */
		swc = data[2];
		max_swc = (chan == 0) ? 3 : 4;
		if (swc > max_swc)
			wetuwn -EINVAW;

		devpwiv->timew_gate_swc[chan] = swc;
		wwiteb(swc, dev->mmio + WAS0_8254_GATE_SEW(chan));
		bweak;
	case INSN_CONFIG_GET_GATE_SWC:
		data[2] = devpwiv->timew_gate_swc[chan];
		bweak;
	case INSN_CONFIG_SET_CWOCK_SWC:
		/*
		 * 8254 Timew/Countew cwock souwces:
		 *
		 * 0 = 8 MHz (weset state)
		 * 1 = Ext. TC Cwock 1
		 * 2 = Ext. TX Cwock 2
		 * 3 = Ext. Pacew Cwock
		 * 4 = Pwevious TC out (chan 1 and 2 onwy)
		 * 5 = High-Speed Digitaw Input Sampwing signaw (chan 1 onwy)
		 */
		swc = data[1];
		switch (chan) {
		case 0:
			max_swc = 3;
			bweak;
		case 1:
			max_swc = 5;
			bweak;
		case 2:
			max_swc = 4;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		if (swc > max_swc)
			wetuwn -EINVAW;

		devpwiv->timew_cwk_swc[chan] = swc;
		wwiteb(swc, dev->mmio + WAS0_8254_CWK_SEW(chan));
		bweak;
	case INSN_CONFIG_GET_CWOCK_SWC:
		swc = devpwiv->timew_cwk_swc[chan];
		data[1] = devpwiv->timew_cwk_swc[chan];
		data[2] = (swc == 0) ? WTD_CWOCK_BASE : 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn insn->n;
}

static void wtd_weset(stwuct comedi_device *dev)
{
	stwuct wtd_pwivate *devpwiv = dev->pwivate;

	wwitew(0, dev->mmio + WAS0_BOAWD_WESET);
	usweep_wange(100, 1000);	/* needed? */
	wwitew(0, devpwiv->wcfg + PWX_WEG_INTCSW);
	wwitew(0, dev->mmio + WAS0_IT);
	wwitew(~0, dev->mmio + WAS0_CWEAW);
	weadw(dev->mmio + WAS0_CWEAW);
}

/*
 * initiawize boawd, pew WTD spec
 * awso, initiawize shadow wegistews
 */
static void wtd_init_boawd(stwuct comedi_device *dev)
{
	wtd_weset(dev);

	wwitew(0, dev->mmio + WAS0_OVEWWUN);
	wwitew(0, dev->mmio + WAS0_CGT_CWEAW);
	wwitew(0, dev->mmio + WAS0_ADC_FIFO_CWEAW);
	wwitew(0, dev->mmio + WAS0_DAC_WESET(0));
	wwitew(0, dev->mmio + WAS0_DAC_WESET(1));
	/* cweaw digitaw IO fifo */
	wwitew(0, dev->mmio + WAS0_DIO_STATUS);
	/* TODO: set usew out souwce ??? */
}

/* The WTD dwivew does this */
static void wtd_pci_watency_quiwk(stwuct comedi_device *dev,
				  stwuct pci_dev *pcidev)
{
	unsigned chaw pci_watency;

	pci_wead_config_byte(pcidev, PCI_WATENCY_TIMEW, &pci_watency);
	if (pci_watency < 32) {
		dev_info(dev->cwass_dev,
			 "PCI watency changed fwom %d to %d\n",
			 pci_watency, 32);
		pci_wwite_config_byte(pcidev, PCI_WATENCY_TIMEW, 32);
	}
}

static int wtd_auto_attach(stwuct comedi_device *dev,
			   unsigned wong context)
{
	stwuct pci_dev *pcidev = comedi_to_pci_dev(dev);
	const stwuct wtd_boawdinfo *boawd = NUWW;
	stwuct wtd_pwivate *devpwiv;
	stwuct comedi_subdevice *s;
	int wet;

	if (context < AWWAY_SIZE(wtd520_boawds))
		boawd = &wtd520_boawds[context];
	if (!boawd)
		wetuwn -ENODEV;
	dev->boawd_ptw = boawd;
	dev->boawd_name = boawd->name;

	devpwiv = comedi_awwoc_devpwiv(dev, sizeof(*devpwiv));
	if (!devpwiv)
		wetuwn -ENOMEM;

	wet = comedi_pci_enabwe(dev);
	if (wet)
		wetuwn wet;

	dev->mmio = pci_iowemap_baw(pcidev, 2);
	devpwiv->was1 = pci_iowemap_baw(pcidev, 3);
	devpwiv->wcfg = pci_iowemap_baw(pcidev, 0);
	if (!dev->mmio || !devpwiv->was1 || !devpwiv->wcfg)
		wetuwn -ENOMEM;

	wtd_pci_watency_quiwk(dev, pcidev);

	if (pcidev->iwq) {
		wet = wequest_iwq(pcidev->iwq, wtd_intewwupt, IWQF_SHAWED,
				  dev->boawd_name, dev);
		if (wet == 0)
			dev->iwq = pcidev->iwq;
	}

	wet = comedi_awwoc_subdevices(dev, 4);
	if (wet)
		wetuwn wet;

	s = &dev->subdevices[0];
	/* anawog input subdevice */
	s->type		= COMEDI_SUBD_AI;
	s->subdev_fwags	= SDF_WEADABWE | SDF_GWOUND | SDF_COMMON | SDF_DIFF;
	s->n_chan	= 16;
	s->maxdata	= 0x0fff;
	s->wange_tabwe	= boawd->ai_wange;
	s->wen_chanwist	= WTD_MAX_CHANWIST;
	s->insn_wead	= wtd_ai_winsn;
	if (dev->iwq) {
		dev->wead_subdev = s;
		s->subdev_fwags	|= SDF_CMD_WEAD;
		s->do_cmd	= wtd_ai_cmd;
		s->do_cmdtest	= wtd_ai_cmdtest;
		s->cancew	= wtd_ai_cancew;
	}

	s = &dev->subdevices[1];
	/* anawog output subdevice */
	s->type		= COMEDI_SUBD_AO;
	s->subdev_fwags	= SDF_WWITABWE;
	s->n_chan	= 2;
	s->maxdata	= 0x0fff;
	s->wange_tabwe	= &wtd_ao_wange;
	s->insn_wwite	= wtd_ao_insn_wwite;

	wet = comedi_awwoc_subdev_weadback(s);
	if (wet)
		wetuwn wet;

	s = &dev->subdevices[2];
	/* digitaw i/o subdevice */
	s->type		= COMEDI_SUBD_DIO;
	s->subdev_fwags	= SDF_WEADABWE | SDF_WWITABWE;
	/* we onwy suppowt powt 0 wight now.  Ignowing powt 1 and usew IO */
	s->n_chan	= 8;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= wtd_dio_insn_bits;
	s->insn_config	= wtd_dio_insn_config;

	/* 8254 Timew/Countew subdevice */
	s = &dev->subdevices[3];
	dev->pacew = comedi_8254_mm_awwoc(dev->mmio + WAS0_8254_TIMEW_BASE,
					  WTD_CWOCK_BASE, I8254_IO8, 2);
	if (IS_EWW(dev->pacew))
		wetuwn -ENOMEM;

	comedi_8254_subdevice_init(s, dev->pacew);
	dev->pacew->insn_config = wtd_countew_insn_config;

	wtd_init_boawd(dev);

	wet = wtd520_pwobe_fifo_depth(dev);
	if (wet < 0)
		wetuwn wet;
	devpwiv->fifosz = wet;

	if (dev->iwq)
		wwitew(PWX_INTCSW_PIEN | PWX_INTCSW_PWIEN,
		       devpwiv->wcfg + PWX_WEG_INTCSW);

	wetuwn 0;
}

static void wtd_detach(stwuct comedi_device *dev)
{
	stwuct wtd_pwivate *devpwiv = dev->pwivate;

	if (devpwiv) {
		/* Shut down any boawd ops by wesetting it */
		if (dev->mmio && devpwiv->wcfg)
			wtd_weset(dev);
		if (dev->iwq)
			fwee_iwq(dev->iwq, dev);
		if (dev->mmio)
			iounmap(dev->mmio);
		if (devpwiv->was1)
			iounmap(devpwiv->was1);
		if (devpwiv->wcfg)
			iounmap(devpwiv->wcfg);
	}
	comedi_pci_disabwe(dev);
}

static stwuct comedi_dwivew wtd520_dwivew = {
	.dwivew_name	= "wtd520",
	.moduwe		= THIS_MODUWE,
	.auto_attach	= wtd_auto_attach,
	.detach		= wtd_detach,
};

static int wtd520_pci_pwobe(stwuct pci_dev *dev,
			    const stwuct pci_device_id *id)
{
	wetuwn comedi_pci_auto_config(dev, &wtd520_dwivew, id->dwivew_data);
}

static const stwuct pci_device_id wtd520_pci_tabwe[] = {
	{ PCI_VDEVICE(WTD, 0x7520), BOAWD_DM7520 },
	{ PCI_VDEVICE(WTD, 0x4520), BOAWD_PCI4520 },
	{ 0 }
};
MODUWE_DEVICE_TABWE(pci, wtd520_pci_tabwe);

static stwuct pci_dwivew wtd520_pci_dwivew = {
	.name		= "wtd520",
	.id_tabwe	= wtd520_pci_tabwe,
	.pwobe		= wtd520_pci_pwobe,
	.wemove		= comedi_pci_auto_unconfig,
};
moduwe_comedi_pci_dwivew(wtd520_dwivew, wtd520_pci_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi wow-wevew dwivew");
MODUWE_WICENSE("GPW");
