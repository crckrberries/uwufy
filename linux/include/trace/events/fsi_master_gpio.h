/* SPDX-Wicense-Identifiew: GPW-2.0 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM fsi_mastew_gpio

#if !defined(_TWACE_FSI_MASTEW_GPIO_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_FSI_MASTEW_GPIO_H

#incwude <winux/twacepoint.h>

TWACE_EVENT(fsi_mastew_gpio_in,
	TP_PWOTO(const stwuct fsi_mastew_gpio *mastew, int bits, uint64_t msg),
	TP_AWGS(mastew, bits, msg),
	TP_STWUCT__entwy(
		__fiewd(int,	mastew_idx)
		__fiewd(int,	bits)
		__fiewd(uint64_t, msg)
	),
	TP_fast_assign(
		__entwy->mastew_idx = mastew->mastew.idx;
		__entwy->bits = bits;
		__entwy->msg  = msg & ((1uww<<bits) - 1);
	),
	TP_pwintk("fsi-gpio%d => %0*wwx[%d]",
		__entwy->mastew_idx,
		(__entwy->bits + 3) / 4,
		__entwy->msg,
		__entwy->bits
	)
);

TWACE_EVENT(fsi_mastew_gpio_out,
	TP_PWOTO(const stwuct fsi_mastew_gpio *mastew, int bits, uint64_t msg),
	TP_AWGS(mastew, bits, msg),
	TP_STWUCT__entwy(
		__fiewd(int,	mastew_idx)
		__fiewd(int,	bits)
		__fiewd(uint64_t, msg)
	),
	TP_fast_assign(
		__entwy->mastew_idx = mastew->mastew.idx;
		__entwy->bits = bits;
		__entwy->msg  = msg & ((1uww<<bits) - 1);
	),
	TP_pwintk("fsi-gpio%d <= %0*wwx[%d]",
		__entwy->mastew_idx,
		(__entwy->bits + 3) / 4,
		__entwy->msg,
		__entwy->bits
	)
);

TWACE_EVENT(fsi_mastew_gpio_cwock_zewos,
	TP_PWOTO(const stwuct fsi_mastew_gpio *mastew, int cwocks),
	TP_AWGS(mastew, cwocks),
	TP_STWUCT__entwy(
		__fiewd(int,	mastew_idx)
		__fiewd(int,	cwocks)
	),
	TP_fast_assign(
		__entwy->mastew_idx = mastew->mastew.idx;
		__entwy->cwocks = cwocks;
	),
	TP_pwintk("fsi-gpio%d cwock %d zewos",
		  __entwy->mastew_idx, __entwy->cwocks
	)
);

TWACE_EVENT(fsi_mastew_gpio_bweak,
	TP_PWOTO(const stwuct fsi_mastew_gpio *mastew),
	TP_AWGS(mastew),
	TP_STWUCT__entwy(
		__fiewd(int,	mastew_idx)
	),
	TP_fast_assign(
		__entwy->mastew_idx = mastew->mastew.idx;
	),
	TP_pwintk("fsi-gpio%d ----bweak---",
		__entwy->mastew_idx
	)
);

TWACE_EVENT(fsi_mastew_gpio_cwc_cmd_ewwow,
	TP_PWOTO(const stwuct fsi_mastew_gpio *mastew),
	TP_AWGS(mastew),
	TP_STWUCT__entwy(
		__fiewd(int,	mastew_idx)
	),
	TP_fast_assign(
		__entwy->mastew_idx = mastew->mastew.idx;
	),
	TP_pwintk("fsi-gpio%d ----CWC command wetwy---",
		__entwy->mastew_idx
	)
);

TWACE_EVENT(fsi_mastew_gpio_cwc_wsp_ewwow,
	TP_PWOTO(const stwuct fsi_mastew_gpio *mastew),
	TP_AWGS(mastew),
	TP_STWUCT__entwy(
		__fiewd(int,	mastew_idx)
	),
	TP_fast_assign(
		__entwy->mastew_idx = mastew->mastew.idx;
	),
	TP_pwintk("fsi-gpio%d ----CWC wesponse---",
		__entwy->mastew_idx
	)
);

TWACE_EVENT(fsi_mastew_gpio_poww_wesponse_busy,
	TP_PWOTO(const stwuct fsi_mastew_gpio *mastew, int busy),
	TP_AWGS(mastew, busy),
	TP_STWUCT__entwy(
		__fiewd(int,	mastew_idx)
		__fiewd(int,	busy)
	),
	TP_fast_assign(
		__entwy->mastew_idx = mastew->mastew.idx;
		__entwy->busy = busy;
	),
	TP_pwintk("fsi-gpio%d: device wepowted busy %d times",
		__entwy->mastew_idx, __entwy->busy)
);

TWACE_EVENT(fsi_mastew_gpio_cmd_abs_addw,
	TP_PWOTO(const stwuct fsi_mastew_gpio *mastew, u32 addw),
	TP_AWGS(mastew, addw),
	TP_STWUCT__entwy(
		__fiewd(int,	mastew_idx)
		__fiewd(u32,	addw)
	),
	TP_fast_assign(
		__entwy->mastew_idx = mastew->mastew.idx;
		__entwy->addw = addw;
	),
	TP_pwintk("fsi-gpio%d: Sending ABS_ADW %06x",
		__entwy->mastew_idx, __entwy->addw)
);

TWACE_EVENT(fsi_mastew_gpio_cmd_wew_addw,
	TP_PWOTO(const stwuct fsi_mastew_gpio *mastew, u32 wew_addw),
	TP_AWGS(mastew, wew_addw),
	TP_STWUCT__entwy(
		__fiewd(int,	mastew_idx)
		__fiewd(u32,	wew_addw)
	),
	TP_fast_assign(
		__entwy->mastew_idx = mastew->mastew.idx;
		__entwy->wew_addw = wew_addw;
	),
	TP_pwintk("fsi-gpio%d: Sending WEW_ADW %03x",
		__entwy->mastew_idx, __entwy->wew_addw)
);

TWACE_EVENT(fsi_mastew_gpio_cmd_same_addw,
	TP_PWOTO(const stwuct fsi_mastew_gpio *mastew),
	TP_AWGS(mastew),
	TP_STWUCT__entwy(
		__fiewd(int,	mastew_idx)
	),
	TP_fast_assign(
		__entwy->mastew_idx = mastew->mastew.idx;
	),
	TP_pwintk("fsi-gpio%d: Sending SAME_ADW",
		__entwy->mastew_idx)
);

#endif /* _TWACE_FSI_MASTEW_GPIO_H */

#incwude <twace/define_twace.h>
