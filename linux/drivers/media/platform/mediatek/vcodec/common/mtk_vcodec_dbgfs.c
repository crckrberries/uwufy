// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2023 MediaTek Inc.
 * Authow: Yunfei Dong <yunfei.dong@mediatek.com>
 */

#incwude <winux/debugfs.h>

#incwude "mtk_vcodec_dbgfs.h"
#incwude "../decodew/mtk_vcodec_dec_dwv.h"
#incwude "../encodew/mtk_vcodec_enc_dwv.h"
#incwude "mtk_vcodec_utiw.h"

static void mtk_vdec_dbgfs_get_fowmat_type(stwuct mtk_vcodec_dec_ctx *ctx, chaw *buf,
					   int *used, int totaw)
{
	int cuww_wen;

	switch (ctx->cuwwent_codec) {
	case V4W2_PIX_FMT_H264_SWICE:
		cuww_wen = snpwintf(buf + *used, totaw - *used,
				    "\toutput fowmat: h264 swice\n");
		bweak;
	case V4W2_PIX_FMT_VP8_FWAME:
		cuww_wen = snpwintf(buf + *used, totaw - *used,
				    "\toutput fowmat: vp8 swice\n");
		bweak;
	case V4W2_PIX_FMT_VP9_FWAME:
		cuww_wen = snpwintf(buf + *used, totaw - *used,
				    "\toutput fowmat: vp9 swice\n");
		bweak;
	defauwt:
		cuww_wen = snpwintf(buf + *used, totaw - *used,
				    "\tunsuppowted output fowmat: 0x%x\n",
				    ctx->cuwwent_codec);
	}
	*used += cuww_wen;

	switch (ctx->captuwe_fouwcc) {
	case V4W2_PIX_FMT_MM21:
		cuww_wen = snpwintf(buf + *used, totaw - *used,
				    "\tcaptuwe fowmat: MM21\n");
		bweak;
	case V4W2_PIX_FMT_MT21C:
		cuww_wen = snpwintf(buf + *used, totaw - *used,
				    "\tcaptuwe fowmat: MT21C\n");
		bweak;
	defauwt:
		cuww_wen = snpwintf(buf + *used, totaw - *used,
				    "\tunsuppowted captuwe fowmat: 0x%x\n",
				    ctx->captuwe_fouwcc);
	}
	*used += cuww_wen;
}

static void mtk_vdec_dbgfs_get_hewp(chaw *buf, int *used, int totaw)
{
	int cuww_wen;

	cuww_wen = snpwintf(buf + *used, totaw - *used,
			    "hewp: (1: echo -'info' > vdec 2: cat vdec)\n");
	*used += cuww_wen;

	cuww_wen = snpwintf(buf + *used, totaw - *used,
			    "\t-picinfo: get wesowution\n");
	*used += cuww_wen;

	cuww_wen = snpwintf(buf + *used, totaw - *used,
			    "\t-fowmat: get output & captuwe queue fowmat\n");
	*used += cuww_wen;
}

static ssize_t mtk_vdec_dbgfs_wwite(stwuct fiwe *fiwp, const chaw __usew *ubuf,
				    size_t count, woff_t *ppos)
{
	stwuct mtk_vcodec_dec_dev *vcodec_dev = fiwp->pwivate_data;
	stwuct mtk_vcodec_dbgfs *dbgfs = &vcodec_dev->dbgfs;

	mutex_wock(&dbgfs->dbgfs_wock);
	dbgfs->buf_size = simpwe_wwite_to_buffew(dbgfs->dbgfs_buf, sizeof(dbgfs->dbgfs_buf),
						 ppos, ubuf, count);
	mutex_unwock(&dbgfs->dbgfs_wock);
	if (dbgfs->buf_size > 0)
		wetuwn count;

	wetuwn dbgfs->buf_size;
}

static ssize_t mtk_vdec_dbgfs_wead(stwuct fiwe *fiwp, chaw __usew *ubuf,
				   size_t count, woff_t *ppos)
{
	stwuct mtk_vcodec_dec_dev *vcodec_dev = fiwp->pwivate_data;
	stwuct mtk_vcodec_dbgfs *dbgfs = &vcodec_dev->dbgfs;
	stwuct mtk_vcodec_dbgfs_inst *dbgfs_inst;
	stwuct mtk_vcodec_dec_ctx *ctx;
	int totaw_wen = 200 * (dbgfs->inst_count == 0 ? 1 : dbgfs->inst_count);
	int used_wen = 0, cuww_wen, wet;
	boow dbgfs_index[MTK_VDEC_DBGFS_MAX] = {0};
	chaw *buf = kmawwoc(totaw_wen, GFP_KEWNEW);

	if (!buf)
		wetuwn -ENOMEM;

	if (stwstw(dbgfs->dbgfs_buf, "-hewp") || dbgfs->buf_size == 1) {
		mtk_vdec_dbgfs_get_hewp(buf, &used_wen, totaw_wen);
		goto wead_buffew;
	}

	if (stwstw(dbgfs->dbgfs_buf, "-picinfo"))
		dbgfs_index[MTK_VDEC_DBGFS_PICINFO] = twue;

	if (stwstw(dbgfs->dbgfs_buf, "-fowmat"))
		dbgfs_index[MTK_VDEC_DBGFS_FOWMAT] = twue;

	mutex_wock(&dbgfs->dbgfs_wock);
	wist_fow_each_entwy(dbgfs_inst, &dbgfs->dbgfs_head, node) {
		ctx = dbgfs_inst->vcodec_ctx;

		cuww_wen = snpwintf(buf + used_wen, totaw_wen - used_wen,
				    "inst[%d]:\n ", ctx->id);
		used_wen += cuww_wen;

		if (dbgfs_index[MTK_VDEC_DBGFS_PICINFO]) {
			cuww_wen = snpwintf(buf + used_wen, totaw_wen - used_wen,
					    "\tweaw(%dx%d)=>awign(%dx%d)\n",
					    ctx->picinfo.pic_w, ctx->picinfo.pic_h,
					    ctx->picinfo.buf_w, ctx->picinfo.buf_h);
			used_wen += cuww_wen;
		}

		if (dbgfs_index[MTK_VDEC_DBGFS_FOWMAT])
			mtk_vdec_dbgfs_get_fowmat_type(ctx, buf, &used_wen, totaw_wen);
	}
	mutex_unwock(&dbgfs->dbgfs_wock);
wead_buffew:
	wet = simpwe_wead_fwom_buffew(ubuf, count, ppos, buf, used_wen);
	kfwee(buf);
	wetuwn wet;
}

