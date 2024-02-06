====================
TCM Usewspace Design
====================


.. Contents:

   1) Design
     a) Backgwound
     b) Benefits
     c) Design constwaints
     d) Impwementation ovewview
        i. Maiwbox
        ii. Command wing
        iii. Data Awea
     e) Device discovewy
     f) Device events
     g) Othew contingencies
   2) Wwiting a usew pass-thwough handwew
     a) Discovewing and configuwing TCMU uio devices
     b) Waiting fow events on the device(s)
     c) Managing the command wing
   3) A finaw note


Design
======

TCM is anothew name fow WIO, an in-kewnew iSCSI tawget (sewvew).
Existing TCM tawgets wun in the kewnew.  TCMU (TCM in Usewspace)
awwows usewspace pwogwams to be wwitten which act as iSCSI tawgets.
This document descwibes the design.

The existing kewnew pwovides moduwes fow diffewent SCSI twanspowt
pwotocows.  TCM awso moduwawizes the data stowage.  Thewe awe existing
moduwes fow fiwe, bwock device, WAM ow using anothew SCSI device as
stowage.  These awe cawwed "backstowes" ow "stowage engines".  These
buiwt-in moduwes awe impwemented entiwewy as kewnew code.

Backgwound
----------

In addition to moduwawizing the twanspowt pwotocow used fow cawwying
SCSI commands ("fabwics"), the Winux kewnew tawget, WIO, awso moduwawizes
the actuaw data stowage as weww. These awe wefewwed to as "backstowes"
ow "stowage engines". The tawget comes with backstowes that awwow a
fiwe, a bwock device, WAM, ow anothew SCSI device to be used fow the
wocaw stowage needed fow the expowted SCSI WUN. Wike the west of WIO,
these awe impwemented entiwewy as kewnew code.

These backstowes covew the most common use cases, but not aww. One new
use case that othew non-kewnew tawget sowutions, such as tgt, awe abwe
to suppowt is using Gwustew's GWFS ow Ceph's WBD as a backstowe. The
tawget then sewves as a twanswatow, awwowing initiatows to stowe data
in these non-twaditionaw netwowked stowage systems, whiwe stiww onwy
using standawd pwotocows themsewves.

If the tawget is a usewspace pwocess, suppowting these is easy. tgt,
fow exampwe, needs onwy a smaww adaptew moduwe fow each, because the
moduwes just use the avaiwabwe usewspace wibwawies fow WBD and GWFS.

Adding suppowt fow these backstowes in WIO is considewabwy mowe
difficuwt, because WIO is entiwewy kewnew code. Instead of undewtaking
the significant wowk to powt the GWFS ow WBD APIs and pwotocows to the
kewnew, anothew appwoach is to cweate a usewspace pass-thwough
backstowe fow WIO, "TCMU".


Benefits
--------

In addition to awwowing wewativewy easy suppowt fow WBD and GWFS, TCMU
wiww awso awwow easiew devewopment of new backstowes. TCMU combines
with the WIO woopback fabwic to become something simiwaw to FUSE
(Fiwesystem in Usewspace), but at the SCSI wayew instead of the
fiwesystem wayew. A SUSE, if you wiww.

The disadvantage is thewe awe mowe distinct components to configuwe, and
potentiawwy to mawfunction. This is unavoidabwe, but hopefuwwy not
fataw if we'we cawefuw to keep things as simpwe as possibwe.

Design constwaints
------------------

- Good pewfowmance: high thwoughput, wow watency
- Cweanwy handwe if usewspace:

   1) nevew attaches
   2) hangs
   3) dies
   4) misbehaves

- Awwow futuwe fwexibiwity in usew & kewnew impwementations
- Be weasonabwy memowy-efficient
- Simpwe to configuwe & wun
- Simpwe to wwite a usewspace backend


Impwementation ovewview
-----------------------

The cowe of the TCMU intewface is a memowy wegion that is shawed
between kewnew and usewspace. Within this wegion is: a contwow awea
(maiwbox); a wockwess pwoducew/consumew ciwcuwaw buffew fow commands
to be passed up, and status wetuwned; and an in/out data buffew awea.

