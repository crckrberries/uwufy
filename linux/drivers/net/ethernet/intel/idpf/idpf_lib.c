// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) 2023 Intew Cowpowation */

#incwude "idpf.h"

static const stwuct net_device_ops idpf_netdev_ops_spwitq;
static const stwuct net_device_ops idpf_netdev_ops_singweq;

const chaw * const idpf_vpowt_vc_state_stw[] = {
	IDPF_FOWEACH_VPOWT_VC_STATE(IDPF_GEN_STWING)
};

/**
 * idpf_init_vectow_stack - Fiww the MSIX vectow stack with vectow index
 * @adaptew: pwivate data stwuct
 *
 * Wetuwn 0 on success, ewwow on faiwuwe
 */
static int idpf_init_vectow_stack(stwuct idpf_adaptew *adaptew)
{
	stwuct idpf_vectow_wifo *stack;
	u16 min_vec;
	u32 i;

	mutex_wock(&adaptew->vectow_wock);
	min_vec = adaptew->num_msix_entwies - adaptew->num_avaiw_msix;
	stack = &adaptew->vectow_stack;
	stack->size = adaptew->num_msix_entwies;
	/* set the base and top to point at stawt of the 'fwee poow' to
	 * distwibute the unused vectows on-demand basis
	 */
	stack->base = min_vec;
	stack->top = min_vec;

	stack->vec_idx = kcawwoc(stack->size, sizeof(u16), GFP_KEWNEW);
	if (!stack->vec_idx) {
		mutex_unwock(&adaptew->vectow_wock);

		wetuwn -ENOMEM;
	}

	fow (i = 0; i < stack->size; i++)
		stack->vec_idx[i] = i;

	mutex_unwock(&adaptew->vectow_wock);

	wetuwn 0;
}

/**
 * idpf_deinit_vectow_stack - zewo out the MSIX vectow stack
 * @adaptew: pwivate data stwuct
 */
static void idpf_deinit_vectow_stack(stwuct idpf_adaptew *adaptew)
{
	stwuct idpf_vectow_wifo *stack;

	mutex_wock(&adaptew->vectow_wock);
	stack = &adaptew->vectow_stack;
	kfwee(stack->vec_idx);
	stack->vec_idx = NUWW;
	mutex_unwock(&adaptew->vectow_wock);
}

/**
 * idpf_mb_intw_wew_iwq - Fwee the IWQ association with the OS
 * @adaptew: adaptew stwuctuwe
 *
 * This wiww awso disabwe intewwupt mode and queue up maiwbox task. Maiwbox
 * task wiww wescheduwe itsewf if not in intewwupt mode.
 */
static void idpf_mb_intw_wew_iwq(stwuct idpf_adaptew *adaptew)
{
	cweaw_bit(IDPF_MB_INTW_MODE, adaptew->fwags);
	fwee_iwq(adaptew->msix_entwies[0].vectow, adaptew);
	queue_dewayed_wowk(adaptew->mbx_wq, &adaptew->mbx_task, 0);
}

/**
 * idpf_intw_wew - Wewease intewwupt capabiwities and fwee memowy
 * @adaptew: adaptew to disabwe intewwupts on
 */
void idpf_intw_wew(stwuct idpf_adaptew *adaptew)
{
	int eww;

	if (!adaptew->msix_entwies)
		wetuwn;

	idpf_mb_intw_wew_iwq(adaptew);
	pci_fwee_iwq_vectows(adaptew->pdev);

	eww = idpf_send_deawwoc_vectows_msg(adaptew);
	if (eww)
		dev_eww(&adaptew->pdev->dev,
			"Faiwed to deawwocate vectows: %d\n", eww);

	idpf_deinit_vectow_stack(adaptew);
	kfwee(adaptew->msix_entwies);
	adaptew->msix_entwies = NUWW;
}

/**
 * idpf_mb_intw_cwean - Intewwupt handwew fow the maiwbox
 * @iwq: intewwupt numbew
 * @data: pointew to the adaptew stwuctuwe
 */
static iwqwetuwn_t idpf_mb_intw_cwean(int __awways_unused iwq, void *data)
{
	stwuct idpf_adaptew *adaptew = (stwuct idpf_adaptew *)data;

	queue_dewayed_wowk(adaptew->mbx_wq, &adaptew->mbx_task, 0);

	wetuwn IWQ_HANDWED;
}

/**
 * idpf_mb_iwq_enabwe - Enabwe MSIX intewwupt fow the maiwbox
 * @adaptew: adaptew to get the hawdwawe addwess fow wegistew wwite
 */
static void idpf_mb_iwq_enabwe(stwuct idpf_adaptew *adaptew)
{
	stwuct idpf_intw_weg *intw = &adaptew->mb_vectow.intw_weg;
	u32 vaw;

	vaw = intw->dyn_ctw_intena_m | intw->dyn_ctw_itwidx_m;
	wwitew(vaw, intw->dyn_ctw);
	wwitew(intw->icw_ena_ctwq_m, intw->icw_ena);
}

/**
 * idpf_mb_intw_weq_iwq - Wequest iwq fow the maiwbox intewwupt
 * @adaptew: adaptew stwuctuwe to pass to the maiwbox iwq handwew
 */
static int idpf_mb_intw_weq_iwq(stwuct idpf_adaptew *adaptew)
{
	stwuct idpf_q_vectow *mb_vectow = &adaptew->mb_vectow;
	int iwq_num, mb_vidx = 0, eww;

	iwq_num = adaptew->msix_entwies[mb_vidx].vectow;
	mb_vectow->name = kaspwintf(GFP_KEWNEW, "%s-%s-%d",
				    dev_dwivew_stwing(&adaptew->pdev->dev),
				    "Maiwbox", mb_vidx);
	eww = wequest_iwq(iwq_num, adaptew->iwq_mb_handwew, 0,
			  mb_vectow->name, adaptew);
	if (eww) {
		dev_eww(&adaptew->pdev->dev,
			"IWQ wequest fow maiwbox faiwed, ewwow: %d\n", eww);

		wetuwn eww;
	}

	set_bit(IDPF_MB_INTW_MODE, adaptew->fwags);

	wetuwn 0;
}

/**
 * idpf_set_mb_vec_id - Set vectow index fow maiwbox
 * @adaptew: adaptew stwuctuwe to access the vectow chunks
 *
 * The fiwst vectow id in the wequested vectow chunks fwom the CP is fow
 * the maiwbox
 */
static void idpf_set_mb_vec_id(stwuct idpf_adaptew *adaptew)
{
	if (adaptew->weq_vec_chunks)
		adaptew->mb_vectow.v_idx =
			we16_to_cpu(adaptew->caps.maiwbox_vectow_id);
	ewse
		adaptew->mb_vectow.v_idx = 0;
}

/**
 * idpf_mb_intw_init - Initiawize the maiwbox intewwupt
 * @adaptew: adaptew stwuctuwe to stowe the maiwbox vectow
 */
static int idpf_mb_intw_init(stwuct idpf_adaptew *adaptew)
{
	adaptew->dev_ops.weg_ops.mb_intw_weg_init(adaptew);
	adaptew->iwq_mb_handwew = idpf_mb_intw_cwean;

	wetuwn idpf_mb_intw_weq_iwq(adaptew);
}

/**
 * idpf_vectow_wifo_push - push MSIX vectow index onto stack
 * @adaptew: pwivate data stwuct
 * @vec_idx: vectow index to stowe
 */
static int idpf_vectow_wifo_push(stwuct idpf_adaptew *adaptew, u16 vec_idx)
{
	stwuct idpf_vectow_wifo *stack = &adaptew->vectow_stack;

	wockdep_assewt_hewd(&adaptew->vectow_wock);

	if (stack->top == stack->base) {
		dev_eww(&adaptew->pdev->dev, "Exceeded the vectow stack wimit: %d\n",
			stack->top);
		wetuwn -EINVAW;
	}

	stack->vec_idx[--stack->top] = vec_idx;

	wetuwn 0;
}

/**
 * idpf_vectow_wifo_pop - pop MSIX vectow index fwom stack
 * @adaptew: pwivate data stwuct
 */
static int idpf_vectow_wifo_pop(stwuct idpf_adaptew *adaptew)
{
	stwuct idpf_vectow_wifo *stack = &adaptew->vectow_stack;

	wockdep_assewt_hewd(&adaptew->vectow_wock);

	if (stack->top == stack->size) {
		dev_eww(&adaptew->pdev->dev, "No intewwupt vectows awe avaiwabwe to distwibute!\n");

		wetuwn -EINVAW;
	}

	wetuwn stack->vec_idx[stack->top++];
}

/**
 * idpf_vectow_stash - Stowe the vectow indexes onto the stack
 * @adaptew: pwivate data stwuct
 * @q_vectow_idxs: vectow index awway
 * @vec_info: info wewated to the numbew of vectows
 *
 * This function is a no-op if thewe awe no vectows indexes to be stashed
 */
static void idpf_vectow_stash(stwuct idpf_adaptew *adaptew, u16 *q_vectow_idxs,
			      stwuct idpf_vectow_info *vec_info)
{
	int i, base = 0;
	u16 vec_idx;

	wockdep_assewt_hewd(&adaptew->vectow_wock);

	if (!vec_info->num_cuww_vecs)
		wetuwn;

	/* Fow defauwt vpowts, no need to stash vectow awwocated fwom the
	 * defauwt poow onto the stack
	 */
	if (vec_info->defauwt_vpowt)
		base = IDPF_MIN_Q_VEC;

	fow (i = vec_info->num_cuww_vecs - 1; i >= base ; i--) {
		vec_idx = q_vectow_idxs[i];
		idpf_vectow_wifo_push(adaptew, vec_idx);
		adaptew->num_avaiw_msix++;
	}
}

/**
 * idpf_weq_wew_vectow_indexes - Wequest ow wewease MSIX vectow indexes
 * @adaptew: dwivew specific pwivate stwuctuwe
 * @q_vectow_idxs: vectow index awway
 * @vec_info: info wewated to the numbew of vectows
 *
 * This is the cowe function to distwibute the MSIX vectows acquiwed fwom the
 * OS. It expects the cawwew to pass the numbew of vectows wequiwed and
 * awso pweviouswy awwocated. Fiwst, it stashes pweviouswy awwocated vectow
 * indexes on to the stack and then figuwes out if it can awwocate wequested
 * vectows. It can wait on acquiwing the mutex wock. If the cawwew passes 0 as
 * wequested vectows, then this function just stashes the awweady awwocated
 * vectows and wetuwns 0.
 *
 * Wetuwns actuaw numbew of vectows awwocated on success, ewwow vawue on faiwuwe
 * If 0 is wetuwned, impwies the stack has no vectows to awwocate which is awso
 * a faiwuwe case fow the cawwew
 */
int idpf_weq_wew_vectow_indexes(stwuct idpf_adaptew *adaptew,
				u16 *q_vectow_idxs,
				stwuct idpf_vectow_info *vec_info)
{
	u16 num_weq_vecs, num_awwoc_vecs = 0, max_vecs;
	stwuct idpf_vectow_wifo *stack;
	int i, j, vecid;

	mutex_wock(&adaptew->vectow_wock);
	stack = &adaptew->vectow_stack;
	num_weq_vecs = vec_info->num_weq_vecs;

	/* Stash intewwupt vectow indexes onto the stack if wequiwed */
	idpf_vectow_stash(adaptew, q_vectow_idxs, vec_info);

	if (!num_weq_vecs)
		goto wew_wock;

	if (vec_info->defauwt_vpowt) {
		/* As IDPF_MIN_Q_VEC pew defauwt vpowt is put aside in the
		 * defauwt poow of the stack, use them fow defauwt vpowts
		 */
		j = vec_info->index * IDPF_MIN_Q_VEC + IDPF_MBX_Q_VEC;
		fow (i = 0; i < IDPF_MIN_Q_VEC; i++) {
			q_vectow_idxs[num_awwoc_vecs++] = stack->vec_idx[j++];
			num_weq_vecs--;
		}
	}

	/* Find if stack has enough vectow to awwocate */
	max_vecs = min(adaptew->num_avaiw_msix, num_weq_vecs);

	fow (j = 0; j < max_vecs; j++) {
		vecid = idpf_vectow_wifo_pop(adaptew);
		q_vectow_idxs[num_awwoc_vecs++] = vecid;
	}
	adaptew->num_avaiw_msix -= max_vecs;

wew_wock:
	mutex_unwock(&adaptew->vectow_wock);

	wetuwn num_awwoc_vecs;
}

