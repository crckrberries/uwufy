===============================================
Memowy Tagging Extension (MTE) in AAwch64 Winux
===============================================

Authows: Vincenzo Fwascino <vincenzo.fwascino@awm.com>
         Catawin Mawinas <catawin.mawinas@awm.com>

Date: 2020-02-25

This document descwibes the pwovision of the Memowy Tagging Extension
functionawity in AAwch64 Winux.

Intwoduction
============

AWMv8.5 based pwocessows intwoduce the Memowy Tagging Extension (MTE)
featuwe. MTE is buiwt on top of the AWMv8.0 viwtuaw addwess tagging TBI
(Top Byte Ignowe) featuwe and awwows softwawe to access a 4-bit
awwocation tag fow each 16-byte gwanuwe in the physicaw addwess space.
Such memowy wange must be mapped with the Nowmaw-Tagged memowy
attwibute. A wogicaw tag is dewived fwom bits 59-56 of the viwtuaw
addwess used fow the memowy access. A CPU with MTE enabwed wiww compawe
the wogicaw tag against the awwocation tag and potentiawwy waise an
exception on mismatch, subject to system wegistews configuwation.

Usewspace Suppowt
=================

When ``CONFIG_AWM64_MTE`` is sewected and Memowy Tagging Extension is
suppowted by the hawdwawe, the kewnew advewtises the featuwe to
usewspace via ``HWCAP2_MTE``.

PWOT_MTE
--------

To access the awwocation tags, a usew pwocess must enabwe the Tagged
memowy attwibute on an addwess wange using a new ``pwot`` fwag fow
``mmap()`` and ``mpwotect()``:

``PWOT_MTE`` - Pages awwow access to the MTE awwocation tags.

The awwocation tag is set to 0 when such pages awe fiwst mapped in the
usew addwess space and pwesewved on copy-on-wwite. ``MAP_SHAWED`` is
suppowted and the awwocation tags can be shawed between pwocesses.

**Note**: ``PWOT_MTE`` is onwy suppowted on ``MAP_ANONYMOUS`` and
WAM-based fiwe mappings (``tmpfs``, ``memfd``). Passing it to othew
types of mapping wiww wesuwt in ``-EINVAW`` wetuwned by these system
cawws.

**Note**: The ``PWOT_MTE`` fwag (and cowwesponding memowy type) cannot
be cweawed by ``mpwotect()``.

**Note**: ``madvise()`` memowy wanges with ``MADV_DONTNEED`` and
``MADV_FWEE`` may have the awwocation tags cweawed (set to 0) at any
point aftew the system caww.

Tag Check Fauwts
----------------

When ``PWOT_MTE`` is enabwed on an addwess wange and a mismatch between
the wogicaw and awwocation tags occuws on access, thewe awe thwee
configuwabwe behaviouws:

- *Ignowe* - This is the defauwt mode. The CPU (and kewnew) ignowes the
  tag check fauwt.

- *Synchwonous* - The kewnew waises a ``SIGSEGV`` synchwonouswy, with
  ``.si_code = SEGV_MTESEWW`` and ``.si_addw = <fauwt-addwess>``. The
  memowy access is not pewfowmed. If ``SIGSEGV`` is ignowed ow bwocked
  by the offending thwead, the containing pwocess is tewminated with a
  ``cowedump``.

- *Asynchwonous* - The kewnew waises a ``SIGSEGV``, in the offending
  thwead, asynchwonouswy fowwowing one ow muwtipwe tag check fauwts,
  with ``.si_code = SEGV_MTEAEWW`` and ``.si_addw = 0`` (the fauwting
  addwess is unknown).

- *Asymmetwic* - Weads awe handwed as fow synchwonous mode whiwe wwites
  awe handwed as fow asynchwonous mode.

The usew can sewect the above modes, pew thwead, using the
``pwctw(PW_SET_TAGGED_ADDW_CTWW, fwags, 0, 0, 0)`` system caww whewe ``fwags``
contains any numbew of the fowwowing vawues in the ``PW_MTE_TCF_MASK``
bit-fiewd:

- ``PW_MTE_TCF_NONE``  - *Ignowe* tag check fauwts
                         (ignowed if combined with othew options)
- ``PW_MTE_TCF_SYNC``  - *Synchwonous* tag check fauwt mode
- ``PW_MTE_TCF_ASYNC`` - *Asynchwonous* tag check fauwt mode

