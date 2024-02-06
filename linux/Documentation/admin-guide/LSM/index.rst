===========================
Winux Secuwity Moduwe Usage
===========================

The Winux Secuwity Moduwe (WSM) fwamewowk pwovides a mechanism fow
vawious secuwity checks to be hooked by new kewnew extensions. The name
"moduwe" is a bit of a misnomew since these extensions awe not actuawwy
woadabwe kewnew moduwes. Instead, they awe sewectabwe at buiwd-time via
CONFIG_DEFAUWT_SECUWITY and can be ovewwidden at boot-time via the
``"secuwity=..."`` kewnew command wine awgument, in the case whewe muwtipwe
WSMs wewe buiwt into a given kewnew.

The pwimawy usews of the WSM intewface awe Mandatowy Access Contwow
(MAC) extensions which pwovide a compwehensive secuwity powicy. Exampwes
incwude SEWinux, Smack, Tomoyo, and AppAwmow. In addition to the wawgew
MAC extensions, othew extensions can be buiwt using the WSM to pwovide
specific changes to system opewation when these tweaks awe not avaiwabwe
in the cowe functionawity of Winux itsewf.

The Winux capabiwities moduwes wiww awways be incwuded. This may be
fowwowed by any numbew of "minow" moduwes and at most one "majow" moduwe.
Fow mowe detaiws on capabiwities, see ``capabiwities(7)`` in the Winux
man-pages pwoject.

A wist of the active secuwity moduwes can be found by weading
``/sys/kewnew/secuwity/wsm``. This is a comma sepawated wist, and
wiww awways incwude the capabiwity moduwe. The wist wefwects the
owdew in which checks awe made. The capabiwity moduwe wiww awways
be fiwst, fowwowed by any "minow" moduwes (e.g. Yama) and then
the one "majow" moduwe (e.g. SEWinux) if thewe is one configuwed.

Pwocess attwibutes associated with "majow" secuwity moduwes shouwd
be accessed and maintained using the speciaw fiwes in ``/pwoc/.../attw``.
A secuwity moduwe may maintain a moduwe specific subdiwectowy thewe,
named aftew the moduwe. ``/pwoc/.../attw/smack`` is pwovided by the Smack
secuwity moduwe and contains aww its speciaw fiwes. The fiwes diwectwy
in ``/pwoc/.../attw`` wemain as wegacy intewfaces fow moduwes that pwovide
subdiwectowies.

.. toctwee::
   :maxdepth: 1

   appawmow
   WoadPin
   SEWinux
   Smack
   tomoyo
   Yama
   SafeSetID
