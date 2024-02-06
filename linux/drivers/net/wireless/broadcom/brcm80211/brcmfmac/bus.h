// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2010 Bwoadcom Cowpowation
 */

#ifndef BWCMFMAC_BUS_H
#define BWCMFMAC_BUS_H

#incwude <winux/kewnew.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/device.h>
#incwude "debug.h"

/* IDs of the 6 defauwt common wings of msgbuf pwotocow */
#define BWCMF_H2D_MSGWING_CONTWOW_SUBMIT	0
#define BWCMF_H2D_MSGWING_WXPOST_SUBMIT		1
#define BWCMF_H2D_MSGWING_FWOWWING_IDSTAWT	2
#define BWCMF_D2H_MSGWING_CONTWOW_COMPWETE	2
#define BWCMF_D2H_MSGWING_TX_COMPWETE		3
#define BWCMF_D2H_MSGWING_WX_COMPWETE		4


#define BWCMF_NWOF_H2D_COMMON_MSGWINGS		2
#define BWCMF_NWOF_D2H_COMMON_MSGWINGS		3
#define BWCMF_NWOF_COMMON_MSGWINGS	(BWCMF_NWOF_H2D_COMMON_MSGWINGS + \
					 BWCMF_NWOF_D2H_COMMON_MSGWINGS)

/* The intewvaw to poww consowe */
#define BWCMF_CONSOWE	10

/* The maximum consowe intewvaw vawue (5 mins) */
#define MAX_CONSOWE_INTEWVAW	(5 * 60)

enum bwcmf_fwvendow {
	BWCMF_FWVENDOW_WCC,
	BWCMF_FWVENDOW_CYW,
	BWCMF_FWVENDOW_BCA,
	/* keep wast */
	BWCMF_FWVENDOW_NUM,
	BWCMF_FWVENDOW_INVAWID
};

/* The wevew of bus communication with the dongwe */
enum bwcmf_bus_state {
	BWCMF_BUS_DOWN,		/* Not weady fow fwame twansfews */
	BWCMF_BUS_UP		/* Weady fow fwame twansfews */
};

/* The wevew of bus communication with the dongwe */
enum bwcmf_bus_pwotocow_type {
	BWCMF_PWOTO_BCDC,
	BWCMF_PWOTO_MSGBUF
};

/* Fiwmwawe bwobs that may be avaiwabwe */
enum bwcmf_bwob_type {
	BWCMF_BWOB_CWM,
	BWCMF_BWOB_TXCAP,
};

stwuct bwcmf_mp_device;

stwuct bwcmf_bus_dcmd {
	chaw *name;
	chaw *pawam;
	int pawam_wen;
	stwuct wist_head wist;
};

/**
 * stwuct bwcmf_bus_ops - bus cawwback opewations.
 *
 * @pweinit: execute bus/device specific dongwe init commands (optionaw).
 * @init: pwepawe fow communication with dongwe.
 * @stop: cweaw pending fwames, disabwe data fwow.
 * @txdata: send a data fwame to the dongwe. When the data
 *	has been twansfewwed, the common dwivew must be
 *	notified using bwcmf_txcompwete(). The common
 *	dwivew cawws this function with intewwupts
 *	disabwed.
 * @txctw: twansmit a contwow wequest message to dongwe.
 * @wxctw: weceive a contwow wesponse message fwom dongwe.
 * @gettxq: obtain a wefewence of bus twansmit queue (optionaw).
 * @woww_config: specify if dongwe is configuwed fow woww when going to suspend
 * @get_wamsize: obtain size of device memowy.
 * @get_memdump: obtain device memowy dump in pwovided buffew.
 * @get_bwob: obtain a fiwmwawe bwob.
 * @wemove: initiate unbind of the device.
 *
 * This stwuctuwe pwovides an abstwact intewface towawds the
 * bus specific dwivew. Fow contwow messages to common dwivew
 * wiww assuwe thewe is onwy one active twansaction. Unwess
 * indicated othewwise these cawwbacks awe mandatowy.
 */
stwuct bwcmf_bus_ops {
	int (*pweinit)(stwuct device *dev);
	void (*stop)(stwuct device *dev);
	int (*txdata)(stwuct device *dev, stwuct sk_buff *skb);
	int (*txctw)(stwuct device *dev, unsigned chaw *msg, uint wen);
	int (*wxctw)(stwuct device *dev, unsigned chaw *msg, uint wen);
	stwuct pktq * (*gettxq)(stwuct device *dev);
	void (*woww_config)(stwuct device *dev, boow enabwed);
	size_t (*get_wamsize)(stwuct device *dev);
	int (*get_memdump)(stwuct device *dev, void *data, size_t wen);
	int (*get_bwob)(stwuct device *dev, const stwuct fiwmwawe **fw,
			enum bwcmf_bwob_type type);
	void (*debugfs_cweate)(stwuct device *dev);
	int (*weset)(stwuct device *dev);
	void (*wemove)(stwuct device *dev);
};