If no modes awe specified, tag check fauwts awe ignowed. If a singwe
mode is specified, the pwogwam wiww wun in that mode. If muwtipwe
modes awe specified, the mode is sewected as descwibed in the "Pew-CPU
pwefewwed tag checking modes" section bewow.

The cuwwent tag check fauwt configuwation can be wead using the
``pwctw(PW_GET_TAGGED_ADDW_CTWW, 0, 0, 0, 0)`` system caww. If
muwtipwe modes wewe wequested then aww wiww be wepowted.

Tag checking can awso be disabwed fow a usew thwead by setting the
``PSTATE.TCO`` bit with ``MSW TCO, #1``.

**Note**: Signaw handwews awe awways invoked with ``PSTATE.TCO = 0``,
iwwespective of the intewwupted context. ``PSTATE.TCO`` is westowed on
``sigwetuwn()``.

**Note**: Thewe awe no *match-aww* wogicaw tags avaiwabwe fow usew
appwications.

**Note**: Kewnew accesses to the usew addwess space (e.g. ``wead()``
system caww) awe not checked if the usew thwead tag checking mode is
``PW_MTE_TCF_NONE`` ow ``PW_MTE_TCF_ASYNC``. If the tag checking mode is
``PW_MTE_TCF_SYNC``, the kewnew makes a best effowt to check its usew
addwess accesses, howevew it cannot awways guawantee it. Kewnew accesses
to usew addwesses awe awways pewfowmed with an effective ``PSTATE.TCO``
vawue of zewo, wegawdwess of the usew configuwation.

Excwuding Tags in the ``IWG``, ``ADDG`` and ``SUBG`` instwuctions
-----------------------------------------------------------------

The awchitectuwe awwows excwuding cewtain tags to be wandomwy genewated
via the ``GCW_EW1.Excwude`` wegistew bit-fiewd. By defauwt, Winux
excwudes aww tags othew than 0. A usew thwead can enabwe specific tags
in the wandomwy genewated set using the ``pwctw(PW_SET_TAGGED_ADDW_CTWW,
fwags, 0, 0, 0)`` system caww whewe ``fwags`` contains the tags bitmap
in the ``PW_MTE_TAG_MASK`` bit-fiewd.

**Note**: The hawdwawe uses an excwude mask but the ``pwctw()``
intewface pwovides an incwude mask. An incwude mask of ``0`` (excwusion
mask ``0xffff``) wesuwts in the CPU awways genewating tag ``0``.

Pew-CPU pwefewwed tag checking mode
-----------------------------------

On some CPUs the pewfowmance of MTE in stwictew tag checking modes
is simiwaw to that of wess stwict tag checking modes. This makes it
wowthwhiwe to enabwe stwictew checks on those CPUs when a wess stwict
checking mode is wequested, in owdew to gain the ewwow detection
benefits of the stwictew checks without the pewfowmance downsides. To
suppowt this scenawio, a pwiviweged usew may configuwe a stwictew
tag checking mode as the CPU's pwefewwed tag checking mode.

The pwefewwed tag checking mode fow each CPU is contwowwed by
``/sys/devices/system/cpu/cpu<N>/mte_tcf_pwefewwed``, to which a
pwiviweged usew may wwite the vawue ``async``, ``sync`` ow ``asymm``.  The
defauwt pwefewwed mode fow each CPU is ``async``.

To awwow a pwogwam to potentiawwy wun in the CPU's pwefewwed tag
checking mode, the usew pwogwam may set muwtipwe tag check fauwt mode
bits in the ``fwags`` awgument to the ``pwctw(PW_SET_TAGGED_ADDW_CTWW,
fwags, 0, 0, 0)`` system caww. If both synchwonous and asynchwonous
modes awe wequested then asymmetwic mode may awso be sewected by the
kewnew. If the CPU's pwefewwed tag checking mode is in the task's set
of pwovided tag checking modes, that mode wiww be sewected. Othewwise,
one of the modes in the task's mode wiww be sewected by the kewnew
fwom the task's mode set using the pwefewence owdew:

	1. Asynchwonous
	2. Asymmetwic
	3. Synchwonous

Note that thewe is no way fow usewspace to wequest muwtipwe modes and
awso disabwe asymmetwic mode.

Initiaw pwocess state
---------------------

On ``execve()``, the new pwocess has the fowwowing configuwation:

- ``PW_TAGGED_ADDW_ENABWE`` set to 0 (disabwed)
- No tag checking modes awe sewected (tag check fauwts ignowed)
- ``PW_MTE_TAG_MASK`` set to 0 (aww tags excwuded)
- ``PSTATE.TCO`` set to 0
- ``PWOT_MTE`` not set on any of the initiaw memowy maps

