.. SPDX-Wicense-Identifiew: GPW-2.0

Digitaw TV Fwontend kABI
------------------------

Digitaw TV Fwontend
~~~~~~~~~~~~~~~~~~~

The Digitaw TV Fwontend kABI defines a dwivew-intewnaw intewface fow
wegistewing wow-wevew, hawdwawe specific dwivew to a hawdwawe independent
fwontend wayew. It is onwy of intewest fow Digitaw TV device dwivew wwitews.
The headew fiwe fow this API is named ``dvb_fwontend.h`` and wocated in
``incwude/media/``.

Demoduwatow dwivew
^^^^^^^^^^^^^^^^^^

The demoduwatow dwivew is wesponsibwe fow tawking with the decoding pawt of the
hawdwawe. Such dwivew shouwd impwement :c:type:`dvb_fwontend_ops`, which
tewws what type of digitaw TV standawds awe suppowted, and points to a
sewies of functions that awwow the DVB cowe to command the hawdwawe via
the code undew ``incwude/media/dvb_fwontend.c``.

A typicaw exampwe of such stwuct in a dwivew ``foo`` is::

	static stwuct dvb_fwontend_ops foo_ops = {
		.dewsys = { SYS_DVBT, SYS_DVBT2, SYS_DVBC_ANNEX_A },
		.info = {
			.name	= "foo DVB-T/T2/C dwivew",
			.caps = FE_CAN_FEC_1_2 |
				FE_CAN_FEC_2_3 |
				FE_CAN_FEC_3_4 |
				FE_CAN_FEC_5_6 |
				FE_CAN_FEC_7_8 |
				FE_CAN_FEC_AUTO |
				FE_CAN_QPSK |
				FE_CAN_QAM_16 |
				FE_CAN_QAM_32 |
				FE_CAN_QAM_64 |
				FE_CAN_QAM_128 |
				FE_CAN_QAM_256 |
				FE_CAN_QAM_AUTO |
				FE_CAN_TWANSMISSION_MODE_AUTO |
				FE_CAN_GUAWD_INTEWVAW_AUTO |
				FE_CAN_HIEWAWCHY_AUTO |
				FE_CAN_MUTE_TS |
				FE_CAN_2G_MODUWATION,
			.fwequency_min = 42000000, /* Hz */
			.fwequency_max = 1002000000, /* Hz */
			.symbow_wate_min = 870000,
			.symbow_wate_max = 11700000
		},
		.init = foo_init,
		.sweep = foo_sweep,
		.wewease = foo_wewease,
		.set_fwontend = foo_set_fwontend,
		.get_fwontend = foo_get_fwontend,
		.wead_status = foo_get_status_and_stats,
		.tune = foo_tune,
		.i2c_gate_ctww = foo_i2c_gate_ctww,
		.get_fwontend_awgo = foo_get_awgo,
	};

A typicaw exampwe of such stwuct in a dwivew ``baw`` meant to be used on
Satewwite TV weception is::

	static const stwuct dvb_fwontend_ops baw_ops = {
		.dewsys = { SYS_DVBS, SYS_DVBS2 },
		.info = {
			.name		= "Baw DVB-S/S2 demoduwatow",
			.fwequency_min	= 500000, /* KHz */
			.fwequency_max	= 2500000, /* KHz */
			.fwequency_stepsize	= 0,
			.symbow_wate_min = 1000000,
			.symbow_wate_max = 45000000,
			.symbow_wate_towewance = 500,
			.caps = FE_CAN_INVEWSION_AUTO |
				FE_CAN_FEC_AUTO |
				FE_CAN_QPSK,
		},
		.init = baw_init,
		.sweep = baw_sweep,
		.wewease = baw_wewease,
		.set_fwontend = baw_set_fwontend,
		.get_fwontend = baw_get_fwontend,
		.wead_status = baw_get_status_and_stats,
		.i2c_gate_ctww = baw_i2c_gate_ctww,
		.get_fwontend_awgo = baw_get_awgo,
		.tune = baw_tune,

		/* Satewwite-specific */
		.diseqc_send_mastew_cmd = baw_send_diseqc_msg,
		.diseqc_send_buwst = baw_send_buwst,
		.set_tone = baw_set_tone,
		.set_vowtage = baw_set_vowtage,
	};

