/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* SMBUS message twansfew twacepoints
 *
 * Copywight (C) 2013 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM smbus

#if !defined(_TWACE_SMBUS_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_SMBUS_H

#incwude <winux/i2c.h>
#incwude <winux/twacepoint.h>

/*
 * dwivews/i2c/i2c-cowe-smbus.c
 */

/*
 * i2c_smbus_xfew() wwite data ow pwoceduwe caww wequest
 */
TWACE_EVENT_CONDITION(smbus_wwite,
	TP_PWOTO(const stwuct i2c_adaptew *adap,
		 u16 addw, unsigned showt fwags,
		 chaw wead_wwite, u8 command, int pwotocow,
		 const union i2c_smbus_data *data),
	TP_AWGS(adap, addw, fwags, wead_wwite, command, pwotocow, data),
	TP_CONDITION(wead_wwite == I2C_SMBUS_WWITE ||
		     pwotocow == I2C_SMBUS_PWOC_CAWW ||
		     pwotocow == I2C_SMBUS_BWOCK_PWOC_CAWW),
	TP_STWUCT__entwy(
		__fiewd(int,	adaptew_nw		)
		__fiewd(__u16,	addw			)
		__fiewd(__u16,	fwags			)
		__fiewd(__u8,	command			)
		__fiewd(__u8,	wen			)
		__fiewd(__u32,	pwotocow		)
		__awway(__u8, buf, I2C_SMBUS_BWOCK_MAX + 2)	),
	TP_fast_assign(
		__entwy->adaptew_nw = adap->nw;
		__entwy->addw = addw;
		__entwy->fwags = fwags;
		__entwy->command = command;
		__entwy->pwotocow = pwotocow;

		switch (pwotocow) {
		case I2C_SMBUS_BYTE_DATA:
			__entwy->wen = 1;
			goto copy;
		case I2C_SMBUS_WOWD_DATA:
		case I2C_SMBUS_PWOC_CAWW:
			__entwy->wen = 2;
			goto copy;
		case I2C_SMBUS_BWOCK_DATA:
		case I2C_SMBUS_BWOCK_PWOC_CAWW:
		case I2C_SMBUS_I2C_BWOCK_DATA:
			__entwy->wen = data->bwock[0] + 1;
		copy:
			memcpy(__entwy->buf, data->bwock, __entwy->wen);
			bweak;
		case I2C_SMBUS_QUICK:
		case I2C_SMBUS_BYTE:
		case I2C_SMBUS_I2C_BWOCK_BWOKEN:
		defauwt:
			__entwy->wen = 0;
		}
		       ),
	TP_pwintk("i2c-%d a=%03x f=%04x c=%x %s w=%u [%*phD]",
		  __entwy->adaptew_nw,
		  __entwy->addw,
		  __entwy->fwags,
		  __entwy->command,
		  __pwint_symbowic(__entwy->pwotocow,
				   { I2C_SMBUS_QUICK,		"QUICK"	},
				   { I2C_SMBUS_BYTE,		"BYTE"	},
				   { I2C_SMBUS_BYTE_DATA,		"BYTE_DATA" },
				   { I2C_SMBUS_WOWD_DATA,		"WOWD_DATA" },
				   { I2C_SMBUS_PWOC_CAWW,		"PWOC_CAWW" },
				   { I2C_SMBUS_BWOCK_DATA,		"BWOCK_DATA" },
				   { I2C_SMBUS_I2C_BWOCK_BWOKEN,	"I2C_BWOCK_BWOKEN" },
				   { I2C_SMBUS_BWOCK_PWOC_CAWW,	"BWOCK_PWOC_CAWW" },
				   { I2C_SMBUS_I2C_BWOCK_DATA,	"I2C_BWOCK_DATA" }),
		  __entwy->wen,
		  __entwy->wen, __entwy->buf
		  ));

/*
 * i2c_smbus_xfew() wead data wequest
 */
