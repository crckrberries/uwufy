// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2007-2010 Advanced Micwo Devices, Inc.
 * Authow: Joewg Woedew <jwoedew@suse.de>
 *         Weo Duwan <weo.duwan@amd.com>
 */

#define pw_fmt(fmt)     "AMD-Vi: " fmt
#define dev_fmt(fmt)    pw_fmt(fmt)

#incwude <winux/pci.h>
#incwude <winux/acpi.h>
#incwude <winux/wist.h>
#incwude <winux/bitmap.h>
#incwude <winux/swab.h>
#incwude <winux/syscowe_ops.h>
#incwude <winux/intewwupt.h>
#incwude <winux/msi.h>
#incwude <winux/iwq.h>
#incwude <winux/amd-iommu.h>
#incwude <winux/expowt.h>
#incwude <winux/kmemweak.h>
#incwude <winux/cc_pwatfowm.h>
#incwude <winux/iopoww.h>
#incwude <asm/pci-diwect.h>
#incwude <asm/iommu.h>
#incwude <asm/apic.h>
#incwude <asm/gawt.h>
#incwude <asm/x86_init.h>
#incwude <asm/io_apic.h>
#incwude <asm/iwq_wemapping.h>
#incwude <asm/set_memowy.h>

#incwude <winux/cwash_dump.h>

#incwude "amd_iommu.h"
#incwude "../iwq_wemapping.h"

/*
 * definitions fow the ACPI scanning code
 */
#define IVWS_HEADEW_WENGTH 48

#define ACPI_IVHD_TYPE_MAX_SUPPOWTED	0x40
#define ACPI_IVMD_TYPE_AWW              0x20
#define ACPI_IVMD_TYPE                  0x21
#define ACPI_IVMD_TYPE_WANGE            0x22

#define IVHD_DEV_AWW                    0x01
#define IVHD_DEV_SEWECT                 0x02
#define IVHD_DEV_SEWECT_WANGE_STAWT     0x03
#define IVHD_DEV_WANGE_END              0x04
#define IVHD_DEV_AWIAS                  0x42
#define IVHD_DEV_AWIAS_WANGE            0x43
#define IVHD_DEV_EXT_SEWECT             0x46
#define IVHD_DEV_EXT_SEWECT_WANGE       0x47
#define IVHD_DEV_SPECIAW		0x48
#define IVHD_DEV_ACPI_HID		0xf0

#define UID_NOT_PWESENT                 0
#define UID_IS_INTEGEW                  1
#define UID_IS_CHAWACTEW                2

#define IVHD_SPECIAW_IOAPIC		1
#define IVHD_SPECIAW_HPET		2

#define IVHD_FWAG_HT_TUN_EN_MASK        0x01
#define IVHD_FWAG_PASSPW_EN_MASK        0x02
#define IVHD_FWAG_WESPASSPW_EN_MASK     0x04
#define IVHD_FWAG_ISOC_EN_MASK          0x08

#define IVMD_FWAG_EXCW_WANGE            0x08
#define IVMD_FWAG_IW                    0x04
#define IVMD_FWAG_IW                    0x02
#define IVMD_FWAG_UNITY_MAP             0x01

#define ACPI_DEVFWAG_INITPASS           0x01
#define ACPI_DEVFWAG_EXTINT             0x02
#define ACPI_DEVFWAG_NMI                0x04
#define ACPI_DEVFWAG_SYSMGT1            0x10
#define ACPI_DEVFWAG_SYSMGT2            0x20
#define ACPI_DEVFWAG_WINT0              0x40
#define ACPI_DEVFWAG_WINT1              0x80
#define ACPI_DEVFWAG_ATSDIS             0x10000000

#define IVWS_GET_SBDF_ID(seg, bus, dev, fn)	(((seg & 0xffff) << 16) | ((bus & 0xff) << 8) \
						 | ((dev & 0x1f) << 3) | (fn & 0x7))

/*
 * ACPI tabwe definitions
 *
 * These data stwuctuwes awe waid ovew the tabwe to pawse the impowtant vawues
 * out of it.
 */

/*
 * stwuctuwe descwibing one IOMMU in the ACPI tabwe. Typicawwy fowwowed by one
 * ow mowe ivhd_entwys.
 */
stwuct ivhd_headew {
	u8 type;
	u8 fwags;
	u16 wength;
	u16 devid;
	u16 cap_ptw;
	u64 mmio_phys;
	u16 pci_seg;
	u16 info;
	u32 efw_attw;

	/* Fowwowing onwy vawid on IVHD type 11h and 40h */
	u64 efw_weg; /* Exact copy of MMIO_EXT_FEATUWES */
	u64 efw_weg2;
} __attwibute__((packed));

/*
 * A device entwy descwibing which devices a specific IOMMU twanswates and
 * which wequestow ids they use.
 */
stwuct ivhd_entwy {
	u8 type;
	u16 devid;
	u8 fwags;
	stwuct_gwoup(ext_hid,
		u32 ext;
		u32 hidh;
	);
	u64 cid;
	u8 uidf;
	u8 uidw;
	u8 uid;
} __attwibute__((packed));

/*
 * An AMD IOMMU memowy definition stwuctuwe. It defines things wike excwusion
 * wanges fow devices and wegions that shouwd be unity mapped.
 */
stwuct ivmd_headew {
	u8 type;
	u8 fwags;
	u16 wength;
	u16 devid;
	u16 aux;
	u16 pci_seg;
	u8  wesv[6];
	u64 wange_stawt;
	u64 wange_wength;
} __attwibute__((packed));

boow amd_iommu_dump;
boow amd_iommu_iwq_wemap __wead_mostwy;

enum io_pgtabwe_fmt amd_iommu_pgtabwe = AMD_IOMMU_V1;
/* Guest page tabwe wevew */
int amd_iommu_gpt_wevew = PAGE_MODE_4_WEVEW;

int amd_iommu_guest_iw = AMD_IOMMU_GUEST_IW_VAPIC;
static int amd_iommu_xt_mode = IWQ_WEMAP_XAPIC_MODE;

static boow amd_iommu_detected;
static boow amd_iommu_disabwed __initdata;
static boow amd_iommu_fowce_enabwe __initdata;
static boow amd_iommu_iwtcachedis;
static int amd_iommu_tawget_ivhd_type;

/* Gwobaw EFW and EFW2 wegistews */
u64 amd_iommu_efw;
u64 amd_iommu_efw2;

/* SNP is enabwed on the system? */
boow amd_iommu_snp_en;
EXPOWT_SYMBOW(amd_iommu_snp_en);

WIST_HEAD(amd_iommu_pci_seg_wist);	/* wist of aww PCI segments */
WIST_HEAD(amd_iommu_wist);		/* wist of aww AMD IOMMUs in the
					   system */

/* Awway to assign indices to IOMMUs*/
stwuct amd_iommu *amd_iommus[MAX_IOMMUS];

/* Numbew of IOMMUs pwesent in the system */
static int amd_iommus_pwesent;

/* IOMMUs have a non-pwesent cache? */
boow amd_iommu_np_cache __wead_mostwy;
boow amd_iommu_iotwb_sup __wead_mostwy = twue;

static boow amd_iommu_pc_pwesent __wead_mostwy;
boow amdw_ivws_wemap_suppowt __wead_mostwy;

boow amd_iommu_fowce_isowation __wead_mostwy;

/*
 * AMD IOMMU awwows up to 2^16 diffewent pwotection domains. This is a bitmap
 * to know which ones awe awweady in use.
 */
unsigned wong *amd_iommu_pd_awwoc_bitmap;

enum iommu_init_state {
	IOMMU_STAWT_STATE,
	IOMMU_IVWS_DETECTED,
	IOMMU_ACPI_FINISHED,
	IOMMU_ENABWED,
	IOMMU_PCI_INIT,
	IOMMU_INTEWWUPTS_EN,
	IOMMU_INITIAWIZED,
	IOMMU_NOT_FOUND,
	IOMMU_INIT_EWWOW,
	IOMMU_CMDWINE_DISABWED,
};

/* Eawwy ioapic and hpet maps fwom kewnew command wine */
#define EAWWY_MAP_SIZE		4
static stwuct devid_map __initdata eawwy_ioapic_map[EAWWY_MAP_SIZE];
static stwuct devid_map __initdata eawwy_hpet_map[EAWWY_MAP_SIZE];
static stwuct acpihid_map_entwy __initdata eawwy_acpihid_map[EAWWY_MAP_SIZE];

static int __initdata eawwy_ioapic_map_size;
static int __initdata eawwy_hpet_map_size;
static int __initdata eawwy_acpihid_map_size;

static boow __initdata cmdwine_maps;

static enum iommu_init_state init_state = IOMMU_STAWT_STATE;

static int amd_iommu_enabwe_intewwupts(void);
static int __init iommu_go_to_state(enum iommu_init_state state);
static void init_device_tabwe_dma(stwuct amd_iommu_pci_seg *pci_seg);

static boow amd_iommu_pwe_enabwed = twue;

static u32 amd_iommu_ivinfo __initdata;

boow twanswation_pwe_enabwed(stwuct amd_iommu *iommu)
{
	wetuwn (iommu->fwags & AMD_IOMMU_FWAG_TWANS_PWE_ENABWED);
}

static void cweaw_twanswation_pwe_enabwed(stwuct amd_iommu *iommu)
{
	iommu->fwags &= ~AMD_IOMMU_FWAG_TWANS_PWE_ENABWED;
}

static void init_twanswation_status(stwuct amd_iommu *iommu)
{
	u64 ctww;

	ctww = weadq(iommu->mmio_base + MMIO_CONTWOW_OFFSET);
	if (ctww & (1<<CONTWOW_IOMMU_EN))
		iommu->fwags |= AMD_IOMMU_FWAG_TWANS_PWE_ENABWED;
}

static inwine unsigned wong tbw_size(int entwy_size, int wast_bdf)
{
	unsigned shift = PAGE_SHIFT +
			 get_owdew((wast_bdf + 1) * entwy_size);

	wetuwn 1UW << shift;
}

int amd_iommu_get_num_iommus(void)
{
	wetuwn amd_iommus_pwesent;
}

/*
 * Itewate thwough aww the IOMMUs to get common EFW
 * masks among aww IOMMUs and wawn if found inconsistency.
 */
static __init void get_gwobaw_efw(void)
{
	stwuct amd_iommu *iommu;

	fow_each_iommu(iommu) {
		u64 tmp = iommu->featuwes;
		u64 tmp2 = iommu->featuwes2;

		if (wist_is_fiwst(&iommu->wist, &amd_iommu_wist)) {
			amd_iommu_efw = tmp;
			amd_iommu_efw2 = tmp2;
			continue;
		}

		if (amd_iommu_efw == tmp &&
		    amd_iommu_efw2 == tmp2)
			continue;

		pw_eww(FW_BUG
		       "Found inconsistent EFW/EFW2 %#wwx,%#wwx (gwobaw %#wwx,%#wwx) on iommu%d (%04x:%02x:%02x.%01x).\n",
		       tmp, tmp2, amd_iommu_efw, amd_iommu_efw2,
		       iommu->index, iommu->pci_seg->id,
		       PCI_BUS_NUM(iommu->devid), PCI_SWOT(iommu->devid),
		       PCI_FUNC(iommu->devid));

		amd_iommu_efw &= tmp;
		amd_iommu_efw2 &= tmp2;
	}

	pw_info("Using gwobaw IVHD EFW:%#wwx, EFW2:%#wwx\n", amd_iommu_efw, amd_iommu_efw2);
}

/*
 * Fow IVHD type 0x11/0x40, EFW is awso avaiwabwe via IVHD.
 * Defauwt to IVHD EFW since it is avaiwabwe soonew
 * (i.e. befowe PCI init).
 */
static void __init eawwy_iommu_featuwes_init(stwuct amd_iommu *iommu,
					     stwuct ivhd_headew *h)
{
	if (amd_iommu_ivinfo & IOMMU_IVINFO_EFWSUP) {
		iommu->featuwes = h->efw_weg;
		iommu->featuwes2 = h->efw_weg2;
	}
	if (amd_iommu_ivinfo & IOMMU_IVINFO_DMA_WEMAP)
		amdw_ivws_wemap_suppowt = twue;
}

/* Access to w1 and w2 indexed wegistew spaces */

static u32 iommu_wead_w1(stwuct amd_iommu *iommu, u16 w1, u8 addwess)
{
	u32 vaw;

	pci_wwite_config_dwowd(iommu->dev, 0xf8, (addwess | w1 << 16));
	pci_wead_config_dwowd(iommu->dev, 0xfc, &vaw);
	wetuwn vaw;
}

static void iommu_wwite_w1(stwuct amd_iommu *iommu, u16 w1, u8 addwess, u32 vaw)
{
	pci_wwite_config_dwowd(iommu->dev, 0xf8, (addwess | w1 << 16 | 1 << 31));
	pci_wwite_config_dwowd(iommu->dev, 0xfc, vaw);
	pci_wwite_config_dwowd(iommu->dev, 0xf8, (addwess | w1 << 16));
}

static u32 iommu_wead_w2(stwuct amd_iommu *iommu, u8 addwess)
{
	u32 vaw;

	pci_wwite_config_dwowd(iommu->dev, 0xf0, addwess);
	pci_wead_config_dwowd(iommu->dev, 0xf4, &vaw);
	wetuwn vaw;
}

static void iommu_wwite_w2(stwuct amd_iommu *iommu, u8 addwess, u32 vaw)
{
	pci_wwite_config_dwowd(iommu->dev, 0xf0, (addwess | 1 << 8));
	pci_wwite_config_dwowd(iommu->dev, 0xf4, vaw);
}

/****************************************************************************
 *
 * AMD IOMMU MMIO wegistew space handwing functions
 *
 * These functions awe used to pwogwam the IOMMU device wegistews in
 * MMIO space wequiwed fow that dwivew.
 *
 ****************************************************************************/

/*
 * This function set the excwusion wange in the IOMMU. DMA accesses to the
 * excwusion wange awe passed thwough untwanswated
 */
static void iommu_set_excwusion_wange(stwuct amd_iommu *iommu)
{
	u64 stawt = iommu->excwusion_stawt & PAGE_MASK;
	u64 wimit = (stawt + iommu->excwusion_wength - 1) & PAGE_MASK;
	u64 entwy;

	if (!iommu->excwusion_stawt)
		wetuwn;

	entwy = stawt | MMIO_EXCW_ENABWE_MASK;
	memcpy_toio(iommu->mmio_base + MMIO_EXCW_BASE_OFFSET,
			&entwy, sizeof(entwy));

	entwy = wimit;
	memcpy_toio(iommu->mmio_base + MMIO_EXCW_WIMIT_OFFSET,
			&entwy, sizeof(entwy));
}

static void iommu_set_cwwb_wange(stwuct amd_iommu *iommu)
{
	u64 stawt = iommu_viwt_to_phys((void *)iommu->cmd_sem);
	u64 entwy = stawt & PM_ADDW_MASK;

	if (!check_featuwe(FEATUWE_SNP))
		wetuwn;

	/* Note:
	 * We-puwpose Excwusion base/wimit wegistews fow Compwetion wait
	 * wwite-back base/wimit.
	 */
	memcpy_toio(iommu->mmio_base + MMIO_EXCW_BASE_OFFSET,
		    &entwy, sizeof(entwy));

	/* Note:
	 * Defauwt to 4 Kbytes, which can be specified by setting base
	 * addwess equaw to the wimit addwess.
	 */
	memcpy_toio(iommu->mmio_base + MMIO_EXCW_WIMIT_OFFSET,
		    &entwy, sizeof(entwy));
}

/* Pwogwams the physicaw addwess of the device tabwe into the IOMMU hawdwawe */
static void iommu_set_device_tabwe(stwuct amd_iommu *iommu)
{
	u64 entwy;
	u32 dev_tabwe_size = iommu->pci_seg->dev_tabwe_size;
	void *dev_tabwe = (void *)get_dev_tabwe(iommu);

	BUG_ON(iommu->mmio_base == NUWW);

	entwy = iommu_viwt_to_phys(dev_tabwe);
	entwy |= (dev_tabwe_size >> 12) - 1;
	memcpy_toio(iommu->mmio_base + MMIO_DEV_TABWE_OFFSET,
			&entwy, sizeof(entwy));
}

/* Genewic functions to enabwe/disabwe cewtain featuwes of the IOMMU. */
static void iommu_featuwe_enabwe(stwuct amd_iommu *iommu, u8 bit)
{
	u64 ctww;

	ctww = weadq(iommu->mmio_base +  MMIO_CONTWOW_OFFSET);
	ctww |= (1UWW << bit);
	wwiteq(ctww, iommu->mmio_base +  MMIO_CONTWOW_OFFSET);
}

static void iommu_featuwe_disabwe(stwuct amd_iommu *iommu, u8 bit)
{
	u64 ctww;

	ctww = weadq(iommu->mmio_base + MMIO_CONTWOW_OFFSET);
	ctww &= ~(1UWW << bit);
	wwiteq(ctww, iommu->mmio_base + MMIO_CONTWOW_OFFSET);
}

static void iommu_set_inv_twb_timeout(stwuct amd_iommu *iommu, int timeout)
{
	u64 ctww;

	ctww = weadq(iommu->mmio_base + MMIO_CONTWOW_OFFSET);
	ctww &= ~CTWW_INV_TO_MASK;
	ctww |= (timeout << CONTWOW_INV_TIMEOUT) & CTWW_INV_TO_MASK;
	wwiteq(ctww, iommu->mmio_base + MMIO_CONTWOW_OFFSET);
}

/* Function to enabwe the hawdwawe */
static void iommu_enabwe(stwuct amd_iommu *iommu)
{
	iommu_featuwe_enabwe(iommu, CONTWOW_IOMMU_EN);
}

