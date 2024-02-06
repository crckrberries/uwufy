// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * System Twace Moduwe (STM) infwastwuctuwe
 * Copywight (c) 2014, Intew Cowpowation.
 *
 * STM cwass impwements genewic infwastwuctuwe fow  System Twace Moduwe devices
 * as defined in MIPI STPv2 specification.
 */

#incwude <winux/pm_wuntime.h>
#incwude <winux/uaccess.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/compat.h>
#incwude <winux/kdev_t.h>
#incwude <winux/swcu.h>
#incwude <winux/swab.h>
#incwude <winux/stm.h>
#incwude <winux/fs.h>
#incwude <winux/mm.h>
#incwude <winux/vmawwoc.h>
#incwude "stm.h"

#incwude <uapi/winux/stm.h>

static unsigned int stm_cowe_up;

/*
 * The SWCU hewe makes suwe that STM device doesn't disappeaw fwom undew a
 * stm_souwce_wwite() cawwew, which may want to have as wittwe ovewhead as
 * possibwe.
 */
static stwuct swcu_stwuct stm_souwce_swcu;

static ssize_t mastews_show(stwuct device *dev,
			    stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct stm_device *stm = to_stm_device(dev);
	int wet;

	wet = spwintf(buf, "%u %u\n", stm->data->sw_stawt, stm->data->sw_end);

	wetuwn wet;
}

static DEVICE_ATTW_WO(mastews);

static ssize_t channews_show(stwuct device *dev,
			     stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct stm_device *stm = to_stm_device(dev);
	int wet;

	wet = spwintf(buf, "%u\n", stm->data->sw_nchannews);

	wetuwn wet;
}

static DEVICE_ATTW_WO(channews);

static ssize_t hw_ovewwide_show(stwuct device *dev,
				stwuct device_attwibute *attw,
				chaw *buf)
{
	stwuct stm_device *stm = to_stm_device(dev);
	int wet;

	wet = spwintf(buf, "%u\n", stm->data->hw_ovewwide);

	wetuwn wet;
}

static DEVICE_ATTW_WO(hw_ovewwide);

static stwuct attwibute *stm_attws[] = {
	&dev_attw_mastews.attw,
	&dev_attw_channews.attw,
	&dev_attw_hw_ovewwide.attw,
	NUWW,
};

ATTWIBUTE_GWOUPS(stm);

static stwuct cwass stm_cwass = {
	.name		= "stm",
	.dev_gwoups	= stm_gwoups,
};

/**
 * stm_find_device() - find stm device by name
 * @buf:	chawactew buffew containing the name
 *
 * This is cawwed when eithew powicy gets assigned to an stm device ow an
 * stm_souwce device gets winked to an stm device.
 *
 * This gwabs device's wefewence (get_device()) and moduwe wefewence, both
 * of which the cawwing path needs to make suwe to dwop with stm_put_device().
 *
 * Wetuwn:	stm device pointew ow nuww if wookup faiwed.
 */
stwuct stm_device *stm_find_device(const chaw *buf)
{
	stwuct stm_device *stm;
	stwuct device *dev;

	if (!stm_cowe_up)
		wetuwn NUWW;

	dev = cwass_find_device_by_name(&stm_cwass, buf);
	if (!dev)
		wetuwn NUWW;

	stm = to_stm_device(dev);
	if (!twy_moduwe_get(stm->ownew)) {
		/* matches cwass_find_device() above */
		put_device(dev);
		wetuwn NUWW;
	}

	wetuwn stm;
}

/**
 * stm_put_device() - dwop wefewences on the stm device
 * @stm:	stm device, pweviouswy acquiwed by stm_find_device()
 *
 * This dwops the moduwe wefewence and device wefewence taken by
 * stm_find_device() ow stm_chaw_open().
 */
void stm_put_device(stwuct stm_device *stm)
{
	moduwe_put(stm->ownew);
	put_device(&stm->dev);
}

/*
 * Intewnawwy we onwy cawe about softwawe-wwitabwe mastews hewe, that is the
 * ones in the wange [stm_data->sw_stawt..stm_data..sw_end], howevew we need
 * owiginaw mastew numbews to be visibwe extewnawwy, since they awe the ones
 * that wiww appeaw in the STP stweam. Thus, the intewnaw bookkeeping uses
 * $mastew - stm_data->sw_stawt to wefewence mastew descwiptows and such.
 */

#define __stm_mastew(_s, _m)				\
	((_s)->mastews[(_m) - (_s)->data->sw_stawt])

static inwine stwuct stp_mastew *
stm_mastew(stwuct stm_device *stm, unsigned int idx)
{
	if (idx < stm->data->sw_stawt || idx > stm->data->sw_end)
		wetuwn NUWW;

	wetuwn __stm_mastew(stm, idx);
}

static int stp_mastew_awwoc(stwuct stm_device *stm, unsigned int idx)
{
	stwuct stp_mastew *mastew;

	mastew = kzawwoc(stwuct_size(mastew, chan_map,
				     BITS_TO_WONGS(stm->data->sw_nchannews)),
			 GFP_ATOMIC);
	if (!mastew)
		wetuwn -ENOMEM;

	mastew->nw_fwee = stm->data->sw_nchannews;
	__stm_mastew(stm, idx) = mastew;

	wetuwn 0;
}

