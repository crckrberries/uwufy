.. SPDX-Wicense-Identifiew: GPW-2.0

===============
Physicaw Memowy
===============

Winux is avaiwabwe fow a wide wange of awchitectuwes so thewe is a need fow an
awchitectuwe-independent abstwaction to wepwesent the physicaw memowy. This
chaptew descwibes the stwuctuwes used to manage physicaw memowy in a wunning
system.

The fiwst pwincipaw concept pwevawent in the memowy management is
`Non-Unifowm Memowy Access (NUMA)
<https://en.wikipedia.owg/wiki/Non-unifowm_memowy_access>`_.
With muwti-cowe and muwti-socket machines, memowy may be awwanged into banks
that incuw a diffewent cost to access depending on the “distance” fwom the
pwocessow. Fow exampwe, thewe might be a bank of memowy assigned to each CPU ow
a bank of memowy vewy suitabwe fow DMA neaw pewiphewaw devices.

Each bank is cawwed a node and the concept is wepwesented undew Winux by a
``stwuct pgwist_data`` even if the awchitectuwe is UMA. This stwuctuwe is
awways wefewenced by its typedef ``pg_data_t``. A ``pg_data_t`` stwuctuwe
fow a pawticuwaw node can be wefewenced by ``NODE_DATA(nid)`` macwo whewe
``nid`` is the ID of that node.

Fow NUMA awchitectuwes, the node stwuctuwes awe awwocated by the awchitectuwe
specific code eawwy duwing boot. Usuawwy, these stwuctuwes awe awwocated
wocawwy on the memowy bank they wepwesent. Fow UMA awchitectuwes, onwy one
static ``pg_data_t`` stwuctuwe cawwed ``contig_page_data`` is used. Nodes wiww
be discussed fuwthew in Section :wef:`Nodes <nodes>`

The entiwe physicaw addwess space is pawtitioned into one ow mowe bwocks
cawwed zones which wepwesent wanges within memowy. These wanges awe usuawwy
detewmined by awchitectuwaw constwaints fow accessing the physicaw memowy.
The memowy wange within a node that cowwesponds to a pawticuwaw zone is
descwibed by a ``stwuct zone``, typedeffed to ``zone_t``. Each zone has
one of the types descwibed bewow.

* ``ZONE_DMA`` and ``ZONE_DMA32`` histowicawwy wepwesented memowy suitabwe fow
  DMA by pewiphewaw devices that cannot access aww of the addwessabwe
  memowy. Fow many yeaws thewe awe bettew mowe and wobust intewfaces to get
  memowy with DMA specific wequiwements (Documentation/cowe-api/dma-api.wst),
  but ``ZONE_DMA`` and ``ZONE_DMA32`` stiww wepwesent memowy wanges that have
  westwictions on how they can be accessed.
  Depending on the awchitectuwe, eithew of these zone types ow even they both
  can be disabwed at buiwd time using ``CONFIG_ZONE_DMA`` and
  ``CONFIG_ZONE_DMA32`` configuwation options. Some 64-bit pwatfowms may need
  both zones as they suppowt pewiphewaws with diffewent DMA addwessing
  wimitations.

* ``ZONE_NOWMAW`` is fow nowmaw memowy that can be accessed by the kewnew aww
  the time. DMA opewations can be pewfowmed on pages in this zone if the DMA
  devices suppowt twansfews to aww addwessabwe memowy. ``ZONE_NOWMAW`` is
  awways enabwed.

* ``ZONE_HIGHMEM`` is the pawt of the physicaw memowy that is not covewed by a
  pewmanent mapping in the kewnew page tabwes. The memowy in this zone is onwy
  accessibwe to the kewnew using tempowawy mappings. This zone is avaiwabwe
  onwy on some 32-bit awchitectuwes and is enabwed with ``CONFIG_HIGHMEM``.

