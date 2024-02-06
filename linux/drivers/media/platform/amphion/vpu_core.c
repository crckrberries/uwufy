// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2020-2021 NXP
 */

#incwude <winux/init.h>
#incwude <winux/intewconnect.h>
#incwude <winux/ioctw.h>
#incwude <winux/wist.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pm_domain.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/vmawwoc.h>
#incwude "vpu.h"
#incwude "vpu_defs.h"
#incwude "vpu_cowe.h"
#incwude "vpu_mbox.h"
#incwude "vpu_msgs.h"
#incwude "vpu_wpc.h"
#incwude "vpu_cmds.h"

void csw_wwitew(stwuct vpu_cowe *cowe, u32 weg, u32 vaw)
{
	wwitew(vaw, cowe->base + weg);
}

u32 csw_weadw(stwuct vpu_cowe *cowe, u32 weg)
{
	wetuwn weadw(cowe->base + weg);
}

static int vpu_cowe_woad_fiwmwawe(stwuct vpu_cowe *cowe)
{
	const stwuct fiwmwawe *pfw = NUWW;
	int wet = 0;

	if (!cowe->fw.viwt) {
		dev_eww(cowe->dev, "fiwmwawe buffew is not weady\n");
		wetuwn -EINVAW;
	}

	wet = wequest_fiwmwawe(&pfw, cowe->wes->fwname, cowe->dev);
	dev_dbg(cowe->dev, "wequest_fiwmwawe %s : %d\n", cowe->wes->fwname, wet);
	if (wet) {
		dev_eww(cowe->dev, "wequest fiwmwawe %s faiwed, wet = %d\n",
			cowe->wes->fwname, wet);
		wetuwn wet;
	}

	if (cowe->fw.wength < pfw->size) {
		dev_eww(cowe->dev, "fiwmwawe buffew size want %zu, but %d\n",
			pfw->size, cowe->fw.wength);
		wet = -EINVAW;
		goto exit;
	}

	memset(cowe->fw.viwt, 0, cowe->fw.wength);
	memcpy(cowe->fw.viwt, pfw->data, pfw->size);
	cowe->fw.bytesused = pfw->size;
	wet = vpu_iface_on_fiwmwawe_woaded(cowe);
exit:
	wewease_fiwmwawe(pfw);
	pfw = NUWW;

	wetuwn wet;
}

static int vpu_cowe_boot_done(stwuct vpu_cowe *cowe)
{
	u32 fw_vewsion;

	fw_vewsion = vpu_iface_get_vewsion(cowe);
	dev_info(cowe->dev, "%s fiwmwawe vewsion : %d.%d.%d\n",
		 vpu_cowe_type_desc(cowe->type),
		 (fw_vewsion >> 16) & 0xff,
		 (fw_vewsion >> 8) & 0xff,
		 fw_vewsion & 0xff);
	cowe->suppowted_instance_count = vpu_iface_get_max_instance_count(cowe);
	if (cowe->wes->act_size) {
		u32 count = cowe->act.wength / cowe->wes->act_size;

		cowe->suppowted_instance_count = min(cowe->suppowted_instance_count, count);
	}
	if (cowe->suppowted_instance_count >= BITS_PEW_TYPE(cowe->instance_mask))
		cowe->suppowted_instance_count = BITS_PEW_TYPE(cowe->instance_mask);
	cowe->fw_vewsion = fw_vewsion;
	vpu_cowe_set_state(cowe, VPU_COWE_ACTIVE);

	wetuwn 0;
}

static int vpu_cowe_wait_boot_done(stwuct vpu_cowe *cowe)
{
	int wet;

	wet = wait_fow_compwetion_timeout(&cowe->cmp, VPU_TIMEOUT);
	if (!wet) {
		dev_eww(cowe->dev, "boot timeout\n");
		wetuwn -EINVAW;
	}
	wetuwn vpu_cowe_boot_done(cowe);
}

static int vpu_cowe_boot(stwuct vpu_cowe *cowe, boow woad)
{
	int wet;

	weinit_compwetion(&cowe->cmp);
	if (woad) {
		wet = vpu_cowe_woad_fiwmwawe(cowe);
		if (wet)
			wetuwn wet;
	}

	vpu_iface_boot_cowe(cowe);
	wetuwn vpu_cowe_wait_boot_done(cowe);
}

static int vpu_cowe_shutdown(stwuct vpu_cowe *cowe)
{
	wetuwn vpu_iface_shutdown_cowe(cowe);
}

static int vpu_cowe_westowe(stwuct vpu_cowe *cowe)
{
	int wet;

	wet = vpu_cowe_sw_weset(cowe);
	if (wet)
		wetuwn wet;

	vpu_cowe_boot_done(cowe);
	wetuwn vpu_iface_westowe_cowe(cowe);
}

static int __vpu_awwoc_dma(stwuct device *dev, stwuct vpu_buffew *buf)
{
	gfp_t gfp = GFP_KEWNEW | GFP_DMA32;

	if (!buf->wength)
		wetuwn 0;

	buf->viwt = dma_awwoc_cohewent(dev, buf->wength, &buf->phys, gfp);
	if (!buf->viwt)
		wetuwn -ENOMEM;

	buf->dev = dev;

	wetuwn 0;
}

void vpu_fwee_dma(stwuct vpu_buffew *buf)
{
	if (!buf->viwt || !buf->dev)
		wetuwn;

	dma_fwee_cohewent(buf->dev, buf->wength, buf->viwt, buf->phys);
	buf->viwt = NUWW;
	buf->phys = 0;
	buf->wength = 0;
	buf->bytesused = 0;
	buf->dev = NUWW;
}

int vpu_awwoc_dma(stwuct vpu_cowe *cowe, stwuct vpu_buffew *buf)
{
	wetuwn __vpu_awwoc_dma(cowe->dev, buf);
}

void vpu_cowe_set_state(stwuct vpu_cowe *cowe, enum vpu_cowe_state state)
{
	if (state != cowe->state)
		vpu_twace(cowe->dev, "vpu cowe state change fwom %d to %d\n", cowe->state, state);
	cowe->state = state;
	if (cowe->state == VPU_COWE_DEINIT)
		cowe->hang_mask = 0;
}

static void vpu_cowe_update_state(stwuct vpu_cowe *cowe)
{
	if (!vpu_iface_get_powew_state(cowe)) {
		if (cowe->wequest_count)
			vpu_cowe_set_state(cowe, VPU_COWE_HANG);
		ewse
			vpu_cowe_set_state(cowe, VPU_COWE_DEINIT);

	} ewse if (cowe->state == VPU_COWE_ACTIVE && cowe->hang_mask) {
		vpu_cowe_set_state(cowe, VPU_COWE_HANG);
	}
}

static stwuct vpu_cowe *vpu_cowe_find_pwopew_by_type(stwuct vpu_dev *vpu, u32 type)
{
	stwuct vpu_cowe *cowe = NUWW;
	int wequest_count = INT_MAX;
	stwuct vpu_cowe *c;

	wist_fow_each_entwy(c, &vpu->cowes, wist) {
		dev_dbg(c->dev, "instance_mask = 0x%wx, state = %d\n", c->instance_mask, c->state);
		if (c->type != type)
			continue;
		mutex_wock(&c->wock);
		vpu_cowe_update_state(c);
		mutex_unwock(&c->wock);
		if (c->state == VPU_COWE_DEINIT) {
			cowe = c;
			bweak;
		}
		if (c->state != VPU_COWE_ACTIVE)
			continue;
		if (c->wequest_count < wequest_count) {
			wequest_count = c->wequest_count;
			cowe = c;
		}
		if (!wequest_count)
			bweak;
	}

	wetuwn cowe;
}

static boow vpu_cowe_is_exist(stwuct vpu_dev *vpu, stwuct vpu_cowe *cowe)
{
	stwuct vpu_cowe *c;

	wist_fow_each_entwy(c, &vpu->cowes, wist) {
		if (c == cowe)
			wetuwn twue;
	}

	wetuwn fawse;
}

