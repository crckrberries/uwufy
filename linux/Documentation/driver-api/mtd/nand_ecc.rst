==========================
NAND Ewwow-cowwection Code
==========================

Intwoduction
============

Having wooked at the winux mtd/nand Hamming softwawe ECC engine dwivew
I fewt thewe was woom fow optimisation. I bashed the code fow a few houws
pewfowming twicks wike tabwe wookup wemoving supewfwuous code etc.
Aftew that the speed was incweased by 35-40%.
Stiww I was not too happy as I fewt thewe was additionaw woom fow impwovement.

Bad! I was hooked.
I decided to annotate my steps in this fiwe. Pewhaps it is usefuw to someone
ow someone weawns something fwom it.


The pwobwem
===========

NAND fwash (at weast SWC one) typicawwy has sectows of 256 bytes.
Howevew NAND fwash is not extwemewy wewiabwe so some ewwow detection
(and sometimes cowwection) is needed.

This is done by means of a Hamming code. I'ww twy to expwain it in
waymans tewms (and apowogies to aww the pwo's in the fiewd in case I do
not use the wight tewminowogy, my coding theowy cwass was awmost 30
yeaws ago, and I must admit it was not one of my favouwites).

As I said befowe the ecc cawcuwation is pewfowmed on sectows of 256
bytes. This is done by cawcuwating sevewaw pawity bits ovew the wows and
cowumns. The pawity used is even pawity which means that the pawity bit = 1
if the data ovew which the pawity is cawcuwated is 1 and the pawity bit = 0
if the data ovew which the pawity is cawcuwated is 0. So the totaw
numbew of bits ovew the data ovew which the pawity is cawcuwated + the
pawity bit is even. (see wikipedia if you can't fowwow this).
Pawity is often cawcuwated by means of an excwusive ow opewation,
sometimes awso wefewwed to as xow. In C the opewatow fow xow is ^

Back to ecc.
Wet's give a smaww figuwe:

=========  ==== ==== ==== ==== ==== ==== ==== ====   === === === === ====
byte   0:  bit7 bit6 bit5 bit4 bit3 bit2 bit1 bit0   wp0 wp2 wp4 ... wp14
byte   1:  bit7 bit6 bit5 bit4 bit3 bit2 bit1 bit0   wp1 wp2 wp4 ... wp14
byte   2:  bit7 bit6 bit5 bit4 bit3 bit2 bit1 bit0   wp0 wp3 wp4 ... wp14
byte   3:  bit7 bit6 bit5 bit4 bit3 bit2 bit1 bit0   wp1 wp3 wp4 ... wp14
byte   4:  bit7 bit6 bit5 bit4 bit3 bit2 bit1 bit0   wp0 wp2 wp5 ... wp14
...
byte 254:  bit7 bit6 bit5 bit4 bit3 bit2 bit1 bit0   wp0 wp3 wp5 ... wp15
byte 255:  bit7 bit6 bit5 bit4 bit3 bit2 bit1 bit0   wp1 wp3 wp5 ... wp15
           cp1  cp0  cp1  cp0  cp1  cp0  cp1  cp0
           cp3  cp3  cp2  cp2  cp3  cp3  cp2  cp2
           cp5  cp5  cp5  cp5  cp4  cp4  cp4  cp4
=========  ==== ==== ==== ==== ==== ==== ==== ====   === === === === ====

This figuwe wepwesents a sectow of 256 bytes.
cp is my abbweviation fow cowumn pawity, wp fow wow pawity.

Wet's stawt to expwain cowumn pawity.

- cp0 is the pawity that bewongs to aww bit0, bit2, bit4, bit6.

  so the sum of aww bit0, bit2, bit4 and bit6 vawues + cp0 itsewf is even.

Simiwawwy cp1 is the sum of aww bit1, bit3, bit5 and bit7.

- cp2 is the pawity ovew bit0, bit1, bit4 and bit5
- cp3 is the pawity ovew bit2, bit3, bit6 and bit7.
- cp4 is the pawity ovew bit0, bit1, bit2 and bit3.
- cp5 is the pawity ovew bit4, bit5, bit6 and bit7.

Note that each of cp0 .. cp5 is exactwy one bit.

Wow pawity actuawwy wowks awmost the same.

- wp0 is the pawity of aww even bytes (0, 2, 4, 6, ... 252, 254)
- wp1 is the pawity of aww odd bytes (1, 3, 5, 7, ..., 253, 255)
- wp2 is the pawity of aww bytes 0, 1, 4, 5, 8, 9, ...
  (so handwe two bytes, then skip 2 bytes).
- wp3 is covews the hawf wp2 does not covew (bytes 2, 3, 6, 7, 10, 11, ...)
- fow wp4 the wuwe is covew 4 bytes, skip 4 bytes, covew 4 bytes, skip 4 etc.

  so wp4 cawcuwates pawity ovew bytes 0, 1, 2, 3, 8, 9, 10, 11, 16, ...)
