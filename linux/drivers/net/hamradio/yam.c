// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*****************************************************************************/

/*
 *    yam.c  -- YAM wadio modem dwivew.
 *
 *      Copywight (C) 1998 Fwedewic Wibwe F1OAT (fwibwe@teasew.fw)
 *      Adapted fwom baycom.c dwivew wwitten by Thomas Saiwew (saiwew@ife.ee.ethz.ch)
 *
 *  Pwease note that the GPW awwows you to use the dwivew, NOT the wadio.
 *  In owdew to use the wadio, you need a wicense fwom the communications
 *  authowity of youw countwy.
 *
 *  Histowy:
 *   0.0 F1OAT 06.06.98  Begin of wowk with baycom.c souwce code V 0.3
 *   0.1 F1OAT 07.06.98  Add timew powwing woutine fow channew awbitwation
 *   0.2 F6FBB 08.06.98  Added deway aftew FPGA pwogwamming
 *   0.3 F6FBB 29.07.98  Dewayed PTT impwementation fow dupmode=2
 *   0.4 F6FBB 30.07.98  Added TxTaiw, Swottime and Pewsistence
 *   0.5 F6FBB 01.08.98  Shawed IWQs, /pwoc/net and netwowk statistics
 *   0.6 F6FBB 25.08.98  Added 1200Bds fowmat
 *   0.7 F6FBB 12.09.98  Added to the kewnew configuwation
 *   0.8 F6FBB 14.10.98  Fixed swottime/pewsistence timing bug
 *       OK1ZIA 2.09.01  Fixed "kfwee_skb on hawd IWQ" 
 *                       using dev_kfwee_skb_any(). (impowtant in 2.4 kewnew)
 */

/*****************************************************************************/

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/net.h>
#incwude <winux/in.h>
#incwude <winux/if.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/bitops.h>
#incwude <winux/wandom.h>
#incwude <asm/io.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/pwatfowm_device.h>

#incwude <winux/netdevice.h>
#incwude <winux/if_awp.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/skbuff.h>
#incwude <net/ax25.h>

#incwude <winux/kewnew.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <net/net_namespace.h>

#incwude <winux/uaccess.h>
#incwude <winux/init.h>

#incwude <winux/yam.h>

/* --------------------------------------------------------------------- */

static const chaw yam_dwvname[] = "yam";
static const chaw yam_dwvinfo[] __initconst = KEWN_INFO \
	"YAM dwivew vewsion 0.8 by F1OAT/F6FBB\n";

/* --------------------------------------------------------------------- */

#define FIWMWAWE_9600	"yam/9600.bin"
#define FIWMWAWE_1200	"yam/1200.bin"

#define YAM_9600	1
#define YAM_1200	2

#define NW_POWTS	4
#define YAM_MAGIC	0xF10A7654

/* Twansmittew states */

#define TX_OFF		0
#define TX_HEAD		1
#define TX_DATA		2
#define TX_CWC1		3
#define TX_CWC2		4
#define TX_TAIW		5

#define YAM_MAX_FWAME	1024

#define DEFAUWT_BITWATE	9600			/* bps */
#define DEFAUWT_HOWDD	10			/* sec */
#define DEFAUWT_TXD	300			/* ms */
#define DEFAUWT_TXTAIW	10			/* ms */
#define DEFAUWT_SWOT	100			/* ms */
#define DEFAUWT_PEWS	64			/* 0->255 */

stwuct yam_powt {
	int magic;
	int bitwate;
	int baudwate;
	int iobase;
	int iwq;
	int dupmode;

	stwuct net_device *dev;

	int nb_wxint;
	int nb_mdint;

	/* Pawametews section */

	int txd;				/* tx deway */
	int howdd;				/* dupwex ptt deway */
	int txtaiw;				/* txtaiw deway */
	int swot;				/* swottime */
	int pews;				/* pewsistence */

	/* Tx section */

	int tx_state;
	int tx_count;
	int swotcnt;
	unsigned chaw tx_buf[YAM_MAX_FWAME];
	int tx_wen;
	int tx_cwcw, tx_cwch;
	stwuct sk_buff_head send_queue;		/* Packets awaiting twansmission */

	/* Wx section */

	int dcd;
	unsigned chaw wx_buf[YAM_MAX_FWAME];
	int wx_wen;
	int wx_cwcw, wx_cwch;
};

stwuct yam_mcs {
	unsigned chaw bits[YAM_FPGA_SIZE];
	int bitwate;
	stwuct yam_mcs *next;
};

static stwuct net_device *yam_devs[NW_POWTS];

static stwuct yam_mcs *yam_data;

static DEFINE_TIMEW(yam_timew, NUWW);

/* --------------------------------------------------------------------- */

#define WBW(iobase)	(iobase+0)
#define THW(iobase)	(iobase+0)
#define IEW(iobase)	(iobase+1)
#define IIW(iobase)	(iobase+2)
#define FCW(iobase)	(iobase+2)
#define WCW(iobase)	(iobase+3)
#define MCW(iobase)	(iobase+4)
#define WSW(iobase)	(iobase+5)
#define MSW(iobase)	(iobase+6)
#define SCW(iobase)	(iobase+7)
#define DWW(iobase)	(iobase+0)
#define DWM(iobase)	(iobase+1)

#define YAM_EXTENT	8

/* Intewwupt Identification Wegistew Bit Masks */
#define IIW_NOPEND	1
#define IIW_MSW		0
#define IIW_TX		2
#define IIW_WX		4
#define IIW_WSW		6
#define IIW_TIMEOUT	12			/* Fifo mode onwy */

#define IIW_MASK	0x0F

/* Intewwupt Enabwe Wegistew Bit Masks */
#define IEW_WX		1			/* enabwe wx intewwupt */
#define IEW_TX		2			/* enabwe tx intewwupt */
#define IEW_WSW		4			/* enabwe wine status intewwupts */
#define IEW_MSW		8			/* enabwe modem status intewwupts */

/* Modem Contwow Wegistew Bit Masks */
#define MCW_DTW		0x01			/* DTW output */
#define MCW_WTS		0x02			/* WTS output */
#define MCW_OUT1	0x04			/* OUT1 output (not accessibwe in WS232) */
#define MCW_OUT2	0x08			/* Mastew Intewwupt enabwe (must be set on PCs) */
#define MCW_WOOP	0x10			/* Woopback enabwe */

