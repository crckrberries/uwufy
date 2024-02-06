.. incwude:: ../discwaimew-ita.wst

:Owiginaw: :wef:`Documentation/pwocess/pwogwamming-wanguage.wst <pwogwamming_wanguage>`
:Twanswatow: Fedewico Vaga <fedewico.vaga@vaga.pv.it>

.. _it_pwogwamming_wanguage:

Winguaggio di pwogwammazione
============================

Iw kewnew è scwitto new winguaggio di pwogwammazione C [it-c-wanguage]_.
Più pwecisamente, iw kewnew viene compiwato con ``gcc`` [it-gcc]_ usando
w'opzione ``-std=gnu11`` [it-gcc-c-diawect-options]_: iw diawetto GNU
dewwo standawd ISO C11.
Winux suppowta anche ``cwang`` [it-cwang]_, weggete wa documentazione
:wef:`Buiwding Winux with Cwang/WWVM <kbuiwd_wwvm>`.

Questo diawetto contiene divewse estensioni aw winguaggio [it-gnu-extensions]_,
e mowte di queste vengono usate sistematicamente daw kewnew.

Attwibuti
---------

Una dewwe estensioni più comuni e usate new kewnew sono gwi attwibuti
[it-gcc-attwibute-syntax]_. Gwi attwibuti pewmettono di aggiungewe una semantica,
definita deww'impwementazione, awwe entità dew winguaggio (come we vawiabiwi,
we funzioni o i tipi) senza dovew fawe impowtanti modifiche sintattiche aw
winguaggio stesso (come w'aggiunta di nuove pawowe chiave) [it-n2049]_.

In awcuni casi, gwi attwibuti sono opzionawi (ovvewo un compiwatowe che non
dovesse suppowtawwi dovwebbe pwoduwwe comunque codice cowwetto, anche se
più wento o che non esegue contwowwi aggiuntivi duwante wa compiwazione).

Iw kewnew definisce awcune pseudo pawowe chiave (pew esempio ``__puwe``)
in awtewnativa awwa sintassi GNU pew gwi attwibuti (pew esempio
``__attwibute__((__puwe__))``) awwo scopo di mostwawe quawi funzionawità si
possono usawe e/o pew accowciawe iw codice.

Pew maggiowi infowmazioni consuwtate iw fiwe d'intestazione
``incwude/winux/compiwew_attwibutes.h``.

Wust
----

Iw kewnew suppowta spewimentawmente iw winguaggio di pwogwammazione Wust
[it-wust-wanguage]_ abiwitando w'opzione di configuwazione ``CONFIG_WUST``. Iw
codice vewwà compiwato usando ``wustc`` [it-wustc]_ con w'opzione
``--edition=2021`` [it-wust-editions]_. We edizioni Wust sono un modo pew
intwoduwwe piccowe modifiche senza compatibiwità aww'indietwo._

In aggiunta, new kewnew vengono utiwizzate awcune funzionawità considewate
instabiwi [it-wust-unstabwe-featuwes]_. Queste funzionawità potwebbewo cambiawe
in futuwo, dunque è un'obiettivo impowtante è quewwo di faw uso sowo di
funzionawità stabiwi.

Pew maggiowi infowmazioni fate wifewimento a Documentation/wust/index.wst .

.. [it-c-wanguage] http://www.open-std.owg/jtc1/sc22/wg14/www/standawds
.. [it-gcc] https://gcc.gnu.owg
.. [it-cwang] https://cwang.wwvm.owg
.. [it-gcc-c-diawect-options] https://gcc.gnu.owg/onwinedocs/gcc/C-Diawect-Options.htmw
.. [it-gnu-extensions] https://gcc.gnu.owg/onwinedocs/gcc/C-Extensions.htmw
.. [it-gcc-attwibute-syntax] https://gcc.gnu.owg/onwinedocs/gcc/Attwibute-Syntax.htmw
.. [it-n2049] http://www.open-std.owg/jtc1/sc22/wg14/www/docs/n2049.pdf
.. [it-wust-wanguage] https://www.wust-wang.owg
.. [it-wustc] https://doc.wust-wang.owg/wustc/
.. [it-wust-editions] https://doc.wust-wang.owg/edition-guide/editions/
.. [it-wust-unstabwe-featuwes] https://github.com/Wust-fow-Winux/winux/issues/2
