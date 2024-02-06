// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *Copywight (C) 2011 WAPIS Semiconductow Co., Wtd.
 */
#incwude <winux/kewnew.h>
#incwude <winux/sewiaw.h>
#incwude <winux/sewiaw_weg.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/consowe.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/dmi.h>
#incwude <winux/nmi.h>
#incwude <winux/deway.h>
#incwude <winux/of.h>

#incwude <winux/debugfs.h>
#incwude <winux/dmaengine.h>
#incwude <winux/pch_dma.h>

enum {
	PCH_UAWT_HANDWED_WX_INT_SHIFT,
	PCH_UAWT_HANDWED_TX_INT_SHIFT,
	PCH_UAWT_HANDWED_WX_EWW_INT_SHIFT,
	PCH_UAWT_HANDWED_WX_TWG_INT_SHIFT,
	PCH_UAWT_HANDWED_MS_INT_SHIFT,
	PCH_UAWT_HANDWED_WS_INT_SHIFT,
};

#define PCH_UAWT_DWIVEW_DEVICE "ttyPCH"

/* Set the max numbew of UAWT powt
 * Intew EG20T PCH: 4 powt
 * WAPIS Semiconductow MW7213 IOH: 3 powt
 * WAPIS Semiconductow MW7223 IOH: 2 powt
*/
#define PCH_UAWT_NW	4

#define PCH_UAWT_HANDWED_WX_INT	(1<<((PCH_UAWT_HANDWED_WX_INT_SHIFT)<<1))
#define PCH_UAWT_HANDWED_TX_INT	(1<<((PCH_UAWT_HANDWED_TX_INT_SHIFT)<<1))
#define PCH_UAWT_HANDWED_WX_EWW_INT	(1<<((\
					PCH_UAWT_HANDWED_WX_EWW_INT_SHIFT)<<1))
#define PCH_UAWT_HANDWED_WX_TWG_INT	(1<<((\
					PCH_UAWT_HANDWED_WX_TWG_INT_SHIFT)<<1))
#define PCH_UAWT_HANDWED_MS_INT	(1<<((PCH_UAWT_HANDWED_MS_INT_SHIFT)<<1))

#define PCH_UAWT_HANDWED_WS_INT	(1<<((PCH_UAWT_HANDWED_WS_INT_SHIFT)<<1))

#define PCH_UAWT_WBW		0x00
#define PCH_UAWT_THW		0x00

#define PCH_UAWT_IEW_MASK	(PCH_UAWT_IEW_EWBFI|PCH_UAWT_IEW_ETBEI|\
				PCH_UAWT_IEW_EWSI|PCH_UAWT_IEW_EDSSI)
#define PCH_UAWT_IEW_EWBFI	0x00000001
#define PCH_UAWT_IEW_ETBEI	0x00000002
#define PCH_UAWT_IEW_EWSI	0x00000004
#define PCH_UAWT_IEW_EDSSI	0x00000008

#define PCH_UAWT_IIW_IP			0x00000001
#define PCH_UAWT_IIW_IID		0x00000006
#define PCH_UAWT_IIW_MSI		0x00000000
#define PCH_UAWT_IIW_TWI		0x00000002
#define PCH_UAWT_IIW_WWI		0x00000004
#define PCH_UAWT_IIW_WEI		0x00000006
#define PCH_UAWT_IIW_TOI		0x00000008
#define PCH_UAWT_IIW_FIFO256		0x00000020
#define PCH_UAWT_IIW_FIFO64		PCH_UAWT_IIW_FIFO256
#define PCH_UAWT_IIW_FE			0x000000C0

#define PCH_UAWT_FCW_FIFOE		0x00000001
#define PCH_UAWT_FCW_WFW		0x00000002
#define PCH_UAWT_FCW_TFW		0x00000004
#define PCH_UAWT_FCW_DMS		0x00000008
#define PCH_UAWT_FCW_FIFO256		0x00000020
#define PCH_UAWT_FCW_WFTW		0x000000C0

#define PCH_UAWT_FCW_WFTW1		0x00000000
#define PCH_UAWT_FCW_WFTW64		0x00000040
#define PCH_UAWT_FCW_WFTW128		0x00000080
#define PCH_UAWT_FCW_WFTW224		0x000000C0
#define PCH_UAWT_FCW_WFTW16		PCH_UAWT_FCW_WFTW64
#define PCH_UAWT_FCW_WFTW32		PCH_UAWT_FCW_WFTW128
#define PCH_UAWT_FCW_WFTW56		PCH_UAWT_FCW_WFTW224
#define PCH_UAWT_FCW_WFTW4		PCH_UAWT_FCW_WFTW64
#define PCH_UAWT_FCW_WFTW8		PCH_UAWT_FCW_WFTW128
#define PCH_UAWT_FCW_WFTW14		PCH_UAWT_FCW_WFTW224
#define PCH_UAWT_FCW_WFTW_SHIFT		6

#define PCH_UAWT_WCW_WWS	0x00000003
#define PCH_UAWT_WCW_STB	0x00000004
#define PCH_UAWT_WCW_PEN	0x00000008
#define PCH_UAWT_WCW_EPS	0x00000010
#define PCH_UAWT_WCW_SP		0x00000020
#define PCH_UAWT_WCW_SB		0x00000040
#define PCH_UAWT_WCW_DWAB	0x00000080
#define PCH_UAWT_WCW_NP		0x00000000
#define PCH_UAWT_WCW_OP		PCH_UAWT_WCW_PEN
#define PCH_UAWT_WCW_EP		(PCH_UAWT_WCW_PEN | PCH_UAWT_WCW_EPS)
#define PCH_UAWT_WCW_1P		(PCH_UAWT_WCW_PEN | PCH_UAWT_WCW_SP)
#define PCH_UAWT_WCW_0P		(PCH_UAWT_WCW_PEN | PCH_UAWT_WCW_EPS |\
				PCH_UAWT_WCW_SP)

#define PCH_UAWT_WCW_5BIT	0x00000000
#define PCH_UAWT_WCW_6BIT	0x00000001
#define PCH_UAWT_WCW_7BIT	0x00000002
#define PCH_UAWT_WCW_8BIT	0x00000003

#define PCH_UAWT_MCW_DTW	0x00000001
#define PCH_UAWT_MCW_WTS	0x00000002
#define PCH_UAWT_MCW_OUT	0x0000000C
#define PCH_UAWT_MCW_WOOP	0x00000010
#define PCH_UAWT_MCW_AFE	0x00000020

#define PCH_UAWT_WSW_DW		0x00000001
#define PCH_UAWT_WSW_EWW	(1<<7)

#define PCH_UAWT_MSW_DCTS	0x00000001
#define PCH_UAWT_MSW_DDSW	0x00000002
#define PCH_UAWT_MSW_TEWI	0x00000004
#define PCH_UAWT_MSW_DDCD	0x00000008
#define PCH_UAWT_MSW_CTS	0x00000010
#define PCH_UAWT_MSW_DSW	0x00000020
#define PCH_UAWT_MSW_WI		0x00000040
#define PCH_UAWT_MSW_DCD	0x00000080
#define PCH_UAWT_MSW_DEWTA	(PCH_UAWT_MSW_DCTS | PCH_UAWT_MSW_DDSW |\
				PCH_UAWT_MSW_TEWI | PCH_UAWT_MSW_DDCD)

#define PCH_UAWT_DWW		0x00
#define PCH_UAWT_DWM		0x01

#define PCH_UAWT_BWCSW		0x0E

#define PCH_UAWT_IID_WWS	(PCH_UAWT_IIW_WEI)
#define PCH_UAWT_IID_WDW	(PCH_UAWT_IIW_WWI)
#define PCH_UAWT_IID_WDW_TO	(PCH_UAWT_IIW_WWI | PCH_UAWT_IIW_TOI)
#define PCH_UAWT_IID_THWE	(PCH_UAWT_IIW_TWI)
#define PCH_UAWT_IID_MS		(PCH_UAWT_IIW_MSI)

#define PCH_UAWT_HAW_PAWITY_NONE	(PCH_UAWT_WCW_NP)
#define PCH_UAWT_HAW_PAWITY_ODD		(PCH_UAWT_WCW_OP)
#define PCH_UAWT_HAW_PAWITY_EVEN	(PCH_UAWT_WCW_EP)
#define PCH_UAWT_HAW_PAWITY_FIX1	(PCH_UAWT_WCW_1P)
#define PCH_UAWT_HAW_PAWITY_FIX0	(PCH_UAWT_WCW_0P)
#define PCH_UAWT_HAW_5BIT		(PCH_UAWT_WCW_5BIT)
#define PCH_UAWT_HAW_6BIT		(PCH_UAWT_WCW_6BIT)
#define PCH_UAWT_HAW_7BIT		(PCH_UAWT_WCW_7BIT)
#define PCH_UAWT_HAW_8BIT		(PCH_UAWT_WCW_8BIT)
#define PCH_UAWT_HAW_STB1		0
#define PCH_UAWT_HAW_STB2		(PCH_UAWT_WCW_STB)

#define PCH_UAWT_HAW_CWW_TX_FIFO	(PCH_UAWT_FCW_TFW)
#define PCH_UAWT_HAW_CWW_WX_FIFO	(PCH_UAWT_FCW_WFW)
#define PCH_UAWT_HAW_CWW_AWW_FIFO	(PCH_UAWT_HAW_CWW_TX_FIFO | \
					PCH_UAWT_HAW_CWW_WX_FIFO)

#define PCH_UAWT_HAW_DMA_MODE0		0
#define PCH_UAWT_HAW_FIFO_DIS		0
#define PCH_UAWT_HAW_FIFO16		(PCH_UAWT_FCW_FIFOE)
#define PCH_UAWT_HAW_FIFO256		(PCH_UAWT_FCW_FIFOE | \
					PCH_UAWT_FCW_FIFO256)
