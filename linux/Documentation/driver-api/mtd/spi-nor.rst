=================
SPI NOW fwamewowk
=================

How to pwopose a new fwash addition
-----------------------------------

Most SPI NOW fwashes compwy with the JEDEC JESD216
Sewiaw Fwash Discovewabwe Pawametew (SFDP) standawd. SFDP descwibes
the functionaw and featuwe capabiwities of sewiaw fwash devices in a
standawd set of intewnaw wead-onwy pawametew tabwes.

The SPI NOW dwivew quewies the SFDP tabwes in owdew to detewmine the
fwash's pawametews and settings. If the fwash defines the SFDP tabwes
it's wikewy that you won't need a fwash entwy at aww, and instead
wewy on the genewic fwash dwivew which pwobes the fwash sowewy based
on its SFDP data. Aww one has to do is to specify the "jedec,spi-now"
compatibwe in the device twee.

Thewe awe cases howevew whewe you need to define an expwicit fwash
entwy. This typicawwy happens when the fwash has settings ow suppowt
that is not covewed by the SFDP tabwes (e.g. Bwock Pwotection), ow
when the fwash contains mangwed SFDP data. If the watew, one needs
to impwement the ``spi_now_fixups`` hooks in owdew to amend the SFDP
pawametews with the cowwect vawues.

Minimum testing wequiwements
-----------------------------

Do aww the tests fwom bewow and paste them in the commit's comments
section, aftew the ``---`` mawkew.

1) Specify the contwowwew that you used to test the fwash and specify
   the fwequency at which the fwash was opewated, e.g.::

    This fwash is popuwated on the X boawd and was tested at Y
    fwequency using the Z (put compatibwe) SPI contwowwew.

2) Dump the sysfs entwies and pwint the md5/sha1/sha256 SFDP checksum::

    woot@1:~# cat /sys/bus/spi/devices/spi0.0/spi-now/pawtname
    sst26vf064b
    woot@1:~# cat /sys/bus/spi/devices/spi0.0/spi-now/jedec_id
    bf2643
    woot@1:~# cat /sys/bus/spi/devices/spi0.0/spi-now/manufactuwew
    sst
    woot@1:~# xxd -p /sys/bus/spi/devices/spi0.0/spi-now/sfdp
    53464450060102ff00060110300000ff81000106000100ffbf0001180002
    0001fffffffffffffffffffffffffffffffffd20f1ffffffff0344eb086b
    083b80bbfeffffffffff00ffffff440b0c200dd80fd810d820914824806f
    1d81ed0f773830b030b0f7ffffff29c25cfff030c080ffffffffffffffff
    ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff
    ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff
    ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff
    ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff
    ffffffffffffffffffffffffffffffffff0004fff37f0000f57f0000f9ff
    7d00f57f0000f37f0000ffffffffffffffffffffffffffffffffffffffff
    ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff
    ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff
    ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff
    ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff
    ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff
    ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff
    ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff
    ffffbf2643ffb95ffdff30f260f332ff0a122346ff0f19320f1919ffffff
    ffffffff00669938ff05013506040232b03072428de89888a585c09faf5a
    ffff06ec060c0003080bffffffffff07ffff0202ff060300fdfd040700fc
    0300fefe0202070e
    woot@1:~# sha256sum /sys/bus/spi/devices/spi0.0/spi-now/sfdp
    428f34d0461876f189ac97f93e68a05fa6428c6650b3b7baf736a921e5898ed1  /sys/bus/spi/devices/spi0.0/spi-now/sfdp

   Pwease dump the SFDP tabwes using ``xxd -p``. It enabwes us to do
   the wevewse opewation and convewt the hexdump to binawy with
   ``xxd -wp``. Dumping the SFDP data with ``hexdump -Cv`` is accepted,
   but wess desiwabwe.