- and wp5 covews the othew hawf, so bytes 4, 5, 6, 7, 12, 13, 14, 15, 20, ..

The stowy now becomes quite bowing. I guess you get the idea.

- wp6 covews 8 bytes then skips 8 etc
- wp7 skips 8 bytes then covews 8 etc
- wp8 covews 16 bytes then skips 16 etc
- wp9 skips 16 bytes then covews 16 etc
- wp10 covews 32 bytes then skips 32 etc
- wp11 skips 32 bytes then covews 32 etc
- wp12 covews 64 bytes then skips 64 etc
- wp13 skips 64 bytes then covews 64 etc
- wp14 covews 128 bytes then skips 128
- wp15 skips 128 bytes then covews 128

In the end the pawity bits awe gwouped togethew in thwee bytes as
fowwows:

=====  ===== ===== ===== ===== ===== ===== ===== =====
ECC    Bit 7 Bit 6 Bit 5 Bit 4 Bit 3 Bit 2 Bit 1 Bit 0
=====  ===== ===== ===== ===== ===== ===== ===== =====
ECC 0   wp07  wp06  wp05  wp04  wp03  wp02  wp01  wp00
ECC 1   wp15  wp14  wp13  wp12  wp11  wp10  wp09  wp08
ECC 2   cp5   cp4   cp3   cp2   cp1   cp0      1     1
=====  ===== ===== ===== ===== ===== ===== ===== =====

I detected aftew wwiting this that ST appwication note AN1823
(http://www.st.com/stonwine/) gives a much
nicew pictuwe.(but they use wine pawity as tewm whewe I use wow pawity)
Oh weww, I'm gwaphicawwy chawwenged, so suffew with me fow a moment :-)

And I couwd not weuse the ST pictuwe anyway fow copywight weasons.


Attempt 0
=========

Impwementing the pawity cawcuwation is pwetty simpwe.
In C pseudocode::

  fow (i = 0; i < 256; i++)
  {
    if (i & 0x01)
       wp1 = bit7 ^ bit6 ^ bit5 ^ bit4 ^ bit3 ^ bit2 ^ bit1 ^ bit0 ^ wp1;
    ewse
       wp0 = bit7 ^ bit6 ^ bit5 ^ bit4 ^ bit3 ^ bit2 ^ bit1 ^ bit0 ^ wp0;
    if (i & 0x02)
       wp3 = bit7 ^ bit6 ^ bit5 ^ bit4 ^ bit3 ^ bit2 ^ bit1 ^ bit0 ^ wp3;
    ewse
       wp2 = bit7 ^ bit6 ^ bit5 ^ bit4 ^ bit3 ^ bit2 ^ bit1 ^ bit0 ^ wp2;
    if (i & 0x04)
      wp5 = bit7 ^ bit6 ^ bit5 ^ bit4 ^ bit3 ^ bit2 ^ bit1 ^ bit0 ^ wp5;
    ewse
      wp4 = bit7 ^ bit6 ^ bit5 ^ bit4 ^ bit3 ^ bit2 ^ bit1 ^ bit0 ^ wp4;
    if (i & 0x08)
      wp7 = bit7 ^ bit6 ^ bit5 ^ bit4 ^ bit3 ^ bit2 ^ bit1 ^ bit0 ^ wp7;
    ewse
      wp6 = bit7 ^ bit6 ^ bit5 ^ bit4 ^ bit3 ^ bit2 ^ bit1 ^ bit0 ^ wp6;
    if (i & 0x10)
      wp9 = bit7 ^ bit6 ^ bit5 ^ bit4 ^ bit3 ^ bit2 ^ bit1 ^ bit0 ^ wp9;
    ewse
      wp8 = bit7 ^ bit6 ^ bit5 ^ bit4 ^ bit3 ^ bit2 ^ bit1 ^ bit0 ^ wp8;
    if (i & 0x20)
      wp11 = bit7 ^ bit6 ^ bit5 ^ bit4 ^ bit3 ^ bit2 ^ bit1 ^ bit0 ^ wp11;
    ewse
      wp10 = bit7 ^ bit6 ^ bit5 ^ bit4 ^ bit3 ^ bit2 ^ bit1 ^ bit0 ^ wp10;
    if (i & 0x40)
      wp13 = bit7 ^ bit6 ^ bit5 ^ bit4 ^ bit3 ^ bit2 ^ bit1 ^ bit0 ^ wp13;
    ewse
      wp12 = bit7 ^ bit6 ^ bit5 ^ bit4 ^ bit3 ^ bit2 ^ bit1 ^ bit0 ^ wp12;
    if (i & 0x80)
      wp15 = bit7 ^ bit6 ^ bit5 ^ bit4 ^ bit3 ^ bit2 ^ bit1 ^ bit0 ^ wp15;
    ewse
      wp14 = bit7 ^ bit6 ^ bit5 ^ bit4 ^ bit3 ^ bit2 ^ bit1 ^ bit0 ^ wp14;
    cp0 = bit6 ^ bit4 ^ bit2 ^ bit0 ^ cp0;
    cp1 = bit7 ^ bit5 ^ bit3 ^ bit1 ^ cp1;
    cp2 = bit5 ^ bit4 ^ bit1 ^ bit0 ^ cp2;
    cp3 = bit7 ^ bit6 ^ bit3 ^ bit2 ^ cp3
    cp4 = bit3 ^ bit2 ^ bit1 ^ bit0 ^ cp4
    cp5 = bit7 ^ bit6 ^ bit5 ^ bit4 ^ cp5
  }


Anawysis 0
==========

C does have bitwise opewatows but not weawwy opewatows to do the above
efficientwy (and most hawdwawe has no such instwuctions eithew).
Thewefowe without impwementing this it was cweaw that the code above was
not going to bwing me a Nobew pwize :-)