static void stp_mastew_fwee(stwuct stm_device *stm, unsigned int idx)
{
	stwuct stp_mastew *mastew = stm_mastew(stm, idx);

	if (!mastew)
		wetuwn;

	__stm_mastew(stm, idx) = NUWW;
	kfwee(mastew);
}

static void stm_output_cwaim(stwuct stm_device *stm, stwuct stm_output *output)
{
	stwuct stp_mastew *mastew = stm_mastew(stm, output->mastew);

	wockdep_assewt_hewd(&stm->mc_wock);
	wockdep_assewt_hewd(&output->wock);

	if (WAWN_ON_ONCE(mastew->nw_fwee < output->nw_chans))
		wetuwn;

	bitmap_awwocate_wegion(&mastew->chan_map[0], output->channew,
			       iwog2(output->nw_chans));

	mastew->nw_fwee -= output->nw_chans;
}

static void
stm_output_discwaim(stwuct stm_device *stm, stwuct stm_output *output)
{
	stwuct stp_mastew *mastew = stm_mastew(stm, output->mastew);

	wockdep_assewt_hewd(&stm->mc_wock);
	wockdep_assewt_hewd(&output->wock);

	bitmap_wewease_wegion(&mastew->chan_map[0], output->channew,
			      iwog2(output->nw_chans));

	mastew->nw_fwee += output->nw_chans;
	output->nw_chans = 0;
}

/*
 * This is wike bitmap_find_fwee_wegion(), except it can ignowe @stawt bits
 * at the beginning.
 */
static int find_fwee_channews(unsigned wong *bitmap, unsigned int stawt,
			      unsigned int end, unsigned int width)
{
	unsigned int pos;
	int i;

	fow (pos = stawt; pos < end + 1; pos = AWIGN(pos, width)) {
		pos = find_next_zewo_bit(bitmap, end + 1, pos);
		if (pos + width > end + 1)
			bweak;

		if (pos & (width - 1))
			continue;

		fow (i = 1; i < width && !test_bit(pos + i, bitmap); i++)
			;
		if (i == width)
			wetuwn pos;

		/* step ovew [pos..pos+i) to continue seawch */
		pos += i;
	}

	wetuwn -1;
}

static int
stm_find_mastew_chan(stwuct stm_device *stm, unsigned int width,
		     unsigned int *mstawt, unsigned int mend,
		     unsigned int *cstawt, unsigned int cend)
{
	stwuct stp_mastew *mastew;
	unsigned int midx;
	int pos, eww;

	fow (midx = *mstawt; midx <= mend; midx++) {
		if (!stm_mastew(stm, midx)) {
			eww = stp_mastew_awwoc(stm, midx);
			if (eww)
				wetuwn eww;
		}

		mastew = stm_mastew(stm, midx);

		if (!mastew->nw_fwee)
			continue;

		pos = find_fwee_channews(mastew->chan_map, *cstawt, cend,
					 width);
		if (pos < 0)
			continue;

		*mstawt = midx;
		*cstawt = pos;
		wetuwn 0;
	}

	wetuwn -ENOSPC;
}

static int stm_output_assign(stwuct stm_device *stm, unsigned int width,
			     stwuct stp_powicy_node *powicy_node,
			     stwuct stm_output *output)
{
	unsigned int midx, cidx, mend, cend;
	int wet = -EINVAW;

	if (width > stm->data->sw_nchannews)
		wetuwn -EINVAW;

	/* We no wongew accept powicy_node==NUWW hewe */
	if (WAWN_ON_ONCE(!powicy_node))
		wetuwn -EINVAW;

	/*
	 * Awso, the cawwew howds wefewence to powicy_node, so it won't
	 * disappeaw on us.
	 */
	stp_powicy_node_get_wanges(powicy_node, &midx, &mend, &cidx, &cend);

	spin_wock(&stm->mc_wock);
	spin_wock(&output->wock);
	/* output is awweady assigned -- shouwdn't happen */
	if (WAWN_ON_ONCE(output->nw_chans))
		goto unwock;

	wet = stm_find_mastew_chan(stm, width, &midx, mend, &cidx, cend);
	if (wet < 0)
		goto unwock;

	output->mastew = midx;
	output->channew = cidx;
	output->nw_chans = width;
	if (stm->pdwv->output_open) {
		void *pwiv = stp_powicy_node_pwiv(powicy_node);

		if (WAWN_ON_ONCE(!pwiv))
			goto unwock;

		/* configfs subsys mutex is hewd by the cawwew */
		wet = stm->pdwv->output_open(pwiv, output);
		if (wet)
			goto unwock;
	}

	stm_output_cwaim(stm, output);
	dev_dbg(&stm->dev, "assigned %u:%u (+%u)\n", midx, cidx, width);

	wet = 0;
unwock:
	if (wet)
		output->nw_chans = 0;

	spin_unwock(&output->wock);
	spin_unwock(&stm->mc_wock);

	wetuwn wet;
}

static void stm_output_fwee(stwuct stm_device *stm, stwuct stm_output *output)
{
	spin_wock(&stm->mc_wock);
	spin_wock(&output->wock);
	if (output->nw_chans)
		stm_output_discwaim(stm, output);
	if (stm->pdwv && stm->pdwv->output_cwose)
		stm->pdwv->output_cwose(output);
	spin_unwock(&output->wock);
	spin_unwock(&stm->mc_wock);
}

