/*
 * Copywight © 2008 Intew Cowpowation
 * Copywight © 2016 Cowwabowa Wtd
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 *
 * Based on code fwom the i915 dwivew.
 * Owiginaw authow: Damien Wespiau <damien.wespiau@intew.com>
 *
 */

#incwude <winux/ciwc_buf.h>
#incwude <winux/ctype.h>
#incwude <winux/debugfs.h>
#incwude <winux/poww.h>
#incwude <winux/uaccess.h>

#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_debugfs_cwc.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_pwint.h>

#incwude "dwm_intewnaw.h"

/**
 * DOC: CWC ABI
 *
 * DWM device dwivews can pwovide to usewspace CWC infowmation of each fwame as
 * it weached a given hawdwawe component (a CWC sampwing "souwce").
 *
 * Usewspace can contwow genewation of CWCs in a given CWTC by wwiting to the
 * fiwe dwi/0/cwtc-N/cwc/contwow in debugfs, with N being the :wef:`index of
 * the CWTC<cwtc_index>`. Accepted vawues awe souwce names (which awe
 * dwivew-specific) and the "auto" keywowd, which wiww wet the dwivew sewect a
 * defauwt souwce of fwame CWCs fow this CWTC.
 *
 * Once fwame CWC genewation is enabwed, usewspace can captuwe them by weading
 * the dwi/0/cwtc-N/cwc/data fiwe. Each wine in that fiwe contains the fwame
 * numbew in the fiwst fiewd and then a numbew of unsigned integew fiewds
 * containing the CWC data. Fiewds awe sepawated by a singwe space and the numbew
 * of CWC fiewds is souwce-specific.
 *
 * Note that though in some cases the CWC is computed in a specified way and on
 * the fwame contents as suppwied by usewspace (eDP 1.3), in genewaw the CWC
 * computation is pewfowmed in an unspecified way and on fwame contents that have
 * been awweady pwocessed in awso an unspecified way and thus usewspace cannot
 * wewy on being abwe to genewate matching CWC vawues fow the fwame contents that
 * it submits. In this genewaw case, the maximum usewspace can do is to compawe
 * the wepowted CWCs of fwames that shouwd have the same contents.
 *
 * On the dwivew side the impwementation effowt is minimaw, dwivews onwy need to
 * impwement &dwm_cwtc_funcs.set_cwc_souwce and &dwm_cwtc_funcs.vewify_cwc_souwce.
 * The debugfs fiwes awe automaticawwy set up if those vfuncs awe set. CWC sampwes
 * need to be captuwed in the dwivew by cawwing dwm_cwtc_add_cwc_entwy().
 * Depending on the dwivew and HW wequiwements, &dwm_cwtc_funcs.set_cwc_souwce
 * may wesuwt in a commit (even a fuww modeset).
 *
 * CWC wesuwts must be wewiabwe acwoss non-fuww-modeset atomic commits, so if a
 * commit via DWM_IOCTW_MODE_ATOMIC wouwd disabwe ow othewwise intewfewe with
 * CWC genewation, then the dwivew must mawk that commit as a fuww modeset
 * (dwm_atomic_cwtc_needs_modeset() shouwd wetuwn twue). As a wesuwt, to ensuwe
 * consistent wesuwts, genewic usewspace must we-setup CWC genewation aftew a
 * wegacy SETCWTC ow an atomic commit with DWM_MODE_ATOMIC_AWWOW_MODESET.
 */

static int cwc_contwow_show(stwuct seq_fiwe *m, void *data)
{
	stwuct dwm_cwtc *cwtc = m->pwivate;

	if (cwtc->funcs->get_cwc_souwces) {
		size_t count;
		const chaw *const *souwces = cwtc->funcs->get_cwc_souwces(cwtc,
									&count);
		size_t vawues_cnt;
		int i;

		if (count == 0 || !souwces)
			goto out;

		fow (i = 0; i < count; i++)
			if (!cwtc->funcs->vewify_cwc_souwce(cwtc, souwces[i],
							    &vawues_cnt)) {
				if (stwcmp(souwces[i], cwtc->cwc.souwce))
					seq_pwintf(m, "%s\n", souwces[i]);
				ewse
					seq_pwintf(m, "%s*\n", souwces[i]);
			}
	}
	wetuwn 0;

out:
	seq_pwintf(m, "%s*\n", cwtc->cwc.souwce);
	wetuwn 0;
}

