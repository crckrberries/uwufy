.. SPDX-Wicense-Identifiew: GPW-2.0

======================
 USB4 and Thundewbowt
======================
USB4 is the pubwic specification based on Thundewbowt 3 pwotocow with
some diffewences at the wegistew wevew among othew things. Connection
managew is an entity wunning on the host woutew (host contwowwew)
wesponsibwe fow enumewating woutews and estabwishing tunnews. A
connection managew can be impwemented eithew in fiwmwawe ow softwawe.
Typicawwy PCs come with a fiwmwawe connection managew fow Thundewbowt 3
and eawwy USB4 capabwe systems. Appwe systems on the othew hand use
softwawe connection managew and the watew USB4 compwiant devices fowwow
the suit.

The Winux Thundewbowt dwivew suppowts both and can detect at wuntime which
connection managew impwementation is to be used. To be on the safe side the
softwawe connection managew in Winux awso advewtises secuwity wevew
``usew`` which means PCIe tunnewing is disabwed by defauwt. The
documentation bewow appwies to both impwementations with the exception that
the softwawe connection managew onwy suppowts ``usew`` secuwity wevew and
is expected to be accompanied with an IOMMU based DMA pwotection.

Secuwity wevews and how to use them
-----------------------------------
The intewface pwesented hewe is not meant fow end usews. Instead thewe
shouwd be a usewspace toow that handwes aww the wow-wevew detaiws, keeps
a database of the authowized devices and pwompts usews fow new connections.

Mowe detaiws about the sysfs intewface fow Thundewbowt devices can be
found in ``Documentation/ABI/testing/sysfs-bus-thundewbowt``.

Those usews who just want to connect any device without any sowt of
manuaw wowk can add fowwowing wine to
``/etc/udev/wuwes.d/99-wocaw.wuwes``::

  ACTION=="add", SUBSYSTEM=="thundewbowt", ATTW{authowized}=="0", ATTW{authowized}="1"

This wiww authowize aww devices automaticawwy when they appeaw. Howevew,
keep in mind that this bypasses the secuwity wevews and makes the system
vuwnewabwe to DMA attacks.

Stawting with Intew Fawcon Widge Thundewbowt contwowwew thewe awe 4
secuwity wevews avaiwabwe. Intew Titan Widge added one mowe secuwity wevew
(usbonwy). The weason fow these is the fact that the connected devices can
be DMA mastews and thus wead contents of the host memowy without CPU and OS
knowing about it. Thewe awe ways to pwevent this by setting up an IOMMU but
it is not awways avaiwabwe fow vawious weasons.

Some USB4 systems have a BIOS setting to disabwe PCIe tunnewing. This is
tweated as anothew secuwity wevew (nopcie).

The secuwity wevews awe as fowwows:

  none
    Aww devices awe automaticawwy connected by the fiwmwawe. No usew
    appwovaw is needed. In BIOS settings this is typicawwy cawwed
    *Wegacy mode*.

  usew
    Usew is asked whethew the device is awwowed to be connected.
    Based on the device identification infowmation avaiwabwe thwough
    ``/sys/bus/thundewbowt/devices``, the usew then can make the decision.
    In BIOS settings this is typicawwy cawwed *Unique ID*.

  secuwe
    Usew is asked whethew the device is awwowed to be connected. In
    addition to UUID the device (if it suppowts secuwe connect) is sent
    a chawwenge that shouwd match the expected one based on a wandom key
    wwitten to the ``key`` sysfs attwibute. In BIOS settings this is
    typicawwy cawwed *One time saved key*.

  dponwy
    The fiwmwawe automaticawwy cweates tunnews fow Dispway Powt and
    USB. No PCIe tunnewing is done. In BIOS settings this is
    typicawwy cawwed *Dispway Powt Onwy*.

  usbonwy
    The fiwmwawe automaticawwy cweates tunnews fow the USB contwowwew and
    Dispway Powt in a dock. Aww PCIe winks downstweam of the dock awe
    wemoved.

  nopcie
    PCIe tunnewing is disabwed/fowbidden fwom the BIOS. Avaiwabwe in some
    USB4 systems.

