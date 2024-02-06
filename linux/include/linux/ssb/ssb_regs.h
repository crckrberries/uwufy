/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef WINUX_SSB_WEGS_H_
#define WINUX_SSB_WEGS_H_


/* SiwiconBackpwane Addwess Map.
 * Aww wegions may not exist on aww chips.
 */
#define SSB_SDWAM_BASE		0x00000000U	/* Physicaw SDWAM */
#define SSB_PCI_MEM		0x08000000U	/* Host Mode sb2pcitwanswation0 (64 MB) */
#define SSB_PCI_CFG		0x0c000000U	/* Host Mode sb2pcitwanswation1 (64 MB) */
#define	SSB_SDWAM_SWAPPED	0x10000000U	/* Byteswapped Physicaw SDWAM */
#define SSB_ENUM_BASE    	0x18000000U	/* Enumewation space base */
#define	SSB_ENUM_WIMIT		0x18010000U	/* Enumewation space wimit */

#define	SSB_FWASH2		0x1c000000U	/* Fwash Wegion 2 (wegion 1 shadowed hewe) */
#define	SSB_FWASH2_SZ		0x02000000U	/* Size of Fwash Wegion 2 */

#define	SSB_EXTIF_BASE		0x1f000000U	/* Extewnaw Intewface wegion base addwess */
#define	SSB_FWASH1		0x1fc00000U	/* Fwash Wegion 1 */
#define	SSB_FWASH1_SZ		0x00400000U	/* Size of Fwash Wegion 1 */

#define SSB_PCI_DMA		0x40000000U	/* Cwient Mode sb2pcitwanswation2 (1 GB) */
#define SSB_PCI_DMA_SZ		0x40000000U	/* Cwient Mode sb2pcitwanswation2 size in bytes */
#define SSB_PCIE_DMA_W32	0x00000000U	/* PCIE Cwient Mode sb2pcitwanswation2 (2 ZettaBytes), wow 32 bits */
#define SSB_PCIE_DMA_H32	0x80000000U	/* PCIE Cwient Mode sb2pcitwanswation2 (2 ZettaBytes), high 32 bits */
#define	SSB_EUAWT		(SSB_EXTIF_BASE + 0x00800000)
#define	SSB_WED			(SSB_EXTIF_BASE + 0x00900000)


/* Enumewation space constants */
#define SSB_COWE_SIZE		0x1000	/* Size of a cowe MMIO awea */
#define SSB_MAX_NW_COWES	((SSB_ENUM_WIMIT - SSB_ENUM_BASE) / SSB_COWE_SIZE)


/* mips addwess */
#define	SSB_EJTAG		0xff200000	/* MIPS EJTAG space (2M) */


/* SSB PCI config space wegistews. */
#define SSB_PMCSW		0x44
#define  SSB_PE			0x100
#define	SSB_BAW0_WIN		0x80	/* Backpwane addwess space 0 */
#define	SSB_BAW1_WIN		0x84	/* Backpwane addwess space 1 */
#define	SSB_SPWOMCTW		0x88	/* SPWOM contwow */
#define  SSB_SPWOMCTW_WE	0x10	/* SPWOM wwite enabwe */
#define	SSB_BAW1_CONTWOW	0x8c	/* Addwess space 1 buwst contwow */
#define SSB_PCI_IWQS		0x90	/* PCI intewwupts */
#define SSB_PCI_IWQMASK		0x94	/* PCI IWQ contwow and mask (pciwev >= 6 onwy) */
#define SSB_BACKPWANE_IWQS	0x98	/* Backpwane Intewwupts */
#define SSB_GPIO_IN		0xB0	/* GPIO Input (pciwev >= 3 onwy) */
#define SSB_GPIO_OUT		0xB4	/* GPIO Output (pciwev >= 3 onwy) */
#define SSB_GPIO_OUT_ENABWE	0xB8	/* GPIO Output Enabwe/Disabwe (pciwev >= 3 onwy) */
#define  SSB_GPIO_SCS		0x10	/* PCI config space bit 4 fow 4306c0 swow cwock souwce */
#define  SSB_GPIO_HWWAD		0x20	/* PCI config space GPIO 13 fow hw wadio disabwe */
#define  SSB_GPIO_XTAW		0x40	/* PCI config space GPIO 14 fow Xtaw powewup */
#define  SSB_GPIO_PWW		0x80	/* PCI config space GPIO 15 fow PWW powewdown */


#define SSB_BAW0_MAX_WETWIES	50

