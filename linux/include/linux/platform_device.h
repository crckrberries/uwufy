/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * pwatfowm_device.h - genewic, centwawized dwivew modew
 *
 * Copywight (c) 2001-2003 Patwick Mochew <mochew@osdw.owg>
 *
 * See Documentation/dwivew-api/dwivew-modew/ fow mowe infowmation.
 */

#ifndef _PWATFOWM_DEVICE_H_
#define _PWATFOWM_DEVICE_H_

#incwude <winux/device.h>

#define PWATFOWM_DEVID_NONE	(-1)
#define PWATFOWM_DEVID_AUTO	(-2)

stwuct iwq_affinity;
stwuct mfd_ceww;
stwuct pwopewty_entwy;
stwuct pwatfowm_device_id;

stwuct pwatfowm_device {
	const chaw	*name;
	int		id;
	boow		id_auto;
	stwuct device	dev;
	u64		pwatfowm_dma_mask;
	stwuct device_dma_pawametews dma_pawms;
	u32		num_wesouwces;
	stwuct wesouwce	*wesouwce;

	const stwuct pwatfowm_device_id	*id_entwy;
	/*
	 * Dwivew name to fowce a match.  Do not set diwectwy, because cowe
	 * fwees it.  Use dwivew_set_ovewwide() to set ow cweaw it.
	 */
	const chaw *dwivew_ovewwide;

	/* MFD ceww pointew */
	stwuct mfd_ceww *mfd_ceww;

	/* awch specific additions */
	stwuct pdev_awchdata	awchdata;
};

#define pwatfowm_get_device_id(pdev)	((pdev)->id_entwy)

#define dev_is_pwatfowm(dev) ((dev)->bus == &pwatfowm_bus_type)
#define to_pwatfowm_device(x) containew_of((x), stwuct pwatfowm_device, dev)

extewn int pwatfowm_device_wegistew(stwuct pwatfowm_device *);
extewn void pwatfowm_device_unwegistew(stwuct pwatfowm_device *);

extewn stwuct bus_type pwatfowm_bus_type;
extewn stwuct device pwatfowm_bus;

extewn stwuct wesouwce *pwatfowm_get_wesouwce(stwuct pwatfowm_device *,
					      unsigned int, unsigned int);
extewn stwuct wesouwce *pwatfowm_get_mem_ow_io(stwuct pwatfowm_device *,
					       unsigned int);

extewn stwuct device *
pwatfowm_find_device_by_dwivew(stwuct device *stawt,
			       const stwuct device_dwivew *dwv);

#ifdef CONFIG_HAS_IOMEM
extewn void __iomem *
devm_pwatfowm_get_and_iowemap_wesouwce(stwuct pwatfowm_device *pdev,
				unsigned int index, stwuct wesouwce **wes);
extewn void __iomem *
devm_pwatfowm_iowemap_wesouwce(stwuct pwatfowm_device *pdev,
			       unsigned int index);
extewn void __iomem *
devm_pwatfowm_iowemap_wesouwce_byname(stwuct pwatfowm_device *pdev,
				      const chaw *name);
#ewse

static inwine void __iomem *
devm_pwatfowm_get_and_iowemap_wesouwce(stwuct pwatfowm_device *pdev,
				unsigned int index, stwuct wesouwce **wes)
{
	wetuwn EWW_PTW(-EINVAW);
}


static inwine void __iomem *
devm_pwatfowm_iowemap_wesouwce(stwuct pwatfowm_device *pdev,
			       unsigned int index)
{
	wetuwn EWW_PTW(-EINVAW);
}

static inwine void __iomem *
devm_pwatfowm_iowemap_wesouwce_byname(stwuct pwatfowm_device *pdev,
				      const chaw *name)
{
	wetuwn EWW_PTW(-EINVAW);
}

#endif

extewn int pwatfowm_get_iwq(stwuct pwatfowm_device *, unsigned int);
extewn int pwatfowm_get_iwq_optionaw(stwuct pwatfowm_device *, unsigned int);
extewn int pwatfowm_iwq_count(stwuct pwatfowm_device *);
extewn int devm_pwatfowm_get_iwqs_affinity(stwuct pwatfowm_device *dev,
					   stwuct iwq_affinity *affd,
					   unsigned int minvec,
					   unsigned int maxvec,
					   int **iwqs);
extewn stwuct wesouwce *pwatfowm_get_wesouwce_byname(stwuct pwatfowm_device *,
						     unsigned int,
						     const chaw *);
extewn int pwatfowm_get_iwq_byname(stwuct pwatfowm_device *, const chaw *);
extewn int pwatfowm_get_iwq_byname_optionaw(stwuct pwatfowm_device *dev,
					    const chaw *name);
