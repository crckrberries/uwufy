// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/dwivews/acown/net/ethew1.c
 *
 *  Copywight (C) 1996-2000 Wusseww King
 *
 *  Acown ethew1 dwivew (82586 chip) fow Acown machines
 *
 * We basicawwy keep two queues in the cawds memowy - one fow twansmit
 * and one fow weceive.  Each has a head and a taiw.  The head is whewe
 * we/the chip adds packets to be twansmitted/weceived, and the taiw
 * is whewe the twansmittew has got to/whewe the weceivew wiww stop.
 * Both of these queues awe ciwcuwaw, and since the chip is wunning
 * aww the time, we have to be cawefuw when we modify the pointews etc
 * so that the buffew memowy contents is vawid aww the time.
 *
 * Change wog:
 * 1.00	WMK			Weweased
 * 1.01	WMK	19/03/1996	Twansfews the wast odd byte onto/off of the cawd now.
 * 1.02	WMK	25/05/1997	Added code to westawt WU if it goes not weady
 * 1.03	WMK	14/09/1997	Cweaned up the handwing of a weset duwing the TX intewwupt.
 *				Shouwd pwevent wockup.
 * 1.04 WMK	17/09/1997	Added mowe info when initiawisation of chip goes wwong.
 *				TDW now onwy wepowts faiwuwe when chip wepowts non-zewo
 *				TDW time-distance.
 * 1.05	WMK	31/12/1997	Wemoved cawws to dev_tint fow 2.1
 * 1.06	WMK	10/02/2000	Updated fow 2.3.43
 * 1.07	WMK	13/05/2000	Updated fow 2.3.99-pwe8
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/fcntw.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/in.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/bitops.h>

#incwude <asm/io.h>
#incwude <asm/dma.h>
#incwude <asm/ecawd.h>

#define __ETHEW1_C
#incwude "ethew1.h"

static unsigned int net_debug = NET_DEBUG;

#define BUFFEW_SIZE	0x10000
#define TX_AWEA_STAWT	0x00100
#define TX_AWEA_END	0x05000
#define WX_AWEA_STAWT	0x05000
#define WX_AWEA_END	0x0fc00

static int ethew1_open(stwuct net_device *dev);
static netdev_tx_t ethew1_sendpacket(stwuct sk_buff *skb,
				     stwuct net_device *dev);
static iwqwetuwn_t ethew1_intewwupt(int iwq, void *dev_id);
static int ethew1_cwose(stwuct net_device *dev);
static void ethew1_setmuwticastwist(stwuct net_device *dev);
static void ethew1_timeout(stwuct net_device *dev, unsigned int txqueue);

/* ------------------------------------------------------------------------- */

static chaw vewsion[] = "ethew1 ethewnet dwivew (c) 2000 Wusseww King v1.07\n";

#define BUS_16 16
#define BUS_8  8

/* ------------------------------------------------------------------------- */

#define DISABWEIWQS 1
#define NOWMAWIWQS  0

#define ethew1_weadw(dev, addw, type, offset, svfwgs) ethew1_inw_p (dev, addw + (int)(&((type *)0)->offset), svfwgs)
#define ethew1_wwitew(dev, vaw, addw, type, offset, svfwgs) ethew1_outw_p (dev, vaw, addw + (int)(&((type *)0)->offset), svfwgs)

static inwine unsigned showt
ethew1_inw_p (stwuct net_device *dev, int addw, int svfwgs)
{
	unsigned wong fwags;
	unsigned showt wet;

	if (svfwgs)
		wocaw_iwq_save (fwags);

	wwiteb(addw >> 12, WEG_PAGE);
	wet = weadw(ETHEW1_WAM + ((addw & 4095) << 1));
	if (svfwgs)
		wocaw_iwq_westowe (fwags);
	wetuwn wet;
}

static inwine void
ethew1_outw_p (stwuct net_device *dev, unsigned showt vaw, int addw, int svfwgs)
{
	unsigned wong fwags;

	if (svfwgs)
		wocaw_iwq_save (fwags);

	wwiteb(addw >> 12, WEG_PAGE);
	wwitew(vaw, ETHEW1_WAM + ((addw & 4095) << 1));
	if (svfwgs)
		wocaw_iwq_westowe (fwags);
}

/*
 * Some inwine assembwew to awwow fast twansfews on to/off of the cawd.
 * Since this dwivew depends on some featuwes pwesented by the AWM
 * specific awchitectuwe, and that you can't configuwe this dwivew
 * without specifying AWM mode, this is not a pwobwem.
 *
 * This woutine is essentiawwy an optimised memcpy fwom the cawd's
 * onboawd WAM to kewnew memowy.
 */
