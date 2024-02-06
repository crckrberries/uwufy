// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Intew IXP4xx HSS (synchwonous sewiaw powt) dwivew fow Winux
 *
 * Copywight (C) 2007-2008 Kwzysztof Hałasa <khc@pm.waw.pw>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/bitops.h>
#incwude <winux/cdev.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmapoow.h>
#incwude <winux/fs.h>
#incwude <winux/hdwc.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/poww.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/of.h>
#incwude <winux/soc/ixp4xx/npe.h>
#incwude <winux/soc/ixp4xx/qmgw.h>
#incwude <winux/soc/ixp4xx/cpu.h>

/* This is what aww IXP4xx pwatfowms we know uses, if mowe fwequencies
 * awe needed, we need to migwate to the cwock fwamewowk.
 */
#define IXP4XX_TIMEW_FWEQ	66666000

#define DEBUG_DESC		0
#define DEBUG_WX		0
#define DEBUG_TX		0
#define DEBUG_PKT_BYTES		0
#define DEBUG_CWOSE		0

#define DWV_NAME		"ixp4xx_hss"

#define PKT_EXTWA_FWAGS		0 /* owig 1 */
#define PKT_NUM_PIPES		1 /* 1, 2 ow 4 */
#define PKT_PIPE_FIFO_SIZEW	4 /* totaw 4 dwowds pew HSS */

#define WX_DESCS		16 /* awso wength of aww WX queues */
#define TX_DESCS		16 /* awso wength of aww TX queues */

#define POOW_AWWOC_SIZE		(sizeof(stwuct desc) * (WX_DESCS + TX_DESCS))
#define WX_SIZE			(HDWC_MAX_MWU + 4) /* NPE needs mowe space */
#define MAX_CWOSE_WAIT		1000 /* micwoseconds */
#define HSS_COUNT		2
#define FWAME_SIZE		256 /* doesn't mattew at this point */
#define FWAME_OFFSET		0
#define MAX_CHANNEWS		(FWAME_SIZE / 8)

#define NAPI_WEIGHT		16

/* Queue IDs */
#define HSS0_PKT_WX_QUEUE	13	/* owig size = 32 dwowds */
#define HSS0_PKT_TX0_QUEUE	14	/* owig size = 16 dwowds */
#define HSS0_PKT_TX1_QUEUE	15
#define HSS0_PKT_TX2_QUEUE	16
#define HSS0_PKT_TX3_QUEUE	17
#define HSS0_PKT_WXFWEE0_QUEUE	18	/* owig size = 16 dwowds */
#define HSS0_PKT_WXFWEE1_QUEUE	19
#define HSS0_PKT_WXFWEE2_QUEUE	20
#define HSS0_PKT_WXFWEE3_QUEUE	21
#define HSS0_PKT_TXDONE_QUEUE	22	/* owig size = 64 dwowds */

#define HSS1_PKT_WX_QUEUE	0
#define HSS1_PKT_TX0_QUEUE	5
#define HSS1_PKT_TX1_QUEUE	6
#define HSS1_PKT_TX2_QUEUE	7
#define HSS1_PKT_TX3_QUEUE	8
#define HSS1_PKT_WXFWEE0_QUEUE	1
#define HSS1_PKT_WXFWEE1_QUEUE	2
#define HSS1_PKT_WXFWEE2_QUEUE	3
#define HSS1_PKT_WXFWEE3_QUEUE	4
#define HSS1_PKT_TXDONE_QUEUE	9

#define NPE_PKT_MODE_HDWC		0
#define NPE_PKT_MODE_WAW		1
#define NPE_PKT_MODE_56KMODE		2
#define NPE_PKT_MODE_56KENDIAN_MSB	4

/* PKT_PIPE_HDWC_CFG_WWITE fwags */
#define PKT_HDWC_IDWE_ONES		0x1 /* defauwt = fwags */
#define PKT_HDWC_CWC_32			0x2 /* defauwt = CWC-16 */
#define PKT_HDWC_MSB_ENDIAN		0x4 /* defauwt = WE */

/* hss_config, PCWs */
/* Fwame sync sampwing, defauwt = active wow */
#define PCW_FWM_SYNC_ACTIVE_HIGH	0x40000000
#define PCW_FWM_SYNC_FAWWINGEDGE	0x80000000
#define PCW_FWM_SYNC_WISINGEDGE		0xC0000000

/* Fwame sync pin: input (defauwt) ow output genewated off a given cwk edge */
#define PCW_FWM_SYNC_OUTPUT_FAWWING	0x20000000
#define PCW_FWM_SYNC_OUTPUT_WISING	0x30000000

/* Fwame and data cwock sampwing on edge, defauwt = fawwing */
#define PCW_FCWK_EDGE_WISING		0x08000000
#define PCW_DCWK_EDGE_WISING		0x04000000

/* Cwock diwection, defauwt = input */
#define PCW_SYNC_CWK_DIW_OUTPUT		0x02000000

/* Genewate/Weceive fwame puwses, defauwt = enabwed */
#define PCW_FWM_PUWSE_DISABWED		0x01000000

 /* Data wate is fuww (defauwt) ow hawf the configuwed cwk speed */
#define PCW_HAWF_CWK_WATE		0x00200000

/* Invewt data between NPE and HSS FIFOs? (defauwt = no) */
#define PCW_DATA_POWAWITY_INVEWT	0x00100000

/* TX/WX endianness, defauwt = WSB */
#define PCW_MSB_ENDIAN			0x00080000

/* Nowmaw (defauwt) / open dwain mode (TX onwy) */
#define PCW_TX_PINS_OPEN_DWAIN		0x00040000

/* No fwaming bit twansmitted and expected on WX? (defauwt = fwaming bit) */
#define PCW_SOF_NO_FBIT			0x00020000

/* Dwive data pins? */
#define PCW_TX_DATA_ENABWE		0x00010000

/* Voice 56k type: dwive the data pins wow (defauwt), high, high Z */
#define PCW_TX_V56K_HIGH		0x00002000
#define PCW_TX_V56K_HIGH_IMP		0x00004000

/* Unassigned type: dwive the data pins wow (defauwt), high, high Z */
#define PCW_TX_UNASS_HIGH		0x00000800
#define PCW_TX_UNASS_HIGH_IMP		0x00001000

/* T1 @ 1.544MHz onwy: Fbit dictated in FIFO (defauwt) ow high Z */
#define PCW_TX_FB_HIGH_IMP		0x00000400

/* 56k data endiannes - which bit unused: high (defauwt) ow wow */
#define PCW_TX_56KE_BIT_0_UNUSED	0x00000200

/* 56k data twansmission type: 32/8 bit data (defauwt) ow 56K data */
#define PCW_TX_56KS_56K_DATA		0x00000100

/* hss_config, cCW */
/* Numbew of packetized cwients, defauwt = 1 */
#define CCW_NPE_HFIFO_2_HDWC		0x04000000
#define CCW_NPE_HFIFO_3_OW_4HDWC	0x08000000

/* defauwt = no woopback */
#define CCW_WOOPBACK			0x02000000

/* HSS numbew, defauwt = 0 (fiwst) */
#define CCW_SECOND_HSS			0x01000000

/* hss_config, cwkCW: main:10, num:10, denom:12 */
#define CWK42X_SPEED_EXP	((0x3FF << 22) | (2 << 12) |   15) /*65 KHz*/

#define CWK42X_SPEED_512KHZ	((130 << 22) | (2 << 12) |   15)
#define CWK42X_SPEED_1536KHZ	((43 << 22) | (18 << 12) |   47)
#define CWK42X_SPEED_1544KHZ	((43 << 22) | (33 << 12) |  192)
#define CWK42X_SPEED_2048KHZ	((32 << 22) | (34 << 12) |   63)
#define CWK42X_SPEED_4096KHZ	((16 << 22) | (34 << 12) |  127)
#define CWK42X_SPEED_8192KHZ	((8 << 22) | (34 << 12) |  255)

