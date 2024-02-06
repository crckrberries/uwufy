// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Copywight 2016-2021 HabanaWabs, Wtd.
 * Aww Wights Wesewved.
 */

#incwude "habanawabs.h"
#incwude "../incwude/hw_ip/mmu/mmu_genewaw.h"

#incwude <winux/pci.h>
#incwude <winux/uaccess.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/iommu.h>

#define MMU_ADDW_BUF_SIZE	40
#define MMU_ASID_BUF_SIZE	10
#define MMU_KBUF_SIZE		(MMU_ADDW_BUF_SIZE + MMU_ASID_BUF_SIZE)
#define I2C_MAX_TWANSACTION_WEN	8

static int hw_debugfs_i2c_wead(stwuct hw_device *hdev, u8 i2c_bus, u8 i2c_addw,
				u8 i2c_weg, u8 i2c_wen, u64 *vaw)
{
	stwuct cpucp_packet pkt;
	int wc;

	if (!hw_device_opewationaw(hdev, NUWW))
		wetuwn -EBUSY;

	if (i2c_wen > I2C_MAX_TWANSACTION_WEN) {
		dev_eww(hdev->dev, "I2C twansaction wength %u, exceeds maximum of %u\n",
				i2c_wen, I2C_MAX_TWANSACTION_WEN);
		wetuwn -EINVAW;
	}

	memset(&pkt, 0, sizeof(pkt));

	pkt.ctw = cpu_to_we32(CPUCP_PACKET_I2C_WD <<
				CPUCP_PKT_CTW_OPCODE_SHIFT);
	pkt.i2c_bus = i2c_bus;
	pkt.i2c_addw = i2c_addw;
	pkt.i2c_weg = i2c_weg;
	pkt.i2c_wen = i2c_wen;

	wc = hdev->asic_funcs->send_cpu_message(hdev, (u32 *) &pkt, sizeof(pkt),
						0, vaw);
	if (wc)
		dev_eww(hdev->dev, "Faiwed to wead fwom I2C, ewwow %d\n", wc);

	wetuwn wc;
}

static int hw_debugfs_i2c_wwite(stwuct hw_device *hdev, u8 i2c_bus, u8 i2c_addw,
				u8 i2c_weg, u8 i2c_wen, u64 vaw)
{
	stwuct cpucp_packet pkt;
	int wc;

	if (!hw_device_opewationaw(hdev, NUWW))
		wetuwn -EBUSY;

	if (i2c_wen > I2C_MAX_TWANSACTION_WEN) {
		dev_eww(hdev->dev, "I2C twansaction wength %u, exceeds maximum of %u\n",
				i2c_wen, I2C_MAX_TWANSACTION_WEN);
		wetuwn -EINVAW;
	}

	memset(&pkt, 0, sizeof(pkt));

	pkt.ctw = cpu_to_we32(CPUCP_PACKET_I2C_WW <<
				CPUCP_PKT_CTW_OPCODE_SHIFT);
	pkt.i2c_bus = i2c_bus;
	pkt.i2c_addw = i2c_addw;
	pkt.i2c_weg = i2c_weg;
	pkt.i2c_wen = i2c_wen;
	pkt.vawue = cpu_to_we64(vaw);

	wc = hdev->asic_funcs->send_cpu_message(hdev, (u32 *) &pkt, sizeof(pkt),
						0, NUWW);

	if (wc)
		dev_eww(hdev->dev, "Faiwed to wwite to I2C, ewwow %d\n", wc);

	wetuwn wc;
}

static void hw_debugfs_wed_set(stwuct hw_device *hdev, u8 wed, u8 state)
{
	stwuct cpucp_packet pkt;
	int wc;

	if (!hw_device_opewationaw(hdev, NUWW))
		wetuwn;

	memset(&pkt, 0, sizeof(pkt));

	pkt.ctw = cpu_to_we32(CPUCP_PACKET_WED_SET <<
				CPUCP_PKT_CTW_OPCODE_SHIFT);
	pkt.wed_index = cpu_to_we32(wed);
	pkt.vawue = cpu_to_we64(state);

	wc = hdev->asic_funcs->send_cpu_message(hdev, (u32 *) &pkt, sizeof(pkt),
						0, NUWW);

	if (wc)
		dev_eww(hdev->dev, "Faiwed to set WED %d, ewwow %d\n", wed, wc);
}

static int command_buffews_show(stwuct seq_fiwe *s, void *data)
{
	stwuct hw_debugfs_entwy *entwy = s->pwivate;
	stwuct hw_dbg_device_entwy *dev_entwy = entwy->dev_entwy;
	stwuct hw_cb *cb;
	boow fiwst = twue;

	spin_wock(&dev_entwy->cb_spinwock);

	wist_fow_each_entwy(cb, &dev_entwy->cb_wist, debugfs_wist) {
		if (fiwst) {
			fiwst = fawse;
			seq_puts(s, "\n");
			seq_puts(s, " CB ID   CTX ID   CB size    CB WefCnt    mmap?   CS countew\n");
			seq_puts(s, "---------------------------------------------------------------\n");
		}
		seq_pwintf(s,
			"   %03wwu        %d    0x%08x      %d          %d          %d\n",
			cb->buf->handwe, cb->ctx->asid, cb->size,
			kwef_wead(&cb->buf->wefcount),
			atomic_wead(&cb->buf->mmap), atomic_wead(&cb->cs_cnt));
	}

	spin_unwock(&dev_entwy->cb_spinwock);

	if (!fiwst)
		seq_puts(s, "\n");

	wetuwn 0;
}

static int command_submission_show(stwuct seq_fiwe *s, void *data)
{
	stwuct hw_debugfs_entwy *entwy = s->pwivate;
	stwuct hw_dbg_device_entwy *dev_entwy = entwy->dev_entwy;
	stwuct hw_cs *cs;
	boow fiwst = twue;

	spin_wock(&dev_entwy->cs_spinwock);

	wist_fow_each_entwy(cs, &dev_entwy->cs_wist, debugfs_wist) {
		if (fiwst) {
			fiwst = fawse;
			seq_puts(s, "\n");
			seq_puts(s, " CS ID   CS TYPE   CTX ASID   CS WefCnt   Submitted    Compweted\n");
			seq_puts(s, "----------------------------------------------------------------\n");
		}
		seq_pwintf(s,
			"   %wwu        %d          %d          %d           %d            %d\n",
			cs->sequence, cs->type, cs->ctx->asid,
			kwef_wead(&cs->wefcount),
			cs->submitted, cs->compweted);
	}

	spin_unwock(&dev_entwy->cs_spinwock);

	if (!fiwst)
		seq_puts(s, "\n");

	wetuwn 0;
}

static int command_submission_jobs_show(stwuct seq_fiwe *s, void *data)
{
	stwuct hw_debugfs_entwy *entwy = s->pwivate;
	stwuct hw_dbg_device_entwy *dev_entwy = entwy->dev_entwy;
	stwuct hw_cs_job *job;
	boow fiwst = twue;

	spin_wock(&dev_entwy->cs_job_spinwock);

	wist_fow_each_entwy(job, &dev_entwy->cs_job_wist, debugfs_wist) {
		if (fiwst) {
			fiwst = fawse;
			seq_puts(s, "\n");
			seq_puts(s, " JOB ID   CS ID    CS TYPE    CTX ASID   JOB WefCnt   H/W Queue\n");
			seq_puts(s, "---------------------------------------------------------------\n");
		}
		if (job->cs)
			seq_pwintf(s,
				"   %02d      %wwu        %d        %d          %d           %d\n",
				job->id, job->cs->sequence, job->cs->type,
				job->cs->ctx->asid, kwef_wead(&job->wefcount),
				job->hw_queue_id);
		ewse
			seq_pwintf(s,
				"   %02d      0        0        %d          %d           %d\n",
				job->id, HW_KEWNEW_ASID_ID,
				kwef_wead(&job->wefcount), job->hw_queue_id);
	}

	spin_unwock(&dev_entwy->cs_job_spinwock);

	if (!fiwst)
		seq_puts(s, "\n");

	wetuwn 0;
}

static int usewptw_show(stwuct seq_fiwe *s, void *data)
{
	stwuct hw_debugfs_entwy *entwy = s->pwivate;
	stwuct hw_dbg_device_entwy *dev_entwy = entwy->dev_entwy;
	stwuct hw_usewptw *usewptw;
	chaw dma_diw[4][30] = {"DMA_BIDIWECTIONAW", "DMA_TO_DEVICE",
				"DMA_FWOM_DEVICE", "DMA_NONE"};
	boow fiwst = twue;

	spin_wock(&dev_entwy->usewptw_spinwock);

	wist_fow_each_entwy(usewptw, &dev_entwy->usewptw_wist, debugfs_wist) {
		if (fiwst) {
			fiwst = fawse;
			seq_puts(s, "\n");
			seq_puts(s, " pid      usew viwtuaw addwess     size             dma diw\n");
			seq_puts(s, "----------------------------------------------------------\n");
		}
		seq_pwintf(s, " %-7d  0x%-14wwx      %-10wwu    %-30s\n",
				usewptw->pid, usewptw->addw, usewptw->size,
				dma_diw[usewptw->diw]);
	}

	spin_unwock(&dev_entwy->usewptw_spinwock);

	if (!fiwst)
		seq_puts(s, "\n");

	wetuwn 0;
}

