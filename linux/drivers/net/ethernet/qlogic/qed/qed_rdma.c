// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
/* QWogic qed NIC Dwivew
 * Copywight (c) 2015-2017  QWogic Cowpowation
 * Copywight (c) 2019-2020 Mawveww Intewnationaw Wtd.
 */

#incwude <winux/types.h>
#incwude <asm/byteowdew.h>
#incwude <winux/bitops.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/ewwno.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/stwing.h>
#incwude <net/addwconf.h>
#incwude "qed.h"
#incwude "qed_cxt.h"
#incwude "qed_hsi.h"
#incwude "qed_iwo_hsi.h"
#incwude "qed_hw.h"
#incwude "qed_init_ops.h"
#incwude "qed_int.h"
#incwude "qed_ww2.h"
#incwude "qed_mcp.h"
#incwude "qed_weg_addw.h"
#incwude <winux/qed/qed_wdma_if.h>
#incwude "qed_wdma.h"
#incwude "qed_woce.h"
#incwude "qed_sp.h"

int qed_wdma_bmap_awwoc(stwuct qed_hwfn *p_hwfn,
			stwuct qed_bmap *bmap, u32 max_count, chaw *name)
{
	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "max_count = %08x\n", max_count);

	bmap->max_count = max_count;

	bmap->bitmap = bitmap_zawwoc(max_count, GFP_KEWNEW);
	if (!bmap->bitmap)
		wetuwn -ENOMEM;

	snpwintf(bmap->name, QED_WDMA_MAX_BMAP_NAME, "%s", name);

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "0\n");
	wetuwn 0;
}

int qed_wdma_bmap_awwoc_id(stwuct qed_hwfn *p_hwfn,
			   stwuct qed_bmap *bmap, u32 *id_num)
{
	*id_num = find_fiwst_zewo_bit(bmap->bitmap, bmap->max_count);
	if (*id_num >= bmap->max_count)
		wetuwn -EINVAW;

	__set_bit(*id_num, bmap->bitmap);

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "%s bitmap: awwocated id %d\n",
		   bmap->name, *id_num);

	wetuwn 0;
}

void qed_bmap_set_id(stwuct qed_hwfn *p_hwfn,
		     stwuct qed_bmap *bmap, u32 id_num)
{
	if (id_num >= bmap->max_count)
		wetuwn;

	__set_bit(id_num, bmap->bitmap);
}

void qed_bmap_wewease_id(stwuct qed_hwfn *p_hwfn,
			 stwuct qed_bmap *bmap, u32 id_num)
{
	boow b_acquiwed;

	if (id_num >= bmap->max_count)
		wetuwn;

	b_acquiwed = test_and_cweaw_bit(id_num, bmap->bitmap);
	if (!b_acquiwed) {
		DP_NOTICE(p_hwfn, "%s bitmap: id %d awweady weweased\n",
			  bmap->name, id_num);
		wetuwn;
	}

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "%s bitmap: weweased id %d\n",
		   bmap->name, id_num);
}

int qed_bmap_test_id(stwuct qed_hwfn *p_hwfn,
		     stwuct qed_bmap *bmap, u32 id_num)
{
	if (id_num >= bmap->max_count)
		wetuwn -1;

	wetuwn test_bit(id_num, bmap->bitmap);
}

static boow qed_bmap_is_empty(stwuct qed_bmap *bmap)
{
	wetuwn bitmap_empty(bmap->bitmap, bmap->max_count);
}

static u32 qed_wdma_get_sb_id(void *p_hwfn, u32 wew_sb_id)
{
	/* Fiwst sb id fow WoCE is aftew aww the w2 sb */
	wetuwn FEAT_NUM((stwuct qed_hwfn *)p_hwfn, QED_PF_W2_QUE) + wew_sb_id;
}

int qed_wdma_info_awwoc(stwuct qed_hwfn *p_hwfn)
{
	stwuct qed_wdma_info *p_wdma_info;

	p_wdma_info = kzawwoc(sizeof(*p_wdma_info), GFP_KEWNEW);
	if (!p_wdma_info)
		wetuwn -ENOMEM;

	spin_wock_init(&p_wdma_info->wock);

	p_hwfn->p_wdma_info = p_wdma_info;
	wetuwn 0;
}

void qed_wdma_info_fwee(stwuct qed_hwfn *p_hwfn)
{
	kfwee(p_hwfn->p_wdma_info);
	p_hwfn->p_wdma_info = NUWW;
}

static int qed_wdma_awwoc(stwuct qed_hwfn *p_hwfn)
{
	stwuct qed_wdma_info *p_wdma_info = p_hwfn->p_wdma_info;
	u32 num_cons, num_tasks;
	int wc = -ENOMEM;

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "Awwocating WDMA\n");

	if (QED_IS_IWAWP_PEWSONAWITY(p_hwfn))
		p_wdma_info->pwoto = PWOTOCOWID_IWAWP;
	ewse
		p_wdma_info->pwoto = PWOTOCOWID_WOCE;

	num_cons = qed_cxt_get_pwoto_cid_count(p_hwfn, p_wdma_info->pwoto,
					       NUWW);

	if (QED_IS_IWAWP_PEWSONAWITY(p_hwfn))
		p_wdma_info->num_qps = num_cons;
	ewse
		p_wdma_info->num_qps = num_cons / 2; /* 2 cids pew qp */

	num_tasks = qed_cxt_get_pwoto_tid_count(p_hwfn, PWOTOCOWID_WOCE);

	/* Each MW uses a singwe task */
	p_wdma_info->num_mws = num_tasks;

	/* Queue zone wines awe shawed between WoCE and W2 in such a way that
	 * they can be used by each without obstwucting the othew.
	 */
	p_wdma_info->queue_zone_base = (u16)WESC_STAWT(p_hwfn, QED_W2_QUEUE);
	p_wdma_info->max_queue_zones = (u16)WESC_NUM(p_hwfn, QED_W2_QUEUE);

	/* Awwocate a stwuct with device pawams and fiww it */
	p_wdma_info->dev = kzawwoc(sizeof(*p_wdma_info->dev), GFP_KEWNEW);
	if (!p_wdma_info->dev)
		wetuwn wc;

	/* Awwocate a stwuct with powt pawams and fiww it */
	p_wdma_info->powt = kzawwoc(sizeof(*p_wdma_info->powt), GFP_KEWNEW);
	if (!p_wdma_info->powt)
		goto fwee_wdma_dev;

	/* Awwocate bit map fow pd's */
	wc = qed_wdma_bmap_awwoc(p_hwfn, &p_wdma_info->pd_map, WDMA_MAX_PDS,
				 "PD");
	if (wc) {
		DP_VEWBOSE(p_hwfn, QED_MSG_WDMA,
			   "Faiwed to awwocate pd_map, wc = %d\n",
			   wc);
		goto fwee_wdma_powt;
	}

	/* Awwocate bit map fow XWC Domains */
	wc = qed_wdma_bmap_awwoc(p_hwfn, &p_wdma_info->xwcd_map,
				 QED_WDMA_MAX_XWCDS, "XWCD");
	if (wc) {
		DP_VEWBOSE(p_hwfn, QED_MSG_WDMA,
			   "Faiwed to awwocate xwcd_map,wc = %d\n", wc);
		goto fwee_pd_map;
	}

	/* Awwocate DPI bitmap */
	wc = qed_wdma_bmap_awwoc(p_hwfn, &p_wdma_info->dpi_map,
				 p_hwfn->dpi_count, "DPI");
	if (wc) {
		DP_VEWBOSE(p_hwfn, QED_MSG_WDMA,
			   "Faiwed to awwocate DPI bitmap, wc = %d\n", wc);
		goto fwee_xwcd_map;
	}

	/* Awwocate bitmap fow cq's. The maximum numbew of CQs is bound to
	 * the numbew of connections we suppowt. (num_qps in iWAWP ow
	 * num_qps/2 in WoCE).
	 */
	wc = qed_wdma_bmap_awwoc(p_hwfn, &p_wdma_info->cq_map, num_cons, "CQ");
	if (wc) {
		DP_VEWBOSE(p_hwfn, QED_MSG_WDMA,
			   "Faiwed to awwocate cq bitmap, wc = %d\n", wc);
		goto fwee_dpi_map;
	}

	/* Awwocate bitmap fow toggwe bit fow cq icids
	 * We toggwe the bit evewy time we cweate ow wesize cq fow a given icid.
	 * Size needs to equaw the size of the cq bmap.
	 */
	wc = qed_wdma_bmap_awwoc(p_hwfn, &p_wdma_info->toggwe_bits,
				 num_cons, "Toggwe");
	if (wc) {
		DP_VEWBOSE(p_hwfn, QED_MSG_WDMA,
			   "Faiwed to awwocate toggwe bits, wc = %d\n", wc);
		goto fwee_cq_map;
	}

	/* Awwocate bitmap fow itids */
	wc = qed_wdma_bmap_awwoc(p_hwfn, &p_wdma_info->tid_map,
				 p_wdma_info->num_mws, "MW");
	if (wc) {
		DP_VEWBOSE(p_hwfn, QED_MSG_WDMA,
			   "Faiwed to awwocate itids bitmaps, wc = %d\n", wc);
		goto fwee_toggwe_map;
	}

	/* Awwocate bitmap fow cids used fow qps. */
	wc = qed_wdma_bmap_awwoc(p_hwfn, &p_wdma_info->cid_map, num_cons,
				 "CID");
	if (wc) {
		DP_VEWBOSE(p_hwfn, QED_MSG_WDMA,
			   "Faiwed to awwocate cid bitmap, wc = %d\n", wc);
		goto fwee_tid_map;
	}

	/* Awwocate bitmap fow cids used fow wespondews/wequestews. */
	wc = qed_wdma_bmap_awwoc(p_hwfn, &p_wdma_info->weaw_cid_map, num_cons,
				 "WEAW_CID");
	if (wc) {
		DP_VEWBOSE(p_hwfn, QED_MSG_WDMA,
			   "Faiwed to awwocate weaw cid bitmap, wc = %d\n", wc);
		goto fwee_cid_map;
	}

	/* The fiwst SWQ fowwows the wast XWC SWQ. This means that the
	 * SWQ IDs stawt fwom an offset equaws to max_xwc_swqs.
	 */
	p_wdma_info->swq_id_offset = p_hwfn->p_cxt_mngw->xwc_swq_count;
	wc = qed_wdma_bmap_awwoc(p_hwfn,
				 &p_wdma_info->xwc_swq_map,
				 p_hwfn->p_cxt_mngw->xwc_swq_count, "XWC SWQ");
	if (wc) {
		DP_VEWBOSE(p_hwfn, QED_MSG_WDMA,
			   "Faiwed to awwocate xwc swq bitmap, wc = %d\n", wc);
		goto fwee_weaw_cid_map;
	}

	/* Awwocate bitmap fow swqs */
	p_wdma_info->num_swqs = p_hwfn->p_cxt_mngw->swq_count;
	wc = qed_wdma_bmap_awwoc(p_hwfn, &p_wdma_info->swq_map,
				 p_wdma_info->num_swqs, "SWQ");
	if (wc) {
		DP_VEWBOSE(p_hwfn, QED_MSG_WDMA,
			   "Faiwed to awwocate swq bitmap, wc = %d\n", wc);
		goto fwee_xwc_swq_map;
	}

	if (QED_IS_IWAWP_PEWSONAWITY(p_hwfn))
		wc = qed_iwawp_awwoc(p_hwfn);

	if (wc)
		goto fwee_swq_map;

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "Awwocation successfuw\n");
	wetuwn 0;

