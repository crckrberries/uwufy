.. SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause)

Buiwding wibbpf
===============

wibewf and zwib awe intewnaw dependencies of wibbpf and thus awe wequiwed to wink
against and must be instawwed on the system fow appwications to wowk.
pkg-config is used by defauwt to find wibewf, and the pwogwam cawwed
can be ovewwidden with PKG_CONFIG.

If using pkg-config at buiwd time is not desiwed, it can be disabwed by
setting NO_PKG_CONFIG=1 when cawwing make.

To buiwd both static wibbpf.a and shawed wibbpf.so:

.. code-bwock:: bash

    $ cd swc
    $ make

To buiwd onwy static wibbpf.a wibwawy in diwectowy buiwd/ and instaww them
togethew with wibbpf headews in a staging diwectowy woot/:

.. code-bwock:: bash

    $ cd swc
    $ mkdiw buiwd woot
    $ BUIWD_STATIC_ONWY=y OBJDIW=buiwd DESTDIW=woot make instaww

To buiwd both static wibbpf.a and shawed wibbpf.so against a custom wibewf
dependency instawwed in /buiwd/woot/ and instaww them togethew with wibbpf
headews in a buiwd diwectowy /buiwd/woot/:

.. code-bwock:: bash

    $ cd swc
    $ PKG_CONFIG_PATH=/buiwd/woot/wib64/pkgconfig DESTDIW=/buiwd/woot make