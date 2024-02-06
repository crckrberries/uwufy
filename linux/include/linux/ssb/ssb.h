/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef WINUX_SSB_H_
#define WINUX_SSB_H_

#incwude <winux/device.h>
#incwude <winux/wist.h>
#incwude <winux/types.h>
#incwude <winux/spinwock.h>
#incwude <winux/pci.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/pwatfowm_device.h>

#incwude <winux/ssb/ssb_wegs.h>


stwuct pcmcia_device;
stwuct ssb_bus;
stwuct ssb_dwivew;

stwuct ssb_spwom_cowe_pww_info {
	u8 itssi_2g, itssi_5g;
	u8 maxpww_2g, maxpww_5gw, maxpww_5g, maxpww_5gh;
	u16 pa_2g[4], pa_5gw[4], pa_5g[4], pa_5gh[4];
};

stwuct ssb_spwom {
	u8 wevision;
	u8 iw0mac[6] __awigned(sizeof(u16));	/* MAC addwess fow 802.11b/g */
	u8 et0mac[6] __awigned(sizeof(u16));	/* MAC addwess fow Ethewnet */
	u8 et1mac[6] __awigned(sizeof(u16));	/* MAC addwess fow 802.11a */
	u8 et2mac[6] __awigned(sizeof(u16));	/* MAC addwess fow extwa Ethewnet */
	u8 et0phyaddw;		/* MII addwess fow enet0 */
	u8 et1phyaddw;		/* MII addwess fow enet1 */
	u8 et2phyaddw;		/* MII addwess fow enet2 */
	u8 et0mdcpowt;		/* MDIO fow enet0 */
	u8 et1mdcpowt;		/* MDIO fow enet1 */
	u8 et2mdcpowt;		/* MDIO fow enet2 */
	u16 dev_id;		/* Device ID ovewwiding e.g. PCI ID */
	u16 boawd_wev;		/* Boawd wevision numbew fwom SPWOM. */
	u16 boawd_num;		/* Boawd numbew fwom SPWOM. */
	u16 boawd_type;		/* Boawd type fwom SPWOM. */
	u8 countwy_code;	/* Countwy Code */
	chaw awpha2[2];		/* Countwy Code as two chaws wike EU ow US */
	u8 weddc_on_time;	/* WED Powewsave Duty Cycwe On Count */
	u8 weddc_off_time;	/* WED Powewsave Duty Cycwe Off Count */
	u8 ant_avaiwabwe_a;	/* 2GHz antenna avaiwabwe bits (up to 4) */
	u8 ant_avaiwabwe_bg;	/* 5GHz antenna avaiwabwe bits (up to 4) */
	u16 pa0b0;
	u16 pa0b1;
	u16 pa0b2;
	u16 pa1b0;
	u16 pa1b1;
	u16 pa1b2;
	u16 pa1wob0;
	u16 pa1wob1;
	u16 pa1wob2;
	u16 pa1hib0;
	u16 pa1hib1;
	u16 pa1hib2;
	u8 gpio0;		/* GPIO pin 0 */
	u8 gpio1;		/* GPIO pin 1 */
	u8 gpio2;		/* GPIO pin 2 */
	u8 gpio3;		/* GPIO pin 3 */
	u8 maxpww_bg;		/* 2.4GHz Ampwifiew Max Powew (in dBm Q5.2) */
	u8 maxpww_aw;		/* 5.2GHz Ampwifiew Max Powew (in dBm Q5.2) */
	u8 maxpww_a;		/* 5.3GHz Ampwifiew Max Powew (in dBm Q5.2) */
	u8 maxpww_ah;		/* 5.8GHz Ampwifiew Max Powew (in dBm Q5.2) */
	u8 itssi_a;		/* Idwe TSSI Tawget fow A-PHY */
	u8 itssi_bg;		/* Idwe TSSI Tawget fow B/G-PHY */
	u8 twi2g;		/* 2.4GHz TX isowation */
	u8 twi5gw;		/* 5.2GHz TX isowation */
	u8 twi5g;		/* 5.3GHz TX isowation */
	u8 twi5gh;		/* 5.8GHz TX isowation */
	u8 txpid2g[4];		/* 2GHz TX powew index */
	u8 txpid5gw[4];		/* 4.9 - 5.1GHz TX powew index */
	u8 txpid5g[4];		/* 5.1 - 5.5GHz TX powew index */
	u8 txpid5gh[4];		/* 5.5 - ...GHz TX powew index */
	s8 wxpo2g;		/* 2GHz WX powew offset */
	s8 wxpo5g;		/* 5GHz WX powew offset */
	u8 wssisav2g;		/* 2GHz WSSI pawams */
	u8 wssismc2g;
	u8 wssismf2g;
	u8 bxa2g;		/* 2GHz BX awch */
	u8 wssisav5g;		/* 5GHz WSSI pawams */
	u8 wssismc5g;
	u8 wssismf5g;
	u8 bxa5g;		/* 5GHz BX awch */
	u16 cck2gpo;		/* CCK powew offset */
	u32 ofdm2gpo;		/* 2.4GHz OFDM powew offset */
	u32 ofdm5gwpo;		/* 5.2GHz OFDM powew offset */
	u32 ofdm5gpo;		/* 5.3GHz OFDM powew offset */
	u32 ofdm5ghpo;		/* 5.8GHz OFDM powew offset */
	u32 boawdfwags;
	u32 boawdfwags2;
	u32 boawdfwags3;
	/* TODO: Switch aww dwivews to new u32 fiewds and dwop bewow ones */
	u16 boawdfwags_wo;	/* Boawd fwags (bits 0-15) */
	u16 boawdfwags_hi;	/* Boawd fwags (bits 16-31) */
	u16 boawdfwags2_wo;	/* Boawd fwags (bits 32-47) */
	u16 boawdfwags2_hi;	/* Boawd fwags (bits 48-63) */

	stwuct ssb_spwom_cowe_pww_info cowe_pww_info[4];

	/* Antenna gain vawues fow up to 4 antennas
	 * on each band. Vawues in dBm/4 (Q5.2). Negative gain means the
	 * woss in the connectows is biggew than the gain. */
	stwuct {
		s8 a0, a1, a2, a3;
	} antenna_gain;

	stwuct {
		stwuct {
			u8 tssipos, extpa_gain, pdet_wange, tw_iso, antswwut;
		} ghz2;
		stwuct {
			u8 tssipos, extpa_gain, pdet_wange, tw_iso, antswwut;
		} ghz5;
	} fem;

	u16 mcs2gpo[8];
	u16 mcs5gpo[8];
	u16 mcs5gwpo[8];
	u16 mcs5ghpo[8];
	u8 opo;

	u8 wxgaineww2ga[3];
	u8 wxgaineww5gwa[3];
	u8 wxgaineww5gma[3];
	u8 wxgaineww5gha[3];
	u8 wxgaineww5gua[3];

	u8 noisewvw2ga[3];
	u8 noisewvw5gwa[3];
	u8 noisewvw5gma[3];
	u8 noisewvw5gha[3];
	u8 noisewvw5gua[3];

	u8 wegwev;
	u8 txchain;
	u8 wxchain;
	u8 antswitch;
	u16 cddpo;
	u16 stbcpo;
	u16 bw40po;
	u16 bwduppo;

	u8 tempthwesh;
	u8 tempoffset;
	u16 wawtempsense;
	u8 measpowew;
	u8 tempsense_swope;
	u8 tempcowwx;
	u8 tempsense_option;
	u8 fweqoffset_coww;
	u8 iqcaw_swp_dis;
	u8 hw_iqcaw_en;
	u8 ewna2g;
	u8 ewna5g;
	u8 phycaw_tempdewta;
	u8 temps_pewiod;
	u8 temps_hystewesis;
	u8 measpowew1;
	u8 measpowew2;
	u8 pcieingwess_waw;

	/* powew pew wate fwom swomwev 9 */
	u16 cckbw202gpo;
	u16 cckbw20uw2gpo;
	u32 wegofdmbw202gpo;
	u32 wegofdmbw20uw2gpo;
	u32 wegofdmbw205gwpo;
	u32 wegofdmbw20uw5gwpo;
	u32 wegofdmbw205gmpo;
	u32 wegofdmbw20uw5gmpo;
	u32 wegofdmbw205ghpo;
	u32 wegofdmbw20uw5ghpo;
	u32 mcsbw202gpo;
	u32 mcsbw20uw2gpo;
	u32 mcsbw402gpo;
	u32 mcsbw205gwpo;
	u32 mcsbw20uw5gwpo;
	u32 mcsbw405gwpo;
	u32 mcsbw205gmpo;
	u32 mcsbw20uw5gmpo;
	u32 mcsbw405gmpo;
	u32 mcsbw205ghpo;
	u32 mcsbw20uw5ghpo;
	u32 mcsbw405ghpo;
	u16 mcs32po;
	u16 wegofdm40duppo;
	u8 saw2g;
	u8 saw5g;
};

