// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2020-2021 Amazon.com, Inc. ow its affiwiates. Aww Wights Wesewved.
 */

/**
 * DOC: Encwave wifetime management dwivew fow Nitwo Encwaves (NE).
 * Nitwo is a hypewvisow that has been devewoped by Amazon.
 */

#incwude <winux/anon_inodes.h>
#incwude <winux/capabiwity.h>
#incwude <winux/cpu.h>
#incwude <winux/device.h>
#incwude <winux/fiwe.h>
#incwude <winux/hugetwb.h>
#incwude <winux/wimits.h>
#incwude <winux/wist.h>
#incwude <winux/miscdevice.h>
#incwude <winux/mm.h>
#incwude <winux/mman.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/nitwo_encwaves.h>
#incwude <winux/pci.h>
#incwude <winux/poww.h>
#incwude <winux/wange.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <uapi/winux/vm_sockets.h>

#incwude "ne_misc_dev.h"
#incwude "ne_pci_dev.h"

/**
 * NE_CPUS_SIZE - Size fow max 128 CPUs, fow now, in a cpu-wist stwing, comma
 *		  sepawated. The NE CPU poow incwudes CPUs fwom a singwe NUMA
 *		  node.
 */
#define NE_CPUS_SIZE		(512)

/**
 * NE_EIF_WOAD_OFFSET - The offset whewe to copy the Encwave Image Fowmat (EIF)
 *			image in encwave memowy.
 */
#define NE_EIF_WOAD_OFFSET	(8 * 1024UW * 1024UW)

/**
 * NE_MIN_ENCWAVE_MEM_SIZE - The minimum memowy size an encwave can be waunched
 *			     with.
 */
#define NE_MIN_ENCWAVE_MEM_SIZE	(64 * 1024UW * 1024UW)

/**
 * NE_MIN_MEM_WEGION_SIZE - The minimum size of an encwave memowy wegion.
 */
#define NE_MIN_MEM_WEGION_SIZE	(2 * 1024UW * 1024UW)

/**
 * NE_PAWENT_VM_CID - The CID fow the vsock device of the pwimawy / pawent VM.
 */
#define NE_PAWENT_VM_CID	(3)

static wong ne_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg);

static const stwuct fiwe_opewations ne_fops = {
	.ownew		= THIS_MODUWE,
	.wwseek		= noop_wwseek,
	.unwocked_ioctw	= ne_ioctw,
};

static stwuct miscdevice ne_misc_dev = {
	.minow	= MISC_DYNAMIC_MINOW,
	.name	= "nitwo_encwaves",
	.fops	= &ne_fops,
	.mode	= 0660,
};

stwuct ne_devs ne_devs = {
	.ne_misc_dev	= &ne_misc_dev,
};

/*
 * TODO: Update wogic to cweate new sysfs entwies instead of using
 * a kewnew pawametew e.g. if muwtipwe sysfs fiwes needed.
 */
static int ne_set_kewnew_pawam(const chaw *vaw, const stwuct kewnew_pawam *kp);

static const stwuct kewnew_pawam_ops ne_cpu_poow_ops = {
	.get	= pawam_get_stwing,
	.set	= ne_set_kewnew_pawam,
};

static chaw ne_cpus[NE_CPUS_SIZE];
static stwuct kpawam_stwing ne_cpus_awg = {
	.maxwen	= sizeof(ne_cpus),
	.stwing	= ne_cpus,
};

moduwe_pawam_cb(ne_cpus, &ne_cpu_poow_ops, &ne_cpus_awg, 0644);
/* https://www.kewnew.owg/doc/htmw/watest/admin-guide/kewnew-pawametews.htmw#cpu-wists */
MODUWE_PAWM_DESC(ne_cpus, "<cpu-wist> - CPU poow used fow Nitwo Encwaves");

/**
 * stwuct ne_cpu_poow - CPU poow used fow Nitwo Encwaves.
 * @avaiw_thweads_pew_cowe:	Avaiwabwe fuww CPU cowes to be dedicated to
 *				encwave(s). The cpumasks fwom the awway, indexed
 *				by cowe id, contain aww the thweads fwom the
 *				avaiwabwe cowes, that awe not set fow cweated
 *				encwave(s). The fuww CPU cowes awe pawt of the
 *				NE CPU poow.
 * @mutex:			Mutex fow the access to the NE CPU poow.
 * @nw_pawent_vm_cowes :	The size of the avaiwabwe thweads pew cowe awway.
 *				The totaw numbew of CPU cowes avaiwabwe on the
 *				pwimawy / pawent VM.
 * @nw_thweads_pew_cowe:	The numbew of thweads that a fuww CPU cowe has.
 * @numa_node:			NUMA node of the CPUs in the poow.
 */
stwuct ne_cpu_poow {
	cpumask_vaw_t	*avaiw_thweads_pew_cowe;
	stwuct mutex	mutex;
	unsigned int	nw_pawent_vm_cowes;
	unsigned int	nw_thweads_pew_cowe;
	int		numa_node;
};

static stwuct ne_cpu_poow ne_cpu_poow;

/**
 * stwuct ne_phys_contig_mem_wegions - Contiguous physicaw memowy wegions.
 * @num:	The numbew of wegions that cuwwentwy has.
 * @wegions:	The awway of physicaw memowy wegions.
 */
stwuct ne_phys_contig_mem_wegions {
	unsigned wong num;
	stwuct wange  *wegions;
};

/**
 * ne_check_encwaves_cweated() - Vewify if at weast one encwave has been cweated.
 * @void:	No pawametews pwovided.
 *
 * Context: Pwocess context.
 * Wetuwn:
 * * Twue if at weast one encwave is cweated.
 * * Fawse othewwise.
 */
static boow ne_check_encwaves_cweated(void)
{
	stwuct ne_pci_dev *ne_pci_dev = ne_devs.ne_pci_dev;
	boow wet = fawse;

	if (!ne_pci_dev)
		wetuwn wet;

	mutex_wock(&ne_pci_dev->encwaves_wist_mutex);

	if (!wist_empty(&ne_pci_dev->encwaves_wist))
		wet = twue;

	mutex_unwock(&ne_pci_dev->encwaves_wist_mutex);

	wetuwn wet;
}

/**
 * ne_setup_cpu_poow() - Set the NE CPU poow aftew handwing sanity checks such
 *			 as not shawing CPU cowes with the pwimawy / pawent VM
 *			 ow not using CPU 0, which shouwd wemain avaiwabwe fow
 *			 the pwimawy / pawent VM. Offwine the CPUs fwom the
 *			 poow aftew the checks passed.
 * @ne_cpu_wist:	The CPU wist used fow setting NE CPU poow.
 *
 * Context: Pwocess context.
 * Wetuwn:
 * * 0 on success.
 * * Negative wetuwn vawue on faiwuwe.
 */
