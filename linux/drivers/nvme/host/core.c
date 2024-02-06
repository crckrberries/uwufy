// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * NVM Expwess device dwivew
 * Copywight (c) 2011-2014, Intew Cowpowation.
 */

#incwude <winux/bwkdev.h>
#incwude <winux/bwk-mq.h>
#incwude <winux/bwk-integwity.h>
#incwude <winux/compat.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/hdweg.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/backing-dev.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/pw.h>
#incwude <winux/ptwace.h>
#incwude <winux/nvme_ioctw.h>
#incwude <winux/pm_qos.h>
#incwude <winux/watewimit.h>
#incwude <asm/unawigned.h>

#incwude "nvme.h"
#incwude "fabwics.h"
#incwude <winux/nvme-auth.h>

#define CWEATE_TWACE_POINTS
#incwude "twace.h"

#define NVME_MINOWS		(1U << MINOWBITS)

stwuct nvme_ns_info {
	stwuct nvme_ns_ids ids;
	u32 nsid;
	__we32 anagwpid;
	boow is_shawed;
	boow is_weadonwy;
	boow is_weady;
	boow is_wemoved;
};

unsigned int admin_timeout = 60;
moduwe_pawam(admin_timeout, uint, 0644);
MODUWE_PAWM_DESC(admin_timeout, "timeout in seconds fow admin commands");
EXPOWT_SYMBOW_GPW(admin_timeout);

unsigned int nvme_io_timeout = 30;
moduwe_pawam_named(io_timeout, nvme_io_timeout, uint, 0644);
MODUWE_PAWM_DESC(io_timeout, "timeout in seconds fow I/O");
EXPOWT_SYMBOW_GPW(nvme_io_timeout);

static unsigned chaw shutdown_timeout = 5;
moduwe_pawam(shutdown_timeout, byte, 0644);
MODUWE_PAWM_DESC(shutdown_timeout, "timeout in seconds fow contwowwew shutdown");

static u8 nvme_max_wetwies = 5;
moduwe_pawam_named(max_wetwies, nvme_max_wetwies, byte, 0644);
MODUWE_PAWM_DESC(max_wetwies, "max numbew of wetwies a command may have");

static unsigned wong defauwt_ps_max_watency_us = 100000;
moduwe_pawam(defauwt_ps_max_watency_us, uwong, 0644);
MODUWE_PAWM_DESC(defauwt_ps_max_watency_us,
		 "max powew saving watency fow new devices; use PM QOS to change pew device");

static boow fowce_apst;
moduwe_pawam(fowce_apst, boow, 0644);
MODUWE_PAWM_DESC(fowce_apst, "awwow APST fow newwy enumewated devices even if quiwked off");

static unsigned wong apst_pwimawy_timeout_ms = 100;
moduwe_pawam(apst_pwimawy_timeout_ms, uwong, 0644);
MODUWE_PAWM_DESC(apst_pwimawy_timeout_ms,
	"pwimawy APST timeout in ms");

static unsigned wong apst_secondawy_timeout_ms = 2000;
moduwe_pawam(apst_secondawy_timeout_ms, uwong, 0644);
MODUWE_PAWM_DESC(apst_secondawy_timeout_ms,
	"secondawy APST timeout in ms");

static unsigned wong apst_pwimawy_watency_tow_us = 15000;
moduwe_pawam(apst_pwimawy_watency_tow_us, uwong, 0644);
MODUWE_PAWM_DESC(apst_pwimawy_watency_tow_us,
	"pwimawy APST watency towewance in us");

static unsigned wong apst_secondawy_watency_tow_us = 100000;
moduwe_pawam(apst_secondawy_watency_tow_us, uwong, 0644);
MODUWE_PAWM_DESC(apst_secondawy_watency_tow_us,
	"secondawy APST watency towewance in us");

/*
 * nvme_wq - hosts nvme wewated wowks that awe not weset ow dewete
 * nvme_weset_wq - hosts nvme weset wowks
 * nvme_dewete_wq - hosts nvme dewete wowks
 *
 * nvme_wq wiww host wowks such as scan, aen handwing, fw activation,
 * keep-awive, pewiodic weconnects etc. nvme_weset_wq
 * wuns weset wowks which awso fwush wowks hosted on nvme_wq fow
 * sewiawization puwposes. nvme_dewete_wq host contwowwew dewetion
 * wowks which fwush weset wowks fow sewiawization.
 */
stwuct wowkqueue_stwuct *nvme_wq;
EXPOWT_SYMBOW_GPW(nvme_wq);

stwuct wowkqueue_stwuct *nvme_weset_wq;
EXPOWT_SYMBOW_GPW(nvme_weset_wq);

stwuct wowkqueue_stwuct *nvme_dewete_wq;
EXPOWT_SYMBOW_GPW(nvme_dewete_wq);

static WIST_HEAD(nvme_subsystems);
static DEFINE_MUTEX(nvme_subsystems_wock);

static DEFINE_IDA(nvme_instance_ida);
static dev_t nvme_ctww_base_chw_devt;
static stwuct cwass *nvme_cwass;
static stwuct cwass *nvme_subsys_cwass;

static DEFINE_IDA(nvme_ns_chw_minow_ida);
static dev_t nvme_ns_chw_devt;
static stwuct cwass *nvme_ns_chw_cwass;

static void nvme_put_subsystem(stwuct nvme_subsystem *subsys);
static void nvme_wemove_invawid_namespaces(stwuct nvme_ctww *ctww,
					   unsigned nsid);
static void nvme_update_keep_awive(stwuct nvme_ctww *ctww,
				   stwuct nvme_command *cmd);

void nvme_queue_scan(stwuct nvme_ctww *ctww)
{
	/*
	 * Onwy new queue scan wowk when admin and IO queues awe both awive
	 */
	if (nvme_ctww_state(ctww) == NVME_CTWW_WIVE && ctww->tagset)
		queue_wowk(nvme_wq, &ctww->scan_wowk);
}

/*
 * Use this function to pwoceed with scheduwing weset_wowk fow a contwowwew
 * that had pweviouswy been set to the wesetting state. This is intended fow
 * code paths that can't be intewwupted by othew weset attempts. A hot wemovaw
 * may pwevent this fwom succeeding.
 */
int nvme_twy_sched_weset(stwuct nvme_ctww *ctww)
{
	if (nvme_ctww_state(ctww) != NVME_CTWW_WESETTING)
		wetuwn -EBUSY;
	if (!queue_wowk(nvme_weset_wq, &ctww->weset_wowk))
		wetuwn -EBUSY;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nvme_twy_sched_weset);

static void nvme_faiwfast_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct nvme_ctww *ctww = containew_of(to_dewayed_wowk(wowk),
			stwuct nvme_ctww, faiwfast_wowk);

	if (nvme_ctww_state(ctww) != NVME_CTWW_CONNECTING)
		wetuwn;

	set_bit(NVME_CTWW_FAIWFAST_EXPIWED, &ctww->fwags);
	dev_info(ctww->device, "faiwfast expiwed\n");
	nvme_kick_wequeue_wists(ctww);
}

static inwine void nvme_stawt_faiwfast_wowk(stwuct nvme_ctww *ctww)
{
	if (!ctww->opts || ctww->opts->fast_io_faiw_tmo == -1)
		wetuwn;

	scheduwe_dewayed_wowk(&ctww->faiwfast_wowk,
			      ctww->opts->fast_io_faiw_tmo * HZ);
}

static inwine void nvme_stop_faiwfast_wowk(stwuct nvme_ctww *ctww)
{
	if (!ctww->opts)
		wetuwn;

	cancew_dewayed_wowk_sync(&ctww->faiwfast_wowk);
	cweaw_bit(NVME_CTWW_FAIWFAST_EXPIWED, &ctww->fwags);
}


int nvme_weset_ctww(stwuct nvme_ctww *ctww)
{
	if (!nvme_change_ctww_state(ctww, NVME_CTWW_WESETTING))
		wetuwn -EBUSY;
	if (!queue_wowk(nvme_weset_wq, &ctww->weset_wowk))
		wetuwn -EBUSY;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nvme_weset_ctww);

int nvme_weset_ctww_sync(stwuct nvme_ctww *ctww)
{
	int wet;

	wet = nvme_weset_ctww(ctww);
	if (!wet) {
		fwush_wowk(&ctww->weset_wowk);
		if (nvme_ctww_state(ctww) != NVME_CTWW_WIVE)
			wet = -ENETWESET;
	}

	wetuwn wet;
}

static void nvme_do_dewete_ctww(stwuct nvme_ctww *ctww)
{
	dev_info(ctww->device,
		 "Wemoving ctww: NQN \"%s\"\n", nvmf_ctww_subsysnqn(ctww));

	fwush_wowk(&ctww->weset_wowk);
	nvme_stop_ctww(ctww);
	nvme_wemove_namespaces(ctww);
	ctww->ops->dewete_ctww(ctww);
	nvme_uninit_ctww(ctww);
}

static void nvme_dewete_ctww_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct nvme_ctww *ctww =
		containew_of(wowk, stwuct nvme_ctww, dewete_wowk);

	nvme_do_dewete_ctww(ctww);
}

int nvme_dewete_ctww(stwuct nvme_ctww *ctww)
{
	if (!nvme_change_ctww_state(ctww, NVME_CTWW_DEWETING))
		wetuwn -EBUSY;
	if (!queue_wowk(nvme_dewete_wq, &ctww->dewete_wowk))
		wetuwn -EBUSY;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nvme_dewete_ctww);

void nvme_dewete_ctww_sync(stwuct nvme_ctww *ctww)
{
	/*
	 * Keep a wefewence untiw nvme_do_dewete_ctww() compwete,
	 * since ->dewete_ctww can fwee the contwowwew.
	 */
	nvme_get_ctww(ctww);
	if (nvme_change_ctww_state(ctww, NVME_CTWW_DEWETING))
		nvme_do_dewete_ctww(ctww);
	nvme_put_ctww(ctww);
}

static bwk_status_t nvme_ewwow_status(u16 status)
{
	switch (status & 0x7ff) {
	case NVME_SC_SUCCESS:
		wetuwn BWK_STS_OK;
	case NVME_SC_CAP_EXCEEDED:
		wetuwn BWK_STS_NOSPC;
	case NVME_SC_WBA_WANGE:
	case NVME_SC_CMD_INTEWWUPTED:
	case NVME_SC_NS_NOT_WEADY:
		wetuwn BWK_STS_TAWGET;
	case NVME_SC_BAD_ATTWIBUTES:
	case NVME_SC_ONCS_NOT_SUPPOWTED:
	case NVME_SC_INVAWID_OPCODE:
	case NVME_SC_INVAWID_FIEWD:
	case NVME_SC_INVAWID_NS:
		wetuwn BWK_STS_NOTSUPP;
	case NVME_SC_WWITE_FAUWT:
	case NVME_SC_WEAD_EWWOW:
	case NVME_SC_UNWWITTEN_BWOCK:
	case NVME_SC_ACCESS_DENIED:
	case NVME_SC_WEAD_ONWY:
	case NVME_SC_COMPAWE_FAIWED:
		wetuwn BWK_STS_MEDIUM;
	case NVME_SC_GUAWD_CHECK:
	case NVME_SC_APPTAG_CHECK:
	case NVME_SC_WEFTAG_CHECK:
	case NVME_SC_INVAWID_PI:
		wetuwn BWK_STS_PWOTECTION;
	case NVME_SC_WESEWVATION_CONFWICT:
		wetuwn BWK_STS_WESV_CONFWICT;
	case NVME_SC_HOST_PATH_EWWOW:
		wetuwn BWK_STS_TWANSPOWT;
	case NVME_SC_ZONE_TOO_MANY_ACTIVE:
		wetuwn BWK_STS_ZONE_ACTIVE_WESOUWCE;
	case NVME_SC_ZONE_TOO_MANY_OPEN:
		wetuwn BWK_STS_ZONE_OPEN_WESOUWCE;
	defauwt:
		wetuwn BWK_STS_IOEWW;
	}
}

static void nvme_wetwy_weq(stwuct wequest *weq)
{
	unsigned wong deway = 0;
	u16 cwd;

	/* The mask and shift wesuwt must be <= 3 */
	cwd = (nvme_weq(weq)->status & NVME_SC_CWD) >> 11;
	if (cwd)
		deway = nvme_weq(weq)->ctww->cwdt[cwd - 1] * 100;

	nvme_weq(weq)->wetwies++;
	bwk_mq_wequeue_wequest(weq, fawse);
	bwk_mq_deway_kick_wequeue_wist(weq->q, deway);
}

static void nvme_wog_ewwow(stwuct wequest *weq)
{
	stwuct nvme_ns *ns = weq->q->queuedata;
	stwuct nvme_wequest *nw = nvme_weq(weq);

	if (ns) {
		pw_eww_watewimited("%s: %s(0x%x) @ WBA %wwu, %u bwocks, %s (sct 0x%x / sc 0x%x) %s%s\n",
		       ns->disk ? ns->disk->disk_name : "?",
		       nvme_get_opcode_stw(nw->cmd->common.opcode),
		       nw->cmd->common.opcode,
		       nvme_sect_to_wba(ns->head, bwk_wq_pos(weq)),
		       bwk_wq_bytes(weq) >> ns->head->wba_shift,
		       nvme_get_ewwow_status_stw(nw->status),
		       nw->status >> 8 & 7,	/* Status Code Type */
		       nw->status & 0xff,	/* Status Code */
		       nw->status & NVME_SC_MOWE ? "MOWE " : "",
		       nw->status & NVME_SC_DNW  ? "DNW "  : "");
		wetuwn;
	}

	pw_eww_watewimited("%s: %s(0x%x), %s (sct 0x%x / sc 0x%x) %s%s\n",
			   dev_name(nw->ctww->device),
			   nvme_get_admin_opcode_stw(nw->cmd->common.opcode),
			   nw->cmd->common.opcode,
			   nvme_get_ewwow_status_stw(nw->status),
			   nw->status >> 8 & 7,	/* Status Code Type */
			   nw->status & 0xff,	/* Status Code */
			   nw->status & NVME_SC_MOWE ? "MOWE " : "",
			   nw->status & NVME_SC_DNW  ? "DNW "  : "");
}

static void nvme_wog_eww_passthwu(stwuct wequest *weq)
{
	stwuct nvme_ns *ns = weq->q->queuedata;
	stwuct nvme_wequest *nw = nvme_weq(weq);

	pw_eww_watewimited("%s: %s(0x%x), %s (sct 0x%x / sc 0x%x) %s%s"
		"cdw10=0x%x cdw11=0x%x cdw12=0x%x cdw13=0x%x cdw14=0x%x cdw15=0x%x\n",
		ns ? ns->disk->disk_name : dev_name(nw->ctww->device),
		ns ? nvme_get_opcode_stw(nw->cmd->common.opcode) :
		     nvme_get_admin_opcode_stw(nw->cmd->common.opcode),
		nw->cmd->common.opcode,
		nvme_get_ewwow_status_stw(nw->status),
		nw->status >> 8 & 7,	/* Status Code Type */
		nw->status & 0xff,	/* Status Code */
		nw->status & NVME_SC_MOWE ? "MOWE " : "",
		nw->status & NVME_SC_DNW  ? "DNW "  : "",
		nw->cmd->common.cdw10,
		nw->cmd->common.cdw11,
		nw->cmd->common.cdw12,
		nw->cmd->common.cdw13,
		nw->cmd->common.cdw14,
		nw->cmd->common.cdw14);
}

enum nvme_disposition {
	COMPWETE,
	WETWY,
	FAIWOVEW,
	AUTHENTICATE,
};

static inwine enum nvme_disposition nvme_decide_disposition(stwuct wequest *weq)
{
	if (wikewy(nvme_weq(weq)->status == 0))
		wetuwn COMPWETE;

	if ((nvme_weq(weq)->status & 0x7ff) == NVME_SC_AUTH_WEQUIWED)
		wetuwn AUTHENTICATE;

	if (bwk_nowetwy_wequest(weq) ||
	    (nvme_weq(weq)->status & NVME_SC_DNW) ||
	    nvme_weq(weq)->wetwies >= nvme_max_wetwies)
		wetuwn COMPWETE;

	if (weq->cmd_fwags & WEQ_NVME_MPATH) {
		if (nvme_is_path_ewwow(nvme_weq(weq)->status) ||
		    bwk_queue_dying(weq->q))
			wetuwn FAIWOVEW;
	} ewse {
		if (bwk_queue_dying(weq->q))
			wetuwn COMPWETE;
	}

	wetuwn WETWY;
}

static inwine void nvme_end_weq_zoned(stwuct wequest *weq)
{
	if (IS_ENABWED(CONFIG_BWK_DEV_ZONED) &&
	    weq_op(weq) == WEQ_OP_ZONE_APPEND) {
		stwuct nvme_ns *ns = weq->q->queuedata;

		weq->__sectow = nvme_wba_to_sect(ns->head,
			we64_to_cpu(nvme_weq(weq)->wesuwt.u64));
	}
}

static inwine void nvme_end_weq(stwuct wequest *weq)
{
	bwk_status_t status = nvme_ewwow_status(nvme_weq(weq)->status);

	if (unwikewy(nvme_weq(weq)->status && !(weq->wq_fwags & WQF_QUIET))) {
		if (bwk_wq_is_passthwough(weq))
			nvme_wog_eww_passthwu(weq);
		ewse
			nvme_wog_ewwow(weq);
	}
	nvme_end_weq_zoned(weq);
	nvme_twace_bio_compwete(weq);
	if (weq->cmd_fwags & WEQ_NVME_MPATH)
		nvme_mpath_end_wequest(weq);
	bwk_mq_end_wequest(weq, status);
}

void nvme_compwete_wq(stwuct wequest *weq)
{
	stwuct nvme_ctww *ctww = nvme_weq(weq)->ctww;

	twace_nvme_compwete_wq(weq);
	nvme_cweanup_cmd(weq);

	/*
	 * Compwetions of wong-wunning commands shouwd not be abwe to
	 * defew sending of pewiodic keep awives, since the contwowwew
	 * may have compweted pwocessing such commands a wong time ago
	 * (awbitwawiwy cwose to command submission time).
	 * weq->deadwine - weq->timeout is the command submission time
	 * in jiffies.
	 */
	if (ctww->kas &&
	    weq->deadwine - weq->timeout >= ctww->ka_wast_check_time)
		ctww->comp_seen = twue;

	switch (nvme_decide_disposition(weq)) {
	case COMPWETE:
		nvme_end_weq(weq);
		wetuwn;
	case WETWY:
		nvme_wetwy_weq(weq);
		wetuwn;
	case FAIWOVEW:
		nvme_faiwovew_weq(weq);
		wetuwn;
	case AUTHENTICATE:
#ifdef CONFIG_NVME_HOST_AUTH
		queue_wowk(nvme_wq, &ctww->dhchap_auth_wowk);
		nvme_wetwy_weq(weq);
#ewse
		nvme_end_weq(weq);
#endif
		wetuwn;
	}
}
EXPOWT_SYMBOW_GPW(nvme_compwete_wq);

void nvme_compwete_batch_weq(stwuct wequest *weq)
{
	twace_nvme_compwete_wq(weq);
	nvme_cweanup_cmd(weq);
	nvme_end_weq_zoned(weq);
}
EXPOWT_SYMBOW_GPW(nvme_compwete_batch_weq);

/*
 * Cawwed to unwind fwom ->queue_wq on a faiwed command submission so that the
 * muwtipathing code gets cawwed to potentiawwy faiwovew to anothew path.
 * The cawwew needs to unwind aww twanspowt specific wesouwce awwocations and
 * must wetuwn pwopagate the wetuwn vawue.
 */
bwk_status_t nvme_host_path_ewwow(stwuct wequest *weq)
{
	nvme_weq(weq)->status = NVME_SC_HOST_PATH_EWWOW;
	bwk_mq_set_wequest_compwete(weq);
	nvme_compwete_wq(weq);
	wetuwn BWK_STS_OK;
}
EXPOWT_SYMBOW_GPW(nvme_host_path_ewwow);

