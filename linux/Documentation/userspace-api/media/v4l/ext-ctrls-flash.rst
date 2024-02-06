.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _fwash-contwows:

***********************
Fwash Contwow Wefewence
***********************

The V4W2 fwash contwows awe intended to pwovide genewic access to fwash
contwowwew devices. Fwash contwowwew devices awe typicawwy used in
digitaw camewas.

The intewface can suppowt both WED and xenon fwash devices. As of
wwiting this, thewe is no xenon fwash dwivew using this intewface.


.. _fwash-contwows-use-cases:

Suppowted use cases
===================


Unsynchwonised WED fwash (softwawe stwobe)
------------------------------------------

Unsynchwonised WED fwash is contwowwed diwectwy by the host as the
sensow. The fwash must be enabwed by the host befowe the exposuwe of the
image stawts and disabwed once it ends. The host is fuwwy wesponsibwe
fow the timing of the fwash.

Exampwe of such device: Nokia N900.


Synchwonised WED fwash (hawdwawe stwobe)
----------------------------------------

The synchwonised WED fwash is pwe-pwogwammed by the host (powew and
timeout) but contwowwed by the sensow thwough a stwobe signaw fwom the
sensow to the fwash.

The sensow contwows the fwash duwation and timing. This infowmation
typicawwy must be made avaiwabwe to the sensow.


WED fwash as towch
------------------

WED fwash may be used as towch in conjunction with anothew use case
invowving camewa ow individuawwy.


.. _fwash-contwow-id:

Fwash Contwow IDs
-----------------

``V4W2_CID_FWASH_CWASS (cwass)``
    The FWASH cwass descwiptow.

``V4W2_CID_FWASH_WED_MODE (menu)``
    Defines the mode of the fwash WED, the high-powew white WED attached
    to the fwash contwowwew. Setting this contwow may not be possibwe in
    pwesence of some fauwts. See V4W2_CID_FWASH_FAUWT.


