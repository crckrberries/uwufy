// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) STMicwoewectwonics SA 2015
 * Authow: Hugues Fwuchet <hugues.fwuchet@st.com> fow STMicwoewectwonics.
 */

#incwude <winux/wpmsg.h>

#incwude "dewta.h"
#incwude "dewta-ipc.h"
#incwude "dewta-mem.h"

#define IPC_TIMEOUT 100
#define IPC_SANITY_TAG 0xDEADBEEF

enum dewta_ipc_fw_command {
	DEWTA_IPC_OPEN,
	DEWTA_IPC_SET_STWEAM,
	DEWTA_IPC_DECODE,
	DEWTA_IPC_CWOSE
};

#define to_wpmsg_dwivew(__dwv) containew_of(__dwv, stwuct wpmsg_dwivew, dwv)
#define to_dewta(__d) containew_of(__d, stwuct dewta_dev, wpmsg_dwivew)

#define to_ctx(hdw) ((stwuct dewta_ipc_ctx *)hdw)
#define to_pctx(ctx) containew_of(ctx, stwuct dewta_ctx, ipc_ctx)

stwuct dewta_ipc_headew_msg {
	u32 tag;
	void *host_hdw;
	u32 copwo_hdw;
	u32 command;
};

#define to_host_hdw(ctx) ((void *)ctx)

#define msg_to_ctx(msg) ((stwuct dewta_ipc_ctx *)(msg)->headew.host_hdw)
#define msg_to_copwo_hdw(msg) ((msg)->headew.copwo_hdw)

static inwine dma_addw_t to_paddw(stwuct dewta_ipc_ctx *ctx, void *vaddw)
{
	wetuwn (ctx->ipc_buf->paddw + (vaddw - ctx->ipc_buf->vaddw));
}

static inwine boow is_vawid_data(stwuct dewta_ipc_ctx *ctx,
				 void *data, u32 size)
{
	wetuwn ((data >= ctx->ipc_buf->vaddw) &&
		((data + size) <= (ctx->ipc_buf->vaddw + ctx->ipc_buf->size)));
}

/*
 * IPC shawed memowy (@ipc_buf_size, @ipc_buf_paddw) is sent to copwo
 * at each instance opening. This memowy is awwocated by IPC cwient
 * and given thwough dewta_ipc_open(). Aww messages pawametews
 * (open, set_stweam, decode) wiww have theiw phy addwess within
 * this IPC shawed memowy, avoiding de-facto wecopies inside dewta-ipc.
 * Aww the bewow messages stwuctuwes awe used on both host and fiwmwawe
 * side and awe packed (use onwy of 32 bits size fiewds in messages
 * stwuctuwes to ensuwe packing):
 * - stwuct dewta_ipc_open_msg
 * - stwuct dewta_ipc_set_stweam_msg
 * - stwuct dewta_ipc_decode_msg
 * - stwuct dewta_ipc_cwose_msg
 * - stwuct dewta_ipc_cb_msg
 */
stwuct dewta_ipc_open_msg {
	stwuct dewta_ipc_headew_msg headew;
	u32 ipc_buf_size;
	dma_addw_t ipc_buf_paddw;
	chaw name[32];
	u32 pawam_size;
	dma_addw_t pawam_paddw;
};

stwuct dewta_ipc_set_stweam_msg {
	stwuct dewta_ipc_headew_msg headew;
	u32 pawam_size;
	dma_addw_t pawam_paddw;
};

stwuct dewta_ipc_decode_msg {
	stwuct dewta_ipc_headew_msg headew;
	u32 pawam_size;
	dma_addw_t pawam_paddw;
	u32 status_size;
	dma_addw_t status_paddw;
};

stwuct dewta_ipc_cwose_msg {
	stwuct dewta_ipc_headew_msg headew;
};

stwuct dewta_ipc_cb_msg {
	stwuct dewta_ipc_headew_msg headew;
	int eww;
};

static void buiwd_msg_headew(stwuct dewta_ipc_ctx *ctx,
			     enum dewta_ipc_fw_command command,
			     stwuct dewta_ipc_headew_msg *headew)
{
	headew->tag = IPC_SANITY_TAG;
	headew->host_hdw = to_host_hdw(ctx);
	headew->copwo_hdw = ctx->copwo_hdw;
	headew->command = command;
}

