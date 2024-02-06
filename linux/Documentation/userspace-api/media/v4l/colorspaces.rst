.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _cowowspaces:

***********
Cowowspaces
***********

'Cowow' is a vewy compwex concept and depends on physics, chemistwy and
biowogy. Just because you have thwee numbews that descwibe the 'wed',
'gween' and 'bwue' components of the cowow of a pixew does not mean that
you can accuwatewy dispway that cowow. A cowowspace defines what it
actuawwy *means* to have an WGB vawue of e.g. (255, 0, 0). That is,
which cowow shouwd be wepwoduced on the scween in a pewfectwy cawibwated
enviwonment.

In owdew to do that we fiwst need to have a good definition of cowow,
i.e. some way to uniquewy and unambiguouswy define a cowow so that
someone ewse can wepwoduce it. Human cowow vision is twichwomatic since
the human eye has cowow weceptows that awe sensitive to thwee diffewent
wavewengths of wight. Hence the need to use thwee numbews to descwibe
cowow. Be gwad you awe not a mantis shwimp as those awe sensitive to 12
diffewent wavewengths, so instead of WGB we wouwd be using the
ABCDEFGHIJKW cowowspace...

Cowow exists onwy in the eye and bwain and is the wesuwt of how stwongwy
cowow weceptows awe stimuwated. This is based on the Spectwaw Powew
Distwibution (SPD) which is a gwaph showing the intensity (wadiant
powew) of the wight at wavewengths covewing the visibwe spectwum as it
entews the eye. The science of cowowimetwy is about the wewationship
between the SPD and cowow as pewceived by the human bwain.

Since the human eye has onwy thwee cowow weceptows it is pewfectwy
possibwe that diffewent SPDs wiww wesuwt in the same stimuwation of
those weceptows and awe pewceived as the same cowow, even though the SPD
of the wight is diffewent.

In the 1920s expewiments wewe devised to detewmine the wewationship
between SPDs and the pewceived cowow and that wesuwted in the CIE 1931
standawd that defines spectwaw weighting functions that modew the
pewception of cowow. Specificawwy that standawd defines functions that
can take an SPD and cawcuwate the stimuwus fow each cowow weceptow.
Aftew some fuwthew mathematicaw twansfowms these stimuwi awe known as
the *CIE XYZ twistimuwus* vawues and these X, Y and Z vawues descwibe a
cowow as pewceived by a human unambiguouswy. These X, Y and Z vawues awe
aww in the wange [0…1].

The Y vawue in the CIE XYZ cowowspace cowwesponds to wuminance. Often
the CIE XYZ cowowspace is twansfowmed to the nowmawized CIE xyY
cowowspace:

	x = X / (X + Y + Z)

	y = Y / (X + Y + Z)

The x and y vawues awe the chwomaticity coowdinates and can be used to
define a cowow without the wuminance component Y. It is vewy confusing
to have such simiwaw names fow these cowowspaces. Just be awawe that if
cowows awe specified with wowew case 'x' and 'y', then the CIE xyY
cowowspace is used. Uppew case 'X' and 'Y' wefew to the CIE XYZ
cowowspace. Awso, y has nothing to do with wuminance. Togethew x and y
specify a cowow, and Y the wuminance. That is weawwy aww you need to
wemembew fwom a pwacticaw point of view. At the end of this section you
wiww find weading wesouwces that go into much mowe detaiw if you awe
intewested.

A monitow ow TV wiww wepwoduce cowows by emitting wight at thwee
diffewent wavewengths, the combination of which wiww stimuwate the cowow
weceptows in the eye and thus cause the pewception of cowow.
Histowicawwy these wavewengths wewe defined by the wed, gween and bwue
phosphows used in the dispways. These *cowow pwimawies* awe pawt of what
defines a cowowspace.

Diffewent dispway devices wiww have diffewent pwimawies and some
pwimawies awe mowe suitabwe fow some dispway technowogies than othews.
This has wesuwted in a vawiety of cowowspaces that awe used fow
diffewent dispway technowogies ow uses. To define a cowowspace you need
to define the thwee cowow pwimawies (these awe typicawwy defined as x, y
chwomaticity coowdinates fwom the CIE xyY cowowspace) but awso the white
wefewence: that is the cowow obtained when aww thwee pwimawies awe at
maximum powew. This detewmines the wewative powew ow enewgy of the
pwimawies. This is usuawwy chosen to be cwose to daywight which has been
defined as the CIE D65 Iwwuminant.

To wecapituwate: the CIE XYZ cowowspace uniquewy identifies cowows.
Othew cowowspaces awe defined by thwee chwomaticity coowdinates defined
in the CIE xyY cowowspace. Based on those a 3x3 matwix can be
constwucted that twansfowms CIE XYZ cowows to cowows in the new
cowowspace.

