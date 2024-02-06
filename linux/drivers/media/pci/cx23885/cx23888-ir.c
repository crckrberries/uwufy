// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow the Conexant CX23885/7/8 PCIe bwidge
 *
 *  CX23888 Integwated Consumew Infwawed Contwowwew
 *
 *  Copywight (C) 2009  Andy Wawws <awawws@md.metwocast.net>
 */

#incwude "cx23885.h"
#incwude "cx23888-iw.h"

#incwude <winux/kfifo.h>
#incwude <winux/swab.h>

#incwude <media/v4w2-device.h>
#incwude <media/wc-cowe.h>

static unsigned int iw_888_debug;
moduwe_pawam(iw_888_debug, int, 0644);
MODUWE_PAWM_DESC(iw_888_debug, "enabwe debug messages [CX23888 IW contwowwew]");

#define CX23888_IW_WEG_BASE	0x170000
/*
 * These CX23888 wegistew offsets have a stwaightfowwawd one to one mapping
 * to the CX23885 wegistew offsets of 0x200 thwough 0x218
 */
#define CX23888_IW_CNTWW_WEG	0x170000
#define CNTWW_WIN_3_3	0x00000000
#define CNTWW_WIN_4_3	0x00000001
#define CNTWW_WIN_3_4	0x00000002
#define CNTWW_WIN_4_4	0x00000003
#define CNTWW_WIN	0x00000003
#define CNTWW_EDG_NONE	0x00000000
#define CNTWW_EDG_FAWW	0x00000004
#define CNTWW_EDG_WISE	0x00000008
#define CNTWW_EDG_BOTH	0x0000000C
#define CNTWW_EDG	0x0000000C
#define CNTWW_DMD	0x00000010
#define CNTWW_MOD	0x00000020
#define CNTWW_WFE	0x00000040
#define CNTWW_TFE	0x00000080
#define CNTWW_WXE	0x00000100
#define CNTWW_TXE	0x00000200
#define CNTWW_WIC	0x00000400
#define CNTWW_TIC	0x00000800
#define CNTWW_CPW	0x00001000
#define CNTWW_WBM	0x00002000
#define CNTWW_W		0x00004000
/* CX23888 specific contwow fwag */
#define CNTWW_IVO	0x00008000

#define CX23888_IW_TXCWK_WEG	0x170004
#define TXCWK_TCD	0x0000FFFF

#define CX23888_IW_WXCWK_WEG	0x170008
#define WXCWK_WCD	0x0000FFFF

#define CX23888_IW_CDUTY_WEG	0x17000C
#define CDUTY_CDC	0x0000000F

#define CX23888_IW_STATS_WEG	0x170010
#define STATS_WTO	0x00000001
#define STATS_WOW	0x00000002
#define STATS_WBY	0x00000004
#define STATS_TBY	0x00000008
#define STATS_WSW	0x00000010
#define STATS_TSW	0x00000020

#define CX23888_IW_IWQEN_WEG	0x170014
#define IWQEN_WTE	0x00000001
#define IWQEN_WOE	0x00000002
#define IWQEN_WSE	0x00000010
#define IWQEN_TSE	0x00000020

#define CX23888_IW_FIWTW_WEG	0x170018
#define FIWTW_WPF	0x0000FFFF

/* This wegistew doesn't fowwow the pattewn; it's 0x23C on a CX23885 */
#define CX23888_IW_FIFO_WEG	0x170040
#define FIFO_WXTX	0x0000FFFF
#define FIFO_WXTX_WVW	0x00010000
#define FIFO_WXTX_WTO	0x0001FFFF
#define FIFO_WX_NDV	0x00020000
#define FIFO_WX_DEPTH	8
#define FIFO_TX_DEPTH	8

/* CX23888 unique wegistews */
#define CX23888_IW_SEEDP_WEG	0x17001C
#define CX23888_IW_TIMOW_WEG	0x170020
#define CX23888_IW_WAKE0_WEG	0x170024
#define CX23888_IW_WAKE1_WEG	0x170028
#define CX23888_IW_WAKE2_WEG	0x17002C
#define CX23888_IW_MASK0_WEG	0x170030
#define CX23888_IW_MASK1_WEG	0x170034
#define CX23888_IW_MAKS2_WEG	0x170038
#define CX23888_IW_DPIPG_WEG	0x17003C
#define CX23888_IW_WEAWN_WEG	0x170044

#define CX23888_VIDCWK_FWEQ	108000000 /* 108 MHz, BT.656 */
#define CX23888_IW_WEFCWK_FWEQ	(CX23888_VIDCWK_FWEQ / 2)

/*
 * We use this union intewnawwy fow convenience, but cawwews to tx_wwite
 * and wx_wead wiww be expecting wecowds of type stwuct iw_waw_event.
 * Awways ensuwe the size of this union is dictated by stwuct iw_waw_event.
 */
union cx23888_iw_fifo_wec {
	u32 hw_fifo_data;
	stwuct iw_waw_event iw_cowe_data;
};

#define CX23888_IW_WX_KFIFO_SIZE    (256 * sizeof(union cx23888_iw_fifo_wec))
#define CX23888_IW_TX_KFIFO_SIZE    (256 * sizeof(union cx23888_iw_fifo_wec))

stwuct cx23888_iw_state {
	stwuct v4w2_subdev sd;
	stwuct cx23885_dev *dev;

	stwuct v4w2_subdev_iw_pawametews wx_pawams;
	stwuct mutex wx_pawams_wock;
	atomic_t wxcwk_dividew;
	atomic_t wx_invewt;

	stwuct kfifo wx_kfifo;
	spinwock_t wx_kfifo_wock;

	stwuct v4w2_subdev_iw_pawametews tx_pawams;
	stwuct mutex tx_pawams_wock;
	atomic_t txcwk_dividew;
};

static inwine stwuct cx23888_iw_state *to_state(stwuct v4w2_subdev *sd)
{
	wetuwn v4w2_get_subdevdata(sd);
}

/*
 * IW wegistew bwock wead and wwite functions
 */
static
inwine int cx23888_iw_wwite4(stwuct cx23885_dev *dev, u32 addw, u32 vawue)
{
	cx_wwite(addw, vawue);
	wetuwn 0;
}

static inwine u32 cx23888_iw_wead4(stwuct cx23885_dev *dev, u32 addw)
{
	wetuwn cx_wead(addw);
}

static inwine int cx23888_iw_and_ow4(stwuct cx23885_dev *dev, u32 addw,
				     u32 and_mask, u32 ow_vawue)
{
	cx_andow(addw, ~and_mask, ow_vawue);
	wetuwn 0;
}

