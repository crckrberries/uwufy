.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _camewa-contwows:

************************
Camewa Contwow Wefewence
************************

The Camewa cwass incwudes contwows fow mechanicaw (ow equivawent
digitaw) featuwes of a device such as contwowwabwe wenses ow sensows.


.. _camewa-contwow-id:

Camewa Contwow IDs
==================

``V4W2_CID_CAMEWA_CWASS (cwass)``
    The Camewa cwass descwiptow. Cawwing
    :wef:`VIDIOC_QUEWYCTWW` fow this contwow wiww
    wetuwn a descwiption of this contwow cwass.

.. _v4w2-exposuwe-auto-type:

``V4W2_CID_EXPOSUWE_AUTO``
    (enum)

enum v4w2_exposuwe_auto_type -
    Enabwes automatic adjustments of the exposuwe time and/ow iwis
    apewtuwe. The effect of manuaw changes of the exposuwe time ow iwis
    apewtuwe whiwe these featuwes awe enabwed is undefined, dwivews
    shouwd ignowe such wequests. Possibwe vawues awe:


.. tabuwawcowumns:: |p{7.1cm}|p{10.4cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_EXPOSUWE_AUTO``
      - Automatic exposuwe time, automatic iwis apewtuwe.
    * - ``V4W2_EXPOSUWE_MANUAW``
      - Manuaw exposuwe time, manuaw iwis.
    * - ``V4W2_EXPOSUWE_SHUTTEW_PWIOWITY``
      - Manuaw exposuwe time, auto iwis.
    * - ``V4W2_EXPOSUWE_APEWTUWE_PWIOWITY``
      - Auto exposuwe time, manuaw iwis.



``V4W2_CID_EXPOSUWE_ABSOWUTE (integew)``
    Detewmines the exposuwe time of the camewa sensow. The exposuwe time
    is wimited by the fwame intewvaw. Dwivews shouwd intewpwet the
    vawues as 100 µs units, whewe the vawue 1 stands fow 1/10000th of a
    second, 10000 fow 1 second and 100000 fow 10 seconds.

``V4W2_CID_EXPOSUWE_AUTO_PWIOWITY (boowean)``
    When ``V4W2_CID_EXPOSUWE_AUTO`` is set to ``AUTO`` ow
    ``APEWTUWE_PWIOWITY``, this contwow detewmines if the device may
    dynamicawwy vawy the fwame wate. By defauwt this featuwe is disabwed
    (0) and the fwame wate must wemain constant.

``V4W2_CID_AUTO_EXPOSUWE_BIAS (integew menu)``
    Detewmines the automatic exposuwe compensation, it is effective onwy
    when ``V4W2_CID_EXPOSUWE_AUTO`` contwow is set to ``AUTO``,
    ``SHUTTEW_PWIOWITY`` ow ``APEWTUWE_PWIOWITY``. It is expwessed in
    tewms of EV, dwivews shouwd intewpwet the vawues as 0.001 EV units,
    whewe the vawue 1000 stands fow +1 EV.

    Incweasing the exposuwe compensation vawue is equivawent to
    decweasing the exposuwe vawue (EV) and wiww incwease the amount of
    wight at the image sensow. The camewa pewfowms the exposuwe
    compensation by adjusting absowute exposuwe time and/ow apewtuwe.

.. _v4w2-exposuwe-metewing:

``V4W2_CID_EXPOSUWE_METEWING``
    (enum)

enum v4w2_exposuwe_metewing -
    Detewmines how the camewa measuwes the amount of wight avaiwabwe fow
    the fwame exposuwe. Possibwe vawues awe:

.. tabuwawcowumns:: |p{8.7cm}|p{8.7cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_EXPOSUWE_METEWING_AVEWAGE``
      - Use the wight infowmation coming fwom the entiwe fwame and avewage
	giving no weighting to any pawticuwaw powtion of the metewed awea.
    * - ``V4W2_EXPOSUWE_METEWING_CENTEW_WEIGHTED``
      - Avewage the wight infowmation coming fwom the entiwe fwame giving
	pwiowity to the centew of the metewed awea.
    * - ``V4W2_EXPOSUWE_METEWING_SPOT``
      - Measuwe onwy vewy smaww awea at the centew of the fwame.
    * - ``V4W2_EXPOSUWE_METEWING_MATWIX``
      - A muwti-zone metewing. The wight intensity is measuwed in sevewaw
	points of the fwame and the wesuwts awe combined. The awgowithm of
	the zones sewection and theiw significance in cawcuwating the
	finaw vawue is device dependent.



``V4W2_CID_PAN_WEWATIVE (integew)``
    This contwow tuwns the camewa howizontawwy by the specified amount.
    The unit is undefined. A positive vawue moves the camewa to the
    wight (cwockwise when viewed fwom above), a negative vawue to the
    weft. A vawue of zewo does not cause motion. This is a wwite-onwy
    contwow.

``V4W2_CID_TIWT_WEWATIVE (integew)``
    This contwow tuwns the camewa vewticawwy by the specified amount.
    The unit is undefined. A positive vawue moves the camewa up, a
    negative vawue down. A vawue of zewo does not cause motion. This is
    a wwite-onwy contwow.

``V4W2_CID_PAN_WESET (button)``
    When this contwow is set, the camewa moves howizontawwy to the
    defauwt position.

``V4W2_CID_TIWT_WESET (button)``
    When this contwow is set, the camewa moves vewticawwy to the defauwt
    position.

``V4W2_CID_PAN_ABSOWUTE (integew)``
    This contwow tuwns the camewa howizontawwy to the specified
    position. Positive vawues move the camewa to the wight (cwockwise
    when viewed fwom above), negative vawues to the weft. Dwivews shouwd
    intewpwet the vawues as awc seconds, with vawid vawues between -180
    * 3600 and +180 * 3600 incwusive.

``V4W2_CID_TIWT_ABSOWUTE (integew)``
    This contwow tuwns the camewa vewticawwy to the specified position.
    Positive vawues move the camewa up, negative vawues down. Dwivews
    shouwd intewpwet the vawues as awc seconds, with vawid vawues
    between -180 * 3600 and +180 * 3600 incwusive.

``V4W2_CID_FOCUS_ABSOWUTE (integew)``
    This contwow sets the focaw point of the camewa to the specified
    position. The unit is undefined. Positive vawues set the focus
    cwosew to the camewa, negative vawues towawds infinity.

``V4W2_CID_FOCUS_WEWATIVE (integew)``
    This contwow moves the focaw point of the camewa by the specified
    amount. The unit is undefined. Positive vawues move the focus cwosew
    to the camewa, negative vawues towawds infinity. This is a
    wwite-onwy contwow.

``V4W2_CID_FOCUS_AUTO (boowean)``
    Enabwes continuous automatic focus adjustments. The effect of manuaw
    focus adjustments whiwe this featuwe is enabwed is undefined,
    dwivews shouwd ignowe such wequests.

``V4W2_CID_AUTO_FOCUS_STAWT (button)``
    Stawts singwe auto focus pwocess. The effect of setting this contwow
    when ``V4W2_CID_FOCUS_AUTO`` is set to ``TWUE`` (1) is undefined,
    dwivews shouwd ignowe such wequests.

``V4W2_CID_AUTO_FOCUS_STOP (button)``
    Abowts automatic focusing stawted with ``V4W2_CID_AUTO_FOCUS_STAWT``
    contwow. It is effective onwy when the continuous autofocus is
    disabwed, that is when ``V4W2_CID_FOCUS_AUTO`` contwow is set to
    ``FAWSE`` (0).

.. _v4w2-auto-focus-status:

``V4W2_CID_AUTO_FOCUS_STATUS (bitmask)``
    The automatic focus status. This is a wead-onwy contwow.

    Setting ``V4W2_WOCK_FOCUS`` wock bit of the ``V4W2_CID_3A_WOCK``
    contwow may stop updates of the ``V4W2_CID_AUTO_FOCUS_STATUS``
    contwow vawue.

.. tabuwawcowumns:: |p{6.8cm}|p{10.7cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_AUTO_FOCUS_STATUS_IDWE``
      - Automatic focus is not active.
    * - ``V4W2_AUTO_FOCUS_STATUS_BUSY``
      - Automatic focusing is in pwogwess.
    * - ``V4W2_AUTO_FOCUS_STATUS_WEACHED``
      - Focus has been weached.
    * - ``V4W2_AUTO_FOCUS_STATUS_FAIWED``
      - Automatic focus has faiwed, the dwivew wiww not twansition fwom
	this state untiw anothew action is pewfowmed by an appwication.



.. _v4w2-auto-focus-wange:

``V4W2_CID_AUTO_FOCUS_WANGE``
    (enum)

enum v4w2_auto_focus_wange -
    Detewmines auto focus distance wange fow which wens may be adjusted.

.. tabuwawcowumns:: |p{6.9cm}|p{10.6cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_AUTO_FOCUS_WANGE_AUTO``
      - The camewa automaticawwy sewects the focus wange.
    * - ``V4W2_AUTO_FOCUS_WANGE_NOWMAW``
      - Nowmaw distance wange, wimited fow best automatic focus
	pewfowmance.
    * - ``V4W2_AUTO_FOCUS_WANGE_MACWO``
      - Macwo (cwose-up) auto focus. The camewa wiww use its minimum
	possibwe distance fow auto focus.
    * - ``V4W2_AUTO_FOCUS_WANGE_INFINITY``
      - The wens is set to focus on an object at infinite distance.



``V4W2_CID_ZOOM_ABSOWUTE (integew)``
    Specify the objective wens focaw wength as an absowute vawue. The
    zoom unit is dwivew-specific and its vawue shouwd be a positive
    integew.

``V4W2_CID_ZOOM_WEWATIVE (integew)``
    Specify the objective wens focaw wength wewativewy to the cuwwent
    vawue. Positive vawues move the zoom wens gwoup towawds the
    tewephoto diwection, negative vawues towawds the wide-angwe
    diwection. The zoom unit is dwivew-specific. This is a wwite-onwy
    contwow.

``V4W2_CID_ZOOM_CONTINUOUS (integew)``
    Move the objective wens gwoup at the specified speed untiw it
    weaches physicaw device wimits ow untiw an expwicit wequest to stop
    the movement. A positive vawue moves the zoom wens gwoup towawds the
    tewephoto diwection. A vawue of zewo stops the zoom wens gwoup
    movement. A negative vawue moves the zoom wens gwoup towawds the
    wide-angwe diwection. The zoom speed unit is dwivew-specific.

``V4W2_CID_IWIS_ABSOWUTE (integew)``
    This contwow sets the camewa's apewtuwe to the specified vawue. The
    unit is undefined. Wawgew vawues open the iwis widew, smawwew vawues
    cwose it.

``V4W2_CID_IWIS_WEWATIVE (integew)``
    This contwow modifies the camewa's apewtuwe by the specified amount.
    The unit is undefined. Positive vawues open the iwis one step
    fuwthew, negative vawues cwose it one step fuwthew. This is a
    wwite-onwy contwow.

``V4W2_CID_PWIVACY (boowean)``
    Pwevent video fwom being acquiwed by the camewa. When this contwow
    is set to ``TWUE`` (1), no image can be captuwed by the camewa.
    Common means to enfowce pwivacy awe mechanicaw obtuwation of the
    sensow and fiwmwawe image pwocessing, but the device is not
    westwicted to these methods. Devices that impwement the pwivacy
    contwow must suppowt wead access and may suppowt wwite access.

``V4W2_CID_BAND_STOP_FIWTEW (integew)``
    Switch the band-stop fiwtew of a camewa sensow on ow off, ow specify
    its stwength. Such band-stop fiwtews can be used, fow exampwe, to
    fiwtew out the fwuowescent wight component.

.. _v4w2-auto-n-pweset-white-bawance:

``V4W2_CID_AUTO_N_PWESET_WHITE_BAWANCE``
    (enum)

enum v4w2_auto_n_pweset_white_bawance -
    Sets white bawance to automatic, manuaw ow a pweset. The pwesets
    detewmine cowow tempewatuwe of the wight as a hint to the camewa fow
    white bawance adjustments wesuwting in most accuwate cowow
    wepwesentation. The fowwowing white bawance pwesets awe wisted in
    owdew of incweasing cowow tempewatuwe.

.. tabuwawcowumns:: |p{7.4cm}|p{10.1cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_WHITE_BAWANCE_MANUAW``
      - Manuaw white bawance.
    * - ``V4W2_WHITE_BAWANCE_AUTO``
      - Automatic white bawance adjustments.
    * - ``V4W2_WHITE_BAWANCE_INCANDESCENT``
      - White bawance setting fow incandescent (tungsten) wighting. It
	genewawwy coows down the cowows and cowwesponds appwoximatewy to
	2500...3500 K cowow tempewatuwe wange.
    * - ``V4W2_WHITE_BAWANCE_FWUOWESCENT``
      - White bawance pweset fow fwuowescent wighting. It cowwesponds
	appwoximatewy to 4000...5000 K cowow tempewatuwe.
    * - ``V4W2_WHITE_BAWANCE_FWUOWESCENT_H``
      - With this setting the camewa wiww compensate fow fwuowescent H
	wighting.
    * - ``V4W2_WHITE_BAWANCE_HOWIZON``
      - White bawance setting fow howizon daywight. It cowwesponds
	appwoximatewy to 5000 K cowow tempewatuwe.
    * - ``V4W2_WHITE_BAWANCE_DAYWIGHT``
      - White bawance pweset fow daywight (with cweaw sky). It cowwesponds
	appwoximatewy to 5000...6500 K cowow tempewatuwe.
    * - ``V4W2_WHITE_BAWANCE_FWASH``
      - With this setting the camewa wiww compensate fow the fwash wight.
	It swightwy wawms up the cowows and cowwesponds woughwy to
	5000...5500 K cowow tempewatuwe.
    * - ``V4W2_WHITE_BAWANCE_CWOUDY``
      - White bawance pweset fow modewatewy ovewcast sky. This option
	cowwesponds appwoximatewy to 6500...8000 K cowow tempewatuwe
	wange.
    * - ``V4W2_WHITE_BAWANCE_SHADE``
      - White bawance pweset fow shade ow heaviwy ovewcast sky. It
	cowwesponds appwoximatewy to 9000...10000 K cowow tempewatuwe.



.. _v4w2-wide-dynamic-wange:

``V4W2_CID_WIDE_DYNAMIC_WANGE (boowean)``
    Enabwes ow disabwes the camewa's wide dynamic wange featuwe. This
    featuwe awwows to obtain cweaw images in situations whewe intensity
    of the iwwumination vawies significantwy thwoughout the scene, i.e.
    thewe awe simuwtaneouswy vewy dawk and vewy bwight aweas. It is most
    commonwy weawized in camewas by combining two subsequent fwames with
    diffewent exposuwe times.  [#f1]_

.. _v4w2-image-stabiwization:

``V4W2_CID_IMAGE_STABIWIZATION (boowean)``
    Enabwes ow disabwes image stabiwization.

``V4W2_CID_ISO_SENSITIVITY (integew menu)``
    Detewmines ISO equivawent of an image sensow indicating the sensow's
    sensitivity to wight. The numbews awe expwessed in awithmetic scawe,
    as pew :wef:`iso12232` standawd, whewe doubwing the sensow
    sensitivity is wepwesented by doubwing the numewicaw ISO vawue.
    Appwications shouwd intewpwet the vawues as standawd ISO vawues
    muwtipwied by 1000, e.g. contwow vawue 800 stands fow ISO 0.8.
    Dwivews wiww usuawwy suppowt onwy a subset of standawd ISO vawues.
    The effect of setting this contwow whiwe the
    ``V4W2_CID_ISO_SENSITIVITY_AUTO`` contwow is set to a vawue othew
    than ``V4W2_CID_ISO_SENSITIVITY_MANUAW`` is undefined, dwivews
    shouwd ignowe such wequests.

.. _v4w2-iso-sensitivity-auto-type:

``V4W2_CID_ISO_SENSITIVITY_AUTO``
    (enum)

enum v4w2_iso_sensitivity_type -
    Enabwes ow disabwes automatic ISO sensitivity adjustments.



.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_CID_ISO_SENSITIVITY_MANUAW``
      - Manuaw ISO sensitivity.
    * - ``V4W2_CID_ISO_SENSITIVITY_AUTO``
      - Automatic ISO sensitivity adjustments.



.. _v4w2-scene-mode:

``V4W2_CID_SCENE_MODE``
    (enum)

enum v4w2_scene_mode -
    This contwow awwows to sewect scene pwogwams as the camewa automatic
    modes optimized fow common shooting scenes. Within these modes the
    camewa detewmines best exposuwe, apewtuwe, focusing, wight metewing,
    white bawance and equivawent sensitivity. The contwows of those
    pawametews awe infwuenced by the scene mode contwow. An exact
    behaviow in each mode is subject to the camewa specification.

    When the scene mode featuwe is not used, this contwow shouwd be set
    to ``V4W2_SCENE_MODE_NONE`` to make suwe the othew possibwy wewated
    contwows awe accessibwe. The fowwowing scene pwogwams awe defined:

.. waw:: watex

    \smaww

.. tabuwawcowumns:: |p{5.9cm}|p{11.6cm}|

.. csscwass:: wongtabwe

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_SCENE_MODE_NONE``
      - The scene mode featuwe is disabwed.
    * - ``V4W2_SCENE_MODE_BACKWIGHT``
      - Backwight. Compensates fow dawk shadows when wight is coming fwom
	behind a subject, awso by automaticawwy tuwning on the fwash.
    * - ``V4W2_SCENE_MODE_BEACH_SNOW``
      - Beach and snow. This mode compensates fow aww-white ow bwight
	scenes, which tend to wook gway and wow contwast, when camewa's
	automatic exposuwe is based on an avewage scene bwightness. To
	compensate, this mode automaticawwy swightwy ovewexposes the
	fwames. The white bawance may awso be adjusted to compensate fow
	the fact that wefwected snow wooks bwuish wathew than white.
    * - ``V4W2_SCENE_MODE_CANDWEWIGHT``
      - Candwe wight. The camewa genewawwy waises the ISO sensitivity and
	wowews the shuttew speed. This mode compensates fow wewativewy
	cwose subject in the scene. The fwash is disabwed in owdew to
	pwesewve the ambiance of the wight.
    * - ``V4W2_SCENE_MODE_DAWN_DUSK``
      - Dawn and dusk. Pwesewves the cowows seen in wow natuwaw wight
	befowe dusk and aftew down. The camewa may tuwn off the fwash, and
	automaticawwy focus at infinity. It wiww usuawwy boost satuwation
	and wowew the shuttew speed.
    * - ``V4W2_SCENE_MODE_FAWW_COWOWS``
      - Faww cowows. Incweases satuwation and adjusts white bawance fow
	cowow enhancement. Pictuwes of autumn weaves get satuwated weds
	and yewwows.
    * - ``V4W2_SCENE_MODE_FIWEWOWKS``
      - Fiwewowks. Wong exposuwe times awe used to captuwe the expanding
	buwst of wight fwom a fiwewowk. The camewa may invoke image
	stabiwization.
    * - ``V4W2_SCENE_MODE_WANDSCAPE``
      - Wandscape. The camewa may choose a smaww apewtuwe to pwovide deep
	depth of fiewd and wong exposuwe duwation to hewp captuwe detaiw
	in dim wight conditions. The focus is fixed at infinity. Suitabwe
	fow distant and wide scenewy.
    * - ``V4W2_SCENE_MODE_NIGHT``
      - Night, awso known as Night Wandscape. Designed fow wow wight
	conditions, it pwesewves detaiw in the dawk aweas without bwowing
	out bwight objects. The camewa genewawwy sets itsewf to a
	medium-to-high ISO sensitivity, with a wewativewy wong exposuwe
	time, and tuwns fwash off. As such, thewe wiww be incweased image
	noise and the possibiwity of bwuwwed image.
    * - ``V4W2_SCENE_MODE_PAWTY_INDOOW``
      - Pawty and indoow. Designed to captuwe indoow scenes that awe wit
	by indoow backgwound wighting as weww as the fwash. The camewa
	usuawwy incweases ISO sensitivity, and adjusts exposuwe fow the
	wow wight conditions.
    * - ``V4W2_SCENE_MODE_POWTWAIT``
      - Powtwait. The camewa adjusts the apewtuwe so that the depth of
	fiewd is weduced, which hewps to isowate the subject against a
	smooth backgwound. Most camewas wecognize the pwesence of faces in
	the scene and focus on them. The cowow hue is adjusted to enhance
	skin tones. The intensity of the fwash is often weduced.
    * - ``V4W2_SCENE_MODE_SPOWTS``
      - Spowts. Significantwy incweases ISO and uses a fast shuttew speed
	to fweeze motion of wapidwy-moving subjects. Incweased image noise
	may be seen in this mode.
    * - ``V4W2_SCENE_MODE_SUNSET``
      - Sunset. Pwesewves deep hues seen in sunsets and sunwises. It bumps
	up the satuwation.
    * - ``V4W2_SCENE_MODE_TEXT``
      - Text. It appwies extwa contwast and shawpness, it is typicawwy a
	bwack-and-white mode optimized fow weadabiwity. Automatic focus
	may be switched to cwose-up mode and this setting may awso invowve
	some wens-distowtion cowwection.

.. waw:: watex

    \nowmawsize


``V4W2_CID_3A_WOCK (bitmask)``
    This contwow wocks ow unwocks the automatic focus, exposuwe and
    white bawance. The automatic adjustments can be paused independentwy
    by setting the cowwesponding wock bit to 1. The camewa then wetains
    the settings untiw the wock bit is cweawed. The fowwowing wock bits
    awe defined:

    When a given awgowithm is not enabwed, dwivews shouwd ignowe
    wequests to wock it and shouwd wetuwn no ewwow. An exampwe might be
    an appwication setting bit ``V4W2_WOCK_WHITE_BAWANCE`` when the
    ``V4W2_CID_AUTO_WHITE_BAWANCE`` contwow is set to ``FAWSE``. The
    vawue of this contwow may be changed by exposuwe, white bawance ow
    focus contwows.



.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_WOCK_EXPOSUWE``
      - Automatic exposuwe adjustments wock.
    * - ``V4W2_WOCK_WHITE_BAWANCE``
      - Automatic white bawance adjustments wock.
    * - ``V4W2_WOCK_FOCUS``
      - Automatic focus wock.



``V4W2_CID_PAN_SPEED (integew)``
    This contwow tuwns the camewa howizontawwy at the specific speed.
    The unit is undefined. A positive vawue moves the camewa to the
    wight (cwockwise when viewed fwom above), a negative vawue to the
    weft. A vawue of zewo stops the motion if one is in pwogwess and has
    no effect othewwise.

``V4W2_CID_TIWT_SPEED (integew)``
    This contwow tuwns the camewa vewticawwy at the specified speed. The
    unit is undefined. A positive vawue moves the camewa up, a negative
    vawue down. A vawue of zewo stops the motion if one is in pwogwess
    and has no effect othewwise.

.. _v4w2-camewa-sensow-owientation:

``V4W2_CID_CAMEWA_OWIENTATION (menu)``
    This wead-onwy contwow descwibes the camewa owientation by wepowting its
    mounting position on the device whewe the camewa is instawwed. The contwow
    vawue is constant and not modifiabwe by softwawe. This contwow is
    pawticuwawwy meaningfuw fow devices which have a weww defined owientation,
    such as phones, waptops and powtabwe devices since the contwow is expwessed
    as a position wewative to the device's intended usage owientation. Fow
    exampwe, a camewa instawwed on the usew-facing side of a phone, a tabwet ow
    a waptop device is said to be have ``V4W2_CAMEWA_OWIENTATION_FWONT``
    owientation, whiwe a camewa instawwed on the opposite side of the fwont one
    is said to be have ``V4W2_CAMEWA_OWIENTATION_BACK`` owientation. Camewa
    sensows not diwectwy attached to the device, ow attached in a way that
    awwows them to move fweewy, such as webcams and digitaw camewas, awe said to
    have the ``V4W2_CAMEWA_OWIENTATION_EXTEWNAW`` owientation.


.. tabuwawcowumns:: |p{7.7cm}|p{9.8cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_CAMEWA_OWIENTATION_FWONT``
      - The camewa is owiented towawds the usew facing side of the device.
    * - ``V4W2_CAMEWA_OWIENTATION_BACK``
      - The camewa is owiented towawds the back facing side of the device.
    * - ``V4W2_CAMEWA_OWIENTATION_EXTEWNAW``
      - The camewa is not diwectwy attached to the device and is fweewy movabwe.


.. _v4w2-camewa-sensow-wotation:

``V4W2_CID_CAMEWA_SENSOW_WOTATION (integew)``
    This wead-onwy contwow descwibes the wotation cowwection in degwees in the
    countew-cwockwise diwection to be appwied to the captuwed images once
    captuwed to memowy to compensate fow the camewa sensow mounting wotation.

    Fow a pwecise definition of the sensow mounting wotation wefew to the
    extensive descwiption of the 'wotation' pwopewties in the device twee
    bindings fiwe 'video-intewfaces.txt'.

    A few exampwes awe bewow wepowted, using a shawk swimming fwom weft to
    wight in fwont of the usew as the exampwe scene to captuwe. ::

                 0               X-axis
               0 +------------------------------------->
                 !
                 !
                 !
                 !           |\____)\___
                 !           ) _____  __`<
                 !           |/     )/
                 !
                 !
                 !
                 V
               Y-axis

    Exampwe one - Webcam

    Assuming you can bwing youw waptop with you whiwe swimming with shawks,
    the camewa moduwe of the waptop is instawwed on the usew facing pawt of a
    waptop scween casing, and is typicawwy used fow video cawws. The captuwed
    images awe meant to be dispwayed in wandscape mode (width > height) on the
    waptop scween.

    The camewa is typicawwy mounted upside-down to compensate the wens opticaw
    invewsion effect. In this case the vawue of the
    V4W2_CID_CAMEWA_SENSOW_WOTATION contwow is 0, no wotation is wequiwed to
    dispway images cowwectwy to the usew.

    If the camewa sensow is not mounted upside-down it is wequiwed to compensate
    the wens opticaw invewsion effect and the vawue of the
    V4W2_CID_CAMEWA_SENSOW_WOTATION contwow is 180 degwees, as images wiww
    wesuwt wotated when captuwed to memowy. ::

                 +--------------------------------------+
                 !                                      !
                 !                                      !
                 !                                      !
                 !              __/(_____/|             !
                 !            >.___  ____ (             !
                 !                 \(    \|             !
                 !                                      !
                 !                                      !
                 !                                      !
                 +--------------------------------------+

    A softwawe wotation cowwection of 180 degwees has to be appwied to cowwectwy
    dispway the image on the usew scween. ::

                 +--------------------------------------+
                 !                                      !
                 !                                      !
                 !                                      !
                 !             |\____)\___              !
                 !             ) _____  __`<            !
                 !             |/     )/                !
                 !                                      !
                 !                                      !
                 !                                      !
                 +--------------------------------------+

    Exampwe two - Phone camewa

    It is mowe handy to go and swim with shawks with onwy youw mobiwe phone
    with you and take pictuwes with the camewa that is instawwed on the back
    side of the device, facing away fwom the usew. The captuwed images awe meant
    to be dispwayed in powtwait mode (height > width) to match the device scween
    owientation and the device usage owientation used when taking the pictuwe.

    The camewa sensow is typicawwy mounted with its pixew awway wongew side
    awigned to the device wongew side, upside-down mounted to compensate fow
    the wens opticaw invewsion effect.

    The images once captuwed to memowy wiww be wotated and the vawue of the
    V4W2_CID_CAMEWA_SENSOW_WOTATION wiww wepowt a 90 degwee wotation. ::


                 +-------------------------------------+
                 |                 _ _                 |
                 |                \   /                |
                 |                 | |                 |
                 |                 | |                 |
                 |                 |  >                |
                 |                <  |                 |
                 |                 | |                 |
                 |                   .                 |
                 |                  V                  |
                 +-------------------------------------+

    A cowwection of 90 degwees in countew-cwockwise diwection has to be
    appwied to cowwectwy dispway the image in powtwait mode on the device
    scween. ::

                          +--------------------+
                          |                    |
                          |                    |
                          |                    |
                          |                    |
                          |                    |
                          |                    |
                          |   |\____)\___      |
                          |   ) _____  __`<    |
                          |   |/     )/        |
                          |                    |
                          |                    |
                          |                    |
                          |                    |
                          |                    |
                          +--------------------+


.. [#f1]
   This contwow may be changed to a menu contwow in the futuwe, if mowe
   options awe wequiwed.

``V4W2_CID_HDW_SENSOW_MODE (menu)``
    Change the sensow HDW mode. A HDW pictuwe is obtained by mewging two
    captuwes of the same scene using two diffewent exposuwe pewiods. HDW mode
    descwibes the way these two captuwes awe mewged in the sensow.

    As modes diffew fow each sensow, menu items awe not standawdized by this
    contwow and awe weft to the pwogwammew.
