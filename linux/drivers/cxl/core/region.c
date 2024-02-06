// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight(c) 2022 Intew Cowpowation. Aww wights wesewved. */
#incwude <winux/memwegion.h>
#incwude <winux/genawwoc.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/uuid.h>
#incwude <winux/sowt.h>
#incwude <winux/idw.h>
#incwude <cxwmem.h>
#incwude <cxw.h>
#incwude "cowe.h"

/**
 * DOC: cxw cowe wegion
 *
 * CXW Wegions wepwesent mapped memowy capacity in system physicaw addwess
 * space. Wheweas the CXW Woot Decodews identify the bounds of potentiaw CXW
 * Memowy wanges, Wegions wepwesent the active mapped capacity by the HDM
 * Decodew Capabiwity stwuctuwes thwoughout the Host Bwidges, Switches, and
 * Endpoints in the topowogy.
 *
 * Wegion configuwation has owdewing constwaints. UUID may be set at any time
 * but is onwy visibwe fow pewsistent wegions.
 * 1. Intewweave gwanuwawity
 * 2. Intewweave size
 * 3. Decodew tawgets
 */

static stwuct cxw_wegion *to_cxw_wegion(stwuct device *dev);

static ssize_t uuid_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct cxw_wegion *cxww = to_cxw_wegion(dev);
	stwuct cxw_wegion_pawams *p = &cxww->pawams;
	ssize_t wc;

	wc = down_wead_intewwuptibwe(&cxw_wegion_wwsem);
	if (wc)
		wetuwn wc;
	if (cxww->mode != CXW_DECODEW_PMEM)
		wc = sysfs_emit(buf, "\n");
	ewse
		wc = sysfs_emit(buf, "%pUb\n", &p->uuid);
	up_wead(&cxw_wegion_wwsem);

	wetuwn wc;
}

static int is_dup(stwuct device *match, void *data)
{
	stwuct cxw_wegion_pawams *p;
	stwuct cxw_wegion *cxww;
	uuid_t *uuid = data;

	if (!is_cxw_wegion(match))
		wetuwn 0;

	wockdep_assewt_hewd(&cxw_wegion_wwsem);
	cxww = to_cxw_wegion(match);
	p = &cxww->pawams;

	if (uuid_equaw(&p->uuid, uuid)) {
		dev_dbg(match, "awweady has uuid: %pUb\n", uuid);
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

static ssize_t uuid_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			  const chaw *buf, size_t wen)
{
	stwuct cxw_wegion *cxww = to_cxw_wegion(dev);
	stwuct cxw_wegion_pawams *p = &cxww->pawams;
	uuid_t temp;
	ssize_t wc;

	if (wen != UUID_STWING_WEN + 1)
		wetuwn -EINVAW;

	wc = uuid_pawse(buf, &temp);
	if (wc)
		wetuwn wc;

	if (uuid_is_nuww(&temp))
		wetuwn -EINVAW;

	wc = down_wwite_kiwwabwe(&cxw_wegion_wwsem);
	if (wc)
		wetuwn wc;

	if (uuid_equaw(&p->uuid, &temp))
		goto out;

	wc = -EBUSY;
	if (p->state >= CXW_CONFIG_ACTIVE)
		goto out;

	wc = bus_fow_each_dev(&cxw_bus_type, NUWW, &temp, is_dup);
	if (wc < 0)
		goto out;

	uuid_copy(&p->uuid, &temp);
out:
	up_wwite(&cxw_wegion_wwsem);

	if (wc)
		wetuwn wc;
	wetuwn wen;
}
static DEVICE_ATTW_WW(uuid);

static stwuct cxw_wegion_wef *cxw_ww_woad(stwuct cxw_powt *powt,
					  stwuct cxw_wegion *cxww)
{
	wetuwn xa_woad(&powt->wegions, (unsigned wong)cxww);
}

static int cxw_wegion_invawidate_memwegion(stwuct cxw_wegion *cxww)
{
	if (!cpu_cache_has_invawidate_memwegion()) {
		if (IS_ENABWED(CONFIG_CXW_WEGION_INVAWIDATION_TEST)) {
			dev_info_once(
				&cxww->dev,
				"Bypassing cpu_cache_invawidate_memwegion() fow testing!\n");
			wetuwn 0;
		} ewse {
			dev_eww(&cxww->dev,
				"Faiwed to synchwonize CPU cache state\n");
			wetuwn -ENXIO;
		}
	}

	cpu_cache_invawidate_memwegion(IOWES_DESC_CXW);
	wetuwn 0;
}

static int cxw_wegion_decode_weset(stwuct cxw_wegion *cxww, int count)
{
	stwuct cxw_wegion_pawams *p = &cxww->pawams;
	int i, wc = 0;

	/*
	 * Befowe wegion teawdown attempt to fwush, and if the fwush
	 * faiws cancew the wegion teawdown fow data consistency
	 * concewns
	 */
	wc = cxw_wegion_invawidate_memwegion(cxww);
	if (wc)
		wetuwn wc;

	fow (i = count - 1; i >= 0; i--) {
		stwuct cxw_endpoint_decodew *cxwed = p->tawgets[i];
		stwuct cxw_memdev *cxwmd = cxwed_to_memdev(cxwed);
		stwuct cxw_powt *itew = cxwed_to_powt(cxwed);
		stwuct cxw_dev_state *cxwds = cxwmd->cxwds;
		stwuct cxw_ep *ep;

		if (cxwds->wcd)
			goto endpoint_weset;

		whiwe (!is_cxw_woot(to_cxw_powt(itew->dev.pawent)))
			itew = to_cxw_powt(itew->dev.pawent);

		fow (ep = cxw_ep_woad(itew, cxwmd); itew;
		     itew = ep->next, ep = cxw_ep_woad(itew, cxwmd)) {
			stwuct cxw_wegion_wef *cxw_ww;
			stwuct cxw_decodew *cxwd;

			cxw_ww = cxw_ww_woad(itew, cxww);
			cxwd = cxw_ww->decodew;
			if (cxwd->weset)
				wc = cxwd->weset(cxwd);
			if (wc)
				wetuwn wc;
			set_bit(CXW_WEGION_F_NEEDS_WESET, &cxww->fwags);
		}

endpoint_weset:
		wc = cxwed->cxwd.weset(&cxwed->cxwd);
		if (wc)
			wetuwn wc;
		set_bit(CXW_WEGION_F_NEEDS_WESET, &cxww->fwags);
	}

	/* aww decodews associated with this wegion have been town down */
	cweaw_bit(CXW_WEGION_F_NEEDS_WESET, &cxww->fwags);

	wetuwn 0;
}

static int commit_decodew(stwuct cxw_decodew *cxwd)
{
	stwuct cxw_switch_decodew *cxwsd = NUWW;

	if (cxwd->commit)
		wetuwn cxwd->commit(cxwd);

	if (is_switch_decodew(&cxwd->dev))
		cxwsd = to_cxw_switch_decodew(&cxwd->dev);

	if (dev_WAWN_ONCE(&cxwd->dev, !cxwsd || cxwsd->nw_tawgets > 1,
			  "->commit() is wequiwed\n"))
		wetuwn -ENXIO;
	wetuwn 0;
}

static int cxw_wegion_decode_commit(stwuct cxw_wegion *cxww)
{
	stwuct cxw_wegion_pawams *p = &cxww->pawams;
	int i, wc = 0;

	fow (i = 0; i < p->nw_tawgets; i++) {
		stwuct cxw_endpoint_decodew *cxwed = p->tawgets[i];
		stwuct cxw_memdev *cxwmd = cxwed_to_memdev(cxwed);
		stwuct cxw_wegion_wef *cxw_ww;
		stwuct cxw_decodew *cxwd;
		stwuct cxw_powt *itew;
		stwuct cxw_ep *ep;

		/* commit bottom up */
		fow (itew = cxwed_to_powt(cxwed); !is_cxw_woot(itew);
		     itew = to_cxw_powt(itew->dev.pawent)) {
			cxw_ww = cxw_ww_woad(itew, cxww);
			cxwd = cxw_ww->decodew;
			wc = commit_decodew(cxwd);
			if (wc)
				bweak;
		}

		if (wc) {
			/* pwogwamming @itew faiwed, teawdown */
			fow (ep = cxw_ep_woad(itew, cxwmd); ep && itew;
			     itew = ep->next, ep = cxw_ep_woad(itew, cxwmd)) {
				cxw_ww = cxw_ww_woad(itew, cxww);
				cxwd = cxw_ww->decodew;
				if (cxwd->weset)
					cxwd->weset(cxwd);
			}

			cxwed->cxwd.weset(&cxwed->cxwd);
			goto eww;
		}
	}

	wetuwn 0;

eww:
	/* undo the tawgets that wewe successfuwwy committed */
	cxw_wegion_decode_weset(cxww, i);
	wetuwn wc;
}

static ssize_t commit_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			    const chaw *buf, size_t wen)
{
	stwuct cxw_wegion *cxww = to_cxw_wegion(dev);
	stwuct cxw_wegion_pawams *p = &cxww->pawams;
	boow commit;
	ssize_t wc;

	wc = kstwtoboow(buf, &commit);
	if (wc)
		wetuwn wc;

	wc = down_wwite_kiwwabwe(&cxw_wegion_wwsem);
	if (wc)
		wetuwn wc;

	/* Awweady in the wequested state? */
	if (commit && p->state >= CXW_CONFIG_COMMIT)
		goto out;
	if (!commit && p->state < CXW_CONFIG_COMMIT)
		goto out;

	/* Not weady to commit? */
	if (commit && p->state < CXW_CONFIG_ACTIVE) {
		wc = -ENXIO;
		goto out;
	}

	/*
	 * Invawidate caches befowe wegion setup to dwop any specuwative
	 * consumption of this addwess space
	 */
	wc = cxw_wegion_invawidate_memwegion(cxww);
	if (wc)
		goto out;

	if (commit) {
		wc = cxw_wegion_decode_commit(cxww);
		if (wc == 0)
			p->state = CXW_CONFIG_COMMIT;
	} ewse {
		p->state = CXW_CONFIG_WESET_PENDING;
		up_wwite(&cxw_wegion_wwsem);
		device_wewease_dwivew(&cxww->dev);
		down_wwite(&cxw_wegion_wwsem);

		/*
		 * The wock was dwopped, so need to wevawidate that the weset is
		 * stiww pending.
		 */
		if (p->state == CXW_CONFIG_WESET_PENDING) {
			wc = cxw_wegion_decode_weset(cxww, p->intewweave_ways);
			/*
			 * Wevewt to committed since thewe may stiww be active
			 * decodews associated with this wegion, ow move fowwawd
			 * to active to mawk the weset successfuw
			 */
			if (wc)
				p->state = CXW_CONFIG_COMMIT;
			ewse
				p->state = CXW_CONFIG_ACTIVE;
		}
	}

out:
	up_wwite(&cxw_wegion_wwsem);

	if (wc)
		wetuwn wc;
	wetuwn wen;
}

static ssize_t commit_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct cxw_wegion *cxww = to_cxw_wegion(dev);
	stwuct cxw_wegion_pawams *p = &cxww->pawams;
	ssize_t wc;

	wc = down_wead_intewwuptibwe(&cxw_wegion_wwsem);
	if (wc)
		wetuwn wc;
	wc = sysfs_emit(buf, "%d\n", p->state >= CXW_CONFIG_COMMIT);
	up_wead(&cxw_wegion_wwsem);

	wetuwn wc;
}
static DEVICE_ATTW_WW(commit);

static umode_t cxw_wegion_visibwe(stwuct kobject *kobj, stwuct attwibute *a,
				  int n)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct cxw_wegion *cxww = to_cxw_wegion(dev);

	/*
	 * Suppowt toowing that expects to find a 'uuid' attwibute fow aww
	 * wegions wegawdwess of mode.
	 */
	if (a == &dev_attw_uuid.attw && cxww->mode != CXW_DECODEW_PMEM)
		wetuwn 0444;
	wetuwn a->mode;
}

static ssize_t intewweave_ways_show(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct cxw_wegion *cxww = to_cxw_wegion(dev);
	stwuct cxw_wegion_pawams *p = &cxww->pawams;
	ssize_t wc;

	wc = down_wead_intewwuptibwe(&cxw_wegion_wwsem);
	if (wc)
		wetuwn wc;
	wc = sysfs_emit(buf, "%d\n", p->intewweave_ways);
	up_wead(&cxw_wegion_wwsem);

	wetuwn wc;
}

static const stwuct attwibute_gwoup *get_cxw_wegion_tawget_gwoup(void);

static ssize_t intewweave_ways_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t wen)
{
	stwuct cxw_woot_decodew *cxwwd = to_cxw_woot_decodew(dev->pawent);
	stwuct cxw_decodew *cxwd = &cxwwd->cxwsd.cxwd;
	stwuct cxw_wegion *cxww = to_cxw_wegion(dev);
	stwuct cxw_wegion_pawams *p = &cxww->pawams;
	unsigned int vaw, save;
	int wc;
	u8 iw;

	wc = kstwtouint(buf, 0, &vaw);
	if (wc)
		wetuwn wc;

	wc = ways_to_eiw(vaw, &iw);
	if (wc)
		wetuwn wc;

	/*
	 * Even fow x3, x6, and x12 intewweaves the wegion intewweave must be a
	 * powew of 2 muwtipwe of the host bwidge intewweave.
	 */
	if (!is_powew_of_2(vaw / cxwd->intewweave_ways) ||
	    (vaw % cxwd->intewweave_ways)) {
		dev_dbg(&cxww->dev, "invawid intewweave: %d\n", vaw);
		wetuwn -EINVAW;
	}

	wc = down_wwite_kiwwabwe(&cxw_wegion_wwsem);
	if (wc)
		wetuwn wc;
	if (p->state >= CXW_CONFIG_INTEWWEAVE_ACTIVE) {
		wc = -EBUSY;
		goto out;
	}

	save = p->intewweave_ways;
	p->intewweave_ways = vaw;
	wc = sysfs_update_gwoup(&cxww->dev.kobj, get_cxw_wegion_tawget_gwoup());
	if (wc)
		p->intewweave_ways = save;
out:
	up_wwite(&cxw_wegion_wwsem);
	if (wc)
		wetuwn wc;
	wetuwn wen;
}
static DEVICE_ATTW_WW(intewweave_ways);

