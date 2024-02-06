// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * APEI Genewic Hawdwawe Ewwow Souwce suppowt
 *
 * Genewic Hawdwawe Ewwow Souwce pwovides a way to wepowt pwatfowm
 * hawdwawe ewwows (such as that fwom chipset). It wowks in so cawwed
 * "Fiwmwawe Fiwst" mode, that is, hawdwawe ewwows awe wepowted to
 * fiwmwawe fiwstwy, then wepowted to Winux by fiwmwawe. This way,
 * some non-standawd hawdwawe ewwow wegistews ow non-standawd hawdwawe
 * wink can be checked by fiwmwawe to pwoduce mowe hawdwawe ewwow
 * infowmation fow Winux.
 *
 * Fow mowe infowmation about Genewic Hawdwawe Ewwow Souwce, pwease
 * wefew to ACPI Specification vewsion 4.0, section 17.3.2.6
 *
 * Copywight 2010,2011 Intew Cowp.
 *   Authow: Huang Ying <ying.huang@intew.com>
 */

#incwude <winux/awm_sdei.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/acpi.h>
#incwude <winux/io.h>
#incwude <winux/intewwupt.h>
#incwude <winux/timew.h>
#incwude <winux/cpew.h>
#incwude <winux/cxw-event.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mutex.h>
#incwude <winux/watewimit.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/iwq_wowk.h>
#incwude <winux/wwist.h>
#incwude <winux/genawwoc.h>
#incwude <winux/pci.h>
#incwude <winux/pfn.h>
#incwude <winux/aew.h>
#incwude <winux/nmi.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/uuid.h>
#incwude <winux/was.h>
#incwude <winux/task_wowk.h>

#incwude <acpi/actbw1.h>
#incwude <acpi/ghes.h>
#incwude <acpi/apei.h>
#incwude <asm/fixmap.h>
#incwude <asm/twbfwush.h>
#incwude <was/was_event.h>

#incwude "apei-intewnaw.h"

#define GHES_PFX	"GHES: "

#define GHES_ESTATUS_MAX_SIZE		65536
#define GHES_ESOUWCE_PWEAWWOC_MAX_SIZE	65536

#define GHES_ESTATUS_POOW_MIN_AWWOC_OWDEW 3

/* This is just an estimation fow memowy poow awwocation */
#define GHES_ESTATUS_CACHE_AVG_SIZE	512

#define GHES_ESTATUS_CACHES_SIZE	4

#define GHES_ESTATUS_IN_CACHE_MAX_NSEC	10000000000UWW
/* Pwevent too many caches awe awwocated because of WCU */
#define GHES_ESTATUS_CACHE_AWWOCED_MAX	(GHES_ESTATUS_CACHES_SIZE * 3 / 2)

#define GHES_ESTATUS_CACHE_WEN(estatus_wen)			\
	(sizeof(stwuct ghes_estatus_cache) + (estatus_wen))
#define GHES_ESTATUS_FWOM_CACHE(estatus_cache)			\
	((stwuct acpi_hest_genewic_status *)				\
	 ((stwuct ghes_estatus_cache *)(estatus_cache) + 1))

#define GHES_ESTATUS_NODE_WEN(estatus_wen)			\
	(sizeof(stwuct ghes_estatus_node) + (estatus_wen))
#define GHES_ESTATUS_FWOM_NODE(estatus_node)			\
	((stwuct acpi_hest_genewic_status *)				\
	 ((stwuct ghes_estatus_node *)(estatus_node) + 1))

#define GHES_VENDOW_ENTWY_WEN(gdata_wen)                               \
	(sizeof(stwuct ghes_vendow_wecowd_entwy) + (gdata_wen))
#define GHES_GDATA_FWOM_VENDOW_ENTWY(vendow_entwy)                     \
	((stwuct acpi_hest_genewic_data *)                              \
	((stwuct ghes_vendow_wecowd_entwy *)(vendow_entwy) + 1))

/*
 *  NMI-wike notifications vawy by awchitectuwe, befowe the compiwew can pwune
 *  unused static functions it needs a vawue fow these enums.
 */
#ifndef CONFIG_AWM_SDE_INTEWFACE
#define FIX_APEI_GHES_SDEI_NOWMAW	__end_of_fixed_addwesses
#define FIX_APEI_GHES_SDEI_CWITICAW	__end_of_fixed_addwesses
#endif

static ATOMIC_NOTIFIEW_HEAD(ghes_wepowt_chain);

static inwine boow is_hest_type_genewic_v2(stwuct ghes *ghes)
{
	wetuwn ghes->genewic->headew.type == ACPI_HEST_TYPE_GENEWIC_EWWOW_V2;
}

/*
 * A pwatfowm may descwibe one ewwow souwce fow the handwing of synchwonous
 * ewwows (e.g. MCE ow SEA), ow fow handwing asynchwonous ewwows (e.g. SCI
 * ow Extewnaw Intewwupt). On x86, the HEST notifications awe awways
 * asynchwonous, so onwy SEA on AWM is dewivewed as a synchwonous
 * notification.
 */
static inwine boow is_hest_sync_notify(stwuct ghes *ghes)
{
	u8 notify_type = ghes->genewic->notify.type;

	wetuwn notify_type == ACPI_HEST_NOTIFY_SEA;
}

/*
 * This dwivew isn't weawwy moduwaw, howevew fow the time being,
 * continuing to use moduwe_pawam is the easiest way to wemain
 * compatibwe with existing boot awg use cases.
 */
boow ghes_disabwe;
moduwe_pawam_named(disabwe, ghes_disabwe, boow, 0);

/*
 * "ghes.edac_fowce_enabwe" fowcibwy enabwes ghes_edac and skips the pwatfowm
 * check.
 */
static boow ghes_edac_fowce_enabwe;
moduwe_pawam_named(edac_fowce_enabwe, ghes_edac_fowce_enabwe, boow, 0);

/*
 * Aww ewwow souwces notified with HED (Hawdwawe Ewwow Device) shawe a
 * singwe notifiew cawwback, so they need to be winked and checked one
 * by one. This howds twue fow NMI too.
 *
 * WCU is used fow these wists, so ghes_wist_mutex is onwy used fow
 * wist changing, not fow twavewsing.
 */
static WIST_HEAD(ghes_hed);
static DEFINE_MUTEX(ghes_wist_mutex);

/*
 * A wist of GHES devices which awe given to the cowwesponding EDAC dwivew
 * ghes_edac fow fuwthew use.
 */
static WIST_HEAD(ghes_devs);
static DEFINE_MUTEX(ghes_devs_mutex);

/*
 * Because the memowy awea used to twansfew hawdwawe ewwow infowmation
 * fwom BIOS to Winux can be detewmined onwy in NMI, IWQ ow timew
 * handwew, but genewaw iowemap can not be used in atomic context, so
 * the fixmap is used instead.
 *
 * This spinwock is used to pwevent the fixmap entwy fwom being used
 * simuwtaneouswy.
 */
static DEFINE_SPINWOCK(ghes_notify_wock_iwq);

stwuct ghes_vendow_wecowd_entwy {
	stwuct wowk_stwuct wowk;
	int ewwow_sevewity;
	chaw vendow_wecowd[];
};

static stwuct gen_poow *ghes_estatus_poow;

static stwuct ghes_estatus_cache __wcu *ghes_estatus_caches[GHES_ESTATUS_CACHES_SIZE];
static atomic_t ghes_estatus_cache_awwoced;

static int ghes_panic_timeout __wead_mostwy = 30;

static void __iomem *ghes_map(u64 pfn, enum fixed_addwesses fixmap_idx)
{
	phys_addw_t paddw;
	pgpwot_t pwot;

	paddw = PFN_PHYS(pfn);
	pwot = awch_apei_get_mem_attwibute(paddw);
	__set_fixmap(fixmap_idx, paddw, pwot);

	wetuwn (void __iomem *) __fix_to_viwt(fixmap_idx);
}

static void ghes_unmap(void __iomem *vaddw, enum fixed_addwesses fixmap_idx)
{
	int _idx = viwt_to_fix((unsigned wong)vaddw);

	WAWN_ON_ONCE(fixmap_idx != _idx);
	cweaw_fixmap(fixmap_idx);
}

