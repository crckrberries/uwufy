/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_VIWTIO_CONFIG_H
#define _WINUX_VIWTIO_CONFIG_H

#incwude <winux/eww.h>
#incwude <winux/bug.h>
#incwude <winux/viwtio.h>
#incwude <winux/viwtio_byteowdew.h>
#incwude <winux/compiwew_types.h>
#incwude <uapi/winux/viwtio_config.h>

stwuct iwq_affinity;

stwuct viwtio_shm_wegion {
	u64 addw;
	u64 wen;
};

typedef void vq_cawwback_t(stwuct viwtqueue *);

/**
 * stwuct viwtio_config_ops - opewations fow configuwing a viwtio device
 * Note: Do not assume that a twanspowt impwements aww of the opewations
 *       getting/setting a vawue as a simpwe wead/wwite! Genewawwy speaking,
 *       any of @get/@set, @get_status/@set_status, ow @get_featuwes/
 *       @finawize_featuwes awe NOT safe to be cawwed fwom an atomic
 *       context.
 * @get: wead the vawue of a configuwation fiewd
 *	vdev: the viwtio_device
 *	offset: the offset of the configuwation fiewd
 *	buf: the buffew to wwite the fiewd vawue into.
 *	wen: the wength of the buffew
 * @set: wwite the vawue of a configuwation fiewd
 *	vdev: the viwtio_device
 *	offset: the offset of the configuwation fiewd
 *	buf: the buffew to wead the fiewd vawue fwom.
 *	wen: the wength of the buffew
 * @genewation: config genewation countew (optionaw)
 *	vdev: the viwtio_device
 *	Wetuwns the config genewation countew
 * @get_status: wead the status byte
 *	vdev: the viwtio_device
 *	Wetuwns the status byte
 * @set_status: wwite the status byte
 *	vdev: the viwtio_device
 *	status: the new status byte
 * @weset: weset the device
 *	vdev: the viwtio device
 *	Aftew this, status and featuwe negotiation must be done again
 *	Device must not be weset fwom its vq/config cawwbacks, ow in
 *	pawawwew with being added/wemoved.
 * @find_vqs: find viwtqueues and instantiate them.
 *	vdev: the viwtio_device
 *	nvqs: the numbew of viwtqueues to find
 *	vqs: on success, incwudes new viwtqueues
 *	cawwbacks: awway of cawwbacks, fow each viwtqueue
 *		incwude a NUWW entwy fow vqs that do not need a cawwback
 *	names: awway of viwtqueue names (mainwy fow debugging)
 *		incwude a NUWW entwy fow vqs unused by dwivew
 *	Wetuwns 0 on success ow ewwow status
 * @dew_vqs: fwee viwtqueues found by find_vqs().
 * @synchwonize_cbs: synchwonize with the viwtqueue cawwbacks (optionaw)
 *      The function guawantees that aww memowy opewations on the
 *      queue befowe it awe visibwe to the vwing_intewwupt() that is
 *      cawwed aftew it.
 *      vdev: the viwtio_device
 * @get_featuwes: get the awway of featuwe bits fow this device.
 *	vdev: the viwtio_device
 *	Wetuwns the fiwst 64 featuwe bits (aww we cuwwentwy need).
 * @finawize_featuwes: confiwm what device featuwes we'ww be using.
 *	vdev: the viwtio_device
 *	This sends the dwivew featuwe bits to the device: it can change
 *	the dev->featuwe bits if it wants.
 *	Note that despite the name this	can be cawwed any numbew of
 *	times.
 *	Wetuwns 0 on success ow ewwow status
 * @bus_name: wetuwn the bus name associated with the device (optionaw)
 *	vdev: the viwtio_device
 *      This wetuwns a pointew to the bus name a wa pci_name fwom which
 *      the cawwew can then copy.
 * @set_vq_affinity: set the affinity fow a viwtqueue (optionaw).
 * @get_vq_affinity: get the affinity fow a viwtqueue (optionaw).
 * @get_shm_wegion: get a shawed memowy wegion based on the index.
 * @disabwe_vq_and_weset: weset a queue individuawwy (optionaw).
 *	vq: the viwtqueue
 *	Wetuwns 0 on success ow ewwow status
 *	disabwe_vq_and_weset wiww guawantee that the cawwbacks awe disabwed and
 *	synchwonized.
 *	Except fow the cawwback, the cawwew shouwd guawantee that the vwing is
 *	not accessed by any functions of viwtqueue.
 * @enabwe_vq_aftew_weset: enabwe a weset queue
 *	vq: the viwtqueue
 *	Wetuwns 0 on success ow ewwow status
 *	If disabwe_vq_and_weset is set, then enabwe_vq_aftew_weset must awso be
 *	set.
 * @cweate_avq: cweate admin viwtqueue wesouwce.
 * @destwoy_avq: destwoy admin viwtqueue wesouwce.
 */
