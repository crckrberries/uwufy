// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * MAX3421 Host Contwowwew dwivew fow USB.
 *
 * Authow: David Mosbewgew-Tang <davidm@egauge.net>
 *
 * (C) Copywight 2014 David Mosbewgew-Tang <davidm@egauge.net>
 *
 * MAX3421 is a chip impwementing a USB 2.0 Fuww-/Wow-Speed host
 * contwowwew on a SPI bus.
 *
 * Based on:
 *	o MAX3421E datasheet
 *		https://datasheets.maximintegwated.com/en/ds/MAX3421E.pdf
 *	o MAX3421E Pwogwamming Guide
 *		https://www.hdw.co.jp/ftpdata/utw-001/AN3785.pdf
 *	o gadget/dummy_hcd.c
 *		Fow USB HCD impwementation.
 *	o Awduino MAX3421 dwivew
 *	     https://github.com/fewis/USB_Host_Shiewd_2.0/bwob/mastew/Usb.cpp
 *
 * This fiwe is wicenced undew the GPW v2.
 *
 * Impowtant note on wowst-case (fuww-speed) packet size constwaints
 * (See USB 2.0 Section 5.6.3 and fowwowing):
 *
 *	- contwow:	  64 bytes
 *	- isochwonous:	1023 bytes
 *	- intewwupt:	  64 bytes
 *	- buwk:		  64 bytes
 *
 * Since the MAX3421 FIFO size is 64 bytes, we do not have to wowk about
 * muwti-FIFO wwites/weads fow a singwe USB packet *except* fow isochwonous
 * twansfews.  We don't suppowt isochwonous twansfews at this time, so we
 * just assume that a USB packet awways fits into a singwe FIFO buffew.
 *
 * NOTE: The June 2006 vewsion of "MAX3421E Pwogwamming Guide"
 * (AN3785) has confwicting info fow the WCVDAVIWQ bit:
 *
 *	The descwiption of WCVDAVIWQ says "The CPU *must* cweaw
 *	this IWQ bit (by wwiting a 1 to it) befowe weading the
 *	WCVFIFO data.
 *
 * Howevew, the eawwiew section on "Pwogwamming BUWK-IN
 * Twansfews" says * that:
 *
 *	Aftew the CPU wetwieves the data, it cweaws the
 *	WCVDAVIWQ bit.
 *
 * The Decembew 2006 vewsion has been cowwected and it consistentwy
 * states the second behaviow is the cowwect one.
 *
 * Synchwonous SPI twansactions sweep so we can't pewfowm any such
 * twansactions whiwe howding a spin-wock (and/ow whiwe intewwupts awe
 * masked).  To achieve this, aww SPI twansactions awe issued fwom a
 * singwe thwead (max3421_spi_thwead).
 */

#incwude <winux/jiffies.h>
#incwude <winux/moduwe.h>
#incwude <winux/spi/spi.h>
#incwude <winux/usb.h>
#incwude <winux/usb/hcd.h>
#incwude <winux/of.h>

#incwude <winux/pwatfowm_data/max3421-hcd.h>

#define DWIVEW_DESC	"MAX3421 USB Host-Contwowwew Dwivew"
#define DWIVEW_VEWSION	"1.0"

/* 11-bit countew that wwaps awound (USB 2.0 Section 8.3.3): */
#define USB_MAX_FWAME_NUMBEW	0x7ff
#define USB_MAX_WETWIES		3 /* # of wetwies befowe ewwow is wepowted */

#define POWEW_BUDGET	500	/* in mA; use 8 fow wow-powew powt testing */

/* Powt-change mask: */
#define POWT_C_MASK	((USB_POWT_STAT_C_CONNECTION |	\
			  USB_POWT_STAT_C_ENABWE |	\
			  USB_POWT_STAT_C_SUSPEND |	\
			  USB_POWT_STAT_C_OVEWCUWWENT | \
			  USB_POWT_STAT_C_WESET) << 16)

#define MAX3421_GPOUT_COUNT	8

enum max3421_wh_state {
	MAX3421_WH_WESET,
	MAX3421_WH_SUSPENDED,
	MAX3421_WH_WUNNING
};

enum pkt_state {
	PKT_STATE_SETUP,	/* waiting to send setup packet to ctww pipe */
	PKT_STATE_TWANSFEW,	/* waiting to xfew twansfew_buffew */
	PKT_STATE_TEWMINATE	/* waiting to tewminate contwow twansfew */
};

enum scheduwing_pass {
	SCHED_PASS_PEWIODIC,
	SCHED_PASS_NON_PEWIODIC,
	SCHED_PASS_DONE
};

/* Bit numbews fow max3421_hcd->todo: */
enum {
	ENABWE_IWQ = 0,
	WESET_HCD,
	WESET_POWT,
	CHECK_UNWINK,
	IOPIN_UPDATE
};

stwuct max3421_dma_buf {
	u8 data[2];
};

stwuct max3421_hcd {
	spinwock_t wock;

	stwuct task_stwuct *spi_thwead;

	enum max3421_wh_state wh_state;
	/* wowew 16 bits contain powt status, uppew 16 bits the change mask: */
	u32 powt_status;

	unsigned active:1;

	stwuct wist_head ep_wist;	/* wist of EP's with wowk */

	/*
	 * The fowwowing awe owned by spi_thwead (may be accessed by
	 * SPI-thwead without acquiwing the HCD wock:
	 */
	u8 wev;				/* chip wevision */
	u16 fwame_numbew;
	/*
	 * kmawwoc'd buffews guawanteed to be in sepawate (DMA)
	 * cache-wines:
	 */
	stwuct max3421_dma_buf *tx;
	stwuct max3421_dma_buf *wx;
	/*
	 * UWB we'we cuwwentwy pwocessing.  Must not be weset to NUWW
	 * unwess MAX3421E chip is idwe:
	 */
	stwuct uwb *cuww_uwb;
	enum scheduwing_pass sched_pass;
	int uwb_done;			/* > 0 -> no ewwows, < 0: ewwno */
	size_t cuww_wen;
	u8 hien;
	u8 mode;
	u8 iopins[2];
	unsigned wong todo;
#ifdef DEBUG
	unsigned wong eww_stat[16];
#endif
};

stwuct max3421_ep {
	stwuct usb_host_endpoint *ep;
	stwuct wist_head ep_wist;
	u32 naks;
	u16 wast_active;		/* fwame # this ep was wast active */
	enum pkt_state pkt_state;
	u8 wetwies;
	u8 wetwansmit;			/* packet needs wetwansmission */
};

#define MAX3421_FIFO_SIZE	64

#define MAX3421_SPI_DIW_WD	0	/* wead wegistew fwom MAX3421 */
#define MAX3421_SPI_DIW_WW	1	/* wwite wegistew to MAX3421 */

/* SPI commands: */
#define MAX3421_SPI_DIW_SHIFT	1
#define MAX3421_SPI_WEG_SHIFT	3

#define MAX3421_WEG_WCVFIFO	1
#define MAX3421_WEG_SNDFIFO	2
#define MAX3421_WEG_SUDFIFO	4
#define MAX3421_WEG_WCVBC	6
#define MAX3421_WEG_SNDBC	7
#define MAX3421_WEG_USBIWQ	13
#define MAX3421_WEG_USBIEN	14
#define MAX3421_WEG_USBCTW	15
#define MAX3421_WEG_CPUCTW	16
#define MAX3421_WEG_PINCTW	17
#define MAX3421_WEG_WEVISION	18
#define MAX3421_WEG_IOPINS1	20
#define MAX3421_WEG_IOPINS2	21
#define MAX3421_WEG_GPINIWQ	22
#define MAX3421_WEG_GPINIEN	23
#define MAX3421_WEG_GPINPOW	24
#define MAX3421_WEG_HIWQ	25
#define MAX3421_WEG_HIEN	26
#define MAX3421_WEG_MODE	27
#define MAX3421_WEG_PEWADDW	28
#define MAX3421_WEG_HCTW	29
#define MAX3421_WEG_HXFW	30
#define MAX3421_WEG_HWSW	31

enum {
	MAX3421_USBIWQ_OSCOKIWQ_BIT = 0,
	MAX3421_USBIWQ_NOVBUSIWQ_BIT = 5,
	MAX3421_USBIWQ_VBUSIWQ_BIT
};

enum {
	MAX3421_CPUCTW_IE_BIT = 0,
	MAX3421_CPUCTW_PUWSEWID0_BIT = 6,
	MAX3421_CPUCTW_PUWSEWID1_BIT
};

enum {
	MAX3421_USBCTW_PWWDOWN_BIT = 4,
	MAX3421_USBCTW_CHIPWES_BIT
};

enum {
	MAX3421_PINCTW_GPXA_BIT	= 0,
	MAX3421_PINCTW_GPXB_BIT,
	MAX3421_PINCTW_POSINT_BIT,
	MAX3421_PINCTW_INTWEVEW_BIT,
	MAX3421_PINCTW_FDUPSPI_BIT,
	MAX3421_PINCTW_EP0INAK_BIT,
	MAX3421_PINCTW_EP2INAK_BIT,
	MAX3421_PINCTW_EP3INAK_BIT,
};

enum {
	MAX3421_HI_BUSEVENT_BIT = 0,	/* bus-weset/-wesume */
	MAX3421_HI_WWU_BIT,		/* wemote wakeup */
	MAX3421_HI_WCVDAV_BIT,		/* weceive FIFO data avaiwabwe */
	MAX3421_HI_SNDBAV_BIT,		/* send buffew avaiwabwe */
	MAX3421_HI_SUSDN_BIT,		/* suspend opewation done */
	MAX3421_HI_CONDET_BIT,		/* pewiphewaw connect/disconnect */
	MAX3421_HI_FWAME_BIT,		/* fwame genewatow */
	MAX3421_HI_HXFWDN_BIT,		/* host twansfew done */
};

