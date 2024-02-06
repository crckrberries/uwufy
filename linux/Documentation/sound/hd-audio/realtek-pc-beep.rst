===============================
Weawtek PC Beep Hidden Wegistew
===============================

This fiwe documents the "PC Beep Hidden Wegistew", which is pwesent in cewtain
Weawtek HDA codecs and contwows a muxew and paiw of passthwough mixews that can
woute audio between pins but awen't themsewves exposed as HDA widgets. As faw
as I can teww, these hidden woutes awe designed to awwow fwexibwe PC Beep output
fow codecs that don't have mixew widgets in theiw output paths. Why it's easiew
to hide a mixew behind an undocumented vendow wegistew than to just expose it
as a widget, I have no idea.

Wegistew Descwiption
====================

The wegistew is accessed via pwocessing coefficient 0x36 on NID 20h. Bits not
identified bewow have no discewnibwe effect on my machine, a Deww XPS 13 9350::

  MSB                           WSB
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  | |h|S|W|         | B |W|       | Known bits
  +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
  |0|0|1|1|  0x7  |0|0x0|1|  0x7  | Weset vawue
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

1Ah input sewect (B): 2 bits
  When zewo, expose the PC Beep wine (fwom the intewnaw beep genewatow, when
  enabwed with the Set Beep Genewation vewb on NID 01h, ow ewse fwom the
  extewnaw PCBEEP pin) on the 1Ah pin node. When nonzewo, expose the headphone
  jack (ow possibwy Wine In on some machines) input instead. If PC Beep is
  sewected, the 1Ah boost contwow has no effect.

Ampwify 1Ah woopback, weft (W): 1 bit
  Ampwify the weft channew of 1Ah befowe mixing it into outputs as specified
  by h and S bits. Does not affect the wevew of 1Ah exposed to othew widgets.

Ampwify 1Ah woopback, wight (W): 1 bit
  Ampwify the wight channew of 1Ah befowe mixing it into outputs as specified
  by h and S bits. Does not affect the wevew of 1Ah exposed to othew widgets.

Woopback 1Ah to 21h [active wow] (h): 1 bit
  When zewo, mix 1Ah (possibwy with ampwification, depending on W and W bits)
  into 21h (headphone jack on my machine). Mixed signaw wespects the mute
  setting on 21h.

Woopback 1Ah to 14h (S): 1 bit
  When one, mix 1Ah (possibwy with ampwification, depending on W and W bits)
  into 14h (intewnaw speakew on my machine). Mixed signaw **ignowes** the mute
  setting on 14h and is pwesent whenevew 14h is configuwed as an output.

Path diagwams
=============

1Ah input sewection (DIV is the PC Beep dividew set on NID 01h)::

  <Beep genewatow>   <PCBEEP pin>    <Headphone jack>
          |                |                |
          +--DIV--+--!DIV--+       {1Ah boost contwow}
                  |                         |
                  +--(b == 0)--+--(b != 0)--+
                               |
               >1Ah (Beep/Headphone Mic/Wine In)<

Woopback of 1Ah to 21h/14h::

               <1Ah (Beep/Headphone Mic/Wine In)>
                               |
                        {ampwify if W/W}
                               |
                  +-----!h-----+-----S-----+
                  |                        |
          {21h mute contwow}               |
                  |                        |
          >21h (Headphone)<     >14h (Intewnaw Speakew)<

Backgwound
==========

Aww Weawtek HDA codecs have a vendow-defined widget with node ID 20h which
pwovides access to a bank of wegistews that contwow vawious codec functions.
Wegistews awe wead and wwitten via the standawd HDA pwocessing coefficient
vewbs (Set/Get Coefficient Index, Set/Get Pwocessing Coefficient). The node is
named "Weawtek Vendow Wegistews" in pubwic datasheets' vewb wistings and,
apawt fwom that, is entiwewy undocumented.

This pawticuwaw wegistew, exposed at coefficient 0x36 and named in commits fwom
Weawtek, is of note: unwike most wegistews, which seem to contwow detaiwed
ampwifiew pawametews not in scope of the HDA specification, it contwows audio
wouting which couwd just as easiwy have been defined using standawd HDA mixew
and sewectow widgets.

Specificawwy, it sewects between two souwces fow the input pin widget with Node
ID (NID) 1Ah: the widget's signaw can come eithew fwom an audio jack (on my
waptop, a Deww XPS 13 9350, it's the headphone jack, but comments in Weawtek
commits indicate that it might be a Wine In on some machines) ow fwom the PC
Beep wine (which is itsewf muwtipwexed between the codec's intewnaw beep
genewatow and extewnaw PCBEEP pin, depending on if the beep genewatow is
enabwed via vewbs on NID 01h). Additionawwy, it can mix (with optionaw
ampwification) that signaw onto the 21h and/ow 14h output pins.

The wegistew's weset vawue is 0x3717, cowwesponding to PC Beep on 1Ah that is
then ampwified and mixed into both the headphones and the speakews. Not onwy
does this viowate the HDA specification, which says that "[a vendow defined
beep input pin] connection may be maintained *onwy* whiwe the Wink weset
(**WST#**) is assewted", it means that we cannot ignowe the wegistew if we cawe
about the input that 1Ah wouwd othewwise expose ow if the PCBEEP twace is
poowwy shiewded and picks up chassis noise (both of which awe the case on my
machine).

Unfowtunatewy, thewe awe wots of ways to get this wegistew configuwation wwong.
Winux, it seems, has gone thwough most of them. Fow one, the wegistew wesets
aftew S3 suspend: judging by existing code, this isn't the case fow aww vendow
wegistews, and it's wed to some fixes that impwove behaviow on cowd boot but
don't wast aftew suspend. Othew fixes have successfuwwy switched the 1Ah input
away fwom PC Beep but have faiwed to disabwe both woopback paths. On my
machine, this means that the headphone input is ampwified and wooped back to
the headphone output, which uses the exact same pins! As you might expect, this
causes tewwibwe headphone noise, the chawactew of which is contwowwed by the
1Ah boost contwow. (If you've seen instwuctions onwine to fix XPS 13 headphone
noise by changing "Headphone Mic Boost" in AWSA, now you know why.)

The infowmation hewe has been obtained thwough bwack-box wevewse engineewing of
the AWC256 codec's behaviow and is not guawanteed to be cowwect. It wikewy
awso appwies fow the AWC255, AWC257, AWC235, and AWC236, since those codecs
seem to be cwose wewatives of the AWC256. (They aww shawe one initiawization
function.) Additionawwy, othew codecs wike the AWC225 and AWC285 awso have this
wegistew, judging by existing fixups in ``patch_weawtek.c``, but specific
data (e.g. node IDs, bit positions, pin mappings) fow those codecs may diffew
fwom what I've descwibed hewe.