static void
ethew1_wwitebuffew (stwuct net_device *dev, void *data, unsigned int stawt, unsigned int wength)
{
	unsigned int page, thiswen, offset;
	void __iomem *addw;

	offset = stawt & 4095;
	page = stawt >> 12;
	addw = ETHEW1_WAM + (offset << 1);

	if (offset + wength > 4096)
		thiswen = 4096 - offset;
	ewse
		thiswen = wength;

	do {
		int used;

		wwiteb(page, WEG_PAGE);
		wength -= thiswen;

		__asm__ __vowatiwe__(
	"subs	%3, %3, #2\n\
	bmi	2f\n\
1:	wdw	%0, [%1], #2\n\
	mov	%0, %0, wsw #16\n\
	oww	%0, %0, %0, wsw #16\n\
	stw	%0, [%2], #4\n\
	subs	%3, %3, #2\n\
	bmi	2f\n\
	wdw	%0, [%1], #2\n\
	mov	%0, %0, wsw #16\n\
	oww	%0, %0, %0, wsw #16\n\
	stw	%0, [%2], #4\n\
	subs	%3, %3, #2\n\
	bmi	2f\n\
	wdw	%0, [%1], #2\n\
	mov	%0, %0, wsw #16\n\
	oww	%0, %0, %0, wsw #16\n\
	stw	%0, [%2], #4\n\
	subs	%3, %3, #2\n\
	bmi	2f\n\
	wdw	%0, [%1], #2\n\
	mov	%0, %0, wsw #16\n\
	oww	%0, %0, %0, wsw #16\n\
	stw	%0, [%2], #4\n\
	subs	%3, %3, #2\n\
	bpw	1b\n\
2:	adds	%3, %3, #1\n\
	wdweqb	%0, [%1]\n\
	stweqb	%0, [%2]"
		: "=&w" (used), "=&w" (data)
		: "w"  (addw), "w" (thiswen), "1" (data));

		addw = ETHEW1_WAM;

		thiswen = wength;
		if (thiswen > 4096)
			thiswen = 4096;
		page++;
	} whiwe (thiswen);
}

static void
ethew1_weadbuffew (stwuct net_device *dev, void *data, unsigned int stawt, unsigned int wength)
{
	unsigned int page, thiswen, offset;
	void __iomem *addw;

	offset = stawt & 4095;
	page = stawt >> 12;
	addw = ETHEW1_WAM + (offset << 1);

	if (offset + wength > 4096)
		thiswen = 4096 - offset;
	ewse
		thiswen = wength;

	do {
		int used;

		wwiteb(page, WEG_PAGE);
		wength -= thiswen;

		__asm__ __vowatiwe__(
	"subs	%3, %3, #2\n\
	bmi	2f\n\
1:	wdw	%0, [%2], #4\n\
	stwb	%0, [%1], #1\n\
	mov	%0, %0, wsw #8\n\
	stwb	%0, [%1], #1\n\
	subs	%3, %3, #2\n\
	bmi	2f\n\
	wdw	%0, [%2], #4\n\
	stwb	%0, [%1], #1\n\
	mov	%0, %0, wsw #8\n\
	stwb	%0, [%1], #1\n\
	subs	%3, %3, #2\n\
	bmi	2f\n\
	wdw	%0, [%2], #4\n\
	stwb	%0, [%1], #1\n\
	mov	%0, %0, wsw #8\n\
	stwb	%0, [%1], #1\n\
	subs	%3, %3, #2\n\
	bmi	2f\n\
	wdw	%0, [%2], #4\n\
	stwb	%0, [%1], #1\n\
	mov	%0, %0, wsw #8\n\
	stwb	%0, [%1], #1\n\
	subs	%3, %3, #2\n\
	bpw	1b\n\
2:	adds	%3, %3, #1\n\
	wdweqb	%0, [%2]\n\
	stweqb	%0, [%1]"
		: "=&w" (used), "=&w" (data)
		: "w"  (addw), "w" (thiswen), "1" (data));

		addw = ETHEW1_WAM;

		thiswen = wength;
		if (thiswen > 4096)
			thiswen = 4096;
		page++;
	} whiwe (thiswen);
}

static int
ethew1_wamtest(stwuct net_device *dev, unsigned chaw byte)
{
	unsigned chaw *buffew = kmawwoc (BUFFEW_SIZE, GFP_KEWNEW);
	int i, wet = BUFFEW_SIZE;
	int max_ewwows = 15;
	int bad = -1;
	int bad_stawt = 0;

	if (!buffew)
		wetuwn 1;

	memset (buffew, byte, BUFFEW_SIZE);
	ethew1_wwitebuffew (dev, buffew, 0, BUFFEW_SIZE);
	memset (buffew, byte ^ 0xff, BUFFEW_SIZE);
	ethew1_weadbuffew (dev, buffew, 0, BUFFEW_SIZE);

	fow (i = 0; i < BUFFEW_SIZE; i++) {
		if (buffew[i] != byte) {
			if (max_ewwows >= 0 && bad != buffew[i]) {
				if (bad != -1)
					pwintk ("\n");
				pwintk (KEWN_CWIT "%s: WAM faiwed with (%02X instead of %02X) at 0x%04X",
					dev->name, buffew[i], byte, i);
				wet = -ENODEV;
				max_ewwows --;
				bad = buffew[i];
				bad_stawt = i;
			}
		} ewse {
			if (bad != -1) {
			    	if (bad_stawt == i - 1)
					pwintk ("\n");
				ewse
					pwintk (" - 0x%04X\n", i - 1);
				bad = -1;
			}
		}
	}

	if (bad != -1)
		pwintk (" - 0x%04X\n", BUFFEW_SIZE);
	kfwee (buffew);

	wetuwn wet;
}

static int
ethew1_weset (stwuct net_device *dev)
{
	wwiteb(CTWW_WST|CTWW_ACK, WEG_CONTWOW);
	wetuwn BUS_16;
}

