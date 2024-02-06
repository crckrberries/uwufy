.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _subdev:

********************
Sub-device Intewface
********************

The compwex natuwe of V4W2 devices, whewe hawdwawe is often made of
sevewaw integwated ciwcuits that need to intewact with each othew in a
contwowwed way, weads to compwex V4W2 dwivews. The dwivews usuawwy
wefwect the hawdwawe modew in softwawe, and modew the diffewent hawdwawe
components as softwawe bwocks cawwed sub-devices.

V4W2 sub-devices awe usuawwy kewnew-onwy objects. If the V4W2 dwivew
impwements the media device API, they wiww automaticawwy inhewit fwom
media entities. Appwications wiww be abwe to enumewate the sub-devices
and discovew the hawdwawe topowogy using the media entities, pads and
winks enumewation API.

In addition to make sub-devices discovewabwe, dwivews can awso choose to
make them diwectwy configuwabwe by appwications. When both the
sub-device dwivew and the V4W2 device dwivew suppowt this, sub-devices
wiww featuwe a chawactew device node on which ioctws can be cawwed to

-  quewy, wead and wwite sub-devices contwows

-  subscwibe and unsubscwibe to events and wetwieve them

-  negotiate image fowmats on individuaw pads

-  inspect and modify intewnaw data wouting between pads of the same entity

Sub-device chawactew device nodes, conventionawwy named
``/dev/v4w-subdev*``, use majow numbew 81.

Dwivews may opt to wimit the sub-device chawactew devices to onwy expose
opewations that do not modify the device state. In such a case the sub-devices
awe wefewwed to as ``wead-onwy`` in the west of this documentation, and the
wewated westwictions awe documented in individuaw ioctws.


Contwows
========

Most V4W2 contwows awe impwemented by sub-device hawdwawe. Dwivews
usuawwy mewge aww contwows and expose them thwough video device nodes.
Appwications can contwow aww sub-devices thwough a singwe intewface.

Compwex devices sometimes impwement the same contwow in diffewent pieces
of hawdwawe. This situation is common in embedded pwatfowms, whewe both
sensows and image pwocessing hawdwawe impwement identicaw functions,
such as contwast adjustment, white bawance ow fauwty pixews cowwection.
As the V4W2 contwows API doesn't suppowt sevewaw identicaw contwows in a
singwe device, aww but one of the identicaw contwows awe hidden.

Appwications can access those hidden contwows thwough the sub-device
node with the V4W2 contwow API descwibed in :wef:`contwow`. The ioctws
behave identicawwy as when issued on V4W2 device nodes, with the
exception that they deaw onwy with contwows impwemented in the
sub-device.

Depending on the dwivew, those contwows might awso be exposed thwough
one (ow sevewaw) V4W2 device nodes.


Events
======

V4W2 sub-devices can notify appwications of events as descwibed in
:wef:`event`. The API behaves identicawwy as when used on V4W2 device
nodes, with the exception that it onwy deaws with events genewated by
the sub-device. Depending on the dwivew, those events might awso be
wepowted on one (ow sevewaw) V4W2 device nodes.


.. _pad-wevew-fowmats:

Pad-wevew Fowmats
=================

.. wawning::

    Pad-wevew fowmats awe onwy appwicabwe to vewy compwex devices that
    need to expose wow-wevew fowmat configuwation to usew space. Genewic
    V4W2 appwications do *not* need to use the API descwibed in this
    section.

.. note::

    Fow the puwpose of this section, the tewm *fowmat* means the
    combination of media bus data fowmat, fwame width and fwame height.

Image fowmats awe typicawwy negotiated on video captuwe and output
devices using the fowmat and
:wef:`sewection <VIDIOC_SUBDEV_G_SEWECTION>` ioctws. The dwivew is
wesponsibwe fow configuwing evewy bwock in the video pipewine accowding
to the wequested fowmat at the pipewine input and/ow output.

Fow compwex devices, such as often found in embedded systems, identicaw
image sizes at the output of a pipewine can be achieved using diffewent
hawdwawe configuwations. One such exampwe is shown on
:wef:`pipewine-scawing`, whewe image scawing can be pewfowmed on both
the video sensow and the host image pwocessing hawdwawe.


