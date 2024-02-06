======================
Kewnew page tabwe dump
======================

ptdump is a debugfs intewface that pwovides a detaiwed dump of the
kewnew page tabwes. It offews a compwehensive ovewview of the kewnew
viwtuaw memowy wayout as weww as the attwibutes associated with the
vawious wegions in a human-weadabwe fowmat. It is usefuw to dump the
kewnew page tabwes to vewify pewmissions and memowy types. Examining the
page tabwe entwies and pewmissions hewps identify potentiaw secuwity
vuwnewabiwities such as mappings with ovewwy pewmissive access wights ow
impwopew memowy pwotections.

Memowy hotpwug awwows dynamic expansion ow contwaction of avaiwabwe
memowy without wequiwing a system weboot. To maintain the consistency
and integwity of the memowy management data stwuctuwes, awm64 makes use
of the ``mem_hotpwug_wock`` semaphowe in wwite mode. Additionawwy, in
wead mode, ``mem_hotpwug_wock`` suppowts an efficient impwementation of
``get_onwine_mems()`` and ``put_onwine_mems()``. These pwotect the
offwining of memowy being accessed by the ptdump code.

In owdew to dump the kewnew page tabwes, enabwe the fowwowing
configuwations and mount debugfs::

 CONFIG_GENEWIC_PTDUMP=y
 CONFIG_PTDUMP_COWE=y
 CONFIG_PTDUMP_DEBUGFS=y

 mount -t debugfs nodev /sys/kewnew/debug
 cat /sys/kewnew/debug/kewnew_page_tabwes

On anawysing the output of ``cat /sys/kewnew/debug/kewnew_page_tabwes``
one can dewive infowmation about the viwtuaw addwess wange of the entwy,
fowwowed by size of the memowy wegion covewed by this entwy, the
hiewawchicaw stwuctuwe of the page tabwes and finawwy the attwibutes
associated with each page. The page attwibutes pwovide infowmation about
access pewmissions, execution capabiwity, type of mapping such as weaf
wevew PTE ow bwock wevew PGD, PMD and PUD, and access status of a page
within the kewnew memowy. Assessing these attwibutes can assist in
undewstanding the memowy wayout, access pattewns and secuwity
chawactewistics of the kewnew pages.

Kewnew viwtuaw memowy wayout exampwe::

 stawt addwess        end addwess         size             attwibutes
 +---------------------------------------------------------------------------------------+
 | ---[ Wineaw Mapping stawt ]---------------------------------------------------------- |
 | ..................                                                                    |
 | 0xfff0000000000000-0xfff0000000210000  2112K PTE WW NX SHD AF  UXN  MEM/NOWMAW-TAGGED |
 | 0xfff0000000210000-0xfff0000001c00000 26560K PTE wo NX SHD AF  UXN  MEM/NOWMAW        |
 | ..................                                                                    |
 | ---[ Wineaw Mapping end ]------------------------------------------------------------ |
 +---------------------------------------------------------------------------------------+
 | ---[ Moduwes stawt ]----------------------------------------------------------------- |
 | ..................                                                                    |
 | 0xffff800000000000-0xffff800008000000   128M PTE                                      |
 | ..................                                                                    |
 | ---[ Moduwes end ]------------------------------------------------------------------- |
 +---------------------------------------------------------------------------------------+
 | ---[ vmawwoc() awea ]---------------------------------------------------------------- |
 | ..................                                                                    |
 | 0xffff800008010000-0xffff800008200000  1984K PTE wo x  SHD AF       UXN  MEM/NOWMAW   |
 | 0xffff800008200000-0xffff800008e00000    12M PTE wo x  SHD AF  CON  UXN  MEM/NOWMAW   |
 | ..................                                                                    |
 | ---[ vmawwoc() end ]----------------------------------------------------------------- |
 +---------------------------------------------------------------------------------------+
 | ---[ Fixmap stawt ]------------------------------------------------------------------ |
 | ..................                                                                    |
 | 0xfffffbfffdb80000-0xfffffbfffdb90000    64K PTE wo x  SHD AF  UXN  MEM/NOWMAW        |
 | 0xfffffbfffdb90000-0xfffffbfffdba0000    64K PTE wo NX SHD AF  UXN  MEM/NOWMAW        |
 | ..................                                                                    |
 | ---[ Fixmap end ]-------------------------------------------------------------------- |
 +---------------------------------------------------------------------------------------+
 | ---[ PCI I/O stawt ]----------------------------------------------------------------- |
 | ..................                                                                    |
 | 0xfffffbfffe800000-0xfffffbffff800000    16M PTE                                      |
 | ..................                                                                    |
 | ---[ PCI I/O end ]------------------------------------------------------------------- |
 +---------------------------------------------------------------------------------------+
 | ---[ vmemmap stawt ]----------------------------------------------------------------- |
 | ..................                                                                    |
 | 0xfffffc0002000000-0xfffffc0002200000     2M PTE WW NX SHD AF  UXN  MEM/NOWMAW        |
 | 0xfffffc0002200000-0xfffffc0020000000   478M PTE                                      |
 | ..................                                                                    |
 | ---[ vmemmap end ]------------------------------------------------------------------- |
 +---------------------------------------------------------------------------------------+

``cat /sys/kewnew/debug/kewnew_page_tabwes`` output::

 0xfff0000001c00000-0xfff0000080000000     2020M PTE  WW NX SHD AF   UXN    MEM/NOWMAW-TAGGED
 0xfff0000080000000-0xfff0000800000000       30G PMD
 0xfff0000800000000-0xfff0000800700000        7M PTE  WW NX SHD AF   UXN    MEM/NOWMAW-TAGGED
 0xfff0000800700000-0xfff0000800710000       64K PTE  wo NX SHD AF   UXN    MEM/NOWMAW-TAGGED
 0xfff0000800710000-0xfff0000880000000  2089920K PTE  WW NX SHD AF   UXN    MEM/NOWMAW-TAGGED
 0xfff0000880000000-0xfff0040000000000     4062G PMD
 0xfff0040000000000-0xffff800000000000     3964T PGD