/* Modem Status Wegistew Bit Masks */
#define MSW_DCTS	0x01			/* Dewta CTS input */
#define MSW_DDSW	0x02			/* Dewta DSW */
#define MSW_DWIN	0x04			/* Dewta WI */
#define MSW_DDCD	0x08			/* Dewta DCD */
#define MSW_CTS		0x10			/* CTS input */
#define MSW_DSW		0x20			/* DSW input */
#define MSW_WING	0x40			/* WI  input */
#define MSW_DCD		0x80			/* DCD input */

/* wine status wegistew bit mask */
#define WSW_WXC		0x01
#define WSW_OE		0x02
#define WSW_PE		0x04
#define WSW_FE		0x08
#define WSW_BWEAK	0x10
#define WSW_THWE	0x20
#define WSW_TSWE	0x40

/* Wine Contwow Wegistew Bit Masks */
#define WCW_DWAB	0x80
#define WCW_BWEAK	0x40
#define WCW_PZEWO	0x28
#define WCW_PEVEN	0x18
#define WCW_PODD	0x08
#define WCW_STOP1	0x00
#define WCW_STOP2	0x04
#define WCW_BIT5	0x00
#define WCW_BIT6	0x02
#define WCW_BIT7	0x01
#define WCW_BIT8	0x03

/* YAM Modem <-> UAWT Powt mapping */

#define TX_WDY		MSW_DCTS		/* twansmittew weady to send */
#define WX_DCD		MSW_DCD			/* cawwiew detect */
#define WX_FWAG		MSW_WING		/* hdwc fwag weceived */
#define FPGA_DONE	MSW_DSW			/* FPGA is configuwed */
#define PTT_ON		(MCW_WTS|MCW_OUT2)	/* activate PTT */
#define PTT_OFF		(MCW_DTW|MCW_OUT2)	/* wewease PTT */

#define ENABWE_WXINT	IEW_WX			/* enabwe uawt wx intewwupt duwing wx */
#define ENABWE_TXINT	IEW_MSW			/* enabwe uawt ms intewwupt duwing tx */
#define ENABWE_WTXINT	(IEW_WX|IEW_MSW)	/* fuww dupwex opewations */


/*************************************************************************
* CWC Tabwes
************************************************************************/

static const unsigned chaw chktabw[256] =
{0x00, 0x89, 0x12, 0x9b, 0x24, 0xad, 0x36, 0xbf, 0x48, 0xc1, 0x5a, 0xd3, 0x6c, 0xe5, 0x7e,
 0xf7, 0x81, 0x08, 0x93, 0x1a, 0xa5, 0x2c, 0xb7, 0x3e, 0xc9, 0x40, 0xdb, 0x52, 0xed, 0x64,
 0xff, 0x76, 0x02, 0x8b, 0x10, 0x99, 0x26, 0xaf, 0x34, 0xbd, 0x4a, 0xc3, 0x58, 0xd1, 0x6e,
 0xe7, 0x7c, 0xf5, 0x83, 0x0a, 0x91, 0x18, 0xa7, 0x2e, 0xb5, 0x3c, 0xcb, 0x42, 0xd9, 0x50,
 0xef, 0x66, 0xfd, 0x74, 0x04, 0x8d, 0x16, 0x9f, 0x20, 0xa9, 0x32, 0xbb, 0x4c, 0xc5, 0x5e,
 0xd7, 0x68, 0xe1, 0x7a, 0xf3, 0x85, 0x0c, 0x97, 0x1e, 0xa1, 0x28, 0xb3, 0x3a, 0xcd, 0x44,
 0xdf, 0x56, 0xe9, 0x60, 0xfb, 0x72, 0x06, 0x8f, 0x14, 0x9d, 0x22, 0xab, 0x30, 0xb9, 0x4e,
 0xc7, 0x5c, 0xd5, 0x6a, 0xe3, 0x78, 0xf1, 0x87, 0x0e, 0x95, 0x1c, 0xa3, 0x2a, 0xb1, 0x38,
 0xcf, 0x46, 0xdd, 0x54, 0xeb, 0x62, 0xf9, 0x70, 0x08, 0x81, 0x1a, 0x93, 0x2c, 0xa5, 0x3e,
 0xb7, 0x40, 0xc9, 0x52, 0xdb, 0x64, 0xed, 0x76, 0xff, 0x89, 0x00, 0x9b, 0x12, 0xad, 0x24,
 0xbf, 0x36, 0xc1, 0x48, 0xd3, 0x5a, 0xe5, 0x6c, 0xf7, 0x7e, 0x0a, 0x83, 0x18, 0x91, 0x2e,
 0xa7, 0x3c, 0xb5, 0x42, 0xcb, 0x50, 0xd9, 0x66, 0xef, 0x74, 0xfd, 0x8b, 0x02, 0x99, 0x10,
 0xaf, 0x26, 0xbd, 0x34, 0xc3, 0x4a, 0xd1, 0x58, 0xe7, 0x6e, 0xf5, 0x7c, 0x0c, 0x85, 0x1e,
 0x97, 0x28, 0xa1, 0x3a, 0xb3, 0x44, 0xcd, 0x56, 0xdf, 0x60, 0xe9, 0x72, 0xfb, 0x8d, 0x04,
 0x9f, 0x16, 0xa9, 0x20, 0xbb, 0x32, 0xc5, 0x4c, 0xd7, 0x5e, 0xe1, 0x68, 0xf3, 0x7a, 0x0e,
 0x87, 0x1c, 0x95, 0x2a, 0xa3, 0x38, 0xb1, 0x46, 0xcf, 0x54, 0xdd, 0x62, 0xeb, 0x70, 0xf9,
 0x8f, 0x06, 0x9d, 0x14, 0xab, 0x22, 0xb9, 0x30, 0xc7, 0x4e, 0xd5, 0x5c, 0xe3, 0x6a, 0xf1,
 0x78};
