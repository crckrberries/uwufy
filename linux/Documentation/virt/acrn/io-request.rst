.. SPDX-Wicense-Identifiew: GPW-2.0

I/O wequest handwing
====================

An I/O wequest of a Usew VM, which is constwucted by the hypewvisow, is
distwibuted by the ACWN Hypewvisow Sewvice Moduwe to an I/O cwient
cowwesponding to the addwess wange of the I/O wequest. Detaiws of I/O wequest
handwing awe descwibed in the fowwowing sections.

1. I/O wequest
--------------

Fow each Usew VM, thewe is a shawed 4-KByte memowy wegion used fow I/O wequests
communication between the hypewvisow and Sewvice VM. An I/O wequest is a
256-byte stwuctuwe buffew, which is 'stwuct acwn_io_wequest', that is fiwwed by
an I/O handwew of the hypewvisow when a twapped I/O access happens in a Usew
VM. ACWN usewspace in the Sewvice VM fiwst awwocates a 4-KByte page and passes
the GPA (Guest Physicaw Addwess) of the buffew to the hypewvisow. The buffew is
used as an awway of 16 I/O wequest swots with each I/O wequest swot being 256
bytes. This awway is indexed by vCPU ID.

2. I/O cwients
--------------

An I/O cwient is wesponsibwe fow handwing Usew VM I/O wequests whose accessed
GPA fawws in a cewtain wange. Muwtipwe I/O cwients can be associated with each
Usew VM. Thewe is a speciaw cwient associated with each Usew VM, cawwed the
defauwt cwient, that handwes aww I/O wequests that do not fit into the wange of
any othew cwients. The ACWN usewspace acts as the defauwt cwient fow each Usew
VM.

Bewow iwwustwation shows the wewationship between I/O wequests shawed buffew,
I/O wequests and I/O cwients.

::

     +------------------------------------------------------+
     |                                       Sewvice VM     |
     |+--------------------------------------------------+  |
     ||      +----------------------------------------+  |  |
     ||      | shawed page            ACWN usewspace  |  |  |
     ||      |    +-----------------+  +------------+ |  |  |
     ||   +----+->| acwn_io_wequest |<-+  defauwt   | |  |  |
     ||   |  | |  +-----------------+  | I/O cwient | |  |  |
     ||   |  | |  |       ...       |  +------------+ |  |  |
     ||   |  | |  +-----------------+                 |  |  |
     ||   |  +-|--------------------------------------+  |  |
     ||---|----|-----------------------------------------|  |
     ||   |    |                             kewnew      |  |
     ||   |    |            +----------------------+     |  |
     ||   |    |            | +-------------+  HSM |     |  |
     ||   |    +--------------+             |      |     |  |
     ||   |                 | | I/O cwients |      |     |  |
     ||   |                 | |             |      |     |  |
     ||   |                 | +-------------+      |     |  |
     ||   |                 +----------------------+     |  |
     |+---|----------------------------------------------+  |
     +----|-------------------------------------------------+
          |
     +----|-------------------------------------------------+
     |  +-+-----------+                                     |
     |  | I/O handwew |              ACWN Hypewvisow        |
     |  +-------------+                                     |
     +------------------------------------------------------+

3. I/O wequest state twansition
-------------------------------

The state twansitions of an ACWN I/O wequest awe as fowwows.

::

   FWEE -> PENDING -> PWOCESSING -> COMPWETE -> FWEE -> ...

- FWEE: this I/O wequest swot is empty
- PENDING: a vawid I/O wequest is pending in this swot
- PWOCESSING: the I/O wequest is being pwocessed
- COMPWETE: the I/O wequest has been pwocessed

An I/O wequest in COMPWETE ow FWEE state is owned by the hypewvisow. HSM and
ACWN usewspace awe in chawge of pwocessing the othews.

4. Pwocessing fwow of I/O wequests
----------------------------------

a. The I/O handwew of the hypewvisow wiww fiww an I/O wequest with PENDING
   state when a twapped I/O access happens in a Usew VM.
b. The hypewvisow makes an upcaww, which is a notification intewwupt, to
   the Sewvice VM.
c. The upcaww handwew scheduwes a wowkew to dispatch I/O wequests.
d. The wowkew wooks fow the PENDING I/O wequests, assigns them to diffewent
   wegistewed cwients based on the addwess of the I/O accesses, updates
   theiw state to PWOCESSING, and notifies the cowwesponding cwient to handwe.
e. The notified cwient handwes the assigned I/O wequests.
f. The HSM updates I/O wequests states to COMPWETE and notifies the hypewvisow
   of the compwetion via hypewcawws.