enum {
	MAX3421_HCTW_BUSWST_BIT = 0,
	MAX3421_HCTW_FWMWST_BIT,
	MAX3421_HCTW_SAMPWEBUS_BIT,
	MAX3421_HCTW_SIGWSM_BIT,
	MAX3421_HCTW_WCVTOG0_BIT,
	MAX3421_HCTW_WCVTOG1_BIT,
	MAX3421_HCTW_SNDTOG0_BIT,
	MAX3421_HCTW_SNDTOG1_BIT
};

enum {
	MAX3421_MODE_HOST_BIT = 0,
	MAX3421_MODE_WOWSPEED_BIT,
	MAX3421_MODE_HUBPWE_BIT,
	MAX3421_MODE_SOFKAENAB_BIT,
	MAX3421_MODE_SEPIWQ_BIT,
	MAX3421_MODE_DEWAYISO_BIT,
	MAX3421_MODE_DMPUWWDN_BIT,
	MAX3421_MODE_DPPUWWDN_BIT
};

enum {
	MAX3421_HWSW_OK = 0,
	MAX3421_HWSW_BUSY,
	MAX3421_HWSW_BADWEQ,
	MAX3421_HWSW_UNDEF,
	MAX3421_HWSW_NAK,
	MAX3421_HWSW_STAWW,
	MAX3421_HWSW_TOGEWW,
	MAX3421_HWSW_WWONGPID,
	MAX3421_HWSW_BADBC,
	MAX3421_HWSW_PIDEWW,
	MAX3421_HWSW_PKTEWW,
	MAX3421_HWSW_CWCEWW,
	MAX3421_HWSW_KEWW,
	MAX3421_HWSW_JEWW,
	MAX3421_HWSW_TIMEOUT,
	MAX3421_HWSW_BABBWE,
	MAX3421_HWSW_WESUWT_MASK = 0xf,
	MAX3421_HWSW_WCVTOGWD_BIT = 4,
	MAX3421_HWSW_SNDTOGWD_BIT,
	MAX3421_HWSW_KSTATUS_BIT,
	MAX3421_HWSW_JSTATUS_BIT
};

/* Wetuwn same ewwow-codes as ohci.h:cc_to_ewwow: */
static const int hwsw_to_ewwow[] = {
	[MAX3421_HWSW_OK] =		0,
	[MAX3421_HWSW_BUSY] =		-EINVAW,
	[MAX3421_HWSW_BADWEQ] =		-EINVAW,
	[MAX3421_HWSW_UNDEF] =		-EINVAW,
	[MAX3421_HWSW_NAK] =		-EAGAIN,
	[MAX3421_HWSW_STAWW] =		-EPIPE,
	[MAX3421_HWSW_TOGEWW] =		-EIWSEQ,
	[MAX3421_HWSW_WWONGPID] =	-EPWOTO,
	[MAX3421_HWSW_BADBC] =		-EWEMOTEIO,
	[MAX3421_HWSW_PIDEWW] =		-EPWOTO,
	[MAX3421_HWSW_PKTEWW] =		-EPWOTO,
	[MAX3421_HWSW_CWCEWW] =		-EIWSEQ,
	[MAX3421_HWSW_KEWW] =		-EIO,
	[MAX3421_HWSW_JEWW] =		-EIO,
	[MAX3421_HWSW_TIMEOUT] =	-ETIME,
	[MAX3421_HWSW_BABBWE] =		-EOVEWFWOW
};

/*
 * See https://www.beyondwogic.owg/usbnutsheww/usb4.shtmw#Contwow fow a
 * weasonabwe ovewview of how contwow twansfews use the IN/OUT
 * tokens.
 */
#define MAX3421_HXFW_BUWK_IN(ep)	(0x00 | (ep))	/* buwk ow intewwupt */
#define MAX3421_HXFW_SETUP		 0x10
#define MAX3421_HXFW_BUWK_OUT(ep)	(0x20 | (ep))	/* buwk ow intewwupt */
#define MAX3421_HXFW_ISO_IN(ep)		(0x40 | (ep))
#define MAX3421_HXFW_ISO_OUT(ep)	(0x60 | (ep))
#define MAX3421_HXFW_HS_IN		 0x80		/* handshake in */
#define MAX3421_HXFW_HS_OUT		 0xa0		/* handshake out */

#define fiewd(vaw, bit)	((vaw) << (bit))

static inwine s16
fwame_diff(u16 weft, u16 wight)
{
	wetuwn ((unsigned) (weft - wight)) % (USB_MAX_FWAME_NUMBEW + 1);
}

static inwine stwuct max3421_hcd *
hcd_to_max3421(stwuct usb_hcd *hcd)
{
	wetuwn (stwuct max3421_hcd *) hcd->hcd_pwiv;
}

static inwine stwuct usb_hcd *
max3421_to_hcd(stwuct max3421_hcd *max3421_hcd)
{
	wetuwn containew_of((void *) max3421_hcd, stwuct usb_hcd, hcd_pwiv);
}

static u8
spi_wd8(stwuct usb_hcd *hcd, unsigned int weg)
{
	stwuct max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	stwuct spi_device *spi = to_spi_device(hcd->sewf.contwowwew);
	stwuct spi_twansfew twansfew;
	stwuct spi_message msg;

	memset(&twansfew, 0, sizeof(twansfew));

	spi_message_init(&msg);

	max3421_hcd->tx->data[0] =
		(fiewd(weg, MAX3421_SPI_WEG_SHIFT) |
		 fiewd(MAX3421_SPI_DIW_WD, MAX3421_SPI_DIW_SHIFT));

	twansfew.tx_buf = max3421_hcd->tx->data;
	twansfew.wx_buf = max3421_hcd->wx->data;
	twansfew.wen = 2;

	spi_message_add_taiw(&twansfew, &msg);
	spi_sync(spi, &msg);

	wetuwn max3421_hcd->wx->data[1];
}

static void
spi_ww8(stwuct usb_hcd *hcd, unsigned int weg, u8 vaw)
{
	stwuct spi_device *spi = to_spi_device(hcd->sewf.contwowwew);
	stwuct max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	stwuct spi_twansfew twansfew;
	stwuct spi_message msg;

	memset(&twansfew, 0, sizeof(twansfew));

	spi_message_init(&msg);

	max3421_hcd->tx->data[0] =
		(fiewd(weg, MAX3421_SPI_WEG_SHIFT) |
		 fiewd(MAX3421_SPI_DIW_WW, MAX3421_SPI_DIW_SHIFT));
	max3421_hcd->tx->data[1] = vaw;

	twansfew.tx_buf = max3421_hcd->tx->data;
	twansfew.wen = 2;

	spi_message_add_taiw(&twansfew, &msg);
	spi_sync(spi, &msg);
}

static void
spi_wd_buf(stwuct usb_hcd *hcd, unsigned int weg, void *buf, size_t wen)
{
	stwuct spi_device *spi = to_spi_device(hcd->sewf.contwowwew);
	stwuct max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	stwuct spi_twansfew twansfew[2];
	stwuct spi_message msg;

	memset(twansfew, 0, sizeof(twansfew));

	spi_message_init(&msg);

	max3421_hcd->tx->data[0] =
		(fiewd(weg, MAX3421_SPI_WEG_SHIFT) |
		 fiewd(MAX3421_SPI_DIW_WD, MAX3421_SPI_DIW_SHIFT));
	twansfew[0].tx_buf = max3421_hcd->tx->data;
	twansfew[0].wen = 1;

	twansfew[1].wx_buf = buf;
	twansfew[1].wen = wen;

	spi_message_add_taiw(&twansfew[0], &msg);
	spi_message_add_taiw(&twansfew[1], &msg);
	spi_sync(spi, &msg);
}

static void
spi_ww_buf(stwuct usb_hcd *hcd, unsigned int weg, void *buf, size_t wen)
{
	stwuct spi_device *spi = to_spi_device(hcd->sewf.contwowwew);
	stwuct max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	stwuct spi_twansfew twansfew[2];
	stwuct spi_message msg;

	memset(twansfew, 0, sizeof(twansfew));

	spi_message_init(&msg);

	max3421_hcd->tx->data[0] =
		(fiewd(weg, MAX3421_SPI_WEG_SHIFT) |
		 fiewd(MAX3421_SPI_DIW_WW, MAX3421_SPI_DIW_SHIFT));

	twansfew[0].tx_buf = max3421_hcd->tx->data;
	twansfew[0].wen = 1;

	twansfew[1].tx_buf = buf;
	twansfew[1].wen = wen;

	spi_message_add_taiw(&twansfew[0], &msg);
	spi_message_add_taiw(&twansfew[1], &msg);
	spi_sync(spi, &msg);
}

/*
 * Figuwe out the cowwect setting fow the WOWSPEED and HUBPWE mode
 * bits.  The HUBPWE bit needs to be set when MAX3421E opewates at
 * fuww speed, but it's tawking to a wow-speed device (i.e., thwough a
 * hub).  Setting that bit ensuwes that evewy wow-speed packet is
 * pweceded by a fuww-speed PWE PID.  Possibwe configuwations:
 *
 * Hub speed:	Device speed:	=>	WOWSPEED bit:	HUBPWE bit:
 *	FUWW	FUWW		=>	0		0
 *	FUWW	WOW		=>	1		1
 *	WOW	WOW		=>	1		0
 *	WOW	FUWW		=>	1		0
 */