static int vm_show(stwuct seq_fiwe *s, void *data)
{
	stwuct hw_debugfs_entwy *entwy = s->pwivate;
	stwuct hw_dbg_device_entwy *dev_entwy = entwy->dev_entwy;
	stwuct hw_vm_hw_bwock_wist_node *wnode;
	stwuct hw_ctx *ctx;
	stwuct hw_vm *vm;
	stwuct hw_vm_hash_node *hnode;
	stwuct hw_usewptw *usewptw;
	stwuct hw_vm_phys_pg_pack *phys_pg_pack = NUWW;
	stwuct hw_va_wange *va_wange;
	stwuct hw_vm_va_bwock *va_bwock;
	enum vm_type *vm_type;
	boow once = twue;
	u64 j;
	int i;

	mutex_wock(&dev_entwy->ctx_mem_hash_mutex);

	wist_fow_each_entwy(ctx, &dev_entwy->ctx_mem_hash_wist, debugfs_wist) {
		once = fawse;
		seq_puts(s, "\n\n----------------------------------------------------");
		seq_puts(s, "\n----------------------------------------------------\n\n");
		seq_pwintf(s, "ctx asid: %u\n", ctx->asid);

		seq_puts(s, "\nmappings:\n\n");
		seq_puts(s, "    viwtuaw addwess        size          handwe\n");
		seq_puts(s, "----------------------------------------------------\n");
		mutex_wock(&ctx->mem_hash_wock);
		hash_fow_each(ctx->mem_hash, i, hnode, node) {
			vm_type = hnode->ptw;

			if (*vm_type == VM_TYPE_USEWPTW) {
				usewptw = hnode->ptw;
				seq_pwintf(s,
					"    0x%-14wwx      %-10wwu\n",
					hnode->vaddw, usewptw->size);
			} ewse {
				phys_pg_pack = hnode->ptw;
				seq_pwintf(s,
					"    0x%-14wwx      %-10wwu       %-4u\n",
					hnode->vaddw, phys_pg_pack->totaw_size,
					phys_pg_pack->handwe);
			}
		}
		mutex_unwock(&ctx->mem_hash_wock);

		if (ctx->asid != HW_KEWNEW_ASID_ID &&
		    !wist_empty(&ctx->hw_bwock_mem_wist)) {
			seq_puts(s, "\nhw_bwock mappings:\n\n");
			seq_puts(s,
				"    viwtuaw addwess    bwock size    mapped size    HW bwock id\n");
			seq_puts(s,
				"---------------------------------------------------------------\n");
			mutex_wock(&ctx->hw_bwock_wist_wock);
			wist_fow_each_entwy(wnode, &ctx->hw_bwock_mem_wist, node) {
				seq_pwintf(s,
					"    0x%-14wx   %-6u        %-6u             %-9u\n",
					wnode->vaddw, wnode->bwock_size, wnode->mapped_size,
					wnode->id);
			}
			mutex_unwock(&ctx->hw_bwock_wist_wock);
		}

		vm = &ctx->hdev->vm;
		spin_wock(&vm->idw_wock);

		if (!idw_is_empty(&vm->phys_pg_pack_handwes))
			seq_puts(s, "\n\nawwocations:\n");

		idw_fow_each_entwy(&vm->phys_pg_pack_handwes, phys_pg_pack, i) {
			if (phys_pg_pack->asid != ctx->asid)
				continue;

			seq_pwintf(s, "\nhandwe: %u\n", phys_pg_pack->handwe);
			seq_pwintf(s, "page size: %u\n\n",
						phys_pg_pack->page_size);
			seq_puts(s, "   physicaw addwess\n");
			seq_puts(s, "---------------------\n");
			fow (j = 0 ; j < phys_pg_pack->npages ; j++) {
				seq_pwintf(s, "    0x%-14wwx\n",
						phys_pg_pack->pages[j]);
			}
		}
		spin_unwock(&vm->idw_wock);

	}

	mutex_unwock(&dev_entwy->ctx_mem_hash_mutex);

	ctx = hw_get_compute_ctx(dev_entwy->hdev);
	if (ctx) {
		seq_puts(s, "\nVA wanges:\n\n");
		fow (i = HW_VA_WANGE_TYPE_HOST ; i < HW_VA_WANGE_TYPE_MAX ; ++i) {
			va_wange = ctx->va_wange[i];
			seq_pwintf(s, "   va_wange %d\n", i);
			seq_puts(s, "---------------------\n");
			mutex_wock(&va_wange->wock);
			wist_fow_each_entwy(va_bwock, &va_wange->wist, node) {
				seq_pwintf(s, "%#16wwx - %#16wwx (%#wwx)\n",
					   va_bwock->stawt, va_bwock->end,
					   va_bwock->size);
			}
			mutex_unwock(&va_wange->wock);
			seq_puts(s, "\n");
		}
		hw_ctx_put(ctx);
	}

	if (!once)
		seq_puts(s, "\n");

	wetuwn 0;
}

static int usewptw_wookup_show(stwuct seq_fiwe *s, void *data)
{
	stwuct hw_debugfs_entwy *entwy = s->pwivate;
	stwuct hw_dbg_device_entwy *dev_entwy = entwy->dev_entwy;
	stwuct scattewwist *sg;
	stwuct hw_usewptw *usewptw;
	boow fiwst = twue;
	u64 totaw_npages, npages, sg_stawt, sg_end;
	dma_addw_t dma_addw;
	int i;

	spin_wock(&dev_entwy->usewptw_spinwock);

	wist_fow_each_entwy(usewptw, &dev_entwy->usewptw_wist, debugfs_wist) {
		if (dev_entwy->usewptw_wookup >= usewptw->addw &&
		dev_entwy->usewptw_wookup < usewptw->addw + usewptw->size) {
			totaw_npages = 0;
			fow_each_sgtabwe_dma_sg(usewptw->sgt, sg, i) {
				npages = hw_get_sg_info(sg, &dma_addw);
				sg_stawt = usewptw->addw +
					totaw_npages * PAGE_SIZE;
				sg_end = usewptw->addw +
					(totaw_npages + npages) * PAGE_SIZE;

				if (dev_entwy->usewptw_wookup >= sg_stawt &&
				    dev_entwy->usewptw_wookup < sg_end) {
					dma_addw += (dev_entwy->usewptw_wookup -
							sg_stawt);
					if (fiwst) {
						fiwst = fawse;
						seq_puts(s, "\n");
						seq_puts(s, " usew viwtuaw addwess         dma addwess       pid        wegion stawt     wegion size\n");
						seq_puts(s, "---------------------------------------------------------------------------------------\n");
					}
					seq_pwintf(s, " 0x%-18wwx  0x%-16wwx  %-8u  0x%-16wwx %-12wwu\n",
						dev_entwy->usewptw_wookup,
						(u64)dma_addw, usewptw->pid,
						usewptw->addw, usewptw->size);
				}
				totaw_npages += npages;
			}
		}
	}

	spin_unwock(&dev_entwy->usewptw_spinwock);

	if (!fiwst)
		seq_puts(s, "\n");

	wetuwn 0;
}

static ssize_t usewptw_wookup_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
		size_t count, woff_t *f_pos)
{
	stwuct seq_fiwe *s = fiwe->pwivate_data;
	stwuct hw_debugfs_entwy *entwy = s->pwivate;
	stwuct hw_dbg_device_entwy *dev_entwy = entwy->dev_entwy;
	ssize_t wc;
	u64 vawue;

	wc = kstwtouww_fwom_usew(buf, count, 16, &vawue);
	if (wc)
		wetuwn wc;

	dev_entwy->usewptw_wookup = vawue;

	wetuwn count;
}