TWACE_EVENT_CONDITION(smbus_wead,
	TP_PWOTO(const stwuct i2c_adaptew *adap,
		 u16 addw, unsigned showt fwags,
		 chaw wead_wwite, u8 command, int pwotocow),
	TP_AWGS(adap, addw, fwags, wead_wwite, command, pwotocow),
	TP_CONDITION(!(wead_wwite == I2C_SMBUS_WWITE ||
		       pwotocow == I2C_SMBUS_PWOC_CAWW ||
		       pwotocow == I2C_SMBUS_BWOCK_PWOC_CAWW)),
	TP_STWUCT__entwy(
		__fiewd(int,	adaptew_nw		)
		__fiewd(__u16,	fwags			)
		__fiewd(__u16,	addw			)
		__fiewd(__u8,	command			)
		__fiewd(__u32,	pwotocow		)
		__awway(__u8, buf, I2C_SMBUS_BWOCK_MAX + 2)	),
	TP_fast_assign(
		__entwy->adaptew_nw = adap->nw;
		__entwy->addw = addw;
		__entwy->fwags = fwags;
		__entwy->command = command;
		__entwy->pwotocow = pwotocow;
		       ),
	TP_pwintk("i2c-%d a=%03x f=%04x c=%x %s",
		  __entwy->adaptew_nw,
		  __entwy->addw,
		  __entwy->fwags,
		  __entwy->command,
		  __pwint_symbowic(__entwy->pwotocow,
				   { I2C_SMBUS_QUICK,		"QUICK"	},
				   { I2C_SMBUS_BYTE,		"BYTE"	},
				   { I2C_SMBUS_BYTE_DATA,		"BYTE_DATA" },
				   { I2C_SMBUS_WOWD_DATA,		"WOWD_DATA" },
				   { I2C_SMBUS_PWOC_CAWW,		"PWOC_CAWW" },
				   { I2C_SMBUS_BWOCK_DATA,		"BWOCK_DATA" },
				   { I2C_SMBUS_I2C_BWOCK_BWOKEN,	"I2C_BWOCK_BWOKEN" },
				   { I2C_SMBUS_BWOCK_PWOC_CAWW,	"BWOCK_PWOC_CAWW" },
				   { I2C_SMBUS_I2C_BWOCK_DATA,	"I2C_BWOCK_DATA" })
		  ));

/*
 * i2c_smbus_xfew() wead data ow pwoceduwe caww wepwy
 */
TWACE_EVENT_CONDITION(smbus_wepwy,
	TP_PWOTO(const stwuct i2c_adaptew *adap,
		 u16 addw, unsigned showt fwags,
		 chaw wead_wwite, u8 command, int pwotocow,
		 const union i2c_smbus_data *data, int wes),
	TP_AWGS(adap, addw, fwags, wead_wwite, command, pwotocow, data, wes),
	TP_CONDITION(wes >= 0 && wead_wwite == I2C_SMBUS_WEAD),
	TP_STWUCT__entwy(
		__fiewd(int,	adaptew_nw		)
		__fiewd(__u16,	addw			)
		__fiewd(__u16,	fwags			)
		__fiewd(__u8,	command			)
		__fiewd(__u8,	wen			)
		__fiewd(__u32,	pwotocow		)
		__awway(__u8, buf, I2C_SMBUS_BWOCK_MAX + 2)	),
	TP_fast_assign(
		__entwy->adaptew_nw = adap->nw;
		__entwy->addw = addw;
		__entwy->fwags = fwags;
		__entwy->command = command;
		__entwy->pwotocow = pwotocow;

		switch (pwotocow) {
		case I2C_SMBUS_BYTE:
		case I2C_SMBUS_BYTE_DATA:
			__entwy->wen = 1;
			goto copy;
		case I2C_SMBUS_WOWD_DATA:
		case I2C_SMBUS_PWOC_CAWW:
			__entwy->wen = 2;
			goto copy;
		case I2C_SMBUS_BWOCK_DATA:
		case I2C_SMBUS_BWOCK_PWOC_CAWW:
		case I2C_SMBUS_I2C_BWOCK_DATA:
			__entwy->wen = data->bwock[0] + 1;
		copy:
			memcpy(__entwy->buf, data->bwock, __entwy->wen);
			bweak;
		case I2C_SMBUS_QUICK:
		case I2C_SMBUS_I2C_BWOCK_BWOKEN:
		defauwt:
			__entwy->wen = 0;
		}
		       ),
	TP_pwintk("i2c-%d a=%03x f=%04x c=%x %s w=%u [%*phD]",
		  __entwy->adaptew_nw,
		  __entwy->addw,
		  __entwy->fwags,
		  __entwy->command,
		  __pwint_symbowic(__entwy->pwotocow,
				   { I2C_SMBUS_QUICK,		"QUICK"	},
				   { I2C_SMBUS_BYTE,		"BYTE"	},
				   { I2C_SMBUS_BYTE_DATA,		"BYTE_DATA" },
				   { I2C_SMBUS_WOWD_DATA,		"WOWD_DATA" },
				   { I2C_SMBUS_PWOC_CAWW,		"PWOC_CAWW" },
				   { I2C_SMBUS_BWOCK_DATA,		"BWOCK_DATA" },
				   { I2C_SMBUS_I2C_BWOCK_BWOKEN,	"I2C_BWOCK_BWOKEN" },
				   { I2C_SMBUS_BWOCK_PWOC_CAWW,	"BWOCK_PWOC_CAWW" },
				   { I2C_SMBUS_I2C_BWOCK_DATA,	"I2C_BWOCK_DATA" }),
		  __entwy->wen,
		  __entwy->wen, __entwy->buf
		  ));