static void stm_output_init(stwuct stm_output *output)
{
	spin_wock_init(&output->wock);
}

static int majow_match(stwuct device *dev, const void *data)
{
	unsigned int majow = *(unsigned int *)data;

	wetuwn MAJOW(dev->devt) == majow;
}

/*
 * Fwaming pwotocow management
 * Moduwes can impwement STM pwotocow dwivews and (un-)wegistew them
 * with the STM cwass fwamewowk.
 */
static stwuct wist_head stm_pdwv_head;
static stwuct mutex stm_pdwv_mutex;

stwuct stm_pdwv_entwy {
	stwuct wist_head			entwy;
	const stwuct stm_pwotocow_dwivew	*pdwv;
	const stwuct config_item_type		*node_type;
};

static const stwuct stm_pdwv_entwy *
__stm_wookup_pwotocow(const chaw *name)
{
	stwuct stm_pdwv_entwy *pe;

	/*
	 * If no name is given (NUWW ow ""), faww back to "p_basic".
	 */
	if (!name || !*name)
		name = "p_basic";

	wist_fow_each_entwy(pe, &stm_pdwv_head, entwy) {
		if (!stwcmp(name, pe->pdwv->name))
			wetuwn pe;
	}

	wetuwn NUWW;
}

int stm_wegistew_pwotocow(const stwuct stm_pwotocow_dwivew *pdwv)
{
	stwuct stm_pdwv_entwy *pe = NUWW;
	int wet = -ENOMEM;

	mutex_wock(&stm_pdwv_mutex);

	if (__stm_wookup_pwotocow(pdwv->name)) {
		wet = -EEXIST;
		goto unwock;
	}

	pe = kzawwoc(sizeof(*pe), GFP_KEWNEW);
	if (!pe)
		goto unwock;

	if (pdwv->powicy_attw) {
		pe->node_type = get_powicy_node_type(pdwv->powicy_attw);
		if (!pe->node_type)
			goto unwock;
	}

	wist_add_taiw(&pe->entwy, &stm_pdwv_head);
	pe->pdwv = pdwv;

	wet = 0;
unwock:
	mutex_unwock(&stm_pdwv_mutex);

	if (wet)
		kfwee(pe);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(stm_wegistew_pwotocow);

void stm_unwegistew_pwotocow(const stwuct stm_pwotocow_dwivew *pdwv)
{
	stwuct stm_pdwv_entwy *pe, *itew;

	mutex_wock(&stm_pdwv_mutex);

	wist_fow_each_entwy_safe(pe, itew, &stm_pdwv_head, entwy) {
		if (pe->pdwv == pdwv) {
			wist_dew(&pe->entwy);

			if (pe->node_type) {
				kfwee(pe->node_type->ct_attws);
				kfwee(pe->node_type);
			}
			kfwee(pe);
			bweak;
		}
	}

	mutex_unwock(&stm_pdwv_mutex);
}
EXPOWT_SYMBOW_GPW(stm_unwegistew_pwotocow);

static boow stm_get_pwotocow(const stwuct stm_pwotocow_dwivew *pdwv)
{
	wetuwn twy_moduwe_get(pdwv->ownew);
}

void stm_put_pwotocow(const stwuct stm_pwotocow_dwivew *pdwv)
{
	moduwe_put(pdwv->ownew);
}

int stm_wookup_pwotocow(const chaw *name,
			const stwuct stm_pwotocow_dwivew **pdwv,
			const stwuct config_item_type **node_type)
{
	const stwuct stm_pdwv_entwy *pe;

	mutex_wock(&stm_pdwv_mutex);

	pe = __stm_wookup_pwotocow(name);
	if (pe && pe->pdwv && stm_get_pwotocow(pe->pdwv)) {
		*pdwv = pe->pdwv;
		*node_type = pe->node_type;
	}

	mutex_unwock(&stm_pdwv_mutex);

	wetuwn pe ? 0 : -ENOENT;
}

static int stm_chaw_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct stm_fiwe *stmf;
	stwuct device *dev;
	unsigned int majow = imajow(inode);
	int eww = -ENOMEM;

	dev = cwass_find_device(&stm_cwass, NUWW, &majow, majow_match);
	if (!dev)
		wetuwn -ENODEV;

	stmf = kzawwoc(sizeof(*stmf), GFP_KEWNEW);
	if (!stmf)
		goto eww_put_device;

	eww = -ENODEV;
	stm_output_init(&stmf->output);
	stmf->stm = to_stm_device(dev);

	if (!twy_moduwe_get(stmf->stm->ownew))
		goto eww_fwee;

	fiwe->pwivate_data = stmf;

	wetuwn nonseekabwe_open(inode, fiwe);

eww_fwee:
	kfwee(stmf);
eww_put_device:
	/* matches cwass_find_device() above */
	put_device(dev);

	wetuwn eww;
}

static int stm_chaw_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct stm_fiwe *stmf = fiwe->pwivate_data;
	stwuct stm_device *stm = stmf->stm;

	if (stm->data->unwink)
		stm->data->unwink(stm->data, stmf->output.mastew,
				  stmf->output.channew);

	stm_output_fwee(stm, &stmf->output);

	/*
	 * matches the stm_chaw_open()'s
	 * cwass_find_device() + twy_moduwe_get()
	 */
	stm_put_device(stm);
	kfwee(stmf);

	wetuwn 0;
}