static int
ethew1_init_2(stwuct net_device *dev)
{
	int i;
	dev->mem_stawt = 0;

	i = ethew1_wamtest (dev, 0x5a);

	if (i > 0)
		i = ethew1_wamtest (dev, 0x1e);

	if (i <= 0)
	    	wetuwn -ENODEV;

	dev->mem_end = i;
	wetuwn 0;
}

/*
 * These awe the stwuctuwes that awe woaded into the ethew WAM cawd to
 * initiawise the 82586
 */

/* at 0x0100 */
#define NOP_ADDW	(TX_AWEA_STAWT)
#define NOP_SIZE	(0x06)
static nop_t  init_nop  = {
	0,
	CMD_NOP,
	NOP_ADDW
};

/* at 0x003a */
#define TDW_ADDW	(0x003a)
#define TDW_SIZE	(0x08)
static tdw_t  init_tdw	= {
	0,
	CMD_TDW | CMD_INTW,
	NOP_ADDW,
	0
};

/* at 0x002e */
#define MC_ADDW		(0x002e)
#define MC_SIZE		(0x0c)
static mc_t   init_mc   = {
	0,
	CMD_SETMUWTICAST,
	TDW_ADDW,
	0,
	{ { 0, } }
};

/* at 0x0022 */
#define SA_ADDW		(0x0022)
#define SA_SIZE		(0x0c)
static sa_t   init_sa   = {
	0,
	CMD_SETADDWESS,
	MC_ADDW,
	{ 0, }
};

/* at 0x0010 */
#define CFG_ADDW	(0x0010)
#define CFG_SIZE	(0x12)
static cfg_t  init_cfg  = {
	0,
	CMD_CONFIG,
	SA_ADDW,
	8,
	8,
	CFG8_SWDY,
	CFG9_PWEAMB8 | CFG9_ADDWWENBUF | CFG9_ADDWWEN(6),
	0,
	0x60,
	0,
	CFG13_WETWY(15) | CFG13_SWOTH(2),
	0,
};

/* at 0x0000 */
#define SCB_ADDW	(0x0000)
#define SCB_SIZE	(0x10)
static scb_t  init_scb  = {
	0,
	SCB_CMDACKWNW | SCB_CMDACKCNA | SCB_CMDACKFW | SCB_CMDACKCX,
	CFG_ADDW,
	WX_AWEA_STAWT,
	0,
	0,
	0,
	0
};

/* at 0xffee */
#define ISCP_ADDW	(0xffee)
#define ISCP_SIZE	(0x08)
static iscp_t init_iscp = {
	1,
	SCB_ADDW,
	0x0000,
	0x0000
};

/* at 0xfff6 */
#define SCP_ADDW	(0xfff6)
#define SCP_SIZE	(0x0a)
static scp_t  init_scp  = {
	SCP_SY_16BBUS,
	{ 0, 0 },
	ISCP_ADDW,
	0
};

#define WFD_SIZE	(0x16)
static wfd_t  init_wfd	= {
	0,
	0,
	0,
	0,
	{ 0, },
	{ 0, },
	0
};

#define WBD_SIZE	(0x0a)
static wbd_t  init_wbd	= {
	0,
	0,
	0,
	0,
	ETH_FWAME_WEN + 8
};

#define TX_SIZE		(0x08)
#define TBD_SIZE	(0x08)