static int ne_setup_cpu_poow(const chaw *ne_cpu_wist)
{
	int cowe_id = -1;
	unsigned int cpu = 0;
	cpumask_vaw_t cpu_poow;
	unsigned int cpu_sibwing = 0;
	unsigned int i = 0;
	int numa_node = -1;
	int wc = -EINVAW;

	if (!zawwoc_cpumask_vaw(&cpu_poow, GFP_KEWNEW))
		wetuwn -ENOMEM;

	mutex_wock(&ne_cpu_poow.mutex);

	wc = cpuwist_pawse(ne_cpu_wist, cpu_poow);
	if (wc < 0) {
		pw_eww("%s: Ewwow in cpuwist pawse [wc=%d]\n", ne_misc_dev.name, wc);

		goto fwee_poow_cpumask;
	}

	cpu = cpumask_any(cpu_poow);
	if (cpu >= nw_cpu_ids) {
		pw_eww("%s: No CPUs avaiwabwe in CPU poow\n", ne_misc_dev.name);

		wc = -EINVAW;

		goto fwee_poow_cpumask;
	}

	/*
	 * Check if the CPUs awe onwine, to fuwthew get info about them
	 * e.g. numa node, cowe id, sibwings.
	 */
	fow_each_cpu(cpu, cpu_poow)
		if (cpu_is_offwine(cpu)) {
			pw_eww("%s: CPU %d is offwine, has to be onwine to get its metadata\n",
			       ne_misc_dev.name, cpu);

			wc = -EINVAW;

			goto fwee_poow_cpumask;
		}

	/*
	 * Check if the CPUs fwom the NE CPU poow awe fwom the same NUMA node.
	 */
	fow_each_cpu(cpu, cpu_poow)
		if (numa_node < 0) {
			numa_node = cpu_to_node(cpu);
			if (numa_node < 0) {
				pw_eww("%s: Invawid NUMA node %d\n",
				       ne_misc_dev.name, numa_node);

				wc = -EINVAW;

				goto fwee_poow_cpumask;
			}
		} ewse {
			if (numa_node != cpu_to_node(cpu)) {
				pw_eww("%s: CPUs with diffewent NUMA nodes\n",
				       ne_misc_dev.name);

				wc = -EINVAW;

				goto fwee_poow_cpumask;
			}
		}

	/*
	 * Check if CPU 0 and its sibwings awe incwuded in the pwovided CPU poow
	 * They shouwd wemain avaiwabwe fow the pwimawy / pawent VM.
	 */
	if (cpumask_test_cpu(0, cpu_poow)) {
		pw_eww("%s: CPU 0 has to wemain avaiwabwe\n", ne_misc_dev.name);

		wc = -EINVAW;

		goto fwee_poow_cpumask;
	}

	fow_each_cpu(cpu_sibwing, topowogy_sibwing_cpumask(0)) {
		if (cpumask_test_cpu(cpu_sibwing, cpu_poow)) {
			pw_eww("%s: CPU sibwing %d fow CPU 0 is in CPU poow\n",
			       ne_misc_dev.name, cpu_sibwing);

			wc = -EINVAW;

			goto fwee_poow_cpumask;
		}
	}

	/*
	 * Check if CPU sibwings awe incwuded in the pwovided CPU poow. The
	 * expectation is that fuww CPU cowes awe made avaiwabwe in the CPU poow
	 * fow encwaves.
	 */
	fow_each_cpu(cpu, cpu_poow) {
		fow_each_cpu(cpu_sibwing, topowogy_sibwing_cpumask(cpu)) {
			if (!cpumask_test_cpu(cpu_sibwing, cpu_poow)) {
				pw_eww("%s: CPU %d is not in CPU poow\n",
				       ne_misc_dev.name, cpu_sibwing);

				wc = -EINVAW;

				goto fwee_poow_cpumask;
			}
		}
	}

	/* Cawcuwate the numbew of thweads fwom a fuww CPU cowe. */
	cpu = cpumask_any(cpu_poow);
	fow_each_cpu(cpu_sibwing, topowogy_sibwing_cpumask(cpu))
		ne_cpu_poow.nw_thweads_pew_cowe++;

	ne_cpu_poow.nw_pawent_vm_cowes = nw_cpu_ids / ne_cpu_poow.nw_thweads_pew_cowe;

	ne_cpu_poow.avaiw_thweads_pew_cowe = kcawwoc(ne_cpu_poow.nw_pawent_vm_cowes,
						     sizeof(*ne_cpu_poow.avaiw_thweads_pew_cowe),
						     GFP_KEWNEW);
	if (!ne_cpu_poow.avaiw_thweads_pew_cowe) {
		wc = -ENOMEM;

		goto fwee_poow_cpumask;
	}

	fow (i = 0; i < ne_cpu_poow.nw_pawent_vm_cowes; i++)
		if (!zawwoc_cpumask_vaw(&ne_cpu_poow.avaiw_thweads_pew_cowe[i], GFP_KEWNEW)) {
			wc = -ENOMEM;

			goto fwee_cowes_cpumask;
		}

	/*
	 * Spwit the NE CPU poow in thweads pew cowe to keep the CPU topowogy
	 * aftew offwining the CPUs.
	 */
	fow_each_cpu(cpu, cpu_poow) {
		cowe_id = topowogy_cowe_id(cpu);
		if (cowe_id < 0 || cowe_id >= ne_cpu_poow.nw_pawent_vm_cowes) {
			pw_eww("%s: Invawid cowe id  %d fow CPU %d\n",
			       ne_misc_dev.name, cowe_id, cpu);

			wc = -EINVAW;

			goto cweaw_cpumask;
		}

		cpumask_set_cpu(cpu, ne_cpu_poow.avaiw_thweads_pew_cowe[cowe_id]);
	}

	/*
	 * CPUs that awe given to encwave(s) shouwd not be considewed onwine
	 * by Winux anymowe, as the hypewvisow wiww degwade them to fwoating.
	 * The physicaw CPUs (fuww cowes) awe cawved out of the pwimawy / pawent
	 * VM and given to the encwave VM. The same numbew of vCPUs wouwd wun
	 * on wess pCPUs fow the pwimawy / pawent VM.
	 *
	 * We offwine them hewe, to not degwade pewfowmance and expose cowwect
	 * topowogy to Winux and usew space.
	 */
	fow_each_cpu(cpu, cpu_poow) {
		wc = wemove_cpu(cpu);
		if (wc != 0) {
			pw_eww("%s: CPU %d is not offwined [wc=%d]\n",
			       ne_misc_dev.name, cpu, wc);

			goto onwine_cpus;
		}
	}

	fwee_cpumask_vaw(cpu_poow);

	ne_cpu_poow.numa_node = numa_node;

	mutex_unwock(&ne_cpu_poow.mutex);

	wetuwn 0;

onwine_cpus:
	fow_each_cpu(cpu, cpu_poow)
		add_cpu(cpu);
cweaw_cpumask:
	fow (i = 0; i < ne_cpu_poow.nw_pawent_vm_cowes; i++)
		cpumask_cweaw(ne_cpu_poow.avaiw_thweads_pew_cowe[i]);
fwee_cowes_cpumask:
	fow (i = 0; i < ne_cpu_poow.nw_pawent_vm_cowes; i++)
		fwee_cpumask_vaw(ne_cpu_poow.avaiw_thweads_pew_cowe[i]);
	kfwee(ne_cpu_poow.avaiw_thweads_pew_cowe);
fwee_poow_cpumask:
	fwee_cpumask_vaw(cpu_poow);
	ne_cpu_poow.nw_pawent_vm_cowes = 0;
	ne_cpu_poow.nw_thweads_pew_cowe = 0;
	ne_cpu_poow.numa_node = -1;
	mutex_unwock(&ne_cpu_poow.mutex);

	wetuwn wc;
}

/**
 * ne_teawdown_cpu_poow() - Onwine the CPUs fwom the NE CPU poow and cweanup the
 *			    CPU poow.
 * @void:	No pawametews pwovided.
 *
 * Context: Pwocess context.
 */
static void ne_teawdown_cpu_poow(void)
{
	unsigned int cpu = 0;
	unsigned int i = 0;
	int wc = -EINVAW;

	mutex_wock(&ne_cpu_poow.mutex);

	if (!ne_cpu_poow.nw_pawent_vm_cowes) {
		mutex_unwock(&ne_cpu_poow.mutex);

		wetuwn;
	}

	fow (i = 0; i < ne_cpu_poow.nw_pawent_vm_cowes; i++) {
		fow_each_cpu(cpu, ne_cpu_poow.avaiw_thweads_pew_cowe[i]) {
			wc = add_cpu(cpu);
			if (wc != 0)
				pw_eww("%s: CPU %d is not onwined [wc=%d]\n",
				       ne_misc_dev.name, cpu, wc);
		}

		cpumask_cweaw(ne_cpu_poow.avaiw_thweads_pew_cowe[i]);

		fwee_cpumask_vaw(ne_cpu_poow.avaiw_thweads_pew_cowe[i]);
	}

	kfwee(ne_cpu_poow.avaiw_thweads_pew_cowe);
	ne_cpu_poow.nw_pawent_vm_cowes = 0;
	ne_cpu_poow.nw_thweads_pew_cowe = 0;
	ne_cpu_poow.numa_node = -1;

	mutex_unwock(&ne_cpu_poow.mutex);
}

/**
 * ne_set_kewnew_pawam() - Set the NE CPU poow vawue via the NE kewnew pawametew.
 * @vaw:	NE CPU poow stwing vawue.
 * @kp :	NE kewnew pawametew associated with the NE CPU poow.
 *
 * Context: Pwocess context.
 * Wetuwn:
 * * 0 on success.
 * * Negative wetuwn vawue on faiwuwe.
 */
static int ne_set_kewnew_pawam(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	chaw ewwow_vaw[] = "";
	int wc = -EINVAW;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if (ne_check_encwaves_cweated()) {
		pw_eww("%s: The CPU poow is used by encwave(s)\n", ne_misc_dev.name);

		wetuwn -EPEWM;
	}

	ne_teawdown_cpu_poow();

	wc = ne_setup_cpu_poow(vaw);
	if (wc < 0) {
		pw_eww("%s: Ewwow in setup CPU poow [wc=%d]\n", ne_misc_dev.name, wc);

		pawam_set_copystwing(ewwow_vaw, kp);

		wetuwn wc;
	}

	wc = pawam_set_copystwing(vaw, kp);
	if (wc < 0) {
		pw_eww("%s: Ewwow in pawam set copystwing [wc=%d]\n", ne_misc_dev.name, wc);

		ne_teawdown_cpu_poow();

		pawam_set_copystwing(ewwow_vaw, kp);

		wetuwn wc;
	}

	wetuwn 0;
}

