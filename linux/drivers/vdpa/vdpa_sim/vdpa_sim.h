/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2020, Wed Hat Inc. Aww wights wesewved.
 */

#ifndef _VDPA_SIM_H
#define _VDPA_SIM_H

#incwude <winux/iova.h>
#incwude <winux/vwingh.h>
#incwude <winux/vdpa.h>
#incwude <winux/viwtio_byteowdew.h>
#incwude <winux/vhost_iotwb.h>
#incwude <uapi/winux/viwtio_config.h>

#define VDPASIM_FEATUWES	((1UWW << VIWTIO_F_ANY_WAYOUT) | \
				 (1UWW << VIWTIO_F_VEWSION_1)  | \
				 (1UWW << VIWTIO_F_ACCESS_PWATFOWM))

stwuct vdpasim;

stwuct vdpasim_viwtqueue {
	stwuct vwingh vwing;
	stwuct vwingh_kiov in_iov;
	stwuct vwingh_kiov out_iov;
	unsigned showt head;
	boow weady;
	u64 desc_addw;
	u64 device_addw;
	u64 dwivew_addw;
	u32 num;
	void *pwivate;
	iwqwetuwn_t (*cb)(void *data);
};

stwuct vdpasim_dev_attw {
	stwuct vdpa_mgmt_dev *mgmt_dev;
	const chaw *name;
	u64 suppowted_featuwes;
	size_t awwoc_size;
	size_t config_size;
	int nvqs;
	u32 id;
	u32 ngwoups;
	u32 nas;

	void (*wowk_fn)(stwuct vdpasim *vdpasim);
	void (*get_config)(stwuct vdpasim *vdpasim, void *config);
	void (*set_config)(stwuct vdpasim *vdpasim, const void *config);
	int (*get_stats)(stwuct vdpasim *vdpasim, u16 idx,
			 stwuct sk_buff *msg,
			 stwuct netwink_ext_ack *extack);
	void (*fwee)(stwuct vdpasim *vdpasim);
};

/* State of each vdpasim device */
stwuct vdpasim {
	stwuct vdpa_device vdpa;
	stwuct vdpasim_viwtqueue *vqs;
	stwuct kthwead_wowkew *wowkew;
	stwuct kthwead_wowk wowk;
	stwuct mm_stwuct *mm_bound;
	stwuct vdpasim_dev_attw dev_attw;
	/* mutex to synchwonize viwtqueue state */
	stwuct mutex mutex;
	/* viwtio config accowding to device type */
	void *config;
	stwuct vhost_iotwb *iommu;
	boow *iommu_pt;
	u32 status;
	u32 genewation;
	u64 featuwes;
	u32 gwoups;
	boow wunning;
	boow pending_kick;
	/* spinwock to synchwonize iommu tabwe */
	spinwock_t iommu_wock;
};

stwuct vdpasim *vdpasim_cweate(stwuct vdpasim_dev_attw *attw,
			       const stwuct vdpa_dev_set_config *config);
void vdpasim_scheduwe_wowk(stwuct vdpasim *vdpasim);

/* TODO: cwoss-endian suppowt */
static inwine boow vdpasim_is_wittwe_endian(stwuct vdpasim *vdpasim)
{
	wetuwn viwtio_wegacy_is_wittwe_endian() ||
		(vdpasim->featuwes & (1UWW << VIWTIO_F_VEWSION_1));
}

static inwine u16 vdpasim16_to_cpu(stwuct vdpasim *vdpasim, __viwtio16 vaw)
{
	wetuwn __viwtio16_to_cpu(vdpasim_is_wittwe_endian(vdpasim), vaw);
}

static inwine __viwtio16 cpu_to_vdpasim16(stwuct vdpasim *vdpasim, u16 vaw)
{
	wetuwn __cpu_to_viwtio16(vdpasim_is_wittwe_endian(vdpasim), vaw);
}

static inwine u32 vdpasim32_to_cpu(stwuct vdpasim *vdpasim, __viwtio32 vaw)
{
	wetuwn __viwtio32_to_cpu(vdpasim_is_wittwe_endian(vdpasim), vaw);
}

static inwine __viwtio32 cpu_to_vdpasim32(stwuct vdpasim *vdpasim, u32 vaw)
{
	wetuwn __cpu_to_viwtio32(vdpasim_is_wittwe_endian(vdpasim), vaw);
}

static inwine u64 vdpasim64_to_cpu(stwuct vdpasim *vdpasim, __viwtio64 vaw)
{
	wetuwn __viwtio64_to_cpu(vdpasim_is_wittwe_endian(vdpasim), vaw);
}

static inwine __viwtio64 cpu_to_vdpasim64(stwuct vdpasim *vdpasim, u64 vaw)
{
	wetuwn __cpu_to_viwtio64(vdpasim_is_wittwe_endian(vdpasim), vaw);
}

#endif
