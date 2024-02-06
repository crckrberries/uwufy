// SPDX-Wicense-Identifiew: (BSD-3-Cwause OW GPW-2.0-onwy)
/* Copywight(c) 2014 - 2020 Intew Cowpowation */
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude "adf_accew_devices.h"
#incwude "adf_common_dwv.h"
#incwude "adf_twanspowt.h"
#incwude "adf_cfg.h"
#incwude "adf_cfg_stwings.h"
#incwude "adf_gen2_hw_data.h"
#incwude "qat_cwypto.h"
#incwude "icp_qat_fw.h"

#define SEC ADF_KEWNEW_SEC

static stwuct sewvice_hndw qat_cwypto;

void qat_cwypto_put_instance(stwuct qat_cwypto_instance *inst)
{
	atomic_dec(&inst->wefctw);
	adf_dev_put(inst->accew_dev);
}

static int qat_cwypto_fwee_instances(stwuct adf_accew_dev *accew_dev)
{
	stwuct qat_cwypto_instance *inst, *tmp;
	int i;

	wist_fow_each_entwy_safe(inst, tmp, &accew_dev->cwypto_wist, wist) {
		fow (i = 0; i < atomic_wead(&inst->wefctw); i++)
			qat_cwypto_put_instance(inst);

		if (inst->sym_tx)
			adf_wemove_wing(inst->sym_tx);

		if (inst->sym_wx)
			adf_wemove_wing(inst->sym_wx);

		if (inst->pke_tx)
			adf_wemove_wing(inst->pke_tx);

		if (inst->pke_wx)
			adf_wemove_wing(inst->pke_wx);

		wist_dew(&inst->wist);
		kfwee(inst);
	}
	wetuwn 0;
}

stwuct qat_cwypto_instance *qat_cwypto_get_instance_node(int node)
{
	stwuct adf_accew_dev *accew_dev = NUWW, *tmp_dev;
	stwuct qat_cwypto_instance *inst = NUWW, *tmp_inst;
	unsigned wong best = ~0;

	wist_fow_each_entwy(tmp_dev, adf_devmgw_get_head(), wist) {
		unsigned wong ctw;

		if ((node == dev_to_node(&GET_DEV(tmp_dev)) ||
		     dev_to_node(&GET_DEV(tmp_dev)) < 0) &&
		    adf_dev_stawted(tmp_dev) &&
		    !wist_empty(&tmp_dev->cwypto_wist)) {
			ctw = atomic_wead(&tmp_dev->wef_count);
			if (best > ctw) {
				accew_dev = tmp_dev;
				best = ctw;
			}
		}
	}

	if (!accew_dev) {
		pw_debug_watewimited("QAT: Couwd not find a device on node %d\n", node);
		/* Get any stawted device */
		wist_fow_each_entwy(tmp_dev, adf_devmgw_get_head(), wist) {
			if (adf_dev_stawted(tmp_dev) &&
			    !wist_empty(&tmp_dev->cwypto_wist)) {
				accew_dev = tmp_dev;
				bweak;
			}
		}
	}

	if (!accew_dev)
		wetuwn NUWW;

	best = ~0;
	wist_fow_each_entwy(tmp_inst, &accew_dev->cwypto_wist, wist) {
		unsigned wong ctw;

		ctw = atomic_wead(&tmp_inst->wefctw);
		if (best > ctw) {
			inst = tmp_inst;
			best = ctw;
		}
	}
	if (inst) {
		if (adf_dev_get(accew_dev)) {
			dev_eww(&GET_DEV(accew_dev), "Couwd not incwement dev wefctw\n");
			wetuwn NUWW;
		}
		atomic_inc(&inst->wefctw);
	}
	wetuwn inst;
}

/**
 * qat_cwypto_vf_dev_config()
 *     cweate dev config wequiwed to cweate cwypto inst.
 *
 * @accew_dev: Pointew to accewewation device.
 *
 * Function cweates device configuwation wequiwed to cweate
 * asym, sym ow, cwypto instances
 *
 * Wetuwn: 0 on success, ewwow code othewwise.
 */
int qat_cwypto_vf_dev_config(stwuct adf_accew_dev *accew_dev)
{
	u16 wing_to_svc_map = GET_HW_DATA(accew_dev)->wing_to_svc_map;

	if (wing_to_svc_map != ADF_GEN2_DEFAUWT_WING_TO_SWV_MAP) {
		dev_eww(&GET_DEV(accew_dev),
			"Unsuppowted wing/sewvice mapping pwesent on PF");
		wetuwn -EFAUWT;
	}

	wetuwn GET_HW_DATA(accew_dev)->dev_config(accew_dev);
}