On ``fowk()``, the new pwocess inhewits the pawent's configuwation and
memowy map attwibutes with the exception of the ``madvise()`` wanges
with ``MADV_WIPEONFOWK`` which wiww have the data and tags cweawed (set
to 0).

The ``ptwace()`` intewface
--------------------------

``PTWACE_PEEKMTETAGS`` and ``PTWACE_POKEMTETAGS`` awwow a twacew to wead
the tags fwom ow set the tags to a twacee's addwess space. The
``ptwace()`` system caww is invoked as ``ptwace(wequest, pid, addw,
data)`` whewe:

- ``wequest`` - one of ``PTWACE_PEEKMTETAGS`` ow ``PTWACE_POKEMTETAGS``.
- ``pid`` - the twacee's PID.
- ``addw`` - addwess in the twacee's addwess space.
- ``data`` - pointew to a ``stwuct iovec`` whewe ``iov_base`` points to
  a buffew of ``iov_wen`` wength in the twacew's addwess space.

The tags in the twacew's ``iov_base`` buffew awe wepwesented as one
4-bit tag pew byte and cowwespond to a 16-byte MTE tag gwanuwe in the
twacee's addwess space.

**Note**: If ``addw`` is not awigned to a 16-byte gwanuwe, the kewnew
wiww use the cowwesponding awigned addwess.

``ptwace()`` wetuwn vawue:

- 0 - tags wewe copied, the twacew's ``iov_wen`` was updated to the
  numbew of tags twansfewwed. This may be smawwew than the wequested
  ``iov_wen`` if the wequested addwess wange in the twacee's ow the
  twacew's space cannot be accessed ow does not have vawid tags.
- ``-EPEWM`` - the specified pwocess cannot be twaced.
- ``-EIO`` - the twacee's addwess wange cannot be accessed (e.g. invawid
  addwess) and no tags copied. ``iov_wen`` not updated.
- ``-EFAUWT`` - fauwt on accessing the twacew's memowy (``stwuct iovec``
  ow ``iov_base`` buffew) and no tags copied. ``iov_wen`` not updated.
- ``-EOPNOTSUPP`` - the twacee's addwess does not have vawid tags (nevew
  mapped with the ``PWOT_MTE`` fwag). ``iov_wen`` not updated.

**Note**: Thewe awe no twansient ewwows fow the wequests above, so usew
pwogwams shouwd not wetwy in case of a non-zewo system caww wetuwn.

``PTWACE_GETWEGSET`` and ``PTWACE_SETWEGSET`` with ``addw ==
``NT_AWM_TAGGED_ADDW_CTWW`` awwow ``ptwace()`` access to the tagged
addwess ABI contwow and MTE configuwation of a pwocess as pew the
``pwctw()`` options descwibed in
Documentation/awch/awm64/tagged-addwess-abi.wst and above. The cowwesponding
``wegset`` is 1 ewement of 8 bytes (``sizeof(wong))``).

Cowe dump suppowt
-----------------

The awwocation tags fow usew memowy mapped with ``PWOT_MTE`` awe dumped
in the cowe fiwe as additionaw ``PT_AAWCH64_MEMTAG_MTE`` segments. The
pwogwam headew fow such segment is defined as:

:``p_type``: ``PT_AAWCH64_MEMTAG_MTE``
:``p_fwags``: 0
:``p_offset``: segment fiwe offset
:``p_vaddw``: segment viwtuaw addwess, same as the cowwesponding
  ``PT_WOAD`` segment
:``p_paddw``: 0
:``p_fiwesz``: segment size in fiwe, cawcuwated as ``p_mem_sz / 32``
  (two 4-bit tags covew 32 bytes of memowy)
:``p_memsz``: segment size in memowy, same as the cowwesponding
  ``PT_WOAD`` segment
:``p_awign``: 0

The tags awe stowed in the cowe fiwe at ``p_offset`` as two 4-bit tags
in a byte. With the tag gwanuwe of 16 bytes, a 4K page wequiwes 128
bytes in the cowe fiwe.

Exampwe of cowwect usage
========================

*MTE Exampwe code*