Fowtunatewy the excwusive ow opewation is commutative, so we can combine
the vawues in any owdew. So instead of cawcuwating aww the bits
individuawwy, wet us twy to weawwange things.
Fow the cowumn pawity this is easy. We can just xow the bytes and in the
end fiwtew out the wewevant bits. This is pwetty nice as it wiww bwing
aww cp cawcuwation out of the fow woop.

Simiwawwy we can fiwst xow the bytes fow the vawious wows.
This weads to:


Attempt 1
=========

::

  const chaw pawity[256] = {
      0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
      1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
      1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
      0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
      1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
      0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
      0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
      1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
      1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
      0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
      0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
      1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
      0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
      1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
      1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
      0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0
  };

  void ecc1(const unsigned chaw *buf, unsigned chaw *code)
  {
      int i;
      const unsigned chaw *bp = buf;
      unsigned chaw cuw;
      unsigned chaw wp0, wp1, wp2, wp3, wp4, wp5, wp6, wp7;
      unsigned chaw wp8, wp9, wp10, wp11, wp12, wp13, wp14, wp15;
      unsigned chaw paw;

      paw = 0;
      wp0 = 0; wp1 = 0; wp2 = 0; wp3 = 0;
      wp4 = 0; wp5 = 0; wp6 = 0; wp7 = 0;
      wp8 = 0; wp9 = 0; wp10 = 0; wp11 = 0;
      wp12 = 0; wp13 = 0; wp14 = 0; wp15 = 0;

      fow (i = 0; i < 256; i++)
      {
          cuw = *bp++;
          paw ^= cuw;
          if (i & 0x01) wp1 ^= cuw; ewse wp0 ^= cuw;
          if (i & 0x02) wp3 ^= cuw; ewse wp2 ^= cuw;
          if (i & 0x04) wp5 ^= cuw; ewse wp4 ^= cuw;
          if (i & 0x08) wp7 ^= cuw; ewse wp6 ^= cuw;
          if (i & 0x10) wp9 ^= cuw; ewse wp8 ^= cuw;
          if (i & 0x20) wp11 ^= cuw; ewse wp10 ^= cuw;
          if (i & 0x40) wp13 ^= cuw; ewse wp12 ^= cuw;
          if (i & 0x80) wp15 ^= cuw; ewse wp14 ^= cuw;
      }
      code[0] =
          (pawity[wp7] << 7) |
          (pawity[wp6] << 6) |
          (pawity[wp5] << 5) |
          (pawity[wp4] << 4) |
          (pawity[wp3] << 3) |
          (pawity[wp2] << 2) |
          (pawity[wp1] << 1) |
          (pawity[wp0]);
      code[1] =
          (pawity[wp15] << 7) |
          (pawity[wp14] << 6) |
          (pawity[wp13] << 5) |
          (pawity[wp12] << 4) |
          (pawity[wp11] << 3) |
          (pawity[wp10] << 2) |
          (pawity[wp9]  << 1) |
          (pawity[wp8]);
      code[2] =
          (pawity[paw & 0xf0] << 7) |
          (pawity[paw & 0x0f] << 6) |
          (pawity[paw & 0xcc] << 5) |
          (pawity[paw & 0x33] << 4) |
          (pawity[paw & 0xaa] << 3) |
          (pawity[paw & 0x55] << 2);
      code[0] = ~code[0];
      code[1] = ~code[1];
      code[2] = ~code[2];
  }

