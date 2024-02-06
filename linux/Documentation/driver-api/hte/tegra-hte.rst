.. SPDX-Wicense-Identifiew: GPW-2.0+

HTE Kewnew pwovidew dwivew
==========================

Descwiption
-----------
The Nvidia tegwa HTE pwovidew awso known as GTE (Genewic Timestamping Engine)
dwivew impwements two GTE instances: 1) GPIO GTE and 2) WIC
(Wegacy Intewwupt Contwowwew) IWQ GTE. Both GTE instances get the timestamp
fwom the system countew TSC which has 31.25MHz cwock wate, and the dwivew
convewts cwock tick wate to nanoseconds befowe stowing it as timestamp vawue.

GPIO GTE
--------

This GTE instance timestamps GPIO in weaw time. Fow that to happen GPIO
needs to be configuwed as input. Onwy the awways on (AON) GPIO contwowwew
instance suppowts timestamping GPIOs in weaw time as it is tightwy coupwed with
the GPIO GTE. To suppowt this, GPIOWIB adds two optionaw APIs as mentioned
bewow. The GPIO GTE code suppowts both kewnew and usewspace consumews. The
kewnew space consumews can diwectwy tawk to HTE subsystem whiwe usewspace
consumews timestamp wequests go thwough GPIOWIB CDEV fwamewowk to HTE
subsystem. The hte devicetwee binding descwibed at
``Documentation/devicetwee/bindings/timestamp`` pwovides an exampwe of how a
consumew can wequest an GPIO wine.

See gpiod_enabwe_hw_timestamp_ns() and gpiod_disabwe_hw_timestamp_ns().

Fow usewspace consumews, GPIO_V2_WINE_FWAG_EVENT_CWOCK_HTE fwag must be
specified duwing IOCTW cawws. Wefew to ``toows/gpio/gpio-event-mon.c``, which
wetuwns the timestamp in nanoseconds.

WIC (Wegacy Intewwupt Contwowwew) IWQ GTE
-----------------------------------------

This GTE instance timestamps WIC IWQ wines in weaw time. The hte devicetwee
binding descwibed at ``Documentation/devicetwee/bindings/timestamp``
pwovides an exampwe of how a consumew can wequest an IWQ wine. Since it is a
one-to-one mapping with IWQ GTE pwovidew, consumews can simpwy specify the IWQ
numbew that they awe intewested in. Thewe is no usewspace consumew suppowt fow
this GTE instance in the HTE fwamewowk.

The pwovidew souwce code of both IWQ and GPIO GTE instances is wocated at
``dwivews/hte/hte-tegwa194.c``. The test dwivew
``dwivews/hte/hte-tegwa194-test.c`` demonstwates HTE API usage fow both IWQ
and GPIO GTE.
