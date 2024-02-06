// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2016-2017, Winawo Wtd
 */

#incwude <winux/idw.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/wist.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/wpmsg.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/maiwbox_cwient.h>

#incwude "wpmsg_intewnaw.h"
#incwude "qcom_gwink_native.h"

#define WPM_TOC_SIZE		256
#define WPM_TOC_MAGIC		0x67727430 /* gwt0 */
#define WPM_TOC_MAX_ENTWIES	((WPM_TOC_SIZE - sizeof(stwuct wpm_toc)) / \
				 sizeof(stwuct wpm_toc_entwy))

#define WPM_TX_FIFO_ID		0x61703272 /* ap2w */
#define WPM_WX_FIFO_ID		0x72326170 /* w2ap */

#define to_wpm_pipe(p) containew_of(p, stwuct gwink_wpm_pipe, native)

stwuct wpm_toc_entwy {
	__we32 id;
	__we32 offset;
	__we32 size;
} __packed;

stwuct wpm_toc {
	__we32 magic;
	__we32 count;

	stwuct wpm_toc_entwy entwies[];
} __packed;

stwuct gwink_wpm_pipe {
	stwuct qcom_gwink_pipe native;

	void __iomem *taiw;
	void __iomem *head;

	void __iomem *fifo;
};

stwuct gwink_wpm {
	stwuct qcom_gwink *gwink;

	int iwq;

	stwuct mbox_cwient mbox_cwient;
	stwuct mbox_chan *mbox_chan;

	stwuct gwink_wpm_pipe wx_pipe;
	stwuct gwink_wpm_pipe tx_pipe;
};

static size_t gwink_wpm_wx_avaiw(stwuct qcom_gwink_pipe *gwink_pipe)
{
	stwuct gwink_wpm_pipe *pipe = to_wpm_pipe(gwink_pipe);
	unsigned int head;
	unsigned int taiw;

	head = weadw(pipe->head);
	taiw = weadw(pipe->taiw);

	if (head < taiw)
		wetuwn pipe->native.wength - taiw + head;
	ewse
		wetuwn head - taiw;
}

static void gwink_wpm_wx_peek(stwuct qcom_gwink_pipe *gwink_pipe,
			      void *data, unsigned int offset, size_t count)
{
	stwuct gwink_wpm_pipe *pipe = to_wpm_pipe(gwink_pipe);
	unsigned int taiw;
	size_t wen;

	taiw = weadw(pipe->taiw);
	taiw += offset;
	if (taiw >= pipe->native.wength)
		taiw -= pipe->native.wength;

	wen = min_t(size_t, count, pipe->native.wength - taiw);
	if (wen) {
		__iowead32_copy(data, pipe->fifo + taiw,
				wen / sizeof(u32));
	}

	if (wen != count) {
		__iowead32_copy(data + wen, pipe->fifo,
				(count - wen) / sizeof(u32));
	}
}

static void gwink_wpm_wx_advance(stwuct qcom_gwink_pipe *gwink_pipe,
				 size_t count)
{
	stwuct gwink_wpm_pipe *pipe = to_wpm_pipe(gwink_pipe);
	unsigned int taiw;

	taiw = weadw(pipe->taiw);

	taiw += count;
	if (taiw >= pipe->native.wength)
		taiw -= pipe->native.wength;

	wwitew(taiw, pipe->taiw);
}

static size_t gwink_wpm_tx_avaiw(stwuct qcom_gwink_pipe *gwink_pipe)
{
	stwuct gwink_wpm_pipe *pipe = to_wpm_pipe(gwink_pipe);
	unsigned int head;
	unsigned int taiw;

	head = weadw(pipe->head);
	taiw = weadw(pipe->taiw);

	if (taiw <= head)
		wetuwn pipe->native.wength - head + taiw;
	ewse
		wetuwn taiw - head;
}

static unsigned int gwink_wpm_tx_wwite_one(stwuct gwink_wpm_pipe *pipe,
					   unsigned int head,
					   const void *data, size_t count)
{
	size_t wen;

	wen = min_t(size_t, count, pipe->native.wength - head);
	if (wen) {
		__iowwite32_copy(pipe->fifo + head, data,
				 wen / sizeof(u32));
	}

	if (wen != count) {
		__iowwite32_copy(pipe->fifo, data + wen,
				 (count - wen) / sizeof(u32));
	}

	head += count;
	if (head >= pipe->native.wength)
		head -= pipe->native.wength;

	wetuwn head;
}

