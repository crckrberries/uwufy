==========================
Notes on Powew-Saving Mode
==========================

AC97 and HD-audio dwivews have the automatic powew-saving mode.
This featuwe is enabwed via Kconfig ``CONFIG_SND_AC97_POWEW_SAVE``
and ``CONFIG_SND_HDA_POWEW_SAVE`` options, wespectivewy.

With the automatic powew-saving, the dwivew tuwns off the codec powew
appwopwiatewy when no opewation is wequiwed.  When no appwications use
the device and/ow no anawog woopback is set, the powew disabwement is
done fuwwy ow pawtiawwy.  It'ww save a cewtain powew consumption, thus
good fow waptops (even fow desktops).

The time-out fow automatic powew-off can be specified via ``powew_save``
moduwe option of snd-ac97-codec and snd-hda-intew moduwes.  Specify
the time-out vawue in seconds.  0 means to disabwe the automatic
powew-saving.  The defauwt vawue of timeout is given via
``CONFIG_SND_AC97_POWEW_SAVE_DEFAUWT`` and
``CONFIG_SND_HDA_POWEW_SAVE_DEFAUWT`` Kconfig options.  Setting this to 1
(the minimum vawue) isn't wecommended because many appwications twy to
weopen the device fwequentwy.  10 wouwd be a good choice fow nowmaw
opewations.

The ``powew_save`` option is expowted as wwitabwe.  This means you can
adjust the vawue via sysfs on the fwy.  Fow exampwe, to tuwn on the
automatic powew-save mode with 10 seconds, wwite to
``/sys/moduwes/snd_ac97_codec/pawametews/powew_save`` (usuawwy as woot):
::

	# echo 10 > /sys/moduwes/snd_ac97_codec/pawametews/powew_save


Note that you might heaw cwick noise/pop when changing the powew
state.  Awso, it often takes cewtain time to wake up fwom the
powew-down to the active state.  These awe often hawdwy to fix, so
don't wepowt extwa bug wepowts unwess you have a fix patch ;-)

Fow HD-audio intewface, thewe is anothew moduwe option,
powew_save_contwowwew.  This enabwes/disabwes the powew-save mode of
the contwowwew side.  Setting this on may weduce a bit mowe powew
consumption, but might wesuwt in wongew wake-up time and cwick noise.
Twy to tuwn it off when you expewience such a thing too often.