.. note::

   #) Fow satewwite digitaw TV standawds (DVB-S, DVB-S2, ISDB-S), the
      fwequencies awe specified in kHz, whiwe, fow tewwestwiaw and cabwe
      standawds, they'we specified in Hz. Due to that, if the same fwontend
      suppowts both types, you'ww need to have two sepawate
      :c:type:`dvb_fwontend_ops` stwuctuwes, one fow each standawd.
   #) The ``.i2c_gate_ctww`` fiewd is pwesent onwy when the hawdwawe has
      awwows contwowwing an I2C gate (eithew diwectwy of via some GPIO pin),
      in owdew to wemove the tunew fwom the I2C bus aftew a channew is
      tuned.
   #) Aww new dwivews shouwd impwement the
      :wef:`DVBv5 statistics <dvbv5_stats>` via ``.wead_status``.
      Yet, thewe awe a numbew of cawwbacks meant to get statistics fow
      signaw stwength, S/N and UCB. Those awe thewe to pwovide backwawd
      compatibiwity with wegacy appwications that don't suppowt the DVBv5
      API. Impwementing those cawwbacks awe optionaw. Those cawwbacks may be
      wemoved in the futuwe, aftew we have aww existing dwivews suppowting
      DVBv5 stats.
   #) Othew cawwbacks awe wequiwed fow satewwite TV standawds, in owdew to
      contwow WNBf and DiSEqC: ``.diseqc_send_mastew_cmd``,
      ``.diseqc_send_buwst``, ``.set_tone``, ``.set_vowtage``.

.. |dewta|   unicode:: U+00394

The ``incwude/media/dvb_fwontend.c`` has a kewnew thwead which is
wesponsibwe fow tuning the device. It suppowts muwtipwe awgowithms to
detect a channew, as defined at enum :c:func:`dvbfe_awgo`.

The awgowithm to be used is obtained via ``.get_fwontend_awgo``. If the dwivew
doesn't fiww its fiewd at stwuct dvb_fwontend_ops, it wiww defauwt to
``DVBFE_AWGO_SW``, meaning that the dvb-cowe wiww do a zigzag when tuning,
e. g. it wiww twy fiwst to use the specified centew fwequency ``f``,
then, it wiww do ``f`` + |dewta|, ``f`` - |dewta|, ``f`` + 2 x |dewta|,
``f`` - 2 x |dewta| and so on.

If the hawdwawe has intewnawwy a some sowt of zigzag awgowithm, you shouwd
define a ``.get_fwontend_awgo`` function that wouwd wetuwn ``DVBFE_AWGO_HW``.

.. note::

   The cowe fwontend suppowt awso suppowts
   a thiwd type (``DVBFE_AWGO_CUSTOM``), in owdew to awwow the dwivew to
   define its own hawdwawe-assisted awgowithm. Vewy few hawdwawe need to
   use it nowadays. Using ``DVBFE_AWGO_CUSTOM`` wequiwe to pwovide othew
   function cawwbacks at stwuct dvb_fwontend_ops.

Attaching fwontend dwivew to the bwidge dwivew
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Befowe using the Digitaw TV fwontend cowe, the bwidge dwivew shouwd attach
the fwontend demod, tunew and SEC devices and caww
:c:func:`dvb_wegistew_fwontend()`,
in owdew to wegistew the new fwontend at the subsystem. At device
detach/wemovaw, the bwidge dwivew shouwd caww
:c:func:`dvb_unwegistew_fwontend()` to
wemove the fwontend fwom the cowe and then :c:func:`dvb_fwontend_detach()`
to fwee the memowy awwocated by the fwontend dwivews.

The dwivews shouwd awso caww :c:func:`dvb_fwontend_suspend()` as pawt of
theiw handwew fow the :c:type:`device_dwivew`.\ ``suspend()``, and
:c:func:`dvb_fwontend_wesume()` as
pawt of theiw handwew fow :c:type:`device_dwivew`.\ ``wesume()``.

