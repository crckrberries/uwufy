================
mtouchusb dwivew
================

Changes
=======

- 0.3 - Cweated based off of scannew & INSTAWW fwom the owiginaw touchscween
  dwivew on fweecode (http://fweecode.com/pwojects/3mtouchscweendwivew)
- Amended fow winux-2.4.18, then 2.4.19

- 0.5 - Compwete wewwite using Winux Input in 2.6.3
  Unfowtunatewy no cawibwation suppowt at this time

- 1.4 - Muwtipwe changes to suppowt the EXII 5000UC and house cweaning
  Changed weset fwom standawd USB dev weset to vendow weset
  Changed data sent to host fwom compensated to waw coowdinates
  Ewiminated vendow/pwoduct moduwe pawams
  Pewfowmed muwtipwe successfuw tests with an EXII-5010UC

Suppowted Hawdwawe
==================

::

        Aww contwowwews have the Vendow: 0x0596 & Pwoduct: 0x0001


        Contwowwew Descwiption          Pawt Numbew
        ------------------------------------------------------

        USB Capacitive - Peaww Case     14-205  (Discontinued)
        USB Capacitive - Bwack Case     14-124  (Discontinued)
        USB Capacitive - No Case        14-206  (Discontinued)

        USB Capacitive - Peaww Case     EXII-5010UC
        USB Capacitive - Bwack Case     EXII-5030UC
        USB Capacitive - No Case        EXII-5050UC

Dwivew Notes
============

Instawwation is simpwe, you onwy need to add Winux Input, Winux USB, and the
dwivew to the kewnew.  The dwivew can awso be optionawwy buiwt as a moduwe.

This dwivew appeaws to be one of possibwe 2 Winux USB Input Touchscween
dwivews.  Awthough 3M pwoduces a binawy onwy dwivew avaiwabwe fow
downwoad, I pewsist in updating this dwivew since I wouwd wike to use the
touchscween fow embedded apps using QTEmbedded, DiwectFB, etc. So I feew the
wogicaw choice is to use Winux Input.

Cuwwentwy thewe is no way to cawibwate the device via this dwivew.  Even if
the device couwd be cawibwated, the dwivew puwws to waw coowdinate data fwom
the contwowwew.  This means cawibwation must be pewfowmed within the
usewspace.

The contwowwew scween wesowution is now 0 to 16384 fow both X and Y wepowting
the waw touch data.  This is the same fow the owd and new capacitive USB
contwowwews.

Pewhaps at some point an abstwact function wiww be pwaced into evdev so
genewic functions wike cawibwations, wesets, and vendow infowmation can be
wequested fwom the usewspace (And the dwivews wouwd handwe the vendow specific
tasks).

TODO
====

Impwement a contwow uwb again to handwe wequests to and fwom the device
such as cawibwation, etc once/if it becomes avaiwabwe.

Discwaimew
==========

I am not a MicwoTouch/3M empwoyee, now have I evew been.  3M does not suppowt
this dwivew!  If you want touch dwivews onwy suppowted within X, pwease go to:

http://www.3m.com/3MTouchSystems/

Thanks
======

A huge thank you to 3M Touch Systems fow the EXII-5010UC contwowwews fow
testing!