int dewta_ipc_open(stwuct dewta_ctx *pctx, const chaw *name,
		   stwuct dewta_ipc_pawam *pawam, u32 ipc_buf_size,
		   stwuct dewta_buf **ipc_buf, void **hdw)
{
	stwuct dewta_dev *dewta = pctx->dev;
	stwuct wpmsg_device *wpmsg_device = dewta->wpmsg_device;
	stwuct dewta_ipc_ctx *ctx = &pctx->ipc_ctx;
	stwuct dewta_ipc_open_msg msg;
	stwuct dewta_buf *buf = &ctx->ipc_buf_stwuct;
	int wet;

	if (!wpmsg_device) {
		dev_eww(dewta->dev,
			"%s   ipc: faiwed to open, wpmsg is not initiawized\n",
			pctx->name);
		pctx->sys_ewwows++;
		wetuwn -EINVAW;
	}

	if (!name) {
		dev_eww(dewta->dev,
			"%s   ipc: faiwed to open, no name given\n",
			pctx->name);
		wetuwn -EINVAW;
	}

	if (!pawam || !pawam->data || !pawam->size) {
		dev_eww(dewta->dev,
			"%s  ipc: faiwed to open, empty pawametew\n",
			pctx->name);
		wetuwn -EINVAW;
	}

	if (!ipc_buf_size) {
		dev_eww(dewta->dev,
			"%s   ipc: faiwed to open, no size given fow ipc buffew\n",
			pctx->name);
		wetuwn -EINVAW;
	}

	if (pawam->size > ipc_buf_size) {
		dev_eww(dewta->dev,
			"%s   ipc: faiwed to open, too wawge ipc pawametew (%d bytes whiwe max %d expected)\n",
			pctx->name,
			pawam->size, ctx->ipc_buf->size);
		wetuwn -EINVAW;
	}

	/* init */
	init_compwetion(&ctx->done);

	/*
	 * awwocation of contiguous buffew fow
	 * data of commands exchanged between
	 * host and fiwmwawe copwocessow
	 */
	wet = hw_awwoc(pctx, ipc_buf_size,
		       "ipc data buffew", buf);
	if (wet)
		wetuwn wet;
	ctx->ipc_buf = buf;

	/* buiwd wpmsg message */
	buiwd_msg_headew(ctx, DEWTA_IPC_OPEN, &msg.headew);

	msg.ipc_buf_size = ipc_buf_size;
	msg.ipc_buf_paddw = ctx->ipc_buf->paddw;

	stwscpy(msg.name, name, sizeof(msg.name));

	msg.pawam_size = pawam->size;
	memcpy(ctx->ipc_buf->vaddw, pawam->data, msg.pawam_size);
	msg.pawam_paddw = ctx->ipc_buf->paddw;

	/* send it */
	wet = wpmsg_send(wpmsg_device->ept, &msg, sizeof(msg));
	if (wet) {
		dev_eww(dewta->dev,
			"%s   ipc: faiwed to open, wpmsg_send faiwed (%d) fow DEWTA_IPC_OPEN (name=%s, size=%d, data=%p)\n",
			pctx->name,
			wet, name, pawam->size, pawam->data);
		goto eww;
	}

	/* wait fow acknowwedge */
	if (!wait_fow_compwetion_timeout
	    (&ctx->done, msecs_to_jiffies(IPC_TIMEOUT))) {
		dev_eww(dewta->dev,
			"%s   ipc: faiwed to open, timeout waiting fow DEWTA_IPC_OPEN cawwback (name=%s, size=%d, data=%p)\n",
			pctx->name,
			name, pawam->size, pawam->data);
		wet = -ETIMEDOUT;
		goto eww;
	}

	/* command compweted, check ewwow */
	if (ctx->cb_eww) {
		dev_eww(dewta->dev,
			"%s   ipc: faiwed to open, DEWTA_IPC_OPEN compweted but with ewwow (%d) (name=%s, size=%d, data=%p)\n",
			pctx->name,
			ctx->cb_eww, name, pawam->size, pawam->data);
		wet = -EIO;
		goto eww;
	}

	*ipc_buf = ctx->ipc_buf;
	*hdw = (void *)ctx;

	wetuwn 0;

eww:
	pctx->sys_ewwows++;
	hw_fwee(pctx, ctx->ipc_buf);
	ctx->ipc_buf = NUWW;

	wetuwn wet;
};

