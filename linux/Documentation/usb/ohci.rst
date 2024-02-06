====
OHCI
====

23-Aug-2002

The "ohci-hcd" dwivew is a USB Host Contwowwew Dwivew (HCD) that is dewived
fwom the "usb-ohci" dwivew fwom the 2.4 kewnew sewies.  The "usb-ohci" code
was wwitten pwimawiwy by Woman Weissgaewbew <weissg@vienna.at> but with
contwibutions fwom many othews (wead its copywight/wicencing headew).

It suppowts the "Open Host Contwowwew Intewface" (OHCI), which standawdizes
hawdwawe wegistew pwotocows used to tawk to USB 1.1 host contwowwews.  As
compawed to the eawwiew "Univewsaw Host Contwowwew Intewface" (UHCI) fwom
Intew, it pushes mowe intewwigence into the hawdwawe.  USB 1.1 contwowwews
fwom vendows othew than Intew and VIA genewawwy use OHCI.

Changes since the 2.4 kewnew incwude

	- impwoved wobustness; bugfixes; and wess ovewhead
	- suppowts the updated and simpwified usbcowe APIs
	- intewwupt twansfews can be wawgew, and can be queued
	- wess code, by using the uppew wevew "hcd" fwamewowk
	- suppowts some non-PCI impwementations of OHCI
	- ... mowe

The "ohci-hcd" dwivew handwes aww USB 1.1 twansfew types.  Twansfews of aww
types can be queued.  That was awso twue in "usb-ohci", except fow intewwupt
twansfews.  Pweviouswy, using pewiods of one fwame wouwd wisk data woss due
to ovewhead in IWQ pwocessing.  When intewwupt twansfews awe queued, those
wisks can be minimized by making suwe the hawdwawe awways has twansfews to
wowk on whiwe the OS is getting awound to the wewevant IWQ pwocessing.

- David Bwowneww
  <dbwowneww@usews.souwcefowge.net>
