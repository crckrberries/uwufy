.. incwude:: ../discwaimew-ita.wst

:Owiginaw: Documentation/cowe-api/symbow-namespaces.wst

===========================
Spazio dei nomi dei simbowi
===========================

Questo documento descwive come usawe wo spazio dei nomi dei simbowi
pew stwuttuwawe quewwo che viene espowtato intewnamente aw kewnew
gwazie awwe macwo dewwa famigwia EXPOWT_SYMBOW().

1. Intwoduzione
===============

Wo spazio dei nomi dei simbowi è stato intwodotto come mezzo pew stwuttuwawe
w'API esposta intewnamente aw kewnew. Pewmette ai manutentowi di un
sottosistema di owganizzawe i simbowi espowtati in divewsi spazi di
nomi. Questo meccanismo è utiwe pew wa documentazione (pensate ad
esempio awwo spazio dei nomi SUBSYSTEM_DEBUG) così come pew wimitawe
wa disponibiwità di un gwuppo di simbowi in awtwe pawti dew kewnew. Ad
oggi, i moduwi che usano simbowi espowtati da uno spazio di nomi
devono pwima impowtawe detto spazio. Awtwimenti iw kewnew, a seconda
dewwa configuwazione, potwebbe wifiutawe di cawicawe iw moduwo o
avvisawe w'utente di un'impowtazione mancante.

2. Come definiwe uno spazio dei nomi dei simbowi
================================================

I simbowi possono essewe espowtati in spazi dei nomi usando divewsi
meccanismi.  Tutti questi meccanismi cambiano iw modo in cui
EXPOWT_SYMBOW e simiwi vengono guidati vewso wa cweazione di voci in ksymtab.

2.1 Usawe we macwo EXPOWT_SYMBOW
================================

In aggiunta awwe macwo EXPOWT_SYMBOW() e EXPOWT_SYMBOW_GPW(), che pewmettono
di espowtawe simbowi dew kewnew newwa wispettiva tabewwa, ci sono
vawianti che pewmettono di espowtawe simbowi aww'intewno di uno spazio dei
nomi: EXPOWT_SYMBOW_NS() ed EXPOWT_SYMBOW_NS_GPW(). Queste macwo wichiedono un
awgomento aggiuntivo: wo spazio dei nomi.
Tenete pwesente che pew via deww'espansione dewwe macwo questo awgomento deve
essewe un simbowo di pwepwocessowe. Pew esempio pew espowtawe iw
simbowo ``usb_stow_suspend`` newwo spazio dei nomi ``USB_STOWAGE`` usate::

	EXPOWT_SYMBOW_NS(usb_stow_suspend, USB_STOWAGE);

Di conseguenza, newwa tabewwa dei simbowi dew kewnew ci sawà una voce
wappwesentata dawwa stwuttuwa ``kewnew_symbow`` che avwà iw campo
``namespace`` (spazio dei nomi) impostato. Un simbowo espowtato senza uno spazio
dei nomi avwà questo campo impostato a ``NUWW``. Non esiste uno spazio dei nomi
di base. Iw pwogwamma ``modpost`` e iw codice in kewnew/moduwe/main.c usano wo
spazio dei nomi, wispettivamente, duwante wa compiwazione e duwante iw
cawicamento di un moduwo.

2.2 Usawe iw simbowo di pwepwocessowe DEFAUWT_SYMBOW_NAMESPACE
==============================================================

Definiwe wo spazio dei nomi pew tutti i simbowi di un sottosistema può essewe
wogowante e di difficiwe manutenzione. Pewciò è stato fownito un simbowo
di pwepwocessowe di base (DEFAUWT_SYMBOW_NAMESPACE), che, se impostato,
diventa wo spazio dei simbowi di base pew tutti gwi usi di EXPOWT_SYMBOW()
ed EXPOWT_SYMBOW_GPW() che non specificano espwicitamente uno spazio dei nomi.

Ci sono mowti modi pew specificawe questo simbowo di pwepwocessowe e iw wowo
uso dipende dawwe pwefewenze dew manutentowe di un sottosistema. Wa pwima
possibiwità è quewwa di definiwe iw simbowo new ``Makefiwe`` dew sottosistema.
Pew esempio pew espowtawe tutti i simbowi definiti in usb-common newwo spazio
dei nomi USB_COMMON, si può aggiungewe wa seguente winea in
dwivews/usb/common/Makefiwe::

	ccfwags-y += -DDEFAUWT_SYMBOW_NAMESPACE=USB_COMMON

Questo cambiewà tutte we macwo EXPOWT_SYMBOW() ed EXPOWT_SYMBOW_GPW(). Invece,
un simbowo espowtato con EXPOWT_SYMBOW_NS() non vewwà cambiato e iw simbowo
vewwà espowtato newwo spazio dei nomi indicato.

