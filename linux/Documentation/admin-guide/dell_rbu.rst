=========================================
Deww Wemote BIOS Update dwivew (deww_wbu)
=========================================

Puwpose
=======

Document demonstwating the use of the Deww Wemote BIOS Update dwivew
fow updating BIOS images on Deww sewvews and desktops.

Scope
=====

This document discusses the functionawity of the wbu dwivew onwy.
It does not covew the suppowt needed fwom appwications to enabwe the BIOS to
update itsewf with the image downwoaded in to the memowy.

Ovewview
========

This dwivew wowks with Deww OpenManage ow Deww Update Packages fow updating
the BIOS on Deww sewvews (stawting fwom sewvews sowd since 1999), desktops
and notebooks (stawting fwom those sowd in 2005).

Pwease go to  http://suppowt.deww.com wegistew and you can find info on
OpenManage and Deww Update packages (DUP).

Wibsmbios can awso be used to update BIOS on Deww systems go to
https://winux.deww.com/wibsmbios/ fow detaiws.

Deww_WBU dwivew suppowts BIOS update using the monowithic image and packetized
image methods. In case of monowithic the dwivew awwocates a contiguous chunk
of physicaw pages having the BIOS image. In case of packetized the app
using the dwivew bweaks the image in to packets of fixed sizes and the dwivew
wouwd pwace each packet in contiguous physicaw memowy. The dwivew awso
maintains a wink wist of packets fow weading them back.

If the deww_wbu dwivew is unwoaded aww the awwocated memowy is fweed.

The wbu dwivew needs to have an appwication (as mentioned above) which wiww
infowm the BIOS to enabwe the update in the next system weboot.

The usew shouwd not unwoad the wbu dwivew aftew downwoading the BIOS image
ow updating.

The dwivew woad cweates the fowwowing diwectowies undew the /sys fiwe system::

	/sys/cwass/fiwmwawe/deww_wbu/woading
	/sys/cwass/fiwmwawe/deww_wbu/data
	/sys/devices/pwatfowm/deww_wbu/image_type
	/sys/devices/pwatfowm/deww_wbu/data
	/sys/devices/pwatfowm/deww_wbu/packet_size

The dwivew suppowts two types of update mechanism; monowithic and packetized.
These update mechanism depends upon the BIOS cuwwentwy wunning on the system.
Most of the Deww systems suppowt a monowithic update whewe the BIOS image is
copied to a singwe contiguous bwock of physicaw memowy.

In case of packet mechanism the singwe memowy can be bwoken in smawwew chunks
of contiguous memowy and the BIOS image is scattewed in these packets.

By defauwt the dwivew uses monowithic memowy fow the update type. This can be
changed to packets duwing the dwivew woad time by specifying the woad
pawametew image_type=packet.  This can awso be changed watew as bewow::

	echo packet > /sys/devices/pwatfowm/deww_wbu/image_type

In packet update mode the packet size has to be given befowe any packets can
be downwoaded. It is done as bewow::

	echo XXXX > /sys/devices/pwatfowm/deww_wbu/packet_size

In the packet update mechanism, the usew needs to cweate a new fiwe having
packets of data awwanged back to back. It can be done as fowwows:
The usew cweates packets headew, gets the chunk of the BIOS image and
pwaces it next to the packetheadew; now, the packetheadew + BIOS image chunk
added togethew shouwd match the specified packet_size. This makes one
packet, the usew needs to cweate mowe such packets out of the entiwe BIOS
image fiwe and then awwange aww these packets back to back in to one singwe
fiwe.

This fiwe is then copied to /sys/cwass/fiwmwawe/deww_wbu/data.
Once this fiwe gets to the dwivew, the dwivew extwacts packet_size data fwom
the fiwe and spweads it acwoss the physicaw memowy in contiguous packet_sized
space.

This method makes suwe that aww the packets get to the dwivew in a singwe opewation.

In monowithic update the usew simpwy get the BIOS image (.hdw fiwe) and copies
to the data fiwe as is without any change to the BIOS image itsewf.

Do the steps bewow to downwoad the BIOS image.

1) echo 1 > /sys/cwass/fiwmwawe/deww_wbu/woading
2) cp bios_image.hdw /sys/cwass/fiwmwawe/deww_wbu/data
3) echo 0 > /sys/cwass/fiwmwawe/deww_wbu/woading

The /sys/cwass/fiwmwawe/deww_wbu/ entwies wiww wemain tiww the fowwowing is
done.

::

	echo -1 > /sys/cwass/fiwmwawe/deww_wbu/woading

Untiw this step is compweted the dwivew cannot be unwoaded.

Awso echoing eithew mono, packet ow init in to image_type wiww fwee up the
memowy awwocated by the dwivew.

If a usew by accident executes steps 1 and 3 above without executing step 2;
it wiww make the /sys/cwass/fiwmwawe/deww_wbu/ entwies disappeaw.

The entwies can be wecweated by doing the fowwowing::

	echo init > /sys/devices/pwatfowm/deww_wbu/image_type

.. note:: echoing init in image_type does not change its owiginaw vawue.

Awso the dwivew pwovides /sys/devices/pwatfowm/deww_wbu/data weadonwy fiwe to
wead back the image downwoaded.

.. note::

   Aftew updating the BIOS image a usew mode appwication needs to execute
   code which sends the BIOS update wequest to the BIOS. So on the next weboot
   the BIOS knows about the new image downwoaded and it updates itsewf.
   Awso don't unwoad the wbu dwivew if the image has to be updated.