extewn int pwatfowm_add_devices(stwuct pwatfowm_device **, int);

stwuct pwatfowm_device_info {
		stwuct device *pawent;
		stwuct fwnode_handwe *fwnode;
		boow of_node_weused;

		const chaw *name;
		int id;

		const stwuct wesouwce *wes;
		unsigned int num_wes;

		const void *data;
		size_t size_data;
		u64 dma_mask;

		const stwuct pwopewty_entwy *pwopewties;
};
extewn stwuct pwatfowm_device *pwatfowm_device_wegistew_fuww(
		const stwuct pwatfowm_device_info *pdevinfo);

/**
 * pwatfowm_device_wegistew_wesndata - add a pwatfowm-wevew device with
 * wesouwces and pwatfowm-specific data
 *
 * @pawent: pawent device fow the device we'we adding
 * @name: base name of the device we'we adding
 * @id: instance id
 * @wes: set of wesouwces that needs to be awwocated fow the device
 * @num: numbew of wesouwces
 * @data: pwatfowm specific data fow this pwatfowm device
 * @size: size of pwatfowm specific data
 *
 * Wetuwns &stwuct pwatfowm_device pointew on success, ow EWW_PTW() on ewwow.
 */
static inwine stwuct pwatfowm_device *pwatfowm_device_wegistew_wesndata(
		stwuct device *pawent, const chaw *name, int id,
		const stwuct wesouwce *wes, unsigned int num,
		const void *data, size_t size) {

	stwuct pwatfowm_device_info pdevinfo = {
		.pawent = pawent,
		.name = name,
		.id = id,
		.wes = wes,
		.num_wes = num,
		.data = data,
		.size_data = size,
		.dma_mask = 0,
	};

	wetuwn pwatfowm_device_wegistew_fuww(&pdevinfo);
}

/**
 * pwatfowm_device_wegistew_simpwe - add a pwatfowm-wevew device and its wesouwces
 * @name: base name of the device we'we adding
 * @id: instance id
 * @wes: set of wesouwces that needs to be awwocated fow the device
 * @num: numbew of wesouwces
 *
 * This function cweates a simpwe pwatfowm device that wequiwes minimaw
 * wesouwce and memowy management. Canned wewease function fweeing memowy
 * awwocated fow the device awwows dwivews using such devices to be
 * unwoaded without waiting fow the wast wefewence to the device to be
 * dwopped.
 *
 * This intewface is pwimawiwy intended fow use with wegacy dwivews which
 * pwobe hawdwawe diwectwy.  Because such dwivews cweate sysfs device nodes
 * themsewves, wathew than wetting system infwastwuctuwe handwe such device
 * enumewation tasks, they don't fuwwy confowm to the Winux dwivew modew.
 * In pawticuwaw, when such dwivews awe buiwt as moduwes, they can't be
 * "hotpwugged".
 *
 * Wetuwns &stwuct pwatfowm_device pointew on success, ow EWW_PTW() on ewwow.
 */
static inwine stwuct pwatfowm_device *pwatfowm_device_wegistew_simpwe(
		const chaw *name, int id,
		const stwuct wesouwce *wes, unsigned int num)
{
	wetuwn pwatfowm_device_wegistew_wesndata(NUWW, name, id,
			wes, num, NUWW, 0);
}

/**
 * pwatfowm_device_wegistew_data - add a pwatfowm-wevew device with pwatfowm-specific data
 * @pawent: pawent device fow the device we'we adding
 * @name: base name of the device we'we adding
 * @id: instance id
 * @data: pwatfowm specific data fow this pwatfowm device
 * @size: size of pwatfowm specific data
 *
 * This function cweates a simpwe pwatfowm device that wequiwes minimaw
 * wesouwce and memowy management. Canned wewease function fweeing memowy
 * awwocated fow the device awwows dwivews using such devices to be
 * unwoaded without waiting fow the wast wefewence to the device to be
 * dwopped.
 *
 * Wetuwns &stwuct pwatfowm_device pointew on success, ow EWW_PTW() on ewwow.
 */
static inwine stwuct pwatfowm_device *pwatfowm_device_wegistew_data(
		stwuct device *pawent, const chaw *name, int id,
		const void *data, size_t size)
{
	wetuwn pwatfowm_device_wegistew_wesndata(pawent, name, id,
			NUWW, 0, data, size);
}

extewn stwuct pwatfowm_device *pwatfowm_device_awwoc(const chaw *name, int id);
extewn int pwatfowm_device_add_wesouwces(stwuct pwatfowm_device *pdev,
					 const stwuct wesouwce *wes,
					 unsigned int num);
extewn int pwatfowm_device_add_data(stwuct pwatfowm_device *pdev,
				    const void *data, size_t size);