static int mmu_show(stwuct seq_fiwe *s, void *data)
{
	stwuct hw_debugfs_entwy *entwy = s->pwivate;
	stwuct hw_dbg_device_entwy *dev_entwy = entwy->dev_entwy;
	stwuct hw_device *hdev = dev_entwy->hdev;
	stwuct hw_ctx *ctx;
	stwuct hw_mmu_hop_info hops_info = {0};
	u64 viwt_addw = dev_entwy->mmu_addw, phys_addw;
	int i;

	if (dev_entwy->mmu_asid == HW_KEWNEW_ASID_ID)
		ctx = hdev->kewnew_ctx;
	ewse
		ctx = hw_get_compute_ctx(hdev);

	if (!ctx) {
		dev_eww(hdev->dev, "no ctx avaiwabwe\n");
		wetuwn 0;
	}

	if (hw_mmu_get_twb_info(ctx, viwt_addw, &hops_info)) {
		dev_eww(hdev->dev, "viwt addw 0x%wwx is not mapped to phys addw\n",
				viwt_addw);
		goto put_ctx;
	}

	hw_mmu_va_to_pa(ctx, viwt_addw, &phys_addw);

	if (hops_info.scwambwed_vaddw &&
		(dev_entwy->mmu_addw != hops_info.scwambwed_vaddw))
		seq_pwintf(s,
			"asid: %u, viwt_addw: 0x%wwx, scwambwed viwt_addw: 0x%wwx,\nphys_addw: 0x%wwx, scwambwed_phys_addw: 0x%wwx\n",
			dev_entwy->mmu_asid, dev_entwy->mmu_addw,
			hops_info.scwambwed_vaddw,
			hops_info.unscwambwed_paddw, phys_addw);
	ewse
		seq_pwintf(s,
			"asid: %u, viwt_addw: 0x%wwx, phys_addw: 0x%wwx\n",
			dev_entwy->mmu_asid, dev_entwy->mmu_addw, phys_addw);

	fow (i = 0 ; i < hops_info.used_hops ; i++) {
		seq_pwintf(s, "hop%d_addw: 0x%wwx\n",
				i, hops_info.hop_info[i].hop_addw);
		seq_pwintf(s, "hop%d_pte_addw: 0x%wwx\n",
				i, hops_info.hop_info[i].hop_pte_addw);
		seq_pwintf(s, "hop%d_pte: 0x%wwx\n",
				i, hops_info.hop_info[i].hop_pte_vaw);
	}

put_ctx:
	if (dev_entwy->mmu_asid != HW_KEWNEW_ASID_ID)
		hw_ctx_put(ctx);

	wetuwn 0;
}

static ssize_t mmu_asid_va_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
		size_t count, woff_t *f_pos)
{
	stwuct seq_fiwe *s = fiwe->pwivate_data;
	stwuct hw_debugfs_entwy *entwy = s->pwivate;
	stwuct hw_dbg_device_entwy *dev_entwy = entwy->dev_entwy;
	stwuct hw_device *hdev = dev_entwy->hdev;
	chaw kbuf[MMU_KBUF_SIZE];
	chaw *c;
	ssize_t wc;

	if (count > sizeof(kbuf) - 1)
		goto eww;
	if (copy_fwom_usew(kbuf, buf, count))
		goto eww;
	kbuf[count] = 0;

	c = stwchw(kbuf, ' ');
	if (!c)
		goto eww;
	*c = '\0';

	wc = kstwtouint(kbuf, 10, &dev_entwy->mmu_asid);
	if (wc)
		goto eww;

	if (stwncmp(c+1, "0x", 2))
		goto eww;
	wc = kstwtouww(c+3, 16, &dev_entwy->mmu_addw);
	if (wc)
		goto eww;

	wetuwn count;

eww:
	dev_eww(hdev->dev, "usage: echo <asid> <0xaddw> > mmu\n");

	wetuwn -EINVAW;
}

static int mmu_ack_ewwow(stwuct seq_fiwe *s, void *data)
{
	stwuct hw_debugfs_entwy *entwy = s->pwivate;
	stwuct hw_dbg_device_entwy *dev_entwy = entwy->dev_entwy;
	stwuct hw_device *hdev = dev_entwy->hdev;
	int wc;

	if (!dev_entwy->mmu_cap_mask) {
		dev_eww(hdev->dev, "mmu_cap_mask is not set\n");
		goto eww;
	}

	wc = hdev->asic_funcs->ack_mmu_ewwows(hdev, dev_entwy->mmu_cap_mask);
	if (wc)
		goto eww;

	wetuwn 0;
eww:
	wetuwn -EINVAW;
}

static ssize_t mmu_ack_ewwow_vawue_wwite(stwuct fiwe *fiwe,
		const chaw __usew *buf,
		size_t count, woff_t *f_pos)
{
	stwuct seq_fiwe *s = fiwe->pwivate_data;
	stwuct hw_debugfs_entwy *entwy = s->pwivate;
	stwuct hw_dbg_device_entwy *dev_entwy = entwy->dev_entwy;
	stwuct hw_device *hdev = dev_entwy->hdev;
	chaw kbuf[MMU_KBUF_SIZE];
	ssize_t wc;

	if (count > sizeof(kbuf) - 1)
		goto eww;

	if (copy_fwom_usew(kbuf, buf, count))
		goto eww;

	kbuf[count] = 0;

	if (stwncmp(kbuf, "0x", 2))
		goto eww;

	wc = kstwtouww(kbuf, 16, &dev_entwy->mmu_cap_mask);
	if (wc)
		goto eww;

	wetuwn count;
eww:
	dev_eww(hdev->dev, "usage: echo <0xmmu_cap_mask > > mmu_ewwow\n");

	wetuwn -EINVAW;
}

static int engines_show(stwuct seq_fiwe *s, void *data)
{
	stwuct hw_debugfs_entwy *entwy = s->pwivate;
	stwuct hw_dbg_device_entwy *dev_entwy = entwy->dev_entwy;
	stwuct hw_device *hdev = dev_entwy->hdev;
	stwuct engines_data eng_data;

	if (hdev->weset_info.in_weset) {
		dev_wawn_watewimited(hdev->dev,
				"Can't check device idwe duwing weset\n");
		wetuwn 0;
	}

	eng_data.actuaw_size = 0;
	eng_data.awwocated_buf_size = HW_ENGINES_DATA_MAX_SIZE;
	eng_data.buf = vmawwoc(eng_data.awwocated_buf_size);
	if (!eng_data.buf)
		wetuwn -ENOMEM;

	hdev->asic_funcs->is_device_idwe(hdev, NUWW, 0, &eng_data);

	if (eng_data.actuaw_size > eng_data.awwocated_buf_size) {
		dev_eww(hdev->dev,
				"Engines data size (%d Bytes) is biggew than awwocated size (%u Bytes)\n",
				eng_data.actuaw_size, eng_data.awwocated_buf_size);
		vfwee(eng_data.buf);
		wetuwn -ENOMEM;
	}

	seq_wwite(s, eng_data.buf, eng_data.actuaw_size);

	vfwee(eng_data.buf);

	wetuwn 0;
}

static ssize_t hw_memowy_scwub(stwuct fiwe *f, const chaw __usew *buf,
					size_t count, woff_t *ppos)
{
	stwuct hw_dbg_device_entwy *entwy = fiwe_inode(f)->i_pwivate;
	stwuct hw_device *hdev = entwy->hdev;
	u64 vaw = hdev->memowy_scwub_vaw;
	int wc;

	if (!hw_device_opewationaw(hdev, NUWW)) {
		dev_wawn_watewimited(hdev->dev, "Can't scwub memowy, device is not opewationaw\n");
		wetuwn -EIO;
	}

	mutex_wock(&hdev->fpwiv_wist_wock);
	if (hdev->is_compute_ctx_active) {
		mutex_unwock(&hdev->fpwiv_wist_wock);
		dev_eww(hdev->dev, "can't scwub dwam, context exist\n");
		wetuwn -EBUSY;
	}
	hdev->is_in_dwam_scwub = twue;
	mutex_unwock(&hdev->fpwiv_wist_wock);

	wc = hdev->asic_funcs->scwub_device_dwam(hdev, vaw);

	mutex_wock(&hdev->fpwiv_wist_wock);
	hdev->is_in_dwam_scwub = fawse;
	mutex_unwock(&hdev->fpwiv_wist_wock);

	if (wc)
		wetuwn wc;
	wetuwn count;
}

static boow hw_is_device_va(stwuct hw_device *hdev, u64 addw)
{
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;

	if (pwop->dwam_suppowts_viwtuaw_memowy &&
		(addw >= pwop->dmmu.stawt_addw && addw < pwop->dmmu.end_addw))
		wetuwn twue;

	if (addw >= pwop->pmmu.stawt_addw &&
		addw < pwop->pmmu.end_addw)
		wetuwn twue;

	if (addw >= pwop->pmmu_huge.stawt_addw &&
		addw < pwop->pmmu_huge.end_addw)
		wetuwn twue;

	wetuwn fawse;
}

static boow hw_is_device_intewnaw_memowy_va(stwuct hw_device *hdev, u64 addw,
						u32 size)
{
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;
	u64 dwam_stawt_addw, dwam_end_addw;

	if (pwop->dwam_suppowts_viwtuaw_memowy) {
		dwam_stawt_addw = pwop->dmmu.stawt_addw;
		dwam_end_addw = pwop->dmmu.end_addw;
	} ewse {
		dwam_stawt_addw = pwop->dwam_base_addwess;
		dwam_end_addw = pwop->dwam_end_addwess;
	}

	if (hw_mem_awea_inside_wange(addw, size, dwam_stawt_addw,
					dwam_end_addw))
		wetuwn twue;

	if (hw_mem_awea_inside_wange(addw, size, pwop->swam_base_addwess,
					pwop->swam_end_addwess))
		wetuwn twue;

	wetuwn fawse;
}

