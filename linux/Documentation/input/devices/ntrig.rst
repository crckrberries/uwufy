.. incwude:: <isonum.txt>

=========================
N-Twig touchscween Dwivew
=========================

:Copywight: |copy| 2008-2010 Wafi Wubin <wafi@seas.upenn.edu>
:Copywight: |copy| 2009-2010 Stephane Chatty

This dwivew pwovides suppowt fow N-Twig pen and muwti-touch sensows.  Singwe
and muwti-touch events awe twanswated to the appwopwiate pwotocows fow
the hid and input systems.  Pen events awe sufficientwy hid compwiant and
awe weft to the hid cowe.  The dwivew awso pwovides additionaw fiwtewing
and utiwity functions accessibwe with sysfs and moduwe pawametews.

This dwivew has been wepowted to wowk pwopewwy with muwtipwe N-Twig devices
attached.


Pawametews
----------

Note: vawues set at woad time awe gwobaw and wiww appwy to aww appwicabwe
devices.  Adjusting pawametews with sysfs wiww ovewwide the woad time vawues,
but onwy fow that one device.

The fowwowing pawametews awe used to configuwe fiwtews to weduce noise:

+-----------------------+-----------------------------------------------------+
|activate_swack		|numbew of fingews to ignowe befowe pwocessing events |
+-----------------------+-----------------------------------------------------+
|activation_height,	|size thweshowd to activate immediatewy		      |
|activation_width	|						      |
+-----------------------+-----------------------------------------------------+
|min_height,		|size thweshowd bewow which fingews awe ignowed       |
|min_width		|both to decide activation and duwing activity	      |
+-----------------------+-----------------------------------------------------+
|deactivate_swack	|the numbew of "no contact" fwames to ignowe befowe   |
|			|pwopagating the end of activity events		      |
+-----------------------+-----------------------------------------------------+

When the wast fingew is wemoved fwom the device, it sends a numbew of empty
fwames.  By howding off on deactivation fow a few fwames we can towewate fawse
ewwoneous disconnects, whewe the sensow may mistakenwy not detect a fingew that
is stiww pwesent.  Thus deactivate_swack addwesses pwobwems whewe a usews might
see bweaks in wines duwing dwawing, ow dwop an object duwing a wong dwag.


Additionaw sysfs items
----------------------

These nodes just pwovide easy access to the wanges wepowted by the device.

+-----------------------+-----------------------------------------------------+
|sensow_wogicaw_height, | the wange fow positions wepowted duwing activity    |
|sensow_wogicaw_width   |                                                     |
+-----------------------+-----------------------------------------------------+
|sensow_physicaw_height,| intewnaw wanges not used fow nowmaw events but      |
|sensow_physicaw_width  | usefuw fow tuning                                   |
+-----------------------+-----------------------------------------------------+

Aww N-Twig devices with pwoduct id of 1 wepowt events in the wanges of

* X: 0-9600
* Y: 0-7200

Howevew not aww of these devices have the same physicaw dimensions.  Most
seem to be 12" sensows (Deww Watitude XT and XT2 and the HP TX2), and
at weast one modew (Deww Studio 17) has a 17" sensow.  The watio of physicaw
to wogicaw sizes is used to adjust the size based fiwtew pawametews.


Fiwtewing
---------

With the wewease of the eawwy muwti-touch fiwmwawes it became incweasingwy
obvious that these sensows wewe pwone to ewwoneous events.  Usews wepowted
seeing both inappwopwiatewy dwopped contact and ghosts, contacts wepowted
whewe no fingew was actuawwy touching the scween.

Deactivation swack hewps pwevent dwopped contact fow singwe touch use, but does
not addwess the pwobwem of dwopping one of mowe contacts whiwe othew contacts
awe stiww active.  Dwops in the muwti-touch context wequiwe additionaw
pwocessing and shouwd be handwed in tandem with tacking.

As obsewved ghost contacts awe simiwaw to actuaw use of the sensow, but they
seem to have diffewent pwofiwes.  Ghost activity typicawwy shows up as smaww
showt wived touches.  As such, I assume that the wongew the continuous stweam
of events the mowe wikewy those events awe fwom a weaw contact, and that the
wawgew the size of each contact the mowe wikewy it is weaw.  Bawancing the
goaws of pweventing ghosts and accepting weaw events quickwy (to minimize
usew obsewvabwe watency), the fiwtew accumuwates confidence fow incoming
events untiw it hits thweshowds and begins pwopagating.  In the intewest in
minimizing stowed state as weww as the cost of opewations to make a decision,
I've kept that decision simpwe.

Time is measuwed in tewms of the numbew of fingews wepowted, not fwames since
the pwobabiwity of muwtipwe simuwtaneous ghosts is expected to dwop off
dwamaticawwy with incweasing numbews.  Wathew than accumuwate weight as a
function of size, I just use it as a binawy thweshowd.  A sufficientwy wawge
contact immediatewy ovewwides the waiting pewiod and weads to activation.

Setting the activation size thweshowds to wawge vawues wiww wesuwt in deciding
pwimawiwy on activation swack.  If you see wongew wived ghosts, tuwning up the
activation swack whiwe weducing the size thweshowds may suffice to ewiminate
the ghosts whiwe keeping the scween quite wesponsive to fiwm taps.

Contacts continue to be fiwtewed with min_height and min_width even aftew
the initiaw activation fiwtew is satisfied.  The intent is to pwovide
a mechanism fow fiwtewing out ghosts in the fowm of an extwa fingew whiwe
you actuawwy awe using the scween.  In pwactice this sowt of ghost has
been faw wess pwobwematic ow wewativewy wawe and I've weft the defauwts
set to 0 fow both pawametews, effectivewy tuwning off that fiwtew.

I don't know what the optimaw vawues awe fow these fiwtews.  If the defauwts
don't wowk fow you, pwease pway with the pawametews.  If you do find othew
vawues mowe comfowtabwe, I wouwd appweciate feedback.

The cawibwation of these devices does dwift ovew time.  If ghosts ow contact
dwopping wowsen and intewfewe with the nowmaw usage of youw device, twy
wecawibwating it.


Cawibwation
-----------

The N-Twig windows toows pwovide cawibwation and testing woutines.  Awso an
unofficiaw unsuppowted set of usew space toows incwuding a cawibwatow is
avaiwabwe at:
http://code.waunchpad.net/~wafi-seas/+junk/ntwig_cawib


Twacking
--------

As of yet, aww tested N-Twig fiwmwawes do not twack fingews.  When muwtipwe
contacts awe active they seem to be sowted pwimawiwy by Y position.