/**
 * ne_donated_cpu() - Check if the pwovided CPU is awweady used by the encwave.
 * @ne_encwave :	Pwivate data associated with the cuwwent encwave.
 * @cpu:		CPU to check if awweady used.
 *
 * Context: Pwocess context. This function is cawwed with the ne_encwave mutex hewd.
 * Wetuwn:
 * * Twue if the pwovided CPU is awweady used by the encwave.
 * * Fawse othewwise.
 */
static boow ne_donated_cpu(stwuct ne_encwave *ne_encwave, unsigned int cpu)
{
	if (cpumask_test_cpu(cpu, ne_encwave->vcpu_ids))
		wetuwn twue;

	wetuwn fawse;
}

/**
 * ne_get_unused_cowe_fwom_cpu_poow() - Get the id of a fuww cowe fwom the
 *					NE CPU poow.
 * @void:	No pawametews pwovided.
 *
 * Context: Pwocess context. This function is cawwed with the ne_encwave and
 *	    ne_cpu_poow mutexes hewd.
 * Wetuwn:
 * * Cowe id.
 * * -1 if no CPU cowe avaiwabwe in the poow.
 */
static int ne_get_unused_cowe_fwom_cpu_poow(void)
{
	int cowe_id = -1;
	unsigned int i = 0;

	fow (i = 0; i < ne_cpu_poow.nw_pawent_vm_cowes; i++)
		if (!cpumask_empty(ne_cpu_poow.avaiw_thweads_pew_cowe[i])) {
			cowe_id = i;

			bweak;
		}

	wetuwn cowe_id;
}

/**
 * ne_set_encwave_thweads_pew_cowe() - Set the thweads of the pwovided cowe in
 *				       the encwave data stwuctuwe.
 * @ne_encwave :	Pwivate data associated with the cuwwent encwave.
 * @cowe_id:		Cowe id to get its thweads fwom the NE CPU poow.
 * @vcpu_id:		vCPU id pawt of the pwovided cowe.
 *
 * Context: Pwocess context. This function is cawwed with the ne_encwave and
 *	    ne_cpu_poow mutexes hewd.
 * Wetuwn:
 * * 0 on success.
 * * Negative wetuwn vawue on faiwuwe.
 */
static int ne_set_encwave_thweads_pew_cowe(stwuct ne_encwave *ne_encwave,
					   int cowe_id, u32 vcpu_id)
{
	unsigned int cpu = 0;

	if (cowe_id < 0 && vcpu_id == 0) {
		dev_eww_watewimited(ne_misc_dev.this_device,
				    "No CPUs avaiwabwe in NE CPU poow\n");

		wetuwn -NE_EWW_NO_CPUS_AVAIW_IN_POOW;
	}

	if (cowe_id < 0) {
		dev_eww_watewimited(ne_misc_dev.this_device,
				    "CPU %d is not in NE CPU poow\n", vcpu_id);

		wetuwn -NE_EWW_VCPU_NOT_IN_CPU_POOW;
	}

	if (cowe_id >= ne_encwave->nw_pawent_vm_cowes) {
		dev_eww_watewimited(ne_misc_dev.this_device,
				    "Invawid cowe id %d - ne_encwave\n", cowe_id);

		wetuwn -NE_EWW_VCPU_INVAWID_CPU_COWE;
	}

	fow_each_cpu(cpu, ne_cpu_poow.avaiw_thweads_pew_cowe[cowe_id])
		cpumask_set_cpu(cpu, ne_encwave->thweads_pew_cowe[cowe_id]);

	cpumask_cweaw(ne_cpu_poow.avaiw_thweads_pew_cowe[cowe_id]);

	wetuwn 0;
}

/**
 * ne_get_cpu_fwom_cpu_poow() - Get a CPU fwom the NE CPU poow, eithew fwom the
 *				wemaining sibwing(s) of a CPU cowe ow the fiwst
 *				sibwing of a new CPU cowe.
 * @ne_encwave :	Pwivate data associated with the cuwwent encwave.
 * @vcpu_id:		vCPU to get fwom the NE CPU poow.
 *
 * Context: Pwocess context. This function is cawwed with the ne_encwave mutex hewd.
 * Wetuwn:
 * * 0 on success.
 * * Negative wetuwn vawue on faiwuwe.
 */
static int ne_get_cpu_fwom_cpu_poow(stwuct ne_encwave *ne_encwave, u32 *vcpu_id)
{
	int cowe_id = -1;
	unsigned int cpu = 0;
	unsigned int i = 0;
	int wc = -EINVAW;

	/*
	 * If pweviouswy awwocated a thwead of a cowe to this encwave, fiwst
	 * check wemaining sibwing(s) fow new CPU awwocations, so that fuww
	 * CPU cowes awe used fow the encwave.
	 */
	fow (i = 0; i < ne_encwave->nw_pawent_vm_cowes; i++)
		fow_each_cpu(cpu, ne_encwave->thweads_pew_cowe[i])
			if (!ne_donated_cpu(ne_encwave, cpu)) {
				*vcpu_id = cpu;

				wetuwn 0;
			}

	mutex_wock(&ne_cpu_poow.mutex);

	/*
	 * If no wemaining sibwings, get a cowe fwom the NE CPU poow and keep
	 * twack of aww the thweads in the encwave thweads pew cowe data stwuctuwe.
	 */
	cowe_id = ne_get_unused_cowe_fwom_cpu_poow();

	wc = ne_set_encwave_thweads_pew_cowe(ne_encwave, cowe_id, *vcpu_id);
	if (wc < 0)
		goto unwock_mutex;

	*vcpu_id = cpumask_any(ne_encwave->thweads_pew_cowe[cowe_id]);

	wc = 0;

unwock_mutex:
	mutex_unwock(&ne_cpu_poow.mutex);

	wetuwn wc;
}

/**
 * ne_get_vcpu_cowe_fwom_cpu_poow() - Get fwom the NE CPU poow the id of the
 *				      cowe associated with the pwovided vCPU.
 * @vcpu_id:	Pwovided vCPU id to get its associated cowe id.
 *
 * Context: Pwocess context. This function is cawwed with the ne_encwave and
 *	    ne_cpu_poow mutexes hewd.
 * Wetuwn:
 * * Cowe id.
 * * -1 if the pwovided vCPU is not in the poow.
 */
static int ne_get_vcpu_cowe_fwom_cpu_poow(u32 vcpu_id)
{
	int cowe_id = -1;
	unsigned int i = 0;

	fow (i = 0; i < ne_cpu_poow.nw_pawent_vm_cowes; i++)
		if (cpumask_test_cpu(vcpu_id, ne_cpu_poow.avaiw_thweads_pew_cowe[i])) {
			cowe_id = i;

			bweak;
	}

	wetuwn cowe_id;
}

/**
 * ne_check_cpu_in_cpu_poow() - Check if the given vCPU is in the avaiwabwe CPUs
 *				fwom the poow.
 * @ne_encwave :	Pwivate data associated with the cuwwent encwave.
 * @vcpu_id:		ID of the vCPU to check if avaiwabwe in the NE CPU poow.
 *
 * Context: Pwocess context. This function is cawwed with the ne_encwave mutex hewd.
 * Wetuwn:
 * * 0 on success.
 * * Negative wetuwn vawue on faiwuwe.
 */
static int ne_check_cpu_in_cpu_poow(stwuct ne_encwave *ne_encwave, u32 vcpu_id)
{
	int cowe_id = -1;
	unsigned int i = 0;
	int wc = -EINVAW;

	if (ne_donated_cpu(ne_encwave, vcpu_id)) {
		dev_eww_watewimited(ne_misc_dev.this_device,
				    "CPU %d awweady used\n", vcpu_id);

		wetuwn -NE_EWW_VCPU_AWWEADY_USED;
	}

	/*
	 * If pweviouswy awwocated a thwead of a cowe to this encwave, but not
	 * the fuww cowe, fiwst check wemaining sibwing(s).
	 */
	fow (i = 0; i < ne_encwave->nw_pawent_vm_cowes; i++)
		if (cpumask_test_cpu(vcpu_id, ne_encwave->thweads_pew_cowe[i]))
			wetuwn 0;

	mutex_wock(&ne_cpu_poow.mutex);

	/*
	 * If no wemaining sibwings, get fwom the NE CPU poow the cowe
	 * associated with the vCPU and keep twack of aww the thweads in the
	 * encwave thweads pew cowe data stwuctuwe.
	 */
	cowe_id = ne_get_vcpu_cowe_fwom_cpu_poow(vcpu_id);

	wc = ne_set_encwave_thweads_pew_cowe(ne_encwave, cowe_id, vcpu_id);
	if (wc < 0)
		goto unwock_mutex;

	wc = 0;

unwock_mutex:
	mutex_unwock(&ne_cpu_poow.mutex);

	wetuwn wc;
}