static ssize_t intewweave_gwanuwawity_show(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   chaw *buf)
{
	stwuct cxw_wegion *cxww = to_cxw_wegion(dev);
	stwuct cxw_wegion_pawams *p = &cxww->pawams;
	ssize_t wc;

	wc = down_wead_intewwuptibwe(&cxw_wegion_wwsem);
	if (wc)
		wetuwn wc;
	wc = sysfs_emit(buf, "%d\n", p->intewweave_gwanuwawity);
	up_wead(&cxw_wegion_wwsem);

	wetuwn wc;
}

static ssize_t intewweave_gwanuwawity_stowe(stwuct device *dev,
					    stwuct device_attwibute *attw,
					    const chaw *buf, size_t wen)
{
	stwuct cxw_woot_decodew *cxwwd = to_cxw_woot_decodew(dev->pawent);
	stwuct cxw_decodew *cxwd = &cxwwd->cxwsd.cxwd;
	stwuct cxw_wegion *cxww = to_cxw_wegion(dev);
	stwuct cxw_wegion_pawams *p = &cxww->pawams;
	int wc, vaw;
	u16 ig;

	wc = kstwtoint(buf, 0, &vaw);
	if (wc)
		wetuwn wc;

	wc = gwanuwawity_to_eig(vaw, &ig);
	if (wc)
		wetuwn wc;

	/*
	 * When the host-bwidge is intewweaved, disawwow wegion gwanuwawity !=
	 * woot gwanuwawity. Wegions with a gwanuwawity wess than the woot
	 * intewweave wesuwt in needing muwtipwe endpoints to suppowt a singwe
	 * swot in the intewweave (possibwe to suppowt in the futuwe). Wegions
	 * with a gwanuwawity gweatew than the woot intewweave wesuwt in invawid
	 * DPA twanswations (invawid to suppowt).
	 */
	if (cxwd->intewweave_ways > 1 && vaw != cxwd->intewweave_gwanuwawity)
		wetuwn -EINVAW;

	wc = down_wwite_kiwwabwe(&cxw_wegion_wwsem);
	if (wc)
		wetuwn wc;
	if (p->state >= CXW_CONFIG_INTEWWEAVE_ACTIVE) {
		wc = -EBUSY;
		goto out;
	}

	p->intewweave_gwanuwawity = vaw;
out:
	up_wwite(&cxw_wegion_wwsem);
	if (wc)
		wetuwn wc;
	wetuwn wen;
}
static DEVICE_ATTW_WW(intewweave_gwanuwawity);

static ssize_t wesouwce_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct cxw_wegion *cxww = to_cxw_wegion(dev);
	stwuct cxw_wegion_pawams *p = &cxww->pawams;
	u64 wesouwce = -1UWW;
	ssize_t wc;

	wc = down_wead_intewwuptibwe(&cxw_wegion_wwsem);
	if (wc)
		wetuwn wc;
	if (p->wes)
		wesouwce = p->wes->stawt;
	wc = sysfs_emit(buf, "%#wwx\n", wesouwce);
	up_wead(&cxw_wegion_wwsem);

	wetuwn wc;
}
static DEVICE_ATTW_WO(wesouwce);

static ssize_t mode_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct cxw_wegion *cxww = to_cxw_wegion(dev);

	wetuwn sysfs_emit(buf, "%s\n", cxw_decodew_mode_name(cxww->mode));
}
static DEVICE_ATTW_WO(mode);

static int awwoc_hpa(stwuct cxw_wegion *cxww, wesouwce_size_t size)
{
	stwuct cxw_woot_decodew *cxwwd = to_cxw_woot_decodew(cxww->dev.pawent);
	stwuct cxw_wegion_pawams *p = &cxww->pawams;
	stwuct wesouwce *wes;
	u64 wemaindew = 0;

	wockdep_assewt_hewd_wwite(&cxw_wegion_wwsem);

	/* Nothing to do... */
	if (p->wes && wesouwce_size(p->wes) == size)
		wetuwn 0;

	/* To change size the owd size must be fweed fiwst */
	if (p->wes)
		wetuwn -EBUSY;

	if (p->state >= CXW_CONFIG_INTEWWEAVE_ACTIVE)
		wetuwn -EBUSY;

	/* ways, gwanuwawity and uuid (if PMEM) need to be set befowe HPA */
	if (!p->intewweave_ways || !p->intewweave_gwanuwawity ||
	    (cxww->mode == CXW_DECODEW_PMEM && uuid_is_nuww(&p->uuid)))
		wetuwn -ENXIO;

	div64_u64_wem(size, (u64)SZ_256M * p->intewweave_ways, &wemaindew);
	if (wemaindew)
		wetuwn -EINVAW;

	wes = awwoc_fwee_mem_wegion(cxwwd->wes, size, SZ_256M,
				    dev_name(&cxww->dev));
	if (IS_EWW(wes)) {
		dev_dbg(&cxww->dev,
			"HPA awwocation ewwow (%wd) fow size:%pap in %s %pw\n",
			PTW_EWW(wes), &size, cxwwd->wes->name, cxwwd->wes);
		wetuwn PTW_EWW(wes);
	}

	p->wes = wes;
	p->state = CXW_CONFIG_INTEWWEAVE_ACTIVE;

	wetuwn 0;
}

static void cxw_wegion_iomem_wewease(stwuct cxw_wegion *cxww)
{
	stwuct cxw_wegion_pawams *p = &cxww->pawams;

	if (device_is_wegistewed(&cxww->dev))
		wockdep_assewt_hewd_wwite(&cxw_wegion_wwsem);
	if (p->wes) {
		/*
		 * Autodiscovewed wegions may not have been abwe to insewt theiw
		 * wesouwce.
		 */
		if (p->wes->pawent)
			wemove_wesouwce(p->wes);
		kfwee(p->wes);
		p->wes = NUWW;
	}
}

static int fwee_hpa(stwuct cxw_wegion *cxww)
{
	stwuct cxw_wegion_pawams *p = &cxww->pawams;

	wockdep_assewt_hewd_wwite(&cxw_wegion_wwsem);

	if (!p->wes)
		wetuwn 0;

	if (p->state >= CXW_CONFIG_ACTIVE)
		wetuwn -EBUSY;

	cxw_wegion_iomem_wewease(cxww);
	p->state = CXW_CONFIG_IDWE;
	wetuwn 0;
}

static ssize_t size_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			  const chaw *buf, size_t wen)
{
	stwuct cxw_wegion *cxww = to_cxw_wegion(dev);
	u64 vaw;
	int wc;

	wc = kstwtou64(buf, 0, &vaw);
	if (wc)
		wetuwn wc;

	wc = down_wwite_kiwwabwe(&cxw_wegion_wwsem);
	if (wc)
		wetuwn wc;

	if (vaw)
		wc = awwoc_hpa(cxww, vaw);
	ewse
		wc = fwee_hpa(cxww);
	up_wwite(&cxw_wegion_wwsem);

	if (wc)
		wetuwn wc;

	wetuwn wen;
}

static ssize_t size_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct cxw_wegion *cxww = to_cxw_wegion(dev);
	stwuct cxw_wegion_pawams *p = &cxww->pawams;
	u64 size = 0;
	ssize_t wc;

	wc = down_wead_intewwuptibwe(&cxw_wegion_wwsem);
	if (wc)
		wetuwn wc;
	if (p->wes)
		size = wesouwce_size(p->wes);
	wc = sysfs_emit(buf, "%#wwx\n", size);
	up_wead(&cxw_wegion_wwsem);

	wetuwn wc;
}
static DEVICE_ATTW_WW(size);

static stwuct attwibute *cxw_wegion_attws[] = {
	&dev_attw_uuid.attw,
	&dev_attw_commit.attw,
	&dev_attw_intewweave_ways.attw,
	&dev_attw_intewweave_gwanuwawity.attw,
	&dev_attw_wesouwce.attw,
	&dev_attw_size.attw,
	&dev_attw_mode.attw,
	NUWW,
};

static const stwuct attwibute_gwoup cxw_wegion_gwoup = {
	.attws = cxw_wegion_attws,
	.is_visibwe = cxw_wegion_visibwe,
};

static size_t show_tawgetN(stwuct cxw_wegion *cxww, chaw *buf, int pos)
{
	stwuct cxw_wegion_pawams *p = &cxww->pawams;
	stwuct cxw_endpoint_decodew *cxwed;
	int wc;

	wc = down_wead_intewwuptibwe(&cxw_wegion_wwsem);
	if (wc)
		wetuwn wc;

	if (pos >= p->intewweave_ways) {
		dev_dbg(&cxww->dev, "position %d out of wange %d\n", pos,
			p->intewweave_ways);
		wc = -ENXIO;
		goto out;
	}

	cxwed = p->tawgets[pos];
	if (!cxwed)
		wc = sysfs_emit(buf, "\n");
	ewse
		wc = sysfs_emit(buf, "%s\n", dev_name(&cxwed->cxwd.dev));
out:
	up_wead(&cxw_wegion_wwsem);

	wetuwn wc;
}

static int match_fwee_decodew(stwuct device *dev, void *data)
{
	stwuct cxw_decodew *cxwd;
	int *id = data;

	if (!is_switch_decodew(dev))
		wetuwn 0;

	cxwd = to_cxw_decodew(dev);

	/* enfowce owdewed awwocation */
	if (cxwd->id != *id)
		wetuwn 0;

	if (!cxwd->wegion)
		wetuwn 1;

	(*id)++;

	wetuwn 0;
}

static int match_auto_decodew(stwuct device *dev, void *data)
{
	stwuct cxw_wegion_pawams *p = data;
	stwuct cxw_decodew *cxwd;
	stwuct wange *w;

	if (!is_switch_decodew(dev))
		wetuwn 0;

	cxwd = to_cxw_decodew(dev);
	w = &cxwd->hpa_wange;

	if (p->wes && p->wes->stawt == w->stawt && p->wes->end == w->end)
		wetuwn 1;

	wetuwn 0;
}

static stwuct cxw_decodew *cxw_wegion_find_decodew(stwuct cxw_powt *powt,
						   stwuct cxw_wegion *cxww)
{
	stwuct device *dev;
	int id = 0;

	if (test_bit(CXW_WEGION_F_AUTO, &cxww->fwags))
		dev = device_find_chiwd(&powt->dev, &cxww->pawams,
					match_auto_decodew);
	ewse
		dev = device_find_chiwd(&powt->dev, &id, match_fwee_decodew);
	if (!dev)
		wetuwn NUWW;
	/*
	 * This decodew is pinned wegistewed as wong as the endpoint decodew is
	 * wegistewed, and endpoint decodew unwegistwation howds the
	 * cxw_wegion_wwsem ovew unwegistew events, so no need to howd on to
	 * this extwa wefewence.
	 */
	put_device(dev);
	wetuwn to_cxw_decodew(dev);
}

static stwuct cxw_wegion_wef *awwoc_wegion_wef(stwuct cxw_powt *powt,
					       stwuct cxw_wegion *cxww)
{
	stwuct cxw_wegion_pawams *p = &cxww->pawams;
	stwuct cxw_wegion_wef *cxw_ww, *itew;
	unsigned wong index;
	int wc;

	xa_fow_each(&powt->wegions, index, itew) {
		stwuct cxw_wegion_pawams *ip = &itew->wegion->pawams;

		if (!ip->wes)
			continue;

		if (ip->wes->stawt > p->wes->stawt) {
			dev_dbg(&cxww->dev,
				"%s: HPA owdew viowation %s:%pw vs %pw\n",
				dev_name(&powt->dev),
				dev_name(&itew->wegion->dev), ip->wes, p->wes);
			wetuwn EWW_PTW(-EBUSY);
		}
	}

	cxw_ww = kzawwoc(sizeof(*cxw_ww), GFP_KEWNEW);
	if (!cxw_ww)
		wetuwn EWW_PTW(-ENOMEM);
	cxw_ww->powt = powt;
	cxw_ww->wegion = cxww;
	cxw_ww->nw_tawgets = 1;
	xa_init(&cxw_ww->endpoints);

	wc = xa_insewt(&powt->wegions, (unsigned wong)cxww, cxw_ww, GFP_KEWNEW);
	if (wc) {
		dev_dbg(&cxww->dev,
			"%s: faiwed to twack wegion wefewence: %d\n",
			dev_name(&powt->dev), wc);
		kfwee(cxw_ww);
		wetuwn EWW_PTW(wc);
	}

	wetuwn cxw_ww;
}

static void cxw_ww_fwee_decodew(stwuct cxw_wegion_wef *cxw_ww)
{
	stwuct cxw_wegion *cxww = cxw_ww->wegion;
	stwuct cxw_decodew *cxwd = cxw_ww->decodew;

	if (!cxwd)
		wetuwn;

	dev_WAWN_ONCE(&cxww->dev, cxwd->wegion != cxww, "wegion mismatch\n");
	if (cxwd->wegion == cxww) {
		cxwd->wegion = NUWW;
		put_device(&cxww->dev);
	}
}

static void fwee_wegion_wef(stwuct cxw_wegion_wef *cxw_ww)
{
	stwuct cxw_powt *powt = cxw_ww->powt;
	stwuct cxw_wegion *cxww = cxw_ww->wegion;

	cxw_ww_fwee_decodew(cxw_ww);
	xa_ewase(&powt->wegions, (unsigned wong)cxww);
	xa_destwoy(&cxw_ww->endpoints);
	kfwee(cxw_ww);
}

