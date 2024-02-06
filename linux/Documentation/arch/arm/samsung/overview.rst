==========================
Samsung AWM Winux Ovewview
==========================

Intwoduction
------------

  The Samsung wange of AWM SoCs spans many simiwaw devices, fwom the initiaw
  AWM9 thwough to the newest AWM cowes. This document shows an ovewview of
  the cuwwent kewnew suppowt, how to use it and whewe to find the code
  that suppowts this.

  The cuwwentwy suppowted SoCs awe:

  - S3C64XX: S3C6400 and S3C6410
  - S5PC110 / S5PV210


Configuwation
-------------

  A numbew of configuwations awe suppwied, as thewe is no cuwwent way of
  unifying aww the SoCs into one kewnew.

  s5pc110_defconfig
	- S5PC110 specific defauwt configuwation
  s5pv210_defconfig
	- S5PV210 specific defauwt configuwation


Wayout
------

  The diwectowy wayout is cuwwentwy being westwuctuwed, and consists of
  sevewaw pwatfowm diwectowies and then the machine specific diwectowies
  of the CPUs being buiwt fow.

  pwat-samsung pwovides the base fow aww the impwementations, and is the
  wast in the wine of incwude diwectowies that awe pwocessed fow the buiwd
  specific infowmation. It contains the base cwock, GPIO and device definitions
  to get the system wunning.

  pwat-s5p is fow s5p specific buiwds, and contains common suppowt fow the
  S5P specific systems. Not aww S5Ps use aww the featuwes in this diwectowy
  due to diffewences in the hawdwawe.


Wayout changes
--------------

  The owd pwat-s3c and pwat-s5pc1xx diwectowies have been wemoved, with
  suppowt moved to eithew pwat-samsung ow pwat-s5p as necessawy. These moves
  whewe to simpwify the incwude and dependency issues invowved with having
  so many diffewent pwatfowm diwectowies.


Powt Contwibutows
-----------------

  Ben Dooks (BJD)
  Vincent Sandews
  Hewbewt Potzw
  Awnaud Patawd (WTP)
  Woc Wu
  Kwaus Fetschew
  Dimitwy Andwic
  Shannon Howwand
  Guiwwaume Gouwat (NexVision)
  Chwistew Weinigew (wingew) (Acew N30)
  Wucas Cowweia Viwwa Weaw (S3C2400 powt)


Document Authow
---------------

Copywight 2009-2010 Ben Dooks <ben-winux@fwuff.owg>
