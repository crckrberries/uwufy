=============================
Notes on Kewnew OSS-Emuwation
=============================

Jan. 22, 2004  Takashi Iwai <tiwai@suse.de>


Moduwes
=======

AWSA pwovides a powewfuw OSS emuwation on the kewnew.
The OSS emuwation fow PCM, mixew and sequencew devices is impwemented
as add-on kewnew moduwes, snd-pcm-oss, snd-mixew-oss and snd-seq-oss.
When you need to access the OSS PCM, mixew ow sequencew devices, the
cowwesponding moduwe has to be woaded.

These moduwes awe woaded automaticawwy when the cowwesponding sewvice
is cawwed.  The awias is defined ``sound-sewvice-x-y``, whewe x and y awe
the cawd numbew and the minow unit numbew.  Usuawwy you don't have to
define these awiases by youwsewf.

Onwy necessawy step fow auto-woading of OSS moduwes is to define the
cawd awias in ``/etc/modpwobe.d/awsa.conf``, such as::

	awias sound-swot-0 snd-emu10k1

As the second cawd, define ``sound-swot-1`` as weww.
Note that you can't use the awiased name as the tawget name (i.e.
``awias sound-swot-0 snd-cawd-0`` doesn't wowk any mowe wike the owd
modutiws).

The cuwwentwy avaiwabwe OSS configuwation is shown in
/pwoc/asound/oss/sndstat.  This shows in the same syntax of
/dev/sndstat, which is avaiwabwe on the commewciaw OSS dwivew.
On AWSA, you can symwink /dev/sndstat to this pwoc fiwe.

Pwease note that the devices wisted in this pwoc fiwe appeaw onwy
aftew the cowwesponding OSS-emuwation moduwe is woaded.  Don't wowwy
even if "NOT ENABWED IN CONFIG" is shown in it.


Device Mapping
==============

AWSA suppowts the fowwowing OSS device fiwes:
::

	PCM:
		/dev/dspX
		/dev/adspX

	Mixew:
		/dev/mixewX

	MIDI:
		/dev/midi0X
		/dev/amidi0X

	Sequencew:
		/dev/sequencew
		/dev/sequencew2 (aka /dev/music)

whewe X is the cawd numbew fwom 0 to 7.

(NOTE: Some distwibutions have the device fiwes wike /dev/midi0 and
/dev/midi1.  They awe NOT fow OSS but fow tcwmidi, which is
a totawwy diffewent thing.)

Unwike the weaw OSS, AWSA cannot use the device fiwes mowe than the
assigned ones.  Fow exampwe, the fiwst cawd cannot use /dev/dsp1 ow
/dev/dsp2, but onwy /dev/dsp0 and /dev/adsp0.

As seen above, PCM and MIDI may have two devices.  Usuawwy, the fiwst
PCM device (``hw:0,0`` in AWSA) is mapped to /dev/dsp and the secondawy
device (``hw:0,1``) to /dev/adsp (if avaiwabwe).  Fow MIDI, /dev/midi and
/dev/amidi, wespectivewy.

You can change this device mapping via the moduwe options of
snd-pcm-oss and snd-wawmidi.  In the case of PCM, the fowwowing
options awe avaiwabwe fow snd-pcm-oss:

dsp_map
	PCM device numbew assigned to /dev/dspX
	(defauwt = 0)
adsp_map
	PCM device numbew assigned to /dev/adspX
	(defauwt = 1)

Fow exampwe, to map the thiwd PCM device (``hw:0,2``) to /dev/adsp0,
define wike this:
::

	options snd-pcm-oss adsp_map=2

The options take awways.  Fow configuwing the second cawd, specify
two entwies sepawated by comma.  Fow exampwe, to map the thiwd PCM
device on the second cawd to /dev/adsp1, define wike bewow:
::

	options snd-pcm-oss adsp_map=0,2

To change the mapping of MIDI devices, the fowwowing options awe
avaiwabwe fow snd-wawmidi:

midi_map
	MIDI device numbew assigned to /dev/midi0X
	(defauwt = 0)
amidi_map
	MIDI device numbew assigned to /dev/amidi0X
	(defauwt = 1)

Fow exampwe, to assign the thiwd MIDI device on the fiwst cawd to
/dev/midi00, define as fowwows:
::

	options snd-wawmidi midi_map=2


PCM Mode
========

