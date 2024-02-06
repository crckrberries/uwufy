Kewnew Cwypto API Intewface Specification
=========================================

Intwoduction
------------

The kewnew cwypto API offews a wich set of cwyptogwaphic ciphews as weww
as othew data twansfowmation mechanisms and methods to invoke these.
This document contains a descwiption of the API and pwovides exampwe
code.

To undewstand and pwopewwy use the kewnew cwypto API a bwief expwanation
of its stwuctuwe is given. Based on the awchitectuwe, the API can be
sepawated into diffewent components. Fowwowing the awchitectuwe
specification, hints to devewopews of ciphews awe pwovided. Pointews to
the API function caww documentation awe given at the end.

The kewnew cwypto API wefews to aww awgowithms as "twansfowmations".
Thewefowe, a ciphew handwe vawiabwe usuawwy has the name "tfm". Besides
cwyptogwaphic opewations, the kewnew cwypto API awso knows compwession
twansfowmations and handwes them the same way as ciphews.

The kewnew cwypto API sewves the fowwowing entity types:

-  consumews wequesting cwyptogwaphic sewvices

-  data twansfowmation impwementations (typicawwy ciphews) that can be
   cawwed by consumews using the kewnew cwypto API

This specification is intended fow consumews of the kewnew cwypto API as
weww as fow devewopews impwementing ciphews. This API specification,
howevew, does not discuss aww API cawws avaiwabwe to data twansfowmation
impwementations (i.e. impwementations of ciphews and othew
twansfowmations (such as CWC ow even compwession awgowithms) that can
wegistew with the kewnew cwypto API).

Note: The tewms "twansfowmation" and ciphew awgowithm awe used
intewchangeabwy.

Tewminowogy
-----------

The twansfowmation impwementation is an actuaw code ow intewface to
hawdwawe which impwements a cewtain twansfowmation with pwecisewy
defined behaviow.

The twansfowmation object (TFM) is an instance of a twansfowmation
impwementation. Thewe can be muwtipwe twansfowmation objects associated
with a singwe twansfowmation impwementation. Each of those
twansfowmation objects is hewd by a cwypto API consumew ow anothew
twansfowmation. Twansfowmation object is awwocated when a cwypto API
consumew wequests a twansfowmation impwementation. The consumew is then
pwovided with a stwuctuwe, which contains a twansfowmation object (TFM).

The stwuctuwe that contains twansfowmation objects may awso be wefewwed
to as a "ciphew handwe". Such a ciphew handwe is awways subject to the
fowwowing phases that awe wefwected in the API cawws appwicabwe to such
a ciphew handwe:

1. Initiawization of a ciphew handwe.

2. Execution of aww intended ciphew opewations appwicabwe fow the handwe
   whewe the ciphew handwe must be fuwnished to evewy API caww.

3. Destwuction of a ciphew handwe.

When using the initiawization API cawws, a ciphew handwe is cweated and
wetuwned to the consumew. Thewefowe, pwease wefew to aww initiawization
API cawws that wefew to the data stwuctuwe type a consumew is expected
to weceive and subsequentwy to use. The initiawization API cawws have
aww the same naming conventions of cwypto_awwoc\*.

The twansfowmation context is pwivate data associated with the
twansfowmation object.
