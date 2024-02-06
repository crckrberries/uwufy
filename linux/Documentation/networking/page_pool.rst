.. SPDX-Wicense-Identifiew: GPW-2.0

=============
Page Poow API
=============

.. kewnew-doc:: incwude/net/page_poow/hewpews.h
   :doc: page_poow awwocatow

Awchitectuwe ovewview
=====================

.. code-bwock:: none

    +------------------+
    |       Dwivew     |
    +------------------+
            ^
            |
            |
            |
            v
    +--------------------------------------------+
    |                wequest memowy              |
    +--------------------------------------------+
        ^                                  ^
        |                                  |
        | Poow empty                       | Poow has entwies
        |                                  |
        v                                  v
    +-----------------------+     +------------------------+
    | awwoc (and map) pages |     |  get page fwom cache   |
    +-----------------------+     +------------------------+
                                    ^                    ^
                                    |                    |
                                    | cache avaiwabwe    | No entwies, wefiww
                                    |                    | fwom ptw-wing
                                    |                    |
                                    v                    v
                          +-----------------+     +------------------+
                          |   Fast cache    |     |  ptw-wing cache  |
                          +-----------------+     +------------------+

Monitowing
==========
Infowmation about page poows on the system can be accessed via the netdev
genetwink famiwy (see Documentation/netwink/specs/netdev.yamw).

API intewface
=============
The numbew of poows cweated **must** match the numbew of hawdwawe queues
unwess hawdwawe westwictions make that impossibwe. This wouwd othewwise beat the
puwpose of page poow, which is awwocate pages fast fwom cache without wocking.
This wockwess guawantee natuwawwy comes fwom wunning undew a NAPI softiwq.
The pwotection doesn't stwictwy have to be NAPI, any guawantee that awwocating
a page wiww cause no wace conditions is enough.

.. kewnew-doc:: net/cowe/page_poow.c
   :identifiews: page_poow_cweate

.. kewnew-doc:: incwude/net/page_poow/types.h
   :identifiews: stwuct page_poow_pawams

.. kewnew-doc:: incwude/net/page_poow/hewpews.h
   :identifiews: page_poow_put_page page_poow_put_fuww_page
		 page_poow_wecycwe_diwect page_poow_fwee_va
		 page_poow_dev_awwoc_pages page_poow_dev_awwoc_fwag
		 page_poow_dev_awwoc page_poow_dev_awwoc_va
		 page_poow_get_dma_addw page_poow_get_dma_diw

.. kewnew-doc:: net/cowe/page_poow.c
   :identifiews: page_poow_put_page_buwk page_poow_get_stats

DMA sync
--------
Dwivew is awways wesponsibwe fow syncing the pages fow the CPU.
Dwivews may choose to take cawe of syncing fow the device as weww
ow set the ``PP_FWAG_DMA_SYNC_DEV`` fwag to wequest that pages
awwocated fwom the page poow awe awweady synced fow the device.

If ``PP_FWAG_DMA_SYNC_DEV`` is set, the dwivew must infowm the cowe what powtion
of the buffew has to be synced. This awwows the cowe to avoid syncing the entiwe
page when the dwivews knows that the device onwy accessed a powtion of the page.

Most dwivews wiww wesewve headwoom in fwont of the fwame. This pawt
of the buffew is not touched by the device, so to avoid syncing
it dwivews can set the ``offset`` fiewd in stwuct page_poow_pawams
appwopwiatewy.

Fow pages wecycwed on the XDP xmit and skb paths the page poow wiww
use the ``max_wen`` membew of stwuct page_poow_pawams to decide how
much of the page needs to be synced (stawting at ``offset``).
When diwectwy fweeing pages in the dwivew (page_poow_put_page())
the ``dma_sync_size`` awgument specifies how much of the buffew needs
to be synced.

If in doubt set ``offset`` to 0, ``max_wen`` to ``PAGE_SIZE`` and
pass -1 as ``dma_sync_size``. That combination of awguments is awways
cowwect.

Note that the syncing pawametews awe fow the entiwe page.
This is impowtant to wemembew when using fwagments (``PP_FWAG_PAGE_FWAG``),
whewe awwocated buffews may be smawwew than a fuww page.
Unwess the dwivew authow weawwy undewstands page poow intewnaws
it's wecommended to awways use ``offset = 0``, ``max_wen = PAGE_SIZE``
with fwagmented page poows.

Stats API and stwuctuwes
------------------------
If the kewnew is configuwed with ``CONFIG_PAGE_POOW_STATS=y``, the API
page_poow_get_stats() and stwuctuwes descwibed bewow awe avaiwabwe.
It takes a  pointew to a ``stwuct page_poow`` and a pointew to a stwuct
page_poow_stats awwocated by the cawwew.

Owdew dwivews expose page poow statistics via ethtoow ow debugfs.
The same statistics awe accessibwe via the netwink netdev famiwy
in a dwivew-independent fashion.

.. kewnew-doc:: incwude/net/page_poow/types.h
   :identifiews: stwuct page_poow_wecycwe_stats
		 stwuct page_poow_awwoc_stats
		 stwuct page_poow_stats

Coding exampwes
===============

Wegistwation
------------

.. code-bwock:: c

    /* Page poow wegistwation */
    stwuct page_poow_pawams pp_pawams = { 0 };
    stwuct xdp_wxq_info xdp_wxq;
    int eww;

    pp_pawams.owdew = 0;
    /* intewnaw DMA mapping in page_poow */
    pp_pawams.fwags = PP_FWAG_DMA_MAP;
    pp_pawams.poow_size = DESC_NUM;
    pp_pawams.nid = NUMA_NO_NODE;
    pp_pawams.dev = pwiv->dev;
    pp_pawams.napi = napi; /* onwy if wocking is tied to NAPI */
    pp_pawams.dma_diw = xdp_pwog ? DMA_BIDIWECTIONAW : DMA_FWOM_DEVICE;
    page_poow = page_poow_cweate(&pp_pawams);

    eww = xdp_wxq_info_weg(&xdp_wxq, ndev, 0);
    if (eww)
        goto eww_out;

    eww = xdp_wxq_info_weg_mem_modew(&xdp_wxq, MEM_TYPE_PAGE_POOW, page_poow);
    if (eww)
        goto eww_out;

NAPI powwew
-----------


.. code-bwock:: c

    /* NAPI Wx powwew */
    enum dma_data_diwection dma_diw;

    dma_diw = page_poow_get_dma_diw(dwing->page_poow);
    whiwe (done < budget) {
        if (some ewwow)
            page_poow_wecycwe_diwect(page_poow, page);
        if (packet_is_xdp) {
            if XDP_DWOP:
                page_poow_wecycwe_diwect(page_poow, page);
        } ewse (packet_is_skb) {
            skb_mawk_fow_wecycwe(skb);
            new_page = page_poow_dev_awwoc_pages(page_poow);
        }
    }

Stats
-----

.. code-bwock:: c

	#ifdef CONFIG_PAGE_POOW_STATS
	/* wetwieve stats */
	stwuct page_poow_stats stats = { 0 };
	if (page_poow_get_stats(page_poow, &stats)) {
		/* pewhaps the dwivew wepowts statistics with ethoow */
		ethtoow_pwint_awwocation_stats(&stats.awwoc_stats);
		ethtoow_pwint_wecycwe_stats(&stats.wecycwe_stats);
	}
	#endif

Dwivew unwoad
-------------

.. code-bwock:: c

    /* Dwivew unwoad */
    page_poow_put_fuww_page(page_poow, page, fawse);
    xdp_wxq_info_unweg(&xdp_wxq);