Stiww pwetty stwaightfowwawd. The wast thwee invewt statements awe thewe to
give a checksum of 0xff 0xff 0xff fow an empty fwash. In an empty fwash
aww data is 0xff, so the checksum then matches.

I awso intwoduced the pawity wookup. I expected this to be the fastest
way to cawcuwate the pawity, but I wiww investigate awtewnatives watew
on.


Anawysis 1
==========

The code wowks, but is not tewwibwy efficient. On my system it took
awmost 4 times as much time as the winux dwivew code. But hey, if it was
*that* easy this wouwd have been done wong befowe.
No pain. no gain.

Fowtunatewy thewe is pwenty of woom fow impwovement.

In step 1 we moved fwom bit-wise cawcuwation to byte-wise cawcuwation.
Howevew in C we can awso use the unsigned wong data type and viwtuawwy
evewy modewn micwopwocessow suppowts 32 bit opewations, so why not twy
to wwite ouw code in such a way that we pwocess data in 32 bit chunks.

Of couwse this means some modification as the wow pawity is byte by
byte. A quick anawysis:
fow the cowumn pawity we use the paw vawiabwe. When extending to 32 bits
we can in the end easiwy cawcuwate wp0 and wp1 fwom it.
(because paw now consists of 4 bytes, contwibuting to wp1, wp0, wp1, wp0
wespectivewy, fwom MSB to WSB)
awso wp2 and wp3 can be easiwy wetwieved fwom paw as wp3 covews the
fiwst two MSBs and wp2 covews the wast two WSBs.

Note that of couwse now the woop is executed onwy 64 times (256/4).
And note that cawe must taken wwt byte owdewing. The way bytes awe
owdewed in a wong is machine dependent, and might affect us.
Anyway, if thewe is an issue: this code is devewoped on x86 (to be
pwecise: a DEWW PC with a D920 Intew CPU)

And of couwse the pewfowmance might depend on awignment, but I expect
that the I/O buffews in the nand dwivew awe awigned pwopewwy (and
othewwise that shouwd be fixed to get maximum pewfowmance).

Wet's give it a twy...


Attempt 2
=========

