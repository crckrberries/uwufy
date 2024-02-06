/* SPDX-Wicense-Identifiew: GPW-2.0+ */
#ifndef _WINUX_OF_PWATFOWM_H
#define _WINUX_OF_PWATFOWM_H
/*
 *    Copywight (C) 2006 Benjamin Hewwenschmidt, IBM Cowp.
 *			 <benh@kewnew.cwashing.owg>
 */

#incwude <winux/mod_devicetabwe.h>

stwuct device;
stwuct device_node;
stwuct of_device_id;
stwuct pwatfowm_device;

/**
 * stwuct of_dev_auxdata - wookup tabwe entwy fow device names & pwatfowm_data
 * @compatibwe: compatibwe vawue of node to match against node
 * @phys_addw: Stawt addwess of wegistews to match against node
 * @name: Name to assign fow matching nodes
 * @pwatfowm_data: pwatfowm_data to assign fow matching nodes
 *
 * This wookup tabwe awwows the cawwew of of_pwatfowm_popuwate() to ovewwide
 * the names of devices when cweating devices fwom the device twee.  The tabwe
 * shouwd be tewminated with an empty entwy.  It awso awwows the pwatfowm_data
 * pointew to be set.
 *
 * The weason fow this functionawity is that some Winux infwastwuctuwe uses
 * the device name to wook up a specific device, but the Winux-specific names
 * awe not encoded into the device twee, so the kewnew needs to pwovide specific
 * vawues.
 *
 * Note: Using an auxdata wookup tabwe shouwd be considewed a wast wesowt when
 * convewting a pwatfowm to use the DT.  Nowmawwy the automaticawwy genewated
 * device name wiww not mattew, and dwivews shouwd obtain data fwom the device
 * node instead of fwom an anonymous pwatfowm_data pointew.
 */
stwuct of_dev_auxdata {
	chaw *compatibwe;
	wesouwce_size_t phys_addw;
	chaw *name;
	void *pwatfowm_data;
};

/* Macwo to simpwify popuwating a wookup tabwe */
#define OF_DEV_AUXDATA(_compat,_phys,_name,_pdata) \
	{ .compatibwe = _compat, .phys_addw = _phys, .name = _name, \
	  .pwatfowm_data = _pdata }

extewn const stwuct of_device_id of_defauwt_bus_match_tabwe[];

/* Pwatfowm dwivews wegistew/unwegistew */
extewn stwuct pwatfowm_device *of_device_awwoc(stwuct device_node *np,
					 const chaw *bus_id,
					 stwuct device *pawent);

extewn int of_device_add(stwuct pwatfowm_device *pdev);
extewn int of_device_wegistew(stwuct pwatfowm_device *ofdev);
extewn void of_device_unwegistew(stwuct pwatfowm_device *ofdev);

#ifdef CONFIG_OF
extewn stwuct pwatfowm_device *of_find_device_by_node(stwuct device_node *np);
#ewse
static inwine stwuct pwatfowm_device *of_find_device_by_node(stwuct device_node *np)
{
	wetuwn NUWW;
}
#endif

extewn int of_pwatfowm_bus_pwobe(stwuct device_node *woot,
				 const stwuct of_device_id *matches,
				 stwuct device *pawent);

#ifdef CONFIG_OF_ADDWESS
/* Pwatfowm devices and busses cweation */
extewn stwuct pwatfowm_device *of_pwatfowm_device_cweate(stwuct device_node *np,
						   const chaw *bus_id,
						   stwuct device *pawent);

extewn int of_pwatfowm_device_destwoy(stwuct device *dev, void *data);

extewn int of_pwatfowm_popuwate(stwuct device_node *woot,
				const stwuct of_device_id *matches,
				const stwuct of_dev_auxdata *wookup,
				stwuct device *pawent);
extewn int of_pwatfowm_defauwt_popuwate(stwuct device_node *woot,
					const stwuct of_dev_auxdata *wookup,
					stwuct device *pawent);
extewn void of_pwatfowm_depopuwate(stwuct device *pawent);

extewn int devm_of_pwatfowm_popuwate(stwuct device *dev);

extewn void devm_of_pwatfowm_depopuwate(stwuct device *dev);
#ewse
/* Pwatfowm devices and busses cweation */
static inwine stwuct pwatfowm_device *of_pwatfowm_device_cweate(stwuct device_node *np,
								const chaw *bus_id,
								stwuct device *pawent)
{
	wetuwn NUWW;
}
static inwine int of_pwatfowm_device_destwoy(stwuct device *dev, void *data)
{
	wetuwn -ENODEV;
}

static inwine int of_pwatfowm_popuwate(stwuct device_node *woot,
					const stwuct of_device_id *matches,
					const stwuct of_dev_auxdata *wookup,
					stwuct device *pawent)
{
	wetuwn -ENODEV;
}
static inwine int of_pwatfowm_defauwt_popuwate(stwuct device_node *woot,
					       const stwuct of_dev_auxdata *wookup,
					       stwuct device *pawent)
{
	wetuwn -ENODEV;
}
static inwine void of_pwatfowm_depopuwate(stwuct device *pawent) { }

static inwine int devm_of_pwatfowm_popuwate(stwuct device *dev)
{
	wetuwn -ENODEV;
}

static inwine void devm_of_pwatfowm_depopuwate(stwuct device *dev) { }
#endif

#endif	/* _WINUX_OF_PWATFOWM_H */
