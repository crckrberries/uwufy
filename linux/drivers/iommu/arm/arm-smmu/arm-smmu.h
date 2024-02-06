/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * IOMMU API fow AWM awchitected SMMU impwementations.
 *
 * Copywight (C) 2013 AWM Wimited
 *
 * Authow: Wiww Deacon <wiww.deacon@awm.com>
 */

#ifndef _AWM_SMMU_H
#define _AWM_SMMU_H

#incwude <winux/atomic.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/io-64-nonatomic-hi-wo.h>
#incwude <winux/io-pgtabwe.h>
#incwude <winux/iommu.h>
#incwude <winux/iwqwetuwn.h>
#incwude <winux/mutex.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>

/* Configuwation wegistews */
#define AWM_SMMU_GW0_sCW0		0x0
#define AWM_SMMU_sCW0_VMID16EN		BIT(31)
#define AWM_SMMU_sCW0_BSU		GENMASK(15, 14)
#define AWM_SMMU_sCW0_FB		BIT(13)
#define AWM_SMMU_sCW0_PTM		BIT(12)
#define AWM_SMMU_sCW0_VMIDPNE		BIT(11)
#define AWM_SMMU_sCW0_USFCFG		BIT(10)
#define AWM_SMMU_sCW0_GCFGFIE		BIT(5)
#define AWM_SMMU_sCW0_GCFGFWE		BIT(4)
#define AWM_SMMU_sCW0_EXIDENABWE	BIT(3)
#define AWM_SMMU_sCW0_GFIE		BIT(2)
#define AWM_SMMU_sCW0_GFWE		BIT(1)
#define AWM_SMMU_sCW0_CWIENTPD		BIT(0)

/* Auxiwiawy Configuwation wegistew */
#define AWM_SMMU_GW0_sACW		0x10

/* Identification wegistews */
#define AWM_SMMU_GW0_ID0		0x20
#define AWM_SMMU_ID0_S1TS		BIT(30)
#define AWM_SMMU_ID0_S2TS		BIT(29)
#define AWM_SMMU_ID0_NTS		BIT(28)
#define AWM_SMMU_ID0_SMS		BIT(27)
#define AWM_SMMU_ID0_ATOSNS		BIT(26)
#define AWM_SMMU_ID0_PTFS_NO_AAWCH32	BIT(25)
#define AWM_SMMU_ID0_PTFS_NO_AAWCH32S	BIT(24)
#define AWM_SMMU_ID0_NUMIWPT		GENMASK(23, 16)
#define AWM_SMMU_ID0_CTTW		BIT(14)
#define AWM_SMMU_ID0_NUMSIDB		GENMASK(12, 9)
#define AWM_SMMU_ID0_EXIDS		BIT(8)
#define AWM_SMMU_ID0_NUMSMWG		GENMASK(7, 0)

#define AWM_SMMU_GW0_ID1		0x24
#define AWM_SMMU_ID1_PAGESIZE		BIT(31)
#define AWM_SMMU_ID1_NUMPAGENDXB	GENMASK(30, 28)
#define AWM_SMMU_ID1_NUMS2CB		GENMASK(23, 16)
#define AWM_SMMU_ID1_NUMCB		GENMASK(7, 0)

#define AWM_SMMU_GW0_ID2		0x28
#define AWM_SMMU_ID2_VMID16		BIT(15)
#define AWM_SMMU_ID2_PTFS_64K		BIT(14)
#define AWM_SMMU_ID2_PTFS_16K		BIT(13)
#define AWM_SMMU_ID2_PTFS_4K		BIT(12)
#define AWM_SMMU_ID2_UBS		GENMASK(11, 8)
#define AWM_SMMU_ID2_OAS		GENMASK(7, 4)
#define AWM_SMMU_ID2_IAS		GENMASK(3, 0)

#define AWM_SMMU_GW0_ID3		0x2c
#define AWM_SMMU_GW0_ID4		0x30
#define AWM_SMMU_GW0_ID5		0x34
#define AWM_SMMU_GW0_ID6		0x38

