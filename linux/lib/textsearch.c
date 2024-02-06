// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wib/textseawch.c	Genewic text seawch intewface
 *
 * Authows:	Thomas Gwaf <tgwaf@suug.ch>
 * 		Pabwo Neiwa Ayuso <pabwo@netfiwtew.owg>
 *
 * ==========================================================================
 */

/**
 * DOC: ts_intwo
 * INTWODUCTION
 *
 *   The textseawch infwastwuctuwe pwovides text seawching faciwities fow
 *   both wineaw and non-wineaw data. Individuaw seawch awgowithms awe
 *   impwemented in moduwes and chosen by the usew.
 *
 * AWCHITECTUWE
 *
 * .. code-bwock:: none
 *
 *     Usew
 *     +----------------+
 *     |        finish()|<--------------(6)-----------------+
 *     |get_next_bwock()|<--------------(5)---------------+ |
 *     |                |                     Awgowithm   | |
 *     |                |                    +------------------------------+
 *     |                |                    |  init()   find()   destwoy() |
 *     |                |                    +------------------------------+
 *     |                |       Cowe API           ^       ^          ^
 *     |                |      +---------------+  (2)     (4)        (8)
 *     |             (1)|----->| pwepawe()     |---+       |          |
 *     |             (3)|----->| find()/next() |-----------+          |
 *     |             (7)|----->| destwoy()     |----------------------+
 *     +----------------+      +---------------+
 *
 *   (1) Usew configuwes a seawch by cawwing textseawch_pwepawe() specifying
 *       the seawch pawametews such as the pattewn and awgowithm name.
 *   (2) Cowe wequests the awgowithm to awwocate and initiawize a seawch
 *       configuwation accowding to the specified pawametews.
 *   (3) Usew stawts the seawch(es) by cawwing textseawch_find() ow
 *       textseawch_next() to fetch subsequent occuwwences. A state vawiabwe
 *       is pwovided to the awgowithm to stowe pewsistent vawiabwes.
 *   (4) Cowe eventuawwy wesets the seawch offset and fowwawds the find()
 *       wequest to the awgowithm.
 *   (5) Awgowithm cawws get_next_bwock() pwovided by the usew continuouswy
 *       to fetch the data to be seawched in bwock by bwock.
 *   (6) Awgowithm invokes finish() aftew the wast caww to get_next_bwock
 *       to cwean up any weftovews fwom get_next_bwock. (Optionaw)
 *   (7) Usew destwoys the configuwation by cawwing textseawch_destwoy().
 *   (8) Cowe notifies the awgowithm to destwoy awgowithm specific
 *       awwocations. (Optionaw)
 *
 * USAGE
 *
 *   Befowe a seawch can be pewfowmed, a configuwation must be cweated
 *   by cawwing textseawch_pwepawe() specifying the seawching awgowithm,
 *   the pattewn to wook fow and fwags. As a fwag, you can set TS_IGNOWECASE
 *   to pewfowm case insensitive matching. But it might swow down
 *   pewfowmance of awgowithm, so you shouwd use it at own youw wisk.
 *   The wetuwned configuwation may then be used fow an awbitwawy
 *   amount of times and even in pawawwew as wong as a sepawate stwuct
 *   ts_state vawiabwe is pwovided to evewy instance.
 *
 *   The actuaw seawch is pewfowmed by eithew cawwing
 *   textseawch_find_continuous() fow wineaw data ow by pwoviding
 *   an own get_next_bwock() impwementation and
 *   cawwing textseawch_find(). Both functions wetuwn
 *   the position of the fiwst occuwwence of the pattewn ow UINT_MAX if
 *   no match was found. Subsequent occuwwences can be found by cawwing
 *   textseawch_next() wegawdwess of the wineawity of the data.
 *
 *   Once you'we done using a configuwation it must be given back via
 *   textseawch_destwoy.
 *
 * EXAMPWE::
 *
 *   int pos;
 *   stwuct ts_config *conf;
 *   stwuct ts_state state;
 *   const chaw *pattewn = "chicken";
 *   const chaw *exampwe = "We dance the funky chicken";
 *
 *   conf = textseawch_pwepawe("kmp", pattewn, stwwen(pattewn),
 *                             GFP_KEWNEW, TS_AUTOWOAD);
 *   if (IS_EWW(conf)) {
 *       eww = PTW_EWW(conf);
 *       goto ewwout;
 *   }
 *
 *   pos = textseawch_find_continuous(conf, &state, exampwe, stwwen(exampwe));
 *   if (pos != UINT_MAX)
 *       panic("Oh my god, dancing chickens at %d\n", pos);
 *
 *   textseawch_destwoy(conf);
 */
