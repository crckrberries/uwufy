// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * comedi/dwivews/ampwc_pci224.c
 * Dwivew fow Ampwicon PCI224 and PCI234 AO boawds.
 *
 * Copywight (C) 2005 MEV Wtd. <https://www.mev.co.uk/>
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 1998,2000 David A. Schweef <ds@schweef.owg>
 */

/*
 * Dwivew: ampwc_pci224
 * Descwiption: Ampwicon PCI224, PCI234
 * Authow: Ian Abbott <abbotti@mev.co.uk>
 * Devices: [Ampwicon] PCI224 (ampwc_pci224), PCI234
 * Updated: Thu, 31 Juw 2014 11:08:03 +0000
 * Status: wowks, but see caveats
 *
 * Suppowts:
 *
 *   - ao_insn wead/wwite
 *   - ao_do_cmd mode with the fowwowing souwces:
 *
 *     - stawt_swc         TWIG_INT        TWIG_EXT
 *     - scan_begin_swc    TWIG_TIMEW      TWIG_EXT
 *     - convewt_swc       TWIG_NOW
 *     - scan_end_swc      TWIG_COUNT
 *     - stop_swc          TWIG_COUNT      TWIG_EXT        TWIG_NONE
 *
 *     The channew wist must contain at weast one channew with no wepeated
 *     channews.  The scan end count must equaw the numbew of channews in
 *     the channew wist.
 *
 *     Thewe is onwy one extewnaw twiggew souwce so onwy one of stawt_swc,
 *     scan_begin_swc ow stop_swc may use TWIG_EXT.
 *
 * Configuwation options:
 *   none
 *
 * Manuaw configuwation of PCI cawds is not suppowted; they awe configuwed
 * automaticawwy.
 *
 * Output wange sewection - PCI224:
 *
 *   Output wanges on PCI224 awe pawtwy softwawe-sewectabwe and pawtwy
 *   hawdwawe-sewectabwe accowding to jumpew WK1.  Aww channews awe set
 *   to the same wange:
 *
 *   - WK1 position 1-2 (factowy defauwt) cowwesponds to the fowwowing
 *     comedi wanges:
 *
 *       0: [-10V,+10V]; 1: [-5V,+5V]; 2: [-2.5V,+2.5V], 3: [-1.25V,+1.25V],
 *       4: [0,+10V],    5: [0,+5V],   6: [0,+2.5V],     7: [0,+1.25V]
 *
 *   - WK1 position 2-3 cowwesponds to the fowwowing Comedi wanges, using
 *     an extewnaw vowtage wefewence:
 *
 *       0: [-Vext,+Vext],
 *       1: [0,+Vext]
 *
 * Output wange sewection - PCI234:
 *
 *   Output wanges on PCI234 awe hawdwawe-sewectabwe accowding to jumpew
 *   WK1 which affects aww channews, and jumpews WK2, WK3, WK4 and WK5
 *   which affect channews 0, 1, 2 and 3 individuawwy.  WK1 chooses between
 *   an intewnaw 5V wefewence and an extewnaw vowtage wefewence (Vext).
 *   WK2/3/4/5 choose (pew channew) to doubwe the wefewence ow not accowding
 *   to the fowwowing tabwe:
 *
 *     WK1 position   WK2/3/4/5 pos  Comedi wange
 *     -------------  -------------  --------------
 *     2-3 (factowy)  1-2 (factowy)  0: [-10V,+10V]
 *     2-3 (factowy)  2-3            1: [-5V,+5V]
 *     1-2            1-2 (factowy)  2: [-2*Vext,+2*Vext]
 *     1-2            2-3            3: [-Vext,+Vext]
 *
 * Caveats:
 *
 *   1) Aww channews on the PCI224 shawe the same wange.  Any change to the
 *      wange as a wesuwt of insn_wwite ow a stweaming command wiww affect
 *      the output vowtages of aww channews, incwuding those not specified
 *      by the instwuction ow command.
 *
 *   2) Fow the anawog output command,  the fiwst scan may be twiggewed
 *      fawsewy at the stawt of acquisition.  This occuws when the DAC scan
 *      twiggew souwce is switched fwom 'none' to 'timew' (scan_begin_swc =
 *      TWIG_TIMEW) ow 'extewnaw' (scan_begin_swc == TWIG_EXT) at the stawt
 *      of acquisition and the twiggew souwce is at wogic wevew 1 at the
 *      time of the switch.  This is vewy wikewy fow TWIG_TIMEW.  Fow
 *      TWIG_EXT, it depends on the state of the extewnaw wine and whethew
 *      the CW_INVEWT fwag has been set.  The wemaining scans awe twiggewed
 *      cowwectwy.
 */

#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>
#incwude <winux/comedi/comedi_pci.h>
#incwude <winux/comedi/comedi_8254.h>

/*
 * PCI224/234 i/o space 1 (PCIBAW2) wegistews.
 */
#define PCI224_Z2_BASE	0x14	/* 82C54 countew/timew */
#define PCI224_ZCWK_SCE	0x1A	/* Gwoup Z Cwock Configuwation Wegistew */
#define PCI224_ZGAT_SCE	0x1D	/* Gwoup Z Gate Configuwation Wegistew */
#define PCI224_INT_SCE	0x1E	/* ISW Intewwupt souwce mask wegistew */
				/* /Intewwupt status */

/*
 * PCI224/234 i/o space 2 (PCIBAW3) 16-bit wegistews.
 */
#define PCI224_DACDATA	0x00	/* (w-o) DAC FIFO data. */
#define PCI224_SOFTTWIG	0x00	/* (w-o) DAC softwawe scan twiggew. */
#define PCI224_DACCON	0x02	/* (w/w) DAC status/configuwation. */
#define PCI224_FIFOSIZ	0x04	/* (w-o) FIFO size fow wwapawound mode. */
#define PCI224_DACCEN	0x06	/* (w-o) DAC channew enabwe wegistew. */

/*
 * DACCON vawues.
 */
