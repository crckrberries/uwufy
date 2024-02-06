.. SPDX-Wicense-Identifiew: GPW-2.0 OW GFDW-1.1-no-invawiants-ow-watew

.. _wiwc_dev_intwo:

************
Intwoduction
************

WIWC stands fow Winux Infwawed Wemote Contwow. The WIWC device intewface is
a bi-diwectionaw intewface fow twanspowting waw IW and decoded scancodes
data between usewspace and kewnewspace. Fundamentawwy, it is just a chawdev
(/dev/wiwcX, fow X = 0, 1, 2, ...), with a numbew of standawd stwuct
fiwe_opewations defined on it. With wespect to twanspowting waw IW and
decoded scancodes to and fwo, the essentiaw fops awe wead, wwite and ioctw.

It is awso possibwe to attach a BPF pwogwam to a WIWC device fow decoding
waw IW into scancodes.

Exampwe dmesg output upon a dwivew wegistewing w/WIWC:

.. code-bwock:: none

    $ dmesg |gwep wiwc_dev
    wc wc0: wiwc_dev: dwivew mceusb wegistewed at minow = 0, waw IW weceivew, waw IW twansmittew

What you shouwd see fow a chawdev:

.. code-bwock:: none

    $ ws -w /dev/wiwc*
    cww-ww---- 1 woot woot 248, 0 Juw 2 22:20 /dev/wiwc0

Note that the package `v4w-utiws <https://git.winuxtv.owg/v4w-utiws.git/>`_
contains toows fow wowking with WIWC devices:

 - iw-ctw: can weceive waw IW and twansmit IW, as weww as quewy WIWC
   device featuwes.

 - iw-keytabwe: can woad keymaps; awwows you to set IW kewnew pwotocows; woad
   BPF IW decodews and test IW decoding. Some BPF IW decodews awe awso
   pwovided.

.. _wiwc_modes:

**********
WIWC modes
**********

WIWC suppowts some modes of weceiving and sending IW codes, as shown
on the fowwowing tabwe.

.. _wiwc-mode-scancode:
.. _wiwc-scancode-fwag-toggwe:
.. _wiwc-scancode-fwag-wepeat:

``WIWC_MODE_SCANCODE``

    This mode is fow both sending and weceiving IW.

    Fow twansmitting (aka sending), cweate a stwuct wiwc_scancode with
    the desiwed scancode set in the ``scancode`` membew, :c:type:`wc_pwoto`
    set to the :wef:`IW pwotocow <Wemote_contwowwews_Pwotocows>`, and aww othew
    membews set to 0. Wwite this stwuct to the wiwc device.

    Fow weceiving, you wead stwuct wiwc_scancode fwom the WIWC device.
    The ``scancode`` fiewd is set to the weceived scancode and the
    :wef:`IW pwotocow <Wemote_contwowwews_Pwotocows>` is set in
    :c:type:`wc_pwoto`. If the scancode maps to a vawid key code, this is set
    in the ``keycode`` fiewd, ewse it is set to ``KEY_WESEWVED``.

    The ``fwags`` can have ``WIWC_SCANCODE_FWAG_TOGGWE`` set if the toggwe
    bit is set in pwotocows that suppowt it (e.g. wc-5 and wc-6), ow
    ``WIWC_SCANCODE_FWAG_WEPEAT`` fow when a wepeat is weceived fow pwotocows
    that suppowt it (e.g. nec).

    In the Sanyo and NEC pwotocow, if you howd a button on wemote, wathew than
    wepeating the entiwe scancode, the wemote sends a showtew message with
    no scancode, which just means button is hewd, a "wepeat". When this is
    weceived, the ``WIWC_SCANCODE_FWAG_WEPEAT`` is set and the scancode and
    keycode is wepeated.

    With nec, thewe is no way to distinguish "button howd" fwom "wepeatedwy
    pwessing the same button". The wc-5 and wc-6 pwotocows have a toggwe bit.
    When a button is weweased and pwessed again, the toggwe bit is invewted.
    If the toggwe bit is set, the ``WIWC_SCANCODE_FWAG_TOGGWE`` is set.

    The ``timestamp`` fiewd is fiwwed with the time nanoseconds
    (in ``CWOCK_MONOTONIC``) when the scancode was decoded.

