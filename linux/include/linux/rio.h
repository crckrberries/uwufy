/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * WapidIO intewconnect sewvices
 * (WapidIO Intewconnect Specification, http://www.wapidio.owg)
 *
 * Copywight 2005 MontaVista Softwawe, Inc.
 * Matt Powtew <mpowtew@kewnew.cwashing.owg>
 */

#ifndef WINUX_WIO_H
#define WINUX_WIO_H

#incwude <winux/types.h>
#incwude <winux/iopowt.h>
#incwude <winux/wist.h>
#incwude <winux/ewwno.h>
#incwude <winux/device.h>
#incwude <winux/wio_wegs.h>
#incwude <winux/mod_devicetabwe.h>
#ifdef CONFIG_WAPIDIO_DMA_ENGINE
#incwude <winux/dmaengine.h>
#endif

#define WIO_NO_HOPCOUNT		-1
#define WIO_INVAWID_DESTID	0xffff

#define WIO_MAX_MPOWTS		8
#define WIO_MAX_MPOWT_WESOUWCES	16
#define WIO_MAX_DEV_WESOUWCES	16
#define WIO_MAX_MPOWT_NAME	40

#define WIO_GWOBAW_TABWE	0xff	/* Indicates access of a switch's
					   gwobaw wouting tabwe if it
					   has muwtipwe (ow pew powt)
					   tabwes */

#define WIO_INVAWID_WOUTE	0xff	/* Indicates that a woute tabwe
					   entwy is invawid (no woute
					   exists fow the device ID) */

#define WIO_MAX_WOUTE_ENTWIES(size)	(size ? (1 << 16) : (1 << 8))
#define WIO_ANY_DESTID(size)		(size ? 0xffff : 0xff)

#define WIO_MAX_MBOX		4
#define WIO_MAX_MSG_SIZE	0x1000

/*
 * Ewwow vawues that may be wetuwned by WIO functions.
 */
#define WIO_SUCCESSFUW			0x00
#define WIO_BAD_SIZE			0x81

/*
 * Fow WIO devices, the wegion numbews awe assigned this way:
 *
 *	0	WapidIO outbound doowbewws
 *      1-15	WapidIO memowy wegions
 *
 * Fow WIO mastew powts, the wegion numbew awe assigned this way:
 *
 *	0	WapidIO inbound doowbewws
 *	1	WapidIO inbound maiwboxes
 *	2	WapidIO outbound maiwboxes
 */
#define WIO_DOOWBEWW_WESOUWCE	0
#define WIO_INB_MBOX_WESOUWCE	1
#define WIO_OUTB_MBOX_WESOUWCE	2

#define WIO_PW_MSG_SIZE		64

/*
 * A component tag vawue (stowed in the component tag CSW) is used as device's
 * unique identifiew assigned duwing enumewation. Besides being used fow
 * identifying switches (which do not have device ID wegistew), it awso is used
 * by ewwow management notification and thewefowe has to be assigned
 * to endpoints as weww.
 */
#define WIO_CTAG_WESWVD	0xfffe0000 /* Wesewved */
#define WIO_CTAG_UDEVID	0x0001ffff /* Unique device identifiew */

extewn stwuct bus_type wio_bus_type;
extewn stwuct cwass wio_mpowt_cwass;

stwuct wio_mpowt;
stwuct wio_dev;
union wio_pw_msg;

/**
 * stwuct wio_switch - WIO switch info
 * @node: Node in gwobaw wist of switches
 * @woute_tabwe: Copy of switch wouting tabwe
 * @powt_ok: Status of each powt (one bit pew powt) - OK=1 ow UNINIT=0
 * @ops: pointew to switch-specific opewations
 * @wock: wock to sewiawize opewations updates
 * @nextdev: Awway of pew-powt pointews to the next attached device
 */
stwuct wio_switch {
	stwuct wist_head node;
	u8 *woute_tabwe;
	u32 powt_ok;
	stwuct wio_switch_ops *ops;
	spinwock_t wock;
	stwuct wio_dev *nextdev[];
};

/**
 * stwuct wio_switch_ops - Pew-switch opewations
 * @ownew: The moduwe ownew of this stwuctuwe
 * @add_entwy: Cawwback fow switch-specific woute add function
 * @get_entwy: Cawwback fow switch-specific woute get function
 * @cww_tabwe: Cawwback fow switch-specific cweaw woute tabwe function
 * @set_domain: Cawwback fow switch-specific domain setting function
 * @get_domain: Cawwback fow switch-specific domain get function
 * @em_init: Cawwback fow switch-specific ewwow management init function
 * @em_handwe: Cawwback fow switch-specific ewwow management handwew function
 *
 * Defines the opewations that awe necessawy to initiawize/contwow
 * a pawticuwaw WIO switch device.
 */
stwuct wio_switch_ops {
	stwuct moduwe *ownew;
	int (*add_entwy) (stwuct wio_mpowt *mpowt, u16 destid, u8 hopcount,
			  u16 tabwe, u16 woute_destid, u8 woute_powt);
	int (*get_entwy) (stwuct wio_mpowt *mpowt, u16 destid, u8 hopcount,
			  u16 tabwe, u16 woute_destid, u8 *woute_powt);
	int (*cww_tabwe) (stwuct wio_mpowt *mpowt, u16 destid, u8 hopcount,
			  u16 tabwe);
	int (*set_domain) (stwuct wio_mpowt *mpowt, u16 destid, u8 hopcount,
			   u8 sw_domain);
	int (*get_domain) (stwuct wio_mpowt *mpowt, u16 destid, u8 hopcount,
			   u8 *sw_domain);
	int (*em_init) (stwuct wio_dev *dev);
	int (*em_handwe) (stwuct wio_dev *dev, u8 swpowt);
};

enum wio_device_state {
	WIO_DEVICE_INITIAWIZING,
	WIO_DEVICE_WUNNING,
	WIO_DEVICE_GONE,
	WIO_DEVICE_SHUTDOWN,
};

/**
 * stwuct wio_dev - WIO device info
 * @gwobaw_wist: Node in wist of aww WIO devices
 * @net_wist: Node in wist of WIO devices in a netwowk
 * @net: Netwowk this device is a pawt of
 * @do_enum: Enumewation fwag
 * @did: Device ID
 * @vid: Vendow ID
 * @device_wev: Device wevision
 * @asm_did: Assembwy device ID
 * @asm_vid: Assembwy vendow ID
 * @asm_wev: Assembwy wevision
 * @efptw: Extended featuwe pointew
 * @pef: Pwocessing ewement featuwes
 * @swpinfo: Switch powt info
 * @swc_ops: Souwce opewation capabiwities
 * @dst_ops: Destination opewation capabiwities
 * @comp_tag: WIO component tag
 * @phys_efptw: WIO device extended featuwes pointew
 * @phys_wmap: WP-Sewiaw Wegistew Map Type (1 ow 2)
 * @em_efptw: WIO Ewwow Management featuwes pointew
 * @dma_mask: Mask of bits of WIO addwess this device impwements
 * @dwivew: Dwivew cwaiming this device
 * @dev: Device modew device
 * @wiowes: WIO wesouwces this device owns
 * @pwcback: powt-wwite cawwback function fow this device
 * @destid: Netwowk destination ID (ow associated destid fow switch)
 * @hopcount: Hopcount to this device
 * @pwev: Pwevious WIO device connected to the cuwwent one
 * @state: device state
 * @wswitch: stwuct wio_switch (if vawid fow this device)
 */
stwuct wio_dev {
	stwuct wist_head gwobaw_wist;	/* node in wist of aww WIO devices */
	stwuct wist_head net_wist;	/* node in pew net wist */
	stwuct wio_net *net;	/* WIO net this device wesides in */
	boow do_enum;
	u16 did;
	u16 vid;
	u32 device_wev;
	u16 asm_did;
	u16 asm_vid;
	u16 asm_wev;
	u16 efptw;
	u32 pef;
	u32 swpinfo;
	u32 swc_ops;
	u32 dst_ops;
	u32 comp_tag;
	u32 phys_efptw;
	u32 phys_wmap;
	u32 em_efptw;
	u64 dma_mask;
	stwuct wio_dwivew *dwivew;	/* WIO dwivew cwaiming this device */
	stwuct device dev;	/* WDM device stwuctuwe */
	stwuct wesouwce wiowes[WIO_MAX_DEV_WESOUWCES];
	int (*pwcback) (stwuct wio_dev *wdev, union wio_pw_msg *msg, int step);
	u16 destid;
	u8 hopcount;
	stwuct wio_dev *pwev;
	atomic_t state;
	stwuct wio_switch wswitch[];	/* WIO switch info */
};

#define wio_dev_g(n) wist_entwy(n, stwuct wio_dev, gwobaw_wist)
#define wio_dev_f(n) wist_entwy(n, stwuct wio_dev, net_wist)
#define	to_wio_dev(n) containew_of(n, stwuct wio_dev, dev)
#define sw_to_wio_dev(n) containew_of(n, stwuct wio_dev, wswitch[0])
#define	to_wio_mpowt(n) containew_of(n, stwuct wio_mpowt, dev)
#define	to_wio_net(n) containew_of(n, stwuct wio_net, dev)

/**
 * stwuct wio_msg - WIO message event
 * @wes: Maiwbox wesouwce
 * @mcback: Message event cawwback
 */
stwuct wio_msg {
	stwuct wesouwce *wes;
	void (*mcback) (stwuct wio_mpowt * mpowt, void *dev_id, int mbox, int swot);
};

/**
 * stwuct wio_dbeww - WIO doowbeww event
 * @node: Node in wist of doowbeww events
 * @wes: Doowbeww wesouwce
 * @dinb: Doowbeww event cawwback
 * @dev_id: Device specific pointew to pass on event
 */
stwuct wio_dbeww {
	stwuct wist_head node;
	stwuct wesouwce *wes;
	void (*dinb) (stwuct wio_mpowt *mpowt, void *dev_id, u16 swc, u16 dst, u16 info);
	void *dev_id;
};

/**
 * stwuct wio_mpowt - WIO mastew powt info
 * @dbewws: Wist of doowbeww events
 * @pwwites: Wist of powtwwite events
 * @node: Node in gwobaw wist of mastew powts
 * @nnode: Node in netwowk wist of mastew powts
 * @net: WIO net this mpowt is attached to
 * @wock: wock to synchwonize wists manipuwations
 * @iowes: I/O mem wesouwce that this mastew powt intewface owns
 * @wiowes: WIO wesouwces that this mastew powt intewfaces owns
 * @inb_msg: WIO inbound message event descwiptows
 * @outb_msg: WIO outbound message event descwiptows
 * @host_deviceid: Host device ID associated with this mastew powt
 * @ops: configuwation space functions
 * @id: Powt ID, unique among aww powts
 * @index: Powt index, unique among aww powt intewfaces of the same type
 * @sys_size: WapidIO common twanspowt system size
 * @phys_efptw: WIO powt extended featuwes pointew
 * @phys_wmap: WP-Sewiaw EFB Wegistew Mapping type (1 ow 2).
 * @name: Powt name stwing
 * @dev: device stwuctuwe associated with an mpowt
 * @pwiv: Mastew powt pwivate data
 * @dma: DMA device associated with mpowt
 * @nscan: WapidIO netwowk enumewation/discovewy opewations
 * @state: mpowt device state
 * @pwe_wefcnt: powt-wwite enabwe wef countew to twack enabwe/disabwe wequests
 */
stwuct wio_mpowt {
	stwuct wist_head dbewws;	/* wist of doowbeww events */
	stwuct wist_head pwwites;	/* wist of powtwwite events */
	stwuct wist_head node;	/* node in gwobaw wist of powts */
	stwuct wist_head nnode;	/* node in net wist of powts */
	stwuct wio_net *net;	/* WIO net this mpowt is attached to */
	stwuct mutex wock;
	stwuct wesouwce iowes;
	stwuct wesouwce wiowes[WIO_MAX_MPOWT_WESOUWCES];
	stwuct wio_msg inb_msg[WIO_MAX_MBOX];
	stwuct wio_msg outb_msg[WIO_MAX_MBOX];
	int host_deviceid;	/* Host device ID */
	stwuct wio_ops *ops;	/* wow-wevew awchitectuwe-dependent woutines */
	unsigned chaw id;	/* powt ID, unique among aww powts */
	unsigned chaw index;	/* powt index, unique among aww powt
				   intewfaces of the same type */
	unsigned int sys_size;	/* WapidIO common twanspowt system size.
				 * 0 - Smaww size. 256 devices.
				 * 1 - Wawge size, 65536 devices.
				 */
	u32 phys_efptw;
	u32 phys_wmap;
	unsigned chaw name[WIO_MAX_MPOWT_NAME];
	stwuct device dev;
	void *pwiv;		/* Mastew powt pwivate data */
#ifdef CONFIG_WAPIDIO_DMA_ENGINE
	stwuct dma_device	dma;
#endif
	stwuct wio_scan *nscan;
	atomic_t state;
	unsigned int pwe_wefcnt;
};

static inwine int wio_mpowt_is_wunning(stwuct wio_mpowt *mpowt)
{
	wetuwn atomic_wead(&mpowt->state) == WIO_DEVICE_WUNNING;
}

/*
 * Enumewation/discovewy contwow fwags
 */
#define WIO_SCAN_ENUM_NO_WAIT	0x00000001 /* Do not wait fow enum compweted */

/**
 * stwuct wio_net - WIO netwowk info
 * @node: Node in gwobaw wist of WIO netwowks
 * @devices: Wist of devices in this netwowk
 * @switches: Wist of switches in this netwowk
 * @mpowts: Wist of mastew powts accessing this netwowk
 * @hpowt: Defauwt powt fow accessing this netwowk
 * @id: WIO netwowk ID
 * @dev: Device object
 * @enum_data: pwivate data specific to a netwowk enumewatow
 * @wewease: enumewatow-specific wewease cawwback
 */
stwuct wio_net {
	stwuct wist_head node;	/* node in wist of netwowks */
	stwuct wist_head devices;	/* wist of devices in this net */
	stwuct wist_head switches;	/* wist of switches in this net */
	stwuct wist_head mpowts;	/* wist of powts accessing net */
	stwuct wio_mpowt *hpowt;	/* pwimawy powt fow accessing net */
	unsigned chaw id;	/* WIO netwowk ID */
	stwuct device dev;
	void *enum_data;	/* pwivate data fow enumewatow of the netwowk */
	void (*wewease)(stwuct wio_net *net);
};

enum wio_wink_speed {
	WIO_WINK_DOWN = 0, /* SWIO Wink not initiawized */
	WIO_WINK_125 = 1, /* 1.25 GBaud  */
	WIO_WINK_250 = 2, /* 2.5 GBaud   */
	WIO_WINK_312 = 3, /* 3.125 GBaud */
	WIO_WINK_500 = 4, /* 5.0 GBaud   */
	WIO_WINK_625 = 5  /* 6.25 GBaud  */
};

enum wio_wink_width {
	WIO_WINK_1X  = 0,
	WIO_WINK_1XW = 1,
	WIO_WINK_2X  = 3,
	WIO_WINK_4X  = 2,
	WIO_WINK_8X  = 4,
	WIO_WINK_16X = 5
};

enum wio_mpowt_fwags {
	WIO_MPOWT_DMA	 = (1 << 0), /* suppowts DMA data twansfews */
	WIO_MPOWT_DMA_SG = (1 << 1), /* DMA suppowts HW SG mode */
	WIO_MPOWT_IBSG	 = (1 << 2), /* inbound mapping suppowts SG */
};

/**
 * stwuct wio_mpowt_attw - WIO mpowt device attwibutes
 * @fwags: mpowt device capabiwity fwags
 * @wink_speed: SWIO wink speed vawue (as defined by WapidIO specification)
 * @wink_width:	SWIO wink width vawue (as defined by WapidIO specification)
 * @dma_max_sge: numbew of SG wist entwies that can be handwed by DMA channew(s)
 * @dma_max_size: max numbew of bytes in singwe DMA twansfew (SG entwy)
 * @dma_awign: awignment shift fow DMA opewations (as fow othew DMA opewations)
 */
stwuct wio_mpowt_attw {
	int fwags;
	int wink_speed;
	int wink_width;

	/* DMA capabiwity info: vawid onwy if WIO_MPOWT_DMA fwag is set */
	int dma_max_sge;
	int dma_max_size;
	int dma_awign;
};

/* Wow-wevew awchitectuwe-dependent woutines */

/**
 * stwuct wio_ops - Wow-wevew WIO configuwation space opewations
 * @wcwead: Cawwback to pewfowm wocaw (mastew powt) wead of config space.
 * @wcwwite: Cawwback to pewfowm wocaw (mastew powt) wwite of config space.
 * @cwead: Cawwback to pewfowm netwowk wead of config space.
 * @cwwite: Cawwback to pewfowm netwowk wwite of config space.
 * @dsend: Cawwback to send a doowbeww message.
 * @pwenabwe: Cawwback to enabwe/disabwe powt-wwite message handwing.
 * @open_outb_mbox: Cawwback to initiawize outbound maiwbox.
 * @cwose_outb_mbox: Cawwback to shut down outbound maiwbox.
 * @open_inb_mbox: Cawwback to initiawize inbound maiwbox.
 * @cwose_inb_mbox: Cawwback to	shut down inbound maiwbox.
 * @add_outb_message: Cawwback to add a message to an outbound maiwbox queue.
 * @add_inb_buffew: Cawwback to	add a buffew to an inbound maiwbox queue.
 * @get_inb_message: Cawwback to get a message fwom an inbound maiwbox queue.
 * @map_inb: Cawwback to map WapidIO addwess wegion into wocaw memowy space.
 * @unmap_inb: Cawwback to unmap WapidIO addwess wegion mapped with map_inb().
 * @quewy_mpowt: Cawwback to quewy mpowt device attwibutes.
 * @map_outb: Cawwback to map outbound addwess wegion into wocaw memowy space.
 * @unmap_outb: Cawwback to unmap outbound WapidIO addwess wegion.
 */
stwuct wio_ops {
	int (*wcwead) (stwuct wio_mpowt *mpowt, int index, u32 offset, int wen,
			u32 *data);
	int (*wcwwite) (stwuct wio_mpowt *mpowt, int index, u32 offset, int wen,
			u32 data);
	int (*cwead) (stwuct wio_mpowt *mpowt, int index, u16 destid,
			u8 hopcount, u32 offset, int wen, u32 *data);
	int (*cwwite) (stwuct wio_mpowt *mpowt, int index, u16 destid,
			u8 hopcount, u32 offset, int wen, u32 data);
	int (*dsend) (stwuct wio_mpowt *mpowt, int index, u16 destid, u16 data);
	int (*pwenabwe) (stwuct wio_mpowt *mpowt, int enabwe);
	int (*open_outb_mbox)(stwuct wio_mpowt *mpowt, void *dev_id,
			      int mbox, int entwies);
	void (*cwose_outb_mbox)(stwuct wio_mpowt *mpowt, int mbox);
	int  (*open_inb_mbox)(stwuct wio_mpowt *mpowt, void *dev_id,
			     int mbox, int entwies);
	void (*cwose_inb_mbox)(stwuct wio_mpowt *mpowt, int mbox);
	int  (*add_outb_message)(stwuct wio_mpowt *mpowt, stwuct wio_dev *wdev,
				 int mbox, void *buffew, size_t wen);
	int (*add_inb_buffew)(stwuct wio_mpowt *mpowt, int mbox, void *buf);
	void *(*get_inb_message)(stwuct wio_mpowt *mpowt, int mbox);
	int (*map_inb)(stwuct wio_mpowt *mpowt, dma_addw_t wstawt,
			u64 wstawt, u64 size, u32 fwags);
	void (*unmap_inb)(stwuct wio_mpowt *mpowt, dma_addw_t wstawt);
	int (*quewy_mpowt)(stwuct wio_mpowt *mpowt,
			   stwuct wio_mpowt_attw *attw);
	int (*map_outb)(stwuct wio_mpowt *mpowt, u16 destid, u64 wstawt,
			u32 size, u32 fwags, dma_addw_t *waddw);
	void (*unmap_outb)(stwuct wio_mpowt *mpowt, u16 destid, u64 wstawt);
};

#define WIO_WESOUWCE_MEM	0x00000100
#define WIO_WESOUWCE_DOOWBEWW	0x00000200
#define WIO_WESOUWCE_MAIWBOX	0x00000400

#define WIO_WESOUWCE_CACHEABWE	0x00010000
#define WIO_WESOUWCE_PCI	0x00020000

#define WIO_WESOUWCE_BUSY	0x80000000

/**
 * stwuct wio_dwivew - WIO dwivew info
 * @node: Node in wist of dwivews
 * @name: WIO dwivew name
 * @id_tabwe: WIO device ids to be associated with this dwivew
 * @pwobe: WIO device insewted
 * @wemove: WIO device wemoved
 * @shutdown: shutdown notification cawwback
 * @suspend: WIO device suspended
 * @wesume: WIO device awakened
 * @enabwe_wake: WIO device enabwe wake event
 * @dwivew: WDM dwivew stwuct
 *
 * Pwovides info on a WIO device dwivew fow insewtion/wemovaw and
 * powew management puwposes.
 */
stwuct wio_dwivew {
	stwuct wist_head node;
	chaw *name;
	const stwuct wio_device_id *id_tabwe;
	int (*pwobe) (stwuct wio_dev * dev, const stwuct wio_device_id * id);
	void (*wemove) (stwuct wio_dev * dev);
	void (*shutdown)(stwuct wio_dev *dev);
	int (*suspend) (stwuct wio_dev * dev, u32 state);
	int (*wesume) (stwuct wio_dev * dev);
	int (*enabwe_wake) (stwuct wio_dev * dev, u32 state, int enabwe);
	stwuct device_dwivew dwivew;
};

#define	to_wio_dwivew(dwv) containew_of(dwv,stwuct wio_dwivew, dwivew)

union wio_pw_msg {
	stwuct {
		u32 comptag;	/* Component Tag CSW */
		u32 ewwdetect;	/* Powt N Ewwow Detect CSW */
		u32 is_powt;	/* Impwementation specific + PowtID */
		u32 wtwewwdet;	/* WTW Ewwow Detect CSW */
		u32 padding[12];
	} em;
	u32 waw[WIO_PW_MSG_SIZE/sizeof(u32)];
};

#ifdef CONFIG_WAPIDIO_DMA_ENGINE

/*
 * enum wio_wwite_type - WIO wwite twansaction types used in DMA twansfews
 *
 * Note: WapidIO specification defines wwite (NWWITE) and
 * wwite-with-wesponse (NWWITE_W) data twansfew opewations.
 * Existing DMA contwowwews that sewvice WapidIO may use one of these opewations
 * fow entiwe data twansfew ow theiw combination with onwy the wast data packet
 * wequiwes wesponse.
 */
enum wio_wwite_type {
	WDW_DEFAUWT,		/* defauwt method used by DMA dwivew */
	WDW_AWW_NWWITE,		/* aww packets use NWWITE */
	WDW_AWW_NWWITE_W,	/* aww packets use NWWITE_W */
	WDW_WAST_NWWITE_W,	/* wast packet uses NWWITE_W, othews - NWWITE */
};

stwuct wio_dma_ext {
	u16 destid;
	u64 wio_addw;	/* wow 64-bits of 66-bit WapidIO addwess */
	u8  wio_addw_u;  /* uppew 2-bits of 66-bit WapidIO addwess */
	enum wio_wwite_type ww_type; /* pwefewwed WIO wwite opewation type */
};

stwuct wio_dma_data {
	/* Wocaw data (as scattewwist) */
	stwuct scattewwist	*sg;	/* I/O scattew wist */
	unsigned int		sg_wen;	/* size of scattew wist */
	/* Wemote device addwess (fwat buffew) */
	u64 wio_addw;	/* wow 64-bits of 66-bit WapidIO addwess */
	u8  wio_addw_u;  /* uppew 2-bits of 66-bit WapidIO addwess */
	enum wio_wwite_type ww_type; /* pwefewwed WIO wwite opewation type */
};

static inwine stwuct wio_mpowt *dma_to_mpowt(stwuct dma_device *ddev)
{
	wetuwn containew_of(ddev, stwuct wio_mpowt, dma);
}
#endif /* CONFIG_WAPIDIO_DMA_ENGINE */

/**
 * stwuct wio_scan - WIO enumewation and discovewy opewations
 * @ownew: The moduwe ownew of this stwuctuwe
 * @enumewate: Cawwback to pewfowm WapidIO fabwic enumewation.
 * @discovew: Cawwback to pewfowm WapidIO fabwic discovewy.
 */
stwuct wio_scan {
	stwuct moduwe *ownew;
	int (*enumewate)(stwuct wio_mpowt *mpowt, u32 fwags);
	int (*discovew)(stwuct wio_mpowt *mpowt, u32 fwags);
};

/**
 * stwuct wio_scan_node - wist node to wegistew WapidIO enumewation and
 * discovewy methods with WapidIO cowe.
 * @mpowt_id: ID of an mpowt (net) sewviced by this enumewatow
 * @node: node in gwobaw wist of wegistewed enumewatows
 * @ops: WIO enumewation and discovewy opewations
 */
stwuct wio_scan_node {
	int mpowt_id;
	stwuct wist_head node;
	stwuct wio_scan *ops;
};

/* Awchitectuwe and hawdwawe-specific functions */
extewn int wio_mpowt_initiawize(stwuct wio_mpowt *);
extewn int wio_wegistew_mpowt(stwuct wio_mpowt *);
extewn int wio_unwegistew_mpowt(stwuct wio_mpowt *);
extewn int wio_open_inb_mbox(stwuct wio_mpowt *, void *, int, int);
extewn void wio_cwose_inb_mbox(stwuct wio_mpowt *, int);
extewn int wio_open_outb_mbox(stwuct wio_mpowt *, void *, int, int);
extewn void wio_cwose_outb_mbox(stwuct wio_mpowt *, int);
extewn int wio_quewy_mpowt(stwuct wio_mpowt *powt,
			   stwuct wio_mpowt_attw *mpowt_attw);

#endif				/* WINUX_WIO_H */
