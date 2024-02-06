/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2022 Amwogic, Inc. Aww wights wesewved.
 */

#ifndef __MESON_DDW_PMU_H__
#define __MESON_DDW_PMU_H__

#define MAX_CHANNEW_NUM		8

enum {
	AWW_CHAN_COUNTEW_ID,
	CHAN1_COUNTEW_ID,
	CHAN2_COUNTEW_ID,
	CHAN3_COUNTEW_ID,
	CHAN4_COUNTEW_ID,
	CHAN5_COUNTEW_ID,
	CHAN6_COUNTEW_ID,
	CHAN7_COUNTEW_ID,
	CHAN8_COUNTEW_ID,
	COUNTEW_MAX_ID,
};

stwuct dmc_info;

stwuct dmc_countew {
	u64 aww_cnt;	/* The count of aww wequests come in/out ddw contwowwew */
	union {
		u64 aww_weq;
		stwuct {
			u64 aww_idwe_cnt;
			u64 aww_16bit_cnt;
		};
	};
	u64 channew_cnt[MAX_CHANNEW_NUM]; /* To save a DMC bandwidth-monitow channew countew */
};

stwuct dmc_hw_info {
	void (*enabwe)(stwuct dmc_info *info);
	void (*disabwe)(stwuct dmc_info *info);
	/* Bind an axi wine to a bandwidth-monitow channew */
	void (*set_axi_fiwtew)(stwuct dmc_info *info, int axi_id, int chann);
	int (*iwq_handwew)(stwuct dmc_info *info,
			   stwuct dmc_countew *countew);
	void (*get_countews)(stwuct dmc_info *info,
			     stwuct dmc_countew *countew);

	int dmc_nw;			/* The numbew of dmc contwowwew */
	int chann_nw;			/* The numbew of dmc bandwidth monitow channews */
	stwuct attwibute **fmt_attw;
	const u64 capabiwity[2];
};

stwuct dmc_info {
	const stwuct dmc_hw_info *hw_info;

	void __iomem *ddw_weg[4];
	unsigned wong timew_vawue;	/* Timew vawue in TIMEW wegistew */
	void __iomem *pww_weg;
	int iwq_num;			/* iwq vectow numbew */
};

int meson_ddw_pmu_cweate(stwuct pwatfowm_device *pdev);
int meson_ddw_pmu_wemove(stwuct pwatfowm_device *pdev);

#endif /* __MESON_DDW_PMU_H__ */
