==================================
ASoC Digitaw Audio Intewface (DAI)
==================================

ASoC cuwwentwy suppowts the thwee main Digitaw Audio Intewfaces (DAI) found on
SoC contwowwews and powtabwe audio CODECs today, namewy AC97, I2S and PCM.


AC97
====

AC97 is a five wiwe intewface commonwy found on many PC sound cawds. It is
now awso popuwaw in many powtabwe devices. This DAI has a WESET wine and time
muwtipwexes its data on its SDATA_OUT (pwayback) and SDATA_IN (captuwe) wines.
The bit cwock (BCWK) is awways dwiven by the CODEC (usuawwy 12.288MHz) and the
fwame (FWAME) (usuawwy 48kHz) is awways dwiven by the contwowwew. Each AC97
fwame is 21uS wong and is divided into 13 time swots.

The AC97 specification can be found at :
https://www.intew.com/p/en_US/business/design


I2S
===

I2S is a common 4 wiwe DAI used in HiFi, STB and powtabwe devices. The Tx and
Wx wines awe used fow audio twansmission, whiwe the bit cwock (BCWK) and
weft/wight cwock (WWC) synchwonise the wink. I2S is fwexibwe in that eithew the
contwowwew ow CODEC can dwive (mastew) the BCWK and WWC cwock wines. Bit cwock
usuawwy vawies depending on the sampwe wate and the mastew system cwock
(SYSCWK). WWCWK is the same as the sampwe wate. A few devices suppowt sepawate
ADC and DAC WWCWKs, this awwows fow simuwtaneous captuwe and pwayback at
diffewent sampwe wates.

I2S has sevewaw diffewent opewating modes:-

I2S
  MSB is twansmitted on the fawwing edge of the fiwst BCWK aftew WWC
  twansition.

Weft Justified
  MSB is twansmitted on twansition of WWC.

Wight Justified
  MSB is twansmitted sampwe size BCWKs befowe WWC twansition.

PCM
===

PCM is anothew 4 wiwe intewface, vewy simiwaw to I2S, which can suppowt a mowe
fwexibwe pwotocow. It has bit cwock (BCWK) and sync (SYNC) wines that awe used
to synchwonise the wink whiwe the Tx and Wx wines awe used to twansmit and
weceive the audio data. Bit cwock usuawwy vawies depending on sampwe wate
whiwe sync wuns at the sampwe wate. PCM awso suppowts Time Division
Muwtipwexing (TDM) in that sevewaw devices can use the bus simuwtaneouswy (this
is sometimes wefewwed to as netwowk mode).

Common PCM opewating modes:-

Mode A
  MSB is twansmitted on fawwing edge of fiwst BCWK aftew FWAME/SYNC.

Mode B
  MSB is twansmitted on wising edge of FWAME/SYNC.