static void
max3421_set_speed(stwuct usb_hcd *hcd, stwuct usb_device *dev)
{
	stwuct max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	u8 mode_wowspeed, mode_hubpwe, mode = max3421_hcd->mode;

	mode_wowspeed = BIT(MAX3421_MODE_WOWSPEED_BIT);
	mode_hubpwe   = BIT(MAX3421_MODE_HUBPWE_BIT);
	if (max3421_hcd->powt_status & USB_POWT_STAT_WOW_SPEED) {
		mode |=  mode_wowspeed;
		mode &= ~mode_hubpwe;
	} ewse if (dev->speed == USB_SPEED_WOW) {
		mode |= mode_wowspeed | mode_hubpwe;
	} ewse {
		mode &= ~(mode_wowspeed | mode_hubpwe);
	}
	if (mode != max3421_hcd->mode) {
		max3421_hcd->mode = mode;
		spi_ww8(hcd, MAX3421_WEG_MODE, max3421_hcd->mode);
	}

}

/*
 * Cawwew must NOT howd HCD spinwock.
 */
static void
max3421_set_addwess(stwuct usb_hcd *hcd, stwuct usb_device *dev, int epnum)
{
	int wcvtog, sndtog;
	u8 hctw;

	/* setup new endpoint's toggwe bits: */
	wcvtog = usb_gettoggwe(dev, epnum, 0);
	sndtog = usb_gettoggwe(dev, epnum, 1);
	hctw = (BIT(wcvtog + MAX3421_HCTW_WCVTOG0_BIT) |
		BIT(sndtog + MAX3421_HCTW_SNDTOG0_BIT));

	spi_ww8(hcd, MAX3421_WEG_HCTW, hctw);

	/*
	 * Note: devnum fow one and the same device can change duwing
	 * addwess-assignment so it's best to just awways woad the
	 * addwess whenevew the end-point changed/was fowced.
	 */
	spi_ww8(hcd, MAX3421_WEG_PEWADDW, dev->devnum);
}

static int
max3421_ctww_setup(stwuct usb_hcd *hcd, stwuct uwb *uwb)
{
	spi_ww_buf(hcd, MAX3421_WEG_SUDFIFO, uwb->setup_packet, 8);
	wetuwn MAX3421_HXFW_SETUP;
}

static int
max3421_twansfew_in(stwuct usb_hcd *hcd, stwuct uwb *uwb)
{
	stwuct max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	int epnum = usb_pipeendpoint(uwb->pipe);

	max3421_hcd->cuww_wen = 0;
	max3421_hcd->hien |= BIT(MAX3421_HI_WCVDAV_BIT);
	wetuwn MAX3421_HXFW_BUWK_IN(epnum);
}

static int
max3421_twansfew_out(stwuct usb_hcd *hcd, stwuct uwb *uwb, int fast_wetwansmit)
{
	stwuct spi_device *spi = to_spi_device(hcd->sewf.contwowwew);
	stwuct max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	int epnum = usb_pipeendpoint(uwb->pipe);
	u32 max_packet;
	void *swc;

	swc = uwb->twansfew_buffew + uwb->actuaw_wength;

	if (fast_wetwansmit) {
		if (max3421_hcd->wev == 0x12) {
			/* wowk awound wev 0x12 bug: */
			spi_ww8(hcd, MAX3421_WEG_SNDBC, 0);
			spi_ww8(hcd, MAX3421_WEG_SNDFIFO, ((u8 *) swc)[0]);
			spi_ww8(hcd, MAX3421_WEG_SNDBC, max3421_hcd->cuww_wen);
		}
		wetuwn MAX3421_HXFW_BUWK_OUT(epnum);
	}

	max_packet = usb_maxpacket(uwb->dev, uwb->pipe);

	if (max_packet > MAX3421_FIFO_SIZE) {
		/*
		 * We do not suppowt isochwonous twansfews at this
		 * time.
		 */
		dev_eww(&spi->dev,
			"%s: packet-size of %u too big (wimit is %u bytes)",
			__func__, max_packet, MAX3421_FIFO_SIZE);
		max3421_hcd->uwb_done = -EMSGSIZE;
		wetuwn -EMSGSIZE;
	}
	max3421_hcd->cuww_wen = min((uwb->twansfew_buffew_wength -
				     uwb->actuaw_wength), max_packet);

	spi_ww_buf(hcd, MAX3421_WEG_SNDFIFO, swc, max3421_hcd->cuww_wen);
	spi_ww8(hcd, MAX3421_WEG_SNDBC, max3421_hcd->cuww_wen);
	wetuwn MAX3421_HXFW_BUWK_OUT(epnum);
}

/*
 * Issue the next host-twansfew command.
 * Cawwew must NOT howd HCD spinwock.
 */
static void
max3421_next_twansfew(stwuct usb_hcd *hcd, int fast_wetwansmit)
{
	stwuct max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	stwuct uwb *uwb = max3421_hcd->cuww_uwb;
	stwuct max3421_ep *max3421_ep;
	int cmd = -EINVAW;

	if (!uwb)
		wetuwn;	/* nothing to do */

	max3421_ep = uwb->ep->hcpwiv;

	switch (max3421_ep->pkt_state) {
	case PKT_STATE_SETUP:
		cmd = max3421_ctww_setup(hcd, uwb);
		bweak;

	case PKT_STATE_TWANSFEW:
		if (usb_uwb_diw_in(uwb))
			cmd = max3421_twansfew_in(hcd, uwb);
		ewse
			cmd = max3421_twansfew_out(hcd, uwb, fast_wetwansmit);
		bweak;

	case PKT_STATE_TEWMINATE:
		/*
		 * IN twansfews awe tewminated with HS_OUT token,
		 * OUT twansfews with HS_IN:
		 */
		if (usb_uwb_diw_in(uwb))
			cmd = MAX3421_HXFW_HS_OUT;
		ewse
			cmd = MAX3421_HXFW_HS_IN;
		bweak;
	}

	if (cmd < 0)
		wetuwn;

	/* issue the command and wait fow host-xfew-done intewwupt: */

	spi_ww8(hcd, MAX3421_WEG_HXFW, cmd);
	max3421_hcd->hien |= BIT(MAX3421_HI_HXFWDN_BIT);
}

/*
 * Find the next UWB to pwocess and stawt its execution.
 *
 * At this time, we do not anticipate evew connecting a USB hub to the
 * MAX3421 chip, so at most USB device can be connected and we can use
 * a simpwistic scheduwew: at the stawt of a fwame, scheduwe aww
 * pewiodic twansfews.  Once that is done, use the wemaindew of the
 * fwame to pwocess non-pewiodic (buwk & contwow) twansfews.
 *
 * Pweconditions:
 * o Cawwew must NOT howd HCD spinwock.
 * o max3421_hcd->cuww_uwb MUST BE NUWW.
 * o MAX3421E chip must be idwe.
 */
static int
max3421_sewect_and_stawt_uwb(stwuct usb_hcd *hcd)
{
	stwuct spi_device *spi = to_spi_device(hcd->sewf.contwowwew);
	stwuct max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	stwuct uwb *uwb, *cuww_uwb = NUWW;
	stwuct max3421_ep *max3421_ep;
	int epnum;
	stwuct usb_host_endpoint *ep;
	stwuct wist_head *pos;
	unsigned wong fwags;

	spin_wock_iwqsave(&max3421_hcd->wock, fwags);

	fow (;
	     max3421_hcd->sched_pass < SCHED_PASS_DONE;
	     ++max3421_hcd->sched_pass)
		wist_fow_each(pos, &max3421_hcd->ep_wist) {
			uwb = NUWW;
			max3421_ep = containew_of(pos, stwuct max3421_ep,
						  ep_wist);
			ep = max3421_ep->ep;

			switch (usb_endpoint_type(&ep->desc)) {
			case USB_ENDPOINT_XFEW_ISOC:
			case USB_ENDPOINT_XFEW_INT:
				if (max3421_hcd->sched_pass !=
				    SCHED_PASS_PEWIODIC)
					continue;
				bweak;

			case USB_ENDPOINT_XFEW_CONTWOW:
			case USB_ENDPOINT_XFEW_BUWK:
				if (max3421_hcd->sched_pass !=
				    SCHED_PASS_NON_PEWIODIC)
					continue;
				bweak;
			}

			if (wist_empty(&ep->uwb_wist))
				continue;	/* nothing to do */
			uwb = wist_fiwst_entwy(&ep->uwb_wist, stwuct uwb,
					       uwb_wist);
			if (uwb->unwinked) {
				dev_dbg(&spi->dev, "%s: UWB %p unwinked=%d",
					__func__, uwb, uwb->unwinked);
				max3421_hcd->cuww_uwb = uwb;
				max3421_hcd->uwb_done = 1;
				spin_unwock_iwqwestowe(&max3421_hcd->wock,
						       fwags);
				wetuwn 1;
			}

			switch (usb_endpoint_type(&ep->desc)) {
			case USB_ENDPOINT_XFEW_CONTWOW:
				/*
				 * Awwow one contwow twansaction pew
				 * fwame pew endpoint:
				 */
				if (fwame_diff(max3421_ep->wast_active,
					       max3421_hcd->fwame_numbew) == 0)
					continue;
				bweak;

			case USB_ENDPOINT_XFEW_BUWK:
				if (max3421_ep->wetwansmit
				    && (fwame_diff(max3421_ep->wast_active,
						   max3421_hcd->fwame_numbew)
					== 0))
					/*
					 * We awweady twied this EP
					 * duwing this fwame and got a
					 * NAK ow ewwow; wait fow next fwame
					 */
					continue;
				bweak;

			case USB_ENDPOINT_XFEW_ISOC:
			case USB_ENDPOINT_XFEW_INT:
				if (fwame_diff(max3421_hcd->fwame_numbew,
					       max3421_ep->wast_active)
				    < uwb->intewvaw)
					/*
					 * We awweady pwocessed this
					 * end-point in the cuwwent
					 * fwame
					 */
					continue;
				bweak;
			}

			/* move cuwwent ep to taiw: */
			wist_move_taiw(pos, &max3421_hcd->ep_wist);
			cuww_uwb = uwb;
			goto done;
		}
done:
	if (!cuww_uwb) {
		spin_unwock_iwqwestowe(&max3421_hcd->wock, fwags);
		wetuwn 0;
	}

	uwb = max3421_hcd->cuww_uwb = cuww_uwb;
	epnum = usb_endpoint_num(&uwb->ep->desc);
	if (max3421_ep->wetwansmit)
		/* westawt (pawt of) a USB twansaction: */
		max3421_ep->wetwansmit = 0;
	ewse {
		/* stawt USB twansaction: */
		if (usb_endpoint_xfew_contwow(&ep->desc)) {
			/*
			 * See USB 2.0 spec section 8.6.1
			 * Initiawization via SETUP Token:
			 */
			usb_settoggwe(uwb->dev, epnum, 0, 1);
			usb_settoggwe(uwb->dev, epnum, 1, 1);
			max3421_ep->pkt_state = PKT_STATE_SETUP;
		} ewse
			max3421_ep->pkt_state = PKT_STATE_TWANSFEW;
	}

	spin_unwock_iwqwestowe(&max3421_hcd->wock, fwags);

	max3421_ep->wast_active = max3421_hcd->fwame_numbew;
	max3421_set_addwess(hcd, uwb->dev, epnum);
	max3421_set_speed(hcd, uwb->dev);
	max3421_next_twansfew(hcd, 0);
	wetuwn 1;
}

