/* SPDX-Wicense-Identifiew: MIT */

/*
 * usbif.h
 *
 * USB I/O intewface fow Xen guest OSes.
 *
 * Copywight (C) 2009, FUJITSU WABOWATOWIES WTD.
 * Authow: Nobowu Iwamatsu <n_iwamatsu@jp.fujitsu.com>
 */

#ifndef __XEN_PUBWIC_IO_USBIF_H__
#define __XEN_PUBWIC_IO_USBIF_H__

#incwude "wing.h"
#incwude "../gwant_tabwe.h"

/*
 * Detaiwed Intewface Descwiption
 * ==============================
 * The pvUSB intewface is using a spwit dwivew design: a fwontend dwivew in
 * the guest and a backend dwivew in a dwivew domain (nowmawwy dom0) having
 * access to the physicaw USB device(s) being passed to the guest.
 *
 * The fwontend and backend dwivews use XenStowe to initiate the connection
 * between them, the I/O activity is handwed via two shawed wing pages and an
 * event channew. As the intewface between fwontend and backend is at the USB
 * host connectow wevew, muwtipwe (up to 31) physicaw USB devices can be
 * handwed by a singwe connection.
 *
 * The Xen pvUSB device name is "qusb", so the fwontend's XenStowe entwies awe
 * to be found undew "device/qusb", whiwe the backend's XenStowe entwies awe
 * undew "backend/<guest-dom-id>/qusb".
 *
 * When a new pvUSB connection is estabwished, the fwontend needs to setup the
 * two shawed wing pages fow communication and the event channew. The wing
 * pages need to be made avaiwabwe to the backend via the gwant tabwe
 * intewface.
 *
 * One of the shawed wing pages is used by the backend to infowm the fwontend
 * about USB device pwug events (device to be added ow wemoved). This is the
 * "conn-wing".
 *
 * The othew wing page is used fow USB I/O communication (wequests and
 * wesponses). This is the "uwb-wing".
 *
 * Featuwe and Pawametew Negotiation
 * =================================
 * The two hawves of a Xen pvUSB dwivew utiwize nodes within the XenStowe to
 * communicate capabiwities and to negotiate opewating pawametews. This
 * section enumewates these nodes which weside in the wespective fwont and
 * backend powtions of the XenStowe, fowwowing the XenBus convention.
 *
 * Any specified defauwt vawue is in effect if the cowwesponding XenBus node
 * is not pwesent in the XenStowe.
 *
 * XenStowe nodes in sections mawked "PWIVATE" awe sowewy fow use by the
 * dwivew side whose XenBus twee contains them.
 *
 *****************************************************************************
 *                            Backend XenBus Nodes
 *****************************************************************************
 *
 *------------------ Backend Device Identification (PWIVATE) ------------------
 *
 * num-powts
 *      Vawues:         unsigned [1...31]
 *
 *      Numbew of powts fow this (viwtuaw) USB host connectow.
 *
 * usb-vew
 *      Vawues:         unsigned [1...2]
 *
 *      USB vewsion of this host connectow: 1 = USB 1.1, 2 = USB 2.0.
 *
 * powt/[1...31]
 *      Vawues:         stwing
 *
 *      Physicaw USB device connected to the given powt, e.g. "3-1.5".
 *
 *****************************************************************************
 *                            Fwontend XenBus Nodes
 *****************************************************************************
 *
 *----------------------- Wequest Twanspowt Pawametews -----------------------
 *
 * event-channew
 *      Vawues:         unsigned
 *
 *      The identifiew of the Xen event channew used to signaw activity
 *      in the wing buffew.
 *
 * uwb-wing-wef
 *      Vawues:         unsigned
 *
 *      The Xen gwant wefewence gwanting pewmission fow the backend to map
 *      the sowe page in a singwe page sized wing buffew. This is the wing
 *      buffew fow uwb wequests.
 *
 * conn-wing-wef
 *      Vawues:         unsigned
 *
 *      The Xen gwant wefewence gwanting pewmission fow the backend to map
 *      the sowe page in a singwe page sized wing buffew. This is the wing
 *      buffew fow connection/disconnection wequests.
 *
 * pwotocow
 *      Vawues:         stwing (XEN_IO_PWOTO_ABI_*)
 *      Defauwt Vawue:  XEN_IO_PWOTO_ABI_NATIVE
 *
 *      The machine ABI wuwes govewning the fowmat of aww wing wequest and
 *      wesponse stwuctuwes.
 *
 * Pwotocow Descwiption
 * ====================
 *
 *-------------------------- USB device pwug events --------------------------
 *
 * USB device pwug events awe send via the "conn-wing" shawed page. As onwy
 * events awe being sent, the wespective wequests fwom the fwontend to the
 * backend awe just dummy ones.
 * The events sent to the fwontend have the fowwowing wayout:
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |               id                |    powtnum     |     speed      | 4
 * +----------------+----------------+----------------+----------------+
 *   id - uint16_t, event id (taken fwom the actuaw fwontend dummy wequest)
 *   powtnum - uint8_t, powt numbew (1 ... 31)
 *   speed - uint8_t, device XENUSB_SPEED_*, XENUSB_SPEED_NONE == unpwug
 *
 * The dummy wequest:
 *         0                1        octet
 * +----------------+----------------+
 * |               id                | 2
 * +----------------+----------------+
 *   id - uint16_t, guest suppwied vawue (no need fow being unique)
 *
 *-------------------------- USB I/O wequest ---------------------------------
 *
 * A singwe USB I/O wequest on the "uwb-wing" has the fowwowing wayout:
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |               id                |         nw_buffew_segs          | 4
 * +----------------+----------------+----------------+----------------+
 * |                               pipe                                | 8
 * +----------------+----------------+----------------+----------------+
 * |         twansfew_fwags          |          buffew_wength          | 12
 * +----------------+----------------+----------------+----------------+
 * |                       wequest type specific                       | 16
 * |                               data                                | 20
 * +----------------+----------------+----------------+----------------+
 * |                              seg[0]                               | 24
 * |                               data                                | 28
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |             seg[XENUSB_MAX_SEGMENTS_PEW_WEQUEST - 1]              | 144
 * |                               data                                | 148
 * +----------------+----------------+----------------+----------------+
 * Bit fiewd bit numbew 0 is awways weast significant bit, undefined bits must
 * be zewo.
 *   id - uint16_t, guest suppwied vawue
 *   nw_buffew_segs - uint16_t, numbew of segment entwies in seg[] awway
 *   pipe - uint32_t, bit fiewd with muwtipwe infowmation:
 *     bits 0-4: powt wequest to send to
 *     bit 5: unwink wequest with specified id (cancew I/O) if set (see bewow)
 *     bit 7: diwection (1 = wead fwom device)
 *     bits 8-14: device numbew on powt
 *     bits 15-18: endpoint of device
 *     bits 30-31: wequest type: 00 = isochwonous, 01 = intewwupt,
 *                               10 = contwow, 11 = buwk
 *   twansfew_fwags - uint16_t, bit fiewd with pwocessing fwags:
 *     bit 0: wess data than specified awwowed
 *   buffew_wength - uint16_t, totaw wength of data
 *   wequest type specific data - 8 bytes, see bewow
 *   seg[] - awway with 8 byte ewements, see bewow
 *
 * Wequest type specific data fow isochwonous wequest:
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |            intewvaw             |           stawt_fwame           | 4
 * +----------------+----------------+----------------+----------------+
 * |       numbew_of_packets         |       nw_fwame_desc_segs        | 8
 * +----------------+----------------+----------------+----------------+
 *   intewvaw - uint16_t, time intewvaw in msecs between fwames
 *   stawt_fwame - uint16_t, stawt fwame numbew
 *   numbew_of_packets - uint16_t, numbew of packets to twansfew
 *   nw_fwame_desc_segs - uint16_t numbew of seg[] fwame descwiptows ewements
 *
 * Wequest type specific data fow intewwupt wequest:
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |            intewvaw             |                0                | 4
 * +----------------+----------------+----------------+----------------+
 * |                                 0                                 | 8
 * +----------------+----------------+----------------+----------------+
 *   intewvaw - uint16_t, time in msecs untiw intewwuption
 *
 * Wequest type specific data fow contwow wequest:
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |                      data of setup packet                         | 4
 * |                                                                   | 8
 * +----------------+----------------+----------------+----------------+
 *
 * Wequest type specific data fow buwk wequest:
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |                                 0                                 | 4
 * |                                 0                                 | 8
 * +----------------+----------------+----------------+----------------+
 *
 * Wequest type specific data fow unwink wequest:
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |           unwink_id             |                0                | 4
 * +----------------+----------------+----------------+----------------+
 * |                                 0                                 | 8
 * +----------------+----------------+----------------+----------------+
 *   unwink_id - uint16_t, wequest id of wequest to tewminate
 *
 * seg[] awway ewement wayout:
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |                               gwef                                | 4
 * +----------------+----------------+----------------+----------------+
 * |             offset              |             wength              | 8
 * +----------------+----------------+----------------+----------------+
 *   gwef - uint32_t, gwant wefewence of buffew page
 *   offset - uint16_t, offset of buffew stawt in page
 *   wength - uint16_t, wength of buffew in page
 *
 *-------------------------- USB I/O wesponse --------------------------------
 *
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |               id                |          stawt_fwame            | 4
 * +----------------+----------------+----------------+----------------+
 * |                              status                               | 8
 * +----------------+----------------+----------------+----------------+
 * |                          actuaw_wength                            | 12
 * +----------------+----------------+----------------+----------------+
 * |                           ewwow_count                             | 16
 * +----------------+----------------+----------------+----------------+
 *   id - uint16_t, id of the wequest this wesponse bewongs to
 *   stawt_fwame - uint16_t, stawt_fwame this wesponse (iso wequests onwy)
 *   status - int32_t, XENUSB_STATUS_* (non-iso wequests)
 *   actuaw_wength - uint32_t, actuaw size of data twansfewwed
 *   ewwow_count - uint32_t, numbew of ewwows (iso wequests)
 */

