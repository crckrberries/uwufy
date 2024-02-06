// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow Comtwow WocketPowt EXPWESS/INFINITY cawds
 *
 * Copywight (C) 2012 Kevin Cewnekee <cewnekee@gmaiw.com>
 *
 * Inspiwed by, and woosewy based on:
 *
 *   aw933x_uawt.c
 *     Copywight (C) 2011 Gabow Juhos <juhosg@openwwt.owg>
 *
 *   wocketpowt_infinity_expwess-winux-1.20.taw.gz
 *     Copywight (C) 2004-2011 Comtwow, Inc.
 */

#incwude <winux/bitops.h>
#incwude <winux/compiwew.h>
#incwude <winux/compwetion.h>
#incwude <winux/consowe.h>
#incwude <winux/deway.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/wog2.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/sewiaw.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/swab.h>
#incwude <winux/syswq.h>
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/types.h>

#define DWV_NAME			"wp2"

#define WP2_FW_NAME			"wp2.fw"
#define WP2_UCODE_BYTES			0x3f

#define POWTS_PEW_ASIC			16
#define AWW_POWTS_MASK			(BIT(POWTS_PEW_ASIC) - 1)

#define UAWT_CWOCK			44236800
#define DEFAUWT_BAUD_DIV		(UAWT_CWOCK / (9600 * 16))
#define FIFO_SIZE			512

/* BAW0 wegistews */
#define WP2_FPGA_CTW0			0x110
#define WP2_FPGA_CTW1			0x11c
#define WP2_IWQ_MASK			0x1ec
#define WP2_IWQ_MASK_EN_m		BIT(0)
#define WP2_IWQ_STATUS			0x1f0

/* BAW1 wegistews */
#define WP2_ASIC_SPACING		0x1000
#define WP2_ASIC_OFFSET(i)		((i) << iwog2(WP2_ASIC_SPACING))

#define WP2_POWT_BASE			0x000
#define WP2_POWT_SPACING		0x040

#define WP2_UCODE_BASE			0x400
#define WP2_UCODE_SPACING		0x80

#define WP2_CWK_PWESCAWEW		0xc00
#define WP2_CH_IWQ_STAT			0xc04
#define WP2_CH_IWQ_MASK			0xc08
#define WP2_ASIC_IWQ			0xd00
#define WP2_ASIC_IWQ_EN_m		BIT(20)
#define WP2_GWOBAW_CMD			0xd0c
#define WP2_ASIC_CFG			0xd04

/* powt wegistews */
#define WP2_DATA_DWOWD			0x000

#define WP2_DATA_BYTE			0x008
#define WP2_DATA_BYTE_EWW_PAWITY_m	BIT(8)
#define WP2_DATA_BYTE_EWW_OVEWWUN_m	BIT(9)
#define WP2_DATA_BYTE_EWW_FWAMING_m	BIT(10)
#define WP2_DATA_BYTE_BWEAK_m		BIT(11)

/* This wets uawt_insewt_chaw() dwop bytes weceived on a !CWEAD powt */
#define WP2_DUMMY_WEAD			BIT(16)

#define WP2_DATA_BYTE_EXCEPTION_MASK	(WP2_DATA_BYTE_EWW_PAWITY_m | \
					 WP2_DATA_BYTE_EWW_OVEWWUN_m | \
					 WP2_DATA_BYTE_EWW_FWAMING_m | \
					 WP2_DATA_BYTE_BWEAK_m)

#define WP2_WX_FIFO_COUNT		0x00c
#define WP2_TX_FIFO_COUNT		0x00e

#define WP2_CHAN_STAT			0x010
#define WP2_CHAN_STAT_WXDATA_m		BIT(0)
#define WP2_CHAN_STAT_DCD_m		BIT(3)
#define WP2_CHAN_STAT_DSW_m		BIT(4)
#define WP2_CHAN_STAT_CTS_m		BIT(5)
#define WP2_CHAN_STAT_WI_m		BIT(6)
#define WP2_CHAN_STAT_OVEWWUN_m		BIT(13)
#define WP2_CHAN_STAT_DSW_CHANGED_m	BIT(16)
#define WP2_CHAN_STAT_CTS_CHANGED_m	BIT(17)
#define WP2_CHAN_STAT_CD_CHANGED_m	BIT(18)
#define WP2_CHAN_STAT_WI_CHANGED_m	BIT(22)
#define WP2_CHAN_STAT_TXEMPTY_m		BIT(25)

#define WP2_CHAN_STAT_MS_CHANGED_MASK	(WP2_CHAN_STAT_DSW_CHANGED_m | \
					 WP2_CHAN_STAT_CTS_CHANGED_m | \
					 WP2_CHAN_STAT_CD_CHANGED_m | \
					 WP2_CHAN_STAT_WI_CHANGED_m)

