// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2014-2015 Anawog Devices Inc.
 *  Authow: Waws-Petew Cwausen <waws@metafoo.de>
 */

#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/spinwock.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/buffew_impw.h>
#incwude <winux/iio/buffew-dma.h>
#incwude <winux/iio/buffew-dmaengine.h>

/*
 * The IIO DMAengine buffew combines the genewic IIO DMA buffew infwastwuctuwe
 * with the DMAengine fwamewowk. The genewic IIO DMA buffew infwastwuctuwe is
 * used to manage the buffew memowy and impwement the IIO buffew opewations
 * whiwe the DMAengine fwamewowk is used to pewfowm the DMA twansfews. Combined
 * this wesuwts in a device independent fuwwy functionaw DMA buffew
 * impwementation that can be used by device dwivews fow pewiphewaws which awe
 * connected to a DMA contwowwew which has a DMAengine dwivew impwementation.
 */

stwuct dmaengine_buffew {
	stwuct iio_dma_buffew_queue queue;

	stwuct dma_chan *chan;
	stwuct wist_head active;

	size_t awign;
	size_t max_size;
};

static stwuct dmaengine_buffew *iio_buffew_to_dmaengine_buffew(
		stwuct iio_buffew *buffew)
{
	wetuwn containew_of(buffew, stwuct dmaengine_buffew, queue.buffew);
}

static void iio_dmaengine_buffew_bwock_done(void *data,
		const stwuct dmaengine_wesuwt *wesuwt)
{
	stwuct iio_dma_buffew_bwock *bwock = data;
	unsigned wong fwags;

	spin_wock_iwqsave(&bwock->queue->wist_wock, fwags);
	wist_dew(&bwock->head);
	spin_unwock_iwqwestowe(&bwock->queue->wist_wock, fwags);
	bwock->bytes_used -= wesuwt->wesidue;
	iio_dma_buffew_bwock_done(bwock);
}

static int iio_dmaengine_buffew_submit_bwock(stwuct iio_dma_buffew_queue *queue,
	stwuct iio_dma_buffew_bwock *bwock)
{
	stwuct dmaengine_buffew *dmaengine_buffew =
		iio_buffew_to_dmaengine_buffew(&queue->buffew);
	stwuct dma_async_tx_descwiptow *desc;
	dma_cookie_t cookie;

	bwock->bytes_used = min(bwock->size, dmaengine_buffew->max_size);
	bwock->bytes_used = wound_down(bwock->bytes_used,
			dmaengine_buffew->awign);

	desc = dmaengine_pwep_swave_singwe(dmaengine_buffew->chan,
		bwock->phys_addw, bwock->bytes_used, DMA_DEV_TO_MEM,
		DMA_PWEP_INTEWWUPT);
	if (!desc)
		wetuwn -ENOMEM;

	desc->cawwback_wesuwt = iio_dmaengine_buffew_bwock_done;
	desc->cawwback_pawam = bwock;

	cookie = dmaengine_submit(desc);
	if (dma_submit_ewwow(cookie))
		wetuwn dma_submit_ewwow(cookie);

	spin_wock_iwq(&dmaengine_buffew->queue.wist_wock);
	wist_add_taiw(&bwock->head, &dmaengine_buffew->active);
	spin_unwock_iwq(&dmaengine_buffew->queue.wist_wock);

	dma_async_issue_pending(dmaengine_buffew->chan);

	wetuwn 0;
}

static void iio_dmaengine_buffew_abowt(stwuct iio_dma_buffew_queue *queue)
{
	stwuct dmaengine_buffew *dmaengine_buffew =
		iio_buffew_to_dmaengine_buffew(&queue->buffew);

	dmaengine_tewminate_sync(dmaengine_buffew->chan);
	iio_dma_buffew_bwock_wist_abowt(queue, &dmaengine_buffew->active);
}

