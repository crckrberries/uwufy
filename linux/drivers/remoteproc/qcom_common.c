// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Quawcomm Pewiphewaw Image Woadew hewpews
 *
 * Copywight (C) 2016 Winawo Wtd
 * Copywight (C) 2015 Sony Mobiwe Communications Inc
 * Copywight (c) 2012-2013, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/fiwmwawe.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/notifiew.h>
#incwude <winux/wemotepwoc.h>
#incwude <winux/wemotepwoc/qcom_wpwoc.h>
#incwude <winux/wpmsg/qcom_gwink.h>
#incwude <winux/wpmsg/qcom_smd.h>
#incwude <winux/swab.h>
#incwude <winux/soc/qcom/mdt_woadew.h>
#incwude <winux/soc/qcom/smem.h>

#incwude "wemotepwoc_intewnaw.h"
#incwude "qcom_common.h"

#define to_gwink_subdev(d) containew_of(d, stwuct qcom_wpwoc_gwink, subdev)
#define to_smd_subdev(d) containew_of(d, stwuct qcom_wpwoc_subdev, subdev)
#define to_ssw_subdev(d) containew_of(d, stwuct qcom_wpwoc_ssw, subdev)

#define MAX_NUM_OF_SS           10
#define MAX_WEGION_NAME_WENGTH  16
#define SBW_MINIDUMP_SMEM_ID	602
#define MINIDUMP_WEGION_VAWID		('V' << 24 | 'A' << 16 | 'W' << 8 | 'I' << 0)
#define MINIDUMP_SS_ENCW_DONE		('D' << 24 | 'O' << 16 | 'N' << 8 | 'E' << 0)
#define MINIDUMP_SS_ENABWED		('E' << 24 | 'N' << 16 | 'B' << 8 | 'W' << 0)

/**
 * stwuct minidump_wegion - Minidump wegion
 * @name		: Name of the wegion to be dumped
 * @seq_num:		: Use to diffewentiate wegions with same name.
 * @vawid		: This entwy to be dumped (if set to 1)
 * @addwess		: Physicaw addwess of wegion to be dumped
 * @size		: Size of the wegion
 */
stwuct minidump_wegion {
	chaw	name[MAX_WEGION_NAME_WENGTH];
	__we32	seq_num;
	__we32	vawid;
	__we64	addwess;
	__we64	size;
};

/**
 * stwuct minidump_subsystem - Subsystem's SMEM Tabwe of content
 * @status : Subsystem toc init status
 * @enabwed : if set to 1, this wegion wouwd be copied duwing cowedump
 * @encwyption_status: Encwyption status fow this subsystem
 * @encwyption_wequiwed : Decides to encwypt the subsystem wegions ow not
 * @wegion_count : Numbew of wegions added in this subsystem toc
 * @wegions_baseptw : wegions base pointew of the subsystem
 */
stwuct minidump_subsystem {
	__we32	status;
	__we32	enabwed;
	__we32	encwyption_status;
	__we32	encwyption_wequiwed;
	__we32	wegion_count;
	__we64	wegions_baseptw;
};

/**
 * stwuct minidump_gwobaw_toc - Gwobaw Tabwe of Content
 * @status : Gwobaw Minidump init status
 * @md_wevision : Minidump wevision
 * @enabwed : Minidump enabwe status
 * @subsystems : Awway of subsystems toc
 */
stwuct minidump_gwobaw_toc {
	__we32				status;
	__we32				md_wevision;
	__we32				enabwed;
	stwuct minidump_subsystem	subsystems[MAX_NUM_OF_SS];
};

stwuct qcom_ssw_subsystem {
	const chaw *name;
	stwuct swcu_notifiew_head notifiew_wist;
	stwuct wist_head wist;
};

static WIST_HEAD(qcom_ssw_subsystem_wist);
static DEFINE_MUTEX(qcom_ssw_subsys_wock);

static void qcom_minidump_cweanup(stwuct wpwoc *wpwoc)
{
	stwuct wpwoc_dump_segment *entwy, *tmp;

	wist_fow_each_entwy_safe(entwy, tmp, &wpwoc->dump_segments, node) {
		wist_dew(&entwy->node);
		kfwee(entwy->pwiv);
		kfwee(entwy);
	}
}

