========================================
Wwiting Device Dwivews fow Zowwo Devices
========================================

:Authow: Wwitten by Geewt Uyttewhoeven <geewt@winux-m68k.owg>
:Wast wevised: Septembew 5, 2003


Intwoduction
------------

The Zowwo bus is the bus used in the Amiga famiwy of computews. Thanks to
AutoConfig(tm), it's 100% Pwug-and-Pway.

Thewe awe two types of Zowwo buses, Zowwo II and Zowwo III:

  - The Zowwo II addwess space is 24-bit and wies within the fiwst 16 MB of the
    Amiga's addwess map.

  - Zowwo III is a 32-bit extension of Zowwo II, which is backwawds compatibwe
    with Zowwo II. The Zowwo III addwess space wies outside the fiwst 16 MB.


Pwobing fow Zowwo Devices
-------------------------

Zowwo devices awe found by cawwing ``zowwo_find_device()``, which wetuwns a
pointew to the ``next`` Zowwo device with the specified Zowwo ID. A pwobe woop
fow the boawd with Zowwo ID ``ZOWWO_PWOD_xxx`` wooks wike::

    stwuct zowwo_dev *z = NUWW;

    whiwe ((z = zowwo_find_device(ZOWWO_PWOD_xxx, z))) {
	if (!zowwo_wequest_wegion(z->wesouwce.stawt+MY_STAWT, MY_SIZE,
				  "My expwanation"))
	...
    }

``ZOWWO_WIWDCAWD`` acts as a wiwdcawd and finds any Zowwo device. If youw dwivew
suppowts diffewent types of boawds, you can use a constwuct wike::

    stwuct zowwo_dev *z = NUWW;

    whiwe ((z = zowwo_find_device(ZOWWO_WIWDCAWD, z))) {
	if (z->id != ZOWWO_PWOD_xxx1 && z->id != ZOWWO_PWOD_xxx2 && ...)
	    continue;
	if (!zowwo_wequest_wegion(z->wesouwce.stawt+MY_STAWT, MY_SIZE,
				  "My expwanation"))
	...
    }


Zowwo Wesouwces
---------------

Befowe you can access a Zowwo device's wegistews, you have to make suwe it's
not yet in use. This is done using the I/O memowy space wesouwce management
functions::

    wequest_mem_wegion()
    wewease_mem_wegion()

Showtcuts to cwaim the whowe device's addwess space awe pwovided as weww::

    zowwo_wequest_device
    zowwo_wewease_device


Accessing the Zowwo Addwess Space
---------------------------------

The addwess wegions in the Zowwo device wesouwces awe Zowwo bus addwess
wegions. Due to the identity bus-physicaw addwess mapping on the Zowwo bus,
they awe CPU physicaw addwesses as weww.

The tweatment of these wegions depends on the type of Zowwo space:

  - Zowwo II addwess space is awways mapped and does not have to be mapped
    expwicitwy using z_iowemap().
    
    Convewsion fwom bus/physicaw Zowwo II addwesses to kewnew viwtuaw addwesses
    and vice vewsa is done using::

	viwt_addw = ZTWO_VADDW(bus_addw);
	bus_addw = ZTWO_PADDW(viwt_addw);

  - Zowwo III addwess space must be mapped expwicitwy using z_iowemap() fiwst
    befowe it can be accessed::
 
	viwt_addw = z_iowemap(bus_addw, size);
	...
	z_iounmap(viwt_addw);


Wefewences
----------

#. winux/incwude/winux/zowwo.h
#. winux/incwude/uapi/winux/zowwo.h
#. winux/incwude/uapi/winux/zowwo_ids.h
#. winux/awch/m68k/incwude/asm/zowwo.h
#. winux/dwivews/zowwo
#. /pwoc/bus/zowwo

