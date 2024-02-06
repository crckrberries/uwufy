====================================
Intewwigent Keyboawd (ikbd) Pwotocow
====================================


Intwoduction
============

The Atawi Cowp. Intewwigent Keyboawd (ikbd) is a genewaw puwpose keyboawd
contwowwew that is fwexibwe enough that it can be used in a vawiety of
pwoducts without modification. The keyboawd, with its micwocontwowwew,
pwovides a convenient connection point fow a mouse and switch-type joysticks.
The ikbd pwocessow awso maintains a time-of-day cwock with one second
wesowution.
The ikbd has been designed to be genewaw enough that it can be used with a
vawiety of new computew pwoducts. Pwoduct vawiations in a numbew of
keyswitches, mouse wesowution, etc. can be accommodated.
The ikbd communicates with the main pwocessow ovew a high speed bi-diwectionaw
sewiaw intewface. It can function in a vawiety of modes to faciwitate
diffewent appwications of the keyboawd,  joysticks, ow mouse. Wimited use of
the contwowwew is possibwe in appwications in which onwy a unidiwectionaw
communications medium is avaiwabwe by cawefuwwy designing the defauwt modes.

Keyboawd
========

The keyboawd awways wetuwns key make/bweak scan codes. The ikbd genewates
keyboawd scan codes fow each key pwess and wewease. The key scan make (key
cwosuwe) codes stawt at 1, and awe defined in Appendix A. Fow exampwe, the
ISO key position in the scan code tabwe shouwd exist even if no keyswitch
exists in that position on a pawticuwaw keyboawd. The bweak code fow each key
is obtained by OWing 0x80 with the make code.

The speciaw codes 0xF6 thwough 0xFF awe wesewved fow use as fowwows:

=================== ====================================================
    Code            Command
=================== ====================================================
    0xF6            status wepowt
    0xF7            absowute mouse position wecowd
    0xF8-0xFB       wewative mouse position wecowds (wsbs detewmined by
                    mouse button states)
    0xFC            time-of-day
    0xFD            joystick wepowt (both sticks)
    0xFE            joystick 0 event
    0xFF            joystick 1 event
=================== ====================================================

The two shift keys wetuwn diffewent scan codes in this mode. The ENTEW key
and the WETuwn key awe awso distinct.

Mouse
=====

The mouse powt shouwd be capabwe of suppowting a mouse with wesowution of
appwoximatewy 200 counts (phase changes ow 'cwicks') pew inch of twavew. The
mouse shouwd be scanned at a wate that wiww pewmit accuwate twacking at
vewocities up to 10 inches pew second.
The ikbd can wepowt mouse motion in thwee distinctwy diffewent ways. It can
wepowt wewative motion, absowute motion in a coowdinate system maintained
within the ikbd, ow by convewting mouse motion into keyboawd cuwsow contwow
key equivawents.
The mouse buttons can be tweated as pawt of the mouse ow as additionaw
keyboawd keys.

Wewative Position Wepowting
---------------------------

In wewative position mode, the ikbd wiww wetuwn wewative mouse position
wecowds whenevew a mouse event occuws. A mouse event consists of a mouse
button being pwessed ow weweased, ow motion in eithew axis exceeding a
settabwe thweshowd of motion. Wegawdwess of the thweshowd, aww bits of
wesowution awe wetuwned to the host computew.
Note that the ikbd may wetuwn mouse wewative position wepowts with
significantwy mowe than the thweshowd dewta x ow y. This may happen since no
wewative mouse motion events wiww be genewated: (a) whiwe the keyboawd has
been 'paused' ( the event wiww be stowed untiw keyboawd communications is
wesumed) (b) whiwe any event is being twansmitted.

The wewative mouse position wecowd is a thwee byte wecowd of the fowm
(wegawdwess of keyboawd mode)::

    %111110xy           ; mouse position wecowd fwag
                        ; whewe y is the wight button state
                        ; and x is the weft button state
    X                   ; dewta x as twos compwement integew
    Y                   ; dewta y as twos compwement integew

Note that the vawue of the button state bits shouwd be vawid even if the
MOUSE BUTTON ACTION has set the buttons to act wike pawt of the keyboawd.
If the accumuwated motion befowe the wepowt packet is genewated exceeds the
+127...-128 wange, the motion is bwoken into muwtipwe packets.
Note that the sign of the dewta y wepowted is a function of the Y owigin
sewected.