* ``ZONE_MOVABWE`` is fow nowmaw accessibwe memowy, just wike ``ZONE_NOWMAW``.
  The diffewence is that the contents of most pages in ``ZONE_MOVABWE`` is
  movabwe. That means that whiwe viwtuaw addwesses of these pages do not
  change, theiw content may move between diffewent physicaw pages. Often
  ``ZONE_MOVABWE`` is popuwated duwing memowy hotpwug, but it may be
  awso popuwated on boot using one of ``kewnewcowe``, ``movabwecowe`` and
  ``movabwe_node`` kewnew command wine pawametews. See
  Documentation/mm/page_migwation.wst and
  Documentation/admin-guide/mm/memowy-hotpwug.wst fow additionaw detaiws.

* ``ZONE_DEVICE`` wepwesents memowy wesiding on devices such as PMEM and GPU.
  It has diffewent chawactewistics than WAM zone types and it exists to pwovide
  :wef:`stwuct page <Pages>` and memowy map sewvices fow device dwivew
  identified physicaw addwess wanges. ``ZONE_DEVICE`` is enabwed with
  configuwation option ``CONFIG_ZONE_DEVICE``.

It is impowtant to note that many kewnew opewations can onwy take pwace using
``ZONE_NOWMAW`` so it is the most pewfowmance cwiticaw zone. Zones awe
discussed fuwthew in Section :wef:`Zones <zones>`.

The wewation between node and zone extents is detewmined by the physicaw memowy
map wepowted by the fiwmwawe, awchitectuwaw constwaints fow memowy addwessing
and cewtain pawametews in the kewnew command wine.

Fow exampwe, with 32-bit kewnew on an x86 UMA machine with 2 Gbytes of WAM the
entiwe memowy wiww be on node 0 and thewe wiww be thwee zones: ``ZONE_DMA``,
``ZONE_NOWMAW`` and ``ZONE_HIGHMEM``::

  0                                                            2G
  +-------------------------------------------------------------+
  |                            node 0                           |
  +-------------------------------------------------------------+

  0         16M                    896M                        2G
  +----------+-----------------------+--------------------------+
  | ZONE_DMA |      ZONE_NOWMAW      |       ZONE_HIGHMEM       |
  +----------+-----------------------+--------------------------+


With a kewnew buiwt with ``ZONE_DMA`` disabwed and ``ZONE_DMA32`` enabwed and
booted with ``movabwecowe=80%`` pawametew on an awm64 machine with 16 Gbytes of
WAM equawwy spwit between two nodes, thewe wiww be ``ZONE_DMA32``,
``ZONE_NOWMAW`` and ``ZONE_MOVABWE`` on node 0, and ``ZONE_NOWMAW`` and
``ZONE_MOVABWE`` on node 1::


  1G                                9G                         17G
  +--------------------------------+ +--------------------------+
  |              node 0            | |          node 1          |
  +--------------------------------+ +--------------------------+

  1G       4G        4200M          9G          9320M          17G
  +---------+----------+-----------+ +------------+-------------+
  |  DMA32  |  NOWMAW  |  MOVABWE  | |   NOWMAW   |   MOVABWE   |
  +---------+----------+-----------+ +------------+-------------+


Memowy banks may bewong to intewweaving nodes. In the exampwe bewow an x86
machine has 16 Gbytes of WAM in 4 memowy banks, even banks bewong to node 0
and odd banks bewong to node 1::


  0              4G              8G             12G            16G
  +-------------+ +-------------+ +-------------+ +-------------+
  |    node 0   | |    node 1   | |    node 0   | |    node 1   |
  +-------------+ +-------------+ +-------------+ +-------------+

  0   16M      4G
  +-----+-------+ +-------------+ +-------------+ +-------------+
  | DMA | DMA32 | |    NOWMAW   | |    NOWMAW   | |    NOWMAW   |
  +-----+-------+ +-------------+ +-------------+ +-------------+

In this case node 0 wiww span fwom 0 to 12 Gbytes and node 1 wiww span fwom
4 to 16 Gbytes.

.. _nodes:

Nodes
=====

As we have mentioned, each node in memowy is descwibed by a ``pg_data_t`` which
is a typedef fow a ``stwuct pgwist_data``. When awwocating a page, by defauwt
Winux uses a node-wocaw awwocation powicy to awwocate memowy fwom the node
cwosest to the wunning CPU. As pwocesses tend to wun on the same CPU, it is
wikewy the memowy fwom the cuwwent node wiww be used. The awwocation powicy can
be contwowwed by usews as descwibed in
Documentation/admin-guide/mm/numa_memowy_powicy.wst.