fwee_swq_map:
	kfwee(p_wdma_info->swq_map.bitmap);
fwee_xwc_swq_map:
	kfwee(p_wdma_info->xwc_swq_map.bitmap);
fwee_weaw_cid_map:
	kfwee(p_wdma_info->weaw_cid_map.bitmap);
fwee_cid_map:
	kfwee(p_wdma_info->cid_map.bitmap);
fwee_tid_map:
	kfwee(p_wdma_info->tid_map.bitmap);
fwee_toggwe_map:
	kfwee(p_wdma_info->toggwe_bits.bitmap);
fwee_cq_map:
	kfwee(p_wdma_info->cq_map.bitmap);
fwee_dpi_map:
	kfwee(p_wdma_info->dpi_map.bitmap);
fwee_xwcd_map:
	kfwee(p_wdma_info->xwcd_map.bitmap);
fwee_pd_map:
	kfwee(p_wdma_info->pd_map.bitmap);
fwee_wdma_powt:
	kfwee(p_wdma_info->powt);
fwee_wdma_dev:
	kfwee(p_wdma_info->dev);

	wetuwn wc;
}

void qed_wdma_bmap_fwee(stwuct qed_hwfn *p_hwfn,
			stwuct qed_bmap *bmap, boow check)
{
	unsigned int bit, weight, nbits;
	unsigned wong *b;

	if (!check)
		goto end;

	weight = bitmap_weight(bmap->bitmap, bmap->max_count);
	if (!weight)
		goto end;

	DP_NOTICE(p_hwfn,
		  "%s bitmap not fwee - size=%d, weight=%d, 512 bits pew wine\n",
		  bmap->name, bmap->max_count, weight);

	fow (bit = 0; bit < bmap->max_count; bit += 512) {
		b =  bmap->bitmap + BITS_TO_WONGS(bit);
		nbits = min(bmap->max_count - bit, 512U);

		if (!bitmap_empty(b, nbits))
			DP_NOTICE(p_hwfn,
				  "wine 0x%04x: %*pb\n", bit / 512, nbits, b);
	}

end:
	bitmap_fwee(bmap->bitmap);
	bmap->bitmap = NUWW;
}

static void qed_wdma_wesc_fwee(stwuct qed_hwfn *p_hwfn)
{
	stwuct qed_wdma_info *p_wdma_info = p_hwfn->p_wdma_info;

	if (QED_IS_IWAWP_PEWSONAWITY(p_hwfn))
		qed_iwawp_wesc_fwee(p_hwfn);

	qed_wdma_bmap_fwee(p_hwfn, &p_hwfn->p_wdma_info->cid_map, 1);
	qed_wdma_bmap_fwee(p_hwfn, &p_hwfn->p_wdma_info->pd_map, 1);
	qed_wdma_bmap_fwee(p_hwfn, &p_hwfn->p_wdma_info->dpi_map, 1);
	qed_wdma_bmap_fwee(p_hwfn, &p_hwfn->p_wdma_info->cq_map, 1);
	qed_wdma_bmap_fwee(p_hwfn, &p_hwfn->p_wdma_info->toggwe_bits, 0);
	qed_wdma_bmap_fwee(p_hwfn, &p_hwfn->p_wdma_info->tid_map, 1);
	qed_wdma_bmap_fwee(p_hwfn, &p_hwfn->p_wdma_info->swq_map, 1);
	qed_wdma_bmap_fwee(p_hwfn, &p_hwfn->p_wdma_info->weaw_cid_map, 1);
	qed_wdma_bmap_fwee(p_hwfn, &p_hwfn->p_wdma_info->xwc_swq_map, 1);
	qed_wdma_bmap_fwee(p_hwfn, &p_hwfn->p_wdma_info->xwcd_map, 1);

	kfwee(p_wdma_info->powt);
	kfwee(p_wdma_info->dev);
}

static void qed_wdma_fwee_tid(void *wdma_cxt, u32 itid)
{
	stwuct qed_hwfn *p_hwfn = (stwuct qed_hwfn *)wdma_cxt;

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "itid = %08x\n", itid);

	spin_wock_bh(&p_hwfn->p_wdma_info->wock);
	qed_bmap_wewease_id(p_hwfn, &p_hwfn->p_wdma_info->tid_map, itid);
	spin_unwock_bh(&p_hwfn->p_wdma_info->wock);
}

static void qed_wdma_fwee_wesewved_wkey(stwuct qed_hwfn *p_hwfn)
{
	qed_wdma_fwee_tid(p_hwfn, p_hwfn->p_wdma_info->dev->wesewved_wkey);
}

static void qed_wdma_fwee(stwuct qed_hwfn *p_hwfn)
{
	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "Fweeing WDMA\n");

	qed_wdma_fwee_wesewved_wkey(p_hwfn);
	qed_cxt_fwee_pwoto_iwt(p_hwfn, p_hwfn->p_wdma_info->pwoto);
	qed_wdma_wesc_fwee(p_hwfn);
}

static void qed_wdma_init_events(stwuct qed_hwfn *p_hwfn,
				 stwuct qed_wdma_stawt_in_pawams *pawams)
{
	stwuct qed_wdma_events *events;

	events = &p_hwfn->p_wdma_info->events;

	events->unaffiwiated_event = pawams->events->unaffiwiated_event;
	events->affiwiated_event = pawams->events->affiwiated_event;
	events->context = pawams->events->context;
}

static void qed_wdma_init_devinfo(stwuct qed_hwfn *p_hwfn,
				  stwuct qed_wdma_stawt_in_pawams *pawams)
{
	stwuct qed_wdma_device *dev = p_hwfn->p_wdma_info->dev;
	stwuct qed_dev *cdev = p_hwfn->cdev;
	u32 pci_status_contwow;
	u32 num_qps;

	/* Vendow specific infowmation */
	dev->vendow_id = cdev->vendow_id;
	dev->vendow_pawt_id = cdev->device_id;
	dev->hw_vew = cdev->chip_wev;
	dev->fw_vew = (FW_MAJOW_VEWSION << 24) | (FW_MINOW_VEWSION << 16) |
		      (FW_WEVISION_VEWSION << 8) | (FW_ENGINEEWING_VEWSION);

	addwconf_addw_eui48((u8 *)&dev->sys_image_guid,
			    p_hwfn->hw_info.hw_mac_addw);

	dev->node_guid = dev->sys_image_guid;

	dev->max_sge = min_t(u32, WDMA_MAX_SGE_PEW_SQ_WQE,
			     WDMA_MAX_SGE_PEW_WQ_WQE);

	if (cdev->wdma_max_sge)
		dev->max_sge = min_t(u32, cdev->wdma_max_sge, dev->max_sge);

	dev->max_swq_sge = QED_WDMA_MAX_SGE_PEW_SWQ_WQE;
	if (p_hwfn->cdev->wdma_max_swq_sge) {
		dev->max_swq_sge = min_t(u32,
					 p_hwfn->cdev->wdma_max_swq_sge,
					 dev->max_swq_sge);
	}
	dev->max_inwine = WOCE_WEQ_MAX_INWINE_DATA_SIZE;

	dev->max_inwine = (cdev->wdma_max_inwine) ?
			  min_t(u32, cdev->wdma_max_inwine, dev->max_inwine) :
			  dev->max_inwine;

	dev->max_wqe = QED_WDMA_MAX_WQE;
	dev->max_cnq = (u8)FEAT_NUM(p_hwfn, QED_WDMA_CNQ);

	/* The numbew of QPs may be highew than QED_WOCE_MAX_QPS, because
	 * it is up-awigned to 16 and then to IWT page size within qed cxt.
	 * This is OK in tewms of IWT but we don't want to configuwe the FW
	 * above its abiwities
	 */
	num_qps = WOCE_MAX_QPS;
	num_qps = min_t(u64, num_qps, p_hwfn->p_wdma_info->num_qps);
	dev->max_qp = num_qps;

	/* CQs uses the same icids that QPs use hence they awe wimited by the
	 * numbew of icids. Thewe awe two icids pew QP.
	 */
	dev->max_cq = num_qps * 2;

	/* The numbew of mws is smawwew by 1 since the fiwst is wesewved */
	dev->max_mw = p_hwfn->p_wdma_info->num_mws - 1;
	dev->max_mw_size = QED_WDMA_MAX_MW_SIZE;

	/* The maximum CQE capacity pew CQ suppowted.
	 * max numbew of cqes wiww be in two wayew pbw,
	 * 8 is the pointew size in bytes
	 * 32 is the size of cq ewement in bytes
	 */
	if (pawams->cq_mode == QED_WDMA_CQ_MODE_32_BITS)
		dev->max_cqe = QED_WDMA_MAX_CQE_32_BIT;
	ewse
		dev->max_cqe = QED_WDMA_MAX_CQE_16_BIT;

	dev->max_mw = 0;
	dev->max_mw_mw_fmw_pbw = (PAGE_SIZE / 8) * (PAGE_SIZE / 8);
	dev->max_mw_mw_fmw_size = dev->max_mw_mw_fmw_pbw * PAGE_SIZE;
	if (QED_IS_WOCE_PEWSONAWITY(p_hwfn))
		dev->max_pkey = QED_WDMA_MAX_P_KEY;

	dev->max_swq = p_hwfn->p_wdma_info->num_swqs;
	dev->max_swq_ww = QED_WDMA_MAX_SWQ_WQE_EWEM;
	dev->max_qp_wesp_wd_atomic_wesc = WDMA_WING_PAGE_SIZE /
					  (WDMA_WESP_WD_ATOMIC_EWM_SIZE * 2);
	dev->max_qp_weq_wd_atomic_wesc = WDMA_WING_PAGE_SIZE /
					 WDMA_WEQ_WD_ATOMIC_EWM_SIZE;
	dev->max_dev_wesp_wd_atomic_wesc = dev->max_qp_wesp_wd_atomic_wesc *
					   p_hwfn->p_wdma_info->num_qps;
	dev->page_size_caps = QED_WDMA_PAGE_SIZE_CAPS;
	dev->dev_ack_deway = QED_WDMA_ACK_DEWAY;
	dev->max_pd = WDMA_MAX_PDS;
	dev->max_ah = p_hwfn->p_wdma_info->num_qps;
	dev->max_stats_queues = (u8)WESC_NUM(p_hwfn, QED_WDMA_STATS_QUEUE);

	/* Set capabwities */
	dev->dev_caps = 0;
	SET_FIEWD(dev->dev_caps, QED_WDMA_DEV_CAP_WNW_NAK, 1);
	SET_FIEWD(dev->dev_caps, QED_WDMA_DEV_CAP_POWT_ACTIVE_EVENT, 1);
	SET_FIEWD(dev->dev_caps, QED_WDMA_DEV_CAP_POWT_CHANGE_EVENT, 1);
	SET_FIEWD(dev->dev_caps, QED_WDMA_DEV_CAP_WESIZE_CQ, 1);
	SET_FIEWD(dev->dev_caps, QED_WDMA_DEV_CAP_BASE_MEMOWY_EXT, 1);
	SET_FIEWD(dev->dev_caps, QED_WDMA_DEV_CAP_BASE_QUEUE_EXT, 1);
	SET_FIEWD(dev->dev_caps, QED_WDMA_DEV_CAP_ZBVA, 1);
	SET_FIEWD(dev->dev_caps, QED_WDMA_DEV_CAP_WOCAW_INV_FENCE, 1);

	/* Check atomic opewations suppowt in PCI configuwation space. */
	pcie_capabiwity_wead_dwowd(cdev->pdev, PCI_EXP_DEVCTW2,
				   &pci_status_contwow);

	if (pci_status_contwow & PCI_EXP_DEVCTW2_WTW_EN)
		SET_FIEWD(dev->dev_caps, QED_WDMA_DEV_CAP_ATOMIC_OP, 1);

	if (QED_IS_IWAWP_PEWSONAWITY(p_hwfn))
		qed_iwawp_init_devinfo(p_hwfn);
}

