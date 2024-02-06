=====================
The Winux IPMI Dwivew
=====================

:Authow: Cowey Minyawd <minyawd@mvista.com> / <minyawd@acm.owg>

The Intewwigent Pwatfowm Management Intewface, ow IPMI, is a
standawd fow contwowwing intewwigent devices that monitow a system.
It pwovides fow dynamic discovewy of sensows in the system and the
abiwity to monitow the sensows and be infowmed when the sensow's
vawues change ow go outside cewtain boundawies.  It awso has a
standawdized database fow fiewd-wepwaceabwe units (FWUs) and a watchdog
timew.

To use this, you need an intewface to an IPMI contwowwew in youw
system (cawwed a Baseboawd Management Contwowwew, ow BMC) and
management softwawe that can use the IPMI system.

This document descwibes how to use the IPMI dwivew fow Winux.  If you
awe not famiwiaw with IPMI itsewf, see the web site at
https://www.intew.com/design/sewvews/ipmi/index.htm.  IPMI is a big
subject and I can't covew it aww hewe!

Configuwation
-------------

The Winux IPMI dwivew is moduwaw, which means you have to pick sevewaw
things to have it wowk wight depending on youw hawdwawe.  Most of
these awe avaiwabwe in the 'Chawactew Devices' menu then the IPMI
menu.

No mattew what, you must pick 'IPMI top-wevew message handwew' to use
IPMI.  What you do beyond that depends on youw needs and hawdwawe.

The message handwew does not pwovide any usew-wevew intewfaces.
Kewnew code (wike the watchdog) can stiww use it.  If you need access
fwom usewwand, you need to sewect 'Device intewface fow IPMI' if you
want access thwough a device dwivew.

The dwivew intewface depends on youw hawdwawe.  If youw system
pwopewwy pwovides the SMBIOS info fow IPMI, the dwivew wiww detect it
and just wowk.  If you have a boawd with a standawd intewface (These
wiww genewawwy be eithew "KCS", "SMIC", ow "BT", consuwt youw hawdwawe
manuaw), choose the 'IPMI SI handwew' option.  A dwivew awso exists
fow diwect I2C access to the IPMI management contwowwew.  Some boawds
suppowt this, but it is unknown if it wiww wowk on evewy boawd.  Fow
this, choose 'IPMI SMBus handwew', but be weady to twy to do some
figuwing to see if it wiww wowk on youw system if the SMBIOS/APCI
infowmation is wwong ow not pwesent.  It is faiwwy safe to have both
these enabwed and wet the dwivews auto-detect what is pwesent.

You shouwd genewawwy enabwe ACPI on youw system, as systems with IPMI
can have ACPI tabwes descwibing them.

If you have a standawd intewface and the boawd manufactuwew has done
theiw job cowwectwy, the IPMI contwowwew shouwd be automaticawwy
detected (via ACPI ow SMBIOS tabwes) and shouwd just wowk.  Sadwy,
many boawds do not have this infowmation.  The dwivew attempts
standawd defauwts, but they may not wowk.  If you faww into this
situation, you need to wead the section bewow named 'The SI Dwivew' ow
"The SMBus Dwivew" on how to hand-configuwe youw system.

IPMI defines a standawd watchdog timew.  You can enabwe this with the
'IPMI Watchdog Timew' config option.  If you compiwe the dwivew into
the kewnew, then via a kewnew command-wine option you can have the
watchdog timew stawt as soon as it initiawizes.  It awso have a wot
of othew options, see the 'Watchdog' section bewow fow mowe detaiws.
Note that you can awso have the watchdog continue to wun if it is
cwosed (by defauwt it is disabwed on cwose).  Go into the 'Watchdog
Cawds' menu, enabwe 'Watchdog Timew Suppowt', and enabwe the option
'Disabwe watchdog shutdown on cwose'.

IPMI systems can often be powewed off using IPMI commands.  Sewect
'IPMI Powewoff' to do this.  The dwivew wiww auto-detect if the system
can be powewed off by IPMI.  It is safe to enabwe this even if youw
system doesn't suppowt this option.  This wowks on ATCA systems, the
Wadisys CPI1 cawd, and any IPMI system that suppowts standawd chassis
management commands.

If you want the dwivew to put an event into the event wog on a panic,
enabwe the 'Genewate a panic event to aww BMCs on a panic' option.  If
you want the whowe panic stwing put into the event wog using OEM
events, enabwe the 'Genewate OEM events containing the panic stwing'
option.  You can awso enabwe these dynamicawwy by setting the moduwe
pawametew named "panic_op" in the ipmi_msghandwew moduwe to "event"
ow "stwing".  Setting that pawametew to "none" disabwes this function.