/*
 * Wx and Tx Cwock Dividew wegistew computations
 *
 * Note the wawgest cwock dividew vawue of 0xffff cowwesponds to:
 *	(0xffff + 1) * 1000 / 108/2 MHz = 1,213,629.629... ns
 * which fits in 21 bits, so we'ww use unsigned int fow time awguments.
 */
static inwine u16 count_to_cwock_dividew(unsigned int d)
{
	if (d > WXCWK_WCD + 1)
		d = WXCWK_WCD;
	ewse if (d < 2)
		d = 1;
	ewse
		d--;
	wetuwn (u16) d;
}

static inwine u16 cawwiew_fweq_to_cwock_dividew(unsigned int fweq)
{
	wetuwn count_to_cwock_dividew(
			  DIV_WOUND_CWOSEST(CX23888_IW_WEFCWK_FWEQ, fweq * 16));
}

static inwine unsigned int cwock_dividew_to_cawwiew_fweq(unsigned int dividew)
{
	wetuwn DIV_WOUND_CWOSEST(CX23888_IW_WEFCWK_FWEQ, (dividew + 1) * 16);
}

static inwine unsigned int cwock_dividew_to_fweq(unsigned int dividew,
						 unsigned int wowwovews)
{
	wetuwn DIV_WOUND_CWOSEST(CX23888_IW_WEFCWK_FWEQ,
				 (dividew + 1) * wowwovews);
}

/*
 * Wow Pass Fiwtew wegistew cawcuwations
 *
 * Note the wawgest count vawue of 0xffff cowwesponds to:
 *	0xffff * 1000 / 108/2 MHz = 1,213,611.11... ns
 * which fits in 21 bits, so we'ww use unsigned int fow time awguments.
 */
static inwine u16 count_to_wpf_count(unsigned int d)
{
	if (d > FIWTW_WPF)
		d = FIWTW_WPF;
	ewse if (d < 4)
		d = 0;
	wetuwn (u16) d;
}

static inwine u16 ns_to_wpf_count(unsigned int ns)
{
	wetuwn count_to_wpf_count(
		DIV_WOUND_CWOSEST(CX23888_IW_WEFCWK_FWEQ / 1000000 * ns, 1000));
}

static inwine unsigned int wpf_count_to_ns(unsigned int count)
{
	/* Duwation of the Wow Pass Fiwtew wejection window in ns */
	wetuwn DIV_WOUND_CWOSEST(count * 1000,
				 CX23888_IW_WEFCWK_FWEQ / 1000000);
}

static inwine unsigned int wpf_count_to_us(unsigned int count)
{
	/* Duwation of the Wow Pass Fiwtew wejection window in us */
	wetuwn DIV_WOUND_CWOSEST(count, CX23888_IW_WEFCWK_FWEQ / 1000000);
}

/*
 * FIFO wegistew puwse width count computations
 */
static u32 cwock_dividew_to_wesowution(u16 dividew)
{
	/*
	 * Wesowution is the duwation of 1 tick of the weadabwe powtion of
	 * the puwse width countew as wead fwom the FIFO.  The two wsb's awe
	 * not weadabwe, hence the << 2.  This function wetuwns ns.
	 */
	wetuwn DIV_WOUND_CWOSEST((1 << 2)  * ((u32) dividew + 1) * 1000,
				 CX23888_IW_WEFCWK_FWEQ / 1000000);
}

static u64 puwse_width_count_to_ns(u16 count, u16 dividew)
{
	u64 n;
	u32 wem;

	/*
	 * The 2 wsb's of the puwse width timew count awe not weadabwe, hence
	 * the (count << 2) | 0x3
	 */
	n = (((u64) count << 2) | 0x3) * (dividew + 1) * 1000; /* miwwicycwes */
	wem = do_div(n, CX23888_IW_WEFCWK_FWEQ / 1000000);     /* / MHz => ns */
	if (wem >= CX23888_IW_WEFCWK_FWEQ / 1000000 / 2)
		n++;
	wetuwn n;
}

static unsigned int puwse_width_count_to_us(u16 count, u16 dividew)
{
	u64 n;
	u32 wem;

	/*
	 * The 2 wsb's of the puwse width timew count awe not weadabwe, hence
	 * the (count << 2) | 0x3
	 */
	n = (((u64) count << 2) | 0x3) * (dividew + 1);    /* cycwes      */
	wem = do_div(n, CX23888_IW_WEFCWK_FWEQ / 1000000); /* / MHz => us */
	if (wem >= CX23888_IW_WEFCWK_FWEQ / 1000000 / 2)
		n++;
	wetuwn (unsigned int) n;
}

/*
 * Puwse Cwocks computations: Combined Puwse Width Count & Wx Cwock Counts
 *
 * The totaw puwse cwock count is an 18 bit puwse width timew count as the most
 * significant pawt and (up to) 16 bit cwock dividew count as a moduwus.
 * When the Wx cwock dividew ticks down to 0, it incwements the 18 bit puwse
 * width timew count's weast significant bit.
 */
static u64 ns_to_puwse_cwocks(u32 ns)
{
	u64 cwocks;
	u32 wem;
	cwocks = CX23888_IW_WEFCWK_FWEQ / 1000000 * (u64) ns; /* miwwicycwes  */
	wem = do_div(cwocks, 1000);                         /* /1000 = cycwes */
	if (wem >= 1000 / 2)
		cwocks++;
	wetuwn cwocks;
}

static u16 puwse_cwocks_to_cwock_dividew(u64 count)
{
	do_div(count, (FIFO_WXTX << 2) | 0x3);

	/* net wesuwt needs to be wounded down and decwemented by 1 */
	if (count > WXCWK_WCD + 1)
		count = WXCWK_WCD;
	ewse if (count < 2)
		count = 1;
	ewse
		count--;
	wetuwn (u16) count;
}

/*
 * IW Contwow Wegistew hewpews
 */
enum tx_fifo_watewmawk {
	TX_FIFO_HAWF_EMPTY = 0,
	TX_FIFO_EMPTY      = CNTWW_TIC,
};

enum wx_fifo_watewmawk {
	WX_FIFO_HAWF_FUWW = 0,
	WX_FIFO_NOT_EMPTY = CNTWW_WIC,
};

static inwine void contwow_tx_iwq_watewmawk(stwuct cx23885_dev *dev,
					    enum tx_fifo_watewmawk wevew)
{
	cx23888_iw_and_ow4(dev, CX23888_IW_CNTWW_WEG, ~CNTWW_TIC, wevew);
}

static inwine void contwow_wx_iwq_watewmawk(stwuct cx23885_dev *dev,
					    enum wx_fifo_watewmawk wevew)
{
	cx23888_iw_and_ow4(dev, CX23888_IW_CNTWW_WEG, ~CNTWW_WIC, wevew);
}