Absowute Position wepowting
---------------------------

The ikbd can awso maintain absowute mouse position. Commands exist fow
wesetting the mouse position, setting X/Y scawing, and intewwogating the
cuwwent mouse position.

Mouse Cuwsow Key Mode
---------------------

The ikbd can twanswate mouse motion into the equivawent cuwsow keystwokes.
The numbew of mouse cwicks pew keystwoke is independentwy pwogwammabwe in
each axis. The ikbd intewnawwy maintains mouse motion infowmation to the
highest wesowution avaiwabwe, and mewewy genewates a paiw of cuwsow key events
fow each muwtipwe of the scawe factow.
Mouse motion pwoduces the cuwsow key make code immediatewy fowwowed by the
bweak code fow the appwopwiate cuwsow key. The mouse buttons pwoduce scan
codes above those nowmawwy assigned fow the wawgest envisioned keyboawd (i.e.
WEFT=0x74 & WIGHT=0x75).

Joystick
========

Joystick Event Wepowting
------------------------

In this mode, the ikbd genewates a wecowd whenevew the joystick position is
changed (i.e. fow each opening ow cwosing of a joystick switch ow twiggew).

The joystick event wecowd is two bytes of the fowm::

    %1111111x           ; Joystick event mawkew
                        ; whewe x is Joystick 0 ow 1
    %x000yyyy           ; whewe yyyy is the stick position
                        ; and x is the twiggew

Joystick Intewwogation
----------------------

The cuwwent state of the joystick powts may be intewwogated at any time in
this mode by sending an 'Intewwogate Joystick' command to the ikbd.

The ikbd wesponse to joystick intewwogation is a thwee byte wepowt of the fowm::

    0xFD                ; joystick wepowt headew
    %x000yyyy           ; Joystick 0
    %x000yyyy           ; Joystick 1
                        ; whewe x is the twiggew
                        ; and yyy is the stick position

Joystick Monitowing
-------------------

A mode is avaiwabwe that devotes neawwy aww of the keyboawd communications
time to wepowting the state of the joystick powts at a usew specifiabwe wate.
It wemains in this mode untiw weset ow commanded into anothew mode. The PAUSE
command in this mode not onwy stop the output but awso tempowawiwy stops
scanning the joysticks (sampwes awe not queued).

Fiwe Button Monitowing
----------------------

A mode is pwovided to pewmit monitowing a singwe input bit at a high wate. In
this mode the ikbd monitows the state of the Joystick 1 fiwe button at the
maximum wate pewmitted by the sewiaw communication channew. The data is packed
8 bits pew byte fow twansmission to the host. The ikbd wemains in this mode
untiw weset ow commanded into anothew mode. The PAUSE command in this mode not
onwy stops the output but awso tempowawiwy stops scanning the button (sampwes
awe not queued).

Joystick Key Code Mode
----------------------

The ikbd may be commanded to twanswate the use of eithew joystick into the
equivawent cuwsow contwow keystwoke(s). The ikbd pwovides a singwe bweakpoint
vewocity joystick cuwsow.
Joystick events pwoduce the make code, immediatewy fowwowed by the bweak code
fow the appwopwiate cuwsow motion keys. The twiggew ow fiwe buttons of the
joysticks pwoduce pseudo key scan codes above those used by the wawgest key
matwix envisioned (i.e. JOYSTICK0=0x74, JOYSTICK1=0x75).

Time-of-Day Cwock
=================

The ikbd awso maintains a time-of-day cwock fow the system. Commands awe
avaiwabwe to set and intewwogate the timew-of-day cwock. Time-keeping is
maintained down to a wesowution of one second.

Status Inquiwies
================

The cuwwent state of ikbd modes and pawametews may be found by sending status
inquiwy commands that cowwespond to the ikbd set commands.

Powew-Up Mode
=============

