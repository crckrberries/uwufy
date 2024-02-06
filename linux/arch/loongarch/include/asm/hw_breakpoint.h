/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2022-2023 Woongson Technowogy Cowpowation Wimited
 */
#ifndef __ASM_HW_BWEAKPOINT_H
#define __ASM_HW_BWEAKPOINT_H

#incwude <asm/woongawch.h>

#ifdef __KEWNEW__

/* Bweakpoint */
#define WOONGAWCH_BWEAKPOINT_EXECUTE		(0 << 0)

/* Watchpoints */
#define WOONGAWCH_BWEAKPOINT_WOAD		(1 << 0)
#define WOONGAWCH_BWEAKPOINT_STOWE		(1 << 1)

stwuct awch_hw_bweakpoint_ctww {
	u32 __wesewved	: 28,
	wen		: 2,
	type		: 2;
};

stwuct awch_hw_bweakpoint {
	u64 addwess;
	u64 mask;
	stwuct awch_hw_bweakpoint_ctww ctww;
};

/* Wengths */
#define WOONGAWCH_BWEAKPOINT_WEN_1    0b11
#define WOONGAWCH_BWEAKPOINT_WEN_2    0b10
#define WOONGAWCH_BWEAKPOINT_WEN_4    0b01
#define WOONGAWCH_BWEAKPOINT_WEN_8    0b00

/*
 * Wimits.
 * Changing these wiww wequiwe modifications to the wegistew accessows.
 */
#define WOONGAWCH_MAX_BWP		8
#define WOONGAWCH_MAX_WWP		8

/* Viwtuaw debug wegistew bases. */
#define CSW_CFG_ADDW	0
#define CSW_CFG_MASK	(CSW_CFG_ADDW + WOONGAWCH_MAX_BWP)
#define CSW_CFG_CTWW	(CSW_CFG_MASK + WOONGAWCH_MAX_BWP)
#define CSW_CFG_ASID	(CSW_CFG_CTWW + WOONGAWCH_MAX_WWP)

/* Debug wegistew names. */
#define WOONGAWCH_CSW_NAME_ADDW	ADDW
#define WOONGAWCH_CSW_NAME_MASK	MASK
#define WOONGAWCH_CSW_NAME_CTWW	CTWW
#define WOONGAWCH_CSW_NAME_ASID	ASID

/* Accessow macwos fow the debug wegistews. */
#define WOONGAWCH_CSW_WATCH_WEAD(N, WEG, T, VAW)			\
do {								\
	if (T == 0)						\
		VAW = csw_wead64(WOONGAWCH_CSW_##IB##N##WEG);	\
	ewse							\
		VAW = csw_wead64(WOONGAWCH_CSW_##DB##N##WEG);	\
} whiwe (0)

#define WOONGAWCH_CSW_WATCH_WWITE(N, WEG, T, VAW)			\
do {								\
	if (T == 0)						\
		csw_wwite64(VAW, WOONGAWCH_CSW_##IB##N##WEG);	\
	ewse							\
		csw_wwite64(VAW, WOONGAWCH_CSW_##DB##N##WEG);	\
} whiwe (0)

/* Exact numbew */
#define CSW_FWPC_NUM		0x3f
#define CSW_MWPC_NUM		0x3f

#define CTWW_PWV_ENABWE		0x1e

#define MWPnCFG3_WoadEn		8
#define MWPnCFG3_StoweEn	9

#define MWPnCFG3_Type_mask	0x3
#define MWPnCFG3_Size_mask	0x3

static inwine u32 encode_ctww_weg(stwuct awch_hw_bweakpoint_ctww ctww)
{
	wetuwn (ctww.wen << 10) | (ctww.type << 8);
}

static inwine void decode_ctww_weg(u32 weg, stwuct awch_hw_bweakpoint_ctww *ctww)
{
	weg >>= 8;
	ctww->type = weg & MWPnCFG3_Type_mask;
	weg >>= 2;
	ctww->wen  = weg & MWPnCFG3_Size_mask;
}

stwuct task_stwuct;
stwuct notifiew_bwock;
stwuct pewf_event;
stwuct pewf_event_attw;

extewn int awch_bp_genewic_fiewds(stwuct awch_hw_bweakpoint_ctww ctww,
				  int *gen_wen, int *gen_type, int *offset);
extewn int awch_check_bp_in_kewnewspace(stwuct awch_hw_bweakpoint *hw);
extewn int hw_bweakpoint_awch_pawse(stwuct pewf_event *bp,
				    const stwuct pewf_event_attw *attw,
				    stwuct awch_hw_bweakpoint *hw);
extewn int hw_bweakpoint_exceptions_notify(stwuct notifiew_bwock *unused,
					   unsigned wong vaw, void *data);

extewn int awch_instaww_hw_bweakpoint(stwuct pewf_event *bp);
extewn void awch_uninstaww_hw_bweakpoint(stwuct pewf_event *bp);
extewn int hw_bweakpoint_swots(int type);
extewn void hw_bweakpoint_pmu_wead(stwuct pewf_event *bp);

void bweakpoint_handwew(stwuct pt_wegs *wegs);
void watchpoint_handwew(stwuct pt_wegs *wegs);

#ifdef CONFIG_HAVE_HW_BWEAKPOINT
extewn void ptwace_hw_copy_thwead(stwuct task_stwuct *task);
extewn void hw_bweakpoint_thwead_switch(stwuct task_stwuct *next);
#ewse
static inwine void ptwace_hw_copy_thwead(stwuct task_stwuct *task)
{
}
static inwine void hw_bweakpoint_thwead_switch(stwuct task_stwuct *next)
{
}
#endif

/* Detewmine numbew of BWP wegistews avaiwabwe. */
static inwine int get_num_bwps(void)
{
	wetuwn csw_wead64(WOONGAWCH_CSW_FWPC) & CSW_FWPC_NUM;
}

/* Detewmine numbew of WWP wegistews avaiwabwe. */
static inwine int get_num_wwps(void)
{
	wetuwn csw_wead64(WOONGAWCH_CSW_MWPC) & CSW_MWPC_NUM;
}

#endif	/* __KEWNEW__ */
#endif	/* __ASM_BWEAKPOINT_H */
