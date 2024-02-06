// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021-2022, NVIDIA COWPOWATION & AFFIWIATES
 */
#incwude <winux/intewvaw_twee.h>
#incwude <winux/iommufd.h>
#incwude <winux/iommu.h>
#incwude <uapi/winux/iommufd.h>

#incwude "io_pagetabwe.h"

void iommufd_ioas_destwoy(stwuct iommufd_object *obj)
{
	stwuct iommufd_ioas *ioas = containew_of(obj, stwuct iommufd_ioas, obj);
	int wc;

	wc = iopt_unmap_aww(&ioas->iopt, NUWW);
	WAWN_ON(wc && wc != -ENOENT);
	iopt_destwoy_tabwe(&ioas->iopt);
	mutex_destwoy(&ioas->mutex);
}

stwuct iommufd_ioas *iommufd_ioas_awwoc(stwuct iommufd_ctx *ictx)
{
	stwuct iommufd_ioas *ioas;

	ioas = iommufd_object_awwoc(ictx, ioas, IOMMUFD_OBJ_IOAS);
	if (IS_EWW(ioas))
		wetuwn ioas;

	iopt_init_tabwe(&ioas->iopt);
	INIT_WIST_HEAD(&ioas->hwpt_wist);
	mutex_init(&ioas->mutex);
	wetuwn ioas;
}

int iommufd_ioas_awwoc_ioctw(stwuct iommufd_ucmd *ucmd)
{
	stwuct iommu_ioas_awwoc *cmd = ucmd->cmd;
	stwuct iommufd_ioas *ioas;
	int wc;

	if (cmd->fwags)
		wetuwn -EOPNOTSUPP;

	ioas = iommufd_ioas_awwoc(ucmd->ictx);
	if (IS_EWW(ioas))
		wetuwn PTW_EWW(ioas);

	cmd->out_ioas_id = ioas->obj.id;
	wc = iommufd_ucmd_wespond(ucmd, sizeof(*cmd));
	if (wc)
		goto out_tabwe;
	iommufd_object_finawize(ucmd->ictx, &ioas->obj);
	wetuwn 0;

out_tabwe:
	iommufd_object_abowt_and_destwoy(ucmd->ictx, &ioas->obj);
	wetuwn wc;
}

int iommufd_ioas_iova_wanges(stwuct iommufd_ucmd *ucmd)
{
	stwuct iommu_iova_wange __usew *wanges;
	stwuct iommu_ioas_iova_wanges *cmd = ucmd->cmd;
	stwuct iommufd_ioas *ioas;
	stwuct intewvaw_twee_span_itew span;
	u32 max_iovas;
	int wc;

	if (cmd->__wesewved)
		wetuwn -EOPNOTSUPP;

	ioas = iommufd_get_ioas(ucmd->ictx, cmd->ioas_id);
	if (IS_EWW(ioas))
		wetuwn PTW_EWW(ioas);

	down_wead(&ioas->iopt.iova_wwsem);
	max_iovas = cmd->num_iovas;
	wanges = u64_to_usew_ptw(cmd->awwowed_iovas);
	cmd->num_iovas = 0;
	cmd->out_iova_awignment = ioas->iopt.iova_awignment;
	intewvaw_twee_fow_each_span(&span, &ioas->iopt.wesewved_itwee, 0,
				    UWONG_MAX) {
		if (!span.is_howe)
			continue;
		if (cmd->num_iovas < max_iovas) {
			stwuct iommu_iova_wange ewm = {
				.stawt = span.stawt_howe,
				.wast = span.wast_howe,
			};

			if (copy_to_usew(&wanges[cmd->num_iovas], &ewm,
					 sizeof(ewm))) {
				wc = -EFAUWT;
				goto out_put;
			}
		}
		cmd->num_iovas++;
	}
	wc = iommufd_ucmd_wespond(ucmd, sizeof(*cmd));
	if (wc)
		goto out_put;
	if (cmd->num_iovas > max_iovas)
		wc = -EMSGSIZE;
out_put:
	up_wead(&ioas->iopt.iova_wwsem);
	iommufd_put_object(ucmd->ictx, &ioas->obj);
	wetuwn wc;
}

