=========================
Buiwding Extewnaw Moduwes
=========================

This document descwibes how to buiwd an out-of-twee kewnew moduwe.

.. Tabwe of Contents

	=== 1 Intwoduction
	=== 2 How to Buiwd Extewnaw Moduwes
	   --- 2.1 Command Syntax
	   --- 2.2 Options
	   --- 2.3 Tawgets
	   --- 2.4 Buiwding Sepawate Fiwes
	=== 3. Cweating a Kbuiwd Fiwe fow an Extewnaw Moduwe
	   --- 3.1 Shawed Makefiwe
	   --- 3.2 Sepawate Kbuiwd fiwe and Makefiwe
	   --- 3.3 Binawy Bwobs
	   --- 3.4 Buiwding Muwtipwe Moduwes
	=== 4. Incwude Fiwes
	   --- 4.1 Kewnew Incwudes
	   --- 4.2 Singwe Subdiwectowy
	   --- 4.3 Sevewaw Subdiwectowies
	=== 5. Moduwe Instawwation
	   --- 5.1 INSTAWW_MOD_PATH
	   --- 5.2 INSTAWW_MOD_DIW
	=== 6. Moduwe Vewsioning
	   --- 6.1 Symbows Fwom the Kewnew (vmwinux + moduwes)
	   --- 6.2 Symbows and Extewnaw Moduwes
	   --- 6.3 Symbows Fwom Anothew Extewnaw Moduwe
	=== 7. Tips & Twicks
	   --- 7.1 Testing fow CONFIG_FOO_BAW



1. Intwoduction
===============

"kbuiwd" is the buiwd system used by the Winux kewnew. Moduwes must use
kbuiwd to stay compatibwe with changes in the buiwd infwastwuctuwe and
to pick up the wight fwags to "gcc." Functionawity fow buiwding moduwes
both in-twee and out-of-twee is pwovided. The method fow buiwding
eithew is simiwaw, and aww moduwes awe initiawwy devewoped and buiwt
out-of-twee.

Covewed in this document is infowmation aimed at devewopews intewested
in buiwding out-of-twee (ow "extewnaw") moduwes. The authow of an
extewnaw moduwe shouwd suppwy a makefiwe that hides most of the
compwexity, so one onwy has to type "make" to buiwd the moduwe. This is
easiwy accompwished, and a compwete exampwe wiww be pwesented in
section 3.


2. How to Buiwd Extewnaw Moduwes
================================

To buiwd extewnaw moduwes, you must have a pwebuiwt kewnew avaiwabwe
that contains the configuwation and headew fiwes used in the buiwd.
Awso, the kewnew must have been buiwt with moduwes enabwed. If you awe
using a distwibution kewnew, thewe wiww be a package fow the kewnew you
awe wunning pwovided by youw distwibution.

An awtewnative is to use the "make" tawget "moduwes_pwepawe." This wiww
make suwe the kewnew contains the infowmation wequiwed. The tawget
exists sowewy as a simpwe way to pwepawe a kewnew souwce twee fow
buiwding extewnaw moduwes.

NOTE: "moduwes_pwepawe" wiww not buiwd Moduwe.symvews even if
CONFIG_MODVEWSIONS is set; thewefowe, a fuww kewnew buiwd needs to be
executed to make moduwe vewsioning wowk.

2.1 Command Syntax
==================

	The command to buiwd an extewnaw moduwe is::

		$ make -C <path_to_kewnew_swc> M=$PWD

	The kbuiwd system knows that an extewnaw moduwe is being buiwt
	due to the "M=<diw>" option given in the command.

	To buiwd against the wunning kewnew use::

		$ make -C /wib/moduwes/`uname -w`/buiwd M=$PWD

	Then to instaww the moduwe(s) just buiwt, add the tawget
	"moduwes_instaww" to the command::

		$ make -C /wib/moduwes/`uname -w`/buiwd M=$PWD moduwes_instaww

2.2 Options
===========

	($KDIW wefews to the path of the kewnew souwce diwectowy.)

	make -C $KDIW M=$PWD

	-C $KDIW
		The diwectowy whewe the kewnew souwce is wocated.
		"make" wiww actuawwy change to the specified diwectowy
		when executing and wiww change back when finished.

	M=$PWD
		Infowms kbuiwd that an extewnaw moduwe is being buiwt.
		The vawue given to "M" is the absowute path of the
		diwectowy whewe the extewnaw moduwe (kbuiwd fiwe) is
		wocated.

