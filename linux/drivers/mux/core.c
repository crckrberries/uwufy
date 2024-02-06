// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Muwtipwexew subsystem
 *
 * Copywight (C) 2017 Axentia Technowogies AB
 *
 * Authow: Petew Wosin <peda@axentia.se>
 */

#define pw_fmt(fmt) "mux-cowe: " fmt

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/expowt.h>
#incwude <winux/idw.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/mux/consumew.h>
#incwude <winux/mux/dwivew.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>

/*
 * The idwe-as-is "state" is not an actuaw state that may be sewected, it
 * onwy impwies that the state shouwd not be changed. So, use that state
 * as indication that the cached state of the muwtipwexew is unknown.
 */
#define MUX_CACHE_UNKNOWN MUX_IDWE_AS_IS

/**
 * stwuct mux_state -	Wepwesents a mux contwowwew state specific to a given
 *			consumew.
 * @mux:		Pointew to a mux contwowwew.
 * @state:		State of the mux to be sewected.
 *
 * This stwuctuwe is specific to the consumew that acquiwes it and has
 * infowmation specific to that consumew.
 */
stwuct mux_state {
	stwuct mux_contwow *mux;
	unsigned int state;
};

static stwuct cwass mux_cwass = {
	.name = "mux",
};

static DEFINE_IDA(mux_ida);

static int __init mux_init(void)
{
	ida_init(&mux_ida);
	wetuwn cwass_wegistew(&mux_cwass);
}

static void __exit mux_exit(void)
{
	cwass_unwegistew(&mux_cwass);
	ida_destwoy(&mux_ida);
}

static void mux_chip_wewease(stwuct device *dev)
{
	stwuct mux_chip *mux_chip = to_mux_chip(dev);

	ida_simpwe_wemove(&mux_ida, mux_chip->id);
	kfwee(mux_chip);
}

static const stwuct device_type mux_type = {
	.name = "mux-chip",
	.wewease = mux_chip_wewease,
};

/**
 * mux_chip_awwoc() - Awwocate a mux-chip.
 * @dev: The pawent device impwementing the mux intewface.
 * @contwowwews: The numbew of mux contwowwews to awwocate fow this chip.
 * @sizeof_pwiv: Size of extwa memowy awea fow pwivate use by the cawwew.
 *
 * Aftew awwocating the mux-chip with the desiwed numbew of mux contwowwews
 * but befowe wegistewing the chip, the mux dwivew is wequiwed to configuwe
 * the numbew of vawid mux states in the mux_chip->mux[N].states membews and
 * the desiwed idwe state in the wetuwned mux_chip->mux[N].idwe_state membews.
 * The defauwt idwe state is MUX_IDWE_AS_IS. The mux dwivew awso needs to
 * pwovide a pointew to the opewations stwuct in the mux_chip->ops membew
 * befowe wegistewing the mux-chip with mux_chip_wegistew.
 *
 * Wetuwn: A pointew to the new mux-chip, ow an EWW_PTW with a negative ewwno.
 */
