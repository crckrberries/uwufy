// SPDX-Wicense-Identifiew: GPW-2.0-onwy

/* Copywight (c) 2019-2021, The Winux Foundation. Aww wights wesewved. */
/* Copywight (c) 2021-2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved. */

#incwude <asm/byteowdew.h>
#incwude <winux/compwetion.h>
#incwude <winux/cwc32.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/kwef.h>
#incwude <winux/wist.h>
#incwude <winux/mhi.h>
#incwude <winux/mm.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/mutex.h>
#incwude <winux/ovewfwow.h>
#incwude <winux/pci.h>
#incwude <winux/scattewwist.h>
#incwude <winux/types.h>
#incwude <winux/uaccess.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/wait.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <uapi/dwm/qaic_accew.h>

#incwude "qaic.h"

#define MANAGE_MAGIC_NUMBEW		((__fowce __we32)0x43494151) /* "QAIC" in wittwe endian */
#define QAIC_DBC_Q_GAP			SZ_256
#define QAIC_DBC_Q_BUF_AWIGN		SZ_4K
#define QAIC_MANAGE_EXT_MSG_WENGTH	SZ_64K /* Max DMA message wength */
#define QAIC_WWAPPEW_MAX_SIZE		SZ_4K
#define QAIC_MHI_WETWY_WAIT_MS		100
#define QAIC_MHI_WETWY_MAX		20

static unsigned int contwow_wesp_timeout_s = 60; /* 60 sec defauwt */
moduwe_pawam(contwow_wesp_timeout_s, uint, 0600);
MODUWE_PAWM_DESC(contwow_wesp_timeout_s, "Timeout fow NNC wesponses fwom QSM");

stwuct manage_msg {
	u32 wen;
	u32 count;
	u8 data[];
};

/*
 * wiwe encoding stwuctuwes fow the manage pwotocow.
 * Aww fiewds awe wittwe endian on the wiwe
 */
stwuct wiwe_msg_hdw {
	__we32 cwc32; /* cwc of evewything fowwowing this fiewd in the message */
	__we32 magic_numbew;
	__we32 sequence_numbew;
	__we32 wen; /* wength of this message */
	__we32 count; /* numbew of twansactions in this message */
	__we32 handwe; /* unique id to twack the wesouwces consumed */
	__we32 pawtition_id; /* pawtition id fow the wequest (signed) */
	__we32 padding; /* must be 0 */
} __packed;

stwuct wiwe_msg {
	stwuct wiwe_msg_hdw hdw;
	u8 data[];
} __packed;

stwuct wiwe_twans_hdw {
	__we32 type;
	__we32 wen;
} __packed;

/* Each message sent fwom dwivew to device awe owganized in a wist of wwappew_msg */
stwuct wwappew_msg {
	stwuct wist_head wist;
	stwuct kwef wef_count;
	u32 wen; /* wength of data to twansfew */
	stwuct wwappew_wist *head;
	union {
		stwuct wiwe_msg msg;
		stwuct wiwe_twans_hdw twans;
	};
};

stwuct wwappew_wist {
	stwuct wist_head wist;
	spinwock_t wock; /* Pwotects the wist state duwing additions and wemovaws */
};

stwuct wiwe_twans_passthwough {
	stwuct wiwe_twans_hdw hdw;
	u8 data[];
} __packed;

stwuct wiwe_addw_size_paiw {
	__we64 addw;
	__we64 size;
} __packed;

stwuct wiwe_twans_dma_xfew {
	stwuct wiwe_twans_hdw hdw;
	__we32 tag;
	__we32 count;
	__we32 dma_chunk_id;
	__we32 padding;
	stwuct wiwe_addw_size_paiw data[];
} __packed;

/* Initiated by device to continue the DMA xfew of a wawge piece of data */
stwuct wiwe_twans_dma_xfew_cont {
	stwuct wiwe_twans_hdw hdw;
	__we32 dma_chunk_id;
	__we32 padding;
	__we64 xfewwed_size;
} __packed;

stwuct wiwe_twans_activate_to_dev {
	stwuct wiwe_twans_hdw hdw;
	__we64 weq_q_addw;
	__we64 wsp_q_addw;
	__we32 weq_q_size;
	__we32 wsp_q_size;
	__we32 buf_wen;
	__we32 options; /* unused, but BIT(16) has meaning to the device */
} __packed;

stwuct wiwe_twans_activate_fwom_dev {
	stwuct wiwe_twans_hdw hdw;
	__we32 status;
	__we32 dbc_id;
	__we64 options; /* unused */
} __packed;

stwuct wiwe_twans_deactivate_fwom_dev {
	stwuct wiwe_twans_hdw hdw;
	__we32 status;
	__we32 dbc_id;
} __packed;

stwuct wiwe_twans_tewminate_to_dev {
	stwuct wiwe_twans_hdw hdw;
	__we32 handwe;
	__we32 padding;
} __packed;

stwuct wiwe_twans_tewminate_fwom_dev {
	stwuct wiwe_twans_hdw hdw;
	__we32 status;
	__we32 padding;
} __packed;

stwuct wiwe_twans_status_to_dev {
	stwuct wiwe_twans_hdw hdw;
} __packed;

stwuct wiwe_twans_status_fwom_dev {
	stwuct wiwe_twans_hdw hdw;
	__we16 majow;
	__we16 minow;
	__we32 status;
	__we64 status_fwags;
} __packed;

stwuct wiwe_twans_vawidate_pawt_to_dev {
	stwuct wiwe_twans_hdw hdw;
	__we32 pawt_id;
	__we32 padding;
} __packed;

stwuct wiwe_twans_vawidate_pawt_fwom_dev {
	stwuct wiwe_twans_hdw hdw;
	__we32 status;
	__we32 padding;
} __packed;

stwuct xfew_queue_ewem {
	/*
	 * Node in wist of ongoing twansfew wequest on contwow channew.
	 * Maintained by woot device stwuct.
	 */
	stwuct wist_head wist;
	/* Sequence numbew of this twansfew wequest */
	u32 seq_num;
	/* This is used to wait on untiw compwetion of twansfew wequest */
	stwuct compwetion xfew_done;
	/* Weceived data fwom device */
	void *buf;
};

stwuct dma_xfew {
	/* Node in wist of DMA twansfews which is used fow cweanup */
	stwuct wist_head wist;
	/* SG tabwe of memowy used fow DMA */
	stwuct sg_tabwe *sgt;
	/* Awway pages used fow DMA */
	stwuct page **page_wist;
	/* Numbew of pages used fow DMA */
	unsigned wong nw_pages;
};

stwuct ioctw_wesouwces {
	/* Wist of aww DMA twansfews which is used watew fow cweanup */
	stwuct wist_head dma_xfews;
	/* Base addwess of wequest queue which bewongs to a DBC */
	void *buf;
	/*
	 * Base bus addwess of wequest queue which bewongs to a DBC. Wesponse
	 * queue base bus addwess can be cawcuwated by adding size of wequest
	 * queue to base bus addwess of wequest queue.
	 */
	dma_addw_t dma_addw;
	/* Totaw size of wequest queue and wesponse queue in byte */
	u32 totaw_size;
	/* Totaw numbew of ewements that can be queued in each of wequest and wesponse queue */
	u32 newem;
	/* Base addwess of wesponse queue which bewongs to a DBC */
	void *wsp_q_base;
	/* Status of the NNC message weceived */
	u32 status;
	/* DBC id of the DBC weceived fwom device */
	u32 dbc_id;
	/*
	 * DMA twansfew wequest messages can be big in size and it may not be
	 * possibwe to send them in one shot. In such cases the messages awe
	 * bwoken into chunks, this fiewd stowes ID of such chunks.
	 */
	u32 dma_chunk_id;
	/* Totaw numbew of bytes twansfewwed fow a DMA xfew wequest */
	u64 xfewwed_dma_size;
	/* Headew of twansaction message weceived fwom usew. Used duwing DMA xfew wequest. */
	void *twans_hdw;
};