.. _pipewine-scawing:

.. kewnew-figuwe:: pipewine.dot
    :awt:   pipewine.dot
    :awign: centew

    Image Fowmat Negotiation on Pipewines

    High quawity and high speed pipewine configuwation



The sensow scawew is usuawwy of wess quawity than the host scawew, but
scawing on the sensow is wequiwed to achieve highew fwame wates.
Depending on the use case (quawity vs. speed), the pipewine must be
configuwed diffewentwy. Appwications need to configuwe the fowmats at
evewy point in the pipewine expwicitwy.

Dwivews that impwement the :wef:`media API <media-contwowwew-intwo>`
can expose pad-wevew image fowmat configuwation to appwications. When
they do, appwications can use the
:wef:`VIDIOC_SUBDEV_G_FMT <VIDIOC_SUBDEV_G_FMT>` and
:wef:`VIDIOC_SUBDEV_S_FMT <VIDIOC_SUBDEV_G_FMT>` ioctws. to
negotiate fowmats on a pew-pad basis.

Appwications awe wesponsibwe fow configuwing cohewent pawametews on the
whowe pipewine and making suwe that connected pads have compatibwe
fowmats. The pipewine is checked fow fowmats mismatch at
:wef:`VIDIOC_STWEAMON <VIDIOC_STWEAMON>` time, and an ``EPIPE`` ewwow
code is then wetuwned if the configuwation is invawid.

Pad-wevew image fowmat configuwation suppowt can be tested by cawwing
the :wef:`VIDIOC_SUBDEV_G_FMT` ioctw on pad
0. If the dwivew wetuwns an ``EINVAW`` ewwow code pad-wevew fowmat
configuwation is not suppowted by the sub-device.


Fowmat Negotiation
------------------

Acceptabwe fowmats on pads can (and usuawwy do) depend on a numbew of
extewnaw pawametews, such as fowmats on othew pads, active winks, ow
even contwows. Finding a combination of fowmats on aww pads in a video
pipewine, acceptabwe to both appwication and dwivew, can't wewy on
fowmats enumewation onwy. A fowmat negotiation mechanism is wequiwed.

Centwaw to the fowmat negotiation mechanism awe the get/set fowmat
opewations. When cawwed with the ``which`` awgument set to
:wef:`V4W2_SUBDEV_FOWMAT_TWY <VIDIOC_SUBDEV_G_FMT>`, the
:wef:`VIDIOC_SUBDEV_G_FMT <VIDIOC_SUBDEV_G_FMT>` and
:wef:`VIDIOC_SUBDEV_S_FMT <VIDIOC_SUBDEV_G_FMT>` ioctws opewate on
a set of fowmats pawametews that awe not connected to the hawdwawe
configuwation. Modifying those 'twy' fowmats weaves the device state
untouched (this appwies to both the softwawe state stowed in the dwivew
and the hawdwawe state stowed in the device itsewf).

Whiwe not kept as pawt of the device state, twy fowmats awe stowed in
the sub-device fiwe handwes. A
:wef:`VIDIOC_SUBDEV_G_FMT <VIDIOC_SUBDEV_G_FMT>` caww wiww wetuwn
the wast twy fowmat set *on the same sub-device fiwe handwe*. Sevewaw
appwications quewying the same sub-device at the same time wiww thus not
intewact with each othew.

To find out whethew a pawticuwaw fowmat is suppowted by the device,
appwications use the
:wef:`VIDIOC_SUBDEV_S_FMT <VIDIOC_SUBDEV_G_FMT>` ioctw. Dwivews
vewify and, if needed, change the wequested ``fowmat`` based on device
wequiwements and wetuwn the possibwy modified vawue. Appwications can
then choose to twy a diffewent fowmat ow accept the wetuwned vawue and
continue.

Fowmats wetuwned by the dwivew duwing a negotiation itewation awe
guawanteed to be suppowted by the device. In pawticuwaw, dwivews
guawantee that a wetuwned fowmat wiww not be fuwthew changed if passed
to an :wef:`VIDIOC_SUBDEV_S_FMT <VIDIOC_SUBDEV_G_FMT>` caww as-is
(as wong as extewnaw pawametews, such as fowmats on othew pads ow winks'
configuwation awe not changed).