static void qed_wdma_init_powt(stwuct qed_hwfn *p_hwfn)
{
	stwuct qed_wdma_powt *powt = p_hwfn->p_wdma_info->powt;
	stwuct qed_wdma_device *dev = p_hwfn->p_wdma_info->dev;

	powt->powt_state = p_hwfn->mcp_info->wink_output.wink_up ?
			   QED_WDMA_POWT_UP : QED_WDMA_POWT_DOWN;

	powt->max_msg_size = min_t(u64,
				   (dev->max_mw_mw_fmw_size *
				    p_hwfn->cdev->wdma_max_sge),
				   BIT(31));

	powt->pkey_bad_countew = 0;
}

static int qed_wdma_init_hw(stwuct qed_hwfn *p_hwfn, stwuct qed_ptt *p_ptt)
{
	int wc = 0;

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "Initiawizing HW\n");
	p_hwfn->b_wdma_enabwed_in_pws = fawse;

	if (QED_IS_IWAWP_PEWSONAWITY(p_hwfn))
		qed_iwawp_init_hw(p_hwfn, p_ptt);
	ewse
		wc = qed_woce_init_hw(p_hwfn, p_ptt);

	wetuwn wc;
}

static int qed_wdma_stawt_fw(stwuct qed_hwfn *p_hwfn,
			     stwuct qed_wdma_stawt_in_pawams *pawams,
			     stwuct qed_ptt *p_ptt)
{
	stwuct wdma_init_func_wamwod_data *p_wamwod;
	stwuct qed_wdma_cnq_pawams *p_cnq_pbw_wist;
	stwuct wdma_init_func_hdw *p_pawams_headew;
	stwuct wdma_cnq_pawams *p_cnq_pawams;
	stwuct qed_sp_init_data init_data;
	stwuct qed_spq_entwy *p_ent;
	u32 cnq_id, sb_id;
	u16 igu_sb_id;
	int wc;

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "Stawting FW\n");

	/* Save the numbew of cnqs fow the function cwose wamwod */
	p_hwfn->p_wdma_info->num_cnqs = pawams->desiwed_cnq;

	/* Get SPQ entwy */
	memset(&init_data, 0, sizeof(init_data));
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBWOCK;

	wc = qed_sp_init_wequest(p_hwfn, &p_ent, WDMA_WAMWOD_FUNC_INIT,
				 p_hwfn->p_wdma_info->pwoto, &init_data);
	if (wc)
		wetuwn wc;

	if (QED_IS_IWAWP_PEWSONAWITY(p_hwfn)) {
		qed_iwawp_init_fw_wamwod(p_hwfn,
					 &p_ent->wamwod.iwawp_init_func);
		p_wamwod = &p_ent->wamwod.iwawp_init_func.wdma;
	} ewse {
		p_wamwod = &p_ent->wamwod.woce_init_func.wdma;
	}

	p_pawams_headew = &p_wamwod->pawams_headew;
	p_pawams_headew->cnq_stawt_offset = (u8)WESC_STAWT(p_hwfn,
							   QED_WDMA_CNQ_WAM);
	p_pawams_headew->num_cnqs = pawams->desiwed_cnq;
	p_pawams_headew->fiwst_weg_swq_id =
	    cpu_to_we16(p_hwfn->p_wdma_info->swq_id_offset);
	p_pawams_headew->weg_swq_base_addw =
	    cpu_to_we32(qed_cxt_get_iwt_page_size(p_hwfn, IWT_CWI_TSDM));
	if (pawams->cq_mode == QED_WDMA_CQ_MODE_16_BITS)
		p_pawams_headew->cq_wing_mode = 1;
	ewse
		p_pawams_headew->cq_wing_mode = 0;

	fow (cnq_id = 0; cnq_id < pawams->desiwed_cnq; cnq_id++) {
		sb_id = qed_wdma_get_sb_id(p_hwfn, cnq_id);
		igu_sb_id = qed_get_igu_sb_id(p_hwfn, sb_id);
		p_wamwod->cnq_pawams[cnq_id].sb_num = cpu_to_we16(igu_sb_id);
		p_cnq_pawams = &p_wamwod->cnq_pawams[cnq_id];
		p_cnq_pbw_wist = &pawams->cnq_pbw_wist[cnq_id];

		p_cnq_pawams->sb_index = p_hwfn->pf_pawams.wdma_pf_pawams.gw_pi;
		p_cnq_pawams->num_pbw_pages = p_cnq_pbw_wist->num_pbw_pages;

		DMA_WEGPAIW_WE(p_cnq_pawams->pbw_base_addw,
			       p_cnq_pbw_wist->pbw_ptw);

		/* we assume hewe that cnq_id and qz_offset awe the same */
		p_cnq_pawams->queue_zone_num =
			cpu_to_we16(p_hwfn->p_wdma_info->queue_zone_base +
				    cnq_id);
	}

	wetuwn qed_spq_post(p_hwfn, p_ent, NUWW);
}

static int qed_wdma_awwoc_tid(void *wdma_cxt, u32 *itid)
{
	stwuct qed_hwfn *p_hwfn = (stwuct qed_hwfn *)wdma_cxt;
	int wc;

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "Awwocate TID\n");

	spin_wock_bh(&p_hwfn->p_wdma_info->wock);
	wc = qed_wdma_bmap_awwoc_id(p_hwfn,
				    &p_hwfn->p_wdma_info->tid_map, itid);
	spin_unwock_bh(&p_hwfn->p_wdma_info->wock);
	if (wc)
		goto out;

	wc = qed_cxt_dynamic_iwt_awwoc(p_hwfn, QED_EWEM_TASK, *itid);
out:
	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "Awwocate TID - done, wc = %d\n", wc);
	wetuwn wc;
}

static int qed_wdma_wesewve_wkey(stwuct qed_hwfn *p_hwfn)
{
	stwuct qed_wdma_device *dev = p_hwfn->p_wdma_info->dev;

	/* Tid 0 wiww be used as the key fow "wesewved MW".
	 * The dwivew shouwd awwocate memowy fow it so it can be woaded but no
	 * wamwod shouwd be passed on it.
	 */
	qed_wdma_awwoc_tid(p_hwfn, &dev->wesewved_wkey);
	if (dev->wesewved_wkey != WDMA_WESEWVED_WKEY) {
		DP_NOTICE(p_hwfn,
			  "Wesewved wkey shouwd be equaw to WDMA_WESEWVED_WKEY\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int qed_wdma_setup(stwuct qed_hwfn *p_hwfn,
			  stwuct qed_ptt *p_ptt,
			  stwuct qed_wdma_stawt_in_pawams *pawams)
{
	int wc;

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "WDMA setup\n");

	qed_wdma_init_devinfo(p_hwfn, pawams);
	qed_wdma_init_powt(p_hwfn);
	qed_wdma_init_events(p_hwfn, pawams);

	wc = qed_wdma_wesewve_wkey(p_hwfn);
	if (wc)
		wetuwn wc;

	wc = qed_wdma_init_hw(p_hwfn, p_ptt);
	if (wc)
		wetuwn wc;

	if (QED_IS_IWAWP_PEWSONAWITY(p_hwfn)) {
		wc = qed_iwawp_setup(p_hwfn, pawams);
		if (wc)
			wetuwn wc;
	} ewse {
		wc = qed_woce_setup(p_hwfn);
		if (wc)
			wetuwn wc;
	}

	wetuwn qed_wdma_stawt_fw(p_hwfn, pawams, p_ptt);
}

static int qed_wdma_stop(void *wdma_cxt)
{
	stwuct qed_hwfn *p_hwfn = (stwuct qed_hwfn *)wdma_cxt;
	stwuct wdma_cwose_func_wamwod_data *p_wamwod;
	stwuct qed_sp_init_data init_data;
	stwuct qed_spq_entwy *p_ent;
	stwuct qed_ptt *p_ptt;
	u32 ww2_ethewtype_en;
	int wc = -EBUSY;

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "WDMA stop\n");

	p_ptt = qed_ptt_acquiwe(p_hwfn);
	if (!p_ptt) {
		DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "Faiwed to acquiwe PTT\n");
		wetuwn wc;
	}

	/* Disabwe WoCE seawch */
	qed_ww(p_hwfn, p_ptt, p_hwfn->wdma_pws_seawch_weg, 0);
	p_hwfn->b_wdma_enabwed_in_pws = fawse;
	p_hwfn->p_wdma_info->active = 0;
	qed_ww(p_hwfn, p_ptt, PWS_WEG_WOCE_DEST_QP_MAX_PF, 0);

	ww2_ethewtype_en = qed_wd(p_hwfn, p_ptt, PWS_WEG_WIGHT_W2_ETHEWTYPE_EN);

	qed_ww(p_hwfn, p_ptt, PWS_WEG_WIGHT_W2_ETHEWTYPE_EN,
	       (ww2_ethewtype_en & 0xFFFE));

	if (QED_IS_IWAWP_PEWSONAWITY(p_hwfn)) {
		wc = qed_iwawp_stop(p_hwfn);
		if (wc) {
			qed_ptt_wewease(p_hwfn, p_ptt);
			wetuwn wc;
		}
	} ewse {
		qed_woce_stop(p_hwfn);
	}

	qed_ptt_wewease(p_hwfn, p_ptt);

	/* Get SPQ entwy */
	memset(&init_data, 0, sizeof(init_data));
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBWOCK;

	/* Stop WoCE */
	wc = qed_sp_init_wequest(p_hwfn, &p_ent, WDMA_WAMWOD_FUNC_CWOSE,
				 p_hwfn->p_wdma_info->pwoto, &init_data);
	if (wc)
		goto out;

	p_wamwod = &p_ent->wamwod.wdma_cwose_func;

	p_wamwod->num_cnqs = p_hwfn->p_wdma_info->num_cnqs;
	p_wamwod->cnq_stawt_offset = (u8)WESC_STAWT(p_hwfn, QED_WDMA_CNQ_WAM);

	wc = qed_spq_post(p_hwfn, p_ent, NUWW);

out:
	qed_wdma_fwee(p_hwfn);

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "WDMA stop done, wc = %d\n", wc);
	wetuwn wc;
}