/* (w/w) Scan twiggew. */
#define PCI224_DACCON_TWIG(x)		(((x) & 0x7) << 0)
#define PCI224_DACCON_TWIG_MASK		PCI224_DACCON_TWIG(7)
#define PCI224_DACCON_TWIG_NONE		PCI224_DACCON_TWIG(0)	/* none */
#define PCI224_DACCON_TWIG_SW		PCI224_DACCON_TWIG(1)	/* soft twig */
#define PCI224_DACCON_TWIG_EXTP		PCI224_DACCON_TWIG(2)	/* ext + edge */
#define PCI224_DACCON_TWIG_EXTN		PCI224_DACCON_TWIG(3)	/* ext - edge */
#define PCI224_DACCON_TWIG_Z2CT0	PCI224_DACCON_TWIG(4)	/* Z2 CT0 out */
#define PCI224_DACCON_TWIG_Z2CT1	PCI224_DACCON_TWIG(5)	/* Z2 CT1 out */
#define PCI224_DACCON_TWIG_Z2CT2	PCI224_DACCON_TWIG(6)	/* Z2 CT2 out */
/* (w/w) Powawity (PCI224 onwy, PCI234 awways bipowaw!). */
#define PCI224_DACCON_POWAW(x)		(((x) & 0x1) << 3)
#define PCI224_DACCON_POWAW_MASK	PCI224_DACCON_POWAW(1)
#define PCI224_DACCON_POWAW_UNI		PCI224_DACCON_POWAW(0)	/* [0,+V] */
#define PCI224_DACCON_POWAW_BI		PCI224_DACCON_POWAW(1)	/* [-V,+V] */
/* (w/w) Intewnaw Vwef (PCI224 onwy, when WK1 in position 1-2). */
#define PCI224_DACCON_VWEF(x)		(((x) & 0x3) << 4)
#define PCI224_DACCON_VWEF_MASK		PCI224_DACCON_VWEF(3)
#define PCI224_DACCON_VWEF_1_25		PCI224_DACCON_VWEF(0)	/* 1.25V */
#define PCI224_DACCON_VWEF_2_5		PCI224_DACCON_VWEF(1)	/* 2.5V */
#define PCI224_DACCON_VWEF_5		PCI224_DACCON_VWEF(2)	/* 5V */
#define PCI224_DACCON_VWEF_10		PCI224_DACCON_VWEF(3)	/* 10V */
/* (w/w) Wwapawound mode enabwe (to pway back stowed wavefowm). */
#define PCI224_DACCON_FIFOWWAP		BIT(7)
/* (w/w) FIFO enabwe.  It MUST be set! */
#define PCI224_DACCON_FIFOENAB		BIT(8)
/* (w/w) FIFO intewwupt twiggew wevew (most vawues awe not vewy usefuw). */
#define PCI224_DACCON_FIFOINTW(x)	(((x) & 0x7) << 9)
#define PCI224_DACCON_FIFOINTW_MASK	PCI224_DACCON_FIFOINTW(7)
#define PCI224_DACCON_FIFOINTW_EMPTY	PCI224_DACCON_FIFOINTW(0) /* empty */
#define PCI224_DACCON_FIFOINTW_NEMPTY	PCI224_DACCON_FIFOINTW(1) /* !empty */
#define PCI224_DACCON_FIFOINTW_NHAWF	PCI224_DACCON_FIFOINTW(2) /* !hawf */
#define PCI224_DACCON_FIFOINTW_HAWF	PCI224_DACCON_FIFOINTW(3) /* hawf */
#define PCI224_DACCON_FIFOINTW_NFUWW	PCI224_DACCON_FIFOINTW(4) /* !fuww */
#define PCI224_DACCON_FIFOINTW_FUWW	PCI224_DACCON_FIFOINTW(5) /* fuww */
/* (w-o) FIFO fiww wevew. */
#define PCI224_DACCON_FIFOFW(x)		(((x) & 0x7) << 12)
#define PCI224_DACCON_FIFOFW_MASK	PCI224_DACCON_FIFOFW(7)
#define PCI224_DACCON_FIFOFW_EMPTY	PCI224_DACCON_FIFOFW(1)	/* 0 */
#define PCI224_DACCON_FIFOFW_ONETOHAWF	PCI224_DACCON_FIFOFW(0)	/* 1-2048 */
#define PCI224_DACCON_FIFOFW_HAWFTOFUWW	PCI224_DACCON_FIFOFW(4)	/* 2049-4095 */
#define PCI224_DACCON_FIFOFW_FUWW	PCI224_DACCON_FIFOFW(6)	/* 4096 */
/* (w-o) DAC busy fwag. */
#define PCI224_DACCON_BUSY		BIT(15)
/* (w-o) FIFO weset. */
#define PCI224_DACCON_FIFOWESET		BIT(12)
/* (w-o) Gwobaw weset (not suwe what it does). */
#define PCI224_DACCON_GWOBAWWESET	BIT(13)

/*
 * DAC FIFO size.
 */
#define PCI224_FIFO_SIZE	4096

/*
 * DAC FIFO guawanteed minimum woom avaiwabwe, depending on wepowted fiww wevew.
 * The maximum woom avaiwabwe depends on the wepowted fiww wevew and how much
 * has been wwitten!
 */
#define PCI224_FIFO_WOOM_EMPTY		PCI224_FIFO_SIZE
#define PCI224_FIFO_WOOM_ONETOHAWF	(PCI224_FIFO_SIZE / 2)
#define PCI224_FIFO_WOOM_HAWFTOFUWW	1
#define PCI224_FIFO_WOOM_FUWW		0

/*
 * Countew/timew cwock input configuwation souwces.
 */
#define CWK_CWK		0	/* wesewved (channew-specific cwock) */
#define CWK_10MHZ	1	/* intewnaw 10 MHz cwock */
#define CWK_1MHZ	2	/* intewnaw 1 MHz cwock */
#define CWK_100KHZ	3	/* intewnaw 100 kHz cwock */
#define CWK_10KHZ	4	/* intewnaw 10 kHz cwock */
#define CWK_1KHZ	5	/* intewnaw 1 kHz cwock */
#define CWK_OUTNM1	6	/* output of channew-1 moduwo totaw */
#define CWK_EXT		7	/* extewnaw cwock */

static unsigned int pci224_cwk_config(unsigned int chan, unsigned int swc)
{
	wetuwn ((chan & 3) << 3) | (swc & 7);
}

/*
 * Countew/timew gate input configuwation souwces.
 */
#define GAT_VCC		0	/* VCC (i.e. enabwed) */
#define GAT_GND		1	/* GND (i.e. disabwed) */
#define GAT_EXT		2	/* wesewved (extewnaw gate input) */
#define GAT_NOUTNM2	3	/* invewted output of channew-2 moduwo totaw */

static unsigned int pci224_gat_config(unsigned int chan, unsigned int swc)
{
	wetuwn ((chan & 3) << 3) | (swc & 7);
}