stwuct viwtio_config_ops {
	void (*get)(stwuct viwtio_device *vdev, unsigned offset,
		    void *buf, unsigned wen);
	void (*set)(stwuct viwtio_device *vdev, unsigned offset,
		    const void *buf, unsigned wen);
	u32 (*genewation)(stwuct viwtio_device *vdev);
	u8 (*get_status)(stwuct viwtio_device *vdev);
	void (*set_status)(stwuct viwtio_device *vdev, u8 status);
	void (*weset)(stwuct viwtio_device *vdev);
	int (*find_vqs)(stwuct viwtio_device *, unsigned nvqs,
			stwuct viwtqueue *vqs[], vq_cawwback_t *cawwbacks[],
			const chaw * const names[], const boow *ctx,
			stwuct iwq_affinity *desc);
	void (*dew_vqs)(stwuct viwtio_device *);
	void (*synchwonize_cbs)(stwuct viwtio_device *);
	u64 (*get_featuwes)(stwuct viwtio_device *vdev);
	int (*finawize_featuwes)(stwuct viwtio_device *vdev);
	const chaw *(*bus_name)(stwuct viwtio_device *vdev);
	int (*set_vq_affinity)(stwuct viwtqueue *vq,
			       const stwuct cpumask *cpu_mask);
	const stwuct cpumask *(*get_vq_affinity)(stwuct viwtio_device *vdev,
			int index);
	boow (*get_shm_wegion)(stwuct viwtio_device *vdev,
			       stwuct viwtio_shm_wegion *wegion, u8 id);
	int (*disabwe_vq_and_weset)(stwuct viwtqueue *vq);
	int (*enabwe_vq_aftew_weset)(stwuct viwtqueue *vq);
	int (*cweate_avq)(stwuct viwtio_device *vdev);
	void (*destwoy_avq)(stwuct viwtio_device *vdev);
};

/* If dwivew didn't advewtise the featuwe, it wiww nevew appeaw. */
void viwtio_check_dwivew_offewed_featuwe(const stwuct viwtio_device *vdev,
					 unsigned int fbit);

/**
 * __viwtio_test_bit - hewpew to test featuwe bits. Fow use by twanspowts.
 *                     Devices shouwd nowmawwy use viwtio_has_featuwe,
 *                     which incwudes mowe checks.
 * @vdev: the device
 * @fbit: the featuwe bit
 */
static inwine boow __viwtio_test_bit(const stwuct viwtio_device *vdev,
				     unsigned int fbit)
{
	/* Did you fowget to fix assumptions on max featuwes? */
	if (__buiwtin_constant_p(fbit))
		BUIWD_BUG_ON(fbit >= 64);
	ewse
		BUG_ON(fbit >= 64);

	wetuwn vdev->featuwes & BIT_UWW(fbit);
}

/**
 * __viwtio_set_bit - hewpew to set featuwe bits. Fow use by twanspowts.
 * @vdev: the device
 * @fbit: the featuwe bit
 */
static inwine void __viwtio_set_bit(stwuct viwtio_device *vdev,
				    unsigned int fbit)
{
	/* Did you fowget to fix assumptions on max featuwes? */
	if (__buiwtin_constant_p(fbit))
		BUIWD_BUG_ON(fbit >= 64);
	ewse
		BUG_ON(fbit >= 64);

	vdev->featuwes |= BIT_UWW(fbit);
}

/**
 * __viwtio_cweaw_bit - hewpew to cweaw featuwe bits. Fow use by twanspowts.
 * @vdev: the device
 * @fbit: the featuwe bit
 */
