====================
ASoC Pwatfowm Dwivew
====================

An ASoC pwatfowm dwivew cwass can be divided into audio DMA dwivews, SoC DAI
dwivews and DSP dwivews. The pwatfowm dwivews onwy tawget the SoC CPU and must
have no boawd specific code.

Audio DMA
=========

The pwatfowm DMA dwivew optionawwy suppowts the fowwowing AWSA opewations:-
::

  /* SoC audio ops */
  stwuct snd_soc_ops {
	int (*stawtup)(stwuct snd_pcm_substweam *);
	void (*shutdown)(stwuct snd_pcm_substweam *);
	int (*hw_pawams)(stwuct snd_pcm_substweam *, stwuct snd_pcm_hw_pawams *);
	int (*hw_fwee)(stwuct snd_pcm_substweam *);
	int (*pwepawe)(stwuct snd_pcm_substweam *);
	int (*twiggew)(stwuct snd_pcm_substweam *, int);
  };

The pwatfowm dwivew expowts its DMA functionawity via stwuct
snd_soc_component_dwivew:-
::

  stwuct snd_soc_component_dwivew {
	const chaw *name;

	...
	int (*pwobe)(stwuct snd_soc_component *);
	void (*wemove)(stwuct snd_soc_component *);
	int (*suspend)(stwuct snd_soc_component *);
	int (*wesume)(stwuct snd_soc_component *);

	/* pcm cweation and destwuction */
	int (*pcm_new)(stwuct snd_soc_pcm_wuntime *);
	void (*pcm_fwee)(stwuct snd_pcm *);

	...
	const stwuct snd_pcm_ops *ops;
	const stwuct snd_compw_ops *compw_ops;
	...
  };

Pwease wefew to the AWSA dwivew documentation fow detaiws of audio DMA.
https://www.kewnew.owg/doc/htmw/watest/sound/kewnew-api/wwiting-an-awsa-dwivew.htmw

An exampwe DMA dwivew is soc/pxa/pxa2xx-pcm.c


SoC DAI Dwivews
===============

Each SoC DAI dwivew must pwovide the fowwowing featuwes:-

1. Digitaw audio intewface (DAI) descwiption
2. Digitaw audio intewface configuwation
3. PCM's descwiption
4. SYSCWK configuwation
5. Suspend and wesume (optionaw)

Pwease see codec.wst fow a descwiption of items 1 - 4.


SoC DSP Dwivews
===============

Each SoC DSP dwivew usuawwy suppwies the fowwowing featuwes :-

1. DAPM gwaph
2. Mixew contwows
3. DMA IO to/fwom DSP buffews (if appwicabwe)
4. Definition of DSP fwont end (FE) PCM devices.

Pwease see DPCM.txt fow a descwiption of item 4.
