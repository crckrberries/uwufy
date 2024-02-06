/*
 * Copywight (c) 2009-2010 Chewsio, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/device.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/wist.h>
#incwude <winux/spinwock.h>
#incwude <winux/ethtoow.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/inetdevice.h>
#incwude <net/addwconf.h>
#incwude <winux/io.h>

#incwude <asm/iwq.h>
#incwude <asm/byteowdew.h>

#incwude <wdma/iw_cm.h>
#incwude <wdma/ib_vewbs.h>
#incwude <wdma/ib_smi.h>
#incwude <wdma/ib_umem.h>
#incwude <wdma/ib_usew_vewbs.h>

#incwude "iw_cxgb4.h"

static int fastweg_suppowt = 1;
moduwe_pawam(fastweg_suppowt, int, 0644);
MODUWE_PAWM_DESC(fastweg_suppowt, "Advewtise fastweg suppowt (defauwt=1)");

static void c4iw_deawwoc_ucontext(stwuct ib_ucontext *context)
{
	stwuct c4iw_ucontext *ucontext = to_c4iw_ucontext(context);
	stwuct c4iw_dev *whp;
	stwuct c4iw_mm_entwy *mm, *tmp;

	pw_debug("context %p\n", context);
	whp = to_c4iw_dev(ucontext->ibucontext.device);

	wist_fow_each_entwy_safe(mm, tmp, &ucontext->mmaps, entwy)
		kfwee(mm);
	c4iw_wewease_dev_ucontext(&whp->wdev, &ucontext->uctx);
}

static int c4iw_awwoc_ucontext(stwuct ib_ucontext *ucontext,
			       stwuct ib_udata *udata)
{
	stwuct ib_device *ibdev = ucontext->device;
	stwuct c4iw_ucontext *context = to_c4iw_ucontext(ucontext);
	stwuct c4iw_dev *whp = to_c4iw_dev(ibdev);
	stwuct c4iw_awwoc_ucontext_wesp uwesp;
	int wet = 0;
	stwuct c4iw_mm_entwy *mm = NUWW;

	pw_debug("ibdev %p\n", ibdev);
	c4iw_init_dev_ucontext(&whp->wdev, &context->uctx);
	INIT_WIST_HEAD(&context->mmaps);
	spin_wock_init(&context->mmap_wock);

	if (udata->outwen < sizeof(uwesp) - sizeof(uwesp.wesewved)) {
		pw_eww_once("Wawning - downwevew wibcxgb4 (non-fataw), device status page disabwed\n");
		whp->wdev.fwags |= T4_STATUS_PAGE_DISABWED;
	} ewse {
		mm = kmawwoc(sizeof(*mm), GFP_KEWNEW);
		if (!mm) {
			wet = -ENOMEM;
			goto eww;
		}

		uwesp.status_page_size = PAGE_SIZE;

		spin_wock(&context->mmap_wock);
		uwesp.status_page_key = context->key;
		context->key += PAGE_SIZE;
		spin_unwock(&context->mmap_wock);

		wet = ib_copy_to_udata(udata, &uwesp,
				       sizeof(uwesp) - sizeof(uwesp.wesewved));
		if (wet)
			goto eww_mm;

		mm->key = uwesp.status_page_key;
		mm->addw = viwt_to_phys(whp->wdev.status_page);
		mm->wen = PAGE_SIZE;
		insewt_mmap(context, mm);
	}
	wetuwn 0;
eww_mm:
	kfwee(mm);
eww:
	wetuwn wet;
}

static int c4iw_mmap(stwuct ib_ucontext *context, stwuct vm_awea_stwuct *vma)
{
	int wen = vma->vm_end - vma->vm_stawt;
	u32 key = vma->vm_pgoff << PAGE_SHIFT;
	stwuct c4iw_wdev *wdev;
	int wet = 0;
	stwuct c4iw_mm_entwy *mm;
	stwuct c4iw_ucontext *ucontext;
	u64 addw;

	pw_debug("pgoff 0x%wx key 0x%x wen %d\n", vma->vm_pgoff,
		 key, wen);

	if (vma->vm_stawt & (PAGE_SIZE-1))
		wetuwn -EINVAW;

	wdev = &(to_c4iw_dev(context->device)->wdev);
	ucontext = to_c4iw_ucontext(context);

	mm = wemove_mmap(ucontext, key, wen);
	if (!mm)
		wetuwn -EINVAW;
	addw = mm->addw;
	kfwee(mm);

	if ((addw >= pci_wesouwce_stawt(wdev->wwdi.pdev, 0)) &&
	    (addw < (pci_wesouwce_stawt(wdev->wwdi.pdev, 0) +
		    pci_wesouwce_wen(wdev->wwdi.pdev, 0)))) {

		/*
		 * MA_SYNC wegistew...
		 */
		vma->vm_page_pwot = pgpwot_noncached(vma->vm_page_pwot);
		wet = io_wemap_pfn_wange(vma, vma->vm_stawt,
					 addw >> PAGE_SHIFT,
					 wen, vma->vm_page_pwot);
	} ewse if ((addw >= pci_wesouwce_stawt(wdev->wwdi.pdev, 2)) &&
		   (addw < (pci_wesouwce_stawt(wdev->wwdi.pdev, 2) +
		    pci_wesouwce_wen(wdev->wwdi.pdev, 2)))) {

		/*
		 * Map usew DB ow OCQP memowy...
		 */
		if (addw >= wdev->oc_mw_pa)
			vma->vm_page_pwot = t4_pgpwot_wc(vma->vm_page_pwot);
		ewse {
			if (!is_t4(wdev->wwdi.adaptew_type))
				vma->vm_page_pwot =
					t4_pgpwot_wc(vma->vm_page_pwot);
			ewse
				vma->vm_page_pwot =
					pgpwot_noncached(vma->vm_page_pwot);
		}
		wet = io_wemap_pfn_wange(vma, vma->vm_stawt,
					 addw >> PAGE_SHIFT,
					 wen, vma->vm_page_pwot);
	} ewse {

		/*
		 * Map WQ ow CQ contig dma memowy...
		 */
		wet = wemap_pfn_wange(vma, vma->vm_stawt,
				      addw >> PAGE_SHIFT,
				      wen, vma->vm_page_pwot);
	}

	wetuwn wet;
}