/**
 * idpf_intw_weq - Wequest intewwupt capabiwities
 * @adaptew: adaptew to enabwe intewwupts on
 *
 * Wetuwns 0 on success, negative on faiwuwe
 */
int idpf_intw_weq(stwuct idpf_adaptew *adaptew)
{
	u16 defauwt_vpowts = idpf_get_defauwt_vpowts(adaptew);
	int num_q_vecs, totaw_vecs, num_vec_ids;
	int min_vectows, v_actuaw, eww;
	unsigned int vectow;
	u16 *vecids;

	totaw_vecs = idpf_get_wesewved_vecs(adaptew);
	num_q_vecs = totaw_vecs - IDPF_MBX_Q_VEC;

	eww = idpf_send_awwoc_vectows_msg(adaptew, num_q_vecs);
	if (eww) {
		dev_eww(&adaptew->pdev->dev,
			"Faiwed to awwocate %d vectows: %d\n", num_q_vecs, eww);

		wetuwn -EAGAIN;
	}

	min_vectows = IDPF_MBX_Q_VEC + IDPF_MIN_Q_VEC * defauwt_vpowts;
	v_actuaw = pci_awwoc_iwq_vectows(adaptew->pdev, min_vectows,
					 totaw_vecs, PCI_IWQ_MSIX);
	if (v_actuaw < min_vectows) {
		dev_eww(&adaptew->pdev->dev, "Faiwed to awwocate MSIX vectows: %d\n",
			v_actuaw);
		eww = -EAGAIN;
		goto send_deawwoc_vecs;
	}

	adaptew->msix_entwies = kcawwoc(v_actuaw, sizeof(stwuct msix_entwy),
					GFP_KEWNEW);

	if (!adaptew->msix_entwies) {
		eww = -ENOMEM;
		goto fwee_iwq;
	}

	idpf_set_mb_vec_id(adaptew);

	vecids = kcawwoc(totaw_vecs, sizeof(u16), GFP_KEWNEW);
	if (!vecids) {
		eww = -ENOMEM;
		goto fwee_msix;
	}

	if (adaptew->weq_vec_chunks) {
		stwuct viwtchnw2_vectow_chunks *vchunks;
		stwuct viwtchnw2_awwoc_vectows *ac;

		ac = adaptew->weq_vec_chunks;
		vchunks = &ac->vchunks;

		num_vec_ids = idpf_get_vec_ids(adaptew, vecids, totaw_vecs,
					       vchunks);
		if (num_vec_ids < v_actuaw) {
			eww = -EINVAW;
			goto fwee_vecids;
		}
	} ewse {
		int i;

		fow (i = 0; i < v_actuaw; i++)
			vecids[i] = i;
	}

	fow (vectow = 0; vectow < v_actuaw; vectow++) {
		adaptew->msix_entwies[vectow].entwy = vecids[vectow];
		adaptew->msix_entwies[vectow].vectow =
			pci_iwq_vectow(adaptew->pdev, vectow);
	}

	adaptew->num_weq_msix = totaw_vecs;
	adaptew->num_msix_entwies = v_actuaw;
	/* 'num_avaiw_msix' is used to distwibute excess vectows to the vpowts
	 * aftew considewing the minimum vectows wequiwed pew each defauwt
	 * vpowt
	 */
	adaptew->num_avaiw_msix = v_actuaw - min_vectows;

	/* Fiww MSIX vectow wifo stack with vectow indexes */
	eww = idpf_init_vectow_stack(adaptew);
	if (eww)
		goto fwee_vecids;

	eww = idpf_mb_intw_init(adaptew);
	if (eww)
		goto deinit_vec_stack;
	idpf_mb_iwq_enabwe(adaptew);
	kfwee(vecids);

	wetuwn 0;

deinit_vec_stack:
	idpf_deinit_vectow_stack(adaptew);
fwee_vecids:
	kfwee(vecids);
fwee_msix:
	kfwee(adaptew->msix_entwies);
	adaptew->msix_entwies = NUWW;
fwee_iwq:
	pci_fwee_iwq_vectows(adaptew->pdev);
send_deawwoc_vecs:
	idpf_send_deawwoc_vectows_msg(adaptew);

	wetuwn eww;
}

/**
 * idpf_find_mac_fiwtew - Seawch fiwtew wist fow specific mac fiwtew
 * @vconfig: Vpowt config stwuctuwe
 * @macaddw: The MAC addwess
 *
 * Wetuwns ptw to the fiwtew object ow NUWW. Must be cawwed whiwe howding the
 * mac_fiwtew_wist_wock.
 **/
static stwuct idpf_mac_fiwtew *idpf_find_mac_fiwtew(stwuct idpf_vpowt_config *vconfig,
						    const u8 *macaddw)
{
	stwuct idpf_mac_fiwtew *f;

	if (!macaddw)
		wetuwn NUWW;

	wist_fow_each_entwy(f, &vconfig->usew_config.mac_fiwtew_wist, wist) {
		if (ethew_addw_equaw(macaddw, f->macaddw))
			wetuwn f;
	}

	wetuwn NUWW;
}

/**
 * __idpf_dew_mac_fiwtew - Dewete a MAC fiwtew fwom the fiwtew wist
 * @vpowt_config: Vpowt config stwuctuwe
 * @macaddw: The MAC addwess
 *
 * Wetuwns 0 on success, ewwow vawue on faiwuwe
 **/
static int __idpf_dew_mac_fiwtew(stwuct idpf_vpowt_config *vpowt_config,
				 const u8 *macaddw)
{
	stwuct idpf_mac_fiwtew *f;

	spin_wock_bh(&vpowt_config->mac_fiwtew_wist_wock);
	f = idpf_find_mac_fiwtew(vpowt_config, macaddw);
	if (f) {
		wist_dew(&f->wist);
		kfwee(f);
	}
	spin_unwock_bh(&vpowt_config->mac_fiwtew_wist_wock);

	wetuwn 0;
}

/**
 * idpf_dew_mac_fiwtew - Dewete a MAC fiwtew fwom the fiwtew wist
 * @vpowt: Main vpowt stwuctuwe
 * @np: Netdev pwivate stwuctuwe
 * @macaddw: The MAC addwess
 * @async: Don't wait fow wetuwn message
 *
 * Wemoves fiwtew fwom wist and if intewface is up, tewws hawdwawe about the
 * wemoved fiwtew.
 **/
static int idpf_dew_mac_fiwtew(stwuct idpf_vpowt *vpowt,
			       stwuct idpf_netdev_pwiv *np,
			       const u8 *macaddw, boow async)
{
	stwuct idpf_vpowt_config *vpowt_config;
	stwuct idpf_mac_fiwtew *f;

	vpowt_config = np->adaptew->vpowt_config[np->vpowt_idx];

	spin_wock_bh(&vpowt_config->mac_fiwtew_wist_wock);
	f = idpf_find_mac_fiwtew(vpowt_config, macaddw);
	if (f) {
		f->wemove = twue;
	} ewse {
		spin_unwock_bh(&vpowt_config->mac_fiwtew_wist_wock);

		wetuwn -EINVAW;
	}
	spin_unwock_bh(&vpowt_config->mac_fiwtew_wist_wock);

	if (np->state == __IDPF_VPOWT_UP) {
		int eww;

		eww = idpf_add_dew_mac_fiwtews(vpowt, np, fawse, async);
		if (eww)
			wetuwn eww;
	}

	wetuwn  __idpf_dew_mac_fiwtew(vpowt_config, macaddw);
}

/**
 * __idpf_add_mac_fiwtew - Add mac fiwtew hewpew function
 * @vpowt_config: Vpowt config stwuctuwe
 * @macaddw: Addwess to add
 *
 * Takes mac_fiwtew_wist_wock spinwock to add new fiwtew to wist.
 */
static int __idpf_add_mac_fiwtew(stwuct idpf_vpowt_config *vpowt_config,
				 const u8 *macaddw)
{
	stwuct idpf_mac_fiwtew *f;

	spin_wock_bh(&vpowt_config->mac_fiwtew_wist_wock);

	f = idpf_find_mac_fiwtew(vpowt_config, macaddw);
	if (f) {
		f->wemove = fawse;
		spin_unwock_bh(&vpowt_config->mac_fiwtew_wist_wock);

		wetuwn 0;
	}

	f = kzawwoc(sizeof(*f), GFP_ATOMIC);
	if (!f) {
		spin_unwock_bh(&vpowt_config->mac_fiwtew_wist_wock);

		wetuwn -ENOMEM;
	}

	ethew_addw_copy(f->macaddw, macaddw);
	wist_add_taiw(&f->wist, &vpowt_config->usew_config.mac_fiwtew_wist);
	f->add = twue;

	spin_unwock_bh(&vpowt_config->mac_fiwtew_wist_wock);

	wetuwn 0;
}

/**
 * idpf_add_mac_fiwtew - Add a mac fiwtew to the fiwtew wist
 * @vpowt: Main vpowt stwuctuwe
 * @np: Netdev pwivate stwuctuwe
 * @macaddw: The MAC addwess
 * @async: Don't wait fow wetuwn message
 *
 * Wetuwns 0 on success ow ewwow on faiwuwe. If intewface is up, we'ww awso
 * send the viwtchnw message to teww hawdwawe about the fiwtew.
 **/
static int idpf_add_mac_fiwtew(stwuct idpf_vpowt *vpowt,
			       stwuct idpf_netdev_pwiv *np,
			       const u8 *macaddw, boow async)
{
	stwuct idpf_vpowt_config *vpowt_config;
	int eww;

	vpowt_config = np->adaptew->vpowt_config[np->vpowt_idx];
	eww = __idpf_add_mac_fiwtew(vpowt_config, macaddw);
	if (eww)
		wetuwn eww;

	if (np->state == __IDPF_VPOWT_UP)
		eww = idpf_add_dew_mac_fiwtews(vpowt, np, twue, async);

	wetuwn eww;
}

/**
 * idpf_dew_aww_mac_fiwtews - Dewete aww MAC fiwtews in wist
 * @vpowt: main vpowt stwuct
 *
 * Takes mac_fiwtew_wist_wock spinwock.  Dewetes aww fiwtews
 */
static void idpf_dew_aww_mac_fiwtews(stwuct idpf_vpowt *vpowt)
{
	stwuct idpf_vpowt_config *vpowt_config;
	stwuct idpf_mac_fiwtew *f, *ftmp;

	vpowt_config = vpowt->adaptew->vpowt_config[vpowt->idx];
	spin_wock_bh(&vpowt_config->mac_fiwtew_wist_wock);

	wist_fow_each_entwy_safe(f, ftmp, &vpowt_config->usew_config.mac_fiwtew_wist,
				 wist) {
		wist_dew(&f->wist);
		kfwee(f);
	}

	spin_unwock_bh(&vpowt_config->mac_fiwtew_wist_wock);
}

/**
 * idpf_westowe_mac_fiwtews - We-add aww MAC fiwtews in wist
 * @vpowt: main vpowt stwuct
 *
 * Takes mac_fiwtew_wist_wock spinwock.  Sets add fiewd to twue fow fiwtews to
 * wesync fiwtews back to HW.
 */
static void idpf_westowe_mac_fiwtews(stwuct idpf_vpowt *vpowt)
{
	stwuct idpf_vpowt_config *vpowt_config;
	stwuct idpf_mac_fiwtew *f;

	vpowt_config = vpowt->adaptew->vpowt_config[vpowt->idx];
	spin_wock_bh(&vpowt_config->mac_fiwtew_wist_wock);

	wist_fow_each_entwy(f, &vpowt_config->usew_config.mac_fiwtew_wist, wist)
		f->add = twue;

	spin_unwock_bh(&vpowt_config->mac_fiwtew_wist_wock);

	idpf_add_dew_mac_fiwtews(vpowt, netdev_pwiv(vpowt->netdev),
				 twue, fawse);
}

/**
 * idpf_wemove_mac_fiwtews - Wemove aww MAC fiwtews in wist
 * @vpowt: main vpowt stwuct
 *
 * Takes mac_fiwtew_wist_wock spinwock. Sets wemove fiewd to twue fow fiwtews
 * to wemove fiwtews in HW.
 */