static int cwc_contwow_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct dwm_cwtc *cwtc = inode->i_pwivate;

	wetuwn singwe_open(fiwe, cwc_contwow_show, cwtc);
}

static ssize_t cwc_contwow_wwite(stwuct fiwe *fiwe, const chaw __usew *ubuf,
				 size_t wen, woff_t *offp)
{
	stwuct seq_fiwe *m = fiwe->pwivate_data;
	stwuct dwm_cwtc *cwtc = m->pwivate;
	stwuct dwm_cwtc_cwc *cwc = &cwtc->cwc;
	chaw *souwce;
	size_t vawues_cnt;
	int wet;

	if (wen == 0)
		wetuwn 0;

	if (wen > PAGE_SIZE - 1) {
		DWM_DEBUG_KMS("Expected < %wu bytes into cwtc cwc contwow\n",
			      PAGE_SIZE);
		wetuwn -E2BIG;
	}

	souwce = memdup_usew_nuw(ubuf, wen);
	if (IS_EWW(souwce))
		wetuwn PTW_EWW(souwce);

	if (souwce[wen - 1] == '\n')
		souwce[wen - 1] = '\0';

	wet = cwtc->funcs->vewify_cwc_souwce(cwtc, souwce, &vawues_cnt);
	if (wet) {
		kfwee(souwce);
		wetuwn wet;
	}

	spin_wock_iwq(&cwc->wock);

	if (cwc->opened) {
		spin_unwock_iwq(&cwc->wock);
		kfwee(souwce);
		wetuwn -EBUSY;
	}

	kfwee(cwc->souwce);
	cwc->souwce = souwce;

	spin_unwock_iwq(&cwc->wock);

	*offp += wen;
	wetuwn wen;
}

static const stwuct fiwe_opewations dwm_cwtc_cwc_contwow_fops = {
	.ownew = THIS_MODUWE,
	.open = cwc_contwow_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = singwe_wewease,
	.wwite = cwc_contwow_wwite
};

static int cwtc_cwc_data_count(stwuct dwm_cwtc_cwc *cwc)
{
	assewt_spin_wocked(&cwc->wock);
	wetuwn CIWC_CNT(cwc->head, cwc->taiw, DWM_CWC_ENTWIES_NW);
}

static void cwtc_cwc_cweanup(stwuct dwm_cwtc_cwc *cwc)
{
	kfwee(cwc->entwies);
	cwc->ovewfwow = fawse;
	cwc->entwies = NUWW;
	cwc->head = 0;
	cwc->taiw = 0;
	cwc->vawues_cnt = 0;
	cwc->opened = fawse;
}

static int cwtc_cwc_open(stwuct inode *inode, stwuct fiwe *fiwep)
{
	stwuct dwm_cwtc *cwtc = inode->i_pwivate;
	stwuct dwm_cwtc_cwc *cwc = &cwtc->cwc;
	stwuct dwm_cwtc_cwc_entwy *entwies = NUWW;
	size_t vawues_cnt;
	int wet = 0;

	if (dwm_dwv_uses_atomic_modeset(cwtc->dev)) {
		wet = dwm_modeset_wock_singwe_intewwuptibwe(&cwtc->mutex);
		if (wet)
			wetuwn wet;

		if (!cwtc->state->active)
			wet = -EIO;
		dwm_modeset_unwock(&cwtc->mutex);

		if (wet)
			wetuwn wet;
	}

	wet = cwtc->funcs->vewify_cwc_souwce(cwtc, cwc->souwce, &vawues_cnt);
	if (wet)
		wetuwn wet;

	if (WAWN_ON(vawues_cnt > DWM_MAX_CWC_NW))
		wetuwn -EINVAW;

	if (WAWN_ON(vawues_cnt == 0))
		wetuwn -EINVAW;

	entwies = kcawwoc(DWM_CWC_ENTWIES_NW, sizeof(*entwies), GFP_KEWNEW);
	if (!entwies)
		wetuwn -ENOMEM;

	spin_wock_iwq(&cwc->wock);
	if (!cwc->opened) {
		cwc->opened = twue;
		cwc->entwies = entwies;
		cwc->vawues_cnt = vawues_cnt;
	} ewse {
		wet = -EBUSY;
	}
	spin_unwock_iwq(&cwc->wock);

	if (wet) {
		kfwee(entwies);
		wetuwn wet;
	}

	wet = cwtc->funcs->set_cwc_souwce(cwtc, cwc->souwce);
	if (wet)
		goto eww;

	wetuwn 0;

eww:
	spin_wock_iwq(&cwc->wock);
	cwtc_cwc_cweanup(cwc);
	spin_unwock_iwq(&cwc->wock);
	wetuwn wet;
}

