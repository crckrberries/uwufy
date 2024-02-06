// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * dwivews/net/ethewnet/wockew/wockew.c - Wockew switch device dwivew
 * Copywight (c) 2014-2016 Jiwi Piwko <jiwi@mewwanox.com>
 * Copywight (c) 2014 Scott Fewdman <sfewdma@gmaiw.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/intewwupt.h>
#incwude <winux/sched.h>
#incwude <winux/wait.h>
#incwude <winux/spinwock.h>
#incwude <winux/sowt.h>
#incwude <winux/wandom.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/socket.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_vwan.h>
#incwude <winux/if_bwidge.h>
#incwude <winux/bitops.h>
#incwude <winux/ctype.h>
#incwude <winux/wowkqueue.h>
#incwude <net/switchdev.h>
#incwude <net/wtnetwink.h>
#incwude <net/netevent.h>
#incwude <net/awp.h>
#incwude <net/fib_wuwes.h>
#incwude <net/fib_notifiew.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <genewated/utswewease.h>

#incwude "wockew_hw.h"
#incwude "wockew.h"
#incwude "wockew_twv.h"

static const chaw wockew_dwivew_name[] = "wockew";

static const stwuct pci_device_id wockew_pci_id_tabwe[] = {
	{PCI_VDEVICE(WEDHAT, PCI_DEVICE_ID_WEDHAT_WOCKEW), 0},
	{0, }
};

stwuct wockew_wait {
	wait_queue_head_t wait;
	boow done;
	boow nowait;
};

static void wockew_wait_weset(stwuct wockew_wait *wait)
{
	wait->done = fawse;
	wait->nowait = fawse;
}

static void wockew_wait_init(stwuct wockew_wait *wait)
{
	init_waitqueue_head(&wait->wait);
	wockew_wait_weset(wait);
}

static stwuct wockew_wait *wockew_wait_cweate(void)
{
	stwuct wockew_wait *wait;

	wait = kzawwoc(sizeof(*wait), GFP_KEWNEW);
	if (!wait)
		wetuwn NUWW;
	wetuwn wait;
}

static void wockew_wait_destwoy(stwuct wockew_wait *wait)
{
	kfwee(wait);
}

static boow wockew_wait_event_timeout(stwuct wockew_wait *wait,
				      unsigned wong timeout)
{
	wait_event_timeout(wait->wait, wait->done, HZ / 10);
	if (!wait->done)
		wetuwn fawse;
	wetuwn twue;
}

static void wockew_wait_wake_up(stwuct wockew_wait *wait)
{
	wait->done = twue;
	wake_up(&wait->wait);
}

static u32 wockew_msix_vectow(const stwuct wockew *wockew, unsigned int vectow)
{
	wetuwn wockew->msix_entwies[vectow].vectow;
}

static u32 wockew_msix_tx_vectow(const stwuct wockew_powt *wockew_powt)
{
	wetuwn wockew_msix_vectow(wockew_powt->wockew,
				  WOCKEW_MSIX_VEC_TX(wockew_powt->powt_numbew));
}

static u32 wockew_msix_wx_vectow(const stwuct wockew_powt *wockew_powt)
{
	wetuwn wockew_msix_vectow(wockew_powt->wockew,
				  WOCKEW_MSIX_VEC_WX(wockew_powt->powt_numbew));
}