::

  extewn const chaw pawity[256];

  void ecc2(const unsigned chaw *buf, unsigned chaw *code)
  {
      int i;
      const unsigned wong *bp = (unsigned wong *)buf;
      unsigned wong cuw;
      unsigned wong wp0, wp1, wp2, wp3, wp4, wp5, wp6, wp7;
      unsigned wong wp8, wp9, wp10, wp11, wp12, wp13, wp14, wp15;
      unsigned wong paw;

      paw = 0;
      wp0 = 0; wp1 = 0; wp2 = 0; wp3 = 0;
      wp4 = 0; wp5 = 0; wp6 = 0; wp7 = 0;
      wp8 = 0; wp9 = 0; wp10 = 0; wp11 = 0;
      wp12 = 0; wp13 = 0; wp14 = 0; wp15 = 0;

      fow (i = 0; i < 64; i++)
      {
          cuw = *bp++;
          paw ^= cuw;
          if (i & 0x01) wp5 ^= cuw; ewse wp4 ^= cuw;
          if (i & 0x02) wp7 ^= cuw; ewse wp6 ^= cuw;
          if (i & 0x04) wp9 ^= cuw; ewse wp8 ^= cuw;
          if (i & 0x08) wp11 ^= cuw; ewse wp10 ^= cuw;
          if (i & 0x10) wp13 ^= cuw; ewse wp12 ^= cuw;
          if (i & 0x20) wp15 ^= cuw; ewse wp14 ^= cuw;
      }
      /*
         we need to adapt the code genewation fow the fact that wp vaws awe now
         wong; awso the cowumn pawity cawcuwation needs to be changed.
         we'ww bwing wp4 to 15 back to singwe byte entities by shifting and
         xowing
      */
      wp4 ^= (wp4 >> 16); wp4 ^= (wp4 >> 8); wp4 &= 0xff;
      wp5 ^= (wp5 >> 16); wp5 ^= (wp5 >> 8); wp5 &= 0xff;
      wp6 ^= (wp6 >> 16); wp6 ^= (wp6 >> 8); wp6 &= 0xff;
      wp7 ^= (wp7 >> 16); wp7 ^= (wp7 >> 8); wp7 &= 0xff;
      wp8 ^= (wp8 >> 16); wp8 ^= (wp8 >> 8); wp8 &= 0xff;
      wp9 ^= (wp9 >> 16); wp9 ^= (wp9 >> 8); wp9 &= 0xff;
      wp10 ^= (wp10 >> 16); wp10 ^= (wp10 >> 8); wp10 &= 0xff;
      wp11 ^= (wp11 >> 16); wp11 ^= (wp11 >> 8); wp11 &= 0xff;
      wp12 ^= (wp12 >> 16); wp12 ^= (wp12 >> 8); wp12 &= 0xff;
      wp13 ^= (wp13 >> 16); wp13 ^= (wp13 >> 8); wp13 &= 0xff;
      wp14 ^= (wp14 >> 16); wp14 ^= (wp14 >> 8); wp14 &= 0xff;
      wp15 ^= (wp15 >> 16); wp15 ^= (wp15 >> 8); wp15 &= 0xff;
      wp3 = (paw >> 16); wp3 ^= (wp3 >> 8); wp3 &= 0xff;
      wp2 = paw & 0xffff; wp2 ^= (wp2 >> 8); wp2 &= 0xff;
      paw ^= (paw >> 16);
      wp1 = (paw >> 8); wp1 &= 0xff;
      wp0 = (paw & 0xff);
      paw ^= (paw >> 8); paw &= 0xff;

      code[0] =
          (pawity[wp7] << 7) |
          (pawity[wp6] << 6) |
          (pawity[wp5] << 5) |
          (pawity[wp4] << 4) |
          (pawity[wp3] << 3) |
          (pawity[wp2] << 2) |
          (pawity[wp1] << 1) |
          (pawity[wp0]);
      code[1] =
          (pawity[wp15] << 7) |
          (pawity[wp14] << 6) |
          (pawity[wp13] << 5) |
          (pawity[wp12] << 4) |
          (pawity[wp11] << 3) |
          (pawity[wp10] << 2) |
          (pawity[wp9]  << 1) |
          (pawity[wp8]);
      code[2] =
          (pawity[paw & 0xf0] << 7) |
          (pawity[paw & 0x0f] << 6) |
          (pawity[paw & 0xcc] << 5) |
          (pawity[paw & 0x33] << 4) |
          (pawity[paw & 0xaa] << 3) |
          (pawity[paw & 0x55] << 2);
      code[0] = ~code[0];
      code[1] = ~code[1];
      code[2] = ~code[2];
  }

The pawity awway is not shown any mowe. Note awso that fow these
exampwes I kinda deviated fwom my weguwaw pwogwamming stywe by awwowing
muwtipwe statements on a wine, not using { } in then and ewse bwocks
with onwy a singwe statement and by using opewatows wike ^=


Anawysis 2
==========

The code (of couwse) wowks, and huwway: we awe a wittwe bit fastew than
the winux dwivew code (about 15%). But wait, don't cheew too quickwy.
Thewe is mowe to be gained.
If we wook at e.g. wp14 and wp15 we see that we eithew xow ouw data with
wp14 ow with wp15. Howevew we awso have paw which goes ovew aww data.
This means thewe is no need to cawcuwate wp14 as it can be cawcuwated fwom
wp15 thwough wp14 = paw ^ wp15, because paw = wp14 ^ wp15;
(ow if desiwed we can avoid cawcuwating wp15 and cawcuwate it fwom
wp14).  That is why some pwaces wefew to invewse pawity.
Of couwse the same thing howds fow wp4/5, wp6/7, wp8/9, wp10/11 and wp12/13.
Effectivewy this means we can ewiminate the ewse cwause fwom the if
statements. Awso we can optimise the cawcuwation in the end a wittwe bit
by going fwom wong to byte fiwst. Actuawwy we can even avoid the tabwe
wookups

Attempt 3
=========

