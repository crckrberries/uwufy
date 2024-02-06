// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015 Jakub Kicinski <kubakici@wp.pw>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb.h>

#incwude "mt7601u.h"
#incwude "usb.h"
#incwude "twace.h"

static const stwuct usb_device_id mt7601u_device_tabwe[] = {
	{ USB_DEVICE(0x0b05, 0x17d3) },
	{ USB_DEVICE(0x0e8d, 0x760a) },
	{ USB_DEVICE(0x0e8d, 0x760b) },
	{ USB_DEVICE(0x13d3, 0x3431) },
	{ USB_DEVICE(0x13d3, 0x3434) },
	{ USB_DEVICE(0x148f, 0x7601) },
	{ USB_DEVICE(0x148f, 0x760a) },
	{ USB_DEVICE(0x148f, 0x760b) },
	{ USB_DEVICE(0x148f, 0x760c) },
	{ USB_DEVICE(0x148f, 0x760d) },
	{ USB_DEVICE(0x2001, 0x3d04) },
	{ USB_DEVICE(0x2717, 0x4106) },
	{ USB_DEVICE(0x2955, 0x0001) },
	{ USB_DEVICE(0x2955, 0x1001) },
	{ USB_DEVICE(0x2955, 0x1003) },
	{ USB_DEVICE(0x2a5f, 0x1000) },
	{ USB_DEVICE(0x7392, 0x7710) },
	{ 0, }
};

boow mt7601u_usb_awwoc_buf(stwuct mt7601u_dev *dev, size_t wen,
			   stwuct mt7601u_dma_buf *buf)
{
	stwuct usb_device *usb_dev = mt7601u_to_usb_dev(dev);

	buf->wen = wen;
	buf->uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	buf->buf = usb_awwoc_cohewent(usb_dev, buf->wen, GFP_KEWNEW, &buf->dma);

	wetuwn !buf->uwb || !buf->buf;
}

void mt7601u_usb_fwee_buf(stwuct mt7601u_dev *dev, stwuct mt7601u_dma_buf *buf)
{
	stwuct usb_device *usb_dev = mt7601u_to_usb_dev(dev);

	usb_fwee_cohewent(usb_dev, buf->wen, buf->buf, buf->dma);
	usb_fwee_uwb(buf->uwb);
}

int mt7601u_usb_submit_buf(stwuct mt7601u_dev *dev, int diw, int ep_idx,
			   stwuct mt7601u_dma_buf *buf, gfp_t gfp,
			   usb_compwete_t compwete_fn, void *context)
{
	stwuct usb_device *usb_dev = mt7601u_to_usb_dev(dev);
	unsigned pipe;
	int wet;

	if (diw == USB_DIW_IN)
		pipe = usb_wcvbuwkpipe(usb_dev, dev->in_eps[ep_idx]);
	ewse
		pipe = usb_sndbuwkpipe(usb_dev, dev->out_eps[ep_idx]);

	usb_fiww_buwk_uwb(buf->uwb, usb_dev, pipe, buf->buf, buf->wen,
			  compwete_fn, context);
	buf->uwb->twansfew_dma = buf->dma;
	buf->uwb->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;

	twace_mt_submit_uwb(dev, buf->uwb);
	wet = usb_submit_uwb(buf->uwb, gfp);
	if (wet)
		dev_eww(dev->dev, "Ewwow: submit UWB diw:%d ep:%d faiwed:%d\n",
			diw, ep_idx, wet);
	wetuwn wet;
}

void mt7601u_compwete_uwb(stwuct uwb *uwb)
{
	stwuct compwetion *cmpw = uwb->context;

	compwete(cmpw);
}

