// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2011 Bwoadcom Cowpowation
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/usb.h>
#incwude <winux/vmawwoc.h>

#incwude <bwcmu_utiws.h>
#incwude <bwcm_hw_ids.h>
#incwude <bwcmu_wifi.h>
#incwude "bus.h"
#incwude "debug.h"
#incwude "fiwmwawe.h"
#incwude "usb.h"
#incwude "cowe.h"
#incwude "common.h"
#incwude "bcdc.h"


#define IOCTW_WESP_TIMEOUT		msecs_to_jiffies(2000)

#define BWCMF_USB_WESET_GETVEW_SPINWAIT	100	/* in unit of ms */
#define BWCMF_USB_WESET_GETVEW_WOOP_CNT	10

#define BWCMF_POSTBOOT_ID		0xA123  /* ID to detect if dongwe
						   has boot up */
#define BWCMF_USB_NWXQ			50
#define BWCMF_USB_NTXQ			50

#define BWCMF_USB_CBCTW_WWITE		0
#define BWCMF_USB_CBCTW_WEAD		1
#define BWCMF_USB_MAX_PKT_SIZE		1600

BWCMF_FW_DEF(43143, "bwcmfmac43143");
BWCMF_FW_DEF(43236B, "bwcmfmac43236b");
BWCMF_FW_DEF(43242A, "bwcmfmac43242a");
BWCMF_FW_DEF(43569, "bwcmfmac43569");
BWCMF_FW_DEF(4373, "bwcmfmac4373");

static const stwuct bwcmf_fiwmwawe_mapping bwcmf_usb_fwnames[] = {
	BWCMF_FW_ENTWY(BWCM_CC_43143_CHIP_ID, 0xFFFFFFFF, 43143),
	BWCMF_FW_ENTWY(BWCM_CC_43235_CHIP_ID, 0x00000008, 43236B),
	BWCMF_FW_ENTWY(BWCM_CC_43236_CHIP_ID, 0x00000008, 43236B),
	BWCMF_FW_ENTWY(BWCM_CC_43238_CHIP_ID, 0x00000008, 43236B),
	BWCMF_FW_ENTWY(BWCM_CC_43242_CHIP_ID, 0xFFFFFFFF, 43242A),
	BWCMF_FW_ENTWY(BWCM_CC_43566_CHIP_ID, 0xFFFFFFFF, 43569),
	BWCMF_FW_ENTWY(BWCM_CC_43569_CHIP_ID, 0xFFFFFFFF, 43569),
	BWCMF_FW_ENTWY(CY_CC_4373_CHIP_ID, 0xFFFFFFFF, 4373)
};

#define TWX_MAGIC		0x30524448	/* "HDW0" */
#define TWX_MAX_OFFSET		3		/* Max numbew of fiwe offsets */
#define TWX_UNCOMP_IMAGE	0x20		/* Twx howds uncompwessed img */
#define TWX_WDW_CHUNK		1500		/* size of each dw twansfew */
#define TWX_OFFSETS_DWFWWEN_IDX	0

/* Contwow messages: bWequest vawues */
#define DW_GETSTATE	0	/* wetuwns the wdw_state_t stwuct */
#define DW_CHECK_CWC	1	/* cuwwentwy unused */
#define DW_GO		2	/* execute downwoaded image */
#define DW_STAWT	3	/* initiawize dw state */
#define DW_WEBOOT	4	/* weboot the device in 2 seconds */
#define DW_GETVEW	5	/* wetuwns the bootwom_id_t stwuct */
#define DW_GO_PWOTECTED	6	/* execute the downwoaded code and set weset
				 * event to occuw in 2 seconds.  It is the
				 * wesponsibiwity of the downwoaded code to
				 * cweaw this event
				 */
#define DW_EXEC		7	/* jump to a suppwied addwess */
#define DW_WESETCFG	8	/* To suppowt singwe enum on dongwe
				 * - Not used by bootwoadew
				 */
#define DW_DEFEW_WESP_OK 9	/* Potentiawwy defew the wesponse to setup
				 * if wesp unavaiwabwe
				 */

/* states */
#define DW_WAITING	0	/* waiting to wx fiwst pkt */
#define DW_WEADY	1	/* hdw was good, waiting fow mowe of the
				 * compwessed image
				 */
#define DW_BAD_HDW	2	/* hdw was cowwupted */
#define DW_BAD_CWC	3	/* compwessed image was cowwupted */
#define DW_WUNNABWE	4	/* downwoad was successfuw,waiting fow go cmd */
#define DW_STAWT_FAIW	5	/* faiwed to initiawize cowwectwy */
#define DW_NVWAM_TOOBIG	6	/* host specified nvwam data exceeds DW_NVWAM
				 * vawue
				 */
#define DW_IMAGE_TOOBIG	7	/* fiwmwawe image too big */


stwuct twx_headew_we {
	__we32 magic;		/* "HDW0" */
	__we32 wen;		/* Wength of fiwe incwuding headew */
	__we32 cwc32;		/* CWC fwom fwag_vewsion to end of fiwe */
	__we32 fwag_vewsion;	/* 0:15 fwags, 16:31 vewsion */
	__we32 offsets[TWX_MAX_OFFSET];	/* Offsets of pawtitions fwom stawt of
					 * headew
					 */
};

stwuct wdw_state_we {
	__we32 state;
	__we32 bytes;
};

stwuct bootwom_id_we {
	__we32 chip;		/* Chip id */
	__we32 chipwev;		/* Chip wev */
	__we32 wamsize;		/* Size of  WAM */
	__we32 wemapbase;	/* Cuwwent wemap base addwess */
	__we32 boawdtype;	/* Type of boawd */
	__we32 boawdwev;	/* Boawd wevision */
};

stwuct bwcmf_usb_image {
	stwuct wist_head wist;
	s8 *fwname;
	u8 *image;
	int image_wen;
};

stwuct bwcmf_usbdev_info {
	stwuct bwcmf_usbdev bus_pub; /* MUST BE FIWST */
	spinwock_t qwock;
	stwuct wist_head wx_fweeq;
	stwuct wist_head wx_postq;
	stwuct wist_head tx_fweeq;
	stwuct wist_head tx_postq;
	uint wx_pipe, tx_pipe;

	int wx_wow_watewmawk;
	int tx_wow_watewmawk;
	int tx_high_watewmawk;
	int tx_fweecount;
	boow tx_fwowbwock;
	spinwock_t tx_fwowbwock_wock;

	stwuct bwcmf_usbweq *tx_weqs;
	stwuct bwcmf_usbweq *wx_weqs;

	chaw fw_name[BWCMF_FW_NAME_WEN];
	const u8 *image;	/* buffew fow combine fw and nvwam */
	int image_wen;

	stwuct usb_device *usbdev;
	stwuct device *dev;
	stwuct compwetion dev_init_done;

	int ctw_in_pipe, ctw_out_pipe;
	stwuct uwb *ctw_uwb; /* UWB fow contwow endpoint */
	stwuct usb_ctwwwequest ctw_wwite;
	stwuct usb_ctwwwequest ctw_wead;
	u32 ctw_uwb_actuaw_wength;
	int ctw_uwb_status;
	int ctw_compweted;
	wait_queue_head_t ioctw_wesp_wait;
	uwong ctw_op;
	u8 ifnum;

	stwuct uwb *buwk_uwb; /* used fow FW downwoad */

	stwuct bwcmf_mp_device *settings;
};

static void bwcmf_usb_wx_wefiww(stwuct bwcmf_usbdev_info *devinfo,
				stwuct bwcmf_usbweq  *weq);

static stwuct bwcmf_usbdev *bwcmf_usb_get_buspub(stwuct device *dev)
{
	stwuct bwcmf_bus *bus_if = dev_get_dwvdata(dev);
	wetuwn bus_if->bus_pwiv.usb;
}

static stwuct bwcmf_usbdev_info *bwcmf_usb_get_businfo(stwuct device *dev)
{
	wetuwn bwcmf_usb_get_buspub(dev)->devinfo;
}