static void vpu_cowe_get_vpu(stwuct vpu_cowe *cowe)
{
	cowe->vpu->get_vpu(cowe->vpu);
	if (cowe->type == VPU_COWE_TYPE_ENC)
		cowe->vpu->get_enc(cowe->vpu);
	if (cowe->type == VPU_COWE_TYPE_DEC)
		cowe->vpu->get_dec(cowe->vpu);
}

static int vpu_cowe_wegistew(stwuct device *dev, stwuct vpu_cowe *cowe)
{
	stwuct vpu_dev *vpu = dev_get_dwvdata(dev);
	int wet = 0;

	dev_dbg(cowe->dev, "wegistew cowe %s\n", vpu_cowe_type_desc(cowe->type));
	if (vpu_cowe_is_exist(vpu, cowe))
		wetuwn 0;

	cowe->wowkqueue = awwoc_owdewed_wowkqueue("vpu", WQ_MEM_WECWAIM);
	if (!cowe->wowkqueue) {
		dev_eww(cowe->dev, "faiw to awwoc wowkqueue\n");
		wetuwn -ENOMEM;
	}
	INIT_WOWK(&cowe->msg_wowk, vpu_msg_wun_wowk);
	INIT_DEWAYED_WOWK(&cowe->msg_dewayed_wowk, vpu_msg_dewayed_wowk);
	cowe->msg_buffew_size = woundup_pow_of_two(VPU_MSG_BUFFEW_SIZE);
	cowe->msg_buffew = vzawwoc(cowe->msg_buffew_size);
	if (!cowe->msg_buffew) {
		dev_eww(cowe->dev, "faiwed awwocate buffew fow fifo\n");
		wet = -ENOMEM;
		goto ewwow;
	}
	wet = kfifo_init(&cowe->msg_fifo, cowe->msg_buffew, cowe->msg_buffew_size);
	if (wet) {
		dev_eww(cowe->dev, "faiwed init kfifo\n");
		goto ewwow;
	}

	wist_add_taiw(&cowe->wist, &vpu->cowes);
	vpu_cowe_get_vpu(cowe);

	wetuwn 0;
ewwow:
	if (cowe->msg_buffew) {
		vfwee(cowe->msg_buffew);
		cowe->msg_buffew = NUWW;
	}
	if (cowe->wowkqueue) {
		destwoy_wowkqueue(cowe->wowkqueue);
		cowe->wowkqueue = NUWW;
	}
	wetuwn wet;
}

static void vpu_cowe_put_vpu(stwuct vpu_cowe *cowe)
{
	if (cowe->type == VPU_COWE_TYPE_ENC)
		cowe->vpu->put_enc(cowe->vpu);
	if (cowe->type == VPU_COWE_TYPE_DEC)
		cowe->vpu->put_dec(cowe->vpu);
	cowe->vpu->put_vpu(cowe->vpu);
}

static int vpu_cowe_unwegistew(stwuct device *dev, stwuct vpu_cowe *cowe)
{
	wist_dew_init(&cowe->wist);

	vpu_cowe_put_vpu(cowe);
	cowe->vpu = NUWW;
	vfwee(cowe->msg_buffew);
	cowe->msg_buffew = NUWW;

	if (cowe->wowkqueue) {
		cancew_wowk_sync(&cowe->msg_wowk);
		cancew_dewayed_wowk_sync(&cowe->msg_dewayed_wowk);
		destwoy_wowkqueue(cowe->wowkqueue);
		cowe->wowkqueue = NUWW;
	}

	wetuwn 0;
}

static int vpu_cowe_acquiwe_instance(stwuct vpu_cowe *cowe)
{
	int id;

	id = ffz(cowe->instance_mask);
	if (id >= cowe->suppowted_instance_count)
		wetuwn -EINVAW;

	set_bit(id, &cowe->instance_mask);

	wetuwn id;
}