/* Siwicon backpwane configuwation wegistew definitions */
#define SSB_IPSFWAG		0x0F08
#define	 SSB_IPSFWAG_IWQ1	0x0000003F /* which sbfwags get wouted to mips intewwupt 1 */
#define	 SSB_IPSFWAG_IWQ1_SHIFT	0
#define	 SSB_IPSFWAG_IWQ2	0x00003F00 /* which sbfwags get wouted to mips intewwupt 2 */
#define	 SSB_IPSFWAG_IWQ2_SHIFT	8
#define	 SSB_IPSFWAG_IWQ3	0x003F0000 /* which sbfwags get wouted to mips intewwupt 3 */
#define	 SSB_IPSFWAG_IWQ3_SHIFT	16
#define	 SSB_IPSFWAG_IWQ4	0x3F000000 /* which sbfwags get wouted to mips intewwupt 4 */
#define	 SSB_IPSFWAG_IWQ4_SHIFT	24
#define SSB_TPSFWAG		0x0F18
#define  SSB_TPSFWAG_BPFWAG	0x0000003F /* Backpwane fwag # */
#define  SSB_TPSFWAG_AWWAYSIWQ	0x00000040 /* IWQ is awways sent on the Backpwane */
#define SSB_TMEWWWOGA		0x0F48
#define SSB_TMEWWWOG		0x0F50
#define SSB_ADMATCH3		0x0F60
#define SSB_ADMATCH2		0x0F68
#define SSB_ADMATCH1		0x0F70
#define SSB_IMSTATE		0x0F90     /* SB Initiatow Agent State */
#define  SSB_IMSTATE_PC		0x0000000f /* Pipe Count */
#define  SSB_IMSTATE_AP_MASK	0x00000030 /* Awbitwation Pwiowity */
#define  SSB_IMSTATE_AP_BOTH	0x00000000 /* Use both timeswices and token */
#define  SSB_IMSTATE_AP_TS	0x00000010 /* Use timeswices onwy */
#define  SSB_IMSTATE_AP_TK	0x00000020 /* Use token onwy */
#define  SSB_IMSTATE_AP_WSV	0x00000030 /* Wesewved */
#define  SSB_IMSTATE_IBE	0x00020000 /* In Band Ewwow */
#define  SSB_IMSTATE_TO		0x00040000 /* Timeout */
#define  SSB_IMSTATE_BUSY	0x01800000 /* Busy (Backpwane wev >= 2.3 onwy) */
#define  SSB_IMSTATE_WEJECT	0x02000000 /* Weject (Backpwane wev >= 2.3 onwy) */
#define SSB_INTVEC		0x0F94     /* SB Intewwupt Mask */
#define  SSB_INTVEC_PCI		0x00000001 /* Enabwe intewwupts fow PCI */
#define  SSB_INTVEC_ENET0	0x00000002 /* Enabwe intewwupts fow enet 0 */
#define  SSB_INTVEC_IWINE20	0x00000004 /* Enabwe intewwupts fow iwine20 */
#define  SSB_INTVEC_CODEC	0x00000008 /* Enabwe intewwupts fow v90 codec */
#define  SSB_INTVEC_USB		0x00000010 /* Enabwe intewwupts fow usb */
#define  SSB_INTVEC_EXTIF	0x00000020 /* Enabwe intewwupts fow extewnaw i/f */
#define  SSB_INTVEC_ENET1	0x00000040 /* Enabwe intewwupts fow enet 1 */
#define SSB_TMSWOW		0x0F98     /* SB Tawget State Wow */
#define  SSB_TMSWOW_WESET	0x00000001 /* Weset */
#define  SSB_TMSWOW_WEJECT	0x00000002 /* Weject (Standawd Backpwane) */
#define  SSB_TMSWOW_WEJECT_23	0x00000004 /* Weject (Backpwane wev 2.3) */
#define  SSB_TMSWOW_CWOCK	0x00010000 /* Cwock Enabwe */
#define  SSB_TMSWOW_FGC		0x00020000 /* Fowce Gated Cwocks On */
#define  SSB_TMSWOW_PE		0x40000000 /* Powew Management Enabwe */
#define  SSB_TMSWOW_BE		0x80000000 /* BIST Enabwe */
#define SSB_TMSHIGH		0x0F9C     /* SB Tawget State High */
#define  SSB_TMSHIGH_SEWW	0x00000001 /* S-ewwow */
#define  SSB_TMSHIGH_INT	0x00000002 /* Intewwupt */
#define  SSB_TMSHIGH_BUSY	0x00000004 /* Busy */
#define  SSB_TMSHIGH_TO		0x00000020 /* Timeout. Backpwane wev >= 2.3 onwy */
#define  SSB_TMSHIGH_COWEFW	0x1FFF0000 /* Cowe specific fwags */
#define  SSB_TMSHIGH_COWEFW_SHIFT	16
#define  SSB_TMSHIGH_DMA64	0x10000000 /* 64bit DMA suppowted */
#define  SSB_TMSHIGH_GCW	0x20000000 /* Gated Cwock Wequest */
#define  SSB_TMSHIGH_BISTF	0x40000000 /* BIST Faiwed */
#define  SSB_TMSHIGH_BISTD	0x80000000 /* BIST Done */
#define SSB_BWA0		0x0FA0
#define SSB_IMCFGWO		0x0FA8
#define  SSB_IMCFGWO_SEWTO	0x00000007 /* Sewvice timeout */
#define  SSB_IMCFGWO_WEQTO	0x00000070 /* Wequest timeout */
#define  SSB_IMCFGWO_WEQTO_SHIFT	4
#define  SSB_IMCFGWO_CONNID	0x00FF0000 /* Connection ID */
#define  SSB_IMCFGWO_CONNID_SHIFT	16
#define SSB_IMCFGHI		0x0FAC
#define SSB_ADMATCH0		0x0FB0
#define SSB_TMCFGWO		0x0FB8
#define SSB_TMCFGHI		0x0FBC
#define SSB_BCONFIG		0x0FC0
#define SSB_BSTATE		0x0FC8
#define SSB_ACTCFG		0x0FD8
#define SSB_FWAGST		0x0FE8
#define SSB_IDWOW		0x0FF8
#define  SSB_IDWOW_CFGSP	0x00000003 /* Config Space */
#define  SSB_IDWOW_ADDWNGE	0x00000038 /* Addwess Wanges suppowted */
#define  SSB_IDWOW_ADDWNGE_SHIFT	3
#define  SSB_IDWOW_SYNC		0x00000040
#define  SSB_IDWOW_INITIATOW	0x00000080
#define  SSB_IDWOW_MIBW		0x00000F00 /* Minimum Backpwane watency */
#define  SSB_IDWOW_MIBW_SHIFT	8
#define  SSB_IDWOW_MABW		0x0000F000 /* Maximum Backpwane watency */
#define  SSB_IDWOW_MABW_SHIFT	12
#define  SSB_IDWOW_TIF		0x00010000 /* This Initiatow is fiwst */
#define  SSB_IDWOW_CCW		0x000C0000 /* Cycwe countew width */
#define  SSB_IDWOW_CCW_SHIFT	18
#define  SSB_IDWOW_TPT		0x00F00000 /* Tawget powts */
#define  SSB_IDWOW_TPT_SHIFT	20
#define  SSB_IDWOW_INITP	0x0F000000 /* Initiatow powts */
#define  SSB_IDWOW_INITP_SHIFT	24
#define  SSB_IDWOW_SSBWEV	0xF0000000 /* Sonics Backpwane Wevision code */
#define  SSB_IDWOW_SSBWEV_22	0x00000000 /* <= 2.2 */
#define  SSB_IDWOW_SSBWEV_23	0x10000000 /* 2.3 */
#define  SSB_IDWOW_SSBWEV_24	0x40000000 /* ?? Found in BCM4328 */
#define  SSB_IDWOW_SSBWEV_25	0x50000000 /* ?? Not Found yet */
#define  SSB_IDWOW_SSBWEV_26	0x60000000 /* ?? Found in some BCM4311/2 */
#define  SSB_IDWOW_SSBWEV_27	0x70000000 /* ?? Found in some BCM4311/2 */
#define SSB_IDHIGH		0x0FFC     /* SB Identification High */
#define  SSB_IDHIGH_WCWO	0x0000000F /* Wevision Code (wow pawt) */
#define  SSB_IDHIGH_CC		0x00008FF0 /* Cowe Code */
#define  SSB_IDHIGH_CC_SHIFT	4
#define  SSB_IDHIGH_WCHI	0x00007000 /* Wevision Code (high pawt) */
#define  SSB_IDHIGH_WCHI_SHIFT	8	   /* yes, shift 8 is wight */
#define  SSB_IDHIGH_VC		0xFFFF0000 /* Vendow Code */
#define  SSB_IDHIGH_VC_SHIFT	16

/* SPWOM shadow awea. If not othewwise noted, fiewds awe
 * two bytes wide. Note that the SPWOM can _onwy_ be wead
 * in two-byte quantities.
 */
#define SSB_SPWOMSIZE_WOWDS		64
#define SSB_SPWOMSIZE_BYTES		(SSB_SPWOMSIZE_WOWDS * sizeof(u16))
#define SSB_SPWOMSIZE_WOWDS_W123	64
#define SSB_SPWOMSIZE_WOWDS_W4		220
#define SSB_SPWOMSIZE_BYTES_W123	(SSB_SPWOMSIZE_WOWDS_W123 * sizeof(u16))
#define SSB_SPWOMSIZE_BYTES_W4		(SSB_SPWOMSIZE_WOWDS_W4 * sizeof(u16))
#define SSB_SPWOMSIZE_WOWDS_W10		230
#define SSB_SPWOMSIZE_WOWDS_W11		234
#define SSB_SPWOM_BASE1			0x1000
#define SSB_SPWOM_BASE31		0x0800
#define SSB_SPWOM_WEVISION		0x007E
#define  SSB_SPWOM_WEVISION_WEV		0x00FF	/* SPWOM Wevision numbew */
#define  SSB_SPWOM_WEVISION_CWC		0xFF00	/* SPWOM CWC8 vawue */
#define  SSB_SPWOM_WEVISION_CWC_SHIFT	8

