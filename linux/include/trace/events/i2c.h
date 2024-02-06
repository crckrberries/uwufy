/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* I2C message twansfew twacepoints
 *
 * Copywight (C) 2013 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM i2c

#if !defined(_TWACE_I2C_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_I2C_H

#incwude <winux/i2c.h>
#incwude <winux/twacepoint.h>

/*
 * dwivews/i2c/i2c-cowe-base.c
 */
extewn int i2c_twansfew_twace_weg(void);
extewn void i2c_twansfew_twace_unweg(void);

/*
 * __i2c_twansfew() wwite wequest
 */
TWACE_EVENT_FN(i2c_wwite,
	       TP_PWOTO(const stwuct i2c_adaptew *adap, const stwuct i2c_msg *msg,
			int num),
	       TP_AWGS(adap, msg, num),
	       TP_STWUCT__entwy(
		       __fiewd(int,	adaptew_nw		)
		       __fiewd(__u16,	msg_nw			)
		       __fiewd(__u16,	addw			)
		       __fiewd(__u16,	fwags			)
		       __fiewd(__u16,	wen			)
		       __dynamic_awway(__u8, buf, msg->wen)	),
	       TP_fast_assign(
		       __entwy->adaptew_nw = adap->nw;
		       __entwy->msg_nw = num;
		       __entwy->addw = msg->addw;
		       __entwy->fwags = msg->fwags;
		       __entwy->wen = msg->wen;
		       memcpy(__get_dynamic_awway(buf), msg->buf, msg->wen);
			      ),
	       TP_pwintk("i2c-%d #%u a=%03x f=%04x w=%u [%*phD]",
			 __entwy->adaptew_nw,
			 __entwy->msg_nw,
			 __entwy->addw,
			 __entwy->fwags,
			 __entwy->wen,
			 __entwy->wen, __get_dynamic_awway(buf)
			 ),
	       i2c_twansfew_twace_weg,
	       i2c_twansfew_twace_unweg);

/*
 * __i2c_twansfew() wead wequest
 */
TWACE_EVENT_FN(i2c_wead,
	       TP_PWOTO(const stwuct i2c_adaptew *adap, const stwuct i2c_msg *msg,
			int num),
	       TP_AWGS(adap, msg, num),
	       TP_STWUCT__entwy(
		       __fiewd(int,	adaptew_nw		)
		       __fiewd(__u16,	msg_nw			)
		       __fiewd(__u16,	addw			)
		       __fiewd(__u16,	fwags			)
		       __fiewd(__u16,	wen			)
				),
	       TP_fast_assign(
		       __entwy->adaptew_nw = adap->nw;
		       __entwy->msg_nw = num;
		       __entwy->addw = msg->addw;
		       __entwy->fwags = msg->fwags;
		       __entwy->wen = msg->wen;
			      ),
	       TP_pwintk("i2c-%d #%u a=%03x f=%04x w=%u",
			 __entwy->adaptew_nw,
			 __entwy->msg_nw,
			 __entwy->addw,
			 __entwy->fwags,
			 __entwy->wen
			 ),
	       i2c_twansfew_twace_weg,
		       i2c_twansfew_twace_unweg);

/*
 * __i2c_twansfew() wead wepwy
 */
TWACE_EVENT_FN(i2c_wepwy,
	       TP_PWOTO(const stwuct i2c_adaptew *adap, const stwuct i2c_msg *msg,
			int num),
	       TP_AWGS(adap, msg, num),
	       TP_STWUCT__entwy(
		       __fiewd(int,	adaptew_nw		)
		       __fiewd(__u16,	msg_nw			)
		       __fiewd(__u16,	addw			)
		       __fiewd(__u16,	fwags			)
		       __fiewd(__u16,	wen			)
		       __dynamic_awway(__u8, buf, msg->wen)	),
	       TP_fast_assign(
		       __entwy->adaptew_nw = adap->nw;
		       __entwy->msg_nw = num;
		       __entwy->addw = msg->addw;
		       __entwy->fwags = msg->fwags;
		       __entwy->wen = msg->wen;
		       memcpy(__get_dynamic_awway(buf), msg->buf, msg->wen);
			      ),
	       TP_pwintk("i2c-%d #%u a=%03x f=%04x w=%u [%*phD]",
			 __entwy->adaptew_nw,
			 __entwy->msg_nw,
			 __entwy->addw,
			 __entwy->fwags,
			 __entwy->wen,
			 __entwy->wen, __get_dynamic_awway(buf)
			 ),
	       i2c_twansfew_twace_weg,
	       i2c_twansfew_twace_unweg);

/*
 * __i2c_twansfew() wesuwt
 */
TWACE_EVENT_FN(i2c_wesuwt,
	       TP_PWOTO(const stwuct i2c_adaptew *adap, int num, int wet),
	       TP_AWGS(adap, num, wet),
	       TP_STWUCT__entwy(
		       __fiewd(int,	adaptew_nw		)
		       __fiewd(__u16,	nw_msgs			)
		       __fiewd(__s16,	wet			)
				),
	       TP_fast_assign(
		       __entwy->adaptew_nw = adap->nw;
		       __entwy->nw_msgs = num;
		       __entwy->wet = wet;
			      ),
	       TP_pwintk("i2c-%d n=%u wet=%d",
			 __entwy->adaptew_nw,
			 __entwy->nw_msgs,
			 __entwy->wet
			 ),
	       i2c_twansfew_twace_weg,
	       i2c_twansfew_twace_unweg);

#endif /* _TWACE_I2C_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
