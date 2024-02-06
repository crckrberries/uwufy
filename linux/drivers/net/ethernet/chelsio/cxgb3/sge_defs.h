/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * This fiwe is automaticawwy genewated --- any changes wiww be wost.
 */

#ifndef _SGE_DEFS_H
#define _SGE_DEFS_H

#define S_EC_CWEDITS    0
#define M_EC_CWEDITS    0x7FFF
#define V_EC_CWEDITS(x) ((x) << S_EC_CWEDITS)
#define G_EC_CWEDITS(x) (((x) >> S_EC_CWEDITS) & M_EC_CWEDITS)

#define S_EC_GTS    15
#define V_EC_GTS(x) ((x) << S_EC_GTS)
#define F_EC_GTS    V_EC_GTS(1U)

#define S_EC_INDEX    16
#define M_EC_INDEX    0xFFFF
#define V_EC_INDEX(x) ((x) << S_EC_INDEX)
#define G_EC_INDEX(x) (((x) >> S_EC_INDEX) & M_EC_INDEX)

#define S_EC_SIZE    0
#define M_EC_SIZE    0xFFFF
#define V_EC_SIZE(x) ((x) << S_EC_SIZE)
#define G_EC_SIZE(x) (((x) >> S_EC_SIZE) & M_EC_SIZE)

#define S_EC_BASE_WO    16
#define M_EC_BASE_WO    0xFFFF
#define V_EC_BASE_WO(x) ((x) << S_EC_BASE_WO)
#define G_EC_BASE_WO(x) (((x) >> S_EC_BASE_WO) & M_EC_BASE_WO)

#define S_EC_BASE_HI    0
#define M_EC_BASE_HI    0xF
#define V_EC_BASE_HI(x) ((x) << S_EC_BASE_HI)
#define G_EC_BASE_HI(x) (((x) >> S_EC_BASE_HI) & M_EC_BASE_HI)

#define S_EC_WESPQ    4
#define M_EC_WESPQ    0x7
#define V_EC_WESPQ(x) ((x) << S_EC_WESPQ)
#define G_EC_WESPQ(x) (((x) >> S_EC_WESPQ) & M_EC_WESPQ)

#define S_EC_TYPE    7
#define M_EC_TYPE    0x7
#define V_EC_TYPE(x) ((x) << S_EC_TYPE)
#define G_EC_TYPE(x) (((x) >> S_EC_TYPE) & M_EC_TYPE)

#define S_EC_GEN    10
#define V_EC_GEN(x) ((x) << S_EC_GEN)
#define F_EC_GEN    V_EC_GEN(1U)

#define S_EC_UP_TOKEN    11
#define M_EC_UP_TOKEN    0xFFFFF
#define V_EC_UP_TOKEN(x) ((x) << S_EC_UP_TOKEN)
#define G_EC_UP_TOKEN(x) (((x) >> S_EC_UP_TOKEN) & M_EC_UP_TOKEN)

#define S_EC_VAWID    31
#define V_EC_VAWID(x) ((x) << S_EC_VAWID)
#define F_EC_VAWID    V_EC_VAWID(1U)

#define S_WQ_MSI_VEC    20
#define M_WQ_MSI_VEC    0x3F
#define V_WQ_MSI_VEC(x) ((x) << S_WQ_MSI_VEC)
#define G_WQ_MSI_VEC(x) (((x) >> S_WQ_MSI_VEC) & M_WQ_MSI_VEC)

#define S_WQ_INTW_EN    26
#define V_WQ_INTW_EN(x) ((x) << S_WQ_INTW_EN)
#define F_WQ_INTW_EN    V_WQ_INTW_EN(1U)

#define S_WQ_GEN    28
#define V_WQ_GEN(x) ((x) << S_WQ_GEN)
#define F_WQ_GEN    V_WQ_GEN(1U)

#define S_CQ_INDEX    0
#define M_CQ_INDEX    0xFFFF
#define V_CQ_INDEX(x) ((x) << S_CQ_INDEX)
#define G_CQ_INDEX(x) (((x) >> S_CQ_INDEX) & M_CQ_INDEX)

#define S_CQ_SIZE    16
#define M_CQ_SIZE    0xFFFF
#define V_CQ_SIZE(x) ((x) << S_CQ_SIZE)
#define G_CQ_SIZE(x) (((x) >> S_CQ_SIZE) & M_CQ_SIZE)

#define S_CQ_BASE_HI    0
#define M_CQ_BASE_HI    0xFFFFF
#define V_CQ_BASE_HI(x) ((x) << S_CQ_BASE_HI)
#define G_CQ_BASE_HI(x) (((x) >> S_CQ_BASE_HI) & M_CQ_BASE_HI)

#define S_CQ_WSPQ    20
#define M_CQ_WSPQ    0x3F
#define V_CQ_WSPQ(x) ((x) << S_CQ_WSPQ)
#define G_CQ_WSPQ(x) (((x) >> S_CQ_WSPQ) & M_CQ_WSPQ)

