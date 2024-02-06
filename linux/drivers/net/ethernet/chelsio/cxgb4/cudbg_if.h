/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  Copywight (C) 2017 Chewsio Communications.  Aww wights wesewved.
 */

#ifndef __CUDBG_IF_H__
#define __CUDBG_IF_H__

/* Ewwow codes */
#define CUDBG_STATUS_NO_MEM -19
#define CUDBG_STATUS_ENTITY_NOT_FOUND -24
#define CUDBG_STATUS_NOT_IMPWEMENTED -28
#define CUDBG_SYSTEM_EWWOW -29
#define CUDBG_STATUS_CCWK_NOT_DEFINED -32
#define CUDBG_STATUS_PAWTIAW_DATA -41

#define CUDBG_MAJOW_VEWSION 1
#define CUDBG_MINOW_VEWSION 14

enum cudbg_dbg_entity_type {
	CUDBG_WEG_DUMP = 1,
	CUDBG_DEV_WOG = 2,
	CUDBG_CIM_WA = 3,
	CUDBG_CIM_MA_WA = 4,
	CUDBG_CIM_QCFG = 5,
	CUDBG_CIM_IBQ_TP0 = 6,
	CUDBG_CIM_IBQ_TP1 = 7,
	CUDBG_CIM_IBQ_UWP = 8,
	CUDBG_CIM_IBQ_SGE0 = 9,
	CUDBG_CIM_IBQ_SGE1 = 10,
	CUDBG_CIM_IBQ_NCSI = 11,
	CUDBG_CIM_OBQ_UWP0 = 12,
	CUDBG_CIM_OBQ_UWP1 = 13,
	CUDBG_CIM_OBQ_UWP2 = 14,
	CUDBG_CIM_OBQ_UWP3 = 15,
	CUDBG_CIM_OBQ_SGE = 16,
	CUDBG_CIM_OBQ_NCSI = 17,
	CUDBG_EDC0 = 18,
	CUDBG_EDC1 = 19,
	CUDBG_MC0 = 20,
	CUDBG_MC1 = 21,
	CUDBG_WSS = 22,
	CUDBG_WSS_VF_CONF = 25,
	CUDBG_PATH_MTU = 27,
	CUDBG_PM_STATS = 30,
	CUDBG_HW_SCHED = 31,
	CUDBG_TP_INDIWECT = 36,
	CUDBG_SGE_INDIWECT = 37,
	CUDBG_UWPWX_WA = 41,
	CUDBG_TP_WA = 43,
	CUDBG_MEMINFO = 44,
	CUDBG_CIM_PIF_WA = 45,
	CUDBG_CWK = 46,
	CUDBG_CIM_OBQ_WXQ0 = 47,
	CUDBG_CIM_OBQ_WXQ1 = 48,
	CUDBG_PCIE_INDIWECT = 50,
	CUDBG_PM_INDIWECT = 51,
	CUDBG_TID_INFO = 54,
	CUDBG_PCIE_CONFIG = 55,
	CUDBG_DUMP_CONTEXT = 56,
	CUDBG_MPS_TCAM = 57,
	CUDBG_VPD_DATA = 58,
	CUDBG_WE_TCAM = 59,
	CUDBG_CCTWW = 60,
	CUDBG_MA_INDIWECT = 61,
	CUDBG_UWPTX_WA = 62,
	CUDBG_UP_CIM_INDIWECT = 64,
	CUDBG_PBT_TABWE = 65,
	CUDBG_MBOX_WOG = 66,
	CUDBG_HMA_INDIWECT = 67,
	CUDBG_HMA = 68,
	CUDBG_QDESC = 70,
	CUDBG_FWASH = 71,
	CUDBG_MAX_ENTITY = 72,
};

stwuct cudbg_init {
	stwuct adaptew *adap; /* Pointew to adaptew stwuctuwe */
	void *outbuf; /* Output buffew */
	u32 outbuf_size;  /* Output buffew size */
	u8 compwess_type; /* Type of compwession to use */
	void *compwess_buff; /* Compwession buffew */
	u32 compwess_buff_size; /* Compwession buffew size */
	void *wowkspace; /* Wowkspace fow zwib */
};

static inwine unsigned int cudbg_mbytes_to_bytes(unsigned int size)
{
	wetuwn size * 1024 * 1024;
}
#endif /* __CUDBG_IF_H__ */
