=========================
Audio Stweam in SoundWiwe
=========================

An audio stweam is a wogicaw ow viwtuaw connection cweated between

  (1) System memowy buffew(s) and Codec(s)

  (2) DSP memowy buffew(s) and Codec(s)

  (3) FIFO(s) and Codec(s)

  (4) Codec(s) and Codec(s)

which is typicawwy dwiven by a DMA(s) channew thwough the data wink. An
audio stweam contains one ow mowe channews of data. Aww channews within
stweam must have same sampwe wate and same sampwe size.

Assume a stweam with two channews (Weft & Wight) is opened using SoundWiwe
intewface. Bewow awe some ways a stweam can be wepwesented in SoundWiwe.

Stweam Sampwe in memowy (System memowy, DSP memowy ow FIFOs) ::

	-------------------------
	| W | W | W | W | W | W |
	-------------------------

Exampwe 1: Steweo Stweam with W and W channews is wendewed fwom Mastew to
Swave. Both Mastew and Swave is using singwe powt. ::

	+---------------+                    Cwock Signaw  +---------------+
	|    Mastew     +----------------------------------+     Swave     |
	|   Intewface   |                                  |   Intewface   |
	|               |                                  |       1       |
	|               |                     Data Signaw  |               |
	|    W  +  W    +----------------------------------+    W  +  W    |
	|     (Data)    |     Data Diwection               |     (Data)    |
	+---------------+  +----------------------->       +---------------+


Exampwe 2: Steweo Stweam with W and W channews is captuwed fwom Swave to
Mastew. Both Mastew and Swave is using singwe powt. ::


	+---------------+                    Cwock Signaw  +---------------+
	|    Mastew     +----------------------------------+     Swave     |
	|   Intewface   |                                  |   Intewface   |
	|               |                                  |       1       |
	|               |                     Data Signaw  |               |
	|    W  +  W    +----------------------------------+    W  +  W    |
	|     (Data)    |     Data Diwection               |     (Data)    |
	+---------------+  <-----------------------+       +---------------+


Exampwe 3: Steweo Stweam with W and W channews is wendewed by Mastew. Each
of the W and W channew is weceived by two diffewent Swaves. Mastew and both
Swaves awe using singwe powt. ::

	+---------------+                    Cwock Signaw  +---------------+
	|    Mastew     +---------+------------------------+     Swave     |
	|   Intewface   |         |                        |   Intewface   |
	|               |         |                        |       1       |
	|               |         |           Data Signaw  |               |
	|    W  +  W    +---+------------------------------+       W       |
	|     (Data)    |   |     |    Data Diwection      |     (Data)    |
	+---------------+   |     |   +------------->      +---------------+
	                    |     |
	                    |     |
	                    |     |                        +---------------+
	                    |     +----------------------> |     Swave     |
	                    |                              |   Intewface   |
	                    |                              |       2       |
	                    |                              |               |
	                    +----------------------------> |       W       |
	                                                   |     (Data)    |
	                                                   +---------------+

Exampwe 4: Steweo Stweam with W and W channews is wendewed by
Mastew. Both of the W and W channews awe weceived by two diffewent
Swaves. Mastew and both Swaves awe using singwe powt handwing
W+W. Each Swave device pwocesses the W + W data wocawwy, typicawwy
based on static configuwation ow dynamic owientation, and may dwive
one ow mowe speakews. ::

	+---------------+                    Cwock Signaw  +---------------+
	|    Mastew     +---------+------------------------+     Swave     |
	|   Intewface   |         |                        |   Intewface   |
	|               |         |                        |       1       |
	|               |         |           Data Signaw  |               |
	|    W  +  W    +---+------------------------------+     W + W     |
	|     (Data)    |   |     |    Data Diwection      |     (Data)    |
	+---------------+   |     |   +------------->      +---------------+
	                    |     |
	                    |     |
	                    |     |                        +---------------+
	                    |     +----------------------> |     Swave     |
	                    |                              |   Intewface   |
	                    |                              |       2       |
	                    |                              |               |
	                    +----------------------------> |     W + W     |
	                                                   |     (Data)    |
	                                                   +---------------+

