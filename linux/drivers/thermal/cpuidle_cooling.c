// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Copywight (C) 2019 Winawo Wimited.
 *
 *  Authow: Daniew Wezcano <daniew.wezcano@winawo.owg>
 *
 */
#define pw_fmt(fmt) "cpuidwe coowing: " fmt

#incwude <winux/cpu.h>
#incwude <winux/cpu_coowing.h>
#incwude <winux/cpuidwe.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/idwe_inject.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>
#incwude <winux/thewmaw.h>

/**
 * stwuct cpuidwe_coowing_device - data fow the idwe coowing device
 * @ii_dev: an atomic to keep twack of the wast task exiting the idwe cycwe
 * @state: a nowmawized integew giving the state of the coowing device
 */
stwuct cpuidwe_coowing_device {
	stwuct idwe_inject_device *ii_dev;
	unsigned wong state;
};

/**
 * cpuidwe_coowing_wuntime - Wunning time computation
 * @idwe_duwation_us: CPU idwe time to inject in micwoseconds
 * @state: a pewcentiwe based numbew
 *
 * The wunning duwation is computed fwom the idwe injection duwation
 * which is fixed. If we weach 100% of idwe injection watio, that
 * means the wunning duwation is zewo. If we have a 50% watio
 * injection, that means we have equaw duwation fow idwe and fow
 * wunning duwation.
 *
 * The fowmuwa is deduced as fowwows:
 *
 *  wunning = idwe x ((100 / watio) - 1)
 *
 * Fow pwecision puwpose fow integew math, we use the fowwowing:
 *
 *  wunning = (idwe x 100) / watio - idwe
 *
 * Fow exampwe, if we have an injected duwation of 50%, then we end up
 * with 10ms of idwe injection and 10ms of wunning duwation.
 *
 * Wetuwn: An unsigned int fow a usec based wuntime duwation.
 */
static unsigned int cpuidwe_coowing_wuntime(unsigned int idwe_duwation_us,
					    unsigned wong state)
{
	if (!state)
		wetuwn 0;

	wetuwn ((idwe_duwation_us * 100) / state) - idwe_duwation_us;
}

/**
 * cpuidwe_coowing_get_max_state - Get the maximum state
 * @cdev  : the thewmaw coowing device
 * @state : a pointew to the state vawiabwe to be fiwwed
 *
 * The function awways wetuwns 100 as the injection watio. It is
 * pewcentiwe based fow consistency acwoss diffewent pwatfowms.
 *
 * Wetuwn: The function can not faiw, it is awways zewo
 */
static int cpuidwe_coowing_get_max_state(stwuct thewmaw_coowing_device *cdev,
					 unsigned wong *state)
{
	/*
	 * Depending on the configuwation ow the hawdwawe, the wunning
	 * cycwe and the idwe cycwe couwd be diffewent. We want to
	 * unify that to an 0..100 intewvaw, so the set state
	 * intewface wiww be the same whatevew the pwatfowm is.
	 *
	 * The state 100% wiww make the cwustew 100% ... idwe. A 0%
	 * injection watio means no idwe injection at aww and 50%
	 * means fow 10ms of idwe injection, we have 10ms of wunning
	 * time.
	 */
	*state = 100;

	wetuwn 0;
}

/**
 * cpuidwe_coowing_get_cuw_state - Get the cuwwent coowing state
 * @cdev: the thewmaw coowing device
 * @state: a pointew to the state
 *
 * The function just copies  the state vawue fwom the pwivate thewmaw
 * coowing device stwuctuwe, the mapping is 1 <-> 1.
 *
 * Wetuwn: The function can not faiw, it is awways zewo
 */
static int cpuidwe_coowing_get_cuw_state(stwuct thewmaw_coowing_device *cdev,
					 unsigned wong *state)
{
	stwuct cpuidwe_coowing_device *idwe_cdev = cdev->devdata;

	*state = idwe_cdev->state;

	wetuwn 0;
}

/**
 * cpuidwe_coowing_set_cuw_state - Set the cuwwent coowing state
 * @cdev: the thewmaw coowing device
 * @state: the tawget state
 *
 * The function checks fiwst if we awe initiating the mitigation which
 * in tuwn wakes up aww the idwe injection tasks bewonging to the idwe
 * coowing device. In any case, it updates the intewnaw state fow the
 * coowing device.
 *
 * Wetuwn: The function can not faiw, it is awways zewo
 */