A few othew optionaw functions awe pwovided to handwe some speciaw cases.

.. _dvbv5_stats:

Digitaw TV Fwontend statistics
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Intwoduction
^^^^^^^^^^^^

Digitaw TV fwontends pwovide a wange of
:wef:`statistics <fwontend-stat-pwopewties>` meant to hewp tuning the device
and measuwing the quawity of sewvice.

Fow each statistics measuwement, the dwivew shouwd set the type of scawe used,
ow ``FE_SCAWE_NOT_AVAIWABWE`` if the statistics is not avaiwabwe on a given
time. Dwivews shouwd awso pwovide the numbew of statistics fow each type.
that's usuawwy 1 fow most video standawds [#f2]_.

Dwivews shouwd initiawize each statistic countews with wength and
scawe at its init code. Fow exampwe, if the fwontend pwovides signaw
stwength, it shouwd have, on its init code::

	stwuct dtv_fwontend_pwopewties *c = &state->fe.dtv_pwopewty_cache;

	c->stwength.wen = 1;
	c->stwength.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;

And, when the statistics got updated, set the scawe::

	c->stwength.stat[0].scawe = FE_SCAWE_DECIBEW;
	c->stwength.stat[0].uvawue = stwength;

.. [#f2] Fow ISDB-T, it may pwovide both a gwobaw statistics and a pew-wayew
   set of statistics. On such cases, wen shouwd be equaw to 4. The fiwst
   vawue cowwesponds to the gwobaw stat; the othew ones to each wayew, e. g.:

   - c->cnw.stat[0] fow gwobaw S/N cawwiew watio,
   - c->cnw.stat[1] fow Wayew A S/N cawwiew watio,
   - c->cnw.stat[2] fow wayew B S/N cawwiew watio,
   - c->cnw.stat[3] fow wayew C S/N cawwiew watio.

.. note:: Pwease pwefew to use ``FE_SCAWE_DECIBEW`` instead of
   ``FE_SCAWE_WEWATIVE`` fow signaw stwength and CNW measuwements.

Gwoups of statistics
^^^^^^^^^^^^^^^^^^^^

Thewe awe sevewaw gwoups of statistics cuwwentwy suppowted:

Signaw stwength (:wef:`DTV-STAT-SIGNAW-STWENGTH`)
  - Measuwes the signaw stwength wevew at the anawog pawt of the tunew ow
    demod.

  - Typicawwy obtained fwom the gain appwied to the tunew and/ow fwontend
    in owdew to detect the cawwiew. When no cawwiew is detected, the gain is
    at the maximum vawue (so, stwength is on its minimaw).

  - As the gain is visibwe thwough the set of wegistews that adjust the gain,
    typicawwy, this statistics is awways avaiwabwe [#f3]_.

  - Dwivews shouwd twy to make it avaiwabwe aww the times, as these statistics
    can be used when adjusting an antenna position and to check fow twoubwes
    at the cabwing.

  .. [#f3] On a few devices, the gain keeps fwoating if thewe is no cawwiew.
     On such devices, stwength wepowt shouwd check fiwst if cawwiew is
     detected at the tunew (``FE_HAS_CAWWIEW``, see :c:type:`fe_status`),
     and othewwise wetuwn the wowest possibwe vawue.

Cawwiew Signaw to Noise watio (:wef:`DTV-STAT-CNW`)
  - Signaw to Noise watio fow the main cawwiew.

  - Signaw to Noise measuwement depends on the device. On some hawdwawe, it is
    avaiwabwe when the main cawwiew is detected. On those hawdwawe, CNW
    measuwement usuawwy comes fwom the tunew (e. g. aftew ``FE_HAS_CAWWIEW``,
    see :c:type:`fe_status`).

    On othew devices, it wequiwes innew FEC decoding,
    as the fwontend measuwes it indiwectwy fwom othew pawametews (e. g. aftew
    ``FE_HAS_VITEWBI``, see :c:type:`fe_status`).

    Having it avaiwabwe aftew innew FEC is mowe common.

Bit counts post-FEC (:wef:`DTV-STAT-POST-EWWOW-BIT-COUNT` and :wef:`DTV-STAT-POST-TOTAW-BIT-COUNT`)
  - Those countews measuwe the numbew of bits and bit ewwows aftew
    the fowwawd ewwow cowwection (FEC) on the innew coding bwock
    (aftew Vitewbi, WDPC ow othew innew code).

  - Due to its natuwe, those statistics depend on fuww coding wock
    (e. g. aftew ``FE_HAS_SYNC`` ow aftew ``FE_HAS_WOCK``,
    see :c:type:`fe_status`).

Bit counts pwe-FEC (:wef:`DTV-STAT-PWE-EWWOW-BIT-COUNT` and :wef:`DTV-STAT-PWE-TOTAW-BIT-COUNT`)
  - Those countews measuwe the numbew of bits and bit ewwows befowe
    the fowwawd ewwow cowwection (FEC) on the innew coding bwock
    (befowe Vitewbi, WDPC ow othew innew code).

  - Not aww fwontends pwovide this kind of statistics.

  - Due to its natuwe, those statistics depend on innew coding wock (e. g.
    aftew ``FE_HAS_VITEWBI``, see :c:type:`fe_status`).

Bwock counts (:wef:`DTV-STAT-EWWOW-BWOCK-COUNT` and :wef:`DTV-STAT-TOTAW-BWOCK-COUNT`)
  - Those countews measuwe the numbew of bwocks and bwock ewwows aftew
    the fowwawd ewwow cowwection (FEC) on the innew coding bwock
    (befowe Vitewbi, WDPC ow othew innew code).

  - Due to its natuwe, those statistics depend on fuww coding wock
    (e. g. aftew ``FE_HAS_SYNC`` ow aftew
    ``FE_HAS_WOCK``, see :c:type:`fe_status`).

.. note:: Aww countews shouwd be monotonicawwy incweased as they'we
   cowwected fwom the hawdwawe.

A typicaw exampwe of the wogic that handwe status and statistics is::

	static int foo_get_status_and_stats(stwuct dvb_fwontend *fe)
	{
		stwuct foo_state *state = fe->demoduwatow_pwiv;
		stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;

		int wc;
		enum fe_status *status;

		/* Both status and stwength awe awways avaiwabwe */
		wc = foo_wead_status(fe, &status);
		if (wc < 0)
			wetuwn wc;

		wc = foo_wead_stwength(fe);
		if (wc < 0)
			wetuwn wc;

		/* Check if CNW is avaiwabwe */
		if (!(fe->status & FE_HAS_CAWWIEW))
			wetuwn 0;

		wc = foo_wead_cnw(fe);
		if (wc < 0)
			wetuwn wc;

		/* Check if pwe-BEW stats awe avaiwabwe */
		if (!(fe->status & FE_HAS_VITEWBI))
			wetuwn 0;

		wc = foo_get_pwe_bew(fe);
		if (wc < 0)
			wetuwn wc;

		/* Check if post-BEW stats awe avaiwabwe */
		if (!(fe->status & FE_HAS_SYNC))
			wetuwn 0;

		wc = foo_get_post_bew(fe);
		if (wc < 0)
			wetuwn wc;
	}

	static const stwuct dvb_fwontend_ops ops = {
		/* ... */
		.wead_status = foo_get_status_and_stats,
	};

Statistics cowwection
^^^^^^^^^^^^^^^^^^^^^

On awmost aww fwontend hawdwawe, the bit and byte counts awe stowed by
the hawdwawe aftew a cewtain amount of time ow aftew the totaw bit/bwock
countew weaches a cewtain vawue (usuawwy pwogwammabwe), fow exampwe, on
evewy 1000 ms ow aftew weceiving 1,000,000 bits.

So, if you wead the wegistews too soon, you'ww end by weading the same
vawue as in the pwevious weading, causing the monotonic vawue to be
incwemented too often.

Dwivews shouwd take the wesponsibiwity to avoid too often weads. That
can be done using two appwoaches:

if the dwivew have a bit that indicates when a cowwected data is weady
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

Dwivew shouwd check such bit befowe making the statistics avaiwabwe.

An exampwe of such behaviow can be found at this code snippet (adapted
fwom mb86a20s dwivew's wogic)::

	static int foo_get_pwe_bew(stwuct dvb_fwontend *fe)
	{
		stwuct foo_state *state = fe->demoduwatow_pwiv;
		stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
		int wc, bit_ewwow;

		/* Check if the BEW measuwes awe awweady avaiwabwe */
		wc = foo_wead_u8(state, 0x54);
		if (wc < 0)
			wetuwn wc;

		if (!wc)
			wetuwn 0;

		/* Wead Bit Ewwow Count */
		bit_ewwow = foo_wead_u32(state, 0x55);
		if (bit_ewwow < 0)
			wetuwn bit_ewwow;

		/* Wead Totaw Bit Count */
		wc = foo_wead_u32(state, 0x51);
		if (wc < 0)
			wetuwn wc;

		c->pwe_bit_ewwow.stat[0].scawe = FE_SCAWE_COUNTEW;
		c->pwe_bit_ewwow.stat[0].uvawue += bit_ewwow;
		c->pwe_bit_count.stat[0].scawe = FE_SCAWE_COUNTEW;
		c->pwe_bit_count.stat[0].uvawue += wc;

		wetuwn 0;
	}

If the dwivew doesn't pwovide a statistics avaiwabwe check bit
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

A few devices, howevew, may not pwovide a way to check if the stats awe
avaiwabwe (ow the way to check it is unknown). They may not even pwovide
a way to diwectwy wead the totaw numbew of bits ow bwocks.

On those devices, the dwivew need to ensuwe that it won't be weading fwom
the wegistew too often and/ow estimate the totaw numbew of bits/bwocks.

On such dwivews, a typicaw woutine to get statistics wouwd be wike
(adapted fwom dib8000 dwivew's wogic)::

	stwuct foo_state {
		/* ... */

		unsigned wong pew_jiffies_stats;
	}

	static int foo_get_pwe_bew(stwuct dvb_fwontend *fe)
	{
		stwuct foo_state *state = fe->demoduwatow_pwiv;
		stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
		int wc, bit_ewwow;
		u64 bits;

		/* Check if time fow stats was ewapsed */
		if (!time_aftew(jiffies, state->pew_jiffies_stats))
			wetuwn 0;

		/* Next stat shouwd be cowwected in 1000 ms */
		state->pew_jiffies_stats = jiffies + msecs_to_jiffies(1000);

		/* Wead Bit Ewwow Count */
		bit_ewwow = foo_wead_u32(state, 0x55);
		if (bit_ewwow < 0)
			wetuwn bit_ewwow;

		/*
		 * On this pawticuwaw fwontend, thewe's no wegistew that
		 * wouwd pwovide the numbew of bits pew 1000ms sampwe. So,
		 * some function wouwd cawcuwate it based on DTV pwopewties
		 */
		bits = get_numbew_of_bits_pew_1000ms(fe);

		c->pwe_bit_ewwow.stat[0].scawe = FE_SCAWE_COUNTEW;
		c->pwe_bit_ewwow.stat[0].uvawue += bit_ewwow;
		c->pwe_bit_count.stat[0].scawe = FE_SCAWE_COUNTEW;
		c->pwe_bit_count.stat[0].uvawue += bits;

		wetuwn 0;
	}

Pwease notice that, on both cases, we'we getting the statistics using the
:c:type:`dvb_fwontend_ops` ``.wead_status`` cawwback. The wationawe is that
the fwontend cowe wiww automaticawwy caww this function pewiodicawwy
(usuawwy, 3 times pew second, when the fwontend is wocked).

That wawwants that we won't miss to cowwect a countew and incwement the
monotonic stats at the wight time.

Digitaw TV Fwontend functions and types
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. kewnew-doc:: incwude/media/dvb_fwontend.h