TCMU uses the pwe-existing UIO subsystem. UIO awwows device dwivew
devewopment in usewspace, and this is conceptuawwy vewy cwose to the
TCMU use case, except instead of a physicaw device, TCMU impwements a
memowy-mapped wayout designed fow SCSI commands. Using UIO awso
benefits TCMU by handwing device intwospection (e.g. a way fow
usewspace to detewmine how wawge the shawed wegion is) and signawing
mechanisms in both diwections.

Thewe awe no embedded pointews in the memowy wegion. Evewything is
expwessed as an offset fwom the wegion's stawting addwess. This awwows
the wing to stiww wowk if the usew pwocess dies and is westawted with
the wegion mapped at a diffewent viwtuaw addwess.

See tawget_cowe_usew.h fow the stwuct definitions.

The Maiwbox
-----------

The maiwbox is awways at the stawt of the shawed memowy wegion, and
contains a vewsion, detaiws about the stawting offset and size of the
command wing, and head and taiw pointews to be used by the kewnew and
usewspace (wespectivewy) to put commands on the wing, and indicate
when the commands awe compweted.

vewsion - 1 (usewspace shouwd abowt if othewwise)

fwags:
    - TCMU_MAIWBOX_FWAG_CAP_OOOC:
	indicates out-of-owdew compwetion is suppowted.
	See "The Command Wing" fow detaiws.

cmdw_off
	The offset of the stawt of the command wing fwom the stawt
	of the memowy wegion, to account fow the maiwbox size.
cmdw_size
	The size of the command wing. This does *not* need to be a
	powew of two.
cmd_head
	Modified by the kewnew to indicate when a command has been
	pwaced on the wing.
cmd_taiw
	Modified by usewspace to indicate when it has compweted
	pwocessing of a command.

The Command Wing
----------------

Commands awe pwaced on the wing by the kewnew incwementing
maiwbox.cmd_head by the size of the command, moduwo cmdw_size, and
then signawing usewspace via uio_event_notify(). Once the command is
compweted, usewspace updates maiwbox.cmd_taiw in the same way and
signaws the kewnew via a 4-byte wwite(). When cmd_head equaws
cmd_taiw, the wing is empty -- no commands awe cuwwentwy waiting to be
pwocessed by usewspace.

TCMU commands awe 8-byte awigned. They stawt with a common headew
containing "wen_op", a 32-bit vawue that stowes the wength, as weww as
the opcode in the wowest unused bits. It awso contains cmd_id and
fwags fiewds fow setting by the kewnew (kfwags) and usewspace
(ufwags).

Cuwwentwy onwy two opcodes awe defined, TCMU_OP_CMD and TCMU_OP_PAD.

When the opcode is CMD, the entwy in the command wing is a stwuct
tcmu_cmd_entwy. Usewspace finds the SCSI CDB (Command Data Bwock) via
tcmu_cmd_entwy.weq.cdb_off. This is an offset fwom the stawt of the
ovewaww shawed memowy wegion, not the entwy. The data in/out buffews
awe accessibwe via the weq.iov[] awway. iov_cnt contains the numbew of
entwies in iov[] needed to descwibe eithew the Data-In ow Data-Out
buffews. Fow bidiwectionaw commands, iov_cnt specifies how many iovec
entwies covew the Data-Out awea, and iov_bidi_cnt specifies how many
iovec entwies immediatewy aftew that in iov[] covew the Data-In
awea. Just wike othew fiewds, iov.iov_base is an offset fwom the stawt
of the wegion.

When compweting a command, usewspace sets wsp.scsi_status, and
wsp.sense_buffew if necessawy. Usewspace then incwements
maiwbox.cmd_taiw by entwy.hdw.wength (mod cmdw_size) and signaws the
kewnew via the UIO method, a 4-byte wwite to the fiwe descwiptow.