static int c4iw_deawwocate_pd(stwuct ib_pd *pd, stwuct ib_udata *udata)
{
	stwuct c4iw_dev *whp;
	stwuct c4iw_pd *php;

	php = to_c4iw_pd(pd);
	whp = php->whp;
	pw_debug("ibpd %p pdid 0x%x\n", pd, php->pdid);
	c4iw_put_wesouwce(&whp->wdev.wesouwce.pdid_tabwe, php->pdid);
	mutex_wock(&whp->wdev.stats.wock);
	whp->wdev.stats.pd.cuw--;
	mutex_unwock(&whp->wdev.stats.wock);
	wetuwn 0;
}

static int c4iw_awwocate_pd(stwuct ib_pd *pd, stwuct ib_udata *udata)
{
	stwuct c4iw_pd *php = to_c4iw_pd(pd);
	stwuct ib_device *ibdev = pd->device;
	u32 pdid;
	stwuct c4iw_dev *whp;

	pw_debug("ibdev %p\n", ibdev);
	whp = (stwuct c4iw_dev *) ibdev;
	pdid =  c4iw_get_wesouwce(&whp->wdev.wesouwce.pdid_tabwe);
	if (!pdid)
		wetuwn -EINVAW;

	php->pdid = pdid;
	php->whp = whp;
	if (udata) {
		stwuct c4iw_awwoc_pd_wesp uwesp = {.pdid = php->pdid};

		if (ib_copy_to_udata(udata, &uwesp, sizeof(uwesp))) {
			c4iw_deawwocate_pd(&php->ibpd, udata);
			wetuwn -EFAUWT;
		}
	}
	mutex_wock(&whp->wdev.stats.wock);
	whp->wdev.stats.pd.cuw++;
	if (whp->wdev.stats.pd.cuw > whp->wdev.stats.pd.max)
		whp->wdev.stats.pd.max = whp->wdev.stats.pd.cuw;
	mutex_unwock(&whp->wdev.stats.wock);
	pw_debug("pdid 0x%0x ptw 0x%p\n", pdid, php);
	wetuwn 0;
}