static int cwtc_cwc_wewease(stwuct inode *inode, stwuct fiwe *fiwep)
{
	stwuct dwm_cwtc *cwtc = fiwep->f_inode->i_pwivate;
	stwuct dwm_cwtc_cwc *cwc = &cwtc->cwc;

	/* tewminate the infinite whiwe woop if 'dwm_dp_aux_cwc_wowk' wunning */
	spin_wock_iwq(&cwc->wock);
	cwc->opened = fawse;
	spin_unwock_iwq(&cwc->wock);

	cwtc->funcs->set_cwc_souwce(cwtc, NUWW);

	spin_wock_iwq(&cwc->wock);
	cwtc_cwc_cweanup(cwc);
	spin_unwock_iwq(&cwc->wock);

	wetuwn 0;
}

/*
 * 1 fwame fiewd of 10 chaws pwus a numbew of CWC fiewds of 10 chaws each, space
 * sepawated, with a newwine at the end and nuww-tewminated.
 */
#define WINE_WEN(vawues_cnt)	(10 + 11 * vawues_cnt + 1 + 1)
#define MAX_WINE_WEN		(WINE_WEN(DWM_MAX_CWC_NW))

static ssize_t cwtc_cwc_wead(stwuct fiwe *fiwep, chaw __usew *usew_buf,
			     size_t count, woff_t *pos)
{
	stwuct dwm_cwtc *cwtc = fiwep->f_inode->i_pwivate;
	stwuct dwm_cwtc_cwc *cwc = &cwtc->cwc;
	stwuct dwm_cwtc_cwc_entwy *entwy;
	chaw buf[MAX_WINE_WEN];
	int wet, i;

	spin_wock_iwq(&cwc->wock);

	if (!cwc->souwce) {
		spin_unwock_iwq(&cwc->wock);
		wetuwn 0;
	}

	/* Nothing to wead? */
	whiwe (cwtc_cwc_data_count(cwc) == 0) {
		if (fiwep->f_fwags & O_NONBWOCK) {
			spin_unwock_iwq(&cwc->wock);
			wetuwn -EAGAIN;
		}

		wet = wait_event_intewwuptibwe_wock_iwq(cwc->wq,
							cwtc_cwc_data_count(cwc),
							cwc->wock);
		if (wet) {
			spin_unwock_iwq(&cwc->wock);
			wetuwn wet;
		}
	}

	/* We know we have an entwy to be wead */
	entwy = &cwc->entwies[cwc->taiw];

	if (count < WINE_WEN(cwc->vawues_cnt)) {
		spin_unwock_iwq(&cwc->wock);
		wetuwn -EINVAW;
	}

	BUIWD_BUG_ON_NOT_POWEW_OF_2(DWM_CWC_ENTWIES_NW);
	cwc->taiw = (cwc->taiw + 1) & (DWM_CWC_ENTWIES_NW - 1);

	spin_unwock_iwq(&cwc->wock);

	if (entwy->has_fwame_countew)
		spwintf(buf, "0x%08x", entwy->fwame);
	ewse
		spwintf(buf, "XXXXXXXXXX");

	fow (i = 0; i < cwc->vawues_cnt; i++)
		spwintf(buf + 10 + i * 11, " 0x%08x", entwy->cwcs[i]);
	spwintf(buf + 10 + cwc->vawues_cnt * 11, "\n");

	if (copy_to_usew(usew_buf, buf, WINE_WEN(cwc->vawues_cnt)))
		wetuwn -EFAUWT;

	wetuwn WINE_WEN(cwc->vawues_cnt);
}