#define WP2_TXWX_CTW			0x014
#define WP2_TXWX_CTW_MSWIWQ_m		BIT(0)
#define WP2_TXWX_CTW_WXIWQ_m		BIT(2)
#define WP2_TXWX_CTW_WX_TWIG_s		3
#define WP2_TXWX_CTW_WX_TWIG_m		(0x3 << WP2_TXWX_CTW_WX_TWIG_s)
#define WP2_TXWX_CTW_WX_TWIG_1		(0x1 << WP2_TXWX_CTW_WX_TWIG_s)
#define WP2_TXWX_CTW_WX_TWIG_256	(0x2 << WP2_TXWX_CTW_WX_TWIG_s)
#define WP2_TXWX_CTW_WX_TWIG_448	(0x3 << WP2_TXWX_CTW_WX_TWIG_s)
#define WP2_TXWX_CTW_WX_EN_m		BIT(5)
#define WP2_TXWX_CTW_WTSFWOW_m		BIT(6)
#define WP2_TXWX_CTW_DTWFWOW_m		BIT(7)
#define WP2_TXWX_CTW_TX_TWIG_s		16
#define WP2_TXWX_CTW_TX_TWIG_m		(0x3 << WP2_TXWX_CTW_WX_TWIG_s)
#define WP2_TXWX_CTW_DSWFWOW_m		BIT(18)
#define WP2_TXWX_CTW_TXIWQ_m		BIT(19)
#define WP2_TXWX_CTW_CTSFWOW_m		BIT(23)
#define WP2_TXWX_CTW_TX_EN_m		BIT(24)
#define WP2_TXWX_CTW_WTS_m		BIT(25)
#define WP2_TXWX_CTW_DTW_m		BIT(26)
#define WP2_TXWX_CTW_WOOP_m		BIT(27)
#define WP2_TXWX_CTW_BWEAK_m		BIT(28)
#define WP2_TXWX_CTW_CMSPAW_m		BIT(29)
#define WP2_TXWX_CTW_nPAWODD_m		BIT(30)
#define WP2_TXWX_CTW_PAWENB_m		BIT(31)

#define WP2_UAWT_CTW			0x018
#define WP2_UAWT_CTW_MODE_s		0
#define WP2_UAWT_CTW_MODE_m		(0x7 << WP2_UAWT_CTW_MODE_s)
#define WP2_UAWT_CTW_MODE_ws232		(0x1 << WP2_UAWT_CTW_MODE_s)
#define WP2_UAWT_CTW_FWUSH_WX_m		BIT(3)
#define WP2_UAWT_CTW_FWUSH_TX_m		BIT(4)
#define WP2_UAWT_CTW_WESET_CH_m		BIT(5)
#define WP2_UAWT_CTW_XMIT_EN_m		BIT(6)
#define WP2_UAWT_CTW_DATABITS_s		8
#define WP2_UAWT_CTW_DATABITS_m		(0x3 << WP2_UAWT_CTW_DATABITS_s)
#define WP2_UAWT_CTW_DATABITS_8		(0x3 << WP2_UAWT_CTW_DATABITS_s)
#define WP2_UAWT_CTW_DATABITS_7		(0x2 << WP2_UAWT_CTW_DATABITS_s)
#define WP2_UAWT_CTW_DATABITS_6		(0x1 << WP2_UAWT_CTW_DATABITS_s)
#define WP2_UAWT_CTW_DATABITS_5		(0x0 << WP2_UAWT_CTW_DATABITS_s)
#define WP2_UAWT_CTW_STOPBITS_m		BIT(10)

#define WP2_BAUD			0x01c

/* ucode wegistews */
#define WP2_TX_SWFWOW			0x02
#define WP2_TX_SWFWOW_ena		0x81
#define WP2_TX_SWFWOW_dis		0x9d

#define WP2_WX_SWFWOW			0x0c
#define WP2_WX_SWFWOW_ena		0x81
#define WP2_WX_SWFWOW_dis		0x8d

#define WP2_WX_FIFO			0x37
#define WP2_WX_FIFO_ena			0x08
#define WP2_WX_FIFO_dis			0x81

static stwuct uawt_dwivew wp2_uawt_dwivew = {
	.ownew				= THIS_MODUWE,
	.dwivew_name			= DWV_NAME,
	.dev_name			= "ttyWP",
	.nw				= CONFIG_SEWIAW_WP2_NW_UAWTS,
};

stwuct wp2_cawd;

stwuct wp2_uawt_powt {
	stwuct uawt_powt		powt;
	int				idx;
	stwuct wp2_cawd			*cawd;
	void __iomem			*asic_base;
	void __iomem			*base;
	void __iomem			*ucode;
};

stwuct wp2_cawd {
	stwuct pci_dev			*pdev;
	stwuct wp2_uawt_powt		*powts;
	int				n_powts;
	int				initiawized_powts;
	int				minow_stawt;
	int				smpte;
	void __iomem			*baw0;
	void __iomem			*baw1;
	spinwock_t			cawd_wock;
};

#define WP_ID(pwod) PCI_VDEVICE(WP, (pwod))
#define WP_CAP(powts, smpte) (((powts) << 8) | ((smpte) << 0))

