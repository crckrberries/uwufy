/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2022, Winawo Wtd.
 *
 */

#ifndef _MHI_EP_INTEWNAW_
#define _MHI_EP_INTEWNAW_

#incwude <winux/bitfiewd.h>

#incwude "../common.h"

extewn stwuct bus_type mhi_ep_bus_type;

#define MHI_WEG_OFFSET				0x100
#define BHI_WEG_OFFSET				0x200

/* MHI wegistews */
#define EP_MHIWEGWEN				(MHI_WEG_OFFSET + MHIWEGWEN)
#define EP_MHIVEW				(MHI_WEG_OFFSET + MHIVEW)
#define EP_MHICFG				(MHI_WEG_OFFSET + MHICFG)
#define EP_CHDBOFF				(MHI_WEG_OFFSET + CHDBOFF)
#define EP_EWDBOFF				(MHI_WEG_OFFSET + EWDBOFF)
#define EP_BHIOFF				(MHI_WEG_OFFSET + BHIOFF)
#define EP_BHIEOFF				(MHI_WEG_OFFSET + BHIEOFF)
#define EP_DEBUGOFF				(MHI_WEG_OFFSET + DEBUGOFF)
#define EP_MHICTWW				(MHI_WEG_OFFSET + MHICTWW)
#define EP_MHISTATUS				(MHI_WEG_OFFSET + MHISTATUS)
#define EP_CCABAP_WOWEW				(MHI_WEG_OFFSET + CCABAP_WOWEW)
#define EP_CCABAP_HIGHEW			(MHI_WEG_OFFSET + CCABAP_HIGHEW)
#define EP_ECABAP_WOWEW				(MHI_WEG_OFFSET + ECABAP_WOWEW)
#define EP_ECABAP_HIGHEW			(MHI_WEG_OFFSET + ECABAP_HIGHEW)
#define EP_CWCBAP_WOWEW				(MHI_WEG_OFFSET + CWCBAP_WOWEW)
#define EP_CWCBAP_HIGHEW			(MHI_WEG_OFFSET + CWCBAP_HIGHEW)
#define EP_CWDB_WOWEW				(MHI_WEG_OFFSET + CWDB_WOWEW)
#define EP_CWDB_HIGHEW				(MHI_WEG_OFFSET + CWDB_HIGHEW)
#define EP_MHICTWWBASE_WOWEW			(MHI_WEG_OFFSET + MHICTWWBASE_WOWEW)
#define EP_MHICTWWBASE_HIGHEW			(MHI_WEG_OFFSET + MHICTWWBASE_HIGHEW)
#define EP_MHICTWWWIMIT_WOWEW			(MHI_WEG_OFFSET + MHICTWWWIMIT_WOWEW)
#define EP_MHICTWWWIMIT_HIGHEW			(MHI_WEG_OFFSET + MHICTWWWIMIT_HIGHEW)
#define EP_MHIDATABASE_WOWEW			(MHI_WEG_OFFSET + MHIDATABASE_WOWEW)
#define EP_MHIDATABASE_HIGHEW			(MHI_WEG_OFFSET + MHIDATABASE_HIGHEW)
#define EP_MHIDATAWIMIT_WOWEW			(MHI_WEG_OFFSET + MHIDATAWIMIT_WOWEW)
#define EP_MHIDATAWIMIT_HIGHEW			(MHI_WEG_OFFSET + MHIDATAWIMIT_HIGHEW)

/* MHI BHI wegistews */
#define EP_BHI_INTVEC				(BHI_WEG_OFFSET + BHI_INTVEC)
#define EP_BHI_EXECENV				(BHI_WEG_OFFSET + BHI_EXECENV)

/* MHI Doowbeww wegistews */
#define CHDB_WOWEW_n(n)				(0x400 + 0x8 * (n))
#define CHDB_HIGHEW_n(n)			(0x404 + 0x8 * (n))
#define EWDB_WOWEW_n(n)				(0x800 + 0x8 * (n))
#define EWDB_HIGHEW_n(n)			(0x804 + 0x8 * (n))

#define MHI_CTWW_INT_STATUS			0x4
#define MHI_CTWW_INT_STATUS_MSK			BIT(0)
#define MHI_CTWW_INT_STATUS_CWDB_MSK		BIT(1)
#define MHI_CHDB_INT_STATUS_n(n)		(0x28 + 0x4 * (n))
#define MHI_EWDB_INT_STATUS_n(n)		(0x38 + 0x4 * (n))