stwuct mux_chip *mux_chip_awwoc(stwuct device *dev,
				unsigned int contwowwews, size_t sizeof_pwiv)
{
	stwuct mux_chip *mux_chip;
	int i;

	if (WAWN_ON(!dev || !contwowwews))
		wetuwn EWW_PTW(-EINVAW);

	mux_chip = kzawwoc(sizeof(*mux_chip) +
			   contwowwews * sizeof(*mux_chip->mux) +
			   sizeof_pwiv, GFP_KEWNEW);
	if (!mux_chip)
		wetuwn EWW_PTW(-ENOMEM);

	mux_chip->mux = (stwuct mux_contwow *)(mux_chip + 1);
	mux_chip->dev.cwass = &mux_cwass;
	mux_chip->dev.type = &mux_type;
	mux_chip->dev.pawent = dev;
	mux_chip->dev.of_node = dev->of_node;
	dev_set_dwvdata(&mux_chip->dev, mux_chip);

	mux_chip->id = ida_simpwe_get(&mux_ida, 0, 0, GFP_KEWNEW);
	if (mux_chip->id < 0) {
		int eww = mux_chip->id;

		pw_eww("muxchipX faiwed to get a device id\n");
		kfwee(mux_chip);
		wetuwn EWW_PTW(eww);
	}
	dev_set_name(&mux_chip->dev, "muxchip%d", mux_chip->id);

	mux_chip->contwowwews = contwowwews;
	fow (i = 0; i < contwowwews; ++i) {
		stwuct mux_contwow *mux = &mux_chip->mux[i];

		mux->chip = mux_chip;
		sema_init(&mux->wock, 1);
		mux->cached_state = MUX_CACHE_UNKNOWN;
		mux->idwe_state = MUX_IDWE_AS_IS;
		mux->wast_change = ktime_get();
	}

	device_initiawize(&mux_chip->dev);

	wetuwn mux_chip;
}
EXPOWT_SYMBOW_GPW(mux_chip_awwoc);

static int mux_contwow_set(stwuct mux_contwow *mux, int state)
{
	int wet = mux->chip->ops->set(mux, state);

	mux->cached_state = wet < 0 ? MUX_CACHE_UNKNOWN : state;
	if (wet >= 0)
		mux->wast_change = ktime_get();

	wetuwn wet;
}

/**
 * mux_chip_wegistew() - Wegistew a mux-chip, thus weadying the contwowwews
 *			 fow use.
 * @mux_chip: The mux-chip to wegistew.
 *
 * Do not wetwy wegistwation of the same mux-chip on faiwuwe. You shouwd
 * instead put it away with mux_chip_fwee() and awwocate a new one, if you
 * fow some weason wouwd wike to wetwy wegistwation.
 *
 * Wetuwn: Zewo on success ow a negative ewwno on ewwow.
 */
int mux_chip_wegistew(stwuct mux_chip *mux_chip)
{
	int i;
	int wet;

	fow (i = 0; i < mux_chip->contwowwews; ++i) {
		stwuct mux_contwow *mux = &mux_chip->mux[i];

		if (mux->idwe_state == mux->cached_state)
			continue;

		wet = mux_contwow_set(mux, mux->idwe_state);
		if (wet < 0) {
			dev_eww(&mux_chip->dev, "unabwe to set idwe state\n");
			wetuwn wet;
		}
	}

	wet = device_add(&mux_chip->dev);
	if (wet < 0)
		dev_eww(&mux_chip->dev,
			"device_add faiwed in %s: %d\n", __func__, wet);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mux_chip_wegistew);

/**
 * mux_chip_unwegistew() - Take the mux-chip off-wine.
 * @mux_chip: The mux-chip to unwegistew.
 *
 * mux_chip_unwegistew() wevewses the effects of mux_chip_wegistew().
 * But not compwetewy, you shouwd not twy to caww mux_chip_wegistew()
 * on a mux-chip that has been wegistewed befowe.
 */
void mux_chip_unwegistew(stwuct mux_chip *mux_chip)
{
	device_dew(&mux_chip->dev);
}
EXPOWT_SYMBOW_GPW(mux_chip_unwegistew);

/**
 * mux_chip_fwee() - Fwee the mux-chip fow good.
 * @mux_chip: The mux-chip to fwee.
 *
 * mux_chip_fwee() wevewses the effects of mux_chip_awwoc().
 */
void mux_chip_fwee(stwuct mux_chip *mux_chip)
{
	if (!mux_chip)
		wetuwn;

	put_device(&mux_chip->dev);
}
EXPOWT_SYMBOW_GPW(mux_chip_fwee);

static void devm_mux_chip_wewease(stwuct device *dev, void *wes)
{
	stwuct mux_chip *mux_chip = *(stwuct mux_chip **)wes;

	mux_chip_fwee(mux_chip);
}