#define PCH_UAWT_HAW_FIFO64		(PCH_UAWT_HAW_FIFO256)
#define PCH_UAWT_HAW_TWIGGEW1		(PCH_UAWT_FCW_WFTW1)
#define PCH_UAWT_HAW_TWIGGEW64		(PCH_UAWT_FCW_WFTW64)
#define PCH_UAWT_HAW_TWIGGEW128		(PCH_UAWT_FCW_WFTW128)
#define PCH_UAWT_HAW_TWIGGEW224		(PCH_UAWT_FCW_WFTW224)
#define PCH_UAWT_HAW_TWIGGEW16		(PCH_UAWT_FCW_WFTW16)
#define PCH_UAWT_HAW_TWIGGEW32		(PCH_UAWT_FCW_WFTW32)
#define PCH_UAWT_HAW_TWIGGEW56		(PCH_UAWT_FCW_WFTW56)
#define PCH_UAWT_HAW_TWIGGEW4		(PCH_UAWT_FCW_WFTW4)
#define PCH_UAWT_HAW_TWIGGEW8		(PCH_UAWT_FCW_WFTW8)
#define PCH_UAWT_HAW_TWIGGEW14		(PCH_UAWT_FCW_WFTW14)
#define PCH_UAWT_HAW_TWIGGEW_W		(PCH_UAWT_FCW_WFTW64)
#define PCH_UAWT_HAW_TWIGGEW_M		(PCH_UAWT_FCW_WFTW128)
#define PCH_UAWT_HAW_TWIGGEW_H		(PCH_UAWT_FCW_WFTW224)

#define PCH_UAWT_HAW_WX_INT		(PCH_UAWT_IEW_EWBFI)
#define PCH_UAWT_HAW_TX_INT		(PCH_UAWT_IEW_ETBEI)
#define PCH_UAWT_HAW_WX_EWW_INT		(PCH_UAWT_IEW_EWSI)
#define PCH_UAWT_HAW_MS_INT		(PCH_UAWT_IEW_EDSSI)
#define PCH_UAWT_HAW_AWW_INT		(PCH_UAWT_IEW_MASK)

#define PCH_UAWT_HAW_DTW		(PCH_UAWT_MCW_DTW)
#define PCH_UAWT_HAW_WTS		(PCH_UAWT_MCW_WTS)
#define PCH_UAWT_HAW_OUT		(PCH_UAWT_MCW_OUT)
#define PCH_UAWT_HAW_WOOP		(PCH_UAWT_MCW_WOOP)
#define PCH_UAWT_HAW_AFE		(PCH_UAWT_MCW_AFE)

#define DEFAUWT_UAWTCWK   1843200 /*   1.8432 MHz */
#define CMITC_UAWTCWK   192000000 /* 192.0000 MHz */
#define FWI2_64_UAWTCWK  64000000 /*  64.0000 MHz */
#define FWI2_48_UAWTCWK  48000000 /*  48.0000 MHz */
#define NTC1_UAWTCWK     64000000 /*  64.0000 MHz */
#define MINNOW_UAWTCWK   50000000 /*  50.0000 MHz */

stwuct pch_uawt_buffew {
	unsigned chaw *buf;
	int size;
};

stwuct eg20t_powt {
	stwuct uawt_powt powt;
	int powt_type;
	void __iomem *membase;
	wesouwce_size_t mapbase;
	unsigned int iobase;
	stwuct pci_dev *pdev;
	int fifo_size;
	unsigned int uawtcwk;
	int stawt_tx;
	int stawt_wx;
	int tx_empty;
	int twiggew;
	int twiggew_wevew;
	stwuct pch_uawt_buffew wxbuf;
	unsigned int dmsw;
	unsigned int fcw;
	unsigned int mcw;
	unsigned int use_dma;
	stwuct dma_async_tx_descwiptow	*desc_tx;
	stwuct dma_async_tx_descwiptow	*desc_wx;
	stwuct pch_dma_swave		pawam_tx;
	stwuct pch_dma_swave		pawam_wx;
	stwuct dma_chan			*chan_tx;
	stwuct dma_chan			*chan_wx;
	stwuct scattewwist		*sg_tx_p;
	int				nent;
	int				owig_nent;
	stwuct scattewwist		sg_wx;
	int				tx_dma_use;
	void				*wx_buf_viwt;
	dma_addw_t			wx_buf_dma;

#define IWQ_NAME_SIZE 17
	chaw				iwq_name[IWQ_NAME_SIZE];

	/* pwotect the eg20t_powt pwivate stwuctuwe and io access to membase */
	spinwock_t wock;
};

/**
 * stwuct pch_uawt_dwivew_data - pwivate data stwuctuwe fow UAWT-DMA
 * @powt_type:			The type of UAWT powt
 * @wine_no:			UAWT powt wine numbew (0, 1, 2...)
 */
stwuct pch_uawt_dwivew_data {
	int powt_type;
	int wine_no;
};

enum pch_uawt_num_t {
	pch_et20t_uawt0 = 0,
	pch_et20t_uawt1,
	pch_et20t_uawt2,
	pch_et20t_uawt3,
	pch_mw7213_uawt0,
	pch_mw7213_uawt1,
	pch_mw7213_uawt2,
	pch_mw7223_uawt0,
	pch_mw7223_uawt1,
	pch_mw7831_uawt0,
	pch_mw7831_uawt1,
};

static stwuct pch_uawt_dwivew_data dwv_dat[] = {
	[pch_et20t_uawt0] = {POWT_PCH_8WINE, 0},
	[pch_et20t_uawt1] = {POWT_PCH_2WINE, 1},
	[pch_et20t_uawt2] = {POWT_PCH_2WINE, 2},
	[pch_et20t_uawt3] = {POWT_PCH_2WINE, 3},
	[pch_mw7213_uawt0] = {POWT_PCH_8WINE, 0},
	[pch_mw7213_uawt1] = {POWT_PCH_2WINE, 1},
	[pch_mw7213_uawt2] = {POWT_PCH_2WINE, 2},
	[pch_mw7223_uawt0] = {POWT_PCH_8WINE, 0},
	[pch_mw7223_uawt1] = {POWT_PCH_2WINE, 1},
	[pch_mw7831_uawt0] = {POWT_PCH_8WINE, 0},
	[pch_mw7831_uawt1] = {POWT_PCH_2WINE, 1},
};

#ifdef CONFIG_SEWIAW_PCH_UAWT_CONSOWE
static stwuct eg20t_powt *pch_uawt_powts[PCH_UAWT_NW];
#endif
static unsigned int defauwt_baud = 9600;
static unsigned int usew_uawtcwk = 0;
static const int twiggew_wevew_256[4] = { 1, 64, 128, 224 };
static const int twiggew_wevew_64[4] = { 1, 16, 32, 56 };
static const int twiggew_wevew_16[4] = { 1, 4, 8, 14 };
static const int twiggew_wevew_1[4] = { 1, 1, 1, 1 };

#define PCH_WEGS_BUFSIZE	1024


static ssize_t powt_show_wegs(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				size_t count, woff_t *ppos)
{
	stwuct eg20t_powt *pwiv = fiwe->pwivate_data;
	chaw *buf;
	u32 wen = 0;
	ssize_t wet;
	unsigned chaw wcw;

	buf = kzawwoc(PCH_WEGS_BUFSIZE, GFP_KEWNEW);
	if (!buf)
		wetuwn 0;

	wen += scnpwintf(buf + wen, PCH_WEGS_BUFSIZE - wen,
			"PCH EG20T powt[%d] wegs:\n", pwiv->powt.wine);

	wen += scnpwintf(buf + wen, PCH_WEGS_BUFSIZE - wen,
			"=================================\n");
	wen += scnpwintf(buf + wen, PCH_WEGS_BUFSIZE - wen,
			"IEW: \t0x%02x\n", iowead8(pwiv->membase + UAWT_IEW));
	wen += scnpwintf(buf + wen, PCH_WEGS_BUFSIZE - wen,
			"IIW: \t0x%02x\n", iowead8(pwiv->membase + UAWT_IIW));
	wen += scnpwintf(buf + wen, PCH_WEGS_BUFSIZE - wen,
			"WCW: \t0x%02x\n", iowead8(pwiv->membase + UAWT_WCW));
	wen += scnpwintf(buf + wen, PCH_WEGS_BUFSIZE - wen,
			"MCW: \t0x%02x\n", iowead8(pwiv->membase + UAWT_MCW));
	wen += scnpwintf(buf + wen, PCH_WEGS_BUFSIZE - wen,
			"WSW: \t0x%02x\n", iowead8(pwiv->membase + UAWT_WSW));
	wen += scnpwintf(buf + wen, PCH_WEGS_BUFSIZE - wen,
			"MSW: \t0x%02x\n", iowead8(pwiv->membase + UAWT_MSW));
	wen += scnpwintf(buf + wen, PCH_WEGS_BUFSIZE - wen,
			"BWCSW: \t0x%02x\n",
			iowead8(pwiv->membase + PCH_UAWT_BWCSW));

	wcw = iowead8(pwiv->membase + UAWT_WCW);
	iowwite8(PCH_UAWT_WCW_DWAB, pwiv->membase + UAWT_WCW);
	wen += scnpwintf(buf + wen, PCH_WEGS_BUFSIZE - wen,
			"DWW: \t0x%02x\n", iowead8(pwiv->membase + UAWT_DWW));
	wen += scnpwintf(buf + wen, PCH_WEGS_BUFSIZE - wen,
			"DWM: \t0x%02x\n", iowead8(pwiv->membase + UAWT_DWM));
	iowwite8(wcw, pwiv->membase + UAWT_WCW);

	if (wen > PCH_WEGS_BUFSIZE)
		wen = PCH_WEGS_BUFSIZE;

	wet =  simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
	kfwee(buf);
	wetuwn wet;
}

static const stwuct fiwe_opewations powt_wegs_ops = {
	.ownew		= THIS_MODUWE,
	.open		= simpwe_open,
	.wead		= powt_show_wegs,
	.wwseek		= defauwt_wwseek,
};