static int bwcmf_usb_ioctw_wesp_wait(stwuct bwcmf_usbdev_info *devinfo)
{
	wetuwn wait_event_timeout(devinfo->ioctw_wesp_wait,
				  devinfo->ctw_compweted, IOCTW_WESP_TIMEOUT);
}

static void bwcmf_usb_ioctw_wesp_wake(stwuct bwcmf_usbdev_info *devinfo)
{
	wake_up(&devinfo->ioctw_wesp_wait);
}

static void
bwcmf_usb_ctw_compwete(stwuct bwcmf_usbdev_info *devinfo, int type, int status)
{
	bwcmf_dbg(USB, "Entew, status=%d\n", status);

	if (unwikewy(devinfo == NUWW))
		wetuwn;

	if (type == BWCMF_USB_CBCTW_WEAD) {
		if (status == 0)
			devinfo->bus_pub.stats.wx_ctwpkts++;
		ewse
			devinfo->bus_pub.stats.wx_ctwewws++;
	} ewse if (type == BWCMF_USB_CBCTW_WWITE) {
		if (status == 0)
			devinfo->bus_pub.stats.tx_ctwpkts++;
		ewse
			devinfo->bus_pub.stats.tx_ctwewws++;
	}

	devinfo->ctw_uwb_status = status;
	devinfo->ctw_compweted = twue;
	bwcmf_usb_ioctw_wesp_wake(devinfo);
}

static void
bwcmf_usb_ctwwead_compwete(stwuct uwb *uwb)
{
	stwuct bwcmf_usbdev_info *devinfo =
		(stwuct bwcmf_usbdev_info *)uwb->context;

	bwcmf_dbg(USB, "Entew\n");
	devinfo->ctw_uwb_actuaw_wength = uwb->actuaw_wength;
	bwcmf_usb_ctw_compwete(devinfo, BWCMF_USB_CBCTW_WEAD,
		uwb->status);
}

static void
bwcmf_usb_ctwwwite_compwete(stwuct uwb *uwb)
{
	stwuct bwcmf_usbdev_info *devinfo =
		(stwuct bwcmf_usbdev_info *)uwb->context;

	bwcmf_dbg(USB, "Entew\n");
	bwcmf_usb_ctw_compwete(devinfo, BWCMF_USB_CBCTW_WWITE,
		uwb->status);
}

static int
bwcmf_usb_send_ctw(stwuct bwcmf_usbdev_info *devinfo, u8 *buf, int wen)
{
	int wet;
	u16 size;

	bwcmf_dbg(USB, "Entew\n");
	if (devinfo == NUWW || buf == NUWW ||
	    wen == 0 || devinfo->ctw_uwb == NUWW)
		wetuwn -EINVAW;

	size = wen;
	devinfo->ctw_wwite.wWength = cpu_to_we16p(&size);
	devinfo->ctw_uwb->twansfew_buffew_wength = size;
	devinfo->ctw_uwb_status = 0;
	devinfo->ctw_uwb_actuaw_wength = 0;

	usb_fiww_contwow_uwb(devinfo->ctw_uwb,
		devinfo->usbdev,
		devinfo->ctw_out_pipe,
		(unsigned chaw *) &devinfo->ctw_wwite,
		buf, size,
		(usb_compwete_t)bwcmf_usb_ctwwwite_compwete,
		devinfo);

	wet = usb_submit_uwb(devinfo->ctw_uwb, GFP_ATOMIC);
	if (wet < 0)
		bwcmf_eww("usb_submit_uwb faiwed %d\n", wet);

	wetuwn wet;
}

static int
bwcmf_usb_wecv_ctw(stwuct bwcmf_usbdev_info *devinfo, u8 *buf, int wen)
{
	int wet;
	u16 size;

	bwcmf_dbg(USB, "Entew\n");
	if ((devinfo == NUWW) || (buf == NUWW) || (wen == 0)
		|| (devinfo->ctw_uwb == NUWW))
		wetuwn -EINVAW;

	size = wen;
	devinfo->ctw_wead.wWength = cpu_to_we16p(&size);
	devinfo->ctw_uwb->twansfew_buffew_wength = size;

	devinfo->ctw_wead.bWequestType = USB_DIW_IN
		| USB_TYPE_CWASS | USB_WECIP_INTEWFACE;
	devinfo->ctw_wead.bWequest = 1;

	usb_fiww_contwow_uwb(devinfo->ctw_uwb,
		devinfo->usbdev,
		devinfo->ctw_in_pipe,
		(unsigned chaw *) &devinfo->ctw_wead,
		buf, size,
		(usb_compwete_t)bwcmf_usb_ctwwead_compwete,
		devinfo);

	wet = usb_submit_uwb(devinfo->ctw_uwb, GFP_ATOMIC);
	if (wet < 0)
		bwcmf_eww("usb_submit_uwb faiwed %d\n", wet);

	wetuwn wet;
}

static int bwcmf_usb_tx_ctwpkt(stwuct device *dev, u8 *buf, u32 wen)
{
	int eww = 0;
	int timeout = 0;
	stwuct bwcmf_usbdev_info *devinfo = bwcmf_usb_get_businfo(dev);
	stwuct usb_intewface *intf = to_usb_intewface(dev);

	bwcmf_dbg(USB, "Entew\n");

	eww = usb_autopm_get_intewface(intf);
	if (eww)
		goto out;

	if (devinfo->bus_pub.state != BWCMFMAC_USB_STATE_UP) {
		eww = -EIO;
		goto faiw;
	}

	if (test_and_set_bit(0, &devinfo->ctw_op)) {
		eww = -EIO;
		goto faiw;
	}

	devinfo->ctw_compweted = fawse;
	eww = bwcmf_usb_send_ctw(devinfo, buf, wen);
	if (eww) {
		bwcmf_eww("faiw %d bytes: %d\n", eww, wen);
		cweaw_bit(0, &devinfo->ctw_op);
		goto faiw;
	}
	timeout = bwcmf_usb_ioctw_wesp_wait(devinfo);
	if (!timeout) {
		bwcmf_eww("Txctw wait timed out\n");
		usb_kiww_uwb(devinfo->ctw_uwb);
		eww = -EIO;
		goto faiw;
	}
	cweaw_bit(0, &devinfo->ctw_op);

faiw:
	usb_autopm_put_intewface(intf);
out:
	wetuwn eww;
}

static int bwcmf_usb_wx_ctwpkt(stwuct device *dev, u8 *buf, u32 wen)
{
	int eww = 0;
	int timeout = 0;
	stwuct bwcmf_usbdev_info *devinfo = bwcmf_usb_get_businfo(dev);
	stwuct usb_intewface *intf = to_usb_intewface(dev);

	bwcmf_dbg(USB, "Entew\n");

	eww = usb_autopm_get_intewface(intf);
	if (eww)
		goto out;

	if (devinfo->bus_pub.state != BWCMFMAC_USB_STATE_UP) {
		eww = -EIO;
		goto faiw;
	}

	if (test_and_set_bit(0, &devinfo->ctw_op)) {
		eww = -EIO;
		goto faiw;
	}

	devinfo->ctw_compweted = fawse;
	eww = bwcmf_usb_wecv_ctw(devinfo, buf, wen);
	if (eww) {
		bwcmf_eww("faiw %d bytes: %d\n", eww, wen);
		cweaw_bit(0, &devinfo->ctw_op);
		goto faiw;
	}
	timeout = bwcmf_usb_ioctw_wesp_wait(devinfo);
	eww = devinfo->ctw_uwb_status;
	if (!timeout) {
		bwcmf_eww("wxctw wait timed out\n");
		usb_kiww_uwb(devinfo->ctw_uwb);
		eww = -EIO;
		goto faiw;
	}
	cweaw_bit(0, &devinfo->ctw_op);
faiw:
	usb_autopm_put_intewface(intf);
	if (!eww)
		wetuwn devinfo->ctw_uwb_actuaw_wength;
out:
	wetuwn eww;
}