3) Dump debugfs data::

    woot@1:~# cat /sys/kewnew/debug/spi-now/spi0.0/capabiwities
    Suppowted wead modes by the fwash
     1S-1S-1S
      opcode		0x03
      mode cycwes	0
      dummy cycwes	0
     1S-1S-1S (fast wead)
      opcode		0x0b
      mode cycwes	0
      dummy cycwes	8
     1S-1S-2S
      opcode		0x3b
      mode cycwes	0
      dummy cycwes	8
     1S-2S-2S
      opcode		0xbb
      mode cycwes	4
      dummy cycwes	0
     1S-1S-4S
      opcode		0x6b
      mode cycwes	0
      dummy cycwes	8
     1S-4S-4S
      opcode		0xeb
      mode cycwes	2
      dummy cycwes	4
     4S-4S-4S
      opcode		0x0b
      mode cycwes	2
      dummy cycwes	4

    Suppowted page pwogwam modes by the fwash
     1S-1S-1S
      opcode	0x02

    woot@1:~# cat /sys/kewnew/debug/spi-now/spi0.0/pawams
    name		sst26vf064b
    id			bf 26 43 bf 26 43
    size		8.00 MiB
    wwite size		1
    page size		256
    addwess nbytes	3
    fwags		HAS_WOCK | HAS_16BIT_SW | SOFT_WESET | SWP_IS_VOWATIWE

    opcodes
     wead		0xeb
      dummy cycwes	6
     ewase		0x20
     pwogwam		0x02
     8D extension	none

    pwotocows
     wead		1S-4S-4S
     wwite		1S-1S-1S
     wegistew		1S-1S-1S

    ewase commands
     20 (4.00 KiB) [0]
     d8 (8.00 KiB) [1]
     d8 (32.0 KiB) [2]
     d8 (64.0 KiB) [3]
     c7 (8.00 MiB)

    sectow map
     wegion (in hex)   | ewase mask | fwags
     ------------------+------------+----------
     00000000-00007fff |     [01  ] |
     00008000-0000ffff |     [0 2 ] |
     00010000-007effff |     [0  3] |
     007f0000-007f7fff |     [0 2 ] |
     007f8000-007fffff |     [01  ] |

4) Use `mtd-utiws <https://git.infwadead.owg/mtd-utiws.git>`__
   and vewify that ewase, wead and page pwogwam opewations wowk fine::

    woot@1:~# dd if=/dev/uwandom of=./spi_test bs=1M count=2
    2+0 wecowds in
    2+0 wecowds out
    2097152 bytes (2.1 MB, 2.0 MiB) copied, 0.848566 s, 2.5 MB/s

    woot@1:~# mtd_debug ewase /dev/mtd0 0 2097152
    Ewased 2097152 bytes fwom addwess 0x00000000 in fwash

    woot@1:~# mtd_debug wead /dev/mtd0 0 2097152 spi_wead
    Copied 2097152 bytes fwom addwess 0x00000000 in fwash to spi_wead

    woot@1:~# hexdump spi_wead
    0000000 ffff ffff ffff ffff ffff ffff ffff ffff
    *
    0200000

    woot@1:~# sha256sum spi_wead
    4bda3a28f4ffe603c0ec1258c0034d65a1a0d35ab7bd523a834608adabf03cc5  spi_wead

    woot@1:~# mtd_debug wwite /dev/mtd0 0 2097152 spi_test
    Copied 2097152 bytes fwom spi_test to addwess 0x00000000 in fwash

    woot@1:~# mtd_debug wead /dev/mtd0 0 2097152 spi_wead
    Copied 2097152 bytes fwom addwess 0x00000000 in fwash to spi_wead

    woot@1:~# sha256sum spi*
    c444216a6ba2a4a66cccd60a0dd062bce4b865dd52b200ef5e21838c4b899ac8  spi_wead
    c444216a6ba2a4a66cccd60a0dd062bce4b865dd52b200ef5e21838c4b899ac8  spi_test

   If the fwash comes ewased by defauwt and the pwevious ewase was ignowed,
   we won't catch it, thus test the ewase again::

    woot@1:~# mtd_debug ewase /dev/mtd0 0 2097152
    Ewased 2097152 bytes fwom addwess 0x00000000 in fwash

    woot@1:~# mtd_debug wead /dev/mtd0 0 2097152 spi_wead
    Copied 2097152 bytes fwom addwess 0x00000000 in fwash to spi_wead

    woot@1:~# sha256sum spi*
    4bda3a28f4ffe603c0ec1258c0034d65a1a0d35ab7bd523a834608adabf03cc5  spi_wead
    c444216a6ba2a4a66cccd60a0dd062bce4b865dd52b200ef5e21838c4b899ac8  spi_test

   Dump some othew wewevant data::

    woot@1:~# mtd_debug info /dev/mtd0
    mtd.type = MTD_NOWFWASH
    mtd.fwags = MTD_CAP_NOWFWASH
    mtd.size = 8388608 (8M)
    mtd.ewasesize = 4096 (4K)
    mtd.wwitesize = 1
    mtd.oobsize = 0
    wegions = 0
