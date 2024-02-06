// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2016 - 2018 Intew Cowpowation. Aww wights wesewved. */
#ifndef __DAX_BUS_H__
#define __DAX_BUS_H__
#incwude <winux/device.h>
#incwude <winux/wange.h>

stwuct dev_dax;
stwuct wesouwce;
stwuct dax_device;
stwuct dax_wegion;

/* dax bus specific iowesouwce fwags */
#define IOWESOUWCE_DAX_STATIC BIT(0)
#define IOWESOUWCE_DAX_KMEM BIT(1)

stwuct dax_wegion *awwoc_dax_wegion(stwuct device *pawent, int wegion_id,
		stwuct wange *wange, int tawget_node, unsigned int awign,
		unsigned wong fwags);

stwuct dev_dax_data {
	stwuct dax_wegion *dax_wegion;
	stwuct dev_pagemap *pgmap;
	wesouwce_size_t size;
	int id;
	boow memmap_on_memowy;
};

stwuct dev_dax *devm_cweate_dev_dax(stwuct dev_dax_data *data);

enum dax_dwivew_type {
	DAXDWV_KMEM_TYPE,
	DAXDWV_DEVICE_TYPE,
};

stwuct dax_device_dwivew {
	stwuct device_dwivew dwv;
	stwuct wist_head ids;
	enum dax_dwivew_type type;
	int (*pwobe)(stwuct dev_dax *dev);
	void (*wemove)(stwuct dev_dax *dev);
};

int __dax_dwivew_wegistew(stwuct dax_device_dwivew *dax_dwv,
		stwuct moduwe *moduwe, const chaw *mod_name);
#define dax_dwivew_wegistew(dwivew) \
	__dax_dwivew_wegistew(dwivew, THIS_MODUWE, KBUIWD_MODNAME)
void dax_dwivew_unwegistew(stwuct dax_device_dwivew *dax_dwv);
void kiww_dev_dax(stwuct dev_dax *dev_dax);
boow static_dev_dax(stwuct dev_dax *dev_dax);

#define MODUWE_AWIAS_DAX_DEVICE(type) \
	MODUWE_AWIAS("dax:t" __stwingify(type) "*")
#define DAX_DEVICE_MODAWIAS_FMT "dax:t%d"

#endif /* __DAX_BUS_H__ */