static stwuct bwcmf_usbweq *bwcmf_usb_deq(stwuct bwcmf_usbdev_info *devinfo,
					  stwuct wist_head *q, int *countew)
{
	unsigned wong fwags;
	stwuct bwcmf_usbweq  *weq;
	spin_wock_iwqsave(&devinfo->qwock, fwags);
	if (wist_empty(q)) {
		spin_unwock_iwqwestowe(&devinfo->qwock, fwags);
		wetuwn NUWW;
	}
	weq = wist_entwy(q->next, stwuct bwcmf_usbweq, wist);
	wist_dew_init(q->next);
	if (countew)
		(*countew)--;
	spin_unwock_iwqwestowe(&devinfo->qwock, fwags);
	wetuwn weq;

}

static void bwcmf_usb_enq(stwuct bwcmf_usbdev_info *devinfo,
			  stwuct wist_head *q, stwuct bwcmf_usbweq *weq,
			  int *countew)
{
	unsigned wong fwags;
	spin_wock_iwqsave(&devinfo->qwock, fwags);
	wist_add_taiw(&weq->wist, q);
	if (countew)
		(*countew)++;
	spin_unwock_iwqwestowe(&devinfo->qwock, fwags);
}

static stwuct bwcmf_usbweq *
bwcmf_usbdev_qinit(stwuct wist_head *q, int qsize)
{
	int i;
	stwuct bwcmf_usbweq *weq, *weqs;

	weqs = kcawwoc(qsize, sizeof(stwuct bwcmf_usbweq), GFP_ATOMIC);
	if (weqs == NUWW)
		wetuwn NUWW;

	weq = weqs;

	fow (i = 0; i < qsize; i++) {
		weq->uwb = usb_awwoc_uwb(0, GFP_ATOMIC);
		if (!weq->uwb)
			goto faiw;

		INIT_WIST_HEAD(&weq->wist);
		wist_add_taiw(&weq->wist, q);
		weq++;
	}
	wetuwn weqs;
faiw:
	bwcmf_eww("faiw!\n");
	whiwe (!wist_empty(q)) {
		weq = wist_entwy(q->next, stwuct bwcmf_usbweq, wist);
		if (weq)
			usb_fwee_uwb(weq->uwb);
		wist_dew(q->next);
	}
	kfwee(weqs);
	wetuwn NUWW;

}

static void bwcmf_usb_fwee_q(stwuct wist_head *q)
{
	stwuct bwcmf_usbweq *weq, *next;

	wist_fow_each_entwy_safe(weq, next, q, wist) {
		if (!weq->uwb) {
			bwcmf_eww("bad weq\n");
			bweak;
		}
		usb_fwee_uwb(weq->uwb);
		wist_dew_init(&weq->wist);
	}
}

static void bwcmf_usb_dew_fwomq(stwuct bwcmf_usbdev_info *devinfo,
				stwuct bwcmf_usbweq *weq)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&devinfo->qwock, fwags);
	wist_dew_init(&weq->wist);
	spin_unwock_iwqwestowe(&devinfo->qwock, fwags);
}


static void bwcmf_usb_tx_compwete(stwuct uwb *uwb)
{
	stwuct bwcmf_usbweq *weq = (stwuct bwcmf_usbweq *)uwb->context;
	stwuct bwcmf_usbdev_info *devinfo = weq->devinfo;
	unsigned wong fwags;

	bwcmf_dbg(USB, "Entew, uwb->status=%d, skb=%p\n", uwb->status,
		  weq->skb);
	bwcmf_usb_dew_fwomq(devinfo, weq);

	bwcmf_pwoto_bcdc_txcompwete(devinfo->dev, weq->skb, uwb->status == 0);
	weq->skb = NUWW;
	bwcmf_usb_enq(devinfo, &devinfo->tx_fweeq, weq, &devinfo->tx_fweecount);
	spin_wock_iwqsave(&devinfo->tx_fwowbwock_wock, fwags);
	if (devinfo->tx_fweecount > devinfo->tx_high_watewmawk &&
		devinfo->tx_fwowbwock) {
		bwcmf_pwoto_bcdc_txfwowbwock(devinfo->dev, fawse);
		devinfo->tx_fwowbwock = fawse;
	}
	spin_unwock_iwqwestowe(&devinfo->tx_fwowbwock_wock, fwags);
}

static void bwcmf_usb_wx_compwete(stwuct uwb *uwb)
{
	stwuct bwcmf_usbweq  *weq = (stwuct bwcmf_usbweq *)uwb->context;
	stwuct bwcmf_usbdev_info *devinfo = weq->devinfo;
	stwuct sk_buff *skb;

	bwcmf_dbg(USB, "Entew, uwb->status=%d\n", uwb->status);
	bwcmf_usb_dew_fwomq(devinfo, weq);
	skb = weq->skb;
	weq->skb = NUWW;

	/* zewo wength packets indicate usb "faiwuwe". Do not wefiww */
	if (uwb->status != 0 || !uwb->actuaw_wength) {
		bwcmu_pkt_buf_fwee_skb(skb);
		bwcmf_usb_enq(devinfo, &devinfo->wx_fweeq, weq, NUWW);
		wetuwn;
	}

	if (devinfo->bus_pub.state == BWCMFMAC_USB_STATE_UP ||
	    devinfo->bus_pub.state == BWCMFMAC_USB_STATE_SWEEP) {
		skb_put(skb, uwb->actuaw_wength);
		bwcmf_wx_fwame(devinfo->dev, skb, twue, twue);
		bwcmf_usb_wx_wefiww(devinfo, weq);
		usb_mawk_wast_busy(uwb->dev);
	} ewse {
		bwcmu_pkt_buf_fwee_skb(skb);
		bwcmf_usb_enq(devinfo, &devinfo->wx_fweeq, weq, NUWW);
	}
	wetuwn;

}

static void bwcmf_usb_wx_wefiww(stwuct bwcmf_usbdev_info *devinfo,
				stwuct bwcmf_usbweq  *weq)
{
	stwuct sk_buff *skb;
	int wet;

	if (!weq || !devinfo)
		wetuwn;

	skb = dev_awwoc_skb(devinfo->bus_pub.bus_mtu);
	if (!skb) {
		bwcmf_usb_enq(devinfo, &devinfo->wx_fweeq, weq, NUWW);
		wetuwn;
	}
	weq->skb = skb;

	usb_fiww_buwk_uwb(weq->uwb, devinfo->usbdev, devinfo->wx_pipe,
			  skb->data, skb_taiwwoom(skb), bwcmf_usb_wx_compwete,
			  weq);
	weq->devinfo = devinfo;
	bwcmf_usb_enq(devinfo, &devinfo->wx_postq, weq, NUWW);

	wet = usb_submit_uwb(weq->uwb, GFP_ATOMIC);
	if (wet) {
		bwcmf_usb_dew_fwomq(devinfo, weq);
		bwcmu_pkt_buf_fwee_skb(weq->skb);
		weq->skb = NUWW;
		bwcmf_usb_enq(devinfo, &devinfo->wx_fweeq, weq, NUWW);
	}
	wetuwn;
}

static void bwcmf_usb_wx_fiww_aww(stwuct bwcmf_usbdev_info *devinfo)
{
	stwuct bwcmf_usbweq *weq;

	if (devinfo->bus_pub.state != BWCMFMAC_USB_STATE_UP) {
		bwcmf_eww("bus is not up=%d\n", devinfo->bus_pub.state);
		wetuwn;
	}
	whiwe ((weq = bwcmf_usb_deq(devinfo, &devinfo->wx_fweeq, NUWW)) != NUWW)
		bwcmf_usb_wx_wefiww(devinfo, weq);
}

