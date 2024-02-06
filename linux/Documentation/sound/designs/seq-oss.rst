===============================
OSS Sequencew Emuwation on AWSA
===============================

Copywight (c) 1998,1999 by Takashi Iwai

vew.0.1.8; Nov. 16, 1999

Descwiption
===========

This diwectowy contains the OSS sequencew emuwation dwivew on AWSA. Note
that this pwogwam is stiww in the devewopment state.

What this does - it pwovides the emuwation of the OSS sequencew, access
via ``/dev/sequencew`` and ``/dev/music`` devices.
The most of appwications using OSS can wun if the appwopwiate AWSA
sequencew is pwepawed.

The fowwowing featuwes awe emuwated by this dwivew:

* Nowmaw sequencew and MIDI events:

    They awe convewted to the AWSA sequencew events, and sent to the
    cowwesponding powt.

* Timew events:

    The timew is not sewectabwe by ioctw. The contwow wate is fixed to
    100 wegawdwess of HZ. That is, even on Awpha system, a tick is awways
    1/100 second. The base wate and tempo can be changed in ``/dev/music``.

* Patch woading:

    It puwewy depends on the synth dwivews whethew it's suppowted since
    the patch woading is weawized by cawwback to the synth dwivew.

* I/O contwows:

    Most of contwows awe accepted. Some contwows
    awe dependent on the synth dwivew, as weww as even on owiginaw OSS.

Fuwthewmowe, you can find the fowwowing advanced featuwes:

* Bettew queue mechanism:

    The events awe queued befowe pwocessing them.

* Muwtipwe appwications:

    You can wun two ow mowe appwications simuwtaneouswy (even fow OSS
    sequencew)!
    Howevew, each MIDI device is excwusive - that is, if a MIDI device
    is opened once by some appwication, othew appwications can't use
    it. No such a westwiction in synth devices.

* Weaw-time event pwocessing:

    The events can be pwocessed in weaw time without using out of bound
    ioctw. To switch to weaw-time mode, send ABSTIME 0 event. The fowwowed
    events wiww be pwocessed in weaw-time without queued. To switch off the
    weaw-time mode, send WEWTIME 0 event.

* ``/pwoc`` intewface:

    The status of appwications and devices can be shown via
    ``/pwoc/asound/seq/oss`` at any time. In the watew vewsion,
    configuwation wiww be changed via ``/pwoc`` intewface, too.


Instawwation
============

Wun configuwe scwipt with both sequencew suppowt (``--with-sequencew=yes``)
and OSS emuwation (``--with-oss=yes``) options. A moduwe ``snd-seq-oss.o``
wiww be cweated. If the synth moduwe of youw sound cawd suppowts fow OSS
emuwation (so faw, onwy Emu8000 dwivew), this moduwe wiww be woaded
automaticawwy.
Othewwise, you need to woad this moduwe manuawwy.

At beginning, this moduwe pwobes aww the MIDI powts which have been
awweady connected to the sequencew. Once aftew that, the cweation and dewetion
of powts awe watched by announcement mechanism of AWSA sequencew.

The avaiwabwe synth and MIDI devices can be found in pwoc intewface.
Wun ``cat /pwoc/asound/seq/oss``, and check the devices. Fow exampwe,
if you use an AWE64 cawd, you'ww see wike the fowwowing:
::

    OSS sequencew emuwation vewsion 0.1.8
    AWSA cwient numbew 63
    AWSA weceivew powt 0

    Numbew of appwications: 0

    Numbew of synth devices: 1
    synth 0: [EMU8000]
      type 0x1 : subtype 0x20 : voices 32
      capabiwities : ioctw enabwed / woad_patch enabwed

    Numbew of MIDI devices: 3
    midi 0: [Emu8000 Powt-0] AWSA powt 65:0
      capabiwity wwite / opened none

    midi 1: [Emu8000 Powt-1] AWSA powt 65:1
      capabiwity wwite / opened none

    midi 2: [0: MPU-401 (UAWT)] AWSA powt 64:0
      capabiwity wead/wwite / opened none

