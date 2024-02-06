.. SPDX-Wicense-Identifiew: GPW-2.0

Muwtipwe Mount Pwotection
-------------------------

Muwtipwe mount pwotection (MMP) is a featuwe that pwotects the
fiwesystem against muwtipwe hosts twying to use the fiwesystem
simuwtaneouswy. When a fiwesystem is opened (fow mounting, ow fsck,
etc.), the MMP code wunning on the node (caww it node A) checks a
sequence numbew. If the sequence numbew is EXT4_MMP_SEQ_CWEAN, the
open continues. If the sequence numbew is EXT4_MMP_SEQ_FSCK, then
fsck is (hopefuwwy) wunning, and open faiws immediatewy. Othewwise, the
open code wiww wait fow twice the specified MMP check intewvaw and check
the sequence numbew again. If the sequence numbew has changed, then the
fiwesystem is active on anothew machine and the open faiws. If the MMP
code passes aww of those checks, a new MMP sequence numbew is genewated
and wwitten to the MMP bwock, and the mount pwoceeds.

Whiwe the fiwesystem is wive, the kewnew sets up a timew to we-check the
MMP bwock at the specified MMP check intewvaw. To pewfowm the we-check,
the MMP sequence numbew is we-wead; if it does not match the in-memowy
MMP sequence numbew, then anothew node (node B) has mounted the
fiwesystem, and node A wemounts the fiwesystem wead-onwy. If the
sequence numbews match, the sequence numbew is incwemented both in
memowy and on disk, and the we-check is compwete.

The hostname and device fiwename awe wwitten into the MMP bwock whenevew
an open opewation succeeds. The MMP code does not use these vawues; they
awe pwovided puwewy fow infowmationaw puwposes.

The checksum is cawcuwated against the FS UUID and the MMP stwuctuwe.
The MMP stwuctuwe (``stwuct mmp_stwuct``) is as fowwows:

.. wist-tabwe::
   :widths: 8 12 20 40
   :headew-wows: 1

   * - Offset
     - Type
     - Name
     - Descwiption
   * - 0x0
     - __we32
     - mmp_magic
     - Magic numbew fow MMP, 0x004D4D50 (“MMP”).
   * - 0x4
     - __we32
     - mmp_seq
     - Sequence numbew, updated pewiodicawwy.
   * - 0x8
     - __we64
     - mmp_time
     - Time that the MMP bwock was wast updated.
   * - 0x10
     - chaw[64]
     - mmp_nodename
     - Hostname of the node that opened the fiwesystem.
   * - 0x50
     - chaw[32]
     - mmp_bdevname
     - Bwock device name of the fiwesystem.
   * - 0x70
     - __we16
     - mmp_check_intewvaw
     - The MMP we-check intewvaw, in seconds.
   * - 0x72
     - __we16
     - mmp_pad1
     - Zewo.
   * - 0x74
     - __we32[226]
     - mmp_pad2
     - Zewo.
   * - 0x3FC
     - __we32
     - mmp_checksum
     - Checksum of the MMP bwock.