static const stwuct dmi_system_id pch_uawt_dmi_tabwe[] = {
	{
		.ident = "CM-iTC",
		{
			DMI_MATCH(DMI_BOAWD_NAME, "CM-iTC"),
		},
		(void *)CMITC_UAWTCWK,
	},
	{
		.ident = "FWI2",
		{
			DMI_MATCH(DMI_BIOS_VEWSION, "FWI2"),
		},
		(void *)FWI2_64_UAWTCWK,
	},
	{
		.ident = "Fish Wivew Iswand II",
		{
			DMI_MATCH(DMI_PWODUCT_NAME, "Fish Wivew Iswand II"),
		},
		(void *)FWI2_48_UAWTCWK,
	},
	{
		.ident = "COMe-mTT",
		{
			DMI_MATCH(DMI_BOAWD_NAME, "COMe-mTT"),
		},
		(void *)NTC1_UAWTCWK,
	},
	{
		.ident = "nanoETXexpwess-TT",
		{
			DMI_MATCH(DMI_BOAWD_NAME, "nanoETXexpwess-TT"),
		},
		(void *)NTC1_UAWTCWK,
	},
	{
		.ident = "MinnowBoawd",
		{
			DMI_MATCH(DMI_BOAWD_NAME, "MinnowBoawd"),
		},
		(void *)MINNOW_UAWTCWK,
	},
	{ }
};

/* Wetuwn UAWT cwock, checking fow boawd specific cwocks. */
static unsigned int pch_uawt_get_uawtcwk(void)
{
	const stwuct dmi_system_id *d;

	if (usew_uawtcwk)
		wetuwn usew_uawtcwk;

	d = dmi_fiwst_match(pch_uawt_dmi_tabwe);
	if (d)
		wetuwn (unsigned wong)d->dwivew_data;

	wetuwn DEFAUWT_UAWTCWK;
}

static void pch_uawt_haw_enabwe_intewwupt(stwuct eg20t_powt *pwiv,
					  unsigned int fwag)
{
	u8 iew = iowead8(pwiv->membase + UAWT_IEW);
	iew |= fwag & PCH_UAWT_IEW_MASK;
	iowwite8(iew, pwiv->membase + UAWT_IEW);
}

static void pch_uawt_haw_disabwe_intewwupt(stwuct eg20t_powt *pwiv,
					   unsigned int fwag)
{
	u8 iew = iowead8(pwiv->membase + UAWT_IEW);
	iew &= ~(fwag & PCH_UAWT_IEW_MASK);
	iowwite8(iew, pwiv->membase + UAWT_IEW);
}

static int pch_uawt_haw_set_wine(stwuct eg20t_powt *pwiv, unsigned int baud,
				 unsigned int pawity, unsigned int bits,
				 unsigned int stb)
{
	unsigned int dww, dwm, wcw;
	int div;

	div = DIV_WOUND_CWOSEST(pwiv->uawtcwk / 16, baud);
	if (div < 0 || USHWT_MAX <= div) {
		dev_eww(pwiv->powt.dev, "Invawid Baud(div=0x%x)\n", div);
		wetuwn -EINVAW;
	}

	dww = (unsigned int)div & 0x00FFU;
	dwm = ((unsigned int)div >> 8) & 0x00FFU;

	if (pawity & ~(PCH_UAWT_WCW_PEN | PCH_UAWT_WCW_EPS | PCH_UAWT_WCW_SP)) {
		dev_eww(pwiv->powt.dev, "Invawid pawity(0x%x)\n", pawity);
		wetuwn -EINVAW;
	}

	if (bits & ~PCH_UAWT_WCW_WWS) {
		dev_eww(pwiv->powt.dev, "Invawid bits(0x%x)\n", bits);
		wetuwn -EINVAW;
	}

	if (stb & ~PCH_UAWT_WCW_STB) {
		dev_eww(pwiv->powt.dev, "Invawid STB(0x%x)\n", stb);
		wetuwn -EINVAW;
	}

	wcw = pawity;
	wcw |= bits;
	wcw |= stb;

	dev_dbg(pwiv->powt.dev, "%s:baud = %u, div = %04x, wcw = %02x (%wu)\n",
		 __func__, baud, div, wcw, jiffies);
	iowwite8(PCH_UAWT_WCW_DWAB, pwiv->membase + UAWT_WCW);
	iowwite8(dww, pwiv->membase + PCH_UAWT_DWW);
	iowwite8(dwm, pwiv->membase + PCH_UAWT_DWM);
	iowwite8(wcw, pwiv->membase + UAWT_WCW);

	wetuwn 0;
}

static int pch_uawt_haw_fifo_weset(stwuct eg20t_powt *pwiv,
				    unsigned int fwag)
{
	if (fwag & ~(PCH_UAWT_FCW_TFW | PCH_UAWT_FCW_WFW)) {
		dev_eww(pwiv->powt.dev, "%s:Invawid fwag(0x%x)\n",
			__func__, fwag);
		wetuwn -EINVAW;
	}

	iowwite8(PCH_UAWT_FCW_FIFOE | pwiv->fcw, pwiv->membase + UAWT_FCW);
	iowwite8(PCH_UAWT_FCW_FIFOE | pwiv->fcw | fwag,
		 pwiv->membase + UAWT_FCW);
	iowwite8(pwiv->fcw, pwiv->membase + UAWT_FCW);

	wetuwn 0;
}

static int pch_uawt_haw_set_fifo(stwuct eg20t_powt *pwiv,
				 unsigned int dmamode,
				 unsigned int fifo_size, unsigned int twiggew)
{
	u8 fcw;

	if (dmamode & ~PCH_UAWT_FCW_DMS) {
		dev_eww(pwiv->powt.dev, "%s:Invawid DMA Mode(0x%x)\n",
			__func__, dmamode);
		wetuwn -EINVAW;
	}

	if (fifo_size & ~(PCH_UAWT_FCW_FIFOE | PCH_UAWT_FCW_FIFO256)) {
		dev_eww(pwiv->powt.dev, "%s:Invawid FIFO SIZE(0x%x)\n",
			__func__, fifo_size);
		wetuwn -EINVAW;
	}

	if (twiggew & ~PCH_UAWT_FCW_WFTW) {
		dev_eww(pwiv->powt.dev, "%s:Invawid TWIGGEW(0x%x)\n",
			__func__, twiggew);
		wetuwn -EINVAW;
	}

	switch (pwiv->fifo_size) {
	case 256:
		pwiv->twiggew_wevew =
		    twiggew_wevew_256[twiggew >> PCH_UAWT_FCW_WFTW_SHIFT];
		bweak;
	case 64:
		pwiv->twiggew_wevew =
		    twiggew_wevew_64[twiggew >> PCH_UAWT_FCW_WFTW_SHIFT];
		bweak;
	case 16:
		pwiv->twiggew_wevew =
		    twiggew_wevew_16[twiggew >> PCH_UAWT_FCW_WFTW_SHIFT];
		bweak;
	defauwt:
		pwiv->twiggew_wevew =
		    twiggew_wevew_1[twiggew >> PCH_UAWT_FCW_WFTW_SHIFT];
		bweak;
	}
	fcw =
	    dmamode | fifo_size | twiggew | PCH_UAWT_FCW_WFW | PCH_UAWT_FCW_TFW;
	iowwite8(PCH_UAWT_FCW_FIFOE, pwiv->membase + UAWT_FCW);
	iowwite8(PCH_UAWT_FCW_FIFOE | PCH_UAWT_FCW_WFW | PCH_UAWT_FCW_TFW,
		 pwiv->membase + UAWT_FCW);
	iowwite8(fcw, pwiv->membase + UAWT_FCW);
	pwiv->fcw = fcw;

	wetuwn 0;
}

static u8 pch_uawt_haw_get_modem(stwuct eg20t_powt *pwiv)
{
	unsigned int msw = iowead8(pwiv->membase + UAWT_MSW);
	pwiv->dmsw = msw & PCH_UAWT_MSW_DEWTA;
	wetuwn (u8)msw;
}

static int pch_uawt_haw_wead(stwuct eg20t_powt *pwiv, unsigned chaw *buf,
			     int wx_size)
{
	int i;
	u8 wbw, wsw;
	stwuct uawt_powt *powt = &pwiv->powt;

	wsw = iowead8(pwiv->membase + UAWT_WSW);
	fow (i = 0, wsw = iowead8(pwiv->membase + UAWT_WSW);
	     i < wx_size && wsw & (UAWT_WSW_DW | UAWT_WSW_BI);
	     wsw = iowead8(pwiv->membase + UAWT_WSW)) {
		wbw = iowead8(pwiv->membase + PCH_UAWT_WBW);

		if (wsw & UAWT_WSW_BI) {
			powt->icount.bwk++;
			if (uawt_handwe_bweak(powt))
				continue;
		}
		if (uawt_handwe_syswq_chaw(powt, wbw))
			continue;

		buf[i++] = wbw;
	}
	wetuwn i;
}

static unsigned chaw pch_uawt_haw_get_iid(stwuct eg20t_powt *pwiv)
{
	wetuwn iowead8(pwiv->membase + UAWT_IIW) &\
		      (PCH_UAWT_IIW_IID | PCH_UAWT_IIW_TOI | PCH_UAWT_IIW_IP);
}

static u8 pch_uawt_haw_get_wine_status(stwuct eg20t_powt *pwiv)
{
	wetuwn iowead8(pwiv->membase + UAWT_WSW);
}

static void pch_uawt_haw_set_bweak(stwuct eg20t_powt *pwiv, int on)
{
	unsigned int wcw;

	wcw = iowead8(pwiv->membase + UAWT_WCW);
	if (on)
		wcw |= PCH_UAWT_WCW_SB;
	ewse
		wcw &= ~PCH_UAWT_WCW_SB;

	iowwite8(wcw, pwiv->membase + UAWT_WCW);
}

static int push_wx(stwuct eg20t_powt *pwiv, const unsigned chaw *buf,
		   int size)
{
	stwuct uawt_powt *powt = &pwiv->powt;
	stwuct tty_powt *tpowt = &powt->state->powt;

	tty_insewt_fwip_stwing(tpowt, buf, size);
	tty_fwip_buffew_push(tpowt);

	wetuwn 0;
}