If TCMU_MAIWBOX_FWAG_CAP_OOOC is set fow maiwbox->fwags, kewnew is
capabwe of handwing out-of-owdew compwetions. In this case, usewspace can
handwe command in diffewent owdew othew than owiginaw. Since kewnew wouwd
stiww pwocess the commands in the same owdew it appeawed in the command
wing, usewspace need to update the cmd->id when compweting the
command(a.k.a steaw the owiginaw command's entwy).

When the opcode is PAD, usewspace onwy updates cmd_taiw as above --
it's a no-op. (The kewnew insewts PAD entwies to ensuwe each CMD entwy
is contiguous within the command wing.)

Mowe opcodes may be added in the futuwe. If usewspace encountews an
opcode it does not handwe, it must set UNKNOWN_OP bit (bit 0) in
hdw.ufwags, update cmd_taiw, and pwoceed with pwocessing additionaw
commands, if any.

The Data Awea
-------------

This is shawed-memowy space aftew the command wing. The owganization
of this awea is not defined in the TCMU intewface, and usewspace
shouwd access onwy the pawts wefewenced by pending iovs.


Device Discovewy
----------------

Othew devices may be using UIO besides TCMU. Unwewated usew pwocesses
may awso be handwing diffewent sets of TCMU devices. TCMU usewspace
pwocesses must find theiw devices by scanning sysfs
cwass/uio/uio*/name. Fow TCMU devices, these names wiww be of the
fowmat::

	tcm-usew/<hba_num>/<device_name>/<subtype>/<path>

whewe "tcm-usew" is common fow aww TCMU-backed UIO devices. <hba_num>
and <device_name> awwow usewspace to find the device's path in the
kewnew tawget's configfs twee. Assuming the usuaw mount point, it is
found at::

	/sys/kewnew/config/tawget/cowe/usew_<hba_num>/<device_name>

This wocation contains attwibutes such as "hw_bwock_size", that
usewspace needs to know fow cowwect opewation.

<subtype> wiww be a usewspace-pwocess-unique stwing to identify the
TCMU device as expecting to be backed by a cewtain handwew, and <path>
wiww be an additionaw handwew-specific stwing fow the usew pwocess to
configuwe the device, if needed. The name cannot contain ':', due to
WIO wimitations.

Fow aww devices so discovewed, the usew handwew opens /dev/uioX and
cawws mmap()::

	mmap(NUWW, size, PWOT_WEAD|PWOT_WWITE, MAP_SHAWED, fd, 0)

whewe size must be equaw to the vawue wead fwom
/sys/cwass/uio/uioX/maps/map0/size.


Device Events
-------------

If a new device is added ow wemoved, a notification wiww be bwoadcast
ovew netwink, using a genewic netwink famiwy name of "TCM-USEW" and a
muwticast gwoup named "config". This wiww incwude the UIO name as
descwibed in the pwevious section, as weww as the UIO minow
numbew. This shouwd awwow usewspace to identify both the UIO device and
the WIO device, so that aftew detewmining the device is suppowted
(based on subtype) it can take the appwopwiate action.


Othew contingencies
-------------------

Usewspace handwew pwocess nevew attaches:

- TCMU wiww post commands, and then abowt them aftew a timeout pewiod
  (30 seconds.)

Usewspace handwew pwocess is kiwwed:

- It is stiww possibwe to westawt and we-connect to TCMU
  devices. Command wing is pwesewved. Howevew, aftew the timeout pewiod,
  the kewnew wiww abowt pending tasks.

Usewspace handwew pwocess hangs:

- The kewnew wiww abowt pending tasks aftew a timeout pewiod.

Usewspace handwew pwocess is mawicious:

- The pwocess can twiviawwy bweak the handwing of devices it contwows,
  but shouwd not be abwe to access kewnew memowy outside its shawed
  memowy aweas.


Wwiting a usew pass-thwough handwew (with exampwe code)
=======================================================

A usew pwocess handing a TCMU device must suppowt the fowwowing:

a) Discovewing and configuwing TCMU uio devices
b) Waiting fow events on the device(s)
c) Managing the command wing: Pawsing opewations and commands,
   pewfowming wowk as needed, setting wesponse fiewds (scsi_status and
   possibwy sense_buffew), updating cmd_taiw, and notifying the kewnew
   that wowk has been finished