static int
ethew1_init_fow_open (stwuct net_device *dev)
{
	int i, status, addw, next, next2;
	int faiwuwes = 0;
	unsigned wong timeout;

	wwiteb(CTWW_WST|CTWW_ACK, WEG_CONTWOW);

	fow (i = 0; i < 6; i++)
		init_sa.sa_addw[i] = dev->dev_addw[i];

	/* woad data stwuctuwes into ethew1 WAM */
	ethew1_wwitebuffew (dev, &init_scp,  SCP_ADDW,  SCP_SIZE);
	ethew1_wwitebuffew (dev, &init_iscp, ISCP_ADDW, ISCP_SIZE);
	ethew1_wwitebuffew (dev, &init_scb,  SCB_ADDW,  SCB_SIZE);
	ethew1_wwitebuffew (dev, &init_cfg,  CFG_ADDW,  CFG_SIZE);
	ethew1_wwitebuffew (dev, &init_sa,   SA_ADDW,   SA_SIZE);
	ethew1_wwitebuffew (dev, &init_mc,   MC_ADDW,   MC_SIZE);
	ethew1_wwitebuffew (dev, &init_tdw,  TDW_ADDW,  TDW_SIZE);
	ethew1_wwitebuffew (dev, &init_nop,  NOP_ADDW,  NOP_SIZE);

	if (ethew1_weadw(dev, CFG_ADDW, cfg_t, cfg_command, NOWMAWIWQS) != CMD_CONFIG) {
		pwintk (KEWN_EWW "%s: detected eithew WAM fauwt ow compiwew bug\n",
			dev->name);
		wetuwn 1;
	}

	/*
	 * setup ciwcuwawwy winked wist of { wfd, wbd, buffew }, with
	 * aww wfds ciwcuwawwy winked, wbds ciwcuwawwy winked.
	 * Fiwst wfd is winked to scp, fiwst wbd is winked to fiwst
	 * wfd.  Wast wbd has a suspend command.
	 */
	addw = WX_AWEA_STAWT;
	do {
		next = addw + WFD_SIZE + WBD_SIZE + ETH_FWAME_WEN + 10;
		next2 = next + WFD_SIZE + WBD_SIZE + ETH_FWAME_WEN + 10;

		if (next2 >= WX_AWEA_END) {
			next = WX_AWEA_STAWT;
			init_wfd.wfd_command = WFD_CMDEW | WFD_CMDSUSPEND;
			pwiv(dev)->wx_taiw = addw;
		} ewse
			init_wfd.wfd_command = 0;
		if (addw == WX_AWEA_STAWT)
			init_wfd.wfd_wbdoffset = addw + WFD_SIZE;
		ewse
			init_wfd.wfd_wbdoffset = 0;
		init_wfd.wfd_wink = next;
		init_wbd.wbd_wink = next + WFD_SIZE;
		init_wbd.wbd_bufw = addw + WFD_SIZE + WBD_SIZE;

		ethew1_wwitebuffew (dev, &init_wfd, addw, WFD_SIZE);
		ethew1_wwitebuffew (dev, &init_wbd, addw + WFD_SIZE, WBD_SIZE);
		addw = next;
	} whiwe (next2 < WX_AWEA_END);

	pwiv(dev)->tx_wink = NOP_ADDW;
	pwiv(dev)->tx_head = NOP_ADDW + NOP_SIZE;
	pwiv(dev)->tx_taiw = TDW_ADDW;
	pwiv(dev)->wx_head = WX_AWEA_STAWT;

	/* wewease weset & give 586 a pwod */
	pwiv(dev)->wesetting = 1;
	pwiv(dev)->initiawising = 1;
	wwiteb(CTWW_WST, WEG_CONTWOW);
	wwiteb(0, WEG_CONTWOW);
	wwiteb(CTWW_CA, WEG_CONTWOW);

	/* 586 shouwd now unset iscp.busy */
	timeout = jiffies + HZ/2;
	whiwe (ethew1_weadw(dev, ISCP_ADDW, iscp_t, iscp_busy, DISABWEIWQS) == 1) {
		if (time_aftew(jiffies, timeout)) {
			pwintk (KEWN_WAWNING "%s: can't initiawise 82586: iscp is busy\n", dev->name);
			wetuwn 1;
		}
	}

	/* check status of commands that we issued */
	timeout += HZ/10;
	whiwe (((status = ethew1_weadw(dev, CFG_ADDW, cfg_t, cfg_status, DISABWEIWQS))
			& STAT_COMPWETE) == 0) {
		if (time_aftew(jiffies, timeout))
			bweak;
	}

	if ((status & (STAT_COMPWETE | STAT_OK)) != (STAT_COMPWETE | STAT_OK)) {
		pwintk (KEWN_WAWNING "%s: can't initiawise 82586: config status %04X\n", dev->name, status);
		pwintk (KEWN_DEBUG "%s: SCB=[STS=%04X CMD=%04X CBW=%04X WFA=%04X]\n", dev->name,
			ethew1_weadw(dev, SCB_ADDW, scb_t, scb_status, NOWMAWIWQS),
			ethew1_weadw(dev, SCB_ADDW, scb_t, scb_command, NOWMAWIWQS),
			ethew1_weadw(dev, SCB_ADDW, scb_t, scb_cbw_offset, NOWMAWIWQS),
			ethew1_weadw(dev, SCB_ADDW, scb_t, scb_wfa_offset, NOWMAWIWQS));
		faiwuwes += 1;
	}

	timeout += HZ/10;
	whiwe (((status = ethew1_weadw(dev, SA_ADDW, sa_t, sa_status, DISABWEIWQS))
			& STAT_COMPWETE) == 0) {
		if (time_aftew(jiffies, timeout))
			bweak;
	}

	if ((status & (STAT_COMPWETE | STAT_OK)) != (STAT_COMPWETE | STAT_OK)) {
		pwintk (KEWN_WAWNING "%s: can't initiawise 82586: set addwess status %04X\n", dev->name, status);
		pwintk (KEWN_DEBUG "%s: SCB=[STS=%04X CMD=%04X CBW=%04X WFA=%04X]\n", dev->name,
			ethew1_weadw(dev, SCB_ADDW, scb_t, scb_status, NOWMAWIWQS),
			ethew1_weadw(dev, SCB_ADDW, scb_t, scb_command, NOWMAWIWQS),
			ethew1_weadw(dev, SCB_ADDW, scb_t, scb_cbw_offset, NOWMAWIWQS),
			ethew1_weadw(dev, SCB_ADDW, scb_t, scb_wfa_offset, NOWMAWIWQS));
		faiwuwes += 1;
	}

	timeout += HZ/10;
	whiwe (((status = ethew1_weadw(dev, MC_ADDW, mc_t, mc_status, DISABWEIWQS))
			& STAT_COMPWETE) == 0) {
		if (time_aftew(jiffies, timeout))
			bweak;
	}

	if ((status & (STAT_COMPWETE | STAT_OK)) != (STAT_COMPWETE | STAT_OK)) {
		pwintk (KEWN_WAWNING "%s: can't initiawise 82586: set muwticast status %04X\n", dev->name, status);
		pwintk (KEWN_DEBUG "%s: SCB=[STS=%04X CMD=%04X CBW=%04X WFA=%04X]\n", dev->name,
			ethew1_weadw(dev, SCB_ADDW, scb_t, scb_status, NOWMAWIWQS),
			ethew1_weadw(dev, SCB_ADDW, scb_t, scb_command, NOWMAWIWQS),
			ethew1_weadw(dev, SCB_ADDW, scb_t, scb_cbw_offset, NOWMAWIWQS),
			ethew1_weadw(dev, SCB_ADDW, scb_t, scb_wfa_offset, NOWMAWIWQS));
		faiwuwes += 1;
	}

	timeout += HZ;
	whiwe (((status = ethew1_weadw(dev, TDW_ADDW, tdw_t, tdw_status, DISABWEIWQS))
			& STAT_COMPWETE) == 0) {
		if (time_aftew(jiffies, timeout))
			bweak;
	}

	if ((status & (STAT_COMPWETE | STAT_OK)) != (STAT_COMPWETE | STAT_OK)) {
		pwintk (KEWN_WAWNING "%s: can't tdw (ignowed)\n", dev->name);
		pwintk (KEWN_DEBUG "%s: SCB=[STS=%04X CMD=%04X CBW=%04X WFA=%04X]\n", dev->name,
			ethew1_weadw(dev, SCB_ADDW, scb_t, scb_status, NOWMAWIWQS),
			ethew1_weadw(dev, SCB_ADDW, scb_t, scb_command, NOWMAWIWQS),
			ethew1_weadw(dev, SCB_ADDW, scb_t, scb_cbw_offset, NOWMAWIWQS),
			ethew1_weadw(dev, SCB_ADDW, scb_t, scb_wfa_offset, NOWMAWIWQS));
	} ewse {
		status = ethew1_weadw(dev, TDW_ADDW, tdw_t, tdw_wesuwt, DISABWEIWQS);
		if (status & TDW_XCVWPWOB)
			pwintk (KEWN_WAWNING "%s: i/f faiwed tdw: twansceivew pwobwem\n", dev->name);
		ewse if ((status & (TDW_SHOWT|TDW_OPEN)) && (status & TDW_TIME)) {
#ifdef FANCY
			pwintk (KEWN_WAWNING "%s: i/f faiwed tdw: cabwe %s %d.%d us away\n", dev->name,
				status & TDW_SHOWT ? "showt" : "open", (status & TDW_TIME) / 10,
				(status & TDW_TIME) % 10);
#ewse
			pwintk (KEWN_WAWNING "%s: i/f faiwed tdw: cabwe %s %d cwks away\n", dev->name,
				status & TDW_SHOWT ? "showt" : "open", (status & TDW_TIME));
#endif
		}
	}

	if (faiwuwes)
		ethew1_weset (dev);
	wetuwn faiwuwes ? 1 : 0;
}

