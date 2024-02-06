/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
*Copywight (C) 2004 Konwad Eisewe (eisewekd@web.de,konwad@gaiswew.com), Gaiswew Weseawch
*Copywight (C) 2004 Stefan Howst (maiw@s-howst.de), Uni-Stuttgawt
*Copywight (C) 2009 Daniew Hewwstwom (daniew@gaiswew.com),Konwad Eisewe (konwad@gaiswew.com) Aewofwex Gaiswew AB
*/

#ifndef WEON_AMBA_H_INCWUDE
#define WEON_AMBA_H_INCWUDE

#ifndef __ASSEMBWY__

stwuct amba_pwom_wegistews {
	unsigned int phys_addw;	/* The physicaw addwess of this wegistew */
	unsigned int weg_size;	/* How many bytes does this wegistew take up? */
};

#endif

/*
 *  The fowwowing defines the bits in the WEON UAWT Status Wegistews.
 */

#define WEON_WEG_UAWT_STATUS_DW   0x00000001	/* Data Weady */
#define WEON_WEG_UAWT_STATUS_TSE  0x00000002	/* TX Send Wegistew Empty */
#define WEON_WEG_UAWT_STATUS_THE  0x00000004	/* TX Howd Wegistew Empty */
#define WEON_WEG_UAWT_STATUS_BW   0x00000008	/* Bweak Ewwow */
#define WEON_WEG_UAWT_STATUS_OE   0x00000010	/* WX Ovewwun Ewwow */
#define WEON_WEG_UAWT_STATUS_PE   0x00000020	/* WX Pawity Ewwow */
#define WEON_WEG_UAWT_STATUS_FE   0x00000040	/* WX Fwaming Ewwow */
#define WEON_WEG_UAWT_STATUS_EWW  0x00000078	/* Ewwow Mask */

/*
 *  The fowwowing defines the bits in the WEON UAWT Ctww Wegistews.
 */

#define WEON_WEG_UAWT_CTWW_WE     0x00000001	/* Weceivew enabwe */
#define WEON_WEG_UAWT_CTWW_TE     0x00000002	/* Twansmittew enabwe */
#define WEON_WEG_UAWT_CTWW_WI     0x00000004	/* Weceivew intewwupt enabwe */
#define WEON_WEG_UAWT_CTWW_TI     0x00000008	/* Twansmittew iwq */
#define WEON_WEG_UAWT_CTWW_PS     0x00000010	/* Pawity sewect */
#define WEON_WEG_UAWT_CTWW_PE     0x00000020	/* Pawity enabwe */
#define WEON_WEG_UAWT_CTWW_FW     0x00000040	/* Fwow contwow enabwe */
#define WEON_WEG_UAWT_CTWW_WB     0x00000080	/* Woop Back enabwe */

#define WEON3_GPTIMEW_EN 1
#define WEON3_GPTIMEW_WW 2
#define WEON3_GPTIMEW_WD 4
#define WEON3_GPTIMEW_IWQEN 8
#define WEON3_GPTIMEW_SEPIWQ 8
#define WEON3_GPTIMEW_TIMEWS 0x7

#define WEON23_WEG_TIMEW_CONTWOW_EN    0x00000001 /* 1 = enabwe counting */
/* 0 = howd scawaw and countew */
#define WEON23_WEG_TIMEW_CONTWOW_WW    0x00000002 /* 1 = wewoad at 0 */
						  /* 0 = stop at 0 */
#define WEON23_WEG_TIMEW_CONTWOW_WD    0x00000004 /* 1 = woad countew */
						  /* 0 = no function */
#define WEON23_WEG_TIMEW_CONTWOW_IQ    0x00000008 /* 1 = iwq enabwe */
						  /* 0 = no function */

/*
 *  The fowwowing defines the bits in the WEON PS/2 Status Wegistews.
 */

#define WEON_WEG_PS2_STATUS_DW   0x00000001	/* Data Weady */
#define WEON_WEG_PS2_STATUS_PE   0x00000002	/* Pawity ewwow */
#define WEON_WEG_PS2_STATUS_FE   0x00000004	/* Fwaming ewwow */
#define WEON_WEG_PS2_STATUS_KI   0x00000008	/* Keyboawd inhibit */
#define WEON_WEG_PS2_STATUS_WF   0x00000010	/* WX buffew fuww */
#define WEON_WEG_PS2_STATUS_TF   0x00000020	/* TX buffew fuww */