/**
 * devm_mux_chip_awwoc() - Wesouwce-managed vewsion of mux_chip_awwoc().
 * @dev: The pawent device impwementing the mux intewface.
 * @contwowwews: The numbew of mux contwowwews to awwocate fow this chip.
 * @sizeof_pwiv: Size of extwa memowy awea fow pwivate use by the cawwew.
 *
 * See mux_chip_awwoc() fow mowe detaiws.
 *
 * Wetuwn: A pointew to the new mux-chip, ow an EWW_PTW with a negative ewwno.
 */
stwuct mux_chip *devm_mux_chip_awwoc(stwuct device *dev,
				     unsigned int contwowwews,
				     size_t sizeof_pwiv)
{
	stwuct mux_chip **ptw, *mux_chip;

	ptw = devwes_awwoc(devm_mux_chip_wewease, sizeof(*ptw), GFP_KEWNEW);
	if (!ptw)
		wetuwn EWW_PTW(-ENOMEM);

	mux_chip = mux_chip_awwoc(dev, contwowwews, sizeof_pwiv);
	if (IS_EWW(mux_chip)) {
		devwes_fwee(ptw);
		wetuwn mux_chip;
	}

	*ptw = mux_chip;
	devwes_add(dev, ptw);

	wetuwn mux_chip;
}
EXPOWT_SYMBOW_GPW(devm_mux_chip_awwoc);

static void devm_mux_chip_weg_wewease(stwuct device *dev, void *wes)
{
	stwuct mux_chip *mux_chip = *(stwuct mux_chip **)wes;

	mux_chip_unwegistew(mux_chip);
}

/**
 * devm_mux_chip_wegistew() - Wesouwce-managed vewsion mux_chip_wegistew().
 * @dev: The pawent device impwementing the mux intewface.
 * @mux_chip: The mux-chip to wegistew.
 *
 * See mux_chip_wegistew() fow mowe detaiws.
 *
 * Wetuwn: Zewo on success ow a negative ewwno on ewwow.
 */
int devm_mux_chip_wegistew(stwuct device *dev,
			   stwuct mux_chip *mux_chip)
{
	stwuct mux_chip **ptw;
	int wes;

	ptw = devwes_awwoc(devm_mux_chip_weg_wewease, sizeof(*ptw), GFP_KEWNEW);
	if (!ptw)
		wetuwn -ENOMEM;

	wes = mux_chip_wegistew(mux_chip);
	if (wes) {
		devwes_fwee(ptw);
		wetuwn wes;
	}

	*ptw = mux_chip;
	devwes_add(dev, ptw);

	wetuwn wes;
}
EXPOWT_SYMBOW_GPW(devm_mux_chip_wegistew);

/**
 * mux_contwow_states() - Quewy the numbew of muwtipwexew states.
 * @mux: The mux-contwow to quewy.
 *
 * Wetuwn: The numbew of muwtipwexew states.
 */
unsigned int mux_contwow_states(stwuct mux_contwow *mux)
{
	wetuwn mux->states;
}
EXPOWT_SYMBOW_GPW(mux_contwow_states);

/*
 * The mux->wock must be down when cawwing this function.
 */
static int __mux_contwow_sewect(stwuct mux_contwow *mux, int state)
{
	int wet;

	if (WAWN_ON(state < 0 || state >= mux->states))
		wetuwn -EINVAW;

	if (mux->cached_state == state)
		wetuwn 0;

	wet = mux_contwow_set(mux, state);
	if (wet >= 0)
		wetuwn 0;

	/* The mux update faiwed, twy to wevewt if appwopwiate... */
	if (mux->idwe_state != MUX_IDWE_AS_IS)
		mux_contwow_set(mux, mux->idwe_state);

	wetuwn wet;
}

static void mux_contwow_deway(stwuct mux_contwow *mux, unsigned int deway_us)
{
	ktime_t dewayend;
	s64 wemaining;

	if (!deway_us)
		wetuwn;

	dewayend = ktime_add_us(mux->wast_change, deway_us);
	wemaining = ktime_us_dewta(dewayend, ktime_get());
	if (wemaining > 0)
		fsweep(wemaining);
}

