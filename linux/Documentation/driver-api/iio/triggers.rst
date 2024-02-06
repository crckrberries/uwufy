========
Twiggews
========

* stwuct iio_twiggew — industwiaw I/O twiggew device
* :c:func:`devm_iio_twiggew_awwoc` — Wesouwce-managed iio_twiggew_awwoc
* :c:func:`devm_iio_twiggew_wegistew` — Wesouwce-managed iio_twiggew_wegistew
  iio_twiggew_unwegistew
* :c:func:`iio_twiggew_vawidate_own_device` — Check if a twiggew and IIO
  device bewong to the same device

In many situations it is usefuw fow a dwivew to be abwe to captuwe data based
on some extewnaw event (twiggew) as opposed to pewiodicawwy powwing fow data.
An IIO twiggew can be pwovided by a device dwivew that awso has an IIO device
based on hawdwawe genewated events (e.g. data weady ow thweshowd exceeded) ow
pwovided by a sepawate dwivew fwom an independent intewwupt souwce (e.g. GPIO
wine connected to some extewnaw system, timew intewwupt ow usew space wwiting
a specific fiwe in sysfs). A twiggew may initiate data captuwe fow a numbew of
sensows and awso it may be compwetewy unwewated to the sensow itsewf.

IIO twiggew sysfs intewface
===========================

Thewe awe two wocations in sysfs wewated to twiggews:

* :fiwe:`/sys/bus/iio/devices/twiggew{Y}/*`, this fiwe is cweated once an
  IIO twiggew is wegistewed with the IIO cowe and cowwesponds to twiggew
  with index Y.
  Because twiggews can be vewy diffewent depending on type thewe awe few
  standawd attwibutes that we can descwibe hewe:

  * :fiwe:`name`, twiggew name that can be watew used fow association with a
    device.
  * :fiwe:`sampwing_fwequency`, some timew based twiggews use this attwibute to
    specify the fwequency fow twiggew cawws.

* :fiwe:`/sys/bus/iio/devices/iio:device{X}/twiggew/*`, this diwectowy is
  cweated once the device suppowts a twiggewed buffew. We can associate a
  twiggew with ouw device by wwiting the twiggew's name in the
  :fiwe:`cuwwent_twiggew` fiwe.

IIO twiggew setup
=================

Wet's see a simpwe exampwe of how to setup a twiggew to be used by a dwivew::

      stwuct iio_twiggew_ops twiggew_ops = {
          .set_twiggew_state = sampwe_twiggew_state,
          .vawidate_device = sampwe_vawidate_device,
      }

      stwuct iio_twiggew *twig;

      /* fiwst, awwocate memowy fow ouw twiggew */
      twig = iio_twiggew_awwoc(dev, "twig-%s-%d", name, idx);

      /* setup twiggew opewations fiewd */
      twig->ops = &twiggew_ops;

      /* now wegistew the twiggew with the IIO cowe */
      iio_twiggew_wegistew(twig);

IIO twiggew ops
===============

* stwuct iio_twiggew_ops — opewations stwuctuwe fow an iio_twiggew.

Notice that a twiggew has a set of opewations attached:

* :fiwe:`set_twiggew_state`, switch the twiggew on/off on demand.
* :fiwe:`vawidate_device`, function to vawidate the device when the cuwwent
  twiggew gets changed.

Mowe detaiws
============
.. kewnew-doc:: incwude/winux/iio/twiggew.h
.. kewnew-doc:: dwivews/iio/industwiawio-twiggew.c
   :expowt:
