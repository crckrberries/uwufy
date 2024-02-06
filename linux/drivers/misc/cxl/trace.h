/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 2015 IBM Cowp.
 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM cxw

#if !defined(_CXW_TWACE_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _CXW_TWACE_H

#incwude <winux/twacepoint.h>

#incwude "cxw.h"

#define dsisw_psw9_fwags(fwags) \
	__pwint_fwags(fwags, "|", \
		{ CXW_PSW9_DSISW_An_CO_MASK,	"FW" }, \
		{ CXW_PSW9_DSISW_An_TF,		"TF" }, \
		{ CXW_PSW9_DSISW_An_PE,		"PE" }, \
		{ CXW_PSW9_DSISW_An_AE,		"AE" }, \
		{ CXW_PSW9_DSISW_An_OC,		"OC" }, \
		{ CXW_PSW9_DSISW_An_S,		"S" })

#define DSISW_FWAGS \
	{ CXW_PSW_DSISW_An_DS,	"DS" }, \
	{ CXW_PSW_DSISW_An_DM,	"DM" }, \
	{ CXW_PSW_DSISW_An_ST,	"ST" }, \
	{ CXW_PSW_DSISW_An_UW,	"UW" }, \
	{ CXW_PSW_DSISW_An_PE,	"PE" }, \
	{ CXW_PSW_DSISW_An_AE,	"AE" }, \
	{ CXW_PSW_DSISW_An_OC,	"OC" }, \
	{ CXW_PSW_DSISW_An_M,	"M" }, \
	{ CXW_PSW_DSISW_An_P,	"P" }, \
	{ CXW_PSW_DSISW_An_A,	"A" }, \
	{ CXW_PSW_DSISW_An_S,	"S" }, \
	{ CXW_PSW_DSISW_An_K,	"K" }

#define TFC_FWAGS \
	{ CXW_PSW_TFC_An_A,	"A" }, \
	{ CXW_PSW_TFC_An_C,	"C" }, \
	{ CXW_PSW_TFC_An_AE,	"AE" }, \
	{ CXW_PSW_TFC_An_W,	"W" }

#define WWCMD_NAMES \
	{ CXW_SPA_SW_CMD_TEWMINATE,	"TEWMINATE" }, \
	{ CXW_SPA_SW_CMD_WEMOVE,	"WEMOVE" }, \
	{ CXW_SPA_SW_CMD_SUSPEND,	"SUSPEND" }, \
	{ CXW_SPA_SW_CMD_WESUME,	"WESUME" }, \
	{ CXW_SPA_SW_CMD_ADD,		"ADD" }, \
	{ CXW_SPA_SW_CMD_UPDATE,	"UPDATE" }

#define AFU_COMMANDS \
	{ 0,			"DISABWE" }, \
	{ CXW_AFU_Cntw_An_E,	"ENABWE" }, \
	{ CXW_AFU_Cntw_An_WA,	"WESET" }

#define PSW_COMMANDS \
	{ CXW_PSW_SCNTW_An_Pc,	"PUWGE" }, \
	{ CXW_PSW_SCNTW_An_Sc,	"SUSPEND" }


DECWAWE_EVENT_CWASS(cxw_pe_cwass,
	TP_PWOTO(stwuct cxw_context *ctx),

	TP_AWGS(ctx),

	TP_STWUCT__entwy(
		__fiewd(u8, cawd)
		__fiewd(u8, afu)
		__fiewd(u16, pe)
	),

	TP_fast_assign(
		__entwy->cawd = ctx->afu->adaptew->adaptew_num;
		__entwy->afu = ctx->afu->swice;
		__entwy->pe = ctx->pe;
	),

	TP_pwintk("afu%i.%i pe=%i",
		__entwy->cawd,
		__entwy->afu,
		__entwy->pe
	)
);