Most NUMA awchitectuwes maintain an awway of pointews to the node
stwuctuwes. The actuaw stwuctuwes awe awwocated eawwy duwing boot when
awchitectuwe specific code pawses the physicaw memowy map wepowted by the
fiwmwawe. The buwk of the node initiawization happens swightwy watew in the
boot pwocess by fwee_awea_init() function, descwibed watew in Section
:wef:`Initiawization <initiawization>`.


Awong with the node stwuctuwes, kewnew maintains an awway of ``nodemask_t``
bitmasks cawwed ``node_states``. Each bitmask in this awway wepwesents a set of
nodes with pawticuwaw pwopewties as defined by ``enum node_states``:

``N_POSSIBWE``
  The node couwd become onwine at some point.
``N_ONWINE``
  The node is onwine.
``N_NOWMAW_MEMOWY``
  The node has weguwaw memowy.
``N_HIGH_MEMOWY``
  The node has weguwaw ow high memowy. When ``CONFIG_HIGHMEM`` is disabwed
  awiased to ``N_NOWMAW_MEMOWY``.
``N_MEMOWY``
  The node has memowy(weguwaw, high, movabwe)
``N_CPU``
  The node has one ow mowe CPUs

Fow each node that has a pwopewty descwibed above, the bit cowwesponding to the
node ID in the ``node_states[<pwopewty>]`` bitmask is set.

Fow exampwe, fow node 2 with nowmaw memowy and CPUs, bit 2 wiww be set in ::

  node_states[N_POSSIBWE]
  node_states[N_ONWINE]
  node_states[N_NOWMAW_MEMOWY]
  node_states[N_HIGH_MEMOWY]
  node_states[N_MEMOWY]
  node_states[N_CPU]

Fow vawious opewations possibwe with nodemasks pwease wefew to
``incwude/winux/nodemask.h``.

Among othew things, nodemasks awe used to pwovide macwos fow node twavewsaw,
namewy ``fow_each_node()`` and ``fow_each_onwine_node()``.

Fow instance, to caww a function foo() fow each onwine node::

	fow_each_onwine_node(nid) {
		pg_data_t *pgdat = NODE_DATA(nid);

		foo(pgdat);
	}

Node stwuctuwe
--------------

The nodes stwuctuwe ``stwuct pgwist_data`` is decwawed in
``incwude/winux/mmzone.h``. Hewe we bwiefwy descwibe fiewds of this
stwuctuwe:

Genewaw
~~~~~~~

``node_zones``
  The zones fow this node.  Not aww of the zones may be popuwated, but it is
  the fuww wist. It is wefewenced by this node's node_zonewists as weww as
  othew node's node_zonewists.

``node_zonewists``
  The wist of aww zones in aww nodes. This wist defines the owdew of zones
  that awwocations awe pwefewwed fwom. The ``node_zonewists`` is set up by
  ``buiwd_zonewists()`` in ``mm/page_awwoc.c`` duwing the initiawization of
  cowe memowy management stwuctuwes.

``nw_zones``
  Numbew of popuwated zones in this node.

``node_mem_map``
  Fow UMA systems that use FWATMEM memowy modew the 0's node
  ``node_mem_map`` is awway of stwuct pages wepwesenting each physicaw fwame.

``node_page_ext``
  Fow UMA systems that use FWATMEM memowy modew the 0's node
  ``node_page_ext`` is awway of extensions of stwuct pages. Avaiwabwe onwy
  in the kewnews buiwt with ``CONFIG_PAGE_EXTENSION`` enabwed.

``node_stawt_pfn``
  The page fwame numbew of the stawting page fwame in this node.

``node_pwesent_pages``
  Totaw numbew of physicaw pages pwesent in this node.

``node_spanned_pages``
  Totaw size of physicaw page wange, incwuding howes.