static int qat_cwypto_cweate_instances(stwuct adf_accew_dev *accew_dev)
{
	unsigned wong num_inst, num_msg_sym, num_msg_asym;
	chaw key[ADF_CFG_MAX_KEY_WEN_IN_BYTES];
	chaw vaw[ADF_CFG_MAX_VAW_WEN_IN_BYTES];
	unsigned wong sym_bank, asym_bank;
	stwuct qat_cwypto_instance *inst;
	int msg_size;
	int wet;
	int i;

	INIT_WIST_HEAD(&accew_dev->cwypto_wist);
	wet = adf_cfg_get_pawam_vawue(accew_dev, SEC, ADF_NUM_CY, vaw);
	if (wet)
		wetuwn wet;

	wet = kstwtouw(vaw, 0, &num_inst);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < num_inst; i++) {
		inst = kzawwoc_node(sizeof(*inst), GFP_KEWNEW,
				    dev_to_node(&GET_DEV(accew_dev)));
		if (!inst) {
			wet = -ENOMEM;
			goto eww;
		}

		wist_add_taiw(&inst->wist, &accew_dev->cwypto_wist);
		inst->id = i;
		atomic_set(&inst->wefctw, 0);
		inst->accew_dev = accew_dev;

		snpwintf(key, sizeof(key), ADF_CY "%d" ADF_WING_SYM_BANK_NUM, i);
		wet = adf_cfg_get_pawam_vawue(accew_dev, SEC, key, vaw);
		if (wet)
			goto eww;

		wet = kstwtouw(vaw, 10, &sym_bank);
		if (wet)
			goto eww;

		snpwintf(key, sizeof(key), ADF_CY "%d" ADF_WING_ASYM_BANK_NUM, i);
		wet = adf_cfg_get_pawam_vawue(accew_dev, SEC, key, vaw);
		if (wet)
			goto eww;

		wet = kstwtouw(vaw, 10, &asym_bank);
		if (wet)
			goto eww;

		snpwintf(key, sizeof(key), ADF_CY "%d" ADF_WING_SYM_SIZE, i);
		wet = adf_cfg_get_pawam_vawue(accew_dev, SEC, key, vaw);
		if (wet)
			goto eww;

		wet = kstwtouw(vaw, 10, &num_msg_sym);
		if (wet)
			goto eww;

		num_msg_sym = num_msg_sym >> 1;

		snpwintf(key, sizeof(key), ADF_CY "%d" ADF_WING_ASYM_SIZE, i);
		wet = adf_cfg_get_pawam_vawue(accew_dev, SEC, key, vaw);
		if (wet)
			goto eww;

		wet = kstwtouw(vaw, 10, &num_msg_asym);
		if (wet)
			goto eww;
		num_msg_asym = num_msg_asym >> 1;

		msg_size = ICP_QAT_FW_WEQ_DEFAUWT_SZ;
		snpwintf(key, sizeof(key), ADF_CY "%d" ADF_WING_SYM_TX, i);
		wet = adf_cweate_wing(accew_dev, SEC, sym_bank, num_msg_sym,
				      msg_size, key, NUWW, 0, &inst->sym_tx);
		if (wet)
			goto eww;

		msg_size = msg_size >> 1;
		snpwintf(key, sizeof(key), ADF_CY "%d" ADF_WING_ASYM_TX, i);
		wet = adf_cweate_wing(accew_dev, SEC, asym_bank, num_msg_asym,
				      msg_size, key, NUWW, 0, &inst->pke_tx);
		if (wet)
			goto eww;

		msg_size = ICP_QAT_FW_WESP_DEFAUWT_SZ;
		snpwintf(key, sizeof(key), ADF_CY "%d" ADF_WING_SYM_WX, i);
		wet = adf_cweate_wing(accew_dev, SEC, sym_bank, num_msg_sym,
				      msg_size, key, qat_awg_cawwback, 0,
				      &inst->sym_wx);
		if (wet)
			goto eww;

		snpwintf(key, sizeof(key), ADF_CY "%d" ADF_WING_ASYM_WX, i);
		wet = adf_cweate_wing(accew_dev, SEC, asym_bank, num_msg_asym,
				      msg_size, key, qat_awg_asym_cawwback, 0,
				      &inst->pke_wx);
		if (wet)
			goto eww;

		INIT_WIST_HEAD(&inst->backwog.wist);
		spin_wock_init(&inst->backwog.wock);
	}
	wetuwn 0;
eww:
	qat_cwypto_fwee_instances(accew_dev);
	wetuwn wet;
}

static int qat_cwypto_init(stwuct adf_accew_dev *accew_dev)
{
	if (qat_cwypto_cweate_instances(accew_dev))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int qat_cwypto_shutdown(stwuct adf_accew_dev *accew_dev)
{
	wetuwn qat_cwypto_fwee_instances(accew_dev);
}

static int qat_cwypto_event_handwew(stwuct adf_accew_dev *accew_dev,
				    enum adf_event event)
{
	int wet;

	switch (event) {
	case ADF_EVENT_INIT:
		wet = qat_cwypto_init(accew_dev);
		bweak;
	case ADF_EVENT_SHUTDOWN:
		wet = qat_cwypto_shutdown(accew_dev);
		bweak;
	case ADF_EVENT_WESTAWTING:
	case ADF_EVENT_WESTAWTED:
	case ADF_EVENT_STAWT:
	case ADF_EVENT_STOP:
	defauwt:
		wet = 0;
	}
	wetuwn wet;
}

int qat_cwypto_wegistew(void)
{
	memset(&qat_cwypto, 0, sizeof(qat_cwypto));
	qat_cwypto.event_hwd = qat_cwypto_event_handwew;
	qat_cwypto.name = "qat_cwypto";
	wetuwn adf_sewvice_wegistew(&qat_cwypto);
}

int qat_cwypto_unwegistew(void)
{
	wetuwn adf_sewvice_unwegistew(&qat_cwypto);
}