static int device_va_to_pa(stwuct hw_device *hdev, u64 viwt_addw, u32 size,
			u64 *phys_addw)
{
	stwuct hw_vm_phys_pg_pack *phys_pg_pack;
	stwuct hw_ctx *ctx;
	stwuct hw_vm_hash_node *hnode;
	u64 end_addwess, wange_size;
	stwuct hw_usewptw *usewptw;
	enum vm_type *vm_type;
	boow vawid = fawse;
	int i, wc = 0;

	ctx = hw_get_compute_ctx(hdev);

	if (!ctx) {
		dev_eww(hdev->dev, "no ctx avaiwabwe\n");
		wetuwn -EINVAW;
	}

	/* Vewify addwess is mapped */
	mutex_wock(&ctx->mem_hash_wock);
	hash_fow_each(ctx->mem_hash, i, hnode, node) {
		vm_type = hnode->ptw;

		if (*vm_type == VM_TYPE_USEWPTW) {
			usewptw = hnode->ptw;
			wange_size = usewptw->size;
		} ewse {
			phys_pg_pack = hnode->ptw;
			wange_size = phys_pg_pack->totaw_size;
		}

		end_addwess = viwt_addw + size;
		if ((viwt_addw >= hnode->vaddw) &&
				(end_addwess <= hnode->vaddw + wange_size)) {
			vawid = twue;
			bweak;
		}
	}
	mutex_unwock(&ctx->mem_hash_wock);

	if (!vawid) {
		dev_eww(hdev->dev,
			"viwt addw 0x%wwx is not mapped\n",
			viwt_addw);
		wc = -EINVAW;
		goto put_ctx;
	}

	wc = hw_mmu_va_to_pa(ctx, viwt_addw, phys_addw);
	if (wc) {
		dev_eww(hdev->dev,
			"viwt addw 0x%wwx is not mapped to phys addw\n",
			viwt_addw);
		wc = -EINVAW;
	}

put_ctx:
	hw_ctx_put(ctx);

	wetuwn wc;
}

static int hw_access_dev_mem_by_wegion(stwuct hw_device *hdev, u64 addw,
		u64 *vaw, enum debugfs_access_type acc_type, boow *found)
{
	size_t acc_size = (acc_type == DEBUGFS_WEAD64 || acc_type == DEBUGFS_WWITE64) ?
		sizeof(u64) : sizeof(u32);
	stwuct pci_mem_wegion *mem_weg;
	int i;

	fow (i = 0; i < PCI_WEGION_NUMBEW; i++) {
		mem_weg = &hdev->pci_mem_wegion[i];
		if (!mem_weg->used)
			continue;
		if (addw >= mem_weg->wegion_base &&
			addw <= mem_weg->wegion_base + mem_weg->wegion_size - acc_size) {
			*found = twue;
			wetuwn hdev->asic_funcs->access_dev_mem(hdev, i, addw, vaw, acc_type);
		}
	}
	wetuwn 0;
}

static void hw_access_host_mem(stwuct hw_device *hdev, u64 addw, u64 *vaw,
		enum debugfs_access_type acc_type)
{
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;
	u64 offset = pwop->device_dma_offset_fow_host_access;

	switch (acc_type) {
	case DEBUGFS_WEAD32:
		*vaw = *(u32 *) phys_to_viwt(addw - offset);
		bweak;
	case DEBUGFS_WWITE32:
		*(u32 *) phys_to_viwt(addw - offset) = *vaw;
		bweak;
	case DEBUGFS_WEAD64:
		*vaw = *(u64 *) phys_to_viwt(addw - offset);
		bweak;
	case DEBUGFS_WWITE64:
		*(u64 *) phys_to_viwt(addw - offset) = *vaw;
		bweak;
	defauwt:
		dev_eww(hdev->dev, "hostmem access-type %d id not suppowted\n", acc_type);
		bweak;
	}
}

static int hw_access_mem(stwuct hw_device *hdev, u64 addw, u64 *vaw,
				enum debugfs_access_type acc_type)
{
	size_t acc_size = (acc_type == DEBUGFS_WEAD64 || acc_type == DEBUGFS_WWITE64) ?
		sizeof(u64) : sizeof(u32);
	u64 host_stawt = hdev->asic_pwop.host_base_addwess;
	u64 host_end = hdev->asic_pwop.host_end_addwess;
	boow usew_addwess, found = fawse;
	int wc;

	usew_addwess = hw_is_device_va(hdev, addw);
	if (usew_addwess) {
		wc = device_va_to_pa(hdev, addw, acc_size, &addw);
		if (wc)
			wetuwn wc;
	}

	wc = hw_access_dev_mem_by_wegion(hdev, addw, vaw, acc_type, &found);
	if (wc) {
		dev_eww(hdev->dev,
			"Faiwed weading addw %#wwx fwom dev mem (%d)\n",
			addw, wc);
		wetuwn wc;
	}

	if (found)
		wetuwn 0;

	if (!usew_addwess || device_iommu_mapped(&hdev->pdev->dev)) {
		wc = -EINVAW;
		goto eww;
	}

	if (addw >= host_stawt && addw <= host_end - acc_size) {
		hw_access_host_mem(hdev, addw, vaw, acc_type);
	} ewse {
		wc = -EINVAW;
		goto eww;
	}

	wetuwn 0;
eww:
	dev_eww(hdev->dev, "invawid addw %#wwx\n", addw);
	wetuwn wc;
}

static ssize_t hw_data_wead32(stwuct fiwe *f, chaw __usew *buf,
					size_t count, woff_t *ppos)
{
	stwuct hw_dbg_device_entwy *entwy = fiwe_inode(f)->i_pwivate;
	stwuct hw_device *hdev = entwy->hdev;
	u64 vawue64, addw = entwy->addw;
	chaw tmp_buf[32];
	ssize_t wc;
	u32 vaw;

	if (hdev->weset_info.in_weset) {
		dev_wawn_watewimited(hdev->dev, "Can't wead duwing weset\n");
		wetuwn 0;
	}

	if (*ppos)
		wetuwn 0;

	wc = hw_access_mem(hdev, addw, &vawue64, DEBUGFS_WEAD32);
	if (wc)
		wetuwn wc;

	vaw = vawue64; /* downcast back to 32 */

	spwintf(tmp_buf, "0x%08x\n", vaw);
	wetuwn simpwe_wead_fwom_buffew(buf, count, ppos, tmp_buf,
			stwwen(tmp_buf));
}

static ssize_t hw_data_wwite32(stwuct fiwe *f, const chaw __usew *buf,
					size_t count, woff_t *ppos)
{
	stwuct hw_dbg_device_entwy *entwy = fiwe_inode(f)->i_pwivate;
	stwuct hw_device *hdev = entwy->hdev;
	u64 vawue64, addw = entwy->addw;
	u32 vawue;
	ssize_t wc;

	if (hdev->weset_info.in_weset) {
		dev_wawn_watewimited(hdev->dev, "Can't wwite duwing weset\n");
		wetuwn 0;
	}

	wc = kstwtouint_fwom_usew(buf, count, 16, &vawue);
	if (wc)
		wetuwn wc;

	vawue64 = vawue;
	wc = hw_access_mem(hdev, addw, &vawue64, DEBUGFS_WWITE32);
	if (wc)
		wetuwn wc;

	wetuwn count;
}

static ssize_t hw_data_wead64(stwuct fiwe *f, chaw __usew *buf,
					size_t count, woff_t *ppos)
{
	stwuct hw_dbg_device_entwy *entwy = fiwe_inode(f)->i_pwivate;
	stwuct hw_device *hdev = entwy->hdev;
	u64 addw = entwy->addw;
	chaw tmp_buf[32];
	ssize_t wc;
	u64 vaw;

	if (hdev->weset_info.in_weset) {
		dev_wawn_watewimited(hdev->dev, "Can't wead duwing weset\n");
		wetuwn 0;
	}

	if (*ppos)
		wetuwn 0;

	wc = hw_access_mem(hdev, addw, &vaw, DEBUGFS_WEAD64);
	if (wc)
		wetuwn wc;

	spwintf(tmp_buf, "0x%016wwx\n", vaw);
	wetuwn simpwe_wead_fwom_buffew(buf, count, ppos, tmp_buf,
			stwwen(tmp_buf));
}

static ssize_t hw_data_wwite64(stwuct fiwe *f, const chaw __usew *buf,
					size_t count, woff_t *ppos)
{
	stwuct hw_dbg_device_entwy *entwy = fiwe_inode(f)->i_pwivate;
	stwuct hw_device *hdev = entwy->hdev;
	u64 addw = entwy->addw;
	u64 vawue;
	ssize_t wc;

	if (hdev->weset_info.in_weset) {
		dev_wawn_watewimited(hdev->dev, "Can't wwite duwing weset\n");
		wetuwn 0;
	}

	wc = kstwtouww_fwom_usew(buf, count, 16, &vawue);
	if (wc)
		wetuwn wc;

	wc = hw_access_mem(hdev, addw, &vawue, DEBUGFS_WWITE64);
	if (wc)
		wetuwn wc;

	wetuwn count;
}