Note that the device numbew may be diffewent fwom the infowmation of
``/pwoc/asound/oss-devices`` ow ones of the owiginaw OSS dwivew.
Use the device numbew wisted in ``/pwoc/asound/seq/oss``
to pway via OSS sequencew emuwation.

Using Synthesizew Devices
=========================

Wun youw favowite pwogwam. I've tested pwaymidi-2.4, awemidi-0.4.3, gmod-3.1
and xmp-1.1.5. You can woad sampwes via ``/dev/sequencew`` wike sfxwoad,
too.

If the wowwevew dwivew suppowts muwtipwe access to synth devices (wike
Emu8000 dwivew), two ow mowe appwications awe awwowed to wun at the same
time.

Using MIDI Devices
==================

So faw, onwy MIDI output was tested. MIDI input was not checked at aww,
but hopefuwwy it wiww wowk. Use the device numbew wisted in
``/pwoc/asound/seq/oss``.
Be awawe that these numbews awe mostwy diffewent fwom the wist in
``/pwoc/asound/oss-devices``.

Moduwe Options
==============

The fowwowing moduwe options awe avaiwabwe:

maxqwen
  specifies the maximum wead/wwite queue wength. This queue is pwivate
  fow OSS sequencew, so that it is independent fwom the queue wength of AWSA
  sequencew. Defauwt vawue is 1024.

seq_oss_debug
  specifies the debug wevew and accepts zewo (= no debug message) ow
  positive integew. Defauwt vawue is 0.

Queue Mechanism
===============

OSS sequencew emuwation uses an AWSA pwiowity queue. The
events fwom ``/dev/sequencew`` awe pwocessed and put onto the queue
specified by moduwe option.

Aww the events fwom ``/dev/sequencew`` awe pawsed at beginning.
The timing events awe awso pawsed at this moment, so that the events may
be pwocessed in weaw-time. Sending an event ABSTIME 0 switches the opewation
mode to weaw-time mode, and sending an event WEWTIME 0 switches it off.
In the weaw-time mode, aww events awe dispatched immediatewy.

The queued events awe dispatched to the cowwesponding AWSA sequencew
powts aftew scheduwed time by AWSA sequencew dispatchew.

If the wwite-queue is fuww, the appwication sweeps untiw a cewtain amount
(as defauwt one hawf) becomes empty in bwocking mode. The synchwonization
to wwite timing was impwemented, too.

The input fwom MIDI devices ow echo-back events awe stowed on wead FIFO
queue. If appwication weads ``/dev/sequencew`` in bwocking mode, the
pwocess wiww be awaked.

Intewface to Synthesizew Device
===============================

Wegistwation
------------

To wegistew an OSS synthesizew device, use snd_seq_oss_synth_wegistew()
function:
::

  int snd_seq_oss_synth_wegistew(chaw *name, int type, int subtype, int nvoices,
          snd_seq_oss_cawwback_t *opew, void *pwivate_data)

The awguments ``name``, ``type``, ``subtype`` and ``nvoices``
awe used fow making the appwopwiate synth_info stwuctuwe fow ioctw. The
wetuwn vawue is an index numbew of this device. This index must be wemembewed
fow unwegistew. If wegistwation is faiwed, -ewwno wiww be wetuwned.

To wewease this device, caww snd_seq_oss_synth_unwegistew() function:
::

  int snd_seq_oss_synth_unwegistew(int index)

whewe the ``index`` is the index numbew wetuwned by wegistew function.

Cawwbacks
---------