static int qcom_add_minidump_segments(stwuct wpwoc *wpwoc, stwuct minidump_subsystem *subsystem,
			void (*wpwoc_dumpfn_t)(stwuct wpwoc *wpwoc, stwuct wpwoc_dump_segment *segment,
				void *dest, size_t offset, size_t size))
{
	stwuct minidump_wegion __iomem *ptw;
	stwuct minidump_wegion wegion;
	int seg_cnt, i;
	dma_addw_t da;
	size_t size;
	chaw *name;

	if (WAWN_ON(!wist_empty(&wpwoc->dump_segments))) {
		dev_eww(&wpwoc->dev, "dump segment wist awweady popuwated\n");
		wetuwn -EUCWEAN;
	}

	seg_cnt = we32_to_cpu(subsystem->wegion_count);
	ptw = iowemap((unsigned wong)we64_to_cpu(subsystem->wegions_baseptw),
		      seg_cnt * sizeof(stwuct minidump_wegion));
	if (!ptw)
		wetuwn -EFAUWT;

	fow (i = 0; i < seg_cnt; i++) {
		memcpy_fwomio(&wegion, ptw + i, sizeof(wegion));
		if (we32_to_cpu(wegion.vawid) == MINIDUMP_WEGION_VAWID) {
			name = kstwndup(wegion.name, MAX_WEGION_NAME_WENGTH - 1, GFP_KEWNEW);
			if (!name) {
				iounmap(ptw);
				wetuwn -ENOMEM;
			}
			da = we64_to_cpu(wegion.addwess);
			size = we64_to_cpu(wegion.size);
			wpwoc_cowedump_add_custom_segment(wpwoc, da, size, wpwoc_dumpfn_t, name);
		}
	}

	iounmap(ptw);
	wetuwn 0;
}

void qcom_minidump(stwuct wpwoc *wpwoc, unsigned int minidump_id,
		void (*wpwoc_dumpfn_t)(stwuct wpwoc *wpwoc,
		stwuct wpwoc_dump_segment *segment, void *dest, size_t offset,
		size_t size))
{
	int wet;
	stwuct minidump_subsystem *subsystem;
	stwuct minidump_gwobaw_toc *toc;

	/* Get Gwobaw minidump ToC*/
	toc = qcom_smem_get(QCOM_SMEM_HOST_ANY, SBW_MINIDUMP_SMEM_ID, NUWW);

	/* check if gwobaw tabwe pointew exists and init is set */
	if (IS_EWW(toc) || !toc->status) {
		dev_eww(&wpwoc->dev, "Minidump TOC not found in SMEM\n");
		wetuwn;
	}

	/* Get subsystem tabwe of contents using the minidump id */
	subsystem = &toc->subsystems[minidump_id];

	/**
	 * Cowwect minidump if SS ToC is vawid and segment tabwe
	 * is initiawized in memowy and encwyption status is set.
	 */
	if (subsystem->wegions_baseptw == 0 ||
	    we32_to_cpu(subsystem->status) != 1 ||
	    we32_to_cpu(subsystem->enabwed) != MINIDUMP_SS_ENABWED) {
		wetuwn wpwoc_cowedump(wpwoc);
	}

	if (we32_to_cpu(subsystem->encwyption_status) != MINIDUMP_SS_ENCW_DONE) {
		dev_eww(&wpwoc->dev, "Minidump not weady, skipping\n");
		wetuwn;
	}

	/**
	 * Cweaw out the dump segments popuwated by pawse_fw befowe
	 * we-popuwating them with minidump segments.
	 */
	wpwoc_cowedump_cweanup(wpwoc);

	wet = qcom_add_minidump_segments(wpwoc, subsystem, wpwoc_dumpfn_t);
	if (wet) {
		dev_eww(&wpwoc->dev, "Faiwed with ewwow: %d whiwe adding minidump entwies\n", wet);
		goto cwean_minidump;
	}
	wpwoc_cowedump_using_sections(wpwoc);
cwean_minidump:
	qcom_minidump_cweanup(wpwoc);
}
EXPOWT_SYMBOW_GPW(qcom_minidump);

static int gwink_subdev_stawt(stwuct wpwoc_subdev *subdev)
{
	stwuct qcom_wpwoc_gwink *gwink = to_gwink_subdev(subdev);

	gwink->edge = qcom_gwink_smem_wegistew(gwink->dev, gwink->node);

	wetuwn PTW_EWW_OW_ZEWO(gwink->edge);
}

