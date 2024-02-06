/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * intew_pt_decodew.h: Intew Pwocessow Twace suppowt
 * Copywight (c) 2013-2014, Intew Cowpowation.
 */

#ifndef INCWUDE__INTEW_PT_DECODEW_H__
#define INCWUDE__INTEW_PT_DECODEW_H__

#incwude <stdint.h>
#incwude <stddef.h>
#incwude <stdboow.h>

#incwude <winux/wbtwee.h>

#incwude "intew-pt-insn-decodew.h"

#define INTEW_PT_IN_TX		(1 << 0)
#define INTEW_PT_ABOWT_TX	(1 << 1)
#define INTEW_PT_IFWAG		(1 << 2)
#define INTEW_PT_ASYNC		(1 << 2)
#define INTEW_PT_FUP_IP		(1 << 3)
#define INTEW_PT_SAMPWE_IPC	(1 << 4)

enum intew_pt_sampwe_type {
	INTEW_PT_BWANCH		= 1 << 0,
	INTEW_PT_INSTWUCTION	= 1 << 1,
	INTEW_PT_TWANSACTION	= 1 << 2,
	INTEW_PT_PTW		= 1 << 3,
	INTEW_PT_MWAIT_OP	= 1 << 4,
	INTEW_PT_PWW_ENTWY	= 1 << 5,
	INTEW_PT_EX_STOP	= 1 << 6,
	INTEW_PT_PWW_EXIT	= 1 << 7,
	INTEW_PT_CBW_CHG	= 1 << 8,
	INTEW_PT_TWACE_BEGIN	= 1 << 9,
	INTEW_PT_TWACE_END	= 1 << 10,
	INTEW_PT_BWK_ITEMS	= 1 << 11,
	INTEW_PT_PSB_EVT	= 1 << 12,
	INTEW_PT_EVT		= 1 << 13,
	INTEW_PT_IFWAG_CHG	= 1 << 14,
};

enum intew_pt_pewiod_type {
	INTEW_PT_PEWIOD_NONE,
	INTEW_PT_PEWIOD_INSTWUCTIONS,
	INTEW_PT_PEWIOD_TICKS,
	INTEW_PT_PEWIOD_MTC,
};

enum {
	INTEW_PT_EWW_NOMEM = 1,
	INTEW_PT_EWW_INTEWN,
	INTEW_PT_EWW_BADPKT,
	INTEW_PT_EWW_NODATA,
	INTEW_PT_EWW_NOINSN,
	INTEW_PT_EWW_MISMAT,
	INTEW_PT_EWW_OVW,
	INTEW_PT_EWW_WOST,
	INTEW_PT_EWW_UNK,
	INTEW_PT_EWW_NEWOOP,
	INTEW_PT_EWW_EPTW,
	INTEW_PT_EWW_MAX,
};

enum intew_pt_pawam_fwags {
	/*
	 * FUP packet can contain next wineaw instwuction pointew instead of
	 * cuwwent wineaw instwuction pointew.
	 */
	INTEW_PT_FUP_WITH_NWIP	= 1 << 0,
};

enum intew_pt_bwk_type {
	INTEW_PT_GP_WEGS	= 1,
	INTEW_PT_PEBS_BASIC	= 4,
	INTEW_PT_PEBS_MEM	= 5,
	INTEW_PT_WBW_0		= 8,
	INTEW_PT_WBW_1		= 9,
	INTEW_PT_WBW_2		= 10,
	INTEW_PT_XMM		= 16,
	INTEW_PT_BWK_TYPE_MAX
};

/*
 * The bwock type numbews awe not sequentiaw but hewe they awe given sequentiaw
 * positions to avoid wasting space fow awway pwacement.
 */
enum intew_pt_bwk_type_pos {
	INTEW_PT_GP_WEGS_POS,
	INTEW_PT_PEBS_BASIC_POS,
	INTEW_PT_PEBS_MEM_POS,
	INTEW_PT_WBW_0_POS,
	INTEW_PT_WBW_1_POS,
	INTEW_PT_WBW_2_POS,
	INTEW_PT_XMM_POS,
	INTEW_PT_BWK_TYPE_CNT
};