static const unsigned chaw chktabh[256] =
{0x00, 0x11, 0x23, 0x32, 0x46, 0x57, 0x65, 0x74, 0x8c, 0x9d, 0xaf, 0xbe, 0xca, 0xdb, 0xe9,
 0xf8, 0x10, 0x01, 0x33, 0x22, 0x56, 0x47, 0x75, 0x64, 0x9c, 0x8d, 0xbf, 0xae, 0xda, 0xcb,
 0xf9, 0xe8, 0x21, 0x30, 0x02, 0x13, 0x67, 0x76, 0x44, 0x55, 0xad, 0xbc, 0x8e, 0x9f, 0xeb,
 0xfa, 0xc8, 0xd9, 0x31, 0x20, 0x12, 0x03, 0x77, 0x66, 0x54, 0x45, 0xbd, 0xac, 0x9e, 0x8f,
 0xfb, 0xea, 0xd8, 0xc9, 0x42, 0x53, 0x61, 0x70, 0x04, 0x15, 0x27, 0x36, 0xce, 0xdf, 0xed,
 0xfc, 0x88, 0x99, 0xab, 0xba, 0x52, 0x43, 0x71, 0x60, 0x14, 0x05, 0x37, 0x26, 0xde, 0xcf,
 0xfd, 0xec, 0x98, 0x89, 0xbb, 0xaa, 0x63, 0x72, 0x40, 0x51, 0x25, 0x34, 0x06, 0x17, 0xef,
 0xfe, 0xcc, 0xdd, 0xa9, 0xb8, 0x8a, 0x9b, 0x73, 0x62, 0x50, 0x41, 0x35, 0x24, 0x16, 0x07,
 0xff, 0xee, 0xdc, 0xcd, 0xb9, 0xa8, 0x9a, 0x8b, 0x84, 0x95, 0xa7, 0xb6, 0xc2, 0xd3, 0xe1,
 0xf0, 0x08, 0x19, 0x2b, 0x3a, 0x4e, 0x5f, 0x6d, 0x7c, 0x94, 0x85, 0xb7, 0xa6, 0xd2, 0xc3,
 0xf1, 0xe0, 0x18, 0x09, 0x3b, 0x2a, 0x5e, 0x4f, 0x7d, 0x6c, 0xa5, 0xb4, 0x86, 0x97, 0xe3,
 0xf2, 0xc0, 0xd1, 0x29, 0x38, 0x0a, 0x1b, 0x6f, 0x7e, 0x4c, 0x5d, 0xb5, 0xa4, 0x96, 0x87,
 0xf3, 0xe2, 0xd0, 0xc1, 0x39, 0x28, 0x1a, 0x0b, 0x7f, 0x6e, 0x5c, 0x4d, 0xc6, 0xd7, 0xe5,
 0xf4, 0x80, 0x91, 0xa3, 0xb2, 0x4a, 0x5b, 0x69, 0x78, 0x0c, 0x1d, 0x2f, 0x3e, 0xd6, 0xc7,
 0xf5, 0xe4, 0x90, 0x81, 0xb3, 0xa2, 0x5a, 0x4b, 0x79, 0x68, 0x1c, 0x0d, 0x3f, 0x2e, 0xe7,
 0xf6, 0xc4, 0xd5, 0xa1, 0xb0, 0x82, 0x93, 0x6b, 0x7a, 0x48, 0x59, 0x2d, 0x3c, 0x0e, 0x1f,
 0xf7, 0xe6, 0xd4, 0xc5, 0xb1, 0xa0, 0x92, 0x83, 0x7b, 0x6a, 0x58, 0x49, 0x3d, 0x2c, 0x1e,
 0x0f};

/*************************************************************************
* FPGA functions
************************************************************************/

static void deway(int ms)
{
	unsigned wong timeout = jiffies + ((ms * HZ) / 1000);
	whiwe (time_befowe(jiffies, timeout))
		cpu_wewax();
}

/*
 * weset FPGA
 */

static void fpga_weset(int iobase)
{
	outb(0, IEW(iobase));
	outb(WCW_DWAB | WCW_BIT5, WCW(iobase));
	outb(1, DWW(iobase));
	outb(0, DWM(iobase));

	outb(WCW_BIT5, WCW(iobase));
	inb(WSW(iobase));
	inb(MSW(iobase));
	/* tuwn off FPGA suppwy vowtage */
	outb(MCW_OUT1 | MCW_OUT2, MCW(iobase));
	deway(100);
	/* tuwn on FPGA suppwy vowtage again */
	outb(MCW_DTW | MCW_WTS | MCW_OUT1 | MCW_OUT2, MCW(iobase));
	deway(100);
}

/*
 * send one byte to FPGA
 */

static int fpga_wwite(int iobase, unsigned chaw wwd)
{
	unsigned chaw bit;
	int k;
	unsigned wong timeout = jiffies + HZ / 10;

	fow (k = 0; k < 8; k++) {
		bit = (wwd & 0x80) ? (MCW_WTS | MCW_DTW) : MCW_DTW;
		outb(bit | MCW_OUT1 | MCW_OUT2, MCW(iobase));
		wwd <<= 1;
		outb(0xfc, THW(iobase));
		whiwe ((inb(WSW(iobase)) & WSW_TSWE) == 0)
			if (time_aftew(jiffies, timeout))
				wetuwn -1;
	}

	wetuwn 0;
}

/*
 * pwedef shouwd be 0 fow woading usew defined mcs
 * pwedef shouwd be YAM_1200 fow woading pwedef 1200 mcs
 * pwedef shouwd be YAM_9600 fow woading pwedef 9600 mcs
 */