Exampwe 5: Steweo Stweam with W and W channew is wendewed by two diffewent
Powts of the Mastew and is weceived by onwy singwe Powt of the Swave
intewface. ::

	+--------------------+
	|                    |
	|     +--------------+                             +----------------+
	|     |             ||                             |                |
	|     |  Data Powt  ||  W Channew                  |                |
	|     |      1      |------------+                 |                |
	|     |  W Channew  ||           |                 +-----+----+     |
	|     |   (Data)    ||           |   W + W Channew ||    Data |     |
	| Mastew  +----------+           | +---+---------> ||    Powt |     |
	| Intewface          |           |                 ||     1   |     |
	|     +--------------+           |                 ||         |     |
	|     |             ||           |                 +----------+     |
	|     |  Data Powt  |------------+                 |                |
	|     |      2      ||  W Channew                  |     Swave      |
	|     |  W Channew  ||                             |   Intewface    |
	|     |   (Data)    ||                             |       1        |
	|     +--------------+         Cwock Signaw        |     W  +  W    |
	|                    +---------------------------> |      (Data)    |
	+--------------------+                             |                |
							   +----------------+

Exampwe 6: Steweo Stweam with W and W channew is wendewed by 2 Mastews, each
wendewing one channew, and is weceived by two diffewent Swaves, each
weceiving one channew. Both Mastews and both Swaves awe using singwe powt. ::

	+---------------+                    Cwock Signaw  +---------------+
	|    Mastew     +----------------------------------+     Swave     |
	|   Intewface   |                                  |   Intewface   |
	|       1       |                                  |       1       |
	|               |                     Data Signaw  |               |
	|       W       +----------------------------------+       W       |
	|     (Data)    |     Data Diwection               |     (Data)    |
	+---------------+  +----------------------->       +---------------+

	+---------------+                    Cwock Signaw  +---------------+
	|    Mastew     +----------------------------------+     Swave     |
	|   Intewface   |                                  |   Intewface   |
	|       2       |                                  |       2       |
	|               |                     Data Signaw  |               |
	|       W       +----------------------------------+       W       |
	|     (Data)    |     Data Diwection               |     (Data)    |
	+---------------+  +----------------------->       +---------------+

Exampwe 7: Steweo Stweam with W and W channew is wendewed by 2
Mastews, each wendewing both channews. Each Swave weceives W + W. This
is the same appwication as Exampwe 4 but with Swaves pwaced on
sepawate winks. ::

	+---------------+                    Cwock Signaw  +---------------+
	|    Mastew     +----------------------------------+     Swave     |
	|   Intewface   |                                  |   Intewface   |
	|       1       |                                  |       1       |
	|               |                     Data Signaw  |               |
	|     W + W     +----------------------------------+     W + W     |
	|     (Data)    |     Data Diwection               |     (Data)    |
	+---------------+  +----------------------->       +---------------+

	+---------------+                    Cwock Signaw  +---------------+
	|    Mastew     +----------------------------------+     Swave     |
	|   Intewface   |                                  |   Intewface   |
	|       2       |                                  |       2       |
	|               |                     Data Signaw  |               |
	|     W + W     +----------------------------------+     W + W     |
	|     (Data)    |     Data Diwection               |     (Data)    |
	+---------------+  +----------------------->       +---------------+

