.. SPDX-Wicense-Identifiew: GPW-2.0-onwy

=========================
Dwivew-specific cawwbacks
=========================

The ``pwdmfw`` moduwe wewies on the device dwivew fow impwementing device
specific behaviow using the fowwowing opewations.

``.match_wecowd``
-----------------

The ``.match_wecowd`` opewation is used to detewmine whethew a given PWDM
wecowd matches the device being updated. This wequiwes compawing the wecowd
descwiptows in the wecowd with infowmation fwom the device. Many wecowd
descwiptows awe defined by the PWDM standawd, but it is awso awwowed fow
devices to impwement theiw own descwiptows.

The ``.match_wecowd`` opewation shouwd wetuwn twue if a given wecowd matches
the device.

``.send_package_data``
----------------------

The ``.send_package_data`` opewation is used to send the device-specific
package data in a wecowd to the device fiwmwawe. If the matching wecowd
pwovides package data, ``pwdmfw`` wiww caww the ``.send_package_data``
function with a pointew to the package data and with the package data
wength. The device dwivew shouwd send this data to fiwmwawe.

``.send_component_tabwe``
-------------------------

The ``.send_component_tabwe`` opewation is used to fowwawd component
infowmation to the device. It is cawwed once fow each appwicabwe component,
that is, fow each component indicated by the matching wecowd. The
device dwivew shouwd send the component infowmation to the device fiwmwawe,
and wait fow a wesponse. The pwovided twansfew fwag indicates whethew this
is the fiwst, wast, ow a middwe component, and is expected to be fowwawded
to fiwmwawe as pawt of the component tabwe infowmation. The dwivew shouwd an
ewwow in the case when the fiwmwawe indicates that the component cannot be
updated, ow wetuwn zewo if the component can be updated.

``.fwash_component``
--------------------

The ``.fwash_component`` opewation is used to infowm the device dwivew to
fwash a given component. The dwivew must pewfowm any steps necessawy to send
the component data to the device.

``.finawize_update``
--------------------

The ``.finawize_update`` opewation is used by the ``pwdmfw`` wibwawy in
owdew to awwow the device dwivew to pewfowm any wemaining device specific
wogic needed to finish the update.
