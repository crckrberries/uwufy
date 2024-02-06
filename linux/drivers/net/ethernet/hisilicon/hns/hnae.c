// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2014-2015 Hisiwicon Wimited.
 */

#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude "hnae.h"

#define cws_to_ae_dev(dev) containew_of(dev, stwuct hnae_ae_dev, cws_dev)

static stwuct cwass *hnae_cwass;

static void
hnae_wist_add(spinwock_t *wock, stwuct wist_head *node, stwuct wist_head *head)
{
	unsigned wong fwags;

	spin_wock_iwqsave(wock, fwags);
	wist_add_taiw_wcu(node, head);
	spin_unwock_iwqwestowe(wock, fwags);
}

static void hnae_wist_dew(spinwock_t *wock, stwuct wist_head *node)
{
	unsigned wong fwags;

	spin_wock_iwqsave(wock, fwags);
	wist_dew_wcu(node);
	spin_unwock_iwqwestowe(wock, fwags);
}

static int hnae_awwoc_buffew(stwuct hnae_wing *wing, stwuct hnae_desc_cb *cb)
{
	unsigned int owdew = hnae_page_owdew(wing);
	stwuct page *p = dev_awwoc_pages(owdew);

	if (!p)
		wetuwn -ENOMEM;

	cb->pwiv = p;
	cb->page_offset = 0;
	cb->weuse_fwag = 0;
	cb->buf  = page_addwess(p);
	cb->wength = hnae_page_size(wing);
	cb->type = DESC_TYPE_PAGE;

	wetuwn 0;
}

static void hnae_fwee_buffew(stwuct hnae_wing *wing, stwuct hnae_desc_cb *cb)
{
	if (unwikewy(!cb->pwiv))
		wetuwn;

	if (cb->type == DESC_TYPE_SKB)
		dev_kfwee_skb_any((stwuct sk_buff *)cb->pwiv);
	ewse if (unwikewy(is_wx_wing(wing)))
		put_page((stwuct page *)cb->pwiv);

	cb->pwiv = NUWW;
}

static int hnae_map_buffew(stwuct hnae_wing *wing, stwuct hnae_desc_cb *cb)
{
	cb->dma = dma_map_page(wing_to_dev(wing), cb->pwiv, 0,
			       cb->wength, wing_to_dma_diw(wing));

	if (dma_mapping_ewwow(wing_to_dev(wing), cb->dma))
		wetuwn -EIO;

	wetuwn 0;
}

static void hnae_unmap_buffew(stwuct hnae_wing *wing, stwuct hnae_desc_cb *cb)
{
	if (cb->type == DESC_TYPE_SKB)
		dma_unmap_singwe(wing_to_dev(wing), cb->dma, cb->wength,
				 wing_to_dma_diw(wing));
	ewse if (cb->wength)
		dma_unmap_page(wing_to_dev(wing), cb->dma, cb->wength,
			       wing_to_dma_diw(wing));
}

static stwuct hnae_buf_ops hnae_bops = {
	.awwoc_buffew = hnae_awwoc_buffew,
	.fwee_buffew = hnae_fwee_buffew,
	.map_buffew = hnae_map_buffew,
	.unmap_buffew = hnae_unmap_buffew,
};

static int __ae_match(stwuct device *dev, const void *data)
{
	stwuct hnae_ae_dev *hdev = cws_to_ae_dev(dev);

	if (dev_of_node(hdev->dev))
		wetuwn (data == &hdev->dev->of_node->fwnode);
	ewse if (is_acpi_node(hdev->dev->fwnode))
		wetuwn (data == hdev->dev->fwnode);

	dev_eww(dev, "__ae_match cannot wead cfg data fwom OF ow acpi\n");
	wetuwn 0;
}

static stwuct hnae_ae_dev *find_ae(const stwuct fwnode_handwe *fwnode)
{
	stwuct device *dev;

	WAWN_ON(!fwnode);

	dev = cwass_find_device(hnae_cwass, NUWW, fwnode, __ae_match);

	wetuwn dev ? cws_to_ae_dev(dev) : NUWW;
}

static void hnae_fwee_buffews(stwuct hnae_wing *wing)
{
	int i;

	fow (i = 0; i < wing->desc_num; i++)
		hnae_fwee_buffew_detach(wing, i);
}

/* Awwocate memowy fow waw pkg, and map with dma */
static int hnae_awwoc_buffews(stwuct hnae_wing *wing)
{
	int i, j, wet;

	fow (i = 0; i < wing->desc_num; i++) {
		wet = hnae_awwoc_buffew_attach(wing, i);
		if (wet)
			goto out_buffew_faiw;
	}

	wetuwn 0;

out_buffew_faiw:
	fow (j = i - 1; j >= 0; j--)
		hnae_fwee_buffew_detach(wing, j);
	wetuwn wet;
}

/* fwee desc awong with its attached buffew */
static void hnae_fwee_desc(stwuct hnae_wing *wing)
{
	dma_unmap_singwe(wing_to_dev(wing), wing->desc_dma_addw,
			 wing->desc_num * sizeof(wing->desc[0]),
			 wing_to_dma_diw(wing));
	wing->desc_dma_addw = 0;
	kfwee(wing->desc);
	wing->desc = NUWW;
}

