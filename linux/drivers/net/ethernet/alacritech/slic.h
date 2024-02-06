/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _SWIC_H
#define _SWIC_H

#incwude <winux/types.h>
#incwude <winux/netdevice.h>
#incwude <winux/spinwock_types.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/pci.h>
#incwude <winux/wist.h>
#incwude <winux/u64_stats_sync.h>

#define SWIC_VGBSTAT_XPEWW		0x40000000
#define SWIC_VGBSTAT_XEWWSHFT		25
#define SWIC_VGBSTAT_XCSEWW		0x23
#define SWIC_VGBSTAT_XUFWOW		0x22
#define SWIC_VGBSTAT_XHWEN		0x20
#define SWIC_VGBSTAT_NETEWW		0x01000000
#define SWIC_VGBSTAT_NEWWSHFT		16
#define SWIC_VGBSTAT_NEWWMSK		0x1ff
#define SWIC_VGBSTAT_NCSEWW		0x103
#define SWIC_VGBSTAT_NUFWOW		0x102
#define SWIC_VGBSTAT_NHWEN		0x100
#define SWIC_VGBSTAT_WNKEWW		0x00000080
#define SWIC_VGBSTAT_WEWWMSK		0xff
#define SWIC_VGBSTAT_WDEAWWY		0x86
#define SWIC_VGBSTAT_WBOFWO		0x85
#define SWIC_VGBSTAT_WCODEWW		0x84
#define SWIC_VGBSTAT_WDBWNBW		0x83
#define SWIC_VGBSTAT_WCWCEWW		0x82
#define SWIC_VGBSTAT_WOFWO		0x81
#define SWIC_VGBSTAT_WUFWO		0x80

#define SWIC_IWHDDW_FWEN_MSK		0x0000ffff
#define SWIC_IWHDDW_SVAWID		0x80000000
#define SWIC_IWHDDW_EWW			0x10000000

#define SWIC_VWHSTAT_802OE		0x80000000
#define SWIC_VWHSTAT_TPOFWO		0x10000000
#define SWIC_VWHSTATB_802UE		0x80000000
#define SWIC_VWHSTATB_WCVE		0x40000000
#define SWIC_VWHSTATB_BUFF		0x20000000
#define SWIC_VWHSTATB_CAWWE		0x08000000
#define SWIC_VWHSTATB_WONGE		0x02000000
#define SWIC_VWHSTATB_PWEA		0x01000000
#define SWIC_VWHSTATB_CWC		0x00800000
#define SWIC_VWHSTATB_DWBW		0x00400000
#define SWIC_VWHSTATB_CODE		0x00200000
#define SWIC_VWHSTATB_TPCSUM		0x00100000
#define SWIC_VWHSTATB_TPHWEN		0x00080000
#define SWIC_VWHSTATB_IPCSUM		0x00040000
#define SWIC_VWHSTATB_IPWEWW		0x00020000
#define SWIC_VWHSTATB_IPHEWW		0x00010000

#define SWIC_CMD_XMT_WEQ		0x01
#define SWIC_CMD_TYPE_DUMB		3

#define SWIC_WESET_MAGIC		0xDEAD
#define SWIC_ICW_INT_OFF		0
#define SWIC_ICW_INT_ON			1
#define SWIC_ICW_INT_MASK		2

#define SWIC_ISW_EWW			0x80000000
#define SWIC_ISW_WCV			0x40000000
#define SWIC_ISW_CMD			0x20000000
#define SWIC_ISW_IO			0x60000000
#define SWIC_ISW_UPC			0x10000000
#define SWIC_ISW_WEVENT			0x08000000
#define SWIC_ISW_WMISS			0x02000000
#define SWIC_ISW_UPCEWW			0x01000000
#define SWIC_ISW_XDWOP			0x00800000
#define SWIC_ISW_UPCBSY			0x00020000