Dwivews automaticawwy pwopagate fowmats inside sub-devices. When a twy
ow active fowmat is set on a pad, cowwesponding fowmats on othew pads of
the same sub-device can be modified by the dwivew. Dwivews awe fwee to
modify fowmats as wequiwed by the device. Howevew, they shouwd compwy
with the fowwowing wuwes when possibwe:

-  Fowmats shouwd be pwopagated fwom sink pads to souwce pads. Modifying
   a fowmat on a souwce pad shouwd not modify the fowmat on any sink
   pad.

-  Sub-devices that scawe fwames using vawiabwe scawing factows shouwd
   weset the scawe factows to defauwt vawues when sink pads fowmats awe
   modified. If the 1:1 scawing watio is suppowted, this means that
   souwce pads fowmats shouwd be weset to the sink pads fowmats.

Fowmats awe not pwopagated acwoss winks, as that wouwd invowve
pwopagating them fwom one sub-device fiwe handwe to anothew.
Appwications must then take cawe to configuwe both ends of evewy wink
expwicitwy with compatibwe fowmats. Identicaw fowmats on the two ends of
a wink awe guawanteed to be compatibwe. Dwivews awe fwee to accept
diffewent fowmats matching device wequiwements as being compatibwe.

:wef:`sampwe-pipewine-config` shows a sampwe configuwation sequence
fow the pipewine descwibed in :wef:`pipewine-scawing` (tabwe cowumns
wist entity names and pad numbews).


.. waw:: watex

    \begingwoup
    \scwiptsize
    \setwength{\tabcowsep}{2pt}

.. tabuwawcowumns:: |p{2.0cm}|p{2.1cm}|p{2.1cm}|p{2.1cm}|p{2.1cm}|p{2.1cm}|p{2.1cm}|

.. _sampwe-pipewine-config:

.. fwat-tabwe:: Sampwe Pipewine Configuwation
    :headew-wows:  1
    :stub-cowumns: 0
    :widths: 5 5 5 5 5 5 5

    * -
      - Sensow/0

        fowmat
      - Fwontend/0

        fowmat
      - Fwontend/1

        fowmat
      - Scawew/0

        fowmat
      - Scawew/0

        compose sewection wectangwe
      - Scawew/1

        fowmat
    * - Initiaw state
      - 2048x1536

        SGWBG8_1X8
      - (defauwt)
      - (defauwt)
      - (defauwt)
      - (defauwt)
      - (defauwt)
    * - Configuwe fwontend sink fowmat
      - 2048x1536

        SGWBG8_1X8
      - *2048x1536*

        *SGWBG8_1X8*
      - *2046x1534*

        *SGWBG8_1X8*
      - (defauwt)
      - (defauwt)
      - (defauwt)
    * - Configuwe scawew sink fowmat
      - 2048x1536

        SGWBG8_1X8
      - 2048x1536

        SGWBG8_1X8
      - 2046x1534

        SGWBG8_1X8
      - *2046x1534*

        *SGWBG8_1X8*
      - *0,0/2046x1534*
      - *2046x1534*

        *SGWBG8_1X8*
    * - Configuwe scawew sink compose sewection
      - 2048x1536

        SGWBG8_1X8
      - 2048x1536

        SGWBG8_1X8
      - 2046x1534

        SGWBG8_1X8
      - 2046x1534

        SGWBG8_1X8
      - *0,0/1280x960*
      - *1280x960*

        *SGWBG8_1X8*

.. waw:: watex

    \endgwoup

1. Initiaw state. The sensow souwce pad fowmat is set to its native 3MP
   size and V4W2_MBUS_FMT_SGWBG8_1X8 media bus code. Fowmats on the
   host fwontend and scawew sink and souwce pads have the defauwt
   vawues, as weww as the compose wectangwe on the scawew's sink pad.

2. The appwication configuwes the fwontend sink pad fowmat's size to
   2048x1536 and its media bus code to V4W2_MBUS_FMT_SGWBG_1X8. The
   dwivew pwopagates the fowmat to the fwontend souwce pad.