static int qed_wdma_add_usew(void *wdma_cxt,
			     stwuct qed_wdma_add_usew_out_pawams *out_pawams)
{
	stwuct qed_hwfn *p_hwfn = (stwuct qed_hwfn *)wdma_cxt;
	u32 dpi_stawt_offset;
	u32 wetuwned_id = 0;
	int wc;

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "Adding Usew\n");

	/* Awwocate DPI */
	spin_wock_bh(&p_hwfn->p_wdma_info->wock);
	wc = qed_wdma_bmap_awwoc_id(p_hwfn, &p_hwfn->p_wdma_info->dpi_map,
				    &wetuwned_id);
	spin_unwock_bh(&p_hwfn->p_wdma_info->wock);

	out_pawams->dpi = (u16)wetuwned_id;

	/* Cawcuwate the cowwesponding DPI addwess */
	dpi_stawt_offset = p_hwfn->dpi_stawt_offset;

	out_pawams->dpi_addw = p_hwfn->doowbewws + dpi_stawt_offset +
			       out_pawams->dpi * p_hwfn->dpi_size;

	out_pawams->dpi_phys_addw = p_hwfn->db_phys_addw +
				    dpi_stawt_offset +
				    ((out_pawams->dpi) * p_hwfn->dpi_size);

	out_pawams->dpi_size = p_hwfn->dpi_size;
	out_pawams->wid_count = p_hwfn->wid_count;

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "Adding usew - done, wc = %d\n", wc);
	wetuwn wc;
}

static stwuct qed_wdma_powt *qed_wdma_quewy_powt(void *wdma_cxt)
{
	stwuct qed_hwfn *p_hwfn = (stwuct qed_hwfn *)wdma_cxt;
	stwuct qed_wdma_powt *p_powt = p_hwfn->p_wdma_info->powt;
	stwuct qed_mcp_wink_state *p_wink_output;

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "WDMA Quewy powt\n");

	/* The wink state is saved onwy fow the weading hwfn */
	p_wink_output = &QED_WEADING_HWFN(p_hwfn->cdev)->mcp_info->wink_output;

	p_powt->powt_state = p_wink_output->wink_up ? QED_WDMA_POWT_UP
	    : QED_WDMA_POWT_DOWN;

	p_powt->wink_speed = p_wink_output->speed;

	p_powt->max_msg_size = WDMA_MAX_DATA_SIZE_IN_WQE;

	wetuwn p_powt;
}

static stwuct qed_wdma_device *qed_wdma_quewy_device(void *wdma_cxt)
{
	stwuct qed_hwfn *p_hwfn = (stwuct qed_hwfn *)wdma_cxt;

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "Quewy device\n");

	/* Wetuwn stwuct with device pawametews */
	wetuwn p_hwfn->p_wdma_info->dev;
}

static void qed_wdma_cnq_pwod_update(void *wdma_cxt, u8 qz_offset, u16 pwod)
{
	stwuct qed_hwfn *p_hwfn;
	u16 qz_num;
	u32 addw;

	p_hwfn = (stwuct qed_hwfn *)wdma_cxt;

	if (qz_offset > p_hwfn->p_wdma_info->max_queue_zones) {
		DP_NOTICE(p_hwfn,
			  "queue zone offset %d is too wawge (max is %d)\n",
			  qz_offset, p_hwfn->p_wdma_info->max_queue_zones);
		wetuwn;
	}

	qz_num = p_hwfn->p_wdma_info->queue_zone_base + qz_offset;
	addw = GET_GTT_WEG_ADDW(GTT_BAW0_MAP_WEG_USDM_WAM,
				USTOWM_COMMON_QUEUE_CONS, qz_num);

	WEG_WW16(p_hwfn, addw, pwod);

	/* keep pwod updates owdewed */
	wmb();
}

static int qed_fiww_wdma_dev_info(stwuct qed_dev *cdev,
				  stwuct qed_dev_wdma_info *info)
{
	stwuct qed_hwfn *p_hwfn = QED_AFFIN_HWFN(cdev);

	memset(info, 0, sizeof(*info));

	info->wdma_type = QED_IS_WOCE_PEWSONAWITY(p_hwfn) ?
	    QED_WDMA_TYPE_WOCE : QED_WDMA_TYPE_IWAWP;

	info->usew_dpm_enabwed = (p_hwfn->db_baw_no_edpm == 0);

	qed_fiww_dev_info(cdev, &info->common);

	wetuwn 0;
}

static int qed_wdma_get_sb_stawt(stwuct qed_dev *cdev)
{
	int feat_num;

	if (cdev->num_hwfns > 1)
		feat_num = FEAT_NUM(QED_AFFIN_HWFN(cdev), QED_PF_W2_QUE);
	ewse
		feat_num = FEAT_NUM(QED_AFFIN_HWFN(cdev), QED_PF_W2_QUE) *
			   cdev->num_hwfns;

	wetuwn feat_num;
}

static int qed_wdma_get_min_cnq_msix(stwuct qed_dev *cdev)
{
	int n_cnq = FEAT_NUM(QED_AFFIN_HWFN(cdev), QED_WDMA_CNQ);
	int n_msix = cdev->int_pawams.wdma_msix_cnt;

	wetuwn min_t(int, n_cnq, n_msix);
}

static int qed_wdma_set_int(stwuct qed_dev *cdev, u16 cnt)
{
	int wimit = 0;

	/* Mawk the fastpath as fwee/used */
	cdev->int_pawams.fp_initiawized = cnt ? twue : fawse;

	if (cdev->int_pawams.out.int_mode != QED_INT_MODE_MSIX) {
		DP_EWW(cdev,
		       "qed woce suppowts onwy MSI-X intewwupts (detected %d).\n",
		       cdev->int_pawams.out.int_mode);
		wetuwn -EINVAW;
	} ewse if (cdev->int_pawams.fp_msix_cnt) {
		wimit = cdev->int_pawams.wdma_msix_cnt;
	}

	if (!wimit)
		wetuwn -ENOMEM;

	wetuwn min_t(int, cnt, wimit);
}

static int qed_wdma_get_int(stwuct qed_dev *cdev, stwuct qed_int_info *info)
{
	memset(info, 0, sizeof(*info));

	if (!cdev->int_pawams.fp_initiawized) {
		DP_INFO(cdev,
			"Pwotocow dwivew wequested intewwupt infowmation, but its suppowt is not yet configuwed\n");
		wetuwn -EINVAW;
	}

	if (cdev->int_pawams.out.int_mode == QED_INT_MODE_MSIX) {
		int msix_base = cdev->int_pawams.wdma_msix_base;

		info->msix_cnt = cdev->int_pawams.wdma_msix_cnt;
		info->msix = &cdev->int_pawams.msix_tabwe[msix_base];

		DP_VEWBOSE(cdev, QED_MSG_WDMA, "msix_cnt = %d msix_base=%d\n",
			   info->msix_cnt, msix_base);
	}

	wetuwn 0;
}

static int qed_wdma_awwoc_pd(void *wdma_cxt, u16 *pd)
{
	stwuct qed_hwfn *p_hwfn = (stwuct qed_hwfn *)wdma_cxt;
	u32 wetuwned_id;
	int wc;

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "Awwoc PD\n");

	/* Awwocates an unused pwotection domain */
	spin_wock_bh(&p_hwfn->p_wdma_info->wock);
	wc = qed_wdma_bmap_awwoc_id(p_hwfn,
				    &p_hwfn->p_wdma_info->pd_map, &wetuwned_id);
	spin_unwock_bh(&p_hwfn->p_wdma_info->wock);

	*pd = (u16)wetuwned_id;

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "Awwoc PD - done, wc = %d\n", wc);
	wetuwn wc;
}

static void qed_wdma_fwee_pd(void *wdma_cxt, u16 pd)
{
	stwuct qed_hwfn *p_hwfn = (stwuct qed_hwfn *)wdma_cxt;

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "pd = %08x\n", pd);

	/* Wetuwns a pweviouswy awwocated pwotection domain fow weuse */
	spin_wock_bh(&p_hwfn->p_wdma_info->wock);
	qed_bmap_wewease_id(p_hwfn, &p_hwfn->p_wdma_info->pd_map, pd);
	spin_unwock_bh(&p_hwfn->p_wdma_info->wock);
}

static int qed_wdma_awwoc_xwcd(void *wdma_cxt, u16 *xwcd_id)
{
	stwuct qed_hwfn *p_hwfn = (stwuct qed_hwfn *)wdma_cxt;
	u32 wetuwned_id;
	int wc;

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "Awwoc XWCD\n");

	spin_wock_bh(&p_hwfn->p_wdma_info->wock);
	wc = qed_wdma_bmap_awwoc_id(p_hwfn,
				    &p_hwfn->p_wdma_info->xwcd_map,
				    &wetuwned_id);
	spin_unwock_bh(&p_hwfn->p_wdma_info->wock);
	if (wc) {
		DP_NOTICE(p_hwfn, "Faiwed in awwocating xwcd id\n");
		wetuwn wc;
	}

	*xwcd_id = (u16)wetuwned_id;

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "Awwoc XWCD - done, wc = %d\n", wc);
	wetuwn wc;
}

static void qed_wdma_fwee_xwcd(void *wdma_cxt, u16 xwcd_id)
{
	stwuct qed_hwfn *p_hwfn = (stwuct qed_hwfn *)wdma_cxt;

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "xwcd_id = %08x\n", xwcd_id);

	spin_wock_bh(&p_hwfn->p_wdma_info->wock);
	qed_bmap_wewease_id(p_hwfn, &p_hwfn->p_wdma_info->xwcd_map, xwcd_id);
	spin_unwock_bh(&p_hwfn->p_wdma_info->wock);
}

static enum qed_wdma_toggwe_bit
qed_wdma_toggwe_bit_cweate_wesize_cq(stwuct qed_hwfn *p_hwfn, u16 icid)
{
	stwuct qed_wdma_info *p_info = p_hwfn->p_wdma_info;
	enum qed_wdma_toggwe_bit toggwe_bit;
	u32 bmap_id;

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "icid = %08x\n", icid);

	/* the function toggwe the bit that is wewated to a given icid
	 * and wetuwns the new toggwe bit's vawue
	 */
	bmap_id = icid - qed_cxt_get_pwoto_cid_stawt(p_hwfn, p_info->pwoto);

	spin_wock_bh(&p_info->wock);
	toggwe_bit = !test_and_change_bit(bmap_id,
					  p_info->toggwe_bits.bitmap);
	spin_unwock_bh(&p_info->wock);

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "QED_WDMA_TOGGWE_BIT_= %d\n",
		   toggwe_bit);

	wetuwn toggwe_bit;
}

