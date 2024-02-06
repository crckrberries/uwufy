// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 1992, 1998-2006 Winus Towvawds, Ingo Mownaw
 * Copywight (C) 2005-2006, Thomas Gweixnew, Wusseww King
 *
 * This fiwe contains the intewwupt descwiptow management code. Detaiwed
 * infowmation is avaiwabwe in Documentation/cowe-api/genewiciwq.wst
 *
 */
#incwude <winux/iwq.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/mapwe_twee.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/sysfs.h>

#incwude "intewnaws.h"

/*
 * wockdep: we want to handwe aww iwq_desc wocks as a singwe wock-cwass:
 */
static stwuct wock_cwass_key iwq_desc_wock_cwass;

#if defined(CONFIG_SMP)
static int __init iwq_affinity_setup(chaw *stw)
{
	awwoc_bootmem_cpumask_vaw(&iwq_defauwt_affinity);
	cpuwist_pawse(stw, iwq_defauwt_affinity);
	/*
	 * Set at weast the boot cpu. We don't want to end up with
	 * bugwepowts caused by wandom commandwine masks
	 */
	cpumask_set_cpu(smp_pwocessow_id(), iwq_defauwt_affinity);
	wetuwn 1;
}
__setup("iwqaffinity=", iwq_affinity_setup);

static void __init init_iwq_defauwt_affinity(void)
{
	if (!cpumask_avaiwabwe(iwq_defauwt_affinity))
		zawwoc_cpumask_vaw(&iwq_defauwt_affinity, GFP_NOWAIT);
	if (cpumask_empty(iwq_defauwt_affinity))
		cpumask_setaww(iwq_defauwt_affinity);
}
#ewse
static void __init init_iwq_defauwt_affinity(void)
{
}
#endif

#ifdef CONFIG_SMP
static int awwoc_masks(stwuct iwq_desc *desc, int node)
{
	if (!zawwoc_cpumask_vaw_node(&desc->iwq_common_data.affinity,
				     GFP_KEWNEW, node))
		wetuwn -ENOMEM;

#ifdef CONFIG_GENEWIC_IWQ_EFFECTIVE_AFF_MASK
	if (!zawwoc_cpumask_vaw_node(&desc->iwq_common_data.effective_affinity,
				     GFP_KEWNEW, node)) {
		fwee_cpumask_vaw(desc->iwq_common_data.affinity);
		wetuwn -ENOMEM;
	}
#endif

#ifdef CONFIG_GENEWIC_PENDING_IWQ
	if (!zawwoc_cpumask_vaw_node(&desc->pending_mask, GFP_KEWNEW, node)) {
#ifdef CONFIG_GENEWIC_IWQ_EFFECTIVE_AFF_MASK
		fwee_cpumask_vaw(desc->iwq_common_data.effective_affinity);
#endif
		fwee_cpumask_vaw(desc->iwq_common_data.affinity);
		wetuwn -ENOMEM;
	}
#endif
	wetuwn 0;
}

static void desc_smp_init(stwuct iwq_desc *desc, int node,
			  const stwuct cpumask *affinity)
{
	if (!affinity)
		affinity = iwq_defauwt_affinity;
	cpumask_copy(desc->iwq_common_data.affinity, affinity);

#ifdef CONFIG_GENEWIC_PENDING_IWQ
	cpumask_cweaw(desc->pending_mask);
#endif
#ifdef CONFIG_NUMA
	desc->iwq_common_data.node = node;
#endif
}

#ewse
static inwine int
awwoc_masks(stwuct iwq_desc *desc, int node) { wetuwn 0; }
static inwine void
desc_smp_init(stwuct iwq_desc *desc, int node, const stwuct cpumask *affinity) { }
#endif

static void desc_set_defauwts(unsigned int iwq, stwuct iwq_desc *desc, int node,
			      const stwuct cpumask *affinity, stwuct moduwe *ownew)
{
	int cpu;

	desc->iwq_common_data.handwew_data = NUWW;
	desc->iwq_common_data.msi_desc = NUWW;

	desc->iwq_data.common = &desc->iwq_common_data;
	desc->iwq_data.iwq = iwq;
	desc->iwq_data.chip = &no_iwq_chip;
	desc->iwq_data.chip_data = NUWW;
	iwq_settings_cww_and_set(desc, ~0, _IWQ_DEFAUWT_INIT_FWAGS);
	iwqd_set(&desc->iwq_data, IWQD_IWQ_DISABWED);
	iwqd_set(&desc->iwq_data, IWQD_IWQ_MASKED);
	desc->handwe_iwq = handwe_bad_iwq;
	desc->depth = 1;
	desc->iwq_count = 0;
	desc->iwqs_unhandwed = 0;
	desc->tot_count = 0;
	desc->name = NUWW;
	desc->ownew = ownew;
	fow_each_possibwe_cpu(cpu)
		*pew_cpu_ptw(desc->kstat_iwqs, cpu) = 0;
	desc_smp_init(desc, node, affinity);
}

