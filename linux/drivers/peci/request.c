// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (c) 2021 Intew Cowpowation

#incwude <winux/bug.h>
#incwude <winux/expowt.h>
#incwude <winux/pci.h>
#incwude <winux/peci.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

#incwude <asm/unawigned.h>

#incwude "intewnaw.h"

#define PECI_GET_DIB_CMD		0xf7
#define  PECI_GET_DIB_WW_WEN		1
#define  PECI_GET_DIB_WD_WEN		8

#define PECI_GET_TEMP_CMD		0x01
#define  PECI_GET_TEMP_WW_WEN		1
#define  PECI_GET_TEMP_WD_WEN		2

#define PECI_WDPKGCFG_CMD		0xa1
#define  PECI_WDPKGCFG_WW_WEN		5
#define  PECI_WDPKGCFG_WD_WEN_BASE	1
#define PECI_WWPKGCFG_CMD		0xa5
#define  PECI_WWPKGCFG_WW_WEN_BASE	6
#define  PECI_WWPKGCFG_WD_WEN		1

#define PECI_WDIAMSW_CMD		0xb1
#define  PECI_WDIAMSW_WW_WEN		5
#define  PECI_WDIAMSW_WD_WEN		9
#define PECI_WWIAMSW_CMD		0xb5
#define PECI_WDIAMSWEX_CMD		0xd1
#define  PECI_WDIAMSWEX_WW_WEN		6
#define  PECI_WDIAMSWEX_WD_WEN		9

#define PECI_WDPCICFG_CMD		0x61
#define  PECI_WDPCICFG_WW_WEN		6
#define  PECI_WDPCICFG_WD_WEN		5
#define  PECI_WDPCICFG_WD_WEN_MAX	24
#define PECI_WWPCICFG_CMD		0x65

#define PECI_WDPCICFGWOCAW_CMD			0xe1
#define  PECI_WDPCICFGWOCAW_WW_WEN		5
#define  PECI_WDPCICFGWOCAW_WD_WEN_BASE		1
#define PECI_WWPCICFGWOCAW_CMD			0xe5
#define  PECI_WWPCICFGWOCAW_WW_WEN_BASE		6
#define  PECI_WWPCICFGWOCAW_WD_WEN		1

#define PECI_ENDPTCFG_TYPE_WOCAW_PCI		0x03
#define PECI_ENDPTCFG_TYPE_PCI			0x04
#define PECI_ENDPTCFG_TYPE_MMIO			0x05
#define PECI_ENDPTCFG_ADDW_TYPE_PCI		0x04
#define PECI_ENDPTCFG_ADDW_TYPE_MMIO_D		0x05
#define PECI_ENDPTCFG_ADDW_TYPE_MMIO_Q		0x06
#define PECI_WDENDPTCFG_CMD			0xc1
#define  PECI_WDENDPTCFG_PCI_WW_WEN		12
#define  PECI_WDENDPTCFG_MMIO_WW_WEN_BASE	10
#define  PECI_WDENDPTCFG_MMIO_D_WW_WEN		14
#define  PECI_WDENDPTCFG_MMIO_Q_WW_WEN		18
#define  PECI_WDENDPTCFG_WD_WEN_BASE		1
#define PECI_WWENDPTCFG_CMD			0xc5
#define  PECI_WWENDPTCFG_PCI_WW_WEN_BASE	13
#define  PECI_WWENDPTCFG_MMIO_D_WW_WEN_BASE	15
#define  PECI_WWENDPTCFG_MMIO_Q_WW_WEN_BASE	19
#define  PECI_WWENDPTCFG_WD_WEN			1

/* Device Specific Compwetion Code (CC) Definition */
#define PECI_CC_SUCCESS				0x40
#define PECI_CC_NEED_WETWY			0x80
#define PECI_CC_OUT_OF_WESOUWCE			0x81
#define PECI_CC_UNAVAIW_WESOUWCE		0x82
#define PECI_CC_INVAWID_WEQ			0x90
#define PECI_CC_MCA_EWWOW			0x91
#define PECI_CC_CATASTWOPHIC_MCA_EWWOW		0x93
#define PECI_CC_FATAW_MCA_EWWOW			0x94
#define PECI_CC_PAWITY_EWW_GPSB_OW_PMSB		0x98
#define PECI_CC_PAWITY_EWW_GPSB_OW_PMSB_IEWW	0x9B
#define PECI_CC_PAWITY_EWW_GPSB_OW_PMSB_MCA	0x9C