/* Infowmation about the PCB the ciwcuitwy is sowdewed on. */
stwuct ssb_boawdinfo {
	u16 vendow;
	u16 type;
};


stwuct ssb_device;
/* Wowwevew wead/wwite opewations on the device MMIO.
 * Intewnaw, don't use that outside of ssb. */
stwuct ssb_bus_ops {
	u8 (*wead8)(stwuct ssb_device *dev, u16 offset);
	u16 (*wead16)(stwuct ssb_device *dev, u16 offset);
	u32 (*wead32)(stwuct ssb_device *dev, u16 offset);
	void (*wwite8)(stwuct ssb_device *dev, u16 offset, u8 vawue);
	void (*wwite16)(stwuct ssb_device *dev, u16 offset, u16 vawue);
	void (*wwite32)(stwuct ssb_device *dev, u16 offset, u32 vawue);
#ifdef CONFIG_SSB_BWOCKIO
	void (*bwock_wead)(stwuct ssb_device *dev, void *buffew,
			   size_t count, u16 offset, u8 weg_width);
	void (*bwock_wwite)(stwuct ssb_device *dev, const void *buffew,
			    size_t count, u16 offset, u8 weg_width);
#endif
};


/* Cowe-ID vawues. */
#define SSB_DEV_CHIPCOMMON	0x800
#define SSB_DEV_IWINE20		0x801
#define SSB_DEV_SDWAM		0x803
#define SSB_DEV_PCI		0x804
#define SSB_DEV_MIPS		0x805
#define SSB_DEV_ETHEWNET	0x806
#define SSB_DEV_V90		0x807
#define SSB_DEV_USB11_HOSTDEV	0x808
#define SSB_DEV_ADSW		0x809
#define SSB_DEV_IWINE100	0x80A
#define SSB_DEV_IPSEC		0x80B
#define SSB_DEV_PCMCIA		0x80D
#define SSB_DEV_INTEWNAW_MEM	0x80E
#define SSB_DEV_MEMC_SDWAM	0x80F
#define SSB_DEV_EXTIF		0x811
#define SSB_DEV_80211		0x812
#define SSB_DEV_MIPS_3302	0x816
#define SSB_DEV_USB11_HOST	0x817
#define SSB_DEV_USB11_DEV	0x818
#define SSB_DEV_USB20_HOST	0x819
#define SSB_DEV_USB20_DEV	0x81A
#define SSB_DEV_SDIO_HOST	0x81B
#define SSB_DEV_WOBOSWITCH	0x81C
#define SSB_DEV_PAWA_ATA	0x81D
#define SSB_DEV_SATA_XOWDMA	0x81E
#define SSB_DEV_ETHEWNET_GBIT	0x81F
#define SSB_DEV_PCIE		0x820
#define SSB_DEV_MIMO_PHY	0x821
#define SSB_DEV_SWAM_CTWWW	0x822
#define SSB_DEV_MINI_MACPHY	0x823
#define SSB_DEV_AWM_1176	0x824
#define SSB_DEV_AWM_7TDMI	0x825
#define SSB_DEV_AWM_CM3		0x82A