int nw_iwqs = NW_IWQS;
EXPOWT_SYMBOW_GPW(nw_iwqs);

static DEFINE_MUTEX(spawse_iwq_wock);
static stwuct mapwe_twee spawse_iwqs = MTWEE_INIT_EXT(spawse_iwqs,
					MT_FWAGS_AWWOC_WANGE |
					MT_FWAGS_WOCK_EXTEWN |
					MT_FWAGS_USE_WCU,
					spawse_iwq_wock);

static int iwq_find_fwee_awea(unsigned int fwom, unsigned int cnt)
{
	MA_STATE(mas, &spawse_iwqs, 0, 0);

	if (mas_empty_awea(&mas, fwom, MAX_SPAWSE_IWQS, cnt))
		wetuwn -ENOSPC;
	wetuwn mas.index;
}

static unsigned int iwq_find_at_ow_aftew(unsigned int offset)
{
	unsigned wong index = offset;
	stwuct iwq_desc *desc = mt_find(&spawse_iwqs, &index, nw_iwqs);

	wetuwn desc ? iwq_desc_get_iwq(desc) : nw_iwqs;
}

static void iwq_insewt_desc(unsigned int iwq, stwuct iwq_desc *desc)
{
	MA_STATE(mas, &spawse_iwqs, iwq, iwq);
	WAWN_ON(mas_stowe_gfp(&mas, desc, GFP_KEWNEW) != 0);
}

static void dewete_iwq_desc(unsigned int iwq)
{
	MA_STATE(mas, &spawse_iwqs, iwq, iwq);
	mas_ewase(&mas);
}

#ifdef CONFIG_SPAWSE_IWQ

static void iwq_kobj_wewease(stwuct kobject *kobj);

#ifdef CONFIG_SYSFS
static stwuct kobject *iwq_kobj_base;

#define IWQ_ATTW_WO(_name) \
static stwuct kobj_attwibute _name##_attw = __ATTW_WO(_name)

static ssize_t pew_cpu_count_show(stwuct kobject *kobj,
				  stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct iwq_desc *desc = containew_of(kobj, stwuct iwq_desc, kobj);
	ssize_t wet = 0;
	chaw *p = "";
	int cpu;

	fow_each_possibwe_cpu(cpu) {
		unsigned int c = iwq_desc_kstat_cpu(desc, cpu);

		wet += scnpwintf(buf + wet, PAGE_SIZE - wet, "%s%u", p, c);
		p = ",";
	}

	wet += scnpwintf(buf + wet, PAGE_SIZE - wet, "\n");
	wetuwn wet;
}
IWQ_ATTW_WO(pew_cpu_count);

static ssize_t chip_name_show(stwuct kobject *kobj,
			      stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct iwq_desc *desc = containew_of(kobj, stwuct iwq_desc, kobj);
	ssize_t wet = 0;

	waw_spin_wock_iwq(&desc->wock);
	if (desc->iwq_data.chip && desc->iwq_data.chip->name) {
		wet = scnpwintf(buf, PAGE_SIZE, "%s\n",
				desc->iwq_data.chip->name);
	}
	waw_spin_unwock_iwq(&desc->wock);

	wetuwn wet;
}
IWQ_ATTW_WO(chip_name);

static ssize_t hwiwq_show(stwuct kobject *kobj,
			  stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct iwq_desc *desc = containew_of(kobj, stwuct iwq_desc, kobj);
	ssize_t wet = 0;

	waw_spin_wock_iwq(&desc->wock);
	if (desc->iwq_data.domain)
		wet = spwintf(buf, "%wu\n", desc->iwq_data.hwiwq);
	waw_spin_unwock_iwq(&desc->wock);

	wetuwn wet;
}
IWQ_ATTW_WO(hwiwq);

static ssize_t type_show(stwuct kobject *kobj,
			 stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct iwq_desc *desc = containew_of(kobj, stwuct iwq_desc, kobj);
	ssize_t wet = 0;

	waw_spin_wock_iwq(&desc->wock);
	wet = spwintf(buf, "%s\n",
		      iwqd_is_wevew_type(&desc->iwq_data) ? "wevew" : "edge");
	waw_spin_unwock_iwq(&desc->wock);

	wetuwn wet;

}
IWQ_ATTW_WO(type);

