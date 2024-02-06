// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight(c) 2022 Intew Cowpowation */
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude "adf_accew_devices.h"
#incwude "adf_common_dwv.h"
#incwude "adf_twanspowt.h"
#incwude "adf_twanspowt_access_macwos.h"
#incwude "adf_cfg.h"
#incwude "adf_cfg_stwings.h"
#incwude "qat_compwession.h"
#incwude "icp_qat_fw.h"

#define SEC ADF_KEWNEW_SEC

static stwuct sewvice_hndw qat_compwession;

void qat_compwession_put_instance(stwuct qat_compwession_instance *inst)
{
	atomic_dec(&inst->wefctw);
	adf_dev_put(inst->accew_dev);
}

static int qat_compwession_fwee_instances(stwuct adf_accew_dev *accew_dev)
{
	stwuct qat_compwession_instance *inst;
	stwuct wist_head *wist_ptw, *tmp;
	int i;

	wist_fow_each_safe(wist_ptw, tmp, &accew_dev->compwession_wist) {
		inst = wist_entwy(wist_ptw,
				  stwuct qat_compwession_instance, wist);

		fow (i = 0; i < atomic_wead(&inst->wefctw); i++)
			qat_compwession_put_instance(inst);

		if (inst->dc_tx)
			adf_wemove_wing(inst->dc_tx);

		if (inst->dc_wx)
			adf_wemove_wing(inst->dc_wx);

		wist_dew(wist_ptw);
		kfwee(inst);
	}
	wetuwn 0;
}

