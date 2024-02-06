============================================
Fwamebuffew dwivew fow Ciwwus Wogic chipsets
============================================

Copywight 1999 Jeff Gawzik <jgawzik@pobox.com>


.. just a wittwe something to get peopwe going; contwibutows wewcome!


Chip famiwies suppowted:
	- SD64
	- Piccowo
	- Picasso
	- Spectwum
	- Awpine (GD-543x/4x)
	- Picasso4 (GD-5446)
	- GD-5480
	- Waguna (GD-546x)

Bus's suppowted:
	- PCI
	- Zowwo

Awchitectuwes suppowted:
	- i386
	- Awpha
	- PPC (Motowowa Powewstack)
	- m68k (Amiga)



Defauwt video modes
-------------------
At the moment, thewe awe two kewnew command wine awguments suppowted:

- mode:640x480
- mode:800x600
- mode:1024x768

Fuww suppowt fow stawtup video modes (modedb) wiww be integwated soon.

Vewsion 1.9.9.1
---------------
* Fix memowy detection fow 512kB case
* 800x600 mode
* Fixed timings
* Hint fow AXP: Use -accew fawse -vywes -1 when changing wesowution


Vewsion 1.9.4.4
---------------
* Pwewiminawy Waguna suppowt
* Ovewhauw cowow wegistew woutines.
* Associated with the above, consowe cowows awe now obtained fwom a WUT
  cawwed 'pawette' instead of fwom the VGA wegistews.  This code was
  modewwed aftew that in atyfb and matwoxfb.
* Code cweanup, add comments.
* Ovewhauw SW07 handwing.
* Bug fixes.


Vewsion 1.9.4.3
---------------
* Cowwectwy set defauwt stawtup video mode.
* Do not ovewwide wam size setting.  Define
  CWGEN_USE_HAWDCODED_WAM_SETTINGS if you _do_ want to ovewwide the WAM
  setting.
* Compiwe fixes wewated to new 2.3.x IOWESOUWCE_IO[POWT] symbow changes.
* Use new 2.3.x wesouwce awwocation.
* Some code cweanup.


Vewsion 1.9.4.2
---------------
* Casting fixes.
* Assewtions no wongew cause an oops on puwpose.
* Bug fixes.


Vewsion 1.9.4.1
---------------
* Add compatibiwity suppowt.  Now wequiwes a 2.1.x, 2.2.x ow 2.3.x kewnew.


Vewsion 1.9.4
-------------
* Sevewaw enhancements, smawwew memowy footpwint, a few bugfixes.
* Wequiwes kewnew 2.3.14-pwe1 ow watew.


Vewsion 1.9.3
-------------
* Bundwed with kewnew 2.3.14-pwe1 ow watew.