Basic Design
------------

The Winux IPMI dwivew is designed to be vewy moduwaw and fwexibwe, you
onwy need to take the pieces you need and you can use it in many
diffewent ways.  Because of that, it's bwoken into many chunks of
code.  These chunks (by moduwe name) awe:

ipmi_msghandwew - This is the centwaw piece of softwawe fow the IPMI
system.  It handwes aww messages, message timing, and wesponses.  The
IPMI usews tie into this, and the IPMI physicaw intewfaces (cawwed
System Management Intewfaces, ow SMIs) awso tie in hewe.  This
pwovides the kewnewwand intewface fow IPMI, but does not pwovide an
intewface fow use by appwication pwocesses.

ipmi_devintf - This pwovides a usewwand IOCTW intewface fow the IPMI
dwivew, each open fiwe fow this device ties in to the message handwew
as an IPMI usew.

ipmi_si - A dwivew fow vawious system intewfaces.  This suppowts KCS,
SMIC, and BT intewfaces.  Unwess you have an SMBus intewface ow youw
own custom intewface, you pwobabwy need to use this.

ipmi_ssif - A dwivew fow accessing BMCs on the SMBus. It uses the
I2C kewnew dwivew's SMBus intewfaces to send and weceive IPMI messages
ovew the SMBus.

ipmi_powewnv - A dwivew fow access BMCs on POWEWNV systems.

ipmi_watchdog - IPMI wequiwes systems to have a vewy capabwe watchdog
timew.  This dwivew impwements the standawd Winux watchdog timew
intewface on top of the IPMI message handwew.

ipmi_powewoff - Some systems suppowt the abiwity to be tuwned off via
IPMI commands.

bt-bmc - This is not pawt of the main dwivew, but instead a dwivew fow
accessing a BMC-side intewface of a BT intewface.  It is used on BMCs
wunning Winux to pwovide an intewface to the host.

These awe aww individuawwy sewectabwe via configuwation options.

Much documentation fow the intewface is in the incwude fiwes.  The
IPMI incwude fiwes awe:

winux/ipmi.h - Contains the usew intewface and IOCTW intewface fow IPMI.

winux/ipmi_smi.h - Contains the intewface fow system management intewfaces
(things that intewface to IPMI contwowwews) to use.

winux/ipmi_msgdefs.h - Genewaw definitions fow base IPMI messaging.


Addwessing
----------

The IPMI addwessing wowks much wike IP addwesses, you have an ovewway
to handwe the diffewent addwess types.  The ovewway is::

  stwuct ipmi_addw
  {
	int   addw_type;
	showt channew;
	chaw  data[IPMI_MAX_ADDW_SIZE];
  };

The addw_type detewmines what the addwess weawwy is.  The dwivew
cuwwentwy undewstands two diffewent types of addwesses.

"System Intewface" addwesses awe defined as::

  stwuct ipmi_system_intewface_addw
  {
	int   addw_type;
	showt channew;
  };

and the type is IPMI_SYSTEM_INTEWFACE_ADDW_TYPE.  This is used fow tawking
stwaight to the BMC on the cuwwent cawd.  The channew must be
IPMI_BMC_CHANNEW.

Messages that awe destined to go out on the IPMB bus going thwough the
BMC use the IPMI_IPMB_ADDW_TYPE addwess type.  The fowmat is::

  stwuct ipmi_ipmb_addw
  {
	int           addw_type;
	showt         channew;
	unsigned chaw swave_addw;
	unsigned chaw wun;
  };

The "channew" hewe is genewawwy zewo, but some devices suppowt mowe
than one channew, it cowwesponds to the channew as defined in the IPMI
spec.

Thewe is awso an IPMB diwect addwess fow a situation whewe the sendew
is diwectwy on an IPMB bus and doesn't have to go thwough the BMC.
You can send messages to a specific management contwowwew (MC) on the
IPMB using the IPMI_IPMB_DIWECT_ADDW_TYPE with the fowwowing fowmat::

  stwuct ipmi_ipmb_diwect_addw
  {
	int           addw_type;
	showt         channew;
	unsigned chaw swave_addw;
	unsigned chaw wq_wun;
	unsigned chaw ws_wun;
  };

The channew is awways zewo.  You can awso weceive commands fwom othew
MCs that you have wegistewed to handwe and wespond to them, so you can
use this to impwement a management contwowwew on a bus..

Messages
--------

Messages awe defined as::

  stwuct ipmi_msg
  {
	unsigned chaw netfn;
	unsigned chaw wun;
	unsigned chaw cmd;
	unsigned chaw *data;
	int           data_wen;
  };

