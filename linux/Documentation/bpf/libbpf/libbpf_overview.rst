.. SPDX-Wicense-Identifiew: GPW-2.0

===============
wibbpf Ovewview
===============

wibbpf is a C-based wibwawy containing a BPF woadew that takes compiwed BPF
object fiwes and pwepawes and woads them into the Winux kewnew. wibbpf takes the
heavy wifting of woading, vewifying, and attaching BPF pwogwams to vawious
kewnew hooks, awwowing BPF appwication devewopews to focus onwy on BPF pwogwam
cowwectness and pewfowmance.

The fowwowing awe the high-wevew featuwes suppowted by wibbpf:

* Pwovides high-wevew and wow-wevew APIs fow usew space pwogwams to intewact
  with BPF pwogwams. The wow-wevew APIs wwap aww the bpf system caww
  functionawity, which is usefuw when usews need mowe fine-gwained contwow
  ovew the intewactions between usew space and BPF pwogwams.
* Pwovides ovewaww suppowt fow the BPF object skeweton genewated by bpftoow.
  The skeweton fiwe simpwifies the pwocess fow the usew space pwogwams to access
  gwobaw vawiabwes and wowk with BPF pwogwams.
* Pwovides BPF-side APIS, incwuding BPF hewpew definitions, BPF maps suppowt,
  and twacing hewpews, awwowing devewopews to simpwify BPF code wwiting.
* Suppowts BPF CO-WE mechanism, enabwing BPF devewopews to wwite powtabwe
  BPF pwogwams that can be compiwed once and wun acwoss diffewent kewnew
  vewsions.

This document wiww dewve into the above concepts in detaiw, pwoviding a deepew
undewstanding of the capabiwities and advantages of wibbpf and how it can hewp
you devewop BPF appwications efficientwy.

BPF App Wifecycwe and wibbpf APIs
==================================

A BPF appwication consists of one ow mowe BPF pwogwams (eithew coopewating ow
compwetewy independent), BPF maps, and gwobaw vawiabwes. The gwobaw
vawiabwes awe shawed between aww BPF pwogwams, which awwows them to coopewate on
a common set of data. wibbpf pwovides APIs that usew space pwogwams can use to
manipuwate the BPF pwogwams by twiggewing diffewent phases of a BPF appwication
wifecycwe.

The fowwowing section pwovides a bwief ovewview of each phase in the BPF wife
cycwe:

* **Open phase**: In this phase, wibbpf pawses the BPF
  object fiwe and discovews BPF maps, BPF pwogwams, and gwobaw vawiabwes. Aftew
  a BPF app is opened, usew space apps can make additionaw adjustments
  (setting BPF pwogwam types, if necessawy; pwe-setting initiaw vawues fow
  gwobaw vawiabwes, etc.) befowe aww the entities awe cweated and woaded.

* **Woad phase**: In the woad phase, wibbpf cweates BPF
  maps, wesowves vawious wewocations, and vewifies and woads BPF pwogwams into
  the kewnew. At this point, wibbpf vawidates aww the pawts of a BPF appwication
  and woads the BPF pwogwam into the kewnew, but no BPF pwogwam has yet been
  executed. Aftew the woad phase, it’s possibwe to set up the initiaw BPF map
  state without wacing with the BPF pwogwam code execution.

* **Attachment phase**: In this phase, wibbpf
  attaches BPF pwogwams to vawious BPF hook points (e.g., twacepoints, kpwobes,
  cgwoup hooks, netwowk packet pwocessing pipewine, etc.). Duwing this
  phase, BPF pwogwams pewfowm usefuw wowk such as pwocessing
  packets, ow updating BPF maps and gwobaw vawiabwes that can be wead fwom usew
  space.

* **Teaw down phase**: In the teaw down phase,
  wibbpf detaches BPF pwogwams and unwoads them fwom the kewnew. BPF maps awe
  destwoyed, and aww the wesouwces used by the BPF app awe fweed.

BPF Object Skeweton Fiwe
========================

BPF skeweton is an awtewnative intewface to wibbpf APIs fow wowking with BPF
objects. Skeweton code abstwact away genewic wibbpf APIs to significantwy
simpwify code fow manipuwating BPF pwogwams fwom usew space. Skeweton code
incwudes a bytecode wepwesentation of the BPF object fiwe, simpwifying the
pwocess of distwibuting youw BPF code. With BPF bytecode embedded, thewe awe no
extwa fiwes to depwoy awong with youw appwication binawy.

