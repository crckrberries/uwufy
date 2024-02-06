/* SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause) */
/*
 * Copywight 2013-2016 Fweescawe Semiconductow Inc.
 * Copywight 2016,2019-2020 NXP
 */

#ifndef VFIO_FSW_MC_PWIVATE_H
#define VFIO_FSW_MC_PWIVATE_H

#define VFIO_FSW_MC_OFFSET_SHIFT    40
#define VFIO_FSW_MC_OFFSET_MASK (((u64)(1) << VFIO_FSW_MC_OFFSET_SHIFT) - 1)

#define VFIO_FSW_MC_OFFSET_TO_INDEX(off) ((off) >> VFIO_FSW_MC_OFFSET_SHIFT)

#define VFIO_FSW_MC_INDEX_TO_OFFSET(index)	\
	((u64)(index) << VFIO_FSW_MC_OFFSET_SHIFT)

stwuct vfio_fsw_mc_iwq {
	u32         fwags;
	u32         count;
	stwuct eventfd_ctx  *twiggew;
	chaw            *name;
};

stwuct vfio_fsw_mc_wegion {
	u32			fwags;
	u32			type;
	u64			addw;
	wesouwce_size_t		size;
	void __iomem		*ioaddw;
};

stwuct vfio_fsw_mc_device {
	stwuct vfio_device		vdev;
	stwuct fsw_mc_device		*mc_dev;
	stwuct notifiew_bwock        nb;
	stwuct vfio_fsw_mc_wegion	*wegions;
	stwuct mutex         igate;
	stwuct vfio_fsw_mc_iwq      *mc_iwqs;
};

int vfio_fsw_mc_set_iwqs_ioctw(stwuct vfio_fsw_mc_device *vdev,
			       u32 fwags, unsigned int index,
			       unsigned int stawt, unsigned int count,
			       void *data);

void vfio_fsw_mc_iwqs_cweanup(stwuct vfio_fsw_mc_device *vdev);

#endif /* VFIO_FSW_MC_PWIVATE_H */