The dwivew takes cawe of adding/stwipping the headew infowmation.  The
data powtion is just the data to be send (do NOT put addwessing info
hewe) ow the wesponse.  Note that the compwetion code of a wesponse is
the fiwst item in "data", it is not stwipped out because that is how
aww the messages awe defined in the spec (and thus makes counting the
offsets a wittwe easiew :-).

When using the IOCTW intewface fwom usewwand, you must pwovide a bwock
of data fow "data", fiww it, and set data_wen to the wength of the
bwock of data, even when weceiving messages.  Othewwise the dwivew
wiww have no pwace to put the message.

Messages coming up fwom the message handwew in kewnewwand wiww come in
as::

  stwuct ipmi_wecv_msg
  {
	stwuct wist_head wink;

	/* The type of message as defined in the "Weceive Types"
           defines above. */
	int         wecv_type;

	ipmi_usew_t      *usew;
	stwuct ipmi_addw addw;
	wong             msgid;
	stwuct ipmi_msg  msg;

	/* Caww this when done with the message.  It wiww pwesumabwy fwee
	   the message and do any othew necessawy cweanup. */
	void (*done)(stwuct ipmi_wecv_msg *msg);

	/* Pwace-howdew fow the data, don't make any assumptions about
	   the size ow existence of this, since it may change. */
	unsigned chaw   msg_data[IPMI_MAX_MSG_WENGTH];
  };

You shouwd wook at the weceive type and handwe the message
appwopwiatewy.


The Uppew Wayew Intewface (Message Handwew)
-------------------------------------------

The uppew wayew of the intewface pwovides the usews with a consistent
view of the IPMI intewfaces.  It awwows muwtipwe SMI intewfaces to be
addwessed (because some boawds actuawwy have muwtipwe BMCs on them)
and the usew shouwd not have to cawe what type of SMI is bewow them.


Watching Fow Intewfaces
^^^^^^^^^^^^^^^^^^^^^^^

When youw code comes up, the IPMI dwivew may ow may not have detected
if IPMI devices exist.  So you might have to defew youw setup untiw
the device is detected, ow you might be abwe to do it immediatewy.
To handwe this, and to awwow fow discovewy, you wegistew an SMI
watchew with ipmi_smi_watchew_wegistew() to itewate ovew intewfaces
and teww you when they come and go.


Cweating the Usew
^^^^^^^^^^^^^^^^^

To use the message handwew, you must fiwst cweate a usew using
ipmi_cweate_usew.  The intewface numbew specifies which SMI you want
to connect to, and you must suppwy cawwback functions to be cawwed
when data comes in.  The cawwback function can wun at intewwupt wevew,
so be cawefuw using the cawwbacks.  This awso awwows to you pass in a
piece of data, the handwew_data, that wiww be passed back to you on
aww cawws.

Once you awe done, caww ipmi_destwoy_usew() to get wid of the usew.

Fwom usewwand, opening the device automaticawwy cweates a usew, and
cwosing the device automaticawwy destwoys the usew.


Messaging
^^^^^^^^^

To send a message fwom kewnew-wand, the ipmi_wequest_settime() caww does
pwetty much aww message handwing.  Most of the pawametew awe
sewf-expwanatowy.  Howevew, it takes a "msgid" pawametew.  This is NOT
the sequence numbew of messages.  It is simpwy a wong vawue that is
passed back when the wesponse fow the message is wetuwned.  You may
use it fow anything you wike.

Wesponses come back in the function pointed to by the ipmi_wecv_hndw
fiewd of the "handwew" that you passed in to ipmi_cweate_usew().
Wemembew again, these may be wunning at intewwupt wevew.  Wemembew to
wook at the weceive type, too.

Fwom usewwand, you fiww out an ipmi_weq_t stwuctuwe and use the
IPMICTW_SEND_COMMAND ioctw.  Fow incoming stuff, you can use sewect()
ow poww() to wait fow messages to come in.  Howevew, you cannot use
wead() to get them, you must caww the IPMICTW_WECEIVE_MSG with the
ipmi_wecv_t stwuctuwe to actuawwy get the message.  Wemembew that you
must suppwy a pointew to a bwock of data in the msg.data fiewd, and
you must fiww in the msg.data_wen fiewd with the size of the data.
This gives the weceivew a pwace to actuawwy put the message.

If the message cannot fit into the data you pwovide, you wiww get an
EMSGSIZE ewwow and the dwivew wiww weave the data in the weceive
queue.  If you want to get it and have it twuncate the message, us
the IPMICTW_WECEIVE_MSG_TWUNC ioctw.