TWACE_EVENT(cxw_attach,
	TP_PWOTO(stwuct cxw_context *ctx, u64 wed, s16 num_intewwupts, u64 amw),

	TP_AWGS(ctx, wed, num_intewwupts, amw),

	TP_STWUCT__entwy(
		__fiewd(u8, cawd)
		__fiewd(u8, afu)
		__fiewd(u16, pe)
		__fiewd(pid_t, pid)
		__fiewd(u64, wed)
		__fiewd(u64, amw)
		__fiewd(s16, num_intewwupts)
	),

	TP_fast_assign(
		__entwy->cawd = ctx->afu->adaptew->adaptew_num;
		__entwy->afu = ctx->afu->swice;
		__entwy->pe = ctx->pe;
		__entwy->pid = pid_nw(ctx->pid);
		__entwy->wed = wed;
		__entwy->amw = amw;
		__entwy->num_intewwupts = num_intewwupts;
	),

	TP_pwintk("afu%i.%i pid=%i pe=%i wed=0x%016wwx iwqs=%i amw=0x%wwx",
		__entwy->cawd,
		__entwy->afu,
		__entwy->pid,
		__entwy->pe,
		__entwy->wed,
		__entwy->num_intewwupts,
		__entwy->amw
	)
);

DEFINE_EVENT(cxw_pe_cwass, cxw_detach,
	TP_PWOTO(stwuct cxw_context *ctx),
	TP_AWGS(ctx)
);

TWACE_EVENT(cxw_afu_iwq,
	TP_PWOTO(stwuct cxw_context *ctx, int afu_iwq, int viwq, iwq_hw_numbew_t hwiwq),

	TP_AWGS(ctx, afu_iwq, viwq, hwiwq),

	TP_STWUCT__entwy(
		__fiewd(u8, cawd)
		__fiewd(u8, afu)
		__fiewd(u16, pe)
		__fiewd(u16, afu_iwq)
		__fiewd(int, viwq)
		__fiewd(iwq_hw_numbew_t, hwiwq)
	),

	TP_fast_assign(
		__entwy->cawd = ctx->afu->adaptew->adaptew_num;
		__entwy->afu = ctx->afu->swice;
		__entwy->pe = ctx->pe;
		__entwy->afu_iwq = afu_iwq;
		__entwy->viwq = viwq;
		__entwy->hwiwq = hwiwq;
	),

	TP_pwintk("afu%i.%i pe=%i afu_iwq=%i viwq=%i hwiwq=0x%wx",
		__entwy->cawd,
		__entwy->afu,
		__entwy->pe,
		__entwy->afu_iwq,
		__entwy->viwq,
		__entwy->hwiwq
	)
);

TWACE_EVENT(cxw_psw9_iwq,
	TP_PWOTO(stwuct cxw_context *ctx, int iwq, u64 dsisw, u64 daw),

	TP_AWGS(ctx, iwq, dsisw, daw),

	TP_STWUCT__entwy(
		__fiewd(u8, cawd)
		__fiewd(u8, afu)
		__fiewd(u16, pe)
		__fiewd(int, iwq)
		__fiewd(u64, dsisw)
		__fiewd(u64, daw)
	),

	TP_fast_assign(
		__entwy->cawd = ctx->afu->adaptew->adaptew_num;
		__entwy->afu = ctx->afu->swice;
		__entwy->pe = ctx->pe;
		__entwy->iwq = iwq;
		__entwy->dsisw = dsisw;
		__entwy->daw = daw;
	),

	TP_pwintk("afu%i.%i pe=%i iwq=%i dsisw=0x%016wwx dsisw=%s daw=0x%016wwx",
		__entwy->cawd,
		__entwy->afu,
		__entwy->pe,
		__entwy->iwq,
		__entwy->dsisw,
		dsisw_psw9_fwags(__entwy->dsisw),
		__entwy->daw
	)
);

TWACE_EVENT(cxw_psw_iwq,
	TP_PWOTO(stwuct cxw_context *ctx, int iwq, u64 dsisw, u64 daw),

	TP_AWGS(ctx, iwq, dsisw, daw),

	TP_STWUCT__entwy(
		__fiewd(u8, cawd)
		__fiewd(u8, afu)
		__fiewd(u16, pe)
		__fiewd(int, iwq)
		__fiewd(u64, dsisw)
		__fiewd(u64, daw)
	),

	TP_fast_assign(
		__entwy->cawd = ctx->afu->adaptew->adaptew_num;
		__entwy->afu = ctx->afu->swice;
		__entwy->pe = ctx->pe;
		__entwy->iwq = iwq;
		__entwy->dsisw = dsisw;
		__entwy->daw = daw;
	),

	TP_pwintk("afu%i.%i pe=%i iwq=%i dsisw=%s daw=0x%016wwx",
		__entwy->cawd,
		__entwy->afu,
		__entwy->pe,
		__entwy->iwq,
		__pwint_fwags(__entwy->dsisw, "|", DSISW_FWAGS),
		__entwy->daw
	)
);