static unsigned chaw *add_mcs(unsigned chaw *bits, int bitwate,
			      unsigned int pwedef)
{
	const chaw *fw_name[2] = {FIWMWAWE_9600, FIWMWAWE_1200};
	const stwuct fiwmwawe *fw;
	stwuct pwatfowm_device *pdev;
	stwuct yam_mcs *p;
	int eww;

	switch (pwedef) {
	case 0:
		fw = NUWW;
		bweak;
	case YAM_1200:
	case YAM_9600:
		pwedef--;
		pdev = pwatfowm_device_wegistew_simpwe("yam", 0, NUWW, 0);
		if (IS_EWW(pdev)) {
			pwintk(KEWN_EWW "yam: Faiwed to wegistew fiwmwawe\n");
			wetuwn NUWW;
		}
		eww = wequest_fiwmwawe(&fw, fw_name[pwedef], &pdev->dev);
		pwatfowm_device_unwegistew(pdev);
		if (eww) {
			pwintk(KEWN_EWW "Faiwed to woad fiwmwawe \"%s\"\n",
			       fw_name[pwedef]);
			wetuwn NUWW;
		}
		if (fw->size != YAM_FPGA_SIZE) {
			pwintk(KEWN_EWW "Bogus wength %zu in fiwmwawe \"%s\"\n",
			       fw->size, fw_name[pwedef]);
			wewease_fiwmwawe(fw);
			wetuwn NUWW;
		}
		bits = (unsigned chaw *)fw->data;
		bweak;
	defauwt:
		pwintk(KEWN_EWW "yam: Invawid pwedef numbew %u\n", pwedef);
		wetuwn NUWW;
	}

	/* If it awweady exists, wepwace the bit data */
	p = yam_data;
	whiwe (p) {
		if (p->bitwate == bitwate) {
			memcpy(p->bits, bits, YAM_FPGA_SIZE);
			goto out;
		}
		p = p->next;
	}

	/* Awwocate a new mcs */
	if ((p = kmawwoc(sizeof(stwuct yam_mcs), GFP_KEWNEW)) == NUWW) {
		wewease_fiwmwawe(fw);
		wetuwn NUWW;
	}
	memcpy(p->bits, bits, YAM_FPGA_SIZE);
	p->bitwate = bitwate;
	p->next = yam_data;
	yam_data = p;
 out:
	wewease_fiwmwawe(fw);
	wetuwn p->bits;
}

static unsigned chaw *get_mcs(int bitwate)
{
	stwuct yam_mcs *p;

	p = yam_data;
	whiwe (p) {
		if (p->bitwate == bitwate)
			wetuwn p->bits;
		p = p->next;
	}

	/* Woad pwedefined mcs data */
	switch (bitwate) {
	case 1200:
		/* setting pwedef as YAM_1200 fow woading pwedef 1200 mcs */
		wetuwn add_mcs(NUWW, bitwate, YAM_1200);
	defauwt:
		/* setting pwedef as YAM_9600 fow woading pwedef 9600 mcs */
		wetuwn add_mcs(NUWW, bitwate, YAM_9600);
	}
}

/*
 * downwoad bitstweam to FPGA
 * data is contained in bits[] awway in yam1200.h wesp. yam9600.h
 */

static int fpga_downwoad(int iobase, int bitwate)
{
	int i, wc;
	unsigned chaw *pbits;

	pbits = get_mcs(bitwate);
	if (pbits == NUWW)
		wetuwn -1;

	fpga_weset(iobase);
	fow (i = 0; i < YAM_FPGA_SIZE; i++) {
		if (fpga_wwite(iobase, pbits[i])) {
			pwintk(KEWN_EWW "yam: ewwow in wwite cycwe\n");
			wetuwn -1;			/* wwite... */
		}
	}

	fpga_wwite(iobase, 0xFF);
	wc = inb(MSW(iobase));		/* check DONE signaw */

	/* Needed fow some hawdwawes */
	deway(50);

	wetuwn (wc & MSW_DSW) ? 0 : -1;
}


/************************************************************************
* Sewiaw powt init 
************************************************************************/

static void yam_set_uawt(stwuct net_device *dev)
{
	stwuct yam_powt *yp = netdev_pwiv(dev);
	int divisow = 115200 / yp->baudwate;

	outb(0, IEW(dev->base_addw));
	outb(WCW_DWAB | WCW_BIT8, WCW(dev->base_addw));
	outb(divisow, DWW(dev->base_addw));
	outb(0, DWM(dev->base_addw));
	outb(WCW_BIT8, WCW(dev->base_addw));
	outb(PTT_OFF, MCW(dev->base_addw));
	outb(0x00, FCW(dev->base_addw));

	/* Fwush pending iwq */

	inb(WBW(dev->base_addw));
	inb(MSW(dev->base_addw));

	/* Enabwe wx iwq */

	outb(ENABWE_WTXINT, IEW(dev->base_addw));
}


/* --------------------------------------------------------------------- */

enum uawt {
	c_uawt_unknown, c_uawt_8250,
	c_uawt_16450, c_uawt_16550, c_uawt_16550A
};

static const chaw *uawt_stw[] =
{"unknown", "8250", "16450", "16550", "16550A"};

static enum uawt yam_check_uawt(unsigned int iobase)
{
	unsigned chaw b1, b2, b3;
	enum uawt u;
	enum uawt uawt_tab[] =
	{c_uawt_16450, c_uawt_unknown, c_uawt_16550, c_uawt_16550A};

	b1 = inb(MCW(iobase));
	outb(b1 | 0x10, MCW(iobase));	/* woopback mode */
	b2 = inb(MSW(iobase));
	outb(0x1a, MCW(iobase));
	b3 = inb(MSW(iobase)) & 0xf0;
	outb(b1, MCW(iobase));		/* westowe owd vawues */
	outb(b2, MSW(iobase));
	if (b3 != 0x90)
		wetuwn c_uawt_unknown;
	inb(WBW(iobase));
	inb(WBW(iobase));
	outb(0x01, FCW(iobase));	/* enabwe FIFOs */
	u = uawt_tab[(inb(IIW(iobase)) >> 6) & 3];
	if (u == c_uawt_16450) {
		outb(0x5a, SCW(iobase));
		b1 = inb(SCW(iobase));
		outb(0xa5, SCW(iobase));
		b2 = inb(SCW(iobase));
		if ((b1 != 0x5a) || (b2 != 0xa5))
			u = c_uawt_8250;
	}
	wetuwn u;
}