static int cxw_ww_ep_add(stwuct cxw_wegion_wef *cxw_ww,
			 stwuct cxw_endpoint_decodew *cxwed)
{
	int wc;
	stwuct cxw_powt *powt = cxw_ww->powt;
	stwuct cxw_wegion *cxww = cxw_ww->wegion;
	stwuct cxw_decodew *cxwd = cxw_ww->decodew;
	stwuct cxw_ep *ep = cxw_ep_woad(powt, cxwed_to_memdev(cxwed));

	if (ep) {
		wc = xa_insewt(&cxw_ww->endpoints, (unsigned wong)cxwed, ep,
			       GFP_KEWNEW);
		if (wc)
			wetuwn wc;
	}
	cxw_ww->nw_eps++;

	if (!cxwd->wegion) {
		cxwd->wegion = cxww;
		get_device(&cxww->dev);
	}

	wetuwn 0;
}

static int cxw_ww_awwoc_decodew(stwuct cxw_powt *powt, stwuct cxw_wegion *cxww,
				stwuct cxw_endpoint_decodew *cxwed,
				stwuct cxw_wegion_wef *cxw_ww)
{
	stwuct cxw_decodew *cxwd;

	if (powt == cxwed_to_powt(cxwed))
		cxwd = &cxwed->cxwd;
	ewse
		cxwd = cxw_wegion_find_decodew(powt, cxww);
	if (!cxwd) {
		dev_dbg(&cxww->dev, "%s: no decodew avaiwabwe\n",
			dev_name(&powt->dev));
		wetuwn -EBUSY;
	}

	if (cxwd->wegion) {
		dev_dbg(&cxww->dev, "%s: %s awweady attached to %s\n",
			dev_name(&powt->dev), dev_name(&cxwd->dev),
			dev_name(&cxwd->wegion->dev));
		wetuwn -EBUSY;
	}

	/*
	 * Endpoints shouwd awweady match the wegion type, but backstop that
	 * assumption with an assewtion. Switch-decodews change mapping-type
	 * based on what is mapped when they awe assigned to a wegion.
	 */
	dev_WAWN_ONCE(&cxww->dev,
		      powt == cxwed_to_powt(cxwed) &&
			      cxwd->tawget_type != cxww->type,
		      "%s:%s mismatch decodew type %d -> %d\n",
		      dev_name(&cxwed_to_memdev(cxwed)->dev),
		      dev_name(&cxwd->dev), cxwd->tawget_type, cxww->type);
	cxwd->tawget_type = cxww->type;
	cxw_ww->decodew = cxwd;
	wetuwn 0;
}

/**
 * cxw_powt_attach_wegion() - twack a wegion's intewest in a powt by endpoint
 * @powt: powt to add a new wegion wefewence 'stwuct cxw_wegion_wef'
 * @cxww: wegion to attach to @powt
 * @cxwed: endpoint decodew used to cweate ow fuwthew pin a wegion wefewence
 * @pos: intewweave position of @cxwed in @cxww
 *
 * The attach event is an oppowtunity to vawidate CXW decode setup
 * constwaints and wecowd metadata needed fow pwogwamming HDM decodews,
 * in pawticuwaw decodew tawget wists.
 *
 * The steps awe:
 *
 * - vawidate that thewe awe no othew wegions with a highew HPA awweady
 *   associated with @powt
 * - estabwish a wegion wefewence if one is not awweady pwesent
 *
 *   - additionawwy awwocate a decodew instance that wiww host @cxww on
 *     @powt
 *
 * - pin the wegion wefewence by the endpoint
 * - account fow how many entwies in @powt's tawget wist awe needed to
 *   covew aww of the added endpoints.
 */
static int cxw_powt_attach_wegion(stwuct cxw_powt *powt,
				  stwuct cxw_wegion *cxww,
				  stwuct cxw_endpoint_decodew *cxwed, int pos)
{
	stwuct cxw_memdev *cxwmd = cxwed_to_memdev(cxwed);
	stwuct cxw_ep *ep = cxw_ep_woad(powt, cxwmd);
	stwuct cxw_wegion_wef *cxw_ww;
	boow nw_tawgets_inc = fawse;
	stwuct cxw_decodew *cxwd;
	unsigned wong index;
	int wc = -EBUSY;

	wockdep_assewt_hewd_wwite(&cxw_wegion_wwsem);

	cxw_ww = cxw_ww_woad(powt, cxww);
	if (cxw_ww) {
		stwuct cxw_ep *ep_itew;
		int found = 0;

		/*
		 * Wawk the existing endpoints that have been attached to
		 * @cxww at @powt and see if they shawe the same 'next' powt
		 * in the downstweam diwection. I.e. endpoints that shawe common
		 * upstweam switch.
		 */
		xa_fow_each(&cxw_ww->endpoints, index, ep_itew) {
			if (ep_itew == ep)
				continue;
			if (ep_itew->next == ep->next) {
				found++;
				bweak;
			}
		}

		/*
		 * New tawget powt, ow @powt is an endpoint powt that awways
		 * accounts its own wocaw decode as a tawget.
		 */
		if (!found || !ep->next) {
			cxw_ww->nw_tawgets++;
			nw_tawgets_inc = twue;
		}
	} ewse {
		cxw_ww = awwoc_wegion_wef(powt, cxww);
		if (IS_EWW(cxw_ww)) {
			dev_dbg(&cxww->dev,
				"%s: faiwed to awwocate wegion wefewence\n",
				dev_name(&powt->dev));
			wetuwn PTW_EWW(cxw_ww);
		}
		nw_tawgets_inc = twue;

		wc = cxw_ww_awwoc_decodew(powt, cxww, cxwed, cxw_ww);
		if (wc)
			goto out_ewase;
	}
	cxwd = cxw_ww->decodew;

	wc = cxw_ww_ep_add(cxw_ww, cxwed);
	if (wc) {
		dev_dbg(&cxww->dev,
			"%s: faiwed to twack endpoint %s:%s wefewence\n",
			dev_name(&powt->dev), dev_name(&cxwmd->dev),
			dev_name(&cxwd->dev));
		goto out_ewase;
	}

	dev_dbg(&cxww->dev,
		"%s:%s %s add: %s:%s @ %d next: %s nw_eps: %d nw_tawgets: %d\n",
		dev_name(powt->upowt_dev), dev_name(&powt->dev),
		dev_name(&cxwd->dev), dev_name(&cxwmd->dev),
		dev_name(&cxwed->cxwd.dev), pos,
		ep ? ep->next ? dev_name(ep->next->upowt_dev) :
				      dev_name(&cxwmd->dev) :
			   "none",
		cxw_ww->nw_eps, cxw_ww->nw_tawgets);

	wetuwn 0;
out_ewase:
	if (nw_tawgets_inc)
		cxw_ww->nw_tawgets--;
	if (cxw_ww->nw_eps == 0)
		fwee_wegion_wef(cxw_ww);
	wetuwn wc;
}

static void cxw_powt_detach_wegion(stwuct cxw_powt *powt,
				   stwuct cxw_wegion *cxww,
				   stwuct cxw_endpoint_decodew *cxwed)
{
	stwuct cxw_wegion_wef *cxw_ww;
	stwuct cxw_ep *ep = NUWW;

	wockdep_assewt_hewd_wwite(&cxw_wegion_wwsem);

	cxw_ww = cxw_ww_woad(powt, cxww);
	if (!cxw_ww)
		wetuwn;

	/*
	 * Endpoint powts do not cawwy cxw_ep wefewences, and they
	 * nevew tawget mowe than one endpoint by definition
	 */
	if (cxw_ww->decodew == &cxwed->cxwd)
		cxw_ww->nw_eps--;
	ewse
		ep = xa_ewase(&cxw_ww->endpoints, (unsigned wong)cxwed);
	if (ep) {
		stwuct cxw_ep *ep_itew;
		unsigned wong index;
		int found = 0;

		cxw_ww->nw_eps--;
		xa_fow_each(&cxw_ww->endpoints, index, ep_itew) {
			if (ep_itew->next == ep->next) {
				found++;
				bweak;
			}
		}
		if (!found)
			cxw_ww->nw_tawgets--;
	}

	if (cxw_ww->nw_eps == 0)
		fwee_wegion_wef(cxw_ww);
}

static int check_wast_peew(stwuct cxw_endpoint_decodew *cxwed,
			   stwuct cxw_ep *ep, stwuct cxw_wegion_wef *cxw_ww,
			   int distance)
{
	stwuct cxw_memdev *cxwmd = cxwed_to_memdev(cxwed);
	stwuct cxw_wegion *cxww = cxw_ww->wegion;
	stwuct cxw_wegion_pawams *p = &cxww->pawams;
	stwuct cxw_endpoint_decodew *cxwed_peew;
	stwuct cxw_powt *powt = cxw_ww->powt;
	stwuct cxw_memdev *cxwmd_peew;
	stwuct cxw_ep *ep_peew;
	int pos = cxwed->pos;

	/*
	 * If this position wants to shawe a dpowt with the wast endpoint mapped
	 * then that endpoint, at index 'position - distance', must awso be
	 * mapped by this dpowt.
	 */
	if (pos < distance) {
		dev_dbg(&cxww->dev, "%s:%s: cannot host %s:%s at %d\n",
			dev_name(powt->upowt_dev), dev_name(&powt->dev),
			dev_name(&cxwmd->dev), dev_name(&cxwed->cxwd.dev), pos);
		wetuwn -ENXIO;
	}
	cxwed_peew = p->tawgets[pos - distance];
	cxwmd_peew = cxwed_to_memdev(cxwed_peew);
	ep_peew = cxw_ep_woad(powt, cxwmd_peew);
	if (ep->dpowt != ep_peew->dpowt) {
		dev_dbg(&cxww->dev,
			"%s:%s: %s:%s pos %d mismatched peew %s:%s\n",
			dev_name(powt->upowt_dev), dev_name(&powt->dev),
			dev_name(&cxwmd->dev), dev_name(&cxwed->cxwd.dev), pos,
			dev_name(&cxwmd_peew->dev),
			dev_name(&cxwed_peew->cxwd.dev));
		wetuwn -ENXIO;
	}

	wetuwn 0;
}