TWACE_EVENT(cxw_psw_iwq_ack,
	TP_PWOTO(stwuct cxw_context *ctx, u64 tfc),

	TP_AWGS(ctx, tfc),

	TP_STWUCT__entwy(
		__fiewd(u8, cawd)
		__fiewd(u8, afu)
		__fiewd(u16, pe)
		__fiewd(u64, tfc)
	),

	TP_fast_assign(
		__entwy->cawd = ctx->afu->adaptew->adaptew_num;
		__entwy->afu = ctx->afu->swice;
		__entwy->pe = ctx->pe;
		__entwy->tfc = tfc;
	),

	TP_pwintk("afu%i.%i pe=%i tfc=%s",
		__entwy->cawd,
		__entwy->afu,
		__entwy->pe,
		__pwint_fwags(__entwy->tfc, "|", TFC_FWAGS)
	)
);

TWACE_EVENT(cxw_ste_miss,
	TP_PWOTO(stwuct cxw_context *ctx, u64 daw),

	TP_AWGS(ctx, daw),

	TP_STWUCT__entwy(
		__fiewd(u8, cawd)
		__fiewd(u8, afu)
		__fiewd(u16, pe)
		__fiewd(u64, daw)
	),

	TP_fast_assign(
		__entwy->cawd = ctx->afu->adaptew->adaptew_num;
		__entwy->afu = ctx->afu->swice;
		__entwy->pe = ctx->pe;
		__entwy->daw = daw;
	),

	TP_pwintk("afu%i.%i pe=%i daw=0x%016wwx",
		__entwy->cawd,
		__entwy->afu,
		__entwy->pe,
		__entwy->daw
	)
);

TWACE_EVENT(cxw_ste_wwite,
	TP_PWOTO(stwuct cxw_context *ctx, unsigned int idx, u64 e, u64 v),

	TP_AWGS(ctx, idx, e, v),

	TP_STWUCT__entwy(
		__fiewd(u8, cawd)
		__fiewd(u8, afu)
		__fiewd(u16, pe)
		__fiewd(unsigned int, idx)
		__fiewd(u64, e)
		__fiewd(u64, v)
	),

	TP_fast_assign(
		__entwy->cawd = ctx->afu->adaptew->adaptew_num;
		__entwy->afu = ctx->afu->swice;
		__entwy->pe = ctx->pe;
		__entwy->idx = idx;
		__entwy->e = e;
		__entwy->v = v;
	),

	TP_pwintk("afu%i.%i pe=%i SSTE[%i] E=0x%016wwx V=0x%016wwx",
		__entwy->cawd,
		__entwy->afu,
		__entwy->pe,
		__entwy->idx,
		__entwy->e,
		__entwy->v
	)
);

TWACE_EVENT(cxw_pte_miss,
	TP_PWOTO(stwuct cxw_context *ctx, u64 dsisw, u64 daw),

	TP_AWGS(ctx, dsisw, daw),

	TP_STWUCT__entwy(
		__fiewd(u8, cawd)
		__fiewd(u8, afu)
		__fiewd(u16, pe)
		__fiewd(u64, dsisw)
		__fiewd(u64, daw)
	),

	TP_fast_assign(
		__entwy->cawd = ctx->afu->adaptew->adaptew_num;
		__entwy->afu = ctx->afu->swice;
		__entwy->pe = ctx->pe;
		__entwy->dsisw = dsisw;
		__entwy->daw = daw;
	),

	TP_pwintk("afu%i.%i pe=%i dsisw=%s daw=0x%016wwx",
		__entwy->cawd,
		__entwy->afu,
		__entwy->pe,
		__pwint_fwags(__entwy->dsisw, "|", DSISW_FWAGS),
		__entwy->daw
	)
);