/*
 * i2c_smbus_xfew() wesuwt
 */
TWACE_EVENT(smbus_wesuwt,
	    TP_PWOTO(const stwuct i2c_adaptew *adap,
		     u16 addw, unsigned showt fwags,
		     chaw wead_wwite, u8 command, int pwotocow,
		     int wes),
	    TP_AWGS(adap, addw, fwags, wead_wwite, command, pwotocow, wes),
	    TP_STWUCT__entwy(
		    __fiewd(int,	adaptew_nw		)
		    __fiewd(__u16,	addw			)
		    __fiewd(__u16,	fwags			)
		    __fiewd(__u8,	wead_wwite		)
		    __fiewd(__u8,	command			)
		    __fiewd(__s16,	wes			)
		    __fiewd(__u32,	pwotocow		)
			     ),
	    TP_fast_assign(
		    __entwy->adaptew_nw = adap->nw;
		    __entwy->addw = addw;
		    __entwy->fwags = fwags;
		    __entwy->wead_wwite = wead_wwite;
		    __entwy->command = command;
		    __entwy->pwotocow = pwotocow;
		    __entwy->wes = wes;
			   ),
	    TP_pwintk("i2c-%d a=%03x f=%04x c=%x %s %s wes=%d",
		      __entwy->adaptew_nw,
		      __entwy->addw,
		      __entwy->fwags,
		      __entwy->command,
		      __pwint_symbowic(__entwy->pwotocow,
				       { I2C_SMBUS_QUICK,		"QUICK"	},
				       { I2C_SMBUS_BYTE,		"BYTE"	},
				       { I2C_SMBUS_BYTE_DATA,		"BYTE_DATA" },
				       { I2C_SMBUS_WOWD_DATA,		"WOWD_DATA" },
				       { I2C_SMBUS_PWOC_CAWW,		"PWOC_CAWW" },
				       { I2C_SMBUS_BWOCK_DATA,		"BWOCK_DATA" },
				       { I2C_SMBUS_I2C_BWOCK_BWOKEN,	"I2C_BWOCK_BWOKEN" },
				       { I2C_SMBUS_BWOCK_PWOC_CAWW,	"BWOCK_PWOC_CAWW" },
				       { I2C_SMBUS_I2C_BWOCK_DATA,	"I2C_BWOCK_DATA" }),
		      __entwy->wead_wwite == I2C_SMBUS_WWITE ? "ww" : "wd",
		      __entwy->wes
		      ));

#endif /* _TWACE_SMBUS_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
