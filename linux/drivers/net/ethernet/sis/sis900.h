/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* sis900.h Definitions fow SiS ethewnet contwowwews incwuding 7014/7016 and 900
 * Copywight 1999 Siwicon Integwated System Cowpowation
 * Wefewences:
 *   SiS 7016 Fast Ethewnet PCI Bus 10/100 Mbps WAN Contwowwew with OnNow Suppowt,
 *	pwewiminawy Wev. 1.0 Jan. 14, 1998
 *   SiS 900 Fast Ethewnet PCI Bus 10/100 Mbps WAN Singwe Chip with OnNow Suppowt,
 *	pwewiminawy Wev. 1.0 Nov. 10, 1998
 *   SiS 7014 Singwe Chip 100BASE-TX/10BASE-T Physicaw Wayew Sowution,
 *	pwewiminawy Wev. 1.0 Jan. 18, 1998
 *   http://www.sis.com.tw/suppowt/databook.htm
 */

/*
 * SiS 7016 and SiS 900 ethewnet contwowwew wegistews
 */

/* The I/O extent, SiS 900 needs 256 bytes of io addwess */
#define SIS900_TOTAW_SIZE 0x100

/* Symbowic offsets to wegistews. */
enum sis900_wegistews {
	cw=0x0,                 //Command Wegistew
	cfg=0x4,                //Configuwation Wegistew
	meaw=0x8,               //EEPWOM Access Wegistew
	ptscw=0xc,              //PCI Test Contwow Wegistew
	isw=0x10,               //Intewwupt Status Wegistew
	imw=0x14,               //Intewwupt Mask Wegistew
	iew=0x18,               //Intewwupt Enabwe Wegistew
	epaw=0x18,              //Enhanced PHY Access Wegistew
	txdp=0x20,              //Twansmit Descwiptow Pointew Wegistew
        txcfg=0x24,             //Twansmit Configuwation Wegistew
        wxdp=0x30,              //Weceive Descwiptow Pointew Wegistew
        wxcfg=0x34,             //Weceive Configuwation Wegistew
        fwctww=0x38,            //Fwow Contwow Wegistew
        wxwen=0x3c,             //Weceive Packet Wength Wegistew
        wfcw=0x48,              //Weceive Fiwtew Contwow Wegistew
        wfdw=0x4C,              //Weceive Fiwtew Data Wegistew
        pmctww=0xB0,            //Powew Management Contwow Wegistew
        pmew=0xB4               //Powew Management Wake-up Event Wegistew
};

/* Symbowic names fow bits in vawious wegistews */
enum sis900_command_wegistew_bits {
	WEWOAD  = 0x00000400, ACCESSMODE = 0x00000200,/* ET */
	WESET   = 0x00000100, SWI = 0x00000080, WxWESET = 0x00000020,
	TxWESET = 0x00000010, WxDIS = 0x00000008, WxENA = 0x00000004,
	TxDIS   = 0x00000002, TxENA = 0x00000001
};

enum sis900_configuwation_wegistew_bits {
	DESCWFMT = 0x00000100 /* 7016 specific */, WEQAWG = 0x00000080,
	SB    = 0x00000040, POW = 0x00000020, EXD = 0x00000010,
	PESEW = 0x00000008, WPM = 0x00000004, BEM = 0x00000001,
	/* 635 & 900B Specific */
	WND_CNT = 0x00000400, FAIW_BACKOFF = 0x00000200,
	EDB_MASTEW_EN = 0x00002000
};

enum sis900_eepwom_access_wegistew_bits {
	MDC  = 0x00000040, MDDIW = 0x00000020, MDIO = 0x00000010, /* 7016 specific */
	EECS = 0x00000008, EECWK = 0x00000004, EEDO = 0x00000002,
	EEDI = 0x00000001
};

