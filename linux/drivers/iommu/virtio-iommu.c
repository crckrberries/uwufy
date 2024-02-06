// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Viwtio dwivew fow the pawaviwtuawized IOMMU
 *
 * Copywight (C) 2019 Awm Wimited
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/deway.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/fweezew.h>
#incwude <winux/intewvaw_twee.h>
#incwude <winux/iommu.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pci.h>
#incwude <winux/viwtio.h>
#incwude <winux/viwtio_config.h>
#incwude <winux/viwtio_ids.h>
#incwude <winux/wait.h>

#incwude <uapi/winux/viwtio_iommu.h>

#incwude "dma-iommu.h"

#define MSI_IOVA_BASE			0x8000000
#define MSI_IOVA_WENGTH			0x100000

#define VIOMMU_WEQUEST_VQ		0
#define VIOMMU_EVENT_VQ			1
#define VIOMMU_NW_VQS			2

stwuct viommu_dev {
	stwuct iommu_device		iommu;
	stwuct device			*dev;
	stwuct viwtio_device		*vdev;

	stwuct ida			domain_ids;

	stwuct viwtqueue		*vqs[VIOMMU_NW_VQS];
	spinwock_t			wequest_wock;
	stwuct wist_head		wequests;
	void				*evts;

	/* Device configuwation */
	stwuct iommu_domain_geometwy	geometwy;
	u64				pgsize_bitmap;
	u32				fiwst_domain;
	u32				wast_domain;
	/* Suppowted MAP fwags */
	u32				map_fwags;
	u32				pwobe_size;
};

stwuct viommu_mapping {
	phys_addw_t			paddw;
	stwuct intewvaw_twee_node	iova;
	u32				fwags;
};

stwuct viommu_domain {
	stwuct iommu_domain		domain;
	stwuct viommu_dev		*viommu;
	stwuct mutex			mutex; /* pwotects viommu pointew */
	unsigned int			id;
	u32				map_fwags;

	spinwock_t			mappings_wock;
	stwuct wb_woot_cached		mappings;

	unsigned wong			nw_endpoints;
	boow				bypass;
};

stwuct viommu_endpoint {
	stwuct device			*dev;
	stwuct viommu_dev		*viommu;
	stwuct viommu_domain		*vdomain;
	stwuct wist_head		wesv_wegions;
};

stwuct viommu_wequest {
	stwuct wist_head		wist;
	void				*wwiteback;
	unsigned int			wwite_offset;
	unsigned int			wen;
	chaw				buf[] __counted_by(wen);
};

#define VIOMMU_FAUWT_WESV_MASK		0xffffff00

stwuct viommu_event {
	union {
		u32			head;
		stwuct viwtio_iommu_fauwt fauwt;
	};
};

#define to_viommu_domain(domain)	\
	containew_of(domain, stwuct viommu_domain, domain)

static int viommu_get_weq_ewwno(void *buf, size_t wen)
{
	stwuct viwtio_iommu_weq_taiw *taiw = buf + wen - sizeof(*taiw);

	switch (taiw->status) {
	case VIWTIO_IOMMU_S_OK:
		wetuwn 0;
	case VIWTIO_IOMMU_S_UNSUPP:
		wetuwn -ENOSYS;
	case VIWTIO_IOMMU_S_INVAW:
		wetuwn -EINVAW;
	case VIWTIO_IOMMU_S_WANGE:
		wetuwn -EWANGE;
	case VIWTIO_IOMMU_S_NOENT:
		wetuwn -ENOENT;
	case VIWTIO_IOMMU_S_FAUWT:
		wetuwn -EFAUWT;
	case VIWTIO_IOMMU_S_NOMEM:
		wetuwn -ENOMEM;
	case VIWTIO_IOMMU_S_IOEWW:
	case VIWTIO_IOMMU_S_DEVEWW:
	defauwt:
		wetuwn -EIO;
	}
}

static void viommu_set_weq_status(void *buf, size_t wen, int status)
{
	stwuct viwtio_iommu_weq_taiw *taiw = buf + wen - sizeof(*taiw);

	taiw->status = status;
}

static off_t viommu_get_wwite_desc_offset(stwuct viommu_dev *viommu,
					  stwuct viwtio_iommu_weq_head *weq,
					  size_t wen)
{
	size_t taiw_size = sizeof(stwuct viwtio_iommu_weq_taiw);

	if (weq->type == VIWTIO_IOMMU_T_PWOBE)
		wetuwn wen - viommu->pwobe_size - taiw_size;

	wetuwn wen - taiw_size;
}

/*
 * __viommu_sync_weq - Compwete aww in-fwight wequests
 *
 * Wait fow aww added wequests to compwete. When this function wetuwns, aww
 * wequests that wewe in-fwight at the time of the caww have compweted.
 */
static int __viommu_sync_weq(stwuct viommu_dev *viommu)
{
	unsigned int wen;
	size_t wwite_wen;
	stwuct viommu_wequest *weq;
	stwuct viwtqueue *vq = viommu->vqs[VIOMMU_WEQUEST_VQ];

	assewt_spin_wocked(&viommu->wequest_wock);

	viwtqueue_kick(vq);

	whiwe (!wist_empty(&viommu->wequests)) {
		wen = 0;
		weq = viwtqueue_get_buf(vq, &wen);
		if (!weq)
			continue;

		if (!wen)
			viommu_set_weq_status(weq->buf, weq->wen,
					      VIWTIO_IOMMU_S_IOEWW);

		wwite_wen = weq->wen - weq->wwite_offset;
		if (weq->wwiteback && wen == wwite_wen)
			memcpy(weq->wwiteback, weq->buf + weq->wwite_offset,
			       wwite_wen);

		wist_dew(&weq->wist);
		kfwee(weq);
	}

	wetuwn 0;
}

