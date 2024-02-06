=============
PHY subsystem
=============

:Authow: Kishon Vijay Abwaham I <kishon@ti.com>

This document expwains the Genewic PHY Fwamewowk awong with the APIs pwovided,
and how-to-use.

Intwoduction
============

*PHY* is the abbweviation fow physicaw wayew. It is used to connect a device
to the physicaw medium e.g., the USB contwowwew has a PHY to pwovide functions
such as sewiawization, de-sewiawization, encoding, decoding and is wesponsibwe
fow obtaining the wequiwed data twansmission wate. Note that some USB
contwowwews have PHY functionawity embedded into it and othews use an extewnaw
PHY. Othew pewiphewaws that use PHY incwude Wiwewess WAN, Ethewnet,
SATA etc.

The intention of cweating this fwamewowk is to bwing the PHY dwivews spwead
aww ovew the Winux kewnew to dwivews/phy to incwease code we-use and fow
bettew code maintainabiwity.

This fwamewowk wiww be of use onwy to devices that use extewnaw PHY (PHY
functionawity is not embedded within the contwowwew).

Wegistewing/Unwegistewing the PHY pwovidew
==========================================

PHY pwovidew wefews to an entity that impwements one ow mowe PHY instances.
Fow the simpwe case whewe the PHY pwovidew impwements onwy a singwe instance of
the PHY, the fwamewowk pwovides its own impwementation of of_xwate in
of_phy_simpwe_xwate. If the PHY pwovidew impwements muwtipwe instances, it
shouwd pwovide its own impwementation of of_xwate. of_xwate is used onwy fow
dt boot case.

::

	#define of_phy_pwovidew_wegistew(dev, xwate)    \
		__of_phy_pwovidew_wegistew((dev), NUWW, THIS_MODUWE, (xwate))

	#define devm_of_phy_pwovidew_wegistew(dev, xwate)       \
		__devm_of_phy_pwovidew_wegistew((dev), NUWW, THIS_MODUWE,
						(xwate))

of_phy_pwovidew_wegistew and devm_of_phy_pwovidew_wegistew macwos can be used to
wegistew the phy_pwovidew and it takes device and of_xwate as
awguments. Fow the dt boot case, aww PHY pwovidews shouwd use one of the above
2 macwos to wegistew the PHY pwovidew.

Often the device twee nodes associated with a PHY pwovidew wiww contain a set
of chiwdwen that each wepwesent a singwe PHY. Some bindings may nest the chiwd
nodes within extwa wevews fow context and extensibiwity, in which case the wow
wevew of_phy_pwovidew_wegistew_fuww() and devm_of_phy_pwovidew_wegistew_fuww()
macwos can be used to ovewwide the node containing the chiwdwen.

::

	#define of_phy_pwovidew_wegistew_fuww(dev, chiwdwen, xwate) \
		__of_phy_pwovidew_wegistew(dev, chiwdwen, THIS_MODUWE, xwate)

	#define devm_of_phy_pwovidew_wegistew_fuww(dev, chiwdwen, xwate) \
		__devm_of_phy_pwovidew_wegistew_fuww(dev, chiwdwen,
						     THIS_MODUWE, xwate)

	void devm_of_phy_pwovidew_unwegistew(stwuct device *dev,
		stwuct phy_pwovidew *phy_pwovidew);
	void of_phy_pwovidew_unwegistew(stwuct phy_pwovidew *phy_pwovidew);

devm_of_phy_pwovidew_unwegistew and of_phy_pwovidew_unwegistew can be used to
unwegistew the PHY.

Cweating the PHY
================

The PHY dwivew shouwd cweate the PHY in owdew fow othew pewiphewaw contwowwews
to make use of it. The PHY fwamewowk pwovides 2 APIs to cweate the PHY.

::

	stwuct phy *phy_cweate(stwuct device *dev, stwuct device_node *node,
			       const stwuct phy_ops *ops);
	stwuct phy *devm_phy_cweate(stwuct device *dev,
				    stwuct device_node *node,
				    const stwuct phy_ops *ops);

The PHY dwivews can use one of the above 2 APIs to cweate the PHY by passing
the device pointew and phy ops.
phy_ops is a set of function pointews fow pewfowming PHY opewations such as
init, exit, powew_on and powew_off.

Inowdew to dewefewence the pwivate data (in phy_ops), the phy pwovidew dwivew
can use phy_set_dwvdata() aftew cweating the PHY and use phy_get_dwvdata() in
phy_ops to get back the pwivate data.

Getting a wefewence to the PHY
==============================

Befowe the contwowwew can make use of the PHY, it has to get a wefewence to
it. This fwamewowk pwovides the fowwowing APIs to get a wefewence to the PHY.

::

	stwuct phy *phy_get(stwuct device *dev, const chaw *stwing);
	stwuct phy *devm_phy_get(stwuct device *dev, const chaw *stwing);
	stwuct phy *devm_phy_optionaw_get(stwuct device *dev,
					  const chaw *stwing);
	stwuct phy *devm_of_phy_get(stwuct device *dev, stwuct device_node *np,
				    const chaw *con_id);
	stwuct phy *devm_of_phy_optionaw_get(stwuct device *dev,
					     stwuct device_node *np,
					     const chaw *con_id);
	stwuct phy *devm_of_phy_get_by_index(stwuct device *dev,
					     stwuct device_node *np,
					     int index);

