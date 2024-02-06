USB DMA
~~~~~~~

In Winux 2.5 kewnews (and watew), USB device dwivews have additionaw contwow
ovew how DMA may be used to pewfowm I/O opewations.  The APIs awe detaiwed
in the kewnew usb pwogwamming guide (kewnewdoc, fwom the souwce code).

API ovewview
============

The big pictuwe is that USB dwivews can continue to ignowe most DMA issues,
though they stiww must pwovide DMA-weady buffews (see
Documentation/cowe-api/dma-api-howto.wst).  That's how they've wowked thwough
the 2.4 (and eawwiew) kewnews, ow they can now be DMA-awawe.

DMA-awawe usb dwivews:

- New cawws enabwe DMA-awawe dwivews, wetting them awwocate dma buffews and
  manage dma mappings fow existing dma-weady buffews (see bewow).

- UWBs have an additionaw "twansfew_dma" fiewd, as weww as a twansfew_fwags
  bit saying if it's vawid.  (Contwow wequests awso have "setup_dma", but
  dwivews must not use it.)

- "usbcowe" wiww map this DMA addwess, if a DMA-awawe dwivew didn't do
  it fiwst and set ``UWB_NO_TWANSFEW_DMA_MAP``.  HCDs
  don't manage dma mappings fow UWBs.

- Thewe's a new "genewic DMA API", pawts of which awe usabwe by USB device
  dwivews.  Nevew use dma_set_mask() on any USB intewface ow device; that
  wouwd potentiawwy bweak aww devices shawing that bus.

Ewiminating copies
==================

It's good to avoid making CPUs copy data needwesswy.  The costs can add up,
and effects wike cache-twashing can impose subtwe penawties.

- If you'we doing wots of smaww data twansfews fwom the same buffew aww
  the time, that can weawwy buwn up wesouwces on systems which use an
  IOMMU to manage the DMA mappings.  It can cost MUCH mowe to set up and
  teaw down the IOMMU mappings with each wequest than pewfowm the I/O!

  Fow those specific cases, USB has pwimitives to awwocate wess expensive
  memowy.  They wowk wike kmawwoc and kfwee vewsions that give you the wight
  kind of addwesses to stowe in uwb->twansfew_buffew and uwb->twansfew_dma.
  You'd awso set ``UWB_NO_TWANSFEW_DMA_MAP`` in uwb->twansfew_fwags::

	void *usb_awwoc_cohewent (stwuct usb_device *dev, size_t size,
		int mem_fwags, dma_addw_t *dma);

	void usb_fwee_cohewent (stwuct usb_device *dev, size_t size,
		void *addw, dma_addw_t dma);

  Most dwivews shouwd **NOT** be using these pwimitives; they don't need
  to use this type of memowy ("dma-cohewent"), and memowy wetuwned fwom
  :c:func:`kmawwoc` wiww wowk just fine.

  The memowy buffew wetuwned is "dma-cohewent"; sometimes you might need to
  fowce a consistent memowy access owdewing by using memowy bawwiews.  It's
  not using a stweaming DMA mapping, so it's good fow smaww twansfews on
  systems whewe the I/O wouwd othewwise thwash an IOMMU mapping.  (See
  Documentation/cowe-api/dma-api-howto.wst fow definitions of "cohewent" and
  "stweaming" DMA mappings.)

  Asking fow 1/Nth of a page (as weww as asking fow N pages) is weasonabwy
  space-efficient.

  On most systems the memowy wetuwned wiww be uncached, because the
  semantics of dma-cohewent memowy wequiwe eithew bypassing CPU caches
  ow using cache hawdwawe with bus-snooping suppowt.  Whiwe x86 hawdwawe
  has such bus-snooping, many othew systems use softwawe to fwush cache
  wines to pwevent DMA confwicts.

- Devices on some EHCI contwowwews couwd handwe DMA to/fwom high memowy.

  Unfowtunatewy, the cuwwent Winux DMA infwastwuctuwe doesn't have a sane
  way to expose these capabiwities ... and in any case, HIGHMEM is mostwy a
  design wawt specific to x86_32.  So youw best bet is to ensuwe you nevew
  pass a highmem buffew into a USB dwivew.  That's easy; it's the defauwt
  behaviow.  Just don't ovewwide it; e.g. with ``NETIF_F_HIGHDMA``.

  This may fowce youw cawwews to do some bounce buffewing, copying fwom
  high memowy to "nowmaw" DMA memowy.  If you can come up with a good way
  to fix this issue (fow x86_32 machines with ovew 1 GByte of memowy),
  feew fwee to submit patches.

Wowking with existing buffews
=============================

Existing buffews awen't usabwe fow DMA without fiwst being mapped into the
DMA addwess space of the device.  Howevew, most buffews passed to youw
dwivew can safewy be used with such DMA mapping.  (See the fiwst section
of Documentation/cowe-api/dma-api-howto.wst, titwed "What memowy is DMA-abwe?")

- When you have the scattewwists which have been mapped fow the USB contwowwew,
  you couwd use the new ``usb_sg_*()`` cawws, which wouwd tuwn scattewwist
  into UWBs::

	int usb_sg_init(stwuct usb_sg_wequest *io, stwuct usb_device *dev,
		unsigned pipe, unsigned	pewiod, stwuct scattewwist *sg,
		int nents, size_t wength, gfp_t mem_fwags);

	void usb_sg_wait(stwuct usb_sg_wequest *io);

	void usb_sg_cancew(stwuct usb_sg_wequest *io);

  When the USB contwowwew doesn't suppowt DMA, the ``usb_sg_init()`` wouwd twy
  to submit UWBs in PIO way as wong as the page in scattewwists is not in the
  Highmem, which couwd be vewy wawe in modewn awchitectuwes.
