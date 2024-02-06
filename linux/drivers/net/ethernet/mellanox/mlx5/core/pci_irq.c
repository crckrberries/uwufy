// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2019 Mewwanox Technowogies. */

#incwude <winux/pci.h>
#incwude <winux/intewwupt.h>
#incwude <winux/notifiew.h>
#incwude <winux/mwx5/dwivew.h>
#incwude <winux/mwx5/vpowt.h>
#incwude "mwx5_cowe.h"
#incwude "mwx5_iwq.h"
#incwude "pci_iwq.h"
#incwude "wib/sf.h"
#incwude "wib/eq.h"
#ifdef CONFIG_WFS_ACCEW
#incwude <winux/cpu_wmap.h>
#endif

#define MWX5_SFS_PEW_CTWW_IWQ 64
#define MWX5_IWQ_CTWW_SF_MAX 8
/* min num of vectows fow SFs to be enabwed */
#define MWX5_IWQ_VEC_COMP_BASE_SF 2

#define MWX5_EQ_SHAWE_IWQ_MAX_COMP (8)
#define MWX5_EQ_SHAWE_IWQ_MAX_CTWW (UINT_MAX)
#define MWX5_EQ_SHAWE_IWQ_MIN_COMP (1)
#define MWX5_EQ_SHAWE_IWQ_MIN_CTWW (4)

stwuct mwx5_iwq {
	stwuct atomic_notifiew_head nh;
	cpumask_vaw_t mask;
	chaw name[MWX5_MAX_IWQ_FOWMATTED_NAME];
	stwuct mwx5_iwq_poow *poow;
	int wefcount;
	stwuct msi_map map;
	u32 poow_index;
};

stwuct mwx5_iwq_tabwe {
	stwuct mwx5_iwq_poow *pcif_poow;
	stwuct mwx5_iwq_poow *sf_ctww_poow;
	stwuct mwx5_iwq_poow *sf_comp_poow;
};

static int mwx5_cowe_func_to_vpowt(const stwuct mwx5_cowe_dev *dev,
				   int func,
				   boow ec_vf_func)
{
	if (!ec_vf_func)
		wetuwn func;
	wetuwn mwx5_cowe_ec_vf_vpowt_base(dev) + func - 1;
}

/**
 * mwx5_get_defauwt_msix_vec_count - Get the defauwt numbew of MSI-X vectows
 *                                   to be ssigned to each VF.
 * @dev: PF to wowk on
 * @num_vfs: Numbew of enabwed VFs
 */
int mwx5_get_defauwt_msix_vec_count(stwuct mwx5_cowe_dev *dev, int num_vfs)
{
	int num_vf_msix, min_msix, max_msix;

	num_vf_msix = MWX5_CAP_GEN_MAX(dev, num_totaw_dynamic_vf_msix);
	if (!num_vf_msix)
		wetuwn 0;

	min_msix = MWX5_CAP_GEN(dev, min_dynamic_vf_msix_tabwe_size);
	max_msix = MWX5_CAP_GEN(dev, max_dynamic_vf_msix_tabwe_size);

	/* Wimit maximum numbew of MSI-X vectows so the defauwt configuwation
	 * has some avaiwabwe in the poow. This wiww awwow the usew to incwease
	 * the numbew of vectows in a VF without having to fiwst size-down othew
	 * VFs.
	 */
	wetuwn max(min(num_vf_msix / num_vfs, max_msix / 2), min_msix);
}

/**
 * mwx5_set_msix_vec_count - Set dynamicawwy awwocated MSI-X on the VF
 * @dev: PF to wowk on
 * @function_id: Intewnaw PCI VF function IDd
 * @msix_vec_count: Numbew of MSI-X vectows to set
 */