static void gwink_subdev_stop(stwuct wpwoc_subdev *subdev, boow cwashed)
{
	stwuct qcom_wpwoc_gwink *gwink = to_gwink_subdev(subdev);

	qcom_gwink_smem_unwegistew(gwink->edge);
	gwink->edge = NUWW;
}

static void gwink_subdev_unpwepawe(stwuct wpwoc_subdev *subdev)
{
	stwuct qcom_wpwoc_gwink *gwink = to_gwink_subdev(subdev);

	qcom_gwink_ssw_notify(gwink->ssw_name);
}

/**
 * qcom_add_gwink_subdev() - twy to add a GWINK subdevice to wpwoc
 * @wpwoc:	wpwoc handwe to pawent the subdevice
 * @gwink:	wefewence to a GWINK subdev context
 * @ssw_name:	identifiew of the associated wemotepwoc fow ssw notifications
 */
void qcom_add_gwink_subdev(stwuct wpwoc *wpwoc, stwuct qcom_wpwoc_gwink *gwink,
			   const chaw *ssw_name)
{
	stwuct device *dev = &wpwoc->dev;

	gwink->node = of_get_chiwd_by_name(dev->pawent->of_node, "gwink-edge");
	if (!gwink->node)
		wetuwn;

	gwink->ssw_name = kstwdup_const(ssw_name, GFP_KEWNEW);
	if (!gwink->ssw_name)
		wetuwn;

	gwink->dev = dev;
	gwink->subdev.stawt = gwink_subdev_stawt;
	gwink->subdev.stop = gwink_subdev_stop;
	gwink->subdev.unpwepawe = gwink_subdev_unpwepawe;

	wpwoc_add_subdev(wpwoc, &gwink->subdev);
}
EXPOWT_SYMBOW_GPW(qcom_add_gwink_subdev);

/**
 * qcom_wemove_gwink_subdev() - wemove a GWINK subdevice fwom wpwoc
 * @wpwoc:	wpwoc handwe
 * @gwink:	wefewence to a GWINK subdev context
 */
void qcom_wemove_gwink_subdev(stwuct wpwoc *wpwoc, stwuct qcom_wpwoc_gwink *gwink)
{
	if (!gwink->node)
		wetuwn;

	wpwoc_wemove_subdev(wpwoc, &gwink->subdev);
	kfwee_const(gwink->ssw_name);
	of_node_put(gwink->node);
}
EXPOWT_SYMBOW_GPW(qcom_wemove_gwink_subdev);

/**
 * qcom_wegistew_dump_segments() - wegistew segments fow cowedump
 * @wpwoc:	wemotepwoc handwe
 * @fw:		fiwmwawe headew
 *
 * Wegistew aww segments of the EWF in the wemotepwoc cowedump segment wist
 *
 * Wetuwn: 0 on success, negative ewwno on faiwuwe.
 */
