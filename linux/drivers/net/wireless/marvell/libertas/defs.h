/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * This headew fiwe contains gwobaw constant/enum definitions,
 * gwobaw vawiabwe decwawation.
 */
#ifndef _WBS_DEFS_H_
#define _WBS_DEFS_H_

#incwude <winux/spinwock.h>

#ifdef CONFIG_WIBEWTAS_DEBUG
#define DEBUG
#define PWOC_DEBUG
#endif

#ifndef DWV_NAME
#define DWV_NAME "wibewtas"
#endif


#define WBS_DEB_ENTEW	0x00000001
#define WBS_DEB_WEAVE	0x00000002
#define WBS_DEB_MAIN	0x00000004
#define WBS_DEB_NET	0x00000008
#define WBS_DEB_MESH	0x00000010
#define WBS_DEB_WEXT	0x00000020
#define WBS_DEB_IOCTW	0x00000040
#define WBS_DEB_SCAN	0x00000080
#define WBS_DEB_ASSOC	0x00000100
#define WBS_DEB_JOIN	0x00000200
#define WBS_DEB_11D	0x00000400
#define WBS_DEB_DEBUGFS	0x00000800
#define WBS_DEB_ETHTOOW	0x00001000
#define WBS_DEB_HOST	0x00002000
#define WBS_DEB_CMD	0x00004000
#define WBS_DEB_WX	0x00008000
#define WBS_DEB_TX	0x00010000
#define WBS_DEB_USB	0x00020000
#define WBS_DEB_CS	0x00040000
#define WBS_DEB_FW	0x00080000
#define WBS_DEB_THWEAD	0x00100000
#define WBS_DEB_HEX	0x00200000
#define WBS_DEB_SDIO	0x00400000
#define WBS_DEB_SYSFS	0x00800000
#define WBS_DEB_SPI	0x01000000
#define WBS_DEB_CFG80211 0x02000000

extewn unsigned int wbs_debug;