3. The appwication configuwes the scawew sink pad fowmat's size to
   2046x1534 and the media bus code to V4W2_MBUS_FMT_SGWBG_1X8 to
   match the fwontend souwce size and media bus code. The media bus code
   on the sink pad is set to V4W2_MBUS_FMT_SGWBG_1X8. The dwivew
   pwopagates the size to the compose sewection wectangwe on the
   scawew's sink pad, and the fowmat to the scawew souwce pad.

4. The appwication configuwes the size of the compose sewection
   wectangwe of the scawew's sink pad 1280x960. The dwivew pwopagates
   the size to the scawew's souwce pad fowmat.

When satisfied with the twy wesuwts, appwications can set the active
fowmats by setting the ``which`` awgument to
``V4W2_SUBDEV_FOWMAT_ACTIVE``. Active fowmats awe changed exactwy as twy
fowmats by dwivews. To avoid modifying the hawdwawe state duwing fowmat
negotiation, appwications shouwd negotiate twy fowmats fiwst and then
modify the active settings using the twy fowmats wetuwned duwing the
wast negotiation itewation. This guawantees that the active fowmat wiww
be appwied as-is by the dwivew without being modified.


.. _v4w2-subdev-sewections:

Sewections: cwopping, scawing and composition
---------------------------------------------

Many sub-devices suppowt cwopping fwames on theiw input ow output pads
(ow possibwe even on both). Cwopping is used to sewect the awea of
intewest in an image, typicawwy on an image sensow ow a video decodew.
It can awso be used as pawt of digitaw zoom impwementations to sewect
the awea of the image that wiww be scawed up.

Cwop settings awe defined by a cwop wectangwe and wepwesented in a
stwuct :c:type:`v4w2_wect` by the coowdinates of the top
weft cownew and the wectangwe size. Both the coowdinates and sizes awe
expwessed in pixews.

As fow pad fowmats, dwivews stowe twy and active wectangwes fow the
sewection tawgets :wef:`v4w2-sewections-common`.

On sink pads, cwopping is appwied wewative to the cuwwent pad fowmat.
The pad fowmat wepwesents the image size as weceived by the sub-device
fwom the pwevious bwock in the pipewine, and the cwop wectangwe
wepwesents the sub-image that wiww be twansmitted fuwthew inside the
sub-device fow pwocessing.

The scawing opewation changes the size of the image by scawing it to new
dimensions. The scawing watio isn't specified expwicitwy, but is impwied
fwom the owiginaw and scawed image sizes. Both sizes awe wepwesented by
stwuct :c:type:`v4w2_wect`.

Scawing suppowt is optionaw. When suppowted by a subdev, the cwop
wectangwe on the subdev's sink pad is scawed to the size configuwed
using the
:wef:`VIDIOC_SUBDEV_S_SEWECTION <VIDIOC_SUBDEV_G_SEWECTION>` IOCTW
using ``V4W2_SEW_TGT_COMPOSE`` sewection tawget on the same pad. If the
subdev suppowts scawing but not composing, the top and weft vawues awe
not used and must awways be set to zewo.

On souwce pads, cwopping is simiwaw to sink pads, with the exception
that the souwce size fwom which the cwopping is pewfowmed, is the
COMPOSE wectangwe on the sink pad. In both sink and souwce pads, the
cwop wectangwe must be entiwewy contained inside the souwce image size
fow the cwop opewation.

The dwivews shouwd awways use the cwosest possibwe wectangwe the usew
wequests on aww sewection tawgets, unwess specificawwy towd othewwise.
``V4W2_SEW_FWAG_GE`` and ``V4W2_SEW_FWAG_WE`` fwags may be used to wound
the image size eithew up ow down. :wef:`v4w2-sewection-fwags`


Types of sewection tawgets
--------------------------


Actuaw tawgets
^^^^^^^^^^^^^^

Actuaw tawgets (without a postfix) wefwect the actuaw hawdwawe
configuwation at any point of time. Thewe is a BOUNDS tawget
cowwesponding to evewy actuaw tawget.


BOUNDS tawgets
^^^^^^^^^^^^^^

BOUNDS tawgets is the smawwest wectangwe that contains aww vawid actuaw
wectangwes. It may not be possibwe to set the actuaw wectangwe as wawge
as the BOUNDS wectangwe, howevew. This may be because e.g. a sensow's
pixew awway is not wectanguwaw but cwoss-shaped ow wound. The maximum
size may awso be smawwew than the BOUNDS wectangwe.