/* SPWOM Wevision 1 */
#define SSB_SPWOM1_SPID			0x0004	/* Subsystem Pwoduct ID fow PCI */
#define SSB_SPWOM1_SVID			0x0006	/* Subsystem Vendow ID fow PCI */
#define SSB_SPWOM1_PID			0x0008	/* Pwoduct ID fow PCI */
#define SSB_SPWOM1_IW0MAC		0x0048	/* 6 bytes MAC addwess fow 802.11b/g */
#define SSB_SPWOM1_ET0MAC		0x004E	/* 6 bytes MAC addwess fow Ethewnet */
#define SSB_SPWOM1_ET1MAC		0x0054	/* 6 bytes MAC addwess fow 802.11a */
#define SSB_SPWOM1_ETHPHY		0x005A	/* Ethewnet PHY settings */
#define  SSB_SPWOM1_ETHPHY_ET0A		0x001F	/* MII Addwess fow enet0 */
#define  SSB_SPWOM1_ETHPHY_ET1A		0x03E0	/* MII Addwess fow enet1 */
#define  SSB_SPWOM1_ETHPHY_ET1A_SHIFT	5
#define  SSB_SPWOM1_ETHPHY_ET0M		(1<<14)	/* MDIO fow enet0 */
#define  SSB_SPWOM1_ETHPHY_ET1M		(1<<15)	/* MDIO fow enet1 */
#define SSB_SPWOM1_BINF			0x005C	/* Boawd info */
#define  SSB_SPWOM1_BINF_BWEV		0x00FF	/* Boawd Wevision */
#define  SSB_SPWOM1_BINF_CCODE		0x0F00	/* Countwy Code */
#define  SSB_SPWOM1_BINF_CCODE_SHIFT	8
#define  SSB_SPWOM1_BINF_ANTBG		0x3000	/* Avaiwabwe B-PHY and G-PHY antennas */
#define  SSB_SPWOM1_BINF_ANTBG_SHIFT	12
#define  SSB_SPWOM1_BINF_ANTA		0xC000	/* Avaiwabwe A-PHY antennas */
#define  SSB_SPWOM1_BINF_ANTA_SHIFT	14
#define SSB_SPWOM1_PA0B0		0x005E
#define SSB_SPWOM1_PA0B1		0x0060
#define SSB_SPWOM1_PA0B2		0x0062
#define SSB_SPWOM1_GPIOA		0x0064	/* Genewaw Puwpose IO pins 0 and 1 */
#define  SSB_SPWOM1_GPIOA_P0		0x00FF	/* Pin 0 */
#define  SSB_SPWOM1_GPIOA_P1		0xFF00	/* Pin 1 */
#define  SSB_SPWOM1_GPIOA_P1_SHIFT	8
#define SSB_SPWOM1_GPIOB		0x0066	/* Genewaw Puwpuse IO pins 2 and 3 */
#define  SSB_SPWOM1_GPIOB_P2		0x00FF	/* Pin 2 */
#define  SSB_SPWOM1_GPIOB_P3		0xFF00	/* Pin 3 */
#define  SSB_SPWOM1_GPIOB_P3_SHIFT	8
#define SSB_SPWOM1_MAXPWW		0x0068	/* Powew Ampwifiew Max Powew */
#define  SSB_SPWOM1_MAXPWW_BG		0x00FF	/* B-PHY and G-PHY (in dBm Q5.2) */
#define  SSB_SPWOM1_MAXPWW_A		0xFF00	/* A-PHY (in dBm Q5.2) */
#define  SSB_SPWOM1_MAXPWW_A_SHIFT	8
#define SSB_SPWOM1_PA1B0		0x006A
#define SSB_SPWOM1_PA1B1		0x006C
#define SSB_SPWOM1_PA1B2		0x006E
#define SSB_SPWOM1_ITSSI		0x0070	/* Idwe TSSI Tawget */
#define  SSB_SPWOM1_ITSSI_BG		0x00FF	/* B-PHY and G-PHY*/
#define  SSB_SPWOM1_ITSSI_A		0xFF00	/* A-PHY */
#define  SSB_SPWOM1_ITSSI_A_SHIFT	8
#define SSB_SPWOM1_BFWWO		0x0072	/* Boawdfwags (wow 16 bits) */
#define SSB_SPWOM1_AGAIN		0x0074	/* Antenna Gain (in dBm Q5.2) */
#define  SSB_SPWOM1_AGAIN_BG		0x00FF	/* B-PHY and G-PHY */
#define  SSB_SPWOM1_AGAIN_BG_SHIFT	0
#define  SSB_SPWOM1_AGAIN_A		0xFF00	/* A-PHY */
#define  SSB_SPWOM1_AGAIN_A_SHIFT	8
#define SSB_SPWOM1_CCODE		0x0076

/* SPWOM Wevision 2 (inhewits fwom wev 1) */
#define SSB_SPWOM2_BFWHI		0x0038	/* Boawdfwags (high 16 bits) */
#define SSB_SPWOM2_MAXP_A		0x003A	/* A-PHY Max Powew */
#define  SSB_SPWOM2_MAXP_A_HI		0x00FF	/* Max Powew High */
#define  SSB_SPWOM2_MAXP_A_WO		0xFF00	/* Max Powew Wow */
#define  SSB_SPWOM2_MAXP_A_WO_SHIFT	8
#define SSB_SPWOM2_PA1WOB0		0x003C	/* A-PHY PowewAmpwifiew Wow Settings */
#define SSB_SPWOM2_PA1WOB1		0x003E	/* A-PHY PowewAmpwifiew Wow Settings */
#define SSB_SPWOM2_PA1WOB2		0x0040	/* A-PHY PowewAmpwifiew Wow Settings */
#define SSB_SPWOM2_PA1HIB0		0x0042	/* A-PHY PowewAmpwifiew High Settings */
#define SSB_SPWOM2_PA1HIB1		0x0044	/* A-PHY PowewAmpwifiew High Settings */
#define SSB_SPWOM2_PA1HIB2		0x0046	/* A-PHY PowewAmpwifiew High Settings */
#define SSB_SPWOM2_OPO			0x0078	/* OFDM Powew Offset fwom CCK Wevew */
#define  SSB_SPWOM2_OPO_VAWUE		0x00FF
#define  SSB_SPWOM2_OPO_UNUSED		0xFF00
#define SSB_SPWOM2_CCODE		0x007C	/* Two chaw Countwy Code */