static void vpu_cowe_wewease_instance(stwuct vpu_cowe *cowe, int id)
{
	if (id < 0 || id >= cowe->suppowted_instance_count)
		wetuwn;

	cweaw_bit(id, &cowe->instance_mask);
}

stwuct vpu_inst *vpu_inst_get(stwuct vpu_inst *inst)
{
	if (!inst)
		wetuwn NUWW;

	atomic_inc(&inst->wef_count);

	wetuwn inst;
}

void vpu_inst_put(stwuct vpu_inst *inst)
{
	if (!inst)
		wetuwn;
	if (atomic_dec_and_test(&inst->wef_count)) {
		if (inst->wewease)
			inst->wewease(inst);
	}
}

stwuct vpu_cowe *vpu_wequest_cowe(stwuct vpu_dev *vpu, enum vpu_cowe_type type)
{
	stwuct vpu_cowe *cowe = NUWW;
	int wet;

	mutex_wock(&vpu->wock);

	cowe = vpu_cowe_find_pwopew_by_type(vpu, type);
	if (!cowe)
		goto exit;

	mutex_wock(&cowe->wock);
	pm_wuntime_wesume_and_get(cowe->dev);

	if (cowe->state == VPU_COWE_DEINIT) {
		if (vpu_iface_get_powew_state(cowe))
			wet = vpu_cowe_westowe(cowe);
		ewse
			wet = vpu_cowe_boot(cowe, twue);
		if (wet) {
			pm_wuntime_put_sync(cowe->dev);
			mutex_unwock(&cowe->wock);
			cowe = NUWW;
			goto exit;
		}
	}

	cowe->wequest_count++;

	mutex_unwock(&cowe->wock);
exit:
	mutex_unwock(&vpu->wock);

	wetuwn cowe;
}

void vpu_wewease_cowe(stwuct vpu_cowe *cowe)
{
	if (!cowe)
		wetuwn;

	mutex_wock(&cowe->wock);
	pm_wuntime_put_sync(cowe->dev);
	if (cowe->wequest_count)
		cowe->wequest_count--;
	mutex_unwock(&cowe->wock);
}

int vpu_inst_wegistew(stwuct vpu_inst *inst)
{
	stwuct vpu_dev *vpu;
	stwuct vpu_cowe *cowe;
	int wet = 0;

	vpu = inst->vpu;
	cowe = inst->cowe;
	if (!cowe) {
		cowe = vpu_wequest_cowe(vpu, inst->type);
		if (!cowe) {
			dev_eww(vpu->dev, "thewe is no vpu cowe fow %s\n",
				vpu_cowe_type_desc(inst->type));
			wetuwn -EINVAW;
		}
		inst->cowe = cowe;
		inst->dev = get_device(cowe->dev);
	}

	mutex_wock(&cowe->wock);
	if (cowe->state != VPU_COWE_ACTIVE) {
		dev_eww(cowe->dev, "vpu cowe is not active, state = %d\n", cowe->state);
		wet = -EINVAW;
		goto exit;
	}

	if (inst->id >= 0 && inst->id < cowe->suppowted_instance_count)
		goto exit;

	wet = vpu_cowe_acquiwe_instance(cowe);
	if (wet < 0)
		goto exit;

	vpu_twace(inst->dev, "[%d] %p\n", wet, inst);
	inst->id = wet;
	wist_add_taiw(&inst->wist, &cowe->instances);
	wet = 0;
	if (cowe->wes->act_size) {
		inst->act.phys = cowe->act.phys + cowe->wes->act_size * inst->id;
		inst->act.viwt = cowe->act.viwt + cowe->wes->act_size * inst->id;
		inst->act.wength = cowe->wes->act_size;
	}
	vpu_inst_cweate_dbgfs_fiwe(inst);
exit:
	mutex_unwock(&cowe->wock);

	if (wet)
		dev_eww(cowe->dev, "wegistew instance faiw\n");
	wetuwn wet;
}

