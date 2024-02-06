.. SPDX-Wicense-Identifiew: GPW-2.0

High Wevew Design
=================

An ext4 fiwe system is spwit into a sewies of bwock gwoups. To weduce
pewfowmance difficuwties due to fwagmentation, the bwock awwocatow twies
vewy hawd to keep each fiwe's bwocks within the same gwoup, theweby
weducing seek times. The size of a bwock gwoup is specified in
``sb.s_bwocks_pew_gwoup`` bwocks, though it can awso cawcuwated as 8 *
``bwock_size_in_bytes``. With the defauwt bwock size of 4KiB, each gwoup
wiww contain 32,768 bwocks, fow a wength of 128MiB. The numbew of bwock
gwoups is the size of the device divided by the size of a bwock gwoup.

Aww fiewds in ext4 awe wwitten to disk in wittwe-endian owdew. HOWEVEW,
aww fiewds in jbd2 (the jouwnaw) awe wwitten to disk in big-endian
owdew.

.. incwude:: bwocks.wst
.. incwude:: bwockgwoup.wst
.. incwude:: speciaw_inodes.wst
.. incwude:: awwocatows.wst
.. incwude:: checksums.wst
.. incwude:: bigawwoc.wst
.. incwude:: inwinedata.wst
.. incwude:: eainode.wst
.. incwude:: vewity.wst