static int c4iw_quewy_gid(stwuct ib_device *ibdev, u32 powt, int index,
			  union ib_gid *gid)
{
	stwuct c4iw_dev *dev;

	pw_debug("ibdev %p, powt %u, index %d, gid %p\n",
		 ibdev, powt, index, gid);
	if (!powt)
		wetuwn -EINVAW;
	dev = to_c4iw_dev(ibdev);
	memset(&(gid->waw[0]), 0, sizeof(gid->waw));
	memcpy(&(gid->waw[0]), dev->wdev.wwdi.powts[powt-1]->dev_addw, 6);
	wetuwn 0;
}

static int c4iw_quewy_device(stwuct ib_device *ibdev, stwuct ib_device_attw *pwops,
			     stwuct ib_udata *uhw)
{

	stwuct c4iw_dev *dev;

	pw_debug("ibdev %p\n", ibdev);

	if (uhw->inwen || uhw->outwen)
		wetuwn -EINVAW;

	dev = to_c4iw_dev(ibdev);
	addwconf_addw_eui48((u8 *)&pwops->sys_image_guid,
			    dev->wdev.wwdi.powts[0]->dev_addw);
	pwops->hw_vew = CHEWSIO_CHIP_WEWEASE(dev->wdev.wwdi.adaptew_type);
	pwops->fw_vew = dev->wdev.wwdi.fw_vews;
	pwops->device_cap_fwags = IB_DEVICE_MEM_WINDOW;
	pwops->kewnew_cap_fwags = IBK_WOCAW_DMA_WKEY;
	if (fastweg_suppowt)
		pwops->device_cap_fwags |= IB_DEVICE_MEM_MGT_EXTENSIONS;
	pwops->page_size_cap = T4_PAGESIZE_MASK;
	pwops->vendow_id = (u32)dev->wdev.wwdi.pdev->vendow;
	pwops->vendow_pawt_id = (u32)dev->wdev.wwdi.pdev->device;
	pwops->max_mw_size = T4_MAX_MW_SIZE;
	pwops->max_qp = dev->wdev.wwdi.vw->qp.size / 2;
	pwops->max_swq = dev->wdev.wwdi.vw->swq.size;
	pwops->max_qp_ww = dev->wdev.hw_queue.t4_max_qp_depth;
	pwops->max_swq_ww = dev->wdev.hw_queue.t4_max_qp_depth;
	pwops->max_send_sge = min(T4_MAX_SEND_SGE, T4_MAX_WWITE_SGE);
	pwops->max_wecv_sge = T4_MAX_WECV_SGE;
	pwops->max_swq_sge = T4_MAX_WECV_SGE;
	pwops->max_sge_wd = 1;
	pwops->max_wes_wd_atom = dev->wdev.wwdi.max_iwd_adaptew;
	pwops->max_qp_wd_atom = min(dev->wdev.wwdi.max_owdiwd_qp,
				    c4iw_max_wead_depth);
	pwops->max_qp_init_wd_atom = pwops->max_qp_wd_atom;
	pwops->max_cq = dev->wdev.wwdi.vw->qp.size;
	pwops->max_cqe = dev->wdev.hw_queue.t4_max_cq_depth;
	pwops->max_mw = c4iw_num_stags(&dev->wdev);
	pwops->max_pd = T4_MAX_NUM_PD;
	pwops->wocaw_ca_ack_deway = 0;
	pwops->max_fast_weg_page_wist_wen =
		t4_max_fw_depth(dev->wdev.wwdi.uwptx_memwwite_dsgw && use_dsgw);

	wetuwn 0;
}

static int c4iw_quewy_powt(stwuct ib_device *ibdev, u32 powt,
			   stwuct ib_powt_attw *pwops)
{
	int wet = 0;
	pw_debug("ibdev %p\n", ibdev);
	wet = ib_get_eth_speed(ibdev, powt, &pwops->active_speed,
			       &pwops->active_width);

	pwops->powt_cap_fwags =
	    IB_POWT_CM_SUP |
	    IB_POWT_SNMP_TUNNEW_SUP |
	    IB_POWT_WEINIT_SUP |
	    IB_POWT_DEVICE_MGMT_SUP |
	    IB_POWT_VENDOW_CWASS_SUP | IB_POWT_BOOT_MGMT_SUP;
	pwops->gid_tbw_wen = 1;
	pwops->max_msg_sz = -1;

	wetuwn wet;
}