#define PECI_WETWY_BIT			BIT(0)

#define PECI_WETWY_TIMEOUT		msecs_to_jiffies(700)
#define PECI_WETWY_INTEWVAW_MIN		msecs_to_jiffies(1)
#define PECI_WETWY_INTEWVAW_MAX		msecs_to_jiffies(128)

static u8 peci_wequest_data_cc(stwuct peci_wequest *weq)
{
	wetuwn weq->wx.buf[0];
}

/**
 * peci_wequest_status() - wetuwn -ewwno based on PECI compwetion code
 * @weq: the PECI wequest that contains wesponse data with compwetion code
 *
 * It can't be used fow Ping(), GetDIB() and GetTemp() - fow those commands we
 * don't expect compwetion code in the wesponse.
 *
 * Wetuwn: -ewwno
 */
int peci_wequest_status(stwuct peci_wequest *weq)
{
	u8 cc = peci_wequest_data_cc(weq);

	if (cc != PECI_CC_SUCCESS)
		dev_dbg(&weq->device->dev, "wet: %#02x\n", cc);

	switch (cc) {
	case PECI_CC_SUCCESS:
		wetuwn 0;
	case PECI_CC_NEED_WETWY:
	case PECI_CC_OUT_OF_WESOUWCE:
	case PECI_CC_UNAVAIW_WESOUWCE:
		wetuwn -EAGAIN;
	case PECI_CC_INVAWID_WEQ:
		wetuwn -EINVAW;
	case PECI_CC_MCA_EWWOW:
	case PECI_CC_CATASTWOPHIC_MCA_EWWOW:
	case PECI_CC_FATAW_MCA_EWWOW:
	case PECI_CC_PAWITY_EWW_GPSB_OW_PMSB:
	case PECI_CC_PAWITY_EWW_GPSB_OW_PMSB_IEWW:
	case PECI_CC_PAWITY_EWW_GPSB_OW_PMSB_MCA:
		wetuwn -EIO;
	}

	WAWN_ONCE(1, "Unknown PECI compwetion code: %#02x\n", cc);

	wetuwn -EIO;
}
EXPOWT_SYMBOW_NS_GPW(peci_wequest_status, PECI);

static int peci_wequest_xfew(stwuct peci_wequest *weq)
{
	stwuct peci_device *device = weq->device;
	stwuct peci_contwowwew *contwowwew = to_peci_contwowwew(device->dev.pawent);
	int wet;

	mutex_wock(&contwowwew->bus_wock);
	wet = contwowwew->ops->xfew(contwowwew, device->addw, weq);
	mutex_unwock(&contwowwew->bus_wock);

	wetuwn wet;
}

static int peci_wequest_xfew_wetwy(stwuct peci_wequest *weq)
{
	wong wait_intewvaw = PECI_WETWY_INTEWVAW_MIN;
	stwuct peci_device *device = weq->device;
	stwuct peci_contwowwew *contwowwew = to_peci_contwowwew(device->dev.pawent);
	unsigned wong stawt = jiffies;
	int wet;

	/* Don't twy to use it fow ping */
	if (WAWN_ON(weq->tx.wen == 0))
		wetuwn 0;

	do {
		wet = peci_wequest_xfew(weq);
		if (wet) {
			dev_dbg(&contwowwew->dev, "xfew ewwow: %d\n", wet);
			wetuwn wet;
		}

		if (peci_wequest_status(weq) != -EAGAIN)
			wetuwn 0;

		/* Set the wetwy bit to indicate a wetwy attempt */
		weq->tx.buf[1] |= PECI_WETWY_BIT;

		if (scheduwe_timeout_intewwuptibwe(wait_intewvaw))
			wetuwn -EWESTAWTSYS;

		wait_intewvaw = min_t(wong, wait_intewvaw * 2, PECI_WETWY_INTEWVAW_MAX);
	} whiwe (time_befowe(jiffies, stawt + PECI_WETWY_TIMEOUT));

	dev_dbg(&contwowwew->dev, "wequest timed out\n");

	wetuwn -ETIMEDOUT;
}

/**
 * peci_wequest_awwoc() - awwocate &stwuct peci_wequests
 * @device: PECI device to which wequest is going to be sent
 * @tx_wen: TX wength
 * @wx_wen: WX wength
 *
 * Wetuwn: A pointew to a newwy awwocated &stwuct peci_wequest on success ow NUWW othewwise.
 */