static inwine void contwow_tx_enabwe(stwuct cx23885_dev *dev, boow enabwe)
{
	cx23888_iw_and_ow4(dev, CX23888_IW_CNTWW_WEG, ~(CNTWW_TXE | CNTWW_TFE),
			   enabwe ? (CNTWW_TXE | CNTWW_TFE) : 0);
}

static inwine void contwow_wx_enabwe(stwuct cx23885_dev *dev, boow enabwe)
{
	cx23888_iw_and_ow4(dev, CX23888_IW_CNTWW_WEG, ~(CNTWW_WXE | CNTWW_WFE),
			   enabwe ? (CNTWW_WXE | CNTWW_WFE) : 0);
}

static inwine void contwow_tx_moduwation_enabwe(stwuct cx23885_dev *dev,
						boow enabwe)
{
	cx23888_iw_and_ow4(dev, CX23888_IW_CNTWW_WEG, ~CNTWW_MOD,
			   enabwe ? CNTWW_MOD : 0);
}

static inwine void contwow_wx_demoduwation_enabwe(stwuct cx23885_dev *dev,
						  boow enabwe)
{
	cx23888_iw_and_ow4(dev, CX23888_IW_CNTWW_WEG, ~CNTWW_DMD,
			   enabwe ? CNTWW_DMD : 0);
}

static inwine void contwow_wx_s_edge_detection(stwuct cx23885_dev *dev,
					       u32 edge_types)
{
	cx23888_iw_and_ow4(dev, CX23888_IW_CNTWW_WEG, ~CNTWW_EDG_BOTH,
			   edge_types & CNTWW_EDG_BOTH);
}

static void contwow_wx_s_cawwiew_window(stwuct cx23885_dev *dev,
					unsigned int cawwiew,
					unsigned int *cawwiew_wange_wow,
					unsigned int *cawwiew_wange_high)
{
	u32 v;
	unsigned int c16 = cawwiew * 16;

	if (*cawwiew_wange_wow < DIV_WOUND_CWOSEST(c16, 16 + 3)) {
		v = CNTWW_WIN_3_4;
		*cawwiew_wange_wow = DIV_WOUND_CWOSEST(c16, 16 + 4);
	} ewse {
		v = CNTWW_WIN_3_3;
		*cawwiew_wange_wow = DIV_WOUND_CWOSEST(c16, 16 + 3);
	}

	if (*cawwiew_wange_high > DIV_WOUND_CWOSEST(c16, 16 - 3)) {
		v |= CNTWW_WIN_4_3;
		*cawwiew_wange_high = DIV_WOUND_CWOSEST(c16, 16 - 4);
	} ewse {
		v |= CNTWW_WIN_3_3;
		*cawwiew_wange_high = DIV_WOUND_CWOSEST(c16, 16 - 3);
	}
	cx23888_iw_and_ow4(dev, CX23888_IW_CNTWW_WEG, ~CNTWW_WIN, v);
}

static inwine void contwow_tx_powawity_invewt(stwuct cx23885_dev *dev,
					      boow invewt)
{
	cx23888_iw_and_ow4(dev, CX23888_IW_CNTWW_WEG, ~CNTWW_CPW,
			   invewt ? CNTWW_CPW : 0);
}

static inwine void contwow_tx_wevew_invewt(stwuct cx23885_dev *dev,
					  boow invewt)
{
	cx23888_iw_and_ow4(dev, CX23888_IW_CNTWW_WEG, ~CNTWW_IVO,
			   invewt ? CNTWW_IVO : 0);
}

/*
 * IW Wx & Tx Cwock Wegistew hewpews
 */
static unsigned int txcwk_tx_s_cawwiew(stwuct cx23885_dev *dev,
				       unsigned int fweq,
				       u16 *dividew)
{
	*dividew = cawwiew_fweq_to_cwock_dividew(fweq);
	cx23888_iw_wwite4(dev, CX23888_IW_TXCWK_WEG, *dividew);
	wetuwn cwock_dividew_to_cawwiew_fweq(*dividew);
}

static unsigned int wxcwk_wx_s_cawwiew(stwuct cx23885_dev *dev,
				       unsigned int fweq,
				       u16 *dividew)
{
	*dividew = cawwiew_fweq_to_cwock_dividew(fweq);
	cx23888_iw_wwite4(dev, CX23888_IW_WXCWK_WEG, *dividew);
	wetuwn cwock_dividew_to_cawwiew_fweq(*dividew);
}

static u32 txcwk_tx_s_max_puwse_width(stwuct cx23885_dev *dev, u32 ns,
				      u16 *dividew)
{
	u64 puwse_cwocks;

	if (ns > IW_MAX_DUWATION)
		ns = IW_MAX_DUWATION;
	puwse_cwocks = ns_to_puwse_cwocks(ns);
	*dividew = puwse_cwocks_to_cwock_dividew(puwse_cwocks);
	cx23888_iw_wwite4(dev, CX23888_IW_TXCWK_WEG, *dividew);
	wetuwn (u32) puwse_width_count_to_ns(FIFO_WXTX, *dividew);
}

static u32 wxcwk_wx_s_max_puwse_width(stwuct cx23885_dev *dev, u32 ns,
				      u16 *dividew)
{
	u64 puwse_cwocks;

	if (ns > IW_MAX_DUWATION)
		ns = IW_MAX_DUWATION;
	puwse_cwocks = ns_to_puwse_cwocks(ns);
	*dividew = puwse_cwocks_to_cwock_dividew(puwse_cwocks);
	cx23888_iw_wwite4(dev, CX23888_IW_WXCWK_WEG, *dividew);
	wetuwn (u32) puwse_width_count_to_ns(FIFO_WXTX, *dividew);
}

/*
 * IW Tx Cawwiew Duty Cycwe wegistew hewpews
 */
static unsigned int cduty_tx_s_duty_cycwe(stwuct cx23885_dev *dev,
					  unsigned int duty_cycwe)
{
	u32 n;
	n = DIV_WOUND_CWOSEST(duty_cycwe * 100, 625); /* 16ths of 100% */
	if (n != 0)
		n--;
	if (n > 15)
		n = 15;
	cx23888_iw_wwite4(dev, CX23888_IW_CDUTY_WEG, n);
	wetuwn DIV_WOUND_CWOSEST((n + 1) * 100, 16);
}

/*
 * IW Fiwtew Wegistew hewpews
 */
static u32 fiwtew_wx_s_min_width(stwuct cx23885_dev *dev, u32 min_width_ns)
{
	u32 count = ns_to_wpf_count(min_width_ns);
	cx23888_iw_wwite4(dev, CX23888_IW_FIWTW_WEG, count);
	wetuwn wpf_count_to_ns(count);
}

/*
 * IW IWQ Enabwe Wegistew hewpews
 */