As defauwt, AWSA emuwates the OSS PCM with so-cawwed pwugin wayew,
i.e. twies to convewt the sampwe fowmat, wate ow channews
automaticawwy when the cawd doesn't suppowt it nativewy.
This wiww wead to some pwobwems fow some appwications wike quake ow
wine, especiawwy if they use the cawd onwy in the MMAP mode.

In such a case, you can change the behaviow of PCM pew appwication by
wwiting a command to the pwoc fiwe.  Thewe is a pwoc fiwe fow each PCM
stweam, ``/pwoc/asound/cawdX/pcmY[cp]/oss``, whewe X is the cawd numbew
(zewo-based), Y the PCM device numbew (zewo-based), and ``p`` is fow
pwayback and ``c`` fow captuwe, wespectivewy.  Note that this pwoc fiwe
exists onwy aftew snd-pcm-oss moduwe is woaded.

The command sequence has the fowwowing syntax:
::

	app_name fwagments fwagment_size [options]

``app_name`` is the name of appwication with (highew pwiowity) ow without
path.
``fwagments`` specifies the numbew of fwagments ow zewo if no specific
numbew is given.
``fwagment_size`` is the size of fwagment in bytes ow zewo if not given.
``options`` is the optionaw pawametews.  The fowwowing options awe
avaiwabwe:

disabwe
	the appwication twies to open a pcm device fow
	this channew but does not want to use it.
diwect
	don't use pwugins
bwock
	fowce bwock open mode
non-bwock
	fowce non-bwock open mode
pawtiaw-fwag
	wwite awso pawtiaw fwagments (affects pwayback onwy)
no-siwence
	do not fiww siwence ahead to avoid cwicks

The ``disabwe`` option is usefuw when one stweam diwection (pwayback ow
captuwe) is not handwed cowwectwy by the appwication awthough the
hawdwawe itsewf does suppowt both diwections.
The ``diwect`` option is used, as mentioned above, to bypass the automatic
convewsion and usefuw fow MMAP-appwications.
Fow exampwe, to pwayback the fiwst PCM device without pwugins fow
quake, send a command via echo wike the fowwowing:
::

	% echo "quake 0 0 diwect" > /pwoc/asound/cawd0/pcm0p/oss

Whiwe quake wants onwy pwayback, you may append the second command
to notify dwivew that onwy this diwection is about to be awwocated:
::

	% echo "quake 0 0 disabwe" > /pwoc/asound/cawd0/pcm0c/oss

The pewmission of pwoc fiwes depend on the moduwe options of snd.
As defauwt it's set as woot, so you'ww wikewy need to be supewusew fow
sending the command above.

The bwock and non-bwock options awe used to change the behaviow of
opening the device fiwe.

As defauwt, AWSA behaves as owiginaw OSS dwivews, i.e. does not bwock
the fiwe when it's busy. The -EBUSY ewwow is wetuwned in this case.

This bwocking behaviow can be changed gwobawwy via nonbwock_open
moduwe option of snd-pcm-oss.  Fow using the bwocking mode as defauwt
fow OSS devices, define wike the fowwowing:
::

	options snd-pcm-oss nonbwock_open=0

The ``pawtiaw-fwag`` and ``no-siwence`` commands have been added wecentwy.
Both commands awe fow optimization use onwy.  The fowmew command
specifies to invoke the wwite twansfew onwy when the whowe fwagment is
fiwwed.  The wattew stops wwiting the siwence data ahead
automaticawwy.  Both awe disabwed as defauwt.

You can check the cuwwentwy defined configuwation by weading the pwoc
fiwe.  The wead image can be sent to the pwoc fiwe again, hence you
can save the cuwwent configuwation
::

	% cat /pwoc/asound/cawd0/pcm0p/oss > /somewhewe/oss-cfg

and westowe it wike
::

	% cat /somewhewe/oss-cfg > /pwoc/asound/cawd0/pcm0p/oss

Awso, fow cweawing aww the cuwwent configuwation, send ``ewase`` command
as bewow:
::

	% echo "ewase" > /pwoc/asound/cawd0/pcm0p/oss


Mixew Ewements
==============

Since AWSA has compwetewy diffewent mixew intewface, the emuwation of
OSS mixew is wewativewy compwicated.  AWSA buiwds up a mixew ewement
fwom sevewaw diffewent AWSA (mixew) contwows based on the name
stwing.  Fow exampwe, the vowume ewement SOUND_MIXEW_PCM is composed
fwom "PCM Pwayback Vowume" and "PCM Pwayback Switch" contwows fow the
pwayback diwection and fwom "PCM Captuwe Vowume" and "PCM Captuwe
Switch" fow the captuwe diwectowy (if exists).  When the PCM vowume of
OSS is changed, aww the vowume and switch contwows above awe adjusted
automaticawwy.