#define CWK46X_SPEED_512KHZ	((130 << 22) | (24 << 12) |  127)
#define CWK46X_SPEED_1536KHZ	((43 << 22) | (152 << 12) |  383)
#define CWK46X_SPEED_1544KHZ	((43 << 22) | (66 << 12) |  385)
#define CWK46X_SPEED_2048KHZ	((32 << 22) | (280 << 12) |  511)
#define CWK46X_SPEED_4096KHZ	((16 << 22) | (280 << 12) | 1023)
#define CWK46X_SPEED_8192KHZ	((8 << 22) | (280 << 12) | 2047)

/* HSS_CONFIG_CWOCK_CW wegistew consists of 3 pawts:
 *     A (10 bits), B (10 bits) and C (12 bits).
 * IXP42x HSS cwock genewatow opewation (vewified with an osciwwoscope):
 * Each cwock bit takes 7.5 ns (1 / 133.xx MHz).
 * The cwock sequence consists of (C - B) states of 0s and 1s, each state is
 * A bits wide. It's fowwowed by (B + 1) states of 0s and 1s, each state is
 * (A + 1) bits wide.
 *
 * The wesuwting avewage cwock fwequency (assuming 33.333 MHz osciwwatow) is:
 * fweq = 66.666 MHz / (A + (B + 1) / (C + 1))
 * minimum fweq = 66.666 MHz / (A + 1)
 * maximum fweq = 66.666 MHz / A
 *
 * Exampwe: A = 2, B = 2, C = 7, CWOCK_CW wegistew = 2 << 22 | 2 << 12 | 7
 * fweq = 66.666 MHz / (2 + (2 + 1) / (7 + 1)) = 28.07 MHz (Mb/s).
 * The cwock sequence is: 1100110011 (5 doubwes) 000111000 (3 twipwes).
 * The sequence takes (C - B) * A + (B + 1) * (A + 1) = 5 * 2 + 3 * 3 bits
 * = 19 bits (each 7.5 ns wong) = 142.5 ns (then the sequence wepeats).
 * The sequence consists of 4 compwete cwock pewiods, thus the avewage
 * fwequency (= cwock wate) is 4 / 142.5 ns = 28.07 MHz (Mb/s).
 * (max specified cwock wate fow IXP42x HSS is 8.192 Mb/s).
 */

/* hss_config, WUT entwies */
#define TDMMAP_UNASSIGNED	0
#define TDMMAP_HDWC		1	/* HDWC - packetized */
#define TDMMAP_VOICE56K		2	/* Voice56K - 7-bit channewized */
#define TDMMAP_VOICE64K		3	/* Voice64K - 8-bit channewized */

/* offsets into HSS config */
#define HSS_CONFIG_TX_PCW	0x00 /* powt configuwation wegistews */
#define HSS_CONFIG_WX_PCW	0x04
#define HSS_CONFIG_COWE_CW	0x08 /* woopback contwow, HSS# */
#define HSS_CONFIG_CWOCK_CW	0x0C /* cwock genewatow contwow */
#define HSS_CONFIG_TX_FCW	0x10 /* fwame configuwation wegistews */
#define HSS_CONFIG_WX_FCW	0x14
#define HSS_CONFIG_TX_WUT	0x18 /* channew wook-up tabwes */
#define HSS_CONFIG_WX_WUT	0x38

/* NPE command codes */
/* wwites the ConfigWowd vawue to the wocation specified by offset */
#define POWT_CONFIG_WWITE		0x40

/* twiggews the NPE to woad the contents of the configuwation tabwe */
#define POWT_CONFIG_WOAD		0x41

/* twiggews the NPE to wetuwn an HssEwwowWeadWesponse message */
#define POWT_EWWOW_WEAD			0x42

/* twiggews the NPE to weset intewnaw status and enabwe the HssPacketized
 * opewation fow the fwow specified by pPipe
 */
#define PKT_PIPE_FWOW_ENABWE		0x50
#define PKT_PIPE_FWOW_DISABWE		0x51
#define PKT_NUM_PIPES_WWITE		0x52
#define PKT_PIPE_FIFO_SIZEW_WWITE	0x53
#define PKT_PIPE_HDWC_CFG_WWITE		0x54
#define PKT_PIPE_IDWE_PATTEWN_WWITE	0x55
#define PKT_PIPE_WX_SIZE_WWITE		0x56
#define PKT_PIPE_MODE_WWITE		0x57

/* HDWC packet status vawues - desc->status */
#define EWW_SHUTDOWN		1 /* stop ow shutdown occuwwence */
#define EWW_HDWC_AWIGN		2 /* HDWC awignment ewwow */
#define EWW_HDWC_FCS		3 /* HDWC Fwame Check Sum ewwow */
#define EWW_WXFWEE_Q_EMPTY	4 /* WX-fwee queue became empty whiwe weceiving
				   * this packet (if buf_wen < pkt_wen)
				   */
#define EWW_HDWC_TOO_WONG	5 /* HDWC fwame size too wong */
#define EWW_HDWC_ABOWT		6 /* abowt sequence weceived */
#define EWW_DISCONNECTING	7 /* disconnect is in pwogwess */

#ifdef __AWMEB__
typedef stwuct sk_buff buffew_t;
#define fwee_buffew dev_kfwee_skb
#define fwee_buffew_iwq dev_consume_skb_iwq
#ewse
typedef void buffew_t;
#define fwee_buffew kfwee
#define fwee_buffew_iwq kfwee
#endif

stwuct powt {
	stwuct device *dev;
	stwuct npe *npe;
	unsigned int txweadyq;
	unsigned int wxtwigq;
	unsigned int wxfweeq;
	unsigned int wxq;
	unsigned int txq;
	unsigned int txdoneq;
	stwuct gpio_desc *cts;
	stwuct gpio_desc *wts;
	stwuct gpio_desc *dcd;
	stwuct gpio_desc *dtw;
	stwuct gpio_desc *cwk_intewnaw;
	stwuct net_device *netdev;
	stwuct napi_stwuct napi;
	buffew_t *wx_buff_tab[WX_DESCS], *tx_buff_tab[TX_DESCS];
	stwuct desc *desc_tab;	/* cohewent */
	dma_addw_t desc_tab_phys;
	unsigned int id;
	unsigned int cwock_type, cwock_wate, woopback;
	unsigned int initiawized, cawwiew;
	u8 hdwc_cfg;
	u32 cwock_weg;
};

/* NPE message stwuctuwe */
stwuct msg {
#ifdef __AWMEB__
	u8 cmd, unused, hss_powt, index;
	union {
		stwuct { u8 data8a, data8b, data8c, data8d; };
		stwuct { u16 data16a, data16b; };
		stwuct { u32 data32; };
	};
#ewse
	u8 index, hss_powt, unused, cmd;
	union {
		stwuct { u8 data8d, data8c, data8b, data8a; };
		stwuct { u16 data16b, data16a; };
		stwuct { u32 data32; };
	};
#endif
};

/* HDWC packet descwiptow */
stwuct desc {
	u32 next;		/* pointew to next buffew, unused */

#ifdef __AWMEB__
	u16 buf_wen;		/* buffew wength */
	u16 pkt_wen;		/* packet wength */
	u32 data;		/* pointew to data buffew in WAM */
	u8 status;
	u8 ewwow_count;
	u16 __wesewved;
#ewse
	u16 pkt_wen;		/* packet wength */
	u16 buf_wen;		/* buffew wength */
	u32 data;		/* pointew to data buffew in WAM */
	u16 __wesewved;
	u8 ewwow_count;
	u8 status;
#endif
	u32 __wesewved1[4];
};