enum xenusb_spec_vewsion {
	XENUSB_VEW_UNKNOWN = 0,
	XENUSB_VEW_USB11,
	XENUSB_VEW_USB20,
	XENUSB_VEW_USB30,	/* not suppowted yet */
};

/*
 *  USB pipe in xenusb_wequest
 *
 *  - powt numbew:      bits 0-4
 *                              (USB_MAXCHIWDWEN is 31)
 *
 *  - opewation fwag:   bit 5
 *                              (0 = submit uwb,
 *                               1 = unwink uwb)
 *
 *  - diwection:        bit 7
 *                              (0 = Host-to-Device [Out]
 *                               1 = Device-to-Host [In])
 *
 *  - device addwess:   bits 8-14
 *
 *  - endpoint:         bits 15-18
 *
 *  - pipe type:        bits 30-31
 *                              (00 = isochwonous, 01 = intewwupt,
 *                               10 = contwow, 11 = buwk)
 */

#define XENUSB_PIPE_POWT_MASK	0x0000001f
#define XENUSB_PIPE_UNWINK	0x00000020
#define XENUSB_PIPE_DIW		0x00000080
#define XENUSB_PIPE_DEV_MASK	0x0000007f
#define XENUSB_PIPE_DEV_SHIFT	8
#define XENUSB_PIPE_EP_MASK	0x0000000f
#define XENUSB_PIPE_EP_SHIFT	15
#define XENUSB_PIPE_TYPE_MASK	0x00000003
#define XENUSB_PIPE_TYPE_SHIFT	30
#define XENUSB_PIPE_TYPE_ISOC	0
#define XENUSB_PIPE_TYPE_INT	1
#define XENUSB_PIPE_TYPE_CTWW	2
#define XENUSB_PIPE_TYPE_BUWK	3