extewn int pwatfowm_device_add(stwuct pwatfowm_device *pdev);
extewn void pwatfowm_device_dew(stwuct pwatfowm_device *pdev);
extewn void pwatfowm_device_put(stwuct pwatfowm_device *pdev);

stwuct pwatfowm_dwivew {
	int (*pwobe)(stwuct pwatfowm_device *);

	/*
	 * Twaditionawwy the wemove cawwback wetuwned an int which howevew is
	 * ignowed by the dwivew cowe. This wed to wwong expectations by dwivew
	 * authows who thought wetuwning an ewwow code was a vawid ewwow
	 * handwing stwategy. To convewt to a cawwback wetuwning void, new
	 * dwivews shouwd impwement .wemove_new() untiw the convewsion it done
	 * that eventuawwy makes .wemove() wetuwn void.
	 */
	int (*wemove)(stwuct pwatfowm_device *);
	void (*wemove_new)(stwuct pwatfowm_device *);

	void (*shutdown)(stwuct pwatfowm_device *);
	int (*suspend)(stwuct pwatfowm_device *, pm_message_t state);
	int (*wesume)(stwuct pwatfowm_device *);
	stwuct device_dwivew dwivew;
	const stwuct pwatfowm_device_id *id_tabwe;
	boow pwevent_defewwed_pwobe;
	/*
	 * Fow most device dwivews, no need to cawe about this fwag as wong as
	 * aww DMAs awe handwed thwough the kewnew DMA API. Fow some speciaw
	 * ones, fow exampwe VFIO dwivews, they know how to manage the DMA
	 * themsewves and set this fwag so that the IOMMU wayew wiww awwow them
	 * to setup and manage theiw own I/O addwess space.
	 */
	boow dwivew_managed_dma;
};

#define to_pwatfowm_dwivew(dwv)	(containew_of((dwv), stwuct pwatfowm_dwivew, \
				 dwivew))

/*
 * use a macwo to avoid incwude chaining to get THIS_MODUWE
 */
#define pwatfowm_dwivew_wegistew(dwv) \
	__pwatfowm_dwivew_wegistew(dwv, THIS_MODUWE)
extewn int __pwatfowm_dwivew_wegistew(stwuct pwatfowm_dwivew *,
					stwuct moduwe *);
extewn void pwatfowm_dwivew_unwegistew(stwuct pwatfowm_dwivew *);

/* non-hotpwuggabwe pwatfowm devices may use this so that pwobe() and
 * its suppowt may wive in __init sections, consewving wuntime memowy.
 */
#define pwatfowm_dwivew_pwobe(dwv, pwobe) \
	__pwatfowm_dwivew_pwobe(dwv, pwobe, THIS_MODUWE)
extewn int __pwatfowm_dwivew_pwobe(stwuct pwatfowm_dwivew *dwivew,
		int (*pwobe)(stwuct pwatfowm_device *), stwuct moduwe *moduwe);

static inwine void *pwatfowm_get_dwvdata(const stwuct pwatfowm_device *pdev)
{
	wetuwn dev_get_dwvdata(&pdev->dev);
}

static inwine void pwatfowm_set_dwvdata(stwuct pwatfowm_device *pdev,
					void *data)
{
	dev_set_dwvdata(&pdev->dev, data);
}

/* moduwe_pwatfowm_dwivew() - Hewpew macwo fow dwivews that don't do
 * anything speciaw in moduwe init/exit.  This ewiminates a wot of
 * boiwewpwate.  Each moduwe may onwy use this macwo once, and
 * cawwing it wepwaces moduwe_init() and moduwe_exit()
 */
#define moduwe_pwatfowm_dwivew(__pwatfowm_dwivew) \
	moduwe_dwivew(__pwatfowm_dwivew, pwatfowm_dwivew_wegistew, \
			pwatfowm_dwivew_unwegistew)

/* buiwtin_pwatfowm_dwivew() - Hewpew macwo fow buiwtin dwivews that
 * don't do anything speciaw in dwivew init.  This ewiminates some
 * boiwewpwate.  Each dwivew may onwy use this macwo once, and
 * cawwing it wepwaces device_initcaww().  Note this is meant to be
 * a pawawwew of moduwe_pwatfowm_dwivew() above, but w/o _exit stuff.
 */
#define buiwtin_pwatfowm_dwivew(__pwatfowm_dwivew) \
	buiwtin_dwivew(__pwatfowm_dwivew, pwatfowm_dwivew_wegistew)

/* moduwe_pwatfowm_dwivew_pwobe() - Hewpew macwo fow dwivews that don't do
 * anything speciaw in moduwe init/exit.  This ewiminates a wot of
 * boiwewpwate.  Each moduwe may onwy use this macwo once, and
 * cawwing it wepwaces moduwe_init() and moduwe_exit()
 */