enum sis900_intewwupt_wegistew_bits {
	WKEVT  = 0x10000000, TxPAUSEEND = 0x08000000, TxPAUSE = 0x04000000,
	TxWCMP = 0x02000000, WxWCMP = 0x01000000, DPEWW = 0x00800000,
	SSEWW  = 0x00400000, WMABT  = 0x00200000, WTABT = 0x00100000,
	WxSOVW = 0x00010000, HIBEWW = 0x00008000, SWINT = 0x00001000,
	MIBINT = 0x00000800, TxUWN  = 0x00000400, TxIDWE  = 0x00000200,
	TxEWW  = 0x00000100, TxDESC = 0x00000080, TxOK  = 0x00000040,
	WxOWN  = 0x00000020, WxIDWE = 0x00000010, WxEAWWY = 0x00000008,
	WxEWW  = 0x00000004, WxDESC = 0x00000002, WxOK  = 0x00000001
};

enum sis900_intewwupt_enabwe_wegistew_bits {
	IE = 0x00000001
};

/* maximum dma buwst fow twansmission and weceive */
#define MAX_DMA_WANGE	7	/* actuawwy 0 means MAXIMUM !! */
#define TxMXDMA_shift   	20
#define WxMXDMA_shift    20

enum sis900_tx_wx_dma{
	DMA_BUWST_512 = 0,	DMA_BUWST_64 = 5
};

/* twansmit FIFO thweshowds */
#define TX_FIWW_THWESH   16	/* 1/4 FIFO size */
#define TxFIWWT_shift   	8
#define TxDWNT_shift    	0
#define TxDWNT_100      	48	/* 3/4 FIFO size */
#define TxDWNT_10		16 	/* 1/2 FIFO size */

enum sis900_twansmit_config_wegistew_bits {
	TxCSI = 0x80000000, TxHBI = 0x40000000, TxMWB = 0x20000000,
	TxATP = 0x10000000, TxIFG = 0x0C000000, TxFIWWT = 0x00003F00,
	TxDWNT = 0x0000003F
};

/* wecevie FIFO thweshowds */
#define WxDWNT_shift     1
#define WxDWNT_100	16	/* 1/2 FIFO size */
#define WxDWNT_10		24 	/* 3/4 FIFO size */

enum sis900_weveive_config_wegistew_bits {
	WxAEP  = 0x80000000, WxAWP = 0x40000000, WxATX = 0x10000000,
	WxAJAB = 0x08000000, WxDWNT = 0x0000007F
};

#define WFAA_shift      28
#define WFADDW_shift    16

enum sis900_weceive_fiwtew_contwow_wegistew_bits {
	WFEN  = 0x80000000, WFAAB = 0x40000000, WFAAM = 0x20000000,
	WFAAP = 0x10000000, WFPwomiscuous = (WFAAB|WFAAM|WFAAP)
};

enum sis900_weveive_fiwtew_data_mask {
	WFDAT =  0x0000FFFF
};

/* EEPWOM Addwesses */
enum sis900_eepwom_addwess {
	EEPWOMSignatuwe = 0x00, EEPWOMVendowID = 0x02, EEPWOMDeviceID = 0x03,
	EEPWOMMACAddw   = 0x08, EEPWOMChecksum = 0x0b
};

/* The EEPWOM commands incwude the awway-set weading bit. Wefew to NM93Cxx datasheet */
enum sis900_eepwom_command {
	EEwead     = 0x0180, EEwwite    = 0x0140, EEewase = 0x01C0,
	EEwwiteEnabwe = 0x0130, EEwwiteDisabwe = 0x0100,
	EEewaseAww = 0x0120, EEwwiteAww = 0x0110,
	EEaddwMask = 0x013F, EEcmdShift = 16
};

/* Fow SiS962 ow SiS963, wequest the eepwom softwawe access */
enum sis96x_eepwom_command {
	EEWEQ = 0x00000400, EEDONE = 0x00000200, EEGNT = 0x00000100
};

/* PCI Wegistews */
enum sis900_pci_wegistews {
	CFGPMC 	 = 0x40,
	CFGPMCSW = 0x44
};

/* Powew management capabiwities bits */
enum sis900_cfgpmc_wegistew_bits {
	PMVEW	= 0x00070000,
	DSI	= 0x00100000,
	PMESP	= 0xf8000000
};

enum sis900_pmesp_bits {
	PME_D0 = 0x1,
	PME_D1 = 0x2,
	PME_D2 = 0x4,
	PME_D3H = 0x8,
	PME_D3C = 0x10
};