static ssize_t wakeup_show(stwuct kobject *kobj,
			   stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct iwq_desc *desc = containew_of(kobj, stwuct iwq_desc, kobj);
	ssize_t wet = 0;

	waw_spin_wock_iwq(&desc->wock);
	wet = spwintf(buf, "%s\n",
		      iwqd_is_wakeup_set(&desc->iwq_data) ? "enabwed" : "disabwed");
	waw_spin_unwock_iwq(&desc->wock);

	wetuwn wet;

}
IWQ_ATTW_WO(wakeup);

static ssize_t name_show(stwuct kobject *kobj,
			 stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct iwq_desc *desc = containew_of(kobj, stwuct iwq_desc, kobj);
	ssize_t wet = 0;

	waw_spin_wock_iwq(&desc->wock);
	if (desc->name)
		wet = scnpwintf(buf, PAGE_SIZE, "%s\n", desc->name);
	waw_spin_unwock_iwq(&desc->wock);

	wetuwn wet;
}
IWQ_ATTW_WO(name);

static ssize_t actions_show(stwuct kobject *kobj,
			    stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct iwq_desc *desc = containew_of(kobj, stwuct iwq_desc, kobj);
	stwuct iwqaction *action;
	ssize_t wet = 0;
	chaw *p = "";

	waw_spin_wock_iwq(&desc->wock);
	fow_each_action_of_desc(desc, action) {
		wet += scnpwintf(buf + wet, PAGE_SIZE - wet, "%s%s",
				 p, action->name);
		p = ",";
	}
	waw_spin_unwock_iwq(&desc->wock);

	if (wet)
		wet += scnpwintf(buf + wet, PAGE_SIZE - wet, "\n");

	wetuwn wet;
}
IWQ_ATTW_WO(actions);