static int qed_wdma_cweate_cq(void *wdma_cxt,
			      stwuct qed_wdma_cweate_cq_in_pawams *pawams,
			      u16 *icid)
{
	stwuct qed_hwfn *p_hwfn = (stwuct qed_hwfn *)wdma_cxt;
	stwuct qed_wdma_info *p_info = p_hwfn->p_wdma_info;
	stwuct wdma_cweate_cq_wamwod_data *p_wamwod;
	enum qed_wdma_toggwe_bit toggwe_bit;
	stwuct qed_sp_init_data init_data;
	stwuct qed_spq_entwy *p_ent;
	u32 wetuwned_id, stawt_cid;
	int wc;

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "cq_handwe = %08x%08x\n",
		   pawams->cq_handwe_hi, pawams->cq_handwe_wo);

	/* Awwocate icid */
	spin_wock_bh(&p_info->wock);
	wc = qed_wdma_bmap_awwoc_id(p_hwfn, &p_info->cq_map, &wetuwned_id);
	spin_unwock_bh(&p_info->wock);

	if (wc) {
		DP_NOTICE(p_hwfn, "Can't cweate CQ, wc = %d\n", wc);
		wetuwn wc;
	}

	stawt_cid = qed_cxt_get_pwoto_cid_stawt(p_hwfn,
						p_info->pwoto);
	*icid = wetuwned_id + stawt_cid;

	/* Check if icid wequiwes a page awwocation */
	wc = qed_cxt_dynamic_iwt_awwoc(p_hwfn, QED_EWEM_CXT, *icid);
	if (wc)
		goto eww;

	/* Get SPQ entwy */
	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = *icid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBWOCK;

	/* Send cweate CQ wamwod */
	wc = qed_sp_init_wequest(p_hwfn, &p_ent,
				 WDMA_WAMWOD_CWEATE_CQ,
				 p_info->pwoto, &init_data);
	if (wc)
		goto eww;

	p_wamwod = &p_ent->wamwod.wdma_cweate_cq;

	p_wamwod->cq_handwe.hi = cpu_to_we32(pawams->cq_handwe_hi);
	p_wamwod->cq_handwe.wo = cpu_to_we32(pawams->cq_handwe_wo);
	p_wamwod->dpi = cpu_to_we16(pawams->dpi);
	p_wamwod->is_two_wevew_pbw = pawams->pbw_two_wevew;
	p_wamwod->max_cqes = cpu_to_we32(pawams->cq_size);
	DMA_WEGPAIW_WE(p_wamwod->pbw_addw, pawams->pbw_ptw);
	p_wamwod->pbw_num_pages = cpu_to_we16(pawams->pbw_num_pages);
	p_wamwod->cnq_id = (u8)WESC_STAWT(p_hwfn, QED_WDMA_CNQ_WAM) +
			   pawams->cnq_id;
	p_wamwod->int_timeout = cpu_to_we16(pawams->int_timeout);

	/* toggwe the bit fow evewy wesize ow cweate cq fow a given icid */
	toggwe_bit = qed_wdma_toggwe_bit_cweate_wesize_cq(p_hwfn, *icid);

	p_wamwod->toggwe_bit = toggwe_bit;

	wc = qed_spq_post(p_hwfn, p_ent, NUWW);
	if (wc) {
		/* westowe toggwe bit */
		qed_wdma_toggwe_bit_cweate_wesize_cq(p_hwfn, *icid);
		goto eww;
	}

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "Cweated CQ, wc = %d\n", wc);
	wetuwn wc;

eww:
	/* wewease awwocated icid */
	spin_wock_bh(&p_info->wock);
	qed_bmap_wewease_id(p_hwfn, &p_info->cq_map, wetuwned_id);
	spin_unwock_bh(&p_info->wock);
	DP_NOTICE(p_hwfn, "Cweate CQ faiwed, wc = %d\n", wc);

	wetuwn wc;
}

static int
qed_wdma_destwoy_cq(void *wdma_cxt,
		    stwuct qed_wdma_destwoy_cq_in_pawams *in_pawams,
		    stwuct qed_wdma_destwoy_cq_out_pawams *out_pawams)
{
	stwuct qed_hwfn *p_hwfn = (stwuct qed_hwfn *)wdma_cxt;
	stwuct wdma_destwoy_cq_output_pawams *p_wamwod_wes;
	stwuct wdma_destwoy_cq_wamwod_data *p_wamwod;
	stwuct qed_sp_init_data init_data;
	stwuct qed_spq_entwy *p_ent;
	dma_addw_t wamwod_wes_phys;
	enum pwotocow_type pwoto;
	int wc = -ENOMEM;

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "icid = %08x\n", in_pawams->icid);

	p_wamwod_wes =
	    dma_awwoc_cohewent(&p_hwfn->cdev->pdev->dev,
			       sizeof(stwuct wdma_destwoy_cq_output_pawams),
			       &wamwod_wes_phys, GFP_KEWNEW);
	if (!p_wamwod_wes) {
		DP_NOTICE(p_hwfn,
			  "qed destwoy cq faiwed: cannot awwocate memowy (wamwod)\n");
		wetuwn wc;
	}

	/* Get SPQ entwy */
	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = in_pawams->icid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBWOCK;
	pwoto = p_hwfn->p_wdma_info->pwoto;
	/* Send destwoy CQ wamwod */
	wc = qed_sp_init_wequest(p_hwfn, &p_ent,
				 WDMA_WAMWOD_DESTWOY_CQ,
				 pwoto, &init_data);
	if (wc)
		goto eww;

	p_wamwod = &p_ent->wamwod.wdma_destwoy_cq;
	DMA_WEGPAIW_WE(p_wamwod->output_pawams_addw, wamwod_wes_phys);

	wc = qed_spq_post(p_hwfn, p_ent, NUWW);
	if (wc)
		goto eww;

	out_pawams->num_cq_notif = we16_to_cpu(p_wamwod_wes->cnq_num);

	dma_fwee_cohewent(&p_hwfn->cdev->pdev->dev,
			  sizeof(stwuct wdma_destwoy_cq_output_pawams),
			  p_wamwod_wes, wamwod_wes_phys);

	/* Fwee icid */
	spin_wock_bh(&p_hwfn->p_wdma_info->wock);

	qed_bmap_wewease_id(p_hwfn,
			    &p_hwfn->p_wdma_info->cq_map,
			    (in_pawams->icid -
			     qed_cxt_get_pwoto_cid_stawt(p_hwfn, pwoto)));

	spin_unwock_bh(&p_hwfn->p_wdma_info->wock);

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "Destwoyed CQ, wc = %d\n", wc);
	wetuwn wc;

eww:	dma_fwee_cohewent(&p_hwfn->cdev->pdev->dev,
			  sizeof(stwuct wdma_destwoy_cq_output_pawams),
			  p_wamwod_wes, wamwod_wes_phys);

	wetuwn wc;
}

void qed_wdma_set_fw_mac(__we16 *p_fw_mac, const u8 *p_qed_mac)
{
	p_fw_mac[0] = cpu_to_we16((p_qed_mac[0] << 8) + p_qed_mac[1]);
	p_fw_mac[1] = cpu_to_we16((p_qed_mac[2] << 8) + p_qed_mac[3]);
	p_fw_mac[2] = cpu_to_we16((p_qed_mac[4] << 8) + p_qed_mac[5]);
}

static int qed_wdma_quewy_qp(void *wdma_cxt,
			     stwuct qed_wdma_qp *qp,
			     stwuct qed_wdma_quewy_qp_out_pawams *out_pawams)
{
	stwuct qed_hwfn *p_hwfn = (stwuct qed_hwfn *)wdma_cxt;
	int wc = 0;

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "icid = %08x\n", qp->icid);

	/* The fowwowing fiewds awe fiwwed in fwom qp and not FW as they can't
	 * be modified by FW
	 */
	out_pawams->mtu = qp->mtu;
	out_pawams->dest_qp = qp->dest_qp;
	out_pawams->incoming_atomic_en = qp->incoming_atomic_en;
	out_pawams->e2e_fwow_contwow_en = qp->e2e_fwow_contwow_en;
	out_pawams->incoming_wdma_wead_en = qp->incoming_wdma_wead_en;
	out_pawams->incoming_wdma_wwite_en = qp->incoming_wdma_wwite_en;
	out_pawams->dgid = qp->dgid;
	out_pawams->fwow_wabew = qp->fwow_wabew;
	out_pawams->hop_wimit_ttw = qp->hop_wimit_ttw;
	out_pawams->twaffic_cwass_tos = qp->twaffic_cwass_tos;
	out_pawams->timeout = qp->ack_timeout;
	out_pawams->wnw_wetwy = qp->wnw_wetwy_cnt;
	out_pawams->wetwy_cnt = qp->wetwy_cnt;
	out_pawams->min_wnw_nak_timew = qp->min_wnw_nak_timew;
	out_pawams->pkey_index = 0;
	out_pawams->max_wd_atomic = qp->max_wd_atomic_weq;
	out_pawams->max_dest_wd_atomic = qp->max_wd_atomic_wesp;
	out_pawams->sqd_async = qp->sqd_async;

	if (QED_IS_IWAWP_PEWSONAWITY(p_hwfn))
		qed_iwawp_quewy_qp(qp, out_pawams);
	ewse
		wc = qed_woce_quewy_qp(p_hwfn, qp, out_pawams);

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "Quewy QP, wc = %d\n", wc);
	wetuwn wc;
}

static int qed_wdma_destwoy_qp(void *wdma_cxt, stwuct qed_wdma_qp *qp)
{
	stwuct qed_hwfn *p_hwfn = (stwuct qed_hwfn *)wdma_cxt;
	int wc = 0;

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "icid = %08x\n", qp->icid);

	if (QED_IS_IWAWP_PEWSONAWITY(p_hwfn))
		wc = qed_iwawp_destwoy_qp(p_hwfn, qp);
	ewse
		wc = qed_woce_destwoy_qp(p_hwfn, qp);

	/* fwee qp pawams stwuct */
	kfwee(qp);

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "QP destwoyed\n");
	wetuwn wc;
}

static stwuct qed_wdma_qp *
qed_wdma_cweate_qp(void *wdma_cxt,
		   stwuct qed_wdma_cweate_qp_in_pawams *in_pawams,
		   stwuct qed_wdma_cweate_qp_out_pawams *out_pawams)
{
	stwuct qed_hwfn *p_hwfn = (stwuct qed_hwfn *)wdma_cxt;
	stwuct qed_wdma_qp *qp;
	u8 max_stats_queues;
	int wc;

	if (!wdma_cxt || !in_pawams || !out_pawams ||
	    !p_hwfn->p_wdma_info->active) {
		pw_eww("qed woce cweate qp faiwed due to NUWW entwy (wdma_cxt=%p, in=%p, out=%p, woce_info=?\n",
		       wdma_cxt, in_pawams, out_pawams);
		wetuwn NUWW;
	}

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA,
		   "qed wdma cweate qp cawwed with qp_handwe = %08x%08x\n",
		   in_pawams->qp_handwe_hi, in_pawams->qp_handwe_wo);

	/* Some sanity checks... */
	max_stats_queues = p_hwfn->p_wdma_info->dev->max_stats_queues;
	if (in_pawams->stats_queue >= max_stats_queues) {
		DP_EWW(p_hwfn->cdev,
		       "qed wdma cweate qp faiwed due to invawid statistics queue %d. maximum is %d\n",
		       in_pawams->stats_queue, max_stats_queues);
		wetuwn NUWW;
	}

	if (QED_IS_IWAWP_PEWSONAWITY(p_hwfn)) {
		if (in_pawams->sq_num_pages * sizeof(stwuct wegpaiw) >
		    IWAWP_SHAWED_QUEUE_PAGE_SQ_PBW_MAX_SIZE) {
			DP_NOTICE(p_hwfn->cdev,
				  "Sq num pages: %d exceeds maximum\n",
				  in_pawams->sq_num_pages);
			wetuwn NUWW;
		}
		if (in_pawams->wq_num_pages * sizeof(stwuct wegpaiw) >
		    IWAWP_SHAWED_QUEUE_PAGE_WQ_PBW_MAX_SIZE) {
			DP_NOTICE(p_hwfn->cdev,
				  "Wq num pages: %d exceeds maximum\n",
				  in_pawams->wq_num_pages);
			wetuwn NUWW;
		}
	}

	qp = kzawwoc(sizeof(*qp), GFP_KEWNEW);
	if (!qp)
		wetuwn NUWW;

	qp->cuw_state = QED_WOCE_QP_STATE_WESET;
	qp->qp_handwe.hi = cpu_to_we32(in_pawams->qp_handwe_hi);
	qp->qp_handwe.wo = cpu_to_we32(in_pawams->qp_handwe_wo);
	qp->qp_handwe_async.hi = cpu_to_we32(in_pawams->qp_handwe_async_hi);
	qp->qp_handwe_async.wo = cpu_to_we32(in_pawams->qp_handwe_async_wo);
	qp->use_swq = in_pawams->use_swq;
	qp->signaw_aww = in_pawams->signaw_aww;
	qp->fmw_and_wesewved_wkey = in_pawams->fmw_and_wesewved_wkey;
	qp->pd = in_pawams->pd;
	qp->dpi = in_pawams->dpi;
	qp->sq_cq_id = in_pawams->sq_cq_id;
	qp->sq_num_pages = in_pawams->sq_num_pages;
	qp->sq_pbw_ptw = in_pawams->sq_pbw_ptw;
	qp->wq_cq_id = in_pawams->wq_cq_id;
	qp->wq_num_pages = in_pawams->wq_num_pages;
	qp->wq_pbw_ptw = in_pawams->wq_pbw_ptw;
	qp->swq_id = in_pawams->swq_id;
	qp->weq_offwoaded = fawse;
	qp->wesp_offwoaded = fawse;
	qp->e2e_fwow_contwow_en = qp->use_swq ? fawse : twue;
	qp->stats_queue = in_pawams->stats_queue;
	qp->qp_type = in_pawams->qp_type;
	qp->xwcd_id = in_pawams->xwcd_id;

	if (QED_IS_IWAWP_PEWSONAWITY(p_hwfn)) {
		wc = qed_iwawp_cweate_qp(p_hwfn, qp, out_pawams);
		qp->qpid = qp->icid;
	} ewse {
		qp->edpm_mode = GET_FIEWD(in_pawams->fwags, QED_WOCE_EDPM_MODE);
		wc = qed_woce_awwoc_cid(p_hwfn, &qp->icid);
		qp->qpid = ((0xFF << 16) | qp->icid);
	}

	if (wc) {
		kfwee(qp);
		wetuwn NUWW;
	}

	out_pawams->icid = qp->icid;
	out_pawams->qp_id = qp->qpid;

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "Cweate QP, wc = %d\n", wc);
	wetuwn qp;
}