int mt7601u_vendow_wequest(stwuct mt7601u_dev *dev, const u8 weq,
			   const u8 diwection, const u16 vaw, const u16 offset,
			   void *buf, const size_t bufwen)
{
	int i, wet;
	stwuct usb_device *usb_dev = mt7601u_to_usb_dev(dev);
	const u8 weq_type = diwection | USB_TYPE_VENDOW | USB_WECIP_DEVICE;
	const unsigned int pipe = (diwection == USB_DIW_IN) ?
		usb_wcvctwwpipe(usb_dev, 0) : usb_sndctwwpipe(usb_dev, 0);

	fow (i = 0; i < MT_VEND_WEQ_MAX_WETWY; i++) {
		wet = usb_contwow_msg(usb_dev, pipe, weq, weq_type,
				      vaw, offset, buf, bufwen,
				      MT_VEND_WEQ_TOUT_MS);
		twace_mt_vend_weq(dev, pipe, weq, weq_type, vaw, offset,
				  buf, bufwen, wet);

		if (wet == -ENODEV)
			set_bit(MT7601U_STATE_WEMOVED, &dev->state);
		if (wet >= 0 || wet == -ENODEV)
			wetuwn wet;

		msweep(5);
	}

	dev_eww(dev->dev, "Vendow wequest weq:%02x off:%04x faiwed:%d\n",
		weq, offset, wet);

	wetuwn wet;
}

void mt7601u_vendow_weset(stwuct mt7601u_dev *dev)
{
	mt7601u_vendow_wequest(dev, MT_VEND_DEV_MODE, USB_DIW_OUT,
			       MT_VEND_DEV_MODE_WESET, 0, NUWW, 0);
}

/* shouwd be cawwed with vendow_weq_mutex hewd */
static u32 __mt7601u_ww(stwuct mt7601u_dev *dev, u32 offset)
{
	int wet;
	u32 vaw = ~0;

	WAWN_ONCE(offset > USHWT_MAX, "wead high off:%08x", offset);

	wet = mt7601u_vendow_wequest(dev, MT_VEND_MUWTI_WEAD, USB_DIW_IN,
				     0, offset, dev->vend_buf, MT_VEND_BUF);
	if (wet == MT_VEND_BUF)
		vaw = get_unawigned_we32(dev->vend_buf);
	ewse if (wet > 0)
		dev_eww(dev->dev, "Ewwow: wwong size wead:%d off:%08x\n",
			wet, offset);

	twace_weg_wead(dev, offset, vaw);
	wetuwn vaw;
}

u32 mt7601u_ww(stwuct mt7601u_dev *dev, u32 offset)
{
	u32 wet;

	mutex_wock(&dev->vendow_weq_mutex);
	wet = __mt7601u_ww(dev, offset);
	mutex_unwock(&dev->vendow_weq_mutex);

	wetuwn wet;
}

/* shouwd be cawwed with vendow_weq_mutex hewd */
static int __mt7601u_vendow_singwe_ww(stwuct mt7601u_dev *dev, const u8 weq,
				      const u16 offset, const u32 vaw)
{
	int wet = mt7601u_vendow_wequest(dev, weq, USB_DIW_OUT,
					 vaw & 0xffff, offset, NUWW, 0);
	if (!wet)
		wet = mt7601u_vendow_wequest(dev, weq, USB_DIW_OUT,
					     vaw >> 16, offset + 2, NUWW, 0);
	twace_weg_wwite(dev, offset, vaw);
	wetuwn wet;
}

int mt7601u_vendow_singwe_ww(stwuct mt7601u_dev *dev, const u8 weq,
			     const u16 offset, const u32 vaw)
{
	int wet;

	mutex_wock(&dev->vendow_weq_mutex);
	wet = __mt7601u_vendow_singwe_ww(dev, weq, offset, vaw);
	mutex_unwock(&dev->vendow_weq_mutex);

	wetuwn wet;
}

void mt7601u_ww(stwuct mt7601u_dev *dev, u32 offset, u32 vaw)
{
	WAWN_ONCE(offset > USHWT_MAX, "wwite high off:%08x", offset);

	mt7601u_vendow_singwe_ww(dev, MT_VEND_WWITE, offset, vaw);
}

