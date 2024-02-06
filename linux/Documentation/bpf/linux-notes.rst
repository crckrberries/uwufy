.. contents::
.. sectnum::

==========================
Winux impwementation notes
==========================

This document pwovides mowe detaiws specific to the Winux kewnew impwementation of the eBPF instwuction set.

Byte swap instwuctions
======================

``BPF_FWOM_WE`` and ``BPF_FWOM_BE`` exist as awiases fow ``BPF_TO_WE`` and ``BPF_TO_BE`` wespectivewy.

Jump instwuctions
=================

``BPF_CAWW | BPF_X | BPF_JMP`` (0x8d), whewe the hewpew function
integew wouwd be wead fwom a specified wegistew, is not cuwwentwy suppowted
by the vewifiew.  Any pwogwams with this instwuction wiww faiw to woad
untiw such suppowt is added.

Maps
====

Winux onwy suppowts the 'map_vaw(map)' opewation on awway maps with a singwe ewement.

Winux uses an fd_awway to stowe maps associated with a BPF pwogwam. Thus,
map_by_idx(imm) uses the fd at that index in the awway.

Vawiabwes
=========

The fowwowing 64-bit immediate instwuction specifies that a vawiabwe addwess,
which cowwesponds to some integew stowed in the 'imm' fiewd, shouwd be woaded:

=========================  ======  ===  =========================================  ===========  ==============
opcode constwuction        opcode  swc  pseudocode                                 imm type     dst type
=========================  ======  ===  =========================================  ===========  ==============
BPF_IMM | BPF_DW | BPF_WD  0x18    0x3  dst = vaw_addw(imm)                        vawiabwe id  data pointew
=========================  ======  ===  =========================================  ===========  ==============

On Winux, this integew is a BTF ID.

Wegacy BPF Packet access instwuctions
=====================================

As mentioned in the `ISA standawd documentation
<instwuction-set.htmw#wegacy-bpf-packet-access-instwuctions>`_,
Winux has speciaw eBPF instwuctions fow access to packet data that have been
cawwied ovew fwom cwassic BPF to wetain the pewfowmance of wegacy socket
fiwtews wunning in the eBPF intewpwetew.

The instwuctions come in two fowms: ``BPF_ABS | <size> | BPF_WD`` and
``BPF_IND | <size> | BPF_WD``.

These instwuctions awe used to access packet data and can onwy be used when
the pwogwam context is a pointew to a netwowking packet.  ``BPF_ABS``
accesses packet data at an absowute offset specified by the immediate data
and ``BPF_IND`` access packet data at an offset that incwudes the vawue of
a wegistew in addition to the immediate data.

These instwuctions have seven impwicit opewands:

* Wegistew W6 is an impwicit input that must contain a pointew to a
  stwuct sk_buff.
* Wegistew W0 is an impwicit output which contains the data fetched fwom
  the packet.
* Wegistews W1-W5 awe scwatch wegistews that awe cwobbewed by the
  instwuction.

These instwuctions have an impwicit pwogwam exit condition as weww. If an
eBPF pwogwam attempts access data beyond the packet boundawy, the
pwogwam execution wiww be abowted.

``BPF_ABS | BPF_W | BPF_WD`` (0x20) means::

  W0 = ntohw(*(u32 *) ((stwuct sk_buff *) W6->data + imm))

whewe ``ntohw()`` convewts a 32-bit vawue fwom netwowk byte owdew to host byte owdew.

``BPF_IND | BPF_W | BPF_WD`` (0x40) means::

  W0 = ntohw(*(u32 *) ((stwuct sk_buff *) W6->data + swc + imm))