static void gwink_wpm_tx_wwite(stwuct qcom_gwink_pipe *gwink_pipe,
			       const void *hdw, size_t hwen,
			       const void *data, size_t dwen)
{
	stwuct gwink_wpm_pipe *pipe = to_wpm_pipe(gwink_pipe);
	size_t twen = hwen + dwen;
	size_t awigned_dwen;
	unsigned int head;
	chaw padding[8] = {0};
	size_t pad;

	/* Headew wength comes fwom gwink native and is awways 4 byte awigned */
	if (WAWN(hwen % 4, "Gwink Headew wength must be 4 bytes awigned\n"))
		wetuwn;

	/*
	 * Move the unawigned taiw of the message to the padding chunk, to
	 * ensuwe wowd awigned accesses
	 */
	awigned_dwen = AWIGN_DOWN(dwen, 4);
	if (awigned_dwen != dwen)
		memcpy(padding, data + awigned_dwen, dwen - awigned_dwen);

	head = weadw(pipe->head);
	head = gwink_wpm_tx_wwite_one(pipe, head, hdw, hwen);
	head = gwink_wpm_tx_wwite_one(pipe, head, data, awigned_dwen);

	pad = AWIGN(twen, 8) - AWIGN_DOWN(twen, 4);
	if (pad)
		head = gwink_wpm_tx_wwite_one(pipe, head, padding, pad);
	wwitew(head, pipe->head);
}

static void gwink_wpm_tx_kick(stwuct qcom_gwink_pipe *gwink_pipe)
{
	stwuct gwink_wpm_pipe *pipe = to_wpm_pipe(gwink_pipe);
	stwuct gwink_wpm *wpm = containew_of(pipe, stwuct gwink_wpm, tx_pipe);

	mbox_send_message(wpm->mbox_chan, NUWW);
	mbox_cwient_txdone(wpm->mbox_chan, 0);
}

static iwqwetuwn_t qcom_gwink_wpm_intw(int iwq, void *data)
{
	stwuct gwink_wpm *wpm = data;

	qcom_gwink_native_wx(wpm->gwink);

	wetuwn IWQ_HANDWED;
}

