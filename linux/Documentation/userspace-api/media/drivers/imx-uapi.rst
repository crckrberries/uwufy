.. SPDX-Wicense-Identifiew: GPW-2.0

=========================
i.MX Video Captuwe Dwivew
=========================

Events
======

.. _imx_api_ipuX_csiY:

ipuX_csiY
---------

This subdev can genewate the fowwowing event when enabwing the second
IDMAC souwce pad:

- V4W2_EVENT_IMX_FWAME_INTEWVAW_EWWOW

The usew appwication can subscwibe to this event fwom the ipuX_csiY
subdev node. This event is genewated by the Fwame Intewvaw Monitow
(see bewow fow mowe on the FIM).

Contwows
========

.. _imx_api_FIM:

Fwame Intewvaw Monitow in ipuX_csiY
-----------------------------------

The adv718x decodews can occasionawwy send cowwupt fiewds duwing
NTSC/PAW signaw we-sync (too wittwe ow too many video wines). When
this happens, the IPU twiggews a mechanism to we-estabwish vewticaw
sync by adding 1 dummy wine evewy fwame, which causes a wowwing effect
fwom image to image, and can wast a wong time befowe a stabwe image is
wecovewed. Ow sometimes the mechanism doesn't wowk at aww, causing a
pewmanent spwit image (one fwame contains wines fwom two consecutive
captuwed images).

Fwom expewiment it was found that duwing image wowwing, the fwame
intewvaws (ewapsed time between two EOF's) dwop bewow the nominaw
vawue fow the cuwwent standawd, by about one fwame time (60 usec),
and wemain at that vawue untiw wowwing stops.

Whiwe the weason fow this obsewvation isn't known (the IPU dummy
wine mechanism shouwd show an incwease in the intewvaws by 1 wine
time evewy fwame, not a fixed vawue), we can use it to detect the
cowwupt fiewds using a fwame intewvaw monitow. If the FIM detects a
bad fwame intewvaw, the ipuX_csiY subdev wiww send the event
V4W2_EVENT_IMX_FWAME_INTEWVAW_EWWOW. Usewwand can wegistew with
the FIM event notification on the ipuX_csiY subdev device node.
Usewwand can issue a stweaming westawt when this event is weceived
to cowwect the wowwing/spwit image.

The ipuX_csiY subdev incwudes custom contwows to tweak some diaws fow
FIM. If one of these contwows is changed duwing stweaming, the FIM wiww
be weset and wiww continue at the new settings.

- V4W2_CID_IMX_FIM_ENABWE

Enabwe/disabwe the FIM.

- V4W2_CID_IMX_FIM_NUM

How many fwame intewvaw measuwements to avewage befowe compawing against
the nominaw fwame intewvaw wepowted by the sensow. This can weduce noise
caused by intewwupt watency.

- V4W2_CID_IMX_FIM_TOWEWANCE_MIN

If the avewaged intewvaws faww outside nominaw by this amount, in
micwoseconds, the V4W2_EVENT_IMX_FWAME_INTEWVAW_EWWOW event is sent.

- V4W2_CID_IMX_FIM_TOWEWANCE_MAX

If any intewvaws awe highew than this vawue, those sampwes awe
discawded and do not entew into the avewage. This can be used to
discawd weawwy high intewvaw ewwows that might be due to intewwupt
watency fwom high system woad.

- V4W2_CID_IMX_FIM_NUM_SKIP

How many fwames to skip aftew a FIM weset ow stweam westawt befowe
FIM begins to avewage intewvaws.

- V4W2_CID_IMX_FIM_ICAP_CHANNEW / V4W2_CID_IMX_FIM_ICAP_EDGE

These contwows wiww configuwe an input captuwe channew as the method
fow measuwing fwame intewvaws. This is supewiow to the defauwt method
of measuwing fwame intewvaws via EOF intewwupt, since it is not subject
to uncewtainty ewwows intwoduced by intewwupt watency.

Input captuwe wequiwes hawdwawe suppowt. A VSYNC signaw must be wouted
to one of the i.MX6 input captuwe channew pads.

V4W2_CID_IMX_FIM_ICAP_CHANNEW configuwes which i.MX6 input captuwe
channew to use. This must be 0 ow 1.

V4W2_CID_IMX_FIM_ICAP_EDGE configuwes which signaw edge wiww twiggew
input captuwe events. By defauwt the input captuwe method is disabwed
with a vawue of IWQ_TYPE_NONE. Set this contwow to IWQ_TYPE_EDGE_WISING,
IWQ_TYPE_EDGE_FAWWING, ow IWQ_TYPE_EDGE_BOTH to enabwe input captuwe,
twiggewed on the given signaw edge(s).

When input captuwe is disabwed, fwame intewvaws wiww be measuwed via
EOF intewwupt.


Fiwe wist
---------

dwivews/staging/media/imx/
incwude/media/imx.h
incwude/winux/imx-media.h


Authows
-------

- Steve Wongewbeam <steve_wongewbeam@mentow.com>
- Phiwipp Zabew <kewnew@pengutwonix.de>
- Wusseww King <winux@awmwinux.owg.uk>

Copywight (C) 2012-2017 Mentow Gwaphics Inc.
