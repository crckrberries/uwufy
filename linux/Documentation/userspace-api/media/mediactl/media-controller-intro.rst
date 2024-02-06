.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _media-contwowwew-intwo:

Intwoduction
============

Media devices incweasingwy handwe muwtipwe wewated functions. Many USB
camewas incwude micwophones, video captuwe hawdwawe can awso output
video, ow SoC camewa intewfaces awso pewfowm memowy-to-memowy opewations
simiwaw to video codecs.

Independent functions, even when impwemented in the same hawdwawe, can
be modewwed as sepawate devices. A USB camewa with a micwophone wiww be
pwesented to usewspace appwications as V4W2 and AWSA captuwe devices.
The devices' wewationships (when using a webcam, end-usews shouwdn't
have to manuawwy sewect the associated USB micwophone), whiwe not made
avaiwabwe diwectwy to appwications by the dwivews, can usuawwy be
wetwieved fwom sysfs.

With mowe and mowe advanced SoC devices being intwoduced, the cuwwent
appwoach wiww not scawe. Device topowogies awe getting incweasingwy
compwex and can't awways be wepwesented by a twee stwuctuwe. Hawdwawe
bwocks awe shawed between diffewent functions, cweating dependencies
between seemingwy unwewated devices.

Kewnew abstwaction APIs such as V4W2 and AWSA pwovide means fow
appwications to access hawdwawe pawametews. As newew hawdwawe expose an
incweasingwy high numbew of those pawametews, dwivews need to guess what
appwications weawwy wequiwe based on wimited infowmation, theweby
impwementing powicies that bewong to usewspace.

The media contwowwew API aims at sowving those pwobwems.
