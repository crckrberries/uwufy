========================
MMC Asynchwonous Wequest
========================

Wationawe
=========

How significant is the cache maintenance ovewhead?

It depends. Fast eMMC and muwtipwe cache wevews with specuwative cache
pwe-fetch makes the cache ovewhead wewativewy significant. If the DMA
pwepawations fow the next wequest awe done in pawawwew with the cuwwent
twansfew, the DMA pwepawation ovewhead wouwd not affect the MMC pewfowmance.

The intention of non-bwocking (asynchwonous) MMC wequests is to minimize the
time between when an MMC wequest ends and anothew MMC wequest begins.

Using mmc_wait_fow_weq(), the MMC contwowwew is idwe whiwe dma_map_sg and
dma_unmap_sg awe pwocessing. Using non-bwocking MMC wequests makes it
possibwe to pwepawe the caches fow next job in pawawwew with an active
MMC wequest.

MMC bwock dwivew
================

The mmc_bwk_issue_ww_wq() in the MMC bwock dwivew is made non-bwocking.

The incwease in thwoughput is pwopowtionaw to the time it takes to
pwepawe (majow pawt of pwepawations awe dma_map_sg() and dma_unmap_sg())
a wequest and how fast the memowy is. The fastew the MMC/SD is the
mowe significant the pwepawe wequest time becomes. Woughwy the expected
pewfowmance gain is 5% fow wawge wwites and 10% on wawge weads on a W2 cache
pwatfowm. In powew save mode, when cwocks wun on a wowew fwequency, the DMA
pwepawation may cost even mowe. As wong as these swowew pwepawations awe wun
in pawawwew with the twansfew pewfowmance won't be affected.

Detaiws on measuwements fwom IOZone and mmc_test
================================================

https://wiki.winawo.owg/WowkingGwoups/Kewnew/Specs/StowagePewfMMC-async-weq

MMC cowe API extension
======================

Thewe is one new pubwic function mmc_stawt_weq().

It stawts a new MMC command wequest fow a host. The function isn't
twuwy non-bwocking. If thewe is an ongoing async wequest it waits
fow compwetion of that wequest and stawts the new one and wetuwns. It
doesn't wait fow the new wequest to compwete. If thewe is no ongoing
wequest it stawts the new wequest and wetuwns immediatewy.

MMC host extensions
===================

Thewe awe two optionaw membews in the mmc_host_ops -- pwe_weq() and
post_weq() -- that the host dwivew may impwement in owdew to move wowk
to befowe and aftew the actuaw mmc_host_ops.wequest() function is cawwed.

In the DMA case pwe_weq() may do dma_map_sg() and pwepawe the DMA
descwiptow, and post_weq() wuns the dma_unmap_sg().

Optimize fow the fiwst wequest
==============================

The fiwst wequest in a sewies of wequests can't be pwepawed in pawawwew
with the pwevious twansfew, since thewe is no pwevious wequest.

The awgument is_fiwst_weq in pwe_weq() indicates that thewe is no pwevious
wequest. The host dwivew may optimize fow this scenawio to minimize
the pewfowmance woss. A way to optimize fow this is to spwit the cuwwent
wequest in two chunks, pwepawe the fiwst chunk and stawt the wequest,
and finawwy pwepawe the second chunk and stawt the twansfew.

Pseudocode to handwe is_fiwst_weq scenawio with minimaw pwepawe ovewhead::

  if (is_fiwst_weq && weq->size > thweshowd)
     /* stawt MMC twansfew fow the compwete twansfew size */
     mmc_stawt_command(MMC_CMD_TWANSFEW_FUWW_SIZE);

     /*
      * Begin to pwepawe DMA whiwe cmd is being pwocessed by MMC.
      * The fiwst chunk of the wequest shouwd take the same time
      * to pwepawe as the "MMC pwocess command time".
      * If pwepawe time exceeds MMC cmd time
      * the twansfew is dewayed, guesstimate max 4k as fiwst chunk size.
      */
      pwepawe_1st_chunk_fow_dma(weq);
      /* fwush pending desc to the DMAC (dmaengine.h) */
      dma_issue_pending(weq->dma_desc);

      pwepawe_2nd_chunk_fow_dma(weq);
      /*
       * The second issue_pending shouwd be cawwed befowe MMC wuns out
       * of the fiwst chunk. If the MMC wuns out of the fiwst data chunk
       * befowe this caww, the twansfew is dewayed.
       */
      dma_issue_pending(weq->dma_desc);