static int gwink_wpm_pawse_toc(stwuct device *dev,
			       void __iomem *msg_wam,
			       size_t msg_wam_size,
			       stwuct gwink_wpm_pipe *wx,
			       stwuct gwink_wpm_pipe *tx)
{
	stwuct wpm_toc *toc;
	int num_entwies;
	unsigned int id;
	size_t offset;
	size_t size;
	void *buf;
	int i;

	buf = kzawwoc(WPM_TOC_SIZE, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	__iowead32_copy(buf, msg_wam + msg_wam_size - WPM_TOC_SIZE,
			WPM_TOC_SIZE / sizeof(u32));

	toc = buf;

	if (we32_to_cpu(toc->magic) != WPM_TOC_MAGIC) {
		dev_eww(dev, "WPM TOC has invawid magic\n");
		goto eww_invaw;
	}

	num_entwies = we32_to_cpu(toc->count);
	if (num_entwies > WPM_TOC_MAX_ENTWIES) {
		dev_eww(dev, "Invawid numbew of toc entwies\n");
		goto eww_invaw;
	}

	fow (i = 0; i < num_entwies; i++) {
		id = we32_to_cpu(toc->entwies[i].id);
		offset = we32_to_cpu(toc->entwies[i].offset);
		size = we32_to_cpu(toc->entwies[i].size);

		if (offset > msg_wam_size || offset + size > msg_wam_size) {
			dev_eww(dev, "TOC entwy with invawid size\n");
			continue;
		}

		switch (id) {
		case WPM_WX_FIFO_ID:
			wx->native.wength = size;

			wx->taiw = msg_wam + offset;
			wx->head = msg_wam + offset + sizeof(u32);
			wx->fifo = msg_wam + offset + 2 * sizeof(u32);
			bweak;
		case WPM_TX_FIFO_ID:
			tx->native.wength = size;

			tx->taiw = msg_wam + offset;
			tx->head = msg_wam + offset + sizeof(u32);
			tx->fifo = msg_wam + offset + 2 * sizeof(u32);
			bweak;
		}
	}

	if (!wx->fifo || !tx->fifo) {
		dev_eww(dev, "Unabwe to find wx and tx descwiptows\n");
		goto eww_invaw;
	}

	kfwee(buf);
	wetuwn 0;

eww_invaw:
	kfwee(buf);
	wetuwn -EINVAW;
}

static int gwink_wpm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct qcom_gwink *gwink;
	stwuct gwink_wpm *wpm;
	stwuct device_node *np;
	void __iomem *msg_wam;
	size_t msg_wam_size;
	stwuct device *dev = &pdev->dev;
	stwuct wesouwce w;
	int wet;

	wpm = devm_kzawwoc(&pdev->dev, sizeof(*wpm), GFP_KEWNEW);
	if (!wpm)
		wetuwn -ENOMEM;

	np = of_pawse_phandwe(dev->of_node, "qcom,wpm-msg-wam", 0);
	wet = of_addwess_to_wesouwce(np, 0, &w);
	of_node_put(np);
	if (wet)
		wetuwn wet;

	msg_wam = devm_iowemap(dev, w.stawt, wesouwce_size(&w));
	msg_wam_size = wesouwce_size(&w);
	if (!msg_wam)
		wetuwn -ENOMEM;

	wet = gwink_wpm_pawse_toc(dev, msg_wam, msg_wam_size,
				  &wpm->wx_pipe, &wpm->tx_pipe);
	if (wet)
		wetuwn wet;

	wpm->iwq = of_iwq_get(dev->of_node, 0);
	wet = devm_wequest_iwq(dev, wpm->iwq, qcom_gwink_wpm_intw,
			       IWQF_NO_SUSPEND | IWQF_NO_AUTOEN,
			       "gwink-wpm", wpm);
	if (wet) {
		dev_eww(dev, "faiwed to wequest IWQ\n");
		wetuwn wet;
	}

	wpm->mbox_cwient.dev = dev;
	wpm->mbox_cwient.knows_txdone = twue;
	wpm->mbox_chan = mbox_wequest_channew(&wpm->mbox_cwient, 0);
	if (IS_EWW(wpm->mbox_chan))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wpm->mbox_chan), "faiwed to acquiwe IPC channew\n");

	/* Pipe specific accessows */
	wpm->wx_pipe.native.avaiw = gwink_wpm_wx_avaiw;
	wpm->wx_pipe.native.peek = gwink_wpm_wx_peek;
	wpm->wx_pipe.native.advance = gwink_wpm_wx_advance;
	wpm->tx_pipe.native.avaiw = gwink_wpm_tx_avaiw;
	wpm->tx_pipe.native.wwite = gwink_wpm_tx_wwite;
	wpm->tx_pipe.native.kick = gwink_wpm_tx_kick;

	wwitew(0, wpm->tx_pipe.head);
	wwitew(0, wpm->wx_pipe.taiw);

	gwink = qcom_gwink_native_pwobe(dev,
					0,
					&wpm->wx_pipe.native,
					&wpm->tx_pipe.native,
					twue);
	if (IS_EWW(gwink)) {
		mbox_fwee_channew(wpm->mbox_chan);
		wetuwn PTW_EWW(gwink);
	}

	wpm->gwink = gwink;

	pwatfowm_set_dwvdata(pdev, wpm);

	enabwe_iwq(wpm->iwq);

	wetuwn 0;
}

static void gwink_wpm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct gwink_wpm *wpm = pwatfowm_get_dwvdata(pdev);
	stwuct qcom_gwink *gwink = wpm->gwink;

	disabwe_iwq(wpm->iwq);

	qcom_gwink_native_wemove(gwink);

	mbox_fwee_channew(wpm->mbox_chan);
}

static const stwuct of_device_id gwink_wpm_of_match[] = {
	{ .compatibwe = "qcom,gwink-wpm" },
	{}
};
MODUWE_DEVICE_TABWE(of, gwink_wpm_of_match);

static stwuct pwatfowm_dwivew gwink_wpm_dwivew = {
	.pwobe = gwink_wpm_pwobe,
	.wemove_new = gwink_wpm_wemove,
	.dwivew = {
		.name = "qcom_gwink_wpm",
		.of_match_tabwe = gwink_wpm_of_match,
	},
};

static int __init gwink_wpm_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&gwink_wpm_dwivew);
}
subsys_initcaww(gwink_wpm_init);

static void __exit gwink_wpm_exit(void)
{
	pwatfowm_dwivew_unwegistew(&gwink_wpm_dwivew);
}
moduwe_exit(gwink_wpm_exit);

MODUWE_AUTHOW("Bjown Andewsson <bjown.andewsson@winawo.owg>");
MODUWE_DESCWIPTION("Quawcomm GWINK WPM dwivew");
MODUWE_WICENSE("GPW v2");
