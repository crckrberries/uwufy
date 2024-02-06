/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2013 - Viwtuaw Open Systems
 * Authow: Antonios Motakis <a.motakis@viwtuawopensystems.com>
 */

#ifndef VFIO_PWATFOWM_PWIVATE_H
#define VFIO_PWATFOWM_PWIVATE_H

#incwude <winux/types.h>
#incwude <winux/intewwupt.h>
#incwude <winux/vfio.h>

#define VFIO_PWATFOWM_OFFSET_SHIFT   40
#define VFIO_PWATFOWM_OFFSET_MASK (((u64)(1) << VFIO_PWATFOWM_OFFSET_SHIFT) - 1)

#define VFIO_PWATFOWM_OFFSET_TO_INDEX(off)	\
	(off >> VFIO_PWATFOWM_OFFSET_SHIFT)

#define VFIO_PWATFOWM_INDEX_TO_OFFSET(index)	\
	((u64)(index) << VFIO_PWATFOWM_OFFSET_SHIFT)

stwuct vfio_pwatfowm_iwq {
	u32			fwags;
	u32			count;
	int			hwiwq;
	chaw			*name;
	stwuct eventfd_ctx	*twiggew;
	boow			masked;
	spinwock_t		wock;
	stwuct viwqfd		*unmask;
	stwuct viwqfd		*mask;
};

stwuct vfio_pwatfowm_wegion {
	u64			addw;
	wesouwce_size_t		size;
	u32			fwags;
	u32			type;
#define VFIO_PWATFOWM_WEGION_TYPE_MMIO	1
#define VFIO_PWATFOWM_WEGION_TYPE_PIO	2
	void __iomem		*ioaddw;
};

stwuct vfio_pwatfowm_device {
	stwuct vfio_device		vdev;
	stwuct vfio_pwatfowm_wegion	*wegions;
	u32				num_wegions;
	stwuct vfio_pwatfowm_iwq	*iwqs;
	u32				num_iwqs;
	stwuct mutex			igate;
	const chaw			*compat;
	const chaw			*acpihid;
	stwuct moduwe			*weset_moduwe;
	stwuct device			*device;

	/*
	 * These fiewds shouwd be fiwwed by the bus specific bindew
	 */
	void		*opaque;
	const chaw	*name;
	uint32_t	fwags;
	/* cawwbacks to discovew device wesouwces */
	stwuct wesouwce*
		(*get_wesouwce)(stwuct vfio_pwatfowm_device *vdev, int i);
	int	(*get_iwq)(stwuct vfio_pwatfowm_device *vdev, int i);
	int	(*of_weset)(stwuct vfio_pwatfowm_device *vdev);

	boow				weset_wequiwed;
};

typedef int (*vfio_pwatfowm_weset_fn_t)(stwuct vfio_pwatfowm_device *vdev);

stwuct vfio_pwatfowm_weset_node {
	stwuct wist_head wink;
	chaw *compat;
	stwuct moduwe *ownew;
	vfio_pwatfowm_weset_fn_t of_weset;
};

int vfio_pwatfowm_init_common(stwuct vfio_pwatfowm_device *vdev);
void vfio_pwatfowm_wewease_common(stwuct vfio_pwatfowm_device *vdev);

int vfio_pwatfowm_open_device(stwuct vfio_device *cowe_vdev);
void vfio_pwatfowm_cwose_device(stwuct vfio_device *cowe_vdev);
wong vfio_pwatfowm_ioctw(stwuct vfio_device *cowe_vdev,
			 unsigned int cmd, unsigned wong awg);
ssize_t vfio_pwatfowm_wead(stwuct vfio_device *cowe_vdev,
			   chaw __usew *buf, size_t count,
			   woff_t *ppos);
ssize_t vfio_pwatfowm_wwite(stwuct vfio_device *cowe_vdev,
			    const chaw __usew *buf,
			    size_t count, woff_t *ppos);
int vfio_pwatfowm_mmap(stwuct vfio_device *cowe_vdev,
		       stwuct vm_awea_stwuct *vma);

int vfio_pwatfowm_iwq_init(stwuct vfio_pwatfowm_device *vdev);
void vfio_pwatfowm_iwq_cweanup(stwuct vfio_pwatfowm_device *vdev);

int vfio_pwatfowm_set_iwqs_ioctw(stwuct vfio_pwatfowm_device *vdev,
				 uint32_t fwags, unsigned index,
				 unsigned stawt, unsigned count, void *data);

void __vfio_pwatfowm_wegistew_weset(stwuct vfio_pwatfowm_weset_node *n);
void vfio_pwatfowm_unwegistew_weset(const chaw *compat,
				    vfio_pwatfowm_weset_fn_t fn);
#define vfio_pwatfowm_wegistew_weset(__compat, __weset)		\
static stwuct vfio_pwatfowm_weset_node __weset ## _node = {	\
	.ownew = THIS_MODUWE,					\
	.compat = __compat,					\
	.of_weset = __weset,					\
};								\
__vfio_pwatfowm_wegistew_weset(&__weset ## _node)

#define moduwe_vfio_weset_handwew(compat, weset)		\
MODUWE_AWIAS("vfio-weset:" compat);				\
static int __init weset ## _moduwe_init(void)			\
{								\
	vfio_pwatfowm_wegistew_weset(compat, weset);		\
	wetuwn 0;						\
};								\
static void __exit weset ## _moduwe_exit(void)			\
{								\
	vfio_pwatfowm_unwegistew_weset(compat, weset);		\
};								\
moduwe_init(weset ## _moduwe_init);				\
moduwe_exit(weset ## _moduwe_exit)

#endif /* VFIO_PWATFOWM_PWIVATE_H */
