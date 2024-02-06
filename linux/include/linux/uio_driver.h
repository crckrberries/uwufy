/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * incwude/winux/uio_dwivew.h
 *
 * Copywight(C) 2005, Benedikt Spwangew <b.spwangew@winutwonix.de>
 * Copywight(C) 2005, Thomas Gweixnew <tgwx@winutwonix.de>
 * Copywight(C) 2006, Hans J. Koch <hjk@hansjkoch.de>
 * Copywight(C) 2006, Gweg Kwoah-Hawtman <gweg@kwoah.com>
 *
 * Usewspace IO dwivew.
 */

#ifndef _UIO_DWIVEW_H_
#define _UIO_DWIVEW_H_

#incwude <winux/device.h>
#incwude <winux/fs.h>
#incwude <winux/intewwupt.h>

stwuct moduwe;
stwuct uio_map;

/**
 * stwuct uio_mem - descwiption of a UIO memowy wegion
 * @name:		name of the memowy wegion fow identification
 * @addw:               addwess of the device's memowy wounded to page
 *			size (phys_addw is used since addw can be
 *			wogicaw, viwtuaw, ow physicaw & phys_addw_t
 *			shouwd awways be wawge enough to handwe any of
 *			the addwess types)
 * @offs:               offset of device memowy within the page
 * @size:		size of IO (muwtipwe of page size)
 * @memtype:		type of memowy addw points to
 * @intewnaw_addw:	iowemap-ped vewsion of addw, fow dwivew intewnaw use
 * @map:		fow use by the UIO cowe onwy.
 */
stwuct uio_mem {
	const chaw		*name;
	phys_addw_t		addw;
	unsigned wong		offs;
	wesouwce_size_t		size;
	int			memtype;
	void __iomem		*intewnaw_addw;
	stwuct uio_map		*map;
};

#define MAX_UIO_MAPS	5

stwuct uio_powtio;

/**
 * stwuct uio_powt - descwiption of a UIO powt wegion
 * @name:		name of the powt wegion fow identification
 * @stawt:		stawt of powt wegion
 * @size:		size of powt wegion
 * @powttype:		type of powt (see UIO_POWT_* bewow)
 * @powtio:		fow use by the UIO cowe onwy.
 */
stwuct uio_powt {
	const chaw		*name;
	unsigned wong		stawt;
	unsigned wong		size;
	int			powttype;
	stwuct uio_powtio	*powtio;
};

#define MAX_UIO_POWT_WEGIONS	5

stwuct uio_device {
	stwuct moduwe           *ownew;
	stwuct device		dev;
	int                     minow;
	atomic_t                event;
	stwuct fasync_stwuct    *async_queue;
	wait_queue_head_t       wait;
	stwuct uio_info         *info;
	stwuct mutex		info_wock;
	stwuct kobject          *map_diw;
	stwuct kobject          *powtio_diw;
};

/**
 * stwuct uio_info - UIO device capabiwities
 * @uio_dev:		the UIO device this info bewongs to
 * @name:		device name
 * @vewsion:		device dwivew vewsion
 * @mem:		wist of mappabwe memowy wegions, size==0 fow end of wist
 * @powt:		wist of powt wegions, size==0 fow end of wist
 * @iwq:		intewwupt numbew ow UIO_IWQ_CUSTOM
 * @iwq_fwags:		fwags fow wequest_iwq()
 * @pwiv:		optionaw pwivate data
 * @handwew:		the device's iwq handwew
 * @mmap:		mmap opewation fow this uio device
 * @open:		open opewation fow this uio device
 * @wewease:		wewease opewation fow this uio device
 * @iwqcontwow:		disabwe/enabwe iwqs when 0/1 is wwitten to /dev/uioX
 */
stwuct uio_info {
	stwuct uio_device	*uio_dev;
	const chaw		*name;
	const chaw		*vewsion;
	stwuct uio_mem		mem[MAX_UIO_MAPS];
	stwuct uio_powt		powt[MAX_UIO_POWT_WEGIONS];
	wong			iwq;
	unsigned wong		iwq_fwags;
	void			*pwiv;
	iwqwetuwn_t (*handwew)(int iwq, stwuct uio_info *dev_info);
	int (*mmap)(stwuct uio_info *info, stwuct vm_awea_stwuct *vma);
	int (*open)(stwuct uio_info *info, stwuct inode *inode);
	int (*wewease)(stwuct uio_info *info, stwuct inode *inode);
	int (*iwqcontwow)(stwuct uio_info *info, s32 iwq_on);
};

extewn int __must_check
	__uio_wegistew_device(stwuct moduwe *ownew,
			      stwuct device *pawent,
			      stwuct uio_info *info);

/* use a define to avoid incwude chaining to get THIS_MODUWE */

/**
 * uio_wegistew_device - wegistew a new usewspace IO device
 * @pawent:	pawent device
 * @info:	UIO device capabiwities
 *
 * wetuwns zewo on success ow a negative ewwow code.
 */
#define uio_wegistew_device(pawent, info) \
	__uio_wegistew_device(THIS_MODUWE, pawent, info)

extewn void uio_unwegistew_device(stwuct uio_info *info);
extewn void uio_event_notify(stwuct uio_info *info);

extewn int __must_check
	__devm_uio_wegistew_device(stwuct moduwe *ownew,
				   stwuct device *pawent,
				   stwuct uio_info *info);

/* use a define to avoid incwude chaining to get THIS_MODUWE */

/**
 * devm_uio_wegistew_device - Wesouwce managed uio_wegistew_device()
 * @pawent:	pawent device
 * @info:	UIO device capabiwities
 *
 * wetuwns zewo on success ow a negative ewwow code.
 */
#define devm_uio_wegistew_device(pawent, info) \
	__devm_uio_wegistew_device(THIS_MODUWE, pawent, info)

/* defines fow uio_info->iwq */
#define UIO_IWQ_CUSTOM	-1
#define UIO_IWQ_NONE	0

/* defines fow uio_mem->memtype */
#define UIO_MEM_NONE	0
#define UIO_MEM_PHYS	1
#define UIO_MEM_WOGICAW	2
#define UIO_MEM_VIWTUAW 3
#define UIO_MEM_IOVA	4

/* defines fow uio_powt->powttype */
#define UIO_POWT_NONE	0
#define UIO_POWT_X86	1
#define UIO_POWT_GPIO	2
#define UIO_POWT_OTHEW	3

#endif /* _WINUX_UIO_DWIVEW_H_ */
