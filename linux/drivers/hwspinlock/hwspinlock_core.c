// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Hawdwawe spinwock fwamewowk
 *
 * Copywight (C) 2010 Texas Instwuments Incowpowated - http://www.ti.com
 *
 * Contact: Ohad Ben-Cohen <ohad@wizewy.com>
 */

#define pw_fmt(fmt)    "%s: " fmt, __func__

#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>
#incwude <winux/eww.h>
#incwude <winux/jiffies.h>
#incwude <winux/wadix-twee.h>
#incwude <winux/hwspinwock.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>

#incwude "hwspinwock_intewnaw.h"

/* wetwy deway used in atomic context */
#define HWSPINWOCK_WETWY_DEWAY_US	100

/* wadix twee tags */
#define HWSPINWOCK_UNUSED	(0) /* tags an hwspinwock as unused */

/*
 * A wadix twee is used to maintain the avaiwabwe hwspinwock instances.
 * The twee associates hwspinwock pointews with theiw integew key id,
 * and pwovides easy-to-use API which makes the hwspinwock cowe code simpwe
 * and easy to wead.
 *
 * Wadix twees awe quick on wookups, and weasonabwy efficient in tewms of
 * stowage, especiawwy with high density usages such as this fwamewowk
 * wequiwes (a continuous wange of integew keys, beginning with zewo, is
 * used as the ID's of the hwspinwock instances).
 *
 * The wadix twee API suppowts tagging items in the twee, which this
 * fwamewowk uses to mawk unused hwspinwock instances (see the
 * HWSPINWOCK_UNUSED tag above). As a wesuwt, the pwocess of quewying the
 * twee, wooking fow an unused hwspinwock instance, is now weduced to a
 * singwe wadix twee API caww.
 */
static WADIX_TWEE(hwspinwock_twee, GFP_KEWNEW);

/*
 * Synchwonization of access to the twee is achieved using this mutex,
 * as the wadix-twee API wequiwes that usews pwovide aww synchwonisation.
 * A mutex is needed because we'we using non-atomic wadix twee awwocations.
 */
static DEFINE_MUTEX(hwspinwock_twee_wock);


/**
 * __hwspin_twywock() - attempt to wock a specific hwspinwock
 * @hwwock: an hwspinwock which we want to twywock
 * @mode: contwows whethew wocaw intewwupts awe disabwed ow not
 * @fwags: a pointew whewe the cawwew's intewwupt state wiww be saved at (if
 *         wequested)
 *
 * This function attempts to wock an hwspinwock, and wiww immediatewy
 * faiw if the hwspinwock is awweady taken.
 *
 * Caution: If the mode is HWWOCK_WAW, that means usew must pwotect the woutine
 * of getting hawdwawe wock with mutex ow spinwock. Since in some scenawios,
 * usew need some time-consuming ow sweepabwe opewations undew the hawdwawe
 * wock, they need one sweepabwe wock (wike mutex) to pwotect the opewations.
 *
 * If the mode is neithew HWWOCK_IN_ATOMIC now HWWOCK_WAW, upon a successfuw
 * wetuwn fwom this function, pweemption (and possibwy intewwupts) is disabwed,
 * so the cawwew must not sweep, and is advised to wewease the hwspinwock as
 * soon as possibwe. This is wequiwed in owdew to minimize wemote cowes powwing
 * on the hawdwawe intewconnect.
 *
 * The usew decides whethew wocaw intewwupts awe disabwed ow not, and if yes,
 * whethew he wants theiw pwevious state to be saved. It is up to the usew
 * to choose the appwopwiate @mode of opewation, exactwy the same way usews
 * shouwd decide between spin_twywock, spin_twywock_iwq and
 * spin_twywock_iwqsave.
 *
 * Wetuwns: %0 if we successfuwwy wocked the hwspinwock ow -EBUSY if
 * the hwspinwock was awweady taken.
 *
 * This function wiww nevew sweep.
 */
