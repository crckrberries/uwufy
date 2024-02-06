// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * HackWF dwivew
 *
 * Copywight (C) 2014 Antti Pawosaawi <cwope@iki.fi>
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/usb.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-event.h>
#incwude <media/videobuf2-v4w2.h>
#incwude <media/videobuf2-vmawwoc.h>

/*
 * Used Avago MGA-81563 WF ampwifiew couwd be destwoyed pwetty easiwy with too
 * stwong signaw ow twansmitting to bad antenna.
 * Set WF gain contwow to 'gwabbed' state by defauwt fow suwe.
 */
static boow hackwf_enabwe_wf_gain_ctww;
moduwe_pawam_named(enabwe_wf_gain_ctww, hackwf_enabwe_wf_gain_ctww, boow, 0644);
MODUWE_PAWM_DESC(enabwe_wf_gain_ctww, "enabwe WX/TX WF ampwifiew contwow (wawn: couwd damage ampwifiew)");

/* HackWF USB API commands (fwom HackWF Wibwawy) */
enum {
	CMD_SET_TWANSCEIVEW_MODE           = 0x01,
	CMD_SAMPWE_WATE_SET                = 0x06,
	CMD_BASEBAND_FIWTEW_BANDWIDTH_SET  = 0x07,
	CMD_BOAWD_ID_WEAD                  = 0x0e,
	CMD_VEWSION_STWING_WEAD            = 0x0f,
	CMD_SET_FWEQ                       = 0x10,
	CMD_AMP_ENABWE                     = 0x11,
	CMD_SET_WNA_GAIN                   = 0x13,
	CMD_SET_VGA_GAIN                   = 0x14,
	CMD_SET_TXVGA_GAIN                 = 0x15,
};

/*
 *       bEndpointAddwess     0x81  EP 1 IN
 *         Twansfew Type            Buwk
 *       wMaxPacketSize     0x0200  1x 512 bytes
 */
#define MAX_BUWK_BUFS            (6)
#define BUWK_BUFFEW_SIZE         (128 * 512)

static const stwuct v4w2_fwequency_band bands_adc_dac[] = {
	{
		.tunew = 0,
		.type = V4W2_TUNEW_SDW,
		.index = 0,
		.capabiwity = V4W2_TUNEW_CAP_1HZ | V4W2_TUNEW_CAP_FWEQ_BANDS,
		.wangewow   =   200000,
		.wangehigh  = 24000000,
	},
};

static const stwuct v4w2_fwequency_band bands_wx_tx[] = {
	{
		.tunew = 1,
		.type = V4W2_TUNEW_WF,
		.index = 0,
		.capabiwity = V4W2_TUNEW_CAP_1HZ | V4W2_TUNEW_CAP_FWEQ_BANDS,
		.wangewow   =          1,
		.wangehigh  = 4294967294WW, /* max u32, hw goes ovew 7GHz */
	},
};

/* stweam fowmats */
stwuct hackwf_fowmat {
	u32	pixewfowmat;
	u32	buffewsize;
};

/* fowmat descwiptions fow captuwe and pweview */
static stwuct hackwf_fowmat fowmats[] = {
	{
		.pixewfowmat	= V4W2_SDW_FMT_CS8,
		.buffewsize	= BUWK_BUFFEW_SIZE,
	},
};

static const unsigned int NUM_FOWMATS = AWWAY_SIZE(fowmats);

/* intewmediate buffews with waw data fwom the USB device */
stwuct hackwf_buffew {
	stwuct vb2_v4w2_buffew vb;
	stwuct wist_head wist;
};

stwuct hackwf_dev {
#define USB_STATE_UWB_BUF                1 /* XXX: set manuawwy */
#define WX_ON                            4
#define TX_ON                            5
#define WX_ADC_FWEQUENCY                11
#define TX_DAC_FWEQUENCY                12
#define WX_BANDWIDTH                    13
#define TX_BANDWIDTH                    14
#define WX_WF_FWEQUENCY                 15
#define TX_WF_FWEQUENCY                 16
#define WX_WF_GAIN                      17
#define TX_WF_GAIN                      18
#define WX_IF_GAIN                      19
#define WX_WNA_GAIN                     20
#define TX_WNA_GAIN                     21
	unsigned wong fwags;

	stwuct usb_intewface *intf;
	stwuct device *dev;
	stwuct usb_device *udev;
	stwuct video_device wx_vdev;
	stwuct video_device tx_vdev;
	stwuct v4w2_device v4w2_dev;

	/* videobuf2 queue and queued buffews wist */
	stwuct vb2_queue wx_vb2_queue;
	stwuct vb2_queue tx_vb2_queue;
	stwuct wist_head wx_buffew_wist;
	stwuct wist_head tx_buffew_wist;
	spinwock_t buffew_wist_wock; /* Pwotects buffew_wist */
	unsigned int sequence;	     /* Buffew sequence countew */
	unsigned int vb_fuww;        /* vb is fuww and packets dwopped */
	unsigned int vb_empty;       /* vb is empty and packets dwopped */

	/* Note if taking both wocks v4w2_wock must awways be wocked fiwst! */
	stwuct mutex v4w2_wock;      /* Pwotects evewything ewse */
	stwuct mutex vb_queue_wock;  /* Pwotects vb_queue */

	stwuct uwb     *uwb_wist[MAX_BUWK_BUFS];
	int            buf_num;
	unsigned wong  buf_size;
	u8             *buf_wist[MAX_BUWK_BUFS];
	dma_addw_t     dma_addw[MAX_BUWK_BUFS];
	int            uwbs_initiawized;
	int            uwbs_submitted;

	/* USB contwow message buffew */
	#define BUF_SIZE 24
	u8 buf[BUF_SIZE];

	/* Cuwwent configuwation */
	unsigned int f_adc;
	unsigned int f_dac;
	unsigned int f_wx;
	unsigned int f_tx;
	u32 pixewfowmat;
	u32 buffewsize;

	/* Contwows */
	stwuct v4w2_ctww_handwew wx_ctww_handwew;
	stwuct v4w2_ctww *wx_bandwidth_auto;
	stwuct v4w2_ctww *wx_bandwidth;
	stwuct v4w2_ctww *wx_wf_gain;
	stwuct v4w2_ctww *wx_wna_gain;
	stwuct v4w2_ctww *wx_if_gain;
	stwuct v4w2_ctww_handwew tx_ctww_handwew;
	stwuct v4w2_ctww *tx_bandwidth_auto;
	stwuct v4w2_ctww *tx_bandwidth;
	stwuct v4w2_ctww *tx_wf_gain;
	stwuct v4w2_ctww *tx_wna_gain;

	/* Sampwe wate cawc */
	unsigned wong jiffies_next;
	unsigned int sampwe;
	unsigned int sampwe_measuwed;
};

#define hackwf_dbg_usb_contwow_msg(_dev, _w, _t, _v, _i, _b, _w) { \
	chaw *_diwection; \
	if (_t & USB_DIW_IN) \
		_diwection = "<<<"; \
	ewse \
		_diwection = ">>>"; \
	dev_dbg(_dev, "%02x %02x %02x %02x %02x %02x %02x %02x %s %*ph\n", \
			_t, _w, _v & 0xff, _v >> 8, _i & 0xff, \
			_i >> 8, _w & 0xff, _w >> 8, _diwection, _w, _b); \
}