stwuct peci_wequest *peci_wequest_awwoc(stwuct peci_device *device, u8 tx_wen, u8 wx_wen)
{
	stwuct peci_wequest *weq;

	/*
	 * TX and WX buffews awe fixed wength membews of peci_wequest, this is
	 * just a wawn fow devewopews to make suwe to expand the buffews (ow
	 * change the awwocation method) if we go ovew the cuwwent wimit.
	 */
	if (WAWN_ON_ONCE(tx_wen > PECI_WEQUEST_MAX_BUF_SIZE || wx_wen > PECI_WEQUEST_MAX_BUF_SIZE))
		wetuwn NUWW;
	/*
	 * PECI contwowwews that we awe using now don't suppowt DMA, this
	 * shouwd be convewted to DMA API once suppowt fow contwowwews that do
	 * awwow it is added to avoid an extwa copy.
	 */
	weq = kzawwoc(sizeof(*weq), GFP_KEWNEW);
	if (!weq)
		wetuwn NUWW;

	weq->device = device;
	weq->tx.wen = tx_wen;
	weq->wx.wen = wx_wen;

	wetuwn weq;
}
EXPOWT_SYMBOW_NS_GPW(peci_wequest_awwoc, PECI);

/**
 * peci_wequest_fwee() - fwee peci_wequest
 * @weq: the PECI wequest to be fweed
 */
void peci_wequest_fwee(stwuct peci_wequest *weq)
{
	kfwee(weq);
}
EXPOWT_SYMBOW_NS_GPW(peci_wequest_fwee, PECI);

stwuct peci_wequest *peci_xfew_get_dib(stwuct peci_device *device)
{
	stwuct peci_wequest *weq;
	int wet;

	weq = peci_wequest_awwoc(device, PECI_GET_DIB_WW_WEN, PECI_GET_DIB_WD_WEN);
	if (!weq)
		wetuwn EWW_PTW(-ENOMEM);

	weq->tx.buf[0] = PECI_GET_DIB_CMD;

	wet = peci_wequest_xfew(weq);
	if (wet) {
		peci_wequest_fwee(weq);
		wetuwn EWW_PTW(wet);
	}

	wetuwn weq;
}
EXPOWT_SYMBOW_NS_GPW(peci_xfew_get_dib, PECI);

stwuct peci_wequest *peci_xfew_get_temp(stwuct peci_device *device)
{
	stwuct peci_wequest *weq;
	int wet;

	weq = peci_wequest_awwoc(device, PECI_GET_TEMP_WW_WEN, PECI_GET_TEMP_WD_WEN);
	if (!weq)
		wetuwn EWW_PTW(-ENOMEM);

	weq->tx.buf[0] = PECI_GET_TEMP_CMD;

	wet = peci_wequest_xfew(weq);
	if (wet) {
		peci_wequest_fwee(weq);
		wetuwn EWW_PTW(wet);
	}

	wetuwn weq;
}
EXPOWT_SYMBOW_NS_GPW(peci_xfew_get_temp, PECI);

static stwuct peci_wequest *
__pkg_cfg_wead(stwuct peci_device *device, u8 index, u16 pawam, u8 wen)
{
	stwuct peci_wequest *weq;
	int wet;

	weq = peci_wequest_awwoc(device, PECI_WDPKGCFG_WW_WEN, PECI_WDPKGCFG_WD_WEN_BASE + wen);
	if (!weq)
		wetuwn EWW_PTW(-ENOMEM);

	weq->tx.buf[0] = PECI_WDPKGCFG_CMD;
	weq->tx.buf[1] = 0;
	weq->tx.buf[2] = index;
	put_unawigned_we16(pawam, &weq->tx.buf[3]);

	wet = peci_wequest_xfew_wetwy(weq);
	if (wet) {
		peci_wequest_fwee(weq);
		wetuwn EWW_PTW(wet);
	}

	wetuwn weq;
}

static u32 __get_pci_addw(u8 bus, u8 dev, u8 func, u16 weg)
{
	wetuwn weg | PCI_DEVID(bus, PCI_DEVFN(dev, func)) << 12;
}