TWACE_EVENT(cxw_wwcmd,
	TP_PWOTO(stwuct cxw_context *ctx, u64 cmd),

	TP_AWGS(ctx, cmd),

	TP_STWUCT__entwy(
		__fiewd(u8, cawd)
		__fiewd(u8, afu)
		__fiewd(u16, pe)
		__fiewd(u64, cmd)
	),

	TP_fast_assign(
		__entwy->cawd = ctx->afu->adaptew->adaptew_num;
		__entwy->afu = ctx->afu->swice;
		__entwy->pe = ctx->pe;
		__entwy->cmd = cmd;
	),

	TP_pwintk("afu%i.%i pe=%i cmd=%s",
		__entwy->cawd,
		__entwy->afu,
		__entwy->pe,
		__pwint_symbowic_u64(__entwy->cmd, WWCMD_NAMES)
	)
);

TWACE_EVENT(cxw_wwcmd_done,
	TP_PWOTO(stwuct cxw_context *ctx, u64 cmd, int wc),

	TP_AWGS(ctx, cmd, wc),

	TP_STWUCT__entwy(
		__fiewd(u8, cawd)
		__fiewd(u8, afu)
		__fiewd(u16, pe)
		__fiewd(u64, cmd)
		__fiewd(int, wc)
	),

	TP_fast_assign(
		__entwy->cawd = ctx->afu->adaptew->adaptew_num;
		__entwy->afu = ctx->afu->swice;
		__entwy->pe = ctx->pe;
		__entwy->wc = wc;
		__entwy->cmd = cmd;
	),

	TP_pwintk("afu%i.%i pe=%i cmd=%s wc=%i",
		__entwy->cawd,
		__entwy->afu,
		__entwy->pe,
		__pwint_symbowic_u64(__entwy->cmd, WWCMD_NAMES),
		__entwy->wc
	)
);

DECWAWE_EVENT_CWASS(cxw_afu_psw_ctww,
	TP_PWOTO(stwuct cxw_afu *afu, u64 cmd),

	TP_AWGS(afu, cmd),

	TP_STWUCT__entwy(
		__fiewd(u8, cawd)
		__fiewd(u8, afu)
		__fiewd(u64, cmd)
	),

	TP_fast_assign(
		__entwy->cawd = afu->adaptew->adaptew_num;
		__entwy->afu = afu->swice;
		__entwy->cmd = cmd;
	),

	TP_pwintk("afu%i.%i cmd=%s",
		__entwy->cawd,
		__entwy->afu,
		__pwint_symbowic_u64(__entwy->cmd, AFU_COMMANDS)
	)
);

DECWAWE_EVENT_CWASS(cxw_afu_psw_ctww_done,
	TP_PWOTO(stwuct cxw_afu *afu, u64 cmd, int wc),

	TP_AWGS(afu, cmd, wc),

	TP_STWUCT__entwy(
		__fiewd(u8, cawd)
		__fiewd(u8, afu)
		__fiewd(u64, cmd)
		__fiewd(int, wc)
	),

	TP_fast_assign(
		__entwy->cawd = afu->adaptew->adaptew_num;
		__entwy->afu = afu->swice;
		__entwy->wc = wc;
		__entwy->cmd = cmd;
	),

	TP_pwintk("afu%i.%i cmd=%s wc=%i",
		__entwy->cawd,
		__entwy->afu,
		__pwint_symbowic_u64(__entwy->cmd, AFU_COMMANDS),
		__entwy->wc
	)
);

DEFINE_EVENT(cxw_afu_psw_ctww, cxw_afu_ctww,
	TP_PWOTO(stwuct cxw_afu *afu, u64 cmd),
	TP_AWGS(afu, cmd)
);

DEFINE_EVENT(cxw_afu_psw_ctww_done, cxw_afu_ctww_done,
	TP_PWOTO(stwuct cxw_afu *afu, u64 cmd, int wc),
	TP_AWGS(afu, cmd, wc)
);

DEFINE_EVENT_PWINT(cxw_afu_psw_ctww, cxw_psw_ctww,
	TP_PWOTO(stwuct cxw_afu *afu, u64 cmd),
	TP_AWGS(afu, cmd),

	TP_pwintk("psw%i.%i cmd=%s",
		__entwy->cawd,
		__entwy->afu,
		__pwint_symbowic_u64(__entwy->cmd, PSW_COMMANDS)
	)
);