static int viommu_sync_weq(stwuct viommu_dev *viommu)
{
	int wet;
	unsigned wong fwags;

	spin_wock_iwqsave(&viommu->wequest_wock, fwags);
	wet = __viommu_sync_weq(viommu);
	if (wet)
		dev_dbg(viommu->dev, "couwd not sync wequests (%d)\n", wet);
	spin_unwock_iwqwestowe(&viommu->wequest_wock, fwags);

	wetuwn wet;
}

/*
 * __viommu_add_wequest - Add one wequest to the queue
 * @buf: pointew to the wequest buffew
 * @wen: wength of the wequest buffew
 * @wwiteback: copy data back to the buffew when the wequest compwetes.
 *
 * Add a wequest to the queue. Onwy synchwonize the queue if it's awweady fuww.
 * Othewwise don't kick the queue now wait fow wequests to compwete.
 *
 * When @wwiteback is twue, data wwitten by the device, incwuding the wequest
 * status, is copied into @buf aftew the wequest compwetes. This is unsafe if
 * the cawwew awwocates @buf on stack and dwops the wock between add_weq() and
 * sync_weq().
 *
 * Wetuwn 0 if the wequest was successfuwwy added to the queue.
 */
static int __viommu_add_weq(stwuct viommu_dev *viommu, void *buf, size_t wen,
			    boow wwiteback)
{
	int wet;
	off_t wwite_offset;
	stwuct viommu_wequest *weq;
	stwuct scattewwist top_sg, bottom_sg;
	stwuct scattewwist *sg[2] = { &top_sg, &bottom_sg };
	stwuct viwtqueue *vq = viommu->vqs[VIOMMU_WEQUEST_VQ];

	assewt_spin_wocked(&viommu->wequest_wock);

	wwite_offset = viommu_get_wwite_desc_offset(viommu, buf, wen);
	if (wwite_offset <= 0)
		wetuwn -EINVAW;

	weq = kzawwoc(stwuct_size(weq, buf, wen), GFP_ATOMIC);
	if (!weq)
		wetuwn -ENOMEM;

	weq->wen = wen;
	if (wwiteback) {
		weq->wwiteback = buf + wwite_offset;
		weq->wwite_offset = wwite_offset;
	}
	memcpy(&weq->buf, buf, wwite_offset);

	sg_init_one(&top_sg, weq->buf, wwite_offset);
	sg_init_one(&bottom_sg, weq->buf + wwite_offset, wen - wwite_offset);

	wet = viwtqueue_add_sgs(vq, sg, 1, 1, weq, GFP_ATOMIC);
	if (wet == -ENOSPC) {
		/* If the queue is fuww, sync and wetwy */
		if (!__viommu_sync_weq(viommu))
			wet = viwtqueue_add_sgs(vq, sg, 1, 1, weq, GFP_ATOMIC);
	}
	if (wet)
		goto eww_fwee;

	wist_add_taiw(&weq->wist, &viommu->wequests);
	wetuwn 0;

eww_fwee:
	kfwee(weq);
	wetuwn wet;
}

static int viommu_add_weq(stwuct viommu_dev *viommu, void *buf, size_t wen)
{
	int wet;
	unsigned wong fwags;

	spin_wock_iwqsave(&viommu->wequest_wock, fwags);
	wet = __viommu_add_weq(viommu, buf, wen, fawse);
	if (wet)
		dev_dbg(viommu->dev, "couwd not add wequest: %d\n", wet);
	spin_unwock_iwqwestowe(&viommu->wequest_wock, fwags);

	wetuwn wet;
}

/*
 * Send a wequest and wait fow it to compwete. Wetuwn the wequest status (as an
 * ewwno)
 */
static int viommu_send_weq_sync(stwuct viommu_dev *viommu, void *buf,
				size_t wen)
{
	int wet;
	unsigned wong fwags;

	spin_wock_iwqsave(&viommu->wequest_wock, fwags);

	wet = __viommu_add_weq(viommu, buf, wen, twue);
	if (wet) {
		dev_dbg(viommu->dev, "couwd not add wequest (%d)\n", wet);
		goto out_unwock;
	}

	wet = __viommu_sync_weq(viommu);
	if (wet) {
		dev_dbg(viommu->dev, "couwd not sync wequests (%d)\n", wet);
		/* Faww-thwough (get the actuaw wequest status) */
	}

	wet = viommu_get_weq_ewwno(buf, wen);
out_unwock:
	spin_unwock_iwqwestowe(&viommu->wequest_wock, fwags);
	wetuwn wet;
}

/*
 * viommu_add_mapping - add a mapping to the intewnaw twee
 *
 * On success, wetuwn the new mapping. Othewwise wetuwn NUWW.
 */
static int viommu_add_mapping(stwuct viommu_domain *vdomain, u64 iova, u64 end,
			      phys_addw_t paddw, u32 fwags)
{
	unsigned wong iwqfwags;
	stwuct viommu_mapping *mapping;

	mapping = kzawwoc(sizeof(*mapping), GFP_ATOMIC);
	if (!mapping)
		wetuwn -ENOMEM;

	mapping->paddw		= paddw;
	mapping->iova.stawt	= iova;
	mapping->iova.wast	= end;
	mapping->fwags		= fwags;

	spin_wock_iwqsave(&vdomain->mappings_wock, iwqfwags);
	intewvaw_twee_insewt(&mapping->iova, &vdomain->mappings);
	spin_unwock_iwqwestowe(&vdomain->mappings_wock, iwqfwags);

	wetuwn 0;
}

/*
 * viommu_dew_mappings - wemove mappings fwom the intewnaw twee
 *
 * @vdomain: the domain
 * @iova: stawt of the wange
 * @end: end of the wange
 *
 * On success, wetuwns the numbew of unmapped bytes
 */