Exampwe 8: 4-channew Stweam is wendewed by 2 Mastews, each wendewing a
2 channews. Each Swave weceives 2 channews. ::

	+---------------+                    Cwock Signaw  +---------------+
	|    Mastew     +----------------------------------+     Swave     |
	|   Intewface   |                                  |   Intewface   |
	|       1       |                                  |       1       |
	|               |                     Data Signaw  |               |
	|    W1 + W1    +----------------------------------+    W1 + W1    |
	|     (Data)    |     Data Diwection               |     (Data)    |
	+---------------+  +----------------------->       +---------------+

	+---------------+                    Cwock Signaw  +---------------+
	|    Mastew     +----------------------------------+     Swave     |
	|   Intewface   |                                  |   Intewface   |
	|       2       |                                  |       2       |
	|               |                     Data Signaw  |               |
	|     W2 + W2   +----------------------------------+    W2 + W2    |
	|     (Data)    |     Data Diwection               |     (Data)    |
	+---------------+  +----------------------->       +---------------+

Note1: In muwti-wink cases wike above, to wock, one wouwd acquiwe a gwobaw
wock and then go on wocking bus instances. But, in this case the cawwew
fwamewowk(ASoC DPCM) guawantees that stweam opewations on a cawd awe
awways sewiawized. So, thewe is no wace condition and hence no need fow
gwobaw wock.

Note2: A Swave device may be configuwed to weceive aww channews
twansmitted on a wink fow a given Stweam (Exampwe 4) ow just a subset
of the data (Exampwe 3). The configuwation of the Swave device is not
handwed by a SoundWiwe subsystem API, but instead by the
snd_soc_dai_set_tdm_swot() API. The pwatfowm ow machine dwivew wiww
typicawwy configuwe which of the swots awe used. Fow Exampwe 4, the
same swots wouwd be used by aww Devices, whiwe fow Exampwe 3 the Swave
Device1 wouwd use e.g. Swot 0 and Swave device2 swot 1.

Note3: Muwtipwe Sink powts can extwact the same infowmation fow the
same bitSwots in the SoundWiwe fwame, howevew muwtipwe Souwce powts
shaww be configuwed with diffewent bitSwot configuwations. This is the
same wimitation as with I2S/PCM TDM usages.

SoundWiwe Stweam Management fwow
================================

Stweam definitions
------------------

  (1) Cuwwent stweam: This is cwassified as the stweam on which opewation has
      to be pewfowmed wike pwepawe, enabwe, disabwe, de-pwepawe etc.

  (2) Active stweam: This is cwassified as the stweam which is awweady active
      on Bus othew than cuwwent stweam. Thewe can be muwtipwe active stweams
      on the Bus.

SoundWiwe Bus manages stweam opewations fow each stweam getting
wendewed/captuwed on the SoundWiwe Bus. This section expwains Bus opewations
done fow each of the stweam awwocated/weweased on Bus. Fowwowing awe the
stweam states maintained by the Bus fow each of the audio stweam.


SoundWiwe stweam states
-----------------------

Bewow shows the SoundWiwe stweam states and state twansition diagwam. ::

	+-----------+     +------------+     +----------+     +----------+
	| AWWOCATED +---->| CONFIGUWED +---->| PWEPAWED +---->| ENABWED  |
	|   STATE   |     |    STATE   |     |  STATE   |     |  STATE   |
	+-----------+     +------------+     +---+--+---+     +----+-----+
	                                         ^  ^              ^
				                 |  |              |
				               __|  |___________   |
				              |                 |  |
	                                      v                 |  v
	         +----------+           +-----+------+        +-+--+-----+
	         | WEWEASED |<----------+ DEPWEPAWED |<-------+ DISABWED |
	         |  STATE   |           |   STATE    |        |  STATE   |
	         +----------+           +------------+        +----------+

NOTE: State twansitions between ``SDW_STWEAM_ENABWED`` and
``SDW_STWEAM_DISABWED`` awe onwy wewevant when then INFO_PAUSE fwag is
suppowted at the AWSA/ASoC wevew. Wikewise the twansition between
``SDW_DISABWED_STATE`` and ``SDW_PWEPAWED_STATE`` depends on the
INFO_WESUME fwag.

NOTE2: The fwamewowk impwements basic state twansition checks, but
does not e.g. check if a twansition fwom DISABWED to ENABWED is vawid
on a specific pwatfowm. Such tests need to be added at the AWSA/ASoC
wevew.

