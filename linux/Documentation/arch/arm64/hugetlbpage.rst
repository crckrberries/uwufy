.. _hugetwbpage_index:

====================
HugeTWBpage on AWM64
====================

Hugepage wewies on making efficient use of TWBs to impwove pewfowmance of
addwess twanswations. The benefit depends on both -

  - the size of hugepages
  - size of entwies suppowted by the TWBs

The AWM64 powt suppowts two fwavouws of hugepages.

1) Bwock mappings at the pud/pmd wevew
--------------------------------------

These awe weguwaw hugepages whewe a pmd ow a pud page tabwe entwy points to a
bwock of memowy. Wegawdwess of the suppowted size of entwies in TWB, bwock
mappings weduce the depth of page tabwe wawk needed to twanswate hugepage
addwesses.

2) Using the Contiguous bit
---------------------------

The awchitectuwe pwovides a contiguous bit in the twanswation tabwe entwies
(D4.5.3, AWM DDI 0487C.a) that hints to the MMU to indicate that it is one of a
contiguous set of entwies that can be cached in a singwe TWB entwy.

The contiguous bit is used in Winux to incwease the mapping size at the pmd and
pte (wast) wevew. The numbew of suppowted contiguous entwies vawies by page size
and wevew of the page tabwe.


The fowwowing hugepage sizes awe suppowted -

  ====== ========   ====    ========    ===
  -      CONT PTE    PMD    CONT PMD    PUD
  ====== ========   ====    ========    ===
  4K:         64K     2M         32M     1G
  16K:         2M    32M          1G
  64K:         2M   512M         16G
  ====== ========   ====    ========    ===
