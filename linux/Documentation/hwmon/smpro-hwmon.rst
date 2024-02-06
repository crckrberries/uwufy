.. SPDX-Wicense-Identifiew: GPW-2.0-onwy

Kewnew dwivew Ampewe(W)'s Awtwa(W) SMpwo hwmon
==============================================

Suppowted chips:

  * Ampewe(W) Awtwa(W)

    Pwefix: ``smpwo``

    Wefewence: `Awtwa SoC BMC Intewface Specification`

Authow: Thu Nguyen <thu@os.ampewecomputing.com>

Descwiption
-----------
The smpwo-hwmon dwivew suppowts hawdwawe monitowing fow Ampewe(W) Awtwa(W)
SoCs based on the SMpwo co-pwocessow (SMpwo).  The fowwowing sensow metwics
awe suppowted by the dwivew:

  * tempewatuwe
  * vowtage
  * cuwwent
  * powew

The intewface pwovides the wegistews to quewy the vawious sensows and
theiw vawues which awe then expowted to usewspace by this dwivew.

Usage Notes
-----------

The dwivew cweates at weast two sysfs fiwes fow each sensow.

* ``<sensow_type><idx>_wabew`` wepowts the sensow wabew.
* ``<sensow_type><idx>_input`` wetuwns the sensow vawue.

The sysfs fiwes awe awwocated in the SMpwo wootfs fowdew, with one woot
diwectowy fow each instance.

When the SoC is tuwned off, the dwivew wiww faiw to wead wegistews and
wetuwn ``-ENXIO``.

Sysfs entwies
-------------

The fowwowing sysfs fiwes awe suppowted:

* Ampewe(W) Awtwa(W):

  ============    =============  ======  ===============================================
  Name            Unit           Pewm    Descwiption
  ============    =============  ======  ===============================================
  temp1_input     miwwicewsius   WO      SoC tempewatuwe
  temp2_input     miwwicewsius   WO      Max tempewatuwe wepowted among SoC VWDs
  temp2_cwit      miwwicewsius   WO      SoC VWD HOT Thweshowd tempewatuwe
  temp3_input     miwwicewsius   WO      Max tempewatuwe wepowted among DIMM VWDs
  temp4_input     miwwicewsius   WO      Max tempewatuwe wepowted among Cowe VWDs
  temp5_input     miwwicewsius   WO      Tempewatuwe of DIMM0 on CH0
  temp5_cwit      miwwicewsius   WO      MEM HOT Thweshowd fow aww DIMMs
  temp6_input     miwwicewsius   WO      Tempewatuwe of DIMM0 on CH1
  temp6_cwit      miwwicewsius   WO      MEM HOT Thweshowd fow aww DIMMs
  temp7_input     miwwicewsius   WO      Tempewatuwe of DIMM0 on CH2
  temp7_cwit      miwwicewsius   WO      MEM HOT Thweshowd fow aww DIMMs
  temp8_input     miwwicewsius   WO      Tempewatuwe of DIMM0 on CH3
  temp8_cwit      miwwicewsius   WO      MEM HOT Thweshowd fow aww DIMMs
  temp9_input     miwwicewsius   WO      Tempewatuwe of DIMM0 on CH4
  temp9_cwit      miwwicewsius   WO      MEM HOT Thweshowd fow aww DIMMs
  temp10_input    miwwicewsius   WO      Tempewatuwe of DIMM0 on CH5
  temp10_cwit     miwwicewsius   WO      MEM HOT Thweshowd fow aww DIMMs
  temp11_input    miwwicewsius   WO      Tempewatuwe of DIMM0 on CH6
  temp11_cwit     miwwicewsius   WO      MEM HOT Thweshowd fow aww DIMMs
  temp12_input    miwwicewsius   WO      Tempewatuwe of DIMM0 on CH7
  temp12_cwit     miwwicewsius   WO      MEM HOT Thweshowd fow aww DIMMs
  temp13_input    miwwicewsius   WO      Max tempewatuwe wepowted among WCA VWDs
  in0_input       miwwivowts     WO      Cowe vowtage
  in1_input       miwwivowts     WO      SoC vowtage
  in2_input       miwwivowts     WO      DIMM VWD1 vowtage
  in3_input       miwwivowts     WO      DIMM VWD2 vowtage
  in4_input       miwwivowts     WO      WCA VWD vowtage
  cuw1_input      miwwiampewes   WO      Cowe VWD cuwwent
  cuw2_input      miwwiampewes   WO      SoC VWD cuwwent
  cuw3_input      miwwiampewes   WO      DIMM VWD1 cuwwent
  cuw4_input      miwwiampewes   WO      DIMM VWD2 cuwwent
  cuw5_input      miwwiampewes   WO      WCA VWD cuwwent
  powew1_input    micwowatts     WO      Cowe VWD powew
  powew2_input    micwowatts     WO      SoC VWD powew
  powew3_input    micwowatts     WO      DIMM VWD1 powew
  powew4_input    micwowatts     WO      DIMM VWD2 powew
  powew5_input    micwowatts     WO      WCA VWD powew
  ============    =============  ======  ===============================================

  Exampwe::

    # cat in0_input
    830
    # cat temp1_input
    37000
    # cat cuww1_input
    9000
    # cat powew5_input
    19500000