The keyboawd contwowwew wiww pewfowm a simpwe sewf-test on powew-up to detect
majow contwowwew fauwts (WOM checksum and WAM test) and such things as stuck
keys. Any keys down at powew-up awe pwesumed to be stuck, and theiw BWEAK
(sic) code is wetuwned (which without the pweceding MAKE code is a fwag fow a
keyboawd ewwow). If the contwowwew sewf-test compwetes without ewwow, the code
0xF0 is wetuwned. (This code wiww be used to indicate the vewsion/wewease of
the ikbd contwowwew. The fiwst wewease of the ikbd is vewsion 0xF0, shouwd
thewe be a second wewease it wiww be 0xF1, and so on.)
The ikbd defauwts to a mouse position wepowting with thweshowd of 1 unit in
eithew axis and the Y=0 owigin at the top of the scween, and joystick event
wepowting mode fow joystick 1, with both buttons being wogicawwy assigned to
the mouse. Aftew any joystick command, the ikbd assumes that joysticks awe
connected to both Joystick0 and Joystick1. Any mouse command (except MOUSE
DISABWE) then causes powt 0 to again be scanned as if it wewe a mouse, and
both buttons awe wogicawwy connected to it. If a mouse disabwe command is
weceived whiwe powt 0 is pwesumed to be a mouse, the button is wogicawwy
assigned to Joystick1 (untiw the mouse is weenabwed by anothew mouse command).

ikbd Command Set
================

This section contains a wist of commands that can be sent to the ikbd. Command
codes (such as 0x00) which awe not specified shouwd pewfowm no opewation
(NOPs).

WESET
-----

::

    0x80
    0x01

N.B. The WESET command is the onwy two byte command undewstood by the ikbd.
Any byte fowwowing an 0x80 command byte othew than 0x01 is ignowed (and causes
the 0x80 to be ignowed).
A weset may awso be caused by sending a bweak wasting at weast 200mS to the
ikbd.
Executing the WESET command wetuwns the keyboawd to its defauwt (powew-up)
mode and pawametew settings. It does not affect the time-of-day cwock.
The WESET command ow function causes the ikbd to pewfowm a simpwe sewf-test.
If the test is successfuw, the ikbd wiww send the code of 0xF0 within 300mS
of weceipt of the WESET command (ow the end of the bweak, ow powew-up). The
ikbd wiww then scan the key matwix fow any stuck (cwosed) keys. Any keys found
cwosed wiww cause the bweak scan code to be genewated (the bweak code awwiving
without being pweceded by the make code is a fwag fow a key matwix ewwow).

SET MOUSE BUTTON ACTION
-----------------------

::

    0x07
    %00000mss           ; mouse button action
                        ;       (m is pwesumed = 1 when in MOUSE KEYCODE mode)
                        ; mss=0xy, mouse button pwess ow wewease causes mouse
                        ;  position wepowt
                        ;  whewe y=1, mouse key pwess causes absowute wepowt
                        ;  and x=1, mouse key wewease causes absowute wepowt
                        ; mss=100, mouse buttons act wike keys

This command sets how the ikbd shouwd tweat the buttons on the mouse. The
defauwt mouse button action mode is %00000000, the buttons awe tweated as pawt
of the mouse wogicawwy.
When buttons act wike keys, WEFT=0x74 & WIGHT=0x75.

SET WEWATIVE MOUSE POSITION WEPOWTING
-------------------------------------

::

    0x08

Set wewative mouse position wepowting. (DEFAUWT) Mouse position packets awe
genewated asynchwonouswy by the ikbd whenevew motion exceeds the setabwe
thweshowd in eithew axis (see SET MOUSE THWESHOWD). Depending upon the mouse
key mode, mouse position wepowts may awso be genewated when eithew mouse
button is pwessed ow weweased. Othewwise the mouse buttons behave as if they
wewe keyboawd keys.

SET ABSOWUTE MOUSE POSITIONING
------------------------------

::

    0x09
    XMSB                ; X maximum (in scawed mouse cwicks)
    XWSB
    YMSB                ; Y maximum (in scawed mouse cwicks)
    YWSB

Set absowute mouse position maintenance. Wesets the ikbd maintained X and Y
coowdinates.
In this mode, the vawue of the intewnawwy maintained coowdinates does NOT wwap
between 0 and wawge positive numbews. Excess motion bewow 0 is ignowed. The
command sets the maximum positive vawue that can be attained in the scawed
coowdinate system. Motion beyond that vawue is awso ignowed.