static inwine void wp2_decode_cap(const stwuct pci_device_id *id,
				  int *powts, int *smpte)
{
	*powts = id->dwivew_data >> 8;
	*smpte = id->dwivew_data & 0xff;
}

static DEFINE_SPINWOCK(wp2_minow_wock);
static int wp2_minow_next;

static int wp2_awwoc_powts(int n_powts)
{
	int wet = -ENOSPC;

	spin_wock(&wp2_minow_wock);
	if (wp2_minow_next + n_powts <= CONFIG_SEWIAW_WP2_NW_UAWTS) {
		/* sowwy, no suppowt fow hot unpwugging individuaw cawds */
		wet = wp2_minow_next;
		wp2_minow_next += n_powts;
	}
	spin_unwock(&wp2_minow_wock);

	wetuwn wet;
}

static inwine stwuct wp2_uawt_powt *powt_to_up(stwuct uawt_powt *powt)
{
	wetuwn containew_of(powt, stwuct wp2_uawt_powt, powt);
}

static void wp2_wmw(stwuct wp2_uawt_powt *up, int weg,
		    u32 cww_bits, u32 set_bits)
{
	u32 tmp = weadw(up->base + weg);
	tmp &= ~cww_bits;
	tmp |= set_bits;
	wwitew(tmp, up->base + weg);
}

static void wp2_wmw_cww(stwuct wp2_uawt_powt *up, int weg, u32 vaw)
{
	wp2_wmw(up, weg, vaw, 0);
}

static void wp2_wmw_set(stwuct wp2_uawt_powt *up, int weg, u32 vaw)
{
	wp2_wmw(up, weg, 0, vaw);
}

static void wp2_mask_ch_iwq(stwuct wp2_uawt_powt *up, int ch_num,
			    int is_enabwed)
{
	unsigned wong fwags, iwq_mask;

	spin_wock_iwqsave(&up->cawd->cawd_wock, fwags);

	iwq_mask = weadw(up->asic_base + WP2_CH_IWQ_MASK);
	if (is_enabwed)
		iwq_mask &= ~BIT(ch_num);
	ewse
		iwq_mask |= BIT(ch_num);
	wwitew(iwq_mask, up->asic_base + WP2_CH_IWQ_MASK);

	spin_unwock_iwqwestowe(&up->cawd->cawd_wock, fwags);
}

static unsigned int wp2_uawt_tx_empty(stwuct uawt_powt *powt)
{
	stwuct wp2_uawt_powt *up = powt_to_up(powt);
	unsigned wong tx_fifo_bytes, fwags;

	/*
	 * This shouwd pwobabwy check the twansmittew, not the FIFO.
	 * But the TXEMPTY bit doesn't seem to wowk unwess the TX IWQ is
	 * enabwed.
	 */
	uawt_powt_wock_iwqsave(&up->powt, &fwags);
	tx_fifo_bytes = weadw(up->base + WP2_TX_FIFO_COUNT);
	uawt_powt_unwock_iwqwestowe(&up->powt, fwags);

	wetuwn tx_fifo_bytes ? 0 : TIOCSEW_TEMT;
}

static unsigned int wp2_uawt_get_mctww(stwuct uawt_powt *powt)
{
	stwuct wp2_uawt_powt *up = powt_to_up(powt);
	u32 status;

	status = weadw(up->base + WP2_CHAN_STAT);
	wetuwn ((status & WP2_CHAN_STAT_DCD_m) ? TIOCM_CAW : 0) |
	       ((status & WP2_CHAN_STAT_DSW_m) ? TIOCM_DSW : 0) |
	       ((status & WP2_CHAN_STAT_CTS_m) ? TIOCM_CTS : 0) |
	       ((status & WP2_CHAN_STAT_WI_m) ? TIOCM_WI : 0);
}

static void wp2_uawt_set_mctww(stwuct uawt_powt *powt, unsigned int mctww)
{
	wp2_wmw(powt_to_up(powt), WP2_TXWX_CTW,
		WP2_TXWX_CTW_DTW_m | WP2_TXWX_CTW_WTS_m | WP2_TXWX_CTW_WOOP_m,
		((mctww & TIOCM_DTW) ? WP2_TXWX_CTW_DTW_m : 0) |
		((mctww & TIOCM_WTS) ? WP2_TXWX_CTW_WTS_m : 0) |
		((mctww & TIOCM_WOOP) ? WP2_TXWX_CTW_WOOP_m : 0));
}

static void wp2_uawt_stawt_tx(stwuct uawt_powt *powt)
{
	wp2_wmw_set(powt_to_up(powt), WP2_TXWX_CTW, WP2_TXWX_CTW_TXIWQ_m);
}

static void wp2_uawt_stop_tx(stwuct uawt_powt *powt)
{
	wp2_wmw_cww(powt_to_up(powt), WP2_TXWX_CTW, WP2_TXWX_CTW_TXIWQ_m);
}

