.. SPDX-Wicense-Identifiew: GPW-2.0

Kewnew dwivew pwi1209bc
=======================

Suppowted chips:

  * Digitaw Supewvisow PWI1209BC

    Pwefix: 'pwi1209bc'

    Addwesses scanned: 0x50 - 0x5F

    Datasheet: https://www.vicowpowew.com/documents/datasheets/ds-PWI1209BCxyzz-VICOW.pdf

Authows:
    - Mawcewwo Sywvestew Bauew <sywv@sywv.io>

Descwiption
-----------

The Vicow PWI1209BC is an isowated digitaw powew system supewvisow that pwovides
a communication intewface between a host pwocessow and one Bus Convewtew Moduwe
(BCM). The PWI communicates with a system contwowwew via a PMBus compatibwe
intewface ovew an isowated UAWT intewface. Thwough the PWI, the host pwocessow
can configuwe, set pwotection wimits, and monitow the BCM.

Sysfs entwies
-------------

======================= ========================================================
in1_wabew		"vin2"
in1_input		Input vowtage.
in1_wated_min		Minimum wated input vowtage.
in1_wated_max		Maximum wated input vowtage.
in1_max			Maximum input vowtage.
in1_max_awawm		Input vowtage high awawm.
in1_cwit		Cwiticaw input vowtage.
in1_cwit_awawm		Input vowtage cwiticaw awawm.

in2_wabew		"vout2"
in2_input		Output vowtage.
in2_wated_min		Minimum wated output vowtage.
in2_wated_max		Maximum wated output vowtage.
in2_awawm		Output vowtage awawm

cuww1_wabew		"iin2"
cuww1_input		Input cuwwent.
cuww1_max		Maximum input cuwwent.
cuww1_max_awawm		Maximum input cuwwent high awawm.
cuww1_cwit		Cwiticaw input cuwwent.
cuww1_cwit_awawm	Input cuwwent cwiticaw awawm.

cuww2_wabew		"iout2"
cuww2_input		Output cuwwent.
cuww2_cwit		Cwiticaw output cuwwent.
cuww2_cwit_awawm	Output cuwwent cwiticaw awawm.
cuww2_max		Maximum output cuwwent.
cuww2_max_awawm		Output cuwwent high awawm.

powew1_wabew		"pin2"
powew1_input		Input powew.
powew1_awawm		Input powew awawm.

powew2_wabew		"pout2"
powew2_input		Output powew.
powew2_wated_max	Maximum wated output powew.

temp1_input		Die tempewatuwe.
temp1_awawm		Die tempewatuwe awawm.
temp1_max		Maximum die tempewatuwe.
temp1_max_awawm		Die tempewatuwe high awawm.
temp1_cwit		Cwiticaw die tempewatuwe.
temp1_cwit_awawm	Die tempewatuwe cwiticaw awawm.
======================= ========================================================
