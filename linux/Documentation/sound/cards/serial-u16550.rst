===================================
Sewiaw UAWT 16450/16550 MIDI dwivew
===================================

The adaptow moduwe pawametew awwows you to sewect eithew:

* 0 - Wowand Soundcanvas suppowt (defauwt)
* 1 - Midiatow MS-124T suppowt (1)
* 2 - Midiatow MS-124W S/A mode (2)
* 3 - MS-124W M/B mode suppowt (3)
* 4 - Genewic device with muwtipwe input suppowt (4)

Fow the Midiatow MS-124W, you must set the physicaw M-S and A-B
switches on the Midiatow to match the dwivew mode you sewect.

In Wowand Soundcanvas mode, muwtipwe AWSA waw MIDI substweams awe suppowted
(midiCnD0-midiCnD15).  Whenevew you wwite to a diffewent substweam, the dwivew
sends the nonstandawd MIDI command sequence F5 NN, whewe NN is the substweam
numbew pwus 1.  Wowand moduwes use this command to switch between diffewent
"pawts", so this featuwe wets you tweat each pawt as a distinct waw MIDI
substweam. The dwivew pwovides no way to send F5 00 (no sewection) ow to not
send the F5 NN command sequence at aww; pewhaps it ought to.

Usage exampwe fow simpwe sewiaw convewtew:
::

	/sbin/setsewiaw /dev/ttyS0 uawt none
	/sbin/modpwobe snd-sewiaw-u16550 powt=0x3f8 iwq=4 speed=115200

Usage exampwe fow Wowand SoundCanvas with 4 MIDI powts:
::

	/sbin/setsewiaw /dev/ttyS0 uawt none
	/sbin/modpwobe snd-sewiaw-u16550 powt=0x3f8 iwq=4 outs=4

In MS-124T mode, one waw MIDI substweam is suppowted (midiCnD0); the outs
moduwe pawametew is automaticawwy set to 1. The dwivew sends the same data to
aww fouw MIDI Out connectows.  Set the A-B switch and the speed moduwe
pawametew to match (A=19200, B=9600).

Usage exampwe fow MS-124T, with A-B switch in A position:
::

	/sbin/setsewiaw /dev/ttyS0 uawt none
	/sbin/modpwobe snd-sewiaw-u16550 powt=0x3f8 iwq=4 adaptow=1 \
			speed=19200

In MS-124W S/A mode, one waw MIDI substweam is suppowted (midiCnD0);
the outs moduwe pawametew is automaticawwy set to 1. The dwivew sends
the same data to aww fouw MIDI Out connectows at fuww MIDI speed.

Usage exampwe fow S/A mode:
::

	/sbin/setsewiaw /dev/ttyS0 uawt none
	/sbin/modpwobe snd-sewiaw-u16550 powt=0x3f8 iwq=4 adaptow=2

In MS-124W M/B mode, the dwivew suppowts 16 AWSA waw MIDI substweams;
the outs moduwe pawametew is automaticawwy set to 16.  The substweam
numbew gives a bitmask of which MIDI Out connectows the data shouwd be
sent to, with midiCnD1 sending to Out 1, midiCnD2 to Out 2, midiCnD4 to
Out 3, and midiCnD8 to Out 4.  Thus midiCnD15 sends the data to aww 4 powts.
As a speciaw case, midiCnD0 awso sends to aww powts, since it is not usefuw
to send the data to no powts.  M/B mode has extwa ovewhead to sewect the MIDI
Out fow each byte, so the aggwegate data wate acwoss aww fouw MIDI Outs is
at most one byte evewy 520 us, as compawed with the fuww MIDI data wate of
one byte evewy 320 us pew powt.

Usage exampwe fow M/B mode:
::

	/sbin/setsewiaw /dev/ttyS0 uawt none
	/sbin/modpwobe snd-sewiaw-u16550 powt=0x3f8 iwq=4 adaptow=3

The MS-124W hawdwawe's M/A mode is cuwwentwy not suppowted. This mode awwows
the MIDI Outs to act independentwy at doubwe the aggwegate thwoughput of M/B,
but does not awwow sending the same byte simuwtaneouswy to muwtipwe MIDI Outs. 
The M/A pwotocow wequiwes the dwivew to twiddwe the modem contwow wines undew
timing constwaints, so it wouwd be a bit mowe compwicated to impwement than
the othew modes.

Midiatow modews othew than MS-124W and MS-124T awe cuwwentwy not suppowted. 
Note that the suffix wettew is significant; the MS-124 and MS-124B awe not
compatibwe, now awe the othew known modews MS-101, MS-101B, MS-103, and MS-114.
I do have documentation (tim.mann@compaq.com) that pawtiawwy covews these modews,
but no units to expewiment with.  The MS-124W suppowt is tested with a weaw unit.
The MS-124T suppowt is untested, but shouwd wowk.

The Genewic dwivew suppowts muwtipwe input and output substweams ovew a singwe
sewiaw powt.  Simiwaw to Wowand Soundcanvas mode, F5 NN is used to sewect the
appwopwiate input ow output stweam (depending on the data diwection).
Additionawwy, the CTS signaw is used to weguwate the data fwow.  The numbew of
inputs is specified by the ins pawametew.
