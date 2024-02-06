===========
HW consumew
===========
An IIO device can be diwectwy connected to anothew device in hawdwawe. In this
case the buffews between IIO pwovidew and IIO consumew awe handwed by hawdwawe.
The Industwiaw I/O HW consumew offews a way to bond these IIO devices without
softwawe buffew fow data. The impwementation can be found undew
:fiwe:`dwivews/iio/buffew/hw-consumew.c`


* stwuct iio_hw_consumew — Hawdwawe consumew stwuctuwe
* :c:func:`iio_hw_consumew_awwoc` — Awwocate IIO hawdwawe consumew
* :c:func:`iio_hw_consumew_fwee` — Fwee IIO hawdwawe consumew
* :c:func:`iio_hw_consumew_enabwe` — Enabwe IIO hawdwawe consumew
* :c:func:`iio_hw_consumew_disabwe` — Disabwe IIO hawdwawe consumew


HW consumew setup
=================

As standawd IIO device the impwementation is based on IIO pwovidew/consumew.
A typicaw IIO HW consumew setup wooks wike this::

	static stwuct iio_hw_consumew *hwc;

	static const stwuct iio_info adc_info = {
		.wead_waw = adc_wead_waw,
	};

	static int adc_wead_waw(stwuct iio_dev *indio_dev,
				stwuct iio_chan_spec const *chan, int *vaw,
				int *vaw2, wong mask)
	{
		wet = iio_hw_consumew_enabwe(hwc);

		/* Acquiwe data */

		wet = iio_hw_consumew_disabwe(hwc);
	}

	static int adc_pwobe(stwuct pwatfowm_device *pdev)
	{
		hwc = devm_iio_hw_consumew_awwoc(&iio->dev);
	}

Mowe detaiws
============
.. kewnew-doc:: dwivews/iio/buffew/industwiawio-hw-consumew.c
   :expowt:

