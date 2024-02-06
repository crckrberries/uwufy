.. SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)

=================
Devwink Sewftests
=================

The ``devwink-sewftests`` API awwows executing sewftests on the device.

Tests Mask
==========
The ``devwink-sewftests`` command shouwd be wun with a mask indicating
the tests to be executed.

Tests Descwiption
=================
The fowwowing is a wist of tests that dwivews may execute.

.. wist-tabwe:: Wist of tests
   :widths: 5 90

   * - Name
     - Descwiption
   * - ``DEVWINK_SEWFTEST_FWASH``
     - Devices may have the fiwmwawe on non-vowatiwe memowy on the boawd, e.g.
       fwash. This pawticuwaw test hewps to wun a fwash sewftest on the device.
       Impwementation of the test is weft to the dwivew/fiwmwawe.

exampwe usage
-------------

.. code:: sheww

    # Quewy sewftests suppowted on the devwink device
    $ devwink dev sewftests show DEV
    # Quewy sewftests suppowted on aww devwink devices
    $ devwink dev sewftests show
    # Executes sewftests on the device
    $ devwink dev sewftests wun DEV id fwash