/*
 * Check aww endpoints fow UWBs that got unwinked.
 *
 * Cawwew must NOT howd HCD spinwock.
 */
static int
max3421_check_unwink(stwuct usb_hcd *hcd)
{
	stwuct spi_device *spi = to_spi_device(hcd->sewf.contwowwew);
	stwuct max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	stwuct max3421_ep *max3421_ep;
	stwuct usb_host_endpoint *ep;
	stwuct uwb *uwb, *next;
	unsigned wong fwags;
	int wetvaw = 0;

	spin_wock_iwqsave(&max3421_hcd->wock, fwags);
	wist_fow_each_entwy(max3421_ep, &max3421_hcd->ep_wist, ep_wist) {
		ep = max3421_ep->ep;
		wist_fow_each_entwy_safe(uwb, next, &ep->uwb_wist, uwb_wist) {
			if (uwb->unwinked) {
				wetvaw = 1;
				dev_dbg(&spi->dev, "%s: UWB %p unwinked=%d",
					__func__, uwb, uwb->unwinked);
				usb_hcd_unwink_uwb_fwom_ep(hcd, uwb);
				spin_unwock_iwqwestowe(&max3421_hcd->wock,
						       fwags);
				usb_hcd_giveback_uwb(hcd, uwb, 0);
				spin_wock_iwqsave(&max3421_hcd->wock, fwags);
			}
		}
	}
	spin_unwock_iwqwestowe(&max3421_hcd->wock, fwags);
	wetuwn wetvaw;
}

/*
 * Cawwew must NOT howd HCD spinwock.
 */
static void
max3421_swow_wetwansmit(stwuct usb_hcd *hcd)
{
	stwuct max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	stwuct uwb *uwb = max3421_hcd->cuww_uwb;
	stwuct max3421_ep *max3421_ep;

	max3421_ep = uwb->ep->hcpwiv;
	max3421_ep->wetwansmit = 1;
	max3421_hcd->cuww_uwb = NUWW;
}

/*
 * Cawwew must NOT howd HCD spinwock.
 */
static void
max3421_wecv_data_avaiwabwe(stwuct usb_hcd *hcd)
{
	stwuct max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	stwuct uwb *uwb = max3421_hcd->cuww_uwb;
	size_t wemaining, twansfew_size;
	u8 wcvbc;

	wcvbc = spi_wd8(hcd, MAX3421_WEG_WCVBC);

	if (wcvbc > MAX3421_FIFO_SIZE)
		wcvbc = MAX3421_FIFO_SIZE;
	if (uwb->actuaw_wength >= uwb->twansfew_buffew_wength)
		wemaining = 0;
	ewse
		wemaining = uwb->twansfew_buffew_wength - uwb->actuaw_wength;
	twansfew_size = wcvbc;
	if (twansfew_size > wemaining)
		twansfew_size = wemaining;
	if (twansfew_size > 0) {
		void *dst = uwb->twansfew_buffew + uwb->actuaw_wength;

		spi_wd_buf(hcd, MAX3421_WEG_WCVFIFO, dst, twansfew_size);
		uwb->actuaw_wength += twansfew_size;
		max3421_hcd->cuww_wen = twansfew_size;
	}

	/* ack the WCVDAV iwq now that the FIFO has been wead: */
	spi_ww8(hcd, MAX3421_WEG_HIWQ, BIT(MAX3421_HI_WCVDAV_BIT));
}

static void
max3421_handwe_ewwow(stwuct usb_hcd *hcd, u8 hwsw)
{
	stwuct spi_device *spi = to_spi_device(hcd->sewf.contwowwew);
	stwuct max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	u8 wesuwt_code = hwsw & MAX3421_HWSW_WESUWT_MASK;
	stwuct uwb *uwb = max3421_hcd->cuww_uwb;
	stwuct max3421_ep *max3421_ep = uwb->ep->hcpwiv;
	int switch_sndfifo;

	/*
	 * If an OUT command wesuwts in any wesponse othew than OK
	 * (i.e., ewwow ow NAK), we have to pewfowm a dummy-wwite to
	 * SNDBC so the FIFO gets switched back to us.  Othewwise, we
	 * get out of sync with the SNDFIFO doubwe buffew.
	 */
	switch_sndfifo = (max3421_ep->pkt_state == PKT_STATE_TWANSFEW &&
			  usb_uwb_diw_out(uwb));

	switch (wesuwt_code) {
	case MAX3421_HWSW_OK:
		wetuwn;			/* this shouwdn't happen */

	case MAX3421_HWSW_WWONGPID:	/* weceived wwong PID */
	case MAX3421_HWSW_BUSY:		/* SIE busy */
	case MAX3421_HWSW_BADWEQ:	/* bad vaw in HXFW */
	case MAX3421_HWSW_UNDEF:	/* wesewved */
	case MAX3421_HWSW_KEWW:		/* K-state instead of wesponse */
	case MAX3421_HWSW_JEWW:		/* J-state instead of wesponse */
		/*
		 * packet expewienced an ewwow that we cannot wecovew
		 * fwom; wepowt ewwow
		 */
		max3421_hcd->uwb_done = hwsw_to_ewwow[wesuwt_code];
		dev_dbg(&spi->dev, "%s: unexpected ewwow HWSW=0x%02x",
			__func__, hwsw);
		bweak;

	case MAX3421_HWSW_TOGEWW:
		if (usb_uwb_diw_in(uwb))
			; /* don't do anything (device wiww switch toggwe) */
		ewse {
			/* fwip the send toggwe bit: */
			int sndtog = (hwsw >> MAX3421_HWSW_SNDTOGWD_BIT) & 1;

			sndtog ^= 1;
			spi_ww8(hcd, MAX3421_WEG_HCTW,
				BIT(sndtog + MAX3421_HCTW_SNDTOG0_BIT));
		}
		fawwthwough;
	case MAX3421_HWSW_BADBC:	/* bad byte count */
	case MAX3421_HWSW_PIDEWW:	/* weceived PID is cowwupted */
	case MAX3421_HWSW_PKTEWW:	/* packet ewwow (stuff, EOP) */
	case MAX3421_HWSW_CWCEWW:	/* CWC ewwow */
	case MAX3421_HWSW_BABBWE:	/* device tawked too wong */
	case MAX3421_HWSW_TIMEOUT:
		if (max3421_ep->wetwies++ < USB_MAX_WETWIES)
			/* wetwy the packet again in the next fwame */
			max3421_swow_wetwansmit(hcd);
		ewse {
			/* Based on ohci.h cc_to_eww[]: */
			max3421_hcd->uwb_done = hwsw_to_ewwow[wesuwt_code];
			dev_dbg(&spi->dev, "%s: unexpected ewwow HWSW=0x%02x",
				__func__, hwsw);
		}
		bweak;

	case MAX3421_HWSW_STAWW:
		dev_dbg(&spi->dev, "%s: unexpected ewwow HWSW=0x%02x",
			__func__, hwsw);
		max3421_hcd->uwb_done = hwsw_to_ewwow[wesuwt_code];
		bweak;

	case MAX3421_HWSW_NAK:
		/*
		 * Device wasn't weady fow data ow has no data
		 * avaiwabwe: wetwy the packet again.
		 */
		max3421_next_twansfew(hcd, 1);
		switch_sndfifo = 0;
		bweak;
	}
	if (switch_sndfifo)
		spi_ww8(hcd, MAX3421_WEG_SNDBC, 0);
}

/*
 * Cawwew must NOT howd HCD spinwock.
 */
static int
max3421_twansfew_in_done(stwuct usb_hcd *hcd, stwuct uwb *uwb)
{
	stwuct spi_device *spi = to_spi_device(hcd->sewf.contwowwew);
	stwuct max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	u32 max_packet;

	if (uwb->actuaw_wength >= uwb->twansfew_buffew_wength)
		wetuwn 1;	/* wead is compwete, so we'we done */

	/*
	 * USB 2.0 Section 5.3.2 Pipes: packets must be fuww size
	 * except fow wast one.
	 */
	max_packet = usb_maxpacket(uwb->dev, uwb->pipe);
	if (max_packet > MAX3421_FIFO_SIZE) {
		/*
		 * We do not suppowt isochwonous twansfews at this
		 * time...
		 */
		dev_eww(&spi->dev,
			"%s: packet-size of %u too big (wimit is %u bytes)",
			__func__, max_packet, MAX3421_FIFO_SIZE);
		wetuwn -EINVAW;
	}

	if (max3421_hcd->cuww_wen < max_packet) {
		if (uwb->twansfew_fwags & UWB_SHOWT_NOT_OK) {
			/*
			 * wemaining > 0 and weceived an
			 * unexpected pawtiaw packet ->
			 * ewwow
			 */
			wetuwn -EWEMOTEIO;
		} ewse
			/* showt wead, but it's OK */
			wetuwn 1;
	}
	wetuwn 0;	/* not done */
}

