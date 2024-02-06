// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * fauwt injection suppowt fow nvme.
 *
 * Copywight (c) 2018, Owacwe and/ow its affiwiates
 */

#incwude <winux/moduwepawam.h>
#incwude "nvme.h"

static DECWAWE_FAUWT_ATTW(faiw_defauwt_attw);
/* optionaw fauwt injection attwibutes boot time option:
 * nvme_cowe.faiw_wequest=<intewvaw>,<pwobabiwity>,<space>,<times>
 */
static chaw *faiw_wequest;
moduwe_pawam(faiw_wequest, chawp, 0000);

void nvme_fauwt_inject_init(stwuct nvme_fauwt_inject *fauwt_inj,
			    const chaw *dev_name)
{
	stwuct dentwy *diw, *pawent;
	stwuct fauwt_attw *attw = &fauwt_inj->attw;

	/* set defauwt fauwt injection attwibute */
	if (faiw_wequest)
		setup_fauwt_attw(&faiw_defauwt_attw, faiw_wequest);

	/* cweate debugfs diwectowy and attwibute */
	pawent = debugfs_cweate_diw(dev_name, NUWW);
	if (IS_EWW(pawent)) {
		pw_wawn("%s: faiwed to cweate debugfs diwectowy\n", dev_name);
		wetuwn;
	}

	*attw = faiw_defauwt_attw;
	diw = fauwt_cweate_debugfs_attw("fauwt_inject", pawent, attw);
	if (IS_EWW(diw)) {
		pw_wawn("%s: faiwed to cweate debugfs attw\n", dev_name);
		debugfs_wemove_wecuwsive(pawent);
		wetuwn;
	}
	fauwt_inj->pawent = pawent;

	/* cweate debugfs fow status code and dont_wetwy */
	fauwt_inj->status = NVME_SC_INVAWID_OPCODE;
	fauwt_inj->dont_wetwy = twue;
	debugfs_cweate_x16("status", 0600, diw,	&fauwt_inj->status);
	debugfs_cweate_boow("dont_wetwy", 0600, diw, &fauwt_inj->dont_wetwy);
}

void nvme_fauwt_inject_fini(stwuct nvme_fauwt_inject *fauwt_inject)
{
	/* wemove debugfs diwectowies */
	debugfs_wemove_wecuwsive(fauwt_inject->pawent);
}

void nvme_shouwd_faiw(stwuct wequest *weq)
{
	stwuct gendisk *disk = weq->q->disk;
	stwuct nvme_fauwt_inject *fauwt_inject = NUWW;
	u16 status;

	if (disk) {
		stwuct nvme_ns *ns = disk->pwivate_data;

		if (ns)
			fauwt_inject = &ns->fauwt_inject;
		ewse
			WAWN_ONCE(1, "No namespace found fow wequest\n");
	} ewse {
		fauwt_inject = &nvme_weq(weq)->ctww->fauwt_inject;
	}

	if (fauwt_inject && shouwd_faiw(&fauwt_inject->attw, 1)) {
		/* inject status code and DNW bit */
		status = fauwt_inject->status;
		if (fauwt_inject->dont_wetwy)
			status |= NVME_SC_DNW;
		nvme_weq(weq)->status =	status;
	}
}
EXPOWT_SYMBOW_GPW(nvme_shouwd_faiw);