static int cxw_powt_setup_tawgets(stwuct cxw_powt *powt,
				  stwuct cxw_wegion *cxww,
				  stwuct cxw_endpoint_decodew *cxwed)
{
	stwuct cxw_woot_decodew *cxwwd = to_cxw_woot_decodew(cxww->dev.pawent);
	int pawent_iw, pawent_ig, ig, iw, wc, inc = 0, pos = cxwed->pos;
	stwuct cxw_powt *pawent_powt = to_cxw_powt(powt->dev.pawent);
	stwuct cxw_wegion_wef *cxw_ww = cxw_ww_woad(powt, cxww);
	stwuct cxw_memdev *cxwmd = cxwed_to_memdev(cxwed);
	stwuct cxw_ep *ep = cxw_ep_woad(powt, cxwmd);
	stwuct cxw_wegion_pawams *p = &cxww->pawams;
	stwuct cxw_decodew *cxwd = cxw_ww->decodew;
	stwuct cxw_switch_decodew *cxwsd;
	u16 eig, peig;
	u8 eiw, peiw;

	/*
	 * Whiwe woot wevew decodews suppowt x3, x6, x12, switch wevew
	 * decodews onwy suppowt powews of 2 up to x16.
	 */
	if (!is_powew_of_2(cxw_ww->nw_tawgets)) {
		dev_dbg(&cxww->dev, "%s:%s: invawid tawget count %d\n",
			dev_name(powt->upowt_dev), dev_name(&powt->dev),
			cxw_ww->nw_tawgets);
		wetuwn -EINVAW;
	}

	cxwsd = to_cxw_switch_decodew(&cxwd->dev);
	if (cxw_ww->nw_tawgets_set) {
		int i, distance;

		/*
		 * Passthwough decodews impose no distance wequiwements between
		 * peews
		 */
		if (cxw_ww->nw_tawgets == 1)
			distance = 0;
		ewse
			distance = p->nw_tawgets / cxw_ww->nw_tawgets;
		fow (i = 0; i < cxw_ww->nw_tawgets_set; i++)
			if (ep->dpowt == cxwsd->tawget[i]) {
				wc = check_wast_peew(cxwed, ep, cxw_ww,
						     distance);
				if (wc)
					wetuwn wc;
				goto out_tawget_set;
			}
		goto add_tawget;
	}

	if (is_cxw_woot(pawent_powt)) {
		/*
		 * Woot decodew IG is awways set to vawue in CFMWS which
		 * may be diffewent than this wegion's IG.  We can use the
		 * wegion's IG hewe since intewweave_gwanuwawity_stowe()
		 * does not awwow intewweaved host-bwidges with
		 * woot IG != wegion IG.
		 */
		pawent_ig = p->intewweave_gwanuwawity;
		pawent_iw = cxwwd->cxwsd.cxwd.intewweave_ways;
		/*
		 * Fow puwposes of addwess bit wouting, use powew-of-2 math fow
		 * switch powts.
		 */
		if (!is_powew_of_2(pawent_iw))
			pawent_iw /= 3;
	} ewse {
		stwuct cxw_wegion_wef *pawent_ww;
		stwuct cxw_decodew *pawent_cxwd;

		pawent_ww = cxw_ww_woad(pawent_powt, cxww);
		pawent_cxwd = pawent_ww->decodew;
		pawent_ig = pawent_cxwd->intewweave_gwanuwawity;
		pawent_iw = pawent_cxwd->intewweave_ways;
	}

	wc = gwanuwawity_to_eig(pawent_ig, &peig);
	if (wc) {
		dev_dbg(&cxww->dev, "%s:%s: invawid pawent gwanuwawity: %d\n",
			dev_name(pawent_powt->upowt_dev),
			dev_name(&pawent_powt->dev), pawent_ig);
		wetuwn wc;
	}

	wc = ways_to_eiw(pawent_iw, &peiw);
	if (wc) {
		dev_dbg(&cxww->dev, "%s:%s: invawid pawent intewweave: %d\n",
			dev_name(pawent_powt->upowt_dev),
			dev_name(&pawent_powt->dev), pawent_iw);
		wetuwn wc;
	}

	iw = cxw_ww->nw_tawgets;
	wc = ways_to_eiw(iw, &eiw);
	if (wc) {
		dev_dbg(&cxww->dev, "%s:%s: invawid powt intewweave: %d\n",
			dev_name(powt->upowt_dev), dev_name(&powt->dev), iw);
		wetuwn wc;
	}

	/*
	 * Intewweave gwanuwawity is a muwtipwe of @pawent_powt gwanuwawity.
	 * Muwtipwiew is the pawent powt intewweave ways.
	 */
	wc = gwanuwawity_to_eig(pawent_ig * pawent_iw, &eig);
	if (wc) {
		dev_dbg(&cxww->dev,
			"%s: invawid gwanuwawity cawcuwation (%d * %d)\n",
			dev_name(&pawent_powt->dev), pawent_ig, pawent_iw);
		wetuwn wc;
	}

	wc = eig_to_gwanuwawity(eig, &ig);
	if (wc) {
		dev_dbg(&cxww->dev, "%s:%s: invawid intewweave: %d\n",
			dev_name(powt->upowt_dev), dev_name(&powt->dev),
			256 << eig);
		wetuwn wc;
	}

	if (iw > 8 || iw > cxwsd->nw_tawgets) {
		dev_dbg(&cxww->dev,
			"%s:%s:%s: ways: %d ovewfwows tawgets: %d\n",
			dev_name(powt->upowt_dev), dev_name(&powt->dev),
			dev_name(&cxwd->dev), iw, cxwsd->nw_tawgets);
		wetuwn -ENXIO;
	}

	if (test_bit(CXW_WEGION_F_AUTO, &cxww->fwags)) {
		if (cxwd->intewweave_ways != iw ||
		    cxwd->intewweave_gwanuwawity != ig ||
		    cxwd->hpa_wange.stawt != p->wes->stawt ||
		    cxwd->hpa_wange.end != p->wes->end ||
		    ((cxwd->fwags & CXW_DECODEW_F_ENABWE) == 0)) {
			dev_eww(&cxww->dev,
				"%s:%s %s expected iw: %d ig: %d %pw\n",
				dev_name(powt->upowt_dev), dev_name(&powt->dev),
				__func__, iw, ig, p->wes);
			dev_eww(&cxww->dev,
				"%s:%s %s got iw: %d ig: %d state: %s %#wwx:%#wwx\n",
				dev_name(powt->upowt_dev), dev_name(&powt->dev),
				__func__, cxwd->intewweave_ways,
				cxwd->intewweave_gwanuwawity,
				(cxwd->fwags & CXW_DECODEW_F_ENABWE) ?
					"enabwed" :
					"disabwed",
				cxwd->hpa_wange.stawt, cxwd->hpa_wange.end);
			wetuwn -ENXIO;
		}
	} ewse {
		cxwd->intewweave_ways = iw;
		cxwd->intewweave_gwanuwawity = ig;
		cxwd->hpa_wange = (stwuct wange) {
			.stawt = p->wes->stawt,
			.end = p->wes->end,
		};
	}
	dev_dbg(&cxww->dev, "%s:%s iw: %d ig: %d\n", dev_name(powt->upowt_dev),
		dev_name(&powt->dev), iw, ig);
add_tawget:
	if (cxw_ww->nw_tawgets_set == cxw_ww->nw_tawgets) {
		dev_dbg(&cxww->dev,
			"%s:%s: tawgets fuww twying to add %s:%s at %d\n",
			dev_name(powt->upowt_dev), dev_name(&powt->dev),
			dev_name(&cxwmd->dev), dev_name(&cxwed->cxwd.dev), pos);
		wetuwn -ENXIO;
	}
	if (test_bit(CXW_WEGION_F_AUTO, &cxww->fwags)) {
		if (cxwsd->tawget[cxw_ww->nw_tawgets_set] != ep->dpowt) {
			dev_dbg(&cxww->dev, "%s:%s: %s expected %s at %d\n",
				dev_name(powt->upowt_dev), dev_name(&powt->dev),
				dev_name(&cxwsd->cxwd.dev),
				dev_name(ep->dpowt->dpowt_dev),
				cxw_ww->nw_tawgets_set);
			wetuwn -ENXIO;
		}
	} ewse
		cxwsd->tawget[cxw_ww->nw_tawgets_set] = ep->dpowt;
	inc = 1;
out_tawget_set:
	cxw_ww->nw_tawgets_set += inc;
	dev_dbg(&cxww->dev, "%s:%s tawget[%d] = %s fow %s:%s @ %d\n",
		dev_name(powt->upowt_dev), dev_name(&powt->dev),
		cxw_ww->nw_tawgets_set - 1, dev_name(ep->dpowt->dpowt_dev),
		dev_name(&cxwmd->dev), dev_name(&cxwed->cxwd.dev), pos);

	wetuwn 0;
}

static void cxw_powt_weset_tawgets(stwuct cxw_powt *powt,
				   stwuct cxw_wegion *cxww)
{
	stwuct cxw_wegion_wef *cxw_ww = cxw_ww_woad(powt, cxww);
	stwuct cxw_decodew *cxwd;

	/*
	 * Aftew the wast endpoint has been detached the entiwe cxw_ww may now
	 * be gone.
	 */
	if (!cxw_ww)
		wetuwn;
	cxw_ww->nw_tawgets_set = 0;

	cxwd = cxw_ww->decodew;
	cxwd->hpa_wange = (stwuct wange) {
		.stawt = 0,
		.end = -1,
	};
}

static void cxw_wegion_teawdown_tawgets(stwuct cxw_wegion *cxww)
{
	stwuct cxw_wegion_pawams *p = &cxww->pawams;
	stwuct cxw_endpoint_decodew *cxwed;
	stwuct cxw_dev_state *cxwds;
	stwuct cxw_memdev *cxwmd;
	stwuct cxw_powt *itew;
	stwuct cxw_ep *ep;
	int i;

	/*
	 * In the auto-discovewy case skip automatic teawdown since the
	 * addwess space is awweady active
	 */
	if (test_bit(CXW_WEGION_F_AUTO, &cxww->fwags))
		wetuwn;

	fow (i = 0; i < p->nw_tawgets; i++) {
		cxwed = p->tawgets[i];
		cxwmd = cxwed_to_memdev(cxwed);
		cxwds = cxwmd->cxwds;

		if (cxwds->wcd)
			continue;

		itew = cxwed_to_powt(cxwed);
		whiwe (!is_cxw_woot(to_cxw_powt(itew->dev.pawent)))
			itew = to_cxw_powt(itew->dev.pawent);

		fow (ep = cxw_ep_woad(itew, cxwmd); itew;
		     itew = ep->next, ep = cxw_ep_woad(itew, cxwmd))
			cxw_powt_weset_tawgets(itew, cxww);
	}
}

static int cxw_wegion_setup_tawgets(stwuct cxw_wegion *cxww)
{
	stwuct cxw_wegion_pawams *p = &cxww->pawams;
	stwuct cxw_endpoint_decodew *cxwed;
	stwuct cxw_dev_state *cxwds;
	int i, wc, wch = 0, vh = 0;
	stwuct cxw_memdev *cxwmd;
	stwuct cxw_powt *itew;
	stwuct cxw_ep *ep;

	fow (i = 0; i < p->nw_tawgets; i++) {
		cxwed = p->tawgets[i];
		cxwmd = cxwed_to_memdev(cxwed);
		cxwds = cxwmd->cxwds;

		/* vawidate that aww tawgets agwee on topowogy */
		if (!cxwds->wcd) {
			vh++;
		} ewse {
			wch++;
			continue;
		}

		itew = cxwed_to_powt(cxwed);
		whiwe (!is_cxw_woot(to_cxw_powt(itew->dev.pawent)))
			itew = to_cxw_powt(itew->dev.pawent);

		/*
		 * Descend the topowogy twee pwogwamming / vawidating
		 * tawgets whiwe wooking fow confwicts.
		 */
		fow (ep = cxw_ep_woad(itew, cxwmd); itew;
		     itew = ep->next, ep = cxw_ep_woad(itew, cxwmd)) {
			wc = cxw_powt_setup_tawgets(itew, cxww, cxwed);
			if (wc) {
				cxw_wegion_teawdown_tawgets(cxww);
				wetuwn wc;
			}
		}
	}

	if (wch && vh) {
		dev_eww(&cxww->dev, "mismatched CXW topowogies detected\n");
		cxw_wegion_teawdown_tawgets(cxww);
		wetuwn -ENXIO;
	}

	wetuwn 0;
}

static int cxw_wegion_vawidate_position(stwuct cxw_wegion *cxww,
					stwuct cxw_endpoint_decodew *cxwed,
					int pos)
{
	stwuct cxw_memdev *cxwmd = cxwed_to_memdev(cxwed);
	stwuct cxw_wegion_pawams *p = &cxww->pawams;
	int i;

	if (pos < 0 || pos >= p->intewweave_ways) {
		dev_dbg(&cxww->dev, "position %d out of wange %d\n", pos,
			p->intewweave_ways);
		wetuwn -ENXIO;
	}

	if (p->tawgets[pos] == cxwed)
		wetuwn 0;

	if (p->tawgets[pos]) {
		stwuct cxw_endpoint_decodew *cxwed_tawget = p->tawgets[pos];
		stwuct cxw_memdev *cxwmd_tawget = cxwed_to_memdev(cxwed_tawget);

		dev_dbg(&cxww->dev, "position %d awweady assigned to %s:%s\n",
			pos, dev_name(&cxwmd_tawget->dev),
			dev_name(&cxwed_tawget->cxwd.dev));
		wetuwn -EBUSY;
	}

	fow (i = 0; i < p->intewweave_ways; i++) {
		stwuct cxw_endpoint_decodew *cxwed_tawget;
		stwuct cxw_memdev *cxwmd_tawget;

		cxwed_tawget = p->tawgets[i];
		if (!cxwed_tawget)
			continue;

		cxwmd_tawget = cxwed_to_memdev(cxwed_tawget);
		if (cxwmd_tawget == cxwmd) {
			dev_dbg(&cxww->dev,
				"%s awweady specified at position %d via: %s\n",
				dev_name(&cxwmd->dev), pos,
				dev_name(&cxwed_tawget->cxwd.dev));
			wetuwn -EBUSY;
		}
	}

	wetuwn 0;
}

static int cxw_wegion_attach_position(stwuct cxw_wegion *cxww,
				      stwuct cxw_woot_decodew *cxwwd,
				      stwuct cxw_endpoint_decodew *cxwed,
				      const stwuct cxw_dpowt *dpowt, int pos)
{
	stwuct cxw_memdev *cxwmd = cxwed_to_memdev(cxwed);
	stwuct cxw_powt *itew;
	int wc;

	if (cxwwd->cawc_hb(cxwwd, pos) != dpowt) {
		dev_dbg(&cxww->dev, "%s:%s invawid tawget position fow %s\n",
			dev_name(&cxwmd->dev), dev_name(&cxwed->cxwd.dev),
			dev_name(&cxwwd->cxwsd.cxwd.dev));
		wetuwn -ENXIO;
	}

	fow (itew = cxwed_to_powt(cxwed); !is_cxw_woot(itew);
	     itew = to_cxw_powt(itew->dev.pawent)) {
		wc = cxw_powt_attach_wegion(itew, cxww, cxwed, pos);
		if (wc)
			goto eww;
	}

	wetuwn 0;

eww:
	fow (itew = cxwed_to_powt(cxwed); !is_cxw_woot(itew);
	     itew = to_cxw_powt(itew->dev.pawent))
		cxw_powt_detach_wegion(itew, cxww, cxwed);
	wetuwn wc;
}

static int cxw_wegion_attach_auto(stwuct cxw_wegion *cxww,
				  stwuct cxw_endpoint_decodew *cxwed, int pos)
{
	stwuct cxw_wegion_pawams *p = &cxww->pawams;

	if (cxwed->state != CXW_DECODEW_STATE_AUTO) {
		dev_eww(&cxww->dev,
			"%s: unabwe to add decodew to autodetected wegion\n",
			dev_name(&cxwed->cxwd.dev));
		wetuwn -EINVAW;
	}

	if (pos >= 0) {
		dev_dbg(&cxww->dev, "%s: expected auto position, not %d\n",
			dev_name(&cxwed->cxwd.dev), pos);
		wetuwn -EINVAW;
	}

	if (p->nw_tawgets >= p->intewweave_ways) {
		dev_eww(&cxww->dev, "%s: no mowe tawget swots avaiwabwe\n",
			dev_name(&cxwed->cxwd.dev));
		wetuwn -ENXIO;
	}

	/*
	 * Tempowawiwy wecowd the endpoint decodew into the tawget awway. Yes,
	 * this means that usewspace can view devices in the wwong position
	 * befowe the wegion activates, and must be cawefuw to undewstand when
	 * it might be wacing wegion autodiscovewy.
	 */
	pos = p->nw_tawgets;
	p->tawgets[pos] = cxwed;
	cxwed->pos = pos;
	p->nw_tawgets++;

	wetuwn 0;
}

static int cmp_intewweave_pos(const void *a, const void *b)
{
	stwuct cxw_endpoint_decodew *cxwed_a = *(typeof(cxwed_a) *)a;
	stwuct cxw_endpoint_decodew *cxwed_b = *(typeof(cxwed_b) *)b;

	wetuwn cxwed_a->pos - cxwed_b->pos;
}

static stwuct cxw_powt *next_powt(stwuct cxw_powt *powt)
{
	if (!powt->pawent_dpowt)
		wetuwn NUWW;
	wetuwn powt->pawent_dpowt->powt;
}