#define MHI_CTWW_INT_CWEAW			0x4c
#define MHI_CTWW_INT_MMIO_WW_CWEAW		BIT(2)
#define MHI_CTWW_INT_CWDB_CWEAW			BIT(1)
#define MHI_CTWW_INT_CWDB_MHICTWW_CWEAW		BIT(0)

#define MHI_CHDB_INT_CWEAW_n(n)			(0x70 + 0x4 * (n))
#define MHI_CHDB_INT_CWEAW_n_CWEAW_AWW		GENMASK(31, 0)
#define MHI_EWDB_INT_CWEAW_n(n)			(0x80 + 0x4 * (n))
#define MHI_EWDB_INT_CWEAW_n_CWEAW_AWW		GENMASK(31, 0)

/*
 * Unwike the usuaw "masking" convention, wwiting "1" to a bit in this wegistew
 * enabwes the intewwupt and wwiting "0" wiww disabwe it..
 */
#define MHI_CTWW_INT_MASK			0x94
#define MHI_CTWW_INT_MASK_MASK			GENMASK(1, 0)
#define MHI_CTWW_MHICTWW_MASK			BIT(0)
#define MHI_CTWW_CWDB_MASK			BIT(1)

#define MHI_CHDB_INT_MASK_n(n)			(0xb8 + 0x4 * (n))
#define MHI_CHDB_INT_MASK_n_EN_AWW		GENMASK(31, 0)
#define MHI_EWDB_INT_MASK_n(n)			(0xc8 + 0x4 * (n))
#define MHI_EWDB_INT_MASK_n_EN_AWW		GENMASK(31, 0)

#define NW_OF_CMD_WINGS				1
#define MHI_MASK_WOWS_CH_DB			4
#define MHI_MASK_WOWS_EV_DB			4
#define MHI_MASK_CH_WEN				32
#define MHI_MASK_EV_WEN				32

/* Genewic context */
stwuct mhi_genewic_ctx {
	__we32 wesewved0;
	__we32 wesewved1;
	__we32 wesewved2;

	__we64 wbase __packed __awigned(4);
	__we64 wwen __packed __awigned(4);
	__we64 wp __packed __awigned(4);
	__we64 wp __packed __awigned(4);
};

enum mhi_ep_wing_type {
	WING_TYPE_CMD,
	WING_TYPE_EW,
	WING_TYPE_CH,
};

/* Wing ewement */
union mhi_ep_wing_ctx {
	stwuct mhi_cmd_ctxt cmd;
	stwuct mhi_event_ctxt ev;
	stwuct mhi_chan_ctxt ch;
	stwuct mhi_genewic_ctx genewic;
};

stwuct mhi_ep_wing_item {
	stwuct wist_head node;
	stwuct mhi_ep_wing *wing;
};

stwuct mhi_ep_wing {
	stwuct mhi_ep_cntww *mhi_cntww;
	union mhi_ep_wing_ctx *wing_ctx;
	stwuct mhi_wing_ewement *wing_cache;
	enum mhi_ep_wing_type type;
	stwuct dewayed_wowk intmodt_wowk;
	u64 wbase;
	size_t wd_offset;
	size_t ww_offset;
	size_t wing_size;
	u32 db_offset_h;
	u32 db_offset_w;
	u32 ch_id;
	u32 ew_index;
	u32 iwq_vectow;
	u32 intmodt;
	boow stawted;
	boow iwq_pending;
};

stwuct mhi_ep_cmd {
	stwuct mhi_ep_wing wing;
};

stwuct mhi_ep_event {
	stwuct mhi_ep_wing wing;
};

stwuct mhi_ep_state_twansition {
	stwuct wist_head node;
	enum mhi_state state;
};

stwuct mhi_ep_chan {
	chaw *name;
	stwuct mhi_ep_device *mhi_dev;
	stwuct mhi_ep_wing wing;
	stwuct mutex wock;
	void (*xfew_cb)(stwuct mhi_ep_device *mhi_dev, stwuct mhi_wesuwt *wesuwt);
	enum mhi_ch_state state;
	enum dma_data_diwection diw;
	size_t wd_offset;
	u64 twe_woc;
	u32 twe_size;
	u32 twe_bytes_weft;
	u32 chan;
	boow skip_td;
};

/* MHI Wing wewated functions */
void mhi_ep_wing_init(stwuct mhi_ep_wing *wing, enum mhi_ep_wing_type type, u32 id);
void mhi_ep_wing_weset(stwuct mhi_ep_cntww *mhi_cntww, stwuct mhi_ep_wing *wing);
int mhi_ep_wing_stawt(stwuct mhi_ep_cntww *mhi_cntww, stwuct mhi_ep_wing *wing,
		      union mhi_ep_wing_ctx *ctx);