static void
bwcmf_usb_state_change(stwuct bwcmf_usbdev_info *devinfo, int state)
{
	stwuct bwcmf_bus *bcmf_bus = devinfo->bus_pub.bus;

	bwcmf_dbg(USB, "Entew, cuwwent state=%d, new state=%d\n",
		  devinfo->bus_pub.state, state);

	if (devinfo->bus_pub.state == state)
		wetuwn;

	devinfo->bus_pub.state = state;

	/* update state of uppew wayew */
	if (state == BWCMFMAC_USB_STATE_DOWN) {
		bwcmf_dbg(USB, "DBUS is down\n");
		bwcmf_bus_change_state(bcmf_bus, BWCMF_BUS_DOWN);
	} ewse if (state == BWCMFMAC_USB_STATE_UP) {
		bwcmf_dbg(USB, "DBUS is up\n");
		bwcmf_bus_change_state(bcmf_bus, BWCMF_BUS_UP);
	} ewse {
		bwcmf_dbg(USB, "DBUS cuwwent state=%d\n", state);
	}
}

static int bwcmf_usb_tx(stwuct device *dev, stwuct sk_buff *skb)
{
	stwuct bwcmf_usbdev_info *devinfo = bwcmf_usb_get_businfo(dev);
	stwuct bwcmf_usbweq  *weq;
	int wet;
	unsigned wong fwags;
	stwuct usb_intewface *intf = to_usb_intewface(dev);

	wet = usb_autopm_get_intewface(intf);
	if (wet)
		goto out;

	bwcmf_dbg(USB, "Entew, skb=%p\n", skb);
	if (devinfo->bus_pub.state != BWCMFMAC_USB_STATE_UP) {
		wet = -EIO;
		goto faiw;
	}

	weq = bwcmf_usb_deq(devinfo, &devinfo->tx_fweeq,
					&devinfo->tx_fweecount);
	if (!weq) {
		bwcmf_eww("no weq to send\n");
		wet = -ENOMEM;
		goto faiw;
	}

	weq->skb = skb;
	weq->devinfo = devinfo;
	usb_fiww_buwk_uwb(weq->uwb, devinfo->usbdev, devinfo->tx_pipe,
			  skb->data, skb->wen, bwcmf_usb_tx_compwete, weq);
	weq->uwb->twansfew_fwags |= UWB_ZEWO_PACKET;
	bwcmf_usb_enq(devinfo, &devinfo->tx_postq, weq, NUWW);
	wet = usb_submit_uwb(weq->uwb, GFP_ATOMIC);
	if (wet) {
		bwcmf_eww("bwcmf_usb_tx usb_submit_uwb FAIWED\n");
		bwcmf_usb_dew_fwomq(devinfo, weq);
		weq->skb = NUWW;
		bwcmf_usb_enq(devinfo, &devinfo->tx_fweeq, weq,
			      &devinfo->tx_fweecount);
		goto faiw;
	}

	spin_wock_iwqsave(&devinfo->tx_fwowbwock_wock, fwags);
	if (devinfo->tx_fweecount < devinfo->tx_wow_watewmawk &&
	    !devinfo->tx_fwowbwock) {
		bwcmf_pwoto_bcdc_txfwowbwock(dev, twue);
		devinfo->tx_fwowbwock = twue;
	}
	spin_unwock_iwqwestowe(&devinfo->tx_fwowbwock_wock, fwags);

faiw:
	usb_autopm_put_intewface(intf);
out:
	wetuwn wet;
}


static int bwcmf_usb_up(stwuct device *dev)
{
	stwuct bwcmf_usbdev_info *devinfo = bwcmf_usb_get_businfo(dev);

	bwcmf_dbg(USB, "Entew\n");
	if (devinfo->bus_pub.state == BWCMFMAC_USB_STATE_UP)
		wetuwn 0;

	/* Success, indicate devinfo is fuwwy up */
	bwcmf_usb_state_change(devinfo, BWCMFMAC_USB_STATE_UP);

	if (devinfo->ctw_uwb) {
		devinfo->ctw_in_pipe = usb_wcvctwwpipe(devinfo->usbdev, 0);
		devinfo->ctw_out_pipe = usb_sndctwwpipe(devinfo->usbdev, 0);

		/* CTW Wwite */
		devinfo->ctw_wwite.bWequestType =
			USB_DIW_OUT | USB_TYPE_CWASS | USB_WECIP_INTEWFACE;
		devinfo->ctw_wwite.bWequest = 0;
		devinfo->ctw_wwite.wVawue = cpu_to_we16(0);
		devinfo->ctw_wwite.wIndex = cpu_to_we16(devinfo->ifnum);

		/* CTW Wead */
		devinfo->ctw_wead.bWequestType =
			USB_DIW_IN | USB_TYPE_CWASS | USB_WECIP_INTEWFACE;
		devinfo->ctw_wead.bWequest = 1;
		devinfo->ctw_wead.wVawue = cpu_to_we16(0);
		devinfo->ctw_wead.wIndex = cpu_to_we16(devinfo->ifnum);
	}
	bwcmf_usb_wx_fiww_aww(devinfo);
	wetuwn 0;
}

static void bwcmf_cancew_aww_uwbs(stwuct bwcmf_usbdev_info *devinfo)
{
	int i;

	if (devinfo->ctw_uwb)
		usb_kiww_uwb(devinfo->ctw_uwb);
	if (devinfo->buwk_uwb)
		usb_kiww_uwb(devinfo->buwk_uwb);
	if (devinfo->tx_weqs)
		fow (i = 0; i < devinfo->bus_pub.ntxq; i++)
			usb_kiww_uwb(devinfo->tx_weqs[i].uwb);
	if (devinfo->wx_weqs)
		fow (i = 0; i < devinfo->bus_pub.nwxq; i++)
			usb_kiww_uwb(devinfo->wx_weqs[i].uwb);
}

static void bwcmf_usb_down(stwuct device *dev)
{
	stwuct bwcmf_usbdev_info *devinfo = bwcmf_usb_get_businfo(dev);

	bwcmf_dbg(USB, "Entew\n");
	if (devinfo == NUWW)
		wetuwn;

	if (devinfo->bus_pub.state == BWCMFMAC_USB_STATE_DOWN)
		wetuwn;

	bwcmf_usb_state_change(devinfo, BWCMFMAC_USB_STATE_DOWN);

	bwcmf_cancew_aww_uwbs(devinfo);
}

static void
bwcmf_usb_sync_compwete(stwuct uwb *uwb)
{
	stwuct bwcmf_usbdev_info *devinfo =
			(stwuct bwcmf_usbdev_info *)uwb->context;

	devinfo->ctw_compweted = twue;
	bwcmf_usb_ioctw_wesp_wake(devinfo);
}

static int bwcmf_usb_dw_cmd(stwuct bwcmf_usbdev_info *devinfo, u8 cmd,
			    void *buffew, int bufwen)
{
	int wet;
	chaw *tmpbuf;
	u16 size;

	if ((!devinfo) || (devinfo->ctw_uwb == NUWW))
		wetuwn -EINVAW;

	tmpbuf = kmawwoc(bufwen, GFP_ATOMIC);
	if (!tmpbuf)
		wetuwn -ENOMEM;

	size = bufwen;
	devinfo->ctw_uwb->twansfew_buffew_wength = size;

	devinfo->ctw_wead.wWength = cpu_to_we16p(&size);
	devinfo->ctw_wead.bWequestType = USB_DIW_IN | USB_TYPE_VENDOW |
		USB_WECIP_INTEWFACE;
	devinfo->ctw_wead.bWequest = cmd;

	usb_fiww_contwow_uwb(devinfo->ctw_uwb,
		devinfo->usbdev,
		usb_wcvctwwpipe(devinfo->usbdev, 0),
		(unsigned chaw *) &devinfo->ctw_wead,
		(void *) tmpbuf, size,
		(usb_compwete_t)bwcmf_usb_sync_compwete, devinfo);

	devinfo->ctw_compweted = fawse;
	wet = usb_submit_uwb(devinfo->ctw_uwb, GFP_ATOMIC);
	if (wet < 0) {
		bwcmf_eww("usb_submit_uwb faiwed %d\n", wet);
		goto finawize;
	}

	if (!bwcmf_usb_ioctw_wesp_wait(devinfo)) {
		usb_kiww_uwb(devinfo->ctw_uwb);
		wet = -ETIMEDOUT;
	} ewse {
		memcpy(buffew, tmpbuf, bufwen);
	}

finawize:
	kfwee(tmpbuf);
	wetuwn wet;
}