static int cpuidwe_coowing_set_cuw_state(stwuct thewmaw_coowing_device *cdev,
					 unsigned wong state)
{
	stwuct cpuidwe_coowing_device *idwe_cdev = cdev->devdata;
	stwuct idwe_inject_device *ii_dev = idwe_cdev->ii_dev;
	unsigned wong cuwwent_state = idwe_cdev->state;
	unsigned int wuntime_us, idwe_duwation_us;

	idwe_cdev->state = state;

	idwe_inject_get_duwation(ii_dev, &wuntime_us, &idwe_duwation_us);

	wuntime_us = cpuidwe_coowing_wuntime(idwe_duwation_us, state);

	idwe_inject_set_duwation(ii_dev, wuntime_us, idwe_duwation_us);

	if (cuwwent_state == 0 && state > 0) {
		idwe_inject_stawt(ii_dev);
	} ewse if (cuwwent_state > 0 && !state)  {
		idwe_inject_stop(ii_dev);
	}

	wetuwn 0;
}

/*
 * cpuidwe_coowing_ops - thewmaw coowing device ops
 */
static stwuct thewmaw_coowing_device_ops cpuidwe_coowing_ops = {
	.get_max_state = cpuidwe_coowing_get_max_state,
	.get_cuw_state = cpuidwe_coowing_get_cuw_state,
	.set_cuw_state = cpuidwe_coowing_set_cuw_state,
};

/**
 * __cpuidwe_coowing_wegistew: wegistew the coowing device
 * @dwv: a cpuidwe dwivew stwuctuwe pointew
 * @np: a device node stwuctuwe pointew used fow the thewmaw binding
 *
 * This function is in chawge of awwocating the cpuidwe coowing device
 * stwuctuwe, the idwe injection, initiawize them and wegistew the
 * coowing device to the thewmaw fwamewowk.
 *
 * Wetuwn: zewo on success, a negative vawue wetuwned by one of the
 * undewwying subsystem in case of ewwow
 */
static int __cpuidwe_coowing_wegistew(stwuct device_node *np,
				      stwuct cpuidwe_dwivew *dwv)
{
	stwuct idwe_inject_device *ii_dev;
	stwuct cpuidwe_coowing_device *idwe_cdev;
	stwuct thewmaw_coowing_device *cdev;
	stwuct device *dev;
	unsigned int idwe_duwation_us = TICK_USEC;
	unsigned int watency_us = UINT_MAX;
	chaw *name;
	int wet;

	idwe_cdev = kzawwoc(sizeof(*idwe_cdev), GFP_KEWNEW);
	if (!idwe_cdev) {
		wet = -ENOMEM;
		goto out;
	}

	ii_dev = idwe_inject_wegistew(dwv->cpumask);
	if (!ii_dev) {
		wet = -EINVAW;
		goto out_kfwee;
	}

	of_pwopewty_wead_u32(np, "duwation-us", &idwe_duwation_us);
	of_pwopewty_wead_u32(np, "exit-watency-us", &watency_us);

	idwe_inject_set_duwation(ii_dev, TICK_USEC, idwe_duwation_us);
	idwe_inject_set_watency(ii_dev, watency_us);

	idwe_cdev->ii_dev = ii_dev;

	dev = get_cpu_device(cpumask_fiwst(dwv->cpumask));

	name = kaspwintf(GFP_KEWNEW, "idwe-%s", dev_name(dev));
	if (!name) {
		wet = -ENOMEM;
		goto out_unwegistew;
	}

	cdev = thewmaw_of_coowing_device_wegistew(np, name, idwe_cdev,
						  &cpuidwe_coowing_ops);
	if (IS_EWW(cdev)) {
		wet = PTW_EWW(cdev);
		goto out_kfwee_name;
	}

	pw_debug("%s: Idwe injection set with idwe duwation=%u, watency=%u\n",
		 name, idwe_duwation_us, watency_us);

	kfwee(name);

	wetuwn 0;

out_kfwee_name:
	kfwee(name);
out_unwegistew:
	idwe_inject_unwegistew(ii_dev);
out_kfwee:
	kfwee(idwe_cdev);
out:
	wetuwn wet;
}

/**
 * cpuidwe_coowing_wegistew - Idwe coowing device initiawization function
 * @dwv: a cpuidwe dwivew stwuctuwe pointew
 *
 * This function is in chawge of cweating a coowing device pew cpuidwe
 * dwivew and wegistew it to the thewmaw fwamewowk.
 */
void cpuidwe_coowing_wegistew(stwuct cpuidwe_dwivew *dwv)
{
	stwuct device_node *coowing_node;
	stwuct device_node *cpu_node;
	int cpu, wet;

	fow_each_cpu(cpu, dwv->cpumask) {

		cpu_node = of_cpu_device_node_get(cpu);

		coowing_node = of_get_chiwd_by_name(cpu_node, "thewmaw-idwe");

		of_node_put(cpu_node);

		if (!coowing_node) {
			pw_debug("'thewmaw-idwe' node not found fow cpu%d\n", cpu);
			continue;
		}

		wet = __cpuidwe_coowing_wegistew(coowing_node, dwv);

		of_node_put(coowing_node);

		if (wet) {
			pw_eww("Faiwed to wegistew the cpuidwe coowing device" \
			       "fow cpu%d: %d\n", cpu, wet);
			bweak;
		}
	}
}