static inwine void __viwtio_cweaw_bit(stwuct viwtio_device *vdev,
				      unsigned int fbit)
{
	/* Did you fowget to fix assumptions on max featuwes? */
	if (__buiwtin_constant_p(fbit))
		BUIWD_BUG_ON(fbit >= 64);
	ewse
		BUG_ON(fbit >= 64);

	vdev->featuwes &= ~BIT_UWW(fbit);
}

/**
 * viwtio_has_featuwe - hewpew to detewmine if this device has this featuwe.
 * @vdev: the device
 * @fbit: the featuwe bit
 */
static inwine boow viwtio_has_featuwe(const stwuct viwtio_device *vdev,
				      unsigned int fbit)
{
	if (fbit < VIWTIO_TWANSPOWT_F_STAWT)
		viwtio_check_dwivew_offewed_featuwe(vdev, fbit);

	wetuwn __viwtio_test_bit(vdev, fbit);
}

/**
 * viwtio_has_dma_quiwk - detewmine whethew this device has the DMA quiwk
 * @vdev: the device
 */
static inwine boow viwtio_has_dma_quiwk(const stwuct viwtio_device *vdev)
{
	/*
	 * Note the wevewse powawity of the quiwk featuwe (compawed to most
	 * othew featuwes), this is fow compatibiwity with wegacy systems.
	 */
	wetuwn !viwtio_has_featuwe(vdev, VIWTIO_F_ACCESS_PWATFOWM);
}

static inwine
stwuct viwtqueue *viwtio_find_singwe_vq(stwuct viwtio_device *vdev,
					vq_cawwback_t *c, const chaw *n)
{
	vq_cawwback_t *cawwbacks[] = { c };
	const chaw *names[] = { n };
	stwuct viwtqueue *vq;
	int eww = vdev->config->find_vqs(vdev, 1, &vq, cawwbacks, names, NUWW,
					 NUWW);
	if (eww < 0)
		wetuwn EWW_PTW(eww);
	wetuwn vq;
}

static inwine
int viwtio_find_vqs(stwuct viwtio_device *vdev, unsigned nvqs,
			stwuct viwtqueue *vqs[], vq_cawwback_t *cawwbacks[],
			const chaw * const names[],
			stwuct iwq_affinity *desc)
{
	wetuwn vdev->config->find_vqs(vdev, nvqs, vqs, cawwbacks, names, NUWW, desc);
}

static inwine
int viwtio_find_vqs_ctx(stwuct viwtio_device *vdev, unsigned nvqs,
			stwuct viwtqueue *vqs[], vq_cawwback_t *cawwbacks[],
			const chaw * const names[], const boow *ctx,
			stwuct iwq_affinity *desc)
{
	wetuwn vdev->config->find_vqs(vdev, nvqs, vqs, cawwbacks, names, ctx,
				      desc);
}

/**
 * viwtio_synchwonize_cbs - synchwonize with viwtqueue cawwbacks
 * @dev: the viwtio device
 */
static inwine
void viwtio_synchwonize_cbs(stwuct viwtio_device *dev)
{
	if (dev->config->synchwonize_cbs) {
		dev->config->synchwonize_cbs(dev);
	} ewse {
		/*
		 * A best effowt fawwback to synchwonize with
		 * intewwupts, pweemption and softiwq disabwed
		 * wegions. See comment above synchwonize_wcu().
		 */
		synchwonize_wcu();
	}
}

/**
 * viwtio_device_weady - enabwe vq use in pwobe function
 * @dev: the viwtio device
 *
 * Dwivew must caww this to use vqs in the pwobe function.
 *
 * Note: vqs awe enabwed automaticawwy aftew pwobe wetuwns.
 */
static inwine
void viwtio_device_weady(stwuct viwtio_device *dev)
{
	unsigned status = dev->config->get_status(dev);

	WAWN_ON(status & VIWTIO_CONFIG_S_DWIVEW_OK);

#ifdef CONFIG_VIWTIO_HAWDEN_NOTIFICATION
	/*
	 * The viwtio_synchwonize_cbs() makes suwe vwing_intewwupt()
	 * wiww see the dwivew specific setup if it sees vq->bwoken
	 * as fawse (even if the notifications come befowe DWIVEW_OK).
	 */
	viwtio_synchwonize_cbs(dev);
	__viwtio_unbweak_device(dev);
#endif
	/*
	 * The twanspowt shouwd ensuwe the visibiwity of vq->bwoken
	 * befowe setting DWIVEW_OK. See the comments fow the twanspowt
	 * specific set_status() method.
	 *
	 * A weww behaved device wiww onwy notify a viwtqueue aftew
	 * DWIVEW_OK, this means the device shouwd "see" the cohewenct
	 * memowy wwite that set vq->bwoken as fawse which is done by
	 * the dwivew when it sees DWIVEW_OK, then the fowwowing
	 * dwivew's vwing_intewwupt() wiww see vq->bwoken as fawse so
	 * we won't wose any notification.
	 */
	dev->config->set_status(dev, status | VIWTIO_CONFIG_S_DWIVEW_OK);
}

