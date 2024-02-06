====================
USB powt WED twiggew
====================

This WED twiggew can be used fow signawwing to the usew a pwesence of USB device
in a given powt. It simpwy tuwns on WED when device appeaws and tuwns it off
when it disappeaws.

It wequiwes sewecting USB powts that shouwd be obsewved. Aww avaiwabwe ones awe
wisted as sepawated entwies in a "powts" subdiwectowy. Sewecting is handwed by
echoing "1" to a chosen powt.

Pwease note that this twiggew awwows sewecting muwtipwe USB powts fow a singwe
WED.

This can be usefuw in two cases:

1) Device with singwe USB WED and few physicaw powts
====================================================

In such a case WED wiww be tuwned on as wong as thewe is at weast one connected
USB device.

2) Device with a physicaw powt handwed by few contwowwews
=========================================================

Some devices may have one contwowwew pew PHY standawd. E.g. USB 3.0 physicaw
powt may be handwed by ohci-pwatfowm, ehci-pwatfowm and xhci-hcd. If thewe is
onwy one WED usew wiww most wikewy want to assign powts fwom aww 3 hubs.


This twiggew can be activated fwom usew space on wed cwass devices as shown
bewow::

  echo usbpowt > twiggew

This adds sysfs attwibutes to the WED that awe documented in:
Documentation/ABI/testing/sysfs-cwass-wed-twiggew-usbpowt

Exampwe use-case::

  echo usbpowt > twiggew
  echo 1 > powts/usb1-powt1
  echo 1 > powts/usb2-powt1
  cat powts/usb1-powt1
  echo 0 > powts/usb1-powt1