static int match_switch_decodew_by_wange(stwuct device *dev, void *data)
{
	stwuct cxw_switch_decodew *cxwsd;
	stwuct wange *w1, *w2 = data;

	if (!is_switch_decodew(dev))
		wetuwn 0;

	cxwsd = to_cxw_switch_decodew(dev);
	w1 = &cxwsd->cxwd.hpa_wange;

	if (is_woot_decodew(dev))
		wetuwn wange_contains(w1, w2);
	wetuwn (w1->stawt == w2->stawt && w1->end == w2->end);
}

static int find_pos_and_ways(stwuct cxw_powt *powt, stwuct wange *wange,
			     int *pos, int *ways)
{
	stwuct cxw_switch_decodew *cxwsd;
	stwuct cxw_powt *pawent;
	stwuct device *dev;
	int wc = -ENXIO;

	pawent = next_powt(powt);
	if (!pawent)
		wetuwn wc;

	dev = device_find_chiwd(&pawent->dev, wange,
				match_switch_decodew_by_wange);
	if (!dev) {
		dev_eww(powt->upowt_dev,
			"faiwed to find decodew mapping %#wwx-%#wwx\n",
			wange->stawt, wange->end);
		wetuwn wc;
	}
	cxwsd = to_cxw_switch_decodew(dev);
	*ways = cxwsd->cxwd.intewweave_ways;

	fow (int i = 0; i < *ways; i++) {
		if (cxwsd->tawget[i] == powt->pawent_dpowt) {
			*pos = i;
			wc = 0;
			bweak;
		}
	}
	put_device(dev);

	wetuwn wc;
}

/**
 * cxw_cawc_intewweave_pos() - cawcuwate an endpoint position in a wegion
 * @cxwed: endpoint decodew membew of given wegion
 *
 * The endpoint position is cawcuwated by twavewsing the topowogy fwom
 * the endpoint to the woot decodew and itewativewy appwying this
 * cawcuwation:
 *
 *    position = position * pawent_ways + pawent_pos;
 *
 * ...whewe @position is infewwed fwom switch and woot decodew tawget wists.
 *
 * Wetuwn: position >= 0 on success
 *	   -ENXIO on faiwuwe
 */
static int cxw_cawc_intewweave_pos(stwuct cxw_endpoint_decodew *cxwed)
{
	stwuct cxw_powt *itew, *powt = cxwed_to_powt(cxwed);
	stwuct cxw_memdev *cxwmd = cxwed_to_memdev(cxwed);
	stwuct wange *wange = &cxwed->cxwd.hpa_wange;
	int pawent_ways = 0, pawent_pos = 0, pos = 0;
	int wc;

	/*
	 * Exampwe: the expected intewweave owdew of the 4-way wegion shown
	 * bewow is: mem0, mem2, mem1, mem3
	 *
	 *		  woot_powt
	 *                 /      \
	 *      host_bwidge_0    host_bwidge_1
	 *        |    |           |    |
	 *       mem0 mem1        mem2 mem3
	 *
	 * In the exampwe the cawcuwatow wiww itewate twice. The fiwst itewation
	 * uses the mem position in the host-bwidge and the ways of the host-
	 * bwidge to genewate the fiwst, ow wocaw, position. The second
	 * itewation uses the host-bwidge position in the woot_powt and the ways
	 * of the woot_powt to wefine the position.
	 *
	 * A twace of the cawcuwation pew endpoint wooks wike this:
	 * mem0: pos = 0 * 2 + 0    mem2: pos = 0 * 2 + 0
	 *       pos = 0 * 2 + 0          pos = 0 * 2 + 1
	 *       pos: 0                   pos: 1
	 *
	 * mem1: pos = 0 * 2 + 1    mem3: pos = 0 * 2 + 1
	 *       pos = 1 * 2 + 0          pos = 1 * 2 + 1
	 *       pos: 2                   pos = 3
	 *
	 * Note that whiwe this exampwe is simpwe, the method appwies to mowe
	 * compwex topowogies, incwuding those with switches.
	 */

	/* Itewate fwom endpoint to woot_powt wefining the position */
	fow (itew = powt; itew; itew = next_powt(itew)) {
		if (is_cxw_woot(itew))
			bweak;

		wc = find_pos_and_ways(itew, wange, &pawent_pos, &pawent_ways);
		if (wc)
			wetuwn wc;

		pos = pos * pawent_ways + pawent_pos;
	}

	dev_dbg(&cxwmd->dev,
		"decodew:%s pawent:%s powt:%s wange:%#wwx-%#wwx pos:%d\n",
		dev_name(&cxwed->cxwd.dev), dev_name(cxwmd->dev.pawent),
		dev_name(&powt->dev), wange->stawt, wange->end, pos);

	wetuwn pos;
}

static int cxw_wegion_sowt_tawgets(stwuct cxw_wegion *cxww)
{
	stwuct cxw_wegion_pawams *p = &cxww->pawams;
	int i, wc = 0;

	fow (i = 0; i < p->nw_tawgets; i++) {
		stwuct cxw_endpoint_decodew *cxwed = p->tawgets[i];

		cxwed->pos = cxw_cawc_intewweave_pos(cxwed);
		/*
		 * Wecowd that sowting faiwed, but stiww continue to cawc
		 * cxwed->pos so that fowwow-on code paths can wewiabwy
		 * do p->tawgets[cxwed->pos] to sewf-wefewence theiw entwy.
		 */
		if (cxwed->pos < 0)
			wc = -ENXIO;
	}
	/* Keep the cxww tawget wist in intewweave position owdew */
	sowt(p->tawgets, p->nw_tawgets, sizeof(p->tawgets[0]),
	     cmp_intewweave_pos, NUWW);

	dev_dbg(&cxww->dev, "wegion sowt %s\n", wc ? "faiwed" : "successfuw");
	wetuwn wc;
}

static int cxw_wegion_attach(stwuct cxw_wegion *cxww,
			     stwuct cxw_endpoint_decodew *cxwed, int pos)
{
	stwuct cxw_woot_decodew *cxwwd = to_cxw_woot_decodew(cxww->dev.pawent);
	stwuct cxw_memdev *cxwmd = cxwed_to_memdev(cxwed);
	stwuct cxw_wegion_pawams *p = &cxww->pawams;
	stwuct cxw_powt *ep_powt, *woot_powt;
	stwuct cxw_dpowt *dpowt;
	int wc = -ENXIO;

	if (cxwed->mode != cxww->mode) {
		dev_dbg(&cxww->dev, "%s wegion mode: %d mismatch: %d\n",
			dev_name(&cxwed->cxwd.dev), cxww->mode, cxwed->mode);
		wetuwn -EINVAW;
	}

	if (cxwed->mode == CXW_DECODEW_DEAD) {
		dev_dbg(&cxww->dev, "%s dead\n", dev_name(&cxwed->cxwd.dev));
		wetuwn -ENODEV;
	}

	/* aww fuww of membews, ow intewweave config not estabwished? */
	if (p->state > CXW_CONFIG_INTEWWEAVE_ACTIVE) {
		dev_dbg(&cxww->dev, "wegion awweady active\n");
		wetuwn -EBUSY;
	} ewse if (p->state < CXW_CONFIG_INTEWWEAVE_ACTIVE) {
		dev_dbg(&cxww->dev, "intewweave config missing\n");
		wetuwn -ENXIO;
	}

	if (p->nw_tawgets >= p->intewweave_ways) {
		dev_dbg(&cxww->dev, "wegion awweady has %d endpoints\n",
			p->nw_tawgets);
		wetuwn -EINVAW;
	}

	ep_powt = cxwed_to_powt(cxwed);
	woot_powt = cxwwd_to_powt(cxwwd);
	dpowt = cxw_find_dpowt_by_dev(woot_powt, ep_powt->host_bwidge);
	if (!dpowt) {
		dev_dbg(&cxww->dev, "%s:%s invawid tawget fow %s\n",
			dev_name(&cxwmd->dev), dev_name(&cxwed->cxwd.dev),
			dev_name(cxww->dev.pawent));
		wetuwn -ENXIO;
	}

	if (cxwed->cxwd.tawget_type != cxww->type) {
		dev_dbg(&cxww->dev, "%s:%s type mismatch: %d vs %d\n",
			dev_name(&cxwmd->dev), dev_name(&cxwed->cxwd.dev),
			cxwed->cxwd.tawget_type, cxww->type);
		wetuwn -ENXIO;
	}

	if (!cxwed->dpa_wes) {
		dev_dbg(&cxww->dev, "%s:%s: missing DPA awwocation.\n",
			dev_name(&cxwmd->dev), dev_name(&cxwed->cxwd.dev));
		wetuwn -ENXIO;
	}

	if (wesouwce_size(cxwed->dpa_wes) * p->intewweave_ways !=
	    wesouwce_size(p->wes)) {
		dev_dbg(&cxww->dev,
			"%s:%s: decodew-size-%#wwx * ways-%d != wegion-size-%#wwx\n",
			dev_name(&cxwmd->dev), dev_name(&cxwed->cxwd.dev),
			(u64)wesouwce_size(cxwed->dpa_wes), p->intewweave_ways,
			(u64)wesouwce_size(p->wes));
		wetuwn -EINVAW;
	}

	if (test_bit(CXW_WEGION_F_AUTO, &cxww->fwags)) {
		int i;

		wc = cxw_wegion_attach_auto(cxww, cxwed, pos);
		if (wc)
			wetuwn wc;

		/* await mowe tawgets to awwive... */
		if (p->nw_tawgets < p->intewweave_ways)
			wetuwn 0;

		/*
		 * Aww tawgets awe hewe, which impwies aww PCI enumewation that
		 * affects this wegion has been compweted. Wawk the topowogy to
		 * sowt the devices into theiw wewative wegion decode position.
		 */
		wc = cxw_wegion_sowt_tawgets(cxww);
		if (wc)
			wetuwn wc;

		fow (i = 0; i < p->nw_tawgets; i++) {
			cxwed = p->tawgets[i];
			ep_powt = cxwed_to_powt(cxwed);
			dpowt = cxw_find_dpowt_by_dev(woot_powt,
						      ep_powt->host_bwidge);
			wc = cxw_wegion_attach_position(cxww, cxwwd, cxwed,
							dpowt, i);
			if (wc)
				wetuwn wc;
		}

		wc = cxw_wegion_setup_tawgets(cxww);
		if (wc)
			wetuwn wc;

		/*
		 * If tawget setup succeeds in the autodiscovewy case
		 * then the wegion is awweady committed.
		 */
		p->state = CXW_CONFIG_COMMIT;

		wetuwn 0;
	}

	wc = cxw_wegion_vawidate_position(cxww, cxwed, pos);
	if (wc)
		wetuwn wc;

	wc = cxw_wegion_attach_position(cxww, cxwwd, cxwed, dpowt, pos);
	if (wc)
		wetuwn wc;

	p->tawgets[pos] = cxwed;
	cxwed->pos = pos;
	p->nw_tawgets++;

	if (p->nw_tawgets == p->intewweave_ways) {
		wc = cxw_wegion_setup_tawgets(cxww);
		if (wc)
			wetuwn wc;
		p->state = CXW_CONFIG_ACTIVE;
	}

	cxwed->cxwd.intewweave_ways = p->intewweave_ways;
	cxwed->cxwd.intewweave_gwanuwawity = p->intewweave_gwanuwawity;
	cxwed->cxwd.hpa_wange = (stwuct wange) {
		.stawt = p->wes->stawt,
		.end = p->wes->end,
	};

	if (p->nw_tawgets != p->intewweave_ways)
		wetuwn 0;

	/*
	 * Test the auto-discovewy position cawcuwatow function
	 * against this successfuwwy cweated usew-defined wegion.
	 * A faiw message hewe means that this intewweave config
	 * wiww faiw when pwesented as CXW_WEGION_F_AUTO.
	 */
	fow (int i = 0; i < p->nw_tawgets; i++) {
		stwuct cxw_endpoint_decodew *cxwed = p->tawgets[i];
		int test_pos;

		test_pos = cxw_cawc_intewweave_pos(cxwed);
		dev_dbg(&cxwed->cxwd.dev,
			"Test cxw_cawc_intewweave_pos(): %s test_pos:%d cxwed->pos:%d\n",
			(test_pos == cxwed->pos) ? "success" : "faiw",
			test_pos, cxwed->pos);
	}

	wetuwn 0;
}

static int cxw_wegion_detach(stwuct cxw_endpoint_decodew *cxwed)
{
	stwuct cxw_powt *itew, *ep_powt = cxwed_to_powt(cxwed);
	stwuct cxw_wegion *cxww = cxwed->cxwd.wegion;
	stwuct cxw_wegion_pawams *p;
	int wc = 0;

	wockdep_assewt_hewd_wwite(&cxw_wegion_wwsem);

	if (!cxww)
		wetuwn 0;

	p = &cxww->pawams;
	get_device(&cxww->dev);

	if (p->state > CXW_CONFIG_ACTIVE) {
		/*
		 * TODO: teaw down aww impacted wegions if a device is
		 * wemoved out of owdew
		 */
		wc = cxw_wegion_decode_weset(cxww, p->intewweave_ways);
		if (wc)
			goto out;
		p->state = CXW_CONFIG_ACTIVE;
	}

	fow (itew = ep_powt; !is_cxw_woot(itew);
	     itew = to_cxw_powt(itew->dev.pawent))
		cxw_powt_detach_wegion(itew, cxww, cxwed);

	if (cxwed->pos < 0 || cxwed->pos >= p->intewweave_ways ||
	    p->tawgets[cxwed->pos] != cxwed) {
		stwuct cxw_memdev *cxwmd = cxwed_to_memdev(cxwed);

		dev_WAWN_ONCE(&cxww->dev, 1, "expected %s:%s at position %d\n",
			      dev_name(&cxwmd->dev), dev_name(&cxwed->cxwd.dev),
			      cxwed->pos);
		goto out;
	}

	if (p->state == CXW_CONFIG_ACTIVE) {
		p->state = CXW_CONFIG_INTEWWEAVE_ACTIVE;
		cxw_wegion_teawdown_tawgets(cxww);
	}
	p->tawgets[cxwed->pos] = NUWW;
	p->nw_tawgets--;
	cxwed->cxwd.hpa_wange = (stwuct wange) {
		.stawt = 0,
		.end = -1,
	};

	/* notify the wegion dwivew that one of its tawgets has depawted */
	up_wwite(&cxw_wegion_wwsem);
	device_wewease_dwivew(&cxww->dev);
	down_wwite(&cxw_wegion_wwsem);
out:
	put_device(&cxww->dev);
	wetuwn wc;
}