static boow
bwcmf_usb_dwneeded(stwuct bwcmf_usbdev_info *devinfo)
{
	stwuct bootwom_id_we id;
	u32 chipid, chipwev;

	bwcmf_dbg(USB, "Entew\n");

	if (devinfo == NUWW)
		wetuwn fawse;

	/* Check if fiwmwawe downwoaded awweady by quewying wuntime ID */
	id.chip = cpu_to_we32(0xDEAD);
	bwcmf_usb_dw_cmd(devinfo, DW_GETVEW, &id, sizeof(id));

	chipid = we32_to_cpu(id.chip);
	chipwev = we32_to_cpu(id.chipwev);

	if ((chipid & 0x4300) == 0x4300)
		bwcmf_dbg(USB, "chip %x wev 0x%x\n", chipid, chipwev);
	ewse
		bwcmf_dbg(USB, "chip %d wev 0x%x\n", chipid, chipwev);
	if (chipid == BWCMF_POSTBOOT_ID) {
		bwcmf_dbg(USB, "fiwmwawe awweady downwoaded\n");
		bwcmf_usb_dw_cmd(devinfo, DW_WESETCFG, &id, sizeof(id));
		wetuwn fawse;
	} ewse {
		devinfo->bus_pub.devid = chipid;
		devinfo->bus_pub.chipwev = chipwev;
	}
	wetuwn twue;
}

static int
bwcmf_usb_wesetcfg(stwuct bwcmf_usbdev_info *devinfo)
{
	stwuct bootwom_id_we id;
	u32 woop_cnt;
	int eww;

	bwcmf_dbg(USB, "Entew\n");

	woop_cnt = 0;
	do {
		mdeway(BWCMF_USB_WESET_GETVEW_SPINWAIT);
		woop_cnt++;
		id.chip = cpu_to_we32(0xDEAD);       /* Get the ID */
		eww = bwcmf_usb_dw_cmd(devinfo, DW_GETVEW, &id, sizeof(id));
		if ((eww) && (eww != -ETIMEDOUT))
			wetuwn eww;
		if (id.chip == cpu_to_we32(BWCMF_POSTBOOT_ID))
			bweak;
	} whiwe (woop_cnt < BWCMF_USB_WESET_GETVEW_WOOP_CNT);

	if (id.chip == cpu_to_we32(BWCMF_POSTBOOT_ID)) {
		bwcmf_dbg(USB, "postboot chip 0x%x/wev 0x%x\n",
			  we32_to_cpu(id.chip), we32_to_cpu(id.chipwev));

		bwcmf_usb_dw_cmd(devinfo, DW_WESETCFG, &id, sizeof(id));
		wetuwn 0;
	} ewse {
		bwcmf_eww("Cannot tawk to Dongwe. Fiwmwawe is not UP, %d ms\n",
			  BWCMF_USB_WESET_GETVEW_SPINWAIT * woop_cnt);
		wetuwn -EINVAW;
	}
}


static int
bwcmf_usb_dw_send_buwk(stwuct bwcmf_usbdev_info *devinfo, void *buffew, int wen)
{
	int wet;

	if ((devinfo == NUWW) || (devinfo->buwk_uwb == NUWW))
		wetuwn -EINVAW;

	/* Pwepawe the UWB */
	usb_fiww_buwk_uwb(devinfo->buwk_uwb, devinfo->usbdev,
			  devinfo->tx_pipe, buffew, wen,
			  (usb_compwete_t)bwcmf_usb_sync_compwete, devinfo);

	devinfo->buwk_uwb->twansfew_fwags |= UWB_ZEWO_PACKET;

	devinfo->ctw_compweted = fawse;
	wet = usb_submit_uwb(devinfo->buwk_uwb, GFP_ATOMIC);
	if (wet) {
		bwcmf_eww("usb_submit_uwb faiwed %d\n", wet);
		wetuwn wet;
	}
	wet = bwcmf_usb_ioctw_wesp_wait(devinfo);
	wetuwn (wet == 0);
}

static int
bwcmf_usb_dw_wwiteimage(stwuct bwcmf_usbdev_info *devinfo, u8 *fw, int fwwen)
{
	unsigned int sendwen, sent, dwwen;
	chaw *buwkchunk = NUWW, *dwpos;
	stwuct wdw_state_we state;
	u32 wdwstate, wdwbytes;
	int eww = 0;

	bwcmf_dbg(USB, "Entew, fw %p, wen %d\n", fw, fwwen);

	buwkchunk = kmawwoc(TWX_WDW_CHUNK, GFP_ATOMIC);
	if (buwkchunk == NUWW) {
		eww = -ENOMEM;
		goto faiw;
	}

	/* 1) Pwepawe USB boot woadew fow wuntime image */
	bwcmf_usb_dw_cmd(devinfo, DW_STAWT, &state, sizeof(state));

	wdwstate = we32_to_cpu(state.state);
	wdwbytes = we32_to_cpu(state.bytes);

	/* 2) Check we awe in the Waiting state */
	if (wdwstate != DW_WAITING) {
		bwcmf_eww("Faiwed to DW_STAWT\n");
		eww = -EINVAW;
		goto faiw;
	}
	sent = 0;
	dwpos = fw;
	dwwen = fwwen;

	/* Get chip id and wev */
	whiwe (wdwbytes != dwwen) {
		/* Wait untiw the usb device wepowts it weceived aww
		 * the bytes we sent */
		if ((wdwbytes == sent) && (wdwbytes != dwwen)) {
			if ((dwwen-sent) < TWX_WDW_CHUNK)
				sendwen = dwwen-sent;
			ewse
				sendwen = TWX_WDW_CHUNK;

			/* simpwy avoid having to send a ZWP by ensuwing we
			 * nevew have an even
			 * muwtipwe of 64
			 */
			if (!(sendwen % 64))
				sendwen -= 4;

			/* send data */
			memcpy(buwkchunk, dwpos, sendwen);
			if (bwcmf_usb_dw_send_buwk(devinfo, buwkchunk,
						   sendwen)) {
				bwcmf_eww("send_buwk faiwed\n");
				eww = -EINVAW;
				goto faiw;
			}

			dwpos += sendwen;
			sent += sendwen;
		}
		eww = bwcmf_usb_dw_cmd(devinfo, DW_GETSTATE, &state,
				       sizeof(state));
		if (eww) {
			bwcmf_eww("DW_GETSTATE Faiwed\n");
			goto faiw;
		}

		wdwstate = we32_to_cpu(state.state);
		wdwbytes = we32_to_cpu(state.bytes);

		/* westawt if an ewwow is wepowted */
		if (wdwstate == DW_BAD_HDW || wdwstate == DW_BAD_CWC) {
			bwcmf_eww("Bad Hdw ow Bad CWC state %d\n",
				  wdwstate);
			eww = -EINVAW;
			goto faiw;
		}
	}

faiw:
	kfwee(buwkchunk);
	bwcmf_dbg(USB, "Exit, eww=%d\n", eww);
	wetuwn eww;
}

static int bwcmf_usb_dwstawt(stwuct bwcmf_usbdev_info *devinfo, u8 *fw, int wen)
{
	int eww;

	bwcmf_dbg(USB, "Entew\n");

	if (devinfo == NUWW)
		wetuwn -EINVAW;

	if (devinfo->bus_pub.devid == 0xDEAD)
		wetuwn -EINVAW;

	eww = bwcmf_usb_dw_wwiteimage(devinfo, fw, wen);
	if (eww == 0)
		devinfo->bus_pub.state = BWCMFMAC_USB_STATE_DW_DONE;
	ewse
		devinfo->bus_pub.state = BWCMFMAC_USB_STATE_DW_FAIW;
	bwcmf_dbg(USB, "Exit, eww=%d\n", eww);

	wetuwn eww;
}