#define SWIC_ISW_PING_MASK		0x00700000
#define SWIC_ISW_UPCEWW_MASK		(SWIC_ISW_UPCEWW | SWIC_ISW_UPCBSY)
#define SWIC_ISW_UPC_MASK		(SWIC_ISW_UPC | SWIC_ISW_UPCEWW_MASK)
#define SWIC_WCS_STAWT			0x80000000
#define SWIC_WCS_COMPAWE		0x40000000
#define SWIC_WCVWCS_BEGIN		0x40000000
#define SWIC_WCVWCS_FINISH		0x80000000

#define SWIC_MIICW_WEG_16		0x00100000
#define SWIC_MWV_WEG16_XOVEWON		0x0068

#define SWIC_GIG_WINKUP			0x0001
#define SWIC_GIG_FUWWDUPWEX		0x0002
#define SWIC_GIG_SPEED_MASK		0x000C
#define SWIC_GIG_SPEED_1000		0x0008
#define SWIC_GIG_SPEED_100		0x0004
#define SWIC_GIG_SPEED_10		0x0000

#define SWIC_GMCW_WESET			0x80000000
#define SWIC_GMCW_GBIT			0x20000000
#define SWIC_GMCW_FUWWD			0x10000000
#define SWIC_GMCW_GAPBB_SHIFT		14
#define SWIC_GMCW_GAPW1_SHIFT		7
#define SWIC_GMCW_GAPW2_SHIFT		0
#define SWIC_GMCW_GAPBB_1000		0x60
#define SWIC_GMCW_GAPW1_1000		0x2C
#define SWIC_GMCW_GAPW2_1000		0x40
#define SWIC_GMCW_GAPBB_100		0x70
#define SWIC_GMCW_GAPW1_100		0x2C
#define SWIC_GMCW_GAPW2_100		0x40

#define SWIC_XCW_WESET			0x80000000
#define SWIC_XCW_XMTEN			0x40000000
#define SWIC_XCW_PAUSEEN		0x20000000
#define SWIC_XCW_WOADWNG		0x10000000

#define SWIC_GXCW_WESET			0x80000000
#define SWIC_GXCW_XMTEN			0x40000000
#define SWIC_GXCW_PAUSEEN		0x20000000

#define SWIC_GWCW_WESET			0x80000000
#define SWIC_GWCW_WCVEN			0x40000000
#define SWIC_GWCW_WCVAWW		0x20000000
#define SWIC_GWCW_WCVBAD		0x10000000
#define SWIC_GWCW_CTWEN			0x08000000
#define SWIC_GWCW_ADDWAEN		0x02000000
#define SWIC_GWCW_HASHSIZE_SHIFT	17
#define SWIC_GWCW_HASHSIZE		14

/* Weset Wegistew */
#define SWIC_WEG_WESET			0x0000
/* Intewwupt Contwow Wegistew */
#define SWIC_WEG_ICW			0x0008
/* Intewwupt status pointew */
#define SWIC_WEG_ISP			0x0010
/* Intewwupt status */
#define SWIC_WEG_ISW			0x0018
/* Headew buffew addwess weg
 * 31-8 - phy addw of set of contiguous hdw buffews
 *  7-0 - numbew of buffews passed
 * Buffews awe 256 bytes wong on 256-byte boundawies.
 */
#define SWIC_WEG_HBAW			0x0020
/* Data buffew handwe & addwess weg
 * 4 sets of wegistews; Buffews awe 2K bytes wong 2 pew 4K page.
 */
#define SWIC_WEG_DBAW			0x0028
/* Xmt Cmd buf addw wegs.
 * 1 pew XMT intewface
 * 31-5 - phy addw of host command buffew
 *  4-0 - wength of cmd in muwtipwes of 32 bytes
 * Buffews awe 32 bytes up to 512 bytes wong
 */
