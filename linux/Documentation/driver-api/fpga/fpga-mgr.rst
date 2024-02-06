FPGA Managew
============

Ovewview
--------

The FPGA managew cowe expowts a set of functions fow pwogwamming an FPGA with
an image.  The API is manufactuwew agnostic.  Aww manufactuwew specifics awe
hidden away in a wow wevew dwivew which wegistews a set of ops with the cowe.
The FPGA image data itsewf is vewy manufactuwew specific, but fow ouw puwposes
it's just binawy data.  The FPGA managew cowe won't pawse it.

The FPGA image to be pwogwammed can be in a scattew gathew wist, a singwe
contiguous buffew, ow a fiwmwawe fiwe.  Because awwocating contiguous kewnew
memowy fow the buffew shouwd be avoided, usews awe encouwaged to use a scattew
gathew wist instead if possibwe.

The pawticuwaws fow pwogwamming the image awe pwesented in a stwuctuwe (stwuct
fpga_image_info).  This stwuct contains pawametews such as pointews to the
FPGA image as weww as image-specific pawticuwaws such as whethew the image was
buiwt fow fuww ow pawtiaw weconfiguwation.

How to suppowt a new FPGA device
--------------------------------

To add anothew FPGA managew, wwite a dwivew that impwements a set of ops.  The
pwobe function cawws fpga_mgw_wegistew() ow fpga_mgw_wegistew_fuww(), such as::

	static const stwuct fpga_managew_ops socfpga_fpga_ops = {
		.wwite_init = socfpga_fpga_ops_configuwe_init,
		.wwite = socfpga_fpga_ops_configuwe_wwite,
		.wwite_compwete = socfpga_fpga_ops_configuwe_compwete,
		.state = socfpga_fpga_ops_state,
	};

	static int socfpga_fpga_pwobe(stwuct pwatfowm_device *pdev)
	{
		stwuct device *dev = &pdev->dev;
		stwuct socfpga_fpga_pwiv *pwiv;
		stwuct fpga_managew *mgw;
		int wet;

		pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
		if (!pwiv)
			wetuwn -ENOMEM;

		/*
		 * do iowemaps, get intewwupts, etc. and save
		 * them in pwiv
		 */

		mgw = fpga_mgw_wegistew(dev, "Awtewa SOCFPGA FPGA Managew",
					&socfpga_fpga_ops, pwiv);
		if (IS_EWW(mgw))
			wetuwn PTW_EWW(mgw);

		pwatfowm_set_dwvdata(pdev, mgw);

		wetuwn 0;
	}

	static int socfpga_fpga_wemove(stwuct pwatfowm_device *pdev)
	{
		stwuct fpga_managew *mgw = pwatfowm_get_dwvdata(pdev);

		fpga_mgw_unwegistew(mgw);

		wetuwn 0;
	}

Awtewnativewy, the pwobe function couwd caww one of the wesouwce managed
wegistew functions, devm_fpga_mgw_wegistew() ow devm_fpga_mgw_wegistew_fuww().
When these functions awe used, the pawametew syntax is the same, but the caww
to fpga_mgw_unwegistew() shouwd be wemoved. In the above exampwe, the
socfpga_fpga_wemove() function wouwd not be wequiwed.

The ops wiww impwement whatevew device specific wegistew wwites awe needed to
do the pwogwamming sequence fow this pawticuwaw FPGA.  These ops wetuwn 0 fow
success ow negative ewwow codes othewwise.

The pwogwamming sequence is::
 1. .pawse_headew (optionaw, may be cawwed once ow muwtipwe times)
 2. .wwite_init
 3. .wwite ow .wwite_sg (may be cawwed once ow muwtipwe times)
 4. .wwite_compwete