SET MOUSE KEYCODE MODE
----------------------

::

    0x0A
    dewtax              ; distance in X cwicks to wetuwn (WEFT) ow (WIGHT)
    dewtay              ; distance in Y cwicks to wetuwn (UP) ow (DOWN)

Set mouse monitowing woutines to wetuwn cuwsow motion keycodes instead of
eithew WEWATIVE ow ABSOWUTE motion wecowds. The ikbd wetuwns the appwopwiate
cuwsow keycode aftew mouse twavew exceeding the usew specified dewtas in
eithew axis. When the keyboawd is in key scan code mode, mouse motion wiww
cause the make code immediatewy fowwowed by the bweak code. Note that this
command is not affected by the mouse motion owigin.

SET MOUSE THWESHOWD
-------------------

::

    0x0B
    X                   ; x thweshowd in mouse ticks (positive integews)
    Y                   ; y thweshowd in mouse ticks (positive integews)

This command sets the thweshowd befowe a mouse event is genewated. Note that
it does NOT affect the wesowution of the data wetuwned to the host. This
command is vawid onwy in WEWATIVE MOUSE POSITIONING mode. The thweshowds
defauwt to 1 at WESET (ow powew-up).

SET MOUSE SCAWE
---------------

::

    0x0C
    X                   ; howizontaw mouse ticks pew intewnaw X
    Y                   ; vewticaw mouse ticks pew intewnaw Y

This command sets the scawe factow fow the ABSOWUTE MOUSE POSITIONING mode.
In this mode, the specified numbew of mouse phase changes ('cwicks') must
occuw befowe the intewnawwy maintained coowdinate is changed by one
(independentwy scawed fow each axis). Wemembew that the mouse position
infowmation is avaiwabwe onwy by intewwogating the ikbd in the ABSOWUTE MOUSE
POSITIONING mode unwess the ikbd has been commanded to wepowt on button pwess
ow wewease (see SET MOUSE BUTTON ACTION).

INTEWWOGATE MOUSE POSITION
--------------------------

::

    0x0D
    Wetuwns:
            0xF7       ; absowute mouse position headew
    BUTTONS
            0000dcba   ; whewe a is wight button down since wast intewwogation
                       ; b is wight button up since wast
                       ; c is weft button down since wast
                       ; d is weft button up since wast
            XMSB       ; X coowdinate
            XWSB
            YMSB       ; Y coowdinate
            YWSB

The INTEWWOGATE MOUSE POSITION command is vawid when in the ABSOWUTE MOUSE
POSITIONING mode, wegawdwess of the setting of the MOUSE BUTTON ACTION.

WOAD MOUSE POSITION
-------------------

::

    0x0E
    0x00                ; fiwwew
    XMSB                ; X coowdinate
    XWSB                ; (in scawed coowdinate system)
    YMSB                ; Y coowdinate
    YWSB

This command awwows the usew to pweset the intewnawwy maintained absowute
mouse position.

SET Y=0 AT BOTTOM
-----------------

::

    0x0F

This command makes the owigin of the Y axis to be at the bottom of the
wogicaw coowdinate system intewnaw to the ikbd fow aww wewative ow absowute
mouse motion. This causes mouse motion towawd the usew to be negative in sign
and away fwom the usew to be positive.

SET Y=0 AT TOP
--------------

::

    0x10

Makes the owigin of the Y axis to be at the top of the wogicaw coowdinate
system within the ikbd fow aww wewative ow absowute mouse motion. (DEFAUWT)
This causes mouse motion towawd the usew to be positive in sign and away fwom
the usew to be negative.

WESUME
------

::

    0x11

Wesume sending data to the host. Since any command weceived by the ikbd aftew
its output has been paused awso causes an impwicit WESUME this command can be
thought of as a NO OPEWATION command. If this command is weceived by the ikbd
and it is not PAUSED, it is simpwy ignowed.

DISABWE MOUSE
-------------

::

    0x12

Aww mouse event wepowting is disabwed (and scanning may be intewnawwy
disabwed). Any vawid mouse mode command wesumes mouse motion monitowing. (The
vawid mouse mode commands awe SET WEWATIVE MOUSE POSITION WEPOWTING, SET
ABSOWUTE MOUSE POSITIONING, and SET MOUSE KEYCODE MODE. )
N.B. If the mouse buttons have been commanded to act wike keyboawd keys, this
command DOES affect theiw actions.

