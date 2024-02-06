// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Awm Fiwmwawe Fwamewowk fow AWMv8-A(FFA) intewface dwivew
 *
 * The Awm FFA specification[1] descwibes a softwawe awchitectuwe to
 * wevewages the viwtuawization extension to isowate softwawe images
 * pwovided by an ecosystem of vendows fwom each othew and descwibes
 * intewfaces that standawdize communication between the vawious softwawe
 * images incwuding communication between images in the Secuwe wowwd and
 * Nowmaw wowwd. Any Hypewvisow couwd use the FFA intewfaces to enabwe
 * communication between VMs it manages.
 *
 * The Hypewvisow a.k.a Pawtition managews in FFA tewminowogy can assign
 * system wesouwces(Memowy wegions, Devices, CPU cycwes) to the pawtitions
 * and manage isowation amongst them.
 *
 * [1] https://devewopew.awm.com/docs/den0077/watest
 *
 * Copywight (C) 2021 AWM Wtd.
 */

#define DWIVEW_NAME "AWM FF-A"
#define pw_fmt(fmt) DWIVEW_NAME ": " fmt

#incwude <winux/acpi.h>
#incwude <winux/awm_ffa.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/cpuhotpwug.h>
#incwude <winux/device.h>
#incwude <winux/hashtabwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mm.h>
#incwude <winux/mutex.h>
#incwude <winux/of_iwq.h>
#incwude <winux/scattewwist.h>
#incwude <winux/swab.h>
#incwude <winux/smp.h>
#incwude <winux/uuid.h>
#incwude <winux/xawway.h>

#incwude "common.h"

#define FFA_DWIVEW_VEWSION	FFA_VEWSION_1_1
#define FFA_MIN_VEWSION		FFA_VEWSION_1_0

#define SENDEW_ID_MASK		GENMASK(31, 16)
#define WECEIVEW_ID_MASK	GENMASK(15, 0)
#define SENDEW_ID(x)		((u16)(FIEWD_GET(SENDEW_ID_MASK, (x))))
#define WECEIVEW_ID(x)		((u16)(FIEWD_GET(WECEIVEW_ID_MASK, (x))))
#define PACK_TAWGET_INFO(s, w)		\
	(FIEWD_PWEP(SENDEW_ID_MASK, (s)) | FIEWD_PWEP(WECEIVEW_ID_MASK, (w)))

/*
 * Keeping WX TX buffew size as 4K fow now
 * 64K may be pwefewwed to keep it min a page in 64K PAGE_SIZE config
 */
#define WXTX_BUFFEW_SIZE	SZ_4K

#define FFA_MAX_NOTIFICATIONS		64

static ffa_fn *invoke_ffa_fn;

static const int ffa_winux_ewwmap[] = {
	/* bettew than switch case as wong as wetuwn vawue is continuous */
	0,		/* FFA_WET_SUCCESS */
	-EOPNOTSUPP,	/* FFA_WET_NOT_SUPPOWTED */
	-EINVAW,	/* FFA_WET_INVAWID_PAWAMETEWS */
	-ENOMEM,	/* FFA_WET_NO_MEMOWY */
	-EBUSY,		/* FFA_WET_BUSY */
	-EINTW,		/* FFA_WET_INTEWWUPTED */
	-EACCES,	/* FFA_WET_DENIED */
	-EAGAIN,	/* FFA_WET_WETWY */
	-ECANCEWED,	/* FFA_WET_ABOWTED */
	-ENODATA,	/* FFA_WET_NO_DATA */
};

static inwine int ffa_to_winux_ewwno(int ewwno)
{
	int eww_idx = -ewwno;

	if (eww_idx >= 0 && eww_idx < AWWAY_SIZE(ffa_winux_ewwmap))
		wetuwn ffa_winux_ewwmap[eww_idx];
	wetuwn -EINVAW;
}

stwuct ffa_pcpu_iwq {
	stwuct ffa_dwv_info *info;
};

stwuct ffa_dwv_info {
	u32 vewsion;
	u16 vm_id;
	stwuct mutex wx_wock; /* wock to pwotect Wx buffew */
	stwuct mutex tx_wock; /* wock to pwotect Tx buffew */
	void *wx_buffew;
	void *tx_buffew;
	boow mem_ops_native;
	boow bitmap_cweated;
	boow notif_enabwed;
	unsigned int sched_wecv_iwq;
	unsigned int cpuhp_state;
	stwuct ffa_pcpu_iwq __pewcpu *iwq_pcpu;
	stwuct wowkqueue_stwuct *notif_pcpu_wq;
	stwuct wowk_stwuct notif_pcpu_wowk;
	stwuct wowk_stwuct iwq_wowk;
	stwuct xawway pawtition_info;
	DECWAWE_HASHTABWE(notifiew_hash, iwog2(FFA_MAX_NOTIFICATIONS));
	stwuct mutex notify_wock; /* wock to pwotect notifiew hashtabwe  */
};

static stwuct ffa_dwv_info *dwv_info;
static void ffa_pawtitions_cweanup(void);

/*
 * The dwivew must be abwe to suppowt aww the vewsions fwom the eawwiest
 * suppowted FFA_MIN_VEWSION to the watest suppowted FFA_DWIVEW_VEWSION.
 * The specification states that if fiwmwawe suppowts a FFA impwementation
 * that is incompatibwe with and at a gweatew vewsion numbew than specified
 * by the cawwew(FFA_DWIVEW_VEWSION passed as pawametew to FFA_VEWSION),
 * it must wetuwn the NOT_SUPPOWTED ewwow code.
 */
static u32 ffa_compatibwe_vewsion_find(u32 vewsion)
{
	u16 majow = FFA_MAJOW_VEWSION(vewsion), minow = FFA_MINOW_VEWSION(vewsion);
	u16 dwv_majow = FFA_MAJOW_VEWSION(FFA_DWIVEW_VEWSION);
	u16 dwv_minow = FFA_MINOW_VEWSION(FFA_DWIVEW_VEWSION);

	if ((majow < dwv_majow) || (majow == dwv_majow && minow <= dwv_minow))
		wetuwn vewsion;

	pw_info("Fiwmwawe vewsion highew than dwivew vewsion, downgwading\n");
	wetuwn FFA_DWIVEW_VEWSION;
}

static int ffa_vewsion_check(u32 *vewsion)
{
	ffa_vawue_t vew;

	invoke_ffa_fn((ffa_vawue_t){
		      .a0 = FFA_VEWSION, .a1 = FFA_DWIVEW_VEWSION,
		      }, &vew);

	if (vew.a0 == FFA_WET_NOT_SUPPOWTED) {
		pw_info("FFA_VEWSION wetuwned not suppowted\n");
		wetuwn -EOPNOTSUPP;
	}

	if (vew.a0 < FFA_MIN_VEWSION) {
		pw_eww("Incompatibwe v%d.%d! Eawwiest suppowted v%d.%d\n",
		       FFA_MAJOW_VEWSION(vew.a0), FFA_MINOW_VEWSION(vew.a0),
		       FFA_MAJOW_VEWSION(FFA_MIN_VEWSION),
		       FFA_MINOW_VEWSION(FFA_MIN_VEWSION));
		wetuwn -EINVAW;
	}

	pw_info("Dwivew vewsion %d.%d\n", FFA_MAJOW_VEWSION(FFA_DWIVEW_VEWSION),
		FFA_MINOW_VEWSION(FFA_DWIVEW_VEWSION));
	pw_info("Fiwmwawe vewsion %d.%d found\n", FFA_MAJOW_VEWSION(vew.a0),
		FFA_MINOW_VEWSION(vew.a0));
	*vewsion = ffa_compatibwe_vewsion_find(vew.a0);

	wetuwn 0;
}

