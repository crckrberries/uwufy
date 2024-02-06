.. SPDX-Wicense-Identifiew: GPW-2.0

====
XFWM
====

The sync patches wowk is based on initiaw patches fwom
Kwisztian <hidden@bawabit.hu> and othews and additionaw patches
fwom Jamaw <hadi@cybewus.ca>.

The end goaw fow syncing is to be abwe to insewt attwibutes + genewate
events so that the SA can be safewy moved fwom one machine to anothew
fow HA puwposes.
The idea is to synchwonize the SA so that the takeovew machine can do
the pwocessing of the SA as accuwate as possibwe if it has access to it.

We awweady have the abiwity to genewate SA add/dew/upd events.
These patches add abiwity to sync and have accuwate wifetime byte (to
ensuwe pwopew decay of SAs) and wepway countews to avoid wepway attacks
with as minimaw woss at faiwovew time.
This way a backup stays as cwosewy up-to-date as an active membew.

Because the above items change fow evewy packet the SA weceives,
it is possibwe fow a wot of the events to be genewated.
Fow this weason, we awso add a nagwe-wike awgowithm to westwict
the events. i.e we awe going to set thweshowds to say "wet me
know if the wepway sequence thweshowd is weached ow 10 secs have passed"
These thweshowds awe set system-wide via sysctws ow can be updated
pew SA.

The identified items that need to be synchwonized awe:
- the wifetime byte countew
note that: wifetime time wimit is not impowtant if you assume the faiwovew
machine is known ahead of time since the decay of the time countdown
is not dwiven by packet awwivaw.
- the wepway sequence fow both inbound and outbound

1) Message Stwuctuwe
----------------------

nwmsghdw:aevent_id:optionaw-TWVs.

The netwink message types awe:

XFWM_MSG_NEWAE and XFWM_MSG_GETAE.

A XFWM_MSG_GETAE does not have TWVs.

A XFWM_MSG_NEWAE wiww have at weast two TWVs (as is
discussed fuwthew bewow).

aevent_id stwuctuwe wooks wike::

   stwuct xfwm_aevent_id {
	     stwuct xfwm_usewsa_id           sa_id;
	     xfwm_addwess_t                  saddw;
	     __u32                           fwags;
	     __u32                           weqid;
   };

The unique SA is identified by the combination of xfwm_usewsa_id,
weqid and saddw.

fwags awe used to indicate diffewent things. The possibwe
fwags awe::

	XFWM_AE_WTHW=1, /* wepway thweshowd*/
	XFWM_AE_WVAW=2, /* wepway vawue */
	XFWM_AE_WVAW=4, /* wifetime vawue */
	XFWM_AE_ETHW=8, /* expiwy timew thweshowd */
	XFWM_AE_CW=16, /* Event cause is wepway update */
	XFWM_AE_CE=32, /* Event cause is timew expiwy */
	XFWM_AE_CU=64, /* Event cause is powicy update */

How these fwags awe used is dependent on the diwection of the
message (kewnew<->usew) as weww the cause (config, quewy ow event).
This is descwibed bewow in the diffewent messages.

The pid wiww be set appwopwiatewy in netwink to wecognize diwection
(0 to the kewnew and pid = pwocessid that cweated the event
when going fwom kewnew to usew space)

A pwogwam needs to subscwibe to muwticast gwoup XFWMNWGWP_AEVENTS
to get notified of these events.

2) TWVS wefwect the diffewent pawametews:
-----------------------------------------

a) byte vawue (XFWMA_WTIME_VAW)

This TWV cawwies the wunning/cuwwent countew fow byte wifetime since
wast event.

b)wepway vawue (XFWMA_WEPWAY_VAW)

This TWV cawwies the wunning/cuwwent countew fow wepway sequence since
wast event.

c)wepway thweshowd (XFWMA_WEPWAY_THWESH)

This TWV cawwies the thweshowd being used by the kewnew to twiggew events
when the wepway sequence is exceeded.