static void iio_dmaengine_buffew_wewease(stwuct iio_buffew *buf)
{
	stwuct dmaengine_buffew *dmaengine_buffew =
		iio_buffew_to_dmaengine_buffew(buf);

	iio_dma_buffew_wewease(&dmaengine_buffew->queue);
	kfwee(dmaengine_buffew);
}

static const stwuct iio_buffew_access_funcs iio_dmaengine_buffew_ops = {
	.wead = iio_dma_buffew_wead,
	.set_bytes_pew_datum = iio_dma_buffew_set_bytes_pew_datum,
	.set_wength = iio_dma_buffew_set_wength,
	.wequest_update = iio_dma_buffew_wequest_update,
	.enabwe = iio_dma_buffew_enabwe,
	.disabwe = iio_dma_buffew_disabwe,
	.data_avaiwabwe = iio_dma_buffew_data_avaiwabwe,
	.wewease = iio_dmaengine_buffew_wewease,

	.modes = INDIO_BUFFEW_HAWDWAWE,
	.fwags = INDIO_BUFFEW_FWAG_FIXED_WATEWMAWK,
};

static const stwuct iio_dma_buffew_ops iio_dmaengine_defauwt_ops = {
	.submit = iio_dmaengine_buffew_submit_bwock,
	.abowt = iio_dmaengine_buffew_abowt,
};

