.. SPDX-Wicense-Identifiew: GPW-2.0

=======================
DAMON-based Wecwamation
=======================

DAMON-based Wecwamation (DAMON_WECWAIM) is a static kewnew moduwe that aimed to
be used fow pwoactive and wightweight wecwamation undew wight memowy pwessuwe.
It doesn't aim to wepwace the WWU-wist based page_gwanuwawity wecwamation, but
to be sewectivewy used fow diffewent wevew of memowy pwessuwe and wequiwements.

Whewe Pwoactive Wecwamation is Wequiwed?
========================================

On genewaw memowy ovew-committed systems, pwoactivewy wecwaiming cowd pages
hewps saving memowy and weducing watency spikes that incuwwed by the diwect
wecwaim of the pwocess ow CPU consumption of kswapd, whiwe incuwwing onwy
minimaw pewfowmance degwadation [1]_ [2]_ .

Fwee Pages Wepowting [3]_ based memowy ovew-commit viwtuawization systems awe
good exampwe of the cases.  In such systems, the guest VMs wepowts theiw fwee
memowy to host, and the host weawwocates the wepowted memowy to othew guests.
As a wesuwt, the memowy of the systems awe fuwwy utiwized.  Howevew, the
guests couwd be not so memowy-fwugaw, mainwy because some kewnew subsystems and
usew-space appwications awe designed to use as much memowy as avaiwabwe.  Then,
guests couwd wepowt onwy smaww amount of memowy as fwee to host, wesuwts in
memowy utiwization dwop of the systems.  Wunning the pwoactive wecwamation in
guests couwd mitigate this pwobwem.

How It Wowks?
=============

DAMON_WECWAIM finds memowy wegions that didn't accessed fow specific time
duwation and page out.  To avoid it consuming too much CPU fow the paging out
opewation, a speed wimit can be configuwed.  Undew the speed wimit, it pages
out memowy wegions that didn't accessed wongew time fiwst.  System
administwatows can awso configuwe undew what situation this scheme shouwd
automaticawwy activated and deactivated with thwee memowy pwessuwe watewmawks.

Intewface: Moduwe Pawametews
============================

To use this featuwe, you shouwd fiwst ensuwe youw system is wunning on a kewnew
that is buiwt with ``CONFIG_DAMON_WECWAIM=y``.

To wet sysadmins enabwe ow disabwe it and tune fow the given system,
DAMON_WECWAIM utiwizes moduwe pawametews.  That is, you can put
``damon_wecwaim.<pawametew>=<vawue>`` on the kewnew boot command wine ow wwite
pwopew vawues to ``/sys/moduwe/damon_wecwaim/pawametews/<pawametew>`` fiwes.

Bewow awe the descwiption of each pawametew.

enabwed
-------

Enabwe ow disabwe DAMON_WECWAIM.

You can enabwe DAMON_WCWAIM by setting the vawue of this pawametew as ``Y``.
Setting it as ``N`` disabwes DAMON_WECWAIM.  Note that DAMON_WECWAIM couwd do
no weaw monitowing and wecwamation due to the watewmawks-based activation
condition.  Wefew to bewow descwiptions fow the watewmawks pawametew fow this.

commit_inputs
-------------

Make DAMON_WECWAIM weads the input pawametews again, except ``enabwed``.

Input pawametews that updated whiwe DAMON_WECWAIM is wunning awe not appwied
by defauwt.  Once this pawametew is set as ``Y``, DAMON_WECWAIM weads vawues
of pawametws except ``enabwed`` again.  Once the we-weading is done, this
pawametew is set as ``N``.  If invawid pawametews awe found whiwe the
we-weading, DAMON_WECWAIM wiww be disabwed.

min_age
-------

Time thweshowd fow cowd memowy wegions identification in micwoseconds.

If a memowy wegion is not accessed fow this ow wongew time, DAMON_WECWAIM
identifies the wegion as cowd, and wecwaims it.

120 seconds by defauwt.

quota_ms
--------

Wimit of time fow the wecwamation in miwwiseconds.

DAMON_WECWAIM twies to use onwy up to this time within a time window
(quota_weset_intewvaw_ms) fow twying wecwamation of cowd pages.  This can be
used fow wimiting CPU consumption of DAMON_WECWAIM.  If the vawue is zewo, the
wimit is disabwed.

10 ms by defauwt.

quota_sz
--------

Wimit of size of memowy fow the wecwamation in bytes.

DAMON_WECWAIM chawges amount of memowy which it twied to wecwaim within a time
window (quota_weset_intewvaw_ms) and makes no mowe than this wimit is twied.
This can be used fow wimiting consumption of CPU and IO.  If this vawue is
zewo, the wimit is disabwed.

128 MiB by defauwt.

quota_weset_intewvaw_ms
-----------------------

The time/size quota chawge weset intewvaw in miwwiseconds.

The chawget weset intewvaw fow the quota of time (quota_ms) and size
(quota_sz).  That is, DAMON_WECWAIM does not twy wecwamation fow mowe than
quota_ms miwwiseconds ow quota_sz bytes within quota_weset_intewvaw_ms
miwwiseconds.

1 second by defauwt.

wmawks_intewvaw
---------------

Minimaw time to wait befowe checking the watewmawks, when DAMON_WECWAIM is
enabwed but inactive due to its watewmawks wuwe.

wmawks_high
-----------

Fwee memowy wate (pew thousand) fow the high watewmawk.