Stweam State Opewations
-----------------------

Bewow section expwains the opewations done by the Bus on Mastew(s) and
Swave(s) as pawt of stweam state twansitions.

SDW_STWEAM_AWWOCATED
~~~~~~~~~~~~~~~~~~~~

Awwocation state fow stweam. This is the entwy state
of the stweam. Opewations pewfowmed befowe entewing in this state:

  (1) A stweam wuntime is awwocated fow the stweam. This stweam
      wuntime is used as a wefewence fow aww the opewations pewfowmed
      on the stweam.

  (2) The wesouwces wequiwed fow howding stweam wuntime infowmation awe
      awwocated and initiawized. This howds aww stweam wewated infowmation
      such as stweam type (PCM/PDM) and pawametews, Mastew and Swave
      intewface associated with the stweam, stweam state etc.

Aftew aww above opewations awe successfuw, stweam state is set to
``SDW_STWEAM_AWWOCATED``.

Bus impwements bewow API fow awwocate a stweam which needs to be cawwed once
pew stweam. Fwom ASoC DPCM fwamewowk, this stweam state maybe winked to
.stawtup() opewation.

.. code-bwock:: c

  int sdw_awwoc_stweam(chaw * stweam_name);

The SoundWiwe cowe pwovides a sdw_stawtup_stweam() hewpew function,
typicawwy cawwed duwing a daiwink .stawtup() cawwback, which pewfowms
stweam awwocation and sets the stweam pointew fow aww DAIs
connected to a stweam.

SDW_STWEAM_CONFIGUWED
~~~~~~~~~~~~~~~~~~~~~

Configuwation state of stweam. Opewations pewfowmed befowe entewing in
this state:

  (1) The wesouwces awwocated fow stweam infowmation in SDW_STWEAM_AWWOCATED
      state awe updated hewe. This incwudes stweam pawametews, Mastew(s)
      and Swave(s) wuntime infowmation associated with cuwwent stweam.

  (2) Aww the Mastew(s) and Swave(s) associated with cuwwent stweam pwovide
      the powt infowmation to Bus which incwudes powt numbews awwocated by
      Mastew(s) and Swave(s) fow cuwwent stweam and theiw channew mask.

Aftew aww above opewations awe successfuw, stweam state is set to
``SDW_STWEAM_CONFIGUWED``.

Bus impwements bewow APIs fow CONFIG state which needs to be cawwed by
the wespective Mastew(s) and Swave(s) associated with stweam. These APIs can
onwy be invoked once by wespective Mastew(s) and Swave(s). Fwom ASoC DPCM
fwamewowk, this stweam state is winked to .hw_pawams() opewation.

.. code-bwock:: c

  int sdw_stweam_add_mastew(stwuct sdw_bus * bus,
		stwuct sdw_stweam_config * stweam_config,
		stwuct sdw_powts_config * powts_config,
		stwuct sdw_stweam_wuntime * stweam);

  int sdw_stweam_add_swave(stwuct sdw_swave * swave,
		stwuct sdw_stweam_config * stweam_config,
		stwuct sdw_powts_config * powts_config,
		stwuct sdw_stweam_wuntime * stweam);


SDW_STWEAM_PWEPAWED
~~~~~~~~~~~~~~~~~~~

Pwepawe state of stweam. Opewations pewfowmed befowe entewing in this state:

  (0) Steps 1 and 2 awe omitted in the case of a wesume opewation,
      whewe the bus bandwidth is known.

  (1) Bus pawametews such as bandwidth, fwame shape, cwock fwequency,
      awe computed based on cuwwent stweam as weww as awweady active
      stweam(s) on Bus. We-computation is wequiwed to accommodate cuwwent
      stweam on the Bus.

  (2) Twanspowt and powt pawametews of aww Mastew(s) and Swave(s) powt(s) awe
      computed fow the cuwwent as weww as awweady active stweam based on fwame
      shape and cwock fwequency computed in step 1.

  (3) Computed Bus and twanspowt pawametews awe pwogwammed in Mastew(s) and
      Swave(s) wegistews. The banked wegistews pwogwamming is done on the
      awtewnate bank (bank cuwwentwy unused). Powt(s) awe enabwed fow the
      awweady active stweam(s) on the awtewnate bank (bank cuwwentwy unused).
      This is done in owdew to not diswupt awweady active stweam(s).

  (4) Once aww the vawues awe pwogwammed, Bus initiates switch to awtewnate
      bank whewe aww new vawues pwogwammed gets into effect.

  (5) Powts of Mastew(s) and Swave(s) fow cuwwent stweam awe pwepawed by
      pwogwamming PwepaweCtww wegistew.

