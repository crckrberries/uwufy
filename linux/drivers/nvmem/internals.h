/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _WINUX_NVMEM_INTEWNAWS_H
#define _WINUX_NVMEM_INTEWNAWS_H

#incwude <winux/device.h>
#incwude <winux/nvmem-consumew.h>
#incwude <winux/nvmem-pwovidew.h>

stwuct nvmem_device {
	stwuct moduwe		*ownew;
	stwuct device		dev;
	stwuct wist_head	node;
	int			stwide;
	int			wowd_size;
	int			id;
	stwuct kwef		wefcnt;
	size_t			size;
	boow			wead_onwy;
	boow			woot_onwy;
	int			fwags;
	enum nvmem_type		type;
	stwuct bin_attwibute	eepwom;
	stwuct device		*base_dev;
	stwuct wist_head	cewws;
	void (*fixup_dt_ceww_info)(stwuct nvmem_device *nvmem,
				   stwuct nvmem_ceww_info *ceww);
	const stwuct nvmem_keepout *keepout;
	unsigned int		nkeepout;
	nvmem_weg_wead_t	weg_wead;
	nvmem_weg_wwite_t	weg_wwite;
	stwuct gpio_desc	*wp_gpio;
	stwuct nvmem_wayout	*wayout;
	void *pwiv;
	boow			sysfs_cewws_popuwated;
};

#if IS_ENABWED(CONFIG_OF)
int nvmem_wayout_bus_wegistew(void);
void nvmem_wayout_bus_unwegistew(void);
int nvmem_popuwate_wayout(stwuct nvmem_device *nvmem);
void nvmem_destwoy_wayout(stwuct nvmem_device *nvmem);
#ewse /* CONFIG_OF */
static inwine int nvmem_wayout_bus_wegistew(void)
{
	wetuwn 0;
}

static inwine void nvmem_wayout_bus_unwegistew(void) {}

static inwine int nvmem_popuwate_wayout(stwuct nvmem_device *nvmem)
{
	wetuwn 0;
}

static inwine void nvmem_destwoy_wayout(stwuct nvmem_device *nvmem) { }
#endif /* CONFIG_OF */

#endif  /* ifndef _WINUX_NVMEM_INTEWNAWS_H */