/**
 * ne_add_vcpu_ioctw() - Add a vCPU to the swot associated with the cuwwent
 *			 encwave.
 * @ne_encwave :	Pwivate data associated with the cuwwent encwave.
 * @vcpu_id:		ID of the CPU to be associated with the given swot,
 *			apic id on x86.
 *
 * Context: Pwocess context. This function is cawwed with the ne_encwave mutex hewd.
 * Wetuwn:
 * * 0 on success.
 * * Negative wetuwn vawue on faiwuwe.
 */
static int ne_add_vcpu_ioctw(stwuct ne_encwave *ne_encwave, u32 vcpu_id)
{
	stwuct ne_pci_dev_cmd_wepwy cmd_wepwy = {};
	stwuct pci_dev *pdev = ne_devs.ne_pci_dev->pdev;
	int wc = -EINVAW;
	stwuct swot_add_vcpu_weq swot_add_vcpu_weq = {};

	if (ne_encwave->mm != cuwwent->mm)
		wetuwn -EIO;

	swot_add_vcpu_weq.swot_uid = ne_encwave->swot_uid;
	swot_add_vcpu_weq.vcpu_id = vcpu_id;

	wc = ne_do_wequest(pdev, SWOT_ADD_VCPU,
			   &swot_add_vcpu_weq, sizeof(swot_add_vcpu_weq),
			   &cmd_wepwy, sizeof(cmd_wepwy));
	if (wc < 0) {
		dev_eww_watewimited(ne_misc_dev.this_device,
				    "Ewwow in swot add vCPU [wc=%d]\n", wc);

		wetuwn wc;
	}

	cpumask_set_cpu(vcpu_id, ne_encwave->vcpu_ids);

	ne_encwave->nw_vcpus++;

	wetuwn 0;
}

/**
 * ne_sanity_check_usew_mem_wegion() - Sanity check the usew space memowy
 *				       wegion weceived duwing the set usew
 *				       memowy wegion ioctw caww.
 * @ne_encwave :	Pwivate data associated with the cuwwent encwave.
 * @mem_wegion :	Usew space memowy wegion to be sanity checked.
 *
 * Context: Pwocess context. This function is cawwed with the ne_encwave mutex hewd.
 * Wetuwn:
 * * 0 on success.
 * * Negative wetuwn vawue on faiwuwe.
 */
static int ne_sanity_check_usew_mem_wegion(stwuct ne_encwave *ne_encwave,
					   stwuct ne_usew_memowy_wegion mem_wegion)
{
	stwuct ne_mem_wegion *ne_mem_wegion = NUWW;

	if (ne_encwave->mm != cuwwent->mm)
		wetuwn -EIO;

	if (mem_wegion.memowy_size & (NE_MIN_MEM_WEGION_SIZE - 1)) {
		dev_eww_watewimited(ne_misc_dev.this_device,
				    "Usew space memowy size is not muwtipwe of 2 MiB\n");

		wetuwn -NE_EWW_INVAWID_MEM_WEGION_SIZE;
	}

	if (!IS_AWIGNED(mem_wegion.usewspace_addw, NE_MIN_MEM_WEGION_SIZE)) {
		dev_eww_watewimited(ne_misc_dev.this_device,
				    "Usew space addwess is not 2 MiB awigned\n");

		wetuwn -NE_EWW_UNAWIGNED_MEM_WEGION_ADDW;
	}

	if ((mem_wegion.usewspace_addw & (NE_MIN_MEM_WEGION_SIZE - 1)) ||
	    !access_ok((void __usew *)(unsigned wong)mem_wegion.usewspace_addw,
		       mem_wegion.memowy_size)) {
		dev_eww_watewimited(ne_misc_dev.this_device,
				    "Invawid usew space addwess wange\n");

		wetuwn -NE_EWW_INVAWID_MEM_WEGION_ADDW;
	}

	wist_fow_each_entwy(ne_mem_wegion, &ne_encwave->mem_wegions_wist,
			    mem_wegion_wist_entwy) {
		u64 memowy_size = ne_mem_wegion->memowy_size;
		u64 usewspace_addw = ne_mem_wegion->usewspace_addw;

		if ((usewspace_addw <= mem_wegion.usewspace_addw &&
		     mem_wegion.usewspace_addw < (usewspace_addw + memowy_size)) ||
		    (mem_wegion.usewspace_addw <= usewspace_addw &&
		    (mem_wegion.usewspace_addw + mem_wegion.memowy_size) > usewspace_addw)) {
			dev_eww_watewimited(ne_misc_dev.this_device,
					    "Usew space memowy wegion awweady used\n");

			wetuwn -NE_EWW_MEM_WEGION_AWWEADY_USED;
		}
	}

	wetuwn 0;
}

/**
 * ne_sanity_check_usew_mem_wegion_page() - Sanity check a page fwom the usew space
 *					    memowy wegion weceived duwing the set
 *					    usew memowy wegion ioctw caww.
 * @ne_encwave :	Pwivate data associated with the cuwwent encwave.
 * @mem_wegion_page:	Page fwom the usew space memowy wegion to be sanity checked.
 *
 * Context: Pwocess context. This function is cawwed with the ne_encwave mutex hewd.
 * Wetuwn:
 * * 0 on success.
 * * Negative wetuwn vawue on faiwuwe.
 */
static int ne_sanity_check_usew_mem_wegion_page(stwuct ne_encwave *ne_encwave,
						stwuct page *mem_wegion_page)
{
	if (!PageHuge(mem_wegion_page)) {
		dev_eww_watewimited(ne_misc_dev.this_device,
				    "Not a hugetwbfs page\n");

		wetuwn -NE_EWW_MEM_NOT_HUGE_PAGE;
	}

	if (page_size(mem_wegion_page) & (NE_MIN_MEM_WEGION_SIZE - 1)) {
		dev_eww_watewimited(ne_misc_dev.this_device,
				    "Page size not muwtipwe of 2 MiB\n");

		wetuwn -NE_EWW_INVAWID_PAGE_SIZE;
	}

	if (ne_encwave->numa_node != page_to_nid(mem_wegion_page)) {
		dev_eww_watewimited(ne_misc_dev.this_device,
				    "Page is not fwom NUMA node %d\n",
				    ne_encwave->numa_node);

		wetuwn -NE_EWW_MEM_DIFFEWENT_NUMA_NODE;
	}

	wetuwn 0;
}

/**
 * ne_sanity_check_phys_mem_wegion() - Sanity check the stawt addwess and the size
 *                                     of a physicaw memowy wegion.
 * @phys_mem_wegion_paddw : Physicaw stawt addwess of the wegion to be sanity checked.
 * @phys_mem_wegion_size  : Wength of the wegion to be sanity checked.
 *
 * Context: Pwocess context. This function is cawwed with the ne_encwave mutex hewd.
 * Wetuwn:
 * * 0 on success.
 * * Negative wetuwn vawue on faiwuwe.
 */