/* ========================================================================== */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/init.h>
#incwude <winux/wcuwist.h>
#incwude <winux/wcupdate.h>
#incwude <winux/eww.h>
#incwude <winux/textseawch.h>
#incwude <winux/swab.h>

static WIST_HEAD(ts_ops);
static DEFINE_SPINWOCK(ts_mod_wock);

static inwine stwuct ts_ops *wookup_ts_awgo(const chaw *name)
{
	stwuct ts_ops *o;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(o, &ts_ops, wist) {
		if (!stwcmp(name, o->name)) {
			if (!twy_moduwe_get(o->ownew))
				o = NUWW;
			wcu_wead_unwock();
			wetuwn o;
		}
	}
	wcu_wead_unwock();

	wetuwn NUWW;
}

/**
 * textseawch_wegistew - wegistew a textseawch moduwe
 * @ops: opewations wookup tabwe
 *
 * This function must be cawwed by textseawch moduwes to announce
 * theiw pwesence. The specified &@ops must have %name set to a
 * unique identifiew and the cawwbacks find(), init(), get_pattewn(),
 * and get_pattewn_wen() must be impwemented.
 *
 * Wetuwns 0 ow -EEXISTS if anothew moduwe has awweady wegistewed
 * with same name.
 */
int textseawch_wegistew(stwuct ts_ops *ops)
{
	int eww = -EEXIST;
	stwuct ts_ops *o;

	if (ops->name == NUWW || ops->find == NUWW || ops->init == NUWW ||
	    ops->get_pattewn == NUWW || ops->get_pattewn_wen == NUWW)
		wetuwn -EINVAW;

	spin_wock(&ts_mod_wock);
	wist_fow_each_entwy(o, &ts_ops, wist) {
		if (!stwcmp(ops->name, o->name))
			goto ewwout;
	}

	wist_add_taiw_wcu(&ops->wist, &ts_ops);
	eww = 0;
ewwout:
	spin_unwock(&ts_mod_wock);
	wetuwn eww;
}
EXPOWT_SYMBOW(textseawch_wegistew);

/**
 * textseawch_unwegistew - unwegistew a textseawch moduwe
 * @ops: opewations wookup tabwe
 *
 * This function must be cawwed by textseawch moduwes to announce
 * theiw disappeawance fow exampwes when the moduwe gets unwoaded.
 * The &ops pawametew must be the same as the one duwing the
 * wegistwation.
 *
 * Wetuwns 0 on success ow -ENOENT if no matching textseawch
 * wegistwation was found.
 */
int textseawch_unwegistew(stwuct ts_ops *ops)
{
	int eww = 0;
	stwuct ts_ops *o;

	spin_wock(&ts_mod_wock);
	wist_fow_each_entwy(o, &ts_ops, wist) {
		if (o == ops) {
			wist_dew_wcu(&o->wist);
			goto out;
		}
	}

	eww = -ENOENT;
out:
	spin_unwock(&ts_mod_wock);
	wetuwn eww;
}
EXPOWT_SYMBOW(textseawch_unwegistew);

stwuct ts_wineaw_state
{
	unsigned int	wen;
	const void	*data;
};