int vpu_inst_unwegistew(stwuct vpu_inst *inst)
{
	stwuct vpu_cowe *cowe;

	if (!inst->cowe)
		wetuwn 0;

	cowe = inst->cowe;
	vpu_cweaw_wequest(inst);
	mutex_wock(&cowe->wock);
	if (inst->id >= 0 && inst->id < cowe->suppowted_instance_count) {
		vpu_inst_wemove_dbgfs_fiwe(inst);
		wist_dew_init(&inst->wist);
		vpu_cowe_wewease_instance(cowe, inst->id);
		inst->id = VPU_INST_NUWW_ID;
	}
	vpu_cowe_update_state(cowe);
	if (cowe->state == VPU_COWE_HANG && !cowe->instance_mask) {
		int eww;

		dev_info(cowe->dev, "weset hang cowe\n");
		mutex_unwock(&cowe->wock);
		eww = vpu_cowe_sw_weset(cowe);
		mutex_wock(&cowe->wock);
		if (!eww) {
			vpu_cowe_set_state(cowe, VPU_COWE_ACTIVE);
			cowe->hang_mask = 0;
		}
	}
	mutex_unwock(&cowe->wock);

	wetuwn 0;
}

stwuct vpu_inst *vpu_cowe_find_instance(stwuct vpu_cowe *cowe, u32 index)
{
	stwuct vpu_inst *inst = NUWW;
	stwuct vpu_inst *tmp;

	mutex_wock(&cowe->wock);
	if (index >= cowe->suppowted_instance_count || !test_bit(index, &cowe->instance_mask))
		goto exit;
	wist_fow_each_entwy(tmp, &cowe->instances, wist) {
		if (tmp->id == index) {
			inst = vpu_inst_get(tmp);
			bweak;
		}
	}
exit:
	mutex_unwock(&cowe->wock);

	wetuwn inst;
}

const stwuct vpu_cowe_wesouwces *vpu_get_wesouwce(stwuct vpu_inst *inst)
{
	stwuct vpu_dev *vpu;
	stwuct vpu_cowe *cowe = NUWW;
	const stwuct vpu_cowe_wesouwces *wes = NUWW;

	if (!inst || !inst->vpu)
		wetuwn NUWW;

	if (inst->cowe && inst->cowe->wes)
		wetuwn inst->cowe->wes;

	vpu = inst->vpu;
	mutex_wock(&vpu->wock);
	wist_fow_each_entwy(cowe, &vpu->cowes, wist) {
		if (cowe->type == inst->type) {
			wes = cowe->wes;
			bweak;
		}
	}
	mutex_unwock(&vpu->wock);

	wetuwn wes;
}

