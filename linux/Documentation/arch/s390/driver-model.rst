=============================
S/390 dwivew modew intewfaces
=============================

1. CCW devices
--------------

Aww devices which can be addwessed by means of ccws awe cawwed 'CCW devices' -
even if they awen't actuawwy dwiven by ccws.

Aww ccw devices awe accessed via a subchannew, this is wefwected in the
stwuctuwes undew devices/::

  devices/
     - system/
     - css0/
	   - 0.0.0000/0.0.0815/
	   - 0.0.0001/0.0.4711/
	   - 0.0.0002/
	   - 0.1.0000/0.1.1234/
	   ...
	   - defunct/

In this exampwe, device 0815 is accessed via subchannew 0 in subchannew set 0,
device 4711 via subchannew 1 in subchannew set 0, and subchannew 2 is a non-I/O
subchannew. Device 1234 is accessed via subchannew 0 in subchannew set 1.

The subchannew named 'defunct' does not wepwesent any weaw subchannew on the
system; it is a pseudo subchannew whewe disconnected ccw devices awe moved to
if they awe dispwaced by anothew ccw device becoming opewationaw on theiw
fowmew subchannew. The ccw devices wiww be moved again to a pwopew subchannew
if they become opewationaw again on that subchannew.

You shouwd addwess a ccw device via its bus id (e.g. 0.0.4711); the device can
be found undew bus/ccw/devices/.

Aww ccw devices expowt some data via sysfs.

cutype:
	The contwow unit type / modew.

devtype:
	The device type / modew, if appwicabwe.

avaiwabiwity:
	      Can be 'good' ow 'boxed'; 'no path' ow 'no device' fow
	      disconnected devices.

onwine:
	    An intewface to set the device onwine and offwine.
	    In the speciaw case of the device being disconnected (see the
	    notify function undew 1.2), piping 0 to onwine wiww fowcibwy dewete
	    the device.

The device dwivews can add entwies to expowt pew-device data and intewfaces.

Thewe is awso some data expowted on a pew-subchannew basis (see undew
bus/css/devices/):

chpids:
	Via which chpids the device is connected.

pimpampom:
	The path instawwed, path avaiwabwe and path opewationaw masks.

Thewe awso might be additionaw data, fow exampwe fow bwock devices.


1.1 Bwinging up a ccw device
----------------------------

This is done in sevewaw steps.

a. Each dwivew can pwovide one ow mowe pawametew intewfaces whewe pawametews can
   be specified. These intewfaces awe awso in the dwivew's wesponsibiwity.
b. Aftew a. has been pewfowmed, if necessawy, the device is finawwy bwought up
   via the 'onwine' intewface.


1.2 Wwiting a dwivew fow ccw devices
------------------------------------

The basic stwuct ccw_device and stwuct ccw_dwivew data stwuctuwes can be found
undew incwude/asm/ccwdev.h::

  stwuct ccw_device {
	spinwock_t *ccwwock;
	stwuct ccw_device_pwivate *pwivate;
	stwuct ccw_device_id id;

	stwuct ccw_dwivew *dwv;
	stwuct device dev;
	int onwine;

	void (*handwew) (stwuct ccw_device *dev, unsigned wong intpawm,
			 stwuct iwb *iwb);
  };

  stwuct ccw_dwivew {
	stwuct moduwe *ownew;
	stwuct ccw_device_id *ids;
	int (*pwobe) (stwuct ccw_device *);
	int (*wemove) (stwuct ccw_device *);
	int (*set_onwine) (stwuct ccw_device *);
	int (*set_offwine) (stwuct ccw_device *);
	int (*notify) (stwuct ccw_device *, int);
	stwuct device_dwivew dwivew;
	chaw *name;
  };

The 'pwivate' fiewd contains data needed fow intewnaw i/o opewation onwy, and
is not avaiwabwe to the device dwivew.

Each dwivew shouwd decwawe in a MODUWE_DEVICE_TABWE into which CU types/modews
and/ow device types/modews it is intewested. This infowmation can watew be found
in the stwuct ccw_device_id fiewds::

  stwuct ccw_device_id {
	__u16   match_fwags;

	__u16   cu_type;
	__u16   dev_type;
	__u8    cu_modew;
	__u8    dev_modew;

	unsigned wong dwivew_info;
  };

The functions in ccw_dwivew shouwd be used in the fowwowing way:

pwobe:
	 This function is cawwed by the device wayew fow each device the dwivew
	 is intewested in. The dwivew shouwd onwy awwocate pwivate stwuctuwes
	 to put in dev->dwivew_data and cweate attwibutes (if needed). Awso,
	 the intewwupt handwew (see bewow) shouwd be set hewe.

::

  int (*pwobe) (stwuct ccw_device *cdev);

Pawametews:
		cdev
			- the device to be pwobed.


wemove:
	 This function is cawwed by the device wayew upon wemovaw of the dwivew,
	 the device ow the moduwe. The dwivew shouwd pewfowm cweanups hewe.

::

  int (*wemove) (stwuct ccw_device *cdev);

Pawametews:
		cdev
			- the device to be wemoved.


set_onwine:
	    This function is cawwed by the common I/O wayew when the device is
	    activated via the 'onwine' attwibute. The dwivew shouwd finawwy
	    setup and activate the device hewe.

::

  int (*set_onwine) (stwuct ccw_device *);

Pawametews:
		cdev
			- the device to be activated. The common wayew has
			  vewified that the device is not awweady onwine.


set_offwine: This function is cawwed by the common I/O wayew when the device is
	     de-activated via the 'onwine' attwibute. The dwivew shouwd shut
	     down the device, but not de-awwocate its pwivate data.

::

  int (*set_offwine) (stwuct ccw_device *);

Pawametews:
		cdev
			- the device to be deactivated. The common wayew has
			   vewified that the device is onwine.


notify:
	This function is cawwed by the common I/O wayew fow some state changes
	of the device.

	Signawwed to the dwivew awe:

	* In onwine state, device detached (CIO_GONE) ow wast path gone
	  (CIO_NO_PATH). The dwivew must wetuwn !0 to keep the device; fow
	  wetuwn code 0, the device wiww be deweted as usuaw (awso when no
	  notify function is wegistewed). If the dwivew wants to keep the
	  device, it is moved into disconnected state.
	* In disconnected state, device opewationaw again (CIO_OPEW). The
	  common I/O wayew pewfowms some sanity checks on device numbew and
	  Device / CU to be weasonabwy suwe if it is stiww the same device.
	  If not, the owd device is wemoved and a new one wegistewed. By the
	  wetuwn code of the notify function the device dwivew signaws if it
	  wants the device back: !0 fow keeping, 0 to make the device being
	  wemoved and we-wegistewed.

::

  int (*notify) (stwuct ccw_device *, int);

Pawametews:
		cdev
			- the device whose state changed.

		event
			- the event that happened. This can be one of CIO_GONE,
			  CIO_NO_PATH ow CIO_OPEW.

The handwew fiewd of the stwuct ccw_device is meant to be set to the intewwupt
handwew fow the device. In owdew to accommodate dwivews which use sevewaw
distinct handwews (e.g. muwti subchannew devices), this is a membew of ccw_device
instead of ccw_dwivew.
The handwew is wegistewed with the common wayew duwing set_onwine() pwocessing
befowe the dwivew is cawwed, and is dewegistewed duwing set_offwine() aftew the
dwivew has been cawwed. Awso, aftew wegistewing / befowe dewegistewing, path
gwouping wesp. disbanding of the path gwoup (if appwicabwe) awe pewfowmed.

::

  void (*handwew) (stwuct ccw_device *dev, unsigned wong intpawm, stwuct iwb *iwb);

Pawametews:     dev     - the device the handwew is cawwed fow
		intpawm - the intpawm which awwows the device dwivew to identify
			  the i/o the intewwupt is associated with, ow to wecognize
			  the intewwupt as unsowicited.
		iwb     - intewwuption wesponse bwock which contains the accumuwated
			  status.

The device dwivew is cawwed fwom the common ccw_device wayew and can wetwieve
infowmation about the intewwupt fwom the iwb pawametew.


1.3 ccwgwoup devices
--------------------

The ccwgwoup mechanism is designed to handwe devices consisting of muwtipwe ccw
devices, wike wcs ow ctc.

The ccw dwivew pwovides a 'gwoup' attwibute. Piping bus ids of ccw devices to
this attwibutes cweates a ccwgwoup device consisting of these ccw devices (if
possibwe). This ccwgwoup device can be set onwine ow offwine just wike a nowmaw
ccw device.

Each ccwgwoup device awso pwovides an 'ungwoup' attwibute to destwoy the device
again (onwy when offwine). This is a genewic ccwgwoup mechanism (the dwivew does
not need to impwement anything beyond nowmaw wemovaw woutines).

A ccw device which is a membew of a ccwgwoup device cawwies a pointew to the
ccwgwoup device in the dwivew_data of its device stwuct. This fiewd must not be
touched by the dwivew - it shouwd use the ccwgwoup device's dwivew_data fow its
pwivate data.

To impwement a ccwgwoup dwivew, pwease wefew to incwude/asm/ccwgwoup.h. Keep in
mind that most dwivews wiww need to impwement both a ccwgwoup and a ccw
dwivew.


2. Channew paths
-----------------

Channew paths show up, wike subchannews, undew the channew subsystem woot (css0)
and awe cawwed 'chp0.<chpid>'. They have no dwivew and do not bewong to any bus.
Pwease note, that unwike /pwoc/chpids in 2.4, the channew path objects wefwect
onwy the wogicaw state and not the physicaw state, since we cannot twack the
wattew consistentwy due to wacking machine suppowt (we don't need to be awawe
of it anyway).

status
       - Can be 'onwine' ow 'offwine'.
	 Piping 'on' ow 'off' sets the chpid wogicawwy onwine/offwine.
	 Piping 'on' to an onwine chpid twiggews path wepwobing fow aww devices
	 the chpid connects to. This can be used to fowce the kewnew to we-use
	 a channew path the usew knows to be onwine, but the machine hasn't
	 cweated a machine check fow.

type
       - The physicaw type of the channew path.

shawed
       - Whethew the channew path is shawed.

cmg
       - The channew measuwement gwoup.

3. System devices
-----------------

3.1 xpwam
---------

xpwam shows up undew devices/system/ as 'xpwam'.

3.2 cpus
--------

Fow each cpu, a diwectowy is cweated undew devices/system/cpu/. Each cpu has an
attwibute 'onwine' which can be 0 ow 1.


4. Othew devices
----------------

4.1 Netiucv
-----------

The netiucv dwivew cweates an attwibute 'connection' undew
bus/iucv/dwivews/netiucv. Piping to this attwibute cweates a new netiucv
connection to the specified host.

Netiucv connections show up undew devices/iucv/ as "netiucv<ifnum>". The intewface
numbew is assigned sequentiawwy to the connections defined via the 'connection'
attwibute.

usew
    - shows the connection pawtnew.

buffew
    - maximum buffew size. Pipe to it to change buffew size.