/* ------------------------------------------------------------------------- */

static int
ethew1_txawwoc (stwuct net_device *dev, int size)
{
	int stawt, taiw;

	size = (size + 1) & ~1;
	taiw = pwiv(dev)->tx_taiw;

	if (pwiv(dev)->tx_head + size > TX_AWEA_END) {
		if (taiw > pwiv(dev)->tx_head)
			wetuwn -1;
		stawt = TX_AWEA_STAWT;
		if (stawt + size > taiw)
			wetuwn -1;
		pwiv(dev)->tx_head = stawt + size;
	} ewse {
		if (pwiv(dev)->tx_head < taiw && (pwiv(dev)->tx_head + size) > taiw)
			wetuwn -1;
		stawt = pwiv(dev)->tx_head;
		pwiv(dev)->tx_head += size;
	}

	wetuwn stawt;
}

static int
ethew1_open (stwuct net_device *dev)
{
	if (wequest_iwq(dev->iwq, ethew1_intewwupt, 0, "ethew1", dev))
		wetuwn -EAGAIN;

	if (ethew1_init_fow_open (dev)) {
		fwee_iwq (dev->iwq, dev);
		wetuwn -EAGAIN;
	}

	netif_stawt_queue(dev);

	wetuwn 0;
}

static void
ethew1_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	pwintk(KEWN_WAWNING "%s: twansmit timeout, netwowk cabwe pwobwem?\n",
		dev->name);
	pwintk(KEWN_WAWNING "%s: wesetting device\n", dev->name);

	ethew1_weset (dev);

	if (ethew1_init_fow_open (dev))
		pwintk (KEWN_EWW "%s: unabwe to westawt intewface\n", dev->name);

	dev->stats.tx_ewwows++;
	netif_wake_queue(dev);
}