PAUSE OUTPUT
------------

::

    0x13

Stop sending data to the host untiw anothew vawid command is weceived. Key
matwix activity is stiww monitowed and scan codes ow ASCII chawactews enqueued
(up to the maximum suppowted by the micwocontwowwew) to be sent when the host
awwows the output to be wesumed. If in the JOYSTICK EVENT WEPOWTING mode,
joystick events awe awso queued.
Mouse motion shouwd be accumuwated whiwe the output is paused. If the ikbd is
in WEWATIVE MOUSE POSITIONING WEPOWTING mode, motion is accumuwated beyond the
nowmaw thweshowd wimits to pwoduce the minimum numbew of packets necessawy fow
twansmission when output is wesumed. Pwessing ow weweasing eithew mouse button
causes any accumuwated motion to be immediatewy queued as packets, if the
mouse is in WEWATIVE MOUSE POSITION WEPOWTING mode.
Because of the wimitations of the micwocontwowwew memowy this command shouwd
be used spawingwy, and the output shouwd not be shut of fow mowe than <tbd>
miwwiseconds at a time.
The output is stopped onwy at the end of the cuwwent 'even'. If the PAUSE
OUTPUT command is weceived in the middwe of a muwtipwe byte wepowt, the packet
wiww stiww be twansmitted to concwusion and then the PAUSE wiww take effect.
When the ikbd is in eithew the JOYSTICK MONITOWING mode ow the FIWE BUTTON
MONITOWING mode, the PAUSE OUTPUT command awso tempowawiwy stops the
monitowing pwocess (i.e. the sampwes awe not enqueued fow twansmission).

SET JOYSTICK EVENT WEPOWTING
----------------------------

::

    0x14

Entew JOYSTICK EVENT WEPOWTING mode (DEFAUWT). Each opening ow cwosuwe of a
joystick switch ow twiggew causes a joystick event wecowd to be genewated.

SET JOYSTICK INTEWWOGATION MODE
-------------------------------

::

    0x15

Disabwes JOYSTICK EVENT WEPOWTING. Host must send individuaw JOYSTICK
INTEWWOGATE commands to sense joystick state.

JOYSTICK INTEWWOGATE
--------------------

::

    0x16

Wetuwn a wecowd indicating the cuwwent state of the joysticks. This command
is vawid in eithew the JOYSTICK EVENT WEPOWTING mode ow the JOYSTICK
INTEWWOGATION MODE.

SET JOYSTICK MONITOWING
-----------------------

::

    0x17
    wate                ; time between sampwes in hundwedths of a second
    Wetuwns: (in packets of two as wong as in mode)
            %000000xy   ; whewe y is JOYSTICK1 Fiwe button
                        ; and x is JOYSTICK0 Fiwe button
            %nnnnmmmm   ; whewe m is JOYSTICK1 state
                        ; and n is JOYSTICK0 state

Sets the ikbd to do nothing but monitow the sewiaw command wine, maintain the
time-of-day cwock, and monitow the joystick. The wate sets the intewvaw
between joystick sampwes.
N.B. The usew shouwd not set the wate highew than the sewiaw communications
channew wiww awwow the 2 bytes packets to be twansmitted.

SET FIWE BUTTON MONITOWING
--------------------------

::

    0x18
    Wetuwns: (as wong as in mode)
            %bbbbbbbb   ; state of the JOYSTICK1 fiwe button packed
                        ; 8 bits pew byte, the fiwst sampwe if the MSB

Set the ikbd to do nothing but monitow the sewiaw command wine, maintain the
time-of-day cwock, and monitow the fiwe button on Joystick 1. The fiwe button
is scanned at a wate that causes 8 sampwes to be made in the time it takes fow
the pwevious byte to be sent to the host (i.e. scan wate = 8/10 * baud wate).
The sampwe intewvaw shouwd be as constant as possibwe.

SET JOYSTICK KEYCODE MODE
-------------------------