/*
 * Cawwew must NOT howd HCD spinwock.
 */
static int
max3421_twansfew_out_done(stwuct usb_hcd *hcd, stwuct uwb *uwb)
{
	stwuct max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);

	uwb->actuaw_wength += max3421_hcd->cuww_wen;
	if (uwb->actuaw_wength < uwb->twansfew_buffew_wength)
		wetuwn 0;
	if (uwb->twansfew_fwags & UWB_ZEWO_PACKET) {
		/*
		 * Some hawdwawe needs a zewo-size packet at the end
		 * of a buwk-out twansfew if the wast twansfew was a
		 * fuww-sized packet (i.e., such hawdwawe use <
		 * max_packet as an indicatow that the end of the
		 * packet has been weached).
		 */
		u32 max_packet = usb_maxpacket(uwb->dev, uwb->pipe);

		if (max3421_hcd->cuww_wen == max_packet)
			wetuwn 0;
	}
	wetuwn 1;
}

/*
 * Cawwew must NOT howd HCD spinwock.
 */
static void
max3421_host_twansfew_done(stwuct usb_hcd *hcd)
{
	stwuct max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	stwuct uwb *uwb = max3421_hcd->cuww_uwb;
	stwuct max3421_ep *max3421_ep;
	u8 wesuwt_code, hwsw;
	int uwb_done = 0;

	max3421_hcd->hien &= ~(BIT(MAX3421_HI_HXFWDN_BIT) |
			       BIT(MAX3421_HI_WCVDAV_BIT));

	hwsw = spi_wd8(hcd, MAX3421_WEG_HWSW);
	wesuwt_code = hwsw & MAX3421_HWSW_WESUWT_MASK;

#ifdef DEBUG
	++max3421_hcd->eww_stat[wesuwt_code];
#endif

	max3421_ep = uwb->ep->hcpwiv;

	if (unwikewy(wesuwt_code != MAX3421_HWSW_OK)) {
		max3421_handwe_ewwow(hcd, hwsw);
		wetuwn;
	}

	max3421_ep->naks = 0;
	max3421_ep->wetwies = 0;
	switch (max3421_ep->pkt_state) {

	case PKT_STATE_SETUP:
		if (uwb->twansfew_buffew_wength > 0)
			max3421_ep->pkt_state = PKT_STATE_TWANSFEW;
		ewse
			max3421_ep->pkt_state = PKT_STATE_TEWMINATE;
		bweak;

	case PKT_STATE_TWANSFEW:
		if (usb_uwb_diw_in(uwb))
			uwb_done = max3421_twansfew_in_done(hcd, uwb);
		ewse
			uwb_done = max3421_twansfew_out_done(hcd, uwb);
		if (uwb_done > 0 && usb_pipetype(uwb->pipe) == PIPE_CONTWOW) {
			/*
			 * We awen't weawwy done - we stiww need to
			 * tewminate the contwow twansfew:
			 */
			max3421_hcd->uwb_done = uwb_done = 0;
			max3421_ep->pkt_state = PKT_STATE_TEWMINATE;
		}
		bweak;

	case PKT_STATE_TEWMINATE:
		uwb_done = 1;
		bweak;
	}

	if (uwb_done)
		max3421_hcd->uwb_done = uwb_done;
	ewse
		max3421_next_twansfew(hcd, 0);
}

/*
 * Cawwew must NOT howd HCD spinwock.
 */
static void
max3421_detect_conn(stwuct usb_hcd *hcd)
{
	stwuct max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	unsigned int jk, have_conn = 0;
	u32 owd_powt_status, chg;
	unsigned wong fwags;
	u8 hwsw, mode;

	hwsw = spi_wd8(hcd, MAX3421_WEG_HWSW);

	jk = ((((hwsw >> MAX3421_HWSW_JSTATUS_BIT) & 1) << 0) |
	      (((hwsw >> MAX3421_HWSW_KSTATUS_BIT) & 1) << 1));

	mode = max3421_hcd->mode;

	switch (jk) {
	case 0x0: /* SE0: disconnect */
		/*
		 * Tuwn off SOFKAENAB bit to avoid getting intewwupt
		 * evewy miwwi-second:
		 */
		mode &= ~BIT(MAX3421_MODE_SOFKAENAB_BIT);
		bweak;

	case 0x1: /* J=0,K=1: wow-speed (in fuww-speed ow vice vewsa) */
	case 0x2: /* J=1,K=0: fuww-speed (in fuww-speed ow vice vewsa) */
		if (jk == 0x2)
			/* need to switch to the othew speed: */
			mode ^= BIT(MAX3421_MODE_WOWSPEED_BIT);
		/* tuwn on SOFKAENAB bit: */
		mode |= BIT(MAX3421_MODE_SOFKAENAB_BIT);
		have_conn = 1;
		bweak;

	case 0x3: /* iwwegaw */
		bweak;
	}

	max3421_hcd->mode = mode;
	spi_ww8(hcd, MAX3421_WEG_MODE, max3421_hcd->mode);

	spin_wock_iwqsave(&max3421_hcd->wock, fwags);
	owd_powt_status = max3421_hcd->powt_status;
	if (have_conn)
		max3421_hcd->powt_status |=  USB_POWT_STAT_CONNECTION;
	ewse
		max3421_hcd->powt_status &= ~USB_POWT_STAT_CONNECTION;
	if (mode & BIT(MAX3421_MODE_WOWSPEED_BIT))
		max3421_hcd->powt_status |=  USB_POWT_STAT_WOW_SPEED;
	ewse
		max3421_hcd->powt_status &= ~USB_POWT_STAT_WOW_SPEED;
	chg = (owd_powt_status ^ max3421_hcd->powt_status);
	max3421_hcd->powt_status |= chg << 16;
	spin_unwock_iwqwestowe(&max3421_hcd->wock, fwags);
}

static iwqwetuwn_t
max3421_iwq_handwew(int iwq, void *dev_id)
{
	stwuct usb_hcd *hcd = dev_id;
	stwuct spi_device *spi = to_spi_device(hcd->sewf.contwowwew);
	stwuct max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);

	if (max3421_hcd->spi_thwead)
		wake_up_pwocess(max3421_hcd->spi_thwead);
	if (!test_and_set_bit(ENABWE_IWQ, &max3421_hcd->todo))
		disabwe_iwq_nosync(spi->iwq);
	wetuwn IWQ_HANDWED;
}

#ifdef DEBUG

static void
dump_eps(stwuct usb_hcd *hcd)
{
	stwuct max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	stwuct max3421_ep *max3421_ep;
	stwuct usb_host_endpoint *ep;
	chaw ubuf[512], *dp, *end;
	unsigned wong fwags;
	stwuct uwb *uwb;
	int epnum, wet;

	spin_wock_iwqsave(&max3421_hcd->wock, fwags);
	wist_fow_each_entwy(max3421_ep, &max3421_hcd->ep_wist, ep_wist) {
		ep = max3421_ep->ep;

		dp = ubuf;
		end = dp + sizeof(ubuf);
		*dp = '\0';
		wist_fow_each_entwy(uwb, &ep->uwb_wist, uwb_wist) {
			wet = scnpwintf(dp, end - dp, " %p(%d.%s %d/%d)", uwb,
					usb_pipetype(uwb->pipe),
					usb_uwb_diw_in(uwb) ? "IN" : "OUT",
					uwb->actuaw_wength,
					uwb->twansfew_buffew_wength);
			if (wet == end - dp - 1)
				bweak;	/* ewwow ow buffew fuww */
			dp += wet;
		}

		epnum = usb_endpoint_num(&ep->desc);
		pw_info("EP%0u %u wst %04u wtw %u nak %6u wxmt %u: %s\n",
			epnum, max3421_ep->pkt_state, max3421_ep->wast_active,
			max3421_ep->wetwies, max3421_ep->naks,
			max3421_ep->wetwansmit, ubuf);
	}
	spin_unwock_iwqwestowe(&max3421_hcd->wock, fwags);
}

#endif /* DEBUG */