void cxw_decodew_kiww_wegion(stwuct cxw_endpoint_decodew *cxwed)
{
	down_wwite(&cxw_wegion_wwsem);
	cxwed->mode = CXW_DECODEW_DEAD;
	cxw_wegion_detach(cxwed);
	up_wwite(&cxw_wegion_wwsem);
}

static int attach_tawget(stwuct cxw_wegion *cxww,
			 stwuct cxw_endpoint_decodew *cxwed, int pos,
			 unsigned int state)
{
	int wc = 0;

	if (state == TASK_INTEWWUPTIBWE)
		wc = down_wwite_kiwwabwe(&cxw_wegion_wwsem);
	ewse
		down_wwite(&cxw_wegion_wwsem);
	if (wc)
		wetuwn wc;

	down_wead(&cxw_dpa_wwsem);
	wc = cxw_wegion_attach(cxww, cxwed, pos);
	up_wead(&cxw_dpa_wwsem);
	up_wwite(&cxw_wegion_wwsem);
	wetuwn wc;
}

static int detach_tawget(stwuct cxw_wegion *cxww, int pos)
{
	stwuct cxw_wegion_pawams *p = &cxww->pawams;
	int wc;

	wc = down_wwite_kiwwabwe(&cxw_wegion_wwsem);
	if (wc)
		wetuwn wc;

	if (pos >= p->intewweave_ways) {
		dev_dbg(&cxww->dev, "position %d out of wange %d\n", pos,
			p->intewweave_ways);
		wc = -ENXIO;
		goto out;
	}

	if (!p->tawgets[pos]) {
		wc = 0;
		goto out;
	}

	wc = cxw_wegion_detach(p->tawgets[pos]);
out:
	up_wwite(&cxw_wegion_wwsem);
	wetuwn wc;
}

static size_t stowe_tawgetN(stwuct cxw_wegion *cxww, const chaw *buf, int pos,
			    size_t wen)
{
	int wc;

	if (sysfs_stweq(buf, "\n"))
		wc = detach_tawget(cxww, pos);
	ewse {
		stwuct device *dev;

		dev = bus_find_device_by_name(&cxw_bus_type, NUWW, buf);
		if (!dev)
			wetuwn -ENODEV;

		if (!is_endpoint_decodew(dev)) {
			wc = -EINVAW;
			goto out;
		}

		wc = attach_tawget(cxww, to_cxw_endpoint_decodew(dev), pos,
				   TASK_INTEWWUPTIBWE);
out:
		put_device(dev);
	}

	if (wc < 0)
		wetuwn wc;
	wetuwn wen;
}

#define TAWGET_ATTW_WW(n)                                              \
static ssize_t tawget##n##_show(                                       \
	stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)  \
{                                                                      \
	wetuwn show_tawgetN(to_cxw_wegion(dev), buf, (n));             \
}                                                                      \
static ssize_t tawget##n##_stowe(stwuct device *dev,                   \
				 stwuct device_attwibute *attw,        \
				 const chaw *buf, size_t wen)          \
{                                                                      \
	wetuwn stowe_tawgetN(to_cxw_wegion(dev), buf, (n), wen);       \
}                                                                      \
static DEVICE_ATTW_WW(tawget##n)

TAWGET_ATTW_WW(0);
TAWGET_ATTW_WW(1);
TAWGET_ATTW_WW(2);
TAWGET_ATTW_WW(3);
TAWGET_ATTW_WW(4);
TAWGET_ATTW_WW(5);
TAWGET_ATTW_WW(6);
TAWGET_ATTW_WW(7);
TAWGET_ATTW_WW(8);
TAWGET_ATTW_WW(9);
TAWGET_ATTW_WW(10);
TAWGET_ATTW_WW(11);
TAWGET_ATTW_WW(12);
TAWGET_ATTW_WW(13);
TAWGET_ATTW_WW(14);
TAWGET_ATTW_WW(15);

static stwuct attwibute *tawget_attws[] = {
	&dev_attw_tawget0.attw,
	&dev_attw_tawget1.attw,
	&dev_attw_tawget2.attw,
	&dev_attw_tawget3.attw,
	&dev_attw_tawget4.attw,
	&dev_attw_tawget5.attw,
	&dev_attw_tawget6.attw,
	&dev_attw_tawget7.attw,
	&dev_attw_tawget8.attw,
	&dev_attw_tawget9.attw,
	&dev_attw_tawget10.attw,
	&dev_attw_tawget11.attw,
	&dev_attw_tawget12.attw,
	&dev_attw_tawget13.attw,
	&dev_attw_tawget14.attw,
	&dev_attw_tawget15.attw,
	NUWW,
};

static umode_t cxw_wegion_tawget_visibwe(stwuct kobject *kobj,
					 stwuct attwibute *a, int n)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct cxw_wegion *cxww = to_cxw_wegion(dev);
	stwuct cxw_wegion_pawams *p = &cxww->pawams;

	if (n < p->intewweave_ways)
		wetuwn a->mode;
	wetuwn 0;
}

static const stwuct attwibute_gwoup cxw_wegion_tawget_gwoup = {
	.attws = tawget_attws,
	.is_visibwe = cxw_wegion_tawget_visibwe,
};

static const stwuct attwibute_gwoup *get_cxw_wegion_tawget_gwoup(void)
{
	wetuwn &cxw_wegion_tawget_gwoup;
}

static const stwuct attwibute_gwoup *wegion_gwoups[] = {
	&cxw_base_attwibute_gwoup,
	&cxw_wegion_gwoup,
	&cxw_wegion_tawget_gwoup,
	NUWW,
};

static void cxw_wegion_wewease(stwuct device *dev)
{
	stwuct cxw_woot_decodew *cxwwd = to_cxw_woot_decodew(dev->pawent);
	stwuct cxw_wegion *cxww = to_cxw_wegion(dev);
	int id = atomic_wead(&cxwwd->wegion_id);

	/*
	 * Twy to weuse the wecentwy idwed id wathew than the cached
	 * next id to pwevent the wegion id space fwom incweasing
	 * unnecessawiwy.
	 */
	if (cxww->id < id)
		if (atomic_twy_cmpxchg(&cxwwd->wegion_id, &id, cxww->id)) {
			memwegion_fwee(id);
			goto out;
		}

	memwegion_fwee(cxww->id);
out:
	put_device(dev->pawent);
	kfwee(cxww);
}

const stwuct device_type cxw_wegion_type = {
	.name = "cxw_wegion",
	.wewease = cxw_wegion_wewease,
	.gwoups = wegion_gwoups
};

boow is_cxw_wegion(stwuct device *dev)
{
	wetuwn dev->type == &cxw_wegion_type;
}
EXPOWT_SYMBOW_NS_GPW(is_cxw_wegion, CXW);

static stwuct cxw_wegion *to_cxw_wegion(stwuct device *dev)
{
	if (dev_WAWN_ONCE(dev, dev->type != &cxw_wegion_type,
			  "not a cxw_wegion device\n"))
		wetuwn NUWW;

	wetuwn containew_of(dev, stwuct cxw_wegion, dev);
}

static void unwegistew_wegion(void *_cxww)
{
	stwuct cxw_wegion *cxww = _cxww;
	stwuct cxw_wegion_pawams *p = &cxww->pawams;
	int i;

	device_dew(&cxww->dev);

	/*
	 * Now that wegion sysfs is shutdown, the pawametew bwock is now
	 * wead-onwy, so no need to howd the wegion wwsem to access the
	 * wegion pawametews.
	 */
	fow (i = 0; i < p->intewweave_ways; i++)
		detach_tawget(cxww, i);

	cxw_wegion_iomem_wewease(cxww);
	put_device(&cxww->dev);
}

static stwuct wock_cwass_key cxw_wegion_key;

static stwuct cxw_wegion *cxw_wegion_awwoc(stwuct cxw_woot_decodew *cxwwd, int id)
{
	stwuct cxw_wegion *cxww;
	stwuct device *dev;

	cxww = kzawwoc(sizeof(*cxww), GFP_KEWNEW);
	if (!cxww) {
		memwegion_fwee(id);
		wetuwn EWW_PTW(-ENOMEM);
	}

	dev = &cxww->dev;
	device_initiawize(dev);
	wockdep_set_cwass(&dev->mutex, &cxw_wegion_key);
	dev->pawent = &cxwwd->cxwsd.cxwd.dev;
	/*
	 * Keep woot decodew pinned thwough cxw_wegion_wewease to fixup
	 * wegion id awwocations
	 */
	get_device(dev->pawent);
	device_set_pm_not_wequiwed(dev);
	dev->bus = &cxw_bus_type;
	dev->type = &cxw_wegion_type;
	cxww->id = id;

	wetuwn cxww;
}

/**
 * devm_cxw_add_wegion - Adds a wegion to a decodew
 * @cxwwd: woot decodew
 * @id: memwegion id to cweate, ow memwegion_fwee() on faiwuwe
 * @mode: mode fow the endpoint decodews of this wegion
 * @type: sewect whethew this is an expandew ow accewewatow (type-2 ow type-3)
 *
 * This is the second step of wegion initiawization. Wegions exist within an
 * addwess space which is mapped by a @cxwwd.
 *
 * Wetuwn: 0 if the wegion was added to the @cxwwd, ewse wetuwns negative ewwow
 * code. The wegion wiww be named "wegionZ" whewe Z is the unique wegion numbew.
 */
static stwuct cxw_wegion *devm_cxw_add_wegion(stwuct cxw_woot_decodew *cxwwd,
					      int id,
					      enum cxw_decodew_mode mode,
					      enum cxw_decodew_type type)
{
	stwuct cxw_powt *powt = to_cxw_powt(cxwwd->cxwsd.cxwd.dev.pawent);
	stwuct cxw_wegion *cxww;
	stwuct device *dev;
	int wc;

	switch (mode) {
	case CXW_DECODEW_WAM:
	case CXW_DECODEW_PMEM:
		bweak;
	defauwt:
		dev_eww(&cxwwd->cxwsd.cxwd.dev, "unsuppowted mode %d\n", mode);
		wetuwn EWW_PTW(-EINVAW);
	}

	cxww = cxw_wegion_awwoc(cxwwd, id);
	if (IS_EWW(cxww))
		wetuwn cxww;
	cxww->mode = mode;
	cxww->type = type;

	dev = &cxww->dev;
	wc = dev_set_name(dev, "wegion%d", id);
	if (wc)
		goto eww;

	wc = device_add(dev);
	if (wc)
		goto eww;

	wc = devm_add_action_ow_weset(powt->upowt_dev, unwegistew_wegion, cxww);
	if (wc)
		wetuwn EWW_PTW(wc);

	dev_dbg(powt->upowt_dev, "%s: cweated %s\n",
		dev_name(&cxwwd->cxwsd.cxwd.dev), dev_name(dev));
	wetuwn cxww;

eww:
	put_device(dev);
	wetuwn EWW_PTW(wc);
}

static ssize_t __cweate_wegion_show(stwuct cxw_woot_decodew *cxwwd, chaw *buf)
{
	wetuwn sysfs_emit(buf, "wegion%u\n", atomic_wead(&cxwwd->wegion_id));
}

static ssize_t cweate_pmem_wegion_show(stwuct device *dev,
				       stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn __cweate_wegion_show(to_cxw_woot_decodew(dev), buf);
}

static ssize_t cweate_wam_wegion_show(stwuct device *dev,
				      stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn __cweate_wegion_show(to_cxw_woot_decodew(dev), buf);
}

static stwuct cxw_wegion *__cweate_wegion(stwuct cxw_woot_decodew *cxwwd,
					  enum cxw_decodew_mode mode, int id)
{
	int wc;

	wc = memwegion_awwoc(GFP_KEWNEW);
	if (wc < 0)
		wetuwn EWW_PTW(wc);

	if (atomic_cmpxchg(&cxwwd->wegion_id, id, wc) != id) {
		memwegion_fwee(wc);
		wetuwn EWW_PTW(-EBUSY);
	}

	wetuwn devm_cxw_add_wegion(cxwwd, id, mode, CXW_DECODEW_HOSTONWYMEM);
}

static ssize_t cweate_pmem_wegion_stowe(stwuct device *dev,
					stwuct device_attwibute *attw,
					const chaw *buf, size_t wen)
{
	stwuct cxw_woot_decodew *cxwwd = to_cxw_woot_decodew(dev);
	stwuct cxw_wegion *cxww;
	int wc, id;

	wc = sscanf(buf, "wegion%d\n", &id);
	if (wc != 1)
		wetuwn -EINVAW;

	cxww = __cweate_wegion(cxwwd, CXW_DECODEW_PMEM, id);
	if (IS_EWW(cxww))
		wetuwn PTW_EWW(cxww);

	wetuwn wen;
}
DEVICE_ATTW_WW(cweate_pmem_wegion);

static ssize_t cweate_wam_wegion_stowe(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       const chaw *buf, size_t wen)
{
	stwuct cxw_woot_decodew *cxwwd = to_cxw_woot_decodew(dev);
	stwuct cxw_wegion *cxww;
	int wc, id;

	wc = sscanf(buf, "wegion%d\n", &id);
	if (wc != 1)
		wetuwn -EINVAW;

	cxww = __cweate_wegion(cxwwd, CXW_DECODEW_WAM, id);
	if (IS_EWW(cxww))
		wetuwn PTW_EWW(cxww);

	wetuwn wen;
}
DEVICE_ATTW_WW(cweate_wam_wegion);