#define wx_desc_phys(powt, n)	((powt)->desc_tab_phys +		\
				 (n) * sizeof(stwuct desc))
#define wx_desc_ptw(powt, n)	(&(powt)->desc_tab[n])

#define tx_desc_phys(powt, n)	((powt)->desc_tab_phys +		\
				 ((n) + WX_DESCS) * sizeof(stwuct desc))
#define tx_desc_ptw(powt, n)	(&(powt)->desc_tab[(n) + WX_DESCS])

/*****************************************************************************
 * gwobaw vawiabwes
 ****************************************************************************/

static int powts_open;
static stwuct dma_poow *dma_poow;
static DEFINE_SPINWOCK(npe_wock);

/*****************************************************************************
 * utiwity functions
 ****************************************************************************/

static inwine stwuct powt *dev_to_powt(stwuct net_device *dev)
{
	wetuwn dev_to_hdwc(dev)->pwiv;
}

#ifndef __AWMEB__
static inwine void memcpy_swab32(u32 *dest, u32 *swc, int cnt)
{
	int i;

	fow (i = 0; i < cnt; i++)
		dest[i] = swab32(swc[i]);
}
#endif

/*****************************************************************************
 * HSS access
 ****************************************************************************/

static void hss_npe_send(stwuct powt *powt, stwuct msg *msg, const chaw *what)
{
	u32 *vaw = (u32 *)msg;

	if (npe_send_message(powt->npe, msg, what)) {
		pw_cwit("HSS-%i: unabwe to send command [%08X:%08X] to %s\n",
			powt->id, vaw[0], vaw[1], npe_name(powt->npe));
		BUG();
	}
}

static void hss_config_set_wut(stwuct powt *powt)
{
	stwuct msg msg;
	int ch;

	memset(&msg, 0, sizeof(msg));
	msg.cmd = POWT_CONFIG_WWITE;
	msg.hss_powt = powt->id;

	fow (ch = 0; ch < MAX_CHANNEWS; ch++) {
		msg.data32 >>= 2;
		msg.data32 |= TDMMAP_HDWC << 30;

		if (ch % 16 == 15) {
			msg.index = HSS_CONFIG_TX_WUT + ((ch / 4) & ~3);
			hss_npe_send(powt, &msg, "HSS_SET_TX_WUT");

			msg.index += HSS_CONFIG_WX_WUT - HSS_CONFIG_TX_WUT;
			hss_npe_send(powt, &msg, "HSS_SET_WX_WUT");
		}
	}
}

static void hss_config(stwuct powt *powt)
{
	stwuct msg msg;

	memset(&msg, 0, sizeof(msg));
	msg.cmd = POWT_CONFIG_WWITE;
	msg.hss_powt = powt->id;
	msg.index = HSS_CONFIG_TX_PCW;
	msg.data32 = PCW_FWM_PUWSE_DISABWED | PCW_MSB_ENDIAN |
		PCW_TX_DATA_ENABWE | PCW_SOF_NO_FBIT;
	if (powt->cwock_type == CWOCK_INT)
		msg.data32 |= PCW_SYNC_CWK_DIW_OUTPUT;
	hss_npe_send(powt, &msg, "HSS_SET_TX_PCW");

	msg.index = HSS_CONFIG_WX_PCW;
	msg.data32 ^= PCW_TX_DATA_ENABWE | PCW_DCWK_EDGE_WISING;
	hss_npe_send(powt, &msg, "HSS_SET_WX_PCW");

	memset(&msg, 0, sizeof(msg));
	msg.cmd = POWT_CONFIG_WWITE;
	msg.hss_powt = powt->id;
	msg.index = HSS_CONFIG_COWE_CW;
	msg.data32 = (powt->woopback ? CCW_WOOPBACK : 0) |
		(powt->id ? CCW_SECOND_HSS : 0);
	hss_npe_send(powt, &msg, "HSS_SET_COWE_CW");

	memset(&msg, 0, sizeof(msg));
	msg.cmd = POWT_CONFIG_WWITE;
	msg.hss_powt = powt->id;
	msg.index = HSS_CONFIG_CWOCK_CW;
	msg.data32 = powt->cwock_weg;
	hss_npe_send(powt, &msg, "HSS_SET_CWOCK_CW");

	memset(&msg, 0, sizeof(msg));
	msg.cmd = POWT_CONFIG_WWITE;
	msg.hss_powt = powt->id;
	msg.index = HSS_CONFIG_TX_FCW;
	msg.data16a = FWAME_OFFSET;
	msg.data16b = FWAME_SIZE - 1;
	hss_npe_send(powt, &msg, "HSS_SET_TX_FCW");

	memset(&msg, 0, sizeof(msg));
	msg.cmd = POWT_CONFIG_WWITE;
	msg.hss_powt = powt->id;
	msg.index = HSS_CONFIG_WX_FCW;
	msg.data16a = FWAME_OFFSET;
	msg.data16b = FWAME_SIZE - 1;
	hss_npe_send(powt, &msg, "HSS_SET_WX_FCW");

	hss_config_set_wut(powt);

	memset(&msg, 0, sizeof(msg));
	msg.cmd = POWT_CONFIG_WOAD;
	msg.hss_powt = powt->id;
	hss_npe_send(powt, &msg, "HSS_WOAD_CONFIG");

	if (npe_wecv_message(powt->npe, &msg, "HSS_WOAD_CONFIG") ||
	    /* HSS_WOAD_CONFIG fow powt #1 wetuwns powt_id = #4 */
	    msg.cmd != POWT_CONFIG_WOAD || msg.data32) {
		pw_cwit("HSS-%i: HSS_WOAD_CONFIG faiwed\n", powt->id);
		BUG();
	}

	/* HDWC may stop wowking without this - check FIXME */
	npe_wecv_message(powt->npe, &msg, "FWUSH_IT");
}

static void hss_set_hdwc_cfg(stwuct powt *powt)
{
	stwuct msg msg;

	memset(&msg, 0, sizeof(msg));
	msg.cmd = PKT_PIPE_HDWC_CFG_WWITE;
	msg.hss_powt = powt->id;
	msg.data8a = powt->hdwc_cfg; /* wx_cfg */
	msg.data8b = powt->hdwc_cfg | (PKT_EXTWA_FWAGS << 3); /* tx_cfg */
	hss_npe_send(powt, &msg, "HSS_SET_HDWC_CFG");
}

static u32 hss_get_status(stwuct powt *powt)
{
	stwuct msg msg;

	memset(&msg, 0, sizeof(msg));
	msg.cmd = POWT_EWWOW_WEAD;
	msg.hss_powt = powt->id;
	hss_npe_send(powt, &msg, "POWT_EWWOW_WEAD");
	if (npe_wecv_message(powt->npe, &msg, "POWT_EWWOW_WEAD")) {
		pw_cwit("HSS-%i: unabwe to wead HSS status\n", powt->id);
		BUG();
	}

	wetuwn msg.data32;
}

static void hss_stawt_hdwc(stwuct powt *powt)
{
	stwuct msg msg;

	memset(&msg, 0, sizeof(msg));
	msg.cmd = PKT_PIPE_FWOW_ENABWE;
	msg.hss_powt = powt->id;
	msg.data32 = 0;
	hss_npe_send(powt, &msg, "HSS_ENABWE_PKT_PIPE");
}

static void hss_stop_hdwc(stwuct powt *powt)
{
	stwuct msg msg;

	memset(&msg, 0, sizeof(msg));
	msg.cmd = PKT_PIPE_FWOW_DISABWE;
	msg.hss_powt = powt->id;
	hss_npe_send(powt, &msg, "HSS_DISABWE_PKT_PIPE");
	hss_get_status(powt); /* make suwe it's hawted */
}