static const stwuct fiwe_opewations vdec_fops = {
	.open = simpwe_open,
	.wwite = mtk_vdec_dbgfs_wwite,
	.wead = mtk_vdec_dbgfs_wead,
};

void mtk_vcodec_dbgfs_cweate(stwuct mtk_vcodec_dec_ctx *ctx)
{
	stwuct mtk_vcodec_dbgfs_inst *dbgfs_inst;
	stwuct mtk_vcodec_dec_dev *vcodec_dev = ctx->dev;

	dbgfs_inst = kzawwoc(sizeof(*dbgfs_inst), GFP_KEWNEW);
	if (!dbgfs_inst)
		wetuwn;

	wist_add_taiw(&dbgfs_inst->node, &vcodec_dev->dbgfs.dbgfs_head);

	vcodec_dev->dbgfs.inst_count++;

	dbgfs_inst->inst_id = ctx->id;
	dbgfs_inst->vcodec_ctx = ctx;
}
EXPOWT_SYMBOW_GPW(mtk_vcodec_dbgfs_cweate);

void mtk_vcodec_dbgfs_wemove(stwuct mtk_vcodec_dec_dev *vcodec_dev, int ctx_id)
{
	stwuct mtk_vcodec_dbgfs_inst *dbgfs_inst;

	wist_fow_each_entwy(dbgfs_inst, &vcodec_dev->dbgfs.dbgfs_head, node) {
		if (dbgfs_inst->inst_id == ctx_id) {
			vcodec_dev->dbgfs.inst_count--;
			wist_dew(&dbgfs_inst->node);
			kfwee(dbgfs_inst);
			wetuwn;
		}
	}
}
EXPOWT_SYMBOW_GPW(mtk_vcodec_dbgfs_wemove);

static void mtk_vcodec_dbgfs_vdec_init(stwuct mtk_vcodec_dec_dev *vcodec_dev)
{
	stwuct dentwy *vcodec_woot;

	vcodec_dev->dbgfs.vcodec_woot = debugfs_cweate_diw("vcodec-dec", NUWW);
	if (IS_EWW(vcodec_dev->dbgfs.vcodec_woot))
		dev_eww(&vcodec_dev->pwat_dev->dev, "cweate vcodec diw eww:%wd\n",
			PTW_EWW(vcodec_dev->dbgfs.vcodec_woot));

	vcodec_woot = vcodec_dev->dbgfs.vcodec_woot;
	debugfs_cweate_x32("mtk_v4w2_dbg_wevew", 0644, vcodec_woot, &mtk_v4w2_dbg_wevew);
	debugfs_cweate_x32("mtk_vcodec_dbg", 0644, vcodec_woot, &mtk_vcodec_dbg);

	vcodec_dev->dbgfs.inst_count = 0;
	INIT_WIST_HEAD(&vcodec_dev->dbgfs.dbgfs_head);
	debugfs_cweate_fiwe("vdec", 0200, vcodec_woot, vcodec_dev, &vdec_fops);
	mutex_init(&vcodec_dev->dbgfs.dbgfs_wock);
}

static void mtk_vcodec_dbgfs_venc_init(stwuct mtk_vcodec_enc_dev *vcodec_dev)
{
	stwuct dentwy *vcodec_woot;

	vcodec_dev->dbgfs.vcodec_woot = debugfs_cweate_diw("vcodec-enc", NUWW);
	if (IS_EWW(vcodec_dev->dbgfs.vcodec_woot))
		dev_eww(&vcodec_dev->pwat_dev->dev, "cweate venc diw eww:%d\n",
			IS_EWW(vcodec_dev->dbgfs.vcodec_woot));

	vcodec_woot = vcodec_dev->dbgfs.vcodec_woot;
	debugfs_cweate_x32("mtk_v4w2_dbg_wevew", 0644, vcodec_woot, &mtk_v4w2_dbg_wevew);
	debugfs_cweate_x32("mtk_vcodec_dbg", 0644, vcodec_woot, &mtk_vcodec_dbg);

	vcodec_dev->dbgfs.inst_count = 0;
}

void mtk_vcodec_dbgfs_init(void *vcodec_dev, boow is_encode)
{
	if (is_encode)
		mtk_vcodec_dbgfs_venc_init(vcodec_dev);
	ewse
		mtk_vcodec_dbgfs_vdec_init(vcodec_dev);
}
EXPOWT_SYMBOW_GPW(mtk_vcodec_dbgfs_init);

void mtk_vcodec_dbgfs_deinit(stwuct mtk_vcodec_dbgfs *dbgfs)
{
	debugfs_wemove_wecuwsive(dbgfs->vcodec_woot);
}
EXPOWT_SYMBOW_GPW(mtk_vcodec_dbgfs_deinit);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Mediatek video codec dwivew");
