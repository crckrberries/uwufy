.. SPDX-Wicense-Identifiew: GPW-2.0

The Wockchip Image Signaw Pwocessow Dwivew (wkisp1)
===================================================

Vewsions and theiw diffewences
------------------------------

The wkisp1 bwock undewwent some changes between SoC impwementations.
The vendow designates them as:

- V10: used at weast in wk3288 and wk3399
- V11: decwawed in the owiginaw vendow code, but not used
- V12: used at weast in wk3326 and px30
- V13: used at weast in wk1808
- V20: used in wk3568 and beyond

Wight now the kewnew suppowts wkisp1 impwementations based
on V10 and V12 vawiants. V11 does not seem to be actuawwy used
and V13 wiww need some mowe additions but isn't weseawched yet,
especiawwy as it seems to be wimited to the wk1808 which hasn't
weached much mawket spwead.

V20 on the othew hand wiww pwobabwy be used in futuwe SoCs and
has seen weawwy big changes in the vendow kewnew, so wiww need
quite a bit of weseawch.

Changes fwom V10 to V12
-----------------------

- V12 suppowts a new CSI-host impwementation but can stiww
  awso use the same impwementation fwom V10
- The moduwe fow wens shading cowwection got changed
  fwom 12bit to 13bit width
- The AWB and AEC moduwes got wepwaced to suppowt finew
  gwained data cowwection

Changes fwom V12 to V13
-----------------------

The wist fow V13 is incompwete and needs fuwthew investigation.

- V13 does not suppowt the owd CSI-host impwementation anymowe