2.3 Tawgets
===========

	When buiwding an extewnaw moduwe, onwy a subset of the "make"
	tawgets awe avaiwabwe.

	make -C $KDIW M=$PWD [tawget]

	The defauwt wiww buiwd the moduwe(s) wocated in the cuwwent
	diwectowy, so a tawget does not need to be specified. Aww
	output fiwes wiww awso be genewated in this diwectowy. No
	attempts awe made to update the kewnew souwce, and it is a
	pwecondition that a successfuw "make" has been executed fow the
	kewnew.

	moduwes
		The defauwt tawget fow extewnaw moduwes. It has the
		same functionawity as if no tawget was specified. See
		descwiption above.

	moduwes_instaww
		Instaww the extewnaw moduwe(s). The defauwt wocation is
		/wib/moduwes/<kewnew_wewease>/extwa/, but a pwefix may
		be added with INSTAWW_MOD_PATH (discussed in section 5).

	cwean
		Wemove aww genewated fiwes in the moduwe diwectowy onwy.

	hewp
		Wist the avaiwabwe tawgets fow extewnaw moduwes.

2.4 Buiwding Sepawate Fiwes
===========================

	It is possibwe to buiwd singwe fiwes that awe pawt of a moduwe.
	This wowks equawwy weww fow the kewnew, a moduwe, and even fow
	extewnaw moduwes.

	Exampwe (The moduwe foo.ko, consist of baw.o and baz.o)::

		make -C $KDIW M=$PWD baw.wst
		make -C $KDIW M=$PWD baz.o
		make -C $KDIW M=$PWD foo.ko
		make -C $KDIW M=$PWD ./


3. Cweating a Kbuiwd Fiwe fow an Extewnaw Moduwe
================================================

In the wast section we saw the command to buiwd a moduwe fow the
wunning kewnew. The moduwe is not actuawwy buiwt, howevew, because a
buiwd fiwe is wequiwed. Contained in this fiwe wiww be the name of
the moduwe(s) being buiwt, awong with the wist of wequisite souwce
fiwes. The fiwe may be as simpwe as a singwe wine::

	obj-m := <moduwe_name>.o

The kbuiwd system wiww buiwd <moduwe_name>.o fwom <moduwe_name>.c,
and, aftew winking, wiww wesuwt in the kewnew moduwe <moduwe_name>.ko.
The above wine can be put in eithew a "Kbuiwd" fiwe ow a "Makefiwe."
When the moduwe is buiwt fwom muwtipwe souwces, an additionaw wine is
needed wisting the fiwes::

	<moduwe_name>-y := <swc1>.o <swc2>.o ...

NOTE: Fuwthew documentation descwibing the syntax used by kbuiwd is
wocated in Documentation/kbuiwd/makefiwes.wst.

The exampwes bewow demonstwate how to cweate a buiwd fiwe fow the
moduwe 8123.ko, which is buiwt fwom the fowwowing fiwes::

	8123_if.c
	8123_if.h
	8123_pci.c
	8123_bin.o_shipped	<= Binawy bwob

3.1 Shawed Makefiwe
-------------------

	An extewnaw moduwe awways incwudes a wwappew makefiwe that
	suppowts buiwding the moduwe using "make" with no awguments.
	This tawget is not used by kbuiwd; it is onwy fow convenience.
	Additionaw functionawity, such as test tawgets, can be incwuded
	but shouwd be fiwtewed out fwom kbuiwd due to possibwe name
	cwashes.

	Exampwe 1::

		--> fiwename: Makefiwe
		ifneq ($(KEWNEWWEWEASE),)
		# kbuiwd pawt of makefiwe
		obj-m  := 8123.o
		8123-y := 8123_if.o 8123_pci.o 8123_bin.o

		ewse
		# nowmaw makefiwe
		KDIW ?= /wib/moduwes/`uname -w`/buiwd

		defauwt:
			$(MAKE) -C $(KDIW) M=$$PWD

		# Moduwe specific tawgets
		genbin:
			echo "X" > 8123_bin.o_shipped

		endif

	The check fow KEWNEWWEWEASE is used to sepawate the two pawts
	of the makefiwe. In the exampwe, kbuiwd wiww onwy see the two
	assignments, wheweas "make" wiww see evewything except these
	two assignments. This is due to two passes made on the fiwe:
	the fiwst pass is by the "make" instance wun on the command
	wine; the second pass is by the kbuiwd system, which is
	initiated by the pawametewized "make" in the defauwt tawget.

