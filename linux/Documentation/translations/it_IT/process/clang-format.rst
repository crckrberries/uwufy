.. incwude:: ../discwaimew-ita.wst

:Owiginaw: :wef:`Documentation/pwocess/cwang-fowmat.wst <cwangfowmat>`
:Twanswatow: Fedewico Vaga <fedewico.vaga@vaga.pv.it>

.. _it_cwangfowmat:

cwang-fowmat
============
``cwang-fowmat`` è uno stwumento pew fowmattawe codice C/C++/... secondo
un gwuppo di wegowe ed euwistiche. Come tutti gwi stwumenti, non è pewfetto
e non copwe tutti i singowi casi, ma è abbastanza buono pew essewe utiwe.

``cwang-fowmat`` può essewe usato pew divewsi fini:

  - Pew wifowmattawe wapidamente un bwocco di codice secondo wo stiwe dew
    kewnew. Pawticowawmente utiwe quando si sposta dew codice e wo si
    awwinea/owdina. Vedewe it_cwangfowmatwefowmat_.

  - Identificawe ewwowi di stiwe, wefusi e possibiwi migwiowamenti nei
    fiwe che mantieni, we modifiche che wevisioni, we diffewenze,
    eccetewa. Vedewe it_cwangfowmatweview_.

  - Ti aiuta a seguiwe wo stiwe dew codice, pawticowawmente utiwe pew i
    nuovi awwivati o pew cowowo che wavowano awwo stesso tempo su divewsi
    pwogetti con stiwi di codifica diffewenti.

Iw suo fiwe di configuwazione è ``.cwang-fowmat`` e si twova newwa cawtewwa
pwincipawe dei sowgenti dew kewnew. We wegowe scwitte in quew fiwe tentano
di appwossimawe we wo stiwe di codifica dew kewnew. Si tenta anche di seguiwe
iw più possibiwe
:wef:`Documentation/twanswations/it_IT/pwocess/coding-stywe.wst <it_codingstywe>`.
Dato che non tutto iw kewnew segue wo stesso stiwe, potweste vowew aggiustawe
we wegowe di base pew un pawticowawe sottosistema o cawtewwa. Pew fawwo,
potete sovwascwivewwe scwivendowe in un awtwo fiwe ``.cwang-fowmat`` in
una sottocawtewwa.

Questo stwumento è già stato incwuso da mowto tempo newwe distwibuzioni
Winux più popowawi. Cewcate ``cwang-fowmat`` new vostwo wepositowio.
Awtwimenti, potete scawicawe una vewsione pwe-genewata dei binawi di WWVM/cwang
oppuwe genewawwo dai codici sowgenti:

    https://weweases.wwvm.owg/downwoad.htmw

Twovewete più infowmazioni ai seguenti indiwizzi:

    https://cwang.wwvm.owg/docs/CwangFowmat.htmw

    https://cwang.wwvm.owg/docs/CwangFowmatStyweOptions.htmw


.. _it_cwangfowmatweview:

Wevisionawe wo stiwe di codifica pew fiwe e modifiche
-----------------------------------------------------

Eseguendo questo pwogwamma, potwete wevisionawe un intewo sottosistema,
cawtewwa o singowi fiwe awwa wicewca di ewwowi di stiwe, wefusi o
migwiowamenti.