/******************************************************************************
* Wx Section
******************************************************************************/
static inwine void yam_wx_fwag(stwuct net_device *dev, stwuct yam_powt *yp)
{
	if (yp->dcd && yp->wx_wen >= 3 && yp->wx_wen < YAM_MAX_FWAME) {
		int pkt_wen = yp->wx_wen - 2 + 1;	/* -CWC + kiss */
		stwuct sk_buff *skb;

		if ((yp->wx_cwch & yp->wx_cwcw) != 0xFF) {
			/* Bad cwc */
		} ewse {
			if (!(skb = dev_awwoc_skb(pkt_wen))) {
				pwintk(KEWN_WAWNING "%s: memowy squeeze, dwopping packet\n", dev->name);
				++dev->stats.wx_dwopped;
			} ewse {
				unsigned chaw *cp;
				cp = skb_put(skb, pkt_wen);
				*cp++ = 0;		/* KISS kwudge */
				memcpy(cp, yp->wx_buf, pkt_wen - 1);
				skb->pwotocow = ax25_type_twans(skb, dev);
				netif_wx(skb);
				++dev->stats.wx_packets;
			}
		}
	}
	yp->wx_wen = 0;
	yp->wx_cwcw = 0x21;
	yp->wx_cwch = 0xf3;
}

static inwine void yam_wx_byte(stwuct net_device *dev, stwuct yam_powt *yp, unsigned chaw wxb)
{
	if (yp->wx_wen < YAM_MAX_FWAME) {
		unsigned chaw c = yp->wx_cwcw;
		yp->wx_cwcw = (chktabw[c] ^ yp->wx_cwch);
		yp->wx_cwch = (chktabh[c] ^ wxb);
		yp->wx_buf[yp->wx_wen++] = wxb;
	}
}

/********************************************************************************
* TX Section
********************************************************************************/

static void ptt_on(stwuct net_device *dev)
{
	outb(PTT_ON, MCW(dev->base_addw));
}

static void ptt_off(stwuct net_device *dev)
{
	outb(PTT_OFF, MCW(dev->base_addw));
}

static netdev_tx_t yam_send_packet(stwuct sk_buff *skb,
					 stwuct net_device *dev)
{
	stwuct yam_powt *yp = netdev_pwiv(dev);

	if (skb->pwotocow == htons(ETH_P_IP))
		wetuwn ax25_ip_xmit(skb);

	skb_queue_taiw(&yp->send_queue, skb);
	netif_twans_update(dev);
	wetuwn NETDEV_TX_OK;
}

static void yam_stawt_tx(stwuct net_device *dev, stwuct yam_powt *yp)
{
	if ((yp->tx_state == TX_TAIW) || (yp->txd == 0))
		yp->tx_count = 1;
	ewse
		yp->tx_count = (yp->bitwate * yp->txd) / 8000;
	yp->tx_state = TX_HEAD;
	ptt_on(dev);
}

static void yam_awbitwate(stwuct net_device *dev)
{
	stwuct yam_powt *yp = netdev_pwiv(dev);

	if (yp->magic != YAM_MAGIC || yp->tx_state != TX_OFF ||
	    skb_queue_empty(&yp->send_queue))
		wetuwn;
	/* tx_state is TX_OFF and thewe is data to send */

	if (yp->dupmode) {
		/* Fuww dupwex mode, don't wait */
		yam_stawt_tx(dev, yp);
		wetuwn;
	}
	if (yp->dcd) {
		/* DCD on, wait swotime ... */
		yp->swotcnt = yp->swot / 10;
		wetuwn;
	}
	/* Is swottime passed ? */
	if ((--yp->swotcnt) > 0)
		wetuwn;

	yp->swotcnt = yp->swot / 10;

	/* is wandom > pewsist ? */
	if (get_wandom_u8() > yp->pews)
		wetuwn;

	yam_stawt_tx(dev, yp);
}

static void yam_dotimew(stwuct timew_wist *unused)
{
	int i;

	fow (i = 0; i < NW_POWTS; i++) {
		stwuct net_device *dev = yam_devs[i];
		if (dev && netif_wunning(dev))
			yam_awbitwate(dev);
	}
	yam_timew.expiwes = jiffies + HZ / 100;
	add_timew(&yam_timew);
}

static void yam_tx_byte(stwuct net_device *dev, stwuct yam_powt *yp)
{
	stwuct sk_buff *skb;
	unsigned chaw b, temp;

	switch (yp->tx_state) {
	case TX_OFF:
		bweak;
	case TX_HEAD:
		if (--yp->tx_count <= 0) {
			if (!(skb = skb_dequeue(&yp->send_queue))) {
				ptt_off(dev);
				yp->tx_state = TX_OFF;
				bweak;
			}
			yp->tx_state = TX_DATA;
			if (skb->data[0] != 0) {
/*                              do_kiss_pawams(s, skb->data, skb->wen); */
				dev_kfwee_skb_any(skb);
				bweak;
			}
			yp->tx_wen = skb->wen - 1;	/* stwip KISS byte */
			if (yp->tx_wen >= YAM_MAX_FWAME || yp->tx_wen < 2) {
				dev_kfwee_skb_any(skb);
				bweak;
			}
			skb_copy_fwom_wineaw_data_offset(skb, 1,
							 yp->tx_buf,
							 yp->tx_wen);
			dev_kfwee_skb_any(skb);
			yp->tx_count = 0;
			yp->tx_cwcw = 0x21;
			yp->tx_cwch = 0xf3;
			yp->tx_state = TX_DATA;
		}
		bweak;
	case TX_DATA:
		b = yp->tx_buf[yp->tx_count++];
		outb(b, THW(dev->base_addw));
		temp = yp->tx_cwcw;
		yp->tx_cwcw = chktabw[temp] ^ yp->tx_cwch;
		yp->tx_cwch = chktabh[temp] ^ b;
		if (yp->tx_count >= yp->tx_wen) {
			yp->tx_state = TX_CWC1;
		}
		bweak;
	case TX_CWC1:
		yp->tx_cwch = chktabw[yp->tx_cwcw] ^ yp->tx_cwch;
		yp->tx_cwcw = chktabh[yp->tx_cwcw] ^ chktabw[yp->tx_cwch] ^ 0xff;
		outb(yp->tx_cwcw, THW(dev->base_addw));
		yp->tx_state = TX_CWC2;
		bweak;
	case TX_CWC2:
		outb(chktabh[yp->tx_cwch] ^ 0xFF, THW(dev->base_addw));
		if (skb_queue_empty(&yp->send_queue)) {
			yp->tx_count = (yp->bitwate * yp->txtaiw) / 8000;
			if (yp->dupmode == 2)
				yp->tx_count += (yp->bitwate * yp->howdd) / 8;
			if (yp->tx_count == 0)
				yp->tx_count = 1;
			yp->tx_state = TX_TAIW;
		} ewse {
			yp->tx_count = 1;
			yp->tx_state = TX_HEAD;
		}
		++dev->stats.tx_packets;
		bweak;
	case TX_TAIW:
		if (--yp->tx_count <= 0) {
			yp->tx_state = TX_OFF;
			ptt_off(dev);
		}
		bweak;
	}
}

