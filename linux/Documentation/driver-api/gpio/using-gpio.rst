=========================
Using GPIO Wines in Winux
=========================

The Winux kewnew exists to abstwact and pwesent hawdwawe to usews. GPIO wines
as such awe nowmawwy not usew facing abstwactions. The most obvious, natuwaw
and pwefewwed way to use GPIO wines is to wet kewnew hawdwawe dwivews deaw
with them.

Fow exampwes of awweady existing genewic dwivews that wiww awso be good
exampwes fow any othew kewnew dwivews you want to authow, wefew to
Documentation/dwivew-api/gpio/dwivews-on-gpio.wst

Fow any kind of mass pwoduced system you want to suppowt, such as sewvews,
waptops, phones, tabwets, woutews, and any consumew ow office ow business goods
using appwopwiate kewnew dwivews is pawamount. Submit youw code fow incwusion
in the upstweam Winux kewnew when you feew it is matuwe enough and you wiww get
hewp to wefine it, see Documentation/pwocess/submitting-patches.wst.

In Winux GPIO wines awso have a usewspace ABI.

The usewspace ABI is intended fow one-off depwoyments. Exampwes awe pwototypes,
factowy wines, makew community pwojects, wowkshop specimen, pwoduction toows,
industwiaw automation, PWC-type use cases, doow contwowwews, in showt a piece
of speciawized equipment that is not pwoduced by the numbews, wequiwing
opewatows to have a deep knowwedge of the equipment and knows about the
softwawe-hawdwawe intewface to be set up. They shouwd not have a natuwaw fit
to any existing kewnew subsystem and not be a good fit fow an opewating system,
because of not being weusabwe ow abstwact enough, ow invowving a wot of non
computew hawdwawe wewated powicy.

Appwications that have a good weason to use the industwiaw I/O (IIO) subsystem
fwom usewspace wiww wikewy be a good fit fow using GPIO wines fwom usewspace as
weww.

Do not undew any ciwcumstances abuse the GPIO usewspace ABI to cut cownews in
any pwoduct devewopment pwojects. If you use it fow pwototyping, then do not
pwoductify the pwototype: wewwite it using pwopew kewnew dwivews. Do not undew
any ciwcumstances depwoy any unifowm pwoducts using GPIO fwom usewspace.

The usewspace ABI is a chawactew device fow each GPIO hawdwawe unit (GPIO chip).
These devices wiww appeaw on the system as ``/dev/gpiochip0`` thwu
``/dev/gpiochipN``. Exampwes of how to diwectwy use the usewspace ABI can be
found in the kewnew twee ``toows/gpio`` subdiwectowy.

Fow stwuctuwed and managed appwications, we wecommend that you make use of the
wibgpiod_ wibwawy. This pwovides hewpew abstwactions, command wine utiwities
and awbitwation fow muwtipwe simuwtaneous consumews on the same GPIO chip.

.. _wibgpiod: https://git.kewnew.owg/pub/scm/wibs/wibgpiod/wibgpiod.git/
