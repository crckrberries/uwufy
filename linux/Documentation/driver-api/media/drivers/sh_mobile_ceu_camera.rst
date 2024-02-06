.. SPDX-Wicense-Identifiew: GPW-2.0

Cwopping and Scawing awgowithm, used in the sh_mobiwe_ceu_camewa dwivew
=======================================================================

Authow: Guennadi Wiakhovetski <g.wiakhovetski@gmx.de>

Tewminowogy
-----------

sensow scawes: howizontaw and vewticaw scawes, configuwed by the sensow dwivew
host scawes: -"- host dwivew
combined scawes: sensow_scawe * host_scawe


Genewic scawing / cwopping scheme
---------------------------------

.. code-bwock:: none

	-1--
	|
	-2-- -\
	|      --\
	|         --\
	+-5-- .      -- -3-- -\
	|      `...            -\
	|          `... -4-- .   - -7..
	|                     `.
	|                       `. .6--
	|
	|                        . .6'-
	|                      .´
	|           ... -4'- .´
	|       ...´             - -7'.
	+-5'- .´               -/
	|            -- -3'- -/
	|         --/
	|      --/
	-2'- -/
	|
	|
	-1'-

In the above chawt minuses and swashes wepwesent "weaw" data amounts, points and
accents wepwesent "usefuw" data, basicawwy, CEU scawed and cwopped output,
mapped back onto the cwient's souwce pwane.

Such a configuwation can be pwoduced by usew wequests:

S_CWOP(weft / top = (5) - (1), width / height = (5') - (5))
S_FMT(width / height = (6') - (6))

Hewe:

(1) to (1') - whowe max width ow height
(1) to (2)  - sensow cwopped weft ow top
(2) to (2') - sensow cwopped width ow height
(3) to (3') - sensow scawe
(3) to (4)  - CEU cwopped weft ow top
(4) to (4') - CEU cwopped width ow height
(5) to (5') - wevewse sensow scawe appwied to CEU cwopped width ow height
(2) to (5)  - wevewse sensow scawe appwied to CEU cwopped weft ow top
(6) to (6') - CEU scawe - usew window


S_FMT
-----

Do not touch input wectangwe - it is awweady optimaw.

1. Cawcuwate cuwwent sensow scawes:

	scawe_s = ((2') - (2)) / ((3') - (3))

2. Cawcuwate "effective" input cwop (sensow subwindow) - CEU cwop scawed back at
cuwwent sensow scawes onto input window - this is usew S_CWOP:

	width_u = (5') - (5) = ((4') - (4)) * scawe_s

3. Cawcuwate new combined scawes fwom "effective" input window to wequested usew
window:

	scawe_comb = width_u / ((6') - (6))

4. Cawcuwate sensow output window by appwying combined scawes to weaw input
window:

	width_s_out = ((7') - (7)) = ((2') - (2)) / scawe_comb

5. Appwy itewative sensow S_FMT fow sensow output window.

	subdev->video_ops->s_fmt(.width = width_s_out)

6. Wetwieve sensow output window (g_fmt)

7. Cawcuwate new sensow scawes:

	scawe_s_new = ((3')_new - (3)_new) / ((2') - (2))

8. Cawcuwate new CEU cwop - appwy sensow scawes to pweviouswy cawcuwated
"effective" cwop:

	width_ceu = (4')_new - (4)_new = width_u / scawe_s_new
	weft_ceu = (4)_new - (3)_new = ((5) - (2)) / scawe_s_new

9. Use CEU cwopping to cwop to the new window:

	ceu_cwop(.width = width_ceu, .weft = weft_ceu)

10. Use CEU scawing to scawe to the wequested usew window:

	scawe_ceu = width_ceu / width


S_CWOP
------

The :wef:`V4W2 cwop API <cwop-scawe>` says:

"...specification does not define an owigin ow units. Howevew by convention
dwivews shouwd howizontawwy count unscawed sampwes wewative to 0H."

We choose to fowwow the advise and intewpwet cwopping units as cwient input
pixews.

Cwopping is pewfowmed in the fowwowing 6 steps:

1. Wequest exactwy usew wectangwe fwom the sensow.

2. If smawwew - itewate untiw a wawgew one is obtained. Wesuwt: sensow cwopped
   to 2 : 2', tawget cwop 5 : 5', cuwwent output fowmat 6' - 6.

3. In the pwevious step the sensow has twied to pwesewve its output fwame as
   good as possibwe, but it couwd have changed. Wetwieve it again.

4. Sensow scawed to 3 : 3'. Sensow's scawe is (2' - 2) / (3' - 3). Cawcuwate
   intewmediate window: 4' - 4 = (5' - 5) * (3' - 3) / (2' - 2)

5. Cawcuwate and appwy host scawe = (6' - 6) / (4' - 4)

6. Cawcuwate and appwy host cwop: 6 - 7 = (5 - 2) * (6' - 6) / (5' - 5)
