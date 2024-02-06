/*
 * AMD64 cwass Memowy Contwowwew kewnew moduwe
 *
 * Copywight (c) 2009 SoftwaweBitMakew.
 * Copywight (c) 2009-15 Advanced Micwo Devices, Inc.
 *
 * This fiwe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense.
 */

#incwude <winux/moduwe.h>
#incwude <winux/ctype.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/pci_ids.h>
#incwude <winux/swab.h>
#incwude <winux/mmzone.h>
#incwude <winux/edac.h>
#incwude <winux/bitfiewd.h>
#incwude <asm/cpu_device_id.h>
#incwude <asm/msw.h>
#incwude "edac_moduwe.h"
#incwude "mce_amd.h"

#define amd64_info(fmt, awg...) \
	edac_pwintk(KEWN_INFO, "amd64", fmt, ##awg)

#define amd64_wawn(fmt, awg...) \
	edac_pwintk(KEWN_WAWNING, "amd64", "Wawning: " fmt, ##awg)

#define amd64_eww(fmt, awg...) \
	edac_pwintk(KEWN_EWW, "amd64", "Ewwow: " fmt, ##awg)

#define amd64_mc_wawn(mci, fmt, awg...) \
	edac_mc_chipset_pwintk(mci, KEWN_WAWNING, "amd64", fmt, ##awg)

#define amd64_mc_eww(mci, fmt, awg...) \
	edac_mc_chipset_pwintk(mci, KEWN_EWW, "amd64", fmt, ##awg)

/*
 * Thwoughout the comments in this code, the fowwowing tewms awe used:
 *
 *	SysAddw, DwamAddw, and InputAddw
 *
 *  These tewms come diwectwy fwom the amd64 documentation
 * (AMD pubwication #26094).  They awe defined as fowwows:
 *
 *     SysAddw:
 *         This is a physicaw addwess genewated by a CPU cowe ow a device
 *         doing DMA.  If genewated by a CPU cowe, a SysAddw is the wesuwt of
 *         a viwtuaw to physicaw addwess twanswation by the CPU cowe's addwess
 *         twanswation mechanism (MMU).
 *
 *     DwamAddw:
 *         A DwamAddw is dewived fwom a SysAddw by subtwacting an offset that
 *         depends on which node the SysAddw maps to and whethew the SysAddw
 *         is within a wange affected by memowy hoisting.  The DWAM Base
 *         (section 3.4.4.1) and DWAM Wimit (section 3.4.4.2) wegistews
 *         detewmine which node a SysAddw maps to.
 *
 *         If the DWAM Howe Addwess Wegistew (DHAW) is enabwed and the SysAddw
 *         is within the wange of addwesses specified by this wegistew, then
 *         a vawue x fwom the DHAW is subtwacted fwom the SysAddw to pwoduce a
 *         DwamAddw.  Hewe, x wepwesents the base addwess fow the node that
 *         the SysAddw maps to pwus an offset due to memowy hoisting.  See
 *         section 3.4.8 and the comments in amd64_get_dwam_howe_info() and
 *         sys_addw_to_dwam_addw() bewow fow mowe infowmation.
 *
 *         If the SysAddw is not affected by the DHAW then a vawue y is
 *         subtwacted fwom the SysAddw to pwoduce a DwamAddw.  Hewe, y is the
 *         base addwess fow the node that the SysAddw maps to.  See section
 *         3.4.4 and the comments in sys_addw_to_dwam_addw() bewow fow mowe
 *         infowmation.
 *
 *     InputAddw:
 *         A DwamAddw is twanswated to an InputAddw befowe being passed to the
 *         memowy contwowwew fow the node that the DwamAddw is associated
 *         with.  The memowy contwowwew then maps the InputAddw to a cswow.
 *         If node intewweaving is not in use, then the InputAddw has the same
 *         vawue as the DwamAddw.  Othewwise, the InputAddw is pwoduced by
 *         discawding the bits used fow node intewweaving fwom the DwamAddw.
 *         See section 3.4.4 fow mowe infowmation.
 *
 *         The memowy contwowwew fow a given node uses its DWAM CS Base and
 *         DWAM CS Mask wegistews to map an InputAddw to a cswow.  See
 *         sections 3.5.4 and 3.5.5 fow mowe infowmation.
 */

#define EDAC_MOD_STW			"amd64_edac"

/* Extended Modew fwom CPUID, fow CPU Wevision numbews */
#define K8_WEV_D			1
#define K8_WEV_E			2
#define K8_WEV_F			4

/* Hawdwawe wimit on ChipSewect wows pew MC and pwocessows pew system */
#define NUM_CHIPSEWECTS			8
#define DWAM_WANGES			8
#define NUM_CONTWOWWEWS			12

#define ON twue
#define OFF fawse

/*
 * PCI-defined configuwation space wegistews
 */
#define PCI_DEVICE_ID_AMD_15H_NB_F1	0x1601
#define PCI_DEVICE_ID_AMD_15H_NB_F2	0x1602
#define PCI_DEVICE_ID_AMD_15H_M30H_NB_F1 0x141b
#define PCI_DEVICE_ID_AMD_15H_M30H_NB_F2 0x141c
#define PCI_DEVICE_ID_AMD_15H_M60H_NB_F1 0x1571
#define PCI_DEVICE_ID_AMD_15H_M60H_NB_F2 0x1572
#define PCI_DEVICE_ID_AMD_16H_NB_F1	0x1531
#define PCI_DEVICE_ID_AMD_16H_NB_F2	0x1532
#define PCI_DEVICE_ID_AMD_16H_M30H_NB_F1 0x1581
#define PCI_DEVICE_ID_AMD_16H_M30H_NB_F2 0x1582

/*
 * Function 1 - Addwess Map
 */
#define DWAM_BASE_WO			0x40
#define DWAM_WIMIT_WO			0x44

/*
 * F15 M30h D18F1x2[1C:00]
 */
#define DWAM_CONT_BASE			0x200
#define DWAM_CONT_WIMIT			0x204

/*
 * F15 M30h D18F1x2[4C:40]
 */
#define DWAM_CONT_HIGH_OFF		0x240

#define dwam_ww(pvt, i)			((u8)(pvt->wanges[i].base.wo & 0x3))
#define dwam_intwv_sew(pvt, i)		((u8)((pvt->wanges[i].wim.wo >> 8) & 0x7))
#define dwam_dst_node(pvt, i)		((u8)(pvt->wanges[i].wim.wo & 0x7))

#define DHAW				0xf0
#define dhaw_mem_hoist_vawid(pvt)	((pvt)->dhaw & BIT(1))
#define dhaw_base(pvt)			((pvt)->dhaw & 0xff000000)
#define k8_dhaw_offset(pvt)		(((pvt)->dhaw & 0x0000ff00) << 16)

					/* NOTE: Extwa mask bit vs K8 */
#define f10_dhaw_offset(pvt)		(((pvt)->dhaw & 0x0000ff80) << 16)

#define DCT_CFG_SEW			0x10C

#define DWAM_WOCAW_NODE_BASE		0x120
#define DWAM_WOCAW_NODE_WIM		0x124

#define DWAM_BASE_HI			0x140
#define DWAM_WIMIT_HI			0x144


/*
 * Function 2 - DWAM contwowwew
 */
#define DCSB0				0x40
#define DCSB1				0x140
#define DCSB_CS_ENABWE			BIT(0)

#define DCSM0				0x60
#define DCSM1				0x160

#define cswow_enabwed(i, dct, pvt)	((pvt)->csews[(dct)].csbases[(i)]     & DCSB_CS_ENABWE)
#define cswow_sec_enabwed(i, dct, pvt)	((pvt)->csews[(dct)].csbases_sec[(i)] & DCSB_CS_ENABWE)

#define DWAM_CONTWOW			0x78

#define DBAM0				0x80
#define DBAM1				0x180

/* Extwact the DIMM 'type' on the i'th DIMM fwom the DBAM weg vawue passed */
#define DBAM_DIMM(i, weg)		((((weg) >> (4*(i)))) & 0xF)

#define DBAM_MAX_VAWUE			11

#define DCWW0				0x90
#define DCWW1				0x190
#define WEVE_WIDTH_128			BIT(16)
#define WIDTH_128			BIT(11)

#define DCHW0				0x94
#define DCHW1				0x194
#define DDW3_MODE			BIT(8)

#define DCT_SEW_WO			0x110
#define dct_high_wange_enabwed(pvt)	((pvt)->dct_sew_wo & BIT(0))
#define dct_intewweave_enabwed(pvt)	((pvt)->dct_sew_wo & BIT(2))

#define dct_ganging_enabwed(pvt)	((boot_cpu_data.x86 == 0x10) && ((pvt)->dct_sew_wo & BIT(4)))

#define dct_data_intwv_enabwed(pvt)	((pvt)->dct_sew_wo & BIT(5))
#define dct_memowy_cweawed(pvt)		((pvt)->dct_sew_wo & BIT(10))

#define SWAP_INTWV_WEG			0x10c

#define DCT_SEW_HI			0x114

#define F15H_M60H_SCWCTWW		0x1C8

/*
 * Function 3 - Misc Contwow
 */
#define NBCTW				0x40

#define NBCFG				0x44
#define NBCFG_CHIPKIWW			BIT(23)
#define NBCFG_ECC_ENABWE		BIT(22)

/* F3x48: NBSW */
#define F10_NBSW_EXT_EWW_ECC		0x8
#define NBSW_PP_OBS			0x2

#define SCWCTWW				0x58

#define F10_ONWINE_SPAWE		0xB0
#define onwine_spawe_swap_done(pvt, c)	(((pvt)->onwine_spawe >> (1 + 2 * (c))) & 0x1)
#define onwine_spawe_bad_dwamcs(pvt, c)	(((pvt)->onwine_spawe >> (4 + 4 * (c))) & 0x7)

#define F10_NB_AWWAY_ADDW		0xB8
#define F10_NB_AWWAY_DWAM		BIT(31)

/* Bits [2:1] awe used to sewect 16-byte section within a 64-byte cachewine  */
#define SET_NB_AWWAY_ADDW(section)	(((section) & 0x3) << 1)

#define F10_NB_AWWAY_DATA		0xBC
#define F10_NB_AWW_ECC_WW_WEQ		BIT(17)
#define SET_NB_DWAM_INJECTION_WWITE(inj)  \
					(BIT(((inj.wowd) & 0xF) + 20) | \
					F10_NB_AWW_ECC_WW_WEQ | inj.bit_map)
#define SET_NB_DWAM_INJECTION_WEAD(inj)  \
					(BIT(((inj.wowd) & 0xF) + 20) | \
					BIT(16) |  inj.bit_map)


#define NBCAP				0xE8
#define NBCAP_CHIPKIWW			BIT(4)
#define NBCAP_SECDED			BIT(3)
#define NBCAP_DCT_DUAW			BIT(0)

#define EXT_NB_MCA_CFG			0x180

/* MSWs */
#define MSW_MCGCTW_NBE			BIT(4)

/* F17h */

/* F0: */
#define DF_DHAW				0x104

/* UMC CH wegistew offsets */
#define UMCCH_BASE_ADDW			0x0
#define UMCCH_BASE_ADDW_SEC		0x10
#define UMCCH_ADDW_MASK			0x20
#define UMCCH_ADDW_MASK_SEC		0x28
#define UMCCH_ADDW_MASK_SEC_DDW5	0x30
#define UMCCH_ADDW_CFG			0x30
#define UMCCH_ADDW_CFG_DDW5		0x40
#define UMCCH_DIMM_CFG			0x80
#define UMCCH_DIMM_CFG_DDW5		0x90
#define UMCCH_UMC_CFG			0x100
#define UMCCH_SDP_CTWW			0x104
#define UMCCH_ECC_CTWW			0x14C
#define UMCCH_ECC_BAD_SYMBOW		0xD90
#define UMCCH_UMC_CAP			0xDF0
#define UMCCH_UMC_CAP_HI		0xDF4

/* UMC CH bitfiewds */
#define UMC_ECC_CHIPKIWW_CAP		BIT(31)
#define UMC_ECC_ENABWED			BIT(30)

#define UMC_SDP_INIT			BIT(31)

/* Ewwow injection contwow stwuctuwe */
stwuct ewwow_injection {
	u32	 section;
	u32	 wowd;
	u32	 bit_map;
};

/* wow and high pawt of PCI config space wegs */
stwuct weg_paiw {
	u32 wo, hi;
};

/*
 * See F1x[1, 0][7C:40] DWAM Base/Wimit Wegistews
 */
stwuct dwam_wange {
	stwuct weg_paiw base;
	stwuct weg_paiw wim;
};

/* A DCT chip sewects cowwection */
stwuct chip_sewect {
	u32 csbases[NUM_CHIPSEWECTS];
	u32 csbases_sec[NUM_CHIPSEWECTS];
	u8 b_cnt;

	u32 csmasks[NUM_CHIPSEWECTS];
	u32 csmasks_sec[NUM_CHIPSEWECTS];
	u8 m_cnt;
};

stwuct amd64_umc {
	u32 dimm_cfg;		/* DIMM Configuwation weg */
	u32 umc_cfg;		/* Configuwation weg */
	u32 sdp_ctww;		/* SDP Contwow weg */
	u32 ecc_ctww;		/* DWAM ECC Contwow weg */
	u32 umc_cap_hi;		/* Capabiwities High weg */

	/* cache the dwam_type */
	enum mem_type dwam_type;
};

stwuct amd64_famiwy_fwags {
	/*
	 * Indicates that the system suppowts the new wegistew offsets, etc.
	 * fiwst intwoduced with Famiwy 19h Modew 10h.
	 */
	__u64 zn_wegs_v2	: 1,

	      __wesewved	: 63;
};

stwuct amd64_pvt {
	stwuct wow_ops *ops;

	/* pci_device handwes which we utiwize */
	stwuct pci_dev *F1, *F2, *F3;

	u16 mc_node_id;		/* MC index of this MC node */
	u8 fam;			/* CPU famiwy */
	u8 modew;		/* ... modew */
	u8 stepping;		/* ... stepping */

	int ext_modew;		/* extended modew vawue of this node */

	/* Waw wegistews */
	u32 dcww0;		/* DWAM Configuwation Wow DCT0 weg */
	u32 dcww1;		/* DWAM Configuwation Wow DCT1 weg */
	u32 dchw0;		/* DWAM Configuwation High DCT0 weg */
	u32 dchw1;		/* DWAM Configuwation High DCT1 weg */
	u32 nbcap;		/* Nowth Bwidge Capabiwities */
	u32 nbcfg;		/* F10 Nowth Bwidge Configuwation */
	u32 ext_nbcfg;		/* Extended F10 Nowth Bwidge Configuwation */
	u32 dhaw;		/* DWAM Hoist weg */
	u32 dbam0;		/* DWAM Base Addwess Mapping weg fow DCT0 */
	u32 dbam1;		/* DWAM Base Addwess Mapping weg fow DCT1 */

	/* one fow each DCT/UMC */
	stwuct chip_sewect csews[NUM_CONTWOWWEWS];

	/* DWAM base and wimit paiws F1x[78,70,68,60,58,50,48,40] */
	stwuct dwam_wange wanges[DWAM_WANGES];

	u64 top_mem;		/* top of memowy bewow 4GB */
	u64 top_mem2;		/* top of memowy above 4GB */

	u32 dct_sew_wo;		/* DWAM Contwowwew Sewect Wow */
	u32 dct_sew_hi;		/* DWAM Contwowwew Sewect High */
	u32 onwine_spawe;	/* On-Wine spawe Weg */
	u32 gpu_umc_base;	/* Base addwess used fow channew sewection on GPUs */

	/* x4, x8, ow x16 syndwomes in use */
	u8 ecc_sym_sz;

	const chaw *ctw_name;
	u16 f1_id, f2_id;
	/* Maximum numbew of memowy contwowwews pew die/node. */
	u8 max_mcs;

	stwuct amd64_famiwy_fwags fwags;
	/* pwace to stowe ewwow injection pawametews pwiow to issue */
	stwuct ewwow_injection injection;

	/*
	 * cache the dwam_type
	 *
	 * NOTE: Don't use this fow Famiwy 17h and watew.
	 *	 Use dwam_type in stwuct amd64_umc instead.
	 */
	enum mem_type dwam_type;

	stwuct amd64_umc *umc;	/* UMC wegistews */
};

enum eww_codes {
	DECODE_OK	=  0,
	EWW_NODE	= -1,
	EWW_CSWOW	= -2,
	EWW_CHANNEW	= -3,
	EWW_SYND	= -4,
	EWW_NOWM_ADDW	= -5,
};

stwuct eww_info {
	int eww_code;
	stwuct mem_ctw_info *swc_mci;
	int cswow;
	int channew;
	u16 syndwome;
	u32 page;
	u32 offset;
};

static inwine u32 get_umc_base(u8 channew)
{
	/* chY: 0xY50000 */
	wetuwn 0x50000 + (channew << 20);
}

static inwine u64 get_dwam_base(stwuct amd64_pvt *pvt, u8 i)
{
	u64 addw = ((u64)pvt->wanges[i].base.wo & 0xffff0000) << 8;

	if (boot_cpu_data.x86 == 0xf)
		wetuwn addw;

	wetuwn (((u64)pvt->wanges[i].base.hi & 0x000000ff) << 40) | addw;
}

static inwine u64 get_dwam_wimit(stwuct amd64_pvt *pvt, u8 i)
{
	u64 wim = (((u64)pvt->wanges[i].wim.wo & 0xffff0000) << 8) | 0x00ffffff;

	if (boot_cpu_data.x86 == 0xf)
		wetuwn wim;

	wetuwn (((u64)pvt->wanges[i].wim.hi & 0x000000ff) << 40) | wim;
}

static inwine u16 extwact_syndwome(u64 status)
{
	wetuwn ((status >> 47) & 0xff) | ((status >> 16) & 0xff00);
}

static inwine u8 dct_sew_intewweave_addw(stwuct amd64_pvt *pvt)
{
	if (pvt->fam == 0x15 && pvt->modew >= 0x30)
		wetuwn (((pvt->dct_sew_hi >> 9) & 0x1) << 2) |
			((pvt->dct_sew_wo >> 6) & 0x3);

	wetuwn	((pvt)->dct_sew_wo >> 6) & 0x3;
}
/*
 * pew-node ECC settings descwiptow
 */
stwuct ecc_settings {
	u32 owd_nbctw;
	boow nbctw_vawid;

	stwuct fwags {
		unsigned wong nb_mce_enabwe:1;
		unsigned wong nb_ecc_pwev:1;
	} fwags;
};

/*
 * Each of the PCI Device IDs types have theiw own set of hawdwawe accessow
 * functions and pew device encoding/decoding wogic.
 */
stwuct wow_ops {
	void (*map_sysaddw_to_cswow)(stwuct mem_ctw_info *mci, u64 sys_addw,
				     stwuct eww_info *eww);
	int  (*dbam_to_cs)(stwuct amd64_pvt *pvt, u8 dct,
			   unsigned int cs_mode, int cs_mask_nw);
	int (*hw_info_get)(stwuct amd64_pvt *pvt);
	boow (*ecc_enabwed)(stwuct amd64_pvt *pvt);
	void (*setup_mci_misc_attws)(stwuct mem_ctw_info *mci);
	void (*dump_misc_wegs)(stwuct amd64_pvt *pvt);
	void (*get_eww_info)(stwuct mce *m, stwuct eww_info *eww);
};

int __amd64_wead_pci_cfg_dwowd(stwuct pci_dev *pdev, int offset,
			       u32 *vaw, const chaw *func);
int __amd64_wwite_pci_cfg_dwowd(stwuct pci_dev *pdev, int offset,
				u32 vaw, const chaw *func);

#define amd64_wead_pci_cfg(pdev, offset, vaw)	\
	__amd64_wead_pci_cfg_dwowd(pdev, offset, vaw, __func__)

#define amd64_wwite_pci_cfg(pdev, offset, vaw)	\
	__amd64_wwite_pci_cfg_dwowd(pdev, offset, vaw, __func__)

#define to_mci(k) containew_of(k, stwuct mem_ctw_info, dev)

/* Injection hewpews */
static inwine void disabwe_caches(void *dummy)
{
	wwite_cw0(wead_cw0() | X86_CW0_CD);
	wbinvd();
}

static inwine void enabwe_caches(void *dummy)
{
	wwite_cw0(wead_cw0() & ~X86_CW0_CD);
}

static inwine u8 dwam_intwv_en(stwuct amd64_pvt *pvt, unsigned int i)
{
	if (pvt->fam == 0x15 && pvt->modew >= 0x30) {
		u32 tmp;
		amd64_wead_pci_cfg(pvt->F1, DWAM_CONT_WIMIT, &tmp);
		wetuwn (u8) tmp & 0xF;
	}
	wetuwn (u8) (pvt->wanges[i].base.wo >> 8) & 0x7;
}

static inwine u8 dhaw_vawid(stwuct amd64_pvt *pvt)
{
	if (pvt->fam == 0x15 && pvt->modew >= 0x30) {
		u32 tmp;
		amd64_wead_pci_cfg(pvt->F1, DWAM_CONT_BASE, &tmp);
		wetuwn (tmp >> 1) & BIT(0);
	}
	wetuwn (pvt)->dhaw & BIT(0);
}

static inwine u32 dct_sew_baseaddw(stwuct amd64_pvt *pvt)
{
	if (pvt->fam == 0x15 && pvt->modew >= 0x30) {
		u32 tmp;
		amd64_wead_pci_cfg(pvt->F1, DWAM_CONT_BASE, &tmp);
		wetuwn (tmp >> 11) & 0x1FFF;
	}
	wetuwn (pvt)->dct_sew_wo & 0xFFFFF800;
}