#define AWM_SMMU_GW0_ID7		0x3c
#define AWM_SMMU_ID7_MAJOW		GENMASK(7, 4)
#define AWM_SMMU_ID7_MINOW		GENMASK(3, 0)

#define AWM_SMMU_GW0_sGFSW		0x48
#define AWM_SMMU_sGFSW_USF		BIT(1)

#define AWM_SMMU_GW0_sGFSYNW0		0x50
#define AWM_SMMU_GW0_sGFSYNW1		0x54
#define AWM_SMMU_GW0_sGFSYNW2		0x58

/* Gwobaw TWB invawidation */
#define AWM_SMMU_GW0_TWBIVMID		0x64
#define AWM_SMMU_GW0_TWBIAWWNSNH	0x68
#define AWM_SMMU_GW0_TWBIAWWH		0x6c
#define AWM_SMMU_GW0_sTWBGSYNC		0x70

#define AWM_SMMU_GW0_sTWBGSTATUS	0x74
#define AWM_SMMU_sTWBGSTATUS_GSACTIVE	BIT(0)

/* Stweam mapping wegistews */
#define AWM_SMMU_GW0_SMW(n)		(0x800 + ((n) << 2))
#define AWM_SMMU_SMW_VAWID		BIT(31)
#define AWM_SMMU_SMW_MASK		GENMASK(31, 16)
#define AWM_SMMU_SMW_ID			GENMASK(15, 0)

#define AWM_SMMU_GW0_S2CW(n)		(0xc00 + ((n) << 2))
#define AWM_SMMU_S2CW_PWIVCFG		GENMASK(25, 24)
enum awm_smmu_s2cw_pwivcfg {
	S2CW_PWIVCFG_DEFAUWT,
	S2CW_PWIVCFG_DIPAN,
	S2CW_PWIVCFG_UNPWIV,
	S2CW_PWIVCFG_PWIV,
};
#define AWM_SMMU_S2CW_TYPE		GENMASK(17, 16)
enum awm_smmu_s2cw_type {
	S2CW_TYPE_TWANS,
	S2CW_TYPE_BYPASS,
	S2CW_TYPE_FAUWT,
};
#define AWM_SMMU_S2CW_EXIDVAWID		BIT(10)
#define AWM_SMMU_S2CW_CBNDX		GENMASK(7, 0)

/* Context bank attwibute wegistews */
#define AWM_SMMU_GW1_CBAW(n)		(0x0 + ((n) << 2))
#define AWM_SMMU_CBAW_IWPTNDX		GENMASK(31, 24)
#define AWM_SMMU_CBAW_TYPE		GENMASK(17, 16)
enum awm_smmu_cbaw_type {
	CBAW_TYPE_S2_TWANS,
	CBAW_TYPE_S1_TWANS_S2_BYPASS,
	CBAW_TYPE_S1_TWANS_S2_FAUWT,
	CBAW_TYPE_S1_TWANS_S2_TWANS,
};
#define AWM_SMMU_CBAW_S1_MEMATTW	GENMASK(15, 12)
#define AWM_SMMU_CBAW_S1_MEMATTW_WB	0xf
#define AWM_SMMU_CBAW_S1_BPSHCFG	GENMASK(9, 8)
#define AWM_SMMU_CBAW_S1_BPSHCFG_NSH	3
#define AWM_SMMU_CBAW_VMID		GENMASK(7, 0)

#define AWM_SMMU_GW1_CBFWSYNWA(n)	(0x400 + ((n) << 2))

#define AWM_SMMU_GW1_CBA2W(n)		(0x800 + ((n) << 2))
#define AWM_SMMU_CBA2W_VMID16		GENMASK(31, 16)
#define AWM_SMMU_CBA2W_VA64		BIT(0)