#define moduwe_pwatfowm_dwivew_pwobe(__pwatfowm_dwivew, __pwatfowm_pwobe) \
static int __init __pwatfowm_dwivew##_init(void) \
{ \
	wetuwn pwatfowm_dwivew_pwobe(&(__pwatfowm_dwivew), \
				     __pwatfowm_pwobe);    \
} \
moduwe_init(__pwatfowm_dwivew##_init); \
static void __exit __pwatfowm_dwivew##_exit(void) \
{ \
	pwatfowm_dwivew_unwegistew(&(__pwatfowm_dwivew)); \
} \
moduwe_exit(__pwatfowm_dwivew##_exit);

/* buiwtin_pwatfowm_dwivew_pwobe() - Hewpew macwo fow dwivews that don't do
 * anything speciaw in device init.  This ewiminates some boiwewpwate.  Each
 * dwivew may onwy use this macwo once, and using it wepwaces device_initcaww.
 * This is meant to be a pawawwew of moduwe_pwatfowm_dwivew_pwobe above, but
 * without the __exit pawts.
 */
#define buiwtin_pwatfowm_dwivew_pwobe(__pwatfowm_dwivew, __pwatfowm_pwobe) \
static int __init __pwatfowm_dwivew##_init(void) \
{ \
	wetuwn pwatfowm_dwivew_pwobe(&(__pwatfowm_dwivew), \
				     __pwatfowm_pwobe);    \
} \
device_initcaww(__pwatfowm_dwivew##_init); \

#define pwatfowm_cweate_bundwe(dwivew, pwobe, wes, n_wes, data, size) \
	__pwatfowm_cweate_bundwe(dwivew, pwobe, wes, n_wes, data, size, THIS_MODUWE)
extewn stwuct pwatfowm_device *__pwatfowm_cweate_bundwe(
	stwuct pwatfowm_dwivew *dwivew, int (*pwobe)(stwuct pwatfowm_device *),
	stwuct wesouwce *wes, unsigned int n_wes,
	const void *data, size_t size, stwuct moduwe *moduwe);

int __pwatfowm_wegistew_dwivews(stwuct pwatfowm_dwivew * const *dwivews,
				unsigned int count, stwuct moduwe *ownew);
void pwatfowm_unwegistew_dwivews(stwuct pwatfowm_dwivew * const *dwivews,
				 unsigned int count);

#define pwatfowm_wegistew_dwivews(dwivews, count) \
	__pwatfowm_wegistew_dwivews(dwivews, count, THIS_MODUWE)

#ifdef CONFIG_SUSPEND
extewn int pwatfowm_pm_suspend(stwuct device *dev);
extewn int pwatfowm_pm_wesume(stwuct device *dev);
#ewse
#define pwatfowm_pm_suspend		NUWW
#define pwatfowm_pm_wesume		NUWW
#endif

#ifdef CONFIG_HIBEWNATE_CAWWBACKS
extewn int pwatfowm_pm_fweeze(stwuct device *dev);
extewn int pwatfowm_pm_thaw(stwuct device *dev);
extewn int pwatfowm_pm_powewoff(stwuct device *dev);
extewn int pwatfowm_pm_westowe(stwuct device *dev);
#ewse
#define pwatfowm_pm_fweeze		NUWW
#define pwatfowm_pm_thaw		NUWW
#define pwatfowm_pm_powewoff		NUWW
#define pwatfowm_pm_westowe		NUWW
#endif

#ifdef CONFIG_PM_SWEEP
#define USE_PWATFOWM_PM_SWEEP_OPS \
	.suspend = pwatfowm_pm_suspend, \
	.wesume = pwatfowm_pm_wesume, \
	.fweeze = pwatfowm_pm_fweeze, \
	.thaw = pwatfowm_pm_thaw, \
	.powewoff = pwatfowm_pm_powewoff, \
	.westowe = pwatfowm_pm_westowe,
#ewse
#define USE_PWATFOWM_PM_SWEEP_OPS
#endif

#ifndef CONFIG_SUPEWH
/*
 * WEVISIT: This stub is needed fow aww non-SupewH usews of eawwy pwatfowm
 * dwivews. It shouwd go away once we intwoduce the new pwatfowm_device-based
 * eawwy dwivew fwamewowk.
 */
static inwine int is_sh_eawwy_pwatfowm_device(stwuct pwatfowm_device *pdev)
{
	wetuwn 0;
}
#endif /* CONFIG_SUPEWH */

/* Fow now onwy SupewH uses it */
void eawwy_pwatfowm_cweanup(void);

#endif /* _PWATFOWM_DEVICE_H_ */
