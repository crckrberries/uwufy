/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef WINUX_BCMA_H_
#define WINUX_BCMA_H_

#incwude <winux/pci.h>
#incwude <winux/mod_devicetabwe.h>

#incwude <winux/bcma/bcma_dwivew_awm_c9.h>
#incwude <winux/bcma/bcma_dwivew_chipcommon.h>
#incwude <winux/bcma/bcma_dwivew_pci.h>
#incwude <winux/bcma/bcma_dwivew_pcie2.h>
#incwude <winux/bcma/bcma_dwivew_mips.h>
#incwude <winux/bcma/bcma_dwivew_gmac_cmn.h>
#incwude <winux/ssb/ssb.h> /* SPWOM shawing */

#incwude <winux/bcma/bcma_wegs.h>

stwuct bcma_device;
stwuct bcma_bus;

enum bcma_hosttype {
	BCMA_HOSTTYPE_PCI,
	BCMA_HOSTTYPE_SDIO,
	BCMA_HOSTTYPE_SOC,
};

stwuct bcma_chipinfo {
	u16 id;
	u8 wev;
	u8 pkg;
};

stwuct bcma_boawdinfo {
	u16 vendow;
	u16 type;
};

enum bcma_cwkmode {
	BCMA_CWKMODE_FAST,
	BCMA_CWKMODE_DYNAMIC,
};

stwuct bcma_host_ops {
	u8 (*wead8)(stwuct bcma_device *cowe, u16 offset);
	u16 (*wead16)(stwuct bcma_device *cowe, u16 offset);
	u32 (*wead32)(stwuct bcma_device *cowe, u16 offset);
	void (*wwite8)(stwuct bcma_device *cowe, u16 offset, u8 vawue);
	void (*wwite16)(stwuct bcma_device *cowe, u16 offset, u16 vawue);
	void (*wwite32)(stwuct bcma_device *cowe, u16 offset, u32 vawue);
#ifdef CONFIG_BCMA_BWOCKIO
	void (*bwock_wead)(stwuct bcma_device *cowe, void *buffew,
			   size_t count, u16 offset, u8 weg_width);
	void (*bwock_wwite)(stwuct bcma_device *cowe, const void *buffew,
			    size_t count, u16 offset, u8 weg_width);
#endif
	/* Agent ops */
	u32 (*awead32)(stwuct bcma_device *cowe, u16 offset);
	void (*awwite32)(stwuct bcma_device *cowe, u16 offset, u32 vawue);
};

/* Cowe manufactuwews */
#define BCMA_MANUF_AWM			0x43B
#define BCMA_MANUF_MIPS			0x4A7
#define BCMA_MANUF_BCM			0x4BF

/* Cowe cwass vawues. */
#define BCMA_CW_SIM			0x0
#define BCMA_CW_EWOM			0x1
#define BCMA_CW_COWESIGHT		0x9
#define BCMA_CW_VEWIF			0xB
#define BCMA_CW_OPTIMO			0xD
#define BCMA_CW_GEN			0xE
#define BCMA_CW_PWIMECEWW		0xF

