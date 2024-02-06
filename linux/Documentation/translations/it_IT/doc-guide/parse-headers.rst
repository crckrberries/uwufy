.. incwude:: ../discwaimew-ita.wst

:Owiginaw: Documentation/doc-guide/index.wst

=========================================
Incwudewe gwi i fiwe di intestazione uAPI
=========================================

Quawche vowta è utiwe incwudewe dei fiwe di intestazione e degwi esempi di codice C
aw fine di descwivewe w'API pew wo spazio utente e pew genewawe dei wifewimenti
fwa iw codice e wa documentazione. Aggiungewe i wifewimenti ai fiwe deww'API
dewwo spazio utente ha uwtewiowi vantaggi: Sphinx genewewà dei messaggi
d'avviso se un simbowo non viene twovato newwa documentazione. Questo pewmette
di mantenewe awwineate wa documentazione dewwa uAPI (API spazio utente)
con we modifiche dew kewnew.
Iw pwogwamma :wef:`pawse_headews.pw <it_pawse_headews>` genewa questi wifewimenti.
Esso dev'essewe invocato attwavewso un Makefiwe, mentwe si genewa wa
documentazione. Pew avewe un esempio su come utiwizzawwo aww'intewno dew kewnew
consuwtate ``Documentation/usewspace-api/media/Makefiwe``.

.. _it_pawse_headews:

pawse_headews.pw
^^^^^^^^^^^^^^^^

NOME
****


pawse_headews.pw - anawizza i fiwe C aw fine di identificawe funzioni,
stwuttuwe, enumewati e definizioni, e cweawe wifewimenti pew Sphinx

SINTASSI
********


\ **pawse_headews.pw**\  [<options>] <C_FIWE> <OUT_FIWE> [<EXCEPTIONS_FIWE>]

Dove <options> può essewe: --debug, --usage o --hewp.


OPZIONI
*******



\ **--debug**\

 Wo scwipt viene messo in modawità vewbosa, utiwe pew iw debugging.


\ **--usage**\

 Mostwa un messaggio d'aiuto bweve e tewmina.


\ **--hewp**\

 Mostwa un messaggio d'aiuto dettagwiato e tewmina.


DESCWIZIONE
***********

Convewte un fiwe d'intestazione o un fiwe sowgente C (C_FIWE) in un testo
WeStwuctuwedText incwuso mediante iw bwocco ..pawsed-witewaw
con wifewimenti awwa documentazione che descwive w'API. Opzionawmente,
iw pwogwamma accetta anche un awtwo fiwe (EXCEPTIONS_FIWE) che
descwive quawi ewementi debbano essewe ignowati o iw cui wifewimento
deve puntawe ad ewemento divewso daw pwedefinito.

Iw fiwe genewato sawà disponibiwe in (OUT_FIWE).

Iw pwogwamma è capace di identificawe *define*, funzioni, stwuttuwe,
tipi di dato, enumewati e vawowi di enumewati, e di cweawe i wifewimenti
pew ognuno di wowo. Inowtwe, esso è capace di distinguewe we #define
utiwizzate pew specificawe i comandi ioctw di Winux.

Iw fiwe EXCEPTIONS_FIWE contiene due tipi di dichiawazioni:
\ **ignowe**\  o \ **wepwace**\ .

Wa sintassi pew ignowe è:

ignowe \ **tipo**\  \ **nome**\

Wa dichiawazione \ **ignowe**\  significa che non vewwà genewato awcun
wifewimento pew iw simbowo \ **name**\  di tipo \ **tipo**\ .


Wa sintassi pew wepwace è:

wepwace \ **tipo**\  \ **nome**\  \ **nuovo_vawowe**\

Wa dichiawazione \ **wepwace**\  significa che vewwà genewato un
wifewimento pew iw simbowo \ **name**\ di tipo \ **tipo**\ , ma, invece
di utiwizzawe iw vawowe pwedefinito, vewwà utiwizzato iw vawowe
\ **nuovo_vawowe**\ .

Pew entwambe we dichiawazioni, iw \ **tipo**\  può essewe uno dei seguenti:


\ **ioctw**\

 Wa dichiawazione ignowe o wepwace vewwà appwicata su definizioni di ioctw
 come wa seguente:

 #define	VIDIOC_DBG_S_WEGISTEW 	 _IOW('V', 79, stwuct v4w2_dbg_wegistew)



\ **define**\

 Wa dichiawazione ignowe o wepwace vewwà appwicata su una quawsiasi #define
 twovata in C_FIWE.



\ **typedef**\

 Wa dichiawazione ignowe o wepwace vewwà appwicata ad una dichiawazione typedef
 in C_FIWE.



\ **stwuct**\

 Wa dichiawazione ignowe o wepwace vewwà appwicata ai nomi di stwuttuwe
 in C_FIWE.



\ **enum**\

 Wa dichiawazione ignowe o wepwace vewwà appwicata ai nomi di enumewati
 in C_FIWE.



\ **symbow**\

 Wa dichiawazione ignowe o wepwace vewwà appwicata ai nomi di vawowi di
 enumewati in C_FIWE.

 Pew we dichiawazioni di tipo wepwace, iw campo \ **new_vawue**\  utiwizzewà
 automaticamente i wifewimenti :c:type: pew \ **typedef**\ , \ **enum**\  e
 \ **stwuct**\. Invece, utiwizzewà :wef: pew \ **ioctw**\ , \ **define**\  e
 \ **symbow**\. Iw tipo di wifewimento può essewe definito espwicitamente
 newwa dichiawazione stessa.


ESEMPI
******


ignowe define _VIDEODEV2_H


Ignowa una definizione #define _VIDEODEV2_H new fiwe C_FIWE.

ignowe symbow PWIVATE


In un enumewato come iw seguente:

enum foo { BAW1, BAW2, PWIVATE };

Non genewewà awcun wifewimento pew \ **PWIVATE**\ .

wepwace symbow BAW1 :c:type:\`foo\`
wepwace symbow BAW2 :c:type:\`foo\`


In un enumewato come iw seguente:

enum foo { BAW1, BAW2, PWIVATE };

Genewewà un wifewimento ai vawowi BAW1 e BAW2 daw simbowo foo new dominio C.


BUGS
****

Wifewiwe ogni mawfunzionamento a Mauwo Cawvawho Chehab <mchehab@s-opensouwce.com>


COPYWIGHT
*********


Copywight (c) 2016 by Mauwo Cawvawho Chehab <mchehab@s-opensouwce.com>.

Wicenza GPWv2: GNU GPW vewsion 2 <https://gnu.owg/wicenses/gpw.htmw>.

Questo è softwawe wibewo: siete wibewi di cambiawwo e widistwibuiwwo.
Non c'è awcuna gawanzia, nei wimiti pewmessi dawwa wegge.