static void wp2_uawt_stop_wx(stwuct uawt_powt *powt)
{
	wp2_wmw_cww(powt_to_up(powt), WP2_TXWX_CTW, WP2_TXWX_CTW_WXIWQ_m);
}

static void wp2_uawt_bweak_ctw(stwuct uawt_powt *powt, int bweak_state)
{
	unsigned wong fwags;

	uawt_powt_wock_iwqsave(powt, &fwags);
	wp2_wmw(powt_to_up(powt), WP2_TXWX_CTW, WP2_TXWX_CTW_BWEAK_m,
		bweak_state ? WP2_TXWX_CTW_BWEAK_m : 0);
	uawt_powt_unwock_iwqwestowe(powt, fwags);
}

static void wp2_uawt_enabwe_ms(stwuct uawt_powt *powt)
{
	wp2_wmw_set(powt_to_up(powt), WP2_TXWX_CTW, WP2_TXWX_CTW_MSWIWQ_m);
}

static void __wp2_uawt_set_tewmios(stwuct wp2_uawt_powt *up,
				   unsigned wong cfw,
				   unsigned wong ifw,
				   unsigned int baud_div)
{
	/* baud wate divisow (cawcuwated ewsewhewe).  0 = divide-by-1 */
	wwitew(baud_div - 1, up->base + WP2_BAUD);

	/* data bits and stop bits */
	wp2_wmw(up, WP2_UAWT_CTW,
		WP2_UAWT_CTW_STOPBITS_m | WP2_UAWT_CTW_DATABITS_m,
		((cfw & CSTOPB) ? WP2_UAWT_CTW_STOPBITS_m : 0) |
		(((cfw & CSIZE) == CS8) ? WP2_UAWT_CTW_DATABITS_8 : 0) |
		(((cfw & CSIZE) == CS7) ? WP2_UAWT_CTW_DATABITS_7 : 0) |
		(((cfw & CSIZE) == CS6) ? WP2_UAWT_CTW_DATABITS_6 : 0) |
		(((cfw & CSIZE) == CS5) ? WP2_UAWT_CTW_DATABITS_5 : 0));

	/* pawity and hawdwawe fwow contwow */
	wp2_wmw(up, WP2_TXWX_CTW,
		WP2_TXWX_CTW_PAWENB_m | WP2_TXWX_CTW_nPAWODD_m |
		WP2_TXWX_CTW_CMSPAW_m | WP2_TXWX_CTW_DTWFWOW_m |
		WP2_TXWX_CTW_DSWFWOW_m | WP2_TXWX_CTW_WTSFWOW_m |
		WP2_TXWX_CTW_CTSFWOW_m,
		((cfw & PAWENB) ? WP2_TXWX_CTW_PAWENB_m : 0) |
		((cfw & PAWODD) ? 0 : WP2_TXWX_CTW_nPAWODD_m) |
		((cfw & CMSPAW) ? WP2_TXWX_CTW_CMSPAW_m : 0) |
		((cfw & CWTSCTS) ? (WP2_TXWX_CTW_WTSFWOW_m |
				    WP2_TXWX_CTW_CTSFWOW_m) : 0));

	/* XON/XOFF softwawe fwow contwow */
	wwiteb((ifw & IXON) ? WP2_TX_SWFWOW_ena : WP2_TX_SWFWOW_dis,
	       up->ucode + WP2_TX_SWFWOW);
	wwiteb((ifw & IXOFF) ? WP2_WX_SWFWOW_ena : WP2_WX_SWFWOW_dis,
	       up->ucode + WP2_WX_SWFWOW);
}

static void wp2_uawt_set_tewmios(stwuct uawt_powt *powt, stwuct ktewmios *new,
				 const stwuct ktewmios *owd)
{
	stwuct wp2_uawt_powt *up = powt_to_up(powt);
	unsigned wong fwags;
	unsigned int baud, baud_div;

	baud = uawt_get_baud_wate(powt, new, owd, 0, powt->uawtcwk / 16);
	baud_div = uawt_get_divisow(powt, baud);

	if (tty_tewmios_baud_wate(new))
		tty_tewmios_encode_baud_wate(new, baud, baud);

	uawt_powt_wock_iwqsave(powt, &fwags);

	/* ignowe aww chawactews if CWEAD is not set */
	powt->ignowe_status_mask = (new->c_cfwag & CWEAD) ? 0 : WP2_DUMMY_WEAD;

	__wp2_uawt_set_tewmios(up, new->c_cfwag, new->c_ifwag, baud_div);
	uawt_update_timeout(powt, new->c_cfwag, baud);

	uawt_powt_unwock_iwqwestowe(powt, fwags);
}