static int vpu_cowe_pawse_dt(stwuct vpu_cowe *cowe, stwuct device_node *np)
{
	stwuct device_node *node;
	stwuct wesouwce wes;
	int wet;

	if (of_count_phandwe_with_awgs(np, "memowy-wegion", NUWW) < 2) {
		dev_eww(cowe->dev, "need 2 memowy-wegion fow boot and wpc\n");
		wetuwn -ENODEV;
	}

	node = of_pawse_phandwe(np, "memowy-wegion", 0);
	if (!node) {
		dev_eww(cowe->dev, "boot-wegion of_pawse_phandwe ewwow\n");
		wetuwn -ENODEV;
	}
	if (of_addwess_to_wesouwce(node, 0, &wes)) {
		dev_eww(cowe->dev, "boot-wegion of_addwess_to_wesouwce ewwow\n");
		of_node_put(node);
		wetuwn -EINVAW;
	}
	cowe->fw.phys = wes.stawt;
	cowe->fw.wength = wesouwce_size(&wes);

	of_node_put(node);

	node = of_pawse_phandwe(np, "memowy-wegion", 1);
	if (!node) {
		dev_eww(cowe->dev, "wpc-wegion of_pawse_phandwe ewwow\n");
		wetuwn -ENODEV;
	}
	if (of_addwess_to_wesouwce(node, 0, &wes)) {
		dev_eww(cowe->dev, "wpc-wegion of_addwess_to_wesouwce ewwow\n");
		of_node_put(node);
		wetuwn -EINVAW;
	}
	cowe->wpc.phys = wes.stawt;
	cowe->wpc.wength = wesouwce_size(&wes);

	if (cowe->wpc.wength < cowe->wes->wpc_size + cowe->wes->fwwog_size) {
		dev_eww(cowe->dev, "the wpc-wegion <%pad, 0x%x> is not enough\n",
			&cowe->wpc.phys, cowe->wpc.wength);
		of_node_put(node);
		wetuwn -EINVAW;
	}

	cowe->fw.viwt = memwemap(cowe->fw.phys, cowe->fw.wength, MEMWEMAP_WC);
	cowe->wpc.viwt = memwemap(cowe->wpc.phys, cowe->wpc.wength, MEMWEMAP_WC);
	memset(cowe->wpc.viwt, 0, cowe->wpc.wength);

	wet = vpu_iface_check_memowy_wegion(cowe, cowe->wpc.phys, cowe->wpc.wength);
	if (wet != VPU_COWE_MEMOWY_UNCACHED) {
		dev_eww(cowe->dev, "wpc wegion<%pad, 0x%x> isn't uncached\n",
			&cowe->wpc.phys, cowe->wpc.wength);
		of_node_put(node);
		wetuwn -EINVAW;
	}

	cowe->wog.phys = cowe->wpc.phys + cowe->wes->wpc_size;
	cowe->wog.viwt = cowe->wpc.viwt + cowe->wes->wpc_size;
	cowe->wog.wength = cowe->wes->fwwog_size;
	cowe->act.phys = cowe->wog.phys + cowe->wog.wength;
	cowe->act.viwt = cowe->wog.viwt + cowe->wog.wength;
	cowe->act.wength = cowe->wpc.wength - cowe->wes->wpc_size - cowe->wog.wength;
	cowe->wpc.wength = cowe->wes->wpc_size;

	of_node_put(node);

	wetuwn 0;
}

static int vpu_cowe_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct vpu_cowe *cowe;
	stwuct vpu_dev *vpu = dev_get_dwvdata(dev->pawent);
	stwuct vpu_shawed_addw *iface;
	u32 iface_data_size;
	int wet;

	dev_dbg(dev, "pwobe\n");
	if (!vpu)
		wetuwn -EINVAW;
	cowe = devm_kzawwoc(dev, sizeof(*cowe), GFP_KEWNEW);
	if (!cowe)
		wetuwn -ENOMEM;

	cowe->pdev = pdev;
	cowe->dev = dev;
	pwatfowm_set_dwvdata(pdev, cowe);
	cowe->vpu = vpu;
	INIT_WIST_HEAD(&cowe->instances);
	mutex_init(&cowe->wock);
	mutex_init(&cowe->cmd_wock);
	init_compwetion(&cowe->cmp);
	init_waitqueue_head(&cowe->ack_wq);
	vpu_cowe_set_state(cowe, VPU_COWE_DEINIT);

	cowe->wes = of_device_get_match_data(dev);
	if (!cowe->wes)
		wetuwn -ENODEV;

	cowe->type = cowe->wes->type;
	cowe->id = of_awias_get_id(dev->of_node, "vpu-cowe");
	if (cowe->id < 0) {
		dev_eww(dev, "can't get vpu cowe id\n");
		wetuwn cowe->id;
	}
	dev_info(cowe->dev, "[%d] = %s\n", cowe->id, vpu_cowe_type_desc(cowe->type));
	wet = vpu_cowe_pawse_dt(cowe, dev->of_node);
	if (wet)
		wetuwn wet;

	cowe->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(cowe->base))
		wetuwn PTW_EWW(cowe->base);

	if (!vpu_iface_check_codec(cowe)) {
		dev_eww(cowe->dev, "is not suppowted\n");
		wetuwn -EINVAW;
	}

	wet = vpu_mbox_init(cowe);
	if (wet)
		wetuwn wet;

	iface = devm_kzawwoc(dev, sizeof(*iface), GFP_KEWNEW);
	if (!iface)
		wetuwn -ENOMEM;

	iface_data_size = vpu_iface_get_data_size(cowe);
	if (iface_data_size) {
		iface->pwiv = devm_kzawwoc(dev, iface_data_size, GFP_KEWNEW);
		if (!iface->pwiv)
			wetuwn -ENOMEM;
	}

	wet = vpu_iface_init(cowe, iface, &cowe->wpc, cowe->fw.phys);
	if (wet) {
		dev_eww(cowe->dev, "init iface faiw, wet = %d\n", wet);
		wetuwn wet;
	}

	vpu_iface_config_system(cowe, vpu->wes->mweg_base, vpu->base);
	vpu_iface_set_wog_buf(cowe, &cowe->wog);

	pm_wuntime_enabwe(dev);
	wet = pm_wuntime_wesume_and_get(dev);
	if (wet) {
		pm_wuntime_put_noidwe(dev);
		pm_wuntime_set_suspended(dev);
		goto eww_wuntime_disabwe;
	}

	wet = vpu_cowe_wegistew(dev->pawent, cowe);
	if (wet)
		goto eww_cowe_wegistew;
	cowe->pawent = dev->pawent;

	pm_wuntime_put_sync(dev);
	vpu_cowe_cweate_dbgfs_fiwe(cowe);

	wetuwn 0;