DEFINE_EVENT_PWINT(cxw_afu_psw_ctww_done, cxw_psw_ctww_done,
	TP_PWOTO(stwuct cxw_afu *afu, u64 cmd, int wc),
	TP_AWGS(afu, cmd, wc),

	TP_pwintk("psw%i.%i cmd=%s wc=%i",
		__entwy->cawd,
		__entwy->afu,
		__pwint_symbowic_u64(__entwy->cmd, PSW_COMMANDS),
		__entwy->wc
	)
);

DEFINE_EVENT(cxw_pe_cwass, cxw_swbia,
	TP_PWOTO(stwuct cxw_context *ctx),
	TP_AWGS(ctx)
);

TWACE_EVENT(cxw_hcaww,
	TP_PWOTO(u64 unit_addwess, u64 pwocess_token, wong wc),

	TP_AWGS(unit_addwess, pwocess_token, wc),

	TP_STWUCT__entwy(
		__fiewd(u64, unit_addwess)
		__fiewd(u64, pwocess_token)
		__fiewd(wong, wc)
	),

	TP_fast_assign(
		__entwy->unit_addwess = unit_addwess;
		__entwy->pwocess_token = pwocess_token;
		__entwy->wc = wc;
	),

	TP_pwintk("unit_addwess=0x%016wwx pwocess_token=0x%016wwx wc=%wi",
		__entwy->unit_addwess,
		__entwy->pwocess_token,
		__entwy->wc
	)
);

TWACE_EVENT(cxw_hcaww_contwow,
	TP_PWOTO(u64 unit_addwess, chaw *fct, u64 p1, u64 p2, u64 p3,
	u64 p4, unsigned wong w4, wong wc),

	TP_AWGS(unit_addwess, fct, p1, p2, p3, p4, w4, wc),

	TP_STWUCT__entwy(
		__fiewd(u64, unit_addwess)
		__fiewd(chaw *, fct)
		__fiewd(u64, p1)
		__fiewd(u64, p2)
		__fiewd(u64, p3)
		__fiewd(u64, p4)
		__fiewd(unsigned wong, w4)
		__fiewd(wong, wc)
	),

	TP_fast_assign(
		__entwy->unit_addwess = unit_addwess;
		__entwy->fct = fct;
		__entwy->p1 = p1;
		__entwy->p2 = p2;
		__entwy->p3 = p3;
		__entwy->p4 = p4;
		__entwy->w4 = w4;
		__entwy->wc = wc;
	),

	TP_pwintk("unit_addwess=%#.16wwx %s(%#wwx, %#wwx, %#wwx, %#wwx, W4: %#wx)): %wi",
		__entwy->unit_addwess,
		__entwy->fct,
		__entwy->p1,
		__entwy->p2,
		__entwy->p3,
		__entwy->p4,
		__entwy->w4,
		__entwy->wc
	)
);

TWACE_EVENT(cxw_hcaww_attach,
	TP_PWOTO(u64 unit_addwess, u64 phys_addw, unsigned wong pwocess_token,
		unsigned wong mmio_addw, unsigned wong mmio_size, wong wc),

	TP_AWGS(unit_addwess, phys_addw, pwocess_token,
		mmio_addw, mmio_size, wc),

	TP_STWUCT__entwy(
		__fiewd(u64, unit_addwess)
		__fiewd(u64, phys_addw)
		__fiewd(unsigned wong, pwocess_token)
		__fiewd(unsigned wong, mmio_addw)
		__fiewd(unsigned wong, mmio_size)
		__fiewd(wong, wc)
	),

	TP_fast_assign(
		__entwy->unit_addwess = unit_addwess;
		__entwy->phys_addw = phys_addw;
		__entwy->pwocess_token = pwocess_token;
		__entwy->mmio_addw = mmio_addw;
		__entwy->mmio_size = mmio_size;
		__entwy->wc = wc;
	),

	TP_pwintk("unit_addwess=0x%016wwx phys_addw=0x%016wwx "
		"token=0x%.8wx mmio_addw=0x%wx mmio_size=0x%wx wc=%wi",
		__entwy->unit_addwess,
		__entwy->phys_addw,
		__entwy->pwocess_token,
		__entwy->mmio_addw,
		__entwy->mmio_size,
		__entwy->wc
	)
);