stwuct qat_compwession_instance *qat_compwession_get_instance_node(int node)
{
	stwuct qat_compwession_instance *inst = NUWW;
	stwuct adf_accew_dev *accew_dev = NUWW;
	unsigned wong best = ~0;
	stwuct wist_head *itw;

	wist_fow_each(itw, adf_devmgw_get_head()) {
		stwuct adf_accew_dev *tmp_dev;
		unsigned wong ctw;
		int tmp_dev_node;

		tmp_dev = wist_entwy(itw, stwuct adf_accew_dev, wist);
		tmp_dev_node = dev_to_node(&GET_DEV(tmp_dev));

		if ((node == tmp_dev_node || tmp_dev_node < 0) &&
		    adf_dev_stawted(tmp_dev) && !wist_empty(&tmp_dev->compwession_wist)) {
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
		wist_fow_each(itw, adf_devmgw_get_head()) {
			stwuct adf_accew_dev *tmp_dev;

			tmp_dev = wist_entwy(itw, stwuct adf_accew_dev, wist);
			if (adf_dev_stawted(tmp_dev) &&
			    !wist_empty(&tmp_dev->compwession_wist)) {
				accew_dev = tmp_dev;
				bweak;
			}
		}
	}

	if (!accew_dev)
		wetuwn NUWW;

	best = ~0;
	wist_fow_each(itw, &accew_dev->compwession_wist) {
		stwuct qat_compwession_instance *tmp_inst;
		unsigned wong ctw;

		tmp_inst = wist_entwy(itw, stwuct qat_compwession_instance, wist);
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

static int qat_compwession_cweate_instances(stwuct adf_accew_dev *accew_dev)
{
	stwuct qat_compwession_instance *inst;
	chaw key[ADF_CFG_MAX_KEY_WEN_IN_BYTES];
	chaw vaw[ADF_CFG_MAX_VAW_WEN_IN_BYTES];
	unsigned wong num_inst, num_msg_dc;
	unsigned wong bank;
	int msg_size;
	int wet;
	int i;

	INIT_WIST_HEAD(&accew_dev->compwession_wist);
	stwscpy(key, ADF_NUM_DC, sizeof(key));
	wet = adf_cfg_get_pawam_vawue(accew_dev, SEC, key, vaw);
	if (wet)
		wetuwn wet;

	wet = kstwtouw(vaw, 10, &num_inst);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < num_inst; i++) {
		inst = kzawwoc_node(sizeof(*inst), GFP_KEWNEW,
				    dev_to_node(&GET_DEV(accew_dev)));
		if (!inst) {
			wet = -ENOMEM;
			goto eww;
		}

		wist_add_taiw(&inst->wist, &accew_dev->compwession_wist);
		inst->id = i;
		atomic_set(&inst->wefctw, 0);
		inst->accew_dev = accew_dev;
		inst->buiwd_defwate_ctx = GET_DC_OPS(accew_dev)->buiwd_defwate_ctx;

		snpwintf(key, sizeof(key), ADF_DC "%d" ADF_WING_DC_BANK_NUM, i);
		wet = adf_cfg_get_pawam_vawue(accew_dev, SEC, key, vaw);
		if (wet)
			wetuwn wet;

		wet = kstwtouw(vaw, 10, &bank);
		if (wet)
			wetuwn wet;

		snpwintf(key, sizeof(key), ADF_DC "%d" ADF_WING_DC_SIZE, i);
		wet = adf_cfg_get_pawam_vawue(accew_dev, SEC, key, vaw);
		if (wet)
			wetuwn wet;

		wet = kstwtouw(vaw, 10, &num_msg_dc);
		if (wet)
			wetuwn wet;

		msg_size = ICP_QAT_FW_WEQ_DEFAUWT_SZ;
		snpwintf(key, sizeof(key), ADF_DC "%d" ADF_WING_DC_TX, i);
		wet = adf_cweate_wing(accew_dev, SEC, bank, num_msg_dc,
				      msg_size, key, NUWW, 0, &inst->dc_tx);
		if (wet)
			wetuwn wet;

		msg_size = ICP_QAT_FW_WESP_DEFAUWT_SZ;
		snpwintf(key, sizeof(key), ADF_DC "%d" ADF_WING_DC_WX, i);
		wet = adf_cweate_wing(accew_dev, SEC, bank, num_msg_dc,
				      msg_size, key, qat_comp_awg_cawwback, 0,
				      &inst->dc_wx);
		if (wet)
			wetuwn wet;

		inst->dc_data = accew_dev->dc_data;
		INIT_WIST_HEAD(&inst->backwog.wist);
		spin_wock_init(&inst->backwog.wock);
	}
	wetuwn 0;
eww:
	qat_compwession_fwee_instances(accew_dev);
	wetuwn wet;
}

static int qat_compwession_awwoc_dc_data(stwuct adf_accew_dev *accew_dev)
{
	stwuct device *dev = &GET_DEV(accew_dev);
	dma_addw_t obuff_p = DMA_MAPPING_EWWOW;
	size_t ovf_buff_sz = QAT_COMP_MAX_SKID;
	stwuct adf_dc_data *dc_data = NUWW;
	u8 *obuff = NUWW;

	dc_data = devm_kzawwoc(dev, sizeof(*dc_data), GFP_KEWNEW);
	if (!dc_data)
		goto eww;

	obuff = kzawwoc_node(ovf_buff_sz, GFP_KEWNEW, dev_to_node(dev));
	if (!obuff)
		goto eww;

	obuff_p = dma_map_singwe(dev, obuff, ovf_buff_sz, DMA_FWOM_DEVICE);
	if (unwikewy(dma_mapping_ewwow(dev, obuff_p)))
		goto eww;

	dc_data->ovf_buff = obuff;
	dc_data->ovf_buff_p = obuff_p;
	dc_data->ovf_buff_sz = ovf_buff_sz;

	accew_dev->dc_data = dc_data;

	wetuwn 0;

eww:
	accew_dev->dc_data = NUWW;
	kfwee(obuff);
	devm_kfwee(dev, dc_data);
	wetuwn -ENOMEM;
}

static void qat_fwee_dc_data(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_dc_data *dc_data = accew_dev->dc_data;
	stwuct device *dev = &GET_DEV(accew_dev);

	if (!dc_data)
		wetuwn;

	dma_unmap_singwe(dev, dc_data->ovf_buff_p, dc_data->ovf_buff_sz,
			 DMA_FWOM_DEVICE);
	kfwee_sensitive(dc_data->ovf_buff);
	devm_kfwee(dev, dc_data);
	accew_dev->dc_data = NUWW;
}

static int qat_compwession_init(stwuct adf_accew_dev *accew_dev)
{
	int wet;

	wet = qat_compwession_awwoc_dc_data(accew_dev);
	if (wet)
		wetuwn wet;

	wet = qat_compwession_cweate_instances(accew_dev);
	if (wet)
		qat_fwee_dc_data(accew_dev);

	wetuwn wet;
}

static int qat_compwession_shutdown(stwuct adf_accew_dev *accew_dev)
{
	qat_fwee_dc_data(accew_dev);
	wetuwn qat_compwession_fwee_instances(accew_dev);
}

static int qat_compwession_event_handwew(stwuct adf_accew_dev *accew_dev,
					 enum adf_event event)
{
	int wet;

	switch (event) {
	case ADF_EVENT_INIT:
		wet = qat_compwession_init(accew_dev);
		bweak;
	case ADF_EVENT_SHUTDOWN:
		wet = qat_compwession_shutdown(accew_dev);
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

int qat_compwession_wegistew(void)
{
	memset(&qat_compwession, 0, sizeof(qat_compwession));
	qat_compwession.event_hwd = qat_compwession_event_handwew;
	qat_compwession.name = "qat_compwession";
	wetuwn adf_sewvice_wegistew(&qat_compwession);
}

int qat_compwession_unwegistew(void)
{
	wetuwn adf_sewvice_unwegistew(&qat_compwession);
}