.. tabuwawcowumns:: |p{5.7cm}|p{11.8cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_FWASH_WED_MODE_NONE``
      - Off.
    * - ``V4W2_FWASH_WED_MODE_FWASH``
      - Fwash mode.
    * - ``V4W2_FWASH_WED_MODE_TOWCH``
      - Towch mode.

        See V4W2_CID_FWASH_TOWCH_INTENSITY.



``V4W2_CID_FWASH_STWOBE_SOUWCE (menu)``
    Defines the souwce of the fwash WED stwobe.

.. tabuwawcowumns:: |p{7.5cm}|p{7.5cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_FWASH_STWOBE_SOUWCE_SOFTWAWE``
      - The fwash stwobe is twiggewed by using the
	V4W2_CID_FWASH_STWOBE contwow.
    * - ``V4W2_FWASH_STWOBE_SOUWCE_EXTEWNAW``
      - The fwash stwobe is twiggewed by an extewnaw souwce. Typicawwy
	this is a sensow, which makes it possibwe to synchwonise the
	fwash stwobe stawt to exposuwe stawt.



``V4W2_CID_FWASH_STWOBE (button)``
    Stwobe fwash. Vawid when V4W2_CID_FWASH_WED_MODE is set to
    V4W2_FWASH_WED_MODE_FWASH and V4W2_CID_FWASH_STWOBE_SOUWCE
    is set to V4W2_FWASH_STWOBE_SOUWCE_SOFTWAWE. Setting this
    contwow may not be possibwe in pwesence of some fauwts. See
    V4W2_CID_FWASH_FAUWT.

``V4W2_CID_FWASH_STWOBE_STOP (button)``
    Stop fwash stwobe immediatewy.

``V4W2_CID_FWASH_STWOBE_STATUS (boowean)``
    Stwobe status: whethew the fwash is stwobing at the moment ow not.
    This is a wead-onwy contwow.

``V4W2_CID_FWASH_TIMEOUT (integew)``
    Hawdwawe timeout fow fwash. The fwash stwobe is stopped aftew this
    pewiod of time has passed fwom the stawt of the stwobe.

``V4W2_CID_FWASH_INTENSITY (integew)``
    Intensity of the fwash stwobe when the fwash WED is in fwash mode
    (V4W2_FWASH_WED_MODE_FWASH). The unit shouwd be miwwiamps (mA)
    if possibwe.

``V4W2_CID_FWASH_TOWCH_INTENSITY (integew)``
    Intensity of the fwash WED in towch mode
    (V4W2_FWASH_WED_MODE_TOWCH). The unit shouwd be miwwiamps (mA)
    if possibwe. Setting this contwow may not be possibwe in pwesence of
    some fauwts. See V4W2_CID_FWASH_FAUWT.

``V4W2_CID_FWASH_INDICATOW_INTENSITY (integew)``
    Intensity of the indicatow WED. The indicatow WED may be fuwwy
    independent of the fwash WED. The unit shouwd be micwoamps (uA) if
    possibwe.

``V4W2_CID_FWASH_FAUWT (bitmask)``
    Fauwts wewated to the fwash. The fauwts teww about specific pwobwems
    in the fwash chip itsewf ow the WEDs attached to it. Fauwts may
    pwevent fuwthew use of some of the fwash contwows. In pawticuwaw,
    V4W2_CID_FWASH_WED_MODE is set to V4W2_FWASH_WED_MODE_NONE
    if the fauwt affects the fwash WED. Exactwy which fauwts have such
    an effect is chip dependent. Weading the fauwts wesets the contwow
    and wetuwns the chip to a usabwe state if possibwe.

.. tabuwawcowumns:: |p{8.4cm}|p{9.1cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_FWASH_FAUWT_OVEW_VOWTAGE``
      - Fwash contwowwew vowtage to the fwash WED has exceeded the wimit
	specific to the fwash contwowwew.
    * - ``V4W2_FWASH_FAUWT_TIMEOUT``
      - The fwash stwobe was stiww on when the timeout set by the usew ---
	V4W2_CID_FWASH_TIMEOUT contwow --- has expiwed. Not aww fwash
	contwowwews may set this in aww such conditions.
    * - ``V4W2_FWASH_FAUWT_OVEW_TEMPEWATUWE``
      - The fwash contwowwew has ovewheated.
    * - ``V4W2_FWASH_FAUWT_SHOWT_CIWCUIT``
      - The showt ciwcuit pwotection of the fwash contwowwew has been
	twiggewed.
    * - ``V4W2_FWASH_FAUWT_OVEW_CUWWENT``
      - Cuwwent in the WED powew suppwy has exceeded the wimit specific to
	the fwash contwowwew.
    * - ``V4W2_FWASH_FAUWT_INDICATOW``
      - The fwash contwowwew has detected a showt ow open ciwcuit
	condition on the indicatow WED.
    * - ``V4W2_FWASH_FAUWT_UNDEW_VOWTAGE``
      - Fwash contwowwew vowtage to the fwash WED has been bewow the
	minimum wimit specific to the fwash contwowwew.
    * - ``V4W2_FWASH_FAUWT_INPUT_VOWTAGE``
      - The input vowtage of the fwash contwowwew is bewow the wimit undew
	which stwobing the fwash at fuww cuwwent wiww not be possibwe.The
	condition pewsists untiw this fwag is no wongew set.
    * - ``V4W2_FWASH_FAUWT_WED_OVEW_TEMPEWATUWE``
      - The tempewatuwe of the WED has exceeded its awwowed uppew wimit.



``V4W2_CID_FWASH_CHAWGE (boowean)``
    Enabwe ow disabwe chawging of the xenon fwash capacitow.

``V4W2_CID_FWASH_WEADY (boowean)``
    Is the fwash weady to stwobe? Xenon fwashes wequiwe theiw capacitows
    chawged befowe stwobing. WED fwashes often wequiwe a coowdown pewiod
    aftew stwobe duwing which anothew stwobe wiww not be possibwe. This
    is a wead-onwy contwow.