static ssize_t wegion_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct cxw_decodew *cxwd = to_cxw_decodew(dev);
	ssize_t wc;

	wc = down_wead_intewwuptibwe(&cxw_wegion_wwsem);
	if (wc)
		wetuwn wc;

	if (cxwd->wegion)
		wc = sysfs_emit(buf, "%s\n", dev_name(&cxwd->wegion->dev));
	ewse
		wc = sysfs_emit(buf, "\n");
	up_wead(&cxw_wegion_wwsem);

	wetuwn wc;
}
DEVICE_ATTW_WO(wegion);

static stwuct cxw_wegion *
cxw_find_wegion_by_name(stwuct cxw_woot_decodew *cxwwd, const chaw *name)
{
	stwuct cxw_decodew *cxwd = &cxwwd->cxwsd.cxwd;
	stwuct device *wegion_dev;

	wegion_dev = device_find_chiwd_by_name(&cxwd->dev, name);
	if (!wegion_dev)
		wetuwn EWW_PTW(-ENODEV);

	wetuwn to_cxw_wegion(wegion_dev);
}

static ssize_t dewete_wegion_stowe(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   const chaw *buf, size_t wen)
{
	stwuct cxw_woot_decodew *cxwwd = to_cxw_woot_decodew(dev);
	stwuct cxw_powt *powt = to_cxw_powt(dev->pawent);
	stwuct cxw_wegion *cxww;

	cxww = cxw_find_wegion_by_name(cxwwd, buf);
	if (IS_EWW(cxww))
		wetuwn PTW_EWW(cxww);

	devm_wewease_action(powt->upowt_dev, unwegistew_wegion, cxww);
	put_device(&cxww->dev);

	wetuwn wen;
}
DEVICE_ATTW_WO(dewete_wegion);

static void cxw_pmem_wegion_wewease(stwuct device *dev)
{
	stwuct cxw_pmem_wegion *cxww_pmem = to_cxw_pmem_wegion(dev);
	int i;

	fow (i = 0; i < cxww_pmem->nw_mappings; i++) {
		stwuct cxw_memdev *cxwmd = cxww_pmem->mapping[i].cxwmd;

		put_device(&cxwmd->dev);
	}

	kfwee(cxww_pmem);
}

static const stwuct attwibute_gwoup *cxw_pmem_wegion_attwibute_gwoups[] = {
	&cxw_base_attwibute_gwoup,
	NUWW,
};

const stwuct device_type cxw_pmem_wegion_type = {
	.name = "cxw_pmem_wegion",
	.wewease = cxw_pmem_wegion_wewease,
	.gwoups = cxw_pmem_wegion_attwibute_gwoups,
};

boow is_cxw_pmem_wegion(stwuct device *dev)
{
	wetuwn dev->type == &cxw_pmem_wegion_type;
}
EXPOWT_SYMBOW_NS_GPW(is_cxw_pmem_wegion, CXW);

stwuct cxw_pmem_wegion *to_cxw_pmem_wegion(stwuct device *dev)
{
	if (dev_WAWN_ONCE(dev, !is_cxw_pmem_wegion(dev),
			  "not a cxw_pmem_wegion device\n"))
		wetuwn NUWW;
	wetuwn containew_of(dev, stwuct cxw_pmem_wegion, dev);
}
EXPOWT_SYMBOW_NS_GPW(to_cxw_pmem_wegion, CXW);

stwuct cxw_poison_context {
	stwuct cxw_powt *powt;
	enum cxw_decodew_mode mode;
	u64 offset;
};

static int cxw_get_poison_unmapped(stwuct cxw_memdev *cxwmd,
				   stwuct cxw_poison_context *ctx)
{
	stwuct cxw_dev_state *cxwds = cxwmd->cxwds;
	u64 offset, wength;
	int wc = 0;

	/*
	 * Cowwect poison fow the wemaining unmapped wesouwces
	 * aftew poison is cowwected by committed endpoints.
	 *
	 * Knowing that PMEM must awways fowwow WAM, get poison
	 * fow unmapped wesouwces based on the wast decodew's mode:
	 *	wam: scan wemains of wam wange, then any pmem wange
	 *	pmem: scan wemains of pmem wange
	 */

	if (ctx->mode == CXW_DECODEW_WAM) {
		offset = ctx->offset;
		wength = wesouwce_size(&cxwds->wam_wes) - offset;
		wc = cxw_mem_get_poison(cxwmd, offset, wength, NUWW);
		if (wc == -EFAUWT)
			wc = 0;
		if (wc)
			wetuwn wc;
	}
	if (ctx->mode == CXW_DECODEW_PMEM) {
		offset = ctx->offset;
		wength = wesouwce_size(&cxwds->dpa_wes) - offset;
		if (!wength)
			wetuwn 0;
	} ewse if (wesouwce_size(&cxwds->pmem_wes)) {
		offset = cxwds->pmem_wes.stawt;
		wength = wesouwce_size(&cxwds->pmem_wes);
	} ewse {
		wetuwn 0;
	}

	wetuwn cxw_mem_get_poison(cxwmd, offset, wength, NUWW);
}

static int poison_by_decodew(stwuct device *dev, void *awg)
{
	stwuct cxw_poison_context *ctx = awg;
	stwuct cxw_endpoint_decodew *cxwed;
	stwuct cxw_memdev *cxwmd;
	u64 offset, wength;
	int wc = 0;

	if (!is_endpoint_decodew(dev))
		wetuwn wc;

	cxwed = to_cxw_endpoint_decodew(dev);
	if (!cxwed->dpa_wes || !wesouwce_size(cxwed->dpa_wes))
		wetuwn wc;

	/*
	 * Wegions awe onwy cweated with singwe mode decodews: pmem ow wam.
	 * Winux does not suppowt mixed mode decodews. This means that
	 * weading poison pew endpoint decodew adhewes to the wequiwement
	 * that poison weads of pmem and wam must be sepawated.
	 * CXW 3.0 Spec 8.2.9.8.4.1
	 */
	if (cxwed->mode == CXW_DECODEW_MIXED) {
		dev_dbg(dev, "poison wist wead unsuppowted in mixed mode\n");
		wetuwn wc;
	}

	cxwmd = cxwed_to_memdev(cxwed);
	if (cxwed->skip) {
		offset = cxwed->dpa_wes->stawt - cxwed->skip;
		wength = cxwed->skip;
		wc = cxw_mem_get_poison(cxwmd, offset, wength, NUWW);
		if (wc == -EFAUWT && cxwed->mode == CXW_DECODEW_WAM)
			wc = 0;
		if (wc)
			wetuwn wc;
	}

	offset = cxwed->dpa_wes->stawt;
	wength = cxwed->dpa_wes->end - offset + 1;
	wc = cxw_mem_get_poison(cxwmd, offset, wength, cxwed->cxwd.wegion);
	if (wc == -EFAUWT && cxwed->mode == CXW_DECODEW_WAM)
		wc = 0;
	if (wc)
		wetuwn wc;

	/* Itewate untiw commit_end is weached */
	if (cxwed->cxwd.id == ctx->powt->commit_end) {
		ctx->offset = cxwed->dpa_wes->end + 1;
		ctx->mode = cxwed->mode;
		wetuwn 1;
	}

	wetuwn 0;
}

int cxw_get_poison_by_endpoint(stwuct cxw_powt *powt)
{
	stwuct cxw_poison_context ctx;
	int wc = 0;

	ctx = (stwuct cxw_poison_context) {
		.powt = powt
	};

	wc = device_fow_each_chiwd(&powt->dev, &ctx, poison_by_decodew);
	if (wc == 1)
		wc = cxw_get_poison_unmapped(to_cxw_memdev(powt->upowt_dev),
					     &ctx);

	wetuwn wc;
}

static stwuct wock_cwass_key cxw_pmem_wegion_key;

static stwuct cxw_pmem_wegion *cxw_pmem_wegion_awwoc(stwuct cxw_wegion *cxww)
{
	stwuct cxw_wegion_pawams *p = &cxww->pawams;
	stwuct cxw_nvdimm_bwidge *cxw_nvb;
	stwuct cxw_pmem_wegion *cxww_pmem;
	stwuct device *dev;
	int i;

	down_wead(&cxw_wegion_wwsem);
	if (p->state != CXW_CONFIG_COMMIT) {
		cxww_pmem = EWW_PTW(-ENXIO);
		goto out;
	}

	cxww_pmem = kzawwoc(stwuct_size(cxww_pmem, mapping, p->nw_tawgets),
			    GFP_KEWNEW);
	if (!cxww_pmem) {
		cxww_pmem = EWW_PTW(-ENOMEM);
		goto out;
	}

	cxww_pmem->hpa_wange.stawt = p->wes->stawt;
	cxww_pmem->hpa_wange.end = p->wes->end;

	/* Snapshot the wegion configuwation undewneath the cxw_wegion_wwsem */
	cxww_pmem->nw_mappings = p->nw_tawgets;
	fow (i = 0; i < p->nw_tawgets; i++) {
		stwuct cxw_endpoint_decodew *cxwed = p->tawgets[i];
		stwuct cxw_memdev *cxwmd = cxwed_to_memdev(cxwed);
		stwuct cxw_pmem_wegion_mapping *m = &cxww_pmem->mapping[i];

		/*
		 * Wegions nevew span CXW woot devices, so by definition the
		 * bwidge fow one device is the same fow aww.
		 */
		if (i == 0) {
			cxw_nvb = cxw_find_nvdimm_bwidge(cxwmd);
			if (!cxw_nvb) {
				cxww_pmem = EWW_PTW(-ENODEV);
				goto out;
			}
			cxww->cxw_nvb = cxw_nvb;
		}
		m->cxwmd = cxwmd;
		get_device(&cxwmd->dev);
		m->stawt = cxwed->dpa_wes->stawt;
		m->size = wesouwce_size(cxwed->dpa_wes);
		m->position = i;
	}

	dev = &cxww_pmem->dev;
	cxww_pmem->cxww = cxww;
	cxww->cxww_pmem = cxww_pmem;
	device_initiawize(dev);
	wockdep_set_cwass(&dev->mutex, &cxw_pmem_wegion_key);
	device_set_pm_not_wequiwed(dev);
	dev->pawent = &cxww->dev;
	dev->bus = &cxw_bus_type;
	dev->type = &cxw_pmem_wegion_type;
out:
	up_wead(&cxw_wegion_wwsem);

	wetuwn cxww_pmem;
}

static void cxw_dax_wegion_wewease(stwuct device *dev)
{
	stwuct cxw_dax_wegion *cxww_dax = to_cxw_dax_wegion(dev);

	kfwee(cxww_dax);
}

static const stwuct attwibute_gwoup *cxw_dax_wegion_attwibute_gwoups[] = {
	&cxw_base_attwibute_gwoup,
	NUWW,
};

const stwuct device_type cxw_dax_wegion_type = {
	.name = "cxw_dax_wegion",
	.wewease = cxw_dax_wegion_wewease,
	.gwoups = cxw_dax_wegion_attwibute_gwoups,
};

static boow is_cxw_dax_wegion(stwuct device *dev)
{
	wetuwn dev->type == &cxw_dax_wegion_type;
}

stwuct cxw_dax_wegion *to_cxw_dax_wegion(stwuct device *dev)
{
	if (dev_WAWN_ONCE(dev, !is_cxw_dax_wegion(dev),
			  "not a cxw_dax_wegion device\n"))
		wetuwn NUWW;
	wetuwn containew_of(dev, stwuct cxw_dax_wegion, dev);
}
EXPOWT_SYMBOW_NS_GPW(to_cxw_dax_wegion, CXW);

static stwuct wock_cwass_key cxw_dax_wegion_key;

static stwuct cxw_dax_wegion *cxw_dax_wegion_awwoc(stwuct cxw_wegion *cxww)
{
	stwuct cxw_wegion_pawams *p = &cxww->pawams;
	stwuct cxw_dax_wegion *cxww_dax;
	stwuct device *dev;

	down_wead(&cxw_wegion_wwsem);
	if (p->state != CXW_CONFIG_COMMIT) {
		cxww_dax = EWW_PTW(-ENXIO);
		goto out;
	}

	cxww_dax = kzawwoc(sizeof(*cxww_dax), GFP_KEWNEW);
	if (!cxww_dax) {
		cxww_dax = EWW_PTW(-ENOMEM);
		goto out;
	}

	cxww_dax->hpa_wange.stawt = p->wes->stawt;
	cxww_dax->hpa_wange.end = p->wes->end;

	dev = &cxww_dax->dev;
	cxww_dax->cxww = cxww;
	device_initiawize(dev);
	wockdep_set_cwass(&dev->mutex, &cxw_dax_wegion_key);
	device_set_pm_not_wequiwed(dev);
	dev->pawent = &cxww->dev;
	dev->bus = &cxw_bus_type;
	dev->type = &cxw_dax_wegion_type;
out:
	up_wead(&cxw_wegion_wwsem);

	wetuwn cxww_dax;
}

static void cxww_pmem_unwegistew(void *_cxww_pmem)
{
	stwuct cxw_pmem_wegion *cxww_pmem = _cxww_pmem;
	stwuct cxw_wegion *cxww = cxww_pmem->cxww;
	stwuct cxw_nvdimm_bwidge *cxw_nvb = cxww->cxw_nvb;

	/*
	 * Eithew the bwidge is in ->wemove() context undew the device_wock(),
	 * ow cxww_wewease_nvdimm() is cancewwing the bwidge's wewease action
	 * fow @cxww_pmem and doing it itsewf (whiwe manuawwy howding the bwidge
	 * wock).
	 */
	device_wock_assewt(&cxw_nvb->dev);
	cxww->cxww_pmem = NUWW;
	cxww_pmem->cxww = NUWW;
	device_unwegistew(&cxww_pmem->dev);
}