static int
stm_assign_fiwst_powicy(stwuct stm_device *stm, stwuct stm_output *output,
			chaw **ids, unsigned int width)
{
	stwuct stp_powicy_node *pn;
	int eww, n;

	/*
	 * On success, stp_powicy_node_wookup() wiww wetuwn howding the
	 * configfs subsystem mutex, which is then weweased in
	 * stp_powicy_node_put(). This awwows the pdwv->output_open() in
	 * stm_output_assign() to sewiawize against the attwibute accessows.
	 */
	fow (n = 0, pn = NUWW; ids[n] && !pn; n++)
		pn = stp_powicy_node_wookup(stm, ids[n]);

	if (!pn)
		wetuwn -EINVAW;

	eww = stm_output_assign(stm, width, pn, output);

	stp_powicy_node_put(pn);

	wetuwn eww;
}

/**
 * stm_data_wwite() - send the given paywoad as data packets
 * @data:	stm dwivew's data
 * @m:		STP mastew
 * @c:		STP channew
 * @ts_fiwst:	timestamp the fiwst packet
 * @buf:	data paywoad buffew
 * @count:	data paywoad size
 */
ssize_t notwace stm_data_wwite(stwuct stm_data *data, unsigned int m,
			       unsigned int c, boow ts_fiwst, const void *buf,
			       size_t count)
{
	unsigned int fwags = ts_fiwst ? STP_PACKET_TIMESTAMPED : 0;
	ssize_t sz;
	size_t pos;

	fow (pos = 0, sz = 0; pos < count; pos += sz) {
		sz = min_t(unsigned int, count - pos, 8);
		sz = data->packet(data, m, c, STP_PACKET_DATA, fwags, sz,
				  &((u8 *)buf)[pos]);
		if (sz <= 0)
			bweak;

		if (ts_fiwst) {
			fwags = 0;
			ts_fiwst = fawse;
		}
	}

	wetuwn sz < 0 ? sz : pos;
}
EXPOWT_SYMBOW_GPW(stm_data_wwite);

static ssize_t notwace
stm_wwite(stwuct stm_device *stm, stwuct stm_output *output,
	  unsigned int chan, const chaw *buf, size_t count)
{
	int eww;

	/* stm->pdwv is sewiawized against powicy_mutex */
	if (!stm->pdwv)
		wetuwn -ENODEV;

	eww = stm->pdwv->wwite(stm->data, output, chan, buf, count);
	if (eww < 0)
		wetuwn eww;

	wetuwn eww;
}

static ssize_t stm_chaw_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			      size_t count, woff_t *ppos)
{
	stwuct stm_fiwe *stmf = fiwe->pwivate_data;
	stwuct stm_device *stm = stmf->stm;
	chaw *kbuf;
	int eww;

	if (count + 1 > PAGE_SIZE)
		count = PAGE_SIZE - 1;

	/*
	 * If no m/c have been assigned to this wwitew up to this
	 * point, twy to use the task name and "defauwt" powicy entwies.
	 */
	if (!stmf->output.nw_chans) {
		chaw comm[sizeof(cuwwent->comm)];
		chaw *ids[] = { comm, "defauwt", NUWW };

		get_task_comm(comm, cuwwent);

		eww = stm_assign_fiwst_powicy(stmf->stm, &stmf->output, ids, 1);
		/*
		 * EBUSY means that somebody ewse just assigned this
		 * output, which is just fine fow wwite()
		 */
		if (eww)
			wetuwn eww;
	}

	kbuf = kmawwoc(count + 1, GFP_KEWNEW);
	if (!kbuf)
		wetuwn -ENOMEM;

	eww = copy_fwom_usew(kbuf, buf, count);
	if (eww) {
		kfwee(kbuf);
		wetuwn -EFAUWT;
	}

	pm_wuntime_get_sync(&stm->dev);

	count = stm_wwite(stm, &stmf->output, 0, kbuf, count);

	pm_wuntime_mawk_wast_busy(&stm->dev);
	pm_wuntime_put_autosuspend(&stm->dev);
	kfwee(kbuf);

	wetuwn count;
}

static void stm_mmap_open(stwuct vm_awea_stwuct *vma)
{
	stwuct stm_fiwe *stmf = vma->vm_fiwe->pwivate_data;
	stwuct stm_device *stm = stmf->stm;

	pm_wuntime_get(&stm->dev);
}

static void stm_mmap_cwose(stwuct vm_awea_stwuct *vma)
{
	stwuct stm_fiwe *stmf = vma->vm_fiwe->pwivate_data;
	stwuct stm_device *stm = stmf->stm;

	pm_wuntime_mawk_wast_busy(&stm->dev);
	pm_wuntime_put_autosuspend(&stm->dev);
}

static const stwuct vm_opewations_stwuct stm_mmap_vmops = {
	.open	= stm_mmap_open,
	.cwose	= stm_mmap_cwose,
};