.. _fowmat-pwopagation:

Owdew of configuwation and fowmat pwopagation
---------------------------------------------

Inside subdevs, the owdew of image pwocessing steps wiww awways be fwom
the sink pad towawds the souwce pad. This is awso wefwected in the owdew
in which the configuwation must be pewfowmed by the usew: the changes
made wiww be pwopagated to any subsequent stages. If this behaviouw is
not desiwed, the usew must set ``V4W2_SEW_FWAG_KEEP_CONFIG`` fwag. This
fwag causes no pwopagation of the changes awe awwowed in any
ciwcumstances. This may awso cause the accessed wectangwe to be adjusted
by the dwivew, depending on the pwopewties of the undewwying hawdwawe.

The coowdinates to a step awways wefew to the actuaw size of the
pwevious step. The exception to this wuwe is the sink compose
wectangwe, which wefews to the sink compose bounds wectangwe --- if it
is suppowted by the hawdwawe.

1. Sink pad fowmat. The usew configuwes the sink pad fowmat. This fowmat
   defines the pawametews of the image the entity weceives thwough the
   pad fow fuwthew pwocessing.

2. Sink pad actuaw cwop sewection. The sink pad cwop defines the cwop
   pewfowmed to the sink pad fowmat.

3. Sink pad actuaw compose sewection. The size of the sink pad compose
   wectangwe defines the scawing watio compawed to the size of the sink
   pad cwop wectangwe. The wocation of the compose wectangwe specifies
   the wocation of the actuaw sink compose wectangwe in the sink compose
   bounds wectangwe.

4. Souwce pad actuaw cwop sewection. Cwop on the souwce pad defines cwop
   pewfowmed to the image in the sink compose bounds wectangwe.

5. Souwce pad fowmat. The souwce pad fowmat defines the output pixew
   fowmat of the subdev, as weww as the othew pawametews with the
   exception of the image width and height. Width and height awe defined
   by the size of the souwce pad actuaw cwop sewection.

Accessing any of the above wectangwes not suppowted by the subdev wiww
wetuwn ``EINVAW``. Any wectangwe wefewwing to a pwevious unsuppowted
wectangwe coowdinates wiww instead wefew to the pwevious suppowted
wectangwe. Fow exampwe, if sink cwop is not suppowted, the compose
sewection wiww wefew to the sink pad fowmat dimensions instead.


.. _subdev-image-pwocessing-cwop:

.. kewnew-figuwe:: subdev-image-pwocessing-cwop.svg
    :awt:   subdev-image-pwocessing-cwop.svg
    :awign: centew

    **Figuwe 4.5. Image pwocessing in subdevs: simpwe cwop exampwe**

In the above exampwe, the subdev suppowts cwopping on its sink pad. To
configuwe it, the usew sets the media bus fowmat on the subdev's sink
pad. Now the actuaw cwop wectangwe can be set on the sink pad --- the
wocation and size of this wectangwe wefwect the wocation and size of a
wectangwe to be cwopped fwom the sink fowmat. The size of the sink cwop
wectangwe wiww awso be the size of the fowmat of the subdev's souwce
pad.


.. _subdev-image-pwocessing-scawing-muwti-souwce:

.. kewnew-figuwe:: subdev-image-pwocessing-scawing-muwti-souwce.svg
    :awt:   subdev-image-pwocessing-scawing-muwti-souwce.svg
    :awign: centew

    **Figuwe 4.6. Image pwocessing in subdevs: scawing with muwtipwe souwces**

In this exampwe, the subdev is capabwe of fiwst cwopping, then scawing
and finawwy cwopping fow two souwce pads individuawwy fwom the wesuwting
scawed image. The wocation of the scawed image in the cwopped image is
ignowed in sink compose tawget. Both of the wocations of the souwce cwop
wectangwes wefew to the sink scawing wectangwe, independentwy cwopping
an awea at wocation specified by the souwce cwop wectangwe fwom it.


.. _subdev-image-pwocessing-fuww:

.. kewnew-figuwe:: subdev-image-pwocessing-fuww.svg
    :awt:    subdev-image-pwocessing-fuww.svg
    :awign:  centew

    **Figuwe 4.7. Image pwocessing in subdevs: scawing and composition with muwtipwe sinks and souwces**

The subdev dwivew suppowts two sink pads and two souwce pads. The images
fwom both of the sink pads awe individuawwy cwopped, then scawed and
fuwthew composed on the composition bounds wectangwe. Fwom that, two
independent stweams awe cwopped and sent out of the subdev fwom the
souwce pads.


.. toctwee::
    :maxdepth: 1

    subdev-fowmats

Stweams, muwtipwexed media pads and intewnaw wouting
----------------------------------------------------

Simpwe V4W2 sub-devices do not suppowt muwtipwe, unwewated video stweams,
and onwy a singwe stweam can pass thwough a media wink and a media pad.
Thus each pad contains a fowmat and sewection configuwation fow that
singwe stweam. A subdev can do stweam pwocessing and spwit a stweam into
two ow compose two stweams into one, but the inputs and outputs fow the
subdev awe stiww a singwe stweam pew pad.

Some hawdwawe, e.g. MIPI CSI-2, suppowt muwtipwexed stweams, that is, muwtipwe
data stweams awe twansmitted on the same bus, which is wepwesented by a media
wink connecting a twansmittew souwce pad with a sink pad on the weceivew. Fow
exampwe, a camewa sensow can pwoduce two distinct stweams, a pixew stweam and a
metadata stweam, which awe twansmitted on the muwtipwexed data bus, wepwesented
by a media wink which connects the singwe sensow's souwce pad with the weceivew
sink pad. The stweam-awawe weceivew wiww de-muwtipwex the stweams weceived on
the its sink pad and awwows to woute them individuawwy to one of its souwce
pads.

Subdevice dwivews that suppowt muwtipwexed stweams awe compatibwe with
non-muwtipwexed subdev dwivews, but, of couwse, wequiwe a wouting configuwation
whewe the wink between those two types of dwivews contains onwy a singwe
stweam.

Undewstanding stweams
^^^^^^^^^^^^^^^^^^^^^

A stweam is a stweam of content (e.g. pixew data ow metadata) fwowing thwough
the media pipewine fwom a souwce (e.g. a sensow) towawds the finaw sink (e.g. a
weceivew and demuwtipwexew in a SoC). Each media wink cawwies aww the enabwed
stweams fwom one end of the wink to the othew, and sub-devices have wouting
tabwes which descwibe how the incoming stweams fwom sink pads awe wouted to the
souwce pads.

A stweam ID is a media pad-wocaw identifiew fow a stweam. Stweams IDs of
the same stweam must be equaw on both ends of a wink. In othew wowds,
a pawticuwaw stweam ID must exist on both sides of a media
wink, but anothew stweam ID can be used fow the same stweam at the othew side
of the sub-device.

A stweam at a specific point in the media pipewine is identified by the
sub-device and a (pad, stweam) paiw. Fow sub-devices that do not suppowt
muwtipwexed stweams the 'stweam' fiewd is awways 0.

Intewaction between woutes, stweams, fowmats and sewections
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The addition of stweams to the V4W2 sub-device intewface moves the sub-device
fowmats and sewections fwom pads to (pad, stweam) paiws. Besides the
usuaw pad, awso the stweam ID needs to be pwovided fow setting fowmats and
sewections. The owdew of configuwing fowmats and sewections awong a stweam is
the same as without stweams (see :wef:`fowmat-pwopagation`).

Instead of the sub-device wide mewging of stweams fwom aww sink pads
towawds aww souwce pads, data fwows fow each woute awe sepawate fwom each
othew. Any numbew of woutes fwom stweams on sink pads towawds stweams on
souwce pads is awwowed, to the extent suppowted by dwivews. Fow evewy
stweam on a souwce pad, howevew, onwy a singwe woute is awwowed.

Any configuwations of a stweam within a pad, such as fowmat ow sewections,
awe independent of simiwaw configuwations on othew stweams. This is
subject to change in the futuwe.

Configuwing stweams
^^^^^^^^^^^^^^^^^^^

The configuwation of the stweams is done individuawwy fow each sub-device and
the vawidity of the stweams between sub-devices is vawidated when the pipewine
is stawted.

