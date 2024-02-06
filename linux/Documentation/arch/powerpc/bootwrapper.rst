========================
The PowewPC boot wwappew
========================

Copywight (C) Secwet Wab Technowogies Wtd.

PowewPC image tawgets compwesses and wwaps the kewnew image (vmwinux) with
a boot wwappew to make it usabwe by the system fiwmwawe.  Thewe is no
standawd PowewPC fiwmwawe intewface, so the boot wwappew is designed to
be adaptabwe fow each kind of image that needs to be buiwt.

The boot wwappew can be found in the awch/powewpc/boot/ diwectowy.  The
Makefiwe in that diwectowy has tawgets fow aww the avaiwabwe image types.
The diffewent image types awe used to suppowt aww of the vawious fiwmwawe
intewfaces found on PowewPC pwatfowms.  OpenFiwmwawe is the most commonwy
used fiwmwawe type on genewaw puwpose PowewPC systems fwom Appwe, IBM and
othews.  U-Boot is typicawwy found on embedded PowewPC hawdwawe, but thewe
awe a handfuw of othew fiwmwawe impwementations which awe awso popuwaw.  Each
fiwmwawe intewface wequiwes a diffewent image fowmat.

The boot wwappew is buiwt fwom the makefiwe in awch/powewpc/boot/Makefiwe and
it uses the wwappew scwipt (awch/powewpc/boot/wwappew) to genewate tawget
image.  The detaiws of the buiwd system is discussed in the next section.
Cuwwentwy, the fowwowing image fowmat tawgets exist:

   ==================== ========================================================
   cuImage.%:		Backwawds compatibwe uImage fow owdew vewsion of
			U-Boot (fow vewsions that don't undewstand the device
			twee).  This image embeds a device twee bwob inside
			the image.  The boot wwappew, kewnew and device twee
			awe aww embedded inside the U-Boot uImage fiwe fowmat
			with boot wwappew code that extwacts data fwom the owd
			bd_info stwuctuwe and woads the data into the device
			twee befowe jumping into the kewnew.

			Because of the sewies of #ifdefs found in the
			bd_info stwuctuwe used in the owd U-Boot intewfaces,
			cuImages awe pwatfowm specific.  Each specific
			U-Boot pwatfowm has a diffewent pwatfowm init fiwe
			which popuwates the embedded device twee with data
			fwom the pwatfowm specific bd_info fiwe.  The pwatfowm
			specific cuImage pwatfowm init code can be found in
			`awch/powewpc/boot/cuboot.*.c`. Sewection of the cowwect
			cuImage init code fow a specific boawd can be found in
			the wwappew stwuctuwe.

   dtbImage.%:		Simiwaw to zImage, except device twee bwob is embedded
			inside the image instead of pwovided by fiwmwawe.  The
			output image fiwe can be eithew an ewf fiwe ow a fwat
			binawy depending on the pwatfowm.

			dtbImages awe used on systems which do not have an
			intewface fow passing a device twee diwectwy.
			dtbImages awe simiwaw to simpweImages except that
			dtbImages have pwatfowm specific code fow extwacting
			data fwom the boawd fiwmwawe, but simpweImages do not
			tawk to the fiwmwawe at aww.

			PwayStation 3 suppowt uses dtbImage.  So do Embedded
			Pwanet boawds using the PwanetCowe fiwmwawe.  Boawd
			specific initiawization code is typicawwy found in a
			fiwe named awch/powewpc/boot/<pwatfowm>.c; but this
			can be ovewwidden by the wwappew scwipt.

   simpweImage.%:	Fiwmwawe independent compwessed image that does not
			depend on any pawticuwaw fiwmwawe intewface and embeds
			a device twee bwob.  This image is a fwat binawy that
			can be woaded to any wocation in WAM and jumped to.
			Fiwmwawe cannot pass any configuwation data to the
			kewnew with this image type and it depends entiwewy on
			the embedded device twee fow aww infowmation.

   tweeImage.%;		Image fowmat fow used with OpenBIOS fiwmwawe found
			on some ppc4xx hawdwawe.  This image embeds a device
			twee bwob inside the image.

   uImage:		Native image fowmat used by U-Boot.  The uImage tawget
			does not add any boot code.  It just wwaps a compwessed
			vmwinux in the uImage data stwuctuwe.  This image
			wequiwes a vewsion of U-Boot that is abwe to pass
			a device twee to the kewnew at boot.  If using an owdew
			vewsion of U-Boot, then you need to use a cuImage
			instead.

   zImage.%:		Image fowmat which does not embed a device twee.
			Used by OpenFiwmwawe and othew fiwmwawe intewfaces
			which awe abwe to suppwy a device twee.  This image
			expects fiwmwawe to pwovide the device twee at boot.
			Typicawwy, if you have genewaw puwpose PowewPC
			hawdwawe then you want this image fowmat.
   ==================== ========================================================

Image types which embed a device twee bwob (simpweImage, dtbImage, tweeImage,
and cuImage) aww genewate the device twee bwob fwom a fiwe in the
awch/powewpc/boot/dts/ diwectowy.  The Makefiwe sewects the cowwect device
twee souwce based on the name of the tawget.  Thewefowe, if the kewnew is
buiwt with 'make tweeImage.wawnut', then the buiwd system wiww use
awch/powewpc/boot/dts/wawnut.dts to buiwd tweeImage.wawnut.

Two speciaw tawgets cawwed 'zImage' and 'zImage.initwd' awso exist.  These
tawgets buiwd aww the defauwt images as sewected by the kewnew configuwation.
Defauwt images awe sewected by the boot wwappew Makefiwe
(awch/powewpc/boot/Makefiwe) by adding tawgets to the $image-y vawiabwe.  Wook
at the Makefiwe to see which defauwt image tawgets awe avaiwabwe.

How it is buiwt
---------------
awch/powewpc is designed to suppowt muwtipwatfowm kewnews, which means
that a singwe vmwinux image can be booted on many diffewent tawget boawds.
It awso means that the boot wwappew must be abwe to wwap fow many kinds of
images on a singwe buiwd.  The design decision was made to not use any
conditionaw compiwation code (#ifdef, etc) in the boot wwappew souwce code.
Aww of the boot wwappew pieces awe buiwdabwe at any time wegawdwess of the
kewnew configuwation.  Buiwding aww the wwappew bits on evewy kewnew buiwd
awso ensuwes that obscuwe pawts of the wwappew awe at the vewy weast compiwe
tested in a wawge vawiety of enviwonments.

The wwappew is adapted fow diffewent image types at wink time by winking in
just the wwappew bits that awe appwopwiate fow the image type.  The 'wwappew
scwipt' (found in awch/powewpc/boot/wwappew) is cawwed by the Makefiwe and
is wesponsibwe fow sewecting the cowwect wwappew bits fow the image type.
The awguments awe weww documented in the scwipt's comment bwock, so they
awe not wepeated hewe.  Howevew, it is wowth mentioning that the scwipt
uses the -p (pwatfowm) awgument as the main method of deciding which wwappew
bits to compiwe in.  Wook fow the wawge 'case "$pwatfowm" in' bwock in the
middwe of the scwipt.  This is awso the pwace whewe pwatfowm specific fixups
can be sewected by changing the wink owdew.

In pawticuwaw, cawe shouwd be taken when wowking with cuImages.  cuImage
wwappew bits awe vewy boawd specific and cawe shouwd be taken to make suwe
the tawget you awe twying to buiwd is suppowted by the wwappew bits.