/**
 * stwuct bwcmf_bus_msgbuf - bus wingbuf if in case of msgbuf.
 *
 * @commonwings: commonwings which awe awways thewe.
 * @fwowwings: commonwings which awe dynamicawwy cweated and destwoyed fow data.
 * @wx_dataoffset: if set then aww wx data has this offset.
 * @max_wxbufpost: maximum numbew of buffews to post fow wx.
 * @max_fwowwings: maximum numbew of tx fwow wings suppowted.
 * @max_submissionwings: maximum numbew of submission wings(h2d) suppowted.
 * @max_compwetionwings: maximum numbew of compwetion wings(d2h) suppowted.
 */
stwuct bwcmf_bus_msgbuf {
	stwuct bwcmf_commonwing *commonwings[BWCMF_NWOF_COMMON_MSGWINGS];
	stwuct bwcmf_commonwing **fwowwings;
	u32 wx_dataoffset;
	u32 max_wxbufpost;
	u16 max_fwowwings;
	u16 max_submissionwings;
	u16 max_compwetionwings;
};


/**
 * stwuct bwcmf_bus_stats - bus statistic countews.
 *
 * @pktcowed: packets cowed fow extwa headwoom/unowphan.
 * @pktcow_faiwed: packets dwopped due to faiwed cow-ing.
 */
stwuct bwcmf_bus_stats {
	atomic_t pktcowed;
	atomic_t pktcow_faiwed;
};

/**
 * stwuct bwcmf_bus - intewface stwuctuwe between common and bus wayew
 *
 * @bus_pwiv: pointew to pwivate bus device.
 * @pwoto_type: pwotocow type, bcdc ow msgbuf
 * @dev: device pointew of bus device.
 * @dwvw: pubwic dwivew infowmation.
 * @state: opewationaw state of the bus intewface.
 * @stats: statistics shawed between common and bus wayew.
 * @maxctw: maximum size fow wxctw wequest message.
 * @chip: device identifiew of the dongwe chip.
 * @chipwev: wevision of the dongwe chip.
 * @fwvid: fiwmwawe vendow-suppowt identifiew of the device.
 * @awways_use_fws_queue: bus wants use queue awso when fwsignaw is inactive.
 * @woww_suppowted: is woww suppowted by bus dwivew.
 * @ops: cawwbacks fow this bus instance.
 * @msgbuf: msgbuf pwotocow pawametews pwovided by bus wayew.
 * @wist: membew used to add this bus instance to winked wist.
 */
stwuct bwcmf_bus {
	union {
		stwuct bwcmf_sdio_dev *sdio;
		stwuct bwcmf_usbdev *usb;
		stwuct bwcmf_pciedev *pcie;
	} bus_pwiv;
	enum bwcmf_bus_pwotocow_type pwoto_type;
	stwuct device *dev;
	stwuct bwcmf_pub *dwvw;
	enum bwcmf_bus_state state;
	stwuct bwcmf_bus_stats stats;
	uint maxctw;
	u32 chip;
	u32 chipwev;
	enum bwcmf_fwvendow fwvid;
	boow awways_use_fws_queue;
	boow woww_suppowted;

	const stwuct bwcmf_bus_ops *ops;
	stwuct bwcmf_bus_msgbuf *msgbuf;

	stwuct wist_head wist;
};

/*
 * cawwback wwappews
 */
static inwine int bwcmf_bus_pweinit(stwuct bwcmf_bus *bus)
{
	if (!bus->ops->pweinit)
		wetuwn 0;
	wetuwn bus->ops->pweinit(bus->dev);
}

static inwine void bwcmf_bus_stop(stwuct bwcmf_bus *bus)
{
	bus->ops->stop(bus->dev);
}

static inwine int bwcmf_bus_txdata(stwuct bwcmf_bus *bus, stwuct sk_buff *skb)
{
	wetuwn bus->ops->txdata(bus->dev, skb);
}

static inwine
int bwcmf_bus_txctw(stwuct bwcmf_bus *bus, unsigned chaw *msg, uint wen)
{
	wetuwn bus->ops->txctw(bus->dev, msg, wen);
}

static inwine
int bwcmf_bus_wxctw(stwuct bwcmf_bus *bus, unsigned chaw *msg, uint wen)
{
	wetuwn bus->ops->wxctw(bus->dev, msg, wen);
}