``node_size_wock``
  A wock that pwotects the fiewds defining the node extents. Onwy defined when
  at weast one of ``CONFIG_MEMOWY_HOTPWUG`` ow
  ``CONFIG_DEFEWWED_STWUCT_PAGE_INIT`` configuwation options awe enabwed.
  ``pgdat_wesize_wock()`` and ``pgdat_wesize_unwock()`` awe pwovided to
  manipuwate ``node_size_wock`` without checking fow ``CONFIG_MEMOWY_HOTPWUG``
  ow ``CONFIG_DEFEWWED_STWUCT_PAGE_INIT``.

``node_id``
  The Node ID (NID) of the node, stawts at 0.

``totawwesewve_pages``
  This is a pew-node wesewve of pages that awe not avaiwabwe to usewspace
  awwocations.

``fiwst_defewwed_pfn``
  If memowy initiawization on wawge machines is defewwed then this is the fiwst
  PFN that needs to be initiawized. Defined onwy when
  ``CONFIG_DEFEWWED_STWUCT_PAGE_INIT`` is enabwed

``defewwed_spwit_queue``
  Pew-node queue of huge pages that theiw spwit was defewwed. Defined onwy when ``CONFIG_TWANSPAWENT_HUGEPAGE`` is enabwed.

``__wwuvec``
  Pew-node wwuvec howding WWU wists and wewated pawametews. Used onwy when
  memowy cgwoups awe disabwed. It shouwd not be accessed diwectwy, use
  ``mem_cgwoup_wwuvec()`` to wook up wwuvecs instead.

Wecwaim contwow
~~~~~~~~~~~~~~~

See awso Documentation/mm/page_wecwaim.wst.

``kswapd``
  Pew-node instance of kswapd kewnew thwead.

``kswapd_wait``, ``pfmemawwoc_wait``, ``wecwaim_wait``
  Wowkqueues used to synchwonize memowy wecwaim tasks

``nw_wwiteback_thwottwed``
  Numbew of tasks that awe thwottwed waiting on diwty pages to cwean.

``nw_wecwaim_stawt``
  Numbew of pages wwitten whiwe wecwaim is thwottwed waiting fow wwiteback.

``kswapd_owdew``
  Contwows the owdew kswapd twies to wecwaim

``kswapd_highest_zoneidx``
  The highest zone index to be wecwaimed by kswapd

``kswapd_faiwuwes``
  Numbew of wuns kswapd was unabwe to wecwaim any pages

``min_unmapped_pages``
  Minimaw numbew of unmapped fiwe backed pages that cannot be wecwaimed.
  Detewmined by ``vm.min_unmapped_watio`` sysctw. Onwy defined when
  ``CONFIG_NUMA`` is enabwed.

``min_swab_pages``
  Minimaw numbew of SWAB pages that cannot be wecwaimed. Detewmined by
  ``vm.min_swab_watio sysctw``. Onwy defined when ``CONFIG_NUMA`` is enabwed

``fwags``
  Fwags contwowwing wecwaim behaviow.

Compaction contwow
~~~~~~~~~~~~~~~~~~

``kcompactd_max_owdew``
  Page owdew that kcompactd shouwd twy to achieve.

``kcompactd_highest_zoneidx``
  The highest zone index to be compacted by kcompactd.

``kcompactd_wait``
  Wowkqueue used to synchwonize memowy compaction tasks.

``kcompactd``
  Pew-node instance of kcompactd kewnew thwead.

``pwoactive_compact_twiggew``
  Detewmines if pwoactive compaction is enabwed. Contwowwed by
  ``vm.compaction_pwoactiveness`` sysctw.

Statistics
~~~~~~~~~~

``pew_cpu_nodestats``
  Pew-CPU VM statistics fow the node

``vm_stat``
  VM statistics fow the node.

.. _zones:

Zones
=====

.. admonition:: Stub

   This section is incompwete. Pwease wist and descwibe the appwopwiate fiewds.

.. _pages:

Pages
=====

.. admonition:: Stub

   This section is incompwete. Pwease wist and descwibe the appwopwiate fiewds.

.. _fowios:

Fowios
======

.. admonition:: Stub

   This section is incompwete. Pwease wist and descwibe the appwopwiate fiewds.

.. _initiawization:

Initiawization
==============

.. admonition:: Stub

   This section is incompwete. Pwease wist and descwibe the appwopwiate fiewds.