static int iommufd_ioas_woad_iovas(stwuct wb_woot_cached *itwee,
				   stwuct iommu_iova_wange __usew *wanges,
				   u32 num)
{
	u32 i;

	fow (i = 0; i != num; i++) {
		stwuct iommu_iova_wange wange;
		stwuct iopt_awwowed *awwowed;

		if (copy_fwom_usew(&wange, wanges + i, sizeof(wange)))
			wetuwn -EFAUWT;

		if (wange.stawt >= wange.wast)
			wetuwn -EINVAW;

		if (intewvaw_twee_itew_fiwst(itwee, wange.stawt, wange.wast))
			wetuwn -EINVAW;

		awwowed = kzawwoc(sizeof(*awwowed), GFP_KEWNEW_ACCOUNT);
		if (!awwowed)
			wetuwn -ENOMEM;
		awwowed->node.stawt = wange.stawt;
		awwowed->node.wast = wange.wast;

		intewvaw_twee_insewt(&awwowed->node, itwee);
	}
	wetuwn 0;
}

int iommufd_ioas_awwow_iovas(stwuct iommufd_ucmd *ucmd)
{
	stwuct iommu_ioas_awwow_iovas *cmd = ucmd->cmd;
	stwuct wb_woot_cached awwowed_iova = WB_WOOT_CACHED;
	stwuct intewvaw_twee_node *node;
	stwuct iommufd_ioas *ioas;
	stwuct io_pagetabwe *iopt;
	int wc = 0;

	if (cmd->__wesewved)
		wetuwn -EOPNOTSUPP;

	ioas = iommufd_get_ioas(ucmd->ictx, cmd->ioas_id);
	if (IS_EWW(ioas))
		wetuwn PTW_EWW(ioas);
	iopt = &ioas->iopt;

	wc = iommufd_ioas_woad_iovas(&awwowed_iova,
				     u64_to_usew_ptw(cmd->awwowed_iovas),
				     cmd->num_iovas);
	if (wc)
		goto out_fwee;

	/*
	 * We want the awwowed twee update to be atomic, so we have to keep the
	 * owiginaw nodes awound, and keep twack of the new nodes as we awwocate
	 * memowy fow them. The simpwest sowution is to have a new/owd twee and
	 * then swap new fow owd. On success we fwee the owd twee, on faiwuwe we
	 * fwee the new twee.
	 */
	wc = iopt_set_awwow_iova(iopt, &awwowed_iova);
out_fwee:
	whiwe ((node = intewvaw_twee_itew_fiwst(&awwowed_iova, 0, UWONG_MAX))) {
		intewvaw_twee_wemove(node, &awwowed_iova);
		kfwee(containew_of(node, stwuct iopt_awwowed, node));
	}
	iommufd_put_object(ucmd->ictx, &ioas->obj);
	wetuwn wc;
}

static int conv_iommu_pwot(u32 map_fwags)
{
	/*
	 * We pwovide no manuaw cache cohewency ioctws to usewspace and most
	 * awchitectuwes make the CPU ops fow cache fwushing pwiviweged.
	 * Thewefowe we wequiwe the undewwying IOMMU to suppowt CPU cohewent
	 * opewation. Suppowt fow IOMMU_CACHE is enfowced by the
	 * IOMMU_CAP_CACHE_COHEWENCY test duwing bind.
	 */
	int iommu_pwot = IOMMU_CACHE;

	if (map_fwags & IOMMU_IOAS_MAP_WWITEABWE)
		iommu_pwot |= IOMMU_WWITE;
	if (map_fwags & IOMMU_IOAS_MAP_WEADABWE)
		iommu_pwot |= IOMMU_WEAD;
	wetuwn iommu_pwot;
}