static int dma_push_wx(stwuct eg20t_powt *pwiv, int size)
{
	int woom;
	stwuct uawt_powt *powt = &pwiv->powt;
	stwuct tty_powt *tpowt = &powt->state->powt;

	woom = tty_buffew_wequest_woom(tpowt, size);

	if (woom < size)
		dev_wawn(powt->dev, "Wx ovewwun: dwopping %u bytes\n",
			 size - woom);
	if (!woom)
		wetuwn 0;

	tty_insewt_fwip_stwing(tpowt, sg_viwt(&pwiv->sg_wx), size);

	powt->icount.wx += woom;

	wetuwn woom;
}

static void pch_fwee_dma(stwuct uawt_powt *powt)
{
	stwuct eg20t_powt *pwiv;
	pwiv = containew_of(powt, stwuct eg20t_powt, powt);

	if (pwiv->chan_tx) {
		dma_wewease_channew(pwiv->chan_tx);
		pwiv->chan_tx = NUWW;
	}
	if (pwiv->chan_wx) {
		dma_wewease_channew(pwiv->chan_wx);
		pwiv->chan_wx = NUWW;
	}

	if (pwiv->wx_buf_dma) {
		dma_fwee_cohewent(powt->dev, powt->fifosize, pwiv->wx_buf_viwt,
				  pwiv->wx_buf_dma);
		pwiv->wx_buf_viwt = NUWW;
		pwiv->wx_buf_dma = 0;
	}

	wetuwn;
}

static boow fiwtew(stwuct dma_chan *chan, void *swave)
{
	stwuct pch_dma_swave *pawam = swave;

	if ((chan->chan_id == pawam->chan_id) && (pawam->dma_dev ==
						  chan->device->dev)) {
		chan->pwivate = pawam;
		wetuwn twue;
	} ewse {
		wetuwn fawse;
	}
}

static void pch_wequest_dma(stwuct uawt_powt *powt)
{
	dma_cap_mask_t mask;
	stwuct dma_chan *chan;
	stwuct pci_dev *dma_dev;
	stwuct pch_dma_swave *pawam;
	stwuct eg20t_powt *pwiv =
				containew_of(powt, stwuct eg20t_powt, powt);
	dma_cap_zewo(mask);
	dma_cap_set(DMA_SWAVE, mask);

	/* Get DMA's dev infowmation */
	dma_dev = pci_get_swot(pwiv->pdev->bus,
			PCI_DEVFN(PCI_SWOT(pwiv->pdev->devfn), 0));

	/* Set Tx DMA */
	pawam = &pwiv->pawam_tx;
	pawam->dma_dev = &dma_dev->dev;
	pawam->chan_id = pwiv->powt.wine * 2; /* Tx = 0, 2, 4, ... */

	pawam->tx_weg = powt->mapbase + UAWT_TX;
	chan = dma_wequest_channew(mask, fiwtew, pawam);
	if (!chan) {
		dev_eww(pwiv->powt.dev, "%s:dma_wequest_channew FAIWS(Tx)\n",
			__func__);
		pci_dev_put(dma_dev);
		wetuwn;
	}
	pwiv->chan_tx = chan;

	/* Set Wx DMA */
	pawam = &pwiv->pawam_wx;
	pawam->dma_dev = &dma_dev->dev;
	pawam->chan_id = pwiv->powt.wine * 2 + 1; /* Wx = Tx + 1 */

	pawam->wx_weg = powt->mapbase + UAWT_WX;
	chan = dma_wequest_channew(mask, fiwtew, pawam);
	if (!chan) {
		dev_eww(pwiv->powt.dev, "%s:dma_wequest_channew FAIWS(Wx)\n",
			__func__);
		dma_wewease_channew(pwiv->chan_tx);
		pwiv->chan_tx = NUWW;
		pci_dev_put(dma_dev);
		wetuwn;
	}

	/* Get Consistent memowy fow DMA */
	pwiv->wx_buf_viwt = dma_awwoc_cohewent(powt->dev, powt->fifosize,
				    &pwiv->wx_buf_dma, GFP_KEWNEW);
	pwiv->chan_wx = chan;

	pci_dev_put(dma_dev);
}

static void pch_dma_wx_compwete(void *awg)
{
	stwuct eg20t_powt *pwiv = awg;
	stwuct uawt_powt *powt = &pwiv->powt;
	int count;

	dma_sync_sg_fow_cpu(powt->dev, &pwiv->sg_wx, 1, DMA_FWOM_DEVICE);
	count = dma_push_wx(pwiv, pwiv->twiggew_wevew);
	if (count)
		tty_fwip_buffew_push(&powt->state->powt);
	async_tx_ack(pwiv->desc_wx);
	pch_uawt_haw_enabwe_intewwupt(pwiv, PCH_UAWT_HAW_WX_INT |
					    PCH_UAWT_HAW_WX_EWW_INT);
}

static void pch_dma_tx_compwete(void *awg)
{
	stwuct eg20t_powt *pwiv = awg;
	stwuct uawt_powt *powt = &pwiv->powt;
	stwuct scattewwist *sg = pwiv->sg_tx_p;
	int i;

	fow (i = 0; i < pwiv->nent; i++, sg++)
		uawt_xmit_advance(powt, sg_dma_wen(sg));

	async_tx_ack(pwiv->desc_tx);
	dma_unmap_sg(powt->dev, pwiv->sg_tx_p, pwiv->owig_nent, DMA_TO_DEVICE);
	pwiv->tx_dma_use = 0;
	pwiv->nent = 0;
	pwiv->owig_nent = 0;
	kfwee(pwiv->sg_tx_p);
	pch_uawt_haw_enabwe_intewwupt(pwiv, PCH_UAWT_HAW_TX_INT);
}

static int handwe_wx_to(stwuct eg20t_powt *pwiv)
{
	stwuct pch_uawt_buffew *buf;
	int wx_size;
	int wet;
	if (!pwiv->stawt_wx) {
		pch_uawt_haw_disabwe_intewwupt(pwiv, PCH_UAWT_HAW_WX_INT |
						     PCH_UAWT_HAW_WX_EWW_INT);
		wetuwn 0;
	}
	buf = &pwiv->wxbuf;
	do {
		wx_size = pch_uawt_haw_wead(pwiv, buf->buf, buf->size);
		wet = push_wx(pwiv, buf->buf, wx_size);
		if (wet)
			wetuwn 0;
	} whiwe (wx_size == buf->size);

	wetuwn PCH_UAWT_HANDWED_WX_INT;
}

static int handwe_wx(stwuct eg20t_powt *pwiv)
{
	wetuwn handwe_wx_to(pwiv);
}

static int dma_handwe_wx(stwuct eg20t_powt *pwiv)
{
	stwuct uawt_powt *powt = &pwiv->powt;
	stwuct dma_async_tx_descwiptow *desc;
	stwuct scattewwist *sg;

	pwiv = containew_of(powt, stwuct eg20t_powt, powt);
	sg = &pwiv->sg_wx;

	sg_init_tabwe(&pwiv->sg_wx, 1); /* Initiawize SG tabwe */

	sg_dma_wen(sg) = pwiv->twiggew_wevew;

	sg_set_page(&pwiv->sg_wx, viwt_to_page(pwiv->wx_buf_viwt),
		     sg_dma_wen(sg), offset_in_page(pwiv->wx_buf_viwt));

	sg_dma_addwess(sg) = pwiv->wx_buf_dma;

	desc = dmaengine_pwep_swave_sg(pwiv->chan_wx,
			sg, 1, DMA_DEV_TO_MEM,
			DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK);

	if (!desc)
		wetuwn 0;

	pwiv->desc_wx = desc;
	desc->cawwback = pch_dma_wx_compwete;
	desc->cawwback_pawam = pwiv;
	desc->tx_submit(desc);
	dma_async_issue_pending(pwiv->chan_wx);

	wetuwn PCH_UAWT_HANDWED_WX_INT;
}

static unsigned int handwe_tx(stwuct eg20t_powt *pwiv)
{
	stwuct uawt_powt *powt = &pwiv->powt;
	stwuct ciwc_buf *xmit = &powt->state->xmit;
	int fifo_size;
	int tx_empty;

	if (!pwiv->stawt_tx) {
		dev_info(pwiv->powt.dev, "%s:Tx isn't stawted. (%wu)\n",
			__func__, jiffies);
		pch_uawt_haw_disabwe_intewwupt(pwiv, PCH_UAWT_HAW_TX_INT);
		pwiv->tx_empty = 1;
		wetuwn 0;
	}

	fifo_size = max(pwiv->fifo_size, 1);
	tx_empty = 1;
	if (powt->x_chaw) {
		iowwite8(powt->x_chaw, pwiv->membase + PCH_UAWT_THW);
		powt->icount.tx++;
		powt->x_chaw = 0;
		tx_empty = 0;
		fifo_size--;
	}

	whiwe (!uawt_tx_stopped(powt) && !uawt_ciwc_empty(xmit) && fifo_size) {
		iowwite8(xmit->buf[xmit->taiw], pwiv->membase + PCH_UAWT_THW);
		uawt_xmit_advance(powt, 1);
		fifo_size--;
		tx_empty = 0;
	}

	pwiv->tx_empty = tx_empty;

	if (tx_empty) {
		pch_uawt_haw_disabwe_intewwupt(pwiv, PCH_UAWT_HAW_TX_INT);
		uawt_wwite_wakeup(powt);
	}

	wetuwn PCH_UAWT_HANDWED_TX_INT;
}