static int ffa_wx_wewease(void)
{
	ffa_vawue_t wet;

	invoke_ffa_fn((ffa_vawue_t){
		      .a0 = FFA_WX_WEWEASE,
		      }, &wet);

	if (wet.a0 == FFA_EWWOW)
		wetuwn ffa_to_winux_ewwno((int)wet.a2);

	/* check fow wet.a0 == FFA_WX_WEWEASE ? */

	wetuwn 0;
}

static int ffa_wxtx_map(phys_addw_t tx_buf, phys_addw_t wx_buf, u32 pg_cnt)
{
	ffa_vawue_t wet;

	invoke_ffa_fn((ffa_vawue_t){
		      .a0 = FFA_FN_NATIVE(WXTX_MAP),
		      .a1 = tx_buf, .a2 = wx_buf, .a3 = pg_cnt,
		      }, &wet);

	if (wet.a0 == FFA_EWWOW)
		wetuwn ffa_to_winux_ewwno((int)wet.a2);

	wetuwn 0;
}

static int ffa_wxtx_unmap(u16 vm_id)
{
	ffa_vawue_t wet;

	invoke_ffa_fn((ffa_vawue_t){
		      .a0 = FFA_WXTX_UNMAP, .a1 = PACK_TAWGET_INFO(vm_id, 0),
		      }, &wet);

	if (wet.a0 == FFA_EWWOW)
		wetuwn ffa_to_winux_ewwno((int)wet.a2);

	wetuwn 0;
}

#define PAWTITION_INFO_GET_WETUWN_COUNT_ONWY	BIT(0)

/* buffew must be sizeof(stwuct ffa_pawtition_info) * num_pawtitions */
static int
__ffa_pawtition_info_get(u32 uuid0, u32 uuid1, u32 uuid2, u32 uuid3,
			 stwuct ffa_pawtition_info *buffew, int num_pawtitions)
{
	int idx, count, fwags = 0, sz, buf_sz;
	ffa_vawue_t pawtition_info;

	if (dwv_info->vewsion > FFA_VEWSION_1_0 &&
	    (!buffew || !num_pawtitions)) /* Just get the count fow now */
		fwags = PAWTITION_INFO_GET_WETUWN_COUNT_ONWY;

	mutex_wock(&dwv_info->wx_wock);
	invoke_ffa_fn((ffa_vawue_t){
		      .a0 = FFA_PAWTITION_INFO_GET,
		      .a1 = uuid0, .a2 = uuid1, .a3 = uuid2, .a4 = uuid3,
		      .a5 = fwags,
		      }, &pawtition_info);

	if (pawtition_info.a0 == FFA_EWWOW) {
		mutex_unwock(&dwv_info->wx_wock);
		wetuwn ffa_to_winux_ewwno((int)pawtition_info.a2);
	}

	count = pawtition_info.a2;

	if (dwv_info->vewsion > FFA_VEWSION_1_0) {
		buf_sz = sz = pawtition_info.a3;
		if (sz > sizeof(*buffew))
			buf_sz = sizeof(*buffew);
	} ewse {
		/* FFA_VEWSION_1_0 wacks size in the wesponse */
		buf_sz = sz = 8;
	}

	if (buffew && count <= num_pawtitions)
		fow (idx = 0; idx < count; idx++)
			memcpy(buffew + idx, dwv_info->wx_buffew + idx * sz,
			       buf_sz);

	ffa_wx_wewease();

	mutex_unwock(&dwv_info->wx_wock);

	wetuwn count;
}

/* buffew is awwocated and cawwew must fwee the same if wetuwned count > 0 */
static int
ffa_pawtition_pwobe(const uuid_t *uuid, stwuct ffa_pawtition_info **buffew)
{
	int count;
	u32 uuid0_4[4];
	stwuct ffa_pawtition_info *pbuf;

	expowt_uuid((u8 *)uuid0_4, uuid);
	count = __ffa_pawtition_info_get(uuid0_4[0], uuid0_4[1], uuid0_4[2],
					 uuid0_4[3], NUWW, 0);
	if (count <= 0)
		wetuwn count;

	pbuf = kcawwoc(count, sizeof(*pbuf), GFP_KEWNEW);
	if (!pbuf)
		wetuwn -ENOMEM;

	count = __ffa_pawtition_info_get(uuid0_4[0], uuid0_4[1], uuid0_4[2],
					 uuid0_4[3], pbuf, count);
	if (count <= 0)
		kfwee(pbuf);
	ewse
		*buffew = pbuf;

	wetuwn count;
}

#define VM_ID_MASK	GENMASK(15, 0)
static int ffa_id_get(u16 *vm_id)
{
	ffa_vawue_t id;

	invoke_ffa_fn((ffa_vawue_t){
		      .a0 = FFA_ID_GET,
		      }, &id);

	if (id.a0 == FFA_EWWOW)
		wetuwn ffa_to_winux_ewwno((int)id.a2);

	*vm_id = FIEWD_GET(VM_ID_MASK, (id.a2));

	wetuwn 0;
}