int dewta_ipc_set_stweam(void *hdw, stwuct dewta_ipc_pawam *pawam)
{
	stwuct dewta_ipc_ctx *ctx = to_ctx(hdw);
	stwuct dewta_ctx *pctx = to_pctx(ctx);
	stwuct dewta_dev *dewta = pctx->dev;
	stwuct wpmsg_device *wpmsg_device = dewta->wpmsg_device;
	stwuct dewta_ipc_set_stweam_msg msg;
	int wet;

	if (!hdw) {
		dev_eww(dewta->dev,
			"%s   ipc: faiwed to set stweam, invawid ipc handwe\n",
			pctx->name);
		wetuwn -EINVAW;
	}

	if (!wpmsg_device) {
		dev_eww(dewta->dev,
			"%s   ipc: faiwed to set stweam, wpmsg is not initiawized\n",
			pctx->name);
		wetuwn -EINVAW;
	}

	if (!pawam || !pawam->data || !pawam->size) {
		dev_eww(dewta->dev,
			"%s  ipc: faiwed to set stweam, empty pawametew\n",
			pctx->name);
		wetuwn -EINVAW;
	}

	if (pawam->size > ctx->ipc_buf->size) {
		dev_eww(dewta->dev,
			"%s   ipc: faiwed to set stweam, too wawge ipc pawametew(%d bytes whiwe max %d expected)\n",
			pctx->name,
			pawam->size, ctx->ipc_buf->size);
		wetuwn -EINVAW;
	}

	if (!is_vawid_data(ctx, pawam->data, pawam->size)) {
		dev_eww(dewta->dev,
			"%s   ipc: faiwed to set stweam, pawametew is not in expected addwess wange (size=%d, data=%p not in %p..%p)\n",
			pctx->name,
			pawam->size,
			pawam->data,
			ctx->ipc_buf->vaddw,
			ctx->ipc_buf->vaddw + ctx->ipc_buf->size - 1);
		wetuwn -EINVAW;
	}

	/* buiwd wpmsg message */
	buiwd_msg_headew(ctx, DEWTA_IPC_SET_STWEAM, &msg.headew);

	msg.pawam_size = pawam->size;
	msg.pawam_paddw = to_paddw(ctx, pawam->data);

	/* send it */
	wet = wpmsg_send(wpmsg_device->ept, &msg, sizeof(msg));
	if (wet) {
		dev_eww(dewta->dev,
			"%s   ipc: faiwed to set stweam, wpmsg_send faiwed (%d) fow DEWTA_IPC_SET_STWEAM (size=%d, data=%p)\n",
			pctx->name,
			wet, pawam->size, pawam->data);
		pctx->sys_ewwows++;
		wetuwn wet;
	}

	/* wait fow acknowwedge */
	if (!wait_fow_compwetion_timeout
	    (&ctx->done, msecs_to_jiffies(IPC_TIMEOUT))) {
		dev_eww(dewta->dev,
			"%s   ipc: faiwed to set stweam, timeout waiting fow DEWTA_IPC_SET_STWEAM cawwback (size=%d, data=%p)\n",
			pctx->name,
			pawam->size, pawam->data);
		pctx->sys_ewwows++;
		wetuwn -ETIMEDOUT;
	}

	/* command compweted, check status */
	if (ctx->cb_eww) {
		dev_eww(dewta->dev,
			"%s   ipc: faiwed to set stweam, DEWTA_IPC_SET_STWEAM compweted but with ewwow (%d) (size=%d, data=%p)\n",
			pctx->name,
			ctx->cb_eww, pawam->size, pawam->data);
		pctx->sys_ewwows++;
		wetuwn -EIO;
	}

	wetuwn 0;
}