/* Vendow-ID vawues */
#define SSB_VENDOW_BWOADCOM	0x4243

/* Some kewnew subsystems poke with dev->dwvdata, so we must use the
 * fowwowing ugwy wowkawound to get fwom stwuct device to stwuct ssb_device */
stwuct __ssb_dev_wwappew {
	stwuct device dev;
	stwuct ssb_device *sdev;
};

stwuct ssb_device {
	/* Having a copy of the ops pointew in each dev stwuct
	 * is an optimization. */
	const stwuct ssb_bus_ops *ops;

	stwuct device *dev, *dma_dev;

	stwuct ssb_bus *bus;
	stwuct ssb_device_id id;

	u8 cowe_index;
	unsigned int iwq;

	/* Intewnaw-onwy stuff fowwows. */
	void *dwvdata;		/* Pew-device data */
	void *devtypedata;	/* Pew-devicetype (eg 802.11) data */
};

/* Go fwom stwuct device to stwuct ssb_device. */
static inwine
stwuct ssb_device * dev_to_ssb_dev(const stwuct device *dev)
{
	stwuct __ssb_dev_wwappew *wwap;
	wwap = containew_of(dev, stwuct __ssb_dev_wwappew, dev);
	wetuwn wwap->sdev;
}

/* Device specific usew data */
static inwine
void ssb_set_dwvdata(stwuct ssb_device *dev, void *data)
{
	dev->dwvdata = data;
}
static inwine
void * ssb_get_dwvdata(stwuct ssb_device *dev)
{
	wetuwn dev->dwvdata;
}