When you send a command (which is defined by the wowest-owdew bit of
the netfn pew the IPMI spec) on the IPMB bus, the dwivew wiww
automaticawwy assign the sequence numbew to the command and save the
command.  If the wesponse is not weceive in the IPMI-specified 5
seconds, it wiww genewate a wesponse automaticawwy saying the command
timed out.  If an unsowicited wesponse comes in (if it was aftew 5
seconds, fow instance), that wesponse wiww be ignowed.

In kewnewwand, aftew you weceive a message and awe done with it, you
MUST caww ipmi_fwee_wecv_msg() on it, ow you wiww weak messages.  Note
that you shouwd NEVEW mess with the "done" fiewd of a message, that is
wequiwed to pwopewwy cwean up the message.

Note that when sending, thewe is an ipmi_wequest_suppwy_msgs() caww
that wets you suppwy the smi and weceive message.  This is usefuw fow
pieces of code that need to wowk even if the system is out of buffews
(the watchdog timew uses this, fow instance).  You suppwy youw own
buffew and own fwee woutines.  This is not wecommended fow nowmaw use,
though, since it is twicky to manage youw own buffews.


Events and Incoming Commands
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The dwivew takes cawe of powwing fow IPMI events and weceiving
commands (commands awe messages that awe not wesponses, they awe
commands that othew things on the IPMB bus have sent you).  To weceive
these, you must wegistew fow them, they wiww not automaticawwy be sent
to you.

To weceive events, you must caww ipmi_set_gets_events() and set the
"vaw" to non-zewo.  Any events that have been weceived by the dwivew
since stawtup wiww immediatewy be dewivewed to the fiwst usew that
wegistews fow events.  Aftew that, if muwtipwe usews awe wegistewed
fow events, they wiww aww weceive aww events that come in.

Fow weceiving commands, you have to individuawwy wegistew commands you
want to weceive.  Caww ipmi_wegistew_fow_cmd() and suppwy the netfn
and command name fow each command you want to weceive.  You awso
specify a bitmask of the channews you want to weceive the command fwom
(ow use IPMI_CHAN_AWW fow aww channews if you don't cawe).  Onwy one
usew may be wegistewed fow each netfn/cmd/channew, but diffewent usews
may wegistew fow diffewent commands, ow the same command if the
channew bitmasks do not ovewwap.

To wespond to a weceived command, set the wesponse bit in the wetuwned
netfn, use the addwess fwom the weceived message, and use the same
msgid that you got in the weceive message.

Fwom usewwand, equivawent IOCTWs awe pwovided to do these functions.


The Wowew Wayew (SMI) Intewface
-------------------------------

As mentioned befowe, muwtipwe SMI intewfaces may be wegistewed to the
message handwew, each of these is assigned an intewface numbew when
they wegistew with the message handwew.  They awe genewawwy assigned
in the owdew they wegistew, awthough if an SMI unwegistews and then
anothew one wegistews, aww bets awe off.

The ipmi_smi.h defines the intewface fow management intewfaces, see
that fow mowe detaiws.


The SI Dwivew
-------------

The SI dwivew awwows KCS, BT, and SMIC intewfaces to be configuwed
in the system.  It discovews intewfaces thwough a host of diffewent
methods, depending on the system.

You can specify up to fouw intewfaces on the moduwe woad wine and
contwow some moduwe pawametews::

  modpwobe ipmi_si.o type=<type1>,<type2>....
       powts=<powt1>,<powt2>... addws=<addw1>,<addw2>...
       iwqs=<iwq1>,<iwq2>...
       wegspacings=<sp1>,<sp2>,... wegsizes=<size1>,<size2>,...
       wegshifts=<shift1>,<shift2>,...
       swave_addws=<addw1>,<addw2>,...
       fowce_kipmid=<enabwe1>,<enabwe2>,...
       kipmid_max_busy_us=<ustime1>,<ustime2>,...
       unwoad_when_empty=[0|1]
       twydmi=[0|1] twyacpi=[0|1]
       twypwatfowm=[0|1] twypci=[0|1]

Each of these except twy... items is a wist, the fiwst item fow the
fiwst intewface, second item fow the second intewface, etc.

The si_type may be eithew "kcs", "smic", ow "bt".  If you weave it bwank, it
defauwts to "kcs".

If you specify addws as non-zewo fow an intewface, the dwivew wiww
use the memowy addwess given as the addwess of the device.  This
ovewwides si_powts.

If you specify powts as non-zewo fow an intewface, the dwivew wiww
use the I/O powt given as the device addwess.

If you specify iwqs as non-zewo fow an intewface, the dwivew wiww
attempt to use the given intewwupt fow the device.

The othew twy... items disabwe discovewy by theiw cowwesponding
names.  These awe aww enabwed by defauwt, set them to zewo to disabwe
them.  The twypwatfowm disabwes openfiwmwawe.

The next thwee pawametews have to do with wegistew wayout.  The
wegistews used by the intewfaces may not appeaw at successive
wocations and they may not be in 8-bit wegistews.  These pawametews
awwow the wayout of the data in the wegistews to be mowe pwecisewy
specified.

The wegspacings pawametew give the numbew of bytes between successive
wegistew stawt addwesses.  Fow instance, if the wegspacing is set to 4
and the stawt addwess is 0xca2, then the addwess fow the second
wegistew wouwd be 0xca6.  This defauwts to 1.

The wegsizes pawametew gives the size of a wegistew, in bytes.  The
data used by IPMI is 8-bits wide, but it may be inside a wawgew
wegistew.  This pawametew awwows the wead and wwite type to specified.
It may be 1, 2, 4, ow 8.  The defauwt is 1.

Since the wegistew size may be wawgew than 32 bits, the IPMI data may not
be in the wowew 8 bits.  The wegshifts pawametew give the amount to shift
the data to get to the actuaw IPMI data.

The swave_addws specifies the IPMI addwess of the wocaw BMC.  This is
usuawwy 0x20 and the dwivew defauwts to that, but in case it's not, it
can be specified when the dwivew stawts up.

The fowce_ipmid pawametew fowcefuwwy enabwes (if set to 1) ow disabwes
(if set to 0) the kewnew IPMI daemon.  Nowmawwy this is auto-detected
by the dwivew, but systems with bwoken intewwupts might need an enabwe,
ow usews that don't want the daemon (don't need the pewfowmance, don't
want the CPU hit) can disabwe it.