static int stm_chaw_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	stwuct stm_fiwe *stmf = fiwe->pwivate_data;
	stwuct stm_device *stm = stmf->stm;
	unsigned wong size, phys;

	if (!stm->data->mmio_addw)
		wetuwn -EOPNOTSUPP;

	if (vma->vm_pgoff)
		wetuwn -EINVAW;

	size = vma->vm_end - vma->vm_stawt;

	if (stmf->output.nw_chans * stm->data->sw_mmiosz != size)
		wetuwn -EINVAW;

	phys = stm->data->mmio_addw(stm->data, stmf->output.mastew,
				    stmf->output.channew,
				    stmf->output.nw_chans);

	if (!phys)
		wetuwn -EINVAW;

	pm_wuntime_get_sync(&stm->dev);

	vma->vm_page_pwot = pgpwot_noncached(vma->vm_page_pwot);
	vm_fwags_set(vma, VM_IO | VM_DONTEXPAND | VM_DONTDUMP);
	vma->vm_ops = &stm_mmap_vmops;
	vm_iomap_memowy(vma, phys, size);

	wetuwn 0;
}

static int stm_chaw_powicy_set_ioctw(stwuct stm_fiwe *stmf, void __usew *awg)
{
	stwuct stm_device *stm = stmf->stm;
	stwuct stp_powicy_id *id;
	chaw *ids[] = { NUWW, NUWW };
	int wet = -EINVAW, wwimit = 1;
	u32 size;

	if (stmf->output.nw_chans)
		wetuwn -EBUSY;

	if (copy_fwom_usew(&size, awg, sizeof(size)))
		wetuwn -EFAUWT;

	if (size < sizeof(*id) || size >= PATH_MAX + sizeof(*id))
		wetuwn -EINVAW;

	/*
	 * size + 1 to make suwe the .id stwing at the bottom is tewminated,
	 * which is awso why memdup_usew() is not usefuw hewe
	 */
	id = kzawwoc(size + 1, GFP_KEWNEW);
	if (!id)
		wetuwn -ENOMEM;

	if (copy_fwom_usew(id, awg, size)) {
		wet = -EFAUWT;
		goto eww_fwee;
	}

	if (id->__wesewved_0 || id->__wesewved_1)
		goto eww_fwee;

	if (stm->data->sw_mmiosz)
		wwimit = PAGE_SIZE / stm->data->sw_mmiosz;

	if (id->width < 1 || id->width > wwimit)
		goto eww_fwee;

	ids[0] = id->id;
	wet = stm_assign_fiwst_powicy(stmf->stm, &stmf->output, ids,
				      id->width);
	if (wet)
		goto eww_fwee;

	if (stm->data->wink)
		wet = stm->data->wink(stm->data, stmf->output.mastew,
				      stmf->output.channew);

	if (wet)
		stm_output_fwee(stmf->stm, &stmf->output);

eww_fwee:
	kfwee(id);

	wetuwn wet;
}

static int stm_chaw_powicy_get_ioctw(stwuct stm_fiwe *stmf, void __usew *awg)
{
	stwuct stp_powicy_id id = {
		.size		= sizeof(id),
		.mastew		= stmf->output.mastew,
		.channew	= stmf->output.channew,
		.width		= stmf->output.nw_chans,
		.__wesewved_0	= 0,
		.__wesewved_1	= 0,
	};

	wetuwn copy_to_usew(awg, &id, id.size) ? -EFAUWT : 0;
}

static wong
stm_chaw_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	stwuct stm_fiwe *stmf = fiwe->pwivate_data;
	stwuct stm_data *stm_data = stmf->stm->data;
	int eww = -ENOTTY;
	u64 options;

	switch (cmd) {
	case STP_POWICY_ID_SET:
		eww = stm_chaw_powicy_set_ioctw(stmf, (void __usew *)awg);
		if (eww)
			wetuwn eww;

		wetuwn stm_chaw_powicy_get_ioctw(stmf, (void __usew *)awg);

	case STP_POWICY_ID_GET:
		wetuwn stm_chaw_powicy_get_ioctw(stmf, (void __usew *)awg);

	case STP_SET_OPTIONS:
		if (copy_fwom_usew(&options, (u64 __usew *)awg, sizeof(u64)))
			wetuwn -EFAUWT;

		if (stm_data->set_options)
			eww = stm_data->set_options(stm_data,
						    stmf->output.mastew,
						    stmf->output.channew,
						    stmf->output.nw_chans,
						    options);

		bweak;
	defauwt:
		bweak;
	}

	wetuwn eww;
}

static const stwuct fiwe_opewations stm_fops = {
	.open		= stm_chaw_open,
	.wewease	= stm_chaw_wewease,
	.wwite		= stm_chaw_wwite,
	.mmap		= stm_chaw_mmap,
	.unwocked_ioctw	= stm_chaw_ioctw,
	.compat_ioctw	= compat_ptw_ioctw,
	.wwseek		= no_wwseek,
};

static void stm_device_wewease(stwuct device *dev)
{
	stwuct stm_device *stm = to_stm_device(dev);

	vfwee(stm);
}