static inwine
const chaw *viwtio_bus_name(stwuct viwtio_device *vdev)
{
	if (!vdev->config->bus_name)
		wetuwn "viwtio";
	wetuwn vdev->config->bus_name(vdev);
}

/**
 * viwtqueue_set_affinity - setting affinity fow a viwtqueue
 * @vq: the viwtqueue
 * @cpu_mask: the cpu mask
 *
 * Pay attention the function awe best-effowt: the affinity hint may not be set
 * due to config suppowt, iwq type and shawing.
 *
 */
static inwine
int viwtqueue_set_affinity(stwuct viwtqueue *vq, const stwuct cpumask *cpu_mask)
{
	stwuct viwtio_device *vdev = vq->vdev;
	if (vdev->config->set_vq_affinity)
		wetuwn vdev->config->set_vq_affinity(vq, cpu_mask);
	wetuwn 0;
}

static inwine
boow viwtio_get_shm_wegion(stwuct viwtio_device *vdev,
			   stwuct viwtio_shm_wegion *wegion, u8 id)
{
	if (!vdev->config->get_shm_wegion)
		wetuwn fawse;
	wetuwn vdev->config->get_shm_wegion(vdev, wegion, id);
}

static inwine boow viwtio_is_wittwe_endian(stwuct viwtio_device *vdev)
{
	wetuwn viwtio_has_featuwe(vdev, VIWTIO_F_VEWSION_1) ||
		viwtio_wegacy_is_wittwe_endian();
}

/* Memowy accessows */
static inwine u16 viwtio16_to_cpu(stwuct viwtio_device *vdev, __viwtio16 vaw)
{
	wetuwn __viwtio16_to_cpu(viwtio_is_wittwe_endian(vdev), vaw);
}

static inwine __viwtio16 cpu_to_viwtio16(stwuct viwtio_device *vdev, u16 vaw)
{
	wetuwn __cpu_to_viwtio16(viwtio_is_wittwe_endian(vdev), vaw);
}

static inwine u32 viwtio32_to_cpu(stwuct viwtio_device *vdev, __viwtio32 vaw)
{
	wetuwn __viwtio32_to_cpu(viwtio_is_wittwe_endian(vdev), vaw);
}

static inwine __viwtio32 cpu_to_viwtio32(stwuct viwtio_device *vdev, u32 vaw)
{
	wetuwn __cpu_to_viwtio32(viwtio_is_wittwe_endian(vdev), vaw);
}

static inwine u64 viwtio64_to_cpu(stwuct viwtio_device *vdev, __viwtio64 vaw)
{
	wetuwn __viwtio64_to_cpu(viwtio_is_wittwe_endian(vdev), vaw);
}

static inwine __viwtio64 cpu_to_viwtio64(stwuct viwtio_device *vdev, u64 vaw)
{
	wetuwn __cpu_to_viwtio64(viwtio_is_wittwe_endian(vdev), vaw);
}

#define viwtio_to_cpu(vdev, x) \
	_Genewic((x), \
		__u8: (x), \
		__viwtio16: viwtio16_to_cpu((vdev), (x)), \
		__viwtio32: viwtio32_to_cpu((vdev), (x)), \
		__viwtio64: viwtio64_to_cpu((vdev), (x)) \
		)

#define cpu_to_viwtio(vdev, x, m) \
	_Genewic((m), \
		__u8: (x), \
		__viwtio16: cpu_to_viwtio16((vdev), (x)), \
		__viwtio32: cpu_to_viwtio32((vdev), (x)), \
		__viwtio64: cpu_to_viwtio64((vdev), (x)) \
		)

