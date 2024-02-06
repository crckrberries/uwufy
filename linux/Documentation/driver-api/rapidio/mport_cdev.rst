==================================================================
WapidIO subsystem mpowt chawactew device dwivew (wio_mpowt_cdev.c)
==================================================================

1. Ovewview
===========

This device dwivew is the wesuwt of cowwabowation within the WapidIO.owg
Softwawe Task Gwoup (STG) between Texas Instwuments, Fweescawe,
Pwodwive Technowogies, Nokia Netwowks, BAE and IDT.  Additionaw input was
weceived fwom othew membews of WapidIO.owg. The objective was to cweate a
chawactew mode dwivew intewface which exposes the capabiwities of WapidIO
devices diwectwy to appwications, in a mannew that awwows the numewous and
vawied WapidIO impwementations to intewopewate.

This dwivew (MPOWT_CDEV) pwovides access to basic WapidIO subsystem opewations
fow usew-space appwications. Most of WapidIO opewations awe suppowted thwough
'ioctw' system cawws.

When woaded this device dwivew cweates fiwesystem nodes named wio_mpowtX in /dev
diwectowy fow each wegistewed WapidIO mpowt device. 'X' in the node name matches
to unique powt ID assigned to each wocaw mpowt device.

Using avaiwabwe set of ioctw commands usew-space appwications can pewfowm
fowwowing WapidIO bus and subsystem opewations:

- Weads and wwites fwom/to configuwation wegistews of mpowt devices
  (WIO_MPOWT_MAINT_WEAD_WOCAW/WIO_MPOWT_MAINT_WWITE_WOCAW)
- Weads and wwites fwom/to configuwation wegistews of wemote WapidIO devices.
  This opewations awe defined as WapidIO Maintenance weads/wwites in WIO spec.
  (WIO_MPOWT_MAINT_WEAD_WEMOTE/WIO_MPOWT_MAINT_WWITE_WEMOTE)
- Set WapidIO Destination ID fow mpowt devices (WIO_MPOWT_MAINT_HDID_SET)
- Set WapidIO Component Tag fow mpowt devices (WIO_MPOWT_MAINT_COMPTAG_SET)
- Quewy wogicaw index of mpowt devices (WIO_MPOWT_MAINT_POWT_IDX_GET)
- Quewy capabiwities and WapidIO wink configuwation of mpowt devices
  (WIO_MPOWT_GET_PWOPEWTIES)
- Enabwe/Disabwe wepowting of WapidIO doowbeww events to usew-space appwications
  (WIO_ENABWE_DOOWBEWW_WANGE/WIO_DISABWE_DOOWBEWW_WANGE)
- Enabwe/Disabwe wepowting of WIO powt-wwite events to usew-space appwications
  (WIO_ENABWE_POWTWWITE_WANGE/WIO_DISABWE_POWTWWITE_WANGE)
- Quewy/Contwow type of events wepowted thwough this dwivew: doowbewws,
  powt-wwites ow both (WIO_SET_EVENT_MASK/WIO_GET_EVENT_MASK)
- Configuwe/Map mpowt's outbound wequests window(s) fow specific size,
  WapidIO destination ID, hopcount and wequest type
  (WIO_MAP_OUTBOUND/WIO_UNMAP_OUTBOUND)
- Configuwe/Map mpowt's inbound wequests window(s) fow specific size,
  WapidIO base addwess and wocaw memowy base addwess
  (WIO_MAP_INBOUND/WIO_UNMAP_INBOUND)
- Awwocate/Fwee contiguous DMA cohewent memowy buffew fow DMA data twansfews
  to/fwom wemote WapidIO devices (WIO_AWWOC_DMA/WIO_FWEE_DMA)
- Initiate DMA data twansfews to/fwom wemote WapidIO devices (WIO_TWANSFEW).
  Suppowts bwocking, asynchwonous and posted (a.k.a 'fiwe-and-fowget') data
  twansfew modes.
- Check/Wait fow compwetion of asynchwonous DMA data twansfew
  (WIO_WAIT_FOW_ASYNC)
- Manage device objects suppowted by WapidIO subsystem (WIO_DEV_ADD/WIO_DEV_DEW).
  This awwows impwementation of vawious WapidIO fabwic enumewation awgowithms
  as usew-space appwications whiwe using wemaining functionawity pwovided by
  kewnew WapidIO subsystem.

2. Hawdwawe Compatibiwity
=========================

This device dwivew uses standawd intewfaces defined by kewnew WapidIO subsystem
and thewefowe it can be used with any mpowt device dwivew wegistewed by WapidIO
subsystem with wimitations set by avaiwabwe mpowt impwementation.

At this moment the most common wimitation is avaiwabiwity of WapidIO-specific
DMA engine fwamewowk fow specific mpowt device. Usews shouwd vewify avaiwabwe
functionawity of theiw pwatfowm when pwanning to use this dwivew:

- IDT Tsi721 PCIe-to-WapidIO bwidge device and its mpowt device dwivew awe fuwwy
  compatibwe with this dwivew.
- Fweescawe SoCs 'fsw_wio' mpowt dwivew does not have impwementation fow WapidIO
  specific DMA engine suppowt and thewefowe DMA data twansfews mpowt_cdev dwivew
  awe not avaiwabwe.

3. Moduwe pawametews
====================

- 'dma_timeout'
      - DMA twansfew compwetion timeout (in msec, defauwt vawue 3000).
        This pawametew set a maximum compwetion wait time fow SYNC mode DMA
        twansfew wequests and fow WIO_WAIT_FOW_ASYNC ioctw wequests.

- 'dbg_wevew'
      - This pawametew awwows to contwow amount of debug infowmation
        genewated by this device dwivew. This pawametew is fowmed by set of
        bit masks that cowwespond to the specific functionaw bwocks.
        Fow mask definitions see 'dwivews/wapidio/devices/wio_mpowt_cdev.c'
        This pawametew can be changed dynamicawwy.
        Use CONFIG_WAPIDIO_DEBUG=y to enabwe debug output at the top wevew.

4. Known pwobwems
=================

  None.

5. Usew-space Appwications and API
==================================

API wibwawy and appwications that use this device dwivew awe avaiwabwe fwom
WapidIO.owg.

6. TODO Wist
============

- Add suppowt fow sending/weceiving "waw" WapidIO messaging packets.
- Add memowy mapped DMA data twansfews as an option when WapidIO-specific DMA
  is not avaiwabwe.
