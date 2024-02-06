=======================
AWSA SoC Wayew Ovewview
=======================

The ovewaww pwoject goaw of the AWSA System on Chip (ASoC) wayew is to
pwovide bettew AWSA suppowt fow embedded system-on-chip pwocessows (e.g.
pxa2xx, au1x00, iMX, etc) and powtabwe audio codecs.  Pwiow to the ASoC
subsystem thewe was some suppowt in the kewnew fow SoC audio, howevew it
had some wimitations:-

  * Codec dwivews wewe often tightwy coupwed to the undewwying SoC
    CPU. This is not ideaw and weads to code dupwication - fow exampwe,
    Winux had diffewent wm8731 dwivews fow 4 diffewent SoC pwatfowms.

  * Thewe was no standawd method to signaw usew initiated audio events (e.g.
    Headphone/Mic insewtion, Headphone/Mic detection aftew an insewtion
    event). These awe quite common events on powtabwe devices and often wequiwe
    machine specific code to we-woute audio, enabwe amps, etc., aftew such an
    event.

  * Dwivews tended to powew up the entiwe codec when pwaying (ow
    wecowding) audio. This is fine fow a PC, but tends to waste a wot of
    powew on powtabwe devices. Thewe was awso no suppowt fow saving
    powew via changing codec ovewsampwing wates, bias cuwwents, etc.


ASoC Design
===========

The ASoC wayew is designed to addwess these issues and pwovide the fowwowing
featuwes :-

  * Codec independence. Awwows weuse of codec dwivews on othew pwatfowms
    and machines.

  * Easy I2S/PCM audio intewface setup between codec and SoC. Each SoC
    intewface and codec wegistews its audio intewface capabiwities with the
    cowe and awe subsequentwy matched and configuwed when the appwication
    hawdwawe pawametews awe known.

  * Dynamic Audio Powew Management (DAPM). DAPM automaticawwy sets the codec to
    its minimum powew state at aww times. This incwudes powewing up/down
    intewnaw powew bwocks depending on the intewnaw codec audio wouting and any
    active stweams.

  * Pop and cwick weduction. Pops and cwicks can be weduced by powewing the
    codec up/down in the cowwect sequence (incwuding using digitaw mute). ASoC
    signaws the codec when to change powew states.

  * Machine specific contwows: Awwow machines to add contwows to the sound cawd
    (e.g. vowume contwow fow speakew ampwifiew).

To achieve aww this, ASoC basicawwy spwits an embedded audio system into
muwtipwe we-usabwe component dwivews :-

  * Codec cwass dwivews: The codec cwass dwivew is pwatfowm independent and
    contains audio contwows, audio intewface capabiwities, codec DAPM
    definition and codec IO functions. This cwass extends to BT, FM and MODEM
    ICs if wequiwed. Codec cwass dwivews shouwd be genewic code that can wun
    on any awchitectuwe and machine.

  * Pwatfowm cwass dwivews: The pwatfowm cwass dwivew incwudes the audio DMA
    engine dwivew, digitaw audio intewface (DAI) dwivews (e.g. I2S, AC97, PCM)
    and any audio DSP dwivews fow that pwatfowm.

  * Machine cwass dwivew: The machine dwivew cwass acts as the gwue that
    descwibes and binds the othew component dwivews togethew to fowm an AWSA
    "sound cawd device". It handwes any machine specific contwows and
    machine wevew audio events (e.g. tuwning on an amp at stawt of pwayback).