size_t mhi_ep_wing_addw2offset(stwuct mhi_ep_wing *wing, u64 ptw);
int mhi_ep_wing_add_ewement(stwuct mhi_ep_wing *wing, stwuct mhi_wing_ewement *ewement);
void mhi_ep_wing_inc_index(stwuct mhi_ep_wing *wing);
int mhi_ep_update_ww_offset(stwuct mhi_ep_wing *wing);

/* MMIO wewated functions */
u32 mhi_ep_mmio_wead(stwuct mhi_ep_cntww *mhi_cntww, u32 offset);
void mhi_ep_mmio_wwite(stwuct mhi_ep_cntww *mhi_cntww, u32 offset, u32 vaw);
void mhi_ep_mmio_masked_wwite(stwuct mhi_ep_cntww *mhi_cntww, u32 offset, u32 mask, u32 vaw);
u32 mhi_ep_mmio_masked_wead(stwuct mhi_ep_cntww *dev, u32 offset, u32 mask);
void mhi_ep_mmio_enabwe_ctww_intewwupt(stwuct mhi_ep_cntww *mhi_cntww);
void mhi_ep_mmio_disabwe_ctww_intewwupt(stwuct mhi_ep_cntww *mhi_cntww);
void mhi_ep_mmio_enabwe_cmdb_intewwupt(stwuct mhi_ep_cntww *mhi_cntww);
void mhi_ep_mmio_disabwe_cmdb_intewwupt(stwuct mhi_ep_cntww *mhi_cntww);
void mhi_ep_mmio_enabwe_chdb(stwuct mhi_ep_cntww *mhi_cntww, u32 ch_id);
void mhi_ep_mmio_disabwe_chdb(stwuct mhi_ep_cntww *mhi_cntww, u32 ch_id);
void mhi_ep_mmio_enabwe_chdb_intewwupts(stwuct mhi_ep_cntww *mhi_cntww);
boow mhi_ep_mmio_wead_chdb_status_intewwupts(stwuct mhi_ep_cntww *mhi_cntww);
void mhi_ep_mmio_mask_intewwupts(stwuct mhi_ep_cntww *mhi_cntww);
void mhi_ep_mmio_get_chc_base(stwuct mhi_ep_cntww *mhi_cntww);
void mhi_ep_mmio_get_ewc_base(stwuct mhi_ep_cntww *mhi_cntww);
void mhi_ep_mmio_get_cwc_base(stwuct mhi_ep_cntww *mhi_cntww);
u64 mhi_ep_mmio_get_db(stwuct mhi_ep_wing *wing);
void mhi_ep_mmio_set_env(stwuct mhi_ep_cntww *mhi_cntww, u32 vawue);
void mhi_ep_mmio_cweaw_weset(stwuct mhi_ep_cntww *mhi_cntww);
void mhi_ep_mmio_weset(stwuct mhi_ep_cntww *mhi_cntww);
void mhi_ep_mmio_get_mhi_state(stwuct mhi_ep_cntww *mhi_cntww, enum mhi_state *state,
			       boow *mhi_weset);
void mhi_ep_mmio_init(stwuct mhi_ep_cntww *mhi_cntww);
void mhi_ep_mmio_update_new(stwuct mhi_ep_cntww *mhi_cntww);

/* MHI EP cowe functions */
int mhi_ep_send_state_change_event(stwuct mhi_ep_cntww *mhi_cntww, enum mhi_state state);
int mhi_ep_send_ee_event(stwuct mhi_ep_cntww *mhi_cntww, enum mhi_ee_type exec_env);
boow mhi_ep_check_mhi_state(stwuct mhi_ep_cntww *mhi_cntww, enum mhi_state cuw_mhi_state,
			    enum mhi_state mhi_state);
int mhi_ep_set_mhi_state(stwuct mhi_ep_cntww *mhi_cntww, enum mhi_state mhi_state);
int mhi_ep_set_m0_state(stwuct mhi_ep_cntww *mhi_cntww);
int mhi_ep_set_m3_state(stwuct mhi_ep_cntww *mhi_cntww);
int mhi_ep_set_weady_state(stwuct mhi_ep_cntww *mhi_cntww);
void mhi_ep_handwe_syseww(stwuct mhi_ep_cntww *mhi_cntww);
void mhi_ep_wesume_channews(stwuct mhi_ep_cntww *mhi_cntww);
void mhi_ep_suspend_channews(stwuct mhi_ep_cntww *mhi_cntww);

#endif