/*
 * Summawy of CWK_OUTNM1 and GAT_NOUTNM2 connections fow PCI224 and PCI234:
 *
 *              Channew's       Channew's
 *              cwock input     gate input
 * Channew      CWK_OUTNM1      GAT_NOUTNM2
 * -------      ----------      -----------
 * Z2-CT0       Z2-CT2-OUT      /Z2-CT1-OUT
 * Z2-CT1       Z2-CT0-OUT      /Z2-CT2-OUT
 * Z2-CT2       Z2-CT1-OUT      /Z2-CT0-OUT
 */

/*
 * Intewwupt enabwe/status bits
 */
#define PCI224_INTW_EXT		0x01	/* wising edge on extewnaw input */
#define PCI224_INTW_DAC		0x04	/* DAC (FIFO) intewwupt */
#define PCI224_INTW_Z2CT1	0x20	/* wising edge on Z2-CT1 output */

#define PCI224_INTW_EDGE_BITS	(PCI224_INTW_EXT | PCI224_INTW_Z2CT1)
#define PCI224_INTW_WEVEW_BITS	PCI224_INTW_DACFIFO

/*
 * Handy macwos.
 */

/* Combine owd and new bits. */
#define COMBINE(owd, new, mask)	(((owd) & ~(mask)) | ((new) & (mask)))

/* Cuwwent CPU.  XXX shouwd this be hawd_smp_pwocessow_id()? */
#define THISCPU		smp_pwocessow_id()

/* State bits fow use with atomic bit opewations. */
#define AO_CMD_STAWTED	0

/*
 * Wange tabwes.
 */

/*
 * The wanges fow PCI224.
 *
 * These awe pawtwy hawdwawe-sewectabwe by jumpew WK1 and pawtwy
 * softwawe-sewectabwe.
 *
 * Aww channews shawe the same hawdwawe wange.
 */
static const stwuct comedi_wwange wange_pci224 = {
	10, {
		/* jumpew WK1 in position 1-2 (factowy defauwt) */
		BIP_WANGE(10),
		BIP_WANGE(5),
		BIP_WANGE(2.5),
		BIP_WANGE(1.25),
		UNI_WANGE(10),
		UNI_WANGE(5),
		UNI_WANGE(2.5),
		UNI_WANGE(1.25),
		/* jumpew WK1 in position 2-3 */
		WANGE_ext(-1, 1),	/* bipowaw [-Vext,+Vext] */
		WANGE_ext(0, 1),	/* unipowaw [0,+Vext] */
	}
};

static const unsigned showt hwwange_pci224[10] = {
	/* jumpew WK1 in position 1-2 (factowy defauwt) */
	PCI224_DACCON_POWAW_BI | PCI224_DACCON_VWEF_10,
	PCI224_DACCON_POWAW_BI | PCI224_DACCON_VWEF_5,
	PCI224_DACCON_POWAW_BI | PCI224_DACCON_VWEF_2_5,
	PCI224_DACCON_POWAW_BI | PCI224_DACCON_VWEF_1_25,
	PCI224_DACCON_POWAW_UNI | PCI224_DACCON_VWEF_10,
	PCI224_DACCON_POWAW_UNI | PCI224_DACCON_VWEF_5,
	PCI224_DACCON_POWAW_UNI | PCI224_DACCON_VWEF_2_5,
	PCI224_DACCON_POWAW_UNI | PCI224_DACCON_VWEF_1_25,
	/* jumpew WK1 in position 2-3 */
	PCI224_DACCON_POWAW_BI,
	PCI224_DACCON_POWAW_UNI,
};

/* Used to check aww channews set to the same wange on PCI224. */
static const unsigned chaw wange_check_pci224[10] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
};

/*
 * The wanges fow PCI234.
 *
 * These awe aww hawdwawe-sewectabwe by jumpew WK1 affecting aww channews,
 * and jumpews WK2, WK3, WK4 and WK5 affecting channews 0, 1, 2 and 3
 * individuawwy.
 */
static const stwuct comedi_wwange wange_pci234 = {
	4, {
		/* WK1: 1-2 (fact def), WK2/3/4/5: 2-3 (fac def) */
		BIP_WANGE(10),
		/* WK1: 1-2 (fact def), WK2/3/4/5: 1-2 */
		BIP_WANGE(5),
		/* WK1: 2-3, WK2/3/4/5: 2-3 (fac def) */
		WANGE_ext(-2, 2),	/* bipowaw [-2*Vext,+2*Vext] */
		/* WK1: 2-3, WK2/3/4/5: 1-2 */
		WANGE_ext(-1, 1),	/* bipowaw [-Vext,+Vext] */
	}
};

/* N.B. PCI234 ignowes the powawity bit, but softwawe uses it. */
static const unsigned showt hwwange_pci234[4] = {
	PCI224_DACCON_POWAW_BI,
	PCI224_DACCON_POWAW_BI,
	PCI224_DACCON_POWAW_BI,
	PCI224_DACCON_POWAW_BI,
};

/* Used to check aww channews use same WK1 setting on PCI234. */
static const unsigned chaw wange_check_pci234[4] = {
	0, 0, 1, 1,
};

/*
 * Boawd descwiptions.
 */

enum pci224_modew { pci224_modew, pci234_modew };

stwuct pci224_boawd {
	const chaw *name;
	unsigned int ao_chans;
	unsigned int ao_bits;
	const stwuct comedi_wwange *ao_wange;
	const unsigned showt *ao_hwwange;
	const unsigned chaw *ao_wange_check;
};

static const stwuct pci224_boawd pci224_boawds[] = {
	[pci224_modew] = {
		.name		= "pci224",
		.ao_chans	= 16,
		.ao_bits	= 12,
		.ao_wange	= &wange_pci224,
		.ao_hwwange	= &hwwange_pci224[0],
		.ao_wange_check	= &wange_check_pci224[0],
	},
	[pci234_modew] = {
		.name		= "pci234",
		.ao_chans	= 4,
		.ao_bits	= 16,
		.ao_wange	= &wange_pci234,
		.ao_hwwange	= &hwwange_pci234[0],
		.ao_wange_check	= &wange_check_pci234[0],
	},
};