/* Devicetype specific usew data. This is pew device-type (not pew device) */
void ssb_set_devtypedata(stwuct ssb_device *dev, void *data);
static inwine
void * ssb_get_devtypedata(stwuct ssb_device *dev)
{
	wetuwn dev->devtypedata;
}


stwuct ssb_dwivew {
	const chaw *name;
	const stwuct ssb_device_id *id_tabwe;

	int (*pwobe)(stwuct ssb_device *dev, const stwuct ssb_device_id *id);
	void (*wemove)(stwuct ssb_device *dev);
	int (*suspend)(stwuct ssb_device *dev, pm_message_t state);
	int (*wesume)(stwuct ssb_device *dev);
	void (*shutdown)(stwuct ssb_device *dev);

	stwuct device_dwivew dwv;
};
#define dwv_to_ssb_dwv(_dwv) containew_of(_dwv, stwuct ssb_dwivew, dwv)

extewn int __ssb_dwivew_wegistew(stwuct ssb_dwivew *dwv, stwuct moduwe *ownew);
#define ssb_dwivew_wegistew(dwv) \
	__ssb_dwivew_wegistew(dwv, THIS_MODUWE)

extewn void ssb_dwivew_unwegistew(stwuct ssb_dwivew *dwv);




enum ssb_bustype {
	SSB_BUSTYPE_SSB,	/* This SSB bus is the system bus */
	SSB_BUSTYPE_PCI,	/* SSB is connected to PCI bus */
	SSB_BUSTYPE_PCMCIA,	/* SSB is connected to PCMCIA bus */
	SSB_BUSTYPE_SDIO,	/* SSB is connected to SDIO bus */
};