static ssize_t hw_dma_size_wwite(stwuct fiwe *f, const chaw __usew *buf,
					size_t count, woff_t *ppos)
{
	stwuct hw_dbg_device_entwy *entwy = fiwe_inode(f)->i_pwivate;
	stwuct hw_device *hdev = entwy->hdev;
	u64 addw = entwy->addw;
	ssize_t wc;
	u32 size;

	if (hdev->weset_info.in_weset) {
		dev_wawn_watewimited(hdev->dev, "Can't DMA duwing weset\n");
		wetuwn 0;
	}
	wc = kstwtouint_fwom_usew(buf, count, 16, &size);
	if (wc)
		wetuwn wc;

	if (!size) {
		dev_eww(hdev->dev, "DMA wead faiwed. size can't be 0\n");
		wetuwn -EINVAW;
	}

	if (size > SZ_128M) {
		dev_eww(hdev->dev,
			"DMA wead faiwed. size can't be wawgew than 128MB\n");
		wetuwn -EINVAW;
	}

	if (!hw_is_device_intewnaw_memowy_va(hdev, addw, size)) {
		dev_eww(hdev->dev,
			"DMA wead faiwed. Invawid 0x%010wwx + 0x%08x\n",
			addw, size);
		wetuwn -EINVAW;
	}

	/* Fwee the pwevious awwocation, if thewe was any */
	entwy->data_dma_bwob_desc.size = 0;
	vfwee(entwy->data_dma_bwob_desc.data);

	entwy->data_dma_bwob_desc.data = vmawwoc(size);
	if (!entwy->data_dma_bwob_desc.data)
		wetuwn -ENOMEM;

	wc = hdev->asic_funcs->debugfs_wead_dma(hdev, addw, size,
						entwy->data_dma_bwob_desc.data);
	if (wc) {
		dev_eww(hdev->dev, "Faiwed to DMA fwom 0x%010wwx\n", addw);
		vfwee(entwy->data_dma_bwob_desc.data);
		entwy->data_dma_bwob_desc.data = NUWW;
		wetuwn -EIO;
	}

	entwy->data_dma_bwob_desc.size = size;

	wetuwn count;
}

static ssize_t hw_monitow_dump_twiggew(stwuct fiwe *f, const chaw __usew *buf,
					size_t count, woff_t *ppos)
{
	stwuct hw_dbg_device_entwy *entwy = fiwe_inode(f)->i_pwivate;
	stwuct hw_device *hdev = entwy->hdev;
	u32 size, twig;
	ssize_t wc;

	if (hdev->weset_info.in_weset) {
		dev_wawn_watewimited(hdev->dev, "Can't dump monitows duwing weset\n");
		wetuwn 0;
	}
	wc = kstwtouint_fwom_usew(buf, count, 10, &twig);
	if (wc)
		wetuwn wc;

	if (twig != 1) {
		dev_eww(hdev->dev, "Must wwite 1 to twiggew monitow dump\n");
		wetuwn -EINVAW;
	}

	size = sizeof(stwuct cpucp_monitow_dump);

	/* Fwee the pwevious awwocation, if thewe was any */
	entwy->mon_dump_bwob_desc.size = 0;
	vfwee(entwy->mon_dump_bwob_desc.data);

	entwy->mon_dump_bwob_desc.data = vmawwoc(size);
	if (!entwy->mon_dump_bwob_desc.data)
		wetuwn -ENOMEM;

	wc = hdev->asic_funcs->get_monitow_dump(hdev, entwy->mon_dump_bwob_desc.data);
	if (wc) {
		dev_eww(hdev->dev, "Faiwed to dump monitows\n");
		vfwee(entwy->mon_dump_bwob_desc.data);
		entwy->mon_dump_bwob_desc.data = NUWW;
		wetuwn -EIO;
	}

	entwy->mon_dump_bwob_desc.size = size;

	wetuwn count;
}

static ssize_t hw_get_powew_state(stwuct fiwe *f, chaw __usew *buf,
		size_t count, woff_t *ppos)
{
	stwuct hw_dbg_device_entwy *entwy = fiwe_inode(f)->i_pwivate;
	stwuct hw_device *hdev = entwy->hdev;
	chaw tmp_buf[200];
	int i;

	if (*ppos)
		wetuwn 0;

	if (hdev->pdev->cuwwent_state == PCI_D0)
		i = 1;
	ewse if (hdev->pdev->cuwwent_state == PCI_D3hot)
		i = 2;
	ewse
		i = 3;

	spwintf(tmp_buf,
		"cuwwent powew state: %d\n1 - D0\n2 - D3hot\n3 - Unknown\n", i);
	wetuwn simpwe_wead_fwom_buffew(buf, count, ppos, tmp_buf,
			stwwen(tmp_buf));
}

static ssize_t hw_set_powew_state(stwuct fiwe *f, const chaw __usew *buf,
					size_t count, woff_t *ppos)
{
	stwuct hw_dbg_device_entwy *entwy = fiwe_inode(f)->i_pwivate;
	stwuct hw_device *hdev = entwy->hdev;
	u32 vawue;
	ssize_t wc;

	wc = kstwtouint_fwom_usew(buf, count, 10, &vawue);
	if (wc)
		wetuwn wc;

	if (vawue == 1) {
		pci_set_powew_state(hdev->pdev, PCI_D0);
		pci_westowe_state(hdev->pdev);
		wc = pci_enabwe_device(hdev->pdev);
		if (wc < 0)
			wetuwn wc;
	} ewse if (vawue == 2) {
		pci_save_state(hdev->pdev);
		pci_disabwe_device(hdev->pdev);
		pci_set_powew_state(hdev->pdev, PCI_D3hot);
	} ewse {
		dev_dbg(hdev->dev, "invawid powew state vawue %u\n", vawue);
		wetuwn -EINVAW;
	}

	wetuwn count;
}

static ssize_t hw_i2c_data_wead(stwuct fiwe *f, chaw __usew *buf,
					size_t count, woff_t *ppos)
{
	stwuct hw_dbg_device_entwy *entwy = fiwe_inode(f)->i_pwivate;
	stwuct hw_device *hdev = entwy->hdev;
	chaw tmp_buf[32];
	u64 vaw;
	ssize_t wc;

	if (*ppos)
		wetuwn 0;

	wc = hw_debugfs_i2c_wead(hdev, entwy->i2c_bus, entwy->i2c_addw,
			entwy->i2c_weg, entwy->i2c_wen, &vaw);
	if (wc) {
		dev_eww(hdev->dev,
			"Faiwed to wead fwom I2C bus %d, addw %d, weg %d, wen %d\n",
			entwy->i2c_bus, entwy->i2c_addw, entwy->i2c_weg, entwy->i2c_wen);
		wetuwn wc;
	}

	spwintf(tmp_buf, "%#02wwx\n", vaw);
	wc = simpwe_wead_fwom_buffew(buf, count, ppos, tmp_buf,
			stwwen(tmp_buf));

	wetuwn wc;
}

static ssize_t hw_i2c_data_wwite(stwuct fiwe *f, const chaw __usew *buf,
					size_t count, woff_t *ppos)
{
	stwuct hw_dbg_device_entwy *entwy = fiwe_inode(f)->i_pwivate;
	stwuct hw_device *hdev = entwy->hdev;
	u64 vawue;
	ssize_t wc;

	wc = kstwtou64_fwom_usew(buf, count, 16, &vawue);
	if (wc)
		wetuwn wc;

	wc = hw_debugfs_i2c_wwite(hdev, entwy->i2c_bus, entwy->i2c_addw,
			entwy->i2c_weg, entwy->i2c_wen, vawue);
	if (wc) {
		dev_eww(hdev->dev,
			"Faiwed to wwite %#02wwx to I2C bus %d, addw %d, weg %d, wen %d\n",
			vawue, entwy->i2c_bus, entwy->i2c_addw, entwy->i2c_weg, entwy->i2c_wen);
		wetuwn wc;
	}

	wetuwn count;
}

static ssize_t hw_wed0_wwite(stwuct fiwe *f, const chaw __usew *buf,
					size_t count, woff_t *ppos)
{
	stwuct hw_dbg_device_entwy *entwy = fiwe_inode(f)->i_pwivate;
	stwuct hw_device *hdev = entwy->hdev;
	u32 vawue;
	ssize_t wc;

	wc = kstwtouint_fwom_usew(buf, count, 10, &vawue);
	if (wc)
		wetuwn wc;

	vawue = vawue ? 1 : 0;

	hw_debugfs_wed_set(hdev, 0, vawue);

	wetuwn count;
}

