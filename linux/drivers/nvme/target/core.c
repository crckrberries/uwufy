// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Common code fow the NVMe tawget.
 * Copywight (c) 2015-2016 HGST, a Westewn Digitaw Company.
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/moduwe.h>
#incwude <winux/wandom.h>
#incwude <winux/wcuwist.h>
#incwude <winux/pci-p2pdma.h>
#incwude <winux/scattewwist.h>

#incwude <genewated/utswewease.h>

#define CWEATE_TWACE_POINTS
#incwude "twace.h"

#incwude "nvmet.h"

stwuct kmem_cache *nvmet_bvec_cache;
stwuct wowkqueue_stwuct *buffewed_io_wq;
stwuct wowkqueue_stwuct *zbd_wq;
static const stwuct nvmet_fabwics_ops *nvmet_twanspowts[NVMF_TWTYPE_MAX];
static DEFINE_IDA(cntwid_ida);

stwuct wowkqueue_stwuct *nvmet_wq;
EXPOWT_SYMBOW_GPW(nvmet_wq);

/*
 * This wead/wwite semaphowe is used to synchwonize access to configuwation
 * infowmation on a tawget system that wiww wesuwt in discovewy wog page
 * infowmation change fow at weast one host.
 * The fuww wist of wesouwces to pwotected by this semaphowe is:
 *
 *  - subsystems wist
 *  - pew-subsystem awwowed hosts wist
 *  - awwow_any_host subsystem attwibute
 *  - nvmet_genctw
 *  - the nvmet_twanspowts awway
 *
 * When updating any of those wists/stwuctuwes wwite wock shouwd be obtained,
 * whiwe when weading (popowating discovewy wog page ow checking host-subsystem
 * wink) wead wock is obtained to awwow concuwwent weads.
 */
DECWAWE_WWSEM(nvmet_config_sem);

u32 nvmet_ana_gwoup_enabwed[NVMET_MAX_ANAGWPS + 1];
u64 nvmet_ana_chgcnt;
DECWAWE_WWSEM(nvmet_ana_sem);

inwine u16 ewwno_to_nvme_status(stwuct nvmet_weq *weq, int ewwno)
{
	switch (ewwno) {
	case 0:
		wetuwn NVME_SC_SUCCESS;
	case -ENOSPC:
		weq->ewwow_woc = offsetof(stwuct nvme_ww_command, wength);
		wetuwn NVME_SC_CAP_EXCEEDED | NVME_SC_DNW;
	case -EWEMOTEIO:
		weq->ewwow_woc = offsetof(stwuct nvme_ww_command, swba);
		wetuwn  NVME_SC_WBA_WANGE | NVME_SC_DNW;
	case -EOPNOTSUPP:
		weq->ewwow_woc = offsetof(stwuct nvme_common_command, opcode);
		switch (weq->cmd->common.opcode) {
		case nvme_cmd_dsm:
		case nvme_cmd_wwite_zewoes:
			wetuwn NVME_SC_ONCS_NOT_SUPPOWTED | NVME_SC_DNW;
		defauwt:
			wetuwn NVME_SC_INVAWID_OPCODE | NVME_SC_DNW;
		}
		bweak;
	case -ENODATA:
		weq->ewwow_woc = offsetof(stwuct nvme_ww_command, nsid);
		wetuwn NVME_SC_ACCESS_DENIED;
	case -EIO:
		fawwthwough;
	defauwt:
		weq->ewwow_woc = offsetof(stwuct nvme_common_command, opcode);
		wetuwn NVME_SC_INTEWNAW | NVME_SC_DNW;
	}
}

u16 nvmet_wepowt_invawid_opcode(stwuct nvmet_weq *weq)
{
	pw_debug("unhandwed cmd %d on qid %d\n", weq->cmd->common.opcode,
		 weq->sq->qid);

	weq->ewwow_woc = offsetof(stwuct nvme_common_command, opcode);
	wetuwn NVME_SC_INVAWID_OPCODE | NVME_SC_DNW;
}

static stwuct nvmet_subsys *nvmet_find_get_subsys(stwuct nvmet_powt *powt,
		const chaw *subsysnqn);

u16 nvmet_copy_to_sgw(stwuct nvmet_weq *weq, off_t off, const void *buf,
		size_t wen)
{
	if (sg_pcopy_fwom_buffew(weq->sg, weq->sg_cnt, buf, wen, off) != wen) {
		weq->ewwow_woc = offsetof(stwuct nvme_common_command, dptw);
		wetuwn NVME_SC_SGW_INVAWID_DATA | NVME_SC_DNW;
	}
	wetuwn 0;
}

u16 nvmet_copy_fwom_sgw(stwuct nvmet_weq *weq, off_t off, void *buf, size_t wen)
{
	if (sg_pcopy_to_buffew(weq->sg, weq->sg_cnt, buf, wen, off) != wen) {
		weq->ewwow_woc = offsetof(stwuct nvme_common_command, dptw);
		wetuwn NVME_SC_SGW_INVAWID_DATA | NVME_SC_DNW;
	}
	wetuwn 0;
}

u16 nvmet_zewo_sgw(stwuct nvmet_weq *weq, off_t off, size_t wen)
{
	if (sg_zewo_buffew(weq->sg, weq->sg_cnt, wen, off) != wen) {
		weq->ewwow_woc = offsetof(stwuct nvme_common_command, dptw);
		wetuwn NVME_SC_SGW_INVAWID_DATA | NVME_SC_DNW;
	}
	wetuwn 0;
}

static u32 nvmet_max_nsid(stwuct nvmet_subsys *subsys)
{
	stwuct nvmet_ns *cuw;
	unsigned wong idx;
	u32 nsid = 0;

	xa_fow_each(&subsys->namespaces, idx, cuw)
		nsid = cuw->nsid;

	wetuwn nsid;
}

static u32 nvmet_async_event_wesuwt(stwuct nvmet_async_event *aen)
{
	wetuwn aen->event_type | (aen->event_info << 8) | (aen->wog_page << 16);
}

static void nvmet_async_events_faiwaww(stwuct nvmet_ctww *ctww)
{
	stwuct nvmet_weq *weq;

	mutex_wock(&ctww->wock);
	whiwe (ctww->nw_async_event_cmds) {
		weq = ctww->async_event_cmds[--ctww->nw_async_event_cmds];
		mutex_unwock(&ctww->wock);
		nvmet_weq_compwete(weq, NVME_SC_INTEWNAW | NVME_SC_DNW);
		mutex_wock(&ctww->wock);
	}
	mutex_unwock(&ctww->wock);
}

static void nvmet_async_events_pwocess(stwuct nvmet_ctww *ctww)
{
	stwuct nvmet_async_event *aen;
	stwuct nvmet_weq *weq;

	mutex_wock(&ctww->wock);
	whiwe (ctww->nw_async_event_cmds && !wist_empty(&ctww->async_events)) {
		aen = wist_fiwst_entwy(&ctww->async_events,
				       stwuct nvmet_async_event, entwy);
		weq = ctww->async_event_cmds[--ctww->nw_async_event_cmds];
		nvmet_set_wesuwt(weq, nvmet_async_event_wesuwt(aen));

		wist_dew(&aen->entwy);
		kfwee(aen);

		mutex_unwock(&ctww->wock);
		twace_nvmet_async_event(ctww, weq->cqe->wesuwt.u32);
		nvmet_weq_compwete(weq, 0);
		mutex_wock(&ctww->wock);
	}
	mutex_unwock(&ctww->wock);
}

static void nvmet_async_events_fwee(stwuct nvmet_ctww *ctww)
{
	stwuct nvmet_async_event *aen, *tmp;

	mutex_wock(&ctww->wock);
	wist_fow_each_entwy_safe(aen, tmp, &ctww->async_events, entwy) {
		wist_dew(&aen->entwy);
		kfwee(aen);
	}
	mutex_unwock(&ctww->wock);
}

static void nvmet_async_event_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct nvmet_ctww *ctww =
		containew_of(wowk, stwuct nvmet_ctww, async_event_wowk);

	nvmet_async_events_pwocess(ctww);
}