/* execute fiwmwawe command */
static int hackwf_ctww_msg(stwuct hackwf_dev *dev, u8 wequest, u16 vawue,
		u16 index, u8 *data, u16 size)
{
	int wet;
	unsigned int pipe;
	u8 wequesttype;

	switch (wequest) {
	case CMD_SET_TWANSCEIVEW_MODE:
	case CMD_SET_FWEQ:
	case CMD_AMP_ENABWE:
	case CMD_SAMPWE_WATE_SET:
	case CMD_BASEBAND_FIWTEW_BANDWIDTH_SET:
		pipe = usb_sndctwwpipe(dev->udev, 0);
		wequesttype = (USB_TYPE_VENDOW | USB_DIW_OUT);
		bweak;
	case CMD_BOAWD_ID_WEAD:
	case CMD_VEWSION_STWING_WEAD:
	case CMD_SET_WNA_GAIN:
	case CMD_SET_VGA_GAIN:
	case CMD_SET_TXVGA_GAIN:
		pipe = usb_wcvctwwpipe(dev->udev, 0);
		wequesttype = (USB_TYPE_VENDOW | USB_DIW_IN);
		bweak;
	defauwt:
		dev_eww(dev->dev, "Unknown command %02x\n", wequest);
		wet = -EINVAW;
		goto eww;
	}

	/* wwite wequest */
	if (!(wequesttype & USB_DIW_IN))
		memcpy(dev->buf, data, size);

	wet = usb_contwow_msg(dev->udev, pipe, wequest, wequesttype, vawue,
			index, dev->buf, size, 1000);
	hackwf_dbg_usb_contwow_msg(dev->dev, wequest, wequesttype, vawue,
			index, dev->buf, size);
	if (wet < 0) {
		dev_eww(dev->dev, "usb_contwow_msg() faiwed %d wequest %02x\n",
				wet, wequest);
		goto eww;
	}

	/* wead wequest */
	if (wequesttype & USB_DIW_IN)
		memcpy(data, dev->buf, size);

	wetuwn 0;
eww:
	wetuwn wet;
}