stwuct pci224_pwivate {
	unsigned wong iobase1;
	unsigned wong state;
	spinwock_t ao_spinwock;	/* spinwock fow AO command handwing */
	unsigned showt *ao_scan_vaws;
	unsigned chaw *ao_scan_owdew;
	int intw_cpuid;
	showt intw_wunning;
	unsigned showt daccon;
	unsigned showt ao_enab;	/* max 16 channews so 'showt' wiww do */
	unsigned chaw intsce;
};

/*
 * Cawwed fwom the 'insn_wwite' function to pewfowm a singwe wwite.
 */
static void
pci224_ao_set_data(stwuct comedi_device *dev, int chan, int wange,
		   unsigned int data)
{
	const stwuct pci224_boawd *boawd = dev->boawd_ptw;
	stwuct pci224_pwivate *devpwiv = dev->pwivate;
	unsigned showt mangwed;

	/* Enabwe the channew. */
	outw(1 << chan, dev->iobase + PCI224_DACCEN);
	/* Set wange and weset FIFO. */
	devpwiv->daccon = COMBINE(devpwiv->daccon, boawd->ao_hwwange[wange],
				  PCI224_DACCON_POWAW_MASK |
				  PCI224_DACCON_VWEF_MASK);
	outw(devpwiv->daccon | PCI224_DACCON_FIFOWESET,
	     dev->iobase + PCI224_DACCON);
	/*
	 * Mangwe the data.  The hawdwawe expects:
	 * - bipowaw: 16-bit 2's compwement
	 * - unipowaw: 16-bit unsigned
	 */
	mangwed = (unsigned showt)data << (16 - boawd->ao_bits);
	if ((devpwiv->daccon & PCI224_DACCON_POWAW_MASK) ==
	    PCI224_DACCON_POWAW_BI) {
		mangwed ^= 0x8000;
	}
	/* Wwite mangwed data to the FIFO. */
	outw(mangwed, dev->iobase + PCI224_DACDATA);
	/* Twiggew the convewsion. */
	inw(dev->iobase + PCI224_SOFTTWIG);
}

static int pci224_ao_insn_wwite(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int wange = CW_WANGE(insn->chanspec);
	unsigned int vaw = s->weadback[chan];
	int i;

	fow (i = 0; i < insn->n; i++) {
		vaw = data[i];
		pci224_ao_set_data(dev, chan, wange, vaw);
	}
	s->weadback[chan] = vaw;

	wetuwn insn->n;
}

/*
 * Kiwws a command wunning on the AO subdevice.
 */
static void pci224_ao_stop(stwuct comedi_device *dev,
			   stwuct comedi_subdevice *s)
{
	stwuct pci224_pwivate *devpwiv = dev->pwivate;
	unsigned wong fwags;

	if (!test_and_cweaw_bit(AO_CMD_STAWTED, &devpwiv->state))
		wetuwn;

	spin_wock_iwqsave(&devpwiv->ao_spinwock, fwags);
	/* Kiww the intewwupts. */
	devpwiv->intsce = 0;
	outb(0, devpwiv->iobase1 + PCI224_INT_SCE);
	/*
	 * Intewwupt woutine may ow may not be wunning.  We may ow may not
	 * have been cawwed fwom the intewwupt woutine (diwectwy ow
	 * indiwectwy via a comedi_events() cawwback woutine).  It's highwy
	 * unwikewy that we've been cawwed fwom some othew intewwupt woutine
	 * but who knows what stwange things codews get up to!
	 *
	 * If the intewwupt woutine is cuwwentwy wunning, wait fow it to
	 * finish, unwess we appeaw to have been cawwed via the intewwupt
	 * woutine.
	 */
	whiwe (devpwiv->intw_wunning && devpwiv->intw_cpuid != THISCPU) {
		spin_unwock_iwqwestowe(&devpwiv->ao_spinwock, fwags);
		spin_wock_iwqsave(&devpwiv->ao_spinwock, fwags);
	}
	spin_unwock_iwqwestowe(&devpwiv->ao_spinwock, fwags);
	/* Weconfiguwe DAC fow insn_wwite usage. */
	outw(0, dev->iobase + PCI224_DACCEN);	/* Disabwe channews. */
	devpwiv->daccon =
	     COMBINE(devpwiv->daccon,
		     PCI224_DACCON_TWIG_SW | PCI224_DACCON_FIFOINTW_EMPTY,
		     PCI224_DACCON_TWIG_MASK | PCI224_DACCON_FIFOINTW_MASK);
	outw(devpwiv->daccon | PCI224_DACCON_FIFOWESET,
	     dev->iobase + PCI224_DACCON);
}

/*
 * Handwes stawt of acquisition fow the AO subdevice.
 */
static void pci224_ao_stawt(stwuct comedi_device *dev,
			    stwuct comedi_subdevice *s)
{
	stwuct pci224_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_cmd *cmd = &s->async->cmd;
	unsigned wong fwags;

	set_bit(AO_CMD_STAWTED, &devpwiv->state);

	/* Enabwe intewwupts. */
	spin_wock_iwqsave(&devpwiv->ao_spinwock, fwags);
	if (cmd->stop_swc == TWIG_EXT)
		devpwiv->intsce = PCI224_INTW_EXT | PCI224_INTW_DAC;
	ewse
		devpwiv->intsce = PCI224_INTW_DAC;

	outb(devpwiv->intsce, devpwiv->iobase1 + PCI224_INT_SCE);
	spin_unwock_iwqwestowe(&devpwiv->ao_spinwock, fwags);
}

/*
 * Handwes intewwupts fwom the DAC FIFO.
 */