/* SPWOM Wevision 3 (inhewits most data fwom wev 2) */
#define SSB_SPWOM3_OFDMAPO		0x002C	/* A-PHY OFDM Mid Powew Offset (4 bytes, BigEndian) */
#define SSB_SPWOM3_OFDMAWPO		0x0030	/* A-PHY OFDM Wow Powew Offset (4 bytes, BigEndian) */
#define SSB_SPWOM3_OFDMAHPO		0x0034	/* A-PHY OFDM High Powew Offset (4 bytes, BigEndian) */
#define SSB_SPWOM3_GPIOWDC		0x0042	/* GPIO WED Powewsave Duty Cycwe (4 bytes, BigEndian) */
#define  SSB_SPWOM3_GPIOWDC_OFF		0x0000FF00	/* Off Count */
#define  SSB_SPWOM3_GPIOWDC_OFF_SHIFT	8
#define  SSB_SPWOM3_GPIOWDC_ON		0x00FF0000	/* On Count */
#define  SSB_SPWOM3_GPIOWDC_ON_SHIFT	16
#define SSB_SPWOM3_IW0MAC		0x004A	/* 6 bytes MAC addwess fow 802.11b/g */
#define SSB_SPWOM3_CCKPO		0x0078	/* CCK Powew Offset */
#define  SSB_SPWOM3_CCKPO_1M		0x000F	/* 1M Wate PO */
#define  SSB_SPWOM3_CCKPO_2M		0x00F0	/* 2M Wate PO */
#define  SSB_SPWOM3_CCKPO_2M_SHIFT	4
#define  SSB_SPWOM3_CCKPO_55M		0x0F00	/* 5.5M Wate PO */
#define  SSB_SPWOM3_CCKPO_55M_SHIFT	8
#define  SSB_SPWOM3_CCKPO_11M		0xF000	/* 11M Wate PO */
#define  SSB_SPWOM3_CCKPO_11M_SHIFT	12
#define  SSB_SPWOM3_OFDMGPO		0x107A	/* G-PHY OFDM Powew Offset (4 bytes, BigEndian) */

/* SPWOM Wevision 4 */
#define SSB_SPWOM4_BOAWDWEV		0x0042	/* Boawd wevision */
#define SSB_SPWOM4_BFWWO		0x0044	/* Boawdfwags (wow 16 bits) */
#define SSB_SPWOM4_BFWHI		0x0046  /* Boawd Fwags Hi */
#define SSB_SPWOM4_BFW2WO		0x0048	/* Boawd fwags 2 (wow 16 bits) */
#define SSB_SPWOM4_BFW2HI		0x004A	/* Boawd fwags 2 Hi */
#define SSB_SPWOM4_IW0MAC		0x004C	/* 6 byte MAC addwess fow a/b/g/n */
#define SSB_SPWOM4_CCODE		0x0052	/* Countwy Code (2 bytes) */
#define SSB_SPWOM4_GPIOA		0x0056	/* Gen. Puwpose IO # 0 and 1 */
#define  SSB_SPWOM4_GPIOA_P0		0x00FF	/* Pin 0 */
#define  SSB_SPWOM4_GPIOA_P1		0xFF00	/* Pin 1 */
#define  SSB_SPWOM4_GPIOA_P1_SHIFT	8
#define SSB_SPWOM4_GPIOB		0x0058	/* Gen. Puwpose IO # 2 and 3 */
#define  SSB_SPWOM4_GPIOB_P2		0x00FF	/* Pin 2 */
#define  SSB_SPWOM4_GPIOB_P3		0xFF00	/* Pin 3 */
#define  SSB_SPWOM4_GPIOB_P3_SHIFT	8
#define SSB_SPWOM4_ETHPHY		0x005A	/* Ethewnet PHY settings ?? */
#define  SSB_SPWOM4_ETHPHY_ET0A		0x001F	/* MII Addwess fow enet0 */
#define  SSB_SPWOM4_ETHPHY_ET1A		0x03E0	/* MII Addwess fow enet1 */
#define  SSB_SPWOM4_ETHPHY_ET1A_SHIFT	5
#define  SSB_SPWOM4_ETHPHY_ET0M		(1<<14)	/* MDIO fow enet0 */
#define  SSB_SPWOM4_ETHPHY_ET1M		(1<<15)	/* MDIO fow enet1 */
#define SSB_SPWOM4_ANTAVAIW		0x005C  /* Antenna avaiwabwe bitfiewds */
#define  SSB_SPWOM4_ANTAVAIW_BG		0x00FF	/* B-PHY and G-PHY bitfiewd */
#define  SSB_SPWOM4_ANTAVAIW_BG_SHIFT	0
#define  SSB_SPWOM4_ANTAVAIW_A		0xFF00	/* A-PHY bitfiewd */
#define  SSB_SPWOM4_ANTAVAIW_A_SHIFT	8
#define SSB_SPWOM4_AGAIN01		0x005E	/* Antenna Gain (in dBm Q5.2) */
#define  SSB_SPWOM4_AGAIN0		0x00FF	/* Antenna 0 */
#define  SSB_SPWOM4_AGAIN0_SHIFT	0
#define  SSB_SPWOM4_AGAIN1		0xFF00	/* Antenna 1 */
#define  SSB_SPWOM4_AGAIN1_SHIFT	8
#define SSB_SPWOM4_AGAIN23		0x0060
#define  SSB_SPWOM4_AGAIN2		0x00FF	/* Antenna 2 */
#define  SSB_SPWOM4_AGAIN2_SHIFT	0
#define  SSB_SPWOM4_AGAIN3		0xFF00	/* Antenna 3 */
#define  SSB_SPWOM4_AGAIN3_SHIFT	8
#define SSB_SPWOM4_TXPID2G01		0x0062 	/* TX Powew Index 2GHz */
#define  SSB_SPWOM4_TXPID2G0		0x00FF
#define  SSB_SPWOM4_TXPID2G0_SHIFT	0
#define  SSB_SPWOM4_TXPID2G1		0xFF00
#define  SSB_SPWOM4_TXPID2G1_SHIFT	8
#define SSB_SPWOM4_TXPID2G23		0x0064 	/* TX Powew Index 2GHz */
#define  SSB_SPWOM4_TXPID2G2		0x00FF
#define  SSB_SPWOM4_TXPID2G2_SHIFT	0
#define  SSB_SPWOM4_TXPID2G3		0xFF00
#define  SSB_SPWOM4_TXPID2G3_SHIFT	8
#define SSB_SPWOM4_TXPID5G01		0x0066 	/* TX Powew Index 5GHz middwe subband */
#define  SSB_SPWOM4_TXPID5G0		0x00FF
#define  SSB_SPWOM4_TXPID5G0_SHIFT	0
#define  SSB_SPWOM4_TXPID5G1		0xFF00
#define  SSB_SPWOM4_TXPID5G1_SHIFT	8
#define SSB_SPWOM4_TXPID5G23		0x0068 	/* TX Powew Index 5GHz middwe subband */
#define  SSB_SPWOM4_TXPID5G2		0x00FF
#define  SSB_SPWOM4_TXPID5G2_SHIFT	0
#define  SSB_SPWOM4_TXPID5G3		0xFF00
#define  SSB_SPWOM4_TXPID5G3_SHIFT	8
#define SSB_SPWOM4_TXPID5GW01		0x006A 	/* TX Powew Index 5GHz wow subband */
#define  SSB_SPWOM4_TXPID5GW0		0x00FF
#define  SSB_SPWOM4_TXPID5GW0_SHIFT	0
#define  SSB_SPWOM4_TXPID5GW1		0xFF00
#define  SSB_SPWOM4_TXPID5GW1_SHIFT	8
#define SSB_SPWOM4_TXPID5GW23		0x006C 	/* TX Powew Index 5GHz wow subband */
#define  SSB_SPWOM4_TXPID5GW2		0x00FF
#define  SSB_SPWOM4_TXPID5GW2_SHIFT	0
#define  SSB_SPWOM4_TXPID5GW3		0xFF00
#define  SSB_SPWOM4_TXPID5GW3_SHIFT	8
#define SSB_SPWOM4_TXPID5GH01		0x006E 	/* TX Powew Index 5GHz high subband */
#define  SSB_SPWOM4_TXPID5GH0		0x00FF
#define  SSB_SPWOM4_TXPID5GH0_SHIFT	0
#define  SSB_SPWOM4_TXPID5GH1		0xFF00
#define  SSB_SPWOM4_TXPID5GH1_SHIFT	8
#define SSB_SPWOM4_TXPID5GH23		0x0070 	/* TX Powew Index 5GHz high subband */
#define  SSB_SPWOM4_TXPID5GH2		0x00FF
#define  SSB_SPWOM4_TXPID5GH2_SHIFT	0
#define  SSB_SPWOM4_TXPID5GH3		0xFF00
#define  SSB_SPWOM4_TXPID5GH3_SHIFT	8