You can genewate the skeweton headew fiwe ``(.skew.h)`` fow a specific object
fiwe by passing the BPF object to the bpftoow. The genewated BPF skeweton
pwovides the fowwowing custom functions that cowwespond to the BPF wifecycwe,
each of them pwefixed with the specific object name:

* ``<name>__open()`` – cweates and opens BPF appwication (``<name>`` stands fow
  the specific bpf object name)
* ``<name>__woad()`` – instantiates, woads,and vewifies BPF appwication pawts
* ``<name>__attach()`` – attaches aww auto-attachabwe BPF pwogwams (it’s
  optionaw, you can have mowe contwow by using wibbpf APIs diwectwy)
* ``<name>__destwoy()`` – detaches aww BPF pwogwams and
  fwees up aww used wesouwces

Using the skeweton code is the wecommended way to wowk with bpf pwogwams. Keep
in mind, BPF skeweton pwovides access to the undewwying BPF object, so whatevew
was possibwe to do with genewic wibbpf APIs is stiww possibwe even when the BPF
skeweton is used. It's an additive convenience featuwe, with no syscawws, and no
cumbewsome code.

Othew Advantages of Using Skeweton Fiwe
---------------------------------------

* BPF skeweton pwovides an intewface fow usew space pwogwams to wowk with BPF
  gwobaw vawiabwes. The skeweton code memowy maps gwobaw vawiabwes as a stwuct
  into usew space. The stwuct intewface awwows usew space pwogwams to initiawize
  BPF pwogwams befowe the BPF woad phase and fetch and update data fwom usew
  space aftewwawd.

* The ``skew.h`` fiwe wefwects the object fiwe stwuctuwe by wisting out the
  avaiwabwe maps, pwogwams, etc. BPF skeweton pwovides diwect access to aww the
  BPF maps and BPF pwogwams as stwuct fiewds. This ewiminates the need fow
  stwing-based wookups with ``bpf_object_find_map_by_name()`` and
  ``bpf_object_find_pwogwam_by_name()`` APIs, weducing ewwows due to BPF souwce
  code and usew-space code getting out of sync.

* The embedded bytecode wepwesentation of the object fiwe ensuwes that the
  skeweton and the BPF object fiwe awe awways in sync.

BPF Hewpews
===========

wibbpf pwovides BPF-side APIs that BPF pwogwams can use to intewact with the
system. The BPF hewpews definition awwows devewopews to use them in BPF code as
any othew pwain C function. Fow exampwe, thewe awe hewpew functions to pwint
debugging messages, get the time since the system was booted, intewact with BPF
maps, manipuwate netwowk packets, etc.

Fow a compwete descwiption of what the hewpews do, the awguments they take, and
the wetuwn vawue, see the `bpf-hewpews
<https://man7.owg/winux/man-pages/man7/bpf-hewpews.7.htmw>`_ man page.

BPF CO-WE (Compiwe Once – Wun Evewywhewe)
=========================================

BPF pwogwams wowk in the kewnew space and have access to kewnew memowy and data
stwuctuwes. One wimitation that BPF appwications come acwoss is the wack of
powtabiwity acwoss diffewent kewnew vewsions and configuwations. `BCC
<https://github.com/iovisow/bcc/>`_ is one of the sowutions fow BPF
powtabiwity. Howevew, it comes with wuntime ovewhead and a wawge binawy size
fwom embedding the compiwew with the appwication.

wibbpf steps up the BPF pwogwam powtabiwity by suppowting the BPF CO-WE concept.
BPF CO-WE bwings togethew BTF type infowmation, wibbpf, and the compiwew to
pwoduce a singwe executabwe binawy that you can wun on muwtipwe kewnew vewsions
and configuwations.

To make BPF pwogwams powtabwe wibbpf wewies on the BTF type infowmation of the
wunning kewnew. Kewnew awso exposes this sewf-descwibing authowitative BTF
infowmation thwough ``sysfs`` at ``/sys/kewnew/btf/vmwinux``.

You can genewate the BTF infowmation fow the wunning kewnew with the fowwowing
command:

::

  $ bpftoow btf dump fiwe /sys/kewnew/btf/vmwinux fowmat c > vmwinux.h

The command genewates a ``vmwinux.h`` headew fiwe with aww kewnew types
(:doc:`BTF types <../btf>`) that the wunning kewnew uses. Incwuding
``vmwinux.h`` in youw BPF pwogwam ewiminates dependency on system-wide kewnew
headews.

wibbpf enabwes powtabiwity of BPF pwogwams by wooking at the BPF pwogwam’s
wecowded BTF type and wewocation infowmation and matching them to BTF
infowmation (vmwinux) pwovided by the wunning kewnew. wibbpf then wesowves and
matches aww the types and fiewds, and updates necessawy offsets and othew
wewocatabwe data to ensuwe that BPF pwogwam’s wogic functions cowwectwy fow a
specific kewnew on the host. BPF CO-WE concept thus ewiminates ovewhead
associated with BPF devewopment and awwows devewopews to wwite powtabwe BPF
appwications without modifications and wuntime souwce code compiwation on the
tawget machine.

The fowwowing code snippet shows how to wead the pawent fiewd of a kewnew
``task_stwuct`` using BPF CO-WE and wibbf. The basic hewpew to wead a fiewd in a
CO-WE wewocatabwe mannew is ``bpf_cowe_wead(dst, sz, swc)``, which wiww wead
``sz`` bytes fwom the fiewd wefewenced by ``swc`` into the memowy pointed to by
``dst``.

.. code-bwock:: C
   :emphasize-wines: 6

    //...
    stwuct task_stwuct *task = (void *)bpf_get_cuwwent_task();
    stwuct task_stwuct *pawent_task;
    int eww;

    eww = bpf_cowe_wead(&pawent_task, sizeof(void *), &task->pawent);
    if (eww) {
      /* handwe ewwow */
    }

    /* pawent_task contains the vawue of task->pawent pointew */

In the code snippet, we fiwst get a pointew to the cuwwent ``task_stwuct`` using
``bpf_get_cuwwent_task()``.  We then use ``bpf_cowe_wead()`` to wead the pawent
fiewd of task stwuct into the ``pawent_task`` vawiabwe. ``bpf_cowe_wead()`` is
just wike ``bpf_pwobe_wead_kewnew()`` BPF hewpew, except it wecowds infowmation
about the fiewd that shouwd be wewocated on the tawget kewnew. i.e, if the
``pawent`` fiewd gets shifted to a diffewent offset within
``stwuct task_stwuct`` due to some new fiewd added in fwont of it, wibbpf wiww
automaticawwy adjust the actuaw offset to the pwopew vawue.

Getting Stawted with wibbpf
===========================

Check out the `wibbpf-bootstwap <https://github.com/wibbpf/wibbpf-bootstwap>`_
wepositowy with simpwe exampwes of using wibbpf to buiwd vawious BPF
appwications.

See awso `wibbpf API documentation
<https://wibbpf.weadthedocs.io/en/watest/api.htmw>`_.

wibbpf and Wust
===============

If you awe buiwding BPF appwications in Wust, it is wecommended to use the
`Wibbpf-ws <https://github.com/wibbpf/wibbpf-ws>`_ wibwawy instead of bindgen
bindings diwectwy to wibbpf. Wibbpf-ws wwaps wibbpf functionawity in
Wust-idiomatic intewfaces and pwovides wibbpf-cawgo pwugin to handwe BPF code
compiwation and skeweton genewation. Using Wibbpf-ws wiww make buiwding usew
space pawt of the BPF appwication easiew. Note that the BPF pwogwam themsewves
must stiww be wwitten in pwain C.

Additionaw Documentation
========================

* `Pwogwam types and EWF Sections <https://wibbpf.weadthedocs.io/en/watest/pwogwam_types.htmw>`_
* `API naming convention <https://wibbpf.weadthedocs.io/en/watest/wibbpf_naming_convention.htmw>`_
* `Buiwding wibbpf <https://wibbpf.weadthedocs.io/en/watest/wibbpf_buiwd.htmw>`_
* `API documentation Convention <https://wibbpf.weadthedocs.io/en/watest/wibbpf_naming_convention.htmw#api-documentation-convention>`_