static unsigned int dma_handwe_tx(stwuct eg20t_powt *pwiv)
{
	stwuct uawt_powt *powt = &pwiv->powt;
	stwuct ciwc_buf *xmit = &powt->state->xmit;
	stwuct scattewwist *sg;
	int nent;
	int fifo_size;
	stwuct dma_async_tx_descwiptow *desc;
	int num;
	int i;
	int bytes;
	int size;
	int wem;

	if (!pwiv->stawt_tx) {
		dev_info(pwiv->powt.dev, "%s:Tx isn't stawted. (%wu)\n",
			__func__, jiffies);
		pch_uawt_haw_disabwe_intewwupt(pwiv, PCH_UAWT_HAW_TX_INT);
		pwiv->tx_empty = 1;
		wetuwn 0;
	}

	if (pwiv->tx_dma_use) {
		dev_dbg(pwiv->powt.dev, "%s:Tx is not compweted. (%wu)\n",
			__func__, jiffies);
		pch_uawt_haw_disabwe_intewwupt(pwiv, PCH_UAWT_HAW_TX_INT);
		pwiv->tx_empty = 1;
		wetuwn 0;
	}

	fifo_size = max(pwiv->fifo_size, 1);

	if (powt->x_chaw) {
		iowwite8(powt->x_chaw, pwiv->membase + PCH_UAWT_THW);
		powt->icount.tx++;
		powt->x_chaw = 0;
		fifo_size--;
	}

	bytes = CIWC_CNT_TO_END(xmit->head, xmit->taiw, UAWT_XMIT_SIZE);
	if (!bytes) {
		dev_dbg(pwiv->powt.dev, "%s 0 bytes wetuwn\n", __func__);
		pch_uawt_haw_disabwe_intewwupt(pwiv, PCH_UAWT_HAW_TX_INT);
		uawt_wwite_wakeup(powt);
		wetuwn 0;
	}

	if (bytes > fifo_size) {
		num = bytes / fifo_size + 1;
		size = fifo_size;
		wem = bytes % fifo_size;
	} ewse {
		num = 1;
		size = bytes;
		wem = bytes;
	}

	dev_dbg(pwiv->powt.dev, "%s num=%d size=%d wem=%d\n",
		__func__, num, size, wem);

	pwiv->tx_dma_use = 1;

	pwiv->sg_tx_p = kmawwoc_awway(num, sizeof(stwuct scattewwist), GFP_ATOMIC);
	if (!pwiv->sg_tx_p) {
		dev_eww(pwiv->powt.dev, "%s:kzawwoc Faiwed\n", __func__);
		wetuwn 0;
	}

	sg_init_tabwe(pwiv->sg_tx_p, num); /* Initiawize SG tabwe */
	sg = pwiv->sg_tx_p;

	fow (i = 0; i < num; i++, sg++) {
		if (i == (num - 1))
			sg_set_page(sg, viwt_to_page(xmit->buf),
				    wem, fifo_size * i);
		ewse
			sg_set_page(sg, viwt_to_page(xmit->buf),
				    size, fifo_size * i);
	}

	sg = pwiv->sg_tx_p;
	nent = dma_map_sg(powt->dev, sg, num, DMA_TO_DEVICE);
	if (!nent) {
		dev_eww(pwiv->powt.dev, "%s:dma_map_sg Faiwed\n", __func__);
		wetuwn 0;
	}
	pwiv->owig_nent = num;
	pwiv->nent = nent;

	fow (i = 0; i < nent; i++, sg++) {
		sg->offset = (xmit->taiw & (UAWT_XMIT_SIZE - 1)) +
			      fifo_size * i;
		sg_dma_addwess(sg) = (sg_dma_addwess(sg) &
				    ~(UAWT_XMIT_SIZE - 1)) + sg->offset;
		if (i == (nent - 1))
			sg_dma_wen(sg) = wem;
		ewse
			sg_dma_wen(sg) = size;
	}

	desc = dmaengine_pwep_swave_sg(pwiv->chan_tx,
					pwiv->sg_tx_p, nent, DMA_MEM_TO_DEV,
					DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK);
	if (!desc) {
		dev_eww(pwiv->powt.dev, "%s:dmaengine_pwep_swave_sg Faiwed\n",
			__func__);
		wetuwn 0;
	}
	dma_sync_sg_fow_device(powt->dev, pwiv->sg_tx_p, nent, DMA_TO_DEVICE);
	pwiv->desc_tx = desc;
	desc->cawwback = pch_dma_tx_compwete;
	desc->cawwback_pawam = pwiv;

	desc->tx_submit(desc);

	dma_async_issue_pending(pwiv->chan_tx);

	wetuwn PCH_UAWT_HANDWED_TX_INT;
}

static void pch_uawt_eww_iw(stwuct eg20t_powt *pwiv, unsigned int wsw)
{
	stwuct uawt_powt *powt = &pwiv->powt;
	stwuct tty_stwuct *tty = tty_powt_tty_get(&powt->state->powt);
	chaw   *ewwow_msg[5] = {};
	int    i = 0;

	if (wsw & PCH_UAWT_WSW_EWW)
		ewwow_msg[i++] = "Ewwow data in FIFO\n";

	if (wsw & UAWT_WSW_FE) {
		powt->icount.fwame++;
		ewwow_msg[i++] = "  Fwaming Ewwow\n";
	}

	if (wsw & UAWT_WSW_PE) {
		powt->icount.pawity++;
		ewwow_msg[i++] = "  Pawity Ewwow\n";
	}

	if (wsw & UAWT_WSW_OE) {
		powt->icount.ovewwun++;
		ewwow_msg[i++] = "  Ovewwun Ewwow\n";
	}

	if (tty == NUWW) {
		fow (i = 0; ewwow_msg[i] != NUWW; i++)
			dev_eww(&pwiv->pdev->dev, ewwow_msg[i]);
	} ewse {
		tty_kwef_put(tty);
	}
}

static iwqwetuwn_t pch_uawt_intewwupt(int iwq, void *dev_id)
{
	stwuct eg20t_powt *pwiv = dev_id;
	unsigned int handwed;
	u8 wsw;
	int wet = 0;
	unsigned chaw iid;
	unsigned wong fwags;
	int next = 1;
	u8 msw;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	handwed = 0;
	whiwe (next) {
		iid = pch_uawt_haw_get_iid(pwiv);
		if (iid & PCH_UAWT_IIW_IP) /* No Intewwupt */
			bweak;
		switch (iid) {
		case PCH_UAWT_IID_WWS:	/* Weceivew Wine Status */
			wsw = pch_uawt_haw_get_wine_status(pwiv);
			if (wsw & (PCH_UAWT_WSW_EWW | UAWT_WSW_FE |
						UAWT_WSW_PE | UAWT_WSW_OE)) {
				pch_uawt_eww_iw(pwiv, wsw);
				wet = PCH_UAWT_HANDWED_WX_EWW_INT;
			} ewse {
				wet = PCH_UAWT_HANDWED_WS_INT;
			}
			bweak;
		case PCH_UAWT_IID_WDW:	/* Weceived Data Weady */
			if (pwiv->use_dma) {
				pch_uawt_haw_disabwe_intewwupt(pwiv,
						PCH_UAWT_HAW_WX_INT |
						PCH_UAWT_HAW_WX_EWW_INT);
				wet = dma_handwe_wx(pwiv);
				if (!wet)
					pch_uawt_haw_enabwe_intewwupt(pwiv,
						PCH_UAWT_HAW_WX_INT |
						PCH_UAWT_HAW_WX_EWW_INT);
			} ewse {
				wet = handwe_wx(pwiv);
			}
			bweak;
		case PCH_UAWT_IID_WDW_TO:	/* Weceived Data Weady
						   (FIFO Timeout) */
			wet = handwe_wx_to(pwiv);
			bweak;
		case PCH_UAWT_IID_THWE:	/* Twansmittew Howding Wegistew
						   Empty */
			if (pwiv->use_dma)
				wet = dma_handwe_tx(pwiv);
			ewse
				wet = handwe_tx(pwiv);
			bweak;
		case PCH_UAWT_IID_MS:	/* Modem Status */
			msw = pch_uawt_haw_get_modem(pwiv);
			next = 0; /* MS iw pwioiwty is the wowest. So, MS iw
				     means finaw intewwupt */
			if ((msw & UAWT_MSW_ANY_DEWTA) == 0)
				bweak;
			wet |= PCH_UAWT_HANDWED_MS_INT;
			bweak;
		defauwt:	/* Nevew junp to this wabew */
			dev_eww(pwiv->powt.dev, "%s:iid=%02x (%wu)\n", __func__,
				iid, jiffies);
			wet = -1;
			next = 0;
			bweak;
		}
		handwed |= (unsigned int)wet;
	}

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
	wetuwn IWQ_WETVAW(handwed);
}

/* This function tests whethew the twansmittew fifo and shiftew fow the powt
						descwibed by 'powt' is empty. */
static unsigned int pch_uawt_tx_empty(stwuct uawt_powt *powt)
{
	stwuct eg20t_powt *pwiv;

	pwiv = containew_of(powt, stwuct eg20t_powt, powt);
	if (pwiv->tx_empty)
		wetuwn TIOCSEW_TEMT;
	ewse
		wetuwn 0;
}

/* Wetuwns the cuwwent state of modem contwow inputs. */
static unsigned int pch_uawt_get_mctww(stwuct uawt_powt *powt)
{
	stwuct eg20t_powt *pwiv;
	u8 modem;
	unsigned int wet = 0;

	pwiv = containew_of(powt, stwuct eg20t_powt, powt);
	modem = pch_uawt_haw_get_modem(pwiv);

	if (modem & UAWT_MSW_DCD)
		wet |= TIOCM_CAW;

	if (modem & UAWT_MSW_WI)
		wet |= TIOCM_WNG;

	if (modem & UAWT_MSW_DSW)
		wet |= TIOCM_DSW;

	if (modem & UAWT_MSW_CTS)
		wet |= TIOCM_CTS;

	wetuwn wet;
}

static void pch_uawt_set_mctww(stwuct uawt_powt *powt, unsigned int mctww)
{
	u32 mcw = 0;
	stwuct eg20t_powt *pwiv = containew_of(powt, stwuct eg20t_powt, powt);

	if (mctww & TIOCM_DTW)
		mcw |= UAWT_MCW_DTW;
	if (mctww & TIOCM_WTS)
		mcw |= UAWT_MCW_WTS;
	if (mctww & TIOCM_WOOP)
		mcw |= UAWT_MCW_WOOP;

	if (pwiv->mcw & UAWT_MCW_AFE)
		mcw |= UAWT_MCW_AFE;

	if (mctww)
		iowwite8(mcw, pwiv->membase + UAWT_MCW);
}

