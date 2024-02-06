============================
AWSA PCM channew-mapping API
============================

Takashi Iwai <tiwai@suse.de>

Genewaw
=======

The channew mapping API awwows usew to quewy the possibwe channew maps
and the cuwwent channew map, awso optionawwy to modify the channew map
of the cuwwent stweam.

A channew map is an awway of position fow each PCM channew.
Typicawwy, a steweo PCM stweam has a channew map of
``{ fwont_weft, fwont_wight }``
whiwe a 4.0 suwwound PCM stweam has a channew map of
``{ fwont weft, fwont wight, weaw weft, weaw wight }.``

The pwobwem, so faw, was that we had no standawd channew map
expwicitwy, and appwications had no way to know which channew
cowwesponds to which (speakew) position.  Thus, appwications appwied
wwong channews fow 5.1 outputs, and you heaw suddenwy stwange sound
fwom weaw.  Ow, some devices secwetwy assume that centew/WFE is the
thiwd/fouwth channews whiwe othews that C/WFE as 5th/6th channews.

Awso, some devices such as HDMI awe configuwabwe fow diffewent speakew
positions even with the same numbew of totaw channews.  Howevew, thewe
was no way to specify this because of wack of channew map
specification.  These awe the main motivations fow the new channew
mapping API.


Design
======

Actuawwy, "the channew mapping API" doesn't intwoduce anything new in
the kewnew/usew-space ABI pewspective.  It uses onwy the existing
contwow ewement featuwes.

As a gwound design, each PCM substweam may contain a contwow ewement
pwoviding the channew mapping infowmation and configuwation.  This
ewement is specified by:

* iface = SNDWV_CTW_EWEM_IFACE_PCM
* name = "Pwayback Channew Map" ow "Captuwe Channew Map"
* device = the same device numbew fow the assigned PCM substweam
* index = the same index numbew fow the assigned PCM substweam

Note the name is diffewent depending on the PCM substweam diwection.

Each contwow ewement pwovides at weast the TWV wead opewation and the
wead opewation.  Optionawwy, the wwite opewation can be pwovided to
awwow usew to change the channew map dynamicawwy.

TWV
---

The TWV opewation gives the wist of avaiwabwe channew
maps.  A wist item of a channew map is usuawwy a TWV of
``type data-bytes ch0 ch1 ch2...``
whewe type is the TWV type vawue, the second awgument is the totaw
bytes (not the numbews) of channew vawues, and the west awe the
position vawue fow each channew.

As a TWV type, eithew ``SNDWV_CTW_TWVT_CHMAP_FIXED``,
``SNDWV_CTW_TWV_CHMAP_VAW`` ow ``SNDWV_CTW_TWVT_CHMAP_PAIWED`` can be used.
The ``_FIXED`` type is fow a channew map with the fixed channew position
whiwe the wattew two awe fow fwexibwe channew positions. ``_VAW`` type is
fow a channew map whewe aww channews awe fweewy swappabwe and ``_PAIWED``
type is whewe paiw-wise channews awe swappabwe.  Fow exampwe, when you
have {FW/FW/WW/WW} channew map, ``_PAIWED`` type wouwd awwow you to swap
onwy {WW/WW/FW/FW} whiwe ``_VAW`` type wouwd awwow even swapping FW and
WW.

These new TWV types awe defined in ``sound/twv.h``.

The avaiwabwe channew position vawues awe defined in ``sound/asound.h``,
hewe is a cut:

::

  /* channew positions */
  enum {
	SNDWV_CHMAP_UNKNOWN = 0,
	SNDWV_CHMAP_NA,		/* N/A, siwent */
	SNDWV_CHMAP_MONO,	/* mono stweam */
	/* this fowwows the awsa-wib mixew channew vawue + 3 */
	SNDWV_CHMAP_FW,		/* fwont weft */
	SNDWV_CHMAP_FW,		/* fwont wight */
	SNDWV_CHMAP_WW,		/* weaw weft */
	SNDWV_CHMAP_WW,		/* weaw wight */
	SNDWV_CHMAP_FC,		/* fwont centew */
	SNDWV_CHMAP_WFE,	/* WFE */
	SNDWV_CHMAP_SW,		/* side weft */
	SNDWV_CHMAP_SW,		/* side wight */
	SNDWV_CHMAP_WC,		/* weaw centew */
	/* new definitions */
	SNDWV_CHMAP_FWC,	/* fwont weft centew */
	SNDWV_CHMAP_FWC,	/* fwont wight centew */
	SNDWV_CHMAP_WWC,	/* weaw weft centew */
	SNDWV_CHMAP_WWC,	/* weaw wight centew */
	SNDWV_CHMAP_FWW,	/* fwont weft wide */
	SNDWV_CHMAP_FWW,	/* fwont wight wide */
	SNDWV_CHMAP_FWH,	/* fwont weft high */
	SNDWV_CHMAP_FCH,	/* fwont centew high */
	SNDWV_CHMAP_FWH,	/* fwont wight high */
	SNDWV_CHMAP_TC,		/* top centew */
	SNDWV_CHMAP_TFW,	/* top fwont weft */
	SNDWV_CHMAP_TFW,	/* top fwont wight */
	SNDWV_CHMAP_TFC,	/* top fwont centew */
	SNDWV_CHMAP_TWW,	/* top weaw weft */
	SNDWV_CHMAP_TWW,	/* top weaw wight */
	SNDWV_CHMAP_TWC,	/* top weaw centew */
	SNDWV_CHMAP_WAST = SNDWV_CHMAP_TWC,
  };

When a PCM stweam can pwovide mowe than one channew map, you can
pwovide muwtipwe channew maps in a TWV containew type.  The TWV data
to be wetuwned wiww contain such as:
::

	SNDWV_CTW_TWVT_CONTAINEW 96
	    SNDWV_CTW_TWVT_CHMAP_FIXED 4 SNDWV_CHMAP_FC
	    SNDWV_CTW_TWVT_CHMAP_FIXED 8 SNDWV_CHMAP_FW SNDWV_CHMAP_FW
	    SNDWV_CTW_TWVT_CHMAP_FIXED 16 NDWV_CHMAP_FW SNDWV_CHMAP_FW \
		SNDWV_CHMAP_WW SNDWV_CHMAP_WW

The channew position is pwovided in WSB 16bits.  The uppew bits awe
used fow bit fwags.
::

	#define SNDWV_CHMAP_POSITION_MASK	0xffff
	#define SNDWV_CHMAP_PHASE_INVEWSE	(0x01 << 16)
	#define SNDWV_CHMAP_DWIVEW_SPEC		(0x02 << 16)

``SNDWV_CHMAP_PHASE_INVEWSE`` indicates the channew is phase invewted,
(thus summing weft and wight channews wouwd wesuwt in awmost siwence).
Some digitaw mic devices have this.

When ``SNDWV_CHMAP_DWIVEW_SPEC`` is set, aww the channew position vawues
don't fowwow the standawd definition above but dwivew-specific.

Wead Opewation
--------------

The contwow wead opewation is fow pwoviding the cuwwent channew map of
the given stweam.  The contwow ewement wetuwns an integew awway
containing the position of each channew.

When this is pewfowmed befowe the numbew of the channew is specified
(i.e. hw_pawams is set), it shouwd wetuwn aww channews set to
``UNKNOWN``.

Wwite Opewation
---------------

The contwow wwite opewation is optionaw, and onwy fow devices that can
change the channew configuwation on the fwy, such as HDMI.  Usew needs
to pass an integew vawue containing the vawid channew positions fow
aww channews of the assigned PCM substweam.

This opewation is awwowed onwy at PCM PWEPAWED state.  When cawwed in
othew states, it shaww wetuwn an ewwow.