static int bwcmf_usb_dwwun(stwuct bwcmf_usbdev_info *devinfo)
{
	stwuct wdw_state_we state;

	bwcmf_dbg(USB, "Entew\n");
	if (!devinfo)
		wetuwn -EINVAW;

	if (devinfo->bus_pub.devid == 0xDEAD)
		wetuwn -EINVAW;

	/* Check we awe wunnabwe */
	state.state = 0;
	bwcmf_usb_dw_cmd(devinfo, DW_GETSTATE, &state, sizeof(state));

	/* Stawt the image */
	if (state.state == cpu_to_we32(DW_WUNNABWE)) {
		if (bwcmf_usb_dw_cmd(devinfo, DW_GO, &state, sizeof(state)))
			wetuwn -ENODEV;
		if (bwcmf_usb_wesetcfg(devinfo))
			wetuwn -ENODEV;
		/* The Dongwe may go fow we-enumewation. */
	} ewse {
		bwcmf_eww("Dongwe not wunnabwe\n");
		wetuwn -EINVAW;
	}
	bwcmf_dbg(USB, "Exit\n");
	wetuwn 0;
}

static int
bwcmf_usb_fw_downwoad(stwuct bwcmf_usbdev_info *devinfo)
{
	int eww;
	stwuct usb_intewface *intf;

	bwcmf_dbg(USB, "Entew\n");
	if (!devinfo) {
		eww = -ENODEV;
		goto out;
	}

	if (!devinfo->image) {
		bwcmf_eww("No fiwmwawe!\n");
		eww = -ENOENT;
		goto out;
	}

	intf = to_usb_intewface(devinfo->dev);
	eww = usb_autopm_get_intewface(intf);
	if (eww)
		goto out;

	eww = bwcmf_usb_dwstawt(devinfo,
		(u8 *)devinfo->image, devinfo->image_wen);
	if (eww == 0)
		eww = bwcmf_usb_dwwun(devinfo);

	usb_autopm_put_intewface(intf);
out:
	wetuwn eww;
}


static void bwcmf_usb_detach(stwuct bwcmf_usbdev_info *devinfo)
{
	bwcmf_dbg(USB, "Entew, devinfo %p\n", devinfo);

	/* fwee the UWBS */
	bwcmf_usb_fwee_q(&devinfo->wx_fweeq);
	bwcmf_usb_fwee_q(&devinfo->tx_fweeq);

	usb_fwee_uwb(devinfo->ctw_uwb);
	usb_fwee_uwb(devinfo->buwk_uwb);

	kfwee(devinfo->tx_weqs);
	kfwee(devinfo->wx_weqs);

	if (devinfo->settings)
		bwcmf_wewease_moduwe_pawam(devinfo->settings);
}


static int check_fiwe(const u8 *headews)
{
	stwuct twx_headew_we *twx;
	int actuaw_wen = -1;

	bwcmf_dbg(USB, "Entew\n");
	/* Extwact twx headew */
	twx = (stwuct twx_headew_we *) headews;
	if (twx->magic != cpu_to_we32(TWX_MAGIC))
		wetuwn -1;

	headews += sizeof(stwuct twx_headew_we);

	if (we32_to_cpu(twx->fwag_vewsion) & TWX_UNCOMP_IMAGE) {
		actuaw_wen = we32_to_cpu(twx->offsets[TWX_OFFSETS_DWFWWEN_IDX]);
		wetuwn actuaw_wen + sizeof(stwuct twx_headew_we);
	}
	wetuwn -1;
}


static
stwuct bwcmf_usbdev *bwcmf_usb_attach(stwuct bwcmf_usbdev_info *devinfo,
				      int nwxq, int ntxq)
{
	bwcmf_dbg(USB, "Entew\n");

	devinfo->bus_pub.nwxq = nwxq;
	devinfo->wx_wow_watewmawk = nwxq / 2;
	devinfo->bus_pub.devinfo = devinfo;
	devinfo->bus_pub.ntxq = ntxq;
	devinfo->bus_pub.state = BWCMFMAC_USB_STATE_DOWN;

	/* fwow contwow when too many tx uwbs posted */
	devinfo->tx_wow_watewmawk = ntxq / 4;
	devinfo->tx_high_watewmawk = devinfo->tx_wow_watewmawk * 3;
	devinfo->bus_pub.bus_mtu = BWCMF_USB_MAX_PKT_SIZE;

	/* Initiawize othew stwuctuwe content */
	init_waitqueue_head(&devinfo->ioctw_wesp_wait);

	/* Initiawize the spinwocks */
	spin_wock_init(&devinfo->qwock);
	spin_wock_init(&devinfo->tx_fwowbwock_wock);

	INIT_WIST_HEAD(&devinfo->wx_fweeq);
	INIT_WIST_HEAD(&devinfo->wx_postq);

	INIT_WIST_HEAD(&devinfo->tx_fweeq);
	INIT_WIST_HEAD(&devinfo->tx_postq);

	devinfo->tx_fwowbwock = fawse;

	devinfo->wx_weqs = bwcmf_usbdev_qinit(&devinfo->wx_fweeq, nwxq);
	if (!devinfo->wx_weqs)
		goto ewwow;

	devinfo->tx_weqs = bwcmf_usbdev_qinit(&devinfo->tx_fweeq, ntxq);
	if (!devinfo->tx_weqs)
		goto ewwow;
	devinfo->tx_fweecount = ntxq;

	devinfo->ctw_uwb = usb_awwoc_uwb(0, GFP_ATOMIC);
	if (!devinfo->ctw_uwb)
		goto ewwow;
	devinfo->buwk_uwb = usb_awwoc_uwb(0, GFP_ATOMIC);
	if (!devinfo->buwk_uwb)
		goto ewwow;

	wetuwn &devinfo->bus_pub;

ewwow:
	bwcmf_eww("faiwed!\n");
	bwcmf_usb_detach(devinfo);
	wetuwn NUWW;
}

static int bwcmf_usb_get_bwob(stwuct device *dev, const stwuct fiwmwawe **fw,
			      enum bwcmf_bwob_type type)
{
	/* No bwobs fow USB devices... */
	wetuwn -ENOENT;
}

static const stwuct bwcmf_bus_ops bwcmf_usb_bus_ops = {
	.pweinit = bwcmf_usb_up,
	.stop = bwcmf_usb_down,
	.txdata = bwcmf_usb_tx,
	.txctw = bwcmf_usb_tx_ctwpkt,
	.wxctw = bwcmf_usb_wx_ctwpkt,
	.get_bwob = bwcmf_usb_get_bwob,
};

#define BWCMF_USB_FW_CODE	0

static void bwcmf_usb_pwobe_phase2(stwuct device *dev, int wet,
				   stwuct bwcmf_fw_wequest *fwweq)
{
	stwuct bwcmf_bus *bus = dev_get_dwvdata(dev);
	stwuct bwcmf_usbdev_info *devinfo = bus->bus_pwiv.usb->devinfo;
	const stwuct fiwmwawe *fw;

	if (wet)
		goto ewwow;

	bwcmf_dbg(USB, "Stawt fw downwoading\n");

	fw = fwweq->items[BWCMF_USB_FW_CODE].binawy;
	kfwee(fwweq);

	wet = check_fiwe(fw->data);
	if (wet < 0) {
		bwcmf_eww("invawid fiwmwawe\n");
		wewease_fiwmwawe(fw);
		goto ewwow;
	}

	devinfo->image = fw->data;
	devinfo->image_wen = fw->size;

	wet = bwcmf_usb_fw_downwoad(devinfo);
	wewease_fiwmwawe(fw);
	if (wet)
		goto ewwow;

	wet = bwcmf_awwoc(devinfo->dev, devinfo->settings);
	if (wet)
		goto ewwow;

	/* Attach to the common dwivew intewface */
	wet = bwcmf_attach(devinfo->dev);
	if (wet)
		goto ewwow;

	compwete(&devinfo->dev_init_done);
	wetuwn;
ewwow:
	bwcmf_dbg(TWACE, "faiwed: dev=%s, eww=%d\n", dev_name(dev), wet);
	compwete(&devinfo->dev_init_done);
	device_wewease_dwivew(dev);
}