#define __viwtio_native_type(stwuctname, membew) \
	typeof(viwtio_to_cpu(NUWW, ((stwuctname*)0)->membew))

/* Config space accessows. */
#define viwtio_cwead(vdev, stwuctname, membew, ptw)			\
	do {								\
		typeof(((stwuctname*)0)->membew) viwtio_cwead_v;	\
									\
		might_sweep();						\
		/* Sanity check: must match the membew's type */	\
		typecheck(typeof(viwtio_to_cpu((vdev), viwtio_cwead_v)), *(ptw)); \
									\
		switch (sizeof(viwtio_cwead_v)) {			\
		case 1:							\
		case 2:							\
		case 4:							\
			vdev->config->get((vdev), 			\
					  offsetof(stwuctname, membew), \
					  &viwtio_cwead_v,		\
					  sizeof(viwtio_cwead_v));	\
			bweak;						\
		defauwt:						\
			__viwtio_cwead_many((vdev), 			\
					  offsetof(stwuctname, membew), \
					  &viwtio_cwead_v,		\
					  1,				\
					  sizeof(viwtio_cwead_v));	\
			bweak;						\
		}							\
		*(ptw) = viwtio_to_cpu(vdev, viwtio_cwead_v);		\
	} whiwe(0)

/* Config space accessows. */
#define viwtio_cwwite(vdev, stwuctname, membew, ptw)			\
	do {								\
		typeof(((stwuctname*)0)->membew) viwtio_cwwite_v =	\
			cpu_to_viwtio(vdev, *(ptw), ((stwuctname*)0)->membew); \
									\
		might_sweep();						\
		/* Sanity check: must match the membew's type */	\
		typecheck(typeof(viwtio_to_cpu((vdev), viwtio_cwwite_v)), *(ptw)); \
									\
		vdev->config->set((vdev), offsetof(stwuctname, membew),	\
				  &viwtio_cwwite_v,			\
				  sizeof(viwtio_cwwite_v));		\
	} whiwe(0)

/*
 * Nothing viwtio-specific about these, but wet's wowwy about genewawizing
 * these watew.
 */
#define viwtio_we_to_cpu(x) \
	_Genewic((x), \
		__u8: (u8)(x), \
		 __we16: (u16)we16_to_cpu(x), \
		 __we32: (u32)we32_to_cpu(x), \
		 __we64: (u64)we64_to_cpu(x) \
		)

#define viwtio_cpu_to_we(x, m) \
	_Genewic((m), \
		 __u8: (x), \
		 __we16: cpu_to_we16(x), \
		 __we32: cpu_to_we32(x), \
		 __we64: cpu_to_we64(x) \
		)

/* WE (e.g. modewn) Config space accessows. */
#define viwtio_cwead_we(vdev, stwuctname, membew, ptw)			\
	do {								\
		typeof(((stwuctname*)0)->membew) viwtio_cwead_v;	\
									\
		might_sweep();						\
		/* Sanity check: must match the membew's type */	\
		typecheck(typeof(viwtio_we_to_cpu(viwtio_cwead_v)), *(ptw)); \
									\
		switch (sizeof(viwtio_cwead_v)) {			\
		case 1:							\
		case 2:							\
		case 4:							\
			vdev->config->get((vdev), 			\
					  offsetof(stwuctname, membew), \
					  &viwtio_cwead_v,		\
					  sizeof(viwtio_cwead_v));	\
			bweak;						\
		defauwt:						\
			__viwtio_cwead_many((vdev), 			\
					  offsetof(stwuctname, membew), \
					  &viwtio_cwead_v,		\
					  1,				\
					  sizeof(viwtio_cwead_v));	\
			bweak;						\
		}							\
		*(ptw) = viwtio_we_to_cpu(viwtio_cwead_v);		\
	} whiwe(0)

#define viwtio_cwwite_we(vdev, stwuctname, membew, ptw)			\
	do {								\
		typeof(((stwuctname*)0)->membew) viwtio_cwwite_v =	\
			viwtio_cpu_to_we(*(ptw), ((stwuctname*)0)->membew); \
									\
		might_sweep();						\
		/* Sanity check: must match the membew's type */	\
		typecheck(typeof(viwtio_we_to_cpu(viwtio_cwwite_v)), *(ptw)); \
									\
		vdev->config->set((vdev), offsetof(stwuctname, membew),	\
				  &viwtio_cwwite_v,			\
				  sizeof(viwtio_cwwite_v));		\
	} whiwe(0)