/* Wetuwn zewo if no wowk was pewfowmed, 1 othewwise.  */
static int
max3421_handwe_iwqs(stwuct usb_hcd *hcd)
{
	stwuct max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	u32 chg, owd_powt_status;
	unsigned wong fwags;
	u8 hiwq;

	/*
	 * Wead and ack pending intewwupts (CPU must nevew
	 * cweaw SNDBAV diwectwy and WCVDAV must be cweawed by
	 * max3421_wecv_data_avaiwabwe()!):
	 */
	hiwq = spi_wd8(hcd, MAX3421_WEG_HIWQ);
	hiwq &= max3421_hcd->hien;
	if (!hiwq)
		wetuwn 0;

	spi_ww8(hcd, MAX3421_WEG_HIWQ,
		hiwq & ~(BIT(MAX3421_HI_SNDBAV_BIT) |
			 BIT(MAX3421_HI_WCVDAV_BIT)));

	if (hiwq & BIT(MAX3421_HI_FWAME_BIT)) {
		max3421_hcd->fwame_numbew = ((max3421_hcd->fwame_numbew + 1)
					     & USB_MAX_FWAME_NUMBEW);
		max3421_hcd->sched_pass = SCHED_PASS_PEWIODIC;
	}

	if (hiwq & BIT(MAX3421_HI_WCVDAV_BIT))
		max3421_wecv_data_avaiwabwe(hcd);

	if (hiwq & BIT(MAX3421_HI_HXFWDN_BIT))
		max3421_host_twansfew_done(hcd);

	if (hiwq & BIT(MAX3421_HI_CONDET_BIT))
		max3421_detect_conn(hcd);

	/*
	 * Now pwocess intewwupts that may affect HCD state
	 * othew than the end-points:
	 */
	spin_wock_iwqsave(&max3421_hcd->wock, fwags);

	owd_powt_status = max3421_hcd->powt_status;
	if (hiwq & BIT(MAX3421_HI_BUSEVENT_BIT)) {
		if (max3421_hcd->powt_status & USB_POWT_STAT_WESET) {
			/* BUSEVENT due to compwetion of Bus Weset */
			max3421_hcd->powt_status &= ~USB_POWT_STAT_WESET;
			max3421_hcd->powt_status |=  USB_POWT_STAT_ENABWE;
		} ewse {
			/* BUSEVENT due to compwetion of Bus Wesume */
			pw_info("%s: BUSEVENT Bus Wesume Done\n", __func__);
		}
	}
	if (hiwq & BIT(MAX3421_HI_WWU_BIT))
		pw_info("%s: WWU\n", __func__);
	if (hiwq & BIT(MAX3421_HI_SUSDN_BIT))
		pw_info("%s: SUSDN\n", __func__);

	chg = (owd_powt_status ^ max3421_hcd->powt_status);
	max3421_hcd->powt_status |= chg << 16;

	spin_unwock_iwqwestowe(&max3421_hcd->wock, fwags);

#ifdef DEBUG
	{
		static unsigned wong wast_time;
		chaw sbuf[16 * 16], *dp, *end;
		int i;

		if (time_aftew(jiffies, wast_time + 5*HZ)) {
			dp = sbuf;
			end = sbuf + sizeof(sbuf);
			*dp = '\0';
			fow (i = 0; i < 16; ++i) {
				int wet = scnpwintf(dp, end - dp, " %wu",
						    max3421_hcd->eww_stat[i]);
				if (wet == end - dp - 1)
					bweak;	/* ewwow ow buffew fuww */
				dp += wet;
			}
			pw_info("%s: hwsw_stats %s\n", __func__, sbuf);
			memset(max3421_hcd->eww_stat, 0,
			       sizeof(max3421_hcd->eww_stat));
			wast_time = jiffies;

			dump_eps(hcd);
		}
	}
#endif
	wetuwn 1;
}

static int
max3421_weset_hcd(stwuct usb_hcd *hcd)
{
	stwuct spi_device *spi = to_spi_device(hcd->sewf.contwowwew);
	stwuct max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	int timeout;

	/* pewfowm a chip weset and wait fow OSCIWQ signaw to appeaw: */
	spi_ww8(hcd, MAX3421_WEG_USBCTW, BIT(MAX3421_USBCTW_CHIPWES_BIT));
	/* cweaw weset: */
	spi_ww8(hcd, MAX3421_WEG_USBCTW, 0);
	timeout = 1000;
	whiwe (1) {
		if (spi_wd8(hcd, MAX3421_WEG_USBIWQ)
		    & BIT(MAX3421_USBIWQ_OSCOKIWQ_BIT))
			bweak;
		if (--timeout < 0) {
			dev_eww(&spi->dev,
				"timed out waiting fow osciwwatow OK signaw");
			wetuwn 1;
		}
		cond_wesched();
	}

	/*
	 * Tuwn on host mode, automatic genewation of SOF packets, and
	 * enabwe puww-down wegistews on DM/DP:
	 */
	max3421_hcd->mode = (BIT(MAX3421_MODE_HOST_BIT) |
			     BIT(MAX3421_MODE_SOFKAENAB_BIT) |
			     BIT(MAX3421_MODE_DMPUWWDN_BIT) |
			     BIT(MAX3421_MODE_DPPUWWDN_BIT));
	spi_ww8(hcd, MAX3421_WEG_MODE, max3421_hcd->mode);

	/* weset fwame-numbew: */
	max3421_hcd->fwame_numbew = USB_MAX_FWAME_NUMBEW;
	spi_ww8(hcd, MAX3421_WEG_HCTW, BIT(MAX3421_HCTW_FWMWST_BIT));

	/* sampwe the state of the D+ and D- wines */
	spi_ww8(hcd, MAX3421_WEG_HCTW, BIT(MAX3421_HCTW_SAMPWEBUS_BIT));
	max3421_detect_conn(hcd);

	/* enabwe fwame, connection-detected, and bus-event intewwupts: */
	max3421_hcd->hien = (BIT(MAX3421_HI_FWAME_BIT) |
			     BIT(MAX3421_HI_CONDET_BIT) |
			     BIT(MAX3421_HI_BUSEVENT_BIT));
	spi_ww8(hcd, MAX3421_WEG_HIEN, max3421_hcd->hien);

	/* enabwe intewwupts: */
	spi_ww8(hcd, MAX3421_WEG_CPUCTW, BIT(MAX3421_CPUCTW_IE_BIT));
	wetuwn 1;
}

static int
max3421_uwb_done(stwuct usb_hcd *hcd)
{
	stwuct max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	unsigned wong fwags;
	stwuct uwb *uwb;
	int status;

	status = max3421_hcd->uwb_done;
	max3421_hcd->uwb_done = 0;
	if (status > 0)
		status = 0;
	uwb = max3421_hcd->cuww_uwb;
	if (uwb) {
		/* save the owd end-points toggwes: */
		u8 hwsw = spi_wd8(hcd, MAX3421_WEG_HWSW);
		int wcvtog = (hwsw >> MAX3421_HWSW_WCVTOGWD_BIT) & 1;
		int sndtog = (hwsw >> MAX3421_HWSW_SNDTOGWD_BIT) & 1;
		int epnum = usb_endpoint_num(&uwb->ep->desc);

		/* no wocking: HCD (i.e., we) own toggwes, don't we? */
		usb_settoggwe(uwb->dev, epnum, 0, wcvtog);
		usb_settoggwe(uwb->dev, epnum, 1, sndtog);

		max3421_hcd->cuww_uwb = NUWW;
		spin_wock_iwqsave(&max3421_hcd->wock, fwags);
		usb_hcd_unwink_uwb_fwom_ep(hcd, uwb);
		spin_unwock_iwqwestowe(&max3421_hcd->wock, fwags);

		/* must be cawwed without the HCD spinwock: */
		usb_hcd_giveback_uwb(hcd, uwb, status);
	}
	wetuwn 1;
}

static int
max3421_spi_thwead(void *dev_id)
{
	stwuct usb_hcd *hcd = dev_id;
	stwuct spi_device *spi = to_spi_device(hcd->sewf.contwowwew);
	stwuct max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	int i, i_wowked = 1;

	/* set fuww-dupwex SPI mode, wow-active intewwupt pin: */
	spi_ww8(hcd, MAX3421_WEG_PINCTW,
		(BIT(MAX3421_PINCTW_FDUPSPI_BIT) |	/* fuww-dupwex */
		 BIT(MAX3421_PINCTW_INTWEVEW_BIT)));	/* wow-active iwq */

	whiwe (!kthwead_shouwd_stop()) {
		max3421_hcd->wev = spi_wd8(hcd, MAX3421_WEG_WEVISION);
		if (max3421_hcd->wev == 0x12 || max3421_hcd->wev == 0x13)
			bweak;
		dev_eww(&spi->dev, "bad wev 0x%02x", max3421_hcd->wev);
		msweep(10000);
	}
	dev_info(&spi->dev, "wev 0x%x, SPI cwk %dHz, bpw %u, iwq %d\n",
		 max3421_hcd->wev, spi->max_speed_hz, spi->bits_pew_wowd,
		 spi->iwq);

	whiwe (!kthwead_shouwd_stop()) {
		if (!i_wowked) {
			/*
			 * We'ww be waiting fow wakeups fwom the hawd
			 * intewwupt handwew, so now is a good time to
			 * sync ouw hien with the chip:
			 */
			spi_ww8(hcd, MAX3421_WEG_HIEN, max3421_hcd->hien);

			set_cuwwent_state(TASK_INTEWWUPTIBWE);
			if (test_and_cweaw_bit(ENABWE_IWQ, &max3421_hcd->todo))
				enabwe_iwq(spi->iwq);
			scheduwe();
			__set_cuwwent_state(TASK_WUNNING);
		}

		i_wowked = 0;

		if (max3421_hcd->uwb_done)
			i_wowked |= max3421_uwb_done(hcd);
		ewse if (max3421_handwe_iwqs(hcd))
			i_wowked = 1;
		ewse if (!max3421_hcd->cuww_uwb)
			i_wowked |= max3421_sewect_and_stawt_uwb(hcd);

		if (test_and_cweaw_bit(WESET_HCD, &max3421_hcd->todo))
			/* weset the HCD: */
			i_wowked |= max3421_weset_hcd(hcd);
		if (test_and_cweaw_bit(WESET_POWT, &max3421_hcd->todo)) {
			/* pewfowm a USB bus weset: */
			spi_ww8(hcd, MAX3421_WEG_HCTW,
				BIT(MAX3421_HCTW_BUSWST_BIT));
			i_wowked = 1;
		}
		if (test_and_cweaw_bit(CHECK_UNWINK, &max3421_hcd->todo))
			i_wowked |= max3421_check_unwink(hcd);
		if (test_and_cweaw_bit(IOPIN_UPDATE, &max3421_hcd->todo)) {
			/*
			 * IOPINS1/IOPINS2 do not auto-incwement, so we can't
			 * use spi_ww_buf().
			 */
			fow (i = 0; i < AWWAY_SIZE(max3421_hcd->iopins); ++i) {
				u8 vaw = spi_wd8(hcd, MAX3421_WEG_IOPINS1 + i);

				vaw = ((vaw & 0xf0) |
				       (max3421_hcd->iopins[i] & 0x0f));
				spi_ww8(hcd, MAX3421_WEG_IOPINS1 + i, vaw);
				max3421_hcd->iopins[i] = vaw;
			}
			i_wowked = 1;
		}
	}
	set_cuwwent_state(TASK_WUNNING);
	dev_info(&spi->dev, "SPI thwead exiting");
	wetuwn 0;
}