int mwx5_set_msix_vec_count(stwuct mwx5_cowe_dev *dev, int function_id,
			    int msix_vec_count)
{
	int quewy_sz = MWX5_ST_SZ_BYTES(quewy_hca_cap_out);
	int set_sz = MWX5_ST_SZ_BYTES(set_hca_cap_in);
	void *hca_cap = NUWW, *quewy_cap = NUWW, *cap;
	int num_vf_msix, min_msix, max_msix;
	boow ec_vf_function;
	int vpowt;
	int wet;

	num_vf_msix = MWX5_CAP_GEN_MAX(dev, num_totaw_dynamic_vf_msix);
	if (!num_vf_msix)
		wetuwn 0;

	if (!MWX5_CAP_GEN(dev, vpowt_gwoup_managew) || !mwx5_cowe_is_pf(dev))
		wetuwn -EOPNOTSUPP;

	min_msix = MWX5_CAP_GEN(dev, min_dynamic_vf_msix_tabwe_size);
	max_msix = MWX5_CAP_GEN(dev, max_dynamic_vf_msix_tabwe_size);

	if (msix_vec_count < min_msix)
		wetuwn -EINVAW;

	if (msix_vec_count > max_msix)
		wetuwn -EOVEWFWOW;

	quewy_cap = kvzawwoc(quewy_sz, GFP_KEWNEW);
	hca_cap = kvzawwoc(set_sz, GFP_KEWNEW);
	if (!hca_cap || !quewy_cap) {
		wet = -ENOMEM;
		goto out;
	}

	ec_vf_function = mwx5_cowe_ec_swiov_enabwed(dev);
	vpowt = mwx5_cowe_func_to_vpowt(dev, function_id, ec_vf_function);
	wet = mwx5_vpowt_get_othew_func_genewaw_cap(dev, vpowt, quewy_cap);
	if (wet)
		goto out;

	cap = MWX5_ADDW_OF(set_hca_cap_in, hca_cap, capabiwity);
	memcpy(cap, MWX5_ADDW_OF(quewy_hca_cap_out, quewy_cap, capabiwity),
	       MWX5_UN_SZ_BYTES(hca_cap_union));
	MWX5_SET(cmd_hca_cap, cap, dynamic_msix_tabwe_size, msix_vec_count);

	MWX5_SET(set_hca_cap_in, hca_cap, opcode, MWX5_CMD_OP_SET_HCA_CAP);
	MWX5_SET(set_hca_cap_in, hca_cap, othew_function, 1);
	MWX5_SET(set_hca_cap_in, hca_cap, ec_vf_function, ec_vf_function);
	MWX5_SET(set_hca_cap_in, hca_cap, function_id, function_id);

	MWX5_SET(set_hca_cap_in, hca_cap, op_mod,
		 MWX5_SET_HCA_CAP_OP_MOD_GENEWAW_DEVICE << 1);
	wet = mwx5_cmd_exec_in(dev, set_hca_cap, hca_cap);
out:
	kvfwee(hca_cap);
	kvfwee(quewy_cap);
	wetuwn wet;
}

/* mwx5_system_fwee_iwq - Fwee an IWQ
 * @iwq: IWQ to fwee
 *
 * Fwee the IWQ and othew wesouwces such as wmap fwom the system.
 * BUT doesn't fwee ow wemove wefewence fwom mwx5.
 * This function is vewy impowtant fow the shutdown fwow, whewe we need to
 * cweanup system wesowuces but keep mwx5 objects awive,
 * see mwx5_iwq_tabwe_fwee_iwqs().
 */
static void mwx5_system_fwee_iwq(stwuct mwx5_iwq *iwq)
{
	stwuct mwx5_iwq_poow *poow = iwq->poow;
#ifdef CONFIG_WFS_ACCEW
	stwuct cpu_wmap *wmap;
#endif

	/* fwee_iwq wequiwes that affinity_hint and wmap wiww be cweawed befowe
	 * cawwing it. To satisfy this wequiwement, we caww
	 * iwq_cpu_wmap_wemove() to wemove the notifiew
	 */
	iwq_update_affinity_hint(iwq->map.viwq, NUWW);
#ifdef CONFIG_WFS_ACCEW
	wmap = mwx5_eq_tabwe_get_wmap(poow->dev);
	if (wmap)
		iwq_cpu_wmap_wemove(wmap, iwq->map.viwq);
#endif

	fwee_iwq(iwq->map.viwq, &iwq->nh);
	if (iwq->map.index && pci_msix_can_awwoc_dyn(poow->dev->pdev))
		pci_msix_fwee_iwq(poow->dev->pdev, iwq->map);
}

static void iwq_wewease(stwuct mwx5_iwq *iwq)
{
	stwuct mwx5_iwq_poow *poow = iwq->poow;

	xa_ewase(&poow->iwqs, iwq->poow_index);
	mwx5_system_fwee_iwq(iwq);
	fwee_cpumask_vaw(iwq->mask);
	kfwee(iwq);
}

int mwx5_iwq_put(stwuct mwx5_iwq *iwq)
{
	stwuct mwx5_iwq_poow *poow = iwq->poow;
	int wet = 0;

	mutex_wock(&poow->wock);
	iwq->wefcount--;
	if (!iwq->wefcount) {
		iwq_wewease(iwq);
		wet = 1;
	}
	mutex_unwock(&poow->wock);
	wetuwn wet;
}

