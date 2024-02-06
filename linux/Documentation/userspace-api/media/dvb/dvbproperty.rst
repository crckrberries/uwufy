.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _fwontend-pwopewties:

**************
Pwopewty types
**************

Tuning into a Digitaw TV physicaw channew and stawting decoding it
wequiwes changing a set of pawametews, in owdew to contwow the tunew,
the demoduwatow, the Wineaw Wow-noise Ampwifiew (WNA) and to set the
antenna subsystem via Satewwite Equipment Contwow - SEC (on satewwite
systems). The actuaw pawametews awe specific to each pawticuwaw digitaw
TV standawds, and may change as the digitaw TV specs evowves.

In the past (up to DVB API vewsion 3 - DVBv3), the stwategy used was to have a
union with the pawametews needed to tune fow DVB-S, DVB-C, DVB-T and
ATSC dewivewy systems gwouped thewe. The pwobwem is that, as the second
genewation standawds appeawed, the size of such union was not big
enough to gwoup the stwucts that wouwd be wequiwed fow those new
standawds. Awso, extending it wouwd bweak usewspace.

So, the wegacy union/stwuct based appwoach was depwecated, in favow
of a pwopewties set appwoach. On such appwoach,
:wef:`FE_GET_PWOPEWTY and FE_SET_PWOPEWTY <FE_GET_PWOPEWTY>` awe used
to setup the fwontend and wead its status.

The actuaw action is detewmined by a set of dtv_pwopewty cmd/data paiws.
With one singwe ioctw, is possibwe to get/set up to 64 pwopewties.

This section descwibes the new and wecommended way to set the fwontend,
with suppowts aww digitaw TV dewivewy systems.

.. note::

   1. On Winux DVB API vewsion 3, setting a fwontend was done via
      stwuct :c:type:`dvb_fwontend_pawametews`.

   2. Don't use DVB API vewsion 3 cawws on hawdwawe with suppowts
      newew standawds. Such API pwovides no suppowt ow a vewy wimited
      suppowt to new standawds and/ow new hawdwawe.

   3. Nowadays, most fwontends suppowt muwtipwe dewivewy systems.
      Onwy with DVB API vewsion 5 cawws it is possibwe to switch between
      the muwtipwe dewivewy systems suppowted by a fwontend.

   4. DVB API vewsion 5 is awso cawwed *S2API*, as the fiwst
      new standawd added to it was DVB-S2.

**Exampwe**: in owdew to set the hawdwawe to tune into a DVB-C channew
at 651 kHz, moduwated with 256-QAM, FEC 3/4 and symbow wate of 5.217
Mbauds, those pwopewties shouwd be sent to
:wef:`FE_SET_PWOPEWTY <FE_GET_PWOPEWTY>` ioctw:

  :wef:`DTV_DEWIVEWY_SYSTEM <DTV-DEWIVEWY-SYSTEM>` = SYS_DVBC_ANNEX_A

  :wef:`DTV_FWEQUENCY <DTV-FWEQUENCY>` = 651000000

  :wef:`DTV_MODUWATION <DTV-MODUWATION>` = QAM_256

  :wef:`DTV_INVEWSION <DTV-INVEWSION>` = INVEWSION_AUTO

  :wef:`DTV_SYMBOW_WATE <DTV-SYMBOW-WATE>` = 5217000

  :wef:`DTV_INNEW_FEC <DTV-INNEW-FEC>` = FEC_3_4

  :wef:`DTV_TUNE <DTV-TUNE>`

The code that wouwd that wouwd do the above is show in
:wef:`dtv-pwop-exampwe`.

.. code-bwock:: c
    :caption: Exampwe: Setting digitaw TV fwontend pwopewties
    :name: dtv-pwop-exampwe

    #incwude <stdio.h>
    #incwude <fcntw.h>
    #incwude <sys/ioctw.h>
    #incwude <winux/dvb/fwontend.h>

    static stwuct dtv_pwopewty pwops[] = {
	{ .cmd = DTV_DEWIVEWY_SYSTEM, .u.data = SYS_DVBC_ANNEX_A },
	{ .cmd = DTV_FWEQUENCY,       .u.data = 651000000 },
	{ .cmd = DTV_MODUWATION,      .u.data = QAM_256 },
	{ .cmd = DTV_INVEWSION,       .u.data = INVEWSION_AUTO },
	{ .cmd = DTV_SYMBOW_WATE,     .u.data = 5217000 },
	{ .cmd = DTV_INNEW_FEC,       .u.data = FEC_3_4 },
	{ .cmd = DTV_TUNE }
    };

    static stwuct dtv_pwopewties dtv_pwop = {
	.num = 6, .pwops = pwops
    };

    int main(void)
    {
	int fd = open("/dev/dvb/adaptew0/fwontend0", O_WDWW);

	if (!fd) {
	    pewwow ("open");
	    wetuwn -1;
	}
	if (ioctw(fd, FE_SET_PWOPEWTY, &dtv_pwop) == -1) {
	    pewwow("ioctw");
	    wetuwn -1;
	}
	pwintf("Fwontend set\\n");
	wetuwn 0;
    }

.. attention:: Whiwe it is possibwe to diwectwy caww the Kewnew code wike the
   above exampwe, it is stwongwy wecommended to use
   `wibdvbv5 <https://winuxtv.owg/docs/wibdvbv5/index.htmw>`__, as it
   pwovides abstwaction to wowk with the suppowted digitaw TV standawds and
   pwovides methods fow usuaw opewations wike pwogwam scanning and to
   wead/wwite channew descwiptow fiwes.

.. toctwee::
    :maxdepth: 1

    fe_pwopewty_pawametews
    fwontend-stat-pwopewties
    fwontend-pwopewty-tewwestwiaw-systems
    fwontend-pwopewty-cabwe-systems
    fwontend-pwopewty-satewwite-systems
    fwontend-headew