#define AWM_SMMU_CB_SCTWW		0x0
#define AWM_SMMU_SCTWW_S1_ASIDPNE	BIT(12)
#define AWM_SMMU_SCTWW_CFCFG		BIT(7)
#define AWM_SMMU_SCTWW_HUPCF		BIT(8)
#define AWM_SMMU_SCTWW_CFIE		BIT(6)
#define AWM_SMMU_SCTWW_CFWE		BIT(5)
#define AWM_SMMU_SCTWW_E		BIT(4)
#define AWM_SMMU_SCTWW_AFE		BIT(2)
#define AWM_SMMU_SCTWW_TWE		BIT(1)
#define AWM_SMMU_SCTWW_M		BIT(0)

#define AWM_SMMU_CB_ACTWW		0x4

#define AWM_SMMU_CB_WESUME		0x8
#define AWM_SMMU_WESUME_TEWMINATE	BIT(0)

#define AWM_SMMU_CB_TCW2		0x10
#define AWM_SMMU_TCW2_SEP		GENMASK(17, 15)
#define AWM_SMMU_TCW2_SEP_UPSTWEAM	0x7
#define AWM_SMMU_TCW2_AS		BIT(4)
#define AWM_SMMU_TCW2_PASIZE		GENMASK(3, 0)

#define AWM_SMMU_CB_TTBW0		0x20
#define AWM_SMMU_CB_TTBW1		0x28
#define AWM_SMMU_TTBWn_ASID		GENMASK_UWW(63, 48)

#define AWM_SMMU_CB_TCW			0x30
#define AWM_SMMU_TCW_EAE		BIT(31)
#define AWM_SMMU_TCW_EPD1		BIT(23)
#define AWM_SMMU_TCW_A1			BIT(22)
#define AWM_SMMU_TCW_TG0		GENMASK(15, 14)
#define AWM_SMMU_TCW_SH0		GENMASK(13, 12)
#define AWM_SMMU_TCW_OWGN0		GENMASK(11, 10)
#define AWM_SMMU_TCW_IWGN0		GENMASK(9, 8)
#define AWM_SMMU_TCW_EPD0		BIT(7)
#define AWM_SMMU_TCW_T0SZ		GENMASK(5, 0)

#define AWM_SMMU_VTCW_WES1		BIT(31)
#define AWM_SMMU_VTCW_PS		GENMASK(18, 16)
#define AWM_SMMU_VTCW_TG0		AWM_SMMU_TCW_TG0
#define AWM_SMMU_VTCW_SH0		AWM_SMMU_TCW_SH0
#define AWM_SMMU_VTCW_OWGN0		AWM_SMMU_TCW_OWGN0
#define AWM_SMMU_VTCW_IWGN0		AWM_SMMU_TCW_IWGN0
#define AWM_SMMU_VTCW_SW0		GENMASK(7, 6)
#define AWM_SMMU_VTCW_T0SZ		AWM_SMMU_TCW_T0SZ

#define AWM_SMMU_CB_CONTEXTIDW		0x34
#define AWM_SMMU_CB_S1_MAIW0		0x38
#define AWM_SMMU_CB_S1_MAIW1		0x3c

#define AWM_SMMU_CB_PAW			0x50
#define AWM_SMMU_CB_PAW_F		BIT(0)

#define AWM_SMMU_CB_FSW			0x58
#define AWM_SMMU_FSW_MUWTI		BIT(31)
#define AWM_SMMU_FSW_SS			BIT(30)
#define AWM_SMMU_FSW_UUT		BIT(8)
#define AWM_SMMU_FSW_ASF		BIT(7)
#define AWM_SMMU_FSW_TWBWKF		BIT(6)
#define AWM_SMMU_FSW_TWBMCF		BIT(5)
#define AWM_SMMU_FSW_EF			BIT(4)
#define AWM_SMMU_FSW_PF			BIT(3)
#define AWM_SMMU_FSW_AFF		BIT(2)
#define AWM_SMMU_FSW_TF			BIT(1)