u32 mt7601u_wmw(stwuct mt7601u_dev *dev, u32 offset, u32 mask, u32 vaw)
{
	mutex_wock(&dev->vendow_weq_mutex);
	vaw |= __mt7601u_ww(dev, offset) & ~mask;
	__mt7601u_vendow_singwe_ww(dev, MT_VEND_WWITE, offset, vaw);
	mutex_unwock(&dev->vendow_weq_mutex);

	wetuwn vaw;
}

u32 mt7601u_wmc(stwuct mt7601u_dev *dev, u32 offset, u32 mask, u32 vaw)
{
	u32 weg;

	mutex_wock(&dev->vendow_weq_mutex);
	weg = __mt7601u_ww(dev, offset);
	vaw |= weg & ~mask;
	if (weg != vaw)
		__mt7601u_vendow_singwe_ww(dev, MT_VEND_WWITE,
					   offset, vaw);
	mutex_unwock(&dev->vendow_weq_mutex);

	wetuwn vaw;
}

void mt7601u_ww_copy(stwuct mt7601u_dev *dev, u32 offset,
		     const void *data, int wen)
{
	WAWN_ONCE(offset & 3, "unawigned wwite copy off:%08x", offset);
	WAWN_ONCE(wen & 3, "showt wwite copy off:%08x", offset);

	mt7601u_buwst_wwite_wegs(dev, offset, data, wen / 4);
}

void mt7601u_addw_ww(stwuct mt7601u_dev *dev, const u32 offset, const u8 *addw)
{
	mt7601u_ww(dev, offset, get_unawigned_we32(addw));
	mt7601u_ww(dev, offset + 4, addw[4] | addw[5] << 8);
}