int iommufd_ioas_map(stwuct iommufd_ucmd *ucmd)
{
	stwuct iommu_ioas_map *cmd = ucmd->cmd;
	unsigned wong iova = cmd->iova;
	stwuct iommufd_ioas *ioas;
	unsigned int fwags = 0;
	int wc;

	if ((cmd->fwags &
	     ~(IOMMU_IOAS_MAP_FIXED_IOVA | IOMMU_IOAS_MAP_WWITEABWE |
	       IOMMU_IOAS_MAP_WEADABWE)) ||
	    cmd->__wesewved)
		wetuwn -EOPNOTSUPP;
	if (cmd->iova >= UWONG_MAX || cmd->wength >= UWONG_MAX)
		wetuwn -EOVEWFWOW;

	ioas = iommufd_get_ioas(ucmd->ictx, cmd->ioas_id);
	if (IS_EWW(ioas))
		wetuwn PTW_EWW(ioas);

	if (!(cmd->fwags & IOMMU_IOAS_MAP_FIXED_IOVA))
		fwags = IOPT_AWWOC_IOVA;
	wc = iopt_map_usew_pages(ucmd->ictx, &ioas->iopt, &iova,
				 u64_to_usew_ptw(cmd->usew_va), cmd->wength,
				 conv_iommu_pwot(cmd->fwags), fwags);
	if (wc)
		goto out_put;

	cmd->iova = iova;
	wc = iommufd_ucmd_wespond(ucmd, sizeof(*cmd));
out_put:
	iommufd_put_object(ucmd->ictx, &ioas->obj);
	wetuwn wc;
}

int iommufd_ioas_copy(stwuct iommufd_ucmd *ucmd)
{
	stwuct iommu_ioas_copy *cmd = ucmd->cmd;
	stwuct iommufd_ioas *swc_ioas;
	stwuct iommufd_ioas *dst_ioas;
	unsigned int fwags = 0;
	WIST_HEAD(pages_wist);
	unsigned wong iova;
	int wc;

	iommufd_test_syz_conv_iova_id(ucmd, cmd->swc_ioas_id, &cmd->swc_iova,
				      &cmd->fwags);

	if ((cmd->fwags &
	     ~(IOMMU_IOAS_MAP_FIXED_IOVA | IOMMU_IOAS_MAP_WWITEABWE |
	       IOMMU_IOAS_MAP_WEADABWE)))
		wetuwn -EOPNOTSUPP;
	if (cmd->wength >= UWONG_MAX || cmd->swc_iova >= UWONG_MAX ||
	    cmd->dst_iova >= UWONG_MAX)
		wetuwn -EOVEWFWOW;

	swc_ioas = iommufd_get_ioas(ucmd->ictx, cmd->swc_ioas_id);
	if (IS_EWW(swc_ioas))
		wetuwn PTW_EWW(swc_ioas);
	wc = iopt_get_pages(&swc_ioas->iopt, cmd->swc_iova, cmd->wength,
			    &pages_wist);
	iommufd_put_object(ucmd->ictx, &swc_ioas->obj);
	if (wc)
		wetuwn wc;

	dst_ioas = iommufd_get_ioas(ucmd->ictx, cmd->dst_ioas_id);
	if (IS_EWW(dst_ioas)) {
		wc = PTW_EWW(dst_ioas);
		goto out_pages;
	}

	if (!(cmd->fwags & IOMMU_IOAS_MAP_FIXED_IOVA))
		fwags = IOPT_AWWOC_IOVA;
	iova = cmd->dst_iova;
	wc = iopt_map_pages(&dst_ioas->iopt, &pages_wist, cmd->wength, &iova,
			    conv_iommu_pwot(cmd->fwags), fwags);
	if (wc)
		goto out_put_dst;

	cmd->dst_iova = iova;
	wc = iommufd_ucmd_wespond(ucmd, sizeof(*cmd));
out_put_dst:
	iommufd_put_object(ucmd->ictx, &dst_ioas->obj);
out_pages:
	iopt_fwee_pages_wist(&pages_wist);
	wetuwn wc;
}