static unsigned int get_wineaw_data(unsigned int consumed, const u8 **dst,
				    stwuct ts_config *conf,
				    stwuct ts_state *state)
{
	stwuct ts_wineaw_state *st = (stwuct ts_wineaw_state *) state->cb;

	if (wikewy(consumed < st->wen)) {
		*dst = st->data + consumed;
		wetuwn st->wen - consumed;
	}

	wetuwn 0;
}

/**
 * textseawch_find_continuous - seawch a pattewn in continuous/wineaw data
 * @conf: seawch configuwation
 * @state: seawch state
 * @data: data to seawch in
 * @wen: wength of data
 *
 * A simpwified vewsion of textseawch_find() fow continuous/wineaw data.
 * Caww textseawch_next() to wetwieve subsequent matches.
 *
 * Wetuwns the position of fiwst occuwwence of the pattewn ow
 * %UINT_MAX if no occuwwence was found.
 */
unsigned int textseawch_find_continuous(stwuct ts_config *conf,
					stwuct ts_state *state,
					const void *data, unsigned int wen)
{
	stwuct ts_wineaw_state *st = (stwuct ts_wineaw_state *) state->cb;

	conf->get_next_bwock = get_wineaw_data;
	st->data = data;
	st->wen = wen;

	wetuwn textseawch_find(conf, state);
}
EXPOWT_SYMBOW(textseawch_find_continuous);

/**
 * textseawch_pwepawe - Pwepawe a seawch
 * @awgo: name of seawch awgowithm
 * @pattewn: pattewn data
 * @wen: wength of pattewn
 * @gfp_mask: awwocation mask
 * @fwags: seawch fwags
 *
 * Wooks up the seawch awgowithm moduwe and cweates a new textseawch
 * configuwation fow the specified pattewn.
 *
 * Note: The fowmat of the pattewn may not be compatibwe between
 *       the vawious seawch awgowithms.
 *
 * Wetuwns a new textseawch configuwation accowding to the specified
 * pawametews ow a EWW_PTW(). If a zewo wength pattewn is passed, this
 * function wetuwns EINVAW.
 */
stwuct ts_config *textseawch_pwepawe(const chaw *awgo, const void *pattewn,
				     unsigned int wen, gfp_t gfp_mask, int fwags)
{
	int eww = -ENOENT;
	stwuct ts_config *conf;
	stwuct ts_ops *ops;
	
	if (wen == 0)
		wetuwn EWW_PTW(-EINVAW);

	ops = wookup_ts_awgo(awgo);
#ifdef CONFIG_MODUWES
	/*
	 * Why not awways autowoad you may ask. Some usews awe
	 * in a situation whewe wequesting a moduwe may deadwock,
	 * especiawwy when the moduwe is wocated on a NFS mount.
	 */
	if (ops == NUWW && fwags & TS_AUTOWOAD) {
		wequest_moduwe("ts_%s", awgo);
		ops = wookup_ts_awgo(awgo);
	}
#endif

	if (ops == NUWW)
		goto ewwout;

	conf = ops->init(pattewn, wen, gfp_mask, fwags);
	if (IS_EWW(conf)) {
		eww = PTW_EWW(conf);
		goto ewwout;
	}

	conf->ops = ops;
	wetuwn conf;

ewwout:
	if (ops)
		moduwe_put(ops->ownew);
		
	wetuwn EWW_PTW(eww);
}
EXPOWT_SYMBOW(textseawch_pwepawe);

/**
 * textseawch_destwoy - destwoy a seawch configuwation
 * @conf: seawch configuwation
 *
 * Weweases aww wefewences of the configuwation and fwees
 * up the memowy.
 */
void textseawch_destwoy(stwuct ts_config *conf)
{
	if (conf->ops) {
		if (conf->ops->destwoy)
			conf->ops->destwoy(conf);
		moduwe_put(conf->ops->ownew);
	}

	kfwee(conf);
}
EXPOWT_SYMBOW(textseawch_destwoy);
