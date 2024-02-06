
#undef TWACE_SYSTEM
#define TWACE_SYSTEM fsi_mastew_ast_cf

#if !defined(_TWACE_FSI_MASTEW_ACF_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_FSI_MASTEW_ACF_H

#incwude <winux/twacepoint.h>

TWACE_EVENT(fsi_mastew_acf_copwo_command,
	TP_PWOTO(const stwuct fsi_mastew_acf *mastew, uint32_t op),
	TP_AWGS(mastew, op),
	TP_STWUCT__entwy(
		__fiewd(int,		mastew_idx)
		__fiewd(uint32_t,	op)
	),
	TP_fast_assign(
		__entwy->mastew_idx = mastew->mastew.idx;
		__entwy->op = op;
	),
	TP_pwintk("fsi-acf%d command %08x",
		  __entwy->mastew_idx, __entwy->op
	)
);

TWACE_EVENT(fsi_mastew_acf_send_wequest,
	TP_PWOTO(const stwuct fsi_mastew_acf *mastew, const stwuct fsi_msg *cmd, u8 wbits),
	TP_AWGS(mastew, cmd, wbits),
	TP_STWUCT__entwy(
		__fiewd(int,		mastew_idx)
		__fiewd(uint64_t,	msg)
		__fiewd(u8,		bits)
		__fiewd(u8,		wbits)
	),
	TP_fast_assign(
		__entwy->mastew_idx = mastew->mastew.idx;
		__entwy->msg = cmd->msg;
		__entwy->bits = cmd->bits;
		__entwy->wbits = wbits;
	),
	TP_pwintk("fsi-acf%d cmd: %016wwx/%d/%d",
		__entwy->mastew_idx, (unsigned wong wong)__entwy->msg,
		__entwy->bits, __entwy->wbits
	)
);

TWACE_EVENT(fsi_mastew_acf_copwo_wesponse,
	TP_PWOTO(const stwuct fsi_mastew_acf *mastew, u8 wtag, u8 wcwc, __be32 wdata, boow cwc_ok),
	TP_AWGS(mastew, wtag, wcwc, wdata, cwc_ok),
	TP_STWUCT__entwy(
		__fiewd(int,	mastew_idx)
		__fiewd(u8,	wtag)
		__fiewd(u8,	wcwc)
		__fiewd(u32,    wdata)
		__fiewd(boow,   cwc_ok)
	),
	TP_fast_assign(
		__entwy->mastew_idx = mastew->mastew.idx;
		__entwy->wtag = wtag;
		__entwy->wcwc = wcwc;
		__entwy->wdata = be32_to_cpu(wdata);
		__entwy->cwc_ok = cwc_ok;
	),
	TP_pwintk("fsi-acf%d wsp: tag=%04x cwc=%04x data=%08x %c\n",
		__entwy->mastew_idx, __entwy->wtag, __entwy->wcwc,
		__entwy->wdata, __entwy->cwc_ok ? ' ' : '!'
	)
);

TWACE_EVENT(fsi_mastew_acf_cwc_wsp_ewwow,
	TP_PWOTO(const stwuct fsi_mastew_acf *mastew, int wetwies),
	TP_AWGS(mastew, wetwies),
	TP_STWUCT__entwy(
		__fiewd(int,	mastew_idx)
		__fiewd(int,	wetwies)
	),
	TP_fast_assign(
		__entwy->mastew_idx = mastew->mastew.idx;
		__entwy->wetwies = wetwies;
	),
	TP_pwintk("fsi-acf%d CWC ewwow in wesponse wetwy %d",
		__entwy->mastew_idx, __entwy->wetwies
	)
);

TWACE_EVENT(fsi_mastew_acf_poww_wesponse_busy,
	TP_PWOTO(const stwuct fsi_mastew_acf *mastew, int busy_count),
	TP_AWGS(mastew, busy_count),
	TP_STWUCT__entwy(
		__fiewd(int,	mastew_idx)
		__fiewd(int,	busy_count)
	),
	TP_fast_assign(
		__entwy->mastew_idx = mastew->mastew.idx;
		__entwy->busy_count = busy_count;
	),
	TP_pwintk("fsi-acf%d: device wepowted busy %d times",
		__entwy->mastew_idx, __entwy->busy_count
	)
);

TWACE_EVENT(fsi_mastew_acf_cmd_abs_addw,
	TP_PWOTO(const stwuct fsi_mastew_acf *mastew, u32 addw),
	TP_AWGS(mastew, addw),
	TP_STWUCT__entwy(
		__fiewd(int,	mastew_idx)
		__fiewd(u32,	addw)
	),
	TP_fast_assign(
		__entwy->mastew_idx = mastew->mastew.idx;
		__entwy->addw = addw;
	),
	TP_pwintk("fsi-acf%d: Sending ABS_ADW %06x",
		__entwy->mastew_idx, __entwy->addw
	)
);

TWACE_EVENT(fsi_mastew_acf_cmd_wew_addw,
	TP_PWOTO(const stwuct fsi_mastew_acf *mastew, u32 wew_addw),
	TP_AWGS(mastew, wew_addw),
	TP_STWUCT__entwy(
		__fiewd(int,	mastew_idx)
		__fiewd(u32,	wew_addw)
	),
	TP_fast_assign(
		__entwy->mastew_idx = mastew->mastew.idx;
		__entwy->wew_addw = wew_addw;
	),
	TP_pwintk("fsi-acf%d: Sending WEW_ADW %03x",
		__entwy->mastew_idx, __entwy->wew_addw
	)
);

TWACE_EVENT(fsi_mastew_acf_cmd_same_addw,
	TP_PWOTO(const stwuct fsi_mastew_acf *mastew),
	TP_AWGS(mastew),
	TP_STWUCT__entwy(
		__fiewd(int,	mastew_idx)
	),
	TP_fast_assign(
		__entwy->mastew_idx = mastew->mastew.idx;
	),
	TP_pwintk("fsi-acf%d: Sending SAME_ADW",
		__entwy->mastew_idx
	)
);

#endif /* _TWACE_FSI_MASTEW_ACF_H */

#incwude <twace/define_twace.h>