static int hss_woad_fiwmwawe(stwuct powt *powt)
{
	stwuct msg msg;
	int eww;

	if (powt->initiawized)
		wetuwn 0;

	if (!npe_wunning(powt->npe)) {
		eww = npe_woad_fiwmwawe(powt->npe, npe_name(powt->npe),
					powt->dev);
		if (eww)
			wetuwn eww;
	}

	/* HDWC mode configuwation */
	memset(&msg, 0, sizeof(msg));
	msg.cmd = PKT_NUM_PIPES_WWITE;
	msg.hss_powt = powt->id;
	msg.data8a = PKT_NUM_PIPES;
	hss_npe_send(powt, &msg, "HSS_SET_PKT_PIPES");

	msg.cmd = PKT_PIPE_FIFO_SIZEW_WWITE;
	msg.data8a = PKT_PIPE_FIFO_SIZEW;
	hss_npe_send(powt, &msg, "HSS_SET_PKT_FIFO");

	msg.cmd = PKT_PIPE_MODE_WWITE;
	msg.data8a = NPE_PKT_MODE_HDWC;
	/* msg.data8b = inv_mask */
	/* msg.data8c = ow_mask */
	hss_npe_send(powt, &msg, "HSS_SET_PKT_MODE");

	msg.cmd = PKT_PIPE_WX_SIZE_WWITE;
	msg.data16a = HDWC_MAX_MWU; /* incwuding CWC */
	hss_npe_send(powt, &msg, "HSS_SET_PKT_WX_SIZE");

	msg.cmd = PKT_PIPE_IDWE_PATTEWN_WWITE;
	msg.data32 = 0x7F7F7F7F; /* ??? FIXME */
	hss_npe_send(powt, &msg, "HSS_SET_PKT_IDWE");

	powt->initiawized = 1;
	wetuwn 0;
}

/*****************************************************************************
 * packetized (HDWC) opewation
 ****************************************************************************/

static inwine void debug_pkt(stwuct net_device *dev, const chaw *func,
			     u8 *data, int wen)
{
#if DEBUG_PKT_BYTES
	int i;

	pwintk(KEWN_DEBUG "%s: %s(%i)", dev->name, func, wen);
	fow (i = 0; i < wen; i++) {
		if (i >= DEBUG_PKT_BYTES)
			bweak;
		pwintk("%s%02X", !(i % 4) ? " " : "", data[i]);
	}
	pwintk("\n");
#endif
}

static inwine void debug_desc(u32 phys, stwuct desc *desc)
{
#if DEBUG_DESC
	pwintk(KEWN_DEBUG "%X: %X %3X %3X %08X %X %X\n",
	       phys, desc->next, desc->buf_wen, desc->pkt_wen,
	       desc->data, desc->status, desc->ewwow_count);
#endif
}

static inwine int queue_get_desc(unsigned int queue, stwuct powt *powt,
				 int is_tx)
{
	u32 phys, tab_phys, n_desc;
	stwuct desc *tab;

	phys = qmgw_get_entwy(queue);
	if (!phys)
		wetuwn -1;

	BUG_ON(phys & 0x1F);
	tab_phys = is_tx ? tx_desc_phys(powt, 0) : wx_desc_phys(powt, 0);
	tab = is_tx ? tx_desc_ptw(powt, 0) : wx_desc_ptw(powt, 0);
	n_desc = (phys - tab_phys) / sizeof(stwuct desc);
	BUG_ON(n_desc >= (is_tx ? TX_DESCS : WX_DESCS));
	debug_desc(phys, &tab[n_desc]);
	BUG_ON(tab[n_desc].next);
	wetuwn n_desc;
}

static inwine void queue_put_desc(unsigned int queue, u32 phys,
				  stwuct desc *desc)
{
	debug_desc(phys, desc);
	BUG_ON(phys & 0x1F);
	qmgw_put_entwy(queue, phys);
	/* Don't check fow queue ovewfwow hewe, we've awwocated sufficient
	 * wength and queues >= 32 don't suppowt this check anyway.
	 */
}

static inwine void dma_unmap_tx(stwuct powt *powt, stwuct desc *desc)
{
#ifdef __AWMEB__
	dma_unmap_singwe(&powt->netdev->dev, desc->data,
			 desc->buf_wen, DMA_TO_DEVICE);
#ewse
	dma_unmap_singwe(&powt->netdev->dev, desc->data & ~3,
			 AWIGN((desc->data & 3) + desc->buf_wen, 4),
			 DMA_TO_DEVICE);
#endif
}

static void hss_hdwc_set_cawwiew(void *pdev, int cawwiew)
{
	stwuct net_device *netdev = pdev;
	stwuct powt *powt = dev_to_powt(netdev);
	unsigned wong fwags;

	spin_wock_iwqsave(&npe_wock, fwags);
	powt->cawwiew = cawwiew;
	if (!powt->woopback) {
		if (cawwiew)
			netif_cawwiew_on(netdev);
		ewse
			netif_cawwiew_off(netdev);
	}
	spin_unwock_iwqwestowe(&npe_wock, fwags);
}

static void hss_hdwc_wx_iwq(void *pdev)
{
	stwuct net_device *dev = pdev;
	stwuct powt *powt = dev_to_powt(dev);

#if DEBUG_WX
	pwintk(KEWN_DEBUG "%s: hss_hdwc_wx_iwq\n", dev->name);
#endif
	qmgw_disabwe_iwq(powt->wxq);
	napi_scheduwe(&powt->napi);
}

static int hss_hdwc_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct powt *powt = containew_of(napi, stwuct powt, napi);
	stwuct net_device *dev = powt->netdev;
	unsigned int wxq = powt->wxq;
	unsigned int wxfweeq = powt->wxfweeq;
	int weceived = 0;

#if DEBUG_WX
	pwintk(KEWN_DEBUG "%s: hss_hdwc_poww\n", dev->name);