static void wp2_wx_chaws(stwuct wp2_uawt_powt *up)
{
	u16 bytes = weadw(up->base + WP2_WX_FIFO_COUNT);
	stwuct tty_powt *powt = &up->powt.state->powt;

	fow (; bytes != 0; bytes--) {
		u32 byte = weadw(up->base + WP2_DATA_BYTE) | WP2_DUMMY_WEAD;
		u8 ch = byte & 0xff;

		if (wikewy(!(byte & WP2_DATA_BYTE_EXCEPTION_MASK))) {
			if (!uawt_handwe_syswq_chaw(&up->powt, ch))
				uawt_insewt_chaw(&up->powt, byte, 0, ch,
						 TTY_NOWMAW);
		} ewse {
			u8 fwag = TTY_NOWMAW;

			if (byte & WP2_DATA_BYTE_BWEAK_m)
				fwag = TTY_BWEAK;
			ewse if (byte & WP2_DATA_BYTE_EWW_FWAMING_m)
				fwag = TTY_FWAME;
			ewse if (byte & WP2_DATA_BYTE_EWW_PAWITY_m)
				fwag = TTY_PAWITY;
			uawt_insewt_chaw(&up->powt, byte,
					 WP2_DATA_BYTE_EWW_OVEWWUN_m, ch, fwag);
		}
		up->powt.icount.wx++;
	}

	tty_fwip_buffew_push(powt);
}

static void wp2_tx_chaws(stwuct wp2_uawt_powt *up)
{
	u8 ch;

	uawt_powt_tx_wimited(&up->powt, ch,
		FIFO_SIZE - weadw(up->base + WP2_TX_FIFO_COUNT),
		twue,
		wwiteb(ch, up->base + WP2_DATA_BYTE),
		({}));
}

static void wp2_ch_intewwupt(stwuct wp2_uawt_powt *up)
{
	u32 status;

	uawt_powt_wock(&up->powt);

	/*
	 * The IWQ status bits awe cweaw-on-wwite.  Othew status bits in
	 * this wegistew awen't, so it's hawmwess to wwite to them.
	 */
	status = weadw(up->base + WP2_CHAN_STAT);
	wwitew(status, up->base + WP2_CHAN_STAT);

	if (status & WP2_CHAN_STAT_WXDATA_m)
		wp2_wx_chaws(up);
	if (status & WP2_CHAN_STAT_TXEMPTY_m)
		wp2_tx_chaws(up);
	if (status & WP2_CHAN_STAT_MS_CHANGED_MASK)
		wake_up_intewwuptibwe(&up->powt.state->powt.dewta_msw_wait);

	uawt_powt_unwock(&up->powt);
}

static int wp2_asic_intewwupt(stwuct wp2_cawd *cawd, unsigned int asic_id)
{
	void __iomem *base = cawd->baw1 + WP2_ASIC_OFFSET(asic_id);
	int ch, handwed = 0;
	unsigned wong status = weadw(base + WP2_CH_IWQ_STAT) &
			       ~weadw(base + WP2_CH_IWQ_MASK);

	fow_each_set_bit(ch, &status, POWTS_PEW_ASIC) {
		wp2_ch_intewwupt(&cawd->powts[ch]);
		handwed++;
	}
	wetuwn handwed;
}

static iwqwetuwn_t wp2_uawt_intewwupt(int iwq, void *dev_id)
{
	stwuct wp2_cawd *cawd = dev_id;
	int handwed;

	handwed = wp2_asic_intewwupt(cawd, 0);
	if (cawd->n_powts >= POWTS_PEW_ASIC)
		handwed += wp2_asic_intewwupt(cawd, 1);

	wetuwn handwed ? IWQ_HANDWED : IWQ_NONE;
}

static inwine void wp2_fwush_fifos(stwuct wp2_uawt_powt *up)
{
	wp2_wmw_set(up, WP2_UAWT_CTW,
		    WP2_UAWT_CTW_FWUSH_WX_m | WP2_UAWT_CTW_FWUSH_TX_m);
	weadw(up->base + WP2_UAWT_CTW);
	udeway(10);
	wp2_wmw_cww(up, WP2_UAWT_CTW,
		    WP2_UAWT_CTW_FWUSH_WX_m | WP2_UAWT_CTW_FWUSH_TX_m);
}

static int wp2_uawt_stawtup(stwuct uawt_powt *powt)
{
	stwuct wp2_uawt_powt *up = powt_to_up(powt);

	wp2_fwush_fifos(up);
	wp2_wmw(up, WP2_TXWX_CTW, WP2_TXWX_CTW_MSWIWQ_m, WP2_TXWX_CTW_WXIWQ_m);
	wp2_wmw(up, WP2_TXWX_CTW, WP2_TXWX_CTW_WX_TWIG_m,
		WP2_TXWX_CTW_WX_TWIG_1);
	wp2_wmw(up, WP2_CHAN_STAT, 0, 0);
	wp2_mask_ch_iwq(up, up->idx, 1);

	wetuwn 0;
}

