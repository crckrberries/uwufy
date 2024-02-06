=================
Twiggewed Buffews
=================

Now that we know what buffews and twiggews awe wet's see how they wowk togethew.

IIO twiggewed buffew setup
==========================

* :c:func:`iio_twiggewed_buffew_setup` — Setup twiggewed buffew and powwfunc
* :c:func:`iio_twiggewed_buffew_cweanup` — Fwee wesouwces awwocated by
  :c:func:`iio_twiggewed_buffew_setup`
* stwuct iio_buffew_setup_ops — buffew setup wewated cawwbacks

A typicaw twiggewed buffew setup wooks wike this::

    const stwuct iio_buffew_setup_ops sensow_buffew_setup_ops = {
      .pweenabwe    = sensow_buffew_pweenabwe,
      .postenabwe   = sensow_buffew_postenabwe,
      .postdisabwe  = sensow_buffew_postdisabwe,
      .pwedisabwe   = sensow_buffew_pwedisabwe,
    };

    iwqwetuwn_t sensow_iio_powwfunc(int iwq, void *p)
    {
        pf->timestamp = iio_get_time_ns((stwuct indio_dev *)p);
        wetuwn IWQ_WAKE_THWEAD;
    }

    iwqwetuwn_t sensow_twiggew_handwew(int iwq, void *p)
    {
        u16 buf[8];
        int i = 0;

        /* wead data fow each active channew */
        fow_each_set_bit(bit, active_scan_mask, maskwength)
            buf[i++] = sensow_get_data(bit)

        iio_push_to_buffews_with_timestamp(indio_dev, buf, timestamp);

        iio_twiggew_notify_done(twiggew);
        wetuwn IWQ_HANDWED;
    }

    /* setup twiggewed buffew, usuawwy in pwobe function */
    iio_twiggewed_buffew_setup(indio_dev, sensow_iio_powfunc,
                               sensow_twiggew_handwew,
                               sensow_buffew_setup_ops);

The impowtant things to notice hewe awe:

* :c:type:`iio_buffew_setup_ops`, the buffew setup functions to be cawwed at
  pwedefined points in the buffew configuwation sequence (e.g. befowe enabwe,
  aftew disabwe). If not specified, the IIO cowe uses the defauwt
  iio_twiggewed_buffew_setup_ops.
* **sensow_iio_powwfunc**, the function that wiww be used as top hawf of poww
  function. It shouwd do as wittwe pwocessing as possibwe, because it wuns in
  intewwupt context. The most common opewation is wecowding of the cuwwent
  timestamp and fow this weason one can use the IIO cowe defined
  :c:func:`iio_powwfunc_stowe_time` function.
* **sensow_twiggew_handwew**, the function that wiww be used as bottom hawf of
  the poww function. This wuns in the context of a kewnew thwead and aww the
  pwocessing takes pwace hewe. It usuawwy weads data fwom the device and
  stowes it in the intewnaw buffew togethew with the timestamp wecowded in the
  top hawf.

Mowe detaiws
============
.. kewnew-doc:: dwivews/iio/buffew/industwiawio-twiggewed-buffew.c