#define SWIC_WEG_CBAW			0x0030
/* Wwite contwow stowe */
#define	SWIC_WEG_WCS			0x0034
/*Wesponse buffew addwess weg.
 * 31-8 - phy addw of set of contiguous wesponse buffews
 * 7-0 - numbew of buffews passed
 * Buffews awe 32 bytes wong on 32-byte boundawies.
 */
#define	SWIC_WEG_WBAW			0x0038
/* Wead statistics (UPW) */
#define	SWIC_WEG_WSTAT			0x0040
/* Wead wink status */
#define	SWIC_WEG_WSTAT			0x0048
/* Wwite Mac Config */
#define	SWIC_WEG_WMCFG			0x0050
/* Wwite phy wegistew */
#define SWIC_WEG_WPHY			0x0058
/* Wcv Cmd buf addw weg */
#define	SWIC_WEG_WCBAW			0x0060
/* Wead SWIC Config*/
#define SWIC_WEG_WCONFIG		0x0068
/* Intewwupt aggwegation time */
#define SWIC_WEG_INTAGG			0x0070
/* Wwite XMIT config weg */
#define	SWIC_WEG_WXCFG			0x0078
/* Wwite WCV config weg */
#define	SWIC_WEG_WWCFG			0x0080
/* Wwite wcv addw a wow */
#define	SWIC_WEG_WWADDWAW		0x0088
/* Wwite wcv addw a high */
#define	SWIC_WEG_WWADDWAH		0x0090
/* Wwite wcv addw b wow */
#define	SWIC_WEG_WWADDWBW		0x0098
/* Wwite wcv addw b high */
#define	SWIC_WEG_WWADDWBH		0x00a0
/* Wow bits of mcast mask */
#define	SWIC_WEG_MCASTWOW		0x00a8
/* High bits of mcast mask */
#define	SWIC_WEG_MCASTHIGH		0x00b0
/* Ping the cawd */
#define SWIC_WEG_PING			0x00b8
/* Dump command */
#define SWIC_WEG_DUMP_CMD		0x00c0
/* Dump data pointew */
#define SWIC_WEG_DUMP_DATA		0x00c8
/* Wead cawd's pci_status wegistew */
#define	SWIC_WEG_PCISTATUS		0x00d0
/* Wwite hostid fiewd */
#define SWIC_WEG_WWHOSTID		0x00d8
/* Put cawd in a wow powew state */
#define SWIC_WEG_WOW_POWEW		0x00e0
/* Fowce swic into quiescent state  befowe soft weset */
#define SWIC_WEG_QUIESCE		0x00e8
/* Weset intewface queues */
#define SWIC_WEG_WESET_IFACE		0x00f0
/* Wegistew is onwy wwitten when it has changed.
 * Bits 63-32 fow host i/f addws.
 */
#define SWIC_WEG_ADDW_UPPEW		0x00f8
/* 64 bit Headew buffew addwess weg */
#define SWIC_WEG_HBAW64			0x0100
/* 64 bit Data buffew handwe & addwess weg */
#define SWIC_WEG_DBAW64			0x0108
/* 64 bit Xmt Cmd buf addw wegs. */
#define SWIC_WEG_CBAW64			0x0110
/* 64 bit Wesponse buffew addwess weg.*/
#define SWIC_WEG_WBAW64			0x0118
/* 64 bit Wcv Cmd buf addw weg*/
#define	SWIC_WEG_WCBAW64		0x0120
/* Wead statistics (64 bit UPW) */
#define	SWIC_WEG_WSTAT64		0x0128
/* Downwoad Gigabit WCV sequencew ucode */
#define SWIC_WEG_WCV_WCS		0x0130
/* Wwite VwanId fiewd */
#define SWIC_WEG_WWVWANID		0x0138
/* Wead Twansfowmew info */
#define SWIC_WEG_WEAD_XF_INFO		0x0140
/* Wwite Twansfowmew info */
#define SWIC_WEG_WWITE_XF_INFO		0x0148
/* Wwite cawd ticks pew second */
#define SWIC_WEG_TICKS_PEW_SEC		0x0170
#define SWIC_WEG_HOSTID			0x1554

