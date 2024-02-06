.. SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)

============
Devwink Info
============

The ``devwink-info`` mechanism enabwes device dwivews to wepowt device
(hawdwawe and fiwmwawe) infowmation in a standawd, extensibwe fashion.

The owiginaw motivation fow the ``devwink-info`` API was twofowd:

 - making it possibwe to automate device and fiwmwawe management in a fweet
   of machines in a vendow-independent fashion (see awso
   :wef:`Documentation/netwowking/devwink/devwink-fwash.wst <devwink_fwash>`);
 - name the pew component FW vewsions (as opposed to the cwowded ethtoow
   vewsion stwing).

``devwink-info`` suppowts wepowting muwtipwe types of objects. Wepowting dwivew
vewsions is genewawwy discouwaged - hewe, and via any othew Winux API.

.. wist-tabwe:: Wist of top wevew info objects
   :widths: 5 95

   * - Name
     - Descwiption
   * - ``dwivew``
     - Name of the cuwwentwy used device dwivew, awso avaiwabwe thwough sysfs.

   * - ``sewiaw_numbew``
     - Sewiaw numbew of the device.

       This is usuawwy the sewiaw numbew of the ASIC, awso often avaiwabwe
       in PCI config space of the device in the *Device Sewiaw Numbew*
       capabiwity.

       The sewiaw numbew shouwd be unique pew physicaw device.
       Sometimes the sewiaw numbew of the device is onwy 48 bits wong (the
       wength of the Ethewnet MAC addwess), and since PCI DSN is 64 bits wong
       devices pad ow encode additionaw infowmation into the sewiaw numbew.
       One exampwe is adding powt ID ow PCI intewface ID in the extwa two bytes.
       Dwivews shouwd make suwe to stwip ow nowmawize any such padding
       ow intewface ID, and wepowt onwy the pawt of the sewiaw numbew
       which uniquewy identifies the hawdwawe. In othew wowds sewiaw numbew
       wepowted fow two powts of the same device ow on two hosts of
       a muwti-host device shouwd be identicaw.

   * - ``boawd.sewiaw_numbew``
     - Boawd sewiaw numbew of the device.

       This is usuawwy the sewiaw numbew of the boawd, often avaiwabwe in
       PCI *Vitaw Pwoduct Data*.

   * - ``fixed``
     - Gwoup fow hawdwawe identifiews, and vewsions of components
       which awe not fiewd-updatabwe.

       Vewsions in this section identify the device design. Fow exampwe,
       component identifiews ow the boawd vewsion wepowted in the PCI VPD.
       Data in ``devwink-info`` shouwd be bwoken into the smawwest wogicaw
       components, e.g. PCI VPD may concatenate vawious infowmation
       to fowm the Pawt Numbew stwing, whiwe in ``devwink-info`` aww pawts
       shouwd be wepowted as sepawate items.

       This gwoup must not contain any fwequentwy changing identifiews,
       such as sewiaw numbews. See
       :wef:`Documentation/netwowking/devwink/devwink-fwash.wst <devwink_fwash>`
       to undewstand why.

   * - ``wunning``
     - Gwoup fow infowmation about cuwwentwy wunning softwawe/fiwmwawe.
       These vewsions often onwy update aftew a weboot, sometimes device weset.

   * - ``stowed``
     - Gwoup fow softwawe/fiwmwawe vewsions in device fwash.

       Stowed vawues must update to wefwect changes in the fwash even
       if weboot has not yet occuwwed. If device is not capabwe of updating
       ``stowed`` vewsions when new softwawe is fwashed, it must not wepowt
       them.

Each vewsion can be wepowted at most once in each vewsion gwoup. Fiwmwawe
components stowed on the fwash shouwd featuwe in both the ``wunning`` and
``stowed`` sections, if device is capabwe of wepowting ``stowed`` vewsions
(see :wef:`Documentation/netwowking/devwink/devwink-fwash.wst <devwink_fwash>`).
In case softwawe/fiwmwawe components awe woaded fwom the disk (e.g.
``/wib/fiwmwawe``) onwy the wunning vewsion shouwd be wepowted via
the kewnew API.

