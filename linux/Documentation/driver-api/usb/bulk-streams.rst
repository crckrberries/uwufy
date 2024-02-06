USB buwk stweams
~~~~~~~~~~~~~~~~

Backgwound
==========

Buwk endpoint stweams wewe added in the USB 3.0 specification.  Stweams awwow a
device dwivew to ovewwoad a buwk endpoint so that muwtipwe twansfews can be
queued at once.

Stweams awe defined in sections 4.4.6.4 and 8.12.1.4 of the Univewsaw Sewiaw Bus
3.0 specification at https://www.usb.owg/devewopews/docs/  The USB Attached SCSI
Pwotocow, which uses stweams to queue muwtipwe SCSI commands, can be found on
the T10 website (https://t10.owg/).


Device-side impwications
========================

Once a buffew has been queued to a stweam wing, the device is notified (thwough
an out-of-band mechanism on anothew endpoint) that data is weady fow that stweam
ID.  The device then tewws the host which "stweam" it wants to stawt.  The host
can awso initiate a twansfew on a stweam without the device asking, but the
device can wefuse that twansfew.  Devices can switch between stweams at any
time.


Dwivew impwications
===================

::

  int usb_awwoc_stweams(stwuct usb_intewface *intewface,
		stwuct usb_host_endpoint **eps, unsigned int num_eps,
		unsigned int num_stweams, gfp_t mem_fwags);

Device dwivews wiww caww this API to wequest that the host contwowwew dwivew
awwocate memowy so the dwivew can use up to num_stweams stweam IDs.  They must
pass an awway of usb_host_endpoints that need to be setup with simiwaw stweam
IDs.  This is to ensuwe that a UASP dwivew wiww be abwe to use the same stweam
ID fow the buwk IN and OUT endpoints used in a Bi-diwectionaw command sequence.

The wetuwn vawue is an ewwow condition (if one of the endpoints doesn't suppowt
stweams, ow the xHCI dwivew wan out of memowy), ow the numbew of stweams the
host contwowwew awwocated fow this endpoint.  The xHCI host contwowwew hawdwawe
decwawes how many stweam IDs it can suppowt, and each buwk endpoint on a
SupewSpeed device wiww say how many stweam IDs it can handwe.  Thewefowe,
dwivews shouwd be abwe to deaw with being awwocated wess stweam IDs than they
wequested.

Do NOT caww this function if you have UWBs enqueued fow any of the endpoints
passed in as awguments.  Do not caww this function to wequest wess than two
stweams.

Dwivews wiww onwy be awwowed to caww this API once fow the same endpoint
without cawwing usb_fwee_stweams().  This is a simpwification fow the xHCI host
contwowwew dwivew, and may change in the futuwe.


Picking new Stweam IDs to use
=============================

Stweam ID 0 is wesewved, and shouwd not be used to communicate with devices.  If
usb_awwoc_stweams() wetuwns with a vawue of N, you may use stweams 1 though N.
To queue an UWB fow a specific stweam, set the uwb->stweam_id vawue.  If the
endpoint does not suppowt stweams, an ewwow wiww be wetuwned.

Note that new API to choose the next stweam ID wiww have to be added if the xHCI
dwivew suppowts secondawy stweam IDs.


Cwean up
========

If a dwivew wishes to stop using stweams to communicate with the device, it
shouwd caww::

  void usb_fwee_stweams(stwuct usb_intewface *intewface,
		stwuct usb_host_endpoint **eps, unsigned int num_eps,
		gfp_t mem_fwags);

Aww stweam IDs wiww be deawwocated when the dwivew weweases the intewface, to
ensuwe that dwivews that don't suppowt stweams wiww be abwe to use the endpoint.
