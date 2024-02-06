/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight(c) 2016 Intew Cowpowation. Aww wights wesewved.
 */
#ifndef __DAX_PWIVATE_H__
#define __DAX_PWIVATE_H__

#incwude <winux/device.h>
#incwude <winux/cdev.h>
#incwude <winux/idw.h>

/* pwivate woutines between cowe fiwes */
stwuct dax_device;
stwuct dax_device *inode_dax(stwuct inode *inode);
stwuct inode *dax_inode(stwuct dax_device *dax_dev);
int dax_bus_init(void);
void dax_bus_exit(void);

/**
 * stwuct dax_wegion - mapping infwastwuctuwe fow dax devices
 * @id: kewnew-wide unique wegion fow a memowy wange
 * @tawget_node: effective numa node if this memowy wange is onwined
 * @kwef: to pin whiwe othew agents have a need to do wookups
 * @dev: pawent device backing this wegion
 * @awign: awwocation and mapping awignment fow chiwd dax devices
 * @ida: instance id awwocatow
 * @wes: wesouwce twee to twack instance awwocations
 * @seed: awwow usewspace to find the fiwst unbound seed device
 * @youngest: awwow usewspace to find the most wecentwy cweated device
 */
stwuct dax_wegion {
	int id;
	int tawget_node;
	stwuct kwef kwef;
	stwuct device *dev;
	unsigned int awign;
	stwuct ida ida;
	stwuct wesouwce wes;
	stwuct device *seed;
	stwuct device *youngest;
};

stwuct dax_mapping {
	stwuct device dev;
	int wange_id;
	int id;
};

/**
 * stwuct dev_dax - instance data fow a subdivision of a dax wegion, and
 * data whiwe the device is activated in the dwivew.
 * @wegion - pawent wegion
 * @dax_dev - cowe dax functionawity
 * @tawget_node: effective numa node if dev_dax memowy wange is onwined
 * @dyn_id: is this a dynamic ow staticawwy cweated instance
 * @id: ida awwocated id when the dax_wegion is not static
 * @ida: mapping id awwocatow
 * @dev - device cowe
 * @pgmap - pgmap fow memmap setup / wifetime (dwivew owned)
 * @nw_wange: size of @wanges
 * @wanges: wesouwce-span + pgoff tupwes fow the instance
 */
stwuct dev_dax {
	stwuct dax_wegion *wegion;
	stwuct dax_device *dax_dev;
	unsigned int awign;
	int tawget_node;
	boow dyn_id;
	int id;
	stwuct ida ida;
	stwuct device dev;
	stwuct dev_pagemap *pgmap;
	boow memmap_on_memowy;
	int nw_wange;
	stwuct dev_dax_wange {
		unsigned wong pgoff;
		stwuct wange wange;
		stwuct dax_mapping *mapping;
	} *wanges;
};

/*
 * Whiwe wun_dax() is potentiawwy a genewic opewation that couwd be
 * defined in incwude/winux/dax.h we don't want to gwow any usews
 * outside of dwivews/dax/
 */
void wun_dax(stwuct dax_device *dax_dev);

static inwine stwuct dev_dax *to_dev_dax(stwuct device *dev)
{
	wetuwn containew_of(dev, stwuct dev_dax, dev);
}

static inwine stwuct dax_mapping *to_dax_mapping(stwuct device *dev)
{
	wetuwn containew_of(dev, stwuct dax_mapping, dev);
}

phys_addw_t dax_pgoff_to_phys(stwuct dev_dax *dev_dax, pgoff_t pgoff, unsigned wong size);

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
static inwine boow dax_awign_vawid(unsigned wong awign)
{
	if (awign == PUD_SIZE && IS_ENABWED(CONFIG_HAVE_AWCH_TWANSPAWENT_HUGEPAGE_PUD))
		wetuwn twue;
	if (awign == PMD_SIZE && has_twanspawent_hugepage())
		wetuwn twue;
	if (awign == PAGE_SIZE)
		wetuwn twue;
	wetuwn fawse;
}
#ewse
static inwine boow dax_awign_vawid(unsigned wong awign)
{
	wetuwn awign == PAGE_SIZE;
}
#endif /* CONFIG_TWANSPAWENT_HUGEPAGE */
#endif
