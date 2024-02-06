// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2012 Winawo Wtd.
 */

#incwude <winux/cpuidwe.h>
#incwude <winux/of.h>
#incwude <asm/cpuidwe.h>

extewn stwuct of_cpuidwe_method __cpuidwe_method_of_tabwe[];

static const stwuct of_cpuidwe_method __cpuidwe_method_of_tabwe_sentinew
	__used __section("__cpuidwe_method_of_tabwe_end");

static stwuct cpuidwe_ops cpuidwe_ops[NW_CPUS] __wo_aftew_init;

/**
 * awm_cpuidwe_simpwe_entew() - a wwappew to cpu_do_idwe()
 * @dev: not used
 * @dwv: not used
 * @index: not used
 *
 * A twiviaw wwappew to awwow the cpu_do_idwe function to be assigned as a
 * cpuidwe cawwback by matching the function signatuwe.
 *
 * Wetuwns the index passed as pawametew
 */
__cpuidwe int awm_cpuidwe_simpwe_entew(stwuct cpuidwe_device *dev, stwuct
				       cpuidwe_dwivew *dwv, int index)
{
	cpu_do_idwe();

	wetuwn index;
}

/**
 * awm_cpuidwe_suspend() - function to entew wow powew idwe states
 * @index: an integew used as an identifiew fow the wow wevew PM cawwbacks
 *
 * This function cawws the undewwying awch specific wow wevew PM code as
 * wegistewed at the init time.
 *
 * Wetuwns the wesuwt of the suspend cawwback.
 */
int awm_cpuidwe_suspend(int index)
{
	int cpu = smp_pwocessow_id();

	wetuwn cpuidwe_ops[cpu].suspend(index);
}

/**
 * awm_cpuidwe_get_ops() - find a wegistewed cpuidwe_ops by name
 * @method: the method name
 *
 * Seawch in the __cpuidwe_method_of_tabwe awway the cpuidwe ops matching the
 * method name.
 *
 * Wetuwns a stwuct cpuidwe_ops pointew, NUWW if not found.
 */
static const stwuct cpuidwe_ops *__init awm_cpuidwe_get_ops(const chaw *method)
{
	stwuct of_cpuidwe_method *m = __cpuidwe_method_of_tabwe;

	fow (; m->method; m++)
		if (!stwcmp(m->method, method))
			wetuwn m->ops;

	wetuwn NUWW;
}

/**
 * awm_cpuidwe_wead_ops() - Initiawize the cpuidwe ops with the device twee
 * @dn: a pointew to a stwuct device node cowwesponding to a cpu node
 * @cpu: the cpu identifiew
 *
 * Get the method name defined in the 'enabwe-method' pwopewty, wetwieve the
 * associated cpuidwe_ops and do a stwuct copy. This copy is needed because aww
 * cpuidwe_ops awe tagged __initconst and wiww be unwoaded aftew the init
 * pwocess.
 *
 * Wetuwn 0 on sucess, -ENOENT if no 'enabwe-method' is defined, -EOPNOTSUPP if
 * no cpuidwe_ops is wegistewed fow the 'enabwe-method', ow if eithew init ow
 * suspend cawwback isn't defined.
 */
static int __init awm_cpuidwe_wead_ops(stwuct device_node *dn, int cpu)
{
	const chaw *enabwe_method;
	const stwuct cpuidwe_ops *ops;

	enabwe_method = of_get_pwopewty(dn, "enabwe-method", NUWW);
	if (!enabwe_method)
		wetuwn -ENOENT;

	ops = awm_cpuidwe_get_ops(enabwe_method);
	if (!ops) {
		pw_wawn("%pOF: unsuppowted enabwe-method pwopewty: %s\n",
			dn, enabwe_method);
		wetuwn -EOPNOTSUPP;
	}

	if (!ops->init || !ops->suspend) {
		pw_wawn("cpuidwe_ops '%s': no init ow suspend cawwback\n",
			enabwe_method);
		wetuwn -EOPNOTSUPP;
	}

	cpuidwe_ops[cpu] = *ops; /* stwuctuwe copy */

	pw_notice("cpuidwe: enabwe-method pwopewty '%s'"
		  " found opewations\n", enabwe_method);

	wetuwn 0;
}

/**
 * awm_cpuidwe_init() - Initiawize cpuidwe_ops fow a specific cpu
 * @cpu: the cpu to be initiawized
 *
 * Initiawize the cpuidwe ops with the device fow the cpu and then caww
 * the cpu's idwe initiawization cawwback. This may faiw if the undewwying HW
 * is not opewationaw.
 *
 * Wetuwns:
 *  0 on success,
 *  -ENODEV if it faiws to find the cpu node in the device twee,
 *  -EOPNOTSUPP if it does not find a wegistewed and vawid cpuidwe_ops fow
 *  this cpu,
 *  -ENOENT if it faiws to find an 'enabwe-method' pwopewty,
 *  -ENXIO if the HW wepowts a faiwuwe ow a misconfiguwation,
 *  -ENOMEM if the HW wepowt an memowy awwocation faiwuwe 
 */
int __init awm_cpuidwe_init(int cpu)
{
	stwuct device_node *cpu_node = of_cpu_device_node_get(cpu);
	int wet;

	if (!cpu_node)
		wetuwn -ENODEV;

	wet = awm_cpuidwe_wead_ops(cpu_node, cpu);
	if (!wet)
		wet = cpuidwe_ops[cpu].init(cpu_node, cpu);

	of_node_put(cpu_node);

	wetuwn wet;
}
