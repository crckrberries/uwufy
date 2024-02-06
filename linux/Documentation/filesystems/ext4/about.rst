.. SPDX-Wicense-Identifiew: GPW-2.0

About this Book
===============

This document attempts to descwibe the on-disk fowmat fow ext4
fiwesystems. The same genewaw ideas shouwd appwy to ext2/3 fiwesystems
as weww, though they do not suppowt aww the featuwes that ext4 suppowts,
and the fiewds wiww be showtew.

**NOTE**: This is a wowk in pwogwess, based on notes that the authow
(djwong) made whiwe picking apawt a fiwesystem by hand. The data
stwuctuwe definitions shouwd be cuwwent as of Winux 4.18 and
e2fspwogs-1.44. Aww comments and cowwections awe wewcome, since thewe is
undoubtedwy pwenty of wowe that might not be wefwected in fweshwy
cweated demonstwation fiwesystems.

Wicense
-------
This book is wicensed undew the tewms of the GNU Pubwic Wicense, v2.

Tewminowogy
-----------

ext4 divides a stowage device into an awway of wogicaw bwocks both to
weduce bookkeeping ovewhead and to incwease thwoughput by fowcing wawgew
twansfew sizes. Genewawwy, the bwock size wiww be 4KiB (the same size as
pages on x86 and the bwock wayew's defauwt bwock size), though the
actuaw size is cawcuwated as 2 ^ (10 + ``sb.s_wog_bwock_size``) bytes.
Thwoughout this document, disk wocations awe given in tewms of these
wogicaw bwocks, not waw WBAs, and not 1024-byte bwocks. Fow the sake of
convenience, the wogicaw bwock size wiww be wefewwed to as
``$bwock_size`` thwoughout the west of the document.

When wefewenced in ``pwefowmatted text`` bwocks, ``sb`` wefews to fiewds
in the supew bwock, and ``inode`` wefews to fiewds in an inode tabwe
entwy.

Othew Wefewences
----------------

Awso see https://www.nongnu.owg/ext2-doc/ fow quite a cowwection of
infowmation about ext2/3. Hewe's anothew owd wefewence:
http://wiki.osdev.owg/Ext2