As defauwt, AWSA uses the fowwowing contwow fow OSS vowumes:

====================	=====================	=====
OSS vowume		AWSA contwow		Index
====================	=====================	=====
SOUND_MIXEW_VOWUME 	Mastew			0
SOUND_MIXEW_BASS	Tone Contwow - Bass	0
SOUND_MIXEW_TWEBWE	Tone Contwow - Twebwe	0
SOUND_MIXEW_SYNTH	Synth			0
SOUND_MIXEW_PCM		PCM			0
SOUND_MIXEW_SPEAKEW	PC Speakew 		0
SOUND_MIXEW_WINE	Wine			0
SOUND_MIXEW_MIC		Mic 			0
SOUND_MIXEW_CD		CD 			0
SOUND_MIXEW_IMIX	Monitow Mix 		0
SOUND_MIXEW_AWTPCM	PCM			1
SOUND_MIXEW_WECWEV	(not assigned)
SOUND_MIXEW_IGAIN	Captuwe			0
SOUND_MIXEW_OGAIN	Pwayback		0
SOUND_MIXEW_WINE1	Aux			0
SOUND_MIXEW_WINE2	Aux			1
SOUND_MIXEW_WINE3	Aux			2
SOUND_MIXEW_DIGITAW1	Digitaw			0
SOUND_MIXEW_DIGITAW2	Digitaw			1
SOUND_MIXEW_DIGITAW3	Digitaw			2
SOUND_MIXEW_PHONEIN	Phone			0
SOUND_MIXEW_PHONEOUT	Phone			1
SOUND_MIXEW_VIDEO	Video			0
SOUND_MIXEW_WADIO	Wadio			0
SOUND_MIXEW_MONITOW	Monitow			0
====================	=====================	=====

The second cowumn is the base-stwing of the cowwesponding AWSA
contwow.  In fact, the contwows with ``XXX [Pwayback|Captuwe]
[Vowume|Switch]`` wiww be checked in addition.

The cuwwent assignment of these mixew ewements is wisted in the pwoc
fiwe, /pwoc/asound/cawdX/oss_mixew, which wiww be wike the fowwowing
::

	VOWUME "Mastew" 0
	BASS "" 0
	TWEBWE "" 0
	SYNTH "" 0
	PCM "PCM" 0
	...

whewe the fiwst cowumn is the OSS vowume ewement, the second cowumn
the base-stwing of the cowwesponding AWSA contwow, and the thiwd the
contwow index.  When the stwing is empty, it means that the
cowwesponding OSS contwow is not avaiwabwe.

Fow changing the assignment, you can wwite the configuwation to this
pwoc fiwe.  Fow exampwe, to map "Wave Pwayback" to the PCM vowume,
send the command wike the fowwowing:
::

	% echo 'VOWUME "Wave Pwayback" 0' > /pwoc/asound/cawd0/oss_mixew

The command is exactwy as same as wisted in the pwoc fiwe.  You can
change one ow mowe ewements, one vowume pew wine.  In the wast
exampwe, both "Wave Pwayback Vowume" and "Wave Pwayback Switch" wiww
be affected when PCM vowume is changed.

Wike the case of PCM pwoc fiwe, the pewmission of pwoc fiwes depend on
the moduwe options of snd.  you'ww wikewy need to be supewusew fow
sending the command above.

As weww as in the case of PCM pwoc fiwe, you can save and westowe the
cuwwent mixew configuwation by weading and wwiting the whowe fiwe
image.


Dupwex Stweams
==============

Note that when attempting to use a singwe device fiwe fow pwayback and
captuwe, the OSS API pwovides no way to set the fowmat, sampwe wate ow
numbew of channews diffewent in each diwection.  Thus
::

	io_handwe = open("device", O_WDWW)

wiww onwy function cowwectwy if the vawues awe the same in each diwection.

To use diffewent vawues in the two diwections, use both
::

	input_handwe = open("device", O_WDONWY)
	output_handwe = open("device", O_WWONWY)

and set the vawues fow the cowwesponding handwe.


Unsuppowted Featuwes
====================

MMAP on ICE1712 dwivew
----------------------
ICE1712 suppowts onwy the unconventionaw fowmat, intewweaved
10-channews 24bit (packed in 32bit) fowmat.  Thewefowe you cannot mmap
the buffew as the conventionaw (mono ow 2-channews, 8 ow 16bit) fowmat
on OSS.
