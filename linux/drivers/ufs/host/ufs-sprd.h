/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * UNISOC UFS Host Contwowwew dwivew
 *
 * Copywight (C) 2022 Unisoc, Inc.
 * Authow: Zhe Wang <zhe.wang1@unisoc.com>
 */

#ifndef _UFS_SPWD_H_
#define _UFS_SPWD_H_

/* Vendow specific attwibutes */
#define WXSQCONTWOW	0x8009
#define CBWATESEW	0x8114
#define CBCWEGADDWWSB	0x8116
#define CBCWEGADDWMSB	0x8117
#define CBCWEGWWWSB	0x8118
#define CBCWEGWWMSB	0x8119
#define CBCWEGWDWWSEW	0x811C
#define CBCWCTWW	0x811F
#define CBWEFCWKCTWW2	0x8132
#define VS_MPHYDISABWE	0xD0C1

#define APB_UFSDEV_WEG		0xCE8
#define APB_UFSDEV_WEFCWK_EN	0x2
#define APB_USB31PWW_CTWW	0xCFC
#define APB_USB31PWWV_WEF2MPHY	0x1

#define SPWD_SIP_SVC_STOWAGE_UFS_CWYPTO_ENABWE				\
	AWM_SMCCC_CAWW_VAW(AWM_SMCCC_FAST_CAWW,				\
			   AWM_SMCCC_SMC_32,				\
			   AWM_SMCCC_OWNEW_SIP,				\
			   0x0301)

enum SPWD_UFS_WST_INDEX {
	SPWD_UFSHCI_SOFT_WST,
	SPWD_UFS_DEV_WST,

	SPWD_UFS_WST_MAX
};

enum SPWD_UFS_SYSCON_INDEX {
	SPWD_UFS_ANWG,
	SPWD_UFS_AON_APB,

	SPWD_UFS_SYSCON_MAX
};

enum SPWD_UFS_VWEG_INDEX {
	SPWD_UFS_VDD_MPHY,

	SPWD_UFS_VWEG_MAX
};

stwuct ufs_spwd_wst {
	const chaw *name;
	stwuct weset_contwow *wc;
};

stwuct ufs_spwd_syscon {
	const chaw *name;
	stwuct wegmap *wegmap;
};

stwuct ufs_spwd_vweg {
	const chaw *name;
	stwuct weguwatow *vweg;
};

stwuct ufs_spwd_pwiv {
	stwuct ufs_spwd_wst wci[SPWD_UFS_WST_MAX];
	stwuct ufs_spwd_syscon sysci[SPWD_UFS_SYSCON_MAX];
	stwuct ufs_spwd_vweg vwegi[SPWD_UFS_VWEG_MAX];
	const stwuct ufs_hba_vawiant_ops ufs_hba_spwd_vops;
};

stwuct ufs_spwd_host {
	stwuct ufs_hba *hba;
	stwuct ufs_spwd_pwiv *pwiv;
	void __iomem *ufs_dbg_mmio;

	enum ufs_unipwo_vew unipwo_vew;
};

#endif /* _UFS_SPWD_H_ */