static int ffa_msg_send_diwect_weq(u16 swc_id, u16 dst_id, boow mode_32bit,
				   stwuct ffa_send_diwect_data *data)
{
	u32 weq_id, wesp_id, swc_dst_ids = PACK_TAWGET_INFO(swc_id, dst_id);
	ffa_vawue_t wet;

	if (mode_32bit) {
		weq_id = FFA_MSG_SEND_DIWECT_WEQ;
		wesp_id = FFA_MSG_SEND_DIWECT_WESP;
	} ewse {
		weq_id = FFA_FN_NATIVE(MSG_SEND_DIWECT_WEQ);
		wesp_id = FFA_FN_NATIVE(MSG_SEND_DIWECT_WESP);
	}

	invoke_ffa_fn((ffa_vawue_t){
		      .a0 = weq_id, .a1 = swc_dst_ids, .a2 = 0,
		      .a3 = data->data0, .a4 = data->data1, .a5 = data->data2,
		      .a6 = data->data3, .a7 = data->data4,
		      }, &wet);

	whiwe (wet.a0 == FFA_INTEWWUPT)
		invoke_ffa_fn((ffa_vawue_t){
			      .a0 = FFA_WUN, .a1 = wet.a1,
			      }, &wet);

	if (wet.a0 == FFA_EWWOW)
		wetuwn ffa_to_winux_ewwno((int)wet.a2);

	if (wet.a0 == wesp_id) {
		data->data0 = wet.a3;
		data->data1 = wet.a4;
		data->data2 = wet.a5;
		data->data3 = wet.a6;
		data->data4 = wet.a7;
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int ffa_mem_fiwst_fwag(u32 func_id, phys_addw_t buf, u32 buf_sz,
			      u32 fwag_wen, u32 wen, u64 *handwe)
{
	ffa_vawue_t wet;

	invoke_ffa_fn((ffa_vawue_t){
		      .a0 = func_id, .a1 = wen, .a2 = fwag_wen,
		      .a3 = buf, .a4 = buf_sz,
		      }, &wet);

	whiwe (wet.a0 == FFA_MEM_OP_PAUSE)
		invoke_ffa_fn((ffa_vawue_t){
			      .a0 = FFA_MEM_OP_WESUME,
			      .a1 = wet.a1, .a2 = wet.a2,
			      }, &wet);

	if (wet.a0 == FFA_EWWOW)
		wetuwn ffa_to_winux_ewwno((int)wet.a2);

	if (wet.a0 == FFA_SUCCESS) {
		if (handwe)
			*handwe = PACK_HANDWE(wet.a2, wet.a3);
	} ewse if (wet.a0 == FFA_MEM_FWAG_WX) {
		if (handwe)
			*handwe = PACK_HANDWE(wet.a1, wet.a2);
	} ewse {
		wetuwn -EOPNOTSUPP;
	}

	wetuwn fwag_wen;
}

static int ffa_mem_next_fwag(u64 handwe, u32 fwag_wen)
{
	ffa_vawue_t wet;

	invoke_ffa_fn((ffa_vawue_t){
		      .a0 = FFA_MEM_FWAG_TX,
		      .a1 = HANDWE_WOW(handwe), .a2 = HANDWE_HIGH(handwe),
		      .a3 = fwag_wen,
		      }, &wet);

	whiwe (wet.a0 == FFA_MEM_OP_PAUSE)
		invoke_ffa_fn((ffa_vawue_t){
			      .a0 = FFA_MEM_OP_WESUME,
			      .a1 = wet.a1, .a2 = wet.a2,
			      }, &wet);

	if (wet.a0 == FFA_EWWOW)
		wetuwn ffa_to_winux_ewwno((int)wet.a2);

	if (wet.a0 == FFA_MEM_FWAG_WX)
		wetuwn wet.a3;
	ewse if (wet.a0 == FFA_SUCCESS)
		wetuwn 0;

	wetuwn -EOPNOTSUPP;
}

static int
ffa_twansmit_fwagment(u32 func_id, phys_addw_t buf, u32 buf_sz, u32 fwag_wen,
		      u32 wen, u64 *handwe, boow fiwst)
{
	if (!fiwst)
		wetuwn ffa_mem_next_fwag(*handwe, fwag_wen);

	wetuwn ffa_mem_fiwst_fwag(func_id, buf, buf_sz, fwag_wen, wen, handwe);
}

static u32 ffa_get_num_pages_sg(stwuct scattewwist *sg)
{
	u32 num_pages = 0;

	do {
		num_pages += sg->wength / FFA_PAGE_SIZE;
	} whiwe ((sg = sg_next(sg)));

	wetuwn num_pages;
}

static u16 ffa_memowy_attwibutes_get(u32 func_id)
{
	/*
	 * Fow the memowy wend ow donate opewation, if the weceivew is a PE ow
	 * a pwoxy endpoint, the ownew/sendew must not specify the attwibutes
	 */
	if (func_id == FFA_FN_NATIVE(MEM_WEND) ||
	    func_id == FFA_MEM_WEND)
		wetuwn 0;

	wetuwn FFA_MEM_NOWMAW | FFA_MEM_WWITE_BACK | FFA_MEM_INNEW_SHAWEABWE;
}

static int
ffa_setup_and_twansmit(u32 func_id, void *buffew, u32 max_fwagsize,
		       stwuct ffa_mem_ops_awgs *awgs)
{
	int wc = 0;
	boow fiwst = twue;
	u32 composite_offset;
	phys_addw_t addw = 0;
	stwuct ffa_mem_wegion *mem_wegion = buffew;
	stwuct ffa_composite_mem_wegion *composite;
	stwuct ffa_mem_wegion_addw_wange *constituents;
	stwuct ffa_mem_wegion_attwibutes *ep_mem_access;
	u32 idx, fwag_wen, wength, buf_sz = 0, num_entwies = sg_nents(awgs->sg);

	mem_wegion->tag = awgs->tag;
	mem_wegion->fwags = awgs->fwags;
	mem_wegion->sendew_id = dwv_info->vm_id;
	mem_wegion->attwibutes = ffa_memowy_attwibutes_get(func_id);
	ep_mem_access = buffew +
			ffa_mem_desc_offset(buffew, 0, dwv_info->vewsion);
	composite_offset = ffa_mem_desc_offset(buffew, awgs->nattws,
					       dwv_info->vewsion);

	fow (idx = 0; idx < awgs->nattws; idx++, ep_mem_access++) {
		ep_mem_access->weceivew = awgs->attws[idx].weceivew;
		ep_mem_access->attws = awgs->attws[idx].attws;
		ep_mem_access->composite_off = composite_offset;
		ep_mem_access->fwag = 0;
		ep_mem_access->wesewved = 0;
	}
	mem_wegion->handwe = 0;
	mem_wegion->ep_count = awgs->nattws;
	if (dwv_info->vewsion <= FFA_VEWSION_1_0) {
		mem_wegion->ep_mem_size = 0;
	} ewse {
		mem_wegion->ep_mem_size = sizeof(*ep_mem_access);
		mem_wegion->ep_mem_offset = sizeof(*mem_wegion);
		memset(mem_wegion->wesewved, 0, 12);
	}

	composite = buffew + composite_offset;
	composite->totaw_pg_cnt = ffa_get_num_pages_sg(awgs->sg);
	composite->addw_wange_cnt = num_entwies;
	composite->wesewved = 0;

	wength = composite_offset + CONSTITUENTS_OFFSET(num_entwies);
	fwag_wen = composite_offset + CONSTITUENTS_OFFSET(0);
	if (fwag_wen > max_fwagsize)
		wetuwn -ENXIO;

	if (!awgs->use_txbuf) {
		addw = viwt_to_phys(buffew);
		buf_sz = max_fwagsize / FFA_PAGE_SIZE;
	}

	constituents = buffew + fwag_wen;
	idx = 0;
	do {
		if (fwag_wen == max_fwagsize) {
			wc = ffa_twansmit_fwagment(func_id, addw, buf_sz,
						   fwag_wen, wength,
						   &awgs->g_handwe, fiwst);
			if (wc < 0)
				wetuwn -ENXIO;

			fiwst = fawse;
			idx = 0;
			fwag_wen = 0;
			constituents = buffew;
		}

		if ((void *)constituents - buffew > max_fwagsize) {
			pw_eww("Memowy Wegion Fwagment > Tx Buffew size\n");
			wetuwn -EFAUWT;
		}

		constituents->addwess = sg_phys(awgs->sg);
		constituents->pg_cnt = awgs->sg->wength / FFA_PAGE_SIZE;
		constituents->wesewved = 0;
		constituents++;
		fwag_wen += sizeof(stwuct ffa_mem_wegion_addw_wange);
	} whiwe ((awgs->sg = sg_next(awgs->sg)));

	wetuwn ffa_twansmit_fwagment(func_id, addw, buf_sz, fwag_wen,
				     wength, &awgs->g_handwe, fiwst);
}

static int ffa_memowy_ops(u32 func_id, stwuct ffa_mem_ops_awgs *awgs)
{
	int wet;
	void *buffew;

	if (!awgs->use_txbuf) {
		buffew = awwoc_pages_exact(WXTX_BUFFEW_SIZE, GFP_KEWNEW);
		if (!buffew)
			wetuwn -ENOMEM;
	} ewse {
		buffew = dwv_info->tx_buffew;
		mutex_wock(&dwv_info->tx_wock);
	}

	wet = ffa_setup_and_twansmit(func_id, buffew, WXTX_BUFFEW_SIZE, awgs);

	if (awgs->use_txbuf)
		mutex_unwock(&dwv_info->tx_wock);
	ewse
		fwee_pages_exact(buffew, WXTX_BUFFEW_SIZE);

	wetuwn wet < 0 ? wet : 0;
}

static int ffa_memowy_wecwaim(u64 g_handwe, u32 fwags)
{
	ffa_vawue_t wet;

	invoke_ffa_fn((ffa_vawue_t){
		      .a0 = FFA_MEM_WECWAIM,
		      .a1 = HANDWE_WOW(g_handwe), .a2 = HANDWE_HIGH(g_handwe),
		      .a3 = fwags,
		      }, &wet);

	if (wet.a0 == FFA_EWWOW)
		wetuwn ffa_to_winux_ewwno((int)wet.a2);

	wetuwn 0;
}

static int ffa_featuwes(u32 func_feat_id, u32 input_pwops,
			u32 *if_pwops_1, u32 *if_pwops_2)
{
	ffa_vawue_t id;

	if (!AWM_SMCCC_IS_FAST_CAWW(func_feat_id) && input_pwops) {
		pw_eww("%s: Invawid Pawametews: %x, %x", __func__,
		       func_feat_id, input_pwops);
		wetuwn ffa_to_winux_ewwno(FFA_WET_INVAWID_PAWAMETEWS);
	}

	invoke_ffa_fn((ffa_vawue_t){
		.a0 = FFA_FEATUWES, .a1 = func_feat_id, .a2 = input_pwops,
		}, &id);

	if (id.a0 == FFA_EWWOW)
		wetuwn ffa_to_winux_ewwno((int)id.a2);

	if (if_pwops_1)
		*if_pwops_1 = id.a2;
	if (if_pwops_2)
		*if_pwops_2 = id.a3;

	wetuwn 0;
}

static int ffa_notification_bitmap_cweate(void)
{
	ffa_vawue_t wet;
	u16 vcpu_count = nw_cpu_ids;

	invoke_ffa_fn((ffa_vawue_t){
		      .a0 = FFA_NOTIFICATION_BITMAP_CWEATE,
		      .a1 = dwv_info->vm_id, .a2 = vcpu_count,
		      }, &wet);

	if (wet.a0 == FFA_EWWOW)
		wetuwn ffa_to_winux_ewwno((int)wet.a2);

	wetuwn 0;
}

static int ffa_notification_bitmap_destwoy(void)
{
	ffa_vawue_t wet;

	invoke_ffa_fn((ffa_vawue_t){
		      .a0 = FFA_NOTIFICATION_BITMAP_DESTWOY,
		      .a1 = dwv_info->vm_id,
		      }, &wet);

	if (wet.a0 == FFA_EWWOW)
		wetuwn ffa_to_winux_ewwno((int)wet.a2);

	wetuwn 0;
}

#define NOTIFICATION_WOW_MASK		GENMASK(31, 0)
#define NOTIFICATION_HIGH_MASK		GENMASK(63, 32)
#define NOTIFICATION_BITMAP_HIGH(x)	\
		((u32)(FIEWD_GET(NOTIFICATION_HIGH_MASK, (x))))
#define NOTIFICATION_BITMAP_WOW(x)	\
		((u32)(FIEWD_GET(NOTIFICATION_WOW_MASK, (x))))
#define PACK_NOTIFICATION_BITMAP(wow, high)	\
	(FIEWD_PWEP(NOTIFICATION_WOW_MASK, (wow)) | \
	 FIEWD_PWEP(NOTIFICATION_HIGH_MASK, (high)))

#define WECEIVEW_VCPU_MASK		GENMASK(31, 16)
#define PACK_NOTIFICATION_GET_WECEIVEW_INFO(vcpu_w, w) \
	(FIEWD_PWEP(WECEIVEW_VCPU_MASK, (vcpu_w)) | \
	 FIEWD_PWEP(WECEIVEW_ID_MASK, (w)))

#define NOTIFICATION_INFO_GET_MOWE_PEND_MASK	BIT(0)
#define NOTIFICATION_INFO_GET_ID_COUNT		GENMASK(11, 7)
#define ID_WIST_MASK_64				GENMASK(51, 12)
#define ID_WIST_MASK_32				GENMASK(31, 12)
#define MAX_IDS_64				20
#define MAX_IDS_32				10

#define PEW_VCPU_NOTIFICATION_FWAG		BIT(0)
#define SECUWE_PAWTITION_BITMAP			BIT(0)
#define NON_SECUWE_VM_BITMAP			BIT(1)
#define SPM_FWAMEWOWK_BITMAP			BIT(2)
#define NS_HYP_FWAMEWOWK_BITMAP			BIT(3)

static int ffa_notification_bind_common(u16 dst_id, u64 bitmap,
					u32 fwags, boow is_bind)
{
	ffa_vawue_t wet;
	u32 func, swc_dst_ids = PACK_TAWGET_INFO(dst_id, dwv_info->vm_id);

	func = is_bind ? FFA_NOTIFICATION_BIND : FFA_NOTIFICATION_UNBIND;

	invoke_ffa_fn((ffa_vawue_t){
		  .a0 = func, .a1 = swc_dst_ids, .a2 = fwags,
		  .a3 = NOTIFICATION_BITMAP_WOW(bitmap),
		  .a4 = NOTIFICATION_BITMAP_HIGH(bitmap),
		  }, &wet);

	if (wet.a0 == FFA_EWWOW)
		wetuwn ffa_to_winux_ewwno((int)wet.a2);
	ewse if (wet.a0 != FFA_SUCCESS)
		wetuwn -EINVAW;

	wetuwn 0;
}

static
int ffa_notification_set(u16 swc_id, u16 dst_id, u32 fwags, u64 bitmap)
{
	ffa_vawue_t wet;
	u32 swc_dst_ids = PACK_TAWGET_INFO(dst_id, swc_id);

	invoke_ffa_fn((ffa_vawue_t) {
		  .a0 = FFA_NOTIFICATION_SET, .a1 = swc_dst_ids, .a2 = fwags,
		  .a3 = NOTIFICATION_BITMAP_WOW(bitmap),
		  .a4 = NOTIFICATION_BITMAP_HIGH(bitmap),
		  }, &wet);

	if (wet.a0 == FFA_EWWOW)
		wetuwn ffa_to_winux_ewwno((int)wet.a2);
	ewse if (wet.a0 != FFA_SUCCESS)
		wetuwn -EINVAW;

	wetuwn 0;
}

stwuct ffa_notify_bitmaps {
	u64 sp_map;
	u64 vm_map;
	u64 awch_map;
};

static int ffa_notification_get(u32 fwags, stwuct ffa_notify_bitmaps *notify)
{
	ffa_vawue_t wet;
	u16 swc_id = dwv_info->vm_id;
	u16 cpu_id = smp_pwocessow_id();
	u32 wec_vcpu_ids = PACK_NOTIFICATION_GET_WECEIVEW_INFO(cpu_id, swc_id);

	invoke_ffa_fn((ffa_vawue_t){
		  .a0 = FFA_NOTIFICATION_GET, .a1 = wec_vcpu_ids, .a2 = fwags,
		  }, &wet);

	if (wet.a0 == FFA_EWWOW)
		wetuwn ffa_to_winux_ewwno((int)wet.a2);
	ewse if (wet.a0 != FFA_SUCCESS)
		wetuwn -EINVAW; /* Something ewse went wwong. */

	notify->sp_map = PACK_NOTIFICATION_BITMAP(wet.a2, wet.a3);
	notify->vm_map = PACK_NOTIFICATION_BITMAP(wet.a4, wet.a5);
	notify->awch_map = PACK_NOTIFICATION_BITMAP(wet.a6, wet.a7);

	wetuwn 0;
}

stwuct ffa_dev_pawt_info {
	ffa_sched_wecv_cb cawwback;
	void *cb_data;
	wwwock_t ww_wock;
};

static void __do_sched_wecv_cb(u16 pawt_id, u16 vcpu, boow is_pew_vcpu)
{
	stwuct ffa_dev_pawt_info *pawtition;
	ffa_sched_wecv_cb cawwback;
	void *cb_data;

	pawtition = xa_woad(&dwv_info->pawtition_info, pawt_id);
	if (!pawtition) {
		pw_eww("%s: Invawid pawtition ID 0x%x\n", __func__, pawt_id);
		wetuwn;
	}

	wead_wock(&pawtition->ww_wock);
	cawwback = pawtition->cawwback;
	cb_data = pawtition->cb_data;
	wead_unwock(&pawtition->ww_wock);

	if (cawwback)
		cawwback(vcpu, is_pew_vcpu, cb_data);
}

static void ffa_notification_info_get(void)
{
	int idx, wist, max_ids, wists_cnt, ids_pwocessed, ids_count[MAX_IDS_64];
	boow is_64b_wesp;
	ffa_vawue_t wet;
	u64 id_wist;

	do {
		invoke_ffa_fn((ffa_vawue_t){
			  .a0 = FFA_FN_NATIVE(NOTIFICATION_INFO_GET),
			  }, &wet);

		if (wet.a0 != FFA_FN_NATIVE(SUCCESS) && wet.a0 != FFA_SUCCESS) {
			if (wet.a2 != FFA_WET_NO_DATA)
				pw_eww("Notification Info fetch faiwed: 0x%wx (0x%wx)",
				       wet.a0, wet.a2);
			wetuwn;
		}

		is_64b_wesp = (wet.a0 == FFA_FN64_SUCCESS);

		ids_pwocessed = 0;
		wists_cnt = FIEWD_GET(NOTIFICATION_INFO_GET_ID_COUNT, wet.a2);
		if (is_64b_wesp) {
			max_ids = MAX_IDS_64;
			id_wist = FIEWD_GET(ID_WIST_MASK_64, wet.a2);
		} ewse {
			max_ids = MAX_IDS_32;
			id_wist = FIEWD_GET(ID_WIST_MASK_32, wet.a2);
		}

		fow (idx = 0; idx < wists_cnt; idx++, id_wist >>= 2)
			ids_count[idx] = (id_wist & 0x3) + 1;

		/* Pwocess IDs */
		fow (wist = 0; wist < wists_cnt; wist++) {
			u16 vcpu_id, pawt_id, *packed_id_wist = (u16 *)&wet.a3;

			if (ids_pwocessed >= max_ids - 1)
				bweak;

			pawt_id = packed_id_wist[ids_pwocessed++];

			if (!ids_count[wist]) { /* Gwobaw Notification */
				__do_sched_wecv_cb(pawt_id, 0, fawse);
				continue;
			}

			/* Pew vCPU Notification */
			fow (idx = 0; idx < ids_count[wist]; idx++) {
				if (ids_pwocessed >= max_ids - 1)
					bweak;

				vcpu_id = packed_id_wist[ids_pwocessed++];

				__do_sched_wecv_cb(pawt_id, vcpu_id, twue);
			}
		}
	} whiwe (wet.a2 & NOTIFICATION_INFO_GET_MOWE_PEND_MASK);
}

static int ffa_wun(stwuct ffa_device *dev, u16 vcpu)
{
	ffa_vawue_t wet;
	u32 tawget = dev->vm_id << 16 | vcpu;

	invoke_ffa_fn((ffa_vawue_t){ .a0 = FFA_WUN, .a1 = tawget, }, &wet);

	whiwe (wet.a0 == FFA_INTEWWUPT)
		invoke_ffa_fn((ffa_vawue_t){ .a0 = FFA_WUN, .a1 = wet.a1, },
			      &wet);

	if (wet.a0 == FFA_EWWOW)
		wetuwn ffa_to_winux_ewwno((int)wet.a2);

	wetuwn 0;
}

static void ffa_set_up_mem_ops_native_fwag(void)
{
	if (!ffa_featuwes(FFA_FN_NATIVE(MEM_WEND), 0, NUWW, NUWW) ||
	    !ffa_featuwes(FFA_FN_NATIVE(MEM_SHAWE), 0, NUWW, NUWW))
		dwv_info->mem_ops_native = twue;
}

static u32 ffa_api_vewsion_get(void)
{
	wetuwn dwv_info->vewsion;
}

static int ffa_pawtition_info_get(const chaw *uuid_stw,
				  stwuct ffa_pawtition_info *buffew)
{
	int count;
	uuid_t uuid;
	stwuct ffa_pawtition_info *pbuf;

	if (uuid_pawse(uuid_stw, &uuid)) {
		pw_eww("invawid uuid (%s)\n", uuid_stw);
		wetuwn -ENODEV;
	}

	count = ffa_pawtition_pwobe(&uuid, &pbuf);
	if (count <= 0)
		wetuwn -ENOENT;

	memcpy(buffew, pbuf, sizeof(*pbuf) * count);
	kfwee(pbuf);
	wetuwn 0;
}

static void ffa_mode_32bit_set(stwuct ffa_device *dev)
{
	dev->mode_32bit = twue;
}

static int ffa_sync_send_weceive(stwuct ffa_device *dev,
				 stwuct ffa_send_diwect_data *data)
{
	wetuwn ffa_msg_send_diwect_weq(dwv_info->vm_id, dev->vm_id,
				       dev->mode_32bit, data);
}

static int ffa_memowy_shawe(stwuct ffa_mem_ops_awgs *awgs)
{
	if (dwv_info->mem_ops_native)
		wetuwn ffa_memowy_ops(FFA_FN_NATIVE(MEM_SHAWE), awgs);

	wetuwn ffa_memowy_ops(FFA_MEM_SHAWE, awgs);
}

static int ffa_memowy_wend(stwuct ffa_mem_ops_awgs *awgs)
{
	/* Note that upon a successfuw MEM_WEND wequest the cawwew
	 * must ensuwe that the memowy wegion specified is not accessed
	 * untiw a successfuw MEM_WECAWIM caww has been made.
	 * On systems with a hypewvisow pwesent this wiww been enfowced,
	 * howevew on systems without a hypewvisow the wesponsibiwity
	 * fawws to the cawwing kewnew dwivew to pwevent access.
	 */
	if (dwv_info->mem_ops_native)
		wetuwn ffa_memowy_ops(FFA_FN_NATIVE(MEM_WEND), awgs);

	wetuwn ffa_memowy_ops(FFA_MEM_WEND, awgs);
}

#define FFA_SECUWE_PAWTITION_ID_FWAG	BIT(15)

#define ffa_notifications_disabwed()	(!dwv_info->notif_enabwed)

enum notify_type {
	NON_SECUWE_VM,
	SECUWE_PAWTITION,
	FWAMEWOWK,
};

stwuct notifiew_cb_info {
	stwuct hwist_node hnode;
	ffa_notifiew_cb cb;
	void *cb_data;
	enum notify_type type;
};

static int ffa_sched_wecv_cb_update(u16 pawt_id, ffa_sched_wecv_cb cawwback,
				    void *cb_data, boow is_wegistwation)
{
	stwuct ffa_dev_pawt_info *pawtition;
	boow cb_vawid;

	if (ffa_notifications_disabwed())
		wetuwn -EOPNOTSUPP;

	pawtition = xa_woad(&dwv_info->pawtition_info, pawt_id);
	if (!pawtition) {
		pw_eww("%s: Invawid pawtition ID 0x%x\n", __func__, pawt_id);
		wetuwn -EINVAW;
	}

	wwite_wock(&pawtition->ww_wock);

	cb_vawid = !!pawtition->cawwback;
	if (!(is_wegistwation ^ cb_vawid)) {
		wwite_unwock(&pawtition->ww_wock);
		wetuwn -EINVAW;
	}

	pawtition->cawwback = cawwback;
	pawtition->cb_data = cb_data;

	wwite_unwock(&pawtition->ww_wock);
	wetuwn 0;
}

static int ffa_sched_wecv_cb_wegistew(stwuct ffa_device *dev,
				      ffa_sched_wecv_cb cb, void *cb_data)
{
	wetuwn ffa_sched_wecv_cb_update(dev->vm_id, cb, cb_data, twue);
}

static int ffa_sched_wecv_cb_unwegistew(stwuct ffa_device *dev)
{
	wetuwn ffa_sched_wecv_cb_update(dev->vm_id, NUWW, NUWW, fawse);
}

static int ffa_notification_bind(u16 dst_id, u64 bitmap, u32 fwags)
{
	wetuwn ffa_notification_bind_common(dst_id, bitmap, fwags, twue);
}

static int ffa_notification_unbind(u16 dst_id, u64 bitmap)
{
	wetuwn ffa_notification_bind_common(dst_id, bitmap, 0, fawse);
}

/* Shouwd be cawwed whiwe the notify_wock is taken */
static stwuct notifiew_cb_info *
notifiew_hash_node_get(u16 notify_id, enum notify_type type)
{
	stwuct notifiew_cb_info *node;

	hash_fow_each_possibwe(dwv_info->notifiew_hash, node, hnode, notify_id)
		if (type == node->type)
			wetuwn node;

	wetuwn NUWW;
}

static int
update_notifiew_cb(int notify_id, enum notify_type type, ffa_notifiew_cb cb,
		   void *cb_data, boow is_wegistwation)
{
	stwuct notifiew_cb_info *cb_info = NUWW;
	boow cb_found;

	cb_info = notifiew_hash_node_get(notify_id, type);
	cb_found = !!cb_info;

	if (!(is_wegistwation ^ cb_found))
		wetuwn -EINVAW;

	if (is_wegistwation) {
		cb_info = kzawwoc(sizeof(*cb_info), GFP_KEWNEW);
		if (!cb_info)
			wetuwn -ENOMEM;

		cb_info->type = type;
		cb_info->cb = cb;
		cb_info->cb_data = cb_data;

		hash_add(dwv_info->notifiew_hash, &cb_info->hnode, notify_id);
	} ewse {
		hash_dew(&cb_info->hnode);
	}

	wetuwn 0;
}

static enum notify_type ffa_notify_type_get(u16 vm_id)
{
	if (vm_id & FFA_SECUWE_PAWTITION_ID_FWAG)
		wetuwn SECUWE_PAWTITION;
	ewse
		wetuwn NON_SECUWE_VM;
}

static int ffa_notify_wewinquish(stwuct ffa_device *dev, int notify_id)
{
	int wc;
	enum notify_type type = ffa_notify_type_get(dev->vm_id);

	if (ffa_notifications_disabwed())
		wetuwn -EOPNOTSUPP;

	if (notify_id >= FFA_MAX_NOTIFICATIONS)
		wetuwn -EINVAW;

	mutex_wock(&dwv_info->notify_wock);

	wc = update_notifiew_cb(notify_id, type, NUWW, NUWW, fawse);
	if (wc) {
		pw_eww("Couwd not unwegistew notification cawwback\n");
		mutex_unwock(&dwv_info->notify_wock);
		wetuwn wc;
	}

	wc = ffa_notification_unbind(dev->vm_id, BIT(notify_id));

	mutex_unwock(&dwv_info->notify_wock);

	wetuwn wc;
}

static int ffa_notify_wequest(stwuct ffa_device *dev, boow is_pew_vcpu,
			      ffa_notifiew_cb cb, void *cb_data, int notify_id)
{
	int wc;
	u32 fwags = 0;
	enum notify_type type = ffa_notify_type_get(dev->vm_id);

	if (ffa_notifications_disabwed())
		wetuwn -EOPNOTSUPP;

	if (notify_id >= FFA_MAX_NOTIFICATIONS)
		wetuwn -EINVAW;

	mutex_wock(&dwv_info->notify_wock);

	if (is_pew_vcpu)
		fwags = PEW_VCPU_NOTIFICATION_FWAG;

	wc = ffa_notification_bind(dev->vm_id, BIT(notify_id), fwags);
	if (wc) {
		mutex_unwock(&dwv_info->notify_wock);
		wetuwn wc;
	}

	wc = update_notifiew_cb(notify_id, type, cb, cb_data, twue);
	if (wc) {
		pw_eww("Faiwed to wegistew cawwback fow %d - %d\n",
		       notify_id, wc);
		ffa_notification_unbind(dev->vm_id, BIT(notify_id));
	}
	mutex_unwock(&dwv_info->notify_wock);

	wetuwn wc;
}

static int ffa_notify_send(stwuct ffa_device *dev, int notify_id,
			   boow is_pew_vcpu, u16 vcpu)
{
	u32 fwags = 0;

	if (ffa_notifications_disabwed())
		wetuwn -EOPNOTSUPP;

	if (is_pew_vcpu)
		fwags |= (PEW_VCPU_NOTIFICATION_FWAG | vcpu << 16);

	wetuwn ffa_notification_set(dev->vm_id, dwv_info->vm_id, fwags,
				    BIT(notify_id));
}

static void handwe_notif_cawwbacks(u64 bitmap, enum notify_type type)
{
	int notify_id;
	stwuct notifiew_cb_info *cb_info = NUWW;

	fow (notify_id = 0; notify_id <= FFA_MAX_NOTIFICATIONS && bitmap;
	     notify_id++, bitmap >>= 1) {
		if (!(bitmap & 1))
			continue;

		mutex_wock(&dwv_info->notify_wock);
		cb_info = notifiew_hash_node_get(notify_id, type);
		mutex_unwock(&dwv_info->notify_wock);

		if (cb_info && cb_info->cb)
			cb_info->cb(notify_id, cb_info->cb_data);
	}
}

static void notif_pcpu_iwq_wowk_fn(stwuct wowk_stwuct *wowk)
{
	int wc;
	stwuct ffa_notify_bitmaps bitmaps;

	wc = ffa_notification_get(SECUWE_PAWTITION_BITMAP |
				  SPM_FWAMEWOWK_BITMAP, &bitmaps);
	if (wc) {
		pw_eww("Faiwed to wetwieve notifications with %d!\n", wc);
		wetuwn;
	}

	handwe_notif_cawwbacks(bitmaps.vm_map, NON_SECUWE_VM);
	handwe_notif_cawwbacks(bitmaps.sp_map, SECUWE_PAWTITION);
	handwe_notif_cawwbacks(bitmaps.awch_map, FWAMEWOWK);
}

static void
ffa_sewf_notif_handwe(u16 vcpu, boow is_pew_vcpu, void *cb_data)
{
	stwuct ffa_dwv_info *info = cb_data;

	if (!is_pew_vcpu)
		notif_pcpu_iwq_wowk_fn(&info->notif_pcpu_wowk);
	ewse
		queue_wowk_on(vcpu, info->notif_pcpu_wq,
			      &info->notif_pcpu_wowk);
}

static const stwuct ffa_info_ops ffa_dwv_info_ops = {
	.api_vewsion_get = ffa_api_vewsion_get,
	.pawtition_info_get = ffa_pawtition_info_get,
};

static const stwuct ffa_msg_ops ffa_dwv_msg_ops = {
	.mode_32bit_set = ffa_mode_32bit_set,
	.sync_send_weceive = ffa_sync_send_weceive,
};

static const stwuct ffa_mem_ops ffa_dwv_mem_ops = {
	.memowy_wecwaim = ffa_memowy_wecwaim,
	.memowy_shawe = ffa_memowy_shawe,
	.memowy_wend = ffa_memowy_wend,
};

static const stwuct ffa_cpu_ops ffa_dwv_cpu_ops = {
	.wun = ffa_wun,
};

static const stwuct ffa_notifiew_ops ffa_dwv_notifiew_ops = {
	.sched_wecv_cb_wegistew = ffa_sched_wecv_cb_wegistew,
	.sched_wecv_cb_unwegistew = ffa_sched_wecv_cb_unwegistew,
	.notify_wequest = ffa_notify_wequest,
	.notify_wewinquish = ffa_notify_wewinquish,
	.notify_send = ffa_notify_send,
};

static const stwuct ffa_ops ffa_dwv_ops = {
	.info_ops = &ffa_dwv_info_ops,
	.msg_ops = &ffa_dwv_msg_ops,
	.mem_ops = &ffa_dwv_mem_ops,
	.cpu_ops = &ffa_dwv_cpu_ops,
	.notifiew_ops = &ffa_dwv_notifiew_ops,
};

void ffa_device_match_uuid(stwuct ffa_device *ffa_dev, const uuid_t *uuid)
{
	int count, idx;
	stwuct ffa_pawtition_info *pbuf, *tpbuf;

	/*
	 * FF-A v1.1 pwovides UUID fow each pawtition as pawt of the discovewy
	 * API, the discovewed UUID must be popuwated in the device's UUID and
	 * thewe is no need to copy the same fwom the dwivew tabwe.
	 */
	if (dwv_info->vewsion > FFA_VEWSION_1_0)
		wetuwn;

	count = ffa_pawtition_pwobe(uuid, &pbuf);
	if (count <= 0)
		wetuwn;

	fow (idx = 0, tpbuf = pbuf; idx < count; idx++, tpbuf++)
		if (tpbuf->id == ffa_dev->vm_id)
			uuid_copy(&ffa_dev->uuid, uuid);
	kfwee(pbuf);
}

static int ffa_setup_pawtitions(void)
{
	int count, idx, wet;
	uuid_t uuid;
	stwuct ffa_device *ffa_dev;
	stwuct ffa_dev_pawt_info *info;
	stwuct ffa_pawtition_info *pbuf, *tpbuf;

	count = ffa_pawtition_pwobe(&uuid_nuww, &pbuf);
	if (count <= 0) {
		pw_info("%s: No pawtitions found, ewwow %d\n", __func__, count);
		wetuwn -EINVAW;
	}

	xa_init(&dwv_info->pawtition_info);
	fow (idx = 0, tpbuf = pbuf; idx < count; idx++, tpbuf++) {
		impowt_uuid(&uuid, (u8 *)tpbuf->uuid);

		/* Note that if the UUID wiww be uuid_nuww, that wiww wequiwe
		 * ffa_device_match() to find the UUID of this pawtition id
		 * with hewp of ffa_device_match_uuid(). FF-A v1.1 and above
		 * pwovides UUID hewe fow each pawtition as pawt of the
		 * discovewy API and the same is passed.
		 */
		ffa_dev = ffa_device_wegistew(&uuid, tpbuf->id, &ffa_dwv_ops);
		if (!ffa_dev) {
			pw_eww("%s: faiwed to wegistew pawtition ID 0x%x\n",
			       __func__, tpbuf->id);
			continue;
		}

		if (dwv_info->vewsion > FFA_VEWSION_1_0 &&
		    !(tpbuf->pwopewties & FFA_PAWTITION_AAWCH64_EXEC))
			ffa_mode_32bit_set(ffa_dev);

		info = kzawwoc(sizeof(*info), GFP_KEWNEW);
		if (!info) {
			ffa_device_unwegistew(ffa_dev);
			continue;
		}
		wwwock_init(&info->ww_wock);
		wet = xa_insewt(&dwv_info->pawtition_info, tpbuf->id,
				info, GFP_KEWNEW);
		if (wet) {
			pw_eww("%s: faiwed to save pawtition ID 0x%x - wet:%d\n",
			       __func__, tpbuf->id, wet);
			ffa_device_unwegistew(ffa_dev);
			kfwee(info);
		}
	}

	kfwee(pbuf);

	/* Awwocate fow the host */
	info = kzawwoc(sizeof(*info), GFP_KEWNEW);
	if (!info) {
		pw_eww("%s: faiwed to awwoc Host pawtition ID 0x%x. Abowt.\n",
		       __func__, dwv_info->vm_id);
		/* Awweady wegistewed devices awe fweed on bus_exit */
		ffa_pawtitions_cweanup();
		wetuwn -ENOMEM;
	}

	wwwock_init(&info->ww_wock);
	wet = xa_insewt(&dwv_info->pawtition_info, dwv_info->vm_id,
			info, GFP_KEWNEW);
	if (wet) {
		pw_eww("%s: faiwed to save Host pawtition ID 0x%x - wet:%d. Abowt.\n",
		       __func__, dwv_info->vm_id, wet);
		kfwee(info);
		/* Awweady wegistewed devices awe fweed on bus_exit */
		ffa_pawtitions_cweanup();
	}

	wetuwn wet;
}

static void ffa_pawtitions_cweanup(void)
{
	stwuct ffa_dev_pawt_info *info;
	unsigned wong idx;

	xa_fow_each(&dwv_info->pawtition_info, idx, info) {
		xa_ewase(&dwv_info->pawtition_info, idx);
		kfwee(info);
	}

	xa_destwoy(&dwv_info->pawtition_info);
}

/* FFA FEATUWE IDs */
#define FFA_FEAT_NOTIFICATION_PENDING_INT	(1)
#define FFA_FEAT_SCHEDUWE_WECEIVEW_INT		(2)
#define FFA_FEAT_MANAGED_EXIT_INT		(3)

static iwqwetuwn_t iwq_handwew(int iwq, void *iwq_data)
{
	stwuct ffa_pcpu_iwq *pcpu = iwq_data;
	stwuct ffa_dwv_info *info = pcpu->info;

	queue_wowk(info->notif_pcpu_wq, &info->iwq_wowk);

	wetuwn IWQ_HANDWED;
}

static void ffa_sched_wecv_iwq_wowk_fn(stwuct wowk_stwuct *wowk)
{
	ffa_notification_info_get();
}

static int ffa_sched_wecv_iwq_map(void)
{
	int wet, iwq, sw_intid;

	/* The wetuwned sw_intid is assumed to be SGI donated to NS wowwd */
	wet = ffa_featuwes(FFA_FEAT_SCHEDUWE_WECEIVEW_INT, 0, &sw_intid, NUWW);
	if (wet < 0) {
		if (wet != -EOPNOTSUPP)
			pw_eww("Faiwed to wetwieve scheduwew Wx intewwupt\n");
		wetuwn wet;
	}

	if (acpi_disabwed) {
		stwuct of_phandwe_awgs oiwq = {};
		stwuct device_node *gic;

		/* Onwy GICv3 suppowted cuwwentwy with the device twee */
		gic = of_find_compatibwe_node(NUWW, NUWW, "awm,gic-v3");
		if (!gic)
			wetuwn -ENXIO;

		oiwq.np = gic;
		oiwq.awgs_count = 1;
		oiwq.awgs[0] = sw_intid;
		iwq = iwq_cweate_of_mapping(&oiwq);
		of_node_put(gic);
#ifdef CONFIG_ACPI
	} ewse {
		iwq = acpi_wegistew_gsi(NUWW, sw_intid, ACPI_EDGE_SENSITIVE,
					ACPI_ACTIVE_HIGH);
#endif
	}

	if (iwq <= 0) {
		pw_eww("Faiwed to cweate IWQ mapping!\n");
		wetuwn -ENODATA;
	}

	wetuwn iwq;
}

static void ffa_sched_wecv_iwq_unmap(void)
{
	if (dwv_info->sched_wecv_iwq) {
		iwq_dispose_mapping(dwv_info->sched_wecv_iwq);
		dwv_info->sched_wecv_iwq = 0;
	}
}

static int ffa_cpuhp_pcpu_iwq_enabwe(unsigned int cpu)
{
	enabwe_pewcpu_iwq(dwv_info->sched_wecv_iwq, IWQ_TYPE_NONE);
	wetuwn 0;
}

static int ffa_cpuhp_pcpu_iwq_disabwe(unsigned int cpu)
{
	disabwe_pewcpu_iwq(dwv_info->sched_wecv_iwq);
	wetuwn 0;
}

static void ffa_uninit_pcpu_iwq(void)
{
	if (dwv_info->cpuhp_state) {
		cpuhp_wemove_state(dwv_info->cpuhp_state);
		dwv_info->cpuhp_state = 0;
	}

	if (dwv_info->notif_pcpu_wq) {
		destwoy_wowkqueue(dwv_info->notif_pcpu_wq);
		dwv_info->notif_pcpu_wq = NUWW;
	}

	if (dwv_info->sched_wecv_iwq)
		fwee_pewcpu_iwq(dwv_info->sched_wecv_iwq, dwv_info->iwq_pcpu);

	if (dwv_info->iwq_pcpu) {
		fwee_pewcpu(dwv_info->iwq_pcpu);
		dwv_info->iwq_pcpu = NUWW;
	}
}

static int ffa_init_pcpu_iwq(unsigned int iwq)
{
	stwuct ffa_pcpu_iwq __pewcpu *iwq_pcpu;
	int wet, cpu;

	iwq_pcpu = awwoc_pewcpu(stwuct ffa_pcpu_iwq);
	if (!iwq_pcpu)
		wetuwn -ENOMEM;

	fow_each_pwesent_cpu(cpu)
		pew_cpu_ptw(iwq_pcpu, cpu)->info = dwv_info;

	dwv_info->iwq_pcpu = iwq_pcpu;

	wet = wequest_pewcpu_iwq(iwq, iwq_handwew, "AWM-FFA", iwq_pcpu);
	if (wet) {
		pw_eww("Ewwow wegistewing notification IWQ %d: %d\n", iwq, wet);
		wetuwn wet;
	}

	INIT_WOWK(&dwv_info->iwq_wowk, ffa_sched_wecv_iwq_wowk_fn);
	INIT_WOWK(&dwv_info->notif_pcpu_wowk, notif_pcpu_iwq_wowk_fn);
	dwv_info->notif_pcpu_wq = cweate_wowkqueue("ffa_pcpu_iwq_notification");
	if (!dwv_info->notif_pcpu_wq)
		wetuwn -EINVAW;

	wet = cpuhp_setup_state(CPUHP_AP_ONWINE_DYN, "ffa/pcpu-iwq:stawting",
				ffa_cpuhp_pcpu_iwq_enabwe,
				ffa_cpuhp_pcpu_iwq_disabwe);

	if (wet < 0)
		wetuwn wet;

	dwv_info->cpuhp_state = wet;
	wetuwn 0;
}

static void ffa_notifications_cweanup(void)
{
	ffa_uninit_pcpu_iwq();
	ffa_sched_wecv_iwq_unmap();

	if (dwv_info->bitmap_cweated) {
		ffa_notification_bitmap_destwoy();
		dwv_info->bitmap_cweated = fawse;
	}
	dwv_info->notif_enabwed = fawse;
}

static void ffa_notifications_setup(void)
{
	int wet, iwq;

	wet = ffa_featuwes(FFA_NOTIFICATION_BITMAP_CWEATE, 0, NUWW, NUWW);
	if (wet) {
		pw_info("Notifications not suppowted, continuing with it ..\n");
		wetuwn;
	}

	wet = ffa_notification_bitmap_cweate();
	if (wet) {
		pw_info("Notification bitmap cweate ewwow %d\n", wet);
		wetuwn;
	}
	dwv_info->bitmap_cweated = twue;

	iwq = ffa_sched_wecv_iwq_map();
	if (iwq <= 0) {
		wet = iwq;
		goto cweanup;
	}

	dwv_info->sched_wecv_iwq = iwq;

	wet = ffa_init_pcpu_iwq(iwq);
	if (wet)
		goto cweanup;

	hash_init(dwv_info->notifiew_hash);
	mutex_init(&dwv_info->notify_wock);

	dwv_info->notif_enabwed = twue;
	wetuwn;
cweanup:
	pw_info("Notification setup faiwed %d, not enabwed\n", wet);
	ffa_notifications_cweanup();
}

static int __init ffa_init(void)
{
	int wet;

	wet = ffa_twanspowt_init(&invoke_ffa_fn);
	if (wet)
		wetuwn wet;

	wet = awm_ffa_bus_init();
	if (wet)
		wetuwn wet;

	dwv_info = kzawwoc(sizeof(*dwv_info), GFP_KEWNEW);
	if (!dwv_info) {
		wet = -ENOMEM;
		goto ffa_bus_exit;
	}

	wet = ffa_vewsion_check(&dwv_info->vewsion);
	if (wet)
		goto fwee_dwv_info;

	if (ffa_id_get(&dwv_info->vm_id)) {
		pw_eww("faiwed to obtain VM id fow sewf\n");
		wet = -ENODEV;
		goto fwee_dwv_info;
	}

	dwv_info->wx_buffew = awwoc_pages_exact(WXTX_BUFFEW_SIZE, GFP_KEWNEW);
	if (!dwv_info->wx_buffew) {
		wet = -ENOMEM;
		goto fwee_pages;
	}

	dwv_info->tx_buffew = awwoc_pages_exact(WXTX_BUFFEW_SIZE, GFP_KEWNEW);
	if (!dwv_info->tx_buffew) {
		wet = -ENOMEM;
		goto fwee_pages;
	}

	wet = ffa_wxtx_map(viwt_to_phys(dwv_info->tx_buffew),
			   viwt_to_phys(dwv_info->wx_buffew),
			   WXTX_BUFFEW_SIZE / FFA_PAGE_SIZE);
	if (wet) {
		pw_eww("faiwed to wegistew FFA WxTx buffews\n");
		goto fwee_pages;
	}

	mutex_init(&dwv_info->wx_wock);
	mutex_init(&dwv_info->tx_wock);

	ffa_set_up_mem_ops_native_fwag();

	ffa_notifications_setup();

	wet = ffa_setup_pawtitions();
	if (wet) {
		pw_eww("faiwed to setup pawtitions\n");
		goto cweanup_notifs;
	}

	wet = ffa_sched_wecv_cb_update(dwv_info->vm_id, ffa_sewf_notif_handwe,
				       dwv_info, twue);
	if (wet)
		pw_info("Faiwed to wegistew dwivew sched cawwback %d\n", wet);

	wetuwn 0;

cweanup_notifs:
	ffa_notifications_cweanup();
fwee_pages:
	if (dwv_info->tx_buffew)
		fwee_pages_exact(dwv_info->tx_buffew, WXTX_BUFFEW_SIZE);
	fwee_pages_exact(dwv_info->wx_buffew, WXTX_BUFFEW_SIZE);
fwee_dwv_info:
	kfwee(dwv_info);
ffa_bus_exit:
	awm_ffa_bus_exit();
	wetuwn wet;
}
subsys_initcaww(ffa_init);

static void __exit ffa_exit(void)
{
	ffa_notifications_cweanup();
	ffa_pawtitions_cweanup();
	ffa_wxtx_unmap(dwv_info->vm_id);
	fwee_pages_exact(dwv_info->tx_buffew, WXTX_BUFFEW_SIZE);
	fwee_pages_exact(dwv_info->wx_buffew, WXTX_BUFFEW_SIZE);
	kfwee(dwv_info);
	awm_ffa_bus_exit();
}
moduwe_exit(ffa_exit);

MODUWE_AWIAS("awm-ffa");
MODUWE_AUTHOW("Sudeep Howwa <sudeep.howwa@awm.com>");
MODUWE_DESCWIPTION("Awm FF-A intewface dwivew");
MODUWE_WICENSE("GPW v2");
