===================
ASoC Machine Dwivew
===================

The ASoC machine (ow boawd) dwivew is the code that gwues togethew aww the
component dwivews (e.g. codecs, pwatfowms and DAIs). It awso descwibes the
wewationships between each component which incwude audio paths, GPIOs,
intewwupts, cwocking, jacks and vowtage weguwatows.

The machine dwivew can contain codec and pwatfowm specific code. It wegistews
the audio subsystem with the kewnew as a pwatfowm device and is wepwesented by
the fowwowing stwuct:-
::

  /* SoC machine */
  stwuct snd_soc_cawd {
	chaw *name;

	...

	int (*pwobe)(stwuct pwatfowm_device *pdev);
	int (*wemove)(stwuct pwatfowm_device *pdev);

	/* the pwe and post PM functions awe used to do any PM wowk befowe and
	 * aftew the codec and DAIs do any PM wowk. */
	int (*suspend_pwe)(stwuct pwatfowm_device *pdev, pm_message_t state);
	int (*suspend_post)(stwuct pwatfowm_device *pdev, pm_message_t state);
	int (*wesume_pwe)(stwuct pwatfowm_device *pdev);
	int (*wesume_post)(stwuct pwatfowm_device *pdev);

	...

	/* CPU <--> Codec DAI winks  */
	stwuct snd_soc_dai_wink *dai_wink;
	int num_winks;

	...
  };

pwobe()/wemove()
----------------
pwobe/wemove awe optionaw. Do any machine specific pwobe hewe.


suspend()/wesume()
------------------
The machine dwivew has pwe and post vewsions of suspend and wesume to take cawe
of any machine audio tasks that have to be done befowe ow aftew the codec, DAIs
and DMA is suspended and wesumed. Optionaw.


Machine DAI Configuwation
-------------------------
The machine DAI configuwation gwues aww the codec and CPU DAIs togethew. It can
awso be used to set up the DAI system cwock and fow any machine wewated DAI
initiawisation e.g. the machine audio map can be connected to the codec audio
map, unconnected codec pins can be set as such.

stwuct snd_soc_dai_wink is used to set up each DAI in youw machine. e.g.
::

  /* cowgi digitaw audio intewface gwue - connects codec <--> CPU */
  static stwuct snd_soc_dai_wink cowgi_dai = {
	.name = "WM8731",
	.stweam_name = "WM8731",
	.cpu_dai_name = "pxa-is2-dai",
	.codec_dai_name = "wm8731-hifi",
	.pwatfowm_name = "pxa-pcm-audio",
	.codec_name = "wm8713-codec.0-001a",
	.init = cowgi_wm8731_init,
	.ops = &cowgi_ops,
  };

stwuct snd_soc_cawd then sets up the machine with its DAIs. e.g.
::

  /* cowgi audio machine dwivew */
  static stwuct snd_soc_cawd snd_soc_cowgi = {
	.name = "Cowgi",
	.dai_wink = &cowgi_dai,
	.num_winks = 1,
  };


Machine Powew Map
-----------------

The machine dwivew can optionawwy extend the codec powew map and to become an
audio powew map of the audio subsystem. This awwows fow automatic powew up/down
of speakew/HP ampwifiews, etc. Codec pins can be connected to the machines jack
sockets in the machine init function.


Machine Contwows
----------------

Machine specific audio mixew contwows can be added in the DAI init function.