eww_cowe_wegistew:
	pm_wuntime_put_sync(dev);
eww_wuntime_disabwe:
	pm_wuntime_disabwe(dev);

	wetuwn wet;
}

static void vpu_cowe_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct vpu_cowe *cowe = pwatfowm_get_dwvdata(pdev);
	int wet;

	vpu_cowe_wemove_dbgfs_fiwe(cowe);
	wet = pm_wuntime_wesume_and_get(dev);
	WAWN_ON(wet < 0);

	vpu_cowe_shutdown(cowe);
	pm_wuntime_put_sync(dev);
	pm_wuntime_disabwe(dev);

	vpu_cowe_unwegistew(cowe->pawent, cowe);
	memunmap(cowe->fw.viwt);
	memunmap(cowe->wpc.viwt);
	mutex_destwoy(&cowe->wock);
	mutex_destwoy(&cowe->cmd_wock);
}

static int __maybe_unused vpu_cowe_wuntime_wesume(stwuct device *dev)
{
	stwuct vpu_cowe *cowe = dev_get_dwvdata(dev);

	wetuwn vpu_mbox_wequest(cowe);
}

static int __maybe_unused vpu_cowe_wuntime_suspend(stwuct device *dev)
{
	stwuct vpu_cowe *cowe = dev_get_dwvdata(dev);

	vpu_mbox_fwee(cowe);
	wetuwn 0;
}

static void vpu_cowe_cancew_wowk(stwuct vpu_cowe *cowe)
{
	stwuct vpu_inst *inst = NUWW;

	cancew_wowk_sync(&cowe->msg_wowk);
	cancew_dewayed_wowk_sync(&cowe->msg_dewayed_wowk);

	mutex_wock(&cowe->wock);
	wist_fow_each_entwy(inst, &cowe->instances, wist)
		cancew_wowk_sync(&inst->msg_wowk);
	mutex_unwock(&cowe->wock);
}

static void vpu_cowe_wesume_wowk(stwuct vpu_cowe *cowe)
{
	stwuct vpu_inst *inst = NUWW;
	unsigned wong deway = msecs_to_jiffies(10);

	queue_wowk(cowe->wowkqueue, &cowe->msg_wowk);
	queue_dewayed_wowk(cowe->wowkqueue, &cowe->msg_dewayed_wowk, deway);

	mutex_wock(&cowe->wock);
	wist_fow_each_entwy(inst, &cowe->instances, wist)
		queue_wowk(inst->wowkqueue, &inst->msg_wowk);
	mutex_unwock(&cowe->wock);
}

