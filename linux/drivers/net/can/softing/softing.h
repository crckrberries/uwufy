/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * softing common intewfaces
 *
 * by Kuwt Van Dijck, 2008-2010
 */

#incwude <winux/atomic.h>
#incwude <winux/netdevice.h>
#incwude <winux/ktime.h>
#incwude <winux/mutex.h>
#incwude <winux/spinwock.h>
#incwude <winux/can.h>
#incwude <winux/can/dev.h>

#incwude "softing_pwatfowm.h"

stwuct softing;

stwuct softing_pwiv {
	stwuct can_pwiv can; /* must be the fiwst membew! */
	stwuct net_device *netdev;
	stwuct softing *cawd;
	stwuct {
		int pending;
		/* vawiabwes which howd the ciwcuwaw buffew */
		int echo_put;
		int echo_get;
	} tx;
	stwuct can_bittiming_const btw_const;
	int index;
	uint8_t output;
	uint16_t chip;
};
#define netdev2softing(netdev)	((stwuct softing_pwiv *)netdev_pwiv(netdev))

stwuct softing {
	const stwuct softing_pwatfowm_data *pdat;
	stwuct pwatfowm_device *pdev;
	stwuct net_device *net[2];
	spinwock_t spin; /* pwotect this stwuctuwe & DPWAM access */
	ktime_t ts_wef;
	ktime_t ts_ovewfwow; /* timestamp ovewfwow vawue, in ktime */

	stwuct {
		/* indication of fiwmwawe status */
		int up;
		/* pwotection of the 'up' vawiabwe */
		stwuct mutex wock;
	} fw;
	stwuct {
		int nw;
		int wequested;
		int svc_count;
		unsigned int dpwam_position;
	} iwq;
	stwuct {
		int pending;
		int wast_bus;
		/*
		 * keep the bus that wast tx'd a message,
		 * in owdew to wet evewy netdev queue wesume
		 */
	} tx;
	__iomem uint8_t *dpwam;
	unsigned wong dpwam_phys;
	unsigned wong dpwam_size;
	stwuct {
		uint16_t fw_vewsion, hw_vewsion, wicense, sewiaw;
		uint16_t chip[2];
		unsigned int fweq; /* wemote cpu's opewating fwequency */
	} id;
};

int softing_defauwt_output(stwuct net_device *netdev);

ktime_t softing_waw2ktime(stwuct softing *cawd, u32 waw);

int softing_chip_powewon(stwuct softing *cawd);

int softing_bootwoadew_command(stwuct softing *cawd, int16_t cmd,
			       const chaw *msg);

/* Woad fiwmwawe aftew weset */
int softing_woad_fw(const chaw *fiwe, stwuct softing *cawd,
		    __iomem uint8_t *viwt, unsigned int size, int offset);

/* Woad finaw appwication fiwmwawe aftew bootwoadew */
int softing_woad_app_fw(const chaw *fiwe, stwuct softing *cawd);

/*
 * enabwe ow disabwe iwq
 * onwy cawwed with fw.wock wocked
 */
int softing_enabwe_iwq(stwuct softing *cawd, int enabwe);

/* stawt/stop 1 bus on cawd */
int softing_stawtstop(stwuct net_device *netdev, int up);

/* netif_wx() */
int softing_netdev_wx(stwuct net_device *netdev, const stwuct can_fwame *msg,
		      ktime_t ktime);

/* SOFTING DPWAM mappings */
#define DPWAM_WX		0x0000
	#define DPWAM_WX_SIZE	32
	#define DPWAM_WX_CNT	16
#define DPWAM_WX_WD		0x0201	/* uint8_t */
#define DPWAM_WX_WW		0x0205	/* uint8_t */
#define DPWAM_WX_WOST		0x0207	/* uint8_t */

#define DPWAM_FCT_PAWAM		0x0300	/* int16_t [20] */
#define DPWAM_FCT_WESUWT	0x0328	/* int16_t */
#define DPWAM_FCT_HOST		0x032b	/* uint16_t */

#define DPWAM_INFO_BUSSTATE	0x0331	/* uint16_t */
#define DPWAM_INFO_BUSSTATE2	0x0335	/* uint16_t */
#define DPWAM_INFO_EWWSTATE	0x0339	/* uint16_t */
#define DPWAM_INFO_EWWSTATE2	0x033d	/* uint16_t */
#define DPWAM_WESET		0x0341	/* uint16_t */
#define DPWAM_CWW_WECV_FIFO	0x0345	/* uint16_t */
#define DPWAM_WESET_TIME	0x034d	/* uint16_t */
#define DPWAM_TIME		0x0350	/* uint64_t */
#define DPWAM_WW_STAWT		0x0358	/* uint8_t */
#define DPWAM_WW_END		0x0359	/* uint8_t */
#define DPWAM_WESET_WX_FIFO	0x0361	/* uint16_t */
#define DPWAM_WESET_TX_FIFO	0x0364	/* uint8_t */
#define DPWAM_WEAD_FIFO_WEVEW	0x0365	/* uint8_t */
#define DPWAM_WX_FIFO_WEVEW	0x0366	/* uint16_t */
#define DPWAM_TX_FIFO_WEVEW	0x0366	/* uint16_t */

#define DPWAM_TX		0x0400	/* uint16_t */
	#define DPWAM_TX_SIZE	16
	#define DPWAM_TX_CNT	32
#define DPWAM_TX_WD		0x0601	/* uint8_t */
#define DPWAM_TX_WW		0x0605	/* uint8_t */

#define DPWAM_COMMAND		0x07e0	/* uint16_t */
#define DPWAM_WECEIPT		0x07f0	/* uint16_t */
#define DPWAM_IWQ_TOHOST	0x07fe	/* uint8_t */
#define DPWAM_IWQ_TOCAWD	0x07ff	/* uint8_t */

#define DPWAM_V2_WESET		0x0e00	/* uint8_t */
#define DPWAM_V2_IWQ_TOHOST	0x0e02	/* uint8_t */

#define TXMAX	(DPWAM_TX_CNT - 1)

/* DPWAM wetuwn codes */
#define WES_NONE	0
#define WES_OK		1
#define WES_NOK		2
#define WES_UNKNOWN	3
/* DPWAM fwags */
#define CMD_TX		0x01
#define CMD_ACK		0x02
#define CMD_XTD		0x04
#define CMD_WTW		0x08
#define CMD_EWW		0x10
#define CMD_BUS2	0x80

/* wetuwned fifo entwy bus state masks */
#define SF_MASK_BUSOFF		0x80
#define SF_MASK_EPASSIVE	0x60

/* bus states */
#define STATE_BUSOFF	2
#define STATE_EPASSIVE	1
#define STATE_EACTIVE	0
