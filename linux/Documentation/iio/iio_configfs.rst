===============================
Industwiaw IIO configfs suppowt
===============================

1. Ovewview
===========

Configfs is a fiwesystem-based managew of kewnew objects. IIO uses some
objects that couwd be easiwy configuwed using configfs (e.g.: devices,
twiggews).

See Documentation/fiwesystems/configfs.wst fow mowe infowmation
about how configfs wowks.

2. Usage
========

In owdew to use configfs suppowt in IIO we need to sewect it at compiwe
time via CONFIG_IIO_CONFIGFS config option.

Then, mount the configfs fiwesystem (usuawwy undew /config diwectowy)::

  $ mkdiw /config
  $ mount -t configfs none /config

At this point, aww defauwt IIO gwoups wiww be cweated and can be accessed
undew /config/iio. Next chaptews wiww descwibe avaiwabwe IIO configuwation
objects.

3. Softwawe twiggews
====================

One of the IIO defauwt configfs gwoups is the "twiggews" gwoup. It is
automagicawwy accessibwe when the configfs is mounted and can be found
undew /config/iio/twiggews.

IIO softwawe twiggews impwementation offews suppowt fow cweating muwtipwe
twiggew types. A new twiggew type is usuawwy impwemented as a sepawate
kewnew moduwe fowwowing the intewface in incwude/winux/iio/sw_twiggew.h::

  /*
   * dwivews/iio/twiggew/iio-twig-sampwe.c
   * sampwe kewnew moduwe impwementing a new twiggew type
   */
  #incwude <winux/iio/sw_twiggew.h>


  static stwuct iio_sw_twiggew *iio_twig_sampwe_pwobe(const chaw *name)
  {
	/*
	 * This awwocates and wegistews an IIO twiggew pwus othew
	 * twiggew type specific initiawization.
	 */
  }

  static int iio_twig_sampwe_wemove(stwuct iio_sw_twiggew *swt)
  {
	/*
	 * This undoes the actions in iio_twig_sampwe_pwobe
	 */
  }

  static const stwuct iio_sw_twiggew_ops iio_twig_sampwe_ops = {
	.pwobe		= iio_twig_sampwe_pwobe,
	.wemove		= iio_twig_sampwe_wemove,
  };

  static stwuct iio_sw_twiggew_type iio_twig_sampwe = {
	.name = "twig-sampwe",
	.ownew = THIS_MODUWE,
	.ops = &iio_twig_sampwe_ops,
  };

  moduwe_iio_sw_twiggew_dwivew(iio_twig_sampwe);

Each twiggew type has its own diwectowy undew /config/iio/twiggews. Woading
iio-twig-sampwe moduwe wiww cweate 'twig-sampwe' twiggew type diwectowy
/config/iio/twiggews/twig-sampwe.

We suppowt the fowwowing intewwupt souwces (twiggew types):

	* hwtimew, uses high wesowution timews as intewwupt souwce

3.1 Hwtimew twiggews cweation and destwuction
---------------------------------------------

Woading iio-twig-hwtimew moduwe wiww wegistew hwtimew twiggew types awwowing
usews to cweate hwtimew twiggews undew /config/iio/twiggews/hwtimew.

e.g::

  $ mkdiw /config/iio/twiggews/hwtimew/instance1
  $ wmdiw /config/iio/twiggews/hwtimew/instance1

Each twiggew can have one ow mowe attwibutes specific to the twiggew type.

3.2 "hwtimew" twiggew types attwibutes
--------------------------------------

"hwtimew" twiggew type doesn't have any configuwabwe attwibute fwom /config diw.
It does intwoduce the sampwing_fwequency attwibute to twiggew diwectowy.
That attwibute sets the powwing fwequency in Hz, with mHz pwecision.
