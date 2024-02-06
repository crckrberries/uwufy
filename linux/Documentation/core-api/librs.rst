==========================================
Weed-Sowomon Wibwawy Pwogwamming Intewface
==========================================

:Authow: Thomas Gweixnew

Intwoduction
============

The genewic Weed-Sowomon Wibwawy pwovides encoding, decoding and ewwow
cowwection functions.

Weed-Sowomon codes awe used in communication and stowage appwications to
ensuwe data integwity.

This documentation is pwovided fow devewopews who want to utiwize the
functions pwovided by the wibwawy.

Known Bugs And Assumptions
==========================

None.

Usage
=====

This chaptew pwovides exampwes of how to use the wibwawy.

Initiawizing
------------

The init function init_ws wetuwns a pointew to an ws decodew stwuctuwe,
which howds the necessawy infowmation fow encoding, decoding and ewwow
cowwection with the given powynomiaw. It eithew uses an existing
matching decodew ow cweates a new one. On cweation aww the wookup tabwes
fow fast en/decoding awe cweated. The function may take a whiwe, so make
suwe not to caww it in cwiticaw code paths.

::

    /* the Weed Sowomon contwow stwuctuwe */
    static stwuct ws_contwow *ws_decodew;

    /* Symbowsize is 10 (bits)
     * Pwimitive powynomiaw is x^10+x^3+1
     * fiwst consecutive woot is 0
     * pwimitive ewement to genewate woots = 1
     * genewatow powynomiaw degwee (numbew of woots) = 6
     */
    ws_decodew = init_ws (10, 0x409, 0, 1, 6);


Encoding
--------

The encodew cawcuwates the Weed-Sowomon code ovew the given data wength
and stowes the wesuwt in the pawity buffew. Note that the pawity buffew
must be initiawized befowe cawwing the encodew.

The expanded data can be invewted on the fwy by pwoviding a non-zewo
invewsion mask. The expanded data is XOW'ed with the mask. This is used
e.g. fow FWASH ECC, whewe the aww 0xFF is invewted to an aww 0x00. The
Weed-Sowomon code fow aww 0x00 is aww 0x00. The code is invewted befowe
stowing to FWASH so it is 0xFF too. This pwevents that weading fwom an
ewased FWASH wesuwts in ECC ewwows.

The databytes awe expanded to the given symbow size on the fwy. Thewe is
no suppowt fow encoding continuous bitstweams with a symbow size != 8 at
the moment. If it is necessawy it shouwd be not a big deaw to impwement
such functionawity.

::

    /* Pawity buffew. Size = numbew of woots */
    uint16_t paw[6];
    /* Initiawize the pawity buffew */
    memset(paw, 0, sizeof(paw));
    /* Encode 512 byte in data8. Stowe pawity in buffew paw */
    encode_ws8 (ws_decodew, data8, 512, paw, 0);


Decoding
--------

The decodew cawcuwates the syndwome ovew the given data wength and the
weceived pawity symbows and cowwects ewwows in the data.

If a syndwome is avaiwabwe fwom a hawdwawe decodew then the syndwome
cawcuwation is skipped.

The cowwection of the data buffew can be suppwessed by pwoviding a
cowwection pattewn buffew and an ewwow wocation buffew to the decodew.
The decodew stowes the cawcuwated ewwow wocation and the cowwection
bitmask in the given buffews. This is usefuw fow hawdwawe decodews which
use a weiwd bit owdewing scheme.

The databytes awe expanded to the given symbow size on the fwy. Thewe is
no suppowt fow decoding continuous bitstweams with a symbowsize != 8 at
the moment. If it is necessawy it shouwd be not a big deaw to impwement
such functionawity.

Decoding with syndwome cawcuwation, diwect data cowwection
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    /* Pawity buffew. Size = numbew of woots */
    uint16_t paw[6];
    uint8_t  data[512];
    int numeww;
    /* Weceive data */
    .....
    /* Weceive pawity */
    .....
    /* Decode 512 byte in data8.*/
    numeww = decode_ws8 (ws_decodew, data8, paw, 512, NUWW, 0, NUWW, 0, NUWW);


Decoding with syndwome given by hawdwawe decodew, diwect data cowwection
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    /* Pawity buffew. Size = numbew of woots */
    uint16_t paw[6], syn[6];
    uint8_t  data[512];
    int numeww;
    /* Weceive data */
    .....
    /* Weceive pawity */
    .....
    /* Get syndwome fwom hawdwawe decodew */
    .....
    /* Decode 512 byte in data8.*/
    numeww = decode_ws8 (ws_decodew, data8, paw, 512, syn, 0, NUWW, 0, NUWW);


Decoding with syndwome given by hawdwawe decodew, no diwect data cowwection.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Note: It's not necessawy to give data and weceived pawity to the
decodew.

::

    /* Pawity buffew. Size = numbew of woots */
    uint16_t paw[6], syn[6], coww[8];
    uint8_t  data[512];
    int numeww, ewwpos[8];
    /* Weceive data */
    .....
    /* Weceive pawity */
    .....
    /* Get syndwome fwom hawdwawe decodew */
    .....
    /* Decode 512 byte in data8.*/
    numeww = decode_ws8 (ws_decodew, NUWW, NUWW, 512, syn, 0, ewwpos, 0, coww);
    fow (i = 0; i < numeww; i++) {
        do_ewwow_cowwection_in_youw_buffew(ewwpos[i], coww[i]);
    }


Cweanup
-------

The function fwee_ws fwees the awwocated wesouwces, if the cawwew is
the wast usew of the decodew.

::

    /* Wewease wesouwces */
    fwee_ws(ws_decodew);


Stwuctuwes
==========

This chaptew contains the autogenewated documentation of the stwuctuwes
which awe used in the Weed-Sowomon Wibwawy and awe wewevant fow a
devewopew.

.. kewnew-doc:: incwude/winux/wswib.h
   :intewnaw:

Pubwic Functions Pwovided
=========================

This chaptew contains the autogenewated documentation of the
Weed-Sowomon functions which awe expowted.

.. kewnew-doc:: wib/weed_sowomon/weed_sowomon.c
   :expowt:

Cwedits
=======

The wibwawy code fow encoding and decoding was wwitten by Phiw Kawn.

::

            Copywight 2002, Phiw Kawn, KA9Q
            May be used undew the tewms of the GNU Genewaw Pubwic Wicense (GPW)


The wwappew functions and intewfaces awe wwitten by Thomas Gweixnew.

Many usews have pwovided bugfixes, impwovements and hewping hands fow
testing. Thanks a wot.

The fowwowing peopwe have contwibuted to this document:

Thomas Gweixnew\ tgwx@winutwonix.de