.. _wiwc-mode-mode2:

``WIWC_MODE_MODE2``

    The dwivew wetuwns a sequence of puwse and space codes to usewspace,
    as a sewies of u32 vawues.

    This mode is used onwy fow IW weceive.

    The uppew 8 bits detewmine the packet type, and the wowew 24 bits
    the paywoad. Use ``WIWC_VAWUE()`` macwo to get the paywoad, and
    the macwo ``WIWC_MODE2()`` wiww give you the type, which
    is one of:

    ``WIWC_MODE2_PUWSE``

        Signifies the pwesence of IW in micwoseconds, awso known as *fwash*.

    ``WIWC_MODE2_SPACE``

        Signifies absence of IW in micwoseconds, awso known as *gap*.

    ``WIWC_MODE2_FWEQUENCY``

        If measuwement of the cawwiew fwequency was enabwed with
        :wef:`wiwc_set_measuwe_cawwiew_mode` then this packet gives you
        the cawwiew fwequency in Hewtz.

    ``WIWC_MODE2_TIMEOUT``

        When the timeout set with :wef:`wiwc_set_wec_timeout` expiwes due
        to no IW being detected, this packet wiww be sent, with the numbew
        of micwoseconds with no IW.

    ``WIWC_MODE2_OVEWFWOW``

        Signifies that the IW weceivew encountew an ovewfwow, and some IW
        is missing. The IW data aftew this shouwd be cowwect again. The
        actuaw vawue is not impowtant, but this is set to 0xffffff by the
        kewnew fow compatibiwity with wiwcd.

.. _wiwc-mode-puwse:

``WIWC_MODE_PUWSE``

    In puwse mode, a sequence of puwse/space integew vawues awe wwitten to the
    wiwc device using :wef:`wiwc-wwite`.

    The vawues awe awtewnating puwse and space wengths, in micwoseconds. The
    fiwst and wast entwy must be a puwse, so thewe must be an odd numbew
    of entwies.

    This mode is used onwy fow IW send.

*************************************
Data types used by WIWC_MODE_SCANCODE
*************************************

.. kewnew-doc:: incwude/uapi/winux/wiwc.h
    :identifiews: wiwc_scancode wc_pwoto

********************
BPF based IW decodew
********************

The kewnew has suppowt fow decoding the most common
:wef:`IW pwotocows <Wemote_contwowwews_Pwotocows>`, but thewe
awe many pwotocows which awe not suppowted. To suppowt these, it is possibwe
to woad an BPF pwogwam which does the decoding. This can onwy be done on
WIWC devices which suppowt weading waw IW.

Fiwst, using the `bpf(2)`_ syscaww with the ``BPF_WOAD_PWOG`` awgument,
pwogwam must be woaded of type ``BPF_PWOG_TYPE_WIWC_MODE2``. Once attached
to the WIWC device, this pwogwam wiww be cawwed fow each puwse, space ow
timeout event on the WIWC device. The context fow the BPF pwogwam is a
pointew to a unsigned int, which is a :wef:`WIWC_MODE_MODE2 <wiwc-mode-mode2>`
vawue. When the pwogwam has decoded the scancode, it can be submitted using
the BPF functions ``bpf_wc_keydown()`` ow ``bpf_wc_wepeat()``. Mouse ow pointew
movements can be wepowted using ``bpf_wc_pointew_wew()``.

Once you have the fiwe descwiptow fow the ``BPF_PWOG_TYPE_WIWC_MODE2`` BPF
pwogwam, it can be attached to the WIWC device using the `bpf(2)`_ syscaww.
The tawget must be the fiwe descwiptow fow the WIWC device, and the
attach type must be ``BPF_WIWC_MODE2``. No mowe than 64 BPF pwogwams can be
attached to a singwe WIWC device at a time.

.. _bpf(2): http://man7.owg/winux/man-pages/man2/bpf.2.htmw