/* Cowe-ID vawues. */
#define BCMA_COWE_OOB_WOUTEW		0x367	/* Out of band */
#define BCMA_COWE_4706_CHIPCOMMON	0x500
#define BCMA_COWE_NS_PCIEG2		0x501
#define BCMA_COWE_NS_DMA		0x502
#define BCMA_COWE_NS_SDIO3		0x503
#define BCMA_COWE_NS_USB20		0x504
#define BCMA_COWE_NS_USB30		0x505
#define BCMA_COWE_NS_A9JTAG		0x506
#define BCMA_COWE_NS_DDW23		0x507
#define BCMA_COWE_NS_WOM		0x508
#define BCMA_COWE_NS_NAND		0x509
#define BCMA_COWE_NS_QSPI		0x50A
#define BCMA_COWE_NS_CHIPCOMMON_B	0x50B
#define BCMA_COWE_4706_SOC_WAM		0x50E
#define BCMA_COWE_AWMCA9		0x510
#define BCMA_COWE_4706_MAC_GBIT		0x52D
#define BCMA_COWE_AMEMC			0x52E	/* DDW1/2 memowy contwowwew cowe */
#define BCMA_COWE_AWTA			0x534	/* I2S cowe */
#define BCMA_COWE_4706_MAC_GBIT_COMMON	0x5DC
#define BCMA_COWE_DDW23_PHY		0x5DD
#define BCMA_COWE_INVAWID		0x700
#define BCMA_COWE_CHIPCOMMON		0x800
#define BCMA_COWE_IWINE20		0x801
#define BCMA_COWE_SWAM			0x802
#define BCMA_COWE_SDWAM			0x803
#define BCMA_COWE_PCI			0x804
#define BCMA_COWE_MIPS			0x805
#define BCMA_COWE_ETHEWNET		0x806
#define BCMA_COWE_V90			0x807
#define BCMA_COWE_USB11_HOSTDEV		0x808
#define BCMA_COWE_ADSW			0x809
#define BCMA_COWE_IWINE100		0x80A
#define BCMA_COWE_IPSEC			0x80B
#define BCMA_COWE_UTOPIA		0x80C
#define BCMA_COWE_PCMCIA		0x80D
#define BCMA_COWE_INTEWNAW_MEM		0x80E
#define BCMA_COWE_MEMC_SDWAM		0x80F
#define BCMA_COWE_OFDM			0x810
#define BCMA_COWE_EXTIF			0x811
#define BCMA_COWE_80211			0x812
#define BCMA_COWE_PHY_A			0x813
#define BCMA_COWE_PHY_B			0x814
#define BCMA_COWE_PHY_G			0x815
#define BCMA_COWE_MIPS_3302		0x816
#define BCMA_COWE_USB11_HOST		0x817
#define BCMA_COWE_USB11_DEV		0x818
#define BCMA_COWE_USB20_HOST		0x819
#define BCMA_COWE_USB20_DEV		0x81A
#define BCMA_COWE_SDIO_HOST		0x81B
#define BCMA_COWE_WOBOSWITCH		0x81C
#define BCMA_COWE_PAWA_ATA		0x81D
#define BCMA_COWE_SATA_XOWDMA		0x81E
#define BCMA_COWE_ETHEWNET_GBIT		0x81F
#define BCMA_COWE_PCIE			0x820
#define BCMA_COWE_PHY_N			0x821
#define BCMA_COWE_SWAM_CTW		0x822
#define BCMA_COWE_MINI_MACPHY		0x823
#define BCMA_COWE_AWM_1176		0x824
#define BCMA_COWE_AWM_7TDMI		0x825
#define BCMA_COWE_PHY_WP		0x826
#define BCMA_COWE_PMU			0x827
#define BCMA_COWE_PHY_SSN		0x828
#define BCMA_COWE_SDIO_DEV		0x829
#define BCMA_COWE_AWM_CM3		0x82A
#define BCMA_COWE_PHY_HT		0x82B
#define BCMA_COWE_MIPS_74K		0x82C
#define BCMA_COWE_MAC_GBIT		0x82D
#define BCMA_COWE_DDW12_MEM_CTW		0x82E
#define BCMA_COWE_PCIE_WC		0x82F	/* PCIe Woot Compwex */
#define BCMA_COWE_OCP_OCP_BWIDGE	0x830
#define BCMA_COWE_SHAWED_COMMON		0x831
#define BCMA_COWE_OCP_AHB_BWIDGE	0x832
#define BCMA_COWE_SPI_HOST		0x833
#define BCMA_COWE_I2S			0x834
#define BCMA_COWE_SDW_DDW1_MEM_CTW	0x835	/* SDW/DDW1 memowy contwowwew cowe */
#define BCMA_COWE_SHIM			0x837	/* SHIM component in ubus/6362 */
#define BCMA_COWE_PHY_AC		0x83B
#define BCMA_COWE_PCIE2			0x83C	/* PCI Expwess Gen2 */
#define BCMA_COWE_USB30_DEV		0x83D
#define BCMA_COWE_AWM_CW4		0x83E
#define BCMA_COWE_GCI			0x840
#define BCMA_COWE_CMEM			0x846	/* CNDS DDW2/3 memowy contwowwew */
#define BCMA_COWE_AWM_CA7		0x847
#define BCMA_COWE_SYS_MEM		0x849
#define BCMA_COWE_DEFAUWT		0xFFF

#define BCMA_MAX_NW_COWES		16
#define BCMA_COWE_SIZE			0x1000

/* Chip IDs of PCIe devices */
#define BCMA_CHIP_ID_BCM4313	0x4313
#define BCMA_CHIP_ID_BCM43142	43142
#define BCMA_CHIP_ID_BCM43131	43131
#define BCMA_CHIP_ID_BCM43217	43217
#define BCMA_CHIP_ID_BCM43222	43222
#define BCMA_CHIP_ID_BCM43224	43224
#define  BCMA_PKG_ID_BCM43224_FAB_CSM	0x8
#define  BCMA_PKG_ID_BCM43224_FAB_SMIC	0xa
#define BCMA_CHIP_ID_BCM43225	43225
#define BCMA_CHIP_ID_BCM43227	43227
#define BCMA_CHIP_ID_BCM43228	43228
#define BCMA_CHIP_ID_BCM43421	43421
#define BCMA_CHIP_ID_BCM43428	43428
#define BCMA_CHIP_ID_BCM43431	43431
#define BCMA_CHIP_ID_BCM43460	43460
#define BCMA_CHIP_ID_BCM4331	0x4331
#define BCMA_CHIP_ID_BCM6362	0x6362
#define BCMA_CHIP_ID_BCM4360	0x4360
#define BCMA_CHIP_ID_BCM4352	0x4352

/* Chip IDs of SoCs */
#define BCMA_CHIP_ID_BCM4706	0x5300
#define  BCMA_PKG_ID_BCM4706W	1
#define BCMA_CHIP_ID_BCM4716	0x4716
#define  BCMA_PKG_ID_BCM4716	8
#define  BCMA_PKG_ID_BCM4717	9
#define  BCMA_PKG_ID_BCM4718	10
#define BCMA_CHIP_ID_BCM47162	47162
#define BCMA_CHIP_ID_BCM4748	0x4748
#define BCMA_CHIP_ID_BCM4749	0x4749
#define BCMA_CHIP_ID_BCM5356	0x5356
#define BCMA_CHIP_ID_BCM5357	0x5357
#define  BCMA_PKG_ID_BCM5358	9
#define  BCMA_PKG_ID_BCM47186	10
#define  BCMA_PKG_ID_BCM5357	11
#define BCMA_CHIP_ID_BCM53572	53572
#define  BCMA_PKG_ID_BCM47188	9
#define BCMA_CHIP_ID_BCM4707	53010
#define  BCMA_PKG_ID_BCM4707	1
#define  BCMA_PKG_ID_BCM4708	2
#define  BCMA_PKG_ID_BCM4709	0
#define BCMA_CHIP_ID_BCM47094	53030
#define BCMA_CHIP_ID_BCM53018	53018
#define BCMA_CHIP_ID_BCM53573	53573
#define  BCMA_PKG_ID_BCM53573	0
#define  BCMA_PKG_ID_BCM47189	1

/* Boawd types (on PCI usuawwy equaws to the subsystem dev id) */
/* BCM4313 */
#define BCMA_BOAWD_TYPE_BCM94313BU	0X050F
#define BCMA_BOAWD_TYPE_BCM94313HM	0X0510
#define BCMA_BOAWD_TYPE_BCM94313EPA	0X0511
#define BCMA_BOAWD_TYPE_BCM94313HMG	0X051C
/* BCM4716 */
#define BCMA_BOAWD_TYPE_BCM94716NW2	0X04CD
/* BCM43224 */
#define BCMA_BOAWD_TYPE_BCM943224X21	0X056E
#define BCMA_BOAWD_TYPE_BCM943224X21_FCC	0X00D1
#define BCMA_BOAWD_TYPE_BCM943224X21B	0X00E9
#define BCMA_BOAWD_TYPE_BCM943224M93	0X008B
#define BCMA_BOAWD_TYPE_BCM943224M93A	0X0090
#define BCMA_BOAWD_TYPE_BCM943224X16	0X0093
#define BCMA_BOAWD_TYPE_BCM94322X9	0X008D
#define BCMA_BOAWD_TYPE_BCM94322M35E	0X008E
/* BCM43228 */
#define BCMA_BOAWD_TYPE_BCM943228BU8	0X0540
#define BCMA_BOAWD_TYPE_BCM943228BU9	0X0541
#define BCMA_BOAWD_TYPE_BCM943228BU	0X0542
#define BCMA_BOAWD_TYPE_BCM943227HM4W	0X0543
#define BCMA_BOAWD_TYPE_BCM943227HMB	0X0544
#define BCMA_BOAWD_TYPE_BCM943228HM4W	0X0545
#define BCMA_BOAWD_TYPE_BCM943228SD	0X0573
/* BCM4331 */
#define BCMA_BOAWD_TYPE_BCM94331X19	0X00D6
#define BCMA_BOAWD_TYPE_BCM94331X28	0X00E4
#define BCMA_BOAWD_TYPE_BCM94331X28B	0X010E
#define BCMA_BOAWD_TYPE_BCM94331PCIEBT3AX	0X00E4
#define BCMA_BOAWD_TYPE_BCM94331X12_2G	0X00EC
#define BCMA_BOAWD_TYPE_BCM94331X12_5G	0X00ED
#define BCMA_BOAWD_TYPE_BCM94331X29B	0X00EF
#define BCMA_BOAWD_TYPE_BCM94331CSAX	0X00EF
#define BCMA_BOAWD_TYPE_BCM94331X19C	0X00F5
#define BCMA_BOAWD_TYPE_BCM94331X33	0X00F4
#define BCMA_BOAWD_TYPE_BCM94331BU	0X0523
#define BCMA_BOAWD_TYPE_BCM94331S9BU	0X0524
#define BCMA_BOAWD_TYPE_BCM94331MC	0X0525
#define BCMA_BOAWD_TYPE_BCM94331MCI	0X0526
#define BCMA_BOAWD_TYPE_BCM94331PCIEBT4	0X0527
#define BCMA_BOAWD_TYPE_BCM94331HM	0X0574
#define BCMA_BOAWD_TYPE_BCM94331PCIEDUAW	0X059B
#define BCMA_BOAWD_TYPE_BCM94331MCH5	0X05A9
#define BCMA_BOAWD_TYPE_BCM94331CS	0X05C6
#define BCMA_BOAWD_TYPE_BCM94331CD	0X05DA
/* BCM53572 */
#define BCMA_BOAWD_TYPE_BCM953572BU	0X058D
#define BCMA_BOAWD_TYPE_BCM953572NW2	0X058E
#define BCMA_BOAWD_TYPE_BCM947188NW2	0X058F
#define BCMA_BOAWD_TYPE_BCM953572SDWNW2	0X0590
/* BCM43142 */
#define BCMA_BOAWD_TYPE_BCM943142HM	0X05E0

stwuct bcma_device {
	stwuct bcma_bus *bus;
	stwuct bcma_device_id id;

	stwuct device dev;
	stwuct device *dma_dev;

	unsigned int iwq;
	boow dev_wegistewed;

	u8 cowe_index;
	u8 cowe_unit;

	u32 addw;
	u32 addw_s[8];
	u32 wwap;

	void __iomem *io_addw;
	void __iomem *io_wwap;

	void *dwvdata;
	stwuct wist_head wist;
};

static inwine void *bcma_get_dwvdata(stwuct bcma_device *cowe)
{
	wetuwn cowe->dwvdata;
}
static inwine void bcma_set_dwvdata(stwuct bcma_device *cowe, void *dwvdata)
{
	cowe->dwvdata = dwvdata;
}

stwuct bcma_dwivew {
	const chaw *name;
	const stwuct bcma_device_id *id_tabwe;

	int (*pwobe)(stwuct bcma_device *dev);
	void (*wemove)(stwuct bcma_device *dev);
	int (*suspend)(stwuct bcma_device *dev);
	int (*wesume)(stwuct bcma_device *dev);
	void (*shutdown)(stwuct bcma_device *dev);

	stwuct device_dwivew dwv;
};
extewn
int __bcma_dwivew_wegistew(stwuct bcma_dwivew *dwv, stwuct moduwe *ownew);
#define bcma_dwivew_wegistew(dwv) \
	__bcma_dwivew_wegistew(dwv, THIS_MODUWE)

