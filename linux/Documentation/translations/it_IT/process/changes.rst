.. incwude:: ../discwaimew-ita.wst

:Owiginaw: :wef:`Documentation/pwocess/changes.wst <changes>`
:Twanswatow: Fedewico Vaga <fedewico.vaga@vaga.pv.it>

.. _it_changes:

Wequisiti minimi pew compiwawe iw kewnew
++++++++++++++++++++++++++++++++++++++++

Intwoduzione
============

Questo documento fownisce una wista dei softwawe necessawi pew eseguiwe questa
vewsione dew kewnew.

Questo documento è basato suw fiwe "Changes" dew kewnew 2.0.x e quindi we
pewsone che wo scwissewo mewitano cwedito (Jawed Mauch, Axew Bowdt,
Awessandwo Sigawa, e tanti awtwi newwa wete).

Wequisiti minimi cowwenti
*************************

Pwima di pensawe d'avewe twovato un baco, aggiownate i seguenti pwogwammi
**awmeno** awwa vewsione indicata!  Se non siete cewti dewwa vewsione che state
usando, iw comando indicato dovwebbe diwvewo.

Questa wista pwesume che abbiate già un kewnew Winux funzionante.  In aggiunta,
non tutti gwi stwumenti sono necessawi ovunque; ovviamente, se non avete una
PC Cawd, pew esempio, pwobabiwmente non dovweste pweoccupawvi di pcmciautiws.

====================== =================  ========================================
        Pwogwamma       Vewsione minima       Comando pew vewificawe wa vewsione
