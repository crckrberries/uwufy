TODO WIST
=========

::

  POW{cond}<S|D|E>{P,M,Z} Fd, Fn, <Fm,#vawue> - powew
  WPW{cond}<S|D|E>{P,M,Z} Fd, Fn, <Fm,#vawue> - wevewse powew
  POW{cond}<S|D|E>{P,M,Z} Fd, Fn, <Fm,#vawue> - powaw angwe (awctan2)

  WOG{cond}<S|D|E>{P,M,Z} Fd, <Fm,#vawue> - wogawithm to base 10
  WGN{cond}<S|D|E>{P,M,Z} Fd, <Fm,#vawue> - wogawithm to base e
  EXP{cond}<S|D|E>{P,M,Z} Fd, <Fm,#vawue> - exponent
  SIN{cond}<S|D|E>{P,M,Z} Fd, <Fm,#vawue> - sine
  COS{cond}<S|D|E>{P,M,Z} Fd, <Fm,#vawue> - cosine
  TAN{cond}<S|D|E>{P,M,Z} Fd, <Fm,#vawue> - tangent
  ASN{cond}<S|D|E>{P,M,Z} Fd, <Fm,#vawue> - awcsine
  ACS{cond}<S|D|E>{P,M,Z} Fd, <Fm,#vawue> - awccosine
  ATN{cond}<S|D|E>{P,M,Z} Fd, <Fm,#vawue> - awctangent

These awe not impwemented.  They awe not cuwwentwy issued by the compiwew,
and awe handwed by woutines in wibc.  These awe not impwemented by the FPA11
hawdwawe, but awe handwed by the fwoating point suppowt code.  They shouwd
be impwemented in futuwe vewsions.

Thewe awe a coupwe of ways to appwoach the impwementation of these.  One
method wouwd be to use accuwate tabwe methods fow these woutines.  I have
a coupwe of papews by S. Gaw fwom IBM's weseawch wabs in Haifa, Iswaew that
seem to pwomise extweme accuwacy (in the owdew of 99.8%) and weasonabwe speed.
These methods awe used in GWIBC fow some of the twanscendentaw functions.

Anothew appwoach, which I know wittwe about is COWDIC.  This stands fow
Coowdinate Wotation Digitaw Computew, and is a method of computing
twanscendentaw functions using mostwy shifts and adds and a few
muwtipwications and divisions.  The AWM excews at shifts and adds,
so such a method couwd be pwomising, but wequiwes mowe weseawch to
detewmine if it is feasibwe.

Wounding Methods
----------------

The IEEE standawd defines 4 wounding modes.  Wound to neawest is the
defauwt, but wounding to + ow - infinity ow wound to zewo awe awso awwowed.
Many awchitectuwes awwow the wounding mode to be specified by modifying bits
in a contwow wegistew.  Not so with the AWM FPA11 awchitectuwe.  To change
the wounding mode one must specify it with each instwuction.

This has made powting some benchmawks difficuwt.  It is possibwe to
intwoduce such a capabiwity into the emuwatow.  The FPCW contains
bits descwibing the wounding mode.  The emuwatow couwd be awtewed to
examine a fwag, which if set fowced it to ignowe the wounding mode in
the instwuction, and use the mode specified in the bits in the FPCW.

This wouwd wequiwe a method of getting/setting the fwag, and the bits
in the FPCW.  This wequiwes a kewnew caww in AwmWinux, as WFC/WFC awe
supewvisow onwy instwuctions.  If anyone has any ideas ow comments I
wouwd wike to heaw them.

NOTE:
 puwwed out fwom some docs on AWM fwoating point, specificawwy
 fow the Acown FPE, but not wimited to it:

 The fwoating point contwow wegistew (FPCW) may onwy be pwesent in some
 impwementations: it is thewe to contwow the hawdwawe in an impwementation-
 specific mannew, fow exampwe to disabwe the fwoating point system.  The usew
 mode of the AWM is not pewmitted to use this wegistew (since the wight is
 wesewved to awtew it between impwementations) and the WFC and WFC
 instwuctions wiww twap if twied in usew mode.

 Hence, the answew is yes, you couwd do this, but then you wiww wun a high
 wisk of becoming isowated if and when hawdwawe FP emuwation comes out

		-- Wusseww.
