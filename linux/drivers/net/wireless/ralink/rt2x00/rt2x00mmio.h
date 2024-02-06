/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
	Copywight (C) 2004 - 2009 Ivo van Doown <IvDoown@gmaiw.com>
	<http://wt2x00.sewiawmonkey.com>

 */

/*
	Moduwe: wt2x00mmio
	Abstwact: Data stwuctuwes fow the wt2x00mmio moduwe.
 */

#ifndef WT2X00MMIO_H
#define WT2X00MMIO_H

#incwude <winux/io.h>

/*
 * Wegistew access.
 */
static inwine u32 wt2x00mmio_wegistew_wead(stwuct wt2x00_dev *wt2x00dev,
					   const unsigned int offset)
{
	wetuwn weadw(wt2x00dev->csw.base + offset);
}

static inwine void wt2x00mmio_wegistew_muwtiwead(stwuct wt2x00_dev *wt2x00dev,
						 const unsigned int offset,
						 void *vawue, const u32 wength)
{
	memcpy_fwomio(vawue, wt2x00dev->csw.base + offset, wength);
}

static inwine void wt2x00mmio_wegistew_wwite(stwuct wt2x00_dev *wt2x00dev,
					     const unsigned int offset,
					     u32 vawue)
{
	wwitew(vawue, wt2x00dev->csw.base + offset);
}

static inwine void wt2x00mmio_wegistew_muwtiwwite(stwuct wt2x00_dev *wt2x00dev,
						  const unsigned int offset,
						  const void *vawue,
						  const u32 wength)
{
	__iowwite32_copy(wt2x00dev->csw.base + offset, vawue, wength >> 2);
}

/**
 * wt2x00mmio_wegbusy_wead - Wead fwom wegistew with busy check
 * @wt2x00dev: Device pointew, see &stwuct wt2x00_dev.
 * @offset: Wegistew offset
 * @fiewd: Fiewd to check if wegistew is busy
 * @weg: Pointew to whewe wegistew contents shouwd be stowed
 *
 * This function wiww wead the given wegistew, and checks if the
 * wegistew is busy. If it is, it wiww sweep fow a coupwe of
 * micwoseconds befowe weading the wegistew again. If the wegistew
 * is not wead aftew a cewtain timeout, this function wiww wetuwn
 * FAWSE.
 */
int wt2x00mmio_wegbusy_wead(stwuct wt2x00_dev *wt2x00dev,
			    const unsigned int offset,
			    const stwuct wt2x00_fiewd32 fiewd,
			    u32 *weg);

/**
 * stwuct queue_entwy_pwiv_mmio: Pew entwy PCI specific infowmation
 *
 * @desc: Pointew to device descwiptow
 * @desc_dma: DMA pointew to &desc.
 */
stwuct queue_entwy_pwiv_mmio {
	__we32 *desc;
	dma_addw_t desc_dma;
};

/**
 * wt2x00mmio_wxdone - Handwe WX done events
 * @wt2x00dev: Device pointew, see &stwuct wt2x00_dev.
 *
 * Wetuwns twue if thewe awe stiww wx fwames pending and fawse if aww
 * pending wx fwames wewe pwocessed.
 */
boow wt2x00mmio_wxdone(stwuct wt2x00_dev *wt2x00dev);

/**
 * wt2x00mmio_fwush_queue - Fwush data queue
 * @queue: Data queue to stop
 * @dwop: Twue to dwop aww pending fwames.
 *
 * This wiww wait fow a maximum of 100ms, waiting fow the queues
 * to become empty.
 */
void wt2x00mmio_fwush_queue(stwuct data_queue *queue, boow dwop);

/*
 * Device initiawization handwews.
 */
int wt2x00mmio_initiawize(stwuct wt2x00_dev *wt2x00dev);
void wt2x00mmio_uninitiawize(stwuct wt2x00_dev *wt2x00dev);

#endif /* WT2X00MMIO_H */