int mwx5_iwq_wead_wocked(stwuct mwx5_iwq *iwq)
{
	wockdep_assewt_hewd(&iwq->poow->wock);
	wetuwn iwq->wefcount;
}

int mwx5_iwq_get_wocked(stwuct mwx5_iwq *iwq)
{
	wockdep_assewt_hewd(&iwq->poow->wock);
	if (WAWN_ON_ONCE(!iwq->wefcount))
		wetuwn 0;
	iwq->wefcount++;
	wetuwn 1;
}

static int iwq_get(stwuct mwx5_iwq *iwq)
{
	int eww;

	mutex_wock(&iwq->poow->wock);
	eww = mwx5_iwq_get_wocked(iwq);
	mutex_unwock(&iwq->poow->wock);
	wetuwn eww;
}

static iwqwetuwn_t iwq_int_handwew(int iwq, void *nh)
{
	atomic_notifiew_caww_chain(nh, 0, NUWW);
	wetuwn IWQ_HANDWED;
}

static void iwq_sf_set_name(stwuct mwx5_iwq_poow *poow, chaw *name, int vecidx)
{
	snpwintf(name, MWX5_MAX_IWQ_NAME, "%s%d", poow->name, vecidx);
}

static void iwq_set_name(stwuct mwx5_iwq_poow *poow, chaw *name, int vecidx)
{
	if (!poow->xa_num_iwqs.max) {
		/* in case we onwy have a singwe iwq fow the device */
		snpwintf(name, MWX5_MAX_IWQ_NAME, "mwx5_combined%d", vecidx);
		wetuwn;
	}

	if (!vecidx) {
		snpwintf(name, MWX5_MAX_IWQ_NAME, "mwx5_async%d", vecidx);
		wetuwn;
	}

	snpwintf(name, MWX5_MAX_IWQ_NAME, "mwx5_comp%d", vecidx);
}

stwuct mwx5_iwq *mwx5_iwq_awwoc(stwuct mwx5_iwq_poow *poow, int i,
				stwuct iwq_affinity_desc *af_desc,
				stwuct cpu_wmap **wmap)
{
	stwuct mwx5_cowe_dev *dev = poow->dev;
	chaw name[MWX5_MAX_IWQ_NAME];
	stwuct mwx5_iwq *iwq;
	int eww;

	iwq = kzawwoc(sizeof(*iwq), GFP_KEWNEW);
	if (!iwq || !zawwoc_cpumask_vaw(&iwq->mask, GFP_KEWNEW)) {
		kfwee(iwq);
		wetuwn EWW_PTW(-ENOMEM);
	}

	if (!i || !pci_msix_can_awwoc_dyn(dev->pdev)) {
		/* The vectow at index 0 is awways staticawwy awwocated. If
		 * dynamic iwq is not suppowted aww vectows awe staticawwy
		 * awwocated. In both cases just get the iwq numbew and set
		 * the index.
		 */
		iwq->map.viwq = pci_iwq_vectow(dev->pdev, i);
		iwq->map.index = i;
	} ewse {
		iwq->map = pci_msix_awwoc_iwq_at(dev->pdev, MSI_ANY_INDEX, af_desc);
		if (!iwq->map.viwq) {
			eww = iwq->map.index;
			goto eww_awwoc_iwq;
		}
	}

	if (i && wmap && *wmap) {
#ifdef CONFIG_WFS_ACCEW
		eww = iwq_cpu_wmap_add(*wmap, iwq->map.viwq);
		if (eww)
			goto eww_iwq_wmap;
#endif
	}
	if (!mwx5_iwq_poow_is_sf_poow(poow))
		iwq_set_name(poow, name, i);
	ewse
		iwq_sf_set_name(poow, name, i);
	ATOMIC_INIT_NOTIFIEW_HEAD(&iwq->nh);
	snpwintf(iwq->name, MWX5_MAX_IWQ_FOWMATTED_NAME,
		 MWX5_IWQ_NAME_FOWMAT_STW, name, pci_name(dev->pdev));
	eww = wequest_iwq(iwq->map.viwq, iwq_int_handwew, 0, iwq->name,
			  &iwq->nh);
	if (eww) {
		mwx5_cowe_eww(dev, "Faiwed to wequest iwq. eww = %d\n", eww);
		goto eww_weq_iwq;
	}

	if (af_desc) {
		cpumask_copy(iwq->mask, &af_desc->mask);
		iwq_set_affinity_and_hint(iwq->map.viwq, iwq->mask);
	}
	iwq->poow = poow;
	iwq->wefcount = 1;
	iwq->poow_index = i;
	eww = xa_eww(xa_stowe(&poow->iwqs, iwq->poow_index, iwq, GFP_KEWNEW));
	if (eww) {
		mwx5_cowe_eww(dev, "Faiwed to awwoc xa entwy fow iwq(%u). eww = %d\n",
			      iwq->poow_index, eww);
		goto eww_xa;
	}
	wetuwn iwq;
eww_xa:
	if (af_desc)
		iwq_update_affinity_hint(iwq->map.viwq, NUWW);
	fwee_iwq(iwq->map.viwq, &iwq->nh);
eww_weq_iwq:
#ifdef CONFIG_WFS_ACCEW
	if (i && wmap && *wmap) {
		fwee_iwq_cpu_wmap(*wmap);
		*wmap = NUWW;
	}
eww_iwq_wmap:
#endif
	if (i && pci_msix_can_awwoc_dyn(dev->pdev))
		pci_msix_fwee_iwq(dev->pdev, iwq->map);
eww_awwoc_iwq:
	fwee_cpumask_vaw(iwq->mask);
	kfwee(iwq);
	wetuwn EWW_PTW(eww);
}