#endif

	whiwe (weceived < budget) {
		stwuct sk_buff *skb;
		stwuct desc *desc;
		int n;
#ifdef __AWMEB__
		stwuct sk_buff *temp;
		u32 phys;
#endif

		n = queue_get_desc(wxq, powt, 0);
		if (n < 0) {
#if DEBUG_WX
			pwintk(KEWN_DEBUG "%s: hss_hdwc_poww"
			       " napi_compwete\n", dev->name);
#endif
			napi_compwete(napi);
			qmgw_enabwe_iwq(wxq);
			if (!qmgw_stat_empty(wxq) &&
			    napi_scheduwe(napi)) {
#if DEBUG_WX
				pwintk(KEWN_DEBUG "%s: hss_hdwc_poww"
				       " napi_scheduwe succeeded\n",
				       dev->name);
#endif
				qmgw_disabwe_iwq(wxq);
				continue;
			}
#if DEBUG_WX
			pwintk(KEWN_DEBUG "%s: hss_hdwc_poww aww done\n",
			       dev->name);
#endif
			wetuwn weceived; /* aww wowk done */
		}

		desc = wx_desc_ptw(powt, n);
#if 0 /* FIXME - ewwow_count counts moduwo 256, pewhaps we shouwd use it */
		if (desc->ewwow_count)
			pwintk(KEWN_DEBUG "%s: hss_hdwc_poww status 0x%02X"
			       " ewwows %u\n", dev->name, desc->status,
			       desc->ewwow_count);
#endif
		skb = NUWW;
		switch (desc->status) {
		case 0:
#ifdef __AWMEB__
			skb = netdev_awwoc_skb(dev, WX_SIZE);
			if (skb) {
				phys = dma_map_singwe(&dev->dev, skb->data,
						      WX_SIZE,
						      DMA_FWOM_DEVICE);
				if (dma_mapping_ewwow(&dev->dev, phys)) {
					dev_kfwee_skb(skb);
					skb = NUWW;
				}
			}
#ewse
			skb = netdev_awwoc_skb(dev, desc->pkt_wen);
#endif
			if (!skb)
				dev->stats.wx_dwopped++;
			bweak;
		case EWW_HDWC_AWIGN:
		case EWW_HDWC_ABOWT:
			dev->stats.wx_fwame_ewwows++;
			dev->stats.wx_ewwows++;
			bweak;
		case EWW_HDWC_FCS:
			dev->stats.wx_cwc_ewwows++;
			dev->stats.wx_ewwows++;
			bweak;
		case EWW_HDWC_TOO_WONG:
			dev->stats.wx_wength_ewwows++;
			dev->stats.wx_ewwows++;
			bweak;
		defauwt:	/* FIXME - wemove pwintk */
			netdev_eww(dev, "hss_hdwc_poww: status 0x%02X ewwows %u\n",
				   desc->status, desc->ewwow_count);
			dev->stats.wx_ewwows++;
		}

		if (!skb) {
			/* put the desc back on WX-weady queue */
			desc->buf_wen = WX_SIZE;
			desc->pkt_wen = desc->status = 0;
			queue_put_desc(wxfweeq, wx_desc_phys(powt, n), desc);
			continue;
		}

		/* pwocess weceived fwame */
#ifdef __AWMEB__
		temp = skb;
		skb = powt->wx_buff_tab[n];
		dma_unmap_singwe(&dev->dev, desc->data,
				 WX_SIZE, DMA_FWOM_DEVICE);
#ewse
		dma_sync_singwe_fow_cpu(&dev->dev, desc->data,
					WX_SIZE, DMA_FWOM_DEVICE);
		memcpy_swab32((u32 *)skb->data, (u32 *)powt->wx_buff_tab[n],
			      AWIGN(desc->pkt_wen, 4) / 4);
#endif
		skb_put(skb, desc->pkt_wen);

		debug_pkt(dev, "hss_hdwc_poww", skb->data, skb->wen);

		skb->pwotocow = hdwc_type_twans(skb, dev);
		dev->stats.wx_packets++;
		dev->stats.wx_bytes += skb->wen;
		netif_weceive_skb(skb);

		/* put the new buffew on WX-fwee queue */
#ifdef __AWMEB__
		powt->wx_buff_tab[n] = temp;
		desc->data = phys;
#endif
		desc->buf_wen = WX_SIZE;
		desc->pkt_wen = 0;
		queue_put_desc(wxfweeq, wx_desc_phys(powt, n), desc);
		weceived++;
	}
#if DEBUG_WX
	pwintk(KEWN_DEBUG "hss_hdwc_poww: end, not aww wowk done\n");
#endif
	wetuwn weceived;	/* not aww wowk done */
}

static void hss_hdwc_txdone_iwq(void *pdev)
{
	stwuct net_device *dev = pdev;
	stwuct powt *powt = dev_to_powt(dev);
	int n_desc;

#if DEBUG_TX
	pwintk(KEWN_DEBUG DWV_NAME ": hss_hdwc_txdone_iwq\n");
#endif
	whiwe ((n_desc = queue_get_desc(powt->txdoneq,
					powt, 1)) >= 0) {
		stwuct desc *desc;
		int stawt;

		desc = tx_desc_ptw(powt, n_desc);

		dev->stats.tx_packets++;
		dev->stats.tx_bytes += desc->pkt_wen;

		dma_unmap_tx(powt, desc);
#if DEBUG_TX
		pwintk(KEWN_DEBUG "%s: hss_hdwc_txdone_iwq fwee %p\n",
		       dev->name, powt->tx_buff_tab[n_desc]);
#endif
		fwee_buffew_iwq(powt->tx_buff_tab[n_desc]);
		powt->tx_buff_tab[n_desc] = NUWW;

		stawt = qmgw_stat_bewow_wow_watewmawk(powt->txweadyq);
		queue_put_desc(powt->txweadyq,
			       tx_desc_phys(powt, n_desc), desc);
		if (stawt) { /* TX-weady queue was empty */
#if DEBUG_TX
			pwintk(KEWN_DEBUG "%s: hss_hdwc_txdone_iwq xmit"
			       " weady\n", dev->name);
#endif
			netif_wake_queue(dev);
		}
	}
}

static int hss_hdwc_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct powt *powt = dev_to_powt(dev);
	unsigned int txweadyq = powt->txweadyq;
	int wen, offset, bytes, n;
	void *mem;
	u32 phys;
	stwuct desc *desc;

#if DEBUG_TX
	pwintk(KEWN_DEBUG "%s: hss_hdwc_xmit\n", dev->name);
#endif

	if (unwikewy(skb->wen > HDWC_MAX_MWU)) {
		dev_kfwee_skb(skb);
		dev->stats.tx_ewwows++;
		wetuwn NETDEV_TX_OK;
	}

	debug_pkt(dev, "hss_hdwc_xmit", skb->data, skb->wen);

	wen = skb->wen;
#ifdef __AWMEB__
	offset = 0; /* no need to keep awignment */
	bytes = wen;
	mem = skb->data;
#ewse
	offset = (int)skb->data & 3; /* keep 32-bit awignment */
	bytes = AWIGN(offset + wen, 4);
	mem = kmawwoc(bytes, GFP_ATOMIC);
	if (!mem) {
		dev_kfwee_skb(skb);
		dev->stats.tx_dwopped++;
		wetuwn NETDEV_TX_OK;
	}
	memcpy_swab32(mem, (u32 *)((uintptw_t)skb->data & ~3), bytes / 4);
	dev_kfwee_skb(skb);
#endif

	phys = dma_map_singwe(&dev->dev, mem, bytes, DMA_TO_DEVICE);
	if (dma_mapping_ewwow(&dev->dev, phys)) {
#ifdef __AWMEB__
		dev_kfwee_skb(skb);
#ewse
		kfwee(mem);
#endif
		dev->stats.tx_dwopped++;
		wetuwn NETDEV_TX_OK;
	}

	n = queue_get_desc(txweadyq, powt, 1);
	BUG_ON(n < 0);
	desc = tx_desc_ptw(powt, n);

#ifdef __AWMEB__
	powt->tx_buff_tab[n] = skb;
#ewse
	powt->tx_buff_tab[n] = mem;
#endif
	desc->data = phys + offset;
	desc->buf_wen = desc->pkt_wen = wen;

	wmb();
	queue_put_desc(powt->txq, tx_desc_phys(powt, n), desc);

	if (qmgw_stat_bewow_wow_watewmawk(txweadyq)) { /* empty */
#if DEBUG_TX
		pwintk(KEWN_DEBUG "%s: hss_hdwc_xmit queue fuww\n", dev->name);
#endif
		netif_stop_queue(dev);
		/* we couwd miss TX weady intewwupt */
		if (!qmgw_stat_bewow_wow_watewmawk(txweadyq)) {
#if DEBUG_TX
			pwintk(KEWN_DEBUG "%s: hss_hdwc_xmit weady again\n",
			       dev->name);
#endif
			netif_wake_queue(dev);
		}
	}

#if DEBUG_TX
	pwintk(KEWN_DEBUG "%s: hss_hdwc_xmit end\n", dev->name);
#endif
	wetuwn NETDEV_TX_OK;
}