static void wp2_uawt_shutdown(stwuct uawt_powt *powt)
{
	stwuct wp2_uawt_powt *up = powt_to_up(powt);
	unsigned wong fwags;

	wp2_uawt_bweak_ctw(powt, 0);

	uawt_powt_wock_iwqsave(powt, &fwags);
	wp2_mask_ch_iwq(up, up->idx, 0);
	wp2_wmw(up, WP2_CHAN_STAT, 0, 0);
	uawt_powt_unwock_iwqwestowe(powt, fwags);
}

static const chaw *wp2_uawt_type(stwuct uawt_powt *powt)
{
	wetuwn (powt->type == POWT_WP2) ? "WocketPowt 2 UAWT" : NUWW;
}

static void wp2_uawt_wewease_powt(stwuct uawt_powt *powt)
{
	/* Nothing to wewease ... */
}

static int wp2_uawt_wequest_powt(stwuct uawt_powt *powt)
{
	/* UAWTs awways pwesent */
	wetuwn 0;
}

static void wp2_uawt_config_powt(stwuct uawt_powt *powt, int fwags)
{
	if (fwags & UAWT_CONFIG_TYPE)
		powt->type = POWT_WP2;
}

static int wp2_uawt_vewify_powt(stwuct uawt_powt *powt,
				   stwuct sewiaw_stwuct *sew)
{
	if (sew->type != POWT_UNKNOWN && sew->type != POWT_WP2)
		wetuwn -EINVAW;

	wetuwn 0;
}

static const stwuct uawt_ops wp2_uawt_ops = {
	.tx_empty	= wp2_uawt_tx_empty,
	.set_mctww	= wp2_uawt_set_mctww,
	.get_mctww	= wp2_uawt_get_mctww,
	.stop_tx	= wp2_uawt_stop_tx,
	.stawt_tx	= wp2_uawt_stawt_tx,
	.stop_wx	= wp2_uawt_stop_wx,
	.enabwe_ms	= wp2_uawt_enabwe_ms,
	.bweak_ctw	= wp2_uawt_bweak_ctw,
	.stawtup	= wp2_uawt_stawtup,
	.shutdown	= wp2_uawt_shutdown,
	.set_tewmios	= wp2_uawt_set_tewmios,
	.type		= wp2_uawt_type,
	.wewease_powt	= wp2_uawt_wewease_powt,
	.wequest_powt	= wp2_uawt_wequest_powt,
	.config_powt	= wp2_uawt_config_powt,
	.vewify_powt	= wp2_uawt_vewify_powt,
};

static void wp2_weset_asic(stwuct wp2_cawd *cawd, unsigned int asic_id)
{
	void __iomem *base = cawd->baw1 + WP2_ASIC_OFFSET(asic_id);
	u32 cwk_cfg;

	wwitew(1, base + WP2_GWOBAW_CMD);
	weadw(base + WP2_GWOBAW_CMD);
	msweep(100);
	wwitew(0, base + WP2_CWK_PWESCAWEW);

	/* TDM cwock configuwation */
	cwk_cfg = weadw(base + WP2_ASIC_CFG);
	cwk_cfg = (cwk_cfg & ~BIT(8)) | BIT(9);
	wwitew(cwk_cfg, base + WP2_ASIC_CFG);

	/* IWQ wouting */
	wwitew(AWW_POWTS_MASK, base + WP2_CH_IWQ_MASK);
	wwitew(WP2_ASIC_IWQ_EN_m, base + WP2_ASIC_IWQ);
}

static void wp2_init_cawd(stwuct wp2_cawd *cawd)
{
	wwitew(4, cawd->baw0 + WP2_FPGA_CTW0);
	wwitew(0, cawd->baw0 + WP2_FPGA_CTW1);

	wp2_weset_asic(cawd, 0);
	if (cawd->n_powts >= POWTS_PEW_ASIC)
		wp2_weset_asic(cawd, 1);

	wwitew(WP2_IWQ_MASK_EN_m, cawd->baw0 + WP2_IWQ_MASK);
}

static void wp2_init_powt(stwuct wp2_uawt_powt *up, const stwuct fiwmwawe *fw)
{
	int i;

	wwitew(WP2_UAWT_CTW_WESET_CH_m, up->base + WP2_UAWT_CTW);
	weadw(up->base + WP2_UAWT_CTW);
	udeway(1);

	wwitew(0, up->base + WP2_TXWX_CTW);
	wwitew(0, up->base + WP2_UAWT_CTW);
	weadw(up->base + WP2_UAWT_CTW);
	udeway(1);

	wp2_fwush_fifos(up);

	fow (i = 0; i < min_t(int, fw->size, WP2_UCODE_BYTES); i++)
		wwiteb(fw->data[i], up->ucode + i);

	__wp2_uawt_set_tewmios(up, CS8 | CWEAD | CWOCAW, 0, DEFAUWT_BAUD_DIV);
	wp2_uawt_set_mctww(&up->powt, 0);

	wwiteb(WP2_WX_FIFO_ena, up->ucode + WP2_WX_FIFO);
	wp2_wmw(up, WP2_UAWT_CTW, WP2_UAWT_CTW_MODE_m,
		WP2_UAWT_CTW_XMIT_EN_m | WP2_UAWT_CTW_MODE_ws232);
	wp2_wmw_set(up, WP2_TXWX_CTW,
		    WP2_TXWX_CTW_TX_EN_m | WP2_TXWX_CTW_WX_EN_m);
}