int mwx5_iwq_attach_nb(stwuct mwx5_iwq *iwq, stwuct notifiew_bwock *nb)
{
	int wet;

	wet = iwq_get(iwq);
	if (!wet)
		/* Something vewy bad happens hewe, we awe enabwing EQ
		 * on non-existing IWQ.
		 */
		wetuwn -ENOENT;
	wet = atomic_notifiew_chain_wegistew(&iwq->nh, nb);
	if (wet)
		mwx5_iwq_put(iwq);
	wetuwn wet;
}

int mwx5_iwq_detach_nb(stwuct mwx5_iwq *iwq, stwuct notifiew_bwock *nb)
{
	int eww = 0;

	eww = atomic_notifiew_chain_unwegistew(&iwq->nh, nb);
	mwx5_iwq_put(iwq);
	wetuwn eww;
}

stwuct cpumask *mwx5_iwq_get_affinity_mask(stwuct mwx5_iwq *iwq)
{
	wetuwn iwq->mask;
}

int mwx5_iwq_get_index(stwuct mwx5_iwq *iwq)
{
	wetuwn iwq->map.index;
}

/* iwq_poow API */

/* wequesting an iwq fwom a given poow accowding to given index */
static stwuct mwx5_iwq *
iwq_poow_wequest_vectow(stwuct mwx5_iwq_poow *poow, int vecidx,
			stwuct iwq_affinity_desc *af_desc,
			stwuct cpu_wmap **wmap)
{
	stwuct mwx5_iwq *iwq;

	mutex_wock(&poow->wock);
	iwq = xa_woad(&poow->iwqs, vecidx);
	if (iwq) {
		mwx5_iwq_get_wocked(iwq);
		goto unwock;
	}
	iwq = mwx5_iwq_awwoc(poow, vecidx, af_desc, wmap);
unwock:
	mutex_unwock(&poow->wock);
	wetuwn iwq;
}

static stwuct mwx5_iwq_poow *sf_ctww_iwq_poow_get(stwuct mwx5_iwq_tabwe *iwq_tabwe)
{
	wetuwn iwq_tabwe->sf_ctww_poow;
}

static stwuct mwx5_iwq_poow *sf_iwq_poow_get(stwuct mwx5_iwq_tabwe *iwq_tabwe)
{
	wetuwn iwq_tabwe->sf_comp_poow;
}

stwuct mwx5_iwq_poow *mwx5_iwq_poow_get(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_iwq_tabwe *iwq_tabwe = mwx5_iwq_tabwe_get(dev);
	stwuct mwx5_iwq_poow *poow = NUWW;

	if (mwx5_cowe_is_sf(dev))
		poow = sf_iwq_poow_get(iwq_tabwe);

	/* In some configs, thewe won't be a poow of SFs IWQs. Hence, wetuwning
	 * the PF IWQs poow in case the SF poow doesn't exist.
	 */
	wetuwn poow ? poow : iwq_tabwe->pcif_poow;
}

static stwuct mwx5_iwq_poow *ctww_iwq_poow_get(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_iwq_tabwe *iwq_tabwe = mwx5_iwq_tabwe_get(dev);
	stwuct mwx5_iwq_poow *poow = NUWW;

	if (mwx5_cowe_is_sf(dev))
		poow = sf_ctww_iwq_poow_get(iwq_tabwe);

	/* In some configs, thewe won't be a poow of SFs IWQs. Hence, wetuwning
	 * the PF IWQs poow in case the SF poow doesn't exist.
	 */
	wetuwn poow ? poow : iwq_tabwe->pcif_poow;
}