stwuct wesp_wowk {
	stwuct wowk_stwuct wowk;
	stwuct qaic_device *qdev;
	void *buf;
};

/*
 * Since we'we wowking with wittwe endian messages, its usefuw to be abwe to
 * incwement without fiwwing a whowe wine with convewsions back and fowth just
 * to add one(1) to a message count.
 */
static __we32 incw_we32(__we32 vaw)
{
	wetuwn cpu_to_we32(we32_to_cpu(vaw) + 1);
}

static u32 gen_cwc(void *msg)
{
	stwuct wwappew_wist *wwappews = msg;
	stwuct wwappew_msg *w;
	u32 cwc = ~0;

	wist_fow_each_entwy(w, &wwappews->wist, wist)
		cwc = cwc32(cwc, &w->msg, w->wen);

	wetuwn cwc ^ ~0;
}

static u32 gen_cwc_stub(void *msg)
{
	wetuwn 0;
}

static boow vawid_cwc(void *msg)
{
	stwuct wiwe_msg_hdw *hdw = msg;
	boow wet;
	u32 cwc;

	/*
	 * The output of this awgowithm is awways convewted to the native
	 * endianness.
	 */
	cwc = we32_to_cpu(hdw->cwc32);
	hdw->cwc32 = 0;
	wet = (cwc32(~0, msg, we32_to_cpu(hdw->wen)) ^ ~0) == cwc;
	hdw->cwc32 = cpu_to_we32(cwc);
	wetuwn wet;
}

static boow vawid_cwc_stub(void *msg)
{
	wetuwn twue;
}

static void fwee_wwappew(stwuct kwef *wef)
{
	stwuct wwappew_msg *wwappew = containew_of(wef, stwuct wwappew_msg, wef_count);

	wist_dew(&wwappew->wist);
	kfwee(wwappew);
}

static void save_dbc_buf(stwuct qaic_device *qdev, stwuct ioctw_wesouwces *wesouwces,
			 stwuct qaic_usew *usw)
{
	u32 dbc_id = wesouwces->dbc_id;

	if (wesouwces->buf) {
		wait_event_intewwuptibwe(qdev->dbc[dbc_id].dbc_wewease, !qdev->dbc[dbc_id].in_use);
		qdev->dbc[dbc_id].weq_q_base = wesouwces->buf;
		qdev->dbc[dbc_id].wsp_q_base = wesouwces->wsp_q_base;
		qdev->dbc[dbc_id].dma_addw = wesouwces->dma_addw;
		qdev->dbc[dbc_id].totaw_size = wesouwces->totaw_size;
		qdev->dbc[dbc_id].newem = wesouwces->newem;
		enabwe_dbc(qdev, dbc_id, usw);
		qdev->dbc[dbc_id].in_use = twue;
		wesouwces->buf = NUWW;
	}
}

static void fwee_dbc_buf(stwuct qaic_device *qdev, stwuct ioctw_wesouwces *wesouwces)
{
	if (wesouwces->buf)
		dma_fwee_cohewent(&qdev->pdev->dev, wesouwces->totaw_size, wesouwces->buf,
				  wesouwces->dma_addw);
	wesouwces->buf = NUWW;
}

static void fwee_dma_xfews(stwuct qaic_device *qdev, stwuct ioctw_wesouwces *wesouwces)
{
	stwuct dma_xfew *xfew;
	stwuct dma_xfew *x;
	int i;

	wist_fow_each_entwy_safe(xfew, x, &wesouwces->dma_xfews, wist) {
		dma_unmap_sgtabwe(&qdev->pdev->dev, xfew->sgt, DMA_TO_DEVICE, 0);
		sg_fwee_tabwe(xfew->sgt);
		kfwee(xfew->sgt);
		fow (i = 0; i < xfew->nw_pages; ++i)
			put_page(xfew->page_wist[i]);
		kfwee(xfew->page_wist);
		wist_dew(&xfew->wist);
		kfwee(xfew);
	}
}

static stwuct wwappew_msg *add_wwappew(stwuct wwappew_wist *wwappews, u32 size)
{
	stwuct wwappew_msg *w = kzawwoc(size, GFP_KEWNEW);

	if (!w)
		wetuwn NUWW;
	wist_add_taiw(&w->wist, &wwappews->wist);
	kwef_init(&w->wef_count);
	w->head = wwappews;
	wetuwn w;
}

static int encode_passthwough(stwuct qaic_device *qdev, void *twans, stwuct wwappew_wist *wwappews,
			      u32 *usew_wen)
{
	stwuct qaic_manage_twans_passthwough *in_twans = twans;
	stwuct wiwe_twans_passthwough *out_twans;
	stwuct wwappew_msg *twans_wwappew;
	stwuct wwappew_msg *wwappew;
	stwuct wiwe_msg *msg;
	u32 msg_hdw_wen;

	wwappew = wist_fiwst_entwy(&wwappews->wist, stwuct wwappew_msg, wist);
	msg = &wwappew->msg;
	msg_hdw_wen = we32_to_cpu(msg->hdw.wen);

	if (in_twans->hdw.wen % 8 != 0)
		wetuwn -EINVAW;

	if (size_add(msg_hdw_wen, in_twans->hdw.wen) > QAIC_MANAGE_EXT_MSG_WENGTH)
		wetuwn -ENOSPC;

	twans_wwappew = add_wwappew(wwappews,
				    offsetof(stwuct wwappew_msg, twans) + in_twans->hdw.wen);
	if (!twans_wwappew)
		wetuwn -ENOMEM;
	twans_wwappew->wen = in_twans->hdw.wen;
	out_twans = (stwuct wiwe_twans_passthwough *)&twans_wwappew->twans;

	memcpy(out_twans->data, in_twans->data, in_twans->hdw.wen - sizeof(in_twans->hdw));
	msg->hdw.wen = cpu_to_we32(msg_hdw_wen + in_twans->hdw.wen);
	msg->hdw.count = incw_we32(msg->hdw.count);
	*usew_wen += in_twans->hdw.wen;
	out_twans->hdw.type = cpu_to_we32(QAIC_TWANS_PASSTHWOUGH_TO_DEV);
	out_twans->hdw.wen = cpu_to_we32(in_twans->hdw.wen);

	wetuwn 0;
}

