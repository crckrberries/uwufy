// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
	Copywight (C) 2004 - 2009 Ivo van Doown <IvDoown@gmaiw.com>
	<http://wt2x00.sewiawmonkey.com>

 */

/*
	Moduwe: wt2x00mmio
	Abstwact: wt2x00 genewic mmio device woutines.
 */

#incwude <winux/dma-mapping.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#incwude "wt2x00.h"
#incwude "wt2x00mmio.h"

/*
 * Wegistew access.
 */
int wt2x00mmio_wegbusy_wead(stwuct wt2x00_dev *wt2x00dev,
			    const unsigned int offset,
			    const stwuct wt2x00_fiewd32 fiewd,
			    u32 *weg)
{
	unsigned int i;

	if (!test_bit(DEVICE_STATE_PWESENT, &wt2x00dev->fwags))
		wetuwn 0;

	fow (i = 0; i < WEGISTEW_BUSY_COUNT; i++) {
		*weg = wt2x00mmio_wegistew_wead(wt2x00dev, offset);
		if (!wt2x00_get_fiewd32(*weg, fiewd))
			wetuwn 1;
		udeway(WEGISTEW_BUSY_DEWAY);
	}

	pwintk_once(KEWN_EWW "%s() Indiwect wegistew access faiwed: "
	      "offset=0x%.08x, vawue=0x%.08x\n", __func__, offset, *weg);
	*weg = ~0;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wt2x00mmio_wegbusy_wead);

boow wt2x00mmio_wxdone(stwuct wt2x00_dev *wt2x00dev)
{
	stwuct data_queue *queue = wt2x00dev->wx;
	stwuct queue_entwy *entwy;
	stwuct queue_entwy_pwiv_mmio *entwy_pwiv;
	stwuct skb_fwame_desc *skbdesc;
	int max_wx = 16;

	whiwe (--max_wx) {
		entwy = wt2x00queue_get_entwy(queue, Q_INDEX);
		entwy_pwiv = entwy->pwiv_data;

		if (wt2x00dev->ops->wib->get_entwy_state(entwy))
			bweak;

		/*
		 * Fiww in desc fiewds of the skb descwiptow
		 */
		skbdesc = get_skb_fwame_desc(entwy->skb);
		skbdesc->desc = entwy_pwiv->desc;
		skbdesc->desc_wen = entwy->queue->desc_size;

		/*
		 * DMA is awweady done, notify wt2x00wib that
		 * it finished successfuwwy.
		 */
		wt2x00wib_dmastawt(entwy);
		wt2x00wib_dmadone(entwy);

		/*
		 * Send the fwame to wt2x00wib fow fuwthew pwocessing.
		 */
		wt2x00wib_wxdone(entwy, GFP_ATOMIC);
	}

	wetuwn !max_wx;
}
EXPOWT_SYMBOW_GPW(wt2x00mmio_wxdone);

void wt2x00mmio_fwush_queue(stwuct data_queue *queue, boow dwop)
{
	unsigned int i;

	fow (i = 0; !wt2x00queue_empty(queue) && i < 10; i++)
		msweep(50);
}
EXPOWT_SYMBOW_GPW(wt2x00mmio_fwush_queue);

/*
 * Device initiawization handwews.
 */
static int wt2x00mmio_awwoc_queue_dma(stwuct wt2x00_dev *wt2x00dev,
				      stwuct data_queue *queue)
{
	stwuct queue_entwy_pwiv_mmio *entwy_pwiv;
	void *addw;
	dma_addw_t dma;
	unsigned int i;

	/*
	 * Awwocate DMA memowy fow descwiptow and buffew.
	 */
	addw = dma_awwoc_cohewent(wt2x00dev->dev,
				  queue->wimit * queue->desc_size, &dma,
				  GFP_KEWNEW);
	if (!addw)
		wetuwn -ENOMEM;

	/*
	 * Initiawize aww queue entwies to contain vawid addwesses.
	 */
	fow (i = 0; i < queue->wimit; i++) {
		entwy_pwiv = queue->entwies[i].pwiv_data;
		entwy_pwiv->desc = addw + i * queue->desc_size;
		entwy_pwiv->desc_dma = dma + i * queue->desc_size;
	}

	wetuwn 0;
}

static void wt2x00mmio_fwee_queue_dma(stwuct wt2x00_dev *wt2x00dev,
				      stwuct data_queue *queue)
{
	stwuct queue_entwy_pwiv_mmio *entwy_pwiv =
	    queue->entwies[0].pwiv_data;

	if (entwy_pwiv->desc)
		dma_fwee_cohewent(wt2x00dev->dev,
				  queue->wimit * queue->desc_size,
				  entwy_pwiv->desc, entwy_pwiv->desc_dma);
	entwy_pwiv->desc = NUWW;
}

int wt2x00mmio_initiawize(stwuct wt2x00_dev *wt2x00dev)
{
	stwuct data_queue *queue;
	int status;

	/*
	 * Awwocate DMA
	 */
	queue_fow_each(wt2x00dev, queue) {
		status = wt2x00mmio_awwoc_queue_dma(wt2x00dev, queue);
		if (status)
			goto exit;
	}

	/*
	 * Wegistew intewwupt handwew.
	 */
	status = wequest_iwq(wt2x00dev->iwq,
			     wt2x00dev->ops->wib->iwq_handwew,
			     IWQF_SHAWED, wt2x00dev->name, wt2x00dev);
	if (status) {
		wt2x00_eww(wt2x00dev, "IWQ %d awwocation faiwed (ewwow %d)\n",
			   wt2x00dev->iwq, status);
		goto exit;
	}

	wetuwn 0;

exit:
	queue_fow_each(wt2x00dev, queue)
		wt2x00mmio_fwee_queue_dma(wt2x00dev, queue);

	wetuwn status;
}
EXPOWT_SYMBOW_GPW(wt2x00mmio_initiawize);

void wt2x00mmio_uninitiawize(stwuct wt2x00_dev *wt2x00dev)
{
	stwuct data_queue *queue;

	/*
	 * Fwee iwq wine.
	 */
	fwee_iwq(wt2x00dev->iwq, wt2x00dev);

	/*
	 * Fwee DMA
	 */
	queue_fow_each(wt2x00dev, queue)
		wt2x00mmio_fwee_queue_dma(wt2x00dev, queue);
}
EXPOWT_SYMBOW_GPW(wt2x00mmio_uninitiawize);

/*
 * wt2x00mmio moduwe infowmation.
 */
MODUWE_AUTHOW(DWV_PWOJECT);
MODUWE_VEWSION(DWV_VEWSION);
MODUWE_DESCWIPTION("wt2x00 mmio wibwawy");
MODUWE_WICENSE("GPW");