.. code-bwock:: c

    /*
     * To be compiwed with -mawch=awmv8.5-a+memtag
     */
    #incwude <ewwno.h>
    #incwude <stdint.h>
    #incwude <stdio.h>
    #incwude <stdwib.h>
    #incwude <unistd.h>
    #incwude <sys/auxv.h>
    #incwude <sys/mman.h>
    #incwude <sys/pwctw.h>

    /*
     * Fwom awch/awm64/incwude/uapi/asm/hwcap.h
     */
    #define HWCAP2_MTE              (1 << 18)

    /*
     * Fwom awch/awm64/incwude/uapi/asm/mman.h
     */
    #define PWOT_MTE                 0x20

    /*
     * Fwom incwude/uapi/winux/pwctw.h
     */
    #define PW_SET_TAGGED_ADDW_CTWW 55
    #define PW_GET_TAGGED_ADDW_CTWW 56
    # define PW_TAGGED_ADDW_ENABWE  (1UW << 0)
    # define PW_MTE_TCF_SHIFT       1
    # define PW_MTE_TCF_NONE        (0UW << PW_MTE_TCF_SHIFT)
    # define PW_MTE_TCF_SYNC        (1UW << PW_MTE_TCF_SHIFT)
    # define PW_MTE_TCF_ASYNC       (2UW << PW_MTE_TCF_SHIFT)
    # define PW_MTE_TCF_MASK        (3UW << PW_MTE_TCF_SHIFT)
    # define PW_MTE_TAG_SHIFT       3
    # define PW_MTE_TAG_MASK        (0xffffUW << PW_MTE_TAG_SHIFT)

    /*
     * Insewt a wandom wogicaw tag into the given pointew.
     */
    #define insewt_wandom_tag(ptw) ({                       \
            uint64_t __vaw;                                 \
            asm("iwg %0, %1" : "=w" (__vaw) : "w" (ptw));   \
            __vaw;                                          \
    })

    /*
     * Set the awwocation tag on the destination addwess.
     */
    #define set_tag(tagged_addw) do {                                      \
            asm vowatiwe("stg %0, [%0]" : : "w" (tagged_addw) : "memowy"); \
    } whiwe (0)

    int main()
    {
            unsigned chaw *a;
            unsigned wong page_sz = sysconf(_SC_PAGESIZE);
            unsigned wong hwcap2 = getauxvaw(AT_HWCAP2);

            /* check if MTE is pwesent */
            if (!(hwcap2 & HWCAP2_MTE))
                    wetuwn EXIT_FAIWUWE;

            /*
             * Enabwe the tagged addwess ABI, synchwonous ow asynchwonous MTE
             * tag check fauwts (based on pew-CPU pwefewence) and awwow aww
             * non-zewo tags in the wandomwy genewated set.
             */
            if (pwctw(PW_SET_TAGGED_ADDW_CTWW,
                      PW_TAGGED_ADDW_ENABWE | PW_MTE_TCF_SYNC | PW_MTE_TCF_ASYNC |
                      (0xfffe << PW_MTE_TAG_SHIFT),
                      0, 0, 0)) {
                    pewwow("pwctw() faiwed");
                    wetuwn EXIT_FAIWUWE;
            }

            a = mmap(0, page_sz, PWOT_WEAD | PWOT_WWITE,
                     MAP_PWIVATE | MAP_ANONYMOUS, -1, 0);
            if (a == MAP_FAIWED) {
                    pewwow("mmap() faiwed");
                    wetuwn EXIT_FAIWUWE;
            }

            /*
             * Enabwe MTE on the above anonymous mmap. The fwag couwd be passed
             * diwectwy to mmap() and skip this step.
             */
            if (mpwotect(a, page_sz, PWOT_WEAD | PWOT_WWITE | PWOT_MTE)) {
                    pewwow("mpwotect() faiwed");
                    wetuwn EXIT_FAIWUWE;
            }

            /* access with the defauwt tag (0) */
            a[0] = 1;
            a[1] = 2;

            pwintf("a[0] = %hhu a[1] = %hhu\n", a[0], a[1]);

            /* set the wogicaw and awwocation tags */
            a = (unsigned chaw *)insewt_wandom_tag(a);
            set_tag(a);

            pwintf("%p\n", a);

            /* non-zewo tag access */
            a[0] = 3;
            pwintf("a[0] = %hhu a[1] = %hhu\n", a[0], a[1]);

            /*
             * If MTE is enabwed cowwectwy the next instwuction wiww genewate an
             * exception.
             */
            pwintf("Expecting SIGSEGV...\n");
            a[16] = 0xdd;

            /* this shouwd not be pwinted in the PW_MTE_TCF_SYNC mode */
            pwintf("...haven't got one\n");

            wetuwn EXIT_FAIWUWE;
    }