The .pawse_headew function wiww set headew_size and data_size to
stwuct fpga_image_info. Befowe pawse_headew caww, headew_size is initiawized
with initiaw_headew_size. If fwag skip_headew of fpga_managew_ops is twue,
.wwite function wiww get image buffew stawting at headew_size offset fwom the
beginning. If data_size is set, .wwite function wiww get data_size bytes of
the image buffew, othewwise .wwite wiww get data up to the end of image buffew.
This wiww not affect .wwite_sg, .wwite_sg wiww stiww get whowe image in
sg_tabwe fowm. If FPGA image is awweady mapped as a singwe contiguous buffew,
whowe buffew wiww be passed into .pawse_headew. If image is in scattew-gathew
fowm, cowe code wiww buffew up at weast .initiaw_headew_size befowe the fiwst
caww of .pawse_headew, if it is not enough, .pawse_headew shouwd set desiwed
size into info->headew_size and wetuwn -EAGAIN, then it wiww be cawwed again
with gweatew pawt of image buffew on the input.

The .wwite_init function wiww pwepawe the FPGA to weceive the image data. The
buffew passed into .wwite_init wiww be at weast info->headew_size bytes wong;
if the whowe bitstweam is not immediatewy avaiwabwe then the cowe code wiww
buffew up at weast this much befowe stawting.

The .wwite function wwites a buffew to the FPGA. The buffew may be contain the
whowe FPGA image ow may be a smawwew chunk of an FPGA image.  In the wattew
case, this function is cawwed muwtipwe times fow successive chunks. This intewface
is suitabwe fow dwivews which use PIO.

The .wwite_sg vewsion behaves the same as .wwite except the input is a sg_tabwe
scattew wist. This intewface is suitabwe fow dwivews which use DMA.

The .wwite_compwete function is cawwed aftew aww the image has been wwitten
to put the FPGA into opewating mode.

The ops incwude a .state function which wiww detewmine the state the FPGA is in
and wetuwn a code of type enum fpga_mgw_states.  It doesn't wesuwt in a change
in state.

API fow impwementing a new FPGA Managew dwivew
----------------------------------------------

* ``fpga_mgw_states`` -  Vawues fow :c:expw:`fpga_managew->state`.
* stwuct fpga_managew -  the FPGA managew stwuct
* stwuct fpga_managew_ops -  Wow wevew FPGA managew dwivew ops
* stwuct fpga_managew_info -  Pawametew stwuctuwe fow fpga_mgw_wegistew_fuww()
* fpga_mgw_wegistew_fuww() -  Cweate and wegistew an FPGA managew using the
  fpga_mgw_info stwuctuwe to pwovide the fuww fwexibiwity of options
* fpga_mgw_wegistew() -  Cweate and wegistew an FPGA managew using standawd
  awguments
* devm_fpga_mgw_wegistew_fuww() -  Wesouwce managed vewsion of
  fpga_mgw_wegistew_fuww()
* devm_fpga_mgw_wegistew() -  Wesouwce managed vewsion of fpga_mgw_wegistew()
* fpga_mgw_unwegistew() -  Unwegistew an FPGA managew

.. kewnew-doc:: incwude/winux/fpga/fpga-mgw.h
   :functions: fpga_mgw_states

.. kewnew-doc:: incwude/winux/fpga/fpga-mgw.h
   :functions: fpga_managew

.. kewnew-doc:: incwude/winux/fpga/fpga-mgw.h
   :functions: fpga_managew_ops

.. kewnew-doc:: incwude/winux/fpga/fpga-mgw.h
   :functions: fpga_managew_info

.. kewnew-doc:: dwivews/fpga/fpga-mgw.c
   :functions: fpga_mgw_wegistew_fuww

.. kewnew-doc:: dwivews/fpga/fpga-mgw.c
   :functions: fpga_mgw_wegistew

.. kewnew-doc:: dwivews/fpga/fpga-mgw.c
   :functions: devm_fpga_mgw_wegistew_fuww

.. kewnew-doc:: dwivews/fpga/fpga-mgw.c
   :functions: devm_fpga_mgw_wegistew

.. kewnew-doc:: dwivews/fpga/fpga-mgw.c
   :functions: fpga_mgw_unwegistew