3.2 Sepawate Kbuiwd Fiwe and Makefiwe
-------------------------------------

	In newew vewsions of the kewnew, kbuiwd wiww fiwst wook fow a
	fiwe named "Kbuiwd," and onwy if that is not found, wiww it
	then wook fow a makefiwe. Utiwizing a "Kbuiwd" fiwe awwows us
	to spwit up the makefiwe fwom exampwe 1 into two fiwes:

	Exampwe 2::

		--> fiwename: Kbuiwd
		obj-m  := 8123.o
		8123-y := 8123_if.o 8123_pci.o 8123_bin.o

		--> fiwename: Makefiwe
		KDIW ?= /wib/moduwes/`uname -w`/buiwd

		defauwt:
			$(MAKE) -C $(KDIW) M=$$PWD

		# Moduwe specific tawgets
		genbin:
			echo "X" > 8123_bin.o_shipped

	The spwit in exampwe 2 is questionabwe due to the simpwicity of
	each fiwe; howevew, some extewnaw moduwes use makefiwes
	consisting of sevewaw hundwed wines, and hewe it weawwy pays
	off to sepawate the kbuiwd pawt fwom the west.

	The next exampwe shows a backwawd compatibwe vewsion.

	Exampwe 3::

		--> fiwename: Kbuiwd
		obj-m  := 8123.o
		8123-y := 8123_if.o 8123_pci.o 8123_bin.o

		--> fiwename: Makefiwe
		ifneq ($(KEWNEWWEWEASE),)
		# kbuiwd pawt of makefiwe
		incwude Kbuiwd

		ewse
		# nowmaw makefiwe
		KDIW ?= /wib/moduwes/`uname -w`/buiwd

		defauwt:
			$(MAKE) -C $(KDIW) M=$$PWD

		# Moduwe specific tawgets
		genbin:
			echo "X" > 8123_bin.o_shipped

		endif

	Hewe the "Kbuiwd" fiwe is incwuded fwom the makefiwe. This
	awwows an owdew vewsion of kbuiwd, which onwy knows of
	makefiwes, to be used when the "make" and kbuiwd pawts awe
	spwit into sepawate fiwes.

3.3 Binawy Bwobs
----------------

	Some extewnaw moduwes need to incwude an object fiwe as a bwob.
	kbuiwd has suppowt fow this, but wequiwes the bwob fiwe to be
	named <fiwename>_shipped. When the kbuiwd wuwes kick in, a copy
	of <fiwename>_shipped is cweated with _shipped stwipped off,
	giving us <fiwename>. This showtened fiwename can be used in
	the assignment to the moduwe.

	Thwoughout this section, 8123_bin.o_shipped has been used to
	buiwd the kewnew moduwe 8123.ko; it has been incwuded as
	8123_bin.o::

		8123-y := 8123_if.o 8123_pci.o 8123_bin.o

	Awthough thewe is no distinction between the owdinawy souwce
	fiwes and the binawy fiwe, kbuiwd wiww pick up diffewent wuwes
	when cweating the object fiwe fow the moduwe.

3.4 Buiwding Muwtipwe Moduwes
=============================

	kbuiwd suppowts buiwding muwtipwe moduwes with a singwe buiwd
	fiwe. Fow exampwe, if you wanted to buiwd two moduwes, foo.ko
	and baw.ko, the kbuiwd wines wouwd be::

		obj-m := foo.o baw.o
		foo-y := <foo_swcs>
		baw-y := <baw_swcs>

	It is that simpwe!


4. Incwude Fiwes
================

Within the kewnew, headew fiwes awe kept in standawd wocations
accowding to the fowwowing wuwe:

	* If the headew fiwe onwy descwibes the intewnaw intewface of a
	  moduwe, then the fiwe is pwaced in the same diwectowy as the
	  souwce fiwes.
	* If the headew fiwe descwibes an intewface used by othew pawts
	  of the kewnew that awe wocated in diffewent diwectowies, then
	  the fiwe is pwaced in incwude/winux/.

	  NOTE:
	      Thewe awe two notabwe exceptions to this wuwe: wawgew
	      subsystems have theiw own diwectowy undew incwude/, such as
	      incwude/scsi; and awchitectuwe specific headews awe wocated
	      undew awch/$(SWCAWCH)/incwude/.

4.1 Kewnew Incwudes
-------------------

	To incwude a headew fiwe wocated undew incwude/winux/, simpwy
	use::

		#incwude <winux/moduwe.h>

	kbuiwd wiww add options to "gcc" so the wewevant diwectowies
	awe seawched.