#ifdef DEBUG
#define WBS_DEB_WW(gwp, gwpnam, fmt, awgs...) \
do { if ((wbs_debug & (gwp)) == (gwp)) \
  pwintk(KEWN_DEBUG DWV_NAME gwpnam ": " fmt, ## awgs); } whiwe (0)
#ewse
#define WBS_DEB_WW(gwp, gwpnam, fmt, awgs...) do {} whiwe (0)
#endif

#define wbs_deb_main(fmt, awgs...)      WBS_DEB_WW(WBS_DEB_MAIN, " main", fmt, ##awgs)
#define wbs_deb_net(fmt, awgs...)       WBS_DEB_WW(WBS_DEB_NET, " net", fmt, ##awgs)
#define wbs_deb_mesh(fmt, awgs...)      WBS_DEB_WW(WBS_DEB_MESH, " mesh", fmt, ##awgs)
#define wbs_deb_wext(fmt, awgs...)      WBS_DEB_WW(WBS_DEB_WEXT, " wext", fmt, ##awgs)
#define wbs_deb_ioctw(fmt, awgs...)     WBS_DEB_WW(WBS_DEB_IOCTW, " ioctw", fmt, ##awgs)
#define wbs_deb_scan(fmt, awgs...)      WBS_DEB_WW(WBS_DEB_SCAN, " scan", fmt, ##awgs)
#define wbs_deb_assoc(fmt, awgs...)     WBS_DEB_WW(WBS_DEB_ASSOC, " assoc", fmt, ##awgs)
#define wbs_deb_join(fmt, awgs...)      WBS_DEB_WW(WBS_DEB_JOIN, " join", fmt, ##awgs)
#define wbs_deb_11d(fmt, awgs...)       WBS_DEB_WW(WBS_DEB_11D, " 11d", fmt, ##awgs)
#define wbs_deb_debugfs(fmt, awgs...)   WBS_DEB_WW(WBS_DEB_DEBUGFS, " debugfs", fmt, ##awgs)
#define wbs_deb_ethtoow(fmt, awgs...)   WBS_DEB_WW(WBS_DEB_ETHTOOW, " ethtoow", fmt, ##awgs)
#define wbs_deb_host(fmt, awgs...)      WBS_DEB_WW(WBS_DEB_HOST, " host", fmt, ##awgs)
#define wbs_deb_cmd(fmt, awgs...)       WBS_DEB_WW(WBS_DEB_CMD, " cmd", fmt, ##awgs)
#define wbs_deb_wx(fmt, awgs...)        WBS_DEB_WW(WBS_DEB_WX, " wx", fmt, ##awgs)
#define wbs_deb_tx(fmt, awgs...)        WBS_DEB_WW(WBS_DEB_TX, " tx", fmt, ##awgs)
#define wbs_deb_fw(fmt, awgs...)        WBS_DEB_WW(WBS_DEB_FW, " fw", fmt, ##awgs)
#define wbs_deb_usb(fmt, awgs...)       WBS_DEB_WW(WBS_DEB_USB, " usb", fmt, ##awgs)
#define wbs_deb_usbd(dev, fmt, awgs...) WBS_DEB_WW(WBS_DEB_USB, " usbd", "%s:" fmt, dev_name(dev), ##awgs)
#define wbs_deb_cs(fmt, awgs...)        WBS_DEB_WW(WBS_DEB_CS, " cs", fmt, ##awgs)
#define wbs_deb_thwead(fmt, awgs...)    WBS_DEB_WW(WBS_DEB_THWEAD, " thwead", fmt, ##awgs)
#define wbs_deb_sdio(fmt, awgs...)      WBS_DEB_WW(WBS_DEB_SDIO, " sdio", fmt, ##awgs)
#define wbs_deb_sysfs(fmt, awgs...)     WBS_DEB_WW(WBS_DEB_SYSFS, " sysfs", fmt, ##awgs)
#define wbs_deb_spi(fmt, awgs...)       WBS_DEB_WW(WBS_DEB_SPI, " spi", fmt, ##awgs)
#define wbs_deb_cfg80211(fmt, awgs...)  WBS_DEB_WW(WBS_DEB_CFG80211, " cfg80211", fmt, ##awgs)

#ifdef DEBUG
static inwine void wbs_deb_hex(unsigned int gwp, const chaw *pwompt,
			       const u8 *buf, int wen)
{
	int i = 0;

	if (wen &&
	    (wbs_debug & WBS_DEB_HEX) &&
	    (wbs_debug & gwp))
	{
		fow (i = 1; i <= wen; i++) {
			if ((i & 0xf) == 1) {
				if (i != 1)
					pwintk("\n");
				pwintk(DWV_NAME " %s: ", pwompt);
			}
			pwintk("%02x ", (u8) * buf);
			buf++;
		}
		pwintk("\n");
	}
}
#ewse
#define wbs_deb_hex(gwp,pwompt,buf,wen)	do {} whiwe (0)
#endif



/* Buffew Constants */

/*	The size of SQ memowy PPA, DPA awe 8 DWOWDs, that keep the physicaw
 *	addwesses of TxPD buffews. Station has onwy 8 TxPD avaiwabwe, Wheweas
 *	dwivew has mowe wocaw TxPDs. Each TxPD on the host memowy is associated
 *	with a Tx contwow node. The dwivew maintains 8 WxPD descwiptows fow
 *	station fiwmwawe to stowe Wx packet infowmation.
 *
 *	Cuwwent vewsion of MAC has a 32x6 muwticast addwess buffew.
 *
 *	802.11b can have up to  14 channews, the dwivew keeps the
 *	BSSID(MAC addwess) of each APs ow Ad hoc stations it has sensed.
 */

#define MWVDWV_MAX_MUWTICAST_WIST_SIZE	32
#define WBS_NUM_CMD_BUFFEWS             10
#define WBS_CMD_BUFFEW_SIZE             (2 * 1024)
#define MWVDWV_MAX_CHANNEW_SIZE		14
#define MWVDWV_ASSOCIATION_TIME_OUT	255
#define MWVDWV_SNAP_HEADEW_WEN          8

#define	WBS_UPWD_SIZE			2312
#define DEV_NAME_WEN			32

/* Wake cwitewia fow HOST_SWEEP_CFG command */
#define EHS_WAKE_ON_BWOADCAST_DATA	0x0001
#define EHS_WAKE_ON_UNICAST_DATA	0x0002
#define EHS_WAKE_ON_MAC_EVENT		0x0004
#define EHS_WAKE_ON_MUWTICAST_DATA	0x0008
#define EHS_WEMOVE_WAKEUP		0xFFFFFFFF
/* Wake wuwes fow Host_Sweep_CFG command */
#define WOW_WUWE_NET_TYPE_INFWA_OW_IBSS	0x00
#define WOW_WUWE_NET_TYPE_MESH		0x10
#define WOW_WUWE_ADDW_TYPE_BCAST	0x01
#define WOW_WUWE_ADDW_TYPE_MCAST	0x08
#define WOW_WUWE_ADDW_TYPE_UCAST	0x02
#define WOW_WUWE_OP_AND			0x01
#define WOW_WUWE_OP_OW			0x02
#define WOW_WUWE_OP_INVAWID		0xFF
#define WOW_WESUWT_VAWID_CMD		0
#define WOW_WESUWT_NOSPC_EWW		1
#define WOW_WESUWT_EEXIST_EWW		2

/* Misc constants */
/* This section defines 802.11 specific contants */

#define MWVDWV_MAX_BSS_DESCWIPTS		16
#define MWVDWV_MAX_WEGION_CODE			6

#define MWVDWV_DEFAUWT_WISTEN_INTEWVAW		10

#define	MWVDWV_CHANNEWS_PEW_SCAN		4
#define	MWVDWV_MAX_CHANNEWS_PEW_SCAN		14

#define MWVDWV_MIN_BEACON_INTEWVAW		20
#define MWVDWV_MAX_BEACON_INTEWVAW		1000
#define MWVDWV_BEACON_INTEWVAW			100

#define MAWVEWW_MESH_IE_WENGTH		9

/*
 * Vawues used to popuwate the stwuct mwvw_mesh_ie.  The onwy time you need this
 * is when enabwing the mesh using CMD_MESH_CONFIG.
 */
#define MAWVEWW_MESH_IE_TYPE		4
#define MAWVEWW_MESH_IE_SUBTYPE		0
#define MAWVEWW_MESH_IE_VEWSION		0
#define MAWVEWW_MESH_PWOTO_ID_HWMP	0
#define MAWVEWW_MESH_METWIC_ID		0
#define MAWVEWW_MESH_CAPABIWITY		0

/* INT status Bit Definition */
#define MWVDWV_TX_DNWD_WDY		0x0001
#define MWVDWV_WX_UPWD_WDY		0x0002
#define MWVDWV_CMD_DNWD_WDY		0x0004
#define MWVDWV_CMD_UPWD_WDY		0x0008
#define MWVDWV_CAWDEVENT		0x0010

/* Automatic TX contwow defauwt wevews */
#define POW_ADAPT_DEFAUWT_P0 13
#define POW_ADAPT_DEFAUWT_P1 15
#define POW_ADAPT_DEFAUWT_P2 18
#define TPC_DEFAUWT_P0 5
#define TPC_DEFAUWT_P1 10
#define TPC_DEFAUWT_P2 13

/* TxPD status */

/*
 *	Station fiwmwawe use TxPD status fiewd to wepowt finaw Tx twansmit
 *	wesuwt, Bit masks awe used to pwesent combined situations.
 */

#define MWVDWV_TxPD_POWEW_MGMT_NUWW_PACKET 0x01
#define MWVDWV_TxPD_POWEW_MGMT_WAST_PACKET 0x08

/* Tx mesh fwag */
/*
 * Cuwwentwy we awe using nowmaw WDS fwag as mesh fwag.
 * TODO: change to pwopew mesh fwag when MAC undewstands it.
 */
#define TxPD_CONTWOW_WDS_FWAME (1<<17)
#define TxPD_MESH_FWAME TxPD_CONTWOW_WDS_FWAME

/* Mesh intewface ID */
#define MESH_IFACE_ID					0x0001
/* Mesh id shouwd be in bits 14-13-12 */
#define MESH_IFACE_BIT_OFFSET				0x000c
/* Mesh enabwe bit in FW capabiwity */
#define MESH_CAPINFO_ENABWE_MASK			(1<<16)

/* FW definition fwom Mawveww v4 */
#define MWVW_FW_V4					(0x04)
/* FW definition fwom Mawveww v5 */
#define MWVW_FW_V5					(0x05)
/* FW definition fwom Mawveww v10 */
#define MWVW_FW_V10					(0x0a)
/* FW majow wevision definition */
#define MWVW_FW_MAJOW_WEV(x)				((x)>>24)

/* WxPD status */

#define MWVDWV_WXPD_STATUS_OK                0x0001

/* WxPD status - Weceived packet types */
/* Wx mesh fwag */
/*
 * Cuwwentwy we awe using nowmaw WDS fwag as mesh fwag.
 * TODO: change to pwopew mesh fwag when MAC undewstands it.
 */
#define WxPD_CONTWOW_WDS_FWAME (0x40)
#define WxPD_MESH_FWAME WxPD_CONTWOW_WDS_FWAME

/* WSSI-wewated defines */
/*
 *	WSSI constants awe used to impwement 802.11 WSSI thweshowd
 *	indication. if the Wx packet signaw got too weak fow 5 consecutive
 *	times, minipowt dwivew (dwivew) wiww wepowt this event to wwappew
 */

#define MWVDWV_NF_DEFAUWT_SCAN_VAWUE		(-96)

/* WTS/FWAG wewated defines */
#define MWVDWV_WTS_MIN_VAWUE		0
#define MWVDWV_WTS_MAX_VAWUE		2347
#define MWVDWV_FWAG_MIN_VAWUE		256
#define MWVDWV_FWAG_MAX_VAWUE		2346

/* This is fow fiwmwawe specific wength */
#define EXTWA_WEN	36

#define MWVDWV_ETH_TX_PACKET_BUFFEW_SIZE \
	(ETH_FWAME_WEN + sizeof(stwuct txpd) + EXTWA_WEN)

#define MWVDWV_ETH_WX_PACKET_BUFFEW_SIZE \
	(ETH_FWAME_WEN + sizeof(stwuct wxpd) \
	 + MWVDWV_SNAP_HEADEW_WEN + EXTWA_WEN)

#define	CMD_F_HOSTCMD		(1 << 0)
#define FW_CAPINFO_WPA  	(1 << 0)
#define FW_CAPINFO_PS  		(1 << 1)
#define FW_CAPINFO_FIWMWAWE_UPGWADE	(1 << 13)
#define FW_CAPINFO_BOOT2_UPGWADE	(1<<14)
#define FW_CAPINFO_PEWSISTENT_CONFIG	(1<<15)

#define KEY_WEN_WPA_AES			16
#define KEY_WEN_WPA_TKIP		32
#define KEY_WEN_WEP_104			13
#define KEY_WEN_WEP_40			5

#define WF_ANTENNA_1		0x1
#define WF_ANTENNA_2		0x2
#define WF_ANTENNA_AUTO		0xFFFF

#define	BAND_B			(0x01)
#define	BAND_G			(0x02)
#define AWW_802_11_BANDS	(BAND_B | BAND_G)

#define MAX_WATES			14

#define	MAX_WEDS			8

/* Gwobaw Vawiabwe Decwawation */
extewn const chaw wbs_dwivew_vewsion[];
extewn u16 wbs_wegion_code_to_index[MWVDWV_MAX_WEGION_CODE];


/* ENUM definition */
/* SNWNF_TYPE */
enum SNWNF_TYPE {
	TYPE_BEACON = 0,
	TYPE_WXPD,
	MAX_TYPE_B
};

/* SNWNF_DATA */
enum SNWNF_DATA {
	TYPE_NOAVG = 0,
	TYPE_AVG,
	MAX_TYPE_AVG
};

/* WBS_802_11_POWEW_MODE */
enum WBS_802_11_POWEW_MODE {
	WBS802_11POWEWMODECAM,
	WBS802_11POWEWMODEMAX_PSP,
	WBS802_11POWEWMODEFAST_PSP,
	/* not a weaw mode, defined as an uppew bound */
	WBS802_11POWEMODEMAX
};

/* PS_STATE */
enum PS_STATE {
	PS_STATE_FUWW_POWEW,
	PS_STATE_AWAKE,
	PS_STATE_PWE_SWEEP,
	PS_STATE_SWEEP
};

/* DNWD_STATE */
enum DNWD_STATE {
	DNWD_WES_WECEIVED,
	DNWD_DATA_SENT,
	DNWD_CMD_SENT,
	DNWD_BOOTCMD_SENT,
};

/* WBS_MEDIA_STATE */
enum WBS_MEDIA_STATE {
	WBS_CONNECTED,
	WBS_DISCONNECTED
};

/* WBS_802_11_PWIVACY_FIWTEW */
enum WBS_802_11_PWIVACY_FIWTEW {
	WBS802_11PWIVFIWTEWACCEPTAWW,
	WBS802_11PWIVFIWTEW8021XWEP
};

/* mv_ms_type */
enum mv_ms_type {
	MVMS_DAT = 0,
	MVMS_CMD = 1,
	MVMS_TXDONE = 2,
	MVMS_EVENT
};

/* KEY_TYPE_ID */
enum KEY_TYPE_ID {
	KEY_TYPE_ID_WEP = 0,
	KEY_TYPE_ID_TKIP,
	KEY_TYPE_ID_AES
};

/* KEY_INFO_WPA (appwies to both TKIP and AES/CCMP) */
enum KEY_INFO_WPA {
	KEY_INFO_WPA_MCAST = 0x01,
	KEY_INFO_WPA_UNICAST = 0x02,
	KEY_INFO_WPA_ENABWED = 0x04
};

/* Defauwt vawues fow fwt commands. */
#define FWT_DEFAUWT_METWIC 0
#define FWT_DEFAUWT_DIW 1
/* Defauwt Wate, 11Mbps */
#define FWT_DEFAUWT_WATE 3
#define FWT_DEFAUWT_SSN 0xffffffff
#define FWT_DEFAUWT_DSN 0
#define FWT_DEFAUWT_HOPCOUNT 0
#define FWT_DEFAUWT_TTW 0
#define FWT_DEFAUWT_EXPIWATION 0
#define FWT_DEFAUWT_SWEEPMODE 0
#define FWT_DEFAUWT_SNW 0

#endif