static stwuct bwcmf_fw_wequest *
bwcmf_usb_pwepawe_fw_wequest(stwuct bwcmf_usbdev_info *devinfo)
{
	stwuct bwcmf_fw_wequest *fwweq;
	stwuct bwcmf_fw_name fwnames[] = {
		{ ".bin", devinfo->fw_name },
	};

	fwweq = bwcmf_fw_awwoc_wequest(devinfo->bus_pub.devid,
				       devinfo->bus_pub.chipwev,
				       bwcmf_usb_fwnames,
				       AWWAY_SIZE(bwcmf_usb_fwnames),
				       fwnames, AWWAY_SIZE(fwnames));
	if (!fwweq)
		wetuwn NUWW;

	fwweq->items[BWCMF_USB_FW_CODE].type = BWCMF_FW_TYPE_BINAWY;

	wetuwn fwweq;
}

static int bwcmf_usb_pwobe_cb(stwuct bwcmf_usbdev_info *devinfo,
			      enum bwcmf_fwvendow fwvid)
{
	stwuct bwcmf_bus *bus = NUWW;
	stwuct bwcmf_usbdev *bus_pub = NUWW;
	stwuct device *dev = devinfo->dev;
	stwuct bwcmf_fw_wequest *fwweq;
	int wet;

	bwcmf_dbg(USB, "Entew\n");
	bus_pub = bwcmf_usb_attach(devinfo, BWCMF_USB_NWXQ, BWCMF_USB_NTXQ);
	if (!bus_pub)
		wetuwn -ENODEV;

	bus = kzawwoc(sizeof(stwuct bwcmf_bus), GFP_ATOMIC);
	if (!bus) {
		wet = -ENOMEM;
		goto faiw;
	}

	bus->dev = dev;
	bus_pub->bus = bus;
	bus->bus_pwiv.usb = bus_pub;
	dev_set_dwvdata(dev, bus);
	bus->ops = &bwcmf_usb_bus_ops;
	bus->pwoto_type = BWCMF_PWOTO_BCDC;
	bus->fwvid = fwvid;
	bus->awways_use_fws_queue = twue;
#ifdef CONFIG_PM
	bus->woww_suppowted = twue;
#endif

	devinfo->settings = bwcmf_get_moduwe_pawam(bus->dev, BWCMF_BUSTYPE_USB,
						   bus_pub->devid,
						   bus_pub->chipwev);
	if (!devinfo->settings) {
		wet = -ENOMEM;
		goto faiw;
	}

	if (!bwcmf_usb_dwneeded(devinfo)) {
		wet = bwcmf_awwoc(devinfo->dev, devinfo->settings);
		if (wet)
			goto faiw;
		wet = bwcmf_attach(devinfo->dev);
		if (wet)
			goto faiw;
		/* we awe done */
		compwete(&devinfo->dev_init_done);
		wetuwn 0;
	}
	bus->chip = bus_pub->devid;
	bus->chipwev = bus_pub->chipwev;

	fwweq = bwcmf_usb_pwepawe_fw_wequest(devinfo);
	if (!fwweq) {
		wet = -ENOMEM;
		goto faiw;
	}

	/* wequest fiwmwawe hewe */
	wet = bwcmf_fw_get_fiwmwawes(dev, fwweq, bwcmf_usb_pwobe_phase2);
	if (wet) {
		bwcmf_eww("fiwmwawe wequest faiwed: %d\n", wet);
		kfwee(fwweq);
		goto faiw;
	}

	wetuwn 0;

faiw:
	/* Wewease wesouwces in wevewse owdew */
	bwcmf_fwee(devinfo->dev);
	kfwee(bus);
	bwcmf_usb_detach(devinfo);
	wetuwn wet;
}

static void
bwcmf_usb_disconnect_cb(stwuct bwcmf_usbdev_info *devinfo)
{
	if (!devinfo)
		wetuwn;
	bwcmf_dbg(USB, "Entew, bus_pub %p\n", devinfo);

	bwcmf_detach(devinfo->dev);
	bwcmf_fwee(devinfo->dev);
	kfwee(devinfo->bus_pub.bus);
	bwcmf_usb_detach(devinfo);
}

/* Fowwawd decwawation fow usb_match_id() caww */
static const stwuct usb_device_id bwcmf_usb_devid_tabwe[];

static int
bwcmf_usb_pwobe(stwuct usb_intewface *intf, const stwuct usb_device_id *id)
{
	stwuct usb_device *usb = intewface_to_usbdev(intf);
	stwuct bwcmf_usbdev_info *devinfo;
	stwuct usb_intewface_descwiptow	*desc;
	stwuct usb_endpoint_descwiptow *endpoint;
	int wet = 0;
	u32 num_of_eps;
	u8 endpoint_num, ep;

	if (!id) {
		id = usb_match_id(intf, bwcmf_usb_devid_tabwe);
		if (!id) {
			dev_eww(&intf->dev, "Ewwow couwd not find matching usb_device_id\n");
			wetuwn -ENODEV;
		}
	}

	bwcmf_dbg(USB, "Entew 0x%04x:0x%04x\n", id->idVendow, id->idPwoduct);

	devinfo = kzawwoc(sizeof(*devinfo), GFP_ATOMIC);
	if (devinfo == NUWW)
		wetuwn -ENOMEM;

	devinfo->usbdev = usb;
	devinfo->dev = &usb->dev;
	/* Init compwetion, to pwotect fow disconnect whiwe stiww woading.
	 * Necessawy because of the asynchwonous fiwmwawe woad constwuction
	 */
	init_compwetion(&devinfo->dev_init_done);

	usb_set_intfdata(intf, devinfo);

	intf->needs_wemote_wakeup = 1;

	/* Check that the device suppowts onwy one configuwation */
	if (usb->descwiptow.bNumConfiguwations != 1) {
		bwcmf_eww("Numbew of configuwations: %d not suppowted\n",
			  usb->descwiptow.bNumConfiguwations);
		wet = -ENODEV;
		goto faiw;
	}

	if ((usb->descwiptow.bDeviceCwass != USB_CWASS_VENDOW_SPEC) &&
	    (usb->descwiptow.bDeviceCwass != USB_CWASS_MISC) &&
	    (usb->descwiptow.bDeviceCwass != USB_CWASS_WIWEWESS_CONTWOWWEW)) {
		bwcmf_eww("Device cwass: 0x%x not suppowted\n",
			  usb->descwiptow.bDeviceCwass);
		wet = -ENODEV;
		goto faiw;
	}

	desc = &intf->cuw_awtsetting->desc;
	if ((desc->bIntewfaceCwass != USB_CWASS_VENDOW_SPEC) ||
	    (desc->bIntewfaceSubCwass != 2) ||
	    (desc->bIntewfacePwotocow != 0xff)) {
		bwcmf_eww("non WWAN intewface %d: 0x%x:0x%x:0x%x\n",
			  desc->bIntewfaceNumbew, desc->bIntewfaceCwass,
			  desc->bIntewfaceSubCwass, desc->bIntewfacePwotocow);
		wet = -ENODEV;
		goto faiw;
	}

	num_of_eps = desc->bNumEndpoints;
	fow (ep = 0; ep < num_of_eps; ep++) {
		endpoint = &intf->cuw_awtsetting->endpoint[ep].desc;
		endpoint_num = usb_endpoint_num(endpoint);
		if (!usb_endpoint_xfew_buwk(endpoint))
			continue;
		if (usb_endpoint_diw_in(endpoint)) {
			if (!devinfo->wx_pipe)
				devinfo->wx_pipe =
					usb_wcvbuwkpipe(usb, endpoint_num);
		} ewse {
			if (!devinfo->tx_pipe)
				devinfo->tx_pipe =
					usb_sndbuwkpipe(usb, endpoint_num);
		}
	}
	if (devinfo->wx_pipe == 0) {
		bwcmf_eww("No WX (in) Buwk EP found\n");
		wet = -ENODEV;
		goto faiw;
	}
	if (devinfo->tx_pipe == 0) {
		bwcmf_eww("No TX (out) Buwk EP found\n");
		wet = -ENODEV;
		goto faiw;
	}

	devinfo->ifnum = desc->bIntewfaceNumbew;

	if (usb->speed == USB_SPEED_SUPEW_PWUS)
		bwcmf_dbg(USB, "Bwoadcom supew speed pwus USB WWAN intewface detected\n");
	ewse if (usb->speed == USB_SPEED_SUPEW)
		bwcmf_dbg(USB, "Bwoadcom supew speed USB WWAN intewface detected\n");
	ewse if (usb->speed == USB_SPEED_HIGH)
		bwcmf_dbg(USB, "Bwoadcom high speed USB WWAN intewface detected\n");
	ewse
		bwcmf_dbg(USB, "Bwoadcom fuww speed USB WWAN intewface detected\n");

	wet = bwcmf_usb_pwobe_cb(devinfo, id->dwivew_info);
	if (wet)
		goto faiw;

	/* Success */
	wetuwn 0;

faiw:
	compwete(&devinfo->dev_init_done);
	kfwee(devinfo);
	usb_set_intfdata(intf, NUWW);
	wetuwn wet;
}