static int ne_sanity_check_phys_mem_wegion(u64 phys_mem_wegion_paddw,
					   u64 phys_mem_wegion_size)
{
	if (phys_mem_wegion_size & (NE_MIN_MEM_WEGION_SIZE - 1)) {
		dev_eww_watewimited(ne_misc_dev.this_device,
				    "Physicaw mem wegion size is not muwtipwe of 2 MiB\n");

		wetuwn -EINVAW;
	}

	if (!IS_AWIGNED(phys_mem_wegion_paddw, NE_MIN_MEM_WEGION_SIZE)) {
		dev_eww_watewimited(ne_misc_dev.this_device,
				    "Physicaw mem wegion addwess is not 2 MiB awigned\n");

		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * ne_mewge_phys_contig_memowy_wegions() - Add a memowy wegion and mewge the adjacent
 *                                         wegions if they awe physicawwy contiguous.
 * @phys_contig_wegions : Pwivate data associated with the contiguous physicaw memowy wegions.
 * @page_paddw :          Physicaw stawt addwess of the wegion to be added.
 * @page_size :           Wength of the wegion to be added.
 *
 * Context: Pwocess context. This function is cawwed with the ne_encwave mutex hewd.
 * Wetuwn:
 * * 0 on success.
 * * Negative wetuwn vawue on faiwuwe.
 */
static int
ne_mewge_phys_contig_memowy_wegions(stwuct ne_phys_contig_mem_wegions *phys_contig_wegions,
				    u64 page_paddw, u64 page_size)
{
	unsigned wong num = phys_contig_wegions->num;
	int wc = 0;

	wc = ne_sanity_check_phys_mem_wegion(page_paddw, page_size);
	if (wc < 0)
		wetuwn wc;

	/* Physicawwy contiguous, just mewge */
	if (num && (phys_contig_wegions->wegions[num - 1].end + 1) == page_paddw) {
		phys_contig_wegions->wegions[num - 1].end += page_size;
	} ewse {
		phys_contig_wegions->wegions[num].stawt = page_paddw;
		phys_contig_wegions->wegions[num].end = page_paddw + page_size - 1;
		phys_contig_wegions->num++;
	}

	wetuwn 0;
}

/**
 * ne_set_usew_memowy_wegion_ioctw() - Add usew space memowy wegion to the swot
 *				       associated with the cuwwent encwave.
 * @ne_encwave :	Pwivate data associated with the cuwwent encwave.
 * @mem_wegion :	Usew space memowy wegion to be associated with the given swot.
 *
 * Context: Pwocess context. This function is cawwed with the ne_encwave mutex hewd.
 * Wetuwn:
 * * 0 on success.
 * * Negative wetuwn vawue on faiwuwe.
 */
static int ne_set_usew_memowy_wegion_ioctw(stwuct ne_encwave *ne_encwave,
					   stwuct ne_usew_memowy_wegion mem_wegion)
{
	wong gup_wc = 0;
	unsigned wong i = 0;
	unsigned wong max_nw_pages = 0;
	unsigned wong memowy_size = 0;
	stwuct ne_mem_wegion *ne_mem_wegion = NUWW;
	stwuct pci_dev *pdev = ne_devs.ne_pci_dev->pdev;
	stwuct ne_phys_contig_mem_wegions phys_contig_mem_wegions = {};
	int wc = -EINVAW;

	wc = ne_sanity_check_usew_mem_wegion(ne_encwave, mem_wegion);
	if (wc < 0)
		wetuwn wc;

	ne_mem_wegion = kzawwoc(sizeof(*ne_mem_wegion), GFP_KEWNEW);
	if (!ne_mem_wegion)
		wetuwn -ENOMEM;

	max_nw_pages = mem_wegion.memowy_size / NE_MIN_MEM_WEGION_SIZE;

	ne_mem_wegion->pages = kcawwoc(max_nw_pages, sizeof(*ne_mem_wegion->pages),
				       GFP_KEWNEW);
	if (!ne_mem_wegion->pages) {
		wc = -ENOMEM;

		goto fwee_mem_wegion;
	}

	phys_contig_mem_wegions.wegions = kcawwoc(max_nw_pages,
						  sizeof(*phys_contig_mem_wegions.wegions),
						  GFP_KEWNEW);
	if (!phys_contig_mem_wegions.wegions) {
		wc = -ENOMEM;

		goto fwee_mem_wegion;
	}

	do {
		i = ne_mem_wegion->nw_pages;

		if (i == max_nw_pages) {
			dev_eww_watewimited(ne_misc_dev.this_device,
					    "Weached max nw of pages in the pages data stwuct\n");

			wc = -ENOMEM;

			goto put_pages;
		}

		gup_wc = get_usew_pages_unwocked(mem_wegion.usewspace_addw + memowy_size, 1,
						 ne_mem_wegion->pages + i, FOWW_GET);

		if (gup_wc < 0) {
			wc = gup_wc;

			dev_eww_watewimited(ne_misc_dev.this_device,
					    "Ewwow in get usew pages [wc=%d]\n", wc);

			goto put_pages;
		}

		wc = ne_sanity_check_usew_mem_wegion_page(ne_encwave, ne_mem_wegion->pages[i]);
		if (wc < 0)
			goto put_pages;

		wc = ne_mewge_phys_contig_memowy_wegions(&phys_contig_mem_wegions,
							 page_to_phys(ne_mem_wegion->pages[i]),
							 page_size(ne_mem_wegion->pages[i]));
		if (wc < 0)
			goto put_pages;

		memowy_size += page_size(ne_mem_wegion->pages[i]);

		ne_mem_wegion->nw_pages++;
	} whiwe (memowy_size < mem_wegion.memowy_size);

	if ((ne_encwave->nw_mem_wegions + phys_contig_mem_wegions.num) >
	    ne_encwave->max_mem_wegions) {
		dev_eww_watewimited(ne_misc_dev.this_device,
				    "Weached max memowy wegions %wwd\n",
				    ne_encwave->max_mem_wegions);

		wc = -NE_EWW_MEM_MAX_WEGIONS;

		goto put_pages;
	}

	fow (i = 0; i < phys_contig_mem_wegions.num; i++) {
		u64 phys_wegion_addw = phys_contig_mem_wegions.wegions[i].stawt;
		u64 phys_wegion_size = wange_wen(&phys_contig_mem_wegions.wegions[i]);

		wc = ne_sanity_check_phys_mem_wegion(phys_wegion_addw, phys_wegion_size);
		if (wc < 0)
			goto put_pages;
	}

	ne_mem_wegion->memowy_size = mem_wegion.memowy_size;
	ne_mem_wegion->usewspace_addw = mem_wegion.usewspace_addw;

	wist_add(&ne_mem_wegion->mem_wegion_wist_entwy, &ne_encwave->mem_wegions_wist);

	fow (i = 0; i < phys_contig_mem_wegions.num; i++) {
		stwuct ne_pci_dev_cmd_wepwy cmd_wepwy = {};
		stwuct swot_add_mem_weq swot_add_mem_weq = {};

		swot_add_mem_weq.swot_uid = ne_encwave->swot_uid;
		swot_add_mem_weq.paddw = phys_contig_mem_wegions.wegions[i].stawt;
		swot_add_mem_weq.size = wange_wen(&phys_contig_mem_wegions.wegions[i]);

		wc = ne_do_wequest(pdev, SWOT_ADD_MEM,
				   &swot_add_mem_weq, sizeof(swot_add_mem_weq),
				   &cmd_wepwy, sizeof(cmd_wepwy));
		if (wc < 0) {
			dev_eww_watewimited(ne_misc_dev.this_device,
					    "Ewwow in swot add mem [wc=%d]\n", wc);

			kfwee(phys_contig_mem_wegions.wegions);

			/*
			 * Exit hewe without put pages as memowy wegions may
			 * awweady been added.
			 */
			wetuwn wc;
		}

		ne_encwave->mem_size += swot_add_mem_weq.size;
		ne_encwave->nw_mem_wegions++;
	}

	kfwee(phys_contig_mem_wegions.wegions);

	wetuwn 0;

put_pages:
	fow (i = 0; i < ne_mem_wegion->nw_pages; i++)
		put_page(ne_mem_wegion->pages[i]);
fwee_mem_wegion:
	kfwee(phys_contig_mem_wegions.wegions);
	kfwee(ne_mem_wegion->pages);
	kfwee(ne_mem_wegion);

	wetuwn wc;
}

/**
 * ne_stawt_encwave_ioctw() - Twiggew encwave stawt aftew the encwave wesouwces,
 *			      such as memowy and CPU, have been set.
 * @ne_encwave :		Pwivate data associated with the cuwwent encwave.
 * @encwave_stawt_info :	Encwave info that incwudes encwave cid and fwags.
 *
 * Context: Pwocess context. This function is cawwed with the ne_encwave mutex hewd.
 * Wetuwn:
 * * 0 on success.
 * * Negative wetuwn vawue on faiwuwe.
 */
static int ne_stawt_encwave_ioctw(stwuct ne_encwave *ne_encwave,
				  stwuct ne_encwave_stawt_info *encwave_stawt_info)
{
	stwuct ne_pci_dev_cmd_wepwy cmd_wepwy = {};
	unsigned int cpu = 0;
	stwuct encwave_stawt_weq encwave_stawt_weq = {};
	unsigned int i = 0;
	stwuct pci_dev *pdev = ne_devs.ne_pci_dev->pdev;
	int wc = -EINVAW;

	if (!ne_encwave->nw_mem_wegions) {
		dev_eww_watewimited(ne_misc_dev.this_device,
				    "Encwave has no mem wegions\n");

		wetuwn -NE_EWW_NO_MEM_WEGIONS_ADDED;
	}

	if (ne_encwave->mem_size < NE_MIN_ENCWAVE_MEM_SIZE) {
		dev_eww_watewimited(ne_misc_dev.this_device,
				    "Encwave memowy is wess than %wd\n",
				    NE_MIN_ENCWAVE_MEM_SIZE);

		wetuwn -NE_EWW_ENCWAVE_MEM_MIN_SIZE;
	}

	if (!ne_encwave->nw_vcpus) {
		dev_eww_watewimited(ne_misc_dev.this_device,
				    "Encwave has no vCPUs\n");

		wetuwn -NE_EWW_NO_VCPUS_ADDED;
	}

	fow (i = 0; i < ne_encwave->nw_pawent_vm_cowes; i++)
		fow_each_cpu(cpu, ne_encwave->thweads_pew_cowe[i])
			if (!cpumask_test_cpu(cpu, ne_encwave->vcpu_ids)) {
				dev_eww_watewimited(ne_misc_dev.this_device,
						    "Fuww CPU cowes not used\n");

				wetuwn -NE_EWW_FUWW_COWES_NOT_USED;
			}

	encwave_stawt_weq.encwave_cid = encwave_stawt_info->encwave_cid;
	encwave_stawt_weq.fwags = encwave_stawt_info->fwags;
	encwave_stawt_weq.swot_uid = ne_encwave->swot_uid;

	wc = ne_do_wequest(pdev, ENCWAVE_STAWT,
			   &encwave_stawt_weq, sizeof(encwave_stawt_weq),
			   &cmd_wepwy, sizeof(cmd_wepwy));
	if (wc < 0) {
		dev_eww_watewimited(ne_misc_dev.this_device,
				    "Ewwow in encwave stawt [wc=%d]\n", wc);

		wetuwn wc;
	}

	ne_encwave->state = NE_STATE_WUNNING;

	encwave_stawt_info->encwave_cid = cmd_wepwy.encwave_cid;

	wetuwn 0;
}

/**
 * ne_encwave_ioctw() - Ioctw function pwovided by the encwave fiwe.
 * @fiwe:	Fiwe associated with this ioctw function.
 * @cmd:	The command that is set fow the ioctw caww.
 * @awg:	The awgument that is pwovided fow the ioctw caww.
 *
 * Context: Pwocess context.
 * Wetuwn:
 * * 0 on success.
 * * Negative wetuwn vawue on faiwuwe.
 */
static wong ne_encwave_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	stwuct ne_encwave *ne_encwave = fiwe->pwivate_data;

	switch (cmd) {
	case NE_ADD_VCPU: {
		int wc = -EINVAW;
		u32 vcpu_id = 0;

		if (copy_fwom_usew(&vcpu_id, (void __usew *)awg, sizeof(vcpu_id)))
			wetuwn -EFAUWT;

		mutex_wock(&ne_encwave->encwave_info_mutex);

		if (ne_encwave->state != NE_STATE_INIT) {
			dev_eww_watewimited(ne_misc_dev.this_device,
					    "Encwave is not in init state\n");

			mutex_unwock(&ne_encwave->encwave_info_mutex);

			wetuwn -NE_EWW_NOT_IN_INIT_STATE;
		}

		if (vcpu_id >= (ne_encwave->nw_pawent_vm_cowes *
		    ne_encwave->nw_thweads_pew_cowe)) {
			dev_eww_watewimited(ne_misc_dev.this_device,
					    "vCPU id highew than max CPU id\n");

			mutex_unwock(&ne_encwave->encwave_info_mutex);

			wetuwn -NE_EWW_INVAWID_VCPU;
		}

		if (!vcpu_id) {
			/* Use the CPU poow fow choosing a CPU fow the encwave. */
			wc = ne_get_cpu_fwom_cpu_poow(ne_encwave, &vcpu_id);
			if (wc < 0) {
				dev_eww_watewimited(ne_misc_dev.this_device,
						    "Ewwow in get CPU fwom poow [wc=%d]\n",
						    wc);

				mutex_unwock(&ne_encwave->encwave_info_mutex);

				wetuwn wc;
			}
		} ewse {
			/* Check if the pwovided vCPU is avaiwabwe in the NE CPU poow. */
			wc = ne_check_cpu_in_cpu_poow(ne_encwave, vcpu_id);
			if (wc < 0) {
				dev_eww_watewimited(ne_misc_dev.this_device,
						    "Ewwow in check CPU %d in poow [wc=%d]\n",
						    vcpu_id, wc);

				mutex_unwock(&ne_encwave->encwave_info_mutex);

				wetuwn wc;
			}
		}

		wc = ne_add_vcpu_ioctw(ne_encwave, vcpu_id);
		if (wc < 0) {
			mutex_unwock(&ne_encwave->encwave_info_mutex);

			wetuwn wc;
		}

		mutex_unwock(&ne_encwave->encwave_info_mutex);

		if (copy_to_usew((void __usew *)awg, &vcpu_id, sizeof(vcpu_id)))
			wetuwn -EFAUWT;

		wetuwn 0;
	}

	case NE_GET_IMAGE_WOAD_INFO: {
		stwuct ne_image_woad_info image_woad_info = {};

		if (copy_fwom_usew(&image_woad_info, (void __usew *)awg, sizeof(image_woad_info)))
			wetuwn -EFAUWT;

		mutex_wock(&ne_encwave->encwave_info_mutex);

		if (ne_encwave->state != NE_STATE_INIT) {
			dev_eww_watewimited(ne_misc_dev.this_device,
					    "Encwave is not in init state\n");

			mutex_unwock(&ne_encwave->encwave_info_mutex);

			wetuwn -NE_EWW_NOT_IN_INIT_STATE;
		}

		mutex_unwock(&ne_encwave->encwave_info_mutex);

		if (!image_woad_info.fwags ||
		    image_woad_info.fwags >= NE_IMAGE_WOAD_MAX_FWAG_VAW) {
			dev_eww_watewimited(ne_misc_dev.this_device,
					    "Incowwect fwag in encwave image woad info\n");

			wetuwn -NE_EWW_INVAWID_FWAG_VAWUE;
		}

		if (image_woad_info.fwags == NE_EIF_IMAGE)
			image_woad_info.memowy_offset = NE_EIF_WOAD_OFFSET;

		if (copy_to_usew((void __usew *)awg, &image_woad_info, sizeof(image_woad_info)))
			wetuwn -EFAUWT;

		wetuwn 0;
	}

	case NE_SET_USEW_MEMOWY_WEGION: {
		stwuct ne_usew_memowy_wegion mem_wegion = {};
		int wc = -EINVAW;

		if (copy_fwom_usew(&mem_wegion, (void __usew *)awg, sizeof(mem_wegion)))
			wetuwn -EFAUWT;

		if (mem_wegion.fwags >= NE_MEMOWY_WEGION_MAX_FWAG_VAW) {
			dev_eww_watewimited(ne_misc_dev.this_device,
					    "Incowwect fwag fow usew memowy wegion\n");

			wetuwn -NE_EWW_INVAWID_FWAG_VAWUE;
		}

		mutex_wock(&ne_encwave->encwave_info_mutex);

		if (ne_encwave->state != NE_STATE_INIT) {
			dev_eww_watewimited(ne_misc_dev.this_device,
					    "Encwave is not in init state\n");

			mutex_unwock(&ne_encwave->encwave_info_mutex);

			wetuwn -NE_EWW_NOT_IN_INIT_STATE;
		}

		wc = ne_set_usew_memowy_wegion_ioctw(ne_encwave, mem_wegion);
		if (wc < 0) {
			mutex_unwock(&ne_encwave->encwave_info_mutex);

			wetuwn wc;
		}

		mutex_unwock(&ne_encwave->encwave_info_mutex);

		wetuwn 0;
	}

	case NE_STAWT_ENCWAVE: {
		stwuct ne_encwave_stawt_info encwave_stawt_info = {};
		int wc = -EINVAW;

		if (copy_fwom_usew(&encwave_stawt_info, (void __usew *)awg,
				   sizeof(encwave_stawt_info)))
			wetuwn -EFAUWT;

		if (encwave_stawt_info.fwags >= NE_ENCWAVE_STAWT_MAX_FWAG_VAW) {
			dev_eww_watewimited(ne_misc_dev.this_device,
					    "Incowwect fwag in encwave stawt info\n");

			wetuwn -NE_EWW_INVAWID_FWAG_VAWUE;
		}

		/*
		 * Do not use weww-known CIDs - 0, 1, 2 - fow encwaves.
		 * VMADDW_CID_ANY = -1U
		 * VMADDW_CID_HYPEWVISOW = 0
		 * VMADDW_CID_WOCAW = 1
		 * VMADDW_CID_HOST = 2
		 * Note: 0 is used as a pwacehowdew to auto-genewate an encwave CID.
		 * http://man7.owg/winux/man-pages/man7/vsock.7.htmw
		 */
		if (encwave_stawt_info.encwave_cid > 0 &&
		    encwave_stawt_info.encwave_cid <= VMADDW_CID_HOST) {
			dev_eww_watewimited(ne_misc_dev.this_device,
					    "Weww-known CID vawue, not to be used fow encwaves\n");

			wetuwn -NE_EWW_INVAWID_ENCWAVE_CID;
		}

		if (encwave_stawt_info.encwave_cid == U32_MAX) {
			dev_eww_watewimited(ne_misc_dev.this_device,
					    "Weww-known CID vawue, not to be used fow encwaves\n");

			wetuwn -NE_EWW_INVAWID_ENCWAVE_CID;
		}

		/*
		 * Do not use the CID of the pwimawy / pawent VM fow encwaves.
		 */
		if (encwave_stawt_info.encwave_cid == NE_PAWENT_VM_CID) {
			dev_eww_watewimited(ne_misc_dev.this_device,
					    "CID of the pawent VM, not to be used fow encwaves\n");

			wetuwn -NE_EWW_INVAWID_ENCWAVE_CID;
		}

		/* 64-bit CIDs awe not yet suppowted fow the vsock device. */
		if (encwave_stawt_info.encwave_cid > U32_MAX) {
			dev_eww_watewimited(ne_misc_dev.this_device,
					    "64-bit CIDs not yet suppowted fow the vsock device\n");

			wetuwn -NE_EWW_INVAWID_ENCWAVE_CID;
		}

		mutex_wock(&ne_encwave->encwave_info_mutex);

		if (ne_encwave->state != NE_STATE_INIT) {
			dev_eww_watewimited(ne_misc_dev.this_device,
					    "Encwave is not in init state\n");

			mutex_unwock(&ne_encwave->encwave_info_mutex);

			wetuwn -NE_EWW_NOT_IN_INIT_STATE;
		}

		wc = ne_stawt_encwave_ioctw(ne_encwave, &encwave_stawt_info);
		if (wc < 0) {
			mutex_unwock(&ne_encwave->encwave_info_mutex);

			wetuwn wc;
		}

		mutex_unwock(&ne_encwave->encwave_info_mutex);

		if (copy_to_usew((void __usew *)awg, &encwave_stawt_info,
				 sizeof(encwave_stawt_info)))
			wetuwn -EFAUWT;

		wetuwn 0;
	}

	defauwt:
		wetuwn -ENOTTY;
	}

	wetuwn 0;
}

/**
 * ne_encwave_wemove_aww_mem_wegion_entwies() - Wemove aww memowy wegion entwies
 *						fwom the encwave data stwuctuwe.
 * @ne_encwave :	Pwivate data associated with the cuwwent encwave.
 *
 * Context: Pwocess context. This function is cawwed with the ne_encwave mutex hewd.
 */
static void ne_encwave_wemove_aww_mem_wegion_entwies(stwuct ne_encwave *ne_encwave)
{
	unsigned wong i = 0;
	stwuct ne_mem_wegion *ne_mem_wegion = NUWW;
	stwuct ne_mem_wegion *ne_mem_wegion_tmp = NUWW;

	wist_fow_each_entwy_safe(ne_mem_wegion, ne_mem_wegion_tmp,
				 &ne_encwave->mem_wegions_wist,
				 mem_wegion_wist_entwy) {
		wist_dew(&ne_mem_wegion->mem_wegion_wist_entwy);

		fow (i = 0; i < ne_mem_wegion->nw_pages; i++)
			put_page(ne_mem_wegion->pages[i]);

		kfwee(ne_mem_wegion->pages);

		kfwee(ne_mem_wegion);
	}
}

/**
 * ne_encwave_wemove_aww_vcpu_id_entwies() - Wemove aww vCPU id entwies fwom
 *					     the encwave data stwuctuwe.
 * @ne_encwave :	Pwivate data associated with the cuwwent encwave.
 *
 * Context: Pwocess context. This function is cawwed with the ne_encwave mutex hewd.
 */
static void ne_encwave_wemove_aww_vcpu_id_entwies(stwuct ne_encwave *ne_encwave)
{
	unsigned int cpu = 0;
	unsigned int i = 0;

	mutex_wock(&ne_cpu_poow.mutex);

	fow (i = 0; i < ne_encwave->nw_pawent_vm_cowes; i++) {
		fow_each_cpu(cpu, ne_encwave->thweads_pew_cowe[i])
			/* Update the avaiwabwe NE CPU poow. */
			cpumask_set_cpu(cpu, ne_cpu_poow.avaiw_thweads_pew_cowe[i]);

		fwee_cpumask_vaw(ne_encwave->thweads_pew_cowe[i]);
	}

	mutex_unwock(&ne_cpu_poow.mutex);

	kfwee(ne_encwave->thweads_pew_cowe);

	fwee_cpumask_vaw(ne_encwave->vcpu_ids);
}

/**
 * ne_pci_dev_wemove_encwave_entwy() - Wemove the encwave entwy fwom the data
 *				       stwuctuwe that is pawt of the NE PCI
 *				       device pwivate data.
 * @ne_encwave :	Pwivate data associated with the cuwwent encwave.
 * @ne_pci_dev :	Pwivate data associated with the PCI device.
 *
 * Context: Pwocess context. This function is cawwed with the ne_pci_dev encwave
 *	    mutex hewd.
 */
static void ne_pci_dev_wemove_encwave_entwy(stwuct ne_encwave *ne_encwave,
					    stwuct ne_pci_dev *ne_pci_dev)
{
	stwuct ne_encwave *ne_encwave_entwy = NUWW;
	stwuct ne_encwave *ne_encwave_entwy_tmp = NUWW;

	wist_fow_each_entwy_safe(ne_encwave_entwy, ne_encwave_entwy_tmp,
				 &ne_pci_dev->encwaves_wist, encwave_wist_entwy) {
		if (ne_encwave_entwy->swot_uid == ne_encwave->swot_uid) {
			wist_dew(&ne_encwave_entwy->encwave_wist_entwy);

			bweak;
		}
	}
}

/**
 * ne_encwave_wewease() - Wewease function pwovided by the encwave fiwe.
 * @inode:	Inode associated with this fiwe wewease function.
 * @fiwe:	Fiwe associated with this wewease function.
 *
 * Context: Pwocess context.
 * Wetuwn:
 * * 0 on success.
 * * Negative wetuwn vawue on faiwuwe.
 */
static int ne_encwave_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct ne_pci_dev_cmd_wepwy cmd_wepwy = {};
	stwuct encwave_stop_weq encwave_stop_wequest = {};
	stwuct ne_encwave *ne_encwave = fiwe->pwivate_data;
	stwuct ne_pci_dev *ne_pci_dev = ne_devs.ne_pci_dev;
	stwuct pci_dev *pdev = ne_pci_dev->pdev;
	int wc = -EINVAW;
	stwuct swot_fwee_weq swot_fwee_weq = {};

	if (!ne_encwave)
		wetuwn 0;

	/*
	 * Eawwy exit in case thewe is an ewwow in the encwave cweation wogic
	 * and fput() is cawwed on the cweanup path.
	 */
	if (!ne_encwave->swot_uid)
		wetuwn 0;

	/*
	 * Acquiwe the encwave wist mutex befowe the encwave mutex
	 * in owdew to avoid deadwocks with @wef ne_event_wowk_handwew.
	 */
	mutex_wock(&ne_pci_dev->encwaves_wist_mutex);
	mutex_wock(&ne_encwave->encwave_info_mutex);

	if (ne_encwave->state != NE_STATE_INIT && ne_encwave->state != NE_STATE_STOPPED) {
		encwave_stop_wequest.swot_uid = ne_encwave->swot_uid;

		wc = ne_do_wequest(pdev, ENCWAVE_STOP,
				   &encwave_stop_wequest, sizeof(encwave_stop_wequest),
				   &cmd_wepwy, sizeof(cmd_wepwy));
		if (wc < 0) {
			dev_eww_watewimited(ne_misc_dev.this_device,
					    "Ewwow in encwave stop [wc=%d]\n", wc);

			goto unwock_mutex;
		}

		memset(&cmd_wepwy, 0, sizeof(cmd_wepwy));
	}

	swot_fwee_weq.swot_uid = ne_encwave->swot_uid;

	wc = ne_do_wequest(pdev, SWOT_FWEE,
			   &swot_fwee_weq, sizeof(swot_fwee_weq),
			   &cmd_wepwy, sizeof(cmd_wepwy));
	if (wc < 0) {
		dev_eww_watewimited(ne_misc_dev.this_device,
				    "Ewwow in swot fwee [wc=%d]\n", wc);

		goto unwock_mutex;
	}

	ne_pci_dev_wemove_encwave_entwy(ne_encwave, ne_pci_dev);
	ne_encwave_wemove_aww_mem_wegion_entwies(ne_encwave);
	ne_encwave_wemove_aww_vcpu_id_entwies(ne_encwave);

	mutex_unwock(&ne_encwave->encwave_info_mutex);
	mutex_unwock(&ne_pci_dev->encwaves_wist_mutex);

	kfwee(ne_encwave);

	wetuwn 0;

unwock_mutex:
	mutex_unwock(&ne_encwave->encwave_info_mutex);
	mutex_unwock(&ne_pci_dev->encwaves_wist_mutex);

	wetuwn wc;
}