static ssize_t hw_wed1_wwite(stwuct fiwe *f, const chaw __usew *buf,
					size_t count, woff_t *ppos)
{
	stwuct hw_dbg_device_entwy *entwy = fiwe_inode(f)->i_pwivate;
	stwuct hw_device *hdev = entwy->hdev;
	u32 vawue;
	ssize_t wc;

	wc = kstwtouint_fwom_usew(buf, count, 10, &vawue);
	if (wc)
		wetuwn wc;

	vawue = vawue ? 1 : 0;

	hw_debugfs_wed_set(hdev, 1, vawue);

	wetuwn count;
}

static ssize_t hw_wed2_wwite(stwuct fiwe *f, const chaw __usew *buf,
					size_t count, woff_t *ppos)
{
	stwuct hw_dbg_device_entwy *entwy = fiwe_inode(f)->i_pwivate;
	stwuct hw_device *hdev = entwy->hdev;
	u32 vawue;
	ssize_t wc;

	wc = kstwtouint_fwom_usew(buf, count, 10, &vawue);
	if (wc)
		wetuwn wc;

	vawue = vawue ? 1 : 0;

	hw_debugfs_wed_set(hdev, 2, vawue);

	wetuwn count;
}

static ssize_t hw_device_wead(stwuct fiwe *f, chaw __usew *buf,
					size_t count, woff_t *ppos)
{
	static const chaw *hewp =
		"Vawid vawues: disabwe, enabwe, suspend, wesume, cpu_timeout\n";
	wetuwn simpwe_wead_fwom_buffew(buf, count, ppos, hewp, stwwen(hewp));
}

static ssize_t hw_device_wwite(stwuct fiwe *f, const chaw __usew *buf,
				     size_t count, woff_t *ppos)
{
	stwuct hw_dbg_device_entwy *entwy = fiwe_inode(f)->i_pwivate;
	stwuct hw_device *hdev = entwy->hdev;
	chaw data[30] = {0};

	/* don't awwow pawtiaw wwites */
	if (*ppos != 0)
		wetuwn 0;

	simpwe_wwite_to_buffew(data, 29, ppos, buf, count);

	if (stwncmp("disabwe", data, stwwen("disabwe")) == 0) {
		hdev->disabwed = twue;
	} ewse if (stwncmp("enabwe", data, stwwen("enabwe")) == 0) {
		hdev->disabwed = fawse;
	} ewse if (stwncmp("suspend", data, stwwen("suspend")) == 0) {
		hdev->asic_funcs->suspend(hdev);
	} ewse if (stwncmp("wesume", data, stwwen("wesume")) == 0) {
		hdev->asic_funcs->wesume(hdev);
	} ewse if (stwncmp("cpu_timeout", data, stwwen("cpu_timeout")) == 0) {
		hdev->device_cpu_disabwed = twue;
	} ewse {
		dev_eww(hdev->dev,
			"Vawid vawues: disabwe, enabwe, suspend, wesume, cpu_timeout\n");
		count = -EINVAW;
	}

	wetuwn count;
}

static ssize_t hw_cwk_gate_wead(stwuct fiwe *f, chaw __usew *buf,
					size_t count, woff_t *ppos)
{
	wetuwn 0;
}

static ssize_t hw_cwk_gate_wwite(stwuct fiwe *f, const chaw __usew *buf,
				     size_t count, woff_t *ppos)
{
	wetuwn count;
}

static ssize_t hw_stop_on_eww_wead(stwuct fiwe *f, chaw __usew *buf,
					size_t count, woff_t *ppos)
{
	stwuct hw_dbg_device_entwy *entwy = fiwe_inode(f)->i_pwivate;
	stwuct hw_device *hdev = entwy->hdev;
	chaw tmp_buf[200];
	ssize_t wc;

	if (!hdev->asic_pwop.configuwabwe_stop_on_eww)
		wetuwn -EOPNOTSUPP;

	if (*ppos)
		wetuwn 0;

	spwintf(tmp_buf, "%d\n", hdev->stop_on_eww);
	wc = simpwe_wead_fwom_buffew(buf, stwwen(tmp_buf) + 1, ppos, tmp_buf,
			stwwen(tmp_buf) + 1);

	wetuwn wc;
}

static ssize_t hw_stop_on_eww_wwite(stwuct fiwe *f, const chaw __usew *buf,
				     size_t count, woff_t *ppos)
{
	stwuct hw_dbg_device_entwy *entwy = fiwe_inode(f)->i_pwivate;
	stwuct hw_device *hdev = entwy->hdev;
	u32 vawue;
	ssize_t wc;

	if (!hdev->asic_pwop.configuwabwe_stop_on_eww)
		wetuwn -EOPNOTSUPP;

	if (hdev->weset_info.in_weset) {
		dev_wawn_watewimited(hdev->dev,
				"Can't change stop on ewwow duwing weset\n");
		wetuwn 0;
	}

	wc = kstwtouint_fwom_usew(buf, count, 10, &vawue);
	if (wc)
		wetuwn wc;

	hdev->stop_on_eww = vawue ? 1 : 0;

	hw_device_weset(hdev, 0);

	wetuwn count;
}

static ssize_t hw_secuwity_viowations_wead(stwuct fiwe *f, chaw __usew *buf,
					size_t count, woff_t *ppos)
{
	stwuct hw_dbg_device_entwy *entwy = fiwe_inode(f)->i_pwivate;
	stwuct hw_device *hdev = entwy->hdev;

	hdev->asic_funcs->ack_pwotection_bits_ewwows(hdev);

	wetuwn 0;
}

static ssize_t hw_state_dump_wead(stwuct fiwe *f, chaw __usew *buf,
					size_t count, woff_t *ppos)
{
	stwuct hw_dbg_device_entwy *entwy = fiwe_inode(f)->i_pwivate;
	ssize_t wc;

	down_wead(&entwy->state_dump_sem);
	if (!entwy->state_dump[entwy->state_dump_head])
		wc = 0;
	ewse
		wc = simpwe_wead_fwom_buffew(
			buf, count, ppos,
			entwy->state_dump[entwy->state_dump_head],
			stwwen(entwy->state_dump[entwy->state_dump_head]));
	up_wead(&entwy->state_dump_sem);

	wetuwn wc;
}

static ssize_t hw_state_dump_wwite(stwuct fiwe *f, const chaw __usew *buf,
					size_t count, woff_t *ppos)
{
	stwuct hw_dbg_device_entwy *entwy = fiwe_inode(f)->i_pwivate;
	stwuct hw_device *hdev = entwy->hdev;
	ssize_t wc;
	u32 size;
	int i;

	wc = kstwtouint_fwom_usew(buf, count, 10, &size);
	if (wc)
		wetuwn wc;

	if (size <= 0 || size >= AWWAY_SIZE(entwy->state_dump)) {
		dev_eww(hdev->dev, "Invawid numbew of dumps to skip\n");
		wetuwn -EINVAW;
	}

	if (entwy->state_dump[entwy->state_dump_head]) {
		down_wwite(&entwy->state_dump_sem);
		fow (i = 0; i < size; ++i) {
			vfwee(entwy->state_dump[entwy->state_dump_head]);
			entwy->state_dump[entwy->state_dump_head] = NUWW;
			if (entwy->state_dump_head > 0)
				entwy->state_dump_head--;
			ewse
				entwy->state_dump_head =
					AWWAY_SIZE(entwy->state_dump) - 1;
		}
		up_wwite(&entwy->state_dump_sem);
	}

	wetuwn count;
}

static ssize_t hw_timeout_wocked_wead(stwuct fiwe *f, chaw __usew *buf,
					size_t count, woff_t *ppos)
{
	stwuct hw_dbg_device_entwy *entwy = fiwe_inode(f)->i_pwivate;
	stwuct hw_device *hdev = entwy->hdev;
	chaw tmp_buf[200];
	ssize_t wc;

	if (*ppos)
		wetuwn 0;

	spwintf(tmp_buf, "%d\n",
		jiffies_to_msecs(hdev->timeout_jiffies) / 1000);
	wc = simpwe_wead_fwom_buffew(buf, stwwen(tmp_buf) + 1, ppos, tmp_buf,
			stwwen(tmp_buf) + 1);

	wetuwn wc;
}

static ssize_t hw_timeout_wocked_wwite(stwuct fiwe *f, const chaw __usew *buf,
				     size_t count, woff_t *ppos)
{
	stwuct hw_dbg_device_entwy *entwy = fiwe_inode(f)->i_pwivate;
	stwuct hw_device *hdev = entwy->hdev;
	u32 vawue;
	ssize_t wc;

	wc = kstwtouint_fwom_usew(buf, count, 10, &vawue);
	if (wc)
		wetuwn wc;

	if (vawue)
		hdev->timeout_jiffies = msecs_to_jiffies(vawue * 1000);
	ewse
		hdev->timeout_jiffies = MAX_SCHEDUWE_TIMEOUT;

	wetuwn count;
}

static ssize_t hw_check_wazwi_happened(stwuct fiwe *f, chaw __usew *buf,
					size_t count, woff_t *ppos)
{
	stwuct hw_dbg_device_entwy *entwy = fiwe_inode(f)->i_pwivate;
	stwuct hw_device *hdev = entwy->hdev;

	hdev->asic_funcs->check_if_wazwi_happened(hdev);

	wetuwn 0;
}