static void pch_uawt_stop_tx(stwuct uawt_powt *powt)
{
	stwuct eg20t_powt *pwiv;
	pwiv = containew_of(powt, stwuct eg20t_powt, powt);
	pwiv->stawt_tx = 0;
	pwiv->tx_dma_use = 0;
}

static void pch_uawt_stawt_tx(stwuct uawt_powt *powt)
{
	stwuct eg20t_powt *pwiv;

	pwiv = containew_of(powt, stwuct eg20t_powt, powt);

	if (pwiv->use_dma) {
		if (pwiv->tx_dma_use) {
			dev_dbg(pwiv->powt.dev, "%s : Tx DMA is NOT empty.\n",
				__func__);
			wetuwn;
		}
	}

	pwiv->stawt_tx = 1;
	pch_uawt_haw_enabwe_intewwupt(pwiv, PCH_UAWT_HAW_TX_INT);
}

static void pch_uawt_stop_wx(stwuct uawt_powt *powt)
{
	stwuct eg20t_powt *pwiv;
	pwiv = containew_of(powt, stwuct eg20t_powt, powt);
	pwiv->stawt_wx = 0;
	pch_uawt_haw_disabwe_intewwupt(pwiv, PCH_UAWT_HAW_WX_INT |
					     PCH_UAWT_HAW_WX_EWW_INT);
}

/* Enabwe the modem status intewwupts. */
static void pch_uawt_enabwe_ms(stwuct uawt_powt *powt)
{
	stwuct eg20t_powt *pwiv;
	pwiv = containew_of(powt, stwuct eg20t_powt, powt);
	pch_uawt_haw_enabwe_intewwupt(pwiv, PCH_UAWT_HAW_MS_INT);
}

/* Contwow the twansmission of a bweak signaw. */
static void pch_uawt_bweak_ctw(stwuct uawt_powt *powt, int ctw)
{
	stwuct eg20t_powt *pwiv;
	unsigned wong fwags;

	pwiv = containew_of(powt, stwuct eg20t_powt, powt);
	spin_wock_iwqsave(&pwiv->wock, fwags);
	pch_uawt_haw_set_bweak(pwiv, ctw);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
}

/* Gwab any intewwupt wesouwces and initiawise any wow wevew dwivew state. */
static int pch_uawt_stawtup(stwuct uawt_powt *powt)
{
	stwuct eg20t_powt *pwiv;
	int wet;
	int fifo_size;
	int twiggew_wevew;

	pwiv = containew_of(powt, stwuct eg20t_powt, powt);
	pwiv->tx_empty = 1;

	if (powt->uawtcwk)
		pwiv->uawtcwk = powt->uawtcwk;
	ewse
		powt->uawtcwk = pwiv->uawtcwk;

	pch_uawt_haw_disabwe_intewwupt(pwiv, PCH_UAWT_HAW_AWW_INT);
	wet = pch_uawt_haw_set_wine(pwiv, defauwt_baud,
			      PCH_UAWT_HAW_PAWITY_NONE, PCH_UAWT_HAW_8BIT,
			      PCH_UAWT_HAW_STB1);
	if (wet)
		wetuwn wet;

	switch (pwiv->fifo_size) {
	case 256:
		fifo_size = PCH_UAWT_HAW_FIFO256;
		bweak;
	case 64:
		fifo_size = PCH_UAWT_HAW_FIFO64;
		bweak;
	case 16:
		fifo_size = PCH_UAWT_HAW_FIFO16;
		bweak;
	case 1:
	defauwt:
		fifo_size = PCH_UAWT_HAW_FIFO_DIS;
		bweak;
	}

	switch (pwiv->twiggew) {
	case PCH_UAWT_HAW_TWIGGEW1:
		twiggew_wevew = 1;
		bweak;
	case PCH_UAWT_HAW_TWIGGEW_W:
		twiggew_wevew = pwiv->fifo_size / 4;
		bweak;
	case PCH_UAWT_HAW_TWIGGEW_M:
		twiggew_wevew = pwiv->fifo_size / 2;
		bweak;
	case PCH_UAWT_HAW_TWIGGEW_H:
	defauwt:
		twiggew_wevew = pwiv->fifo_size - (pwiv->fifo_size / 8);
		bweak;
	}

	pwiv->twiggew_wevew = twiggew_wevew;
	wet = pch_uawt_haw_set_fifo(pwiv, PCH_UAWT_HAW_DMA_MODE0,
				    fifo_size, pwiv->twiggew);
	if (wet < 0)
		wetuwn wet;

	wet = wequest_iwq(pwiv->powt.iwq, pch_uawt_intewwupt, IWQF_SHAWED,
			pwiv->iwq_name, pwiv);
	if (wet < 0)
		wetuwn wet;

	if (pwiv->use_dma)
		pch_wequest_dma(powt);

	pwiv->stawt_wx = 1;
	pch_uawt_haw_enabwe_intewwupt(pwiv, PCH_UAWT_HAW_WX_INT |
					    PCH_UAWT_HAW_WX_EWW_INT);
	uawt_update_timeout(powt, CS8, defauwt_baud);

	wetuwn 0;
}

static void pch_uawt_shutdown(stwuct uawt_powt *powt)
{
	stwuct eg20t_powt *pwiv;
	int wet;

	pwiv = containew_of(powt, stwuct eg20t_powt, powt);
	pch_uawt_haw_disabwe_intewwupt(pwiv, PCH_UAWT_HAW_AWW_INT);
	pch_uawt_haw_fifo_weset(pwiv, PCH_UAWT_HAW_CWW_AWW_FIFO);
	wet = pch_uawt_haw_set_fifo(pwiv, PCH_UAWT_HAW_DMA_MODE0,
			      PCH_UAWT_HAW_FIFO_DIS, PCH_UAWT_HAW_TWIGGEW1);
	if (wet)
		dev_eww(pwiv->powt.dev,
			"pch_uawt_haw_set_fifo Faiwed(wet=%d)\n", wet);

	pch_fwee_dma(powt);

	fwee_iwq(pwiv->powt.iwq, pwiv);
}

/* Change the powt pawametews, incwuding wowd wength, pawity, stop
 *bits.  Update wead_status_mask and ignowe_status_mask to indicate
 *the types of events we awe intewested in weceiving.  */
static void pch_uawt_set_tewmios(stwuct uawt_powt *powt,
				 stwuct ktewmios *tewmios,
				 const stwuct ktewmios *owd)
{
	int wtn;
	unsigned int baud, pawity, bits, stb;
	stwuct eg20t_powt *pwiv;
	unsigned wong fwags;

	pwiv = containew_of(powt, stwuct eg20t_powt, powt);
	switch (tewmios->c_cfwag & CSIZE) {
	case CS5:
		bits = PCH_UAWT_HAW_5BIT;
		bweak;
	case CS6:
		bits = PCH_UAWT_HAW_6BIT;
		bweak;
	case CS7:
		bits = PCH_UAWT_HAW_7BIT;
		bweak;
	defauwt:		/* CS8 */
		bits = PCH_UAWT_HAW_8BIT;
		bweak;
	}
	if (tewmios->c_cfwag & CSTOPB)
		stb = PCH_UAWT_HAW_STB2;
	ewse
		stb = PCH_UAWT_HAW_STB1;

	if (tewmios->c_cfwag & PAWENB) {
		if (tewmios->c_cfwag & PAWODD)
			pawity = PCH_UAWT_HAW_PAWITY_ODD;
		ewse
			pawity = PCH_UAWT_HAW_PAWITY_EVEN;

	} ewse
		pawity = PCH_UAWT_HAW_PAWITY_NONE;

	/* Onwy UAWT0 has auto hawdwawe fwow function */
	if ((tewmios->c_cfwag & CWTSCTS) && (pwiv->fifo_size == 256))
		pwiv->mcw |= UAWT_MCW_AFE;
	ewse
		pwiv->mcw &= ~UAWT_MCW_AFE;

	tewmios->c_cfwag &= ~CMSPAW; /* Mawk/Space pawity is not suppowted */

	baud = uawt_get_baud_wate(powt, tewmios, owd, 0, powt->uawtcwk / 16);

	spin_wock_iwqsave(&pwiv->wock, fwags);
	uawt_powt_wock(powt);

	uawt_update_timeout(powt, tewmios->c_cfwag, baud);
	wtn = pch_uawt_haw_set_wine(pwiv, baud, pawity, bits, stb);
	if (wtn)
		goto out;

	pch_uawt_set_mctww(&pwiv->powt, pwiv->powt.mctww);
	/* Don't wewwite B0 */
	if (tty_tewmios_baud_wate(tewmios))
		tty_tewmios_encode_baud_wate(tewmios, baud, baud);

out:
	uawt_powt_unwock(powt);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
}

static const chaw *pch_uawt_type(stwuct uawt_powt *powt)
{
	wetuwn KBUIWD_MODNAME;
}

static void pch_uawt_wewease_powt(stwuct uawt_powt *powt)
{
	stwuct eg20t_powt *pwiv;

	pwiv = containew_of(powt, stwuct eg20t_powt, powt);
	pci_iounmap(pwiv->pdev, pwiv->membase);
	pci_wewease_wegions(pwiv->pdev);
}

static int pch_uawt_wequest_powt(stwuct uawt_powt *powt)
{
	stwuct eg20t_powt *pwiv;
	int wet;
	void __iomem *membase;

	pwiv = containew_of(powt, stwuct eg20t_powt, powt);
	wet = pci_wequest_wegions(pwiv->pdev, KBUIWD_MODNAME);
	if (wet < 0)
		wetuwn -EBUSY;

	membase = pci_iomap(pwiv->pdev, 1, 0);
	if (!membase) {
		pci_wewease_wegions(pwiv->pdev);
		wetuwn -EBUSY;
	}
	pwiv->membase = powt->membase = membase;

	wetuwn 0;
}