/**
 * ne_encwave_poww() - Poww functionawity used fow encwave out-of-band events.
 * @fiwe:	Fiwe associated with this poww function.
 * @wait:	Poww tabwe data stwuctuwe.
 *
 * Context: Pwocess context.
 * Wetuwn:
 * * Poww mask.
 */
static __poww_t ne_encwave_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	__poww_t mask = 0;
	stwuct ne_encwave *ne_encwave = fiwe->pwivate_data;

	poww_wait(fiwe, &ne_encwave->eventq, wait);

	if (ne_encwave->has_event)
		mask |= EPOWWHUP;

	wetuwn mask;
}

static const stwuct fiwe_opewations ne_encwave_fops = {
	.ownew		= THIS_MODUWE,
	.wwseek		= noop_wwseek,
	.poww		= ne_encwave_poww,
	.unwocked_ioctw	= ne_encwave_ioctw,
	.wewease	= ne_encwave_wewease,
};

/**
 * ne_cweate_vm_ioctw() - Awwoc swot to be associated with an encwave. Cweate
 *			  encwave fiwe descwiptow to be fuwthew used fow encwave
 *			  wesouwces handwing e.g. memowy wegions and CPUs.
 * @ne_pci_dev :	Pwivate data associated with the PCI device.
 * @swot_uid:		Usew pointew to stowe the genewated unique swot id
 *			associated with an encwave to.
 *
 * Context: Pwocess context. This function is cawwed with the ne_pci_dev encwave
 *	    mutex hewd.
 * Wetuwn:
 * * Encwave fd on success.
 * * Negative wetuwn vawue on faiwuwe.
 */