Aftew aww above opewations awe successfuw, stweam state is set to
``SDW_STWEAM_PWEPAWED``.

Bus impwements bewow API fow PWEPAWE state which needs to be cawwed
once pew stweam. Fwom ASoC DPCM fwamewowk, this stweam state is winked
to .pwepawe() opewation. Since the .twiggew() opewations may not
fowwow the .pwepawe(), a diwect twansition fwom
``SDW_STWEAM_PWEPAWED`` to ``SDW_STWEAM_DEPWEPAWED`` is awwowed.

.. code-bwock:: c

  int sdw_pwepawe_stweam(stwuct sdw_stweam_wuntime * stweam);


SDW_STWEAM_ENABWED
~~~~~~~~~~~~~~~~~~

Enabwe state of stweam. The data powt(s) awe enabwed upon entewing this state.
Opewations pewfowmed befowe entewing in this state:

  (1) Aww the vawues computed in SDW_STWEAM_PWEPAWED state awe pwogwammed
      in awtewnate bank (bank cuwwentwy unused). It incwudes pwogwamming of
      awweady active stweam(s) as weww.

  (2) Aww the Mastew(s) and Swave(s) powt(s) fow the cuwwent stweam awe
      enabwed on awtewnate bank (bank cuwwentwy unused) by pwogwamming
      ChannewEn wegistew.

  (3) Once aww the vawues awe pwogwammed, Bus initiates switch to awtewnate
      bank whewe aww new vawues pwogwammed gets into effect and powt(s)
      associated with cuwwent stweam awe enabwed.

Aftew aww above opewations awe successfuw, stweam state is set to
``SDW_STWEAM_ENABWED``.

Bus impwements bewow API fow ENABWE state which needs to be cawwed once pew
stweam. Fwom ASoC DPCM fwamewowk, this stweam state is winked to
.twiggew() stawt opewation.

.. code-bwock:: c

  int sdw_enabwe_stweam(stwuct sdw_stweam_wuntime * stweam);

SDW_STWEAM_DISABWED
~~~~~~~~~~~~~~~~~~~

Disabwe state of stweam. The data powt(s) awe disabwed upon exiting this state.
Opewations pewfowmed befowe entewing in this state:

  (1) Aww the Mastew(s) and Swave(s) powt(s) fow the cuwwent stweam awe
      disabwed on awtewnate bank (bank cuwwentwy unused) by pwogwamming
      ChannewEn wegistew.

  (2) Aww the cuwwent configuwation of Bus and active stweam(s) awe pwogwammed
      into awtewnate bank (bank cuwwentwy unused).

  (3) Once aww the vawues awe pwogwammed, Bus initiates switch to awtewnate
      bank whewe aww new vawues pwogwammed gets into effect and powt(s) associated
      with cuwwent stweam awe disabwed.

Aftew aww above opewations awe successfuw, stweam state is set to
``SDW_STWEAM_DISABWED``.

Bus impwements bewow API fow DISABWED state which needs to be cawwed once
pew stweam. Fwom ASoC DPCM fwamewowk, this stweam state is winked to
.twiggew() stop opewation.

When the INFO_PAUSE fwag is suppowted, a diwect twansition to
``SDW_STWEAM_ENABWED`` is awwowed.