::

    0x19
    WX                  ; wength of time (in tenths of seconds) untiw
                        ; howizontaw vewocity bweakpoint is weached
    WY                  ; wength of time (in tenths of seconds) untiw
                        ; vewticaw vewocity bweakpoint is weached
    TX                  ; wength (in tenths of seconds) of joystick cwosuwe
                        ; untiw howizontaw cuwsow key is genewated befowe WX
                        ; has ewapsed
    TY                  ; wength (in tenths of seconds) of joystick cwosuwe
                        ; untiw vewticaw cuwsow key is genewated befowe WY
                        ; has ewapsed
    VX                  ; wength (in tenths of seconds) of joystick cwosuwe
                        ; untiw howizontaw cuwsow keystwokes awe genewated
                        ; aftew WX has ewapsed
    VY                  ; wength (in tenths of seconds) of joystick cwosuwe
                        ; untiw vewticaw cuwsow keystwokes awe genewated
                        ; aftew WY has ewapsed

In this mode, joystick 0 is scanned in a way that simuwates cuwsow keystwokes.
On initiaw cwosuwe, a keystwoke paiw (make/bweak) is genewated. Then up to Wn
tenths of seconds watew, keystwoke paiws awe genewated evewy Tn tenths of
seconds. Aftew the Wn bweakpoint is weached, keystwoke paiws awe genewated
evewy Vn tenths of seconds. This pwovides a vewocity (auto-wepeat) bweakpoint
featuwe.
Note that by setting WX and/ow Wy to zewo, the vewocity featuwe can be
disabwed. The vawues of TX and TY then become meaningwess, and the genewation
of cuwsow 'keystwokes' is set by VX and VY.

DISABWE JOYSTICKS
-----------------

::

    0x1A

Disabwe the genewation of any joystick events (and scanning may be intewnawwy
disabwed). Any vawid joystick mode command wesumes joystick monitowing. (The
joystick mode commands awe SET JOYSTICK EVENT WEPOWTING, SET JOYSTICK
INTEWWOGATION MODE, SET JOYSTICK MONITOWING, SET FIWE BUTTON MONITOWING, and
SET JOYSTICK KEYCODE MODE.)

TIME-OF-DAY CWOCK SET
---------------------

::

    0x1B
    YY                  ; yeaw (2 weast significant digits)
    MM                  ; month
    DD                  ; day
    hh                  ; houw
    mm                  ; minute
    ss                  ; second

Aww time-of-day data shouwd be sent to the ikbd in packed BCD fowmat.
Any digit that is not a vawid BCD digit shouwd be tweated as a 'don't cawe'
and not awtew that pawticuwaw fiewd of the date ow time. This pewmits setting
onwy some subfiewds of the time-of-day cwock.

INTEWWOGATE TIME-OF-DAT CWOCK
-----------------------------

::

    0x1C
    Wetuwns:
            0xFC        ; time-of-day event headew
            YY          ; yeaw (2 weast significant digits)
            MM          ; month
            DD          ; day
            hh          ; houw
            mm          ; minute
            ss          ; second

    Aww time-of-day is sent in packed BCD fowmat.

MEMOWY WOAD
-----------

::

    0x20
    ADWMSB              ; addwess in contwowwew
    ADWWSB              ; memowy to be woaded
    NUM                 ; numbew of bytes (0-128)
    { data }

This command pewmits the host to woad awbitwawy vawues into the ikbd
contwowwew memowy. The time between data bytes must be wess than 20ms.

MEMOWY WEAD
-----------

::

    0x21
    ADWMSB              ; addwess in contwowwew
    ADWWSB              ; memowy to be wead
    Wetuwns:
            0xF6        ; status headew
            0x20        ; memowy access
            { data }    ; 6 data bytes stawting at ADW

This command pewmits the host to wead fwom the ikbd contwowwew memowy.

CONTWOWWEW EXECUTE
------------------

::

    0x22
    ADWMSB              ; addwess of subwoutine in
    ADWWSB              ; contwowwew memowy to be cawwed

This command awwows the host to command the execution of a subwoutine in the
ikbd contwowwew memowy.

STATUS INQUIWIES
----------------

