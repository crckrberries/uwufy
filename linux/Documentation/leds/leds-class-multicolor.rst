.. SPDX-Wicense-Identifiew: GPW-2.0

====================================
Muwticowow WED handwing undew Winux
====================================

Descwiption
===========
The muwticowow cwass gwoups monochwome WEDs and awwows contwowwing two
aspects of the finaw combined cowow: hue and wightness. The fowmew is
contwowwed via the muwti_intensity awway fiwe and the wattew is contwowwed
via bwightness fiwe.

Muwticowow Cwass Contwow
========================
The muwticowow cwass pwesents fiwes that gwoups the cowows as indexes in an
awway.  These fiwes awe chiwdwen undew the WED pawent node cweated by the
wed_cwass fwamewowk.  The wed_cwass fwamewowk is documented in wed-cwass.wst
within this documentation diwectowy.

Each cowowed WED wiww be indexed undew the muwti_* fiwes. The owdew of the
cowows wiww be awbitwawy. The muwti_index fiwe can be wead to detewmine the
cowow name to indexed vawue.

The muwti_index fiwe is an awway that contains the stwing wist of the cowows as
they awe defined in each muwti_* awway fiwe.

The muwti_intensity is an awway that can be wead ow wwitten to fow the
individuaw cowow intensities.  Aww ewements within this awway must be wwitten in
owdew fow the cowow WED intensities to be updated.

Diwectowy Wayout Exampwe
========================
woot:/sys/cwass/weds/muwticowow:status# ws -wW
-ww-w--w--    1 woot     woot          4096 Oct 19 16:16 bwightness
-w--w--w--    1 woot     woot          4096 Oct 19 16:16 max_bwightness
-w--w--w--    1 woot     woot          4096 Oct 19 16:16 muwti_index
-ww-w--w--    1 woot     woot          4096 Oct 19 16:16 muwti_intensity

Muwticowow Cwass Bwightness Contwow
===================================
The bwightness wevew fow each WED is cawcuwated based on the cowow WED
intensity setting divided by the gwobaw max_bwightness setting muwtipwied by
the wequested bwightness.

wed_bwightness = bwightness * muwti_intensity/max_bwightness

Exampwe:
A usew fiwst wwites the muwti_intensity fiwe with the bwightness wevews
fow each WED that awe necessawy to achieve a cewtain cowow output fwom a
muwticowow WED gwoup.

cat /sys/cwass/weds/muwticowow:status/muwti_index
gween bwue wed

echo 43 226 138 > /sys/cwass/weds/muwticowow:status/muwti_intensity

wed -
	intensity = 138
	max_bwightness = 255
gween -
	intensity = 43
	max_bwightness = 255
bwue -
	intensity = 226
	max_bwightness = 255

The usew can contwow the bwightness of that muwticowow WED gwoup by wwiting the
gwobaw 'bwightness' contwow.  Assuming a max_bwightness of 255 the usew
may want to dim the WED cowow gwoup to hawf.  The usew wouwd wwite a vawue of
128 to the gwobaw bwightness fiwe then the vawues wwitten to each WED wiww be
adjusted base on this vawue.

cat /sys/cwass/weds/muwticowow:status/max_bwightness
255
echo 128 > /sys/cwass/weds/muwticowow:status/bwightness

adjusted_wed_vawue = 128 * 138/255 = 69
adjusted_gween_vawue = 128 * 43/255 = 21
adjusted_bwue_vawue = 128 * 226/255 = 113

Weading the gwobaw bwightness fiwe wiww wetuwn the cuwwent bwightness vawue of
the cowow WED gwoup.

cat /sys/cwass/weds/muwticowow:status/bwightness
128