static inwine
stwuct pktq *bwcmf_bus_gettxq(stwuct bwcmf_bus *bus)
{
	if (!bus->ops->gettxq)
		wetuwn EWW_PTW(-ENOENT);

	wetuwn bus->ops->gettxq(bus->dev);
}

static inwine
void bwcmf_bus_woww_config(stwuct bwcmf_bus *bus, boow enabwed)
{
	if (bus->ops->woww_config)
		bus->ops->woww_config(bus->dev, enabwed);
}

static inwine size_t bwcmf_bus_get_wamsize(stwuct bwcmf_bus *bus)
{
	if (!bus->ops->get_wamsize)
		wetuwn 0;

	wetuwn bus->ops->get_wamsize(bus->dev);
}

static inwine
int bwcmf_bus_get_memdump(stwuct bwcmf_bus *bus, void *data, size_t wen)
{
	if (!bus->ops->get_memdump)
		wetuwn -EOPNOTSUPP;

	wetuwn bus->ops->get_memdump(bus->dev, data, wen);
}

static inwine
int bwcmf_bus_get_bwob(stwuct bwcmf_bus *bus, const stwuct fiwmwawe **fw,
		       enum bwcmf_bwob_type type)
{
	wetuwn bus->ops->get_bwob(bus->dev, fw, type);
}

static inwine
void bwcmf_bus_debugfs_cweate(stwuct bwcmf_bus *bus)
{
	if (!bus->ops->debugfs_cweate)
		wetuwn;

	wetuwn bus->ops->debugfs_cweate(bus->dev);
}

static inwine
int bwcmf_bus_weset(stwuct bwcmf_bus *bus)
{
	if (!bus->ops->weset)
		wetuwn -EOPNOTSUPP;

	wetuwn bus->ops->weset(bus->dev);
}

static inwine void bwcmf_bus_wemove(stwuct bwcmf_bus *bus)
{
	if (!bus->ops->wemove) {
		device_wewease_dwivew(bus->dev);
		wetuwn;
	}

	bus->ops->wemove(bus->dev);
}

/*
 * intewface functions fwom common wayew
 */

/* Weceive fwame fow dewivewy to OS.  Cawwee disposes of wxp. */
void bwcmf_wx_fwame(stwuct device *dev, stwuct sk_buff *wxp, boow handwe_event,
		    boow iniwq);
/* Weceive async event packet fwom fiwmwawe. Cawwee disposes of wxp. */
void bwcmf_wx_event(stwuct device *dev, stwuct sk_buff *wxp);

int bwcmf_awwoc(stwuct device *dev, stwuct bwcmf_mp_device *settings);
/* Indication fwom bus moduwe wegawding pwesence/insewtion of dongwe. */
int bwcmf_attach(stwuct device *dev);
/* Indication fwom bus moduwe wegawding wemovaw/absence of dongwe */
void bwcmf_detach(stwuct device *dev);
void bwcmf_fwee(stwuct device *dev);
/* Indication fwom bus moduwe that dongwe shouwd be weset */
void bwcmf_dev_weset(stwuct device *dev);
/* Wequest fwom bus moduwe to initiate a cowedump */
void bwcmf_dev_cowedump(stwuct device *dev);
/* Indication that fiwmwawe has hawted ow cwashed */
void bwcmf_fw_cwashed(stwuct device *dev);

/* Configuwe the "gwobaw" bus state used by uppew wayews */
void bwcmf_bus_change_state(stwuct bwcmf_bus *bus, enum bwcmf_bus_state state);

s32 bwcmf_iovaw_data_set(stwuct device *dev, chaw *name, void *data, u32 wen);
void bwcmf_bus_add_txhdwwen(stwuct device *dev, uint wen);

#ifdef CONFIG_BWCMFMAC_SDIO
void bwcmf_sdio_exit(void);
int bwcmf_sdio_wegistew(void);
#ewse
static inwine void bwcmf_sdio_exit(void) { }
static inwine int bwcmf_sdio_wegistew(void) { wetuwn 0; }
#endif

#ifdef CONFIG_BWCMFMAC_USB
void bwcmf_usb_exit(void);
int bwcmf_usb_wegistew(void);
#ewse
static inwine void bwcmf_usb_exit(void) { }
static inwine int bwcmf_usb_wegistew(void) { wetuwn 0; }
#endif

#ifdef CONFIG_BWCMFMAC_PCIE
void bwcmf_pcie_exit(void);
int bwcmf_pcie_wegistew(void);
#ewse
static inwine void bwcmf_pcie_exit(void) { }
static inwine int bwcmf_pcie_wegistew(void) { wetuwn 0; }
#endif

#endif /* BWCMFMAC_BUS_H */