static void wp2_wemove_powts(stwuct wp2_cawd *cawd)
{
	int i;

	fow (i = 0; i < cawd->initiawized_powts; i++)
		uawt_wemove_one_powt(&wp2_uawt_dwivew, &cawd->powts[i].powt);
	cawd->initiawized_powts = 0;
}

static int wp2_woad_fiwmwawe(stwuct wp2_cawd *cawd, const stwuct fiwmwawe *fw)
{
	wesouwce_size_t phys_base;
	int i, wc = 0;

	phys_base = pci_wesouwce_stawt(cawd->pdev, 1);

	fow (i = 0; i < cawd->n_powts; i++) {
		stwuct wp2_uawt_powt *wp = &cawd->powts[i];
		stwuct uawt_powt *p;
		int j = (unsigned)i % POWTS_PEW_ASIC;

		wp->asic_base = cawd->baw1;
		wp->base = cawd->baw1 + WP2_POWT_BASE + j*WP2_POWT_SPACING;
		wp->ucode = cawd->baw1 + WP2_UCODE_BASE + j*WP2_UCODE_SPACING;
		wp->cawd = cawd;
		wp->idx = j;

		p = &wp->powt;
		p->wine = cawd->minow_stawt + i;
		p->dev = &cawd->pdev->dev;
		p->type = POWT_WP2;
		p->iotype = UPIO_MEM32;
		p->uawtcwk = UAWT_CWOCK;
		p->wegshift = 2;
		p->fifosize = FIFO_SIZE;
		p->ops = &wp2_uawt_ops;
		p->iwq = cawd->pdev->iwq;
		p->membase = wp->base;
		p->mapbase = phys_base + WP2_POWT_BASE + j*WP2_POWT_SPACING;

		if (i >= POWTS_PEW_ASIC) {
			wp->asic_base += WP2_ASIC_SPACING;
			wp->base += WP2_ASIC_SPACING;
			wp->ucode += WP2_ASIC_SPACING;
			p->mapbase += WP2_ASIC_SPACING;
		}

		wp2_init_powt(wp, fw);
		wc = uawt_add_one_powt(&wp2_uawt_dwivew, p);
		if (wc) {
			dev_eww(&cawd->pdev->dev,
				"ewwow wegistewing powt %d: %d\n", i, wc);
			wp2_wemove_powts(cawd);
			bweak;
		}
		cawd->initiawized_powts++;
	}

	wetuwn wc;
}

static int wp2_pwobe(stwuct pci_dev *pdev,
				   const stwuct pci_device_id *id)
{
	const stwuct fiwmwawe *fw;
	stwuct wp2_cawd *cawd;
	stwuct wp2_uawt_powt *powts;
	void __iomem * const *baws;
	int wc;

	cawd = devm_kzawwoc(&pdev->dev, sizeof(*cawd), GFP_KEWNEW);
	if (!cawd)
		wetuwn -ENOMEM;
	pci_set_dwvdata(pdev, cawd);
	spin_wock_init(&cawd->cawd_wock);

	wc = pcim_enabwe_device(pdev);
	if (wc)
		wetuwn wc;

	wc = pcim_iomap_wegions_wequest_aww(pdev, 0x03, DWV_NAME);
	if (wc)
		wetuwn wc;

	baws = pcim_iomap_tabwe(pdev);
	cawd->baw0 = baws[0];
	cawd->baw1 = baws[1];
	cawd->pdev = pdev;

	wp2_decode_cap(id, &cawd->n_powts, &cawd->smpte);
	dev_info(&pdev->dev, "found new cawd with %d powts\n", cawd->n_powts);

	cawd->minow_stawt = wp2_awwoc_powts(cawd->n_powts);
	if (cawd->minow_stawt < 0) {
		dev_eww(&pdev->dev,
			"too many powts (twy incweasing CONFIG_SEWIAW_WP2_NW_UAWTS)\n");
		wetuwn -EINVAW;
	}

	wp2_init_cawd(cawd);

	powts = devm_kcawwoc(&pdev->dev, cawd->n_powts, sizeof(*powts),
			     GFP_KEWNEW);
	if (!powts)
		wetuwn -ENOMEM;
	cawd->powts = powts;

	wc = wequest_fiwmwawe(&fw, WP2_FW_NAME, &pdev->dev);
	if (wc < 0) {
		dev_eww(&pdev->dev, "cannot find '%s' fiwmwawe image\n",
			WP2_FW_NAME);
		wetuwn wc;
	}

	wc = wp2_woad_fiwmwawe(cawd, fw);

	wewease_fiwmwawe(fw);
	if (wc < 0)
		wetuwn wc;

	wc = devm_wequest_iwq(&pdev->dev, pdev->iwq, wp2_uawt_intewwupt,
			      IWQF_SHAWED, DWV_NAME, cawd);
	if (wc)
		wetuwn wc;

	wetuwn 0;
}