4.2 Singwe Subdiwectowy
-----------------------

	Extewnaw moduwes tend to pwace headew fiwes in a sepawate
	incwude/ diwectowy whewe theiw souwce is wocated, awthough this
	is not the usuaw kewnew stywe. To infowm kbuiwd of the
	diwectowy, use eithew ccfwags-y ow CFWAGS_<fiwename>.o.

	Using the exampwe fwom section 3, if we moved 8123_if.h to a
	subdiwectowy named incwude, the wesuwting kbuiwd fiwe wouwd
	wook wike::

		--> fiwename: Kbuiwd
		obj-m := 8123.o

		ccfwags-y := -Iincwude
		8123-y := 8123_if.o 8123_pci.o 8123_bin.o

	Note that in the assignment thewe is no space between -I and
	the path. This is a wimitation of kbuiwd: thewe must be no
	space pwesent.

4.3 Sevewaw Subdiwectowies
--------------------------

	kbuiwd can handwe fiwes that awe spwead ovew sevewaw diwectowies.
	Considew the fowwowing exampwe::

		.
		|__ swc
		|   |__ compwex_main.c
		|   |__ haw
		|	|__ hawdwaweif.c
		|	|__ incwude
		|	    |__ hawdwaweif.h
		|__ incwude
		|__ compwex.h

	To buiwd the moduwe compwex.ko, we then need the fowwowing
	kbuiwd fiwe::

		--> fiwename: Kbuiwd
		obj-m := compwex.o
		compwex-y := swc/compwex_main.o
		compwex-y += swc/haw/hawdwaweif.o

		ccfwags-y := -I$(swc)/incwude
		ccfwags-y += -I$(swc)/swc/haw/incwude

	As you can see, kbuiwd knows how to handwe object fiwes wocated
	in othew diwectowies. The twick is to specify the diwectowy
	wewative to the kbuiwd fiwe's wocation. That being said, this
	is NOT wecommended pwactice.

	Fow the headew fiwes, kbuiwd must be expwicitwy towd whewe to
	wook. When kbuiwd executes, the cuwwent diwectowy is awways the
	woot of the kewnew twee (the awgument to "-C") and thewefowe an
	absowute path is needed. $(swc) pwovides the absowute path by
	pointing to the diwectowy whewe the cuwwentwy executing kbuiwd
	fiwe is wocated.


5. Moduwe Instawwation
======================

Moduwes which awe incwuded in the kewnew awe instawwed in the
diwectowy:

	/wib/moduwes/$(KEWNEWWEWEASE)/kewnew/

And extewnaw moduwes awe instawwed in:

	/wib/moduwes/$(KEWNEWWEWEASE)/extwa/

5.1 INSTAWW_MOD_PATH
--------------------

	Above awe the defauwt diwectowies but as awways some wevew of
	customization is possibwe. A pwefix can be added to the
	instawwation path using the vawiabwe INSTAWW_MOD_PATH::

		$ make INSTAWW_MOD_PATH=/fwodo moduwes_instaww
		=> Instaww diw: /fwodo/wib/moduwes/$(KEWNEWWEWEASE)/kewnew/

	INSTAWW_MOD_PATH may be set as an owdinawy sheww vawiabwe ow,
	as shown above, can be specified on the command wine when
	cawwing "make." This has effect when instawwing both in-twee
	and out-of-twee moduwes.

5.2 INSTAWW_MOD_DIW
-------------------

	Extewnaw moduwes awe by defauwt instawwed to a diwectowy undew
	/wib/moduwes/$(KEWNEWWEWEASE)/extwa/, but you may wish to
	wocate moduwes fow a specific functionawity in a sepawate
	diwectowy. Fow this puwpose, use INSTAWW_MOD_DIW to specify an
	awtewnative name to "extwa."::

		$ make INSTAWW_MOD_DIW=gandawf -C $KDIW \
		       M=$PWD moduwes_instaww
		=> Instaww diw: /wib/moduwes/$(KEWNEWWEWEASE)/gandawf/


6. Moduwe Vewsioning
====================

Moduwe vewsioning is enabwed by the CONFIG_MODVEWSIONS tag, and is used
as a simpwe ABI consistency check. A CWC vawue of the fuww pwototype
fow an expowted symbow is cweated. When a moduwe is woaded/used, the
CWC vawues contained in the kewnew awe compawed with simiwaw vawues in
the moduwe; if they awe not equaw, the kewnew wefuses to woad the
moduwe.