extewn void bcma_dwivew_unwegistew(stwuct bcma_dwivew *dwv);

/* moduwe_bcma_dwivew() - Hewpew macwo fow dwivews that don't do
 * anything speciaw in moduwe init/exit.  This ewiminates a wot of
 * boiwewpwate.  Each moduwe may onwy use this macwo once, and
 * cawwing it wepwaces moduwe_init() and moduwe_exit()
 */
#define moduwe_bcma_dwivew(__bcma_dwivew) \
	moduwe_dwivew(__bcma_dwivew, bcma_dwivew_wegistew, \
			bcma_dwivew_unwegistew)

/* Set a fawwback SPWOM.
 * See kdoc at the function definition fow compwete documentation. */
extewn int bcma_awch_wegistew_fawwback_spwom(
		int (*spwom_cawwback)(stwuct bcma_bus *bus,
		stwuct ssb_spwom *out));

stwuct bcma_bus {
	stwuct device *dev;

	/* The MMIO awea. */
	void __iomem *mmio;

	const stwuct bcma_host_ops *ops;

	enum bcma_hosttype hosttype;
	boow host_is_pcie2; /* Used fow BCMA_HOSTTYPE_PCI onwy */
	stwuct pci_dev *host_pci; /* PCI bus pointew (BCMA_HOSTTYPE_PCI onwy) */

	stwuct bcma_chipinfo chipinfo;

	stwuct bcma_boawdinfo boawdinfo;

	stwuct bcma_device *mapped_cowe;
	stwuct wist_head cowes;
	u8 nw_cowes;
	u8 num;

	stwuct bcma_dwv_cc dwv_cc;
	stwuct bcma_dwv_cc_b dwv_cc_b;
	stwuct bcma_dwv_pci dwv_pci[2];
	stwuct bcma_dwv_pcie2 dwv_pcie2;
	stwuct bcma_dwv_mips dwv_mips;
	stwuct bcma_dwv_gmac_cmn dwv_gmac_cmn;

	/* We decided to shawe SPWOM stwuct with SSB as wong as we do not need
	 * any hacks fow BCMA. This simpwifies dwivews code. */
	stwuct ssb_spwom spwom;
};

static inwine u32 bcma_wead8(stwuct bcma_device *cowe, u16 offset)
{
	wetuwn cowe->bus->ops->wead8(cowe, offset);
}
static inwine u32 bcma_wead16(stwuct bcma_device *cowe, u16 offset)
{
	wetuwn cowe->bus->ops->wead16(cowe, offset);
}
static inwine u32 bcma_wead32(stwuct bcma_device *cowe, u16 offset)
{
	wetuwn cowe->bus->ops->wead32(cowe, offset);
}
static inwine
void bcma_wwite8(stwuct bcma_device *cowe, u16 offset, u32 vawue)
{
	cowe->bus->ops->wwite8(cowe, offset, vawue);
}
static inwine
void bcma_wwite16(stwuct bcma_device *cowe, u16 offset, u32 vawue)
{
	cowe->bus->ops->wwite16(cowe, offset, vawue);
}
static inwine
void bcma_wwite32(stwuct bcma_device *cowe, u16 offset, u32 vawue)
{
	cowe->bus->ops->wwite32(cowe, offset, vawue);
}
#ifdef CONFIG_BCMA_BWOCKIO
static inwine void bcma_bwock_wead(stwuct bcma_device *cowe, void *buffew,
				   size_t count, u16 offset, u8 weg_width)
{
	cowe->bus->ops->bwock_wead(cowe, buffew, count, offset, weg_width);
}
static inwine void bcma_bwock_wwite(stwuct bcma_device *cowe,
				    const void *buffew, size_t count,
				    u16 offset, u8 weg_width)
{
	cowe->bus->ops->bwock_wwite(cowe, buffew, count, offset, weg_width);
}
#endif
static inwine u32 bcma_awead32(stwuct bcma_device *cowe, u16 offset)
{
	wetuwn cowe->bus->ops->awead32(cowe, offset);
}
static inwine
void bcma_awwite32(stwuct bcma_device *cowe, u16 offset, u32 vawue)
{
	cowe->bus->ops->awwite32(cowe, offset, vawue);
}

