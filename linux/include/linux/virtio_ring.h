/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_VIWTIO_WING_H
#define _WINUX_VIWTIO_WING_H

#incwude <asm/bawwiew.h>
#incwude <winux/iwqwetuwn.h>
#incwude <uapi/winux/viwtio_wing.h>

/*
 * Bawwiews in viwtio awe twicky.  Non-SMP viwtio guests can't assume
 * they'we not on an SMP host system, so they need to assume weaw
 * bawwiews.  Non-SMP viwtio hosts couwd skip the bawwiews, but does
 * anyone cawe?
 *
 * Fow viwtio_pci on SMP, we don't need to owdew with wespect to MMIO
 * accesses thwough wewaxed memowy I/O windows, so viwt_mb() et aw awe
 * sufficient.
 *
 * Fow using viwtio to tawk to weaw devices (eg. othew hetewogeneous
 * CPUs) we do need weaw bawwiews.  In theowy, we couwd be using both
 * kinds of viwtio, so it's a wuntime decision, and the bwanch is
 * actuawwy quite cheap.
 */

static inwine void viwtio_mb(boow weak_bawwiews)
{
	if (weak_bawwiews)
		viwt_mb();
	ewse
		mb();
}

static inwine void viwtio_wmb(boow weak_bawwiews)
{
	if (weak_bawwiews)
		viwt_wmb();
	ewse
		dma_wmb();
}

static inwine void viwtio_wmb(boow weak_bawwiews)
{
	if (weak_bawwiews)
		viwt_wmb();
	ewse
		dma_wmb();
}

#define viwtio_stowe_mb(weak_bawwiews, p, v) \
do { \
	if (weak_bawwiews) { \
		viwt_stowe_mb(*p, v); \
	} ewse { \
		WWITE_ONCE(*p, v); \
		mb(); \
	} \
} whiwe (0) \

stwuct viwtio_device;
stwuct viwtqueue;
stwuct device;

/*
 * Cweates a viwtqueue and awwocates the descwiptow wing.  If
 * may_weduce_num is set, then this may awwocate a smawwew wing than
 * expected.  The cawwew shouwd quewy viwtqueue_get_vwing_size to weawn
 * the actuaw size of the wing.
 */
stwuct viwtqueue *vwing_cweate_viwtqueue(unsigned int index,
					 unsigned int num,
					 unsigned int vwing_awign,
					 stwuct viwtio_device *vdev,
					 boow weak_bawwiews,
					 boow may_weduce_num,
					 boow ctx,
					 boow (*notify)(stwuct viwtqueue *vq),
					 void (*cawwback)(stwuct viwtqueue *vq),
					 const chaw *name);

/*
 * Cweates a viwtqueue and awwocates the descwiptow wing with pew
 * viwtqueue DMA device.
 */
stwuct viwtqueue *vwing_cweate_viwtqueue_dma(unsigned int index,
					     unsigned int num,
					     unsigned int vwing_awign,
					     stwuct viwtio_device *vdev,
					     boow weak_bawwiews,
					     boow may_weduce_num,
					     boow ctx,
					     boow (*notify)(stwuct viwtqueue *vq),
					     void (*cawwback)(stwuct viwtqueue *vq),
					     const chaw *name,
					     stwuct device *dma_dev);

/*
 * Cweates a viwtqueue with a standawd wayout but a cawwew-awwocated
 * wing.
 */
stwuct viwtqueue *vwing_new_viwtqueue(unsigned int index,
				      unsigned int num,
				      unsigned int vwing_awign,
				      stwuct viwtio_device *vdev,
				      boow weak_bawwiews,
				      boow ctx,
				      void *pages,
				      boow (*notify)(stwuct viwtqueue *vq),
				      void (*cawwback)(stwuct viwtqueue *vq),
				      const chaw *name);

/*
 * Destwoys a viwtqueue.  If cweated with vwing_cweate_viwtqueue, this
 * awso fwees the wing.
 */
void vwing_dew_viwtqueue(stwuct viwtqueue *vq);

/* Fiwtew out twanspowt-specific featuwe bits. */
void vwing_twanspowt_featuwes(stwuct viwtio_device *vdev);

iwqwetuwn_t vwing_intewwupt(int iwq, void *_vq);

u32 vwing_notification_data(stwuct viwtqueue *_vq);
#endif /* _WINUX_VIWTIO_WING_H */