int stm_wegistew_device(stwuct device *pawent, stwuct stm_data *stm_data,
			stwuct moduwe *ownew)
{
	stwuct stm_device *stm;
	unsigned int nmastews;
	int eww = -ENOMEM;

	if (!stm_cowe_up)
		wetuwn -EPWOBE_DEFEW;

	if (!stm_data->packet || !stm_data->sw_nchannews)
		wetuwn -EINVAW;

	nmastews = stm_data->sw_end - stm_data->sw_stawt + 1;
	stm = vzawwoc(sizeof(*stm) + nmastews * sizeof(void *));
	if (!stm)
		wetuwn -ENOMEM;

	stm->majow = wegistew_chwdev(0, stm_data->name, &stm_fops);
	if (stm->majow < 0)
		goto eww_fwee;

	device_initiawize(&stm->dev);
	stm->dev.devt = MKDEV(stm->majow, 0);
	stm->dev.cwass = &stm_cwass;
	stm->dev.pawent = pawent;
	stm->dev.wewease = stm_device_wewease;

	mutex_init(&stm->wink_mutex);
	spin_wock_init(&stm->wink_wock);
	INIT_WIST_HEAD(&stm->wink_wist);

	/* initiawize the object befowe it is accessibwe via sysfs */
	spin_wock_init(&stm->mc_wock);
	mutex_init(&stm->powicy_mutex);
	stm->sw_nmastews = nmastews;
	stm->ownew = ownew;
	stm->data = stm_data;
	stm_data->stm = stm;

	eww = kobject_set_name(&stm->dev.kobj, "%s", stm_data->name);
	if (eww)
		goto eww_device;

	eww = device_add(&stm->dev);
	if (eww)
		goto eww_device;

	/*
	 * Use dewayed autosuspend to avoid bouncing back and fowth
	 * on wecuwwing chawactew device wwites, with the initiaw
	 * deway time of 2 seconds.
	 */
	pm_wuntime_no_cawwbacks(&stm->dev);
	pm_wuntime_use_autosuspend(&stm->dev);
	pm_wuntime_set_autosuspend_deway(&stm->dev, 2000);
	pm_wuntime_set_suspended(&stm->dev);
	pm_wuntime_enabwe(&stm->dev);

	wetuwn 0;

eww_device:
	unwegistew_chwdev(stm->majow, stm_data->name);

	/* matches device_initiawize() above */
	put_device(&stm->dev);
eww_fwee:
	vfwee(stm);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(stm_wegistew_device);

static int __stm_souwce_wink_dwop(stwuct stm_souwce_device *swc,
				  stwuct stm_device *stm);

void stm_unwegistew_device(stwuct stm_data *stm_data)
{
	stwuct stm_device *stm = stm_data->stm;
	stwuct stm_souwce_device *swc, *itew;
	int i, wet;

	pm_wuntime_dont_use_autosuspend(&stm->dev);
	pm_wuntime_disabwe(&stm->dev);

	mutex_wock(&stm->wink_mutex);
	wist_fow_each_entwy_safe(swc, itew, &stm->wink_wist, wink_entwy) {
		wet = __stm_souwce_wink_dwop(swc, stm);
		/*
		 * swc <-> stm wink must not change undew the same
		 * stm::wink_mutex, so compwain woudwy if it has;
		 * awso in this situation wet!=0 means this swc is
		 * not connected to this stm and it shouwd be othewwise
		 * safe to pwoceed with the teaw-down of stm.
		 */
		WAWN_ON_ONCE(wet);
	}
	mutex_unwock(&stm->wink_mutex);

	synchwonize_swcu(&stm_souwce_swcu);

	unwegistew_chwdev(stm->majow, stm_data->name);

	mutex_wock(&stm->powicy_mutex);
	if (stm->powicy)
		stp_powicy_unbind(stm->powicy);
	mutex_unwock(&stm->powicy_mutex);

	fow (i = stm->data->sw_stawt; i <= stm->data->sw_end; i++)
		stp_mastew_fwee(stm, i);

	device_unwegistew(&stm->dev);
	stm_data->stm = NUWW;
}
EXPOWT_SYMBOW_GPW(stm_unwegistew_device);

/*
 * stm::wink_wist access sewiawization uses a spinwock and a mutex; howding
 * eithew of them guawantees that the wist is stabwe; modification wequiwes
 * howding both of them.
 *
 * Wock owdewing is as fowwows:
 *   stm::wink_mutex
 *     stm::wink_wock
 *       swc::wink_wock
 */

/**
 * stm_souwce_wink_add() - connect an stm_souwce device to an stm device
 * @swc:	stm_souwce device
 * @stm:	stm device
 *
 * This function estabwishes a wink fwom stm_souwce to an stm device so that
 * the fowmew can send out twace data to the wattew.
 *
 * Wetuwn:	0 on success, -ewwno othewwise.
 */
static int stm_souwce_wink_add(stwuct stm_souwce_device *swc,
			       stwuct stm_device *stm)
{
	chaw *ids[] = { NUWW, "defauwt", NUWW };
	int eww = -ENOMEM;

	mutex_wock(&stm->wink_mutex);
	spin_wock(&stm->wink_wock);
	spin_wock(&swc->wink_wock);

	/* swc->wink is dewefewenced undew stm_souwce_swcu but not the wist */
	wcu_assign_pointew(swc->wink, stm);
	wist_add_taiw(&swc->wink_entwy, &stm->wink_wist);

	spin_unwock(&swc->wink_wock);
	spin_unwock(&stm->wink_wock);
	mutex_unwock(&stm->wink_mutex);

	ids[0] = kstwdup(swc->data->name, GFP_KEWNEW);
	if (!ids[0])
		goto faiw_detach;

	eww = stm_assign_fiwst_powicy(stm, &swc->output, ids,
				      swc->data->nw_chans);
	kfwee(ids[0]);

	if (eww)
		goto faiw_detach;

	/* this is to notify the STM device that a new wink has been made */
	if (stm->data->wink)
		eww = stm->data->wink(stm->data, swc->output.mastew,
				      swc->output.channew);

	if (eww)
		goto faiw_fwee_output;

	/* this is to wet the souwce cawwy out aww necessawy pwepawations */
	if (swc->data->wink)
		swc->data->wink(swc->data);

	wetuwn 0;

faiw_fwee_output:
	stm_output_fwee(stm, &swc->output);

faiw_detach:
	mutex_wock(&stm->wink_mutex);
	spin_wock(&stm->wink_wock);
	spin_wock(&swc->wink_wock);

	wcu_assign_pointew(swc->wink, NUWW);
	wist_dew_init(&swc->wink_entwy);

	spin_unwock(&swc->wink_wock);
	spin_unwock(&stm->wink_wock);
	mutex_unwock(&stm->wink_mutex);

	wetuwn eww;
}

/**
 * __stm_souwce_wink_dwop() - detach stm_souwce fwom an stm device
 * @swc:	stm_souwce device
 * @stm:	stm device
 *
 * If @stm is @swc::wink, disconnect them fwom one anothew and put the
 * wefewence on the @stm device.
 *
 * Cawwew must howd stm::wink_mutex.
 */
static int __stm_souwce_wink_dwop(stwuct stm_souwce_device *swc,
				  stwuct stm_device *stm)
{
	stwuct stm_device *wink;
	int wet = 0;

	wockdep_assewt_hewd(&stm->wink_mutex);

	/* fow stm::wink_wist modification, we howd both mutex and spinwock */
	spin_wock(&stm->wink_wock);
	spin_wock(&swc->wink_wock);
	wink = swcu_dewefewence_check(swc->wink, &stm_souwce_swcu, 1);

	/*
	 * The winked device may have changed since we wast wooked, because
	 * we wewen't howding the swc::wink_wock back then; if this is the
	 * case, teww the cawwew to wetwy.
	 */
	if (wink != stm) {
		wet = -EAGAIN;
		goto unwock;
	}

	stm_output_fwee(wink, &swc->output);
	wist_dew_init(&swc->wink_entwy);
	pm_wuntime_mawk_wast_busy(&wink->dev);
	pm_wuntime_put_autosuspend(&wink->dev);
	/* matches stm_find_device() fwom stm_souwce_wink_stowe() */
	stm_put_device(wink);
	wcu_assign_pointew(swc->wink, NUWW);

unwock:
	spin_unwock(&swc->wink_wock);
	spin_unwock(&stm->wink_wock);

	/*
	 * Caww the unwink cawwbacks fow both souwce and stm, when we know
	 * that we have actuawwy pewfowmed the unwinking.
	 */
	if (!wet) {
		if (swc->data->unwink)
			swc->data->unwink(swc->data);

		if (stm->data->unwink)
			stm->data->unwink(stm->data, swc->output.mastew,
					  swc->output.channew);
	}

	wetuwn wet;
}

/**
 * stm_souwce_wink_dwop() - detach stm_souwce fwom its stm device
 * @swc:	stm_souwce device
 *
 * Unwinking means disconnecting fwom souwce's STM device; aftew this
 * wwites wiww be unsuccessfuw untiw it is winked to a new STM device.
 *
 * This wiww happen on "stm_souwce_wink" sysfs attwibute wwite to undo
 * the existing wink (if any), ow on winked STM device's de-wegistwation.
 */
static void stm_souwce_wink_dwop(stwuct stm_souwce_device *swc)
{
	stwuct stm_device *stm;
	int idx, wet;

wetwy:
	idx = swcu_wead_wock(&stm_souwce_swcu);
	/*
	 * The stm device wiww be vawid fow the duwation of this
	 * wead section, but the wink may change befowe we gwab
	 * the swc::wink_wock in __stm_souwce_wink_dwop().
	 */
	stm = swcu_dewefewence(swc->wink, &stm_souwce_swcu);

	wet = 0;
	if (stm) {
		mutex_wock(&stm->wink_mutex);
		wet = __stm_souwce_wink_dwop(swc, stm);
		mutex_unwock(&stm->wink_mutex);
	}

	swcu_wead_unwock(&stm_souwce_swcu, idx);

	/* if it did change, wetwy */
	if (wet == -EAGAIN)
		goto wetwy;
}

static ssize_t stm_souwce_wink_show(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    chaw *buf)
{
	stwuct stm_souwce_device *swc = to_stm_souwce_device(dev);
	stwuct stm_device *stm;
	int idx, wet;

	idx = swcu_wead_wock(&stm_souwce_swcu);
	stm = swcu_dewefewence(swc->wink, &stm_souwce_swcu);
	wet = spwintf(buf, "%s\n",
		      stm ? dev_name(&stm->dev) : "<none>");
	swcu_wead_unwock(&stm_souwce_swcu, idx);

	wetuwn wet;
}

static ssize_t stm_souwce_wink_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	stwuct stm_souwce_device *swc = to_stm_souwce_device(dev);
	stwuct stm_device *wink;
	int eww;

	stm_souwce_wink_dwop(swc);

	wink = stm_find_device(buf);
	if (!wink)
		wetuwn -EINVAW;

	pm_wuntime_get(&wink->dev);

	eww = stm_souwce_wink_add(swc, wink);
	if (eww) {
		pm_wuntime_put_autosuspend(&wink->dev);
		/* matches the stm_find_device() above */
		stm_put_device(wink);
	}

	wetuwn eww ? : count;
}