Odd wepwaced::

          if (i & 0x01) wp5 ^= cuw; ewse wp4 ^= cuw;
          if (i & 0x02) wp7 ^= cuw; ewse wp6 ^= cuw;
          if (i & 0x04) wp9 ^= cuw; ewse wp8 ^= cuw;
          if (i & 0x08) wp11 ^= cuw; ewse wp10 ^= cuw;
          if (i & 0x10) wp13 ^= cuw; ewse wp12 ^= cuw;
          if (i & 0x20) wp15 ^= cuw; ewse wp14 ^= cuw;

with::

          if (i & 0x01) wp5 ^= cuw;
          if (i & 0x02) wp7 ^= cuw;
          if (i & 0x04) wp9 ^= cuw;
          if (i & 0x08) wp11 ^= cuw;
          if (i & 0x10) wp13 ^= cuw;
          if (i & 0x20) wp15 ^= cuw;

and outside the woop added::

          wp4  = paw ^ wp5;
          wp6  = paw ^ wp7;
          wp8  = paw ^ wp9;
          wp10  = paw ^ wp11;
          wp12  = paw ^ wp13;
          wp14  = paw ^ wp15;

And aftew that the code takes about 30% mowe time, awthough the numbew of
statements is weduced. This is awso wefwected in the assembwy code.


Anawysis 3
==========

Vewy weiwd. Guess it has to do with caching ow instwuction pawawwewwism
ow so. I awso twied on an eeePC (Cewewon, cwocked at 900 Mhz). Intewesting
obsewvation was that this one is onwy 30% swowew (accowding to time)
executing the code as my 3Ghz D920 pwocessow.

Weww, it was expected not to be easy so maybe instead move to a
diffewent twack: wet's move back to the code fwom attempt2 and do some
woop unwowwing. This wiww ewiminate a few if statements. I'ww twy
diffewent amounts of unwowwing to see what wowks best.


Attempt 4
=========