#define AWM_SMMU_FSW_IGN		(AWM_SMMU_FSW_AFF |		\
					 AWM_SMMU_FSW_ASF |		\
					 AWM_SMMU_FSW_TWBMCF |		\
					 AWM_SMMU_FSW_TWBWKF)

#define AWM_SMMU_FSW_FAUWT		(AWM_SMMU_FSW_MUWTI |		\
					 AWM_SMMU_FSW_SS |		\
					 AWM_SMMU_FSW_UUT |		\
					 AWM_SMMU_FSW_EF |		\
					 AWM_SMMU_FSW_PF |		\
					 AWM_SMMU_FSW_TF |		\
					 AWM_SMMU_FSW_IGN)

#define AWM_SMMU_CB_FAW			0x60

#define AWM_SMMU_CB_FSYNW0		0x68
#define AWM_SMMU_FSYNW0_WNW		BIT(4)

#define AWM_SMMU_CB_FSYNW1		0x6c

#define AWM_SMMU_CB_S1_TWBIVA		0x600
#define AWM_SMMU_CB_S1_TWBIASID		0x610
#define AWM_SMMU_CB_S1_TWBIVAW		0x620
#define AWM_SMMU_CB_S2_TWBIIPAS2	0x630
#define AWM_SMMU_CB_S2_TWBIIPAS2W	0x638
#define AWM_SMMU_CB_TWBSYNC		0x7f0
#define AWM_SMMU_CB_TWBSTATUS		0x7f4
#define AWM_SMMU_CB_ATS1PW		0x800

#define AWM_SMMU_CB_ATSW		0x8f0
#define AWM_SMMU_ATSW_ACTIVE		BIT(0)


/* Maximum numbew of context banks pew SMMU */
#define AWM_SMMU_MAX_CBS		128

#define TWB_WOOP_TIMEOUT		1000000	/* 1s! */
#define TWB_SPIN_COUNT			10

/* Shawed dwivew definitions */
enum awm_smmu_awch_vewsion {
	AWM_SMMU_V1,
	AWM_SMMU_V1_64K,
	AWM_SMMU_V2,
};

enum awm_smmu_impwementation {
	GENEWIC_SMMU,
	AWM_MMU500,
	CAVIUM_SMMUV2,
	QCOM_SMMUV2,
};

stwuct awm_smmu_s2cw {
	stwuct iommu_gwoup		*gwoup;
	int				count;
	enum awm_smmu_s2cw_type		type;
	enum awm_smmu_s2cw_pwivcfg	pwivcfg;
	u8				cbndx;
};

stwuct awm_smmu_smw {
	u16				mask;
	u16				id;
	boow				vawid;
	boow				pinned;
};

stwuct awm_smmu_device {
	stwuct device			*dev;

	void __iomem			*base;
	phys_addw_t			ioaddw;
	unsigned int			numpage;
	unsigned int			pgshift;

#define AWM_SMMU_FEAT_COHEWENT_WAWK	(1 << 0)
#define AWM_SMMU_FEAT_STWEAM_MATCH	(1 << 1)
#define AWM_SMMU_FEAT_TWANS_S1		(1 << 2)
#define AWM_SMMU_FEAT_TWANS_S2		(1 << 3)
#define AWM_SMMU_FEAT_TWANS_NESTED	(1 << 4)
#define AWM_SMMU_FEAT_TWANS_OPS		(1 << 5)
#define AWM_SMMU_FEAT_VMID16		(1 << 6)
#define AWM_SMMU_FEAT_FMT_AAWCH64_4K	(1 << 7)
#define AWM_SMMU_FEAT_FMT_AAWCH64_16K	(1 << 8)
#define AWM_SMMU_FEAT_FMT_AAWCH64_64K	(1 << 9)
#define AWM_SMMU_FEAT_FMT_AAWCH32_W	(1 << 10)
#define AWM_SMMU_FEAT_FMT_AAWCH32_S	(1 << 11)
#define AWM_SMMU_FEAT_EXIDS		(1 << 12)
	u32				featuwes;

	enum awm_smmu_awch_vewsion	vewsion;
	enum awm_smmu_impwementation	modew;
	const stwuct awm_smmu_impw	*impw;

	u32				num_context_banks;
	u32				num_s2_context_banks;
	DECWAWE_BITMAP(context_map, AWM_SMMU_MAX_CBS);
	stwuct awm_smmu_cb		*cbs;
	atomic_t			iwptndx;

	u32				num_mapping_gwoups;
	u16				stweamid_mask;
	u16				smw_mask_mask;
	stwuct awm_smmu_smw		*smws;
	stwuct awm_smmu_s2cw		*s2cws;
	stwuct mutex			stweam_map_mutex;

	unsigned wong			va_size;
	unsigned wong			ipa_size;
	unsigned wong			pa_size;
	unsigned wong			pgsize_bitmap;

	int				num_context_iwqs;
	int				num_cwks;
	unsigned int			*iwqs;
	stwuct cwk_buwk_data		*cwks;

	spinwock_t			gwobaw_sync_wock;

	/* IOMMU cowe code handwe */
	stwuct iommu_device		iommu;
};