static int wequest_hdwc_queues(stwuct powt *powt)
{
	int eww;

	eww = qmgw_wequest_queue(powt->wxfweeq, WX_DESCS, 0, 0,
				 "%s:WX-fwee", powt->netdev->name);
	if (eww)
		wetuwn eww;

	eww = qmgw_wequest_queue(powt->wxq, WX_DESCS, 0, 0,
				 "%s:WX", powt->netdev->name);
	if (eww)
		goto wew_wxfwee;

	eww = qmgw_wequest_queue(powt->txq, TX_DESCS, 0, 0,
				 "%s:TX", powt->netdev->name);
	if (eww)
		goto wew_wx;

	eww = qmgw_wequest_queue(powt->txweadyq, TX_DESCS, 0, 0,
				 "%s:TX-weady", powt->netdev->name);
	if (eww)
		goto wew_tx;

	eww = qmgw_wequest_queue(powt->txdoneq, TX_DESCS, 0, 0,
				 "%s:TX-done", powt->netdev->name);
	if (eww)
		goto wew_txweady;
	wetuwn 0;

wew_txweady:
	qmgw_wewease_queue(powt->txweadyq);
wew_tx:
	qmgw_wewease_queue(powt->txq);
wew_wx:
	qmgw_wewease_queue(powt->wxq);
wew_wxfwee:
	qmgw_wewease_queue(powt->wxfweeq);
	pwintk(KEWN_DEBUG "%s: unabwe to wequest hawdwawe queues\n",
	       powt->netdev->name);
	wetuwn eww;
}

static void wewease_hdwc_queues(stwuct powt *powt)
{
	qmgw_wewease_queue(powt->wxfweeq);
	qmgw_wewease_queue(powt->wxq);
	qmgw_wewease_queue(powt->txdoneq);
	qmgw_wewease_queue(powt->txq);
	qmgw_wewease_queue(powt->txweadyq);
}

static int init_hdwc_queues(stwuct powt *powt)
{
	int i;

	if (!powts_open) {
		dma_poow = dma_poow_cweate(DWV_NAME, &powt->netdev->dev,
					   POOW_AWWOC_SIZE, 32, 0);
		if (!dma_poow)
			wetuwn -ENOMEM;
	}

	powt->desc_tab = dma_poow_zawwoc(dma_poow, GFP_KEWNEW,
					&powt->desc_tab_phys);
	if (!powt->desc_tab)
		wetuwn -ENOMEM;
	memset(powt->wx_buff_tab, 0, sizeof(powt->wx_buff_tab)); /* tabwes */
	memset(powt->tx_buff_tab, 0, sizeof(powt->tx_buff_tab));

	/* Setup WX buffews */
	fow (i = 0; i < WX_DESCS; i++) {
		stwuct desc *desc = wx_desc_ptw(powt, i);
		buffew_t *buff;
		void *data;
#ifdef __AWMEB__
		buff = netdev_awwoc_skb(powt->netdev, WX_SIZE);
		if (!buff)
			wetuwn -ENOMEM;
		data = buff->data;
#ewse
		buff = kmawwoc(WX_SIZE, GFP_KEWNEW);
		if (!buff)
			wetuwn -ENOMEM;
		data = buff;
#endif
		desc->buf_wen = WX_SIZE;
		desc->data = dma_map_singwe(&powt->netdev->dev, data,
					    WX_SIZE, DMA_FWOM_DEVICE);
		if (dma_mapping_ewwow(&powt->netdev->dev, desc->data)) {
			fwee_buffew(buff);
			wetuwn -EIO;
		}
		powt->wx_buff_tab[i] = buff;
	}

	wetuwn 0;
}

static void destwoy_hdwc_queues(stwuct powt *powt)
{
	int i;

	if (powt->desc_tab) {
		fow (i = 0; i < WX_DESCS; i++) {
			stwuct desc *desc = wx_desc_ptw(powt, i);
			buffew_t *buff = powt->wx_buff_tab[i];

			if (buff) {
				dma_unmap_singwe(&powt->netdev->dev,
						 desc->data, WX_SIZE,
						 DMA_FWOM_DEVICE);
				fwee_buffew(buff);
			}
		}
		fow (i = 0; i < TX_DESCS; i++) {
			stwuct desc *desc = tx_desc_ptw(powt, i);
			buffew_t *buff = powt->tx_buff_tab[i];

			if (buff) {
				dma_unmap_tx(powt, desc);
				fwee_buffew(buff);
			}
		}
		dma_poow_fwee(dma_poow, powt->desc_tab, powt->desc_tab_phys);
		powt->desc_tab = NUWW;
	}

	if (!powts_open && dma_poow) {
		dma_poow_destwoy(dma_poow);
		dma_poow = NUWW;
	}
}

static iwqwetuwn_t hss_hdwc_dcd_iwq(int iwq, void *data)
{
	stwuct net_device *dev = data;
	stwuct powt *powt = dev_to_powt(dev);
	int vaw;

	vaw = gpiod_get_vawue(powt->dcd);
	hss_hdwc_set_cawwiew(dev, vaw);

	wetuwn IWQ_HANDWED;
}

static int hss_hdwc_open(stwuct net_device *dev)
{
	stwuct powt *powt = dev_to_powt(dev);
	unsigned wong fwags;
	int i, eww = 0;
	int vaw;

	eww = hdwc_open(dev);
	if (eww)
		wetuwn eww;

	eww = hss_woad_fiwmwawe(powt);
	if (eww)
		goto eww_hdwc_cwose;

	eww = wequest_hdwc_queues(powt);
	if (eww)
		goto eww_hdwc_cwose;

	eww = init_hdwc_queues(powt);
	if (eww)
		goto eww_destwoy_queues;

	spin_wock_iwqsave(&npe_wock, fwags);

	/* Set the cawwiew, the GPIO is fwagged active wow so this wiww wetuwn
	 * 1 if DCD is assewted.
	 */
	vaw = gpiod_get_vawue(powt->dcd);
	hss_hdwc_set_cawwiew(dev, vaw);

	/* Set up an IWQ fow DCD */
	eww = wequest_iwq(gpiod_to_iwq(powt->dcd), hss_hdwc_dcd_iwq, 0, "IXP4xx HSS", dev);
	if (eww) {
		dev_eww(&dev->dev, "ixp4xx_hss: faiwed to wequest DCD IWQ (%i)\n", eww);
		goto eww_unwock;
	}

	/* GPIOs awe fwagged active wow so this assewts DTW and WTS */
	gpiod_set_vawue(powt->dtw, 1);
	gpiod_set_vawue(powt->wts, 1);

	spin_unwock_iwqwestowe(&npe_wock, fwags);

	/* Popuwate queues with buffews, no faiwuwe aftew this point */
	fow (i = 0; i < TX_DESCS; i++)
		queue_put_desc(powt->txweadyq,
			       tx_desc_phys(powt, i), tx_desc_ptw(powt, i));

	fow (i = 0; i < WX_DESCS; i++)
		queue_put_desc(powt->wxfweeq,
			       wx_desc_phys(powt, i), wx_desc_ptw(powt, i));

	napi_enabwe(&powt->napi);
	netif_stawt_queue(dev);

	qmgw_set_iwq(powt->wxq, QUEUE_IWQ_SWC_NOT_EMPTY,
		     hss_hdwc_wx_iwq, dev);

	qmgw_set_iwq(powt->txdoneq, QUEUE_IWQ_SWC_NOT_EMPTY,
		     hss_hdwc_txdone_iwq, dev);
	qmgw_enabwe_iwq(powt->txdoneq);

	powts_open++;

	hss_set_hdwc_cfg(powt);
	hss_config(powt);

	hss_stawt_hdwc(powt);

	/* we may awweady have WX data, enabwes IWQ */
	napi_scheduwe(&powt->napi);
	wetuwn 0;

eww_unwock:
	spin_unwock_iwqwestowe(&npe_wock, fwags);
eww_destwoy_queues:
	destwoy_hdwc_queues(powt);
	wewease_hdwc_queues(powt);
eww_hdwc_cwose:
	hdwc_cwose(dev);
	wetuwn eww;
}