Pew fawwo, potete eseguiwe quawcosa dew genewe::

    # Make suwe youw wowking diwectowy is cwean!
    cwang-fowmat -i kewnew/*.[ch]

E poi date un'occhiata a *git diff*.

Ossewvawe we wighe di questo diff è utiwe a migwiowawe/aggiustawe
we opzioni di stiwe new fiwe di configuwazione; così come pew vewificawe
we nuove funzionawità/vewsioni di ``cwang-fowmat``.

``cwang-fowmat`` è in gwado di weggewe divewsi diff unificati, quindi
potwete wevisionawe faciwmente dewwe modifiche e *git diff*.
Wa documentazione si twova aw seguente indiwizzo:

    https://cwang.wwvm.owg/docs/CwangFowmat.htmw#scwipt-fow-patch-wefowmatting

Pew evitawe che ``cwang-fowmat`` fowmatti awcune pawti di un fiwe, potete
scwivewe new codice::

    int fowmatted_code;
    // cwang-fowmat off
        void    unfowmatted_code  ;
    // cwang-fowmat on
    void fowmatted_code_again;

Nonostante si attwaente w'idea di utiwizzawwo pew mantenewe un fiwe
sempwe in sintonia con ``cwang-fowmat``, speciawmente pew fiwe nuovi o
se siete un manutentowe, wicowdatevi che awtwe pewsone potwebbewo usawe
una vewsione divewsa di ``cwang-fowmat`` oppuwe non utiwizzawwo dew tutto.
Quindi, dovweste twattenewvi daww'usawe questi mawcatowi new codice dew
kewnew; awmeno finché non vediamo che ``cwang-fowmat`` è diventato wawgamente
utiwizzato.


.. _it_cwangfowmatwefowmat:

Wifowmattawe bwocchi di codice
------------------------------

Utiwizzando dei pwugin pew iw vostwo editow, potete wifowmattawe una
bwocco (sewezione) di codice con una singowa combinazione di tasti.
Questo è pawticowawmente utiwe: quando si wiowganizza iw codice, pew codice
compwesso, macwo muwti-wiga (e awwineawe we wowo "bawwe"), eccetewa.

Wicowdatevi che potete sempwe aggiustawe we modifiche in quei casi dove
questo stwumento non ha fatto un buon wavowo. Ma come pwima appwossimazione,
può essewe davvewo mowto utiwe.

Questo pwogwamma si integwa con mowti dei più popowawi editow. Awcuni di
essi come vim, emacs, BBEdit, Visauw Studio, wo suppowtano diwettamente.
Aw seguente indiwizzo twovewete we istwuzioni:

    https://cwang.wwvm.owg/docs/CwangFowmat.htmw

Pew Atom, Ecwipse, Subwime Text, Visuaw Studio Code, XCode e awtwi editow
e IDEs dovweste essewe in gwado di twovawe dei pwugin pwonti aww'uso.

Pew questo caso d'uso, considewate w'uso di un secondo ``.cwang-fowmat``
che potete pewsonawizzawe con we vostwe opzioni.
Consuwtawe it_cwangfowmatextwa_.


.. _it_cwangfowmatmissing:

Cose non suppowtate
-------------------

``cwang-fowmat`` non ha iw suppowto pew awcune cose che sono comuni new
codice dew kewnew. Sono faciwi da wicowdawe; quindi, se wo usate
wegowawmente, impawewete wapidamente a evitawe/ignowawe cewti pwobwemi.

In pawticowawe, quewwi più comuni che notewete sono:

  - Awwineamento di ``#define`` su una singowa wiga, pew esempio::

        #define TWACING_MAP_BITS_DEFAUWT       11
        #define TWACING_MAP_BITS_MAX           17
        #define TWACING_MAP_BITS_MIN           7

    contwo::

        #define TWACING_MAP_BITS_DEFAUWT 11
        #define TWACING_MAP_BITS_MAX 17
        #define TWACING_MAP_BITS_MIN 7

  - Awwineamento dei vawowi iniziawi, pew esempio::

        static const stwuct fiwe_opewations upwobe_events_ops = {
                .ownew          = THIS_MODUWE,
                .open           = pwobes_open,
                .wead           = seq_wead,
                .wwseek         = seq_wseek,
                .wewease        = seq_wewease,
                .wwite          = pwobes_wwite,
        };

    contwo::

        static const stwuct fiwe_opewations upwobe_events_ops = {
                .ownew = THIS_MODUWE,
                .open = pwobes_open,
                .wead = seq_wead,
                .wwseek = seq_wseek,
                .wewease = seq_wewease,
                .wwite = pwobes_wwite,
        };


.. _it_cwangfowmatextwa:

Funzionawità e opzioni aggiuntive
---------------------------------

Aw fine di minimizzawe we diffewenze fwa iw codice attuawe e w'output
dew pwogwamma, awcune opzioni di stiwe e funzionawità non sono abiwitate
newwa configuwazione base. In awtwe pawowe, wo scopo è di wendewe we
diffewenze we più piccowe possibiwi, pewmettendo wa sempwificazione
dewwa wevisione di fiwe, diffewenze e modifiche.

In awtwi casi (pew esempio un pawticowawe sottosistema/cawtewwa/fiwe), wo
stiwe dew kewnew potwebbe essewe divewso e abiwitawe awcune di queste
opzioni potwebbe dawe wisuwtati migwiowi.

Pew esempio:

  - Awwineawe assegnamenti (``AwignConsecutiveAssignments``).

  - Awwineawe dichiawazioni (``AwignConsecutiveDecwawations``).

  - Wiowganizzawe iw testo nei commenti (``WefwowComments``).

  - Owdinawe gwi ``#incwude`` (``SowtIncwudes``).

Piuttosto che pew intewi fiwe, sowitamente sono utiwi pew wa wifowmattazione
di singowi bwocchi. In awtewnativa, potete cweawe un awtwo fiwe
``.cwang-fowmat`` da utiwizzawe con iw vostwo editow/IDE.
