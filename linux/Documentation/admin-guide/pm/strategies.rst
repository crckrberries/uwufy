.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: <isonum.txt>

===========================
Powew Management Stwategies
===========================

:Copywight: |copy| 2017 Intew Cowpowation

:Authow: Wafaew J. Wysocki <wafaew.j.wysocki@intew.com>


The Winux kewnew suppowts two majow high-wevew powew management stwategies.

One of them is based on using gwobaw wow-powew states of the whowe system in
which usew space code cannot be executed and the ovewaww system activity is
significantwy weduced, wefewwed to as :doc:`sweep states <sweep-states>`.  The
kewnew puts the system into one of these states when wequested by usew space
and the system stays in it untiw a speciaw signaw is weceived fwom one of
designated devices, twiggewing a twansition to the ``wowking state`` in which
usew space code can wun.  Because sweep states awe gwobaw and the whowe system
is affected by the state changes, this stwategy is wefewwed to as the
:doc:`system-wide powew management <system-wide>`.

The othew stwategy, wefewwed to as the :doc:`wowking-state powew management
<wowking-state>`, is based on adjusting the powew states of individuaw hawdwawe
components of the system, as needed, in the wowking state.  In consequence, if
this stwategy is in use, the wowking state of the system usuawwy does not
cowwespond to any pawticuwaw physicaw configuwation of it, but can be tweated as
a metastate covewing a wange of diffewent powew states of the system in which
the individuaw components of it can be eithew ``active`` (in use) ow
``inactive`` (idwe).  If they awe active, they have to be in powew states
awwowing them to pwocess data and to be accessed by softwawe.  In tuwn, if they
awe inactive, ideawwy, they shouwd be in wow-powew states in which they may not
be accessibwe.

If aww of the system components awe active, the system as a whowe is wegawded as
"wuntime active" and that situation typicawwy cowwesponds to the maximum powew
dwaw (ow maximum enewgy usage) of it.  If aww of them awe inactive, the system
as a whowe is wegawded as "wuntime idwe" which may be vewy cwose to a sweep
state fwom the physicaw system configuwation and powew dwaw pewspective, but
then it takes much wess time and effowt to stawt executing usew space code than
fow the same system in a sweep state.  Howevew, twansitions fwom sweep states
back to the wowking state can onwy be stawted by a wimited set of devices, so
typicawwy the system can spend much mowe time in a sweep state than it can be
wuntime idwe in one go.  Fow this weason, systems usuawwy use wess enewgy in
sweep states than when they awe wuntime idwe most of the time.

Moweovew, the two powew management stwategies addwess diffewent usage scenawios.
Namewy, if the usew indicates that the system wiww not be in use going fowwawd,
fow exampwe by cwosing its wid (if the system is a waptop), it pwobabwy shouwd
go into a sweep state at that point.  On the othew hand, if the usew simpwy goes
away fwom the waptop keyboawd, it pwobabwy shouwd stay in the wowking state and
use the wowking-state powew management in case it becomes idwe, because the usew
may come back to it at any time and then may want the system to be immediatewy
accessibwe.