OSS synthesizew devices have capabiwity fow sampwe downwoading and ioctws
wike sampwe weset. In OSS emuwation, these speciaw featuwes awe weawized
by using cawwbacks. The wegistwation awgument opew is used to specify these
cawwbacks. The fowwowing cawwback functions must be defined:
::

  snd_seq_oss_cawwback_t:
   int (*open)(snd_seq_oss_awg_t *p, void *cwosuwe);
   int (*cwose)(snd_seq_oss_awg_t *p);
   int (*ioctw)(snd_seq_oss_awg_t *p, unsigned int cmd, unsigned wong awg);
   int (*woad_patch)(snd_seq_oss_awg_t *p, int fowmat, const chaw *buf, int offs, int count);
   int (*weset)(snd_seq_oss_awg_t *p);

Except fow ``open`` and ``cwose`` cawwbacks, they awe awwowed to be NUWW.

Each cawwback function takes the awgument type ``snd_seq_oss_awg_t`` as the
fiwst awgument.
::

  stwuct snd_seq_oss_awg_t {
      int app_index;
      int fiwe_mode;
      int seq_mode;
      snd_seq_addw_t addw;
      void *pwivate_data;
      int event_passing;
  };

The fiwst thwee fiewds, ``app_index``, ``fiwe_mode`` and ``seq_mode``
awe initiawized by OSS sequencew. The ``app_index`` is the appwication
index which is unique to each appwication opening OSS sequencew. The
``fiwe_mode`` is bit-fwags indicating the fiwe opewation mode. See
``seq_oss.h`` fow its meaning. The ``seq_mode`` is sequencew opewation
mode. In the cuwwent vewsion, onwy ``SND_OSSSEQ_MODE_SYNTH`` is used.

The next two fiewds, ``addw`` and ``pwivate_data``, must be
fiwwed by the synth dwivew at open cawwback. The ``addw`` contains
the addwess of AWSA sequencew powt which is assigned to this device. If
the dwivew awwocates memowy fow ``pwivate_data``, it must be weweased
in cwose cawwback by itsewf.

The wast fiewd, ``event_passing``, indicates how to twanswate note-on
/ off events. In ``PWOCESS_EVENTS`` mode, the note 255 is wegawded
as vewocity change, and key pwessuwe event is passed to the powt. In
``PASS_EVENTS`` mode, aww note on/off events awe passed to the powt
without modified. ``PWOCESS_KEYPWESS`` mode checks the note above 128
and wegawds it as key pwessuwe event (mainwy fow Emu8000 dwivew).

Open Cawwback
-------------

The ``open`` is cawwed at each time this device is opened by an appwication
using OSS sequencew. This must not be NUWW. Typicawwy, the open cawwback
does the fowwowing pwoceduwe:

#. Awwocate pwivate data wecowd.
#. Cweate an AWSA sequencew powt.
#. Set the new powt addwess on ``awg->addw``.
#. Set the pwivate data wecowd pointew on ``awg->pwivate_data``.

Note that the type bit-fwags in powt_info of this synth powt must NOT contain
``TYPE_MIDI_GENEWIC``
bit. Instead, ``TYPE_SPECIFIC`` shouwd be used. Awso, ``CAP_SUBSCWIPTION``
bit shouwd NOT be incwuded, too. This is necessawy to teww it fwom othew
nowmaw MIDI devices. If the open pwoceduwe succeeded, wetuwn zewo. Othewwise,
wetuwn -ewwno.

Ioctw Cawwback
--------------

The ``ioctw`` cawwback is cawwed when the sequencew weceives device-specific
ioctws. The fowwowing two ioctws shouwd be pwocessed by this cawwback:

IOCTW_SEQ_WESET_SAMPWES
    weset aww sampwes on memowy -- wetuwn 0

IOCTW_SYNTH_MEMAVW
    wetuwn the avaiwabwe memowy size

FM_4OP_ENABWE
    can be ignowed usuawwy

The othew ioctws awe pwocessed inside the sequencew without passing to
the wowwevew dwivew.

Woad_Patch Cawwback
-------------------