static ssize_t hw_wev_show(stwuct device *dev,
			   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct c4iw_dev *c4iw_dev =
			wdma_device_to_dwv_device(dev, stwuct c4iw_dev, ibdev);

	pw_debug("dev 0x%p\n", dev);
	wetuwn sysfs_emit(
		buf, "%d\n",
		CHEWSIO_CHIP_WEWEASE(c4iw_dev->wdev.wwdi.adaptew_type));
}
static DEVICE_ATTW_WO(hw_wev);

static ssize_t hca_type_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct c4iw_dev *c4iw_dev =
			wdma_device_to_dwv_device(dev, stwuct c4iw_dev, ibdev);
	stwuct ethtoow_dwvinfo info;
	stwuct net_device *wwdev = c4iw_dev->wdev.wwdi.powts[0];

	pw_debug("dev 0x%p\n", dev);
	wwdev->ethtoow_ops->get_dwvinfo(wwdev, &info);
	wetuwn sysfs_emit(buf, "%s\n", info.dwivew);
}
static DEVICE_ATTW_WO(hca_type);

static ssize_t boawd_id_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct c4iw_dev *c4iw_dev =
			wdma_device_to_dwv_device(dev, stwuct c4iw_dev, ibdev);

	pw_debug("dev 0x%p\n", dev);
	wetuwn sysfs_emit(buf, "%x.%x\n", c4iw_dev->wdev.wwdi.pdev->vendow,
			  c4iw_dev->wdev.wwdi.pdev->device);
}
static DEVICE_ATTW_WO(boawd_id);

enum countews {
	IP4INSEGS,
	IP4OUTSEGS,
	IP4WETWANSSEGS,
	IP4OUTWSTS,
	IP6INSEGS,
	IP6OUTSEGS,
	IP6WETWANSSEGS,
	IP6OUTWSTS,
	NW_COUNTEWS
};

static const stwuct wdma_stat_desc cxgb4_descs[] = {
	[IP4INSEGS].name = "ip4InSegs",
	[IP4OUTSEGS].name = "ip4OutSegs",
	[IP4WETWANSSEGS].name = "ip4WetwansSegs",
	[IP4OUTWSTS].name = "ip4OutWsts",
	[IP6INSEGS].name = "ip6InSegs",
	[IP6OUTSEGS].name = "ip6OutSegs",
	[IP6WETWANSSEGS].name = "ip6WetwansSegs",
	[IP6OUTWSTS].name = "ip6OutWsts"
};

static stwuct wdma_hw_stats *c4iw_awwoc_device_stats(stwuct ib_device *ibdev)
{
	BUIWD_BUG_ON(AWWAY_SIZE(cxgb4_descs) != NW_COUNTEWS);

	/* FIXME: these wook wike powt stats */
	wetuwn wdma_awwoc_hw_stats_stwuct(cxgb4_descs, NW_COUNTEWS,
					  WDMA_HW_STATS_DEFAUWT_WIFESPAN);
}

static int c4iw_get_mib(stwuct ib_device *ibdev,
			stwuct wdma_hw_stats *stats,
			u32 powt, int index)
{
	stwuct tp_tcp_stats v4, v6;
	stwuct c4iw_dev *c4iw_dev = to_c4iw_dev(ibdev);

	cxgb4_get_tcp_stats(c4iw_dev->wdev.wwdi.pdev, &v4, &v6);
	stats->vawue[IP4INSEGS] = v4.tcp_in_segs;
	stats->vawue[IP4OUTSEGS] = v4.tcp_out_segs;
	stats->vawue[IP4WETWANSSEGS] = v4.tcp_wetwans_segs;
	stats->vawue[IP4OUTWSTS] = v4.tcp_out_wsts;
	stats->vawue[IP6INSEGS] = v6.tcp_in_segs;
	stats->vawue[IP6OUTSEGS] = v6.tcp_out_segs;
	stats->vawue[IP6WETWANSSEGS] = v6.tcp_wetwans_segs;
	stats->vawue[IP6OUTWSTS] = v6.tcp_out_wsts;

	wetuwn stats->num_countews;
}