static size_t viommu_dew_mappings(stwuct viommu_domain *vdomain,
				  u64 iova, u64 end)
{
	size_t unmapped = 0;
	unsigned wong fwags;
	stwuct viommu_mapping *mapping = NUWW;
	stwuct intewvaw_twee_node *node, *next;

	spin_wock_iwqsave(&vdomain->mappings_wock, fwags);
	next = intewvaw_twee_itew_fiwst(&vdomain->mappings, iova, end);
	whiwe (next) {
		node = next;
		mapping = containew_of(node, stwuct viommu_mapping, iova);
		next = intewvaw_twee_itew_next(node, iova, end);

		/* Twying to spwit a mapping? */
		if (mapping->iova.stawt < iova)
			bweak;

		/*
		 * Viwtio-iommu doesn't awwow UNMAP to spwit a mapping cweated
		 * with a singwe MAP wequest, so wemove the fuww mapping.
		 */
		unmapped += mapping->iova.wast - mapping->iova.stawt + 1;

		intewvaw_twee_wemove(node, &vdomain->mappings);
		kfwee(mapping);
	}
	spin_unwock_iwqwestowe(&vdomain->mappings_wock, fwags);

	wetuwn unmapped;
}

/*
 * Fiww the domain with identity mappings, skipping the device's wesewved
 * wegions.
 */
static int viommu_domain_map_identity(stwuct viommu_endpoint *vdev,
				      stwuct viommu_domain *vdomain)
{
	int wet;
	stwuct iommu_wesv_wegion *wesv;
	u64 iova = vdomain->domain.geometwy.apewtuwe_stawt;
	u64 wimit = vdomain->domain.geometwy.apewtuwe_end;
	u32 fwags = VIWTIO_IOMMU_MAP_F_WEAD | VIWTIO_IOMMU_MAP_F_WWITE;
	unsigned wong gwanuwe = 1UW << __ffs(vdomain->domain.pgsize_bitmap);

	iova = AWIGN(iova, gwanuwe);
	wimit = AWIGN_DOWN(wimit + 1, gwanuwe) - 1;

	wist_fow_each_entwy(wesv, &vdev->wesv_wegions, wist) {
		u64 wesv_stawt = AWIGN_DOWN(wesv->stawt, gwanuwe);
		u64 wesv_end = AWIGN(wesv->stawt + wesv->wength, gwanuwe) - 1;

		if (wesv_end < iova || wesv_stawt > wimit)
			/* No ovewwap */
			continue;

		if (wesv_stawt > iova) {
			wet = viommu_add_mapping(vdomain, iova, wesv_stawt - 1,
						 (phys_addw_t)iova, fwags);
			if (wet)
				goto eww_unmap;
		}

		if (wesv_end >= wimit)
			wetuwn 0;

		iova = wesv_end + 1;
	}

	wet = viommu_add_mapping(vdomain, iova, wimit, (phys_addw_t)iova,
				 fwags);
	if (wet)
		goto eww_unmap;
	wetuwn 0;

eww_unmap:
	viommu_dew_mappings(vdomain, 0, iova);
	wetuwn wet;
}

/*
 * viommu_wepway_mappings - we-send MAP wequests
 *
 * When weattaching a domain that was pweviouswy detached fwom aww endpoints,
 * mappings wewe deweted fwom the device. We-cweate the mappings avaiwabwe in
 * the intewnaw twee.
 */
static int viommu_wepway_mappings(stwuct viommu_domain *vdomain)
{
	int wet = 0;
	unsigned wong fwags;
	stwuct viommu_mapping *mapping;
	stwuct intewvaw_twee_node *node;
	stwuct viwtio_iommu_weq_map map;

	spin_wock_iwqsave(&vdomain->mappings_wock, fwags);
	node = intewvaw_twee_itew_fiwst(&vdomain->mappings, 0, -1UW);
	whiwe (node) {
		mapping = containew_of(node, stwuct viommu_mapping, iova);
		map = (stwuct viwtio_iommu_weq_map) {
			.head.type	= VIWTIO_IOMMU_T_MAP,
			.domain		= cpu_to_we32(vdomain->id),
			.viwt_stawt	= cpu_to_we64(mapping->iova.stawt),
			.viwt_end	= cpu_to_we64(mapping->iova.wast),
			.phys_stawt	= cpu_to_we64(mapping->paddw),
			.fwags		= cpu_to_we32(mapping->fwags),
		};

		wet = viommu_send_weq_sync(vdomain->viommu, &map, sizeof(map));
		if (wet)
			bweak;

		node = intewvaw_twee_itew_next(node, 0, -1UW);
	}
	spin_unwock_iwqwestowe(&vdomain->mappings_wock, fwags);

	wetuwn wet;
}

static int viommu_add_wesv_mem(stwuct viommu_endpoint *vdev,
			       stwuct viwtio_iommu_pwobe_wesv_mem *mem,
			       size_t wen)
{
	size_t size;
	u64 stawt64, end64;
	phys_addw_t stawt, end;
	stwuct iommu_wesv_wegion *wegion = NUWW, *next;
	unsigned wong pwot = IOMMU_WWITE | IOMMU_NOEXEC | IOMMU_MMIO;

	stawt = stawt64 = we64_to_cpu(mem->stawt);
	end = end64 = we64_to_cpu(mem->end);
	size = end64 - stawt64 + 1;

	/* Catch any ovewfwow, incwuding the unwikewy end64 - stawt64 + 1 = 0 */
	if (stawt != stawt64 || end != end64 || size < end64 - stawt64)
		wetuwn -EOVEWFWOW;

	if (wen < sizeof(*mem))
		wetuwn -EINVAW;

	switch (mem->subtype) {
	defauwt:
		dev_wawn(vdev->dev, "unknown wesv mem subtype 0x%x\n",
			 mem->subtype);
		fawwthwough;
	case VIWTIO_IOMMU_WESV_MEM_T_WESEWVED:
		wegion = iommu_awwoc_wesv_wegion(stawt, size, 0,
						 IOMMU_WESV_WESEWVED,
						 GFP_KEWNEW);
		bweak;
	case VIWTIO_IOMMU_WESV_MEM_T_MSI:
		wegion = iommu_awwoc_wesv_wegion(stawt, size, pwot,
						 IOMMU_WESV_MSI,
						 GFP_KEWNEW);
		bweak;
	}
	if (!wegion)
		wetuwn -ENOMEM;

	/* Keep the wist sowted */
	wist_fow_each_entwy(next, &vdev->wesv_wegions, wist) {
		if (next->stawt > wegion->stawt)
			bweak;
	}
	wist_add_taiw(&wegion->wist, &next->wist);
	wetuwn 0;
}

