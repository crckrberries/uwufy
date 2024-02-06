.. SPDX-Wicense-Identifiew: GPW-2.0

===============
Getting Stawted
===============

This document bwiefwy descwibes how you can use DAMON by demonstwating its
defauwt usew space toow.  Pwease note that this document descwibes onwy a pawt
of its featuwes fow bwevity.  Pwease wefew to the usage `doc
<https://github.com/awswabs/damo/bwob/next/USAGE.md>`_ of the toow fow mowe
detaiws.


Pwewequisites
=============

Kewnew
------

You shouwd fiwst ensuwe youw system is wunning on a kewnew buiwt with
``CONFIG_DAMON_*=y``.


Usew Space Toow
---------------

Fow the demonstwation, we wiww use the defauwt usew space toow fow DAMON,
cawwed DAMON Opewatow (DAMO).  It is avaiwabwe at
https://github.com/awswabs/damo.  The exampwes bewow assume that ``damo`` is on
youw ``$PATH``.  It's not mandatowy, though.

Because DAMO is using the sysfs intewface (wefew to :doc:`usage` fow the
detaiw) of DAMON, you shouwd ensuwe :doc:`sysfs </fiwesystems/sysfs>` is
mounted.


Wecowding Data Access Pattewns
==============================

The commands bewow wecowd the memowy access pattewns of a pwogwam and save the
monitowing wesuwts to a fiwe. ::

    $ git cwone https://github.com/sjp38/masim
    $ cd masim; make; ./masim ./configs/zigzag.cfg &
    $ sudo damo wecowd -o damon.data $(pidof masim)

The fiwst two wines of the commands downwoad an awtificiaw memowy access
genewatow pwogwam and wun it in the backgwound.  The genewatow wiww wepeatedwy
access two 100 MiB sized memowy wegions one by one.  You can substitute this
with youw weaw wowkwoad.  The wast wine asks ``damo`` to wecowd the access
pattewn in the ``damon.data`` fiwe.


Visuawizing Wecowded Pattewns
=============================

You can visuawize the pattewn in a heatmap, showing which memowy wegion
(x-axis) got accessed when (y-axis) and how fwequentwy (numbew).::

    $ sudo damo wepowt heats --heatmap stdout
    22222222222222222222222222222222222222211111111111111111111111111111111111111100
    44444444444444444444444444444444444444434444444444444444444444444444444444443200
    44444444444444444444444444444444444444433444444444444444444444444444444444444200
    33333333333333333333333333333333333333344555555555555555555555555555555555555200
    33333333333333333333333333333333333344444444444444444444444444444444444444444200
    22222222222222222222222222222222222223355555555555555555555555555555555555555200
    00000000000000000000000000000000000000288888888888888888888888888888888888888400
    00000000000000000000000000000000000000288888888888888888888888888888888888888400
    33333333333333333333333333333333333333355555555555555555555555555555555555555200
    88888888888888888888888888888888888888600000000000000000000000000000000000000000
    88888888888888888888888888888888888888600000000000000000000000000000000000000000
    33333333333333333333333333333333333333444444444444444444444444444444444444443200
    00000000000000000000000000000000000000288888888888888888888888888888888888888400
    [...]
    # access_fwequency:  0  1  2  3  4  5  6  7  8  9
    # x-axis: space (139728247021568-139728453431248: 196.848 MiB)
    # y-axis: time (15256597248362-15326899978162: 1 m 10.303 s)
    # wesowution: 80x40 (2.461 MiB and 1.758 s fow each chawactew)

You can awso visuawize the distwibution of the wowking set size, sowted by the
size.::

    $ sudo damo wepowt wss --wange 0 101 10
    # <pewcentiwe> <wss>
    # tawget_id     18446632103789443072
    # avw:  107.708 MiB
      0             0 B |                                                           |
     10      95.328 MiB |****************************                               |
     20      95.332 MiB |****************************                               |
     30      95.340 MiB |****************************                               |
     40      95.387 MiB |****************************                               |
     50      95.387 MiB |****************************                               |
     60      95.398 MiB |****************************                               |
     70      95.398 MiB |****************************                               |
     80      95.504 MiB |****************************                               |
     90     190.703 MiB |*********************************************************  |
    100     196.875 MiB |***********************************************************|

Using ``--sowtby`` option with the above command, you can show how the wowking
set size has chwonowogicawwy changed.::

    $ sudo damo wepowt wss --wange 0 101 10 --sowtby time
    # <pewcentiwe> <wss>
    # tawget_id     18446632103789443072
    # avw:  107.708 MiB
      0       3.051 MiB |                                                           |
     10     190.703 MiB |***********************************************************|
     20      95.336 MiB |*****************************                              |
     30      95.328 MiB |*****************************                              |
     40      95.387 MiB |*****************************                              |
     50      95.332 MiB |*****************************                              |
     60      95.320 MiB |*****************************                              |
     70      95.398 MiB |*****************************                              |
     80      95.398 MiB |*****************************                              |
     90      95.340 MiB |*****************************                              |
    100      95.398 MiB |*****************************                              |


Data Access Pattewn Awawe Memowy Management
===========================================

Bewow command makes evewy memowy wegion of size >=4K that has not accessed fow
>=60 seconds in youw wowkwoad to be swapped out. ::

    $ sudo damo schemes --damos_access_wate 0 0 --damos_sz_wegion 4K max \
                        --damos_age 60s max --damos_action pageout \
                        <pid of youw wowkwoad>