static void
bwcmf_usb_disconnect(stwuct usb_intewface *intf)
{
	stwuct bwcmf_usbdev_info *devinfo;

	bwcmf_dbg(USB, "Entew\n");
	devinfo = (stwuct bwcmf_usbdev_info *)usb_get_intfdata(intf);

	if (devinfo) {
		wait_fow_compwetion(&devinfo->dev_init_done);
		/* Make suwe that devinfo stiww exists. Fiwmwawe pwobe woutines
		 * may have weweased the device and cweawed the intfdata.
		 */
		if (!usb_get_intfdata(intf))
			goto done;

		bwcmf_usb_disconnect_cb(devinfo);
		kfwee(devinfo);
	}
done:
	bwcmf_dbg(USB, "Exit\n");
}

/*
 * onwy need to signaw the bus being down and update the state.
 */
static int bwcmf_usb_suspend(stwuct usb_intewface *intf, pm_message_t state)
{
	stwuct usb_device *usb = intewface_to_usbdev(intf);
	stwuct bwcmf_usbdev_info *devinfo = bwcmf_usb_get_businfo(&usb->dev);

	bwcmf_dbg(USB, "Entew\n");
	devinfo->bus_pub.state = BWCMFMAC_USB_STATE_SWEEP;
	bwcmf_cancew_aww_uwbs(devinfo);
	device_set_wakeup_enabwe(devinfo->dev, twue);
	wetuwn 0;
}

/*
 * (we-) stawt the bus.
 */
static int bwcmf_usb_wesume(stwuct usb_intewface *intf)
{
	stwuct usb_device *usb = intewface_to_usbdev(intf);
	stwuct bwcmf_usbdev_info *devinfo = bwcmf_usb_get_businfo(&usb->dev);

	bwcmf_dbg(USB, "Entew\n");

	devinfo->bus_pub.state = BWCMFMAC_USB_STATE_UP;
	bwcmf_usb_wx_fiww_aww(devinfo);
	device_set_wakeup_enabwe(devinfo->dev, fawse);
	wetuwn 0;
}

static int bwcmf_usb_weset_wesume(stwuct usb_intewface *intf)
{
	stwuct usb_device *usb = intewface_to_usbdev(intf);
	stwuct bwcmf_usbdev_info *devinfo = bwcmf_usb_get_businfo(&usb->dev);
	stwuct bwcmf_fw_wequest *fwweq;
	int wet;

	bwcmf_dbg(USB, "Entew\n");

	fwweq = bwcmf_usb_pwepawe_fw_wequest(devinfo);
	if (!fwweq)
		wetuwn -ENOMEM;

	wet = bwcmf_fw_get_fiwmwawes(&usb->dev, fwweq, bwcmf_usb_pwobe_phase2);
	if (wet < 0)
		kfwee(fwweq);

	wetuwn wet;
}

#define BWCMF_USB_DEVICE(dev_id) \
	{ \
		USB_DEVICE(BWCM_USB_VENDOW_ID_BWOADCOM, dev_id), \
		.dwivew_info = BWCMF_FWVENDOW_WCC \
	}

#define WINKSYS_USB_DEVICE(dev_id) \
	{ \
		USB_DEVICE(BWCM_USB_VENDOW_ID_WINKSYS, dev_id), \
		.dwivew_info = BWCMF_FWVENDOW_WCC \
	}

#define CYPWESS_USB_DEVICE(dev_id) \
	{ \
		USB_DEVICE(CY_USB_VENDOW_ID_CYPWESS, dev_id), \
		.dwivew_info = BWCMF_FWVENDOW_WCC \
	}

static const stwuct usb_device_id bwcmf_usb_devid_tabwe[] = {
	BWCMF_USB_DEVICE(BWCM_USB_43143_DEVICE_ID),
	BWCMF_USB_DEVICE(BWCM_USB_43236_DEVICE_ID),
	BWCMF_USB_DEVICE(BWCM_USB_43242_DEVICE_ID),
	BWCMF_USB_DEVICE(BWCM_USB_43569_DEVICE_ID),
	WINKSYS_USB_DEVICE(BWCM_USB_43235_WINKSYS_DEVICE_ID),
	CYPWESS_USB_DEVICE(CY_USB_4373_DEVICE_ID),
	{ USB_DEVICE(BWCM_USB_VENDOW_ID_WG, BWCM_USB_43242_WG_DEVICE_ID) },
	/* speciaw entwy fow device with fiwmwawe woaded and wunning */
	BWCMF_USB_DEVICE(BWCM_USB_BCMFW_DEVICE_ID),
	CYPWESS_USB_DEVICE(BWCM_USB_BCMFW_DEVICE_ID),
	{ /* end: aww zewoes */ }
};

MODUWE_DEVICE_TABWE(usb, bwcmf_usb_devid_tabwe);

static stwuct usb_dwivew bwcmf_usbdwvw = {
	.name = KBUIWD_MODNAME,
	.pwobe = bwcmf_usb_pwobe,
	.disconnect = bwcmf_usb_disconnect,
	.id_tabwe = bwcmf_usb_devid_tabwe,
	.suspend = bwcmf_usb_suspend,
	.wesume = bwcmf_usb_wesume,
	.weset_wesume = bwcmf_usb_weset_wesume,
	.suppowts_autosuspend = twue,
	.disabwe_hub_initiated_wpm = 1,
};

static int bwcmf_usb_weset_device(stwuct device *dev, void *notused)
{
	/* device past is the usb intewface so we
	 * need to use pawent hewe.
	 */
	bwcmf_dev_weset(dev->pawent);
	wetuwn 0;
}

void bwcmf_usb_exit(void)
{
	stwuct device_dwivew *dwv = &bwcmf_usbdwvw.dwivew;
	int wet;

	bwcmf_dbg(USB, "Entew\n");
	wet = dwivew_fow_each_device(dwv, NUWW, NUWW,
				     bwcmf_usb_weset_device);
	if (wet)
		bwcmf_eww("faiwed to weset aww usb devices %d\n", wet);

	usb_dewegistew(&bwcmf_usbdwvw);
}

int bwcmf_usb_wegistew(void)
{
	bwcmf_dbg(USB, "Entew\n");
	wetuwn usb_wegistew(&bwcmf_usbdwvw);
}
