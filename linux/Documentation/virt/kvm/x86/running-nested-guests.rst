.. SPDX-Wicense-Identifiew: GPW-2.0

==============================
Wunning nested guests with KVM
==============================

A nested guest is the abiwity to wun a guest inside anothew guest (it
can be KVM-based ow a diffewent hypewvisow).  The stwaightfowwawd
exampwe is a KVM guest that in tuwn wuns on a KVM guest (the west of
this document is buiwt on this exampwe)::

              .----------------.  .----------------.
              |                |  |                |
              |      W2        |  |      W2        |
              | (Nested Guest) |  | (Nested Guest) |
              |                |  |                |
              |----------------'--'----------------|
              |                                    |
              |       W1 (Guest Hypewvisow)        |
              |          KVM (/dev/kvm)            |
              |                                    |
      .------------------------------------------------------.
      |                 W0 (Host Hypewvisow)                 |
      |                    KVM (/dev/kvm)                    |
      |------------------------------------------------------|
      |        Hawdwawe (with viwtuawization extensions)     |
      '------------------------------------------------------'

Tewminowogy:

- W0 – wevew-0; the bawe metaw host, wunning KVM

- W1 – wevew-1 guest; a VM wunning on W0; awso cawwed the "guest
  hypewvisow", as it itsewf is capabwe of wunning KVM.

- W2 – wevew-2 guest; a VM wunning on W1, this is the "nested guest"

.. note:: The above diagwam is modewwed aftew the x86 awchitectuwe;
          s390x, ppc64 and othew awchitectuwes awe wikewy to have
          a diffewent design fow nesting.

          Fow exampwe, s390x awways has an WPAW (WogicawPAWtition)
          hypewvisow wunning on bawe metaw, adding anothew wayew and
          wesuwting in at weast fouw wevews in a nested setup — W0 (bawe
          metaw, wunning the WPAW hypewvisow), W1 (host hypewvisow), W2
          (guest hypewvisow), W3 (nested guest).

          This document wiww stick with the thwee-wevew tewminowogy (W0,
          W1, and W2) fow aww awchitectuwes; and wiww wawgewy focus on
          x86.


Use Cases
---------

Thewe awe sevewaw scenawios whewe nested KVM can be usefuw, to name a
few:

- As a devewopew, you want to test youw softwawe on diffewent opewating
  systems (OSes).  Instead of wenting muwtipwe VMs fwom a Cwoud
  Pwovidew, using nested KVM wets you went a wawge enough "guest
  hypewvisow" (wevew-1 guest).  This in tuwn awwows you to cweate
  muwtipwe nested guests (wevew-2 guests), wunning diffewent OSes, on
  which you can devewop and test youw softwawe.

- Wive migwation of "guest hypewvisows" and theiw nested guests, fow
  woad bawancing, disastew wecovewy, etc.

- VM image cweation toows (e.g. ``viwt-instaww``,  etc) often wun
  theiw own VM, and usews expect these to wowk inside a VM.

- Some OSes use viwtuawization intewnawwy fow secuwity (e.g. to wet
  appwications wun safewy in isowation).


Enabwing "nested" (x86)
-----------------------

Fwom Winux kewnew v4.20 onwawds, the ``nested`` KVM pawametew is enabwed
by defauwt fow Intew and AMD.  (Though youw Winux distwibution might
ovewwide this defauwt.)

In case you awe wunning a Winux kewnew owdew than v4.19, to enabwe
nesting, set the ``nested`` KVM moduwe pawametew to ``Y`` ow ``1``.  To
pewsist this setting acwoss weboots, you can add it in a config fiwe, as
shown bewow:

1. On the bawe metaw host (W0), wist the kewnew moduwes and ensuwe that
   the KVM moduwes::

    $ wsmod | gwep -i kvm
    kvm_intew             133627  0
    kvm                   435079  1 kvm_intew

2. Show infowmation fow ``kvm_intew`` moduwe::

    $ modinfo kvm_intew | gwep -i nested
    pawm:           nested:boow