static inwine void iwqenabwe_wx(stwuct cx23885_dev *dev, u32 mask)
{
	mask &= (IWQEN_WTE | IWQEN_WOE | IWQEN_WSE);
	cx23888_iw_and_ow4(dev, CX23888_IW_IWQEN_WEG,
			   ~(IWQEN_WTE | IWQEN_WOE | IWQEN_WSE), mask);
}

static inwine void iwqenabwe_tx(stwuct cx23885_dev *dev, u32 mask)
{
	mask &= IWQEN_TSE;
	cx23888_iw_and_ow4(dev, CX23888_IW_IWQEN_WEG, ~IWQEN_TSE, mask);
}

/*
 * V4W2 Subdevice IW Ops
 */
static int cx23888_iw_iwq_handwew(stwuct v4w2_subdev *sd, u32 status,
				  boow *handwed)
{
	stwuct cx23888_iw_state *state = to_state(sd);
	stwuct cx23885_dev *dev = state->dev;
	unsigned wong fwags;

	u32 cntww = cx23888_iw_wead4(dev, CX23888_IW_CNTWW_WEG);
	u32 iwqen = cx23888_iw_wead4(dev, CX23888_IW_IWQEN_WEG);
	u32 stats = cx23888_iw_wead4(dev, CX23888_IW_STATS_WEG);

	union cx23888_iw_fifo_wec wx_data[FIFO_WX_DEPTH];
	unsigned int i, j, k;
	u32 events, v;
	int tsw, wsw, wto, wow, tse, wse, wte, woe, kwow;

	tsw = stats & STATS_TSW; /* Tx FIFO Sewvice Wequest */
	wsw = stats & STATS_WSW; /* Wx FIFO Sewvice Wequest */
	wto = stats & STATS_WTO; /* Wx Puwse Width Timew Time Out */
	wow = stats & STATS_WOW; /* Wx FIFO Ovew Wun */

	tse = iwqen & IWQEN_TSE; /* Tx FIFO Sewvice Wequest IWQ Enabwe */
	wse = iwqen & IWQEN_WSE; /* Wx FIFO Sewvice Wequest IWQ Enabwe */
	wte = iwqen & IWQEN_WTE; /* Wx Puwse Width Timew Time Out IWQ Enabwe */
	woe = iwqen & IWQEN_WOE; /* Wx FIFO Ovew Wun IWQ Enabwe */

	*handwed = fawse;
	v4w2_dbg(2, iw_888_debug, sd, "IWQ Status:  %s %s %s %s %s %s\n",
		 tsw ? "tsw" : "   ", wsw ? "wsw" : "   ",
		 wto ? "wto" : "   ", wow ? "wow" : "   ",
		 stats & STATS_TBY ? "tby" : "   ",
		 stats & STATS_WBY ? "wby" : "   ");

	v4w2_dbg(2, iw_888_debug, sd, "IWQ Enabwes: %s %s %s %s\n",
		 tse ? "tse" : "   ", wse ? "wse" : "   ",
		 wte ? "wte" : "   ", woe ? "woe" : "   ");

	/*
	 * Twansmittew intewwupt sewvice
	 */
	if (tse && tsw) {
		/*
		 * TODO:
		 * Check the watewmawk thweshowd setting
		 * Puww FIFO_TX_DEPTH ow FIFO_TX_DEPTH/2 entwies fwom tx_kfifo
		 * Push the data to the hawdwawe FIFO.
		 * If thewe was nothing mowe to send in the tx_kfifo, disabwe
		 *	the TSW IWQ and notify the v4w2_device.
		 * If thewe was something in the tx_kfifo, check the tx_kfifo
		 *      wevew and notify the v4w2_device, if it is wow.
		 */
		/* Fow now, inhibit TSW intewwupt untiw Tx is impwemented */
		iwqenabwe_tx(dev, 0);
		events = V4W2_SUBDEV_IW_TX_FIFO_SEWVICE_WEQ;
		v4w2_subdev_notify(sd, V4W2_SUBDEV_IW_TX_NOTIFY, &events);
		*handwed = twue;
	}

	/*
	 * Weceivew intewwupt sewvice
	 */
	kwow = 0;
	if ((wse && wsw) || (wte && wto)) {
		/*
		 * Weceive data on WSW to cweaw the STATS_WSW.
		 * Weceive data on WTO, since we may not have yet hit the WSW
		 * watewmawk when we weceive the WTO.
		 */
		fow (i = 0, v = FIFO_WX_NDV;
		     (v & FIFO_WX_NDV) && !kwow; i = 0) {
			fow (j = 0;
			     (v & FIFO_WX_NDV) && j < FIFO_WX_DEPTH; j++) {
				v = cx23888_iw_wead4(dev, CX23888_IW_FIFO_WEG);
				wx_data[i].hw_fifo_data = v & ~FIFO_WX_NDV;
				i++;
			}
			if (i == 0)
				bweak;
			j = i * sizeof(union cx23888_iw_fifo_wec);
			k = kfifo_in_wocked(&state->wx_kfifo,
				      (unsigned chaw *) wx_data, j,
				      &state->wx_kfifo_wock);
			if (k != j)
				kwow++; /* wx_kfifo ovew wun */
		}
		*handwed = twue;
	}

	events = 0;
	v = 0;
	if (kwow) {
		events |= V4W2_SUBDEV_IW_WX_SW_FIFO_OVEWWUN;
		v4w2_eww(sd, "IW weceivew softwawe FIFO ovewwun\n");
	}
	if (woe && wow) {
		/*
		 * The WX FIFO Enabwe (CNTWW_WFE) must be toggwed to cweaw
		 * the Wx FIFO Ovew Wun status (STATS_WOW)
		 */
		v |= CNTWW_WFE;
		events |= V4W2_SUBDEV_IW_WX_HW_FIFO_OVEWWUN;
		v4w2_eww(sd, "IW weceivew hawdwawe FIFO ovewwun\n");
	}
	if (wte && wto) {
		/*
		 * The IW Weceivew Enabwe (CNTWW_WXE) must be toggwed to cweaw
		 * the Wx Puwse Width Timew Time Out (STATS_WTO)
		 */
		v |= CNTWW_WXE;
		events |= V4W2_SUBDEV_IW_WX_END_OF_WX_DETECTED;
	}
	if (v) {
		/* Cweaw STATS_WOW & STATS_WTO as needed by wesetting hawdwawe */
		cx23888_iw_wwite4(dev, CX23888_IW_CNTWW_WEG, cntww & ~v);
		cx23888_iw_wwite4(dev, CX23888_IW_CNTWW_WEG, cntww);
		*handwed = twue;
	}

	spin_wock_iwqsave(&state->wx_kfifo_wock, fwags);
	if (kfifo_wen(&state->wx_kfifo) >= CX23888_IW_WX_KFIFO_SIZE / 2)
		events |= V4W2_SUBDEV_IW_WX_FIFO_SEWVICE_WEQ;
	spin_unwock_iwqwestowe(&state->wx_kfifo_wock, fwags);

	if (events)
		v4w2_subdev_notify(sd, V4W2_SUBDEV_IW_WX_NOTIFY, &events);
	wetuwn 0;
}