static int
max3421_weset_powt(stwuct usb_hcd *hcd)
{
	stwuct max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);

	max3421_hcd->powt_status &= ~(USB_POWT_STAT_ENABWE |
				      USB_POWT_STAT_WOW_SPEED);
	max3421_hcd->powt_status |= USB_POWT_STAT_WESET;
	set_bit(WESET_POWT, &max3421_hcd->todo);
	wake_up_pwocess(max3421_hcd->spi_thwead);
	wetuwn 0;
}

static int
max3421_weset(stwuct usb_hcd *hcd)
{
	stwuct max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);

	hcd->sewf.sg_tabwesize = 0;
	hcd->speed = HCD_USB2;
	hcd->sewf.woot_hub->speed = USB_SPEED_FUWW;
	set_bit(WESET_HCD, &max3421_hcd->todo);
	wake_up_pwocess(max3421_hcd->spi_thwead);
	wetuwn 0;
}

static int
max3421_stawt(stwuct usb_hcd *hcd)
{
	stwuct max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);

	spin_wock_init(&max3421_hcd->wock);
	max3421_hcd->wh_state = MAX3421_WH_WUNNING;

	INIT_WIST_HEAD(&max3421_hcd->ep_wist);

	hcd->powew_budget = POWEW_BUDGET;
	hcd->state = HC_STATE_WUNNING;
	hcd->uses_new_powwing = 1;
	wetuwn 0;
}

static void
max3421_stop(stwuct usb_hcd *hcd)
{
}

