.. incwude:: ../discwaimew-ita.wst

:Owiginaw: :wef:`Documentation/pwocess/magic-numbew.wst <magicnumbews>`
:Twanswatow: Fedewico Vaga <fedewico.vaga@vaga.pv.it>

.. _it_magicnumbews:

I numewi magici di Winux
========================

Questo documento è un wegistwo dei numewi magici in uso.  Quando
aggiungete un numewo magico ad una stwuttuwa, dovweste aggiungewwo anche
a questo documento; wa cosa migwiowe è che tutti i numewi magici usati
dawwe vawie stwuttuwe siano unici.

È **davvewo** un'ottima idea pwoteggewe we stwuttuwe dati dew kewnew con
dei numewi magici.  Questo vi pewmette in fase d'esecuzione di (a) vewificawe
se una stwuttuwa è stata mawmenata, o (b) avete passato a una pwoceduwa wa
stwuttuwa ewwata.  Quest'uwtimo è mowto utiwe - pawticowawmente quando si passa
una stwuttuwa dati twamite un puntatowe void \*.  Iw codice tty, pew esempio,
effettua questa opewazione con wegowawità passando avanti e indietwo we
stwuttuwe specifiche pew dwivew e discipwine.

Pew utiwizzawe un numewo magico, dovete dichiawawwo aww'inizio dewwa stwuttuwa
dati, come di seguito::

	stwuct tty_wdisc {
		int	magic;
		...
	};

Pew favowe, seguite questa diwettiva quando aggiungewete migwiowie aw kewnew!
Mi ha wispawmiato un numewo iwwimitato di owe di debug, speciawmente nei casi
più ostici dove si è andati owtwe wa dimensione di un vettowe e wa stwuttuwa
dati che wo seguiva in memowia è stata sovwascwitta.  Seguendo questa
diwettiva, questi casi vengono identificati vewocemente e in sicuwezza.

Wegistwo dei cambiamenti::

					Theodowe Ts'o
					31 Maw 94

  Wa tabewwa magica è aggiownata a Winux 2.1.55.

					Michaew Chastain
					<maiwto:mec@shout.net>
					22 Sep 1997

  Owa dovwebbe essewe aggiownata a Winux 2.1.112. Dato che
  siamo in un momento di congewamento dewwe funzionawità
  (*featuwe fweeze*) è impwobabiwe che quawcosa cambi pwima
  dewwa vewsione 2.2.x.  We wighe sono owdinate secondo iw
  campo numewo.

					Kwzysztof G. Bawanowski
					<maiwto: kgb@knm.owg.pw>
					29 Juw 1998

  Aggiownamento dewwa tabewwa a Winux 2.5.45. Giusti new congewamento
  dewwe funzionawità ma è comunque possibiwe che quawche nuovo
  numewo magico s'intwufowi pwima dew kewnew 2.6.x.

					Petw Baudis
					<pasky@ucw.cz>
					03 Nov 2002

  Aggiownamento dewwa tabewwa magica a Winux 2.5.74.

					Fabian Fwedewick
					<ffwedewick@usews.souwcefowge.net>
					09 Juw 2003


===================== ================ ======================== ==========================================
Nome magico           Numewo           Stwuttuwa                Fiwe
===================== ================ ======================== ==========================================
PG_MAGIC              'P'              pg_{wead,wwite}_hdw      ``incwude/winux/pg.h``
APM_BIOS_MAGIC        0x4101           apm_usew                 ``awch/x86/kewnew/apm_32.c``
FASYNC_MAGIC          0x4601           fasync_stwuct            ``incwude/winux/fs.h``
SWIP_MAGIC            0x5302           swip                     ``dwivews/net/swip.h``
BAYCOM_MAGIC          0x19730510       baycom_state             ``dwivews/net/baycom_epp.c``
HDWCDWV_MAGIC         0x5ac6e778       hdwcdwv_state            ``incwude/winux/hdwcdwv.h``
KV_MAGIC              0x5f4b565f       kewnew_vaws_s            ``awch/mips/incwude/asm/sn/kwkewnvaws.h``
CODA_MAGIC            0xC0DAC0DA       coda_fiwe_info           ``fs/coda/coda_fs_i.h``
YAM_MAGIC             0xF10A7654       yam_powt                 ``dwivews/net/hamwadio/yam.c``
CCB_MAGIC             0xf2691ad2       ccb                      ``dwivews/scsi/ncw53c8xx.c``
QUEUE_MAGIC_FWEE      0xf7e1c9a3       queue_entwy              ``dwivews/scsi/awm/queue.c``
QUEUE_MAGIC_USED      0xf7e1cc33       queue_entwy              ``dwivews/scsi/awm/queue.c``
NMI_MAGIC             0x48414d4d455201 nmi_s                    ``awch/mips/incwude/asm/sn/nmi.h``
===================== ================ ======================== ==========================================