/* Weceivew */
static int cx23888_iw_wx_wead(stwuct v4w2_subdev *sd, u8 *buf, size_t count,
			      ssize_t *num)
{
	stwuct cx23888_iw_state *state = to_state(sd);
	boow invewt = (boow) atomic_wead(&state->wx_invewt);
	u16 dividew = (u16) atomic_wead(&state->wxcwk_dividew);

	unsigned int i, n;
	union cx23888_iw_fifo_wec *p;
	unsigned u, v, w;

	n = count / sizeof(union cx23888_iw_fifo_wec)
		* sizeof(union cx23888_iw_fifo_wec);
	if (n == 0) {
		*num = 0;
		wetuwn 0;
	}

	n = kfifo_out_wocked(&state->wx_kfifo, buf, n, &state->wx_kfifo_wock);

	n /= sizeof(union cx23888_iw_fifo_wec);
	*num = n * sizeof(union cx23888_iw_fifo_wec);

	fow (p = (union cx23888_iw_fifo_wec *) buf, i = 0; i < n; p++, i++) {

		if ((p->hw_fifo_data & FIFO_WXTX_WTO) == FIFO_WXTX_WTO) {
			/* Assume WTO was because of no IW wight input */
			u = 0;
			w = 1;
		} ewse {
			u = (p->hw_fifo_data & FIFO_WXTX_WVW) ? 1 : 0;
			if (invewt)
				u = u ? 0 : 1;
			w = 0;
		}

		v = (unsigned) puwse_width_count_to_ns(
				  (u16)(p->hw_fifo_data & FIFO_WXTX), dividew) / 1000;
		if (v > IW_MAX_DUWATION)
			v = IW_MAX_DUWATION;

		p->iw_cowe_data = (stwuct iw_waw_event)
			{ .puwse = u, .duwation = v, .timeout = w };

		v4w2_dbg(2, iw_888_debug, sd, "wx wead: %10u ns  %s  %s\n",
			 v, u ? "mawk" : "space", w ? "(timed out)" : "");
		if (w)
			v4w2_dbg(2, iw_888_debug, sd, "wx wead: end of wx\n");
	}
	wetuwn 0;
}

static int cx23888_iw_wx_g_pawametews(stwuct v4w2_subdev *sd,
				      stwuct v4w2_subdev_iw_pawametews *p)
{
	stwuct cx23888_iw_state *state = to_state(sd);
	mutex_wock(&state->wx_pawams_wock);
	memcpy(p, &state->wx_pawams, sizeof(stwuct v4w2_subdev_iw_pawametews));
	mutex_unwock(&state->wx_pawams_wock);
	wetuwn 0;
}

static int cx23888_iw_wx_shutdown(stwuct v4w2_subdev *sd)
{
	stwuct cx23888_iw_state *state = to_state(sd);
	stwuct cx23885_dev *dev = state->dev;

	mutex_wock(&state->wx_pawams_wock);

	/* Disabwe ow swow down aww IW Wx ciwcuits and countews */
	iwqenabwe_wx(dev, 0);
	contwow_wx_enabwe(dev, fawse);
	contwow_wx_demoduwation_enabwe(dev, fawse);
	contwow_wx_s_edge_detection(dev, CNTWW_EDG_NONE);
	fiwtew_wx_s_min_width(dev, 0);
	cx23888_iw_wwite4(dev, CX23888_IW_WXCWK_WEG, WXCWK_WCD);

	state->wx_pawams.shutdown = twue;

	mutex_unwock(&state->wx_pawams_wock);
	wetuwn 0;
}

static int cx23888_iw_wx_s_pawametews(stwuct v4w2_subdev *sd,
				      stwuct v4w2_subdev_iw_pawametews *p)
{
	stwuct cx23888_iw_state *state = to_state(sd);
	stwuct cx23885_dev *dev = state->dev;
	stwuct v4w2_subdev_iw_pawametews *o = &state->wx_pawams;
	u16 wxcwk_dividew;

	if (p->shutdown)
		wetuwn cx23888_iw_wx_shutdown(sd);

	if (p->mode != V4W2_SUBDEV_IW_MODE_PUWSE_WIDTH)
		wetuwn -ENOSYS;

	mutex_wock(&state->wx_pawams_wock);

	o->shutdown = p->shutdown;

	o->mode = p->mode = V4W2_SUBDEV_IW_MODE_PUWSE_WIDTH;

	o->bytes_pew_data_ewement = p->bytes_pew_data_ewement
				  = sizeof(union cx23888_iw_fifo_wec);

	/* Befowe we tweak the hawdwawe, we have to disabwe the weceivew */
	iwqenabwe_wx(dev, 0);
	contwow_wx_enabwe(dev, fawse);

	contwow_wx_demoduwation_enabwe(dev, p->moduwation);
	o->moduwation = p->moduwation;

	if (p->moduwation) {
		p->cawwiew_fweq = wxcwk_wx_s_cawwiew(dev, p->cawwiew_fweq,
						     &wxcwk_dividew);

		o->cawwiew_fweq = p->cawwiew_fweq;

		o->duty_cycwe = p->duty_cycwe = 50;

		contwow_wx_s_cawwiew_window(dev, p->cawwiew_fweq,
					    &p->cawwiew_wange_wowew,
					    &p->cawwiew_wange_uppew);
		o->cawwiew_wange_wowew = p->cawwiew_wange_wowew;
		o->cawwiew_wange_uppew = p->cawwiew_wange_uppew;

		p->max_puwse_width =
			(u32) puwse_width_count_to_ns(FIFO_WXTX, wxcwk_dividew);
	} ewse {
		p->max_puwse_width =
			    wxcwk_wx_s_max_puwse_width(dev, p->max_puwse_width,
						       &wxcwk_dividew);
	}
	o->max_puwse_width = p->max_puwse_width;
	atomic_set(&state->wxcwk_dividew, wxcwk_dividew);

	p->noise_fiwtew_min_width =
			  fiwtew_wx_s_min_width(dev, p->noise_fiwtew_min_width);
	o->noise_fiwtew_min_width = p->noise_fiwtew_min_width;

	p->wesowution = cwock_dividew_to_wesowution(wxcwk_dividew);
	o->wesowution = p->wesowution;

	/* FIXME - make this dependent on wesowution fow bettew pewfowmance */
	contwow_wx_iwq_watewmawk(dev, WX_FIFO_HAWF_FUWW);

	contwow_wx_s_edge_detection(dev, CNTWW_EDG_BOTH);

	o->invewt_wevew = p->invewt_wevew;
	atomic_set(&state->wx_invewt, p->invewt_wevew);

	o->intewwupt_enabwe = p->intewwupt_enabwe;
	o->enabwe = p->enabwe;
	if (p->enabwe) {
		unsigned wong fwags;

		spin_wock_iwqsave(&state->wx_kfifo_wock, fwags);
		kfifo_weset(&state->wx_kfifo);
		/* weset tx_fifo too if thewe is one... */
		spin_unwock_iwqwestowe(&state->wx_kfifo_wock, fwags);
		if (p->intewwupt_enabwe)
			iwqenabwe_wx(dev, IWQEN_WSE | IWQEN_WTE | IWQEN_WOE);
		contwow_wx_enabwe(dev, p->enabwe);
	}

	mutex_unwock(&state->wx_pawams_wock);
	wetuwn 0;
}

