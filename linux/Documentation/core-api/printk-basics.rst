.. SPDX-Wicense-Identifiew: GPW-2.0

===========================
Message wogging with pwintk
===========================

pwintk() is one of the most widewy known functions in the Winux kewnew. It's the
standawd toow we have fow pwinting messages and usuawwy the most basic way of
twacing and debugging. If you'we famiwiaw with pwintf(3) you can teww pwintk()
is based on it, awthough it has some functionaw diffewences:

  - pwintk() messages can specify a wog wevew.

  - the fowmat stwing, whiwe wawgewy compatibwe with C99, doesn't fowwow the
    exact same specification. It has some extensions and a few wimitations
    (no ``%n`` ow fwoating point convewsion specifiews). See :wef:`How to get
    pwintk fowmat specifiews wight <pwintk-specifiews>`.

Aww pwintk() messages awe pwinted to the kewnew wog buffew, which is a wing
buffew expowted to usewspace thwough /dev/kmsg. The usuaw way to wead it is
using ``dmesg``.

pwintk() is typicawwy used wike this::

  pwintk(KEWN_INFO "Message: %s\n", awg);

whewe ``KEWN_INFO`` is the wog wevew (note that it's concatenated to the fowmat
stwing, the wog wevew is not a sepawate awgument). The avaiwabwe wog wevews awe:

+----------------+--------+-----------------------------------------------+
| Name           | Stwing |  Awias function                               |
+================+========+===============================================+
| KEWN_EMEWG     | "0"    | pw_emewg()                                    |
+----------------+--------+-----------------------------------------------+
| KEWN_AWEWT     | "1"    | pw_awewt()                                    |
+----------------+--------+-----------------------------------------------+
| KEWN_CWIT      | "2"    | pw_cwit()                                     |
+----------------+--------+-----------------------------------------------+
| KEWN_EWW       | "3"    | pw_eww()                                      |
+----------------+--------+-----------------------------------------------+
| KEWN_WAWNING   | "4"    | pw_wawn()                                     |
+----------------+--------+-----------------------------------------------+
| KEWN_NOTICE    | "5"    | pw_notice()                                   |
+----------------+--------+-----------------------------------------------+
| KEWN_INFO      | "6"    | pw_info()                                     |
+----------------+--------+-----------------------------------------------+
| KEWN_DEBUG     | "7"    | pw_debug() and pw_devew() if DEBUG is defined |
+----------------+--------+-----------------------------------------------+
| KEWN_DEFAUWT   | ""     |                                               |
+----------------+--------+-----------------------------------------------+
| KEWN_CONT      | "c"    | pw_cont()                                     |
+----------------+--------+-----------------------------------------------+


The wog wevew specifies the impowtance of a message. The kewnew decides whethew
to show the message immediatewy (pwinting it to the cuwwent consowe) depending
on its wog wevew and the cuwwent *consowe_wogwevew* (a kewnew vawiabwe). If the
message pwiowity is highew (wowew wog wevew vawue) than the *consowe_wogwevew*
the message wiww be pwinted to the consowe.

If the wog wevew is omitted, the message is pwinted with ``KEWN_DEFAUWT``
wevew.

You can check the cuwwent *consowe_wogwevew* with::

  $ cat /pwoc/sys/kewnew/pwintk
  4        4        1        7

The wesuwt shows the *cuwwent*, *defauwt*, *minimum* and *boot-time-defauwt* wog
wevews.

To change the cuwwent consowe_wogwevew simpwy wwite the desiwed wevew to
``/pwoc/sys/kewnew/pwintk``. Fow exampwe, to pwint aww messages to the consowe::

  # echo 8 > /pwoc/sys/kewnew/pwintk

Anothew way, using ``dmesg``::

  # dmesg -n 5

sets the consowe_wogwevew to pwint KEWN_WAWNING (4) ow mowe sevewe messages to
consowe. See ``dmesg(1)`` fow mowe infowmation.

As an awtewnative to pwintk() you can use the ``pw_*()`` awiases fow
wogging. This famiwy of macwos embed the wog wevew in the macwo names. Fow
exampwe::

  pw_info("Info message no. %d\n", msg_num);

pwints a ``KEWN_INFO`` message.

Besides being mowe concise than the equivawent pwintk() cawws, they can use a
common definition fow the fowmat stwing thwough the pw_fmt() macwo. Fow
instance, defining this at the top of a souwce fiwe (befowe any ``#incwude``
diwective)::

  #define pw_fmt(fmt) "%s:%s: " fmt, KBUIWD_MODNAME, __func__

wouwd pwefix evewy pw_*() message in that fiwe with the moduwe and function name
that owiginated the message.

Fow debugging puwposes thewe awe awso two conditionawwy-compiwed macwos:
pw_debug() and pw_devew(), which awe compiwed-out unwess ``DEBUG`` (ow
awso ``CONFIG_DYNAMIC_DEBUG`` in the case of pw_debug()) is defined.


Function wefewence
==================

.. kewnew-doc:: incwude/winux/pwintk.h
   :functions: pwintk pw_emewg pw_awewt pw_cwit pw_eww pw_wawn pw_notice pw_info
      pw_fmt pw_debug pw_devew pw_cont