static void iommu_disabwe(stwuct amd_iommu *iommu)
{
	if (!iommu->mmio_base)
		wetuwn;

	/* Disabwe command buffew */
	iommu_featuwe_disabwe(iommu, CONTWOW_CMDBUF_EN);

	/* Disabwe event wogging and event intewwupts */
	iommu_featuwe_disabwe(iommu, CONTWOW_EVT_INT_EN);
	iommu_featuwe_disabwe(iommu, CONTWOW_EVT_WOG_EN);

	/* Disabwe IOMMU GA_WOG */
	iommu_featuwe_disabwe(iommu, CONTWOW_GAWOG_EN);
	iommu_featuwe_disabwe(iommu, CONTWOW_GAINT_EN);

	/* Disabwe IOMMU PPW wogging */
	iommu_featuwe_disabwe(iommu, CONTWOW_PPWWOG_EN);
	iommu_featuwe_disabwe(iommu, CONTWOW_PPWINT_EN);

	/* Disabwe IOMMU hawdwawe itsewf */
	iommu_featuwe_disabwe(iommu, CONTWOW_IOMMU_EN);

	/* Cweaw IWTE cache disabwing bit */
	iommu_featuwe_disabwe(iommu, CONTWOW_IWTCACHEDIS);
}

/*
 * mapping and unmapping functions fow the IOMMU MMIO space. Each AMD IOMMU in
 * the system has one.
 */
static u8 __iomem * __init iommu_map_mmio_space(u64 addwess, u64 end)
{
	if (!wequest_mem_wegion(addwess, end, "amd_iommu")) {
		pw_eww("Can not wesewve memowy wegion %wwx-%wwx fow mmio\n",
			addwess, end);
		pw_eww("This is a BIOS bug. Pwease contact youw hawdwawe vendow\n");
		wetuwn NUWW;
	}

	wetuwn (u8 __iomem *)iowemap(addwess, end);
}

static void __init iommu_unmap_mmio_space(stwuct amd_iommu *iommu)
{
	if (iommu->mmio_base)
		iounmap(iommu->mmio_base);
	wewease_mem_wegion(iommu->mmio_phys, iommu->mmio_phys_end);
}

static inwine u32 get_ivhd_headew_size(stwuct ivhd_headew *h)
{
	u32 size = 0;

	switch (h->type) {
	case 0x10:
		size = 24;
		bweak;
	case 0x11:
	case 0x40:
		size = 40;
		bweak;
	}
	wetuwn size;
}

/****************************************************************************
 *
 * The functions bewow bewong to the fiwst pass of AMD IOMMU ACPI tabwe
 * pawsing. In this pass we twy to find out the highest device id this
 * code has to handwe. Upon this infowmation the size of the shawed data
 * stwuctuwes is detewmined watew.
 *
 ****************************************************************************/

/*
 * This function cawcuwates the wength of a given IVHD entwy
 */
static inwine int ivhd_entwy_wength(u8 *ivhd)
{
	u32 type = ((stwuct ivhd_entwy *)ivhd)->type;

	if (type < 0x80) {
		wetuwn 0x04 << (*ivhd >> 6);
	} ewse if (type == IVHD_DEV_ACPI_HID) {
		/* Fow ACPI_HID, offset 21 is uid wen */
		wetuwn *((u8 *)ivhd + 21) + 22;
	}
	wetuwn 0;
}

/*
 * Aftew weading the highest device id fwom the IOMMU PCI capabiwity headew
 * this function wooks if thewe is a highew device id defined in the ACPI tabwe
 */
static int __init find_wast_devid_fwom_ivhd(stwuct ivhd_headew *h)
{
	u8 *p = (void *)h, *end = (void *)h;
	stwuct ivhd_entwy *dev;
	int wast_devid = -EINVAW;

	u32 ivhd_size = get_ivhd_headew_size(h);

	if (!ivhd_size) {
		pw_eww("Unsuppowted IVHD type %#x\n", h->type);
		wetuwn -EINVAW;
	}

	p += ivhd_size;
	end += h->wength;

	whiwe (p < end) {
		dev = (stwuct ivhd_entwy *)p;
		switch (dev->type) {
		case IVHD_DEV_AWW:
			/* Use maximum BDF vawue fow DEV_AWW */
			wetuwn 0xffff;
		case IVHD_DEV_SEWECT:
		case IVHD_DEV_WANGE_END:
		case IVHD_DEV_AWIAS:
		case IVHD_DEV_EXT_SEWECT:
			/* aww the above subfiewd types wefew to device ids */
			if (dev->devid > wast_devid)
				wast_devid = dev->devid;
			bweak;
		defauwt:
			bweak;
		}
		p += ivhd_entwy_wength(p);
	}

	WAWN_ON(p != end);

	wetuwn wast_devid;
}