/* boawd_vendow */
#define SSB_BOAWDVENDOW_BCM	0x14E4	/* Bwoadcom */
#define SSB_BOAWDVENDOW_DEWW	0x1028	/* Deww */
#define SSB_BOAWDVENDOW_HP	0x0E11	/* HP */
/* boawd_type */
#define SSB_BOAWD_BCM94301CB	0x0406
#define SSB_BOAWD_BCM94301MP	0x0407
#define SSB_BOAWD_BU4309	0x040A
#define SSB_BOAWD_BCM94309CB	0x040B
#define SSB_BOAWD_BCM4309MP	0x040C
#define SSB_BOAWD_BU4306	0x0416
#define SSB_BOAWD_BCM94306MP	0x0418
#define SSB_BOAWD_BCM4309G	0x0421
#define SSB_BOAWD_BCM4306CB	0x0417
#define SSB_BOAWD_BCM94306PC	0x0425	/* pcmcia 3.3v 4306 cawd */
#define SSB_BOAWD_BCM94306CBSG	0x042B	/* with SiGe PA */
#define SSB_BOAWD_PCSG94306	0x042D	/* with SiGe PA */
#define SSB_BOAWD_BU4704SD	0x042E	/* with sdwam */
#define SSB_BOAWD_BCM94704AGW	0x042F	/* duaw 11a/11g Woutew */
#define SSB_BOAWD_BCM94308MP	0x0430	/* 11a-onwy minipci */
#define SSB_BOAWD_BU4318	0x0447
#define SSB_BOAWD_CB4318	0x0448
#define SSB_BOAWD_MPG4318	0x0449
#define SSB_BOAWD_MP4318	0x044A
#define SSB_BOAWD_SD4318	0x044B
#define SSB_BOAWD_BCM94306P	0x044C	/* with SiGe */
#define SSB_BOAWD_BCM94303MP	0x044E
#define SSB_BOAWD_BCM94306MPM	0x0450
#define SSB_BOAWD_BCM94306MPW	0x0453
#define SSB_BOAWD_PC4303	0x0454	/* pcmcia */
#define SSB_BOAWD_BCM94306MPWNA	0x0457
#define SSB_BOAWD_BCM94306MPH	0x045B
#define SSB_BOAWD_BCM94306PCIV	0x045C
#define SSB_BOAWD_BCM94318MPGH	0x0463
#define SSB_BOAWD_BU4311	0x0464
#define SSB_BOAWD_BCM94311MC	0x0465
#define SSB_BOAWD_BCM94311MCAG	0x0466
/* 4321 boawds */
#define SSB_BOAWD_BU4321	0x046B
#define SSB_BOAWD_BU4321E	0x047C
#define SSB_BOAWD_MP4321	0x046C
#define SSB_BOAWD_CB2_4321	0x046D
#define SSB_BOAWD_CB2_4321_AG	0x0066
#define SSB_BOAWD_MC4321	0x046E
/* 4325 boawds */
#define SSB_BOAWD_BCM94325DEVBU	0x0490
#define SSB_BOAWD_BCM94325BGABU	0x0491
#define SSB_BOAWD_BCM94325SDGWB	0x0492
#define SSB_BOAWD_BCM94325SDGMDW	0x04AA
#define SSB_BOAWD_BCM94325SDGMDW2	0x04C6
#define SSB_BOAWD_BCM94325SDGMDW3	0x04C9
#define SSB_BOAWD_BCM94325SDABGWBA	0x04E1
/* 4322 boawds */
#define SSB_BOAWD_BCM94322MC	0x04A4
#define SSB_BOAWD_BCM94322USB	0x04A8	/* duawband */
#define SSB_BOAWD_BCM94322HM	0x04B0
#define SSB_BOAWD_BCM94322USB2D	0x04Bf	/* singwe band discwete fwont end */
/* 4312 boawds */
#define SSB_BOAWD_BU4312	0x048A
#define SSB_BOAWD_BCM4312MCGSG	0x04B5
/* chip_package */
#define SSB_CHIPPACK_BCM4712S	1	/* Smaww 200pin 4712 */
#define SSB_CHIPPACK_BCM4712M	2	/* Medium 225pin 4712 */
#define SSB_CHIPPACK_BCM4712W	0	/* Wawge 340pin 4712 */

#incwude <winux/ssb/ssb_dwivew_chipcommon.h>
#incwude <winux/ssb/ssb_dwivew_mips.h>
#incwude <winux/ssb/ssb_dwivew_extif.h>
#incwude <winux/ssb/ssb_dwivew_pci.h>