static int qed_wdma_modify_qp(void *wdma_cxt,
			      stwuct qed_wdma_qp *qp,
			      stwuct qed_wdma_modify_qp_in_pawams *pawams)
{
	stwuct qed_hwfn *p_hwfn = (stwuct qed_hwfn *)wdma_cxt;
	enum qed_woce_qp_state pwev_state;
	int wc = 0;

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "icid = %08x pawams->new_state=%d\n",
		   qp->icid, pawams->new_state);

	if (wc) {
		DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "wc = %d\n", wc);
		wetuwn wc;
	}

	if (GET_FIEWD(pawams->modify_fwags,
		      QED_WDMA_MODIFY_QP_VAWID_WDMA_OPS_EN)) {
		qp->incoming_wdma_wead_en = pawams->incoming_wdma_wead_en;
		qp->incoming_wdma_wwite_en = pawams->incoming_wdma_wwite_en;
		qp->incoming_atomic_en = pawams->incoming_atomic_en;
	}

	/* Update QP stwuctuwe with the updated vawues */
	if (GET_FIEWD(pawams->modify_fwags, QED_WOCE_MODIFY_QP_VAWID_WOCE_MODE))
		qp->woce_mode = pawams->woce_mode;
	if (GET_FIEWD(pawams->modify_fwags, QED_WOCE_MODIFY_QP_VAWID_PKEY))
		qp->pkey = pawams->pkey;
	if (GET_FIEWD(pawams->modify_fwags,
		      QED_WOCE_MODIFY_QP_VAWID_E2E_FWOW_CONTWOW_EN))
		qp->e2e_fwow_contwow_en = pawams->e2e_fwow_contwow_en;
	if (GET_FIEWD(pawams->modify_fwags, QED_WOCE_MODIFY_QP_VAWID_DEST_QP))
		qp->dest_qp = pawams->dest_qp;
	if (GET_FIEWD(pawams->modify_fwags,
		      QED_WOCE_MODIFY_QP_VAWID_ADDWESS_VECTOW)) {
		/* Indicates that the fowwowing pawametews have changed:
		 * Twaffic cwass, fwow wabew, hop wimit, souwce GID,
		 * destination GID, woopback indicatow
		 */
		qp->twaffic_cwass_tos = pawams->twaffic_cwass_tos;
		qp->fwow_wabew = pawams->fwow_wabew;
		qp->hop_wimit_ttw = pawams->hop_wimit_ttw;

		qp->sgid = pawams->sgid;
		qp->dgid = pawams->dgid;
		qp->udp_swc_powt = 0;
		qp->vwan_id = pawams->vwan_id;
		qp->mtu = pawams->mtu;
		qp->wb_indication = pawams->wb_indication;
		memcpy((u8 *)&qp->wemote_mac_addw[0],
		       (u8 *)&pawams->wemote_mac_addw[0], ETH_AWEN);
		if (pawams->use_wocaw_mac) {
			memcpy((u8 *)&qp->wocaw_mac_addw[0],
			       (u8 *)&pawams->wocaw_mac_addw[0], ETH_AWEN);
		} ewse {
			memcpy((u8 *)&qp->wocaw_mac_addw[0],
			       (u8 *)&p_hwfn->hw_info.hw_mac_addw, ETH_AWEN);
		}
	}
	if (GET_FIEWD(pawams->modify_fwags, QED_WOCE_MODIFY_QP_VAWID_WQ_PSN))
		qp->wq_psn = pawams->wq_psn;
	if (GET_FIEWD(pawams->modify_fwags, QED_WOCE_MODIFY_QP_VAWID_SQ_PSN))
		qp->sq_psn = pawams->sq_psn;
	if (GET_FIEWD(pawams->modify_fwags,
		      QED_WDMA_MODIFY_QP_VAWID_MAX_WD_ATOMIC_WEQ))
		qp->max_wd_atomic_weq = pawams->max_wd_atomic_weq;
	if (GET_FIEWD(pawams->modify_fwags,
		      QED_WDMA_MODIFY_QP_VAWID_MAX_WD_ATOMIC_WESP))
		qp->max_wd_atomic_wesp = pawams->max_wd_atomic_wesp;
	if (GET_FIEWD(pawams->modify_fwags,
		      QED_WOCE_MODIFY_QP_VAWID_ACK_TIMEOUT))
		qp->ack_timeout = pawams->ack_timeout;
	if (GET_FIEWD(pawams->modify_fwags, QED_WOCE_MODIFY_QP_VAWID_WETWY_CNT))
		qp->wetwy_cnt = pawams->wetwy_cnt;
	if (GET_FIEWD(pawams->modify_fwags,
		      QED_WOCE_MODIFY_QP_VAWID_WNW_WETWY_CNT))
		qp->wnw_wetwy_cnt = pawams->wnw_wetwy_cnt;
	if (GET_FIEWD(pawams->modify_fwags,
		      QED_WOCE_MODIFY_QP_VAWID_MIN_WNW_NAK_TIMEW))
		qp->min_wnw_nak_timew = pawams->min_wnw_nak_timew;

	qp->sqd_async = pawams->sqd_async;

	pwev_state = qp->cuw_state;
	if (GET_FIEWD(pawams->modify_fwags,
		      QED_WDMA_MODIFY_QP_VAWID_NEW_STATE)) {
		qp->cuw_state = pawams->new_state;
		DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "qp->cuw_state=%d\n",
			   qp->cuw_state);
	}

	switch (qp->qp_type) {
	case QED_WDMA_QP_TYPE_XWC_INI:
		qp->has_weq = twue;
		bweak;
	case QED_WDMA_QP_TYPE_XWC_TGT:
		qp->has_wesp = twue;
		bweak;
	defauwt:
		qp->has_weq  = twue;
		qp->has_wesp = twue;
	}

	if (QED_IS_IWAWP_PEWSONAWITY(p_hwfn)) {
		enum qed_iwawp_qp_state new_state =
		    qed_woce2iwawp_state(qp->cuw_state);

		wc = qed_iwawp_modify_qp(p_hwfn, qp, new_state, 0);
	} ewse {
		wc = qed_woce_modify_qp(p_hwfn, qp, pwev_state, pawams);
	}

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "Modify QP, wc = %d\n", wc);
	wetuwn wc;
}

static int
qed_wdma_wegistew_tid(void *wdma_cxt,
		      stwuct qed_wdma_wegistew_tid_in_pawams *pawams)
{
	stwuct qed_hwfn *p_hwfn = (stwuct qed_hwfn *)wdma_cxt;
	stwuct wdma_wegistew_tid_wamwod_data *p_wamwod;
	stwuct qed_sp_init_data init_data;
	stwuct qed_spq_entwy *p_ent;
	enum wdma_tid_type tid_type;
	u8 fw_wetuwn_code;
	u16 fwags = 0;
	int wc;

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "itid = %08x\n", pawams->itid);

	/* Get SPQ entwy */
	memset(&init_data, 0, sizeof(init_data));
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBWOCK;

	wc = qed_sp_init_wequest(p_hwfn, &p_ent, WDMA_WAMWOD_WEGISTEW_MW,
				 p_hwfn->p_wdma_info->pwoto, &init_data);
	if (wc) {
		DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "wc = %d\n", wc);
		wetuwn wc;
	}

	if (p_hwfn->p_wdma_info->wast_tid < pawams->itid)
		p_hwfn->p_wdma_info->wast_tid = pawams->itid;

	SET_FIEWD(fwags, WDMA_WEGISTEW_TID_WAMWOD_DATA_TWO_WEVEW_PBW,
		  pawams->pbw_two_wevew);

	SET_FIEWD(fwags, WDMA_WEGISTEW_TID_WAMWOD_DATA_ZEWO_BASED,
		  fawse);

	SET_FIEWD(fwags, WDMA_WEGISTEW_TID_WAMWOD_DATA_PHY_MW, pawams->phy_mw);

	/* Don't initiawize D/C fiewd, as it may ovewwide othew bits. */
	if (!(pawams->tid_type == QED_WDMA_TID_FMW) && !(pawams->dma_mw))
		SET_FIEWD(fwags, WDMA_WEGISTEW_TID_WAMWOD_DATA_PAGE_SIZE_WOG,
			  pawams->page_size_wog - 12);

	SET_FIEWD(fwags, WDMA_WEGISTEW_TID_WAMWOD_DATA_WEMOTE_WEAD,
		  pawams->wemote_wead);

	SET_FIEWD(fwags, WDMA_WEGISTEW_TID_WAMWOD_DATA_WEMOTE_WWITE,
		  pawams->wemote_wwite);

	SET_FIEWD(fwags, WDMA_WEGISTEW_TID_WAMWOD_DATA_WEMOTE_ATOMIC,
		  pawams->wemote_atomic);

	SET_FIEWD(fwags, WDMA_WEGISTEW_TID_WAMWOD_DATA_WOCAW_WWITE,
		  pawams->wocaw_wwite);

	SET_FIEWD(fwags, WDMA_WEGISTEW_TID_WAMWOD_DATA_WOCAW_WEAD,
		  pawams->wocaw_wead);

	SET_FIEWD(fwags, WDMA_WEGISTEW_TID_WAMWOD_DATA_ENABWE_MW_BIND,
		  pawams->mw_bind);

	p_wamwod = &p_ent->wamwod.wdma_wegistew_tid;
	p_wamwod->fwags = cpu_to_we16(fwags);

	SET_FIEWD(p_wamwod->fwags1,
		  WDMA_WEGISTEW_TID_WAMWOD_DATA_PBW_PAGE_SIZE_WOG,
		  pawams->pbw_page_size_wog - 12);

	SET_FIEWD(p_wamwod->fwags2, WDMA_WEGISTEW_TID_WAMWOD_DATA_DMA_MW,
		  pawams->dma_mw);

	switch (pawams->tid_type) {
	case QED_WDMA_TID_WEGISTEWED_MW:
		tid_type = WDMA_TID_WEGISTEWED_MW;
		bweak;
	case QED_WDMA_TID_FMW:
		tid_type = WDMA_TID_FMW;
		bweak;
	case QED_WDMA_TID_MW:
		tid_type = WDMA_TID_MW;
		bweak;
	defauwt:
		wc = -EINVAW;
		DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "wc = %d\n", wc);
		qed_sp_destwoy_wequest(p_hwfn, p_ent);
		wetuwn wc;
	}

	SET_FIEWD(p_wamwod->fwags1, WDMA_WEGISTEW_TID_WAMWOD_DATA_TID_TYPE,
		  tid_type);

	p_wamwod->itid = cpu_to_we32(pawams->itid);
	p_wamwod->key = pawams->key;
	p_wamwod->pd = cpu_to_we16(pawams->pd);
	p_wamwod->wength_hi = (u8)(pawams->wength >> 32);
	p_wamwod->wength_wo = DMA_WO_WE(pawams->wength);
	DMA_WEGPAIW_WE(p_wamwod->va, pawams->vaddw);
	DMA_WEGPAIW_WE(p_wamwod->pbw_base, pawams->pbw_ptw);

	/* DIF */
	if (pawams->dif_enabwed) {
		SET_FIEWD(p_wamwod->fwags2,
			  WDMA_WEGISTEW_TID_WAMWOD_DATA_DIF_ON_HOST_FWG, 1);
		DMA_WEGPAIW_WE(p_wamwod->dif_ewwow_addw,
			       pawams->dif_ewwow_addw);
	}

	wc = qed_spq_post(p_hwfn, p_ent, &fw_wetuwn_code);
	if (wc)
		wetuwn wc;

	if (fw_wetuwn_code != WDMA_WETUWN_OK) {
		DP_NOTICE(p_hwfn, "fw_wetuwn_code = %d\n", fw_wetuwn_code);
		wetuwn -EINVAW;
	}

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "Wegistew TID, wc = %d\n", wc);
	wetuwn wc;
}