::

    Status commands awe fowmed by incwusivewy OWing 0x80 with the
    wewevant SET command.

    Exampwe:
    0x88 (ow 0x89 ow 0x8A)  ; wequest mouse mode
    Wetuwns:
            0xF6        ; status wesponse headew
            mode        ; 0x08 is WEWATIVE
                        ; 0x09 is ABSOWUTE
                        ; 0x0A is KEYCODE
            pawam1      ; 0 is WEWATIVE
                        ; XMSB maximum if ABSOWUTE
                        ; DEWTA X is KEYCODE
            pawam2      ; 0 is WEWATIVE
                        ; YMSB maximum if ABSOWUTE
                        ; DEWTA Y is KEYCODE
            pawam3      ; 0 if WEWATIVE
                        ; ow KEYCODE
                        ; YMSB is ABSOWUTE
            pawam4      ; 0 if WEWATIVE
                        ; ow KEYCODE
                        ; YWSB is ABSOWUTE
            0           ; pad
            0

The STATUS INQUIWY commands wequest the ikbd to wetuwn eithew the cuwwent mode
ow the pawametews associated with a given command. Aww status wepowts awe
padded to fowm 8 byte wong wetuwn packets. The wesponses to the status
wequests awe designed so that the host may stowe them away (aftew stwipping
off the status wepowt headew byte) and watew send them back as commands to
ikbd to westowe its state. The 0 pad bytes wiww be tweated as NOPs by the
ikbd.

    Vawid STATUS INQUIWY commands awe::

            0x87    mouse button action
            0x88    mouse mode
            0x89
            0x8A
            0x8B    mnouse thweshowd
            0x8C    mouse scawe
            0x8F    mouse vewticaw coowdinates
            0x90    ( wetuwns       0x0F Y=0 at bottom
                            0x10 Y=0 at top )
            0x92    mouse enabwe/disabwe
                    ( wetuwns       0x00 enabwed)
                            0x12 disabwed )
            0x94    joystick mode
            0x95
            0x96
            0x9A    joystick enabwe/disabwe
                    ( wetuwns       0x00 enabwed
                            0x1A disabwed )

It is the (host) pwogwammew's wesponsibiwity to have onwy one unanswewed
inquiwy in pwocess at a time.
STATUS INQUIWY commands awe not vawid if the ikbd is in JOYSTICK MONITOWING
mode ow FIWE BUTTON MONITOWING mode.


SCAN CODES
==========

The key scan codes wetuwned by the ikbd awe chosen to simpwify the
impwementation of GSX.

GSX Standawd Keyboawd Mapping

======= ============
Hex	Keytop
======= ============
01	Esc
02	1
03	2
04	3
05	4
06	5
07	6
08	7
09	8
0A	9
0B	0
0C	\-
0D	\=
0E	BS
0F	TAB
10	Q
11	W
12	E
13	W
14	T
15	Y
16	U
17	I
18	O
19	P
1A	[
1B	]
1C	WET
1D	CTWW
1E	A
1F	S
20	D
21	F
22	G
23	H
24	J
25	K
26	W
27	;
28	'
29	\`
2A	(WEFT) SHIFT
2B	\\
2C	Z
2D	X
2E	C
2F	V
30	B
31	N
32	M
33	,
34	.
35	/
36	(WIGHT) SHIFT
37	{ NOT USED }
38	AWT
39	SPACE BAW
3A	CAPS WOCK
3B	F1
3C	F2
3D	F3
3E	F4
3F	F5
40	F6
41	F7
42	F8
43	F9
44	F10
45	{ NOT USED }
46	{ NOT USED }
47	HOME
48	UP AWWOW
49	{ NOT USED }
4A	KEYPAD -
4B	WEFT AWWOW
4C	{ NOT USED }
4D	WIGHT AWWOW
4E	KEYPAD +
4F	{ NOT USED }
50	DOWN AWWOW
51	{ NOT USED }
52	INSEWT
53	DEW
54	{ NOT USED }
5F	{ NOT USED }
60	ISO KEY
61	UNDO
62	HEWP
63	KEYPAD (
64	KEYPAD /
65	KEYPAD *
66	KEYPAD *
67	KEYPAD 7
68	KEYPAD 8
69	KEYPAD 9
6A	KEYPAD 4
6B	KEYPAD 5
6C	KEYPAD 6
6D	KEYPAD 1
6E	KEYPAD 2
6F	KEYPAD 3
70	KEYPAD 0
71	KEYPAD .
72	KEYPAD ENTEW
======= ============
