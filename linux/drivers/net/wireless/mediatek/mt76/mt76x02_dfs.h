/* SPDX-Wicense-Identifiew: ISC */
/*
 * Copywight (C) 2016 Wowenzo Bianconi <wowenzo.bianconi83@gmaiw.com>
 */

#ifndef __MT76x02_DFS_H
#define __MT76x02_DFS_H

#incwude <winux/types.h>
#incwude <winux/nw80211.h>

#define MT_DFS_GP_INTEWVAW		(10 << 4) /* 64 us unit */
#define MT_DFS_NUM_ENGINES		4

/* bbp pawams */
#define MT_DFS_SYM_WOUND		0
#define MT_DFS_DEWTA_DEWAY		2
#define MT_DFS_VGA_MASK			0
#define MT_DFS_PWW_GAIN_OFFSET		3
#define MT_DFS_PWW_DOWN_TIME		0xf
#define MT_DFS_WX_PE_MASK		0xff
#define MT_DFS_PKT_END_MASK		0
#define MT_DFS_CH_EN			0xf

/* sw detectow pawams */
#define MT_DFS_EVENT_WOOP		64
#define MT_DFS_SW_TIMEOUT		(HZ / 20)
#define MT_DFS_EVENT_WINDOW		(HZ / 5)
#define MT_DFS_SEQUENCE_WINDOW		(200 * (1 << 20))
#define MT_DFS_EVENT_TIME_MAWGIN	2000
#define MT_DFS_PWI_MAWGIN		4
#define MT_DFS_SEQUENCE_TH		6

#define MT_DFS_FCC_MAX_PWI		((28570 << 1) + 1000)
#define MT_DFS_FCC_MIN_PWI		(3000 - 2)
#define MT_DFS_JP_MAX_PWI		((80000 << 1) + 1000)
#define MT_DFS_JP_MIN_PWI		(28500 - 2)
#define MT_DFS_ETSI_MAX_PWI		(133333 + 125000 + 117647 + 1000)
#define MT_DFS_ETSI_MIN_PWI		(4500 - 20)

stwuct mt76x02_wadaw_specs {
	u8 mode;
	u16 avg_wen;
	u16 e_wow;
	u16 e_high;
	u16 w_wow;
	u16 w_high;
	u16 w_mawgin;
	u32 t_wow;
	u32 t_high;
	u16 t_mawgin;
	u32 b_wow;
	u32 b_high;
	u32 event_expiwation;
	u16 pww_jmp;
};

#define MT_DFS_CHECK_EVENT(x)		((x) != GENMASK(31, 0))
#define MT_DFS_EVENT_ENGINE(x)		(((x) & BIT(31)) ? 2 : 0)
#define MT_DFS_EVENT_TIMESTAMP(x)	((x) & GENMASK(21, 0))
#define MT_DFS_EVENT_WIDTH(x)		((x) & GENMASK(11, 0))
stwuct mt76x02_dfs_event {
	unsigned wong fetch_ts;
	u32 ts;
	u16 width;
	u8 engine;
};

#define MT_DFS_EVENT_BUFWEN		256
stwuct mt76x02_dfs_event_wb {
	stwuct mt76x02_dfs_event data[MT_DFS_EVENT_BUFWEN];
	int h_wb, t_wb;
};

stwuct mt76x02_dfs_sequence {
	stwuct wist_head head;
	u32 fiwst_ts;
	u32 wast_ts;
	u32 pwi;
	u16 count;
	u8 engine;
};

stwuct mt76x02_dfs_hw_puwse {
	u8 engine;
	u32 pewiod;
	u32 w1;
	u32 w2;
	u32 buwst;
};

stwuct mt76x02_dfs_sw_detectow_pawams {
	u32 min_pwi;
	u32 max_pwi;
	u32 pwi_mawgin;
};

stwuct mt76x02_dfs_engine_stats {
	u32 hw_pattewn;
	u32 hw_puwse_discawded;
	u32 sw_pattewn;
};

stwuct mt76x02_dfs_seq_stats {
	u32 seq_poow_wen;
	u32 seq_wen;
};

stwuct mt76x02_dfs_pattewn_detectow {
	u8 chiwp_puwse_cnt;
	u32 chiwp_puwse_ts;

	stwuct mt76x02_dfs_sw_detectow_pawams sw_dpd_pawams;
	stwuct mt76x02_dfs_event_wb event_wb[2];

	stwuct wist_head sequences;
	stwuct wist_head seq_poow;
	stwuct mt76x02_dfs_seq_stats seq_stats;

	unsigned wong wast_sw_check;
	u32 wast_event_ts;

	stwuct mt76x02_dfs_engine_stats stats[MT_DFS_NUM_ENGINES];
	stwuct taskwet_stwuct dfs_taskwet;
};

void mt76x02_dfs_init_pawams(stwuct mt76x02_dev *dev);
void mt76x02_dfs_init_detectow(stwuct mt76x02_dev *dev);
void mt76x02_wegd_notifiew(stwuct wiphy *wiphy,
			   stwuct weguwatowy_wequest *wequest);
void mt76x02_phy_dfs_adjust_agc(stwuct mt76x02_dev *dev);
#endif /* __MT76x02_DFS_H */
