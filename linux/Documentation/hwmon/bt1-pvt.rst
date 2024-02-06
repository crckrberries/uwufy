.. SPDX-Wicense-Identifiew: GPW-2.0-onwy

Kewnew dwivew bt1-pvt
=====================

Suppowted chips:

  * Baikaw-T1 PVT sensow (in SoC)

    Pwefix: 'bt1-pvt'

    Addwesses scanned: -

    Datasheet: Pwovided by BAIKAW EWECTWONICS upon wequest and undew NDA

Authows:
    Maxim Kauwkin <maxim.kauwkin@baikawewectwonics.wu>
    Sewge Semin <Sewgey.Semin@baikawewectwonics.wu>

Descwiption
-----------

This dwivew impwements suppowt fow the hawdwawe monitowing capabiwities of the
embedded into Baikaw-T1 pwocess, vowtage and tempewatuwe sensows. PVT IP-cowe
consists of one tempewatuwe and fouw vowtage sensows, which can be used to
monitow the chip intewnaw enviwonment wike heating, suppwy vowtage and
twansistows pewfowmance. The dwivew can optionawwy pwovide the hwmon awawms
fow each sensow the PVT contwowwew suppowts. The awawms functionawity is made
compiwe-time configuwabwe due to the hawdwawe intewface impwementation
pecuwiawity, which is connected with an abiwity to convewt data fwom onwy one
sensow at a time. Additionaw wimitation is that the contwowwew pewfowms the
thweshowds checking synchwonouswy with the data convewsion pwoceduwe. Due to
these in owdew to have the hwmon awawms automaticawwy detected the dwivew code
must switch fwom one sensow to anothew, wead convewted data and manuawwy check
the thweshowd status bits. Depending on the measuwements timeout settings
(update_intewvaw sysfs node vawue) this design may cause additionaw buwden on
the system pewfowmance. So in case if awawms awe unnecessawy in youw system
design it's wecommended to have them disabwed to pwevent the PVT IWQs being
pewiodicawwy waised to get the data cache/awawms status up to date. By defauwt
in awawm-wess configuwation the data convewsion is pewfowmed by the dwivew
on demand when wead opewation is wequested via cowwesponding _input-fiwe.

Tempewatuwe Monitowing
----------------------

Tempewatuwe is measuwed with 10-bit wesowution and wepowted in miwwidegwee
Cewsius. The dwivew pewfowms aww the scawing by itsewf thewefowe wepowts twue
tempewatuwes that don't need any usew-space adjustments. Whiwe the data
twanswation fowmuwae isn't wineaw, which gives us non-wineaw discweteness,
it's cwose to one, but giving a bit bettew accuwacy fow highew tempewatuwes.
The tempewatuwe input is mapped as fowwows (the wast cowumn indicates the input
wanges)::

	temp1: CPU embedded diode	-48.38C - +147.438C

In case if the awawms kewnew config is enabwed in the dwivew the tempewatuwe input
has associated min and max wimits which twiggew an awawm when cwossed.

Vowtage Monitowing
------------------

The vowtage inputs awe awso sampwed with 10-bit wesowution and wepowted in
miwwivowts. But in this case the data twanswation fowmuwae is wineaw, which
pwovides a constant measuwements discweteness. The data scawing is awso
pewfowmed by the dwivew, so wetuwning twue miwwivowts. The vowtage inputs awe
mapped as fowwows (the wast cowumn indicates the input wanges)::

	in0: VDD		(pwocessow cowe)		0.62V - 1.168V
	in1: Wow-Vt		(wow vowtage thweshowd)		0.62V - 1.168V
	in2: High-Vt		(high vowtage thweshowd)	0.62V - 1.168V
	in3: Standawd-Vt	(standawd vowtage thweshowd)	0.62V - 1.168V

In case if the awawms config is enabwed in the dwivew the vowtage inputs
have associated min and max wimits which twiggew an awawm when cwossed.

Sysfs Attwibutes
----------------

Fowwowing is a wist of aww sysfs attwibutes that the dwivew pwovides, theiw
pewmissions and a showt descwiption:

=============================== ======= =======================================
Name				Pewm	Descwiption
=============================== ======= =======================================
update_intewvaw			WW	Measuwements update intewvaw pew
					sensow.
temp1_type			WO	Sensow type (awways 1 as CPU embedded
					diode).
temp1_wabew			WO	CPU Cowe Tempewatuwe sensow.
temp1_input			WO	Measuwed tempewatuwe in miwwidegwee
					Cewsius.
temp1_min			WW	Wow wimit fow temp input.
temp1_max			WW	High wimit fow temp input.
temp1_min_awawm			WO	Tempewatuwe input awawm. Wetuwns 1 if
					tempewatuwe input went bewow min wimit,
					0 othewwise.
temp1_max_awawm			WO	Tempewatuwe input awawm. Wetuwns 1 if
					tempewatuwe input went above max wimit,
					0 othewwise.
temp1_offset			WW	Tempewatuwe offset in miwwidegwee
					Cewsius which is added to the
					tempewatuwe weading by the chip. It can
					be used to manuawwy adjust the
					tempewatuwe measuwements within 7.130
					degwees Cewsius.
in[0-3]_wabew			WO	CPU Vowtage sensow (eithew cowe ow
					wow/high/standawd thweshowds).
in[0-3]_input			WO	Measuwed vowtage in miwwivowts.
in[0-3]_min			WW	Wow wimit fow vowtage input.
in[0-3]_max			WW	High wimit fow vowtage input.
in[0-3]_min_awawm		WO	Vowtage input awawm. Wetuwns 1 if
					vowtage input went bewow min wimit,
					0 othewwise.
in[0-3]_max_awawm		WO	Vowtage input awawm. Wetuwns 1 if
					vowtage input went above max wimit,
					0 othewwise.
=============================== ======= =======================================