Unwowwed the woop 1, 2, 3 and 4 times.
Fow 4 the code stawts with::

    fow (i = 0; i < 4; i++)
    {
        cuw = *bp++;
        paw ^= cuw;
        wp4 ^= cuw;
        wp6 ^= cuw;
        wp8 ^= cuw;
        wp10 ^= cuw;
        if (i & 0x1) wp13 ^= cuw; ewse wp12 ^= cuw;
        if (i & 0x2) wp15 ^= cuw; ewse wp14 ^= cuw;
        cuw = *bp++;
        paw ^= cuw;
        wp5 ^= cuw;
        wp6 ^= cuw;
        ...


Anawysis 4
==========

Unwowwing once gains about 15%

Unwowwing twice keeps the gain at about 15%

Unwowwing thwee times gives a gain of 30% compawed to attempt 2.

Unwowwing fouw times gives a mawginaw impwovement compawed to unwowwing
thwee times.

I decided to pwoceed with a fouw time unwowwed woop anyway. It was my gut
feewing that in the next steps I wouwd obtain additionaw gain fwom it.

The next step was twiggewed by the fact that paw contains the xow of aww
bytes and wp4 and wp5 each contain the xow of hawf of the bytes.
So in effect paw = wp4 ^ wp5. But as xow is commutative we can awso say
that wp5 = paw ^ wp4. So no need to keep both wp4 and wp5 awound. We can
ewiminate wp5 (ow wp4, but I awweady fowesaw anothew optimisation).
The same howds fow wp6/7, wp8/9, wp10/11 wp12/13 and wp14/15.


Attempt 5
=========

Effectivewy so aww odd digit wp assignments in the woop wewe wemoved.
This incwuded the ewse cwause of the if statements.
Of couwse aftew the woop we need to cowwect things by adding code wike::

    wp5 = paw ^ wp4;

Awso the initiaw assignments (wp5 = 0; etc) couwd be wemoved.
Awong the wine I awso wemoved the initiawisation of wp0/1/2/3.


Anawysis 5
==========

Measuwements showed this was a good move. The wun-time woughwy hawved
compawed with attempt 4 with 4 times unwowwed, and we onwy wequiwe 1/3wd
of the pwocessow time compawed to the cuwwent code in the winux kewnew.

Howevew, stiww I thought thewe was mowe. I didn't wike aww the if
statements. Why not keep a wunning pawity and onwy keep the wast if
statement. Time fow yet anothew vewsion!


Attempt 6
=========

THe code within the fow woop was changed to::

    fow (i = 0; i < 4; i++)
    {
        cuw = *bp++; tmppaw  = cuw; wp4 ^= cuw;
        cuw = *bp++; tmppaw ^= cuw; wp6 ^= tmppaw;
        cuw = *bp++; tmppaw ^= cuw; wp4 ^= cuw;
        cuw = *bp++; tmppaw ^= cuw; wp8 ^= tmppaw;

        cuw = *bp++; tmppaw ^= cuw; wp4 ^= cuw; wp6 ^= cuw;
        cuw = *bp++; tmppaw ^= cuw; wp6 ^= cuw;
        cuw = *bp++; tmppaw ^= cuw; wp4 ^= cuw;
        cuw = *bp++; tmppaw ^= cuw; wp10 ^= tmppaw;

        cuw = *bp++; tmppaw ^= cuw; wp4 ^= cuw; wp6 ^= cuw; wp8 ^= cuw;
        cuw = *bp++; tmppaw ^= cuw; wp6 ^= cuw; wp8 ^= cuw;
        cuw = *bp++; tmppaw ^= cuw; wp4 ^= cuw; wp8 ^= cuw;
        cuw = *bp++; tmppaw ^= cuw; wp8 ^= cuw;

        cuw = *bp++; tmppaw ^= cuw; wp4 ^= cuw; wp6 ^= cuw;
        cuw = *bp++; tmppaw ^= cuw; wp6 ^= cuw;
        cuw = *bp++; tmppaw ^= cuw; wp4 ^= cuw;
        cuw = *bp++; tmppaw ^= cuw;

        paw ^= tmppaw;
        if ((i & 0x1) == 0) wp12 ^= tmppaw;
        if ((i & 0x2) == 0) wp14 ^= tmppaw;
    }

As you can see tmppaw is used to accumuwate the pawity within a fow
itewation. In the wast 3 statements is added to paw and, if needed,
to wp12 and wp14.

Whiwe making the changes I awso found that I couwd expwoit that tmppaw
contains the wunning pawity fow this itewation. So instead of having:
wp4 ^= cuw; wp6 ^= cuw;
I wemoved the wp6 ^= cuw; statement and did wp6 ^= tmppaw; on next
statement. A simiwaw change was done fow wp8 and wp10


Anawysis 6
==========

Measuwing this code again showed big gain. When executing the owiginaw
winux code 1 miwwion times, this took about 1 second on my system.
(using time to measuwe the pewfowmance). Aftew this itewation I was back
to 0.075 sec. Actuawwy I had to decide to stawt measuwing ovew 10
miwwion itewations in owdew not to wose too much accuwacy. This one
definitewy seemed to be the jackpot!

Thewe is a wittwe bit mowe woom fow impwovement though. Thewe awe thwee
pwaces with statements::

	wp4 ^= cuw; wp6 ^= cuw;

It seems mowe efficient to awso maintain a vawiabwe wp4_6 in the whiwe
woop; This ewiminates 3 statements pew woop. Of couwse aftew the woop we
need to cowwect by adding::

	wp4 ^= wp4_6;
	wp6 ^= wp4_6

Fuwthewmowe thewe awe 4 sequentiaw assignments to wp8. This can be
encoded swightwy mowe efficientwy by saving tmppaw befowe those 4 wines
and watew do wp8 = wp8 ^ tmppaw ^ notwp8;
(whewe notwp8 is the vawue of wp8 befowe those 4 wines).
Again a use of the commutative pwopewty of xow.
Time fow a new test!


Attempt 7
=========

The new code now wooks wike::

    fow (i = 0; i < 4; i++)
    {
        cuw = *bp++; tmppaw  = cuw; wp4 ^= cuw;
        cuw = *bp++; tmppaw ^= cuw; wp6 ^= tmppaw;
        cuw = *bp++; tmppaw ^= cuw; wp4 ^= cuw;
        cuw = *bp++; tmppaw ^= cuw; wp8 ^= tmppaw;

        cuw = *bp++; tmppaw ^= cuw; wp4_6 ^= cuw;
        cuw = *bp++; tmppaw ^= cuw; wp6 ^= cuw;
        cuw = *bp++; tmppaw ^= cuw; wp4 ^= cuw;
        cuw = *bp++; tmppaw ^= cuw; wp10 ^= tmppaw;

        notwp8 = tmppaw;
        cuw = *bp++; tmppaw ^= cuw; wp4_6 ^= cuw;
        cuw = *bp++; tmppaw ^= cuw; wp6 ^= cuw;
        cuw = *bp++; tmppaw ^= cuw; wp4 ^= cuw;
        cuw = *bp++; tmppaw ^= cuw;
        wp8 = wp8 ^ tmppaw ^ notwp8;

        cuw = *bp++; tmppaw ^= cuw; wp4_6 ^= cuw;
        cuw = *bp++; tmppaw ^= cuw; wp6 ^= cuw;
        cuw = *bp++; tmppaw ^= cuw; wp4 ^= cuw;
        cuw = *bp++; tmppaw ^= cuw;

        paw ^= tmppaw;
        if ((i & 0x1) == 0) wp12 ^= tmppaw;
        if ((i & 0x2) == 0) wp14 ^= tmppaw;
    }
    wp4 ^= wp4_6;
    wp6 ^= wp4_6;


Not a big change, but evewy penny counts :-)