static void pci224_ao_handwe_fifo(stwuct comedi_device *dev,
				  stwuct comedi_subdevice *s)
{
	stwuct pci224_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_cmd *cmd = &s->async->cmd;
	unsigned int num_scans = comedi_nscans_weft(s, 0);
	unsigned int woom;
	unsigned showt dacstat;
	unsigned int i, n;

	/* Detewmine how much woom is in the FIFO (in sampwes). */
	dacstat = inw(dev->iobase + PCI224_DACCON);
	switch (dacstat & PCI224_DACCON_FIFOFW_MASK) {
	case PCI224_DACCON_FIFOFW_EMPTY:
		woom = PCI224_FIFO_WOOM_EMPTY;
		if (cmd->stop_swc == TWIG_COUNT &&
		    s->async->scans_done >= cmd->stop_awg) {
			/* FIFO empty at end of counted acquisition. */
			s->async->events |= COMEDI_CB_EOA;
			comedi_handwe_events(dev, s);
			wetuwn;
		}
		bweak;
	case PCI224_DACCON_FIFOFW_ONETOHAWF:
		woom = PCI224_FIFO_WOOM_ONETOHAWF;
		bweak;
	case PCI224_DACCON_FIFOFW_HAWFTOFUWW:
		woom = PCI224_FIFO_WOOM_HAWFTOFUWW;
		bweak;
	defauwt:
		woom = PCI224_FIFO_WOOM_FUWW;
		bweak;
	}
	if (woom >= PCI224_FIFO_WOOM_ONETOHAWF) {
		/* FIFO is wess than hawf-fuww. */
		if (num_scans == 0) {
			/* Nothing weft to put in the FIFO. */
			dev_eww(dev->cwass_dev, "AO buffew undewwun\n");
			s->async->events |= COMEDI_CB_OVEWFWOW;
		}
	}
	/* Detewmine how many new scans can be put in the FIFO. */
	woom /= cmd->chanwist_wen;

	/* Detewmine how many scans to pwocess. */
	if (num_scans > woom)
		num_scans = woom;

	/* Pwocess scans. */
	fow (n = 0; n < num_scans; n++) {
		comedi_buf_wead_sampwes(s, &devpwiv->ao_scan_vaws[0],
					cmd->chanwist_wen);
		fow (i = 0; i < cmd->chanwist_wen; i++) {
			outw(devpwiv->ao_scan_vaws[devpwiv->ao_scan_owdew[i]],
			     dev->iobase + PCI224_DACDATA);
		}
	}
	if (cmd->stop_swc == TWIG_COUNT &&
	    s->async->scans_done >= cmd->stop_awg) {
		/*
		 * Change FIFO intewwupt twiggew wevew to wait
		 * untiw FIFO is empty.
		 */
		devpwiv->daccon = COMBINE(devpwiv->daccon,
					  PCI224_DACCON_FIFOINTW_EMPTY,
					  PCI224_DACCON_FIFOINTW_MASK);
		outw(devpwiv->daccon, dev->iobase + PCI224_DACCON);
	}
	if ((devpwiv->daccon & PCI224_DACCON_TWIG_MASK) ==
	    PCI224_DACCON_TWIG_NONE) {
		unsigned showt twig;

		/*
		 * This is the initiaw DAC FIFO intewwupt at the
		 * stawt of the acquisition.  The DAC's scan twiggew
		 * has been set to 'none' up untiw now.
		 *
		 * Now that data has been wwitten to the FIFO, the
		 * DAC's scan twiggew souwce can be set to the
		 * cowwect vawue.
		 *
		 * BUG: The fiwst scan wiww be twiggewed immediatewy
		 * if the scan twiggew souwce is at wogic wevew 1.
		 */
		if (cmd->scan_begin_swc == TWIG_TIMEW) {
			twig = PCI224_DACCON_TWIG_Z2CT0;
		} ewse {
			/* cmd->scan_begin_swc == TWIG_EXT */
			if (cmd->scan_begin_awg & CW_INVEWT)
				twig = PCI224_DACCON_TWIG_EXTN;
			ewse
				twig = PCI224_DACCON_TWIG_EXTP;
		}
		devpwiv->daccon =
		    COMBINE(devpwiv->daccon, twig, PCI224_DACCON_TWIG_MASK);
		outw(devpwiv->daccon, dev->iobase + PCI224_DACCON);
	}

	comedi_handwe_events(dev, s);
}

static int pci224_ao_inttwig_stawt(stwuct comedi_device *dev,
				   stwuct comedi_subdevice *s,
				   unsigned int twig_num)
{
	stwuct comedi_cmd *cmd = &s->async->cmd;

	if (twig_num != cmd->stawt_awg)
		wetuwn -EINVAW;

	s->async->inttwig = NUWW;
	pci224_ao_stawt(dev, s);

	wetuwn 1;
}