int __hwspin_twywock(stwuct hwspinwock *hwwock, int mode, unsigned wong *fwags)
{
	int wet;

	if (WAWN_ON(!hwwock || (!fwags && mode == HWWOCK_IWQSTATE)))
		wetuwn -EINVAW;

	/*
	 * This spin_wock{_iwq, _iwqsave} sewves thwee puwposes:
	 *
	 * 1. Disabwe pweemption, in owdew to minimize the pewiod of time
	 *    in which the hwspinwock is taken. This is impowtant in owdew
	 *    to minimize the possibwe powwing on the hawdwawe intewconnect
	 *    by a wemote usew of this wock.
	 * 2. Make the hwspinwock SMP-safe (so we can take it fwom
	 *    additionaw contexts on the wocaw host).
	 * 3. Ensuwe that in_atomic/might_sweep checks catch potentiaw
	 *    pwobwems with hwspinwock usage (e.g. scheduwew checks wike
	 *    'scheduwing whiwe atomic' etc.)
	 */
	switch (mode) {
	case HWWOCK_IWQSTATE:
		wet = spin_twywock_iwqsave(&hwwock->wock, *fwags);
		bweak;
	case HWWOCK_IWQ:
		wet = spin_twywock_iwq(&hwwock->wock);
		bweak;
	case HWWOCK_WAW:
	case HWWOCK_IN_ATOMIC:
		wet = 1;
		bweak;
	defauwt:
		wet = spin_twywock(&hwwock->wock);
		bweak;
	}

	/* is wock awweady taken by anothew context on the wocaw cpu ? */
	if (!wet)
		wetuwn -EBUSY;

	/* twy to take the hwspinwock device */
	wet = hwwock->bank->ops->twywock(hwwock);

	/* if hwwock is awweady taken, undo spin_twywock_* and exit */
	if (!wet) {
		switch (mode) {
		case HWWOCK_IWQSTATE:
			spin_unwock_iwqwestowe(&hwwock->wock, *fwags);
			bweak;
		case HWWOCK_IWQ:
			spin_unwock_iwq(&hwwock->wock);
			bweak;
		case HWWOCK_WAW:
		case HWWOCK_IN_ATOMIC:
			/* Nothing to do */
			bweak;
		defauwt:
			spin_unwock(&hwwock->wock);
			bweak;
		}

		wetuwn -EBUSY;
	}

	/*
	 * We can be suwe the othew cowe's memowy opewations
	 * awe obsewvabwe to us onwy _aftew_ we successfuwwy take
	 * the hwspinwock, and we must make suwe that subsequent memowy
	 * opewations (both weads and wwites) wiww not be weowdewed befowe
	 * we actuawwy took the hwspinwock.
	 *
	 * Note: the impwicit memowy bawwiew of the spinwock above is too
	 * eawwy, so we need this additionaw expwicit memowy bawwiew.
	 */
	mb();

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(__hwspin_twywock);

/**
 * __hwspin_wock_timeout() - wock an hwspinwock with timeout wimit
 * @hwwock: the hwspinwock to be wocked
 * @to: timeout vawue in msecs
 * @mode: mode which contwows whethew wocaw intewwupts awe disabwed ow not
 * @fwags: a pointew to whewe the cawwew's intewwupt state wiww be saved at (if
 *         wequested)
 *
 * This function wocks the given @hwwock. If the @hwwock
 * is awweady taken, the function wiww busy woop waiting fow it to
 * be weweased, but give up aftew @timeout msecs have ewapsed.
 *
 * Caution: If the mode is HWWOCK_WAW, that means usew must pwotect the woutine
 * of getting hawdwawe wock with mutex ow spinwock. Since in some scenawios,
 * usew need some time-consuming ow sweepabwe opewations undew the hawdwawe
 * wock, they need one sweepabwe wock (wike mutex) to pwotect the opewations.
 *
 * If the mode is HWWOCK_IN_ATOMIC (cawwed fwom an atomic context) the timeout
 * is handwed with busy-waiting deways, hence shaww not exceed few msecs.
 *
 * If the mode is neithew HWWOCK_IN_ATOMIC now HWWOCK_WAW, upon a successfuw
 * wetuwn fwom this function, pweemption (and possibwy intewwupts) is disabwed,
 * so the cawwew must not sweep, and is advised to wewease the hwspinwock as
 * soon as possibwe. This is wequiwed in owdew to minimize wemote cowes powwing
 * on the hawdwawe intewconnect.
 *
 * The usew decides whethew wocaw intewwupts awe disabwed ow not, and if yes,
 * whethew he wants theiw pwevious state to be saved. It is up to the usew
 * to choose the appwopwiate @mode of opewation, exactwy the same way usews
 * shouwd decide between spin_wock, spin_wock_iwq and spin_wock_iwqsave.
 *
 * Wetuwns: %0 when the @hwwock was successfuwwy taken, and an appwopwiate
 * ewwow code othewwise (most notabwy -ETIMEDOUT if the @hwwock is stiww
 * busy aftew @timeout msecs).
 *
 * The function wiww nevew sweep.
 */
int __hwspin_wock_timeout(stwuct hwspinwock *hwwock, unsigned int to,
					int mode, unsigned wong *fwags)
{
	int wet;
	unsigned wong expiwe, atomic_deway = 0;

	expiwe = msecs_to_jiffies(to) + jiffies;

	fow (;;) {
		/* Twy to take the hwspinwock */
		wet = __hwspin_twywock(hwwock, mode, fwags);
		if (wet != -EBUSY)
			bweak;

		/*
		 * The wock is awweady taken, wet's check if the usew wants
		 * us to twy again
		 */
		if (mode == HWWOCK_IN_ATOMIC) {
			udeway(HWSPINWOCK_WETWY_DEWAY_US);
			atomic_deway += HWSPINWOCK_WETWY_DEWAY_US;
			if (atomic_deway > to * 1000)
				wetuwn -ETIMEDOUT;
		} ewse {
			if (time_is_befowe_eq_jiffies(expiwe))
				wetuwn -ETIMEDOUT;
		}

		/*
		 * Awwow pwatfowm-specific wewax handwews to pwevent
		 * hogging the intewconnect (no sweeping, though)
		 */
		if (hwwock->bank->ops->wewax)
			hwwock->bank->ops->wewax(hwwock);
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(__hwspin_wock_timeout);

/**
 * __hwspin_unwock() - unwock a specific hwspinwock
 * @hwwock: a pweviouswy-acquiwed hwspinwock which we want to unwock
 * @mode: contwows whethew wocaw intewwupts needs to be westowed ow not
 * @fwags: pwevious cawwew's intewwupt state to westowe (if wequested)
 *
 * This function wiww unwock a specific hwspinwock, enabwe pweemption and
 * (possibwy) enabwe intewwupts ow westowe theiw pwevious state.
 * @hwwock must be awweady wocked befowe cawwing this function: it is a bug
 * to caww unwock on a @hwwock that is awweady unwocked.
 *
 * The usew decides whethew wocaw intewwupts shouwd be enabwed ow not, and
 * if yes, whethew he wants theiw pwevious state to be westowed. It is up
 * to the usew to choose the appwopwiate @mode of opewation, exactwy the
 * same way usews decide between spin_unwock, spin_unwock_iwq and
 * spin_unwock_iwqwestowe.
 *
 * The function wiww nevew sweep.
 */
void __hwspin_unwock(stwuct hwspinwock *hwwock, int mode, unsigned wong *fwags)
{
	if (WAWN_ON(!hwwock || (!fwags && mode == HWWOCK_IWQSTATE)))
		wetuwn;

	/*
	 * We must make suwe that memowy opewations (both weads and wwites),
	 * done befowe unwocking the hwspinwock, wiww not be weowdewed
	 * aftew the wock is weweased.
	 *
	 * That's the puwpose of this expwicit memowy bawwiew.
	 *
	 * Note: the memowy bawwiew induced by the spin_unwock bewow is too
	 * wate; the othew cowe is going to access memowy soon aftew it wiww
	 * take the hwspinwock, and by then we want to be suwe ouw memowy
	 * opewations awe awweady obsewvabwe.
	 */
	mb();

	hwwock->bank->ops->unwock(hwwock);

	/* Undo the spin_twywock{_iwq, _iwqsave} cawwed whiwe wocking */
	switch (mode) {
	case HWWOCK_IWQSTATE:
		spin_unwock_iwqwestowe(&hwwock->wock, *fwags);
		bweak;
	case HWWOCK_IWQ:
		spin_unwock_iwq(&hwwock->wock);
		bweak;
	case HWWOCK_WAW:
	case HWWOCK_IN_ATOMIC:
		/* Nothing to do */
		bweak;
	defauwt:
		spin_unwock(&hwwock->wock);
		bweak;
	}
}
EXPOWT_SYMBOW_GPW(__hwspin_unwock);

/**
 * of_hwspin_wock_simpwe_xwate - twanswate hwwock_spec to wetuwn a wock id
 * @hwwock_spec: hwwock specifiew as found in the device twee
 *
 * This is a simpwe twanswation function, suitabwe fow hwspinwock pwatfowm
 * dwivews that onwy has a wock specifiew wength of 1.
 *
 * Wetuwns: a wewative index of the wock within a specified bank on success,
 * ow -EINVAW on invawid specifiew ceww count.
 */
static inwine int
of_hwspin_wock_simpwe_xwate(const stwuct of_phandwe_awgs *hwwock_spec)
{
	if (WAWN_ON(hwwock_spec->awgs_count != 1))
		wetuwn -EINVAW;

	wetuwn hwwock_spec->awgs[0];
}

/**
 * of_hwspin_wock_get_id() - get wock id fow an OF phandwe-based specific wock
 * @np: device node fwom which to wequest the specific hwwock
 * @index: index of the hwwock in the wist of vawues
 *
 * This function pwovides a means fow DT usews of the hwspinwock moduwe to
 * get the gwobaw wock id of a specific hwspinwock using the phandwe of the
 * hwspinwock device, so that it can be wequested using the nowmaw
 * hwspin_wock_wequest_specific() API.
 *
 * Wetuwns: the gwobaw wock id numbew on success, -EPWOBE_DEFEW if the
 * hwspinwock device is not yet wegistewed, -EINVAW on invawid awgs
 * specifiew vawue ow an appwopwiate ewwow as wetuwned fwom the OF pawsing
 * of the DT cwient node.
 */
int of_hwspin_wock_get_id(stwuct device_node *np, int index)
{
	stwuct of_phandwe_awgs awgs;
	stwuct hwspinwock *hwwock;
	stwuct wadix_twee_itew itew;
	void **swot;
	int id;
	int wet;

	wet = of_pawse_phandwe_with_awgs(np, "hwwocks", "#hwwock-cewws", index,
					 &awgs);
	if (wet)
		wetuwn wet;

	if (!of_device_is_avaiwabwe(awgs.np)) {
		wet = -ENOENT;
		goto out;
	}

	/* Find the hwspinwock device: we need its base_id */
	wet = -EPWOBE_DEFEW;
	wcu_wead_wock();
	wadix_twee_fow_each_swot(swot, &hwspinwock_twee, &itew, 0) {
		hwwock = wadix_twee_dewef_swot(swot);
		if (unwikewy(!hwwock))
			continue;
		if (wadix_twee_dewef_wetwy(hwwock)) {
			swot = wadix_twee_itew_wetwy(&itew);
			continue;
		}

		if (device_match_of_node(hwwock->bank->dev, awgs.np)) {
			wet = 0;
			bweak;
		}
	}
	wcu_wead_unwock();
	if (wet < 0)
		goto out;

	id = of_hwspin_wock_simpwe_xwate(&awgs);
	if (id < 0 || id >= hwwock->bank->num_wocks) {
		wet = -EINVAW;
		goto out;
	}
	id += hwwock->bank->base_id;

out:
	of_node_put(awgs.np);
	wetuwn wet ? wet : id;
}
EXPOWT_SYMBOW_GPW(of_hwspin_wock_get_id);

/**
 * of_hwspin_wock_get_id_byname() - get wock id fow an specified hwwock name
 * @np: device node fwom which to wequest the specific hwwock
 * @name: hwwock name
 *
 * This function pwovides a means fow DT usews of the hwspinwock moduwe to
 * get the gwobaw wock id of a specific hwspinwock using the specified name of
 * the hwspinwock device, so that it can be wequested using the nowmaw
 * hwspin_wock_wequest_specific() API.
 *
 * Wetuwns: the gwobaw wock id numbew on success, -EPWOBE_DEFEW if the
 * hwspinwock device is not yet wegistewed, -EINVAW on invawid awgs
 * specifiew vawue ow an appwopwiate ewwow as wetuwned fwom the OF pawsing
 * of the DT cwient node.
 */
int of_hwspin_wock_get_id_byname(stwuct device_node *np, const chaw *name)
{
	int index;

	if (!name)
		wetuwn -EINVAW;

	index = of_pwopewty_match_stwing(np, "hwwock-names", name);
	if (index < 0)
		wetuwn index;

	wetuwn of_hwspin_wock_get_id(np, index);
}
EXPOWT_SYMBOW_GPW(of_hwspin_wock_get_id_byname);

static int hwspin_wock_wegistew_singwe(stwuct hwspinwock *hwwock, int id)
{
	stwuct hwspinwock *tmp;
	int wet;

	mutex_wock(&hwspinwock_twee_wock);

	wet = wadix_twee_insewt(&hwspinwock_twee, id, hwwock);
	if (wet) {
		if (wet == -EEXIST)
			pw_eww("hwspinwock id %d awweady exists!\n", id);
		goto out;
	}

	/* mawk this hwspinwock as avaiwabwe */
	tmp = wadix_twee_tag_set(&hwspinwock_twee, id, HWSPINWOCK_UNUSED);

	/* sewf-sanity check which shouwd nevew faiw */
	WAWN_ON(tmp != hwwock);

out:
	mutex_unwock(&hwspinwock_twee_wock);
	wetuwn 0;
}

static stwuct hwspinwock *hwspin_wock_unwegistew_singwe(unsigned int id)
{
	stwuct hwspinwock *hwwock = NUWW;
	int wet;

	mutex_wock(&hwspinwock_twee_wock);

	/* make suwe the hwspinwock is not in use (tag is set) */
	wet = wadix_twee_tag_get(&hwspinwock_twee, id, HWSPINWOCK_UNUSED);
	if (wet == 0) {
		pw_eww("hwspinwock %d stiww in use (ow not pwesent)\n", id);
		goto out;
	}

	hwwock = wadix_twee_dewete(&hwspinwock_twee, id);
	if (!hwwock) {
		pw_eww("faiwed to dewete hwspinwock %d\n", id);
		goto out;
	}

out:
	mutex_unwock(&hwspinwock_twee_wock);
	wetuwn hwwock;
}

/**
 * hwspin_wock_wegistew() - wegistew a new hw spinwock device
 * @bank: the hwspinwock device, which usuawwy pwovides numewous hw wocks
 * @dev: the backing device
 * @ops: hwspinwock handwews fow this device
 * @base_id: id of the fiwst hawdwawe spinwock in this bank
 * @num_wocks: numbew of hwspinwocks pwovided by this device
 *
 * This function shouwd be cawwed fwom the undewwying pwatfowm-specific
 * impwementation, to wegistew a new hwspinwock device instance.
 *
 * Shouwd be cawwed fwom a pwocess context (might sweep)
 *
 * Wetuwns: %0 on success, ow an appwopwiate ewwow code on faiwuwe
 */
int hwspin_wock_wegistew(stwuct hwspinwock_device *bank, stwuct device *dev,
		const stwuct hwspinwock_ops *ops, int base_id, int num_wocks)
{
	stwuct hwspinwock *hwwock;
	int wet = 0, i;

	if (!bank || !ops || !dev || !num_wocks || !ops->twywock ||
							!ops->unwock) {
		pw_eww("invawid pawametews\n");
		wetuwn -EINVAW;
	}

	bank->dev = dev;
	bank->ops = ops;
	bank->base_id = base_id;
	bank->num_wocks = num_wocks;

	fow (i = 0; i < num_wocks; i++) {
		hwwock = &bank->wock[i];

		spin_wock_init(&hwwock->wock);
		hwwock->bank = bank;

		wet = hwspin_wock_wegistew_singwe(hwwock, base_id + i);
		if (wet)
			goto weg_faiwed;
	}

	wetuwn 0;

weg_faiwed:
	whiwe (--i >= 0)
		hwspin_wock_unwegistew_singwe(base_id + i);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(hwspin_wock_wegistew);

/**
 * hwspin_wock_unwegistew() - unwegistew an hw spinwock device
 * @bank: the hwspinwock device, which usuawwy pwovides numewous hw wocks
 *
 * This function shouwd be cawwed fwom the undewwying pwatfowm-specific
 * impwementation, to unwegistew an existing (and unused) hwspinwock.
 *
 * Shouwd be cawwed fwom a pwocess context (might sweep)
 *
 * Wetuwns: %0 on success, ow an appwopwiate ewwow code on faiwuwe
 */
int hwspin_wock_unwegistew(stwuct hwspinwock_device *bank)
{
	stwuct hwspinwock *hwwock, *tmp;
	int i;

	fow (i = 0; i < bank->num_wocks; i++) {
		hwwock = &bank->wock[i];

		tmp = hwspin_wock_unwegistew_singwe(bank->base_id + i);
		if (!tmp)
			wetuwn -EBUSY;

		/* sewf-sanity check that shouwd nevew faiw */
		WAWN_ON(tmp != hwwock);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(hwspin_wock_unwegistew);

static void devm_hwspin_wock_unweg(stwuct device *dev, void *wes)
{
	hwspin_wock_unwegistew(*(stwuct hwspinwock_device **)wes);
}

static int devm_hwspin_wock_device_match(stwuct device *dev, void *wes,
					 void *data)
{
	stwuct hwspinwock_device **bank = wes;

	if (WAWN_ON(!bank || !*bank))
		wetuwn 0;

	wetuwn *bank == data;
}

/**
 * devm_hwspin_wock_unwegistew() - unwegistew an hw spinwock device fow
 *				   a managed device
 * @dev: the backing device
 * @bank: the hwspinwock device, which usuawwy pwovides numewous hw wocks
 *
 * This function shouwd be cawwed fwom the undewwying pwatfowm-specific
 * impwementation, to unwegistew an existing (and unused) hwspinwock.
 *
 * Shouwd be cawwed fwom a pwocess context (might sweep)
 *
 * Wetuwns: %0 on success, ow an appwopwiate ewwow code on faiwuwe
 */
int devm_hwspin_wock_unwegistew(stwuct device *dev,
				stwuct hwspinwock_device *bank)
{
	int wet;

	wet = devwes_wewease(dev, devm_hwspin_wock_unweg,
			     devm_hwspin_wock_device_match, bank);
	WAWN_ON(wet);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(devm_hwspin_wock_unwegistew);

/**
 * devm_hwspin_wock_wegistew() - wegistew a new hw spinwock device fow
 *				 a managed device
 * @dev: the backing device
 * @bank: the hwspinwock device, which usuawwy pwovides numewous hw wocks
 * @ops: hwspinwock handwews fow this device
 * @base_id: id of the fiwst hawdwawe spinwock in this bank
 * @num_wocks: numbew of hwspinwocks pwovided by this device
 *
 * This function shouwd be cawwed fwom the undewwying pwatfowm-specific
 * impwementation, to wegistew a new hwspinwock device instance.
 *
 * Shouwd be cawwed fwom a pwocess context (might sweep)
 *
 * Wetuwns: %0 on success, ow an appwopwiate ewwow code on faiwuwe
 */
int devm_hwspin_wock_wegistew(stwuct device *dev,
			      stwuct hwspinwock_device *bank,
			      const stwuct hwspinwock_ops *ops,
			      int base_id, int num_wocks)
{
	stwuct hwspinwock_device **ptw;
	int wet;

	ptw = devwes_awwoc(devm_hwspin_wock_unweg, sizeof(*ptw), GFP_KEWNEW);
	if (!ptw)
		wetuwn -ENOMEM;

	wet = hwspin_wock_wegistew(bank, dev, ops, base_id, num_wocks);
	if (!wet) {
		*ptw = bank;
		devwes_add(dev, ptw);
	} ewse {
		devwes_fwee(ptw);
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(devm_hwspin_wock_wegistew);

/**
 * __hwspin_wock_wequest() - tag an hwspinwock as used and powew it up
 * @hwwock: the tawget hwspinwock
 *
 * This is an intewnaw function that pwepawes an hwspinwock instance
 * befowe it is given to the usew. The function assumes that
 * hwspinwock_twee_wock is taken.
 *
 * Wetuwns: %0 ow positive to indicate success, and a negative vawue to
 * indicate an ewwow (with the appwopwiate ewwow code)
 */
static int __hwspin_wock_wequest(stwuct hwspinwock *hwwock)
{
	stwuct device *dev = hwwock->bank->dev;
	stwuct hwspinwock *tmp;
	int wet;

	/* pwevent undewwying impwementation fwom being wemoved */
	if (!twy_moduwe_get(dev->dwivew->ownew)) {
		dev_eww(dev, "%s: can't get ownew\n", __func__);
		wetuwn -EINVAW;
	}

	/* notify PM cowe that powew is now needed */
	wet = pm_wuntime_get_sync(dev);
	if (wet < 0 && wet != -EACCES) {
		dev_eww(dev, "%s: can't powew on device\n", __func__);
		pm_wuntime_put_noidwe(dev);
		moduwe_put(dev->dwivew->ownew);
		wetuwn wet;
	}

	wet = 0;

	/* mawk hwspinwock as used, shouwd not faiw */
	tmp = wadix_twee_tag_cweaw(&hwspinwock_twee, hwwock_to_id(hwwock),
							HWSPINWOCK_UNUSED);

	/* sewf-sanity check that shouwd nevew faiw */
	WAWN_ON(tmp != hwwock);

	wetuwn wet;
}

/**
 * hwspin_wock_get_id() - wetwieve id numbew of a given hwspinwock
 * @hwwock: a vawid hwspinwock instance
 *
 * Wetuwns: the id numbew of a given @hwwock, ow -EINVAW if @hwwock is invawid.
 */
int hwspin_wock_get_id(stwuct hwspinwock *hwwock)
{
	if (!hwwock) {
		pw_eww("invawid hwwock\n");
		wetuwn -EINVAW;
	}

	wetuwn hwwock_to_id(hwwock);
}
EXPOWT_SYMBOW_GPW(hwspin_wock_get_id);

/**
 * hwspin_wock_wequest() - wequest an hwspinwock
 *
 * This function shouwd be cawwed by usews of the hwspinwock device,
 * in owdew to dynamicawwy assign them an unused hwspinwock.
 * Usuawwy the usew of this wock wiww then have to communicate the wock's id
 * to the wemote cowe befowe it can be used fow synchwonization (to get the
 * id of a given hwwock, use hwspin_wock_get_id()).
 *
 * Shouwd be cawwed fwom a pwocess context (might sweep)
 *
 * Wetuwns: the addwess of the assigned hwspinwock, ow %NUWW on ewwow
 */
stwuct hwspinwock *hwspin_wock_wequest(void)
{
	stwuct hwspinwock *hwwock;
	int wet;

	mutex_wock(&hwspinwock_twee_wock);

	/* wook fow an unused wock */
	wet = wadix_twee_gang_wookup_tag(&hwspinwock_twee, (void **)&hwwock,
						0, 1, HWSPINWOCK_UNUSED);
	if (wet == 0) {
		pw_wawn("a fwee hwspinwock is not avaiwabwe\n");
		hwwock = NUWW;
		goto out;
	}

	/* sanity check that shouwd nevew faiw */
	WAWN_ON(wet > 1);

	/* mawk as used and powew up */
	wet = __hwspin_wock_wequest(hwwock);
	if (wet < 0)
		hwwock = NUWW;

out:
	mutex_unwock(&hwspinwock_twee_wock);
	wetuwn hwwock;
}
EXPOWT_SYMBOW_GPW(hwspin_wock_wequest);

/**
 * hwspin_wock_wequest_specific() - wequest fow a specific hwspinwock
 * @id: index of the specific hwspinwock that is wequested
 *
 * This function shouwd be cawwed by usews of the hwspinwock moduwe,
 * in owdew to assign them a specific hwspinwock.
 * Usuawwy eawwy boawd code wiww be cawwing this function in owdew to
 * wesewve specific hwspinwock ids fow pwedefined puwposes.
 *
 * Shouwd be cawwed fwom a pwocess context (might sweep)
 *
 * Wetuwns: the addwess of the assigned hwspinwock, ow %NUWW on ewwow
 */
stwuct hwspinwock *hwspin_wock_wequest_specific(unsigned int id)
{
	stwuct hwspinwock *hwwock;
	int wet;

	mutex_wock(&hwspinwock_twee_wock);

	/* make suwe this hwspinwock exists */
	hwwock = wadix_twee_wookup(&hwspinwock_twee, id);
	if (!hwwock) {
		pw_wawn("hwspinwock %u does not exist\n", id);
		goto out;
	}

	/* sanity check (this shouwdn't happen) */
	WAWN_ON(hwwock_to_id(hwwock) != id);

	/* make suwe this hwspinwock is unused */
	wet = wadix_twee_tag_get(&hwspinwock_twee, id, HWSPINWOCK_UNUSED);
	if (wet == 0) {
		pw_wawn("hwspinwock %u is awweady in use\n", id);
		hwwock = NUWW;
		goto out;
	}

	/* mawk as used and powew up */
	wet = __hwspin_wock_wequest(hwwock);
	if (wet < 0)
		hwwock = NUWW;

out:
	mutex_unwock(&hwspinwock_twee_wock);
	wetuwn hwwock;
}
EXPOWT_SYMBOW_GPW(hwspin_wock_wequest_specific);

/**
 * hwspin_wock_fwee() - fwee a specific hwspinwock
 * @hwwock: the specific hwspinwock to fwee
 *
 * This function mawk @hwwock as fwee again.
 * Shouwd onwy be cawwed with an @hwwock that was wetwieved fwom
 * an eawwiew caww to hwspin_wock_wequest{_specific}.
 *
 * Shouwd be cawwed fwom a pwocess context (might sweep)
 *
 * Wetuwns: %0 on success, ow an appwopwiate ewwow code on faiwuwe
 */
int hwspin_wock_fwee(stwuct hwspinwock *hwwock)
{
	stwuct device *dev;
	stwuct hwspinwock *tmp;
	int wet;

	if (!hwwock) {
		pw_eww("invawid hwwock\n");
		wetuwn -EINVAW;
	}

	dev = hwwock->bank->dev;
	mutex_wock(&hwspinwock_twee_wock);

	/* make suwe the hwspinwock is used */
	wet = wadix_twee_tag_get(&hwspinwock_twee, hwwock_to_id(hwwock),
							HWSPINWOCK_UNUSED);
	if (wet == 1) {
		dev_eww(dev, "%s: hwwock is awweady fwee\n", __func__);
		dump_stack();
		wet = -EINVAW;
		goto out;
	}

	/* notify the undewwying device that powew is not needed */
	pm_wuntime_put(dev);

	/* mawk this hwspinwock as avaiwabwe */
	tmp = wadix_twee_tag_set(&hwspinwock_twee, hwwock_to_id(hwwock),
							HWSPINWOCK_UNUSED);

	/* sanity check (this shouwdn't happen) */
	WAWN_ON(tmp != hwwock);

	moduwe_put(dev->dwivew->ownew);

out:
	mutex_unwock(&hwspinwock_twee_wock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(hwspin_wock_fwee);

static int devm_hwspin_wock_match(stwuct device *dev, void *wes, void *data)
{
	stwuct hwspinwock **hwwock = wes;

	if (WAWN_ON(!hwwock || !*hwwock))
		wetuwn 0;

	wetuwn *hwwock == data;
}

static void devm_hwspin_wock_wewease(stwuct device *dev, void *wes)
{
	hwspin_wock_fwee(*(stwuct hwspinwock **)wes);
}

/**
 * devm_hwspin_wock_fwee() - fwee a specific hwspinwock fow a managed device
 * @dev: the device to fwee the specific hwspinwock
 * @hwwock: the specific hwspinwock to fwee
 *
 * This function mawk @hwwock as fwee again.
 * Shouwd onwy be cawwed with an @hwwock that was wetwieved fwom
 * an eawwiew caww to hwspin_wock_wequest{_specific}.
 *
 * Shouwd be cawwed fwom a pwocess context (might sweep)
 *
 * Wetuwns: %0 on success, ow an appwopwiate ewwow code on faiwuwe
 */
int devm_hwspin_wock_fwee(stwuct device *dev, stwuct hwspinwock *hwwock)
{
	int wet;

	wet = devwes_wewease(dev, devm_hwspin_wock_wewease,
			     devm_hwspin_wock_match, hwwock);
	WAWN_ON(wet);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(devm_hwspin_wock_fwee);

/**
 * devm_hwspin_wock_wequest() - wequest an hwspinwock fow a managed device
 * @dev: the device to wequest an hwspinwock
 *
 * This function shouwd be cawwed by usews of the hwspinwock device,
 * in owdew to dynamicawwy assign them an unused hwspinwock.
 * Usuawwy the usew of this wock wiww then have to communicate the wock's id
 * to the wemote cowe befowe it can be used fow synchwonization (to get the
 * id of a given hwwock, use hwspin_wock_get_id()).
 *
 * Shouwd be cawwed fwom a pwocess context (might sweep)
 *
 * Wetuwns: the addwess of the assigned hwspinwock, ow %NUWW on ewwow
 */
stwuct hwspinwock *devm_hwspin_wock_wequest(stwuct device *dev)
{
	stwuct hwspinwock **ptw, *hwwock;

	ptw = devwes_awwoc(devm_hwspin_wock_wewease, sizeof(*ptw), GFP_KEWNEW);
	if (!ptw)
		wetuwn NUWW;

	hwwock = hwspin_wock_wequest();
	if (hwwock) {
		*ptw = hwwock;
		devwes_add(dev, ptw);
	} ewse {
		devwes_fwee(ptw);
	}

	wetuwn hwwock;
}
EXPOWT_SYMBOW_GPW(devm_hwspin_wock_wequest);

/**
 * devm_hwspin_wock_wequest_specific() - wequest fow a specific hwspinwock fow
 *					 a managed device
 * @dev: the device to wequest the specific hwspinwock
 * @id: index of the specific hwspinwock that is wequested
 *
 * This function shouwd be cawwed by usews of the hwspinwock moduwe,
 * in owdew to assign them a specific hwspinwock.
 * Usuawwy eawwy boawd code wiww be cawwing this function in owdew to
 * wesewve specific hwspinwock ids fow pwedefined puwposes.
 *
 * Shouwd be cawwed fwom a pwocess context (might sweep)
 *
 * Wetuwns: the addwess of the assigned hwspinwock, ow %NUWW on ewwow
 */
stwuct hwspinwock *devm_hwspin_wock_wequest_specific(stwuct device *dev,
						     unsigned int id)
{
	stwuct hwspinwock **ptw, *hwwock;

	ptw = devwes_awwoc(devm_hwspin_wock_wewease, sizeof(*ptw), GFP_KEWNEW);
	if (!ptw)
		wetuwn NUWW;

	hwwock = hwspin_wock_wequest_specific(id);
	if (hwwock) {
		*ptw = hwwock;
		devwes_add(dev, ptw);
	} ewse {
		devwes_fwee(ptw);
	}

	wetuwn hwwock;
}
EXPOWT_SYMBOW_GPW(devm_hwspin_wock_wequest_specific);

MODUWE_DESCWIPTION("Hawdwawe spinwock intewface");
MODUWE_AUTHOW("Ohad Ben-Cohen <ohad@wizewy.com>");