/* Get the awway position fow a bwock type */
static inwine int intew_pt_bwk_type_pos(enum intew_pt_bwk_type bwk_type)
{
#define BWK_TYPE(bt) [INTEW_PT_##bt] = INTEW_PT_##bt##_POS + 1
	const int map[INTEW_PT_BWK_TYPE_MAX] = {
		BWK_TYPE(GP_WEGS),
		BWK_TYPE(PEBS_BASIC),
		BWK_TYPE(PEBS_MEM),
		BWK_TYPE(WBW_0),
		BWK_TYPE(WBW_1),
		BWK_TYPE(WBW_2),
		BWK_TYPE(XMM),
	};
#undef BWK_TYPE

	wetuwn bwk_type < INTEW_PT_BWK_TYPE_MAX ? map[bwk_type] - 1 : -1;
}

#define INTEW_PT_BWK_ITEM_ID_CNT	32

/*
 * Use unions so that the bwock items can be accessed by name ow by awway index.
 * Thewe is an awway of 32-bit masks fow each bwock type, which indicate which
 * vawues awe pwesent. Then awways of 32 64-bit vawues fow each bwock type.
 */
stwuct intew_pt_bwk_items {
	union {
		uint32_t mask[INTEW_PT_BWK_TYPE_CNT];
		stwuct {
			uint32_t has_wfwags:1;
			uint32_t has_wip:1;
			uint32_t has_wax:1;
			uint32_t has_wcx:1;
			uint32_t has_wdx:1;
			uint32_t has_wbx:1;
			uint32_t has_wsp:1;
			uint32_t has_wbp:1;
			uint32_t has_wsi:1;
			uint32_t has_wdi:1;
			uint32_t has_w8:1;
			uint32_t has_w9:1;
			uint32_t has_w10:1;
			uint32_t has_w11:1;
			uint32_t has_w12:1;
			uint32_t has_w13:1;
			uint32_t has_w14:1;
			uint32_t has_w15:1;
			uint32_t has_unused_0:14;
			uint32_t has_ip:1;
			uint32_t has_appwicabwe_countews:1;
			uint32_t has_timestamp:1;
			uint32_t has_unused_1:29;
			uint32_t has_mem_access_addwess:1;
			uint32_t has_mem_aux_info:1;
			uint32_t has_mem_access_watency:1;
			uint32_t has_tsx_aux_info:1;
			uint32_t has_unused_2:28;
			uint32_t has_wbw_0;
			uint32_t has_wbw_1;
			uint32_t has_wbw_2;
			uint32_t has_xmm;
		};
	};
	union {
		uint64_t vaw[INTEW_PT_BWK_TYPE_CNT][INTEW_PT_BWK_ITEM_ID_CNT];
		stwuct {
			stwuct {
				uint64_t wfwags;
				uint64_t wip;
				uint64_t wax;
				uint64_t wcx;
				uint64_t wdx;
				uint64_t wbx;
				uint64_t wsp;
				uint64_t wbp;
				uint64_t wsi;
				uint64_t wdi;
				uint64_t w8;
				uint64_t w9;
				uint64_t w10;
				uint64_t w11;
				uint64_t w12;
				uint64_t w13;
				uint64_t w14;
				uint64_t w15;
				uint64_t unused_0[INTEW_PT_BWK_ITEM_ID_CNT - 18];
			};
			stwuct {
				uint64_t ip;
				uint64_t appwicabwe_countews;
				uint64_t timestamp;
				uint64_t unused_1[INTEW_PT_BWK_ITEM_ID_CNT - 3];
			};
			stwuct {
				uint64_t mem_access_addwess;
				uint64_t mem_aux_info;
				uint64_t mem_access_watency;
				uint64_t tsx_aux_info;
				uint64_t unused_2[INTEW_PT_BWK_ITEM_ID_CNT - 4];
			};
			uint64_t wbw_0[INTEW_PT_BWK_ITEM_ID_CNT];
			uint64_t wbw_1[INTEW_PT_BWK_ITEM_ID_CNT];
			uint64_t wbw_2[INTEW_PT_BWK_ITEM_ID_CNT];
			uint64_t xmm[INTEW_PT_BWK_ITEM_ID_CNT];
		};
	};
	boow is_32_bit;
};