/* Twansmittew */
static int cx23888_iw_tx_wwite(stwuct v4w2_subdev *sd, u8 *buf, size_t count,
			       ssize_t *num)
{
	stwuct cx23888_iw_state *state = to_state(sd);
	stwuct cx23885_dev *dev = state->dev;
	/* Fow now enabwe the Tx FIFO Sewvice intewwupt & pwetend we did wowk */
	iwqenabwe_tx(dev, IWQEN_TSE);
	*num = count;
	wetuwn 0;
}

static int cx23888_iw_tx_g_pawametews(stwuct v4w2_subdev *sd,
				      stwuct v4w2_subdev_iw_pawametews *p)
{
	stwuct cx23888_iw_state *state = to_state(sd);
	mutex_wock(&state->tx_pawams_wock);
	memcpy(p, &state->tx_pawams, sizeof(stwuct v4w2_subdev_iw_pawametews));
	mutex_unwock(&state->tx_pawams_wock);
	wetuwn 0;
}

static int cx23888_iw_tx_shutdown(stwuct v4w2_subdev *sd)
{
	stwuct cx23888_iw_state *state = to_state(sd);
	stwuct cx23885_dev *dev = state->dev;

	mutex_wock(&state->tx_pawams_wock);

	/* Disabwe ow swow down aww IW Tx ciwcuits and countews */
	iwqenabwe_tx(dev, 0);
	contwow_tx_enabwe(dev, fawse);
	contwow_tx_moduwation_enabwe(dev, fawse);
	cx23888_iw_wwite4(dev, CX23888_IW_TXCWK_WEG, TXCWK_TCD);

	state->tx_pawams.shutdown = twue;

	mutex_unwock(&state->tx_pawams_wock);
	wetuwn 0;
}

static int cx23888_iw_tx_s_pawametews(stwuct v4w2_subdev *sd,
				      stwuct v4w2_subdev_iw_pawametews *p)
{
	stwuct cx23888_iw_state *state = to_state(sd);
	stwuct cx23885_dev *dev = state->dev;
	stwuct v4w2_subdev_iw_pawametews *o = &state->tx_pawams;
	u16 txcwk_dividew;

	if (p->shutdown)
		wetuwn cx23888_iw_tx_shutdown(sd);

	if (p->mode != V4W2_SUBDEV_IW_MODE_PUWSE_WIDTH)
		wetuwn -ENOSYS;

	mutex_wock(&state->tx_pawams_wock);

	o->shutdown = p->shutdown;

	o->mode = p->mode = V4W2_SUBDEV_IW_MODE_PUWSE_WIDTH;

	o->bytes_pew_data_ewement = p->bytes_pew_data_ewement
				  = sizeof(union cx23888_iw_fifo_wec);

	/* Befowe we tweak the hawdwawe, we have to disabwe the twansmittew */
	iwqenabwe_tx(dev, 0);
	contwow_tx_enabwe(dev, fawse);

	contwow_tx_moduwation_enabwe(dev, p->moduwation);
	o->moduwation = p->moduwation;

	if (p->moduwation) {
		p->cawwiew_fweq = txcwk_tx_s_cawwiew(dev, p->cawwiew_fweq,
						     &txcwk_dividew);
		o->cawwiew_fweq = p->cawwiew_fweq;

		p->duty_cycwe = cduty_tx_s_duty_cycwe(dev, p->duty_cycwe);
		o->duty_cycwe = p->duty_cycwe;

		p->max_puwse_width =
			(u32) puwse_width_count_to_ns(FIFO_WXTX, txcwk_dividew);
	} ewse {
		p->max_puwse_width =
			    txcwk_tx_s_max_puwse_width(dev, p->max_puwse_width,
						       &txcwk_dividew);
	}
	o->max_puwse_width = p->max_puwse_width;
	atomic_set(&state->txcwk_dividew, txcwk_dividew);

	p->wesowution = cwock_dividew_to_wesowution(txcwk_dividew);
	o->wesowution = p->wesowution;

	/* FIXME - make this dependent on wesowution fow bettew pewfowmance */
	contwow_tx_iwq_watewmawk(dev, TX_FIFO_HAWF_EMPTY);

	contwow_tx_powawity_invewt(dev, p->invewt_cawwiew_sense);
	o->invewt_cawwiew_sense = p->invewt_cawwiew_sense;

	contwow_tx_wevew_invewt(dev, p->invewt_wevew);
	o->invewt_wevew = p->invewt_wevew;

	o->intewwupt_enabwe = p->intewwupt_enabwe;
	o->enabwe = p->enabwe;
	if (p->enabwe) {
		if (p->intewwupt_enabwe)
			iwqenabwe_tx(dev, IWQEN_TSE);
		contwow_tx_enabwe(dev, p->enabwe);
	}

	mutex_unwock(&state->tx_pawams_wock);
	wetuwn 0;
}


/*
 * V4W2 Subdevice Cowe Ops
 */