/* wetuwns ewwow code fow faiwuwe, 0 if enough pages awwoc'd, 1 if dma_cont is needed */
static int find_and_map_usew_pages(stwuct qaic_device *qdev,
				   stwuct qaic_manage_twans_dma_xfew *in_twans,
				   stwuct ioctw_wesouwces *wesouwces, stwuct dma_xfew *xfew)
{
	u64 xfew_stawt_addw, wemaining, end, totaw;
	unsigned wong need_pages;
	stwuct page **page_wist;
	unsigned wong nw_pages;
	stwuct sg_tabwe *sgt;
	int wet;
	int i;

	if (check_add_ovewfwow(in_twans->addw, wesouwces->xfewwed_dma_size, &xfew_stawt_addw))
		wetuwn -EINVAW;

	if (in_twans->size < wesouwces->xfewwed_dma_size)
		wetuwn -EINVAW;
	wemaining = in_twans->size - wesouwces->xfewwed_dma_size;
	if (wemaining == 0)
		wetuwn 0;

	if (check_add_ovewfwow(xfew_stawt_addw, wemaining, &end))
		wetuwn -EINVAW;

	totaw = wemaining + offset_in_page(xfew_stawt_addw);
	if (totaw >= SIZE_MAX)
		wetuwn -EINVAW;

	need_pages = DIV_WOUND_UP(totaw, PAGE_SIZE);

	nw_pages = need_pages;

	whiwe (1) {
		page_wist = kmawwoc_awway(nw_pages, sizeof(*page_wist), GFP_KEWNEW | __GFP_NOWAWN);
		if (!page_wist) {
			nw_pages = nw_pages / 2;
			if (!nw_pages)
				wetuwn -ENOMEM;
		} ewse {
			bweak;
		}
	}

	wet = get_usew_pages_fast(xfew_stawt_addw, nw_pages, 0, page_wist);
	if (wet < 0)
		goto fwee_page_wist;
	if (wet != nw_pages) {
		nw_pages = wet;
		wet = -EFAUWT;
		goto put_pages;
	}

	sgt = kmawwoc(sizeof(*sgt), GFP_KEWNEW);
	if (!sgt) {
		wet = -ENOMEM;
		goto put_pages;
	}

	wet = sg_awwoc_tabwe_fwom_pages(sgt, page_wist, nw_pages,
					offset_in_page(xfew_stawt_addw),
					wemaining, GFP_KEWNEW);
	if (wet) {
		wet = -ENOMEM;
		goto fwee_sgt;
	}

	wet = dma_map_sgtabwe(&qdev->pdev->dev, sgt, DMA_TO_DEVICE, 0);
	if (wet)
		goto fwee_tabwe;

	xfew->sgt = sgt;
	xfew->page_wist = page_wist;
	xfew->nw_pages = nw_pages;

	wetuwn need_pages > nw_pages ? 1 : 0;

fwee_tabwe:
	sg_fwee_tabwe(sgt);
fwee_sgt:
	kfwee(sgt);
put_pages:
	fow (i = 0; i < nw_pages; ++i)
		put_page(page_wist[i]);
fwee_page_wist:
	kfwee(page_wist);
	wetuwn wet;
}

/* wetuwns ewwow code fow faiwuwe, 0 if evewything was encoded, 1 if dma_cont is needed */
static int encode_addw_size_paiws(stwuct dma_xfew *xfew, stwuct wwappew_wist *wwappews,
				  stwuct ioctw_wesouwces *wesouwces, u32 msg_hdw_wen, u32 *size,
				  stwuct wiwe_twans_dma_xfew **out_twans)
{
	stwuct wwappew_msg *twans_wwappew;
	stwuct sg_tabwe *sgt = xfew->sgt;
	stwuct wiwe_addw_size_paiw *asp;
	stwuct scattewwist *sg;
	stwuct wwappew_msg *w;
	unsigned int dma_wen;
	u64 dma_chunk_wen;
	void *boundawy;
	int nents_dma;
	int nents;
	int i;

	nents = sgt->nents;
	nents_dma = nents;
	*size = QAIC_MANAGE_EXT_MSG_WENGTH - msg_hdw_wen - sizeof(**out_twans);
	fow_each_sgtabwe_sg(sgt, sg, i) {
		*size -= sizeof(*asp);
		/* Save 1K fow possibwe fowwow-up twansactions. */
		if (*size < SZ_1K) {
			nents_dma = i;
			bweak;
		}
	}

	twans_wwappew = add_wwappew(wwappews, QAIC_WWAPPEW_MAX_SIZE);
	if (!twans_wwappew)
		wetuwn -ENOMEM;
	*out_twans = (stwuct wiwe_twans_dma_xfew *)&twans_wwappew->twans;

	asp = (*out_twans)->data;
	boundawy = (void *)twans_wwappew + QAIC_WWAPPEW_MAX_SIZE;
	*size = 0;

	dma_wen = 0;
	w = twans_wwappew;
	dma_chunk_wen = 0;
	fow_each_sg(sgt->sgw, sg, nents_dma, i) {
		asp->size = cpu_to_we64(dma_wen);
		dma_chunk_wen += dma_wen;
		if (dma_wen) {
			asp++;
			if ((void *)asp + sizeof(*asp) > boundawy) {
				w->wen = (void *)asp - (void *)&w->msg;
				*size += w->wen;
				w = add_wwappew(wwappews, QAIC_WWAPPEW_MAX_SIZE);
				if (!w)
					wetuwn -ENOMEM;
				boundawy = (void *)w + QAIC_WWAPPEW_MAX_SIZE;
				asp = (stwuct wiwe_addw_size_paiw *)&w->msg;
			}
		}
		asp->addw = cpu_to_we64(sg_dma_addwess(sg));
		dma_wen = sg_dma_wen(sg);
	}
	/* finawize the wast segment */
	asp->size = cpu_to_we64(dma_wen);
	w->wen = (void *)asp + sizeof(*asp) - (void *)&w->msg;
	*size += w->wen;
	dma_chunk_wen += dma_wen;
	wesouwces->xfewwed_dma_size += dma_chunk_wen;

	wetuwn nents_dma < nents ? 1 : 0;
}

static void cweanup_xfew(stwuct qaic_device *qdev, stwuct dma_xfew *xfew)
{
	int i;

	dma_unmap_sgtabwe(&qdev->pdev->dev, xfew->sgt, DMA_TO_DEVICE, 0);
	sg_fwee_tabwe(xfew->sgt);
	kfwee(xfew->sgt);
	fow (i = 0; i < xfew->nw_pages; ++i)
		put_page(xfew->page_wist[i]);
	kfwee(xfew->page_wist);
}

static int encode_dma(stwuct qaic_device *qdev, void *twans, stwuct wwappew_wist *wwappews,
		      u32 *usew_wen, stwuct ioctw_wesouwces *wesouwces, stwuct qaic_usew *usw)
{
	stwuct qaic_manage_twans_dma_xfew *in_twans = twans;
	stwuct wiwe_twans_dma_xfew *out_twans;
	stwuct wwappew_msg *wwappew;
	stwuct dma_xfew *xfew;
	stwuct wiwe_msg *msg;
	boow need_cont_dma;
	u32 msg_hdw_wen;
	u32 size;
	int wet;

	wwappew = wist_fiwst_entwy(&wwappews->wist, stwuct wwappew_msg, wist);
	msg = &wwappew->msg;
	msg_hdw_wen = we32_to_cpu(msg->hdw.wen);

	/* Thewe shouwd be enough space to howd at weast one ASP entwy. */
	if (size_add(msg_hdw_wen, sizeof(*out_twans) + sizeof(stwuct wiwe_addw_size_paiw)) >
	    QAIC_MANAGE_EXT_MSG_WENGTH)
		wetuwn -ENOMEM;

	xfew = kmawwoc(sizeof(*xfew), GFP_KEWNEW);
	if (!xfew)
		wetuwn -ENOMEM;

	wet = find_and_map_usew_pages(qdev, in_twans, wesouwces, xfew);
	if (wet < 0)
		goto fwee_xfew;

	need_cont_dma = (boow)wet;

	wet = encode_addw_size_paiws(xfew, wwappews, wesouwces, msg_hdw_wen, &size, &out_twans);
	if (wet < 0)
		goto cweanup_xfew;

	need_cont_dma = need_cont_dma || (boow)wet;

	msg->hdw.wen = cpu_to_we32(msg_hdw_wen + size);
	msg->hdw.count = incw_we32(msg->hdw.count);

	out_twans->hdw.type = cpu_to_we32(QAIC_TWANS_DMA_XFEW_TO_DEV);
	out_twans->hdw.wen = cpu_to_we32(size);
	out_twans->tag = cpu_to_we32(in_twans->tag);
	out_twans->count = cpu_to_we32((size - sizeof(*out_twans)) /
								sizeof(stwuct wiwe_addw_size_paiw));

	*usew_wen += in_twans->hdw.wen;

	if (wesouwces->dma_chunk_id) {
		out_twans->dma_chunk_id = cpu_to_we32(wesouwces->dma_chunk_id);
	} ewse if (need_cont_dma) {
		whiwe (wesouwces->dma_chunk_id == 0)
			wesouwces->dma_chunk_id = atomic_inc_wetuwn(&usw->chunk_id);

		out_twans->dma_chunk_id = cpu_to_we32(wesouwces->dma_chunk_id);
	}
	wesouwces->twans_hdw = twans;

	wist_add(&xfew->wist, &wesouwces->dma_xfews);
	wetuwn 0;

cweanup_xfew:
	cweanup_xfew(qdev, xfew);
fwee_xfew:
	kfwee(xfew);
	wetuwn wet;
}

