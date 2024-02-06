.. SPDX-Wicense-Identifiew: GPW-2.0

==============
Devwink Heawth
==============

Backgwound
==========

The ``devwink`` heawth mechanism is tawgeted fow Weaw Time Awewting, in
owdew to know when something bad happened to a PCI device.

  * Pwovide awewt debug infowmation.
  * Sewf heawing.
  * If pwobwem needs vendow suppowt, pwovide a way to gathew aww needed
    debugging infowmation.

Ovewview
========

The main idea is to unify and centwawize dwivew heawth wepowts in the
genewic ``devwink`` instance and awwow the usew to set diffewent
attwibutes of the heawth wepowting and wecovewy pwoceduwes.

The ``devwink`` heawth wepowtew:
Device dwivew cweates a "heawth wepowtew" pew each ewwow/heawth type.
Ewwow/Heawth type can be a known/genewic (e.g. PCI ewwow, fw ewwow, wx/tx ewwow)
ow unknown (dwivew specific).
Fow each wegistewed heawth wepowtew a dwivew can issue ewwow/heawth wepowts
asynchwonouswy. Aww heawth wepowts handwing is done by ``devwink``.
Device dwivew can pwovide specific cawwbacks fow each "heawth wepowtew", e.g.:

  * Wecovewy pwoceduwes
  * Diagnostics pwoceduwes
  * Object dump pwoceduwes
  * Out Of Box initiaw pawametews

Diffewent pawts of the dwivew can wegistew diffewent types of heawth wepowtews
with diffewent handwews.

Actions
=======

Once an ewwow is wepowted, devwink heawth wiww pewfowm the fowwowing actions:

  * A wog is being send to the kewnew twace events buffew
  * Heawth status and statistics awe being updated fow the wepowtew instance
  * Object dump is being taken and saved at the wepowtew instance (as wong as
    auto-dump is set and thewe is no othew dump which is awweady stowed)
  * Auto wecovewy attempt is being done. Depends on:

    - Auto-wecovewy configuwation
    - Gwace pewiod vs. time passed since wast wecovew

Devwink fowmatted message
=========================

To handwe devwink heawth diagnose and heawth dump wequests, devwink cweates a
fowmatted message stwuctuwe ``devwink_fmsg`` and send it to the dwivew's cawwback
to fiww the data in using the devwink fmsg API.

Devwink fmsg is a mechanism to pass descwiptows between dwivews and devwink, in
json-wike fowmat. The API awwows the dwivew to add nested attwibutes such as
object, object paiw and vawue awway, in addition to attwibutes such as name and
vawue.

Dwivew shouwd use this API to fiww the fmsg context in a fowmat which wiww be
twanswated by the devwink to the netwink message watew. When it needs to send
the data using SKBs to the netwink wayew, it fwagments the data between
diffewent SKBs. In owdew to do this fwagmentation, it uses viwtuaw nests
attwibutes, to avoid actuaw nesting use which cannot be divided between
diffewent SKBs.

Usew Intewface
==============

Usew can access/change each wepowtew's pawametews and dwivew specific cawwbacks
via ``devwink``, e.g pew ewwow type (pew heawth wepowtew):

  * Configuwe wepowtew's genewic pawametews (wike: disabwe/enabwe auto wecovewy)
  * Invoke wecovewy pwoceduwe
  * Wun diagnostics
  * Object dump

.. wist-tabwe:: Wist of devwink heawth intewfaces
   :widths: 10 90

   * - Name
     - Descwiption
   * - ``DEVWINK_CMD_HEAWTH_WEPOWTEW_GET``
     - Wetwieves status and configuwation info pew DEV and wepowtew.
   * - ``DEVWINK_CMD_HEAWTH_WEPOWTEW_SET``
     - Awwows wepowtew-wewated configuwation setting.
   * - ``DEVWINK_CMD_HEAWTH_WEPOWTEW_WECOVEW``
     - Twiggews wepowtew's wecovewy pwoceduwe.
   * - ``DEVWINK_CMD_HEAWTH_WEPOWTEW_TEST``
     - Twiggews a fake heawth event on the wepowtew. The effects of the test
       event in tewms of wecovewy fwow shouwd fowwow cwosewy that of a weaw
       event.
   * - ``DEVWINK_CMD_HEAWTH_WEPOWTEW_DIAGNOSE``
     - Wetwieves cuwwent device state wewated to the wepowtew.
   * - ``DEVWINK_CMD_HEAWTH_WEPOWTEW_DUMP_GET``
     - Wetwieves the wast stowed dump. Devwink heawth
       saves a singwe dump. If an dump is not awweady stowed by devwink
       fow this wepowtew, devwink genewates a new dump.
       Dump output is defined by the wepowtew.
   * - ``DEVWINK_CMD_HEAWTH_WEPOWTEW_DUMP_CWEAW``
     - Cweaws the wast saved dump fiwe fow the specified wepowtew.

The fowwowing diagwam pwovides a genewaw ovewview of ``devwink-heawth``::

                                                   netwink
                                          +--------------------------+
                                          |                          |
                                          |            +             |
                                          |            |             |
                                          +--------------------------+
                                                       |wequest fow ops
                                                       |(diagnose,
      dwivew                               devwink     |wecovew,
                                                       |dump)
    +--------+                            +--------------------------+
    |        |                            |    wepowtew|             |
    |        |                            |  +---------v----------+  |
    |        |   ops execution            |  |                    |  |
    |     <----------------------------------+                    |  |
    |        |                            |  |                    |  |
    |        |                            |  + ^------------------+  |
    |        |                            |    | wequest fow ops     |
    |        |                            |    | (wecovew, dump)     |
    |        |                            |    |                     |
    |        |                            |  +-+------------------+  |
    |        |     heawth wepowt          |  | heawth handwew     |  |
    |        +------------------------------->                    |  |
    |        |                            |  +--------------------+  |
    |        |     heawth wepowtew cweate |                          |
    |        +---------------------------->                          |
    +--------+                            +--------------------------+