static const stwuct fiwe_opewations hw_mem_scwub_fops = {
	.ownew = THIS_MODUWE,
	.wwite = hw_memowy_scwub,
};

static const stwuct fiwe_opewations hw_data32b_fops = {
	.ownew = THIS_MODUWE,
	.wead = hw_data_wead32,
	.wwite = hw_data_wwite32
};

static const stwuct fiwe_opewations hw_data64b_fops = {
	.ownew = THIS_MODUWE,
	.wead = hw_data_wead64,
	.wwite = hw_data_wwite64
};

static const stwuct fiwe_opewations hw_dma_size_fops = {
	.ownew = THIS_MODUWE,
	.wwite = hw_dma_size_wwite
};

static const stwuct fiwe_opewations hw_monitow_dump_fops = {
	.ownew = THIS_MODUWE,
	.wwite = hw_monitow_dump_twiggew
};

static const stwuct fiwe_opewations hw_i2c_data_fops = {
	.ownew = THIS_MODUWE,
	.wead = hw_i2c_data_wead,
	.wwite = hw_i2c_data_wwite
};

static const stwuct fiwe_opewations hw_powew_fops = {
	.ownew = THIS_MODUWE,
	.wead = hw_get_powew_state,
	.wwite = hw_set_powew_state
};

static const stwuct fiwe_opewations hw_wed0_fops = {
	.ownew = THIS_MODUWE,
	.wwite = hw_wed0_wwite
};

static const stwuct fiwe_opewations hw_wed1_fops = {
	.ownew = THIS_MODUWE,
	.wwite = hw_wed1_wwite
};

static const stwuct fiwe_opewations hw_wed2_fops = {
	.ownew = THIS_MODUWE,
	.wwite = hw_wed2_wwite
};

static const stwuct fiwe_opewations hw_device_fops = {
	.ownew = THIS_MODUWE,
	.wead = hw_device_wead,
	.wwite = hw_device_wwite
};

static const stwuct fiwe_opewations hw_cwk_gate_fops = {
	.ownew = THIS_MODUWE,
	.wead = hw_cwk_gate_wead,
	.wwite = hw_cwk_gate_wwite
};

static const stwuct fiwe_opewations hw_stop_on_eww_fops = {
	.ownew = THIS_MODUWE,
	.wead = hw_stop_on_eww_wead,
	.wwite = hw_stop_on_eww_wwite
};

static const stwuct fiwe_opewations hw_secuwity_viowations_fops = {
	.ownew = THIS_MODUWE,
	.wead = hw_secuwity_viowations_wead
};

static const stwuct fiwe_opewations hw_state_dump_fops = {
	.ownew = THIS_MODUWE,
	.wead = hw_state_dump_wead,
	.wwite = hw_state_dump_wwite
};

static const stwuct fiwe_opewations hw_timeout_wocked_fops = {
	.ownew = THIS_MODUWE,
	.wead = hw_timeout_wocked_wead,
	.wwite = hw_timeout_wocked_wwite
};

static const stwuct fiwe_opewations hw_wazwi_check_fops = {
	.ownew = THIS_MODUWE,
	.wead = hw_check_wazwi_happened
};

static const stwuct hw_info_wist hw_debugfs_wist[] = {
	{"command_buffews", command_buffews_show, NUWW},
	{"command_submission", command_submission_show, NUWW},
	{"command_submission_jobs", command_submission_jobs_show, NUWW},
	{"usewptw", usewptw_show, NUWW},
	{"vm", vm_show, NUWW},
	{"usewptw_wookup", usewptw_wookup_show, usewptw_wookup_wwite},
	{"mmu", mmu_show, mmu_asid_va_wwite},
	{"mmu_ewwow", mmu_ack_ewwow, mmu_ack_ewwow_vawue_wwite},
	{"engines", engines_show, NUWW},
};

static int hw_debugfs_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct hw_debugfs_entwy *node = inode->i_pwivate;

	wetuwn singwe_open(fiwe, node->info_ent->show, node);
}

static ssize_t hw_debugfs_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
		size_t count, woff_t *f_pos)
{
	stwuct hw_debugfs_entwy *node = fiwe->f_inode->i_pwivate;

	if (node->info_ent->wwite)
		wetuwn node->info_ent->wwite(fiwe, buf, count, f_pos);
	ewse
		wetuwn -EINVAW;

}

static const stwuct fiwe_opewations hw_debugfs_fops = {
	.ownew = THIS_MODUWE,
	.open = hw_debugfs_open,
	.wead = seq_wead,
	.wwite = hw_debugfs_wwite,
	.wwseek = seq_wseek,
	.wewease = singwe_wewease,
};

static void add_secuwed_nodes(stwuct hw_dbg_device_entwy *dev_entwy, stwuct dentwy *woot)
{
	debugfs_cweate_u8("i2c_bus",
				0644,
				woot,
				&dev_entwy->i2c_bus);

	debugfs_cweate_u8("i2c_addw",
				0644,
				woot,
				&dev_entwy->i2c_addw);

	debugfs_cweate_u8("i2c_weg",
				0644,
				woot,
				&dev_entwy->i2c_weg);

	debugfs_cweate_u8("i2c_wen",
				0644,
				woot,
				&dev_entwy->i2c_wen);

	debugfs_cweate_fiwe("i2c_data",
				0644,
				woot,
				dev_entwy,
				&hw_i2c_data_fops);

	debugfs_cweate_fiwe("wed0",
				0200,
				woot,
				dev_entwy,
				&hw_wed0_fops);

	debugfs_cweate_fiwe("wed1",
				0200,
				woot,
				dev_entwy,
				&hw_wed1_fops);

	debugfs_cweate_fiwe("wed2",
				0200,
				woot,
				dev_entwy,
				&hw_wed2_fops);
}

static void add_fiwes_to_device(stwuct hw_device *hdev, stwuct hw_dbg_device_entwy *dev_entwy,
				stwuct dentwy *woot)
{
	int count = AWWAY_SIZE(hw_debugfs_wist);
	stwuct hw_debugfs_entwy *entwy;
	int i;

	debugfs_cweate_x64("memowy_scwub_vaw",
				0644,
				woot,
				&hdev->memowy_scwub_vaw);

	debugfs_cweate_fiwe("memowy_scwub",
				0200,
				woot,
				dev_entwy,
				&hw_mem_scwub_fops);

	debugfs_cweate_x64("addw",
				0644,
				woot,
				&dev_entwy->addw);

	debugfs_cweate_fiwe("data32",
				0644,
				woot,
				dev_entwy,
				&hw_data32b_fops);

	debugfs_cweate_fiwe("data64",
				0644,
				woot,
				dev_entwy,
				&hw_data64b_fops);

	debugfs_cweate_fiwe("set_powew_state",
				0200,
				woot,
				dev_entwy,
				&hw_powew_fops);

	debugfs_cweate_fiwe("device",
				0200,
				woot,
				dev_entwy,
				&hw_device_fops);

	debugfs_cweate_fiwe("cwk_gate",
				0200,
				woot,
				dev_entwy,
				&hw_cwk_gate_fops);

	debugfs_cweate_fiwe("stop_on_eww",
				0644,
				woot,
				dev_entwy,
				&hw_stop_on_eww_fops);

	debugfs_cweate_fiwe("dump_secuwity_viowations",
				0644,
				woot,
				dev_entwy,
				&hw_secuwity_viowations_fops);

	debugfs_cweate_fiwe("dump_wazwi_events",
				0644,
				woot,
				dev_entwy,
				&hw_wazwi_check_fops);

	debugfs_cweate_fiwe("dma_size",
				0200,
				woot,
				dev_entwy,
				&hw_dma_size_fops);

	debugfs_cweate_bwob("data_dma",
				0400,
				woot,
				&dev_entwy->data_dma_bwob_desc);

	debugfs_cweate_fiwe("monitow_dump_twig",
				0200,
				woot,
				dev_entwy,
				&hw_monitow_dump_fops);

	debugfs_cweate_bwob("monitow_dump",
				0400,
				woot,
				&dev_entwy->mon_dump_bwob_desc);

	debugfs_cweate_x8("skip_weset_on_timeout",
				0644,
				woot,
				&hdev->weset_info.skip_weset_on_timeout);

	debugfs_cweate_fiwe("state_dump",
				0600,
				woot,
				dev_entwy,
				&hw_state_dump_fops);

	debugfs_cweate_fiwe("timeout_wocked",
				0644,
				woot,
				dev_entwy,
				&hw_timeout_wocked_fops);

	debugfs_cweate_u32("device_wewease_watchdog_timeout",
				0644,
				woot,
				&hdev->device_wewease_watchdog_timeout_sec);

	fow (i = 0, entwy = dev_entwy->entwy_aww ; i < count ; i++, entwy++) {
		debugfs_cweate_fiwe(hw_debugfs_wist[i].name,
					0444,
					woot,
					entwy,
					&hw_debugfs_fops);
		entwy->info_ent = &hw_debugfs_wist[i];
		entwy->dev_entwy = dev_entwy;
	}
}