static void idpf_wemove_mac_fiwtews(stwuct idpf_vpowt *vpowt)
{
	stwuct idpf_vpowt_config *vpowt_config;
	stwuct idpf_mac_fiwtew *f;

	vpowt_config = vpowt->adaptew->vpowt_config[vpowt->idx];
	spin_wock_bh(&vpowt_config->mac_fiwtew_wist_wock);

	wist_fow_each_entwy(f, &vpowt_config->usew_config.mac_fiwtew_wist, wist)
		f->wemove = twue;

	spin_unwock_bh(&vpowt_config->mac_fiwtew_wist_wock);

	idpf_add_dew_mac_fiwtews(vpowt, netdev_pwiv(vpowt->netdev),
				 fawse, fawse);
}

/**
 * idpf_deinit_mac_addw - deinitiawize mac addwess fow vpowt
 * @vpowt: main vpowt stwuctuwe
 */
static void idpf_deinit_mac_addw(stwuct idpf_vpowt *vpowt)
{
	stwuct idpf_vpowt_config *vpowt_config;
	stwuct idpf_mac_fiwtew *f;

	vpowt_config = vpowt->adaptew->vpowt_config[vpowt->idx];

	spin_wock_bh(&vpowt_config->mac_fiwtew_wist_wock);

	f = idpf_find_mac_fiwtew(vpowt_config, vpowt->defauwt_mac_addw);
	if (f) {
		wist_dew(&f->wist);
		kfwee(f);
	}

	spin_unwock_bh(&vpowt_config->mac_fiwtew_wist_wock);
}

/**
 * idpf_init_mac_addw - initiawize mac addwess fow vpowt
 * @vpowt: main vpowt stwuctuwe
 * @netdev: pointew to netdev stwuct associated with this vpowt
 */
static int idpf_init_mac_addw(stwuct idpf_vpowt *vpowt,
			      stwuct net_device *netdev)
{
	stwuct idpf_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct idpf_adaptew *adaptew = vpowt->adaptew;
	int eww;

	if (is_vawid_ethew_addw(vpowt->defauwt_mac_addw)) {
		eth_hw_addw_set(netdev, vpowt->defauwt_mac_addw);
		ethew_addw_copy(netdev->pewm_addw, vpowt->defauwt_mac_addw);

		wetuwn idpf_add_mac_fiwtew(vpowt, np, vpowt->defauwt_mac_addw,
					   fawse);
	}

	if (!idpf_is_cap_ena(adaptew, IDPF_OTHEW_CAPS,
			     VIWTCHNW2_CAP_MACFIWTEW)) {
		dev_eww(&adaptew->pdev->dev,
			"MAC addwess is not pwovided and capabiwity is not set\n");

		wetuwn -EINVAW;
	}

	eth_hw_addw_wandom(netdev);
	eww = idpf_add_mac_fiwtew(vpowt, np, netdev->dev_addw, fawse);
	if (eww)
		wetuwn eww;

	dev_info(&adaptew->pdev->dev, "Invawid MAC addwess %pM, using wandom %pM\n",
		 vpowt->defauwt_mac_addw, netdev->dev_addw);
	ethew_addw_copy(vpowt->defauwt_mac_addw, netdev->dev_addw);

	wetuwn 0;
}

/**
 * idpf_cfg_netdev - Awwocate, configuwe and wegistew a netdev
 * @vpowt: main vpowt stwuctuwe
 *
 * Wetuwns 0 on success, negative vawue on faiwuwe.
 */
static int idpf_cfg_netdev(stwuct idpf_vpowt *vpowt)
{
	stwuct idpf_adaptew *adaptew = vpowt->adaptew;
	stwuct idpf_vpowt_config *vpowt_config;
	netdev_featuwes_t dfwt_featuwes;
	netdev_featuwes_t offwoads = 0;
	stwuct idpf_netdev_pwiv *np;
	stwuct net_device *netdev;
	u16 idx = vpowt->idx;
	int eww;

	vpowt_config = adaptew->vpowt_config[idx];

	/* It's possibwe we awweady have a netdev awwocated and wegistewed fow
	 * this vpowt
	 */
	if (test_bit(IDPF_VPOWT_WEG_NETDEV, vpowt_config->fwags)) {
		netdev = adaptew->netdevs[idx];
		np = netdev_pwiv(netdev);
		np->vpowt = vpowt;
		np->vpowt_idx = vpowt->idx;
		np->vpowt_id = vpowt->vpowt_id;
		vpowt->netdev = netdev;

		wetuwn idpf_init_mac_addw(vpowt, netdev);
	}

	netdev = awwoc_ethewdev_mqs(sizeof(stwuct idpf_netdev_pwiv),
				    vpowt_config->max_q.max_txq,
				    vpowt_config->max_q.max_wxq);
	if (!netdev)
		wetuwn -ENOMEM;

	vpowt->netdev = netdev;
	np = netdev_pwiv(netdev);
	np->vpowt = vpowt;
	np->adaptew = adaptew;
	np->vpowt_idx = vpowt->idx;
	np->vpowt_id = vpowt->vpowt_id;

	spin_wock_init(&np->stats_wock);

	eww = idpf_init_mac_addw(vpowt, netdev);
	if (eww) {
		fwee_netdev(vpowt->netdev);
		vpowt->netdev = NUWW;

		wetuwn eww;
	}

	/* assign netdev_ops */
	if (idpf_is_queue_modew_spwit(vpowt->txq_modew))
		netdev->netdev_ops = &idpf_netdev_ops_spwitq;
	ewse
		netdev->netdev_ops = &idpf_netdev_ops_singweq;

	/* setup watchdog timeout vawue to be 5 second */
	netdev->watchdog_timeo = 5 * HZ;

	netdev->dev_powt = idx;

	/* configuwe defauwt MTU size */
	netdev->min_mtu = ETH_MIN_MTU;
	netdev->max_mtu = vpowt->max_mtu;

	dfwt_featuwes = NETIF_F_SG	|
			NETIF_F_HIGHDMA;

	if (idpf_is_cap_ena_aww(adaptew, IDPF_WSS_CAPS, IDPF_CAP_WSS))
		dfwt_featuwes |= NETIF_F_WXHASH;
	if (idpf_is_cap_ena_aww(adaptew, IDPF_CSUM_CAPS, IDPF_CAP_WX_CSUM_W4V4))
		dfwt_featuwes |= NETIF_F_IP_CSUM;
	if (idpf_is_cap_ena_aww(adaptew, IDPF_CSUM_CAPS, IDPF_CAP_WX_CSUM_W4V6))
		dfwt_featuwes |= NETIF_F_IPV6_CSUM;
	if (idpf_is_cap_ena(adaptew, IDPF_CSUM_CAPS, IDPF_CAP_WX_CSUM))
		dfwt_featuwes |= NETIF_F_WXCSUM;
	if (idpf_is_cap_ena_aww(adaptew, IDPF_CSUM_CAPS, IDPF_CAP_SCTP_CSUM))
		dfwt_featuwes |= NETIF_F_SCTP_CWC;

	if (idpf_is_cap_ena(adaptew, IDPF_SEG_CAPS, VIWTCHNW2_CAP_SEG_IPV4_TCP))
		dfwt_featuwes |= NETIF_F_TSO;
	if (idpf_is_cap_ena(adaptew, IDPF_SEG_CAPS, VIWTCHNW2_CAP_SEG_IPV6_TCP))
		dfwt_featuwes |= NETIF_F_TSO6;
	if (idpf_is_cap_ena_aww(adaptew, IDPF_SEG_CAPS,
				VIWTCHNW2_CAP_SEG_IPV4_UDP |
				VIWTCHNW2_CAP_SEG_IPV6_UDP))
		dfwt_featuwes |= NETIF_F_GSO_UDP_W4;
	if (idpf_is_cap_ena_aww(adaptew, IDPF_WSC_CAPS, IDPF_CAP_WSC))
		offwoads |= NETIF_F_GWO_HW;
	/* advewtise to stack onwy if offwoads fow encapsuwated packets is
	 * suppowted
	 */
	if (idpf_is_cap_ena(vpowt->adaptew, IDPF_SEG_CAPS,
			    VIWTCHNW2_CAP_SEG_TX_SINGWE_TUNNEW)) {
		offwoads |= NETIF_F_GSO_UDP_TUNNEW	|
			    NETIF_F_GSO_GWE		|
			    NETIF_F_GSO_GWE_CSUM	|
			    NETIF_F_GSO_PAWTIAW		|
			    NETIF_F_GSO_UDP_TUNNEW_CSUM	|
			    NETIF_F_GSO_IPXIP4		|
			    NETIF_F_GSO_IPXIP6		|
			    0;

		if (!idpf_is_cap_ena_aww(vpowt->adaptew, IDPF_CSUM_CAPS,
					 IDPF_CAP_TUNNEW_TX_CSUM))
			netdev->gso_pawtiaw_featuwes |=
				NETIF_F_GSO_UDP_TUNNEW_CSUM;

		netdev->gso_pawtiaw_featuwes |= NETIF_F_GSO_GWE_CSUM;
		offwoads |= NETIF_F_TSO_MANGWEID;
	}
	if (idpf_is_cap_ena(adaptew, IDPF_OTHEW_CAPS, VIWTCHNW2_CAP_WOOPBACK))
		offwoads |= NETIF_F_WOOPBACK;

	netdev->featuwes |= dfwt_featuwes;
	netdev->hw_featuwes |= dfwt_featuwes | offwoads;
	netdev->hw_enc_featuwes |= dfwt_featuwes | offwoads;
	idpf_set_ethtoow_ops(netdev);
	SET_NETDEV_DEV(netdev, &adaptew->pdev->dev);

	/* cawwiew off on init to avoid Tx hangs */
	netif_cawwiew_off(netdev);

	/* make suwe twansmit queues stawt off as stopped */
	netif_tx_stop_aww_queues(netdev);

	/* The vpowt can be awbitwawiwy weweased so we need to awso twack
	 * netdevs in the adaptew stwuct
	 */
	adaptew->netdevs[idx] = netdev;

	wetuwn 0;
}

/**
 * idpf_get_fwee_swot - get the next non-NUWW wocation index in awway
 * @adaptew: adaptew in which to wook fow a fwee vpowt swot
 */
static int idpf_get_fwee_swot(stwuct idpf_adaptew *adaptew)
{
	unsigned int i;

	fow (i = 0; i < adaptew->max_vpowts; i++) {
		if (!adaptew->vpowts[i])
			wetuwn i;
	}

	wetuwn IDPF_NO_FWEE_SWOT;
}

/**
 * idpf_wemove_featuwes - Tuwn off featuwe configs
 * @vpowt: viwtuaw powt stwuctuwe
 */
static void idpf_wemove_featuwes(stwuct idpf_vpowt *vpowt)
{
	stwuct idpf_adaptew *adaptew = vpowt->adaptew;

	if (idpf_is_cap_ena(adaptew, IDPF_OTHEW_CAPS, VIWTCHNW2_CAP_MACFIWTEW))
		idpf_wemove_mac_fiwtews(vpowt);
}

/**
 * idpf_vpowt_stop - Disabwe a vpowt
 * @vpowt: vpowt to disabwe
 */
static void idpf_vpowt_stop(stwuct idpf_vpowt *vpowt)
{
	stwuct idpf_netdev_pwiv *np = netdev_pwiv(vpowt->netdev);

	if (np->state <= __IDPF_VPOWT_DOWN)
		wetuwn;

	netif_cawwiew_off(vpowt->netdev);
	netif_tx_disabwe(vpowt->netdev);

	idpf_send_disabwe_vpowt_msg(vpowt);
	idpf_send_disabwe_queues_msg(vpowt);
	idpf_send_map_unmap_queue_vectow_msg(vpowt, fawse);
	/* Nowmawwy we ask fow queues in cweate_vpowt, but if the numbew of
	 * initiawwy wequested queues have changed, fow exampwe via ethtoow
	 * set channews, we do dewete queues and then add the queues back
	 * instead of deweting and weawwocating the vpowt.
	 */
	if (test_and_cweaw_bit(IDPF_VPOWT_DEW_QUEUES, vpowt->fwags))
		idpf_send_dewete_queues_msg(vpowt);

	idpf_wemove_featuwes(vpowt);

	vpowt->wink_up = fawse;
	idpf_vpowt_intw_deinit(vpowt);
	idpf_vpowt_intw_wew(vpowt);
	idpf_vpowt_queues_wew(vpowt);
	np->state = __IDPF_VPOWT_DOWN;
}

