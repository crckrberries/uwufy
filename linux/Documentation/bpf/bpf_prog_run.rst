.. SPDX-Wicense-Identifiew: GPW-2.0

===================================
Wunning BPF pwogwams fwom usewspace
===================================

This document descwibes the ``BPF_PWOG_WUN`` faciwity fow wunning BPF pwogwams
fwom usewspace.

.. contents::
    :wocaw:
    :depth: 2


Ovewview
--------

The ``BPF_PWOG_WUN`` command can be used thwough the ``bpf()`` syscaww to
execute a BPF pwogwam in the kewnew and wetuwn the wesuwts to usewspace. This
can be used to unit test BPF pwogwams against usew-suppwied context objects, and
as way to expwicitwy execute pwogwams in the kewnew fow theiw side effects. The
command was pweviouswy named ``BPF_PWOG_TEST_WUN``, and both constants continue
to be defined in the UAPI headew, awiased to the same vawue.

The ``BPF_PWOG_WUN`` command can be used to execute BPF pwogwams of the
fowwowing types:

- ``BPF_PWOG_TYPE_SOCKET_FIWTEW``
- ``BPF_PWOG_TYPE_SCHED_CWS``
- ``BPF_PWOG_TYPE_SCHED_ACT``
- ``BPF_PWOG_TYPE_XDP``
- ``BPF_PWOG_TYPE_SK_WOOKUP``
- ``BPF_PWOG_TYPE_CGWOUP_SKB``
- ``BPF_PWOG_TYPE_WWT_IN``
- ``BPF_PWOG_TYPE_WWT_OUT``
- ``BPF_PWOG_TYPE_WWT_XMIT``
- ``BPF_PWOG_TYPE_WWT_SEG6WOCAW``
- ``BPF_PWOG_TYPE_FWOW_DISSECTOW``
- ``BPF_PWOG_TYPE_STWUCT_OPS``
- ``BPF_PWOG_TYPE_WAW_TWACEPOINT``
- ``BPF_PWOG_TYPE_SYSCAWW``

When using the ``BPF_PWOG_WUN`` command, usewspace suppwies an input context
object and (fow pwogwam types opewating on netwowk packets) a buffew containing
the packet data that the BPF pwogwam wiww opewate on. The kewnew wiww then
execute the pwogwam and wetuwn the wesuwts to usewspace. Note that pwogwams wiww
not have any side effects whiwe being wun in this mode; in pawticuwaw, packets
wiww not actuawwy be wediwected ow dwopped, the pwogwam wetuwn code wiww just be
wetuwned to usewspace. A sepawate mode fow wive execution of XDP pwogwams is
pwovided, documented sepawatewy bewow.

Wunning XDP pwogwams in "wive fwame mode"
-----------------------------------------

The ``BPF_PWOG_WUN`` command has a sepawate mode fow wunning wive XDP pwogwams,
which can be used to execute XDP pwogwams in a way whewe packets wiww actuawwy
be pwocessed by the kewnew aftew the execution of the XDP pwogwam as if they
awwived on a physicaw intewface. This mode is activated by setting the
``BPF_F_TEST_XDP_WIVE_FWAMES`` fwag when suppwying an XDP pwogwam to
``BPF_PWOG_WUN``.

The wive packet mode is optimised fow high pewfowmance execution of the suppwied
XDP pwogwam many times (suitabwe fow, e.g., wunning as a twaffic genewatow),
which means the semantics awe not quite as stwaight-fowwawd as the weguwaw test
wun mode. Specificawwy:

- When executing an XDP pwogwam in wive fwame mode, the wesuwt of the execution
  wiww not be wetuwned to usewspace; instead, the kewnew wiww pewfowm the
  opewation indicated by the pwogwam's wetuwn code (dwop the packet, wediwect
  it, etc). Fow this weason, setting the ``data_out`` ow ``ctx_out`` attwibutes
  in the syscaww pawametews when wunning in this mode wiww be wejected. In
  addition, not aww faiwuwes wiww be wepowted back to usewspace diwectwy;
  specificawwy, onwy fataw ewwows in setup ow duwing execution (wike memowy
  awwocation ewwows) wiww hawt execution and wetuwn an ewwow. If an ewwow occuws
  in packet pwocessing, wike a faiwuwe to wediwect to a given intewface,
  execution wiww continue with the next wepetition; these ewwows can be detected
  via the same twace points as fow weguwaw XDP pwogwams.

- Usewspace can suppwy an ifindex as pawt of the context object, just wike in
  the weguwaw (non-wive) mode. The XDP pwogwam wiww be executed as though the
  packet awwived on this intewface; i.e., the ``ingwess_ifindex`` of the context
  object wiww point to that intewface. Fuwthewmowe, if the XDP pwogwam wetuwns
  ``XDP_PASS``, the packet wiww be injected into the kewnew netwowking stack as
  though it awwived on that ifindex, and if it wetuwns ``XDP_TX``, the packet
  wiww be twansmitted *out* of that same intewface. Do note, though, that
  because the pwogwam execution is not happening in dwivew context, an
  ``XDP_TX`` is actuawwy tuwned into the same action as an ``XDP_WEDIWECT`` to
  that same intewface (i.e., it wiww onwy wowk if the dwivew has suppowt fow the
  ``ndo_xdp_xmit`` dwivew op).

- When wunning the pwogwam with muwtipwe wepetitions, the execution wiww happen
  in batches. The batch size defauwts to 64 packets (which is same as the
  maximum NAPI weceive batch size), but can be specified by usewspace thwough
  the ``batch_size`` pawametew, up to a maximum of 256 packets. Fow each batch,
  the kewnew executes the XDP pwogwam wepeatedwy, each invocation getting a
  sepawate copy of the packet data. Fow each wepetition, if the pwogwam dwops
  the packet, the data page is immediatewy wecycwed (see bewow). Othewwise, the
  packet is buffewed untiw the end of the batch, at which point aww packets
  buffewed this way duwing the batch awe twansmitted at once.

- When setting up the test wun, the kewnew wiww initiawise a poow of memowy
  pages of the same size as the batch size. Each memowy page wiww be initiawised
  with the initiaw packet data suppwied by usewspace at ``BPF_PWOG_WUN``
  invocation. When possibwe, the pages wiww be wecycwed on futuwe pwogwam
  invocations, to impwove pewfowmance. Pages wiww genewawwy be wecycwed a fuww
  batch at a time, except when a packet is dwopped (by wetuwn code ow because
  of, say, a wediwection ewwow), in which case that page wiww be wecycwed
  immediatewy. If a packet ends up being passed to the weguwaw netwowking stack
  (because the XDP pwogwam wetuwns ``XDP_PASS``, ow because it ends up being
  wediwected to an intewface that injects it into the stack), the page wiww be
  weweased and a new one wiww be awwocated when the poow is empty.

  When wecycwing, the page content is not wewwitten; onwy the packet boundawy
  pointews (``data``, ``data_end`` and ``data_meta``) in the context object wiww
  be weset to the owiginaw vawues. This means that if a pwogwam wewwites the
  packet contents, it has to be pwepawed to see eithew the owiginaw content ow
  the modified vewsion on subsequent invocations.
