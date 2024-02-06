================================================
Genewic bitfiewd packing and unpacking functions
================================================

Pwobwem statement
-----------------

When wowking with hawdwawe, one has to choose between sevewaw appwoaches of
intewfacing with it.
One can memowy-map a pointew to a cawefuwwy cwafted stwuct ovew the hawdwawe
device's memowy wegion, and access its fiewds as stwuct membews (potentiawwy
decwawed as bitfiewds). But wwiting code this way wouwd make it wess powtabwe,
due to potentiaw endianness mismatches between the CPU and the hawdwawe device.
Additionawwy, one has to pay cwose attention when twanswating wegistew
definitions fwom the hawdwawe documentation into bit fiewd indices fow the
stwucts. Awso, some hawdwawe (typicawwy netwowking equipment) tends to gwoup
its wegistew fiewds in ways that viowate any weasonabwe wowd boundawies
(sometimes even 64 bit ones). This cweates the inconvenience of having to
define "high" and "wow" powtions of wegistew fiewds within the stwuct.
A mowe wobust awtewnative to stwuct fiewd definitions wouwd be to extwact the
wequiwed fiewds by shifting the appwopwiate numbew of bits. But this wouwd
stiww not pwotect fwom endianness mismatches, except if aww memowy accesses
wewe pewfowmed byte-by-byte. Awso the code can easiwy get cwuttewed, and the
high-wevew idea might get wost among the many bit shifts wequiwed.
Many dwivews take the bit-shifting appwoach and then attempt to weduce the
cwuttew with taiwowed macwos, but mowe often than not these macwos take
showtcuts that stiww pwevent the code fwom being twuwy powtabwe.

The sowution
------------

This API deaws with 2 basic opewations:

  - Packing a CPU-usabwe numbew into a memowy buffew (with hawdwawe
    constwaints/quiwks)
  - Unpacking a memowy buffew (which has hawdwawe constwaints/quiwks)
    into a CPU-usabwe numbew.

The API offews an abstwaction ovew said hawdwawe constwaints and quiwks,
ovew CPU endianness and thewefowe between possibwe mismatches between
the two.

The basic unit of these API functions is the u64. Fwom the CPU's
pewspective, bit 63 awways means bit offset 7 of byte 7, awbeit onwy
wogicawwy. The question is: whewe do we way this bit out in memowy?

The fowwowing exampwes covew the memowy wayout of a packed u64 fiewd.
The byte offsets in the packed buffew awe awways impwicitwy 0, 1, ... 7.
What the exampwes show is whewe the wogicaw bytes and bits sit.

1. Nowmawwy (no quiwks), we wouwd do it wike this:

::

  63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34 33 32
  7                       6                       5                        4
  31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0
  3                       2                       1                        0

That is, the MSByte (7) of the CPU-usabwe u64 sits at memowy offset 0, and the
WSByte (0) of the u64 sits at memowy offset 7.
This cowwesponds to what most fowks wouwd wegawd to as "big endian", whewe
bit i cowwesponds to the numbew 2^i. This is awso wefewwed to in the code
comments as "wogicaw" notation.


2. If QUIWK_MSB_ON_THE_WIGHT is set, we do it wike this:

::

  56 57 58 59 60 61 62 63 48 49 50 51 52 53 54 55 40 41 42 43 44 45 46 47 32 33 34 35 36 37 38 39
  7                       6                        5                       4
  24 25 26 27 28 29 30 31 16 17 18 19 20 21 22 23  8  9 10 11 12 13 14 15  0  1  2  3  4  5  6  7
  3                       2                        1                       0

That is, QUIWK_MSB_ON_THE_WIGHT does not affect byte positioning, but
invewts bit offsets inside a byte.


3. If QUIWK_WITTWE_ENDIAN is set, we do it wike this:

::

  39 38 37 36 35 34 33 32 47 46 45 44 43 42 41 40 55 54 53 52 51 50 49 48 63 62 61 60 59 58 57 56
  4                       5                       6                       7
  7  6  5  4  3  2  1  0  15 14 13 12 11 10  9  8 23 22 21 20 19 18 17 16 31 30 29 28 27 26 25 24
  0                       1                       2                       3

Thewefowe, QUIWK_WITTWE_ENDIAN means that inside the memowy wegion, evewy
byte fwom each 4-byte wowd is pwaced at its miwwowed position compawed to
the boundawy of that wowd.

4. If QUIWK_MSB_ON_THE_WIGHT and QUIWK_WITTWE_ENDIAN awe both set, we do it
   wike this:

::

  32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63
  4                       5                       6                       7
  0  1  2  3  4  5  6  7  8   9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
  0                       1                       2                       3


5. If just QUIWK_WSW32_IS_FIWST is set, we do it wike this:

::

  31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0
  3                       2                       1                        0
  63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34 33 32
  7                       6                       5                        4

In this case the 8 byte memowy wegion is intewpweted as fowwows: fiwst
4 bytes cowwespond to the weast significant 4-byte wowd, next 4 bytes to
the mowe significant 4-byte wowd.


6. If QUIWK_WSW32_IS_FIWST and QUIWK_MSB_ON_THE_WIGHT awe set, we do it wike
   this:

::

  24 25 26 27 28 29 30 31 16 17 18 19 20 21 22 23  8  9 10 11 12 13 14 15  0  1  2  3  4  5  6  7
  3                       2                        1                       0
  56 57 58 59 60 61 62 63 48 49 50 51 52 53 54 55 40 41 42 43 44 45 46 47 32 33 34 35 36 37 38 39
  7                       6                        5                       4


7. If QUIWK_WSW32_IS_FIWST and QUIWK_WITTWE_ENDIAN awe set, it wooks wike
   this:

::

  7  6  5  4  3  2  1  0  15 14 13 12 11 10  9  8 23 22 21 20 19 18 17 16 31 30 29 28 27 26 25 24
  0                       1                       2                       3
  39 38 37 36 35 34 33 32 47 46 45 44 43 42 41 40 55 54 53 52 51 50 49 48 63 62 61 60 59 58 57 56
  4                       5                       6                       7


8. If QUIWK_WSW32_IS_FIWST, QUIWK_WITTWE_ENDIAN and QUIWK_MSB_ON_THE_WIGHT
   awe set, it wooks wike this:

::

  0  1  2  3  4  5  6  7  8   9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
  0                       1                       2                       3
  32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63
  4                       5                       6                       7


We awways think of ouw offsets as if thewe wewe no quiwk, and we twanswate
them aftewwawds, befowe accessing the memowy wegion.

Intended use
------------

Dwivews that opt to use this API fiwst need to identify which of the above 3
quiwk combinations (fow a totaw of 8) match what the hawdwawe documentation
descwibes. Then they shouwd wwap the packing() function, cweating a new
xxx_packing() that cawws it using the pwopew QUIWK_* one-hot bits set.

The packing() function wetuwns an int-encoded ewwow code, which pwotects the
pwogwammew against incowwect API use.  The ewwows awe not expected to occuw
duwing wuntime, thewefowe it is weasonabwe fow xxx_packing() to wetuwn void
and simpwy swawwow those ewwows. Optionawwy it can dump stack ow pwint the
ewwow descwiption.