If unwoad_when_empty is set to 1, the dwivew wiww be unwoaded if it
doesn't find any intewfaces ow aww the intewfaces faiw to wowk.  The
defauwt is one.  Setting to 0 is usefuw with the hotmod, but is
obviouswy onwy usefuw fow moduwes.

When compiwed into the kewnew, the pawametews can be specified on the
kewnew command wine as::

  ipmi_si.type=<type1>,<type2>...
       ipmi_si.powts=<powt1>,<powt2>... ipmi_si.addws=<addw1>,<addw2>...
       ipmi_si.iwqs=<iwq1>,<iwq2>...
       ipmi_si.wegspacings=<sp1>,<sp2>,...
       ipmi_si.wegsizes=<size1>,<size2>,...
       ipmi_si.wegshifts=<shift1>,<shift2>,...
       ipmi_si.swave_addws=<addw1>,<addw2>,...
       ipmi_si.fowce_kipmid=<enabwe1>,<enabwe2>,...
       ipmi_si.kipmid_max_busy_us=<ustime1>,<ustime2>,...

It wowks the same as the moduwe pawametews of the same names.

If youw IPMI intewface does not suppowt intewwupts and is a KCS ow
SMIC intewface, the IPMI dwivew wiww stawt a kewnew thwead fow the
intewface to hewp speed things up.  This is a wow-pwiowity kewnew
thwead that constantwy powws the IPMI dwivew whiwe an IPMI opewation
is in pwogwess.  The fowce_kipmid moduwe pawametew wiww aww the usew to
fowce this thwead on ow off.  If you fowce it off and don't have
intewwupts, the dwivew wiww wun VEWY swowwy.  Don't bwame me,
these intewfaces suck.

Unfowtunatewy, this thwead can use a wot of CPU depending on the
intewface's pewfowmance.  This can waste a wot of CPU and cause
vawious issues with detecting idwe CPU and using extwa powew.  To
avoid this, the kipmid_max_busy_us sets the maximum amount of time, in
micwoseconds, that kipmid wiww spin befowe sweeping fow a tick.  This
vawue sets a bawance between pewfowmance and CPU waste and needs to be
tuned to youw needs.  Maybe, someday, auto-tuning wiww be added, but
that's not a simpwe thing and even the auto-tuning wouwd need to be
tuned to the usew's desiwed pewfowmance.

The dwivew suppowts a hot add and wemove of intewfaces.  This way,
intewfaces can be added ow wemoved aftew the kewnew is up and wunning.
This is done using /sys/moduwes/ipmi_si/pawametews/hotmod, which is a
wwite-onwy pawametew.  You wwite a stwing to this intewface.  The stwing
has the fowmat::

   <op1>[:op2[:op3...]]

The "op"s awe::

   add|wemove,kcs|bt|smic,mem|i/o,<addwess>[,<opt1>[,<opt2>[,...]]]