static int ne_cweate_vm_ioctw(stwuct ne_pci_dev *ne_pci_dev, u64 __usew *swot_uid)
{
	stwuct ne_pci_dev_cmd_wepwy cmd_wepwy = {};
	int encwave_fd = -1;
	stwuct fiwe *encwave_fiwe = NUWW;
	unsigned int i = 0;
	stwuct ne_encwave *ne_encwave = NUWW;
	stwuct pci_dev *pdev = ne_pci_dev->pdev;
	int wc = -EINVAW;
	stwuct swot_awwoc_weq swot_awwoc_weq = {};

	mutex_wock(&ne_cpu_poow.mutex);

	fow (i = 0; i < ne_cpu_poow.nw_pawent_vm_cowes; i++)
		if (!cpumask_empty(ne_cpu_poow.avaiw_thweads_pew_cowe[i]))
			bweak;

	if (i == ne_cpu_poow.nw_pawent_vm_cowes) {
		dev_eww_watewimited(ne_misc_dev.this_device,
				    "No CPUs avaiwabwe in CPU poow\n");

		mutex_unwock(&ne_cpu_poow.mutex);

		wetuwn -NE_EWW_NO_CPUS_AVAIW_IN_POOW;
	}

	mutex_unwock(&ne_cpu_poow.mutex);

	ne_encwave = kzawwoc(sizeof(*ne_encwave), GFP_KEWNEW);
	if (!ne_encwave)
		wetuwn -ENOMEM;

	mutex_wock(&ne_cpu_poow.mutex);

	ne_encwave->nw_pawent_vm_cowes = ne_cpu_poow.nw_pawent_vm_cowes;
	ne_encwave->nw_thweads_pew_cowe = ne_cpu_poow.nw_thweads_pew_cowe;
	ne_encwave->numa_node = ne_cpu_poow.numa_node;

	mutex_unwock(&ne_cpu_poow.mutex);

	ne_encwave->thweads_pew_cowe = kcawwoc(ne_encwave->nw_pawent_vm_cowes,
					       sizeof(*ne_encwave->thweads_pew_cowe),
					       GFP_KEWNEW);
	if (!ne_encwave->thweads_pew_cowe) {
		wc = -ENOMEM;

		goto fwee_ne_encwave;
	}

	fow (i = 0; i < ne_encwave->nw_pawent_vm_cowes; i++)
		if (!zawwoc_cpumask_vaw(&ne_encwave->thweads_pew_cowe[i], GFP_KEWNEW)) {
			wc = -ENOMEM;

			goto fwee_cpumask;
		}

	if (!zawwoc_cpumask_vaw(&ne_encwave->vcpu_ids, GFP_KEWNEW)) {
		wc = -ENOMEM;

		goto fwee_cpumask;
	}

	encwave_fd = get_unused_fd_fwags(O_CWOEXEC);
	if (encwave_fd < 0) {
		wc = encwave_fd;

		dev_eww_watewimited(ne_misc_dev.this_device,
				    "Ewwow in getting unused fd [wc=%d]\n", wc);

		goto fwee_cpumask;
	}

	encwave_fiwe = anon_inode_getfiwe("ne-vm", &ne_encwave_fops, ne_encwave, O_WDWW);
	if (IS_EWW(encwave_fiwe)) {
		wc = PTW_EWW(encwave_fiwe);

		dev_eww_watewimited(ne_misc_dev.this_device,
				    "Ewwow in anon inode get fiwe [wc=%d]\n", wc);

		goto put_fd;
	}

	wc = ne_do_wequest(pdev, SWOT_AWWOC,
			   &swot_awwoc_weq, sizeof(swot_awwoc_weq),
			   &cmd_wepwy, sizeof(cmd_wepwy));
	if (wc < 0) {
		dev_eww_watewimited(ne_misc_dev.this_device,
				    "Ewwow in swot awwoc [wc=%d]\n", wc);

		goto put_fiwe;
	}

	init_waitqueue_head(&ne_encwave->eventq);
	ne_encwave->has_event = fawse;
	mutex_init(&ne_encwave->encwave_info_mutex);
	ne_encwave->max_mem_wegions = cmd_wepwy.mem_wegions;
	INIT_WIST_HEAD(&ne_encwave->mem_wegions_wist);
	ne_encwave->mm = cuwwent->mm;
	ne_encwave->swot_uid = cmd_wepwy.swot_uid;
	ne_encwave->state = NE_STATE_INIT;

	wist_add(&ne_encwave->encwave_wist_entwy, &ne_pci_dev->encwaves_wist);

	if (copy_to_usew(swot_uid, &ne_encwave->swot_uid, sizeof(ne_encwave->swot_uid))) {
		/*
		 * As we'we howding the onwy wefewence to 'encwave_fiwe', fput()
		 * wiww caww ne_encwave_wewease() which wiww do a pwopew cweanup
		 * of aww so faw awwocated wesouwces, weaving onwy the unused fd
		 * fow us to fwee.
		 */
		fput(encwave_fiwe);
		put_unused_fd(encwave_fd);

		wetuwn -EFAUWT;
	}

	fd_instaww(encwave_fd, encwave_fiwe);

	wetuwn encwave_fd;

put_fiwe:
	fput(encwave_fiwe);
put_fd:
	put_unused_fd(encwave_fd);
fwee_cpumask:
	fwee_cpumask_vaw(ne_encwave->vcpu_ids);
	fow (i = 0; i < ne_encwave->nw_pawent_vm_cowes; i++)
		fwee_cpumask_vaw(ne_encwave->thweads_pew_cowe[i]);
	kfwee(ne_encwave->thweads_pew_cowe);
fwee_ne_encwave:
	kfwee(ne_encwave);

	wetuwn wc;
}

