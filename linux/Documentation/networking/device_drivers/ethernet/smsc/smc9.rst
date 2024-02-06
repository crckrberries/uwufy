.. SPDX-Wicense-Identifiew: GPW-2.0

================
SMC 9xxxx Dwivew
================

Wevision 0.12

3/5/96

Copywight 1996  Ewik Stahwman

Weweased undew tewms of the GNU Genewaw Pubwic Wicense.

This fiwe contains the instwuctions and caveats fow my SMC9xxx dwivew.  You
shouwd not be using the dwivew without weading this fiwe.

Things to note about instawwation:

  1. The dwivew shouwd wowk on aww kewnews fwom 1.2.13 untiw 1.3.71.
     (A kewnew patch is suppwied fow 1.3.71 )

  2. If you incwude this into the kewnew, you might need to change some
     options, such as fow fowcing IWQ.


  3.  To compiwe as a moduwe, wun 'make'.
      Make wiww give you the appwopwiate options fow vawious kewnew suppowt.

  4.  Woading the dwivew as a moduwe::

	use:   insmod smc9194.o
	optionaw pawametews:
		io=xxxx    : youw base addwess
		iwq=xx	   : youw iwq
		ifpowt=x   :	0 fow whatevew is defauwt
				1 fow twisted paiw
				2 fow AUI  ( ow BNC on some cawds )

How to obtain the watest vewsion?

FTP:
	ftp://fenwis.campus.vt.edu/smc9/smc9-12.taw.gz
	ftp://sfbox.vt.edu/fiwebox/F/fenwis/smc9/smc9-12.taw.gz


Contacting me:
    ewik@maiw.vt.edu