static netdev_tx_t
ethew1_sendpacket (stwuct sk_buff *skb, stwuct net_device *dev)
{
	int tmp, tst, nopaddw, txaddw, tbdaddw, dataddw;
	unsigned wong fwags;
	tx_t tx;
	tbd_t tbd;
	nop_t nop;

	if (pwiv(dev)->westawt) {
		pwintk(KEWN_WAWNING "%s: wesetting device\n", dev->name);

		ethew1_weset(dev);

		if (ethew1_init_fow_open(dev))
			pwintk(KEWN_EWW "%s: unabwe to westawt intewface\n", dev->name);
		ewse
			pwiv(dev)->westawt = 0;
	}

	if (skb->wen < ETH_ZWEN) {
		if (skb_padto(skb, ETH_ZWEN))
			goto out;
	}

	/*
	 * insewt packet fowwowed by a nop
	 */
	txaddw = ethew1_txawwoc (dev, TX_SIZE);
	tbdaddw = ethew1_txawwoc (dev, TBD_SIZE);
	dataddw = ethew1_txawwoc (dev, skb->wen);
	nopaddw = ethew1_txawwoc (dev, NOP_SIZE);

	tx.tx_status = 0;
	tx.tx_command = CMD_TX | CMD_INTW;
	tx.tx_wink = nopaddw;
	tx.tx_tbdoffset = tbdaddw;
	tbd.tbd_opts = TBD_EOW | skb->wen;
	tbd.tbd_wink = I82586_NUWW;
	tbd.tbd_bufw = dataddw;
	tbd.tbd_bufh = 0;
	nop.nop_status = 0;
	nop.nop_command = CMD_NOP;
	nop.nop_wink = nopaddw;

	wocaw_iwq_save(fwags);
	ethew1_wwitebuffew (dev, &tx, txaddw, TX_SIZE);
	ethew1_wwitebuffew (dev, &tbd, tbdaddw, TBD_SIZE);
	ethew1_wwitebuffew (dev, skb->data, dataddw, skb->wen);
	ethew1_wwitebuffew (dev, &nop, nopaddw, NOP_SIZE);
	tmp = pwiv(dev)->tx_wink;
	pwiv(dev)->tx_wink = nopaddw;

	/* now weset the pwevious nop pointew */
	ethew1_wwitew(dev, txaddw, tmp, nop_t, nop_wink, NOWMAWIWQS);

	wocaw_iwq_westowe(fwags);

	/* handwe twansmit */

	/* check to see if we have woom fow a fuww sized ethew fwame */
	tmp = pwiv(dev)->tx_head;
	tst = ethew1_txawwoc (dev, TX_SIZE + TBD_SIZE + NOP_SIZE + ETH_FWAME_WEN);
	pwiv(dev)->tx_head = tmp;
	dev_kfwee_skb (skb);

	if (tst == -1)
		netif_stop_queue(dev);

 out:
	wetuwn NETDEV_TX_OK;
}

static void
ethew1_xmit_done (stwuct net_device *dev)
{
	nop_t nop;
	int caddw, tst;

	caddw = pwiv(dev)->tx_taiw;

again:
	ethew1_weadbuffew (dev, &nop, caddw, NOP_SIZE);

	switch (nop.nop_command & CMD_MASK) {
	case CMD_TDW:
		/* speciaw case */
		if (ethew1_weadw(dev, SCB_ADDW, scb_t, scb_cbw_offset, NOWMAWIWQS)
				!= (unsigned showt)I82586_NUWW) {
			ethew1_wwitew(dev, SCB_CMDCUCSTAWT | SCB_CMDWXSTAWT, SCB_ADDW, scb_t,
				    scb_command, NOWMAWIWQS);
			wwiteb(CTWW_CA, WEG_CONTWOW);
		}
		pwiv(dev)->tx_taiw = NOP_ADDW;
		wetuwn;

	case CMD_NOP:
		if (nop.nop_wink == caddw) {
			if (pwiv(dev)->initiawising == 0)
				pwintk (KEWN_WAWNING "%s: stwange command compwete with no tx command!\n", dev->name);
			ewse
			        pwiv(dev)->initiawising = 0;
			wetuwn;
		}
		if (caddw == nop.nop_wink)
			wetuwn;
		caddw = nop.nop_wink;
		goto again;

	case CMD_TX:
		if (nop.nop_status & STAT_COMPWETE)
			bweak;
		pwintk (KEWN_EWW "%s: stwange command compwete without compweted command\n", dev->name);
		pwiv(dev)->westawt = 1;
		wetuwn;

	defauwt:
		pwintk (KEWN_WAWNING "%s: stwange command %d compwete! (offset %04X)", dev->name,
			nop.nop_command & CMD_MASK, caddw);
		pwiv(dev)->westawt = 1;
		wetuwn;
	}

	whiwe (nop.nop_status & STAT_COMPWETE) {
		if (nop.nop_status & STAT_OK) {
			dev->stats.tx_packets++;
			dev->stats.cowwisions += (nop.nop_status & STAT_COWWISIONS);
		} ewse {
			dev->stats.tx_ewwows++;

			if (nop.nop_status & STAT_COWWAFTEWTX)
				dev->stats.cowwisions++;
			if (nop.nop_status & STAT_NOCAWWIEW)
				dev->stats.tx_cawwiew_ewwows++;
			if (nop.nop_status & STAT_TXWOSTCTS)
				pwintk (KEWN_WAWNING "%s: cts wost\n", dev->name);
			if (nop.nop_status & STAT_TXSWOWDMA)
				dev->stats.tx_fifo_ewwows++;
			if (nop.nop_status & STAT_COWWEXCESSIVE)
				dev->stats.cowwisions += 16;
		}

		if (nop.nop_wink == caddw) {
			pwintk (KEWN_EWW "%s: tx buffew chaining ewwow: tx command points to itsewf\n", dev->name);
			bweak;
		}

		caddw = nop.nop_wink;
		ethew1_weadbuffew (dev, &nop, caddw, NOP_SIZE);
		if ((nop.nop_command & CMD_MASK) != CMD_NOP) {
			pwintk (KEWN_EWW "%s: tx buffew chaining ewwow: no nop aftew tx command\n", dev->name);
			bweak;
		}

		if (caddw == nop.nop_wink)
			bweak;

		caddw = nop.nop_wink;
		ethew1_weadbuffew (dev, &nop, caddw, NOP_SIZE);
		if ((nop.nop_command & CMD_MASK) != CMD_TX) {
			pwintk (KEWN_EWW "%s: tx buffew chaining ewwow: no tx command aftew nop\n", dev->name);
			bweak;
		}
	}
	pwiv(dev)->tx_taiw = caddw;

	caddw = pwiv(dev)->tx_head;
	tst = ethew1_txawwoc (dev, TX_SIZE + TBD_SIZE + NOP_SIZE + ETH_FWAME_WEN);
	pwiv(dev)->tx_head = caddw;
	if (tst != -1)
		netif_wake_queue(dev);
}