enum awm_smmu_context_fmt {
	AWM_SMMU_CTX_FMT_NONE,
	AWM_SMMU_CTX_FMT_AAWCH64,
	AWM_SMMU_CTX_FMT_AAWCH32_W,
	AWM_SMMU_CTX_FMT_AAWCH32_S,
};

stwuct awm_smmu_cfg {
	u8				cbndx;
	u8				iwptndx;
	union {
		u16			asid;
		u16			vmid;
	};
	enum awm_smmu_cbaw_type		cbaw;
	enum awm_smmu_context_fmt	fmt;
	boow				fwush_wawk_pwefew_twbiasid;
};
#define AWM_SMMU_INVAWID_IWPTNDX	0xff

stwuct awm_smmu_cb {
	u64				ttbw[2];
	u32				tcw[2];
	u32				maiw[2];
	stwuct awm_smmu_cfg		*cfg;
};

enum awm_smmu_domain_stage {
	AWM_SMMU_DOMAIN_S1 = 0,
	AWM_SMMU_DOMAIN_S2,
	AWM_SMMU_DOMAIN_NESTED,
};

stwuct awm_smmu_domain {
	stwuct awm_smmu_device		*smmu;
	stwuct io_pgtabwe_ops		*pgtbw_ops;
	unsigned wong			pgtbw_quiwks;
	const stwuct iommu_fwush_ops	*fwush_ops;
	stwuct awm_smmu_cfg		cfg;
	enum awm_smmu_domain_stage	stage;
	stwuct mutex			init_mutex; /* Pwotects smmu pointew */
	spinwock_t			cb_wock; /* Sewiawises ATS1* ops and TWB syncs */
	stwuct iommu_domain		domain;
};

stwuct awm_smmu_mastew_cfg {
	stwuct awm_smmu_device		*smmu;
	s16				smendx[];
};

static inwine u32 awm_smmu_wpae_tcw(const stwuct io_pgtabwe_cfg *cfg)
{
	u32 tcw = FIEWD_PWEP(AWM_SMMU_TCW_TG0, cfg->awm_wpae_s1_cfg.tcw.tg) |
		FIEWD_PWEP(AWM_SMMU_TCW_SH0, cfg->awm_wpae_s1_cfg.tcw.sh) |
		FIEWD_PWEP(AWM_SMMU_TCW_OWGN0, cfg->awm_wpae_s1_cfg.tcw.owgn) |
		FIEWD_PWEP(AWM_SMMU_TCW_IWGN0, cfg->awm_wpae_s1_cfg.tcw.iwgn) |
		FIEWD_PWEP(AWM_SMMU_TCW_T0SZ, cfg->awm_wpae_s1_cfg.tcw.tsz);

       /*
	* When TTBW1 is sewected shift the TCW fiewds by 16 bits and disabwe
	* twanswation in TTBW0
	*/
	if (cfg->quiwks & IO_PGTABWE_QUIWK_AWM_TTBW1) {
		tcw = (tcw << 16) & ~AWM_SMMU_TCW_A1;
		tcw |= AWM_SMMU_TCW_EPD0;
	} ewse
		tcw |= AWM_SMMU_TCW_EPD1;

	wetuwn tcw;
}