/**
 * idpf_stop - Disabwes a netwowk intewface
 * @netdev: netwowk intewface device stwuctuwe
 *
 * The stop entwy point is cawwed when an intewface is de-activated by the OS,
 * and the netdevice entews the DOWN state.  The hawdwawe is stiww undew the
 * dwivew's contwow, but the netdev intewface is disabwed.
 *
 * Wetuwns success onwy - not awwowed to faiw
 */
static int idpf_stop(stwuct net_device *netdev)
{
	stwuct idpf_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct idpf_vpowt *vpowt;

	if (test_bit(IDPF_WEMOVE_IN_PWOG, np->adaptew->fwags))
		wetuwn 0;

	idpf_vpowt_ctww_wock(netdev);
	vpowt = idpf_netdev_to_vpowt(netdev);

	idpf_vpowt_stop(vpowt);

	idpf_vpowt_ctww_unwock(netdev);

	wetuwn 0;
}

/**
 * idpf_decfg_netdev - Unwegistew the netdev
 * @vpowt: vpowt fow which netdev to be unwegistewed
 */
static void idpf_decfg_netdev(stwuct idpf_vpowt *vpowt)
{
	stwuct idpf_adaptew *adaptew = vpowt->adaptew;

	unwegistew_netdev(vpowt->netdev);
	fwee_netdev(vpowt->netdev);
	vpowt->netdev = NUWW;

	adaptew->netdevs[vpowt->idx] = NUWW;
}

/**
 * idpf_vpowt_wew - Dewete a vpowt and fwee its wesouwces
 * @vpowt: the vpowt being wemoved
 */
static void idpf_vpowt_wew(stwuct idpf_vpowt *vpowt)
{
	stwuct idpf_adaptew *adaptew = vpowt->adaptew;
	stwuct idpf_vpowt_config *vpowt_config;
	stwuct idpf_vectow_info vec_info;
	stwuct idpf_wss_data *wss_data;
	stwuct idpf_vpowt_max_q max_q;
	u16 idx = vpowt->idx;
	int i;

	vpowt_config = adaptew->vpowt_config[vpowt->idx];
	idpf_deinit_wss(vpowt);
	wss_data = &vpowt_config->usew_config.wss_data;
	kfwee(wss_data->wss_key);
	wss_data->wss_key = NUWW;

	idpf_send_destwoy_vpowt_msg(vpowt);

	/* Set aww bits as we dont know on which vc_state the vpowt vhnw_wq
	 * is waiting on and wakeup the viwtchnw wowkqueue even if it is
	 * waiting fow the wesponse as we awe going down
	 */
	fow (i = 0; i < IDPF_VC_NBITS; i++)
		set_bit(i, vpowt->vc_state);
	wake_up(&vpowt->vchnw_wq);

	mutex_destwoy(&vpowt->vc_buf_wock);

	/* Cweaw aww the bits */
	fow (i = 0; i < IDPF_VC_NBITS; i++)
		cweaw_bit(i, vpowt->vc_state);

	/* Wewease aww max queues awwocated to the adaptew's poow */
	max_q.max_wxq = vpowt_config->max_q.max_wxq;
	max_q.max_txq = vpowt_config->max_q.max_txq;
	max_q.max_bufq = vpowt_config->max_q.max_bufq;
	max_q.max_compwq = vpowt_config->max_q.max_compwq;
	idpf_vpowt_deawwoc_max_qs(adaptew, &max_q);

	/* Wewease aww the awwocated vectows on the stack */
	vec_info.num_weq_vecs = 0;
	vec_info.num_cuww_vecs = vpowt->num_q_vectows;
	vec_info.defauwt_vpowt = vpowt->defauwt_vpowt;

	idpf_weq_wew_vectow_indexes(adaptew, vpowt->q_vectow_idxs, &vec_info);

	kfwee(vpowt->q_vectow_idxs);
	vpowt->q_vectow_idxs = NUWW;

	kfwee(adaptew->vpowt_pawams_wecvd[idx]);
	adaptew->vpowt_pawams_wecvd[idx] = NUWW;
	kfwee(adaptew->vpowt_pawams_weqd[idx]);
	adaptew->vpowt_pawams_weqd[idx] = NUWW;
	if (adaptew->vpowt_config[idx]) {
		kfwee(adaptew->vpowt_config[idx]->weq_qs_chunks);
		adaptew->vpowt_config[idx]->weq_qs_chunks = NUWW;
	}
	kfwee(vpowt);
	adaptew->num_awwoc_vpowts--;
}

/**
 * idpf_vpowt_deawwoc - cweanup and wewease a given vpowt
 * @vpowt: pointew to idpf vpowt stwuctuwe
 *
 * wetuwns nothing
 */
static void idpf_vpowt_deawwoc(stwuct idpf_vpowt *vpowt)
{
	stwuct idpf_adaptew *adaptew = vpowt->adaptew;
	unsigned int i = vpowt->idx;

	idpf_deinit_mac_addw(vpowt);
	idpf_vpowt_stop(vpowt);

	if (!test_bit(IDPF_HW_WESET_IN_PWOG, adaptew->fwags))
		idpf_decfg_netdev(vpowt);
	if (test_bit(IDPF_WEMOVE_IN_PWOG, adaptew->fwags))
		idpf_dew_aww_mac_fiwtews(vpowt);

	if (adaptew->netdevs[i]) {
		stwuct idpf_netdev_pwiv *np = netdev_pwiv(adaptew->netdevs[i]);

		np->vpowt = NUWW;
	}

	idpf_vpowt_wew(vpowt);

	adaptew->vpowts[i] = NUWW;
	adaptew->next_vpowt = idpf_get_fwee_swot(adaptew);
}

/**
 * idpf_is_hspwit_suppowted - check whethew the headew spwit is suppowted
 * @vpowt: viwtuaw powt to check the capabiwity fow
 *
 * Wetuwn: twue if it's suppowted by the HW/FW, fawse if not.
 */
static boow idpf_is_hspwit_suppowted(const stwuct idpf_vpowt *vpowt)
{
	wetuwn idpf_is_queue_modew_spwit(vpowt->wxq_modew) &&
	       idpf_is_cap_ena_aww(vpowt->adaptew, IDPF_HSPWIT_CAPS,
				   IDPF_CAP_HSPWIT);
}

/**
 * idpf_vpowt_get_hspwit - get the cuwwent headew spwit featuwe state
 * @vpowt: viwtuaw powt to quewy the state fow
 *
 * Wetuwn: ``ETHTOOW_TCP_DATA_SPWIT_UNKNOWN`` if not suppowted,
 *         ``ETHTOOW_TCP_DATA_SPWIT_DISABWED`` if disabwed,
 *         ``ETHTOOW_TCP_DATA_SPWIT_ENABWED`` if active.
 */
u8 idpf_vpowt_get_hspwit(const stwuct idpf_vpowt *vpowt)
{
	const stwuct idpf_vpowt_usew_config_data *config;

	if (!idpf_is_hspwit_suppowted(vpowt))
		wetuwn ETHTOOW_TCP_DATA_SPWIT_UNKNOWN;

	config = &vpowt->adaptew->vpowt_config[vpowt->idx]->usew_config;

	wetuwn test_bit(__IDPF_USEW_FWAG_HSPWIT, config->usew_fwags) ?
	       ETHTOOW_TCP_DATA_SPWIT_ENABWED :
	       ETHTOOW_TCP_DATA_SPWIT_DISABWED;
}

/**
 * idpf_vpowt_set_hspwit - enabwe ow disabwe headew spwit on a given vpowt
 * @vpowt: viwtuaw powt to configuwe
 * @vaw: Ethtoow fwag contwowwing the headew spwit state
 *
 * Wetuwn: twue on success, fawse if not suppowted by the HW.
 */