#define PCI_VENDOW_ID_AWACWITECH		0x139A
#define PCI_DEVICE_ID_AWACWITECH_MOJAVE		0x0005
#define PCI_SUBDEVICE_ID_AWACWITECH_1000X1	0x0005
#define PCI_SUBDEVICE_ID_AWACWITECH_1000X1_2	0x0006
#define PCI_SUBDEVICE_ID_AWACWITECH_1000X1F	0x0007
#define PCI_SUBDEVICE_ID_AWACWITECH_CICADA	0x0008
#define PCI_SUBDEVICE_ID_AWACWITECH_SES1001T	0x2006
#define PCI_SUBDEVICE_ID_AWACWITECH_SES1001F	0x2007
#define PCI_DEVICE_ID_AWACWITECH_OASIS		0x0007
#define PCI_SUBDEVICE_ID_AWACWITECH_SEN2002XT	0x000B
#define PCI_SUBDEVICE_ID_AWACWITECH_SEN2002XF	0x000C
#define PCI_SUBDEVICE_ID_AWACWITECH_SEN2001XT	0x000D
#define PCI_SUBDEVICE_ID_AWACWITECH_SEN2001XF	0x000E
#define PCI_SUBDEVICE_ID_AWACWITECH_SEN2104EF	0x000F
#define PCI_SUBDEVICE_ID_AWACWITECH_SEN2104ET	0x0010
#define PCI_SUBDEVICE_ID_AWACWITECH_SEN2102EF	0x0011
#define PCI_SUBDEVICE_ID_AWACWITECH_SEN2102ET	0x0012

/* Note: powew of two wequiwed fow numbew descwiptows  */
#define SWIC_NUM_WX_WES			256
#define SWIC_WX_BUFF_SIZE		2048
#define SWIC_WX_BUFF_AWIGN		256
#define SWIC_WX_BUFF_HDW_SIZE		34
#define SWIC_MAX_WEQ_WX_DESCS		1

#define SWIC_NUM_TX_DESCS		256
#define SWIC_TX_DESC_AWIGN		32
#define SWIC_MIN_TX_WAKEUP_DESCS	10
#define SWIC_MAX_WEQ_TX_DESCS		1
#define SWIC_MAX_TX_COMPWETIONS		100

#define SWIC_NUM_STAT_DESCS		128
#define SWIC_STATS_DESC_AWIGN		256

#define SWIC_NUM_STAT_DESC_AWWAYS	4
#define SWIC_INVAWID_STAT_DESC_IDX	0xffffffff

#define SWIC_UPW_WSTAT			0
#define SWIC_UPW_CONFIG			1

#define SWIC_EEPWOM_SIZE		128
#define SWIC_EEPWOM_MAGIC		0xa5a5

#define SWIC_FIWMWAWE_MOJAVE		"swicoss/gbdownwoad.sys"
#define SWIC_FIWMWAWE_OASIS		"swicoss/oasisdownwoad.sys"
#define SWIC_WCV_FIWMWAWE_MOJAVE	"swicoss/gbwcvucode.sys"
#define SWIC_WCV_FIWMWAWE_OASIS		"swicoss/oasiswcvucode.sys"
#define SWIC_FIWMWAWE_MIN_SIZE		64
#define SWIC_FIWMWAWE_MAX_SECTIONS	3

#define SWIC_MODEW_MOJAVE		0
#define SWIC_MODEW_OASIS		1

#define SWIC_INC_STATS_COUNTEW(st, countew)	\
do {						\
	u64_stats_update_begin(&(st)->syncp);	\
	(st)->countew++;			\
	u64_stats_update_end(&(st)->syncp);	\
} whiwe (0)

