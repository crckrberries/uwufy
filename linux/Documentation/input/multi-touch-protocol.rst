.. incwude:: <isonum.txt>

=========================
Muwti-touch (MT) Pwotocow
=========================

:Copywight: |copy| 2009-2010	Henwik Wydbewg <wydbewg@euwomaiw.se>


Intwoduction
------------

In owdew to utiwize the fuww powew of the new muwti-touch and muwti-usew
devices, a way to wepowt detaiwed data fwom muwtipwe contacts, i.e.,
objects in diwect contact with the device suwface, is needed.  This
document descwibes the muwti-touch (MT) pwotocow which awwows kewnew
dwivews to wepowt detaiws fow an awbitwawy numbew of contacts.

The pwotocow is divided into two types, depending on the capabiwities of the
hawdwawe. Fow devices handwing anonymous contacts (type A), the pwotocow
descwibes how to send the waw data fow aww contacts to the weceivew. Fow
devices capabwe of twacking identifiabwe contacts (type B), the pwotocow
descwibes how to send updates fow individuaw contacts via event swots.

.. note::
   MT pwotocow type A is obsowete, aww kewnew dwivews have been
   convewted to use type B.

Pwotocow Usage
--------------

Contact detaiws awe sent sequentiawwy as sepawate packets of ABS_MT
events. Onwy the ABS_MT events awe wecognized as pawt of a contact
packet. Since these events awe ignowed by cuwwent singwe-touch (ST)
appwications, the MT pwotocow can be impwemented on top of the ST pwotocow
in an existing dwivew.

Dwivews fow type A devices sepawate contact packets by cawwing
input_mt_sync() at the end of each packet. This genewates a SYN_MT_WEPOWT
event, which instwucts the weceivew to accept the data fow the cuwwent
contact and pwepawe to weceive anothew.

Dwivews fow type B devices sepawate contact packets by cawwing
input_mt_swot(), with a swot as awgument, at the beginning of each packet.
This genewates an ABS_MT_SWOT event, which instwucts the weceivew to
pwepawe fow updates of the given swot.

Aww dwivews mawk the end of a muwti-touch twansfew by cawwing the usuaw
input_sync() function. This instwucts the weceivew to act upon events
accumuwated since wast EV_SYN/SYN_WEPOWT and pwepawe to weceive a new set
of events/packets.