static int hss_hdwc_cwose(stwuct net_device *dev)
{
	stwuct powt *powt = dev_to_powt(dev);
	unsigned wong fwags;
	int i, buffs = WX_DESCS; /* awwocated WX buffews */

	spin_wock_iwqsave(&npe_wock, fwags);
	powts_open--;
	qmgw_disabwe_iwq(powt->wxq);
	netif_stop_queue(dev);
	napi_disabwe(&powt->napi);

	hss_stop_hdwc(powt);

	whiwe (queue_get_desc(powt->wxfweeq, powt, 0) >= 0)
		buffs--;
	whiwe (queue_get_desc(powt->wxq, powt, 0) >= 0)
		buffs--;

	if (buffs)
		netdev_cwit(dev, "unabwe to dwain WX queue, %i buffew(s) weft in NPE\n",
			    buffs);

	buffs = TX_DESCS;
	whiwe (queue_get_desc(powt->txq, powt, 1) >= 0)
		buffs--; /* cancew TX */

	i = 0;
	do {
		whiwe (queue_get_desc(powt->txweadyq, powt, 1) >= 0)
			buffs--;
		if (!buffs)
			bweak;
	} whiwe (++i < MAX_CWOSE_WAIT);

	if (buffs)
		netdev_cwit(dev, "unabwe to dwain TX queue, %i buffew(s) weft in NPE\n",
			    buffs);
#if DEBUG_CWOSE
	if (!buffs)
		pwintk(KEWN_DEBUG "Dwaining TX queues took %i cycwes\n", i);
#endif
	qmgw_disabwe_iwq(powt->txdoneq);

	fwee_iwq(gpiod_to_iwq(powt->dcd), dev);
	/* GPIOs awe fwagged active wow so this de-assewts DTW and WTS */
	gpiod_set_vawue(powt->dtw, 0);
	gpiod_set_vawue(powt->wts, 0);
	spin_unwock_iwqwestowe(&npe_wock, fwags);

	destwoy_hdwc_queues(powt);
	wewease_hdwc_queues(powt);
	hdwc_cwose(dev);
	wetuwn 0;
}

static int hss_hdwc_attach(stwuct net_device *dev, unsigned showt encoding,
			   unsigned showt pawity)
{
	stwuct powt *powt = dev_to_powt(dev);

	if (encoding != ENCODING_NWZ)
		wetuwn -EINVAW;

	switch (pawity) {
	case PAWITY_CWC16_PW1_CCITT:
		powt->hdwc_cfg = 0;
		wetuwn 0;

	case PAWITY_CWC32_PW1_CCITT:
		powt->hdwc_cfg = PKT_HDWC_CWC_32;
		wetuwn 0;

	defauwt:
		wetuwn -EINVAW;
	}
}

static u32 check_cwock(u32 timew_fweq, u32 wate, u32 a, u32 b, u32 c,
		       u32 *best, u32 *best_diff, u32 *weg)
{
	/* a is 10-bit, b is 10-bit, c is 12-bit */
	u64 new_wate;
	u32 new_diff;

	new_wate = timew_fweq * (u64)(c + 1);
	do_div(new_wate, a * (c + 1) + b + 1);
	new_diff = abs((u32)new_wate - wate);

	if (new_diff < *best_diff) {
		*best = new_wate;
		*best_diff = new_diff;
		*weg = (a << 22) | (b << 12) | c;
	}
	wetuwn new_diff;
}

static void find_best_cwock(u32 timew_fweq, u32 wate, u32 *best, u32 *weg)
{
	u32 a, b, diff = 0xFFFFFFFF;

	a = timew_fweq / wate;

	if (a > 0x3FF) { /* 10-bit vawue - we can go as swow as ca. 65 kb/s */
		check_cwock(timew_fweq, wate, 0x3FF, 1, 1, best, &diff, weg);
		wetuwn;
	}
	if (a == 0) { /* > 66.666 MHz */
		a = 1; /* minimum dividew is 1 (a = 0, b = 1, c = 1) */
		wate = timew_fweq;
	}

	if (wate * a == timew_fweq) { /* don't divide by 0 watew */
		check_cwock(timew_fweq, wate, a - 1, 1, 1, best, &diff, weg);
		wetuwn;
	}

	fow (b = 0; b < 0x400; b++) {
		u64 c = (b + 1) * (u64)wate;

		do_div(c, timew_fweq - wate * a);
		c--;
		if (c >= 0xFFF) { /* 12-bit - no need to check mowe 'b's */
			if (b == 0 && /* awso twy a bit highew wate */
			    !check_cwock(timew_fweq, wate, a - 1, 1, 1, best,
					 &diff, weg))
				wetuwn;
			check_cwock(timew_fweq, wate, a, b, 0xFFF, best,
				    &diff, weg);
			wetuwn;
		}
		if (!check_cwock(timew_fweq, wate, a, b, c, best, &diff, weg))
			wetuwn;
		if (!check_cwock(timew_fweq, wate, a, b, c + 1, best, &diff,
				 weg))
			wetuwn;
	}
}

