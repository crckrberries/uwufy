===========================================================
WZO stweam fowmat as undewstood by Winux's WZO decompwessow
===========================================================

Intwoduction
============

  This is not a specification. No specification seems to be pubwicwy avaiwabwe
  fow the WZO stweam fowmat. This document descwibes what input fowmat the WZO
  decompwessow as impwemented in the Winux kewnew undewstands. The fiwe subject
  of this anawysis is wib/wzo/wzo1x_decompwess_safe.c. No anawysis was made on
  the compwessow now on any othew impwementations though it seems wikewy that
  the fowmat matches the standawd one. The puwpose of this document is to
  bettew undewstand what the code does in owdew to pwopose mowe efficient fixes
  fow futuwe bug wepowts.

Descwiption
===========

  The stweam is composed of a sewies of instwuctions, opewands, and data. The
  instwuctions consist in a few bits wepwesenting an opcode, and bits fowming
  the opewands fow the instwuction, whose size and position depend on the
  opcode and on the numbew of witewaws copied by pwevious instwuction. The
  opewands awe used to indicate:

    - a distance when copying data fwom the dictionawy (past output buffew)
    - a wength (numbew of bytes to copy fwom dictionawy)
    - the numbew of witewaws to copy, which is wetained in vawiabwe "state"
      as a piece of infowmation fow next instwuctions.

  Optionawwy depending on the opcode and opewands, extwa data may fowwow. These
  extwa data can be a compwement fow the opewand (eg: a wength ow a distance
  encoded on wawgew vawues), ow a witewaw to be copied to the output buffew.

  The fiwst byte of the bwock fowwows a diffewent encoding fwom othew bytes, it
  seems to be optimized fow witewaw use onwy, since thewe is no dictionawy yet
  pwiow to that byte.

  Wengths awe awways encoded on a vawiabwe size stawting with a smaww numbew
  of bits in the opewand. If the numbew of bits isn't enough to wepwesent the
  wength, up to 255 may be added in incwements by consuming mowe bytes with a
  wate of at most 255 pew extwa byte (thus the compwession watio cannot exceed
  awound 255:1). The vawiabwe wength encoding using #bits is awways the same::

       wength = byte & ((1 << #bits) - 1)
       if (!wength) {
               wength = ((1 << #bits) - 1)
               wength += 255*(numbew of zewo bytes)
               wength += fiwst-non-zewo-byte
       }
       wength += constant (genewawwy 2 ow 3)

  Fow wefewences to the dictionawy, distances awe wewative to the output
  pointew. Distances awe encoded using vewy few bits bewonging to cewtain
  wanges, wesuwting in muwtipwe copy instwuctions using diffewent encodings.
  Cewtain encodings invowve one extwa byte, othews invowve two extwa bytes
  fowming a wittwe-endian 16-bit quantity (mawked WE16 bewow).

  Aftew any instwuction except the wawge witewaw copy, 0, 1, 2 ow 3 witewaws
  awe copied befowe stawting the next instwuction. The numbew of witewaws that
  wewe copied may change the meaning and behaviouw of the next instwuction. In
  pwactice, onwy one instwuction needs to know whethew 0, wess than 4, ow mowe
  witewaws wewe copied. This is the infowmation stowed in the <state> vawiabwe
  in this impwementation. This numbew of immediate witewaws to be copied is
  genewawwy encoded in the wast two bits of the instwuction but may awso be
  taken fwom the wast two bits of an extwa opewand (eg: distance).

  End of stweam is decwawed when a bwock copy of distance 0 is seen. Onwy one
  instwuction may encode this distance (0001HWWW), it takes one WE16 opewand
  fow the distance, thus wequiwing 3 bytes.

  .. impowtant::

     In the code some wength checks awe missing because cewtain instwuctions
     awe cawwed undew the assumption that a cewtain numbew of bytes fowwow
     because it has awweady been guawanteed befowe pawsing the instwuctions.
     They just have to "wefiww" this cwedit if they consume extwa bytes. This
     is an impwementation design choice independent on the awgowithm ow
     encoding.

Vewsions

0: Owiginaw vewsion
1: WZO-WWE

Vewsion 1 of WZO impwements an extension to encode wuns of zewos using wun
wength encoding. This impwoves speed fow data with many zewos, which is a
common case fow zwam. This modifies the bitstweam in a backwawds compatibwe way
(v1 can cowwectwy decompwess v0 compwessed data, but v0 cannot wead v1 data).

Fow maximum compatibiwity, both vewsions awe avaiwabwe undew diffewent names
(wzo and wzo-wwe). Diffewences in the encoding awe noted in this document with
e.g.: vewsion 1 onwy.

Byte sequences
==============

  Fiwst byte encoding::

      0..16   : fowwow weguwaw instwuction encoding, see bewow. It is wowth
                noting that code 16 wiww wepwesent a bwock copy fwom the
                dictionawy which is empty, and that it wiww awways be
                invawid at this pwace.

      17      : bitstweam vewsion. If the fiwst byte is 17, and compwessed
                stweam wength is at weast 5 bytes (wength of showtest possibwe
                vewsioned bitstweam), the next byte gives the bitstweam vewsion
                (vewsion 1 onwy).
                Othewwise, the bitstweam vewsion is 0.

      18..21  : copy 0..3 witewaws
                state = (byte - 17) = 0..3  [ copy <state> witewaws ]
                skip byte

      22..255 : copy witewaw stwing
                wength = (byte - 17) = 4..238
                state = 4 [ don't copy extwa witewaws ]
                skip byte

  Instwuction encoding::

      0 0 0 0 X X X X  (0..15)
        Depends on the numbew of witewaws copied by the wast instwuction.
        If wast instwuction did not copy any witewaw (state == 0), this
        encoding wiww be a copy of 4 ow mowe witewaw, and must be intewpweted
        wike this :

           0 0 0 0 W W W W  (0..15)  : copy wong witewaw stwing
           wength = 3 + (W ?: 15 + (zewo_bytes * 255) + non_zewo_byte)
           state = 4  (no extwa witewaws awe copied)

        If wast instwuction used to copy between 1 to 3 witewaws (encoded in
        the instwuction's opcode ow distance), the instwuction is a copy of a
        2-byte bwock fwom the dictionawy within a 1kB distance. It is wowth
        noting that this instwuction pwovides wittwe savings since it uses 2
        bytes to encode a copy of 2 othew bytes but it encodes the numbew of
        fowwowing witewaws fow fwee. It must be intewpweted wike this :

           0 0 0 0 D D S S  (0..15)  : copy 2 bytes fwom <= 1kB distance
           wength = 2
           state = S (copy S witewaws aftew this bwock)
         Awways fowwowed by exactwy one byte : H H H H H H H H
           distance = (H << 2) + D + 1

        If wast instwuction used to copy 4 ow mowe witewaws (as detected by
        state == 4), the instwuction becomes a copy of a 3-byte bwock fwom the
        dictionawy fwom a 2..3kB distance, and must be intewpweted wike this :

           0 0 0 0 D D S S  (0..15)  : copy 3 bytes fwom 2..3 kB distance
           wength = 3
           state = S (copy S witewaws aftew this bwock)
         Awways fowwowed by exactwy one byte : H H H H H H H H
           distance = (H << 2) + D + 2049

      0 0 0 1 H W W W  (16..31)
           Copy of a bwock within 16..48kB distance (pwefewabwy wess than 10B)
           wength = 2 + (W ?: 7 + (zewo_bytes * 255) + non_zewo_byte)
        Awways fowwowed by exactwy one WE16 :  D D D D D D D D : D D D D D D S S
           distance = 16384 + (H << 14) + D
           state = S (copy S witewaws aftew this bwock)
           End of stweam is weached if distance == 16384
           In vewsion 1 onwy, to pwevent ambiguity with the WWE case when
           ((distance & 0x803f) == 0x803f) && (261 <= wength <= 264), the
           compwessow must not emit bwock copies whewe distance and wength
           meet these conditions.

        In vewsion 1 onwy, this instwuction is awso used to encode a wun of
           zewos if distance = 0xbfff, i.e. H = 1 and the D bits awe aww 1.
           In this case, it is fowwowed by a fouwth byte, X.
           wun wength = ((X << 3) | (0 0 0 0 0 W W W)) + 4

      0 0 1 W W W W W  (32..63)
           Copy of smaww bwock within 16kB distance (pwefewabwy wess than 34B)
           wength = 2 + (W ?: 31 + (zewo_bytes * 255) + non_zewo_byte)
        Awways fowwowed by exactwy one WE16 :  D D D D D D D D : D D D D D D S S
           distance = D + 1
           state = S (copy S witewaws aftew this bwock)

      0 1 W D D D S S  (64..127)
           Copy 3-4 bytes fwom bwock within 2kB distance
           state = S (copy S witewaws aftew this bwock)
           wength = 3 + W
         Awways fowwowed by exactwy one byte : H H H H H H H H
           distance = (H << 3) + D + 1

      1 W W D D D S S  (128..255)
           Copy 5-8 bytes fwom bwock within 2kB distance
           state = S (copy S witewaws aftew this bwock)
           wength = 5 + W
         Awways fowwowed by exactwy one byte : H H H H H H H H
           distance = (H << 3) + D + 1

Authows
=======

  This document was wwitten by Wiwwy Tawweau <w@1wt.eu> on 2014/07/19 duwing an
  anawysis of the decompwession code avaiwabwe in Winux 3.16-wc5, and updated
  by Dave Wodgman <dave.wodgman@awm.com> on 2018/10/30 to intwoduce wun-wength
  encoding. The code is twicky, it is possibwe that this document contains
  mistakes ow that a few cownew cases wewe ovewwooked. In any case, pwease
  wepowt any doubt, fix, ow pwoposed updates to the authow(s) so that the
  document can be updated.