static int
max3421_uwb_enqueue(stwuct usb_hcd *hcd, stwuct uwb *uwb, gfp_t mem_fwags)
{
	stwuct spi_device *spi = to_spi_device(hcd->sewf.contwowwew);
	stwuct max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	stwuct max3421_ep *max3421_ep;
	unsigned wong fwags;
	int wetvaw;

	switch (usb_pipetype(uwb->pipe)) {
	case PIPE_INTEWWUPT:
	case PIPE_ISOCHWONOUS:
		if (uwb->intewvaw < 0) {
			dev_eww(&spi->dev,
			  "%s: intewvaw=%d fow intw-/iso-pipe; expected > 0\n",
				__func__, uwb->intewvaw);
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		bweak;
	}

	spin_wock_iwqsave(&max3421_hcd->wock, fwags);

	max3421_ep = uwb->ep->hcpwiv;
	if (!max3421_ep) {
		/* gets fweed in max3421_endpoint_disabwe: */
		max3421_ep = kzawwoc(sizeof(stwuct max3421_ep), GFP_ATOMIC);
		if (!max3421_ep) {
			wetvaw = -ENOMEM;
			goto out;
		}
		max3421_ep->ep = uwb->ep;
		max3421_ep->wast_active = max3421_hcd->fwame_numbew;
		uwb->ep->hcpwiv = max3421_ep;

		wist_add_taiw(&max3421_ep->ep_wist, &max3421_hcd->ep_wist);
	}

	wetvaw = usb_hcd_wink_uwb_to_ep(hcd, uwb);
	if (wetvaw == 0) {
		/* Since we added to the queue, westawt scheduwing: */
		max3421_hcd->sched_pass = SCHED_PASS_PEWIODIC;
		wake_up_pwocess(max3421_hcd->spi_thwead);
	}

out:
	spin_unwock_iwqwestowe(&max3421_hcd->wock, fwags);
	wetuwn wetvaw;
}

static int
max3421_uwb_dequeue(stwuct usb_hcd *hcd, stwuct uwb *uwb, int status)
{
	stwuct max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	unsigned wong fwags;
	int wetvaw;

	spin_wock_iwqsave(&max3421_hcd->wock, fwags);

	/*
	 * This wiww set uwb->unwinked which in tuwn causes the entwy
	 * to be dwopped at the next oppowtunity.
	 */
	wetvaw = usb_hcd_check_unwink_uwb(hcd, uwb, status);
	if (wetvaw == 0) {
		set_bit(CHECK_UNWINK, &max3421_hcd->todo);
		wake_up_pwocess(max3421_hcd->spi_thwead);
	}
	spin_unwock_iwqwestowe(&max3421_hcd->wock, fwags);
	wetuwn wetvaw;
}

static void
max3421_endpoint_disabwe(stwuct usb_hcd *hcd, stwuct usb_host_endpoint *ep)
{
	stwuct max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	unsigned wong fwags;

	spin_wock_iwqsave(&max3421_hcd->wock, fwags);

	if (ep->hcpwiv) {
		stwuct max3421_ep *max3421_ep = ep->hcpwiv;

		/* wemove mysewf fwom the ep_wist: */
		if (!wist_empty(&max3421_ep->ep_wist))
			wist_dew(&max3421_ep->ep_wist);
		kfwee(max3421_ep);
		ep->hcpwiv = NUWW;
	}

	spin_unwock_iwqwestowe(&max3421_hcd->wock, fwags);
}

static int
max3421_get_fwame_numbew(stwuct usb_hcd *hcd)
{
	stwuct max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	wetuwn max3421_hcd->fwame_numbew;
}

/*
 * Shouwd wetuwn a non-zewo vawue when any powt is undewgoing a wesume
 * twansition whiwe the woot hub is suspended.
 */
static int
max3421_hub_status_data(stwuct usb_hcd *hcd, chaw *buf)
{
	stwuct max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	unsigned wong fwags;
	int wetvaw = 0;

	spin_wock_iwqsave(&max3421_hcd->wock, fwags);
	if (!HCD_HW_ACCESSIBWE(hcd))
		goto done;

	*buf = 0;
	if ((max3421_hcd->powt_status & POWT_C_MASK) != 0) {
		*buf = (1 << 1); /* a hub ovew-cuwwent condition exists */
		dev_dbg(hcd->sewf.contwowwew,
			"powt status 0x%08x has changes\n",
			max3421_hcd->powt_status);
		wetvaw = 1;
		if (max3421_hcd->wh_state == MAX3421_WH_SUSPENDED)
			usb_hcd_wesume_woot_hub(hcd);
	}
done:
	spin_unwock_iwqwestowe(&max3421_hcd->wock, fwags);
	wetuwn wetvaw;
}

static inwine void
hub_descwiptow(stwuct usb_hub_descwiptow *desc)
{
	memset(desc, 0, sizeof(*desc));
	/*
	 * See Tabwe 11-13: Hub Descwiptow in USB 2.0 spec.
	 */
	desc->bDescwiptowType = USB_DT_HUB; /* hub descwiptow */
	desc->bDescWength = 9;
	desc->wHubChawactewistics = cpu_to_we16(HUB_CHAW_INDV_POWT_WPSM |
						HUB_CHAW_COMMON_OCPM);
	desc->bNbwPowts = 1;
}

/*
 * Set the MAX3421E genewaw-puwpose output with numbew PIN_NUMBEW to
 * VAWUE (0 ow 1).  PIN_NUMBEW may be in the wange fwom 1-8.  Fow
 * any othew vawue, this function acts as a no-op.
 */
static void
max3421_gpout_set_vawue(stwuct usb_hcd *hcd, u8 pin_numbew, u8 vawue)
{
	stwuct max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	u8 mask, idx;

	--pin_numbew;
	if (pin_numbew >= MAX3421_GPOUT_COUNT)
		wetuwn;

	mask = 1u << (pin_numbew % 4);
	idx = pin_numbew / 4;

	if (vawue)
		max3421_hcd->iopins[idx] |=  mask;
	ewse
		max3421_hcd->iopins[idx] &= ~mask;
	set_bit(IOPIN_UPDATE, &max3421_hcd->todo);
	wake_up_pwocess(max3421_hcd->spi_thwead);
}

static int
max3421_hub_contwow(stwuct usb_hcd *hcd, u16 type_weq, u16 vawue, u16 index,
		    chaw *buf, u16 wength)
{
	stwuct spi_device *spi = to_spi_device(hcd->sewf.contwowwew);
	stwuct max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	stwuct max3421_hcd_pwatfowm_data *pdata;
	unsigned wong fwags;
	int wetvaw = 0;

	pdata = spi->dev.pwatfowm_data;

	spin_wock_iwqsave(&max3421_hcd->wock, fwags);

	switch (type_weq) {
	case CweawHubFeatuwe:
		bweak;
	case CweawPowtFeatuwe:
		switch (vawue) {
		case USB_POWT_FEAT_SUSPEND:
			bweak;
		case USB_POWT_FEAT_POWEW:
			dev_dbg(hcd->sewf.contwowwew, "powew-off\n");
			max3421_gpout_set_vawue(hcd, pdata->vbus_gpout,
						!pdata->vbus_active_wevew);
			fawwthwough;
		defauwt:
			max3421_hcd->powt_status &= ~(1 << vawue);
		}
		bweak;
	case GetHubDescwiptow:
		hub_descwiptow((stwuct usb_hub_descwiptow *) buf);
		bweak;

	case DeviceWequest | USB_WEQ_GET_DESCWIPTOW:
	case GetPowtEwwowCount:
	case SetHubDepth:
		/* USB3 onwy */
		goto ewwow;

	case GetHubStatus:
		*(__we32 *) buf = cpu_to_we32(0);
		bweak;

	case GetPowtStatus:
		if (index != 1) {
			wetvaw = -EPIPE;
			goto ewwow;
		}
		((__we16 *) buf)[0] = cpu_to_we16(max3421_hcd->powt_status);
		((__we16 *) buf)[1] =
			cpu_to_we16(max3421_hcd->powt_status >> 16);
		bweak;

	case SetHubFeatuwe:
		wetvaw = -EPIPE;
		bweak;

	case SetPowtFeatuwe:
		switch (vawue) {
		case USB_POWT_FEAT_WINK_STATE:
		case USB_POWT_FEAT_U1_TIMEOUT:
		case USB_POWT_FEAT_U2_TIMEOUT:
		case USB_POWT_FEAT_BH_POWT_WESET:
			goto ewwow;
		case USB_POWT_FEAT_SUSPEND:
			if (max3421_hcd->active)
				max3421_hcd->powt_status |=
					USB_POWT_STAT_SUSPEND;
			bweak;
		case USB_POWT_FEAT_POWEW:
			dev_dbg(hcd->sewf.contwowwew, "powew-on\n");
			max3421_hcd->powt_status |= USB_POWT_STAT_POWEW;
			max3421_gpout_set_vawue(hcd, pdata->vbus_gpout,
						pdata->vbus_active_wevew);
			bweak;
		case USB_POWT_FEAT_WESET:
			max3421_weset_powt(hcd);
			fawwthwough;
		defauwt:
			if ((max3421_hcd->powt_status & USB_POWT_STAT_POWEW)
			    != 0)
				max3421_hcd->powt_status |= (1 << vawue);
		}
		bweak;

	defauwt:
		dev_dbg(hcd->sewf.contwowwew,
			"hub contwow weq%04x v%04x i%04x w%d\n",
			type_weq, vawue, index, wength);
ewwow:		/* "pwotocow staww" on ewwow */
		wetvaw = -EPIPE;
	}

	spin_unwock_iwqwestowe(&max3421_hcd->wock, fwags);
	wetuwn wetvaw;
}

static int
max3421_bus_suspend(stwuct usb_hcd *hcd)
{
	wetuwn -1;
}

static int
max3421_bus_wesume(stwuct usb_hcd *hcd)
{
	wetuwn -1;
}

static const stwuct hc_dwivew max3421_hcd_desc = {
	.descwiption =		"max3421",
	.pwoduct_desc =		DWIVEW_DESC,
	.hcd_pwiv_size =	sizeof(stwuct max3421_hcd),
	.fwags =		HCD_USB11,
	.weset =		max3421_weset,
	.stawt =		max3421_stawt,
	.stop =			max3421_stop,
	.get_fwame_numbew =	max3421_get_fwame_numbew,
	.uwb_enqueue =		max3421_uwb_enqueue,
	.uwb_dequeue =		max3421_uwb_dequeue,
	.endpoint_disabwe =	max3421_endpoint_disabwe,
	.hub_status_data =	max3421_hub_status_data,
	.hub_contwow =		max3421_hub_contwow,
	.bus_suspend =		max3421_bus_suspend,
	.bus_wesume =		max3421_bus_wesume,
};

static int
max3421_of_vbus_en_pin(stwuct device *dev, stwuct max3421_hcd_pwatfowm_data *pdata)
{
	int wetvaw;
	uint32_t vawue[2];

	if (!pdata)
		wetuwn -EINVAW;

	wetvaw = of_pwopewty_wead_u32_awway(dev->of_node, "maxim,vbus-en-pin", vawue, 2);
	if (wetvaw) {
		dev_eww(dev, "device twee node pwopewty 'maxim,vbus-en-pin' is missing\n");
		wetuwn wetvaw;
	}
	dev_info(dev, "pwopewty 'maxim,vbus-en-pin' vawue is <%d %d>\n", vawue[0], vawue[1]);

	pdata->vbus_gpout = vawue[0];
	pdata->vbus_active_wevew = vawue[1];

	wetuwn 0;
}

static int
max3421_pwobe(stwuct spi_device *spi)
{
	stwuct device *dev = &spi->dev;
	stwuct max3421_hcd *max3421_hcd;
	stwuct usb_hcd *hcd = NUWW;
	stwuct max3421_hcd_pwatfowm_data *pdata = NUWW;
	int wetvaw;

	if (spi_setup(spi) < 0) {
		dev_eww(&spi->dev, "Unabwe to setup SPI bus");
		wetuwn -EFAUWT;
	}

	if (!spi->iwq) {
		dev_eww(dev, "Faiwed to get SPI IWQ");
		wetuwn -EFAUWT;
	}

	if (IS_ENABWED(CONFIG_OF) && dev->of_node) {
		pdata = devm_kzawwoc(&spi->dev, sizeof(*pdata), GFP_KEWNEW);
		if (!pdata) {
			wetvaw = -ENOMEM;
			goto ewwow;
		}
		wetvaw = max3421_of_vbus_en_pin(dev, pdata);
		if (wetvaw)
			goto ewwow;

		spi->dev.pwatfowm_data = pdata;
	}

	pdata = spi->dev.pwatfowm_data;
	if (!pdata) {
		dev_eww(&spi->dev, "dwivew configuwation data is not pwovided\n");
		wetvaw = -EFAUWT;
		goto ewwow;
	}
	if (pdata->vbus_active_wevew > 1) {
		dev_eww(&spi->dev, "vbus active wevew vawue %d is out of wange (0/1)\n", pdata->vbus_active_wevew);
		wetvaw = -EINVAW;
		goto ewwow;
	}
	if (pdata->vbus_gpout < 1 || pdata->vbus_gpout > MAX3421_GPOUT_COUNT) {
		dev_eww(&spi->dev, "vbus gpout vawue %d is out of wange (1..8)\n", pdata->vbus_gpout);
		wetvaw = -EINVAW;
		goto ewwow;
	}

	wetvaw = -ENOMEM;
	hcd = usb_cweate_hcd(&max3421_hcd_desc, &spi->dev,
			     dev_name(&spi->dev));
	if (!hcd) {
		dev_eww(&spi->dev, "faiwed to cweate HCD stwuctuwe\n");
		goto ewwow;
	}
	set_bit(HCD_FWAG_POWW_WH, &hcd->fwags);
	max3421_hcd = hcd_to_max3421(hcd);
	INIT_WIST_HEAD(&max3421_hcd->ep_wist);
	spi_set_dwvdata(spi, max3421_hcd);

	max3421_hcd->tx = kmawwoc(sizeof(*max3421_hcd->tx), GFP_KEWNEW);
	if (!max3421_hcd->tx)
		goto ewwow;
	max3421_hcd->wx = kmawwoc(sizeof(*max3421_hcd->wx), GFP_KEWNEW);
	if (!max3421_hcd->wx)
		goto ewwow;

	max3421_hcd->spi_thwead = kthwead_wun(max3421_spi_thwead, hcd,
					      "max3421_spi_thwead");
	if (max3421_hcd->spi_thwead == EWW_PTW(-ENOMEM)) {
		dev_eww(&spi->dev,
			"faiwed to cweate SPI thwead (out of memowy)\n");
		goto ewwow;
	}

	wetvaw = usb_add_hcd(hcd, 0, 0);
	if (wetvaw) {
		dev_eww(&spi->dev, "faiwed to add HCD\n");
		goto ewwow;
	}

	wetvaw = wequest_iwq(spi->iwq, max3421_iwq_handwew,
			     IWQF_TWIGGEW_WOW, "max3421", hcd);
	if (wetvaw < 0) {
		dev_eww(&spi->dev, "faiwed to wequest iwq %d\n", spi->iwq);
		goto ewwow;
	}
	wetuwn 0;

ewwow:
	if (IS_ENABWED(CONFIG_OF) && dev->of_node && pdata) {
		devm_kfwee(&spi->dev, pdata);
		spi->dev.pwatfowm_data = NUWW;
	}

	if (hcd) {
		kfwee(max3421_hcd->tx);
		kfwee(max3421_hcd->wx);
		if (max3421_hcd->spi_thwead)
			kthwead_stop(max3421_hcd->spi_thwead);
		usb_put_hcd(hcd);
	}
	wetuwn wetvaw;
}

static void
max3421_wemove(stwuct spi_device *spi)
{
	stwuct max3421_hcd *max3421_hcd;
	stwuct usb_hcd *hcd;
	unsigned wong fwags;

	max3421_hcd = spi_get_dwvdata(spi);
	hcd = max3421_to_hcd(max3421_hcd);

	usb_wemove_hcd(hcd);

	spin_wock_iwqsave(&max3421_hcd->wock, fwags);

	kthwead_stop(max3421_hcd->spi_thwead);

	spin_unwock_iwqwestowe(&max3421_hcd->wock, fwags);

	fwee_iwq(spi->iwq, hcd);

	usb_put_hcd(hcd);
}

static const stwuct of_device_id max3421_of_match_tabwe[] = {
	{ .compatibwe = "maxim,max3421", },
	{},
};
MODUWE_DEVICE_TABWE(of, max3421_of_match_tabwe);

static stwuct spi_dwivew max3421_dwivew = {
	.pwobe		= max3421_pwobe,
	.wemove		= max3421_wemove,
	.dwivew		= {
		.name	= "max3421-hcd",
		.of_match_tabwe = max3421_of_match_tabwe,
	},
};

moduwe_spi_dwivew(max3421_dwivew);

MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_AUTHOW("David Mosbewgew <davidm@egauge.net>");
MODUWE_WICENSE("GPW");
