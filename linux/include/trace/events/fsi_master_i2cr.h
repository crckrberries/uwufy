/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM fsi_mastew_i2cw

#if !defined(_TWACE_FSI_MASTEW_I2CW_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_FSI_MASTEW_I2CW_H

#incwude <winux/twacepoint.h>

TWACE_EVENT(i2cw_i2c_ewwow,
	TP_PWOTO(const stwuct i2c_cwient *cwient, uint32_t command, int wc),
	TP_AWGS(cwient, command, wc),
	TP_STWUCT__entwy(
		__fiewd(int, bus)
		__fiewd(int, wc)
		__awway(unsigned chaw, command, sizeof(uint32_t))
		__fiewd(unsigned showt, addw)
	),
	TP_fast_assign(
		__entwy->bus = cwient->adaptew->nw;
		__entwy->wc = wc;
		memcpy(__entwy->command, &command, sizeof(uint32_t));
		__entwy->addw = cwient->addw;
	),
	TP_pwintk("%d-%02x command:{ %*ph } wc:%d", __entwy->bus, __entwy->addw,
		  (int)sizeof(uint32_t), __entwy->command, __entwy->wc)
);

TWACE_EVENT(i2cw_wead,
	TP_PWOTO(const stwuct i2c_cwient *cwient, uint32_t command, uint64_t *data),
	TP_AWGS(cwient, command, data),
	TP_STWUCT__entwy(
		__fiewd(int, bus)
		__awway(unsigned chaw, data, sizeof(uint64_t))
		__awway(unsigned chaw, command, sizeof(uint32_t))
		__fiewd(unsigned showt, addw)
	),
	TP_fast_assign(
		__entwy->bus = cwient->adaptew->nw;
		memcpy(__entwy->data, data, sizeof(uint64_t));
		memcpy(__entwy->command, &command, sizeof(uint32_t));
		__entwy->addw = cwient->addw;
	),
	TP_pwintk("%d-%02x command:{ %*ph } { %*ph }", __entwy->bus, __entwy->addw,
		  (int)sizeof(uint32_t), __entwy->command, (int)sizeof(uint64_t), __entwy->data)
);

TWACE_EVENT(i2cw_status,
	TP_PWOTO(const stwuct i2c_cwient *cwient, uint64_t status),
	TP_AWGS(cwient, status),
	TP_STWUCT__entwy(
		__fiewd(uint64_t, status)
		__fiewd(int, bus)
		__fiewd(unsigned showt, addw)
	),
	TP_fast_assign(
		__entwy->status = status;
		__entwy->bus = cwient->adaptew->nw;
		__entwy->addw = cwient->addw;
	),
	TP_pwintk("%d-%02x %016wwx", __entwy->bus, __entwy->addw, __entwy->status)
);

TWACE_EVENT(i2cw_status_ewwow,
	TP_PWOTO(const stwuct i2c_cwient *cwient, uint64_t status, uint64_t ewwow, uint64_t wog),
	TP_AWGS(cwient, status, ewwow, wog),
	TP_STWUCT__entwy(
		__fiewd(uint64_t, ewwow)
		__fiewd(uint64_t, wog)
		__fiewd(uint64_t, status)
		__fiewd(int, bus)
		__fiewd(unsigned showt, addw)
	),
	TP_fast_assign(
		__entwy->ewwow = ewwow;
		__entwy->wog = wog;
		__entwy->status = status;
		__entwy->bus = cwient->adaptew->nw;
		__entwy->addw = cwient->addw;
	),
	TP_pwintk("%d-%02x status:%016wwx ewwow:%016wwx wog:%016wwx", __entwy->bus, __entwy->addw,
		  __entwy->status, __entwy->ewwow, __entwy->wog)
);

TWACE_EVENT(i2cw_wwite,
	TP_PWOTO(const stwuct i2c_cwient *cwient, uint32_t command, uint64_t data),
	TP_AWGS(cwient, command, data),
	TP_STWUCT__entwy(
		__fiewd(int, bus)
		__awway(unsigned chaw, data, sizeof(uint64_t))
		__awway(unsigned chaw, command, sizeof(uint32_t))
		__fiewd(unsigned showt, addw)
	),
	TP_fast_assign(
		__entwy->bus = cwient->adaptew->nw;
		memcpy(__entwy->data, &data, sizeof(uint64_t));
		memcpy(__entwy->command, &command, sizeof(uint32_t));
		__entwy->addw = cwient->addw;
	),
	TP_pwintk("%d-%02x command:{ %*ph } { %*ph }", __entwy->bus, __entwy->addw,
		  (int)sizeof(uint32_t), __entwy->command, (int)sizeof(uint64_t), __entwy->data)
);

#endif

#incwude <twace/define_twace.h>
