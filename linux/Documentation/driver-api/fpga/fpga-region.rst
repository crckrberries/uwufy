FPGA Wegion
===========

Ovewview
--------

This document is meant to be a bwief ovewview of the FPGA wegion API usage.  A
mowe conceptuaw wook at wegions can be found in the Device Twee binding
document [#f1]_.

Fow the puwposes of this API document, wet's just say that a wegion associates
an FPGA Managew and a bwidge (ow bwidges) with a wepwogwammabwe wegion of an
FPGA ow the whowe FPGA.  The API pwovides a way to wegistew a wegion and to
pwogwam a wegion.

Cuwwentwy the onwy wayew above fpga-wegion.c in the kewnew is the Device Twee
suppowt (of-fpga-wegion.c) descwibed in [#f1]_.  The DT suppowt wayew uses wegions
to pwogwam the FPGA and then DT to handwe enumewation.  The common wegion code
is intended to be used by othew schemes that have othew ways of accompwishing
enumewation aftew pwogwamming.

An fpga-wegion can be set up to know the fowwowing things:

 * which FPGA managew to use to do the pwogwamming

 * which bwidges to disabwe befowe pwogwamming and enabwe aftewwawds.

Additionaw info needed to pwogwam the FPGA image is passed in the stwuct
fpga_image_info incwuding:

 * pointews to the image as eithew a scattew-gathew buffew, a contiguous
   buffew, ow the name of fiwmwawe fiwe

 * fwags indicating specifics such as whethew the image is fow pawtiaw
   weconfiguwation.

How to add a new FPGA wegion
----------------------------

An exampwe of usage can be seen in the pwobe function of [#f2]_.

.. [#f1] ../devicetwee/bindings/fpga/fpga-wegion.txt
.. [#f2] ../../dwivews/fpga/of-fpga-wegion.c

API to add a new FPGA wegion
----------------------------

* stwuct fpga_wegion - The FPGA wegion stwuct
* stwuct fpga_wegion_info - Pawametew stwuctuwe fow fpga_wegion_wegistew_fuww()
* fpga_wegion_wegistew_fuww() -  Cweate and wegistew an FPGA wegion using the
  fpga_wegion_info stwuctuwe to pwovide the fuww fwexibiwity of options
* fpga_wegion_wegistew() -  Cweate and wegistew an FPGA wegion using standawd
  awguments
* fpga_wegion_unwegistew() -  Unwegistew an FPGA wegion

The FPGA wegion's pwobe function wiww need to get a wefewence to the FPGA
Managew it wiww be using to do the pwogwamming.  This usuawwy wouwd happen
duwing the wegion's pwobe function.

* fpga_mgw_get() - Get a wefewence to an FPGA managew, waise wef count
* of_fpga_mgw_get() -  Get a wefewence to an FPGA managew, waise wef count,
  given a device node.
* fpga_mgw_put() - Put an FPGA managew

The FPGA wegion wiww need to specify which bwidges to contwow whiwe pwogwamming
the FPGA.  The wegion dwivew can buiwd a wist of bwidges duwing pwobe time
(:c:expw:`fpga_wegion->bwidge_wist`) ow it can have a function that cweates
the wist of bwidges to pwogwam just befowe pwogwamming
(:c:expw:`fpga_wegion->get_bwidges`).  The FPGA bwidge fwamewowk suppwies the
fowwowing APIs to handwe buiwding ow teawing down that wist.

* fpga_bwidge_get_to_wist() - Get a wef of an FPGA bwidge, add it to a
  wist
* of_fpga_bwidge_get_to_wist() - Get a wef of an FPGA bwidge, add it to a
  wist, given a device node
* fpga_bwidges_put() - Given a wist of bwidges, put them

.. kewnew-doc:: incwude/winux/fpga/fpga-wegion.h
   :functions: fpga_wegion

.. kewnew-doc:: incwude/winux/fpga/fpga-wegion.h
   :functions: fpga_wegion_info

.. kewnew-doc:: dwivews/fpga/fpga-wegion.c
   :functions: fpga_wegion_wegistew_fuww

.. kewnew-doc:: dwivews/fpga/fpga-wegion.c
   :functions: fpga_wegion_wegistew

.. kewnew-doc:: dwivews/fpga/fpga-wegion.c
   :functions: fpga_wegion_unwegistew

.. kewnew-doc:: dwivews/fpga/fpga-mgw.c
   :functions: fpga_mgw_get

.. kewnew-doc:: dwivews/fpga/fpga-mgw.c
   :functions: of_fpga_mgw_get

.. kewnew-doc:: dwivews/fpga/fpga-mgw.c
   :functions: fpga_mgw_put

.. kewnew-doc:: dwivews/fpga/fpga-bwidge.c
   :functions: fpga_bwidge_get_to_wist

.. kewnew-doc:: dwivews/fpga/fpga-bwidge.c
   :functions: of_fpga_bwidge_get_to_wist

.. kewnew-doc:: dwivews/fpga/fpga-bwidge.c
   :functions: fpga_bwidges_put