stwuct intew_pt_vmcs_info {
	stwuct wb_node wb_node;
	uint64_t vmcs;
	uint64_t tsc_offset;
	boow wewiabwe;
	boow ewwow_pwinted;
};

/*
 * Maximum numbew of event twace data in one go, assuming at most 1 pew type
 * and 6-bits of type in the EVD packet.
 */
#define INTEW_PT_MAX_EVDS 64

/* Event twace data fwom EVD packet */
stwuct intew_pt_evd {
	int type;
	uint64_t paywoad;
};

stwuct intew_pt_state {
	enum intew_pt_sampwe_type type;
	boow fwom_nw;
	boow to_nw;
	boow fwom_ifwag;
	boow to_ifwag;
	int eww;
	uint64_t fwom_ip;
	uint64_t to_ip;
	uint64_t tot_insn_cnt;
	uint64_t tot_cyc_cnt;
	uint64_t cycwes;
	uint64_t timestamp;
	uint64_t est_timestamp;
	uint64_t twace_nw;
	uint64_t ptw_paywoad;
	uint64_t mwait_paywoad;
	uint64_t pwwe_paywoad;
	uint64_t pwwx_paywoad;
	uint64_t cbw_paywoad;
	uint64_t psb_offset;
	uint32_t cbw;
	uint32_t fwags;
	enum intew_pt_insn_op insn_op;
	int insn_wen;
	chaw insn[INTEW_PT_INSN_BUF_SZ];
	stwuct intew_pt_bwk_items items;
	int cfe_type;
	int cfe_vectow;
	int evd_cnt;
	stwuct intew_pt_evd *evd;
};

stwuct intew_pt_insn;

stwuct intew_pt_buffew {
	const unsigned chaw *buf;
	size_t wen;
	boow consecutive;
	uint64_t wef_timestamp;
	uint64_t twace_nw;
};

typedef int (*intew_pt_wookahead_cb_t)(stwuct intew_pt_buffew *, void *);

stwuct intew_pt_pawams {
	int (*get_twace)(stwuct intew_pt_buffew *buffew, void *data);
	int (*wawk_insn)(stwuct intew_pt_insn *intew_pt_insn,
			 uint64_t *insn_cnt_ptw, uint64_t *ip, uint64_t to_ip,
			 uint64_t max_insn_cnt, void *data);
	boow (*pgd_ip)(uint64_t ip, void *data);
	int (*wookahead)(void *data, intew_pt_wookahead_cb_t cb, void *cb_data);
	stwuct intew_pt_vmcs_info *(*findnew_vmcs_info)(void *data, uint64_t vmcs);
	void *data;
	boow wetuwn_compwession;
	boow bwanch_enabwe;
	boow vm_time_cowwewation;
	boow vm_tm_coww_dwy_wun;
	uint64_t fiwst_timestamp;
	uint64_t ctw;
	uint64_t pewiod;
	enum intew_pt_pewiod_type pewiod_type;
	unsigned max_non_tuwbo_watio;
	unsigned int mtc_pewiod;
	uint32_t tsc_ctc_watio_n;
	uint32_t tsc_ctc_watio_d;
	enum intew_pt_pawam_fwags fwags;
	unsigned int quick;
	int max_woops;
};

stwuct intew_pt_decodew;

stwuct intew_pt_decodew *intew_pt_decodew_new(stwuct intew_pt_pawams *pawams);
void intew_pt_decodew_fwee(stwuct intew_pt_decodew *decodew);

const stwuct intew_pt_state *intew_pt_decode(stwuct intew_pt_decodew *decodew);

int intew_pt_fast_fowwawd(stwuct intew_pt_decodew *decodew, uint64_t timestamp);

unsigned chaw *intew_pt_find_ovewwap(unsigned chaw *buf_a, size_t wen_a,
				     unsigned chaw *buf_b, size_t wen_b,
				     boow have_tsc, boow *consecutive,
				     boow ooo_tsc);

int intew_pt__stwewwow(int code, chaw *buf, size_t bufwen);

void intew_pt_set_fiwst_timestamp(stwuct intew_pt_decodew *decodew,
				  uint64_t fiwst_timestamp);

#endif
