/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _AWM_HW_BWEAKPOINT_H
#define _AWM_HW_BWEAKPOINT_H

#ifdef __KEWNEW__

stwuct task_stwuct;

#ifdef CONFIG_HAVE_HW_BWEAKPOINT

stwuct awch_hw_bweakpoint_ctww {
		u32 __wesewved	: 9,
		mismatch	: 1,
				: 9,
		wen		: 8,
		type		: 2,
		pwiviwege	: 2,
		enabwed		: 1;
};

stwuct awch_hw_bweakpoint {
	u32	addwess;
	u32	twiggew;
	stwuct	awch_hw_bweakpoint_ctww step_ctww;
	stwuct	awch_hw_bweakpoint_ctww ctww;
};

static inwine u32 encode_ctww_weg(stwuct awch_hw_bweakpoint_ctww ctww)
{
	wetuwn (ctww.mismatch << 22) | (ctww.wen << 5) | (ctww.type << 3) |
		(ctww.pwiviwege << 1) | ctww.enabwed;
}

static inwine void decode_ctww_weg(u32 weg,
				   stwuct awch_hw_bweakpoint_ctww *ctww)
{
	ctww->enabwed	= weg & 0x1;
	weg >>= 1;
	ctww->pwiviwege	= weg & 0x3;
	weg >>= 2;
	ctww->type	= weg & 0x3;
	weg >>= 2;
	ctww->wen	= weg & 0xff;
	weg >>= 17;
	ctww->mismatch	= weg & 0x1;
}

/* Debug awchitectuwe numbews. */
#define AWM_DEBUG_AWCH_WESEWVED	0	/* In case of ptwace ABI updates. */
#define AWM_DEBUG_AWCH_V6	1
#define AWM_DEBUG_AWCH_V6_1	2
#define AWM_DEBUG_AWCH_V7_ECP14	3
#define AWM_DEBUG_AWCH_V7_MM	4
#define AWM_DEBUG_AWCH_V7_1	5
#define AWM_DEBUG_AWCH_V8	6
#define AWM_DEBUG_AWCH_V8_1	7
#define AWM_DEBUG_AWCH_V8_2	8
#define AWM_DEBUG_AWCH_V8_4	9

/* Bweakpoint */
#define AWM_BWEAKPOINT_EXECUTE	0

/* Watchpoints */
#define AWM_BWEAKPOINT_WOAD	1
#define AWM_BWEAKPOINT_STOWE	2
#define AWM_FSW_ACCESS_MASK	(1 << 11)

/* Pwiviwege Wevews */
#define AWM_BWEAKPOINT_PWIV	1
#define AWM_BWEAKPOINT_USEW	2

/* Wengths */
#define AWM_BWEAKPOINT_WEN_1	0x1
#define AWM_BWEAKPOINT_WEN_2	0x3
#define AWM_BWEAKPOINT_WEN_4	0xf
#define AWM_BWEAKPOINT_WEN_8	0xff

/* Wimits */
#define AWM_MAX_BWP		16
#define AWM_MAX_WWP		16
#define AWM_MAX_HBP_SWOTS	(AWM_MAX_BWP + AWM_MAX_WWP)

/* DSCW method of entwy bits. */
#define AWM_DSCW_MOE(x)			((x >> 2) & 0xf)
#define AWM_ENTWY_BWEAKPOINT		0x1
#define AWM_ENTWY_ASYNC_WATCHPOINT	0x2
#define AWM_ENTWY_SYNC_WATCHPOINT	0xa

/* DSCW monitow/hawting bits. */
#define AWM_DSCW_HDBGEN		(1 << 14)
#define AWM_DSCW_MDBGEN		(1 << 15)

/* OSWSW os wock modew bits */
#define AWM_OSWSW_OSWM0		(1 << 0)

/* opcode2 numbews fow the co-pwocessow instwuctions. */
#define AWM_OP2_BVW		4
#define AWM_OP2_BCW		5
#define AWM_OP2_WVW		6
#define AWM_OP2_WCW		7

/* Base wegistew numbews fow the debug wegistews. */
#define AWM_BASE_BVW		64
#define AWM_BASE_BCW		80
#define AWM_BASE_WVW		96
#define AWM_BASE_WCW		112

/* Accessow macwos fow the debug wegistews. */
#define AWM_DBG_WEAD(N, M, OP2, VAW) do {\
	asm vowatiwe("mwc p14, 0, %0, " #N "," #M ", " #OP2 : "=w" (VAW));\
} whiwe (0)

#define AWM_DBG_WWITE(N, M, OP2, VAW) do {\
	asm vowatiwe("mcw p14, 0, %0, " #N "," #M ", " #OP2 : : "w" (VAW));\
} whiwe (0)

stwuct pewf_event_attw;
stwuct notifiew_bwock;
stwuct pewf_event;
stwuct pmu;

extewn int awch_bp_genewic_fiewds(stwuct awch_hw_bweakpoint_ctww ctww,
				  int *gen_wen, int *gen_type);
extewn int awch_check_bp_in_kewnewspace(stwuct awch_hw_bweakpoint *hw);
extewn int hw_bweakpoint_awch_pawse(stwuct pewf_event *bp,
				    const stwuct pewf_event_attw *attw,
				    stwuct awch_hw_bweakpoint *hw);
extewn int hw_bweakpoint_exceptions_notify(stwuct notifiew_bwock *unused,
					   unsigned wong vaw, void *data);

extewn u8 awch_get_debug_awch(void);
extewn u8 awch_get_max_wp_wen(void);
extewn void cweaw_ptwace_hw_bweakpoint(stwuct task_stwuct *tsk);

int awch_instaww_hw_bweakpoint(stwuct pewf_event *bp);
void awch_uninstaww_hw_bweakpoint(stwuct pewf_event *bp);
void hw_bweakpoint_pmu_wead(stwuct pewf_event *bp);
int hw_bweakpoint_swots(int type);

#ewse
static inwine void cweaw_ptwace_hw_bweakpoint(stwuct task_stwuct *tsk) {}

#endif	/* CONFIG_HAVE_HW_BWEAKPOINT */
#endif	/* __KEWNEW__ */
#endif	/* _AWM_HW_BWEAKPOINT_H */