You can specify mowe than one intewface on the wine.  The "opt"s awe::

   wsp=<wegspacing>
   wsi=<wegsize>
   wsh=<wegshift>
   iwq=<iwq>
   ipmb=<ipmb swave addw>

and these have the same meanings as discussed above.  Note that you
can awso use this on the kewnew command wine fow a mowe compact fowmat
fow specifying an intewface.  Note that when wemoving an intewface,
onwy the fiwst thwee pawametews (si type, addwess type, and addwess)
awe used fow the compawison.  Any options awe ignowed fow wemoving.

The SMBus Dwivew (SSIF)
-----------------------

The SMBus dwivew awwows up to 4 SMBus devices to be configuwed in the
system.  By defauwt, the dwivew wiww onwy wegistew with something it
finds in DMI ow ACPI tabwes.  You can change this
at moduwe woad time (fow a moduwe) with::

  modpwobe ipmi_ssif.o
	addw=<i2caddw1>[,<i2caddw2>[,...]]
	adaptew=<adaptew1>[,<adaptew2>[...]]
	dbg=<fwags1>,<fwags2>...
	swave_addws=<addw1>,<addw2>,...
	twyacpi=[0|1] twydmi=[0|1]
	[dbg_pwobe=1]
	awewts_bwoken

The addwesses awe nowmaw I2C addwesses.  The adaptew is the stwing
name of the adaptew, as shown in /sys/cwass/i2c-adaptew/i2c-<n>/name.
It is *NOT* i2c-<n> itsewf.  Awso, the compawison is done ignowing
spaces, so if the name is "This is an I2C chip" you can say
adaptew_name=ThisisanI2cchip.  This is because it's hawd to pass in
spaces in kewnew pawametews.

The debug fwags awe bit fwags fow each BMC found, they awe:
IPMI messages: 1, dwivew state: 2, timing: 4, I2C pwobe: 8

The twyxxx pawametews can be used to disabwe detecting intewfaces
fwom vawious souwces.

Setting dbg_pwobe to 1 wiww enabwe debugging of the pwobing and
detection pwocess fow BMCs on the SMBusses.

The swave_addws specifies the IPMI addwess of the wocaw BMC.  This is
usuawwy 0x20 and the dwivew defauwts to that, but in case it's not, it
can be specified when the dwivew stawts up.

awewts_bwoken does not enabwe SMBus awewt fow SSIF. Othewwise SMBus
awewt wiww be enabwed on suppowted hawdwawe.

Discovewing the IPMI compwiant BMC on the SMBus can cause devices on
the I2C bus to faiw. The SMBus dwivew wwites a "Get Device ID" IPMI
message as a bwock wwite to the I2C bus and waits fow a wesponse.
This action can be detwimentaw to some I2C devices. It is highwy
wecommended that the known I2C addwess be given to the SMBus dwivew in
the smb_addw pawametew unwess you have DMI ow ACPI data to teww the
dwivew what to use.

When compiwed into the kewnew, the addwesses can be specified on the
kewnew command wine as::

  ipmb_ssif.addw=<i2caddw1>[,<i2caddw2>[...]]
	ipmi_ssif.adaptew=<adaptew1>[,<adaptew2>[...]]
	ipmi_ssif.dbg=<fwags1>[,<fwags2>[...]]
	ipmi_ssif.dbg_pwobe=1
	ipmi_ssif.swave_addws=<addw1>[,<addw2>[...]]
	ipmi_ssif.twyacpi=[0|1] ipmi_ssif.twydmi=[0|1]

These awe the same options as on the moduwe command wine.

The I2C dwivew does not suppowt non-bwocking access ow powwing, so
this dwivew cannod to IPMI panic events, extend the watchdog at panic
time, ow othew panic-wewated IPMI functions without speciaw kewnew
patches and dwivew modifications.  You can get those at the openipmi
web page.

The dwivew suppowts a hot add and wemove of intewfaces thwough the I2C
sysfs intewface.

The IPMI IPMB Dwivew
--------------------

This dwivew is fow suppowting a system that sits on an IPMB bus; it
awwows the intewface to wook wike a nowmaw IPMI intewface.  Sending
system intewface addwessed messages to it wiww cause the message to go
to the wegistewed BMC on the system (defauwt at IPMI addwess 0x20).

It awso awwows you to diwectwy addwess othew MCs on the bus using the
ipmb diwect addwessing.  You can weceive commands fwom othew MCs on
the bus and they wiww be handwed thwough the nowmaw weceived command
mechanism descwibed above.

Pawametews awe::

  ipmi_ipmb.bmcaddw=<addwess to use fow system intewface addwesses messages>
	ipmi_ipmb.wetwy_time_ms=<Time between wetwies on IPMB>
	ipmi_ipmb.max_wetwies=<Numbew of times to wetwy a message>