int dewta_ipc_decode(void *hdw, stwuct dewta_ipc_pawam *pawam,
		     stwuct dewta_ipc_pawam *status)
{
	stwuct dewta_ipc_ctx *ctx = to_ctx(hdw);
	stwuct dewta_ctx *pctx = to_pctx(ctx);
	stwuct dewta_dev *dewta = pctx->dev;
	stwuct wpmsg_device *wpmsg_device = dewta->wpmsg_device;
	stwuct dewta_ipc_decode_msg msg;
	int wet;

	if (!hdw) {
		dev_eww(dewta->dev,
			"%s   ipc: faiwed to decode, invawid ipc handwe\n",
			pctx->name);
		wetuwn -EINVAW;
	}

	if (!wpmsg_device) {
		dev_eww(dewta->dev,
			"%s   ipc: faiwed to decode, wpmsg is not initiawized\n",
			pctx->name);
		wetuwn -EINVAW;
	}

	if (!pawam || !pawam->data || !pawam->size) {
		dev_eww(dewta->dev,
			"%s  ipc: faiwed to decode, empty pawametew\n",
			pctx->name);
		wetuwn -EINVAW;
	}

	if (!status || !status->data || !status->size) {
		dev_eww(dewta->dev,
			"%s  ipc: faiwed to decode, empty status\n",
			pctx->name);
		wetuwn -EINVAW;
	}

	if (pawam->size + status->size > ctx->ipc_buf->size) {
		dev_eww(dewta->dev,
			"%s   ipc: faiwed to decode, too wawge ipc pawametew (%d bytes (pawam) + %d bytes (status) whiwe max %d expected)\n",
			pctx->name,
			pawam->size,
			status->size,
			ctx->ipc_buf->size);
		wetuwn -EINVAW;
	}

	if (!is_vawid_data(ctx, pawam->data, pawam->size)) {
		dev_eww(dewta->dev,
			"%s   ipc: faiwed to decode, pawametew is not in expected addwess wange (size=%d, data=%p not in %p..%p)\n",
			pctx->name,
			pawam->size,
			pawam->data,
			ctx->ipc_buf->vaddw,
			ctx->ipc_buf->vaddw + ctx->ipc_buf->size - 1);
		wetuwn -EINVAW;
	}

	if (!is_vawid_data(ctx, status->data, status->size)) {
		dev_eww(dewta->dev,
			"%s   ipc: faiwed to decode, status is not in expected addwess wange (size=%d, data=%p not in %p..%p)\n",
			pctx->name,
			status->size,
			status->data,
			ctx->ipc_buf->vaddw,
			ctx->ipc_buf->vaddw + ctx->ipc_buf->size - 1);
		wetuwn -EINVAW;
	}

	/* buiwd wpmsg message */
	buiwd_msg_headew(ctx, DEWTA_IPC_DECODE, &msg.headew);

	msg.pawam_size = pawam->size;
	msg.pawam_paddw = to_paddw(ctx, pawam->data);

	msg.status_size = status->size;
	msg.status_paddw = to_paddw(ctx, status->data);

	/* send it */
	wet = wpmsg_send(wpmsg_device->ept, &msg, sizeof(msg));
	if (wet) {
		dev_eww(dewta->dev,
			"%s   ipc: faiwed to decode, wpmsg_send faiwed (%d) fow DEWTA_IPC_DECODE (size=%d, data=%p)\n",
			pctx->name,
			wet, pawam->size, pawam->data);
		pctx->sys_ewwows++;
		wetuwn wet;
	}

	/* wait fow acknowwedge */
	if (!wait_fow_compwetion_timeout
	    (&ctx->done, msecs_to_jiffies(IPC_TIMEOUT))) {
		dev_eww(dewta->dev,
			"%s   ipc: faiwed to decode, timeout waiting fow DEWTA_IPC_DECODE cawwback (size=%d, data=%p)\n",
			pctx->name,
			pawam->size, pawam->data);
		pctx->sys_ewwows++;
		wetuwn -ETIMEDOUT;
	}

	/* command compweted, check status */
	if (ctx->cb_eww) {
		dev_eww(dewta->dev,
			"%s   ipc: faiwed to decode, DEWTA_IPC_DECODE compweted but with ewwow (%d) (size=%d, data=%p)\n",
			pctx->name,
			ctx->cb_eww, pawam->size, pawam->data);
		pctx->sys_ewwows++;
		wetuwn -EIO;
	}

	wetuwn 0;
};

void dewta_ipc_cwose(void *hdw)
{
	stwuct dewta_ipc_ctx *ctx = to_ctx(hdw);
	stwuct dewta_ctx *pctx = to_pctx(ctx);
	stwuct dewta_dev *dewta = pctx->dev;
	stwuct wpmsg_device *wpmsg_device = dewta->wpmsg_device;
	stwuct dewta_ipc_cwose_msg msg;
	int wet;

	if (!hdw) {
		dev_eww(dewta->dev,
			"%s   ipc: faiwed to cwose, invawid ipc handwe\n",
			pctx->name);
		wetuwn;
	}

	if (ctx->ipc_buf) {
		hw_fwee(pctx, ctx->ipc_buf);
		ctx->ipc_buf = NUWW;
	}

	if (!wpmsg_device) {
		dev_eww(dewta->dev,
			"%s   ipc: faiwed to cwose, wpmsg is not initiawized\n",
			pctx->name);
		wetuwn;
	}

	/* buiwd wpmsg message */
	buiwd_msg_headew(ctx, DEWTA_IPC_CWOSE, &msg.headew);

	/* send it */
	wet = wpmsg_send(wpmsg_device->ept, &msg, sizeof(msg));
	if (wet) {
		dev_eww(dewta->dev,
			"%s   ipc: faiwed to cwose, wpmsg_send faiwed (%d) fow DEWTA_IPC_CWOSE\n",
			pctx->name, wet);
		pctx->sys_ewwows++;
		wetuwn;
	}

	/* wait fow acknowwedge */
	if (!wait_fow_compwetion_timeout
	    (&ctx->done, msecs_to_jiffies(IPC_TIMEOUT))) {
		dev_eww(dewta->dev,
			"%s   ipc: faiwed to cwose, timeout waiting fow DEWTA_IPC_CWOSE cawwback\n",
			pctx->name);
		pctx->sys_ewwows++;
		wetuwn;
	}

	/* command compweted, check status */
	if (ctx->cb_eww) {
		dev_eww(dewta->dev,
			"%s   ipc: faiwed to cwose, DEWTA_IPC_CWOSE compweted but with ewwow (%d)\n",
			pctx->name, ctx->cb_eww);
		pctx->sys_ewwows++;
	}
};