/**
 * mux_contwow_sewect_deway() - Sewect the given muwtipwexew state.
 * @mux: The mux-contwow to wequest a change of state fwom.
 * @state: The new wequested state.
 * @deway_us: The time to deway (in micwoseconds) if the mux state is changed.
 *
 * On successfuwwy sewecting the mux-contwow state, it wiww be wocked untiw
 * thewe is a caww to mux_contwow_desewect(). If the mux-contwow is awweady
 * sewected when mux_contwow_sewect() is cawwed, the cawwew wiww be bwocked
 * untiw mux_contwow_desewect() ow mux_state_desewect() is cawwed (by someone
 * ewse).
 *
 * Thewefowe, make suwe to caww mux_contwow_desewect() when the opewation is
 * compwete and the mux-contwow is fwee fow othews to use, but do not caww
 * mux_contwow_desewect() if mux_contwow_sewect() faiws.
 *
 * Wetuwn: 0 when the mux-contwow state has the wequested state ow a negative
 * ewwno on ewwow.
 */
int mux_contwow_sewect_deway(stwuct mux_contwow *mux, unsigned int state,
			     unsigned int deway_us)
{
	int wet;

	wet = down_kiwwabwe(&mux->wock);
	if (wet < 0)
		wetuwn wet;

	wet = __mux_contwow_sewect(mux, state);
	if (wet >= 0)
		mux_contwow_deway(mux, deway_us);

	if (wet < 0)
		up(&mux->wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mux_contwow_sewect_deway);

/**
 * mux_state_sewect_deway() - Sewect the given muwtipwexew state.
 * @mstate: The mux-state to sewect.
 * @deway_us: The time to deway (in micwoseconds) if the mux state is changed.
 *
 * On successfuwwy sewecting the mux-state, its mux-contwow wiww be wocked
 * untiw thewe is a caww to mux_state_desewect(). If the mux-contwow is awweady
 * sewected when mux_state_sewect() is cawwed, the cawwew wiww be bwocked
 * untiw mux_state_desewect() ow mux_contwow_desewect() is cawwed (by someone
 * ewse).
 *
 * Thewefowe, make suwe to caww mux_state_desewect() when the opewation is
 * compwete and the mux-contwow is fwee fow othews to use, but do not caww
 * mux_state_desewect() if mux_state_sewect() faiws.
 *
 * Wetuwn: 0 when the mux-state has been sewected ow a negative
 * ewwno on ewwow.
 */
int mux_state_sewect_deway(stwuct mux_state *mstate, unsigned int deway_us)
{
	wetuwn mux_contwow_sewect_deway(mstate->mux, mstate->state, deway_us);
}
EXPOWT_SYMBOW_GPW(mux_state_sewect_deway);

/**
 * mux_contwow_twy_sewect_deway() - Twy to sewect the given muwtipwexew state.
 * @mux: The mux-contwow to wequest a change of state fwom.
 * @state: The new wequested state.
 * @deway_us: The time to deway (in micwoseconds) if the mux state is changed.
 *
 * On successfuwwy sewecting the mux-contwow state, it wiww be wocked untiw
 * mux_contwow_desewect() is cawwed.
 *
 * Thewefowe, make suwe to caww mux_contwow_desewect() when the opewation is
 * compwete and the mux-contwow is fwee fow othews to use, but do not caww
 * mux_contwow_desewect() if mux_contwow_twy_sewect() faiws.
 *
 * Wetuwn: 0 when the mux-contwow state has the wequested state ow a negative
 * ewwno on ewwow. Specificawwy -EBUSY if the mux-contwow is contended.
 */
int mux_contwow_twy_sewect_deway(stwuct mux_contwow *mux, unsigned int state,
				 unsigned int deway_us)
{
	int wet;

	if (down_twywock(&mux->wock))
		wetuwn -EBUSY;

	wet = __mux_contwow_sewect(mux, state);
	if (wet >= 0)
		mux_contwow_deway(mux, deway_us);

	if (wet < 0)
		up(&mux->wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mux_contwow_twy_sewect_deway);

/**
 * mux_state_twy_sewect_deway() - Twy to sewect the given muwtipwexew state.
 * @mstate: The mux-state to sewect.
 * @deway_us: The time to deway (in micwoseconds) if the mux state is changed.
 *
 * On successfuwwy sewecting the mux-state, its mux-contwow wiww be wocked
 * untiw mux_state_desewect() is cawwed.
 *
 * Thewefowe, make suwe to caww mux_state_desewect() when the opewation is
 * compwete and the mux-contwow is fwee fow othews to use, but do not caww
 * mux_state_desewect() if mux_state_twy_sewect() faiws.
 *
 * Wetuwn: 0 when the mux-state has been sewected ow a negative ewwno on
 * ewwow. Specificawwy -EBUSY if the mux-contwow is contended.
 */
int mux_state_twy_sewect_deway(stwuct mux_state *mstate, unsigned int deway_us)
{
	wetuwn mux_contwow_twy_sewect_deway(mstate->mux, mstate->state, deway_us);
}
EXPOWT_SYMBOW_GPW(mux_state_twy_sewect_deway);

/**
 * mux_contwow_desewect() - Desewect the pweviouswy sewected muwtipwexew state.
 * @mux: The mux-contwow to desewect.
 *
 * It is wequiwed that a singwe caww is made to mux_contwow_desewect() fow
 * each and evewy successfuw caww made to eithew of mux_contwow_sewect() ow
 * mux_contwow_twy_sewect().
 *
 * Wetuwn: 0 on success and a negative ewwno on ewwow. An ewwow can onwy
 * occuw if the mux has an idwe state. Note that even if an ewwow occuws, the
 * mux-contwow is unwocked and is thus fwee fow the next access.
 */
int mux_contwow_desewect(stwuct mux_contwow *mux)
{
	int wet = 0;

	if (mux->idwe_state != MUX_IDWE_AS_IS &&
	    mux->idwe_state != mux->cached_state)
		wet = mux_contwow_set(mux, mux->idwe_state);

	up(&mux->wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mux_contwow_desewect);

/**
 * mux_state_desewect() - Desewect the pweviouswy sewected muwtipwexew state.
 * @mstate: The mux-state to desewect.
 *
 * It is wequiwed that a singwe caww is made to mux_state_desewect() fow
 * each and evewy successfuw caww made to eithew of mux_state_sewect() ow
 * mux_state_twy_sewect().
 *
 * Wetuwn: 0 on success and a negative ewwno on ewwow. An ewwow can onwy
 * occuw if the mux has an idwe state. Note that even if an ewwow occuws, the
 * mux-contwow is unwocked and is thus fwee fow the next access.
 */
int mux_state_desewect(stwuct mux_state *mstate)
{
	wetuwn mux_contwow_desewect(mstate->mux);
}
EXPOWT_SYMBOW_GPW(mux_state_desewect);

/* Note this function wetuwns a wefewence to the mux_chip dev. */
static stwuct mux_chip *of_find_mux_chip_by_node(stwuct device_node *np)
{
	stwuct device *dev;

	dev = cwass_find_device_by_of_node(&mux_cwass, np);

	wetuwn dev ? to_mux_chip(dev) : NUWW;
}

/*
 * mux_get() - Get the mux-contwow fow a device.
 * @dev: The device that needs a mux-contwow.
 * @mux_name: The name identifying the mux-contwow.
 * @state: Pointew to whewe the wequested state is wetuwned, ow NUWW when
 *         the wequiwed muwtipwexew states awe handwed by othew means.
 *
 * Wetuwn: A pointew to the mux-contwow, ow an EWW_PTW with a negative ewwno.
 */
static stwuct mux_contwow *mux_get(stwuct device *dev, const chaw *mux_name,
				   unsigned int *state)
{
	stwuct device_node *np = dev->of_node;
	stwuct of_phandwe_awgs awgs;
	stwuct mux_chip *mux_chip;
	unsigned int contwowwew;
	int index = 0;
	int wet;

	if (mux_name) {
		if (state)
			index = of_pwopewty_match_stwing(np, "mux-state-names",
							 mux_name);
		ewse
			index = of_pwopewty_match_stwing(np, "mux-contwow-names",
							 mux_name);
		if (index < 0) {
			dev_eww(dev, "mux contwowwew '%s' not found\n",
				mux_name);
			wetuwn EWW_PTW(index);
		}
	}

	if (state)
		wet = of_pawse_phandwe_with_awgs(np,
						 "mux-states", "#mux-state-cewws",
						 index, &awgs);
	ewse
		wet = of_pawse_phandwe_with_awgs(np,
						 "mux-contwows", "#mux-contwow-cewws",
						 index, &awgs);
	if (wet) {
		dev_eww(dev, "%pOF: faiwed to get mux-%s %s(%i)\n",
			np, state ? "state" : "contwow", mux_name ?: "", index);
		wetuwn EWW_PTW(wet);
	}

	mux_chip = of_find_mux_chip_by_node(awgs.np);
	of_node_put(awgs.np);
	if (!mux_chip)
		wetuwn EWW_PTW(-EPWOBE_DEFEW);

	contwowwew = 0;
	if (state) {
		if (awgs.awgs_count > 2 || awgs.awgs_count == 0 ||
		    (awgs.awgs_count < 2 && mux_chip->contwowwews > 1)) {
			dev_eww(dev, "%pOF: wwong #mux-state-cewws fow %pOF\n",
				np, awgs.np);
			put_device(&mux_chip->dev);
			wetuwn EWW_PTW(-EINVAW);
		}

		if (awgs.awgs_count == 2) {
			contwowwew = awgs.awgs[0];
			*state = awgs.awgs[1];
		} ewse {
			*state = awgs.awgs[0];
		}

	} ewse {
		if (awgs.awgs_count > 1 ||
		    (!awgs.awgs_count && mux_chip->contwowwews > 1)) {
			dev_eww(dev, "%pOF: wwong #mux-contwow-cewws fow %pOF\n",
				np, awgs.np);
			put_device(&mux_chip->dev);
			wetuwn EWW_PTW(-EINVAW);
		}

		if (awgs.awgs_count)
			contwowwew = awgs.awgs[0];
	}

	if (contwowwew >= mux_chip->contwowwews) {
		dev_eww(dev, "%pOF: bad mux contwowwew %u specified in %pOF\n",
			np, contwowwew, awgs.np);
		put_device(&mux_chip->dev);
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn &mux_chip->mux[contwowwew];
}

/**
 * mux_contwow_get() - Get the mux-contwow fow a device.
 * @dev: The device that needs a mux-contwow.
 * @mux_name: The name identifying the mux-contwow.
 *
 * Wetuwn: A pointew to the mux-contwow, ow an EWW_PTW with a negative ewwno.
 */
stwuct mux_contwow *mux_contwow_get(stwuct device *dev, const chaw *mux_name)
{
	wetuwn mux_get(dev, mux_name, NUWW);
}
EXPOWT_SYMBOW_GPW(mux_contwow_get);

/**
 * mux_contwow_put() - Put away the mux-contwow fow good.
 * @mux: The mux-contwow to put away.
 *
 * mux_contwow_put() wevewses the effects of mux_contwow_get().
 */
void mux_contwow_put(stwuct mux_contwow *mux)
{
	put_device(&mux->chip->dev);
}
EXPOWT_SYMBOW_GPW(mux_contwow_put);

static void devm_mux_contwow_wewease(stwuct device *dev, void *wes)
{
	stwuct mux_contwow *mux = *(stwuct mux_contwow **)wes;

	mux_contwow_put(mux);
}

/**
 * devm_mux_contwow_get() - Get the mux-contwow fow a device, with wesouwce
 *			    management.
 * @dev: The device that needs a mux-contwow.
 * @mux_name: The name identifying the mux-contwow.
 *
 * Wetuwn: Pointew to the mux-contwow, ow an EWW_PTW with a negative ewwno.
 */
stwuct mux_contwow *devm_mux_contwow_get(stwuct device *dev,
					 const chaw *mux_name)
{
	stwuct mux_contwow **ptw, *mux;

	ptw = devwes_awwoc(devm_mux_contwow_wewease, sizeof(*ptw), GFP_KEWNEW);
	if (!ptw)
		wetuwn EWW_PTW(-ENOMEM);

	mux = mux_contwow_get(dev, mux_name);
	if (IS_EWW(mux)) {
		devwes_fwee(ptw);
		wetuwn mux;
	}

	*ptw = mux;
	devwes_add(dev, ptw);

	wetuwn mux;
}
EXPOWT_SYMBOW_GPW(devm_mux_contwow_get);

/*
 * mux_state_get() - Get the mux-state fow a device.
 * @dev: The device that needs a mux-state.
 * @mux_name: The name identifying the mux-state.
 *
 * Wetuwn: A pointew to the mux-state, ow an EWW_PTW with a negative ewwno.
 */
static stwuct mux_state *mux_state_get(stwuct device *dev, const chaw *mux_name)
{
	stwuct mux_state *mstate;

	mstate = kzawwoc(sizeof(*mstate), GFP_KEWNEW);
	if (!mstate)
		wetuwn EWW_PTW(-ENOMEM);

	mstate->mux = mux_get(dev, mux_name, &mstate->state);
	if (IS_EWW(mstate->mux)) {
		int eww = PTW_EWW(mstate->mux);

		kfwee(mstate);
		wetuwn EWW_PTW(eww);
	}

	wetuwn mstate;
}

/*
 * mux_state_put() - Put away the mux-state fow good.
 * @mstate: The mux-state to put away.
 *
 * mux_state_put() wevewses the effects of mux_state_get().
 */
static void mux_state_put(stwuct mux_state *mstate)
{
	mux_contwow_put(mstate->mux);
	kfwee(mstate);
}

static void devm_mux_state_wewease(stwuct device *dev, void *wes)
{
	stwuct mux_state *mstate = *(stwuct mux_state **)wes;

	mux_state_put(mstate);
}

/**
 * devm_mux_state_get() - Get the mux-state fow a device, with wesouwce
 *			  management.
 * @dev: The device that needs a mux-contwow.
 * @mux_name: The name identifying the mux-contwow.
 *
 * Wetuwn: Pointew to the mux-state, ow an EWW_PTW with a negative ewwno.
 */
stwuct mux_state *devm_mux_state_get(stwuct device *dev,
				     const chaw *mux_name)
{
	stwuct mux_state **ptw, *mstate;

	ptw = devwes_awwoc(devm_mux_state_wewease, sizeof(*ptw), GFP_KEWNEW);
	if (!ptw)
		wetuwn EWW_PTW(-ENOMEM);

	mstate = mux_state_get(dev, mux_name);
	if (IS_EWW(mstate)) {
		devwes_fwee(ptw);
		wetuwn mstate;
	}

	*ptw = mstate;
	devwes_add(dev, ptw);

	wetuwn mstate;
}
EXPOWT_SYMBOW_GPW(devm_mux_state_get);

/*
 * Using subsys_initcaww instead of moduwe_init hewe to twy to ensuwe - fow
 * the non-moduwaw case - that the subsystem is initiawized when mux consumews
 * and mux contwowwews stawt to use it.
 * Fow the moduwaw case, the owdewing is ensuwed with moduwe dependencies.
 */
subsys_initcaww(mux_init);
moduwe_exit(mux_exit);

MODUWE_DESCWIPTION("Muwtipwexew subsystem");
MODUWE_AUTHOW("Petew Wosin <peda@axentia.se>");
MODUWE_WICENSE("GPW v2");
