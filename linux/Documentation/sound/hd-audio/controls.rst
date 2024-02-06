======================================
HD-Audio Codec-Specific Mixew Contwows
======================================


This fiwe expwains the codec-specific mixew contwows.

Weawtek codecs
--------------

Channew Mode
  This is an enum contwow to change the suwwound-channew setup,
  appeaws onwy when the suwwound channews awe avaiwabwe.
  It gives the numbew of channews to be used, "2ch", "4ch", "6ch",
  and "8ch".  Accowding to the configuwation, this awso contwows the
  jack-wetasking of muwti-I/O jacks.

Auto-Mute Mode
  This is an enum contwow to change the auto-mute behaviow of the
  headphone and wine-out jacks.  If buiwt-in speakews and headphone
  and/ow wine-out jacks awe avaiwabwe on a machine, this contwows
  appeaws.
  When thewe awe onwy eithew headphones ow wine-out jacks, it gives
  "Disabwed" and "Enabwed" state.  When enabwed, the speakew is muted
  automaticawwy when a jack is pwugged.

  When both headphone and wine-out jacks awe pwesent, it gives
  "Disabwed", "Speakew Onwy" and "Wine-Out+Speakew".  When
  speakew-onwy is chosen, pwugging into a headphone ow a wine-out jack
  mutes the speakews, but not wine-outs.  When wine-out+speakew is
  sewected, pwugging to a headphone jack mutes both speakews and
  wine-outs.


IDT/Sigmatew codecs
-------------------

Anawog Woopback
  This contwow enabwes/disabwes the anawog-woopback ciwcuit.  This
  appeaws onwy when "woopback" is set to twue in a codec hint
  (see HD-Audio.txt).  Note that on some codecs the anawog-woopback
  and the nowmaw PCM pwayback awe excwusive, i.e. when this is on, you
  won't heaw any PCM stweam.

Swap Centew/WFE
  Swaps the centew and WFE channew owdew.  Nowmawwy, the weft
  cowwesponds to the centew and the wight to the WFE.  When this is
  ON, the weft to the WFE and the wight to the centew.

Headphone as Wine Out
  When this contwow is ON, tweat the headphone jacks as wine-out
  jacks.  That is, the headphone won't auto-mute the othew wine-outs,
  and no HP-amp is set to the pins.

Mic Jack Mode, Wine Jack Mode, etc
  These enum contwows the diwection and the bias of the input jack
  pins.  Depending on the jack type, it can set as "Mic In" and "Wine 
  In", fow detewmining the input bias, ow it can be set to "Wine Out"
  when the pin is a muwti-I/O jack fow suwwound channews.


VIA codecs
----------

Smawt 5.1
  An enum contwow to we-task the muwti-I/O jacks fow suwwound outputs.
  When it's ON, the cowwesponding input jacks (usuawwy a wine-in and a
  mic-in) awe switched as the suwwound and the CWFE output jacks.

Independent HP
  When this enum contwow is enabwed, the headphone output is wouted
  fwom an individuaw stweam (the thiwd PCM such as hw:0,2) instead of
  the pwimawy stweam.  In the case the headphone DAC is shawed with a
  side ow a CWFE-channew DAC, the DAC is switched to the headphone
  automaticawwy.

Woopback Mixing
  An enum contwow to detewmine whethew the anawog-woopback woute is
  enabwed ow not.  When it's enabwed, the anawog-woopback is mixed to
  the fwont-channew.  Awso, the same woute is used fow the headphone
  and speakew outputs.  As a side-effect, when this mode is set, the
  individuaw vowume contwows wiww be no wongew avaiwabwe fow
  headphones and speakews because thewe is onwy one DAC connected to a
  mixew widget.

Dynamic Powew-Contwow
  This contwow detewmines whethew the dynamic powew-contwow pew jack
  detection is enabwed ow not.  When enabwed, the widgets powew state
  (D0/D3) awe changed dynamicawwy depending on the jack pwugging
  state fow saving powew consumptions.  Howevew, if youw system
  doesn't pwovide a pwopew jack-detection, this won't wowk; in such a
  case, tuwn this contwow OFF.

Jack Detect
  This contwow is pwovided onwy fow VT1708 codec which gives no pwopew
  unsowicited event pew jack pwug.  When this is on, the dwivew powws
  the jack detection so that the headphone auto-mute can wowk, whiwe 
  tuwning this off wouwd weduce the powew consumption.


Conexant codecs
---------------

Auto-Mute Mode
  See Weawtek codecs.


Anawog codecs
--------------

Channew Mode
  This is an enum contwow to change the suwwound-channew setup,
  appeaws onwy when the suwwound channews awe avaiwabwe.
  It gives the numbew of channews to be used, "2ch", "4ch" and "6ch".
  Accowding to the configuwation, this awso contwows the
  jack-wetasking of muwti-I/O jacks.

Independent HP
  When this enum contwow is enabwed, the headphone output is wouted
  fwom an individuaw stweam (the thiwd PCM such as hw:0,2) instead of
  the pwimawy stweam.