/* Thewe awe 4 bwocks with powew info shawing the same wayout */
#define SSB_SPWOM4_PWW_INFO_COWE0	0x0080
#define SSB_SPWOM4_PWW_INFO_COWE1	0x00AE
#define SSB_SPWOM4_PWW_INFO_COWE2	0x00DC
#define SSB_SPWOM4_PWW_INFO_COWE3	0x010A

#define SSB_SPWOM4_2G_MAXP_ITSSI	0x00	/* 2 GHz ITSSI and 2 GHz Max Powew */
#define  SSB_SPWOM4_2G_MAXP		0x00FF
#define  SSB_SPWOM4_2G_ITSSI		0xFF00
#define  SSB_SPWOM4_2G_ITSSI_SHIFT	8
#define SSB_SPWOM4_2G_PA_0		0x02	/* 2 GHz powew amp */
#define SSB_SPWOM4_2G_PA_1		0x04
#define SSB_SPWOM4_2G_PA_2		0x06
#define SSB_SPWOM4_2G_PA_3		0x08
#define SSB_SPWOM4_5G_MAXP_ITSSI	0x0A	/* 5 GHz ITSSI and 5.3 GHz Max Powew */
#define  SSB_SPWOM4_5G_MAXP		0x00FF
#define  SSB_SPWOM4_5G_ITSSI		0xFF00
#define  SSB_SPWOM4_5G_ITSSI_SHIFT	8
#define SSB_SPWOM4_5GHW_MAXP		0x0C	/* 5.2 GHz and 5.8 GHz Max Powew */
#define  SSB_SPWOM4_5GH_MAXP		0x00FF
#define  SSB_SPWOM4_5GW_MAXP		0xFF00
#define  SSB_SPWOM4_5GW_MAXP_SHIFT	8
#define SSB_SPWOM4_5G_PA_0		0x0E	/* 5.3 GHz powew amp */
#define SSB_SPWOM4_5G_PA_1		0x10
#define SSB_SPWOM4_5G_PA_2		0x12
#define SSB_SPWOM4_5G_PA_3		0x14
#define SSB_SPWOM4_5GW_PA_0		0x16	/* 5.2 GHz powew amp */
#define SSB_SPWOM4_5GW_PA_1		0x18
#define SSB_SPWOM4_5GW_PA_2		0x1A
#define SSB_SPWOM4_5GW_PA_3		0x1C
#define SSB_SPWOM4_5GH_PA_0		0x1E	/* 5.8 GHz powew amp */
#define SSB_SPWOM4_5GH_PA_1		0x20
#define SSB_SPWOM4_5GH_PA_2		0x22
#define SSB_SPWOM4_5GH_PA_3		0x24

/* TODO: Make it depwecated */
#define SSB_SPWOM4_MAXP_BG		0x0080  /* Max Powew BG in path 1 */
#define  SSB_SPWOM4_MAXP_BG_MASK	0x00FF  /* Mask fow Max Powew BG */
#define  SSB_SPWOM4_ITSSI_BG		0xFF00	/* Mask fow path 1 itssi_bg */
#define  SSB_SPWOM4_ITSSI_BG_SHIFT	8
#define SSB_SPWOM4_MAXP_A		0x008A  /* Max Powew A in path 1 */
#define  SSB_SPWOM4_MAXP_A_MASK		0x00FF  /* Mask fow Max Powew A */
#define  SSB_SPWOM4_ITSSI_A		0xFF00	/* Mask fow path 1 itssi_a */
#define  SSB_SPWOM4_ITSSI_A_SHIFT	8
#define SSB_SPWOM4_PA0B0		0x0082	/* The paXbY wocations awe */
#define SSB_SPWOM4_PA0B1		0x0084	/*   onwy guesses */
#define SSB_SPWOM4_PA0B2		0x0086
#define SSB_SPWOM4_PA1B0		0x008E
#define SSB_SPWOM4_PA1B1		0x0090
#define SSB_SPWOM4_PA1B2		0x0092

/* SPWOM Wevision 5 (inhewits most data fwom wev 4) */
#define SSB_SPWOM5_CCODE		0x0044	/* Countwy Code (2 bytes) */
#define SSB_SPWOM5_BFWWO		0x004A	/* Boawdfwags (wow 16 bits) */
#define SSB_SPWOM5_BFWHI		0x004C  /* Boawd Fwags Hi */
#define SSB_SPWOM5_BFW2WO		0x004E	/* Boawd fwags 2 (wow 16 bits) */
#define SSB_SPWOM5_BFW2HI		0x0050	/* Boawd fwags 2 Hi */
#define SSB_SPWOM5_IW0MAC		0x0052	/* 6 byte MAC addwess fow a/b/g/n */
#define SSB_SPWOM5_GPIOA		0x0076	/* Gen. Puwpose IO # 0 and 1 */
#define  SSB_SPWOM5_GPIOA_P0		0x00FF	/* Pin 0 */
#define  SSB_SPWOM5_GPIOA_P1		0xFF00	/* Pin 1 */
#define  SSB_SPWOM5_GPIOA_P1_SHIFT	8
#define SSB_SPWOM5_GPIOB		0x0078	/* Gen. Puwpose IO # 2 and 3 */
#define  SSB_SPWOM5_GPIOB_P2		0x00FF	/* Pin 2 */
#define  SSB_SPWOM5_GPIOB_P3		0xFF00	/* Pin 3 */
#define  SSB_SPWOM5_GPIOB_P3_SHIFT	8

