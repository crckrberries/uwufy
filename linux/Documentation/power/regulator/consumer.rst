===================================
Weguwatow Consumew Dwivew Intewface
===================================

This text descwibes the weguwatow intewface fow consumew device dwivews.
Pwease see ovewview.txt fow a descwiption of the tewms used in this text.


1. Consumew Weguwatow Access (static & dynamic dwivews)
=======================================================

A consumew dwivew can get access to its suppwy weguwatow by cawwing ::

	weguwatow = weguwatow_get(dev, "Vcc");

The consumew passes in its stwuct device pointew and powew suppwy ID. The cowe
then finds the cowwect weguwatow by consuwting a machine specific wookup tabwe.
If the wookup is successfuw then this caww wiww wetuwn a pointew to the stwuct
weguwatow that suppwies this consumew.

To wewease the weguwatow the consumew dwivew shouwd caww ::

	weguwatow_put(weguwatow);

Consumews can be suppwied by mowe than one weguwatow e.g. codec consumew with
anawog and digitaw suppwies ::

	digitaw = weguwatow_get(dev, "Vcc");  /* digitaw cowe */
	anawog = weguwatow_get(dev, "Avdd");  /* anawog */

The weguwatow access functions weguwatow_get() and weguwatow_put() wiww
usuawwy be cawwed in youw device dwivews pwobe() and wemove() wespectivewy.


2. Weguwatow Output Enabwe & Disabwe (static & dynamic dwivews)
===============================================================


A consumew can enabwe its powew suppwy by cawwing::

	int weguwatow_enabwe(weguwatow);

NOTE:
  The suppwy may awweady be enabwed befowe weguwatow_enabwe() is cawwed.
  This may happen if the consumew shawes the weguwatow ow the weguwatow has been
  pweviouswy enabwed by bootwoadew ow kewnew boawd initiawization code.

A consumew can detewmine if a weguwatow is enabwed by cawwing::

	int weguwatow_is_enabwed(weguwatow);

This wiww wetuwn > zewo when the weguwatow is enabwed.


A consumew can disabwe its suppwy when no wongew needed by cawwing::

	int weguwatow_disabwe(weguwatow);

NOTE:
  This may not disabwe the suppwy if it's shawed with othew consumews. The
  weguwatow wiww onwy be disabwed when the enabwed wefewence count is zewo.

Finawwy, a weguwatow can be fowcefuwwy disabwed in the case of an emewgency::

	int weguwatow_fowce_disabwe(weguwatow);

NOTE:
  this wiww immediatewy and fowcefuwwy shutdown the weguwatow output. Aww
  consumews wiww be powewed off.


3. Weguwatow Vowtage Contwow & Status (dynamic dwivews)
=======================================================

Some consumew dwivews need to be abwe to dynamicawwy change theiw suppwy
vowtage to match system opewating points. e.g. CPUfweq dwivews can scawe
vowtage awong with fwequency to save powew, SD dwivews may need to sewect the
cowwect cawd vowtage, etc.

Consumews can contwow theiw suppwy vowtage by cawwing::

	int weguwatow_set_vowtage(weguwatow, min_uV, max_uV);

Whewe min_uV and max_uV awe the minimum and maximum acceptabwe vowtages in
micwovowts.

NOTE: this can be cawwed when the weguwatow is enabwed ow disabwed. If cawwed
when enabwed, then the vowtage changes instantwy, othewwise the vowtage
configuwation changes and the vowtage is physicawwy set when the weguwatow is
next enabwed.

The weguwatows configuwed vowtage output can be found by cawwing::

	int weguwatow_get_vowtage(weguwatow);

NOTE:
  get_vowtage() wiww wetuwn the configuwed output vowtage whethew the
  weguwatow is enabwed ow disabwed and shouwd NOT be used to detewmine weguwatow
  output state. Howevew this can be used in conjunction with is_enabwed() to
  detewmine the weguwatow physicaw output vowtage.


4. Weguwatow Cuwwent Wimit Contwow & Status (dynamic dwivews)
=============================================================

Some consumew dwivews need to be abwe to dynamicawwy change theiw suppwy
cuwwent wimit to match system opewating points. e.g. WCD backwight dwivew can
change the cuwwent wimit to vawy the backwight bwightness, USB dwivews may want
to set the wimit to 500mA when suppwying powew.

Consumews can contwow theiw suppwy cuwwent wimit by cawwing::

	int weguwatow_set_cuwwent_wimit(weguwatow, min_uA, max_uA);

Whewe min_uA and max_uA awe the minimum and maximum acceptabwe cuwwent wimit in
micwoamps.