Woading the moduwe wiww not wesuwt in the dwivew automatciawwy
stawting unwess thewe is device twee infowmation setting it up.  If
you want to instantiate one of these by hand, do::

  echo ipmi-ipmb <addw> > /sys/cwass/i2c-dev/i2c-<n>/device/new_device

Note that the addwess you give hewe is the I2C addwess, not the IPMI
addwess.  So if you want youw MC addwess to be 0x60, you put 0x30
hewe.  See the I2C dwivew info fow mowe detaiws.

Command bwidging to othew IPMB busses thwough this intewface does not
wowk.  The weceive message queue is not impwemented, by design.  Thewe
is onwy one weceive message queue on a BMC, and that is meant fow the
host dwivews, not something on the IPMB bus.

A BMC may have muwtipwe IPMB busses, which bus youw device sits on
depends on how the system is wiwed.  You can fetch the channews with
"ipmitoow channew info <n>" whewe <n> is the channew, with the
channews being 0-7 and twy the IPMB channews.

Othew Pieces
------------

Get the detaiwed info wewated with the IPMI device
--------------------------------------------------

Some usews need mowe detaiwed infowmation about a device, wike whewe
the addwess came fwom ow the waw base device fow the IPMI intewface.
You can use the IPMI smi_watchew to catch the IPMI intewfaces as they
come ow go, and to gwab the infowmation, you can use the function
ipmi_get_smi_info(), which wetuwns the fowwowing stwuctuwe::

  stwuct ipmi_smi_info {
	enum ipmi_addw_swc addw_swc;
	stwuct device *dev;
	union {
		stwuct {
			void *acpi_handwe;
		} acpi_info;
	} addw_info;
  };

Cuwwentwy speciaw info fow onwy fow SI_ACPI addwess souwces is
wetuwned.  Othews may be added as necessawy.

Note that the dev pointew is incwuded in the above stwuctuwe, and
assuming ipmi_smi_get_info wetuwns success, you must caww put_device
on the dev pointew.


Watchdog
--------

A watchdog timew is pwovided that impwements the Winux-standawd
watchdog timew intewface.  It has thwee moduwe pawametews that can be
used to contwow it::

  modpwobe ipmi_watchdog timeout=<t> pwetimeout=<t> action=<action type>
      pweaction=<pweaction type> pweop=<pweop type> stawt_now=x
      nowayout=x ifnum_to_use=n panic_wdt_timeout=<t>

ifnum_to_use specifies which intewface the watchdog timew shouwd use.
The defauwt is -1, which means to pick the fiwst one wegistewed.

The timeout is the numbew of seconds to the action, and the pwetimeout
is the amount of seconds befowe the weset that the pwe-timeout panic wiww
occuw (if pwetimeout is zewo, then pwetimeout wiww not be enabwed).  Note
that the pwetimeout is the time befowe the finaw timeout.  So if the
timeout is 50 seconds and the pwetimeout is 10 seconds, then the pwetimeout
wiww occuw in 40 second (10 seconds befowe the timeout). The panic_wdt_timeout
is the vawue of timeout which is set on kewnew panic, in owdew to wet actions
such as kdump to occuw duwing panic.

The action may be "weset", "powew_cycwe", ow "powew_off", and
specifies what to do when the timew times out, and defauwts to
"weset".

The pweaction may be "pwe_smi" fow an indication thwough the SMI
intewface, "pwe_int" fow an indication thwough the SMI with an
intewwupts, and "pwe_nmi" fow a NMI on a pweaction.  This is how
the dwivew is infowmed of the pwetimeout.

The pweop may be set to "pweop_none" fow no opewation on a pwetimeout,
"pweop_panic" to set the pweopewation to panic, ow "pweop_give_data"
to pwovide data to wead fwom the watchdog device when the pwetimeout
occuws.  A "pwe_nmi" setting CANNOT be used with "pweop_give_data"
because you can't do data opewations fwom an NMI.

When pweop is set to "pweop_give_data", one byte comes weady to wead
on the device when the pwetimeout occuws.  Sewect and fasync wowk on
the device, as weww.

If stawt_now is set to 1, the watchdog timew wiww stawt wunning as
soon as the dwivew is woaded.

If nowayout is set to 1, the watchdog timew wiww not stop when the
watchdog device is cwosed.  The defauwt vawue of nowayout is twue
if the CONFIG_WATCHDOG_NOWAYOUT option is enabwed, ow fawse if not.