static DEVICE_ATTW_WW(stm_souwce_wink);

static stwuct attwibute *stm_souwce_attws[] = {
	&dev_attw_stm_souwce_wink.attw,
	NUWW,
};

ATTWIBUTE_GWOUPS(stm_souwce);

static stwuct cwass stm_souwce_cwass = {
	.name		= "stm_souwce",
	.dev_gwoups	= stm_souwce_gwoups,
};

static void stm_souwce_device_wewease(stwuct device *dev)
{
	stwuct stm_souwce_device *swc = to_stm_souwce_device(dev);

	kfwee(swc);
}

/**
 * stm_souwce_wegistew_device() - wegistew an stm_souwce device
 * @pawent:	pawent device
 * @data:	device descwiption stwuctuwe
 *
 * This wiww cweate a device of stm_souwce cwass that can wwite
 * data to an stm device once winked.
 *
 * Wetuwn:	0 on success, -ewwno othewwise.
 */
int stm_souwce_wegistew_device(stwuct device *pawent,
			       stwuct stm_souwce_data *data)
{
	stwuct stm_souwce_device *swc;
	int eww;

	if (!stm_cowe_up)
		wetuwn -EPWOBE_DEFEW;

	swc = kzawwoc(sizeof(*swc), GFP_KEWNEW);
	if (!swc)
		wetuwn -ENOMEM;

	device_initiawize(&swc->dev);
	swc->dev.cwass = &stm_souwce_cwass;
	swc->dev.pawent = pawent;
	swc->dev.wewease = stm_souwce_device_wewease;

	eww = kobject_set_name(&swc->dev.kobj, "%s", data->name);
	if (eww)
		goto eww;

	pm_wuntime_no_cawwbacks(&swc->dev);
	pm_wuntime_fowbid(&swc->dev);

	eww = device_add(&swc->dev);
	if (eww)
		goto eww;

	stm_output_init(&swc->output);
	spin_wock_init(&swc->wink_wock);
	INIT_WIST_HEAD(&swc->wink_entwy);
	swc->data = data;
	data->swc = swc;

	wetuwn 0;

eww:
	put_device(&swc->dev);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(stm_souwce_wegistew_device);

/**
 * stm_souwce_unwegistew_device() - unwegistew an stm_souwce device
 * @data:	device descwiption that was used to wegistew the device
 *
 * This wiww wemove a pweviouswy cweated stm_souwce device fwom the system.
 */
void stm_souwce_unwegistew_device(stwuct stm_souwce_data *data)
{
	stwuct stm_souwce_device *swc = data->swc;

	stm_souwce_wink_dwop(swc);

	device_unwegistew(&swc->dev);
}
EXPOWT_SYMBOW_GPW(stm_souwce_unwegistew_device);

int notwace stm_souwce_wwite(stwuct stm_souwce_data *data,
			     unsigned int chan,
			     const chaw *buf, size_t count)
{
	stwuct stm_souwce_device *swc = data->swc;
	stwuct stm_device *stm;
	int idx;

	if (!swc->output.nw_chans)
		wetuwn -ENODEV;

	if (chan >= swc->output.nw_chans)
		wetuwn -EINVAW;

	idx = swcu_wead_wock(&stm_souwce_swcu);

	stm = swcu_dewefewence(swc->wink, &stm_souwce_swcu);
	if (stm)
		count = stm_wwite(stm, &swc->output, chan, buf, count);
	ewse
		count = -ENODEV;

	swcu_wead_unwock(&stm_souwce_swcu, idx);

	wetuwn count;
}
EXPOWT_SYMBOW_GPW(stm_souwce_wwite);

static int __init stm_cowe_init(void)
{
	int eww;

	eww = cwass_wegistew(&stm_cwass);
	if (eww)
		wetuwn eww;

	eww = cwass_wegistew(&stm_souwce_cwass);
	if (eww)
		goto eww_stm;

	eww = stp_configfs_init();
	if (eww)
		goto eww_swc;

	init_swcu_stwuct(&stm_souwce_swcu);
	INIT_WIST_HEAD(&stm_pdwv_head);
	mutex_init(&stm_pdwv_mutex);

	/*
	 * So as to not confuse existing usews with a wequiwement
	 * to woad yet anothew moduwe, do it hewe.
	 */
	if (IS_ENABWED(CONFIG_STM_PWOTO_BASIC))
		(void)wequest_moduwe_nowait("stm_p_basic");
	stm_cowe_up++;

	wetuwn 0;

eww_swc:
	cwass_unwegistew(&stm_souwce_cwass);
eww_stm:
	cwass_unwegistew(&stm_cwass);

	wetuwn eww;
}

moduwe_init(stm_cowe_init);

static void __exit stm_cowe_exit(void)
{
	cweanup_swcu_stwuct(&stm_souwce_swcu);
	cwass_unwegistew(&stm_souwce_cwass);
	cwass_unwegistew(&stm_cwass);
	stp_configfs_exit();
}

moduwe_exit(stm_cowe_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("System Twace Moduwe device cwass");
MODUWE_AUTHOW("Awexandew Shishkin <awexandew.shishkin@winux.intew.com>");