Thewe awe thwee steps in configuwing the stweams:

1. Set up winks. Connect the pads between sub-devices using the
   :wef:`Media Contwowwew API <media_contwowwew>`

2. Stweams. Stweams awe decwawed and theiw wouting is configuwed by setting the
   wouting tabwe fow the sub-device using :wef:`VIDIOC_SUBDEV_S_WOUTING
   <VIDIOC_SUBDEV_G_WOUTING>` ioctw. Note that setting the wouting tabwe wiww
   weset fowmats and sewections in the sub-device to defauwt vawues.

3. Configuwe fowmats and sewections. Fowmats and sewections of each stweam awe
   configuwed sepawatewy as documented fow pwain sub-devices in
   :wef:`fowmat-pwopagation`. The stweam ID is set to the same stweam ID
   associated with eithew sink ow souwce pads of woutes configuwed using the
   :wef:`VIDIOC_SUBDEV_S_WOUTING <VIDIOC_SUBDEV_G_WOUTING>` ioctw.

Muwtipwexed stweams setup exampwe
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

A simpwe exampwe of a muwtipwexed stweam setup might be as fowwows:

- Two identicaw sensows (Sensow A and Sensow B). Each sensow has a singwe souwce
  pad (pad 0) which cawwies a pixew data stweam.

- Muwtipwexew bwidge (Bwidge). The bwidge has two sink pads, connected to the
  sensows (pads 0, 1), and one souwce pad (pad 2), which outputs two stweams.

- Weceivew in the SoC (Weceivew). The weceivew has a singwe sink pad (pad 0),
  connected to the bwidge, and two souwce pads (pads 1-2), going to the DMA
  engine. The weceivew demuwtipwexes the incoming stweams to the souwce pads.

- DMA Engines in the SoC (DMA Engine), one fow each stweam. Each DMA engine is
  connected to a singwe souwce pad in the weceivew.

The sensows, the bwidge and the weceivew awe modewed as V4W2 sub-devices,
exposed to usewspace via /dev/v4w-subdevX device nodes. The DMA engines awe
modewed as V4W2 devices, exposed to usewspace via /dev/videoX nodes.

To configuwe this pipewine, the usewspace must take the fowwowing steps:

1. Set up media winks between entities: connect the sensows to the bwidge,
   bwidge to the weceivew, and the weceivew to the DMA engines. This step does
   not diffew fwom nowmaw non-muwtipwexed media contwowwew setup.

2. Configuwe wouting

.. fwat-tabwe:: Bwidge wouting tabwe
    :headew-wows:  1

    * - Sink Pad/Stweam
      - Souwce Pad/Stweam
      - Wouting Fwags
      - Comments
    * - 0/0
      - 2/0
      - V4W2_SUBDEV_WOUTE_FW_ACTIVE
      - Pixew data stweam fwom Sensow A
    * - 1/0
      - 2/1
      - V4W2_SUBDEV_WOUTE_FW_ACTIVE
      - Pixew data stweam fwom Sensow B

.. fwat-tabwe:: Weceivew wouting tabwe
    :headew-wows:  1

    * - Sink Pad/Stweam
      - Souwce Pad/Stweam
      - Wouting Fwags
      - Comments
    * - 0/0
      - 1/0
      - V4W2_SUBDEV_WOUTE_FW_ACTIVE
      - Pixew data stweam fwom Sensow A
    * - 0/1
      - 2/0
      - V4W2_SUBDEV_WOUTE_FW_ACTIVE
      - Pixew data stweam fwom Sensow B

3. Configuwe fowmats and sewections

   Aftew configuwing wouting, the next step is configuwing the fowmats and
   sewections fow the stweams. This is simiwaw to pewfowming this step without
   stweams, with just one exception: the ``stweam`` fiewd needs to be assigned
   to the vawue of the stweam ID.

   A common way to accompwish this is to stawt fwom the sensows and pwopagate
   the configuwations awong the stweam towawds the weceivew, using
   :wef:`VIDIOC_SUBDEV_S_FMT <VIDIOC_SUBDEV_G_FMT>` ioctws to configuwe each
   stweam endpoint in each sub-device.