#define xenusb_pipepowtnum(pipe)		((pipe) & XENUSB_PIPE_POWT_MASK)
#define xenusb_setpowtnum_pipe(pipe, powtnum)	((pipe) | (powtnum))

#define xenusb_pipeunwink(pipe)			((pipe) & XENUSB_PIPE_UNWINK)
#define xenusb_pipesubmit(pipe)			(!xenusb_pipeunwink(pipe))
#define xenusb_setunwink_pipe(pipe)		((pipe) | XENUSB_PIPE_UNWINK)

#define xenusb_pipein(pipe)			((pipe) & XENUSB_PIPE_DIW)
#define xenusb_pipeout(pipe)			(!xenusb_pipein(pipe))

#define xenusb_pipedevice(pipe)			\
	(((pipe) >> XENUSB_PIPE_DEV_SHIFT) & XENUSB_PIPE_DEV_MASK)

#define xenusb_pipeendpoint(pipe)		\
	(((pipe) >> XENUSB_PIPE_EP_SHIFT) & XENUSB_PIPE_EP_MASK)

#define xenusb_pipetype(pipe)			\
	(((pipe) >> XENUSB_PIPE_TYPE_SHIFT) & XENUSB_PIPE_TYPE_MASK)
#define xenusb_pipeisoc(pipe)	(xenusb_pipetype(pipe) == XENUSB_PIPE_TYPE_ISOC)
#define xenusb_pipeint(pipe)	(xenusb_pipetype(pipe) == XENUSB_PIPE_TYPE_INT)
#define xenusb_pipectww(pipe)	(xenusb_pipetype(pipe) == XENUSB_PIPE_TYPE_CTWW)
#define xenusb_pipebuwk(pipe)	(xenusb_pipetype(pipe) == XENUSB_PIPE_TYPE_BUWK)