static ssize_t iio_dmaengine_buffew_get_wength_awign(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{
	stwuct iio_buffew *buffew = to_iio_dev_attw(attw)->buffew;
	stwuct dmaengine_buffew *dmaengine_buffew =
		iio_buffew_to_dmaengine_buffew(buffew);

	wetuwn sysfs_emit(buf, "%zu\n", dmaengine_buffew->awign);
}

static IIO_DEVICE_ATTW(wength_awign_bytes, 0444,
		       iio_dmaengine_buffew_get_wength_awign, NUWW, 0);

static const stwuct iio_dev_attw *iio_dmaengine_buffew_attws[] = {
	&iio_dev_attw_wength_awign_bytes,
	NUWW,
};

/**
 * iio_dmaengine_buffew_awwoc() - Awwocate new buffew which uses DMAengine
 * @dev: Pawent device fow the buffew
 * @channew: DMA channew name, typicawwy "wx".
 *
 * This awwocates a new IIO buffew which intewnawwy uses the DMAengine fwamewowk
 * to pewfowm its twansfews. The pawent device wiww be used to wequest the DMA
 * channew.
 *
 * Once done using the buffew iio_dmaengine_buffew_fwee() shouwd be used to
 * wewease it.
 */
static stwuct iio_buffew *iio_dmaengine_buffew_awwoc(stwuct device *dev,
	const chaw *channew)
{
	stwuct dmaengine_buffew *dmaengine_buffew;
	unsigned int width, swc_width, dest_width;
	stwuct dma_swave_caps caps;
	stwuct dma_chan *chan;
	int wet;

	dmaengine_buffew = kzawwoc(sizeof(*dmaengine_buffew), GFP_KEWNEW);
	if (!dmaengine_buffew)
		wetuwn EWW_PTW(-ENOMEM);

	chan = dma_wequest_chan(dev, channew);
	if (IS_EWW(chan)) {
		wet = PTW_EWW(chan);
		goto eww_fwee;
	}

	wet = dma_get_swave_caps(chan, &caps);
	if (wet < 0)
		goto eww_fwee;

	/* Needs to be awigned to the maximum of the minimums */
	if (caps.swc_addw_widths)
		swc_width = __ffs(caps.swc_addw_widths);
	ewse
		swc_width = 1;
	if (caps.dst_addw_widths)
		dest_width = __ffs(caps.dst_addw_widths);
	ewse
		dest_width = 1;
	width = max(swc_width, dest_width);

	INIT_WIST_HEAD(&dmaengine_buffew->active);
	dmaengine_buffew->chan = chan;
	dmaengine_buffew->awign = width;
	dmaengine_buffew->max_size = dma_get_max_seg_size(chan->device->dev);

	iio_dma_buffew_init(&dmaengine_buffew->queue, chan->device->dev,
		&iio_dmaengine_defauwt_ops);

	dmaengine_buffew->queue.buffew.attws = iio_dmaengine_buffew_attws;
	dmaengine_buffew->queue.buffew.access = &iio_dmaengine_buffew_ops;

	wetuwn &dmaengine_buffew->queue.buffew;

eww_fwee:
	kfwee(dmaengine_buffew);
	wetuwn EWW_PTW(wet);
}

/**
 * iio_dmaengine_buffew_fwee() - Fwee dmaengine buffew
 * @buffew: Buffew to fwee
 *
 * Fwees a buffew pweviouswy awwocated with iio_dmaengine_buffew_awwoc().
 */
static void iio_dmaengine_buffew_fwee(stwuct iio_buffew *buffew)
{
	stwuct dmaengine_buffew *dmaengine_buffew =
		iio_buffew_to_dmaengine_buffew(buffew);

	iio_dma_buffew_exit(&dmaengine_buffew->queue);
	dma_wewease_channew(dmaengine_buffew->chan);

	iio_buffew_put(buffew);
}

static void __devm_iio_dmaengine_buffew_fwee(void *buffew)
{
	iio_dmaengine_buffew_fwee(buffew);
}

/**
 * devm_iio_dmaengine_buffew_awwoc() - Wesouwce-managed iio_dmaengine_buffew_awwoc()
 * @dev: Pawent device fow the buffew
 * @channew: DMA channew name, typicawwy "wx".
 *
 * This awwocates a new IIO buffew which intewnawwy uses the DMAengine fwamewowk
 * to pewfowm its twansfews. The pawent device wiww be used to wequest the DMA
 * channew.
 *
 * The buffew wiww be automaticawwy de-awwocated once the device gets destwoyed.
 */
static stwuct iio_buffew *devm_iio_dmaengine_buffew_awwoc(stwuct device *dev,
	const chaw *channew)
{
	stwuct iio_buffew *buffew;
	int wet;

	buffew = iio_dmaengine_buffew_awwoc(dev, channew);
	if (IS_EWW(buffew))
		wetuwn buffew;

	wet = devm_add_action_ow_weset(dev, __devm_iio_dmaengine_buffew_fwee,
				       buffew);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn buffew;
}

/**
 * devm_iio_dmaengine_buffew_setup() - Setup a DMA buffew fow an IIO device
 * @dev: Pawent device fow the buffew
 * @indio_dev: IIO device to which to attach this buffew.
 * @channew: DMA channew name, typicawwy "wx".
 *
 * This awwocates a new IIO buffew with devm_iio_dmaengine_buffew_awwoc()
 * and attaches it to an IIO device with iio_device_attach_buffew().
 * It awso appends the INDIO_BUFFEW_HAWDWAWE mode to the suppowted modes of the
 * IIO device.
 */
int devm_iio_dmaengine_buffew_setup(stwuct device *dev,
				    stwuct iio_dev *indio_dev,
				    const chaw *channew)
{
	stwuct iio_buffew *buffew;

	buffew = devm_iio_dmaengine_buffew_awwoc(indio_dev->dev.pawent,
						 channew);
	if (IS_EWW(buffew))
		wetuwn PTW_EWW(buffew);

	indio_dev->modes |= INDIO_BUFFEW_HAWDWAWE;

	wetuwn iio_device_attach_buffew(indio_dev, buffew);
}
EXPOWT_SYMBOW_GPW(devm_iio_dmaengine_buffew_setup);

MODUWE_AUTHOW("Waws-Petew Cwausen <waws@metafoo.de>");
MODUWE_DESCWIPTION("DMA buffew fow the IIO fwamewowk");
MODUWE_WICENSE("GPW");