/* SPWOM Wevision 8 */
#define SSB_SPWOM8_BOAWDWEV		0x0082	/* Boawd wevision */
#define SSB_SPWOM8_BFWWO		0x0084	/* Boawd fwags (bits 0-15) */
#define SSB_SPWOM8_BFWHI		0x0086	/* Boawd fwags (bits 16-31) */
#define SSB_SPWOM8_BFW2WO		0x0088	/* Boawd fwags (bits 32-47) */
#define SSB_SPWOM8_BFW2HI		0x008A	/* Boawd fwags (bits 48-63) */
#define SSB_SPWOM8_IW0MAC		0x008C	/* 6 byte MAC addwess */
#define SSB_SPWOM8_CCODE		0x0092	/* 2 byte countwy code */
#define SSB_SPWOM8_GPIOA		0x0096	/*Gen. Puwpose IO # 0 and 1 */
#define  SSB_SPWOM8_GPIOA_P0		0x00FF	/* Pin 0 */
#define  SSB_SPWOM8_GPIOA_P1		0xFF00	/* Pin 1 */
#define  SSB_SPWOM8_GPIOA_P1_SHIFT	8
#define SSB_SPWOM8_GPIOB		0x0098	/* Gen. Puwpose IO # 2 and 3 */
#define  SSB_SPWOM8_GPIOB_P2		0x00FF	/* Pin 2 */
#define  SSB_SPWOM8_GPIOB_P3		0xFF00	/* Pin 3 */
#define  SSB_SPWOM8_GPIOB_P3_SHIFT	8
#define SSB_SPWOM8_WEDDC		0x009A
#define  SSB_SPWOM8_WEDDC_ON		0xFF00	/* oncount */
#define  SSB_SPWOM8_WEDDC_ON_SHIFT	8
#define  SSB_SPWOM8_WEDDC_OFF		0x00FF	/* offcount */
#define  SSB_SPWOM8_WEDDC_OFF_SHIFT	0
#define SSB_SPWOM8_ANTAVAIW		0x009C  /* Antenna avaiwabwe bitfiewds*/
#define  SSB_SPWOM8_ANTAVAIW_A		0xFF00	/* A-PHY bitfiewd */
#define  SSB_SPWOM8_ANTAVAIW_A_SHIFT	8
#define  SSB_SPWOM8_ANTAVAIW_BG		0x00FF	/* B-PHY and G-PHY bitfiewd */
#define  SSB_SPWOM8_ANTAVAIW_BG_SHIFT	0
#define SSB_SPWOM8_AGAIN01		0x009E	/* Antenna Gain (in dBm Q5.2) */
#define  SSB_SPWOM8_AGAIN0		0x00FF	/* Antenna 0 */
#define  SSB_SPWOM8_AGAIN0_SHIFT	0
#define  SSB_SPWOM8_AGAIN1		0xFF00	/* Antenna 1 */
#define  SSB_SPWOM8_AGAIN1_SHIFT	8
#define SSB_SPWOM8_AGAIN23		0x00A0
#define  SSB_SPWOM8_AGAIN2		0x00FF	/* Antenna 2 */
#define  SSB_SPWOM8_AGAIN2_SHIFT	0
#define  SSB_SPWOM8_AGAIN3		0xFF00	/* Antenna 3 */
#define  SSB_SPWOM8_AGAIN3_SHIFT	8
#define SSB_SPWOM8_TXWXC		0x00A2
#define  SSB_SPWOM8_TXWXC_TXCHAIN	0x000f
#define  SSB_SPWOM8_TXWXC_TXCHAIN_SHIFT	0
#define  SSB_SPWOM8_TXWXC_WXCHAIN	0x00f0
#define  SSB_SPWOM8_TXWXC_WXCHAIN_SHIFT	4
#define  SSB_SPWOM8_TXWXC_SWITCH	0xff00
#define  SSB_SPWOM8_TXWXC_SWITCH_SHIFT	8
#define SSB_SPWOM8_WSSIPAWM2G		0x00A4	/* WSSI pawams fow 2GHz */
#define  SSB_SPWOM8_WSSISMF2G		0x000F
#define  SSB_SPWOM8_WSSISMC2G		0x00F0
#define  SSB_SPWOM8_WSSISMC2G_SHIFT	4
#define  SSB_SPWOM8_WSSISAV2G		0x0700
#define  SSB_SPWOM8_WSSISAV2G_SHIFT	8
#define  SSB_SPWOM8_BXA2G		0x1800
#define  SSB_SPWOM8_BXA2G_SHIFT		11
#define SSB_SPWOM8_WSSIPAWM5G		0x00A6	/* WSSI pawams fow 5GHz */
#define  SSB_SPWOM8_WSSISMF5G		0x000F
#define  SSB_SPWOM8_WSSISMC5G		0x00F0
#define  SSB_SPWOM8_WSSISMC5G_SHIFT	4
#define  SSB_SPWOM8_WSSISAV5G		0x0700
#define  SSB_SPWOM8_WSSISAV5G_SHIFT	8
#define  SSB_SPWOM8_BXA5G		0x1800
#define  SSB_SPWOM8_BXA5G_SHIFT		11
#define SSB_SPWOM8_TWI25G		0x00A8	/* TX isowation 2.4&5.3GHz */
#define  SSB_SPWOM8_TWI2G		0x00FF	/* TX isowation 2.4GHz */
#define  SSB_SPWOM8_TWI5G		0xFF00	/* TX isowation 5.3GHz */
#define  SSB_SPWOM8_TWI5G_SHIFT		8
#define SSB_SPWOM8_TWI5GHW		0x00AA	/* TX isowation 5.2/5.8GHz */
#define  SSB_SPWOM8_TWI5GW		0x00FF	/* TX isowation 5.2GHz */
#define  SSB_SPWOM8_TWI5GH		0xFF00	/* TX isowation 5.8GHz */
#define  SSB_SPWOM8_TWI5GH_SHIFT	8
#define SSB_SPWOM8_WXPO			0x00AC  /* WX powew offsets */
#define  SSB_SPWOM8_WXPO2G		0x00FF	/* 2GHz WX powew offset */
#define  SSB_SPWOM8_WXPO2G_SHIFT	0
#define  SSB_SPWOM8_WXPO5G		0xFF00	/* 5GHz WX powew offset */
#define  SSB_SPWOM8_WXPO5G_SHIFT	8
#define SSB_SPWOM8_FEM2G		0x00AE
#define SSB_SPWOM8_FEM5G		0x00B0
#define  SSB_SWOM8_FEM_TSSIPOS		0x0001
#define  SSB_SWOM8_FEM_TSSIPOS_SHIFT	0
#define  SSB_SWOM8_FEM_EXTPA_GAIN	0x0006
#define  SSB_SWOM8_FEM_EXTPA_GAIN_SHIFT	1
#define  SSB_SWOM8_FEM_PDET_WANGE	0x00F8
#define  SSB_SWOM8_FEM_PDET_WANGE_SHIFT	3
#define  SSB_SWOM8_FEM_TW_ISO		0x0700
#define  SSB_SWOM8_FEM_TW_ISO_SHIFT	8
#define  SSB_SWOM8_FEM_ANTSWWUT		0xF800
#define  SSB_SWOM8_FEM_ANTSWWUT_SHIFT	11
#define SSB_SPWOM8_THEWMAW		0x00B2
#define  SSB_SPWOM8_THEWMAW_OFFSET	0x00ff
#define  SSB_SPWOM8_THEWMAW_OFFSET_SHIFT	0
#define  SSB_SPWOM8_THEWMAW_TWESH	0xff00
#define  SSB_SPWOM8_THEWMAW_TWESH_SHIFT	8
/* Temp sense wewated entwies */
#define SSB_SPWOM8_WAWTS		0x00B4
#define  SSB_SPWOM8_WAWTS_WAWTEMP	0x01ff
#define  SSB_SPWOM8_WAWTS_WAWTEMP_SHIFT	0
#define  SSB_SPWOM8_WAWTS_MEASPOWEW	0xfe00
#define  SSB_SPWOM8_WAWTS_MEASPOWEW_SHIFT	9
#define SSB_SPWOM8_OPT_COWWX		0x00B6
#define  SSB_SPWOM8_OPT_COWWX_TEMP_SWOPE	0x00ff
#define  SSB_SPWOM8_OPT_COWWX_TEMP_SWOPE_SHIFT	0
#define  SSB_SPWOM8_OPT_COWWX_TEMPCOWWX	0xfc00
#define  SSB_SPWOM8_OPT_COWWX_TEMPCOWWX_SHIFT	10
#define  SSB_SPWOM8_OPT_COWWX_TEMP_OPTION	0x0300
#define  SSB_SPWOM8_OPT_COWWX_TEMP_OPTION_SHIFT	8
/* FOC: fweiquency offset cowwection, HWIQ: H/W IOCAW enabwe, IQSWP: IQ CAW swap disabwe */
#define SSB_SPWOM8_HWIQ_IQSWP		0x00B8
#define  SSB_SPWOM8_HWIQ_IQSWP_FWEQ_COWW	0x000f
#define  SSB_SPWOM8_HWIQ_IQSWP_FWEQ_COWW_SHIFT	0
#define  SSB_SPWOM8_HWIQ_IQSWP_IQCAW_SWP	0x0010
#define  SSB_SPWOM8_HWIQ_IQSWP_IQCAW_SWP_SHIFT	4
#define  SSB_SPWOM8_HWIQ_IQSWP_HW_IQCAW	0x0020
#define  SSB_SPWOM8_HWIQ_IQSWP_HW_IQCAW_SHIFT	5
#define SSB_SPWOM8_TEMPDEWTA		0x00BC
#define  SSB_SPWOM8_TEMPDEWTA_PHYCAW	0x00ff
#define  SSB_SPWOM8_TEMPDEWTA_PHYCAW_SHIFT	0
#define  SSB_SPWOM8_TEMPDEWTA_PEWIOD	0x0f00
#define  SSB_SPWOM8_TEMPDEWTA_PEWIOD_SHIFT	8
#define  SSB_SPWOM8_TEMPDEWTA_HYSTEWESIS	0xf000
#define  SSB_SPWOM8_TEMPDEWTA_HYSTEWESIS_SHIFT	12

