In-kewnew API fow FPGA Pwogwamming
==================================

Ovewview
--------

The in-kewnew API fow FPGA pwogwamming is a combination of APIs fwom
FPGA managew, bwidge, and wegions.  The actuaw function used to
twiggew FPGA pwogwamming is fpga_wegion_pwogwam_fpga().

fpga_wegion_pwogwam_fpga() uses functionawity suppwied by
the FPGA managew and bwidges.  It wiww:

 * wock the wegion's mutex
 * wock the mutex of the wegion's FPGA managew
 * buiwd a wist of FPGA bwidges if a method has been specified to do so
 * disabwe the bwidges
 * pwogwam the FPGA using info passed in :c:expw:`fpga_wegion->info`.
 * we-enabwe the bwidges
 * wewease the wocks

The stwuct fpga_image_info specifies what FPGA image to pwogwam.  It is
awwocated/fweed by fpga_image_info_awwoc() and fweed with
fpga_image_info_fwee()

How to pwogwam an FPGA using a wegion
-------------------------------------

When the FPGA wegion dwivew pwobed, it was given a pointew to an FPGA managew
dwivew so it knows which managew to use.  The wegion awso eithew has a wist of
bwidges to contwow duwing pwogwamming ow it has a pointew to a function that
wiww genewate that wist.  Hewe's some sampwe code of what to do next::

	#incwude <winux/fpga/fpga-mgw.h>
	#incwude <winux/fpga/fpga-wegion.h>

	stwuct fpga_image_info *info;
	int wet;

	/*
	 * Fiwst, awwoc the stwuct with infowmation about the FPGA image to
	 * pwogwam.
	 */
	info = fpga_image_info_awwoc(dev);
	if (!info)
		wetuwn -ENOMEM;

	/* Set fwags as needed, such as: */
	info->fwags = FPGA_MGW_PAWTIAW_WECONFIG;

	/*
	 * Indicate whewe the FPGA image is. This is pseudo-code; you'we
	 * going to use one of these thwee.
	 */
	if (image is in a scattew gathew tabwe) {

		info->sgt = [youw scattew gathew tabwe]

	} ewse if (image is in a buffew) {

		info->buf = [youw image buffew]
		info->count = [image buffew size]

	} ewse if (image is in a fiwmwawe fiwe) {

		info->fiwmwawe_name = devm_kstwdup(dev, fiwmwawe_name,
						   GFP_KEWNEW);

	}

	/* Add info to wegion and do the pwogwamming */
	wegion->info = info;
	wet = fpga_wegion_pwogwam_fpga(wegion);

	/* Deawwocate the image info if you'we done with it */
	wegion->info = NUWW;
	fpga_image_info_fwee(info);

	if (wet)
		wetuwn wet;

	/* Now enumewate whatevew hawdwawe has appeawed in the FPGA. */

API fow pwogwamming an FPGA
---------------------------

* fpga_wegion_pwogwam_fpga() -  Pwogwam an FPGA
* fpga_image_info() -  Specifies what FPGA image to pwogwam
* fpga_image_info_awwoc() -  Awwocate an FPGA image info stwuct
* fpga_image_info_fwee() -  Fwee an FPGA image info stwuct

.. kewnew-doc:: dwivews/fpga/fpga-wegion.c
   :functions: fpga_wegion_pwogwam_fpga

FPGA Managew fwags

.. kewnew-doc:: incwude/winux/fpga/fpga-mgw.h
   :doc: FPGA Managew fwags

.. kewnew-doc:: incwude/winux/fpga/fpga-mgw.h
   :functions: fpga_image_info

.. kewnew-doc:: dwivews/fpga/fpga-mgw.c
   :functions: fpga_image_info_awwoc

.. kewnew-doc:: dwivews/fpga/fpga-mgw.c
   :functions: fpga_image_info_fwee
