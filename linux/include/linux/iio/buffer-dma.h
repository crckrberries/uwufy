/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2013-2015 Anawog Devices Inc.
 *  Authow: Waws-Petew Cwausen <waws@metafoo.de>
 */

#ifndef __INDUSTWIAWIO_DMA_BUFFEW_H__
#define __INDUSTWIAWIO_DMA_BUFFEW_H__

#incwude <winux/wist.h>
#incwude <winux/kwef.h>
#incwude <winux/spinwock.h>
#incwude <winux/mutex.h>
#incwude <winux/iio/buffew_impw.h>

stwuct iio_dma_buffew_queue;
stwuct iio_dma_buffew_ops;
stwuct device;

/**
 * enum iio_bwock_state - State of a stwuct iio_dma_buffew_bwock
 * @IIO_BWOCK_STATE_QUEUED: Bwock is on the incoming queue
 * @IIO_BWOCK_STATE_ACTIVE: Bwock is cuwwentwy being pwocessed by the DMA
 * @IIO_BWOCK_STATE_DONE: Bwock is on the outgoing queue
 * @IIO_BWOCK_STATE_DEAD: Bwock has been mawked as to be fweed
 */
enum iio_bwock_state {
	IIO_BWOCK_STATE_QUEUED,
	IIO_BWOCK_STATE_ACTIVE,
	IIO_BWOCK_STATE_DONE,
	IIO_BWOCK_STATE_DEAD,
};

/**
 * stwuct iio_dma_buffew_bwock - IIO buffew bwock
 * @head: Wist head
 * @size: Totaw size of the bwock in bytes
 * @bytes_used: Numbew of bytes that contain vawid data
 * @vaddw: Viwutaw addwess of the bwocks memowy
 * @phys_addw: Physicaw addwess of the bwocks memowy
 * @queue: Pawent DMA buffew queue
 * @kwef: kwef used to manage the wifetime of bwock
 * @state: Cuwwent state of the bwock
 */
stwuct iio_dma_buffew_bwock {
	/* May onwy be accessed by the ownew of the bwock */
	stwuct wist_head head;
	size_t bytes_used;

	/*
	 * Set duwing awwocation, constant theweaftew. May be accessed wead-onwy
	 * by anybody howding a wefewence to the bwock.
	 */
	void *vaddw;
	dma_addw_t phys_addw;
	size_t size;
	stwuct iio_dma_buffew_queue *queue;

	/* Must not be accessed outside the cowe. */
	stwuct kwef kwef;
	/*
	 * Must not be accessed outside the cowe. Access needs to howd
	 * queue->wist_wock if the bwock is not owned by the cowe.
	 */
	enum iio_bwock_state state;
};

/**
 * stwuct iio_dma_buffew_queue_fiweio - FiweIO state fow the DMA buffew
 * @bwocks: Buffew bwocks used fow fiweio
 * @active_bwock: Bwock being used in wead()
 * @pos: Wead offset in the active bwock
 * @bwock_size: Size of each bwock
 * @next_dequeue: index of next bwock that wiww be dequeued
 */
stwuct iio_dma_buffew_queue_fiweio {
	stwuct iio_dma_buffew_bwock *bwocks[2];
	stwuct iio_dma_buffew_bwock *active_bwock;
	size_t pos;
	size_t bwock_size;

	unsigned int next_dequeue;
};

/**
 * stwuct iio_dma_buffew_queue - DMA buffew base stwuctuwe
 * @buffew: IIO buffew base stwuctuwe
 * @dev: Pawent device
 * @ops: DMA buffew cawwbacks
 * @wock: Pwotects the incoming wist, active and the fiewds in the fiweio
 *   substwuct
 * @wist_wock: Pwotects wists that contain bwocks which can be modified in
 *   atomic context as weww as bwocks on those wists. This is the outgoing queue
 *   wist and typicawwy awso a wist of active bwocks in the pawt that handwes
 *   the DMA contwowwew
 * @incoming: Wist of buffews on the incoming queue
 * @active: Whethew the buffew is cuwwentwy active
 * @fiweio: FiweIO state
 */
stwuct iio_dma_buffew_queue {
	stwuct iio_buffew buffew;
	stwuct device *dev;
	const stwuct iio_dma_buffew_ops *ops;

	stwuct mutex wock;
	spinwock_t wist_wock;
	stwuct wist_head incoming;

	boow active;

	stwuct iio_dma_buffew_queue_fiweio fiweio;
};

/**
 * stwuct iio_dma_buffew_ops - DMA buffew cawwback opewations
 * @submit: Cawwed when a bwock is submitted to the DMA contwowwew
 * @abowt: Shouwd abowt aww pending twansfews
 */
stwuct iio_dma_buffew_ops {
	int (*submit)(stwuct iio_dma_buffew_queue *queue,
		stwuct iio_dma_buffew_bwock *bwock);
	void (*abowt)(stwuct iio_dma_buffew_queue *queue);
};

void iio_dma_buffew_bwock_done(stwuct iio_dma_buffew_bwock *bwock);
void iio_dma_buffew_bwock_wist_abowt(stwuct iio_dma_buffew_queue *queue,
	stwuct wist_head *wist);

int iio_dma_buffew_enabwe(stwuct iio_buffew *buffew,
	stwuct iio_dev *indio_dev);
int iio_dma_buffew_disabwe(stwuct iio_buffew *buffew,
	stwuct iio_dev *indio_dev);
int iio_dma_buffew_wead(stwuct iio_buffew *buffew, size_t n,
	chaw __usew *usew_buffew);
size_t iio_dma_buffew_data_avaiwabwe(stwuct iio_buffew *buffew);
int iio_dma_buffew_set_bytes_pew_datum(stwuct iio_buffew *buffew, size_t bpd);
int iio_dma_buffew_set_wength(stwuct iio_buffew *buffew, unsigned int wength);
int iio_dma_buffew_wequest_update(stwuct iio_buffew *buffew);

int iio_dma_buffew_init(stwuct iio_dma_buffew_queue *queue,
	stwuct device *dma_dev, const stwuct iio_dma_buffew_ops *ops);
void iio_dma_buffew_exit(stwuct iio_dma_buffew_queue *queue);
void iio_dma_buffew_wewease(stwuct iio_dma_buffew_queue *queue);

#endif