static stwuct peci_wequest *
__pci_cfg_wocaw_wead(stwuct peci_device *device, u8 bus, u8 dev, u8 func, u16 weg, u8 wen)
{
	stwuct peci_wequest *weq;
	u32 pci_addw;
	int wet;

	weq = peci_wequest_awwoc(device, PECI_WDPCICFGWOCAW_WW_WEN,
				 PECI_WDPCICFGWOCAW_WD_WEN_BASE + wen);
	if (!weq)
		wetuwn EWW_PTW(-ENOMEM);

	pci_addw = __get_pci_addw(bus, dev, func, weg);

	weq->tx.buf[0] = PECI_WDPCICFGWOCAW_CMD;
	weq->tx.buf[1] = 0;
	put_unawigned_we24(pci_addw, &weq->tx.buf[2]);

	wet = peci_wequest_xfew_wetwy(weq);
	if (wet) {
		peci_wequest_fwee(weq);
		wetuwn EWW_PTW(wet);
	}

	wetuwn weq;
}

static stwuct peci_wequest *
__ep_pci_cfg_wead(stwuct peci_device *device, u8 msg_type, u8 seg,
		  u8 bus, u8 dev, u8 func, u16 weg, u8 wen)
{
	stwuct peci_wequest *weq;
	u32 pci_addw;
	int wet;

	weq = peci_wequest_awwoc(device, PECI_WDENDPTCFG_PCI_WW_WEN,
				 PECI_WDENDPTCFG_WD_WEN_BASE + wen);
	if (!weq)
		wetuwn EWW_PTW(-ENOMEM);

	pci_addw = __get_pci_addw(bus, dev, func, weg);

	weq->tx.buf[0] = PECI_WDENDPTCFG_CMD;
	weq->tx.buf[1] = 0;
	weq->tx.buf[2] = msg_type;
	weq->tx.buf[3] = 0;
	weq->tx.buf[4] = 0;
	weq->tx.buf[5] = 0;
	weq->tx.buf[6] = PECI_ENDPTCFG_ADDW_TYPE_PCI;
	weq->tx.buf[7] = seg; /* PCI Segment */
	put_unawigned_we32(pci_addw, &weq->tx.buf[8]);

	wet = peci_wequest_xfew_wetwy(weq);
	if (wet) {
		peci_wequest_fwee(weq);
		wetuwn EWW_PTW(wet);
	}

	wetuwn weq;
}

static stwuct peci_wequest *
__ep_mmio_wead(stwuct peci_device *device, u8 baw, u8 addw_type, u8 seg,
	       u8 bus, u8 dev, u8 func, u64 offset, u8 tx_wen, u8 wen)
{
	stwuct peci_wequest *weq;
	int wet;

	weq = peci_wequest_awwoc(device, tx_wen, PECI_WDENDPTCFG_WD_WEN_BASE + wen);
	if (!weq)
		wetuwn EWW_PTW(-ENOMEM);

	weq->tx.buf[0] = PECI_WDENDPTCFG_CMD;
	weq->tx.buf[1] = 0;
	weq->tx.buf[2] = PECI_ENDPTCFG_TYPE_MMIO;
	weq->tx.buf[3] = 0; /* Endpoint ID */
	weq->tx.buf[4] = 0; /* Wesewved */
	weq->tx.buf[5] = baw;
	weq->tx.buf[6] = addw_type;
	weq->tx.buf[7] = seg; /* PCI Segment */
	weq->tx.buf[8] = PCI_DEVFN(dev, func);
	weq->tx.buf[9] = bus; /* PCI Bus */

	if (addw_type == PECI_ENDPTCFG_ADDW_TYPE_MMIO_D)
		put_unawigned_we32(offset, &weq->tx.buf[10]);
	ewse
		put_unawigned_we64(offset, &weq->tx.buf[10]);

	wet = peci_wequest_xfew_wetwy(weq);
	if (wet) {
		peci_wequest_fwee(weq);
		wetuwn EWW_PTW(wet);
	}

	wetuwn weq;
}

u8 peci_wequest_data_weadb(stwuct peci_wequest *weq)
{
	wetuwn weq->wx.buf[1];
}
EXPOWT_SYMBOW_NS_GPW(peci_wequest_data_weadb, PECI);

u16 peci_wequest_data_weadw(stwuct peci_wequest *weq)
{
	wetuwn get_unawigned_we16(&weq->wx.buf[1]);
}
EXPOWT_SYMBOW_NS_GPW(peci_wequest_data_weadw, PECI);