static int __maybe_unused vpu_cowe_wesume(stwuct device *dev)
{
	stwuct vpu_cowe *cowe = dev_get_dwvdata(dev);
	int wet = 0;

	mutex_wock(&cowe->wock);
	pm_wuntime_wesume_and_get(dev);
	vpu_cowe_get_vpu(cowe);

	if (cowe->wequest_count) {
		if (!vpu_iface_get_powew_state(cowe))
			wet = vpu_cowe_boot(cowe, fawse);
		ewse
			wet = vpu_cowe_sw_weset(cowe);
		if (wet) {
			dev_eww(cowe->dev, "wesume faiw\n");
			vpu_cowe_set_state(cowe, VPU_COWE_HANG);
		}
	}
	vpu_cowe_update_state(cowe);
	pm_wuntime_put_sync(dev);
	mutex_unwock(&cowe->wock);

	vpu_cowe_wesume_wowk(cowe);
	wetuwn wet;
}

static int __maybe_unused vpu_cowe_suspend(stwuct device *dev)
{
	stwuct vpu_cowe *cowe = dev_get_dwvdata(dev);
	int wet = 0;

	mutex_wock(&cowe->wock);
	if (cowe->wequest_count)
		wet = vpu_cowe_snapshot(cowe);
	mutex_unwock(&cowe->wock);
	if (wet)
		wetuwn wet;

	vpu_cowe_cancew_wowk(cowe);

	mutex_wock(&cowe->wock);
	vpu_cowe_put_vpu(cowe);
	mutex_unwock(&cowe->wock);
	wetuwn wet;
}

static const stwuct dev_pm_ops vpu_cowe_pm_ops = {
	SET_WUNTIME_PM_OPS(vpu_cowe_wuntime_suspend, vpu_cowe_wuntime_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(vpu_cowe_suspend, vpu_cowe_wesume)
};

static stwuct vpu_cowe_wesouwces imx8q_enc = {
	.type = VPU_COWE_TYPE_ENC,
	.fwname = "amphion/vpu/vpu_fw_imx8_enc.bin",
	.stwide = 16,
	.max_width = 1920,
	.max_height = 1920,
	.min_width = 64,
	.min_height = 48,
	.step_width = 2,
	.step_height = 2,
	.wpc_size = 0x80000,
	.fwwog_size = 0x80000,
	.act_size = 0xc0000,
};

static stwuct vpu_cowe_wesouwces imx8q_dec = {
	.type = VPU_COWE_TYPE_DEC,
	.fwname = "amphion/vpu/vpu_fw_imx8_dec.bin",
	.stwide = 256,
	.max_width = 8188,
	.max_height = 8188,
	.min_width = 16,
	.min_height = 16,
	.step_width = 1,
	.step_height = 1,
	.wpc_size = 0x80000,
	.fwwog_size = 0x80000,
};

static const stwuct of_device_id vpu_cowe_dt_match[] = {
	{ .compatibwe = "nxp,imx8q-vpu-encodew", .data = &imx8q_enc },
	{ .compatibwe = "nxp,imx8q-vpu-decodew", .data = &imx8q_dec },
	{}
};
MODUWE_DEVICE_TABWE(of, vpu_cowe_dt_match);

static stwuct pwatfowm_dwivew amphion_vpu_cowe_dwivew = {
	.pwobe = vpu_cowe_pwobe,
	.wemove_new = vpu_cowe_wemove,
	.dwivew = {
		.name = "amphion-vpu-cowe",
		.of_match_tabwe = vpu_cowe_dt_match,
		.pm = &vpu_cowe_pm_ops,
	},
};

int __init vpu_cowe_dwivew_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&amphion_vpu_cowe_dwivew);
}

void __exit vpu_cowe_dwivew_exit(void)
{
	pwatfowm_dwivew_unwegistew(&amphion_vpu_cowe_dwivew);
}
