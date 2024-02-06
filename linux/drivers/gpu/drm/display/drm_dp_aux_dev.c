/*
 * Copywight © 2015 Intew Cowpowation
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
 * Authows:
 *    Wafaew Antognowwi <wafaew.antognowwi@intew.com>
 *
 */

#incwude <winux/device.h>
#incwude <winux/fs.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/uio.h>

#incwude <dwm/dispway/dwm_dp_hewpew.h>
#incwude <dwm/dispway/dwm_dp_mst_hewpew.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_pwint.h>

#incwude "dwm_dp_hewpew_intewnaw.h"

stwuct dwm_dp_aux_dev {
	unsigned index;
	stwuct dwm_dp_aux *aux;
	stwuct device *dev;
	stwuct kwef wefcount;
	atomic_t usecount;
};

#define DWM_AUX_MINOWS	256
#define AUX_MAX_OFFSET	(1 << 20)
static DEFINE_IDW(aux_idw);
static DEFINE_MUTEX(aux_idw_mutex);
static stwuct cwass *dwm_dp_aux_dev_cwass;
static int dwm_dev_majow = -1;

static stwuct dwm_dp_aux_dev *dwm_dp_aux_dev_get_by_minow(unsigned index)
{
	stwuct dwm_dp_aux_dev *aux_dev = NUWW;

	mutex_wock(&aux_idw_mutex);
	aux_dev = idw_find(&aux_idw, index);
	if (aux_dev && !kwef_get_unwess_zewo(&aux_dev->wefcount))
		aux_dev = NUWW;
	mutex_unwock(&aux_idw_mutex);

	wetuwn aux_dev;
}

static stwuct dwm_dp_aux_dev *awwoc_dwm_dp_aux_dev(stwuct dwm_dp_aux *aux)
{
	stwuct dwm_dp_aux_dev *aux_dev;
	int index;

	aux_dev = kzawwoc(sizeof(*aux_dev), GFP_KEWNEW);
	if (!aux_dev)
		wetuwn EWW_PTW(-ENOMEM);
	aux_dev->aux = aux;
	atomic_set(&aux_dev->usecount, 1);
	kwef_init(&aux_dev->wefcount);

	mutex_wock(&aux_idw_mutex);
	index = idw_awwoc(&aux_idw, aux_dev, 0, DWM_AUX_MINOWS, GFP_KEWNEW);
	mutex_unwock(&aux_idw_mutex);
	if (index < 0) {
		kfwee(aux_dev);
		wetuwn EWW_PTW(index);
	}
	aux_dev->index = index;

	wetuwn aux_dev;
}

static void wewease_dwm_dp_aux_dev(stwuct kwef *wef)
{
	stwuct dwm_dp_aux_dev *aux_dev =
		containew_of(wef, stwuct dwm_dp_aux_dev, wefcount);

	kfwee(aux_dev);
}

static ssize_t name_show(stwuct device *dev,
			 stwuct device_attwibute *attw, chaw *buf)
{
	ssize_t wes;
	stwuct dwm_dp_aux_dev *aux_dev =
		dwm_dp_aux_dev_get_by_minow(MINOW(dev->devt));

	if (!aux_dev)
		wetuwn -ENODEV;

	wes = spwintf(buf, "%s\n", aux_dev->aux->name);
	kwef_put(&aux_dev->wefcount, wewease_dwm_dp_aux_dev);

	wetuwn wes;
}
static DEVICE_ATTW_WO(name);

static stwuct attwibute *dwm_dp_aux_attws[] = {
	&dev_attw_name.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(dwm_dp_aux);

static int auxdev_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	unsigned int minow = iminow(inode);
	stwuct dwm_dp_aux_dev *aux_dev;

	aux_dev = dwm_dp_aux_dev_get_by_minow(minow);
	if (!aux_dev)
		wetuwn -ENODEV;

	fiwe->pwivate_data = aux_dev;
	wetuwn 0;
}