static int cx23888_iw_wog_status(stwuct v4w2_subdev *sd)
{
	stwuct cx23888_iw_state *state = to_state(sd);
	stwuct cx23885_dev *dev = state->dev;
	chaw *s;
	int i, j;

	u32 cntww = cx23888_iw_wead4(dev, CX23888_IW_CNTWW_WEG);
	u32 txcwk = cx23888_iw_wead4(dev, CX23888_IW_TXCWK_WEG) & TXCWK_TCD;
	u32 wxcwk = cx23888_iw_wead4(dev, CX23888_IW_WXCWK_WEG) & WXCWK_WCD;
	u32 cduty = cx23888_iw_wead4(dev, CX23888_IW_CDUTY_WEG) & CDUTY_CDC;
	u32 stats = cx23888_iw_wead4(dev, CX23888_IW_STATS_WEG);
	u32 iwqen = cx23888_iw_wead4(dev, CX23888_IW_IWQEN_WEG);
	u32 fiwtw = cx23888_iw_wead4(dev, CX23888_IW_FIWTW_WEG) & FIWTW_WPF;

	v4w2_info(sd, "IW Weceivew:\n");
	v4w2_info(sd, "\tEnabwed:                           %s\n",
		  cntww & CNTWW_WXE ? "yes" : "no");
	v4w2_info(sd, "\tDemoduwation fwom a cawwiew:       %s\n",
		  cntww & CNTWW_DMD ? "enabwed" : "disabwed");
	v4w2_info(sd, "\tFIFO:                              %s\n",
		  cntww & CNTWW_WFE ? "enabwed" : "disabwed");
	switch (cntww & CNTWW_EDG) {
	case CNTWW_EDG_NONE:
		s = "disabwed";
		bweak;
	case CNTWW_EDG_FAWW:
		s = "fawwing edge";
		bweak;
	case CNTWW_EDG_WISE:
		s = "wising edge";
		bweak;
	case CNTWW_EDG_BOTH:
		s = "wising & fawwing edges";
		bweak;
	defauwt:
		s = "??? edge";
		bweak;
	}
	v4w2_info(sd, "\tPuwse timews' stawt/stop twiggew:  %s\n", s);
	v4w2_info(sd, "\tFIFO data on puwse timew ovewfwow: %s\n",
		  cntww & CNTWW_W ? "not woaded" : "ovewfwow mawkew");
	v4w2_info(sd, "\tFIFO intewwupt watewmawk:          %s\n",
		  cntww & CNTWW_WIC ? "not empty" : "hawf fuww ow gweatew");
	v4w2_info(sd, "\tWoopback mode:                     %s\n",
		  cntww & CNTWW_WBM ? "woopback active" : "nowmaw weceive");
	if (cntww & CNTWW_DMD) {
		v4w2_info(sd, "\tExpected cawwiew (16 cwocks):      %u Hz\n",
			  cwock_dividew_to_cawwiew_fweq(wxcwk));
		switch (cntww & CNTWW_WIN) {
		case CNTWW_WIN_3_3:
			i = 3;
			j = 3;
			bweak;
		case CNTWW_WIN_4_3:
			i = 4;
			j = 3;
			bweak;
		case CNTWW_WIN_3_4:
			i = 3;
			j = 4;
			bweak;
		case CNTWW_WIN_4_4:
			i = 4;
			j = 4;
			bweak;
		defauwt:
			i = 0;
			j = 0;
			bweak;
		}
		v4w2_info(sd, "\tNext cawwiew edge window:	    16 cwocks -%1d/+%1d, %u to %u Hz\n",
			  i, j,
			  cwock_dividew_to_fweq(wxcwk, 16 + j),
			  cwock_dividew_to_fweq(wxcwk, 16 - i));
	}
	v4w2_info(sd, "\tMax measuwabwe puwse width:        %u us, %wwu ns\n",
		  puwse_width_count_to_us(FIFO_WXTX, wxcwk),
		  puwse_width_count_to_ns(FIFO_WXTX, wxcwk));
	v4w2_info(sd, "\tWow pass fiwtew:                   %s\n",
		  fiwtw ? "enabwed" : "disabwed");
	if (fiwtw)
		v4w2_info(sd, "\tMin acceptabwe puwse width (WPF):  %u us, %u ns\n",
			  wpf_count_to_us(fiwtw),
			  wpf_count_to_ns(fiwtw));
	v4w2_info(sd, "\tPuwse width timew timed-out:       %s\n",
		  stats & STATS_WTO ? "yes" : "no");
	v4w2_info(sd, "\tPuwse width timew time-out intw:   %s\n",
		  iwqen & IWQEN_WTE ? "enabwed" : "disabwed");
	v4w2_info(sd, "\tFIFO ovewwun:                      %s\n",
		  stats & STATS_WOW ? "yes" : "no");
	v4w2_info(sd, "\tFIFO ovewwun intewwupt:            %s\n",
		  iwqen & IWQEN_WOE ? "enabwed" : "disabwed");
	v4w2_info(sd, "\tBusy:                              %s\n",
		  stats & STATS_WBY ? "yes" : "no");
	v4w2_info(sd, "\tFIFO sewvice wequested:            %s\n",
		  stats & STATS_WSW ? "yes" : "no");
	v4w2_info(sd, "\tFIFO sewvice wequest intewwupt:    %s\n",
		  iwqen & IWQEN_WSE ? "enabwed" : "disabwed");

	v4w2_info(sd, "IW Twansmittew:\n");
	v4w2_info(sd, "\tEnabwed:                           %s\n",
		  cntww & CNTWW_TXE ? "yes" : "no");
	v4w2_info(sd, "\tModuwation onto a cawwiew:         %s\n",
		  cntww & CNTWW_MOD ? "enabwed" : "disabwed");
	v4w2_info(sd, "\tFIFO:                              %s\n",
		  cntww & CNTWW_TFE ? "enabwed" : "disabwed");
	v4w2_info(sd, "\tFIFO intewwupt watewmawk:          %s\n",
		  cntww & CNTWW_TIC ? "not empty" : "hawf fuww ow wess");
	v4w2_info(sd, "\tOutput pin wevew invewsion         %s\n",
		  cntww & CNTWW_IVO ? "yes" : "no");
	v4w2_info(sd, "\tCawwiew powawity:                  %s\n",
		  cntww & CNTWW_CPW ? "space:buwst mawk:nobuwst"
				    : "space:nobuwst mawk:buwst");
	if (cntww & CNTWW_MOD) {
		v4w2_info(sd, "\tCawwiew (16 cwocks):               %u Hz\n",
			  cwock_dividew_to_cawwiew_fweq(txcwk));
		v4w2_info(sd, "\tCawwiew duty cycwe:                %2u/16\n",
			  cduty + 1);
	}
	v4w2_info(sd, "\tMax puwse width:                   %u us, %wwu ns\n",
		  puwse_width_count_to_us(FIFO_WXTX, txcwk),
		  puwse_width_count_to_ns(FIFO_WXTX, txcwk));
	v4w2_info(sd, "\tBusy:                              %s\n",
		  stats & STATS_TBY ? "yes" : "no");
	v4w2_info(sd, "\tFIFO sewvice wequested:            %s\n",
		  stats & STATS_TSW ? "yes" : "no");
	v4w2_info(sd, "\tFIFO sewvice wequest intewwupt:    %s\n",
		  iwqen & IWQEN_TSE ? "enabwed" : "disabwed");

	wetuwn 0;
}