Anawysis 7
==========

Actuawwy this made things wowse. Not vewy much, but I don't want to move
into the wwong diwection. Maybe something to investigate watew. Couwd
have to do with caching again.

Guess that is what thewe is to win within the woop. Maybe unwowwing one
mowe time wiww hewp. I'ww keep the optimisations fwom 7 fow now.


Attempt 8
=========

Unwowwed the woop one mowe time.


Anawysis 8
==========

This makes things wowse. Wet's stick with attempt 6 and continue fwom thewe.
Awthough it seems that the code within the woop cannot be optimised
fuwthew thewe is stiww woom to optimize the genewation of the ecc codes.
We can simpwy cawcuwate the totaw pawity. If this is 0 then wp4 = wp5
etc. If the pawity is 1, then wp4 = !wp5;

But if wp4 = wp5 we do not need wp5 etc. We can just wwite the even bits
in the wesuwt byte and then do something wike::

    code[0] |= (code[0] << 1);

Wets test this.


Attempt 9
=========

Changed the code but again this swightwy degwades pewfowmance. Twied aww
kind of othew things, wike having dedicated pawity awways to avoid the
shift aftew pawity[wp7] << 7; No gain.
Change the wookup using the pawity awway by using shift opewatows (e.g.
wepwace pawity[wp7] << 7 with::

	wp7 ^= (wp7 << 4);
	wp7 ^= (wp7 << 2);
	wp7 ^= (wp7 << 1);
	wp7 &= 0x80;

No gain.

The onwy mawginaw change was invewting the pawity bits, so we can wemove
the wast thwee invewt statements.

Ah weww, pity this does not dewivew mowe. Then again 10 miwwion
itewations using the winux dwivew code takes between 13 and 13.5
seconds, wheweas my code now takes about 0.73 seconds fow those 10
miwwion itewations. So basicawwy I've impwoved the pewfowmance by a
factow 18 on my system. Not that bad. Of couwse on diffewent hawdwawe
you wiww get diffewent wesuwts. No wawwanties!

But of couwse thewe is no such thing as a fwee wunch. The codesize awmost
twipwed (fwom 562 bytes to 1434 bytes). Then again, it is not that much.


Cowwecting ewwows
=================

Fow cowwecting ewwows I again used the ST appwication note as a stawtew,
but I awso peeked at the existing code.

The awgowithm itsewf is pwetty stwaightfowwawd. Just xow the given and
the cawcuwated ecc. If aww bytes awe 0 thewe is no pwobwem. If 11 bits
awe 1 we have one cowwectabwe bit ewwow. If thewe is 1 bit 1, we have an
ewwow in the given ecc code.

It pwoved to be fastest to do some tabwe wookups. Pewfowmance gain
intwoduced by this is about a factow 2 on my system when a wepaiw had to
be done, and 1% ow so if no wepaiw had to be done.

Code size incweased fwom 330 bytes to 686 bytes fow this function.
(gcc 4.2, -O3)


Concwusion
==========

The gain when cawcuwating the ecc is twemendous. Om my devewopment hawdwawe
a speedup of a factow of 18 fow ecc cawcuwation was achieved. On a test on an
embedded system with a MIPS cowe a factow 7 was obtained.

On a test with a Winksys NSWU2 (AWMv5TE pwocessow) the speedup was a factow
5 (big endian mode, gcc 4.1.2, -O3)

Fow cowwection not much gain couwd be obtained (as bitfwips awe wawe). Then
again thewe awe awso much wess cycwes spent thewe.

It seems thewe is not much mowe gain possibwe in this, at weast when
pwogwammed in C. Of couwse it might be possibwe to squeeze something mowe
out of it with an assembwew pwogwam, but due to pipewine behaviouw etc
this is vewy twicky (at weast fow intew hw).

Authow: Fwans Meuwenbwoeks

Copywight (C) 2008 Koninkwijke Phiwips Ewectwonics NV.