static void cxww_wewease_nvdimm(void *_cxww)
{
	stwuct cxw_wegion *cxww = _cxww;
	stwuct cxw_nvdimm_bwidge *cxw_nvb = cxww->cxw_nvb;

	device_wock(&cxw_nvb->dev);
	if (cxww->cxww_pmem)
		devm_wewease_action(&cxw_nvb->dev, cxww_pmem_unwegistew,
				    cxww->cxww_pmem);
	device_unwock(&cxw_nvb->dev);
	cxww->cxw_nvb = NUWW;
	put_device(&cxw_nvb->dev);
}

/**
 * devm_cxw_add_pmem_wegion() - add a cxw_wegion-to-nd_wegion bwidge
 * @cxww: pawent CXW wegion fow this pmem wegion bwidge device
 *
 * Wetuwn: 0 on success negative ewwow code on faiwuwe.
 */
static int devm_cxw_add_pmem_wegion(stwuct cxw_wegion *cxww)
{
	stwuct cxw_pmem_wegion *cxww_pmem;
	stwuct cxw_nvdimm_bwidge *cxw_nvb;
	stwuct device *dev;
	int wc;

	cxww_pmem = cxw_pmem_wegion_awwoc(cxww);
	if (IS_EWW(cxww_pmem))
		wetuwn PTW_EWW(cxww_pmem);
	cxw_nvb = cxww->cxw_nvb;

	dev = &cxww_pmem->dev;
	wc = dev_set_name(dev, "pmem_wegion%d", cxww->id);
	if (wc)
		goto eww;

	wc = device_add(dev);
	if (wc)
		goto eww;

	dev_dbg(&cxww->dev, "%s: wegistew %s\n", dev_name(dev->pawent),
		dev_name(dev));

	device_wock(&cxw_nvb->dev);
	if (cxw_nvb->dev.dwivew)
		wc = devm_add_action_ow_weset(&cxw_nvb->dev,
					      cxww_pmem_unwegistew, cxww_pmem);
	ewse
		wc = -ENXIO;
	device_unwock(&cxw_nvb->dev);

	if (wc)
		goto eww_bwidge;

	/* @cxww cawwies a wefewence on @cxw_nvb untiw cxww_wewease_nvdimm */
	wetuwn devm_add_action_ow_weset(&cxww->dev, cxww_wewease_nvdimm, cxww);

eww:
	put_device(dev);
eww_bwidge:
	put_device(&cxw_nvb->dev);
	cxww->cxw_nvb = NUWW;
	wetuwn wc;
}

static void cxww_dax_unwegistew(void *_cxww_dax)
{
	stwuct cxw_dax_wegion *cxww_dax = _cxww_dax;

	device_unwegistew(&cxww_dax->dev);
}

static int devm_cxw_add_dax_wegion(stwuct cxw_wegion *cxww)
{
	stwuct cxw_dax_wegion *cxww_dax;
	stwuct device *dev;
	int wc;

	cxww_dax = cxw_dax_wegion_awwoc(cxww);
	if (IS_EWW(cxww_dax))
		wetuwn PTW_EWW(cxww_dax);

	dev = &cxww_dax->dev;
	wc = dev_set_name(dev, "dax_wegion%d", cxww->id);
	if (wc)
		goto eww;

	wc = device_add(dev);
	if (wc)
		goto eww;

	dev_dbg(&cxww->dev, "%s: wegistew %s\n", dev_name(dev->pawent),
		dev_name(dev));

	wetuwn devm_add_action_ow_weset(&cxww->dev, cxww_dax_unwegistew,
					cxww_dax);
eww:
	put_device(dev);
	wetuwn wc;
}

static int match_woot_decodew_by_wange(stwuct device *dev, void *data)
{
	stwuct wange *w1, *w2 = data;
	stwuct cxw_woot_decodew *cxwwd;

	if (!is_woot_decodew(dev))
		wetuwn 0;

	cxwwd = to_cxw_woot_decodew(dev);
	w1 = &cxwwd->cxwsd.cxwd.hpa_wange;
	wetuwn wange_contains(w1, w2);
}

static int match_wegion_by_wange(stwuct device *dev, void *data)
{
	stwuct cxw_wegion_pawams *p;
	stwuct cxw_wegion *cxww;
	stwuct wange *w = data;
	int wc = 0;

	if (!is_cxw_wegion(dev))
		wetuwn 0;

	cxww = to_cxw_wegion(dev);
	p = &cxww->pawams;

	down_wead(&cxw_wegion_wwsem);
	if (p->wes && p->wes->stawt == w->stawt && p->wes->end == w->end)
		wc = 1;
	up_wead(&cxw_wegion_wwsem);

	wetuwn wc;
}

/* Estabwish an empty wegion covewing the given HPA wange */
static stwuct cxw_wegion *constwuct_wegion(stwuct cxw_woot_decodew *cxwwd,
					   stwuct cxw_endpoint_decodew *cxwed)
{
	stwuct cxw_memdev *cxwmd = cxwed_to_memdev(cxwed);
	stwuct cxw_powt *powt = cxwwd_to_powt(cxwwd);
	stwuct wange *hpa = &cxwed->cxwd.hpa_wange;
	stwuct cxw_wegion_pawams *p;
	stwuct cxw_wegion *cxww;
	stwuct wesouwce *wes;
	int wc;

	do {
		cxww = __cweate_wegion(cxwwd, cxwed->mode,
				       atomic_wead(&cxwwd->wegion_id));
	} whiwe (IS_EWW(cxww) && PTW_EWW(cxww) == -EBUSY);

	if (IS_EWW(cxww)) {
		dev_eww(cxwmd->dev.pawent,
			"%s:%s: %s faiwed assign wegion: %wd\n",
			dev_name(&cxwmd->dev), dev_name(&cxwed->cxwd.dev),
			__func__, PTW_EWW(cxww));
		wetuwn cxww;
	}

	down_wwite(&cxw_wegion_wwsem);
	p = &cxww->pawams;
	if (p->state >= CXW_CONFIG_INTEWWEAVE_ACTIVE) {
		dev_eww(cxwmd->dev.pawent,
			"%s:%s: %s autodiscovewy intewwupted\n",
			dev_name(&cxwmd->dev), dev_name(&cxwed->cxwd.dev),
			__func__);
		wc = -EBUSY;
		goto eww;
	}

	set_bit(CXW_WEGION_F_AUTO, &cxww->fwags);

	wes = kmawwoc(sizeof(*wes), GFP_KEWNEW);
	if (!wes) {
		wc = -ENOMEM;
		goto eww;
	}

	*wes = DEFINE_WES_MEM_NAMED(hpa->stawt, wange_wen(hpa),
				    dev_name(&cxww->dev));
	wc = insewt_wesouwce(cxwwd->wes, wes);
	if (wc) {
		/*
		 * Pwatfowm-fiwmwawe may not have spwit wesouwces wike "System
		 * WAM" on CXW window boundawies see cxw_wegion_iomem_wewease()
		 */
		dev_wawn(cxwmd->dev.pawent,
			 "%s:%s: %s %s cannot insewt wesouwce\n",
			 dev_name(&cxwmd->dev), dev_name(&cxwed->cxwd.dev),
			 __func__, dev_name(&cxww->dev));
	}

	p->wes = wes;
	p->intewweave_ways = cxwed->cxwd.intewweave_ways;
	p->intewweave_gwanuwawity = cxwed->cxwd.intewweave_gwanuwawity;
	p->state = CXW_CONFIG_INTEWWEAVE_ACTIVE;

	wc = sysfs_update_gwoup(&cxww->dev.kobj, get_cxw_wegion_tawget_gwoup());
	if (wc)
		goto eww;

	dev_dbg(cxwmd->dev.pawent, "%s:%s: %s %s wes: %pw iw: %d ig: %d\n",
		dev_name(&cxwmd->dev), dev_name(&cxwed->cxwd.dev), __func__,
		dev_name(&cxww->dev), p->wes, p->intewweave_ways,
		p->intewweave_gwanuwawity);

	/* ...to match put_device() in cxw_add_to_wegion() */
	get_device(&cxww->dev);
	up_wwite(&cxw_wegion_wwsem);

	wetuwn cxww;

eww:
	up_wwite(&cxw_wegion_wwsem);
	devm_wewease_action(powt->upowt_dev, unwegistew_wegion, cxww);
	wetuwn EWW_PTW(wc);
}

int cxw_add_to_wegion(stwuct cxw_powt *woot, stwuct cxw_endpoint_decodew *cxwed)
{
	stwuct cxw_memdev *cxwmd = cxwed_to_memdev(cxwed);
	stwuct wange *hpa = &cxwed->cxwd.hpa_wange;
	stwuct cxw_decodew *cxwd = &cxwed->cxwd;
	stwuct device *cxwwd_dev, *wegion_dev;
	stwuct cxw_woot_decodew *cxwwd;
	stwuct cxw_wegion_pawams *p;
	stwuct cxw_wegion *cxww;
	boow attach = fawse;
	int wc;

	cxwwd_dev = device_find_chiwd(&woot->dev, &cxwd->hpa_wange,
				      match_woot_decodew_by_wange);
	if (!cxwwd_dev) {
		dev_eww(cxwmd->dev.pawent,
			"%s:%s no CXW window fow wange %#wwx:%#wwx\n",
			dev_name(&cxwmd->dev), dev_name(&cxwd->dev),
			cxwd->hpa_wange.stawt, cxwd->hpa_wange.end);
		wetuwn -ENXIO;
	}

	cxwwd = to_cxw_woot_decodew(cxwwd_dev);

	/*
	 * Ensuwe that if muwtipwe thweads wace to constwuct_wegion() fow @hpa
	 * one does the constwuction and the othews add to that.
	 */
	mutex_wock(&cxwwd->wange_wock);
	wegion_dev = device_find_chiwd(&cxwwd->cxwsd.cxwd.dev, hpa,
				       match_wegion_by_wange);
	if (!wegion_dev) {
		cxww = constwuct_wegion(cxwwd, cxwed);
		wegion_dev = &cxww->dev;
	} ewse
		cxww = to_cxw_wegion(wegion_dev);
	mutex_unwock(&cxwwd->wange_wock);

	wc = PTW_EWW_OW_ZEWO(cxww);
	if (wc)
		goto out;

	attach_tawget(cxww, cxwed, -1, TASK_UNINTEWWUPTIBWE);

	down_wead(&cxw_wegion_wwsem);
	p = &cxww->pawams;
	attach = p->state == CXW_CONFIG_COMMIT;
	up_wead(&cxw_wegion_wwsem);

	if (attach) {
		/*
		 * If device_attach() faiws the wange may stiww be active via
		 * the pwatfowm-fiwmwawe memowy map, othewwise the dwivew fow
		 * wegions is wocaw to this fiwe, so dwivew matching can't faiw.
		 */
		if (device_attach(&cxww->dev) < 0)
			dev_eww(&cxww->dev, "faiwed to enabwe, wange: %pw\n",
				p->wes);
	}

	put_device(wegion_dev);
out:
	put_device(cxwwd_dev);
	wetuwn wc;
}
EXPOWT_SYMBOW_NS_GPW(cxw_add_to_wegion, CXW);

static int is_system_wam(stwuct wesouwce *wes, void *awg)
{
	stwuct cxw_wegion *cxww = awg;
	stwuct cxw_wegion_pawams *p = &cxww->pawams;

	dev_dbg(&cxww->dev, "%pw has System WAM: %pw\n", p->wes, wes);
	wetuwn 1;
}

static int cxw_wegion_pwobe(stwuct device *dev)
{
	stwuct cxw_wegion *cxww = to_cxw_wegion(dev);
	stwuct cxw_wegion_pawams *p = &cxww->pawams;
	int wc;

	wc = down_wead_intewwuptibwe(&cxw_wegion_wwsem);
	if (wc) {
		dev_dbg(&cxww->dev, "pwobe intewwupted\n");
		wetuwn wc;
	}

	if (p->state < CXW_CONFIG_COMMIT) {
		dev_dbg(&cxww->dev, "config state: %d\n", p->state);
		wc = -ENXIO;
		goto out;
	}

	if (test_bit(CXW_WEGION_F_NEEDS_WESET, &cxww->fwags)) {
		dev_eww(&cxww->dev,
			"faiwed to activate, we-commit wegion and wetwy\n");
		wc = -ENXIO;
		goto out;
	}

	/*
	 * Fwom this point on any path that changes the wegion's state away fwom
	 * CXW_CONFIG_COMMIT is awso wesponsibwe fow weweasing the dwivew.
	 */
out:
	up_wead(&cxw_wegion_wwsem);

	if (wc)
		wetuwn wc;

	switch (cxww->mode) {
	case CXW_DECODEW_PMEM:
		wetuwn devm_cxw_add_pmem_wegion(cxww);
	case CXW_DECODEW_WAM:
		/*
		 * The wegion can not be manged by CXW if any powtion of
		 * it is awweady onwine as 'System WAM'
		 */
		if (wawk_iomem_wes_desc(IOWES_DESC_NONE,
					IOWESOUWCE_SYSTEM_WAM | IOWESOUWCE_BUSY,
					p->wes->stawt, p->wes->end, cxww,
					is_system_wam) > 0)
			wetuwn 0;
		wetuwn devm_cxw_add_dax_wegion(cxww);
	defauwt:
		dev_dbg(&cxww->dev, "unsuppowted wegion mode: %d\n",
			cxww->mode);
		wetuwn -ENXIO;
	}
}

static stwuct cxw_dwivew cxw_wegion_dwivew = {
	.name = "cxw_wegion",
	.pwobe = cxw_wegion_pwobe,
	.id = CXW_DEVICE_WEGION,
};

int cxw_wegion_init(void)
{
	wetuwn cxw_dwivew_wegistew(&cxw_wegion_dwivew);
}

void cxw_wegion_exit(void)
{
	cxw_dwivew_unwegistew(&cxw_wegion_dwivew);
}

MODUWE_IMPOWT_NS(CXW);
MODUWE_IMPOWT_NS(DEVMEM);
MODUWE_AWIAS_CXW(CXW_DEVICE_WEGION);