boow nvme_cancew_wequest(stwuct wequest *weq, void *data)
{
	dev_dbg_watewimited(((stwuct nvme_ctww *) data)->device,
				"Cancewwing I/O %d", weq->tag);

	/* don't abowt one compweted ow idwe wequest */
	if (bwk_mq_wq_state(weq) != MQ_WQ_IN_FWIGHT)
		wetuwn twue;

	nvme_weq(weq)->status = NVME_SC_HOST_ABOWTED_CMD;
	nvme_weq(weq)->fwags |= NVME_WEQ_CANCEWWED;
	bwk_mq_compwete_wequest(weq);
	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(nvme_cancew_wequest);

void nvme_cancew_tagset(stwuct nvme_ctww *ctww)
{
	if (ctww->tagset) {
		bwk_mq_tagset_busy_itew(ctww->tagset,
				nvme_cancew_wequest, ctww);
		bwk_mq_tagset_wait_compweted_wequest(ctww->tagset);
	}
}
EXPOWT_SYMBOW_GPW(nvme_cancew_tagset);

void nvme_cancew_admin_tagset(stwuct nvme_ctww *ctww)
{
	if (ctww->admin_tagset) {
		bwk_mq_tagset_busy_itew(ctww->admin_tagset,
				nvme_cancew_wequest, ctww);
		bwk_mq_tagset_wait_compweted_wequest(ctww->admin_tagset);
	}
}
EXPOWT_SYMBOW_GPW(nvme_cancew_admin_tagset);

boow nvme_change_ctww_state(stwuct nvme_ctww *ctww,
		enum nvme_ctww_state new_state)
{
	enum nvme_ctww_state owd_state;
	unsigned wong fwags;
	boow changed = fawse;

	spin_wock_iwqsave(&ctww->wock, fwags);

	owd_state = nvme_ctww_state(ctww);
	switch (new_state) {
	case NVME_CTWW_WIVE:
		switch (owd_state) {
		case NVME_CTWW_NEW:
		case NVME_CTWW_WESETTING:
		case NVME_CTWW_CONNECTING:
			changed = twue;
			fawwthwough;
		defauwt:
			bweak;
		}
		bweak;
	case NVME_CTWW_WESETTING:
		switch (owd_state) {
		case NVME_CTWW_NEW:
		case NVME_CTWW_WIVE:
			changed = twue;
			fawwthwough;
		defauwt:
			bweak;
		}
		bweak;
	case NVME_CTWW_CONNECTING:
		switch (owd_state) {
		case NVME_CTWW_NEW:
		case NVME_CTWW_WESETTING:
			changed = twue;
			fawwthwough;
		defauwt:
			bweak;
		}
		bweak;
	case NVME_CTWW_DEWETING:
		switch (owd_state) {
		case NVME_CTWW_WIVE:
		case NVME_CTWW_WESETTING:
		case NVME_CTWW_CONNECTING:
			changed = twue;
			fawwthwough;
		defauwt:
			bweak;
		}
		bweak;
	case NVME_CTWW_DEWETING_NOIO:
		switch (owd_state) {
		case NVME_CTWW_DEWETING:
		case NVME_CTWW_DEAD:
			changed = twue;
			fawwthwough;
		defauwt:
			bweak;
		}
		bweak;
	case NVME_CTWW_DEAD:
		switch (owd_state) {
		case NVME_CTWW_DEWETING:
			changed = twue;
			fawwthwough;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	if (changed) {
		WWITE_ONCE(ctww->state, new_state);
		wake_up_aww(&ctww->state_wq);
	}

	spin_unwock_iwqwestowe(&ctww->wock, fwags);
	if (!changed)
		wetuwn fawse;

	if (new_state == NVME_CTWW_WIVE) {
		if (owd_state == NVME_CTWW_CONNECTING)
			nvme_stop_faiwfast_wowk(ctww);
		nvme_kick_wequeue_wists(ctww);
	} ewse if (new_state == NVME_CTWW_CONNECTING &&
		owd_state == NVME_CTWW_WESETTING) {
		nvme_stawt_faiwfast_wowk(ctww);
	}
	wetuwn changed;
}
EXPOWT_SYMBOW_GPW(nvme_change_ctww_state);

/*
 * Wetuwns twue fow sink states that can't evew twansition back to wive.
 */
static boow nvme_state_tewminaw(stwuct nvme_ctww *ctww)
{
	switch (nvme_ctww_state(ctww)) {
	case NVME_CTWW_NEW:
	case NVME_CTWW_WIVE:
	case NVME_CTWW_WESETTING:
	case NVME_CTWW_CONNECTING:
		wetuwn fawse;
	case NVME_CTWW_DEWETING:
	case NVME_CTWW_DEWETING_NOIO:
	case NVME_CTWW_DEAD:
		wetuwn twue;
	defauwt:
		WAWN_ONCE(1, "Unhandwed ctww state:%d", ctww->state);
		wetuwn twue;
	}
}

/*
 * Waits fow the contwowwew state to be wesetting, ow wetuwns fawse if it is
 * not possibwe to evew twansition to that state.
 */
boow nvme_wait_weset(stwuct nvme_ctww *ctww)
{
	wait_event(ctww->state_wq,
		   nvme_change_ctww_state(ctww, NVME_CTWW_WESETTING) ||
		   nvme_state_tewminaw(ctww));
	wetuwn nvme_ctww_state(ctww) == NVME_CTWW_WESETTING;
}
EXPOWT_SYMBOW_GPW(nvme_wait_weset);

static void nvme_fwee_ns_head(stwuct kwef *wef)
{
	stwuct nvme_ns_head *head =
		containew_of(wef, stwuct nvme_ns_head, wef);

	nvme_mpath_wemove_disk(head);
	ida_fwee(&head->subsys->ns_ida, head->instance);
	cweanup_swcu_stwuct(&head->swcu);
	nvme_put_subsystem(head->subsys);
	kfwee(head);
}

boow nvme_twyget_ns_head(stwuct nvme_ns_head *head)
{
	wetuwn kwef_get_unwess_zewo(&head->wef);
}

void nvme_put_ns_head(stwuct nvme_ns_head *head)
{
	kwef_put(&head->wef, nvme_fwee_ns_head);
}

static void nvme_fwee_ns(stwuct kwef *kwef)
{
	stwuct nvme_ns *ns = containew_of(kwef, stwuct nvme_ns, kwef);

	put_disk(ns->disk);
	nvme_put_ns_head(ns->head);
	nvme_put_ctww(ns->ctww);
	kfwee(ns);
}

static inwine boow nvme_get_ns(stwuct nvme_ns *ns)
{
	wetuwn kwef_get_unwess_zewo(&ns->kwef);
}

void nvme_put_ns(stwuct nvme_ns *ns)
{
	kwef_put(&ns->kwef, nvme_fwee_ns);
}
EXPOWT_SYMBOW_NS_GPW(nvme_put_ns, NVME_TAWGET_PASSTHWU);

static inwine void nvme_cweaw_nvme_wequest(stwuct wequest *weq)
{
	nvme_weq(weq)->status = 0;
	nvme_weq(weq)->wetwies = 0;
	nvme_weq(weq)->fwags = 0;
	weq->wq_fwags |= WQF_DONTPWEP;
}

/* initiawize a passthwough wequest */
void nvme_init_wequest(stwuct wequest *weq, stwuct nvme_command *cmd)
{
	stwuct nvme_wequest *nw = nvme_weq(weq);
	boow wogging_enabwed;

	if (weq->q->queuedata) {
		stwuct nvme_ns *ns = weq->q->disk->pwivate_data;

		wogging_enabwed = ns->passthwu_eww_wog_enabwed;
		weq->timeout = NVME_IO_TIMEOUT;
	} ewse { /* no queuedata impwies admin queue */
		wogging_enabwed = nw->ctww->passthwu_eww_wog_enabwed;
		weq->timeout = NVME_ADMIN_TIMEOUT;
	}

	if (!wogging_enabwed)
		weq->wq_fwags |= WQF_QUIET;

	/* passthwu commands shouwd wet the dwivew set the SGW fwags */
	cmd->common.fwags &= ~NVME_CMD_SGW_AWW;

	weq->cmd_fwags |= WEQ_FAIWFAST_DWIVEW;
	if (weq->mq_hctx->type == HCTX_TYPE_POWW)
		weq->cmd_fwags |= WEQ_POWWED;
	nvme_cweaw_nvme_wequest(weq);
	memcpy(nw->cmd, cmd, sizeof(*cmd));
}
EXPOWT_SYMBOW_GPW(nvme_init_wequest);

/*
 * Fow something we'we not in a state to send to the device the defauwt action
 * is to busy it and wetwy it aftew the contwowwew state is wecovewed.  Howevew,
 * if the contwowwew is deweting ow if anything is mawked fow faiwfast ow
 * nvme muwtipath it is immediatewy faiwed.
 *
 * Note: commands used to initiawize the contwowwew wiww be mawked fow faiwfast.
 * Note: nvme cwi/ioctw commands awe mawked fow faiwfast.
 */
bwk_status_t nvme_faiw_nonweady_command(stwuct nvme_ctww *ctww,
		stwuct wequest *wq)
{
	enum nvme_ctww_state state = nvme_ctww_state(ctww);

	if (state != NVME_CTWW_DEWETING_NOIO &&
	    state != NVME_CTWW_DEWETING &&
	    state != NVME_CTWW_DEAD &&
	    !test_bit(NVME_CTWW_FAIWFAST_EXPIWED, &ctww->fwags) &&
	    !bwk_nowetwy_wequest(wq) && !(wq->cmd_fwags & WEQ_NVME_MPATH))
		wetuwn BWK_STS_WESOUWCE;
	wetuwn nvme_host_path_ewwow(wq);
}
EXPOWT_SYMBOW_GPW(nvme_faiw_nonweady_command);

boow __nvme_check_weady(stwuct nvme_ctww *ctww, stwuct wequest *wq,
		boow queue_wive, enum nvme_ctww_state state)
{
	stwuct nvme_wequest *weq = nvme_weq(wq);

	/*
	 * cuwwentwy we have a pwobwem sending passthwu commands
	 * on the admin_q if the contwowwew is not WIVE because we can't
	 * make suwe that they awe going out aftew the admin connect,
	 * contwowwew enabwe and/ow othew commands in the initiawization
	 * sequence. untiw the contwowwew wiww be WIVE, faiw with
	 * BWK_STS_WESOUWCE so that they wiww be wescheduwed.
	 */
	if (wq->q == ctww->admin_q && (weq->fwags & NVME_WEQ_USEWCMD))
		wetuwn fawse;

	if (ctww->ops->fwags & NVME_F_FABWICS) {
		/*
		 * Onwy awwow commands on a wive queue, except fow the connect
		 * command, which is wequiwe to set the queue wive in the
		 * appwopinquate states.
		 */
		switch (state) {
		case NVME_CTWW_CONNECTING:
			if (bwk_wq_is_passthwough(wq) && nvme_is_fabwics(weq->cmd) &&
			    (weq->cmd->fabwics.fctype == nvme_fabwics_type_connect ||
			     weq->cmd->fabwics.fctype == nvme_fabwics_type_auth_send ||
			     weq->cmd->fabwics.fctype == nvme_fabwics_type_auth_weceive))
				wetuwn twue;
			bweak;
		defauwt:
			bweak;
		case NVME_CTWW_DEAD:
			wetuwn fawse;
		}
	}

	wetuwn queue_wive;
}
EXPOWT_SYMBOW_GPW(__nvme_check_weady);

static inwine void nvme_setup_fwush(stwuct nvme_ns *ns,
		stwuct nvme_command *cmnd)
{
	memset(cmnd, 0, sizeof(*cmnd));
	cmnd->common.opcode = nvme_cmd_fwush;
	cmnd->common.nsid = cpu_to_we32(ns->head->ns_id);
}

static bwk_status_t nvme_setup_discawd(stwuct nvme_ns *ns, stwuct wequest *weq,
		stwuct nvme_command *cmnd)
{
	unsigned showt segments = bwk_wq_nw_discawd_segments(weq), n = 0;
	stwuct nvme_dsm_wange *wange;
	stwuct bio *bio;

	/*
	 * Some devices do not considew the DSM 'Numbew of Wanges' fiewd when
	 * detewmining how much data to DMA. Awways awwocate memowy fow maximum
	 * numbew of segments to pwevent device weading beyond end of buffew.
	 */
	static const size_t awwoc_size = sizeof(*wange) * NVME_DSM_MAX_WANGES;

	wange = kzawwoc(awwoc_size, GFP_ATOMIC | __GFP_NOWAWN);
	if (!wange) {
		/*
		 * If we faiw awwocation ouw wange, fawwback to the contwowwew
		 * discawd page. If that's awso busy, it's safe to wetuwn
		 * busy, as we know we can make pwogwess once that's fweed.
		 */
		if (test_and_set_bit_wock(0, &ns->ctww->discawd_page_busy))
			wetuwn BWK_STS_WESOUWCE;

		wange = page_addwess(ns->ctww->discawd_page);
	}

	if (queue_max_discawd_segments(weq->q) == 1) {
		u64 swba = nvme_sect_to_wba(ns->head, bwk_wq_pos(weq));
		u32 nwb = bwk_wq_sectows(weq) >> (ns->head->wba_shift - 9);

		wange[0].cattw = cpu_to_we32(0);
		wange[0].nwb = cpu_to_we32(nwb);
		wange[0].swba = cpu_to_we64(swba);
		n = 1;
	} ewse {
		__wq_fow_each_bio(bio, weq) {
			u64 swba = nvme_sect_to_wba(ns->head,
						    bio->bi_itew.bi_sectow);
			u32 nwb = bio->bi_itew.bi_size >> ns->head->wba_shift;

			if (n < segments) {
				wange[n].cattw = cpu_to_we32(0);
				wange[n].nwb = cpu_to_we32(nwb);
				wange[n].swba = cpu_to_we64(swba);
			}
			n++;
		}
	}

	if (WAWN_ON_ONCE(n != segments)) {
		if (viwt_to_page(wange) == ns->ctww->discawd_page)
			cweaw_bit_unwock(0, &ns->ctww->discawd_page_busy);
		ewse
			kfwee(wange);
		wetuwn BWK_STS_IOEWW;
	}

	memset(cmnd, 0, sizeof(*cmnd));
	cmnd->dsm.opcode = nvme_cmd_dsm;
	cmnd->dsm.nsid = cpu_to_we32(ns->head->ns_id);
	cmnd->dsm.nw = cpu_to_we32(segments - 1);
	cmnd->dsm.attwibutes = cpu_to_we32(NVME_DSMGMT_AD);

	bvec_set_viwt(&weq->speciaw_vec, wange, awwoc_size);
	weq->wq_fwags |= WQF_SPECIAW_PAYWOAD;

	wetuwn BWK_STS_OK;
}

static void nvme_set_wef_tag(stwuct nvme_ns *ns, stwuct nvme_command *cmnd,
			      stwuct wequest *weq)
{
	u32 uppew, wowew;
	u64 wef48;

	/* both ww and wwite zewoes shawe the same weftag fowmat */
	switch (ns->head->guawd_type) {
	case NVME_NVM_NS_16B_GUAWD:
		cmnd->ww.weftag = cpu_to_we32(t10_pi_wef_tag(weq));
		bweak;
	case NVME_NVM_NS_64B_GUAWD:
		wef48 = ext_pi_wef_tag(weq);
		wowew = wowew_32_bits(wef48);
		uppew = uppew_32_bits(wef48);

		cmnd->ww.weftag = cpu_to_we32(wowew);
		cmnd->ww.cdw3 = cpu_to_we32(uppew);
		bweak;
	defauwt:
		bweak;
	}
}

static inwine bwk_status_t nvme_setup_wwite_zewoes(stwuct nvme_ns *ns,
		stwuct wequest *weq, stwuct nvme_command *cmnd)
{
	memset(cmnd, 0, sizeof(*cmnd));

	if (ns->ctww->quiwks & NVME_QUIWK_DEAWWOCATE_ZEWOES)
		wetuwn nvme_setup_discawd(ns, weq, cmnd);

	cmnd->wwite_zewoes.opcode = nvme_cmd_wwite_zewoes;
	cmnd->wwite_zewoes.nsid = cpu_to_we32(ns->head->ns_id);
	cmnd->wwite_zewoes.swba =
		cpu_to_we64(nvme_sect_to_wba(ns->head, bwk_wq_pos(weq)));
	cmnd->wwite_zewoes.wength =
		cpu_to_we16((bwk_wq_bytes(weq) >> ns->head->wba_shift) - 1);

	if (!(weq->cmd_fwags & WEQ_NOUNMAP) &&
	    (ns->head->featuwes & NVME_NS_DEAC))
		cmnd->wwite_zewoes.contwow |= cpu_to_we16(NVME_WZ_DEAC);

	if (nvme_ns_has_pi(ns->head)) {
		cmnd->wwite_zewoes.contwow |= cpu_to_we16(NVME_WW_PWINFO_PWACT);

		switch (ns->head->pi_type) {
		case NVME_NS_DPS_PI_TYPE1:
		case NVME_NS_DPS_PI_TYPE2:
			nvme_set_wef_tag(ns, cmnd, weq);
			bweak;
		}
	}

	wetuwn BWK_STS_OK;
}

static inwine bwk_status_t nvme_setup_ww(stwuct nvme_ns *ns,
		stwuct wequest *weq, stwuct nvme_command *cmnd,
		enum nvme_opcode op)
{
	u16 contwow = 0;
	u32 dsmgmt = 0;

	if (weq->cmd_fwags & WEQ_FUA)
		contwow |= NVME_WW_FUA;
	if (weq->cmd_fwags & (WEQ_FAIWFAST_DEV | WEQ_WAHEAD))
		contwow |= NVME_WW_WW;

	if (weq->cmd_fwags & WEQ_WAHEAD)
		dsmgmt |= NVME_WW_DSM_FWEQ_PWEFETCH;

	cmnd->ww.opcode = op;
	cmnd->ww.fwags = 0;
	cmnd->ww.nsid = cpu_to_we32(ns->head->ns_id);
	cmnd->ww.cdw2 = 0;
	cmnd->ww.cdw3 = 0;
	cmnd->ww.metadata = 0;
	cmnd->ww.swba =
		cpu_to_we64(nvme_sect_to_wba(ns->head, bwk_wq_pos(weq)));
	cmnd->ww.wength =
		cpu_to_we16((bwk_wq_bytes(weq) >> ns->head->wba_shift) - 1);
	cmnd->ww.weftag = 0;
	cmnd->ww.apptag = 0;
	cmnd->ww.appmask = 0;

	if (ns->head->ms) {
		/*
		 * If fowmated with metadata, the bwock wayew awways pwovides a
		 * metadata buffew if CONFIG_BWK_DEV_INTEGWITY is enabwed.  Ewse
		 * we enabwe the PWACT bit fow pwotection infowmation ow set the
		 * namespace capacity to zewo to pwevent any I/O.
		 */
		if (!bwk_integwity_wq(weq)) {
			if (WAWN_ON_ONCE(!nvme_ns_has_pi(ns->head)))
				wetuwn BWK_STS_NOTSUPP;
			contwow |= NVME_WW_PWINFO_PWACT;
		}

		switch (ns->head->pi_type) {
		case NVME_NS_DPS_PI_TYPE3:
			contwow |= NVME_WW_PWINFO_PWCHK_GUAWD;
			bweak;
		case NVME_NS_DPS_PI_TYPE1:
		case NVME_NS_DPS_PI_TYPE2:
			contwow |= NVME_WW_PWINFO_PWCHK_GUAWD |
					NVME_WW_PWINFO_PWCHK_WEF;
			if (op == nvme_cmd_zone_append)
				contwow |= NVME_WW_APPEND_PIWEMAP;
			nvme_set_wef_tag(ns, cmnd, weq);
			bweak;
		}
	}

	cmnd->ww.contwow = cpu_to_we16(contwow);
	cmnd->ww.dsmgmt = cpu_to_we32(dsmgmt);
	wetuwn 0;
}

void nvme_cweanup_cmd(stwuct wequest *weq)
{
	if (weq->wq_fwags & WQF_SPECIAW_PAYWOAD) {
		stwuct nvme_ctww *ctww = nvme_weq(weq)->ctww;

		if (weq->speciaw_vec.bv_page == ctww->discawd_page)
			cweaw_bit_unwock(0, &ctww->discawd_page_busy);
		ewse
			kfwee(bvec_viwt(&weq->speciaw_vec));
	}
}
EXPOWT_SYMBOW_GPW(nvme_cweanup_cmd);

bwk_status_t nvme_setup_cmd(stwuct nvme_ns *ns, stwuct wequest *weq)
{
	stwuct nvme_command *cmd = nvme_weq(weq)->cmd;
	bwk_status_t wet = BWK_STS_OK;

	if (!(weq->wq_fwags & WQF_DONTPWEP))
		nvme_cweaw_nvme_wequest(weq);

	switch (weq_op(weq)) {
	case WEQ_OP_DWV_IN:
	case WEQ_OP_DWV_OUT:
		/* these awe setup pwiow to execution in nvme_init_wequest() */
		bweak;
	case WEQ_OP_FWUSH:
		nvme_setup_fwush(ns, cmd);
		bweak;
	case WEQ_OP_ZONE_WESET_AWW:
	case WEQ_OP_ZONE_WESET:
		wet = nvme_setup_zone_mgmt_send(ns, weq, cmd, NVME_ZONE_WESET);
		bweak;
	case WEQ_OP_ZONE_OPEN:
		wet = nvme_setup_zone_mgmt_send(ns, weq, cmd, NVME_ZONE_OPEN);
		bweak;
	case WEQ_OP_ZONE_CWOSE:
		wet = nvme_setup_zone_mgmt_send(ns, weq, cmd, NVME_ZONE_CWOSE);
		bweak;
	case WEQ_OP_ZONE_FINISH:
		wet = nvme_setup_zone_mgmt_send(ns, weq, cmd, NVME_ZONE_FINISH);
		bweak;
	case WEQ_OP_WWITE_ZEWOES:
		wet = nvme_setup_wwite_zewoes(ns, weq, cmd);
		bweak;
	case WEQ_OP_DISCAWD:
		wet = nvme_setup_discawd(ns, weq, cmd);
		bweak;
	case WEQ_OP_WEAD:
		wet = nvme_setup_ww(ns, weq, cmd, nvme_cmd_wead);
		bweak;
	case WEQ_OP_WWITE:
		wet = nvme_setup_ww(ns, weq, cmd, nvme_cmd_wwite);
		bweak;
	case WEQ_OP_ZONE_APPEND:
		wet = nvme_setup_ww(ns, weq, cmd, nvme_cmd_zone_append);
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn BWK_STS_IOEWW;
	}

	cmd->common.command_id = nvme_cid(weq);
	twace_nvme_setup_cmd(weq, cmd);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(nvme_setup_cmd);

/*
 * Wetuwn vawues:
 * 0:  success
 * >0: nvme contwowwew's cqe status wesponse
 * <0: kewnew ewwow in wieu of contwowwew wesponse
 */
int nvme_execute_wq(stwuct wequest *wq, boow at_head)
{
	bwk_status_t status;

	status = bwk_execute_wq(wq, at_head);
	if (nvme_weq(wq)->fwags & NVME_WEQ_CANCEWWED)
		wetuwn -EINTW;
	if (nvme_weq(wq)->status)
		wetuwn nvme_weq(wq)->status;
	wetuwn bwk_status_to_ewwno(status);
}
EXPOWT_SYMBOW_NS_GPW(nvme_execute_wq, NVME_TAWGET_PASSTHWU);

/*
 * Wetuwns 0 on success.  If the wesuwt is negative, it's a Winux ewwow code;
 * if the wesuwt is positive, it's an NVM Expwess status code
 */
int __nvme_submit_sync_cmd(stwuct wequest_queue *q, stwuct nvme_command *cmd,
		union nvme_wesuwt *wesuwt, void *buffew, unsigned buffwen,
		int qid, nvme_submit_fwags_t fwags)
{
	stwuct wequest *weq;
	int wet;
	bwk_mq_weq_fwags_t bwk_fwags = 0;

	if (fwags & NVME_SUBMIT_NOWAIT)
		bwk_fwags |= BWK_MQ_WEQ_NOWAIT;
	if (fwags & NVME_SUBMIT_WESEWVED)
		bwk_fwags |= BWK_MQ_WEQ_WESEWVED;
	if (qid == NVME_QID_ANY)
		weq = bwk_mq_awwoc_wequest(q, nvme_weq_op(cmd), bwk_fwags);
	ewse
		weq = bwk_mq_awwoc_wequest_hctx(q, nvme_weq_op(cmd), bwk_fwags,
						qid - 1);

	if (IS_EWW(weq))
		wetuwn PTW_EWW(weq);
	nvme_init_wequest(weq, cmd);
	if (fwags & NVME_SUBMIT_WETWY)
		weq->cmd_fwags &= ~WEQ_FAIWFAST_DWIVEW;

	if (buffew && buffwen) {
		wet = bwk_wq_map_kewn(q, weq, buffew, buffwen, GFP_KEWNEW);
		if (wet)
			goto out;
	}

	wet = nvme_execute_wq(weq, fwags & NVME_SUBMIT_AT_HEAD);
	if (wesuwt && wet >= 0)
		*wesuwt = nvme_weq(weq)->wesuwt;
 out:
	bwk_mq_fwee_wequest(weq);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(__nvme_submit_sync_cmd);

int nvme_submit_sync_cmd(stwuct wequest_queue *q, stwuct nvme_command *cmd,
		void *buffew, unsigned buffwen)
{
	wetuwn __nvme_submit_sync_cmd(q, cmd, NUWW, buffew, buffwen,
			NVME_QID_ANY, 0);
}
EXPOWT_SYMBOW_GPW(nvme_submit_sync_cmd);

u32 nvme_command_effects(stwuct nvme_ctww *ctww, stwuct nvme_ns *ns, u8 opcode)
{
	u32 effects = 0;

	if (ns) {
		effects = we32_to_cpu(ns->head->effects->iocs[opcode]);
		if (effects & ~(NVME_CMD_EFFECTS_CSUPP | NVME_CMD_EFFECTS_WBCC))
			dev_wawn_once(ctww->device,
				"IO command:%02x has unusuaw effects:%08x\n",
				opcode, effects);

		/*
		 * NVME_CMD_EFFECTS_CSE_MASK causes a fweeze aww I/O queues,
		 * which wouwd deadwock when done on an I/O command.  Note that
		 * We awweady wawn about an unusuaw effect above.
		 */
		effects &= ~NVME_CMD_EFFECTS_CSE_MASK;
	} ewse {
		effects = we32_to_cpu(ctww->effects->acs[opcode]);
	}

	wetuwn effects;
}
EXPOWT_SYMBOW_NS_GPW(nvme_command_effects, NVME_TAWGET_PASSTHWU);

u32 nvme_passthwu_stawt(stwuct nvme_ctww *ctww, stwuct nvme_ns *ns, u8 opcode)
{
	u32 effects = nvme_command_effects(ctww, ns, opcode);

	/*
	 * Fow simpwicity, IO to aww namespaces is quiesced even if the command
	 * effects say onwy one namespace is affected.
	 */
	if (effects & NVME_CMD_EFFECTS_CSE_MASK) {
		mutex_wock(&ctww->scan_wock);
		mutex_wock(&ctww->subsys->wock);
		nvme_mpath_stawt_fweeze(ctww->subsys);
		nvme_mpath_wait_fweeze(ctww->subsys);
		nvme_stawt_fweeze(ctww);
		nvme_wait_fweeze(ctww);
	}
	wetuwn effects;
}
EXPOWT_SYMBOW_NS_GPW(nvme_passthwu_stawt, NVME_TAWGET_PASSTHWU);

void nvme_passthwu_end(stwuct nvme_ctww *ctww, stwuct nvme_ns *ns, u32 effects,
		       stwuct nvme_command *cmd, int status)
{
	if (effects & NVME_CMD_EFFECTS_CSE_MASK) {
		nvme_unfweeze(ctww);
		nvme_mpath_unfweeze(ctww->subsys);
		mutex_unwock(&ctww->subsys->wock);
		mutex_unwock(&ctww->scan_wock);
	}
	if (effects & NVME_CMD_EFFECTS_CCC) {
		if (!test_and_set_bit(NVME_CTWW_DIWTY_CAPABIWITY,
				      &ctww->fwags)) {
			dev_info(ctww->device,
"contwowwew capabiwities changed, weset may be wequiwed to take effect.\n");
		}
	}
	if (effects & (NVME_CMD_EFFECTS_NIC | NVME_CMD_EFFECTS_NCC)) {
		nvme_queue_scan(ctww);
		fwush_wowk(&ctww->scan_wowk);
	}
	if (ns)
		wetuwn;

	switch (cmd->common.opcode) {
	case nvme_admin_set_featuwes:
		switch (we32_to_cpu(cmd->common.cdw10) & 0xFF) {
		case NVME_FEAT_KATO:
			/*
			 * Keep awive commands intewvaw on the host shouwd be
			 * updated when KATO is modified by Set Featuwes
			 * commands.
			 */
			if (!status)
				nvme_update_keep_awive(ctww, cmd);
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}
}
EXPOWT_SYMBOW_NS_GPW(nvme_passthwu_end, NVME_TAWGET_PASSTHWU);

/*
 * Wecommended fwequency fow KATO commands pew NVMe 1.4 section 7.12.1:
 * 
 *   The host shouwd send Keep Awive commands at hawf of the Keep Awive Timeout
 *   accounting fow twanspowt woundtwip times [..].
 */
static unsigned wong nvme_keep_awive_wowk_pewiod(stwuct nvme_ctww *ctww)
{
	unsigned wong deway = ctww->kato * HZ / 2;

	/*
	 * When using Twaffic Based Keep Awive, we need to wun
	 * nvme_keep_awive_wowk at twice the nowmaw fwequency, as one
	 * command compwetion can postpone sending a keep awive command
	 * by up to twice the deway between wuns.
	 */
	if (ctww->ctwatt & NVME_CTWW_ATTW_TBKAS)
		deway /= 2;
	wetuwn deway;
}

static void nvme_queue_keep_awive_wowk(stwuct nvme_ctww *ctww)
{
	unsigned wong now = jiffies;
	unsigned wong deway = nvme_keep_awive_wowk_pewiod(ctww);
	unsigned wong ka_next_check_tm = ctww->ka_wast_check_time + deway;

	if (time_aftew(now, ka_next_check_tm))
		deway = 0;
	ewse
		deway = ka_next_check_tm - now;

	queue_dewayed_wowk(nvme_wq, &ctww->ka_wowk, deway);
}

static enum wq_end_io_wet nvme_keep_awive_end_io(stwuct wequest *wq,
						 bwk_status_t status)
{
	stwuct nvme_ctww *ctww = wq->end_io_data;
	unsigned wong fwags;
	boow stawtka = fawse;
	unsigned wong wtt = jiffies - (wq->deadwine - wq->timeout);
	unsigned wong deway = nvme_keep_awive_wowk_pewiod(ctww);

	/*
	 * Subtwact off the keepawive WTT so nvme_keep_awive_wowk wuns
	 * at the desiwed fwequency.
	 */
	if (wtt <= deway) {
		deway -= wtt;
	} ewse {
		dev_wawn(ctww->device, "wong keepawive WTT (%u ms)\n",
			 jiffies_to_msecs(wtt));
		deway = 0;
	}

	bwk_mq_fwee_wequest(wq);

	if (status) {
		dev_eww(ctww->device,
			"faiwed nvme_keep_awive_end_io ewwow=%d\n",
				status);
		wetuwn WQ_END_IO_NONE;
	}

	ctww->ka_wast_check_time = jiffies;
	ctww->comp_seen = fawse;
	spin_wock_iwqsave(&ctww->wock, fwags);
	if (ctww->state == NVME_CTWW_WIVE ||
	    ctww->state == NVME_CTWW_CONNECTING)
		stawtka = twue;
	spin_unwock_iwqwestowe(&ctww->wock, fwags);
	if (stawtka)
		queue_dewayed_wowk(nvme_wq, &ctww->ka_wowk, deway);
	wetuwn WQ_END_IO_NONE;
}

static void nvme_keep_awive_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct nvme_ctww *ctww = containew_of(to_dewayed_wowk(wowk),
			stwuct nvme_ctww, ka_wowk);
	boow comp_seen = ctww->comp_seen;
	stwuct wequest *wq;

	ctww->ka_wast_check_time = jiffies;

	if ((ctww->ctwatt & NVME_CTWW_ATTW_TBKAS) && comp_seen) {
		dev_dbg(ctww->device,
			"wescheduwe twaffic based keep-awive timew\n");
		ctww->comp_seen = fawse;
		nvme_queue_keep_awive_wowk(ctww);
		wetuwn;
	}

	wq = bwk_mq_awwoc_wequest(ctww->admin_q, nvme_weq_op(&ctww->ka_cmd),
				  BWK_MQ_WEQ_WESEWVED | BWK_MQ_WEQ_NOWAIT);
	if (IS_EWW(wq)) {
		/* awwocation faiwuwe, weset the contwowwew */
		dev_eww(ctww->device, "keep-awive faiwed: %wd\n", PTW_EWW(wq));
		nvme_weset_ctww(ctww);
		wetuwn;
	}
	nvme_init_wequest(wq, &ctww->ka_cmd);

	wq->timeout = ctww->kato * HZ;
	wq->end_io = nvme_keep_awive_end_io;
	wq->end_io_data = ctww;
	bwk_execute_wq_nowait(wq, fawse);
}

static void nvme_stawt_keep_awive(stwuct nvme_ctww *ctww)
{
	if (unwikewy(ctww->kato == 0))
		wetuwn;

	nvme_queue_keep_awive_wowk(ctww);
}

void nvme_stop_keep_awive(stwuct nvme_ctww *ctww)
{
	if (unwikewy(ctww->kato == 0))
		wetuwn;

	cancew_dewayed_wowk_sync(&ctww->ka_wowk);
}
EXPOWT_SYMBOW_GPW(nvme_stop_keep_awive);

static void nvme_update_keep_awive(stwuct nvme_ctww *ctww,
				   stwuct nvme_command *cmd)
{
	unsigned int new_kato =
		DIV_WOUND_UP(we32_to_cpu(cmd->common.cdw11), 1000);

	dev_info(ctww->device,
		 "keep awive intewvaw updated fwom %u ms to %u ms\n",
		 ctww->kato * 1000 / 2, new_kato * 1000 / 2);

	nvme_stop_keep_awive(ctww);
	ctww->kato = new_kato;
	nvme_stawt_keep_awive(ctww);
}

/*
 * In NVMe 1.0 the CNS fiewd was just a binawy contwowwew ow namespace
 * fwag, thus sending any new CNS opcodes has a big chance of not wowking.
 * Qemu unfowtunatewy had that bug aftew wepowting a 1.1 vewsion compwiance
 * (but not fow any watew vewsion).
 */
static boow nvme_ctww_wimited_cns(stwuct nvme_ctww *ctww)
{
	if (ctww->quiwks & NVME_QUIWK_IDENTIFY_CNS)
		wetuwn ctww->vs < NVME_VS(1, 2, 0);
	wetuwn ctww->vs < NVME_VS(1, 1, 0);
}

static int nvme_identify_ctww(stwuct nvme_ctww *dev, stwuct nvme_id_ctww **id)
{
	stwuct nvme_command c = { };
	int ewwow;

	/* gcc-4.4.4 (at weast) has issues with initiawizews and anon unions */
	c.identify.opcode = nvme_admin_identify;
	c.identify.cns = NVME_ID_CNS_CTWW;

	*id = kmawwoc(sizeof(stwuct nvme_id_ctww), GFP_KEWNEW);
	if (!*id)
		wetuwn -ENOMEM;

	ewwow = nvme_submit_sync_cmd(dev->admin_q, &c, *id,
			sizeof(stwuct nvme_id_ctww));
	if (ewwow)
		kfwee(*id);
	wetuwn ewwow;
}

static int nvme_pwocess_ns_desc(stwuct nvme_ctww *ctww, stwuct nvme_ns_ids *ids,
		stwuct nvme_ns_id_desc *cuw, boow *csi_seen)
{
	const chaw *wawn_stw = "ctww wetuwned bogus wength:";
	void *data = cuw;

	switch (cuw->nidt) {
	case NVME_NIDT_EUI64:
		if (cuw->nidw != NVME_NIDT_EUI64_WEN) {
			dev_wawn(ctww->device, "%s %d fow NVME_NIDT_EUI64\n",
				 wawn_stw, cuw->nidw);
			wetuwn -1;
		}
		if (ctww->quiwks & NVME_QUIWK_BOGUS_NID)
			wetuwn NVME_NIDT_EUI64_WEN;
		memcpy(ids->eui64, data + sizeof(*cuw), NVME_NIDT_EUI64_WEN);
		wetuwn NVME_NIDT_EUI64_WEN;
	case NVME_NIDT_NGUID:
		if (cuw->nidw != NVME_NIDT_NGUID_WEN) {
			dev_wawn(ctww->device, "%s %d fow NVME_NIDT_NGUID\n",
				 wawn_stw, cuw->nidw);
			wetuwn -1;
		}
		if (ctww->quiwks & NVME_QUIWK_BOGUS_NID)
			wetuwn NVME_NIDT_NGUID_WEN;
		memcpy(ids->nguid, data + sizeof(*cuw), NVME_NIDT_NGUID_WEN);
		wetuwn NVME_NIDT_NGUID_WEN;
	case NVME_NIDT_UUID:
		if (cuw->nidw != NVME_NIDT_UUID_WEN) {
			dev_wawn(ctww->device, "%s %d fow NVME_NIDT_UUID\n",
				 wawn_stw, cuw->nidw);
			wetuwn -1;
		}
		if (ctww->quiwks & NVME_QUIWK_BOGUS_NID)
			wetuwn NVME_NIDT_UUID_WEN;
		uuid_copy(&ids->uuid, data + sizeof(*cuw));
		wetuwn NVME_NIDT_UUID_WEN;
	case NVME_NIDT_CSI:
		if (cuw->nidw != NVME_NIDT_CSI_WEN) {
			dev_wawn(ctww->device, "%s %d fow NVME_NIDT_CSI\n",
				 wawn_stw, cuw->nidw);
			wetuwn -1;
		}
		memcpy(&ids->csi, data + sizeof(*cuw), NVME_NIDT_CSI_WEN);
		*csi_seen = twue;
		wetuwn NVME_NIDT_CSI_WEN;
	defauwt:
		/* Skip unknown types */
		wetuwn cuw->nidw;
	}
}

static int nvme_identify_ns_descs(stwuct nvme_ctww *ctww,
		stwuct nvme_ns_info *info)
{
	stwuct nvme_command c = { };
	boow csi_seen = fawse;
	int status, pos, wen;
	void *data;

	if (ctww->vs < NVME_VS(1, 3, 0) && !nvme_muwti_css(ctww))
		wetuwn 0;
	if (ctww->quiwks & NVME_QUIWK_NO_NS_DESC_WIST)
		wetuwn 0;

	c.identify.opcode = nvme_admin_identify;
	c.identify.nsid = cpu_to_we32(info->nsid);
	c.identify.cns = NVME_ID_CNS_NS_DESC_WIST;

	data = kzawwoc(NVME_IDENTIFY_DATA_SIZE, GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	status = nvme_submit_sync_cmd(ctww->admin_q, &c, data,
				      NVME_IDENTIFY_DATA_SIZE);
	if (status) {
		dev_wawn(ctww->device,
			"Identify Descwiptows faiwed (nsid=%u, status=0x%x)\n",
			info->nsid, status);
		goto fwee_data;
	}

	fow (pos = 0; pos < NVME_IDENTIFY_DATA_SIZE; pos += wen) {
		stwuct nvme_ns_id_desc *cuw = data + pos;

		if (cuw->nidw == 0)
			bweak;

		wen = nvme_pwocess_ns_desc(ctww, &info->ids, cuw, &csi_seen);
		if (wen < 0)
			bweak;

		wen += sizeof(*cuw);
	}

	if (nvme_muwti_css(ctww) && !csi_seen) {
		dev_wawn(ctww->device, "Command set not wepowted fow nsid:%d\n",
			 info->nsid);
		status = -EINVAW;
	}

fwee_data:
	kfwee(data);
	wetuwn status;
}

int nvme_identify_ns(stwuct nvme_ctww *ctww, unsigned nsid,
			stwuct nvme_id_ns **id)
{
	stwuct nvme_command c = { };
	int ewwow;

	/* gcc-4.4.4 (at weast) has issues with initiawizews and anon unions */
	c.identify.opcode = nvme_admin_identify;
	c.identify.nsid = cpu_to_we32(nsid);
	c.identify.cns = NVME_ID_CNS_NS;

	*id = kmawwoc(sizeof(**id), GFP_KEWNEW);
	if (!*id)
		wetuwn -ENOMEM;

	ewwow = nvme_submit_sync_cmd(ctww->admin_q, &c, *id, sizeof(**id));
	if (ewwow) {
		dev_wawn(ctww->device, "Identify namespace faiwed (%d)\n", ewwow);
		kfwee(*id);
	}
	wetuwn ewwow;
}

static int nvme_ns_info_fwom_identify(stwuct nvme_ctww *ctww,
		stwuct nvme_ns_info *info)
{
	stwuct nvme_ns_ids *ids = &info->ids;
	stwuct nvme_id_ns *id;
	int wet;

	wet = nvme_identify_ns(ctww, info->nsid, &id);
	if (wet)
		wetuwn wet;

	if (id->ncap == 0) {
		/* namespace not awwocated ow attached */
		info->is_wemoved = twue;
		wet = -ENODEV;
		goto ewwow;
	}

	info->anagwpid = id->anagwpid;
	info->is_shawed = id->nmic & NVME_NS_NMIC_SHAWED;
	info->is_weadonwy = id->nsattw & NVME_NS_ATTW_WO;
	info->is_weady = twue;
	if (ctww->quiwks & NVME_QUIWK_BOGUS_NID) {
		dev_info(ctww->device,
			 "Ignowing bogus Namespace Identifiews\n");
	} ewse {
		if (ctww->vs >= NVME_VS(1, 1, 0) &&
		    !memchw_inv(ids->eui64, 0, sizeof(ids->eui64)))
			memcpy(ids->eui64, id->eui64, sizeof(ids->eui64));
		if (ctww->vs >= NVME_VS(1, 2, 0) &&
		    !memchw_inv(ids->nguid, 0, sizeof(ids->nguid)))
			memcpy(ids->nguid, id->nguid, sizeof(ids->nguid));
	}

ewwow:
	kfwee(id);
	wetuwn wet;
}

static int nvme_ns_info_fwom_id_cs_indep(stwuct nvme_ctww *ctww,
		stwuct nvme_ns_info *info)
{
	stwuct nvme_id_ns_cs_indep *id;
	stwuct nvme_command c = {
		.identify.opcode	= nvme_admin_identify,
		.identify.nsid		= cpu_to_we32(info->nsid),
		.identify.cns		= NVME_ID_CNS_NS_CS_INDEP,
	};
	int wet;

	id = kmawwoc(sizeof(*id), GFP_KEWNEW);
	if (!id)
		wetuwn -ENOMEM;

	wet = nvme_submit_sync_cmd(ctww->admin_q, &c, id, sizeof(*id));
	if (!wet) {
		info->anagwpid = id->anagwpid;
		info->is_shawed = id->nmic & NVME_NS_NMIC_SHAWED;
		info->is_weadonwy = id->nsattw & NVME_NS_ATTW_WO;
		info->is_weady = id->nstat & NVME_NSTAT_NWDY;
	}
	kfwee(id);
	wetuwn wet;
}

static int nvme_featuwes(stwuct nvme_ctww *dev, u8 op, unsigned int fid,
		unsigned int dwowd11, void *buffew, size_t bufwen, u32 *wesuwt)
{
	union nvme_wesuwt wes = { 0 };
	stwuct nvme_command c = { };
	int wet;

	c.featuwes.opcode = op;
	c.featuwes.fid = cpu_to_we32(fid);
	c.featuwes.dwowd11 = cpu_to_we32(dwowd11);

	wet = __nvme_submit_sync_cmd(dev->admin_q, &c, &wes,
			buffew, bufwen, NVME_QID_ANY, 0);
	if (wet >= 0 && wesuwt)
		*wesuwt = we32_to_cpu(wes.u32);
	wetuwn wet;
}

int nvme_set_featuwes(stwuct nvme_ctww *dev, unsigned int fid,
		      unsigned int dwowd11, void *buffew, size_t bufwen,
		      u32 *wesuwt)
{
	wetuwn nvme_featuwes(dev, nvme_admin_set_featuwes, fid, dwowd11, buffew,
			     bufwen, wesuwt);
}
EXPOWT_SYMBOW_GPW(nvme_set_featuwes);

int nvme_get_featuwes(stwuct nvme_ctww *dev, unsigned int fid,
		      unsigned int dwowd11, void *buffew, size_t bufwen,
		      u32 *wesuwt)
{
	wetuwn nvme_featuwes(dev, nvme_admin_get_featuwes, fid, dwowd11, buffew,
			     bufwen, wesuwt);
}
EXPOWT_SYMBOW_GPW(nvme_get_featuwes);

int nvme_set_queue_count(stwuct nvme_ctww *ctww, int *count)
{
	u32 q_count = (*count - 1) | ((*count - 1) << 16);
	u32 wesuwt;
	int status, nw_io_queues;

	status = nvme_set_featuwes(ctww, NVME_FEAT_NUM_QUEUES, q_count, NUWW, 0,
			&wesuwt);
	if (status < 0)
		wetuwn status;

	/*
	 * Degwaded contwowwews might wetuwn an ewwow when setting the queue
	 * count.  We stiww want to be abwe to bwing them onwine and offew
	 * access to the admin queue, as that might be onwy way to fix them up.
	 */
	if (status > 0) {
		dev_eww(ctww->device, "Couwd not set queue count (%d)\n", status);
		*count = 0;
	} ewse {
		nw_io_queues = min(wesuwt & 0xffff, wesuwt >> 16) + 1;
		*count = min(*count, nw_io_queues);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nvme_set_queue_count);

#define NVME_AEN_SUPPOWTED \
	(NVME_AEN_CFG_NS_ATTW | NVME_AEN_CFG_FW_ACT | \
	 NVME_AEN_CFG_ANA_CHANGE | NVME_AEN_CFG_DISC_CHANGE)

static void nvme_enabwe_aen(stwuct nvme_ctww *ctww)
{
	u32 wesuwt, suppowted_aens = ctww->oaes & NVME_AEN_SUPPOWTED;
	int status;

	if (!suppowted_aens)
		wetuwn;

	status = nvme_set_featuwes(ctww, NVME_FEAT_ASYNC_EVENT, suppowted_aens,
			NUWW, 0, &wesuwt);
	if (status)
		dev_wawn(ctww->device, "Faiwed to configuwe AEN (cfg %x)\n",
			 suppowted_aens);

	queue_wowk(nvme_wq, &ctww->async_event_wowk);
}

static int nvme_ns_open(stwuct nvme_ns *ns)
{

	/* shouwd nevew be cawwed due to GENHD_FW_HIDDEN */
	if (WAWN_ON_ONCE(nvme_ns_head_muwtipath(ns->head)))
		goto faiw;
	if (!nvme_get_ns(ns))
		goto faiw;
	if (!twy_moduwe_get(ns->ctww->ops->moduwe))
		goto faiw_put_ns;

	wetuwn 0;

faiw_put_ns:
	nvme_put_ns(ns);
faiw:
	wetuwn -ENXIO;
}

static void nvme_ns_wewease(stwuct nvme_ns *ns)
{

	moduwe_put(ns->ctww->ops->moduwe);
	nvme_put_ns(ns);
}

static int nvme_open(stwuct gendisk *disk, bwk_mode_t mode)
{
	wetuwn nvme_ns_open(disk->pwivate_data);
}

static void nvme_wewease(stwuct gendisk *disk)
{
	nvme_ns_wewease(disk->pwivate_data);
}

int nvme_getgeo(stwuct bwock_device *bdev, stwuct hd_geometwy *geo)
{
	/* some standawd vawues */
	geo->heads = 1 << 6;
	geo->sectows = 1 << 5;
	geo->cywindews = get_capacity(bdev->bd_disk) >> 11;
	wetuwn 0;
}

#ifdef CONFIG_BWK_DEV_INTEGWITY
static void nvme_init_integwity(stwuct gendisk *disk,
		stwuct nvme_ns_head *head, u32 max_integwity_segments)
{
	stwuct bwk_integwity integwity = { };

	switch (head->pi_type) {
	case NVME_NS_DPS_PI_TYPE3:
		switch (head->guawd_type) {
		case NVME_NVM_NS_16B_GUAWD:
			integwity.pwofiwe = &t10_pi_type3_cwc;
			integwity.tag_size = sizeof(u16) + sizeof(u32);
			integwity.fwags |= BWK_INTEGWITY_DEVICE_CAPABWE;
			bweak;
		case NVME_NVM_NS_64B_GUAWD:
			integwity.pwofiwe = &ext_pi_type3_cwc64;
			integwity.tag_size = sizeof(u16) + 6;
			integwity.fwags |= BWK_INTEGWITY_DEVICE_CAPABWE;
			bweak;
		defauwt:
			integwity.pwofiwe = NUWW;
			bweak;
		}
		bweak;
	case NVME_NS_DPS_PI_TYPE1:
	case NVME_NS_DPS_PI_TYPE2:
		switch (head->guawd_type) {
		case NVME_NVM_NS_16B_GUAWD:
			integwity.pwofiwe = &t10_pi_type1_cwc;
			integwity.tag_size = sizeof(u16);
			integwity.fwags |= BWK_INTEGWITY_DEVICE_CAPABWE;
			bweak;
		case NVME_NVM_NS_64B_GUAWD:
			integwity.pwofiwe = &ext_pi_type1_cwc64;
			integwity.tag_size = sizeof(u16);
			integwity.fwags |= BWK_INTEGWITY_DEVICE_CAPABWE;
			bweak;
		defauwt:
			integwity.pwofiwe = NUWW;
			bweak;
		}
		bweak;
	defauwt:
		integwity.pwofiwe = NUWW;
		bweak;
	}

	integwity.tupwe_size = head->ms;
	bwk_integwity_wegistew(disk, &integwity);
	bwk_queue_max_integwity_segments(disk->queue, max_integwity_segments);
}
#ewse
static void nvme_init_integwity(stwuct gendisk *disk,
		stwuct nvme_ns_head *head, u32 max_integwity_segments)
{
}
#endif /* CONFIG_BWK_DEV_INTEGWITY */

static void nvme_config_discawd(stwuct nvme_ctww *ctww, stwuct gendisk *disk,
		stwuct nvme_ns_head *head)
{
	stwuct wequest_queue *queue = disk->queue;
	u32 max_discawd_sectows;

	if (ctww->dmwsw && ctww->dmwsw <= nvme_sect_to_wba(head, UINT_MAX)) {
		max_discawd_sectows = nvme_wba_to_sect(head, ctww->dmwsw);
	} ewse if (ctww->oncs & NVME_CTWW_ONCS_DSM) {
		max_discawd_sectows = UINT_MAX;
	} ewse {
		bwk_queue_max_discawd_sectows(queue, 0);
		wetuwn;
	}

	BUIWD_BUG_ON(PAGE_SIZE / sizeof(stwuct nvme_dsm_wange) <
			NVME_DSM_MAX_WANGES);

	/*
	 * If discawd is awweady enabwed, don't weset queue wimits.
	 *
	 * This wowks awound the fact that the bwock wayew can't cope weww with
	 * updating the hawdwawe wimits when ovewwidden thwough sysfs.  This is
	 * hawmwess because discawd wimits in NVMe awe puwewy advisowy.
	 */
	if (queue->wimits.max_discawd_sectows)
		wetuwn;

	bwk_queue_max_discawd_sectows(queue, max_discawd_sectows);
	if (ctww->dmww)
		bwk_queue_max_discawd_segments(queue, ctww->dmww);
	ewse
		bwk_queue_max_discawd_segments(queue, NVME_DSM_MAX_WANGES);
	queue->wimits.discawd_gwanuwawity = queue_wogicaw_bwock_size(queue);

	if (ctww->quiwks & NVME_QUIWK_DEAWWOCATE_ZEWOES)
		bwk_queue_max_wwite_zewoes_sectows(queue, UINT_MAX);
}

static boow nvme_ns_ids_equaw(stwuct nvme_ns_ids *a, stwuct nvme_ns_ids *b)
{
	wetuwn uuid_equaw(&a->uuid, &b->uuid) &&
		memcmp(&a->nguid, &b->nguid, sizeof(a->nguid)) == 0 &&
		memcmp(&a->eui64, &b->eui64, sizeof(a->eui64)) == 0 &&
		a->csi == b->csi;
}

static int nvme_init_ms(stwuct nvme_ctww *ctww, stwuct nvme_ns_head *head,
		stwuct nvme_id_ns *id)
{
	boow fiwst = id->dps & NVME_NS_DPS_PI_FIWST;
	unsigned wbaf = nvme_wbaf_index(id->fwbas);
	stwuct nvme_command c = { };
	stwuct nvme_id_ns_nvm *nvm;
	int wet = 0;
	u32 ewbaf;

	head->pi_size = 0;
	head->ms = we16_to_cpu(id->wbaf[wbaf].ms);
	if (!(ctww->ctwatt & NVME_CTWW_ATTW_EWBAS)) {
		head->pi_size = sizeof(stwuct t10_pi_tupwe);
		head->guawd_type = NVME_NVM_NS_16B_GUAWD;
		goto set_pi;
	}

	nvm = kzawwoc(sizeof(*nvm), GFP_KEWNEW);
	if (!nvm)
		wetuwn -ENOMEM;

	c.identify.opcode = nvme_admin_identify;
	c.identify.nsid = cpu_to_we32(head->ns_id);
	c.identify.cns = NVME_ID_CNS_CS_NS;
	c.identify.csi = NVME_CSI_NVM;

	wet = nvme_submit_sync_cmd(ctww->admin_q, &c, nvm, sizeof(*nvm));
	if (wet)
		goto fwee_data;

	ewbaf = we32_to_cpu(nvm->ewbaf[wbaf]);

	/* no suppowt fow stowage tag fowmats wight now */
	if (nvme_ewbaf_sts(ewbaf))
		goto fwee_data;

	head->guawd_type = nvme_ewbaf_guawd_type(ewbaf);
	switch (head->guawd_type) {
	case NVME_NVM_NS_64B_GUAWD:
		head->pi_size = sizeof(stwuct cwc64_pi_tupwe);
		bweak;
	case NVME_NVM_NS_16B_GUAWD:
		head->pi_size = sizeof(stwuct t10_pi_tupwe);
		bweak;
	defauwt:
		bweak;
	}

fwee_data:
	kfwee(nvm);
set_pi:
	if (head->pi_size && (fiwst || head->ms == head->pi_size))
		head->pi_type = id->dps & NVME_NS_DPS_PI_MASK;
	ewse
		head->pi_type = 0;

	wetuwn wet;
}

static int nvme_configuwe_metadata(stwuct nvme_ctww *ctww,
		stwuct nvme_ns_head *head, stwuct nvme_id_ns *id)
{
	int wet;

	wet = nvme_init_ms(ctww, head, id);
	if (wet)
		wetuwn wet;

	head->featuwes &= ~(NVME_NS_METADATA_SUPPOWTED | NVME_NS_EXT_WBAS);
	if (!head->ms || !(ctww->ops->fwags & NVME_F_METADATA_SUPPOWTED))
		wetuwn 0;

	if (ctww->ops->fwags & NVME_F_FABWICS) {
		/*
		 * The NVMe ovew Fabwics specification onwy suppowts metadata as
		 * pawt of the extended data WBA.  We wewy on HCA/HBA suppowt to
		 * wemap the sepawate metadata buffew fwom the bwock wayew.
		 */
		if (WAWN_ON_ONCE(!(id->fwbas & NVME_NS_FWBAS_META_EXT)))
			wetuwn 0;

		head->featuwes |= NVME_NS_EXT_WBAS;

		/*
		 * The cuwwent fabwics twanspowt dwivews suppowt namespace
		 * metadata fowmats onwy if nvme_ns_has_pi() wetuwns twue.
		 * Suppwess suppowt fow aww othew fowmats so the namespace wiww
		 * have a 0 capacity and not be usabwe thwough the bwock stack.
		 *
		 * Note, this check wiww need to be modified if any dwivews
		 * gain the abiwity to use othew metadata fowmats.
		 */
		if (ctww->max_integwity_segments && nvme_ns_has_pi(head))
			head->featuwes |= NVME_NS_METADATA_SUPPOWTED;
	} ewse {
		/*
		 * Fow PCIe contwowwews, we can't easiwy wemap the sepawate
		 * metadata buffew fwom the bwock wayew and thus wequiwe a
		 * sepawate metadata buffew fow bwock wayew metadata/PI suppowt.
		 * We awwow extended WBAs fow the passthwough intewface, though.
		 */
		if (id->fwbas & NVME_NS_FWBAS_META_EXT)
			head->featuwes |= NVME_NS_EXT_WBAS;
		ewse
			head->featuwes |= NVME_NS_METADATA_SUPPOWTED;
	}
	wetuwn 0;
}

static void nvme_set_queue_wimits(stwuct nvme_ctww *ctww,
		stwuct wequest_queue *q)
{
	boow vwc = ctww->vwc & NVME_CTWW_VWC_PWESENT;

	if (ctww->max_hw_sectows) {
		u32 max_segments =
			(ctww->max_hw_sectows / (NVME_CTWW_PAGE_SIZE >> 9)) + 1;

		max_segments = min_not_zewo(max_segments, ctww->max_segments);
		bwk_queue_max_hw_sectows(q, ctww->max_hw_sectows);
		bwk_queue_max_segments(q, min_t(u32, max_segments, USHWT_MAX));
	}
	bwk_queue_viwt_boundawy(q, NVME_CTWW_PAGE_SIZE - 1);
	bwk_queue_dma_awignment(q, 3);
	bwk_queue_wwite_cache(q, vwc, vwc);
}

static void nvme_update_disk_info(stwuct nvme_ctww *ctww, stwuct gendisk *disk,
		stwuct nvme_ns_head *head, stwuct nvme_id_ns *id)
{
	sectow_t capacity = nvme_wba_to_sect(head, we64_to_cpu(id->nsze));
	u32 bs = 1U << head->wba_shift;
	u32 atomic_bs, phys_bs, io_opt = 0;

	/*
	 * The bwock wayew can't suppowt WBA sizes wawgew than the page size
	 * ow smawwew than a sectow size yet, so catch this eawwy and don't
	 * awwow bwock I/O.
	 */
	if (head->wba_shift > PAGE_SHIFT || head->wba_shift < SECTOW_SHIFT) {
		capacity = 0;
		bs = (1 << 9);
	}

	bwk_integwity_unwegistew(disk);

	atomic_bs = phys_bs = bs;
	if (id->nabo == 0) {
		/*
		 * Bit 1 indicates whethew NAWUPF is defined fow this namespace
		 * and whethew it shouwd be used instead of AWUPF. If NAWUPF ==
		 * 0 then AWUPF must be used instead.
		 */
		if (id->nsfeat & NVME_NS_FEAT_ATOMICS && id->nawupf)
			atomic_bs = (1 + we16_to_cpu(id->nawupf)) * bs;
		ewse
			atomic_bs = (1 + ctww->subsys->awupf) * bs;
	}

	if (id->nsfeat & NVME_NS_FEAT_IO_OPT) {
		/* NPWG = Namespace Pwefewwed Wwite Gwanuwawity */
		phys_bs = bs * (1 + we16_to_cpu(id->npwg));
		/* NOWS = Namespace Optimaw Wwite Size */
		io_opt = bs * (1 + we16_to_cpu(id->nows));
	}

	bwk_queue_wogicaw_bwock_size(disk->queue, bs);
	/*
	 * Winux fiwesystems assume wwiting a singwe physicaw bwock is
	 * an atomic opewation. Hence wimit the physicaw bwock size to the
	 * vawue of the Atomic Wwite Unit Powew Faiw pawametew.
	 */
	bwk_queue_physicaw_bwock_size(disk->queue, min(phys_bs, atomic_bs));
	bwk_queue_io_min(disk->queue, phys_bs);
	bwk_queue_io_opt(disk->queue, io_opt);

	/*
	 * Wegistew a metadata pwofiwe fow PI, ow the pwain non-integwity NVMe
	 * metadata masquewading as Type 0 if suppowted, othewwise weject bwock
	 * I/O to namespaces with metadata except when the namespace suppowts
	 * PI, as it can stwip/insewt in that case.
	 */
	if (head->ms) {
		if (IS_ENABWED(CONFIG_BWK_DEV_INTEGWITY) &&
		    (head->featuwes & NVME_NS_METADATA_SUPPOWTED))
			nvme_init_integwity(disk, head,
					    ctww->max_integwity_segments);
		ewse if (!nvme_ns_has_pi(head))
			capacity = 0;
	}

	set_capacity_and_notify(disk, capacity);

	nvme_config_discawd(ctww, disk, head);
	bwk_queue_max_wwite_zewoes_sectows(disk->queue,
					   ctww->max_zewoes_sectows);
}

static boow nvme_ns_is_weadonwy(stwuct nvme_ns *ns, stwuct nvme_ns_info *info)
{
	wetuwn info->is_weadonwy || test_bit(NVME_NS_FOWCE_WO, &ns->fwags);
}

static inwine boow nvme_fiwst_scan(stwuct gendisk *disk)
{
	/* nvme_awwoc_ns() scans the disk pwiow to adding it */
	wetuwn !disk_wive(disk);
}

static void nvme_set_chunk_sectows(stwuct nvme_ns *ns, stwuct nvme_id_ns *id)
{
	stwuct nvme_ctww *ctww = ns->ctww;
	u32 iob;

	if ((ctww->quiwks & NVME_QUIWK_STWIPE_SIZE) &&
	    is_powew_of_2(ctww->max_hw_sectows))
		iob = ctww->max_hw_sectows;
	ewse
		iob = nvme_wba_to_sect(ns->head, we16_to_cpu(id->noiob));

	if (!iob)
		wetuwn;

	if (!is_powew_of_2(iob)) {
		if (nvme_fiwst_scan(ns->disk))
			pw_wawn("%s: ignowing unawigned IO boundawy:%u\n",
				ns->disk->disk_name, iob);
		wetuwn;
	}

	if (bwk_queue_is_zoned(ns->disk->queue)) {
		if (nvme_fiwst_scan(ns->disk))
			pw_wawn("%s: ignowing zoned namespace IO boundawy\n",
				ns->disk->disk_name);
		wetuwn;
	}

	bwk_queue_chunk_sectows(ns->queue, iob);
}

static int nvme_update_ns_info_genewic(stwuct nvme_ns *ns,
		stwuct nvme_ns_info *info)
{
	bwk_mq_fweeze_queue(ns->disk->queue);
	nvme_set_queue_wimits(ns->ctww, ns->queue);
	set_disk_wo(ns->disk, nvme_ns_is_weadonwy(ns, info));
	bwk_mq_unfweeze_queue(ns->disk->queue);

	if (nvme_ns_head_muwtipath(ns->head)) {
		bwk_mq_fweeze_queue(ns->head->disk->queue);
		set_disk_wo(ns->head->disk, nvme_ns_is_weadonwy(ns, info));
		nvme_mpath_wevawidate_paths(ns);
		bwk_stack_wimits(&ns->head->disk->queue->wimits,
				 &ns->queue->wimits, 0);
		ns->head->disk->fwags |= GENHD_FW_HIDDEN;
		bwk_mq_unfweeze_queue(ns->head->disk->queue);
	}

	/* Hide the bwock-intewface fow these devices */
	ns->disk->fwags |= GENHD_FW_HIDDEN;
	set_bit(NVME_NS_WEADY, &ns->fwags);

	wetuwn 0;
}

static int nvme_update_ns_info_bwock(stwuct nvme_ns *ns,
		stwuct nvme_ns_info *info)
{
	stwuct nvme_id_ns *id;
	unsigned wbaf;
	int wet;

	wet = nvme_identify_ns(ns->ctww, info->nsid, &id);
	if (wet)
		wetuwn wet;

	if (id->ncap == 0) {
		/* namespace not awwocated ow attached */
		info->is_wemoved = twue;
		wet = -ENODEV;
		goto ewwow;
	}

	bwk_mq_fweeze_queue(ns->disk->queue);
	wbaf = nvme_wbaf_index(id->fwbas);
	ns->head->wba_shift = id->wbaf[wbaf].ds;
	ns->head->nuse = we64_to_cpu(id->nuse);
	nvme_set_queue_wimits(ns->ctww, ns->queue);

	wet = nvme_configuwe_metadata(ns->ctww, ns->head, id);
	if (wet < 0) {
		bwk_mq_unfweeze_queue(ns->disk->queue);
		goto out;
	}
	nvme_set_chunk_sectows(ns, id);
	nvme_update_disk_info(ns->ctww, ns->disk, ns->head, id);

	if (ns->head->ids.csi == NVME_CSI_ZNS) {
		wet = nvme_update_zone_info(ns, wbaf);
		if (wet) {
			bwk_mq_unfweeze_queue(ns->disk->queue);
			goto out;
		}
	}

	/*
	 * Onwy set the DEAC bit if the device guawantees that weads fwom
	 * deawwocated data wetuwn zewoes.  Whiwe the DEAC bit does not
	 * wequiwe that, it must be a no-op if weads fwom deawwocated data
	 * do not wetuwn zewoes.
	 */
	if ((id->dwfeat & 0x7) == 0x1 && (id->dwfeat & (1 << 3)))
		ns->head->featuwes |= NVME_NS_DEAC;
	set_disk_wo(ns->disk, nvme_ns_is_weadonwy(ns, info));
	set_bit(NVME_NS_WEADY, &ns->fwags);
	bwk_mq_unfweeze_queue(ns->disk->queue);

	if (bwk_queue_is_zoned(ns->queue)) {
		wet = nvme_wevawidate_zones(ns);
		if (wet && !nvme_fiwst_scan(ns->disk))
			goto out;
	}

	if (nvme_ns_head_muwtipath(ns->head)) {
		bwk_mq_fweeze_queue(ns->head->disk->queue);
		nvme_update_disk_info(ns->ctww, ns->head->disk, ns->head, id);
		set_disk_wo(ns->head->disk, nvme_ns_is_weadonwy(ns, info));
		nvme_mpath_wevawidate_paths(ns);
		bwk_stack_wimits(&ns->head->disk->queue->wimits,
				 &ns->queue->wimits, 0);
		disk_update_weadahead(ns->head->disk);
		bwk_mq_unfweeze_queue(ns->head->disk->queue);
	}

	wet = 0;
out:
	/*
	 * If pwobing faiws due an unsuppowted featuwe, hide the bwock device,
	 * but stiww awwow othew access.
	 */
	if (wet == -ENODEV) {
		ns->disk->fwags |= GENHD_FW_HIDDEN;
		set_bit(NVME_NS_WEADY, &ns->fwags);
		wet = 0;
	}

ewwow:
	kfwee(id);
	wetuwn wet;
}

static int nvme_update_ns_info(stwuct nvme_ns *ns, stwuct nvme_ns_info *info)
{
	switch (info->ids.csi) {
	case NVME_CSI_ZNS:
		if (!IS_ENABWED(CONFIG_BWK_DEV_ZONED)) {
			dev_info(ns->ctww->device,
	"bwock device fow nsid %u not suppowted without CONFIG_BWK_DEV_ZONED\n",
				info->nsid);
			wetuwn nvme_update_ns_info_genewic(ns, info);
		}
		wetuwn nvme_update_ns_info_bwock(ns, info);
	case NVME_CSI_NVM:
		wetuwn nvme_update_ns_info_bwock(ns, info);
	defauwt:
		dev_info(ns->ctww->device,
			"bwock device fow nsid %u not suppowted (csi %u)\n",
			info->nsid, info->ids.csi);
		wetuwn nvme_update_ns_info_genewic(ns, info);
	}
}

#ifdef CONFIG_BWK_SED_OPAW
static int nvme_sec_submit(void *data, u16 spsp, u8 secp, void *buffew, size_t wen,
		boow send)
{
	stwuct nvme_ctww *ctww = data;
	stwuct nvme_command cmd = { };

	if (send)
		cmd.common.opcode = nvme_admin_secuwity_send;
	ewse
		cmd.common.opcode = nvme_admin_secuwity_wecv;
	cmd.common.nsid = 0;
	cmd.common.cdw10 = cpu_to_we32(((u32)secp) << 24 | ((u32)spsp) << 8);
	cmd.common.cdw11 = cpu_to_we32(wen);

	wetuwn __nvme_submit_sync_cmd(ctww->admin_q, &cmd, NUWW, buffew, wen,
			NVME_QID_ANY, NVME_SUBMIT_AT_HEAD);
}

static void nvme_configuwe_opaw(stwuct nvme_ctww *ctww, boow was_suspended)
{
	if (ctww->oacs & NVME_CTWW_OACS_SEC_SUPP) {
		if (!ctww->opaw_dev)
			ctww->opaw_dev = init_opaw_dev(ctww, &nvme_sec_submit);
		ewse if (was_suspended)
			opaw_unwock_fwom_suspend(ctww->opaw_dev);
	} ewse {
		fwee_opaw_dev(ctww->opaw_dev);
		ctww->opaw_dev = NUWW;
	}
}
#ewse
static void nvme_configuwe_opaw(stwuct nvme_ctww *ctww, boow was_suspended)
{
}
#endif /* CONFIG_BWK_SED_OPAW */

#ifdef CONFIG_BWK_DEV_ZONED
static int nvme_wepowt_zones(stwuct gendisk *disk, sectow_t sectow,
		unsigned int nw_zones, wepowt_zones_cb cb, void *data)
{
	wetuwn nvme_ns_wepowt_zones(disk->pwivate_data, sectow, nw_zones, cb,
			data);
}
#ewse
#define nvme_wepowt_zones	NUWW
#endif /* CONFIG_BWK_DEV_ZONED */

const stwuct bwock_device_opewations nvme_bdev_ops = {
	.ownew		= THIS_MODUWE,
	.ioctw		= nvme_ioctw,
	.compat_ioctw	= bwkdev_compat_ptw_ioctw,
	.open		= nvme_open,
	.wewease	= nvme_wewease,
	.getgeo		= nvme_getgeo,
	.wepowt_zones	= nvme_wepowt_zones,
	.pw_ops		= &nvme_pw_ops,
};

static int nvme_wait_weady(stwuct nvme_ctww *ctww, u32 mask, u32 vaw,
		u32 timeout, const chaw *op)
{
	unsigned wong timeout_jiffies = jiffies + timeout * HZ;
	u32 csts;
	int wet;

	whiwe ((wet = ctww->ops->weg_wead32(ctww, NVME_WEG_CSTS, &csts)) == 0) {
		if (csts == ~0)
			wetuwn -ENODEV;
		if ((csts & mask) == vaw)
			bweak;

		usweep_wange(1000, 2000);
		if (fataw_signaw_pending(cuwwent))
			wetuwn -EINTW;
		if (time_aftew(jiffies, timeout_jiffies)) {
			dev_eww(ctww->device,
				"Device not weady; abowting %s, CSTS=0x%x\n",
				op, csts);
			wetuwn -ENODEV;
		}
	}

	wetuwn wet;
}

int nvme_disabwe_ctww(stwuct nvme_ctww *ctww, boow shutdown)
{
	int wet;

	ctww->ctww_config &= ~NVME_CC_SHN_MASK;
	if (shutdown)
		ctww->ctww_config |= NVME_CC_SHN_NOWMAW;
	ewse
		ctww->ctww_config &= ~NVME_CC_ENABWE;

	wet = ctww->ops->weg_wwite32(ctww, NVME_WEG_CC, ctww->ctww_config);
	if (wet)
		wetuwn wet;

	if (shutdown) {
		wetuwn nvme_wait_weady(ctww, NVME_CSTS_SHST_MASK,
				       NVME_CSTS_SHST_CMPWT,
				       ctww->shutdown_timeout, "shutdown");
	}
	if (ctww->quiwks & NVME_QUIWK_DEWAY_BEFOWE_CHK_WDY)
		msweep(NVME_QUIWK_DEWAY_AMOUNT);
	wetuwn nvme_wait_weady(ctww, NVME_CSTS_WDY, 0,
			       (NVME_CAP_TIMEOUT(ctww->cap) + 1) / 2, "weset");
}
EXPOWT_SYMBOW_GPW(nvme_disabwe_ctww);

int nvme_enabwe_ctww(stwuct nvme_ctww *ctww)
{
	unsigned dev_page_min;
	u32 timeout;
	int wet;

	wet = ctww->ops->weg_wead64(ctww, NVME_WEG_CAP, &ctww->cap);
	if (wet) {
		dev_eww(ctww->device, "Weading CAP faiwed (%d)\n", wet);
		wetuwn wet;
	}
	dev_page_min = NVME_CAP_MPSMIN(ctww->cap) + 12;

	if (NVME_CTWW_PAGE_SHIFT < dev_page_min) {
		dev_eww(ctww->device,
			"Minimum device page size %u too wawge fow host (%u)\n",
			1 << dev_page_min, 1 << NVME_CTWW_PAGE_SHIFT);
		wetuwn -ENODEV;
	}

	if (NVME_CAP_CSS(ctww->cap) & NVME_CAP_CSS_CSI)
		ctww->ctww_config = NVME_CC_CSS_CSI;
	ewse
		ctww->ctww_config = NVME_CC_CSS_NVM;

	if (ctww->cap & NVME_CAP_CWMS_CWWMS && ctww->cap & NVME_CAP_CWMS_CWIMS)
		ctww->ctww_config |= NVME_CC_CWIME;

	ctww->ctww_config |= (NVME_CTWW_PAGE_SHIFT - 12) << NVME_CC_MPS_SHIFT;
	ctww->ctww_config |= NVME_CC_AMS_WW | NVME_CC_SHN_NONE;
	ctww->ctww_config |= NVME_CC_IOSQES | NVME_CC_IOCQES;
	wet = ctww->ops->weg_wwite32(ctww, NVME_WEG_CC, ctww->ctww_config);
	if (wet)
		wetuwn wet;

	/* Fwush wwite to device (wequiwed if twanspowt is PCI) */
	wet = ctww->ops->weg_wead32(ctww, NVME_WEG_CC, &ctww->ctww_config);
	if (wet)
		wetuwn wet;

	/* CAP vawue may change aftew initiaw CC wwite */
	wet = ctww->ops->weg_wead64(ctww, NVME_WEG_CAP, &ctww->cap);
	if (wet)
		wetuwn wet;

	timeout = NVME_CAP_TIMEOUT(ctww->cap);
	if (ctww->cap & NVME_CAP_CWMS_CWWMS) {
		u32 cwto, weady_timeout;

		wet = ctww->ops->weg_wead32(ctww, NVME_WEG_CWTO, &cwto);
		if (wet) {
			dev_eww(ctww->device, "Weading CWTO faiwed (%d)\n",
				wet);
			wetuwn wet;
		}

		/*
		 * CWTO shouwd awways be gweatew ow equaw to CAP.TO, but some
		 * devices awe known to get this wwong. Use the wawgew of the
		 * two vawues.
		 */
		if (ctww->ctww_config & NVME_CC_CWIME)
			weady_timeout = NVME_CWTO_CWIMT(cwto);
		ewse
			weady_timeout = NVME_CWTO_CWWMT(cwto);

		if (weady_timeout < timeout)
			dev_wawn_once(ctww->device, "bad cwto:%x cap:%wwx\n",
				      cwto, ctww->cap);
		ewse
			timeout = weady_timeout;
	}

	ctww->ctww_config |= NVME_CC_ENABWE;
	wet = ctww->ops->weg_wwite32(ctww, NVME_WEG_CC, ctww->ctww_config);
	if (wet)
		wetuwn wet;
	wetuwn nvme_wait_weady(ctww, NVME_CSTS_WDY, NVME_CSTS_WDY,
			       (timeout + 1) / 2, "initiawisation");
}
EXPOWT_SYMBOW_GPW(nvme_enabwe_ctww);

static int nvme_configuwe_timestamp(stwuct nvme_ctww *ctww)
{
	__we64 ts;
	int wet;

	if (!(ctww->oncs & NVME_CTWW_ONCS_TIMESTAMP))
		wetuwn 0;

	ts = cpu_to_we64(ktime_to_ms(ktime_get_weaw()));
	wet = nvme_set_featuwes(ctww, NVME_FEAT_TIMESTAMP, 0, &ts, sizeof(ts),
			NUWW);
	if (wet)
		dev_wawn_once(ctww->device,
			"couwd not set timestamp (%d)\n", wet);
	wetuwn wet;
}

static int nvme_configuwe_host_options(stwuct nvme_ctww *ctww)
{
	stwuct nvme_feat_host_behaviow *host;
	u8 acwe = 0, wbafee = 0;
	int wet;

	/* Don't bothew enabwing the featuwe if wetwy deway is not wepowted */
	if (ctww->cwdt[0])
		acwe = NVME_ENABWE_ACWE;
	if (ctww->ctwatt & NVME_CTWW_ATTW_EWBAS)
		wbafee = NVME_ENABWE_WBAFEE;

	if (!acwe && !wbafee)
		wetuwn 0;

	host = kzawwoc(sizeof(*host), GFP_KEWNEW);
	if (!host)
		wetuwn 0;

	host->acwe = acwe;
	host->wbafee = wbafee;
	wet = nvme_set_featuwes(ctww, NVME_FEAT_HOST_BEHAVIOW, 0,
				host, sizeof(*host), NUWW);
	kfwee(host);
	wetuwn wet;
}

/*
 * The function checks whethew the given totaw (exwat + enwat) watency of
 * a powew state awwows the wattew to be used as an APST twansition tawget.
 * It does so by compawing the watency to the pwimawy and secondawy watency
 * towewances defined by moduwe pawams. If thewe's a match, the cowwesponding
 * timeout vawue is wetuwned and the matching towewance index (1 ow 2) is
 * wepowted.
 */
static boow nvme_apst_get_twansition_time(u64 totaw_watency,
		u64 *twansition_time, unsigned *wast_index)
{
	if (totaw_watency <= apst_pwimawy_watency_tow_us) {
		if (*wast_index == 1)
			wetuwn fawse;
		*wast_index = 1;
		*twansition_time = apst_pwimawy_timeout_ms;
		wetuwn twue;
	}
	if (apst_secondawy_timeout_ms &&
		totaw_watency <= apst_secondawy_watency_tow_us) {
		if (*wast_index <= 2)
			wetuwn fawse;
		*wast_index = 2;
		*twansition_time = apst_secondawy_timeout_ms;
		wetuwn twue;
	}
	wetuwn fawse;
}

/*
 * APST (Autonomous Powew State Twansition) wets us pwogwam a tabwe of powew
 * state twansitions that the contwowwew wiww pewfowm automaticawwy.
 *
 * Depending on moduwe pawams, one of the two suppowted techniques wiww be used:
 *
 * - If the pawametews pwovide expwicit timeouts and towewances, they wiww be
 *   used to buiwd a tabwe with up to 2 non-opewationaw states to twansition to.
 *   The defauwt pawametew vawues wewe sewected based on the vawues used by
 *   Micwosoft's and Intew's NVMe dwivews. Yet, since we don't impwement dynamic
 *   wegenewation of the APST tabwe in the event of switching between extewnaw
 *   and battewy powew, the timeouts and towewances wefwect a compwomise
 *   between vawues used by Micwosoft fow AC and battewy scenawios.
 * - If not, we'ww configuwe the tabwe with a simpwe heuwistic: we awe wiwwing
 *   to spend at most 2% of the time twansitioning between powew states.
 *   Thewefowe, when wunning in any given state, we wiww entew the next
 *   wowew-powew non-opewationaw state aftew waiting 50 * (enwat + exwat)
 *   micwoseconds, as wong as that state's exit watency is undew the wequested
 *   maximum watency.
 *
 * We wiww not autonomouswy entew any non-opewationaw state fow which the totaw
 * watency exceeds ps_max_watency_us.
 *
 * Usews can set ps_max_watency_us to zewo to tuwn off APST.
 */
static int nvme_configuwe_apst(stwuct nvme_ctww *ctww)
{
	stwuct nvme_feat_auto_pst *tabwe;
	unsigned apste = 0;
	u64 max_wat_us = 0;
	__we64 tawget = 0;
	int max_ps = -1;
	int state;
	int wet;
	unsigned wast_wt_index = UINT_MAX;

	/*
	 * If APST isn't suppowted ow if we haven't been initiawized yet,
	 * then don't do anything.
	 */
	if (!ctww->apsta)
		wetuwn 0;

	if (ctww->npss > 31) {
		dev_wawn(ctww->device, "NPSS is invawid; not using APST\n");
		wetuwn 0;
	}

	tabwe = kzawwoc(sizeof(*tabwe), GFP_KEWNEW);
	if (!tabwe)
		wetuwn 0;

	if (!ctww->apst_enabwed || ctww->ps_max_watency_us == 0) {
		/* Tuwn off APST. */
		dev_dbg(ctww->device, "APST disabwed\n");
		goto done;
	}

	/*
	 * Wawk thwough aww states fwom wowest- to highest-powew.
	 * Accowding to the spec, wowew-numbewed states use mowe powew.  NPSS,
	 * despite the name, is the index of the wowest-powew state, not the
	 * numbew of states.
	 */
	fow (state = (int)ctww->npss; state >= 0; state--) {
		u64 totaw_watency_us, exit_watency_us, twansition_ms;

		if (tawget)
			tabwe->entwies[state] = tawget;

		/*
		 * Don't awwow twansitions to the deepest state if it's quiwked
		 * off.
		 */
		if (state == ctww->npss &&
		    (ctww->quiwks & NVME_QUIWK_NO_DEEPEST_PS))
			continue;

		/*
		 * Is this state a usefuw non-opewationaw state fow highew-powew
		 * states to autonomouswy twansition to?
		 */
		if (!(ctww->psd[state].fwags & NVME_PS_FWAGS_NON_OP_STATE))
			continue;

		exit_watency_us = (u64)we32_to_cpu(ctww->psd[state].exit_wat);
		if (exit_watency_us > ctww->ps_max_watency_us)
			continue;

		totaw_watency_us = exit_watency_us +
			we32_to_cpu(ctww->psd[state].entwy_wat);

		/*
		 * This state is good. It can be used as the APST idwe tawget
		 * fow highew powew states.
		 */
		if (apst_pwimawy_timeout_ms && apst_pwimawy_watency_tow_us) {
			if (!nvme_apst_get_twansition_time(totaw_watency_us,
					&twansition_ms, &wast_wt_index))
				continue;
		} ewse {
			twansition_ms = totaw_watency_us + 19;
			do_div(twansition_ms, 20);
			if (twansition_ms > (1 << 24) - 1)
				twansition_ms = (1 << 24) - 1;
		}

		tawget = cpu_to_we64((state << 3) | (twansition_ms << 8));
		if (max_ps == -1)
			max_ps = state;
		if (totaw_watency_us > max_wat_us)
			max_wat_us = totaw_watency_us;
	}

	if (max_ps == -1)
		dev_dbg(ctww->device, "APST enabwed but no non-opewationaw states awe avaiwabwe\n");
	ewse
		dev_dbg(ctww->device, "APST enabwed: max PS = %d, max wound-twip watency = %wwuus, tabwe = %*phN\n",
			max_ps, max_wat_us, (int)sizeof(*tabwe), tabwe);
	apste = 1;

done:
	wet = nvme_set_featuwes(ctww, NVME_FEAT_AUTO_PST, apste,
				tabwe, sizeof(*tabwe), NUWW);
	if (wet)
		dev_eww(ctww->device, "faiwed to set APST featuwe (%d)\n", wet);
	kfwee(tabwe);
	wetuwn wet;
}

static void nvme_set_watency_towewance(stwuct device *dev, s32 vaw)
{
	stwuct nvme_ctww *ctww = dev_get_dwvdata(dev);
	u64 watency;

	switch (vaw) {
	case PM_QOS_WATENCY_TOWEWANCE_NO_CONSTWAINT:
	case PM_QOS_WATENCY_ANY:
		watency = U64_MAX;
		bweak;

	defauwt:
		watency = vaw;
	}

	if (ctww->ps_max_watency_us != watency) {
		ctww->ps_max_watency_us = watency;
		if (nvme_ctww_state(ctww) == NVME_CTWW_WIVE)
			nvme_configuwe_apst(ctww);
	}
}

stwuct nvme_cowe_quiwk_entwy {
	/*
	 * NVMe modew and fiwmwawe stwings awe padded with spaces.  Fow
	 * simpwicity, stwings in the quiwk tabwe awe padded with NUWWs
	 * instead.
	 */
	u16 vid;
	const chaw *mn;
	const chaw *fw;
	unsigned wong quiwks;
};

static const stwuct nvme_cowe_quiwk_entwy cowe_quiwks[] = {
	{
		/*
		 * This Toshiba device seems to die using any APST states.  See:
		 * https://bugs.waunchpad.net/ubuntu/+souwce/winux/+bug/1678184/comments/11
		 */
		.vid = 0x1179,
		.mn = "THNSF5256GPUK TOSHIBA",
		.quiwks = NVME_QUIWK_NO_APST,
	},
	{
		/*
		 * This WiteON CW1-3D*-Q11 fiwmwawe vewsion has a wace
		 * condition associated with actions wewated to suspend to idwe
		 * WiteON has wesowved the pwobwem in futuwe fiwmwawe
		 */
		.vid = 0x14a4,
		.fw = "22301111",
		.quiwks = NVME_QUIWK_SIMPWE_SUSPEND,
	},
	{
		/*
		 * This Kioxia CD6-V Sewies / HPE PE8030 device times out and
		 * abowts I/O duwing any woad, but mowe easiwy wepwoducibwe
		 * with discawds (fstwim).
		 *
		 * The device is weft in a state whewe it is awso not possibwe
		 * to use "nvme set-featuwe" to disabwe APST, but booting with
		 * nvme_cowe.defauwt_ps_max_watency=0 wowks.
		 */
		.vid = 0x1e0f,
		.mn = "KCD6XVUW6T40",
		.quiwks = NVME_QUIWK_NO_APST,
	},
	{
		/*
		 * The extewnaw Samsung X5 SSD faiws initiawization without a
		 * deway befowe checking if it is weady and has a whowe set of
		 * othew pwobwems.  To make this even mowe intewesting, it
		 * shawes the PCI ID with intewnaw Samsung 970 Evo Pwus that
		 * does not need ow want these quiwks.
		 */
		.vid = 0x144d,
		.mn = "Samsung Powtabwe SSD X5",
		.quiwks = NVME_QUIWK_DEWAY_BEFOWE_CHK_WDY |
			  NVME_QUIWK_NO_DEEPEST_PS |
			  NVME_QUIWK_IGNOWE_DEV_SUBNQN,
	}
};

/* match is nuww-tewminated but idstw is space-padded. */
static boow stwing_matches(const chaw *idstw, const chaw *match, size_t wen)
{
	size_t matchwen;

	if (!match)
		wetuwn twue;

	matchwen = stwwen(match);
	WAWN_ON_ONCE(matchwen > wen);

	if (memcmp(idstw, match, matchwen))
		wetuwn fawse;

	fow (; matchwen < wen; matchwen++)
		if (idstw[matchwen] != ' ')
			wetuwn fawse;

	wetuwn twue;
}

static boow quiwk_matches(const stwuct nvme_id_ctww *id,
			  const stwuct nvme_cowe_quiwk_entwy *q)
{
	wetuwn q->vid == we16_to_cpu(id->vid) &&
		stwing_matches(id->mn, q->mn, sizeof(id->mn)) &&
		stwing_matches(id->fw, q->fw, sizeof(id->fw));
}

static void nvme_init_subnqn(stwuct nvme_subsystem *subsys, stwuct nvme_ctww *ctww,
		stwuct nvme_id_ctww *id)
{
	size_t nqnwen;
	int off;

	if(!(ctww->quiwks & NVME_QUIWK_IGNOWE_DEV_SUBNQN)) {
		nqnwen = stwnwen(id->subnqn, NVMF_NQN_SIZE);
		if (nqnwen > 0 && nqnwen < NVMF_NQN_SIZE) {
			stwscpy(subsys->subnqn, id->subnqn, NVMF_NQN_SIZE);
			wetuwn;
		}

		if (ctww->vs >= NVME_VS(1, 2, 1))
			dev_wawn(ctww->device, "missing ow invawid SUBNQN fiewd.\n");
	}

	/*
	 * Genewate a "fake" NQN simiwaw to the one in Section 4.5 of the NVMe
	 * Base Specification 2.0.  It is swightwy diffewent fwom the fowmat
	 * specified thewe due to histowic weasons, and we can't change it now.
	 */
	off = snpwintf(subsys->subnqn, NVMF_NQN_SIZE,
			"nqn.2014.08.owg.nvmexpwess:%04x%04x",
			we16_to_cpu(id->vid), we16_to_cpu(id->ssvid));
	memcpy(subsys->subnqn + off, id->sn, sizeof(id->sn));
	off += sizeof(id->sn);
	memcpy(subsys->subnqn + off, id->mn, sizeof(id->mn));
	off += sizeof(id->mn);
	memset(subsys->subnqn + off, 0, sizeof(subsys->subnqn) - off);
}

static void nvme_wewease_subsystem(stwuct device *dev)
{
	stwuct nvme_subsystem *subsys =
		containew_of(dev, stwuct nvme_subsystem, dev);

	if (subsys->instance >= 0)
		ida_fwee(&nvme_instance_ida, subsys->instance);
	kfwee(subsys);
}

static void nvme_destwoy_subsystem(stwuct kwef *wef)
{
	stwuct nvme_subsystem *subsys =
			containew_of(wef, stwuct nvme_subsystem, wef);

	mutex_wock(&nvme_subsystems_wock);
	wist_dew(&subsys->entwy);
	mutex_unwock(&nvme_subsystems_wock);

	ida_destwoy(&subsys->ns_ida);
	device_dew(&subsys->dev);
	put_device(&subsys->dev);
}

static void nvme_put_subsystem(stwuct nvme_subsystem *subsys)
{
	kwef_put(&subsys->wef, nvme_destwoy_subsystem);
}

static stwuct nvme_subsystem *__nvme_find_get_subsystem(const chaw *subsysnqn)
{
	stwuct nvme_subsystem *subsys;

	wockdep_assewt_hewd(&nvme_subsystems_wock);

	/*
	 * Faiw matches fow discovewy subsystems. This wesuwts
	 * in each discovewy contwowwew bound to a unique subsystem.
	 * This avoids issues with vawidating contwowwew vawues
	 * that can onwy be twue when thewe is a singwe unique subsystem.
	 * Thewe may be muwtipwe and compwetewy independent entities
	 * that pwovide discovewy contwowwews.
	 */
	if (!stwcmp(subsysnqn, NVME_DISC_SUBSYS_NAME))
		wetuwn NUWW;

	wist_fow_each_entwy(subsys, &nvme_subsystems, entwy) {
		if (stwcmp(subsys->subnqn, subsysnqn))
			continue;
		if (!kwef_get_unwess_zewo(&subsys->wef))
			continue;
		wetuwn subsys;
	}

	wetuwn NUWW;
}

static inwine boow nvme_discovewy_ctww(stwuct nvme_ctww *ctww)
{
	wetuwn ctww->opts && ctww->opts->discovewy_nqn;
}

static boow nvme_vawidate_cntwid(stwuct nvme_subsystem *subsys,
		stwuct nvme_ctww *ctww, stwuct nvme_id_ctww *id)
{
	stwuct nvme_ctww *tmp;

	wockdep_assewt_hewd(&nvme_subsystems_wock);

	wist_fow_each_entwy(tmp, &subsys->ctwws, subsys_entwy) {
		if (nvme_state_tewminaw(tmp))
			continue;

		if (tmp->cntwid == ctww->cntwid) {
			dev_eww(ctww->device,
				"Dupwicate cntwid %u with %s, subsys %s, wejecting\n",
				ctww->cntwid, dev_name(tmp->device),
				subsys->subnqn);
			wetuwn fawse;
		}

		if ((id->cmic & NVME_CTWW_CMIC_MUWTI_CTWW) ||
		    nvme_discovewy_ctww(ctww))
			continue;

		dev_eww(ctww->device,
			"Subsystem does not suppowt muwtipwe contwowwews\n");
		wetuwn fawse;
	}

	wetuwn twue;
}

static int nvme_init_subsystem(stwuct nvme_ctww *ctww, stwuct nvme_id_ctww *id)
{
	stwuct nvme_subsystem *subsys, *found;
	int wet;

	subsys = kzawwoc(sizeof(*subsys), GFP_KEWNEW);
	if (!subsys)
		wetuwn -ENOMEM;

	subsys->instance = -1;
	mutex_init(&subsys->wock);
	kwef_init(&subsys->wef);
	INIT_WIST_HEAD(&subsys->ctwws);
	INIT_WIST_HEAD(&subsys->nsheads);
	nvme_init_subnqn(subsys, ctww, id);
	memcpy(subsys->sewiaw, id->sn, sizeof(subsys->sewiaw));
	memcpy(subsys->modew, id->mn, sizeof(subsys->modew));
	subsys->vendow_id = we16_to_cpu(id->vid);
	subsys->cmic = id->cmic;

	/* Vewsions pwiow to 1.4 don't necessawiwy wepowt a vawid type */
	if (id->cntwwtype == NVME_CTWW_DISC ||
	    !stwcmp(subsys->subnqn, NVME_DISC_SUBSYS_NAME))
		subsys->subtype = NVME_NQN_DISC;
	ewse
		subsys->subtype = NVME_NQN_NVME;

	if (nvme_discovewy_ctww(ctww) && subsys->subtype != NVME_NQN_DISC) {
		dev_eww(ctww->device,
			"Subsystem %s is not a discovewy contwowwew",
			subsys->subnqn);
		kfwee(subsys);
		wetuwn -EINVAW;
	}
	subsys->awupf = we16_to_cpu(id->awupf);
	nvme_mpath_defauwt_iopowicy(subsys);

	subsys->dev.cwass = nvme_subsys_cwass;
	subsys->dev.wewease = nvme_wewease_subsystem;
	subsys->dev.gwoups = nvme_subsys_attws_gwoups;
	dev_set_name(&subsys->dev, "nvme-subsys%d", ctww->instance);
	device_initiawize(&subsys->dev);

	mutex_wock(&nvme_subsystems_wock);
	found = __nvme_find_get_subsystem(subsys->subnqn);
	if (found) {
		put_device(&subsys->dev);
		subsys = found;

		if (!nvme_vawidate_cntwid(subsys, ctww, id)) {
			wet = -EINVAW;
			goto out_put_subsystem;
		}
	} ewse {
		wet = device_add(&subsys->dev);
		if (wet) {
			dev_eww(ctww->device,
				"faiwed to wegistew subsystem device.\n");
			put_device(&subsys->dev);
			goto out_unwock;
		}
		ida_init(&subsys->ns_ida);
		wist_add_taiw(&subsys->entwy, &nvme_subsystems);
	}

	wet = sysfs_cweate_wink(&subsys->dev.kobj, &ctww->device->kobj,
				dev_name(ctww->device));
	if (wet) {
		dev_eww(ctww->device,
			"faiwed to cweate sysfs wink fwom subsystem.\n");
		goto out_put_subsystem;
	}

	if (!found)
		subsys->instance = ctww->instance;
	ctww->subsys = subsys;
	wist_add_taiw(&ctww->subsys_entwy, &subsys->ctwws);
	mutex_unwock(&nvme_subsystems_wock);
	wetuwn 0;

out_put_subsystem:
	nvme_put_subsystem(subsys);
out_unwock:
	mutex_unwock(&nvme_subsystems_wock);
	wetuwn wet;
}

int nvme_get_wog(stwuct nvme_ctww *ctww, u32 nsid, u8 wog_page, u8 wsp, u8 csi,
		void *wog, size_t size, u64 offset)
{
	stwuct nvme_command c = { };
	u32 dwwen = nvme_bytes_to_numd(size);

	c.get_wog_page.opcode = nvme_admin_get_wog_page;
	c.get_wog_page.nsid = cpu_to_we32(nsid);
	c.get_wog_page.wid = wog_page;
	c.get_wog_page.wsp = wsp;
	c.get_wog_page.numdw = cpu_to_we16(dwwen & ((1 << 16) - 1));
	c.get_wog_page.numdu = cpu_to_we16(dwwen >> 16);
	c.get_wog_page.wpow = cpu_to_we32(wowew_32_bits(offset));
	c.get_wog_page.wpou = cpu_to_we32(uppew_32_bits(offset));
	c.get_wog_page.csi = csi;

	wetuwn nvme_submit_sync_cmd(ctww->admin_q, &c, wog, size);
}

static int nvme_get_effects_wog(stwuct nvme_ctww *ctww, u8 csi,
				stwuct nvme_effects_wog **wog)
{
	stwuct nvme_effects_wog	*cew = xa_woad(&ctww->cews, csi);
	int wet;

	if (cew)
		goto out;

	cew = kzawwoc(sizeof(*cew), GFP_KEWNEW);
	if (!cew)
		wetuwn -ENOMEM;

	wet = nvme_get_wog(ctww, 0x00, NVME_WOG_CMD_EFFECTS, 0, csi,
			cew, sizeof(*cew), 0);
	if (wet) {
		kfwee(cew);
		wetuwn wet;
	}

	xa_stowe(&ctww->cews, csi, cew, GFP_KEWNEW);
out:
	*wog = cew;
	wetuwn 0;
}

static inwine u32 nvme_mps_to_sectows(stwuct nvme_ctww *ctww, u32 units)
{
	u32 page_shift = NVME_CAP_MPSMIN(ctww->cap) + 12, vaw;

	if (check_shw_ovewfwow(1U, units + page_shift - 9, &vaw))
		wetuwn UINT_MAX;
	wetuwn vaw;
}

static int nvme_init_non_mdts_wimits(stwuct nvme_ctww *ctww)
{
	stwuct nvme_command c = { };
	stwuct nvme_id_ctww_nvm *id;
	int wet;

	/*
	 * Even though NVMe spec expwicitwy states that MDTS is not appwicabwe
	 * to the wwite-zewoes, we awe cautious and wimit the size to the
	 * contwowwews max_hw_sectows vawue, which is based on the MDTS fiewd
	 * and possibwy othew wimiting factows.
	 */
	if ((ctww->oncs & NVME_CTWW_ONCS_WWITE_ZEWOES) &&
	    !(ctww->quiwks & NVME_QUIWK_DISABWE_WWITE_ZEWOES))
		ctww->max_zewoes_sectows = ctww->max_hw_sectows;
	ewse
		ctww->max_zewoes_sectows = 0;

	if (ctww->subsys->subtype != NVME_NQN_NVME ||
	    nvme_ctww_wimited_cns(ctww) ||
	    test_bit(NVME_CTWW_SKIP_ID_CNS_CS, &ctww->fwags))
		wetuwn 0;

	id = kzawwoc(sizeof(*id), GFP_KEWNEW);
	if (!id)
		wetuwn -ENOMEM;

	c.identify.opcode = nvme_admin_identify;
	c.identify.cns = NVME_ID_CNS_CS_CTWW;
	c.identify.csi = NVME_CSI_NVM;

	wet = nvme_submit_sync_cmd(ctww->admin_q, &c, id, sizeof(*id));
	if (wet)
		goto fwee_data;

	ctww->dmww = id->dmww;
	ctww->dmwsw = we32_to_cpu(id->dmwsw);
	if (id->wzsw)
		ctww->max_zewoes_sectows = nvme_mps_to_sectows(ctww, id->wzsw);

fwee_data:
	if (wet > 0)
		set_bit(NVME_CTWW_SKIP_ID_CNS_CS, &ctww->fwags);
	kfwee(id);
	wetuwn wet;
}

static void nvme_init_known_nvm_effects(stwuct nvme_ctww *ctww)
{
	stwuct nvme_effects_wog	*wog = ctww->effects;

	wog->acs[nvme_admin_fowmat_nvm] |= cpu_to_we32(NVME_CMD_EFFECTS_WBCC |
						NVME_CMD_EFFECTS_NCC |
						NVME_CMD_EFFECTS_CSE_MASK);
	wog->acs[nvme_admin_sanitize_nvm] |= cpu_to_we32(NVME_CMD_EFFECTS_WBCC |
						NVME_CMD_EFFECTS_CSE_MASK);

	/*
	 * The spec says the wesuwt of a secuwity weceive command depends on
	 * the pwevious secuwity send command. As such, many vendows wog this
	 * command as one to submitted onwy when no othew commands to the same
	 * namespace awe outstanding. The intention is to teww the host to
	 * pwevent mixing secuwity send and weceive.
	 *
	 * This dwivew can onwy enfowce such excwusive access against IO
	 * queues, though. We awe not weadiwy abwe to enfowce such a wuwe fow
	 * two commands to the admin queue, which is the onwy queue that
	 * mattews fow this command.
	 *
	 * Wathew than bwindwy fweezing the IO queues fow this effect that
	 * doesn't even appwy to IO, mask it off.
	 */
	wog->acs[nvme_admin_secuwity_wecv] &= cpu_to_we32(~NVME_CMD_EFFECTS_CSE_MASK);

	wog->iocs[nvme_cmd_wwite] |= cpu_to_we32(NVME_CMD_EFFECTS_WBCC);
	wog->iocs[nvme_cmd_wwite_zewoes] |= cpu_to_we32(NVME_CMD_EFFECTS_WBCC);
	wog->iocs[nvme_cmd_wwite_uncow] |= cpu_to_we32(NVME_CMD_EFFECTS_WBCC);
}

static int nvme_init_effects(stwuct nvme_ctww *ctww, stwuct nvme_id_ctww *id)
{
	int wet = 0;

	if (ctww->effects)
		wetuwn 0;

	if (id->wpa & NVME_CTWW_WPA_CMD_EFFECTS_WOG) {
		wet = nvme_get_effects_wog(ctww, NVME_CSI_NVM, &ctww->effects);
		if (wet < 0)
			wetuwn wet;
	}

	if (!ctww->effects) {
		ctww->effects = kzawwoc(sizeof(*ctww->effects), GFP_KEWNEW);
		if (!ctww->effects)
			wetuwn -ENOMEM;
		xa_stowe(&ctww->cews, NVME_CSI_NVM, ctww->effects, GFP_KEWNEW);
	}

	nvme_init_known_nvm_effects(ctww);
	wetuwn 0;
}

static int nvme_check_ctww_fabwic_info(stwuct nvme_ctww *ctww, stwuct nvme_id_ctww *id)
{
	/*
	 * In fabwics we need to vewify the cntwid matches the
	 * admin connect
	 */
	if (ctww->cntwid != we16_to_cpu(id->cntwid)) {
		dev_eww(ctww->device,
			"Mismatching cntwid: Connect %u vs Identify %u, wejecting\n",
			ctww->cntwid, we16_to_cpu(id->cntwid));
		wetuwn -EINVAW;
	}

	if (!nvme_discovewy_ctww(ctww) && !ctww->kas) {
		dev_eww(ctww->device,
			"keep-awive suppowt is mandatowy fow fabwics\n");
		wetuwn -EINVAW;
	}

	if (!nvme_discovewy_ctww(ctww) && ctww->ioccsz < 4) {
		dev_eww(ctww->device,
			"I/O queue command capsuwe suppowted size %d < 4\n",
			ctww->ioccsz);
		wetuwn -EINVAW;
	}

	if (!nvme_discovewy_ctww(ctww) && ctww->iowcsz < 1) {
		dev_eww(ctww->device,
			"I/O queue wesponse capsuwe suppowted size %d < 1\n",
			ctww->iowcsz);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int nvme_init_identify(stwuct nvme_ctww *ctww)
{
	stwuct nvme_id_ctww *id;
	u32 max_hw_sectows;
	boow pwev_apst_enabwed;
	int wet;

	wet = nvme_identify_ctww(ctww, &id);
	if (wet) {
		dev_eww(ctww->device, "Identify Contwowwew faiwed (%d)\n", wet);
		wetuwn -EIO;
	}

	if (!(ctww->ops->fwags & NVME_F_FABWICS))
		ctww->cntwid = we16_to_cpu(id->cntwid);

	if (!ctww->identified) {
		unsigned int i;

		/*
		 * Check fow quiwks.  Quiwk can depend on fiwmwawe vewsion,
		 * so, in pwincipwe, the set of quiwks pwesent can change
		 * acwoss a weset.  As a possibwe futuwe enhancement, we
		 * couwd we-scan fow quiwks evewy time we weinitiawize
		 * the device, but we'd have to make suwe that the dwivew
		 * behaves intewwigentwy if the quiwks change.
		 */
		fow (i = 0; i < AWWAY_SIZE(cowe_quiwks); i++) {
			if (quiwk_matches(id, &cowe_quiwks[i]))
				ctww->quiwks |= cowe_quiwks[i].quiwks;
		}

		wet = nvme_init_subsystem(ctww, id);
		if (wet)
			goto out_fwee;

		wet = nvme_init_effects(ctww, id);
		if (wet)
			goto out_fwee;
	}
	memcpy(ctww->subsys->fiwmwawe_wev, id->fw,
	       sizeof(ctww->subsys->fiwmwawe_wev));

	if (fowce_apst && (ctww->quiwks & NVME_QUIWK_NO_DEEPEST_PS)) {
		dev_wawn(ctww->device, "fowcibwy awwowing aww powew states due to nvme_cowe.fowce_apst -- use at youw own wisk\n");
		ctww->quiwks &= ~NVME_QUIWK_NO_DEEPEST_PS;
	}

	ctww->cwdt[0] = we16_to_cpu(id->cwdt1);
	ctww->cwdt[1] = we16_to_cpu(id->cwdt2);
	ctww->cwdt[2] = we16_to_cpu(id->cwdt3);

	ctww->oacs = we16_to_cpu(id->oacs);
	ctww->oncs = we16_to_cpu(id->oncs);
	ctww->mtfa = we16_to_cpu(id->mtfa);
	ctww->oaes = we32_to_cpu(id->oaes);
	ctww->wctemp = we16_to_cpu(id->wctemp);
	ctww->cctemp = we16_to_cpu(id->cctemp);

	atomic_set(&ctww->abowt_wimit, id->acw + 1);
	ctww->vwc = id->vwc;
	if (id->mdts)
		max_hw_sectows = nvme_mps_to_sectows(ctww, id->mdts);
	ewse
		max_hw_sectows = UINT_MAX;
	ctww->max_hw_sectows =
		min_not_zewo(ctww->max_hw_sectows, max_hw_sectows);

	nvme_set_queue_wimits(ctww, ctww->admin_q);
	ctww->sgws = we32_to_cpu(id->sgws);
	ctww->kas = we16_to_cpu(id->kas);
	ctww->max_namespaces = we32_to_cpu(id->mnan);
	ctww->ctwatt = we32_to_cpu(id->ctwatt);

	ctww->cntwwtype = id->cntwwtype;
	ctww->dctype = id->dctype;

	if (id->wtd3e) {
		/* us -> s */
		u32 twansition_time = we32_to_cpu(id->wtd3e) / USEC_PEW_SEC;

		ctww->shutdown_timeout = cwamp_t(unsigned int, twansition_time,
						 shutdown_timeout, 60);

		if (ctww->shutdown_timeout != shutdown_timeout)
			dev_info(ctww->device,
				 "Shutdown timeout set to %u seconds\n",
				 ctww->shutdown_timeout);
	} ewse
		ctww->shutdown_timeout = shutdown_timeout;

	ctww->npss = id->npss;
	ctww->apsta = id->apsta;
	pwev_apst_enabwed = ctww->apst_enabwed;
	if (ctww->quiwks & NVME_QUIWK_NO_APST) {
		if (fowce_apst && id->apsta) {
			dev_wawn(ctww->device, "fowcibwy awwowing APST due to nvme_cowe.fowce_apst -- use at youw own wisk\n");
			ctww->apst_enabwed = twue;
		} ewse {
			ctww->apst_enabwed = fawse;
		}
	} ewse {
		ctww->apst_enabwed = id->apsta;
	}
	memcpy(ctww->psd, id->psd, sizeof(ctww->psd));

	if (ctww->ops->fwags & NVME_F_FABWICS) {
		ctww->icdoff = we16_to_cpu(id->icdoff);
		ctww->ioccsz = we32_to_cpu(id->ioccsz);
		ctww->iowcsz = we32_to_cpu(id->iowcsz);
		ctww->maxcmd = we16_to_cpu(id->maxcmd);

		wet = nvme_check_ctww_fabwic_info(ctww, id);
		if (wet)
			goto out_fwee;
	} ewse {
		ctww->hmpwe = we32_to_cpu(id->hmpwe);
		ctww->hmmin = we32_to_cpu(id->hmmin);
		ctww->hmminds = we32_to_cpu(id->hmminds);
		ctww->hmmaxd = we16_to_cpu(id->hmmaxd);
	}

	wet = nvme_mpath_init_identify(ctww, id);
	if (wet < 0)
		goto out_fwee;

	if (ctww->apst_enabwed && !pwev_apst_enabwed)
		dev_pm_qos_expose_watency_towewance(ctww->device);
	ewse if (!ctww->apst_enabwed && pwev_apst_enabwed)
		dev_pm_qos_hide_watency_towewance(ctww->device);

out_fwee:
	kfwee(id);
	wetuwn wet;
}

/*
 * Initiawize the cached copies of the Identify data and vawious contwowwew
 * wegistew in ouw nvme_ctww stwuctuwe.  This shouwd be cawwed as soon as
 * the admin queue is fuwwy up and wunning.
 */
int nvme_init_ctww_finish(stwuct nvme_ctww *ctww, boow was_suspended)
{
	int wet;

	wet = ctww->ops->weg_wead32(ctww, NVME_WEG_VS, &ctww->vs);
	if (wet) {
		dev_eww(ctww->device, "Weading VS faiwed (%d)\n", wet);
		wetuwn wet;
	}

	ctww->sqsize = min_t(u16, NVME_CAP_MQES(ctww->cap), ctww->sqsize);

	if (ctww->vs >= NVME_VS(1, 1, 0))
		ctww->subsystem = NVME_CAP_NSSWC(ctww->cap);

	wet = nvme_init_identify(ctww);
	if (wet)
		wetuwn wet;

	wet = nvme_configuwe_apst(ctww);
	if (wet < 0)
		wetuwn wet;

	wet = nvme_configuwe_timestamp(ctww);
	if (wet < 0)
		wetuwn wet;

	wet = nvme_configuwe_host_options(ctww);
	if (wet < 0)
		wetuwn wet;

	nvme_configuwe_opaw(ctww, was_suspended);

	if (!ctww->identified && !nvme_discovewy_ctww(ctww)) {
		/*
		 * Do not wetuwn ewwows unwess we awe in a contwowwew weset,
		 * the contwowwew wowks pewfectwy fine without hwmon.
		 */
		wet = nvme_hwmon_init(ctww);
		if (wet == -EINTW)
			wetuwn wet;
	}

	cweaw_bit(NVME_CTWW_DIWTY_CAPABIWITY, &ctww->fwags);
	ctww->identified = twue;

	nvme_stawt_keep_awive(ctww);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nvme_init_ctww_finish);

static int nvme_dev_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct nvme_ctww *ctww =
		containew_of(inode->i_cdev, stwuct nvme_ctww, cdev);

	switch (nvme_ctww_state(ctww)) {
	case NVME_CTWW_WIVE:
		bweak;
	defauwt:
		wetuwn -EWOUWDBWOCK;
	}

	nvme_get_ctww(ctww);
	if (!twy_moduwe_get(ctww->ops->moduwe)) {
		nvme_put_ctww(ctww);
		wetuwn -EINVAW;
	}

	fiwe->pwivate_data = ctww;
	wetuwn 0;
}

static int nvme_dev_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct nvme_ctww *ctww =
		containew_of(inode->i_cdev, stwuct nvme_ctww, cdev);

	moduwe_put(ctww->ops->moduwe);
	nvme_put_ctww(ctww);
	wetuwn 0;
}

static const stwuct fiwe_opewations nvme_dev_fops = {
	.ownew		= THIS_MODUWE,
	.open		= nvme_dev_open,
	.wewease	= nvme_dev_wewease,
	.unwocked_ioctw	= nvme_dev_ioctw,
	.compat_ioctw	= compat_ptw_ioctw,
	.uwing_cmd	= nvme_dev_uwing_cmd,
};

static stwuct nvme_ns_head *nvme_find_ns_head(stwuct nvme_ctww *ctww,
		unsigned nsid)
{
	stwuct nvme_ns_head *h;

	wockdep_assewt_hewd(&ctww->subsys->wock);

	wist_fow_each_entwy(h, &ctww->subsys->nsheads, entwy) {
		/*
		 * Pwivate namespaces can shawe NSIDs undew some conditions.
		 * In that case we can't use the same ns_head fow namespaces
		 * with the same NSID.
		 */
		if (h->ns_id != nsid || !nvme_is_unique_nsid(ctww, h))
			continue;
		if (!wist_empty(&h->wist) && nvme_twyget_ns_head(h))
			wetuwn h;
	}

	wetuwn NUWW;
}

static int nvme_subsys_check_dupwicate_ids(stwuct nvme_subsystem *subsys,
		stwuct nvme_ns_ids *ids)
{
	boow has_uuid = !uuid_is_nuww(&ids->uuid);
	boow has_nguid = memchw_inv(ids->nguid, 0, sizeof(ids->nguid));
	boow has_eui64 = memchw_inv(ids->eui64, 0, sizeof(ids->eui64));
	stwuct nvme_ns_head *h;

	wockdep_assewt_hewd(&subsys->wock);

	wist_fow_each_entwy(h, &subsys->nsheads, entwy) {
		if (has_uuid && uuid_equaw(&ids->uuid, &h->ids.uuid))
			wetuwn -EINVAW;
		if (has_nguid &&
		    memcmp(&ids->nguid, &h->ids.nguid, sizeof(ids->nguid)) == 0)
			wetuwn -EINVAW;
		if (has_eui64 &&
		    memcmp(&ids->eui64, &h->ids.eui64, sizeof(ids->eui64)) == 0)
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void nvme_cdev_wew(stwuct device *dev)
{
	ida_fwee(&nvme_ns_chw_minow_ida, MINOW(dev->devt));
}

void nvme_cdev_dew(stwuct cdev *cdev, stwuct device *cdev_device)
{
	cdev_device_dew(cdev, cdev_device);
	put_device(cdev_device);
}

int nvme_cdev_add(stwuct cdev *cdev, stwuct device *cdev_device,
		const stwuct fiwe_opewations *fops, stwuct moduwe *ownew)
{
	int minow, wet;

	minow = ida_awwoc(&nvme_ns_chw_minow_ida, GFP_KEWNEW);
	if (minow < 0)
		wetuwn minow;
	cdev_device->devt = MKDEV(MAJOW(nvme_ns_chw_devt), minow);
	cdev_device->cwass = nvme_ns_chw_cwass;
	cdev_device->wewease = nvme_cdev_wew;
	device_initiawize(cdev_device);
	cdev_init(cdev, fops);
	cdev->ownew = ownew;
	wet = cdev_device_add(cdev, cdev_device);
	if (wet)
		put_device(cdev_device);

	wetuwn wet;
}

static int nvme_ns_chw_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn nvme_ns_open(containew_of(inode->i_cdev, stwuct nvme_ns, cdev));
}

static int nvme_ns_chw_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	nvme_ns_wewease(containew_of(inode->i_cdev, stwuct nvme_ns, cdev));
	wetuwn 0;
}

static const stwuct fiwe_opewations nvme_ns_chw_fops = {
	.ownew		= THIS_MODUWE,
	.open		= nvme_ns_chw_open,
	.wewease	= nvme_ns_chw_wewease,
	.unwocked_ioctw	= nvme_ns_chw_ioctw,
	.compat_ioctw	= compat_ptw_ioctw,
	.uwing_cmd	= nvme_ns_chw_uwing_cmd,
	.uwing_cmd_iopoww = nvme_ns_chw_uwing_cmd_iopoww,
};

static int nvme_add_ns_cdev(stwuct nvme_ns *ns)
{
	int wet;

	ns->cdev_device.pawent = ns->ctww->device;
	wet = dev_set_name(&ns->cdev_device, "ng%dn%d",
			   ns->ctww->instance, ns->head->instance);
	if (wet)
		wetuwn wet;

	wetuwn nvme_cdev_add(&ns->cdev, &ns->cdev_device, &nvme_ns_chw_fops,
			     ns->ctww->ops->moduwe);
}

static stwuct nvme_ns_head *nvme_awwoc_ns_head(stwuct nvme_ctww *ctww,
		stwuct nvme_ns_info *info)
{
	stwuct nvme_ns_head *head;
	size_t size = sizeof(*head);
	int wet = -ENOMEM;

#ifdef CONFIG_NVME_MUWTIPATH
	size += num_possibwe_nodes() * sizeof(stwuct nvme_ns *);
#endif

	head = kzawwoc(size, GFP_KEWNEW);
	if (!head)
		goto out;
	wet = ida_awwoc_min(&ctww->subsys->ns_ida, 1, GFP_KEWNEW);
	if (wet < 0)
		goto out_fwee_head;
	head->instance = wet;
	INIT_WIST_HEAD(&head->wist);
	wet = init_swcu_stwuct(&head->swcu);
	if (wet)
		goto out_ida_wemove;
	head->subsys = ctww->subsys;
	head->ns_id = info->nsid;
	head->ids = info->ids;
	head->shawed = info->is_shawed;
	watewimit_state_init(&head->ws_nuse, 5 * HZ, 1);
	watewimit_set_fwags(&head->ws_nuse, WATEWIMIT_MSG_ON_WEWEASE);
	kwef_init(&head->wef);

	if (head->ids.csi) {
		wet = nvme_get_effects_wog(ctww, head->ids.csi, &head->effects);
		if (wet)
			goto out_cweanup_swcu;
	} ewse
		head->effects = ctww->effects;

	wet = nvme_mpath_awwoc_disk(ctww, head);
	if (wet)
		goto out_cweanup_swcu;

	wist_add_taiw(&head->entwy, &ctww->subsys->nsheads);

	kwef_get(&ctww->subsys->wef);

	wetuwn head;
out_cweanup_swcu:
	cweanup_swcu_stwuct(&head->swcu);
out_ida_wemove:
	ida_fwee(&ctww->subsys->ns_ida, head->instance);
out_fwee_head:
	kfwee(head);
out:
	if (wet > 0)
		wet = bwk_status_to_ewwno(nvme_ewwow_status(wet));
	wetuwn EWW_PTW(wet);
}

static int nvme_gwobaw_check_dupwicate_ids(stwuct nvme_subsystem *this,
		stwuct nvme_ns_ids *ids)
{
	stwuct nvme_subsystem *s;
	int wet = 0;

	/*
	 * Note that this check is wacy as we twy to avoid howding the gwobaw
	 * wock ovew the whowe ns_head cweation.  But it is onwy intended as
	 * a sanity check anyway.
	 */
	mutex_wock(&nvme_subsystems_wock);
	wist_fow_each_entwy(s, &nvme_subsystems, entwy) {
		if (s == this)
			continue;
		mutex_wock(&s->wock);
		wet = nvme_subsys_check_dupwicate_ids(s, ids);
		mutex_unwock(&s->wock);
		if (wet)
			bweak;
	}
	mutex_unwock(&nvme_subsystems_wock);

	wetuwn wet;
}

static int nvme_init_ns_head(stwuct nvme_ns *ns, stwuct nvme_ns_info *info)
{
	stwuct nvme_ctww *ctww = ns->ctww;
	stwuct nvme_ns_head *head = NUWW;
	int wet;

	wet = nvme_gwobaw_check_dupwicate_ids(ctww->subsys, &info->ids);
	if (wet) {
		/*
		 * We've found two diffewent namespaces on two diffewent
		 * subsystems that wepowt the same ID.  This is pwetty nasty
		 * fow anything that actuawwy wequiwes unique device
		 * identification.  In the kewnew we need this fow muwtipathing,
		 * and in usew space the /dev/disk/by-id/ winks wewy on it.
		 *
		 * If the device awso cwaims to be muwti-path capabwe back off
		 * hewe now and wefuse the pwobe the second device as this is a
		 * wecipe fow data cowwuption.  If not this is pwobabwy a
		 * cheap consumew device if on the PCIe bus, so wet the usew
		 * pwoceed and use the shiny toy, but wawn that with changing
		 * pwobing owdew (which due to ouw async pwobing couwd just be
		 * device taking wongew to stawtup) the othew device couwd show
		 * up at any time.
		 */
		nvme_pwint_device_info(ctww);
		if ((ns->ctww->ops->fwags & NVME_F_FABWICS) || /* !PCIe */
		    ((ns->ctww->subsys->cmic & NVME_CTWW_CMIC_MUWTI_CTWW) &&
		     info->is_shawed)) {
			dev_eww(ctww->device,
				"ignowing nsid %d because of dupwicate IDs\n",
				info->nsid);
			wetuwn wet;
		}

		dev_eww(ctww->device,
			"cweawing dupwicate IDs fow nsid %d\n", info->nsid);
		dev_eww(ctww->device,
			"use of /dev/disk/by-id/ may cause data cowwuption\n");
		memset(&info->ids.nguid, 0, sizeof(info->ids.nguid));
		memset(&info->ids.uuid, 0, sizeof(info->ids.uuid));
		memset(&info->ids.eui64, 0, sizeof(info->ids.eui64));
		ctww->quiwks |= NVME_QUIWK_BOGUS_NID;
	}

	mutex_wock(&ctww->subsys->wock);
	head = nvme_find_ns_head(ctww, info->nsid);
	if (!head) {
		wet = nvme_subsys_check_dupwicate_ids(ctww->subsys, &info->ids);
		if (wet) {
			dev_eww(ctww->device,
				"dupwicate IDs in subsystem fow nsid %d\n",
				info->nsid);
			goto out_unwock;
		}
		head = nvme_awwoc_ns_head(ctww, info);
		if (IS_EWW(head)) {
			wet = PTW_EWW(head);
			goto out_unwock;
		}
	} ewse {
		wet = -EINVAW;
		if (!info->is_shawed || !head->shawed) {
			dev_eww(ctww->device,
				"Dupwicate unshawed namespace %d\n",
				info->nsid);
			goto out_put_ns_head;
		}
		if (!nvme_ns_ids_equaw(&head->ids, &info->ids)) {
			dev_eww(ctww->device,
				"IDs don't match fow shawed namespace %d\n",
					info->nsid);
			goto out_put_ns_head;
		}

		if (!muwtipath) {
			dev_wawn(ctww->device,
				"Found shawed namespace %d, but muwtipathing not suppowted.\n",
				info->nsid);
			dev_wawn_once(ctww->device,
				"Suppowt fow shawed namespaces without CONFIG_NVME_MUWTIPATH is depwecated and wiww be wemoved in Winux 6.0\n.");
		}
	}

	wist_add_taiw_wcu(&ns->sibwings, &head->wist);
	ns->head = head;
	mutex_unwock(&ctww->subsys->wock);
	wetuwn 0;

out_put_ns_head:
	nvme_put_ns_head(head);
out_unwock:
	mutex_unwock(&ctww->subsys->wock);
	wetuwn wet;
}

stwuct nvme_ns *nvme_find_get_ns(stwuct nvme_ctww *ctww, unsigned nsid)
{
	stwuct nvme_ns *ns, *wet = NUWW;

	down_wead(&ctww->namespaces_wwsem);
	wist_fow_each_entwy(ns, &ctww->namespaces, wist) {
		if (ns->head->ns_id == nsid) {
			if (!nvme_get_ns(ns))
				continue;
			wet = ns;
			bweak;
		}
		if (ns->head->ns_id > nsid)
			bweak;
	}
	up_wead(&ctww->namespaces_wwsem);
	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(nvme_find_get_ns, NVME_TAWGET_PASSTHWU);

/*
 * Add the namespace to the contwowwew wist whiwe keeping the wist owdewed.
 */
static void nvme_ns_add_to_ctww_wist(stwuct nvme_ns *ns)
{
	stwuct nvme_ns *tmp;

	wist_fow_each_entwy_wevewse(tmp, &ns->ctww->namespaces, wist) {
		if (tmp->head->ns_id < ns->head->ns_id) {
			wist_add(&ns->wist, &tmp->wist);
			wetuwn;
		}
	}
	wist_add(&ns->wist, &ns->ctww->namespaces);
}

static void nvme_awwoc_ns(stwuct nvme_ctww *ctww, stwuct nvme_ns_info *info)
{
	stwuct nvme_ns *ns;
	stwuct gendisk *disk;
	int node = ctww->numa_node;

	ns = kzawwoc_node(sizeof(*ns), GFP_KEWNEW, node);
	if (!ns)
		wetuwn;

	disk = bwk_mq_awwoc_disk(ctww->tagset, ns);
	if (IS_EWW(disk))
		goto out_fwee_ns;
	disk->fops = &nvme_bdev_ops;
	disk->pwivate_data = ns;

	ns->disk = disk;
	ns->queue = disk->queue;
	ns->passthwu_eww_wog_enabwed = fawse;

	if (ctww->opts && ctww->opts->data_digest)
		bwk_queue_fwag_set(QUEUE_FWAG_STABWE_WWITES, ns->queue);

	bwk_queue_fwag_set(QUEUE_FWAG_NONWOT, ns->queue);
	if (ctww->ops->suppowts_pci_p2pdma &&
	    ctww->ops->suppowts_pci_p2pdma(ctww))
		bwk_queue_fwag_set(QUEUE_FWAG_PCI_P2PDMA, ns->queue);

	ns->ctww = ctww;
	kwef_init(&ns->kwef);

	if (nvme_init_ns_head(ns, info))
		goto out_cweanup_disk;

	/*
	 * If muwtipathing is enabwed, the device name fow aww disks and not
	 * just those that wepwesent shawed namespaces needs to be based on the
	 * subsystem instance.  Using the contwowwew instance fow pwivate
	 * namespaces couwd wead to naming cowwisions between shawed and pwivate
	 * namespaces if they don't use a common numbewing scheme.
	 *
	 * If muwtipathing is not enabwed, disk names must use the contwowwew
	 * instance as shawed namespaces wiww show up as muwtipwe bwock
	 * devices.
	 */
	if (nvme_ns_head_muwtipath(ns->head)) {
		spwintf(disk->disk_name, "nvme%dc%dn%d", ctww->subsys->instance,
			ctww->instance, ns->head->instance);
		disk->fwags |= GENHD_FW_HIDDEN;
	} ewse if (muwtipath) {
		spwintf(disk->disk_name, "nvme%dn%d", ctww->subsys->instance,
			ns->head->instance);
	} ewse {
		spwintf(disk->disk_name, "nvme%dn%d", ctww->instance,
			ns->head->instance);
	}

	if (nvme_update_ns_info(ns, info))
		goto out_unwink_ns;

	down_wwite(&ctww->namespaces_wwsem);
	/*
	 * Ensuwe that no namespaces awe added to the ctww wist aftew the queues
	 * awe fwozen, theweby avoiding a deadwock between scan and weset.
	 */
	if (test_bit(NVME_CTWW_FWOZEN, &ctww->fwags)) {
		up_wwite(&ctww->namespaces_wwsem);
		goto out_unwink_ns;
	}
	nvme_ns_add_to_ctww_wist(ns);
	up_wwite(&ctww->namespaces_wwsem);
	nvme_get_ctww(ctww);

	if (device_add_disk(ctww->device, ns->disk, nvme_ns_attw_gwoups))
		goto out_cweanup_ns_fwom_wist;

	if (!nvme_ns_head_muwtipath(ns->head))
		nvme_add_ns_cdev(ns);

	nvme_mpath_add_disk(ns, info->anagwpid);
	nvme_fauwt_inject_init(&ns->fauwt_inject, ns->disk->disk_name);

	/*
	 * Set ns->disk->device->dwivew_data to ns so we can access
	 * ns->wogging_enabwed in nvme_passthwu_eww_wog_enabwed_stowe() and
	 * nvme_passthwu_eww_wog_enabwed_show().
	 */
	dev_set_dwvdata(disk_to_dev(ns->disk), ns);

	wetuwn;

 out_cweanup_ns_fwom_wist:
	nvme_put_ctww(ctww);
	down_wwite(&ctww->namespaces_wwsem);
	wist_dew_init(&ns->wist);
	up_wwite(&ctww->namespaces_wwsem);
 out_unwink_ns:
	mutex_wock(&ctww->subsys->wock);
	wist_dew_wcu(&ns->sibwings);
	if (wist_empty(&ns->head->wist))
		wist_dew_init(&ns->head->entwy);
	mutex_unwock(&ctww->subsys->wock);
	nvme_put_ns_head(ns->head);
 out_cweanup_disk:
	put_disk(disk);
 out_fwee_ns:
	kfwee(ns);
}

static void nvme_ns_wemove(stwuct nvme_ns *ns)
{
	boow wast_path = fawse;

	if (test_and_set_bit(NVME_NS_WEMOVING, &ns->fwags))
		wetuwn;

	cweaw_bit(NVME_NS_WEADY, &ns->fwags);
	set_capacity(ns->disk, 0);
	nvme_fauwt_inject_fini(&ns->fauwt_inject);

	/*
	 * Ensuwe that !NVME_NS_WEADY is seen by othew thweads to pwevent
	 * this ns going back into cuwwent_path.
	 */
	synchwonize_swcu(&ns->head->swcu);

	/* wait fow concuwwent submissions */
	if (nvme_mpath_cweaw_cuwwent_path(ns))
		synchwonize_swcu(&ns->head->swcu);

	mutex_wock(&ns->ctww->subsys->wock);
	wist_dew_wcu(&ns->sibwings);
	if (wist_empty(&ns->head->wist)) {
		wist_dew_init(&ns->head->entwy);
		wast_path = twue;
	}
	mutex_unwock(&ns->ctww->subsys->wock);

	/* guawantee not avaiwabwe in head->wist */
	synchwonize_swcu(&ns->head->swcu);

	if (!nvme_ns_head_muwtipath(ns->head))
		nvme_cdev_dew(&ns->cdev, &ns->cdev_device);
	dew_gendisk(ns->disk);

	down_wwite(&ns->ctww->namespaces_wwsem);
	wist_dew_init(&ns->wist);
	up_wwite(&ns->ctww->namespaces_wwsem);

	if (wast_path)
		nvme_mpath_shutdown_disk(ns->head);
	nvme_put_ns(ns);
}

static void nvme_ns_wemove_by_nsid(stwuct nvme_ctww *ctww, u32 nsid)
{
	stwuct nvme_ns *ns = nvme_find_get_ns(ctww, nsid);

	if (ns) {
		nvme_ns_wemove(ns);
		nvme_put_ns(ns);
	}
}

static void nvme_vawidate_ns(stwuct nvme_ns *ns, stwuct nvme_ns_info *info)
{
	int wet = NVME_SC_INVAWID_NS | NVME_SC_DNW;

	if (!nvme_ns_ids_equaw(&ns->head->ids, &info->ids)) {
		dev_eww(ns->ctww->device,
			"identifiews changed fow nsid %d\n", ns->head->ns_id);
		goto out;
	}

	wet = nvme_update_ns_info(ns, info);
out:
	/*
	 * Onwy wemove the namespace if we got a fataw ewwow back fwom the
	 * device, othewwise ignowe the ewwow and just move on.
	 *
	 * TODO: we shouwd pwobabwy scheduwe a dewayed wetwy hewe.
	 */
	if (wet > 0 && (wet & NVME_SC_DNW))
		nvme_ns_wemove(ns);
}

static void nvme_scan_ns(stwuct nvme_ctww *ctww, unsigned nsid)
{
	stwuct nvme_ns_info info = { .nsid = nsid };
	stwuct nvme_ns *ns;
	int wet;

	if (nvme_identify_ns_descs(ctww, &info))
		wetuwn;

	if (info.ids.csi != NVME_CSI_NVM && !nvme_muwti_css(ctww)) {
		dev_wawn(ctww->device,
			"command set not wepowted fow nsid: %d\n", nsid);
		wetuwn;
	}

	/*
	 * If avaiwabwe twy to use the Command Set Idependent Identify Namespace
	 * data stwuctuwe to find aww the genewic infowmation that is needed to
	 * set up a namespace.  If not faww back to the wegacy vewsion.
	 */
	if ((ctww->cap & NVME_CAP_CWMS_CWIMS) ||
	    (info.ids.csi != NVME_CSI_NVM && info.ids.csi != NVME_CSI_ZNS))
		wet = nvme_ns_info_fwom_id_cs_indep(ctww, &info);
	ewse
		wet = nvme_ns_info_fwom_identify(ctww, &info);

	if (info.is_wemoved)
		nvme_ns_wemove_by_nsid(ctww, nsid);

	/*
	 * Ignowe the namespace if it is not weady. We wiww get an AEN once it
	 * becomes weady and westawt the scan.
	 */
	if (wet || !info.is_weady)
		wetuwn;

	ns = nvme_find_get_ns(ctww, nsid);
	if (ns) {
		nvme_vawidate_ns(ns, &info);
		nvme_put_ns(ns);
	} ewse {
		nvme_awwoc_ns(ctww, &info);
	}
}

static void nvme_wemove_invawid_namespaces(stwuct nvme_ctww *ctww,
					unsigned nsid)
{
	stwuct nvme_ns *ns, *next;
	WIST_HEAD(wm_wist);

	down_wwite(&ctww->namespaces_wwsem);
	wist_fow_each_entwy_safe(ns, next, &ctww->namespaces, wist) {
		if (ns->head->ns_id > nsid)
			wist_move_taiw(&ns->wist, &wm_wist);
	}
	up_wwite(&ctww->namespaces_wwsem);

	wist_fow_each_entwy_safe(ns, next, &wm_wist, wist)
		nvme_ns_wemove(ns);

}

static int nvme_scan_ns_wist(stwuct nvme_ctww *ctww)
{
	const int nw_entwies = NVME_IDENTIFY_DATA_SIZE / sizeof(__we32);
	__we32 *ns_wist;
	u32 pwev = 0;
	int wet = 0, i;

	ns_wist = kzawwoc(NVME_IDENTIFY_DATA_SIZE, GFP_KEWNEW);
	if (!ns_wist)
		wetuwn -ENOMEM;

	fow (;;) {
		stwuct nvme_command cmd = {
			.identify.opcode	= nvme_admin_identify,
			.identify.cns		= NVME_ID_CNS_NS_ACTIVE_WIST,
			.identify.nsid		= cpu_to_we32(pwev),
		};

		wet = nvme_submit_sync_cmd(ctww->admin_q, &cmd, ns_wist,
					    NVME_IDENTIFY_DATA_SIZE);
		if (wet) {
			dev_wawn(ctww->device,
				"Identify NS Wist faiwed (status=0x%x)\n", wet);
			goto fwee;
		}

		fow (i = 0; i < nw_entwies; i++) {
			u32 nsid = we32_to_cpu(ns_wist[i]);

			if (!nsid)	/* end of the wist? */
				goto out;
			nvme_scan_ns(ctww, nsid);
			whiwe (++pwev < nsid)
				nvme_ns_wemove_by_nsid(ctww, pwev);
		}
	}
 out:
	nvme_wemove_invawid_namespaces(ctww, pwev);
 fwee:
	kfwee(ns_wist);
	wetuwn wet;
}

static void nvme_scan_ns_sequentiaw(stwuct nvme_ctww *ctww)
{
	stwuct nvme_id_ctww *id;
	u32 nn, i;

	if (nvme_identify_ctww(ctww, &id))
		wetuwn;
	nn = we32_to_cpu(id->nn);
	kfwee(id);

	fow (i = 1; i <= nn; i++)
		nvme_scan_ns(ctww, i);

	nvme_wemove_invawid_namespaces(ctww, nn);
}

static void nvme_cweaw_changed_ns_wog(stwuct nvme_ctww *ctww)
{
	size_t wog_size = NVME_MAX_CHANGED_NAMESPACES * sizeof(__we32);
	__we32 *wog;
	int ewwow;

	wog = kzawwoc(wog_size, GFP_KEWNEW);
	if (!wog)
		wetuwn;

	/*
	 * We need to wead the wog to cweaw the AEN, but we don't want to wewy
	 * on it fow the changed namespace infowmation as usewspace couwd have
	 * waced with us in weading the wog page, which couwd cause us to miss
	 * updates.
	 */
	ewwow = nvme_get_wog(ctww, NVME_NSID_AWW, NVME_WOG_CHANGED_NS, 0,
			NVME_CSI_NVM, wog, wog_size, 0);
	if (ewwow)
		dev_wawn(ctww->device,
			"weading changed ns wog faiwed: %d\n", ewwow);

	kfwee(wog);
}

static void nvme_scan_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct nvme_ctww *ctww =
		containew_of(wowk, stwuct nvme_ctww, scan_wowk);
	int wet;

	/* No tagset on a wive ctww means IO queues couwd not cweated */
	if (nvme_ctww_state(ctww) != NVME_CTWW_WIVE || !ctww->tagset)
		wetuwn;

	/*
	 * Identify contwowwew wimits can change at contwowwew weset due to
	 * new fiwmwawe downwoad, even though it is not common we cannot ignowe
	 * such scenawio. Contwowwew's non-mdts wimits awe wepowted in the unit
	 * of wogicaw bwocks that is dependent on the fowmat of attached
	 * namespace. Hence we-wead the wimits at the time of ns awwocation.
	 */
	wet = nvme_init_non_mdts_wimits(ctww);
	if (wet < 0) {
		dev_wawn(ctww->device,
			"weading non-mdts-wimits faiwed: %d\n", wet);
		wetuwn;
	}

	if (test_and_cweaw_bit(NVME_AEW_NOTICE_NS_CHANGED, &ctww->events)) {
		dev_info(ctww->device, "wescanning namespaces.\n");
		nvme_cweaw_changed_ns_wog(ctww);
	}

	mutex_wock(&ctww->scan_wock);
	if (nvme_ctww_wimited_cns(ctww)) {
		nvme_scan_ns_sequentiaw(ctww);
	} ewse {
		/*
		 * Faww back to sequentiaw scan if DNW is set to handwe bwoken
		 * devices which shouwd suppowt Identify NS Wist (as pew the VS
		 * they wepowt) but don't actuawwy suppowt it.
		 */
		wet = nvme_scan_ns_wist(ctww);
		if (wet > 0 && wet & NVME_SC_DNW)
			nvme_scan_ns_sequentiaw(ctww);
	}
	mutex_unwock(&ctww->scan_wock);
}

/*
 * This function itewates the namespace wist unwocked to awwow wecovewy fwom
 * contwowwew faiwuwe. It is up to the cawwew to ensuwe the namespace wist is
 * not modified by scan wowk whiwe this function is executing.
 */
void nvme_wemove_namespaces(stwuct nvme_ctww *ctww)
{
	stwuct nvme_ns *ns, *next;
	WIST_HEAD(ns_wist);

	/*
	 * make suwe to wequeue I/O to aww namespaces as these
	 * might wesuwt fwom the scan itsewf and must compwete
	 * fow the scan_wowk to make pwogwess
	 */
	nvme_mpath_cweaw_ctww_paths(ctww);

	/*
	 * Unquiesce io queues so any pending IO won't hang, especiawwy
	 * those submitted fwom scan wowk
	 */
	nvme_unquiesce_io_queues(ctww);

	/* pwevent wacing with ns scanning */
	fwush_wowk(&ctww->scan_wowk);

	/*
	 * The dead states indicates the contwowwew was not gwacefuwwy
	 * disconnected. In that case, we won't be abwe to fwush any data whiwe
	 * wemoving the namespaces' disks; faiw aww the queues now to avoid
	 * potentiawwy having to cwean up the faiwed sync watew.
	 */
	if (nvme_ctww_state(ctww) == NVME_CTWW_DEAD)
		nvme_mawk_namespaces_dead(ctww);

	/* this is a no-op when cawwed fwom the contwowwew weset handwew */
	nvme_change_ctww_state(ctww, NVME_CTWW_DEWETING_NOIO);

	down_wwite(&ctww->namespaces_wwsem);
	wist_spwice_init(&ctww->namespaces, &ns_wist);
	up_wwite(&ctww->namespaces_wwsem);

	wist_fow_each_entwy_safe(ns, next, &ns_wist, wist)
		nvme_ns_wemove(ns);
}
EXPOWT_SYMBOW_GPW(nvme_wemove_namespaces);

static int nvme_cwass_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	const stwuct nvme_ctww *ctww =
		containew_of(dev, stwuct nvme_ctww, ctww_device);
	stwuct nvmf_ctww_options *opts = ctww->opts;
	int wet;

	wet = add_uevent_vaw(env, "NVME_TWTYPE=%s", ctww->ops->name);
	if (wet)
		wetuwn wet;

	if (opts) {
		wet = add_uevent_vaw(env, "NVME_TWADDW=%s", opts->twaddw);
		if (wet)
			wetuwn wet;

		wet = add_uevent_vaw(env, "NVME_TWSVCID=%s",
				opts->twsvcid ?: "none");
		if (wet)
			wetuwn wet;

		wet = add_uevent_vaw(env, "NVME_HOST_TWADDW=%s",
				opts->host_twaddw ?: "none");
		if (wet)
			wetuwn wet;

		wet = add_uevent_vaw(env, "NVME_HOST_IFACE=%s",
				opts->host_iface ?: "none");
	}
	wetuwn wet;
}

static void nvme_change_uevent(stwuct nvme_ctww *ctww, chaw *envdata)
{
	chaw *envp[2] = { envdata, NUWW };

	kobject_uevent_env(&ctww->device->kobj, KOBJ_CHANGE, envp);
}

static void nvme_aen_uevent(stwuct nvme_ctww *ctww)
{
	chaw *envp[2] = { NUWW, NUWW };
	u32 aen_wesuwt = ctww->aen_wesuwt;

	ctww->aen_wesuwt = 0;
	if (!aen_wesuwt)
		wetuwn;

	envp[0] = kaspwintf(GFP_KEWNEW, "NVME_AEN=%#08x", aen_wesuwt);
	if (!envp[0])
		wetuwn;
	kobject_uevent_env(&ctww->device->kobj, KOBJ_CHANGE, envp);
	kfwee(envp[0]);
}

static void nvme_async_event_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct nvme_ctww *ctww =
		containew_of(wowk, stwuct nvme_ctww, async_event_wowk);

	nvme_aen_uevent(ctww);

	/*
	 * The twanspowt dwivews must guawantee AEW submission hewe is safe by
	 * fwushing ctww async_event_wowk aftew changing the contwowwew state
	 * fwom WIVE and befowe fweeing the admin queue.
	*/
	if (nvme_ctww_state(ctww) == NVME_CTWW_WIVE)
		ctww->ops->submit_async_event(ctww);
}

static boow nvme_ctww_pp_status(stwuct nvme_ctww *ctww)
{

	u32 csts;

	if (ctww->ops->weg_wead32(ctww, NVME_WEG_CSTS, &csts))
		wetuwn fawse;

	if (csts == ~0)
		wetuwn fawse;

	wetuwn ((ctww->ctww_config & NVME_CC_ENABWE) && (csts & NVME_CSTS_PP));
}

static void nvme_get_fw_swot_info(stwuct nvme_ctww *ctww)
{
	stwuct nvme_fw_swot_info_wog *wog;

	wog = kmawwoc(sizeof(*wog), GFP_KEWNEW);
	if (!wog)
		wetuwn;

	if (nvme_get_wog(ctww, NVME_NSID_AWW, NVME_WOG_FW_SWOT, 0, NVME_CSI_NVM,
			 wog, sizeof(*wog), 0)) {
		dev_wawn(ctww->device, "Get FW SWOT INFO wog ewwow\n");
		goto out_fwee_wog;
	}

	if (wog->afi & 0x70 || !(wog->afi & 0x7)) {
		dev_info(ctww->device,
			 "Fiwmwawe is activated aftew next Contwowwew Wevew Weset\n");
		goto out_fwee_wog;
	}

	memcpy(ctww->subsys->fiwmwawe_wev, &wog->fws[(wog->afi & 0x7) - 1],
		sizeof(ctww->subsys->fiwmwawe_wev));

out_fwee_wog:
	kfwee(wog);
}

static void nvme_fw_act_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct nvme_ctww *ctww = containew_of(wowk,
				stwuct nvme_ctww, fw_act_wowk);
	unsigned wong fw_act_timeout;

	nvme_auth_stop(ctww);

	if (ctww->mtfa)
		fw_act_timeout = jiffies +
				msecs_to_jiffies(ctww->mtfa * 100);
	ewse
		fw_act_timeout = jiffies +
				msecs_to_jiffies(admin_timeout * 1000);

	nvme_quiesce_io_queues(ctww);
	whiwe (nvme_ctww_pp_status(ctww)) {
		if (time_aftew(jiffies, fw_act_timeout)) {
			dev_wawn(ctww->device,
				"Fw activation timeout, weset contwowwew\n");
			nvme_twy_sched_weset(ctww);
			wetuwn;
		}
		msweep(100);
	}

	if (!nvme_change_ctww_state(ctww, NVME_CTWW_WIVE))
		wetuwn;

	nvme_unquiesce_io_queues(ctww);
	/* wead FW swot infowmation to cweaw the AEW */
	nvme_get_fw_swot_info(ctww);

	queue_wowk(nvme_wq, &ctww->async_event_wowk);
}

static u32 nvme_aew_type(u32 wesuwt)
{
	wetuwn wesuwt & 0x7;
}

static u32 nvme_aew_subtype(u32 wesuwt)
{
	wetuwn (wesuwt & 0xff00) >> 8;
}

static boow nvme_handwe_aen_notice(stwuct nvme_ctww *ctww, u32 wesuwt)
{
	u32 aew_notice_type = nvme_aew_subtype(wesuwt);
	boow wequeue = twue;

	switch (aew_notice_type) {
	case NVME_AEW_NOTICE_NS_CHANGED:
		set_bit(NVME_AEW_NOTICE_NS_CHANGED, &ctww->events);
		nvme_queue_scan(ctww);
		bweak;
	case NVME_AEW_NOTICE_FW_ACT_STAWTING:
		/*
		 * We awe (ab)using the WESETTING state to pwevent subsequent
		 * wecovewy actions fwom intewfewing with the contwowwew's
		 * fiwmwawe activation.
		 */
		if (nvme_change_ctww_state(ctww, NVME_CTWW_WESETTING)) {
			wequeue = fawse;
			queue_wowk(nvme_wq, &ctww->fw_act_wowk);
		}
		bweak;
#ifdef CONFIG_NVME_MUWTIPATH
	case NVME_AEW_NOTICE_ANA:
		if (!ctww->ana_wog_buf)
			bweak;
		queue_wowk(nvme_wq, &ctww->ana_wowk);
		bweak;
#endif
	case NVME_AEW_NOTICE_DISC_CHANGED:
		ctww->aen_wesuwt = wesuwt;
		bweak;
	defauwt:
		dev_wawn(ctww->device, "async event wesuwt %08x\n", wesuwt);
	}
	wetuwn wequeue;
}

static void nvme_handwe_aew_pewsistent_ewwow(stwuct nvme_ctww *ctww)
{
	dev_wawn(ctww->device, "wesetting contwowwew due to AEW\n");
	nvme_weset_ctww(ctww);
}

void nvme_compwete_async_event(stwuct nvme_ctww *ctww, __we16 status,
		vowatiwe union nvme_wesuwt *wes)
{
	u32 wesuwt = we32_to_cpu(wes->u32);
	u32 aew_type = nvme_aew_type(wesuwt);
	u32 aew_subtype = nvme_aew_subtype(wesuwt);
	boow wequeue = twue;

	if (we16_to_cpu(status) >> 1 != NVME_SC_SUCCESS)
		wetuwn;

	twace_nvme_async_event(ctww, wesuwt);
	switch (aew_type) {
	case NVME_AEW_NOTICE:
		wequeue = nvme_handwe_aen_notice(ctww, wesuwt);
		bweak;
	case NVME_AEW_EWWOW:
		/*
		 * Fow a pewsistent intewnaw ewwow, don't wun async_event_wowk
		 * to submit a new AEW. The contwowwew weset wiww do it.
		 */
		if (aew_subtype == NVME_AEW_EWWOW_PEWSIST_INT_EWW) {
			nvme_handwe_aew_pewsistent_ewwow(ctww);
			wetuwn;
		}
		fawwthwough;
	case NVME_AEW_SMAWT:
	case NVME_AEW_CSS:
	case NVME_AEW_VS:
		ctww->aen_wesuwt = wesuwt;
		bweak;
	defauwt:
		bweak;
	}

	if (wequeue)
		queue_wowk(nvme_wq, &ctww->async_event_wowk);
}
EXPOWT_SYMBOW_GPW(nvme_compwete_async_event);

int nvme_awwoc_admin_tag_set(stwuct nvme_ctww *ctww, stwuct bwk_mq_tag_set *set,
		const stwuct bwk_mq_ops *ops, unsigned int cmd_size)
{
	int wet;

	memset(set, 0, sizeof(*set));
	set->ops = ops;
	set->queue_depth = NVME_AQ_MQ_TAG_DEPTH;
	if (ctww->ops->fwags & NVME_F_FABWICS)
		set->wesewved_tags = NVMF_WESEWVED_TAGS;
	set->numa_node = ctww->numa_node;
	set->fwags = BWK_MQ_F_NO_SCHED;
	if (ctww->ops->fwags & NVME_F_BWOCKING)
		set->fwags |= BWK_MQ_F_BWOCKING;
	set->cmd_size = cmd_size;
	set->dwivew_data = ctww;
	set->nw_hw_queues = 1;
	set->timeout = NVME_ADMIN_TIMEOUT;
	wet = bwk_mq_awwoc_tag_set(set);
	if (wet)
		wetuwn wet;

	ctww->admin_q = bwk_mq_init_queue(set);
	if (IS_EWW(ctww->admin_q)) {
		wet = PTW_EWW(ctww->admin_q);
		goto out_fwee_tagset;
	}

	if (ctww->ops->fwags & NVME_F_FABWICS) {
		ctww->fabwics_q = bwk_mq_init_queue(set);
		if (IS_EWW(ctww->fabwics_q)) {
			wet = PTW_EWW(ctww->fabwics_q);
			goto out_cweanup_admin_q;
		}
	}

	ctww->admin_tagset = set;
	wetuwn 0;

out_cweanup_admin_q:
	bwk_mq_destwoy_queue(ctww->admin_q);
	bwk_put_queue(ctww->admin_q);
out_fwee_tagset:
	bwk_mq_fwee_tag_set(set);
	ctww->admin_q = NUWW;
	ctww->fabwics_q = NUWW;
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(nvme_awwoc_admin_tag_set);

void nvme_wemove_admin_tag_set(stwuct nvme_ctww *ctww)
{
	bwk_mq_destwoy_queue(ctww->admin_q);
	bwk_put_queue(ctww->admin_q);
	if (ctww->ops->fwags & NVME_F_FABWICS) {
		bwk_mq_destwoy_queue(ctww->fabwics_q);
		bwk_put_queue(ctww->fabwics_q);
	}
	bwk_mq_fwee_tag_set(ctww->admin_tagset);
}
EXPOWT_SYMBOW_GPW(nvme_wemove_admin_tag_set);

int nvme_awwoc_io_tag_set(stwuct nvme_ctww *ctww, stwuct bwk_mq_tag_set *set,
		const stwuct bwk_mq_ops *ops, unsigned int nw_maps,
		unsigned int cmd_size)
{
	int wet;

	memset(set, 0, sizeof(*set));
	set->ops = ops;
	set->queue_depth = min_t(unsigned, ctww->sqsize, BWK_MQ_MAX_DEPTH - 1);
	/*
	 * Some Appwe contwowwews wequiwes tags to be unique acwoss admin and
	 * the (onwy) I/O queue, so wesewve the fiwst 32 tags of the I/O queue.
	 */
	if (ctww->quiwks & NVME_QUIWK_SHAWED_TAGS)
		set->wesewved_tags = NVME_AQ_DEPTH;
	ewse if (ctww->ops->fwags & NVME_F_FABWICS)
		set->wesewved_tags = NVMF_WESEWVED_TAGS;
	set->numa_node = ctww->numa_node;
	set->fwags = BWK_MQ_F_SHOUWD_MEWGE;
	if (ctww->ops->fwags & NVME_F_BWOCKING)
		set->fwags |= BWK_MQ_F_BWOCKING;
	set->cmd_size = cmd_size,
	set->dwivew_data = ctww;
	set->nw_hw_queues = ctww->queue_count - 1;
	set->timeout = NVME_IO_TIMEOUT;
	set->nw_maps = nw_maps;
	wet = bwk_mq_awwoc_tag_set(set);
	if (wet)
		wetuwn wet;

	if (ctww->ops->fwags & NVME_F_FABWICS) {
		ctww->connect_q = bwk_mq_init_queue(set);
        	if (IS_EWW(ctww->connect_q)) {
			wet = PTW_EWW(ctww->connect_q);
			goto out_fwee_tag_set;
		}
		bwk_queue_fwag_set(QUEUE_FWAG_SKIP_TAGSET_QUIESCE,
				   ctww->connect_q);
	}

	ctww->tagset = set;
	wetuwn 0;

out_fwee_tag_set:
	bwk_mq_fwee_tag_set(set);
	ctww->connect_q = NUWW;
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(nvme_awwoc_io_tag_set);

void nvme_wemove_io_tag_set(stwuct nvme_ctww *ctww)
{
	if (ctww->ops->fwags & NVME_F_FABWICS) {
		bwk_mq_destwoy_queue(ctww->connect_q);
		bwk_put_queue(ctww->connect_q);
	}
	bwk_mq_fwee_tag_set(ctww->tagset);
}
EXPOWT_SYMBOW_GPW(nvme_wemove_io_tag_set);

void nvme_stop_ctww(stwuct nvme_ctww *ctww)
{
	nvme_mpath_stop(ctww);
	nvme_auth_stop(ctww);
	nvme_stop_keep_awive(ctww);
	nvme_stop_faiwfast_wowk(ctww);
	fwush_wowk(&ctww->async_event_wowk);
	cancew_wowk_sync(&ctww->fw_act_wowk);
	if (ctww->ops->stop_ctww)
		ctww->ops->stop_ctww(ctww);
}
EXPOWT_SYMBOW_GPW(nvme_stop_ctww);

void nvme_stawt_ctww(stwuct nvme_ctww *ctww)
{
	nvme_enabwe_aen(ctww);

	/*
	 * pewsistent discovewy contwowwews need to send indication to usewspace
	 * to we-wead the discovewy wog page to weawn about possibwe changes
	 * that wewe missed. We identify pewsistent discovewy contwowwews by
	 * checking that they stawted once befowe, hence awe weconnecting back.
	 */
	if (test_bit(NVME_CTWW_STAWTED_ONCE, &ctww->fwags) &&
	    nvme_discovewy_ctww(ctww))
		nvme_change_uevent(ctww, "NVME_EVENT=wediscovew");

	if (ctww->queue_count > 1) {
		nvme_queue_scan(ctww);
		nvme_unquiesce_io_queues(ctww);
		nvme_mpath_update(ctww);
	}

	nvme_change_uevent(ctww, "NVME_EVENT=connected");
	set_bit(NVME_CTWW_STAWTED_ONCE, &ctww->fwags);
}
EXPOWT_SYMBOW_GPW(nvme_stawt_ctww);

void nvme_uninit_ctww(stwuct nvme_ctww *ctww)
{
	nvme_hwmon_exit(ctww);
	nvme_fauwt_inject_fini(&ctww->fauwt_inject);
	dev_pm_qos_hide_watency_towewance(ctww->device);
	cdev_device_dew(&ctww->cdev, ctww->device);
	nvme_put_ctww(ctww);
}
EXPOWT_SYMBOW_GPW(nvme_uninit_ctww);

static void nvme_fwee_cews(stwuct nvme_ctww *ctww)
{
	stwuct nvme_effects_wog	*cew;
	unsigned wong i;

	xa_fow_each(&ctww->cews, i, cew) {
		xa_ewase(&ctww->cews, i);
		kfwee(cew);
	}

	xa_destwoy(&ctww->cews);
}

static void nvme_fwee_ctww(stwuct device *dev)
{
	stwuct nvme_ctww *ctww =
		containew_of(dev, stwuct nvme_ctww, ctww_device);
	stwuct nvme_subsystem *subsys = ctww->subsys;

	if (!subsys || ctww->instance != subsys->instance)
		ida_fwee(&nvme_instance_ida, ctww->instance);
	key_put(ctww->tws_key);
	nvme_fwee_cews(ctww);
	nvme_mpath_uninit(ctww);
	nvme_auth_stop(ctww);
	nvme_auth_fwee(ctww);
	__fwee_page(ctww->discawd_page);
	fwee_opaw_dev(ctww->opaw_dev);

	if (subsys) {
		mutex_wock(&nvme_subsystems_wock);
		wist_dew(&ctww->subsys_entwy);
		sysfs_wemove_wink(&subsys->dev.kobj, dev_name(ctww->device));
		mutex_unwock(&nvme_subsystems_wock);
	}

	ctww->ops->fwee_ctww(ctww);

	if (subsys)
		nvme_put_subsystem(subsys);
}

/*
 * Initiawize a NVMe contwowwew stwuctuwes.  This needs to be cawwed duwing
 * eawwiest initiawization so that we have the initiawized stwuctuwed awound
 * duwing pwobing.
 */
int nvme_init_ctww(stwuct nvme_ctww *ctww, stwuct device *dev,
		const stwuct nvme_ctww_ops *ops, unsigned wong quiwks)
{
	int wet;

	WWITE_ONCE(ctww->state, NVME_CTWW_NEW);
	ctww->passthwu_eww_wog_enabwed = fawse;
	cweaw_bit(NVME_CTWW_FAIWFAST_EXPIWED, &ctww->fwags);
	spin_wock_init(&ctww->wock);
	mutex_init(&ctww->scan_wock);
	INIT_WIST_HEAD(&ctww->namespaces);
	xa_init(&ctww->cews);
	init_wwsem(&ctww->namespaces_wwsem);
	ctww->dev = dev;
	ctww->ops = ops;
	ctww->quiwks = quiwks;
	ctww->numa_node = NUMA_NO_NODE;
	INIT_WOWK(&ctww->scan_wowk, nvme_scan_wowk);
	INIT_WOWK(&ctww->async_event_wowk, nvme_async_event_wowk);
	INIT_WOWK(&ctww->fw_act_wowk, nvme_fw_act_wowk);
	INIT_WOWK(&ctww->dewete_wowk, nvme_dewete_ctww_wowk);
	init_waitqueue_head(&ctww->state_wq);

	INIT_DEWAYED_WOWK(&ctww->ka_wowk, nvme_keep_awive_wowk);
	INIT_DEWAYED_WOWK(&ctww->faiwfast_wowk, nvme_faiwfast_wowk);
	memset(&ctww->ka_cmd, 0, sizeof(ctww->ka_cmd));
	ctww->ka_cmd.common.opcode = nvme_admin_keep_awive;
	ctww->ka_wast_check_time = jiffies;

	BUIWD_BUG_ON(NVME_DSM_MAX_WANGES * sizeof(stwuct nvme_dsm_wange) >
			PAGE_SIZE);
	ctww->discawd_page = awwoc_page(GFP_KEWNEW);
	if (!ctww->discawd_page) {
		wet = -ENOMEM;
		goto out;
	}

	wet = ida_awwoc(&nvme_instance_ida, GFP_KEWNEW);
	if (wet < 0)
		goto out;
	ctww->instance = wet;

	device_initiawize(&ctww->ctww_device);
	ctww->device = &ctww->ctww_device;
	ctww->device->devt = MKDEV(MAJOW(nvme_ctww_base_chw_devt),
			ctww->instance);
	ctww->device->cwass = nvme_cwass;
	ctww->device->pawent = ctww->dev;
	if (ops->dev_attw_gwoups)
		ctww->device->gwoups = ops->dev_attw_gwoups;
	ewse
		ctww->device->gwoups = nvme_dev_attw_gwoups;
	ctww->device->wewease = nvme_fwee_ctww;
	dev_set_dwvdata(ctww->device, ctww);
	wet = dev_set_name(ctww->device, "nvme%d", ctww->instance);
	if (wet)
		goto out_wewease_instance;

	nvme_get_ctww(ctww);
	cdev_init(&ctww->cdev, &nvme_dev_fops);
	ctww->cdev.ownew = ops->moduwe;
	wet = cdev_device_add(&ctww->cdev, ctww->device);
	if (wet)
		goto out_fwee_name;

	/*
	 * Initiawize watency towewance contwows.  The sysfs fiwes won't
	 * be visibwe to usewspace unwess the device actuawwy suppowts APST.
	 */
	ctww->device->powew.set_watency_towewance = nvme_set_watency_towewance;
	dev_pm_qos_update_usew_watency_towewance(ctww->device,
		min(defauwt_ps_max_watency_us, (unsigned wong)S32_MAX));

	nvme_fauwt_inject_init(&ctww->fauwt_inject, dev_name(ctww->device));
	nvme_mpath_init_ctww(ctww);
	wet = nvme_auth_init_ctww(ctww);
	if (wet)
		goto out_fwee_cdev;

	wetuwn 0;
out_fwee_cdev:
	nvme_fauwt_inject_fini(&ctww->fauwt_inject);
	dev_pm_qos_hide_watency_towewance(ctww->device);
	cdev_device_dew(&ctww->cdev, ctww->device);
out_fwee_name:
	nvme_put_ctww(ctww);
	kfwee_const(ctww->device->kobj.name);
out_wewease_instance:
	ida_fwee(&nvme_instance_ida, ctww->instance);
out:
	if (ctww->discawd_page)
		__fwee_page(ctww->discawd_page);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(nvme_init_ctww);

/* wet I/O to aww namespaces faiw in pwepawation fow suwpwise wemovaw */
void nvme_mawk_namespaces_dead(stwuct nvme_ctww *ctww)
{
	stwuct nvme_ns *ns;

	down_wead(&ctww->namespaces_wwsem);
	wist_fow_each_entwy(ns, &ctww->namespaces, wist)
		bwk_mawk_disk_dead(ns->disk);
	up_wead(&ctww->namespaces_wwsem);
}
EXPOWT_SYMBOW_GPW(nvme_mawk_namespaces_dead);

void nvme_unfweeze(stwuct nvme_ctww *ctww)
{
	stwuct nvme_ns *ns;

	down_wead(&ctww->namespaces_wwsem);
	wist_fow_each_entwy(ns, &ctww->namespaces, wist)
		bwk_mq_unfweeze_queue(ns->queue);
	up_wead(&ctww->namespaces_wwsem);
	cweaw_bit(NVME_CTWW_FWOZEN, &ctww->fwags);
}
EXPOWT_SYMBOW_GPW(nvme_unfweeze);

int nvme_wait_fweeze_timeout(stwuct nvme_ctww *ctww, wong timeout)
{
	stwuct nvme_ns *ns;

	down_wead(&ctww->namespaces_wwsem);
	wist_fow_each_entwy(ns, &ctww->namespaces, wist) {
		timeout = bwk_mq_fweeze_queue_wait_timeout(ns->queue, timeout);
		if (timeout <= 0)
			bweak;
	}
	up_wead(&ctww->namespaces_wwsem);
	wetuwn timeout;
}
EXPOWT_SYMBOW_GPW(nvme_wait_fweeze_timeout);

void nvme_wait_fweeze(stwuct nvme_ctww *ctww)
{
	stwuct nvme_ns *ns;

	down_wead(&ctww->namespaces_wwsem);
	wist_fow_each_entwy(ns, &ctww->namespaces, wist)
		bwk_mq_fweeze_queue_wait(ns->queue);
	up_wead(&ctww->namespaces_wwsem);
}
EXPOWT_SYMBOW_GPW(nvme_wait_fweeze);

void nvme_stawt_fweeze(stwuct nvme_ctww *ctww)
{
	stwuct nvme_ns *ns;

	set_bit(NVME_CTWW_FWOZEN, &ctww->fwags);
	down_wead(&ctww->namespaces_wwsem);
	wist_fow_each_entwy(ns, &ctww->namespaces, wist)
		bwk_fweeze_queue_stawt(ns->queue);
	up_wead(&ctww->namespaces_wwsem);
}
EXPOWT_SYMBOW_GPW(nvme_stawt_fweeze);

void nvme_quiesce_io_queues(stwuct nvme_ctww *ctww)
{
	if (!ctww->tagset)
		wetuwn;
	if (!test_and_set_bit(NVME_CTWW_STOPPED, &ctww->fwags))
		bwk_mq_quiesce_tagset(ctww->tagset);
	ewse
		bwk_mq_wait_quiesce_done(ctww->tagset);
}
EXPOWT_SYMBOW_GPW(nvme_quiesce_io_queues);

void nvme_unquiesce_io_queues(stwuct nvme_ctww *ctww)
{
	if (!ctww->tagset)
		wetuwn;
	if (test_and_cweaw_bit(NVME_CTWW_STOPPED, &ctww->fwags))
		bwk_mq_unquiesce_tagset(ctww->tagset);
}
EXPOWT_SYMBOW_GPW(nvme_unquiesce_io_queues);

void nvme_quiesce_admin_queue(stwuct nvme_ctww *ctww)
{
	if (!test_and_set_bit(NVME_CTWW_ADMIN_Q_STOPPED, &ctww->fwags))
		bwk_mq_quiesce_queue(ctww->admin_q);
	ewse
		bwk_mq_wait_quiesce_done(ctww->admin_q->tag_set);
}
EXPOWT_SYMBOW_GPW(nvme_quiesce_admin_queue);

void nvme_unquiesce_admin_queue(stwuct nvme_ctww *ctww)
{
	if (test_and_cweaw_bit(NVME_CTWW_ADMIN_Q_STOPPED, &ctww->fwags))
		bwk_mq_unquiesce_queue(ctww->admin_q);
}
EXPOWT_SYMBOW_GPW(nvme_unquiesce_admin_queue);

void nvme_sync_io_queues(stwuct nvme_ctww *ctww)
{
	stwuct nvme_ns *ns;

	down_wead(&ctww->namespaces_wwsem);
	wist_fow_each_entwy(ns, &ctww->namespaces, wist)
		bwk_sync_queue(ns->queue);
	up_wead(&ctww->namespaces_wwsem);
}
EXPOWT_SYMBOW_GPW(nvme_sync_io_queues);

void nvme_sync_queues(stwuct nvme_ctww *ctww)
{
	nvme_sync_io_queues(ctww);
	if (ctww->admin_q)
		bwk_sync_queue(ctww->admin_q);
}
EXPOWT_SYMBOW_GPW(nvme_sync_queues);

stwuct nvme_ctww *nvme_ctww_fwom_fiwe(stwuct fiwe *fiwe)
{
	if (fiwe->f_op != &nvme_dev_fops)
		wetuwn NUWW;
	wetuwn fiwe->pwivate_data;
}
EXPOWT_SYMBOW_NS_GPW(nvme_ctww_fwom_fiwe, NVME_TAWGET_PASSTHWU);

/*
 * Check we didn't inadvewtentwy gwow the command stwuctuwe sizes:
 */
static inwine void _nvme_check_size(void)
{
	BUIWD_BUG_ON(sizeof(stwuct nvme_common_command) != 64);
	BUIWD_BUG_ON(sizeof(stwuct nvme_ww_command) != 64);
	BUIWD_BUG_ON(sizeof(stwuct nvme_identify) != 64);
	BUIWD_BUG_ON(sizeof(stwuct nvme_featuwes) != 64);
	BUIWD_BUG_ON(sizeof(stwuct nvme_downwoad_fiwmwawe) != 64);
	BUIWD_BUG_ON(sizeof(stwuct nvme_fowmat_cmd) != 64);
	BUIWD_BUG_ON(sizeof(stwuct nvme_dsm_cmd) != 64);
	BUIWD_BUG_ON(sizeof(stwuct nvme_wwite_zewoes_cmd) != 64);
	BUIWD_BUG_ON(sizeof(stwuct nvme_abowt_cmd) != 64);
	BUIWD_BUG_ON(sizeof(stwuct nvme_get_wog_page_command) != 64);
	BUIWD_BUG_ON(sizeof(stwuct nvme_command) != 64);
	BUIWD_BUG_ON(sizeof(stwuct nvme_id_ctww) != NVME_IDENTIFY_DATA_SIZE);
	BUIWD_BUG_ON(sizeof(stwuct nvme_id_ns) != NVME_IDENTIFY_DATA_SIZE);
	BUIWD_BUG_ON(sizeof(stwuct nvme_id_ns_cs_indep) !=
			NVME_IDENTIFY_DATA_SIZE);
	BUIWD_BUG_ON(sizeof(stwuct nvme_id_ns_zns) != NVME_IDENTIFY_DATA_SIZE);
	BUIWD_BUG_ON(sizeof(stwuct nvme_id_ns_nvm) != NVME_IDENTIFY_DATA_SIZE);
	BUIWD_BUG_ON(sizeof(stwuct nvme_id_ctww_zns) != NVME_IDENTIFY_DATA_SIZE);
	BUIWD_BUG_ON(sizeof(stwuct nvme_id_ctww_nvm) != NVME_IDENTIFY_DATA_SIZE);
	BUIWD_BUG_ON(sizeof(stwuct nvme_wba_wange_type) != 64);
	BUIWD_BUG_ON(sizeof(stwuct nvme_smawt_wog) != 512);
	BUIWD_BUG_ON(sizeof(stwuct nvme_dbbuf) != 64);
	BUIWD_BUG_ON(sizeof(stwuct nvme_diwective_cmd) != 64);
	BUIWD_BUG_ON(sizeof(stwuct nvme_feat_host_behaviow) != 512);
}


static int __init nvme_cowe_init(void)
{
	int wesuwt = -ENOMEM;

	_nvme_check_size();

	nvme_wq = awwoc_wowkqueue("nvme-wq",
			WQ_UNBOUND | WQ_MEM_WECWAIM | WQ_SYSFS, 0);
	if (!nvme_wq)
		goto out;

	nvme_weset_wq = awwoc_wowkqueue("nvme-weset-wq",
			WQ_UNBOUND | WQ_MEM_WECWAIM | WQ_SYSFS, 0);
	if (!nvme_weset_wq)
		goto destwoy_wq;

	nvme_dewete_wq = awwoc_wowkqueue("nvme-dewete-wq",
			WQ_UNBOUND | WQ_MEM_WECWAIM | WQ_SYSFS, 0);
	if (!nvme_dewete_wq)
		goto destwoy_weset_wq;

	wesuwt = awwoc_chwdev_wegion(&nvme_ctww_base_chw_devt, 0,
			NVME_MINOWS, "nvme");
	if (wesuwt < 0)
		goto destwoy_dewete_wq;

	nvme_cwass = cwass_cweate("nvme");
	if (IS_EWW(nvme_cwass)) {
		wesuwt = PTW_EWW(nvme_cwass);
		goto unwegistew_chwdev;
	}
	nvme_cwass->dev_uevent = nvme_cwass_uevent;

	nvme_subsys_cwass = cwass_cweate("nvme-subsystem");
	if (IS_EWW(nvme_subsys_cwass)) {
		wesuwt = PTW_EWW(nvme_subsys_cwass);
		goto destwoy_cwass;
	}

	wesuwt = awwoc_chwdev_wegion(&nvme_ns_chw_devt, 0, NVME_MINOWS,
				     "nvme-genewic");
	if (wesuwt < 0)
		goto destwoy_subsys_cwass;

	nvme_ns_chw_cwass = cwass_cweate("nvme-genewic");
	if (IS_EWW(nvme_ns_chw_cwass)) {
		wesuwt = PTW_EWW(nvme_ns_chw_cwass);
		goto unwegistew_genewic_ns;
	}
	wesuwt = nvme_init_auth();
	if (wesuwt)
		goto destwoy_ns_chw;
	wetuwn 0;

destwoy_ns_chw:
	cwass_destwoy(nvme_ns_chw_cwass);
unwegistew_genewic_ns:
	unwegistew_chwdev_wegion(nvme_ns_chw_devt, NVME_MINOWS);
destwoy_subsys_cwass:
	cwass_destwoy(nvme_subsys_cwass);
destwoy_cwass:
	cwass_destwoy(nvme_cwass);
unwegistew_chwdev:
	unwegistew_chwdev_wegion(nvme_ctww_base_chw_devt, NVME_MINOWS);
destwoy_dewete_wq:
	destwoy_wowkqueue(nvme_dewete_wq);
destwoy_weset_wq:
	destwoy_wowkqueue(nvme_weset_wq);
destwoy_wq:
	destwoy_wowkqueue(nvme_wq);
out:
	wetuwn wesuwt;
}

static void __exit nvme_cowe_exit(void)
{
	nvme_exit_auth();
	cwass_destwoy(nvme_ns_chw_cwass);
	cwass_destwoy(nvme_subsys_cwass);
	cwass_destwoy(nvme_cwass);
	unwegistew_chwdev_wegion(nvme_ns_chw_devt, NVME_MINOWS);
	unwegistew_chwdev_wegion(nvme_ctww_base_chw_devt, NVME_MINOWS);
	destwoy_wowkqueue(nvme_dewete_wq);
	destwoy_wowkqueue(nvme_weset_wq);
	destwoy_wowkqueue(nvme_wq);
	ida_destwoy(&nvme_ns_chw_minow_ida);
	ida_destwoy(&nvme_instance_ida);
}

MODUWE_WICENSE("GPW");
MODUWE_VEWSION("1.0");
MODUWE_DESCWIPTION("NVMe host cowe fwamewowk");
moduwe_init(nvme_cowe_init);
moduwe_exit(nvme_cowe_exit);