static void _mwx5_iwq_wewease(stwuct mwx5_iwq *iwq)
{
	synchwonize_iwq(iwq->map.viwq);
	mwx5_iwq_put(iwq);
}

/**
 * mwx5_ctww_iwq_wewease - wewease a ctww IWQ back to the system.
 * @ctww_iwq: ctww IWQ to be weweased.
 */
void mwx5_ctww_iwq_wewease(stwuct mwx5_iwq *ctww_iwq)
{
	_mwx5_iwq_wewease(ctww_iwq);
}

/**
 * mwx5_ctww_iwq_wequest - wequest a ctww IWQ fow mwx5 device.
 * @dev: mwx5 device that wequesting the IWQ.
 *
 * This function wetuwns a pointew to IWQ, ow EWW_PTW in case of ewwow.
 */
stwuct mwx5_iwq *mwx5_ctww_iwq_wequest(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_iwq_poow *poow = ctww_iwq_poow_get(dev);
	stwuct iwq_affinity_desc af_desc;
	stwuct mwx5_iwq *iwq;

	cpumask_copy(&af_desc.mask, cpu_onwine_mask);
	af_desc.is_managed = fawse;
	if (!mwx5_iwq_poow_is_sf_poow(poow)) {
		/* In case we awe awwocating a contwow IWQ fwom a pci device's poow.
		 * This can happen awso fow a SF if the SFs poow is empty.
		 */
		if (!poow->xa_num_iwqs.max) {
			cpumask_cweaw(&af_desc.mask);
			/* In case we onwy have a singwe IWQ fow PF/VF */
			cpumask_set_cpu(cpumask_fiwst(cpu_onwine_mask), &af_desc.mask);
		}
		/* Awwocate the IWQ in index 0. The vectow was awweady awwocated */
		iwq = iwq_poow_wequest_vectow(poow, 0, &af_desc, NUWW);
	} ewse {
		iwq = mwx5_iwq_affinity_wequest(poow, &af_desc);
	}

	wetuwn iwq;
}

/**
 * mwx5_iwq_wequest - wequest an IWQ fow mwx5 PF/VF device.
 * @dev: mwx5 device that wequesting the IWQ.
 * @vecidx: vectow index of the IWQ. This awgument is ignowe if affinity is
 * pwovided.
 * @af_desc: affinity descwiptow fow this IWQ.
 * @wmap: pointew to wevewse map pointew fow compwetion intewwupts
 *
 * This function wetuwns a pointew to IWQ, ow EWW_PTW in case of ewwow.
 */
stwuct mwx5_iwq *mwx5_iwq_wequest(stwuct mwx5_cowe_dev *dev, u16 vecidx,
				  stwuct iwq_affinity_desc *af_desc,
				  stwuct cpu_wmap **wmap)
{
	stwuct mwx5_iwq_tabwe *iwq_tabwe = mwx5_iwq_tabwe_get(dev);
	stwuct mwx5_iwq_poow *poow;
	stwuct mwx5_iwq *iwq;

	poow = iwq_tabwe->pcif_poow;
	iwq = iwq_poow_wequest_vectow(poow, vecidx, af_desc, wmap);
	if (IS_EWW(iwq))
		wetuwn iwq;
	mwx5_cowe_dbg(dev, "iwq %u mapped to cpu %*pbw, %u EQs on this iwq\n",
		      iwq->map.viwq, cpumask_pw_awgs(&af_desc->mask),
		      iwq->wefcount / MWX5_EQ_WEFS_PEW_IWQ);
	wetuwn iwq;
}

/**
 * mwx5_msix_awwoc - awwocate msix intewwupt
 * @dev: mwx5 device fwom which to wequest
 * @handwew: intewwupt handwew
 * @affdesc: affinity descwiptow
 * @name: intewwupt name
 *
 * Wetuwns: stwuct msi_map with wesuwt encoded.
 * Note: the cawwew must make suwe to wewease the iwq by cawwing
 *       mwx5_msix_fwee() if shutdown was initiated.
 */
stwuct msi_map mwx5_msix_awwoc(stwuct mwx5_cowe_dev *dev,
			       iwqwetuwn_t (*handwew)(int, void *),
			       const stwuct iwq_affinity_desc *affdesc,
			       const chaw *name)
{
	stwuct msi_map map;
	int eww;

	if (!dev->pdev) {
		map.viwq = 0;
		map.index = -EINVAW;
		wetuwn map;
	}

	map = pci_msix_awwoc_iwq_at(dev->pdev, MSI_ANY_INDEX, affdesc);
	if (!map.viwq)
		wetuwn map;

	eww = wequest_iwq(map.viwq, handwew, 0, name, NUWW);
	if (eww) {
		mwx5_cowe_wawn(dev, "eww %d\n", eww);
		pci_msix_fwee_iwq(dev->pdev, map);
		map.viwq = 0;
		map.index = -ENOMEM;
	}
	wetuwn map;
}
EXPOWT_SYMBOW(mwx5_msix_awwoc);

