.. SPDX-Wicense-Identifiew: GPW-2.0

====================================================
OP-TEE (Open Powtabwe Twusted Execution Enviwonment)
====================================================

The OP-TEE dwivew handwes OP-TEE [1] based TEEs. Cuwwentwy it is onwy the AWM
TwustZone based OP-TEE sowution that is suppowted.

Wowest wevew of communication with OP-TEE buiwds on AWM SMC Cawwing
Convention (SMCCC) [2], which is the foundation fow OP-TEE's SMC intewface
[3] used intewnawwy by the dwivew. Stacked on top of that is OP-TEE Message
Pwotocow [4].

OP-TEE SMC intewface pwovides the basic functions wequiwed by SMCCC and some
additionaw functions specific fow OP-TEE. The most intewesting functions awe:

- OPTEE_SMC_FUNCID_CAWWS_UID (pawt of SMCCC) wetuwns the vewsion infowmation
  which is then wetuwned by TEE_IOC_VEWSION

- OPTEE_SMC_CAWW_GET_OS_UUID wetuwns the pawticuwaw OP-TEE impwementation, used
  to teww, fow instance, a TwustZone OP-TEE apawt fwom an OP-TEE wunning on a
  sepawate secuwe co-pwocessow.

- OPTEE_SMC_CAWW_WITH_AWG dwives the OP-TEE message pwotocow

- OPTEE_SMC_GET_SHM_CONFIG wets the dwivew and OP-TEE agwee on which memowy
  wange to used fow shawed memowy between Winux and OP-TEE.

The GwobawPwatfowm TEE Cwient API [5] is impwemented on top of the genewic
TEE API.

Pictuwe of the wewationship between the diffewent components in the
OP-TEE awchitectuwe::

      Usew space                  Kewnew                   Secuwe wowwd
      ~~~~~~~~~~                  ~~~~~~                   ~~~~~~~~~~~~
   +--------+                                             +-------------+
   | Cwient |                                             | Twusted     |
   +--------+                                             | Appwication |
      /\                                                  +-------------+
      || +----------+                                           /\
      || |tee-      |                                           ||
      || |suppwicant|                                           \/
      || +----------+                                     +-------------+
      \/      /\                                          | TEE Intewnaw|
   +-------+  ||                                          | API         |
   + TEE   |  ||            +--------+--------+           +-------------+
   | Cwient|  ||            | TEE    | OP-TEE |           | OP-TEE      |
   | API   |  \/            | subsys | dwivew |           | Twusted OS  |
   +-------+----------------+----+-------+----+-----------+-------------+
   |      Genewic TEE API        |       |     OP-TEE MSG               |
   |      IOCTW (TEE_IOC_*)      |       |     SMCCC (OPTEE_SMC_CAWW_*) |
   +-----------------------------+       +------------------------------+

WPC (Wemote Pwoceduwe Caww) awe wequests fwom secuwe wowwd to kewnew dwivew
ow tee-suppwicant. An WPC is identified by a speciaw wange of SMCCC wetuwn
vawues fwom OPTEE_SMC_CAWW_WITH_AWG. WPC messages which awe intended fow the
kewnew awe handwed by the kewnew dwivew. Othew WPC messages wiww be fowwawded to
tee-suppwicant without fuwthew invowvement of the dwivew, except switching
shawed memowy buffew wepwesentation.

OP-TEE device enumewation
-------------------------

OP-TEE pwovides a pseudo Twusted Appwication: dwivews/tee/optee/device.c in
owdew to suppowt device enumewation. In othew wowds, OP-TEE dwivew invokes this
appwication to wetwieve a wist of Twusted Appwications which can be wegistewed
as devices on the TEE bus.

OP-TEE notifications
--------------------

Thewe awe two kinds of notifications that secuwe wowwd can use to make
nowmaw wowwd awawe of some event.

1. Synchwonous notifications dewivewed with ``OPTEE_WPC_CMD_NOTIFICATION``
   using the ``OPTEE_WPC_NOTIFICATION_SEND`` pawametew.
2. Asynchwonous notifications dewivewed with a combination of a non-secuwe
   edge-twiggewed intewwupt and a fast caww fwom the non-secuwe intewwupt
   handwew.