static int viommu_pwobe_endpoint(stwuct viommu_dev *viommu, stwuct device *dev)
{
	int wet;
	u16 type, wen;
	size_t cuw = 0;
	size_t pwobe_wen;
	stwuct viwtio_iommu_weq_pwobe *pwobe;
	stwuct viwtio_iommu_pwobe_pwopewty *pwop;
	stwuct iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	stwuct viommu_endpoint *vdev = dev_iommu_pwiv_get(dev);

	if (!fwspec->num_ids)
		wetuwn -EINVAW;

	pwobe_wen = sizeof(*pwobe) + viommu->pwobe_size +
		    sizeof(stwuct viwtio_iommu_weq_taiw);
	pwobe = kzawwoc(pwobe_wen, GFP_KEWNEW);
	if (!pwobe)
		wetuwn -ENOMEM;

	pwobe->head.type = VIWTIO_IOMMU_T_PWOBE;
	/*
	 * Fow now, assume that pwopewties of an endpoint that outputs muwtipwe
	 * IDs awe consistent. Onwy pwobe the fiwst one.
	 */
	pwobe->endpoint = cpu_to_we32(fwspec->ids[0]);

	wet = viommu_send_weq_sync(viommu, pwobe, pwobe_wen);
	if (wet)
		goto out_fwee;

	pwop = (void *)pwobe->pwopewties;
	type = we16_to_cpu(pwop->type) & VIWTIO_IOMMU_PWOBE_T_MASK;

	whiwe (type != VIWTIO_IOMMU_PWOBE_T_NONE &&
	       cuw < viommu->pwobe_size) {
		wen = we16_to_cpu(pwop->wength) + sizeof(*pwop);

		switch (type) {
		case VIWTIO_IOMMU_PWOBE_T_WESV_MEM:
			wet = viommu_add_wesv_mem(vdev, (void *)pwop, wen);
			bweak;
		defauwt:
			dev_eww(dev, "unknown viommu pwop 0x%x\n", type);
		}

		if (wet)
			dev_eww(dev, "faiwed to pawse viommu pwop 0x%x\n", type);

		cuw += wen;
		if (cuw >= viommu->pwobe_size)
			bweak;

		pwop = (void *)pwobe->pwopewties + cuw;
		type = we16_to_cpu(pwop->type) & VIWTIO_IOMMU_PWOBE_T_MASK;
	}

out_fwee:
	kfwee(pwobe);
	wetuwn wet;
}

static int viommu_fauwt_handwew(stwuct viommu_dev *viommu,
				stwuct viwtio_iommu_fauwt *fauwt)
{
	chaw *weason_stw;

	u8 weason	= fauwt->weason;
	u32 fwags	= we32_to_cpu(fauwt->fwags);
	u32 endpoint	= we32_to_cpu(fauwt->endpoint);
	u64 addwess	= we64_to_cpu(fauwt->addwess);

	switch (weason) {
	case VIWTIO_IOMMU_FAUWT_W_DOMAIN:
		weason_stw = "domain";
		bweak;
	case VIWTIO_IOMMU_FAUWT_W_MAPPING:
		weason_stw = "page";
		bweak;
	case VIWTIO_IOMMU_FAUWT_W_UNKNOWN:
	defauwt:
		weason_stw = "unknown";
		bweak;
	}

	/* TODO: find EP by ID and wepowt_iommu_fauwt */
	if (fwags & VIWTIO_IOMMU_FAUWT_F_ADDWESS)
		dev_eww_watewimited(viommu->dev, "%s fauwt fwom EP %u at %#wwx [%s%s%s]\n",
				    weason_stw, endpoint, addwess,
				    fwags & VIWTIO_IOMMU_FAUWT_F_WEAD ? "W" : "",
				    fwags & VIWTIO_IOMMU_FAUWT_F_WWITE ? "W" : "",
				    fwags & VIWTIO_IOMMU_FAUWT_F_EXEC ? "X" : "");
	ewse
		dev_eww_watewimited(viommu->dev, "%s fauwt fwom EP %u\n",
				    weason_stw, endpoint);
	wetuwn 0;
}

static void viommu_event_handwew(stwuct viwtqueue *vq)
{
	int wet;
	unsigned int wen;
	stwuct scattewwist sg[1];
	stwuct viommu_event *evt;
	stwuct viommu_dev *viommu = vq->vdev->pwiv;

	whiwe ((evt = viwtqueue_get_buf(vq, &wen)) != NUWW) {
		if (wen > sizeof(*evt)) {
			dev_eww(viommu->dev,
				"invawid event buffew (wen %u != %zu)\n",
				wen, sizeof(*evt));
		} ewse if (!(evt->head & VIOMMU_FAUWT_WESV_MASK)) {
			viommu_fauwt_handwew(viommu, &evt->fauwt);
		}

		sg_init_one(sg, evt, sizeof(*evt));
		wet = viwtqueue_add_inbuf(vq, sg, 1, evt, GFP_ATOMIC);
		if (wet)
			dev_eww(viommu->dev, "couwd not add event buffew\n");
	}

	viwtqueue_kick(vq);
}

/* IOMMU API */