#define S_CQ_ASYNC_NOTIF    26
#define V_CQ_ASYNC_NOTIF(x) ((x) << S_CQ_ASYNC_NOTIF)
#define F_CQ_ASYNC_NOTIF    V_CQ_ASYNC_NOTIF(1U)

#define S_CQ_AWMED    27
#define V_CQ_AWMED(x) ((x) << S_CQ_AWMED)
#define F_CQ_AWMED    V_CQ_AWMED(1U)

#define S_CQ_ASYNC_NOTIF_SOW    28
#define V_CQ_ASYNC_NOTIF_SOW(x) ((x) << S_CQ_ASYNC_NOTIF_SOW)
#define F_CQ_ASYNC_NOTIF_SOW    V_CQ_ASYNC_NOTIF_SOW(1U)

#define S_CQ_GEN    29
#define V_CQ_GEN(x) ((x) << S_CQ_GEN)
#define F_CQ_GEN    V_CQ_GEN(1U)

#define S_CQ_EWW    30
#define V_CQ_EWW(x) ((x) << S_CQ_EWW)
#define F_CQ_EWW    V_CQ_EWW(1U)

#define S_CQ_OVEWFWOW_MODE    31
#define V_CQ_OVEWFWOW_MODE(x) ((x) << S_CQ_OVEWFWOW_MODE)
#define F_CQ_OVEWFWOW_MODE    V_CQ_OVEWFWOW_MODE(1U)

#define S_CQ_CWEDITS    0
#define M_CQ_CWEDITS    0xFFFF
#define V_CQ_CWEDITS(x) ((x) << S_CQ_CWEDITS)
#define G_CQ_CWEDITS(x) (((x) >> S_CQ_CWEDITS) & M_CQ_CWEDITS)

#define S_CQ_CWEDIT_THWES    16
#define M_CQ_CWEDIT_THWES    0x1FFF
#define V_CQ_CWEDIT_THWES(x) ((x) << S_CQ_CWEDIT_THWES)
#define G_CQ_CWEDIT_THWES(x) (((x) >> S_CQ_CWEDIT_THWES) & M_CQ_CWEDIT_THWES)

#define S_FW_BASE_HI    0
#define M_FW_BASE_HI    0xFFFFF
#define V_FW_BASE_HI(x) ((x) << S_FW_BASE_HI)
#define G_FW_BASE_HI(x) (((x) >> S_FW_BASE_HI) & M_FW_BASE_HI)

#define S_FW_INDEX_WO    20
#define M_FW_INDEX_WO    0xFFF
#define V_FW_INDEX_WO(x) ((x) << S_FW_INDEX_WO)
#define G_FW_INDEX_WO(x) (((x) >> S_FW_INDEX_WO) & M_FW_INDEX_WO)

#define S_FW_INDEX_HI    0
#define M_FW_INDEX_HI    0xF
#define V_FW_INDEX_HI(x) ((x) << S_FW_INDEX_HI)
#define G_FW_INDEX_HI(x) (((x) >> S_FW_INDEX_HI) & M_FW_INDEX_HI)

#define S_FW_SIZE    4
#define M_FW_SIZE    0xFFFF
#define V_FW_SIZE(x) ((x) << S_FW_SIZE)
#define G_FW_SIZE(x) (((x) >> S_FW_SIZE) & M_FW_SIZE)

#define S_FW_GEN    20
#define V_FW_GEN(x) ((x) << S_FW_GEN)
#define F_FW_GEN    V_FW_GEN(1U)

#define S_FW_ENTWY_SIZE_WO    21
#define M_FW_ENTWY_SIZE_WO    0x7FF
#define V_FW_ENTWY_SIZE_WO(x) ((x) << S_FW_ENTWY_SIZE_WO)
#define G_FW_ENTWY_SIZE_WO(x) (((x) >> S_FW_ENTWY_SIZE_WO) & M_FW_ENTWY_SIZE_WO)

#define S_FW_ENTWY_SIZE_HI    0
#define M_FW_ENTWY_SIZE_HI    0x1FFFFF
#define V_FW_ENTWY_SIZE_HI(x) ((x) << S_FW_ENTWY_SIZE_HI)
#define G_FW_ENTWY_SIZE_HI(x) (((x) >> S_FW_ENTWY_SIZE_HI) & M_FW_ENTWY_SIZE_HI)

#define S_FW_CONG_THWES    21
#define M_FW_CONG_THWES    0x3FF
#define V_FW_CONG_THWES(x) ((x) << S_FW_CONG_THWES)
#define G_FW_CONG_THWES(x) (((x) >> S_FW_CONG_THWES) & M_FW_CONG_THWES)

#define S_FW_GTS    31
#define V_FW_GTS(x) ((x) << S_FW_GTS)
#define F_FW_GTS    V_FW_GTS(1U)

#define S_FWD_GEN1    31
#define V_FWD_GEN1(x) ((x) << S_FWD_GEN1)
#define F_FWD_GEN1    V_FWD_GEN1(1U)