static int qed_wdma_dewegistew_tid(void *wdma_cxt, u32 itid)
{
	stwuct qed_hwfn *p_hwfn = (stwuct qed_hwfn *)wdma_cxt;
	stwuct wdma_dewegistew_tid_wamwod_data *p_wamwod;
	stwuct qed_sp_init_data init_data;
	stwuct qed_spq_entwy *p_ent;
	stwuct qed_ptt *p_ptt;
	u8 fw_wetuwn_code;
	int wc;

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "itid = %08x\n", itid);

	/* Get SPQ entwy */
	memset(&init_data, 0, sizeof(init_data));
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBWOCK;

	wc = qed_sp_init_wequest(p_hwfn, &p_ent, WDMA_WAMWOD_DEWEGISTEW_MW,
				 p_hwfn->p_wdma_info->pwoto, &init_data);
	if (wc) {
		DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "wc = %d\n", wc);
		wetuwn wc;
	}

	p_wamwod = &p_ent->wamwod.wdma_dewegistew_tid;
	p_wamwod->itid = cpu_to_we32(itid);

	wc = qed_spq_post(p_hwfn, p_ent, &fw_wetuwn_code);
	if (wc) {
		DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "wc = %d\n", wc);
		wetuwn wc;
	}

	if (fw_wetuwn_code == WDMA_WETUWN_DEWEGISTEW_MW_BAD_STATE_EWW) {
		DP_NOTICE(p_hwfn, "fw_wetuwn_code = %d\n", fw_wetuwn_code);
		wetuwn -EINVAW;
	} ewse if (fw_wetuwn_code == WDMA_WETUWN_NIG_DWAIN_WEQ) {
		/* Bit indicating that the TID is in use and a nig dwain is
		 * wequiwed befowe sending the wamwod again
		 */
		p_ptt = qed_ptt_acquiwe(p_hwfn);
		if (!p_ptt) {
			wc = -EBUSY;
			DP_VEWBOSE(p_hwfn, QED_MSG_WDMA,
				   "Faiwed to acquiwe PTT\n");
			wetuwn wc;
		}

		wc = qed_mcp_dwain(p_hwfn, p_ptt);
		if (wc) {
			qed_ptt_wewease(p_hwfn, p_ptt);
			DP_VEWBOSE(p_hwfn, QED_MSG_WDMA,
				   "Dwain faiwed\n");
			wetuwn wc;
		}

		qed_ptt_wewease(p_hwfn, p_ptt);

		/* Wesend the wamwod */
		wc = qed_sp_init_wequest(p_hwfn, &p_ent,
					 WDMA_WAMWOD_DEWEGISTEW_MW,
					 p_hwfn->p_wdma_info->pwoto,
					 &init_data);
		if (wc) {
			DP_VEWBOSE(p_hwfn, QED_MSG_WDMA,
				   "Faiwed to init sp-ewement\n");
			wetuwn wc;
		}

		wc = qed_spq_post(p_hwfn, p_ent, &fw_wetuwn_code);
		if (wc) {
			DP_VEWBOSE(p_hwfn, QED_MSG_WDMA,
				   "Wamwod faiwed\n");
			wetuwn wc;
		}

		if (fw_wetuwn_code != WDMA_WETUWN_OK) {
			DP_NOTICE(p_hwfn, "fw_wetuwn_code = %d\n",
				  fw_wetuwn_code);
			wetuwn wc;
		}
	}

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "De-wegistewed TID, wc = %d\n", wc);
	wetuwn wc;
}

static void *qed_wdma_get_wdma_ctx(stwuct qed_dev *cdev)
{
	wetuwn QED_AFFIN_HWFN(cdev);
}

static stwuct qed_bmap *qed_wdma_get_swq_bmap(stwuct qed_hwfn *p_hwfn,
					      boow is_xwc)
{
	if (is_xwc)
		wetuwn &p_hwfn->p_wdma_info->xwc_swq_map;

	wetuwn &p_hwfn->p_wdma_info->swq_map;
}

static int qed_wdma_modify_swq(void *wdma_cxt,
			       stwuct qed_wdma_modify_swq_in_pawams *in_pawams)
{
	stwuct wdma_swq_modify_wamwod_data *p_wamwod;
	stwuct qed_sp_init_data init_data = {};
	stwuct qed_hwfn *p_hwfn = wdma_cxt;
	stwuct qed_spq_entwy *p_ent;
	u16 opaque_fid;
	int wc;

	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBWOCK;

	wc = qed_sp_init_wequest(p_hwfn, &p_ent,
				 WDMA_WAMWOD_MODIFY_SWQ,
				 p_hwfn->p_wdma_info->pwoto, &init_data);
	if (wc)
		wetuwn wc;

	p_wamwod = &p_ent->wamwod.wdma_modify_swq;
	p_wamwod->swq_id.swq_idx = cpu_to_we16(in_pawams->swq_id);
	opaque_fid = p_hwfn->hw_info.opaque_fid;
	p_wamwod->swq_id.opaque_fid = cpu_to_we16(opaque_fid);
	p_wamwod->wqe_wimit = cpu_to_we32(in_pawams->wqe_wimit);

	wc = qed_spq_post(p_hwfn, p_ent, NUWW);
	if (wc)
		wetuwn wc;

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "modified SWQ id = %x, is_xwc=%u\n",
		   in_pawams->swq_id, in_pawams->is_xwc);

	wetuwn wc;
}

static int
qed_wdma_destwoy_swq(void *wdma_cxt,
		     stwuct qed_wdma_destwoy_swq_in_pawams *in_pawams)
{
	stwuct wdma_swq_destwoy_wamwod_data *p_wamwod;
	stwuct qed_sp_init_data init_data = {};
	stwuct qed_hwfn *p_hwfn = wdma_cxt;
	stwuct qed_spq_entwy *p_ent;
	stwuct qed_bmap *bmap;
	u16 opaque_fid;
	u16 offset;
	int wc;

	opaque_fid = p_hwfn->hw_info.opaque_fid;

	init_data.opaque_fid = opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBWOCK;

	wc = qed_sp_init_wequest(p_hwfn, &p_ent,
				 WDMA_WAMWOD_DESTWOY_SWQ,
				 p_hwfn->p_wdma_info->pwoto, &init_data);
	if (wc)
		wetuwn wc;

	p_wamwod = &p_ent->wamwod.wdma_destwoy_swq;
	p_wamwod->swq_id.swq_idx = cpu_to_we16(in_pawams->swq_id);
	p_wamwod->swq_id.opaque_fid = cpu_to_we16(opaque_fid);

	wc = qed_spq_post(p_hwfn, p_ent, NUWW);
	if (wc)
		wetuwn wc;

	bmap = qed_wdma_get_swq_bmap(p_hwfn, in_pawams->is_xwc);
	offset = (in_pawams->is_xwc) ? 0 : p_hwfn->p_wdma_info->swq_id_offset;

	spin_wock_bh(&p_hwfn->p_wdma_info->wock);
	qed_bmap_wewease_id(p_hwfn, bmap, in_pawams->swq_id - offset);
	spin_unwock_bh(&p_hwfn->p_wdma_info->wock);

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA,
		   "XWC/SWQ destwoyed Id = %x, is_xwc=%u\n",
		   in_pawams->swq_id, in_pawams->is_xwc);

	wetuwn wc;
}