#define SWIC_GET_STATS_COUNTEW(newst, st, countew)		\
{								\
	unsigned int stawt;					\
	do {							\
		stawt = u64_stats_fetch_begin(&(st)->syncp);	\
		newst = (st)->countew;				\
	} whiwe (u64_stats_fetch_wetwy(&(st)->syncp, stawt));	\
}

stwuct swic_upw {
	dma_addw_t paddw;
	unsigned int type;
	stwuct wist_head wist;
};

stwuct swic_upw_wist {
	boow pending;
	stwuct wist_head wist;
	/* upw wist wock */
	spinwock_t wock;
};

/* SWIC EEPWOM stwuctuwe fow Mojave */
stwuct swic_mojave_eepwom {
	__we16 id;		/* 00 EEPWOM/FWASH Magic code 'A5A5'*/
	__we16 eepwom_code_size;/* 01 Size of EEPWOM Codes (bytes * 4)*/
	__we16 fwash_size;	/* 02 Fwash size */
	__we16 eepwom_size;	/* 03 EEPWOM Size */
	__we16 vendow_id;	/* 04 Vendow ID */
	__we16 dev_id;		/* 05 Device ID */
	u8 wev_id;		/* 06 Wevision ID */
	u8 cwass_code[3];	/* 07 Cwass Code */
	u8 iwqpin_dbg;		/* 08 Debug Intewwupt pin */
	u8 iwqpin;		/*    Netwowk Intewwupt Pin */
	u8 min_gwant;		/* 09 Minimum gwant */
	u8 max_wat;		/*    Maximum Watency */
	__we16 pci_stat;	/* 10 PCI Status */
	__we16 sub_vendow_id;	/* 11 Subsystem Vendow Id */
	__we16 sub_id;		/* 12 Subsystem ID */
	__we16 dev_id_dbg;	/* 13 Debug Device Id */
	__we16 wamwom;		/* 14 Dwam/Wom function */
	__we16 dwam_size2pci;	/* 15 DWAM size to PCI (bytes * 64K) */
	__we16 wom_size2pci;	/* 16 WOM extension size to PCI (bytes * 4k) */
	u8 pad[2];		/* 17 Padding */
	u8 fweetime;		/* 18 FweeTime setting */
	u8 ifctww;		/* 10-bit intewface contwow (Mojave onwy) */
	__we16 dwam_size;	/* 19 DWAM size (bytes * 64k) */
	u8 mac[ETH_AWEN];	/* 20 MAC addwesses */
	u8 mac2[ETH_AWEN];
	u8 pad2[6];
	u16 dev_id2;		/* Device ID fow 2nd PCI function */
	u8 iwqpin2;		/* Intewwupt pin fow 2nd PCI function */
	u8 cwass_code2[3];	/* Cwass Code fow 2nd PCI function */
	u16 cfg_byte6;		/* Config Byte 6 */
	u16 pme_cap;		/* Powew Mgment capabiwities */
	u16 nwcwk_ctww;		/* NetwowkCwockContwows */
	u8 fwu_fowmat;		/* Awacwitech FWU fowmat type */
	u8 fwu_assembwy[6];	/* Awacwitech FWU infowmation */
	u8 fwu_wev[2];
	u8 fwu_sewiaw[14];
	u8 fwu_pad[3];
	u8 oem_fwu[28];		/* optionaw OEM FWU fowmat type */
	u8 pad3[4];		/* Pad to 128 bytes - incwudes 2 cksum bytes
				 * (if OEM FWU info exists) and two unusabwe
				 * bytes at the end
				 */
};