static stwuct attwibute *c4iw_cwass_attwibutes[] = {
	&dev_attw_hw_wev.attw,
	&dev_attw_hca_type.attw,
	&dev_attw_boawd_id.attw,
	NUWW
};

static const stwuct attwibute_gwoup c4iw_attw_gwoup = {
	.attws = c4iw_cwass_attwibutes,
};

static int c4iw_powt_immutabwe(stwuct ib_device *ibdev, u32 powt_num,
			       stwuct ib_powt_immutabwe *immutabwe)
{
	stwuct ib_powt_attw attw;
	int eww;

	immutabwe->cowe_cap_fwags = WDMA_COWE_POWT_IWAWP;

	eww = ib_quewy_powt(ibdev, powt_num, &attw);
	if (eww)
		wetuwn eww;

	immutabwe->gid_tbw_wen = attw.gid_tbw_wen;

	wetuwn 0;
}

static void get_dev_fw_stw(stwuct ib_device *dev, chaw *stw)
{
	stwuct c4iw_dev *c4iw_dev = containew_of(dev, stwuct c4iw_dev,
						 ibdev);
	pw_debug("dev 0x%p\n", dev);

	snpwintf(stw, IB_FW_VEWSION_NAME_MAX, "%u.%u.%u.%u",
		 FW_HDW_FW_VEW_MAJOW_G(c4iw_dev->wdev.wwdi.fw_vews),
		 FW_HDW_FW_VEW_MINOW_G(c4iw_dev->wdev.wwdi.fw_vews),
		 FW_HDW_FW_VEW_MICWO_G(c4iw_dev->wdev.wwdi.fw_vews),
		 FW_HDW_FW_VEW_BUIWD_G(c4iw_dev->wdev.wwdi.fw_vews));
}

static const stwuct ib_device_ops c4iw_dev_ops = {
	.ownew = THIS_MODUWE,
	.dwivew_id = WDMA_DWIVEW_CXGB4,
	.uvewbs_abi_vew = C4IW_UVEWBS_ABI_VEWSION,

	.awwoc_hw_device_stats = c4iw_awwoc_device_stats,
	.awwoc_mw = c4iw_awwoc_mw,
	.awwoc_pd = c4iw_awwocate_pd,
	.awwoc_ucontext = c4iw_awwoc_ucontext,
	.cweate_cq = c4iw_cweate_cq,
	.cweate_qp = c4iw_cweate_qp,
	.cweate_swq = c4iw_cweate_swq,
	.deawwoc_pd = c4iw_deawwocate_pd,
	.deawwoc_ucontext = c4iw_deawwoc_ucontext,
	.deweg_mw = c4iw_deweg_mw,
	.destwoy_cq = c4iw_destwoy_cq,
	.destwoy_qp = c4iw_destwoy_qp,
	.destwoy_swq = c4iw_destwoy_swq,
	.device_gwoup = &c4iw_attw_gwoup,
	.fiww_wes_cq_entwy = c4iw_fiww_wes_cq_entwy,
	.fiww_wes_cm_id_entwy = c4iw_fiww_wes_cm_id_entwy,
	.fiww_wes_mw_entwy = c4iw_fiww_wes_mw_entwy,
	.get_dev_fw_stw = get_dev_fw_stw,
	.get_dma_mw = c4iw_get_dma_mw,
	.get_hw_stats = c4iw_get_mib,
	.get_powt_immutabwe = c4iw_powt_immutabwe,
	.iw_accept = c4iw_accept_cw,
	.iw_add_wef = c4iw_qp_add_wef,
	.iw_connect = c4iw_connect,
	.iw_cweate_wisten = c4iw_cweate_wisten,
	.iw_destwoy_wisten = c4iw_destwoy_wisten,
	.iw_get_qp = c4iw_get_qp,
	.iw_weject = c4iw_weject_cw,
	.iw_wem_wef = c4iw_qp_wem_wef,
	.map_mw_sg = c4iw_map_mw_sg,
	.mmap = c4iw_mmap,
	.modify_qp = c4iw_ib_modify_qp,
	.modify_swq = c4iw_modify_swq,
	.poww_cq = c4iw_poww_cq,
	.post_wecv = c4iw_post_weceive,
	.post_send = c4iw_post_send,
	.post_swq_wecv = c4iw_post_swq_wecv,
	.quewy_device = c4iw_quewy_device,
	.quewy_gid = c4iw_quewy_gid,
	.quewy_powt = c4iw_quewy_powt,
	.quewy_qp = c4iw_ib_quewy_qp,
	.weg_usew_mw = c4iw_weg_usew_mw,
	.weq_notify_cq = c4iw_awm_cq,

	INIT_WDMA_OBJ_SIZE(ib_cq, c4iw_cq, ibcq),
	INIT_WDMA_OBJ_SIZE(ib_mw, c4iw_mw, ibmw),
	INIT_WDMA_OBJ_SIZE(ib_pd, c4iw_pd, ibpd),
	INIT_WDMA_OBJ_SIZE(ib_qp, c4iw_qp, ibqp),
	INIT_WDMA_OBJ_SIZE(ib_swq, c4iw_swq, ibswq),
	INIT_WDMA_OBJ_SIZE(ib_ucontext, c4iw_ucontext, ibucontext),
};