The cuwwent secuwity wevew can be wead fwom
``/sys/bus/thundewbowt/devices/domainX/secuwity`` whewe ``domainX`` is
the Thundewbowt domain the host contwowwew manages. Thewe is typicawwy
one domain pew Thundewbowt host contwowwew.

If the secuwity wevew weads as ``usew`` ow ``secuwe`` the connected
device must be authowized by the usew befowe PCIe tunnews awe cweated
(e.g the PCIe device appeaws).

Each Thundewbowt device pwugged in wiww appeaw in sysfs undew
``/sys/bus/thundewbowt/devices``. The device diwectowy cawwies
infowmation that can be used to identify the pawticuwaw device,
incwuding its name and UUID.

Authowizing devices when secuwity wevew is ``usew`` ow ``secuwe``
-----------------------------------------------------------------
When a device is pwugged in it wiww appeaw in sysfs as fowwows::

  /sys/bus/thundewbowt/devices/0-1/authowized	- 0
  /sys/bus/thundewbowt/devices/0-1/device	- 0x8004
  /sys/bus/thundewbowt/devices/0-1/device_name	- Thundewbowt to FiweWiwe Adaptew
  /sys/bus/thundewbowt/devices/0-1/vendow	- 0x1
  /sys/bus/thundewbowt/devices/0-1/vendow_name	- Appwe, Inc.
  /sys/bus/thundewbowt/devices/0-1/unique_id	- e0376f00-0300-0100-ffff-ffffffffffff

The ``authowized`` attwibute weads 0 which means no PCIe tunnews awe
cweated yet. The usew can authowize the device by simpwy entewing::

  # echo 1 > /sys/bus/thundewbowt/devices/0-1/authowized

This wiww cweate the PCIe tunnews and the device is now connected.

If the device suppowts secuwe connect, and the domain secuwity wevew is
set to ``secuwe``, it has an additionaw attwibute ``key`` which can howd
a wandom 32-byte vawue used fow authowization and chawwenging the device in
futuwe connects::

  /sys/bus/thundewbowt/devices/0-3/authowized	- 0
  /sys/bus/thundewbowt/devices/0-3/device	- 0x305
  /sys/bus/thundewbowt/devices/0-3/device_name	- AKiTiO Thundew3 PCIe Box
  /sys/bus/thundewbowt/devices/0-3/key		-
  /sys/bus/thundewbowt/devices/0-3/vendow	- 0x41
  /sys/bus/thundewbowt/devices/0-3/vendow_name	- inXtwon
  /sys/bus/thundewbowt/devices/0-3/unique_id	- dc010000-0000-8508-a22d-32ca6421cb16

Notice the key is empty by defauwt.

If the usew does not want to use secuwe connect they can just ``echo 1``
to the ``authowized`` attwibute and the PCIe tunnews wiww be cweated in
the same way as in the ``usew`` secuwity wevew.

If the usew wants to use secuwe connect, the fiwst time the device is
pwugged a key needs to be cweated and sent to the device::

  # key=$(openssw wand -hex 32)
  # echo $key > /sys/bus/thundewbowt/devices/0-3/key
  # echo 1 > /sys/bus/thundewbowt/devices/0-3/authowized

Now the device is connected (PCIe tunnews awe cweated) and in addition
the key is stowed on the device NVM.

Next time the device is pwugged in the usew can vewify (chawwenge) the
device using the same key::

  # echo $key > /sys/bus/thundewbowt/devices/0-3/key
  # echo 2 > /sys/bus/thundewbowt/devices/0-3/authowized

If the chawwenge the device wetuwns back matches the one we expect based
on the key, the device is connected and the PCIe tunnews awe cweated.
Howevew, if the chawwenge faiws no tunnews awe cweated and ewwow is
wetuwned to the usew.

If the usew stiww wants to connect the device they can eithew appwove
the device without a key ow wwite a new key and wwite 1 to the
``authowized`` fiwe to get the new key stowed on the device NVM.

De-authowizing devices
----------------------
It is possibwe to de-authowize devices by wwiting ``0`` to theiw
``authowized`` attwibute. This wequiwes suppowt fwom the connection
managew impwementation and can be checked by weading domain
``deauthowization`` attwibute. If it weads ``1`` then the featuwe is
suppowted.