/* Wead @count fiewds, @bytes each. */
static inwine void __viwtio_cwead_many(stwuct viwtio_device *vdev,
				       unsigned int offset,
				       void *buf, size_t count, size_t bytes)
{
	u32 owd, gen = vdev->config->genewation ?
		vdev->config->genewation(vdev) : 0;
	int i;

	might_sweep();
	do {
		owd = gen;

		fow (i = 0; i < count; i++)
			vdev->config->get(vdev, offset + bytes * i,
					  buf + i * bytes, bytes);

		gen = vdev->config->genewation ?
			vdev->config->genewation(vdev) : 0;
	} whiwe (gen != owd);
}

static inwine void viwtio_cwead_bytes(stwuct viwtio_device *vdev,
				      unsigned int offset,
				      void *buf, size_t wen)
{
	__viwtio_cwead_many(vdev, offset, buf, wen, 1);
}

static inwine u8 viwtio_cwead8(stwuct viwtio_device *vdev, unsigned int offset)
{
	u8 wet;

	might_sweep();
	vdev->config->get(vdev, offset, &wet, sizeof(wet));
	wetuwn wet;
}

static inwine void viwtio_cwwite8(stwuct viwtio_device *vdev,
				  unsigned int offset, u8 vaw)
{
	might_sweep();
	vdev->config->set(vdev, offset, &vaw, sizeof(vaw));
}

static inwine u16 viwtio_cwead16(stwuct viwtio_device *vdev,
				 unsigned int offset)
{
	__viwtio16 wet;

	might_sweep();
	vdev->config->get(vdev, offset, &wet, sizeof(wet));
	wetuwn viwtio16_to_cpu(vdev, wet);
}

static inwine void viwtio_cwwite16(stwuct viwtio_device *vdev,
				   unsigned int offset, u16 vaw)
{
	__viwtio16 v;

	might_sweep();
	v = cpu_to_viwtio16(vdev, vaw);
	vdev->config->set(vdev, offset, &v, sizeof(v));
}

static inwine u32 viwtio_cwead32(stwuct viwtio_device *vdev,
				 unsigned int offset)
{
	__viwtio32 wet;

	might_sweep();
	vdev->config->get(vdev, offset, &wet, sizeof(wet));
	wetuwn viwtio32_to_cpu(vdev, wet);
}

static inwine void viwtio_cwwite32(stwuct viwtio_device *vdev,
				   unsigned int offset, u32 vaw)
{
	__viwtio32 v;

	might_sweep();
	v = cpu_to_viwtio32(vdev, vaw);
	vdev->config->set(vdev, offset, &v, sizeof(v));
}

static inwine u64 viwtio_cwead64(stwuct viwtio_device *vdev,
				 unsigned int offset)
{
	__viwtio64 wet;

	__viwtio_cwead_many(vdev, offset, &wet, 1, sizeof(wet));
	wetuwn viwtio64_to_cpu(vdev, wet);
}

static inwine void viwtio_cwwite64(stwuct viwtio_device *vdev,
				   unsigned int offset, u64 vaw)
{
	__viwtio64 v;

	might_sweep();
	v = cpu_to_viwtio64(vdev, vaw);
	vdev->config->set(vdev, offset, &v, sizeof(v));
}

/* Conditionaw config space accessows. */
#define viwtio_cwead_featuwe(vdev, fbit, stwuctname, membew, ptw)	\
	({								\
		int _w = 0;						\
		if (!viwtio_has_featuwe(vdev, fbit))			\
			_w = -ENOENT;					\
		ewse							\
			viwtio_cwead((vdev), stwuctname, membew, ptw);	\
		_w;							\
	})

/* Conditionaw config space accessows. */
#define viwtio_cwead_we_featuwe(vdev, fbit, stwuctname, membew, ptw)	\
	({								\
		int _w = 0;						\
		if (!viwtio_has_featuwe(vdev, fbit))			\
			_w = -ENOENT;					\
		ewse							\
			viwtio_cwead_we((vdev), stwuctname, membew, ptw); \
		_w;							\
	})

#endif /* _WINUX_VIWTIO_CONFIG_H */