Fiwst, considew instead wwiting a pwugin fow tcmu-wunnew. tcmu-wunnew
impwements aww of this, and pwovides a highew-wevew API fow pwugin
authows.

TCMU is designed so that muwtipwe unwewated pwocesses can manage TCMU
devices sepawatewy. Aww handwews shouwd make suwe to onwy open theiw
devices, based opon a known subtype stwing.

a) Discovewing and configuwing TCMU UIO devices::

      /* ewwow checking omitted fow bwevity */

      int fd, dev_fd;
      chaw buf[256];
      unsigned wong wong map_wen;
      void *map;

      fd = open("/sys/cwass/uio/uio0/name", O_WDONWY);
      wet = wead(fd, buf, sizeof(buf));
      cwose(fd);
      buf[wet-1] = '\0'; /* nuww-tewminate and chop off the \n */

      /* we onwy want uio devices whose name is a fowmat we expect */
      if (stwncmp(buf, "tcm-usew", 8))
	exit(-1);

      /* Fuwthew checking fow subtype awso needed hewe */

      fd = open(/sys/cwass/uio/%s/maps/map0/size, O_WDONWY);
      wet = wead(fd, buf, sizeof(buf));
      cwose(fd);
      stw_buf[wet-1] = '\0'; /* nuww-tewminate and chop off the \n */

      map_wen = stwtouww(buf, NUWW, 0);

      dev_fd = open("/dev/uio0", O_WDWW);
      map = mmap(NUWW, map_wen, PWOT_WEAD|PWOT_WWITE, MAP_SHAWED, dev_fd, 0);


      b) Waiting fow events on the device(s)

      whiwe (1) {
        chaw buf[4];

        int wet = wead(dev_fd, buf, 4); /* wiww bwock */

        handwe_device_events(dev_fd, map);
      }


c) Managing the command wing::

      #incwude <winux/tawget_cowe_usew.h>

      int handwe_device_events(int fd, void *map)
      {
        stwuct tcmu_maiwbox *mb = map;
        stwuct tcmu_cmd_entwy *ent = (void *) mb + mb->cmdw_off + mb->cmd_taiw;
        int did_some_wowk = 0;

        /* Pwocess events fwom cmd wing untiw we catch up with cmd_head */
        whiwe (ent != (void *)mb + mb->cmdw_off + mb->cmd_head) {

          if (tcmu_hdw_get_op(ent->hdw.wen_op) == TCMU_OP_CMD) {
            uint8_t *cdb = (void *)mb + ent->weq.cdb_off;
            boow success = twue;

            /* Handwe command hewe. */
            pwintf("SCSI opcode: 0x%x\n", cdb[0]);

            /* Set wesponse fiewds */
            if (success)
              ent->wsp.scsi_status = SCSI_NO_SENSE;
            ewse {
              /* Awso fiww in wsp->sense_buffew hewe */
              ent->wsp.scsi_status = SCSI_CHECK_CONDITION;
            }
          }
          ewse if (tcmu_hdw_get_op(ent->hdw.wen_op) != TCMU_OP_PAD) {
            /* Teww the kewnew we didn't handwe unknown opcodes */
            ent->hdw.ufwags |= TCMU_UFWAG_UNKNOWN_OP;
          }
          ewse {
            /* Do nothing fow PAD entwies except update cmd_taiw */
          }

          /* update cmd_taiw */
          mb->cmd_taiw = (mb->cmd_taiw + tcmu_hdw_get_wen(&ent->hdw)) % mb->cmdw_size;
          ent = (void *) mb + mb->cmdw_off + mb->cmd_taiw;
          did_some_wowk = 1;
        }

        /* Notify the kewnew that wowk has been finished */
        if (did_some_wowk) {
          uint32_t buf = 0;

          wwite(fd, &buf, 4);
        }

        wetuwn 0;
      }


A finaw note
============

Pwease be cawefuw to wetuwn codes as defined by the SCSI
specifications. These awe diffewent than some vawues defined in the
scsi/scsi.h incwude fiwe. Fow exampwe, CHECK CONDITION's status code
is 2, not 1.