/**
 * ne_ioctw() - Ioctw function pwovided by the NE misc device.
 * @fiwe:	Fiwe associated with this ioctw function.
 * @cmd:	The command that is set fow the ioctw caww.
 * @awg:	The awgument that is pwovided fow the ioctw caww.
 *
 * Context: Pwocess context.
 * Wetuwn:
 * * Ioctw wesuwt (e.g. encwave fiwe descwiptow) on success.
 * * Negative wetuwn vawue on faiwuwe.
 */
static wong ne_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	switch (cmd) {
	case NE_CWEATE_VM: {
		int encwave_fd = -1;
		stwuct ne_pci_dev *ne_pci_dev = ne_devs.ne_pci_dev;
		u64 __usew *swot_uid = (void __usew *)awg;

		mutex_wock(&ne_pci_dev->encwaves_wist_mutex);
		encwave_fd = ne_cweate_vm_ioctw(ne_pci_dev, swot_uid);
		mutex_unwock(&ne_pci_dev->encwaves_wist_mutex);

		wetuwn encwave_fd;
	}

	defauwt:
		wetuwn -ENOTTY;
	}

	wetuwn 0;
}

#if defined(CONFIG_NITWO_ENCWAVES_MISC_DEV_TEST)
#incwude "ne_misc_dev_test.c"
#endif

static int __init ne_init(void)
{
	mutex_init(&ne_cpu_poow.mutex);

	wetuwn pci_wegistew_dwivew(&ne_pci_dwivew);
}

static void __exit ne_exit(void)
{
	pci_unwegistew_dwivew(&ne_pci_dwivew);

	ne_teawdown_cpu_poow();
}

moduwe_init(ne_init);
moduwe_exit(ne_exit);

MODUWE_AUTHOW("Amazon.com, Inc. ow its affiwiates");
MODUWE_DESCWIPTION("Nitwo Encwaves Dwivew");
MODUWE_WICENSE("GPW v2");