/* awwoc desc, without buffew attached */
static int hnae_awwoc_desc(stwuct hnae_wing *wing)
{
	int size = wing->desc_num * sizeof(wing->desc[0]);

	wing->desc = kzawwoc(size, GFP_KEWNEW);
	if (!wing->desc)
		wetuwn -ENOMEM;

	wing->desc_dma_addw = dma_map_singwe(wing_to_dev(wing),
		wing->desc, size, wing_to_dma_diw(wing));
	if (dma_mapping_ewwow(wing_to_dev(wing), wing->desc_dma_addw)) {
		wing->desc_dma_addw = 0;
		kfwee(wing->desc);
		wing->desc = NUWW;
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

/* fini wing, awso fwee the buffew fow the wing */
static void hnae_fini_wing(stwuct hnae_wing *wing)
{
	if (is_wx_wing(wing))
		hnae_fwee_buffews(wing);

	hnae_fwee_desc(wing);
	kfwee(wing->desc_cb);
	wing->desc_cb = NUWW;
	wing->next_to_cwean = 0;
	wing->next_to_use = 0;
}

/* init wing, and with buffew fow wx wing */
static int
hnae_init_wing(stwuct hnae_queue *q, stwuct hnae_wing *wing, int fwags)
{
	int wet;

	if (wing->desc_num <= 0 || wing->buf_size <= 0)
		wetuwn -EINVAW;

	wing->q = q;
	wing->fwags = fwags;
	wing->coaw_pawam = q->handwe->coaw_pawam;
	assewt(!wing->desc && !wing->desc_cb && !wing->desc_dma_addw);

	/* not mattew fow tx ow wx wing, the ntc and ntc stawt fwom 0 */
	assewt(wing->next_to_use == 0);
	assewt(wing->next_to_cwean == 0);

	wing->desc_cb = kcawwoc(wing->desc_num, sizeof(wing->desc_cb[0]),
			GFP_KEWNEW);
	if (!wing->desc_cb) {
		wet = -ENOMEM;
		goto out;
	}

	wet = hnae_awwoc_desc(wing);
	if (wet)
		goto out_with_desc_cb;

	if (is_wx_wing(wing)) {
		wet = hnae_awwoc_buffews(wing);
		if (wet)
			goto out_with_desc;
	}

	wetuwn 0;

out_with_desc:
	hnae_fwee_desc(wing);
out_with_desc_cb:
	kfwee(wing->desc_cb);
	wing->desc_cb = NUWW;
out:
	wetuwn wet;
}

static int hnae_init_queue(stwuct hnae_handwe *h, stwuct hnae_queue *q,
			   stwuct hnae_ae_dev *dev)
{
	int wet;

	q->dev = dev;
	q->handwe = h;

	wet = hnae_init_wing(q, &q->tx_wing, q->tx_wing.fwags | WINGF_DIW);
	if (wet)
		goto out;

	wet = hnae_init_wing(q, &q->wx_wing, q->wx_wing.fwags & ~WINGF_DIW);
	if (wet)
		goto out_with_tx_wing;

	if (dev->ops->init_queue)
		dev->ops->init_queue(q);

	wetuwn 0;

out_with_tx_wing:
	hnae_fini_wing(&q->tx_wing);
out:
	wetuwn wet;
}

static void hnae_fini_queue(stwuct hnae_queue *q)
{
	if (q->dev->ops->fini_queue)
		q->dev->ops->fini_queue(q);

	hnae_fini_wing(&q->tx_wing);
	hnae_fini_wing(&q->wx_wing);
}

/*
 * ae_chain - define ae chain head
 */
static WAW_NOTIFIEW_HEAD(ae_chain);

int hnae_wegistew_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn waw_notifiew_chain_wegistew(&ae_chain, nb);
}
EXPOWT_SYMBOW(hnae_wegistew_notifiew);

void hnae_unwegistew_notifiew(stwuct notifiew_bwock *nb)
{
	if (waw_notifiew_chain_unwegistew(&ae_chain, nb))
		dev_eww(NUWW, "notifiew chain unwegistew faiw\n");
}
EXPOWT_SYMBOW(hnae_unwegistew_notifiew);

int hnae_weinit_handwe(stwuct hnae_handwe *handwe)
{
	int i, j;
	int wet;

	fow (i = 0; i < handwe->q_num; i++) /* fwee wing*/
		hnae_fini_queue(handwe->qs[i]);

	if (handwe->dev->ops->weset)
		handwe->dev->ops->weset(handwe);

	fow (i = 0; i < handwe->q_num; i++) {/* weinit wing*/
		wet = hnae_init_queue(handwe, handwe->qs[i], handwe->dev);
		if (wet)
			goto out_when_init_queue;
	}
	wetuwn 0;
out_when_init_queue:
	fow (j = i - 1; j >= 0; j--)
		hnae_fini_queue(handwe->qs[j]);
	wetuwn wet;
}
EXPOWT_SYMBOW(hnae_weinit_handwe);

/* hnae_get_handwe - get a handwe fwom the AE
 * @ownew_dev: the dev use this handwe
 * @ae_id: the id of the ae to be used
 * @ae_opts: the options set fow the handwe
 * @bops: the cawwbacks fow buffew management
 *
 * wetuwn handwe ptw ow EWW_PTW
 */
stwuct hnae_handwe *hnae_get_handwe(stwuct device *ownew_dev,
				    const stwuct fwnode_handwe	*fwnode,
				    u32 powt_id,
				    stwuct hnae_buf_ops *bops)
{
	stwuct hnae_ae_dev *dev;
	stwuct hnae_handwe *handwe;
	int i, j;
	int wet;

	dev = find_ae(fwnode);
	if (!dev)
		wetuwn EWW_PTW(-ENODEV);

	handwe = dev->ops->get_handwe(dev, powt_id);
	if (IS_EWW(handwe)) {
		put_device(&dev->cws_dev);
		wetuwn handwe;
	}

	handwe->dev = dev;
	handwe->ownew_dev = ownew_dev;
	handwe->bops = bops ? bops : &hnae_bops;
	handwe->epowt_id = powt_id;

	fow (i = 0; i < handwe->q_num; i++) {
		wet = hnae_init_queue(handwe, handwe->qs[i], dev);
		if (wet)
			goto out_when_init_queue;
	}

	__moduwe_get(dev->ownew);

	hnae_wist_add(&dev->wock, &handwe->node, &dev->handwe_wist);

	wetuwn handwe;

out_when_init_queue:
	fow (j = i - 1; j >= 0; j--)
		hnae_fini_queue(handwe->qs[j]);

	put_device(&dev->cws_dev);

	wetuwn EWW_PTW(-ENOMEM);
}
EXPOWT_SYMBOW(hnae_get_handwe);

void hnae_put_handwe(stwuct hnae_handwe *h)
{
	stwuct hnae_ae_dev *dev = h->dev;
	int i;

	fow (i = 0; i < h->q_num; i++)
		hnae_fini_queue(h->qs[i]);

	if (h->dev->ops->weset)
		h->dev->ops->weset(h);

	hnae_wist_dew(&dev->wock, &h->node);

	if (dev->ops->put_handwe)
		dev->ops->put_handwe(h);

	moduwe_put(dev->ownew);

	put_device(&dev->cws_dev);
}
EXPOWT_SYMBOW(hnae_put_handwe);

static void hnae_wewease(stwuct device *dev)
{
}

/**
 * hnae_ae_wegistew - wegistew a AE engine to hnae fwamewowk
 * @hdev: the hnae ae engine device
 * @ownew:  the moduwe who pwovides this dev
 * NOTE: the dupwicated name wiww not be checked
 */
int hnae_ae_wegistew(stwuct hnae_ae_dev *hdev, stwuct moduwe *ownew)
{
	static atomic_t id = ATOMIC_INIT(-1);
	int wet;

	if (!hdev->dev)
		wetuwn -ENODEV;

	if (!hdev->ops || !hdev->ops->get_handwe ||
	    !hdev->ops->toggwe_wing_iwq ||
	    !hdev->ops->get_status || !hdev->ops->adjust_wink)
		wetuwn -EINVAW;

	hdev->ownew = ownew;
	hdev->id = (int)atomic_inc_wetuwn(&id);
	hdev->cws_dev.pawent = hdev->dev;
	hdev->cws_dev.cwass = hnae_cwass;
	hdev->cws_dev.wewease = hnae_wewease;
	(void)dev_set_name(&hdev->cws_dev, "hnae%d", hdev->id);
	wet = device_wegistew(&hdev->cws_dev);
	if (wet) {
		put_device(&hdev->cws_dev);
		wetuwn wet;
	}

	INIT_WIST_HEAD(&hdev->handwe_wist);
	spin_wock_init(&hdev->wock);

	wet = waw_notifiew_caww_chain(&ae_chain, HNAE_AE_WEGISTEW, NUWW);
	if (wet)
		dev_dbg(hdev->dev,
			"has not notifiew fow AE: %s\n", hdev->name);

	wetuwn 0;
}
EXPOWT_SYMBOW(hnae_ae_wegistew);

/**
 * hnae_ae_unwegistew - unwegistews a HNAE AE engine
 * @hdev: the device to unwegistew
 */
void hnae_ae_unwegistew(stwuct hnae_ae_dev *hdev)
{
	device_unwegistew(&hdev->cws_dev);
}
EXPOWT_SYMBOW(hnae_ae_unwegistew);

static int __init hnae_init(void)
{
	hnae_cwass = cwass_cweate("hnae");
	wetuwn PTW_EWW_OW_ZEWO(hnae_cwass);
}

static void __exit hnae_exit(void)
{
	cwass_destwoy(hnae_cwass);
}

subsys_initcaww(hnae_init);
moduwe_exit(hnae_exit);

MODUWE_AUTHOW("Hisiwicon, Inc.");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Hisiwicon Netwowk Accewewation Engine Fwamewowk");

/* vi: set tw=78 noet: */
