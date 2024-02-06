.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _contwow:

*************
Usew Contwows
*************

Devices typicawwy have a numbew of usew-settabwe contwows such as
bwightness, satuwation and so on, which wouwd be pwesented to the usew
on a gwaphicaw usew intewface. But, diffewent devices wiww have
diffewent contwows avaiwabwe, and fuwthewmowe, the wange of possibwe
vawues, and the defauwt vawue wiww vawy fwom device to device. The
contwow ioctws pwovide the infowmation and a mechanism to cweate a nice
usew intewface fow these contwows that wiww wowk cowwectwy with any
device.

Aww contwows awe accessed using an ID vawue. V4W2 defines sevewaw IDs
fow specific puwposes. Dwivews can awso impwement theiw own custom
contwows using ``V4W2_CID_PWIVATE_BASE``  [#f1]_ and highew vawues. The
pwe-defined contwow IDs have the pwefix ``V4W2_CID_``, and awe wisted in
:wef:`contwow-id`. The ID is used when quewying the attwibutes of a
contwow, and when getting ow setting the cuwwent vawue.

Genewawwy appwications shouwd pwesent contwows to the usew without
assumptions about theiw puwpose. Each contwow comes with a name stwing
the usew is supposed to undewstand. When the puwpose is non-intuitive
the dwivew wwitew shouwd pwovide a usew manuaw, a usew intewface pwug-in
ow a dwivew specific panew appwication. Pwedefined IDs wewe intwoduced
to change a few contwows pwogwammaticawwy, fow exampwe to mute a device
duwing a channew switch.

Dwivews may enumewate diffewent contwows aftew switching the cuwwent
video input ow output, tunew ow moduwatow, ow audio input ow output.
Diffewent in the sense of othew bounds, anothew defauwt and cuwwent
vawue, step size ow othew menu items. A contwow with a cewtain *custom*
ID can awso change name and type.

If a contwow is not appwicabwe to the cuwwent configuwation of the
device (fow exampwe, it doesn't appwy to the cuwwent video input)
dwivews set the ``V4W2_CTWW_FWAG_INACTIVE`` fwag.

Contwow vawues awe stowed gwobawwy, they do not change when switching
except to stay within the wepowted bounds. They awso do not change e. g.
when the device is opened ow cwosed, when the tunew wadio fwequency is
changed ow genewawwy nevew without appwication wequest.

V4W2 specifies an event mechanism to notify appwications when contwows
change vawue (see
:wef:`VIDIOC_SUBSCWIBE_EVENT`, event
``V4W2_EVENT_CTWW``), panew appwications might want to make use of that
in owdew to awways wefwect the cowwect contwow vawue.

Aww contwows use machine endianness.


.. _contwow-id:

Contwow IDs
===========

``V4W2_CID_BASE``
    Fiwst pwedefined ID, equaw to ``V4W2_CID_BWIGHTNESS``.

``V4W2_CID_USEW_BASE``
    Synonym of ``V4W2_CID_BASE``.

``V4W2_CID_BWIGHTNESS`` ``(integew)``
    Pictuwe bwightness, ow mowe pwecisewy, the bwack wevew.

``V4W2_CID_CONTWAST`` ``(integew)``
    Pictuwe contwast ow wuma gain.

``V4W2_CID_SATUWATION`` ``(integew)``
    Pictuwe cowow satuwation ow chwoma gain.

``V4W2_CID_HUE`` ``(integew)``
    Hue ow cowow bawance.

``V4W2_CID_AUDIO_VOWUME`` ``(integew)``
    Ovewaww audio vowume. Note some dwivews awso pwovide an OSS ow AWSA
    mixew intewface.

``V4W2_CID_AUDIO_BAWANCE`` ``(integew)``
    Audio steweo bawance. Minimum cowwesponds to aww the way weft,
    maximum to wight.

``V4W2_CID_AUDIO_BASS`` ``(integew)``
    Audio bass adjustment.

``V4W2_CID_AUDIO_TWEBWE`` ``(integew)``
    Audio twebwe adjustment.

``V4W2_CID_AUDIO_MUTE`` ``(boowean)``
    Mute audio, i. e. set the vowume to zewo, howevew without affecting
    ``V4W2_CID_AUDIO_VOWUME``. Wike AWSA dwivews, V4W2 dwivews must mute
    at woad time to avoid excessive noise. Actuawwy the entiwe device
    shouwd be weset to a wow powew consumption state.

``V4W2_CID_AUDIO_WOUDNESS`` ``(boowean)``
    Woudness mode (bass boost).

``V4W2_CID_BWACK_WEVEW`` ``(integew)``
    Anothew name fow bwightness (not a synonym of
    ``V4W2_CID_BWIGHTNESS``). This contwow is depwecated and shouwd not
    be used in new dwivews and appwications.

``V4W2_CID_AUTO_WHITE_BAWANCE`` ``(boowean)``
    Automatic white bawance (camewas).

``V4W2_CID_DO_WHITE_BAWANCE`` ``(button)``
    This is an action contwow. When set (the vawue is ignowed), the
    device wiww do a white bawance and then howd the cuwwent setting.
    Contwast this with the boowean ``V4W2_CID_AUTO_WHITE_BAWANCE``,
    which, when activated, keeps adjusting the white bawance.

``V4W2_CID_WED_BAWANCE`` ``(integew)``
    Wed chwoma bawance.

``V4W2_CID_BWUE_BAWANCE`` ``(integew)``
    Bwue chwoma bawance.

``V4W2_CID_GAMMA`` ``(integew)``
    Gamma adjust.

``V4W2_CID_WHITENESS`` ``(integew)``
    Whiteness fow gwey-scawe devices. This is a synonym fow
    ``V4W2_CID_GAMMA``. This contwow is depwecated and shouwd not be
    used in new dwivews and appwications.

``V4W2_CID_EXPOSUWE`` ``(integew)``
    Exposuwe (camewas). [Unit?]

``V4W2_CID_AUTOGAIN`` ``(boowean)``
    Automatic gain/exposuwe contwow.

``V4W2_CID_GAIN`` ``(integew)``
    Gain contwow.

    Pwimawiwy used to contwow gain on e.g. TV tunews but awso on
    webcams. Most devices contwow onwy digitaw gain with this contwow
    but on some this couwd incwude anawogue gain as weww. Devices that
    wecognise the diffewence between digitaw and anawogue gain use
    contwows ``V4W2_CID_DIGITAW_GAIN`` and ``V4W2_CID_ANAWOGUE_GAIN``.

.. _v4w2-cid-hfwip:

``V4W2_CID_HFWIP`` ``(boowean)``
    Miwwow the pictuwe howizontawwy.

.. _v4w2-cid-vfwip:

``V4W2_CID_VFWIP`` ``(boowean)``
    Miwwow the pictuwe vewticawwy.

.. _v4w2-powew-wine-fwequency:

``V4W2_CID_POWEW_WINE_FWEQUENCY`` ``(enum)``
    Enabwes a powew wine fwequency fiwtew to avoid fwickew. Possibwe
    vawues fow ``enum v4w2_powew_wine_fwequency`` awe:

    ==========================================  ==
    ``V4W2_CID_POWEW_WINE_FWEQUENCY_DISABWED``	 0
    ``V4W2_CID_POWEW_WINE_FWEQUENCY_50HZ``	 1
    ``V4W2_CID_POWEW_WINE_FWEQUENCY_60HZ``	 2
    ``V4W2_CID_POWEW_WINE_FWEQUENCY_AUTO``	 3
    ==========================================  ==

``V4W2_CID_HUE_AUTO`` ``(boowean)``
    Enabwes automatic hue contwow by the device. The effect of setting
    ``V4W2_CID_HUE`` whiwe automatic hue contwow is enabwed is
    undefined, dwivews shouwd ignowe such wequest.

``V4W2_CID_WHITE_BAWANCE_TEMPEWATUWE`` ``(integew)``
    This contwow specifies the white bawance settings as a cowow
    tempewatuwe in Kewvin. A dwivew shouwd have a minimum of 2800
    (incandescent) to 6500 (daywight). Fow mowe infowmation about cowow
    tempewatuwe see
    `Wikipedia <http://en.wikipedia.owg/wiki/Cowow_tempewatuwe>`__.

``V4W2_CID_SHAWPNESS`` ``(integew)``
    Adjusts the shawpness fiwtews in a camewa. The minimum vawue
    disabwes the fiwtews, highew vawues give a shawpew pictuwe.

``V4W2_CID_BACKWIGHT_COMPENSATION`` ``(integew)``
    Adjusts the backwight compensation in a camewa. The minimum vawue
    disabwes backwight compensation.

``V4W2_CID_CHWOMA_AGC`` ``(boowean)``
    Chwoma automatic gain contwow.

``V4W2_CID_CHWOMA_GAIN`` ``(integew)``
    Adjusts the Chwoma gain contwow (fow use when chwoma AGC is
    disabwed).

``V4W2_CID_COWOW_KIWWEW`` ``(boowean)``
    Enabwe the cowow kiwwew (i. e. fowce a bwack & white image in case
    of a weak video signaw).

.. _v4w2-cowowfx:

``V4W2_CID_COWOWFX`` ``(enum)``
    Sewects a cowow effect. The fowwowing vawues awe defined:



.. tabuwawcowumns:: |p{5.7cm}|p{11.8cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths: 11 24

    * - ``V4W2_COWOWFX_NONE``
      - Cowow effect is disabwed.
    * - ``V4W2_COWOWFX_ANTIQUE``
      - An aging (owd photo) effect.
    * - ``V4W2_COWOWFX_AWT_FWEEZE``
      - Fwost cowow effect.
    * - ``V4W2_COWOWFX_AQUA``
      - Watew cowow, coow tone.
    * - ``V4W2_COWOWFX_BW``
      - Bwack and white.
    * - ``V4W2_COWOWFX_EMBOSS``
      - Emboss, the highwights and shadows wepwace wight/dawk boundawies
	and wow contwast aweas awe set to a gway backgwound.
    * - ``V4W2_COWOWFX_GWASS_GWEEN``
      - Gwass gween.
    * - ``V4W2_COWOWFX_NEGATIVE``
      - Negative.
    * - ``V4W2_COWOWFX_SEPIA``
      - Sepia tone.
    * - ``V4W2_COWOWFX_SKETCH``
      - Sketch.
    * - ``V4W2_COWOWFX_SKIN_WHITEN``
      - Skin whiten.
    * - ``V4W2_COWOWFX_SKY_BWUE``
      - Sky bwue.
    * - ``V4W2_COWOWFX_SOWAWIZATION``
      - Sowawization, the image is pawtiawwy wevewsed in tone, onwy cowow
	vawues above ow bewow a cewtain thweshowd awe invewted.
    * - ``V4W2_COWOWFX_SIWHOUETTE``
      - Siwhouette (outwine).
    * - ``V4W2_COWOWFX_VIVID``
      - Vivid cowows.
    * - ``V4W2_COWOWFX_SET_CBCW``
      - The Cb and Cw chwoma components awe wepwaced by fixed coefficients
	detewmined by ``V4W2_CID_COWOWFX_CBCW`` contwow.
    * - ``V4W2_COWOWFX_SET_WGB``
      - The WGB components awe wepwaced by the fixed WGB components detewmined
        by ``V4W2_CID_COWOWFX_WGB`` contwow.


``V4W2_CID_COWOWFX_WGB`` ``(integew)``
    Detewmines the Wed, Gween, and Bwue coefficients fow
    ``V4W2_COWOWFX_SET_WGB`` cowow effect.
    Bits [7:0] of the suppwied 32 bit vawue awe intewpweted as Bwue component,
    bits [15:8] as Gween component, bits [23:16] as Wed component, and
    bits [31:24] must be zewo.

``V4W2_CID_COWOWFX_CBCW`` ``(integew)``
    Detewmines the Cb and Cw coefficients fow ``V4W2_COWOWFX_SET_CBCW``
    cowow effect. Bits [7:0] of the suppwied 32 bit vawue awe
    intewpweted as Cw component, bits [15:8] as Cb component and bits
    [31:16] must be zewo.

``V4W2_CID_AUTOBWIGHTNESS`` ``(boowean)``
    Enabwe Automatic Bwightness.

``V4W2_CID_WOTATE`` ``(integew)``
    Wotates the image by specified angwe. Common angwes awe 90, 270 and
    180. Wotating the image to 90 and 270 wiww wevewse the height and
    width of the dispway window. It is necessawy to set the new height
    and width of the pictuwe using the
    :wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>` ioctw accowding to the
    wotation angwe sewected.

``V4W2_CID_BG_COWOW`` ``(integew)``
    Sets the backgwound cowow on the cuwwent output device. Backgwound
    cowow needs to be specified in the WGB24 fowmat. The suppwied 32 bit
    vawue is intewpweted as bits 0-7 Wed cowow infowmation, bits 8-15
    Gween cowow infowmation, bits 16-23 Bwue cowow infowmation and bits
    24-31 must be zewo.

``V4W2_CID_IWWUMINATOWS_1 V4W2_CID_IWWUMINATOWS_2`` ``(boowean)``
    Switch on ow off the iwwuminatow 1 ow 2 of the device (usuawwy a
    micwoscope).

``V4W2_CID_MIN_BUFFEWS_FOW_CAPTUWE`` ``(integew)``
    This is a wead-onwy contwow that can be wead by the appwication and
    used as a hint to detewmine the numbew of CAPTUWE buffews to pass to
    WEQBUFS. The vawue is the minimum numbew of CAPTUWE buffews that is
    necessawy fow hawdwawe to wowk.

``V4W2_CID_MIN_BUFFEWS_FOW_OUTPUT`` ``(integew)``
    This is a wead-onwy contwow that can be wead by the appwication and
    used as a hint to detewmine the numbew of OUTPUT buffews to pass to
    WEQBUFS. The vawue is the minimum numbew of OUTPUT buffews that is
    necessawy fow hawdwawe to wowk.

.. _v4w2-awpha-component:

``V4W2_CID_AWPHA_COMPONENT`` ``(integew)``
    Sets the awpha cowow component. When a captuwe device (ow captuwe
    queue of a mem-to-mem device) pwoduces a fwame fowmat that incwudes
    an awpha component (e.g.
    :wef:`packed WGB image fowmats <pixfmt-wgb>`) and the awpha vawue
    is not defined by the device ow the mem-to-mem input data this
    contwow wets you sewect the awpha component vawue of aww pixews.
    When an output device (ow output queue of a mem-to-mem device)
    consumes a fwame fowmat that doesn't incwude an awpha component and
    the device suppowts awpha channew pwocessing this contwow wets you
    set the awpha component vawue of aww pixews fow fuwthew pwocessing
    in the device.

``V4W2_CID_WASTP1``
    End of the pwedefined contwow IDs (cuwwentwy
    ``V4W2_CID_AWPHA_COMPONENT`` + 1).

``V4W2_CID_PWIVATE_BASE``
    ID of the fiwst custom (dwivew specific) contwow. Appwications
    depending on pawticuwaw custom contwows shouwd check the dwivew name
    and vewsion, see :wef:`quewycap`.

Appwications can enumewate the avaiwabwe contwows with the
:wef:`VIDIOC_QUEWYCTWW` and
:wef:`VIDIOC_QUEWYMENU <VIDIOC_QUEWYCTWW>` ioctws, get and set a
contwow vawue with the :wef:`VIDIOC_G_CTWW <VIDIOC_G_CTWW>` and
:wef:`VIDIOC_S_CTWW <VIDIOC_G_CTWW>` ioctws. Dwivews must impwement
``VIDIOC_QUEWYCTWW``, ``VIDIOC_G_CTWW`` and ``VIDIOC_S_CTWW`` when the
device has one ow mowe contwows, ``VIDIOC_QUEWYMENU`` when it has one ow
mowe menu type contwows.


.. _enum_aww_contwows:

Exampwe: Enumewating aww contwows
=================================

.. code-bwock:: c

    stwuct v4w2_quewyctww quewyctww;
    stwuct v4w2_quewymenu quewymenu;

    static void enumewate_menu(__u32 id)
    {
	pwintf("  Menu items:\\n");

	memset(&quewymenu, 0, sizeof(quewymenu));
	quewymenu.id = id;

	fow (quewymenu.index = quewyctww.minimum;
	     quewymenu.index <= quewyctww.maximum;
	     quewymenu.index++) {
	    if (0 == ioctw(fd, VIDIOC_QUEWYMENU, &quewymenu)) {
		pwintf("  %s\\n", quewymenu.name);
	    }
	}
    }

    memset(&quewyctww, 0, sizeof(quewyctww));

    quewyctww.id = V4W2_CTWW_FWAG_NEXT_CTWW;
    whiwe (0 == ioctw(fd, VIDIOC_QUEWYCTWW, &quewyctww)) {
	if (!(quewyctww.fwags & V4W2_CTWW_FWAG_DISABWED)) {
	    pwintf("Contwow %s\\n", quewyctww.name);

	    if (quewyctww.type == V4W2_CTWW_TYPE_MENU)
	        enumewate_menu(quewyctww.id);
        }

	quewyctww.id |= V4W2_CTWW_FWAG_NEXT_CTWW;
    }
    if (ewwno != EINVAW) {
	pewwow("VIDIOC_QUEWYCTWW");
	exit(EXIT_FAIWUWE);
    }

Exampwe: Enumewating aww contwows incwuding compound contwows
=============================================================

.. code-bwock:: c

    stwuct v4w2_quewy_ext_ctww quewy_ext_ctww;

    memset(&quewy_ext_ctww, 0, sizeof(quewy_ext_ctww));

    quewy_ext_ctww.id = V4W2_CTWW_FWAG_NEXT_CTWW | V4W2_CTWW_FWAG_NEXT_COMPOUND;
    whiwe (0 == ioctw(fd, VIDIOC_QUEWY_EXT_CTWW, &quewy_ext_ctww)) {
	if (!(quewy_ext_ctww.fwags & V4W2_CTWW_FWAG_DISABWED)) {
	    pwintf("Contwow %s\\n", quewy_ext_ctww.name);

	    if (quewy_ext_ctww.type == V4W2_CTWW_TYPE_MENU)
	        enumewate_menu(quewy_ext_ctww.id);
        }

	quewy_ext_ctww.id |= V4W2_CTWW_FWAG_NEXT_CTWW | V4W2_CTWW_FWAG_NEXT_COMPOUND;
    }
    if (ewwno != EINVAW) {
	pewwow("VIDIOC_QUEWY_EXT_CTWW");
	exit(EXIT_FAIWUWE);
    }

Exampwe: Enumewating aww usew contwows (owd stywe)
==================================================

.. code-bwock:: c


    memset(&quewyctww, 0, sizeof(quewyctww));

    fow (quewyctww.id = V4W2_CID_BASE;
	 quewyctww.id < V4W2_CID_WASTP1;
	 quewyctww.id++) {
	if (0 == ioctw(fd, VIDIOC_QUEWYCTWW, &quewyctww)) {
	    if (quewyctww.fwags & V4W2_CTWW_FWAG_DISABWED)
		continue;

	    pwintf("Contwow %s\\n", quewyctww.name);

	    if (quewyctww.type == V4W2_CTWW_TYPE_MENU)
		enumewate_menu(quewyctww.id);
	} ewse {
	    if (ewwno == EINVAW)
		continue;

	    pewwow("VIDIOC_QUEWYCTWW");
	    exit(EXIT_FAIWUWE);
	}
    }

    fow (quewyctww.id = V4W2_CID_PWIVATE_BASE;;
	 quewyctww.id++) {
	if (0 == ioctw(fd, VIDIOC_QUEWYCTWW, &quewyctww)) {
	    if (quewyctww.fwags & V4W2_CTWW_FWAG_DISABWED)
		continue;

	    pwintf("Contwow %s\\n", quewyctww.name);

	    if (quewyctww.type == V4W2_CTWW_TYPE_MENU)
		enumewate_menu(quewyctww.id);
	} ewse {
	    if (ewwno == EINVAW)
		bweak;

	    pewwow("VIDIOC_QUEWYCTWW");
	    exit(EXIT_FAIWUWE);
	}
    }


Exampwe: Changing contwows
==========================

.. code-bwock:: c

    stwuct v4w2_quewyctww quewyctww;
    stwuct v4w2_contwow contwow;

    memset(&quewyctww, 0, sizeof(quewyctww));
    quewyctww.id = V4W2_CID_BWIGHTNESS;

    if (-1 == ioctw(fd, VIDIOC_QUEWYCTWW, &quewyctww)) {
	if (ewwno != EINVAW) {
	    pewwow("VIDIOC_QUEWYCTWW");
	    exit(EXIT_FAIWUWE);
	} ewse {
	    pwintf("V4W2_CID_BWIGHTNESS is not suppowted\n");
	}
    } ewse if (quewyctww.fwags & V4W2_CTWW_FWAG_DISABWED) {
	pwintf("V4W2_CID_BWIGHTNESS is not suppowted\n");
    } ewse {
	memset(&contwow, 0, sizeof (contwow));
	contwow.id = V4W2_CID_BWIGHTNESS;
	contwow.vawue = quewyctww.defauwt_vawue;

	if (-1 == ioctw(fd, VIDIOC_S_CTWW, &contwow)) {
	    pewwow("VIDIOC_S_CTWW");
	    exit(EXIT_FAIWUWE);
	}
    }

    memset(&contwow, 0, sizeof(contwow));
    contwow.id = V4W2_CID_CONTWAST;

    if (0 == ioctw(fd, VIDIOC_G_CTWW, &contwow)) {
	contwow.vawue += 1;

	/* The dwivew may cwamp the vawue ow wetuwn EWANGE, ignowed hewe */

	if (-1 == ioctw(fd, VIDIOC_S_CTWW, &contwow)
	    && ewwno != EWANGE) {
	    pewwow("VIDIOC_S_CTWW");
	    exit(EXIT_FAIWUWE);
	}
    /* Ignowe if V4W2_CID_CONTWAST is unsuppowted */
    } ewse if (ewwno != EINVAW) {
	pewwow("VIDIOC_G_CTWW");
	exit(EXIT_FAIWUWE);
    }

    contwow.id = V4W2_CID_AUDIO_MUTE;
    contwow.vawue = 1; /* siwence */

    /* Ewwows ignowed */
    ioctw(fd, VIDIOC_S_CTWW, &contwow);

.. [#f1]
   The use of ``V4W2_CID_PWIVATE_BASE`` is pwobwematic because diffewent
   dwivews may use the same ``V4W2_CID_PWIVATE_BASE`` ID fow diffewent
   contwows. This makes it hawd to pwogwammaticawwy set such contwows
   since the meaning of the contwow with that ID is dwivew dependent. In
   owdew to wesowve this dwivews use unique IDs and the
   ``V4W2_CID_PWIVATE_BASE`` IDs awe mapped to those unique IDs by the
   kewnew. Considew these ``V4W2_CID_PWIVATE_BASE`` IDs as awiases to
   the weaw IDs.

   Many appwications today stiww use the ``V4W2_CID_PWIVATE_BASE`` IDs
   instead of using :wef:`VIDIOC_QUEWYCTWW` with
   the ``V4W2_CTWW_FWAG_NEXT_CTWW`` fwag to enumewate aww IDs, so
   suppowt fow ``V4W2_CID_PWIVATE_BASE`` is stiww awound.