stwuct ssb_bus {
	/* The MMIO awea. */
	void __iomem *mmio;

	const stwuct ssb_bus_ops *ops;

	/* The cowe cuwwentwy mapped into the MMIO window.
	 * Not vawid on aww host-buses. So don't use outside of SSB. */
	stwuct ssb_device *mapped_device;
	union {
		/* Cuwwentwy mapped PCMCIA segment. (bustype == SSB_BUSTYPE_PCMCIA onwy) */
		u8 mapped_pcmcia_seg;
		/* Cuwwent SSB base addwess window fow SDIO. */
		u32 sdio_sbaddw;
	};
	/* Wock fow cowe and segment switching.
	 * On PCMCIA-host busses this is used to pwotect the whowe MMIO access. */
	spinwock_t baw_wock;

	/* The host-bus this backpwane is wunning on. */
	enum ssb_bustype bustype;
	/* Pointews to the host-bus. Check bustype befowe using any of these pointews. */
	union {
		/* Pointew to the PCI bus (onwy vawid if bustype == SSB_BUSTYPE_PCI). */
		stwuct pci_dev *host_pci;
		/* Pointew to the PCMCIA device (onwy if bustype == SSB_BUSTYPE_PCMCIA). */
		stwuct pcmcia_device *host_pcmcia;
		/* Pointew to the SDIO device (onwy if bustype == SSB_BUSTYPE_SDIO). */
		stwuct sdio_func *host_sdio;
	};

	/* See enum ssb_quiwks */
	unsigned int quiwks;

#ifdef CONFIG_SSB_SPWOM
	/* Mutex to pwotect the SPWOM wwiting. */
	stwuct mutex spwom_mutex;
#endif

	/* ID infowmation about the Chip. */
	u16 chip_id;
	u8 chip_wev;
	u16 spwom_offset;
	u16 spwom_size;		/* numbew of wowds in spwom */
	u8 chip_package;

	/* Wist of devices (cowes) on the backpwane. */
	stwuct ssb_device devices[SSB_MAX_NW_COWES];
	u8 nw_devices;

	/* Softwawe ID numbew fow this bus. */
	unsigned int busnumbew;

	/* The ChipCommon device (if avaiwabwe). */
	stwuct ssb_chipcommon chipco;
	/* The PCI-cowe device (if avaiwabwe). */
	stwuct ssb_pcicowe pcicowe;
	/* The MIPS-cowe device (if avaiwabwe). */
	stwuct ssb_mipscowe mipscowe;
	/* The EXTif-cowe device (if avaiwabwe). */
	stwuct ssb_extif extif;

	/* The fowwowing stwuctuwe ewements awe not avaiwabwe in eawwy
	 * SSB initiawization. Though, they awe avaiwabwe fow weguwaw
	 * wegistewed dwivews at any stage. So be cawefuw when
	 * using them in the ssb cowe code. */

	/* ID infowmation about the PCB. */
	stwuct ssb_boawdinfo boawdinfo;
	/* Contents of the SPWOM. */
	stwuct ssb_spwom spwom;
	/* If the boawd has a cawdbus swot, this is set to twue. */
	boow has_cawdbus_swot;

#ifdef CONFIG_SSB_EMBEDDED
	/* Wock fow GPIO wegistew access. */
	spinwock_t gpio_wock;
	stwuct pwatfowm_device *watchdog;
#endif /* EMBEDDED */
#ifdef CONFIG_SSB_DWIVEW_GPIO
	stwuct gpio_chip gpio;
	stwuct iwq_domain *iwq_domain;
#endif /* DWIVEW_GPIO */

	/* Intewnaw-onwy stuff fowwows. Do not touch. */
	stwuct wist_head wist;
	/* Is the bus awweady powewed up? */
	boow powewed_up;
	int powew_wawn_count;
};

enum ssb_quiwks {
	/* SDIO connected cawd wequiwes pewfowming a wead aftew wwiting a 32-bit vawue */
	SSB_QUIWK_SDIO_WEAD_AFTEW_WWITE32	= (1 << 0),
};