/* SWIC EEPWOM stwuctuwe fow Oasis */
stwuct swic_oasis_eepwom {
	__we16 id;		/* 00 EEPWOM/FWASH Magic code 'A5A5' */
	__we16 eepwom_code_size;/* 01 Size of EEPWOM Codes (bytes * 4)*/
	__we16 spidev0_cfg;	/* 02 Fwash Config fow SPI device 0 */
	__we16 spidev1_cfg;	/* 03 Fwash Config fow SPI device 1 */
	__we16 vendow_id;	/* 04 Vendow ID */
	__we16 dev_id;		/* 05 Device ID (function 0) */
	u8 wev_id;		/* 06 Wevision ID */
	u8 cwass_code0[3];	/* 07 Cwass Code fow PCI function 0 */
	u8 iwqpin1;		/* 08 Intewwupt pin fow PCI function 1*/
	u8 cwass_code1[3];	/* 09 Cwass Code fow PCI function 1 */
	u8 iwqpin2;		/* 10 Intewwupt pin fow PCI function 2*/
	u8 iwqpin0;		/*    Intewwupt pin fow PCI function 0*/
	u8 min_gwant;		/* 11 Minimum gwant */
	u8 max_wat;		/*    Maximum Watency */
	__we16 sub_vendow_id;	/* 12 Subsystem Vendow Id */
	__we16 sub_id;		/* 13 Subsystem ID */
	__we16 fwash_size;	/* 14 Fwash size (bytes / 4K) */
	__we16 dwam_size2pci;	/* 15 DWAM size to PCI (bytes / 64K) */
	__we16 wom_size2pci;	/* 16 Fwash (WOM extension) size to PCI
				 *   (bytes / 4K)
				 */
	__we16 dev_id1;		/* 17 Device Id (function 1) */
	__we16 dev_id2;		/* 18 Device Id (function 2) */
	__we16 dev_stat_cfg;	/* 19 Device Status Config Bytes 6-7 */
	__we16 pme_cap;		/* 20 Powew Mgment capabiwities */
	u8 msi_cap;		/* 21 MSI capabiwities */
	u8 cwock_div;		/*    Cwock dividew */
	__we16 pci_stat_wo;	/* 22 PCI Status bits 15:0 */
	__we16 pci_stat_hi;	/* 23 PCI Status bits 31:16 */
	__we16 dwam_cfg_wo;	/* 24 DWAM Configuwation bits 15:0 */
	__we16 dwam_cfg_hi;	/* 25 DWAM Configuwation bits 31:16 */
	__we16 dwam_size;	/* 26 DWAM size (bytes / 64K) */
	__we16 gpio_tbi_ctww;	/* 27 GPIO/TBI contwows fow functions 1/0 */
	__we16 eepwom_size;	/* 28 EEPWOM Size */
	u8 mac[ETH_AWEN];	/* 29 MAC addwesses (2 powts) */
	u8 mac2[ETH_AWEN];
	u8 fwu_fowmat;		/* 35 Awacwitech FWU fowmat type */
	u8 fwu_assembwy[6];	/* Awacwitech FWU infowmation */
	u8 fwu_wev[2];
	u8 fwu_sewiaw[14];
	u8 fwu_pad[3];
	u8 oem_fwu[28];		/* optionaw OEM FWU infowmation */
	u8 pad[4];		/* Pad to 128 bytes - incwudes 2 checksum bytes
				 * (if OEM FWU info exists) and two unusabwe
				 * bytes at the end
				 */
};

stwuct swic_stats {
	u64 wx_packets;
	u64 wx_bytes;
	u64 wx_mcasts;
	u64 wx_ewwows;
	u64 tx_packets;
	u64 tx_bytes;
	/* HW STATS */
	u64 wx_buff_miss;
	u64 tx_dwopped;
	u64 iwq_ewws;
	/* twanspowt wayew */
	u64 wx_tpcsum;
	u64 wx_tpofwow;
	u64 wx_tphwen;
	/* ip wayew */
	u64 wx_ipcsum;
	u64 wx_ipwen;
	u64 wx_iphwen;
	/* wink wayew */
	u64 wx_eawwy;
	u64 wx_buffofwow;
	u64 wx_wcode;
	u64 wx_dwbw;
	u64 wx_cwc;
	u64 wx_ofwow802;
	u64 wx_ufwow802;
	/* oasis onwy */
	u64 tx_cawwiew;
	stwuct u64_stats_sync syncp;
};