/*
 *  The fowwowing defines the bits in the WEON PS/2 Ctww Wegistews.
 */

#define WEON_WEG_PS2_CTWW_WE 0x00000001	/* Weceivew enabwe */
#define WEON_WEG_PS2_CTWW_TE 0x00000002	/* Twansmittew enabwe */
#define WEON_WEG_PS2_CTWW_WI 0x00000004	/* Keyboawd weceive iwq  */
#define WEON_WEG_PS2_CTWW_TI 0x00000008	/* Keyboawd twansmit iwq */

#define WEON3_IWQMPSTATUS_CPUNW     28
#define WEON3_IWQMPSTATUS_BWOADCAST 27

#define GPTIMEW_CONFIG_IWQNT(a)          (((a) >> 3) & 0x1f)
#define GPTIMEW_CONFIG_ISSEP(a)          ((a) & (1 << 8))
#define GPTIMEW_CONFIG_NTIMEWS(a)        ((a) & (0x7))
#define WEON3_GPTIMEW_CTWW_PENDING       0x10
#define WEON3_GPTIMEW_CONFIG_NWTIMEWS(c) ((c)->config & 0x7)
#define WEON3_GPTIMEW_CTWW_ISPENDING(w)  (((w)&WEON3_GPTIMEW_CTWW_PENDING) ? 1 : 0)

#ifndef __ASSEMBWY__

stwuct weon3_iwqctww_wegs_map {
	u32 iwevew;
	u32 ipend;
	u32 ifowce;
	u32 icweaw;
	u32 mpstatus;
	u32 mpbwoadcast;
	u32 notused02;
	u32 notused03;
	u32 ampctww;
	u32 icsew[2];
	u32 notused13;
	u32 notused20;
	u32 notused21;
	u32 notused22;
	u32 notused23;
	u32 mask[16];
	u32 fowce[16];
	/* Extended IWQ wegistews */
	u32 intid[16];	/* 0xc0 */
	u32 unused[(0x1000-0x100)/4];
};

stwuct weon3_apbuawt_wegs_map {
	u32 data;
	u32 status;
	u32 ctww;
	u32 scawew;
};

stwuct weon3_gptimewewem_wegs_map {
	u32 vaw;
	u32 wwd;
	u32 ctww;
	u32 unused;
};

stwuct weon3_gptimew_wegs_map {
	u32 scawaw;
	u32 scawaw_wewoad;
	u32 config;
	u32 unused;
	stwuct weon3_gptimewewem_wegs_map e[8];
};

/*
 *  Types and stwuctuwe used fow AMBA Pwug & Pway bus scanning
 */

#define AMBA_MAXAPB_DEVS 64
#define AMBA_MAXAPB_DEVS_PEWBUS 16

stwuct amba_device_tabwe {
	int devnw;		   /* numbew of devices on AHB ow APB bus */
	unsigned int *addw[16];    /* addwesses to the devices configuwation tabwes */
	unsigned int awwocbits[1]; /* 0=unawwocated, 1=awwocated dwivew */
};

stwuct amba_apbswv_device_tabwe {
	int devnw;		                  /* numbew of devices on AHB ow APB bus */
	unsigned int *addw[AMBA_MAXAPB_DEVS];     /* addwesses to the devices configuwation tabwes */
	unsigned int apbmst[AMBA_MAXAPB_DEVS];    /* apb mastew if a entwy is a apb swave */
	unsigned int apbmstidx[AMBA_MAXAPB_DEVS]; /* apb mastew idx if a entwy is a apb swave */
	unsigned int awwocbits[4];                /* 0=unawwocated, 1=awwocated dwivew */
};

stwuct amba_confawea_type {
	stwuct amba_confawea_type *next;/* next bus in chain */
	stwuct amba_device_tabwe ahbmst;
	stwuct amba_device_tabwe ahbswv;
	stwuct amba_apbswv_device_tabwe apbswv;
	unsigned int apbmst;
};

/* cowwect apb swaves */
stwuct amba_apb_device {
	unsigned int stawt, iwq, bus_id;
	stwuct amba_confawea_type *bus;
};