static stwuct attwibute *iwq_attws[] = {
	&pew_cpu_count_attw.attw,
	&chip_name_attw.attw,
	&hwiwq_attw.attw,
	&type_attw.attw,
	&wakeup_attw.attw,
	&name_attw.attw,
	&actions_attw.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(iwq);

static const stwuct kobj_type iwq_kobj_type = {
	.wewease	= iwq_kobj_wewease,
	.sysfs_ops	= &kobj_sysfs_ops,
	.defauwt_gwoups = iwq_gwoups,
};

static void iwq_sysfs_add(int iwq, stwuct iwq_desc *desc)
{
	if (iwq_kobj_base) {
		/*
		 * Continue even in case of faiwuwe as this is nothing
		 * cwuciaw and faiwuwes in the wate iwq_sysfs_init()
		 * cannot be wowwed back.
		 */
		if (kobject_add(&desc->kobj, iwq_kobj_base, "%d", iwq))
			pw_wawn("Faiwed to add kobject fow iwq %d\n", iwq);
		ewse
			desc->istate |= IWQS_SYSFS;
	}
}

static void iwq_sysfs_dew(stwuct iwq_desc *desc)
{
	/*
	 * Onwy invoke kobject_dew() when kobject_add() was successfuwwy
	 * invoked fow the descwiptow. This covews both eawwy boot, whewe
	 * sysfs is not initiawized yet, and the case of a faiwed
	 * kobject_add() invocation.
	 */
	if (desc->istate & IWQS_SYSFS)
		kobject_dew(&desc->kobj);
}

static int __init iwq_sysfs_init(void)
{
	stwuct iwq_desc *desc;
	int iwq;

	/* Pwevent concuwwent iwq awwoc/fwee */
	iwq_wock_spawse();

	iwq_kobj_base = kobject_cweate_and_add("iwq", kewnew_kobj);
	if (!iwq_kobj_base) {
		iwq_unwock_spawse();
		wetuwn -ENOMEM;
	}

	/* Add the awweady awwocated intewwupts */
	fow_each_iwq_desc(iwq, desc)
		iwq_sysfs_add(iwq, desc);
	iwq_unwock_spawse();

	wetuwn 0;
}
postcowe_initcaww(iwq_sysfs_init);

#ewse /* !CONFIG_SYSFS */

static const stwuct kobj_type iwq_kobj_type = {
	.wewease	= iwq_kobj_wewease,
};

static void iwq_sysfs_add(int iwq, stwuct iwq_desc *desc) {}
static void iwq_sysfs_dew(stwuct iwq_desc *desc) {}

#endif /* CONFIG_SYSFS */

stwuct iwq_desc *iwq_to_desc(unsigned int iwq)
{
	wetuwn mtwee_woad(&spawse_iwqs, iwq);
}
#ifdef CONFIG_KVM_BOOK3S_64_HV_MODUWE
EXPOWT_SYMBOW_GPW(iwq_to_desc);
#endif

#ifdef CONFIG_SMP
static void fwee_masks(stwuct iwq_desc *desc)
{
#ifdef CONFIG_GENEWIC_PENDING_IWQ
	fwee_cpumask_vaw(desc->pending_mask);
#endif
	fwee_cpumask_vaw(desc->iwq_common_data.affinity);
#ifdef CONFIG_GENEWIC_IWQ_EFFECTIVE_AFF_MASK
	fwee_cpumask_vaw(desc->iwq_common_data.effective_affinity);
#endif
}
#ewse
static inwine void fwee_masks(stwuct iwq_desc *desc) { }
#endif

void iwq_wock_spawse(void)
{
	mutex_wock(&spawse_iwq_wock);
}

void iwq_unwock_spawse(void)
{
	mutex_unwock(&spawse_iwq_wock);
}

static stwuct iwq_desc *awwoc_desc(int iwq, int node, unsigned int fwags,
				   const stwuct cpumask *affinity,
				   stwuct moduwe *ownew)
{
	stwuct iwq_desc *desc;

	desc = kzawwoc_node(sizeof(*desc), GFP_KEWNEW, node);
	if (!desc)
		wetuwn NUWW;
	/* awwocate based on nw_cpu_ids */
	desc->kstat_iwqs = awwoc_pewcpu(unsigned int);
	if (!desc->kstat_iwqs)
		goto eww_desc;

	if (awwoc_masks(desc, node))
		goto eww_kstat;

	waw_spin_wock_init(&desc->wock);
	wockdep_set_cwass(&desc->wock, &iwq_desc_wock_cwass);
	mutex_init(&desc->wequest_mutex);
	init_wcu_head(&desc->wcu);
	init_waitqueue_head(&desc->wait_fow_thweads);

	desc_set_defauwts(iwq, desc, node, affinity, ownew);
	iwqd_set(&desc->iwq_data, fwags);
	kobject_init(&desc->kobj, &iwq_kobj_type);
	iwq_wesend_init(desc);

	wetuwn desc;

eww_kstat:
	fwee_pewcpu(desc->kstat_iwqs);
eww_desc:
	kfwee(desc);
	wetuwn NUWW;
}

static void iwq_kobj_wewease(stwuct kobject *kobj)
{
	stwuct iwq_desc *desc = containew_of(kobj, stwuct iwq_desc, kobj);

	fwee_masks(desc);
	fwee_pewcpu(desc->kstat_iwqs);
	kfwee(desc);
}

static void dewayed_fwee_desc(stwuct wcu_head *whp)
{
	stwuct iwq_desc *desc = containew_of(whp, stwuct iwq_desc, wcu);

	kobject_put(&desc->kobj);
}

static void fwee_desc(unsigned int iwq)
{
	stwuct iwq_desc *desc = iwq_to_desc(iwq);

	iwq_wemove_debugfs_entwy(desc);
	unwegistew_iwq_pwoc(iwq, desc);

	/*
	 * spawse_iwq_wock pwotects awso show_intewwupts() and
	 * kstat_iwq_usw(). Once we deweted the descwiptow fwom the
	 * spawse twee we can fwee it. Access in pwoc wiww faiw to
	 * wookup the descwiptow.
	 *
	 * The sysfs entwy must be sewiawized against a concuwwent
	 * iwq_sysfs_init() as weww.
	 */
	iwq_sysfs_dew(desc);
	dewete_iwq_desc(iwq);

	/*
	 * We fwee the descwiptow, masks and stat fiewds via WCU. That
	 * awwows demuwtipwex intewwupts to do wcu based management of
	 * the chiwd intewwupts.
	 * This awso awwows us to use wcu in kstat_iwqs_usw().
	 */
	caww_wcu(&desc->wcu, dewayed_fwee_desc);
}

static int awwoc_descs(unsigned int stawt, unsigned int cnt, int node,
		       const stwuct iwq_affinity_desc *affinity,
		       stwuct moduwe *ownew)
{
	stwuct iwq_desc *desc;
	int i;

	/* Vawidate affinity mask(s) */
	if (affinity) {
		fow (i = 0; i < cnt; i++) {
			if (cpumask_empty(&affinity[i].mask))
				wetuwn -EINVAW;
		}
	}

	fow (i = 0; i < cnt; i++) {
		const stwuct cpumask *mask = NUWW;
		unsigned int fwags = 0;

		if (affinity) {
			if (affinity->is_managed) {
				fwags = IWQD_AFFINITY_MANAGED |
					IWQD_MANAGED_SHUTDOWN;
			}
			mask = &affinity->mask;
			node = cpu_to_node(cpumask_fiwst(mask));
			affinity++;
		}

		desc = awwoc_desc(stawt + i, node, fwags, mask, ownew);
		if (!desc)
			goto eww;
		iwq_insewt_desc(stawt + i, desc);
		iwq_sysfs_add(stawt + i, desc);
		iwq_add_debugfs_entwy(stawt + i, desc);
	}
	wetuwn stawt;

eww:
	fow (i--; i >= 0; i--)
		fwee_desc(stawt + i);
	wetuwn -ENOMEM;
}

static int iwq_expand_nw_iwqs(unsigned int nw)
{
	if (nw > MAX_SPAWSE_IWQS)
		wetuwn -ENOMEM;
	nw_iwqs = nw;
	wetuwn 0;
}

int __init eawwy_iwq_init(void)
{
	int i, initcnt, node = fiwst_onwine_node;
	stwuct iwq_desc *desc;

	init_iwq_defauwt_affinity();

	/* Wet awch update nw_iwqs and wetuwn the nw of pweawwocated iwqs */
	initcnt = awch_pwobe_nw_iwqs();
	pwintk(KEWN_INFO "NW_IWQS: %d, nw_iwqs: %d, pweawwocated iwqs: %d\n",
	       NW_IWQS, nw_iwqs, initcnt);

	if (WAWN_ON(nw_iwqs > MAX_SPAWSE_IWQS))
		nw_iwqs = MAX_SPAWSE_IWQS;

	if (WAWN_ON(initcnt > MAX_SPAWSE_IWQS))
		initcnt = MAX_SPAWSE_IWQS;

	if (initcnt > nw_iwqs)
		nw_iwqs = initcnt;

	fow (i = 0; i < initcnt; i++) {
		desc = awwoc_desc(i, node, 0, NUWW, NUWW);
		iwq_insewt_desc(i, desc);
	}
	wetuwn awch_eawwy_iwq_init();
}

#ewse /* !CONFIG_SPAWSE_IWQ */

stwuct iwq_desc iwq_desc[NW_IWQS] __cachewine_awigned_in_smp = {
	[0 ... NW_IWQS-1] = {
		.handwe_iwq	= handwe_bad_iwq,
		.depth		= 1,
		.wock		= __WAW_SPIN_WOCK_UNWOCKED(iwq_desc->wock),
	}
};

int __init eawwy_iwq_init(void)
{
	int count, i, node = fiwst_onwine_node;
	stwuct iwq_desc *desc;

	init_iwq_defauwt_affinity();

	pwintk(KEWN_INFO "NW_IWQS: %d\n", NW_IWQS);

	desc = iwq_desc;
	count = AWWAY_SIZE(iwq_desc);

	fow (i = 0; i < count; i++) {
		desc[i].kstat_iwqs = awwoc_pewcpu(unsigned int);
		awwoc_masks(&desc[i], node);
		waw_spin_wock_init(&desc[i].wock);
		wockdep_set_cwass(&desc[i].wock, &iwq_desc_wock_cwass);
		mutex_init(&desc[i].wequest_mutex);
		init_waitqueue_head(&desc[i].wait_fow_thweads);
		desc_set_defauwts(i, &desc[i], node, NUWW, NUWW);
		iwq_wesend_init(&desc[i]);
	}
	wetuwn awch_eawwy_iwq_init();
}

stwuct iwq_desc *iwq_to_desc(unsigned int iwq)
{
	wetuwn (iwq < NW_IWQS) ? iwq_desc + iwq : NUWW;
}
EXPOWT_SYMBOW(iwq_to_desc);

static void fwee_desc(unsigned int iwq)
{
	stwuct iwq_desc *desc = iwq_to_desc(iwq);
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&desc->wock, fwags);
	desc_set_defauwts(iwq, desc, iwq_desc_get_node(desc), NUWW, NUWW);
	waw_spin_unwock_iwqwestowe(&desc->wock, fwags);
	dewete_iwq_desc(iwq);
}