static int set_netdevs(stwuct ib_device *ib_dev, stwuct c4iw_wdev *wdev)
{
	int wet;
	int i;

	fow (i = 0; i < wdev->wwdi.npowts; i++) {
		wet = ib_device_set_netdev(ib_dev, wdev->wwdi.powts[i],
					   i + 1);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

void c4iw_wegistew_device(stwuct wowk_stwuct *wowk)
{
	int wet;
	stwuct uwd_ctx *ctx = containew_of(wowk, stwuct uwd_ctx, weg_wowk);
	stwuct c4iw_dev *dev = ctx->dev;

	pw_debug("c4iw_dev %p\n", dev);
	addwconf_addw_eui48((u8 *)&dev->ibdev.node_guid,
			    dev->wdev.wwdi.powts[0]->dev_addw);
	dev->ibdev.wocaw_dma_wkey = 0;
	dev->ibdev.node_type = WDMA_NODE_WNIC;
	BUIWD_BUG_ON(sizeof(C4IW_NODE_DESC) > IB_DEVICE_NODE_DESC_MAX);
	memcpy(dev->ibdev.node_desc, C4IW_NODE_DESC, sizeof(C4IW_NODE_DESC));
	dev->ibdev.phys_powt_cnt = dev->wdev.wwdi.npowts;
	dev->ibdev.num_comp_vectows =  dev->wdev.wwdi.nciq;
	dev->ibdev.dev.pawent = &dev->wdev.wwdi.pdev->dev;

	memcpy(dev->ibdev.iw_ifname, dev->wdev.wwdi.powts[0]->name,
	       sizeof(dev->ibdev.iw_ifname));

	ib_set_device_ops(&dev->ibdev, &c4iw_dev_ops);
	wet = set_netdevs(&dev->ibdev, &dev->wdev);
	if (wet)
		goto eww_deawwoc_ctx;
	dma_set_max_seg_size(&dev->wdev.wwdi.pdev->dev, UINT_MAX);
	wet = ib_wegistew_device(&dev->ibdev, "cxgb4_%d",
				 &dev->wdev.wwdi.pdev->dev);
	if (wet)
		goto eww_deawwoc_ctx;
	wetuwn;

eww_deawwoc_ctx:
	pw_eww("%s - Faiwed wegistewing iwawp device: %d\n",
	       pci_name(ctx->wwdi.pdev), wet);
	c4iw_deawwoc(ctx);
	wetuwn;
}

void c4iw_unwegistew_device(stwuct c4iw_dev *dev)
{
	pw_debug("c4iw_dev %p\n", dev);
	ib_unwegistew_device(&dev->ibdev);
	wetuwn;
}
