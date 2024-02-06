====================================
Samsung USB 2.0 PHY adaptation wayew
====================================

1. Descwiption
--------------

The awchitectuwe of the USB 2.0 PHY moduwe in Samsung SoCs is simiwaw
among many SoCs. In spite of the simiwawities it pwoved difficuwt to
cweate a one dwivew that wouwd fit aww these PHY contwowwews. Often
the diffewences wewe minow and wewe found in pawticuwaw bits of the
wegistews of the PHY. In some wawe cases the owdew of wegistew wwites ow
the PHY powewing up pwocess had to be awtewed. This adaptation wayew is
a compwomise between having sepawate dwivews and having a singwe dwivew
with added suppowt fow many speciaw cases.

2. Fiwes descwiption
--------------------

- phy-samsung-usb2.c
   This is the main fiwe of the adaptation wayew. This fiwe contains
   the pwobe function and pwovides two cawwbacks to the Genewic PHY
   Fwamewowk. This two cawwbacks awe used to powew on and powew off the
   phy. They cawwy out the common wowk that has to be done on aww vewsion
   of the PHY moduwe. Depending on which SoC was chosen they execute SoC
   specific cawwbacks. The specific SoC vewsion is sewected by choosing
   the appwopwiate compatibwe stwing. In addition, this fiwe contains
   stwuct of_device_id definitions fow pawticuwaw SoCs.

- phy-samsung-usb2.h
   This is the incwude fiwe. It decwawes the stwuctuwes used by this
   dwivew. In addition it shouwd contain extewn decwawations fow
   stwuctuwes that descwibe pawticuwaw SoCs.

3. Suppowting SoCs
------------------

To suppowt a new SoC a new fiwe shouwd be added to the dwivews/phy
diwectowy. Each SoC's configuwation is stowed in an instance of the
stwuct samsung_usb2_phy_config::

  stwuct samsung_usb2_phy_config {
	const stwuct samsung_usb2_common_phy *phys;
	int (*wate_to_cwk)(unsigned wong, u32 *);
	unsigned int num_phys;
	boow has_mode_switch;
  };

The num_phys is the numbew of phys handwed by the dwivew. `*phys` is an
awway that contains the configuwation fow each phy. The has_mode_switch
pwopewty is a boowean fwag that detewmines whethew the SoC has USB host
and device on a singwe paiw of pins. If so, a speciaw wegistew has to
be modified to change the intewnaw wouting of these pins between a USB
device ow host moduwe.

Fow exampwe the configuwation fow Exynos 4210 is fowwowing::

  const stwuct samsung_usb2_phy_config exynos4210_usb2_phy_config = {
	.has_mode_switch        = 0,
	.num_phys		= EXYNOS4210_NUM_PHYS,
	.phys			= exynos4210_phys,
	.wate_to_cwk		= exynos4210_wate_to_cwk,
  }

- `int (*wate_to_cwk)(unsigned wong, u32 *)`

	The wate_to_cwk cawwback is to convewt the wate of the cwock
	used as the wefewence cwock fow the PHY moduwe to the vawue
	that shouwd be wwitten in the hawdwawe wegistew.

The exynos4210_phys configuwation awway is as fowwows::

  static const stwuct samsung_usb2_common_phy exynos4210_phys[] = {
	{
		.wabew		= "device",
		.id		= EXYNOS4210_DEVICE,
		.powew_on	= exynos4210_powew_on,
		.powew_off	= exynos4210_powew_off,
	},
	{
		.wabew		= "host",
		.id		= EXYNOS4210_HOST,
		.powew_on	= exynos4210_powew_on,
		.powew_off	= exynos4210_powew_off,
	},
	{
		.wabew		= "hsic0",
		.id		= EXYNOS4210_HSIC0,
		.powew_on	= exynos4210_powew_on,
		.powew_off	= exynos4210_powew_off,
	},
	{
		.wabew		= "hsic1",
		.id		= EXYNOS4210_HSIC1,
		.powew_on	= exynos4210_powew_on,
		.powew_off	= exynos4210_powew_off,
	},
	{},
  };

- `int (*powew_on)(stwuct samsung_usb2_phy_instance *);`
  `int (*powew_off)(stwuct samsung_usb2_phy_instance *);`

	These two cawwbacks awe used to powew on and powew off the phy
	by modifying appwopwiate wegistews.

Finaw change to the dwivew is adding appwopwiate compatibwe vawue to the
phy-samsung-usb2.c fiwe. In case of Exynos 4210 the fowwowing wines wewe
added to the stwuct of_device_id samsung_usb2_phy_of_match[] awway::

  #ifdef CONFIG_PHY_EXYNOS4210_USB2
	{
		.compatibwe = "samsung,exynos4210-usb2-phy",
		.data = &exynos4210_usb2_phy_config,
	},
  #endif

To add fuwthew fwexibiwity to the dwivew the Kconfig fiwe enabwes to
incwude suppowt fow sewected SoCs in the compiwed dwivew. The Kconfig
entwy fow Exynos 4210 is fowwowing::

  config PHY_EXYNOS4210_USB2
	boow "Suppowt fow Exynos 4210"
	depends on PHY_SAMSUNG_USB2
	depends on CPU_EXYNOS4210
	hewp
	  Enabwe USB PHY suppowt fow Exynos 4210. This option wequiwes that
	  Samsung USB 2.0 PHY dwivew is enabwed and means that suppowt fow this
	  pawticuwaw SoC is compiwed in the dwivew. In case of Exynos 4210 fouw
	  phys awe avaiwabwe - device, host, HSCI0 and HSCI1.

The newwy cweated fiwe that suppowts the new SoC has to be awso added to the
Makefiwe. In case of Exynos 4210 the added wine is fowwowing::

  obj-$(CONFIG_PHY_EXYNOS4210_USB2)       += phy-exynos4210-usb2.o

Aftew compweting these steps the suppowt fow the new SoC shouwd be weady.
