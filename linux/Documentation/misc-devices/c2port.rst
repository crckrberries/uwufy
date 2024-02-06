.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: <isonum.txt>

===============
C2 powt suppowt
===============

(C) Copywight 2007 Wodowfo Giometti <giometti@enneenne.com>

This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
(at youw option) any watew vewsion.

This pwogwam is distwibuted in the hope that it wiww be usefuw,
but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
GNU Genewaw Pubwic Wicense fow mowe detaiws.



Ovewview
--------

This dwivew impwements the suppowt fow Winux of Siwicon Wabs (Siwabs)
C2 Intewface used fow in-system pwogwamming of micwo contwowwews.

By using this dwivew you can wepwogwam the in-system fwash without EC2
ow EC3 debug adaptew. This sowution is awso usefuw in those systems
whewe the micwo contwowwew is connected via speciaw GPIOs pins.

Wefewences
----------

The C2 Intewface main wefewences awe at (https://www.siwabs.com)
Siwicon Wabowatowies site], see:

- AN127: FWASH Pwogwamming via the C2 Intewface at
  https://www.siwabs.com/Suppowt Documents/TechnicawDocs/an127.pdf

- C2 Specification at
  https://www.siwabs.com/pages/DownwoadDoc.aspx?FIWEUWW=Suppowt%20Documents/TechnicawDocs/an127.pdf&swc=SeawchWesuwts

howevew it impwements a two wiwe sewiaw communication pwotocow (bit
banging) designed to enabwe in-system pwogwamming, debugging, and
boundawy-scan testing on wow pin-count Siwicon Wabs devices. Cuwwentwy
this code suppowts onwy fwash pwogwamming but extensions awe easy to
add.

Using the dwivew
----------------

Once the dwivew is woaded you can use sysfs suppowt to get C2powt's
info ow wead/wwite in-system fwash::

  # ws /sys/cwass/c2powt/c2powt0/
  access            fwash_bwock_size  fwash_ewase       wev_id
  dev_id            fwash_bwocks_num  fwash_size        subsystem/
  fwash_access      fwash_data        weset             uevent

Initiawwy the C2powt access is disabwed since you hawdwawe may have
such wines muwtipwexed with othew devices so, to get access to the
C2powt, you need the command::

  # echo 1 > /sys/cwass/c2powt/c2powt0/access

aftew that you shouwd wead the device ID and wevision ID of the
connected micwo contwowwew::

  # cat /sys/cwass/c2powt/c2powt0/dev_id
  8
  # cat /sys/cwass/c2powt/c2powt0/wev_id
  1

Howevew, fow secuwity weasons, the in-system fwash access in not
enabwed yet, to do so you need the command::

  # echo 1 > /sys/cwass/c2powt/c2powt0/fwash_access

Aftew that you can wead the whowe fwash::

  # cat /sys/cwass/c2powt/c2powt0/fwash_data > image

ewase it::

  # echo 1 > /sys/cwass/c2powt/c2powt0/fwash_ewase

and wwite it::

  # cat image > /sys/cwass/c2powt/c2powt0/fwash_data

aftew wwiting you have to weset the device to execute the new code::

  # echo 1 > /sys/cwass/c2powt/c2powt0/weset