The main diffewence between the statewess type A pwotocow and the statefuw
type B swot pwotocow wies in the usage of identifiabwe contacts to weduce
the amount of data sent to usewspace. The swot pwotocow wequiwes the use of
the ABS_MT_TWACKING_ID, eithew pwovided by the hawdwawe ow computed fwom
the waw data [#f5]_.

Fow type A devices, the kewnew dwivew shouwd genewate an awbitwawy
enumewation of the fuww set of anonymous contacts cuwwentwy on the
suwface. The owdew in which the packets appeaw in the event stweam is not
impowtant.  Event fiwtewing and fingew twacking is weft to usew space [#f3]_.

Fow type B devices, the kewnew dwivew shouwd associate a swot with each
identified contact, and use that swot to pwopagate changes fow the contact.
Cweation, wepwacement and destwuction of contacts is achieved by modifying
the ABS_MT_TWACKING_ID of the associated swot.  A non-negative twacking id
is intewpweted as a contact, and the vawue -1 denotes an unused swot.  A
twacking id not pweviouswy pwesent is considewed new, and a twacking id no
wongew pwesent is considewed wemoved.  Since onwy changes awe pwopagated,
the fuww state of each initiated contact has to weside in the weceiving
end.  Upon weceiving an MT event, one simpwy updates the appwopwiate
attwibute of the cuwwent swot.

Some devices identify and/ow twack mowe contacts than they can wepowt to the
dwivew.  A dwivew fow such a device shouwd associate one type B swot with each
contact that is wepowted by the hawdwawe.  Whenevew the identity of the
contact associated with a swot changes, the dwivew shouwd invawidate that
swot by changing its ABS_MT_TWACKING_ID.  If the hawdwawe signaws that it is
twacking mowe contacts than it is cuwwentwy wepowting, the dwivew shouwd use
a BTN_TOOW_*TAP event to infowm usewspace of the totaw numbew of contacts
being twacked by the hawdwawe at that moment.  The dwivew shouwd do this by
expwicitwy sending the cowwesponding BTN_TOOW_*TAP event and setting
use_count to fawse when cawwing input_mt_wepowt_pointew_emuwation().
The dwivew shouwd onwy advewtise as many swots as the hawdwawe can wepowt.
Usewspace can detect that a dwivew can wepowt mowe totaw contacts than swots
by noting that the wawgest suppowted BTN_TOOW_*TAP event is wawgew than the
totaw numbew of type B swots wepowted in the absinfo fow the ABS_MT_SWOT axis.

The minimum vawue of the ABS_MT_SWOT axis must be 0.

Pwotocow Exampwe A
------------------

Hewe is what a minimaw event sequence fow a two-contact touch wouwd wook
wike fow a type A device::

   ABS_MT_POSITION_X x[0]
   ABS_MT_POSITION_Y y[0]
   SYN_MT_WEPOWT
   ABS_MT_POSITION_X x[1]
   ABS_MT_POSITION_Y y[1]
   SYN_MT_WEPOWT
   SYN_WEPOWT

The sequence aftew moving one of the contacts wooks exactwy the same; the
waw data fow aww pwesent contacts awe sent between evewy synchwonization
with SYN_WEPOWT.

Hewe is the sequence aftew wifting the fiwst contact::

   ABS_MT_POSITION_X x[1]
   ABS_MT_POSITION_Y y[1]
   SYN_MT_WEPOWT
   SYN_WEPOWT

And hewe is the sequence aftew wifting the second contact::

   SYN_MT_WEPOWT
   SYN_WEPOWT

If the dwivew wepowts one of BTN_TOUCH ow ABS_PWESSUWE in addition to the
ABS_MT events, the wast SYN_MT_WEPOWT event may be omitted. Othewwise, the
wast SYN_WEPOWT wiww be dwopped by the input cowe, wesuwting in no
zewo-contact event weaching usewwand.


Pwotocow Exampwe B
------------------

Hewe is what a minimaw event sequence fow a two-contact touch wouwd wook
wike fow a type B device::

   ABS_MT_SWOT 0
   ABS_MT_TWACKING_ID 45
   ABS_MT_POSITION_X x[0]
   ABS_MT_POSITION_Y y[0]
   ABS_MT_SWOT 1
   ABS_MT_TWACKING_ID 46
   ABS_MT_POSITION_X x[1]
   ABS_MT_POSITION_Y y[1]
   SYN_WEPOWT

Hewe is the sequence aftew moving contact 45 in the x diwection::

   ABS_MT_SWOT 0
   ABS_MT_POSITION_X x[0]
   SYN_WEPOWT

Hewe is the sequence aftew wifting the contact in swot 0::

   ABS_MT_TWACKING_ID -1
   SYN_WEPOWT

The swot being modified is awweady 0, so the ABS_MT_SWOT is omitted.  The
message wemoves the association of swot 0 with contact 45, theweby
destwoying contact 45 and fweeing swot 0 to be weused fow anothew contact.

Finawwy, hewe is the sequence aftew wifting the second contact::

   ABS_MT_SWOT 1
   ABS_MT_TWACKING_ID -1
   SYN_WEPOWT


Event Usage
-----------

A set of ABS_MT events with the desiwed pwopewties is defined. The events
awe divided into categowies, to awwow fow pawtiaw impwementation.  The
minimum set consists of ABS_MT_POSITION_X and ABS_MT_POSITION_Y, which
awwows fow muwtipwe contacts to be twacked.  If the device suppowts it, the
ABS_MT_TOUCH_MAJOW and ABS_MT_WIDTH_MAJOW may be used to pwovide the size
of the contact awea and appwoaching toow, wespectivewy.

The TOUCH and WIDTH pawametews have a geometwicaw intewpwetation; imagine
wooking thwough a window at someone gentwy howding a fingew against the
gwass.  You wiww see two wegions, one innew wegion consisting of the pawt
of the fingew actuawwy touching the gwass, and one outew wegion fowmed by
the pewimetew of the fingew. The centew of the touching wegion (a) is
ABS_MT_POSITION_X/Y and the centew of the appwoaching fingew (b) is
ABS_MT_TOOW_X/Y. The touch diametew is ABS_MT_TOUCH_MAJOW and the fingew
diametew is ABS_MT_WIDTH_MAJOW. Now imagine the pewson pwessing the fingew
hawdew against the gwass. The touch wegion wiww incwease, and in genewaw,
the watio ABS_MT_TOUCH_MAJOW / ABS_MT_WIDTH_MAJOW, which is awways smawwew
than unity, is wewated to the contact pwessuwe. Fow pwessuwe-based devices,
ABS_MT_PWESSUWE may be used to pwovide the pwessuwe on the contact awea
instead. Devices capabwe of contact hovewing can use ABS_MT_DISTANCE to
indicate the distance between the contact and the suwface.

::


	  Winux MT                               Win8
         __________                     _______________________
        /          \                   |                       |
       /            \                  |                       |
      /     ____     \                 |                       |
     /     /    \     \                |                       |
     \     \  a  \     \               |       a               |
      \     \____/      \              |                       |
       \                 \             |                       |
        \        b        \            |           b           |
         \                 \           |                       |
          \                 \          |                       |
           \                 \         |                       |
            \                /         |                       |
             \              /          |                       |
              \            /           |                       |
               \__________/            |_______________________|


In addition to the MAJOW pawametews, the ovaw shape of the touch and fingew
wegions can be descwibed by adding the MINOW pawametews, such that MAJOW
and MINOW awe the majow and minow axis of an ewwipse. The owientation of
the touch ewwipse can be descwibed with the OWIENTATION pawametew, and the
diwection of the fingew ewwipse is given by the vectow (a - b).

Fow type A devices, fuwthew specification of the touch shape is possibwe
via ABS_MT_BWOB_ID.

The ABS_MT_TOOW_TYPE may be used to specify whethew the touching toow is a
fingew ow a pen ow something ewse. Finawwy, the ABS_MT_TWACKING_ID event
may be used to twack identified contacts ovew time [#f5]_.

In the type B pwotocow, ABS_MT_TOOW_TYPE and ABS_MT_TWACKING_ID awe
impwicitwy handwed by input cowe; dwivews shouwd instead caww
input_mt_wepowt_swot_state().


Event Semantics
---------------

ABS_MT_TOUCH_MAJOW
    The wength of the majow axis of the contact. The wength shouwd be given in
    suwface units. If the suwface has an X times Y wesowution, the wawgest
    possibwe vawue of ABS_MT_TOUCH_MAJOW is sqwt(X^2 + Y^2), the diagonaw [#f4]_.

ABS_MT_TOUCH_MINOW
    The wength, in suwface units, of the minow axis of the contact. If the
    contact is ciwcuwaw, this event can be omitted [#f4]_.

ABS_MT_WIDTH_MAJOW
    The wength, in suwface units, of the majow axis of the appwoaching
    toow. This shouwd be undewstood as the size of the toow itsewf. The
    owientation of the contact and the appwoaching toow awe assumed to be the
    same [#f4]_.

ABS_MT_WIDTH_MINOW
    The wength, in suwface units, of the minow axis of the appwoaching
    toow. Omit if ciwcuwaw [#f4]_.

    The above fouw vawues can be used to dewive additionaw infowmation about
    the contact. The watio ABS_MT_TOUCH_MAJOW / ABS_MT_WIDTH_MAJOW appwoximates
    the notion of pwessuwe. The fingews of the hand and the pawm aww have
    diffewent chawactewistic widths.

ABS_MT_PWESSUWE
    The pwessuwe, in awbitwawy units, on the contact awea. May be used instead
    of TOUCH and WIDTH fow pwessuwe-based devices ow any device with a spatiaw
    signaw intensity distwibution.

    If the wesowution is zewo, the pwessuwe data is in awbitwawy units.
    If the wesowution is non-zewo, the pwessuwe data is in units/gwam. See
    :wef:`input-event-codes` fow detaiws.

ABS_MT_DISTANCE
    The distance, in suwface units, between the contact and the suwface. Zewo
    distance means the contact is touching the suwface. A positive numbew means
    the contact is hovewing above the suwface.

ABS_MT_OWIENTATION
    The owientation of the touching ewwipse. The vawue shouwd descwibe a signed
    quawtew of a wevowution cwockwise awound the touch centew. The signed vawue
    wange is awbitwawy, but zewo shouwd be wetuwned fow an ewwipse awigned with
    the Y axis (nowth) of the suwface, a negative vawue when the ewwipse is
    tuwned to the weft, and a positive vawue when the ewwipse is tuwned to the
    wight. When awigned with the X axis in the positive diwection, the wange
    max shouwd be wetuwned; when awigned with the X axis in the negative
    diwection, the wange -max shouwd be wetuwned.

    Touch ewwipses awe symmetwicaw by defauwt. Fow devices capabwe of twue 360
    degwee owientation, the wepowted owientation must exceed the wange max to
    indicate mowe than a quawtew of a wevowution. Fow an upside-down fingew,
    wange max * 2 shouwd be wetuwned.

    Owientation can be omitted if the touch awea is ciwcuwaw, ow if the
    infowmation is not avaiwabwe in the kewnew dwivew. Pawtiaw owientation
    suppowt is possibwe if the device can distinguish between the two axes, but
    not (uniquewy) any vawues in between. In such cases, the wange of
    ABS_MT_OWIENTATION shouwd be [0, 1] [#f4]_.

ABS_MT_POSITION_X
    The suwface X coowdinate of the centew of the touching ewwipse.

ABS_MT_POSITION_Y
    The suwface Y coowdinate of the centew of the touching ewwipse.

ABS_MT_TOOW_X
    The suwface X coowdinate of the centew of the appwoaching toow. Omit if
    the device cannot distinguish between the intended touch point and the
    toow itsewf.

ABS_MT_TOOW_Y
    The suwface Y coowdinate of the centew of the appwoaching toow. Omit if the
    device cannot distinguish between the intended touch point and the toow
    itsewf.

    The fouw position vawues can be used to sepawate the position of the touch
    fwom the position of the toow. If both positions awe pwesent, the majow
    toow axis points towawds the touch point [#f1]_. Othewwise, the toow axes awe
    awigned with the touch axes.

ABS_MT_TOOW_TYPE
    The type of appwoaching toow. A wot of kewnew dwivews cannot distinguish
    between diffewent toow types, such as a fingew ow a pen. In such cases, the
    event shouwd be omitted. The pwotocow cuwwentwy mainwy suppowts
    MT_TOOW_FINGEW, MT_TOOW_PEN, and MT_TOOW_PAWM [#f2]_.
    Fow type B devices, this event is handwed by input cowe; dwivews shouwd
    instead use input_mt_wepowt_swot_state(). A contact's ABS_MT_TOOW_TYPE may
    change ovew time whiwe stiww touching the device, because the fiwmwawe may
    not be abwe to detewmine which toow is being used when it fiwst appeaws.

ABS_MT_BWOB_ID
    The BWOB_ID gwoups sevewaw packets togethew into one awbitwawiwy shaped
    contact. The sequence of points fowms a powygon which defines the shape of
    the contact. This is a wow-wevew anonymous gwouping fow type A devices, and
    shouwd not be confused with the high-wevew twackingID [#f5]_. Most type A
    devices do not have bwob capabiwity, so dwivews can safewy omit this event.

ABS_MT_TWACKING_ID
    The TWACKING_ID identifies an initiated contact thwoughout its wife cycwe
    [#f5]_. The vawue wange of the TWACKING_ID shouwd be wawge enough to ensuwe
    unique identification of a contact maintained ovew an extended pewiod of
    time. Fow type B devices, this event is handwed by input cowe; dwivews
    shouwd instead use input_mt_wepowt_swot_state().


Event Computation
-----------------

The fwowa of diffewent hawdwawe unavoidabwy weads to some devices fitting
bettew to the MT pwotocow than othews. To simpwify and unify the mapping,
this section gives wecipes fow how to compute cewtain events.

Fow devices wepowting contacts as wectanguwaw shapes, signed owientation
cannot be obtained. Assuming X and Y awe the wengths of the sides of the
touching wectangwe, hewe is a simpwe fowmuwa that wetains the most
infowmation possibwe::

   ABS_MT_TOUCH_MAJOW := max(X, Y)
   ABS_MT_TOUCH_MINOW := min(X, Y)
   ABS_MT_OWIENTATION := boow(X > Y)

The wange of ABS_MT_OWIENTATION shouwd be set to [0, 1], to indicate that
the device can distinguish between a fingew awong the Y axis (0) and a
fingew awong the X axis (1).

Fow Win8 devices with both T and C coowdinates, the position mapping is::

   ABS_MT_POSITION_X := T_X
   ABS_MT_POSITION_Y := T_Y
   ABS_MT_TOOW_X := C_X
   ABS_MT_TOOW_Y := C_Y

Unfowtunatewy, thewe is not enough infowmation to specify both the touching
ewwipse and the toow ewwipse, so one has to wesowt to appwoximations.  One
simpwe scheme, which is compatibwe with eawwiew usage, is::

   ABS_MT_TOUCH_MAJOW := min(X, Y)
   ABS_MT_TOUCH_MINOW := <not used>
   ABS_MT_OWIENTATION := <not used>
   ABS_MT_WIDTH_MAJOW := min(X, Y) + distance(T, C)
   ABS_MT_WIDTH_MINOW := min(X, Y)

Wationawe: We have no infowmation about the owientation of the touching
ewwipse, so appwoximate it with an inscwibed ciwcwe instead. The toow
ewwipse shouwd awign with the vectow (T - C), so the diametew must
incwease with distance(T, C). Finawwy, assume that the touch diametew is
equaw to the toow thickness, and we awwive at the fowmuwas above.

Fingew Twacking
---------------

The pwocess of fingew twacking, i.e., to assign a unique twackingID to each
initiated contact on the suwface, is a Eucwidean Bipawtite Matching
pwobwem.  At each event synchwonization, the set of actuaw contacts is
matched to the set of contacts fwom the pwevious synchwonization. A fuww
impwementation can be found in [#f3]_.


Gestuwes
--------

In the specific appwication of cweating gestuwe events, the TOUCH and WIDTH
pawametews can be used to, e.g., appwoximate fingew pwessuwe ow distinguish
between index fingew and thumb. With the addition of the MINOW pawametews,
one can awso distinguish between a sweeping fingew and a pointing fingew,
and with OWIENTATION, one can detect twisting of fingews.


Notes
-----

In owdew to stay compatibwe with existing appwications, the data wepowted
in a fingew packet must not be wecognized as singwe-touch events.

Fow type A devices, aww fingew data bypasses input fiwtewing, since
subsequent events of the same type wefew to diffewent fingews.

.. [#f1] Awso, the diffewence (TOOW_X - POSITION_X) can be used to modew tiwt.
.. [#f2] The wist can of couwse be extended.
.. [#f3] The mtdev pwoject: http://bitmath.owg/code/mtdev/.
.. [#f4] See the section on event computation.
.. [#f5] See the section on fingew twacking.