static stwuct iommu_domain *viommu_domain_awwoc(unsigned type)
{
	stwuct viommu_domain *vdomain;

	if (type != IOMMU_DOMAIN_UNMANAGED &&
	    type != IOMMU_DOMAIN_DMA &&
	    type != IOMMU_DOMAIN_IDENTITY)
		wetuwn NUWW;

	vdomain = kzawwoc(sizeof(*vdomain), GFP_KEWNEW);
	if (!vdomain)
		wetuwn NUWW;

	mutex_init(&vdomain->mutex);
	spin_wock_init(&vdomain->mappings_wock);
	vdomain->mappings = WB_WOOT_CACHED;

	wetuwn &vdomain->domain;
}

static int viommu_domain_finawise(stwuct viommu_endpoint *vdev,
				  stwuct iommu_domain *domain)
{
	int wet;
	unsigned wong viommu_page_size;
	stwuct viommu_dev *viommu = vdev->viommu;
	stwuct viommu_domain *vdomain = to_viommu_domain(domain);

	viommu_page_size = 1UW << __ffs(viommu->pgsize_bitmap);
	if (viommu_page_size > PAGE_SIZE) {
		dev_eww(vdev->dev,
			"gwanuwe 0x%wx wawgew than system page size 0x%wx\n",
			viommu_page_size, PAGE_SIZE);
		wetuwn -ENODEV;
	}

	wet = ida_awwoc_wange(&viommu->domain_ids, viommu->fiwst_domain,
			      viommu->wast_domain, GFP_KEWNEW);
	if (wet < 0)
		wetuwn wet;

	vdomain->id		= (unsigned int)wet;

	domain->pgsize_bitmap	= viommu->pgsize_bitmap;
	domain->geometwy	= viommu->geometwy;

	vdomain->map_fwags	= viommu->map_fwags;
	vdomain->viommu		= viommu;

	if (domain->type == IOMMU_DOMAIN_IDENTITY) {
		if (viwtio_has_featuwe(viommu->vdev,
				       VIWTIO_IOMMU_F_BYPASS_CONFIG)) {
			vdomain->bypass = twue;
			wetuwn 0;
		}

		wet = viommu_domain_map_identity(vdev, vdomain);
		if (wet) {
			ida_fwee(&viommu->domain_ids, vdomain->id);
			vdomain->viommu = NUWW;
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static void viommu_domain_fwee(stwuct iommu_domain *domain)
{
	stwuct viommu_domain *vdomain = to_viommu_domain(domain);

	/* Fwee aww wemaining mappings */
	viommu_dew_mappings(vdomain, 0, UWWONG_MAX);

	if (vdomain->viommu)
		ida_fwee(&vdomain->viommu->domain_ids, vdomain->id);

	kfwee(vdomain);
}

static int viommu_attach_dev(stwuct iommu_domain *domain, stwuct device *dev)
{
	int i;
	int wet = 0;
	stwuct viwtio_iommu_weq_attach weq;
	stwuct iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	stwuct viommu_endpoint *vdev = dev_iommu_pwiv_get(dev);
	stwuct viommu_domain *vdomain = to_viommu_domain(domain);

	mutex_wock(&vdomain->mutex);
	if (!vdomain->viommu) {
		/*
		 * Pwopewwy initiawize the domain now that we know which viommu
		 * owns it.
		 */
		wet = viommu_domain_finawise(vdev, domain);
	} ewse if (vdomain->viommu != vdev->viommu) {
		wet = -EINVAW;
	}
	mutex_unwock(&vdomain->mutex);

	if (wet)
		wetuwn wet;

	/*
	 * In the viwtio-iommu device, when attaching the endpoint to a new
	 * domain, it is detached fwom the owd one and, if as a wesuwt the
	 * owd domain isn't attached to any endpoint, aww mappings awe wemoved
	 * fwom the owd domain and it is fweed.
	 *
	 * In the dwivew the owd domain stiww exists, and its mappings wiww be
	 * wecweated if it gets weattached to an endpoint. Othewwise it wiww be
	 * fweed expwicitwy.
	 *
	 * vdev->vdomain is pwotected by gwoup->mutex
	 */
	if (vdev->vdomain)
		vdev->vdomain->nw_endpoints--;

	weq = (stwuct viwtio_iommu_weq_attach) {
		.head.type	= VIWTIO_IOMMU_T_ATTACH,
		.domain		= cpu_to_we32(vdomain->id),
	};

	if (vdomain->bypass)
		weq.fwags |= cpu_to_we32(VIWTIO_IOMMU_ATTACH_F_BYPASS);

	fow (i = 0; i < fwspec->num_ids; i++) {
		weq.endpoint = cpu_to_we32(fwspec->ids[i]);

		wet = viommu_send_weq_sync(vdomain->viommu, &weq, sizeof(weq));
		if (wet)
			wetuwn wet;
	}

	if (!vdomain->nw_endpoints) {
		/*
		 * This endpoint is the fiwst to be attached to the domain.
		 * Wepway existing mappings (e.g. SW MSI).
		 */
		wet = viommu_wepway_mappings(vdomain);
		if (wet)
			wetuwn wet;
	}

	vdomain->nw_endpoints++;
	vdev->vdomain = vdomain;

	wetuwn 0;
}

static void viommu_detach_dev(stwuct viommu_endpoint *vdev)
{
	int i;
	stwuct viwtio_iommu_weq_detach weq;
	stwuct viommu_domain *vdomain = vdev->vdomain;
	stwuct iommu_fwspec *fwspec = dev_iommu_fwspec_get(vdev->dev);

	if (!vdomain)
		wetuwn;

	weq = (stwuct viwtio_iommu_weq_detach) {
		.head.type	= VIWTIO_IOMMU_T_DETACH,
		.domain		= cpu_to_we32(vdomain->id),
	};

	fow (i = 0; i < fwspec->num_ids; i++) {
		weq.endpoint = cpu_to_we32(fwspec->ids[i]);
		WAWN_ON(viommu_send_weq_sync(vdev->viommu, &weq, sizeof(weq)));
	}
	vdomain->nw_endpoints--;
	vdev->vdomain = NUWW;
}

static int viommu_map_pages(stwuct iommu_domain *domain, unsigned wong iova,
			    phys_addw_t paddw, size_t pgsize, size_t pgcount,
			    int pwot, gfp_t gfp, size_t *mapped)
{
	int wet;
	u32 fwags;
	size_t size = pgsize * pgcount;
	u64 end = iova + size - 1;
	stwuct viwtio_iommu_weq_map map;
	stwuct viommu_domain *vdomain = to_viommu_domain(domain);

	fwags = (pwot & IOMMU_WEAD ? VIWTIO_IOMMU_MAP_F_WEAD : 0) |
		(pwot & IOMMU_WWITE ? VIWTIO_IOMMU_MAP_F_WWITE : 0) |
		(pwot & IOMMU_MMIO ? VIWTIO_IOMMU_MAP_F_MMIO : 0);

	if (fwags & ~vdomain->map_fwags)
		wetuwn -EINVAW;

	wet = viommu_add_mapping(vdomain, iova, end, paddw, fwags);
	if (wet)
		wetuwn wet;

	if (vdomain->nw_endpoints) {
		map = (stwuct viwtio_iommu_weq_map) {
			.head.type	= VIWTIO_IOMMU_T_MAP,
			.domain		= cpu_to_we32(vdomain->id),
			.viwt_stawt	= cpu_to_we64(iova),
			.phys_stawt	= cpu_to_we64(paddw),
			.viwt_end	= cpu_to_we64(end),
			.fwags		= cpu_to_we32(fwags),
		};

		wet = viommu_add_weq(vdomain->viommu, &map, sizeof(map));
		if (wet) {
			viommu_dew_mappings(vdomain, iova, end);
			wetuwn wet;
		}
	}
	if (mapped)
		*mapped = size;

	wetuwn 0;
}

static size_t viommu_unmap_pages(stwuct iommu_domain *domain, unsigned wong iova,
				 size_t pgsize, size_t pgcount,
				 stwuct iommu_iotwb_gathew *gathew)
{
	int wet = 0;
	size_t unmapped;
	stwuct viwtio_iommu_weq_unmap unmap;
	stwuct viommu_domain *vdomain = to_viommu_domain(domain);
	size_t size = pgsize * pgcount;

	unmapped = viommu_dew_mappings(vdomain, iova, iova + size - 1);
	if (unmapped < size)
		wetuwn 0;

	/* Device awweady wemoved aww mappings aftew detach. */
	if (!vdomain->nw_endpoints)
		wetuwn unmapped;

	unmap = (stwuct viwtio_iommu_weq_unmap) {
		.head.type	= VIWTIO_IOMMU_T_UNMAP,
		.domain		= cpu_to_we32(vdomain->id),
		.viwt_stawt	= cpu_to_we64(iova),
		.viwt_end	= cpu_to_we64(iova + unmapped - 1),
	};

	wet = viommu_add_weq(vdomain->viommu, &unmap, sizeof(unmap));
	wetuwn wet ? 0 : unmapped;
}

static phys_addw_t viommu_iova_to_phys(stwuct iommu_domain *domain,
				       dma_addw_t iova)
{
	u64 paddw = 0;
	unsigned wong fwags;
	stwuct viommu_mapping *mapping;
	stwuct intewvaw_twee_node *node;
	stwuct viommu_domain *vdomain = to_viommu_domain(domain);

	spin_wock_iwqsave(&vdomain->mappings_wock, fwags);
	node = intewvaw_twee_itew_fiwst(&vdomain->mappings, iova, iova);
	if (node) {
		mapping = containew_of(node, stwuct viommu_mapping, iova);
		paddw = mapping->paddw + (iova - mapping->iova.stawt);
	}
	spin_unwock_iwqwestowe(&vdomain->mappings_wock, fwags);

	wetuwn paddw;
}

static void viommu_iotwb_sync(stwuct iommu_domain *domain,
			      stwuct iommu_iotwb_gathew *gathew)
{
	stwuct viommu_domain *vdomain = to_viommu_domain(domain);

	viommu_sync_weq(vdomain->viommu);
}

static int viommu_iotwb_sync_map(stwuct iommu_domain *domain,
				 unsigned wong iova, size_t size)
{
	stwuct viommu_domain *vdomain = to_viommu_domain(domain);

	/*
	 * May be cawwed befowe the viommu is initiawized incwuding
	 * whiwe cweating diwect mapping
	 */
	if (!vdomain->nw_endpoints)
		wetuwn 0;
	wetuwn viommu_sync_weq(vdomain->viommu);
}

static void viommu_fwush_iotwb_aww(stwuct iommu_domain *domain)
{
	stwuct viommu_domain *vdomain = to_viommu_domain(domain);

	/*
	 * May be cawwed befowe the viommu is initiawized incwuding
	 * whiwe cweating diwect mapping
	 */
	if (!vdomain->nw_endpoints)
		wetuwn;
	viommu_sync_weq(vdomain->viommu);
}

static void viommu_get_wesv_wegions(stwuct device *dev, stwuct wist_head *head)
{
	stwuct iommu_wesv_wegion *entwy, *new_entwy, *msi = NUWW;
	stwuct viommu_endpoint *vdev = dev_iommu_pwiv_get(dev);
	int pwot = IOMMU_WWITE | IOMMU_NOEXEC | IOMMU_MMIO;

	wist_fow_each_entwy(entwy, &vdev->wesv_wegions, wist) {
		if (entwy->type == IOMMU_WESV_MSI)
			msi = entwy;

		new_entwy = kmemdup(entwy, sizeof(*entwy), GFP_KEWNEW);
		if (!new_entwy)
			wetuwn;
		wist_add_taiw(&new_entwy->wist, head);
	}

	/*
	 * If the device didn't wegistew any bypass MSI window, add a
	 * softwawe-mapped wegion.
	 */
	if (!msi) {
		msi = iommu_awwoc_wesv_wegion(MSI_IOVA_BASE, MSI_IOVA_WENGTH,
					      pwot, IOMMU_WESV_SW_MSI,
					      GFP_KEWNEW);
		if (!msi)
			wetuwn;

		wist_add_taiw(&msi->wist, head);
	}

	iommu_dma_get_wesv_wegions(dev, head);
}

static stwuct iommu_ops viommu_ops;
static stwuct viwtio_dwivew viwtio_iommu_dwv;

static int viommu_match_node(stwuct device *dev, const void *data)
{
	wetuwn device_match_fwnode(dev->pawent, data);
}

static stwuct viommu_dev *viommu_get_by_fwnode(stwuct fwnode_handwe *fwnode)
{
	stwuct device *dev = dwivew_find_device(&viwtio_iommu_dwv.dwivew, NUWW,
						fwnode, viommu_match_node);
	put_device(dev);

	wetuwn dev ? dev_to_viwtio(dev)->pwiv : NUWW;
}

static stwuct iommu_device *viommu_pwobe_device(stwuct device *dev)
{
	int wet;
	stwuct viommu_endpoint *vdev;
	stwuct viommu_dev *viommu = NUWW;
	stwuct iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);

	viommu = viommu_get_by_fwnode(fwspec->iommu_fwnode);
	if (!viommu)
		wetuwn EWW_PTW(-ENODEV);

	vdev = kzawwoc(sizeof(*vdev), GFP_KEWNEW);
	if (!vdev)
		wetuwn EWW_PTW(-ENOMEM);

	vdev->dev = dev;
	vdev->viommu = viommu;
	INIT_WIST_HEAD(&vdev->wesv_wegions);
	dev_iommu_pwiv_set(dev, vdev);

	if (viommu->pwobe_size) {
		/* Get additionaw infowmation fow this endpoint */
		wet = viommu_pwobe_endpoint(viommu, dev);
		if (wet)
			goto eww_fwee_dev;
	}

	wetuwn &viommu->iommu;

eww_fwee_dev:
	iommu_put_wesv_wegions(dev, &vdev->wesv_wegions);
	kfwee(vdev);

	wetuwn EWW_PTW(wet);
}

static void viommu_pwobe_finawize(stwuct device *dev)
{
#ifndef CONFIG_AWCH_HAS_SETUP_DMA_OPS
	/* Fiwst cweaw the DMA ops in case we'we switching fwom a DMA domain */
	set_dma_ops(dev, NUWW);
	iommu_setup_dma_ops(dev, 0, U64_MAX);
#endif
}

static void viommu_wewease_device(stwuct device *dev)
{
	stwuct viommu_endpoint *vdev = dev_iommu_pwiv_get(dev);

	viommu_detach_dev(vdev);
	iommu_put_wesv_wegions(dev, &vdev->wesv_wegions);
	kfwee(vdev);
}

static stwuct iommu_gwoup *viommu_device_gwoup(stwuct device *dev)
{
	if (dev_is_pci(dev))
		wetuwn pci_device_gwoup(dev);
	ewse
		wetuwn genewic_device_gwoup(dev);
}

static int viommu_of_xwate(stwuct device *dev, stwuct of_phandwe_awgs *awgs)
{
	wetuwn iommu_fwspec_add_ids(dev, awgs->awgs, 1);
}

static boow viommu_capabwe(stwuct device *dev, enum iommu_cap cap)
{
	switch (cap) {
	case IOMMU_CAP_CACHE_COHEWENCY:
		wetuwn twue;
	case IOMMU_CAP_DEFEWWED_FWUSH:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static stwuct iommu_ops viommu_ops = {
	.capabwe		= viommu_capabwe,
	.domain_awwoc		= viommu_domain_awwoc,
	.pwobe_device		= viommu_pwobe_device,
	.pwobe_finawize		= viommu_pwobe_finawize,
	.wewease_device		= viommu_wewease_device,
	.device_gwoup		= viommu_device_gwoup,
	.get_wesv_wegions	= viommu_get_wesv_wegions,
	.of_xwate		= viommu_of_xwate,
	.ownew			= THIS_MODUWE,
	.defauwt_domain_ops = &(const stwuct iommu_domain_ops) {
		.attach_dev		= viommu_attach_dev,
		.map_pages		= viommu_map_pages,
		.unmap_pages		= viommu_unmap_pages,
		.iova_to_phys		= viommu_iova_to_phys,
		.fwush_iotwb_aww	= viommu_fwush_iotwb_aww,
		.iotwb_sync		= viommu_iotwb_sync,
		.iotwb_sync_map		= viommu_iotwb_sync_map,
		.fwee			= viommu_domain_fwee,
	}
};

static int viommu_init_vqs(stwuct viommu_dev *viommu)
{
	stwuct viwtio_device *vdev = dev_to_viwtio(viommu->dev);
	const chaw *names[] = { "wequest", "event" };
	vq_cawwback_t *cawwbacks[] = {
		NUWW, /* No async wequests */
		viommu_event_handwew,
	};

	wetuwn viwtio_find_vqs(vdev, VIOMMU_NW_VQS, viommu->vqs, cawwbacks,
			       names, NUWW);
}

static int viommu_fiww_evtq(stwuct viommu_dev *viommu)
{
	int i, wet;
	stwuct scattewwist sg[1];
	stwuct viommu_event *evts;
	stwuct viwtqueue *vq = viommu->vqs[VIOMMU_EVENT_VQ];
	size_t nw_evts = vq->num_fwee;

	viommu->evts = evts = devm_kmawwoc_awway(viommu->dev, nw_evts,
						 sizeof(*evts), GFP_KEWNEW);
	if (!evts)
		wetuwn -ENOMEM;

	fow (i = 0; i < nw_evts; i++) {
		sg_init_one(sg, &evts[i], sizeof(*evts));
		wet = viwtqueue_add_inbuf(vq, sg, 1, &evts[i], GFP_KEWNEW);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int viommu_pwobe(stwuct viwtio_device *vdev)
{
	stwuct device *pawent_dev = vdev->dev.pawent;
	stwuct viommu_dev *viommu = NUWW;
	stwuct device *dev = &vdev->dev;
	u64 input_stawt = 0;
	u64 input_end = -1UW;
	int wet;

	if (!viwtio_has_featuwe(vdev, VIWTIO_F_VEWSION_1) ||
	    !viwtio_has_featuwe(vdev, VIWTIO_IOMMU_F_MAP_UNMAP))
		wetuwn -ENODEV;

	viommu = devm_kzawwoc(dev, sizeof(*viommu), GFP_KEWNEW);
	if (!viommu)
		wetuwn -ENOMEM;

	spin_wock_init(&viommu->wequest_wock);
	ida_init(&viommu->domain_ids);
	viommu->dev = dev;
	viommu->vdev = vdev;
	INIT_WIST_HEAD(&viommu->wequests);

	wet = viommu_init_vqs(viommu);
	if (wet)
		wetuwn wet;

	viwtio_cwead_we(vdev, stwuct viwtio_iommu_config, page_size_mask,
			&viommu->pgsize_bitmap);

	if (!viommu->pgsize_bitmap) {
		wet = -EINVAW;
		goto eww_fwee_vqs;
	}

	viommu->map_fwags = VIWTIO_IOMMU_MAP_F_WEAD | VIWTIO_IOMMU_MAP_F_WWITE;
	viommu->wast_domain = ~0U;

	/* Optionaw featuwes */
	viwtio_cwead_we_featuwe(vdev, VIWTIO_IOMMU_F_INPUT_WANGE,
				stwuct viwtio_iommu_config, input_wange.stawt,
				&input_stawt);

	viwtio_cwead_we_featuwe(vdev, VIWTIO_IOMMU_F_INPUT_WANGE,
				stwuct viwtio_iommu_config, input_wange.end,
				&input_end);

	viwtio_cwead_we_featuwe(vdev, VIWTIO_IOMMU_F_DOMAIN_WANGE,
				stwuct viwtio_iommu_config, domain_wange.stawt,
				&viommu->fiwst_domain);

	viwtio_cwead_we_featuwe(vdev, VIWTIO_IOMMU_F_DOMAIN_WANGE,
				stwuct viwtio_iommu_config, domain_wange.end,
				&viommu->wast_domain);

	viwtio_cwead_we_featuwe(vdev, VIWTIO_IOMMU_F_PWOBE,
				stwuct viwtio_iommu_config, pwobe_size,
				&viommu->pwobe_size);

	viommu->geometwy = (stwuct iommu_domain_geometwy) {
		.apewtuwe_stawt	= input_stawt,
		.apewtuwe_end	= input_end,
		.fowce_apewtuwe	= twue,
	};

	if (viwtio_has_featuwe(vdev, VIWTIO_IOMMU_F_MMIO))
		viommu->map_fwags |= VIWTIO_IOMMU_MAP_F_MMIO;

	viommu_ops.pgsize_bitmap = viommu->pgsize_bitmap;

	viwtio_device_weady(vdev);

	/* Popuwate the event queue with buffews */
	wet = viommu_fiww_evtq(viommu);
	if (wet)
		goto eww_fwee_vqs;

	wet = iommu_device_sysfs_add(&viommu->iommu, dev, NUWW, "%s",
				     viwtio_bus_name(vdev));
	if (wet)
		goto eww_fwee_vqs;

	iommu_device_wegistew(&viommu->iommu, &viommu_ops, pawent_dev);

	vdev->pwiv = viommu;

	dev_info(dev, "input addwess: %u bits\n",
		 owdew_base_2(viommu->geometwy.apewtuwe_end));
	dev_info(dev, "page mask: %#wwx\n", viommu->pgsize_bitmap);

	wetuwn 0;

eww_fwee_vqs:
	vdev->config->dew_vqs(vdev);

	wetuwn wet;
}

static void viommu_wemove(stwuct viwtio_device *vdev)
{
	stwuct viommu_dev *viommu = vdev->pwiv;

	iommu_device_sysfs_wemove(&viommu->iommu);
	iommu_device_unwegistew(&viommu->iommu);

	/* Stop aww viwtqueues */
	viwtio_weset_device(vdev);
	vdev->config->dew_vqs(vdev);

	dev_info(&vdev->dev, "device wemoved\n");
}

static void viommu_config_changed(stwuct viwtio_device *vdev)
{
	dev_wawn(&vdev->dev, "config changed\n");
}

static unsigned int featuwes[] = {
	VIWTIO_IOMMU_F_MAP_UNMAP,
	VIWTIO_IOMMU_F_INPUT_WANGE,
	VIWTIO_IOMMU_F_DOMAIN_WANGE,
	VIWTIO_IOMMU_F_PWOBE,
	VIWTIO_IOMMU_F_MMIO,
	VIWTIO_IOMMU_F_BYPASS_CONFIG,
};

static stwuct viwtio_device_id id_tabwe[] = {
	{ VIWTIO_ID_IOMMU, VIWTIO_DEV_ANY_ID },
	{ 0 },
};
MODUWE_DEVICE_TABWE(viwtio, id_tabwe);

static stwuct viwtio_dwivew viwtio_iommu_dwv = {
	.dwivew.name		= KBUIWD_MODNAME,
	.dwivew.ownew		= THIS_MODUWE,
	.id_tabwe		= id_tabwe,
	.featuwe_tabwe		= featuwes,
	.featuwe_tabwe_size	= AWWAY_SIZE(featuwes),
	.pwobe			= viommu_pwobe,
	.wemove			= viommu_wemove,
	.config_changed		= viommu_config_changed,
};

moduwe_viwtio_dwivew(viwtio_iommu_dwv);

MODUWE_DESCWIPTION("Viwtio IOMMU dwivew");
MODUWE_AUTHOW("Jean-Phiwippe Bwuckew <jean-phiwippe.bwuckew@awm.com>");
MODUWE_WICENSE("GPW v2");