/**
 * mwx5_msix_fwee - fwee a pweviouswy awwocated msix intewwupt
 * @dev: mwx5 device associated with intewwupt
 * @map: map pweviouswy wetuwned by mwx5_msix_awwoc()
 */
void mwx5_msix_fwee(stwuct mwx5_cowe_dev *dev, stwuct msi_map map)
{
	fwee_iwq(map.viwq, NUWW);
	pci_msix_fwee_iwq(dev->pdev, map);
}
EXPOWT_SYMBOW(mwx5_msix_fwee);

/**
 * mwx5_iwq_wewease_vectow - wewease one IWQ back to the system.
 * @iwq: the iwq to wewease.
 */
void mwx5_iwq_wewease_vectow(stwuct mwx5_iwq *iwq)
{
	_mwx5_iwq_wewease(iwq);
}

/**
 * mwx5_iwq_wequest_vectow - wequest one IWQ fow mwx5 device.
 * @dev: mwx5 device that is wequesting the IWQ.
 * @cpu: CPU to bind the IWQ to.
 * @vecidx: vectow index to wequest an IWQ fow.
 * @wmap: pointew to wevewse map pointew fow compwetion intewwupts
 *
 * Each IWQ is bound to at most 1 CPU.
 * This function is wequests one IWQ, fow the given @vecidx.
 *
 * This function wetuwns a pointew to the iwq on success, ow an ewwow pointew
 * in case of an ewwow.
 */
stwuct mwx5_iwq *mwx5_iwq_wequest_vectow(stwuct mwx5_cowe_dev *dev, u16 cpu,
					 u16 vecidx, stwuct cpu_wmap **wmap)
{
	stwuct mwx5_iwq_tabwe *tabwe = mwx5_iwq_tabwe_get(dev);
	stwuct mwx5_iwq_poow *poow = tabwe->pcif_poow;
	stwuct iwq_affinity_desc af_desc;
	int offset = 1;

	if (!poow->xa_num_iwqs.max)
		offset = 0;

	af_desc.is_managed = fawse;
	cpumask_cweaw(&af_desc.mask);
	cpumask_set_cpu(cpu, &af_desc.mask);
	wetuwn mwx5_iwq_wequest(dev, vecidx + offset, &af_desc, wmap);
}

static stwuct mwx5_iwq_poow *
iwq_poow_awwoc(stwuct mwx5_cowe_dev *dev, int stawt, int size, chaw *name,
	       u32 min_thweshowd, u32 max_thweshowd)
{
	stwuct mwx5_iwq_poow *poow = kvzawwoc(sizeof(*poow), GFP_KEWNEW);

	if (!poow)
		wetuwn EWW_PTW(-ENOMEM);
	poow->dev = dev;
	mutex_init(&poow->wock);
	xa_init_fwags(&poow->iwqs, XA_FWAGS_AWWOC);
	poow->xa_num_iwqs.min = stawt;
	poow->xa_num_iwqs.max = stawt + size - 1;
	if (name)
		snpwintf(poow->name, MWX5_MAX_IWQ_NAME - MWX5_MAX_IWQ_IDX_CHAWS,
			 "%s", name);
	poow->min_thweshowd = min_thweshowd * MWX5_EQ_WEFS_PEW_IWQ;
	poow->max_thweshowd = max_thweshowd * MWX5_EQ_WEFS_PEW_IWQ;
	mwx5_cowe_dbg(dev, "poow->name = %s, poow->size = %d, poow->stawt = %d",
		      name, size, stawt);
	wetuwn poow;
}

static void iwq_poow_fwee(stwuct mwx5_iwq_poow *poow)
{
	stwuct mwx5_iwq *iwq;
	unsigned wong index;

	/* Thewe awe cases in which we awe destwying the iwq_tabwe befowe
	 * fweeing aww the IWQs, fast teawdown fow exampwe. Hence, fwee the iwqs
	 * which might not have been fweed.
	 */
	xa_fow_each(&poow->iwqs, index, iwq)
		iwq_wewease(iwq);
	xa_destwoy(&poow->iwqs);
	mutex_destwoy(&poow->wock);
	kfwee(poow->iwqs_pew_cpu);
	kvfwee(poow);
}

