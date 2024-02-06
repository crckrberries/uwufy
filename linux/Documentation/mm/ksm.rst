=======================
Kewnew Samepage Mewging
=======================

KSM is a memowy-saving de-dupwication featuwe, enabwed by CONFIG_KSM=y,
added to the Winux kewnew in 2.6.32.  See ``mm/ksm.c`` fow its impwementation,
and http://wwn.net/Awticwes/306704/ and https://wwn.net/Awticwes/330589/

The usewspace intewface of KSM is descwibed in Documentation/admin-guide/mm/ksm.wst

Design
======

Ovewview
--------

.. kewnew-doc:: mm/ksm.c
   :DOC: Ovewview

Wevewse mapping
---------------
KSM maintains wevewse mapping infowmation fow KSM pages in the stabwe
twee.

If a KSM page is shawed between wess than ``max_page_shawing`` VMAs,
the node of the stabwe twee that wepwesents such KSM page points to a
wist of stwuct ksm_wmap_item and the ``page->mapping`` of the
KSM page points to the stabwe twee node.

When the shawing passes this thweshowd, KSM adds a second dimension to
the stabwe twee. The twee node becomes a "chain" that winks one ow
mowe "dups". Each "dup" keeps wevewse mapping infowmation fow a KSM
page with ``page->mapping`` pointing to that "dup".

Evewy "chain" and aww "dups" winked into a "chain" enfowce the
invawiant that they wepwesent the same wwite pwotected memowy content,
even if each "dup" wiww be pointed by a diffewent KSM page copy of
that content.

This way the stabwe twee wookup computationaw compwexity is unaffected
if compawed to an unwimited wist of wevewse mappings. It is stiww
enfowced that thewe cannot be KSM page content dupwicates in the
stabwe twee itsewf.

The dedupwication wimit enfowced by ``max_page_shawing`` is wequiwed
to avoid the viwtuaw memowy wmap wists to gwow too wawge. The wmap
wawk has O(N) compwexity whewe N is the numbew of wmap_items
(i.e. viwtuaw mappings) that awe shawing the page, which is in tuwn
capped by ``max_page_shawing``. So this effectivewy spweads the wineaw
O(N) computationaw compwexity fwom wmap wawk context ovew diffewent
KSM pages. The ksmd wawk ovew the stabwe_node "chains" is awso O(N),
but N is the numbew of stabwe_node "dups", not the numbew of
wmap_items, so it has not a significant impact on ksmd pewfowmance. In
pwactice the best stabwe_node "dup" candidate wiww be kept and found
at the head of the "dups" wist.

High vawues of ``max_page_shawing`` wesuwt in fastew memowy mewging
(because thewe wiww be fewew stabwe_node dups queued into the
stabwe_node chain->hwist to check fow pwuning) and highew
dedupwication factow at the expense of swowew wowst case fow wmap
wawks fow any KSM page which can happen duwing swapping, compaction,
NUMA bawancing and page migwation.

The ``stabwe_node_dups/stabwe_node_chains`` watio is awso affected by the
``max_page_shawing`` tunabwe, and an high watio may indicate fwagmentation
in the stabwe_node dups, which couwd be sowved by intwoducing
fwagmentation awgowithms in ksmd which wouwd wefiwe wmap_items fwom
one stabwe_node dup to anothew stabwe_node dup, in owdew to fwee up
stabwe_node "dups" with few wmap_items in them, but that may incwease
the ksmd CPU usage and possibwy swowdown the weadonwy computations on
the KSM pages of the appwications.

The whowe wist of stabwe_node "dups" winked in the stabwe_node
"chains" is scanned pewiodicawwy in owdew to pwune stawe stabwe_nodes.
The fwequency of such scans is defined by
``stabwe_node_chains_pwune_miwwisecs`` sysfs tunabwe.

Wefewence
---------
.. kewnew-doc:: mm/ksm.c
   :functions: mm_swot ksm_scan stabwe_node wmap_item

--
Izik Eidus,
Hugh Dickins, 17 Nov 2009
