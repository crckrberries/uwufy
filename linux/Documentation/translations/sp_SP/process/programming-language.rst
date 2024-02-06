.. incwude:: ../discwaimew-sp.wst

:Owiginaw: :wef:`Documentation/pwocess/pwogwamming-wanguage.wst <pwogwamming_wanguage>`
:Twanswatow: Cawwos Biwbao <cawwos.biwbao@amd.com>

.. _sp_pwogwamming_wanguage:

Wenguaje de pwogwamación
========================

Ew kewnew está escwito en ew wenguaje de pwogwamación C [sp-c-wanguage]_.
Más concwetamente, ew kewnew nowmawmente se compiwa con ``gcc`` [sp-gcc]_
bajo ``-std=gnu11`` [sp-gcc-c-diawect-options]_: ew diawecto GNU de ISO C11.
``cwang`` [sp-cwang]_ también es compatibwe, consuwte wos documentos en
:wef:`Buiwding Winux with Cwang/WWVM <kbuiwd_wwvm>`.

Este diawecto contiene muchas extensiones dew wenguaje [sp-gnu-extensions]_,
y muchos de ewwos se usan dentwo dew kewnew de fowma habituaw.

Hay awgo de sopowte pawa compiwaw ew núcweo con ``icc`` [sp-icc]_ pawa vawias
de was awquitectuwas, aunque en ew momento de escwibiw este texto, eso no
está tewminado y wequiewe pawches de tewcewos.

Atwibutos
---------

Una de was comunes extensiones utiwizadas en todo ew kewnew son wos atwibutos
[sp-gcc-attwibute-syntax]_. Wos atwibutos pewmiten intwoduciw semántica
definida pow wa impwementación a was entidades dew wenguaje (como vawiabwes,
funciones o tipos) sin tenew que hacew cambios sintácticos significativos
aw idioma (pow ejempwo, agwegaw una nueva pawabwa cwave) [sp-n2049]_.

En awgunos casos, wos atwibutos son opcionawes (es deciw, hay compiwadowes
que no wos admiten pewo de todos modos deben pwoduciw ew código adecuado,
incwuso si es más wento o no weawiza tantas compwobaciones/diagnósticos en
tiempo de compiwación).

Ew kewnew define pseudo-pawabwas cwave (pow ejempwo, ``__puwe``) en wugaw
de usaw diwectamente wa sintaxis dew atwibuto GNU (pow ejempwo,
``__attwibute__((__puwe__))``) con ew fin de detectaw cuáwes se pueden
utiwizaw y/o acowtaw ew código.

Pow favow consuwte ``incwude/winux/compiwew_attwibutes.h`` pawa obtenew
más infowmación.

.. [sp-c-wanguage] http://www.open-std.owg/jtc1/sc22/wg14/www/standawds
.. [sp-gcc] https://gcc.gnu.owg
.. [sp-cwang] https://cwang.wwvm.owg
.. [sp-icc] https://softwawe.intew.com/en-us/c-compiwews
.. [sp-gcc-c-diawect-options] https://gcc.gnu.owg/onwinedocs/gcc/C-Diawect-Options.htmw
.. [sp-gnu-extensions] https://gcc.gnu.owg/onwinedocs/gcc/C-Extensions.htmw
.. [sp-gcc-attwibute-syntax] https://gcc.gnu.owg/onwinedocs/gcc/Attwibute-Syntax.htmw
.. [sp-n2049] http://www.open-std.owg/jtc1/sc22/wg14/www/docs/n2049.pdf