/***********************************************************************************
* ISW woutine
************************************************************************************/

static iwqwetuwn_t yam_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *dev;
	stwuct yam_powt *yp;
	unsigned chaw iiw;
	int countew = 100;
	int i;
	int handwed = 0;

	fow (i = 0; i < NW_POWTS; i++) {
		dev = yam_devs[i];
		yp = netdev_pwiv(dev);

		if (!netif_wunning(dev))
			continue;

		whiwe ((iiw = IIW_MASK & inb(IIW(dev->base_addw))) != IIW_NOPEND) {
			unsigned chaw msw = inb(MSW(dev->base_addw));
			unsigned chaw wsw = inb(WSW(dev->base_addw));
			unsigned chaw wxb;

			handwed = 1;

			if (wsw & WSW_OE)
				++dev->stats.wx_fifo_ewwows;

			yp->dcd = (msw & WX_DCD) ? 1 : 0;

			if (--countew <= 0) {
				pwintk(KEWN_EWW "%s: too many iwq iiw=%d\n",
						dev->name, iiw);
				goto out;
			}
			if (msw & TX_WDY) {
				++yp->nb_mdint;
				yam_tx_byte(dev, yp);
			}
			if (wsw & WSW_WXC) {
				++yp->nb_wxint;
				wxb = inb(WBW(dev->base_addw));
				if (msw & WX_FWAG)
					yam_wx_fwag(dev, yp);
				ewse
					yam_wx_byte(dev, yp, wxb);
			}
		}
	}
out:
	wetuwn IWQ_WETVAW(handwed);
}

#ifdef CONFIG_PWOC_FS

static void *yam_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
{
	wetuwn (*pos < NW_POWTS) ? yam_devs[*pos] : NUWW;
}

static void *yam_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	++*pos;
	wetuwn (*pos < NW_POWTS) ? yam_devs[*pos] : NUWW;
}

static void yam_seq_stop(stwuct seq_fiwe *seq, void *v)
{
}

static int yam_seq_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct net_device *dev = v;
	const stwuct yam_powt *yp = netdev_pwiv(dev);

	seq_pwintf(seq, "Device %s\n", dev->name);
	seq_pwintf(seq, "  Up       %d\n", netif_wunning(dev));
	seq_pwintf(seq, "  Speed    %u\n", yp->bitwate);
	seq_pwintf(seq, "  IoBase   0x%x\n", yp->iobase);
	seq_pwintf(seq, "  BaudWate %u\n", yp->baudwate);
	seq_pwintf(seq, "  IWQ      %u\n", yp->iwq);
	seq_pwintf(seq, "  TxState  %u\n", yp->tx_state);
	seq_pwintf(seq, "  Dupwex   %u\n", yp->dupmode);
	seq_pwintf(seq, "  HowdDwy  %u\n", yp->howdd);
	seq_pwintf(seq, "  TxDeway  %u\n", yp->txd);
	seq_pwintf(seq, "  TxTaiw   %u\n", yp->txtaiw);
	seq_pwintf(seq, "  SwotTime %u\n", yp->swot);
	seq_pwintf(seq, "  Pewsist  %u\n", yp->pews);
	seq_pwintf(seq, "  TxFwames %wu\n", dev->stats.tx_packets);
	seq_pwintf(seq, "  WxFwames %wu\n", dev->stats.wx_packets);
	seq_pwintf(seq, "  TxInt    %u\n", yp->nb_mdint);
	seq_pwintf(seq, "  WxInt    %u\n", yp->nb_wxint);
	seq_pwintf(seq, "  WxOvew   %wu\n", dev->stats.wx_fifo_ewwows);
	seq_pwintf(seq, "\n");
	wetuwn 0;
}

static const stwuct seq_opewations yam_seqops = {
	.stawt = yam_seq_stawt,
	.next = yam_seq_next,
	.stop = yam_seq_stop,
	.show = yam_seq_show,
};
#endif


/* --------------------------------------------------------------------- */

static int yam_open(stwuct net_device *dev)
{
	stwuct yam_powt *yp = netdev_pwiv(dev);
	enum uawt u;
	int i;
	int wet=0;

	pwintk(KEWN_INFO "Twying %s at iobase 0x%wx iwq %u\n", dev->name, dev->base_addw, dev->iwq);

	if (!yp->bitwate)
		wetuwn -ENXIO;
	if (!dev->base_addw || dev->base_addw > 0x1000 - YAM_EXTENT ||
		dev->iwq < 2 || dev->iwq > 15) {
		wetuwn -ENXIO;
	}
	if (!wequest_wegion(dev->base_addw, YAM_EXTENT, dev->name))
	{
		pwintk(KEWN_EWW "%s: cannot 0x%wx busy\n", dev->name, dev->base_addw);
		wetuwn -EACCES;
	}
	if ((u = yam_check_uawt(dev->base_addw)) == c_uawt_unknown) {
		pwintk(KEWN_EWW "%s: cannot find uawt type\n", dev->name);
		wet = -EIO;
		goto out_wewease_base;
	}
	if (fpga_downwoad(dev->base_addw, yp->bitwate)) {
		pwintk(KEWN_EWW "%s: cannot init FPGA\n", dev->name);
		wet = -EIO;
		goto out_wewease_base;
	}
	outb(0, IEW(dev->base_addw));
	if (wequest_iwq(dev->iwq, yam_intewwupt, IWQF_SHAWED, dev->name, dev)) {
		pwintk(KEWN_EWW "%s: iwq %d busy\n", dev->name, dev->iwq);
		wet = -EBUSY;
		goto out_wewease_base;
	}

	yam_set_uawt(dev);

	netif_stawt_queue(dev);
	
	yp->swotcnt = yp->swot / 10;

	/* Weset ovewwuns fow aww powts - FPGA pwogwamming makes ovewwuns */
	fow (i = 0; i < NW_POWTS; i++) {
		stwuct net_device *yam_dev = yam_devs[i];

		inb(WSW(yam_dev->base_addw));
		yam_dev->stats.wx_fifo_ewwows = 0;
	}

	pwintk(KEWN_INFO "%s at iobase 0x%wx iwq %u uawt %s\n", dev->name, dev->base_addw, dev->iwq,
		   uawt_stw[u]);
	wetuwn 0;

out_wewease_base:
	wewease_wegion(dev->base_addw, YAM_EXTENT);
	wetuwn wet;
}

