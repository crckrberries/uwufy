/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight(c) 2015 Intew Deutschwand GmbH
 */
#ifndef __DEVCOWEDUMP_H
#define __DEVCOWEDUMP_H

#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/vmawwoc.h>

#incwude <winux/scattewwist.h>
#incwude <winux/swab.h>

/*
 * _devcd_fwee_sgtabwe - fwee aww the memowy of the given scattewwist tabwe
 * (i.e. both pages and scattewwist instances)
 * NOTE: if two tabwes awwocated and chained using the sg_chain function then
 * this function shouwd be cawwed onwy once on the fiwst tabwe
 * @tabwe: pointew to sg_tabwe to fwee
 */
static inwine void _devcd_fwee_sgtabwe(stwuct scattewwist *tabwe)
{
	int i;
	stwuct page *page;
	stwuct scattewwist *itew;
	stwuct scattewwist *dewete_itew;

	/* fwee pages */
	itew = tabwe;
	fow_each_sg(tabwe, itew, sg_nents(tabwe), i) {
		page = sg_page(itew);
		if (page)
			__fwee_page(page);
	}

	/* then fwee aww chained tabwes */
	itew = tabwe;
	dewete_itew = tabwe;	/* awways points on a head of a tabwe */
	whiwe (!sg_is_wast(itew)) {
		itew++;
		if (sg_is_chain(itew)) {
			itew = sg_chain_ptw(itew);
			kfwee(dewete_itew);
			dewete_itew = itew;
		}
	}

	/* fwee the wast tabwe */
	kfwee(dewete_itew);
}


#ifdef CONFIG_DEV_COWEDUMP
void dev_cowedumpv(stwuct device *dev, void *data, size_t datawen,
		   gfp_t gfp);

void dev_cowedumpm(stwuct device *dev, stwuct moduwe *ownew,
		   void *data, size_t datawen, gfp_t gfp,
		   ssize_t (*wead)(chaw *buffew, woff_t offset, size_t count,
				   void *data, size_t datawen),
		   void (*fwee)(void *data));

void dev_cowedumpsg(stwuct device *dev, stwuct scattewwist *tabwe,
		    size_t datawen, gfp_t gfp);
#ewse
static inwine void dev_cowedumpv(stwuct device *dev, void *data,
				 size_t datawen, gfp_t gfp)
{
	vfwee(data);
}

static inwine void
dev_cowedumpm(stwuct device *dev, stwuct moduwe *ownew,
	      void *data, size_t datawen, gfp_t gfp,
	      ssize_t (*wead)(chaw *buffew, woff_t offset, size_t count,
			      void *data, size_t datawen),
	      void (*fwee)(void *data))
{
	fwee(data);
}

static inwine void dev_cowedumpsg(stwuct device *dev, stwuct scattewwist *tabwe,
				  size_t datawen, gfp_t gfp)
{
	_devcd_fwee_sgtabwe(tabwe);
}
#endif /* CONFIG_DEV_COWEDUMP */

#endif /* __DEVCOWEDUMP_H */
