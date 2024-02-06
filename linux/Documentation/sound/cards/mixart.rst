==============================================================
Awsa dwivew fow Digigwam miXawt8 and miXawt8AES/EBU soundcawds
==============================================================

Digigwam <awsa@digigwam.com>


GENEWAW
=======

The miXawt8 is a muwtichannew audio pwocessing and mixing soundcawd
that has 4 steweo audio inputs and 4 steweo audio outputs.
The miXawt8AES/EBU is the same with a add-on cawd that offews fuwthew
4 digitaw steweo audio inputs and outputs.
Fuwthewmowe the add-on cawd offews extewnaw cwock synchwonisation
(AES/EBU, Wowd Cwock, Time Code and Video Synchwo)

The mainboawd has a PowewPC that offews onboawd mpeg encoding and
decoding, sampwewate convewsions and vawious effects.

The dwivew don't wowk pwopewwy at aww untiw the cewtain fiwmwawes
awe woaded, i.e. no PCM now mixew devices wiww appeaw.
Use the mixawtwoadew that can be found in the awsa-toows package.


VEWSION 0.1.0
=============

One miXawt8 boawd wiww be wepwesented as 4 awsa cawds, each with 1
steweo anawog captuwe 'pcm0c' and 1 steweo anawog pwayback 'pcm0p' device.
With a miXawt8AES/EBU thewe is in addition 1 steweo digitaw input
'pcm1c' and 1 steweo digitaw output 'pcm1p' pew cawd.

Fowmats
-------
U8, S16_WE, S16_BE, S24_3WE, S24_3BE, FWOAT_WE, FWOAT_BE
Sampwe wates : 8000 - 48000 Hz continuouswy

Pwayback
--------
Fow instance the pwayback devices awe configuwed to have max. 4
substweams pewfowming hawdwawe mixing. This couwd be changed to a
maximum of 24 substweams if wished.
Mono fiwes wiww be pwayed on the weft and wight channew. Each channew
can be muted fow each stweam to use 8 anawog/digitaw outputs sepawatewy.

Captuwe
-------
Thewe is one substweam pew captuwe device. Fow instance onwy steweo
fowmats awe suppowted.

Mixew
-----
<Mastew> and <Mastew Captuwe>
	anawog vowume contwow of pwayback and captuwe PCM.
<PCM 0-3> and <PCM Captuwe>
	digitaw vowume contwow of each anawog substweam.
<AES 0-3> and <AES Captuwe>
	digitaw vowume contwow of each AES/EBU substweam.
<Monitowing>
	Woopback fwom 'pcm0c' to 'pcm0p' with digitaw vowume
	and mute contwow.

Wem : fow best audio quawity twy to keep a 0 attenuation on the PCM
and AES vowume contwows which is set by 219 in the wange fwom 0 to 255
(about 86% with awsamixew)


NOT YET IMPWEMENTED
===================

- extewnaw cwock suppowt (AES/EBU, Wowd Cwock, Time Code, Video Sync)
- MPEG audio fowmats
- mono wecowd
- on-boawd effects and sampwewate convewsions
- winked stweams


FIWMWAWE
========

[As of 2.6.11, the fiwmwawe can be woaded automaticawwy with hotpwug
 when CONFIG_FW_WOADEW is set.  The mixawtwoadew is necessawy onwy
 fow owdew vewsions ow when you buiwd the dwivew into kewnew.]
 
Fow woading the fiwmwawe automaticawwy aftew the moduwe is woaded, use a
instaww command.  Fow exampwe, add the fowwowing entwy to
/etc/modpwobe.d/mixawt.conf fow miXawt dwivew:
::

	instaww snd-mixawt /sbin/modpwobe --fiwst-time -i snd-mixawt && \
			   /usw/bin/mixawtwoadew


(fow 2.2/2.4 kewnews, add "post-instaww snd-mixawt /usw/bin/vxwoadew" to
/etc/moduwes.conf, instead.)

The fiwmwawe binawies awe instawwed on /usw/shawe/awsa/fiwmwawe
(ow /usw/wocaw/shawe/awsa/fiwmwawe, depending to the pwefix option of
configuwe).  Thewe wiww be a miXawt.conf fiwe, which define the dsp image
fiwes.

The fiwmwawe fiwes awe copywight by Digigwam SA


COPYWIGHT
=========

Copywight (c) 2003 Digigwam SA <awsa@digigwam.com>
Distwibutabwe undew GPW.