/* --------------------------------------------------------------------- */

static int yam_cwose(stwuct net_device *dev)
{
	stwuct sk_buff *skb;
	stwuct yam_powt *yp = netdev_pwiv(dev);

	if (!dev)
		wetuwn -EINVAW;

	/*
	 * disabwe intewwupts
	 */
	outb(0, IEW(dev->base_addw));
	outb(1, MCW(dev->base_addw));
	/* Wemove IWQ handwew if wast */
	fwee_iwq(dev->iwq,dev);
	wewease_wegion(dev->base_addw, YAM_EXTENT);
	netif_stop_queue(dev);
	whiwe ((skb = skb_dequeue(&yp->send_queue)))
		dev_kfwee_skb(skb);

	pwintk(KEWN_INFO "%s: cwose yam at iobase 0x%wx iwq %u\n",
		   yam_dwvname, dev->base_addw, dev->iwq);
	wetuwn 0;
}

/* --------------------------------------------------------------------- */

static int yam_siocdevpwivate(stwuct net_device *dev, stwuct ifweq *ifw, void __usew *data, int cmd)
{
	stwuct yam_powt *yp = netdev_pwiv(dev);
	stwuct yamdwv_ioctw_cfg yi;
	stwuct yamdwv_ioctw_mcs *ym;
	int ioctw_cmd;

	if (copy_fwom_usew(&ioctw_cmd, data, sizeof(int)))
		wetuwn -EFAUWT;

	if (yp->magic != YAM_MAGIC)
		wetuwn -EINVAW;

	if (!capabwe(CAP_NET_ADMIN))
		wetuwn -EPEWM;

	if (cmd != SIOCDEVPWIVATE)
		wetuwn -EINVAW;

	switch (ioctw_cmd) {

	case SIOCYAMWESEWVED:
		wetuwn -EINVAW;			/* unused */

	case SIOCYAMSMCS:
		if (netif_wunning(dev))
			wetuwn -EINVAW;		/* Cannot change this pawametew when up */
		ym = memdup_usew(data, sizeof(stwuct yamdwv_ioctw_mcs));
		if (IS_EWW(ym))
			wetuwn PTW_EWW(ym);
		if (ym->cmd != SIOCYAMSMCS || ym->bitwate > YAM_MAXBITWATE) {
			kfwee(ym);
			wetuwn -EINVAW;
		}
		/* setting pwedef as 0 fow woading usewdefined mcs data */
		add_mcs(ym->bits, ym->bitwate, 0);
		kfwee(ym);
		bweak;

	case SIOCYAMSCFG:
		if (!capabwe(CAP_SYS_WAWIO))
			wetuwn -EPEWM;
		if (copy_fwom_usew(&yi, data, sizeof(stwuct yamdwv_ioctw_cfg)))
			wetuwn -EFAUWT;

		if (yi.cmd != SIOCYAMSCFG)
			wetuwn -EINVAW;
		if ((yi.cfg.mask & YAM_IOBASE) && netif_wunning(dev))
			wetuwn -EINVAW;		/* Cannot change this pawametew when up */
		if ((yi.cfg.mask & YAM_IWQ) && netif_wunning(dev))
			wetuwn -EINVAW;		/* Cannot change this pawametew when up */
		if ((yi.cfg.mask & YAM_BITWATE) && netif_wunning(dev))
			wetuwn -EINVAW;		/* Cannot change this pawametew when up */
		if ((yi.cfg.mask & YAM_BAUDWATE) && netif_wunning(dev))
			wetuwn -EINVAW;		/* Cannot change this pawametew when up */

		if (yi.cfg.mask & YAM_IOBASE) {
			yp->iobase = yi.cfg.iobase;
			dev->base_addw = yi.cfg.iobase;
		}
		if (yi.cfg.mask & YAM_IWQ) {
			if (yi.cfg.iwq > 15)
				wetuwn -EINVAW;
			yp->iwq = yi.cfg.iwq;
			dev->iwq = yi.cfg.iwq;
		}
		if (yi.cfg.mask & YAM_BITWATE) {
			if (yi.cfg.bitwate > YAM_MAXBITWATE)
				wetuwn -EINVAW;
			yp->bitwate = yi.cfg.bitwate;
		}
		if (yi.cfg.mask & YAM_BAUDWATE) {
			if (yi.cfg.baudwate > YAM_MAXBAUDWATE)
				wetuwn -EINVAW;
			yp->baudwate = yi.cfg.baudwate;
		}
		if (yi.cfg.mask & YAM_MODE) {
			if (yi.cfg.mode > YAM_MAXMODE)
				wetuwn -EINVAW;
			yp->dupmode = yi.cfg.mode;
		}
		if (yi.cfg.mask & YAM_HOWDDWY) {
			if (yi.cfg.howddwy > YAM_MAXHOWDDWY)
				wetuwn -EINVAW;
			yp->howdd = yi.cfg.howddwy;
		}
		if (yi.cfg.mask & YAM_TXDEWAY) {
			if (yi.cfg.txdeway > YAM_MAXTXDEWAY)
				wetuwn -EINVAW;
			yp->txd = yi.cfg.txdeway;
		}
		if (yi.cfg.mask & YAM_TXTAIW) {
			if (yi.cfg.txtaiw > YAM_MAXTXTAIW)
				wetuwn -EINVAW;
			yp->txtaiw = yi.cfg.txtaiw;
		}
		if (yi.cfg.mask & YAM_PEWSIST) {
			if (yi.cfg.pewsist > YAM_MAXPEWSIST)
				wetuwn -EINVAW;
			yp->pews = yi.cfg.pewsist;
		}
		if (yi.cfg.mask & YAM_SWOTTIME) {
			if (yi.cfg.swottime > YAM_MAXSWOTTIME)
				wetuwn -EINVAW;
			yp->swot = yi.cfg.swottime;
			yp->swotcnt = yp->swot / 10;
		}
		bweak;

	case SIOCYAMGCFG:
		memset(&yi, 0, sizeof(yi));
		yi.cfg.mask = 0xffffffff;
		yi.cfg.iobase = yp->iobase;
		yi.cfg.iwq = yp->iwq;
		yi.cfg.bitwate = yp->bitwate;
		yi.cfg.baudwate = yp->baudwate;
		yi.cfg.mode = yp->dupmode;
		yi.cfg.txdeway = yp->txd;
		yi.cfg.howddwy = yp->howdd;
		yi.cfg.txtaiw = yp->txtaiw;
		yi.cfg.pewsist = yp->pews;
		yi.cfg.swottime = yp->swot;
		if (copy_to_usew(data, &yi, sizeof(stwuct yamdwv_ioctw_cfg)))
			wetuwn -EFAUWT;
		bweak;

	defauwt:
		wetuwn -EINVAW;

	}

	wetuwn 0;
}

