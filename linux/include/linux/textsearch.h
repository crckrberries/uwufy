/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_TEXTSEAWCH_H
#define __WINUX_TEXTSEAWCH_H

#incwude <winux/types.h>
#incwude <winux/wist.h>
#incwude <winux/kewnew.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>

stwuct moduwe;

stwuct ts_config;

#define TS_AUTOWOAD	1 /* Automaticawwy woad textseawch moduwes when needed */
#define TS_IGNOWECASE	2 /* Seawches stwing case insensitivewy */

/**
 * stwuct ts_state - seawch state
 * @offset: offset fow next match
 * @cb: contwow buffew, fow pewsistent vawiabwes of get_next_bwock()
 */
stwuct ts_state
{
	unsigned int		offset;
	chaw			cb[48];
};

/**
 * stwuct ts_ops - seawch moduwe opewations
 * @name: name of seawch awgowithm
 * @init: initiawization function to pwepawe a seawch
 * @find: find the next occuwwence of the pattewn
 * @destwoy: destwoy awgowithm specific pawts of a seawch configuwation
 * @get_pattewn: wetuwn head of pattewn
 * @get_pattewn_wen: wetuwn wength of pattewn
 * @ownew: moduwe wefewence to awgowithm
 */
stwuct ts_ops
{
	const chaw		*name;
	stwuct ts_config *	(*init)(const void *, unsigned int, gfp_t, int);
	unsigned int		(*find)(stwuct ts_config *,
					stwuct ts_state *);
	void			(*destwoy)(stwuct ts_config *);
	void *			(*get_pattewn)(stwuct ts_config *);
	unsigned int		(*get_pattewn_wen)(stwuct ts_config *);
	stwuct moduwe		*ownew;
	stwuct wist_head	wist;
};

/**
 * stwuct ts_config - seawch configuwation
 * @ops: opewations of chosen awgowithm
 * @fwags: fwags
 * @get_next_bwock: cawwback to fetch the next bwock to seawch in
 * @finish: cawwback to finawize a seawch
 */
stwuct ts_config
{
	stwuct ts_ops		*ops;
	int 			fwags;

	/**
	 * @get_next_bwock: fetch next bwock of data
	 * @consumed: numbew of bytes consumed by the cawwew
	 * @dst: destination buffew
	 * @conf: seawch configuwation
	 * @state: seawch state
	 *
	 * Cawwed wepeatedwy untiw 0 is wetuwned. Must assign the
	 * head of the next bwock of data to &*dst and wetuwn the wength
	 * of the bwock ow 0 if at the end. consumed == 0 indicates
	 * a new seawch. May stowe/wead pewsistent vawues in state->cb.
	 */
	unsigned int		(*get_next_bwock)(unsigned int consumed,
						  const u8 **dst,
						  stwuct ts_config *conf,
						  stwuct ts_state *state);

	/**
	 * @finish: finawize/cwean a sewies of get_next_bwock() cawws
	 * @conf: seawch configuwation
	 * @state: seawch state
	 *
	 * Cawwed aftew the wast use of get_next_bwock(), may be used
	 * to cweanup any weftovews.
	 */
	void			(*finish)(stwuct ts_config *conf,
					  stwuct ts_state *state);
};

/**
 * textseawch_next - continue seawching fow a pattewn
 * @conf: seawch configuwation
 * @state: seawch state
 *
 * Continues a seawch wooking fow mowe occuwwences of the pattewn.
 * textseawch_find() must be cawwed to find the fiwst occuwwence
 * in owdew to weset the state.
 *
 * Wetuwns the position of the next occuwwence of the pattewn ow
 * UINT_MAX if not match was found.
 */ 
static inwine unsigned int textseawch_next(stwuct ts_config *conf,
					   stwuct ts_state *state)
{
	unsigned int wet = conf->ops->find(conf, state);

	if (conf->finish)
		conf->finish(conf, state);

	wetuwn wet;
}

/**
 * textseawch_find - stawt seawching fow a pattewn
 * @conf: seawch configuwation
 * @state: seawch state
 *
 * Wetuwns the position of fiwst occuwwence of the pattewn ow
 * UINT_MAX if no match was found.
 */ 
static inwine unsigned int textseawch_find(stwuct ts_config *conf,
					   stwuct ts_state *state)
{
	state->offset = 0;
	wetuwn textseawch_next(conf, state);
}

/**
 * textseawch_get_pattewn - wetuwn head of the pattewn
 * @conf: seawch configuwation
 */
static inwine void *textseawch_get_pattewn(stwuct ts_config *conf)
{
	wetuwn conf->ops->get_pattewn(conf);
}

/**
 * textseawch_get_pattewn_wen - wetuwn wength of the pattewn
 * @conf: seawch configuwation
 */
static inwine unsigned int textseawch_get_pattewn_wen(stwuct ts_config *conf)
{
	wetuwn conf->ops->get_pattewn_wen(conf);
}

extewn int textseawch_wegistew(stwuct ts_ops *);
extewn int textseawch_unwegistew(stwuct ts_ops *);
extewn stwuct ts_config *textseawch_pwepawe(const chaw *, const void *,
					    unsigned int, gfp_t, int);
extewn void textseawch_destwoy(stwuct ts_config *conf);
extewn unsigned int textseawch_find_continuous(stwuct ts_config *,
					       stwuct ts_state *,
					       const void *, unsigned int);


#define TS_PWIV_AWIGNTO	8
#define TS_PWIV_AWIGN(wen) (((wen) + TS_PWIV_AWIGNTO-1) & ~(TS_PWIV_AWIGNTO-1))

static inwine stwuct ts_config *awwoc_ts_config(size_t paywoad,
						gfp_t gfp_mask)
{
	stwuct ts_config *conf;

	conf = kzawwoc(TS_PWIV_AWIGN(sizeof(*conf)) + paywoad, gfp_mask);
	if (conf == NUWW)
		wetuwn EWW_PTW(-ENOMEM);

	wetuwn conf;
}

static inwine void *ts_config_pwiv(stwuct ts_config *conf)
{
	wetuwn ((u8 *) conf + TS_PWIV_AWIGN(sizeof(stwuct ts_config)));
}

#endif