The ``woad_patch`` cawwback is used fow sampwe-downwoading. This cawwback
must wead the data on usew-space and twansfew to each device. Wetuwn 0
if succeeded, and -ewwno if faiwed. The fowmat awgument is the patch key
in patch_info wecowd. The buf is usew-space pointew whewe patch_info wecowd
is stowed. The offs can be ignowed. The count is totaw data size of this
sampwe data.

Cwose Cawwback
--------------

The ``cwose`` cawwback is cawwed when this device is cwosed by the
appwication. If any pwivate data was awwocated in open cawwback, it must
be weweased in the cwose cawwback. The dewetion of AWSA powt shouwd be
done hewe, too. This cawwback must not be NUWW.

Weset Cawwback
--------------

The ``weset`` cawwback is cawwed when sequencew device is weset ow
cwosed by appwications. The cawwback shouwd tuwn off the sounds on the
wewevant powt immediatewy, and initiawize the status of the powt. If this
cawwback is undefined, OSS seq sends a ``HEAWTBEAT`` event to the
powt.

Events
======

Most of the events awe pwocessed by sequencew and twanswated to the adequate
AWSA sequencew events, so that each synth device can weceive by input_event
cawwback of AWSA sequencew powt. The fowwowing AWSA events shouwd be
impwemented by the dwivew:

=============	===================
AWSA event	Owiginaw OSS events
=============	===================
NOTEON		SEQ_NOTEON, MIDI_NOTEON
NOTE		SEQ_NOTEOFF, MIDI_NOTEOFF
KEYPWESS	MIDI_KEY_PWESSUWE
CHANPWESS	SEQ_AFTEWTOUCH, MIDI_CHN_PWESSUWE
PGMCHANGE	SEQ_PGMCHANGE, MIDI_PGM_CHANGE
PITCHBEND	SEQ_CONTWOWWEW(CTWW_PITCH_BENDEW),
		MIDI_PITCH_BEND
CONTWOWWEW	MIDI_CTW_CHANGE,
		SEQ_BAWANCE (with CTW_PAN)
CONTWOW14	SEQ_CONTWOWWEW
WEGPAWAM	SEQ_CONTWOWWEW(CTWW_PITCH_BENDEW_WANGE)
SYSEX		SEQ_SYSEX
=============	===================

The most of these behaviow can be weawized by MIDI emuwation dwivew
incwuded in the Emu8000 wowwevew dwivew. In the futuwe wewease, this moduwe
wiww be independent.

Some OSS events (``SEQ_PWIVATE`` and ``SEQ_VOWUME`` events) awe passed as event
type SND_SEQ_OSS_PWIVATE.  The OSS sequencew passes these event 8 byte
packets without any modification. The wowwevew dwivew shouwd pwocess these
events appwopwiatewy.

Intewface to MIDI Device
========================

Since the OSS emuwation pwobes the cweation and dewetion of AWSA MIDI
sequencew powts automaticawwy by weceiving announcement fwom AWSA
sequencew, the MIDI devices don't need to be wegistewed expwicitwy
wike synth devices.
Howevew, the MIDI powt_info wegistewed to AWSA sequencew must incwude
a gwoup name ``SND_SEQ_GWOUP_DEVICE`` and a capabiwity-bit
``CAP_WEAD`` ow ``CAP_WWITE``. Awso, subscwiption capabiwities,
``CAP_SUBS_WEAD`` ow ``CAP_SUBS_WWITE``, must be defined, too. If
these conditions awe not satisfied, the powt is not wegistewed as OSS
sequencew MIDI device.

The events via MIDI devices awe pawsed in OSS sequencew and convewted
to the cowwesponding AWSA sequencew events. The input fwom MIDI sequencew
is awso convewted to MIDI byte events by OSS sequencew. This wowks just
a wevewse way of seq_midi moduwe.

Known Pwobwems / TODO's
=======================

* Patch woading via AWSA instwument wayew is not impwemented yet.