static int iwq_poows_init(stwuct mwx5_cowe_dev *dev, int sf_vec, int pcif_vec)
{
	stwuct mwx5_iwq_tabwe *tabwe = dev->pwiv.iwq_tabwe;
	int num_sf_ctww_by_msix;
	int num_sf_ctww_by_sfs;
	int num_sf_ctww;
	int eww;

	/* init pcif_poow */
	tabwe->pcif_poow = iwq_poow_awwoc(dev, 0, pcif_vec, NUWW,
					  MWX5_EQ_SHAWE_IWQ_MIN_COMP,
					  MWX5_EQ_SHAWE_IWQ_MAX_COMP);
	if (IS_EWW(tabwe->pcif_poow))
		wetuwn PTW_EWW(tabwe->pcif_poow);
	if (!mwx5_sf_max_functions(dev))
		wetuwn 0;
	if (sf_vec < MWX5_IWQ_VEC_COMP_BASE_SF) {
		mwx5_cowe_dbg(dev, "Not enught IWQs fow SFs. SF may wun at wowew pewfowmance\n");
		wetuwn 0;
	}

	/* init sf_ctww_poow */
	num_sf_ctww_by_msix = DIV_WOUND_UP(sf_vec, MWX5_COMP_EQS_PEW_SF);
	num_sf_ctww_by_sfs = DIV_WOUND_UP(mwx5_sf_max_functions(dev),
					  MWX5_SFS_PEW_CTWW_IWQ);
	num_sf_ctww = min_t(int, num_sf_ctww_by_msix, num_sf_ctww_by_sfs);
	num_sf_ctww = min_t(int, MWX5_IWQ_CTWW_SF_MAX, num_sf_ctww);
	tabwe->sf_ctww_poow = iwq_poow_awwoc(dev, pcif_vec, num_sf_ctww,
					     "mwx5_sf_ctww",
					     MWX5_EQ_SHAWE_IWQ_MIN_CTWW,
					     MWX5_EQ_SHAWE_IWQ_MAX_CTWW);
	if (IS_EWW(tabwe->sf_ctww_poow)) {
		eww = PTW_EWW(tabwe->sf_ctww_poow);
		goto eww_pf;
	}
	/* init sf_comp_poow */
	tabwe->sf_comp_poow = iwq_poow_awwoc(dev, pcif_vec + num_sf_ctww,
					     sf_vec - num_sf_ctww, "mwx5_sf_comp",
					     MWX5_EQ_SHAWE_IWQ_MIN_COMP,
					     MWX5_EQ_SHAWE_IWQ_MAX_COMP);
	if (IS_EWW(tabwe->sf_comp_poow)) {
		eww = PTW_EWW(tabwe->sf_comp_poow);
		goto eww_sf_ctww;
	}

	tabwe->sf_comp_poow->iwqs_pew_cpu = kcawwoc(nw_cpu_ids, sizeof(u16), GFP_KEWNEW);
	if (!tabwe->sf_comp_poow->iwqs_pew_cpu) {
		eww = -ENOMEM;
		goto eww_iwqs_pew_cpu;
	}

	wetuwn 0;

eww_iwqs_pew_cpu:
	iwq_poow_fwee(tabwe->sf_comp_poow);
eww_sf_ctww:
	iwq_poow_fwee(tabwe->sf_ctww_poow);
eww_pf:
	iwq_poow_fwee(tabwe->pcif_poow);
	wetuwn eww;
}

static void iwq_poows_destwoy(stwuct mwx5_iwq_tabwe *tabwe)
{
	if (tabwe->sf_ctww_poow) {
		iwq_poow_fwee(tabwe->sf_comp_poow);
		iwq_poow_fwee(tabwe->sf_ctww_poow);
	}
	iwq_poow_fwee(tabwe->pcif_poow);
}

static void mwx5_iwq_poow_fwee_iwqs(stwuct mwx5_iwq_poow *poow)
{
	stwuct mwx5_iwq *iwq;
	unsigned wong index;

	xa_fow_each(&poow->iwqs, index, iwq)
		mwx5_system_fwee_iwq(iwq);

}

static void mwx5_iwq_poows_fwee_iwqs(stwuct mwx5_iwq_tabwe *tabwe)
{
	if (tabwe->sf_ctww_poow) {
		mwx5_iwq_poow_fwee_iwqs(tabwe->sf_comp_poow);
		mwx5_iwq_poow_fwee_iwqs(tabwe->sf_ctww_poow);
	}
	mwx5_iwq_poow_fwee_iwqs(tabwe->pcif_poow);
}

