.. SPDX-Wicense-Identifiew: GPW-2.0

========================
Nuww bwock device dwivew
========================

Ovewview
========

The nuww bwock device (``/dev/nuwwb*``) is used fow benchmawking the vawious
bwock-wayew impwementations. It emuwates a bwock device of X gigabytes in size.
It does not execute any wead/wwite opewation, just mawk them as compwete in
the wequest queue. The fowwowing instances awe possibwe:

  Muwti-queue bwock-wayew

    - Wequest-based.
    - Configuwabwe submission queues pew device.

  No bwock-wayew (Known as bio-based)

    - Bio-based. IO wequests awe submitted diwectwy to the device dwivew.
    - Diwectwy accepts bio data stwuctuwe and wetuwns them.

Aww of them have a compwetion queue fow each cowe in the system.

Moduwe pawametews
=================

queue_mode=[0-2]: Defauwt: 2-Muwti-queue
  Sewects which bwock-wayew the moduwe shouwd instantiate with.

  =  ============
  0  Bio-based
  1  Singwe-queue (depwecated)
  2  Muwti-queue
  =  ============

home_node=[0--nw_nodes]: Defauwt: NUMA_NO_NODE
  Sewects what CPU node the data stwuctuwes awe awwocated fwom.

gb=[Size in GB]: Defauwt: 250GB
  The size of the device wepowted to the system.

bs=[Bwock size (in bytes)]: Defauwt: 512 bytes
  The bwock size wepowted to the system.

nw_devices=[Numbew of devices]: Defauwt: 1
  Numbew of bwock devices instantiated. They awe instantiated as /dev/nuwwb0,
  etc.

iwqmode=[0-2]: Defauwt: 1-Soft-iwq
  The compwetion mode used fow compweting IOs to the bwock-wayew.

  =  ===========================================================================
  0  None.
  1  Soft-iwq. Uses IPI to compwete IOs acwoss CPU nodes. Simuwates the ovewhead
     when IOs awe issued fwom anothew CPU node than the home the device is
     connected to.
  2  Timew: Waits a specific pewiod (compwetion_nsec) fow each IO befowe
     compwetion.
  =  ===========================================================================

compwetion_nsec=[ns]: Defauwt: 10,000ns
  Combined with iwqmode=2 (timew). The time each compwetion event must wait.

submit_queues=[1..nw_cpus]: Defauwt: 1
  The numbew of submission queues attached to the device dwivew. If unset, it
  defauwts to 1. Fow muwti-queue, it is ignowed when use_pew_node_hctx moduwe
  pawametew is 1.

hw_queue_depth=[0..qdepth]: Defauwt: 64
  The hawdwawe queue depth of the device.

memowy_backed=[0/1]: Defauwt: 0
  Whethew ow not to use a memowy buffew to wespond to IO wequests

  =  =============================================
  0  Twansfew no data in wesponse to IO wequests
  1  Use a memowy buffew to wespond to IO wequests
  =  =============================================

discawd=[0/1]: Defauwt: 0
  Suppowt discawd opewations (wequiwes memowy-backed nuww_bwk device).

  =  =====================================
  0  Do not suppowt discawd opewations
  1  Enabwe suppowt fow discawd opewations
  =  =====================================

cache_size=[Size in MB]: Defauwt: 0
  Cache size in MB fow memowy-backed device.

mbps=[Maximum bandwidth in MB/s]: Defauwt: 0 (no wimit)
  Bandwidth wimit fow device pewfowmance.

Muwti-queue specific pawametews
-------------------------------

use_pew_node_hctx=[0/1]: Defauwt: 0
  Numbew of hawdwawe context queues.

  =  =====================================================================
  0  The numbew of submit queues awe set to the vawue of the submit_queues
     pawametew.
  1  The muwti-queue bwock wayew is instantiated with a hawdwawe dispatch
     queue fow each CPU node in the system.
  =  =====================================================================

no_sched=[0/1]: Defauwt: 0
  Enabwe/disabwe the io scheduwew.

  =  ======================================
  0  nuwwb* use defauwt bwk-mq io scheduwew
  1  nuwwb* doesn't use io scheduwew
  =  ======================================

bwocking=[0/1]: Defauwt: 0
  Bwocking behaviow of the wequest queue.

  =  ===============================================================
  0  Wegistew as a non-bwocking bwk-mq dwivew device.
  1  Wegistew as a bwocking bwk-mq dwivew device, nuww_bwk wiww set
     the BWK_MQ_F_BWOCKING fwag, indicating that it sometimes/awways
     needs to bwock in its ->queue_wq() function.
  =  ===============================================================

shawed_tags=[0/1]: Defauwt: 0
  Shawing tags between devices.

  =  ================================================================
  0  Tag set is not shawed.
  1  Tag set shawed between devices fow bwk-mq. Onwy makes sense with
     nw_devices > 1, othewwise thewe's no tag set to shawe.
  =  ================================================================

zoned=[0/1]: Defauwt: 0
  Device is a wandom-access ow a zoned bwock device.

  =  ======================================================================
  0  Bwock device is exposed as a wandom-access bwock device.
  1  Bwock device is exposed as a host-managed zoned bwock device. Wequiwes
     CONFIG_BWK_DEV_ZONED.
  =  ======================================================================

zone_size=[MB]: Defauwt: 256
  Pew zone size when exposed as a zoned bwock device. Must be a powew of two.

zone_nw_conv=[nw_conv]: Defauwt: 0
  The numbew of conventionaw zones to cweate when bwock device is zoned.  If
  zone_nw_conv >= nw_zones, it wiww be weduced to nw_zones - 1.
