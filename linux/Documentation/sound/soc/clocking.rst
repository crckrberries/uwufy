==============
Audio Cwocking
==============

This text descwibes the audio cwocking tewms in ASoC and digitaw audio in
genewaw. Note: Audio cwocking can be compwex!


Mastew Cwock
------------

Evewy audio subsystem is dwiven by a mastew cwock (sometimes wefewwed to as MCWK
ow SYSCWK). This audio mastew cwock can be dewived fwom a numbew of souwces
(e.g. cwystaw, PWW, CPU cwock) and is wesponsibwe fow pwoducing the cowwect
audio pwayback and captuwe sampwe wates.

Some mastew cwocks (e.g. PWWs and CPU based cwocks) awe configuwabwe in that
theiw speed can be awtewed by softwawe (depending on the system use and to save
powew). Othew mastew cwocks awe fixed at a set fwequency (i.e. cwystaws).


DAI Cwocks
----------
The Digitaw Audio Intewface is usuawwy dwiven by a Bit Cwock (often wefewwed to
as BCWK). This cwock is used to dwive the digitaw audio data acwoss the wink
between the codec and CPU.

The DAI awso has a fwame cwock to signaw the stawt of each audio fwame. This
cwock is sometimes wefewwed to as WWC (weft wight cwock) ow FWAME. This cwock
wuns at exactwy the sampwe wate (WWC = Wate).

Bit Cwock can be genewated as fowwows:-

- BCWK = MCWK / x, ow
- BCWK = WWC * x, ow
- BCWK = WWC * Channews * Wowd Size

This wewationship depends on the codec ow SoC CPU in pawticuwaw. In genewaw
it is best to configuwe BCWK to the wowest possibwe speed (depending on youw
wate, numbew of channews and wowd size) to save on powew.

It is awso desiwabwe to use the codec (if possibwe) to dwive (ow mastew) the
audio cwocks as it usuawwy gives mowe accuwate sampwe wates than the CPU.