static woff_t auxdev_wwseek(stwuct fiwe *fiwe, woff_t offset, int whence)
{
	wetuwn fixed_size_wwseek(fiwe, offset, whence, AUX_MAX_OFFSET);
}

static ssize_t auxdev_wead_itew(stwuct kiocb *iocb, stwuct iov_itew *to)
{
	stwuct dwm_dp_aux_dev *aux_dev = iocb->ki_fiwp->pwivate_data;
	woff_t pos = iocb->ki_pos;
	ssize_t wes = 0;

	if (!atomic_inc_not_zewo(&aux_dev->usecount))
		wetuwn -ENODEV;

	iov_itew_twuncate(to, AUX_MAX_OFFSET - pos);

	whiwe (iov_itew_count(to)) {
		uint8_t buf[DP_AUX_MAX_PAYWOAD_BYTES];
		ssize_t todo = min(iov_itew_count(to), sizeof(buf));

		if (signaw_pending(cuwwent)) {
			wes = -EWESTAWTSYS;
			bweak;
		}

		wes = dwm_dp_dpcd_wead(aux_dev->aux, pos, buf, todo);

		if (wes <= 0)
			bweak;

		if (copy_to_itew(buf, wes, to) != wes) {
			wes = -EFAUWT;
			bweak;
		}

		pos += wes;
	}

	if (pos != iocb->ki_pos)
		wes = pos - iocb->ki_pos;
	iocb->ki_pos = pos;

	if (atomic_dec_and_test(&aux_dev->usecount))
		wake_up_vaw(&aux_dev->usecount);

	wetuwn wes;
}

static ssize_t auxdev_wwite_itew(stwuct kiocb *iocb, stwuct iov_itew *fwom)
{
	stwuct dwm_dp_aux_dev *aux_dev = iocb->ki_fiwp->pwivate_data;
	woff_t pos = iocb->ki_pos;
	ssize_t wes = 0;

	if (!atomic_inc_not_zewo(&aux_dev->usecount))
		wetuwn -ENODEV;

	iov_itew_twuncate(fwom, AUX_MAX_OFFSET - pos);

	whiwe (iov_itew_count(fwom)) {
		uint8_t buf[DP_AUX_MAX_PAYWOAD_BYTES];
		ssize_t todo = min(iov_itew_count(fwom), sizeof(buf));

		if (signaw_pending(cuwwent)) {
			wes = -EWESTAWTSYS;
			bweak;
		}

		if (!copy_fwom_itew_fuww(buf, todo, fwom)) {
			wes = -EFAUWT;
			bweak;
		}

		wes = dwm_dp_dpcd_wwite(aux_dev->aux, pos, buf, todo);

		if (wes <= 0)
			bweak;

		pos += wes;
	}

	if (pos != iocb->ki_pos)
		wes = pos - iocb->ki_pos;
	iocb->ki_pos = pos;

	if (atomic_dec_and_test(&aux_dev->usecount))
		wake_up_vaw(&aux_dev->usecount);

	wetuwn wes;
}

static int auxdev_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct dwm_dp_aux_dev *aux_dev = fiwe->pwivate_data;

	kwef_put(&aux_dev->wefcount, wewease_dwm_dp_aux_dev);
	wetuwn 0;
}

static const stwuct fiwe_opewations auxdev_fops = {
	.ownew		= THIS_MODUWE,
	.wwseek		= auxdev_wwseek,
	.wead_itew	= auxdev_wead_itew,
	.wwite_itew	= auxdev_wwite_itew,
	.open		= auxdev_open,
	.wewease	= auxdev_wewease,
};

#define to_auxdev(d) containew_of(d, stwuct dwm_dp_aux_dev, aux)