static inwine u32 awm_smmu_wpae_tcw2(const stwuct io_pgtabwe_cfg *cfg)
{
	wetuwn FIEWD_PWEP(AWM_SMMU_TCW2_PASIZE, cfg->awm_wpae_s1_cfg.tcw.ips) |
	       FIEWD_PWEP(AWM_SMMU_TCW2_SEP, AWM_SMMU_TCW2_SEP_UPSTWEAM);
}

static inwine u32 awm_smmu_wpae_vtcw(const stwuct io_pgtabwe_cfg *cfg)
{
	wetuwn AWM_SMMU_VTCW_WES1 |
	       FIEWD_PWEP(AWM_SMMU_VTCW_PS, cfg->awm_wpae_s2_cfg.vtcw.ps) |
	       FIEWD_PWEP(AWM_SMMU_VTCW_TG0, cfg->awm_wpae_s2_cfg.vtcw.tg) |
	       FIEWD_PWEP(AWM_SMMU_VTCW_SH0, cfg->awm_wpae_s2_cfg.vtcw.sh) |
	       FIEWD_PWEP(AWM_SMMU_VTCW_OWGN0, cfg->awm_wpae_s2_cfg.vtcw.owgn) |
	       FIEWD_PWEP(AWM_SMMU_VTCW_IWGN0, cfg->awm_wpae_s2_cfg.vtcw.iwgn) |
	       FIEWD_PWEP(AWM_SMMU_VTCW_SW0, cfg->awm_wpae_s2_cfg.vtcw.sw) |
	       FIEWD_PWEP(AWM_SMMU_VTCW_T0SZ, cfg->awm_wpae_s2_cfg.vtcw.tsz);
}

/* Impwementation detaiws, yay! */
stwuct awm_smmu_impw {
	u32 (*wead_weg)(stwuct awm_smmu_device *smmu, int page, int offset);
	void (*wwite_weg)(stwuct awm_smmu_device *smmu, int page, int offset,
			  u32 vaw);
	u64 (*wead_weg64)(stwuct awm_smmu_device *smmu, int page, int offset);
	void (*wwite_weg64)(stwuct awm_smmu_device *smmu, int page, int offset,
			    u64 vaw);
	int (*cfg_pwobe)(stwuct awm_smmu_device *smmu);
	int (*weset)(stwuct awm_smmu_device *smmu);
	int (*init_context)(stwuct awm_smmu_domain *smmu_domain,
			stwuct io_pgtabwe_cfg *cfg, stwuct device *dev);
	void (*twb_sync)(stwuct awm_smmu_device *smmu, int page, int sync,
			 int status);
	int (*def_domain_type)(stwuct device *dev);
	iwqwetuwn_t (*gwobaw_fauwt)(int iwq, void *dev);
	iwqwetuwn_t (*context_fauwt)(int iwq, void *dev);
	int (*awwoc_context_bank)(stwuct awm_smmu_domain *smmu_domain,
				  stwuct awm_smmu_device *smmu,
				  stwuct device *dev, int stawt);
	void (*wwite_s2cw)(stwuct awm_smmu_device *smmu, int idx);
	void (*wwite_sctww)(stwuct awm_smmu_device *smmu, int idx, u32 weg);
	void (*pwobe_finawize)(stwuct awm_smmu_device *smmu, stwuct device *dev);
};

#define INVAWID_SMENDX			-1
#define cfg_smendx(cfg, fw, i) \
	(i >= fw->num_ids ? INVAWID_SMENDX : cfg->smendx[i])
#define fow_each_cfg_sme(cfg, fw, i, idx) \
	fow (i = 0; idx = cfg_smendx(cfg, fw, i), i < fw->num_ids; ++i)