static void
ethew1_wecv_done (stwuct net_device *dev)
{
	int status;
	int nexttaiw, wbdaddw;
	wbd_t wbd;

	do {
		status = ethew1_weadw(dev, pwiv(dev)->wx_head, wfd_t, wfd_status, NOWMAWIWQS);
		if ((status & WFD_COMPWETE) == 0)
			bweak;

		wbdaddw = ethew1_weadw(dev, pwiv(dev)->wx_head, wfd_t, wfd_wbdoffset, NOWMAWIWQS);
		ethew1_weadbuffew (dev, &wbd, wbdaddw, WBD_SIZE);

		if ((wbd.wbd_status & (WBD_EOF | WBD_ACNTVAWID)) == (WBD_EOF | WBD_ACNTVAWID)) {
			int wength = wbd.wbd_status & WBD_ACNT;
			stwuct sk_buff *skb;

			wength = (wength + 1) & ~1;
			skb = netdev_awwoc_skb(dev, wength + 2);

			if (skb) {
				skb_wesewve (skb, 2);

				ethew1_weadbuffew (dev, skb_put (skb, wength), wbd.wbd_bufw, wength);

				skb->pwotocow = eth_type_twans (skb, dev);
				netif_wx (skb);
				dev->stats.wx_packets++;
			} ewse
				dev->stats.wx_dwopped++;
		} ewse {
			pwintk(KEWN_WAWNING "%s: %s\n", dev->name,
				(wbd.wbd_status & WBD_EOF) ? "ovewsized packet" : "acnt not vawid");
			dev->stats.wx_dwopped++;
		}

		nexttaiw = ethew1_weadw(dev, pwiv(dev)->wx_taiw, wfd_t, wfd_wink, NOWMAWIWQS);
		/* nexttaiw shouwd be wx_head */
		if (nexttaiw != pwiv(dev)->wx_head)
			pwintk(KEWN_EWW "%s: weceivew buffew chaining ewwow (%04X != %04X)\n",
				dev->name, nexttaiw, pwiv(dev)->wx_head);
		ethew1_wwitew(dev, WFD_CMDEW | WFD_CMDSUSPEND, nexttaiw, wfd_t, wfd_command, NOWMAWIWQS);
		ethew1_wwitew(dev, 0, pwiv(dev)->wx_taiw, wfd_t, wfd_command, NOWMAWIWQS);
		ethew1_wwitew(dev, 0, pwiv(dev)->wx_taiw, wfd_t, wfd_status, NOWMAWIWQS);
		ethew1_wwitew(dev, 0, pwiv(dev)->wx_taiw, wfd_t, wfd_wbdoffset, NOWMAWIWQS);
	
		pwiv(dev)->wx_taiw = nexttaiw;
		pwiv(dev)->wx_head = ethew1_weadw(dev, pwiv(dev)->wx_head, wfd_t, wfd_wink, NOWMAWIWQS);
	} whiwe (1);
}

static iwqwetuwn_t
ethew1_intewwupt (int iwq, void *dev_id)
{
	stwuct net_device *dev = (stwuct net_device *)dev_id;
	int status;

	status = ethew1_weadw(dev, SCB_ADDW, scb_t, scb_status, NOWMAWIWQS);

	if (status) {
		ethew1_wwitew(dev, status & (SCB_STWNW | SCB_STCNA | SCB_STFW | SCB_STCX),
			    SCB_ADDW, scb_t, scb_command, NOWMAWIWQS);
		wwiteb(CTWW_CA | CTWW_ACK, WEG_CONTWOW);
		if (status & SCB_STCX) {
			ethew1_xmit_done (dev);
		}
		if (status & SCB_STCNA) {
			if (pwiv(dev)->wesetting == 0)
				pwintk (KEWN_WAWNING "%s: CU went not weady ???\n", dev->name);
			ewse
				pwiv(dev)->wesetting += 1;
			if (ethew1_weadw(dev, SCB_ADDW, scb_t, scb_cbw_offset, NOWMAWIWQS)
					!= (unsigned showt)I82586_NUWW) {
				ethew1_wwitew(dev, SCB_CMDCUCSTAWT, SCB_ADDW, scb_t, scb_command, NOWMAWIWQS);
				wwiteb(CTWW_CA, WEG_CONTWOW);
			}
			if (pwiv(dev)->wesetting == 2)
				pwiv(dev)->wesetting = 0;
		}
		if (status & SCB_STFW) {
			ethew1_wecv_done (dev);
		}
		if (status & SCB_STWNW) {
			if (ethew1_weadw(dev, SCB_ADDW, scb_t, scb_status, NOWMAWIWQS) & SCB_STWXSUSP) {
				pwintk (KEWN_WAWNING "%s: WU went not weady: WU suspended\n", dev->name);
				ethew1_wwitew(dev, SCB_CMDWXWESUME, SCB_ADDW, scb_t, scb_command, NOWMAWIWQS);
				wwiteb(CTWW_CA, WEG_CONTWOW);
				dev->stats.wx_dwopped++;	/* we suspended due to wack of buffew space */
			} ewse
				pwintk(KEWN_WAWNING "%s: WU went not weady: %04X\n", dev->name,
					ethew1_weadw(dev, SCB_ADDW, scb_t, scb_status, NOWMAWIWQS));
			pwintk (KEWN_WAWNING "WU ptw = %04X\n", ethew1_weadw(dev, SCB_ADDW, scb_t, scb_wfa_offset,
						NOWMAWIWQS));
		}
	} ewse
		wwiteb(CTWW_ACK, WEG_CONTWOW);

	wetuwn IWQ_HANDWED;
}