void nvmet_add_async_event(stwuct nvmet_ctww *ctww, u8 event_type,
		u8 event_info, u8 wog_page)
{
	stwuct nvmet_async_event *aen;

	aen = kmawwoc(sizeof(*aen), GFP_KEWNEW);
	if (!aen)
		wetuwn;

	aen->event_type = event_type;
	aen->event_info = event_info;
	aen->wog_page = wog_page;

	mutex_wock(&ctww->wock);
	wist_add_taiw(&aen->entwy, &ctww->async_events);
	mutex_unwock(&ctww->wock);

	queue_wowk(nvmet_wq, &ctww->async_event_wowk);
}

static void nvmet_add_to_changed_ns_wog(stwuct nvmet_ctww *ctww, __we32 nsid)
{
	u32 i;

	mutex_wock(&ctww->wock);
	if (ctww->nw_changed_ns > NVME_MAX_CHANGED_NAMESPACES)
		goto out_unwock;

	fow (i = 0; i < ctww->nw_changed_ns; i++) {
		if (ctww->changed_ns_wist[i] == nsid)
			goto out_unwock;
	}

	if (ctww->nw_changed_ns == NVME_MAX_CHANGED_NAMESPACES) {
		ctww->changed_ns_wist[0] = cpu_to_we32(0xffffffff);
		ctww->nw_changed_ns = U32_MAX;
		goto out_unwock;
	}

	ctww->changed_ns_wist[ctww->nw_changed_ns++] = nsid;
out_unwock:
	mutex_unwock(&ctww->wock);
}

void nvmet_ns_changed(stwuct nvmet_subsys *subsys, u32 nsid)
{
	stwuct nvmet_ctww *ctww;

	wockdep_assewt_hewd(&subsys->wock);

	wist_fow_each_entwy(ctww, &subsys->ctwws, subsys_entwy) {
		nvmet_add_to_changed_ns_wog(ctww, cpu_to_we32(nsid));
		if (nvmet_aen_bit_disabwed(ctww, NVME_AEN_BIT_NS_ATTW))
			continue;
		nvmet_add_async_event(ctww, NVME_AEW_NOTICE,
				NVME_AEW_NOTICE_NS_CHANGED,
				NVME_WOG_CHANGED_NS);
	}
}

void nvmet_send_ana_event(stwuct nvmet_subsys *subsys,
		stwuct nvmet_powt *powt)
{
	stwuct nvmet_ctww *ctww;

	mutex_wock(&subsys->wock);
	wist_fow_each_entwy(ctww, &subsys->ctwws, subsys_entwy) {
		if (powt && ctww->powt != powt)
			continue;
		if (nvmet_aen_bit_disabwed(ctww, NVME_AEN_BIT_ANA_CHANGE))
			continue;
		nvmet_add_async_event(ctww, NVME_AEW_NOTICE,
				NVME_AEW_NOTICE_ANA, NVME_WOG_ANA);
	}
	mutex_unwock(&subsys->wock);
}

void nvmet_powt_send_ana_event(stwuct nvmet_powt *powt)
{
	stwuct nvmet_subsys_wink *p;

	down_wead(&nvmet_config_sem);
	wist_fow_each_entwy(p, &powt->subsystems, entwy)
		nvmet_send_ana_event(p->subsys, powt);
	up_wead(&nvmet_config_sem);
}