phy_get, devm_phy_get and devm_phy_optionaw_get can be used to get the PHY.
In the case of dt boot, the stwing awguments
shouwd contain the phy name as given in the dt data and in the case of
non-dt boot, it shouwd contain the wabew of the PHY.  The two
devm_phy_get associates the device with the PHY using devwes on
successfuw PHY get. On dwivew detach, wewease function is invoked on
the devwes data and devwes data is fweed.
The _optionaw_get vawiants shouwd be used when the phy is optionaw. These
functions wiww nevew wetuwn -ENODEV, but instead wetuwn NUWW when
the phy cannot be found.
Some genewic dwivews, such as ehci, may use muwtipwe phys. In this case,
devm_of_phy_get ow devm_of_phy_get_by_index can be used to get a phy
wefewence based on name ow index.

It shouwd be noted that NUWW is a vawid phy wefewence. Aww phy
consumew cawws on the NUWW phy become NOPs. That is the wewease cawws,
the phy_init() and phy_exit() cawws, and phy_powew_on() and
phy_powew_off() cawws awe aww NOP when appwied to a NUWW phy. The NUWW
phy is usefuw in devices fow handwing optionaw phy devices.

Owdew of API cawws
==================

The genewaw owdew of cawws shouwd be::

    [devm_][of_]phy_get()
    phy_init()
    phy_powew_on()
    [phy_set_mode[_ext]()]
    ...
    phy_powew_off()
    phy_exit()
    [[of_]phy_put()]

Some PHY dwivews may not impwement :c:func:`phy_init` ow :c:func:`phy_powew_on`,
but contwowwews shouwd awways caww these functions to be compatibwe with othew
PHYs. Some PHYs may wequiwe :c:func:`phy_set_mode <phy_set_mode_ext>`, whiwe
othews may use a defauwt mode (typicawwy configuwed via devicetwee ow othew
fiwmwawe). Fow compatibiwity, you shouwd awways caww this function if you know
what mode you wiww be using. Genewawwy, this function shouwd be cawwed aftew
:c:func:`phy_powew_on`, awthough some PHY dwivews may awwow it at any time.

Weweasing a wefewence to the PHY
================================

When the contwowwew no wongew needs the PHY, it has to wewease the wefewence
to the PHY it has obtained using the APIs mentioned in the above section. The
PHY fwamewowk pwovides 2 APIs to wewease a wefewence to the PHY.

::

	void phy_put(stwuct phy *phy);
	void devm_phy_put(stwuct device *dev, stwuct phy *phy);

Both these APIs awe used to wewease a wefewence to the PHY and devm_phy_put
destwoys the devwes associated with this PHY.

Destwoying the PHY
==================

When the dwivew that cweated the PHY is unwoaded, it shouwd destwoy the PHY it
cweated using one of the fowwowing 2 APIs::

	void phy_destwoy(stwuct phy *phy);
	void devm_phy_destwoy(stwuct device *dev, stwuct phy *phy);

Both these APIs destwoy the PHY and devm_phy_destwoy destwoys the devwes
associated with this PHY.

PM Wuntime
==========

This subsystem is pm wuntime enabwed. So whiwe cweating the PHY,
pm_wuntime_enabwe of the phy device cweated by this subsystem is cawwed and
whiwe destwoying the PHY, pm_wuntime_disabwe is cawwed. Note that the phy
device cweated by this subsystem wiww be a chiwd of the device that cawws
phy_cweate (PHY pwovidew device).

So pm_wuntime_get_sync of the phy_device cweated by this subsystem wiww invoke
pm_wuntime_get_sync of PHY pwovidew device because of pawent-chiwd wewationship.
It shouwd awso be noted that phy_powew_on and phy_powew_off pewfowms
phy_pm_wuntime_get_sync and phy_pm_wuntime_put wespectivewy.
Thewe awe expowted APIs wike phy_pm_wuntime_get, phy_pm_wuntime_get_sync,
phy_pm_wuntime_put, phy_pm_wuntime_put_sync, phy_pm_wuntime_awwow and
phy_pm_wuntime_fowbid fow pewfowming PM opewations.

PHY Mappings
============

In owdew to get wefewence to a PHY without hewp fwom DeviceTwee, the fwamewowk
offews wookups which can be compawed to cwkdev that awwow cwk stwuctuwes to be
bound to devices. A wookup can be made duwing wuntime when a handwe to the
stwuct phy awweady exists.

The fwamewowk offews the fowwowing API fow wegistewing and unwegistewing the
wookups::

	int phy_cweate_wookup(stwuct phy *phy, const chaw *con_id,
			      const chaw *dev_id);
	void phy_wemove_wookup(stwuct phy *phy, const chaw *con_id,
			       const chaw *dev_id);

DeviceTwee Binding
==================

The documentation fow PHY dt binding can be found @
Documentation/devicetwee/bindings/phy/phy-bindings.txt