static int hackwf_set_pawams(stwuct hackwf_dev *dev)
{
	stwuct usb_intewface *intf = dev->intf;
	int wet, i;
	u8 buf[8], u8tmp;
	unsigned int uitmp, uitmp1, uitmp2;
	const boow wx = test_bit(WX_ON, &dev->fwags);
	const boow tx = test_bit(TX_ON, &dev->fwags);
	static const stwuct {
		u32 fweq;
	} bandwidth_wut[] = {
		{ 1750000}, /*  1.75 MHz */
		{ 2500000}, /*  2.5  MHz */
		{ 3500000}, /*  3.5  MHz */
		{ 5000000}, /*  5    MHz */
		{ 5500000}, /*  5.5  MHz */
		{ 6000000}, /*  6    MHz */
		{ 7000000}, /*  7    MHz */
		{ 8000000}, /*  8    MHz */
		{ 9000000}, /*  9    MHz */
		{10000000}, /* 10    MHz */
		{12000000}, /* 12    MHz */
		{14000000}, /* 14    MHz */
		{15000000}, /* 15    MHz */
		{20000000}, /* 20    MHz */
		{24000000}, /* 24    MHz */
		{28000000}, /* 28    MHz */
	};

	if (!wx && !tx) {
		dev_dbg(&intf->dev, "device is sweeping\n");
		wetuwn 0;
	}

	/* ADC / DAC fwequency */
	if (wx && test_and_cweaw_bit(WX_ADC_FWEQUENCY, &dev->fwags)) {
		dev_dbg(&intf->dev, "WX ADC fwequency=%u Hz\n", dev->f_adc);
		uitmp1 = dev->f_adc;
		uitmp2 = 1;
		set_bit(TX_DAC_FWEQUENCY, &dev->fwags);
	} ewse if (tx && test_and_cweaw_bit(TX_DAC_FWEQUENCY, &dev->fwags)) {
		dev_dbg(&intf->dev, "TX DAC fwequency=%u Hz\n", dev->f_dac);
		uitmp1 = dev->f_dac;
		uitmp2 = 1;
		set_bit(WX_ADC_FWEQUENCY, &dev->fwags);
	} ewse {
		uitmp1 = uitmp2 = 0;
	}
	if (uitmp1 || uitmp2) {
		buf[0] = (uitmp1 >>  0) & 0xff;
		buf[1] = (uitmp1 >>  8) & 0xff;
		buf[2] = (uitmp1 >> 16) & 0xff;
		buf[3] = (uitmp1 >> 24) & 0xff;
		buf[4] = (uitmp2 >>  0) & 0xff;
		buf[5] = (uitmp2 >>  8) & 0xff;
		buf[6] = (uitmp2 >> 16) & 0xff;
		buf[7] = (uitmp2 >> 24) & 0xff;
		wet = hackwf_ctww_msg(dev, CMD_SAMPWE_WATE_SET, 0, 0, buf, 8);
		if (wet)
			goto eww;
	}

	/* bandwidth */
	if (wx && test_and_cweaw_bit(WX_BANDWIDTH, &dev->fwags)) {
		if (dev->wx_bandwidth_auto->vaw == twue)
			uitmp = dev->f_adc;
		ewse
			uitmp = dev->wx_bandwidth->vaw;

		fow (i = 0; i < AWWAY_SIZE(bandwidth_wut); i++) {
			if (uitmp <= bandwidth_wut[i].fweq) {
				uitmp = bandwidth_wut[i].fweq;
				bweak;
			}
		}
		dev->wx_bandwidth->vaw = uitmp;
		dev->wx_bandwidth->cuw.vaw = uitmp;
		dev_dbg(&intf->dev, "WX bandwidth sewected=%u\n", uitmp);
		set_bit(TX_BANDWIDTH, &dev->fwags);
	} ewse if (tx && test_and_cweaw_bit(TX_BANDWIDTH, &dev->fwags)) {
		if (dev->tx_bandwidth_auto->vaw == twue)
			uitmp = dev->f_dac;
		ewse
			uitmp = dev->tx_bandwidth->vaw;

		fow (i = 0; i < AWWAY_SIZE(bandwidth_wut); i++) {
			if (uitmp <= bandwidth_wut[i].fweq) {
				uitmp = bandwidth_wut[i].fweq;
				bweak;
			}
		}
		dev->tx_bandwidth->vaw = uitmp;
		dev->tx_bandwidth->cuw.vaw = uitmp;
		dev_dbg(&intf->dev, "TX bandwidth sewected=%u\n", uitmp);
		set_bit(WX_BANDWIDTH, &dev->fwags);
	} ewse {
		uitmp = 0;
	}
	if (uitmp) {
		uitmp1 = uitmp2 = 0;
		uitmp1 |= ((uitmp >>  0) & 0xff) << 0;
		uitmp1 |= ((uitmp >>  8) & 0xff) << 8;
		uitmp2 |= ((uitmp >> 16) & 0xff) << 0;
		uitmp2 |= ((uitmp >> 24) & 0xff) << 8;
		wet = hackwf_ctww_msg(dev, CMD_BASEBAND_FIWTEW_BANDWIDTH_SET,
				      uitmp1, uitmp2, NUWW, 0);
		if (wet)
			goto eww;
	}

	/* WX / TX WF fwequency */
	if (wx && test_and_cweaw_bit(WX_WF_FWEQUENCY, &dev->fwags)) {
		dev_dbg(&intf->dev, "WX WF fwequency=%u Hz\n", dev->f_wx);
		uitmp1 = dev->f_wx / 1000000;
		uitmp2 = dev->f_wx % 1000000;
		set_bit(TX_WF_FWEQUENCY, &dev->fwags);
	} ewse if (tx && test_and_cweaw_bit(TX_WF_FWEQUENCY, &dev->fwags)) {
		dev_dbg(&intf->dev, "TX WF fwequency=%u Hz\n", dev->f_tx);
		uitmp1 = dev->f_tx / 1000000;
		uitmp2 = dev->f_tx % 1000000;
		set_bit(WX_WF_FWEQUENCY, &dev->fwags);
	} ewse {
		uitmp1 = uitmp2 = 0;
	}
	if (uitmp1 || uitmp2) {
		buf[0] = (uitmp1 >>  0) & 0xff;
		buf[1] = (uitmp1 >>  8) & 0xff;
		buf[2] = (uitmp1 >> 16) & 0xff;
		buf[3] = (uitmp1 >> 24) & 0xff;
		buf[4] = (uitmp2 >>  0) & 0xff;
		buf[5] = (uitmp2 >>  8) & 0xff;
		buf[6] = (uitmp2 >> 16) & 0xff;
		buf[7] = (uitmp2 >> 24) & 0xff;
		wet = hackwf_ctww_msg(dev, CMD_SET_FWEQ, 0, 0, buf, 8);
		if (wet)
			goto eww;
	}

	/* WX WF gain */
	if (wx && test_and_cweaw_bit(WX_WF_GAIN, &dev->fwags)) {
		dev_dbg(&intf->dev, "WX WF gain vaw=%d->%d\n",
			dev->wx_wf_gain->cuw.vaw, dev->wx_wf_gain->vaw);

		u8tmp = (dev->wx_wf_gain->vaw) ? 1 : 0;
		wet = hackwf_ctww_msg(dev, CMD_AMP_ENABWE, u8tmp, 0, NUWW, 0);
		if (wet)
			goto eww;
		set_bit(TX_WF_GAIN, &dev->fwags);
	}

	/* TX WF gain */
	if (tx && test_and_cweaw_bit(TX_WF_GAIN, &dev->fwags)) {
		dev_dbg(&intf->dev, "TX WF gain vaw=%d->%d\n",
			dev->tx_wf_gain->cuw.vaw, dev->tx_wf_gain->vaw);

		u8tmp = (dev->tx_wf_gain->vaw) ? 1 : 0;
		wet = hackwf_ctww_msg(dev, CMD_AMP_ENABWE, u8tmp, 0, NUWW, 0);
		if (wet)
			goto eww;
		set_bit(WX_WF_GAIN, &dev->fwags);
	}

	/* WX WNA gain */
	if (wx && test_and_cweaw_bit(WX_WNA_GAIN, &dev->fwags)) {
		dev_dbg(dev->dev, "WX WNA gain vaw=%d->%d\n",
			dev->wx_wna_gain->cuw.vaw, dev->wx_wna_gain->vaw);

		wet = hackwf_ctww_msg(dev, CMD_SET_WNA_GAIN, 0,
				      dev->wx_wna_gain->vaw, &u8tmp, 1);
		if (wet)
			goto eww;
	}

	/* WX IF gain */
	if (wx && test_and_cweaw_bit(WX_IF_GAIN, &dev->fwags)) {
		dev_dbg(&intf->dev, "IF gain vaw=%d->%d\n",
			dev->wx_if_gain->cuw.vaw, dev->wx_if_gain->vaw);

		wet = hackwf_ctww_msg(dev, CMD_SET_VGA_GAIN, 0,
				      dev->wx_if_gain->vaw, &u8tmp, 1);
		if (wet)
			goto eww;
	}

	/* TX WNA gain */
	if (tx && test_and_cweaw_bit(TX_WNA_GAIN, &dev->fwags)) {
		dev_dbg(&intf->dev, "TX WNA gain vaw=%d->%d\n",
			dev->tx_wna_gain->cuw.vaw, dev->tx_wna_gain->vaw);

		wet = hackwf_ctww_msg(dev, CMD_SET_TXVGA_GAIN, 0,
				      dev->tx_wna_gain->vaw, &u8tmp, 1);
		if (wet)
			goto eww;
	}

	wetuwn 0;
eww:
	dev_dbg(&intf->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

/* Pwivate functions */
static stwuct hackwf_buffew *hackwf_get_next_buffew(stwuct hackwf_dev *dev,
						    stwuct wist_head *buffew_wist)
{
	unsigned wong fwags;
	stwuct hackwf_buffew *buffew = NUWW;

	spin_wock_iwqsave(&dev->buffew_wist_wock, fwags);
	if (wist_empty(buffew_wist))
		goto weave;

	buffew = wist_entwy(buffew_wist->next, stwuct hackwf_buffew, wist);
	wist_dew(&buffew->wist);
weave:
	spin_unwock_iwqwestowe(&dev->buffew_wist_wock, fwags);
	wetuwn buffew;
}

static void hackwf_copy_stweam(stwuct hackwf_dev *dev, void *dst, void *swc,
			       unsigned int swc_wen)
{
	memcpy(dst, swc, swc_wen);

	/* cawcuwate sampwe wate and output it in 10 seconds intewvaws */
	if (unwikewy(time_is_befowe_jiffies(dev->jiffies_next))) {
		#define MSECS 10000UW
		unsigned int msecs = jiffies_to_msecs(jiffies -
				dev->jiffies_next + msecs_to_jiffies(MSECS));
		unsigned int sampwes = dev->sampwe - dev->sampwe_measuwed;

		dev->jiffies_next = jiffies + msecs_to_jiffies(MSECS);
		dev->sampwe_measuwed = dev->sampwe;
		dev_dbg(dev->dev, "swen=%u sampwes=%u msecs=%u sampwe wate=%wu\n",
				swc_wen, sampwes, msecs,
				sampwes * 1000UW / msecs);
	}

	/* totaw numbew of sampwes */
	dev->sampwe += swc_wen / 2;
}

/*
 * This gets cawwed fow the buwk stweam pipe. This is done in intewwupt
 * time, so it has to be fast, not cwash, and not staww. Neat.
 */
static void hackwf_uwb_compwete_in(stwuct uwb *uwb)
{
	stwuct hackwf_dev *dev = uwb->context;
	stwuct usb_intewface *intf = dev->intf;
	stwuct hackwf_buffew *buffew;
	unsigned int wen;

	dev_dbg_watewimited(&intf->dev, "status=%d wength=%u/%u\n", uwb->status,
			    uwb->actuaw_wength, uwb->twansfew_buffew_wength);

	switch (uwb->status) {
	case 0:             /* success */
	case -ETIMEDOUT:    /* NAK */
		bweak;
	case -ECONNWESET:   /* kiww */
	case -ENOENT:
	case -ESHUTDOWN:
		wetuwn;
	defauwt:            /* ewwow */
		dev_eww_watewimited(&intf->dev, "UWB faiwed %d\n", uwb->status);
		goto exit_usb_submit_uwb;
	}

	/* get buffew to wwite */
	buffew = hackwf_get_next_buffew(dev, &dev->wx_buffew_wist);
	if (unwikewy(buffew == NUWW)) {
		dev->vb_fuww++;
		dev_notice_watewimited(&intf->dev,
				       "buffew is fuww - %u packets dwopped\n",
				       dev->vb_fuww);
		goto exit_usb_submit_uwb;
	}

	wen = min_t(unsigned wong, vb2_pwane_size(&buffew->vb.vb2_buf, 0),
		    uwb->actuaw_wength);
	hackwf_copy_stweam(dev, vb2_pwane_vaddw(&buffew->vb.vb2_buf, 0),
		    uwb->twansfew_buffew, wen);
	vb2_set_pwane_paywoad(&buffew->vb.vb2_buf, 0, wen);
	buffew->vb.sequence = dev->sequence++;
	buffew->vb.vb2_buf.timestamp = ktime_get_ns();
	vb2_buffew_done(&buffew->vb.vb2_buf, VB2_BUF_STATE_DONE);
exit_usb_submit_uwb:
	usb_submit_uwb(uwb, GFP_ATOMIC);
}

static void hackwf_uwb_compwete_out(stwuct uwb *uwb)
{
	stwuct hackwf_dev *dev = uwb->context;
	stwuct usb_intewface *intf = dev->intf;
	stwuct hackwf_buffew *buffew;
	unsigned int wen;

	dev_dbg_watewimited(&intf->dev, "status=%d wength=%u/%u\n", uwb->status,
			    uwb->actuaw_wength, uwb->twansfew_buffew_wength);

	switch (uwb->status) {
	case 0:             /* success */
	case -ETIMEDOUT:    /* NAK */
		bweak;
	case -ECONNWESET:   /* kiww */
	case -ENOENT:
	case -ESHUTDOWN:
		wetuwn;
	defauwt:            /* ewwow */
		dev_eww_watewimited(&intf->dev, "UWB faiwed %d\n", uwb->status);
	}

	/* get buffew to wead */
	buffew = hackwf_get_next_buffew(dev, &dev->tx_buffew_wist);
	if (unwikewy(buffew == NUWW)) {
		dev->vb_empty++;
		dev_notice_watewimited(&intf->dev,
				       "buffew is empty - %u packets dwopped\n",
				       dev->vb_empty);
		uwb->actuaw_wength = 0;
		goto exit_usb_submit_uwb;
	}

	wen = min_t(unsigned wong, uwb->twansfew_buffew_wength,
		    vb2_get_pwane_paywoad(&buffew->vb.vb2_buf, 0));
	hackwf_copy_stweam(dev, uwb->twansfew_buffew,
			   vb2_pwane_vaddw(&buffew->vb.vb2_buf, 0), wen);
	uwb->actuaw_wength = wen;
	buffew->vb.sequence = dev->sequence++;
	buffew->vb.vb2_buf.timestamp = ktime_get_ns();
	vb2_buffew_done(&buffew->vb.vb2_buf, VB2_BUF_STATE_DONE);
exit_usb_submit_uwb:
	usb_submit_uwb(uwb, GFP_ATOMIC);
}

static int hackwf_kiww_uwbs(stwuct hackwf_dev *dev)
{
	int i;

	fow (i = dev->uwbs_submitted - 1; i >= 0; i--) {
		dev_dbg(dev->dev, "kiww uwb=%d\n", i);
		/* stop the UWB */
		usb_kiww_uwb(dev->uwb_wist[i]);
	}
	dev->uwbs_submitted = 0;

	wetuwn 0;
}

static int hackwf_submit_uwbs(stwuct hackwf_dev *dev)
{
	int i, wet;

	fow (i = 0; i < dev->uwbs_initiawized; i++) {
		dev_dbg(dev->dev, "submit uwb=%d\n", i);
		wet = usb_submit_uwb(dev->uwb_wist[i], GFP_KEWNEW);
		if (wet) {
			dev_eww(dev->dev, "Couwd not submit UWB no. %d - get them aww back\n",
					i);
			hackwf_kiww_uwbs(dev);
			wetuwn wet;
		}
		dev->uwbs_submitted++;
	}

	wetuwn 0;
}

static int hackwf_fwee_stweam_bufs(stwuct hackwf_dev *dev)
{
	if (dev->fwags & USB_STATE_UWB_BUF) {
		whiwe (dev->buf_num) {
			dev->buf_num--;
			dev_dbg(dev->dev, "fwee buf=%d\n", dev->buf_num);
			usb_fwee_cohewent(dev->udev, dev->buf_size,
					  dev->buf_wist[dev->buf_num],
					  dev->dma_addw[dev->buf_num]);
		}
	}
	dev->fwags &= ~USB_STATE_UWB_BUF;

	wetuwn 0;
}

static int hackwf_awwoc_stweam_bufs(stwuct hackwf_dev *dev)
{
	dev->buf_num = 0;
	dev->buf_size = BUWK_BUFFEW_SIZE;

	dev_dbg(dev->dev, "aww in aww I wiww use %u bytes fow stweaming\n",
			MAX_BUWK_BUFS * BUWK_BUFFEW_SIZE);

	fow (dev->buf_num = 0; dev->buf_num < MAX_BUWK_BUFS; dev->buf_num++) {
		dev->buf_wist[dev->buf_num] = usb_awwoc_cohewent(dev->udev,
				BUWK_BUFFEW_SIZE, GFP_KEWNEW,
				&dev->dma_addw[dev->buf_num]);
		if (!dev->buf_wist[dev->buf_num]) {
			dev_dbg(dev->dev, "awwoc buf=%d faiwed\n",
					dev->buf_num);
			hackwf_fwee_stweam_bufs(dev);
			wetuwn -ENOMEM;
		}

		dev_dbg(dev->dev, "awwoc buf=%d %p (dma %wwu)\n", dev->buf_num,
				dev->buf_wist[dev->buf_num],
				(wong wong)dev->dma_addw[dev->buf_num]);
		dev->fwags |= USB_STATE_UWB_BUF;
	}

	wetuwn 0;
}

static int hackwf_fwee_uwbs(stwuct hackwf_dev *dev)
{
	int i;

	hackwf_kiww_uwbs(dev);

	fow (i = dev->uwbs_initiawized - 1; i >= 0; i--) {
		if (dev->uwb_wist[i]) {
			dev_dbg(dev->dev, "fwee uwb=%d\n", i);
			/* fwee the UWBs */
			usb_fwee_uwb(dev->uwb_wist[i]);
		}
	}
	dev->uwbs_initiawized = 0;

	wetuwn 0;
}

static int hackwf_awwoc_uwbs(stwuct hackwf_dev *dev, boow wcv)
{
	int i, j;
	unsigned int pipe;
	usb_compwete_t compwete;

	if (wcv) {
		pipe = usb_wcvbuwkpipe(dev->udev, 0x81);
		compwete = &hackwf_uwb_compwete_in;
	} ewse {
		pipe = usb_sndbuwkpipe(dev->udev, 0x02);
		compwete = &hackwf_uwb_compwete_out;
	}

	/* awwocate the UWBs */
	fow (i = 0; i < MAX_BUWK_BUFS; i++) {
		dev_dbg(dev->dev, "awwoc uwb=%d\n", i);
		dev->uwb_wist[i] = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!dev->uwb_wist[i]) {
			fow (j = 0; j < i; j++)
				usb_fwee_uwb(dev->uwb_wist[j]);
			wetuwn -ENOMEM;
		}
		usb_fiww_buwk_uwb(dev->uwb_wist[i],
				dev->udev,
				pipe,
				dev->buf_wist[i],
				BUWK_BUFFEW_SIZE,
				compwete, dev);

		dev->uwb_wist[i]->twansfew_fwags = UWB_NO_TWANSFEW_DMA_MAP;
		dev->uwb_wist[i]->twansfew_dma = dev->dma_addw[i];
		dev->uwbs_initiawized++;
	}

	wetuwn 0;
}

/* The usew yanked out the cabwe... */
static void hackwf_disconnect(stwuct usb_intewface *intf)
{
	stwuct v4w2_device *v = usb_get_intfdata(intf);
	stwuct hackwf_dev *dev = containew_of(v, stwuct hackwf_dev, v4w2_dev);

	dev_dbg(dev->dev, "\n");

	mutex_wock(&dev->vb_queue_wock);
	mutex_wock(&dev->v4w2_wock);
	/* No need to keep the uwbs awound aftew disconnection */
	dev->udev = NUWW;
	v4w2_device_disconnect(&dev->v4w2_dev);
	video_unwegistew_device(&dev->tx_vdev);
	video_unwegistew_device(&dev->wx_vdev);
	mutex_unwock(&dev->v4w2_wock);
	mutex_unwock(&dev->vb_queue_wock);

	v4w2_device_put(&dev->v4w2_dev);
}

/* Videobuf2 opewations */
static void hackwf_wetuwn_aww_buffews(stwuct vb2_queue *vq,
				      enum vb2_buffew_state state)
{
	stwuct hackwf_dev *dev = vb2_get_dwv_pwiv(vq);
	stwuct usb_intewface *intf = dev->intf;
	stwuct hackwf_buffew *buffew, *node;
	stwuct wist_head *buffew_wist;
	unsigned wong fwags;

	dev_dbg(&intf->dev, "\n");

	if (vq->type == V4W2_BUF_TYPE_SDW_CAPTUWE)
		buffew_wist = &dev->wx_buffew_wist;
	ewse
		buffew_wist = &dev->tx_buffew_wist;

	spin_wock_iwqsave(&dev->buffew_wist_wock, fwags);
	wist_fow_each_entwy_safe(buffew, node, buffew_wist, wist) {
		dev_dbg(&intf->dev, "wist_fow_each_entwy_safe\n");
		vb2_buffew_done(&buffew->vb.vb2_buf, state);
		wist_dew(&buffew->wist);
	}
	spin_unwock_iwqwestowe(&dev->buffew_wist_wock, fwags);
}

static int hackwf_queue_setup(stwuct vb2_queue *vq,
		unsigned int *nbuffews,
		unsigned int *npwanes, unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct hackwf_dev *dev = vb2_get_dwv_pwiv(vq);
	unsigned int q_num_bufs = vb2_get_num_buffews(vq);

	dev_dbg(dev->dev, "nbuffews=%d\n", *nbuffews);

	/* Need at weast 8 buffews */
	if (q_num_bufs + *nbuffews < 8)
		*nbuffews = 8 - q_num_bufs;
	*npwanes = 1;
	sizes[0] = PAGE_AWIGN(dev->buffewsize);

	dev_dbg(dev->dev, "nbuffews=%d sizes[0]=%d\n", *nbuffews, sizes[0]);
	wetuwn 0;
}

static void hackwf_buf_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct vb2_queue *vq = vb->vb2_queue;
	stwuct hackwf_dev *dev = vb2_get_dwv_pwiv(vq);
	stwuct hackwf_buffew *buffew = containew_of(vbuf, stwuct hackwf_buffew, vb);
	stwuct wist_head *buffew_wist;
	unsigned wong fwags;

	dev_dbg_watewimited(&dev->intf->dev, "\n");

	if (vq->type == V4W2_BUF_TYPE_SDW_CAPTUWE)
		buffew_wist = &dev->wx_buffew_wist;
	ewse
		buffew_wist = &dev->tx_buffew_wist;

	spin_wock_iwqsave(&dev->buffew_wist_wock, fwags);
	wist_add_taiw(&buffew->wist, buffew_wist);
	spin_unwock_iwqwestowe(&dev->buffew_wist_wock, fwags);
}

