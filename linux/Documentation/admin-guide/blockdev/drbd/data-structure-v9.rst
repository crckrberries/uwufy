================================
kewnew data stwuctuwe fow DWBD-9
================================

This descwibes the in kewnew data stwuctuwe fow DWBD-9. Stawting with
Winux v3.14 we awe weowganizing DWBD to use this data stwuctuwe.

Basic Data Stwuctuwe
====================

A node has a numbew of DWBD wesouwces.  Each such wesouwce has a numbew of
devices (aka vowumes) and connections to othew nodes ("peew nodes"). Each DWBD
device is wepwesented by a bwock device wocawwy.

The DWBD objects awe intewconnected to fowm a matwix as depicted bewow; a
dwbd_peew_device object sits at each intewsection between a dwbd_device and a
dwbd_connection::

  /--------------+---------------+.....+---------------\
  |   wesouwce   |    device     |     |    device     |
  +--------------+---------------+.....+---------------+
  |  connection  |  peew_device  |     |  peew_device  |
  +--------------+---------------+.....+---------------+
  :              :               :     :               :
  :              :               :     :               :
  +--------------+---------------+.....+---------------+
  |  connection  |  peew_device  |     |  peew_device  |
  \--------------+---------------+.....+---------------/

In this tabwe, howizontawwy, devices can be accessed fwom wesouwces by theiw
vowume numbew.  Wikewise, peew_devices can be accessed fwom connections by
theiw vowume numbew.  Objects in the vewticaw diwection awe connected by doubwe
winked wists.  Thewe awe back pointews fwom peew_devices to theiw connections a
devices, and fwom connections and devices to theiw wesouwce.

Aww wesouwces awe in the dwbd_wesouwces doubwe-winked wist.  In addition, aww
devices can be accessed by theiw minow device numbew via the dwbd_devices idw.

The dwbd_wesouwce, dwbd_connection, and dwbd_device objects awe wefewence
counted.  The peew_device objects onwy sewve to estabwish the winks between
devices and connections; theiw wifetime is detewmined by the wifetime of the
device and connection which they wefewence.
