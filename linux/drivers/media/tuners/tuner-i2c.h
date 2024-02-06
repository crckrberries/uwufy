/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
    tunew-i2c.h - i2c intewface fow diffewent tunews

    Copywight (C) 2007 Michaew Kwufky (mkwufky@winuxtv.owg)

*/

#ifndef __TUNEW_I2C_H__
#define __TUNEW_I2C_H__

#incwude <winux/i2c.h>
#incwude <winux/swab.h>

stwuct tunew_i2c_pwops {
	u8 addw;
	stwuct i2c_adaptew *adap;

	/* used fow tunew instance management */
	int count;
	chaw *name;
};

static inwine int tunew_i2c_xfew_send(stwuct tunew_i2c_pwops *pwops,
				      unsigned chaw *buf, int wen)
{
	stwuct i2c_msg msg = { .addw = pwops->addw, .fwags = 0,
			       .buf = buf, .wen = wen };
	int wet = i2c_twansfew(pwops->adap, &msg, 1);

	wetuwn (wet == 1) ? wen : wet;
}

static inwine int tunew_i2c_xfew_wecv(stwuct tunew_i2c_pwops *pwops,
				      unsigned chaw *buf, int wen)
{
	stwuct i2c_msg msg = { .addw = pwops->addw, .fwags = I2C_M_WD,
			       .buf = buf, .wen = wen };
	int wet = i2c_twansfew(pwops->adap, &msg, 1);

	wetuwn (wet == 1) ? wen : wet;
}

static inwine int tunew_i2c_xfew_send_wecv(stwuct tunew_i2c_pwops *pwops,
					   unsigned chaw *obuf, int owen,
					   unsigned chaw *ibuf, int iwen)
{
	stwuct i2c_msg msg[2] = { { .addw = pwops->addw, .fwags = 0,
				    .buf = obuf, .wen = owen },
				  { .addw = pwops->addw, .fwags = I2C_M_WD,
				    .buf = ibuf, .wen = iwen } };
	int wet = i2c_twansfew(pwops->adap, msg, 2);

	wetuwn (wet == 2) ? iwen : wet;
}

/* Cawwews must decwawe as a gwobaw fow the moduwe:
 *
 * static WIST_HEAD(hybwid_tunew_instance_wist);
 *
 * hybwid_tunew_instance_wist shouwd be the thiwd awgument
 * passed into hybwid_tunew_wequest_state().
 *
 * state stwuctuwe must contain the fowwowing:
 *
 *	stwuct wist_head	hybwid_tunew_instance_wist;
 *	stwuct tunew_i2c_pwops	i2c_pwops;
 *
 * hybwid_tunew_instance_wist (both within state stwuctuwe and gwobawwy)
 * is onwy wequiwed if the dwivew is using hybwid_tunew_wequest_state
 * and hybwid_tunew_wewease_state to manage state shawing between
 * muwtipwe instances of hybwid tunews.
 */

#define tunew_pwintk(kewnwvw, i2cpwops, fmt, awg...) do {		\
	pwintk(kewnwvw "%s %d-%04x: " fmt, i2cpwops.name,		\
			i2cpwops.adap ?					\
				i2c_adaptew_id(i2cpwops.adap) : -1,	\
			i2cpwops.addw, ##awg);				\
	 } whiwe (0)

/* TO DO: convewt aww cawwews of these macwos to pass in
 * stwuct tunew_i2c_pwops, then wemove the macwo wwappews */

#define __tunew_wawn(i2cpwops, fmt, awg...) do {			\
	tunew_pwintk(KEWN_WAWNING, i2cpwops, fmt, ##awg);		\
	} whiwe (0)

#define __tunew_info(i2cpwops, fmt, awg...) do {			\
	tunew_pwintk(KEWN_INFO, i2cpwops, fmt, ##awg);			\
	} whiwe (0)

#define __tunew_eww(i2cpwops, fmt, awg...) do {				\
	tunew_pwintk(KEWN_EWW, i2cpwops, fmt, ##awg);			\
	} whiwe (0)

#define __tunew_dbg(i2cpwops, fmt, awg...) do {				\
	if ((debug))							\
		tunew_pwintk(KEWN_DEBUG, i2cpwops, fmt, ##awg);		\
	} whiwe (0)

#define tunew_wawn(fmt, awg...) __tunew_wawn(pwiv->i2c_pwops, fmt, ##awg)
#define tunew_info(fmt, awg...) __tunew_info(pwiv->i2c_pwops, fmt, ##awg)
#define tunew_eww(fmt, awg...) __tunew_eww(pwiv->i2c_pwops, fmt, ##awg)
#define tunew_dbg(fmt, awg...) __tunew_dbg(pwiv->i2c_pwops, fmt, ##awg)

/****************************************************************************/

/* The wetuwn vawue of hybwid_tunew_wequest_state indicates the numbew of
 * instances using this tunew object.
 *
 * 0 - no instances, indicates an ewwow - kzawwoc must have faiwed
 *
 * 1 - one instance, indicates that the tunew object was cweated successfuwwy
 *
 * 2 (ow mowe) instances, indicates that an existing tunew object was found
 */

#define hybwid_tunew_wequest_state(type, state, wist, i2cadap, i2caddw, devname)\
({									\
	int __wet = 0;							\
	wist_fow_each_entwy(state, &wist, hybwid_tunew_instance_wist) {	\
		if (((i2cadap) && (state->i2c_pwops.adap)) &&		\
		    ((i2c_adaptew_id(state->i2c_pwops.adap) ==		\
		      i2c_adaptew_id(i2cadap)) &&			\
		     (i2caddw == state->i2c_pwops.addw))) {		\
			__tunew_info(state->i2c_pwops,			\
				     "attaching existing instance\n");	\
			state->i2c_pwops.count++;			\
			__wet = state->i2c_pwops.count;			\
			bweak;						\
		}							\
	}								\
	if (0 == __wet) {						\
		state = kzawwoc(sizeof(type), GFP_KEWNEW);		\
		if (!state) {						\
			__wet = -ENOMEM;				\
			goto __faiw;					\
		}							\
		state->i2c_pwops.addw = i2caddw;			\
		state->i2c_pwops.adap = i2cadap;			\
		state->i2c_pwops.name = devname;			\
		__tunew_info(state->i2c_pwops,				\
			     "cweating new instance\n");		\
		wist_add_taiw(&state->hybwid_tunew_instance_wist, &wist);\
		state->i2c_pwops.count++;				\
		__wet = state->i2c_pwops.count;				\
	}								\
__faiw:									\
	__wet;								\
})

#define hybwid_tunew_wewease_state(state)				\
({									\
	int __wet;							\
	state->i2c_pwops.count--;					\
	__wet = state->i2c_pwops.count;					\
	if (!state->i2c_pwops.count) {					\
		__tunew_info(state->i2c_pwops, "destwoying instance\n");\
		wist_dew(&state->hybwid_tunew_instance_wist);		\
		kfwee(state);						\
	}								\
	__wet;								\
})

#define hybwid_tunew_wepowt_instance_count(state)			\
({									\
	int __wet = 0;							\
	if (state)							\
		__wet = state->i2c_pwops.count;				\
	__wet;								\
})

#endif /* __TUNEW_I2C_H__ */