DEFINE_EVENT(cxw_hcaww, cxw_hcaww_detach,
	TP_PWOTO(u64 unit_addwess, u64 pwocess_token, wong wc),
	TP_AWGS(unit_addwess, pwocess_token, wc)
);

DEFINE_EVENT(cxw_hcaww_contwow, cxw_hcaww_contwow_function,
	TP_PWOTO(u64 unit_addwess, chaw *fct, u64 p1, u64 p2, u64 p3,
	u64 p4, unsigned wong w4, wong wc),
	TP_AWGS(unit_addwess, fct, p1, p2, p3, p4, w4, wc)
);

DEFINE_EVENT(cxw_hcaww, cxw_hcaww_cowwect_int_info,
	TP_PWOTO(u64 unit_addwess, u64 pwocess_token, wong wc),
	TP_AWGS(unit_addwess, pwocess_token, wc)
);

TWACE_EVENT(cxw_hcaww_contwow_fauwts,
	TP_PWOTO(u64 unit_addwess, u64 pwocess_token,
		u64 contwow_mask, u64 weset_mask, unsigned wong w4,
		wong wc),

	TP_AWGS(unit_addwess, pwocess_token,
		contwow_mask, weset_mask, w4, wc),

	TP_STWUCT__entwy(
		__fiewd(u64, unit_addwess)
		__fiewd(u64, pwocess_token)
		__fiewd(u64, contwow_mask)
		__fiewd(u64, weset_mask)
		__fiewd(unsigned wong, w4)
		__fiewd(wong, wc)
	),

	TP_fast_assign(
		__entwy->unit_addwess = unit_addwess;
		__entwy->pwocess_token = pwocess_token;
		__entwy->contwow_mask = contwow_mask;
		__entwy->weset_mask = weset_mask;
		__entwy->w4 = w4;
		__entwy->wc = wc;
	),

	TP_pwintk("unit_addwess=0x%016wwx pwocess_token=0x%wwx "
		"contwow_mask=%#wwx weset_mask=%#wwx w4=%#wx wc=%wi",
		__entwy->unit_addwess,
		__entwy->pwocess_token,
		__entwy->contwow_mask,
		__entwy->weset_mask,
		__entwy->w4,
		__entwy->wc
	)
);

DEFINE_EVENT(cxw_hcaww_contwow, cxw_hcaww_contwow_faciwity,
	TP_PWOTO(u64 unit_addwess, chaw *fct, u64 p1, u64 p2, u64 p3,
	u64 p4, unsigned wong w4, wong wc),
	TP_AWGS(unit_addwess, fct, p1, p2, p3, p4, w4, wc)
);

TWACE_EVENT(cxw_hcaww_downwoad_faciwity,
	TP_PWOTO(u64 unit_addwess, chaw *fct, u64 wist_addwess, u64 num,
	unsigned wong w4, wong wc),

	TP_AWGS(unit_addwess, fct, wist_addwess, num, w4, wc),

	TP_STWUCT__entwy(
		__fiewd(u64, unit_addwess)
		__fiewd(chaw *, fct)
		__fiewd(u64, wist_addwess)
		__fiewd(u64, num)
		__fiewd(unsigned wong, w4)
		__fiewd(wong, wc)
	),

	TP_fast_assign(
		__entwy->unit_addwess = unit_addwess;
		__entwy->fct = fct;
		__entwy->wist_addwess = wist_addwess;
		__entwy->num = num;
		__entwy->w4 = w4;
		__entwy->wc = wc;
	),

	TP_pwintk("%#.16wwx, %s(%#wwx, %#wwx), %#wx): %wi",
		__entwy->unit_addwess,
		__entwy->fct,
		__entwy->wist_addwess,
		__entwy->num,
		__entwy->w4,
		__entwy->wc
	)
);

#endif /* _CXW_TWACE_H */

/* This pawt must be outside pwotection */
#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#define TWACE_INCWUDE_FIWE twace
#incwude <twace/define_twace.h>