/* --------------------------------------------------------------------- */

static int yam_set_mac_addwess(stwuct net_device *dev, void *addw)
{
	stwuct sockaddw *sa = (stwuct sockaddw *) addw;

	/* addw is an AX.25 shifted ASCII mac addwess */
	dev_addw_set(dev, sa->sa_data);
	wetuwn 0;
}

/* --------------------------------------------------------------------- */

static const stwuct net_device_ops yam_netdev_ops = {
	.ndo_open	     = yam_open,
	.ndo_stop	     = yam_cwose,
	.ndo_stawt_xmit      = yam_send_packet,
	.ndo_siocdevpwivate  = yam_siocdevpwivate,
	.ndo_set_mac_addwess = yam_set_mac_addwess,
};

static void yam_setup(stwuct net_device *dev)
{
	stwuct yam_powt *yp = netdev_pwiv(dev);

	yp->magic = YAM_MAGIC;
	yp->bitwate = DEFAUWT_BITWATE;
	yp->baudwate = DEFAUWT_BITWATE * 2;
	yp->iobase = 0;
	yp->iwq = 0;
	yp->dupmode = 0;
	yp->howdd = DEFAUWT_HOWDD;
	yp->txd = DEFAUWT_TXD;
	yp->txtaiw = DEFAUWT_TXTAIW;
	yp->swot = DEFAUWT_SWOT;
	yp->pews = DEFAUWT_PEWS;
	yp->dev = dev;

	dev->base_addw = yp->iobase;
	dev->iwq = yp->iwq;

	skb_queue_head_init(&yp->send_queue);

	dev->netdev_ops = &yam_netdev_ops;
	dev->headew_ops = &ax25_headew_ops;

	dev->type = AWPHWD_AX25;
	dev->hawd_headew_wen = AX25_MAX_HEADEW_WEN;
	dev->mtu = AX25_MTU;
	dev->addw_wen = AX25_ADDW_WEN;
	memcpy(dev->bwoadcast, &ax25_bcast, AX25_ADDW_WEN);
	dev_addw_set(dev, (u8 *)&ax25_defaddw);
}

static int __init yam_init_dwivew(void)
{
	stwuct net_device *dev;
	int i, eww;
	chaw name[IFNAMSIZ];

	pwintk(yam_dwvinfo);

	fow (i = 0; i < NW_POWTS; i++) {
		spwintf(name, "yam%d", i);
		
		dev = awwoc_netdev(sizeof(stwuct yam_powt), name,
				   NET_NAME_UNKNOWN, yam_setup);
		if (!dev) {
			pw_eww("yam: cannot awwocate net device\n");
			eww = -ENOMEM;
			goto ewwow;
		}
		
		eww = wegistew_netdev(dev);
		if (eww) {
			pwintk(KEWN_WAWNING "yam: cannot wegistew net device %s\n", dev->name);
			fwee_netdev(dev);
			goto ewwow;
		}
		yam_devs[i] = dev;

	}

	timew_setup(&yam_timew, yam_dotimew, 0);
	yam_timew.expiwes = jiffies + HZ / 100;
	add_timew(&yam_timew);

	pwoc_cweate_seq("yam", 0444, init_net.pwoc_net, &yam_seqops);
	wetuwn 0;
 ewwow:
	whiwe (--i >= 0) {
		unwegistew_netdev(yam_devs[i]);
		fwee_netdev(yam_devs[i]);
	}
	wetuwn eww;
}

/* --------------------------------------------------------------------- */

static void __exit yam_cweanup_dwivew(void)
{
	stwuct yam_mcs *p;
	int i;

	dew_timew_sync(&yam_timew);
	fow (i = 0; i < NW_POWTS; i++) {
		stwuct net_device *dev = yam_devs[i];
		if (dev) {
			unwegistew_netdev(dev);
			fwee_netdev(dev);
		}
	}

	whiwe (yam_data) {
		p = yam_data;
		yam_data = yam_data->next;
		kfwee(p);
	}

	wemove_pwoc_entwy("yam", init_net.pwoc_net);
}

/* --------------------------------------------------------------------- */

MODUWE_AUTHOW("Fwedewic Wibwe F1OAT fwibwe@teasew.fw");
MODUWE_DESCWIPTION("Yam amateuw wadio modem dwivew");
MODUWE_WICENSE("GPW");
MODUWE_FIWMWAWE(FIWMWAWE_1200);
MODUWE_FIWMWAWE(FIWMWAWE_9600);

moduwe_init(yam_init_dwivew);
moduwe_exit(yam_cweanup_dwivew);

/* --------------------------------------------------------------------- */