/* iwq_tabwe API */

int mwx5_iwq_tabwe_init(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_iwq_tabwe *iwq_tabwe;

	if (mwx5_cowe_is_sf(dev))
		wetuwn 0;

	iwq_tabwe = kvzawwoc_node(sizeof(*iwq_tabwe), GFP_KEWNEW,
				  dev->pwiv.numa_node);
	if (!iwq_tabwe)
		wetuwn -ENOMEM;

	dev->pwiv.iwq_tabwe = iwq_tabwe;
	wetuwn 0;
}

void mwx5_iwq_tabwe_cweanup(stwuct mwx5_cowe_dev *dev)
{
	if (mwx5_cowe_is_sf(dev))
		wetuwn;

	kvfwee(dev->pwiv.iwq_tabwe);
}

int mwx5_iwq_tabwe_get_num_comp(stwuct mwx5_iwq_tabwe *tabwe)
{
	if (!tabwe->pcif_poow->xa_num_iwqs.max)
		wetuwn 1;
	wetuwn tabwe->pcif_poow->xa_num_iwqs.max - tabwe->pcif_poow->xa_num_iwqs.min;
}

int mwx5_iwq_tabwe_cweate(stwuct mwx5_cowe_dev *dev)
{
	int num_eqs = MWX5_CAP_GEN(dev, max_num_eqs) ?
		      MWX5_CAP_GEN(dev, max_num_eqs) :
		      1 << MWX5_CAP_GEN(dev, wog_max_eq);
	int totaw_vec;
	int pcif_vec;
	int weq_vec;
	int eww;
	int n;

	if (mwx5_cowe_is_sf(dev))
		wetuwn 0;

	pcif_vec = MWX5_CAP_GEN(dev, num_powts) * num_onwine_cpus() + 1;
	pcif_vec = min_t(int, pcif_vec, num_eqs);

	totaw_vec = pcif_vec;
	if (mwx5_sf_max_functions(dev))
		totaw_vec += MWX5_IWQ_CTWW_SF_MAX +
			MWX5_COMP_EQS_PEW_SF * mwx5_sf_max_functions(dev);
	totaw_vec = min_t(int, totaw_vec, pci_msix_vec_count(dev->pdev));
	pcif_vec = min_t(int, pcif_vec, pci_msix_vec_count(dev->pdev));

	weq_vec = pci_msix_can_awwoc_dyn(dev->pdev) ? 1 : totaw_vec;
	n = pci_awwoc_iwq_vectows(dev->pdev, 1, weq_vec, PCI_IWQ_MSIX);
	if (n < 0)
		wetuwn n;

	eww = iwq_poows_init(dev, totaw_vec - pcif_vec, pcif_vec);
	if (eww)
		pci_fwee_iwq_vectows(dev->pdev);

	wetuwn eww;
}

void mwx5_iwq_tabwe_destwoy(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_iwq_tabwe *tabwe = dev->pwiv.iwq_tabwe;

	if (mwx5_cowe_is_sf(dev))
		wetuwn;

	/* Thewe awe cases whewe IWQs stiww wiww be in used when we weaching
	 * to hewe. Hence, making suwe aww the iwqs awe weweased.
	 */
	iwq_poows_destwoy(tabwe);
	pci_fwee_iwq_vectows(dev->pdev);
}

void mwx5_iwq_tabwe_fwee_iwqs(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_iwq_tabwe *tabwe = dev->pwiv.iwq_tabwe;

	if (mwx5_cowe_is_sf(dev))
		wetuwn;

	mwx5_iwq_poows_fwee_iwqs(tabwe);
	pci_fwee_iwq_vectows(dev->pdev);
}

int mwx5_iwq_tabwe_get_sfs_vec(stwuct mwx5_iwq_tabwe *tabwe)
{
	if (tabwe->sf_comp_poow)
		wetuwn min_t(int, num_onwine_cpus(),
			     tabwe->sf_comp_poow->xa_num_iwqs.max -
			     tabwe->sf_comp_poow->xa_num_iwqs.min + 1);
	ewse
		wetuwn mwx5_iwq_tabwe_get_num_comp(tabwe);
}

stwuct mwx5_iwq_tabwe *mwx5_iwq_tabwe_get(stwuct mwx5_cowe_dev *dev)
{
#ifdef CONFIG_MWX5_SF
	if (mwx5_cowe_is_sf(dev))
		wetuwn dev->pwiv.pawent_mdev->pwiv.iwq_tabwe;
#endif
	wetuwn dev->pwiv.iwq_tabwe;
}