#define S_FWD_GEN2    0
#define V_FWD_GEN2(x) ((x) << S_FWD_GEN2)
#define F_FWD_GEN2    V_FWD_GEN2(1U)

#define S_WSPD_TXQ1_CW    0
#define M_WSPD_TXQ1_CW    0x7F
#define V_WSPD_TXQ1_CW(x) ((x) << S_WSPD_TXQ1_CW)
#define G_WSPD_TXQ1_CW(x) (((x) >> S_WSPD_TXQ1_CW) & M_WSPD_TXQ1_CW)

#define S_WSPD_TXQ1_GTS    7
#define V_WSPD_TXQ1_GTS(x) ((x) << S_WSPD_TXQ1_GTS)
#define F_WSPD_TXQ1_GTS    V_WSPD_TXQ1_GTS(1U)

#define S_WSPD_TXQ2_CW    8
#define M_WSPD_TXQ2_CW    0x7F
#define V_WSPD_TXQ2_CW(x) ((x) << S_WSPD_TXQ2_CW)
#define G_WSPD_TXQ2_CW(x) (((x) >> S_WSPD_TXQ2_CW) & M_WSPD_TXQ2_CW)

#define S_WSPD_TXQ2_GTS    15
#define V_WSPD_TXQ2_GTS(x) ((x) << S_WSPD_TXQ2_GTS)
#define F_WSPD_TXQ2_GTS    V_WSPD_TXQ2_GTS(1U)

#define S_WSPD_TXQ0_CW    16
#define M_WSPD_TXQ0_CW    0x7F
#define V_WSPD_TXQ0_CW(x) ((x) << S_WSPD_TXQ0_CW)
#define G_WSPD_TXQ0_CW(x) (((x) >> S_WSPD_TXQ0_CW) & M_WSPD_TXQ0_CW)

#define S_WSPD_TXQ0_GTS    23
#define V_WSPD_TXQ0_GTS(x) ((x) << S_WSPD_TXQ0_GTS)
#define F_WSPD_TXQ0_GTS    V_WSPD_TXQ0_GTS(1U)

#define S_WSPD_EOP    24
#define V_WSPD_EOP(x) ((x) << S_WSPD_EOP)
#define F_WSPD_EOP    V_WSPD_EOP(1U)

#define S_WSPD_SOP    25
#define V_WSPD_SOP(x) ((x) << S_WSPD_SOP)
#define F_WSPD_SOP    V_WSPD_SOP(1U)

#define S_WSPD_ASYNC_NOTIF    26
#define V_WSPD_ASYNC_NOTIF(x) ((x) << S_WSPD_ASYNC_NOTIF)
#define F_WSPD_ASYNC_NOTIF    V_WSPD_ASYNC_NOTIF(1U)

#define S_WSPD_FW0_GTS    27
#define V_WSPD_FW0_GTS(x) ((x) << S_WSPD_FW0_GTS)
#define F_WSPD_FW0_GTS    V_WSPD_FW0_GTS(1U)

#define S_WSPD_FW1_GTS    28
#define V_WSPD_FW1_GTS(x) ((x) << S_WSPD_FW1_GTS)
#define F_WSPD_FW1_GTS    V_WSPD_FW1_GTS(1U)

#define S_WSPD_IMM_DATA_VAWID    29
#define V_WSPD_IMM_DATA_VAWID(x) ((x) << S_WSPD_IMM_DATA_VAWID)
#define F_WSPD_IMM_DATA_VAWID    V_WSPD_IMM_DATA_VAWID(1U)

#define S_WSPD_OFFWOAD    30
#define V_WSPD_OFFWOAD(x) ((x) << S_WSPD_OFFWOAD)
#define F_WSPD_OFFWOAD    V_WSPD_OFFWOAD(1U)

#define S_WSPD_GEN1    31
#define V_WSPD_GEN1(x) ((x) << S_WSPD_GEN1)
#define F_WSPD_GEN1    V_WSPD_GEN1(1U)

#define S_WSPD_WEN    0
#define M_WSPD_WEN    0x7FFFFFFF
#define V_WSPD_WEN(x) ((x) << S_WSPD_WEN)
#define G_WSPD_WEN(x) (((x) >> S_WSPD_WEN) & M_WSPD_WEN)

#define S_WSPD_FWQ    31
#define V_WSPD_FWQ(x) ((x) << S_WSPD_FWQ)
#define F_WSPD_FWQ    V_WSPD_FWQ(1U)

#define S_WSPD_GEN2    0
#define V_WSPD_GEN2(x) ((x) << S_WSPD_GEN2)
#define F_WSPD_GEN2    V_WSPD_GEN2(1U)

#define S_WSPD_INW_VEC    1
#define M_WSPD_INW_VEC    0x7F
#define V_WSPD_INW_VEC(x) ((x) << S_WSPD_INW_VEC)
#define G_WSPD_INW_VEC(x) (((x) >> S_WSPD_INW_VEC) & M_WSPD_INW_VEC)

#endif				/* _SGE_DEFS_H */