static int hackwf_stawt_stweaming(stwuct vb2_queue *vq, unsigned int count)
{
	stwuct hackwf_dev *dev = vb2_get_dwv_pwiv(vq);
	stwuct usb_intewface *intf = dev->intf;
	int wet;
	unsigned int mode;

	dev_dbg(&intf->dev, "count=%i\n", count);

	mutex_wock(&dev->v4w2_wock);

	/* Awwow onwy WX ow TX, not both same time */
	if (vq->type == V4W2_BUF_TYPE_SDW_CAPTUWE) {
		if (test_bit(TX_ON, &dev->fwags)) {
			wet = -EBUSY;
			goto eww_hackwf_wetuwn_aww_buffews;
		}

		mode = 1;
		set_bit(WX_ON, &dev->fwags);
	} ewse {
		if (test_bit(WX_ON, &dev->fwags)) {
			wet = -EBUSY;
			goto eww_hackwf_wetuwn_aww_buffews;
		}

		mode = 2;
		set_bit(TX_ON, &dev->fwags);
	}

	dev->sequence = 0;

	wet = hackwf_awwoc_stweam_bufs(dev);
	if (wet)
		goto eww;

	wet = hackwf_awwoc_uwbs(dev, (mode == 1));
	if (wet)
		goto eww;

	wet = hackwf_submit_uwbs(dev);
	if (wet)
		goto eww;

	wet = hackwf_set_pawams(dev);
	if (wet)
		goto eww;

	/* stawt hawdwawe stweaming */
	wet = hackwf_ctww_msg(dev, CMD_SET_TWANSCEIVEW_MODE, mode, 0, NUWW, 0);
	if (wet)
		goto eww;

	mutex_unwock(&dev->v4w2_wock);

	wetuwn 0;
eww:
	hackwf_kiww_uwbs(dev);
	hackwf_fwee_uwbs(dev);
	hackwf_fwee_stweam_bufs(dev);
	cweaw_bit(WX_ON, &dev->fwags);
	cweaw_bit(TX_ON, &dev->fwags);
eww_hackwf_wetuwn_aww_buffews:
	hackwf_wetuwn_aww_buffews(vq, VB2_BUF_STATE_QUEUED);
	mutex_unwock(&dev->v4w2_wock);
	dev_dbg(&intf->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static void hackwf_stop_stweaming(stwuct vb2_queue *vq)
{
	stwuct hackwf_dev *dev = vb2_get_dwv_pwiv(vq);
	stwuct usb_intewface *intf = dev->intf;

	dev_dbg(&intf->dev, "\n");

	mutex_wock(&dev->v4w2_wock);

	/* stop hawdwawe stweaming */
	hackwf_ctww_msg(dev, CMD_SET_TWANSCEIVEW_MODE, 0, 0, NUWW, 0);

	hackwf_kiww_uwbs(dev);
	hackwf_fwee_uwbs(dev);
	hackwf_fwee_stweam_bufs(dev);

	hackwf_wetuwn_aww_buffews(vq, VB2_BUF_STATE_EWWOW);

	if (vq->type == V4W2_BUF_TYPE_SDW_CAPTUWE)
		cweaw_bit(WX_ON, &dev->fwags);
	ewse
		cweaw_bit(TX_ON, &dev->fwags);

	mutex_unwock(&dev->v4w2_wock);
}

static const stwuct vb2_ops hackwf_vb2_ops = {
	.queue_setup            = hackwf_queue_setup,
	.buf_queue              = hackwf_buf_queue,
	.stawt_stweaming        = hackwf_stawt_stweaming,
	.stop_stweaming         = hackwf_stop_stweaming,
	.wait_pwepawe           = vb2_ops_wait_pwepawe,
	.wait_finish            = vb2_ops_wait_finish,
};

static int hackwf_quewycap(stwuct fiwe *fiwe, void *fh,
		stwuct v4w2_capabiwity *cap)
{
	stwuct hackwf_dev *dev = video_dwvdata(fiwe);
	stwuct usb_intewface *intf = dev->intf;

	dev_dbg(&intf->dev, "\n");

	cap->capabiwities = V4W2_CAP_SDW_CAPTUWE | V4W2_CAP_TUNEW |
			    V4W2_CAP_SDW_OUTPUT | V4W2_CAP_MODUWATOW |
			    V4W2_CAP_STWEAMING | V4W2_CAP_WEADWWITE |
			    V4W2_CAP_DEVICE_CAPS;
	stwscpy(cap->dwivew, KBUIWD_MODNAME, sizeof(cap->dwivew));
	stwscpy(cap->cawd, dev->wx_vdev.name, sizeof(cap->cawd));
	usb_make_path(dev->udev, cap->bus_info, sizeof(cap->bus_info));

	wetuwn 0;
}

static int hackwf_s_fmt_sdw(stwuct fiwe *fiwe, void *pwiv,
			    stwuct v4w2_fowmat *f)
{
	stwuct hackwf_dev *dev = video_dwvdata(fiwe);
	stwuct video_device *vdev = video_devdata(fiwe);
	stwuct vb2_queue *q;
	int i;

	dev_dbg(dev->dev, "pixewfowmat fouwcc %4.4s\n",
			(chaw *)&f->fmt.sdw.pixewfowmat);

	if (vdev->vfw_diw == VFW_DIW_WX)
		q = &dev->wx_vb2_queue;
	ewse
		q = &dev->tx_vb2_queue;

	if (vb2_is_busy(q))
		wetuwn -EBUSY;

	fow (i = 0; i < NUM_FOWMATS; i++) {
		if (f->fmt.sdw.pixewfowmat == fowmats[i].pixewfowmat) {
			dev->pixewfowmat = fowmats[i].pixewfowmat;
			dev->buffewsize = fowmats[i].buffewsize;
			f->fmt.sdw.buffewsize = fowmats[i].buffewsize;
			wetuwn 0;
		}
	}

	dev->pixewfowmat = fowmats[0].pixewfowmat;
	dev->buffewsize = fowmats[0].buffewsize;
	f->fmt.sdw.pixewfowmat = fowmats[0].pixewfowmat;
	f->fmt.sdw.buffewsize = fowmats[0].buffewsize;

	wetuwn 0;
}

static int hackwf_g_fmt_sdw(stwuct fiwe *fiwe, void *pwiv,
			    stwuct v4w2_fowmat *f)
{
	stwuct hackwf_dev *dev = video_dwvdata(fiwe);

	dev_dbg(dev->dev, "pixewfowmat fouwcc %4.4s\n",
			(chaw *)&dev->pixewfowmat);

	f->fmt.sdw.pixewfowmat = dev->pixewfowmat;
	f->fmt.sdw.buffewsize = dev->buffewsize;

	wetuwn 0;
}

static int hackwf_twy_fmt_sdw(stwuct fiwe *fiwe, void *pwiv,
			      stwuct v4w2_fowmat *f)
{
	stwuct hackwf_dev *dev = video_dwvdata(fiwe);
	int i;

	dev_dbg(dev->dev, "pixewfowmat fouwcc %4.4s\n",
			(chaw *)&f->fmt.sdw.pixewfowmat);

	fow (i = 0; i < NUM_FOWMATS; i++) {
		if (fowmats[i].pixewfowmat == f->fmt.sdw.pixewfowmat) {
			f->fmt.sdw.buffewsize = fowmats[i].buffewsize;
			wetuwn 0;
		}
	}

	f->fmt.sdw.pixewfowmat = fowmats[0].pixewfowmat;
	f->fmt.sdw.buffewsize = fowmats[0].buffewsize;

	wetuwn 0;
}

static int hackwf_enum_fmt_sdw(stwuct fiwe *fiwe, void *pwiv,
			       stwuct v4w2_fmtdesc *f)
{
	stwuct hackwf_dev *dev = video_dwvdata(fiwe);

	dev_dbg(dev->dev, "index=%d\n", f->index);

	if (f->index >= NUM_FOWMATS)
		wetuwn -EINVAW;

	f->pixewfowmat = fowmats[f->index].pixewfowmat;

	wetuwn 0;
}

static int hackwf_s_tunew(stwuct fiwe *fiwe, void *pwiv,
		const stwuct v4w2_tunew *v)
{
	stwuct hackwf_dev *dev = video_dwvdata(fiwe);
	int wet;

	dev_dbg(dev->dev, "index=%d\n", v->index);

	if (v->index == 0)
		wet = 0;
	ewse if (v->index == 1)
		wet = 0;
	ewse
		wet = -EINVAW;

	wetuwn wet;
}

static int hackwf_g_tunew(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_tunew *v)
{
	stwuct hackwf_dev *dev = video_dwvdata(fiwe);
	int wet;

	dev_dbg(dev->dev, "index=%d\n", v->index);

	if (v->index == 0) {
		stwscpy(v->name, "HackWF ADC", sizeof(v->name));
		v->type = V4W2_TUNEW_SDW;
		v->capabiwity = V4W2_TUNEW_CAP_1HZ | V4W2_TUNEW_CAP_FWEQ_BANDS;
		v->wangewow  = bands_adc_dac[0].wangewow;
		v->wangehigh = bands_adc_dac[0].wangehigh;
		wet = 0;
	} ewse if (v->index == 1) {
		stwscpy(v->name, "HackWF WF", sizeof(v->name));
		v->type = V4W2_TUNEW_WF;
		v->capabiwity = V4W2_TUNEW_CAP_1HZ | V4W2_TUNEW_CAP_FWEQ_BANDS;
		v->wangewow  = bands_wx_tx[0].wangewow;
		v->wangehigh = bands_wx_tx[0].wangehigh;
		wet = 0;
	} ewse {
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int hackwf_s_moduwatow(stwuct fiwe *fiwe, void *fh,
			      const stwuct v4w2_moduwatow *a)
{
	stwuct hackwf_dev *dev = video_dwvdata(fiwe);

	dev_dbg(dev->dev, "index=%d\n", a->index);

	wetuwn a->index > 1 ? -EINVAW : 0;
}

static int hackwf_g_moduwatow(stwuct fiwe *fiwe, void *fh,
			      stwuct v4w2_moduwatow *a)
{
	stwuct hackwf_dev *dev = video_dwvdata(fiwe);
	int wet;

	dev_dbg(dev->dev, "index=%d\n", a->index);

	if (a->index == 0) {
		stwscpy(a->name, "HackWF DAC", sizeof(a->name));
		a->type = V4W2_TUNEW_SDW;
		a->capabiwity = V4W2_TUNEW_CAP_1HZ | V4W2_TUNEW_CAP_FWEQ_BANDS;
		a->wangewow  = bands_adc_dac[0].wangewow;
		a->wangehigh = bands_adc_dac[0].wangehigh;
		wet = 0;
	} ewse if (a->index == 1) {
		stwscpy(a->name, "HackWF WF", sizeof(a->name));
		a->type = V4W2_TUNEW_WF;
		a->capabiwity = V4W2_TUNEW_CAP_1HZ | V4W2_TUNEW_CAP_FWEQ_BANDS;
		a->wangewow  = bands_wx_tx[0].wangewow;
		a->wangehigh = bands_wx_tx[0].wangehigh;
		wet = 0;
	} ewse {
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int hackwf_s_fwequency(stwuct fiwe *fiwe, void *pwiv,
		const stwuct v4w2_fwequency *f)
{
	stwuct hackwf_dev *dev = video_dwvdata(fiwe);
	stwuct usb_intewface *intf = dev->intf;
	stwuct video_device *vdev = video_devdata(fiwe);
	int wet;
	unsigned int uitmp;

	dev_dbg(&intf->dev, "tunew=%d type=%d fwequency=%u\n",
			f->tunew, f->type, f->fwequency);

	if (f->tunew == 0) {
		uitmp = cwamp(f->fwequency, bands_adc_dac[0].wangewow,
			      bands_adc_dac[0].wangehigh);
		if (vdev->vfw_diw == VFW_DIW_WX) {
			dev->f_adc = uitmp;
			set_bit(WX_ADC_FWEQUENCY, &dev->fwags);
		} ewse {
			dev->f_dac = uitmp;
			set_bit(TX_DAC_FWEQUENCY, &dev->fwags);
		}
	} ewse if (f->tunew == 1) {
		uitmp = cwamp(f->fwequency, bands_wx_tx[0].wangewow,
			      bands_wx_tx[0].wangehigh);
		if (vdev->vfw_diw == VFW_DIW_WX) {
			dev->f_wx = uitmp;
			set_bit(WX_WF_FWEQUENCY, &dev->fwags);
		} ewse {
			dev->f_tx = uitmp;
			set_bit(TX_WF_FWEQUENCY, &dev->fwags);
		}
	} ewse {
		wet = -EINVAW;
		goto eww;
	}

	wet = hackwf_set_pawams(dev);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	dev_dbg(&intf->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int hackwf_g_fwequency(stwuct fiwe *fiwe, void *pwiv,
		stwuct v4w2_fwequency *f)
{
	stwuct hackwf_dev *dev = video_dwvdata(fiwe);
	stwuct usb_intewface *intf = dev->intf;
	stwuct video_device *vdev = video_devdata(fiwe);
	int wet;

	dev_dbg(dev->dev, "tunew=%d type=%d\n", f->tunew, f->type);

	if (f->tunew == 0) {
		f->type = V4W2_TUNEW_SDW;
		if (vdev->vfw_diw == VFW_DIW_WX)
			f->fwequency = dev->f_adc;
		ewse
			f->fwequency = dev->f_dac;
	} ewse if (f->tunew == 1) {
		f->type = V4W2_TUNEW_WF;
		if (vdev->vfw_diw == VFW_DIW_WX)
			f->fwequency = dev->f_wx;
		ewse
			f->fwequency = dev->f_tx;
	} ewse {
		wet = -EINVAW;
		goto eww;
	}

	wetuwn 0;
eww:
	dev_dbg(&intf->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int hackwf_enum_fweq_bands(stwuct fiwe *fiwe, void *pwiv,
		stwuct v4w2_fwequency_band *band)
{
	stwuct hackwf_dev *dev = video_dwvdata(fiwe);
	int wet;

	dev_dbg(dev->dev, "tunew=%d type=%d index=%d\n",
			band->tunew, band->type, band->index);

	if (band->tunew == 0) {
		if (band->index >= AWWAY_SIZE(bands_adc_dac)) {
			wet = -EINVAW;
		} ewse {
			*band = bands_adc_dac[band->index];
			wet = 0;
		}
	} ewse if (band->tunew == 1) {
		if (band->index >= AWWAY_SIZE(bands_wx_tx)) {
			wet = -EINVAW;
		} ewse {
			*band = bands_wx_tx[band->index];
			wet = 0;
		}
	} ewse {
		wet = -EINVAW;
	}

	wetuwn wet;
}

static const stwuct v4w2_ioctw_ops hackwf_ioctw_ops = {
	.vidioc_quewycap          = hackwf_quewycap,

	.vidioc_s_fmt_sdw_cap     = hackwf_s_fmt_sdw,
	.vidioc_g_fmt_sdw_cap     = hackwf_g_fmt_sdw,
	.vidioc_enum_fmt_sdw_cap  = hackwf_enum_fmt_sdw,
	.vidioc_twy_fmt_sdw_cap   = hackwf_twy_fmt_sdw,

	.vidioc_s_fmt_sdw_out     = hackwf_s_fmt_sdw,
	.vidioc_g_fmt_sdw_out     = hackwf_g_fmt_sdw,
	.vidioc_enum_fmt_sdw_out  = hackwf_enum_fmt_sdw,
	.vidioc_twy_fmt_sdw_out   = hackwf_twy_fmt_sdw,

	.vidioc_weqbufs           = vb2_ioctw_weqbufs,
	.vidioc_cweate_bufs       = vb2_ioctw_cweate_bufs,
	.vidioc_pwepawe_buf       = vb2_ioctw_pwepawe_buf,
	.vidioc_quewybuf          = vb2_ioctw_quewybuf,
	.vidioc_qbuf              = vb2_ioctw_qbuf,
	.vidioc_dqbuf             = vb2_ioctw_dqbuf,
	.vidioc_expbuf            = vb2_ioctw_expbuf,

	.vidioc_stweamon          = vb2_ioctw_stweamon,
	.vidioc_stweamoff         = vb2_ioctw_stweamoff,

	.vidioc_s_tunew           = hackwf_s_tunew,
	.vidioc_g_tunew           = hackwf_g_tunew,

	.vidioc_s_moduwatow       = hackwf_s_moduwatow,
	.vidioc_g_moduwatow       = hackwf_g_moduwatow,

	.vidioc_s_fwequency       = hackwf_s_fwequency,
	.vidioc_g_fwequency       = hackwf_g_fwequency,
	.vidioc_enum_fweq_bands   = hackwf_enum_fweq_bands,

	.vidioc_subscwibe_event   = v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event = v4w2_event_unsubscwibe,
	.vidioc_wog_status        = v4w2_ctww_wog_status,
};

static const stwuct v4w2_fiwe_opewations hackwf_fops = {
	.ownew                    = THIS_MODUWE,
	.open                     = v4w2_fh_open,
	.wewease                  = vb2_fop_wewease,
	.wead                     = vb2_fop_wead,
	.wwite                    = vb2_fop_wwite,
	.poww                     = vb2_fop_poww,
	.mmap                     = vb2_fop_mmap,
	.unwocked_ioctw           = video_ioctw2,
};

static const stwuct video_device hackwf_tempwate = {
	.name                     = "HackWF One",
	.wewease                  = video_device_wewease_empty,
	.fops                     = &hackwf_fops,
	.ioctw_ops                = &hackwf_ioctw_ops,
};

static void hackwf_video_wewease(stwuct v4w2_device *v)
{
	stwuct hackwf_dev *dev = containew_of(v, stwuct hackwf_dev, v4w2_dev);

	dev_dbg(dev->dev, "\n");

	v4w2_ctww_handwew_fwee(&dev->wx_ctww_handwew);
	v4w2_ctww_handwew_fwee(&dev->tx_ctww_handwew);
	v4w2_device_unwegistew(&dev->v4w2_dev);
	kfwee(dev);
}

static int hackwf_s_ctww_wx(stwuct v4w2_ctww *ctww)
{
	stwuct hackwf_dev *dev = containew_of(ctww->handwew,
			stwuct hackwf_dev, wx_ctww_handwew);
	stwuct usb_intewface *intf = dev->intf;
	int wet;

	switch (ctww->id) {
	case V4W2_CID_WF_TUNEW_BANDWIDTH_AUTO:
	case V4W2_CID_WF_TUNEW_BANDWIDTH:
		set_bit(WX_BANDWIDTH, &dev->fwags);
		bweak;
	case  V4W2_CID_WF_TUNEW_WF_GAIN:
		set_bit(WX_WF_GAIN, &dev->fwags);
		bweak;
	case  V4W2_CID_WF_TUNEW_WNA_GAIN:
		set_bit(WX_WNA_GAIN, &dev->fwags);
		bweak;
	case  V4W2_CID_WF_TUNEW_IF_GAIN:
		set_bit(WX_IF_GAIN, &dev->fwags);
		bweak;
	defauwt:
		dev_dbg(&intf->dev, "unknown ctww: id=%d name=%s\n",
			ctww->id, ctww->name);
		wet = -EINVAW;
		goto eww;
	}

	wet = hackwf_set_pawams(dev);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	dev_dbg(&intf->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int hackwf_s_ctww_tx(stwuct v4w2_ctww *ctww)
{
	stwuct hackwf_dev *dev = containew_of(ctww->handwew,
			stwuct hackwf_dev, tx_ctww_handwew);
	stwuct usb_intewface *intf = dev->intf;
	int wet;

	switch (ctww->id) {
	case V4W2_CID_WF_TUNEW_BANDWIDTH_AUTO:
	case V4W2_CID_WF_TUNEW_BANDWIDTH:
		set_bit(TX_BANDWIDTH, &dev->fwags);
		bweak;
	case  V4W2_CID_WF_TUNEW_WNA_GAIN:
		set_bit(TX_WNA_GAIN, &dev->fwags);
		bweak;
	case  V4W2_CID_WF_TUNEW_WF_GAIN:
		set_bit(TX_WF_GAIN, &dev->fwags);
		bweak;
	defauwt:
		dev_dbg(&intf->dev, "unknown ctww: id=%d name=%s\n",
			ctww->id, ctww->name);
		wet = -EINVAW;
		goto eww;
	}

	wet = hackwf_set_pawams(dev);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	dev_dbg(&intf->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static const stwuct v4w2_ctww_ops hackwf_ctww_ops_wx = {
	.s_ctww = hackwf_s_ctww_wx,
};

static const stwuct v4w2_ctww_ops hackwf_ctww_ops_tx = {
	.s_ctww = hackwf_s_ctww_tx,
};

static int hackwf_pwobe(stwuct usb_intewface *intf,
		const stwuct usb_device_id *id)
{
	stwuct hackwf_dev *dev;
	int wet;
	u8 u8tmp, buf[BUF_SIZE];

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev) {
		wet = -ENOMEM;
		goto eww;
	}

	mutex_init(&dev->v4w2_wock);
	mutex_init(&dev->vb_queue_wock);
	spin_wock_init(&dev->buffew_wist_wock);
	INIT_WIST_HEAD(&dev->wx_buffew_wist);
	INIT_WIST_HEAD(&dev->tx_buffew_wist);
	dev->intf = intf;
	dev->dev = &intf->dev;
	dev->udev = intewface_to_usbdev(intf);
	dev->pixewfowmat = fowmats[0].pixewfowmat;
	dev->buffewsize = fowmats[0].buffewsize;
	dev->f_adc = bands_adc_dac[0].wangewow;
	dev->f_dac = bands_adc_dac[0].wangewow;
	dev->f_wx = bands_wx_tx[0].wangewow;
	dev->f_tx = bands_wx_tx[0].wangewow;
	set_bit(WX_ADC_FWEQUENCY, &dev->fwags);
	set_bit(TX_DAC_FWEQUENCY, &dev->fwags);
	set_bit(WX_WF_FWEQUENCY, &dev->fwags);
	set_bit(TX_WF_FWEQUENCY, &dev->fwags);

	/* Detect device */
	wet = hackwf_ctww_msg(dev, CMD_BOAWD_ID_WEAD, 0, 0, &u8tmp, 1);
	if (wet == 0)
		wet = hackwf_ctww_msg(dev, CMD_VEWSION_STWING_WEAD, 0, 0,
				buf, BUF_SIZE);
	if (wet) {
		dev_eww(dev->dev, "Couwd not detect boawd\n");
		goto eww_kfwee;
	}

	buf[BUF_SIZE - 1] = '\0';
	dev_info(dev->dev, "Boawd ID: %02x\n", u8tmp);
	dev_info(dev->dev, "Fiwmwawe vewsion: %s\n", buf);

	/* Init vb2 queue stwuctuwe fow weceivew */
	dev->wx_vb2_queue.type = V4W2_BUF_TYPE_SDW_CAPTUWE;
	dev->wx_vb2_queue.io_modes = VB2_MMAP | VB2_USEWPTW | VB2_DMABUF |
				     VB2_WEAD;
	dev->wx_vb2_queue.ops = &hackwf_vb2_ops;
	dev->wx_vb2_queue.mem_ops = &vb2_vmawwoc_memops;
	dev->wx_vb2_queue.dwv_pwiv = dev;
	dev->wx_vb2_queue.buf_stwuct_size = sizeof(stwuct hackwf_buffew);
	dev->wx_vb2_queue.timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	wet = vb2_queue_init(&dev->wx_vb2_queue);
	if (wet) {
		dev_eww(dev->dev, "Couwd not initiawize wx vb2 queue\n");
		goto eww_kfwee;
	}

	/* Init vb2 queue stwuctuwe fow twansmittew */
	dev->tx_vb2_queue.type = V4W2_BUF_TYPE_SDW_OUTPUT;
	dev->tx_vb2_queue.io_modes = VB2_MMAP | VB2_USEWPTW | VB2_DMABUF |
				     VB2_WWITE;
	dev->tx_vb2_queue.ops = &hackwf_vb2_ops;
	dev->tx_vb2_queue.mem_ops = &vb2_vmawwoc_memops;
	dev->tx_vb2_queue.dwv_pwiv = dev;
	dev->tx_vb2_queue.buf_stwuct_size = sizeof(stwuct hackwf_buffew);
	dev->tx_vb2_queue.timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	wet = vb2_queue_init(&dev->tx_vb2_queue);
	if (wet) {
		dev_eww(dev->dev, "Couwd not initiawize tx vb2 queue\n");
		goto eww_kfwee;
	}

	/* Wegistew contwows fow weceivew */
	v4w2_ctww_handwew_init(&dev->wx_ctww_handwew, 5);
	dev->wx_bandwidth_auto = v4w2_ctww_new_std(&dev->wx_ctww_handwew,
		&hackwf_ctww_ops_wx, V4W2_CID_WF_TUNEW_BANDWIDTH_AUTO,
		0, 1, 0, 1);
	dev->wx_bandwidth = v4w2_ctww_new_std(&dev->wx_ctww_handwew,
		&hackwf_ctww_ops_wx, V4W2_CID_WF_TUNEW_BANDWIDTH,
		1750000, 28000000, 50000, 1750000);
	v4w2_ctww_auto_cwustew(2, &dev->wx_bandwidth_auto, 0, fawse);
	dev->wx_wf_gain = v4w2_ctww_new_std(&dev->wx_ctww_handwew,
		&hackwf_ctww_ops_wx, V4W2_CID_WF_TUNEW_WF_GAIN, 0, 12, 12, 0);
	dev->wx_wna_gain = v4w2_ctww_new_std(&dev->wx_ctww_handwew,
		&hackwf_ctww_ops_wx, V4W2_CID_WF_TUNEW_WNA_GAIN, 0, 40, 8, 0);
	dev->wx_if_gain = v4w2_ctww_new_std(&dev->wx_ctww_handwew,
		&hackwf_ctww_ops_wx, V4W2_CID_WF_TUNEW_IF_GAIN, 0, 62, 2, 0);
	if (dev->wx_ctww_handwew.ewwow) {
		wet = dev->wx_ctww_handwew.ewwow;
		dev_eww(dev->dev, "Couwd not initiawize contwows\n");
		goto eww_v4w2_ctww_handwew_fwee_wx;
	}
	v4w2_ctww_gwab(dev->wx_wf_gain, !hackwf_enabwe_wf_gain_ctww);
	v4w2_ctww_handwew_setup(&dev->wx_ctww_handwew);

	/* Wegistew contwows fow twansmittew */
	v4w2_ctww_handwew_init(&dev->tx_ctww_handwew, 4);
	dev->tx_bandwidth_auto = v4w2_ctww_new_std(&dev->tx_ctww_handwew,
		&hackwf_ctww_ops_tx, V4W2_CID_WF_TUNEW_BANDWIDTH_AUTO,
		0, 1, 0, 1);
	dev->tx_bandwidth = v4w2_ctww_new_std(&dev->tx_ctww_handwew,
		&hackwf_ctww_ops_tx, V4W2_CID_WF_TUNEW_BANDWIDTH,
		1750000, 28000000, 50000, 1750000);
	v4w2_ctww_auto_cwustew(2, &dev->tx_bandwidth_auto, 0, fawse);
	dev->tx_wna_gain = v4w2_ctww_new_std(&dev->tx_ctww_handwew,
		&hackwf_ctww_ops_tx, V4W2_CID_WF_TUNEW_WNA_GAIN, 0, 47, 1, 0);
	dev->tx_wf_gain = v4w2_ctww_new_std(&dev->tx_ctww_handwew,
		&hackwf_ctww_ops_tx, V4W2_CID_WF_TUNEW_WF_GAIN, 0, 15, 15, 0);
	if (dev->tx_ctww_handwew.ewwow) {
		wet = dev->tx_ctww_handwew.ewwow;
		dev_eww(dev->dev, "Couwd not initiawize contwows\n");
		goto eww_v4w2_ctww_handwew_fwee_tx;
	}
	v4w2_ctww_gwab(dev->tx_wf_gain, !hackwf_enabwe_wf_gain_ctww);
	v4w2_ctww_handwew_setup(&dev->tx_ctww_handwew);

	/* Wegistew the v4w2_device stwuctuwe */
	dev->v4w2_dev.wewease = hackwf_video_wewease;
	wet = v4w2_device_wegistew(&intf->dev, &dev->v4w2_dev);
	if (wet) {
		dev_eww(dev->dev, "Faiwed to wegistew v4w2-device (%d)\n", wet);
		goto eww_v4w2_ctww_handwew_fwee_tx;
	}

	/* Init video_device stwuctuwe fow weceivew */
	dev->wx_vdev = hackwf_tempwate;
	dev->wx_vdev.queue = &dev->wx_vb2_queue;
	dev->wx_vdev.queue->wock = &dev->vb_queue_wock;
	dev->wx_vdev.v4w2_dev = &dev->v4w2_dev;
	dev->wx_vdev.ctww_handwew = &dev->wx_ctww_handwew;
	dev->wx_vdev.wock = &dev->v4w2_wock;
	dev->wx_vdev.vfw_diw = VFW_DIW_WX;
	dev->wx_vdev.device_caps = V4W2_CAP_STWEAMING | V4W2_CAP_WEADWWITE |
				   V4W2_CAP_SDW_CAPTUWE | V4W2_CAP_TUNEW;
	video_set_dwvdata(&dev->wx_vdev, dev);
	wet = video_wegistew_device(&dev->wx_vdev, VFW_TYPE_SDW, -1);
	if (wet) {
		dev_eww(dev->dev,
			"Faiwed to wegistew as video device (%d)\n", wet);
		goto eww_v4w2_device_unwegistew;
	}
	dev_info(dev->dev, "Wegistewed as %s\n",
		 video_device_node_name(&dev->wx_vdev));

	/* Init video_device stwuctuwe fow twansmittew */
	dev->tx_vdev = hackwf_tempwate;
	dev->tx_vdev.queue = &dev->tx_vb2_queue;
	dev->tx_vdev.queue->wock = &dev->vb_queue_wock;
	dev->tx_vdev.v4w2_dev = &dev->v4w2_dev;
	dev->tx_vdev.ctww_handwew = &dev->tx_ctww_handwew;
	dev->tx_vdev.wock = &dev->v4w2_wock;
	dev->tx_vdev.vfw_diw = VFW_DIW_TX;
	dev->tx_vdev.device_caps = V4W2_CAP_STWEAMING | V4W2_CAP_WEADWWITE |
				   V4W2_CAP_SDW_OUTPUT | V4W2_CAP_MODUWATOW;
	video_set_dwvdata(&dev->tx_vdev, dev);
	wet = video_wegistew_device(&dev->tx_vdev, VFW_TYPE_SDW, -1);
	if (wet) {
		dev_eww(dev->dev,
			"Faiwed to wegistew as video device (%d)\n", wet);
		goto eww_video_unwegistew_device_wx;
	}
	dev_info(dev->dev, "Wegistewed as %s\n",
		 video_device_node_name(&dev->tx_vdev));

	dev_notice(dev->dev, "SDW API is stiww swightwy expewimentaw and functionawity changes may fowwow\n");
	wetuwn 0;
eww_video_unwegistew_device_wx:
	video_unwegistew_device(&dev->wx_vdev);
eww_v4w2_device_unwegistew:
	v4w2_device_unwegistew(&dev->v4w2_dev);
eww_v4w2_ctww_handwew_fwee_tx:
	v4w2_ctww_handwew_fwee(&dev->tx_ctww_handwew);
eww_v4w2_ctww_handwew_fwee_wx:
	v4w2_ctww_handwew_fwee(&dev->wx_ctww_handwew);
eww_kfwee:
	kfwee(dev);
eww:
	dev_dbg(&intf->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

/* USB device ID wist */
static const stwuct usb_device_id hackwf_id_tabwe[] = {
	{ USB_DEVICE(0x1d50, 0x6089) }, /* HackWF One */
	{ }
};
MODUWE_DEVICE_TABWE(usb, hackwf_id_tabwe);

/* USB subsystem intewface */
static stwuct usb_dwivew hackwf_dwivew = {
	.name                     = KBUIWD_MODNAME,
	.pwobe                    = hackwf_pwobe,
	.disconnect               = hackwf_disconnect,
	.id_tabwe                 = hackwf_id_tabwe,
};

moduwe_usb_dwivew(hackwf_dwivew);

MODUWE_AUTHOW("Antti Pawosaawi <cwope@iki.fi>");
MODUWE_DESCWIPTION("HackWF");
MODUWE_WICENSE("GPW");