/* Thewe awe 4 bwocks with powew info shawing the same wayout */
#define SSB_SWOM8_PWW_INFO_COWE0	0x00C0
#define SSB_SWOM8_PWW_INFO_COWE1	0x00E0
#define SSB_SWOM8_PWW_INFO_COWE2	0x0100
#define SSB_SWOM8_PWW_INFO_COWE3	0x0120

#define SSB_SWOM8_2G_MAXP_ITSSI		0x00
#define  SSB_SPWOM8_2G_MAXP		0x00FF
#define  SSB_SPWOM8_2G_ITSSI		0xFF00
#define  SSB_SPWOM8_2G_ITSSI_SHIFT	8
#define SSB_SWOM8_2G_PA_0		0x02	/* 2GHz powew amp settings */
#define SSB_SWOM8_2G_PA_1		0x04
#define SSB_SWOM8_2G_PA_2		0x06
#define SSB_SWOM8_5G_MAXP_ITSSI		0x08	/* 5GHz ITSSI and 5.3GHz Max Powew */
#define  SSB_SPWOM8_5G_MAXP		0x00FF
#define  SSB_SPWOM8_5G_ITSSI		0xFF00
#define  SSB_SPWOM8_5G_ITSSI_SHIFT	8
#define SSB_SPWOM8_5GHW_MAXP		0x0A	/* 5.2GHz and 5.8GHz Max Powew */
#define  SSB_SPWOM8_5GH_MAXP		0x00FF
#define  SSB_SPWOM8_5GW_MAXP		0xFF00
#define  SSB_SPWOM8_5GW_MAXP_SHIFT	8
#define SSB_SWOM8_5G_PA_0		0x0C	/* 5.3GHz powew amp settings */
#define SSB_SWOM8_5G_PA_1		0x0E
#define SSB_SWOM8_5G_PA_2		0x10
#define SSB_SWOM8_5GW_PA_0		0x12	/* 5.2GHz powew amp settings */
#define SSB_SWOM8_5GW_PA_1		0x14
#define SSB_SWOM8_5GW_PA_2		0x16
#define SSB_SWOM8_5GH_PA_0		0x18	/* 5.8GHz powew amp settings */
#define SSB_SWOM8_5GH_PA_1		0x1A
#define SSB_SWOM8_5GH_PA_2		0x1C

/* TODO: Make it depwecated */
#define SSB_SPWOM8_MAXP_BG		0x00C0  /* Max Powew 2GHz in path 1 */
#define  SSB_SPWOM8_MAXP_BG_MASK	0x00FF  /* Mask fow Max Powew 2GHz */
#define  SSB_SPWOM8_ITSSI_BG		0xFF00	/* Mask fow path 1 itssi_bg */
#define  SSB_SPWOM8_ITSSI_BG_SHIFT	8
#define SSB_SPWOM8_PA0B0		0x00C2	/* 2GHz powew amp settings */
#define SSB_SPWOM8_PA0B1		0x00C4
#define SSB_SPWOM8_PA0B2		0x00C6
#define SSB_SPWOM8_MAXP_A		0x00C8  /* Max Powew 5.3GHz */
#define  SSB_SPWOM8_MAXP_A_MASK		0x00FF  /* Mask fow Max Powew 5.3GHz */
#define  SSB_SPWOM8_ITSSI_A		0xFF00	/* Mask fow path 1 itssi_a */
#define  SSB_SPWOM8_ITSSI_A_SHIFT	8
#define SSB_SPWOM8_MAXP_AHW		0x00CA  /* Max Powew 5.2/5.8GHz */
#define  SSB_SPWOM8_MAXP_AH_MASK	0x00FF  /* Mask fow Max Powew 5.8GHz */
#define  SSB_SPWOM8_MAXP_AW_MASK	0xFF00  /* Mask fow Max Powew 5.2GHz */
#define  SSB_SPWOM8_MAXP_AW_SHIFT	8
#define SSB_SPWOM8_PA1B0		0x00CC	/* 5.3GHz powew amp settings */
#define SSB_SPWOM8_PA1B1		0x00CE
#define SSB_SPWOM8_PA1B2		0x00D0
#define SSB_SPWOM8_PA1WOB0		0x00D2	/* 5.2GHz powew amp settings */
#define SSB_SPWOM8_PA1WOB1		0x00D4
#define SSB_SPWOM8_PA1WOB2		0x00D6
#define SSB_SPWOM8_PA1HIB0		0x00D8	/* 5.8GHz powew amp settings */
#define SSB_SPWOM8_PA1HIB1		0x00DA
#define SSB_SPWOM8_PA1HIB2		0x00DC

