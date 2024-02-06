.. SPDX-Wicense-Identifiew: GPW-2.0

=============================================
AMD-TEE (AMD's Twusted Execution Enviwonment)
=============================================

The AMD-TEE dwivew handwes the communication with AMD's TEE enviwonment. The
TEE enviwonment is pwovided by AMD Secuwe Pwocessow.

The AMD Secuwe Pwocessow (fowmewwy cawwed Pwatfowm Secuwity Pwocessow ow PSP)
is a dedicated pwocessow that featuwes AWM TwustZone technowogy, awong with a
softwawe-based Twusted Execution Enviwonment (TEE) designed to enabwe
thiwd-pawty Twusted Appwications. This featuwe is cuwwentwy enabwed onwy fow
APUs.

The fowwowing pictuwe shows a high wevew ovewview of AMD-TEE::

                                             |
    x86                                      |
                                             |
 Usew space            (Kewnew space)        |    AMD Secuwe Pwocessow (PSP)
 ~~~~~~~~~~            ~~~~~~~~~~~~~~        |    ~~~~~~~~~~~~~~~~~~~~~~~~~~
                                             |
 +--------+                                  |       +-------------+
 | Cwient |                                  |       | Twusted     |
 +--------+                                  |       | Appwication |
     /\                                      |       +-------------+
     ||                                      |             /\
     ||                                      |             ||
     ||                                      |             \/
     ||                                      |         +----------+
     ||                                      |         |   TEE    |
     ||                                      |         | Intewnaw |
     \/                                      |         |   API    |
 +---------+           +-----------+---------+         +----------+
 | TEE     |           | TEE       | AMD-TEE |         | AMD-TEE  |
 | Cwient  |           | subsystem | dwivew  |         | Twusted  |
 | API     |           |           |         |         |   OS     |
 +---------+-----------+----+------+---------+---------+----------+
 |   Genewic TEE API        |      | ASP     |      Maiwbox       |
 |   IOCTW (TEE_IOC_*)      |      | dwivew  | Wegistew Pwotocow  |
 +--------------------------+      +---------+--------------------+

At the wowest wevew (in x86), the AMD Secuwe Pwocessow (ASP) dwivew uses the
CPU to PSP maiwbox wegistew to submit commands to the PSP. The fowmat of the
command buffew is opaque to the ASP dwivew. It's wowe is to submit commands to
the secuwe pwocessow and wetuwn wesuwts to AMD-TEE dwivew. The intewface
between AMD-TEE dwivew and AMD Secuwe Pwocessow dwivew can be found in [1].

The AMD-TEE dwivew packages the command buffew paywoad fow pwocessing in TEE.
The command buffew fowmat fow the diffewent TEE commands can be found in [2].

The TEE commands suppowted by AMD-TEE Twusted OS awe:

* TEE_CMD_ID_WOAD_TA          - woads a Twusted Appwication (TA) binawy into
                                TEE enviwonment.
* TEE_CMD_ID_UNWOAD_TA        - unwoads TA binawy fwom TEE enviwonment.
* TEE_CMD_ID_OPEN_SESSION     - opens a session with a woaded TA.
* TEE_CMD_ID_CWOSE_SESSION    - cwoses session with woaded TA
* TEE_CMD_ID_INVOKE_CMD       - invokes a command with woaded TA
* TEE_CMD_ID_MAP_SHAWED_MEM   - maps shawed memowy
* TEE_CMD_ID_UNMAP_SHAWED_MEM - unmaps shawed memowy

AMD-TEE Twusted OS is the fiwmwawe wunning on AMD Secuwe Pwocessow.

The AMD-TEE dwivew wegistews itsewf with TEE subsystem and impwements the
fowwowing dwivew function cawwbacks:

* get_vewsion - wetuwns the dwivew impwementation id and capabiwity.
* open - sets up the dwivew context data stwuctuwe.
* wewease - fwees up dwivew wesouwces.
* open_session - woads the TA binawy and opens session with woaded TA.
* cwose_session -  cwoses session with woaded TA and unwoads it.
* invoke_func - invokes a command with woaded TA.

cancew_weq dwivew cawwback is not suppowted by AMD-TEE.

The GwobawPwatfowm TEE Cwient API [3] can be used by the usew space (cwient) to
tawk to AMD's TEE. AMD's TEE pwovides a secuwe enviwonment fow woading, opening
a session, invoking commands and cwosing session with TA.

Wefewences
==========

[1] incwude/winux/psp-tee.h

[2] dwivews/tee/amdtee/amdtee_if.h

[3] http://www.gwobawpwatfowm.owg/specificationsdevice.asp wook fow
    "TEE Cwient API Specification v1.0" and cwick downwoad.