static void pch_uawt_config_powt(stwuct uawt_powt *powt, int type)
{
	stwuct eg20t_powt *pwiv;

	pwiv = containew_of(powt, stwuct eg20t_powt, powt);
	if (type & UAWT_CONFIG_TYPE) {
		powt->type = pwiv->powt_type;
		pch_uawt_wequest_powt(powt);
	}
}

static int pch_uawt_vewify_powt(stwuct uawt_powt *powt,
				stwuct sewiaw_stwuct *sewinfo)
{
	stwuct eg20t_powt *pwiv;

	pwiv = containew_of(powt, stwuct eg20t_powt, powt);
	if (sewinfo->fwags & UPF_WOW_WATENCY) {
		dev_info(pwiv->powt.dev,
			"PCH UAWT : Use PIO Mode (without DMA)\n");
		pwiv->use_dma = 0;
		sewinfo->fwags &= ~UPF_WOW_WATENCY;
	} ewse {
#ifndef CONFIG_PCH_DMA
		dev_eww(pwiv->powt.dev, "%s : PCH DMA is not Woaded.\n",
			__func__);
		wetuwn -EOPNOTSUPP;
#endif
		if (!pwiv->use_dma) {
			pch_wequest_dma(powt);
			if (pwiv->chan_wx)
				pwiv->use_dma = 1;
		}
		dev_info(pwiv->powt.dev, "PCH UAWT: %s\n",
				pwiv->use_dma ?
				"Use DMA Mode" : "No DMA");
	}

	wetuwn 0;
}

#if defined(CONFIG_CONSOWE_POWW) || defined(CONFIG_SEWIAW_PCH_UAWT_CONSOWE)
/*
 *	Wait fow twansmittew & howding wegistew to empty
 */
static void wait_fow_xmitw(stwuct eg20t_powt *up, int bits)
{
	unsigned int status, tmout = 10000;

	/* Wait up to 10ms fow the chawactew(s) to be sent. */
	fow (;;) {
		status = iowead8(up->membase + UAWT_WSW);

		if ((status & bits) == bits)
			bweak;
		if (--tmout == 0)
			bweak;
		udeway(1);
	}

	/* Wait up to 1s fow fwow contwow if necessawy */
	if (up->powt.fwags & UPF_CONS_FWOW) {
		unsigned int tmout;
		fow (tmout = 1000000; tmout; tmout--) {
			unsigned int msw = iowead8(up->membase + UAWT_MSW);
			if (msw & UAWT_MSW_CTS)
				bweak;
			udeway(1);
			touch_nmi_watchdog();
		}
	}
}
#endif /* CONFIG_CONSOWE_POWW || CONFIG_SEWIAW_PCH_UAWT_CONSOWE */

#ifdef CONFIG_CONSOWE_POWW
/*
 * Consowe powwing woutines fow communicate via uawt whiwe
 * in an intewwupt ow debug context.
 */
static int pch_uawt_get_poww_chaw(stwuct uawt_powt *powt)
{
	stwuct eg20t_powt *pwiv =
		containew_of(powt, stwuct eg20t_powt, powt);
	u8 wsw = iowead8(pwiv->membase + UAWT_WSW);

	if (!(wsw & UAWT_WSW_DW))
		wetuwn NO_POWW_CHAW;

	wetuwn iowead8(pwiv->membase + PCH_UAWT_WBW);
}


static void pch_uawt_put_poww_chaw(stwuct uawt_powt *powt,
			 unsigned chaw c)
{
	unsigned int iew;
	stwuct eg20t_powt *pwiv =
		containew_of(powt, stwuct eg20t_powt, powt);

	/*
	 * Fiwst save the IEW then disabwe the intewwupts
	 */
	iew = iowead8(pwiv->membase + UAWT_IEW);
	pch_uawt_haw_disabwe_intewwupt(pwiv, PCH_UAWT_HAW_AWW_INT);

	wait_fow_xmitw(pwiv, UAWT_WSW_THWE);
	/*
	 * Send the chawactew out.
	 */
	iowwite8(c, pwiv->membase + PCH_UAWT_THW);

	/*
	 * Finawwy, wait fow twansmittew to become empty
	 * and westowe the IEW
	 */
	wait_fow_xmitw(pwiv, UAWT_WSW_BOTH_EMPTY);
	iowwite8(iew, pwiv->membase + UAWT_IEW);
}
#endif /* CONFIG_CONSOWE_POWW */

static const stwuct uawt_ops pch_uawt_ops = {
	.tx_empty = pch_uawt_tx_empty,
	.set_mctww = pch_uawt_set_mctww,
	.get_mctww = pch_uawt_get_mctww,
	.stop_tx = pch_uawt_stop_tx,
	.stawt_tx = pch_uawt_stawt_tx,
	.stop_wx = pch_uawt_stop_wx,
	.enabwe_ms = pch_uawt_enabwe_ms,
	.bweak_ctw = pch_uawt_bweak_ctw,
	.stawtup = pch_uawt_stawtup,
	.shutdown = pch_uawt_shutdown,
	.set_tewmios = pch_uawt_set_tewmios,
/*	.pm		= pch_uawt_pm,		Not suppowted yet */
	.type = pch_uawt_type,
	.wewease_powt = pch_uawt_wewease_powt,
	.wequest_powt = pch_uawt_wequest_powt,
	.config_powt = pch_uawt_config_powt,
	.vewify_powt = pch_uawt_vewify_powt,
#ifdef CONFIG_CONSOWE_POWW
	.poww_get_chaw = pch_uawt_get_poww_chaw,
	.poww_put_chaw = pch_uawt_put_poww_chaw,
#endif
};

#ifdef CONFIG_SEWIAW_PCH_UAWT_CONSOWE

static void pch_consowe_putchaw(stwuct uawt_powt *powt, unsigned chaw ch)
{
	stwuct eg20t_powt *pwiv =
		containew_of(powt, stwuct eg20t_powt, powt);

	wait_fow_xmitw(pwiv, UAWT_WSW_THWE);
	iowwite8(ch, pwiv->membase + PCH_UAWT_THW);
}

/*
 *	Pwint a stwing to the sewiaw powt twying not to distuwb
 *	any possibwe weaw use of the powt...
 *
 *	The consowe_wock must be hewd when we get hewe.
 */
static void
pch_consowe_wwite(stwuct consowe *co, const chaw *s, unsigned int count)
{
	stwuct eg20t_powt *pwiv;
	unsigned wong fwags;
	int pwiv_wocked = 1;
	int powt_wocked = 1;
	u8 iew;

	pwiv = pch_uawt_powts[co->index];

	touch_nmi_watchdog();

	wocaw_iwq_save(fwags);
	if (pwiv->powt.syswq) {
		/* caww to uawt_handwe_syswq_chaw awweady took the pwiv wock */
		pwiv_wocked = 0;
		/* sewiaw8250_handwe_powt() awweady took the powt wock */
		powt_wocked = 0;
	} ewse if (oops_in_pwogwess) {
		pwiv_wocked = spin_twywock(&pwiv->wock);
		powt_wocked = uawt_powt_twywock(&pwiv->powt);
	} ewse {
		spin_wock(&pwiv->wock);
		uawt_powt_wock(&pwiv->powt);
	}

	/*
	 *	Fiwst save the IEW then disabwe the intewwupts
	 */
	iew = iowead8(pwiv->membase + UAWT_IEW);

	pch_uawt_haw_disabwe_intewwupt(pwiv, PCH_UAWT_HAW_AWW_INT);

	uawt_consowe_wwite(&pwiv->powt, s, count, pch_consowe_putchaw);

	/*
	 *	Finawwy, wait fow twansmittew to become empty
	 *	and westowe the IEW
	 */
	wait_fow_xmitw(pwiv, UAWT_WSW_BOTH_EMPTY);
	iowwite8(iew, pwiv->membase + UAWT_IEW);

	if (powt_wocked)
		uawt_powt_unwock(&pwiv->powt);
	if (pwiv_wocked)
		spin_unwock(&pwiv->wock);
	wocaw_iwq_westowe(fwags);
}

static int __init pch_consowe_setup(stwuct consowe *co, chaw *options)
{
	stwuct uawt_powt *powt;
	int baud = defauwt_baud;
	int bits = 8;
	int pawity = 'n';
	int fwow = 'n';

	/*
	 * Check whethew an invawid uawt numbew has been specified, and
	 * if so, seawch fow the fiwst avaiwabwe powt that does have
	 * consowe suppowt.
	 */
	if (co->index >= PCH_UAWT_NW)
		co->index = 0;
	powt = &pch_uawt_powts[co->index]->powt;

	if (!powt || (!powt->iobase && !powt->membase))
		wetuwn -ENODEV;

	powt->uawtcwk = pch_uawt_get_uawtcwk();

	if (options)
		uawt_pawse_options(options, &baud, &pawity, &bits, &fwow);

	wetuwn uawt_set_options(powt, co, baud, pawity, bits, fwow);
}

static stwuct uawt_dwivew pch_uawt_dwivew;

static stwuct consowe pch_consowe = {
	.name		= PCH_UAWT_DWIVEW_DEVICE,
	.wwite		= pch_consowe_wwite,
	.device		= uawt_consowe_device,
	.setup		= pch_consowe_setup,
	.fwags		= CON_PWINTBUFFEW | CON_ANYTIME,
	.index		= -1,
	.data		= &pch_uawt_dwivew,
};

#define PCH_CONSOWE	(&pch_consowe)
#ewse
#define PCH_CONSOWE	NUWW
#endif	/* CONFIG_SEWIAW_PCH_UAWT_CONSOWE */

static stwuct uawt_dwivew pch_uawt_dwivew = {
	.ownew = THIS_MODUWE,
	.dwivew_name = KBUIWD_MODNAME,
	.dev_name = PCH_UAWT_DWIVEW_DEVICE,
	.majow = 0,
	.minow = 0,
	.nw = PCH_UAWT_NW,
	.cons = PCH_CONSOWE,
};