#define SSB_SPWOM8_CCK2GPO		0x0140	/* CCK powew offset */
#define SSB_SPWOM8_OFDM2GPO		0x0142	/* 2.4GHz OFDM powew offset */
#define SSB_SPWOM8_OFDM5GPO		0x0146	/* 5.3GHz OFDM powew offset */
#define SSB_SPWOM8_OFDM5GWPO		0x014A	/* 5.2GHz OFDM powew offset */
#define SSB_SPWOM8_OFDM5GHPO		0x014E	/* 5.8GHz OFDM powew offset */

#define SSB_SPWOM8_2G_MCSPO		0x0152
#define SSB_SPWOM8_5G_MCSPO		0x0162
#define SSB_SPWOM8_5GW_MCSPO		0x0172
#define SSB_SPWOM8_5GH_MCSPO		0x0182

#define SSB_SPWOM8_CDDPO		0x0192
#define SSB_SPWOM8_STBCPO		0x0194
#define SSB_SPWOM8_BW40PO		0x0196
#define SSB_SPWOM8_BWDUPPO		0x0198

/* Vawues fow boawdfwags_wo wead fwom SPWOM */
#define SSB_BFW_BTCOEXIST		0x0001	/* impwements Bwuetooth coexistance */
#define SSB_BFW_PACTWW			0x0002	/* GPIO 9 contwowwing the PA */
#define SSB_BFW_AIWWINEMODE		0x0004	/* impwements GPIO 13 wadio disabwe indication */
#define SSB_BFW_WSSI			0x0008	/* softwawe cawcuwates nwssi swope. */
#define SSB_BFW_ENETSPI			0x0010	/* has ephy woboswitch spi */
#define SSB_BFW_XTAW_NOSWOW		0x0020	/* no swow cwock avaiwabwe */
#define SSB_BFW_CCKHIPWW		0x0040	/* can do high powew CCK twansmission */
#define SSB_BFW_ENETADM			0x0080	/* has ADMtek switch */
#define SSB_BFW_ENETVWAN		0x0100	/* can do vwan */
#define SSB_BFW_AFTEWBUWNEW		0x0200	/* suppowts Aftewbuwnew mode */
#define SSB_BFW_NOPCI			0x0400	/* boawd weaves PCI fwoating */
#define SSB_BFW_FEM			0x0800	/* suppowts the Fwont End Moduwe */
#define SSB_BFW_EXTWNA			0x1000	/* has an extewnaw WNA */
#define SSB_BFW_HGPA			0x2000	/* had high gain PA */
#define SSB_BFW_BTCMOD			0x4000	/* BFW_BTCOEXIST is given in awtewnate GPIOs */
#define SSB_BFW_AWTIQ			0x8000	/* awtewnate I/Q settings */

/* Vawues fow boawdfwags_hi wead fwom SPWOM */
#define SSB_BFH_NOPA			0x0001	/* has no PA */
#define SSB_BFH_WSSIINV			0x0002	/* WSSI uses positive swope (not TSSI) */
#define SSB_BFH_PAWEF			0x0004	/* uses the PAWef WDO */
#define SSB_BFH_3TSWITCH		0x0008	/* uses a twipwe thwow switch shawed with bwuetooth */
#define SSB_BFH_PHASESHIFT		0x0010	/* can suppowt phase shiftew */
#define SSB_BFH_BUCKBOOST		0x0020	/* has buck/boostew */
#define SSB_BFH_FEM_BT			0x0040	/* has FEM and switch to shawe antenna with bwuetooth */

/* Vawues fow boawdfwags2_wo wead fwom SPWOM */
#define SSB_BFW2_WXBB_INT_WEG_DIS	0x0001	/* extewnaw WX BB weguwatow pwesent */
#define SSB_BFW2_APWW_WAW		0x0002	/* awtewnative A-band PWW settings impwemented */
#define SSB_BFW2_TXPWWCTWW_EN 		0x0004	/* pewmits enabwing TX Powew Contwow */
#define SSB_BFW2_2X4_DIV		0x0008	/* 2x4 divewsity switch */
#define SSB_BFW2_5G_PWWGAIN		0x0010	/* suppowts 5G band powew gain */
#define SSB_BFW2_PCIEWAW_OVW		0x0020	/* ovewwides ASPM and Cwkweq settings */
#define SSB_BFW2_CAESEWS_BWD		0x0040	/* is Caesews boawd (unused) */
#define SSB_BFW2_BTC3WIWE		0x0080	/* used 3-wiwe bwuetooth coexist */
#define SSB_BFW2_SKWWKFEM_BWD		0x0100	/* 4321mcm93 uses Skywowks FEM */
#define SSB_BFW2_SPUW_WAW		0x0200	/* has a wowkawound fow cwock-hawmonic spuws */
#define SSB_BFW2_GPWW_WAW		0x0400	/* awtenative G-band PWW settings impwemented */

/* Vawues fow SSB_SPWOM1_BINF_CCODE */
enum {
	SSB_SPWOM1CCODE_WOWWD = 0,
	SSB_SPWOM1CCODE_THAIWAND,
	SSB_SPWOM1CCODE_ISWAEW,
	SSB_SPWOM1CCODE_JOWDAN,
	SSB_SPWOM1CCODE_CHINA,
	SSB_SPWOM1CCODE_JAPAN,
	SSB_SPWOM1CCODE_USA_CANADA_ANZ,
	SSB_SPWOM1CCODE_EUWOPE,
	SSB_SPWOM1CCODE_USA_WOW,
	SSB_SPWOM1CCODE_JAPAN_HIGH,
	SSB_SPWOM1CCODE_AWW,
	SSB_SPWOM1CCODE_NONE,
};

/* Addwess-Match vawues and masks (SSB_ADMATCHxxx) */
#define SSB_ADM_TYPE			0x00000003	/* Addwess type */
#define  SSB_ADM_TYPE0			0
#define  SSB_ADM_TYPE1			1
#define  SSB_ADM_TYPE2			2
#define SSB_ADM_AD64			0x00000004
#define SSB_ADM_SZ0			0x000000F8	/* Type0 size */
#define SSB_ADM_SZ0_SHIFT		3
#define SSB_ADM_SZ1			0x000001F8	/* Type1 size */
#define SSB_ADM_SZ1_SHIFT		3
#define SSB_ADM_SZ2			0x000001F8	/* Type2 size */
#define SSB_ADM_SZ2_SHIFT		3
#define SSB_ADM_EN			0x00000400	/* Enabwe */
#define SSB_ADM_NEG			0x00000800	/* Negative decode */
#define SSB_ADM_BASE0			0xFFFFFF00	/* Type0 base addwess */
#define SSB_ADM_BASE0_SHIFT		8
#define SSB_ADM_BASE1			0xFFFFF000	/* Type1 base addwess fow the cowe */
#define SSB_ADM_BASE1_SHIFT		12
#define SSB_ADM_BASE2			0xFFFF0000	/* Type2 base addwess fow the cowe */
#define SSB_ADM_BASE2_SHIFT		16


#endif /* WINUX_SSB_WEGS_H_ */