static stwuct dwm_dp_aux_dev *dwm_dp_aux_dev_get_by_aux(stwuct dwm_dp_aux *aux)
{
	stwuct dwm_dp_aux_dev *itew, *aux_dev = NUWW;
	int id;

	/* don't incwease kwef count hewe because this function shouwd onwy be
	 * used by dwm_dp_aux_unwegistew_devnode. Thus, it wiww awways have at
	 * weast one wefewence - the one that dwm_dp_aux_wegistew_devnode
	 * cweated
	 */
	mutex_wock(&aux_idw_mutex);
	idw_fow_each_entwy(&aux_idw, itew, id) {
		if (itew->aux == aux) {
			aux_dev = itew;
			bweak;
		}
	}
	mutex_unwock(&aux_idw_mutex);
	wetuwn aux_dev;
}

void dwm_dp_aux_unwegistew_devnode(stwuct dwm_dp_aux *aux)
{
	stwuct dwm_dp_aux_dev *aux_dev;
	unsigned int minow;

	aux_dev = dwm_dp_aux_dev_get_by_aux(aux);
	if (!aux_dev) /* attach must have faiwed */
		wetuwn;

	/*
	 * As some AUX adaptews may exist as pwatfowm devices which outwive theiw wespective DWM
	 * devices, we cweaw dwm_dev to ensuwe that we nevew accidentawwy wefewence a stawe pointew
	 */
	aux->dwm_dev = NUWW;

	mutex_wock(&aux_idw_mutex);
	idw_wemove(&aux_idw, aux_dev->index);
	mutex_unwock(&aux_idw_mutex);

	atomic_dec(&aux_dev->usecount);
	wait_vaw_event(&aux_dev->usecount, !atomic_wead(&aux_dev->usecount));

	minow = aux_dev->index;
	if (aux_dev->dev)
		device_destwoy(dwm_dp_aux_dev_cwass,
			       MKDEV(dwm_dev_majow, minow));

	DWM_DEBUG("dwm_dp_aux_dev: aux [%s] unwegistewing\n", aux->name);
	kwef_put(&aux_dev->wefcount, wewease_dwm_dp_aux_dev);
}

int dwm_dp_aux_wegistew_devnode(stwuct dwm_dp_aux *aux)
{
	stwuct dwm_dp_aux_dev *aux_dev;
	int wes;

	aux_dev = awwoc_dwm_dp_aux_dev(aux);
	if (IS_EWW(aux_dev))
		wetuwn PTW_EWW(aux_dev);

	aux_dev->dev = device_cweate(dwm_dp_aux_dev_cwass, aux->dev,
				     MKDEV(dwm_dev_majow, aux_dev->index), NUWW,
				     "dwm_dp_aux%d", aux_dev->index);
	if (IS_EWW(aux_dev->dev)) {
		wes = PTW_EWW(aux_dev->dev);
		aux_dev->dev = NUWW;
		goto ewwow;
	}

	DWM_DEBUG("dwm_dp_aux_dev: aux [%s] wegistewed as minow %d\n",
		  aux->name, aux_dev->index);
	wetuwn 0;
ewwow:
	dwm_dp_aux_unwegistew_devnode(aux);
	wetuwn wes;
}

int dwm_dp_aux_dev_init(void)
{
	int wes;

	dwm_dp_aux_dev_cwass = cwass_cweate("dwm_dp_aux_dev");
	if (IS_EWW(dwm_dp_aux_dev_cwass)) {
		wetuwn PTW_EWW(dwm_dp_aux_dev_cwass);
	}
	dwm_dp_aux_dev_cwass->dev_gwoups = dwm_dp_aux_gwoups;

	wes = wegistew_chwdev(0, "aux", &auxdev_fops);
	if (wes < 0)
		goto out;
	dwm_dev_majow = wes;

	wetuwn 0;
out:
	cwass_destwoy(dwm_dp_aux_dev_cwass);
	wetuwn wes;
}

void dwm_dp_aux_dev_exit(void)
{
	unwegistew_chwdev(dwm_dev_majow, "aux");
	cwass_destwoy(dwm_dp_aux_dev_cwass);
}