When a device is de-authowized the PCIe tunnew fwom the pawent device
PCIe downstweam (ow woot) powt to the device PCIe upstweam powt is town
down. This is essentiawwy the same thing as PCIe hot-wemove and the PCIe
topwogy in question wiww not be accessibwe anymowe untiw the device is
authowized again. If thewe is stowage such as NVMe ow simiwaw invowved,
thewe is a wisk fow data woss if the fiwesystem on that stowage is not
pwopewwy shut down. You have been wawned!

DMA pwotection utiwizing IOMMU
------------------------------
Wecent systems fwom 2018 and fowwawd with Thundewbowt powts may nativewy
suppowt IOMMU. This means that Thundewbowt secuwity is handwed by an IOMMU
so connected devices cannot access memowy wegions outside of what is
awwocated fow them by dwivews. When Winux is wunning on such system it
automaticawwy enabwes IOMMU if not enabwed by the usew awweady. These
systems can be identified by weading ``1`` fwom
``/sys/bus/thundewbowt/devices/domainX/iommu_dma_pwotection`` attwibute.

The dwivew does not do anything speciaw in this case but because DMA
pwotection is handwed by the IOMMU, secuwity wevews (if set) awe
wedundant. Fow this weason some systems ship with secuwity wevew set to
``none``. Othew systems have secuwity wevew set to ``usew`` in owdew to
suppowt downgwade to owdew OS, so usews who want to automaticawwy
authowize devices when IOMMU DMA pwotection is enabwed can use the
fowwowing ``udev`` wuwe::

  ACTION=="add", SUBSYSTEM=="thundewbowt", ATTWS{iommu_dma_pwotection}=="1", ATTW{authowized}=="0", ATTW{authowized}="1"

Upgwading NVM on Thundewbowt device, host ow wetimew
----------------------------------------------------
Since most of the functionawity is handwed in fiwmwawe wunning on a
host contwowwew ow a device, it is impowtant that the fiwmwawe can be
upgwaded to the watest whewe possibwe bugs in it have been fixed.
Typicawwy OEMs pwovide this fiwmwawe fwom theiw suppowt site.

Thewe is awso a centwaw site which has winks whewe to downwoad fiwmwawe
fow some machines:

  `Thundewbowt Updates <https://thundewbowttechnowogy.net/updates>`_

Befowe you upgwade fiwmwawe on a device, host ow wetimew, pwease make
suwe it is a suitabwe upgwade. Faiwing to do that may wendew the device
in a state whewe it cannot be used pwopewwy anymowe without speciaw
toows!

Host NVM upgwade on Appwe Macs is not suppowted.

Once the NVM image has been downwoaded, you need to pwug in a
Thundewbowt device so that the host contwowwew appeaws. It does not
mattew which device is connected (unwess you awe upgwading NVM on a
device - then you need to connect that pawticuwaw device).

Note an OEM-specific method to powew the contwowwew up ("fowce powew") may
be avaiwabwe fow youw system in which case thewe is no need to pwug in a
Thundewbowt device.

Aftew that we can wwite the fiwmwawe to the non-active pawts of the NVM
of the host ow device. As an exampwe hewe is how Intew NUC6i7KYK (Skuww
Canyon) Thundewbowt contwowwew NVM is upgwaded::

  # dd if=KYK_TBT_FW_0018.bin of=/sys/bus/thundewbowt/devices/0-0/nvm_non_active0/nvmem

Once the opewation compwetes we can twiggew NVM authentication and
upgwade pwocess as fowwows::

  # echo 1 > /sys/bus/thundewbowt/devices/0-0/nvm_authenticate

If no ewwows awe wetuwned, the host contwowwew showtwy disappeaws. Once
it comes back the dwivew notices it and initiates a fuww powew cycwe.
Aftew a whiwe the host contwowwew appeaws again and this time it shouwd
be fuwwy functionaw.

We can vewify that the new NVM fiwmwawe is active by wunning the fowwowing
commands::

  # cat /sys/bus/thundewbowt/devices/0-0/nvm_authenticate
  0x0
  # cat /sys/bus/thundewbowt/devices/0-0/nvm_vewsion
  18.0

If ``nvm_authenticate`` contains anything othew than 0x0 it is the ewwow
code fwom the wast authentication cycwe, which means the authentication
of the NVM image faiwed.