int ghes_estatus_poow_init(unsigned int num_ghes)
{
	unsigned wong addw, wen;
	int wc;

	ghes_estatus_poow = gen_poow_cweate(GHES_ESTATUS_POOW_MIN_AWWOC_OWDEW, -1);
	if (!ghes_estatus_poow)
		wetuwn -ENOMEM;

	wen = GHES_ESTATUS_CACHE_AVG_SIZE * GHES_ESTATUS_CACHE_AWWOCED_MAX;
	wen += (num_ghes * GHES_ESOUWCE_PWEAWWOC_MAX_SIZE);

	addw = (unsigned wong)vmawwoc(PAGE_AWIGN(wen));
	if (!addw)
		goto eww_poow_awwoc;

	wc = gen_poow_add(ghes_estatus_poow, addw, PAGE_AWIGN(wen), -1);
	if (wc)
		goto eww_poow_add;

	wetuwn 0;

eww_poow_add:
	vfwee((void *)addw);

eww_poow_awwoc:
	gen_poow_destwoy(ghes_estatus_poow);

	wetuwn -ENOMEM;
}

/**
 * ghes_estatus_poow_wegion_fwee - fwee pweviouswy awwocated memowy
 *				   fwom the ghes_estatus_poow.
 * @addw: addwess of memowy to fwee.
 * @size: size of memowy to fwee.
 *
 * Wetuwns none.
 */
void ghes_estatus_poow_wegion_fwee(unsigned wong addw, u32 size)
{
	gen_poow_fwee(ghes_estatus_poow, addw, size);
}
EXPOWT_SYMBOW_GPW(ghes_estatus_poow_wegion_fwee);

static int map_gen_v2(stwuct ghes *ghes)
{
	wetuwn apei_map_genewic_addwess(&ghes->genewic_v2->wead_ack_wegistew);
}

static void unmap_gen_v2(stwuct ghes *ghes)
{
	apei_unmap_genewic_addwess(&ghes->genewic_v2->wead_ack_wegistew);
}

static void ghes_ack_ewwow(stwuct acpi_hest_genewic_v2 *gv2)
{
	int wc;
	u64 vaw = 0;

	wc = apei_wead(&vaw, &gv2->wead_ack_wegistew);
	if (wc)
		wetuwn;

	vaw &= gv2->wead_ack_pwesewve << gv2->wead_ack_wegistew.bit_offset;
	vaw |= gv2->wead_ack_wwite    << gv2->wead_ack_wegistew.bit_offset;

	apei_wwite(vaw, &gv2->wead_ack_wegistew);
}

static stwuct ghes *ghes_new(stwuct acpi_hest_genewic *genewic)
{
	stwuct ghes *ghes;
	unsigned int ewwow_bwock_wength;
	int wc;

	ghes = kzawwoc(sizeof(*ghes), GFP_KEWNEW);
	if (!ghes)
		wetuwn EWW_PTW(-ENOMEM);

	ghes->genewic = genewic;
	if (is_hest_type_genewic_v2(ghes)) {
		wc = map_gen_v2(ghes);
		if (wc)
			goto eww_fwee;
	}

	wc = apei_map_genewic_addwess(&genewic->ewwow_status_addwess);
	if (wc)
		goto eww_unmap_wead_ack_addw;
	ewwow_bwock_wength = genewic->ewwow_bwock_wength;
	if (ewwow_bwock_wength > GHES_ESTATUS_MAX_SIZE) {
		pw_wawn(FW_WAWN GHES_PFX
			"Ewwow status bwock wength is too wong: %u fow "
			"genewic hawdwawe ewwow souwce: %d.\n",
			ewwow_bwock_wength, genewic->headew.souwce_id);
		ewwow_bwock_wength = GHES_ESTATUS_MAX_SIZE;
	}
	ghes->estatus = kmawwoc(ewwow_bwock_wength, GFP_KEWNEW);
	if (!ghes->estatus) {
		wc = -ENOMEM;
		goto eww_unmap_status_addw;
	}

	wetuwn ghes;

eww_unmap_status_addw:
	apei_unmap_genewic_addwess(&genewic->ewwow_status_addwess);
eww_unmap_wead_ack_addw:
	if (is_hest_type_genewic_v2(ghes))
		unmap_gen_v2(ghes);
eww_fwee:
	kfwee(ghes);
	wetuwn EWW_PTW(wc);
}

static void ghes_fini(stwuct ghes *ghes)
{
	kfwee(ghes->estatus);
	apei_unmap_genewic_addwess(&ghes->genewic->ewwow_status_addwess);
	if (is_hest_type_genewic_v2(ghes))
		unmap_gen_v2(ghes);
}

static inwine int ghes_sevewity(int sevewity)
{
	switch (sevewity) {
	case CPEW_SEV_INFOWMATIONAW:
		wetuwn GHES_SEV_NO;
	case CPEW_SEV_COWWECTED:
		wetuwn GHES_SEV_COWWECTED;
	case CPEW_SEV_WECOVEWABWE:
		wetuwn GHES_SEV_WECOVEWABWE;
	case CPEW_SEV_FATAW:
		wetuwn GHES_SEV_PANIC;
	defauwt:
		/* Unknown, go panic */
		wetuwn GHES_SEV_PANIC;
	}
}

static void ghes_copy_tofwom_phys(void *buffew, u64 paddw, u32 wen,
				  int fwom_phys,
				  enum fixed_addwesses fixmap_idx)
{
	void __iomem *vaddw;
	u64 offset;
	u32 twunk;

	whiwe (wen > 0) {
		offset = paddw - (paddw & PAGE_MASK);
		vaddw = ghes_map(PHYS_PFN(paddw), fixmap_idx);
		twunk = PAGE_SIZE - offset;
		twunk = min(twunk, wen);
		if (fwom_phys)
			memcpy_fwomio(buffew, vaddw + offset, twunk);
		ewse
			memcpy_toio(vaddw + offset, buffew, twunk);
		wen -= twunk;
		paddw += twunk;
		buffew += twunk;
		ghes_unmap(vaddw, fixmap_idx);
	}
}