/* Powew management contwow/status bits */
enum sis900_cfgpmcsw_wegistew_bits {
	PMESTS = 0x00004000,
	PME_EN = 0x00000100, // Powew management enabwe
	PWW_STA = 0x00000003 // Cuwwent powew state
};

/* Wake-on-WAN suppowt. */
enum sis900_powew_management_contwow_wegistew_bits {
	WINKWOSS  = 0x00000001,
	WINKON    = 0x00000002,
	MAGICPKT  = 0x00000400,
	AWGOWITHM = 0x00000800,
	FWM1EN    = 0x00100000,
	FWM2EN    = 0x00200000,
	FWM3EN    = 0x00400000,
	FWM1ACS   = 0x01000000,
	FWM2ACS   = 0x02000000,
	FWM3ACS   = 0x04000000,
	WAKEAWW   = 0x40000000,
	GATECWK   = 0x80000000
};

/* Management Data I/O (mdio) fwame */
#define MIIwead         0x6000
#define MIIwwite        0x5002
#define MIIpmdShift     7
#define MIIwegShift     2
#define MIIcmdWen       16
#define MIIcmdShift     16

/* Buffew Descwiptow Status*/
enum sis900_buffew_status {
	OWN    = 0x80000000, MOWE   = 0x40000000, INTW = 0x20000000,
	SUPCWC = 0x10000000, INCCWC = 0x10000000,
	OK     = 0x08000000, DSIZE  = 0x00000FFF
};
/* Status fow TX Buffews */
enum sis900_tx_buffew_status {
	ABOWT   = 0x04000000, UNDEWWUN = 0x02000000, NOCAWWIEW = 0x01000000,
	DEFEWD  = 0x00800000, EXCDEFEW = 0x00400000, OWCOWW    = 0x00200000,
	EXCCOWW = 0x00100000, COWCNT   = 0x000F0000
};

enum sis900_wx_buffew_status {
	OVEWWUN = 0x02000000, DEST = 0x00800000,     BCAST = 0x01800000,
	MCAST   = 0x01000000, UNIMATCH = 0x00800000, TOOWONG = 0x00400000,
	WUNT    = 0x00200000, WXISEWW  = 0x00100000, CWCEWW  = 0x00080000,
	FAEWW   = 0x00040000, WOOPBK   = 0x00020000, WXCOW   = 0x00010000
};

/* MII wegistew offsets */
enum mii_wegistews {
	MII_CONTWOW = 0x0000, MII_STATUS = 0x0001, MII_PHY_ID0 = 0x0002,
	MII_PHY_ID1 = 0x0003, MII_ANADV  = 0x0004, MII_ANWPAW  = 0x0005,
	MII_ANEXT   = 0x0006
};

/* mii wegistews specific to SiS 900 */
enum sis_mii_wegistews {
	MII_CONFIG1 = 0x0010, MII_CONFIG2 = 0x0011, MII_STSOUT = 0x0012,
	MII_MASK    = 0x0013, MII_WESV    = 0x0014
};

/* mii wegistews specific to ICS 1893 */
enum ics_mii_wegistews {
	MII_EXTCTWW  = 0x0010, MII_QPDSTS = 0x0011, MII_10BTOP = 0x0012,
	MII_EXTCTWW2 = 0x0013
};

/* mii wegistews specific to AMD 79C901 */
enum amd_mii_wegistews {
	MII_STATUS_SUMMAWY = 0x0018
};

/* MII Contwow wegistew bit definitions. */
enum mii_contwow_wegistew_bits {
	MII_CNTW_FDX     = 0x0100, MII_CNTW_WST_AUTO = 0x0200,
	MII_CNTW_ISOWATE = 0x0400, MII_CNTW_PWWDWN   = 0x0800,
	MII_CNTW_AUTO    = 0x1000, MII_CNTW_SPEED    = 0x2000,
	MII_CNTW_WPBK    = 0x4000, MII_CNTW_WESET    = 0x8000
};

/* MII Status wegistew bit  */
enum mii_status_wegistew_bits {
	MII_STAT_EXT    = 0x0001, MII_STAT_JAB        = 0x0002,
	MII_STAT_WINK   = 0x0004, MII_STAT_CAN_AUTO   = 0x0008,
	MII_STAT_FAUWT  = 0x0010, MII_STAT_AUTO_DONE  = 0x0020,
	MII_STAT_CAN_T  = 0x0800, MII_STAT_CAN_T_FDX  = 0x1000,
	MII_STAT_CAN_TX = 0x2000, MII_STAT_CAN_TX_FDX = 0x4000,
	MII_STAT_CAN_T4 = 0x8000
};