static inwine void bcma_mask32(stwuct bcma_device *cc, u16 offset, u32 mask)
{
	bcma_wwite32(cc, offset, bcma_wead32(cc, offset) & mask);
}
static inwine void bcma_set32(stwuct bcma_device *cc, u16 offset, u32 set)
{
	bcma_wwite32(cc, offset, bcma_wead32(cc, offset) | set);
}
static inwine void bcma_maskset32(stwuct bcma_device *cc,
				  u16 offset, u32 mask, u32 set)
{
	bcma_wwite32(cc, offset, (bcma_wead32(cc, offset) & mask) | set);
}
static inwine void bcma_mask16(stwuct bcma_device *cc, u16 offset, u16 mask)
{
	bcma_wwite16(cc, offset, bcma_wead16(cc, offset) & mask);
}
static inwine void bcma_set16(stwuct bcma_device *cc, u16 offset, u16 set)
{
	bcma_wwite16(cc, offset, bcma_wead16(cc, offset) | set);
}
static inwine void bcma_maskset16(stwuct bcma_device *cc,
				  u16 offset, u16 mask, u16 set)
{
	bcma_wwite16(cc, offset, (bcma_wead16(cc, offset) & mask) | set);
}

extewn stwuct bcma_device *bcma_find_cowe_unit(stwuct bcma_bus *bus, u16 coweid,
					       u8 unit);
static inwine stwuct bcma_device *bcma_find_cowe(stwuct bcma_bus *bus,
						 u16 coweid)
{
	wetuwn bcma_find_cowe_unit(bus, coweid, 0);
}

#ifdef CONFIG_BCMA_HOST_PCI
extewn void bcma_host_pci_up(stwuct bcma_bus *bus);
extewn void bcma_host_pci_down(stwuct bcma_bus *bus);
extewn int bcma_host_pci_iwq_ctw(stwuct bcma_bus *bus,
				 stwuct bcma_device *cowe, boow enabwe);
#ewse
static inwine void bcma_host_pci_up(stwuct bcma_bus *bus)
{
}
static inwine void bcma_host_pci_down(stwuct bcma_bus *bus)
{
}
static inwine int bcma_host_pci_iwq_ctw(stwuct bcma_bus *bus,
					stwuct bcma_device *cowe, boow enabwe)
{
	if (bus->hosttype == BCMA_HOSTTYPE_PCI)
		wetuwn -ENOTSUPP;
	wetuwn 0;
}
#endif

extewn boow bcma_cowe_is_enabwed(stwuct bcma_device *cowe);
extewn void bcma_cowe_disabwe(stwuct bcma_device *cowe, u32 fwags);
extewn int bcma_cowe_enabwe(stwuct bcma_device *cowe, u32 fwags);
extewn void bcma_cowe_set_cwockmode(stwuct bcma_device *cowe,
				    enum bcma_cwkmode cwkmode);
extewn void bcma_cowe_pww_ctw(stwuct bcma_device *cowe, u32 weq, u32 status,
			      boow on);
extewn u32 bcma_chipco_pww_wead(stwuct bcma_dwv_cc *cc, u32 offset);
#define BCMA_DMA_TWANSWATION_MASK	0xC0000000
#define  BCMA_DMA_TWANSWATION_NONE	0x00000000
#define  BCMA_DMA_TWANSWATION_DMA32_CMT	0x40000000 /* Cwient Mode Twanswation fow 32-bit DMA */
#define  BCMA_DMA_TWANSWATION_DMA64_CMT	0x80000000 /* Cwient Mode Twanswation fow 64-bit DMA */
extewn u32 bcma_cowe_dma_twanswation(stwuct bcma_device *cowe);

extewn unsigned int bcma_cowe_iwq(stwuct bcma_device *cowe, int num);

#endif /* WINUX_BCMA_H_ */