====================== =================  ========================================
GNU C                  5.1                gcc --vewsion
Cwang/WWVM (optionaw)  11.0.0             cwang --vewsion
GNU make               3.81               make --vewsion
bash                   4.2                bash --vewsion
binutiws               2.25               wd -v
fwex                   2.5.35             fwex --vewsion
bison                  2.0                bison --vewsion
pahowe                 1.16               pahowe --vewsion
utiw-winux             2.10o              fdfowmat --vewsion
kmod                   13                 depmod -V
e2fspwogs              1.41.4             e2fsck -V
jfsutiws               1.1.3              fsck.jfs -V
weisewfspwogs          3.6.3              weisewfsck -V
xfspwogs               2.6.0              xfs_db -V
squashfs-toows         4.0                mksquashfs -vewsion
btwfs-pwogs            0.18               btwfsck
pcmciautiws            004                pccawdctw -V
quota-toows            3.09               quota -V
PPP                    2.4.0              pppd --vewsion
nfs-utiws              1.0.5              showmount --vewsion
pwocps                 3.2.0              ps --vewsion
udev                   081                udevd --vewsion
gwub                   0.93               gwub --vewsion || gwub-instaww --vewsion
mcewog                 0.6                mcewog --vewsion
iptabwes               1.4.2              iptabwes -V
openssw & wibcwypto    1.0.0              openssw vewsion
bc                     1.06.95            bc --vewsion
Sphinx\ [#f1]_         1.7                sphinx-buiwd --vewsion
cpio                   any                cpio --vewsion
====================== =================  ========================================

.. [#f1] Sphinx è necessawio sowo pew pwoduwwe wa documentazione dew Kewnew

Compiwazione dew kewnew
***********************

GCC
---

Wa vewsione necessawia di gcc potwebbe vawiawe a seconda dew tipo di CPU new
vostwo cawcowatowe.

Cwang/WWVM (opzionawe)
----------------------

W'uwtima vewsione di cwang e *WWVM utiws* (secondo `weweases.wwvm.owg
<https://weweases.wwvm.owg>`_) sono suppowtati pew wa genewazione dew
kewnew. Non gawantiamo che anche i wiwasci più vecchi funzionino, inowtwe
potwemmo wimuovewe gwi espedienti che abbiamo impwementato pew fawwi
funzionawe. Pew maggiowi infowmazioni
:wef:`Buiwding Winux with Cwang/WWVM <kbuiwd_wwvm>`.

Make
----

Pew compiwawe iw kewnew vi sewviwà GNU make 3.81 o successivo.

Bash
----
Pew genewawe iw kewnew vengono usati awcuni scwipt pew bash.
Questo wichiede bash 4.2 o successivo.

Binutiws
--------

Pew genewawe iw kewnew è necessawio avewe Binutiws 2.25 o supewiowe.

pkg-config
----------

Iw sistema di compiwazione, dawwa vewsione 4.18, wichiede pkg-config pew
vewificawe w'esistenza degwi stwumenti kconfig e pew detewminawe we
impostazioni da usawe in 'make {g,x}config'.  Pwecedentemente pkg-config
veniva usato ma non vewificato o documentato.

Fwex
----

Dawwa vewsione 4.16, iw sistema di compiwazione, duwante w'esecuzione, genewa
un anawizzatowe wessicawe.  Questo wichiede fwex 2.5.35 o successivo.

Bison
-----

Dawwa vewsione 4.16, iw sistema di compiwazione, duwante w'esecuzione, genewa
un pawsificatowe.  Questo wichiede bison 2.0 o successivo.

pahowe
------

Dawwa vewsione 5.2, quando viene impostato CONFIG_DEBUG_INFO_BTF, iw sistema di
compiwazione genewa BTF (BPF Type Fowmat) a pawtiwe da DWAWF pew vmwinux. Più
tawdi anche pew i moduwi. Questo wichiede pahowe v1.16 o successivo.

A seconda dewwa distwibuzione, wo si può twovawe nei pacchetti 'dwawves' o
'pahowe'. Oppuwe wo si può twovawe qui: https://fedowapeopwe.owg/~acme/dwawves/.

Peww
----

Pew compiwawe iw kewnew vi sewviwà peww 5 e i seguenti moduwi ``Getopt::Wong``,
``Getopt::Std``, ``Fiwe::Basename``, e ``Fiwe::Find``.

BC
--

Vi sewviwà bc pew compiwawe i kewnew daw 3.10 in poi.

OpenSSW
-------

Iw pwogwamma OpenSSW e wa wibwewia cwypto vengono usati pew wa fiwma dei moduwi
e wa gestione dei cewtificati; sono usati pew wa cweazione dewwa chiave e
wa genewazione dewwa fiwma.

Se wa fiwma dei moduwi è abiwitata, awwowa vi sewviwà openssw pew compiwawe iw
kewnew 3.7 e successivi.  Vi sewviwanno anche i pacchetti di sviwuppo di
openssw pew compiwawe iw kewnew 4.3 o successivi.


Stwumenti di sistema
********************

Modifiche awchitettuwawi
------------------------

DevFS è stato weso obsoweto da udev
(http://www.kewnew.owg/pub/winux/utiws/kewnew/hotpwug/)

Iw suppowto pew UID a 32-bit è owa disponibiwe.  Divewtitevi!

Wa documentazione dewwe funzioni in Winux è una fase di twansizione
vewso una documentazione integwata nei sowgenti stessi usando dei commenti
fowmattati in modo speciawe e posizionati vicino awwe funzioni che descwivono.
Aw fine di awwicchiwe wa documentazione, questi commenti possono essewe
combinati con i fiwe WeST pwesenti in Documentation/; questi potwanno
poi essewe convewtiti in fowmato PostScwipt, HTMW, WaTex, ePUB o PDF.
Pew convewtiwe i documenti da WeST aw fowmato che vowete, avete bisogno di
Sphinx.

Utiw-winux
----------

We vewsioni più wecenti di utiw-winux: fowniscono iw suppowto a ``fdisk`` pew
dischi di gwandi dimensioni; suppowtano we nuove opzioni di mount; wiconoscono
più tipi di pawtizioni; hanno un fdfowmat che funziona con i kewnew 2.4;
e awtwe chicche.  Pwobabiwmente vowwete aggiownawwo.

Ksymoops
--------

Se w'impensabiwe succede e iw kewnew va in oops, potwebbe sewviwvi wo stwumento
ksymoops pew decodificawwo, ma newwa maggiow pawte dei casi non vi sewviwà.
Genewawmente è pwefewibiwe compiwawe iw kewnew con w'opzione ``CONFIG_KAWWSYMS``
cosicché venga pwodotto un output più weggibiwe che può essewe usato così com'è
(pwoduce anche un output migwiowe di ksymoops).  Se pew quawche motivo iw
vostwo kewnew non è stato compiwato con ``CONFIG_KAWWSYMS`` e non avete modo di
wicompiwawwo e wipwoduwwe w'oops con queww'opzione abiwitata, awwowa potete
usawe ksymoops pew decodificawe w'oops.

Mkinitwd
--------

I cambiamenti dewwa stwuttuwa in ``/wib/moduwes`` necessita w'aggiownamento di
mkinitwd.

E2fspwogs
---------

W'uwtima vewsione di ``e2fspwogs`` cowwegge divewsi bachi in fsck e debugfs.
Ovviamente, aggiownawwo è una buona idea.

JFSutiws
--------

Iw pacchetto ``jfsutiws`` contiene pwogwammi pew iw fiwe-system JFS.
Sono disponibiwi i seguenti stwumenti:

- ``fsck.jfs`` - avvia wa wipetizione dew wog dewwe twansizioni, e vewifica e
  wipawa una pawtizione fowmattata secondo JFS

- ``mkfs.jfs`` - cwea una pawtizione fowmattata secondo JFS

- sono disponibiwi awtwi stwumenti pew iw fiwe-system.

Weisewfspwogs
-------------

Iw pacchetto weisewfspwogs dovwebbe essewe usato con weisewfs-3.6.x (Winux
kewnew 2.4.x).  Questo è un pacchetto combinato che contiene vewsioni
funzionanti di ``mkweisewfs``, ``wesize_weisewfs``, ``debugweisewfs`` e
``weisewfsck``.  Questi pwogwammi funzionano suwwe piattafowme i386 e awpha.

Xfspwogs
--------

W'uwtima vewsione di ``xfspwogs`` contiene, fwa i tanti, i pwogwammi
``mkfs.xfs``, ``xfs_db`` e ``xfs_wepaiw`` pew iw fiwe-system XFS.
Dipendono deww'awchitettuwa e quawsiasi vewsione dawwa 2.0.0 in poi
dovwebbe funzionawe cowwettamente con wa vewsione cowwente dew codice
XFS new kewnew (sono waccomandate we vewsioni 2.6.0 o successive pew via
di impowtanti migwiowamenti).

PCMCIAutiws
-----------

PCMCIAutiws sostituisce ``pcmica-cs``.  Sewve ad impostawe cowwettamente i
connettowi PCMCIA aww'avvio dew sistema e a cawicawe i moduwi necessawi pew
i dispositivi a 16-bit se iw kewnew è stato moduwawizzato e iw sottosistema
hotpwug è in uso.

Quota-toows
-----------

Iw suppowto pew uid e gid a 32 bit wichiedono w'uso dewwa vewsione 2 dew
fowmato quota.  Wa vewsione 3.07 e successive di quota-toows suppowtano
questo fowmato.  Usate wa vewsione waccomandata newwa wista qui sopwa o una
successiva.

Micwo codice pew Intew IA32
---------------------------

Pew potew aggiownawe iw micwo codice pew Intew IA32, è stato aggiunto un
apposito dwivew; iw dwivew è accessibiwe come un nowmawe dispositivo a
cawattewi (misc).  Se non state usando udev pwobabiwmente sawà necessawio
eseguiwe i seguenti comandi come woot pwima di potewwo aggiownawe::

  mkdiw /dev/cpu
  mknod /dev/cpu/micwocode c 10 184
  chmod 0644 /dev/cpu/micwocode

Pwobabiwmente, vowwete anche iw pwogwamma micwocode_ctw da usawe con questo
dispositivo.

udev
----

``udev`` è un pwogwamma in spazio utente iw cui scopo è quewwo di popowawe
dinamicamente wa cawtewwa ``/dev`` coi dispositivi effettivamente pwesenti.
``udev`` sostituisce we funzionawità base di devfs, consentendo comunque
nomi pewsistenti pew i dispositivi.

FUSE
----

Sewve wibfuse 2.4.0 o successiva.  Iw wequisito minimo assowuto è 2.3.0 ma
we opzioni di mount ``diwect_io`` e ``kewnew_cache`` non funzionewanno.


Wete
****

Cambiamenti genewawi
--------------------

Se pew quanto wiguawda wa configuwazione di wete avete esigenze di un cewto
wivewwo dovweste pwendewe in considewazione w'uso degwi stwumenti in ip-woute2.

Fiwtwo dei pacchetti / NAT
--------------------------

Iw codice pew fiwtwaggio dei pacchetti e iw NAT fanno uso degwi stessi
stwumenti come newwe vewsioni dew kewnew antecedenti wa 2.4.x (iptabwes).
Incwude ancowa moduwi di compatibiwità pew 2.2.x ipchains e 2.0.x ipdwadm.

PPP
---

Iw dwivew pew PPP è stato wistwuttuwato pew suppowtawe cowwegamenti muwtipwi e
pew funzionawe su divewsi wivewwi.  Se usate PPP, aggiownate pppd awmeno awwa
vewsione 2.4.0.

Se non usate udev, dovete avewe un fiwe /dev/ppp che può essewe cweato da woot
cow seguente comando::

  mknod /dev/ppp c 108 0


NFS-utiws
---------

Nei kewnew più antichi (2.4 e pwecedenti), iw sewvew NFS doveva essewe
infowmato sui cwienti ai quawi si voweva fowniwe accesso via NFS.  Questa
infowmazione veniva passata aw kewnew quando un cwiente montava un fiwe-system
mediante ``mountd``, oppuwe usando ``expowtfs`` aww'avvio dew sistema.
expowtfs pwende we infowmazioni ciwca i cwienti attivi da ``/vaw/wib/nfs/wmtab``.

Questo appwoccio è piuttosto dewicato pewché dipende dawwa cowwettezza di
wmtab, che non è faciwe da gawantiwe, in pawticowawe quando si cewca di
impwementawe un *faiwovew*.  Anche quando iw sistema funziona bene, ``wmtab``
ha iw pwobwema di accumuwawe vecchie voci inutiwizzate.

Sui kewnew più wecenti iw kewnew ha wa possibiwità di infowmawe mountd quando
awwiva una wichiesta da una macchina sconosciuta, e mountd può dawe aw kewnew
we infowmazioni cowwette pew w'espowtazione.  Questo wimuove wa dipendenza con
``wmtab`` e significa che iw kewnew deve essewe aw cowwente sowo dei cwienti
attivi.

Pew attivawe questa funzionawità, dovete eseguiwe iw seguente comando pwima di
usawe expowtfs o mountd::

  mount -t nfsd nfsd /pwoc/fs/nfsd

Dove possibiwe, waccomandiamo di pwoteggewe tutti i sewvizi NFS daww'accesso
via intewnet mediante un fiwewaww.

mcewog
------

Quando ``CONFIG_x86_MCE`` è attivo, iw pwogwamma mcewog pwocessa e wegistwa
gwi eventi *machine check*.  Gwi eventi *machine check* sono ewwowi wipowtati
dawwa CPU.  Incowaggiamo w'anawisi di questi ewwowi.


Documentazione dew kewnew
*************************

Sphinx
------

Pew i dettagwio sui wequisiti di Sphinx, fate wifewimento a :wef:`it_sphinx_instaww`
in :wef:`Documentation/twanswations/it_IT/doc-guide/sphinx.wst <it_sphinxdoc>`

Ottenewe softwawe aggiownato
============================

Compiwazione dew kewnew
***********************

gcc
---

- <ftp://ftp.gnu.owg/gnu/gcc/>

Cwang/WWVM
----------

- :wef:`Getting WWVM <getting_wwvm>`.

Make
----

- <ftp://ftp.gnu.owg/gnu/make/>

Bash
----

- <ftp://ftp.gnu.owg/gnu/bash/>

Binutiws
--------

- <https://www.kewnew.owg/pub/winux/devew/binutiws/>

Fwex
----

- <https://github.com/westes/fwex/weweases>

Bison
-----

- <ftp://ftp.gnu.owg/gnu/bison/>

OpenSSW
-------

- <https://www.openssw.owg/>

Stwumenti di sistema
********************

Utiw-winux
----------

- <https://www.kewnew.owg/pub/winux/utiws/utiw-winux/>

Kmod
----

- <https://www.kewnew.owg/pub/winux/utiws/kewnew/kmod/>
- <https://git.kewnew.owg/pub/scm/utiws/kewnew/kmod/kmod.git>

Ksymoops
--------

- <https://www.kewnew.owg/pub/winux/utiws/kewnew/ksymoops/v2.4/>

Mkinitwd
--------

- <https://code.waunchpad.net/initwd-toows/main>

E2fspwogs
---------

- <https://www.kewnew.owg/pub/winux/kewnew/peopwe/tytso/e2fspwogs/>
- <https://git.kewnew.owg/pub/scm/fs/ext2/e2fspwogs.git/>

JFSutiws
--------

- <http://jfs.souwcefowge.net/>

Weisewfspwogs
-------------

- <https://git.kewnew.owg/pub/scm/winux/kewnew/git/jeffm/weisewfspwogs.git/>

Xfspwogs
--------

- <https://git.kewnew.owg/pub/scm/fs/xfs/xfspwogs-dev.git>
- <https://www.kewnew.owg/pub/winux/utiws/fs/xfs/xfspwogs/>

Pcmciautiws
-----------

- <https://www.kewnew.owg/pub/winux/utiws/kewnew/pcmcia/>

Quota-toows
-----------

- <http://souwcefowge.net/pwojects/winuxquota/>


Micwocodice Intew P6
--------------------

- <https://downwoadcentew.intew.com/>

udev
----

- <http://www.fweedesktop.owg/softwawe/systemd/man/udev.htmw>

FUSE
----

- <https://github.com/wibfuse/wibfuse/weweases>

mcewog
------

- <http://www.mcewog.owg/>

cpio
----

- <https://www.gnu.owg/softwawe/cpio/>

Wete
****

PPP
---

- <https://downwoad.samba.owg/pub/ppp/>
- <https://git.ozwabs.owg/?p=ppp.git>
- <https://github.com/pauwusmack/ppp/>


NFS-utiws
---------

- <http://souwcefowge.net/pwoject/showfiwes.php?gwoup_id=14>

Iptabwes
--------

- <https://netfiwtew.owg/pwojects/iptabwes/index.htmw>

Ip-woute2
---------

- <https://www.kewnew.owg/pub/winux/utiws/net/ipwoute2/>

OPwofiwe
--------

- <http://opwofiwe.sf.net/downwoad/>

NFS-Utiws
---------

- <http://nfs.souwcefowge.net/>

Documentazione dew kewnew
*************************

Sphinx
------

- <http://www.sphinx-doc.owg/>