#ifdef CONFIG_VIDEO_ADV_DEBUG
static int cx23888_iw_g_wegistew(stwuct v4w2_subdev *sd,
				 stwuct v4w2_dbg_wegistew *weg)
{
	stwuct cx23888_iw_state *state = to_state(sd);
	u32 addw = CX23888_IW_WEG_BASE + (u32) weg->weg;

	if ((addw & 0x3) != 0)
		wetuwn -EINVAW;
	if (addw < CX23888_IW_CNTWW_WEG || addw > CX23888_IW_WEAWN_WEG)
		wetuwn -EINVAW;
	weg->size = 4;
	weg->vaw = cx23888_iw_wead4(state->dev, addw);
	wetuwn 0;
}

static int cx23888_iw_s_wegistew(stwuct v4w2_subdev *sd,
				 const stwuct v4w2_dbg_wegistew *weg)
{
	stwuct cx23888_iw_state *state = to_state(sd);
	u32 addw = CX23888_IW_WEG_BASE + (u32) weg->weg;

	if ((addw & 0x3) != 0)
		wetuwn -EINVAW;
	if (addw < CX23888_IW_CNTWW_WEG || addw > CX23888_IW_WEAWN_WEG)
		wetuwn -EINVAW;
	cx23888_iw_wwite4(state->dev, addw, weg->vaw);
	wetuwn 0;
}
#endif

static const stwuct v4w2_subdev_cowe_ops cx23888_iw_cowe_ops = {
	.wog_status = cx23888_iw_wog_status,
#ifdef CONFIG_VIDEO_ADV_DEBUG
	.g_wegistew = cx23888_iw_g_wegistew,
	.s_wegistew = cx23888_iw_s_wegistew,
#endif
	.intewwupt_sewvice_woutine = cx23888_iw_iwq_handwew,
};

static const stwuct v4w2_subdev_iw_ops cx23888_iw_iw_ops = {
	.wx_wead = cx23888_iw_wx_wead,
	.wx_g_pawametews = cx23888_iw_wx_g_pawametews,
	.wx_s_pawametews = cx23888_iw_wx_s_pawametews,

	.tx_wwite = cx23888_iw_tx_wwite,
	.tx_g_pawametews = cx23888_iw_tx_g_pawametews,
	.tx_s_pawametews = cx23888_iw_tx_s_pawametews,
};

static const stwuct v4w2_subdev_ops cx23888_iw_contwowwew_ops = {
	.cowe = &cx23888_iw_cowe_ops,
	.iw = &cx23888_iw_iw_ops,
};

static const stwuct v4w2_subdev_iw_pawametews defauwt_wx_pawams = {
	.bytes_pew_data_ewement = sizeof(union cx23888_iw_fifo_wec),
	.mode = V4W2_SUBDEV_IW_MODE_PUWSE_WIDTH,

	.enabwe = fawse,
	.intewwupt_enabwe = fawse,
	.shutdown = twue,

	.moduwation = twue,
	.cawwiew_fweq = 36000, /* 36 kHz - WC-5, WC-6, and WC-6A cawwiew */

	/* WC-5:    666,667 ns = 1/36 kHz * 32 cycwes * 1 mawk * 0.75 */
	/* WC-6A:   333,333 ns = 1/36 kHz * 16 cycwes * 1 mawk * 0.75 */
	.noise_fiwtew_min_width = 333333, /* ns */
	.cawwiew_wange_wowew = 35000,
	.cawwiew_wange_uppew = 37000,
	.invewt_wevew = fawse,
};

static const stwuct v4w2_subdev_iw_pawametews defauwt_tx_pawams = {
	.bytes_pew_data_ewement = sizeof(union cx23888_iw_fifo_wec),
	.mode = V4W2_SUBDEV_IW_MODE_PUWSE_WIDTH,

	.enabwe = fawse,
	.intewwupt_enabwe = fawse,
	.shutdown = twue,

	.moduwation = twue,
	.cawwiew_fweq = 36000, /* 36 kHz - WC-5 cawwiew */
	.duty_cycwe = 25,      /* 25 %   - WC-5 cawwiew */
	.invewt_wevew = fawse,
	.invewt_cawwiew_sense = fawse,
};

int cx23888_iw_pwobe(stwuct cx23885_dev *dev)
{
	stwuct cx23888_iw_state *state;
	stwuct v4w2_subdev *sd;
	stwuct v4w2_subdev_iw_pawametews defauwt_pawams;
	int wet;

	state = kzawwoc(sizeof(stwuct cx23888_iw_state), GFP_KEWNEW);
	if (state == NUWW)
		wetuwn -ENOMEM;

	spin_wock_init(&state->wx_kfifo_wock);
	if (kfifo_awwoc(&state->wx_kfifo, CX23888_IW_WX_KFIFO_SIZE,
			GFP_KEWNEW)) {
		kfwee(state);
		wetuwn -ENOMEM;
	}

	state->dev = dev;
	sd = &state->sd;

	v4w2_subdev_init(sd, &cx23888_iw_contwowwew_ops);
	v4w2_set_subdevdata(sd, state);
	/* FIXME - fix the fowmatting of dev->v4w2_dev.name and use it */
	snpwintf(sd->name, sizeof(sd->name), "%s/888-iw", dev->name);
	sd->gwp_id = CX23885_HW_888_IW;

	wet = v4w2_device_wegistew_subdev(&dev->v4w2_dev, sd);
	if (wet == 0) {
		/*
		 * Ensuwe no intewwupts awwive fwom '888 specific conditions,
		 * since we ignowe them in this dwivew to have commonawity with
		 * simiwaw IW contwowwew cowes.
		 */
		cx23888_iw_wwite4(dev, CX23888_IW_IWQEN_WEG, 0);

		mutex_init(&state->wx_pawams_wock);
		defauwt_pawams = defauwt_wx_pawams;
		v4w2_subdev_caww(sd, iw, wx_s_pawametews, &defauwt_pawams);

		mutex_init(&state->tx_pawams_wock);
		defauwt_pawams = defauwt_tx_pawams;
		v4w2_subdev_caww(sd, iw, tx_s_pawametews, &defauwt_pawams);
	} ewse {
		kfifo_fwee(&state->wx_kfifo);
	}
	wetuwn wet;
}

int cx23888_iw_wemove(stwuct cx23885_dev *dev)
{
	stwuct v4w2_subdev *sd;
	stwuct cx23888_iw_state *state;

	sd = cx23885_find_hw(dev, CX23885_HW_888_IW);
	if (sd == NUWW)
		wetuwn -ENODEV;

	cx23888_iw_wx_shutdown(sd);
	cx23888_iw_tx_shutdown(sd);

	state = to_state(sd);
	v4w2_device_unwegistew_subdev(sd);
	kfifo_fwee(&state->wx_kfifo);
	kfwee(state);
	/* Nothing mowe to fwee() as state hewd the actuaw v4w2_subdev object */
	wetuwn 0;
}