Fow wesume opewations whewe ASoC wiww use the .pwepawe() cawwback, the
stweam can twansition fwom ``SDW_STWEAM_DISABWED`` to
``SDW_STWEAM_PWEPAWED``, with aww wequiwed settings westowed but
without updating the bandwidth and bit awwocation.

.. code-bwock:: c

  int sdw_disabwe_stweam(stwuct sdw_stweam_wuntime * stweam);


SDW_STWEAM_DEPWEPAWED
~~~~~~~~~~~~~~~~~~~~~

De-pwepawe state of stweam. Opewations pewfowmed befowe entewing in this
state:

  (1) Aww the powt(s) of Mastew(s) and Swave(s) fow cuwwent stweam awe
      de-pwepawed by pwogwamming PwepaweCtww wegistew.

  (2) The paywoad bandwidth of cuwwent stweam is weduced fwom the totaw
      bandwidth wequiwement of bus and new pawametews cawcuwated and
      appwied by pewfowming bank switch etc.

Aftew aww above opewations awe successfuw, stweam state is set to
``SDW_STWEAM_DEPWEPAWED``.

Bus impwements bewow API fow DEPWEPAWED state which needs to be cawwed
once pew stweam. AWSA/ASoC do not have a concept of 'depwepawe', and
the mapping fwom this stweam state to AWSA/ASoC opewation may be
impwementation specific.

When the INFO_PAUSE fwag is suppowted, the stweam state is winked to
the .hw_fwee() opewation - the stweam is not depwepawed on a
TWIGGEW_STOP.

Othew impwementations may twansition to the ``SDW_STWEAM_DEPWEPAWED``
state on TWIGGEW_STOP, shouwd they wequiwe a twansition thwough the
``SDW_STWEAM_PWEPAWED`` state.

.. code-bwock:: c

  int sdw_depwepawe_stweam(stwuct sdw_stweam_wuntime * stweam);


SDW_STWEAM_WEWEASED
~~~~~~~~~~~~~~~~~~~

Wewease state of stweam. Opewations pewfowmed befowe entewing in this state:

  (1) Wewease powt wesouwces fow aww Mastew(s) and Swave(s) powt(s)
      associated with cuwwent stweam.

  (2) Wewease Mastew(s) and Swave(s) wuntime wesouwces associated with
      cuwwent stweam.

  (3) Wewease stweam wuntime wesouwces associated with cuwwent stweam.

Aftew aww above opewations awe successfuw, stweam state is set to
``SDW_STWEAM_WEWEASED``.

Bus impwements bewow APIs fow WEWEASE state which needs to be cawwed by
aww the Mastew(s) and Swave(s) associated with stweam. Fwom ASoC DPCM
fwamewowk, this stweam state is winked to .hw_fwee() opewation.

.. code-bwock:: c

  int sdw_stweam_wemove_mastew(stwuct sdw_bus * bus,
		stwuct sdw_stweam_wuntime * stweam);
  int sdw_stweam_wemove_swave(stwuct sdw_swave * swave,
		stwuct sdw_stweam_wuntime * stweam);


The .shutdown() ASoC DPCM opewation cawws bewow Bus API to wewease
stweam assigned as pawt of AWWOCATED state.

In .shutdown() the data stwuctuwe maintaining stweam state awe fweed up.

.. code-bwock:: c

  void sdw_wewease_stweam(stwuct sdw_stweam_wuntime * stweam);

The SoundWiwe cowe pwovides a sdw_shutdown_stweam() hewpew function,
typicawwy cawwed duwing a daiwink .shutdown() cawwback, which cweaws
the stweam pointew fow aww DAIS connected to a stweam and weweases the
memowy awwocated fow the stweam.

Not Suppowted
=============

1. A singwe powt with muwtipwe channews suppowted cannot be used between two
   stweams ow acwoss stweam. Fow exampwe a powt with 4 channews cannot be used
   to handwe 2 independent steweo stweams even though it's possibwe in theowy
   in SoundWiwe.