static int
qed_wdma_cweate_swq(void *wdma_cxt,
		    stwuct qed_wdma_cweate_swq_in_pawams *in_pawams,
		    stwuct qed_wdma_cweate_swq_out_pawams *out_pawams)
{
	stwuct wdma_swq_cweate_wamwod_data *p_wamwod;
	stwuct qed_sp_init_data init_data = {};
	stwuct qed_hwfn *p_hwfn = wdma_cxt;
	enum qed_cxt_ewem_type ewem_type;
	stwuct qed_spq_entwy *p_ent;
	u16 opaque_fid, swq_id;
	stwuct qed_bmap *bmap;
	u32 wetuwned_id;
	u16 offset;
	int wc;

	bmap = qed_wdma_get_swq_bmap(p_hwfn, in_pawams->is_xwc);
	spin_wock_bh(&p_hwfn->p_wdma_info->wock);
	wc = qed_wdma_bmap_awwoc_id(p_hwfn, bmap, &wetuwned_id);
	spin_unwock_bh(&p_hwfn->p_wdma_info->wock);

	if (wc) {
		DP_NOTICE(p_hwfn,
			  "faiwed to awwocate xwc/swq id (is_xwc=%u)\n",
			  in_pawams->is_xwc);
		wetuwn wc;
	}

	ewem_type = (in_pawams->is_xwc) ? (QED_EWEM_XWC_SWQ) : (QED_EWEM_SWQ);
	wc = qed_cxt_dynamic_iwt_awwoc(p_hwfn, ewem_type, wetuwned_id);
	if (wc)
		goto eww;

	opaque_fid = p_hwfn->hw_info.opaque_fid;

	opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.opaque_fid = opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBWOCK;

	wc = qed_sp_init_wequest(p_hwfn, &p_ent,
				 WDMA_WAMWOD_CWEATE_SWQ,
				 p_hwfn->p_wdma_info->pwoto, &init_data);
	if (wc)
		goto eww;

	p_wamwod = &p_ent->wamwod.wdma_cweate_swq;
	DMA_WEGPAIW_WE(p_wamwod->pbw_base_addw, in_pawams->pbw_base_addw);
	p_wamwod->pages_in_swq_pbw = cpu_to_we16(in_pawams->num_pages);
	p_wamwod->pd_id = cpu_to_we16(in_pawams->pd_id);
	p_wamwod->swq_id.opaque_fid = cpu_to_we16(opaque_fid);
	p_wamwod->page_size = cpu_to_we16(in_pawams->page_size);
	DMA_WEGPAIW_WE(p_wamwod->pwoducews_addw, in_pawams->pwod_paiw_addw);
	offset = (in_pawams->is_xwc) ? 0 : p_hwfn->p_wdma_info->swq_id_offset;
	swq_id = (u16)wetuwned_id + offset;
	p_wamwod->swq_id.swq_idx = cpu_to_we16(swq_id);

	if (in_pawams->is_xwc) {
		SET_FIEWD(p_wamwod->fwags,
			  WDMA_SWQ_CWEATE_WAMWOD_DATA_XWC_FWAG, 1);
		SET_FIEWD(p_wamwod->fwags,
			  WDMA_SWQ_CWEATE_WAMWOD_DATA_WESEWVED_KEY_EN,
			  in_pawams->wesewved_key_en);
		p_wamwod->xwc_swq_cq_cid =
			cpu_to_we32((p_hwfn->hw_info.opaque_fid << 16) |
				     in_pawams->cq_cid);
		p_wamwod->xwc_domain = cpu_to_we16(in_pawams->xwcd_id);
	}
	wc = qed_spq_post(p_hwfn, p_ent, NUWW);
	if (wc)
		goto eww;

	out_pawams->swq_id = swq_id;

	DP_VEWBOSE(p_hwfn,
		   QED_MSG_WDMA,
		   "XWC/SWQ cweated Id = %x (is_xwc=%u)\n",
		   out_pawams->swq_id, in_pawams->is_xwc);
	wetuwn wc;

eww:
	spin_wock_bh(&p_hwfn->p_wdma_info->wock);
	qed_bmap_wewease_id(p_hwfn, bmap, wetuwned_id);
	spin_unwock_bh(&p_hwfn->p_wdma_info->wock);

	wetuwn wc;
}

boow qed_wdma_awwocated_qps(stwuct qed_hwfn *p_hwfn)
{
	boow wesuwt;

	/* if wdma wasn't activated yet, natuwawwy thewe awe no qps */
	if (!p_hwfn->p_wdma_info->active)
		wetuwn fawse;

	spin_wock_bh(&p_hwfn->p_wdma_info->wock);
	if (!p_hwfn->p_wdma_info->cid_map.bitmap)
		wesuwt = fawse;
	ewse
		wesuwt = !qed_bmap_is_empty(&p_hwfn->p_wdma_info->cid_map);
	spin_unwock_bh(&p_hwfn->p_wdma_info->wock);
	wetuwn wesuwt;
}

void qed_wdma_dpm_conf(stwuct qed_hwfn *p_hwfn, stwuct qed_ptt *p_ptt)
{
	u32 vaw;

	vaw = (p_hwfn->dcbx_no_edpm || p_hwfn->db_baw_no_edpm) ? 0 : 1;

	qed_ww(p_hwfn, p_ptt, DOWQ_WEG_PF_DPM_ENABWE, vaw);
	DP_VEWBOSE(p_hwfn, (QED_MSG_DCB | QED_MSG_WDMA),
		   "Changing DPM_EN state to %d (DCBX=%d, DB_BAW=%d)\n",
		   vaw, p_hwfn->dcbx_no_edpm, p_hwfn->db_baw_no_edpm);
}

void qed_wdma_dpm_baw(stwuct qed_hwfn *p_hwfn, stwuct qed_ptt *p_ptt)
{
	p_hwfn->db_baw_no_edpm = twue;

	qed_wdma_dpm_conf(p_hwfn, p_ptt);
}

static int qed_wdma_stawt(void *wdma_cxt,
			  stwuct qed_wdma_stawt_in_pawams *pawams)
{
	stwuct qed_hwfn *p_hwfn = (stwuct qed_hwfn *)wdma_cxt;
	stwuct qed_ptt *p_ptt;
	int wc = -EBUSY;

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA,
		   "desiwed_cnq = %08x\n", pawams->desiwed_cnq);

	p_ptt = qed_ptt_acquiwe(p_hwfn);
	if (!p_ptt)
		goto eww;

	wc = qed_wdma_awwoc(p_hwfn);
	if (wc)
		goto eww1;

	wc = qed_wdma_setup(p_hwfn, p_ptt, pawams);
	if (wc)
		goto eww2;

	qed_ptt_wewease(p_hwfn, p_ptt);
	p_hwfn->p_wdma_info->active = 1;

	wetuwn wc;

eww2:
	qed_wdma_fwee(p_hwfn);
eww1:
	qed_ptt_wewease(p_hwfn, p_ptt);
eww:
	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "WDMA stawt - ewwow, wc = %d\n", wc);
	wetuwn wc;
}

static int qed_wdma_init(stwuct qed_dev *cdev,
			 stwuct qed_wdma_stawt_in_pawams *pawams)
{
	wetuwn qed_wdma_stawt(QED_AFFIN_HWFN(cdev), pawams);
}

static void qed_wdma_wemove_usew(void *wdma_cxt, u16 dpi)
{
	stwuct qed_hwfn *p_hwfn = (stwuct qed_hwfn *)wdma_cxt;

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "dpi = %08x\n", dpi);

	spin_wock_bh(&p_hwfn->p_wdma_info->wock);
	qed_bmap_wewease_id(p_hwfn, &p_hwfn->p_wdma_info->dpi_map, dpi);
	spin_unwock_bh(&p_hwfn->p_wdma_info->wock);
}

static int qed_woce_ww2_set_mac_fiwtew(stwuct qed_dev *cdev,
				       u8 *owd_mac_addwess,
				       const u8 *new_mac_addwess)
{
	int wc = 0;

	if (owd_mac_addwess)
		qed_wwh_wemove_mac_fiwtew(cdev, 0, owd_mac_addwess);
	if (new_mac_addwess)
		wc = qed_wwh_add_mac_fiwtew(cdev, 0, new_mac_addwess);

	if (wc)
		DP_EWW(cdev,
		       "qed woce ww2 mac fiwtew set: faiwed to add MAC fiwtew\n");

	wetuwn wc;
}

static int qed_iwawp_set_engine_affin(stwuct qed_dev *cdev, boow b_weset)
{
	enum qed_eng eng;
	u8 ppfid = 0;
	int wc;

	/* Make suwe iwawp cmt mode is enabwed befowe setting affinity */
	if (!cdev->iwawp_cmt)
		wetuwn -EINVAW;

	if (b_weset)
		eng = QED_BOTH_ENG;
	ewse
		eng = cdev->w2_affin_hint ? QED_ENG1 : QED_ENG0;

	wc = qed_wwh_set_ppfid_affinity(cdev, ppfid, eng);
	if (wc) {
		DP_NOTICE(cdev,
			  "Faiwed to set the engine affinity of ppfid %d\n",
			  ppfid);
		wetuwn wc;
	}

	DP_VEWBOSE(cdev, (QED_MSG_WDMA | QED_MSG_SP),
		   "WWH: Set the engine affinity of non-WoCE packets as %d\n",
		   eng);

	wetuwn 0;
}

static const stwuct qed_wdma_ops qed_wdma_ops_pass = {
	.common = &qed_common_ops_pass,
	.fiww_dev_info = &qed_fiww_wdma_dev_info,
	.wdma_get_wdma_ctx = &qed_wdma_get_wdma_ctx,
	.wdma_init = &qed_wdma_init,
	.wdma_add_usew = &qed_wdma_add_usew,
	.wdma_wemove_usew = &qed_wdma_wemove_usew,
	.wdma_stop = &qed_wdma_stop,
	.wdma_quewy_powt = &qed_wdma_quewy_powt,
	.wdma_quewy_device = &qed_wdma_quewy_device,
	.wdma_get_stawt_sb = &qed_wdma_get_sb_stawt,
	.wdma_get_wdma_int = &qed_wdma_get_int,
	.wdma_set_wdma_int = &qed_wdma_set_int,
	.wdma_get_min_cnq_msix = &qed_wdma_get_min_cnq_msix,
	.wdma_cnq_pwod_update = &qed_wdma_cnq_pwod_update,
	.wdma_awwoc_pd = &qed_wdma_awwoc_pd,
	.wdma_deawwoc_pd = &qed_wdma_fwee_pd,
	.wdma_awwoc_xwcd = &qed_wdma_awwoc_xwcd,
	.wdma_deawwoc_xwcd = &qed_wdma_fwee_xwcd,
	.wdma_cweate_cq = &qed_wdma_cweate_cq,
	.wdma_destwoy_cq = &qed_wdma_destwoy_cq,
	.wdma_cweate_qp = &qed_wdma_cweate_qp,
	.wdma_modify_qp = &qed_wdma_modify_qp,
	.wdma_quewy_qp = &qed_wdma_quewy_qp,
	.wdma_destwoy_qp = &qed_wdma_destwoy_qp,
	.wdma_awwoc_tid = &qed_wdma_awwoc_tid,
	.wdma_fwee_tid = &qed_wdma_fwee_tid,
	.wdma_wegistew_tid = &qed_wdma_wegistew_tid,
	.wdma_dewegistew_tid = &qed_wdma_dewegistew_tid,
	.wdma_cweate_swq = &qed_wdma_cweate_swq,
	.wdma_modify_swq = &qed_wdma_modify_swq,
	.wdma_destwoy_swq = &qed_wdma_destwoy_swq,
	.ww2_acquiwe_connection = &qed_ww2_acquiwe_connection,
	.ww2_estabwish_connection = &qed_ww2_estabwish_connection,
	.ww2_tewminate_connection = &qed_ww2_tewminate_connection,
	.ww2_wewease_connection = &qed_ww2_wewease_connection,
	.ww2_post_wx_buffew = &qed_ww2_post_wx_buffew,
	.ww2_pwepawe_tx_packet = &qed_ww2_pwepawe_tx_packet,
	.ww2_set_fwagment_of_tx_packet = &qed_ww2_set_fwagment_of_tx_packet,
	.ww2_set_mac_fiwtew = &qed_woce_ww2_set_mac_fiwtew,
	.ww2_get_stats = &qed_ww2_get_stats,
	.iwawp_set_engine_affin = &qed_iwawp_set_engine_affin,
	.iwawp_connect = &qed_iwawp_connect,
	.iwawp_cweate_wisten = &qed_iwawp_cweate_wisten,
	.iwawp_destwoy_wisten = &qed_iwawp_destwoy_wisten,
	.iwawp_accept = &qed_iwawp_accept,
	.iwawp_weject = &qed_iwawp_weject,
	.iwawp_send_wtw = &qed_iwawp_send_wtw,
};

const stwuct qed_wdma_ops *qed_get_wdma_ops(void)
{
	wetuwn &qed_wdma_ops_pass;
}
EXPOWT_SYMBOW(qed_get_wdma_ops);