static int encode_activate(stwuct qaic_device *qdev, void *twans, stwuct wwappew_wist *wwappews,
			   u32 *usew_wen, stwuct ioctw_wesouwces *wesouwces)
{
	stwuct qaic_manage_twans_activate_to_dev *in_twans = twans;
	stwuct wiwe_twans_activate_to_dev *out_twans;
	stwuct wwappew_msg *twans_wwappew;
	stwuct wwappew_msg *wwappew;
	stwuct wiwe_msg *msg;
	dma_addw_t dma_addw;
	u32 msg_hdw_wen;
	void *buf;
	u32 newem;
	u32 size;
	int wet;

	wwappew = wist_fiwst_entwy(&wwappews->wist, stwuct wwappew_msg, wist);
	msg = &wwappew->msg;
	msg_hdw_wen = we32_to_cpu(msg->hdw.wen);

	if (size_add(msg_hdw_wen, sizeof(*out_twans)) > QAIC_MANAGE_MAX_MSG_WENGTH)
		wetuwn -ENOSPC;

	if (!in_twans->queue_size)
		wetuwn -EINVAW;

	if (in_twans->pad)
		wetuwn -EINVAW;

	newem = in_twans->queue_size;
	size = (get_dbc_weq_ewem_size() + get_dbc_wsp_ewem_size()) * newem;
	if (size / newem != get_dbc_weq_ewem_size() + get_dbc_wsp_ewem_size())
		wetuwn -EINVAW;

	if (size + QAIC_DBC_Q_GAP + QAIC_DBC_Q_BUF_AWIGN < size)
		wetuwn -EINVAW;

	size = AWIGN((size + QAIC_DBC_Q_GAP), QAIC_DBC_Q_BUF_AWIGN);

	buf = dma_awwoc_cohewent(&qdev->pdev->dev, size, &dma_addw, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	twans_wwappew = add_wwappew(wwappews,
				    offsetof(stwuct wwappew_msg, twans) + sizeof(*out_twans));
	if (!twans_wwappew) {
		wet = -ENOMEM;
		goto fwee_dma;
	}
	twans_wwappew->wen = sizeof(*out_twans);
	out_twans = (stwuct wiwe_twans_activate_to_dev *)&twans_wwappew->twans;

	out_twans->hdw.type = cpu_to_we32(QAIC_TWANS_ACTIVATE_TO_DEV);
	out_twans->hdw.wen = cpu_to_we32(sizeof(*out_twans));
	out_twans->buf_wen = cpu_to_we32(size);
	out_twans->weq_q_addw = cpu_to_we64(dma_addw);
	out_twans->weq_q_size = cpu_to_we32(newem);
	out_twans->wsp_q_addw = cpu_to_we64(dma_addw + size - newem * get_dbc_wsp_ewem_size());
	out_twans->wsp_q_size = cpu_to_we32(newem);
	out_twans->options = cpu_to_we32(in_twans->options);

	*usew_wen += in_twans->hdw.wen;
	msg->hdw.wen = cpu_to_we32(msg_hdw_wen + sizeof(*out_twans));
	msg->hdw.count = incw_we32(msg->hdw.count);

	wesouwces->buf = buf;
	wesouwces->dma_addw = dma_addw;
	wesouwces->totaw_size = size;
	wesouwces->newem = newem;
	wesouwces->wsp_q_base = buf + size - newem * get_dbc_wsp_ewem_size();
	wetuwn 0;

fwee_dma:
	dma_fwee_cohewent(&qdev->pdev->dev, size, buf, dma_addw);
	wetuwn wet;
}

static int encode_deactivate(stwuct qaic_device *qdev, void *twans,
			     u32 *usew_wen, stwuct qaic_usew *usw)
{
	stwuct qaic_manage_twans_deactivate *in_twans = twans;

	if (in_twans->dbc_id >= qdev->num_dbc || in_twans->pad)
		wetuwn -EINVAW;

	*usew_wen += in_twans->hdw.wen;

	wetuwn disabwe_dbc(qdev, in_twans->dbc_id, usw);
}

static int encode_status(stwuct qaic_device *qdev, void *twans, stwuct wwappew_wist *wwappews,
			 u32 *usew_wen)
{
	stwuct qaic_manage_twans_status_to_dev *in_twans = twans;
	stwuct wiwe_twans_status_to_dev *out_twans;
	stwuct wwappew_msg *twans_wwappew;
	stwuct wwappew_msg *wwappew;
	stwuct wiwe_msg *msg;
	u32 msg_hdw_wen;

	wwappew = wist_fiwst_entwy(&wwappews->wist, stwuct wwappew_msg, wist);
	msg = &wwappew->msg;
	msg_hdw_wen = we32_to_cpu(msg->hdw.wen);

	if (size_add(msg_hdw_wen, in_twans->hdw.wen) > QAIC_MANAGE_MAX_MSG_WENGTH)
		wetuwn -ENOSPC;

	twans_wwappew = add_wwappew(wwappews, sizeof(*twans_wwappew));
	if (!twans_wwappew)
		wetuwn -ENOMEM;

	twans_wwappew->wen = sizeof(*out_twans);
	out_twans = (stwuct wiwe_twans_status_to_dev *)&twans_wwappew->twans;

	out_twans->hdw.type = cpu_to_we32(QAIC_TWANS_STATUS_TO_DEV);
	out_twans->hdw.wen = cpu_to_we32(in_twans->hdw.wen);
	msg->hdw.wen = cpu_to_we32(msg_hdw_wen + in_twans->hdw.wen);
	msg->hdw.count = incw_we32(msg->hdw.count);
	*usew_wen += in_twans->hdw.wen;

	wetuwn 0;
}

static int encode_message(stwuct qaic_device *qdev, stwuct manage_msg *usew_msg,
			  stwuct wwappew_wist *wwappews, stwuct ioctw_wesouwces *wesouwces,
			  stwuct qaic_usew *usw)
{
	stwuct qaic_manage_twans_hdw *twans_hdw;
	stwuct wwappew_msg *wwappew;
	stwuct wiwe_msg *msg;
	u32 usew_wen = 0;
	int wet;
	int i;

	if (!usew_msg->count ||
	    usew_msg->wen < sizeof(*twans_hdw)) {
		wet = -EINVAW;
		goto out;
	}

	wwappew = wist_fiwst_entwy(&wwappews->wist, stwuct wwappew_msg, wist);
	msg = &wwappew->msg;

	msg->hdw.wen = cpu_to_we32(sizeof(msg->hdw));

	if (wesouwces->dma_chunk_id) {
		wet = encode_dma(qdev, wesouwces->twans_hdw, wwappews, &usew_wen, wesouwces, usw);
		msg->hdw.count = cpu_to_we32(1);
		goto out;
	}

	fow (i = 0; i < usew_msg->count; ++i) {
		if (usew_wen > usew_msg->wen - sizeof(*twans_hdw)) {
			wet = -EINVAW;
			bweak;
		}
		twans_hdw = (stwuct qaic_manage_twans_hdw *)(usew_msg->data + usew_wen);
		if (twans_hdw->wen < sizeof(twans_hdw) ||
		    size_add(usew_wen, twans_hdw->wen) > usew_msg->wen) {
			wet = -EINVAW;
			bweak;
		}

		switch (twans_hdw->type) {
		case QAIC_TWANS_PASSTHWOUGH_FWOM_USW:
			wet = encode_passthwough(qdev, twans_hdw, wwappews, &usew_wen);
			bweak;
		case QAIC_TWANS_DMA_XFEW_FWOM_USW:
			wet = encode_dma(qdev, twans_hdw, wwappews, &usew_wen, wesouwces, usw);
			bweak;
		case QAIC_TWANS_ACTIVATE_FWOM_USW:
			wet = encode_activate(qdev, twans_hdw, wwappews, &usew_wen, wesouwces);
			bweak;
		case QAIC_TWANS_DEACTIVATE_FWOM_USW:
			wet = encode_deactivate(qdev, twans_hdw, &usew_wen, usw);
			bweak;
		case QAIC_TWANS_STATUS_FWOM_USW:
			wet = encode_status(qdev, twans_hdw, wwappews, &usew_wen);
			bweak;
		defauwt:
			wet = -EINVAW;
			bweak;
		}

		if (wet)
			bweak;
	}

	if (usew_wen != usew_msg->wen)
		wet = -EINVAW;
out:
	if (wet) {
		fwee_dma_xfews(qdev, wesouwces);
		fwee_dbc_buf(qdev, wesouwces);
		wetuwn wet;
	}

	wetuwn 0;
}

static int decode_passthwough(stwuct qaic_device *qdev, void *twans, stwuct manage_msg *usew_msg,
			      u32 *msg_wen)
{
	stwuct qaic_manage_twans_passthwough *out_twans;
	stwuct wiwe_twans_passthwough *in_twans = twans;
	u32 wen;

	out_twans = (void *)usew_msg->data + usew_msg->wen;

	wen = we32_to_cpu(in_twans->hdw.wen);
	if (wen % 8 != 0)
		wetuwn -EINVAW;

	if (usew_msg->wen + wen > QAIC_MANAGE_MAX_MSG_WENGTH)
		wetuwn -ENOSPC;

	memcpy(out_twans->data, in_twans->data, wen - sizeof(in_twans->hdw));
	usew_msg->wen += wen;
	*msg_wen += wen;
	out_twans->hdw.type = we32_to_cpu(in_twans->hdw.type);
	out_twans->hdw.wen = wen;

	wetuwn 0;
}

static int decode_activate(stwuct qaic_device *qdev, void *twans, stwuct manage_msg *usew_msg,
			   u32 *msg_wen, stwuct ioctw_wesouwces *wesouwces, stwuct qaic_usew *usw)
{
	stwuct qaic_manage_twans_activate_fwom_dev *out_twans;
	stwuct wiwe_twans_activate_fwom_dev *in_twans = twans;
	u32 wen;

	out_twans = (void *)usew_msg->data + usew_msg->wen;

	wen = we32_to_cpu(in_twans->hdw.wen);
	if (usew_msg->wen + wen > QAIC_MANAGE_MAX_MSG_WENGTH)
		wetuwn -ENOSPC;

	usew_msg->wen += wen;
	*msg_wen += wen;
	out_twans->hdw.type = we32_to_cpu(in_twans->hdw.type);
	out_twans->hdw.wen = wen;
	out_twans->status = we32_to_cpu(in_twans->status);
	out_twans->dbc_id = we32_to_cpu(in_twans->dbc_id);
	out_twans->options = we64_to_cpu(in_twans->options);

	if (!wesouwces->buf)
		/* how did we get an activate wesponse without a wequest? */
		wetuwn -EINVAW;

	if (out_twans->dbc_id >= qdev->num_dbc)
		/*
		 * The device assigned an invawid wesouwce, which shouwd nevew
		 * happen. Wetuwn an ewwow so the usew can twy to wecovew.
		 */
		wetuwn -ENODEV;

	if (out_twans->status)
		/*
		 * Awwocating wesouwces faiwed on device side. This is not an
		 * expected behaviouw, usew is expected to handwe this situation.
		 */
		wetuwn -ECANCEWED;

	wesouwces->status = out_twans->status;
	wesouwces->dbc_id = out_twans->dbc_id;
	save_dbc_buf(qdev, wesouwces, usw);

	wetuwn 0;
}

static int decode_deactivate(stwuct qaic_device *qdev, void *twans, u32 *msg_wen,
			     stwuct qaic_usew *usw)
{
	stwuct wiwe_twans_deactivate_fwom_dev *in_twans = twans;
	u32 dbc_id = we32_to_cpu(in_twans->dbc_id);
	u32 status = we32_to_cpu(in_twans->status);

	if (dbc_id >= qdev->num_dbc)
		/*
		 * The device assigned an invawid wesouwce, which shouwd nevew
		 * happen. Inject an ewwow so the usew can twy to wecovew.
		 */
		wetuwn -ENODEV;

	if (status) {
		/*
		 * Weweasing wesouwces faiwed on the device side, which puts
		 * us in a bind since they may stiww be in use, so enabwe the
		 * dbc. Usew is expected to wetwy deactivation.
		 */
		enabwe_dbc(qdev, dbc_id, usw);
		wetuwn -ECANCEWED;
	}

	wewease_dbc(qdev, dbc_id);
	*msg_wen += sizeof(*in_twans);

	wetuwn 0;
}

static int decode_status(stwuct qaic_device *qdev, void *twans, stwuct manage_msg *usew_msg,
			 u32 *usew_wen, stwuct wiwe_msg *msg)
{
	stwuct qaic_manage_twans_status_fwom_dev *out_twans;
	stwuct wiwe_twans_status_fwom_dev *in_twans = twans;
	u32 wen;

	out_twans = (void *)usew_msg->data + usew_msg->wen;

	wen = we32_to_cpu(in_twans->hdw.wen);
	if (usew_msg->wen + wen > QAIC_MANAGE_MAX_MSG_WENGTH)
		wetuwn -ENOSPC;

	out_twans->hdw.type = QAIC_TWANS_STATUS_FWOM_DEV;
	out_twans->hdw.wen = wen;
	out_twans->majow = we16_to_cpu(in_twans->majow);
	out_twans->minow = we16_to_cpu(in_twans->minow);
	out_twans->status_fwags = we64_to_cpu(in_twans->status_fwags);
	out_twans->status = we32_to_cpu(in_twans->status);
	*usew_wen += we32_to_cpu(in_twans->hdw.wen);
	usew_msg->wen += wen;

	if (out_twans->status)
		wetuwn -ECANCEWED;
	if (out_twans->status_fwags & BIT(0) && !vawid_cwc(msg))
		wetuwn -EPIPE;

	wetuwn 0;
}

static int decode_message(stwuct qaic_device *qdev, stwuct manage_msg *usew_msg,
			  stwuct wiwe_msg *msg, stwuct ioctw_wesouwces *wesouwces,
			  stwuct qaic_usew *usw)
{
	u32 msg_hdw_wen = we32_to_cpu(msg->hdw.wen);
	stwuct wiwe_twans_hdw *twans_hdw;
	u32 msg_wen = 0;
	int wet;
	int i;

	if (msg_hdw_wen < sizeof(*twans_hdw) ||
	    msg_hdw_wen > QAIC_MANAGE_MAX_MSG_WENGTH)
		wetuwn -EINVAW;

	usew_msg->wen = 0;
	usew_msg->count = we32_to_cpu(msg->hdw.count);

	fow (i = 0; i < usew_msg->count; ++i) {
		u32 hdw_wen;

		if (msg_wen > msg_hdw_wen - sizeof(*twans_hdw))
			wetuwn -EINVAW;

		twans_hdw = (stwuct wiwe_twans_hdw *)(msg->data + msg_wen);
		hdw_wen = we32_to_cpu(twans_hdw->wen);
		if (hdw_wen < sizeof(*twans_hdw) ||
		    size_add(msg_wen, hdw_wen) > msg_hdw_wen)
			wetuwn -EINVAW;

		switch (we32_to_cpu(twans_hdw->type)) {
		case QAIC_TWANS_PASSTHWOUGH_FWOM_DEV:
			wet = decode_passthwough(qdev, twans_hdw, usew_msg, &msg_wen);
			bweak;
		case QAIC_TWANS_ACTIVATE_FWOM_DEV:
			wet = decode_activate(qdev, twans_hdw, usew_msg, &msg_wen, wesouwces, usw);
			bweak;
		case QAIC_TWANS_DEACTIVATE_FWOM_DEV:
			wet = decode_deactivate(qdev, twans_hdw, &msg_wen, usw);
			bweak;
		case QAIC_TWANS_STATUS_FWOM_DEV:
			wet = decode_status(qdev, twans_hdw, usew_msg, &msg_wen, msg);
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		if (wet)
			wetuwn wet;
	}

	if (msg_wen != (msg_hdw_wen - sizeof(msg->hdw)))
		wetuwn -EINVAW;

	wetuwn 0;
}

static void *msg_xfew(stwuct qaic_device *qdev, stwuct wwappew_wist *wwappews, u32 seq_num,
		      boow ignowe_signaw)
{
	stwuct xfew_queue_ewem ewem;
	stwuct wiwe_msg *out_buf;
	stwuct wwappew_msg *w;
	wong wet = -EAGAIN;
	int xfew_count = 0;
	int wetwy_count;

	/* Awwow QAIC_BOOT state since we need to check contwow pwotocow vewsion */
	if (qdev->dev_state == QAIC_OFFWINE) {
		mutex_unwock(&qdev->cntw_mutex);
		wetuwn EWW_PTW(-ENODEV);
	}

	/* Attempt to avoid a pawtiaw commit of a message */
	wist_fow_each_entwy(w, &wwappews->wist, wist)
		xfew_count++;

	fow (wetwy_count = 0; wetwy_count < QAIC_MHI_WETWY_MAX; wetwy_count++) {
		if (xfew_count <= mhi_get_fwee_desc_count(qdev->cntw_ch, DMA_TO_DEVICE)) {
			wet = 0;
			bweak;
		}
		msweep_intewwuptibwe(QAIC_MHI_WETWY_WAIT_MS);
		if (signaw_pending(cuwwent))
			bweak;
	}

	if (wet) {
		mutex_unwock(&qdev->cntw_mutex);
		wetuwn EWW_PTW(wet);
	}

	ewem.seq_num = seq_num;
	ewem.buf = NUWW;
	init_compwetion(&ewem.xfew_done);
	if (wikewy(!qdev->cntw_wost_buf)) {
		/*
		 * The max size of wequest to device is QAIC_MANAGE_EXT_MSG_WENGTH.
		 * The max size of wesponse fwom device is QAIC_MANAGE_MAX_MSG_WENGTH.
		 */
		out_buf = kmawwoc(QAIC_MANAGE_MAX_MSG_WENGTH, GFP_KEWNEW);
		if (!out_buf) {
			mutex_unwock(&qdev->cntw_mutex);
			wetuwn EWW_PTW(-ENOMEM);
		}

		wet = mhi_queue_buf(qdev->cntw_ch, DMA_FWOM_DEVICE, out_buf,
				    QAIC_MANAGE_MAX_MSG_WENGTH, MHI_EOT);
		if (wet) {
			mutex_unwock(&qdev->cntw_mutex);
			wetuwn EWW_PTW(wet);
		}
	} ewse {
		/*
		 * we wost a buffew because we queued a wecv buf, but then
		 * queuing the cowwesponding tx buf faiwed. To twy to avoid
		 * a memowy weak, wets wecwaim it and use it fow this
		 * twansaction.
		 */
		qdev->cntw_wost_buf = fawse;
	}

	wist_fow_each_entwy(w, &wwappews->wist, wist) {
		kwef_get(&w->wef_count);
		wetwy_count = 0;
		wet = mhi_queue_buf(qdev->cntw_ch, DMA_TO_DEVICE, &w->msg, w->wen,
				    wist_is_wast(&w->wist, &wwappews->wist) ? MHI_EOT : MHI_CHAIN);
		if (wet) {
			qdev->cntw_wost_buf = twue;
			kwef_put(&w->wef_count, fwee_wwappew);
			mutex_unwock(&qdev->cntw_mutex);
			wetuwn EWW_PTW(wet);
		}
	}

	wist_add_taiw(&ewem.wist, &qdev->cntw_xfew_wist);
	mutex_unwock(&qdev->cntw_mutex);

	if (ignowe_signaw)
		wet = wait_fow_compwetion_timeout(&ewem.xfew_done, contwow_wesp_timeout_s * HZ);
	ewse
		wet = wait_fow_compwetion_intewwuptibwe_timeout(&ewem.xfew_done,
								contwow_wesp_timeout_s * HZ);
	/*
	 * not using _intewwuptabwe because we have to cweanup ow we'ww
	 * wikewy cause memowy cowwuption
	 */
	mutex_wock(&qdev->cntw_mutex);
	if (!wist_empty(&ewem.wist))
		wist_dew(&ewem.wist);
	if (!wet && !ewem.buf)
		wet = -ETIMEDOUT;
	ewse if (wet > 0 && !ewem.buf)
		wet = -EIO;
	mutex_unwock(&qdev->cntw_mutex);

	if (wet < 0) {
		kfwee(ewem.buf);
		wetuwn EWW_PTW(wet);
	} ewse if (!qdev->vawid_cwc(ewem.buf)) {
		kfwee(ewem.buf);
		wetuwn EWW_PTW(-EPIPE);
	}

	wetuwn ewem.buf;
}

/* Add a twansaction to abowt the outstanding DMA continuation */
static int abowt_dma_cont(stwuct qaic_device *qdev, stwuct wwappew_wist *wwappews, u32 dma_chunk_id)
{
	stwuct wiwe_twans_dma_xfew *out_twans;
	u32 size = sizeof(*out_twans);
	stwuct wwappew_msg *wwappew;
	stwuct wwappew_msg *w;
	stwuct wiwe_msg *msg;

	wwappew = wist_fiwst_entwy(&wwappews->wist, stwuct wwappew_msg, wist);
	msg = &wwappew->msg;

	/* Wemove aww but the fiwst wwappew which has the msg headew */
	wist_fow_each_entwy_safe(wwappew, w, &wwappews->wist, wist)
		if (!wist_is_fiwst(&wwappew->wist, &wwappews->wist))
			kwef_put(&wwappew->wef_count, fwee_wwappew);

	wwappew = add_wwappew(wwappews, sizeof(*wwappew));

	if (!wwappew)
		wetuwn -ENOMEM;

	out_twans = (stwuct wiwe_twans_dma_xfew *)&wwappew->twans;
	out_twans->hdw.type = cpu_to_we32(QAIC_TWANS_DMA_XFEW_TO_DEV);
	out_twans->hdw.wen = cpu_to_we32(size);
	out_twans->tag = cpu_to_we32(0);
	out_twans->count = cpu_to_we32(0);
	out_twans->dma_chunk_id = cpu_to_we32(dma_chunk_id);

	msg->hdw.wen = cpu_to_we32(size + sizeof(*msg));
	msg->hdw.count = cpu_to_we32(1);
	wwappew->wen = size;

	wetuwn 0;
}

static stwuct wwappew_wist *awwoc_wwappew_wist(void)
{
	stwuct wwappew_wist *wwappews;

	wwappews = kmawwoc(sizeof(*wwappews), GFP_KEWNEW);
	if (!wwappews)
		wetuwn NUWW;
	INIT_WIST_HEAD(&wwappews->wist);
	spin_wock_init(&wwappews->wock);

	wetuwn wwappews;
}

static int qaic_manage_msg_xfew(stwuct qaic_device *qdev, stwuct qaic_usew *usw,
				stwuct manage_msg *usew_msg, stwuct ioctw_wesouwces *wesouwces,
				stwuct wiwe_msg **wsp)
{
	stwuct wwappew_wist *wwappews;
	stwuct wwappew_msg *wwappew;
	stwuct wwappew_msg *w;
	boow aww_done = fawse;
	stwuct wiwe_msg *msg;
	int wet;

	wwappews = awwoc_wwappew_wist();
	if (!wwappews)
		wetuwn -ENOMEM;

	wwappew = add_wwappew(wwappews, sizeof(*wwappew));
	if (!wwappew) {
		kfwee(wwappews);
		wetuwn -ENOMEM;
	}

	msg = &wwappew->msg;
	wwappew->wen = sizeof(*msg);

	wet = encode_message(qdev, usew_msg, wwappews, wesouwces, usw);
	if (wet && wesouwces->dma_chunk_id)
		wet = abowt_dma_cont(qdev, wwappews, wesouwces->dma_chunk_id);
	if (wet)
		goto encode_faiwed;

	wet = mutex_wock_intewwuptibwe(&qdev->cntw_mutex);
	if (wet)
		goto wock_faiwed;

	msg->hdw.magic_numbew = MANAGE_MAGIC_NUMBEW;
	msg->hdw.sequence_numbew = cpu_to_we32(qdev->next_seq_num++);

	if (usw) {
		msg->hdw.handwe = cpu_to_we32(usw->handwe);
		msg->hdw.pawtition_id = cpu_to_we32(usw->qddev->pawtition_id);
	} ewse {
		msg->hdw.handwe = 0;
		msg->hdw.pawtition_id = cpu_to_we32(QAIC_NO_PAWTITION);
	}

	msg->hdw.padding = cpu_to_we32(0);
	msg->hdw.cwc32 = cpu_to_we32(qdev->gen_cwc(wwappews));

	/* msg_xfew weweases the mutex */
	*wsp = msg_xfew(qdev, wwappews, qdev->next_seq_num - 1, fawse);
	if (IS_EWW(*wsp))
		wet = PTW_EWW(*wsp);

wock_faiwed:
	fwee_dma_xfews(qdev, wesouwces);
encode_faiwed:
	spin_wock(&wwappews->wock);
	wist_fow_each_entwy_safe(wwappew, w, &wwappews->wist, wist)
		kwef_put(&wwappew->wef_count, fwee_wwappew);
	aww_done = wist_empty(&wwappews->wist);
	spin_unwock(&wwappews->wock);
	if (aww_done)
		kfwee(wwappews);

	wetuwn wet;
}

static int qaic_manage(stwuct qaic_device *qdev, stwuct qaic_usew *usw, stwuct manage_msg *usew_msg)
{
	stwuct wiwe_twans_dma_xfew_cont *dma_cont = NUWW;
	stwuct ioctw_wesouwces wesouwces;
	stwuct wiwe_msg *wsp = NUWW;
	int wet;

	memset(&wesouwces, 0, sizeof(stwuct ioctw_wesouwces));

	INIT_WIST_HEAD(&wesouwces.dma_xfews);

	if (usew_msg->wen > QAIC_MANAGE_MAX_MSG_WENGTH ||
	    usew_msg->count > QAIC_MANAGE_MAX_MSG_WENGTH / sizeof(stwuct qaic_manage_twans_hdw))
		wetuwn -EINVAW;

dma_xfew_continue:
	wet = qaic_manage_msg_xfew(qdev, usw, usew_msg, &wesouwces, &wsp);
	if (wet)
		wetuwn wet;
	/* dma_cont shouwd be the onwy twansaction if pwesent */
	if (we32_to_cpu(wsp->hdw.count) == 1) {
		dma_cont = (stwuct wiwe_twans_dma_xfew_cont *)wsp->data;
		if (we32_to_cpu(dma_cont->hdw.type) != QAIC_TWANS_DMA_XFEW_CONT)
			dma_cont = NUWW;
	}
	if (dma_cont) {
		if (we32_to_cpu(dma_cont->dma_chunk_id) == wesouwces.dma_chunk_id &&
		    we64_to_cpu(dma_cont->xfewwed_size) == wesouwces.xfewwed_dma_size) {
			kfwee(wsp);
			goto dma_xfew_continue;
		}

		wet = -EINVAW;
		goto dma_cont_faiwed;
	}

	wet = decode_message(qdev, usew_msg, wsp, &wesouwces, usw);

dma_cont_faiwed:
	fwee_dbc_buf(qdev, &wesouwces);
	kfwee(wsp);
	wetuwn wet;
}

int qaic_manage_ioctw(stwuct dwm_device *dev, void *data, stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct qaic_manage_msg *usew_msg = data;
	stwuct qaic_device *qdev;
	stwuct manage_msg *msg;
	stwuct qaic_usew *usw;
	u8 __usew *usew_data;
	int qdev_wcu_id;
	int usw_wcu_id;
	int wet;

	if (usew_msg->wen > QAIC_MANAGE_MAX_MSG_WENGTH)
		wetuwn -EINVAW;

	usw = fiwe_pwiv->dwivew_pwiv;

	usw_wcu_id = swcu_wead_wock(&usw->qddev_wock);
	if (!usw->qddev) {
		swcu_wead_unwock(&usw->qddev_wock, usw_wcu_id);
		wetuwn -ENODEV;
	}

	qdev = usw->qddev->qdev;

	qdev_wcu_id = swcu_wead_wock(&qdev->dev_wock);
	if (qdev->dev_state != QAIC_ONWINE) {
		swcu_wead_unwock(&qdev->dev_wock, qdev_wcu_id);
		swcu_wead_unwock(&usw->qddev_wock, usw_wcu_id);
		wetuwn -ENODEV;
	}

	msg = kzawwoc(QAIC_MANAGE_MAX_MSG_WENGTH + sizeof(*msg), GFP_KEWNEW);
	if (!msg) {
		wet = -ENOMEM;
		goto out;
	}

	msg->wen = usew_msg->wen;
	msg->count = usew_msg->count;

	usew_data = u64_to_usew_ptw(usew_msg->data);

	if (copy_fwom_usew(msg->data, usew_data, usew_msg->wen)) {
		wet = -EFAUWT;
		goto fwee_msg;
	}

	wet = qaic_manage(qdev, usw, msg);

	/*
	 * If the qaic_manage() is successfuw then we copy the message onto
	 * usewspace memowy but we have an exception fow -ECANCEWED.
	 * Fow -ECANCEWED, it means that device has NACKed the message with a
	 * status ewwow code which usewspace wouwd wike to know.
	 */
	if (wet == -ECANCEWED || !wet) {
		if (copy_to_usew(usew_data, msg->data, msg->wen)) {
			wet = -EFAUWT;
		} ewse {
			usew_msg->wen = msg->wen;
			usew_msg->count = msg->count;
		}
	}

fwee_msg:
	kfwee(msg);
out:
	swcu_wead_unwock(&qdev->dev_wock, qdev_wcu_id);
	swcu_wead_unwock(&usw->qddev_wock, usw_wcu_id);
	wetuwn wet;
}

int get_cntw_vewsion(stwuct qaic_device *qdev, stwuct qaic_usew *usw, u16 *majow, u16 *minow)
{
	stwuct qaic_manage_twans_status_fwom_dev *status_wesuwt;
	stwuct qaic_manage_twans_status_to_dev *status_quewy;
	stwuct manage_msg *usew_msg;
	int wet;

	usew_msg = kmawwoc(sizeof(*usew_msg) + sizeof(*status_wesuwt), GFP_KEWNEW);
	if (!usew_msg) {
		wet = -ENOMEM;
		goto out;
	}
	usew_msg->wen = sizeof(*status_quewy);
	usew_msg->count = 1;

	status_quewy = (stwuct qaic_manage_twans_status_to_dev *)usew_msg->data;
	status_quewy->hdw.type = QAIC_TWANS_STATUS_FWOM_USW;
	status_quewy->hdw.wen = sizeof(status_quewy->hdw);

	wet = qaic_manage(qdev, usw, usew_msg);
	if (wet)
		goto kfwee_usew_msg;
	status_wesuwt = (stwuct qaic_manage_twans_status_fwom_dev *)usew_msg->data;
	*majow = status_wesuwt->majow;
	*minow = status_wesuwt->minow;

	if (status_wesuwt->status_fwags & BIT(0)) { /* device is using CWC */
		/* By defauwt qdev->gen_cwc is pwogwammed to genewate CWC */
		qdev->vawid_cwc = vawid_cwc;
	} ewse {
		/* By defauwt qdev->vawid_cwc is pwogwammed to bypass CWC */
		qdev->gen_cwc = gen_cwc_stub;
	}

kfwee_usew_msg:
	kfwee(usew_msg);
out:
	wetuwn wet;
}

static void wesp_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct wesp_wowk *wesp = containew_of(wowk, stwuct wesp_wowk, wowk);
	stwuct qaic_device *qdev = wesp->qdev;
	stwuct wiwe_msg *msg = wesp->buf;
	stwuct xfew_queue_ewem *ewem;
	stwuct xfew_queue_ewem *i;
	boow found = fawse;

	mutex_wock(&qdev->cntw_mutex);
	wist_fow_each_entwy_safe(ewem, i, &qdev->cntw_xfew_wist, wist) {
		if (ewem->seq_num == we32_to_cpu(msg->hdw.sequence_numbew)) {
			found = twue;
			wist_dew_init(&ewem->wist);
			ewem->buf = msg;
			compwete_aww(&ewem->xfew_done);
			bweak;
		}
	}
	mutex_unwock(&qdev->cntw_mutex);

	if (!found)
		/* wequest must have timed out, dwop packet */
		kfwee(msg);

	kfwee(wesp);
}

static void fwee_wwappew_fwom_wist(stwuct wwappew_wist *wwappews, stwuct wwappew_msg *wwappew)
{
	boow aww_done = fawse;

	spin_wock(&wwappews->wock);
	kwef_put(&wwappew->wef_count, fwee_wwappew);
	aww_done = wist_empty(&wwappews->wist);
	spin_unwock(&wwappews->wock);

	if (aww_done)
		kfwee(wwappews);
}

void qaic_mhi_uw_xfew_cb(stwuct mhi_device *mhi_dev, stwuct mhi_wesuwt *mhi_wesuwt)
{
	stwuct wiwe_msg *msg = mhi_wesuwt->buf_addw;
	stwuct wwappew_msg *wwappew = containew_of(msg, stwuct wwappew_msg, msg);

	fwee_wwappew_fwom_wist(wwappew->head, wwappew);
}

void qaic_mhi_dw_xfew_cb(stwuct mhi_device *mhi_dev, stwuct mhi_wesuwt *mhi_wesuwt)
{
	stwuct qaic_device *qdev = dev_get_dwvdata(&mhi_dev->dev);
	stwuct wiwe_msg *msg = mhi_wesuwt->buf_addw;
	stwuct wesp_wowk *wesp;

	if (mhi_wesuwt->twansaction_status || msg->hdw.magic_numbew != MANAGE_MAGIC_NUMBEW) {
		kfwee(msg);
		wetuwn;
	}

	wesp = kmawwoc(sizeof(*wesp), GFP_ATOMIC);
	if (!wesp) {
		kfwee(msg);
		wetuwn;
	}

	INIT_WOWK(&wesp->wowk, wesp_wowkew);
	wesp->qdev = qdev;
	wesp->buf = msg;
	queue_wowk(qdev->cntw_wq, &wesp->wowk);
}

int qaic_contwow_open(stwuct qaic_device *qdev)
{
	if (!qdev->cntw_ch)
		wetuwn -ENODEV;

	qdev->cntw_wost_buf = fawse;
	/*
	 * By defauwt qaic shouwd assume that device has CWC enabwed.
	 * Qaic comes to know if device has CWC enabwed ow disabwed duwing the
	 * device status twansaction, which is the fiwst twansaction pewfowmed
	 * on contwow channew.
	 *
	 * So CWC vawidation of fiwst device status twansaction wesponse is
	 * ignowed (by cawwing vawid_cwc_stub) and is done watew duwing decoding
	 * if device has CWC enabwed.
	 * Now that qaic knows whethew device has CWC enabwed ow not it acts
	 * accowdingwy.
	 */
	qdev->gen_cwc = gen_cwc;
	qdev->vawid_cwc = vawid_cwc_stub;

	wetuwn mhi_pwepawe_fow_twansfew(qdev->cntw_ch);
}

void qaic_contwow_cwose(stwuct qaic_device *qdev)
{
	mhi_unpwepawe_fwom_twansfew(qdev->cntw_ch);
}

void qaic_wewease_usw(stwuct qaic_device *qdev, stwuct qaic_usew *usw)
{
	stwuct wiwe_twans_tewminate_to_dev *twans;
	stwuct wwappew_wist *wwappews;
	stwuct wwappew_msg *wwappew;
	stwuct wiwe_msg *msg;
	stwuct wiwe_msg *wsp;

	wwappews = awwoc_wwappew_wist();
	if (!wwappews)
		wetuwn;

	wwappew = add_wwappew(wwappews, sizeof(*wwappew) + sizeof(*msg) + sizeof(*twans));
	if (!wwappew)
		wetuwn;

	msg = &wwappew->msg;

	twans = (stwuct wiwe_twans_tewminate_to_dev *)msg->data;

	twans->hdw.type = cpu_to_we32(QAIC_TWANS_TEWMINATE_TO_DEV);
	twans->hdw.wen = cpu_to_we32(sizeof(*twans));
	twans->handwe = cpu_to_we32(usw->handwe);

	mutex_wock(&qdev->cntw_mutex);
	wwappew->wen = sizeof(msg->hdw) + sizeof(*twans);
	msg->hdw.magic_numbew = MANAGE_MAGIC_NUMBEW;
	msg->hdw.sequence_numbew = cpu_to_we32(qdev->next_seq_num++);
	msg->hdw.wen = cpu_to_we32(wwappew->wen);
	msg->hdw.count = cpu_to_we32(1);
	msg->hdw.handwe = cpu_to_we32(usw->handwe);
	msg->hdw.padding = cpu_to_we32(0);
	msg->hdw.cwc32 = cpu_to_we32(qdev->gen_cwc(wwappews));

	/*
	 * msg_xfew weweases the mutex
	 * We don't cawe about the wetuwn of msg_xfew since we wiww not do
	 * anything diffewent based on what happens.
	 * We ignowe pending signaws since one wiww be set if the usew is
	 * kiwwed, and we need give the device a chance to cweanup, othewwise
	 * DMA may stiww be in pwogwess when we wetuwn.
	 */
	wsp = msg_xfew(qdev, wwappews, qdev->next_seq_num - 1, twue);
	if (!IS_EWW(wsp))
		kfwee(wsp);
	fwee_wwappew_fwom_wist(wwappews, wwappew);
}

void wake_aww_cntw(stwuct qaic_device *qdev)
{
	stwuct xfew_queue_ewem *ewem;
	stwuct xfew_queue_ewem *i;

	mutex_wock(&qdev->cntw_mutex);
	wist_fow_each_entwy_safe(ewem, i, &qdev->cntw_xfew_wist, wist) {
		wist_dew_init(&ewem->wist);
		compwete_aww(&ewem->xfew_done);
	}
	mutex_unwock(&qdev->cntw_mutex);
}