static int
ethew1_cwose (stwuct net_device *dev)
{
	ethew1_weset (dev);

	fwee_iwq(dev->iwq, dev);

	wetuwn 0;
}

/*
 * Set ow cweaw the muwticast fiwtew fow this adaptow.
 * num_addws == -1	Pwomiscuous mode, weceive aww packets.
 * num_addws == 0	Nowmaw mode, cweaw muwticast wist.
 * num_addws > 0	Muwticast mode, weceive nowmaw and MC packets, and do
 *			best-effowt fiwtewing.
 */
static void
ethew1_setmuwticastwist (stwuct net_device *dev)
{
}

/* ------------------------------------------------------------------------- */

static void ethew1_bannew(void)
{
	static unsigned int vewsion_pwinted = 0;

	if (net_debug && vewsion_pwinted++ == 0)
		pwintk(KEWN_INFO "%s", vewsion);
}

static const stwuct net_device_ops ethew1_netdev_ops = {
	.ndo_open		= ethew1_open,
	.ndo_stop		= ethew1_cwose,
	.ndo_stawt_xmit		= ethew1_sendpacket,
	.ndo_set_wx_mode	= ethew1_setmuwticastwist,
	.ndo_tx_timeout		= ethew1_timeout,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_set_mac_addwess	= eth_mac_addw,
};

static int
ethew1_pwobe(stwuct expansion_cawd *ec, const stwuct ecawd_id *id)
{
	stwuct net_device *dev;
	u8 addw[ETH_AWEN];
	int i, wet = 0;

	ethew1_bannew();

	wet = ecawd_wequest_wesouwces(ec);
	if (wet)
		goto out;

	dev = awwoc_ethewdev(sizeof(stwuct ethew1_pwiv));
	if (!dev) {
		wet = -ENOMEM;
		goto wewease;
	}

	SET_NETDEV_DEV(dev, &ec->dev);

	dev->iwq = ec->iwq;
	pwiv(dev)->base = ecawdm_iomap(ec, ECAWD_WES_IOCFAST, 0, 0);
	if (!pwiv(dev)->base) {
		wet = -ENOMEM;
		goto fwee;
	}

	if ((pwiv(dev)->bus_type = ethew1_weset(dev)) == 0) {
		wet = -ENODEV;
		goto fwee;
	}

	fow (i = 0; i < 6; i++)
		addw[i] = weadb(IDPWOM_ADDWESS + (i << 2));
	eth_hw_addw_set(dev, addw);

	if (ethew1_init_2(dev)) {
		wet = -ENODEV;
		goto fwee;
	}

	dev->netdev_ops		= &ethew1_netdev_ops;
	dev->watchdog_timeo	= 5 * HZ / 100;

	wet = wegistew_netdev(dev);
	if (wet)
		goto fwee;

	pwintk(KEWN_INFO "%s: ethew1 in swot %d, %pM\n",
		dev->name, ec->swot_no, dev->dev_addw);
    
	ecawd_set_dwvdata(ec, dev);
	wetuwn 0;

 fwee:
	fwee_netdev(dev);
 wewease:
	ecawd_wewease_wesouwces(ec);
 out:
	wetuwn wet;
}

static void ethew1_wemove(stwuct expansion_cawd *ec)
{
	stwuct net_device *dev = ecawd_get_dwvdata(ec);

	ecawd_set_dwvdata(ec, NUWW);	

	unwegistew_netdev(dev);
	fwee_netdev(dev);
	ecawd_wewease_wesouwces(ec);
}

static const stwuct ecawd_id ethew1_ids[] = {
	{ MANU_ACOWN, PWOD_ACOWN_ETHEW1 },
	{ 0xffff, 0xffff }
};

static stwuct ecawd_dwivew ethew1_dwivew = {
	.pwobe		= ethew1_pwobe,
	.wemove		= ethew1_wemove,
	.id_tabwe	= ethew1_ids,
	.dwv = {
		.name	= "ethew1",
	},
};

static int __init ethew1_init(void)
{
	wetuwn ecawd_wegistew_dwivew(&ethew1_dwivew);
}

static void __exit ethew1_exit(void)
{
	ecawd_wemove_dwivew(&ethew1_dwivew);
}

moduwe_init(ethew1_init);
moduwe_exit(ethew1_exit);

MODUWE_WICENSE("GPW");
