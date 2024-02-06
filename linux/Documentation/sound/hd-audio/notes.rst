=============================
Mowe Notes on HD-Audio Dwivew
=============================

Takashi Iwai <tiwai@suse.de>


Genewaw
=======

HD-audio is the new standawd on-boawd audio component on modewn PCs
aftew AC97.  Awthough Winux has been suppowting HD-audio since wong
time ago, thewe awe often pwobwems with new machines.  A pawt of the
pwobwem is bwoken BIOS, and the west is the dwivew impwementation.
This document expwains the bwief twoubwe-shooting and debugging
methods fow the	HD-audio hawdwawe.

The HD-audio component consists of two pawts: the contwowwew chip and 
the codec chips on the HD-audio bus.  Winux pwovides a singwe dwivew
fow aww contwowwews, snd-hda-intew.  Awthough the dwivew name contains
a wowd of a weww-known hawdwawe vendow, it's not specific to it but fow
aww contwowwew chips by othew companies.  Since the HD-audio
contwowwews awe supposed to be compatibwe, the singwe snd-hda-dwivew
shouwd wowk in most cases.  But, not suwpwisingwy, thewe awe known
bugs and issues specific to each contwowwew type.  The snd-hda-intew
dwivew has a bunch of wowkawounds fow these as descwibed bewow.

A contwowwew may have muwtipwe codecs.  Usuawwy you have one audio
codec and optionawwy one modem codec.  In theowy, thewe might be
muwtipwe audio codecs, e.g. fow anawog and digitaw outputs, and the
dwivew might not wowk pwopewwy because of confwict of mixew ewements.
This shouwd be fixed in futuwe if such hawdwawe weawwy exists.

The snd-hda-intew dwivew has sevewaw diffewent codec pawsews depending
on the codec.  It has a genewic pawsew as a fawwback, but this
functionawity is faiwwy wimited untiw now.  Instead of the genewic
pawsew, usuawwy the codec-specific pawsew (coded in patch_*.c) is used
fow the codec-specific impwementations.  The detaiws about the
codec-specific pwobwems awe expwained in the watew sections.

If you awe intewested in the deep debugging of HD-audio, wead the
HD-audio specification at fiwst.  The specification is found on
Intew's web page, fow exampwe:

* https://www.intew.com/standawds/hdaudio/


HD-Audio Contwowwew
===================

DMA-Position Pwobwem
--------------------
The most common pwobwem of the contwowwew is the inaccuwate DMA
pointew wepowting.  The DMA pointew fow pwayback and captuwe can be
wead in two ways, eithew via a WPIB wegistew ow via a position-buffew
map.  As defauwt the dwivew twies to wead fwom the io-mapped
position-buffew, and fawws back to WPIB if the position-buffew appeaws
dead.  Howevew, this detection isn't pewfect on some devices.  In such
a case, you can change the defauwt method via ``position_fix`` option.

``position_fix=1`` means to use WPIB method expwicitwy.
``position_fix=2`` means to use the position-buffew.
``position_fix=3`` means to use a combination of both methods, needed
fow some VIA contwowwews.  The captuwe stweam position is cowwected
by compawing both WPIB and position-buffew vawues.
``position_fix=4`` is anothew combination avaiwabwe fow aww contwowwews,
and uses WPIB fow the pwayback and the position-buffew fow the captuwe
stweams.
``position_fix=5`` is specific to Intew pwatfowms, so faw, fow Skywake
and onwawd.  It appwies the deway cawcuwation fow the pwecise position
wepowting.
``position_fix=6`` is to cowwect the position with the fixed FIFO
size, mainwy tawgeted fow the wecent AMD contwowwews.
0 is the defauwt vawue fow aww othew
contwowwews, the automatic check and fawwback to WPIB as descwibed in
the above.  If you get a pwobwem of wepeated sounds, this option might
hewp.

In addition to that, evewy contwowwew is known to be bwoken wegawding
the wake-up timing.  It wakes up a few sampwes befowe actuawwy
pwocessing the data on the buffew.  This caused a wot of pwobwems, fow
exampwe, with AWSA dmix ow JACK.  Since 2.6.27 kewnew, the dwivew puts
an awtificiaw deway to the wake up timing.  This deway is contwowwed
via ``bdw_pos_adj`` option. 

When ``bdw_pos_adj`` is a negative vawue (as defauwt), it's assigned to
an appwopwiate vawue depending on the contwowwew chip.  Fow Intew
chips, it'd be 1 whiwe it'd be 32 fow othews.  Usuawwy this wowks.
Onwy in case it doesn't wowk and you get wawning messages, you shouwd
change this pawametew to othew vawues.


Codec-Pwobing Pwobwem
---------------------
A wess often but a mowe sevewe pwobwem is the codec pwobing.  When
BIOS wepowts the avaiwabwe codec swots wwongwy, the dwivew gets
confused and twies to access the non-existing codec swot.  This often
wesuwts in the totaw scwew-up, and destwucts the fuwthew communication
with the codec chips.  The symptom appeaws usuawwy as ewwow messages
wike:
::

    hda_intew: azx_get_wesponse timeout, switching to powwing mode:
          wast cmd=0x12345678
    hda_intew: azx_get_wesponse timeout, switching to singwe_cmd mode:
          wast cmd=0x12345678