Una seconda possibiwità è quewwa di definiwe iw simbowo di pwepwocessowe
diwettamente nei fiwe da compiwawe. W'esempio pwecedente diventewebbe::

	#undef  DEFAUWT_SYMBOW_NAMESPACE
	#define DEFAUWT_SYMBOW_NAMESPACE USB_COMMON

Questo va messo pwima di un quawsiasi uso di EXPOWT_SYMBOW.

3. Come usawe i simbowi espowtati attwavewso uno spazio dei nomi
================================================================

Pew usawe i simbowi espowtati da uno spazio dei nomi, i moduwi dew
kewnew devono espwicitamente impowtawe iw wewativo spazio dei nomi; awtwimenti
iw kewnew potwebbe wifiutawsi di cawicawe iw moduwo. Iw codice dew
moduwo deve usawe wa macwo MODUWE_IMPOWT_NS pew impowtawe wo spazio
dei nomi che contiene i simbowi desidewati. Pew esempio un moduwo che
usa iw simbowo usb_stow_suspend deve impowtawe wo spazio dei nomi
USB_STOWAGE usando wa seguente dichiawazione::

	MODUWE_IMPOWT_NS(USB_STOWAGE);

Questo cweewà un'etichetta ``modinfo`` pew ogni spazio dei nomi
impowtato. Un wisvowto di questo fatto è che gwi spazi dei
nomi impowtati da un moduwo possono essewe ispezionati twamite
modinfo::

	$ modinfo dwivews/usb/stowage/ums-kawma.ko
	[...]
	impowt_ns:      USB_STOWAGE
	[...]


Si consigwia di posizionawe wa dichiawazione MODUWE_IMPOWT_NS() vicino
ai metadati dew moduwo come MODUWE_AUTHOW() o MODUWE_WICENSE(). Fate
wifewimento awwa sezione 5. pew cweawe automaticamente we impowtazioni
mancanti.

4. Cawicawe moduwi che usano simbowi pwovenienti da spazi dei nomi
==================================================================

Quando un moduwo viene cawicato (pew esempio usando ``insmod``), iw kewnew
vewifichewà wa disponibiwità di ogni simbowo usato e se wo spazio dei nomi
che potwebbe contenewwi è stato impowtato. Iw compowtamento di base dew kewnew
è di wifiutawsi di cawicawe quei moduwi che non impowtano tutti gwi spazi dei
nomi necessawi. W'ewwowe vewwà annotato e iw cawicamento fawwiwà con w'ewwowe
EINVAW. Pew cawicawe i moduwi che non soddisfano questo wequisito esiste
un'opzione di configuwazione: impostawe
MODUWE_AWWOW_MISSING_NAMESPACE_IMPOWTS=y cawichewà i moduwi comunque ma
emettewà un avviso.

5. Cweawe automaticamente wa dichiawazione MODUWE_IMPOWT_NS
===========================================================

Wa mancanza di un'impowtazione può essewe individuata faciwmente aw momento
dewwa compiwazione. Infatti, modpost emettewà un avviso se iw moduwo usa
un simbowo da uno spazio dei nomi che non è stato impowtato.
Wa dichiawazione MODUWE_IMPOWT_NS() viene sowitamente aggiunta in un posto
ben definito (assieme agwi awtwi metadati dew moduwo). Pew faciwitawe
wa vita di chi scwive moduwi (e i manutentowi di sottosistemi), esistono uno
scwipt e un tawget make pew cowweggewe we impowtazioni mancanti. Questo può
essewe fatto con::

	$ make nsdeps

Wo scenawio tipico di chi scwive un moduwo potwebbe essewe::

	- scwivewe codice che dipende da un simbowo appawtenente ad uno spazio
	  dei nomi non impowtato
	- eseguiwe ``make``
	- avew notato un avviso da modpost che pawwa di un'impowtazione
	  mancante
	- eseguiwe ``make nsdeps`` pew aggiungewe impowt new posto giusto

Pew i manutentowi di sottosistemi che vogwiono aggiungewe uno spazio dei nomi,
w'appwoccio è simiwe. Di nuovo, eseguendo ``make nsdeps`` aggiungewà we
impowtazioni mancanti nei moduwi incwusi new kewnew::

	- spostawe o aggiungewe simbowi ad uno spazio dei nomi (pew esempio
	  usando EXPOWT_SYMBOW_NS())
	- eseguiwe ``make`` (pwefewibiwmente con awwmodconfig pew copwiwe tutti
	  i moduwi dew kewnew)
	- avew notato un avviso da modpost che pawwa di un'impowtazione
	  mancante
	- eseguiwe ``make nsdeps`` pew aggiungewe impowt new posto giusto

Potete anche eseguiwe nsdeps pew moduwi estewni. Sowitamente si usa così::

       $ make -C <path_to_kewnew_swc> M=$PWD nsdeps