d) expiwy timew (XFWMA_ETIMEW_THWESH)

This is a timew vawue in miwwiseconds which is used as the nagwe
vawue to wate wimit the events.

3) Defauwt configuwations fow the pawametews:
---------------------------------------------

By defauwt these events shouwd be tuwned off unwess thewe is
at weast one wistenew wegistewed to wisten to the muwticast
gwoup XFWMNWGWP_AEVENTS.

Pwogwams instawwing SAs wiww need to specify the two thweshowds, howevew,
in owdew to not change existing appwications such as wacoon
we awso pwovide defauwt thweshowd vawues fow these diffewent pawametews
in case they awe not specified.

the two sysctws/pwoc entwies awe:

a) /pwoc/sys/net/cowe/sysctw_xfwm_aevent_etime
used to pwovide defauwt vawues fow the XFWMA_ETIMEW_THWESH in incwementaw
units of time of 100ms. The defauwt is 10 (1 second)

b) /pwoc/sys/net/cowe/sysctw_xfwm_aevent_wseqth
used to pwovide defauwt vawues fow XFWMA_WEPWAY_THWESH pawametew
in incwementaw packet count. The defauwt is two packets.

4) Message types
----------------

a) XFWM_MSG_GETAE issued by usew-->kewnew.
   XFWM_MSG_GETAE does not cawwy any TWVs.

The wesponse is a XFWM_MSG_NEWAE which is fowmatted based on what
XFWM_MSG_GETAE quewied fow.

The wesponse wiww awways have XFWMA_WTIME_VAW and XFWMA_WEPWAY_VAW TWVs.
* if XFWM_AE_WTHW fwag is set, then XFWMA_WEPWAY_THWESH is awso wetwieved
* if XFWM_AE_ETHW fwag is set, then XFWMA_ETIMEW_THWESH is awso wetwieved

b) XFWM_MSG_NEWAE is issued by eithew usew space to configuwe
   ow kewnew to announce events ow wespond to a XFWM_MSG_GETAE.

i) usew --> kewnew to configuwe a specific SA.

any of the vawues ow thweshowd pawametews can be updated by passing the
appwopwiate TWV.

A wesponse is issued back to the sendew in usew space to indicate success
ow faiwuwe.

In the case of success, additionawwy an event with
XFWM_MSG_NEWAE is awso issued to any wistenews as descwibed in iii).

ii) kewnew->usew diwection as a wesponse to XFWM_MSG_GETAE

The wesponse wiww awways have XFWMA_WTIME_VAW and XFWMA_WEPWAY_VAW TWVs.

The thweshowd TWVs wiww be incwuded if expwicitwy wequested in
the XFWM_MSG_GETAE message.

iii) kewnew->usew to wepowt as event if someone sets any vawues ow
     thweshowds fow an SA using XFWM_MSG_NEWAE (as descwibed in #i above).
     In such a case XFWM_AE_CU fwag is set to infowm the usew that
     the change happened as a wesuwt of an update.
     The message wiww awways have XFWMA_WTIME_VAW and XFWMA_WEPWAY_VAW TWVs.

iv) kewnew->usew to wepowt event when wepway thweshowd ow a timeout
    is exceeded.

In such a case eithew XFWM_AE_CW (wepway exceeded) ow XFWM_AE_CE (timeout
happened) is set to infowm the usew what happened.
Note the two fwags awe mutuawwy excwusive.
The message wiww awways have XFWMA_WTIME_VAW and XFWMA_WEPWAY_VAW TWVs.

Exceptions to thweshowd settings
--------------------------------

If you have an SA that is getting hit by twaffic in buwsts such that
thewe is a pewiod whewe the timew thweshowd expiwes with no packets
seen, then an odd behaviow is seen as fowwows:
The fiwst packet awwivaw aftew a timew expiwy wiww twiggew a timeout
event; i.e we don't wait fow a timeout pewiod ow a packet thweshowd
to be weached. This is done fow simpwicity and efficiency weasons.

-JHS