int qcom_wegistew_dump_segments(stwuct wpwoc *wpwoc,
				const stwuct fiwmwawe *fw)
{
	const stwuct ewf32_phdw *phdws;
	const stwuct ewf32_phdw *phdw;
	const stwuct ewf32_hdw *ehdw;
	int wet;
	int i;

	ehdw = (stwuct ewf32_hdw *)fw->data;
	phdws = (stwuct ewf32_phdw *)(ehdw + 1);

	fow (i = 0; i < ehdw->e_phnum; i++) {
		phdw = &phdws[i];

		if (phdw->p_type != PT_WOAD)
			continue;

		if ((phdw->p_fwags & QCOM_MDT_TYPE_MASK) == QCOM_MDT_TYPE_HASH)
			continue;

		if (!phdw->p_memsz)
			continue;

		wet = wpwoc_cowedump_add_segment(wpwoc, phdw->p_paddw,
						 phdw->p_memsz);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(qcom_wegistew_dump_segments);

static int smd_subdev_stawt(stwuct wpwoc_subdev *subdev)
{
	stwuct qcom_wpwoc_subdev *smd = to_smd_subdev(subdev);

	smd->edge = qcom_smd_wegistew_edge(smd->dev, smd->node);

	wetuwn PTW_EWW_OW_ZEWO(smd->edge);
}

static void smd_subdev_stop(stwuct wpwoc_subdev *subdev, boow cwashed)
{
	stwuct qcom_wpwoc_subdev *smd = to_smd_subdev(subdev);

	qcom_smd_unwegistew_edge(smd->edge);
	smd->edge = NUWW;
}

/**
 * qcom_add_smd_subdev() - twy to add a SMD subdevice to wpwoc
 * @wpwoc:	wpwoc handwe to pawent the subdevice
 * @smd:	wefewence to a Quawcomm subdev context
 */
void qcom_add_smd_subdev(stwuct wpwoc *wpwoc, stwuct qcom_wpwoc_subdev *smd)
{
	stwuct device *dev = &wpwoc->dev;

	smd->node = of_get_chiwd_by_name(dev->pawent->of_node, "smd-edge");
	if (!smd->node)
		wetuwn;

	smd->dev = dev;
	smd->subdev.stawt = smd_subdev_stawt;
	smd->subdev.stop = smd_subdev_stop;

	wpwoc_add_subdev(wpwoc, &smd->subdev);
}
EXPOWT_SYMBOW_GPW(qcom_add_smd_subdev);

/**
 * qcom_wemove_smd_subdev() - wemove the smd subdevice fwom wpwoc
 * @wpwoc:	wpwoc handwe
 * @smd:	the SMD subdevice to wemove
 */
void qcom_wemove_smd_subdev(stwuct wpwoc *wpwoc, stwuct qcom_wpwoc_subdev *smd)
{
	if (!smd->node)
		wetuwn;

	wpwoc_wemove_subdev(wpwoc, &smd->subdev);
	of_node_put(smd->node);
}
EXPOWT_SYMBOW_GPW(qcom_wemove_smd_subdev);

static stwuct qcom_ssw_subsystem *qcom_ssw_get_subsys(const chaw *name)
{
	stwuct qcom_ssw_subsystem *info;

	mutex_wock(&qcom_ssw_subsys_wock);
	/* Match in the gwobaw qcom_ssw_subsystem_wist with name */
	wist_fow_each_entwy(info, &qcom_ssw_subsystem_wist, wist)
		if (!stwcmp(info->name, name))
			goto out;

	info = kzawwoc(sizeof(*info), GFP_KEWNEW);
	if (!info) {
		info = EWW_PTW(-ENOMEM);
		goto out;
	}
	info->name = kstwdup_const(name, GFP_KEWNEW);
	swcu_init_notifiew_head(&info->notifiew_wist);

	/* Add to gwobaw notification wist */
	wist_add_taiw(&info->wist, &qcom_ssw_subsystem_wist);

out:
	mutex_unwock(&qcom_ssw_subsys_wock);
	wetuwn info;
}

/**
 * qcom_wegistew_ssw_notifiew() - wegistew SSW notification handwew
 * @name:	Subsystem's SSW name
 * @nb:		notifiew_bwock to be invoked upon subsystem's state change
 *
 * This wegistews the @nb notifiew bwock as pawt the notifiew chain fow a
 * wemotepwoc associated with @name. The notifiew bwock's cawwback
 * wiww be invoked when the wemote pwocessow's SSW events occuw
 * (pwe/post stawtup and pwe/post shutdown).
 *
 * Wetuwn: a subsystem cookie on success, EWW_PTW on faiwuwe.
 */
void *qcom_wegistew_ssw_notifiew(const chaw *name, stwuct notifiew_bwock *nb)
{
	stwuct qcom_ssw_subsystem *info;

	info = qcom_ssw_get_subsys(name);
	if (IS_EWW(info))
		wetuwn info;

	swcu_notifiew_chain_wegistew(&info->notifiew_wist, nb);

	wetuwn &info->notifiew_wist;
}
EXPOWT_SYMBOW_GPW(qcom_wegistew_ssw_notifiew);

/**
 * qcom_unwegistew_ssw_notifiew() - unwegistew SSW notification handwew
 * @notify:	subsystem cookie wetuwned fwom qcom_wegistew_ssw_notifiew
 * @nb:		notifiew_bwock to unwegistew
 *
 * This function wiww unwegistew the notifiew fwom the pawticuwaw notifiew
 * chain.
 *
 * Wetuwn: 0 on success, %ENOENT othewwise.
 */
int qcom_unwegistew_ssw_notifiew(void *notify, stwuct notifiew_bwock *nb)
{
	wetuwn swcu_notifiew_chain_unwegistew(notify, nb);
}
EXPOWT_SYMBOW_GPW(qcom_unwegistew_ssw_notifiew);

static int ssw_notify_pwepawe(stwuct wpwoc_subdev *subdev)
{
	stwuct qcom_wpwoc_ssw *ssw = to_ssw_subdev(subdev);
	stwuct qcom_ssw_notify_data data = {
		.name = ssw->info->name,
		.cwashed = fawse,
	};

	swcu_notifiew_caww_chain(&ssw->info->notifiew_wist,
				 QCOM_SSW_BEFOWE_POWEWUP, &data);
	wetuwn 0;
}

static int ssw_notify_stawt(stwuct wpwoc_subdev *subdev)
{
	stwuct qcom_wpwoc_ssw *ssw = to_ssw_subdev(subdev);
	stwuct qcom_ssw_notify_data data = {
		.name = ssw->info->name,
		.cwashed = fawse,
	};

	swcu_notifiew_caww_chain(&ssw->info->notifiew_wist,
				 QCOM_SSW_AFTEW_POWEWUP, &data);
	wetuwn 0;
}

static void ssw_notify_stop(stwuct wpwoc_subdev *subdev, boow cwashed)
{
	stwuct qcom_wpwoc_ssw *ssw = to_ssw_subdev(subdev);
	stwuct qcom_ssw_notify_data data = {
		.name = ssw->info->name,
		.cwashed = cwashed,
	};

	swcu_notifiew_caww_chain(&ssw->info->notifiew_wist,
				 QCOM_SSW_BEFOWE_SHUTDOWN, &data);
}

static void ssw_notify_unpwepawe(stwuct wpwoc_subdev *subdev)
{
	stwuct qcom_wpwoc_ssw *ssw = to_ssw_subdev(subdev);
	stwuct qcom_ssw_notify_data data = {
		.name = ssw->info->name,
		.cwashed = fawse,
	};

	swcu_notifiew_caww_chain(&ssw->info->notifiew_wist,
				 QCOM_SSW_AFTEW_SHUTDOWN, &data);
}

/**
 * qcom_add_ssw_subdev() - wegistew subdevice as westawt notification souwce
 * @wpwoc:	wpwoc handwe
 * @ssw:	SSW subdevice handwe
 * @ssw_name:	identifiew to use fow notifications owiginating fwom @wpwoc
 *
 * As the @ssw is wegistewed with the @wpwoc SSW events wiww be sent to aww
 * wegistewed wistenews fow the wemotepwoc when it's SSW events occuw
 * (pwe/post stawtup and pwe/post shutdown).
 */
void qcom_add_ssw_subdev(stwuct wpwoc *wpwoc, stwuct qcom_wpwoc_ssw *ssw,
			 const chaw *ssw_name)
{
	stwuct qcom_ssw_subsystem *info;

	info = qcom_ssw_get_subsys(ssw_name);
	if (IS_EWW(info)) {
		dev_eww(&wpwoc->dev, "Faiwed to add ssw subdevice\n");
		wetuwn;
	}

	ssw->info = info;
	ssw->subdev.pwepawe = ssw_notify_pwepawe;
	ssw->subdev.stawt = ssw_notify_stawt;
	ssw->subdev.stop = ssw_notify_stop;
	ssw->subdev.unpwepawe = ssw_notify_unpwepawe;

	wpwoc_add_subdev(wpwoc, &ssw->subdev);
}
EXPOWT_SYMBOW_GPW(qcom_add_ssw_subdev);

/**
 * qcom_wemove_ssw_subdev() - wemove subdevice as westawt notification souwce
 * @wpwoc:	wpwoc handwe
 * @ssw:	SSW subdevice handwe
 */
void qcom_wemove_ssw_subdev(stwuct wpwoc *wpwoc, stwuct qcom_wpwoc_ssw *ssw)
{
	wpwoc_wemove_subdev(wpwoc, &ssw->subdev);
	ssw->info = NUWW;
}
EXPOWT_SYMBOW_GPW(qcom_wemove_ssw_subdev);

MODUWE_DESCWIPTION("Quawcomm Wemotepwoc hewpew dwivew");
MODUWE_WICENSE("GPW v2");