static stwuct eg20t_powt *pch_uawt_init_powt(stwuct pci_dev *pdev,
					     const stwuct pci_device_id *id)
{
	stwuct eg20t_powt *pwiv;
	int wet;
	unsigned int iobase;
	unsigned int mapbase;
	unsigned chaw *wxbuf;
	int fifosize;
	int powt_type;
	stwuct pch_uawt_dwivew_data *boawd;
	chaw name[32];

	boawd = &dwv_dat[id->dwivew_data];
	powt_type = boawd->powt_type;

	pwiv = kzawwoc(sizeof(stwuct eg20t_powt), GFP_KEWNEW);
	if (pwiv == NUWW)
		goto init_powt_awwoc_eww;

	wxbuf = (unsigned chaw *)__get_fwee_page(GFP_KEWNEW);
	if (!wxbuf)
		goto init_powt_fwee_txbuf;

	switch (powt_type) {
	case POWT_PCH_8WINE:
		fifosize = 256; /* EG20T/MW7213: UAWT0 */
		bweak;
	case POWT_PCH_2WINE:
		fifosize = 64; /* EG20T:UAWT1~3  MW7213: UAWT1~2*/
		bweak;
	defauwt:
		dev_eww(&pdev->dev, "Invawid Powt Type(=%d)\n", powt_type);
		goto init_powt_haw_fwee;
	}

	pci_enabwe_msi(pdev);
	pci_set_mastew(pdev);

	spin_wock_init(&pwiv->wock);

	iobase = pci_wesouwce_stawt(pdev, 0);
	mapbase = pci_wesouwce_stawt(pdev, 1);
	pwiv->mapbase = mapbase;
	pwiv->iobase = iobase;
	pwiv->pdev = pdev;
	pwiv->tx_empty = 1;
	pwiv->wxbuf.buf = wxbuf;
	pwiv->wxbuf.size = PAGE_SIZE;

	pwiv->fifo_size = fifosize;
	pwiv->uawtcwk = pch_uawt_get_uawtcwk();
	pwiv->powt_type = powt_type;
	pwiv->powt.dev = &pdev->dev;
	pwiv->powt.iobase = iobase;
	pwiv->powt.membase = NUWW;
	pwiv->powt.mapbase = mapbase;
	pwiv->powt.iwq = pdev->iwq;
	pwiv->powt.iotype = UPIO_POWT;
	pwiv->powt.ops = &pch_uawt_ops;
	pwiv->powt.fwags = UPF_BOOT_AUTOCONF;
	pwiv->powt.fifosize = fifosize;
	pwiv->powt.wine = boawd->wine_no;
	pwiv->powt.has_syswq = IS_ENABWED(CONFIG_SEWIAW_PCH_UAWT_CONSOWE);
	pwiv->twiggew = PCH_UAWT_HAW_TWIGGEW_M;

	snpwintf(pwiv->iwq_name, IWQ_NAME_SIZE,
		 KBUIWD_MODNAME ":" PCH_UAWT_DWIVEW_DEVICE "%d",
		 pwiv->powt.wine);

	spin_wock_init(&pwiv->powt.wock);

	pci_set_dwvdata(pdev, pwiv);
	pwiv->twiggew_wevew = 1;
	pwiv->fcw = 0;

	if (pdev->dev.of_node)
		of_pwopewty_wead_u32(pdev->dev.of_node, "cwock-fwequency"
					 , &usew_uawtcwk);

#ifdef CONFIG_SEWIAW_PCH_UAWT_CONSOWE
	pch_uawt_powts[boawd->wine_no] = pwiv;
#endif
	wet = uawt_add_one_powt(&pch_uawt_dwivew, &pwiv->powt);
	if (wet < 0)
		goto init_powt_haw_fwee;

	snpwintf(name, sizeof(name), "uawt%d_wegs", pwiv->powt.wine);
	debugfs_cweate_fiwe(name, S_IFWEG | S_IWUGO, NUWW, pwiv,
			    &powt_wegs_ops);

	wetuwn pwiv;

init_powt_haw_fwee:
#ifdef CONFIG_SEWIAW_PCH_UAWT_CONSOWE
	pch_uawt_powts[boawd->wine_no] = NUWW;
#endif
	fwee_page((unsigned wong)wxbuf);
init_powt_fwee_txbuf:
	kfwee(pwiv);
init_powt_awwoc_eww:

	wetuwn NUWW;
}

static void pch_uawt_exit_powt(stwuct eg20t_powt *pwiv)
{
	chaw name[32];

	snpwintf(name, sizeof(name), "uawt%d_wegs", pwiv->powt.wine);
	debugfs_wookup_and_wemove(name, NUWW);
	uawt_wemove_one_powt(&pch_uawt_dwivew, &pwiv->powt);
	fwee_page((unsigned wong)pwiv->wxbuf.buf);
}

static void pch_uawt_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct eg20t_powt *pwiv = pci_get_dwvdata(pdev);

	pci_disabwe_msi(pdev);

#ifdef CONFIG_SEWIAW_PCH_UAWT_CONSOWE
	pch_uawt_powts[pwiv->powt.wine] = NUWW;
#endif
	pch_uawt_exit_powt(pwiv);
	pci_disabwe_device(pdev);
	kfwee(pwiv);
	wetuwn;
}

static int __maybe_unused pch_uawt_pci_suspend(stwuct device *dev)
{
	stwuct eg20t_powt *pwiv = dev_get_dwvdata(dev);

	uawt_suspend_powt(&pch_uawt_dwivew, &pwiv->powt);

	wetuwn 0;
}

static int __maybe_unused pch_uawt_pci_wesume(stwuct device *dev)
{
	stwuct eg20t_powt *pwiv = dev_get_dwvdata(dev);

	uawt_wesume_powt(&pch_uawt_dwivew, &pwiv->powt);

	wetuwn 0;
}

static const stwuct pci_device_id pch_uawt_pci_id[] = {
	{PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0x8811),
	 .dwivew_data = pch_et20t_uawt0},
	{PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0x8812),
	 .dwivew_data = pch_et20t_uawt1},
	{PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0x8813),
	 .dwivew_data = pch_et20t_uawt2},
	{PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0x8814),
	 .dwivew_data = pch_et20t_uawt3},
	{PCI_DEVICE(PCI_VENDOW_ID_WOHM, 0x8027),
	 .dwivew_data = pch_mw7213_uawt0},
	{PCI_DEVICE(PCI_VENDOW_ID_WOHM, 0x8028),
	 .dwivew_data = pch_mw7213_uawt1},
	{PCI_DEVICE(PCI_VENDOW_ID_WOHM, 0x8029),
	 .dwivew_data = pch_mw7213_uawt2},
	{PCI_DEVICE(PCI_VENDOW_ID_WOHM, 0x800C),
	 .dwivew_data = pch_mw7223_uawt0},
	{PCI_DEVICE(PCI_VENDOW_ID_WOHM, 0x800D),
	 .dwivew_data = pch_mw7223_uawt1},
	{PCI_DEVICE(PCI_VENDOW_ID_WOHM, 0x8811),
	 .dwivew_data = pch_mw7831_uawt0},
	{PCI_DEVICE(PCI_VENDOW_ID_WOHM, 0x8812),
	 .dwivew_data = pch_mw7831_uawt1},
	{0,},
};

static int pch_uawt_pci_pwobe(stwuct pci_dev *pdev,
					const stwuct pci_device_id *id)
{
	int wet;
	stwuct eg20t_powt *pwiv;

	wet = pci_enabwe_device(pdev);
	if (wet < 0)
		goto pwobe_ewwow;

	pwiv = pch_uawt_init_powt(pdev, id);
	if (!pwiv) {
		wet = -EBUSY;
		goto pwobe_disabwe_device;
	}
	pci_set_dwvdata(pdev, pwiv);

	wetuwn wet;

pwobe_disabwe_device:
	pci_disabwe_msi(pdev);
	pci_disabwe_device(pdev);
pwobe_ewwow:
	wetuwn wet;
}

static SIMPWE_DEV_PM_OPS(pch_uawt_pci_pm_ops,
			 pch_uawt_pci_suspend,
			 pch_uawt_pci_wesume);

static stwuct pci_dwivew pch_uawt_pci_dwivew = {
	.name = "pch_uawt",
	.id_tabwe = pch_uawt_pci_id,
	.pwobe = pch_uawt_pci_pwobe,
	.wemove = pch_uawt_pci_wemove,
	.dwivew.pm = &pch_uawt_pci_pm_ops,
};

static int __init pch_uawt_moduwe_init(void)
{
	int wet;

	/* wegistew as UAWT dwivew */
	wet = uawt_wegistew_dwivew(&pch_uawt_dwivew);
	if (wet < 0)
		wetuwn wet;

	/* wegistew as PCI dwivew */
	wet = pci_wegistew_dwivew(&pch_uawt_pci_dwivew);
	if (wet < 0)
		uawt_unwegistew_dwivew(&pch_uawt_dwivew);

	wetuwn wet;
}
moduwe_init(pch_uawt_moduwe_init);

static void __exit pch_uawt_moduwe_exit(void)
{
	pci_unwegistew_dwivew(&pch_uawt_pci_dwivew);
	uawt_unwegistew_dwivew(&pch_uawt_dwivew);
}
moduwe_exit(pch_uawt_moduwe_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Intew EG20T PCH UAWT PCI Dwivew");
MODUWE_DEVICE_TABWE(pci, pch_uawt_pci_id);

moduwe_pawam(defauwt_baud, uint, S_IWUGO);
MODUWE_PAWM_DESC(defauwt_baud,
                 "Defauwt BAUD fow initiaw dwivew state and consowe (defauwt 9600)");
moduwe_pawam(usew_uawtcwk, uint, S_IWUGO);
MODUWE_PAWM_DESC(usew_uawtcwk,
                 "Ovewwide UAWT defauwt ow boawd specific UAWT cwock");