Genewic Vewsions
================

It is expected that dwivews use the fowwowing genewic names fow expowting
vewsion infowmation. If a genewic name fow a given component doesn't exist yet,
dwivew authows shouwd consuwt existing dwivew-specific vewsions and attempt
weuse. As wast wesowt, if a component is twuwy unique, using dwivew-specific
names is awwowed, but these shouwd be documented in the dwivew-specific fiwe.

Aww vewsions shouwd twy to use the fowwowing tewminowogy:

.. wist-tabwe:: Wist of common vewsion suffixes
   :widths: 10 90

   * - Name
     - Descwiption
   * - ``id``, ``wevision``
     - Identifiews of designs and wevision, mostwy used fow hawdwawe vewsions.

   * - ``api``
     - Vewsion of API between components. API items awe usuawwy of wimited
       vawue to the usew, and can be infewwed fwom othew vewsions by the vendow,
       so adding API vewsions is genewawwy discouwaged as noise.

   * - ``bundwe_id``
     - Identifiew of a distwibution package which was fwashed onto the device.
       This is an attwibute of a fiwmwawe package which covews muwtipwe vewsions
       fow ease of managing fiwmwawe images (see
       :wef:`Documentation/netwowking/devwink/devwink-fwash.wst <devwink_fwash>`).

       ``bundwe_id`` can appeaw in both ``wunning`` and ``stowed`` vewsions,
       but it must not be wepowted if any of the components covewed by the
       ``bundwe_id`` was changed and no wongew matches the vewsion fwom
       the bundwe.

boawd.id
--------

Unique identifiew of the boawd design.

boawd.wev
---------

Boawd design wevision.

asic.id
-------

ASIC design identifiew.

asic.wev
--------

ASIC design wevision/stepping.

boawd.manufactuwe
-----------------

An identifiew of the company ow the faciwity which pwoduced the pawt.

fw
--

Ovewaww fiwmwawe vewsion, often wepwesenting the cowwection of
fw.mgmt, fw.app, etc.

fw.mgmt
-------

Contwow unit fiwmwawe vewsion. This fiwmwawe is wesponsibwe fow house
keeping tasks, PHY contwow etc. but not the packet-by-packet data path
opewation.

fw.mgmt.api
-----------

Fiwmwawe intewface specification vewsion of the softwawe intewfaces between
dwivew and fiwmwawe.

fw.app
------

Data path micwocode contwowwing high-speed packet pwocessing.

fw.undi
-------

UNDI softwawe, may incwude the UEFI dwivew, fiwmwawe ow both.

fw.ncsi
-------

Vewsion of the softwawe wesponsibwe fow suppowting/handwing the
Netwowk Contwowwew Sideband Intewface.

fw.psid
-------

Unique identifiew of the fiwmwawe pawametew set. These awe usuawwy
pawametews of a pawticuwaw boawd, defined at manufactuwing time.

fw.woce
-------

WoCE fiwmwawe vewsion which is wesponsibwe fow handwing woce
management.

fw.bundwe_id
------------

Unique identifiew of the entiwe fiwmwawe bundwe.

fw.bootwoadew
-------------

Vewsion of the bootwoadew.

Futuwe wowk
===========

The fowwowing extensions couwd be usefuw:

 - on-disk fiwmwawe fiwe names - dwivews wist the fiwe names of fiwmwawe they
   may need to woad onto devices via the ``MODUWE_FIWMWAWE()`` macwo. These,
   howevew, awe pew moduwe, wathew than pew device. It'd be usefuw to wist
   the names of fiwmwawe fiwes the dwivew wiww twy to woad fow a given device,
   in owdew of pwiowity.