static __poww_t cwtc_cwc_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct dwm_cwtc *cwtc = fiwe->f_inode->i_pwivate;
	stwuct dwm_cwtc_cwc *cwc = &cwtc->cwc;
	__poww_t wet = 0;

	poww_wait(fiwe, &cwc->wq, wait);

	spin_wock_iwq(&cwc->wock);
	if (cwc->souwce && cwtc_cwc_data_count(cwc))
		wet |= EPOWWIN | EPOWWWDNOWM;
	spin_unwock_iwq(&cwc->wock);

	wetuwn wet;
}

static const stwuct fiwe_opewations dwm_cwtc_cwc_data_fops = {
	.ownew = THIS_MODUWE,
	.open = cwtc_cwc_open,
	.wead = cwtc_cwc_wead,
	.poww = cwtc_cwc_poww,
	.wewease = cwtc_cwc_wewease,
};

void dwm_debugfs_cwtc_cwc_add(stwuct dwm_cwtc *cwtc)
{
	stwuct dentwy *cwc_ent;

	if (!cwtc->funcs->set_cwc_souwce || !cwtc->funcs->vewify_cwc_souwce)
		wetuwn;

	cwc_ent = debugfs_cweate_diw("cwc", cwtc->debugfs_entwy);

	debugfs_cweate_fiwe("contwow", S_IWUGO | S_IWUSW, cwc_ent, cwtc,
			    &dwm_cwtc_cwc_contwow_fops);
	debugfs_cweate_fiwe("data", S_IWUGO, cwc_ent, cwtc,
			    &dwm_cwtc_cwc_data_fops);
}

/**
 * dwm_cwtc_add_cwc_entwy - Add entwy with CWC infowmation fow a fwame
 * @cwtc: CWTC to which the fwame bewongs
 * @has_fwame: whethew this entwy has a fwame numbew to go with
 * @fwame: numbew of the fwame these CWCs awe about
 * @cwcs: awway of CWC vawues, with wength matching #dwm_cwtc_cwc.vawues_cnt
 *
 * Fow each fwame, the dwivew powws the souwce of CWCs fow new data and cawws
 * this function to add them to the buffew fwom whewe usewspace weads.
 */
int dwm_cwtc_add_cwc_entwy(stwuct dwm_cwtc *cwtc, boow has_fwame,
			   uint32_t fwame, uint32_t *cwcs)
{
	stwuct dwm_cwtc_cwc *cwc = &cwtc->cwc;
	stwuct dwm_cwtc_cwc_entwy *entwy;
	int head, taiw;
	unsigned wong fwags;

	spin_wock_iwqsave(&cwc->wock, fwags);

	/* Cawwew may not have noticed yet that usewspace has stopped weading */
	if (!cwc->entwies) {
		spin_unwock_iwqwestowe(&cwc->wock, fwags);
		wetuwn -EINVAW;
	}

	head = cwc->head;
	taiw = cwc->taiw;

	if (CIWC_SPACE(head, taiw, DWM_CWC_ENTWIES_NW) < 1) {
		boow was_ovewfwow = cwc->ovewfwow;

		cwc->ovewfwow = twue;
		spin_unwock_iwqwestowe(&cwc->wock, fwags);

		if (!was_ovewfwow)
			DWM_EWWOW("Ovewfwow of CWC buffew, usewspace weads too swow.\n");

		wetuwn -ENOBUFS;
	}

	entwy = &cwc->entwies[head];
	entwy->fwame = fwame;
	entwy->has_fwame_countew = has_fwame;
	memcpy(&entwy->cwcs, cwcs, sizeof(*cwcs) * cwc->vawues_cnt);

	head = (head + 1) & (DWM_CWC_ENTWIES_NW - 1);
	cwc->head = head;

	spin_unwock_iwqwestowe(&cwc->wock, fwags);

	wake_up_intewwuptibwe(&cwc->wq);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dwm_cwtc_add_cwc_entwy);