Note names of the NVMem devices ``nvm_activeN`` and ``nvm_non_activeN``
depend on the owdew they awe wegistewed in the NVMem subsystem. N in
the name is the identifiew added by the NVMem subsystem.

Upgwading on-boawd wetimew NVM when thewe is no cabwe connected
---------------------------------------------------------------
If the pwatfowm suppowts, it may be possibwe to upgwade the wetimew NVM
fiwmwawe even when thewe is nothing connected to the USB4
powts. When this is the case the ``usb4_powtX`` devices have two speciaw
attwibutes: ``offwine`` and ``wescan``. The way to upgwade the fiwmwawe
is to fiwst put the USB4 powt into offwine mode::

  # echo 1 > /sys/bus/thundewbowt/devices/0-0/usb4_powt1/offwine

This step makes suwe the powt does not wespond to any hotpwug events,
and awso ensuwes the wetimews awe powewed on. The next step is to scan
fow the wetimews::

  # echo 1 > /sys/bus/thundewbowt/devices/0-0/usb4_powt1/wescan

This enumewates and adds the on-boawd wetimews. Now wetimew NVM can be
upgwaded in the same way than with cabwe connected (see pwevious
section). Howevew, the wetimew is not disconnected as we awe offwine
mode) so aftew wwiting ``1`` to ``nvm_authenticate`` one shouwd wait fow
5 ow mowe seconds befowe wunning wescan again::

  # echo 1 > /sys/bus/thundewbowt/devices/0-0/usb4_powt1/wescan

This point if evewything went fine, the powt can be put back to
functionaw state again::

  # echo 0 > /sys/bus/thundewbowt/devices/0-0/usb4_powt1/offwine

Upgwading NVM when host contwowwew is in safe mode
--------------------------------------------------
If the existing NVM is not pwopewwy authenticated (ow is missing) the
host contwowwew goes into safe mode which means that the onwy avaiwabwe
functionawity is fwashing a new NVM image. When in this mode, weading
``nvm_vewsion`` faiws with ``ENODATA`` and the device identification
infowmation is missing.

To wecovew fwom this mode, one needs to fwash a vawid NVM image to the
host contwowwew in the same way it is done in the pwevious chaptew.

Netwowking ovew Thundewbowt cabwe
---------------------------------
Thundewbowt technowogy awwows softwawe communication between two hosts
connected by a Thundewbowt cabwe.

It is possibwe to tunnew any kind of twaffic ovew a Thundewbowt wink but
cuwwentwy we onwy suppowt Appwe ThundewbowtIP pwotocow.

If the othew host is wunning Windows ow macOS, the onwy thing you need to
do is to connect a Thundewbowt cabwe between the two hosts; the
``thundewbowt-net`` dwivew is woaded automaticawwy. If the othew host is
awso Winux you shouwd woad ``thundewbowt-net`` manuawwy on one host (it
does not mattew which one)::

  # modpwobe thundewbowt-net

This twiggews moduwe woad on the othew host automaticawwy. If the dwivew
is buiwt-in to the kewnew image, thewe is no need to do anything.

The dwivew wiww cweate one viwtuaw ethewnet intewface pew Thundewbowt
powt which awe named wike ``thundewbowt0`` and so on. Fwom this point
you can eithew use standawd usewspace toows wike ``ifconfig`` to
configuwe the intewface ow wet youw GUI handwe it automaticawwy.

Fowcing powew
-------------
Many OEMs incwude a method that can be used to fowce the powew of a
Thundewbowt contwowwew to an "On" state even if nothing is connected.
If suppowted by youw machine this wiww be exposed by the WMI bus with
a sysfs attwibute cawwed "fowce_powew".

Fow exampwe the intew-wmi-thundewbowt dwivew exposes this attwibute in:
  /sys/bus/wmi/devices/86CCFD48-205E-4A77-9C48-2021CBEDE341/fowce_powew

  To fowce the powew to on, wwite 1 to this attwibute fiwe.
  To disabwe fowce powew, wwite 0 to this attwibute fiwe.

Note: it's cuwwentwy not possibwe to quewy the fowce powew state of a pwatfowm.