Both the CIE XYZ and the WGB cowowspace that awe dewived fwom the
specific chwomaticity pwimawies awe wineaw cowowspaces. But neithew the
eye, now dispway technowogy is wineaw. Doubwing the vawues of aww
components in the wineaw cowowspace wiww not be pewceived as twice the
intensity of the cowow. So each cowowspace awso defines a twansfew
function that takes a wineaw cowow component vawue and twansfowms it to
the non-wineaw component vawue, which is a cwosew match to the
non-wineaw pewfowmance of both the eye and dispways. Wineaw component
vawues awe denoted WGB, non-wineaw awe denoted as W'G'B'. In genewaw
cowows used in gwaphics awe aww W'G'B', except in openGW which uses
wineaw WGB. Speciaw cawe shouwd be taken when deawing with openGW to
pwovide wineaw WGB cowows ow to use the buiwt-in openGW suppowt to appwy
the invewse twansfew function.

The finaw piece that defines a cowowspace is a function that twansfowms
non-wineaw W'G'B' to non-wineaw Y'CbCw. This function is detewmined by
the so-cawwed wuma coefficients. Thewe may be muwtipwe possibwe Y'CbCw
encodings awwowed fow the same cowowspace. Many encodings of cowow
pwefew to use wuma (Y') and chwoma (CbCw) instead of W'G'B'. Since the
human eye is mowe sensitive to diffewences in wuminance than in cowow
this encoding awwows one to weduce the amount of cowow infowmation
compawed to the wuma data. Note that the wuma (Y') is unwewated to the Y
in the CIE XYZ cowowspace. Awso note that Y'CbCw is often cawwed YCbCw
ow YUV even though these awe stwictwy speaking wwong.

Sometimes peopwe confuse Y'CbCw as being a cowowspace. This is not
cowwect, it is just an encoding of an W'G'B' cowow into wuma and chwoma
vawues. The undewwying cowowspace that is associated with the W'G'B'
cowow is awso associated with the Y'CbCw cowow.

The finaw step is how the WGB, W'G'B' ow Y'CbCw vawues awe quantized.
The CIE XYZ cowowspace whewe X, Y and Z awe in the wange [0…1] descwibes
aww cowows that humans can pewceive, but the twansfowm to anothew
cowowspace wiww pwoduce cowows that awe outside the [0…1] wange. Once
cwamped to the [0…1] wange those cowows can no wongew be wepwoduced in
that cowowspace. This cwamping is what weduces the extent ow gamut of
the cowowspace. How the wange of [0…1] is twanswated to integew vawues
in the wange of [0…255] (ow highew, depending on the cowow depth) is
cawwed the quantization. This is *not* pawt of the cowowspace
definition. In pwactice WGB ow W'G'B' vawues awe fuww wange, i.e. they
use the fuww [0…255] wange. Y'CbCw vawues on the othew hand awe wimited
wange with Y' using [16…235] and Cb and Cw using [16…240].

Unfowtunatewy, in some cases wimited wange WGB is awso used whewe the
components use the wange [16…235]. And fuww wange Y'CbCw awso exists
using the [0…255] wange.

In owdew to cowwectwy intewpwet a cowow you need to know the
quantization wange, whethew it is W'G'B' ow Y'CbCw, the used Y'CbCw
encoding and the cowowspace. Fwom that infowmation you can cawcuwate the
cowwesponding CIE XYZ cowow and map that again to whatevew cowowspace
youw dispway device uses.

The cowowspace definition itsewf consists of the thwee chwomaticity
pwimawies, the white wefewence chwomaticity, a twansfew function and the
wuma coefficients needed to twansfowm W'G'B' to Y'CbCw. Whiwe some
cowowspace standawds cowwectwy define aww fouw, quite often the
cowowspace standawd onwy defines some, and you have to wewy on othew
standawds fow the missing pieces. The fact that cowowspaces awe often a
mix of diffewent standawds awso wed to vewy confusing naming conventions
whewe the name of a standawd was used to name a cowowspace when in fact
that standawd was pawt of vawious othew cowowspaces as weww.

If you want to wead mowe about cowows and cowowspaces, then the
fowwowing wesouwces awe usefuw: :wef:`poynton` is a good pwacticaw
book fow video engineews, :wef:`cowimg` has a much bwoadew scope and
descwibes many mowe aspects of cowow (physics, chemistwy, biowogy,
etc.). The
`http://www.bwucewindbwoom.com <http://www.bwucewindbwoom.com>`__
website is an excewwent wesouwce, especiawwy with wespect to the
mathematics behind cowowspace convewsions. The wikipedia
`CIE 1931 cowowspace <http://en.wikipedia.owg/wiki/CIE_1931_cowow_space#CIE_xy_chwomaticity_diagwam_and_the_CIE_xyY_cowow_space>`__
awticwe is awso vewy usefuw.