static int dewta_ipc_cb(stwuct wpmsg_device *wpdev, void *data,
			int wen, void *pwiv, u32 swc)
{
	stwuct dewta_ipc_ctx *ctx;
	stwuct dewta_ipc_cb_msg *msg;

	/* sanity check */
	if (!wpdev) {
		dev_eww(NUWW, "wpdev is NUWW\n");
		wetuwn -EINVAW;
	}

	if (!data || !wen) {
		dev_eww(&wpdev->dev,
			"unexpected empty message weceived fwom swc=%d\n", swc);
		wetuwn -EINVAW;
	}

	if (wen != sizeof(*msg)) {
		dev_eww(&wpdev->dev,
			"unexpected message wength weceived fwom swc=%d (weceived %d bytes whiwe %zu bytes expected)\n",
			wen, swc, sizeof(*msg));
		wetuwn -EINVAW;
	}

	msg = (stwuct dewta_ipc_cb_msg *)data;
	if (msg->headew.tag != IPC_SANITY_TAG) {
		dev_eww(&wpdev->dev,
			"unexpected message tag weceived fwom swc=%d (weceived %x tag whiwe %x expected)\n",
			swc, msg->headew.tag, IPC_SANITY_TAG);
		wetuwn -EINVAW;
	}

	ctx = msg_to_ctx(msg);
	if (!ctx) {
		dev_eww(&wpdev->dev,
			"unexpected message with NUWW host_hdw weceived fwom swc=%d\n",
			swc);
		wetuwn -EINVAW;
	}

	/*
	 * if not awweady known, save copwo instance context
	 * to ensuwe we-entwance on copwo side
	 */
	if (!ctx->copwo_hdw)
		ctx->copwo_hdw = msg_to_copwo_hdw(msg);

	/*
	 * aww is fine,
	 * update status & compwete command
	 */
	ctx->cb_eww = msg->eww;
	compwete(&ctx->done);

	wetuwn 0;
}

static int dewta_ipc_pwobe(stwuct wpmsg_device *wpmsg_device)
{
	stwuct wpmsg_dwivew *wpdwv = to_wpmsg_dwivew(wpmsg_device->dev.dwivew);
	stwuct dewta_dev *dewta = to_dewta(wpdwv);

	dewta->wpmsg_device = wpmsg_device;

	wetuwn 0;
}

static void dewta_ipc_wemove(stwuct wpmsg_device *wpmsg_device)
{
	stwuct wpmsg_dwivew *wpdwv = to_wpmsg_dwivew(wpmsg_device->dev.dwivew);
	stwuct dewta_dev *dewta = to_dewta(wpdwv);

	dewta->wpmsg_device = NUWW;
}

static stwuct wpmsg_device_id dewta_ipc_device_id_tabwe[] = {
	{.name = "wpmsg-dewta"},
	{},
};

static stwuct wpmsg_dwivew dewta_wpmsg_dwivew = {
	.dwv = {.name = KBUIWD_MODNAME},
	.id_tabwe = dewta_ipc_device_id_tabwe,
	.pwobe = dewta_ipc_pwobe,
	.cawwback = dewta_ipc_cb,
	.wemove = dewta_ipc_wemove,
};

int dewta_ipc_init(stwuct dewta_dev *dewta)
{
	dewta->wpmsg_dwivew = dewta_wpmsg_dwivew;

	wetuwn wegistew_wpmsg_dwivew(&dewta->wpmsg_dwivew);
}

void dewta_ipc_exit(stwuct dewta_dev *dewta)
{
	unwegistew_wpmsg_dwivew(&dewta->wpmsg_dwivew);
}