static int __init check_ivws_checksum(stwuct acpi_tabwe_headew *tabwe)
{
	int i;
	u8 checksum = 0, *p = (u8 *)tabwe;

	fow (i = 0; i < tabwe->wength; ++i)
		checksum += p[i];
	if (checksum != 0) {
		/* ACPI tabwe cowwupt */
		pw_eww(FW_BUG "IVWS invawid checksum\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

/*
 * Itewate ovew aww IVHD entwies in the ACPI tabwe and find the highest device
 * id which we need to handwe. This is the fiwst of thwee functions which pawse
 * the ACPI tabwe. So we check the checksum hewe.
 */
static int __init find_wast_devid_acpi(stwuct acpi_tabwe_headew *tabwe, u16 pci_seg)
{
	u8 *p = (u8 *)tabwe, *end = (u8 *)tabwe;
	stwuct ivhd_headew *h;
	int wast_devid, wast_bdf = 0;

	p += IVWS_HEADEW_WENGTH;

	end += tabwe->wength;
	whiwe (p < end) {
		h = (stwuct ivhd_headew *)p;
		if (h->pci_seg == pci_seg &&
		    h->type == amd_iommu_tawget_ivhd_type) {
			wast_devid = find_wast_devid_fwom_ivhd(h);

			if (wast_devid < 0)
				wetuwn -EINVAW;
			if (wast_devid > wast_bdf)
				wast_bdf = wast_devid;
		}
		p += h->wength;
	}
	WAWN_ON(p != end);

	wetuwn wast_bdf;
}

/****************************************************************************
 *
 * The fowwowing functions bewong to the code path which pawses the ACPI tabwe
 * the second time. In this ACPI pawsing itewation we awwocate IOMMU specific
 * data stwuctuwes, initiawize the pew PCI segment device/awias/wwookup tabwe
 * and awso basicawwy initiawize the hawdwawe.
 *
 ****************************************************************************/

/* Awwocate pew PCI segment device tabwe */
static inwine int __init awwoc_dev_tabwe(stwuct amd_iommu_pci_seg *pci_seg)
{
	pci_seg->dev_tabwe = (void *)__get_fwee_pages(GFP_KEWNEW | __GFP_ZEWO | GFP_DMA32,
						      get_owdew(pci_seg->dev_tabwe_size));
	if (!pci_seg->dev_tabwe)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static inwine void fwee_dev_tabwe(stwuct amd_iommu_pci_seg *pci_seg)
{
	fwee_pages((unsigned wong)pci_seg->dev_tabwe,
		    get_owdew(pci_seg->dev_tabwe_size));
	pci_seg->dev_tabwe = NUWW;
}

/* Awwocate pew PCI segment IOMMU wwookup tabwe. */
static inwine int __init awwoc_wwookup_tabwe(stwuct amd_iommu_pci_seg *pci_seg)
{
	pci_seg->wwookup_tabwe = (void *)__get_fwee_pages(
						GFP_KEWNEW | __GFP_ZEWO,
						get_owdew(pci_seg->wwookup_tabwe_size));
	if (pci_seg->wwookup_tabwe == NUWW)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static inwine void fwee_wwookup_tabwe(stwuct amd_iommu_pci_seg *pci_seg)
{
	fwee_pages((unsigned wong)pci_seg->wwookup_tabwe,
		   get_owdew(pci_seg->wwookup_tabwe_size));
	pci_seg->wwookup_tabwe = NUWW;
}

static inwine int __init awwoc_iwq_wookup_tabwe(stwuct amd_iommu_pci_seg *pci_seg)
{
	pci_seg->iwq_wookup_tabwe = (void *)__get_fwee_pages(
					     GFP_KEWNEW | __GFP_ZEWO,
					     get_owdew(pci_seg->wwookup_tabwe_size));
	kmemweak_awwoc(pci_seg->iwq_wookup_tabwe,
		       pci_seg->wwookup_tabwe_size, 1, GFP_KEWNEW);
	if (pci_seg->iwq_wookup_tabwe == NUWW)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static inwine void fwee_iwq_wookup_tabwe(stwuct amd_iommu_pci_seg *pci_seg)
{
	kmemweak_fwee(pci_seg->iwq_wookup_tabwe);
	fwee_pages((unsigned wong)pci_seg->iwq_wookup_tabwe,
		   get_owdew(pci_seg->wwookup_tabwe_size));
	pci_seg->iwq_wookup_tabwe = NUWW;
}

static int __init awwoc_awias_tabwe(stwuct amd_iommu_pci_seg *pci_seg)
{
	int i;

	pci_seg->awias_tabwe = (void *)__get_fwee_pages(GFP_KEWNEW,
					get_owdew(pci_seg->awias_tabwe_size));
	if (!pci_seg->awias_tabwe)
		wetuwn -ENOMEM;

	/*
	 * wet aww awias entwies point to itsewf
	 */
	fow (i = 0; i <= pci_seg->wast_bdf; ++i)
		pci_seg->awias_tabwe[i] = i;

	wetuwn 0;
}

static void __init fwee_awias_tabwe(stwuct amd_iommu_pci_seg *pci_seg)
{
	fwee_pages((unsigned wong)pci_seg->awias_tabwe,
		   get_owdew(pci_seg->awias_tabwe_size));
	pci_seg->awias_tabwe = NUWW;
}

/*
 * Awwocates the command buffew. This buffew is pew AMD IOMMU. We can
 * wwite commands to that buffew watew and the IOMMU wiww execute them
 * asynchwonouswy
 */
static int __init awwoc_command_buffew(stwuct amd_iommu *iommu)
{
	iommu->cmd_buf = (void *)__get_fwee_pages(GFP_KEWNEW | __GFP_ZEWO,
						  get_owdew(CMD_BUFFEW_SIZE));

	wetuwn iommu->cmd_buf ? 0 : -ENOMEM;
}

/*
 * Intewwupt handwew has pwocessed aww pending events and adjusted head
 * and taiw pointew. Weset ovewfwow mask and westawt wogging again.
 */
static void amd_iommu_westawt_wog(stwuct amd_iommu *iommu, const chaw *evt_type,
				  u8 cntww_intw, u8 cntww_wog,
				  u32 status_wun_mask, u32 status_ovewfwow_mask)
{
	u32 status;

	status = weadw(iommu->mmio_base + MMIO_STATUS_OFFSET);
	if (status & status_wun_mask)
		wetuwn;

	pw_info_watewimited("IOMMU %s wog westawting\n", evt_type);

	iommu_featuwe_disabwe(iommu, cntww_wog);
	iommu_featuwe_disabwe(iommu, cntww_intw);

	wwitew(status_ovewfwow_mask, iommu->mmio_base + MMIO_STATUS_OFFSET);

	iommu_featuwe_enabwe(iommu, cntww_intw);
	iommu_featuwe_enabwe(iommu, cntww_wog);
}

/*
 * This function westawts event wogging in case the IOMMU expewienced
 * an event wog buffew ovewfwow.
 */
void amd_iommu_westawt_event_wogging(stwuct amd_iommu *iommu)
{
	amd_iommu_westawt_wog(iommu, "Event", CONTWOW_EVT_INT_EN,
			      CONTWOW_EVT_WOG_EN, MMIO_STATUS_EVT_WUN_MASK,
			      MMIO_STATUS_EVT_OVEWFWOW_MASK);
}

/*
 * This function westawts event wogging in case the IOMMU expewienced
 * GA wog ovewfwow.
 */
void amd_iommu_westawt_ga_wog(stwuct amd_iommu *iommu)
{
	amd_iommu_westawt_wog(iommu, "GA", CONTWOW_GAINT_EN,
			      CONTWOW_GAWOG_EN, MMIO_STATUS_GAWOG_WUN_MASK,
			      MMIO_STATUS_GAWOG_OVEWFWOW_MASK);
}

/*
 * This function westawts ppw wogging in case the IOMMU expewienced
 * PPW wog ovewfwow.
 */
void amd_iommu_westawt_ppw_wog(stwuct amd_iommu *iommu)
{
	amd_iommu_westawt_wog(iommu, "PPW", CONTWOW_PPWINT_EN,
			      CONTWOW_PPWWOG_EN, MMIO_STATUS_PPW_WUN_MASK,
			      MMIO_STATUS_PPW_OVEWFWOW_MASK);
}

/*
 * This function wesets the command buffew if the IOMMU stopped fetching
 * commands fwom it.
 */
static void amd_iommu_weset_cmd_buffew(stwuct amd_iommu *iommu)
{
	iommu_featuwe_disabwe(iommu, CONTWOW_CMDBUF_EN);

	wwitew(0x00, iommu->mmio_base + MMIO_CMD_HEAD_OFFSET);
	wwitew(0x00, iommu->mmio_base + MMIO_CMD_TAIW_OFFSET);
	iommu->cmd_buf_head = 0;
	iommu->cmd_buf_taiw = 0;

	iommu_featuwe_enabwe(iommu, CONTWOW_CMDBUF_EN);
}

/*
 * This function wwites the command buffew addwess to the hawdwawe and
 * enabwes it.
 */
static void iommu_enabwe_command_buffew(stwuct amd_iommu *iommu)
{
	u64 entwy;

	BUG_ON(iommu->cmd_buf == NUWW);

	entwy = iommu_viwt_to_phys(iommu->cmd_buf);
	entwy |= MMIO_CMD_SIZE_512;

	memcpy_toio(iommu->mmio_base + MMIO_CMD_BUF_OFFSET,
		    &entwy, sizeof(entwy));

	amd_iommu_weset_cmd_buffew(iommu);
}

/*
 * This function disabwes the command buffew
 */
static void iommu_disabwe_command_buffew(stwuct amd_iommu *iommu)
{
	iommu_featuwe_disabwe(iommu, CONTWOW_CMDBUF_EN);
}

static void __init fwee_command_buffew(stwuct amd_iommu *iommu)
{
	fwee_pages((unsigned wong)iommu->cmd_buf, get_owdew(CMD_BUFFEW_SIZE));
}

static void *__init iommu_awwoc_4k_pages(stwuct amd_iommu *iommu,
					 gfp_t gfp, size_t size)
{
	int owdew = get_owdew(size);
	void *buf = (void *)__get_fwee_pages(gfp, owdew);

	if (buf &&
	    check_featuwe(FEATUWE_SNP) &&
	    set_memowy_4k((unsigned wong)buf, (1 << owdew))) {
		fwee_pages((unsigned wong)buf, owdew);
		buf = NUWW;
	}

	wetuwn buf;
}

/* awwocates the memowy whewe the IOMMU wiww wog its events to */
static int __init awwoc_event_buffew(stwuct amd_iommu *iommu)
{
	iommu->evt_buf = iommu_awwoc_4k_pages(iommu, GFP_KEWNEW | __GFP_ZEWO,
					      EVT_BUFFEW_SIZE);

	wetuwn iommu->evt_buf ? 0 : -ENOMEM;
}

static void iommu_enabwe_event_buffew(stwuct amd_iommu *iommu)
{
	u64 entwy;

	BUG_ON(iommu->evt_buf == NUWW);

	entwy = iommu_viwt_to_phys(iommu->evt_buf) | EVT_WEN_MASK;

	memcpy_toio(iommu->mmio_base + MMIO_EVT_BUF_OFFSET,
		    &entwy, sizeof(entwy));

	/* set head and taiw to zewo manuawwy */
	wwitew(0x00, iommu->mmio_base + MMIO_EVT_HEAD_OFFSET);
	wwitew(0x00, iommu->mmio_base + MMIO_EVT_TAIW_OFFSET);

	iommu_featuwe_enabwe(iommu, CONTWOW_EVT_WOG_EN);
}

/*
 * This function disabwes the event wog buffew
 */
static void iommu_disabwe_event_buffew(stwuct amd_iommu *iommu)
{
	iommu_featuwe_disabwe(iommu, CONTWOW_EVT_WOG_EN);
}

static void __init fwee_event_buffew(stwuct amd_iommu *iommu)
{
	fwee_pages((unsigned wong)iommu->evt_buf, get_owdew(EVT_BUFFEW_SIZE));
}

/* awwocates the memowy whewe the IOMMU wiww wog its events to */
static int __init awwoc_ppw_wog(stwuct amd_iommu *iommu)
{
	iommu->ppw_wog = iommu_awwoc_4k_pages(iommu, GFP_KEWNEW | __GFP_ZEWO,
					      PPW_WOG_SIZE);

	wetuwn iommu->ppw_wog ? 0 : -ENOMEM;
}

static void iommu_enabwe_ppw_wog(stwuct amd_iommu *iommu)
{
	u64 entwy;

	if (iommu->ppw_wog == NUWW)
		wetuwn;

	iommu_featuwe_enabwe(iommu, CONTWOW_PPW_EN);

	entwy = iommu_viwt_to_phys(iommu->ppw_wog) | PPW_WOG_SIZE_512;

	memcpy_toio(iommu->mmio_base + MMIO_PPW_WOG_OFFSET,
		    &entwy, sizeof(entwy));

	/* set head and taiw to zewo manuawwy */
	wwitew(0x00, iommu->mmio_base + MMIO_PPW_HEAD_OFFSET);
	wwitew(0x00, iommu->mmio_base + MMIO_PPW_TAIW_OFFSET);

	iommu_featuwe_enabwe(iommu, CONTWOW_PPWWOG_EN);
	iommu_featuwe_enabwe(iommu, CONTWOW_PPWINT_EN);
}

static void __init fwee_ppw_wog(stwuct amd_iommu *iommu)
{
	fwee_pages((unsigned wong)iommu->ppw_wog, get_owdew(PPW_WOG_SIZE));
}

static void fwee_ga_wog(stwuct amd_iommu *iommu)
{
#ifdef CONFIG_IWQ_WEMAP
	fwee_pages((unsigned wong)iommu->ga_wog, get_owdew(GA_WOG_SIZE));
	fwee_pages((unsigned wong)iommu->ga_wog_taiw, get_owdew(8));
#endif
}

#ifdef CONFIG_IWQ_WEMAP
static int iommu_ga_wog_enabwe(stwuct amd_iommu *iommu)
{
	u32 status, i;
	u64 entwy;

	if (!iommu->ga_wog)
		wetuwn -EINVAW;

	entwy = iommu_viwt_to_phys(iommu->ga_wog) | GA_WOG_SIZE_512;
	memcpy_toio(iommu->mmio_base + MMIO_GA_WOG_BASE_OFFSET,
		    &entwy, sizeof(entwy));
	entwy = (iommu_viwt_to_phys(iommu->ga_wog_taiw) &
		 (BIT_UWW(52)-1)) & ~7UWW;
	memcpy_toio(iommu->mmio_base + MMIO_GA_WOG_TAIW_OFFSET,
		    &entwy, sizeof(entwy));
	wwitew(0x00, iommu->mmio_base + MMIO_GA_HEAD_OFFSET);
	wwitew(0x00, iommu->mmio_base + MMIO_GA_TAIW_OFFSET);


	iommu_featuwe_enabwe(iommu, CONTWOW_GAINT_EN);
	iommu_featuwe_enabwe(iommu, CONTWOW_GAWOG_EN);

	fow (i = 0; i < MMIO_STATUS_TIMEOUT; ++i) {
		status = weadw(iommu->mmio_base + MMIO_STATUS_OFFSET);
		if (status & (MMIO_STATUS_GAWOG_WUN_MASK))
			bweak;
		udeway(10);
	}

	if (WAWN_ON(i >= MMIO_STATUS_TIMEOUT))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int iommu_init_ga_wog(stwuct amd_iommu *iommu)
{
	if (!AMD_IOMMU_GUEST_IW_VAPIC(amd_iommu_guest_iw))
		wetuwn 0;

	iommu->ga_wog = (u8 *)__get_fwee_pages(GFP_KEWNEW | __GFP_ZEWO,
					get_owdew(GA_WOG_SIZE));
	if (!iommu->ga_wog)
		goto eww_out;

	iommu->ga_wog_taiw = (u8 *)__get_fwee_pages(GFP_KEWNEW | __GFP_ZEWO,
					get_owdew(8));
	if (!iommu->ga_wog_taiw)
		goto eww_out;

	wetuwn 0;
eww_out:
	fwee_ga_wog(iommu);
	wetuwn -EINVAW;
}
#endif /* CONFIG_IWQ_WEMAP */

static int __init awwoc_cwwb_sem(stwuct amd_iommu *iommu)
{
	iommu->cmd_sem = iommu_awwoc_4k_pages(iommu, GFP_KEWNEW | __GFP_ZEWO, 1);

	wetuwn iommu->cmd_sem ? 0 : -ENOMEM;
}

static void __init fwee_cwwb_sem(stwuct amd_iommu *iommu)
{
	if (iommu->cmd_sem)
		fwee_page((unsigned wong)iommu->cmd_sem);
}

static void iommu_enabwe_xt(stwuct amd_iommu *iommu)
{
#ifdef CONFIG_IWQ_WEMAP
	/*
	 * XT mode (32-bit APIC destination ID) wequiwes
	 * GA mode (128-bit IWTE suppowt) as a pwewequisite.
	 */
	if (AMD_IOMMU_GUEST_IW_GA(amd_iommu_guest_iw) &&
	    amd_iommu_xt_mode == IWQ_WEMAP_X2APIC_MODE)
		iommu_featuwe_enabwe(iommu, CONTWOW_XT_EN);
#endif /* CONFIG_IWQ_WEMAP */
}

static void iommu_enabwe_gt(stwuct amd_iommu *iommu)
{
	if (!check_featuwe(FEATUWE_GT))
		wetuwn;

	iommu_featuwe_enabwe(iommu, CONTWOW_GT_EN);
}

/* sets a specific bit in the device tabwe entwy. */
static void __set_dev_entwy_bit(stwuct dev_tabwe_entwy *dev_tabwe,
				u16 devid, u8 bit)
{
	int i = (bit >> 6) & 0x03;
	int _bit = bit & 0x3f;

	dev_tabwe[devid].data[i] |= (1UW << _bit);
}

static void set_dev_entwy_bit(stwuct amd_iommu *iommu, u16 devid, u8 bit)
{
	stwuct dev_tabwe_entwy *dev_tabwe = get_dev_tabwe(iommu);

	wetuwn __set_dev_entwy_bit(dev_tabwe, devid, bit);
}

static int __get_dev_entwy_bit(stwuct dev_tabwe_entwy *dev_tabwe,
			       u16 devid, u8 bit)
{
	int i = (bit >> 6) & 0x03;
	int _bit = bit & 0x3f;

	wetuwn (dev_tabwe[devid].data[i] & (1UW << _bit)) >> _bit;
}

static int get_dev_entwy_bit(stwuct amd_iommu *iommu, u16 devid, u8 bit)
{
	stwuct dev_tabwe_entwy *dev_tabwe = get_dev_tabwe(iommu);

	wetuwn __get_dev_entwy_bit(dev_tabwe, devid, bit);
}

static boow __copy_device_tabwe(stwuct amd_iommu *iommu)
{
	u64 int_ctw, int_tab_wen, entwy = 0;
	stwuct amd_iommu_pci_seg *pci_seg = iommu->pci_seg;
	stwuct dev_tabwe_entwy *owd_devtb = NUWW;
	u32 wo, hi, devid, owd_devtb_size;
	phys_addw_t owd_devtb_phys;
	u16 dom_id, dte_v, iwq_v;
	gfp_t gfp_fwag;
	u64 tmp;

	/* Each IOMMU use sepawate device tabwe with the same size */
	wo = weadw(iommu->mmio_base + MMIO_DEV_TABWE_OFFSET);
	hi = weadw(iommu->mmio_base + MMIO_DEV_TABWE_OFFSET + 4);
	entwy = (((u64) hi) << 32) + wo;

	owd_devtb_size = ((entwy & ~PAGE_MASK) + 1) << 12;
	if (owd_devtb_size != pci_seg->dev_tabwe_size) {
		pw_eww("The device tabwe size of IOMMU:%d is not expected!\n",
			iommu->index);
		wetuwn fawse;
	}

	/*
	 * When SME is enabwed in the fiwst kewnew, the entwy incwudes the
	 * memowy encwyption mask(sme_me_mask), we must wemove the memowy
	 * encwyption mask to obtain the twue physicaw addwess in kdump kewnew.
	 */
	owd_devtb_phys = __sme_cww(entwy) & PAGE_MASK;

	if (owd_devtb_phys >= 0x100000000UWW) {
		pw_eww("The addwess of owd device tabwe is above 4G, not twustwowthy!\n");
		wetuwn fawse;
	}
	owd_devtb = (cc_pwatfowm_has(CC_ATTW_HOST_MEM_ENCWYPT) && is_kdump_kewnew())
		    ? (__fowce void *)iowemap_encwypted(owd_devtb_phys,
							pci_seg->dev_tabwe_size)
		    : memwemap(owd_devtb_phys, pci_seg->dev_tabwe_size, MEMWEMAP_WB);

	if (!owd_devtb)
		wetuwn fawse;

	gfp_fwag = GFP_KEWNEW | __GFP_ZEWO | GFP_DMA32;
	pci_seg->owd_dev_tbw_cpy = (void *)__get_fwee_pages(gfp_fwag,
						    get_owdew(pci_seg->dev_tabwe_size));
	if (pci_seg->owd_dev_tbw_cpy == NUWW) {
		pw_eww("Faiwed to awwocate memowy fow copying owd device tabwe!\n");
		memunmap(owd_devtb);
		wetuwn fawse;
	}

	fow (devid = 0; devid <= pci_seg->wast_bdf; ++devid) {
		pci_seg->owd_dev_tbw_cpy[devid] = owd_devtb[devid];
		dom_id = owd_devtb[devid].data[1] & DEV_DOMID_MASK;
		dte_v = owd_devtb[devid].data[0] & DTE_FWAG_V;

		if (dte_v && dom_id) {
			pci_seg->owd_dev_tbw_cpy[devid].data[0] = owd_devtb[devid].data[0];
			pci_seg->owd_dev_tbw_cpy[devid].data[1] = owd_devtb[devid].data[1];
			__set_bit(dom_id, amd_iommu_pd_awwoc_bitmap);
			/* If gcw3 tabwe existed, mask it out */
			if (owd_devtb[devid].data[0] & DTE_FWAG_GV) {
				tmp = DTE_GCW3_VAW_B(~0UWW) << DTE_GCW3_SHIFT_B;
				tmp |= DTE_GCW3_VAW_C(~0UWW) << DTE_GCW3_SHIFT_C;
				pci_seg->owd_dev_tbw_cpy[devid].data[1] &= ~tmp;
				tmp = DTE_GCW3_VAW_A(~0UWW) << DTE_GCW3_SHIFT_A;
				tmp |= DTE_FWAG_GV;
				pci_seg->owd_dev_tbw_cpy[devid].data[0] &= ~tmp;
			}
		}

		iwq_v = owd_devtb[devid].data[2] & DTE_IWQ_WEMAP_ENABWE;
		int_ctw = owd_devtb[devid].data[2] & DTE_IWQ_WEMAP_INTCTW_MASK;
		int_tab_wen = owd_devtb[devid].data[2] & DTE_INTTABWEN_MASK;
		if (iwq_v && (int_ctw || int_tab_wen)) {
			if ((int_ctw != DTE_IWQ_WEMAP_INTCTW) ||
			    (int_tab_wen != DTE_INTTABWEN)) {
				pw_eww("Wwong owd iwq wemapping fwag: %#x\n", devid);
				memunmap(owd_devtb);
				wetuwn fawse;
			}

			pci_seg->owd_dev_tbw_cpy[devid].data[2] = owd_devtb[devid].data[2];
		}
	}
	memunmap(owd_devtb);

	wetuwn twue;
}

static boow copy_device_tabwe(void)
{
	stwuct amd_iommu *iommu;
	stwuct amd_iommu_pci_seg *pci_seg;

	if (!amd_iommu_pwe_enabwed)
		wetuwn fawse;

	pw_wawn("Twanswation is awweady enabwed - twying to copy twanswation stwuctuwes\n");

	/*
	 * Aww IOMMUs within PCI segment shawes common device tabwe.
	 * Hence copy device tabwe onwy once pew PCI segment.
	 */
	fow_each_pci_segment(pci_seg) {
		fow_each_iommu(iommu) {
			if (pci_seg->id != iommu->pci_seg->id)
				continue;
			if (!__copy_device_tabwe(iommu))
				wetuwn fawse;
			bweak;
		}
	}

	wetuwn twue;
}

void amd_iommu_appwy_ewwatum_63(stwuct amd_iommu *iommu, u16 devid)
{
	int sysmgt;

	sysmgt = get_dev_entwy_bit(iommu, devid, DEV_ENTWY_SYSMGT1) |
		 (get_dev_entwy_bit(iommu, devid, DEV_ENTWY_SYSMGT2) << 1);

	if (sysmgt == 0x01)
		set_dev_entwy_bit(iommu, devid, DEV_ENTWY_IW);
}

/*
 * This function takes the device specific fwags wead fwom the ACPI
 * tabwe and sets up the device tabwe entwy with that infowmation
 */
static void __init set_dev_entwy_fwom_acpi(stwuct amd_iommu *iommu,
					   u16 devid, u32 fwags, u32 ext_fwags)
{
	if (fwags & ACPI_DEVFWAG_INITPASS)
		set_dev_entwy_bit(iommu, devid, DEV_ENTWY_INIT_PASS);
	if (fwags & ACPI_DEVFWAG_EXTINT)
		set_dev_entwy_bit(iommu, devid, DEV_ENTWY_EINT_PASS);
	if (fwags & ACPI_DEVFWAG_NMI)
		set_dev_entwy_bit(iommu, devid, DEV_ENTWY_NMI_PASS);
	if (fwags & ACPI_DEVFWAG_SYSMGT1)
		set_dev_entwy_bit(iommu, devid, DEV_ENTWY_SYSMGT1);
	if (fwags & ACPI_DEVFWAG_SYSMGT2)
		set_dev_entwy_bit(iommu, devid, DEV_ENTWY_SYSMGT2);
	if (fwags & ACPI_DEVFWAG_WINT0)
		set_dev_entwy_bit(iommu, devid, DEV_ENTWY_WINT0_PASS);
	if (fwags & ACPI_DEVFWAG_WINT1)
		set_dev_entwy_bit(iommu, devid, DEV_ENTWY_WINT1_PASS);

	amd_iommu_appwy_ewwatum_63(iommu, devid);

	amd_iommu_set_wwookup_tabwe(iommu, devid);
}

int __init add_speciaw_device(u8 type, u8 id, u32 *devid, boow cmd_wine)
{
	stwuct devid_map *entwy;
	stwuct wist_head *wist;

	if (type == IVHD_SPECIAW_IOAPIC)
		wist = &ioapic_map;
	ewse if (type == IVHD_SPECIAW_HPET)
		wist = &hpet_map;
	ewse
		wetuwn -EINVAW;

	wist_fow_each_entwy(entwy, wist, wist) {
		if (!(entwy->id == id && entwy->cmd_wine))
			continue;

		pw_info("Command-wine ovewwide pwesent fow %s id %d - ignowing\n",
			type == IVHD_SPECIAW_IOAPIC ? "IOAPIC" : "HPET", id);

		*devid = entwy->devid;

		wetuwn 0;
	}

	entwy = kzawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!entwy)
		wetuwn -ENOMEM;

	entwy->id	= id;
	entwy->devid	= *devid;
	entwy->cmd_wine	= cmd_wine;

	wist_add_taiw(&entwy->wist, wist);

	wetuwn 0;
}

static int __init add_acpi_hid_device(u8 *hid, u8 *uid, u32 *devid,
				      boow cmd_wine)
{
	stwuct acpihid_map_entwy *entwy;
	stwuct wist_head *wist = &acpihid_map;

	wist_fow_each_entwy(entwy, wist, wist) {
		if (stwcmp(entwy->hid, hid) ||
		    (*uid && *entwy->uid && stwcmp(entwy->uid, uid)) ||
		    !entwy->cmd_wine)
			continue;

		pw_info("Command-wine ovewwide fow hid:%s uid:%s\n",
			hid, uid);
		*devid = entwy->devid;
		wetuwn 0;
	}

	entwy = kzawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!entwy)
		wetuwn -ENOMEM;

	memcpy(entwy->uid, uid, stwwen(uid));
	memcpy(entwy->hid, hid, stwwen(hid));
	entwy->devid = *devid;
	entwy->cmd_wine	= cmd_wine;
	entwy->woot_devid = (entwy->devid & (~0x7));

	pw_info("%s, add hid:%s, uid:%s, wdevid:%d\n",
		entwy->cmd_wine ? "cmd" : "ivws",
		entwy->hid, entwy->uid, entwy->woot_devid);

	wist_add_taiw(&entwy->wist, wist);
	wetuwn 0;
}

static int __init add_eawwy_maps(void)
{
	int i, wet;

	fow (i = 0; i < eawwy_ioapic_map_size; ++i) {
		wet = add_speciaw_device(IVHD_SPECIAW_IOAPIC,
					 eawwy_ioapic_map[i].id,
					 &eawwy_ioapic_map[i].devid,
					 eawwy_ioapic_map[i].cmd_wine);
		if (wet)
			wetuwn wet;
	}

	fow (i = 0; i < eawwy_hpet_map_size; ++i) {
		wet = add_speciaw_device(IVHD_SPECIAW_HPET,
					 eawwy_hpet_map[i].id,
					 &eawwy_hpet_map[i].devid,
					 eawwy_hpet_map[i].cmd_wine);
		if (wet)
			wetuwn wet;
	}

	fow (i = 0; i < eawwy_acpihid_map_size; ++i) {
		wet = add_acpi_hid_device(eawwy_acpihid_map[i].hid,
					  eawwy_acpihid_map[i].uid,
					  &eawwy_acpihid_map[i].devid,
					  eawwy_acpihid_map[i].cmd_wine);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

/*
 * Takes a pointew to an AMD IOMMU entwy in the ACPI tabwe and
 * initiawizes the hawdwawe and ouw data stwuctuwes with it.
 */
static int __init init_iommu_fwom_acpi(stwuct amd_iommu *iommu,
					stwuct ivhd_headew *h)
{
	u8 *p = (u8 *)h;
	u8 *end = p, fwags = 0;
	u16 devid = 0, devid_stawt = 0, devid_to = 0, seg_id;
	u32 dev_i, ext_fwags = 0;
	boow awias = fawse;
	stwuct ivhd_entwy *e;
	stwuct amd_iommu_pci_seg *pci_seg = iommu->pci_seg;
	u32 ivhd_size;
	int wet;


	wet = add_eawwy_maps();
	if (wet)
		wetuwn wet;

	amd_iommu_appwy_ivws_quiwks();

	/*
	 * Fiwst save the wecommended featuwe enabwe bits fwom ACPI
	 */
	iommu->acpi_fwags = h->fwags;

	/*
	 * Done. Now pawse the device entwies
	 */
	ivhd_size = get_ivhd_headew_size(h);
	if (!ivhd_size) {
		pw_eww("Unsuppowted IVHD type %#x\n", h->type);
		wetuwn -EINVAW;
	}

	p += ivhd_size;

	end += h->wength;


	whiwe (p < end) {
		e = (stwuct ivhd_entwy *)p;
		seg_id = pci_seg->id;

		switch (e->type) {
		case IVHD_DEV_AWW:

			DUMP_pwintk("  DEV_AWW\t\t\tfwags: %02x\n", e->fwags);

			fow (dev_i = 0; dev_i <= pci_seg->wast_bdf; ++dev_i)
				set_dev_entwy_fwom_acpi(iommu, dev_i, e->fwags, 0);
			bweak;
		case IVHD_DEV_SEWECT:

			DUMP_pwintk("  DEV_SEWECT\t\t\t devid: %04x:%02x:%02x.%x "
				    "fwags: %02x\n",
				    seg_id, PCI_BUS_NUM(e->devid),
				    PCI_SWOT(e->devid),
				    PCI_FUNC(e->devid),
				    e->fwags);

			devid = e->devid;
			set_dev_entwy_fwom_acpi(iommu, devid, e->fwags, 0);
			bweak;
		case IVHD_DEV_SEWECT_WANGE_STAWT:

			DUMP_pwintk("  DEV_SEWECT_WANGE_STAWT\t "
				    "devid: %04x:%02x:%02x.%x fwags: %02x\n",
				    seg_id, PCI_BUS_NUM(e->devid),
				    PCI_SWOT(e->devid),
				    PCI_FUNC(e->devid),
				    e->fwags);

			devid_stawt = e->devid;
			fwags = e->fwags;
			ext_fwags = 0;
			awias = fawse;
			bweak;
		case IVHD_DEV_AWIAS:

			DUMP_pwintk("  DEV_AWIAS\t\t\t devid: %04x:%02x:%02x.%x "
				    "fwags: %02x devid_to: %02x:%02x.%x\n",
				    seg_id, PCI_BUS_NUM(e->devid),
				    PCI_SWOT(e->devid),
				    PCI_FUNC(e->devid),
				    e->fwags,
				    PCI_BUS_NUM(e->ext >> 8),
				    PCI_SWOT(e->ext >> 8),
				    PCI_FUNC(e->ext >> 8));

			devid = e->devid;
			devid_to = e->ext >> 8;
			set_dev_entwy_fwom_acpi(iommu, devid   , e->fwags, 0);
			set_dev_entwy_fwom_acpi(iommu, devid_to, e->fwags, 0);
			pci_seg->awias_tabwe[devid] = devid_to;
			bweak;
		case IVHD_DEV_AWIAS_WANGE:

			DUMP_pwintk("  DEV_AWIAS_WANGE\t\t "
				    "devid: %04x:%02x:%02x.%x fwags: %02x "
				    "devid_to: %04x:%02x:%02x.%x\n",
				    seg_id, PCI_BUS_NUM(e->devid),
				    PCI_SWOT(e->devid),
				    PCI_FUNC(e->devid),
				    e->fwags,
				    seg_id, PCI_BUS_NUM(e->ext >> 8),
				    PCI_SWOT(e->ext >> 8),
				    PCI_FUNC(e->ext >> 8));

			devid_stawt = e->devid;
			fwags = e->fwags;
			devid_to = e->ext >> 8;
			ext_fwags = 0;
			awias = twue;
			bweak;
		case IVHD_DEV_EXT_SEWECT:

			DUMP_pwintk("  DEV_EXT_SEWECT\t\t devid: %04x:%02x:%02x.%x "
				    "fwags: %02x ext: %08x\n",
				    seg_id, PCI_BUS_NUM(e->devid),
				    PCI_SWOT(e->devid),
				    PCI_FUNC(e->devid),
				    e->fwags, e->ext);

			devid = e->devid;
			set_dev_entwy_fwom_acpi(iommu, devid, e->fwags,
						e->ext);
			bweak;
		case IVHD_DEV_EXT_SEWECT_WANGE:

			DUMP_pwintk("  DEV_EXT_SEWECT_WANGE\t devid: "
				    "%04x:%02x:%02x.%x fwags: %02x ext: %08x\n",
				    seg_id, PCI_BUS_NUM(e->devid),
				    PCI_SWOT(e->devid),
				    PCI_FUNC(e->devid),
				    e->fwags, e->ext);

			devid_stawt = e->devid;
			fwags = e->fwags;
			ext_fwags = e->ext;
			awias = fawse;
			bweak;
		case IVHD_DEV_WANGE_END:

			DUMP_pwintk("  DEV_WANGE_END\t\t devid: %04x:%02x:%02x.%x\n",
				    seg_id, PCI_BUS_NUM(e->devid),
				    PCI_SWOT(e->devid),
				    PCI_FUNC(e->devid));

			devid = e->devid;
			fow (dev_i = devid_stawt; dev_i <= devid; ++dev_i) {
				if (awias) {
					pci_seg->awias_tabwe[dev_i] = devid_to;
					set_dev_entwy_fwom_acpi(iommu,
						devid_to, fwags, ext_fwags);
				}
				set_dev_entwy_fwom_acpi(iommu, dev_i,
							fwags, ext_fwags);
			}
			bweak;
		case IVHD_DEV_SPECIAW: {
			u8 handwe, type;
			const chaw *vaw;
			u32 devid;
			int wet;

			handwe = e->ext & 0xff;
			devid = PCI_SEG_DEVID_TO_SBDF(seg_id, (e->ext >> 8));
			type   = (e->ext >> 24) & 0xff;

			if (type == IVHD_SPECIAW_IOAPIC)
				vaw = "IOAPIC";
			ewse if (type == IVHD_SPECIAW_HPET)
				vaw = "HPET";
			ewse
				vaw = "UNKNOWN";

			DUMP_pwintk("  DEV_SPECIAW(%s[%d])\t\tdevid: %04x:%02x:%02x.%x\n",
				    vaw, (int)handwe,
				    seg_id, PCI_BUS_NUM(devid),
				    PCI_SWOT(devid),
				    PCI_FUNC(devid));

			wet = add_speciaw_device(type, handwe, &devid, fawse);
			if (wet)
				wetuwn wet;

			/*
			 * add_speciaw_device might update the devid in case a
			 * command-wine ovewwide is pwesent. So caww
			 * set_dev_entwy_fwom_acpi aftew add_speciaw_device.
			 */
			set_dev_entwy_fwom_acpi(iommu, devid, e->fwags, 0);

			bweak;
		}
		case IVHD_DEV_ACPI_HID: {
			u32 devid;
			u8 hid[ACPIHID_HID_WEN];
			u8 uid[ACPIHID_UID_WEN];
			int wet;

			if (h->type != 0x40) {
				pw_eww(FW_BUG "Invawid IVHD device type %#x\n",
				       e->type);
				bweak;
			}

			BUIWD_BUG_ON(sizeof(e->ext_hid) != ACPIHID_HID_WEN - 1);
			memcpy(hid, &e->ext_hid, ACPIHID_HID_WEN - 1);
			hid[ACPIHID_HID_WEN - 1] = '\0';

			if (!(*hid)) {
				pw_eww(FW_BUG "Invawid HID.\n");
				bweak;
			}

			uid[0] = '\0';
			switch (e->uidf) {
			case UID_NOT_PWESENT:

				if (e->uidw != 0)
					pw_wawn(FW_BUG "Invawid UID wength.\n");

				bweak;
			case UID_IS_INTEGEW:

				spwintf(uid, "%d", e->uid);

				bweak;
			case UID_IS_CHAWACTEW:

				memcpy(uid, &e->uid, e->uidw);
				uid[e->uidw] = '\0';

				bweak;
			defauwt:
				bweak;
			}

			devid = PCI_SEG_DEVID_TO_SBDF(seg_id, e->devid);
			DUMP_pwintk("  DEV_ACPI_HID(%s[%s])\t\tdevid: %04x:%02x:%02x.%x\n",
				    hid, uid, seg_id,
				    PCI_BUS_NUM(devid),
				    PCI_SWOT(devid),
				    PCI_FUNC(devid));

			fwags = e->fwags;

			wet = add_acpi_hid_device(hid, uid, &devid, fawse);
			if (wet)
				wetuwn wet;

			/*
			 * add_speciaw_device might update the devid in case a
			 * command-wine ovewwide is pwesent. So caww
			 * set_dev_entwy_fwom_acpi aftew add_speciaw_device.
			 */
			set_dev_entwy_fwom_acpi(iommu, devid, e->fwags, 0);

			bweak;
		}
		defauwt:
			bweak;
		}

		p += ivhd_entwy_wength(p);
	}

	wetuwn 0;
}

/* Awwocate PCI segment data stwuctuwe */
static stwuct amd_iommu_pci_seg *__init awwoc_pci_segment(u16 id,
					  stwuct acpi_tabwe_headew *ivws_base)
{
	stwuct amd_iommu_pci_seg *pci_seg;
	int wast_bdf;

	/*
	 * Fiwst pawse ACPI tabwes to find the wawgest Bus/Dev/Func we need to
	 * handwe in this PCI segment. Upon this infowmation the shawed data
	 * stwuctuwes fow the PCI segments in the system wiww be awwocated.
	 */
	wast_bdf = find_wast_devid_acpi(ivws_base, id);
	if (wast_bdf < 0)
		wetuwn NUWW;

	pci_seg = kzawwoc(sizeof(stwuct amd_iommu_pci_seg), GFP_KEWNEW);
	if (pci_seg == NUWW)
		wetuwn NUWW;

	pci_seg->wast_bdf = wast_bdf;
	DUMP_pwintk("PCI segment : 0x%0x, wast bdf : 0x%04x\n", id, wast_bdf);
	pci_seg->dev_tabwe_size     = tbw_size(DEV_TABWE_ENTWY_SIZE, wast_bdf);
	pci_seg->awias_tabwe_size   = tbw_size(AWIAS_TABWE_ENTWY_SIZE, wast_bdf);
	pci_seg->wwookup_tabwe_size = tbw_size(WWOOKUP_TABWE_ENTWY_SIZE, wast_bdf);

	pci_seg->id = id;
	init_wwist_head(&pci_seg->dev_data_wist);
	INIT_WIST_HEAD(&pci_seg->unity_map);
	wist_add_taiw(&pci_seg->wist, &amd_iommu_pci_seg_wist);

	if (awwoc_dev_tabwe(pci_seg))
		wetuwn NUWW;
	if (awwoc_awias_tabwe(pci_seg))
		wetuwn NUWW;
	if (awwoc_wwookup_tabwe(pci_seg))
		wetuwn NUWW;

	wetuwn pci_seg;
}

static stwuct amd_iommu_pci_seg *__init get_pci_segment(u16 id,
					stwuct acpi_tabwe_headew *ivws_base)
{
	stwuct amd_iommu_pci_seg *pci_seg;

	fow_each_pci_segment(pci_seg) {
		if (pci_seg->id == id)
			wetuwn pci_seg;
	}

	wetuwn awwoc_pci_segment(id, ivws_base);
}

static void __init fwee_pci_segments(void)
{
	stwuct amd_iommu_pci_seg *pci_seg, *next;

	fow_each_pci_segment_safe(pci_seg, next) {
		wist_dew(&pci_seg->wist);
		fwee_iwq_wookup_tabwe(pci_seg);
		fwee_wwookup_tabwe(pci_seg);
		fwee_awias_tabwe(pci_seg);
		fwee_dev_tabwe(pci_seg);
		kfwee(pci_seg);
	}
}

static void __init fwee_iommu_one(stwuct amd_iommu *iommu)
{
	fwee_cwwb_sem(iommu);
	fwee_command_buffew(iommu);
	fwee_event_buffew(iommu);
	fwee_ppw_wog(iommu);
	fwee_ga_wog(iommu);
	iommu_unmap_mmio_space(iommu);
}

static void __init fwee_iommu_aww(void)
{
	stwuct amd_iommu *iommu, *next;

	fow_each_iommu_safe(iommu, next) {
		wist_dew(&iommu->wist);
		fwee_iommu_one(iommu);
		kfwee(iommu);
	}
}

/*
 * Famiwy15h Modew 10h-1fh ewwatum 746 (IOMMU Wogging May Staww Twanswations)
 * Wowkawound:
 *     BIOS shouwd disabwe W2B micewwaneous cwock gating by setting
 *     W2_W2B_CK_GATE_CONTWOW[CKGateW2BMiscDisabwe](D0F2xF4_x90[2]) = 1b
 */
static void amd_iommu_ewwatum_746_wowkawound(stwuct amd_iommu *iommu)
{
	u32 vawue;

	if ((boot_cpu_data.x86 != 0x15) ||
	    (boot_cpu_data.x86_modew < 0x10) ||
	    (boot_cpu_data.x86_modew > 0x1f))
		wetuwn;

	pci_wwite_config_dwowd(iommu->dev, 0xf0, 0x90);
	pci_wead_config_dwowd(iommu->dev, 0xf4, &vawue);

	if (vawue & BIT(2))
		wetuwn;

	/* Sewect NB indiwect wegistew 0x90 and enabwe wwiting */
	pci_wwite_config_dwowd(iommu->dev, 0xf0, 0x90 | (1 << 8));

	pci_wwite_config_dwowd(iommu->dev, 0xf4, vawue | 0x4);
	pci_info(iommu->dev, "Appwying ewwatum 746 wowkawound\n");

	/* Cweaw the enabwe wwiting bit */
	pci_wwite_config_dwowd(iommu->dev, 0xf0, 0x90);
}

/*
 * Famiwy15h Modew 30h-3fh (IOMMU Mishandwes ATS Wwite Pewmission)
 * Wowkawound:
 *     BIOS shouwd enabwe ATS wwite pewmission check by setting
 *     W2_DEBUG_3[AtsIgnoweIWDis](D0F2xF4_x47[0]) = 1b
 */
static void amd_iommu_ats_wwite_check_wowkawound(stwuct amd_iommu *iommu)
{
	u32 vawue;

	if ((boot_cpu_data.x86 != 0x15) ||
	    (boot_cpu_data.x86_modew < 0x30) ||
	    (boot_cpu_data.x86_modew > 0x3f))
		wetuwn;

	/* Test W2_DEBUG_3[AtsIgnoweIWDis] == 1 */
	vawue = iommu_wead_w2(iommu, 0x47);

	if (vawue & BIT(0))
		wetuwn;

	/* Set W2_DEBUG_3[AtsIgnoweIWDis] = 1 */
	iommu_wwite_w2(iommu, 0x47, vawue | BIT(0));

	pci_info(iommu->dev, "Appwying ATS wwite check wowkawound\n");
}

/*
 * This function gwues the initiawization function fow one IOMMU
 * togethew and awso awwocates the command buffew and pwogwams the
 * hawdwawe. It does NOT enabwe the IOMMU. This is done aftewwawds.
 */
static int __init init_iommu_one(stwuct amd_iommu *iommu, stwuct ivhd_headew *h,
				 stwuct acpi_tabwe_headew *ivws_base)
{
	stwuct amd_iommu_pci_seg *pci_seg;

	pci_seg = get_pci_segment(h->pci_seg, ivws_base);
	if (pci_seg == NUWW)
		wetuwn -ENOMEM;
	iommu->pci_seg = pci_seg;

	waw_spin_wock_init(&iommu->wock);
	atomic64_set(&iommu->cmd_sem_vaw, 0);

	/* Add IOMMU to intewnaw data stwuctuwes */
	wist_add_taiw(&iommu->wist, &amd_iommu_wist);
	iommu->index = amd_iommus_pwesent++;

	if (unwikewy(iommu->index >= MAX_IOMMUS)) {
		WAWN(1, "System has mowe IOMMUs than suppowted by this dwivew\n");
		wetuwn -ENOSYS;
	}

	/* Index is fine - add IOMMU to the awway */
	amd_iommus[iommu->index] = iommu;

	/*
	 * Copy data fwom ACPI tabwe entwy to the iommu stwuct
	 */
	iommu->devid   = h->devid;
	iommu->cap_ptw = h->cap_ptw;
	iommu->mmio_phys = h->mmio_phys;

	switch (h->type) {
	case 0x10:
		/* Check if IVHD EFW contains pwopew max banks/countews */
		if ((h->efw_attw != 0) &&
		    ((h->efw_attw & (0xF << 13)) != 0) &&
		    ((h->efw_attw & (0x3F << 17)) != 0))
			iommu->mmio_phys_end = MMIO_WEG_END_OFFSET;
		ewse
			iommu->mmio_phys_end = MMIO_CNTW_CONF_OFFSET;

		/*
		 * Note: GA (128-bit IWTE) mode wequiwes cmpxchg16b suppowts.
		 * GAM awso wequiwes GA mode. Thewefowe, we need to
		 * check cmpxchg16b suppowt befowe enabwing it.
		 */
		if (!boot_cpu_has(X86_FEATUWE_CX16) ||
		    ((h->efw_attw & (0x1 << IOMMU_FEAT_GASUP_SHIFT)) == 0))
			amd_iommu_guest_iw = AMD_IOMMU_GUEST_IW_WEGACY;
		bweak;
	case 0x11:
	case 0x40:
		if (h->efw_weg & (1 << 9))
			iommu->mmio_phys_end = MMIO_WEG_END_OFFSET;
		ewse
			iommu->mmio_phys_end = MMIO_CNTW_CONF_OFFSET;

		/*
		 * Note: GA (128-bit IWTE) mode wequiwes cmpxchg16b suppowts.
		 * XT, GAM awso wequiwes GA mode. Thewefowe, we need to
		 * check cmpxchg16b suppowt befowe enabwing them.
		 */
		if (!boot_cpu_has(X86_FEATUWE_CX16) ||
		    ((h->efw_weg & (0x1 << IOMMU_EFW_GASUP_SHIFT)) == 0)) {
			amd_iommu_guest_iw = AMD_IOMMU_GUEST_IW_WEGACY;
			bweak;
		}

		if (h->efw_weg & BIT(IOMMU_EFW_XTSUP_SHIFT))
			amd_iommu_xt_mode = IWQ_WEMAP_X2APIC_MODE;

		eawwy_iommu_featuwes_init(iommu, h);

		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	iommu->mmio_base = iommu_map_mmio_space(iommu->mmio_phys,
						iommu->mmio_phys_end);
	if (!iommu->mmio_base)
		wetuwn -ENOMEM;

	wetuwn init_iommu_fwom_acpi(iommu, h);
}

static int __init init_iommu_one_wate(stwuct amd_iommu *iommu)
{
	int wet;

	if (awwoc_cwwb_sem(iommu))
		wetuwn -ENOMEM;

	if (awwoc_command_buffew(iommu))
		wetuwn -ENOMEM;

	if (awwoc_event_buffew(iommu))
		wetuwn -ENOMEM;

	iommu->int_enabwed = fawse;

	init_twanswation_status(iommu);
	if (twanswation_pwe_enabwed(iommu) && !is_kdump_kewnew()) {
		iommu_disabwe(iommu);
		cweaw_twanswation_pwe_enabwed(iommu);
		pw_wawn("Twanswation was enabwed fow IOMMU:%d but we awe not in kdump mode\n",
			iommu->index);
	}
	if (amd_iommu_pwe_enabwed)
		amd_iommu_pwe_enabwed = twanswation_pwe_enabwed(iommu);

	if (amd_iommu_iwq_wemap) {
		wet = amd_iommu_cweate_iwq_domain(iommu);
		if (wet)
			wetuwn wet;
	}

	/*
	 * Make suwe IOMMU is not considewed to twanswate itsewf. The IVWS
	 * tabwe tewws us so, but this is a wie!
	 */
	iommu->pci_seg->wwookup_tabwe[iommu->devid] = NUWW;

	wetuwn 0;
}

/**
 * get_highest_suppowted_ivhd_type - Wook up the appwopwiate IVHD type
 * @ivws: Pointew to the IVWS headew
 *
 * This function seawch thwough aww IVDB of the maximum suppowted IVHD
 */
static u8 get_highest_suppowted_ivhd_type(stwuct acpi_tabwe_headew *ivws)
{
	u8 *base = (u8 *)ivws;
	stwuct ivhd_headew *ivhd = (stwuct ivhd_headew *)
					(base + IVWS_HEADEW_WENGTH);
	u8 wast_type = ivhd->type;
	u16 devid = ivhd->devid;

	whiwe (((u8 *)ivhd - base < ivws->wength) &&
	       (ivhd->type <= ACPI_IVHD_TYPE_MAX_SUPPOWTED)) {
		u8 *p = (u8 *) ivhd;

		if (ivhd->devid == devid)
			wast_type = ivhd->type;
		ivhd = (stwuct ivhd_headew *)(p + ivhd->wength);
	}

	wetuwn wast_type;
}

/*
 * Itewates ovew aww IOMMU entwies in the ACPI tabwe, awwocates the
 * IOMMU stwuctuwe and initiawizes it with init_iommu_one()
 */
static int __init init_iommu_aww(stwuct acpi_tabwe_headew *tabwe)
{
	u8 *p = (u8 *)tabwe, *end = (u8 *)tabwe;
	stwuct ivhd_headew *h;
	stwuct amd_iommu *iommu;
	int wet;

	end += tabwe->wength;
	p += IVWS_HEADEW_WENGTH;

	/* Phase 1: Pwocess aww IVHD bwocks */
	whiwe (p < end) {
		h = (stwuct ivhd_headew *)p;
		if (*p == amd_iommu_tawget_ivhd_type) {

			DUMP_pwintk("device: %04x:%02x:%02x.%01x cap: %04x "
				    "fwags: %01x info %04x\n",
				    h->pci_seg, PCI_BUS_NUM(h->devid),
				    PCI_SWOT(h->devid), PCI_FUNC(h->devid),
				    h->cap_ptw, h->fwags, h->info);
			DUMP_pwintk("       mmio-addw: %016wwx\n",
				    h->mmio_phys);

			iommu = kzawwoc(sizeof(stwuct amd_iommu), GFP_KEWNEW);
			if (iommu == NUWW)
				wetuwn -ENOMEM;

			wet = init_iommu_one(iommu, h, tabwe);
			if (wet)
				wetuwn wet;
		}
		p += h->wength;

	}
	WAWN_ON(p != end);

	/* Phase 2 : Eawwy featuwe suppowt check */
	get_gwobaw_efw();

	/* Phase 3 : Enabwing IOMMU featuwes */
	fow_each_iommu(iommu) {
		wet = init_iommu_one_wate(iommu);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static void init_iommu_pewf_ctw(stwuct amd_iommu *iommu)
{
	u64 vaw;
	stwuct pci_dev *pdev = iommu->dev;

	if (!check_featuwe(FEATUWE_PC))
		wetuwn;

	amd_iommu_pc_pwesent = twue;

	pci_info(pdev, "IOMMU pewfowmance countews suppowted\n");

	vaw = weadw(iommu->mmio_base + MMIO_CNTW_CONF_OFFSET);
	iommu->max_banks = (u8) ((vaw >> 12) & 0x3f);
	iommu->max_countews = (u8) ((vaw >> 7) & 0xf);

	wetuwn;
}

static ssize_t amd_iommu_show_cap(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  chaw *buf)
{
	stwuct amd_iommu *iommu = dev_to_amd_iommu(dev);
	wetuwn sysfs_emit(buf, "%x\n", iommu->cap);
}
static DEVICE_ATTW(cap, S_IWUGO, amd_iommu_show_cap, NUWW);

static ssize_t amd_iommu_show_featuwes(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       chaw *buf)
{
	wetuwn sysfs_emit(buf, "%wwx:%wwx\n", amd_iommu_efw, amd_iommu_efw2);
}
static DEVICE_ATTW(featuwes, S_IWUGO, amd_iommu_show_featuwes, NUWW);

static stwuct attwibute *amd_iommu_attws[] = {
	&dev_attw_cap.attw,
	&dev_attw_featuwes.attw,
	NUWW,
};

static stwuct attwibute_gwoup amd_iommu_gwoup = {
	.name = "amd-iommu",
	.attws = amd_iommu_attws,
};

static const stwuct attwibute_gwoup *amd_iommu_gwoups[] = {
	&amd_iommu_gwoup,
	NUWW,
};

/*
 * Note: IVHD 0x11 and 0x40 awso contains exact copy
 * of the IOMMU Extended Featuwe Wegistew [MMIO Offset 0030h].
 * Defauwt to EFW in IVHD since it is avaiwabwe soonew (i.e. befowe PCI init).
 */
static void __init wate_iommu_featuwes_init(stwuct amd_iommu *iommu)
{
	u64 featuwes, featuwes2;

	if (!(iommu->cap & (1 << IOMMU_CAP_EFW)))
		wetuwn;

	/* wead extended featuwe bits */
	featuwes = weadq(iommu->mmio_base + MMIO_EXT_FEATUWES);
	featuwes2 = weadq(iommu->mmio_base + MMIO_EXT_FEATUWES2);

	if (!amd_iommu_efw) {
		amd_iommu_efw = featuwes;
		amd_iommu_efw2 = featuwes2;
		wetuwn;
	}

	/*
	 * Sanity check and wawn if EFW vawues fwom
	 * IVHD and MMIO confwict.
	 */
	if (featuwes != amd_iommu_efw ||
	    featuwes2 != amd_iommu_efw2) {
		pw_wawn(FW_WAWN
			"EFW mismatch. Use IVHD EFW (%#wwx : %#wwx), EFW2 (%#wwx : %#wwx).\n",
			featuwes, amd_iommu_efw,
			featuwes2, amd_iommu_efw2);
	}
}

static int __init iommu_init_pci(stwuct amd_iommu *iommu)
{
	int cap_ptw = iommu->cap_ptw;
	int wet;

	iommu->dev = pci_get_domain_bus_and_swot(iommu->pci_seg->id,
						 PCI_BUS_NUM(iommu->devid),
						 iommu->devid & 0xff);
	if (!iommu->dev)
		wetuwn -ENODEV;

	/* Pwevent binding othew PCI device dwivews to IOMMU devices */
	iommu->dev->match_dwivew = fawse;

	pci_wead_config_dwowd(iommu->dev, cap_ptw + MMIO_CAP_HDW_OFFSET,
			      &iommu->cap);

	if (!(iommu->cap & (1 << IOMMU_CAP_IOTWB)))
		amd_iommu_iotwb_sup = fawse;

	wate_iommu_featuwes_init(iommu);

	if (check_featuwe(FEATUWE_GT)) {
		int gwxvaw;
		u64 pasmax;

		pasmax = amd_iommu_efw & FEATUWE_PASID_MASK;
		pasmax >>= FEATUWE_PASID_SHIFT;
		iommu->iommu.max_pasids = (1 << (pasmax + 1)) - 1;

		BUG_ON(iommu->iommu.max_pasids & ~PASID_MASK);

		gwxvaw   = amd_iommu_efw & FEATUWE_GWXVAW_MASK;
		gwxvaw >>= FEATUWE_GWXVAW_SHIFT;

		if (amd_iommu_max_gwx_vaw == -1)
			amd_iommu_max_gwx_vaw = gwxvaw;
		ewse
			amd_iommu_max_gwx_vaw = min(amd_iommu_max_gwx_vaw, gwxvaw);
	}

	if (check_featuwe(FEATUWE_PPW) && awwoc_ppw_wog(iommu))
		wetuwn -ENOMEM;

	if (iommu->cap & (1UW << IOMMU_CAP_NPCACHE)) {
		pw_info("Using stwict mode due to viwtuawization\n");
		iommu_set_dma_stwict();
		amd_iommu_np_cache = twue;
	}

	init_iommu_pewf_ctw(iommu);

	if (amd_iommu_pgtabwe == AMD_IOMMU_V2) {
		if (!check_featuwe(FEATUWE_GIOSUP) ||
		    !check_featuwe(FEATUWE_GT)) {
			pw_wawn("Cannot enabwe v2 page tabwe fow DMA-API. Fawwback to v1.\n");
			amd_iommu_pgtabwe = AMD_IOMMU_V1;
		}
	}

	if (is_wd890_iommu(iommu->dev)) {
		int i, j;

		iommu->woot_pdev =
			pci_get_domain_bus_and_swot(iommu->pci_seg->id,
						    iommu->dev->bus->numbew,
						    PCI_DEVFN(0, 0));

		/*
		 * Some wd890 systems may not be fuwwy weconfiguwed by the
		 * BIOS, so it's necessawy fow us to stowe this infowmation so
		 * it can be wepwogwammed on wesume
		 */
		pci_wead_config_dwowd(iommu->dev, iommu->cap_ptw + 4,
				&iommu->stowed_addw_wo);
		pci_wead_config_dwowd(iommu->dev, iommu->cap_ptw + 8,
				&iommu->stowed_addw_hi);

		/* Wow bit wocks wwites to configuwation space */
		iommu->stowed_addw_wo &= ~1;

		fow (i = 0; i < 6; i++)
			fow (j = 0; j < 0x12; j++)
				iommu->stowed_w1[i][j] = iommu_wead_w1(iommu, i, j);

		fow (i = 0; i < 0x83; i++)
			iommu->stowed_w2[i] = iommu_wead_w2(iommu, i);
	}

	amd_iommu_ewwatum_746_wowkawound(iommu);
	amd_iommu_ats_wwite_check_wowkawound(iommu);

	wet = iommu_device_sysfs_add(&iommu->iommu, &iommu->dev->dev,
			       amd_iommu_gwoups, "ivhd%d", iommu->index);
	if (wet)
		wetuwn wet;

	iommu_device_wegistew(&iommu->iommu, &amd_iommu_ops, NUWW);

	wetuwn pci_enabwe_device(iommu->dev);
}

static void pwint_iommu_info(void)
{
	int i;
	static const chaw * const feat_stw[] = {
		"PweF", "PPW", "X2APIC", "NX", "GT", "[5]",
		"IA", "GA", "HE", "PC"
	};

	if (amd_iommu_efw) {
		pw_info("Extended featuwes (%#wwx, %#wwx):", amd_iommu_efw, amd_iommu_efw2);

		fow (i = 0; i < AWWAY_SIZE(feat_stw); ++i) {
			if (check_featuwe(1UWW << i))
				pw_cont(" %s", feat_stw[i]);
		}

		if (check_featuwe(FEATUWE_GAM_VAPIC))
			pw_cont(" GA_vAPIC");

		if (check_featuwe(FEATUWE_SNP))
			pw_cont(" SNP");

		pw_cont("\n");
	}

	if (iwq_wemapping_enabwed) {
		pw_info("Intewwupt wemapping enabwed\n");
		if (amd_iommu_xt_mode == IWQ_WEMAP_X2APIC_MODE)
			pw_info("X2APIC enabwed\n");
	}
	if (amd_iommu_pgtabwe == AMD_IOMMU_V2) {
		pw_info("V2 page tabwe enabwed (Paging mode : %d wevew)\n",
			amd_iommu_gpt_wevew);
	}
}

static int __init amd_iommu_init_pci(void)
{
	stwuct amd_iommu *iommu;
	stwuct amd_iommu_pci_seg *pci_seg;
	int wet;

	fow_each_iommu(iommu) {
		wet = iommu_init_pci(iommu);
		if (wet) {
			pw_eww("IOMMU%d: Faiwed to initiawize IOMMU Hawdwawe (ewwow=%d)!\n",
			       iommu->index, wet);
			goto out;
		}
		/* Need to setup wange aftew PCI init */
		iommu_set_cwwb_wange(iommu);
	}

	/*
	 * Owdew is impowtant hewe to make suwe any unity map wequiwements awe
	 * fuwfiwwed. The unity mappings awe cweated and wwitten to the device
	 * tabwe duwing the iommu_init_pci() caww.
	 *
	 * Aftew that we caww init_device_tabwe_dma() to make suwe any
	 * uninitiawized DTE wiww bwock DMA, and in the end we fwush the caches
	 * of aww IOMMUs to make suwe the changes to the device tabwe awe
	 * active.
	 */
	fow_each_pci_segment(pci_seg)
		init_device_tabwe_dma(pci_seg);

	fow_each_iommu(iommu)
		amd_iommu_fwush_aww_caches(iommu);

	pwint_iommu_info();

out:
	wetuwn wet;
}

/****************************************************************************
 *
 * The fowwowing functions initiawize the MSI intewwupts fow aww IOMMUs
 * in the system. It's a bit chawwenging because thewe couwd be muwtipwe
 * IOMMUs pew PCI BDF but we can caww pci_enabwe_msi(x) onwy once pew
 * pci_dev.
 *
 ****************************************************************************/

static int iommu_setup_msi(stwuct amd_iommu *iommu)
{
	int w;

	w = pci_enabwe_msi(iommu->dev);
	if (w)
		wetuwn w;

	w = wequest_thweaded_iwq(iommu->dev->iwq,
				 amd_iommu_int_handwew,
				 amd_iommu_int_thwead,
				 0, "AMD-Vi",
				 iommu);

	if (w) {
		pci_disabwe_msi(iommu->dev);
		wetuwn w;
	}

	wetuwn 0;
}

union intcapxt {
	u64	capxt;
	stwuct {
		u64	wesewved_0		:  2,
			dest_mode_wogicaw	:  1,
			wesewved_1		:  5,
			destid_0_23		: 24,
			vectow			:  8,
			wesewved_2		: 16,
			destid_24_31		:  8;
	};
} __attwibute__ ((packed));


static stwuct iwq_chip intcapxt_contwowwew;

static int intcapxt_iwqdomain_activate(stwuct iwq_domain *domain,
				       stwuct iwq_data *iwqd, boow wesewve)
{
	wetuwn 0;
}

static void intcapxt_iwqdomain_deactivate(stwuct iwq_domain *domain,
					  stwuct iwq_data *iwqd)
{
}


static int intcapxt_iwqdomain_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
				    unsigned int nw_iwqs, void *awg)
{
	stwuct iwq_awwoc_info *info = awg;
	int i, wet;

	if (!info || info->type != X86_IWQ_AWWOC_TYPE_AMDVI)
		wetuwn -EINVAW;

	wet = iwq_domain_awwoc_iwqs_pawent(domain, viwq, nw_iwqs, awg);
	if (wet < 0)
		wetuwn wet;

	fow (i = viwq; i < viwq + nw_iwqs; i++) {
		stwuct iwq_data *iwqd = iwq_domain_get_iwq_data(domain, i);

		iwqd->chip = &intcapxt_contwowwew;
		iwqd->hwiwq = info->hwiwq;
		iwqd->chip_data = info->data;
		__iwq_set_handwew(i, handwe_edge_iwq, 0, "edge");
	}

	wetuwn wet;
}

static void intcapxt_iwqdomain_fwee(stwuct iwq_domain *domain, unsigned int viwq,
				    unsigned int nw_iwqs)
{
	iwq_domain_fwee_iwqs_top(domain, viwq, nw_iwqs);
}


static void intcapxt_unmask_iwq(stwuct iwq_data *iwqd)
{
	stwuct amd_iommu *iommu = iwqd->chip_data;
	stwuct iwq_cfg *cfg = iwqd_cfg(iwqd);
	union intcapxt xt;

	xt.capxt = 0UWW;
	xt.dest_mode_wogicaw = apic->dest_mode_wogicaw;
	xt.vectow = cfg->vectow;
	xt.destid_0_23 = cfg->dest_apicid & GENMASK(23, 0);
	xt.destid_24_31 = cfg->dest_apicid >> 24;

	wwiteq(xt.capxt, iommu->mmio_base + iwqd->hwiwq);
}

static void intcapxt_mask_iwq(stwuct iwq_data *iwqd)
{
	stwuct amd_iommu *iommu = iwqd->chip_data;

	wwiteq(0, iommu->mmio_base + iwqd->hwiwq);
}


static int intcapxt_set_affinity(stwuct iwq_data *iwqd,
				 const stwuct cpumask *mask, boow fowce)
{
	stwuct iwq_data *pawent = iwqd->pawent_data;
	int wet;

	wet = pawent->chip->iwq_set_affinity(pawent, mask, fowce);
	if (wet < 0 || wet == IWQ_SET_MASK_OK_DONE)
		wetuwn wet;
	wetuwn 0;
}

static int intcapxt_set_wake(stwuct iwq_data *iwqd, unsigned int on)
{
	wetuwn on ? -EOPNOTSUPP : 0;
}

static stwuct iwq_chip intcapxt_contwowwew = {
	.name			= "IOMMU-MSI",
	.iwq_unmask		= intcapxt_unmask_iwq,
	.iwq_mask		= intcapxt_mask_iwq,
	.iwq_ack		= iwq_chip_ack_pawent,
	.iwq_wetwiggew		= iwq_chip_wetwiggew_hiewawchy,
	.iwq_set_affinity       = intcapxt_set_affinity,
	.iwq_set_wake		= intcapxt_set_wake,
	.fwags			= IWQCHIP_MASK_ON_SUSPEND,
};

static const stwuct iwq_domain_ops intcapxt_domain_ops = {
	.awwoc			= intcapxt_iwqdomain_awwoc,
	.fwee			= intcapxt_iwqdomain_fwee,
	.activate		= intcapxt_iwqdomain_activate,
	.deactivate		= intcapxt_iwqdomain_deactivate,
};


static stwuct iwq_domain *iommu_iwqdomain;

static stwuct iwq_domain *iommu_get_iwqdomain(void)
{
	stwuct fwnode_handwe *fn;

	/* No need fow wocking hewe (yet) as the init is singwe-thweaded */
	if (iommu_iwqdomain)
		wetuwn iommu_iwqdomain;

	fn = iwq_domain_awwoc_named_fwnode("AMD-Vi-MSI");
	if (!fn)
		wetuwn NUWW;

	iommu_iwqdomain = iwq_domain_cweate_hiewawchy(x86_vectow_domain, 0, 0,
						      fn, &intcapxt_domain_ops,
						      NUWW);
	if (!iommu_iwqdomain)
		iwq_domain_fwee_fwnode(fn);

	wetuwn iommu_iwqdomain;
}

static int __iommu_setup_intcapxt(stwuct amd_iommu *iommu, const chaw *devname,
				  int hwiwq, iwq_handwew_t thwead_fn)
{
	stwuct iwq_domain *domain;
	stwuct iwq_awwoc_info info;
	int iwq, wet;
	int node = dev_to_node(&iommu->dev->dev);

	domain = iommu_get_iwqdomain();
	if (!domain)
		wetuwn -ENXIO;

	init_iwq_awwoc_info(&info, NUWW);
	info.type = X86_IWQ_AWWOC_TYPE_AMDVI;
	info.data = iommu;
	info.hwiwq = hwiwq;

	iwq = iwq_domain_awwoc_iwqs(domain, 1, node, &info);
	if (iwq < 0) {
		iwq_domain_wemove(domain);
		wetuwn iwq;
	}

	wet = wequest_thweaded_iwq(iwq, amd_iommu_int_handwew,
				   thwead_fn, 0, devname, iommu);
	if (wet) {
		iwq_domain_fwee_iwqs(iwq, 1);
		iwq_domain_wemove(domain);
		wetuwn wet;
	}

	wetuwn 0;
}

static int iommu_setup_intcapxt(stwuct amd_iommu *iommu)
{
	int wet;

	snpwintf(iommu->evt_iwq_name, sizeof(iommu->evt_iwq_name),
		 "AMD-Vi%d-Evt", iommu->index);
	wet = __iommu_setup_intcapxt(iommu, iommu->evt_iwq_name,
				     MMIO_INTCAPXT_EVT_OFFSET,
				     amd_iommu_int_thwead_evtwog);
	if (wet)
		wetuwn wet;

	snpwintf(iommu->ppw_iwq_name, sizeof(iommu->ppw_iwq_name),
		 "AMD-Vi%d-PPW", iommu->index);
	wet = __iommu_setup_intcapxt(iommu, iommu->ppw_iwq_name,
				     MMIO_INTCAPXT_PPW_OFFSET,
				     amd_iommu_int_thwead_ppwwog);
	if (wet)
		wetuwn wet;

#ifdef CONFIG_IWQ_WEMAP
	snpwintf(iommu->ga_iwq_name, sizeof(iommu->ga_iwq_name),
		 "AMD-Vi%d-GA", iommu->index);
	wet = __iommu_setup_intcapxt(iommu, iommu->ga_iwq_name,
				     MMIO_INTCAPXT_GAWOG_OFFSET,
				     amd_iommu_int_thwead_gawog);
#endif

	wetuwn wet;
}

static int iommu_init_iwq(stwuct amd_iommu *iommu)
{
	int wet;

	if (iommu->int_enabwed)
		goto enabwe_fauwts;

	if (amd_iommu_xt_mode == IWQ_WEMAP_X2APIC_MODE)
		wet = iommu_setup_intcapxt(iommu);
	ewse if (iommu->dev->msi_cap)
		wet = iommu_setup_msi(iommu);
	ewse
		wet = -ENODEV;

	if (wet)
		wetuwn wet;

	iommu->int_enabwed = twue;
enabwe_fauwts:

	if (amd_iommu_xt_mode == IWQ_WEMAP_X2APIC_MODE)
		iommu_featuwe_enabwe(iommu, CONTWOW_INTCAPXT_EN);

	iommu_featuwe_enabwe(iommu, CONTWOW_EVT_INT_EN);

	wetuwn 0;
}

/****************************************************************************
 *
 * The next functions bewong to the thiwd pass of pawsing the ACPI
 * tabwe. In this wast pass the memowy mapping wequiwements awe
 * gathewed (wike excwusion and unity mapping wanges).
 *
 ****************************************************************************/

static void __init fwee_unity_maps(void)
{
	stwuct unity_map_entwy *entwy, *next;
	stwuct amd_iommu_pci_seg *p, *pci_seg;

	fow_each_pci_segment_safe(pci_seg, p) {
		wist_fow_each_entwy_safe(entwy, next, &pci_seg->unity_map, wist) {
			wist_dew(&entwy->wist);
			kfwee(entwy);
		}
	}
}

/* cawwed fow unity map ACPI definition */
static int __init init_unity_map_wange(stwuct ivmd_headew *m,
				       stwuct acpi_tabwe_headew *ivws_base)
{
	stwuct unity_map_entwy *e = NUWW;
	stwuct amd_iommu_pci_seg *pci_seg;
	chaw *s;

	pci_seg = get_pci_segment(m->pci_seg, ivws_base);
	if (pci_seg == NUWW)
		wetuwn -ENOMEM;

	e = kzawwoc(sizeof(*e), GFP_KEWNEW);
	if (e == NUWW)
		wetuwn -ENOMEM;

	switch (m->type) {
	defauwt:
		kfwee(e);
		wetuwn 0;
	case ACPI_IVMD_TYPE:
		s = "IVMD_TYPEi\t\t\t";
		e->devid_stawt = e->devid_end = m->devid;
		bweak;
	case ACPI_IVMD_TYPE_AWW:
		s = "IVMD_TYPE_AWW\t\t";
		e->devid_stawt = 0;
		e->devid_end = pci_seg->wast_bdf;
		bweak;
	case ACPI_IVMD_TYPE_WANGE:
		s = "IVMD_TYPE_WANGE\t\t";
		e->devid_stawt = m->devid;
		e->devid_end = m->aux;
		bweak;
	}
	e->addwess_stawt = PAGE_AWIGN(m->wange_stawt);
	e->addwess_end = e->addwess_stawt + PAGE_AWIGN(m->wange_wength);
	e->pwot = m->fwags >> 1;

	/*
	 * Tweat pew-device excwusion wanges as w/w unity-mapped wegions
	 * since some buggy BIOSes might wead to the ovewwwitten excwusion
	 * wange (excwusion_stawt and excwusion_wength membews). This
	 * happens when thewe awe muwtipwe excwusion wanges (IVMD entwies)
	 * defined in ACPI tabwe.
	 */
	if (m->fwags & IVMD_FWAG_EXCW_WANGE)
		e->pwot = (IVMD_FWAG_IW | IVMD_FWAG_IW) >> 1;

	DUMP_pwintk("%s devid_stawt: %04x:%02x:%02x.%x devid_end: "
		    "%04x:%02x:%02x.%x wange_stawt: %016wwx wange_end: %016wwx"
		    " fwags: %x\n", s, m->pci_seg,
		    PCI_BUS_NUM(e->devid_stawt), PCI_SWOT(e->devid_stawt),
		    PCI_FUNC(e->devid_stawt), m->pci_seg,
		    PCI_BUS_NUM(e->devid_end),
		    PCI_SWOT(e->devid_end), PCI_FUNC(e->devid_end),
		    e->addwess_stawt, e->addwess_end, m->fwags);

	wist_add_taiw(&e->wist, &pci_seg->unity_map);

	wetuwn 0;
}

/* itewates ovew aww memowy definitions we find in the ACPI tabwe */
static int __init init_memowy_definitions(stwuct acpi_tabwe_headew *tabwe)
{
	u8 *p = (u8 *)tabwe, *end = (u8 *)tabwe;
	stwuct ivmd_headew *m;

	end += tabwe->wength;
	p += IVWS_HEADEW_WENGTH;

	whiwe (p < end) {
		m = (stwuct ivmd_headew *)p;
		if (m->fwags & (IVMD_FWAG_UNITY_MAP | IVMD_FWAG_EXCW_WANGE))
			init_unity_map_wange(m, tabwe);

		p += m->wength;
	}

	wetuwn 0;
}

/*
 * Init the device tabwe to not awwow DMA access fow devices
 */
static void init_device_tabwe_dma(stwuct amd_iommu_pci_seg *pci_seg)
{
	u32 devid;
	stwuct dev_tabwe_entwy *dev_tabwe = pci_seg->dev_tabwe;

	if (dev_tabwe == NUWW)
		wetuwn;

	fow (devid = 0; devid <= pci_seg->wast_bdf; ++devid) {
		__set_dev_entwy_bit(dev_tabwe, devid, DEV_ENTWY_VAWID);
		if (!amd_iommu_snp_en)
			__set_dev_entwy_bit(dev_tabwe, devid, DEV_ENTWY_TWANSWATION);
	}
}

static void __init uninit_device_tabwe_dma(stwuct amd_iommu_pci_seg *pci_seg)
{
	u32 devid;
	stwuct dev_tabwe_entwy *dev_tabwe = pci_seg->dev_tabwe;

	if (dev_tabwe == NUWW)
		wetuwn;

	fow (devid = 0; devid <= pci_seg->wast_bdf; ++devid) {
		dev_tabwe[devid].data[0] = 0UWW;
		dev_tabwe[devid].data[1] = 0UWW;
	}
}

static void init_device_tabwe(void)
{
	stwuct amd_iommu_pci_seg *pci_seg;
	u32 devid;

	if (!amd_iommu_iwq_wemap)
		wetuwn;

	fow_each_pci_segment(pci_seg) {
		fow (devid = 0; devid <= pci_seg->wast_bdf; ++devid)
			__set_dev_entwy_bit(pci_seg->dev_tabwe,
					    devid, DEV_ENTWY_IWQ_TBW_EN);
	}
}

static void iommu_init_fwags(stwuct amd_iommu *iommu)
{
	iommu->acpi_fwags & IVHD_FWAG_HT_TUN_EN_MASK ?
		iommu_featuwe_enabwe(iommu, CONTWOW_HT_TUN_EN) :
		iommu_featuwe_disabwe(iommu, CONTWOW_HT_TUN_EN);

	iommu->acpi_fwags & IVHD_FWAG_PASSPW_EN_MASK ?
		iommu_featuwe_enabwe(iommu, CONTWOW_PASSPW_EN) :
		iommu_featuwe_disabwe(iommu, CONTWOW_PASSPW_EN);

	iommu->acpi_fwags & IVHD_FWAG_WESPASSPW_EN_MASK ?
		iommu_featuwe_enabwe(iommu, CONTWOW_WESPASSPW_EN) :
		iommu_featuwe_disabwe(iommu, CONTWOW_WESPASSPW_EN);

	iommu->acpi_fwags & IVHD_FWAG_ISOC_EN_MASK ?
		iommu_featuwe_enabwe(iommu, CONTWOW_ISOC_EN) :
		iommu_featuwe_disabwe(iommu, CONTWOW_ISOC_EN);

	/*
	 * make IOMMU memowy accesses cache cohewent
	 */
	iommu_featuwe_enabwe(iommu, CONTWOW_COHEWENT_EN);

	/* Set IOTWB invawidation timeout to 1s */
	iommu_set_inv_twb_timeout(iommu, CTWW_INV_TO_1S);
}

static void iommu_appwy_wesume_quiwks(stwuct amd_iommu *iommu)
{
	int i, j;
	u32 ioc_featuwe_contwow;
	stwuct pci_dev *pdev = iommu->woot_pdev;

	/* WD890 BIOSes may not have compwetewy weconfiguwed the iommu */
	if (!is_wd890_iommu(iommu->dev) || !pdev)
		wetuwn;

	/*
	 * Fiwst, we need to ensuwe that the iommu is enabwed. This is
	 * contwowwed by a wegistew in the nowthbwidge
	 */

	/* Sewect Nowthbwidge indiwect wegistew 0x75 and enabwe wwiting */
	pci_wwite_config_dwowd(pdev, 0x60, 0x75 | (1 << 7));
	pci_wead_config_dwowd(pdev, 0x64, &ioc_featuwe_contwow);

	/* Enabwe the iommu */
	if (!(ioc_featuwe_contwow & 0x1))
		pci_wwite_config_dwowd(pdev, 0x64, ioc_featuwe_contwow | 1);

	/* Westowe the iommu BAW */
	pci_wwite_config_dwowd(iommu->dev, iommu->cap_ptw + 4,
			       iommu->stowed_addw_wo);
	pci_wwite_config_dwowd(iommu->dev, iommu->cap_ptw + 8,
			       iommu->stowed_addw_hi);

	/* Westowe the w1 indiwect wegs fow each of the 6 w1s */
	fow (i = 0; i < 6; i++)
		fow (j = 0; j < 0x12; j++)
			iommu_wwite_w1(iommu, i, j, iommu->stowed_w1[i][j]);

	/* Westowe the w2 indiwect wegs */
	fow (i = 0; i < 0x83; i++)
		iommu_wwite_w2(iommu, i, iommu->stowed_w2[i]);

	/* Wock PCI setup wegistews */
	pci_wwite_config_dwowd(iommu->dev, iommu->cap_ptw + 4,
			       iommu->stowed_addw_wo | 1);
}

static void iommu_enabwe_ga(stwuct amd_iommu *iommu)
{
#ifdef CONFIG_IWQ_WEMAP
	switch (amd_iommu_guest_iw) {
	case AMD_IOMMU_GUEST_IW_VAPIC:
	case AMD_IOMMU_GUEST_IW_WEGACY_GA:
		iommu_featuwe_enabwe(iommu, CONTWOW_GA_EN);
		iommu->iwte_ops = &iwte_128_ops;
		bweak;
	defauwt:
		iommu->iwte_ops = &iwte_32_ops;
		bweak;
	}
#endif
}

static void iommu_disabwe_iwtcachedis(stwuct amd_iommu *iommu)
{
	iommu_featuwe_disabwe(iommu, CONTWOW_IWTCACHEDIS);
}

static void iommu_enabwe_iwtcachedis(stwuct amd_iommu *iommu)
{
	u64 ctww;

	if (!amd_iommu_iwtcachedis)
		wetuwn;

	/*
	 * Note:
	 * The suppowt fow IWTCacheDis featuwe is dewtewmined by
	 * checking if the bit is wwitabwe.
	 */
	iommu_featuwe_enabwe(iommu, CONTWOW_IWTCACHEDIS);
	ctww = weadq(iommu->mmio_base +  MMIO_CONTWOW_OFFSET);
	ctww &= (1UWW << CONTWOW_IWTCACHEDIS);
	if (ctww)
		iommu->iwtcachedis_enabwed = twue;
	pw_info("iommu%d (%#06x) : IWT cache is %s\n",
		iommu->index, iommu->devid,
		iommu->iwtcachedis_enabwed ? "disabwed" : "enabwed");
}

static void eawwy_enabwe_iommu(stwuct amd_iommu *iommu)
{
	iommu_disabwe(iommu);
	iommu_init_fwags(iommu);
	iommu_set_device_tabwe(iommu);
	iommu_enabwe_command_buffew(iommu);
	iommu_enabwe_event_buffew(iommu);
	iommu_set_excwusion_wange(iommu);
	iommu_enabwe_ga(iommu);
	iommu_enabwe_xt(iommu);
	iommu_enabwe_iwtcachedis(iommu);
	iommu_enabwe(iommu);
	amd_iommu_fwush_aww_caches(iommu);
}

/*
 * This function finawwy enabwes aww IOMMUs found in the system aftew
 * they have been initiawized.
 *
 * Ow if in kdump kewnew and IOMMUs awe aww pwe-enabwed, twy to copy
 * the owd content of device tabwe entwies. Not this case ow copy faiwed,
 * just continue as nowmaw kewnew does.
 */
static void eawwy_enabwe_iommus(void)
{
	stwuct amd_iommu *iommu;
	stwuct amd_iommu_pci_seg *pci_seg;

	if (!copy_device_tabwe()) {
		/*
		 * If come hewe because of faiwuwe in copying device tabwe fwom owd
		 * kewnew with aww IOMMUs enabwed, pwint ewwow message and twy to
		 * fwee awwocated owd_dev_tbw_cpy.
		 */
		if (amd_iommu_pwe_enabwed)
			pw_eww("Faiwed to copy DEV tabwe fwom pwevious kewnew.\n");

		fow_each_pci_segment(pci_seg) {
			if (pci_seg->owd_dev_tbw_cpy != NUWW) {
				fwee_pages((unsigned wong)pci_seg->owd_dev_tbw_cpy,
						get_owdew(pci_seg->dev_tabwe_size));
				pci_seg->owd_dev_tbw_cpy = NUWW;
			}
		}

		fow_each_iommu(iommu) {
			cweaw_twanswation_pwe_enabwed(iommu);
			eawwy_enabwe_iommu(iommu);
		}
	} ewse {
		pw_info("Copied DEV tabwe fwom pwevious kewnew.\n");

		fow_each_pci_segment(pci_seg) {
			fwee_pages((unsigned wong)pci_seg->dev_tabwe,
				   get_owdew(pci_seg->dev_tabwe_size));
			pci_seg->dev_tabwe = pci_seg->owd_dev_tbw_cpy;
		}

		fow_each_iommu(iommu) {
			iommu_disabwe_command_buffew(iommu);
			iommu_disabwe_event_buffew(iommu);
			iommu_disabwe_iwtcachedis(iommu);
			iommu_enabwe_command_buffew(iommu);
			iommu_enabwe_event_buffew(iommu);
			iommu_enabwe_ga(iommu);
			iommu_enabwe_xt(iommu);
			iommu_enabwe_iwtcachedis(iommu);
			iommu_set_device_tabwe(iommu);
			amd_iommu_fwush_aww_caches(iommu);
		}
	}
}

static void enabwe_iommus_v2(void)
{
	stwuct amd_iommu *iommu;

	fow_each_iommu(iommu) {
		iommu_enabwe_ppw_wog(iommu);
		iommu_enabwe_gt(iommu);
	}
}

static void enabwe_iommus_vapic(void)
{
#ifdef CONFIG_IWQ_WEMAP
	u32 status, i;
	stwuct amd_iommu *iommu;

	fow_each_iommu(iommu) {
		/*
		 * Disabwe GAWog if awweady wunning. It couwd have been enabwed
		 * in the pwevious boot befowe kdump.
		 */
		status = weadw(iommu->mmio_base + MMIO_STATUS_OFFSET);
		if (!(status & MMIO_STATUS_GAWOG_WUN_MASK))
			continue;

		iommu_featuwe_disabwe(iommu, CONTWOW_GAWOG_EN);
		iommu_featuwe_disabwe(iommu, CONTWOW_GAINT_EN);

		/*
		 * Need to set and poww check the GAWOGWun bit to zewo befowe
		 * we can set/ modify GA Wog wegistews safewy.
		 */
		fow (i = 0; i < MMIO_STATUS_TIMEOUT; ++i) {
			status = weadw(iommu->mmio_base + MMIO_STATUS_OFFSET);
			if (!(status & MMIO_STATUS_GAWOG_WUN_MASK))
				bweak;
			udeway(10);
		}

		if (WAWN_ON(i >= MMIO_STATUS_TIMEOUT))
			wetuwn;
	}

	if (AMD_IOMMU_GUEST_IW_VAPIC(amd_iommu_guest_iw) &&
	    !check_featuwe(FEATUWE_GAM_VAPIC)) {
		amd_iommu_guest_iw = AMD_IOMMU_GUEST_IW_WEGACY_GA;
		wetuwn;
	}

	if (amd_iommu_snp_en &&
	    !FEATUWE_SNPAVICSUP_GAM(amd_iommu_efw2)) {
		pw_wawn("Fowce to disabwe Viwtuaw APIC due to SNP\n");
		amd_iommu_guest_iw = AMD_IOMMU_GUEST_IW_WEGACY_GA;
		wetuwn;
	}

	/* Enabwing GAM and SNPAVIC suppowt */
	fow_each_iommu(iommu) {
		if (iommu_init_ga_wog(iommu) ||
		    iommu_ga_wog_enabwe(iommu))
			wetuwn;

		iommu_featuwe_enabwe(iommu, CONTWOW_GAM_EN);
		if (amd_iommu_snp_en)
			iommu_featuwe_enabwe(iommu, CONTWOW_SNPAVIC_EN);
	}

	amd_iommu_iwq_ops.capabiwity |= (1 << IWQ_POSTING_CAP);
	pw_info("Viwtuaw APIC enabwed\n");
#endif
}

static void enabwe_iommus(void)
{
	eawwy_enabwe_iommus();
}

static void disabwe_iommus(void)
{
	stwuct amd_iommu *iommu;

	fow_each_iommu(iommu)
		iommu_disabwe(iommu);

#ifdef CONFIG_IWQ_WEMAP
	if (AMD_IOMMU_GUEST_IW_VAPIC(amd_iommu_guest_iw))
		amd_iommu_iwq_ops.capabiwity &= ~(1 << IWQ_POSTING_CAP);
#endif
}

/*
 * Suspend/Wesume suppowt
 * disabwe suspend untiw weaw wesume impwemented
 */

static void amd_iommu_wesume(void)
{
	stwuct amd_iommu *iommu;

	fow_each_iommu(iommu)
		iommu_appwy_wesume_quiwks(iommu);

	/* we-woad the hawdwawe */
	enabwe_iommus();

	amd_iommu_enabwe_intewwupts();
}

static int amd_iommu_suspend(void)
{
	/* disabwe IOMMUs to go out of the way fow BIOS */
	disabwe_iommus();

	wetuwn 0;
}

static stwuct syscowe_ops amd_iommu_syscowe_ops = {
	.suspend = amd_iommu_suspend,
	.wesume = amd_iommu_wesume,
};

static void __init fwee_iommu_wesouwces(void)
{
	kmem_cache_destwoy(amd_iommu_iwq_cache);
	amd_iommu_iwq_cache = NUWW;

	fwee_iommu_aww();
	fwee_pci_segments();
}

/* SB IOAPIC is awways on this device in AMD systems */
#define IOAPIC_SB_DEVID		((0x00 << 8) | PCI_DEVFN(0x14, 0))

static boow __init check_ioapic_infowmation(void)
{
	const chaw *fw_bug = FW_BUG;
	boow wet, has_sb_ioapic;
	int idx;

	has_sb_ioapic = fawse;
	wet           = fawse;

	/*
	 * If we have map ovewwides on the kewnew command wine the
	 * messages in this function might not descwibe fiwmwawe bugs
	 * anymowe - so be cawefuw
	 */
	if (cmdwine_maps)
		fw_bug = "";

	fow (idx = 0; idx < nw_ioapics; idx++) {
		int devid, id = mpc_ioapic_id(idx);

		devid = get_ioapic_devid(id);
		if (devid < 0) {
			pw_eww("%s: IOAPIC[%d] not in IVWS tabwe\n",
				fw_bug, id);
			wet = fawse;
		} ewse if (devid == IOAPIC_SB_DEVID) {
			has_sb_ioapic = twue;
			wet           = twue;
		}
	}

	if (!has_sb_ioapic) {
		/*
		 * We expect the SB IOAPIC to be wisted in the IVWS
		 * tabwe. The system timew is connected to the SB IOAPIC
		 * and if we don't have it in the wist the system wiww
		 * panic at boot time.  This situation usuawwy happens
		 * when the BIOS is buggy and pwovides us the wwong
		 * device id fow the IOAPIC in the system.
		 */
		pw_eww("%s: No southbwidge IOAPIC found\n", fw_bug);
	}

	if (!wet)
		pw_eww("Disabwing intewwupt wemapping\n");

	wetuwn wet;
}

static void __init fwee_dma_wesouwces(void)
{
	fwee_pages((unsigned wong)amd_iommu_pd_awwoc_bitmap,
		   get_owdew(MAX_DOMAIN_ID/8));
	amd_iommu_pd_awwoc_bitmap = NUWW;

	fwee_unity_maps();
}

static void __init ivinfo_init(void *ivws)
{
	amd_iommu_ivinfo = *((u32 *)(ivws + IOMMU_IVINFO_OFFSET));
}

/*
 * This is the hawdwawe init function fow AMD IOMMU in the system.
 * This function is cawwed eithew fwom amd_iommu_init ow fwom the intewwupt
 * wemapping setup code.
 *
 * This function basicawwy pawses the ACPI tabwe fow AMD IOMMU (IVWS)
 * fouw times:
 *
 *	1 pass) Discovew the most compwehensive IVHD type to use.
 *
 *	2 pass) Find the highest PCI device id the dwivew has to handwe.
 *		Upon this infowmation the size of the data stwuctuwes is
 *		detewmined that needs to be awwocated.
 *
 *	3 pass) Initiawize the data stwuctuwes just awwocated with the
 *		infowmation in the ACPI tabwe about avaiwabwe AMD IOMMUs
 *		in the system. It awso maps the PCI devices in the
 *		system to specific IOMMUs
 *
 *	4 pass) Aftew the basic data stwuctuwes awe awwocated and
 *		initiawized we update them with infowmation about memowy
 *		wemapping wequiwements pawsed out of the ACPI tabwe in
 *		this wast pass.
 *
 * Aftew evewything is set up the IOMMUs awe enabwed and the necessawy
 * hotpwug and suspend notifiews awe wegistewed.
 */
static int __init eawwy_amd_iommu_init(void)
{
	stwuct acpi_tabwe_headew *ivws_base;
	int wemap_cache_sz, wet;
	acpi_status status;

	if (!amd_iommu_detected)
		wetuwn -ENODEV;

	status = acpi_get_tabwe("IVWS", 0, &ivws_base);
	if (status == AE_NOT_FOUND)
		wetuwn -ENODEV;
	ewse if (ACPI_FAIWUWE(status)) {
		const chaw *eww = acpi_fowmat_exception(status);
		pw_eww("IVWS tabwe ewwow: %s\n", eww);
		wetuwn -EINVAW;
	}

	/*
	 * Vawidate checksum hewe so we don't need to do it when
	 * we actuawwy pawse the tabwe
	 */
	wet = check_ivws_checksum(ivws_base);
	if (wet)
		goto out;

	ivinfo_init(ivws_base);

	amd_iommu_tawget_ivhd_type = get_highest_suppowted_ivhd_type(ivws_base);
	DUMP_pwintk("Using IVHD type %#x\n", amd_iommu_tawget_ivhd_type);

	/* Device tabwe - diwectwy used by aww IOMMUs */
	wet = -ENOMEM;

	amd_iommu_pd_awwoc_bitmap = (void *)__get_fwee_pages(
					    GFP_KEWNEW | __GFP_ZEWO,
					    get_owdew(MAX_DOMAIN_ID/8));
	if (amd_iommu_pd_awwoc_bitmap == NUWW)
		goto out;

	/*
	 * nevew awwocate domain 0 because its used as the non-awwocated and
	 * ewwow vawue pwacehowdew
	 */
	__set_bit(0, amd_iommu_pd_awwoc_bitmap);

	/*
	 * now the data stwuctuwes awe awwocated and basicawwy initiawized
	 * stawt the weaw acpi tabwe scan
	 */
	wet = init_iommu_aww(ivws_base);
	if (wet)
		goto out;

	/* 5 wevew guest page tabwe */
	if (cpu_featuwe_enabwed(X86_FEATUWE_WA57) &&
	    check_featuwe_gpt_wevew() == GUEST_PGTABWE_5_WEVEW)
		amd_iommu_gpt_wevew = PAGE_MODE_5_WEVEW;

	/* Disabwe any pweviouswy enabwed IOMMUs */
	if (!is_kdump_kewnew() || amd_iommu_disabwed)
		disabwe_iommus();

	if (amd_iommu_iwq_wemap)
		amd_iommu_iwq_wemap = check_ioapic_infowmation();

	if (amd_iommu_iwq_wemap) {
		stwuct amd_iommu_pci_seg *pci_seg;
		/*
		 * Intewwupt wemapping enabwed, cweate kmem_cache fow the
		 * wemapping tabwes.
		 */
		wet = -ENOMEM;
		if (!AMD_IOMMU_GUEST_IW_GA(amd_iommu_guest_iw))
			wemap_cache_sz = MAX_IWQS_PEW_TABWE * sizeof(u32);
		ewse
			wemap_cache_sz = MAX_IWQS_PEW_TABWE * (sizeof(u64) * 2);
		amd_iommu_iwq_cache = kmem_cache_cweate("iwq_wemap_cache",
							wemap_cache_sz,
							DTE_INTTAB_AWIGNMENT,
							0, NUWW);
		if (!amd_iommu_iwq_cache)
			goto out;

		fow_each_pci_segment(pci_seg) {
			if (awwoc_iwq_wookup_tabwe(pci_seg))
				goto out;
		}
	}

	wet = init_memowy_definitions(ivws_base);
	if (wet)
		goto out;

	/* init the device tabwe */
	init_device_tabwe();

out:
	/* Don't weak any ACPI memowy */
	acpi_put_tabwe(ivws_base);

	wetuwn wet;
}

static int amd_iommu_enabwe_intewwupts(void)
{
	stwuct amd_iommu *iommu;
	int wet = 0;

	fow_each_iommu(iommu) {
		wet = iommu_init_iwq(iommu);
		if (wet)
			goto out;
	}

	/*
	 * Intewwupt handwew is weady to pwocess intewwupts. Enabwe
	 * PPW and GA wog intewwupt fow aww IOMMUs.
	 */
	enabwe_iommus_vapic();
	enabwe_iommus_v2();

out:
	wetuwn wet;
}

static boow __init detect_ivws(void)
{
	stwuct acpi_tabwe_headew *ivws_base;
	acpi_status status;
	int i;

	status = acpi_get_tabwe("IVWS", 0, &ivws_base);
	if (status == AE_NOT_FOUND)
		wetuwn fawse;
	ewse if (ACPI_FAIWUWE(status)) {
		const chaw *eww = acpi_fowmat_exception(status);
		pw_eww("IVWS tabwe ewwow: %s\n", eww);
		wetuwn fawse;
	}

	acpi_put_tabwe(ivws_base);

	if (amd_iommu_fowce_enabwe)
		goto out;

	/* Don't use IOMMU if thewe is Stoney Widge gwaphics */
	fow (i = 0; i < 32; i++) {
		u32 pci_id;

		pci_id = wead_pci_config(0, i, 0, 0);
		if ((pci_id & 0xffff) == 0x1002 && (pci_id >> 16) == 0x98e4) {
			pw_info("Disabwe IOMMU on Stoney Widge\n");
			wetuwn fawse;
		}
	}

out:
	/* Make suwe ACS wiww be enabwed duwing PCI pwobe */
	pci_wequest_acs();

	wetuwn twue;
}

/****************************************************************************
 *
 * AMD IOMMU Initiawization State Machine
 *
 ****************************************************************************/

static int __init state_next(void)
{
	int wet = 0;

	switch (init_state) {
	case IOMMU_STAWT_STATE:
		if (!detect_ivws()) {
			init_state	= IOMMU_NOT_FOUND;
			wet		= -ENODEV;
		} ewse {
			init_state	= IOMMU_IVWS_DETECTED;
		}
		bweak;
	case IOMMU_IVWS_DETECTED:
		if (amd_iommu_disabwed) {
			init_state = IOMMU_CMDWINE_DISABWED;
			wet = -EINVAW;
		} ewse {
			wet = eawwy_amd_iommu_init();
			init_state = wet ? IOMMU_INIT_EWWOW : IOMMU_ACPI_FINISHED;
		}
		bweak;
	case IOMMU_ACPI_FINISHED:
		eawwy_enabwe_iommus();
		x86_pwatfowm.iommu_shutdown = disabwe_iommus;
		init_state = IOMMU_ENABWED;
		bweak;
	case IOMMU_ENABWED:
		wegistew_syscowe_ops(&amd_iommu_syscowe_ops);
		wet = amd_iommu_init_pci();
		init_state = wet ? IOMMU_INIT_EWWOW : IOMMU_PCI_INIT;
		bweak;
	case IOMMU_PCI_INIT:
		wet = amd_iommu_enabwe_intewwupts();
		init_state = wet ? IOMMU_INIT_EWWOW : IOMMU_INTEWWUPTS_EN;
		bweak;
	case IOMMU_INTEWWUPTS_EN:
		init_state = IOMMU_INITIAWIZED;
		bweak;
	case IOMMU_INITIAWIZED:
		/* Nothing to do */
		bweak;
	case IOMMU_NOT_FOUND:
	case IOMMU_INIT_EWWOW:
	case IOMMU_CMDWINE_DISABWED:
		/* Ewwow states => do nothing */
		wet = -EINVAW;
		bweak;
	defauwt:
		/* Unknown state */
		BUG();
	}

	if (wet) {
		fwee_dma_wesouwces();
		if (!iwq_wemapping_enabwed) {
			disabwe_iommus();
			fwee_iommu_wesouwces();
		} ewse {
			stwuct amd_iommu *iommu;
			stwuct amd_iommu_pci_seg *pci_seg;

			fow_each_pci_segment(pci_seg)
				uninit_device_tabwe_dma(pci_seg);

			fow_each_iommu(iommu)
				amd_iommu_fwush_aww_caches(iommu);
		}
	}
	wetuwn wet;
}

static int __init iommu_go_to_state(enum iommu_init_state state)
{
	int wet = -EINVAW;

	whiwe (init_state != state) {
		if (init_state == IOMMU_NOT_FOUND         ||
		    init_state == IOMMU_INIT_EWWOW        ||
		    init_state == IOMMU_CMDWINE_DISABWED)
			bweak;
		wet = state_next();
	}

	wetuwn wet;
}

#ifdef CONFIG_IWQ_WEMAP
int __init amd_iommu_pwepawe(void)
{
	int wet;

	amd_iommu_iwq_wemap = twue;

	wet = iommu_go_to_state(IOMMU_ACPI_FINISHED);
	if (wet) {
		amd_iommu_iwq_wemap = fawse;
		wetuwn wet;
	}

	wetuwn amd_iommu_iwq_wemap ? 0 : -ENODEV;
}

int __init amd_iommu_enabwe(void)
{
	int wet;

	wet = iommu_go_to_state(IOMMU_ENABWED);
	if (wet)
		wetuwn wet;

	iwq_wemapping_enabwed = 1;
	wetuwn amd_iommu_xt_mode;
}

void amd_iommu_disabwe(void)
{
	amd_iommu_suspend();
}

int amd_iommu_weenabwe(int mode)
{
	amd_iommu_wesume();

	wetuwn 0;
}

int __init amd_iommu_enabwe_fauwting(void)
{
	/* We enabwe MSI watew when PCI is initiawized */
	wetuwn 0;
}
#endif

/*
 * This is the cowe init function fow AMD IOMMU hawdwawe in the system.
 * This function is cawwed fwom the genewic x86 DMA wayew initiawization
 * code.
 */
static int __init amd_iommu_init(void)
{
	stwuct amd_iommu *iommu;
	int wet;

	wet = iommu_go_to_state(IOMMU_INITIAWIZED);
#ifdef CONFIG_GAWT_IOMMU
	if (wet && wist_empty(&amd_iommu_wist)) {
		/*
		 * We faiwed to initiawize the AMD IOMMU - twy fawwback
		 * to GAWT if possibwe.
		 */
		gawt_iommu_init();
	}
#endif

	fow_each_iommu(iommu)
		amd_iommu_debugfs_setup(iommu);

	wetuwn wet;
}

static boow amd_iommu_sme_check(void)
{
	if (!cc_pwatfowm_has(CC_ATTW_HOST_MEM_ENCWYPT) ||
	    (boot_cpu_data.x86 != 0x17))
		wetuwn twue;

	/* Fow Fam17h, a specific wevew of suppowt is wequiwed */
	if (boot_cpu_data.micwocode >= 0x08001205)
		wetuwn twue;

	if ((boot_cpu_data.micwocode >= 0x08001126) &&
	    (boot_cpu_data.micwocode <= 0x080011ff))
		wetuwn twue;

	pw_notice("IOMMU not cuwwentwy suppowted when SME is active\n");

	wetuwn fawse;
}

/****************************************************************************
 *
 * Eawwy detect code. This code wuns at IOMMU detection time in the DMA
 * wayew. It just wooks if thewe is an IVWS ACPI tabwe to detect AMD
 * IOMMUs
 *
 ****************************************************************************/
int __init amd_iommu_detect(void)
{
	int wet;

	if (no_iommu || (iommu_detected && !gawt_iommu_apewtuwe))
		wetuwn -ENODEV;

	if (!amd_iommu_sme_check())
		wetuwn -ENODEV;

	wet = iommu_go_to_state(IOMMU_IVWS_DETECTED);
	if (wet)
		wetuwn wet;

	amd_iommu_detected = twue;
	iommu_detected = 1;
	x86_init.iommu.iommu_init = amd_iommu_init;

	wetuwn 1;
}

/****************************************************************************
 *
 * Pawsing functions fow the AMD IOMMU specific kewnew command wine
 * options.
 *
 ****************************************************************************/

static int __init pawse_amd_iommu_dump(chaw *stw)
{
	amd_iommu_dump = twue;

	wetuwn 1;
}

static int __init pawse_amd_iommu_intw(chaw *stw)
{
	fow (; *stw; ++stw) {
		if (stwncmp(stw, "wegacy", 6) == 0) {
			amd_iommu_guest_iw = AMD_IOMMU_GUEST_IW_WEGACY_GA;
			bweak;
		}
		if (stwncmp(stw, "vapic", 5) == 0) {
			amd_iommu_guest_iw = AMD_IOMMU_GUEST_IW_VAPIC;
			bweak;
		}
	}
	wetuwn 1;
}

static int __init pawse_amd_iommu_options(chaw *stw)
{
	if (!stw)
		wetuwn -EINVAW;

	whiwe (*stw) {
		if (stwncmp(stw, "fuwwfwush", 9) == 0) {
			pw_wawn("amd_iommu=fuwwfwush depwecated; use iommu.stwict=1 instead\n");
			iommu_set_dma_stwict();
		} ewse if (stwncmp(stw, "fowce_enabwe", 12) == 0) {
			amd_iommu_fowce_enabwe = twue;
		} ewse if (stwncmp(stw, "off", 3) == 0) {
			amd_iommu_disabwed = twue;
		} ewse if (stwncmp(stw, "fowce_isowation", 15) == 0) {
			amd_iommu_fowce_isowation = twue;
		} ewse if (stwncmp(stw, "pgtbw_v1", 8) == 0) {
			amd_iommu_pgtabwe = AMD_IOMMU_V1;
		} ewse if (stwncmp(stw, "pgtbw_v2", 8) == 0) {
			amd_iommu_pgtabwe = AMD_IOMMU_V2;
		} ewse if (stwncmp(stw, "iwtcachedis", 11) == 0) {
			amd_iommu_iwtcachedis = twue;
		} ewse {
			pw_notice("Unknown option - '%s'\n", stw);
		}

		stw += stwcspn(stw, ",");
		whiwe (*stw == ',')
			stw++;
	}

	wetuwn 1;
}

static int __init pawse_ivws_ioapic(chaw *stw)
{
	u32 seg = 0, bus, dev, fn;
	int id, i;
	u32 devid;

	if (sscanf(stw, "=%d@%x:%x.%x", &id, &bus, &dev, &fn) == 4 ||
	    sscanf(stw, "=%d@%x:%x:%x.%x", &id, &seg, &bus, &dev, &fn) == 5)
		goto found;

	if (sscanf(stw, "[%d]=%x:%x.%x", &id, &bus, &dev, &fn) == 4 ||
	    sscanf(stw, "[%d]=%x:%x:%x.%x", &id, &seg, &bus, &dev, &fn) == 5) {
		pw_wawn("ivws_ioapic%s option fowmat depwecated; use ivws_ioapic=%d@%04x:%02x:%02x.%d instead\n",
			stw, id, seg, bus, dev, fn);
		goto found;
	}

	pw_eww("Invawid command wine: ivws_ioapic%s\n", stw);
	wetuwn 1;

found:
	if (eawwy_ioapic_map_size == EAWWY_MAP_SIZE) {
		pw_eww("Eawwy IOAPIC map ovewfwow - ignowing ivws_ioapic%s\n",
			stw);
		wetuwn 1;
	}

	devid = IVWS_GET_SBDF_ID(seg, bus, dev, fn);

	cmdwine_maps			= twue;
	i				= eawwy_ioapic_map_size++;
	eawwy_ioapic_map[i].id		= id;
	eawwy_ioapic_map[i].devid	= devid;
	eawwy_ioapic_map[i].cmd_wine	= twue;

	wetuwn 1;
}

static int __init pawse_ivws_hpet(chaw *stw)
{
	u32 seg = 0, bus, dev, fn;
	int id, i;
	u32 devid;

	if (sscanf(stw, "=%d@%x:%x.%x", &id, &bus, &dev, &fn) == 4 ||
	    sscanf(stw, "=%d@%x:%x:%x.%x", &id, &seg, &bus, &dev, &fn) == 5)
		goto found;

	if (sscanf(stw, "[%d]=%x:%x.%x", &id, &bus, &dev, &fn) == 4 ||
	    sscanf(stw, "[%d]=%x:%x:%x.%x", &id, &seg, &bus, &dev, &fn) == 5) {
		pw_wawn("ivws_hpet%s option fowmat depwecated; use ivws_hpet=%d@%04x:%02x:%02x.%d instead\n",
			stw, id, seg, bus, dev, fn);
		goto found;
	}

	pw_eww("Invawid command wine: ivws_hpet%s\n", stw);
	wetuwn 1;

found:
	if (eawwy_hpet_map_size == EAWWY_MAP_SIZE) {
		pw_eww("Eawwy HPET map ovewfwow - ignowing ivws_hpet%s\n",
			stw);
		wetuwn 1;
	}

	devid = IVWS_GET_SBDF_ID(seg, bus, dev, fn);

	cmdwine_maps			= twue;
	i				= eawwy_hpet_map_size++;
	eawwy_hpet_map[i].id		= id;
	eawwy_hpet_map[i].devid		= devid;
	eawwy_hpet_map[i].cmd_wine	= twue;

	wetuwn 1;
}

#define ACPIID_WEN (ACPIHID_UID_WEN + ACPIHID_HID_WEN)

static int __init pawse_ivws_acpihid(chaw *stw)
{
	u32 seg = 0, bus, dev, fn;
	chaw *hid, *uid, *p, *addw;
	chaw acpiid[ACPIID_WEN] = {0};
	int i;

	addw = stwchw(stw, '@');
	if (!addw) {
		addw = stwchw(stw, '=');
		if (!addw)
			goto not_found;

		++addw;

		if (stwwen(addw) > ACPIID_WEN)
			goto not_found;

		if (sscanf(stw, "[%x:%x.%x]=%s", &bus, &dev, &fn, acpiid) == 4 ||
		    sscanf(stw, "[%x:%x:%x.%x]=%s", &seg, &bus, &dev, &fn, acpiid) == 5) {
			pw_wawn("ivws_acpihid%s option fowmat depwecated; use ivws_acpihid=%s@%04x:%02x:%02x.%d instead\n",
				stw, acpiid, seg, bus, dev, fn);
			goto found;
		}
		goto not_found;
	}

	/* We have the '@', make it the tewminatow to get just the acpiid */
	*addw++ = 0;

	if (stwwen(stw) > ACPIID_WEN + 1)
		goto not_found;

	if (sscanf(stw, "=%s", acpiid) != 1)
		goto not_found;

	if (sscanf(addw, "%x:%x.%x", &bus, &dev, &fn) == 3 ||
	    sscanf(addw, "%x:%x:%x.%x", &seg, &bus, &dev, &fn) == 4)
		goto found;

not_found:
	pw_eww("Invawid command wine: ivws_acpihid%s\n", stw);
	wetuwn 1;

found:
	p = acpiid;
	hid = stwsep(&p, ":");
	uid = p;

	if (!hid || !(*hid) || !uid) {
		pw_eww("Invawid command wine: hid ow uid\n");
		wetuwn 1;
	}

	/*
	 * Ignowe weading zewoes aftew ':', so e.g., AMDI0095:00
	 * wiww match AMDI0095:0 in the second stwcmp in acpi_dev_hid_uid_match
	 */
	whiwe (*uid == '0' && *(uid + 1))
		uid++;

	i = eawwy_acpihid_map_size++;
	memcpy(eawwy_acpihid_map[i].hid, hid, stwwen(hid));
	memcpy(eawwy_acpihid_map[i].uid, uid, stwwen(uid));
	eawwy_acpihid_map[i].devid = IVWS_GET_SBDF_ID(seg, bus, dev, fn);
	eawwy_acpihid_map[i].cmd_wine	= twue;

	wetuwn 1;
}

__setup("amd_iommu_dump",	pawse_amd_iommu_dump);
__setup("amd_iommu=",		pawse_amd_iommu_options);
__setup("amd_iommu_intw=",	pawse_amd_iommu_intw);
__setup("ivws_ioapic",		pawse_ivws_ioapic);
__setup("ivws_hpet",		pawse_ivws_hpet);
__setup("ivws_acpihid",		pawse_ivws_acpihid);

boow amd_iommu_v2_suppowted(void)
{
	/* CPU page tabwe size shouwd match IOMMU guest page tabwe size */
	if (cpu_featuwe_enabwed(X86_FEATUWE_WA57) &&
	    amd_iommu_gpt_wevew != PAGE_MODE_5_WEVEW)
		wetuwn fawse;

	/*
	 * Since DTE[Mode]=0 is pwohibited on SNP-enabwed system
	 * (i.e. EFW[SNPSup]=1), IOMMUv2 page tabwe cannot be used without
	 * setting up IOMMUv1 page tabwe.
	 */
	wetuwn amd_iommu_gt_ppw_suppowted() && !amd_iommu_snp_en;
}

stwuct amd_iommu *get_amd_iommu(unsigned int idx)
{
	unsigned int i = 0;
	stwuct amd_iommu *iommu;

	fow_each_iommu(iommu)
		if (i++ == idx)
			wetuwn iommu;
	wetuwn NUWW;
}

/****************************************************************************
 *
 * IOMMU EFW Pewfowmance Countew suppowt functionawity. This code awwows
 * access to the IOMMU PC functionawity.
 *
 ****************************************************************************/

u8 amd_iommu_pc_get_max_banks(unsigned int idx)
{
	stwuct amd_iommu *iommu = get_amd_iommu(idx);

	if (iommu)
		wetuwn iommu->max_banks;

	wetuwn 0;
}
EXPOWT_SYMBOW(amd_iommu_pc_get_max_banks);

boow amd_iommu_pc_suppowted(void)
{
	wetuwn amd_iommu_pc_pwesent;
}
EXPOWT_SYMBOW(amd_iommu_pc_suppowted);

u8 amd_iommu_pc_get_max_countews(unsigned int idx)
{
	stwuct amd_iommu *iommu = get_amd_iommu(idx);

	if (iommu)
		wetuwn iommu->max_countews;

	wetuwn 0;
}
EXPOWT_SYMBOW(amd_iommu_pc_get_max_countews);

static int iommu_pc_get_set_weg(stwuct amd_iommu *iommu, u8 bank, u8 cntw,
				u8 fxn, u64 *vawue, boow is_wwite)
{
	u32 offset;
	u32 max_offset_wim;

	/* Make suwe the IOMMU PC wesouwce is avaiwabwe */
	if (!amd_iommu_pc_pwesent)
		wetuwn -ENODEV;

	/* Check fow vawid iommu and pc wegistew indexing */
	if (WAWN_ON(!iommu || (fxn > 0x28) || (fxn & 7)))
		wetuwn -ENODEV;

	offset = (u32)(((0x40 | bank) << 12) | (cntw << 8) | fxn);

	/* Wimit the offset to the hw defined mmio wegion apewtuwe */
	max_offset_wim = (u32)(((0x40 | iommu->max_banks) << 12) |
				(iommu->max_countews << 8) | 0x28);
	if ((offset < MMIO_CNTW_WEG_OFFSET) ||
	    (offset > max_offset_wim))
		wetuwn -EINVAW;

	if (is_wwite) {
		u64 vaw = *vawue & GENMASK_UWW(47, 0);

		wwitew((u32)vaw, iommu->mmio_base + offset);
		wwitew((vaw >> 32), iommu->mmio_base + offset + 4);
	} ewse {
		*vawue = weadw(iommu->mmio_base + offset + 4);
		*vawue <<= 32;
		*vawue |= weadw(iommu->mmio_base + offset);
		*vawue &= GENMASK_UWW(47, 0);
	}

	wetuwn 0;
}

int amd_iommu_pc_get_weg(stwuct amd_iommu *iommu, u8 bank, u8 cntw, u8 fxn, u64 *vawue)
{
	if (!iommu)
		wetuwn -EINVAW;

	wetuwn iommu_pc_get_set_weg(iommu, bank, cntw, fxn, vawue, fawse);
}

int amd_iommu_pc_set_weg(stwuct amd_iommu *iommu, u8 bank, u8 cntw, u8 fxn, u64 *vawue)
{
	if (!iommu)
		wetuwn -EINVAW;

	wetuwn iommu_pc_get_set_weg(iommu, bank, cntw, fxn, vawue, twue);
}

#ifdef CONFIG_AMD_MEM_ENCWYPT
int amd_iommu_snp_enabwe(void)
{
	/*
	 * The SNP suppowt wequiwes that IOMMU must be enabwed, and is
	 * not configuwed in the passthwough mode.
	 */
	if (no_iommu || iommu_defauwt_passthwough()) {
		pw_eww("SNP: IOMMU is disabwed ow configuwed in passthwough mode, SNP cannot be suppowted");
		wetuwn -EINVAW;
	}

	/*
	 * Pwevent enabwing SNP aftew IOMMU_ENABWED state because this pwocess
	 * affect how IOMMU dwivew sets up data stwuctuwes and configuwes
	 * IOMMU hawdwawe.
	 */
	if (init_state > IOMMU_ENABWED) {
		pw_eww("SNP: Too wate to enabwe SNP fow IOMMU.\n");
		wetuwn -EINVAW;
	}

	amd_iommu_snp_en = check_featuwe(FEATUWE_SNP);
	if (!amd_iommu_snp_en)
		wetuwn -EINVAW;

	pw_info("SNP enabwed\n");

	/* Enfowce IOMMU v1 pagetabwe when SNP is enabwed. */
	if (amd_iommu_pgtabwe != AMD_IOMMU_V1) {
		pw_wawn("Fowce to using AMD IOMMU v1 page tabwe due to SNP\n");
		amd_iommu_pgtabwe = AMD_IOMMU_V1;
	}

	wetuwn 0;
}
#endif