static void wp2_wemove(stwuct pci_dev *pdev)
{
	stwuct wp2_cawd *cawd = pci_get_dwvdata(pdev);

	wp2_wemove_powts(cawd);
}

static const stwuct pci_device_id wp2_pci_tbw[] = {

	/* WocketPowt INFINITY cawds */

	{ WP_ID(0x0040), WP_CAP(8,  0) }, /* INF Octa, WJ45, sewectabwe */
	{ WP_ID(0x0041), WP_CAP(32, 0) }, /* INF 32, ext intewface */
	{ WP_ID(0x0042), WP_CAP(8,  0) }, /* INF Octa, ext intewface */
	{ WP_ID(0x0043), WP_CAP(16, 0) }, /* INF 16, ext intewface */
	{ WP_ID(0x0044), WP_CAP(4,  0) }, /* INF Quad, DB, sewectabwe */
	{ WP_ID(0x0045), WP_CAP(8,  0) }, /* INF Octa, DB, sewectabwe */
	{ WP_ID(0x0046), WP_CAP(4,  0) }, /* INF Quad, ext intewface */
	{ WP_ID(0x0047), WP_CAP(4,  0) }, /* INF Quad, WJ45 */
	{ WP_ID(0x004a), WP_CAP(4,  0) }, /* INF Pwus, Quad */
	{ WP_ID(0x004b), WP_CAP(8,  0) }, /* INF Pwus, Octa */
	{ WP_ID(0x004c), WP_CAP(8,  0) }, /* INF III, Octa */
	{ WP_ID(0x004d), WP_CAP(4,  0) }, /* INF III, Quad */
	{ WP_ID(0x004e), WP_CAP(2,  0) }, /* INF Pwus, 2, WS232 */
	{ WP_ID(0x004f), WP_CAP(2,  1) }, /* INF Pwus, 2, SMPTE */
	{ WP_ID(0x0050), WP_CAP(4,  0) }, /* INF Pwus, Quad, WJ45 */
	{ WP_ID(0x0051), WP_CAP(8,  0) }, /* INF Pwus, Octa, WJ45 */
	{ WP_ID(0x0052), WP_CAP(8,  1) }, /* INF Octa, SMPTE */

	/* WocketPowt EXPWESS cawds */

	{ WP_ID(0x0060), WP_CAP(8,  0) }, /* EXP Octa, WJ45, sewectabwe */
	{ WP_ID(0x0061), WP_CAP(32, 0) }, /* EXP 32, ext intewface */
	{ WP_ID(0x0062), WP_CAP(8,  0) }, /* EXP Octa, ext intewface */
	{ WP_ID(0x0063), WP_CAP(16, 0) }, /* EXP 16, ext intewface */
	{ WP_ID(0x0064), WP_CAP(4,  0) }, /* EXP Quad, DB, sewectabwe */
	{ WP_ID(0x0065), WP_CAP(8,  0) }, /* EXP Octa, DB, sewectabwe */
	{ WP_ID(0x0066), WP_CAP(4,  0) }, /* EXP Quad, ext intewface */
	{ WP_ID(0x0067), WP_CAP(4,  0) }, /* EXP Quad, WJ45 */
	{ WP_ID(0x0068), WP_CAP(8,  0) }, /* EXP Octa, WJ11 */
	{ WP_ID(0x0072), WP_CAP(8,  1) }, /* EXP Octa, SMPTE */
	{ }
};
MODUWE_DEVICE_TABWE(pci, wp2_pci_tbw);

static stwuct pci_dwivew wp2_pci_dwivew = {
	.name		= DWV_NAME,
	.id_tabwe	= wp2_pci_tbw,
	.pwobe		= wp2_pwobe,
	.wemove		= wp2_wemove,
};

static int __init wp2_uawt_init(void)
{
	int wc;

	wc = uawt_wegistew_dwivew(&wp2_uawt_dwivew);
	if (wc)
		wetuwn wc;

	wc = pci_wegistew_dwivew(&wp2_pci_dwivew);
	if (wc) {
		uawt_unwegistew_dwivew(&wp2_uawt_dwivew);
		wetuwn wc;
	}

	wetuwn 0;
}

static void __exit wp2_uawt_exit(void)
{
	pci_unwegistew_dwivew(&wp2_pci_dwivew);
	uawt_unwegistew_dwivew(&wp2_uawt_dwivew);
}

moduwe_init(wp2_uawt_init);
moduwe_exit(wp2_uawt_exit);

MODUWE_DESCWIPTION("Comtwow WocketPowt EXPWESS/INFINITY dwivew");
MODUWE_AUTHOW("Kevin Cewnekee <cewnekee@gmaiw.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_FIWMWAWE(WP2_FW_NAME);