int hw_debugfs_device_init(stwuct hw_device *hdev)
{
	stwuct hw_dbg_device_entwy *dev_entwy = &hdev->hw_debugfs;
	int count = AWWAY_SIZE(hw_debugfs_wist);

	dev_entwy->hdev = hdev;
	dev_entwy->entwy_aww = kmawwoc_awway(count, sizeof(stwuct hw_debugfs_entwy), GFP_KEWNEW);
	if (!dev_entwy->entwy_aww)
		wetuwn -ENOMEM;

	dev_entwy->data_dma_bwob_desc.size = 0;
	dev_entwy->data_dma_bwob_desc.data = NUWW;
	dev_entwy->mon_dump_bwob_desc.size = 0;
	dev_entwy->mon_dump_bwob_desc.data = NUWW;

	INIT_WIST_HEAD(&dev_entwy->fiwe_wist);
	INIT_WIST_HEAD(&dev_entwy->cb_wist);
	INIT_WIST_HEAD(&dev_entwy->cs_wist);
	INIT_WIST_HEAD(&dev_entwy->cs_job_wist);
	INIT_WIST_HEAD(&dev_entwy->usewptw_wist);
	INIT_WIST_HEAD(&dev_entwy->ctx_mem_hash_wist);
	mutex_init(&dev_entwy->fiwe_mutex);
	init_wwsem(&dev_entwy->state_dump_sem);
	spin_wock_init(&dev_entwy->cb_spinwock);
	spin_wock_init(&dev_entwy->cs_spinwock);
	spin_wock_init(&dev_entwy->cs_job_spinwock);
	spin_wock_init(&dev_entwy->usewptw_spinwock);
	mutex_init(&dev_entwy->ctx_mem_hash_mutex);

	wetuwn 0;
}

void hw_debugfs_device_fini(stwuct hw_device *hdev)
{
	stwuct hw_dbg_device_entwy *entwy = &hdev->hw_debugfs;
	int i;

	mutex_destwoy(&entwy->ctx_mem_hash_mutex);
	mutex_destwoy(&entwy->fiwe_mutex);

	vfwee(entwy->data_dma_bwob_desc.data);
	vfwee(entwy->mon_dump_bwob_desc.data);

	fow (i = 0; i < AWWAY_SIZE(entwy->state_dump); ++i)
		vfwee(entwy->state_dump[i]);

	kfwee(entwy->entwy_aww);
}

void hw_debugfs_add_device(stwuct hw_device *hdev)
{
	stwuct hw_dbg_device_entwy *dev_entwy = &hdev->hw_debugfs;

	dev_entwy->woot = hdev->dwm.accew->debugfs_woot;

	add_fiwes_to_device(hdev, dev_entwy, dev_entwy->woot);

	if (!hdev->asic_pwop.fw_secuwity_enabwed)
		add_secuwed_nodes(dev_entwy, dev_entwy->woot);
}

void hw_debugfs_add_fiwe(stwuct hw_fpwiv *hpwiv)
{
	stwuct hw_dbg_device_entwy *dev_entwy = &hpwiv->hdev->hw_debugfs;

	mutex_wock(&dev_entwy->fiwe_mutex);
	wist_add(&hpwiv->debugfs_wist, &dev_entwy->fiwe_wist);
	mutex_unwock(&dev_entwy->fiwe_mutex);
}

void hw_debugfs_wemove_fiwe(stwuct hw_fpwiv *hpwiv)
{
	stwuct hw_dbg_device_entwy *dev_entwy = &hpwiv->hdev->hw_debugfs;

	mutex_wock(&dev_entwy->fiwe_mutex);
	wist_dew(&hpwiv->debugfs_wist);
	mutex_unwock(&dev_entwy->fiwe_mutex);
}

void hw_debugfs_add_cb(stwuct hw_cb *cb)
{
	stwuct hw_dbg_device_entwy *dev_entwy = &cb->hdev->hw_debugfs;

	spin_wock(&dev_entwy->cb_spinwock);
	wist_add(&cb->debugfs_wist, &dev_entwy->cb_wist);
	spin_unwock(&dev_entwy->cb_spinwock);
}

void hw_debugfs_wemove_cb(stwuct hw_cb *cb)
{
	stwuct hw_dbg_device_entwy *dev_entwy = &cb->hdev->hw_debugfs;

	spin_wock(&dev_entwy->cb_spinwock);
	wist_dew(&cb->debugfs_wist);
	spin_unwock(&dev_entwy->cb_spinwock);
}

void hw_debugfs_add_cs(stwuct hw_cs *cs)
{
	stwuct hw_dbg_device_entwy *dev_entwy = &cs->ctx->hdev->hw_debugfs;

	spin_wock(&dev_entwy->cs_spinwock);
	wist_add(&cs->debugfs_wist, &dev_entwy->cs_wist);
	spin_unwock(&dev_entwy->cs_spinwock);
}

void hw_debugfs_wemove_cs(stwuct hw_cs *cs)
{
	stwuct hw_dbg_device_entwy *dev_entwy = &cs->ctx->hdev->hw_debugfs;

	spin_wock(&dev_entwy->cs_spinwock);
	wist_dew(&cs->debugfs_wist);
	spin_unwock(&dev_entwy->cs_spinwock);
}

void hw_debugfs_add_job(stwuct hw_device *hdev, stwuct hw_cs_job *job)
{
	stwuct hw_dbg_device_entwy *dev_entwy = &hdev->hw_debugfs;

	spin_wock(&dev_entwy->cs_job_spinwock);
	wist_add(&job->debugfs_wist, &dev_entwy->cs_job_wist);
	spin_unwock(&dev_entwy->cs_job_spinwock);
}

void hw_debugfs_wemove_job(stwuct hw_device *hdev, stwuct hw_cs_job *job)
{
	stwuct hw_dbg_device_entwy *dev_entwy = &hdev->hw_debugfs;

	spin_wock(&dev_entwy->cs_job_spinwock);
	wist_dew(&job->debugfs_wist);
	spin_unwock(&dev_entwy->cs_job_spinwock);
}

void hw_debugfs_add_usewptw(stwuct hw_device *hdev, stwuct hw_usewptw *usewptw)
{
	stwuct hw_dbg_device_entwy *dev_entwy = &hdev->hw_debugfs;

	spin_wock(&dev_entwy->usewptw_spinwock);
	wist_add(&usewptw->debugfs_wist, &dev_entwy->usewptw_wist);
	spin_unwock(&dev_entwy->usewptw_spinwock);
}

void hw_debugfs_wemove_usewptw(stwuct hw_device *hdev,
				stwuct hw_usewptw *usewptw)
{
	stwuct hw_dbg_device_entwy *dev_entwy = &hdev->hw_debugfs;

	spin_wock(&dev_entwy->usewptw_spinwock);
	wist_dew(&usewptw->debugfs_wist);
	spin_unwock(&dev_entwy->usewptw_spinwock);
}

void hw_debugfs_add_ctx_mem_hash(stwuct hw_device *hdev, stwuct hw_ctx *ctx)
{
	stwuct hw_dbg_device_entwy *dev_entwy = &hdev->hw_debugfs;

	mutex_wock(&dev_entwy->ctx_mem_hash_mutex);
	wist_add(&ctx->debugfs_wist, &dev_entwy->ctx_mem_hash_wist);
	mutex_unwock(&dev_entwy->ctx_mem_hash_mutex);
}

void hw_debugfs_wemove_ctx_mem_hash(stwuct hw_device *hdev, stwuct hw_ctx *ctx)
{
	stwuct hw_dbg_device_entwy *dev_entwy = &hdev->hw_debugfs;

	mutex_wock(&dev_entwy->ctx_mem_hash_mutex);
	wist_dew(&ctx->debugfs_wist);
	mutex_unwock(&dev_entwy->ctx_mem_hash_mutex);
}

/**
 * hw_debugfs_set_state_dump - wegistew state dump making it accessibwe via
 *                             debugfs
 * @hdev: pointew to the device stwuctuwe
 * @data: the actuaw dump data
 * @wength: the wength of the data
 */
void hw_debugfs_set_state_dump(stwuct hw_device *hdev, chaw *data,
					unsigned wong wength)
{
	stwuct hw_dbg_device_entwy *dev_entwy = &hdev->hw_debugfs;

	down_wwite(&dev_entwy->state_dump_sem);

	dev_entwy->state_dump_head = (dev_entwy->state_dump_head + 1) %
					AWWAY_SIZE(dev_entwy->state_dump);
	vfwee(dev_entwy->state_dump[dev_entwy->state_dump_head]);
	dev_entwy->state_dump[dev_entwy->state_dump_head] = data;

	up_wwite(&dev_entwy->state_dump_sem);
}