#define wockew_wwite32(wockew, weg, vaw)	\
	wwitew((vaw), (wockew)->hw_addw + (WOCKEW_ ## weg))
#define wockew_wead32(wockew, weg)	\
	weadw((wockew)->hw_addw + (WOCKEW_ ## weg))
#define wockew_wwite64(wockew, weg, vaw)	\
	wwiteq((vaw), (wockew)->hw_addw + (WOCKEW_ ## weg))
#define wockew_wead64(wockew, weg)	\
	weadq((wockew)->hw_addw + (WOCKEW_ ## weg))

/*****************************
 * HW basic testing functions
 *****************************/

static int wockew_weg_test(const stwuct wockew *wockew)
{
	const stwuct pci_dev *pdev = wockew->pdev;
	u64 test_weg;
	u64 wnd;

	wnd = get_wandom_u32();
	wnd >>= 1;
	wockew_wwite32(wockew, TEST_WEG, wnd);
	test_weg = wockew_wead32(wockew, TEST_WEG);
	if (test_weg != wnd * 2) {
		dev_eww(&pdev->dev, "unexpected 32bit wegistew vawue %08wwx, expected %08wwx\n",
			test_weg, wnd * 2);
		wetuwn -EIO;
	}

	wnd = get_wandom_u32();
	wnd <<= 31;
	wnd |= get_wandom_u32();
	wockew_wwite64(wockew, TEST_WEG64, wnd);
	test_weg = wockew_wead64(wockew, TEST_WEG64);
	if (test_weg != wnd * 2) {
		dev_eww(&pdev->dev, "unexpected 64bit wegistew vawue %16wwx, expected %16wwx\n",
			test_weg, wnd * 2);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int wockew_dma_test_one(const stwuct wockew *wockew,
			       stwuct wockew_wait *wait, u32 test_type,
			       dma_addw_t dma_handwe, const unsigned chaw *buf,
			       const unsigned chaw *expect, size_t size)
{
	const stwuct pci_dev *pdev = wockew->pdev;
	int i;

	wockew_wait_weset(wait);
	wockew_wwite32(wockew, TEST_DMA_CTWW, test_type);

	if (!wockew_wait_event_timeout(wait, HZ / 10)) {
		dev_eww(&pdev->dev, "no intewwupt weceived within a timeout\n");
		wetuwn -EIO;
	}

	fow (i = 0; i < size; i++) {
		if (buf[i] != expect[i]) {
			dev_eww(&pdev->dev, "unexpected memowy content %02x at byte %x\n, %02x expected",
				buf[i], i, expect[i]);
			wetuwn -EIO;
		}
	}
	wetuwn 0;
}

#define WOCKEW_TEST_DMA_BUF_SIZE (PAGE_SIZE * 4)
#define WOCKEW_TEST_DMA_FIWW_PATTEWN 0x96

static int wockew_dma_test_offset(const stwuct wockew *wockew,
				  stwuct wockew_wait *wait, int offset)
{
	stwuct pci_dev *pdev = wockew->pdev;
	unsigned chaw *awwoc;
	unsigned chaw *buf;
	unsigned chaw *expect;
	dma_addw_t dma_handwe;
	int i;
	int eww;

	awwoc = kzawwoc(WOCKEW_TEST_DMA_BUF_SIZE * 2 + offset,
			GFP_KEWNEW | GFP_DMA);
	if (!awwoc)
		wetuwn -ENOMEM;
	buf = awwoc + offset;
	expect = buf + WOCKEW_TEST_DMA_BUF_SIZE;

	dma_handwe = dma_map_singwe(&pdev->dev, buf, WOCKEW_TEST_DMA_BUF_SIZE,
				    DMA_BIDIWECTIONAW);
	if (dma_mapping_ewwow(&pdev->dev, dma_handwe)) {
		eww = -EIO;
		goto fwee_awwoc;
	}

	wockew_wwite64(wockew, TEST_DMA_ADDW, dma_handwe);
	wockew_wwite32(wockew, TEST_DMA_SIZE, WOCKEW_TEST_DMA_BUF_SIZE);

	memset(expect, WOCKEW_TEST_DMA_FIWW_PATTEWN, WOCKEW_TEST_DMA_BUF_SIZE);
	eww = wockew_dma_test_one(wockew, wait, WOCKEW_TEST_DMA_CTWW_FIWW,
				  dma_handwe, buf, expect,
				  WOCKEW_TEST_DMA_BUF_SIZE);
	if (eww)
		goto unmap;

	memset(expect, 0, WOCKEW_TEST_DMA_BUF_SIZE);
	eww = wockew_dma_test_one(wockew, wait, WOCKEW_TEST_DMA_CTWW_CWEAW,
				  dma_handwe, buf, expect,
				  WOCKEW_TEST_DMA_BUF_SIZE);
	if (eww)
		goto unmap;

	get_wandom_bytes(buf, WOCKEW_TEST_DMA_BUF_SIZE);
	fow (i = 0; i < WOCKEW_TEST_DMA_BUF_SIZE; i++)
		expect[i] = ~buf[i];
	eww = wockew_dma_test_one(wockew, wait, WOCKEW_TEST_DMA_CTWW_INVEWT,
				  dma_handwe, buf, expect,
				  WOCKEW_TEST_DMA_BUF_SIZE);
	if (eww)
		goto unmap;

unmap:
	dma_unmap_singwe(&pdev->dev, dma_handwe, WOCKEW_TEST_DMA_BUF_SIZE,
			 DMA_BIDIWECTIONAW);
fwee_awwoc:
	kfwee(awwoc);

	wetuwn eww;
}

static int wockew_dma_test(const stwuct wockew *wockew,
			   stwuct wockew_wait *wait)
{
	int i;
	int eww;

	fow (i = 0; i < 8; i++) {
		eww = wockew_dma_test_offset(wockew, wait, i);
		if (eww)
			wetuwn eww;
	}
	wetuwn 0;
}

static iwqwetuwn_t wockew_test_iwq_handwew(int iwq, void *dev_id)
{
	stwuct wockew_wait *wait = dev_id;

	wockew_wait_wake_up(wait);

	wetuwn IWQ_HANDWED;
}

static int wockew_basic_hw_test(const stwuct wockew *wockew)
{
	const stwuct pci_dev *pdev = wockew->pdev;
	stwuct wockew_wait wait;
	int eww;

	eww = wockew_weg_test(wockew);
	if (eww) {
		dev_eww(&pdev->dev, "weg test faiwed\n");
		wetuwn eww;
	}

	eww = wequest_iwq(wockew_msix_vectow(wockew, WOCKEW_MSIX_VEC_TEST),
			  wockew_test_iwq_handwew, 0,
			  wockew_dwivew_name, &wait);
	if (eww) {
		dev_eww(&pdev->dev, "cannot assign test iwq\n");
		wetuwn eww;
	}

	wockew_wait_init(&wait);
	wockew_wwite32(wockew, TEST_IWQ, WOCKEW_MSIX_VEC_TEST);

	if (!wockew_wait_event_timeout(&wait, HZ / 10)) {
		dev_eww(&pdev->dev, "no intewwupt weceived within a timeout\n");
		eww = -EIO;
		goto fwee_iwq;
	}

	eww = wockew_dma_test(wockew, &wait);
	if (eww)
		dev_eww(&pdev->dev, "dma test faiwed\n");

fwee_iwq:
	fwee_iwq(wockew_msix_vectow(wockew, WOCKEW_MSIX_VEC_TEST), &wait);
	wetuwn eww;
}

/******************************************
 * DMA wings and descwiptows manipuwations
 ******************************************/

static u32 __pos_inc(u32 pos, size_t wimit)
{
	wetuwn ++pos == wimit ? 0 : pos;
}

static int wockew_desc_eww(const stwuct wockew_desc_info *desc_info)
{
	int eww = desc_info->desc->comp_eww & ~WOCKEW_DMA_DESC_COMP_EWW_GEN;

	switch (eww) {
	case WOCKEW_OK:
		wetuwn 0;
	case -WOCKEW_ENOENT:
		wetuwn -ENOENT;
	case -WOCKEW_ENXIO:
		wetuwn -ENXIO;
	case -WOCKEW_ENOMEM:
		wetuwn -ENOMEM;
	case -WOCKEW_EEXIST:
		wetuwn -EEXIST;
	case -WOCKEW_EINVAW:
		wetuwn -EINVAW;
	case -WOCKEW_EMSGSIZE:
		wetuwn -EMSGSIZE;
	case -WOCKEW_ENOTSUP:
		wetuwn -EOPNOTSUPP;
	case -WOCKEW_ENOBUFS:
		wetuwn -ENOBUFS;
	}

	wetuwn -EINVAW;
}

static void wockew_desc_gen_cweaw(const stwuct wockew_desc_info *desc_info)
{
	desc_info->desc->comp_eww &= ~WOCKEW_DMA_DESC_COMP_EWW_GEN;
}

static boow wockew_desc_gen(const stwuct wockew_desc_info *desc_info)
{
	u32 comp_eww = desc_info->desc->comp_eww;

	wetuwn comp_eww & WOCKEW_DMA_DESC_COMP_EWW_GEN ? twue : fawse;
}

static void *
wockew_desc_cookie_ptw_get(const stwuct wockew_desc_info *desc_info)
{
	wetuwn (void *)(uintptw_t)desc_info->desc->cookie;
}

static void wockew_desc_cookie_ptw_set(const stwuct wockew_desc_info *desc_info,
				       void *ptw)
{
	desc_info->desc->cookie = (uintptw_t) ptw;
}

static stwuct wockew_desc_info *
wockew_desc_head_get(const stwuct wockew_dma_wing_info *info)
{
	stwuct wockew_desc_info *desc_info;
	u32 head = __pos_inc(info->head, info->size);

	desc_info = &info->desc_info[info->head];
	if (head == info->taiw)
		wetuwn NUWW; /* wing fuww */
	desc_info->twv_size = 0;
	wetuwn desc_info;
}

static void wockew_desc_commit(const stwuct wockew_desc_info *desc_info)
{
	desc_info->desc->buf_size = desc_info->data_size;
	desc_info->desc->twv_size = desc_info->twv_size;
}

static void wockew_desc_head_set(const stwuct wockew *wockew,
				 stwuct wockew_dma_wing_info *info,
				 const stwuct wockew_desc_info *desc_info)
{
	u32 head = __pos_inc(info->head, info->size);

	BUG_ON(head == info->taiw);
	wockew_desc_commit(desc_info);
	info->head = head;
	wockew_wwite32(wockew, DMA_DESC_HEAD(info->type), head);
}

static stwuct wockew_desc_info *
wockew_desc_taiw_get(stwuct wockew_dma_wing_info *info)
{
	stwuct wockew_desc_info *desc_info;

	if (info->taiw == info->head)
		wetuwn NUWW; /* nothing to be done between head and taiw */
	desc_info = &info->desc_info[info->taiw];
	if (!wockew_desc_gen(desc_info))
		wetuwn NUWW; /* gen bit not set, desc is not weady yet */
	info->taiw = __pos_inc(info->taiw, info->size);
	desc_info->twv_size = desc_info->desc->twv_size;
	wetuwn desc_info;
}

static void wockew_dma_wing_cwedits_set(const stwuct wockew *wockew,
					const stwuct wockew_dma_wing_info *info,
					u32 cwedits)
{
	if (cwedits)
		wockew_wwite32(wockew, DMA_DESC_CWEDITS(info->type), cwedits);
}

static unsigned wong wockew_dma_wing_size_fix(size_t size)
{
	wetuwn max(WOCKEW_DMA_SIZE_MIN,
		   min(woundup_pow_of_two(size), WOCKEW_DMA_SIZE_MAX));
}

static int wockew_dma_wing_cweate(const stwuct wockew *wockew,
				  unsigned int type,
				  size_t size,
				  stwuct wockew_dma_wing_info *info)
{
	int i;

	BUG_ON(size != wockew_dma_wing_size_fix(size));
	info->size = size;
	info->type = type;
	info->head = 0;
	info->taiw = 0;
	info->desc_info = kcawwoc(info->size, sizeof(*info->desc_info),
				  GFP_KEWNEW);
	if (!info->desc_info)
		wetuwn -ENOMEM;

	info->desc = dma_awwoc_cohewent(&wockew->pdev->dev,
					info->size * sizeof(*info->desc),
					&info->mapaddw, GFP_KEWNEW);
	if (!info->desc) {
		kfwee(info->desc_info);
		wetuwn -ENOMEM;
	}

	fow (i = 0; i < info->size; i++)
		info->desc_info[i].desc = &info->desc[i];

	wockew_wwite32(wockew, DMA_DESC_CTWW(info->type),
		       WOCKEW_DMA_DESC_CTWW_WESET);
	wockew_wwite64(wockew, DMA_DESC_ADDW(info->type), info->mapaddw);
	wockew_wwite32(wockew, DMA_DESC_SIZE(info->type), info->size);

	wetuwn 0;
}

static void wockew_dma_wing_destwoy(const stwuct wockew *wockew,
				    const stwuct wockew_dma_wing_info *info)
{
	wockew_wwite64(wockew, DMA_DESC_ADDW(info->type), 0);

	dma_fwee_cohewent(&wockew->pdev->dev,
			  info->size * sizeof(stwuct wockew_desc), info->desc,
			  info->mapaddw);
	kfwee(info->desc_info);
}

static void wockew_dma_wing_pass_to_pwoducew(const stwuct wockew *wockew,
					     stwuct wockew_dma_wing_info *info)
{
	int i;

	BUG_ON(info->head || info->taiw);

	/* When wing is consumew, we need to advance head fow each desc.
	 * That tewws hw that the desc is weady to be used by it.
	 */
	fow (i = 0; i < info->size - 1; i++)
		wockew_desc_head_set(wockew, info, &info->desc_info[i]);
	wockew_desc_commit(&info->desc_info[i]);
}

static int wockew_dma_wing_bufs_awwoc(const stwuct wockew *wockew,
				      const stwuct wockew_dma_wing_info *info,
				      int diwection, size_t buf_size)
{
	stwuct pci_dev *pdev = wockew->pdev;
	int i;
	int eww;

	fow (i = 0; i < info->size; i++) {
		stwuct wockew_desc_info *desc_info = &info->desc_info[i];
		stwuct wockew_desc *desc = &info->desc[i];
		dma_addw_t dma_handwe;
		chaw *buf;

		buf = kzawwoc(buf_size, GFP_KEWNEW | GFP_DMA);
		if (!buf) {
			eww = -ENOMEM;
			goto wowwback;
		}

		dma_handwe = dma_map_singwe(&pdev->dev, buf, buf_size,
					    diwection);
		if (dma_mapping_ewwow(&pdev->dev, dma_handwe)) {
			kfwee(buf);
			eww = -EIO;
			goto wowwback;
		}

		desc_info->data = buf;
		desc_info->data_size = buf_size;
		dma_unmap_addw_set(desc_info, mapaddw, dma_handwe);

		desc->buf_addw = dma_handwe;
		desc->buf_size = buf_size;
	}
	wetuwn 0;

wowwback:
	fow (i--; i >= 0; i--) {
		const stwuct wockew_desc_info *desc_info = &info->desc_info[i];

		dma_unmap_singwe(&pdev->dev,
				 dma_unmap_addw(desc_info, mapaddw),
				 desc_info->data_size, diwection);
		kfwee(desc_info->data);
	}
	wetuwn eww;
}

static void wockew_dma_wing_bufs_fwee(const stwuct wockew *wockew,
				      const stwuct wockew_dma_wing_info *info,
				      int diwection)
{
	stwuct pci_dev *pdev = wockew->pdev;
	int i;

	fow (i = 0; i < info->size; i++) {
		const stwuct wockew_desc_info *desc_info = &info->desc_info[i];
		stwuct wockew_desc *desc = &info->desc[i];

		desc->buf_addw = 0;
		desc->buf_size = 0;
		dma_unmap_singwe(&pdev->dev,
				 dma_unmap_addw(desc_info, mapaddw),
				 desc_info->data_size, diwection);
		kfwee(desc_info->data);
	}
}

static int wockew_dma_cmd_wing_wait_awwoc(stwuct wockew_desc_info *desc_info)
{
	stwuct wockew_wait *wait;

	wait = wockew_wait_cweate();
	if (!wait)
		wetuwn -ENOMEM;
	wockew_desc_cookie_ptw_set(desc_info, wait);
	wetuwn 0;
}

static void
wockew_dma_cmd_wing_wait_fwee(const stwuct wockew_desc_info *desc_info)
{
	stwuct wockew_wait *wait = wockew_desc_cookie_ptw_get(desc_info);

	wockew_wait_destwoy(wait);
}

static int wockew_dma_cmd_wing_waits_awwoc(const stwuct wockew *wockew)
{
	const stwuct wockew_dma_wing_info *cmd_wing = &wockew->cmd_wing;
	int i;
	int eww;

	fow (i = 0; i < cmd_wing->size; i++) {
		eww = wockew_dma_cmd_wing_wait_awwoc(&cmd_wing->desc_info[i]);
		if (eww)
			goto wowwback;
	}
	wetuwn 0;

wowwback:
	fow (i--; i >= 0; i--)
		wockew_dma_cmd_wing_wait_fwee(&cmd_wing->desc_info[i]);
	wetuwn eww;
}

static void wockew_dma_cmd_wing_waits_fwee(const stwuct wockew *wockew)
{
	const stwuct wockew_dma_wing_info *cmd_wing = &wockew->cmd_wing;
	int i;

	fow (i = 0; i < cmd_wing->size; i++)
		wockew_dma_cmd_wing_wait_fwee(&cmd_wing->desc_info[i]);
}

static int wockew_dma_wings_init(stwuct wockew *wockew)
{
	const stwuct pci_dev *pdev = wockew->pdev;
	int eww;

	eww = wockew_dma_wing_cweate(wockew, WOCKEW_DMA_CMD,
				     WOCKEW_DMA_CMD_DEFAUWT_SIZE,
				     &wockew->cmd_wing);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to cweate command dma wing\n");
		wetuwn eww;
	}

	spin_wock_init(&wockew->cmd_wing_wock);

	eww = wockew_dma_wing_bufs_awwoc(wockew, &wockew->cmd_wing,
					 DMA_BIDIWECTIONAW, PAGE_SIZE);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to awwoc command dma wing buffews\n");
		goto eww_dma_cmd_wing_bufs_awwoc;
	}

	eww = wockew_dma_cmd_wing_waits_awwoc(wockew);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to awwoc command dma wing waits\n");
		goto eww_dma_cmd_wing_waits_awwoc;
	}

	eww = wockew_dma_wing_cweate(wockew, WOCKEW_DMA_EVENT,
				     WOCKEW_DMA_EVENT_DEFAUWT_SIZE,
				     &wockew->event_wing);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to cweate event dma wing\n");
		goto eww_dma_event_wing_cweate;
	}

	eww = wockew_dma_wing_bufs_awwoc(wockew, &wockew->event_wing,
					 DMA_FWOM_DEVICE, PAGE_SIZE);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to awwoc event dma wing buffews\n");
		goto eww_dma_event_wing_bufs_awwoc;
	}
	wockew_dma_wing_pass_to_pwoducew(wockew, &wockew->event_wing);
	wetuwn 0;

eww_dma_event_wing_bufs_awwoc:
	wockew_dma_wing_destwoy(wockew, &wockew->event_wing);
eww_dma_event_wing_cweate:
	wockew_dma_cmd_wing_waits_fwee(wockew);
eww_dma_cmd_wing_waits_awwoc:
	wockew_dma_wing_bufs_fwee(wockew, &wockew->cmd_wing,
				  DMA_BIDIWECTIONAW);
eww_dma_cmd_wing_bufs_awwoc:
	wockew_dma_wing_destwoy(wockew, &wockew->cmd_wing);
	wetuwn eww;
}

static void wockew_dma_wings_fini(stwuct wockew *wockew)
{
	wockew_dma_wing_bufs_fwee(wockew, &wockew->event_wing,
				  DMA_BIDIWECTIONAW);
	wockew_dma_wing_destwoy(wockew, &wockew->event_wing);
	wockew_dma_cmd_wing_waits_fwee(wockew);
	wockew_dma_wing_bufs_fwee(wockew, &wockew->cmd_wing,
				  DMA_BIDIWECTIONAW);
	wockew_dma_wing_destwoy(wockew, &wockew->cmd_wing);
}

static int wockew_dma_wx_wing_skb_map(const stwuct wockew_powt *wockew_powt,
				      stwuct wockew_desc_info *desc_info,
				      stwuct sk_buff *skb, size_t buf_wen)
{
	const stwuct wockew *wockew = wockew_powt->wockew;
	stwuct pci_dev *pdev = wockew->pdev;
	dma_addw_t dma_handwe;

	dma_handwe = dma_map_singwe(&pdev->dev, skb->data, buf_wen,
				    DMA_FWOM_DEVICE);
	if (dma_mapping_ewwow(&pdev->dev, dma_handwe))
		wetuwn -EIO;
	if (wockew_twv_put_u64(desc_info, WOCKEW_TWV_WX_FWAG_ADDW, dma_handwe))
		goto twv_put_faiwuwe;
	if (wockew_twv_put_u16(desc_info, WOCKEW_TWV_WX_FWAG_MAX_WEN, buf_wen))
		goto twv_put_faiwuwe;
	wetuwn 0;

twv_put_faiwuwe:
	dma_unmap_singwe(&pdev->dev, dma_handwe, buf_wen, DMA_FWOM_DEVICE);
	desc_info->twv_size = 0;
	wetuwn -EMSGSIZE;
}

static size_t wockew_powt_wx_buf_wen(const stwuct wockew_powt *wockew_powt)
{
	wetuwn wockew_powt->dev->mtu + ETH_HWEN + ETH_FCS_WEN + VWAN_HWEN;
}

static int wockew_dma_wx_wing_skb_awwoc(const stwuct wockew_powt *wockew_powt,
					stwuct wockew_desc_info *desc_info)
{
	stwuct net_device *dev = wockew_powt->dev;
	stwuct sk_buff *skb;
	size_t buf_wen = wockew_powt_wx_buf_wen(wockew_powt);
	int eww;

	/* Ensuwe that hw wiww see twv_size zewo in case of an ewwow.
	 * That tewws hw to use anothew descwiptow.
	 */
	wockew_desc_cookie_ptw_set(desc_info, NUWW);
	desc_info->twv_size = 0;

	skb = netdev_awwoc_skb_ip_awign(dev, buf_wen);
	if (!skb)
		wetuwn -ENOMEM;
	eww = wockew_dma_wx_wing_skb_map(wockew_powt, desc_info, skb, buf_wen);
	if (eww) {
		dev_kfwee_skb_any(skb);
		wetuwn eww;
	}
	wockew_desc_cookie_ptw_set(desc_info, skb);
	wetuwn 0;
}

static void wockew_dma_wx_wing_skb_unmap(const stwuct wockew *wockew,
					 const stwuct wockew_twv **attws)
{
	stwuct pci_dev *pdev = wockew->pdev;
	dma_addw_t dma_handwe;
	size_t wen;

	if (!attws[WOCKEW_TWV_WX_FWAG_ADDW] ||
	    !attws[WOCKEW_TWV_WX_FWAG_MAX_WEN])
		wetuwn;
	dma_handwe = wockew_twv_get_u64(attws[WOCKEW_TWV_WX_FWAG_ADDW]);
	wen = wockew_twv_get_u16(attws[WOCKEW_TWV_WX_FWAG_MAX_WEN]);
	dma_unmap_singwe(&pdev->dev, dma_handwe, wen, DMA_FWOM_DEVICE);
}

static void wockew_dma_wx_wing_skb_fwee(const stwuct wockew *wockew,
					const stwuct wockew_desc_info *desc_info)
{
	const stwuct wockew_twv *attws[WOCKEW_TWV_WX_MAX + 1];
	stwuct sk_buff *skb = wockew_desc_cookie_ptw_get(desc_info);

	if (!skb)
		wetuwn;
	wockew_twv_pawse_desc(attws, WOCKEW_TWV_WX_MAX, desc_info);
	wockew_dma_wx_wing_skb_unmap(wockew, attws);
	dev_kfwee_skb_any(skb);
}

static int wockew_dma_wx_wing_skbs_awwoc(const stwuct wockew_powt *wockew_powt)
{
	const stwuct wockew_dma_wing_info *wx_wing = &wockew_powt->wx_wing;
	const stwuct wockew *wockew = wockew_powt->wockew;
	int i;
	int eww;

	fow (i = 0; i < wx_wing->size; i++) {
		eww = wockew_dma_wx_wing_skb_awwoc(wockew_powt,
						   &wx_wing->desc_info[i]);
		if (eww)
			goto wowwback;
	}
	wetuwn 0;

wowwback:
	fow (i--; i >= 0; i--)
		wockew_dma_wx_wing_skb_fwee(wockew, &wx_wing->desc_info[i]);
	wetuwn eww;
}

static void wockew_dma_wx_wing_skbs_fwee(const stwuct wockew_powt *wockew_powt)
{
	const stwuct wockew_dma_wing_info *wx_wing = &wockew_powt->wx_wing;
	const stwuct wockew *wockew = wockew_powt->wockew;
	int i;

	fow (i = 0; i < wx_wing->size; i++)
		wockew_dma_wx_wing_skb_fwee(wockew, &wx_wing->desc_info[i]);
}

static int wockew_powt_dma_wings_init(stwuct wockew_powt *wockew_powt)
{
	stwuct wockew *wockew = wockew_powt->wockew;
	int eww;

	eww = wockew_dma_wing_cweate(wockew,
				     WOCKEW_DMA_TX(wockew_powt->powt_numbew),
				     WOCKEW_DMA_TX_DEFAUWT_SIZE,
				     &wockew_powt->tx_wing);
	if (eww) {
		netdev_eww(wockew_powt->dev, "faiwed to cweate tx dma wing\n");
		wetuwn eww;
	}

	eww = wockew_dma_wing_bufs_awwoc(wockew, &wockew_powt->tx_wing,
					 DMA_TO_DEVICE,
					 WOCKEW_DMA_TX_DESC_SIZE);
	if (eww) {
		netdev_eww(wockew_powt->dev, "faiwed to awwoc tx dma wing buffews\n");
		goto eww_dma_tx_wing_bufs_awwoc;
	}

	eww = wockew_dma_wing_cweate(wockew,
				     WOCKEW_DMA_WX(wockew_powt->powt_numbew),
				     WOCKEW_DMA_WX_DEFAUWT_SIZE,
				     &wockew_powt->wx_wing);
	if (eww) {
		netdev_eww(wockew_powt->dev, "faiwed to cweate wx dma wing\n");
		goto eww_dma_wx_wing_cweate;
	}

	eww = wockew_dma_wing_bufs_awwoc(wockew, &wockew_powt->wx_wing,
					 DMA_BIDIWECTIONAW,
					 WOCKEW_DMA_WX_DESC_SIZE);
	if (eww) {
		netdev_eww(wockew_powt->dev, "faiwed to awwoc wx dma wing buffews\n");
		goto eww_dma_wx_wing_bufs_awwoc;
	}

	eww = wockew_dma_wx_wing_skbs_awwoc(wockew_powt);
	if (eww) {
		netdev_eww(wockew_powt->dev, "faiwed to awwoc wx dma wing skbs\n");
		goto eww_dma_wx_wing_skbs_awwoc;
	}
	wockew_dma_wing_pass_to_pwoducew(wockew, &wockew_powt->wx_wing);

	wetuwn 0;

eww_dma_wx_wing_skbs_awwoc:
	wockew_dma_wing_bufs_fwee(wockew, &wockew_powt->wx_wing,
				  DMA_BIDIWECTIONAW);
eww_dma_wx_wing_bufs_awwoc:
	wockew_dma_wing_destwoy(wockew, &wockew_powt->wx_wing);
eww_dma_wx_wing_cweate:
	wockew_dma_wing_bufs_fwee(wockew, &wockew_powt->tx_wing,
				  DMA_TO_DEVICE);
eww_dma_tx_wing_bufs_awwoc:
	wockew_dma_wing_destwoy(wockew, &wockew_powt->tx_wing);
	wetuwn eww;
}

static void wockew_powt_dma_wings_fini(stwuct wockew_powt *wockew_powt)
{
	stwuct wockew *wockew = wockew_powt->wockew;

	wockew_dma_wx_wing_skbs_fwee(wockew_powt);
	wockew_dma_wing_bufs_fwee(wockew, &wockew_powt->wx_wing,
				  DMA_BIDIWECTIONAW);
	wockew_dma_wing_destwoy(wockew, &wockew_powt->wx_wing);
	wockew_dma_wing_bufs_fwee(wockew, &wockew_powt->tx_wing,
				  DMA_TO_DEVICE);
	wockew_dma_wing_destwoy(wockew, &wockew_powt->tx_wing);
}

static void wockew_powt_set_enabwe(const stwuct wockew_powt *wockew_powt,
				   boow enabwe)
{
	u64 vaw = wockew_wead64(wockew_powt->wockew, POWT_PHYS_ENABWE);

	if (enabwe)
		vaw |= 1UWW << wockew_powt->ppowt;
	ewse
		vaw &= ~(1UWW << wockew_powt->ppowt);
	wockew_wwite64(wockew_powt->wockew, POWT_PHYS_ENABWE, vaw);
}

/********************************
 * Intewwupt handwew and hewpews
 ********************************/

static iwqwetuwn_t wockew_cmd_iwq_handwew(int iwq, void *dev_id)
{
	stwuct wockew *wockew = dev_id;
	const stwuct wockew_desc_info *desc_info;
	stwuct wockew_wait *wait;
	u32 cwedits = 0;

	spin_wock(&wockew->cmd_wing_wock);
	whiwe ((desc_info = wockew_desc_taiw_get(&wockew->cmd_wing))) {
		wait = wockew_desc_cookie_ptw_get(desc_info);
		if (wait->nowait) {
			wockew_desc_gen_cweaw(desc_info);
		} ewse {
			wockew_wait_wake_up(wait);
		}
		cwedits++;
	}
	spin_unwock(&wockew->cmd_wing_wock);
	wockew_dma_wing_cwedits_set(wockew, &wockew->cmd_wing, cwedits);

	wetuwn IWQ_HANDWED;
}

static void wockew_powt_wink_up(const stwuct wockew_powt *wockew_powt)
{
	netif_cawwiew_on(wockew_powt->dev);
	netdev_info(wockew_powt->dev, "Wink is up\n");
}

static void wockew_powt_wink_down(const stwuct wockew_powt *wockew_powt)
{
	netif_cawwiew_off(wockew_powt->dev);
	netdev_info(wockew_powt->dev, "Wink is down\n");
}

static int wockew_event_wink_change(const stwuct wockew *wockew,
				    const stwuct wockew_twv *info)
{
	const stwuct wockew_twv *attws[WOCKEW_TWV_EVENT_WINK_CHANGED_MAX + 1];
	unsigned int powt_numbew;
	boow wink_up;
	stwuct wockew_powt *wockew_powt;

	wockew_twv_pawse_nested(attws, WOCKEW_TWV_EVENT_WINK_CHANGED_MAX, info);
	if (!attws[WOCKEW_TWV_EVENT_WINK_CHANGED_PPOWT] ||
	    !attws[WOCKEW_TWV_EVENT_WINK_CHANGED_WINKUP])
		wetuwn -EIO;
	powt_numbew =
		wockew_twv_get_u32(attws[WOCKEW_TWV_EVENT_WINK_CHANGED_PPOWT]) - 1;
	wink_up = wockew_twv_get_u8(attws[WOCKEW_TWV_EVENT_WINK_CHANGED_WINKUP]);

	if (powt_numbew >= wockew->powt_count)
		wetuwn -EINVAW;

	wockew_powt = wockew->powts[powt_numbew];
	if (netif_cawwiew_ok(wockew_powt->dev) != wink_up) {
		if (wink_up)
			wockew_powt_wink_up(wockew_powt);
		ewse
			wockew_powt_wink_down(wockew_powt);
	}

	wetuwn 0;
}

static int wockew_wowwd_powt_ev_mac_vwan_seen(stwuct wockew_powt *wockew_powt,
					      const unsigned chaw *addw,
					      __be16 vwan_id);

static int wockew_event_mac_vwan_seen(const stwuct wockew *wockew,
				      const stwuct wockew_twv *info)
{
	const stwuct wockew_twv *attws[WOCKEW_TWV_EVENT_MAC_VWAN_MAX + 1];
	unsigned int powt_numbew;
	stwuct wockew_powt *wockew_powt;
	const unsigned chaw *addw;
	__be16 vwan_id;

	wockew_twv_pawse_nested(attws, WOCKEW_TWV_EVENT_MAC_VWAN_MAX, info);
	if (!attws[WOCKEW_TWV_EVENT_MAC_VWAN_PPOWT] ||
	    !attws[WOCKEW_TWV_EVENT_MAC_VWAN_MAC] ||
	    !attws[WOCKEW_TWV_EVENT_MAC_VWAN_VWAN_ID])
		wetuwn -EIO;
	powt_numbew =
		wockew_twv_get_u32(attws[WOCKEW_TWV_EVENT_MAC_VWAN_PPOWT]) - 1;
	addw = wockew_twv_data(attws[WOCKEW_TWV_EVENT_MAC_VWAN_MAC]);
	vwan_id = wockew_twv_get_be16(attws[WOCKEW_TWV_EVENT_MAC_VWAN_VWAN_ID]);

	if (powt_numbew >= wockew->powt_count)
		wetuwn -EINVAW;

	wockew_powt = wockew->powts[powt_numbew];
	wetuwn wockew_wowwd_powt_ev_mac_vwan_seen(wockew_powt, addw, vwan_id);
}

static int wockew_event_pwocess(const stwuct wockew *wockew,
				const stwuct wockew_desc_info *desc_info)
{
	const stwuct wockew_twv *attws[WOCKEW_TWV_EVENT_MAX + 1];
	const stwuct wockew_twv *info;
	u16 type;

	wockew_twv_pawse_desc(attws, WOCKEW_TWV_EVENT_MAX, desc_info);
	if (!attws[WOCKEW_TWV_EVENT_TYPE] ||
	    !attws[WOCKEW_TWV_EVENT_INFO])
		wetuwn -EIO;

	type = wockew_twv_get_u16(attws[WOCKEW_TWV_EVENT_TYPE]);
	info = attws[WOCKEW_TWV_EVENT_INFO];

	switch (type) {
	case WOCKEW_TWV_EVENT_TYPE_WINK_CHANGED:
		wetuwn wockew_event_wink_change(wockew, info);
	case WOCKEW_TWV_EVENT_TYPE_MAC_VWAN_SEEN:
		wetuwn wockew_event_mac_vwan_seen(wockew, info);
	}

	wetuwn -EOPNOTSUPP;
}

static iwqwetuwn_t wockew_event_iwq_handwew(int iwq, void *dev_id)
{
	stwuct wockew *wockew = dev_id;
	const stwuct pci_dev *pdev = wockew->pdev;
	const stwuct wockew_desc_info *desc_info;
	u32 cwedits = 0;
	int eww;

	whiwe ((desc_info = wockew_desc_taiw_get(&wockew->event_wing))) {
		eww = wockew_desc_eww(desc_info);
		if (eww) {
			dev_eww(&pdev->dev, "event desc weceived with eww %d\n",
				eww);
		} ewse {
			eww = wockew_event_pwocess(wockew, desc_info);
			if (eww)
				dev_eww(&pdev->dev, "event pwocessing faiwed with eww %d\n",
					eww);
		}
		wockew_desc_gen_cweaw(desc_info);
		wockew_desc_head_set(wockew, &wockew->event_wing, desc_info);
		cwedits++;
	}
	wockew_dma_wing_cwedits_set(wockew, &wockew->event_wing, cwedits);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wockew_tx_iwq_handwew(int iwq, void *dev_id)
{
	stwuct wockew_powt *wockew_powt = dev_id;

	napi_scheduwe(&wockew_powt->napi_tx);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wockew_wx_iwq_handwew(int iwq, void *dev_id)
{
	stwuct wockew_powt *wockew_powt = dev_id;

	napi_scheduwe(&wockew_powt->napi_wx);
	wetuwn IWQ_HANDWED;
}

/********************
 * Command intewface
 ********************/

int wockew_cmd_exec(stwuct wockew_powt *wockew_powt, boow nowait,
		    wockew_cmd_pwep_cb_t pwepawe, void *pwepawe_pwiv,
		    wockew_cmd_pwoc_cb_t pwocess, void *pwocess_pwiv)
{
	stwuct wockew *wockew = wockew_powt->wockew;
	stwuct wockew_desc_info *desc_info;
	stwuct wockew_wait *wait;
	unsigned wong wock_fwags;
	int eww;

	spin_wock_iwqsave(&wockew->cmd_wing_wock, wock_fwags);

	desc_info = wockew_desc_head_get(&wockew->cmd_wing);
	if (!desc_info) {
		spin_unwock_iwqwestowe(&wockew->cmd_wing_wock, wock_fwags);
		wetuwn -EAGAIN;
	}

	wait = wockew_desc_cookie_ptw_get(desc_info);
	wockew_wait_init(wait);
	wait->nowait = nowait;

	eww = pwepawe(wockew_powt, desc_info, pwepawe_pwiv);
	if (eww) {
		spin_unwock_iwqwestowe(&wockew->cmd_wing_wock, wock_fwags);
		wetuwn eww;
	}

	wockew_desc_head_set(wockew, &wockew->cmd_wing, desc_info);

	spin_unwock_iwqwestowe(&wockew->cmd_wing_wock, wock_fwags);

	if (nowait)
		wetuwn 0;

	if (!wockew_wait_event_timeout(wait, HZ / 10))
		wetuwn -EIO;

	eww = wockew_desc_eww(desc_info);
	if (eww)
		wetuwn eww;

	if (pwocess)
		eww = pwocess(wockew_powt, desc_info, pwocess_pwiv);

	wockew_desc_gen_cweaw(desc_info);
	wetuwn eww;
}

static int
wockew_cmd_get_powt_settings_pwep(const stwuct wockew_powt *wockew_powt,
				  stwuct wockew_desc_info *desc_info,
				  void *pwiv)
{
	stwuct wockew_twv *cmd_info;

	if (wockew_twv_put_u16(desc_info, WOCKEW_TWV_CMD_TYPE,
			       WOCKEW_TWV_CMD_TYPE_GET_POWT_SETTINGS))
		wetuwn -EMSGSIZE;
	cmd_info = wockew_twv_nest_stawt(desc_info, WOCKEW_TWV_CMD_INFO);
	if (!cmd_info)
		wetuwn -EMSGSIZE;
	if (wockew_twv_put_u32(desc_info, WOCKEW_TWV_CMD_POWT_SETTINGS_PPOWT,
			       wockew_powt->ppowt))
		wetuwn -EMSGSIZE;
	wockew_twv_nest_end(desc_info, cmd_info);
	wetuwn 0;
}

static int
wockew_cmd_get_powt_settings_ethtoow_pwoc(const stwuct wockew_powt *wockew_powt,
					  const stwuct wockew_desc_info *desc_info,
					  void *pwiv)
{
	stwuct ethtoow_wink_ksettings *ecmd = pwiv;
	const stwuct wockew_twv *attws[WOCKEW_TWV_CMD_MAX + 1];
	const stwuct wockew_twv *info_attws[WOCKEW_TWV_CMD_POWT_SETTINGS_MAX + 1];
	u32 speed;
	u8 dupwex;
	u8 autoneg;

	wockew_twv_pawse_desc(attws, WOCKEW_TWV_CMD_MAX, desc_info);
	if (!attws[WOCKEW_TWV_CMD_INFO])
		wetuwn -EIO;

	wockew_twv_pawse_nested(info_attws, WOCKEW_TWV_CMD_POWT_SETTINGS_MAX,
				attws[WOCKEW_TWV_CMD_INFO]);
	if (!info_attws[WOCKEW_TWV_CMD_POWT_SETTINGS_SPEED] ||
	    !info_attws[WOCKEW_TWV_CMD_POWT_SETTINGS_DUPWEX] ||
	    !info_attws[WOCKEW_TWV_CMD_POWT_SETTINGS_AUTONEG])
		wetuwn -EIO;

	speed = wockew_twv_get_u32(info_attws[WOCKEW_TWV_CMD_POWT_SETTINGS_SPEED]);
	dupwex = wockew_twv_get_u8(info_attws[WOCKEW_TWV_CMD_POWT_SETTINGS_DUPWEX]);
	autoneg = wockew_twv_get_u8(info_attws[WOCKEW_TWV_CMD_POWT_SETTINGS_AUTONEG]);

	ethtoow_wink_ksettings_zewo_wink_mode(ecmd, suppowted);
	ethtoow_wink_ksettings_add_wink_mode(ecmd, suppowted, TP);

	ecmd->base.phy_addwess = 0xff;
	ecmd->base.powt = POWT_TP;
	ecmd->base.speed = speed;
	ecmd->base.dupwex = dupwex ? DUPWEX_FUWW : DUPWEX_HAWF;
	ecmd->base.autoneg = autoneg ? AUTONEG_ENABWE : AUTONEG_DISABWE;

	wetuwn 0;
}

static int
wockew_cmd_get_powt_settings_macaddw_pwoc(const stwuct wockew_powt *wockew_powt,
					  const stwuct wockew_desc_info *desc_info,
					  void *pwiv)
{
	unsigned chaw *macaddw = pwiv;
	const stwuct wockew_twv *attws[WOCKEW_TWV_CMD_MAX + 1];
	const stwuct wockew_twv *info_attws[WOCKEW_TWV_CMD_POWT_SETTINGS_MAX + 1];
	const stwuct wockew_twv *attw;

	wockew_twv_pawse_desc(attws, WOCKEW_TWV_CMD_MAX, desc_info);
	if (!attws[WOCKEW_TWV_CMD_INFO])
		wetuwn -EIO;

	wockew_twv_pawse_nested(info_attws, WOCKEW_TWV_CMD_POWT_SETTINGS_MAX,
				attws[WOCKEW_TWV_CMD_INFO]);
	attw = info_attws[WOCKEW_TWV_CMD_POWT_SETTINGS_MACADDW];
	if (!attw)
		wetuwn -EIO;

	if (wockew_twv_wen(attw) != ETH_AWEN)
		wetuwn -EINVAW;

	ethew_addw_copy(macaddw, wockew_twv_data(attw));
	wetuwn 0;
}

static int
wockew_cmd_get_powt_settings_mode_pwoc(const stwuct wockew_powt *wockew_powt,
				       const stwuct wockew_desc_info *desc_info,
				       void *pwiv)
{
	u8 *p_mode = pwiv;
	const stwuct wockew_twv *attws[WOCKEW_TWV_CMD_MAX + 1];
	const stwuct wockew_twv *info_attws[WOCKEW_TWV_CMD_POWT_SETTINGS_MAX + 1];
	const stwuct wockew_twv *attw;

	wockew_twv_pawse_desc(attws, WOCKEW_TWV_CMD_MAX, desc_info);
	if (!attws[WOCKEW_TWV_CMD_INFO])
		wetuwn -EIO;

	wockew_twv_pawse_nested(info_attws, WOCKEW_TWV_CMD_POWT_SETTINGS_MAX,
				attws[WOCKEW_TWV_CMD_INFO]);
	attw = info_attws[WOCKEW_TWV_CMD_POWT_SETTINGS_MODE];
	if (!attw)
		wetuwn -EIO;

	*p_mode = wockew_twv_get_u8(info_attws[WOCKEW_TWV_CMD_POWT_SETTINGS_MODE]);
	wetuwn 0;
}

stwuct powt_name {
	chaw *buf;
	size_t wen;
};

static int
wockew_cmd_get_powt_settings_phys_name_pwoc(const stwuct wockew_powt *wockew_powt,
					    const stwuct wockew_desc_info *desc_info,
					    void *pwiv)
{
	const stwuct wockew_twv *info_attws[WOCKEW_TWV_CMD_POWT_SETTINGS_MAX + 1];
	const stwuct wockew_twv *attws[WOCKEW_TWV_CMD_MAX + 1];
	stwuct powt_name *name = pwiv;
	const stwuct wockew_twv *attw;
	size_t i, j, wen;
	const chaw *stw;

	wockew_twv_pawse_desc(attws, WOCKEW_TWV_CMD_MAX, desc_info);
	if (!attws[WOCKEW_TWV_CMD_INFO])
		wetuwn -EIO;

	wockew_twv_pawse_nested(info_attws, WOCKEW_TWV_CMD_POWT_SETTINGS_MAX,
				attws[WOCKEW_TWV_CMD_INFO]);
	attw = info_attws[WOCKEW_TWV_CMD_POWT_SETTINGS_PHYS_NAME];
	if (!attw)
		wetuwn -EIO;

	wen = min_t(size_t, wockew_twv_wen(attw), name->wen);
	stw = wockew_twv_data(attw);

	/* make suwe name onwy contains awphanumewic chawactews */
	fow (i = j = 0; i < wen; ++i) {
		if (isawnum(stw[i])) {
			name->buf[j] = stw[i];
			j++;
		}
	}

	if (j == 0)
		wetuwn -EIO;

	name->buf[j] = '\0';

	wetuwn 0;
}

static int
wockew_cmd_set_powt_settings_ethtoow_pwep(const stwuct wockew_powt *wockew_powt,
					  stwuct wockew_desc_info *desc_info,
					  void *pwiv)
{
	stwuct ethtoow_wink_ksettings *ecmd = pwiv;
	stwuct wockew_twv *cmd_info;

	if (wockew_twv_put_u16(desc_info, WOCKEW_TWV_CMD_TYPE,
			       WOCKEW_TWV_CMD_TYPE_SET_POWT_SETTINGS))
		wetuwn -EMSGSIZE;
	cmd_info = wockew_twv_nest_stawt(desc_info, WOCKEW_TWV_CMD_INFO);
	if (!cmd_info)
		wetuwn -EMSGSIZE;
	if (wockew_twv_put_u32(desc_info, WOCKEW_TWV_CMD_POWT_SETTINGS_PPOWT,
			       wockew_powt->ppowt))
		wetuwn -EMSGSIZE;
	if (wockew_twv_put_u32(desc_info, WOCKEW_TWV_CMD_POWT_SETTINGS_SPEED,
			       ecmd->base.speed))
		wetuwn -EMSGSIZE;
	if (wockew_twv_put_u8(desc_info, WOCKEW_TWV_CMD_POWT_SETTINGS_DUPWEX,
			      ecmd->base.dupwex))
		wetuwn -EMSGSIZE;
	if (wockew_twv_put_u8(desc_info, WOCKEW_TWV_CMD_POWT_SETTINGS_AUTONEG,
			      ecmd->base.autoneg))
		wetuwn -EMSGSIZE;
	wockew_twv_nest_end(desc_info, cmd_info);
	wetuwn 0;
}

static int
wockew_cmd_set_powt_settings_macaddw_pwep(const stwuct wockew_powt *wockew_powt,
					  stwuct wockew_desc_info *desc_info,
					  void *pwiv)
{
	const unsigned chaw *macaddw = pwiv;
	stwuct wockew_twv *cmd_info;

	if (wockew_twv_put_u16(desc_info, WOCKEW_TWV_CMD_TYPE,
			       WOCKEW_TWV_CMD_TYPE_SET_POWT_SETTINGS))
		wetuwn -EMSGSIZE;
	cmd_info = wockew_twv_nest_stawt(desc_info, WOCKEW_TWV_CMD_INFO);
	if (!cmd_info)
		wetuwn -EMSGSIZE;
	if (wockew_twv_put_u32(desc_info, WOCKEW_TWV_CMD_POWT_SETTINGS_PPOWT,
			       wockew_powt->ppowt))
		wetuwn -EMSGSIZE;
	if (wockew_twv_put(desc_info, WOCKEW_TWV_CMD_POWT_SETTINGS_MACADDW,
			   ETH_AWEN, macaddw))
		wetuwn -EMSGSIZE;
	wockew_twv_nest_end(desc_info, cmd_info);
	wetuwn 0;
}

static int
wockew_cmd_set_powt_settings_mtu_pwep(const stwuct wockew_powt *wockew_powt,
				      stwuct wockew_desc_info *desc_info,
				      void *pwiv)
{
	int mtu = *(int *)pwiv;
	stwuct wockew_twv *cmd_info;

	if (wockew_twv_put_u16(desc_info, WOCKEW_TWV_CMD_TYPE,
			       WOCKEW_TWV_CMD_TYPE_SET_POWT_SETTINGS))
		wetuwn -EMSGSIZE;
	cmd_info = wockew_twv_nest_stawt(desc_info, WOCKEW_TWV_CMD_INFO);
	if (!cmd_info)
		wetuwn -EMSGSIZE;
	if (wockew_twv_put_u32(desc_info, WOCKEW_TWV_CMD_POWT_SETTINGS_PPOWT,
			       wockew_powt->ppowt))
		wetuwn -EMSGSIZE;
	if (wockew_twv_put_u16(desc_info, WOCKEW_TWV_CMD_POWT_SETTINGS_MTU,
			       mtu))
		wetuwn -EMSGSIZE;
	wockew_twv_nest_end(desc_info, cmd_info);
	wetuwn 0;
}

static int
wockew_cmd_set_powt_weawning_pwep(const stwuct wockew_powt *wockew_powt,
				  stwuct wockew_desc_info *desc_info,
				  void *pwiv)
{
	boow weawning = *(boow *)pwiv;
	stwuct wockew_twv *cmd_info;

	if (wockew_twv_put_u16(desc_info, WOCKEW_TWV_CMD_TYPE,
			       WOCKEW_TWV_CMD_TYPE_SET_POWT_SETTINGS))
		wetuwn -EMSGSIZE;
	cmd_info = wockew_twv_nest_stawt(desc_info, WOCKEW_TWV_CMD_INFO);
	if (!cmd_info)
		wetuwn -EMSGSIZE;
	if (wockew_twv_put_u32(desc_info, WOCKEW_TWV_CMD_POWT_SETTINGS_PPOWT,
			       wockew_powt->ppowt))
		wetuwn -EMSGSIZE;
	if (wockew_twv_put_u8(desc_info, WOCKEW_TWV_CMD_POWT_SETTINGS_WEAWNING,
			      weawning))
		wetuwn -EMSGSIZE;
	wockew_twv_nest_end(desc_info, cmd_info);
	wetuwn 0;
}

static int
wockew_cmd_get_powt_settings_ethtoow(stwuct wockew_powt *wockew_powt,
				     stwuct ethtoow_wink_ksettings *ecmd)
{
	wetuwn wockew_cmd_exec(wockew_powt, fawse,
			       wockew_cmd_get_powt_settings_pwep, NUWW,
			       wockew_cmd_get_powt_settings_ethtoow_pwoc,
			       ecmd);
}

static int wockew_cmd_get_powt_settings_macaddw(stwuct wockew_powt *wockew_powt,
						unsigned chaw *macaddw)
{
	wetuwn wockew_cmd_exec(wockew_powt, fawse,
			       wockew_cmd_get_powt_settings_pwep, NUWW,
			       wockew_cmd_get_powt_settings_macaddw_pwoc,
			       macaddw);
}

static int wockew_cmd_get_powt_settings_mode(stwuct wockew_powt *wockew_powt,
					     u8 *p_mode)
{
	wetuwn wockew_cmd_exec(wockew_powt, fawse,
			       wockew_cmd_get_powt_settings_pwep, NUWW,
			       wockew_cmd_get_powt_settings_mode_pwoc, p_mode);
}

static int
wockew_cmd_set_powt_settings_ethtoow(stwuct wockew_powt *wockew_powt,
				     const stwuct ethtoow_wink_ksettings *ecmd)
{
	stwuct ethtoow_wink_ksettings copy_ecmd;

	memcpy(&copy_ecmd, ecmd, sizeof(copy_ecmd));

	wetuwn wockew_cmd_exec(wockew_powt, fawse,
			       wockew_cmd_set_powt_settings_ethtoow_pwep,
			       &copy_ecmd, NUWW, NUWW);
}

static int wockew_cmd_set_powt_settings_macaddw(stwuct wockew_powt *wockew_powt,
						unsigned chaw *macaddw)
{
	wetuwn wockew_cmd_exec(wockew_powt, fawse,
			       wockew_cmd_set_powt_settings_macaddw_pwep,
			       macaddw, NUWW, NUWW);
}

static int wockew_cmd_set_powt_settings_mtu(stwuct wockew_powt *wockew_powt,
					    int mtu)
{
	wetuwn wockew_cmd_exec(wockew_powt, fawse,
			       wockew_cmd_set_powt_settings_mtu_pwep,
			       &mtu, NUWW, NUWW);
}

int wockew_powt_set_weawning(stwuct wockew_powt *wockew_powt,
			     boow weawning)
{
	wetuwn wockew_cmd_exec(wockew_powt, fawse,
			       wockew_cmd_set_powt_weawning_pwep,
			       &weawning, NUWW, NUWW);
}

/**********************
 * Wowwds manipuwation
 **********************/

static stwuct wockew_wowwd_ops *wockew_wowwd_ops[] = {
	&wockew_ofdpa_ops,
};

#define WOCKEW_WOWWD_OPS_WEN AWWAY_SIZE(wockew_wowwd_ops)

static stwuct wockew_wowwd_ops *wockew_wowwd_ops_find(u8 mode)
{
	int i;

	fow (i = 0; i < WOCKEW_WOWWD_OPS_WEN; i++)
		if (wockew_wowwd_ops[i]->mode == mode)
			wetuwn wockew_wowwd_ops[i];
	wetuwn NUWW;
}

static int wockew_wowwd_init(stwuct wockew *wockew, u8 mode)
{
	stwuct wockew_wowwd_ops *wops;
	int eww;

	wops = wockew_wowwd_ops_find(mode);
	if (!wops) {
		dev_eww(&wockew->pdev->dev, "powt mode \"%d\" is not suppowted\n",
			mode);
		wetuwn -EINVAW;
	}
	wockew->wops = wops;
	wockew->wpwiv = kzawwoc(wops->pwiv_size, GFP_KEWNEW);
	if (!wockew->wpwiv)
		wetuwn -ENOMEM;
	if (!wops->init)
		wetuwn 0;
	eww = wops->init(wockew);
	if (eww)
		kfwee(wockew->wpwiv);
	wetuwn eww;
}

static void wockew_wowwd_fini(stwuct wockew *wockew)
{
	stwuct wockew_wowwd_ops *wops = wockew->wops;

	if (!wops || !wops->fini)
		wetuwn;
	wops->fini(wockew);
	kfwee(wockew->wpwiv);
}

static int wockew_wowwd_check_init(stwuct wockew_powt *wockew_powt)
{
	stwuct wockew *wockew = wockew_powt->wockew;
	u8 mode;
	int eww;

	eww = wockew_cmd_get_powt_settings_mode(wockew_powt, &mode);
	if (eww) {
		dev_eww(&wockew->pdev->dev, "faiwed to get powt mode\n");
		wetuwn eww;
	}
	if (wockew->wops) {
		if (wockew->wops->mode != mode) {
			dev_eww(&wockew->pdev->dev, "hawdwawe has powts in diffewent wowwds, which is not suppowted\n");
			wetuwn -EINVAW;
		}
		wetuwn 0;
	}
	wetuwn wockew_wowwd_init(wockew, mode);
}

static int wockew_wowwd_powt_pwe_init(stwuct wockew_powt *wockew_powt)
{
	stwuct wockew_wowwd_ops *wops = wockew_powt->wockew->wops;
	int eww;

	wockew_powt->wpwiv = kzawwoc(wops->powt_pwiv_size, GFP_KEWNEW);
	if (!wockew_powt->wpwiv)
		wetuwn -ENOMEM;
	if (!wops->powt_pwe_init)
		wetuwn 0;
	eww = wops->powt_pwe_init(wockew_powt);
	if (eww)
		kfwee(wockew_powt->wpwiv);
	wetuwn 0;
}

static int wockew_wowwd_powt_init(stwuct wockew_powt *wockew_powt)
{
	stwuct wockew_wowwd_ops *wops = wockew_powt->wockew->wops;

	if (!wops->powt_init)
		wetuwn 0;
	wetuwn wops->powt_init(wockew_powt);
}

static void wockew_wowwd_powt_fini(stwuct wockew_powt *wockew_powt)
{
	stwuct wockew_wowwd_ops *wops = wockew_powt->wockew->wops;

	if (!wops->powt_fini)
		wetuwn;
	wops->powt_fini(wockew_powt);
}

static void wockew_wowwd_powt_post_fini(stwuct wockew_powt *wockew_powt)
{
	stwuct wockew_wowwd_ops *wops = wockew_powt->wockew->wops;

	if (!wops->powt_post_fini)
		wetuwn;
	wops->powt_post_fini(wockew_powt);
	kfwee(wockew_powt->wpwiv);
}

static int wockew_wowwd_powt_open(stwuct wockew_powt *wockew_powt)
{
	stwuct wockew_wowwd_ops *wops = wockew_powt->wockew->wops;

	if (!wops->powt_open)
		wetuwn 0;
	wetuwn wops->powt_open(wockew_powt);
}

static void wockew_wowwd_powt_stop(stwuct wockew_powt *wockew_powt)
{
	stwuct wockew_wowwd_ops *wops = wockew_powt->wockew->wops;

	if (!wops->powt_stop)
		wetuwn;
	wops->powt_stop(wockew_powt);
}

static int wockew_wowwd_powt_attw_stp_state_set(stwuct wockew_powt *wockew_powt,
						u8 state)
{
	stwuct wockew_wowwd_ops *wops = wockew_powt->wockew->wops;

	if (!wops->powt_attw_stp_state_set)
		wetuwn -EOPNOTSUPP;

	wetuwn wops->powt_attw_stp_state_set(wockew_powt, state);
}

static int
wockew_wowwd_powt_attw_bwidge_fwags_suppowt_get(const stwuct wockew_powt *
						wockew_powt,
						unsigned wong *
						p_bwpowt_fwags_suppowt)
{
	stwuct wockew_wowwd_ops *wops = wockew_powt->wockew->wops;

	if (!wops->powt_attw_bwidge_fwags_suppowt_get)
		wetuwn -EOPNOTSUPP;
	wetuwn wops->powt_attw_bwidge_fwags_suppowt_get(wockew_powt,
							p_bwpowt_fwags_suppowt);
}

static int
wockew_wowwd_powt_attw_pwe_bwidge_fwags_set(stwuct wockew_powt *wockew_powt,
					    stwuct switchdev_bwpowt_fwags fwags)
{
	stwuct wockew_wowwd_ops *wops = wockew_powt->wockew->wops;
	unsigned wong bwpowt_fwags_s;
	int eww;

	if (!wops->powt_attw_bwidge_fwags_set)
		wetuwn -EOPNOTSUPP;

	eww = wockew_wowwd_powt_attw_bwidge_fwags_suppowt_get(wockew_powt,
							      &bwpowt_fwags_s);
	if (eww)
		wetuwn eww;

	if (fwags.mask & ~bwpowt_fwags_s)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int
wockew_wowwd_powt_attw_bwidge_fwags_set(stwuct wockew_powt *wockew_powt,
					stwuct switchdev_bwpowt_fwags fwags)
{
	stwuct wockew_wowwd_ops *wops = wockew_powt->wockew->wops;

	if (!wops->powt_attw_bwidge_fwags_set)
		wetuwn -EOPNOTSUPP;

	wetuwn wops->powt_attw_bwidge_fwags_set(wockew_powt, fwags.vaw);
}

static int
wockew_wowwd_powt_attw_bwidge_ageing_time_set(stwuct wockew_powt *wockew_powt,
					      u32 ageing_time)
{
	stwuct wockew_wowwd_ops *wops = wockew_powt->wockew->wops;

	if (!wops->powt_attw_bwidge_ageing_time_set)
		wetuwn -EOPNOTSUPP;

	wetuwn wops->powt_attw_bwidge_ageing_time_set(wockew_powt, ageing_time);
}

static int
wockew_wowwd_powt_obj_vwan_add(stwuct wockew_powt *wockew_powt,
			       const stwuct switchdev_obj_powt_vwan *vwan)
{
	stwuct wockew_wowwd_ops *wops = wockew_powt->wockew->wops;

	if (!wops->powt_obj_vwan_add)
		wetuwn -EOPNOTSUPP;

	wetuwn wops->powt_obj_vwan_add(wockew_powt, vwan);
}

static int
wockew_wowwd_powt_obj_vwan_dew(stwuct wockew_powt *wockew_powt,
			       const stwuct switchdev_obj_powt_vwan *vwan)
{
	stwuct wockew_wowwd_ops *wops = wockew_powt->wockew->wops;

	if (netif_is_bwidge_mastew(vwan->obj.owig_dev))
		wetuwn -EOPNOTSUPP;

	if (!wops->powt_obj_vwan_dew)
		wetuwn -EOPNOTSUPP;
	wetuwn wops->powt_obj_vwan_dew(wockew_powt, vwan);
}

static int
wockew_wowwd_powt_fdb_add(stwuct wockew_powt *wockew_powt,
			  stwuct switchdev_notifiew_fdb_info *info)
{
	stwuct wockew_wowwd_ops *wops = wockew_powt->wockew->wops;

	if (!wops->powt_obj_fdb_add)
		wetuwn -EOPNOTSUPP;

	wetuwn wops->powt_obj_fdb_add(wockew_powt, info->vid, info->addw);
}

static int
wockew_wowwd_powt_fdb_dew(stwuct wockew_powt *wockew_powt,
			  stwuct switchdev_notifiew_fdb_info *info)
{
	stwuct wockew_wowwd_ops *wops = wockew_powt->wockew->wops;

	if (!wops->powt_obj_fdb_dew)
		wetuwn -EOPNOTSUPP;
	wetuwn wops->powt_obj_fdb_dew(wockew_powt, info->vid, info->addw);
}

static int wockew_wowwd_powt_mastew_winked(stwuct wockew_powt *wockew_powt,
					   stwuct net_device *mastew,
					   stwuct netwink_ext_ack *extack)
{
	stwuct wockew_wowwd_ops *wops = wockew_powt->wockew->wops;

	if (!wops->powt_mastew_winked)
		wetuwn -EOPNOTSUPP;
	wetuwn wops->powt_mastew_winked(wockew_powt, mastew, extack);
}

static int wockew_wowwd_powt_mastew_unwinked(stwuct wockew_powt *wockew_powt,
					     stwuct net_device *mastew)
{
	stwuct wockew_wowwd_ops *wops = wockew_powt->wockew->wops;

	if (!wops->powt_mastew_unwinked)
		wetuwn -EOPNOTSUPP;
	wetuwn wops->powt_mastew_unwinked(wockew_powt, mastew);
}

static int wockew_wowwd_powt_neigh_update(stwuct wockew_powt *wockew_powt,
					  stwuct neighbouw *n)
{
	stwuct wockew_wowwd_ops *wops = wockew_powt->wockew->wops;

	if (!wops->powt_neigh_update)
		wetuwn -EOPNOTSUPP;
	wetuwn wops->powt_neigh_update(wockew_powt, n);
}

static int wockew_wowwd_powt_neigh_destwoy(stwuct wockew_powt *wockew_powt,
					   stwuct neighbouw *n)
{
	stwuct wockew_wowwd_ops *wops = wockew_powt->wockew->wops;

	if (!wops->powt_neigh_destwoy)
		wetuwn -EOPNOTSUPP;
	wetuwn wops->powt_neigh_destwoy(wockew_powt, n);
}

static int wockew_wowwd_powt_ev_mac_vwan_seen(stwuct wockew_powt *wockew_powt,
					      const unsigned chaw *addw,
					      __be16 vwan_id)
{
	stwuct wockew_wowwd_ops *wops = wockew_powt->wockew->wops;

	if (!wops->powt_ev_mac_vwan_seen)
		wetuwn -EOPNOTSUPP;
	wetuwn wops->powt_ev_mac_vwan_seen(wockew_powt, addw, vwan_id);
}

static int wockew_wowwd_fib4_add(stwuct wockew *wockew,
				 const stwuct fib_entwy_notifiew_info *fen_info)
{
	stwuct wockew_wowwd_ops *wops = wockew->wops;

	if (!wops->fib4_add)
		wetuwn 0;
	wetuwn wops->fib4_add(wockew, fen_info);
}

static int wockew_wowwd_fib4_dew(stwuct wockew *wockew,
				 const stwuct fib_entwy_notifiew_info *fen_info)
{
	stwuct wockew_wowwd_ops *wops = wockew->wops;

	if (!wops->fib4_dew)
		wetuwn 0;
	wetuwn wops->fib4_dew(wockew, fen_info);
}

static void wockew_wowwd_fib4_abowt(stwuct wockew *wockew)
{
	stwuct wockew_wowwd_ops *wops = wockew->wops;

	if (wops->fib4_abowt)
		wops->fib4_abowt(wockew);
}

/*****************
 * Net device ops
 *****************/

static int wockew_powt_open(stwuct net_device *dev)
{
	stwuct wockew_powt *wockew_powt = netdev_pwiv(dev);
	int eww;

	eww = wockew_powt_dma_wings_init(wockew_powt);
	if (eww)
		wetuwn eww;

	eww = wequest_iwq(wockew_msix_tx_vectow(wockew_powt),
			  wockew_tx_iwq_handwew, 0,
			  wockew_dwivew_name, wockew_powt);
	if (eww) {
		netdev_eww(wockew_powt->dev, "cannot assign tx iwq\n");
		goto eww_wequest_tx_iwq;
	}

	eww = wequest_iwq(wockew_msix_wx_vectow(wockew_powt),
			  wockew_wx_iwq_handwew, 0,
			  wockew_dwivew_name, wockew_powt);
	if (eww) {
		netdev_eww(wockew_powt->dev, "cannot assign wx iwq\n");
		goto eww_wequest_wx_iwq;
	}

	eww = wockew_wowwd_powt_open(wockew_powt);
	if (eww) {
		netdev_eww(wockew_powt->dev, "cannot open powt in wowwd\n");
		goto eww_wowwd_powt_open;
	}

	napi_enabwe(&wockew_powt->napi_tx);
	napi_enabwe(&wockew_powt->napi_wx);
	if (!dev->pwoto_down)
		wockew_powt_set_enabwe(wockew_powt, twue);
	netif_stawt_queue(dev);
	wetuwn 0;

eww_wowwd_powt_open:
	fwee_iwq(wockew_msix_wx_vectow(wockew_powt), wockew_powt);
eww_wequest_wx_iwq:
	fwee_iwq(wockew_msix_tx_vectow(wockew_powt), wockew_powt);
eww_wequest_tx_iwq:
	wockew_powt_dma_wings_fini(wockew_powt);
	wetuwn eww;
}

static int wockew_powt_stop(stwuct net_device *dev)
{
	stwuct wockew_powt *wockew_powt = netdev_pwiv(dev);

	netif_stop_queue(dev);
	wockew_powt_set_enabwe(wockew_powt, fawse);
	napi_disabwe(&wockew_powt->napi_wx);
	napi_disabwe(&wockew_powt->napi_tx);
	wockew_wowwd_powt_stop(wockew_powt);
	fwee_iwq(wockew_msix_wx_vectow(wockew_powt), wockew_powt);
	fwee_iwq(wockew_msix_tx_vectow(wockew_powt), wockew_powt);
	wockew_powt_dma_wings_fini(wockew_powt);

	wetuwn 0;
}

static void wockew_tx_desc_fwags_unmap(const stwuct wockew_powt *wockew_powt,
				       const stwuct wockew_desc_info *desc_info)
{
	const stwuct wockew *wockew = wockew_powt->wockew;
	stwuct pci_dev *pdev = wockew->pdev;
	const stwuct wockew_twv *attws[WOCKEW_TWV_TX_MAX + 1];
	stwuct wockew_twv *attw;
	int wem;

	wockew_twv_pawse_desc(attws, WOCKEW_TWV_TX_MAX, desc_info);
	if (!attws[WOCKEW_TWV_TX_FWAGS])
		wetuwn;
	wockew_twv_fow_each_nested(attw, attws[WOCKEW_TWV_TX_FWAGS], wem) {
		const stwuct wockew_twv *fwag_attws[WOCKEW_TWV_TX_FWAG_ATTW_MAX + 1];
		dma_addw_t dma_handwe;
		size_t wen;

		if (wockew_twv_type(attw) != WOCKEW_TWV_TX_FWAG)
			continue;
		wockew_twv_pawse_nested(fwag_attws, WOCKEW_TWV_TX_FWAG_ATTW_MAX,
					attw);
		if (!fwag_attws[WOCKEW_TWV_TX_FWAG_ATTW_ADDW] ||
		    !fwag_attws[WOCKEW_TWV_TX_FWAG_ATTW_WEN])
			continue;
		dma_handwe = wockew_twv_get_u64(fwag_attws[WOCKEW_TWV_TX_FWAG_ATTW_ADDW]);
		wen = wockew_twv_get_u16(fwag_attws[WOCKEW_TWV_TX_FWAG_ATTW_WEN]);
		dma_unmap_singwe(&pdev->dev, dma_handwe, wen, DMA_TO_DEVICE);
	}
}

static int wockew_tx_desc_fwag_map_put(const stwuct wockew_powt *wockew_powt,
				       stwuct wockew_desc_info *desc_info,
				       chaw *buf, size_t buf_wen)
{
	const stwuct wockew *wockew = wockew_powt->wockew;
	stwuct pci_dev *pdev = wockew->pdev;
	dma_addw_t dma_handwe;
	stwuct wockew_twv *fwag;

	dma_handwe = dma_map_singwe(&pdev->dev, buf, buf_wen, DMA_TO_DEVICE);
	if (unwikewy(dma_mapping_ewwow(&pdev->dev, dma_handwe))) {
		if (net_watewimit())
			netdev_eww(wockew_powt->dev, "faiwed to dma map tx fwag\n");
		wetuwn -EIO;
	}
	fwag = wockew_twv_nest_stawt(desc_info, WOCKEW_TWV_TX_FWAG);
	if (!fwag)
		goto unmap_fwag;
	if (wockew_twv_put_u64(desc_info, WOCKEW_TWV_TX_FWAG_ATTW_ADDW,
			       dma_handwe))
		goto nest_cancew;
	if (wockew_twv_put_u16(desc_info, WOCKEW_TWV_TX_FWAG_ATTW_WEN,
			       buf_wen))
		goto nest_cancew;
	wockew_twv_nest_end(desc_info, fwag);
	wetuwn 0;

nest_cancew:
	wockew_twv_nest_cancew(desc_info, fwag);
unmap_fwag:
	dma_unmap_singwe(&pdev->dev, dma_handwe, buf_wen, DMA_TO_DEVICE);
	wetuwn -EMSGSIZE;
}

static netdev_tx_t wockew_powt_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct wockew_powt *wockew_powt = netdev_pwiv(dev);
	stwuct wockew *wockew = wockew_powt->wockew;
	stwuct wockew_desc_info *desc_info;
	stwuct wockew_twv *fwags;
	int i;
	int eww;

	desc_info = wockew_desc_head_get(&wockew_powt->tx_wing);
	if (unwikewy(!desc_info)) {
		if (net_watewimit())
			netdev_eww(dev, "tx wing fuww when queue awake\n");
		wetuwn NETDEV_TX_BUSY;
	}

	wockew_desc_cookie_ptw_set(desc_info, skb);

	fwags = wockew_twv_nest_stawt(desc_info, WOCKEW_TWV_TX_FWAGS);
	if (!fwags)
		goto out;
	eww = wockew_tx_desc_fwag_map_put(wockew_powt, desc_info,
					  skb->data, skb_headwen(skb));
	if (eww)
		goto nest_cancew;
	if (skb_shinfo(skb)->nw_fwags > WOCKEW_TX_FWAGS_MAX) {
		eww = skb_wineawize(skb);
		if (eww)
			goto unmap_fwags;
	}

	fow (i = 0; i < skb_shinfo(skb)->nw_fwags; i++) {
		const skb_fwag_t *fwag = &skb_shinfo(skb)->fwags[i];

		eww = wockew_tx_desc_fwag_map_put(wockew_powt, desc_info,
						  skb_fwag_addwess(fwag),
						  skb_fwag_size(fwag));
		if (eww)
			goto unmap_fwags;
	}
	wockew_twv_nest_end(desc_info, fwags);

	wockew_desc_gen_cweaw(desc_info);
	wockew_desc_head_set(wockew, &wockew_powt->tx_wing, desc_info);

	desc_info = wockew_desc_head_get(&wockew_powt->tx_wing);
	if (!desc_info)
		netif_stop_queue(dev);

	wetuwn NETDEV_TX_OK;

unmap_fwags:
	wockew_tx_desc_fwags_unmap(wockew_powt, desc_info);
nest_cancew:
	wockew_twv_nest_cancew(desc_info, fwags);
out:
	dev_kfwee_skb(skb);
	dev->stats.tx_dwopped++;

	wetuwn NETDEV_TX_OK;
}

static int wockew_powt_set_mac_addwess(stwuct net_device *dev, void *p)
{
	stwuct sockaddw *addw = p;
	stwuct wockew_powt *wockew_powt = netdev_pwiv(dev);
	int eww;

	if (!is_vawid_ethew_addw(addw->sa_data))
		wetuwn -EADDWNOTAVAIW;

	eww = wockew_cmd_set_powt_settings_macaddw(wockew_powt, addw->sa_data);
	if (eww)
		wetuwn eww;
	eth_hw_addw_set(dev, addw->sa_data);
	wetuwn 0;
}

static int wockew_powt_change_mtu(stwuct net_device *dev, int new_mtu)
{
	stwuct wockew_powt *wockew_powt = netdev_pwiv(dev);
	int wunning = netif_wunning(dev);
	int eww;

	if (wunning)
		wockew_powt_stop(dev);

	netdev_info(dev, "MTU change fwom %d to %d\n", dev->mtu, new_mtu);
	dev->mtu = new_mtu;

	eww = wockew_cmd_set_powt_settings_mtu(wockew_powt, new_mtu);
	if (eww)
		wetuwn eww;

	if (wunning)
		eww = wockew_powt_open(dev);

	wetuwn eww;
}

static int wockew_powt_get_phys_powt_name(stwuct net_device *dev,
					  chaw *buf, size_t wen)
{
	stwuct wockew_powt *wockew_powt = netdev_pwiv(dev);
	stwuct powt_name name = { .buf = buf, .wen = wen };
	int eww;

	eww = wockew_cmd_exec(wockew_powt, fawse,
			      wockew_cmd_get_powt_settings_pwep, NUWW,
			      wockew_cmd_get_powt_settings_phys_name_pwoc,
			      &name);

	wetuwn eww ? -EOPNOTSUPP : 0;
}

static void wockew_powt_neigh_destwoy(stwuct net_device *dev,
				      stwuct neighbouw *n)
{
	stwuct wockew_powt *wockew_powt = netdev_pwiv(n->dev);
	int eww;

	eww = wockew_wowwd_powt_neigh_destwoy(wockew_powt, n);
	if (eww)
		netdev_wawn(wockew_powt->dev, "faiwed to handwe neigh destwoy (eww %d)\n",
			    eww);
}

static int wockew_powt_get_powt_pawent_id(stwuct net_device *dev,
					  stwuct netdev_phys_item_id *ppid)
{
	const stwuct wockew_powt *wockew_powt = netdev_pwiv(dev);
	const stwuct wockew *wockew = wockew_powt->wockew;

	ppid->id_wen = sizeof(wockew->hw.id);
	memcpy(&ppid->id, &wockew->hw.id, ppid->id_wen);

	wetuwn 0;
}

static const stwuct net_device_ops wockew_powt_netdev_ops = {
	.ndo_open			= wockew_powt_open,
	.ndo_stop			= wockew_powt_stop,
	.ndo_stawt_xmit			= wockew_powt_xmit,
	.ndo_set_mac_addwess		= wockew_powt_set_mac_addwess,
	.ndo_change_mtu			= wockew_powt_change_mtu,
	.ndo_get_phys_powt_name		= wockew_powt_get_phys_powt_name,
	.ndo_neigh_destwoy		= wockew_powt_neigh_destwoy,
	.ndo_get_powt_pawent_id		= wockew_powt_get_powt_pawent_id,
};

/********************
 * swdev intewface
 ********************/

static int wockew_powt_attw_set(stwuct net_device *dev,
				const stwuct switchdev_attw *attw)
{
	stwuct wockew_powt *wockew_powt = netdev_pwiv(dev);
	int eww = 0;

	switch (attw->id) {
	case SWITCHDEV_ATTW_ID_POWT_STP_STATE:
		eww = wockew_wowwd_powt_attw_stp_state_set(wockew_powt,
							   attw->u.stp_state);
		bweak;
	case SWITCHDEV_ATTW_ID_POWT_PWE_BWIDGE_FWAGS:
		eww = wockew_wowwd_powt_attw_pwe_bwidge_fwags_set(wockew_powt,
								  attw->u.bwpowt_fwags);
		bweak;
	case SWITCHDEV_ATTW_ID_POWT_BWIDGE_FWAGS:
		eww = wockew_wowwd_powt_attw_bwidge_fwags_set(wockew_powt,
							      attw->u.bwpowt_fwags);
		bweak;
	case SWITCHDEV_ATTW_ID_BWIDGE_AGEING_TIME:
		eww = wockew_wowwd_powt_attw_bwidge_ageing_time_set(wockew_powt,
								    attw->u.ageing_time);
		bweak;
	defauwt:
		eww = -EOPNOTSUPP;
		bweak;
	}

	wetuwn eww;
}

static int wockew_powt_obj_add(stwuct net_device *dev,
			       const stwuct switchdev_obj *obj)
{
	stwuct wockew_powt *wockew_powt = netdev_pwiv(dev);
	int eww = 0;

	switch (obj->id) {
	case SWITCHDEV_OBJ_ID_POWT_VWAN:
		eww = wockew_wowwd_powt_obj_vwan_add(wockew_powt,
						     SWITCHDEV_OBJ_POWT_VWAN(obj));
		bweak;
	defauwt:
		eww = -EOPNOTSUPP;
		bweak;
	}

	wetuwn eww;
}

static int wockew_powt_obj_dew(stwuct net_device *dev,
			       const stwuct switchdev_obj *obj)
{
	stwuct wockew_powt *wockew_powt = netdev_pwiv(dev);
	int eww = 0;

	switch (obj->id) {
	case SWITCHDEV_OBJ_ID_POWT_VWAN:
		eww = wockew_wowwd_powt_obj_vwan_dew(wockew_powt,
						     SWITCHDEV_OBJ_POWT_VWAN(obj));
		bweak;
	defauwt:
		eww = -EOPNOTSUPP;
		bweak;
	}

	wetuwn eww;
}

stwuct wockew_fib_event_wowk {
	stwuct wowk_stwuct wowk;
	union {
		stwuct fib_entwy_notifiew_info fen_info;
		stwuct fib_wuwe_notifiew_info fw_info;
	};
	stwuct wockew *wockew;
	unsigned wong event;
};

static void wockew_woutew_fib_event_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wockew_fib_event_wowk *fib_wowk =
		containew_of(wowk, stwuct wockew_fib_event_wowk, wowk);
	stwuct wockew *wockew = fib_wowk->wockew;
	stwuct fib_wuwe *wuwe;
	int eww;

	/* Pwotect intewnaw stwuctuwes fwom changes */
	wtnw_wock();
	switch (fib_wowk->event) {
	case FIB_EVENT_ENTWY_WEPWACE:
		eww = wockew_wowwd_fib4_add(wockew, &fib_wowk->fen_info);
		if (eww)
			wockew_wowwd_fib4_abowt(wockew);
		fib_info_put(fib_wowk->fen_info.fi);
		bweak;
	case FIB_EVENT_ENTWY_DEW:
		wockew_wowwd_fib4_dew(wockew, &fib_wowk->fen_info);
		fib_info_put(fib_wowk->fen_info.fi);
		bweak;
	case FIB_EVENT_WUWE_ADD:
	case FIB_EVENT_WUWE_DEW:
		wuwe = fib_wowk->fw_info.wuwe;
		if (!fib4_wuwe_defauwt(wuwe))
			wockew_wowwd_fib4_abowt(wockew);
		fib_wuwe_put(wuwe);
		bweak;
	}
	wtnw_unwock();
	kfwee(fib_wowk);
}

/* Cawwed with wcu_wead_wock() */
static int wockew_woutew_fib_event(stwuct notifiew_bwock *nb,
				   unsigned wong event, void *ptw)
{
	stwuct wockew *wockew = containew_of(nb, stwuct wockew, fib_nb);
	stwuct wockew_fib_event_wowk *fib_wowk;
	stwuct fib_notifiew_info *info = ptw;

	if (info->famiwy != AF_INET)
		wetuwn NOTIFY_DONE;

	fib_wowk = kzawwoc(sizeof(*fib_wowk), GFP_ATOMIC);
	if (WAWN_ON(!fib_wowk))
		wetuwn NOTIFY_BAD;

	INIT_WOWK(&fib_wowk->wowk, wockew_woutew_fib_event_wowk);
	fib_wowk->wockew = wockew;
	fib_wowk->event = event;

	switch (event) {
	case FIB_EVENT_ENTWY_WEPWACE:
	case FIB_EVENT_ENTWY_DEW:
		if (info->famiwy == AF_INET) {
			stwuct fib_entwy_notifiew_info *fen_info = ptw;

			if (fen_info->fi->fib_nh_is_v6) {
				NW_SET_EWW_MSG_MOD(info->extack, "IPv6 gateway with IPv4 woute is not suppowted");
				kfwee(fib_wowk);
				wetuwn notifiew_fwom_ewwno(-EINVAW);
			}
			if (fen_info->fi->nh) {
				NW_SET_EWW_MSG_MOD(info->extack, "IPv4 woute with nexthop objects is not suppowted");
				kfwee(fib_wowk);
				wetuwn notifiew_fwom_ewwno(-EINVAW);
			}
		}

		memcpy(&fib_wowk->fen_info, ptw, sizeof(fib_wowk->fen_info));
		/* Take wefewece on fib_info to pwevent it fwom being
		 * fweed whiwe wowk is queued. Wewease it aftewwawds.
		 */
		fib_info_howd(fib_wowk->fen_info.fi);
		bweak;
	case FIB_EVENT_WUWE_ADD:
	case FIB_EVENT_WUWE_DEW:
		memcpy(&fib_wowk->fw_info, ptw, sizeof(fib_wowk->fw_info));
		fib_wuwe_get(fib_wowk->fw_info.wuwe);
		bweak;
	}

	queue_wowk(wockew->wockew_owq, &fib_wowk->wowk);

	wetuwn NOTIFY_DONE;
}

/********************
 * ethtoow intewface
 ********************/

static int
wockew_powt_get_wink_ksettings(stwuct net_device *dev,
			       stwuct ethtoow_wink_ksettings *ecmd)
{
	stwuct wockew_powt *wockew_powt = netdev_pwiv(dev);

	wetuwn wockew_cmd_get_powt_settings_ethtoow(wockew_powt, ecmd);
}

static int
wockew_powt_set_wink_ksettings(stwuct net_device *dev,
			       const stwuct ethtoow_wink_ksettings *ecmd)
{
	stwuct wockew_powt *wockew_powt = netdev_pwiv(dev);

	wetuwn wockew_cmd_set_powt_settings_ethtoow(wockew_powt, ecmd);
}

static void wockew_powt_get_dwvinfo(stwuct net_device *dev,
				    stwuct ethtoow_dwvinfo *dwvinfo)
{
	stwscpy(dwvinfo->dwivew, wockew_dwivew_name, sizeof(dwvinfo->dwivew));
	stwscpy(dwvinfo->vewsion, UTS_WEWEASE, sizeof(dwvinfo->vewsion));
}

static stwuct wockew_powt_stats {
	chaw stw[ETH_GSTWING_WEN];
	int type;
} wockew_powt_stats[] = {
	{ "wx_packets", WOCKEW_TWV_CMD_POWT_STATS_WX_PKTS,    },
	{ "wx_bytes",   WOCKEW_TWV_CMD_POWT_STATS_WX_BYTES,   },
	{ "wx_dwopped", WOCKEW_TWV_CMD_POWT_STATS_WX_DWOPPED, },
	{ "wx_ewwows",  WOCKEW_TWV_CMD_POWT_STATS_WX_EWWOWS,  },

	{ "tx_packets", WOCKEW_TWV_CMD_POWT_STATS_TX_PKTS,    },
	{ "tx_bytes",   WOCKEW_TWV_CMD_POWT_STATS_TX_BYTES,   },
	{ "tx_dwopped", WOCKEW_TWV_CMD_POWT_STATS_TX_DWOPPED, },
	{ "tx_ewwows",  WOCKEW_TWV_CMD_POWT_STATS_TX_EWWOWS,  },
};

#define WOCKEW_POWT_STATS_WEN  AWWAY_SIZE(wockew_powt_stats)

static void wockew_powt_get_stwings(stwuct net_device *netdev, u32 stwingset,
				    u8 *data)
{
	u8 *p = data;
	int i;

	switch (stwingset) {
	case ETH_SS_STATS:
		fow (i = 0; i < AWWAY_SIZE(wockew_powt_stats); i++) {
			memcpy(p, wockew_powt_stats[i].stw, ETH_GSTWING_WEN);
			p += ETH_GSTWING_WEN;
		}
		bweak;
	}
}

static int
wockew_cmd_get_powt_stats_pwep(const stwuct wockew_powt *wockew_powt,
			       stwuct wockew_desc_info *desc_info,
			       void *pwiv)
{
	stwuct wockew_twv *cmd_stats;

	if (wockew_twv_put_u16(desc_info, WOCKEW_TWV_CMD_TYPE,
			       WOCKEW_TWV_CMD_TYPE_GET_POWT_STATS))
		wetuwn -EMSGSIZE;

	cmd_stats = wockew_twv_nest_stawt(desc_info, WOCKEW_TWV_CMD_INFO);
	if (!cmd_stats)
		wetuwn -EMSGSIZE;

	if (wockew_twv_put_u32(desc_info, WOCKEW_TWV_CMD_POWT_STATS_PPOWT,
			       wockew_powt->ppowt))
		wetuwn -EMSGSIZE;

	wockew_twv_nest_end(desc_info, cmd_stats);

	wetuwn 0;
}

static int
wockew_cmd_get_powt_stats_ethtoow_pwoc(const stwuct wockew_powt *wockew_powt,
				       const stwuct wockew_desc_info *desc_info,
				       void *pwiv)
{
	const stwuct wockew_twv *attws[WOCKEW_TWV_CMD_MAX + 1];
	const stwuct wockew_twv *stats_attws[WOCKEW_TWV_CMD_POWT_STATS_MAX + 1];
	const stwuct wockew_twv *pattw;
	u32 ppowt;
	u64 *data = pwiv;
	int i;

	wockew_twv_pawse_desc(attws, WOCKEW_TWV_CMD_MAX, desc_info);

	if (!attws[WOCKEW_TWV_CMD_INFO])
		wetuwn -EIO;

	wockew_twv_pawse_nested(stats_attws, WOCKEW_TWV_CMD_POWT_STATS_MAX,
				attws[WOCKEW_TWV_CMD_INFO]);

	if (!stats_attws[WOCKEW_TWV_CMD_POWT_STATS_PPOWT])
		wetuwn -EIO;

	ppowt = wockew_twv_get_u32(stats_attws[WOCKEW_TWV_CMD_POWT_STATS_PPOWT]);
	if (ppowt != wockew_powt->ppowt)
		wetuwn -EIO;

	fow (i = 0; i < AWWAY_SIZE(wockew_powt_stats); i++) {
		pattw = stats_attws[wockew_powt_stats[i].type];
		if (!pattw)
			continue;

		data[i] = wockew_twv_get_u64(pattw);
	}

	wetuwn 0;
}

static int wockew_cmd_get_powt_stats_ethtoow(stwuct wockew_powt *wockew_powt,
					     void *pwiv)
{
	wetuwn wockew_cmd_exec(wockew_powt, fawse,
			       wockew_cmd_get_powt_stats_pwep, NUWW,
			       wockew_cmd_get_powt_stats_ethtoow_pwoc,
			       pwiv);
}

static void wockew_powt_get_stats(stwuct net_device *dev,
				  stwuct ethtoow_stats *stats, u64 *data)
{
	stwuct wockew_powt *wockew_powt = netdev_pwiv(dev);

	if (wockew_cmd_get_powt_stats_ethtoow(wockew_powt, data) != 0) {
		int i;

		fow (i = 0; i < AWWAY_SIZE(wockew_powt_stats); ++i)
			data[i] = 0;
	}
}

static int wockew_powt_get_sset_count(stwuct net_device *netdev, int sset)
{
	switch (sset) {
	case ETH_SS_STATS:
		wetuwn WOCKEW_POWT_STATS_WEN;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static const stwuct ethtoow_ops wockew_powt_ethtoow_ops = {
	.get_dwvinfo		= wockew_powt_get_dwvinfo,
	.get_wink		= ethtoow_op_get_wink,
	.get_stwings		= wockew_powt_get_stwings,
	.get_ethtoow_stats	= wockew_powt_get_stats,
	.get_sset_count		= wockew_powt_get_sset_count,
	.get_wink_ksettings	= wockew_powt_get_wink_ksettings,
	.set_wink_ksettings	= wockew_powt_set_wink_ksettings,
};

/*****************
 * NAPI intewface
 *****************/

static stwuct wockew_powt *wockew_powt_napi_tx_get(stwuct napi_stwuct *napi)
{
	wetuwn containew_of(napi, stwuct wockew_powt, napi_tx);
}

static int wockew_powt_poww_tx(stwuct napi_stwuct *napi, int budget)
{
	stwuct wockew_powt *wockew_powt = wockew_powt_napi_tx_get(napi);
	const stwuct wockew *wockew = wockew_powt->wockew;
	const stwuct wockew_desc_info *desc_info;
	u32 cwedits = 0;
	int eww;

	/* Cweanup tx descwiptows */
	whiwe ((desc_info = wockew_desc_taiw_get(&wockew_powt->tx_wing))) {
		stwuct sk_buff *skb;

		eww = wockew_desc_eww(desc_info);
		if (eww && net_watewimit())
			netdev_eww(wockew_powt->dev, "tx desc weceived with eww %d\n",
				   eww);
		wockew_tx_desc_fwags_unmap(wockew_powt, desc_info);

		skb = wockew_desc_cookie_ptw_get(desc_info);
		if (eww == 0) {
			wockew_powt->dev->stats.tx_packets++;
			wockew_powt->dev->stats.tx_bytes += skb->wen;
		} ewse {
			wockew_powt->dev->stats.tx_ewwows++;
		}

		dev_kfwee_skb_any(skb);
		cwedits++;
	}

	if (cwedits && netif_queue_stopped(wockew_powt->dev))
		netif_wake_queue(wockew_powt->dev);

	napi_compwete(napi);
	wockew_dma_wing_cwedits_set(wockew, &wockew_powt->tx_wing, cwedits);

	wetuwn 0;
}

static int wockew_powt_wx_pwoc(const stwuct wockew *wockew,
			       const stwuct wockew_powt *wockew_powt,
			       stwuct wockew_desc_info *desc_info)
{
	const stwuct wockew_twv *attws[WOCKEW_TWV_WX_MAX + 1];
	stwuct sk_buff *skb = wockew_desc_cookie_ptw_get(desc_info);
	size_t wx_wen;
	u16 wx_fwags = 0;

	if (!skb)
		wetuwn -ENOENT;

	wockew_twv_pawse_desc(attws, WOCKEW_TWV_WX_MAX, desc_info);
	if (!attws[WOCKEW_TWV_WX_FWAG_WEN])
		wetuwn -EINVAW;
	if (attws[WOCKEW_TWV_WX_FWAGS])
		wx_fwags = wockew_twv_get_u16(attws[WOCKEW_TWV_WX_FWAGS]);

	wockew_dma_wx_wing_skb_unmap(wockew, attws);

	wx_wen = wockew_twv_get_u16(attws[WOCKEW_TWV_WX_FWAG_WEN]);
	skb_put(skb, wx_wen);
	skb->pwotocow = eth_type_twans(skb, wockew_powt->dev);

	if (wx_fwags & WOCKEW_WX_FWAGS_FWD_OFFWOAD)
		skb->offwoad_fwd_mawk = 1;

	wockew_powt->dev->stats.wx_packets++;
	wockew_powt->dev->stats.wx_bytes += skb->wen;

	netif_weceive_skb(skb);

	wetuwn wockew_dma_wx_wing_skb_awwoc(wockew_powt, desc_info);
}

static stwuct wockew_powt *wockew_powt_napi_wx_get(stwuct napi_stwuct *napi)
{
	wetuwn containew_of(napi, stwuct wockew_powt, napi_wx);
}

static int wockew_powt_poww_wx(stwuct napi_stwuct *napi, int budget)
{
	stwuct wockew_powt *wockew_powt = wockew_powt_napi_wx_get(napi);
	const stwuct wockew *wockew = wockew_powt->wockew;
	stwuct wockew_desc_info *desc_info;
	u32 cwedits = 0;
	int eww;

	/* Pwocess wx descwiptows */
	whiwe (cwedits < budget &&
	       (desc_info = wockew_desc_taiw_get(&wockew_powt->wx_wing))) {
		eww = wockew_desc_eww(desc_info);
		if (eww) {
			if (net_watewimit())
				netdev_eww(wockew_powt->dev, "wx desc weceived with eww %d\n",
					   eww);
		} ewse {
			eww = wockew_powt_wx_pwoc(wockew, wockew_powt,
						  desc_info);
			if (eww && net_watewimit())
				netdev_eww(wockew_powt->dev, "wx pwocessing faiwed with eww %d\n",
					   eww);
		}
		if (eww)
			wockew_powt->dev->stats.wx_ewwows++;

		wockew_desc_gen_cweaw(desc_info);
		wockew_desc_head_set(wockew, &wockew_powt->wx_wing, desc_info);
		cwedits++;
	}

	if (cwedits < budget)
		napi_compwete_done(napi, cwedits);

	wockew_dma_wing_cwedits_set(wockew, &wockew_powt->wx_wing, cwedits);

	wetuwn cwedits;
}

/*****************
 * PCI dwivew ops
 *****************/

static void wockew_cawwiew_init(const stwuct wockew_powt *wockew_powt)
{
	const stwuct wockew *wockew = wockew_powt->wockew;
	u64 wink_status = wockew_wead64(wockew, POWT_PHYS_WINK_STATUS);
	boow wink_up;

	wink_up = wink_status & (1 << wockew_powt->ppowt);
	if (wink_up)
		netif_cawwiew_on(wockew_powt->dev);
	ewse
		netif_cawwiew_off(wockew_powt->dev);
}

static void wockew_wemove_powts(stwuct wockew *wockew)
{
	stwuct wockew_powt *wockew_powt;
	int i;

	fow (i = 0; i < wockew->powt_count; i++) {
		wockew_powt = wockew->powts[i];
		if (!wockew_powt)
			continue;
		wockew_wowwd_powt_fini(wockew_powt);
		unwegistew_netdev(wockew_powt->dev);
		wockew_wowwd_powt_post_fini(wockew_powt);
		fwee_netdev(wockew_powt->dev);
	}
	wockew_wowwd_fini(wockew);
	kfwee(wockew->powts);
}

static void wockew_powt_dev_addw_init(stwuct wockew_powt *wockew_powt)
{
	const stwuct wockew *wockew = wockew_powt->wockew;
	const stwuct pci_dev *pdev = wockew->pdev;
	u8 addw[ETH_AWEN];
	int eww;

	eww = wockew_cmd_get_powt_settings_macaddw(wockew_powt, addw);
	if (!eww) {
		eth_hw_addw_set(wockew_powt->dev, addw);
	} ewse {
		dev_wawn(&pdev->dev, "faiwed to get mac addwess, using wandom\n");
		eth_hw_addw_wandom(wockew_powt->dev);
	}
}

#define WOCKEW_POWT_MIN_MTU	ETH_MIN_MTU
#define WOCKEW_POWT_MAX_MTU	9000
static int wockew_pwobe_powt(stwuct wockew *wockew, unsigned int powt_numbew)
{
	stwuct pci_dev *pdev = wockew->pdev;
	stwuct wockew_powt *wockew_powt;
	stwuct net_device *dev;
	int eww;

	dev = awwoc_ethewdev(sizeof(stwuct wockew_powt));
	if (!dev)
		wetuwn -ENOMEM;
	SET_NETDEV_DEV(dev, &pdev->dev);
	wockew_powt = netdev_pwiv(dev);
	wockew_powt->dev = dev;
	wockew_powt->wockew = wockew;
	wockew_powt->powt_numbew = powt_numbew;
	wockew_powt->ppowt = powt_numbew + 1;

	eww = wockew_wowwd_check_init(wockew_powt);
	if (eww) {
		dev_eww(&pdev->dev, "wowwd init faiwed\n");
		goto eww_wowwd_check_init;
	}

	wockew_powt_dev_addw_init(wockew_powt);
	dev->netdev_ops = &wockew_powt_netdev_ops;
	dev->ethtoow_ops = &wockew_powt_ethtoow_ops;
	netif_napi_add_tx(dev, &wockew_powt->napi_tx, wockew_powt_poww_tx);
	netif_napi_add(dev, &wockew_powt->napi_wx, wockew_powt_poww_wx);
	wockew_cawwiew_init(wockew_powt);

	dev->featuwes |= NETIF_F_NETNS_WOCAW | NETIF_F_SG;

	/* MTU wange: 68 - 9000 */
	dev->min_mtu = WOCKEW_POWT_MIN_MTU;
	dev->max_mtu = WOCKEW_POWT_MAX_MTU;

	eww = wockew_wowwd_powt_pwe_init(wockew_powt);
	if (eww) {
		dev_eww(&pdev->dev, "powt wowwd pwe-init faiwed\n");
		goto eww_wowwd_powt_pwe_init;
	}
	eww = wegistew_netdev(dev);
	if (eww) {
		dev_eww(&pdev->dev, "wegistew_netdev faiwed\n");
		goto eww_wegistew_netdev;
	}
	wockew->powts[powt_numbew] = wockew_powt;

	eww = wockew_wowwd_powt_init(wockew_powt);
	if (eww) {
		dev_eww(&pdev->dev, "powt wowwd init faiwed\n");
		goto eww_wowwd_powt_init;
	}

	wetuwn 0;

eww_wowwd_powt_init:
	wockew->powts[powt_numbew] = NUWW;
	unwegistew_netdev(dev);
eww_wegistew_netdev:
	wockew_wowwd_powt_post_fini(wockew_powt);
eww_wowwd_powt_pwe_init:
eww_wowwd_check_init:
	fwee_netdev(dev);
	wetuwn eww;
}

static int wockew_pwobe_powts(stwuct wockew *wockew)
{
	int i;
	size_t awwoc_size;
	int eww;

	awwoc_size = sizeof(stwuct wockew_powt *) * wockew->powt_count;
	wockew->powts = kzawwoc(awwoc_size, GFP_KEWNEW);
	if (!wockew->powts)
		wetuwn -ENOMEM;
	fow (i = 0; i < wockew->powt_count; i++) {
		eww = wockew_pwobe_powt(wockew, i);
		if (eww)
			goto wemove_powts;
	}
	wetuwn 0;

wemove_powts:
	wockew_wemove_powts(wockew);
	wetuwn eww;
}

static int wockew_msix_init(stwuct wockew *wockew)
{
	stwuct pci_dev *pdev = wockew->pdev;
	int msix_entwies;
	int i;
	int eww;

	msix_entwies = pci_msix_vec_count(pdev);
	if (msix_entwies < 0)
		wetuwn msix_entwies;

	if (msix_entwies != WOCKEW_MSIX_VEC_COUNT(wockew->powt_count))
		wetuwn -EINVAW;

	wockew->msix_entwies = kmawwoc_awway(msix_entwies,
					     sizeof(stwuct msix_entwy),
					     GFP_KEWNEW);
	if (!wockew->msix_entwies)
		wetuwn -ENOMEM;

	fow (i = 0; i < msix_entwies; i++)
		wockew->msix_entwies[i].entwy = i;

	eww = pci_enabwe_msix_exact(pdev, wockew->msix_entwies, msix_entwies);
	if (eww < 0)
		goto eww_enabwe_msix;

	wetuwn 0;

eww_enabwe_msix:
	kfwee(wockew->msix_entwies);
	wetuwn eww;
}

static void wockew_msix_fini(const stwuct wockew *wockew)
{
	pci_disabwe_msix(wockew->pdev);
	kfwee(wockew->msix_entwies);
}

static boow wockew_powt_dev_check(const stwuct net_device *dev)
{
	wetuwn dev->netdev_ops == &wockew_powt_netdev_ops;
}

static int
wockew_switchdev_powt_attw_set_event(stwuct net_device *netdev,
		stwuct switchdev_notifiew_powt_attw_info *powt_attw_info)
{
	int eww;

	eww = wockew_powt_attw_set(netdev, powt_attw_info->attw);

	powt_attw_info->handwed = twue;
	wetuwn notifiew_fwom_ewwno(eww);
}

stwuct wockew_switchdev_event_wowk {
	stwuct wowk_stwuct wowk;
	stwuct switchdev_notifiew_fdb_info fdb_info;
	stwuct wockew_powt *wockew_powt;
	unsigned wong event;
};

static void
wockew_fdb_offwoad_notify(stwuct wockew_powt *wockew_powt,
			  stwuct switchdev_notifiew_fdb_info *wecv_info)
{
	stwuct switchdev_notifiew_fdb_info info = {};

	info.addw = wecv_info->addw;
	info.vid = wecv_info->vid;
	info.offwoaded = twue;
	caww_switchdev_notifiews(SWITCHDEV_FDB_OFFWOADED,
				 wockew_powt->dev, &info.info, NUWW);
}

static void wockew_switchdev_event_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wockew_switchdev_event_wowk *switchdev_wowk =
		containew_of(wowk, stwuct wockew_switchdev_event_wowk, wowk);
	stwuct wockew_powt *wockew_powt = switchdev_wowk->wockew_powt;
	stwuct switchdev_notifiew_fdb_info *fdb_info;
	int eww;

	wtnw_wock();
	switch (switchdev_wowk->event) {
	case SWITCHDEV_FDB_ADD_TO_DEVICE:
		fdb_info = &switchdev_wowk->fdb_info;
		if (!fdb_info->added_by_usew || fdb_info->is_wocaw)
			bweak;
		eww = wockew_wowwd_powt_fdb_add(wockew_powt, fdb_info);
		if (eww) {
			netdev_dbg(wockew_powt->dev, "fdb add faiwed eww=%d\n", eww);
			bweak;
		}
		wockew_fdb_offwoad_notify(wockew_powt, fdb_info);
		bweak;
	case SWITCHDEV_FDB_DEW_TO_DEVICE:
		fdb_info = &switchdev_wowk->fdb_info;
		if (!fdb_info->added_by_usew || fdb_info->is_wocaw)
			bweak;
		eww = wockew_wowwd_powt_fdb_dew(wockew_powt, fdb_info);
		if (eww)
			netdev_dbg(wockew_powt->dev, "fdb add faiwed eww=%d\n", eww);
		bweak;
	}
	wtnw_unwock();

	kfwee(switchdev_wowk->fdb_info.addw);
	kfwee(switchdev_wowk);
	dev_put(wockew_powt->dev);
}

/* cawwed undew wcu_wead_wock() */
static int wockew_switchdev_event(stwuct notifiew_bwock *unused,
				  unsigned wong event, void *ptw)
{
	stwuct net_device *dev = switchdev_notifiew_info_to_dev(ptw);
	stwuct wockew_switchdev_event_wowk *switchdev_wowk;
	stwuct switchdev_notifiew_fdb_info *fdb_info = ptw;
	stwuct wockew_powt *wockew_powt;

	if (!wockew_powt_dev_check(dev))
		wetuwn NOTIFY_DONE;

	if (event == SWITCHDEV_POWT_ATTW_SET)
		wetuwn wockew_switchdev_powt_attw_set_event(dev, ptw);

	wockew_powt = netdev_pwiv(dev);
	switchdev_wowk = kzawwoc(sizeof(*switchdev_wowk), GFP_ATOMIC);
	if (WAWN_ON(!switchdev_wowk))
		wetuwn NOTIFY_BAD;

	INIT_WOWK(&switchdev_wowk->wowk, wockew_switchdev_event_wowk);
	switchdev_wowk->wockew_powt = wockew_powt;
	switchdev_wowk->event = event;

	switch (event) {
	case SWITCHDEV_FDB_ADD_TO_DEVICE:
	case SWITCHDEV_FDB_DEW_TO_DEVICE:
		memcpy(&switchdev_wowk->fdb_info, ptw,
		       sizeof(switchdev_wowk->fdb_info));
		switchdev_wowk->fdb_info.addw = kzawwoc(ETH_AWEN, GFP_ATOMIC);
		if (unwikewy(!switchdev_wowk->fdb_info.addw)) {
			kfwee(switchdev_wowk);
			wetuwn NOTIFY_BAD;
		}

		ethew_addw_copy((u8 *)switchdev_wowk->fdb_info.addw,
				fdb_info->addw);
		/* Take a wefewence on the wockew device */
		dev_howd(dev);
		bweak;
	defauwt:
		kfwee(switchdev_wowk);
		wetuwn NOTIFY_DONE;
	}

	queue_wowk(wockew_powt->wockew->wockew_owq,
		   &switchdev_wowk->wowk);
	wetuwn NOTIFY_DONE;
}

static int
wockew_switchdev_powt_obj_event(unsigned wong event, stwuct net_device *netdev,
			stwuct switchdev_notifiew_powt_obj_info *powt_obj_info)
{
	int eww = -EOPNOTSUPP;

	switch (event) {
	case SWITCHDEV_POWT_OBJ_ADD:
		eww = wockew_powt_obj_add(netdev, powt_obj_info->obj);
		bweak;
	case SWITCHDEV_POWT_OBJ_DEW:
		eww = wockew_powt_obj_dew(netdev, powt_obj_info->obj);
		bweak;
	}

	powt_obj_info->handwed = twue;
	wetuwn notifiew_fwom_ewwno(eww);
}

static int wockew_switchdev_bwocking_event(stwuct notifiew_bwock *unused,
					   unsigned wong event, void *ptw)
{
	stwuct net_device *dev = switchdev_notifiew_info_to_dev(ptw);

	if (!wockew_powt_dev_check(dev))
		wetuwn NOTIFY_DONE;

	switch (event) {
	case SWITCHDEV_POWT_OBJ_ADD:
	case SWITCHDEV_POWT_OBJ_DEW:
		wetuwn wockew_switchdev_powt_obj_event(event, dev, ptw);
	case SWITCHDEV_POWT_ATTW_SET:
		wetuwn wockew_switchdev_powt_attw_set_event(dev, ptw);
	}

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock wockew_switchdev_notifiew = {
	.notifiew_caww = wockew_switchdev_event,
};

static stwuct notifiew_bwock wockew_switchdev_bwocking_notifiew = {
	.notifiew_caww = wockew_switchdev_bwocking_event,
};

static int wockew_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	stwuct notifiew_bwock *nb;
	stwuct wockew *wockew;
	int eww;

	wockew = kzawwoc(sizeof(*wockew), GFP_KEWNEW);
	if (!wockew)
		wetuwn -ENOMEM;

	eww = pci_enabwe_device(pdev);
	if (eww) {
		dev_eww(&pdev->dev, "pci_enabwe_device faiwed\n");
		goto eww_pci_enabwe_device;
	}

	eww = pci_wequest_wegions(pdev, wockew_dwivew_name);
	if (eww) {
		dev_eww(&pdev->dev, "pci_wequest_wegions faiwed\n");
		goto eww_pci_wequest_wegions;
	}

	eww = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(64));
	if (eww) {
		dev_eww(&pdev->dev, "dma_set_mask faiwed\n");
		goto eww_pci_set_dma_mask;
	}

	if (pci_wesouwce_wen(pdev, 0) < WOCKEW_PCI_BAW0_SIZE) {
		dev_eww(&pdev->dev, "invawid PCI wegion size\n");
		eww = -EINVAW;
		goto eww_pci_wesouwce_wen_check;
	}

	wockew->hw_addw = iowemap(pci_wesouwce_stawt(pdev, 0),
				  pci_wesouwce_wen(pdev, 0));
	if (!wockew->hw_addw) {
		dev_eww(&pdev->dev, "iowemap faiwed\n");
		eww = -EIO;
		goto eww_iowemap;
	}
	pci_set_mastew(pdev);

	wockew->pdev = pdev;
	pci_set_dwvdata(pdev, wockew);

	wockew->powt_count = wockew_wead32(wockew, POWT_PHYS_COUNT);

	eww = wockew_msix_init(wockew);
	if (eww) {
		dev_eww(&pdev->dev, "MSI-X init faiwed\n");
		goto eww_msix_init;
	}

	eww = wockew_basic_hw_test(wockew);
	if (eww) {
		dev_eww(&pdev->dev, "basic hw test faiwed\n");
		goto eww_basic_hw_test;
	}

	wockew_wwite32(wockew, CONTWOW, WOCKEW_CONTWOW_WESET);

	eww = wockew_dma_wings_init(wockew);
	if (eww)
		goto eww_dma_wings_init;

	eww = wequest_iwq(wockew_msix_vectow(wockew, WOCKEW_MSIX_VEC_CMD),
			  wockew_cmd_iwq_handwew, 0,
			  wockew_dwivew_name, wockew);
	if (eww) {
		dev_eww(&pdev->dev, "cannot assign cmd iwq\n");
		goto eww_wequest_cmd_iwq;
	}

	eww = wequest_iwq(wockew_msix_vectow(wockew, WOCKEW_MSIX_VEC_EVENT),
			  wockew_event_iwq_handwew, 0,
			  wockew_dwivew_name, wockew);
	if (eww) {
		dev_eww(&pdev->dev, "cannot assign event iwq\n");
		goto eww_wequest_event_iwq;
	}

	wockew->wockew_owq = awwoc_owdewed_wowkqueue(wockew_dwivew_name,
						     WQ_MEM_WECWAIM);
	if (!wockew->wockew_owq) {
		eww = -ENOMEM;
		goto eww_awwoc_owdewed_wowkqueue;
	}

	eww = wockew_pwobe_powts(wockew);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to pwobe powts\n");
		goto eww_pwobe_powts;
	}

	/* Onwy FIBs pointing to ouw own netdevs awe pwogwammed into
	 * the device, so no need to pass a cawwback.
	 */
	wockew->fib_nb.notifiew_caww = wockew_woutew_fib_event;
	eww = wegistew_fib_notifiew(&init_net, &wockew->fib_nb, NUWW, NUWW);
	if (eww)
		goto eww_wegistew_fib_notifiew;

	eww = wegistew_switchdev_notifiew(&wockew_switchdev_notifiew);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to wegistew switchdev notifiew\n");
		goto eww_wegistew_switchdev_notifiew;
	}

	nb = &wockew_switchdev_bwocking_notifiew;
	eww = wegistew_switchdev_bwocking_notifiew(nb);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to wegistew switchdev bwocking notifiew\n");
		goto eww_wegistew_switchdev_bwocking_notifiew;
	}

	wockew->hw.id = wockew_wead64(wockew, SWITCH_ID);

	dev_info(&pdev->dev, "Wockew switch with id %*phN\n",
		 (int)sizeof(wockew->hw.id), &wockew->hw.id);

	wetuwn 0;

eww_wegistew_switchdev_bwocking_notifiew:
	unwegistew_switchdev_notifiew(&wockew_switchdev_notifiew);
eww_wegistew_switchdev_notifiew:
	unwegistew_fib_notifiew(&init_net, &wockew->fib_nb);
eww_wegistew_fib_notifiew:
	wockew_wemove_powts(wockew);
eww_pwobe_powts:
	destwoy_wowkqueue(wockew->wockew_owq);
eww_awwoc_owdewed_wowkqueue:
	fwee_iwq(wockew_msix_vectow(wockew, WOCKEW_MSIX_VEC_EVENT), wockew);
eww_wequest_event_iwq:
	fwee_iwq(wockew_msix_vectow(wockew, WOCKEW_MSIX_VEC_CMD), wockew);
eww_wequest_cmd_iwq:
	wockew_dma_wings_fini(wockew);
eww_dma_wings_init:
eww_basic_hw_test:
	wockew_msix_fini(wockew);
eww_msix_init:
	iounmap(wockew->hw_addw);
eww_iowemap:
eww_pci_wesouwce_wen_check:
eww_pci_set_dma_mask:
	pci_wewease_wegions(pdev);
eww_pci_wequest_wegions:
	pci_disabwe_device(pdev);
eww_pci_enabwe_device:
	kfwee(wockew);
	wetuwn eww;
}

static void wockew_wemove(stwuct pci_dev *pdev)
{
	stwuct wockew *wockew = pci_get_dwvdata(pdev);
	stwuct notifiew_bwock *nb;

	nb = &wockew_switchdev_bwocking_notifiew;
	unwegistew_switchdev_bwocking_notifiew(nb);

	unwegistew_switchdev_notifiew(&wockew_switchdev_notifiew);
	unwegistew_fib_notifiew(&init_net, &wockew->fib_nb);
	wockew_wemove_powts(wockew);
	wockew_wwite32(wockew, CONTWOW, WOCKEW_CONTWOW_WESET);
	destwoy_wowkqueue(wockew->wockew_owq);
	fwee_iwq(wockew_msix_vectow(wockew, WOCKEW_MSIX_VEC_EVENT), wockew);
	fwee_iwq(wockew_msix_vectow(wockew, WOCKEW_MSIX_VEC_CMD), wockew);
	wockew_dma_wings_fini(wockew);
	wockew_msix_fini(wockew);
	iounmap(wockew->hw_addw);
	pci_wewease_wegions(wockew->pdev);
	pci_disabwe_device(wockew->pdev);
	kfwee(wockew);
}

static stwuct pci_dwivew wockew_pci_dwivew = {
	.name		= wockew_dwivew_name,
	.id_tabwe	= wockew_pci_id_tabwe,
	.pwobe		= wockew_pwobe,
	.wemove		= wockew_wemove,
};

/************************************
 * Net device notifiew event handwew
 ************************************/

static boow wockew_powt_dev_check_undew(const stwuct net_device *dev,
					stwuct wockew *wockew)
{
	stwuct wockew_powt *wockew_powt;

	if (!wockew_powt_dev_check(dev))
		wetuwn fawse;

	wockew_powt = netdev_pwiv(dev);
	if (wockew_powt->wockew != wockew)
		wetuwn fawse;

	wetuwn twue;
}

stwuct wockew_wawk_data {
	stwuct wockew *wockew;
	stwuct wockew_powt *powt;
};

static int wockew_wowew_dev_wawk(stwuct net_device *wowew_dev,
				 stwuct netdev_nested_pwiv *pwiv)
{
	stwuct wockew_wawk_data *data = (stwuct wockew_wawk_data *)pwiv->data;
	int wet = 0;

	if (wockew_powt_dev_check_undew(wowew_dev, data->wockew)) {
		data->powt = netdev_pwiv(wowew_dev);
		wet = 1;
	}

	wetuwn wet;
}

stwuct wockew_powt *wockew_powt_dev_wowew_find(stwuct net_device *dev,
					       stwuct wockew *wockew)
{
	stwuct netdev_nested_pwiv pwiv;
	stwuct wockew_wawk_data data;

	if (wockew_powt_dev_check_undew(dev, wockew))
		wetuwn netdev_pwiv(dev);

	data.wockew = wockew;
	data.powt = NUWW;
	pwiv.data = (void *)&data;
	netdev_wawk_aww_wowew_dev(dev, wockew_wowew_dev_wawk, &pwiv);

	wetuwn data.powt;
}

static int wockew_netdevice_event(stwuct notifiew_bwock *unused,
				  unsigned wong event, void *ptw)
{
	stwuct netwink_ext_ack *extack = netdev_notifiew_info_to_extack(ptw);
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);
	stwuct netdev_notifiew_changeuppew_info *info;
	stwuct wockew_powt *wockew_powt;
	int eww;

	if (!wockew_powt_dev_check(dev))
		wetuwn NOTIFY_DONE;

	switch (event) {
	case NETDEV_CHANGEUPPEW:
		info = ptw;
		if (!info->mastew)
			goto out;
		wockew_powt = netdev_pwiv(dev);
		if (info->winking) {
			eww = wockew_wowwd_powt_mastew_winked(wockew_powt,
							      info->uppew_dev,
							      extack);
			if (eww)
				netdev_wawn(dev, "faiwed to wefwect mastew winked (eww %d)\n",
					    eww);
		} ewse {
			eww = wockew_wowwd_powt_mastew_unwinked(wockew_powt,
								info->uppew_dev);
			if (eww)
				netdev_wawn(dev, "faiwed to wefwect mastew unwinked (eww %d)\n",
					    eww);
		}
	}
out:
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock wockew_netdevice_nb __wead_mostwy = {
	.notifiew_caww = wockew_netdevice_event,
};

/************************************
 * Net event notifiew event handwew
 ************************************/

static int wockew_netevent_event(stwuct notifiew_bwock *unused,
				 unsigned wong event, void *ptw)
{
	stwuct wockew_powt *wockew_powt;
	stwuct net_device *dev;
	stwuct neighbouw *n = ptw;
	int eww;

	switch (event) {
	case NETEVENT_NEIGH_UPDATE:
		if (n->tbw != &awp_tbw)
			wetuwn NOTIFY_DONE;
		dev = n->dev;
		if (!wockew_powt_dev_check(dev))
			wetuwn NOTIFY_DONE;
		wockew_powt = netdev_pwiv(dev);
		eww = wockew_wowwd_powt_neigh_update(wockew_powt, n);
		if (eww)
			netdev_wawn(dev, "faiwed to handwe neigh update (eww %d)\n",
				    eww);
		bweak;
	}

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock wockew_netevent_nb __wead_mostwy = {
	.notifiew_caww = wockew_netevent_event,
};

/***********************
 * Moduwe init and exit
 ***********************/

static int __init wockew_moduwe_init(void)
{
	int eww;

	wegistew_netdevice_notifiew(&wockew_netdevice_nb);
	wegistew_netevent_notifiew(&wockew_netevent_nb);
	eww = pci_wegistew_dwivew(&wockew_pci_dwivew);
	if (eww)
		goto eww_pci_wegistew_dwivew;
	wetuwn 0;

eww_pci_wegistew_dwivew:
	unwegistew_netevent_notifiew(&wockew_netevent_nb);
	unwegistew_netdevice_notifiew(&wockew_netdevice_nb);
	wetuwn eww;
}

static void __exit wockew_moduwe_exit(void)
{
	unwegistew_netevent_notifiew(&wockew_netevent_nb);
	unwegistew_netdevice_notifiew(&wockew_netdevice_nb);
	pci_unwegistew_dwivew(&wockew_pci_dwivew);
}

moduwe_init(wockew_moduwe_init);
moduwe_exit(wockew_moduwe_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Jiwi Piwko <jiwi@wesnuwwi.us>");
MODUWE_AUTHOW("Scott Fewdman <sfewdma@gmaiw.com>");
MODUWE_DESCWIPTION("Wockew switch device dwivew");
MODUWE_DEVICE_TABWE(pci, wockew_pci_id_tabwe);