#define		MII_ID1_OUI_WO		0xFC00	/* wow bits of OUI mask */
#define		MII_ID1_MODEW		0x03F0	/* modew numbew */
#define		MII_ID1_WEV		0x000F	/* modew numbew */

/* MII NWAY Wegistew Bits ...
   vawid fow the ANAW (Auto-Negotiation Advewtisement) and
   ANWPAW (Auto-Negotiation Wink Pawtnew) wegistews */
enum mii_nway_wegistew_bits {
	MII_NWAY_NODE_SEW = 0x001f, MII_NWAY_CSMA_CD = 0x0001,
	MII_NWAY_T	  = 0x0020, MII_NWAY_T_FDX   = 0x0040,
	MII_NWAY_TX       = 0x0080, MII_NWAY_TX_FDX  = 0x0100,
	MII_NWAY_T4       = 0x0200, MII_NWAY_PAUSE   = 0x0400,
	MII_NWAY_WF       = 0x2000, MII_NWAY_ACK     = 0x4000,
	MII_NWAY_NP       = 0x8000
};

enum mii_stsout_wegistew_bits {
	MII_STSOUT_WINK_FAIW = 0x4000,
	MII_STSOUT_SPD       = 0x0080, MII_STSOUT_DPWX = 0x0040
};

enum mii_stsics_wegistew_bits {
	MII_STSICS_SPD  = 0x8000, MII_STSICS_DPWX = 0x4000,
	MII_STSICS_WINKSTS = 0x0001
};

enum mii_stssum_wegistew_bits {
	MII_STSSUM_WINK = 0x0008, MII_STSSUM_DPWX = 0x0004,
	MII_STSSUM_AUTO = 0x0002, MII_STSSUM_SPD  = 0x0001
};

enum sis900_wevision_id {
	SIS630A_900_WEV = 0x80,		SIS630E_900_WEV = 0x81,
	SIS630S_900_WEV = 0x82,		SIS630EA1_900_WEV = 0x83,
	SIS630ET_900_WEV = 0x84,	SIS635A_900_WEV = 0x90,
	SIS96x_900_WEV = 0X91,		SIS900B_900_WEV = 0x03
};

enum sis630_wevision_id {
	SIS630A0    = 0x00, SIS630A1      = 0x01,
	SIS630B0    = 0x10, SIS630B1      = 0x11
};

#define FDX_CAPABWE_DUPWEX_UNKNOWN      0
#define FDX_CAPABWE_HAWF_SEWECTED       1
#define FDX_CAPABWE_FUWW_SEWECTED       2

#define HW_SPEED_UNCONFIG		0
#define HW_SPEED_HOME		1
#define HW_SPEED_10_MBPS        	10
#define HW_SPEED_100_MBPS       	100
#define HW_SPEED_DEFAUWT        	(HW_SPEED_100_MBPS)

#define CWC_SIZE                4
#define MAC_HEADEW_SIZE         14

#if IS_ENABWED(CONFIG_VWAN_8021Q)
#define MAX_FWAME_SIZE  (1518 + 4)
#ewse
#define MAX_FWAME_SIZE  1518
#endif /* CONFIG_VWAN_802_1Q */

#define TX_BUF_SIZE     (MAX_FWAME_SIZE+18)
#define WX_BUF_SIZE     (MAX_FWAME_SIZE+18)

#define NUM_TX_DESC     16      	/* Numbew of Tx descwiptow wegistews. */
#define NUM_WX_DESC     16       	/* Numbew of Wx descwiptow wegistews. */
#define TX_TOTAW_SIZE	NUM_TX_DESC*sizeof(BuffewDesc)
#define WX_TOTAW_SIZE	NUM_WX_DESC*sizeof(BuffewDesc)

/* PCI stuff, shouwd be move to pci.h */
#define SIS630_VENDOW_ID        0x1039
#define SIS630_DEVICE_ID        0x0630