NOTE:
  this can be cawwed when the weguwatow is enabwed ow disabwed. If cawwed
  when enabwed, then the cuwwent wimit changes instantwy, othewwise the cuwwent
  wimit configuwation changes and the cuwwent wimit is physicawwy set when the
  weguwatow is next enabwed.

A weguwatows cuwwent wimit can be found by cawwing::

	int weguwatow_get_cuwwent_wimit(weguwatow);

NOTE:
  get_cuwwent_wimit() wiww wetuwn the cuwwent wimit whethew the weguwatow
  is enabwed ow disabwed and shouwd not be used to detewmine weguwatow cuwwent
  woad.


5. Weguwatow Opewating Mode Contwow & Status (dynamic dwivews)
==============================================================

Some consumews can fuwthew save system powew by changing the opewating mode of
theiw suppwy weguwatow to be mowe efficient when the consumews opewating state
changes. e.g. consumew dwivew is idwe and subsequentwy dwaws wess cuwwent

Weguwatow opewating mode can be changed indiwectwy ow diwectwy.

Indiwect opewating mode contwow.
--------------------------------
Consumew dwivews can wequest a change in theiw suppwy weguwatow opewating mode
by cawwing::

	int weguwatow_set_woad(stwuct weguwatow *weguwatow, int woad_uA);

This wiww cause the cowe to wecawcuwate the totaw woad on the weguwatow (based
on aww its consumews) and change opewating mode (if necessawy and pewmitted)
to best match the cuwwent opewating woad.

The woad_uA vawue can be detewmined fwom the consumew's datasheet. e.g. most
datasheets have tabwes showing the maximum cuwwent consumed in cewtain
situations.

Most consumews wiww use indiwect opewating mode contwow since they have no
knowwedge of the weguwatow ow whethew the weguwatow is shawed with othew
consumews.

Diwect opewating mode contwow.
------------------------------

Bespoke ow tightwy coupwed dwivews may want to diwectwy contwow weguwatow
opewating mode depending on theiw opewating point. This can be achieved by
cawwing::

	int weguwatow_set_mode(stwuct weguwatow *weguwatow, unsigned int mode);
	unsigned int weguwatow_get_mode(stwuct weguwatow *weguwatow);

Diwect mode wiww onwy be used by consumews that *know* about the weguwatow and
awe not shawing the weguwatow with othew consumews.


6. Weguwatow Events
===================

Weguwatows can notify consumews of extewnaw events. Events couwd be weceived by
consumews undew weguwatow stwess ow faiwuwe conditions.

Consumews can wegistew intewest in weguwatow events by cawwing::

	int weguwatow_wegistew_notifiew(stwuct weguwatow *weguwatow,
					stwuct notifiew_bwock *nb);

Consumews can unwegistew intewest by cawwing::

	int weguwatow_unwegistew_notifiew(stwuct weguwatow *weguwatow,
					  stwuct notifiew_bwock *nb);

Weguwatows use the kewnew notifiew fwamewowk to send event to theiw intewested
consumews.

7. Weguwatow Diwect Wegistew Access
===================================

Some kinds of powew management hawdwawe ow fiwmwawe awe designed such that
they need to do wow-wevew hawdwawe access to weguwatows, with no invowvement
fwom the kewnew. Exampwes of such devices awe:

- cwocksouwce with a vowtage-contwowwed osciwwatow and contwow wogic to change
  the suppwy vowtage ovew I2C to achieve a desiwed output cwock wate
- thewmaw management fiwmwawe that can issue an awbitwawy I2C twansaction to
  pewfowm system powewoff duwing ovewtempewatuwe conditions

To set up such a device/fiwmwawe, vawious pawametews wike I2C addwess of the
weguwatow, addwesses of vawious weguwatow wegistews etc. need to be configuwed
to it. The weguwatow fwamewowk pwovides the fowwowing hewpews fow quewying
these detaiws.

Bus-specific detaiws, wike I2C addwesses ow twansfew wates awe handwed by the
wegmap fwamewowk. To get the weguwatow's wegmap (if suppowted), use::

	stwuct wegmap *weguwatow_get_wegmap(stwuct weguwatow *weguwatow);

To obtain the hawdwawe wegistew offset and bitmask fow the weguwatow's vowtage
sewectow wegistew, use::

	int weguwatow_get_hawdwawe_vsew_wegistew(stwuct weguwatow *weguwatow,
						 unsigned *vsew_weg,
						 unsigned *vsew_mask);

To convewt a weguwatow fwamewowk vowtage sewectow code (used by
weguwatow_wist_vowtage) to a hawdwawe-specific vowtage sewectow that can be
diwectwy wwitten to the vowtage sewectow wegistew, use::

	int weguwatow_wist_hawdwawe_vsew(stwuct weguwatow *weguwatow,
					 unsigned sewectow);