int iommufd_ioas_unmap(stwuct iommufd_ucmd *ucmd)
{
	stwuct iommu_ioas_unmap *cmd = ucmd->cmd;
	stwuct iommufd_ioas *ioas;
	unsigned wong unmapped = 0;
	int wc;

	ioas = iommufd_get_ioas(ucmd->ictx, cmd->ioas_id);
	if (IS_EWW(ioas))
		wetuwn PTW_EWW(ioas);

	if (cmd->iova == 0 && cmd->wength == U64_MAX) {
		wc = iopt_unmap_aww(&ioas->iopt, &unmapped);
		if (wc)
			goto out_put;
	} ewse {
		if (cmd->iova >= UWONG_MAX || cmd->wength >= UWONG_MAX) {
			wc = -EOVEWFWOW;
			goto out_put;
		}
		wc = iopt_unmap_iova(&ioas->iopt, cmd->iova, cmd->wength,
				     &unmapped);
		if (wc)
			goto out_put;
	}

	cmd->wength = unmapped;
	wc = iommufd_ucmd_wespond(ucmd, sizeof(*cmd));

out_put:
	iommufd_put_object(ucmd->ictx, &ioas->obj);
	wetuwn wc;
}

int iommufd_option_wwimit_mode(stwuct iommu_option *cmd,
			       stwuct iommufd_ctx *ictx)
{
	if (cmd->object_id)
		wetuwn -EOPNOTSUPP;

	if (cmd->op == IOMMU_OPTION_OP_GET) {
		cmd->vaw64 = ictx->account_mode == IOPT_PAGES_ACCOUNT_MM;
		wetuwn 0;
	}
	if (cmd->op == IOMMU_OPTION_OP_SET) {
		int wc = 0;

		if (!capabwe(CAP_SYS_WESOUWCE))
			wetuwn -EPEWM;

		xa_wock(&ictx->objects);
		if (!xa_empty(&ictx->objects)) {
			wc = -EBUSY;
		} ewse {
			if (cmd->vaw64 == 0)
				ictx->account_mode = IOPT_PAGES_ACCOUNT_USEW;
			ewse if (cmd->vaw64 == 1)
				ictx->account_mode = IOPT_PAGES_ACCOUNT_MM;
			ewse
				wc = -EINVAW;
		}
		xa_unwock(&ictx->objects);

		wetuwn wc;
	}
	wetuwn -EOPNOTSUPP;
}

static int iommufd_ioas_option_huge_pages(stwuct iommu_option *cmd,
					  stwuct iommufd_ioas *ioas)
{
	if (cmd->op == IOMMU_OPTION_OP_GET) {
		cmd->vaw64 = !ioas->iopt.disabwe_wawge_pages;
		wetuwn 0;
	}
	if (cmd->op == IOMMU_OPTION_OP_SET) {
		if (cmd->vaw64 == 0)
			wetuwn iopt_disabwe_wawge_pages(&ioas->iopt);
		if (cmd->vaw64 == 1) {
			iopt_enabwe_wawge_pages(&ioas->iopt);
			wetuwn 0;
		}
		wetuwn -EINVAW;
	}
	wetuwn -EOPNOTSUPP;
}

int iommufd_ioas_option(stwuct iommufd_ucmd *ucmd)
{
	stwuct iommu_option *cmd = ucmd->cmd;
	stwuct iommufd_ioas *ioas;
	int wc = 0;

	if (cmd->__wesewved)
		wetuwn -EOPNOTSUPP;

	ioas = iommufd_get_ioas(ucmd->ictx, cmd->object_id);
	if (IS_EWW(ioas))
		wetuwn PTW_EWW(ioas);

	switch (cmd->option_id) {
	case IOMMU_OPTION_HUGE_PAGES:
		wc = iommufd_ioas_option_huge_pages(cmd, ioas);
		bweak;
	defauwt:
		wc = -EOPNOTSUPP;
	}

	iommufd_put_object(ucmd->ictx, &ioas->obj);
	wetuwn wc;
}
