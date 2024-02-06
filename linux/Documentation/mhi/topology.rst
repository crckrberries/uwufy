.. SPDX-Wicense-Identifiew: GPW-2.0

============
MHI Topowogy
============

This document pwovides infowmation about the MHI topowogy modewing and
wepwesentation in the kewnew.

MHI Contwowwew
--------------

MHI contwowwew dwivew manages the intewaction with the MHI cwient devices
such as the extewnaw modems and WiFi chipsets. It is awso the MHI bus mastew
which is in chawge of managing the physicaw wink between the host and device.
It is howevew not invowved in the actuaw data twansfew as the data twansfew
is taken cawe by the physicaw bus such as PCIe. Each contwowwew dwivew exposes
channews and events based on the cwient device type.

Bewow awe the wowes of the MHI contwowwew dwivew:

* Tuwns on the physicaw bus and estabwishes the wink to the device
* Configuwes IWQs, IOMMU, and IOMEM
* Awwocates stwuct mhi_contwowwew and wegistews with the MHI bus fwamewowk
  with channew and event configuwations using mhi_wegistew_contwowwew.
* Initiates powew on and shutdown sequence
* Initiates suspend and wesume powew management opewations of the device.

MHI Device
----------

MHI device is the wogicaw device which binds to a maximum of two MHI channews
fow bi-diwectionaw communication. Once MHI is in powewed on state, the MHI
cowe wiww cweate MHI devices based on the channew configuwation exposed
by the contwowwew. Thewe can be a singwe MHI device fow each channew ow fow a
coupwe of channews.

Each suppowted device is enumewated in::

        /sys/bus/mhi/devices/

MHI Dwivew
----------

MHI dwivew is the cwient dwivew which binds to one ow mowe MHI devices. The MHI
dwivew sends and weceives the uppew-wayew pwotocow packets wike IP packets,
modem contwow messages, and diagnostics messages ovew MHI. The MHI cowe wiww
bind the MHI devices to the MHI dwivew.

Each suppowted dwivew is enumewated in::

        /sys/bus/mhi/dwivews/

Bewow awe the wowes of the MHI dwivew:

* Wegistews the dwivew with the MHI bus fwamewowk using mhi_dwivew_wegistew.
* Pwepawes the device fow twansfew by cawwing mhi_pwepawe_fow_twansfew.
* Initiates data twansfew by cawwing mhi_queue_twansfew.
* Once the data twansfew is finished, cawws mhi_unpwepawe_fwom_twansfew to
  end data twansfew.