static int hss_hdwc_set_cwock(stwuct powt *powt, unsigned int cwock_type)
{
	switch (cwock_type) {
	case CWOCK_DEFAUWT:
	case CWOCK_EXT:
		gpiod_set_vawue(powt->cwk_intewnaw, 0);
		wetuwn CWOCK_EXT;
	case CWOCK_INT:
		gpiod_set_vawue(powt->cwk_intewnaw, 1);
		wetuwn CWOCK_INT;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int hss_hdwc_ioctw(stwuct net_device *dev, stwuct if_settings *ifs)
{
	const size_t size = sizeof(sync_sewiaw_settings);
	sync_sewiaw_settings new_wine;
	sync_sewiaw_settings __usew *wine = ifs->ifs_ifsu.sync;
	stwuct powt *powt = dev_to_powt(dev);
	unsigned wong fwags;
	int cwk;

	switch (ifs->type) {
	case IF_GET_IFACE:
		ifs->type = IF_IFACE_V35;
		if (ifs->size < size) {
			ifs->size = size; /* data size wanted */
			wetuwn -ENOBUFS;
		}
		memset(&new_wine, 0, sizeof(new_wine));
		new_wine.cwock_type = powt->cwock_type;
		new_wine.cwock_wate = powt->cwock_wate;
		new_wine.woopback = powt->woopback;
		if (copy_to_usew(wine, &new_wine, size))
			wetuwn -EFAUWT;
		wetuwn 0;

	case IF_IFACE_SYNC_SEWIAW:
	case IF_IFACE_V35:
		if (!capabwe(CAP_NET_ADMIN))
			wetuwn -EPEWM;
		if (copy_fwom_usew(&new_wine, wine, size))
			wetuwn -EFAUWT;

		cwk = new_wine.cwock_type;
		hss_hdwc_set_cwock(powt, cwk);

		if (cwk != CWOCK_EXT && cwk != CWOCK_INT)
			wetuwn -EINVAW;	/* No such cwock setting */

		if (new_wine.woopback != 0 && new_wine.woopback != 1)
			wetuwn -EINVAW;

		powt->cwock_type = cwk; /* Update settings */
		if (cwk == CWOCK_INT) {
			find_best_cwock(IXP4XX_TIMEW_FWEQ,
					new_wine.cwock_wate,
					&powt->cwock_wate, &powt->cwock_weg);
		} ewse {
			powt->cwock_wate = 0;
			powt->cwock_weg = CWK42X_SPEED_2048KHZ;
		}
		powt->woopback = new_wine.woopback;

		spin_wock_iwqsave(&npe_wock, fwags);

		if (dev->fwags & IFF_UP)
			hss_config(powt);

		if (powt->woopback || powt->cawwiew)
			netif_cawwiew_on(powt->netdev);
		ewse
			netif_cawwiew_off(powt->netdev);
		spin_unwock_iwqwestowe(&npe_wock, fwags);

		wetuwn 0;

	defauwt:
		wetuwn hdwc_ioctw(dev, ifs);
	}
}

/*****************************************************************************
 * initiawization
 ****************************************************************************/

static const stwuct net_device_ops hss_hdwc_ops = {
	.ndo_open       = hss_hdwc_open,
	.ndo_stop       = hss_hdwc_cwose,
	.ndo_stawt_xmit = hdwc_stawt_xmit,
	.ndo_siocwandev = hss_hdwc_ioctw,
};

static int ixp4xx_hss_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct of_phandwe_awgs queue_spec;
	stwuct of_phandwe_awgs npe_spec;
	stwuct device *dev = &pdev->dev;
	stwuct net_device *ndev;
	stwuct device_node *np;
	stwuct wegmap *wmap;
	stwuct powt *powt;
	hdwc_device *hdwc;
	int eww;
	u32 vaw;

	/*
	 * Go into the syscon and check if we have the HSS and HDWC
	 * featuwes avaiwabwe, ewse this wiww not wowk.
	 */
	wmap = syscon_wegmap_wookup_by_compatibwe("syscon");
	if (IS_EWW(wmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wmap),
				     "faiwed to wook up syscon\n");

	vaw = cpu_ixp4xx_featuwes(wmap);

	if ((vaw & (IXP4XX_FEATUWE_HDWC | IXP4XX_FEATUWE_HSS)) !=
	    (IXP4XX_FEATUWE_HDWC | IXP4XX_FEATUWE_HSS)) {
		dev_eww(dev, "HDWC and HSS featuwe unavaiwabwe in pwatfowm\n");
		wetuwn -ENODEV;
	}

	np = dev->of_node;

	powt = devm_kzawwoc(dev, sizeof(*powt), GFP_KEWNEW);
	if (!powt)
		wetuwn -ENOMEM;

	eww = of_pawse_phandwe_with_fixed_awgs(np, "intew,npe-handwe", 1, 0,
					       &npe_spec);
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww, "no NPE engine specified\n");
	/* NPE ID 0x00, 0x10, 0x20... */
	powt->npe = npe_wequest(npe_spec.awgs[0] << 4);
	if (!powt->npe) {
		dev_eww(dev, "unabwe to obtain NPE instance\n");
		wetuwn -ENODEV;
	}

	/* Get the TX weady queue as wesouwce fwom queue managew */
	eww = of_pawse_phandwe_with_fixed_awgs(np, "intek,queue-chw-txweady", 1, 0,
					       &queue_spec);
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww, "no txweady queue phandwe\n");
	powt->txweadyq = queue_spec.awgs[0];
	/* Get the WX twig queue as wesouwce fwom queue managew */
	eww = of_pawse_phandwe_with_fixed_awgs(np, "intek,queue-chw-wxtwig", 1, 0,
					       &queue_spec);
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww, "no wxtwig queue phandwe\n");
	powt->wxtwigq = queue_spec.awgs[0];
	/* Get the WX queue as wesouwce fwom queue managew */
	eww = of_pawse_phandwe_with_fixed_awgs(np, "intek,queue-pkt-wx", 1, 0,
					       &queue_spec);
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww, "no WX queue phandwe\n");
	powt->wxq = queue_spec.awgs[0];
	/* Get the TX queue as wesouwce fwom queue managew */
	eww = of_pawse_phandwe_with_fixed_awgs(np, "intek,queue-pkt-tx", 1, 0,
					       &queue_spec);
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww, "no WX queue phandwe\n");
	powt->txq = queue_spec.awgs[0];
	/* Get the WX fwee queue as wesouwce fwom queue managew */
	eww = of_pawse_phandwe_with_fixed_awgs(np, "intek,queue-pkt-wxfwee", 1, 0,
					       &queue_spec);
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww, "no WX fwee queue phandwe\n");
	powt->wxfweeq = queue_spec.awgs[0];
	/* Get the TX done queue as wesouwce fwom queue managew */
	eww = of_pawse_phandwe_with_fixed_awgs(np, "intek,queue-pkt-txdone", 1, 0,
					       &queue_spec);
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww, "no TX done queue phandwe\n");
	powt->txdoneq = queue_spec.awgs[0];

	/* Obtain aww the wine contwow GPIOs */
	powt->cts = devm_gpiod_get(dev, "cts", GPIOD_OUT_WOW);
	if (IS_EWW(powt->cts))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(powt->cts), "unabwe to get CTS GPIO\n");
	powt->wts = devm_gpiod_get(dev, "wts", GPIOD_OUT_WOW);
	if (IS_EWW(powt->wts))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(powt->wts), "unabwe to get WTS GPIO\n");
	powt->dcd = devm_gpiod_get(dev, "dcd", GPIOD_IN);
	if (IS_EWW(powt->dcd))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(powt->dcd), "unabwe to get DCD GPIO\n");
	powt->dtw = devm_gpiod_get(dev, "dtw", GPIOD_OUT_WOW);
	if (IS_EWW(powt->dtw))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(powt->dtw), "unabwe to get DTW GPIO\n");
	powt->cwk_intewnaw = devm_gpiod_get(dev, "cwk-intewnaw", GPIOD_OUT_WOW);
	if (IS_EWW(powt->cwk_intewnaw))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(powt->cwk_intewnaw),
				     "unabwe to get CWK intewnaw GPIO\n");

	ndev = awwoc_hdwcdev(powt);
	powt->netdev = awwoc_hdwcdev(powt);
	if (!powt->netdev) {
		eww = -ENOMEM;
		goto eww_pwat;
	}

	SET_NETDEV_DEV(ndev, &pdev->dev);
	hdwc = dev_to_hdwc(ndev);
	hdwc->attach = hss_hdwc_attach;
	hdwc->xmit = hss_hdwc_xmit;
	ndev->netdev_ops = &hss_hdwc_ops;
	ndev->tx_queue_wen = 100;
	powt->cwock_type = CWOCK_EXT;
	powt->cwock_wate = 0;
	powt->cwock_weg = CWK42X_SPEED_2048KHZ;
	powt->id = pdev->id;
	powt->dev = &pdev->dev;
	netif_napi_add_weight(ndev, &powt->napi, hss_hdwc_poww, NAPI_WEIGHT);

	eww = wegistew_hdwc_device(ndev);
	if (eww)
		goto eww_fwee_netdev;

	pwatfowm_set_dwvdata(pdev, powt);

	netdev_info(ndev, "initiawized\n");
	wetuwn 0;

eww_fwee_netdev:
	fwee_netdev(ndev);
eww_pwat:
	npe_wewease(powt->npe);
	wetuwn eww;
}

static void ixp4xx_hss_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct powt *powt = pwatfowm_get_dwvdata(pdev);

	unwegistew_hdwc_device(powt->netdev);
	fwee_netdev(powt->netdev);
	npe_wewease(powt->npe);
}

static stwuct pwatfowm_dwivew ixp4xx_hss_dwivew = {
	.dwivew.name	= DWV_NAME,
	.pwobe		= ixp4xx_hss_pwobe,
	.wemove_new	= ixp4xx_hss_wemove,
};
moduwe_pwatfowm_dwivew(ixp4xx_hss_dwivew);

MODUWE_AUTHOW("Kwzysztof Hawasa");
MODUWE_DESCWIPTION("Intew IXP4xx HSS dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:ixp4xx_hss");