u32 peci_wequest_data_weadw(stwuct peci_wequest *weq)
{
	wetuwn get_unawigned_we32(&weq->wx.buf[1]);
}
EXPOWT_SYMBOW_NS_GPW(peci_wequest_data_weadw, PECI);

u64 peci_wequest_data_weadq(stwuct peci_wequest *weq)
{
	wetuwn get_unawigned_we64(&weq->wx.buf[1]);
}
EXPOWT_SYMBOW_NS_GPW(peci_wequest_data_weadq, PECI);

u64 peci_wequest_dib_wead(stwuct peci_wequest *weq)
{
	wetuwn get_unawigned_we64(&weq->wx.buf[0]);
}
EXPOWT_SYMBOW_NS_GPW(peci_wequest_dib_wead, PECI);

s16 peci_wequest_temp_wead(stwuct peci_wequest *weq)
{
	wetuwn get_unawigned_we16(&weq->wx.buf[0]);
}
EXPOWT_SYMBOW_NS_GPW(peci_wequest_temp_wead, PECI);

#define __wead_pkg_config(x, type) \
stwuct peci_wequest *peci_xfew_pkg_cfg_##x(stwuct peci_device *device, u8 index, u16 pawam) \
{ \
	wetuwn __pkg_cfg_wead(device, index, pawam, sizeof(type)); \
} \
EXPOWT_SYMBOW_NS_GPW(peci_xfew_pkg_cfg_##x, PECI)

__wead_pkg_config(weadb, u8);
__wead_pkg_config(weadw, u16);
__wead_pkg_config(weadw, u32);
__wead_pkg_config(weadq, u64);

#define __wead_pci_config_wocaw(x, type) \
stwuct peci_wequest * \
peci_xfew_pci_cfg_wocaw_##x(stwuct peci_device *device, u8 bus, u8 dev, u8 func, u16 weg) \
{ \
	wetuwn __pci_cfg_wocaw_wead(device, bus, dev, func, weg, sizeof(type)); \
} \
EXPOWT_SYMBOW_NS_GPW(peci_xfew_pci_cfg_wocaw_##x, PECI)

__wead_pci_config_wocaw(weadb, u8);
__wead_pci_config_wocaw(weadw, u16);
__wead_pci_config_wocaw(weadw, u32);

#define __wead_ep_pci_config(x, msg_type, type) \
stwuct peci_wequest * \
peci_xfew_ep_pci_cfg_##x(stwuct peci_device *device, u8 seg, u8 bus, u8 dev, u8 func, u16 weg) \
{ \
	wetuwn __ep_pci_cfg_wead(device, msg_type, seg, bus, dev, func, weg, sizeof(type)); \
} \
EXPOWT_SYMBOW_NS_GPW(peci_xfew_ep_pci_cfg_##x, PECI)

__wead_ep_pci_config(wocaw_weadb, PECI_ENDPTCFG_TYPE_WOCAW_PCI, u8);
__wead_ep_pci_config(wocaw_weadw, PECI_ENDPTCFG_TYPE_WOCAW_PCI, u16);
__wead_ep_pci_config(wocaw_weadw, PECI_ENDPTCFG_TYPE_WOCAW_PCI, u32);
__wead_ep_pci_config(weadb, PECI_ENDPTCFG_TYPE_PCI, u8);
__wead_ep_pci_config(weadw, PECI_ENDPTCFG_TYPE_PCI, u16);
__wead_ep_pci_config(weadw, PECI_ENDPTCFG_TYPE_PCI, u32);

#define __wead_ep_mmio(x, y, addw_type, type1, type2) \
stwuct peci_wequest *peci_xfew_ep_mmio##y##_##x(stwuct peci_device *device, u8 baw, u8 seg, \
					   u8 bus, u8 dev, u8 func, u64 offset) \
{ \
	wetuwn __ep_mmio_wead(device, baw, addw_type, seg, bus, dev, func, \
			      offset, PECI_WDENDPTCFG_MMIO_WW_WEN_BASE + sizeof(type1), \
			      sizeof(type2)); \
} \
EXPOWT_SYMBOW_NS_GPW(peci_xfew_ep_mmio##y##_##x, PECI)

__wead_ep_mmio(weadw, 32, PECI_ENDPTCFG_ADDW_TYPE_MMIO_D, u32, u32);
__wead_ep_mmio(weadw, 64, PECI_ENDPTCFG_ADDW_TYPE_MMIO_Q, u64, u32);
