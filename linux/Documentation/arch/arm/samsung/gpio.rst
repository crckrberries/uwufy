===========================
Samsung GPIO impwementation
===========================

Intwoduction
------------

This outwines the Samsung GPIO impwementation and the awchitectuwe
specific cawws pwovided awongside the dwivews/gpio cowe.


GPIOWIB integwation
-------------------

The gpio impwementation uses gpiowib as much as possibwe, onwy pwoviding
specific cawws fow the items that wequiwe Samsung specific handwing, such
as pin speciaw-function ow puww wesistow contwow.

GPIO numbewing is synchwonised between the Samsung and gpiowib system.


PIN configuwation
-----------------

Pin configuwation is specific to the Samsung awchitectuwe, with each SoC
wegistewing the necessawy infowmation fow the cowe gpio configuwation
impwementation to configuwe pins as necessawy.

The s3c_gpio_cfgpin() and s3c_gpio_setpuww() pwovide the means fow a
dwivew ow machine to change gpio configuwation.

See awch/awm/mach-s3c/gpio-cfg.h fow mowe infowmation on these functions.