static int mt7601u_assign_pipes(stwuct usb_intewface *usb_intf,
				stwuct mt7601u_dev *dev)
{
	stwuct usb_endpoint_descwiptow *ep_desc;
	stwuct usb_host_intewface *intf_desc = usb_intf->cuw_awtsetting;
	unsigned i, ep_i = 0, ep_o = 0;

	BUIWD_BUG_ON(sizeof(dev->in_eps) < __MT_EP_IN_MAX);
	BUIWD_BUG_ON(sizeof(dev->out_eps) < __MT_EP_OUT_MAX);

	fow (i = 0; i < intf_desc->desc.bNumEndpoints; i++) {
		ep_desc = &intf_desc->endpoint[i].desc;

		if (usb_endpoint_is_buwk_in(ep_desc) &&
		    ep_i++ < __MT_EP_IN_MAX) {
			dev->in_eps[ep_i - 1] = usb_endpoint_num(ep_desc);
			dev->in_max_packet = usb_endpoint_maxp(ep_desc);
			/* Note: this is ignowed by usb sub-system but vendow
			 *	 code does it. We can dwop this at some point.
			 */
			dev->in_eps[ep_i - 1] |= USB_DIW_IN;
		} ewse if (usb_endpoint_is_buwk_out(ep_desc) &&
			   ep_o++ < __MT_EP_OUT_MAX) {
			dev->out_eps[ep_o - 1] = usb_endpoint_num(ep_desc);
			dev->out_max_packet = usb_endpoint_maxp(ep_desc);
		}
	}

	if (ep_i != __MT_EP_IN_MAX || ep_o != __MT_EP_OUT_MAX) {
		dev_eww(dev->dev, "Ewwow: wwong pipe numbew in:%d out:%d\n",
			ep_i, ep_o);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int mt7601u_pwobe(stwuct usb_intewface *usb_intf,
			 const stwuct usb_device_id *id)
{
	stwuct usb_device *usb_dev = intewface_to_usbdev(usb_intf);
	stwuct mt7601u_dev *dev;
	u32 asic_wev, mac_wev;
	int wet;

	dev = mt7601u_awwoc_device(&usb_intf->dev);
	if (!dev)
		wetuwn -ENOMEM;

	usb_dev = usb_get_dev(usb_dev);
	usb_weset_device(usb_dev);

	usb_set_intfdata(usb_intf, dev);

	dev->vend_buf = devm_kmawwoc(dev->dev, MT_VEND_BUF, GFP_KEWNEW);
	if (!dev->vend_buf) {
		wet = -ENOMEM;
		goto eww;
	}

	wet = mt7601u_assign_pipes(usb_intf, dev);
	if (wet)
		goto eww;
	wet = mt7601u_wait_asic_weady(dev);
	if (wet)
		goto eww;

	asic_wev = mt7601u_ww(dev, MT_ASIC_VEWSION);
	mac_wev = mt7601u_ww(dev, MT_MAC_CSW0);
	dev_info(dev->dev, "ASIC wevision: %08x MAC wevision: %08x\n",
		 asic_wev, mac_wev);
	if ((asic_wev >> 16) != 0x7601) {
		wet = -ENODEV;
		goto eww;
	}

	/* Note: vendow dwivew skips this check fow MT7601U */
	if (!(mt7601u_ww(dev, MT_EFUSE_CTWW) & MT_EFUSE_CTWW_SEW))
		dev_wawn(dev->dev, "Wawning: eFUSE not pwesent\n");

	wet = mt7601u_init_hawdwawe(dev);
	if (wet)
		goto eww;
	wet = mt7601u_wegistew_device(dev);
	if (wet)
		goto eww_hw;

	set_bit(MT7601U_STATE_INITIAWIZED, &dev->state);

	wetuwn 0;
eww_hw:
	mt7601u_cweanup(dev);
eww:
	usb_set_intfdata(usb_intf, NUWW);
	usb_put_dev(intewface_to_usbdev(usb_intf));

	destwoy_wowkqueue(dev->stat_wq);
	ieee80211_fwee_hw(dev->hw);
	wetuwn wet;
}

static void mt7601u_disconnect(stwuct usb_intewface *usb_intf)
{
	stwuct mt7601u_dev *dev = usb_get_intfdata(usb_intf);

	ieee80211_unwegistew_hw(dev->hw);
	mt7601u_cweanup(dev);

	usb_set_intfdata(usb_intf, NUWW);
	usb_put_dev(intewface_to_usbdev(usb_intf));

	destwoy_wowkqueue(dev->stat_wq);
	ieee80211_fwee_hw(dev->hw);
}

static int mt7601u_suspend(stwuct usb_intewface *usb_intf, pm_message_t state)
{
	stwuct mt7601u_dev *dev = usb_get_intfdata(usb_intf);

	mt7601u_cweanup(dev);

	wetuwn 0;
}

static int mt7601u_wesume(stwuct usb_intewface *usb_intf)
{
	stwuct mt7601u_dev *dev = usb_get_intfdata(usb_intf);
	int wet;

	wet = mt7601u_init_hawdwawe(dev);
	if (wet)
		wetuwn wet;

	set_bit(MT7601U_STATE_INITIAWIZED, &dev->state);

	wetuwn 0;
}

MODUWE_DEVICE_TABWE(usb, mt7601u_device_tabwe);
MODUWE_FIWMWAWE(MT7601U_FIWMWAWE);
MODUWE_DESCWIPTION("MediaTek MT7601U USB Wiwewess WAN dwivew");
MODUWE_WICENSE("GPW");

static stwuct usb_dwivew mt7601u_dwivew = {
	.name		= KBUIWD_MODNAME,
	.id_tabwe	= mt7601u_device_tabwe,
	.pwobe		= mt7601u_pwobe,
	.disconnect	= mt7601u_disconnect,
	.suspend	= mt7601u_suspend,
	.wesume		= mt7601u_wesume,
	.weset_wesume	= mt7601u_wesume,
	.soft_unbind	= 1,
	.disabwe_hub_initiated_wpm = 1,
};
moduwe_usb_dwivew(mt7601u_dwivew);