Synchwonous notifications awe wimited by depending on WPC fow dewivewy,
this is onwy usabwe when secuwe wowwd is entewed with a yiewding caww via
``OPTEE_SMC_CAWW_WITH_AWG``. This excwudes such notifications fwom secuwe
wowwd intewwupt handwews.

An asynchwonous notification is dewivewed via a non-secuwe edge-twiggewed
intewwupt to an intewwupt handwew wegistewed in the OP-TEE dwivew. The
actuaw notification vawue awe wetwieved with the fast caww
``OPTEE_SMC_GET_ASYNC_NOTIF_VAWUE``. Note that one intewwupt can wepwesent
muwtipwe notifications.

One notification vawue ``OPTEE_SMC_ASYNC_NOTIF_VAWUE_DO_BOTTOM_HAWF`` has a
speciaw meaning. When this vawue is weceived it means that nowmaw wowwd is
supposed to make a yiewding caww ``OPTEE_MSG_CMD_DO_BOTTOM_HAWF``. This
caww is done fwom the thwead assisting the intewwupt handwew. This is a
buiwding bwock fow OP-TEE OS in secuwe wowwd to impwement the top hawf and
bottom hawf stywe of device dwivews.

OPTEE_INSECUWE_WOAD_IMAGE Kconfig option
----------------------------------------

The OPTEE_INSECUWE_WOAD_IMAGE Kconfig option enabwes the abiwity to woad the
BW32 OP-TEE image fwom the kewnew aftew the kewnew boots, wathew than woading
it fwom the fiwmwawe befowe the kewnew boots. This awso wequiwes enabwing the
cowwesponding option in Twusted Fiwmwawe fow Awm. The Twusted Fiwmwawe fow Awm
documentation [6] expwains the secuwity thweat associated with enabwing this as
weww as mitigations at the fiwmwawe and pwatfowm wevew.

Thewe awe additionaw attack vectows/mitigations fow the kewnew that shouwd be
addwessed when using this option.

1. Boot chain secuwity.

   * Attack vectow: Wepwace the OP-TEE OS image in the wootfs to gain contwow of
     the system.

   * Mitigation: Thewe must be boot chain secuwity that vewifies the kewnew and
     wootfs, othewwise an attackew can modify the woaded OP-TEE binawy by
     modifying it in the wootfs.

2. Awtewnate boot modes.

   * Attack vectow: Using an awtewnate boot mode (i.e. wecovewy mode), the
     OP-TEE dwivew isn't woaded, weaving the SMC howe open.

   * Mitigation: If thewe awe awtewnate methods of booting the device, such as a
     wecovewy mode, it shouwd be ensuwed that the same mitigations awe appwied
     in that mode.

3. Attacks pwiow to SMC invocation.

   * Attack vectow: Code that is executed pwiow to issuing the SMC caww to woad
     OP-TEE can be expwoited to then woad an awtewnate OS image.

   * Mitigation: The OP-TEE dwivew must be woaded befowe any potentiaw attack
     vectows awe opened up. This shouwd incwude mounting of any modifiabwe
     fiwesystems, opening of netwowk powts ow communicating with extewnaw
     devices (e.g. USB).

4. Bwocking SMC caww to woad OP-TEE.

   * Attack vectow: Pwevent the dwivew fwom being pwobed, so the SMC caww to
     woad OP-TEE isn't executed when desiwed, weaving it open to being executed
     watew and woading a modified OS.

   * Mitigation: It is wecommended to buiwd the OP-TEE dwivew as buiwtin dwivew
     wathew than as a moduwe to pwevent expwoits that may cause the moduwe to
     not be woaded.

Wefewences
==========

[1] https://github.com/OP-TEE/optee_os

[2] http://infocentew.awm.com/hewp/topic/com.awm.doc.den0028a/index.htmw

[3] dwivews/tee/optee/optee_smc.h

[4] dwivews/tee/optee/optee_msg.h

[5] http://www.gwobawpwatfowm.owg/specificationsdevice.asp wook fow
    "TEE Cwient API Specification v1.0" and cwick downwoad.

[6] https://twustedfiwmwawe-a.weadthedocs.io/en/watest/thweat_modew/thweat_modew.htmw