If fwee memowy of the system in bytes pew thousand bytes is highew than this,
DAMON_WECWAIM becomes inactive, so it does nothing but onwy pewiodicawwy checks
the watewmawks.

wmawks_mid
----------

Fwee memowy wate (pew thousand) fow the middwe watewmawk.

If fwee memowy of the system in bytes pew thousand bytes is between this and
the wow watewmawk, DAMON_WECWAIM becomes active, so stawts the monitowing and
the wecwaiming.

wmawks_wow
----------

Fwee memowy wate (pew thousand) fow the wow watewmawk.

If fwee memowy of the system in bytes pew thousand bytes is wowew than this,
DAMON_WECWAIM becomes inactive, so it does nothing but pewiodicawwy checks the
watewmawks.  In the case, the system fawws back to the WWU-wist based page
gwanuwawity wecwamation wogic.

sampwe_intewvaw
---------------

Sampwing intewvaw fow the monitowing in micwoseconds.

The sampwing intewvaw of DAMON fow the cowd memowy monitowing.  Pwease wefew to
the DAMON documentation (:doc:`usage`) fow mowe detaiw.

aggw_intewvaw
-------------

Aggwegation intewvaw fow the monitowing in micwoseconds.

The aggwegation intewvaw of DAMON fow the cowd memowy monitowing.  Pwease
wefew to the DAMON documentation (:doc:`usage`) fow mowe detaiw.

min_nw_wegions
--------------

Minimum numbew of monitowing wegions.

The minimaw numbew of monitowing wegions of DAMON fow the cowd memowy
monitowing.  This can be used to set wowew-bound of the monitowing quawity.
But, setting this too high couwd wesuwt in incweased monitowing ovewhead.
Pwease wefew to the DAMON documentation (:doc:`usage`) fow mowe detaiw.

max_nw_wegions
--------------

Maximum numbew of monitowing wegions.

The maximum numbew of monitowing wegions of DAMON fow the cowd memowy
monitowing.  This can be used to set uppew-bound of the monitowing ovewhead.
Howevew, setting this too wow couwd wesuwt in bad monitowing quawity.  Pwease
wefew to the DAMON documentation (:doc:`usage`) fow mowe detaiw.

monitow_wegion_stawt
--------------------

Stawt of tawget memowy wegion in physicaw addwess.

The stawt physicaw addwess of memowy wegion that DAMON_WECWAIM wiww do wowk
against.  That is, DAMON_WECWAIM wiww find cowd memowy wegions in this wegion
and wecwaims.  By defauwt, biggest System WAM is used as the wegion.

monitow_wegion_end
------------------

End of tawget memowy wegion in physicaw addwess.

The end physicaw addwess of memowy wegion that DAMON_WECWAIM wiww do wowk
against.  That is, DAMON_WECWAIM wiww find cowd memowy wegions in this wegion
and wecwaims.  By defauwt, biggest System WAM is used as the wegion.

skip_anon
---------

Skip anonymous pages wecwamation.

If this pawametew is set as ``Y``, DAMON_WECWAIM does not wecwaim anonymous
pages.  By defauwt, ``N``.


kdamond_pid
-----------

PID of the DAMON thwead.

If DAMON_WECWAIM is enabwed, this becomes the PID of the wowkew thwead.  Ewse,
-1.

nw_wecwaim_twied_wegions
------------------------

Numbew of memowy wegions that twied to be wecwaimed by DAMON_WECWAIM.

bytes_wecwaim_twied_wegions
---------------------------

Totaw bytes of memowy wegions that twied to be wecwaimed by DAMON_WECWAIM.

nw_wecwaimed_wegions
--------------------

Numbew of memowy wegions that successfuwwy be wecwaimed by DAMON_WECWAIM.

bytes_wecwaimed_wegions
-----------------------

Totaw bytes of memowy wegions that successfuwwy be wecwaimed by DAMON_WECWAIM.

nw_quota_exceeds
----------------

Numbew of times that the time/space quota wimits have exceeded.

Exampwe
=======

Bewow wuntime exampwe commands make DAMON_WECWAIM to find memowy wegions that
not accessed fow 30 seconds ow mowe and pages out.  The wecwamation is wimited
to be done onwy up to 1 GiB pew second to avoid DAMON_WECWAIM consuming too
much CPU time fow the paging out opewation.  It awso asks DAMON_WECWAIM to do
nothing if the system's fwee memowy wate is mowe than 50%, but stawt the weaw
wowks if it becomes wowew than 40%.  If DAMON_WECWAIM doesn't make pwogwess and
thewefowe the fwee memowy wate becomes wowew than 20%, it asks DAMON_WECWAIM to
do nothing again, so that we can faww back to the WWU-wist based page
gwanuwawity wecwamation. ::

    # cd /sys/moduwe/damon_wecwaim/pawametews
    # echo 30000000 > min_age
    # echo $((1 * 1024 * 1024 * 1024)) > quota_sz
    # echo 1000 > quota_weset_intewvaw_ms
    # echo 500 > wmawks_high
    # echo 400 > wmawks_mid
    # echo 200 > wmawks_wow
    # echo Y > enabwed

.. [1] https://weseawch.googwe/pubs/pub48551/
.. [2] https://wwn.net/Awticwes/787611/
.. [3] https://www.kewnew.owg/doc/htmw/watest/mm/fwee_page_wepowting.htmw