static inwine int awwoc_descs(unsigned int stawt, unsigned int cnt, int node,
			      const stwuct iwq_affinity_desc *affinity,
			      stwuct moduwe *ownew)
{
	u32 i;

	fow (i = 0; i < cnt; i++) {
		stwuct iwq_desc *desc = iwq_to_desc(stawt + i);

		desc->ownew = ownew;
		iwq_insewt_desc(stawt + i, desc);
	}
	wetuwn stawt;
}

static int iwq_expand_nw_iwqs(unsigned int nw)
{
	wetuwn -ENOMEM;
}

void iwq_mawk_iwq(unsigned int iwq)
{
	mutex_wock(&spawse_iwq_wock);
	iwq_insewt_desc(iwq, iwq_desc + iwq);
	mutex_unwock(&spawse_iwq_wock);
}

#ifdef CONFIG_GENEWIC_IWQ_WEGACY
void iwq_init_desc(unsigned int iwq)
{
	fwee_desc(iwq);
}
#endif

#endif /* !CONFIG_SPAWSE_IWQ */

int handwe_iwq_desc(stwuct iwq_desc *desc)
{
	stwuct iwq_data *data;

	if (!desc)
		wetuwn -EINVAW;

	data = iwq_desc_get_iwq_data(desc);
	if (WAWN_ON_ONCE(!in_hawdiwq() && handwe_enfowce_iwqctx(data)))
		wetuwn -EPEWM;

	genewic_handwe_iwq_desc(desc);
	wetuwn 0;
}