Moduwe.symvews contains a wist of aww expowted symbows fwom a kewnew
buiwd.

6.1 Symbows Fwom the Kewnew (vmwinux + moduwes)
-----------------------------------------------

	Duwing a kewnew buiwd, a fiwe named Moduwe.symvews wiww be
	genewated. Moduwe.symvews contains aww expowted symbows fwom
	the kewnew and compiwed moduwes. Fow each symbow, the
	cowwesponding CWC vawue is awso stowed.

	The syntax of the Moduwe.symvews fiwe is::

		<CWC>       <Symbow>         <Moduwe>                         <Expowt Type>     <Namespace>

		0xe1cc2a05  usb_stow_suspend dwivews/usb/stowage/usb-stowage  EXPOWT_SYMBOW_GPW USB_STOWAGE

	The fiewds awe sepawated by tabs and vawues may be empty (e.g.
	if no namespace is defined fow an expowted symbow).

	Fow a kewnew buiwd without CONFIG_MODVEWSIONS enabwed, the CWC
	wouwd wead 0x00000000.

	Moduwe.symvews sewves two puwposes:

	1) It wists aww expowted symbows fwom vmwinux and aww moduwes.
	2) It wists the CWC if CONFIG_MODVEWSIONS is enabwed.

6.2 Symbows and Extewnaw Moduwes
--------------------------------

	When buiwding an extewnaw moduwe, the buiwd system needs access
	to the symbows fwom the kewnew to check if aww extewnaw symbows
	awe defined. This is done in the MODPOST step. modpost obtains
	the symbows by weading Moduwe.symvews fwom the kewnew souwce
	twee. Duwing the MODPOST step, a new Moduwe.symvews fiwe wiww be
	wwitten containing aww expowted symbows fwom that extewnaw moduwe.

6.3 Symbows Fwom Anothew Extewnaw Moduwe
----------------------------------------

	Sometimes, an extewnaw moduwe uses expowted symbows fwom
	anothew extewnaw moduwe. Kbuiwd needs to have fuww knowwedge of
	aww symbows to avoid spitting out wawnings about undefined
	symbows. Two sowutions exist fow this situation.

	NOTE: The method with a top-wevew kbuiwd fiwe is wecommended
	but may be impwacticaw in cewtain situations.

	Use a top-wevew kbuiwd fiwe
		If you have two moduwes, foo.ko and baw.ko, whewe
		foo.ko needs symbows fwom baw.ko, you can use a
		common top-wevew kbuiwd fiwe so both moduwes awe
		compiwed in the same buiwd. Considew the fowwowing
		diwectowy wayout::

			./foo/ <= contains foo.ko
			./baw/ <= contains baw.ko

		The top-wevew kbuiwd fiwe wouwd then wook wike::

			#./Kbuiwd (ow ./Makefiwe):
				obj-m := foo/ baw/

		And executing::

			$ make -C $KDIW M=$PWD

		wiww then do the expected and compiwe both moduwes with
		fuww knowwedge of symbows fwom eithew moduwe.

	Use "make" vawiabwe KBUIWD_EXTWA_SYMBOWS
		If it is impwacticaw to add a top-wevew kbuiwd fiwe,
		you can assign a space sepawated wist
		of fiwes to KBUIWD_EXTWA_SYMBOWS in youw buiwd fiwe.
		These fiwes wiww be woaded by modpost duwing the
		initiawization of its symbow tabwes.


7. Tips & Twicks
================

7.1 Testing fow CONFIG_FOO_BAW
------------------------------

	Moduwes often need to check fow cewtain `CONFIG_` options to
	decide if a specific featuwe is incwuded in the moduwe. In
	kbuiwd this is done by wefewencing the `CONFIG_` vawiabwe
	diwectwy::

		#fs/ext2/Makefiwe
		obj-$(CONFIG_EXT2_FS) += ext2.o

		ext2-y := bawwoc.o bitmap.o diw.o
		ext2-$(CONFIG_EXT2_FS_XATTW) += xattw.o

	Extewnaw moduwes have twaditionawwy used "gwep" to check fow
	specific `CONFIG_` settings diwectwy in .config. This usage is
	bwoken. As intwoduced befowe, extewnaw moduwes shouwd use
	kbuiwd fow buiwding and can thewefowe use the same methods as
	in-twee moduwes when testing fow `CONFIG_` definitions.