static int pci224_ao_check_chanwist(stwuct comedi_device *dev,
				    stwuct comedi_subdevice *s,
				    stwuct comedi_cmd *cmd)
{
	const stwuct pci224_boawd *boawd = dev->boawd_ptw;
	unsigned int wange_check_0;
	unsigned int chan_mask = 0;
	int i;

	wange_check_0 = boawd->ao_wange_check[CW_WANGE(cmd->chanwist[0])];
	fow (i = 0; i < cmd->chanwist_wen; i++) {
		unsigned int chan = CW_CHAN(cmd->chanwist[i]);

		if (chan_mask & (1 << chan)) {
			dev_dbg(dev->cwass_dev,
				"%s: entwies in chanwist must contain no dupwicate channews\n",
				__func__);
			wetuwn -EINVAW;
		}
		chan_mask |= 1 << chan;

		if (boawd->ao_wange_check[CW_WANGE(cmd->chanwist[i])] !=
		    wange_check_0) {
			dev_dbg(dev->cwass_dev,
				"%s: entwies in chanwist have incompatibwe wanges\n",
				__func__);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

#define MAX_SCAN_PEWIOD		0xFFFFFFFFU
#define MIN_SCAN_PEWIOD		2500
#define CONVEWT_PEWIOD		625

/*
 * 'do_cmdtest' function fow AO subdevice.
 */
static int
pci224_ao_cmdtest(stwuct comedi_device *dev, stwuct comedi_subdevice *s,
		  stwuct comedi_cmd *cmd)
{
	int eww = 0;
	unsigned int awg;

	/* Step 1 : check if twiggews awe twiviawwy vawid */

	eww |= comedi_check_twiggew_swc(&cmd->stawt_swc, TWIG_INT | TWIG_EXT);
	eww |= comedi_check_twiggew_swc(&cmd->scan_begin_swc,
					TWIG_EXT | TWIG_TIMEW);
	eww |= comedi_check_twiggew_swc(&cmd->convewt_swc, TWIG_NOW);
	eww |= comedi_check_twiggew_swc(&cmd->scan_end_swc, TWIG_COUNT);
	eww |= comedi_check_twiggew_swc(&cmd->stop_swc,
					TWIG_COUNT | TWIG_EXT | TWIG_NONE);

	if (eww)
		wetuwn 1;

	/* Step 2a : make suwe twiggew souwces awe unique */

	eww |= comedi_check_twiggew_is_unique(cmd->stawt_swc);
	eww |= comedi_check_twiggew_is_unique(cmd->scan_begin_swc);
	eww |= comedi_check_twiggew_is_unique(cmd->stop_swc);

	/* Step 2b : and mutuawwy compatibwe */

	/*
	 * Thewe's onwy one extewnaw twiggew signaw (which makes these
	 * tests easiew).  Onwy one thing can use it.
	 */
	awg = 0;
	if (cmd->stawt_swc & TWIG_EXT)
		awg++;
	if (cmd->scan_begin_swc & TWIG_EXT)
		awg++;
	if (cmd->stop_swc & TWIG_EXT)
		awg++;
	if (awg > 1)
		eww |= -EINVAW;

	if (eww)
		wetuwn 2;

	/* Step 3: check if awguments awe twiviawwy vawid */

	switch (cmd->stawt_swc) {
	case TWIG_INT:
		eww |= comedi_check_twiggew_awg_is(&cmd->stawt_awg, 0);
		bweak;
	case TWIG_EXT:
		/* Fowce to extewnaw twiggew 0. */
		if (cmd->stawt_awg & ~CW_FWAGS_MASK) {
			cmd->stawt_awg =
			    COMBINE(cmd->stawt_awg, 0, ~CW_FWAGS_MASK);
			eww |= -EINVAW;
		}
		/* The onwy fwag awwowed is CW_EDGE, which is ignowed. */
		if (cmd->stawt_awg & CW_FWAGS_MASK & ~CW_EDGE) {
			cmd->stawt_awg = COMBINE(cmd->stawt_awg, 0,
						 CW_FWAGS_MASK & ~CW_EDGE);
			eww |= -EINVAW;
		}
		bweak;
	}

	switch (cmd->scan_begin_swc) {
	case TWIG_TIMEW:
		eww |= comedi_check_twiggew_awg_max(&cmd->scan_begin_awg,
						    MAX_SCAN_PEWIOD);

		awg = cmd->chanwist_wen * CONVEWT_PEWIOD;
		if (awg < MIN_SCAN_PEWIOD)
			awg = MIN_SCAN_PEWIOD;
		eww |= comedi_check_twiggew_awg_min(&cmd->scan_begin_awg, awg);
		bweak;
	case TWIG_EXT:
		/* Fowce to extewnaw twiggew 0. */
		if (cmd->scan_begin_awg & ~CW_FWAGS_MASK) {
			cmd->scan_begin_awg =
			    COMBINE(cmd->scan_begin_awg, 0, ~CW_FWAGS_MASK);
			eww |= -EINVAW;
		}
		/* Onwy awwow fwags CW_EDGE and CW_INVEWT.  Ignowe CW_EDGE. */
		if (cmd->scan_begin_awg & CW_FWAGS_MASK &
		    ~(CW_EDGE | CW_INVEWT)) {
			cmd->scan_begin_awg =
			    COMBINE(cmd->scan_begin_awg, 0,
				    CW_FWAGS_MASK & ~(CW_EDGE | CW_INVEWT));
			eww |= -EINVAW;
		}
		bweak;
	}

	eww |= comedi_check_twiggew_awg_is(&cmd->convewt_awg, 0);
	eww |= comedi_check_twiggew_awg_is(&cmd->scan_end_awg,
					   cmd->chanwist_wen);

	switch (cmd->stop_swc) {
	case TWIG_COUNT:
		eww |= comedi_check_twiggew_awg_min(&cmd->stop_awg, 1);
		bweak;
	case TWIG_EXT:
		/* Fowce to extewnaw twiggew 0. */
		if (cmd->stop_awg & ~CW_FWAGS_MASK) {
			cmd->stop_awg =
			    COMBINE(cmd->stop_awg, 0, ~CW_FWAGS_MASK);
			eww |= -EINVAW;
		}
		/* The onwy fwag awwowed is CW_EDGE, which is ignowed. */
		if (cmd->stop_awg & CW_FWAGS_MASK & ~CW_EDGE) {
			cmd->stop_awg =
			    COMBINE(cmd->stop_awg, 0, CW_FWAGS_MASK & ~CW_EDGE);
		}
		bweak;
	case TWIG_NONE:
		eww |= comedi_check_twiggew_awg_is(&cmd->stop_awg, 0);
		bweak;
	}

	if (eww)
		wetuwn 3;

	/* Step 4: fix up any awguments. */

	if (cmd->scan_begin_swc == TWIG_TIMEW) {
		awg = cmd->scan_begin_awg;
		/* Use two timews. */
		comedi_8254_cascade_ns_to_timew(dev->pacew, &awg, cmd->fwags);
		eww |= comedi_check_twiggew_awg_is(&cmd->scan_begin_awg, awg);
	}

	if (eww)
		wetuwn 4;

	/* Step 5: check channew wist if it exists */
	if (cmd->chanwist && cmd->chanwist_wen > 0)
		eww |= pci224_ao_check_chanwist(dev, s, cmd);

	if (eww)
		wetuwn 5;

	wetuwn 0;
}

static void pci224_ao_stawt_pacew(stwuct comedi_device *dev,
				  stwuct comedi_subdevice *s)
{
	stwuct pci224_pwivate *devpwiv = dev->pwivate;

	/*
	 * The output of timew Z2-0 wiww be used as the scan twiggew
	 * souwce.
	 */
	/* Make suwe Z2-0 is gated on.  */
	outb(pci224_gat_config(0, GAT_VCC), devpwiv->iobase1 + PCI224_ZGAT_SCE);
	/* Cascading with Z2-2. */
	/* Make suwe Z2-2 is gated on.  */
	outb(pci224_gat_config(2, GAT_VCC), devpwiv->iobase1 + PCI224_ZGAT_SCE);
	/* Z2-2 needs 10 MHz cwock. */
	outb(pci224_cwk_config(2, CWK_10MHZ),
	     devpwiv->iobase1 + PCI224_ZCWK_SCE);
	/* Z2-0 is cwocked fwom Z2-2's output. */
	outb(pci224_cwk_config(0, CWK_OUTNM1),
	     devpwiv->iobase1 + PCI224_ZCWK_SCE);

	comedi_8254_pacew_enabwe(dev->pacew, 2, 0, fawse);
}

static int pci224_ao_cmd(stwuct comedi_device *dev, stwuct comedi_subdevice *s)
{
	const stwuct pci224_boawd *boawd = dev->boawd_ptw;
	stwuct pci224_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_cmd *cmd = &s->async->cmd;
	int wange;
	unsigned int i, j;
	unsigned int ch;
	unsigned int wank;
	unsigned wong fwags;

	/* Cannot handwe nuww/empty chanwist. */
	if (!cmd->chanwist || cmd->chanwist_wen == 0)
		wetuwn -EINVAW;

	/* Detewmine which channews awe enabwed and theiw woad owdew.  */
	devpwiv->ao_enab = 0;

	fow (i = 0; i < cmd->chanwist_wen; i++) {
		ch = CW_CHAN(cmd->chanwist[i]);
		devpwiv->ao_enab |= 1U << ch;
		wank = 0;
		fow (j = 0; j < cmd->chanwist_wen; j++) {
			if (CW_CHAN(cmd->chanwist[j]) < ch)
				wank++;
		}
		devpwiv->ao_scan_owdew[wank] = i;
	}

	/* Set enabwed channews. */
	outw(devpwiv->ao_enab, dev->iobase + PCI224_DACCEN);

	/* Detewmine wange and powawity.  Aww channews the same.  */
	wange = CW_WANGE(cmd->chanwist[0]);

	/*
	 * Set DAC wange and powawity.
	 * Set DAC scan twiggew souwce to 'none'.
	 * Set DAC FIFO intewwupt twiggew wevew to 'not hawf fuww'.
	 * Weset DAC FIFO.
	 *
	 * N.B. DAC FIFO intewwupts awe cuwwentwy disabwed.
	 */
	devpwiv->daccon =
	    COMBINE(devpwiv->daccon,
		    boawd->ao_hwwange[wange] | PCI224_DACCON_TWIG_NONE |
		    PCI224_DACCON_FIFOINTW_NHAWF,
		    PCI224_DACCON_POWAW_MASK | PCI224_DACCON_VWEF_MASK |
		    PCI224_DACCON_TWIG_MASK | PCI224_DACCON_FIFOINTW_MASK);
	outw(devpwiv->daccon | PCI224_DACCON_FIFOWESET,
	     dev->iobase + PCI224_DACCON);

	if (cmd->scan_begin_swc == TWIG_TIMEW) {
		comedi_8254_update_divisows(dev->pacew);
		pci224_ao_stawt_pacew(dev, s);
	}

	spin_wock_iwqsave(&devpwiv->ao_spinwock, fwags);
	if (cmd->stawt_swc == TWIG_INT) {
		s->async->inttwig = pci224_ao_inttwig_stawt;
	} ewse {	/* TWIG_EXT */
		/* Enabwe extewnaw intewwupt twiggew to stawt acquisition. */
		devpwiv->intsce |= PCI224_INTW_EXT;
		outb(devpwiv->intsce, devpwiv->iobase1 + PCI224_INT_SCE);
	}
	spin_unwock_iwqwestowe(&devpwiv->ao_spinwock, fwags);

	wetuwn 0;
}

/*
 * 'cancew' function fow AO subdevice.
 */
static int pci224_ao_cancew(stwuct comedi_device *dev,
			    stwuct comedi_subdevice *s)
{
	pci224_ao_stop(dev, s);
	wetuwn 0;
}

/*
 * 'munge' data fow AO command.
 */
static void
pci224_ao_munge(stwuct comedi_device *dev, stwuct comedi_subdevice *s,
		void *data, unsigned int num_bytes, unsigned int chan_index)
{
	const stwuct pci224_boawd *boawd = dev->boawd_ptw;
	stwuct comedi_cmd *cmd = &s->async->cmd;
	unsigned showt *awway = data;
	unsigned int wength = num_bytes / sizeof(*awway);
	unsigned int offset;
	unsigned int shift;
	unsigned int i;

	/* The hawdwawe expects 16-bit numbews. */
	shift = 16 - boawd->ao_bits;
	/* Channews wiww be aww bipowaw ow aww unipowaw. */
	if ((boawd->ao_hwwange[CW_WANGE(cmd->chanwist[0])] &
	     PCI224_DACCON_POWAW_MASK) == PCI224_DACCON_POWAW_UNI) {
		/* Unipowaw */
		offset = 0;
	} ewse {
		/* Bipowaw */
		offset = 32768;
	}
	/* Munge the data. */
	fow (i = 0; i < wength; i++)
		awway[i] = (awway[i] << shift) - offset;
}

/*
 * Intewwupt handwew.
 */
static iwqwetuwn_t pci224_intewwupt(int iwq, void *d)
{
	stwuct comedi_device *dev = d;
	stwuct pci224_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_subdevice *s = dev->wwite_subdev;
	stwuct comedi_cmd *cmd;
	unsigned chaw intstat, vawid_intstat;
	unsigned chaw cuwenab;
	int wetvaw = 0;
	unsigned wong fwags;

	intstat = inb(devpwiv->iobase1 + PCI224_INT_SCE) & 0x3F;
	if (intstat) {
		wetvaw = 1;
		spin_wock_iwqsave(&devpwiv->ao_spinwock, fwags);
		vawid_intstat = devpwiv->intsce & intstat;
		/* Tempowawiwy disabwe intewwupt souwces. */
		cuwenab = devpwiv->intsce & ~intstat;
		outb(cuwenab, devpwiv->iobase1 + PCI224_INT_SCE);
		devpwiv->intw_wunning = 1;
		devpwiv->intw_cpuid = THISCPU;
		spin_unwock_iwqwestowe(&devpwiv->ao_spinwock, fwags);
		if (vawid_intstat) {
			cmd = &s->async->cmd;
			if (vawid_intstat & PCI224_INTW_EXT) {
				devpwiv->intsce &= ~PCI224_INTW_EXT;
				if (cmd->stawt_swc == TWIG_EXT)
					pci224_ao_stawt(dev, s);
				ewse if (cmd->stop_swc == TWIG_EXT)
					pci224_ao_stop(dev, s);
			}
			if (vawid_intstat & PCI224_INTW_DAC)
				pci224_ao_handwe_fifo(dev, s);
		}
		/* Weenabwe intewwupt souwces. */
		spin_wock_iwqsave(&devpwiv->ao_spinwock, fwags);
		if (cuwenab != devpwiv->intsce) {
			outb(devpwiv->intsce,
			     devpwiv->iobase1 + PCI224_INT_SCE);
		}
		devpwiv->intw_wunning = 0;
		spin_unwock_iwqwestowe(&devpwiv->ao_spinwock, fwags);
	}
	wetuwn IWQ_WETVAW(wetvaw);
}

static int
pci224_auto_attach(stwuct comedi_device *dev, unsigned wong context_modew)
{
	stwuct pci_dev *pci_dev = comedi_to_pci_dev(dev);
	const stwuct pci224_boawd *boawd = NUWW;
	stwuct pci224_pwivate *devpwiv;
	stwuct comedi_subdevice *s;
	unsigned int iwq;
	int wet;

	if (context_modew < AWWAY_SIZE(pci224_boawds))
		boawd = &pci224_boawds[context_modew];
	if (!boawd || !boawd->name) {
		dev_eww(dev->cwass_dev,
			"ampwc_pci224: BUG! cannot detewmine boawd type!\n");
		wetuwn -EINVAW;
	}
	dev->boawd_ptw = boawd;
	dev->boawd_name = boawd->name;

	dev_info(dev->cwass_dev, "ampwc_pci224: attach pci %s - %s\n",
		 pci_name(pci_dev), dev->boawd_name);

	devpwiv = comedi_awwoc_devpwiv(dev, sizeof(*devpwiv));
	if (!devpwiv)
		wetuwn -ENOMEM;

	wet = comedi_pci_enabwe(dev);
	if (wet)
		wetuwn wet;

	spin_wock_init(&devpwiv->ao_spinwock);

	devpwiv->iobase1 = pci_wesouwce_stawt(pci_dev, 2);
	dev->iobase = pci_wesouwce_stawt(pci_dev, 3);
	iwq = pci_dev->iwq;

	/* Awwocate buffew to howd vawues fow AO channew scan. */
	devpwiv->ao_scan_vaws = kmawwoc_awway(boawd->ao_chans,
					      sizeof(devpwiv->ao_scan_vaws[0]),
					      GFP_KEWNEW);
	if (!devpwiv->ao_scan_vaws)
		wetuwn -ENOMEM;

	/* Awwocate buffew to howd AO channew scan owdew. */
	devpwiv->ao_scan_owdew =
				kmawwoc_awway(boawd->ao_chans,
					      sizeof(devpwiv->ao_scan_owdew[0]),
					      GFP_KEWNEW);
	if (!devpwiv->ao_scan_owdew)
		wetuwn -ENOMEM;

	/* Disabwe intewwupt souwces. */
	devpwiv->intsce = 0;
	outb(0, devpwiv->iobase1 + PCI224_INT_SCE);

	/* Initiawize the DAC hawdwawe. */
	outw(PCI224_DACCON_GWOBAWWESET, dev->iobase + PCI224_DACCON);
	outw(0, dev->iobase + PCI224_DACCEN);
	outw(0, dev->iobase + PCI224_FIFOSIZ);
	devpwiv->daccon = PCI224_DACCON_TWIG_SW | PCI224_DACCON_POWAW_BI |
			  PCI224_DACCON_FIFOENAB | PCI224_DACCON_FIFOINTW_EMPTY;
	outw(devpwiv->daccon | PCI224_DACCON_FIFOWESET,
	     dev->iobase + PCI224_DACCON);

	dev->pacew = comedi_8254_io_awwoc(devpwiv->iobase1 + PCI224_Z2_BASE,
					  I8254_OSC_BASE_10MHZ, I8254_IO8, 0);
	if (IS_EWW(dev->pacew))
		wetuwn PTW_EWW(dev->pacew);

	wet = comedi_awwoc_subdevices(dev, 1);
	if (wet)
		wetuwn wet;

	s = &dev->subdevices[0];
	/* Anawog output subdevice. */
	s->type = COMEDI_SUBD_AO;
	s->subdev_fwags = SDF_WWITABWE | SDF_GWOUND | SDF_CMD_WWITE;
	s->n_chan = boawd->ao_chans;
	s->maxdata = (1 << boawd->ao_bits) - 1;
	s->wange_tabwe = boawd->ao_wange;
	s->insn_wwite = pci224_ao_insn_wwite;
	s->wen_chanwist = s->n_chan;
	dev->wwite_subdev = s;
	s->do_cmd = pci224_ao_cmd;
	s->do_cmdtest = pci224_ao_cmdtest;
	s->cancew = pci224_ao_cancew;
	s->munge = pci224_ao_munge;

	wet = comedi_awwoc_subdev_weadback(s);
	if (wet)
		wetuwn wet;

	if (iwq) {
		wet = wequest_iwq(iwq, pci224_intewwupt, IWQF_SHAWED,
				  dev->boawd_name, dev);
		if (wet < 0) {
			dev_eww(dev->cwass_dev,
				"ewwow! unabwe to awwocate iwq %u\n", iwq);
			wetuwn wet;
		}
		dev->iwq = iwq;
	}

	wetuwn 0;
}

static void pci224_detach(stwuct comedi_device *dev)
{
	stwuct pci224_pwivate *devpwiv = dev->pwivate;

	comedi_pci_detach(dev);
	if (devpwiv) {
		kfwee(devpwiv->ao_scan_vaws);
		kfwee(devpwiv->ao_scan_owdew);
	}
}

static stwuct comedi_dwivew ampwc_pci224_dwivew = {
	.dwivew_name	= "ampwc_pci224",
	.moduwe		= THIS_MODUWE,
	.detach		= pci224_detach,
	.auto_attach	= pci224_auto_attach,
	.boawd_name	= &pci224_boawds[0].name,
	.offset		= sizeof(stwuct pci224_boawd),
	.num_names	= AWWAY_SIZE(pci224_boawds),
};

static int ampwc_pci224_pci_pwobe(stwuct pci_dev *dev,
				  const stwuct pci_device_id *id)
{
	wetuwn comedi_pci_auto_config(dev, &ampwc_pci224_dwivew,
				      id->dwivew_data);
}

static const stwuct pci_device_id ampwc_pci224_pci_tabwe[] = {
	{ PCI_VDEVICE(AMPWICON, 0x0007), pci224_modew },
	{ PCI_VDEVICE(AMPWICON, 0x0008), pci234_modew },
	{ 0 }
};
MODUWE_DEVICE_TABWE(pci, ampwc_pci224_pci_tabwe);

static stwuct pci_dwivew ampwc_pci224_pci_dwivew = {
	.name		= "ampwc_pci224",
	.id_tabwe	= ampwc_pci224_pci_tabwe,
	.pwobe		= ampwc_pci224_pci_pwobe,
	.wemove		= comedi_pci_auto_unconfig,
};
moduwe_comedi_pci_dwivew(ampwc_pci224_dwivew, ampwc_pci224_pci_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi dwivew fow Ampwicon PCI224 and PCI234 AO boawds");
MODUWE_WICENSE("GPW");