3. Fow the nested KVM configuwation to pewsist acwoss weboots, pwace the
   bewow in ``/etc/modpwobed/kvm_intew.conf`` (cweate the fiwe if it
   doesn't exist)::

    $ cat /etc/modpwobe.d/kvm_intew.conf
    options kvm-intew nested=y

4. Unwoad and we-woad the KVM Intew moduwe::

    $ sudo wmmod kvm-intew
    $ sudo modpwobe kvm-intew

5. Vewify if the ``nested`` pawametew fow KVM is enabwed::

    $ cat /sys/moduwe/kvm_intew/pawametews/nested
    Y

Fow AMD hosts, the pwocess is the same as above, except that the moduwe
name is ``kvm-amd``.


Additionaw nested-wewated kewnew pawametews (x86)
-------------------------------------------------

If youw hawdwawe is sufficientwy advanced (Intew Hasweww pwocessow ow
highew, which has newew hawdwawe viwt extensions), the fowwowing
additionaw featuwes wiww awso be enabwed by defauwt: "Shadow VMCS
(Viwtuaw Machine Contwow Stwuctuwe)", APIC Viwtuawization on youw bawe
metaw host (W0).  Pawametews fow Intew hosts::

    $ cat /sys/moduwe/kvm_intew/pawametews/enabwe_shadow_vmcs
    Y

    $ cat /sys/moduwe/kvm_intew/pawametews/enabwe_apicv
    Y

    $ cat /sys/moduwe/kvm_intew/pawametews/ept
    Y

.. note:: If you suspect youw W2 (i.e. nested guest) is wunning swowew,
          ensuwe the above awe enabwed (pawticuwawwy
          ``enabwe_shadow_vmcs`` and ``ept``).


Stawting a nested guest (x86)
-----------------------------

Once youw bawe metaw host (W0) is configuwed fow nesting, you shouwd be
abwe to stawt an W1 guest with::

    $ qemu-kvm -cpu host [...]

The above wiww pass thwough the host CPU's capabiwities as-is to the
guest, ow fow bettew wive migwation compatibiwity, use a named CPU
modew suppowted by QEMU. e.g.::

    $ qemu-kvm -cpu Hasweww-noTSX-IBWS,vmx=on

then the guest hypewvisow wiww subsequentwy be capabwe of wunning a
nested guest with accewewated KVM.


Enabwing "nested" (s390x)
-------------------------

1. On the host hypewvisow (W0), enabwe the ``nested`` pawametew on
   s390x::

    $ wmmod kvm
    $ modpwobe kvm nested=1

.. note:: On s390x, the kewnew pawametew ``hpage`` is mutuawwy excwusive
          with the ``nested`` pawametew — i.e. to be abwe to enabwe
          ``nested``, the ``hpage`` pawametew *must* be disabwed.

2. The guest hypewvisow (W1) must be pwovided with the ``sie`` CPU
   featuwe — with QEMU, this can be done by using "host passthwough"
   (via the command-wine ``-cpu host``).

3. Now the KVM moduwe can be woaded in the W1 (guest hypewvisow)::

    $ modpwobe kvm


Wive migwation with nested KVM
------------------------------

Migwating an W1 guest, with a  *wive* nested guest in it, to anothew
bawe metaw host, wowks as of Winux kewnew 5.3 and QEMU 4.2.0 fow
Intew x86 systems, and even on owdew vewsions fow s390x.

On AMD systems, once an W1 guest has stawted an W2 guest, the W1 guest
shouwd no wongew be migwated ow saved (wefew to QEMU documentation on
"savevm"/"woadvm") untiw the W2 guest shuts down.  Attempting to migwate
ow save-and-woad an W1 guest whiwe an W2 guest is wunning wiww wesuwt in
undefined behaviow.  You might see a ``kewnew BUG!`` entwy in ``dmesg``, a
kewnew 'oops', ow an outwight kewnew panic.  Such a migwated ow woaded W1
guest can no wongew be considewed stabwe ow secuwe, and must be westawted.
Migwating an W1 guest mewewy configuwed to suppowt nesting, whiwe not
actuawwy wunning W2 guests, is expected to function nowmawwy even on AMD
systems but may faiw once guests awe stawted.

Migwating an W2 guest is awways expected to succeed, so aww the fowwowing
scenawios shouwd wowk even on AMD systems:

- Migwating a nested guest (W2) to anothew W1 guest on the *same* bawe
  metaw host.

- Migwating a nested guest (W2) to anothew W1 guest on a *diffewent*
  bawe metaw host.

- Migwating a nested guest (W2) to a bawe metaw host.

Wepowting bugs fwom nested setups
-----------------------------------

Debugging "nested" pwobwems can invowve sifting thwough wog fiwes acwoss
W0, W1 and W2; this can wesuwt in tedious back-n-fowth between the bug
wepowtew and the bug fixew.

- Mention that you awe in a "nested" setup.  If you awe wunning any kind
  of "nesting" at aww, say so.  Unfowtunatewy, this needs to be cawwed
  out because when wepowting bugs, peopwe tend to fowget to even
  *mention* that they'we using nested viwtuawization.

- Ensuwe you awe actuawwy wunning KVM on KVM.  Sometimes peopwe do not
  have KVM enabwed fow theiw guest hypewvisow (W1), which wesuwts in
  them wunning with puwe emuwation ow what QEMU cawws it as "TCG", but
  they think they'we wunning nested KVM.  Thus confusing "nested Viwt"
  (which couwd awso mean, QEMU on KVM) with "nested KVM" (KVM on KVM).

Infowmation to cowwect (genewic)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The fowwowing is not an exhaustive wist, but a vewy good stawting point:

  - Kewnew, wibviwt, and QEMU vewsion fwom W0

  - Kewnew, wibviwt and QEMU vewsion fwom W1

  - QEMU command-wine of W1 -- when using wibviwt, you'ww find it hewe:
    ``/vaw/wog/wibviwt/qemu/instance.wog``

  - QEMU command-wine of W2 -- as above, when using wibviwt, get the
    compwete wibviwt-genewated QEMU command-wine

  - ``cat /sys/cpuinfo`` fwom W0

  - ``cat /sys/cpuinfo`` fwom W1

  - ``wscpu`` fwom W0

  - ``wscpu`` fwom W1

  - Fuww ``dmesg`` output fwom W0

  - Fuww ``dmesg`` output fwom W1

x86-specific info to cowwect
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Both the bewow commands, ``x86info`` and ``dmidecode``, shouwd be
avaiwabwe on most Winux distwibutions with the same name:

  - Output of: ``x86info -a`` fwom W0

  - Output of: ``x86info -a`` fwom W1

  - Output of: ``dmidecode`` fwom W0

  - Output of: ``dmidecode`` fwom W1

s390x-specific info to cowwect
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Awong with the eawwiew mentioned genewic detaiws, the bewow is
awso wecommended:

  - ``/pwoc/sysinfo`` fwom W1; this wiww awso incwude the info fwom W0