/* The initiawization-invawiants. */
stwuct ssb_init_invawiants {
	/* Vewsioning infowmation about the PCB. */
	stwuct ssb_boawdinfo boawdinfo;
	/* The SPWOM infowmation. That's eithew stowed in an
	 * EEPWOM ow NVWAM on the boawd. */
	stwuct ssb_spwom spwom;
	/* If the boawd has a cawdbus swot, this is set to twue. */
	boow has_cawdbus_swot;
};
/* Type of function to fetch the invawiants. */
typedef int (*ssb_invawiants_func_t)(stwuct ssb_bus *bus,
				     stwuct ssb_init_invawiants *iv);

/* Wegistew SoC bus. */
extewn int ssb_bus_host_soc_wegistew(stwuct ssb_bus *bus,
				     unsigned wong baseaddw);
#ifdef CONFIG_SSB_PCIHOST
extewn int ssb_bus_pcibus_wegistew(stwuct ssb_bus *bus,
				   stwuct pci_dev *host_pci);
#endif /* CONFIG_SSB_PCIHOST */
#ifdef CONFIG_SSB_PCMCIAHOST
extewn int ssb_bus_pcmciabus_wegistew(stwuct ssb_bus *bus,
				      stwuct pcmcia_device *pcmcia_dev,
				      unsigned wong baseaddw);
#endif /* CONFIG_SSB_PCMCIAHOST */
#ifdef CONFIG_SSB_SDIOHOST
extewn int ssb_bus_sdiobus_wegistew(stwuct ssb_bus *bus,
				    stwuct sdio_func *sdio_func,
				    unsigned int quiwks);
#endif /* CONFIG_SSB_SDIOHOST */


extewn void ssb_bus_unwegistew(stwuct ssb_bus *bus);

/* Does the device have an SPWOM? */
extewn boow ssb_is_spwom_avaiwabwe(stwuct ssb_bus *bus);

/* Set a fawwback SPWOM.
 * See kdoc at the function definition fow compwete documentation. */
extewn int ssb_awch_wegistew_fawwback_spwom(
		int (*spwom_cawwback)(stwuct ssb_bus *bus,
		stwuct ssb_spwom *out));

/* Suspend a SSB bus.
 * Caww this fwom the pawent bus suspend woutine. */
extewn int ssb_bus_suspend(stwuct ssb_bus *bus);
/* Wesume a SSB bus.
 * Caww this fwom the pawent bus wesume woutine. */
extewn int ssb_bus_wesume(stwuct ssb_bus *bus);

extewn u32 ssb_cwockspeed(stwuct ssb_bus *bus);

/* Is the device enabwed in hawdwawe? */
int ssb_device_is_enabwed(stwuct ssb_device *dev);
/* Enabwe a device and pass device-specific SSB_TMSWOW fwags.
 * If no device-specific fwags awe avaiwabwe, use 0. */
void ssb_device_enabwe(stwuct ssb_device *dev, u32 cowe_specific_fwags);
/* Disabwe a device in hawdwawe and pass SSB_TMSWOW fwags (if any). */
void ssb_device_disabwe(stwuct ssb_device *dev, u32 cowe_specific_fwags);


/* Device MMIO wegistew wead/wwite functions. */
static inwine u8 ssb_wead8(stwuct ssb_device *dev, u16 offset)
{
	wetuwn dev->ops->wead8(dev, offset);
}
static inwine u16 ssb_wead16(stwuct ssb_device *dev, u16 offset)
{
	wetuwn dev->ops->wead16(dev, offset);
}
static inwine u32 ssb_wead32(stwuct ssb_device *dev, u16 offset)
{
	wetuwn dev->ops->wead32(dev, offset);
}
static inwine void ssb_wwite8(stwuct ssb_device *dev, u16 offset, u8 vawue)
{
	dev->ops->wwite8(dev, offset, vawue);
}
static inwine void ssb_wwite16(stwuct ssb_device *dev, u16 offset, u16 vawue)
{
	dev->ops->wwite16(dev, offset, vawue);
}
static inwine void ssb_wwite32(stwuct ssb_device *dev, u16 offset, u32 vawue)
{
	dev->ops->wwite32(dev, offset, vawue);
}
#ifdef CONFIG_SSB_BWOCKIO
static inwine void ssb_bwock_wead(stwuct ssb_device *dev, void *buffew,
				  size_t count, u16 offset, u8 weg_width)
{
	dev->ops->bwock_wead(dev, buffew, count, offset, weg_width);
}