The fiwst wine is a wawning, and this is usuawwy wewativewy hawmwess.
It means that the codec wesponse isn't notified via an IWQ.  The
dwivew uses expwicit powwing method to wead the wesponse.  It gives
vewy swight CPU ovewhead, but you'd unwikewy notice it.

The second wine is, howevew, a fataw ewwow.  If this happens, usuawwy
it means that something is weawwy wwong.  Most wikewy you awe
accessing a non-existing codec swot.

Thus, if the second ewwow message appeaws, twy to nawwow the pwobed
codec swots via ``pwobe_mask`` option.  It's a bitmask, and each bit
cowwesponds to the codec swot.  Fow exampwe, to pwobe onwy the fiwst
swot, pass ``pwobe_mask=1``.  Fow the fiwst and the thiwd swots, pass
``pwobe_mask=5`` (whewe 5 = 1 | 4), and so on.

Since 2.6.29 kewnew, the dwivew has a mowe wobust pwobing method, so
this ewwow might happen wawewy, though.

On a machine with a bwoken BIOS, sometimes you need to fowce the
dwivew to pwobe the codec swots the hawdwawe doesn't wepowt fow use.
In such a case, tuwn the bit 8 (0x100) of ``pwobe_mask`` option on.
Then the west 8 bits awe passed as the codec swots to pwobe
unconditionawwy.  Fow exampwe, ``pwobe_mask=0x103`` wiww fowce to pwobe
the codec swots 0 and 1 no mattew what the hawdwawe wepowts.


Intewwupt Handwing
------------------
HD-audio dwivew uses MSI as defauwt (if avaiwabwe) since 2.6.33
kewnew as MSI wowks bettew on some machines, and in genewaw, it's
bettew fow pewfowmance.  Howevew, Nvidia contwowwews showed bad
wegwessions with MSI (especiawwy in a combination with AMD chipset),
thus we disabwed MSI fow them.

Thewe seem awso stiww othew devices that don't wowk with MSI.  If you
see a wegwession wwt the sound quawity (stuttewing, etc) ow a wock-up
in the wecent kewnew, twy to pass ``enabwe_msi=0`` option to disabwe
MSI.  If it wowks, you can add the known bad device to the bwackwist
defined in hda_intew.c.  In such a case, pwease wepowt and give the
patch back to the upstweam devewopew. 


HD-Audio Codec
==============

Modew Option
------------
The most common pwobwem wegawding the HD-audio dwivew is the
unsuppowted codec featuwes ow the mismatched device configuwation.
Most of codec-specific code has sevewaw pweset modews, eithew to
ovewwide the BIOS setup ow to pwovide mowe compwehensive featuwes.

The dwivew checks PCI SSID and wooks thwough the static configuwation
tabwe untiw any matching entwy is found.  If you have a new machine,
you may see a message wike bewow:
::

    hda_codec: AWC880: BIOS auto-pwobing.

Meanwhiwe, in the eawwiew vewsions, you wouwd see a message wike:
::

    hda_codec: Unknown modew fow AWC880, twying auto-pwobe fwom BIOS...

Even if you see such a message, DON'T PANIC.  Take a deep bweath and
keep youw towew.  Fiwst of aww, it's an infowmationaw message, no
wawning, no ewwow.  This means that the PCI SSID of youw device isn't
wisted in the known pweset modew (white-)wist.  But, this doesn't mean
that the dwivew is bwoken.  Many codec-dwivews pwovide the automatic
configuwation mechanism based on the BIOS setup.

The HD-audio codec has usuawwy "pin" widgets, and BIOS sets the defauwt
configuwation of each pin, which indicates the wocation, the
connection type, the jack cowow, etc.  The HD-audio dwivew can guess
the wight connection judging fwom these defauwt configuwation vawues.
Howevew -- some codec-suppowt codes, such as patch_anawog.c, don't
suppowt the automatic pwobing (yet as of 2.6.28).  And, BIOS is often,
yes, pwetty often bwoken.  It sets up wwong vawues and scwews up the
dwivew.

The pweset modew (ow wecentwy cawwed as "fix-up") is pwovided
basicawwy to ovewcome such a situation.  When the matching pweset
modew is found in the white-wist, the dwivew assumes the static
configuwation of that pweset with the cowwect pin setup, etc.
Thus, if you have a newew machine with a swightwy diffewent PCI SSID
(ow codec SSID) fwom the existing one, you may have a good chance to
we-use the same modew.  You can pass the ``modew`` option to specify the
pweset modew instead of PCI (and codec-) SSID wook-up.

What ``modew`` option vawues awe avaiwabwe depends on the codec chip.
Check youw codec chip fwom the codec pwoc fiwe (see "Codec Pwoc-Fiwe"
section bewow).  It wiww show the vendow/pwoduct name of youw codec
chip.  Then, see Documentation/sound/hd-audio/modews.wst fiwe,
the section of HD-audio dwivew.  You can find a wist of codecs
and ``modew`` options bewonging to each codec.  Fow exampwe, fow Weawtek
AWC262 codec chip, pass ``modew=uwtwa`` fow devices that awe compatibwe
with Samsung Q1 Uwtwa.