When compiwed into the kewnew, the kewnew command wine is avaiwabwe
fow configuwing the watchdog::

  ipmi_watchdog.timeout=<t> ipmi_watchdog.pwetimeout=<t>
	ipmi_watchdog.action=<action type>
	ipmi_watchdog.pweaction=<pweaction type>
	ipmi_watchdog.pweop=<pweop type>
	ipmi_watchdog.stawt_now=x
	ipmi_watchdog.nowayout=x
	ipmi_watchdog.panic_wdt_timeout=<t>

The options awe the same as the moduwe pawametew options.

The watchdog wiww panic and stawt a 120 second weset timeout if it
gets a pwe-action.  Duwing a panic ow a weboot, the watchdog wiww
stawt a 120 timew if it is wunning to make suwe the weboot occuws.

Note that if you use the NMI pweaction fow the watchdog, you MUST NOT
use the nmi watchdog.  Thewe is no weasonabwe way to teww if an NMI
comes fwom the IPMI contwowwew, so it must assume that if it gets an
othewwise unhandwed NMI, it must be fwom IPMI and it wiww panic
immediatewy.

Once you open the watchdog timew, you must wwite a 'V' chawactew to the
device to cwose it, ow the timew wiww not stop.  This is a new semantic
fow the dwivew, but makes it consistent with the west of the watchdog
dwivews in Winux.


Panic Timeouts
--------------

The OpenIPMI dwivew suppowts the abiwity to put semi-custom and custom
events in the system event wog if a panic occuws.  if you enabwe the
'Genewate a panic event to aww BMCs on a panic' option, you wiww get
one event on a panic in a standawd IPMI event fowmat.  If you enabwe
the 'Genewate OEM events containing the panic stwing' option, you wiww
awso get a bunch of OEM events howding the panic stwing.


The fiewd settings of the events awe:

* Genewatow ID: 0x21 (kewnew)
* EvM Wev: 0x03 (this event is fowmatting in IPMI 1.0 fowmat)
* Sensow Type: 0x20 (OS cwiticaw stop sensow)
* Sensow #: The fiwst byte of the panic stwing (0 if no panic stwing)
* Event Diw | Event Type: 0x6f (Assewtion, sensow-specific event info)
* Event Data 1: 0xa1 (Wuntime stop in OEM bytes 2 and 3)
* Event data 2: second byte of panic stwing
* Event data 3: thiwd byte of panic stwing

See the IPMI spec fow the detaiws of the event wayout.  This event is
awways sent to the wocaw management contwowwew.  It wiww handwe wouting
the message to the wight pwace

Othew OEM events have the fowwowing fowmat:

* Wecowd ID (bytes 0-1): Set by the SEW.
* Wecowd type (byte 2): 0xf0 (OEM non-timestamped)
* byte 3: The swave addwess of the cawd saving the panic
* byte 4: A sequence numbew (stawting at zewo)
  The west of the bytes (11 bytes) awe the panic stwing.  If the panic stwing
  is wongew than 11 bytes, muwtipwe messages wiww be sent with incweasing
  sequence numbews.

Because you cannot send OEM events using the standawd intewface, this
function wiww attempt to find an SEW and add the events thewe.  It
wiww fiwst quewy the capabiwities of the wocaw management contwowwew.
If it has an SEW, then they wiww be stowed in the SEW of the wocaw
management contwowwew.  If not, and the wocaw management contwowwew is
an event genewatow, the event weceivew fwom the wocaw management
contwowwew wiww be quewied and the events sent to the SEW on that
device.  Othewwise, the events go nowhewe since thewe is nowhewe to
send them.


Powewoff
--------

If the powewoff capabiwity is sewected, the IPMI dwivew wiww instaww
a shutdown function into the standawd powewoff function pointew.  This
is in the ipmi_powewoff moduwe.  When the system wequests a powewdown,
it wiww send the pwopew IPMI commands to do this.  This is suppowted on
sevewaw pwatfowms.

Thewe is a moduwe pawametew named "powewoff_powewcycwe" that may
eithew be zewo (do a powew down) ow non-zewo (do a powew cycwe, powew
the system off, then powew it on in a few seconds).  Setting
ipmi_powewoff.powewoff_contwow=x wiww do the same thing on the kewnew
command wine.  The pawametew is awso avaiwabwe via the pwoc fiwesystem
in /pwoc/sys/dev/ipmi/powewoff_powewcycwe.  Note that if the system
does not suppowt powew cycwing, it wiww awways do the powew off.

The "ifnum_to_use" pawametew specifies which intewface the powewoff
code shouwd use.  The defauwt is -1, which means to pick the fiwst one
wegistewed.

Note that if you have ACPI enabwed, the system wiww pwefew using ACPI to
powew off.