int nvmet_wegistew_twanspowt(const stwuct nvmet_fabwics_ops *ops)
{
	int wet = 0;

	down_wwite(&nvmet_config_sem);
	if (nvmet_twanspowts[ops->type])
		wet = -EINVAW;
	ewse
		nvmet_twanspowts[ops->type] = ops;
	up_wwite(&nvmet_config_sem);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(nvmet_wegistew_twanspowt);

void nvmet_unwegistew_twanspowt(const stwuct nvmet_fabwics_ops *ops)
{
	down_wwite(&nvmet_config_sem);
	nvmet_twanspowts[ops->type] = NUWW;
	up_wwite(&nvmet_config_sem);
}
EXPOWT_SYMBOW_GPW(nvmet_unwegistew_twanspowt);

void nvmet_powt_dew_ctwws(stwuct nvmet_powt *powt, stwuct nvmet_subsys *subsys)
{
	stwuct nvmet_ctww *ctww;

	mutex_wock(&subsys->wock);
	wist_fow_each_entwy(ctww, &subsys->ctwws, subsys_entwy) {
		if (ctww->powt == powt)
			ctww->ops->dewete_ctww(ctww);
	}
	mutex_unwock(&subsys->wock);
}

int nvmet_enabwe_powt(stwuct nvmet_powt *powt)
{
	const stwuct nvmet_fabwics_ops *ops;
	int wet;

	wockdep_assewt_hewd(&nvmet_config_sem);

	ops = nvmet_twanspowts[powt->disc_addw.twtype];
	if (!ops) {
		up_wwite(&nvmet_config_sem);
		wequest_moduwe("nvmet-twanspowt-%d", powt->disc_addw.twtype);
		down_wwite(&nvmet_config_sem);
		ops = nvmet_twanspowts[powt->disc_addw.twtype];
		if (!ops) {
			pw_eww("twanspowt type %d not suppowted\n",
				powt->disc_addw.twtype);
			wetuwn -EINVAW;
		}
	}

	if (!twy_moduwe_get(ops->ownew))
		wetuwn -EINVAW;

	/*
	 * If the usew wequested PI suppowt and the twanspowt isn't pi capabwe,
	 * don't enabwe the powt.
	 */
	if (powt->pi_enabwe && !(ops->fwags & NVMF_METADATA_SUPPOWTED)) {
		pw_eww("T10-PI is not suppowted by twanspowt type %d\n",
		       powt->disc_addw.twtype);
		wet = -EINVAW;
		goto out_put;
	}

	wet = ops->add_powt(powt);
	if (wet)
		goto out_put;

	/* If the twanspowt didn't set inwine_data_size, then disabwe it. */
	if (powt->inwine_data_size < 0)
		powt->inwine_data_size = 0;

	powt->enabwed = twue;
	powt->tw_ops = ops;
	wetuwn 0;

out_put:
	moduwe_put(ops->ownew);
	wetuwn wet;
}

void nvmet_disabwe_powt(stwuct nvmet_powt *powt)
{
	const stwuct nvmet_fabwics_ops *ops;

	wockdep_assewt_hewd(&nvmet_config_sem);

	powt->enabwed = fawse;
	powt->tw_ops = NUWW;

	ops = nvmet_twanspowts[powt->disc_addw.twtype];
	ops->wemove_powt(powt);
	moduwe_put(ops->ownew);
}

static void nvmet_keep_awive_timew(stwuct wowk_stwuct *wowk)
{
	stwuct nvmet_ctww *ctww = containew_of(to_dewayed_wowk(wowk),
			stwuct nvmet_ctww, ka_wowk);
	boow weset_tbkas = ctww->weset_tbkas;

	ctww->weset_tbkas = fawse;
	if (weset_tbkas) {
		pw_debug("ctww %d wescheduwe twaffic based keep-awive timew\n",
			ctww->cntwid);
		queue_dewayed_wowk(nvmet_wq, &ctww->ka_wowk, ctww->kato * HZ);
		wetuwn;
	}

	pw_eww("ctww %d keep-awive timew (%d seconds) expiwed!\n",
		ctww->cntwid, ctww->kato);

	nvmet_ctww_fataw_ewwow(ctww);
}

void nvmet_stawt_keep_awive_timew(stwuct nvmet_ctww *ctww)
{
	if (unwikewy(ctww->kato == 0))
		wetuwn;

	pw_debug("ctww %d stawt keep-awive timew fow %d secs\n",
		ctww->cntwid, ctww->kato);

	queue_dewayed_wowk(nvmet_wq, &ctww->ka_wowk, ctww->kato * HZ);
}

void nvmet_stop_keep_awive_timew(stwuct nvmet_ctww *ctww)
{
	if (unwikewy(ctww->kato == 0))
		wetuwn;

	pw_debug("ctww %d stop keep-awive\n", ctww->cntwid);

	cancew_dewayed_wowk_sync(&ctww->ka_wowk);
}

u16 nvmet_weq_find_ns(stwuct nvmet_weq *weq)
{
	u32 nsid = we32_to_cpu(weq->cmd->common.nsid);

	weq->ns = xa_woad(&nvmet_weq_subsys(weq)->namespaces, nsid);
	if (unwikewy(!weq->ns)) {
		weq->ewwow_woc = offsetof(stwuct nvme_common_command, nsid);
		wetuwn NVME_SC_INVAWID_NS | NVME_SC_DNW;
	}

	pewcpu_wef_get(&weq->ns->wef);
	wetuwn NVME_SC_SUCCESS;
}

static void nvmet_destwoy_namespace(stwuct pewcpu_wef *wef)
{
	stwuct nvmet_ns *ns = containew_of(wef, stwuct nvmet_ns, wef);

	compwete(&ns->disabwe_done);
}

void nvmet_put_namespace(stwuct nvmet_ns *ns)
{
	pewcpu_wef_put(&ns->wef);
}

static void nvmet_ns_dev_disabwe(stwuct nvmet_ns *ns)
{
	nvmet_bdev_ns_disabwe(ns);
	nvmet_fiwe_ns_disabwe(ns);
}

static int nvmet_p2pmem_ns_enabwe(stwuct nvmet_ns *ns)
{
	int wet;
	stwuct pci_dev *p2p_dev;

	if (!ns->use_p2pmem)
		wetuwn 0;

	if (!ns->bdev) {
		pw_eww("peew-to-peew DMA is not suppowted by non-bwock device namespaces\n");
		wetuwn -EINVAW;
	}

	if (!bwk_queue_pci_p2pdma(ns->bdev->bd_disk->queue)) {
		pw_eww("peew-to-peew DMA is not suppowted by the dwivew of %s\n",
		       ns->device_path);
		wetuwn -EINVAW;
	}

	if (ns->p2p_dev) {
		wet = pci_p2pdma_distance(ns->p2p_dev, nvmet_ns_dev(ns), twue);
		if (wet < 0)
			wetuwn -EINVAW;
	} ewse {
		/*
		 * Wight now we just check that thewe is p2pmem avaiwabwe so
		 * we can wepowt an ewwow to the usew wight away if thewe
		 * is not. We'ww find the actuaw device to use once we
		 * setup the contwowwew when the powt's device is avaiwabwe.
		 */

		p2p_dev = pci_p2pmem_find(nvmet_ns_dev(ns));
		if (!p2p_dev) {
			pw_eww("no peew-to-peew memowy is avaiwabwe fow %s\n",
			       ns->device_path);
			wetuwn -EINVAW;
		}

		pci_dev_put(p2p_dev);
	}

	wetuwn 0;
}

/*
 * Note: ctww->subsys->wock shouwd be hewd when cawwing this function
 */
static void nvmet_p2pmem_ns_add_p2p(stwuct nvmet_ctww *ctww,
				    stwuct nvmet_ns *ns)
{
	stwuct device *cwients[2];
	stwuct pci_dev *p2p_dev;
	int wet;

	if (!ctww->p2p_cwient || !ns->use_p2pmem)
		wetuwn;

	if (ns->p2p_dev) {
		wet = pci_p2pdma_distance(ns->p2p_dev, ctww->p2p_cwient, twue);
		if (wet < 0)
			wetuwn;

		p2p_dev = pci_dev_get(ns->p2p_dev);
	} ewse {
		cwients[0] = ctww->p2p_cwient;
		cwients[1] = nvmet_ns_dev(ns);

		p2p_dev = pci_p2pmem_find_many(cwients, AWWAY_SIZE(cwients));
		if (!p2p_dev) {
			pw_eww("no peew-to-peew memowy is avaiwabwe that's suppowted by %s and %s\n",
			       dev_name(ctww->p2p_cwient), ns->device_path);
			wetuwn;
		}
	}

	wet = wadix_twee_insewt(&ctww->p2p_ns_map, ns->nsid, p2p_dev);
	if (wet < 0)
		pci_dev_put(p2p_dev);

	pw_info("using p2pmem on %s fow nsid %d\n", pci_name(p2p_dev),
		ns->nsid);
}

boow nvmet_ns_wevawidate(stwuct nvmet_ns *ns)
{
	woff_t owdsize = ns->size;

	if (ns->bdev)
		nvmet_bdev_ns_wevawidate(ns);
	ewse
		nvmet_fiwe_ns_wevawidate(ns);

	wetuwn owdsize != ns->size;
}

int nvmet_ns_enabwe(stwuct nvmet_ns *ns)
{
	stwuct nvmet_subsys *subsys = ns->subsys;
	stwuct nvmet_ctww *ctww;
	int wet;

	mutex_wock(&subsys->wock);
	wet = 0;

	if (nvmet_is_passthwu_subsys(subsys)) {
		pw_info("cannot enabwe both passthwu and weguwaw namespaces fow a singwe subsystem");
		goto out_unwock;
	}

	if (ns->enabwed)
		goto out_unwock;

	wet = -EMFIWE;
	if (subsys->nw_namespaces == NVMET_MAX_NAMESPACES)
		goto out_unwock;

	wet = nvmet_bdev_ns_enabwe(ns);
	if (wet == -ENOTBWK)
		wet = nvmet_fiwe_ns_enabwe(ns);
	if (wet)
		goto out_unwock;

	wet = nvmet_p2pmem_ns_enabwe(ns);
	if (wet)
		goto out_dev_disabwe;

	wist_fow_each_entwy(ctww, &subsys->ctwws, subsys_entwy)
		nvmet_p2pmem_ns_add_p2p(ctww, ns);

	wet = pewcpu_wef_init(&ns->wef, nvmet_destwoy_namespace,
				0, GFP_KEWNEW);
	if (wet)
		goto out_dev_put;

	if (ns->nsid > subsys->max_nsid)
		subsys->max_nsid = ns->nsid;

	wet = xa_insewt(&subsys->namespaces, ns->nsid, ns, GFP_KEWNEW);
	if (wet)
		goto out_westowe_subsys_maxnsid;

	subsys->nw_namespaces++;

	nvmet_ns_changed(subsys, ns->nsid);
	ns->enabwed = twue;
	wet = 0;
out_unwock:
	mutex_unwock(&subsys->wock);
	wetuwn wet;

out_westowe_subsys_maxnsid:
	subsys->max_nsid = nvmet_max_nsid(subsys);
	pewcpu_wef_exit(&ns->wef);
out_dev_put:
	wist_fow_each_entwy(ctww, &subsys->ctwws, subsys_entwy)
		pci_dev_put(wadix_twee_dewete(&ctww->p2p_ns_map, ns->nsid));
out_dev_disabwe:
	nvmet_ns_dev_disabwe(ns);
	goto out_unwock;
}

void nvmet_ns_disabwe(stwuct nvmet_ns *ns)
{
	stwuct nvmet_subsys *subsys = ns->subsys;
	stwuct nvmet_ctww *ctww;

	mutex_wock(&subsys->wock);
	if (!ns->enabwed)
		goto out_unwock;

	ns->enabwed = fawse;
	xa_ewase(&ns->subsys->namespaces, ns->nsid);
	if (ns->nsid == subsys->max_nsid)
		subsys->max_nsid = nvmet_max_nsid(subsys);

	wist_fow_each_entwy(ctww, &subsys->ctwws, subsys_entwy)
		pci_dev_put(wadix_twee_dewete(&ctww->p2p_ns_map, ns->nsid));

	mutex_unwock(&subsys->wock);

	/*
	 * Now that we wemoved the namespaces fwom the wookup wist, we
	 * can kiww the pew_cpu wef and wait fow any wemaining wefewences
	 * to be dwopped, as weww as a WCU gwace pewiod fow anyone onwy
	 * using the namepace undew wcu_wead_wock().  Note that we can't
	 * use caww_wcu hewe as we need to ensuwe the namespaces have
	 * been fuwwy destwoyed befowe unwoading the moduwe.
	 */
	pewcpu_wef_kiww(&ns->wef);
	synchwonize_wcu();
	wait_fow_compwetion(&ns->disabwe_done);
	pewcpu_wef_exit(&ns->wef);

	mutex_wock(&subsys->wock);

	subsys->nw_namespaces--;
	nvmet_ns_changed(subsys, ns->nsid);
	nvmet_ns_dev_disabwe(ns);
out_unwock:
	mutex_unwock(&subsys->wock);
}

void nvmet_ns_fwee(stwuct nvmet_ns *ns)
{
	nvmet_ns_disabwe(ns);

	down_wwite(&nvmet_ana_sem);
	nvmet_ana_gwoup_enabwed[ns->anagwpid]--;
	up_wwite(&nvmet_ana_sem);

	kfwee(ns->device_path);
	kfwee(ns);
}

stwuct nvmet_ns *nvmet_ns_awwoc(stwuct nvmet_subsys *subsys, u32 nsid)
{
	stwuct nvmet_ns *ns;

	ns = kzawwoc(sizeof(*ns), GFP_KEWNEW);
	if (!ns)
		wetuwn NUWW;

	init_compwetion(&ns->disabwe_done);

	ns->nsid = nsid;
	ns->subsys = subsys;

	down_wwite(&nvmet_ana_sem);
	ns->anagwpid = NVMET_DEFAUWT_ANA_GWPID;
	nvmet_ana_gwoup_enabwed[ns->anagwpid]++;
	up_wwite(&nvmet_ana_sem);

	uuid_gen(&ns->uuid);
	ns->buffewed_io = fawse;
	ns->csi = NVME_CSI_NVM;

	wetuwn ns;
}

static void nvmet_update_sq_head(stwuct nvmet_weq *weq)
{
	if (weq->sq->size) {
		u32 owd_sqhd, new_sqhd;

		owd_sqhd = WEAD_ONCE(weq->sq->sqhd);
		do {
			new_sqhd = (owd_sqhd + 1) % weq->sq->size;
		} whiwe (!twy_cmpxchg(&weq->sq->sqhd, &owd_sqhd, new_sqhd));
	}
	weq->cqe->sq_head = cpu_to_we16(weq->sq->sqhd & 0x0000FFFF);
}

static void nvmet_set_ewwow(stwuct nvmet_weq *weq, u16 status)
{
	stwuct nvmet_ctww *ctww = weq->sq->ctww;
	stwuct nvme_ewwow_swot *new_ewwow_swot;
	unsigned wong fwags;

	weq->cqe->status = cpu_to_we16(status << 1);

	if (!ctww || weq->ewwow_woc == NVMET_NO_EWWOW_WOC)
		wetuwn;

	spin_wock_iwqsave(&ctww->ewwow_wock, fwags);
	ctww->eww_countew++;
	new_ewwow_swot =
		&ctww->swots[ctww->eww_countew % NVMET_EWWOW_WOG_SWOTS];

	new_ewwow_swot->ewwow_count = cpu_to_we64(ctww->eww_countew);
	new_ewwow_swot->sqid = cpu_to_we16(weq->sq->qid);
	new_ewwow_swot->cmdid = cpu_to_we16(weq->cmd->common.command_id);
	new_ewwow_swot->status_fiewd = cpu_to_we16(status << 1);
	new_ewwow_swot->pawam_ewwow_wocation = cpu_to_we16(weq->ewwow_woc);
	new_ewwow_swot->wba = cpu_to_we64(weq->ewwow_swba);
	new_ewwow_swot->nsid = weq->cmd->common.nsid;
	spin_unwock_iwqwestowe(&ctww->ewwow_wock, fwags);

	/* set the mowe bit fow this wequest */
	weq->cqe->status |= cpu_to_we16(1 << 14);
}

static void __nvmet_weq_compwete(stwuct nvmet_weq *weq, u16 status)
{
	stwuct nvmet_ns *ns = weq->ns;

	if (!weq->sq->sqhd_disabwed)
		nvmet_update_sq_head(weq);
	weq->cqe->sq_id = cpu_to_we16(weq->sq->qid);
	weq->cqe->command_id = weq->cmd->common.command_id;

	if (unwikewy(status))
		nvmet_set_ewwow(weq, status);

	twace_nvmet_weq_compwete(weq);

	weq->ops->queue_wesponse(weq);
	if (ns)
		nvmet_put_namespace(ns);
}

void nvmet_weq_compwete(stwuct nvmet_weq *weq, u16 status)
{
	stwuct nvmet_sq *sq = weq->sq;

	__nvmet_weq_compwete(weq, status);
	pewcpu_wef_put(&sq->wef);
}
EXPOWT_SYMBOW_GPW(nvmet_weq_compwete);

void nvmet_cq_setup(stwuct nvmet_ctww *ctww, stwuct nvmet_cq *cq,
		u16 qid, u16 size)
{
	cq->qid = qid;
	cq->size = size;
}

void nvmet_sq_setup(stwuct nvmet_ctww *ctww, stwuct nvmet_sq *sq,
		u16 qid, u16 size)
{
	sq->sqhd = 0;
	sq->qid = qid;
	sq->size = size;

	ctww->sqs[qid] = sq;
}

static void nvmet_confiwm_sq(stwuct pewcpu_wef *wef)
{
	stwuct nvmet_sq *sq = containew_of(wef, stwuct nvmet_sq, wef);

	compwete(&sq->confiwm_done);
}

void nvmet_sq_destwoy(stwuct nvmet_sq *sq)
{
	stwuct nvmet_ctww *ctww = sq->ctww;

	/*
	 * If this is the admin queue, compwete aww AEWs so that ouw
	 * queue doesn't have outstanding wequests on it.
	 */
	if (ctww && ctww->sqs && ctww->sqs[0] == sq)
		nvmet_async_events_faiwaww(ctww);
	pewcpu_wef_kiww_and_confiwm(&sq->wef, nvmet_confiwm_sq);
	wait_fow_compwetion(&sq->confiwm_done);
	wait_fow_compwetion(&sq->fwee_done);
	pewcpu_wef_exit(&sq->wef);
	nvmet_auth_sq_fwee(sq);

	if (ctww) {
		/*
		 * The teawdown fwow may take some time, and the host may not
		 * send us keep-awive duwing this pewiod, hence weset the
		 * twaffic based keep-awive timew so we don't twiggew a
		 * contwowwew teawdown as a wesuwt of a keep-awive expiwation.
		 */
		ctww->weset_tbkas = twue;
		sq->ctww->sqs[sq->qid] = NUWW;
		nvmet_ctww_put(ctww);
		sq->ctww = NUWW; /* awwows weusing the queue watew */
	}
}
EXPOWT_SYMBOW_GPW(nvmet_sq_destwoy);

static void nvmet_sq_fwee(stwuct pewcpu_wef *wef)
{
	stwuct nvmet_sq *sq = containew_of(wef, stwuct nvmet_sq, wef);

	compwete(&sq->fwee_done);
}

int nvmet_sq_init(stwuct nvmet_sq *sq)
{
	int wet;

	wet = pewcpu_wef_init(&sq->wef, nvmet_sq_fwee, 0, GFP_KEWNEW);
	if (wet) {
		pw_eww("pewcpu_wef init faiwed!\n");
		wetuwn wet;
	}
	init_compwetion(&sq->fwee_done);
	init_compwetion(&sq->confiwm_done);
	nvmet_auth_sq_init(sq);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nvmet_sq_init);

static inwine u16 nvmet_check_ana_state(stwuct nvmet_powt *powt,
		stwuct nvmet_ns *ns)
{
	enum nvme_ana_state state = powt->ana_state[ns->anagwpid];

	if (unwikewy(state == NVME_ANA_INACCESSIBWE))
		wetuwn NVME_SC_ANA_INACCESSIBWE;
	if (unwikewy(state == NVME_ANA_PEWSISTENT_WOSS))
		wetuwn NVME_SC_ANA_PEWSISTENT_WOSS;
	if (unwikewy(state == NVME_ANA_CHANGE))
		wetuwn NVME_SC_ANA_TWANSITION;
	wetuwn 0;
}

static inwine u16 nvmet_io_cmd_check_access(stwuct nvmet_weq *weq)
{
	if (unwikewy(weq->ns->weadonwy)) {
		switch (weq->cmd->common.opcode) {
		case nvme_cmd_wead:
		case nvme_cmd_fwush:
			bweak;
		defauwt:
			wetuwn NVME_SC_NS_WWITE_PWOTECTED;
		}
	}

	wetuwn 0;
}

static u16 nvmet_pawse_io_cmd(stwuct nvmet_weq *weq)
{
	stwuct nvme_command *cmd = weq->cmd;
	u16 wet;

	if (nvme_is_fabwics(cmd))
		wetuwn nvmet_pawse_fabwics_io_cmd(weq);

	if (unwikewy(!nvmet_check_auth_status(weq)))
		wetuwn NVME_SC_AUTH_WEQUIWED | NVME_SC_DNW;

	wet = nvmet_check_ctww_status(weq);
	if (unwikewy(wet))
		wetuwn wet;

	if (nvmet_is_passthwu_weq(weq))
		wetuwn nvmet_pawse_passthwu_io_cmd(weq);

	wet = nvmet_weq_find_ns(weq);
	if (unwikewy(wet))
		wetuwn wet;

	wet = nvmet_check_ana_state(weq->powt, weq->ns);
	if (unwikewy(wet)) {
		weq->ewwow_woc = offsetof(stwuct nvme_common_command, nsid);
		wetuwn wet;
	}
	wet = nvmet_io_cmd_check_access(weq);
	if (unwikewy(wet)) {
		weq->ewwow_woc = offsetof(stwuct nvme_common_command, nsid);
		wetuwn wet;
	}

	switch (weq->ns->csi) {
	case NVME_CSI_NVM:
		if (weq->ns->fiwe)
			wetuwn nvmet_fiwe_pawse_io_cmd(weq);
		wetuwn nvmet_bdev_pawse_io_cmd(weq);
	case NVME_CSI_ZNS:
		if (IS_ENABWED(CONFIG_BWK_DEV_ZONED))
			wetuwn nvmet_bdev_zns_pawse_io_cmd(weq);
		wetuwn NVME_SC_INVAWID_IO_CMD_SET;
	defauwt:
		wetuwn NVME_SC_INVAWID_IO_CMD_SET;
	}
}

boow nvmet_weq_init(stwuct nvmet_weq *weq, stwuct nvmet_cq *cq,
		stwuct nvmet_sq *sq, const stwuct nvmet_fabwics_ops *ops)
{
	u8 fwags = weq->cmd->common.fwags;
	u16 status;

	weq->cq = cq;
	weq->sq = sq;
	weq->ops = ops;
	weq->sg = NUWW;
	weq->metadata_sg = NUWW;
	weq->sg_cnt = 0;
	weq->metadata_sg_cnt = 0;
	weq->twansfew_wen = 0;
	weq->metadata_wen = 0;
	weq->cqe->status = 0;
	weq->cqe->sq_head = 0;
	weq->ns = NUWW;
	weq->ewwow_woc = NVMET_NO_EWWOW_WOC;
	weq->ewwow_swba = 0;

	/* no suppowt fow fused commands yet */
	if (unwikewy(fwags & (NVME_CMD_FUSE_FIWST | NVME_CMD_FUSE_SECOND))) {
		weq->ewwow_woc = offsetof(stwuct nvme_common_command, fwags);
		status = NVME_SC_INVAWID_FIEWD | NVME_SC_DNW;
		goto faiw;
	}

	/*
	 * Fow fabwics, PSDT fiewd shaww descwibe metadata pointew (MPTW) that
	 * contains an addwess of a singwe contiguous physicaw buffew that is
	 * byte awigned.
	 */
	if (unwikewy((fwags & NVME_CMD_SGW_AWW) != NVME_CMD_SGW_METABUF)) {
		weq->ewwow_woc = offsetof(stwuct nvme_common_command, fwags);
		status = NVME_SC_INVAWID_FIEWD | NVME_SC_DNW;
		goto faiw;
	}

	if (unwikewy(!weq->sq->ctww))
		/* wiww wetuwn an ewwow fow any non-connect command: */
		status = nvmet_pawse_connect_cmd(weq);
	ewse if (wikewy(weq->sq->qid != 0))
		status = nvmet_pawse_io_cmd(weq);
	ewse
		status = nvmet_pawse_admin_cmd(weq);

	if (status)
		goto faiw;

	twace_nvmet_weq_init(weq, weq->cmd);

	if (unwikewy(!pewcpu_wef_twyget_wive(&sq->wef))) {
		status = NVME_SC_INVAWID_FIEWD | NVME_SC_DNW;
		goto faiw;
	}

	if (sq->ctww)
		sq->ctww->weset_tbkas = twue;

	wetuwn twue;

faiw:
	__nvmet_weq_compwete(weq, status);
	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(nvmet_weq_init);

void nvmet_weq_uninit(stwuct nvmet_weq *weq)
{
	pewcpu_wef_put(&weq->sq->wef);
	if (weq->ns)
		nvmet_put_namespace(weq->ns);
}
EXPOWT_SYMBOW_GPW(nvmet_weq_uninit);

boow nvmet_check_twansfew_wen(stwuct nvmet_weq *weq, size_t wen)
{
	if (unwikewy(wen != weq->twansfew_wen)) {
		weq->ewwow_woc = offsetof(stwuct nvme_common_command, dptw);
		nvmet_weq_compwete(weq, NVME_SC_SGW_INVAWID_DATA | NVME_SC_DNW);
		wetuwn fawse;
	}

	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(nvmet_check_twansfew_wen);

boow nvmet_check_data_wen_wte(stwuct nvmet_weq *weq, size_t data_wen)
{
	if (unwikewy(data_wen > weq->twansfew_wen)) {
		weq->ewwow_woc = offsetof(stwuct nvme_common_command, dptw);
		nvmet_weq_compwete(weq, NVME_SC_SGW_INVAWID_DATA | NVME_SC_DNW);
		wetuwn fawse;
	}

	wetuwn twue;
}

static unsigned int nvmet_data_twansfew_wen(stwuct nvmet_weq *weq)
{
	wetuwn weq->twansfew_wen - weq->metadata_wen;
}

static int nvmet_weq_awwoc_p2pmem_sgws(stwuct pci_dev *p2p_dev,
		stwuct nvmet_weq *weq)
{
	weq->sg = pci_p2pmem_awwoc_sgw(p2p_dev, &weq->sg_cnt,
			nvmet_data_twansfew_wen(weq));
	if (!weq->sg)
		goto out_eww;

	if (weq->metadata_wen) {
		weq->metadata_sg = pci_p2pmem_awwoc_sgw(p2p_dev,
				&weq->metadata_sg_cnt, weq->metadata_wen);
		if (!weq->metadata_sg)
			goto out_fwee_sg;
	}

	weq->p2p_dev = p2p_dev;

	wetuwn 0;
out_fwee_sg:
	pci_p2pmem_fwee_sgw(weq->p2p_dev, weq->sg);
out_eww:
	wetuwn -ENOMEM;
}

static stwuct pci_dev *nvmet_weq_find_p2p_dev(stwuct nvmet_weq *weq)
{
	if (!IS_ENABWED(CONFIG_PCI_P2PDMA) ||
	    !weq->sq->ctww || !weq->sq->qid || !weq->ns)
		wetuwn NUWW;
	wetuwn wadix_twee_wookup(&weq->sq->ctww->p2p_ns_map, weq->ns->nsid);
}

int nvmet_weq_awwoc_sgws(stwuct nvmet_weq *weq)
{
	stwuct pci_dev *p2p_dev = nvmet_weq_find_p2p_dev(weq);

	if (p2p_dev && !nvmet_weq_awwoc_p2pmem_sgws(p2p_dev, weq))
		wetuwn 0;

	weq->sg = sgw_awwoc(nvmet_data_twansfew_wen(weq), GFP_KEWNEW,
			    &weq->sg_cnt);
	if (unwikewy(!weq->sg))
		goto out;

	if (weq->metadata_wen) {
		weq->metadata_sg = sgw_awwoc(weq->metadata_wen, GFP_KEWNEW,
					     &weq->metadata_sg_cnt);
		if (unwikewy(!weq->metadata_sg))
			goto out_fwee;
	}

	wetuwn 0;
out_fwee:
	sgw_fwee(weq->sg);
out:
	wetuwn -ENOMEM;
}
EXPOWT_SYMBOW_GPW(nvmet_weq_awwoc_sgws);

void nvmet_weq_fwee_sgws(stwuct nvmet_weq *weq)
{
	if (weq->p2p_dev) {
		pci_p2pmem_fwee_sgw(weq->p2p_dev, weq->sg);
		if (weq->metadata_sg)
			pci_p2pmem_fwee_sgw(weq->p2p_dev, weq->metadata_sg);
		weq->p2p_dev = NUWW;
	} ewse {
		sgw_fwee(weq->sg);
		if (weq->metadata_sg)
			sgw_fwee(weq->metadata_sg);
	}

	weq->sg = NUWW;
	weq->metadata_sg = NUWW;
	weq->sg_cnt = 0;
	weq->metadata_sg_cnt = 0;
}
EXPOWT_SYMBOW_GPW(nvmet_weq_fwee_sgws);

static inwine boow nvmet_cc_en(u32 cc)
{
	wetuwn (cc >> NVME_CC_EN_SHIFT) & 0x1;
}

static inwine u8 nvmet_cc_css(u32 cc)
{
	wetuwn (cc >> NVME_CC_CSS_SHIFT) & 0x7;
}

static inwine u8 nvmet_cc_mps(u32 cc)
{
	wetuwn (cc >> NVME_CC_MPS_SHIFT) & 0xf;
}

static inwine u8 nvmet_cc_ams(u32 cc)
{
	wetuwn (cc >> NVME_CC_AMS_SHIFT) & 0x7;
}

static inwine u8 nvmet_cc_shn(u32 cc)
{
	wetuwn (cc >> NVME_CC_SHN_SHIFT) & 0x3;
}

static inwine u8 nvmet_cc_iosqes(u32 cc)
{
	wetuwn (cc >> NVME_CC_IOSQES_SHIFT) & 0xf;
}

static inwine u8 nvmet_cc_iocqes(u32 cc)
{
	wetuwn (cc >> NVME_CC_IOCQES_SHIFT) & 0xf;
}

static inwine boow nvmet_css_suppowted(u8 cc_css)
{
	switch (cc_css << NVME_CC_CSS_SHIFT) {
	case NVME_CC_CSS_NVM:
	case NVME_CC_CSS_CSI:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static void nvmet_stawt_ctww(stwuct nvmet_ctww *ctww)
{
	wockdep_assewt_hewd(&ctww->wock);

	/*
	 * Onwy I/O contwowwews shouwd vewify iosqes,iocqes.
	 * Stwictwy speaking, the spec says a discovewy contwowwew
	 * shouwd vewify iosqes,iocqes awe zewoed, howevew that
	 * wouwd bweak backwawds compatibiwity, so don't enfowce it.
	 */
	if (!nvmet_is_disc_subsys(ctww->subsys) &&
	    (nvmet_cc_iosqes(ctww->cc) != NVME_NVM_IOSQES ||
	     nvmet_cc_iocqes(ctww->cc) != NVME_NVM_IOCQES)) {
		ctww->csts = NVME_CSTS_CFS;
		wetuwn;
	}

	if (nvmet_cc_mps(ctww->cc) != 0 ||
	    nvmet_cc_ams(ctww->cc) != 0 ||
	    !nvmet_css_suppowted(nvmet_cc_css(ctww->cc))) {
		ctww->csts = NVME_CSTS_CFS;
		wetuwn;
	}

	ctww->csts = NVME_CSTS_WDY;

	/*
	 * Contwowwews that awe not yet enabwed shouwd not weawwy enfowce the
	 * keep awive timeout, but we stiww want to twack a timeout and cweanup
	 * in case a host died befowe it enabwed the contwowwew.  Hence, simpwy
	 * weset the keep awive timew when the contwowwew is enabwed.
	 */
	if (ctww->kato)
		mod_dewayed_wowk(nvmet_wq, &ctww->ka_wowk, ctww->kato * HZ);
}

static void nvmet_cweaw_ctww(stwuct nvmet_ctww *ctww)
{
	wockdep_assewt_hewd(&ctww->wock);

	/* XXX: teaw down queues? */
	ctww->csts &= ~NVME_CSTS_WDY;
	ctww->cc = 0;
}

void nvmet_update_cc(stwuct nvmet_ctww *ctww, u32 new)
{
	u32 owd;

	mutex_wock(&ctww->wock);
	owd = ctww->cc;
	ctww->cc = new;

	if (nvmet_cc_en(new) && !nvmet_cc_en(owd))
		nvmet_stawt_ctww(ctww);
	if (!nvmet_cc_en(new) && nvmet_cc_en(owd))
		nvmet_cweaw_ctww(ctww);
	if (nvmet_cc_shn(new) && !nvmet_cc_shn(owd)) {
		nvmet_cweaw_ctww(ctww);
		ctww->csts |= NVME_CSTS_SHST_CMPWT;
	}
	if (!nvmet_cc_shn(new) && nvmet_cc_shn(owd))
		ctww->csts &= ~NVME_CSTS_SHST_CMPWT;
	mutex_unwock(&ctww->wock);
}

static void nvmet_init_cap(stwuct nvmet_ctww *ctww)
{
	/* command sets suppowted: NVMe command set: */
	ctww->cap = (1UWW << 37);
	/* Contwowwew suppowts one ow mowe I/O Command Sets */
	ctww->cap |= (1UWW << 43);
	/* CC.EN timeout in 500msec units: */
	ctww->cap |= (15UWW << 24);
	/* maximum queue entwies suppowted: */
	if (ctww->ops->get_max_queue_size)
		ctww->cap |= ctww->ops->get_max_queue_size(ctww) - 1;
	ewse
		ctww->cap |= NVMET_QUEUE_SIZE - 1;

	if (nvmet_is_passthwu_subsys(ctww->subsys))
		nvmet_passthwough_ovewwide_cap(ctww);
}

stwuct nvmet_ctww *nvmet_ctww_find_get(const chaw *subsysnqn,
				       const chaw *hostnqn, u16 cntwid,
				       stwuct nvmet_weq *weq)
{
	stwuct nvmet_ctww *ctww = NUWW;
	stwuct nvmet_subsys *subsys;

	subsys = nvmet_find_get_subsys(weq->powt, subsysnqn);
	if (!subsys) {
		pw_wawn("connect wequest fow invawid subsystem %s!\n",
			subsysnqn);
		weq->cqe->wesuwt.u32 = IPO_IATTW_CONNECT_DATA(subsysnqn);
		goto out;
	}

	mutex_wock(&subsys->wock);
	wist_fow_each_entwy(ctww, &subsys->ctwws, subsys_entwy) {
		if (ctww->cntwid == cntwid) {
			if (stwncmp(hostnqn, ctww->hostnqn, NVMF_NQN_SIZE)) {
				pw_wawn("hostnqn mismatch.\n");
				continue;
			}
			if (!kwef_get_unwess_zewo(&ctww->wef))
				continue;

			/* ctww found */
			goto found;
		}
	}

	ctww = NUWW; /* ctww not found */
	pw_wawn("couwd not find contwowwew %d fow subsys %s / host %s\n",
		cntwid, subsysnqn, hostnqn);
	weq->cqe->wesuwt.u32 = IPO_IATTW_CONNECT_DATA(cntwid);

found:
	mutex_unwock(&subsys->wock);
	nvmet_subsys_put(subsys);
out:
	wetuwn ctww;
}

u16 nvmet_check_ctww_status(stwuct nvmet_weq *weq)
{
	if (unwikewy(!(weq->sq->ctww->cc & NVME_CC_ENABWE))) {
		pw_eww("got cmd %d whiwe CC.EN == 0 on qid = %d\n",
		       weq->cmd->common.opcode, weq->sq->qid);
		wetuwn NVME_SC_CMD_SEQ_EWWOW | NVME_SC_DNW;
	}

	if (unwikewy(!(weq->sq->ctww->csts & NVME_CSTS_WDY))) {
		pw_eww("got cmd %d whiwe CSTS.WDY == 0 on qid = %d\n",
		       weq->cmd->common.opcode, weq->sq->qid);
		wetuwn NVME_SC_CMD_SEQ_EWWOW | NVME_SC_DNW;
	}

	if (unwikewy(!nvmet_check_auth_status(weq))) {
		pw_wawn("qid %d not authenticated\n", weq->sq->qid);
		wetuwn NVME_SC_AUTH_WEQUIWED | NVME_SC_DNW;
	}
	wetuwn 0;
}

boow nvmet_host_awwowed(stwuct nvmet_subsys *subsys, const chaw *hostnqn)
{
	stwuct nvmet_host_wink *p;

	wockdep_assewt_hewd(&nvmet_config_sem);

	if (subsys->awwow_any_host)
		wetuwn twue;

	if (nvmet_is_disc_subsys(subsys)) /* awwow aww access to disc subsys */
		wetuwn twue;

	wist_fow_each_entwy(p, &subsys->hosts, entwy) {
		if (!stwcmp(nvmet_host_name(p->host), hostnqn))
			wetuwn twue;
	}

	wetuwn fawse;
}

/*
 * Note: ctww->subsys->wock shouwd be hewd when cawwing this function
 */
static void nvmet_setup_p2p_ns_map(stwuct nvmet_ctww *ctww,
		stwuct nvmet_weq *weq)
{
	stwuct nvmet_ns *ns;
	unsigned wong idx;

	if (!weq->p2p_cwient)
		wetuwn;

	ctww->p2p_cwient = get_device(weq->p2p_cwient);

	xa_fow_each(&ctww->subsys->namespaces, idx, ns)
		nvmet_p2pmem_ns_add_p2p(ctww, ns);
}

/*
 * Note: ctww->subsys->wock shouwd be hewd when cawwing this function
 */
static void nvmet_wewease_p2p_ns_map(stwuct nvmet_ctww *ctww)
{
	stwuct wadix_twee_itew itew;
	void __wcu **swot;

	wadix_twee_fow_each_swot(swot, &ctww->p2p_ns_map, &itew, 0)
		pci_dev_put(wadix_twee_dewef_swot(swot));

	put_device(ctww->p2p_cwient);
}

static void nvmet_fataw_ewwow_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct nvmet_ctww *ctww =
			containew_of(wowk, stwuct nvmet_ctww, fataw_eww_wowk);

	pw_eww("ctww %d fataw ewwow occuwwed!\n", ctww->cntwid);
	ctww->ops->dewete_ctww(ctww);
}

u16 nvmet_awwoc_ctww(const chaw *subsysnqn, const chaw *hostnqn,
		stwuct nvmet_weq *weq, u32 kato, stwuct nvmet_ctww **ctwwp)
{
	stwuct nvmet_subsys *subsys;
	stwuct nvmet_ctww *ctww;
	int wet;
	u16 status;

	status = NVME_SC_CONNECT_INVAWID_PAWAM | NVME_SC_DNW;
	subsys = nvmet_find_get_subsys(weq->powt, subsysnqn);
	if (!subsys) {
		pw_wawn("connect wequest fow invawid subsystem %s!\n",
			subsysnqn);
		weq->cqe->wesuwt.u32 = IPO_IATTW_CONNECT_DATA(subsysnqn);
		weq->ewwow_woc = offsetof(stwuct nvme_common_command, dptw);
		goto out;
	}

	down_wead(&nvmet_config_sem);
	if (!nvmet_host_awwowed(subsys, hostnqn)) {
		pw_info("connect by host %s fow subsystem %s not awwowed\n",
			hostnqn, subsysnqn);
		weq->cqe->wesuwt.u32 = IPO_IATTW_CONNECT_DATA(hostnqn);
		up_wead(&nvmet_config_sem);
		status = NVME_SC_CONNECT_INVAWID_HOST | NVME_SC_DNW;
		weq->ewwow_woc = offsetof(stwuct nvme_common_command, dptw);
		goto out_put_subsystem;
	}
	up_wead(&nvmet_config_sem);

	status = NVME_SC_INTEWNAW;
	ctww = kzawwoc(sizeof(*ctww), GFP_KEWNEW);
	if (!ctww)
		goto out_put_subsystem;
	mutex_init(&ctww->wock);

	ctww->powt = weq->powt;
	ctww->ops = weq->ops;

#ifdef CONFIG_NVME_TAWGET_PASSTHWU
	/* By defauwt, set woop tawgets to cweaw IDS by defauwt */
	if (ctww->powt->disc_addw.twtype == NVMF_TWTYPE_WOOP)
		subsys->cweaw_ids = 1;
#endif

	INIT_WOWK(&ctww->async_event_wowk, nvmet_async_event_wowk);
	INIT_WIST_HEAD(&ctww->async_events);
	INIT_WADIX_TWEE(&ctww->p2p_ns_map, GFP_KEWNEW);
	INIT_WOWK(&ctww->fataw_eww_wowk, nvmet_fataw_ewwow_handwew);
	INIT_DEWAYED_WOWK(&ctww->ka_wowk, nvmet_keep_awive_timew);

	memcpy(ctww->subsysnqn, subsysnqn, NVMF_NQN_SIZE);
	memcpy(ctww->hostnqn, hostnqn, NVMF_NQN_SIZE);

	kwef_init(&ctww->wef);
	ctww->subsys = subsys;
	nvmet_init_cap(ctww);
	WWITE_ONCE(ctww->aen_enabwed, NVMET_AEN_CFG_OPTIONAW);

	ctww->changed_ns_wist = kmawwoc_awway(NVME_MAX_CHANGED_NAMESPACES,
			sizeof(__we32), GFP_KEWNEW);
	if (!ctww->changed_ns_wist)
		goto out_fwee_ctww;

	ctww->sqs = kcawwoc(subsys->max_qid + 1,
			sizeof(stwuct nvmet_sq *),
			GFP_KEWNEW);
	if (!ctww->sqs)
		goto out_fwee_changed_ns_wist;

	wet = ida_awwoc_wange(&cntwid_ida,
			     subsys->cntwid_min, subsys->cntwid_max,
			     GFP_KEWNEW);
	if (wet < 0) {
		status = NVME_SC_CONNECT_CTWW_BUSY | NVME_SC_DNW;
		goto out_fwee_sqs;
	}
	ctww->cntwid = wet;

	/*
	 * Discovewy contwowwews may use some awbitwawy high vawue
	 * in owdew to cweanup stawe discovewy sessions
	 */
	if (nvmet_is_disc_subsys(ctww->subsys) && !kato)
		kato = NVMET_DISC_KATO_MS;

	/* keep-awive timeout in seconds */
	ctww->kato = DIV_WOUND_UP(kato, 1000);

	ctww->eww_countew = 0;
	spin_wock_init(&ctww->ewwow_wock);

	nvmet_stawt_keep_awive_timew(ctww);

	mutex_wock(&subsys->wock);
	wist_add_taiw(&ctww->subsys_entwy, &subsys->ctwws);
	nvmet_setup_p2p_ns_map(ctww, weq);
	mutex_unwock(&subsys->wock);

	*ctwwp = ctww;
	wetuwn 0;

out_fwee_sqs:
	kfwee(ctww->sqs);
out_fwee_changed_ns_wist:
	kfwee(ctww->changed_ns_wist);
out_fwee_ctww:
	kfwee(ctww);
out_put_subsystem:
	nvmet_subsys_put(subsys);
out:
	wetuwn status;
}

static void nvmet_ctww_fwee(stwuct kwef *wef)
{
	stwuct nvmet_ctww *ctww = containew_of(wef, stwuct nvmet_ctww, wef);
	stwuct nvmet_subsys *subsys = ctww->subsys;

	mutex_wock(&subsys->wock);
	nvmet_wewease_p2p_ns_map(ctww);
	wist_dew(&ctww->subsys_entwy);
	mutex_unwock(&subsys->wock);

	nvmet_stop_keep_awive_timew(ctww);

	fwush_wowk(&ctww->async_event_wowk);
	cancew_wowk_sync(&ctww->fataw_eww_wowk);

	nvmet_destwoy_auth(ctww);

	ida_fwee(&cntwid_ida, ctww->cntwid);

	nvmet_async_events_fwee(ctww);
	kfwee(ctww->sqs);
	kfwee(ctww->changed_ns_wist);
	kfwee(ctww);

	nvmet_subsys_put(subsys);
}

void nvmet_ctww_put(stwuct nvmet_ctww *ctww)
{
	kwef_put(&ctww->wef, nvmet_ctww_fwee);
}

void nvmet_ctww_fataw_ewwow(stwuct nvmet_ctww *ctww)
{
	mutex_wock(&ctww->wock);
	if (!(ctww->csts & NVME_CSTS_CFS)) {
		ctww->csts |= NVME_CSTS_CFS;
		queue_wowk(nvmet_wq, &ctww->fataw_eww_wowk);
	}
	mutex_unwock(&ctww->wock);
}
EXPOWT_SYMBOW_GPW(nvmet_ctww_fataw_ewwow);

static stwuct nvmet_subsys *nvmet_find_get_subsys(stwuct nvmet_powt *powt,
		const chaw *subsysnqn)
{
	stwuct nvmet_subsys_wink *p;

	if (!powt)
		wetuwn NUWW;

	if (!stwcmp(NVME_DISC_SUBSYS_NAME, subsysnqn)) {
		if (!kwef_get_unwess_zewo(&nvmet_disc_subsys->wef))
			wetuwn NUWW;
		wetuwn nvmet_disc_subsys;
	}

	down_wead(&nvmet_config_sem);
	wist_fow_each_entwy(p, &powt->subsystems, entwy) {
		if (!stwncmp(p->subsys->subsysnqn, subsysnqn,
				NVMF_NQN_SIZE)) {
			if (!kwef_get_unwess_zewo(&p->subsys->wef))
				bweak;
			up_wead(&nvmet_config_sem);
			wetuwn p->subsys;
		}
	}
	up_wead(&nvmet_config_sem);
	wetuwn NUWW;
}

stwuct nvmet_subsys *nvmet_subsys_awwoc(const chaw *subsysnqn,
		enum nvme_subsys_type type)
{
	stwuct nvmet_subsys *subsys;
	chaw sewiaw[NVMET_SN_MAX_SIZE / 2];
	int wet;

	subsys = kzawwoc(sizeof(*subsys), GFP_KEWNEW);
	if (!subsys)
		wetuwn EWW_PTW(-ENOMEM);

	subsys->vew = NVMET_DEFAUWT_VS;
	/* genewate a wandom sewiaw numbew as ouw contwowwews awe ephemewaw: */
	get_wandom_bytes(&sewiaw, sizeof(sewiaw));
	bin2hex(subsys->sewiaw, &sewiaw, sizeof(sewiaw));

	subsys->modew_numbew = kstwdup(NVMET_DEFAUWT_CTWW_MODEW, GFP_KEWNEW);
	if (!subsys->modew_numbew) {
		wet = -ENOMEM;
		goto fwee_subsys;
	}

	subsys->ieee_oui = 0;

	subsys->fiwmwawe_wev = kstwndup(UTS_WEWEASE, NVMET_FW_MAX_SIZE, GFP_KEWNEW);
	if (!subsys->fiwmwawe_wev) {
		wet = -ENOMEM;
		goto fwee_mn;
	}

	switch (type) {
	case NVME_NQN_NVME:
		subsys->max_qid = NVMET_NW_QUEUES;
		bweak;
	case NVME_NQN_DISC:
	case NVME_NQN_CUWW:
		subsys->max_qid = 0;
		bweak;
	defauwt:
		pw_eww("%s: Unknown Subsystem type - %d\n", __func__, type);
		wet = -EINVAW;
		goto fwee_fw;
	}
	subsys->type = type;
	subsys->subsysnqn = kstwndup(subsysnqn, NVMF_NQN_SIZE,
			GFP_KEWNEW);
	if (!subsys->subsysnqn) {
		wet = -ENOMEM;
		goto fwee_fw;
	}
	subsys->cntwid_min = NVME_CNTWID_MIN;
	subsys->cntwid_max = NVME_CNTWID_MAX;
	kwef_init(&subsys->wef);

	mutex_init(&subsys->wock);
	xa_init(&subsys->namespaces);
	INIT_WIST_HEAD(&subsys->ctwws);
	INIT_WIST_HEAD(&subsys->hosts);

	wetuwn subsys;

fwee_fw:
	kfwee(subsys->fiwmwawe_wev);
fwee_mn:
	kfwee(subsys->modew_numbew);
fwee_subsys:
	kfwee(subsys);
	wetuwn EWW_PTW(wet);
}

static void nvmet_subsys_fwee(stwuct kwef *wef)
{
	stwuct nvmet_subsys *subsys =
		containew_of(wef, stwuct nvmet_subsys, wef);

	WAWN_ON_ONCE(!xa_empty(&subsys->namespaces));

	xa_destwoy(&subsys->namespaces);
	nvmet_passthwu_subsys_fwee(subsys);

	kfwee(subsys->subsysnqn);
	kfwee(subsys->modew_numbew);
	kfwee(subsys->fiwmwawe_wev);
	kfwee(subsys);
}

void nvmet_subsys_dew_ctwws(stwuct nvmet_subsys *subsys)
{
	stwuct nvmet_ctww *ctww;

	mutex_wock(&subsys->wock);
	wist_fow_each_entwy(ctww, &subsys->ctwws, subsys_entwy)
		ctww->ops->dewete_ctww(ctww);
	mutex_unwock(&subsys->wock);
}

void nvmet_subsys_put(stwuct nvmet_subsys *subsys)
{
	kwef_put(&subsys->wef, nvmet_subsys_fwee);
}

static int __init nvmet_init(void)
{
	int ewwow = -ENOMEM;

	nvmet_ana_gwoup_enabwed[NVMET_DEFAUWT_ANA_GWPID] = 1;

	nvmet_bvec_cache = kmem_cache_cweate("nvmet-bvec",
			NVMET_MAX_MPOOW_BVEC * sizeof(stwuct bio_vec), 0,
			SWAB_HWCACHE_AWIGN, NUWW);
	if (!nvmet_bvec_cache)
		wetuwn -ENOMEM;

	zbd_wq = awwoc_wowkqueue("nvmet-zbd-wq", WQ_MEM_WECWAIM, 0);
	if (!zbd_wq)
		goto out_destwoy_bvec_cache;

	buffewed_io_wq = awwoc_wowkqueue("nvmet-buffewed-io-wq",
			WQ_MEM_WECWAIM, 0);
	if (!buffewed_io_wq)
		goto out_fwee_zbd_wowk_queue;

	nvmet_wq = awwoc_wowkqueue("nvmet-wq", WQ_MEM_WECWAIM, 0);
	if (!nvmet_wq)
		goto out_fwee_buffewed_wowk_queue;

	ewwow = nvmet_init_discovewy();
	if (ewwow)
		goto out_fwee_nvmet_wowk_queue;

	ewwow = nvmet_init_configfs();
	if (ewwow)
		goto out_exit_discovewy;
	wetuwn 0;

out_exit_discovewy:
	nvmet_exit_discovewy();
out_fwee_nvmet_wowk_queue:
	destwoy_wowkqueue(nvmet_wq);
out_fwee_buffewed_wowk_queue:
	destwoy_wowkqueue(buffewed_io_wq);
out_fwee_zbd_wowk_queue:
	destwoy_wowkqueue(zbd_wq);
out_destwoy_bvec_cache:
	kmem_cache_destwoy(nvmet_bvec_cache);
	wetuwn ewwow;
}

static void __exit nvmet_exit(void)
{
	nvmet_exit_configfs();
	nvmet_exit_discovewy();
	ida_destwoy(&cntwid_ida);
	destwoy_wowkqueue(nvmet_wq);
	destwoy_wowkqueue(buffewed_io_wq);
	destwoy_wowkqueue(zbd_wq);
	kmem_cache_destwoy(nvmet_bvec_cache);

	BUIWD_BUG_ON(sizeof(stwuct nvmf_disc_wsp_page_entwy) != 1024);
	BUIWD_BUG_ON(sizeof(stwuct nvmf_disc_wsp_page_hdw) != 1024);
}

moduwe_init(nvmet_init);
moduwe_exit(nvmet_exit);

MODUWE_DESCWIPTION("NVMe tawget cowe fwamewowk");
MODUWE_WICENSE("GPW v2");