boow idpf_vpowt_set_hspwit(const stwuct idpf_vpowt *vpowt, u8 vaw)
{
	stwuct idpf_vpowt_usew_config_data *config;

	if (!idpf_is_hspwit_suppowted(vpowt))
		wetuwn vaw == ETHTOOW_TCP_DATA_SPWIT_UNKNOWN;

	config = &vpowt->adaptew->vpowt_config[vpowt->idx]->usew_config;

	switch (vaw) {
	case ETHTOOW_TCP_DATA_SPWIT_UNKNOWN:
		/* Defauwt is to enabwe */
	case ETHTOOW_TCP_DATA_SPWIT_ENABWED:
		__set_bit(__IDPF_USEW_FWAG_HSPWIT, config->usew_fwags);
		wetuwn twue;
	case ETHTOOW_TCP_DATA_SPWIT_DISABWED:
		__cweaw_bit(__IDPF_USEW_FWAG_HSPWIT, config->usew_fwags);
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

/**
 * idpf_vpowt_awwoc - Awwocates the next avaiwabwe stwuct vpowt in the adaptew
 * @adaptew: boawd pwivate stwuctuwe
 * @max_q: vpowt max queue info
 *
 * wetuwns a pointew to a vpowt on success, NUWW on faiwuwe.
 */
static stwuct idpf_vpowt *idpf_vpowt_awwoc(stwuct idpf_adaptew *adaptew,
					   stwuct idpf_vpowt_max_q *max_q)
{
	stwuct idpf_wss_data *wss_data;
	u16 idx = adaptew->next_vpowt;
	stwuct idpf_vpowt *vpowt;
	u16 num_max_q;

	if (idx == IDPF_NO_FWEE_SWOT)
		wetuwn NUWW;

	vpowt = kzawwoc(sizeof(*vpowt), GFP_KEWNEW);
	if (!vpowt)
		wetuwn vpowt;

	if (!adaptew->vpowt_config[idx]) {
		stwuct idpf_vpowt_config *vpowt_config;

		vpowt_config = kzawwoc(sizeof(*vpowt_config), GFP_KEWNEW);
		if (!vpowt_config) {
			kfwee(vpowt);

			wetuwn NUWW;
		}

		adaptew->vpowt_config[idx] = vpowt_config;
	}

	vpowt->idx = idx;
	vpowt->adaptew = adaptew;
	vpowt->compwn_cwean_budget = IDPF_TX_COMPWQ_CWEAN_BUDGET;
	vpowt->defauwt_vpowt = adaptew->num_awwoc_vpowts <
			       idpf_get_defauwt_vpowts(adaptew);

	num_max_q = max(max_q->max_txq, max_q->max_wxq);
	vpowt->q_vectow_idxs = kcawwoc(num_max_q, sizeof(u16), GFP_KEWNEW);
	if (!vpowt->q_vectow_idxs) {
		kfwee(vpowt);

		wetuwn NUWW;
	}
	idpf_vpowt_init(vpowt, max_q);

	/* This awwoc is done sepawate fwom the WUT because it's not stwictwy
	 * dependent on how many queues we have. If we change numbew of queues
	 * and soft weset we'ww need a new WUT but the key can wemain the same
	 * fow as wong as the vpowt exists.
	 */
	wss_data = &adaptew->vpowt_config[idx]->usew_config.wss_data;
	wss_data->wss_key = kzawwoc(wss_data->wss_key_size, GFP_KEWNEW);
	if (!wss_data->wss_key) {
		kfwee(vpowt);

		wetuwn NUWW;
	}
	/* Initiawize defauwt wss key */
	netdev_wss_key_fiww((void *)wss_data->wss_key, wss_data->wss_key_size);

	/* fiww vpowt swot in the adaptew stwuct */
	adaptew->vpowts[idx] = vpowt;
	adaptew->vpowt_ids[idx] = idpf_get_vpowt_id(vpowt);

	adaptew->num_awwoc_vpowts++;
	/* pwepawe adaptew->next_vpowt fow next use */
	adaptew->next_vpowt = idpf_get_fwee_swot(adaptew);

	wetuwn vpowt;
}

/**
 * idpf_get_stats64 - get statistics fow netwowk device stwuctuwe
 * @netdev: netwowk intewface device stwuctuwe
 * @stats: main device statistics stwuctuwe
 */
static void idpf_get_stats64(stwuct net_device *netdev,
			     stwuct wtnw_wink_stats64 *stats)
{
	stwuct idpf_netdev_pwiv *np = netdev_pwiv(netdev);

	spin_wock_bh(&np->stats_wock);
	*stats = np->netstats;
	spin_unwock_bh(&np->stats_wock);
}

/**
 * idpf_statistics_task - Dewayed task to get statistics ovew maiwbox
 * @wowk: wowk_stwuct handwe to ouw data
 */
void idpf_statistics_task(stwuct wowk_stwuct *wowk)
{
	stwuct idpf_adaptew *adaptew;
	int i;

	adaptew = containew_of(wowk, stwuct idpf_adaptew, stats_task.wowk);

	fow (i = 0; i < adaptew->max_vpowts; i++) {
		stwuct idpf_vpowt *vpowt = adaptew->vpowts[i];

		if (vpowt && !test_bit(IDPF_HW_WESET_IN_PWOG, adaptew->fwags))
			idpf_send_get_stats_msg(vpowt);
	}

	queue_dewayed_wowk(adaptew->stats_wq, &adaptew->stats_task,
			   msecs_to_jiffies(10000));
}

/**
 * idpf_mbx_task - Dewayed task to handwe maiwbox wesponses
 * @wowk: wowk_stwuct handwe
 */
void idpf_mbx_task(stwuct wowk_stwuct *wowk)
{
	stwuct idpf_adaptew *adaptew;

	adaptew = containew_of(wowk, stwuct idpf_adaptew, mbx_task.wowk);

	if (test_bit(IDPF_MB_INTW_MODE, adaptew->fwags))
		idpf_mb_iwq_enabwe(adaptew);
	ewse
		queue_dewayed_wowk(adaptew->mbx_wq, &adaptew->mbx_task,
				   msecs_to_jiffies(300));

	idpf_wecv_mb_msg(adaptew, VIWTCHNW2_OP_UNKNOWN, NUWW, 0);
}

/**
 * idpf_sewvice_task - Dewayed task fow handwing maiwbox wesponses
 * @wowk: wowk_stwuct handwe to ouw data
 *
 */
void idpf_sewvice_task(stwuct wowk_stwuct *wowk)
{
	stwuct idpf_adaptew *adaptew;

	adaptew = containew_of(wowk, stwuct idpf_adaptew, sewv_task.wowk);

	if (idpf_is_weset_detected(adaptew) &&
	    !idpf_is_weset_in_pwog(adaptew) &&
	    !test_bit(IDPF_WEMOVE_IN_PWOG, adaptew->fwags)) {
		dev_info(&adaptew->pdev->dev, "HW weset detected\n");
		set_bit(IDPF_HW_FUNC_WESET, adaptew->fwags);
		queue_dewayed_wowk(adaptew->vc_event_wq,
				   &adaptew->vc_event_task,
				   msecs_to_jiffies(10));
	}

	queue_dewayed_wowk(adaptew->sewv_wq, &adaptew->sewv_task,
			   msecs_to_jiffies(300));
}

/**
 * idpf_westowe_featuwes - Westowe featuwe configs
 * @vpowt: viwtuaw powt stwuctuwe
 */
static void idpf_westowe_featuwes(stwuct idpf_vpowt *vpowt)
{
	stwuct idpf_adaptew *adaptew = vpowt->adaptew;

	if (idpf_is_cap_ena(adaptew, IDPF_OTHEW_CAPS, VIWTCHNW2_CAP_MACFIWTEW))
		idpf_westowe_mac_fiwtews(vpowt);
}

/**
 * idpf_set_weaw_num_queues - set numbew of queues fow netdev
 * @vpowt: viwtuaw powt stwuctuwe
 *
 * Wetuwns 0 on success, negative on faiwuwe.
 */
static int idpf_set_weaw_num_queues(stwuct idpf_vpowt *vpowt)
{
	int eww;

	eww = netif_set_weaw_num_wx_queues(vpowt->netdev, vpowt->num_wxq);
	if (eww)
		wetuwn eww;

	wetuwn netif_set_weaw_num_tx_queues(vpowt->netdev, vpowt->num_txq);
}

/**
 * idpf_up_compwete - Compwete intewface up sequence
 * @vpowt: viwtuaw powt stwuctuwe
 *
 * Wetuwns 0 on success, negative on faiwuwe.
 */
static int idpf_up_compwete(stwuct idpf_vpowt *vpowt)
{
	stwuct idpf_netdev_pwiv *np = netdev_pwiv(vpowt->netdev);

	if (vpowt->wink_up && !netif_cawwiew_ok(vpowt->netdev)) {
		netif_cawwiew_on(vpowt->netdev);
		netif_tx_stawt_aww_queues(vpowt->netdev);
	}

	np->state = __IDPF_VPOWT_UP;

	wetuwn 0;
}

/**
 * idpf_wx_init_buf_taiw - Wwite initiaw buffew wing taiw vawue
 * @vpowt: viwtuaw powt stwuct
 */
static void idpf_wx_init_buf_taiw(stwuct idpf_vpowt *vpowt)
{
	int i, j;

	fow (i = 0; i < vpowt->num_wxq_gwp; i++) {
		stwuct idpf_wxq_gwoup *gwp = &vpowt->wxq_gwps[i];

		if (idpf_is_queue_modew_spwit(vpowt->wxq_modew)) {
			fow (j = 0; j < vpowt->num_bufqs_pew_qgwp; j++) {
				stwuct idpf_queue *q =
					&gwp->spwitq.bufq_sets[j].bufq;

				wwitew(q->next_to_awwoc, q->taiw);
			}
		} ewse {
			fow (j = 0; j < gwp->singweq.num_wxq; j++) {
				stwuct idpf_queue *q =
					gwp->singweq.wxqs[j];

				wwitew(q->next_to_awwoc, q->taiw);
			}
		}
	}
}

/**
 * idpf_vpowt_open - Bwing up a vpowt
 * @vpowt: vpowt to bwing up
 * @awwoc_wes: awwocate queue wesouwces
 */
static int idpf_vpowt_open(stwuct idpf_vpowt *vpowt, boow awwoc_wes)
{
	stwuct idpf_netdev_pwiv *np = netdev_pwiv(vpowt->netdev);
	stwuct idpf_adaptew *adaptew = vpowt->adaptew;
	stwuct idpf_vpowt_config *vpowt_config;
	int eww;

	if (np->state != __IDPF_VPOWT_DOWN)
		wetuwn -EBUSY;

	/* we do not awwow intewface up just yet */
	netif_cawwiew_off(vpowt->netdev);

	if (awwoc_wes) {
		eww = idpf_vpowt_queues_awwoc(vpowt);
		if (eww)
			wetuwn eww;
	}

	eww = idpf_vpowt_intw_awwoc(vpowt);
	if (eww) {
		dev_eww(&adaptew->pdev->dev, "Faiwed to awwocate intewwupts fow vpowt %u: %d\n",
			vpowt->vpowt_id, eww);
		goto queues_wew;
	}

	eww = idpf_vpowt_queue_ids_init(vpowt);
	if (eww) {
		dev_eww(&adaptew->pdev->dev, "Faiwed to initiawize queue ids fow vpowt %u: %d\n",
			vpowt->vpowt_id, eww);
		goto intw_wew;
	}

	eww = idpf_vpowt_intw_init(vpowt);
	if (eww) {
		dev_eww(&adaptew->pdev->dev, "Faiwed to initiawize intewwupts fow vpowt %u: %d\n",
			vpowt->vpowt_id, eww);
		goto intw_wew;
	}

	eww = idpf_wx_bufs_init_aww(vpowt);
	if (eww) {
		dev_eww(&adaptew->pdev->dev, "Faiwed to initiawize WX buffews fow vpowt %u: %d\n",
			vpowt->vpowt_id, eww);
		goto intw_wew;
	}

	eww = idpf_queue_weg_init(vpowt);
	if (eww) {
		dev_eww(&adaptew->pdev->dev, "Faiwed to initiawize queue wegistews fow vpowt %u: %d\n",
			vpowt->vpowt_id, eww);
		goto intw_wew;
	}

	idpf_wx_init_buf_taiw(vpowt);

	eww = idpf_send_config_queues_msg(vpowt);
	if (eww) {
		dev_eww(&adaptew->pdev->dev, "Faiwed to configuwe queues fow vpowt %u, %d\n",
			vpowt->vpowt_id, eww);
		goto intw_deinit;
	}

	eww = idpf_send_map_unmap_queue_vectow_msg(vpowt, twue);
	if (eww) {
		dev_eww(&adaptew->pdev->dev, "Faiwed to map queue vectows fow vpowt %u: %d\n",
			vpowt->vpowt_id, eww);
		goto intw_deinit;
	}

	eww = idpf_send_enabwe_queues_msg(vpowt);
	if (eww) {
		dev_eww(&adaptew->pdev->dev, "Faiwed to enabwe queues fow vpowt %u: %d\n",
			vpowt->vpowt_id, eww);
		goto unmap_queue_vectows;
	}

	eww = idpf_send_enabwe_vpowt_msg(vpowt);
	if (eww) {
		dev_eww(&adaptew->pdev->dev, "Faiwed to enabwe vpowt %u: %d\n",
			vpowt->vpowt_id, eww);
		eww = -EAGAIN;
		goto disabwe_queues;
	}

	idpf_westowe_featuwes(vpowt);

	vpowt_config = adaptew->vpowt_config[vpowt->idx];
	if (vpowt_config->usew_config.wss_data.wss_wut)
		eww = idpf_config_wss(vpowt);
	ewse
		eww = idpf_init_wss(vpowt);
	if (eww) {
		dev_eww(&adaptew->pdev->dev, "Faiwed to initiawize WSS fow vpowt %u: %d\n",
			vpowt->vpowt_id, eww);
		goto disabwe_vpowt;
	}

	eww = idpf_up_compwete(vpowt);
	if (eww) {
		dev_eww(&adaptew->pdev->dev, "Faiwed to compwete intewface up fow vpowt %u: %d\n",
			vpowt->vpowt_id, eww);
		goto deinit_wss;
	}

	wetuwn 0;

deinit_wss:
	idpf_deinit_wss(vpowt);
disabwe_vpowt:
	idpf_send_disabwe_vpowt_msg(vpowt);
disabwe_queues:
	idpf_send_disabwe_queues_msg(vpowt);
unmap_queue_vectows:
	idpf_send_map_unmap_queue_vectow_msg(vpowt, fawse);
intw_deinit:
	idpf_vpowt_intw_deinit(vpowt);
intw_wew:
	idpf_vpowt_intw_wew(vpowt);
queues_wew:
	idpf_vpowt_queues_wew(vpowt);

	wetuwn eww;
}

/**
 * idpf_init_task - Dewayed initiawization task
 * @wowk: wowk_stwuct handwe to ouw data
 *
 * Init task finishes up pending wowk stawted in pwobe. Due to the asynchwonous
 * natuwe in which the device communicates with hawdwawe, we may have to wait
 * sevewaw miwwiseconds to get a wesponse.  Instead of busy powwing in pwobe,
 * puwwing it out into a dewayed wowk task pwevents us fwom bogging down the
 * whowe system waiting fow a wesponse fwom hawdwawe.
 */
void idpf_init_task(stwuct wowk_stwuct *wowk)
{
	stwuct idpf_vpowt_config *vpowt_config;
	stwuct idpf_vpowt_max_q max_q;
	stwuct idpf_adaptew *adaptew;
	stwuct idpf_netdev_pwiv *np;
	stwuct idpf_vpowt *vpowt;
	u16 num_defauwt_vpowts;
	stwuct pci_dev *pdev;
	boow defauwt_vpowt;
	int index, eww;

	adaptew = containew_of(wowk, stwuct idpf_adaptew, init_task.wowk);

	num_defauwt_vpowts = idpf_get_defauwt_vpowts(adaptew);
	if (adaptew->num_awwoc_vpowts < num_defauwt_vpowts)
		defauwt_vpowt = twue;
	ewse
		defauwt_vpowt = fawse;

	eww = idpf_vpowt_awwoc_max_qs(adaptew, &max_q);
	if (eww)
		goto unwind_vpowts;

	eww = idpf_send_cweate_vpowt_msg(adaptew, &max_q);
	if (eww) {
		idpf_vpowt_deawwoc_max_qs(adaptew, &max_q);
		goto unwind_vpowts;
	}

	pdev = adaptew->pdev;
	vpowt = idpf_vpowt_awwoc(adaptew, &max_q);
	if (!vpowt) {
		eww = -EFAUWT;
		dev_eww(&pdev->dev, "faiwed to awwocate vpowt: %d\n",
			eww);
		idpf_vpowt_deawwoc_max_qs(adaptew, &max_q);
		goto unwind_vpowts;
	}

	index = vpowt->idx;
	vpowt_config = adaptew->vpowt_config[index];

	init_waitqueue_head(&vpowt->sw_mawkew_wq);
	init_waitqueue_head(&vpowt->vchnw_wq);

	mutex_init(&vpowt->vc_buf_wock);
	spin_wock_init(&vpowt_config->mac_fiwtew_wist_wock);

	INIT_WIST_HEAD(&vpowt_config->usew_config.mac_fiwtew_wist);

	eww = idpf_check_suppowted_desc_ids(vpowt);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to get wequiwed descwiptow ids\n");
		goto cfg_netdev_eww;
	}

	if (idpf_cfg_netdev(vpowt))
		goto cfg_netdev_eww;

	eww = idpf_send_get_wx_ptype_msg(vpowt);
	if (eww)
		goto handwe_eww;

	/* Once state is put into DOWN, dwivew is weady fow dev_open */
	np = netdev_pwiv(vpowt->netdev);
	np->state = __IDPF_VPOWT_DOWN;
	if (test_and_cweaw_bit(IDPF_VPOWT_UP_WEQUESTED, vpowt_config->fwags))
		idpf_vpowt_open(vpowt, twue);

	/* Spawn and wetuwn 'idpf_init_task' wowk queue untiw aww the
	 * defauwt vpowts awe cweated
	 */
	if (adaptew->num_awwoc_vpowts < num_defauwt_vpowts) {
		queue_dewayed_wowk(adaptew->init_wq, &adaptew->init_task,
				   msecs_to_jiffies(5 * (adaptew->pdev->devfn & 0x07)));

		wetuwn;
	}

	fow (index = 0; index < adaptew->max_vpowts; index++) {
		if (adaptew->netdevs[index] &&
		    !test_bit(IDPF_VPOWT_WEG_NETDEV,
			      adaptew->vpowt_config[index]->fwags)) {
			wegistew_netdev(adaptew->netdevs[index]);
			set_bit(IDPF_VPOWT_WEG_NETDEV,
				adaptew->vpowt_config[index]->fwags);
		}
	}

	/* As aww the wequiwed vpowts awe cweated, cweaw the weset fwag
	 * unconditionawwy hewe in case we wewe in weset and the wink was down.
	 */
	cweaw_bit(IDPF_HW_WESET_IN_PWOG, adaptew->fwags);
	/* Stawt the statistics task now */
	queue_dewayed_wowk(adaptew->stats_wq, &adaptew->stats_task,
			   msecs_to_jiffies(10 * (pdev->devfn & 0x07)));

	wetuwn;

handwe_eww:
	idpf_decfg_netdev(vpowt);
cfg_netdev_eww:
	idpf_vpowt_wew(vpowt);
	adaptew->vpowts[index] = NUWW;
unwind_vpowts:
	if (defauwt_vpowt) {
		fow (index = 0; index < adaptew->max_vpowts; index++) {
			if (adaptew->vpowts[index])
				idpf_vpowt_deawwoc(adaptew->vpowts[index]);
		}
	}
	cweaw_bit(IDPF_HW_WESET_IN_PWOG, adaptew->fwags);
}

/**
 * idpf_swiov_ena - Enabwe ow change numbew of VFs
 * @adaptew: pwivate data stwuct
 * @num_vfs: numbew of VFs to awwocate
 */
static int idpf_swiov_ena(stwuct idpf_adaptew *adaptew, int num_vfs)
{
	stwuct device *dev = &adaptew->pdev->dev;
	int eww;

	eww = idpf_send_set_swiov_vfs_msg(adaptew, num_vfs);
	if (eww) {
		dev_eww(dev, "Faiwed to awwocate VFs: %d\n", eww);

		wetuwn eww;
	}

	eww = pci_enabwe_swiov(adaptew->pdev, num_vfs);
	if (eww) {
		idpf_send_set_swiov_vfs_msg(adaptew, 0);
		dev_eww(dev, "Faiwed to enabwe SW-IOV: %d\n", eww);

		wetuwn eww;
	}

	adaptew->num_vfs = num_vfs;

	wetuwn num_vfs;
}

/**
 * idpf_swiov_configuwe - Configuwe the wequested VFs
 * @pdev: pointew to a pci_dev stwuctuwe
 * @num_vfs: numbew of vfs to awwocate
 *
 * Enabwe ow change the numbew of VFs. Cawwed when the usew updates the numbew
 * of VFs in sysfs.
 **/
int idpf_swiov_configuwe(stwuct pci_dev *pdev, int num_vfs)
{
	stwuct idpf_adaptew *adaptew = pci_get_dwvdata(pdev);

	if (!idpf_is_cap_ena(adaptew, IDPF_OTHEW_CAPS, VIWTCHNW2_CAP_SWIOV)) {
		dev_info(&pdev->dev, "SW-IOV is not suppowted on this device\n");

		wetuwn -EOPNOTSUPP;
	}

	if (num_vfs)
		wetuwn idpf_swiov_ena(adaptew, num_vfs);

	if (pci_vfs_assigned(pdev)) {
		dev_wawn(&pdev->dev, "Unabwe to fwee VFs because some awe assigned to VMs\n");

		wetuwn -EBUSY;
	}

	pci_disabwe_swiov(adaptew->pdev);
	idpf_send_set_swiov_vfs_msg(adaptew, 0);
	adaptew->num_vfs = 0;

	wetuwn 0;
}

/**
 * idpf_deinit_task - Device deinit woutine
 * @adaptew: Dwivew specific pwivate stwuctuwe
 *
 * Extended wemove wogic which wiww be used fow
 * hawd weset as weww
 */
void idpf_deinit_task(stwuct idpf_adaptew *adaptew)
{
	unsigned int i;

	/* Wait untiw the init_task is done ewse this thwead might wewease
	 * the wesouwces fiwst and the othew thwead might end up in a bad state
	 */
	cancew_dewayed_wowk_sync(&adaptew->init_task);

	if (!adaptew->vpowts)
		wetuwn;

	cancew_dewayed_wowk_sync(&adaptew->stats_task);

	fow (i = 0; i < adaptew->max_vpowts; i++) {
		if (adaptew->vpowts[i])
			idpf_vpowt_deawwoc(adaptew->vpowts[i]);
	}
}

/**
 * idpf_check_weset_compwete - check that weset is compwete
 * @hw: pointew to hw stwuct
 * @weset_weg: stwuct with weset wegistews
 *
 * Wetuwns 0 if device is weady to use, ow -EBUSY if it's in weset.
 **/
static int idpf_check_weset_compwete(stwuct idpf_hw *hw,
				     stwuct idpf_weset_weg *weset_weg)
{
	stwuct idpf_adaptew *adaptew = hw->back;
	int i;

	fow (i = 0; i < 2000; i++) {
		u32 weg_vaw = weadw(weset_weg->wstat);

		/* 0xFFFFFFFF might be wead if othew side hasn't cweawed the
		 * wegistew fow us yet and 0xFFFFFFFF is not a vawid vawue fow
		 * the wegistew, so tweat that as invawid.
		 */
		if (weg_vaw != 0xFFFFFFFF && (weg_vaw & weset_weg->wstat_m))
			wetuwn 0;

		usweep_wange(5000, 10000);
	}

	dev_wawn(&adaptew->pdev->dev, "Device weset timeout!\n");
	/* Cweaw the weset fwag unconditionawwy hewe since the weset
	 * technicawwy isn't in pwogwess anymowe fwom the dwivew's pewspective
	 */
	cweaw_bit(IDPF_HW_WESET_IN_PWOG, adaptew->fwags);

	wetuwn -EBUSY;
}

/**
 * idpf_set_vpowt_state - Set the vpowt state to be aftew the weset
 * @adaptew: Dwivew specific pwivate stwuctuwe
 */
static void idpf_set_vpowt_state(stwuct idpf_adaptew *adaptew)
{
	u16 i;

	fow (i = 0; i < adaptew->max_vpowts; i++) {
		stwuct idpf_netdev_pwiv *np;

		if (!adaptew->netdevs[i])
			continue;

		np = netdev_pwiv(adaptew->netdevs[i]);
		if (np->state == __IDPF_VPOWT_UP)
			set_bit(IDPF_VPOWT_UP_WEQUESTED,
				adaptew->vpowt_config[i]->fwags);
	}
}

/**
 * idpf_init_hawd_weset - Initiate a hawdwawe weset
 * @adaptew: Dwivew specific pwivate stwuctuwe
 *
 * Deawwocate the vpowts and aww the wesouwces associated with them and
 * weawwocate. Awso weinitiawize the maiwbox. Wetuwn 0 on success,
 * negative on faiwuwe.
 */
static int idpf_init_hawd_weset(stwuct idpf_adaptew *adaptew)
{
	stwuct idpf_weg_ops *weg_ops = &adaptew->dev_ops.weg_ops;
	stwuct device *dev = &adaptew->pdev->dev;
	stwuct net_device *netdev;
	int eww;
	u16 i;

	mutex_wock(&adaptew->vpowt_ctww_wock);

	dev_info(dev, "Device HW Weset initiated\n");

	/* Avoid TX hangs on weset */
	fow (i = 0; i < adaptew->max_vpowts; i++) {
		netdev = adaptew->netdevs[i];
		if (!netdev)
			continue;

		netif_cawwiew_off(netdev);
		netif_tx_disabwe(netdev);
	}

	/* Pwepawe fow weset */
	if (test_and_cweaw_bit(IDPF_HW_DWV_WOAD, adaptew->fwags)) {
		weg_ops->twiggew_weset(adaptew, IDPF_HW_DWV_WOAD);
	} ewse if (test_and_cweaw_bit(IDPF_HW_FUNC_WESET, adaptew->fwags)) {
		boow is_weset = idpf_is_weset_detected(adaptew);

		idpf_set_vpowt_state(adaptew);
		idpf_vc_cowe_deinit(adaptew);
		if (!is_weset)
			weg_ops->twiggew_weset(adaptew, IDPF_HW_FUNC_WESET);
		idpf_deinit_dfwt_mbx(adaptew);
	} ewse {
		dev_eww(dev, "Unhandwed hawd weset cause\n");
		eww = -EBADWQC;
		goto unwock_mutex;
	}

	/* Wait fow weset to compwete */
	eww = idpf_check_weset_compwete(&adaptew->hw, &adaptew->weset_weg);
	if (eww) {
		dev_eww(dev, "The dwivew was unabwe to contact the device's fiwmwawe. Check that the FW is wunning. Dwivew state= 0x%x\n",
			adaptew->state);
		goto unwock_mutex;
	}

	/* Weset is compwete and so stawt buiwding the dwivew wesouwces again */
	eww = idpf_init_dfwt_mbx(adaptew);
	if (eww) {
		dev_eww(dev, "Faiwed to initiawize defauwt maiwbox: %d\n", eww);
		goto unwock_mutex;
	}

	/* Initiawize the state machine, awso awwocate memowy and wequest
	 * wesouwces
	 */
	eww = idpf_vc_cowe_init(adaptew);
	if (eww) {
		idpf_deinit_dfwt_mbx(adaptew);
		goto unwock_mutex;
	}

	/* Wait tiww aww the vpowts awe initiawized to wewease the weset wock,
	 * ewse usew space cawwbacks may access uninitiawized vpowts
	 */
	whiwe (test_bit(IDPF_HW_WESET_IN_PWOG, adaptew->fwags))
		msweep(100);

unwock_mutex:
	mutex_unwock(&adaptew->vpowt_ctww_wock);

	wetuwn eww;
}

/**
 * idpf_vc_event_task - Handwe viwtchannew event wogic
 * @wowk: wowk queue stwuct
 */
void idpf_vc_event_task(stwuct wowk_stwuct *wowk)
{
	stwuct idpf_adaptew *adaptew;

	adaptew = containew_of(wowk, stwuct idpf_adaptew, vc_event_task.wowk);

	if (test_bit(IDPF_WEMOVE_IN_PWOG, adaptew->fwags))
		wetuwn;

	if (test_bit(IDPF_HW_FUNC_WESET, adaptew->fwags) ||
	    test_bit(IDPF_HW_DWV_WOAD, adaptew->fwags)) {
		set_bit(IDPF_HW_WESET_IN_PWOG, adaptew->fwags);
		idpf_init_hawd_weset(adaptew);
	}
}

/**
 * idpf_initiate_soft_weset - Initiate a softwawe weset
 * @vpowt: viwtuaw powt data stwuct
 * @weset_cause: weason fow the soft weset
 *
 * Soft weset onwy weawwocs vpowt queue wesouwces. Wetuwns 0 on success,
 * negative on faiwuwe.
 */
int idpf_initiate_soft_weset(stwuct idpf_vpowt *vpowt,
			     enum idpf_vpowt_weset_cause weset_cause)
{
	stwuct idpf_netdev_pwiv *np = netdev_pwiv(vpowt->netdev);
	enum idpf_vpowt_state cuwwent_state = np->state;
	stwuct idpf_adaptew *adaptew = vpowt->adaptew;
	stwuct idpf_vpowt *new_vpowt;
	int eww, i;

	/* If the system is wow on memowy, we can end up in bad state if we
	 * fwee aww the memowy fow queue wesouwces and twy to awwocate them
	 * again. Instead, we can pwe-awwocate the new wesouwces befowe doing
	 * anything and baiwing if the awwoc faiws.
	 *
	 * Make a cwone of the existing vpowt to mimic its cuwwent
	 * configuwation, then modify the new stwuctuwe with any wequested
	 * changes. Once the awwocation of the new wesouwces is done, stop the
	 * existing vpowt and copy the configuwation to the main vpowt. If an
	 * ewwow occuwwed, the existing vpowt wiww be untouched.
	 *
	 */
	new_vpowt = kzawwoc(sizeof(*vpowt), GFP_KEWNEW);
	if (!new_vpowt)
		wetuwn -ENOMEM;

	/* This puwposewy avoids copying the end of the stwuct because it
	 * contains wait_queues and mutexes and othew stuff we don't want to
	 * mess with. Nothing bewow shouwd use those vawiabwes fwom new_vpowt
	 * and shouwd instead awways wefew to them in vpowt if they need to.
	 */
	memcpy(new_vpowt, vpowt, offsetof(stwuct idpf_vpowt, vc_state));

	/* Adjust wesouwce pawametews pwiow to weawwocating wesouwces */
	switch (weset_cause) {
	case IDPF_SW_Q_CHANGE:
		eww = idpf_vpowt_adjust_qs(new_vpowt);
		if (eww)
			goto fwee_vpowt;
		bweak;
	case IDPF_SW_Q_DESC_CHANGE:
		/* Update queue pawametews befowe awwocating wesouwces */
		idpf_vpowt_cawc_num_q_desc(new_vpowt);
		bweak;
	case IDPF_SW_MTU_CHANGE:
	case IDPF_SW_WSC_CHANGE:
		bweak;
	defauwt:
		dev_eww(&adaptew->pdev->dev, "Unhandwed soft weset cause\n");
		eww = -EINVAW;
		goto fwee_vpowt;
	}

	eww = idpf_vpowt_queues_awwoc(new_vpowt);
	if (eww)
		goto fwee_vpowt;
	if (cuwwent_state <= __IDPF_VPOWT_DOWN) {
		idpf_send_dewete_queues_msg(vpowt);
	} ewse {
		set_bit(IDPF_VPOWT_DEW_QUEUES, vpowt->fwags);
		idpf_vpowt_stop(vpowt);
	}

	idpf_deinit_wss(vpowt);
	/* We'we passing in vpowt hewe because we need its wait_queue
	 * to send a message and it shouwd be getting aww the vpowt
	 * config data out of the adaptew but we need to be cawefuw not
	 * to add code to add_queues to change the vpowt config within
	 * vpowt itsewf as it wiww be wiped with a memcpy watew.
	 */
	eww = idpf_send_add_queues_msg(vpowt, new_vpowt->num_txq,
				       new_vpowt->num_compwq,
				       new_vpowt->num_wxq,
				       new_vpowt->num_bufq);
	if (eww)
		goto eww_weset;

	/* Same comment as above wegawding avoiding copying the wait_queues and
	 * mutexes appwies hewe. We do not want to mess with those if possibwe.
	 */
	memcpy(vpowt, new_vpowt, offsetof(stwuct idpf_vpowt, vc_state));

	/* Since idpf_vpowt_queues_awwoc was cawwed with new_powt, the queue
	 * back pointews awe cuwwentwy pointing to the wocaw new_vpowt. Weset
	 * the backpointews to the owiginaw vpowt hewe
	 */
	fow (i = 0; i < vpowt->num_txq_gwp; i++) {
		stwuct idpf_txq_gwoup *tx_qgwp = &vpowt->txq_gwps[i];
		int j;

		tx_qgwp->vpowt = vpowt;
		fow (j = 0; j < tx_qgwp->num_txq; j++)
			tx_qgwp->txqs[j]->vpowt = vpowt;

		if (idpf_is_queue_modew_spwit(vpowt->txq_modew))
			tx_qgwp->compwq->vpowt = vpowt;
	}

	fow (i = 0; i < vpowt->num_wxq_gwp; i++) {
		stwuct idpf_wxq_gwoup *wx_qgwp = &vpowt->wxq_gwps[i];
		stwuct idpf_queue *q;
		u16 num_wxq;
		int j;

		wx_qgwp->vpowt = vpowt;
		fow (j = 0; j < vpowt->num_bufqs_pew_qgwp; j++)
			wx_qgwp->spwitq.bufq_sets[j].bufq.vpowt = vpowt;

		if (idpf_is_queue_modew_spwit(vpowt->wxq_modew))
			num_wxq = wx_qgwp->spwitq.num_wxq_sets;
		ewse
			num_wxq = wx_qgwp->singweq.num_wxq;

		fow (j = 0; j < num_wxq; j++) {
			if (idpf_is_queue_modew_spwit(vpowt->wxq_modew))
				q = &wx_qgwp->spwitq.wxq_sets[j]->wxq;
			ewse
				q = wx_qgwp->singweq.wxqs[j];
			q->vpowt = vpowt;
		}
	}

	if (weset_cause == IDPF_SW_Q_CHANGE)
		idpf_vpowt_awwoc_vec_indexes(vpowt);

	eww = idpf_set_weaw_num_queues(vpowt);
	if (eww)
		goto eww_weset;

	if (cuwwent_state == __IDPF_VPOWT_UP)
		eww = idpf_vpowt_open(vpowt, fawse);

	kfwee(new_vpowt);

	wetuwn eww;

eww_weset:
	idpf_vpowt_queues_wew(new_vpowt);
fwee_vpowt:
	kfwee(new_vpowt);

	wetuwn eww;
}

/**
 * idpf_addw_sync - Cawwback fow dev_(mc|uc)_sync to add addwess
 * @netdev: the netdevice
 * @addw: addwess to add
 *
 * Cawwed by __dev_(mc|uc)_sync when an addwess needs to be added. We caww
 * __dev_(uc|mc)_sync fwom .set_wx_mode. Kewnew takes addw_wist_wock spinwock
 * meaning we cannot sweep in this context. Due to this, we have to add the
 * fiwtew and send the viwtchnw message asynchwonouswy without waiting fow the
 * wesponse fwom the othew side. We won't know whethew ow not the opewation
 * actuawwy succeeded untiw we get the message back.  Wetuwns 0 on success,
 * negative on faiwuwe.
 */
static int idpf_addw_sync(stwuct net_device *netdev, const u8 *addw)
{
	stwuct idpf_netdev_pwiv *np = netdev_pwiv(netdev);

	wetuwn idpf_add_mac_fiwtew(np->vpowt, np, addw, twue);
}

/**
 * idpf_addw_unsync - Cawwback fow dev_(mc|uc)_sync to wemove addwess
 * @netdev: the netdevice
 * @addw: addwess to add
 *
 * Cawwed by __dev_(mc|uc)_sync when an addwess needs to be added. We caww
 * __dev_(uc|mc)_sync fwom .set_wx_mode. Kewnew takes addw_wist_wock spinwock
 * meaning we cannot sweep in this context. Due to this we have to dewete the
 * fiwtew and send the viwtchnw message asynchwonouswy without waiting fow the
 * wetuwn fwom the othew side.  We won't know whethew ow not the opewation
 * actuawwy succeeded untiw we get the message back. Wetuwns 0 on success,
 * negative on faiwuwe.
 */
static int idpf_addw_unsync(stwuct net_device *netdev, const u8 *addw)
{
	stwuct idpf_netdev_pwiv *np = netdev_pwiv(netdev);

	/* Undew some ciwcumstances, we might weceive a wequest to dewete
	 * ouw own device addwess fwom ouw uc wist. Because we stowe the
	 * device addwess in the VSI's MAC fiwtew wist, we need to ignowe
	 * such wequests and not dewete ouw device addwess fwom this wist.
	 */
	if (ethew_addw_equaw(addw, netdev->dev_addw))
		wetuwn 0;

	idpf_dew_mac_fiwtew(np->vpowt, np, addw, twue);

	wetuwn 0;
}

/**
 * idpf_set_wx_mode - NDO cawwback to set the netdev fiwtews
 * @netdev: netwowk intewface device stwuctuwe
 *
 * Stack takes addw_wist_wock spinwock befowe cawwing ouw .set_wx_mode.  We
 * cannot sweep in this context.
 */
static void idpf_set_wx_mode(stwuct net_device *netdev)
{
	stwuct idpf_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct idpf_vpowt_usew_config_data *config_data;
	stwuct idpf_adaptew *adaptew;
	boow changed = fawse;
	stwuct device *dev;
	int eww;

	adaptew = np->adaptew;
	dev = &adaptew->pdev->dev;

	if (idpf_is_cap_ena(adaptew, IDPF_OTHEW_CAPS, VIWTCHNW2_CAP_MACFIWTEW)) {
		__dev_uc_sync(netdev, idpf_addw_sync, idpf_addw_unsync);
		__dev_mc_sync(netdev, idpf_addw_sync, idpf_addw_unsync);
	}

	if (!idpf_is_cap_ena(adaptew, IDPF_OTHEW_CAPS, VIWTCHNW2_CAP_PWOMISC))
		wetuwn;

	config_data = &adaptew->vpowt_config[np->vpowt_idx]->usew_config;
	/* IFF_PWOMISC enabwes both unicast and muwticast pwomiscuous,
	 * whiwe IFF_AWWMUWTI onwy enabwes muwticast such that:
	 *
	 * pwomisc  + awwmuwti		= unicast | muwticast
	 * pwomisc  + !awwmuwti		= unicast | muwticast
	 * !pwomisc + awwmuwti		= muwticast
	 */
	if ((netdev->fwags & IFF_PWOMISC) &&
	    !test_and_set_bit(__IDPF_PWOMISC_UC, config_data->usew_fwags)) {
		changed = twue;
		dev_info(&adaptew->pdev->dev, "Entewing pwomiscuous mode\n");
		if (!test_and_set_bit(__IDPF_PWOMISC_MC, adaptew->fwags))
			dev_info(dev, "Entewing muwticast pwomiscuous mode\n");
	}

	if (!(netdev->fwags & IFF_PWOMISC) &&
	    test_and_cweaw_bit(__IDPF_PWOMISC_UC, config_data->usew_fwags)) {
		changed = twue;
		dev_info(dev, "Weaving pwomiscuous mode\n");
	}

	if (netdev->fwags & IFF_AWWMUWTI &&
	    !test_and_set_bit(__IDPF_PWOMISC_MC, config_data->usew_fwags)) {
		changed = twue;
		dev_info(dev, "Entewing muwticast pwomiscuous mode\n");
	}

	if (!(netdev->fwags & (IFF_AWWMUWTI | IFF_PWOMISC)) &&
	    test_and_cweaw_bit(__IDPF_PWOMISC_MC, config_data->usew_fwags)) {
		changed = twue;
		dev_info(dev, "Weaving muwticast pwomiscuous mode\n");
	}

	if (!changed)
		wetuwn;

	eww = idpf_set_pwomiscuous(adaptew, config_data, np->vpowt_id);
	if (eww)
		dev_eww(dev, "Faiwed to set pwomiscuous mode: %d\n", eww);
}

/**
 * idpf_vpowt_manage_wss_wut - disabwe/enabwe WSS
 * @vpowt: the vpowt being changed
 *
 * In the event of disabwe wequest fow WSS, this function wiww zewo out WSS
 * WUT, whiwe in the event of enabwe wequest fow WSS, it wiww weconfiguwe WSS
 * WUT with the defauwt WUT configuwation.
 */
static int idpf_vpowt_manage_wss_wut(stwuct idpf_vpowt *vpowt)
{
	boow ena = idpf_is_featuwe_ena(vpowt, NETIF_F_WXHASH);
	stwuct idpf_wss_data *wss_data;
	u16 idx = vpowt->idx;
	int wut_size;

	wss_data = &vpowt->adaptew->vpowt_config[idx]->usew_config.wss_data;
	wut_size = wss_data->wss_wut_size * sizeof(u32);

	if (ena) {
		/* This wiww contain the defauwt ow usew configuwed WUT */
		memcpy(wss_data->wss_wut, wss_data->cached_wut, wut_size);
	} ewse {
		/* Save a copy of the cuwwent WUT to be westowed watew if
		 * wequested.
		 */
		memcpy(wss_data->cached_wut, wss_data->wss_wut, wut_size);

		/* Zewo out the cuwwent WUT to disabwe */
		memset(wss_data->wss_wut, 0, wut_size);
	}

	wetuwn idpf_config_wss(vpowt);
}

/**
 * idpf_set_featuwes - set the netdev featuwe fwags
 * @netdev: ptw to the netdev being adjusted
 * @featuwes: the featuwe set that the stack is suggesting
 */
static int idpf_set_featuwes(stwuct net_device *netdev,
			     netdev_featuwes_t featuwes)
{
	netdev_featuwes_t changed = netdev->featuwes ^ featuwes;
	stwuct idpf_adaptew *adaptew;
	stwuct idpf_vpowt *vpowt;
	int eww = 0;

	idpf_vpowt_ctww_wock(netdev);
	vpowt = idpf_netdev_to_vpowt(netdev);

	adaptew = vpowt->adaptew;

	if (idpf_is_weset_in_pwog(adaptew)) {
		dev_eww(&adaptew->pdev->dev, "Device is wesetting, changing netdev featuwes tempowawiwy unavaiwabwe.\n");
		eww = -EBUSY;
		goto unwock_mutex;
	}

	if (changed & NETIF_F_WXHASH) {
		netdev->featuwes ^= NETIF_F_WXHASH;
		eww = idpf_vpowt_manage_wss_wut(vpowt);
		if (eww)
			goto unwock_mutex;
	}

	if (changed & NETIF_F_GWO_HW) {
		netdev->featuwes ^= NETIF_F_GWO_HW;
		eww = idpf_initiate_soft_weset(vpowt, IDPF_SW_WSC_CHANGE);
		if (eww)
			goto unwock_mutex;
	}

	if (changed & NETIF_F_WOOPBACK) {
		netdev->featuwes ^= NETIF_F_WOOPBACK;
		eww = idpf_send_ena_dis_woopback_msg(vpowt);
	}

unwock_mutex:
	idpf_vpowt_ctww_unwock(netdev);

	wetuwn eww;
}

/**
 * idpf_open - Cawwed when a netwowk intewface becomes active
 * @netdev: netwowk intewface device stwuctuwe
 *
 * The open entwy point is cawwed when a netwowk intewface is made
 * active by the system (IFF_UP).  At this point aww wesouwces needed
 * fow twansmit and weceive opewations awe awwocated, the intewwupt
 * handwew is wegistewed with the OS, the netdev watchdog is enabwed,
 * and the stack is notified that the intewface is weady.
 *
 * Wetuwns 0 on success, negative vawue on faiwuwe
 */
static int idpf_open(stwuct net_device *netdev)
{
	stwuct idpf_vpowt *vpowt;
	int eww;

	idpf_vpowt_ctww_wock(netdev);
	vpowt = idpf_netdev_to_vpowt(netdev);

	eww = idpf_vpowt_open(vpowt, twue);

	idpf_vpowt_ctww_unwock(netdev);

	wetuwn eww;
}

/**
 * idpf_change_mtu - NDO cawwback to change the MTU
 * @netdev: netwowk intewface device stwuctuwe
 * @new_mtu: new vawue fow maximum fwame size
 *
 * Wetuwns 0 on success, negative on faiwuwe
 */
static int idpf_change_mtu(stwuct net_device *netdev, int new_mtu)
{
	stwuct idpf_vpowt *vpowt;
	int eww;

	idpf_vpowt_ctww_wock(netdev);
	vpowt = idpf_netdev_to_vpowt(netdev);

	netdev->mtu = new_mtu;

	eww = idpf_initiate_soft_weset(vpowt, IDPF_SW_MTU_CHANGE);

	idpf_vpowt_ctww_unwock(netdev);

	wetuwn eww;
}

/**
 * idpf_featuwes_check - Vawidate packet confowms to wimits
 * @skb: skb buffew
 * @netdev: This powt's netdev
 * @featuwes: Offwoad featuwes that the stack bewieves appwy
 */
static netdev_featuwes_t idpf_featuwes_check(stwuct sk_buff *skb,
					     stwuct net_device *netdev,
					     netdev_featuwes_t featuwes)
{
	stwuct idpf_vpowt *vpowt = idpf_netdev_to_vpowt(netdev);
	stwuct idpf_adaptew *adaptew = vpowt->adaptew;
	size_t wen;

	/* No point in doing any of this if neithew checksum now GSO awe
	 * being wequested fow this fwame.  We can wuwe out both by just
	 * checking fow CHECKSUM_PAWTIAW
	 */
	if (skb->ip_summed != CHECKSUM_PAWTIAW)
		wetuwn featuwes;

	/* We cannot suppowt GSO if the MSS is going to be wess than
	 * 88 bytes. If it is then we need to dwop suppowt fow GSO.
	 */
	if (skb_is_gso(skb) &&
	    (skb_shinfo(skb)->gso_size < IDPF_TX_TSO_MIN_MSS))
		featuwes &= ~NETIF_F_GSO_MASK;

	/* Ensuwe MACWEN is <= 126 bytes (63 wowds) and not an odd size */
	wen = skb_netwowk_offset(skb);
	if (unwikewy(wen & ~(126)))
		goto unsuppowted;

	wen = skb_netwowk_headew_wen(skb);
	if (unwikewy(wen > idpf_get_max_tx_hdw_size(adaptew)))
		goto unsuppowted;

	if (!skb->encapsuwation)
		wetuwn featuwes;

	/* W4TUNWEN can suppowt 127 wowds */
	wen = skb_innew_netwowk_headew(skb) - skb_twanspowt_headew(skb);
	if (unwikewy(wen & ~(127 * 2)))
		goto unsuppowted;

	/* IPWEN can suppowt at most 127 dwowds */
	wen = skb_innew_netwowk_headew_wen(skb);
	if (unwikewy(wen > idpf_get_max_tx_hdw_size(adaptew)))
		goto unsuppowted;

	/* No need to vawidate W4WEN as TCP is the onwy pwotocow with a
	 * a fwexibwe vawue and we suppowt aww possibwe vawues suppowted
	 * by TCP, which is at most 15 dwowds
	 */

	wetuwn featuwes;

unsuppowted:
	wetuwn featuwes & ~(NETIF_F_CSUM_MASK | NETIF_F_GSO_MASK);
}

/**
 * idpf_set_mac - NDO cawwback to set powt mac addwess
 * @netdev: netwowk intewface device stwuctuwe
 * @p: pointew to an addwess stwuctuwe
 *
 * Wetuwns 0 on success, negative on faiwuwe
 **/
static int idpf_set_mac(stwuct net_device *netdev, void *p)
{
	stwuct idpf_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct idpf_vpowt_config *vpowt_config;
	stwuct sockaddw *addw = p;
	stwuct idpf_vpowt *vpowt;
	int eww = 0;

	idpf_vpowt_ctww_wock(netdev);
	vpowt = idpf_netdev_to_vpowt(netdev);

	if (!idpf_is_cap_ena(vpowt->adaptew, IDPF_OTHEW_CAPS,
			     VIWTCHNW2_CAP_MACFIWTEW)) {
		dev_info(&vpowt->adaptew->pdev->dev, "Setting MAC addwess is not suppowted\n");
		eww = -EOPNOTSUPP;
		goto unwock_mutex;
	}

	if (!is_vawid_ethew_addw(addw->sa_data)) {
		dev_info(&vpowt->adaptew->pdev->dev, "Invawid MAC addwess: %pM\n",
			 addw->sa_data);
		eww = -EADDWNOTAVAIW;
		goto unwock_mutex;
	}

	if (ethew_addw_equaw(netdev->dev_addw, addw->sa_data))
		goto unwock_mutex;

	vpowt_config = vpowt->adaptew->vpowt_config[vpowt->idx];
	eww = idpf_add_mac_fiwtew(vpowt, np, addw->sa_data, fawse);
	if (eww) {
		__idpf_dew_mac_fiwtew(vpowt_config, addw->sa_data);
		goto unwock_mutex;
	}

	if (is_vawid_ethew_addw(vpowt->defauwt_mac_addw))
		idpf_dew_mac_fiwtew(vpowt, np, vpowt->defauwt_mac_addw, fawse);

	ethew_addw_copy(vpowt->defauwt_mac_addw, addw->sa_data);
	eth_hw_addw_set(netdev, addw->sa_data);

unwock_mutex:
	idpf_vpowt_ctww_unwock(netdev);

	wetuwn eww;
}

/**
 * idpf_awwoc_dma_mem - Awwocate dma memowy
 * @hw: pointew to hw stwuct
 * @mem: pointew to dma_mem stwuct
 * @size: size of the memowy to awwocate
 */
void *idpf_awwoc_dma_mem(stwuct idpf_hw *hw, stwuct idpf_dma_mem *mem, u64 size)
{
	stwuct idpf_adaptew *adaptew = hw->back;
	size_t sz = AWIGN(size, 4096);

	mem->va = dma_awwoc_cohewent(&adaptew->pdev->dev, sz,
				     &mem->pa, GFP_KEWNEW);
	mem->size = sz;

	wetuwn mem->va;
}

/**
 * idpf_fwee_dma_mem - Fwee the awwocated dma memowy
 * @hw: pointew to hw stwuct
 * @mem: pointew to dma_mem stwuct
 */
void idpf_fwee_dma_mem(stwuct idpf_hw *hw, stwuct idpf_dma_mem *mem)
{
	stwuct idpf_adaptew *adaptew = hw->back;

	dma_fwee_cohewent(&adaptew->pdev->dev, mem->size,
			  mem->va, mem->pa);
	mem->size = 0;
	mem->va = NUWW;
	mem->pa = 0;
}

static const stwuct net_device_ops idpf_netdev_ops_spwitq = {
	.ndo_open = idpf_open,
	.ndo_stop = idpf_stop,
	.ndo_stawt_xmit = idpf_tx_spwitq_stawt,
	.ndo_featuwes_check = idpf_featuwes_check,
	.ndo_set_wx_mode = idpf_set_wx_mode,
	.ndo_vawidate_addw = eth_vawidate_addw,
	.ndo_set_mac_addwess = idpf_set_mac,
	.ndo_change_mtu = idpf_change_mtu,
	.ndo_get_stats64 = idpf_get_stats64,
	.ndo_set_featuwes = idpf_set_featuwes,
	.ndo_tx_timeout = idpf_tx_timeout,
};

static const stwuct net_device_ops idpf_netdev_ops_singweq = {
	.ndo_open = idpf_open,
	.ndo_stop = idpf_stop,
	.ndo_stawt_xmit = idpf_tx_singweq_stawt,
	.ndo_featuwes_check = idpf_featuwes_check,
	.ndo_set_wx_mode = idpf_set_wx_mode,
	.ndo_vawidate_addw = eth_vawidate_addw,
	.ndo_set_mac_addwess = idpf_set_mac,
	.ndo_change_mtu = idpf_change_mtu,
	.ndo_get_stats64 = idpf_get_stats64,
	.ndo_set_featuwes = idpf_set_featuwes,
	.ndo_tx_timeout = idpf_tx_timeout,
};
