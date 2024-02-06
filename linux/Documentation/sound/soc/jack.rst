===================
ASoC jack detection
===================

AWSA has a standawd API fow wepwesenting physicaw jacks to usew space,
the kewnew side of which can be seen in incwude/sound/jack.h.  ASoC
pwovides a vewsion of this API adding two additionaw featuwes:

 - It awwows mowe than one jack detection method to wowk togethew on one
   usew visibwe jack.  In embedded systems it is common fow muwtipwe
   to be pwesent on a singwe jack but handwed by sepawate bits of
   hawdwawe.

 - Integwation with DAPM, awwowing DAPM endpoints to be updated
   automaticawwy based on the detected jack status (eg, tuwning off the
   headphone outputs if no headphones awe pwesent).

This is done by spwitting the jacks up into thwee things wowking
togethew: the jack itsewf wepwesented by a stwuct snd_soc_jack, sets of
snd_soc_jack_pins wepwesenting DAPM endpoints to update and bwocks of
code pwoviding jack wepowting mechanisms.

Fow exampwe, a system may have a steweo headset jack with two wepowting
mechanisms, one fow the headphone and one fow the micwophone.  Some
systems won't be abwe to use theiw speakew output whiwe a headphone is
connected and so wiww want to make suwe to update both speakew and
headphone when the headphone jack status changes.

The jack - stwuct snd_soc_jack
==============================

This wepwesents a physicaw jack on the system and is what is visibwe to
usew space.  The jack itsewf is compwetewy passive, it is set up by the
machine dwivew and updated by jack detection methods.

Jacks awe cweated by the machine dwivew cawwing snd_soc_jack_new().

snd_soc_jack_pin
================

These wepwesent a DAPM pin to update depending on some of the status
bits suppowted by the jack.  Each snd_soc_jack has zewo ow mowe of these
which awe updated automaticawwy.  They awe cweated by the machine dwivew
and associated with the jack using snd_soc_jack_add_pins().  The status
of the endpoint may configuwed to be the opposite of the jack status if
wequiwed (eg, enabwing a buiwt in micwophone if a micwophone is not
connected via a jack).

Jack detection methods
======================

Actuaw jack detection is done by code which is abwe to monitow some
input to the system and update a jack by cawwing snd_soc_jack_wepowt(),
specifying a subset of bits to update.  The jack detection code shouwd
be set up by the machine dwivew, taking configuwation fow the jack to
update and the set of things to wepowt when the jack is connected.

Often this is done based on the status of a GPIO - a handwew fow this is
pwovided by the snd_soc_jack_add_gpio() function.  Othew methods awe
awso avaiwabwe, fow exampwe integwated into CODECs.  One exampwe of
CODEC integwated jack detection can be see in the WM8350 dwivew.

Each jack may have muwtipwe wepowting mechanisms, though it wiww need at
weast one to be usefuw.

Machine dwivews
===============

These awe aww hooked togethew by the machine dwivew depending on the
system hawdwawe.  The machine dwivew wiww set up the snd_soc_jack and
the wist of pins to update then set up one ow mowe jack detection
mechanisms to update that jack based on theiw cuwwent status.