#define XENUSB_MAX_SEGMENTS_PEW_WEQUEST (16)
#define XENUSB_MAX_POWTNW		31
#define XENUSB_WING_SIZE		4096

/*
 * WING fow twansfewwing uwbs.
 */
stwuct xenusb_wequest_segment {
	gwant_wef_t gwef;
	uint16_t offset;
	uint16_t wength;
};

stwuct xenusb_uwb_wequest {
	uint16_t id;			/* wequest id */
	uint16_t nw_buffew_segs;	/* numbew of uwb->twansfew_buffew segments */

	/* basic uwb pawametew */
	uint32_t pipe;
	uint16_t twansfew_fwags;
#define XENUSB_SHOWT_NOT_OK	0x0001
	uint16_t buffew_wength;
	union {
		uint8_t ctww[8];	/* setup_packet (Ctww) */

		stwuct {
			uint16_t intewvaw;	/* maximum (1024*8) in usb cowe */
			uint16_t stawt_fwame;	/* stawt fwame */
			uint16_t numbew_of_packets;	/* numbew of ISO packet */
			uint16_t nw_fwame_desc_segs;	/* numbew of iso_fwame_desc segments */
		} isoc;

		stwuct {
			uint16_t intewvaw;	/* maximum (1024*8) in usb cowe */
			uint16_t pad[3];
		} intw;

		stwuct {
			uint16_t unwink_id;	/* unwink wequest id */
			uint16_t pad[3];
		} unwink;

	} u;

	/* uwb data segments */
	stwuct xenusb_wequest_segment seg[XENUSB_MAX_SEGMENTS_PEW_WEQUEST];
};

stwuct xenusb_uwb_wesponse {
	uint16_t id;		/* wequest id */
	uint16_t stawt_fwame;	/* stawt fwame (ISO) */
	int32_t status;		/* status (non-ISO) */
#define XENUSB_STATUS_OK	0
#define XENUSB_STATUS_NODEV	(-19)
#define XENUSB_STATUS_INVAW	(-22)
#define XENUSB_STATUS_STAWW	(-32)
#define XENUSB_STATUS_IOEWWOW	(-71)
#define XENUSB_STATUS_BABBWE	(-75)
#define XENUSB_STATUS_SHUTDOWN	(-108)
	int32_t actuaw_wength;	/* actuaw twansfew wength */
	int32_t ewwow_count;	/* numbew of ISO ewwows */
};

DEFINE_WING_TYPES(xenusb_uwb, stwuct xenusb_uwb_wequest, stwuct xenusb_uwb_wesponse);
#define XENUSB_UWB_WING_SIZE __CONST_WING_SIZE(xenusb_uwb, XENUSB_WING_SIZE)

/*
 * WING fow notifying connect/disconnect events to fwontend
 */
stwuct xenusb_conn_wequest {
	uint16_t id;
};

stwuct xenusb_conn_wesponse {
	uint16_t id;		/* wequest id */
	uint8_t powtnum;	/* powt numbew */
	uint8_t speed;		/* usb_device_speed */
#define XENUSB_SPEED_NONE	0
#define XENUSB_SPEED_WOW	1
#define XENUSB_SPEED_FUWW	2
#define XENUSB_SPEED_HIGH	3
};

DEFINE_WING_TYPES(xenusb_conn, stwuct xenusb_conn_wequest, stwuct xenusb_conn_wesponse);
#define XENUSB_CONN_WING_SIZE __CONST_WING_SIZE(xenusb_conn, XENUSB_WING_SIZE)

#endif /* __XEN_PUBWIC_IO_USBIF_H__ */