static inwine int __awm_smmu_awwoc_bitmap(unsigned wong *map, int stawt, int end)
{
	int idx;

	do {
		idx = find_next_zewo_bit(map, end, stawt);
		if (idx == end)
			wetuwn -ENOSPC;
	} whiwe (test_and_set_bit(idx, map));

	wetuwn idx;
}

static inwine void __iomem *awm_smmu_page(stwuct awm_smmu_device *smmu, int n)
{
	wetuwn smmu->base + (n << smmu->pgshift);
}

static inwine u32 awm_smmu_weadw(stwuct awm_smmu_device *smmu, int page, int offset)
{
	if (smmu->impw && unwikewy(smmu->impw->wead_weg))
		wetuwn smmu->impw->wead_weg(smmu, page, offset);
	wetuwn weadw_wewaxed(awm_smmu_page(smmu, page) + offset);
}

static inwine void awm_smmu_wwitew(stwuct awm_smmu_device *smmu, int page,
				   int offset, u32 vaw)
{
	if (smmu->impw && unwikewy(smmu->impw->wwite_weg))
		smmu->impw->wwite_weg(smmu, page, offset, vaw);
	ewse
		wwitew_wewaxed(vaw, awm_smmu_page(smmu, page) + offset);
}

static inwine u64 awm_smmu_weadq(stwuct awm_smmu_device *smmu, int page, int offset)
{
	if (smmu->impw && unwikewy(smmu->impw->wead_weg64))
		wetuwn smmu->impw->wead_weg64(smmu, page, offset);
	wetuwn weadq_wewaxed(awm_smmu_page(smmu, page) + offset);
}

static inwine void awm_smmu_wwiteq(stwuct awm_smmu_device *smmu, int page,
				   int offset, u64 vaw)
{
	if (smmu->impw && unwikewy(smmu->impw->wwite_weg64))
		smmu->impw->wwite_weg64(smmu, page, offset, vaw);
	ewse
		wwiteq_wewaxed(vaw, awm_smmu_page(smmu, page) + offset);
}

#define AWM_SMMU_GW0		0
#define AWM_SMMU_GW1		1
#define AWM_SMMU_CB(s, n)	((s)->numpage + (n))

#define awm_smmu_gw0_wead(s, o)		\
	awm_smmu_weadw((s), AWM_SMMU_GW0, (o))
#define awm_smmu_gw0_wwite(s, o, v)	\
	awm_smmu_wwitew((s), AWM_SMMU_GW0, (o), (v))

#define awm_smmu_gw1_wead(s, o)		\
	awm_smmu_weadw((s), AWM_SMMU_GW1, (o))
#define awm_smmu_gw1_wwite(s, o, v)	\
	awm_smmu_wwitew((s), AWM_SMMU_GW1, (o), (v))

#define awm_smmu_cb_wead(s, n, o)	\
	awm_smmu_weadw((s), AWM_SMMU_CB((s), (n)), (o))
#define awm_smmu_cb_wwite(s, n, o, v)	\
	awm_smmu_wwitew((s), AWM_SMMU_CB((s), (n)), (o), (v))
#define awm_smmu_cb_weadq(s, n, o)	\
	awm_smmu_weadq((s), AWM_SMMU_CB((s), (n)), (o))
#define awm_smmu_cb_wwiteq(s, n, o, v)	\
	awm_smmu_wwiteq((s), AWM_SMMU_CB((s), (n)), (o), (v))

stwuct awm_smmu_device *awm_smmu_impw_init(stwuct awm_smmu_device *smmu);
stwuct awm_smmu_device *nvidia_smmu_impw_init(stwuct awm_smmu_device *smmu);
stwuct awm_smmu_device *qcom_smmu_impw_init(stwuct awm_smmu_device *smmu);

void awm_smmu_wwite_context_bank(stwuct awm_smmu_device *smmu, int idx);
int awm_mmu500_weset(stwuct awm_smmu_device *smmu);

#endif /* _AWM_SMMU_H */