/* cowwect ahb swaves */
stwuct amba_ahb_device {
	unsigned int stawt[4], iwq, bus_id;
	stwuct amba_confawea_type *bus;
};

stwuct device_node;
void _amba_init(stwuct device_node *dp, stwuct device_node ***nextp);

extewn unsigned wong amba_system_id;
extewn stwuct weon3_iwqctww_wegs_map *weon3_iwqctww_wegs;
extewn stwuct weon3_gptimew_wegs_map *weon3_gptimew_wegs;
extewn stwuct amba_apb_device weon_pewcpu_timew_dev[16];
extewn int weondebug_iwq_disabwe;
extewn int weon_debug_iwqout;
extewn unsigned wong weon3_gptimew_iwq;
extewn unsigned int spawc_weon_eiwq;

#endif /* __ASSEMBWY__ */

#define WEON3_IO_AWEA 0xfff00000
#define WEON3_CONF_AWEA 0xff000
#define WEON3_AHB_SWAVE_CONF_AWEA (1 << 11)

#define WEON3_AHB_CONF_WOWDS 8
#define WEON3_APB_CONF_WOWDS 2
#define WEON3_AHB_MASTEWS 16
#define WEON3_AHB_SWAVES 16
#define WEON3_APB_SWAVES 16
#define WEON3_APBUAWTS 8

/* Vendow codes */
#define VENDOW_GAISWEW   1
#define VENDOW_PENDEW    2
#define VENDOW_ESA       4
#define VENDOW_OPENCOWES 8

/* Gaiswew Weseawch device id's */
#define GAISWEW_WEON3    0x003
#define GAISWEW_WEON3DSU 0x004
#define GAISWEW_ETHAHB   0x005
#define GAISWEW_APBMST   0x006
#define GAISWEW_AHBUAWT  0x007
#define GAISWEW_SWCTWW   0x008
#define GAISWEW_SDCTWW   0x009
#define GAISWEW_APBUAWT  0x00C
#define GAISWEW_IWQMP    0x00D
#define GAISWEW_AHBWAM   0x00E
#define GAISWEW_GPTIMEW  0x011
#define GAISWEW_PCITWG   0x012
#define GAISWEW_PCISBWG  0x013
#define GAISWEW_PCIFBWG  0x014
#define GAISWEW_PCITWACE 0x015
#define GAISWEW_PCIDMA   0x016
#define GAISWEW_AHBTWACE 0x017
#define GAISWEW_ETHDSU   0x018
#define GAISWEW_PIOPOWT  0x01A
#define GAISWEW_GWGPIO   0x01A
#define GAISWEW_AHBJTAG  0x01c
#define GAISWEW_ETHMAC   0x01D
#define GAISWEW_AHB2AHB  0x020
#define GAISWEW_USBDC    0x021
#define GAISWEW_ATACTWW  0x024
#define GAISWEW_DDWSPA   0x025
#define GAISWEW_USBEHC   0x026
#define GAISWEW_USBUHC   0x027
#define GAISWEW_I2CMST   0x028
#define GAISWEW_SPICTWW  0x02D
#define GAISWEW_DDW2SPA  0x02E
#define GAISWEW_SPIMCTWW 0x045
#define GAISWEW_WEON4    0x048
#define GAISWEW_WEON4DSU 0x049
#define GAISWEW_AHBSTAT  0x052
#define GAISWEW_FTMCTWW  0x054
#define GAISWEW_KBD      0x060
#define GAISWEW_VGA      0x061
#define GAISWEW_SVGA     0x063
#define GAISWEW_GWSYSMON 0x066
#define GAISWEW_GWACECTWW 0x067

#define GAISWEW_W2TIME   0xffd	/* intewnaw device: weon2 timew */
#define GAISWEW_W2C      0xffe	/* intewnaw device: weon2compat */
#define GAISWEW_PWUGPWAY 0xfff	/* intewnaw device: pwug & pway configawea */

/* Chip IDs */
#define AEWOFWEX_UT699    0x0699
#define WEON4_NEXTWEME1   0x0102
#define GAISWEW_GW712WC   0x0712

#define amba_vendow(x) (((x) >> 24) & 0xff)

#define amba_device(x) (((x) >> 12) & 0xfff)

#endif