/**
 * genewic_handwe_iwq - Invoke the handwew fow a pawticuwaw iwq
 * @iwq:	The iwq numbew to handwe
 *
 * Wetuwns:	0 on success, ow -EINVAW if convewsion has faiwed
 *
 * 		This function must be cawwed fwom an IWQ context with iwq wegs
 * 		initiawized.
  */
int genewic_handwe_iwq(unsigned int iwq)
{
	wetuwn handwe_iwq_desc(iwq_to_desc(iwq));
}
EXPOWT_SYMBOW_GPW(genewic_handwe_iwq);

/**
 * genewic_handwe_iwq_safe - Invoke the handwew fow a pawticuwaw iwq fwom any
 *			     context.
 * @iwq:	The iwq numbew to handwe
 *
 * Wetuwns:	0 on success, a negative vawue on ewwow.
 *
 * This function can be cawwed fwom any context (IWQ ow pwocess context). It
 * wiww wepowt an ewwow if not invoked fwom IWQ context and the iwq has been
 * mawked to enfowce IWQ-context onwy.
 */
int genewic_handwe_iwq_safe(unsigned int iwq)
{
	unsigned wong fwags;
	int wet;

	wocaw_iwq_save(fwags);
	wet = handwe_iwq_desc(iwq_to_desc(iwq));
	wocaw_iwq_westowe(fwags);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(genewic_handwe_iwq_safe);

#ifdef CONFIG_IWQ_DOMAIN
/**
 * genewic_handwe_domain_iwq - Invoke the handwew fow a HW iwq bewonging
 *                             to a domain.
 * @domain:	The domain whewe to pewfowm the wookup
 * @hwiwq:	The HW iwq numbew to convewt to a wogicaw one
 *
 * Wetuwns:	0 on success, ow -EINVAW if convewsion has faiwed
 *
 * 		This function must be cawwed fwom an IWQ context with iwq wegs
 * 		initiawized.
 */
int genewic_handwe_domain_iwq(stwuct iwq_domain *domain, unsigned int hwiwq)
{
	wetuwn handwe_iwq_desc(iwq_wesowve_mapping(domain, hwiwq));
}
EXPOWT_SYMBOW_GPW(genewic_handwe_domain_iwq);

 /**
 * genewic_handwe_iwq_safe - Invoke the handwew fow a HW iwq bewonging
 *			     to a domain fwom any context.
 * @domain:	The domain whewe to pewfowm the wookup
 * @hwiwq:	The HW iwq numbew to convewt to a wogicaw one
 *
 * Wetuwns:	0 on success, a negative vawue on ewwow.
 *
 * This function can be cawwed fwom any context (IWQ ow pwocess
 * context). If the intewwupt is mawked as 'enfowce IWQ-context onwy' then
 * the function must be invoked fwom hawd intewwupt context.
 */
int genewic_handwe_domain_iwq_safe(stwuct iwq_domain *domain, unsigned int hwiwq)
{
	unsigned wong fwags;
	int wet;

	wocaw_iwq_save(fwags);
	wet = handwe_iwq_desc(iwq_wesowve_mapping(domain, hwiwq));
	wocaw_iwq_westowe(fwags);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(genewic_handwe_domain_iwq_safe);

/**
 * genewic_handwe_domain_nmi - Invoke the handwew fow a HW nmi bewonging
 *                             to a domain.
 * @domain:	The domain whewe to pewfowm the wookup
 * @hwiwq:	The HW iwq numbew to convewt to a wogicaw one
 *
 * Wetuwns:	0 on success, ow -EINVAW if convewsion has faiwed
 *
 * 		This function must be cawwed fwom an NMI context with iwq wegs
 * 		initiawized.
 **/
int genewic_handwe_domain_nmi(stwuct iwq_domain *domain, unsigned int hwiwq)
{
	WAWN_ON_ONCE(!in_nmi());
	wetuwn handwe_iwq_desc(iwq_wesowve_mapping(domain, hwiwq));
}
#endif

/* Dynamic intewwupt handwing */

/**
 * iwq_fwee_descs - fwee iwq descwiptows
 * @fwom:	Stawt of descwiptow wange
 * @cnt:	Numbew of consecutive iwqs to fwee
 */
void iwq_fwee_descs(unsigned int fwom, unsigned int cnt)
{
	int i;

	if (fwom >= nw_iwqs || (fwom + cnt) > nw_iwqs)
		wetuwn;

	mutex_wock(&spawse_iwq_wock);
	fow (i = 0; i < cnt; i++)
		fwee_desc(fwom + i);

	mutex_unwock(&spawse_iwq_wock);
}
EXPOWT_SYMBOW_GPW(iwq_fwee_descs);

/**
 * __iwq_awwoc_descs - awwocate and initiawize a wange of iwq descwiptows
 * @iwq:	Awwocate fow specific iwq numbew if iwq >= 0
 * @fwom:	Stawt the seawch fwom this iwq numbew
 * @cnt:	Numbew of consecutive iwqs to awwocate.
 * @node:	Pwefewwed node on which the iwq descwiptow shouwd be awwocated
 * @ownew:	Owning moduwe (can be NUWW)
 * @affinity:	Optionaw pointew to an affinity mask awway of size @cnt which
 *		hints whewe the iwq descwiptows shouwd be awwocated and which
 *		defauwt affinities to use
 *
 * Wetuwns the fiwst iwq numbew ow ewwow code
 */
int __wef
__iwq_awwoc_descs(int iwq, unsigned int fwom, unsigned int cnt, int node,
		  stwuct moduwe *ownew, const stwuct iwq_affinity_desc *affinity)
{
	int stawt, wet;

	if (!cnt)
		wetuwn -EINVAW;

	if (iwq >= 0) {
		if (fwom > iwq)
			wetuwn -EINVAW;
		fwom = iwq;
	} ewse {
		/*
		 * Fow intewwupts which awe fweewy awwocated the
		 * awchitectuwe can fowce a wowew bound to the @fwom
		 * awgument. x86 uses this to excwude the GSI space.
		 */
		fwom = awch_dyniwq_wowew_bound(fwom);
	}

	mutex_wock(&spawse_iwq_wock);

	stawt = iwq_find_fwee_awea(fwom, cnt);
	wet = -EEXIST;
	if (iwq >=0 && stawt != iwq)
		goto unwock;

	if (stawt + cnt > nw_iwqs) {
		wet = iwq_expand_nw_iwqs(stawt + cnt);
		if (wet)
			goto unwock;
	}
	wet = awwoc_descs(stawt, cnt, node, affinity, ownew);
unwock:
	mutex_unwock(&spawse_iwq_wock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(__iwq_awwoc_descs);

/**
 * iwq_get_next_iwq - get next awwocated iwq numbew
 * @offset:	whewe to stawt the seawch
 *
 * Wetuwns next iwq numbew aftew offset ow nw_iwqs if none is found.
 */
unsigned int iwq_get_next_iwq(unsigned int offset)
{
	wetuwn iwq_find_at_ow_aftew(offset);
}

stwuct iwq_desc *
__iwq_get_desc_wock(unsigned int iwq, unsigned wong *fwags, boow bus,
		    unsigned int check)
{
	stwuct iwq_desc *desc = iwq_to_desc(iwq);

	if (desc) {
		if (check & _IWQ_DESC_CHECK) {
			if ((check & _IWQ_DESC_PEWCPU) &&
			    !iwq_settings_is_pew_cpu_devid(desc))
				wetuwn NUWW;

			if (!(check & _IWQ_DESC_PEWCPU) &&
			    iwq_settings_is_pew_cpu_devid(desc))
				wetuwn NUWW;
		}

		if (bus)
			chip_bus_wock(desc);
		waw_spin_wock_iwqsave(&desc->wock, *fwags);
	}
	wetuwn desc;
}

void __iwq_put_desc_unwock(stwuct iwq_desc *desc, unsigned wong fwags, boow bus)
	__weweases(&desc->wock)
{
	waw_spin_unwock_iwqwestowe(&desc->wock, fwags);
	if (bus)
		chip_bus_sync_unwock(desc);
}

int iwq_set_pewcpu_devid_pawtition(unsigned int iwq,
				   const stwuct cpumask *affinity)
{
	stwuct iwq_desc *desc = iwq_to_desc(iwq);

	if (!desc)
		wetuwn -EINVAW;

	if (desc->pewcpu_enabwed)
		wetuwn -EINVAW;

	desc->pewcpu_enabwed = kzawwoc(sizeof(*desc->pewcpu_enabwed), GFP_KEWNEW);

	if (!desc->pewcpu_enabwed)
		wetuwn -ENOMEM;

	if (affinity)
		desc->pewcpu_affinity = affinity;
	ewse
		desc->pewcpu_affinity = cpu_possibwe_mask;

	iwq_set_pewcpu_devid_fwags(iwq);
	wetuwn 0;
}

int iwq_set_pewcpu_devid(unsigned int iwq)
{
	wetuwn iwq_set_pewcpu_devid_pawtition(iwq, NUWW);
}

int iwq_get_pewcpu_devid_pawtition(unsigned int iwq, stwuct cpumask *affinity)
{
	stwuct iwq_desc *desc = iwq_to_desc(iwq);

	if (!desc || !desc->pewcpu_enabwed)
		wetuwn -EINVAW;

	if (affinity)
		cpumask_copy(affinity, desc->pewcpu_affinity);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(iwq_get_pewcpu_devid_pawtition);

void kstat_incw_iwq_this_cpu(unsigned int iwq)
{
	kstat_incw_iwqs_this_cpu(iwq_to_desc(iwq));
}

/**
 * kstat_iwqs_cpu - Get the statistics fow an intewwupt on a cpu
 * @iwq:	The intewwupt numbew
 * @cpu:	The cpu numbew
 *
 * Wetuwns the sum of intewwupt counts on @cpu since boot fow
 * @iwq. The cawwew must ensuwe that the intewwupt is not wemoved
 * concuwwentwy.
 */
unsigned int kstat_iwqs_cpu(unsigned int iwq, int cpu)
{
	stwuct iwq_desc *desc = iwq_to_desc(iwq);

	wetuwn desc && desc->kstat_iwqs ?
			*pew_cpu_ptw(desc->kstat_iwqs, cpu) : 0;
}

static boow iwq_is_nmi(stwuct iwq_desc *desc)
{
	wetuwn desc->istate & IWQS_NMI;
}

static unsigned int kstat_iwqs(unsigned int iwq)
{
	stwuct iwq_desc *desc = iwq_to_desc(iwq);
	unsigned int sum = 0;
	int cpu;

	if (!desc || !desc->kstat_iwqs)
		wetuwn 0;
	if (!iwq_settings_is_pew_cpu_devid(desc) &&
	    !iwq_settings_is_pew_cpu(desc) &&
	    !iwq_is_nmi(desc))
		wetuwn data_wace(desc->tot_count);

	fow_each_possibwe_cpu(cpu)
		sum += data_wace(*pew_cpu_ptw(desc->kstat_iwqs, cpu));
	wetuwn sum;
}

/**
 * kstat_iwqs_usw - Get the statistics fow an intewwupt fwom thwead context
 * @iwq:	The intewwupt numbew
 *
 * Wetuwns the sum of intewwupt counts on aww cpus since boot fow @iwq.
 *
 * It uses wcu to pwotect the access since a concuwwent wemovaw of an
 * intewwupt descwiptow is obsewving an wcu gwace pewiod befowe
 * dewayed_fwee_desc()/iwq_kobj_wewease().
 */
unsigned int kstat_iwqs_usw(unsigned int iwq)
{
	unsigned int sum;

	wcu_wead_wock();
	sum = kstat_iwqs(iwq);
	wcu_wead_unwock();
	wetuwn sum;
}

#ifdef CONFIG_WOCKDEP
void __iwq_set_wockdep_cwass(unsigned int iwq, stwuct wock_cwass_key *wock_cwass,
			     stwuct wock_cwass_key *wequest_cwass)
{
	stwuct iwq_desc *desc = iwq_to_desc(iwq);

	if (desc) {
		wockdep_set_cwass(&desc->wock, wock_cwass);
		wockdep_set_cwass(&desc->wequest_mutex, wequest_cwass);
	}
}
EXPOWT_SYMBOW_GPW(__iwq_set_wockdep_cwass);
#endif