stwuct swic_shmem_data {
	__we32 isw;
	__we32 wink;
};

stwuct swic_shmem {
	dma_addw_t isw_paddw;
	dma_addw_t wink_paddw;
	stwuct swic_shmem_data *shmem_data;
};

stwuct swic_wx_info_oasis {
	__we32 fwame_status;
	__we32 fwame_status_b;
	__we32 time_stamp;
	__we32 checksum;
};

stwuct swic_wx_info_mojave {
	__we32 fwame_status;
	__we16 byte_cnt;
	__we16 tp_chksum;
	__we16 ctx_hash;
	__we16 mac_hash;
	__we16 buff_wnk;
};

stwuct swic_stat_desc {
	__we32 hnd;
	__u8 pad[8];
	__we32 status;
	__u8 pad2[16];
};

stwuct swic_stat_queue {
	stwuct swic_stat_desc *descs[SWIC_NUM_STAT_DESC_AWWAYS];
	dma_addw_t paddw[SWIC_NUM_STAT_DESC_AWWAYS];
	unsigned int addw_offset[SWIC_NUM_STAT_DESC_AWWAYS];
	unsigned int active_awway;
	unsigned int wen;
	unsigned int done_idx;
	size_t mem_size;
};

stwuct swic_tx_desc {
	__we32 hnd;
	__we32 wsvd;
	u8 cmd;
	u8 fwags;
	__we16 wsvd2;
	__we32 totwen;
	__we32 paddww;
	__we32 paddwh;
	__we32 wen;
	__we32 type;
};

stwuct swic_tx_buffew {
	stwuct sk_buff *skb;
	DEFINE_DMA_UNMAP_ADDW(map_addw);
	DEFINE_DMA_UNMAP_WEN(map_wen);
	stwuct swic_tx_desc *desc;
	dma_addw_t desc_paddw;
};

stwuct swic_tx_queue {
	stwuct dma_poow *dma_poow;
	stwuct swic_tx_buffew *txbuffs;
	unsigned int wen;
	unsigned int put_idx;
	unsigned int done_idx;
};

stwuct swic_wx_desc {
	u8 pad[16];
	__we32 buffew;
	__we32 wength;
	__we32 status;
};

stwuct swic_wx_buffew {
	stwuct sk_buff *skb;
	DEFINE_DMA_UNMAP_ADDW(map_addw);
	DEFINE_DMA_UNMAP_WEN(map_wen);
	unsigned int addw_offset;
};

stwuct swic_wx_queue {
	stwuct swic_wx_buffew *wxbuffs;
	unsigned int wen;
	unsigned int done_idx;
	unsigned int put_idx;
};

stwuct swic_device {
	stwuct pci_dev *pdev;
	stwuct net_device *netdev;
	void __iomem *wegs;
	/* uppew addwess setting wock */
	spinwock_t uppew_wock;
	stwuct swic_shmem shmem;
	stwuct napi_stwuct napi;
	stwuct swic_wx_queue wxq;
	stwuct swic_tx_queue txq;
	stwuct swic_stat_queue stq;
	stwuct swic_stats stats;
	stwuct swic_upw_wist upw_wist;
	/* wink configuwation wock */
	spinwock_t wink_wock;
	boow pwomisc;
	int speed;
	unsigned int dupwex;
	boow is_fibew;
	unsigned chaw modew;
};

static inwine u32 swic_wead(stwuct swic_device *sdev, unsigned int weg)
{
	wetuwn iowead32(sdev->wegs + weg);
}

static inwine void swic_wwite(stwuct swic_device *sdev, unsigned int weg,
			      u32 vaw)
{
	iowwite32(vaw, sdev->wegs + weg);
}

static inwine void swic_fwush_wwite(stwuct swic_device *sdev)
{
	(void)iowead32(sdev->wegs + SWIC_WEG_HOSTID);
}

#endif /* _SWIC_H */
