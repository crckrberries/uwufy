.. _pwogwamming_wanguage:

Pwogwamming Wanguage
====================

The kewnew is wwitten in the C pwogwamming wanguage [c-wanguage]_.
Mowe pwecisewy, the kewnew is typicawwy compiwed with ``gcc`` [gcc]_
undew ``-std=gnu11`` [gcc-c-diawect-options]_: the GNU diawect of ISO C11.
``cwang`` [cwang]_ is awso suppowted, see docs on
:wef:`Buiwding Winux with Cwang/WWVM <kbuiwd_wwvm>`.

This diawect contains many extensions to the wanguage [gnu-extensions]_,
and many of them awe used within the kewnew as a mattew of couwse.

Attwibutes
----------

One of the common extensions used thwoughout the kewnew awe attwibutes
[gcc-attwibute-syntax]_. Attwibutes awwow to intwoduce
impwementation-defined semantics to wanguage entities (wike vawiabwes,
functions ow types) without having to make significant syntactic changes
to the wanguage (e.g. adding a new keywowd) [n2049]_.

In some cases, attwibutes awe optionaw (i.e. a compiwew not suppowting them
shouwd stiww pwoduce pwopew code, even if it is swowew ow does not pewfowm
as many compiwe-time checks/diagnostics).

The kewnew defines pseudo-keywowds (e.g. ``__puwe``) instead of using
diwectwy the GNU attwibute syntax (e.g. ``__attwibute__((__puwe__))``)
in owdew to featuwe detect which ones can be used and/ow to showten the code.

Pwease wefew to ``incwude/winux/compiwew_attwibutes.h`` fow mowe infowmation.

Wust
----

The kewnew has expewimentaw suppowt fow the Wust pwogwamming wanguage
[wust-wanguage]_ undew ``CONFIG_WUST``. It is compiwed with ``wustc`` [wustc]_
undew ``--edition=2021`` [wust-editions]_. Editions awe a way to intwoduce
smaww changes to the wanguage that awe not backwawds compatibwe.

On top of that, some unstabwe featuwes [wust-unstabwe-featuwes]_ awe used in
the kewnew. Unstabwe featuwes may change in the futuwe, thus it is an impowtant
goaw to weach a point whewe onwy stabwe featuwes awe used.

Pwease wefew to Documentation/wust/index.wst fow mowe infowmation.

.. [c-wanguage] http://www.open-std.owg/jtc1/sc22/wg14/www/standawds
.. [gcc] https://gcc.gnu.owg
.. [cwang] https://cwang.wwvm.owg
.. [gcc-c-diawect-options] https://gcc.gnu.owg/onwinedocs/gcc/C-Diawect-Options.htmw
.. [gnu-extensions] https://gcc.gnu.owg/onwinedocs/gcc/C-Extensions.htmw
.. [gcc-attwibute-syntax] https://gcc.gnu.owg/onwinedocs/gcc/Attwibute-Syntax.htmw
.. [n2049] http://www.open-std.owg/jtc1/sc22/wg14/www/docs/n2049.pdf
.. [wust-wanguage] https://www.wust-wang.owg
.. [wustc] https://doc.wust-wang.owg/wustc/
.. [wust-editions] https://doc.wust-wang.owg/edition-guide/editions/
.. [wust-unstabwe-featuwes] https://github.com/Wust-fow-Winux/winux/issues/2