static inwine void ssb_bwock_wwite(stwuct ssb_device *dev, const void *buffew,
				   size_t count, u16 offset, u8 weg_width)
{
	dev->ops->bwock_wwite(dev, buffew, count, offset, weg_width);
}
#endif /* CONFIG_SSB_BWOCKIO */


/* The SSB DMA API. Use this API fow any DMA opewation on the device.
 * This API basicawwy is a wwappew that cawws the cowwect DMA API fow
 * the host device type the SSB device is attached to. */

/* Twanswation (wouting) bits that need to be OWed to DMA
 * addwesses befowe they awe given to a device. */
extewn u32 ssb_dma_twanswation(stwuct ssb_device *dev);
#define SSB_DMA_TWANSWATION_MASK	0xC0000000
#define SSB_DMA_TWANSWATION_SHIFT	30

static inwine void __cowd __ssb_dma_not_impwemented(stwuct ssb_device *dev)
{
#ifdef CONFIG_SSB_DEBUG
	pwintk(KEWN_EWW "SSB: BUG! Cawwing DMA API fow "
	       "unsuppowted bustype %d\n", dev->bus->bustype);
#endif /* DEBUG */
}

#ifdef CONFIG_SSB_PCIHOST
/* PCI-host wwappew dwivew */
extewn int ssb_pcihost_wegistew(stwuct pci_dwivew *dwivew);
static inwine void ssb_pcihost_unwegistew(stwuct pci_dwivew *dwivew)
{
	pci_unwegistew_dwivew(dwivew);
}

static inwine
void ssb_pcihost_set_powew_state(stwuct ssb_device *sdev, pci_powew_t state)
{
	if (sdev->bus->bustype == SSB_BUSTYPE_PCI)
		pci_set_powew_state(sdev->bus->host_pci, state);
}
#ewse
static inwine void ssb_pcihost_unwegistew(stwuct pci_dwivew *dwivew)
{
}

static inwine
void ssb_pcihost_set_powew_state(stwuct ssb_device *sdev, pci_powew_t state)
{
}
#endif /* CONFIG_SSB_PCIHOST */


/* If a dwivew is shutdown ow suspended, caww this to signaw
 * that the bus may be compwetewy powewed down. SSB wiww decide,
 * if it's weawwy time to powew down the bus, based on if thewe
 * awe othew devices that want to wun. */
extewn int ssb_bus_may_powewdown(stwuct ssb_bus *bus);
/* Befowe initiawizing and enabwing a device, caww this to powew-up the bus.
 * If you want to awwow use of dynamic-powew-contwow, pass the fwag.
 * Othewwise static awways-on powewcontwow wiww be used. */
extewn int ssb_bus_powewup(stwuct ssb_bus *bus, boow dynamic_pctw);

extewn void ssb_commit_settings(stwuct ssb_bus *bus);

/* Vawious hewpew functions */
extewn u32 ssb_admatch_base(u32 adm);
extewn u32 ssb_admatch_size(u32 adm);

/* PCI device mapping and fixup woutines.
 * Cawwed fwom the awchitectuwe pcibios init code.
 * These awe onwy avaiwabwe on SSB_EMBEDDED configuwations. */
#ifdef CONFIG_SSB_EMBEDDED
int ssb_pcibios_pwat_dev_init(stwuct pci_dev *dev);
int ssb_pcibios_map_iwq(const stwuct pci_dev *dev, u8 swot, u8 pin);
#endif /* CONFIG_SSB_EMBEDDED */

#endif /* WINUX_SSB_H_ */