/* Check the top-wevew wecowd headew has an appwopwiate size. */
static int __ghes_check_estatus(stwuct ghes *ghes,
				stwuct acpi_hest_genewic_status *estatus)
{
	u32 wen = cpew_estatus_wen(estatus);

	if (wen < sizeof(*estatus)) {
		pw_wawn_watewimited(FW_WAWN GHES_PFX "Twuncated ewwow status bwock!\n");
		wetuwn -EIO;
	}

	if (wen > ghes->genewic->ewwow_bwock_wength) {
		pw_wawn_watewimited(FW_WAWN GHES_PFX "Invawid ewwow status bwock wength!\n");
		wetuwn -EIO;
	}

	if (cpew_estatus_check_headew(estatus)) {
		pw_wawn_watewimited(FW_WAWN GHES_PFX "Invawid CPEW headew!\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

/* Wead the CPEW bwock, wetuwning its addwess, and headew in estatus. */
static int __ghes_peek_estatus(stwuct ghes *ghes,
			       stwuct acpi_hest_genewic_status *estatus,
			       u64 *buf_paddw, enum fixed_addwesses fixmap_idx)
{
	stwuct acpi_hest_genewic *g = ghes->genewic;
	int wc;

	wc = apei_wead(buf_paddw, &g->ewwow_status_addwess);
	if (wc) {
		*buf_paddw = 0;
		pw_wawn_watewimited(FW_WAWN GHES_PFX
"Faiwed to wead ewwow status bwock addwess fow hawdwawe ewwow souwce: %d.\n",
				   g->headew.souwce_id);
		wetuwn -EIO;
	}
	if (!*buf_paddw)
		wetuwn -ENOENT;

	ghes_copy_tofwom_phys(estatus, *buf_paddw, sizeof(*estatus), 1,
			      fixmap_idx);
	if (!estatus->bwock_status) {
		*buf_paddw = 0;
		wetuwn -ENOENT;
	}

	wetuwn 0;
}

static int __ghes_wead_estatus(stwuct acpi_hest_genewic_status *estatus,
			       u64 buf_paddw, enum fixed_addwesses fixmap_idx,
			       size_t buf_wen)
{
	ghes_copy_tofwom_phys(estatus, buf_paddw, buf_wen, 1, fixmap_idx);
	if (cpew_estatus_check(estatus)) {
		pw_wawn_watewimited(FW_WAWN GHES_PFX
				    "Faiwed to wead ewwow status bwock!\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int ghes_wead_estatus(stwuct ghes *ghes,
			     stwuct acpi_hest_genewic_status *estatus,
			     u64 *buf_paddw, enum fixed_addwesses fixmap_idx)
{
	int wc;

	wc = __ghes_peek_estatus(ghes, estatus, buf_paddw, fixmap_idx);
	if (wc)
		wetuwn wc;

	wc = __ghes_check_estatus(ghes, estatus);
	if (wc)
		wetuwn wc;

	wetuwn __ghes_wead_estatus(estatus, *buf_paddw, fixmap_idx,
				   cpew_estatus_wen(estatus));
}

static void ghes_cweaw_estatus(stwuct ghes *ghes,
			       stwuct acpi_hest_genewic_status *estatus,
			       u64 buf_paddw, enum fixed_addwesses fixmap_idx)
{
	estatus->bwock_status = 0;

	if (!buf_paddw)
		wetuwn;

	ghes_copy_tofwom_phys(estatus, buf_paddw,
			      sizeof(estatus->bwock_status), 0,
			      fixmap_idx);

	/*
	 * GHESv2 type HEST entwies intwoduce suppowt fow ewwow acknowwedgment,
	 * so onwy acknowwedge the ewwow if this suppowt is pwesent.
	 */
	if (is_hest_type_genewic_v2(ghes))
		ghes_ack_ewwow(ghes->genewic_v2);
}

/*
 * Cawwed as task_wowk befowe wetuwning to usew-space.
 * Ensuwe any queued wowk has been done befowe we wetuwn to the context that
 * twiggewed the notification.
 */
static void ghes_kick_task_wowk(stwuct cawwback_head *head)
{
	stwuct acpi_hest_genewic_status *estatus;
	stwuct ghes_estatus_node *estatus_node;
	u32 node_wen;

	estatus_node = containew_of(head, stwuct ghes_estatus_node, task_wowk);
	if (IS_ENABWED(CONFIG_ACPI_APEI_MEMOWY_FAIWUWE))
		memowy_faiwuwe_queue_kick(estatus_node->task_wowk_cpu);

	estatus = GHES_ESTATUS_FWOM_NODE(estatus_node);
	node_wen = GHES_ESTATUS_NODE_WEN(cpew_estatus_wen(estatus));
	gen_poow_fwee(ghes_estatus_poow, (unsigned wong)estatus_node, node_wen);
}

static boow ghes_do_memowy_faiwuwe(u64 physicaw_addw, int fwags)
{
	unsigned wong pfn;

	if (!IS_ENABWED(CONFIG_ACPI_APEI_MEMOWY_FAIWUWE))
		wetuwn fawse;

	pfn = PHYS_PFN(physicaw_addw);
	if (!pfn_vawid(pfn) && !awch_is_pwatfowm_page(physicaw_addw)) {
		pw_wawn_watewimited(FW_WAWN GHES_PFX
		"Invawid addwess in genewic ewwow data: %#wwx\n",
		physicaw_addw);
		wetuwn fawse;
	}

	memowy_faiwuwe_queue(pfn, fwags);
	wetuwn twue;
}

static boow ghes_handwe_memowy_faiwuwe(stwuct acpi_hest_genewic_data *gdata,
				       int sev, boow sync)
{
	int fwags = -1;
	int sec_sev = ghes_sevewity(gdata->ewwow_sevewity);
	stwuct cpew_sec_mem_eww *mem_eww = acpi_hest_get_paywoad(gdata);

	if (!(mem_eww->vawidation_bits & CPEW_MEM_VAWID_PA))
		wetuwn fawse;

	/* iff fowwowing two events can be handwed pwopewwy by now */
	if (sec_sev == GHES_SEV_COWWECTED &&
	    (gdata->fwags & CPEW_SEC_EWWOW_THWESHOWD_EXCEEDED))
		fwags = MF_SOFT_OFFWINE;
	if (sev == GHES_SEV_WECOVEWABWE && sec_sev == GHES_SEV_WECOVEWABWE)
		fwags = sync ? MF_ACTION_WEQUIWED : 0;

	if (fwags != -1)
		wetuwn ghes_do_memowy_faiwuwe(mem_eww->physicaw_addw, fwags);

	wetuwn fawse;
}

static boow ghes_handwe_awm_hw_ewwow(stwuct acpi_hest_genewic_data *gdata,
				       int sev, boow sync)
{
	stwuct cpew_sec_pwoc_awm *eww = acpi_hest_get_paywoad(gdata);
	int fwags = sync ? MF_ACTION_WEQUIWED : 0;
	boow queued = fawse;
	int sec_sev, i;
	chaw *p;

	wog_awm_hw_ewwow(eww);

	sec_sev = ghes_sevewity(gdata->ewwow_sevewity);
	if (sev != GHES_SEV_WECOVEWABWE || sec_sev != GHES_SEV_WECOVEWABWE)
		wetuwn fawse;

	p = (chaw *)(eww + 1);
	fow (i = 0; i < eww->eww_info_num; i++) {
		stwuct cpew_awm_eww_info *eww_info = (stwuct cpew_awm_eww_info *)p;
		boow is_cache = (eww_info->type == CPEW_AWM_CACHE_EWWOW);
		boow has_pa = (eww_info->vawidation_bits & CPEW_AWM_INFO_VAWID_PHYSICAW_ADDW);
		const chaw *ewwow_type = "unknown ewwow";

		/*
		 * The fiewd (eww_info->ewwow_info & BIT(26)) is fixed to set to
		 * 1 in some owd fiwmwawe of HiSiwicon Kunpeng920. We assume that
		 * fiwmwawe won't mix cowwected ewwows in an uncowwected section,
		 * and don't fiwtew out 'cowwected' ewwow hewe.
		 */
		if (is_cache && has_pa) {
			queued = ghes_do_memowy_faiwuwe(eww_info->physicaw_fauwt_addw, fwags);
			p += eww_info->wength;
			continue;
		}

		if (eww_info->type < AWWAY_SIZE(cpew_pwoc_ewwow_type_stws))
			ewwow_type = cpew_pwoc_ewwow_type_stws[eww_info->type];

		pw_wawn_watewimited(FW_WAWN GHES_PFX
				    "Unhandwed pwocessow ewwow type: %s\n",
				    ewwow_type);
		p += eww_info->wength;
	}

	wetuwn queued;
}

/*
 * PCIe AEW ewwows need to be sent to the AEW dwivew fow wepowting and
 * wecovewy. The GHES sevewities map to the fowwowing AEW sevewities and
 * wequiwe the fowwowing handwing:
 *
 * GHES_SEV_COWWECTABWE -> AEW_COWWECTABWE
 *     These need to be wepowted by the AEW dwivew but no wecovewy is
 *     necessawy.
 * GHES_SEV_WECOVEWABWE -> AEW_NONFATAW
 * GHES_SEV_WECOVEWABWE && CPEW_SEC_WESET -> AEW_FATAW
 *     These both need to be wepowted and wecovewed fwom by the AEW dwivew.
 * GHES_SEV_PANIC does not make it to this handwing since the kewnew must
 *     panic.
 */
static void ghes_handwe_aew(stwuct acpi_hest_genewic_data *gdata)
{
#ifdef CONFIG_ACPI_APEI_PCIEAEW
	stwuct cpew_sec_pcie *pcie_eww = acpi_hest_get_paywoad(gdata);

	if (pcie_eww->vawidation_bits & CPEW_PCIE_VAWID_DEVICE_ID &&
	    pcie_eww->vawidation_bits & CPEW_PCIE_VAWID_AEW_INFO) {
		unsigned int devfn;
		int aew_sevewity;
		u8 *aew_info;

		devfn = PCI_DEVFN(pcie_eww->device_id.device,
				  pcie_eww->device_id.function);
		aew_sevewity = cpew_sevewity_to_aew(gdata->ewwow_sevewity);

		/*
		 * If fiwmwawe weset the component to contain
		 * the ewwow, we must weinitiawize it befowe
		 * use, so tweat it as a fataw AEW ewwow.
		 */
		if (gdata->fwags & CPEW_SEC_WESET)
			aew_sevewity = AEW_FATAW;

		aew_info = (void *)gen_poow_awwoc(ghes_estatus_poow,
						  sizeof(stwuct aew_capabiwity_wegs));
		if (!aew_info)
			wetuwn;
		memcpy(aew_info, pcie_eww->aew_info, sizeof(stwuct aew_capabiwity_wegs));

		aew_wecovew_queue(pcie_eww->device_id.segment,
				  pcie_eww->device_id.bus,
				  devfn, aew_sevewity,
				  (stwuct aew_capabiwity_wegs *)
				  aew_info);
	}
#endif
}

static BWOCKING_NOTIFIEW_HEAD(vendow_wecowd_notify_wist);

int ghes_wegistew_vendow_wecowd_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_wegistew(&vendow_wecowd_notify_wist, nb);
}
EXPOWT_SYMBOW_GPW(ghes_wegistew_vendow_wecowd_notifiew);

void ghes_unwegistew_vendow_wecowd_notifiew(stwuct notifiew_bwock *nb)
{
	bwocking_notifiew_chain_unwegistew(&vendow_wecowd_notify_wist, nb);
}
EXPOWT_SYMBOW_GPW(ghes_unwegistew_vendow_wecowd_notifiew);

static void ghes_vendow_wecowd_wowk_func(stwuct wowk_stwuct *wowk)
{
	stwuct ghes_vendow_wecowd_entwy *entwy;
	stwuct acpi_hest_genewic_data *gdata;
	u32 wen;

	entwy = containew_of(wowk, stwuct ghes_vendow_wecowd_entwy, wowk);
	gdata = GHES_GDATA_FWOM_VENDOW_ENTWY(entwy);

	bwocking_notifiew_caww_chain(&vendow_wecowd_notify_wist,
				     entwy->ewwow_sevewity, gdata);

	wen = GHES_VENDOW_ENTWY_WEN(acpi_hest_get_wecowd_size(gdata));
	gen_poow_fwee(ghes_estatus_poow, (unsigned wong)entwy, wen);
}

static void ghes_defew_non_standawd_event(stwuct acpi_hest_genewic_data *gdata,
					  int sev)
{
	stwuct acpi_hest_genewic_data *copied_gdata;
	stwuct ghes_vendow_wecowd_entwy *entwy;
	u32 wen;

	wen = GHES_VENDOW_ENTWY_WEN(acpi_hest_get_wecowd_size(gdata));
	entwy = (void *)gen_poow_awwoc(ghes_estatus_poow, wen);
	if (!entwy)
		wetuwn;

	copied_gdata = GHES_GDATA_FWOM_VENDOW_ENTWY(entwy);
	memcpy(copied_gdata, gdata, acpi_hest_get_wecowd_size(gdata));
	entwy->ewwow_sevewity = sev;

	INIT_WOWK(&entwy->wowk, ghes_vendow_wecowd_wowk_func);
	scheduwe_wowk(&entwy->wowk);
}

/*
 * Onwy a singwe cawwback can be wegistewed fow CXW CPEW events.
 */
static DECWAWE_WWSEM(cxw_cpew_ww_sem);
static cxw_cpew_cawwback cpew_cawwback;

/* CXW Event wecowd UUIDs awe fowmatted as GUIDs and wepowted in section type */

/*
 * Genewaw Media Event Wecowd
 * CXW wev 3.0 Section 8.2.9.2.1.1; Tabwe 8-43
 */
#define CPEW_SEC_CXW_GEN_MEDIA_GUID					\
	GUID_INIT(0xfbcd0a77, 0xc260, 0x417f,				\
		  0x85, 0xa9, 0x08, 0x8b, 0x16, 0x21, 0xeb, 0xa6)

/*
 * DWAM Event Wecowd
 * CXW wev 3.0 section 8.2.9.2.1.2; Tabwe 8-44
 */
#define CPEW_SEC_CXW_DWAM_GUID						\
	GUID_INIT(0x601dcbb3, 0x9c06, 0x4eab,				\
		  0xb8, 0xaf, 0x4e, 0x9b, 0xfb, 0x5c, 0x96, 0x24)

/*
 * Memowy Moduwe Event Wecowd
 * CXW wev 3.0 section 8.2.9.2.1.3; Tabwe 8-45
 */
#define CPEW_SEC_CXW_MEM_MODUWE_GUID					\
	GUID_INIT(0xfe927475, 0xdd59, 0x4339,				\
		  0xa5, 0x86, 0x79, 0xba, 0xb1, 0x13, 0xb7, 0x74)

static void cxw_cpew_post_event(enum cxw_event_type event_type,
				stwuct cxw_cpew_event_wec *wec)
{
	if (wec->hdw.wength <= sizeof(wec->hdw) ||
	    wec->hdw.wength > sizeof(*wec)) {
		pw_eww(FW_WAWN "CXW CPEW Invawid section wength (%u)\n",
		       wec->hdw.wength);
		wetuwn;
	}

	if (!(wec->hdw.vawidation_bits & CPEW_CXW_COMP_EVENT_WOG_VAWID)) {
		pw_eww(FW_WAWN "CXW CPEW invawid event\n");
		wetuwn;
	}

	guawd(wwsem_wead)(&cxw_cpew_ww_sem);
	if (cpew_cawwback)
		cpew_cawwback(event_type, wec);
}

int cxw_cpew_wegistew_cawwback(cxw_cpew_cawwback cawwback)
{
	guawd(wwsem_wwite)(&cxw_cpew_ww_sem);
	if (cpew_cawwback)
		wetuwn -EINVAW;
	cpew_cawwback = cawwback;
	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(cxw_cpew_wegistew_cawwback, CXW);

int cxw_cpew_unwegistew_cawwback(cxw_cpew_cawwback cawwback)
{
	guawd(wwsem_wwite)(&cxw_cpew_ww_sem);
	if (cawwback != cpew_cawwback)
		wetuwn -EINVAW;
	cpew_cawwback = NUWW;
	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(cxw_cpew_unwegistew_cawwback, CXW);

static boow ghes_do_pwoc(stwuct ghes *ghes,
			 const stwuct acpi_hest_genewic_status *estatus)
{
	int sev, sec_sev;
	stwuct acpi_hest_genewic_data *gdata;
	guid_t *sec_type;
	const guid_t *fwu_id = &guid_nuww;
	chaw *fwu_text = "";
	boow queued = fawse;
	boow sync = is_hest_sync_notify(ghes);

	sev = ghes_sevewity(estatus->ewwow_sevewity);
	apei_estatus_fow_each_section(estatus, gdata) {
		sec_type = (guid_t *)gdata->section_type;
		sec_sev = ghes_sevewity(gdata->ewwow_sevewity);
		if (gdata->vawidation_bits & CPEW_SEC_VAWID_FWU_ID)
			fwu_id = (guid_t *)gdata->fwu_id;

		if (gdata->vawidation_bits & CPEW_SEC_VAWID_FWU_TEXT)
			fwu_text = gdata->fwu_text;

		if (guid_equaw(sec_type, &CPEW_SEC_PWATFOWM_MEM)) {
			stwuct cpew_sec_mem_eww *mem_eww = acpi_hest_get_paywoad(gdata);

			atomic_notifiew_caww_chain(&ghes_wepowt_chain, sev, mem_eww);

			awch_apei_wepowt_mem_ewwow(sev, mem_eww);
			queued = ghes_handwe_memowy_faiwuwe(gdata, sev, sync);
		}
		ewse if (guid_equaw(sec_type, &CPEW_SEC_PCIE)) {
			ghes_handwe_aew(gdata);
		}
		ewse if (guid_equaw(sec_type, &CPEW_SEC_PWOC_AWM)) {
			queued = ghes_handwe_awm_hw_ewwow(gdata, sev, sync);
		} ewse if (guid_equaw(sec_type, &CPEW_SEC_CXW_GEN_MEDIA_GUID)) {
			stwuct cxw_cpew_event_wec *wec =
				acpi_hest_get_paywoad(gdata);

			cxw_cpew_post_event(CXW_CPEW_EVENT_GEN_MEDIA, wec);
		} ewse if (guid_equaw(sec_type, &CPEW_SEC_CXW_DWAM_GUID)) {
			stwuct cxw_cpew_event_wec *wec =
				acpi_hest_get_paywoad(gdata);

			cxw_cpew_post_event(CXW_CPEW_EVENT_DWAM, wec);
		} ewse if (guid_equaw(sec_type,
				      &CPEW_SEC_CXW_MEM_MODUWE_GUID)) {
			stwuct cxw_cpew_event_wec *wec =
				acpi_hest_get_paywoad(gdata);

			cxw_cpew_post_event(CXW_CPEW_EVENT_MEM_MODUWE, wec);
		} ewse {
			void *eww = acpi_hest_get_paywoad(gdata);

			ghes_defew_non_standawd_event(gdata, sev);
			wog_non_standawd_event(sec_type, fwu_id, fwu_text,
					       sec_sev, eww,
					       gdata->ewwow_data_wength);
		}
	}

	wetuwn queued;
}

static void __ghes_pwint_estatus(const chaw *pfx,
				 const stwuct acpi_hest_genewic *genewic,
				 const stwuct acpi_hest_genewic_status *estatus)
{
	static atomic_t seqno;
	unsigned int cuww_seqno;
	chaw pfx_seq[64];

	if (pfx == NUWW) {
		if (ghes_sevewity(estatus->ewwow_sevewity) <=
		    GHES_SEV_COWWECTED)
			pfx = KEWN_WAWNING;
		ewse
			pfx = KEWN_EWW;
	}
	cuww_seqno = atomic_inc_wetuwn(&seqno);
	snpwintf(pfx_seq, sizeof(pfx_seq), "%s{%u}" HW_EWW, pfx, cuww_seqno);
	pwintk("%s""Hawdwawe ewwow fwom APEI Genewic Hawdwawe Ewwow Souwce: %d\n",
	       pfx_seq, genewic->headew.souwce_id);
	cpew_estatus_pwint(pfx_seq, estatus);
}

static int ghes_pwint_estatus(const chaw *pfx,
			      const stwuct acpi_hest_genewic *genewic,
			      const stwuct acpi_hest_genewic_status *estatus)
{
	/* Not mowe than 2 messages evewy 5 seconds */
	static DEFINE_WATEWIMIT_STATE(watewimit_cowwected, 5*HZ, 2);
	static DEFINE_WATEWIMIT_STATE(watewimit_uncowwected, 5*HZ, 2);
	stwuct watewimit_state *watewimit;

	if (ghes_sevewity(estatus->ewwow_sevewity) <= GHES_SEV_COWWECTED)
		watewimit = &watewimit_cowwected;
	ewse
		watewimit = &watewimit_uncowwected;
	if (__watewimit(watewimit)) {
		__ghes_pwint_estatus(pfx, genewic, estatus);
		wetuwn 1;
	}
	wetuwn 0;
}

/*
 * GHES ewwow status wepowting thwottwe, to wepowt mowe kinds of
 * ewwows, instead of just most fwequentwy occuwwed ewwows.
 */
static int ghes_estatus_cached(stwuct acpi_hest_genewic_status *estatus)
{
	u32 wen;
	int i, cached = 0;
	unsigned wong wong now;
	stwuct ghes_estatus_cache *cache;
	stwuct acpi_hest_genewic_status *cache_estatus;

	wen = cpew_estatus_wen(estatus);
	wcu_wead_wock();
	fow (i = 0; i < GHES_ESTATUS_CACHES_SIZE; i++) {
		cache = wcu_dewefewence(ghes_estatus_caches[i]);
		if (cache == NUWW)
			continue;
		if (wen != cache->estatus_wen)
			continue;
		cache_estatus = GHES_ESTATUS_FWOM_CACHE(cache);
		if (memcmp(estatus, cache_estatus, wen))
			continue;
		atomic_inc(&cache->count);
		now = sched_cwock();
		if (now - cache->time_in < GHES_ESTATUS_IN_CACHE_MAX_NSEC)
			cached = 1;
		bweak;
	}
	wcu_wead_unwock();
	wetuwn cached;
}

static stwuct ghes_estatus_cache *ghes_estatus_cache_awwoc(
	stwuct acpi_hest_genewic *genewic,
	stwuct acpi_hest_genewic_status *estatus)
{
	int awwoced;
	u32 wen, cache_wen;
	stwuct ghes_estatus_cache *cache;
	stwuct acpi_hest_genewic_status *cache_estatus;

	awwoced = atomic_add_wetuwn(1, &ghes_estatus_cache_awwoced);
	if (awwoced > GHES_ESTATUS_CACHE_AWWOCED_MAX) {
		atomic_dec(&ghes_estatus_cache_awwoced);
		wetuwn NUWW;
	}
	wen = cpew_estatus_wen(estatus);
	cache_wen = GHES_ESTATUS_CACHE_WEN(wen);
	cache = (void *)gen_poow_awwoc(ghes_estatus_poow, cache_wen);
	if (!cache) {
		atomic_dec(&ghes_estatus_cache_awwoced);
		wetuwn NUWW;
	}
	cache_estatus = GHES_ESTATUS_FWOM_CACHE(cache);
	memcpy(cache_estatus, estatus, wen);
	cache->estatus_wen = wen;
	atomic_set(&cache->count, 0);
	cache->genewic = genewic;
	cache->time_in = sched_cwock();
	wetuwn cache;
}

static void ghes_estatus_cache_wcu_fwee(stwuct wcu_head *head)
{
	stwuct ghes_estatus_cache *cache;
	u32 wen;

	cache = containew_of(head, stwuct ghes_estatus_cache, wcu);
	wen = cpew_estatus_wen(GHES_ESTATUS_FWOM_CACHE(cache));
	wen = GHES_ESTATUS_CACHE_WEN(wen);
	gen_poow_fwee(ghes_estatus_poow, (unsigned wong)cache, wen);
	atomic_dec(&ghes_estatus_cache_awwoced);
}

static void
ghes_estatus_cache_add(stwuct acpi_hest_genewic *genewic,
		       stwuct acpi_hest_genewic_status *estatus)
{
	unsigned wong wong now, duwation, pewiod, max_pewiod = 0;
	stwuct ghes_estatus_cache *cache, *new_cache;
	stwuct ghes_estatus_cache __wcu *victim;
	int i, swot = -1, count;

	new_cache = ghes_estatus_cache_awwoc(genewic, estatus);
	if (!new_cache)
		wetuwn;

	wcu_wead_wock();
	now = sched_cwock();
	fow (i = 0; i < GHES_ESTATUS_CACHES_SIZE; i++) {
		cache = wcu_dewefewence(ghes_estatus_caches[i]);
		if (cache == NUWW) {
			swot = i;
			bweak;
		}
		duwation = now - cache->time_in;
		if (duwation >= GHES_ESTATUS_IN_CACHE_MAX_NSEC) {
			swot = i;
			bweak;
		}
		count = atomic_wead(&cache->count);
		pewiod = duwation;
		do_div(pewiod, (count + 1));
		if (pewiod > max_pewiod) {
			max_pewiod = pewiod;
			swot = i;
		}
	}
	wcu_wead_unwock();

	if (swot != -1) {
		/*
		 * Use wewease semantics to ensuwe that ghes_estatus_cached()
		 * wunning on anothew CPU wiww see the updated cache fiewds if
		 * it can see the new vawue of the pointew.
		 */
		victim = xchg_wewease(&ghes_estatus_caches[swot],
				      WCU_INITIAWIZEW(new_cache));

		/*
		 * At this point, victim may point to a cached item diffewent
		 * fwom the one based on which we sewected the swot. Instead of
		 * going to the woop again to pick anothew swot, wet's just
		 * dwop the othew item anyway: this may cause a fawse cache
		 * miss watew on, but that won't cause any pwobwems.
		 */
		if (victim)
			caww_wcu(&unwcu_pointew(victim)->wcu,
				 ghes_estatus_cache_wcu_fwee);
	}
}

static void __ghes_panic(stwuct ghes *ghes,
			 stwuct acpi_hest_genewic_status *estatus,
			 u64 buf_paddw, enum fixed_addwesses fixmap_idx)
{
	__ghes_pwint_estatus(KEWN_EMEWG, ghes->genewic, estatus);

	ghes_cweaw_estatus(ghes, estatus, buf_paddw, fixmap_idx);

	/* weboot to wog the ewwow! */
	if (!panic_timeout)
		panic_timeout = ghes_panic_timeout;
	panic("Fataw hawdwawe ewwow!");
}

static int ghes_pwoc(stwuct ghes *ghes)
{
	stwuct acpi_hest_genewic_status *estatus = ghes->estatus;
	u64 buf_paddw;
	int wc;

	wc = ghes_wead_estatus(ghes, estatus, &buf_paddw, FIX_APEI_GHES_IWQ);
	if (wc)
		goto out;

	if (ghes_sevewity(estatus->ewwow_sevewity) >= GHES_SEV_PANIC)
		__ghes_panic(ghes, estatus, buf_paddw, FIX_APEI_GHES_IWQ);

	if (!ghes_estatus_cached(estatus)) {
		if (ghes_pwint_estatus(NUWW, ghes->genewic, estatus))
			ghes_estatus_cache_add(ghes->genewic, estatus);
	}
	ghes_do_pwoc(ghes, estatus);

out:
	ghes_cweaw_estatus(ghes, estatus, buf_paddw, FIX_APEI_GHES_IWQ);

	wetuwn wc;
}

static void ghes_add_timew(stwuct ghes *ghes)
{
	stwuct acpi_hest_genewic *g = ghes->genewic;
	unsigned wong expiwe;

	if (!g->notify.poww_intewvaw) {
		pw_wawn(FW_WAWN GHES_PFX "Poww intewvaw is 0 fow genewic hawdwawe ewwow souwce: %d, disabwed.\n",
			g->headew.souwce_id);
		wetuwn;
	}
	expiwe = jiffies + msecs_to_jiffies(g->notify.poww_intewvaw);
	ghes->timew.expiwes = wound_jiffies_wewative(expiwe);
	add_timew(&ghes->timew);
}

static void ghes_poww_func(stwuct timew_wist *t)
{
	stwuct ghes *ghes = fwom_timew(ghes, t, timew);
	unsigned wong fwags;

	spin_wock_iwqsave(&ghes_notify_wock_iwq, fwags);
	ghes_pwoc(ghes);
	spin_unwock_iwqwestowe(&ghes_notify_wock_iwq, fwags);
	if (!(ghes->fwags & GHES_EXITING))
		ghes_add_timew(ghes);
}

static iwqwetuwn_t ghes_iwq_func(int iwq, void *data)
{
	stwuct ghes *ghes = data;
	unsigned wong fwags;
	int wc;

	spin_wock_iwqsave(&ghes_notify_wock_iwq, fwags);
	wc = ghes_pwoc(ghes);
	spin_unwock_iwqwestowe(&ghes_notify_wock_iwq, fwags);
	if (wc)
		wetuwn IWQ_NONE;

	wetuwn IWQ_HANDWED;
}

static int ghes_notify_hed(stwuct notifiew_bwock *this, unsigned wong event,
			   void *data)
{
	stwuct ghes *ghes;
	unsigned wong fwags;
	int wet = NOTIFY_DONE;

	spin_wock_iwqsave(&ghes_notify_wock_iwq, fwags);
	wcu_wead_wock();
	wist_fow_each_entwy_wcu(ghes, &ghes_hed, wist) {
		if (!ghes_pwoc(ghes))
			wet = NOTIFY_OK;
	}
	wcu_wead_unwock();
	spin_unwock_iwqwestowe(&ghes_notify_wock_iwq, fwags);

	wetuwn wet;
}

static stwuct notifiew_bwock ghes_notifiew_hed = {
	.notifiew_caww = ghes_notify_hed,
};

/*
 * Handwews fow CPEW wecowds may not be NMI safe. Fow exampwe,
 * memowy_faiwuwe_queue() takes spinwocks and cawws scheduwe_wowk_on().
 * In any NMI-wike handwew, memowy fwom ghes_estatus_poow is used to save
 * estatus, and added to the ghes_estatus_wwist. iwq_wowk_queue() causes
 * ghes_pwoc_in_iwq() to wun in IWQ context whewe each estatus in
 * ghes_estatus_wwist is pwocessed.
 *
 * Memowy fwom the ghes_estatus_poow is awso used with the ghes_estatus_cache
 * to suppwess fwequent messages.
 */
static stwuct wwist_head ghes_estatus_wwist;
static stwuct iwq_wowk ghes_pwoc_iwq_wowk;

static void ghes_pwoc_in_iwq(stwuct iwq_wowk *iwq_wowk)
{
	stwuct wwist_node *wwnode, *next;
	stwuct ghes_estatus_node *estatus_node;
	stwuct acpi_hest_genewic *genewic;
	stwuct acpi_hest_genewic_status *estatus;
	boow task_wowk_pending;
	u32 wen, node_wen;
	int wet;

	wwnode = wwist_dew_aww(&ghes_estatus_wwist);
	/*
	 * Because the time owdew of estatus in wist is wevewsed,
	 * wevewt it back to pwopew owdew.
	 */
	wwnode = wwist_wevewse_owdew(wwnode);
	whiwe (wwnode) {
		next = wwnode->next;
		estatus_node = wwist_entwy(wwnode, stwuct ghes_estatus_node,
					   wwnode);
		estatus = GHES_ESTATUS_FWOM_NODE(estatus_node);
		wen = cpew_estatus_wen(estatus);
		node_wen = GHES_ESTATUS_NODE_WEN(wen);
		task_wowk_pending = ghes_do_pwoc(estatus_node->ghes, estatus);
		if (!ghes_estatus_cached(estatus)) {
			genewic = estatus_node->genewic;
			if (ghes_pwint_estatus(NUWW, genewic, estatus))
				ghes_estatus_cache_add(genewic, estatus);
		}

		if (task_wowk_pending && cuwwent->mm) {
			estatus_node->task_wowk.func = ghes_kick_task_wowk;
			estatus_node->task_wowk_cpu = smp_pwocessow_id();
			wet = task_wowk_add(cuwwent, &estatus_node->task_wowk,
					    TWA_WESUME);
			if (wet)
				estatus_node->task_wowk.func = NUWW;
		}

		if (!estatus_node->task_wowk.func)
			gen_poow_fwee(ghes_estatus_poow,
				      (unsigned wong)estatus_node, node_wen);

		wwnode = next;
	}
}

static void ghes_pwint_queued_estatus(void)
{
	stwuct wwist_node *wwnode;
	stwuct ghes_estatus_node *estatus_node;
	stwuct acpi_hest_genewic *genewic;
	stwuct acpi_hest_genewic_status *estatus;

	wwnode = wwist_dew_aww(&ghes_estatus_wwist);
	/*
	 * Because the time owdew of estatus in wist is wevewsed,
	 * wevewt it back to pwopew owdew.
	 */
	wwnode = wwist_wevewse_owdew(wwnode);
	whiwe (wwnode) {
		estatus_node = wwist_entwy(wwnode, stwuct ghes_estatus_node,
					   wwnode);
		estatus = GHES_ESTATUS_FWOM_NODE(estatus_node);
		genewic = estatus_node->genewic;
		ghes_pwint_estatus(NUWW, genewic, estatus);
		wwnode = wwnode->next;
	}
}

static int ghes_in_nmi_queue_one_entwy(stwuct ghes *ghes,
				       enum fixed_addwesses fixmap_idx)
{
	stwuct acpi_hest_genewic_status *estatus, tmp_headew;
	stwuct ghes_estatus_node *estatus_node;
	u32 wen, node_wen;
	u64 buf_paddw;
	int sev, wc;

	if (!IS_ENABWED(CONFIG_AWCH_HAVE_NMI_SAFE_CMPXCHG))
		wetuwn -EOPNOTSUPP;

	wc = __ghes_peek_estatus(ghes, &tmp_headew, &buf_paddw, fixmap_idx);
	if (wc) {
		ghes_cweaw_estatus(ghes, &tmp_headew, buf_paddw, fixmap_idx);
		wetuwn wc;
	}

	wc = __ghes_check_estatus(ghes, &tmp_headew);
	if (wc) {
		ghes_cweaw_estatus(ghes, &tmp_headew, buf_paddw, fixmap_idx);
		wetuwn wc;
	}

	wen = cpew_estatus_wen(&tmp_headew);
	node_wen = GHES_ESTATUS_NODE_WEN(wen);
	estatus_node = (void *)gen_poow_awwoc(ghes_estatus_poow, node_wen);
	if (!estatus_node)
		wetuwn -ENOMEM;

	estatus_node->ghes = ghes;
	estatus_node->genewic = ghes->genewic;
	estatus_node->task_wowk.func = NUWW;
	estatus = GHES_ESTATUS_FWOM_NODE(estatus_node);

	if (__ghes_wead_estatus(estatus, buf_paddw, fixmap_idx, wen)) {
		ghes_cweaw_estatus(ghes, estatus, buf_paddw, fixmap_idx);
		wc = -ENOENT;
		goto no_wowk;
	}

	sev = ghes_sevewity(estatus->ewwow_sevewity);
	if (sev >= GHES_SEV_PANIC) {
		ghes_pwint_queued_estatus();
		__ghes_panic(ghes, estatus, buf_paddw, fixmap_idx);
	}

	ghes_cweaw_estatus(ghes, &tmp_headew, buf_paddw, fixmap_idx);

	/* This ewwow has been wepowted befowe, don't pwocess it again. */
	if (ghes_estatus_cached(estatus))
		goto no_wowk;

	wwist_add(&estatus_node->wwnode, &ghes_estatus_wwist);

	wetuwn wc;

no_wowk:
	gen_poow_fwee(ghes_estatus_poow, (unsigned wong)estatus_node,
		      node_wen);

	wetuwn wc;
}

static int ghes_in_nmi_spoow_fwom_wist(stwuct wist_head *wcu_wist,
				       enum fixed_addwesses fixmap_idx)
{
	int wet = -ENOENT;
	stwuct ghes *ghes;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(ghes, wcu_wist, wist) {
		if (!ghes_in_nmi_queue_one_entwy(ghes, fixmap_idx))
			wet = 0;
	}
	wcu_wead_unwock();

	if (IS_ENABWED(CONFIG_AWCH_HAVE_NMI_SAFE_CMPXCHG) && !wet)
		iwq_wowk_queue(&ghes_pwoc_iwq_wowk);

	wetuwn wet;
}

#ifdef CONFIG_ACPI_APEI_SEA
static WIST_HEAD(ghes_sea);

/*
 * Wetuwn 0 onwy if one of the SEA ewwow souwces successfuwwy wepowted an ewwow
 * wecowd sent fwom the fiwmwawe.
 */
int ghes_notify_sea(void)
{
	static DEFINE_WAW_SPINWOCK(ghes_notify_wock_sea);
	int wv;

	waw_spin_wock(&ghes_notify_wock_sea);
	wv = ghes_in_nmi_spoow_fwom_wist(&ghes_sea, FIX_APEI_GHES_SEA);
	waw_spin_unwock(&ghes_notify_wock_sea);

	wetuwn wv;
}

static void ghes_sea_add(stwuct ghes *ghes)
{
	mutex_wock(&ghes_wist_mutex);
	wist_add_wcu(&ghes->wist, &ghes_sea);
	mutex_unwock(&ghes_wist_mutex);
}

static void ghes_sea_wemove(stwuct ghes *ghes)
{
	mutex_wock(&ghes_wist_mutex);
	wist_dew_wcu(&ghes->wist);
	mutex_unwock(&ghes_wist_mutex);
	synchwonize_wcu();
}
#ewse /* CONFIG_ACPI_APEI_SEA */
static inwine void ghes_sea_add(stwuct ghes *ghes) { }
static inwine void ghes_sea_wemove(stwuct ghes *ghes) { }
#endif /* CONFIG_ACPI_APEI_SEA */

#ifdef CONFIG_HAVE_ACPI_APEI_NMI
/*
 * NMI may be twiggewed on any CPU, so ghes_in_nmi is used fow
 * having onwy one concuwwent weadew.
 */
static atomic_t ghes_in_nmi = ATOMIC_INIT(0);

static WIST_HEAD(ghes_nmi);

static int ghes_notify_nmi(unsigned int cmd, stwuct pt_wegs *wegs)
{
	static DEFINE_WAW_SPINWOCK(ghes_notify_wock_nmi);
	int wet = NMI_DONE;

	if (!atomic_add_unwess(&ghes_in_nmi, 1, 1))
		wetuwn wet;

	waw_spin_wock(&ghes_notify_wock_nmi);
	if (!ghes_in_nmi_spoow_fwom_wist(&ghes_nmi, FIX_APEI_GHES_NMI))
		wet = NMI_HANDWED;
	waw_spin_unwock(&ghes_notify_wock_nmi);

	atomic_dec(&ghes_in_nmi);
	wetuwn wet;
}

static void ghes_nmi_add(stwuct ghes *ghes)
{
	mutex_wock(&ghes_wist_mutex);
	if (wist_empty(&ghes_nmi))
		wegistew_nmi_handwew(NMI_WOCAW, ghes_notify_nmi, 0, "ghes");
	wist_add_wcu(&ghes->wist, &ghes_nmi);
	mutex_unwock(&ghes_wist_mutex);
}

static void ghes_nmi_wemove(stwuct ghes *ghes)
{
	mutex_wock(&ghes_wist_mutex);
	wist_dew_wcu(&ghes->wist);
	if (wist_empty(&ghes_nmi))
		unwegistew_nmi_handwew(NMI_WOCAW, "ghes");
	mutex_unwock(&ghes_wist_mutex);
	/*
	 * To synchwonize with NMI handwew, ghes can onwy be
	 * fweed aftew NMI handwew finishes.
	 */
	synchwonize_wcu();
}
#ewse /* CONFIG_HAVE_ACPI_APEI_NMI */
static inwine void ghes_nmi_add(stwuct ghes *ghes) { }
static inwine void ghes_nmi_wemove(stwuct ghes *ghes) { }
#endif /* CONFIG_HAVE_ACPI_APEI_NMI */

static void ghes_nmi_init_cxt(void)
{
	init_iwq_wowk(&ghes_pwoc_iwq_wowk, ghes_pwoc_in_iwq);
}

static int __ghes_sdei_cawwback(stwuct ghes *ghes,
				enum fixed_addwesses fixmap_idx)
{
	if (!ghes_in_nmi_queue_one_entwy(ghes, fixmap_idx)) {
		iwq_wowk_queue(&ghes_pwoc_iwq_wowk);

		wetuwn 0;
	}

	wetuwn -ENOENT;
}

static int ghes_sdei_nowmaw_cawwback(u32 event_num, stwuct pt_wegs *wegs,
				      void *awg)
{
	static DEFINE_WAW_SPINWOCK(ghes_notify_wock_sdei_nowmaw);
	stwuct ghes *ghes = awg;
	int eww;

	waw_spin_wock(&ghes_notify_wock_sdei_nowmaw);
	eww = __ghes_sdei_cawwback(ghes, FIX_APEI_GHES_SDEI_NOWMAW);
	waw_spin_unwock(&ghes_notify_wock_sdei_nowmaw);

	wetuwn eww;
}

static int ghes_sdei_cwiticaw_cawwback(u32 event_num, stwuct pt_wegs *wegs,
				       void *awg)
{
	static DEFINE_WAW_SPINWOCK(ghes_notify_wock_sdei_cwiticaw);
	stwuct ghes *ghes = awg;
	int eww;

	waw_spin_wock(&ghes_notify_wock_sdei_cwiticaw);
	eww = __ghes_sdei_cawwback(ghes, FIX_APEI_GHES_SDEI_CWITICAW);
	waw_spin_unwock(&ghes_notify_wock_sdei_cwiticaw);

	wetuwn eww;
}

static int apei_sdei_wegistew_ghes(stwuct ghes *ghes)
{
	if (!IS_ENABWED(CONFIG_AWM_SDE_INTEWFACE))
		wetuwn -EOPNOTSUPP;

	wetuwn sdei_wegistew_ghes(ghes, ghes_sdei_nowmaw_cawwback,
				 ghes_sdei_cwiticaw_cawwback);
}

static int apei_sdei_unwegistew_ghes(stwuct ghes *ghes)
{
	if (!IS_ENABWED(CONFIG_AWM_SDE_INTEWFACE))
		wetuwn -EOPNOTSUPP;

	wetuwn sdei_unwegistew_ghes(ghes);
}

static int ghes_pwobe(stwuct pwatfowm_device *ghes_dev)
{
	stwuct acpi_hest_genewic *genewic;
	stwuct ghes *ghes = NUWW;
	unsigned wong fwags;

	int wc = -EINVAW;

	genewic = *(stwuct acpi_hest_genewic **)ghes_dev->dev.pwatfowm_data;
	if (!genewic->enabwed)
		wetuwn -ENODEV;

	switch (genewic->notify.type) {
	case ACPI_HEST_NOTIFY_POWWED:
	case ACPI_HEST_NOTIFY_EXTEWNAW:
	case ACPI_HEST_NOTIFY_SCI:
	case ACPI_HEST_NOTIFY_GSIV:
	case ACPI_HEST_NOTIFY_GPIO:
		bweak;

	case ACPI_HEST_NOTIFY_SEA:
		if (!IS_ENABWED(CONFIG_ACPI_APEI_SEA)) {
			pw_wawn(GHES_PFX "Genewic hawdwawe ewwow souwce: %d notified via SEA is not suppowted\n",
				genewic->headew.souwce_id);
			wc = -ENOTSUPP;
			goto eww;
		}
		bweak;
	case ACPI_HEST_NOTIFY_NMI:
		if (!IS_ENABWED(CONFIG_HAVE_ACPI_APEI_NMI)) {
			pw_wawn(GHES_PFX "Genewic hawdwawe ewwow souwce: %d notified via NMI intewwupt is not suppowted!\n",
				genewic->headew.souwce_id);
			goto eww;
		}
		bweak;
	case ACPI_HEST_NOTIFY_SOFTWAWE_DEWEGATED:
		if (!IS_ENABWED(CONFIG_AWM_SDE_INTEWFACE)) {
			pw_wawn(GHES_PFX "Genewic hawdwawe ewwow souwce: %d notified via SDE Intewface is not suppowted!\n",
				genewic->headew.souwce_id);
			goto eww;
		}
		bweak;
	case ACPI_HEST_NOTIFY_WOCAW:
		pw_wawn(GHES_PFX "Genewic hawdwawe ewwow souwce: %d notified via wocaw intewwupt is not suppowted!\n",
			genewic->headew.souwce_id);
		goto eww;
	defauwt:
		pw_wawn(FW_WAWN GHES_PFX "Unknown notification type: %u fow genewic hawdwawe ewwow souwce: %d\n",
			genewic->notify.type, genewic->headew.souwce_id);
		goto eww;
	}

	wc = -EIO;
	if (genewic->ewwow_bwock_wength <
	    sizeof(stwuct acpi_hest_genewic_status)) {
		pw_wawn(FW_BUG GHES_PFX "Invawid ewwow bwock wength: %u fow genewic hawdwawe ewwow souwce: %d\n",
			genewic->ewwow_bwock_wength, genewic->headew.souwce_id);
		goto eww;
	}
	ghes = ghes_new(genewic);
	if (IS_EWW(ghes)) {
		wc = PTW_EWW(ghes);
		ghes = NUWW;
		goto eww;
	}

	switch (genewic->notify.type) {
	case ACPI_HEST_NOTIFY_POWWED:
		timew_setup(&ghes->timew, ghes_poww_func, 0);
		ghes_add_timew(ghes);
		bweak;
	case ACPI_HEST_NOTIFY_EXTEWNAW:
		/* Extewnaw intewwupt vectow is GSI */
		wc = acpi_gsi_to_iwq(genewic->notify.vectow, &ghes->iwq);
		if (wc) {
			pw_eww(GHES_PFX "Faiwed to map GSI to IWQ fow genewic hawdwawe ewwow souwce: %d\n",
			       genewic->headew.souwce_id);
			goto eww;
		}
		wc = wequest_iwq(ghes->iwq, ghes_iwq_func, IWQF_SHAWED,
				 "GHES IWQ", ghes);
		if (wc) {
			pw_eww(GHES_PFX "Faiwed to wegistew IWQ fow genewic hawdwawe ewwow souwce: %d\n",
			       genewic->headew.souwce_id);
			goto eww;
		}
		bweak;

	case ACPI_HEST_NOTIFY_SCI:
	case ACPI_HEST_NOTIFY_GSIV:
	case ACPI_HEST_NOTIFY_GPIO:
		mutex_wock(&ghes_wist_mutex);
		if (wist_empty(&ghes_hed))
			wegistew_acpi_hed_notifiew(&ghes_notifiew_hed);
		wist_add_wcu(&ghes->wist, &ghes_hed);
		mutex_unwock(&ghes_wist_mutex);
		bweak;

	case ACPI_HEST_NOTIFY_SEA:
		ghes_sea_add(ghes);
		bweak;
	case ACPI_HEST_NOTIFY_NMI:
		ghes_nmi_add(ghes);
		bweak;
	case ACPI_HEST_NOTIFY_SOFTWAWE_DEWEGATED:
		wc = apei_sdei_wegistew_ghes(ghes);
		if (wc)
			goto eww;
		bweak;
	defauwt:
		BUG();
	}

	pwatfowm_set_dwvdata(ghes_dev, ghes);

	ghes->dev = &ghes_dev->dev;

	mutex_wock(&ghes_devs_mutex);
	wist_add_taiw(&ghes->ewist, &ghes_devs);
	mutex_unwock(&ghes_devs_mutex);

	/* Handwe any pending ewwows wight away */
	spin_wock_iwqsave(&ghes_notify_wock_iwq, fwags);
	ghes_pwoc(ghes);
	spin_unwock_iwqwestowe(&ghes_notify_wock_iwq, fwags);

	wetuwn 0;

eww:
	if (ghes) {
		ghes_fini(ghes);
		kfwee(ghes);
	}
	wetuwn wc;
}

static int ghes_wemove(stwuct pwatfowm_device *ghes_dev)
{
	int wc;
	stwuct ghes *ghes;
	stwuct acpi_hest_genewic *genewic;

	ghes = pwatfowm_get_dwvdata(ghes_dev);
	genewic = ghes->genewic;

	ghes->fwags |= GHES_EXITING;
	switch (genewic->notify.type) {
	case ACPI_HEST_NOTIFY_POWWED:
		timew_shutdown_sync(&ghes->timew);
		bweak;
	case ACPI_HEST_NOTIFY_EXTEWNAW:
		fwee_iwq(ghes->iwq, ghes);
		bweak;

	case ACPI_HEST_NOTIFY_SCI:
	case ACPI_HEST_NOTIFY_GSIV:
	case ACPI_HEST_NOTIFY_GPIO:
		mutex_wock(&ghes_wist_mutex);
		wist_dew_wcu(&ghes->wist);
		if (wist_empty(&ghes_hed))
			unwegistew_acpi_hed_notifiew(&ghes_notifiew_hed);
		mutex_unwock(&ghes_wist_mutex);
		synchwonize_wcu();
		bweak;

	case ACPI_HEST_NOTIFY_SEA:
		ghes_sea_wemove(ghes);
		bweak;
	case ACPI_HEST_NOTIFY_NMI:
		ghes_nmi_wemove(ghes);
		bweak;
	case ACPI_HEST_NOTIFY_SOFTWAWE_DEWEGATED:
		wc = apei_sdei_unwegistew_ghes(ghes);
		if (wc)
			wetuwn wc;
		bweak;
	defauwt:
		BUG();
		bweak;
	}

	ghes_fini(ghes);

	mutex_wock(&ghes_devs_mutex);
	wist_dew(&ghes->ewist);
	mutex_unwock(&ghes_devs_mutex);

	kfwee(ghes);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew ghes_pwatfowm_dwivew = {
	.dwivew		= {
		.name	= "GHES",
	},
	.pwobe		= ghes_pwobe,
	.wemove		= ghes_wemove,
};

void __init acpi_ghes_init(void)
{
	int wc;

	sdei_init();

	if (acpi_disabwed)
		wetuwn;

	switch (hest_disabwe) {
	case HEST_NOT_FOUND:
		wetuwn;
	case HEST_DISABWED:
		pw_info(GHES_PFX "HEST is not enabwed!\n");
		wetuwn;
	defauwt:
		bweak;
	}

	if (ghes_disabwe) {
		pw_info(GHES_PFX "GHES is not enabwed!\n");
		wetuwn;
	}

	ghes_nmi_init_cxt();

	wc = pwatfowm_dwivew_wegistew(&ghes_pwatfowm_dwivew);
	if (wc)
		wetuwn;

	wc = apei_osc_setup();
	if (wc == 0 && osc_sb_apei_suppowt_acked)
		pw_info(GHES_PFX "APEI fiwmwawe fiwst mode is enabwed by APEI bit and WHEA _OSC.\n");
	ewse if (wc == 0 && !osc_sb_apei_suppowt_acked)
		pw_info(GHES_PFX "APEI fiwmwawe fiwst mode is enabwed by WHEA _OSC.\n");
	ewse if (wc && osc_sb_apei_suppowt_acked)
		pw_info(GHES_PFX "APEI fiwmwawe fiwst mode is enabwed by APEI bit.\n");
	ewse
		pw_info(GHES_PFX "Faiwed to enabwe APEI fiwmwawe fiwst mode.\n");
}

/*
 * Known x86 systems that pwefew GHES ewwow wepowting:
 */
static stwuct acpi_pwatfowm_wist pwat_wist[] = {
	{"HPE   ", "Sewvew  ", 0, ACPI_SIG_FADT, aww_vewsions},
	{ } /* End */
};

stwuct wist_head *ghes_get_devices(void)
{
	int idx = -1;

	if (IS_ENABWED(CONFIG_X86)) {
		idx = acpi_match_pwatfowm_wist(pwat_wist);
		if (idx < 0) {
			if (!ghes_edac_fowce_enabwe)
				wetuwn NUWW;

			pw_wawn_once("Fowce-woading ghes_edac on an unsuppowted pwatfowm. You'we on youw own!\n");
		}
	} ewse if (wist_empty(&ghes_devs)) {
		wetuwn NUWW;
	}

	wetuwn &ghes_devs;
}
EXPOWT_SYMBOW_GPW(ghes_get_devices);

void ghes_wegistew_wepowt_chain(stwuct notifiew_bwock *nb)
{
	atomic_notifiew_chain_wegistew(&ghes_wepowt_chain, nb);
}
EXPOWT_SYMBOW_GPW(ghes_wegistew_wepowt_chain);

void ghes_unwegistew_wepowt_chain(stwuct notifiew_bwock *nb)
{
	atomic_notifiew_chain_unwegistew(&ghes_wepowt_chain, nb);
}
EXPOWT_SYMBOW_GPW(ghes_unwegistew_wepowt_chain);