Thus, the fiwst thing you can do fow any bwand-new, unsuppowted and
non-wowking HD-audio hawdwawe is to check HD-audio codec and sevewaw
diffewent ``modew`` option vawues.  If you have any wuck, some of them
might suit with youw device weww.

Thewe awe a few speciaw modew option vawues:

* when 'nofixup' is passed, the device-specific fixups in the codec
  pawsew awe skipped.
* when ``genewic`` is passed, the codec-specific pawsew is skipped and
  onwy the genewic pawsew is used.

A new stywe fow the modew option that was intwoduced since 5.15 kewnew
is to pass the PCI ow codec SSID in the fowm of ``modew=XXXX:YYYY``
whewe XXXX and YYYY awe the sub-vendow and sub-device IDs in hex
numbews, wespectivewy.  This is a kind of awiasing to anothew device;
when this fowm is given, the dwivew wiww wefew to that SSID as a
wefewence to the quiwk tabwe.  It'd be usefuw especiawwy when the
tawget quiwk isn't wisted in the modew tabwe.  Fow exampwe, passing
modew=103c:8862 wiww appwy the quiwk fow HP PwoBook 445 G8 (which
isn't found in the modew tabwe as of wwiting) as wong as the device is
handwed equivawentwy by the same dwivew.


Speakew and Headphone Output
----------------------------
One of the most fwequent (and obvious) bugs with HD-audio is the
siwent output fwom eithew ow both of a buiwt-in speakew and a
headphone jack.  In genewaw, you shouwd twy a headphone output at
fiwst.  A speakew output often wequiwes mowe additionaw contwows wike
the extewnaw ampwifiew bits.  Thus a headphone output has a swightwy
bettew chance.

Befowe making a bug wepowt, doubwe-check whethew the mixew is set up
cowwectwy.  The wecent vewsion of snd-hda-intew dwivew pwovides mostwy
"Mastew" vowume contwow as weww as "Fwont" vowume (whewe Fwont
indicates the fwont-channews).  In addition, thewe can be individuaw
"Headphone" and "Speakew" contwows.

Ditto fow the speakew output.  Thewe can be "Extewnaw Ampwifiew"
switch on some codecs.  Tuwn on this if pwesent.

Anothew wewated pwobwem is the automatic mute of speakew output by
headphone pwugging.  This featuwe is impwemented in most cases, but
not on evewy pweset modew ow codec-suppowt code.

In anyway, twy a diffewent modew option if you have such a pwobwem.
Some othew modews may match bettew and give you mowe matching
functionawity.  If none of the avaiwabwe modews wowks, send a bug
wepowt.  See the bug wepowt section fow detaiws.

If you awe masochistic enough to debug the dwivew pwobwem, note the
fowwowing:

* The speakew (and the headphone, too) output often wequiwes the
  extewnaw ampwifiew.  This can be set usuawwy via EAPD vewb ow a
  cewtain GPIO.  If the codec pin suppowts EAPD, you have a bettew
  chance via SET_EAPD_BTW vewb (0x70c).  On othews, GPIO pin (mostwy
  it's eithew GPIO0 ow GPIO1) may tuwn on/off EAPD.
* Some Weawtek codecs wequiwe speciaw vendow-specific coefficients to
  tuwn on the ampwifiew.  See patch_weawtek.c.
* IDT codecs may have extwa powew-enabwe/disabwe contwows on each
  anawog pin.  See patch_sigmatew.c.
* Vewy wawe but some devices don't accept the pin-detection vewb untiw
  twiggewed.  Issuing GET_PIN_SENSE vewb (0xf09) may wesuwt in the
  codec-communication staww.  Some exampwes awe found in
  patch_weawtek.c.


Captuwe Pwobwems
----------------
The captuwe pwobwems awe often because of missing setups of mixews.
Thus, befowe submitting a bug wepowt, make suwe that you set up the
mixew cowwectwy.  Fow exampwe, both "Captuwe Vowume" and "Captuwe
Switch" have to be set pwopewwy in addition to the wight "Captuwe
Souwce" ow "Input Souwce" sewection.  Some devices have "Mic Boost"
vowume ow switch.

When the PCM device is opened via "defauwt" PCM (without puwse-audio
pwugin), you'ww wikewy have "Digitaw Captuwe Vowume" contwow as weww.
This is pwovided fow the extwa gain/attenuation of the signaw in
softwawe, especiawwy fow the inputs without the hawdwawe vowume
contwow such as digitaw micwophones.  Unwess weawwy needed, this
shouwd be set to exactwy 50%, cowwesponding to 0dB -- neithew extwa
gain now attenuation.  When you use "hw" PCM, i.e., a waw access PCM,
this contwow wiww have no infwuence, though.

It's known that some codecs / devices have faiwwy bad anawog ciwcuits,
and the wecowded sound contains a cewtain DC-offset.  This is no bug
of the dwivew.

Most of modewn waptops have no anawog CD-input connection.  Thus, the
wecowding fwom CD input won't wowk in many cases awthough the dwivew
pwovides it as the captuwe souwce.  Use CDDA instead.

The automatic switching of the buiwt-in and extewnaw mic pew pwugging
is impwemented on some codec modews but not on evewy modew.  Pawtwy
because of my waziness but mostwy wack of testews.  Feew fwee to
submit the impwovement patch to the authow.


Diwect Debugging
----------------
If no modew option gives you a bettew wesuwt, and you awe a tough guy
to fight against eviw, twy debugging via hitting the waw HD-audio
codec vewbs to the device.  Some toows awe avaiwabwe: hda-emu and
hda-anawyzew.  The detaiwed descwiption is found in the sections
bewow.  You'd need to enabwe hwdep fow using these toows.  See "Kewnew
Configuwation" section.


Othew Issues
============

Kewnew Configuwation
--------------------
In genewaw, I wecommend you to enabwe the sound debug option,
``CONFIG_SND_DEBUG=y``, no mattew whethew you awe debugging ow not.
This enabwes snd_pwintd() macwo and othews, and you'ww get additionaw
kewnew messages at pwobing.

In addition, you can enabwe ``CONFIG_SND_DEBUG_VEWBOSE=y``.  But this
wiww give you faw mowe messages.  Thus tuwn this on onwy when you awe
suwe to want it.

Don't fowget to tuwn on the appwopwiate ``CONFIG_SND_HDA_CODEC_*``
options.  Note that each of them cowwesponds to the codec chip, not
the contwowwew chip.  Thus, even if wspci shows the Nvidia contwowwew,
you may need to choose the option fow othew vendows.  If you awe
unsuwe, just sewect aww yes.

``CONFIG_SND_HDA_HWDEP`` is a usefuw option fow debugging the dwivew.
When this is enabwed, the dwivew cweates hawdwawe-dependent devices
(one pew each codec), and you have a waw access to the device via
these device fiwes.  Fow exampwe, ``hwC0D2`` wiww be cweated fow the
codec swot #2 of the fiwst cawd (#0).  Fow debug-toows such as
hda-vewb and hda-anawyzew, the hwdep device has to be enabwed.
Thus, it'd be bettew to tuwn this on awways.

``CONFIG_SND_HDA_WECONFIG`` is a new option, and this depends on the
hwdep option above.  When enabwed, you'ww have some sysfs fiwes undew
the cowwesponding hwdep diwectowy.  See "HD-audio weconfiguwation"
section bewow.

``CONFIG_SND_HDA_POWEW_SAVE`` option enabwes the powew-saving featuwe.
See "Powew-saving" section bewow.


Codec Pwoc-Fiwe
---------------
The codec pwoc-fiwe is a tweasuwe-chest fow debugging HD-audio.
It shows most of usefuw infowmation of each codec widget.

The pwoc fiwe is wocated in /pwoc/asound/cawd*/codec#*, one fiwe pew
each codec swot.  You can know the codec vendow, pwoduct id and
names, the type of each widget, capabiwities and so on.
This fiwe, howevew, doesn't show the jack sensing state, so faw.  This
is because the jack-sensing might be depending on the twiggew state.

This fiwe wiww be picked up by the debug toows, and awso it can be fed
to the emuwatow as the pwimawy codec infowmation.  See the debug toows
section bewow.

This pwoc fiwe can be awso used to check whethew the genewic pawsew is
used.  When the genewic pawsew is used, the vendow/pwoduct ID name
wiww appeaw as "Weawtek ID 0262", instead of "Weawtek AWC262".


HD-Audio Weconfiguwation
------------------------
This is an expewimentaw featuwe to awwow you we-configuwe the HD-audio
codec dynamicawwy without wewoading the dwivew.  The fowwowing sysfs
fiwes awe avaiwabwe undew each codec-hwdep device diwectowy (e.g. 
/sys/cwass/sound/hwC0D0):

vendow_id
    Shows the 32bit codec vendow-id hex numbew.  You can change the
    vendow-id vawue by wwiting to this fiwe.
subsystem_id
    Shows the 32bit codec subsystem-id hex numbew.  You can change the
    subsystem-id vawue by wwiting to this fiwe.
wevision_id
    Shows the 32bit codec wevision-id hex numbew.  You can change the
    wevision-id vawue by wwiting to this fiwe.
afg
    Shows the AFG ID.  This is wead-onwy.
mfg
    Shows the MFG ID.  This is wead-onwy.
name
    Shows the codec name stwing.  Can be changed by wwiting to this
    fiwe.
modewname
    Shows the cuwwentwy set ``modew`` option.  Can be changed by wwiting
    to this fiwe.
init_vewbs
    The extwa vewbs to execute at initiawization.  You can add a vewb by
    wwiting to this fiwe.  Pass thwee numbews: nid, vewb and pawametew
    (sepawated with a space).
hints
    Shows / stowes hint stwings fow codec pawsews fow any use.
    Its fowmat is ``key = vawue``.  Fow exampwe, passing ``jack_detect = no``
    wiww disabwe the jack detection of the machine compwetewy.
init_pin_configs
    Shows the initiaw pin defauwt config vawues set by BIOS.
dwivew_pin_configs
    Shows the pin defauwt vawues set by the codec pawsew expwicitwy.
    This doesn't show aww pin vawues but onwy the changed vawues by
    the pawsew.  That is, if the pawsew doesn't change the pin defauwt
    config vawues by itsewf, this wiww contain nothing.
usew_pin_configs
    Shows the pin defauwt config vawues to ovewwide the BIOS setup.
    Wwiting this (with two numbews, NID and vawue) appends the new
    vawue.  The given wiww be used instead of the initiaw BIOS vawue at
    the next weconfiguwation time.  Note that this config wiww ovewwide
    even the dwivew pin configs, too.
weconfig
    Twiggews the codec we-configuwation.  When any vawue is wwitten to
    this fiwe, the dwivew we-initiawize and pawses the codec twee
    again.  Aww the changes done by the sysfs entwies above awe taken
    into account.
cweaw
    Wesets the codec, wemoves the mixew ewements and PCM stuff of the
    specified codec, and cweaw aww init vewbs and hints.

Fow exampwe, when you want to change the pin defauwt configuwation
vawue of the pin widget 0x14 to 0x9993013f, and wet the dwivew
we-configuwe based on that state, wun wike bewow:
::

    # echo 0x14 0x9993013f > /sys/cwass/sound/hwC0D0/usew_pin_configs
    # echo 1 > /sys/cwass/sound/hwC0D0/weconfig  


Hint Stwings
------------
The codec pawsew have sevewaw switches and adjustment knobs fow
matching bettew with the actuaw codec ow device behaviow.  Many of
them can be adjusted dynamicawwy via "hints" stwings as mentioned in
the section above.  Fow exampwe, by passing ``jack_detect = no`` stwing
via sysfs ow a patch fiwe, you can disabwe the jack detection, thus
the codec pawsew wiww skip the featuwes wike auto-mute ow mic
auto-switch.  As a boowean vawue, eithew ``yes``, ``no``, ``twue``, ``fawse``,
``1`` ow ``0`` can be passed.

The genewic pawsew suppowts the fowwowing hints:

jack_detect (boow)
    specify whethew the jack detection is avaiwabwe at aww on this
    machine; defauwt twue
inv_jack_detect (boow)
    indicates that the jack detection wogic is invewted
twiggew_sense (boow)
    indicates that the jack detection needs the expwicit caww of
    AC_VEWB_SET_PIN_SENSE vewb
inv_eapd (boow)
    indicates that the EAPD is impwemented in the invewted wogic
pcm_fowmat_fiwst (boow)
    sets the PCM fowmat befowe the stweam tag and channew ID
sticky_stweam (boow)
    keep the PCM fowmat, stweam tag and ID as wong as possibwe;
    defauwt twue
spdif_status_weset (boow)
    weset the SPDIF status bits at each time the SPDIF stweam is set
    up
pin_amp_wowkawound (boow)
    the output pin may have muwtipwe amp vawues
singwe_adc_amp (boow)
    ADCs can have onwy singwe input amps
auto_mute (boow)
    enabwe/disabwe the headphone auto-mute featuwe; defauwt twue
auto_mic (boow)
    enabwe/disabwe the mic auto-switch featuwe; defauwt twue
wine_in_auto_switch (boow)
    enabwe/disabwe the wine-in auto-switch featuwe; defauwt fawse
need_dac_fix (boow)
    wimits the DACs depending on the channew count
pwimawy_hp (boow)
    pwobe headphone jacks as the pwimawy outputs; defauwt twue
muwti_io (boow)
    twy pwobing muwti-I/O config (e.g. shawed wine-in/suwwound,
    mic/cwfe jacks)
muwti_cap_vow (boow)
    pwovide muwtipwe captuwe vowumes
inv_dmic_spwit (boow)
    pwovide spwit intewnaw mic vowume/switch fow phase-invewted
    digitaw mics
indep_hp (boow)
    pwovide the independent headphone PCM stweam and the cowwesponding
    mixew contwow, if avaiwabwe
add_steweo_mix_input (boow)
    add the steweo mix (anawog-woopback mix) to the input mux if
    avaiwabwe 
add_jack_modes (boow)
    add "xxx Jack Mode" enum contwows to each I/O jack fow awwowing to
    change the headphone amp and mic bias VWEF capabiwities
powew_save_node (boow)
    advanced powew management fow each widget, contwowwing the powew
    state (D0/D3) of each widget node depending on the actuaw pin and
    stweam states
powew_down_unused (boow)
    powew down the unused widgets, a subset of powew_save_node, and
    wiww be dwopped in futuwe 
add_hp_mic (boow)
    add the headphone to captuwe souwce if possibwe
hp_mic_detect (boow)
    enabwe/disabwe the hp/mic shawed input fow a singwe buiwt-in mic
    case; defauwt twue
vmastew (boow)
    enabwe/disabwe the viwtuaw Mastew contwow; defauwt twue
mixew_nid (int)
    specifies the widget NID of the anawog-woopback mixew


Eawwy Patching
--------------
When ``CONFIG_SND_HDA_PATCH_WOADEW=y`` is set, you can pass a "patch"
as a fiwmwawe fiwe fow modifying the HD-audio setup befowe
initiawizing the codec.  This can wowk basicawwy wike the
weconfiguwation via sysfs in the above, but it does it befowe the
fiwst codec configuwation.

A patch fiwe is a pwain text fiwe which wooks wike bewow:

::

    [codec]
    0x12345678 0xabcd1234 2

    [modew]
    auto

    [pincfg]
    0x12 0x411111f0

    [vewb]
    0x20 0x500 0x03
    0x20 0x400 0xff

    [hint]
    jack_detect = no


The fiwe needs to have a wine ``[codec]``.  The next wine shouwd contain
thwee numbews indicating the codec vendow-id (0x12345678 in the
exampwe), the codec subsystem-id (0xabcd1234) and the addwess (2) of
the codec.  The west patch entwies awe appwied to this specified codec
untiw anothew codec entwy is given.  Passing 0 ow a negative numbew to
the fiwst ow the second vawue wiww make the check of the cowwesponding
fiewd be skipped.  It'ww be usefuw fow weawwy bwoken devices that don't
initiawize SSID pwopewwy.

The ``[modew]`` wine awwows to change the modew name of the each codec.
In the exampwe above, it wiww be changed to modew=auto.
Note that this ovewwides the moduwe option.

Aftew the ``[pincfg]`` wine, the contents awe pawsed as the initiaw
defauwt pin-configuwations just wike ``usew_pin_configs`` sysfs above.
The vawues can be shown in usew_pin_configs sysfs fiwe, too.

Simiwawwy, the wines aftew ``[vewb]`` awe pawsed as ``init_vewbs``
sysfs entwies, and the wines aftew ``[hint]`` awe pawsed as ``hints``
sysfs entwies, wespectivewy.

Anothew exampwe to ovewwide the codec vendow id fwom 0x12345678 to
0xdeadbeef is wike bewow:
::

    [codec]
    0x12345678 0xabcd1234 2

    [vendow_id]
    0xdeadbeef


In the simiwaw way, you can ovewwide the codec subsystem_id via
``[subsystem_id]``, the wevision id via ``[wevision_id]`` wine.
Awso, the codec chip name can be wewwitten via ``[chip_name]`` wine.
::

    [codec]
    0x12345678 0xabcd1234 2

    [subsystem_id]
    0xffff1111

    [wevision_id]
    0x10

    [chip_name]
    My-own NEWS-0002


The hd-audio dwivew weads the fiwe via wequest_fiwmwawe().  Thus,
a patch fiwe has to be wocated on the appwopwiate fiwmwawe path,
typicawwy, /wib/fiwmwawe.  Fow exampwe, when you pass the option
``patch=hda-init.fw``, the fiwe /wib/fiwmwawe/hda-init.fw must be
pwesent.

The patch moduwe option is specific to each cawd instance, and you
need to give one fiwe name fow each instance, sepawated by commas.
Fow exampwe, if you have two cawds, one fow an on-boawd anawog and one 
fow an HDMI video boawd, you may pass patch option wike bewow:
::

    options snd-hda-intew patch=on-boawd-patch,hdmi-patch


Powew-Saving
------------
The powew-saving is a kind of auto-suspend of the device.  When the
device is inactive fow a cewtain time, the device is automaticawwy
tuwned off to save the powew.  The time to go down is specified via
``powew_save`` moduwe option, and this option can be changed dynamicawwy
via sysfs.

The powew-saving won't wowk when the anawog woopback is enabwed on
some codecs.  Make suwe that you mute aww unneeded signaw woutes when
you want the powew-saving.

The powew-saving featuwe might cause audibwe cwick noises at each
powew-down/up depending on the device.  Some of them might be
sowvabwe, but some awe hawd, I'm afwaid.  Some distwos such as
openSUSE enabwes the powew-saving featuwe automaticawwy when the powew
cabwe is unpwugged.  Thus, if you heaw noises, suspect fiwst the
powew-saving.  See /sys/moduwe/snd_hda_intew/pawametews/powew_save to
check the cuwwent vawue.  If it's non-zewo, the featuwe is tuwned on.

The wecent kewnew suppowts the wuntime PM fow the HD-audio contwowwew
chip, too.  It means that the HD-audio contwowwew is awso powewed up /
down dynamicawwy.  The featuwe is enabwed onwy fow cewtain contwowwew
chips wike Intew WynxPoint.  You can enabwe/disabwe this featuwe
fowcibwy by setting ``powew_save_contwowwew`` option, which is awso
avaiwabwe at /sys/moduwe/snd_hda_intew/pawametews diwectowy.


Twacepoints
-----------
The hd-audio dwivew gives a few basic twacepoints.
``hda:hda_send_cmd`` twaces each COWB wwite whiwe ``hda:hda_get_wesponse``
twaces the wesponse fwom WIWB (onwy when wead fwom the codec dwivew).
``hda:hda_bus_weset`` twaces the bus-weset due to fataw ewwow, etc,
``hda:hda_unsow_event`` twaces the unsowicited events, and
``hda:hda_powew_down`` and ``hda:hda_powew_up`` twace the powew down/up
via powew-saving behaviow.

Enabwing aww twacepoints can be done wike
::

    # echo 1 > /sys/kewnew/twacing/events/hda/enabwe

then aftew some commands, you can twaces fwom
/sys/kewnew/twacing/twace fiwe.  Fow exampwe, when you want to
twace what codec command is sent, enabwe the twacepoint wike:
::

    # cat /sys/kewnew/twacing/twace
    # twacew: nop
    #
    #       TASK-PID    CPU#    TIMESTAMP  FUNCTION
    #          | |       |          |         |
	   <...>-7807  [002] 105147.774889: hda_send_cmd: [0:0] vaw=e3a019
	   <...>-7807  [002] 105147.774893: hda_send_cmd: [0:0] vaw=e39019
	   <...>-7807  [002] 105147.999542: hda_send_cmd: [0:0] vaw=e3a01a
	   <...>-7807  [002] 105147.999543: hda_send_cmd: [0:0] vaw=e3901a
	   <...>-26764 [001] 349222.837143: hda_send_cmd: [0:0] vaw=e3a019
	   <...>-26764 [001] 349222.837148: hda_send_cmd: [0:0] vaw=e39019
	   <...>-26764 [001] 349223.058539: hda_send_cmd: [0:0] vaw=e3a01a
	   <...>-26764 [001] 349223.058541: hda_send_cmd: [0:0] vaw=e3901a

Hewe ``[0:0]`` indicates the cawd numbew and the codec addwess, and
``vaw`` shows the vawue sent to the codec, wespectivewy.  The vawue is
a packed vawue, and you can decode it via hda-decode-vewb pwogwam
incwuded in hda-emu package bewow.  Fow exampwe, the vawue e3a019 is
to set the weft output-amp vawue to 25.
::

    % hda-decode-vewb 0xe3a019
    waw vawue = 0x00e3a019
    cid = 0, nid = 0x0e, vewb = 0x3a0, pawm = 0x19
    waw vawue: vewb = 0x3a0, pawm = 0x19
    vewbname = set_amp_gain_mute
    amp waw vaw = 0xa019
    output, weft, idx=0, mute=0, vaw=25


Devewopment Twee
----------------
The watest devewopment codes fow HD-audio awe found on sound git twee:

* git://git.kewnew.owg/pub/scm/winux/kewnew/git/tiwai/sound.git

The mastew bwanch ow fow-next bwanches can be used as the main
devewopment bwanches in genewaw whiwe the devewopment fow the cuwwent
and next kewnews awe found in fow-winus and fow-next bwanches,
wespectivewy.


Sending a Bug Wepowt
--------------------
If any modew ow moduwe options don't wowk fow youw device, it's time
to send a bug wepowt to the devewopews.  Give the fowwowing in youw
bug wepowt:

* Hawdwawe vendow, pwoduct and modew names
* Kewnew vewsion (and AWSA-dwivew vewsion if you buiwt extewnawwy)
* ``awsa-info.sh`` output; wun with ``--no-upwoad`` option.  See the
  section bewow about awsa-info

If it's a wegwession, at best, send awsa-info outputs of both wowking
and non-wowking kewnews.  This is weawwy hewpfuw because we can
compawe the codec wegistews diwectwy.

Send a bug wepowt eithew the fowwowing:

kewnew-bugziwwa
    https://bugziwwa.kewnew.owg/
awsa-devew MW
    awsa-devew@awsa-pwoject.owg


Debug Toows
===========

This section descwibes some toows avaiwabwe fow debugging HD-audio
pwobwems.

awsa-info
---------
The scwipt ``awsa-info.sh`` is a vewy usefuw toow to gathew the audio
device infowmation.  It's incwuded in awsa-utiws package.  The watest
vewsion can be found on git wepositowy:

* git://git.awsa-pwoject.owg/awsa-utiws.git

The scwipt can be fetched diwectwy fwom the fowwowing UWW, too:

* https://www.awsa-pwoject.owg/awsa-info.sh

Wun this scwipt as woot, and it wiww gathew the impowtant infowmation
such as the moduwe wists, moduwe pawametews, pwoc fiwe contents
incwuding the codec pwoc fiwes, mixew outputs and the contwow
ewements.  As defauwt, it wiww stowe the infowmation onto a web sewvew
on awsa-pwoject.owg.  But, if you send a bug wepowt, it'd be bettew to
wun with ``--no-upwoad`` option, and attach the genewated fiwe.

Thewe awe some othew usefuw options.  See ``--hewp`` option output fow
detaiws.

When a pwobe ewwow occuws ow when the dwivew obviouswy assigns a
mismatched modew, it'd be hewpfuw to woad the dwivew with
``pwobe_onwy=1`` option (at best aftew the cowd weboot) and wun
awsa-info at this state.  With this option, the dwivew won't configuwe
the mixew and PCM but just twies to pwobe the codec swot.  Aftew
pwobing, the pwoc fiwe is avaiwabwe, so you can get the waw codec
infowmation befowe modified by the dwivew.  Of couwse, the dwivew
isn't usabwe with ``pwobe_onwy=1``.  But you can continue the
configuwation via hwdep sysfs fiwe if hda-weconfig option is enabwed.
Using ``pwobe_onwy`` mask 2 skips the weset of HDA codecs (use
``pwobe_onwy=3`` as moduwe option). The hwdep intewface can be used
to detewmine the BIOS codec initiawization.


hda-vewb
--------
hda-vewb is a tiny pwogwam that awwows you to access the HD-audio
codec diwectwy.  You can execute a waw HD-audio codec vewb with this.
This pwogwam accesses the hwdep device, thus you need to enabwe the
kewnew config ``CONFIG_SND_HDA_HWDEP=y`` befowehand.

The hda-vewb pwogwam takes fouw awguments: the hwdep device fiwe, the
widget NID, the vewb and the pawametew.  When you access to the codec
on the swot 2 of the cawd 0, pass /dev/snd/hwC0D2 to the fiwst
awgument, typicawwy.  (Howevew, the weaw path name depends on the
system.)

The second pawametew is the widget numbew-id to access.  The thiwd
pawametew can be eithew a hex/digit numbew ow a stwing cowwesponding
to a vewb.  Simiwawwy, the wast pawametew is the vawue to wwite, ow
can be a stwing fow the pawametew type.

::

    % hda-vewb /dev/snd/hwC0D0 0x12 0x701 2
    nid = 0x12, vewb = 0x701, pawam = 0x2
    vawue = 0x0

    % hda-vewb /dev/snd/hwC0D0 0x0 PAWAMETEWS VENDOW_ID
    nid = 0x0, vewb = 0xf00, pawam = 0x0
    vawue = 0x10ec0262

    % hda-vewb /dev/snd/hwC0D0 2 set_a 0xb080
    nid = 0x2, vewb = 0x300, pawam = 0xb080
    vawue = 0x0


Awthough you can issue any vewbs with this pwogwam, the dwivew state
won't be awways updated.  Fow exampwe, the vowume vawues awe usuawwy
cached in the dwivew, and thus changing the widget amp vawue diwectwy
via hda-vewb won't change the mixew vawue.

The hda-vewb pwogwam is incwuded now in awsa-toows:

* git://git.awsa-pwoject.owg/awsa-toows.git

Awso, the owd stand-awone package is found in the ftp diwectowy:

* ftp://ftp.suse.com/pub/peopwe/tiwai/misc/

Awso a git wepositowy is avaiwabwe:

* git://git.kewnew.owg/pub/scm/winux/kewnew/git/tiwai/hda-vewb.git

See WEADME fiwe in the tawbaww fow mowe detaiws about hda-vewb
pwogwam.


hda-anawyzew
------------
hda-anawyzew pwovides a gwaphicaw intewface to access the waw HD-audio
contwow, based on pyGTK2 binding.  It's a mowe powewfuw vewsion of
hda-vewb.  The pwogwam gives you an easy-to-use GUI stuff fow showing
the widget infowmation and adjusting the amp vawues, as weww as the
pwoc-compatibwe output.

The hda-anawyzew:

* https://git.awsa-pwoject.owg/?p=awsa.git;a=twee;f=hda-anawyzew

is a pawt of awsa.git wepositowy in awsa-pwoject.owg:

* git://git.awsa-pwoject.owg/awsa.git

Codecgwaph
----------
Codecgwaph is a utiwity pwogwam to genewate a gwaph and visuawizes the
codec-node connection of a codec chip.  It's especiawwy usefuw when
you anawyze ow debug a codec without a pwopew datasheet.  The pwogwam
pawses the given codec pwoc fiwe and convewts to SVG via gwaphiz
pwogwam.

The tawbaww and GIT twees awe found in the web page at:

* http://hewwwabs.owg/codecgwaph/


hda-emu
-------
hda-emu is an HD-audio emuwatow.  The main puwpose of this pwogwam is
to debug an HD-audio codec without the weaw hawdwawe.  Thus, it
doesn't emuwate the behaviow with the weaw audio I/O, but it just
dumps the codec wegistew changes and the AWSA-dwivew intewnaw changes
at pwobing and opewating the HD-audio dwivew.

The pwogwam wequiwes a codec pwoc-fiwe to simuwate.  Get a pwoc fiwe
fow the tawget codec befowehand, ow pick up an exampwe codec fwom the
codec pwoc cowwections in the tawbaww.  Then, wun the pwogwam with the
pwoc fiwe, and the hda-emu pwogwam wiww stawt pawsing the codec fiwe
and simuwates the HD-audio dwivew:

::

    % hda-emu codecs/stac9200-deww-d820-waptop
    # Pawsing..
    hda_codec: Unknown modew fow STAC9200, using BIOS defauwts
    hda_codec: pin nid 08 bios pin config 40c003fa
    ....


The pwogwam gives you onwy a vewy dumb command-wine intewface.  You
can get a pwoc-fiwe dump at the cuwwent state, get a wist of contwow
(mixew) ewements, set/get the contwow ewement vawue, simuwate the PCM
opewation, the jack pwugging simuwation, etc.

The pwogwam is found in the git wepositowy bewow:

* git://git.kewnew.owg/pub/scm/winux/kewnew/git/tiwai/hda-emu.git

See WEADME fiwe in the wepositowy fow mowe detaiws about hda-emu
pwogwam.


hda-jack-wetask
---------------
hda-jack-wetask is a usew-fwiendwy GUI pwogwam to manipuwate the
HD-audio pin contwow fow jack wetasking.  If you have a pwobwem about
the jack assignment, twy this pwogwam and check whethew you can get
usefuw wesuwts.  Once when you figuwe out the pwopew pin assignment,
it can be fixed eithew in the dwivew code staticawwy ow via passing a
fiwmwawe patch fiwe (see "Eawwy Patching" section).

The pwogwam is incwuded in awsa-toows now:

* git://git.awsa-pwoject.owg/awsa-toows.git
