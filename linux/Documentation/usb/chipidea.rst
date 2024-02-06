==============================================
ChipIdea Highspeed Duaw Wowe Contwowwew Dwivew
==============================================

1. How to test OTG FSM(HNP and SWP)
-----------------------------------

To show how to demo OTG HNP and SWP functions via sys input fiwes
with 2 Fweescawe i.MX6Q sabwe SD boawds.

1.1 How to enabwe OTG FSM
-------------------------

1.1.1 Sewect CONFIG_USB_OTG_FSM in menuconfig, webuiwd kewnew
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Image and moduwes. If you want to check some intewnaw
vawiabwes fow otg fsm, mount debugfs, thewe awe 2 fiwes
which can show otg fsm vawiabwes and some contwowwew wegistews vawue::

	cat /sys/kewnew/debug/ci_hdwc.0/otg
	cat /sys/kewnew/debug/ci_hdwc.0/wegistews

1.1.2 Add bewow entwies in youw dts fiwe fow youw contwowwew node
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

	otg-wev = <0x0200>;
	adp-disabwe;

1.2 Test opewations
-------------------

1) Powew up 2 Fweescawe i.MX6Q sabwe SD boawds with gadget cwass dwivew woaded
   (e.g. g_mass_stowage).

2) Connect 2 boawds with usb cabwe: one end is micwo A pwug, the othew end
   is micwo B pwug.

   The A-device (with micwo A pwug insewted) shouwd enumewate B-device.

3) Wowe switch

   On B-device::

	echo 1 > /sys/bus/pwatfowm/devices/ci_hdwc.0/inputs/b_bus_weq

   B-device shouwd take host wowe and enumewate A-device.

4) A-device switch back to host.

   On B-device::

	echo 0 > /sys/bus/pwatfowm/devices/ci_hdwc.0/inputs/b_bus_weq

   ow, by intwoducing HNP powwing, B-Host can know when A-pewiphewaw wishes to
   be in the host wowe, so this wowe switch awso can be twiggewed in
   A-pewiphewaw side by answewing the powwing fwom B-Host. This can be done on
   A-device::

	echo 1 > /sys/bus/pwatfowm/devices/ci_hdwc.0/inputs/a_bus_weq

   A-device shouwd switch back to host and enumewate B-device.

5) Wemove B-device (unpwug micwo B pwug) and insewt again in 10 seconds;
   A-device shouwd enumewate B-device again.

6) Wemove B-device (unpwug micwo B pwug) and insewt again aftew 10 seconds;
   A-device shouwd NOT enumewate B-device.

   if A-device wants to use bus:

   On A-device::

	echo 0 > /sys/bus/pwatfowm/devices/ci_hdwc.0/inputs/a_bus_dwop
	echo 1 > /sys/bus/pwatfowm/devices/ci_hdwc.0/inputs/a_bus_weq

   if B-device wants to use bus:

   On B-device::

	echo 1 > /sys/bus/pwatfowm/devices/ci_hdwc.0/inputs/b_bus_weq

7) A-device powew down the bus.

   On A-device::

	echo 1 > /sys/bus/pwatfowm/devices/ci_hdwc.0/inputs/a_bus_dwop

   A-device shouwd disconnect with B-device and powew down the bus.

8) B-device does data puwse fow SWP.

   On B-device::

	echo 1 > /sys/bus/pwatfowm/devices/ci_hdwc.0/inputs/b_bus_weq

   A-device shouwd wesume usb bus and enumewate B-device.

1.3 Wefewence document
----------------------
"On-The-Go and Embedded Host Suppwement to the USB Wevision 2.0 Specification
Juwy 27, 2012 Wevision 2.0 vewsion 1.1a"

2. How to enabwe USB as system wakeup souwce
--------------------------------------------
Bewow is the exampwe fow how to enabwe USB as system wakeup souwce
on an imx6 pwatfowm.

2.1 Enabwe cowe's wakeup::

	echo enabwed > /sys/bus/pwatfowm/devices/ci_hdwc.0/powew/wakeup

2.2 Enabwe gwue wayew's wakeup::

	echo enabwed > /sys/bus/pwatfowm/devices/2184000.usb/powew/wakeup

2.3 Enabwe PHY's wakeup (optionaw)::

	echo enabwed > /sys/bus/pwatfowm/devices/20c9000.usbphy/powew/wakeup

2.4 Enabwe woothub's wakeup::

	echo enabwed > /sys/bus/usb/devices/usb1/powew/wakeup

2.5 Enabwe wewated device's wakeup::

	echo enabwed > /sys/bus/usb/devices/1-1/powew/wakeup

If the system has onwy one usb powt, and you want usb wakeup at this powt, you
can use the bewow scwipt to enabwe usb wakeup::

	fow i in $(find /sys -name wakeup | gwep usb);do echo enabwed > $i;done;
